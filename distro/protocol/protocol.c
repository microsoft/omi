/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
**
** Licensed under the Apache License, Version 2.0 (the "License"); you may not
** use this file except in compliance with the License. You may obtain a copy
** of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
** MERCHANTABLITY OR NON-INFRINGEMENT.
**
** See the Apache 2 License for the specific language governing permissions
** and limitations under the License.
**
**==============================================================================
*/

#include <assert.h>
#include "protocol.h"
#include <sock/addr.h>
#include <sock/sock.h>
#include <sock/selector.h>
#include "header.h"
#include <sock/thread.h>
#include <base/buf.h>
#include <base/log.h>
#include <base/result.h>
#include <base/user.h>
#include <io/io.h>

// #define ENABLE_TRACING
// #define TRACING_LEVEL 4
#include <logging.h>

/*
**==============================================================================
**
** Local definitions:
**
**==============================================================================
*/

static const MI_Uint32 _MAGIC = 0xC764445E;
#define SR_SOCKET_OUT_QUEUE_WATERMARK_LOW  4
#define SR_SOCKET_OUT_QUEUE_WATERMARK_HIGH  12
#define SR_SOCKET_OUT_QUEUE_WATERMARK_CRITICAL  256

typedef enum _Protocol_AuthState
{
    /* authentication failed (intentionaly takes value '0')*/
    PRT_AUTH_FAILED,

    /* listener (server) waits for connect request */
    PRT_AUTH_WAIT_CONNECTION_REQUEST,

    /* listener (server) waits for second connect request with random data from file */
    PRT_AUTH_WAIT_CONNECTION_REQUEST_WITH_FILE_DATA,

    /* connector (client) waits for server's response */
    PRT_AUTH_WAIT_CONNECTION_RESPONSE,

    /* authentication completed */
    PRT_AUTH_OK
}
Protocol_AuthState;

typedef enum _Protocol_Type
{
    PRT_TYPE_LISTENER,
    PRT_TYPE_CONNECTOR,
    PRT_TYPE_FROM_SOCKET
}
Protocol_Type;

struct _Protocol
{
    MI_Uint32 magic;
    Selector internal_selector;
    Selector*   selector;
    Addr addr;
    struct _Protocol_SR_SocketData* connectorHandle;
    ProtocolCallback callback;
    void* callbackData;
    ProtocolEventCallback eventCallback;
    void* eventCallbackData;
    Protocol_Type   type;
    MI_Boolean  internal_selector_used;
    /* Indicates whether instance has to be upacked or stored as byte array */
    MI_Boolean  skipInstanceUnpack;
};

/* Keeps data for file-based authentication */
typedef struct _Protocol_AuthData
{
    char path[MAX_PATH_SIZE];
    char   authRandom[AUTH_RANDOM_DATA_SIZE];
}
Protocol_AuthData;

typedef struct _Protocol_SR_SocketData
{
    /* based member*/
    Handler     base;

    /* sending data */
    /* Linked list of messages to send */
    ListElem* head;
    ListElem* tail;

    /* ref counter
    NOTE:
        socket may be disconnected, but structure is still alive
        if some outstanding request are not completed.
        refcounter gets '+1' for being connected and '+1' for each outstanding request */
    int     refcounter;

    /* currently sending message */
    Message*    message;
    size_t          sentCurrentBlockBytes;
    int             sendingPageIndex; /* 0 for header otherwise 1-N page index */
    int             sendingQueueLength; /* number of messages in list to send; -1 to disbale watermarks */

    /* receiving data */
    Batch       *receivingBatch;
    size_t          receivedCurrentBlockBytes;
    int             receivingPageIndex; /* 0 for header otherwise 1-N page index */

    /* send/recv buffers */
    Header recv_buffer;
    Header send_buffer;

    /* Auth state */
    Protocol_AuthState  authState;
    /* server side - authenticated user's IDs */
    uid_t uid;
    gid_t gid;
    Protocol_AuthData* authData;

    /* Whether this is a connector */
    MI_Boolean isConnector;

    /* Whether connection has been established */
    MI_Boolean isConnected;

}
Protocol_SR_SocketData;

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
    Protocol_SR_SocketData *handler);

static MI_Boolean _RequestCallbackWrite(
    Protocol_SR_SocketData* handler);

/**************** Auth-support **********************************************************/
/* remove auth file and free auth data */
static void _FreeAuthData(
    Protocol_SR_SocketData* h)
{
    if (h->authData)
    {
#if defined(CONFIG_POSIX)
        unlink(h->authData->path);
#endif
        free(h->authData);
        h->authData = 0;
    }
}

/* Creates and sends authentication request message */
static MI_Boolean _SendAuthRequest(
    Protocol_SR_SocketData* h,
    const char* user,
    const char* password,
    const char* fileContent)
{
    BinProtocolNotification* req;

    req = BinProtocolNotification_New(BinNotificationConnectRequest);

    if (req == NULL)
        return MI_FALSE;

    if (user != NULL && *user != '\0')
    {
        req->user = Batch_Strdup(req->base.batch, user);
        if (req->user == NULL)
        {
            BinProtocolNotification_Release(req);
            return MI_FALSE;
        }
    }

    if (password != NULL && *password != '\0')
    {
        req->password = Batch_Strdup(req->base.batch, password);
        if (req->password == NULL)
        {
            BinProtocolNotification_Release(req);
            return MI_FALSE;
        }
    }

    req->uid = geteuid();
    req->gid = getegid();

    if (fileContent != NULL)
    {
        memcpy(req->authData, fileContent, sizeof(req->authData));
    }

    /* send message */
    {
        /* add message to the list */
        List_Prepend(&h->head, &h->tail, (ListElem*)req);

        if (-1 != h->sendingQueueLength)
            h->sendingQueueLength++;

        Message_AddRef(&req->base);

        _PrepareMessageForSending(h);
        _RequestCallbackWrite(h);
    }

    BinProtocolNotification_Release(req);

    return MI_TRUE;
}

