/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "protocol.h"
#include <sock/addr.h>
#include <sock/sock.h>
#include <sock/selector.h>
#include <base/buf.h>
#include <base/log.h>
#include <base/result.h>
#include <base/user.h>
#include <base/paths.h>
#include <pal/strings.h>
#include <pal/format.h>
#include <pal/file.h>
#include <pal/sleep.h>
#include <pal/hashmap.h>
#include <pal/lock.h>

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

#if defined(CONFIG_ENABLE_PREEXEC)
# include "base/preexec.h"
#endif
/*
**==============================================================================
**
** Local definitions:
**
**==============================================================================
*/

#define S_SECRET_STRING_LENGTH 32
#define INVALID_ID ((uid_t)-1)
static const MI_Uint32 _MAGIC = 0xC764445E;
static ProtocolSocket *s_permanentSocket = NULL;
static char s_socketFile[PAL_MAX_PATH_SIZE];
static char s_secretString[S_SECRET_STRING_LENGTH];
static HashMap s_protocolSocketTracker;
static Lock s_trackerLock;
static MI_Result (*authenticateCallback)(PamCheckUserResp*);
static char s_type = 'U';  // 'U': unknown, 'E': engine, 'S': server

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

typedef struct _TrackerBucket
{
    struct _TrackerBucket *next;
    Sock key;
    PVOID value;
}
TrackerBucket;

/* Forward declaration */
static void _PrepareMessageForSending(
    ProtocolSocket *handler);

static MI_Boolean _RequestCallbackWrite(
    ProtocolSocket* handler);

static MI_Result _ProtocolSocketAndBase_New_Server_Connection(
    ProtocolSocketAndBase* protocolSocketAndBase,
    Selector *selector,
    InteractionOpenParams *params,
    Sock *s);

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
        trace_ProtocolSocket_PostFailed( s_type, &self->strand.info.interaction, self->strand.info.interaction.other );
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
        trace_ProtocolSocket_Release(s_type, cs.file, (MI_Uint32)cs.line, self, (unsigned int)ref);
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
        trace_ProtocolSocket_Addref(s_type, cs.file, (MI_Uint32)cs.line, self, (unsigned int)ref);
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
    ProtocolBase* protocolBase = (ProtocolBase*)handler->base.data;

    if(handler->closeOtherScheduled)
        return;

    handler->closeOtherScheduled = MI_TRUE;

    _FreeAuthData(handler);

    /* free outstanding messages, batch */
    if (handler->receivingBatch)
        Batch_Destroy( handler->receivingBatch );
    if (handler->engineBatch)
    {
        // Remove engine's handler from selector list just in case it has not been removed yet. 
        Selector_RemoveHandler(protocolBase->selector, handler->engineHandler);
        Batch_Destroy( handler->engineBatch );
        handler->engineBatch = NULL;
    }

    handler->receivingBatch = 0;
    handler->engineBatch = 0;

    if (handler->message)
    {
        MI_Boolean internalMessage = Message_IsInternalMessage( handler->message );

        Message_Release(handler->message);
        handler->message = 0;

        //ACK up if the message just sent was posted from up
        if (!internalMessage)
            Strand_ScheduleAck( &handler->strand );
    }

    if (!handler->permanent)
    {
        Sock_Close(handler->base.sock);

        /* Mark handler as closed */
        handler->base.sock = INVALID_SOCK;
    }

    // skip for engine communicating with server
    if (!protocolBase->forwardRequests || protocolBase->type == PRT_TYPE_LISTENER)
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
        trace_ProtocolSocket_PostFailed( s_type, &self->strand.info.interaction, self->strand.info.interaction.other );
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
        s_type,
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

    trace_ProtocolSocket_Finish( s_type, self );

    if( protocolBase->type == PRT_TYPE_LISTENER )
    {
        _ProtocolSocket_Delete( self );
    }
    else
    {
        ProtocolSocketAndBase_Delete( (ProtocolSocketAndBase*)self );
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

    Unique features and special Behaviour:
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

/**************** protocolSocketTracker-support **********************************************************/
static size_t _ProtocolSocketTrackerTestHash(const HashBucket *b)
{
    TrackerBucket *bucket = (TrackerBucket*) b;
    size_t h = 0;
    Sock key = bucket->key;
    h = (unsigned)key % 1024;
    return h;
}

static int _ProtocolSocketTrackerTestEqual(const HashBucket *b1, const HashBucket *b2)
{
    TrackerBucket *bucket1 = (TrackerBucket*) b1;
    TrackerBucket *bucket2 = (TrackerBucket*) b2;
    return bucket1->key == bucket2->key;
}

static void _ProtocolSocketTrackerTestRelease(HashBucket *b)
{
    if (b)
    {
        PAL_Free(b);
    }
    return;
}

static MI_Result _ProtocolSocketTrackerRemoveElement(Sock s)
{
    TrackerBucket b;
    int r;

    b.key = s;

    Lock_Acquire(&s_trackerLock);
    r = HashMap_Remove(&s_protocolSocketTracker, (HashBucket*)&b);
    Lock_Release(&s_trackerLock);

    trace_TrackerHashMapRemove(s);

    return r == 0 ? MI_RESULT_OK : MI_RESULT_FAILED;
}

static MI_Result _ProtocolSocketTrackerAddElement(Sock s, void *p)
{
    TrackerBucket *b;
    int r;

    b = (TrackerBucket*)PAL_Calloc(1, sizeof(TrackerBucket));
    if (b == NULL)
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;

    b->key = s;
    b->value = p;

    Lock_Acquire(&s_trackerLock);
    r = HashMap_Insert(&s_protocolSocketTracker, (HashBucket*)b);
    Lock_Release(&s_trackerLock);

    if (r != 0)
    {
        // already exists
        trace_TrackerHashMapAlreadyExists(p, s);
        MI_Result res = _ProtocolSocketTrackerRemoveElement(s);
        if (res == MI_RESULT_OK)
        {
            Lock_Acquire(&s_trackerLock);
            r = HashMap_Insert(&s_protocolSocketTracker, (HashBucket*)b);
            Lock_Release(&s_trackerLock);
        }
    }

    trace_TrackerHashMapAdd(p, s);

    return r == 0 ? MI_RESULT_OK : MI_RESULT_FAILED;
}

static void* _ProtocolSocketTrackerGetElement(Sock s)
{
    TrackerBucket b;
    TrackerBucket *r;

    b.key = s;

    Lock_Acquire(&s_trackerLock);
    r = (TrackerBucket*) HashMap_Find(&s_protocolSocketTracker, (HashBucket*)&b);
    Lock_Release(&s_trackerLock);

    if (r == NULL)
        return NULL;

    trace_TrackerHashMapFind(r->value, s);
    return r->value;
}

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
    const char* fileContent,
    Sock returnSock,
    uid_t uid,
    gid_t gid
    )
{
    BinProtocolNotification* req;
    MI_Boolean retVal = MI_TRUE;

    req = BinProtocolNotification_New(BinNotificationConnectRequest);

    if (!req)
        return MI_FALSE;

    req->forwardSock = returnSock;

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

    if (uid != INVALID_ID && gid != INVALID_ID)
    {
        req->uid = uid;
        req->gid = gid;
    }
    else
    {
        req->uid = geteuid();
        req->gid = getegid();
    }

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
    const char* path,
    Sock returnSock,
    uid_t uid,
    gid_t gid
    )
{
    ProtocolBase* protocolBase = (ProtocolBase*)h->base.data;
    BinProtocolNotification* req;
    MI_Boolean retVal = MI_TRUE;

    req = BinProtocolNotification_New(BinNotificationConnectResponse);

    if (!req)
        return MI_FALSE;

    req->forwardSock = returnSock;

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

    if (protocolBase->expectedSecretString && *protocolBase->expectedSecretString)
    {
        req->message = Batch_Strdup(req->base.batch, protocolBase->expectedSecretString);
        if (!req->message)
        {
            BinProtocolNotification_Release(req);
            return MI_FALSE;
        }
    }

    req->uid = uid;
    req->gid = gid;

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
    Processes auth message while waiting second connect request
    with content of the file.
    Updates auth states correspondingly.
    Parameters:
    handler - socket handler
    binMsg - BinProtocolNotification message with connect request/response

    Return:
    "TRUE" if connection should stay open; "FALSE" if auth failed
        and connection should be closed immediately
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
        /* Auth ok */
        handler->clientAuthState = PRT_AUTH_OK;
        _FreeAuthData(handler);

        /* Get gid from user name */
        if (0 != GetUserGidByUid(handler->authInfo.uid, &handler->authInfo.gid))
        {
            trace_CannotGetUserGidForUid((int)handler->authInfo.uid);
            return MI_FALSE;
        }

        if (!_SendAuthResponse(handler, MI_RESULT_OK, NULL, binMsg->forwardSock, 
                               handler->authInfo.uid, handler->authInfo.gid))
            return MI_FALSE;

        return MI_TRUE;
    }

    trace_AuthFailed_RandomDataMismatch();

    /* Auth failed */
    _SendAuthResponse(handler, MI_RESULT_ACCESS_DENIED, NULL, binMsg->forwardSock, INVALID_ID, INVALID_ID);
    handler->clientAuthState = PRT_AUTH_FAILED;
    return MI_FALSE;
}

