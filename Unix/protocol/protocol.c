/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <assert.h>
#include "protocol.h"
#include <sock/addr.h>
#include <sock/sock.h>
#include <sock/selector.h>
#include <base/buf.h>
#include <base/log.h>
#include <base/result.h>
#include <base/user.h>
#include <pal/strings.h>
#include <pal/format.h>
#include <pal/file.h>
#include <pal/sleep.h>

//#define  ENABLE_TRACING 1
#ifdef ENABLE_TRACING
//# define TRACING_LEVEL 4
#include <base/result.h>
#include <base/logbase.h>
#include <base/log.h>
#define LOGE2 __LOGE
#define LOGW2 __LOGW
#define LOGD2 __LOGD
#define mistrerror Result_ToString

#else
# define LOGE2(a)
# define LOGW2(a)
# define LOGD2(a)
# define LOGX2(a)
#endif

/*
**==============================================================================
**
** Local definitions:
**
**==============================================================================
*/

static const MI_Uint32 _MAGIC = 0xC764445E;

/*
**==============================================================================
*/
STRAND_DEBUGNAME1( ProtocolSocketServer, PostMsg )
STRAND_DEBUGNAME2( ProtocolFromSocket, PostMsg, ReadyToFinish )
STRAND_DEBUGNAME3( ProtocolConnector, PostMsg, ReadyToFinish, ConnectEvent )

/*
**==============================================================================
*/

ProtocolSocket* _ProtocolSocket_Server_New(
    _In_        ProtocolBase *          protocolBase,
    _In_        Sock                    sock );

/* helper functions result */
typedef enum _Protocol_CallbackResult
{
    PRT_CONTINUE,
    PRT_RETURN_TRUE,
    PRT_RETURN_FALSE
}
Protocol_CallbackResult;

/* Forward declaration */
static void _PrepareMessageForSending(
    ProtocolSocket *handler);

static MI_Boolean _RequestCallbackWrite(
    ProtocolSocket* handler);

static MI_Result _ProtocolSocketAndBase_Delete(
    ProtocolSocketAndBase* self);



/*
**==============================================================================
*/

static MI_Result _SendIN_IO_thread(
    ProtocolBase* self,
    ProtocolSocket* sendSock,
    Message* message);

static void _FreeAuthData(
    ProtocolSocket* h);

static void _ProtocolSocket_Cleanup(ProtocolSocket* handler);

/* Signature must not have return type so we created this wrapper */
static void _SendIN_IO_thread_wrapper(void* self_, Message* message)
{
    ProtocolSocket* self = (ProtocolSocket*) self_;
    ProtocolBase* protocolBase = (ProtocolBase*)self->base.data;
    MI_Result result;

    result = _SendIN_IO_thread( protocolBase, self, message);

    if(result != MI_RESULT_OK)
    {
        trace_ProtocolSocket_PostFailed( &self->strand.info.interaction, self->strand.info.interaction.other );
        // This will do following things
        // 1. cleaning up the message if any and acking it
        // 2. closing the other side
        // 3. Setting the closeOtherScheduled flag which will drop all further Posts after this one and also skip this logic in the SELECTOR_REMOVE callback
        _ProtocolSocket_Cleanup(self);
    }
}

MI_INLINE
void _ProtocolSocket_Release(
    _In_ ProtocolSocket* self,
    _In_ CallSite cs)
{
    ptrdiff_t ref = Atomic_Dec(&self->refCount);

#if defined(CONFIG_ENABLE_DEBUG)
    {
        trace_ProtocolSocket_Release(cs.file, (MI_Uint32)cs.line, self, (unsigned int)ref);
    }
#endif /* defined(CONFIG_ENABLE_DEBUG) */

    if (0 == ref)
        /* Free self pointer */
        PAL_Free(self);

    (void)cs;
}

#define ProtocolSocket_Release(self) \
    _ProtocolSocket_Release(self, CALLSITE)

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 28931) // unused assignment of variable ref
#endif /* _PREFAST_ */

MI_INLINE
void _ProtocolSocket_Addref(
    _In_ ProtocolSocket* self,
    _In_ CallSite cs)
{
    ptrdiff_t ref = Atomic_Inc(&self->refCount);

    (void)cs;
    ((void)ref);
#if defined(CONFIG_ENABLE_DEBUG)
    {
        trace_ProtocolSocket_Addref(cs.file, (MI_Uint32)cs.line, self, (unsigned int)ref);
    }
#endif /* defined(CONFIG_ENABLE_DEBUG) */
}

#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */

#define ProtocolSocket_Addref(self) \
    _ProtocolSocket_Addref(self, CALLSITE)

MI_INLINE
void _ProtocolSocket_Delete(
    _In_ ProtocolSocket* self)
{
    ProtocolSocket_Release(self);
}

MI_Result _AddProtocolSocket_Handler(
    Selector* self,
    ProtocolSocket* protocolSocket)
{
    MI_Result r = MI_RESULT_OK;
    ProtocolSocket_Addref(protocolSocket);
    r = Selector_AddHandler(self, &(protocolSocket->base));
    return r;
}

static void _ProtocolSocket_Cleanup(ProtocolSocket* handler)
{
    if(handler->closeOtherScheduled)
        return;

    handler->closeOtherScheduled = MI_TRUE;

    _FreeAuthData(handler);

    /* free outstanding messages, batch */
    if (handler->receivingBatch)
        Batch_Destroy( handler->receivingBatch );

    handler->receivingBatch = 0;

    if (handler->message)
    {
        MI_Boolean internalMessage = Message_IsInternalMessage( handler->message );

        Message_Release(handler->message);
        handler->message = 0;

        //ACK up if the message just sent was posted from up
        if (!internalMessage)
            Strand_ScheduleAck( &handler->strand );
    }

    Sock_Close(handler->base.sock);

    /* Mark handler as closed */
    handler->base.sock = INVALID_SOCK;

    Strand_ScheduleClose( &handler->strand );
}

/*
**==============================================================================
*/

void _ProtocolSocket_CheckAbort( _In_ ProtocolSocket* self )
{
    if( !self->strand.info.thisClosedOther )
    {
        MI_Uint64 currentTimeUsec = 0;
        ProtocolBase* protocolBase = (ProtocolBase*)self->base.data;

        trace_ProtocolSocket_TimeoutTrigger( self );
        // provoke a timeout to close/delete the socket
        PAL_Time(&currentTimeUsec);
        self->base.fireTimeoutAt = currentTimeUsec;
        Selector_Wakeup( protocolBase->selector, MI_TRUE );
    }
}

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26001) // bogus "we know the strand points to the middle of the ProtocolSocket struct" and Linux sal parser doesnt recognize something like _Readable_elements_(_Inexpressible_(ProtocolSocket))
#endif /* _PREFAST_ */

void _ProtocolSocket_Post( _In_ Strand* self_, _In_ Message* msg)
{
    ProtocolSocket* self = FromOffset( ProtocolSocket, strand, self_ );
    ProtocolBase* protocolBase = (ProtocolBase*)self->base.data;

    DEBUG_ASSERT( NULL != self_ );

    DEBUG_ASSERT(self->message == NULL);
    self->base.mask &= ~SELECTOR_READ;

    trace_ProtocolSocket_PostingOnInteraction( &self->strand.info.interaction, self->strand.info.interaction.other );

    /* Bump ref count during duration of transfer */
    ProtocolSocket_Addref(self);

    if( self->closeOtherScheduled ||
        ( MI_RESULT_OK != Selector_CallInIOThread(
        protocolBase->selector, _SendIN_IO_thread_wrapper, self, msg ) ))
    {
        trace_ProtocolSocket_PostFailed( &self->strand.info.interaction, self->strand.info.interaction.other );
        Strand_ScheduleAck( &self->strand );
    }
}