static MI_Boolean _SendAuthResponse(
    Protocol_SR_SocketData* h,
    MI_Result result,
    const char* path)
{
    BinProtocolNotification* req;

    req = BinProtocolNotification_New(BinNotificationConnectResponse);

    if (req == NULL)
        return MI_FALSE;

    req->result = result;
    if (path != NULL && *path != '\0')
    {
        req->authFile = Batch_Strdup(req->base.batch, path);
        if (req->authFile == NULL)
        {
            BinProtocolNotification_Release(req);
            return MI_FALSE;
        }
    }

    /* send message */
    {
        /* add message to the list */
        List_Prepend(&h->head, &h->tail, (ListElem*)req);

        if (-1 != h->sendingQueueLength)
            h->sendingQueueLength++;

        Message_AddRef(&req->base);

        _PrepareMessageForSending(h);
        _RequestCallbackWrite(h);
    }

    BinProtocolNotification_Release(req);

    return MI_TRUE;
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
        and conneciton should be closed immediately
*/
static MI_Boolean _ProcessAuthMessageWaitingConnectRequestFileData(
    Protocol_SR_SocketData* handler,
    BinProtocolNotification* binMsg)
{
    /* un-expected message */
    if (BinNotificationConnectRequest != binMsg->type)
        return MI_FALSE;

    /* Check internal state */
    if (handler->authData == NULL)
        return MI_FALSE;

    if (memcmp(binMsg->authData, handler->authData->authRandom, AUTH_RANDOM_DATA_SIZE) == 0)
    {
        if (!_SendAuthResponse(handler, MI_RESULT_OK, NULL))
            return MI_FALSE;

        /* Auth ok */
        handler->authState = PRT_AUTH_OK;
        _FreeAuthData(handler);

        /* Get gid from user name */
        if (0 != GetUserGidByUid(handler->uid, &handler->gid))
        {
            LOGW((ZT("_ProcessAuthMessageWaitingConnectRequestFileData - Cannot get user's GID for UID %d"), (int)handler->uid));
            return MI_FALSE;
        }

        return MI_TRUE;
    }

    LOGW((ZT("_ProcessAuthMessageWaitingConnectRequestFileData - Auth failed. Random data mismatch")));

    /* Auth failed */
    _SendAuthResponse(handler, MI_RESULT_ACCESS_DENIED, NULL);
    handler->authState = PRT_AUTH_FAILED;
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
        and conneciton should be closed immediately
*/
static MI_Boolean _ProcessAuthMessageWaitingConnectRequest(
    Protocol_SR_SocketData* handler,
    BinProtocolNotification* binMsg)
{
    /* un-expected message */
    if (BinNotificationConnectRequest != binMsg->type)
        return MI_FALSE;

    /* Use explicit credentials if provided */
    if (binMsg->user)
    {
        /* use empty password if not set */
        if (binMsg->password == NULL)
            binMsg->password = "";

        if (AuthenticateUser(binMsg->user, binMsg->password) == 0 &&
            LookupUser(binMsg->user, &handler->uid, &handler->gid) == 0)
        {
            if (!_SendAuthResponse(handler, MI_RESULT_OK, NULL))
                return MI_FALSE;

            /* Auth ok */
            handler->authState = PRT_AUTH_OK;
            _FreeAuthData(handler);
            return MI_TRUE;
        }

        LOGW((ZT(" _ProcessAuthMessageWaitingConnectRequest - Auth failed for user %s"), scs(binMsg->user)));

        /* Auth failed */
        _SendAuthResponse(handler, MI_RESULT_ACCESS_DENIED, NULL);
        handler->authState = PRT_AUTH_FAILED;
        return MI_FALSE;
    }

    /* If system supports connection-based auth, use it for
        implicit auth */
    if (GetUIDByConnection((int)handler->base.sock, &handler->uid, &handler->gid) == 0)
    {
        if (!_SendAuthResponse(handler, MI_RESULT_OK, NULL))
            return MI_FALSE;

        /* Auth ok */
        handler->authState = PRT_AUTH_OK;
        return MI_TRUE;
    }
#if defined(CONFIG_OS_WINDOWS)
    /* ignore auth on Windows */
    {
        if (!_SendAuthResponse(handler, MI_RESULT_OK, NULL))
            return MI_FALSE;

        /* Auth ok */
        handler->uid = -1;
        handler->gid = -1;
        handler->authState = PRT_AUTH_OK;
        return MI_TRUE;
    }
#else

    /* If valid uid provided, try implicit credentials (file-based)
        gid will be taken from user name */
    {
        handler->authData = (Protocol_AuthData*)calloc(1, sizeof(Protocol_AuthData));

        if (handler->authData == NULL)
        {
            /* Auth failed */
            _SendAuthResponse(handler, MI_RESULT_ACCESS_DENIED, NULL);
            handler->authState = PRT_AUTH_FAILED;
            return MI_FALSE;
        }

        if (0 != CreateAuthFile(binMsg->uid, handler->authData->authRandom, AUTH_RANDOM_DATA_SIZE, handler->authData->path))
        {
            LOGW((ZT(" _ProcessAuthMessageWaitingConnectRequest - Cannot create file for user UID %d"), (int)binMsg->uid));

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
        handler->uid = binMsg->uid;
        handler->gid = -1;

        return MI_TRUE;

    }
#endif
}

/*
    Processes auth message (either connect request or connect-response)
    Updates auth states correspondingly.
    Parameters:
    handler - socket handler
    msg - BinProtocolNotification message with connect request/response

    Return:
    "TRUE" if connection should stay open; "FALSE" if auth failed
        and conneciton should be closed immediately
*/
static MI_Boolean _ProcessAuthMessage(
    Protocol_SR_SocketData* handler,
    Message* msg)
{
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

            /* process backlog items (if any) */
            _PrepareMessageForSending(handler);
            _RequestCallbackWrite(handler);
            return MI_TRUE;
        }
        else if (binMsg->result == MI_RESULT_IN_PROGRESS && binMsg->authFile)
        {
            /* send back file's content */
            char buf[AUTH_RANDOM_DATA_SIZE];
            FILE* is = Fopen(binMsg->authFile, "r");

            if (is == NULL)
            {
                LOGE((ZT(" _ProcessAuthMessage - Cannot open auth data file: %s"), scs(binMsg->authFile)));
                return MI_FALSE;
            }

            /* Read auth data from the file. */
            if (sizeof buf != fread(buf, 1, sizeof buf, is))
            {
                LOGE((ZT("_ProcessAuthMessage - Cannot read from auth data file: %s"), scs(binMsg->authFile)));
                fclose(is);
                return MI_FALSE;
            }

            fclose(is);
            return _SendAuthRequest(handler, 0, 0, buf);
        }
        else
        {
            /* PROTOCOLEVENT_DISCONNECT */
            if (handler->isConnector)
            {
                Protocol* self = (Protocol*)handler->base.data;
                if (self->eventCallback != NULL)
                {
                    (*self->eventCallback)(self,
                                           handler->isConnected ? PROTOCOLEVENT_DISCONNECT : PROTOCOLEVENT_CONNECT_FAILED,
                                           self->eventCallbackData);
                }
                handler->isConnected = MI_FALSE;
            }
        }

        return MI_FALSE;
    }

    /* unknown state? */
    return MI_FALSE;
}

/****************************************************************************************/
static void _RemoveAllMessages(
    Protocol_SR_SocketData* handler)
{
    while (handler->head)
    {
        Message* msg = (Message*)handler->head;

        List_Remove(&handler->head, &handler->tail, (ListElem*)msg);
        Message_Release(msg);

        if (-1 != handler->sendingQueueLength)
            handler->sendingQueueLength--;
    }
}

static void _Release(
    Protocol_SR_SocketData* handler)
{
    if (--handler->refcounter == 0)
    {
        free(handler);
    }
}

static void _PrepareMessageForSending(
    Protocol_SR_SocketData *handler)
{
    /* check for high watermark */
    if (handler->sendingQueueLength == SR_SOCKET_OUT_QUEUE_WATERMARK_HIGH)
        handler->base.mask &= ~SELECTOR_READ;

    /* check for high watermark */
    if (handler->sendingQueueLength == SR_SOCKET_OUT_QUEUE_WATERMARK_LOW)
        handler->base.mask |= SELECTOR_READ;

    if (handler->message != NULL)
        return; /* already sending */

    if (handler->head == NULL)
    {
        handler->base.mask &= ~SELECTOR_WRITE;
        return; /*nothing to do*/
    }

    /* before auth is complete, only auth-related messages should be sent */
    if (PRT_AUTH_OK != handler->authState && BinProtocolNotificationTag != ((Message*)handler->head)->tag)
    {
        handler->base.mask &= ~SELECTOR_WRITE;
        return; /*nothing to do*/
    }

    handler->message = (Message*)handler->head;
    List_Remove(&handler->head, &handler->tail, (ListElem*)handler->message);

    if (-1 != handler->sendingQueueLength)
        handler->sendingQueueLength--;

    /* reset sending attributes */
    handler->sendingPageIndex = 0;
    handler->sentCurrentBlockBytes = 0;

    memset(&handler->send_buffer, 0, sizeof(handler->send_buffer));
    handler->send_buffer.base.magic = PROTOCOL_MAGIC;
    handler->send_buffer.base.version = PROTOCOL_VERSION;
    handler->send_buffer.base.pageCount = (MI_Uint32)Batch_GetPageCount(handler->message->batch);
    handler->send_buffer.base.originalMessagePointer = handler->message;

    /* ATTN! */
    assert (handler->send_buffer.base.pageCount <= PROTOCOL_HEADER_MAX_PAGES);

    /* get page info */

    Batch_GetPageInfo(handler->message->batch, handler->send_buffer.batchInfo);

    /* mark handler as 'want-write' */
    handler->base.mask |= SELECTOR_WRITE;
}

static MI_Boolean _RequestCallbackWrite(
    Protocol_SR_SocketData* handler)
{
    /* try to write to socket as much as possible */
    size_t sent;
    MI_Result r;

    for ( ; ; )
    {
        /* buffers to write */
        struct iovec buffers[32];
        size_t counter;

        if ( !handler->message )
        { /* nothing to send */
            handler->base.mask &= ~SELECTOR_WRITE;
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

            buffers[counter].iov_base = (void*)buf;

            buffers[counter].iov_len = (index == 0) ? (sizeof(HeaderBase) + sizeof(Header_BatchInfoItem) * handler->send_buffer.base.pageCount)
                : handler->send_buffer.batchInfo[index - 1].pageSize;

            if (counter == 0)
                buffers[counter].iov_base = (void*)((unsigned char*)buffers[counter].iov_base - handler->sentCurrentBlockBytes);

            if (index == handler->send_buffer.base.pageCount)
            {
                counter++;
                break;
            }
        }

        sent = 0;

        r = Sock_WriteV(handler->base.sock, buffers, counter, &sent);

        LOGD2((ZT("_RequestCallbackWrite - Sent %lu bytes with result %d (%s)"), sent, (int)r, mistrerror(r)));

        if (r == MI_RESULT_OK && sent == 0)
            return MI_FALSE; /* conection closed */

        if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
            return MI_FALSE;

        if (sent == 0)
            return MI_TRUE;

        /* update index */
        for (counter = 0; counter < MI_COUNT(buffers); counter++)
        {
            if (sent == 0)
                break;

            if (sent >= buffers[counter].iov_len)
            {
                sent -= buffers[counter].iov_len;
                handler->sendingPageIndex++;
                handler->sentCurrentBlockBytes = 0;
                continue;
            }

            handler->sentCurrentBlockBytes += sent;
            break;
        }

        if (handler->sendingPageIndex - 1 == (int)handler->send_buffer.base.pageCount)
        {
            LOGD2((ZT("_RequestCallbackWrite - Message sent. tag %d (%s)"), handler->message->tag, messagetagnamestr(handler->message->tag)));

            /* next message */
            Message_Release(handler->message);
            handler->message = 0;

            _PrepareMessageForSending(handler);
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
static MI_Boolean _ProcessReceivedMessage(
    Protocol_SR_SocketData* handler)
{
    MI_Result r;
    Message* msg = 0;
    Protocol* self = (Protocol*)handler->base.data;
    MI_Boolean ret = MI_TRUE;

    /* create a message from a batch */
    r = MessageFromBatch(
        handler->receivingBatch,
        handler->recv_buffer.base.originalMessagePointer,
        handler->recv_buffer.batchInfo,
        handler->recv_buffer.base.pageCount,
        self->skipInstanceUnpack,
        &msg);

    if (r == MI_RESULT_OK)
    {
        LOGD2((ZT("_ProcessReceivedMessage - Message received. tag %d (%s)"), msg->tag, messagetagnamestr(msg->tag)));

        if (PRT_AUTH_OK != handler->authState)
        {
            ret = _ProcessAuthMessage(handler, msg);
        }
        else
        {
            /* attach client id */
            msg->clientID = PtrToUint64(handler);

            /* +1 for incoming request */
            handler->refcounter++;

            /* auth info */
            msg->uid = handler->uid;
            msg->gid = handler->gid;

            /* count message in for back-pressure feature (only Instances) */
            if (PostInstanceMsgTag == msg->tag &&
                PRT_TYPE_FROM_SOCKET == self->type)
                Selector_NewInstanceCreated(self->selector, msg);

            ret = (*self->callback)(self, msg, self->callbackData);
        }

        Message_Release(msg);
    }
    else
    {
        LOGW((ZT("_ProcessReceivedMessage - Failed to restore message %d [%Z]"), (int)r, zcs(Result_ToString(r))));
        LOGE2((ZT("_ProcessReceivedMessage - Failed to restore message with error: %d (%s)"), (int)r, mistrerror(r)));
        Batch_Destroy(handler->receivingBatch);
    }

    /* clean up the state */
    handler->receivingBatch = 0;
    handler->receivingPageIndex = 0;
    memset(&handler->recv_buffer, 0 ,sizeof(handler->recv_buffer));

    return ret;
}


static Protocol_CallbackResult _ReadHeader(
    Protocol_SR_SocketData* handler)
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

        if (r == MI_RESULT_OK && received == 0)
            return PRT_RETURN_FALSE; /* conection closed */

        if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
            return PRT_RETURN_FALSE;

        if (!received)
            return PRT_RETURN_TRUE;

        handler->receivedCurrentBlockBytes += received;

        if (handler->receivedCurrentBlockBytes == buf_size)
        {
            /* got header - validate/allocate as required */
            if (handler->recv_buffer.base.pageCount > PROTOCOL_HEADER_MAX_PAGES)
                return PRT_RETURN_FALSE;

            if (handler->recv_buffer.base.magic != PROTOCOL_MAGIC)
                return PRT_RETURN_FALSE;

            for (index = 0; index < handler->recv_buffer.base.pageCount; index++)
            {
                if (handler->recv_buffer.batchInfo[index].pageSize > (64*1024))
                    return PRT_RETURN_FALSE;
            }

            /* check if page info is also retrieved */
            if (buf_size != ((sizeof(HeaderBase) + sizeof(Header_BatchInfoItem) * handler->recv_buffer.base.pageCount)))
                continue;

            /* create a batch */
            if (!Batch_CreateBatchByPageInfo(
                &handler->receivingBatch,
                handler->recv_buffer.batchInfo,
                handler->recv_buffer.base.pageCount))
                return PRT_RETURN_FALSE;

            /* skip to next page */
            handler->receivingPageIndex++;
            handler->receivedCurrentBlockBytes = 0;

            if (handler->receivingPageIndex - 1 == (int)handler->recv_buffer.base.pageCount)
            {   /* received the whole message - process it */
                if (!_ProcessReceivedMessage(handler))
                    return PRT_RETURN_FALSE;
            }
            break;
        } /* if we read the whole buffer */
    } /* for( ; ; ) */
    return PRT_CONTINUE;
}

static Protocol_CallbackResult _ReadAllPages(
    Protocol_SR_SocketData* handler)
{
    size_t received;
    MI_Result r;
    /* buffers to write */
    struct iovec buffers[32];
    size_t counter;

    /* are we done with header? - if not, return 'continue' */
    if (handler->receivingPageIndex == 0)
        return PRT_CONTINUE;


    for (counter = 0; counter < MI_COUNT(buffers); counter++)
    {
        const char* buf;
        MI_Uint32 index = (MI_Uint32)(handler->receivingPageIndex + counter);

        buf = Batch_GetPageByIndex(handler->receivingBatch, index - 1);

        if (counter == 0)
            buf += handler->receivedCurrentBlockBytes;

        buffers[counter].iov_base = (void*)buf;
        buffers[counter].iov_len = handler->recv_buffer.batchInfo[index - 1].pageSize;

        if (counter == 0)
            buffers[counter].iov_len -= handler->receivedCurrentBlockBytes;

        if ( index == handler->recv_buffer.base.pageCount)
        {
            counter++;
            break;
        }
    }

    received = 0;

    r = Sock_ReadV(handler->base.sock, buffers, counter, &received);

    LOGD2((ZT("_ReadAllPages - Read %lu bytes with result %d (%s)"), received, (int)r, mistrerror(r)));

    if (r == MI_RESULT_OK && received == 0)
        return PRT_RETURN_FALSE; /* conection closed */

    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
        return PRT_RETURN_FALSE;

    if (!received)
        return PRT_RETURN_TRUE;

    /* update index */
    for (counter = 0; counter < MI_COUNT(buffers); counter++)
    {
        if (!received)
            break;

        if (received >= buffers[counter].iov_len)
        {
            received -= buffers[counter].iov_len;
            handler->receivingPageIndex++;
            handler->receivedCurrentBlockBytes = 0;
            continue;
        }

        handler->receivedCurrentBlockBytes += received;
        break;
    }

    if (handler->receivingPageIndex - 1 == (int)handler->recv_buffer.base.pageCount)
    {   /* received the whole message - process it */
        if (!_ProcessReceivedMessage(handler))
            return PRT_RETURN_FALSE;
    }

    return PRT_CONTINUE;
}

static MI_Boolean _RequestCallbackRead(
    Protocol_SR_SocketData* handler)
{
//  int fullMessagesREceived;

    /* we have to keep repeating read until 'WOULD_BLOCK is returned;
        Windows does not reset event until read buffer is empty */
//  for (fullMessagesReceived = 0; fullMessagesReceived < 3; )
    for ( ; ; )
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
    } /* for ( ; ; )*/
//  return MI_TRUE;
}

static MI_Boolean _RequestCallback(
    Selector* sel,
    Handler* handlerIn,
    MI_Uint32 mask,
    MI_Uint64 currentTimeUsec)
{
    Protocol_SR_SocketData* handler = (Protocol_SR_SocketData*)handlerIn;

    MI_UNUSED(sel);
    MI_UNUSED(currentTimeUsec);

    LOGD2((ZT("RequestCallback - Begin. mask: 0x%X (%s)"), (unsigned int)mask, selectorflagstr(mask)));

    if (mask & SELECTOR_READ)
    {
        if (!_RequestCallbackRead(handler))
        {
            /* PROTOCOLEVENT_DISCONNECT */
            if (handler->isConnector)
            {
                Protocol* self = (Protocol*)handler->base.data;
                if (self->eventCallback != NULL)
                {
                    (*self->eventCallback)(self,
                                           handler->isConnected ? PROTOCOLEVENT_DISCONNECT : PROTOCOLEVENT_CONNECT_FAILED,
                                           self->eventCallbackData);
                }
                handler->isConnected = MI_FALSE;
            }
            goto closeConnection;
        }
        else if (handler->isConnector && !handler->isConnected)
        {
            Protocol* self = (Protocol*)handler->base.data;
            if (self->eventCallback)
            {
                (*self->eventCallback)(self, PROTOCOLEVENT_CONNECT, self->eventCallbackData);
            }
            handler->isConnected = MI_TRUE;
        }
    }

    if (mask & SELECTOR_WRITE)
    {
        if (!_RequestCallbackWrite(handler))
        {
            /* PROTOCOLEVENT_DISCONNECT */
            if (handler->isConnector && handler->isConnected)
            {
                Protocol* self = (Protocol*)handler->base.data;
                if (self->eventCallback)
                {
                    (*self->eventCallback)(self, PROTOCOLEVENT_DISCONNECT, self->eventCallbackData);
                }
                handler->isConnected = MI_FALSE;
            }
            goto closeConnection;
        }
        else if (handler->isConnector && !handler->isConnected)
        {
            Protocol* self = (Protocol*)handler->base.data;
            if (self->eventCallback)
            {
                (*self->eventCallback)(self, PROTOCOLEVENT_CONNECT, self->eventCallbackData);
            }
            handler->isConnected = MI_TRUE;
        }
    }

    /* Close connection by timeout */
    if (mask & SELECTOR_TIMEOUT)
    {
        LOGE2((ZT("RequestCallback - Received timed out status")));
        return MI_FALSE;
    }

    if ((mask & SELECTOR_REMOVE) != 0 || (mask & SELECTOR_DESTROY) != 0)
    {
        Protocol* self = (Protocol*)handler->base.data;

        _FreeAuthData(handler);

        /* free outstanding messages, batch */
        if (handler->receivingBatch)
            Batch_Destroy(handler->receivingBatch);

        handler->receivingBatch = 0;

        if (handler->message)
            Message_Release(handler->message);

        handler->message = 0;

        _RemoveAllMessages(handler);

        Sock_Close(handler->base.sock);

        /* Mark handler as closed */
        handler->base.sock = INVALID_SOCK;

        /* if connection sokcet was released, invalidate pointer to it */
        if (self != NULL && handler == self->connectorHandle)
            self->connectorHandle = NULL;

        if (handler->isConnector)
            free(handler);
        else
            _Release(handler);
    }

    LOGD2((ZT("RequestCallback - OK exit")));

    return MI_TRUE;

closeConnection:

    LOGE2((ZT("_RequestCallback - Closed client connection")));

    return MI_FALSE;
}

static MI_Boolean _ListenerCallback(
    Selector* sel,
    Handler* handler,
    MI_Uint32 mask,
    MI_Uint64 currentTimeUsec)
{
    Protocol* self = (Protocol*)handler->data;
    MI_Result r;
    Sock s;
    Addr addr;
    Protocol_SR_SocketData* h;

    sel=sel;
    mask=mask;
    currentTimeUsec = currentTimeUsec;

    if (mask & SELECTOR_READ)
    {
        /* Accept the incoming connection */
        r = Sock_Accept(handler->sock, &s, &addr);

        if (MI_RESULT_WOULD_BLOCK == r)
            return MI_TRUE;

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("_ListenerCallback - Sock_Accept failed with error: %d"), Sock_GetLastError()));
            return MI_TRUE;
        }

        r = Sock_SetBlocking(s, MI_FALSE);
        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("_ListenerCallback( - Sock_SetBlocking failed with error: %d (%s)"), (int)r, mistrerror(r)));
            Sock_Close(s);
            return MI_TRUE;
        }

        /* Create handler */
        h = (Protocol_SR_SocketData*)calloc(1, sizeof(Protocol_SR_SocketData));

        if (h == NULL)
        {
            LOGE2((ZT("_ListenerCallback - calloc failed")));
            return MI_TRUE;
        }

        h->base.sock = s;
        h->base.mask = SELECTOR_READ | SELECTOR_EXCEPTION;
        h->base.callback = _RequestCallback;
        h->base.data = self;

        /* get '1' for connected */
        h->refcounter = 1;

        /* waiting for connect-request */
        h->authState = PRT_AUTH_WAIT_CONNECTION_REQUEST;

        /* Watch for read events on the incoming connection */
        r = Selector_AddHandler(self->selector, &h->base);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("_ListenerCallback - Selector_AddHandler failed with error: %d (%s)"), (int)r, mistrerror(r)));
            return MI_TRUE;
        }
    }

    if ((mask & SELECTOR_REMOVE) != 0 || (mask & SELECTOR_DESTROY) != 0)
    {
        Sock_Close(handler->sock);
        free(handler);
    }

    return MI_TRUE;
}