/*
    Processes auth message while waiting connect request
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
    BinProtocolNotification* binMsg,
    MI_Boolean *keepConnection)
{
    *keepConnection = MI_FALSE;

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
            if (!_SendAuthResponse(handler, MI_RESULT_OK, NULL, binMsg->forwardSock,
                                   handler->authInfo.uid, handler->authInfo.gid))
                return MI_FALSE;

            /* Auth ok */
            handler->clientAuthState = PRT_AUTH_OK;
            _FreeAuthData(handler);
            return MI_TRUE;
        }

        trace_AuthFailed_ForUser(scs(binMsg->user));

        /* Auth failed */
        _SendAuthResponse(handler, MI_RESULT_ACCESS_DENIED, NULL, binMsg->forwardSock, INVALID_ID, INVALID_ID);
        handler->clientAuthState = PRT_AUTH_FAILED;
        return MI_FALSE;
    }

    if (binMsg->forwardSock != INVALID_SOCK)
    {
        // request from engine
        if (binMsg->uid != INVALID_ID && binMsg->gid != INVALID_ID)
        {
            handler->authInfo.uid = binMsg->uid;
            handler->authInfo.gid = binMsg->gid;
            if (!_SendAuthResponse(handler, MI_RESULT_OK, NULL, binMsg->forwardSock,
                                   binMsg->uid, binMsg->gid))
                return MI_FALSE;

            /* Auth ok */
            handler->clientAuthState = PRT_AUTH_OK;
            return MI_TRUE;
        }
    }
    else
    {
        /* If system supports connection-based auth, use it for
           implicit auth */
        if (0 == GetUIDByConnection((int)handler->base.sock, &handler->authInfo.uid, &handler->authInfo.gid))
        {
            if (!_SendAuthResponse(handler, MI_RESULT_OK, NULL, binMsg->forwardSock,
                                   handler->authInfo.uid, handler->authInfo.gid))
                return MI_FALSE;

            /* Auth ok */
            handler->clientAuthState = PRT_AUTH_OK;
            return MI_TRUE;
        }
    }

    /* If valid uid provided, try implicit credentials (file-based)
        gid will be taken from user name */
    {
        handler->authData = (Protocol_AuthData*)PAL_Calloc(1, sizeof(Protocol_AuthData));

        if (!handler->authData)
        {
            /* Auth failed */
            _SendAuthResponse(handler, MI_RESULT_ACCESS_DENIED, NULL, binMsg->forwardSock, INVALID_ID, INVALID_ID);
            handler->clientAuthState = PRT_AUTH_FAILED;
            return MI_FALSE;
        }

        if (0 != CreateAuthFile(binMsg->uid, handler->authData->authRandom, AUTH_RANDOM_DATA_SIZE, handler->authData->path))
        {
            trace_CannotCreateFileForUser((int)binMsg->uid);

            /* Auth failed */
            _SendAuthResponse(handler, MI_RESULT_ACCESS_DENIED, NULL, binMsg->forwardSock, INVALID_ID, INVALID_ID);
            handler->clientAuthState = PRT_AUTH_FAILED;
            return MI_FALSE;
        }

        /* send file name to the client */
        if (!_SendAuthResponse(handler, MI_RESULT_IN_PROGRESS, handler->authData->path, binMsg->forwardSock, INVALID_ID, INVALID_ID))
            return MI_FALSE;

        /* Auth posponed */
        handler->clientAuthState = PRT_AUTH_WAIT_CONNECTION_REQUEST_WITH_FILE_DATA;
        *keepConnection = MI_TRUE;

        /* Remember uid we used to create file */
        handler->authInfo.uid = binMsg->uid;
        handler->authInfo.gid = INVALID_ID;

        return MI_TRUE;

    }
}