void _ProtocolSocket_PostControl( _In_ Strand* self, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // not used yet
}

void _ProtocolSocket_Cancel( _In_ Strand* self_)
{
    ProtocolSocket* self = FromOffset( ProtocolSocket, strand, self_ );

    trace_ProtocolSocket_CancelReceived(
        self->strand.info.thisClosedOther,
        &self->strand.info.interaction,
        self->strand.info.interaction.other );

    // Abort the socket
    _ProtocolSocket_CheckAbort( self );
}

void _ProtocolSocket_Ack( _In_ Strand* self_)
{
    ProtocolSocket* self = FromOffset( ProtocolSocket, strand, self_ );
    ProtocolBase* protocolBase = (ProtocolBase*)self->base.data;
    DEBUG_ASSERT( NULL != self_ );

    trace_ProtocolSocket_Ack( &self_->info.interaction, self_->info.interaction.other );
    if (!(self->base.mask & SELECTOR_WRITE))
        self->base.mask |= SELECTOR_READ;
    Selector_Wakeup( protocolBase->selector, MI_FALSE );
}

void _ProtocolSocket_Close( _In_ Strand* self_)
{
    ProtocolSocket* self = FromOffset( ProtocolSocket, strand, self_ );

    trace_ProtocolSocket_Close(
        self->strand.info.thisClosedOther,
        &self->strand.info.interaction,
        self->strand.info.interaction.other );

    if( !self->strand.canceled )
    {
        _ProtocolSocket_CheckAbort( self );
    }
}

void _ProtocolSocket_Finish( _In_ Strand* self_)
{
    ProtocolSocket* self = FromOffset( ProtocolSocket, strand, self_ );
    ProtocolBase* protocolBase = (ProtocolBase*)self->base.data;
    DEBUG_ASSERT( NULL != self_ );

    trace_ProtocolSocket_Finish( self );

    if( protocolBase->type == PRT_TYPE_LISTENER )
    {
        _ProtocolSocket_Delete( self );
    }
    else
    {
        _ProtocolSocketAndBase_Delete( (ProtocolSocketAndBase*)self );
    }
}

// PROTOCOLSOCKET_STRANDAUX_POSTMSG
void _ProtocolSocket_Aux_PostMsg( _In_ Strand* self_)
{
    ProtocolSocket* self = FromOffset( ProtocolSocket, strand, self_ );
    ProtocolBase* protocolBase = (ProtocolBase*)self->base.data;
    Message * msg = self->strand.info.otherMsg;

    self->strand.info.otherMsg = NULL;

    if( !self->strand.info.thisClosedOther )
    {
        // process the case where the interaction for the connection has not been opened yet
        if( NULL != protocolBase->callback && NULL == self->strand.info.interaction.other )
        {
            Strand_Open( self_, protocolBase->callback, protocolBase->callbackData, NULL, MI_FALSE );
        }

        if( Message_IsRequest(msg) )
        {
            RequestMsg* request = (RequestMsg*)msg;
            AuthInfo_Copy( &request->authInfo, &self->authInfo );
        }

        DEBUG_ASSERT( NULL != self->strand.info.interaction.other );

        // Leave the strand for the case where this is a new request on server
        // and the provider is in-proc and takes over the thread
        Strand_PostAndLeaveStrand( &self->strand, msg );
    }

    // now we can remove the reference added before Strand_ScheduleAux( PROTOCOLSOCKET_STRANDAUX_POSTMSG )
    Message_Release( msg );
}

// PROTOCOLSOCKET_STRANDAUX_READYTOFINISH
void _ProtocolSocket_Aux_ReadyToFinish( _In_ Strand* self_)
{
    Strand_ResetDelayFinish(self_);
}

// PROTOCOLSOCKET_STRANDAUX_CONNECTEVENT
void _ProtocolSocket_Aux_ConnectEvent( _In_ Strand* self_)
{
    ProtocolSocket* self = FromOffset( ProtocolSocket, strand, self_ );
    ProtocolEventConnect* msg = ProtocolEventConnect_New(self->isConnected);

    DEBUG_ASSERT( NULL != self->strand.info.interaction.other );

    Strand_PostControl( &self->strand, &msg->base );
    Message_Release(&msg->base);
}

#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */

/*
    Object that implements the binary protocol endpoint on a TCP Socket
    There are 3 different types of objects that can be created:
    - ProtocolSocketServer each client connection ON server side
    - ProtocolConnector client connection TO the server
    - ProtocolFromSocket either side of the out-of-proc (agent) connection

    Behaviour:
    - Post tries to schedule the operation on the IO thread (thru selector)
       if that fails it sends the Ack immediately
    - Post control is not implemented
    - both Cancel and Close check if the connection has already been closed and
       if not it triggers a timeout that will close it
    - Ack reactivates keep reading by setting SELECTOR_READ (if no
       write is in progress)
    - Shutdown:
       The ProtocolSocketServer objects are shutdown/deleted thru the normal
       Strand logic (once the interaction is closed).
       However the other Protocol objects are not deleted that way and instead
       they are deleted manually by the object that uses them once it has
       finished its Protocol_Run execution. That works by setting Strand_SetDelayFinish
       (which sets the delayFinish flag on the strand)  on object creation,
       and then calling ProtocolSocketAndBase_ReadyToFinish which schedules
       the auxiliary function PROTOCOLSOCKET_STRANDAUX_CONNECTEVENT
       which in turn disables that flag allowing the object to be deleted.

    Unique features and special Behavour:
    - When a complete message has been read instead of scheduling a post
       the auxiliary function PROTOCOLSOCKET_STRANDAUX_POSTMSG is
       scheduled instead. That function takes care of opening the interaction
       (if not opened already) and posting using Strand_PostAndLeaveStrand
       (which avoids holding the strand in case the thread is going to be hijacked
       by the provider in the processing of that post).
    - On the ProtocolConnector type once the connection succeeds or fails
       a PostControl notifies of that event by scheduling the auxiliary function
       PROTOCOLSOCKET_STRANDAUX_CONNECTEVENT
*/
static StrandFT _ProtocolSocket_FT = {
    _ProtocolSocket_Post,
    _ProtocolSocket_PostControl,
    _ProtocolSocket_Ack,
    _ProtocolSocket_Cancel,
    _ProtocolSocket_Close,
    _ProtocolSocket_Finish,
    NULL,
    _ProtocolSocket_Aux_PostMsg,
    _ProtocolSocket_Aux_ReadyToFinish,
    _ProtocolSocket_Aux_ConnectEvent,
    NULL,
    NULL };

/**************** Auth-support **********************************************************/
/* remove auth file and free auth data */
static void _FreeAuthData(
    ProtocolSocket* h)
{
    if (h->authData)
    {
#if defined(CONFIG_POSIX)
        unlink(h->authData->path);
#endif
        PAL_Free(h->authData);
        h->authData = 0;
    }
}