static MI_Result _CreateListener(
    Sock* s,
    const char* locator)
{
    const char* posColon;

    posColon = strchr(locator, ':');

    if (posColon == NULL)
    {
        return Sock_CreateLocalListener(s, locator);
    }

    /* create listener for remote address like host:port or :port (ANYADDR) */
    {
        unsigned short port = (unsigned short)atol(posColon+1);
        char host[128];
        unsigned int len = (unsigned int)(posColon - locator);
        Addr addr;
        MI_Result r;

        if (len > 0)
        {
            if (len >= sizeof host - 1)
            {
                LOGE2((ZT("_CreateListener - host portion of name too long")));
                return MI_RESULT_FAILED;
            }

            memcpy(host, locator, len);
            host[len] = '\0';

            // Initialize address.
            r = Addr_Init(&addr, host, port, MI_FALSE);
            if (r != MI_RESULT_OK)
            {
                LOGE2((ZT("_CreateListener - AddrInit failed with error: %d (%s)"), (int)r, mistrerror(r)));
                return r;
            }
        }
        else
        {
            Addr_InitAny(&addr, port);
        }

        return Sock_CreateListener(s, &addr);
    }
}

static MI_Result _CreateSocketAndConnect(
    Sock* s,
    Addr* addr)
{
    MI_Result r;

    // Create client socket.
    r = Sock_Create(s, addr->is_ipv6);
    if (r != MI_RESULT_OK)
    {
        LOGE2((ZT("_CreateSocketAndConnect - Sock_Create returned error: %d (%s)"), (int)r, mistrerror(r)));
        return r;
	}

    r = Sock_SetBlocking(*s, MI_FALSE);
    if (r != MI_RESULT_OK)
    {
        LOGD2((ZT("_CreateConnectorSocket - Sock_SetBlocking returned error: %d (%s)"), (int)r, mistrerror(r)));
        return r;
	}

    r = Sock_Connect(*s, addr);
#ifdef ENABLE_TRACING
    if (r != MI_RESULT_OK)
    {
        LOGD2((ZT("_CreateConnectorSocket - Sock_Connect returned error: %d (%s)"), (int)r, mistrerror(r)));
	}
#endif

    return r;
}