/*
    Processes auth message (either connect request or connect-response)
    Updates auth states correspondingly.
    Parameters:
    handler - socket handler
    msg - BinProtocolNotification message with connect request/response

    Return:
    "TRUE" if connection should stay open; "FALSE" if auth failed
        and connection should be closed immediately
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
    if (PRT_AUTH_WAIT_CONNECTION_REQUEST == handler->clientAuthState)
    {
        MI_Boolean keepConnection;
        MI_Boolean r;

        r = _ProcessAuthMessageWaitingConnectRequest(handler, binMsg, &keepConnection);
        if (r && !keepConnection)
        {
            ProtocolSocket_Release(handler);
        }

        return r;
    }

    /* server waiting for client's file's content request? */
    if (PRT_AUTH_WAIT_CONNECTION_REQUEST_WITH_FILE_DATA == handler->clientAuthState)
    {
        MI_Boolean r;

        r = _ProcessAuthMessageWaitingConnectRequestFileData(handler, binMsg);

        if (r)
        {
            ProtocolSocket_Release(handler);
        }

        return r;
    }

    /* client waiting for server's response? */
    if (PRT_AUTH_WAIT_CONNECTION_RESPONSE == handler->clientAuthState)
    {
        /* un-expected message */
        if (BinNotificationConnectResponse != binMsg->type)
            return MI_FALSE;

        if (binMsg->result == MI_RESULT_OK)
        {
            handler->clientAuthState = PRT_AUTH_OK;
            trace_ClientCredentialsVerfied2();

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
            return _SendAuthRequest(handler, 0, 0, buf, binMsg->forwardSock, INVALID_ID, INVALID_ID);
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

/**************** SocketFile-support **********************************************************/

/* Creates and sends SocketFile request message */
MI_Boolean SendSocketFileRequest(
    ProtocolSocket* h)
{
    PostSocketFile* req;
    MI_Boolean retVal = MI_TRUE;

    s_permanentSocket = h;
    s_type = 'E';

    req = PostSocketFile_New(PostSocketFileRequest);

    if (!req)
        return MI_FALSE;

    /* send message */
    {
        DEBUG_ASSERT(h->message == NULL);
        h->message = (Message*) req;

        Message_AddRef(&req->base);

        _PrepareMessageForSending(h);
        retVal = _RequestCallbackWrite(h);
    }

    PostSocketFile_Release(req);

    return retVal;
}

MI_Boolean SendSocketFileResponse(
    ProtocolSocket* h,
    const char *socketFile,
    const char *expectedSecretString)
{
    PostSocketFile* req;
    MI_Boolean retVal = MI_TRUE;

    DEBUG_ASSERT(socketFile);
    DEBUG_ASSERT(expectedSecretString);

    s_permanentSocket = h;
    s_type = 'S';

    req = PostSocketFile_New(PostSocketFileResponse);

    if (!req)
        return MI_FALSE;

    {
        req->sockFilePath = Batch_Strdup(req->base.batch, socketFile);
        if (!req->sockFilePath)
        {
            PostSocketFile_Release(req);
            return MI_FALSE;
        }
    }

    {
        req->secretString = Batch_Strdup(req->base.batch, expectedSecretString);
        if (!req->secretString)
        {
            PostSocketFile_Release(req);
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

    PostSocketFile_Release(req);

    return retVal;
}

static MI_Boolean _ProcessEngineAuthMessage(
    ProtocolSocket* handler,
    Message *msg)
{
    ProtocolBase* protocolBase = (ProtocolBase*)handler->base.data;
    PostSocketFile* sockMsg;

    if (msg->tag != PostSocketFileTag)
        return MI_FALSE;

    sockMsg = (PostSocketFile*) msg;

    /* server waiting engine's request */
    if (PostSocketFileRequest == sockMsg->type)
    {
        if (!SendSocketFileResponse(handler, protocolBase->socketFile, protocolBase->expectedSecretString))
            return MI_FALSE;

        return MI_TRUE;
    }

    /* engine waiting for server's response */
    if (PostSocketFileResponse == sockMsg->type)
    {
        // secret string is mandatory and can be set only during engine start-up
        if( (sockMsg->secretString == NULL) || 
            (*s_secretString && Strncmp(sockMsg->secretString, s_secretString, S_SECRET_STRING_LENGTH) != 0) )
        {
            trace_AttemptToResetSecretString();
            return MI_FALSE;
        }

        DEBUG_ASSERT(sockMsg->sockFilePath);
        DEBUG_ASSERT(sockMsg->secretString);

        Strlcpy(s_socketFile, sockMsg->sockFilePath, PAL_MAX_PATH_SIZE);
        Strlcpy(s_secretString, sockMsg->secretString, S_SECRET_STRING_LENGTH);
        trace_ServerInfoReceived();

        return MI_TRUE;
    }

    return MI_FALSE;
}

/* Creates and sends socket maintenance message */
static MI_Boolean _SendVerifySocketConnMsg(
    ProtocolSocket* h,
    VerifySocketConnType type,
    const char* message,
    Sock s)
{
    VerifySocketConn* req;
    MI_Boolean retVal = MI_TRUE;

    req = VerifySocketConn_New(type);

    if (!req)
        return MI_FALSE;

    req->sock = s;

    if (message && *message)
    {
        req->message = Batch_Strdup(req->base.batch, message);
        if (!req->message)
        {
            VerifySocketConn_Release(req);
            return MI_FALSE;
        }
    }

    /* send message */
    {
        DEBUG_ASSERT(h->message == NULL);
        h->message = (Message*) req;

        Message_AddRef(&req->base);

        _PrepareMessageForSending(h);
        retVal = _RequestCallbackWrite(h);
    }

    VerifySocketConn_Release(req);

    return retVal;
}

static MI_Boolean _SendCreateAgentMsg(
    ProtocolSocket* h,
    CreateAgentMsgType type,
    uid_t uid,
    gid_t gid,
    pid_t pid,
    const char *libraryName)
{
    CreateAgentMsg* req;
    MI_Boolean retVal = MI_TRUE;

    req = CreateAgentMsg_New(type);

    if (!req)
        return MI_FALSE;

    req->uid = uid;
    req->gid = gid;
    req->pid = pid;

    if (libraryName && *libraryName)
    {
        req->libraryName = Batch_Strdup(req->base.batch, libraryName);
        if (!req->libraryName)
        {
            CreateAgentMsg_Release(req);
            return MI_FALSE;
        }
    }

    /* send message */
    {
        DEBUG_ASSERT(h->message == NULL);
        h->message = (Message*) req;

        Message_AddRef(&req->base);

        _PrepareMessageForSending(h);
        retVal = _RequestCallbackWrite(h);
    }

    CreateAgentMsg_Release(req);

    return retVal;
}

static MI_Boolean _ProcessCreateAgentMsg(
    ProtocolSocket* handler,
    Message *msg)
{
    CreateAgentMsg* agentMsg;
    int logfd = INVALID_SOCK;

    if (msg->tag != CreateAgentMsgTag)
        return MI_FALSE;

    agentMsg = (CreateAgentMsg*) msg;

    if (CreateAgentMsgRequest == agentMsg->type)
    {
        /* create/open log file for agent */
        {
            char path[PAL_MAX_PATH_SIZE];

            if (0 != FormatLogFileName(agentMsg->uid, agentMsg->gid, agentMsg->libraryName, path))
            {
                trace_CannotFormatLogFilename();
                return MI_FALSE;
            }

            /* Create/open file with permissions 644 */
            logfd = open(path, O_WRONLY|O_CREAT|O_APPEND, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
            if (logfd == INVALID_SOCK)
            {
                trace_CreateLogFile_Failed(scs(path), (int)errno);
                return MI_FALSE;
            }
        }

        {
            pid_t child;
            int fdLimit;
            int fd;
            char param_sock[32];
            char param_logfd[32];
            const char *agentProgram = OMI_GetPath(ID_AGENTPROGRAM);
            char realAgentProgram[PATH_MAX];
            const char *destDir = OMI_GetPath(ID_DESTDIR);
            char realDestDir[PATH_MAX];
            const char *provDir = OMI_GetPath(ID_PROVIDERDIR);
            char realProvDir[PATH_MAX];
            char *ret;

            ret = realpath(agentProgram, realAgentProgram);
            if (ret == 0)
                return MI_FALSE;
            ret = realpath(destDir, realDestDir);
            if (ret == 0)
                return MI_FALSE;
            ret = realpath(provDir, realProvDir);
            if (ret == 0)
                return MI_FALSE;

            /* prepare parameter:
               socket fd to attach */
            Snprintf(param_sock, sizeof(param_sock), "%d", (int)handler->base.sock);
            Snprintf(param_logfd, sizeof(param_logfd), "%d", (int)logfd);

            Sock_SetCloseOnExec(handler->base.sock, MI_FALSE);
            Sock_SetCloseOnExec(logfd, MI_FALSE);

            child = fork();

            if (child < 0)
                return MI_FALSE;  /* Failed */

            if (child > 0)
            {
                ProtocolSocket_Release(handler);
                Sock_Close(logfd);                
                return MI_FALSE; /* finished with connection */
            }

            /* We are in child process here */

            /* switch user */
            if (0 != SetUser(agentMsg->uid,agentMsg->gid))
            {
                _exit(1);
            }

            /* Close all open file descriptors except provided socket
               (Some systems have UNLIMITED of 2^64; limit to something reasonable) */

            fdLimit = getdtablesize();
            if (fdLimit > 2500 || fdLimit < 0)
            {
                fdLimit = 2500;
            }

            /* ATTN: close first 3 also! Left for debugging only */
            for (fd = 3; fd < fdLimit; ++fd)
            {
                if (fd != handler->base.sock && fd != logfd)
                    close(fd);
            }

            execl(realAgentProgram,
                  realAgentProgram,
                  param_sock,
                  param_logfd,
                  "--destdir",
                  realDestDir,
                  "--providerdir",
                  realProvDir,
                  "--loglevel",
                  Log_GetLevelString(Log_GetLevel()),
                  agentMsg->libraryName,
                  NULL);

            trace_AgentLaunch_Failed(scs(realAgentProgram), errno);
            _exit(1);
            // return -1;  /* never get here */
        }
    }

    if (CreateAgentMsgResponse == agentMsg->type)
    {
        return MI_TRUE;
    }

    return MI_FALSE;
}

/* Creates and sends PamCheckUserReq request message */
static MI_Boolean _SendPamCheckUserReq(
    const char *user,
    const char *passwd,
    MI_Uint64 handle
    )
{
    PamCheckUserReq *req = NULL;
    MI_Boolean retVal = MI_TRUE;
    ProtocolSocket *protocolSocket = s_permanentSocket;

    req = PamCheckUserReq_New();
    if (!req)
    {
        return MI_FALSE;
    }

    if (user && *user)
    {
        req->user = Batch_Strdup(req->base.batch, user);
        if (!req->user)
        {
            PamCheckUserReq_Release(req);
            return MI_FALSE;
        }
    }

    if (passwd && *passwd)
    {
        req->passwd = Batch_Strdup(req->base.batch, passwd);
        if (!req->passwd)
        {
            PamCheckUserReq_Release(req);
            return MI_FALSE;
        }
    }

    req->handle = handle;

    /* send message */
    {
        DEBUG_ASSERT(protocolSocket->message == NULL);
        protocolSocket->message = (Message*) req;

        Message_AddRef(&req->base);

        _PrepareMessageForSending(protocolSocket);
        retVal = _RequestCallbackWrite(protocolSocket);
    }

    PamCheckUserReq_Release(req);

    return retVal;
}

/* Creates and sends PamCheckUserResp request message */
static MI_Boolean _SendPamCheckUserResp(
    ProtocolSocket *h,
    MI_Uint64 handle,
    MI_Boolean result
    )
{
    ProtocolBase* protocolBase = (ProtocolBase*)h->base.data;
    PamCheckUserResp *req = NULL;
    MI_Boolean retVal = MI_TRUE;

    req = PamCheckUserResp_New();
    if (!req)
    {
        return MI_FALSE;
    }

    req->handle = handle;
    req->result = result;

    if (protocolBase->expectedSecretString && *protocolBase->expectedSecretString)
    {
        req->message = Batch_Strdup(req->base.batch, protocolBase->expectedSecretString);
        if (!req->message)
        {
            PamCheckUserResp_Release(req);
            return MI_FALSE;
        }
    }

    /* send message */
    {
        DEBUG_ASSERT(h->message == NULL);
        h->message = (Message*) req;

        Message_AddRef(&req->base);

        _PrepareMessageForSending(h);
        retVal = _RequestCallbackWrite(h);
    }

    PamCheckUserResp_Release(req);

    return retVal;
}

static MI_Boolean _ProcessPamCheckUserReq(
    ProtocolSocket* handler,
    Message *msg)
{
    PamCheckUserReq* pamMsg;
    MI_Boolean ret;
    MI_Boolean valid = MI_TRUE;

    if (msg->tag != PamCheckUserReqTag)
        return MI_FALSE;

    pamMsg = (PamCheckUserReq*) msg;

    /* server waiting engine's request */

    int r = PamCheckUser(pamMsg->user, pamMsg->passwd);
    if (r != 0)
    {
        trace_ServerFailedPamCheckUser(pamMsg->user);
        valid = MI_FALSE;
    }

    ret = _SendPamCheckUserResp(handler, pamMsg->handle, valid);

    return ret;
}

static MI_Boolean _ProcessPamCheckUserResp(
    ProtocolSocket* handler,
    Message *msg)
{
    PamCheckUserResp* pamMsg;
    MI_Result result;

    if (msg->tag != PamCheckUserRespTag)
        return MI_FALSE;

    pamMsg = (PamCheckUserResp*) msg;

    // server authentication check
    if ( (pamMsg->message != NULL) && (*s_secretString) && (Strncmp(pamMsg->message, s_secretString, S_SECRET_STRING_LENGTH) == 0) )
    {
        trace_ServerCredentialsVerified(handler);
    }
    else
    {
        trace_InvalidServerCredentials();
        return MI_FALSE;
    }
    
    pamMsg->message = NULL;

    /* engine waiting server's response */

    result = authenticateCallback(pamMsg);

    return (MI_RESULT_OK == result) ? MI_TRUE : MI_FALSE;
}

#if defined(CONFIG_ENABLE_PREEXEC)
/* Creates and sends ExecPreexecReq request message */

typedef void (*PreexecCtxCompletion)(void *ctx);

struct Protocol_PreexecContext
{
    void *context;
    PreexecCtxCompletion completion;
};

MI_Boolean SendExecutePreexecRequest(
    void *contextp, 
    PreexecCtxCompletion completion,
    uid_t  uid,
    gid_t  gid,
    const ZChar *nameSpace,
    const ZChar *className,
    MI_Uint64 operationId
    )
{
    ExecPreexecReq *req = NULL;
    MI_Boolean retVal = MI_TRUE;
    ProtocolSocket *protocolSocket = s_permanentSocket;
    struct Protocol_PreexecContext *preexecCtx;
    
    preexecCtx = PAL_Malloc(sizeof(struct Protocol_PreexecContext));
    if (preexecCtx == NULL)
        return MI_FALSE;
    preexecCtx->context = contextp;
    preexecCtx->completion = completion;

    req = ExecPreexecReq_New(operationId);
    if (!req)
    {
        PAL_Free(preexecCtx);
        return MI_FALSE;
    }

    if (nameSpace && *nameSpace)
    {
        req->nameSpace = Batch_ZStrdup(req->base.batch, nameSpace);
        if (!req->nameSpace)
        {
            PAL_Free(preexecCtx);
            ExecPreexecReq_Release(req);
            return MI_FALSE;
        }
    }

    if (className && *className)
    {
        req->className = Batch_ZStrdup(req->base.batch, className);
        if (!req->className)
        {
            PAL_Free(preexecCtx);
            ExecPreexecReq_Release(req);
            return MI_FALSE;
        }
    }

    req->context = (ptrdiff_t)preexecCtx;
    req->uid = uid;
    req->gid = gid;

    /* send message */
    {
        DEBUG_ASSERT(protocolSocket->message == NULL);
        protocolSocket->message = (Message*) req;

        Message_AddRef(&req->base);

        _PrepareMessageForSending(protocolSocket);
        retVal = _RequestCallbackWrite(protocolSocket);
    }

    ExecPreexecReq_Release(req);

    return retVal;
}

/* Creates and sends ExecPreexecResp request message */
MI_Boolean SendExecutePreexecResponse(
    void *contextp, 
    int retval,
    MI_Uint64 operationId
    )
{
    ExecPreexecResp *req = NULL;
    MI_Boolean retVal = MI_TRUE;
    ProtocolSocket *protocolSocket = s_permanentSocket;

    req = ExecPreexecResp_New(operationId);
    if (!req)
    {
        return MI_FALSE;
    }

    req->context = (ptrdiff_t)contextp;
    req->result  = retval;

    /* send message */
    {
        DEBUG_ASSERT(protocolSocket != NULL);
        DEBUG_ASSERT(protocolSocket->message == NULL);
        protocolSocket->message = (Message*) req;

        Message_AddRef(&req->base);

        _PrepareMessageForSending(protocolSocket);
        retVal = _RequestCallbackWrite(protocolSocket);
    }

    ExecPreexecResp_Release(req);

    return retVal;
}

static MI_Boolean _ProcessExecPreexecResp(
    ProtocolSocket* handler,
    Message *msg)
{
    ExecPreexecResp* preexecMsg;
    struct Protocol_PreexecContext *preexecCtx;

    if (msg->tag != ExecPreexecRespTag)
        return MI_FALSE;

    preexecMsg = (ExecPreexecResp*) msg;
    preexecCtx = (struct Protocol_PreexecContext *)(preexecMsg->context);

    /* engine waiting server's response */

    preexecCtx->completion(preexecCtx->context);

    PAL_Free(preexecCtx);

    return MI_TRUE;
}
#endif

static MI_Boolean _ProcessVerifySocketConnMessage(
    ProtocolSocket* handler,
    Message *msg)
{
    ProtocolBase* protocolBase = (ProtocolBase*)handler->base.data;
    VerifySocketConn* sockMsg;

    if (msg->tag != VerifySocketConnTag)
        return MI_FALSE;

    sockMsg = (VerifySocketConn*) msg;

    /* server waiting engine's request */
    if (VerifySocketConnStartup == sockMsg->type)
    {
        DEBUG_ASSERT(handler->engineAuthState == PRT_AUTH_WAIT_CONNECTION_REQUEST);
        if (Strncmp(sockMsg->message, protocolBase->expectedSecretString, S_SECRET_STRING_LENGTH) == 0)
        {
            trace_EngineCredentialsVerified(handler);
            handler->engineAuthState = PRT_AUTH_OK;
        }
        else
        {
            trace_InvalidEngineCredentials();
            _SendVerifySocketConnMsg(handler, VerifySocketConnShutdown, "Invalid secret string received", sockMsg->sock);

            _ProtocolSocket_Cleanup(handler);
        }
        return MI_TRUE;
    }

    /* engine waiting for closing request from server*/
    if (VerifySocketConnShutdown == sockMsg->type)
    {
        handler->base.sock = sockMsg->sock;
        _ProtocolSocket_Cleanup(handler);
        return MI_TRUE;
    }

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
            trace_SocketSendCompleted(s_type, handler);
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
                trace_Socket_ConnectionClosed(s_type, handler);
                return MI_FALSE; /* connection closed */
            }

            if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
            {
                trace_Socket_Sending_Error(s_type, handler, r);
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

/*
    Processes incoming message, including:
        - decoding message from batch
        - invoking callback to process message

    Parameters:
        handler - pointer to received data
    Returns:
        it returns result if 'callback' with the following meaning:
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
        trace_RestoreMessage_Failed(s_type, r, tcs(Result_ToString(r)));
        Batch_Destroy( handler->receivingBatch );
    }

    /* clean up the state */
    handler->receivingBatch = 0;
    handler->receivingPageIndex = 0;
    memset(&handler->recv_buffer,0,sizeof(handler->recv_buffer));

    if (MI_RESULT_OK == r)
    {
        trace_Socket_ReceivedMessage(
            s_type,
            msg,
            msg->tag,
            MessageName(msg->tag),
            msg->operationId );

        trace_AuthStates(s_type, handler, handler->clientAuthState, handler->engineAuthState);

        if (msg->tag == PostSocketFileTag)
        {
            if( _ProcessEngineAuthMessage(handler, msg) )
                ret = PRT_CONTINUE;
        }
        else if (msg->tag == VerifySocketConnTag)
        {
            trace_ServerEstablishingSocket(handler, handler->base.sock);
            if( _ProcessVerifySocketConnMessage(handler, msg) )
                ret = PRT_CONTINUE;
        }
        else if (msg->tag == CreateAgentMsgTag)
        {
            if( _ProcessCreateAgentMsg(handler, msg) )
                ret = PRT_CONTINUE;
        }
        else if (msg->tag == PamCheckUserReqTag)
        {
            if( _ProcessPamCheckUserReq(handler, msg) )
                ret = PRT_CONTINUE;
        }
        else if (msg->tag == PamCheckUserRespTag)
        {
            if( _ProcessPamCheckUserResp(handler, msg) )
                ret = PRT_CONTINUE;
        }
#if defined(CONFIG_ENABLE_PREEXEC)
//      server handles ExecPreexecReqTag

        else if (msg->tag == ExecPreexecRespTag)
        {
            if( _ProcessExecPreexecResp(handler, msg) )
                ret = PRT_CONTINUE;
        }
#endif /* CONFIG_ENABLE_PREEXEC */
        else if (PRT_AUTH_OK != handler->engineAuthState)
        {
            trace_EngineCredentialsNotReceived();
            if (msg->tag == BinProtocolNotificationTag)
            {
                BinProtocolNotification* binMsg = (BinProtocolNotification*) msg;
                
                _SendVerifySocketConnMsg(handler, VerifySocketConnShutdown, "Engine credentials not received", binMsg->forwardSock);

                _ProtocolSocket_Cleanup(handler);
                return PRT_RETURN_FALSE;
            }
        }
        else if (msg->tag == BinProtocolNotificationTag && PRT_AUTH_OK != handler->clientAuthState)
        {
            if (protocolBase->forwardRequests == MI_TRUE)
            {
                BinProtocolNotification* binMsg = (BinProtocolNotification*) msg;                    
                if (binMsg->type == BinNotificationConnectRequest)
                {
                    // forward to server

                    uid_t uid = INVALID_ID;
                    gid_t gid = INVALID_ID;
                    Sock s = binMsg->forwardSock;
                    Sock forwardSock = handler->base.sock;

                    // Note that we are storing (socket, ProtocolSocket*) here
                    r = _ProtocolSocketTrackerAddElement(forwardSock, handler);

                    if(MI_RESULT_OK != r)
                    {
                        trace_TrackerHashMapError();
                        return PRT_RETURN_FALSE;
                    }

                    DEBUG_ASSERT(*s_socketFile);
                    DEBUG_ASSERT(*s_secretString);

                    /* If system supports connection-based auth, use it for
                       implicit auth */
                    if (0 != GetUIDByConnection((int)handler->base.sock, &uid, &gid))
                    {
                        uid = binMsg->uid;
                        gid = binMsg->gid;
                    }

                    /* Create connector socket */
                    {
                        if (!handler->engineBatch)
                        {
                            handler->engineBatch = Batch_New(BATCH_MAX_PAGES);
                            if (!handler->engineBatch)
                            {
                                return PRT_RETURN_FALSE;
                            }
                        }

                        ProtocolSocketAndBase *newSocketAndBase = Batch_GetClear(handler->engineBatch, sizeof(ProtocolSocketAndBase));
                        if (!newSocketAndBase)
                        {
                            trace_BatchAllocFailed();
                            return PRT_RETURN_FALSE;
                        }

                        r = _ProtocolSocketAndBase_New_Server_Connection(newSocketAndBase, protocolBase->selector, NULL, &s);
                        if( r != MI_RESULT_OK )
                        {
                            trace_FailedNewServerConnection();
                            return PRT_RETURN_FALSE;
                        }

                        handler->engineHandler = &newSocketAndBase->protocolSocket.base;
                        handler->clientAuthState = PRT_AUTH_WAIT_CONNECTION_RESPONSE;
                        handler = &newSocketAndBase->protocolSocket;
                        newSocketAndBase->internalProtocolBase.forwardRequests = MI_TRUE;

                        // Note that we are storing (socket, ProtocolSocketAndBase*) here
                        r = _ProtocolSocketTrackerAddElement(s, newSocketAndBase);

                        if(MI_RESULT_OK != r)
                        {
                            trace_TrackerHashMapError();
                            return PRT_RETURN_FALSE;
                        }
                    }

                    handler->clientAuthState = PRT_AUTH_WAIT_CONNECTION_RESPONSE;
                        
                    if (_SendAuthRequest(handler, binMsg->user, binMsg->password, NULL, forwardSock, uid, gid) )                
                    {
                        ret = PRT_CONTINUE;
                    }
                }
                else if (binMsg->type == BinNotificationConnectResponse)
                {
                    // server authentication check
                    if ( (binMsg->message != NULL) && (*s_secretString) && (Strncmp(binMsg->message, s_secretString, S_SECRET_STRING_LENGTH) == 0) )
                    {
                        trace_ServerCredentialsVerified(handler);
                    }
                    else
                    {
                        trace_InvalidServerCredentials();
                        return PRT_RETURN_FALSE;
                    }
                    binMsg->message = NULL;

                    // forward to client

                    Sock s = binMsg->forwardSock;
                    Sock forwardSock = INVALID_SOCK;
                    ProtocolSocket *newHandler = _ProtocolSocketTrackerGetElement(s);
                    if (newHandler == NULL)
                    {
                        trace_TrackerHashMapError();
                        return PRT_RETURN_FALSE;
                    }

                    if (binMsg->result == MI_RESULT_OK || binMsg->result == MI_RESULT_ACCESS_DENIED)
                    {
                        if (binMsg->result == MI_RESULT_OK)
                        {
                            newHandler->clientAuthState = PRT_AUTH_OK;
                            newHandler->authInfo.uid = binMsg->uid;
                            newHandler->authInfo.gid = binMsg->gid;
                            trace_ClientCredentialsVerfied(newHandler);
                        }

                        ProtocolSocketAndBase *socketAndBase = _ProtocolSocketTrackerGetElement(handler->base.sock);
                        if (socketAndBase == NULL)
                        {
                            trace_TrackerHashMapError();
                            return PRT_RETURN_FALSE;
                        }

                        r = _ProtocolSocketTrackerRemoveElement(handler->base.sock);
                        if(MI_RESULT_OK != r)
                        {
                            trace_TrackerHashMapError();
                            return PRT_RETURN_FALSE;
                        }

                        r = _ProtocolSocketTrackerRemoveElement(s);
                        if(MI_RESULT_OK != r)
                        {
                            trace_TrackerHashMapError();
                            return PRT_RETURN_FALSE;
                        }

                        // close socket to server
                        trace_EngineClosingSocket(handler, handler->base.sock);
                    }
                    else
                    {
                        forwardSock = handler->base.sock;
                        ret = PRT_CONTINUE;
                    }

                    handler = newHandler;

                    if(!_SendAuthResponse(handler, binMsg->result, binMsg->authFile, forwardSock, 
                                          binMsg->uid, binMsg->gid))
                    {
                        trace_ClientAuthResponseFailed();
                    }
                }
                else
                {
                    trace_ClientCredentialsNotVerified(msg->tag);
                }
            }
            else
            {
                if( _ProcessAuthMessage(handler, msg) )
                    ret = PRT_CONTINUE;
            }
        }
        else
        {
            //disable receiving anything else until this message is ack'ed
            handler->base.mask &= ~SELECTOR_READ;
            // We cannot use Strand_SchedulePost because we have to do
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
            trace_Socket_ReadHeader_ConnectionClosed(s_type, handler);
            return PRT_RETURN_FALSE; /* connection closed */
        }

        if ( r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK )
        {
            trace_Socket_ReadingHeader_Error(s_type, handler, r);
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
                trace_Socket_ReadingHeader_ErrorPageCount(s_type, handler);
                return PRT_RETURN_FALSE;
            }

            if (handler->recv_buffer.base.magic != PROTOCOL_MAGIC)
            {
                trace_Socket_ReadingHeader_ErrorMagic(s_type, handler);
                return PRT_RETURN_FALSE;
            }

            for (index =0; index < handler->recv_buffer.base.pageCount; index++)
            {
                if (handler->recv_buffer.batchInfo[index].pageSize > MAX_ENVELOPE_SIZE)
                {
                    trace_Socket_ReadingHeader_ErrorBatchSize(s_type, handler);
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
                trace_Socket_ReadingHeader_ErrorCreatingBatch(s_type, handler);
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
        trace_Socket_Read_ConnectionClosed(s_type, handler);
        return PRT_RETURN_FALSE; /* connection closed */
    }

    if ( r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK )
    {
        trace_Socket_Read_Error(s_type, handler, r);
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
            trace_RequestCallbackRead_Failed( s_type, handler );
            if( !handler->isConnected && PRT_TYPE_CONNECTOR == protocolBase->type )
            {
                Strand_ScheduleAux( &handler->strand, PROTOCOLSOCKET_STRANDAUX_CONNECTEVENT );
            }
            goto closeConnection;
        }
        else
        {
            handler->isConnected = MI_TRUE;
            if( PRT_TYPE_CONNECTOR == protocolBase->type && PRT_AUTH_OK == handler->clientAuthState )
            {
                if( Atomic_Swap(&handler->connectEventSent, 1) == 0 )
                {
                    trace_RequestCallback_Connect_OnFirstRead(s_type, handler);
                    Strand_ScheduleAux( &handler->strand, PROTOCOLSOCKET_STRANDAUX_CONNECTEVENT );
                }
            }
        }
    }

    if (mask & SELECTOR_WRITE)
    {
        if (!_RequestCallbackWrite(handler))
        {
            trace_RequestCallbackWrite_Failed( s_type, handler );
            goto closeConnection;
        }
        else
        {
            if( !handler->isConnected )
            {
                handler->isConnected = MI_TRUE;
                if( PRT_TYPE_CONNECTOR == protocolBase->type && PRT_AUTH_OK == handler->clientAuthState )
                {
                    if( Atomic_Swap(&handler->connectEventSent, 1) == 0 )
                    {
                        trace_RequestCallback_Connect_OnFirstWrite( s_type, handler );
                        Strand_ScheduleAux( &handler->strand, PROTOCOLSOCKET_STRANDAUX_CONNECTEVENT );
                    }
                }
            }
        }
    }

    /* Close connection by timeout or error */
    if( (mask & SELECTOR_TIMEOUT) || (mask & SELECTOR_EXCEPTION) )
    {
        trace_RequestCallback_Connect_ClosingAfterMask( s_type, handler, mask );
        goto closeConnection;
    }

    if ((mask & SELECTOR_REMOVE) != 0 ||
        (mask & SELECTOR_DESTROY) != 0)
    {
        trace_RequestCallback_Connect_RemovingHandler( s_type, handler, mask, handler->base.mask );

        _ProtocolSocket_Cleanup(handler);

        // Decrement ref count
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
    trace_Socket_ClosingConnection( s_type, handler, mask );

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
            trace_SockAccept_Failed(s_type, Sock_GetLastError());
            return MI_TRUE;
        }

        r = Sock_SetBlocking(s, MI_FALSE);
        if (r != MI_RESULT_OK)
        {
            trace_SockSetBlocking_Failed(s_type);
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
            trace_SelectorAddHandler_Failed(s_type);
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
    {   /* attach the existing selector */
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
    self->authInfo.uid = INVALID_ID;
    self->authInfo.gid = INVALID_ID;
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
        self->clientAuthState = PRT_AUTH_WAIT_CONNECTION_REQUEST;
        self->engineAuthState = (protocolBase->expectedSecretString == NULL) ? PRT_AUTH_OK : PRT_AUTH_WAIT_CONNECTION_REQUEST;
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
            trace_SocketConnectorFailed(s_type, locator);
            ProtocolSocketAndBase_Delete(self);
            return r;
        }
    }

    /* setting connector's structure */
    {
        ProtocolSocket* h = &self->protocolSocket;

        h->base.sock = connector;
        h->base.mask = SELECTOR_READ | SELECTOR_WRITE | SELECTOR_EXCEPTION;
        h->base.handlerName = MI_T("BINARY_CONNECTOR");
        h->clientAuthState = PRT_AUTH_WAIT_CONNECTION_RESPONSE;
        h->engineAuthState = PRT_AUTH_OK;

        /* send connect request */
        if( !_SendAuthRequest(h, user, password, NULL, INVALID_SOCK, INVALID_ID, INVALID_ID) )
        {
            // this will call _RequestCallback which will schedule a CloseOther,
            // but that is not going delete the object (since it is not even truly opened),
            // so do it explicitly
            Sock_Close(connector);
            ProtocolSocketAndBase_Delete(self);
            return MI_RESULT_FAILED;
        }
    }

    r = _AddProtocolSocket_Handler(self->internalProtocolBase.selector, &self->protocolSocket);
    if (r != MI_RESULT_OK)
    {
        Sock_Close(connector);
        ProtocolSocketAndBase_Delete(self);
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
        h->clientAuthState = PRT_AUTH_OK;

        h->engineAuthState = PRT_AUTH_OK;

        r = _AddProtocolSocket_Handler(self->internalProtocolBase.selector, h);

        if (r != MI_RESULT_OK)
        {
            ProtocolSocketAndBase_Delete(self);
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
        Note: selector-destroy closes all sockects in a list including connector and listener */
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

MI_Result ProtocolSocketAndBase_Delete(
    ProtocolSocketAndBase* self)
{
    MI_Result r = _ProtocolBase_Finish( &self->internalProtocolBase );

    if( MI_RESULT_OK != r )
        return r;

    ptrdiff_t ref = Atomic_Dec(&self->protocolSocket.refCount);

    if (0 == ref)
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
        trace_Message_InvalidMagic(s_type);
        ProtocolSocket_Release(sendSock);

        return MI_RESULT_INVALID_PARAMETER;
    }

    /* validate handler */
    if (!sendSock || INVALID_SOCK == sendSock->base.sock)
    {
        /* The refcount was bumped when we posted, this will lower and delete
         * if necessary */
        trace_Message_ExpiredHandler(s_type, sendSock);
        ProtocolSocket_Release(sendSock);

        return MI_RESULT_FAILED;
    }

    DEBUG_ASSERT(sendSock->message == NULL);
    sendSock->message = message;
    Message_AddRef(message);

    _PrepareMessageForSending(sendSock);

    if( !_RequestCallbackWrite(sendSock) && PRT_TYPE_LISTENER == self->type )
    {
        trace_QueueOverflowOrConnectionAbort(s_type, sendSock);
         return MI_RESULT_FAILED;
    }

    /* The refcount was bumped when we posted, this will lower and delete
     * if necessary */
    ProtocolSocket_Release(sendSock);
    return MI_RESULT_OK;
}

// Establish new connection from Engine to Server
static MI_Result _ProtocolSocketAndBase_New_Server_Connection(
    ProtocolSocketAndBase *protocolSocketAndBase,
    Selector *selector,
    InteractionOpenParams *params,
    Sock *s)
{
    MI_Result r;
    StrandFlags flags;

    flags = params ? STRAND_FLAG_ENTERSTRAND : STRAND_FLAG_NOINTERACTION;
    
    Strand_Init( STRAND_DEBUG(ProtocolFromSocket) &protocolSocketAndBase->protocolSocket.strand, 
                 &_ProtocolSocket_FT, flags, params);
    protocolSocketAndBase->protocolSocket.refCount = 1; //ref associated with Strand. Released on Strand_Finish
    protocolSocketAndBase->protocolSocket.closeOtherScheduled = MI_FALSE;
    protocolSocketAndBase->protocolSocket.base.callback = NULL;
    protocolSocketAndBase->protocolSocket.authInfo.uid = INVALID_ID;
    protocolSocketAndBase->protocolSocket.authInfo.gid = INVALID_ID;

    r = _ProtocolBase_Init(&protocolSocketAndBase->internalProtocolBase, selector, NULL, NULL, PRT_TYPE_FROM_SOCKET);
    if( r != MI_RESULT_OK )
        return r;

    protocolSocketAndBase->protocolSocket.base.data = &protocolSocketAndBase->internalProtocolBase;

    if (params)
    {
        // ProtocolSocketAndBase objects need to delay wait until protocol run is done
        Strand_SetDelayFinish(&protocolSocketAndBase->protocolSocket.strand);

        Strand_Leave( &protocolSocketAndBase->protocolSocket.strand );
    }

    // Connect to server.
    r = _CreateConnector(s, s_socketFile);
    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        trace_SocketConnectorFailed(s_type, s_socketFile);
        return r;
    }

    ProtocolSocket* h = &protocolSocketAndBase->protocolSocket;
    trace_EngineEstablishingSocket(h, *s);

    h->base.sock = *s;
    h->base.mask = SELECTOR_READ | SELECTOR_WRITE | SELECTOR_EXCEPTION;
    h->base.callback = _RequestCallback;
    h->clientAuthState = PRT_AUTH_OK;
    h->engineAuthState = PRT_AUTH_OK;

    r = _AddProtocolSocket_Handler(selector, h);

    if (r != MI_RESULT_OK)
    {
        Sock_Close(*s);
        return r;
    }

    if (!_SendVerifySocketConnMsg(h, VerifySocketConnStartup, s_secretString, INVALID_SOCK))
    {
        Selector_RemoveHandler(selector, &h->base);
        return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
}

MI_Result Protocol_New_Agent_Request(
    ProtocolSocketAndBase** selfOut,
    Selector *selector,
    InteractionOpenParams *params,
    uid_t uid,
    gid_t gid,
    const char *libraryName)
{
    MI_Result r;
    Sock s;

    ProtocolSocketAndBase *socketAndBase = (ProtocolSocketAndBase*)PAL_Calloc(1, sizeof(ProtocolSocketAndBase )); 
    if (!socketAndBase)
    {
        trace_BatchAllocFailed();
        return MI_RESULT_FAILED;
    }

    r = _ProtocolSocketAndBase_New_Server_Connection(socketAndBase, selector, params, &s);
    if( r != MI_RESULT_OK )
    {
        trace_FailedNewServerConnection();
        ProtocolSocketAndBase_Delete(socketAndBase);
        return r;
    }

    socketAndBase->internalProtocolBase.skipInstanceUnpack = MI_TRUE;
    
    if (!_SendCreateAgentMsg(&socketAndBase->protocolSocket, CreateAgentMsgRequest, uid, gid, 0, 
                             libraryName))
    {
        Selector_RemoveHandler(selector, &socketAndBase->protocolSocket.base);
        Sock_Close(s);
        ProtocolSocketAndBase_Delete(socketAndBase);
        return MI_RESULT_FAILED;
    }

    *selfOut = socketAndBase;

    return MI_RESULT_OK;
}

int AskServerToAuthenticate(
    const char *user,
    const char *passwd,
    MI_Uint64 handler,
    MI_Result (*callback)(PamCheckUserResp*))
{
    if (handler == 0)
    {
        trace_EngineAuthenticateNullHandler();
        return -1;
    }

    if (!callback)
    {
        trace_EngineAuthenticateNullCallback();
        return -1;
    }
    authenticateCallback = callback;

    if (_SendPamCheckUserReq(user, passwd, handler) != MI_TRUE)
    {
        trace_FailedSendPamRequest();
        return -1;
    }

    return 0;
}

MI_Result Initialize_ProtocolSocketTracker()
{
    /* Initialize socket tracker and lock */
    Lock_Init(&s_trackerLock);
    return HashMap_Init(&s_protocolSocketTracker, 
                        1, 
                        _ProtocolSocketTrackerTestHash, 
                        _ProtocolSocketTrackerTestEqual, 
                        _ProtocolSocketTrackerTestRelease);
}