/* Creates and sends authentication request message */
static MI_Boolean _SendAuthRequest(
    ProtocolSocket* h,
    const char* user,
    const char* password,
    const char* fileContent)
{
    BinProtocolNotification* req;
    MI_Boolean retVal = MI_TRUE;

    req = BinProtocolNotification_New(BinNotificationConnectRequest);

    if (!req)
        return MI_FALSE;

    if (user && *user)
    {
        req->user = Batch_Strdup(req->base.batch, user);
        if (!req->user)
        {
            BinProtocolNotification_Release(req);
            return MI_FALSE;
        }
    }

    if (password && *password)
    {
        req->password = Batch_Strdup(req->base.batch, password);
        if (!req->password)
        {
            BinProtocolNotification_Release(req);
            return MI_FALSE;
        }
    }

    req->uid = geteuid();
    req->gid = getegid();

    if (fileContent)
    {
        memcpy(req->authData, fileContent, sizeof(req->authData));
    }

    /* send message */
    {
        DEBUG_ASSERT(h->message == NULL);
        h->message = (Message*) req;

        Message_AddRef(&req->base);

        _PrepareMessageForSending(h);
        retVal = _RequestCallbackWrite(h);
    }

    BinProtocolNotification_Release(req);

    return retVal;
}

static MI_Boolean _SendAuthResponse(
    ProtocolSocket* h,
    MI_Result result,
    const char* path)
{
    BinProtocolNotification* req;
    MI_Boolean retVal = MI_TRUE;

    req = BinProtocolNotification_New(BinNotificationConnectResponse);

    if (!req)
        return MI_FALSE;

    req->result = result;
    if (path && *path)
    {
        req->authFile = Batch_Strdup(req->base.batch, path);
        if (!req->authFile)
        {
            BinProtocolNotification_Release(req);
            return MI_FALSE;
        }
    }

    /* send message */
    {
        DEBUG_ASSERT(h->message == NULL);
        h->message = (Message*)req;
        Message_AddRef(&req->base);

        _PrepareMessageForSending(h);
        retVal = _RequestCallbackWrite(h);
    }

    BinProtocolNotification_Release(req);

    return retVal;
}

/*
    Processes auht message while waiting second connect request
    with content of the file.
    Updates auth states correspondingly.
    Parameters:
    handler - socket handler
    binMsg - BinProtocolNotification message with connect request/response

    Return:
    "TRUE" if connection should stay open; "FALSE" if auth failed
        and conneciton should be closed immediately
*/
static MI_Boolean _ProcessAuthMessageWaitingConnectRequestFileData(
    ProtocolSocket* handler,
    BinProtocolNotification* binMsg)
{
    /* un-expected message */
    if (BinNotificationConnectRequest != binMsg->type)
        return MI_FALSE;

    /* Check internal state */
    if (!handler->authData)
        return MI_FALSE;

    if (0 == memcmp(binMsg->authData, handler->authData->authRandom, AUTH_RANDOM_DATA_SIZE))
    {
        if (!_SendAuthResponse(handler, MI_RESULT_OK, NULL))
            return MI_FALSE;

        /* Auth ok */
        handler->authState = PRT_AUTH_OK;
        _FreeAuthData(handler);

        /* Get gid from user name */
        if (0 != GetUserGidByUid(handler->authInfo.uid, &handler->authInfo.gid))
        {
            trace_CannotGetUserGidForUid((int)handler->authInfo.uid);
            return MI_FALSE;
        }

        return MI_TRUE;
    }

    trace_AuthFailed_RandomDataMismatch();

    /* Auth failed */
    _SendAuthResponse(handler, MI_RESULT_ACCESS_DENIED, NULL);
    handler->authState = PRT_AUTH_FAILED;
    return MI_FALSE;
}

/*
    Processes auht message while waiting connect request
    Updates auth states correspondingly.
    Parameters:
    handler - socket handler
    binMsg - BinProtocolNotification message with connect request/response

    Return:
    "TRUE" if connection should stay open; "FALSE" if auth failed
        and connection should be closed immediately
*/
static MI_Boolean _ProcessAuthMessageWaitingConnectRequest(
    ProtocolSocket* handler,
    BinProtocolNotification* binMsg)
{
    /* un-expected message */
    if (BinNotificationConnectRequest != binMsg->type)
        return MI_FALSE;

    /* Use explicit credentials if provided */
    if (binMsg->user)
    {
        /* use empty password if not set */
        if (!binMsg->password)
            binMsg->password = "";

        if (0 == AuthenticateUser(binMsg->user, binMsg->password) &&
            0 == LookupUser(binMsg->user, &handler->authInfo.uid, &handler->authInfo.gid))
        {
            if (!_SendAuthResponse(handler, MI_RESULT_OK, NULL))
                return MI_FALSE;

            /* Auth ok */
            handler->authState = PRT_AUTH_OK;
            _FreeAuthData(handler);
            return MI_TRUE;
        }

        trace_AuthFailed_ForUser(scs(binMsg->user));

        /* Auth failed */
        _SendAuthResponse(handler, MI_RESULT_ACCESS_DENIED, NULL);
        handler->authState = PRT_AUTH_FAILED;
        return MI_FALSE;
    }

    /* If system supports connection-based auth, use it for
        implicit auth */
    if (0 == GetUIDByConnection((int)handler->base.sock, &handler->authInfo.uid, &handler->authInfo.gid))
    {
        if (!_SendAuthResponse(handler, MI_RESULT_OK, NULL))
            return MI_FALSE;

        /* Auth ok */
        handler->authState = PRT_AUTH_OK;
        return MI_TRUE;
    }
#if defined(CONFIG_OS_WINDOWS)
    {
        if (!_SendAuthResponse(handler, MI_RESULT_OK, NULL))
            return MI_FALSE;

        /* Ignore Auth by setting it to OK */
        handler->authInfo.uid = -1;
        handler->authInfo.gid = -1;
        handler->authState = PRT_AUTH_OK;
        return MI_TRUE;
    }
#else

    /* If valid uid provided, try implicit credentials (file-based)
        gid will be taken from user name */
    {
        handler->authData = (Protocol_AuthData*)PAL_Calloc(1, sizeof(Protocol_AuthData));

        if (!handler->authData)
        {
            /* Auth failed */
            _SendAuthResponse(handler, MI_RESULT_ACCESS_DENIED, NULL);
            handler->authState = PRT_AUTH_FAILED;
            return MI_FALSE;
        }

        if (0 != CreateAuthFile(binMsg->uid, handler->authData->authRandom, AUTH_RANDOM_DATA_SIZE, handler->authData->path))
        {
            trace_CannotCreateFileForUser((int)binMsg->uid);

            /* Auth failed */
            _SendAuthResponse(handler, MI_RESULT_ACCESS_DENIED, NULL);
            handler->authState = PRT_AUTH_FAILED;
            return MI_FALSE;
        }

        /* send file name to the client */
        if (!_SendAuthResponse(handler, MI_RESULT_IN_PROGRESS, handler->authData->path))
            return MI_FALSE;

        /* Auth posponed */
        handler->authState = PRT_AUTH_WAIT_CONNECTION_REQUEST_WITH_FILE_DATA;

        /* Remember uid we used to create file */
        handler->authInfo.uid = binMsg->uid;
        handler->authInfo.gid = -1;

        return MI_TRUE;

    }
#endif
}