static MI_Result _CreateConnector(
    Sock* s,
    const char* locator)
{
    const char* posColon;

    // This function expects a locator in the form "_host_:_port_", for HTTP connections,
    // or in the form of a file name, for local connections using a socket. In the latter
    // cat, rhe file name is the same of the socket special file. Thus, socket special
    // files used with this code may not contain a colon in their names.

    posColon = strchr(locator, ':');
    if (posColon == NULL)
    {
        return Sock_CreateLocalConnector(s, locator);
	}

    // create a connector to remote address given in the form _host_:_port_
    {
        unsigned short port = (unsigned short)atol(posColon + 1);
        char host[128];
        unsigned int len = (unsigned int)(posColon - locator);
        Addr addr;
        MI_Result r;

        if (len >= sizeof host - 1)
        {
            LOGE2((ZT("_CreateConnector - Host portion of locator is too long: %s"), locator));
            return MI_RESULT_FAILED;
		}

        memcpy(host, locator, len);
        host[len] = '\0';


        // This code tries to connect using the preferred addressing family (IPv4 or IPv6). If that
        // fails and Addr_Init has a secondary addressing family, a connection with the secondary
        // family, it tries using the secondary family next.

        // Initialize preferred address.
        r = Addr_Init(&addr, host, port, MI_FALSE);
        if (r != MI_RESULT_OK)
        {
            LOGD2((ZT("_CreateConnector - Unable to initialize address. host: %s, result: %d (%s)"), host, (int)r, mistrerror(r)));
            return r;
		}

        // Connect to server.
        r = _CreateSocketAndConnect(s, &addr);
        if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
        {
            MI_Result r2;

            Sock_Close(*s);

            // Initialize secondary address.
            r2 = Addr_Init(&addr, host, port, MI_TRUE);
            if (r2 != MI_RESULT_OK)
            {
                return r;               // on error, return original failure
			}
            r2 = _CreateSocketAndConnect(s, &addr);
            if (r2 != MI_RESULT_OK && r2 != MI_RESULT_WOULD_BLOCK)
            {
                Sock_Close(*s);

                return r;               // on error, return original failure
			}
            r = r2;
        }

#ifdef ENABLE_TRACING
        if (r != MI_RESULT_OK)
        {
            LOGD2((ZT("_CreateConnector - Connect failure. host: %s, result: %d (%s)"), host, (int)r, mistrerror(r)));
		}
#endif

        return r;
    }
}