/*
    Processes auht message (either connect request or connect-response)
    Updates auth states correspondingly.
    Parameters:
    handler - socket handler
    msg - BinProtocolNotification message with connect request/response

    Return:
    "TRUE" if connection should stay open; "FALSE" if auth failed
        and conneciton should be closed immediately
*/
static MI_Boolean _ProcessAuthMessage(
    ProtocolSocket* handler,
    Message *msg)
{
    ProtocolBase* protocolBase = (ProtocolBase*)handler->base.data;
    BinProtocolNotification* binMsg;

    if (msg->tag != BinProtocolNotificationTag)
        return MI_FALSE;

    binMsg = (BinProtocolNotification*) msg;

    /* server waiting client's first request? */
    if (PRT_AUTH_WAIT_CONNECTION_REQUEST == handler->authState)
    {
        return _ProcessAuthMessageWaitingConnectRequest(handler, binMsg);
    }

    /* server waiting for client's file's content request? */
    if (PRT_AUTH_WAIT_CONNECTION_REQUEST_WITH_FILE_DATA == handler->authState)
    {
        return _ProcessAuthMessageWaitingConnectRequestFileData(handler, binMsg);
    }

    /* client waiting for server's response? */
    if (PRT_AUTH_WAIT_CONNECTION_RESPONSE == handler->authState)
    {
        /* un-expected message */
        if (BinNotificationConnectResponse != binMsg->type)
            return MI_FALSE;

        if (binMsg->result == MI_RESULT_OK)
        {
            handler->authState = PRT_AUTH_OK;

            if( Atomic_Swap(&handler->connectEventSent, 1) == 0 )
            {
                DEBUG_ASSERT( PRT_TYPE_CONNECTOR == protocolBase->type );
                handler->isConnected = MI_TRUE;
                Strand_ScheduleAux( &handler->strand, PROTOCOLSOCKET_STRANDAUX_CONNECTEVENT );
            }

            return MI_TRUE;
        }
        else if (binMsg->result == MI_RESULT_IN_PROGRESS && binMsg->authFile)
        {
            /* send back file's content */
            char buf[AUTH_RANDOM_DATA_SIZE];
            FILE* is = File_Open(binMsg->authFile, "r");

            if (!is)
            {
                trace_CannotOpenAuthFile(scs(binMsg->authFile));
                return MI_FALSE;
            }

            /* Read auth data from the file. */
            if (sizeof(buf) != fread(buf, 1, sizeof(buf), is))
            {
                trace_CannotReadAuthFile(scs(binMsg->authFile));
                File_Close(is);
                return MI_FALSE;
            }

            File_Close(is);
            return _SendAuthRequest(handler, 0, 0, buf);
        }
        else
        {
            // PROTOCOLEVENT_DISCONNECT
            if( PRT_TYPE_CONNECTOR == protocolBase->type )
            {
                if( Atomic_Swap(&handler->connectEventSent, 1) == 0 )
                {
                    DEBUG_ASSERT( !handler->isConnected );
                    Strand_ScheduleAux( &handler->strand, PROTOCOLSOCKET_STRANDAUX_CONNECTEVENT );
                }
            }
        }

        return MI_FALSE;
    }

    /* unknown state? */
    return MI_FALSE;
}

static void _PrepareMessageForSending(
    ProtocolSocket *handler)
{
    DEBUG_ASSERT(handler->message != NULL);

    /* reset sending attributes */
    handler->sendingPageIndex = 0;
    handler->sentCurrentBlockBytes = 0;

    memset(&handler->send_buffer,0,sizeof(handler->send_buffer));
    handler->send_buffer.base.magic = PROTOCOL_MAGIC;
    handler->send_buffer.base.version = PROTOCOL_VERSION;
    handler->send_buffer.base.pageCount = (MI_Uint32)Batch_GetPageCount(handler->message->batch);
    handler->send_buffer.base.originalMessagePointer = handler->message;

    /* ATTN! */
    DEBUG_ASSERT (handler->send_buffer.base.pageCount <= PROTOCOL_HEADER_MAX_PAGES);

    /* get page info */

    Batch_GetPageInfo(
        handler->message->batch, handler->send_buffer.batchInfo);

    /* mark handler as 'want-write' */
    handler->base.mask |= SELECTOR_WRITE;

}

static MI_Boolean _RequestCallbackWrite(
    ProtocolSocket* handler)
{
    /* try to write to socket as much as possible */
    size_t sent;
    MI_Result r;
    size_t retries = 0;

    for (;;)
    {
        /* buffers to write */
        IOVec buffers[32];
        size_t counter;

        if ( !handler->message )
        { /* nothing to send */
            handler->base.mask &= ~SELECTOR_WRITE;
            if (!handler->strand.info.thisAckPending)
                handler->base.mask |= SELECTOR_READ;
            trace_SocketSendCompleted(handler);
            return MI_TRUE;
        }

        for ( counter = 0; counter < MI_COUNT(buffers); counter++ )
        {
            const char* buf;
            MI_Uint32 index = (MI_Uint32)(handler->sendingPageIndex + counter);

            buf = (index == 0) ?
                &handler->send_buffer :
                handler->send_buffer.batchInfo[index - 1].pagePointer;

            if (!counter)
                buf += handler->sentCurrentBlockBytes;

            buffers[counter].ptr = (void*)buf;

            buffers[counter].len = (index == 0) ? (sizeof(HeaderBase) + sizeof(Header_BatchInfoItem) * handler->send_buffer.base.pageCount)
                : handler->send_buffer.batchInfo[index - 1].pageSize;

            if (!counter)
                buffers[counter].len -= handler->sentCurrentBlockBytes;

            if (index == handler->send_buffer.base.pageCount)
            {
                counter++;
                break;
            }
        }

        sent = 0;

        do
        {
            r = Sock_WriteV(handler->base.sock, buffers, counter, &sent);

            LOGD2((ZT("_RequestCallbackWrite - Sent %lu bytes with result %d (%s)"), sent, (int)r, mistrerror(r)));

            if ( r == MI_RESULT_OK && 0 == sent )
            {
                trace_Socket_ConnectionClosed(handler);
                return MI_FALSE; /* connection closed */
            }

            if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
            {
                trace_Socket_Sending_Error(handler, r);
                if( r == MI_RESULT_NOT_FOUND && retries < 5 )
                {
                    ++retries;
                    Sleep_Milliseconds(100);
                    continue;
                }
                return MI_FALSE;
            }
        }
        while (r == MI_RESULT_NOT_FOUND);

        if (!sent)
        {
            /* trace_QueueingSocket(handler); */
            return MI_TRUE;
        }

        /* update index */
        for ( counter = 0; counter < MI_COUNT(buffers); counter++ )
        {
            if (!sent)
                break;

            if (sent >= buffers[counter].len)
            {
                sent -= buffers[counter].len;
                handler->sendingPageIndex++;
                handler->sentCurrentBlockBytes = 0;
                continue;
            }

            handler->sentCurrentBlockBytes += sent;
            break;
        }

        if (handler->sendingPageIndex - 1 == (int)handler->send_buffer.base.pageCount)
        {
            MI_Boolean internalMessage = Message_IsInternalMessage( handler->message );

            LOGD2((ZT("_RequestCallbackWrite - Message sent. tag %d (%T)"), handler->message->tag, MessageName(handler->message->tag)));

            //for all protocol internal messages, i.e messages that were not posted from up
            /* next message */
            Message_Release(handler->message);
            handler->message = 0;

            //ACK up if the message just sent was posted from up
            if (!internalMessage)
                Strand_ScheduleAck( &handler->strand );
        }
    }
}

/*
    Processes incoming message, including:
        - decoding message from batch
        - invoking callback to process message

    Parameters:
        handler - pointer to received data
    Returns:
        it returns result if 'callback' with the followinf meaning:
        MI_TRUE - to continue normal operations
        MI_FALSE - to close connection
*/
static Protocol_CallbackResult _ProcessReceivedMessage(
    ProtocolSocket* handler)
{
    MI_Result r;
    Message* msg = 0;
    ProtocolBase* protocolBase = (ProtocolBase*)handler->base.data;
    Protocol_CallbackResult ret = PRT_RETURN_FALSE;

    /* create a message from a batch */
    r = MessageFromBatch(
        handler->receivingBatch,
        handler->recv_buffer.base.originalMessagePointer,
        handler->recv_buffer.batchInfo,
        handler->recv_buffer.base.pageCount,
        protocolBase->skipInstanceUnpack,
        &msg);

    if(MI_RESULT_OK != r)
    {
        trace_RestoreMessage_Failed(r, tcs(Result_ToString(r)));
        Batch_Destroy( handler->receivingBatch );
    }

    /* clean up the state */
    handler->receivingBatch = 0;
    handler->receivingPageIndex = 0;
    memset(&handler->recv_buffer,0,sizeof(handler->recv_buffer));

    if (MI_RESULT_OK == r)
    {
        trace_Socket_ReceivedMessage(
            msg,
            msg->tag,
            MessageName(msg->tag),
            msg->operationId );

        if (PRT_AUTH_OK != handler->authState)
        {
            if( _ProcessAuthMessage(handler, msg) )
                ret = PRT_CONTINUE;
        }
        else
        {
            //disable receiving anything else until this message is ack'ed
            handler->base.mask &= ~SELECTOR_READ;
            // We cannot use Strand_SchedulePost becase we have to do
            // special treatment here (leave the strand in post)
            // We can use otherMsg to store this though
            Message_AddRef( msg );  // since the actual message use can be delayed
            handler->strand.info.otherMsg = msg;
            Strand_ScheduleAux( &handler->strand, PROTOCOLSOCKET_STRANDAUX_POSTMSG );
            ret = PRT_RETURN_TRUE;
        }

        Message_Release(msg);
    }

    return ret;
}

static Protocol_CallbackResult _ReadHeader(
    ProtocolSocket* handler)
{
    char* buf;
    size_t buf_size, received;
    MI_Result r;
    MI_Uint32 index;

    /* are we done with header? */
    if (0 != handler->receivingPageIndex)
        return PRT_CONTINUE;

    for ( ; ; )
    {
        buf = (char*)&handler->recv_buffer;
        buf_size = (sizeof(HeaderBase) + sizeof(Header_BatchInfoItem) * handler->recv_buffer.base.pageCount);
        received = 0;

        r = Sock_Read(handler->base.sock, buf + handler->receivedCurrentBlockBytes, buf_size - handler->receivedCurrentBlockBytes, &received);

        LOGD2((ZT("_ReadHeader - Read %lu bytes with result %d (%s)"), received, (int)r, mistrerror(r)));

        if ( r == MI_RESULT_OK && 0 == received )
        {
            trace_Socket_ReadHeader_ConnectionClosed(handler);
            return PRT_RETURN_FALSE; /* connection closed */
        }

        if ( r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK )
        {
            trace_Socket_ReadingHeader_Error(handler, r);
            return PRT_RETURN_FALSE;
        }

        if (!received)
            return PRT_RETURN_TRUE;

        handler->receivedCurrentBlockBytes += received;

        if (handler->receivedCurrentBlockBytes == buf_size)
        {
            /* got header - validate/allocate as required */
            if (handler->recv_buffer.base.pageCount > PROTOCOL_HEADER_MAX_PAGES)
            {
                trace_Socket_ReadingHeader_ErrorPageCount(handler);
                return PRT_RETURN_FALSE;
            }

            if (handler->recv_buffer.base.magic != PROTOCOL_MAGIC)
            {
                trace_Socket_ReadingHeader_ErrorMagic(handler);
                return PRT_RETURN_FALSE;
            }

            for (index =0; index < handler->recv_buffer.base.pageCount; index++)
            {
                if (handler->recv_buffer.batchInfo[index].pageSize > MAX_ENVELOPE_SIZE)
                {
                    trace_Socket_ReadingHeader_ErrorBatchSize(handler);
                    return PRT_RETURN_FALSE;
                }
            }

            /* check if page info is also retrieved */
            if (buf_size != ((sizeof(HeaderBase) + sizeof(Header_BatchInfoItem) * handler->recv_buffer.base.pageCount)))
                continue;

            /* create a batch */
            if (!Batch_CreateBatchByPageInfo(
                &handler->receivingBatch,
                handler->recv_buffer.batchInfo,
                handler->recv_buffer.base.pageCount))
            {
                trace_Socket_ReadingHeader_ErrorCreatingBatch(handler);
                return PRT_RETURN_FALSE;
            }

            /* skip to next page */
            handler->receivingPageIndex++;
            handler->receivedCurrentBlockBytes = 0;

            if ( (handler->receivingPageIndex - 1) == (int)handler->recv_buffer.base.pageCount )
            {   /* received the whole message - process it */
                return _ProcessReceivedMessage(handler);
            }
            break;
        } /* if we read the whole buffer */
    } /* for(;;) */
    return PRT_CONTINUE;
}

static Protocol_CallbackResult _ReadAllPages(
    ProtocolSocket* handler)
{
    size_t received;
    MI_Result r;
    /* buffers to write */
    IOVec   buffers[32];
    size_t counter;

    /* are we done with header? - if not, return 'continue' */
    if (0 == handler->receivingPageIndex)
        return PRT_CONTINUE;


    for ( counter = 0; counter < MI_COUNT(buffers); counter++ )
    {
        const char* buf;
        MI_Uint32 index = (MI_Uint32)(handler->receivingPageIndex + counter);

        buf = Batch_GetPageByIndex(handler->receivingBatch, index - 1);

        if (!counter)
            buf += handler->receivedCurrentBlockBytes;

        buffers[counter].ptr = (void*)buf;
        buffers[counter].len = handler->recv_buffer.batchInfo[index - 1].pageSize;

        if (!counter)
            buffers[counter].len -= handler->receivedCurrentBlockBytes;

        if (index == handler->recv_buffer.base.pageCount)
        {
            counter++;
            break;
        }
    }

    received = 0;

    r = Sock_ReadV(handler->base.sock, buffers, counter, &received);

    LOGD2((ZT("_ReadAllPages - Read %lu bytes with result %d (%s)"), received, (int)r, mistrerror(r)));

    if ( r == MI_RESULT_OK && 0 == received )
    {
        trace_Socket_Read_ConnectionClosed(handler);
        return PRT_RETURN_FALSE; /* connection closed */
    }

    if ( r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK )
    {
        trace_Socket_Read_Error(handler, r);
        return PRT_RETURN_FALSE;
    }

    if (!received)
        return PRT_RETURN_TRUE;

    /* update index */
    for ( counter = 0; counter < MI_COUNT(buffers); counter++ )
    {
        if (!received)
            break;

        if (received >= buffers[counter].len)
        {
            received -= buffers[counter].len;
            handler->receivingPageIndex++;
            handler->receivedCurrentBlockBytes = 0;
            continue;
        }

        handler->receivedCurrentBlockBytes += received;
        break;
    }

    if ( (handler->receivingPageIndex - 1) == (int)handler->recv_buffer.base.pageCount )
    {   /* received the whole message - process it */
        return _ProcessReceivedMessage(handler);
    }

    return PRT_CONTINUE;
}