static MI_Result _New_Protocol(
    Protocol** selfOut,
    Selector* selector, /*optional, maybe NULL*/
    ProtocolCallback callback,
    void* callbackData,
    ProtocolEventCallback eventCallback,
    void* eventCallbackData)
{
    Protocol* self;

    /* Check parameters */
    if (selfOut == NULL)
        return MI_RESULT_INVALID_PARAMETER;

    /* Clear output parameter */
    *selfOut = NULL;

    /* Allocate structure */
    {
        self = (Protocol*)calloc(1, sizeof(Protocol));

        if (self == NULL)
            return MI_RESULT_FAILED;
    }

    if (selector != NULL)
    {   /* attach the existing selector */
        self->selector = selector;
        self->internal_selector_used = MI_FALSE;
    }
    else
    {   /* create a new selector */
        MI_Result r;

        /* Initialize the network */
        Sock_Start();

        /* Initialize the selector */
        r = Selector_Init(&self->internal_selector);
        if (r != MI_RESULT_OK)
        {
            free(self);
            return r;
        }
        self->selector = &self->internal_selector;
        self->internal_selector_used = MI_TRUE;
    }

    /* Save the callback and callbackData */
    self->callback = callback;
    self->callbackData = callbackData;
    self->eventCallback = eventCallback;
    self->eventCallbackData = eventCallbackData;

    /* Set the magic number */
    self->magic = _MAGIC;

    /* Set output parameter */
    *selfOut = self;
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Public definitions:
**
**==============================================================================
*/

MI_Result Protocol_New_Listener(
    Protocol** selfOut,
    Selector* selector, /*optional, maybe NULL*/
    const char* locator,
    ProtocolCallback callback,
    void* callbackData)
{
    Protocol* self;
    MI_Result r;
    Sock listener;

    r = _New_Protocol(selfOut, selector, callback, callbackData, NULL, NULL);

    if (MI_RESULT_OK != r)
        return r;

    self = *selfOut;

    self->type = PRT_TYPE_LISTENER;

    /* Create listener socket */
    {
        r = _CreateListener(&listener, locator);

        if (r != MI_RESULT_OK)
        {
            Protocol_Delete(self);
            return r;
        }

        r = Sock_SetBlocking(listener, MI_FALSE);

        if (r != MI_RESULT_OK)
        {
            Sock_Close(listener);
            Protocol_Delete(self);
            return r;
        }
    }

    /* Watch for read events on the listener socket (client connections) */
    {
        Handler* h = (Handler*)calloc(1, sizeof(Handler));

        if (h == NULL)
        {
            Sock_Close(listener);
            Protocol_Delete(self);
            return MI_RESULT_FAILED;
        }

        h->sock = listener;
        h->mask = SELECTOR_READ | SELECTOR_EXCEPTION;
        h->callback = _ListenerCallback;
        h->data = self;

        r = Selector_AddHandler(self->selector, h);

        if (r != MI_RESULT_OK)
        {
            Sock_Close(listener);
            free(h);
            Protocol_Delete(self);
            return r;
        }
    }

    return MI_RESULT_OK;
}

MI_Result Protocol_New_Connector(
    Protocol** selfOut,
    Selector* selector, /*optional, maybe NULL*/
    const char* locator,
    ProtocolCallback callback,
    void* callbackData,
    ProtocolEventCallback eventCallback,
    void* eventCallbackData,
    const char* user,
    const char* password)
{
    Protocol* self;
    MI_Result r;
    Sock connector;

    r = _New_Protocol(selfOut, selector, callback, callbackData, eventCallback, eventCallbackData);

    if (MI_RESULT_OK != r)
    {
        LOGE2((ZT("Protocol_New_Connector - _New_Protocol failed with error: %d (%s)"), r, mistrerror(r)));
        return r;
    }

    self = *selfOut;
    *selfOut = 0;

    self->type = PRT_TYPE_CONNECTOR;

    /* Create connector socket */
    {
        // Connect to server.
        r = _CreateConnector(&connector, locator);
        if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
        {
            LOGE2((ZT("Protocol_New_Connector - _CreateConnector failed with error: %d (%s)"), r, mistrerror(r)));
            Protocol_Delete(self);
            return MI_RESULT_FAILED;
        }
    }

    /* Allocate connector's structure */
    {
        Protocol_SR_SocketData* h = (Protocol_SR_SocketData*)calloc(1, sizeof(Protocol_SR_SocketData));

        if (h == NULL)
        {
            Sock_Close(connector);
            Protocol_Delete(self);
            LOGE2((ZT("Protocol_New_Connector - calloc failed")));
            return MI_RESULT_FAILED;
        }

        h->base.sock = connector;
        h->base.mask = SELECTOR_READ | SELECTOR_WRITE | SELECTOR_EXCEPTION;
        h->base.callback = _RequestCallback;
        h->base.data = self;
        h->sendingQueueLength = -1; /* disable watermarks for client */
        h->isConnector = MI_TRUE;
        h->isConnected = MI_FALSE;
        h->authState = PRT_AUTH_WAIT_CONNECTION_RESPONSE;

        r = Selector_AddHandler(self->selector, &h->base);

        if (r != MI_RESULT_OK)
        {
            Sock_Close(connector);
            Protocol_Delete(self);
            free(h);
            LOGE2((ZT("Protocol_New_Connector - Selector_AddHandler failed with error: %d (%s)"), r, mistrerror(r)));
            return MI_RESULT_FAILED;
        }
        self->connectorHandle = h;

        /* send connect request */
        if (!_SendAuthRequest(h, user, password, NULL))
        {
            /* remove handler will free 'h' pointer */
            Selector_RemoveHandler(self->selector, &h->base);
            Protocol_Delete(self);
            LOGE2((ZT("Protocol_New_Connector - _SendAuthRequest failed")));
            return MI_RESULT_FAILED;
        }
    }

    /* Set output parameter */
    *selfOut = self;
    return MI_RESULT_OK;
}

MI_Result Protocol_New_From_Socket(
    Protocol** selfOut,
    Selector* selector, /*optional, maybe NULL*/
    Sock s,
    MI_Boolean skipInstanceUnpack,
    ProtocolCallback callback,
    void* callbackData,
    ProtocolEventCallback eventCallback,
    void* eventCallbackData)
{
    Protocol* self;
    MI_Result r;

    r = _New_Protocol(selfOut, selector, callback, callbackData,
        eventCallback, eventCallbackData);

    if (MI_RESULT_OK != r)
        return r;

    self = *selfOut;
    *selfOut = 0;

    self->type = PRT_TYPE_FROM_SOCKET;

    self->skipInstanceUnpack = skipInstanceUnpack;

    /* Attach provided socket to connector */
    {
        Protocol_SR_SocketData* h = (Protocol_SR_SocketData*)calloc(1, sizeof(Protocol_SR_SocketData));

        if (h == NULL)
        {
            Protocol_Delete(self);
            return MI_RESULT_FAILED;
        }

        h->base.sock = s;
        h->base.mask = SELECTOR_READ  | SELECTOR_EXCEPTION;

        if (skipInstanceUnpack)
        {
            /* skipInstanceUnpack indicates that call made from server
                and socket connected to the agent
                In that case we can use back=pressure feature and
                ignore socket operations under stress */
            h->base.mask |= SELECTOR_IGNORE_READ_OVERLOAD;
        }

        h->base.callback = _RequestCallback;
        h->base.data = self;
        h->isConnector = MI_TRUE;
        h->isConnected = MI_TRUE;
        /* skip authentication for established connections
            (only used in server/agent communication) */
        h->authState = PRT_AUTH_OK;

        r = Selector_AddHandler(self->selector, &h->base);

        if (r != MI_RESULT_OK)
        {
            Protocol_Delete(self);
            free(h);
            return MI_RESULT_FAILED;
        }
        self->connectorHandle = h;
    }

    /* Set output parameter */
    *selfOut = self;
    return MI_RESULT_OK;
}

MI_Result Protocol_Delete(
    Protocol* self)
{
    /* Check parameters */
    if (self == NULL)
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

    /* if connector, invalide 'self' pointr in connector */
    if (self->connectorHandle)
        self->connectorHandle->base.data = 0;

    /* Clear magic number */
    self->magic = 0xDDDDDDDD;

    /* Free self pointer */
    free(self);


    return MI_RESULT_OK;
}

MI_Result Protocol_Run(
    Protocol* self,
    MI_Sint64 timeoutUsec)
{
    /* Run the selector */
    if (self == NULL || self->selector == NULL)
    {
        LOGE2((ZT("Protocol_Run - NULL argument")));
        return MI_RESULT_INVALID_PARAMETER;
    }

    LOGX2((ZT("Protocol_Run - Calling Selector_Run. selector: %p, timeoutUsec: %ld"), self->selector, (long)timeoutUsec));
    return Selector_Run(self->selector, timeoutUsec);
}

static MI_Result _SendInIOThread(
    void* self_,
    Message* message)
{
    Protocol* self = (Protocol*)self_;
    Protocol_SR_SocketData* sendSock;

    /* check params */
    if (self == NULL || message == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (self->magic != _MAGIC)
    {
        LOGW((ZT("_SendInIOThread: invalid magic number")));
        return MI_RESULT_INVALID_PARAMETER;
    }

    /* find where to send it */
    if (self->connectorHandle != NULL)
    {
        sendSock = self->connectorHandle;
    }
    else
    {
        sendSock = (Protocol_SR_SocketData*)Uint64ToPtr(message->clientID);
    }

    /* validate handler */
    if (sendSock == NULL || sendSock->base.sock == INVALID_SOCK)
    {
        LOGE2((ZT("_SendInIOThread - cannot send message: expired handler. sendSock: %d"), sendSock == NULL ? 0 : (int)sendSock.base.sock));

        /* connection was closed - ignore message, but release handler if needed */
        if (sendSock && Message_IsFinalRepsonse(message))
            _Release(sendSock);

        return MI_RESULT_FAILED;
    }

    /* decrement number of outstanding requests */
    if (Message_IsFinalRepsonse(message) && !sendSock->isConnector)
    {
        DEBUG_ASSERT(sendSock->refcounter > 1);
        _Release(sendSock);
    }

    /* add message to the list */
    List_Append(&sendSock->head, &sendSock->tail, (ListElem*)message);

    if (-1 != sendSock->sendingQueueLength)
        sendSock->sendingQueueLength++;

    Message_AddRef(message);

    _PrepareMessageForSending(sendSock);

    if (!_RequestCallbackWrite(sendSock) && !sendSock->isConnector)
    {
        //LOGW((ZT("cannot send message: queue overflow) %p\n"), sendSock));
        _RemoveAllMessages(sendSock);
        return MI_RESULT_FAILED;
    }

    {
        int counter = 0;

        while (sendSock->sendingQueueLength > SR_SOCKET_OUT_QUEUE_WATERMARK_CRITICAL)
        {
            _RequestCallbackWrite(sendSock);

            counter++;
            /* give system a chance to clear backlog */
            Sleep_ms(1);

            if (counter > 40000)
            {
                LOGW((ZT("_SendInIOThread - Cannot send message: queue overflow. sendSock: %p"), sendSock));
                _RemoveAllMessages(sendSock);
                return MI_RESULT_FAILED;
            }
        }
    }
    return MI_RESULT_OK;
}

/* Signature must not have return type so we created this wrapper */
static void _SendInIOThread_wrapper(void* self, Message* message)
{
    (void)_SendInIOThread(self, message);

    /* ATTN: log failed result? */
}

MI_Result Protocol_Send(
    Protocol* self,
    Message* message)
{
    return Selector_CallInIOThread(self->selector, _SendInIOThread_wrapper, self, message);
}