static MI_Boolean _RequestCallbackRead(
    ProtocolSocket* handler)
{
    int fullMessagesREceived = 0;

    /* we have to keep repeating read until 'WOULD_BLOCK is returned;
        windows does not reset event until read buffer is empty */
    for (;fullMessagesREceived < 3;)
    {
        switch (_ReadHeader(handler))
        {
        case PRT_CONTINUE: break;
        case PRT_RETURN_TRUE: return MI_TRUE;
        case PRT_RETURN_FALSE: return MI_FALSE;
        }

        switch (_ReadAllPages(handler))
        {
        case PRT_CONTINUE: break;
        case PRT_RETURN_TRUE: return MI_TRUE;
        case PRT_RETURN_FALSE: return MI_FALSE;
        }
    } /* for(;;)*/
    return MI_TRUE;
}

static MI_Boolean _RequestCallback(
    Selector* sel,
    Handler* handlerIn,
    MI_Uint32 mask,
    MI_Uint64 currentTimeUsec)
{
    ProtocolSocket* handler = (ProtocolSocket*)handlerIn;
    ProtocolBase* protocolBase = (ProtocolBase*)handler->base.data;

    MI_UNUSED(sel);
    MI_UNUSED(currentTimeUsec);

    if (mask & SELECTOR_READ)
    {
        if (!_RequestCallbackRead(handler))
        {
            trace_RequestCallbackRead_Failed( handler );
            if( !handler->isConnected && PRT_TYPE_CONNECTOR == protocolBase->type )
            {
                Strand_ScheduleAux( &handler->strand, PROTOCOLSOCKET_STRANDAUX_CONNECTEVENT );
            }
            goto closeConnection;
        }
        else
        {
            handler->isConnected = MI_TRUE;
            if( PRT_TYPE_CONNECTOR == protocolBase->type && PRT_AUTH_OK == handler->authState )
            {
                if( Atomic_Swap(&handler->connectEventSent, 1) == 0 )
                {
                    trace_RequestCallback_Connect_OnFirstRead(handler);
                    Strand_ScheduleAux( &handler->strand, PROTOCOLSOCKET_STRANDAUX_CONNECTEVENT );
                }
            }
        }
    }

    if (mask & SELECTOR_WRITE)
    {
        if (!_RequestCallbackWrite(handler))
        {
            trace_RequestCallbackRead_Failed( handler );
            goto closeConnection;
        }
        else
        {
            if( !handler->isConnected )
            {
                handler->isConnected = MI_TRUE;
                if( PRT_TYPE_CONNECTOR == protocolBase->type && PRT_AUTH_OK == handler->authState )
                {
                    if( Atomic_Swap(&handler->connectEventSent, 1) == 0 )
                    {
                        trace_RequestCallback_Connect_OnFirstWrite( handler );
                        Strand_ScheduleAux( &handler->strand, PROTOCOLSOCKET_STRANDAUX_CONNECTEVENT );
                    }
                }
            }
        }
    }

    /* Close connection by timeout or error */
    if( (mask & SELECTOR_TIMEOUT) || (mask & SELECTOR_EXCEPTION) )
    {
        trace_RequestCallback_Connect_ClosingAfterMask( handler, mask );
        goto closeConnection;
    }

    if ((mask & SELECTOR_REMOVE) != 0 ||
        (mask & SELECTOR_DESTROY) != 0)
    {
        trace_RequestCallback_Connect_RemovingHandler( handler, mask, handler->base.mask );

        _ProtocolSocket_Cleanup(handler);

        ProtocolSocket_Release(handler);
    }

    return MI_TRUE;

closeConnection:

    //release message and post ack if required
    if (handler->message)
    {
        MI_Boolean internalMessage = Message_IsInternalMessage( handler->message );

        Message_Release(handler->message);
        handler->message = 0;

        //ACK up if the message just sent was posted from up
        if (!internalMessage)
            Strand_ScheduleAck( &handler->strand );
    }

    LOGD2((ZT("_RequestCallback - closed client connection")));
    trace_Socket_ClosingConnection( handler, mask );

    return MI_FALSE;
}

static MI_Boolean _ListenerCallback(
    Selector* sel,
    Handler* handler,
    MI_Uint32 mask,
    MI_Uint64 currentTimeUsec)
{
    ProtocolBase* self = (ProtocolBase*)handler->data;
    MI_Result r;
    Sock s;
    Addr addr;
    ProtocolSocket* h;

    MI_UNUSED(sel);
    MI_UNUSED(currentTimeUsec);

    if (mask & SELECTOR_READ)
    {
        /* Accept the incoming connection */
        r = Sock_Accept(handler->sock, &s, &addr);

        if (MI_RESULT_WOULD_BLOCK == r)
            return MI_TRUE;

        if (r != MI_RESULT_OK)
        {
            trace_SockAccept_Failed(Sock_GetLastError());
            return MI_TRUE;
        }

        r = Sock_SetBlocking(s, MI_FALSE);
        if (r != MI_RESULT_OK)
        {
            trace_SockSetBlocking_Failed();
            Sock_Close(s);
            return MI_TRUE;
        }

        /* Create handler */
        h =  _ProtocolSocket_Server_New(self,s);

        if (!h)
        {
            Sock_Close(s);
            return MI_TRUE;
        }

        Strand_Leave( &h->strand );

        /* Watch for read events on the incoming connection */
        r = _AddProtocolSocket_Handler(self->selector, h);

        if (r != MI_RESULT_OK)
        {
            ProtocolSocket_Release(h);
            trace_SelectorAddHandler_Failed();
            return MI_TRUE;
        }
    }

    if ((mask & SELECTOR_REMOVE) != 0 ||
        (mask & SELECTOR_DESTROY) != 0)
    {
        Sock_Close(handler->sock);
        PAL_Free(handler);
    }

    return MI_TRUE;
}

static MI_Result _CreateListener(
    Sock* s,
    const char* locator)
{
    const char* posColon;

    posColon = strchr(locator, ':');

    if (!posColon)
        return Sock_CreateLocalListener(s, locator);

    /* create listener for remote address like host:port or :port (ANYADDR) */
    {
        unsigned short port = (unsigned short)atol(posColon+1);
        char host[128];
        unsigned int len = (unsigned int)(posColon - locator);
        Addr addr;
        MI_Result r;

        if (len > 0)
        {
            if (len >= sizeof(host))
                return MI_RESULT_FAILED;

            memcpy(host, locator, len);
            host[len] = 0;

            // Initialize address.
            r = Addr_Init(&addr, host, port, MI_FALSE);
            if (r != MI_RESULT_OK)
                return MI_RESULT_FAILED;
        }
        else
        {
            Addr_InitAny(&addr, port);
        }

        return Sock_CreateListener(s, &addr);
    }
}

static MI_Result _CreateConnector(
    Sock* s,
    const char* locator)
{
    const char* posColon;

    /* This function expects a locator in the form "_host_:_port_", for HTTP */
    /* connections, or in the form of a file name, for local connections */
    /* using a socket. In the latter case, the file name is the nsme of the */
    /* socket special file. Thus, socket special files used with this code */
    /* may not contain a colon in their names. Servers with IPv6 addresses */
    /* must use symbolic names, because IPv6 addresses use a colon as a separator */

    posColon = strchr(locator, ':');
    if (!posColon)
        return Sock_CreateLocalConnector(s, locator);
    return Sock_CreateIPConnector(s, locator);
}

static MI_Result _ProtocolBase_Init(
    _In_        ProtocolBase*   self,
    _In_opt_    Selector*       selector, /*optional, maybe NULL*/
    _In_opt_    OpenCallback    callback,
    _In_opt_    void*           callbackData,
                Protocol_Type   protocolType)
{
    /* Check parameters */
    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

    if (selector)
    {   /* attach the exisiting selector */
        self->selector = selector;
        self->internal_selector_used = MI_FALSE;
    }
    else
    {   /* create a new selector */
        /* Initialize the network */
        Sock_Start();

        /* Initialize the selector */
        if (Selector_Init(&self->internal_selector) != MI_RESULT_OK)
        {
            return MI_RESULT_FAILED;
        }
        self->selector = &self->internal_selector;
        self->internal_selector_used = MI_TRUE;
    }

    /* Save the callback and callbackData */
    self->callback = callback;
    self->callbackData = callbackData;
    self->skipInstanceUnpack = MI_FALSE;
    self->type = protocolType;

    /* Set the magic number */
    self->magic = _MAGIC;

    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Public definitions:
**
**==============================================================================
*/

MI_Result ProtocolBase_New_Listener(
    _Out_       ProtocolBase** selfOut,
    _In_opt_    Selector* selector, /*optional, maybe NULL*/
    _In_        const char* locator,
    _In_        OpenCallback callback,
    _In_        void* callbackData)
{
    ProtocolBase* self;
    MI_Result r;
    Sock listener;

    /* Allocate structure */
    {
        self = (ProtocolBase*)PAL_Calloc(1, sizeof(ProtocolBase));

        if (!self)
            return MI_RESULT_FAILED;
    }

    r = _ProtocolBase_Init(self, selector, callback, callbackData, PRT_TYPE_LISTENER);

    if (MI_RESULT_OK != r)
    {
        PAL_Free(self);
        return r;
    }

    /* Set output parameter */
    *selfOut = self;

    /* Create listener socket */
    {
        r = _CreateListener(&listener, locator);

        if (r != MI_RESULT_OK)
        {
            ProtocolBase_Delete(self);
            return r;
        }

        r = Sock_SetBlocking(listener, MI_FALSE);

        if (r != MI_RESULT_OK)
        {
            Sock_Close(listener);
            ProtocolBase_Delete(self);
            return r;
        }
    }

    /* Watch for read events on the listener socket (client connections) */
    {
        Handler* h = (Handler*)PAL_Calloc(1, sizeof(Handler));

        if (!h)
        {
            Sock_Close(listener);
            ProtocolBase_Delete(self);
            return MI_RESULT_FAILED;
        }

        h->sock = listener;
        h->mask = SELECTOR_READ | SELECTOR_EXCEPTION;
        h->callback = _ListenerCallback;
        h->data = self;
        h->handlerName = MI_T("BINARY_SERVER_LISTENER");

        r = Selector_AddHandler(self->selector, h);

        if (r != MI_RESULT_OK)
        {
            Sock_Close(listener);
            PAL_Free(h);
            ProtocolBase_Delete(self);
            return r;
        }
    }

    return MI_RESULT_OK;
}

MI_Result _ProtocolSocket_New(
#if defined(STRAND_ENABLE_DEBUG)
    _In_        StrandDebugInfo         debug,
#endif
    _Out_       ProtocolSocket**        selfOut,
    _In_opt_    InteractionOpenParams*  params,         // Only used on connector types
                size_t                  structSize)     // if 0 then sizeof(ProtocolSocket) is assumed
{
    ProtocolSocket* self;

    DEBUG_ASSERT( 0 == structSize || structSize >= sizeof(ProtocolSocket) );

    *selfOut = NULL;

    if( 0 == structSize )
        structSize = sizeof(ProtocolSocket);

    /* Allocate structure */
    {
        self = (ProtocolSocket*)PAL_Calloc(1, structSize);

        if (!self)
            return MI_RESULT_FAILED;
    }

    Strand_Init( STRAND_PASSDEBUG(debug) &self->strand, &_ProtocolSocket_FT, STRAND_FLAG_ENTERSTRAND, params);
    self->refCount = 1; //ref associated with Strand. Released on Strand_Finish
    self->closeOtherScheduled = MI_FALSE;

    self->base.callback = _RequestCallback;

    /* Set output parameter */
    *selfOut = self;
    return MI_RESULT_OK;
}

ProtocolSocket* _ProtocolSocket_Server_New(
    _In_        ProtocolBase *          protocolBase,
    _In_        Sock                    sock )
{
    ProtocolSocket* self = NULL;

    if( MI_RESULT_OK == _ProtocolSocket_New( STRAND_DEBUG(ProtocolSocketServer) &self, NULL, 0) )
    {
        self->base.data = protocolBase;
        self->base.sock = sock;
        self->base.mask = SELECTOR_READ | SELECTOR_EXCEPTION;
        self->base.handlerName = MI_T("BINARY_SERVER_CONNECTION");

        /* waiting for connect-request */
        self->authState = PRT_AUTH_WAIT_CONNECTION_REQUEST;
    }

    return self;
}

MI_Result _ProtocolSocketAndBase_New(
#if defined(STRAND_ENABLE_DEBUG)
    _In_        StrandDebugInfo         debug,
#endif
    _Out_       ProtocolSocketAndBase** selfOut,
    _In_opt_    InteractionOpenParams*  params,             // Only used on connector types
    _In_opt_    Selector*               selector,           // optional, maybe NULL
    _In_opt_    OpenCallback            callback,           // only used on Agent
    _In_opt_    void*                   callbackData,       // used along with callback
                Protocol_Type           protocolType)
{
    ProtocolSocketAndBase* self;
    MI_Result r;

    DEBUG_ASSERT( ( NULL != params && callback == NULL ) || ( NULL == params && callback != NULL ) );

    *selfOut = NULL;

    r = _ProtocolSocket_New( STRAND_PASSDEBUG(debug) (ProtocolSocket**)&self, params, sizeof( ProtocolSocketAndBase ) );

    if( MI_RESULT_OK != r )
        return r;

    r = _ProtocolBase_Init(&self->internalProtocolBase, selector, callback, callbackData, protocolType);

    if (MI_RESULT_OK != r)
    {
        PAL_Free(self);
        return r;
    }

    self->protocolSocket.base.data = &self->internalProtocolBase;

    // ProtocolSocketAndBase objects need to delay wait until protocol run is done
    Strand_SetDelayFinish(&self->protocolSocket.strand);

    Strand_Leave( &self->protocolSocket.strand );

    // Set output parameter
    *selfOut = self;
    return MI_RESULT_OK;
}

MI_Result ProtocolSocketAndBase_New_Connector(
    _Out_       ProtocolSocketAndBase** selfOut,
    _In_opt_    Selector*               selector,       // optional, maybe NULL
    _In_        const char*             locator,
    _In_        InteractionOpenParams*  params,
    _In_        const char*             user,
    _In_        const char*             password )
{
    ProtocolSocketAndBase* self;
    MI_Result r;
    Sock connector;

    DEBUG_ASSERT( NULL != params && NULL != params->interaction && NULL == params->callbackData );

    *selfOut = 0;

    r = _ProtocolSocketAndBase_New( STRAND_DEBUG(ProtocolConnector) &self, params, selector, NULL, NULL, PRT_TYPE_CONNECTOR );

    if( r != MI_RESULT_OK )
        return r;

    /* Create connector socket */
    {
        // Connect to server.
        r = _CreateConnector(&connector, locator);
        if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
        {
            trace_SocketConnectorFailed(locator);
            _ProtocolSocketAndBase_Delete(self);
            return r;
        }
    }

    /* setting connector's structure */
    {
        ProtocolSocket* h = &self->protocolSocket;

        h->base.sock = connector;
        h->base.mask = SELECTOR_READ | SELECTOR_WRITE | SELECTOR_EXCEPTION;
        h->base.handlerName = MI_T("BINARY_CONNECTOR");
        h->authState = PRT_AUTH_WAIT_CONNECTION_RESPONSE;

        /* send connect request */
        if( !_SendAuthRequest(h, user, password, NULL) )
        {
            // this will call _RequestCallback which will schedule a CloseOther,
            // but that is not going delete the object (since it is not even truly opened),
            // so do it explicitely
            Sock_Close(connector);
            _ProtocolSocketAndBase_Delete(self);
            return MI_RESULT_FAILED;
        }
    }

    r = _AddProtocolSocket_Handler(self->internalProtocolBase.selector, &self->protocolSocket);
    if (r != MI_RESULT_OK)
    {
        Sock_Close(connector);
        _ProtocolSocketAndBase_Delete(self);
        return r;
    }

    /* Set output parameter */
    *selfOut = self;
    return MI_RESULT_OK;
}

/*
    Creates a new protocol object from connected stream socket
    (typically a pipe from server to agent).

    Parameters:
    self - [out] protocol object
    selector - [opt] selector to use for socket monitoring
    s - socket; if protocol created successfully, socket will be closed in Protocol_Delete.
        If operation failed, socket is not closed.
    skipInstanceUnpack - flag to skip instance un-packing; used
        to skip unpacking instances from agent
    callback - function that protocol calls to inform about new connection
    callbackData -

    Returns:
    'OK' if succefful, error otherwise
*/
MI_Result _ProtocolSocketAndBase_New_From_Socket(
    _Out_       ProtocolSocketAndBase** selfOut,
    _In_opt_    InteractionOpenParams*  params,         // Only used on connector type
    _In_opt_    Selector*               selector,       // optional, maybe NULL
    _In_        Sock                    sock,
                MI_Boolean              skipInstanceUnpack,
    _In_opt_    OpenCallback            callback,       // only used on Agent
    _In_opt_    void*                   callbackData)   // used along with callback
{
    ProtocolSocketAndBase* self;
    MI_Result r;

    *selfOut = 0;

    r = _ProtocolSocketAndBase_New( STRAND_DEBUG(ProtocolFromSocket) &self, params, selector, callback, callbackData, PRT_TYPE_FROM_SOCKET );

    if( r != MI_RESULT_OK )
        return r;

    self->internalProtocolBase.skipInstanceUnpack = skipInstanceUnpack;

    /* setup provided socket */
    {
        ProtocolSocket* h = &self->protocolSocket;

        h->base.sock = sock;
        h->base.mask = SELECTOR_READ  | SELECTOR_EXCEPTION;
        h->base.handlerName = MI_T("BINARY_FROM_SOCKET");

        if (skipInstanceUnpack)
        {
            /* skipInstanceUnpack indicates that call made from server
                and socket connected to the agent
                In that case we can use back=pressure feature and
                ignore socket operations under stress */
            //no more used - as flow control is implemented in protocol and wsman layers
            //h->base.mask |= SELECTOR_IGNORE_READ_OVERLOAD;
        }

        h->isConnected = MI_TRUE;
        /* skip authentication for established connections
            (only used in server/agent communication) */
        h->authState = PRT_AUTH_OK;

        r = _AddProtocolSocket_Handler(self->internalProtocolBase.selector, h);

        if (r != MI_RESULT_OK)
        {
            _ProtocolSocketAndBase_Delete(self);
            return r;
        }
    }

    /* Set output parameter */
    *selfOut = self;
    return MI_RESULT_OK;
}

MI_Result ProtocolSocketAndBase_New_AgentConnector(
    _Out_       ProtocolSocketAndBase** selfOut,
    _In_opt_    Selector*               selector,       // optional, maybe NULL
    _In_        Sock                    s,
    _In_        InteractionOpenParams*  params )
{
    return _ProtocolSocketAndBase_New_From_Socket( selfOut, params, selector, s, MI_TRUE, NULL, NULL );
}

MI_Result ProtocolSocketAndBase_New_Agent(
    _Out_       ProtocolSocketAndBase** selfOut,
    _In_opt_    Selector*               selector,       // optional, maybe NULL
    _In_        Sock                    s,
    _In_        OpenCallback            callback,
    _In_        void*                   callbackData)   // used along with callback
{
    return _ProtocolSocketAndBase_New_From_Socket( selfOut, NULL, selector, s, MI_FALSE, callback, callbackData );
}

MI_Result _ProtocolBase_Finish(
    ProtocolBase* self)
{
    /* Check parameters */
    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

    /* Check magic number */
    if (self->magic != _MAGIC)
        return MI_RESULT_INVALID_PARAMETER;

    if (self->internal_selector_used)
    {
        /* Release selector;
        Note: selector-destory closes all sockects in a list including connector and listener */
        Selector_Destroy(self->selector);

        /* Shutdown the network */
        Sock_Stop();
    }

    /* Clear magic number */
    self->magic = 0xDDDDDDDD;

    return MI_RESULT_OK;
}

MI_Result ProtocolBase_Delete(
    ProtocolBase* self)
{
    MI_Result r = _ProtocolBase_Finish( self );

    if( MI_RESULT_OK != r )
        return r;

    /* Free self pointer */
    PAL_Free(self);

    return MI_RESULT_OK;
}

MI_Result _ProtocolSocketAndBase_Delete(
    ProtocolSocketAndBase* self)
{
    MI_Result r = _ProtocolBase_Finish( &self->internalProtocolBase );

    if( MI_RESULT_OK != r )
        return r;

    /* Free self pointer */
    PAL_Free(self);

    return MI_RESULT_OK;
}

MI_Result Protocol_Run(
    ProtocolBase* self,
    MI_Uint64 timeoutUsec)
{
    /* Run the selector */
    return Selector_Run(self->selector, timeoutUsec, MI_FALSE);
}

static MI_Result _SendIN_IO_thread(
    ProtocolBase* self,
    ProtocolSocket* sendSock,
    Message* message)
{
    /* check params */
    if (!self || !message )
    {
        /* The refcount was bumped when we posted, this will lower and delete
         * if necessary */
        ProtocolSocket_Release(sendSock);
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (self->magic != _MAGIC)
    {
        /* The refcount was bumped when we posted, this will lower and delete
         * if necessary */
        trace_Message_InvalidMagic();
        ProtocolSocket_Release(sendSock);

        return MI_RESULT_INVALID_PARAMETER;
    }

    /* validate handler */
    if (!sendSock || INVALID_SOCK == sendSock->base.sock)
    {
        /* The refcount was bumped when we posted, this will lower and delete
         * if necessary */
        trace_Message_ExpiredHandler(sendSock);
        ProtocolSocket_Release(sendSock);

        return MI_RESULT_FAILED;
    }

    DEBUG_ASSERT(sendSock->message == NULL);
    sendSock->message = message;
    Message_AddRef(message);

    _PrepareMessageForSending(sendSock);

    if( !_RequestCallbackWrite(sendSock) && PRT_TYPE_LISTENER == self->type )
    {
        trace_QueueOverflowOrConnectionAbort(sendSock);
         return MI_RESULT_FAILED;
    }

    /* The refcount was bumped when we posted, this will lower and delete
     * if necessary */
    ProtocolSocket_Release(sendSock);
    return MI_RESULT_OK;
}
