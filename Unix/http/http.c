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
#include <ctype.h>
#include "httpcommon.h"
#include <sock/addr.h>
#include <sock/sock.h>
#include <sock/selector.h>
#include <pal/sleep.h>
#include <pal/intsafe.h>
#include <base/buf.h>
#include <base/log.h>
#include <base/result.h>
#include <pal/strings.h>
#include <pal/format.h>
#include <base/paths.h>
#include <base/Strand.h>

#ifdef CONFIG_POSIX
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <pthread.h>
#else
/* ssl not supported in this configuration; just make compiler happy */
typedef void SSL;
typedef void SSL_CTX;
#define SSL_CTX_free(c)
#define SSL_new(c) 0
#define SSL_free(c)
#define SSL_set_fd(c,a) (a==a)
#define SSL_read(c,a,b) 0
#define SSL_write(c,a,b) 0
#define SSL_get_error(c,e) e
#define SSL_ERROR_WANT_WRITE 0
#define SSL_ERROR_WANT_READ 1
#define SSL_ERROR_SYSCALL 2

#ifdef EWOULDBLOCK
# undef EWOULDBLOCK
#endif
#define EWOULDBLOCK 0

#ifdef EINPROGRESS
# undef EINPROGRESS
#endif
#define EINPROGRESS 0

#define ERR_get_error() 0
#define ERR_error_string_n(c,a,b) a[0]=0
#define SSL_accept(c) 0

#endif

#define FORCE_TRACING 0

//------------------------------------------------------------------------------

#define HTTPSOCKET_STRANDAUX_NEWREQUEST 0

STRAND_DEBUGNAME1( HttpSocket, NewRequest );

/*
**==============================================================================
**
** Local definitions:
**
**==============================================================================
*/

static const MI_Uint32 _MAGIC = 0xE0BB5FD3;
static const MI_Uint32 MAX_HEADER_SIZE = 2 * 1024;
static const MI_Uint32 INITIAL_BUFFER_SIZE = 2 * 1024;
static const size_t HTTP_MAX_CONTENT = 1024 * 1024;

struct _Http
{
    MI_Uint32       magic;
    Selector        internalSelector;
    Selector*       selector;
    OpenCallback    callbackOnNewConnection;
    void*           callbackData;
    SSL_CTX*        sslContext;
    /* options: timeouts etc */
    HttpOptions     options;
    MI_Boolean      internalSelectorUsed;
};

typedef struct _Http_Listener_SocketData
{
    /* based member*/
    Handler     base;

    MI_Boolean secure;
}
Http_Listener_SocketData;

typedef enum _Http_RecvState
{
    RECV_STATE_HEADER,
    RECV_STATE_CONTENT
}
Http_RecvState;

typedef struct _Http_SR_SocketData
{
    Strand strand;

    Handler handler;    // Used on selector

    Http* http;

    /* ssl part */
    SSL* ssl;
    MI_Boolean reverseOperations;  /*reverse read/write Events/Handlers*/
    MI_Boolean acceptDone;

    /* is server/provider is processing request
        (to disbale timeout) */
    MI_Boolean requestIsBeingProcessed;

    /* receiving data */
    char* recvBuffer;
    size_t recvBufferSize;
    size_t receivedSize;
    Http_RecvState recvingState;
    HttpHeaders recvHeaders;
    Page* recvPage;
    HttpRequestMsg* request;    // request msg with the request page

    /* sending part */
    Page* sendPage;
    size_t sentSize;
    Http_RecvState sendingState;
    int httpErrorCode;

    /* pending send message */
    Message* savedSendMsg;

    /* Enable tracing */
    MI_Boolean enableTracing;

    volatile ptrdiff_t refcount;
}
Http_SR_SocketData;

/* helper functions result */
typedef enum _Http_CallbackResult
{
    PRT_CONTINUE,
    PRT_RETURN_TRUE,
    PRT_RETURN_FALSE
}
Http_CallbackResult;

void _HttpSocket_Finish( _In_ Strand* self_);

MI_INLINE MI_Uint8 _ToLower(MI_Uint8 x)
{
    return (MI_Uint8)tolower(x);
}

#define _HashCode(first,last,len) ( (((MI_Uint8)first) << 16) | (((MI_Uint8)last) << 8)  | (((MI_Uint16)len)) )

_Return_type_success_(return == MI_TRUE)
static MI_Boolean _getNameValuePair(
    _Inout_ CharPtr* line,
    int fieldSeparator,
    _Out_ CharPtr* value,
    int*  nameHashCode )
{
    int len = 0;
    char* p;
    *value = 0;
    /* find name end /hash-code */

    if ((*line)[0] == 0)
    {
        trace_GetNameValuePair_Failed();
        return MI_FALSE;
    }

    *nameHashCode =  _ToLower((MI_Uint8)(*line)[0])<<16;

    for (len = 1; (*line)[len] && (*line)[len] != fieldSeparator && (*line)[len] != '\r'; len++ )
        ;

    if ((*line)[len] != fieldSeparator)
    {
        trace_GetNameValuePair_Failed();
        return MI_FALSE;
    }

    *nameHashCode |=  (len) | _ToLower((MI_Uint8)(*line)[len-1])<<8;
    (*line)[len] = 0;
    p = *line + len + 1;

    /* skip spaces in value */
    while (p[0] == ' ' || p[0] == '\t')
        p++;

    *value = p;

    /* skip to end of line */
    for ( ; p[0]; )
    {
        if (p[0] == '\r' && p[1] == '\n' &&
            (p[2] != ' ' && p[2] != '\t') )
        {
            p[0] = 0;
            (*line) = p + 2;
            break;
        }
        p ++;
    }

    /* remove trailing spaces */
    p--;
#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26001)
#endif
    /* disabling IPv6 OACR warnings - D3M bug 56 */
    while (p[0] == ' ' || p[0] == '\t')
        p--;
#ifdef _PREFAST_
#pragma prefast (pop)
#endif

    p[1] = 0;

    return MI_TRUE;
}

static MI_Boolean _getHeaderField(
    Http_SR_SocketData* handler,
    _Inout_ CharPtr* line,
    int fieldSeparator)
{
    char* name = *line;
    char* value = NULL;
    int nameHashCode;

    if (!_getNameValuePair(line, fieldSeparator, &value, &nameHashCode))
    {
        trace_GetNameValuePair_Failed();
        return MI_FALSE;
    }


#if defined(CONFIG_ENABLE_HTTPHEADERS)

    /* Inject name-value into HTTP header array */

    if (handler->recvHeaders.headersSize < HTTP_MAX_HEADERS)
    {
        handler->recvHeaders.headers[handler->recvHeaders.headersSize].name =
            name;
        handler->recvHeaders.headers[handler->recvHeaders.headersSize].value =
            value;
        handler->recvHeaders.headersSize++;
    }

#endif /* defined(CONFIG_ENABLE_HTTPHEADERS) */

    /* Convert specified headers to static fields */

    switch (nameHashCode)
    {
        case (_HashCode('c','e',12)): /*Content-Type*/
        {
            if (Strcasecmp(name,"Content-Type") == 0)
                ParseContentType(&handler->recvHeaders, value);

            break;
        }
        case (_HashCode('c','h',14)): /*Content-Length*/
        {
            if (Strcasecmp(name,"Content-Length") == 0)
            {
                handler->recvHeaders.contentLength = (size_t)Strtoull(value,
                    NULL, 10);

                if ( handler->recvHeaders.contentLength > HTTP_MAX_CONTENT )
                {
                    trace_ContentLength_MaxCheck_Failed();
                    return MI_FALSE;
                }
            }
            break;
        }
        case (_HashCode('a','n',13)): /*Authorization*/
        {
            if (Strcasecmp(name,"Authorization") == 0)
            {
                if( !ParseAuthorization(&handler->recvHeaders,value) )
                {
                    return MI_FALSE;
                }
            }
            break;
        }
        case (_HashCode('u','t',10)):
        {
            /* Remember the User-Agent for later use */
            if (Strcasecmp(name, "User-Agent") == 0)
            {
                handler->recvHeaders.userAgent = value;
            }
            break;
        }
        case (_HashCode('p', 't', 4)):
        {
            /* Remember the User-Agent for later use */
            if (Strcasecmp(name, "POST") == 0)
            {
                /* Remove the HTTP version from the uri string*/
                char *tmp = Strchr(value, ' ');
                if (tmp)
                    *tmp = '\0';

                handler->recvHeaders.httpUrl = value;
            }
            break;
        }
        default:
            break;

    }

    return MI_TRUE;
}

static MI_Result _Sock_ReadAux(
    Http_SR_SocketData* handler,
    void* buf,
    size_t buf_size,
    size_t* sizeRead)
{
    int res;

    if (!handler->ssl)
        return Sock_Read(handler->handler.sock, buf, buf_size, sizeRead);

    handler->handler.mask &= ~SELECTOR_WRITE;
    handler->handler.mask |= SELECTOR_READ;
    handler->reverseOperations = MI_FALSE;

    *sizeRead = 0;

    if (handler->acceptDone)
    {
        res = SSL_read(handler->ssl, buf, buf_size);
    }
    else
    {
        res = SSL_accept(handler->ssl);

        if ( res > 0 )
        {
            /* we are done with accpet */
            handler->acceptDone = MI_TRUE;
            return _Sock_ReadAux(handler,buf,buf_size,sizeRead);
        }
        /* perform regular error checking */
    }

    if ( res == 0 )
        return MI_RESULT_OK;    /* connection closed */

    if ( res > 0 )
    {
        *sizeRead = res;
        return MI_RESULT_OK;    /* ok */
    }

    switch (SSL_get_error(handler->ssl, res))
    {
    case SSL_ERROR_WANT_WRITE:
        handler->reverseOperations = MI_TRUE;   /* wait until write is allowed */
        handler->handler.mask |= SELECTOR_WRITE;
        handler->handler.mask &= ~SELECTOR_READ;

        return MI_RESULT_WOULD_BLOCK;

    case SSL_ERROR_WANT_READ:
        return MI_RESULT_WOULD_BLOCK;

    case SSL_ERROR_SYSCALL:
        if (EAGAIN == errno ||
            EWOULDBLOCK == errno ||
            EINPROGRESS == errno)
            return MI_RESULT_WOULD_BLOCK;

        trace_SSLRead_UnexpectedSysError(errno);
        break;

    default:
        {
            /* print error */
            unsigned long err = ERR_get_error();
            while (err)
            {
                char err_txt[200];
                ERR_error_string_n(err, err_txt, sizeof(err_txt));

                trace_SSLRead_Error((int)err, scs(err_txt));
                err = ERR_get_error();
            }
        }
        break;
    }
    return MI_RESULT_FAILED;
}

static MI_Result _Sock_WriteAux(
    Http_SR_SocketData* handler,
    void* buf,
    size_t buf_size,
    size_t* sizeWritten)
{
    int res;

    if (!handler->ssl)
        return Sock_Write(handler->handler.sock, buf, buf_size, sizeWritten);

    /* Do not clear READ flag, since 'close' notification
    delivered as READ event*/
    handler->handler.mask &= ~SELECTOR_READ;
    handler->handler.mask |= SELECTOR_WRITE;
    handler->reverseOperations = MI_FALSE;

    *sizeWritten = 0;
    res = SSL_write(handler->ssl, buf, buf_size);

    if ( res == 0 )
        return MI_RESULT_OK;    /* connection closed */

    if ( res > 0 )
    {
        *sizeWritten = res;
        return MI_RESULT_OK;    /* ok */
    }

    switch (SSL_get_error(handler->ssl, res))
    {
    case SSL_ERROR_WANT_WRITE:
        return MI_RESULT_WOULD_BLOCK;

    case SSL_ERROR_WANT_READ:
        handler->reverseOperations = MI_TRUE;   /* wait until write is allowed */
        handler->handler.mask |= SELECTOR_READ;
        handler->handler.mask &= ~SELECTOR_WRITE;
        return MI_RESULT_WOULD_BLOCK;

    case SSL_ERROR_SYSCALL:
        if (EAGAIN == errno ||
            EWOULDBLOCK == errno ||
            EINPROGRESS == errno)
            return MI_RESULT_WOULD_BLOCK;

        trace_SSLWrite_UnexpectedSysError(errno);
        break;

    default:
        break;
    }
    return MI_RESULT_FAILED;
}

static void _WriteTraceFile(PathID id, void* data, size_t size)
{
#ifdef CONFIG_POSIX
    static pthread_mutex_t s_mutex = PTHREAD_MUTEX_INITIALIZER;
#else
    /* TODO: How to synchronize logging */
#endif
    const char* path;

    if (!(path = OMI_GetPath(id)))
        return;

#ifdef CONFIG_POSIX
    pthread_mutex_lock(&s_mutex);
#else
    /* TODO: How to synchronize logging */
#endif
    {
        FILE* out = fopen(path, "a");

        if (out)
        {
            fwrite(data, 1, size, out);
            fclose(out);
        }
        else
        {
            trace_CannotOpenHttptraceFile(path, errno);
        }
    }
#ifdef CONFIG_POSIX
    pthread_mutex_unlock(&s_mutex);
#else
    /* TODO: How to synchronize logging */
#endif
}

INLINE MI_Result _Sock_Read(
    Http_SR_SocketData* handler,
    void* buf,
    size_t buf_size,
    size_t* sizeRead)
{
    MI_Result r = _Sock_ReadAux(handler, buf, buf_size, sizeRead);

    if (FORCE_TRACING || (r == MI_RESULT_OK && handler->enableTracing))
    {
        _WriteTraceFile(ID_HTTPRECVTRACEFILE, buf, *sizeRead);
    }

    return r;
}

INLINE MI_Result _Sock_Write(
    Http_SR_SocketData* handler,
    void* buf,
    size_t buf_size,
    size_t* sizeWritten)
{
    MI_Result r = _Sock_WriteAux(handler, buf, buf_size, sizeWritten);

    if (FORCE_TRACING || (r == MI_RESULT_OK && handler->enableTracing))
    {
        _WriteTraceFile(ID_HTTPSENDTRACEFILE, buf, *sizeWritten);
    }

    return r;
}

static Http_CallbackResult _ReadHeader(
    Http_SR_SocketData* handler)
{
    char* buf;
    char* currentLine;
    char* data;
    size_t buf_size, received, index;
    MI_Result r;
    MI_Boolean fullHeaderReceived = MI_FALSE;

    /* are we done with header? */
    if (handler->recvingState == RECV_STATE_CONTENT)
        return PRT_CONTINUE;

    buf = handler->recvBuffer + handler->receivedSize;
    buf_size = handler->recvBufferSize - handler->receivedSize;
    received = 0;

    r = _Sock_Read(handler, buf, buf_size, &received);

    if ( r == MI_RESULT_OK && 0 == received )
        return PRT_RETURN_FALSE; /* conection closed */

    if ( r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK )
        return PRT_RETURN_FALSE;

    if (!received)
        return PRT_RETURN_TRUE;

    handler->receivedSize += received;

    /* did we get full header? */
    buf = handler->recvBuffer;
    for ( index = 3; index < handler->receivedSize; index++ )
    {
        if (buf[index-3] == '\r' && buf[index-1] == '\r' &&
            buf[index-2] == '\n' && buf[index] == '\n' )
        {
            fullHeaderReceived = MI_TRUE;
            break;
        }
    }

    if (!fullHeaderReceived )
    {
        if ( handler->receivedSize <  handler->recvBufferSize )
            return PRT_RETURN_TRUE; /* continue reading */

        if ( handler->recvBufferSize < MAX_HEADER_SIZE )
        {
            buf = PAL_Realloc(handler->recvBuffer, handler->recvBufferSize * 2);

            if (!buf)
                return PRT_RETURN_FALSE;

            handler->recvBufferSize *= 2;
            handler->recvBuffer = buf;
            return _ReadHeader(handler);
        }
        else
        {
            /* http header is too big - drop connection */
            trace_HttpHeaderIsTooBig();
            return PRT_RETURN_FALSE;
        }
    }

    /* consume data */
    currentLine = buf;
    data = buf + index + 1; /* pointer to data in case we got some */

    if (!_getHeaderField(handler, &currentLine, ' '))
        return PRT_RETURN_FALSE;


    while ((data-currentLine) > 3)
    {
        if (!_getHeaderField(handler, &currentLine, ':'))
            return PRT_RETURN_FALSE;

    }

    size_t allocSize = 0;
    if (SizeTAdd(sizeof(Page), handler->recvHeaders.contentLength, &allocSize) == S_OK &&
        SizeTAdd(allocSize, 1, &allocSize) == S_OK)
    {
        /* Allocate zero-terminated buffer */
        handler->recvPage = (Page*)PAL_Malloc(allocSize);
    }
    else
    {
        // Overflow
        return PRT_RETURN_FALSE;
    }

    if (!handler->recvPage)
        return PRT_RETURN_FALSE;

    ((char*)(handler->recvPage + 1))[handler->recvHeaders.contentLength] = 0;

    handler->recvPage->u.s.size = (unsigned int)handler->recvHeaders.contentLength;
    handler->recvPage->u.s.next = 0;

    handler->receivedSize -= index + 1;

    /* Verify that we have not more than 'content-length' bytes in buffer left
        If we hvae more, assuming http client is invalid and drop connection */
    if (handler->receivedSize > handler->recvHeaders.contentLength)
    {
        trace_HttpPayloadIsBiggerThanContentLength();
        return PRT_RETURN_FALSE;
    }

    memcpy( handler->recvPage + 1, data, handler->receivedSize );
    handler->recvingState = RECV_STATE_CONTENT;

    return PRT_CONTINUE;
}

static Http_CallbackResult _ReadData(
    Http_SR_SocketData* handler)
{
    char* buf;
    size_t buf_size, received;
    MI_Result r;
    HttpRequestMsg* msg;

    /* are we in the right state? */
    if (handler->recvingState != RECV_STATE_CONTENT)
        return PRT_RETURN_FALSE;

    buf = ((char*)(handler->recvPage + 1)) + handler->receivedSize;
    buf_size = handler->recvHeaders.contentLength - handler->receivedSize;
    received = 0;

    if (buf_size)
    {
        r = _Sock_Read(handler, buf, buf_size, &received);

        if ( r == MI_RESULT_OK && 0 == received )
            return PRT_RETURN_FALSE; /* conection closed */

        if ( r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK )
            return PRT_RETURN_FALSE;

        handler->receivedSize += received;
    }

    /* did we get all data? */

    if ( handler->receivedSize != handler->recvHeaders.contentLength )
        return PRT_RETURN_TRUE;

    msg = HttpRequestMsg_New(handler->recvPage, &handler->recvHeaders);

    if( NULL == msg )
    {
        trace_HTTP_RequestAllocFailed( handler );

        if (handler->recvPage)
        {
            PAL_Free(handler->recvPage);
            handler->recvPage = NULL; /* clearing this out so that caller does not double-free it */
        }

        return PRT_RETURN_FALSE;
    }

    handler->requestIsBeingProcessed = MI_TRUE;

    // the page will be owned by receiver of this message
    DEBUG_ASSERT( NULL == handler->request );
    handler->request = msg;
    Strand_ScheduleAux( &handler->strand, HTTPSOCKET_STRANDAUX_NEWREQUEST );

    handler->recvPage = 0;
    handler->receivedSize = 0;
    memset(&handler->recvHeaders, 0, sizeof(handler->recvHeaders));
    handler->recvingState = RECV_STATE_HEADER;
    return PRT_CONTINUE;
}

static MI_Boolean _RequestCallbackRead(
    Http_SR_SocketData* handler)
{
    switch (_ReadHeader(handler))
    {
    case PRT_CONTINUE: break;
    case PRT_RETURN_TRUE: return MI_TRUE;
    case PRT_RETURN_FALSE: return MI_FALSE;
    }

    switch (_ReadData(handler))
    {
    case PRT_CONTINUE: break;
    case PRT_RETURN_TRUE: return MI_TRUE;
    case PRT_RETURN_FALSE: return MI_FALSE;
    }
    return MI_TRUE;
}

/* length of longest description - has to be updated if descriptions are updated */
#define HTTP_LONGEST_ERROR_DESCRIPTION 50
static const char* _GetHttpErrorCodeDescription(
    int httpErrorCode )
{
    switch (httpErrorCode)
    {
    case 200:
        return "OK";

    case 400:
        return "Bad Request";

    case 401:
        return "Unauthorized";

    case 500:
        return "Internal Server Error";
    }
    return "Error";
}

/*
 * Common clean up function that reverts the changes made when preparing
 * the strand for a write.
 */
static void _ResetWriteState(
    Http_SR_SocketData* socketData )
{
    if (socketData->sendPage)
    {
        PAL_Free(socketData->sendPage);
        socketData->sendPage = 0;
    }
    socketData->httpErrorCode = 0;
    socketData->sentSize = 0;
    socketData->sendingState = RECV_STATE_HEADER;
    socketData->handler.mask &= ~SELECTOR_WRITE;
    socketData->handler.mask |= SELECTOR_READ;
}

static Http_CallbackResult _WriteHeader(
    Http_SR_SocketData* handler)
{
#define RESPONSE_HEADER_FMT \
    "HTTP/1.1 %d %s\r\n"   \
    "Content-Length: %d\r\n"\
    "Connection: Keep-Alive\r\n"\
    "Content-Type: application/soap+xml;charset=UTF-8\r\n"\
    "\r\n"

#define RESPONSE_HEADER_NO_AUTH_FMT "HTTP/1.1 %d %s\r\n\r\n"

#define RESPONSE_HEADER_401_ERROR_FMT \
    "HTTP/1.1 %d %s \r\n" \
    HTTP_WWWAUTHENTICATE_BASIC\
    "\r\n"\
    "Content-Length: 0\r\n"\
    "\r\n"

/*    "SOAPAction: http://schemas.xmlsoap.org/ws/2004/08/addressing/fault\r\n"\ */

    char currentLine[sizeof(RESPONSE_HEADER_FMT) +
        10 /* content length */ +
        10 /*error code*/ +
        HTTP_LONGEST_ERROR_DESCRIPTION /* code descirpiton */ ];
    char* buf;
    size_t buf_size, sent;
    MI_Result r;

    /* Do we have any data to send? */
    if (!handler->sendPage && 0 == handler->httpErrorCode)
        return PRT_RETURN_TRUE;

    /* are we done with header? */
    if (handler->sendingState == RECV_STATE_CONTENT)
        return PRT_CONTINUE;

    if (handler->sendPage)
    {
        buf_size = (size_t)Snprintf(
            currentLine,
            sizeof(currentLine),
            RESPONSE_HEADER_FMT,
            (int)handler->httpErrorCode,
            _GetHttpErrorCodeDescription(handler->httpErrorCode),
            (int)handler->sendPage->u.s.size );
    }
    else
    {
        int httpErrorCode = (int)handler->httpErrorCode;
        /*
        Check the error code and in case it is "HTTP_ERROR_CODE_UNAUTHORIZED" (401), then we need to send the
        "WWW-Authenticate" header field. Since right now we only support "Basic" auth so the header will contains
        "WWW-Authenticate: Basic realm=\"WSMAN\".
        */
        char * response =  (httpErrorCode == HTTP_ERROR_CODE_UNAUTHORIZED) ? RESPONSE_HEADER_401_ERROR_FMT : RESPONSE_HEADER_NO_AUTH_FMT;

        buf_size = (size_t)Snprintf(
            currentLine,
            sizeof(currentLine),
            response,
            httpErrorCode,
            _GetHttpErrorCodeDescription(handler->httpErrorCode));
    }

    buf = currentLine + handler->sentSize;

    sent = 0;

    r = _Sock_Write(handler, buf, buf_size - handler->sentSize, &sent);

    if ( r == MI_RESULT_OK && 0 == sent )
        return PRT_RETURN_FALSE; /* conection closed */

    if ( r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK )
        return PRT_RETURN_FALSE;

    if (!sent)
        return PRT_RETURN_TRUE;

    handler->sentSize += sent;

    if (handler->sentSize < buf_size)
        return PRT_RETURN_TRUE;

    handler->sentSize = 0;
    handler->sendingState = RECV_STATE_CONTENT;
    return PRT_CONTINUE;
}

static Http_CallbackResult _WriteData(
    Http_SR_SocketData* handler)
{
    char* buf;
    size_t buf_size, sent;
    MI_Result r;

    /* are we in the right state? */
    if (handler->sendingState != RECV_STATE_CONTENT)
        return PRT_RETURN_FALSE;

    if (!handler->sendPage)
    {   /* no content*/
        _ResetWriteState( handler );
        return PRT_CONTINUE;
    }

    buf = ((char*)(handler->sendPage + 1)) + handler->sentSize;
    buf_size = handler->sendPage->u.s.size - handler->sentSize;
    sent = 0;

    r = _Sock_Write(handler, buf, buf_size, &sent);

    if ( r == MI_RESULT_OK && 0 == sent )
        return PRT_RETURN_FALSE; /* conection closed */

    if ( r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK )
        return PRT_RETURN_FALSE;

    handler->sentSize += sent;

    /* did we get all data? */

    if ( handler->sentSize != handler->sendPage->u.s.size )
        return PRT_RETURN_TRUE;

    _ResetWriteState( handler );

    return PRT_CONTINUE;
}

static MI_Boolean _RequestCallbackWrite(
    Http_SR_SocketData* handler)
{
    switch (_WriteHeader(handler))
    {
    case PRT_CONTINUE: break;
    case PRT_RETURN_TRUE: return MI_TRUE;
    case PRT_RETURN_FALSE:
        _ResetWriteState( handler );
        return MI_FALSE;
    }

    switch (_WriteData(handler))
    {
    case PRT_CONTINUE: break;
    case PRT_RETURN_TRUE: return MI_TRUE;
    case PRT_RETURN_FALSE:
        _ResetWriteState( handler );
        return MI_FALSE;
    }
    return MI_TRUE;
}

static MI_Boolean _RequestCallback(
    Selector* sel,
    Handler* handlerIn,
    MI_Uint32 mask,
    MI_Uint64 currentTimeUsec)
{
    Http_SR_SocketData* handler = FromOffset( Http_SR_SocketData, handler, handlerIn );
    sel=sel;

    if ( ((mask & SELECTOR_READ) != 0 && !handler->reverseOperations) ||
        ((mask & SELECTOR_WRITE) != 0 && handler->reverseOperations) )
    {
        if (!_RequestCallbackRead(handler))
        {
            trace_RequestCallbackRead_Failed(handler);
            return MI_FALSE;
        }
    }

    if ( ((mask & SELECTOR_WRITE) != 0 && !handler->reverseOperations) ||
        ((mask & SELECTOR_READ) != 0 && handler->reverseOperations) )
    {
        if (!_RequestCallbackWrite(handler))
        {
            trace_RequestCallbackWrite_Failed();
            return MI_FALSE;
        }
    }

    /* re-set timeout - if we performed R/W operation, set timeout depending where we are in communication */
    if (mask & (SELECTOR_READ | SELECTOR_WRITE))
    {
        Http* self = (Http*)handler->handler.data;

        if (handler->requestIsBeingProcessed)
        {
            /* since request is processed by server, disable timeout for this period */
            handler->handler.fireTimeoutAt = TIME_NEVER;
        }
        else
        {
            /* Use configuration timeout */
            handler->handler.fireTimeoutAt = currentTimeUsec + self->options.timeoutUsec;
        }
    }

    /* Close conenction by timeout */
    if (mask & SELECTOR_TIMEOUT)
    {
        trace_ConnectionClosed_Timeout();
        return MI_FALSE;
    }

    if ((mask & SELECTOR_REMOVE) != 0 ||
        (mask & SELECTOR_DESTROY) != 0)
    {
        if (handler->ssl)
            SSL_free(handler->ssl);

        trace_SocketClose_REMOVEDESTROY();

        Sock_Close(handler->handler.sock);

        // Free the savedSendMsg and ACK it to prevent leaks when a non-io thread
        // writes to the socket, but it cannot be read because of an error or a
        // ECONNRESET.
        if (handler->savedSendMsg)
        {
            Message_Release(handler->savedSendMsg);
            handler->savedSendMsg = NULL;
            DEBUG_ASSERT(handler->strand.info.otherAckPending);
            Strand_ScheduleAck( &handler->strand );
        }

        if (handler->recvPage)
            PAL_Free(handler->recvPage);

        if (handler->sendPage)
            PAL_Free(handler->sendPage);

        PAL_Free(handler->recvBuffer);
        // handler deleted on its own strand

        // notify next stack layer
        // (only after internal data has been deleted as this may delete the object)
        Strand_ScheduleClose( &handler->strand );
    }

    return MI_TRUE;
}

/*
**==============================================================================
*/

static void _SendIN_IO_thread_HttpSocket(void* self_, Message* message)
{
    Http_SR_SocketData* sendSock = (Http_SR_SocketData*)self_;
    HttpResponseMsg * response = (HttpResponseMsg *)message;

    DEBUG_ASSERT( sendSock );
    DEBUG_ASSERT( HttpResponseMsgTag == message->tag );

    /* validate handler */

    if (MI_RESULT_OK != Selector_ContainsHandler(
            sendSock->http->selector, &sendSock->handler ) )
    {
        trace_SendIN_IO_thread_HttpSocket_InvalidHandler(sendSock);

        /* The refcount was bumped while transferring, this will lower and
         * delete if necessary */
        _HttpSocket_Finish(&sendSock->strand);
        return;
    }

    sendSock->requestIsBeingProcessed = MI_FALSE;

    sendSock->handler.mask |= SELECTOR_WRITE;
    sendSock->handler.mask &= ~SELECTOR_READ;

    // Now we take ownership of the page
    sendSock->sendPage = response->page;
    response->page = NULL;
    sendSock->httpErrorCode = response->httpErrorCode;

    sendSock->sentSize = 0;
    sendSock->sendingState = RECV_STATE_HEADER;

    // Done after response->page is NULL'd to prevent early release
    // of that memory in the message's destructor
    DEBUG_ASSERT( sendSock->savedSendMsg );
    Message_Release(sendSock->savedSendMsg);
    sendSock->savedSendMsg = NULL;

    if( !_RequestCallbackWrite(sendSock) )
    {
        trace_SendIN_IO_thread_HttpSocket_WriteFailed();
    }

    Strand_ScheduleAck( &sendSock->strand );

    /* The refcount was bumped while transferring, this will lower and delete
     * if necessary */
    _HttpSocket_Finish(&sendSock->strand);
}

void _HttpSocket_Post( _In_ Strand* self_, _In_ Message* msg)
{
    Http_SR_SocketData* self = (Http_SR_SocketData*)self_;
    DEBUG_ASSERT( NULL != self_ );
    trace_HttpSocketPosting(&self->strand.info.interaction, self->strand.info.interaction.other);

    // Preserve the message in case there is an error while writing it to the socket during
    // non-IO thread calls to Selector_CallInIOThread.
    // A ref to the message is held until the message is ACK'd.
    DEBUG_ASSERT( NULL == self->savedSendMsg );
    Message_AddRef(msg);
    self->savedSendMsg = msg;

    /* Bump ref count during duration of transfer */
    Atomic_Inc((ptrdiff_t*) &self->refcount);

    if( MI_RESULT_OK != Selector_CallInIOThread(
        self->http->selector, _SendIN_IO_thread_HttpSocket, self, msg ) )
    {
        // We also need to release the page (if any)
        HttpResponseMsg * response = (HttpResponseMsg *)msg;
        DEBUG_ASSERT( HttpResponseMsgTag == msg->tag );

        trace_HttpSocket_CannotPostMessage( self, msg, &self->strand.info.interaction, self->strand.info.interaction.other );

        HttpResponseMsg_Release( response );  // same message as savedSendMsg
        self->savedSendMsg = NULL;
        Strand_ScheduleAck( &self->strand );
    }
}

void _HttpSocket_PostControl( _In_ Strand* self, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // not used yet
}

void _HttpSocket_Ack( _In_ Strand* self)
{
    trace_HttpSocketAck( &self->info.interaction, self->info.interaction.other );
    // No need to do anything for now
}

void _HttpSocket_Cancel( _In_ Strand* self)
{
    // no need to do anything here (upper layer should send proper error response)
}

void _HttpSocket_Finish( _In_ Strand* self_)
{
    Http_SR_SocketData* self = (Http_SR_SocketData*)self_;
    DEBUG_ASSERT( NULL != self_ );

    if (Atomic_Dec((ptrdiff_t*) &self->refcount) == 0)
    {
        trace_HttpSocketFinish( self_ );
        Strand_Delete( &self->strand );
    }
}

// HTTPSOCKET_STRANDAUX_NEWREQUEST
void _HttpSocket_Aux_NewRequest( _In_ Strand* self_)
{
    Http_SR_SocketData* self = (Http_SR_SocketData*)self_;
    HttpRequestMsg* msg;

    DEBUG_ASSERT( NULL != self_ );
    msg = self->request;
    DEBUG_ASSERT( NULL != msg );

    trace_HttpSocketAuxNewRequest( self, msg );
    self->request = NULL;

    if( !self_->info.thisClosedOther )
    {
        // Leave the strand for the case where the new request provider
        // is in-proc and takes over the thread
        Strand_PostAndLeaveStrand( &self->strand, &msg->base );
    }

    HttpRequestMsg_Release( msg );
}

/*
    Object that implements the HTTP protocol endpoint on a TCP Socket.
    Usually connects to WSMAN interaction object.

    Behaviour:
    - Post tries to schedule the operation on the IO thread (thru selector)
       if that fails it sends the Ack immediately. Note that the response message
       is delivered from WSMAN inside a HttpResponseMsg
    - Post control is not implemented
    - Both Cancel, Close and Ack do nothing (in case of cancelation upper layer should
       send an actual response)
    - Shutdown:
       Once the connection is closed by the client that is notified to _RequestCallback
       which calls Strand_ScheduleClose on component to the right.
       From there normal Strand logic applies: once the upper layer
       also closes the interaction the object is deleted.

    Unique features and special Behavour:
    - When a complete message has been read instead of scheduling a post
       the auxiliary function HTTPSOCKET_STRANDAUX_NEWREQUEST is
       scheduled instead. That function takes care of posting using
       Strand_PostAndLeaveStrand (which avoids holding the strand in case the thread
       is going to be hijacked  by the provider in the processing of that post).
*/
static StrandFT _HttpSocket_FT = {
    _HttpSocket_Post,
    _HttpSocket_PostControl,
    _HttpSocket_Ack,
    _HttpSocket_Cancel,
    NULL,
    _HttpSocket_Finish,
    NULL,
    _HttpSocket_Aux_NewRequest,
    NULL,
    NULL,
    NULL,
    NULL };

/*
**==============================================================================
*/

static MI_Boolean _ListenerCallback(
    Selector* sel,
    Handler* handler_,
    MI_Uint32 mask,
    MI_Uint64 currentTimeUsec)
{
    Http_Listener_SocketData* handler = (Http_Listener_SocketData*)handler_;
    Http* self = (Http*)handler->base.data;
    MI_Result r;
    Sock s;
    Addr addr;
    Http_SR_SocketData* h;

    sel=sel;
    mask=mask;
    currentTimeUsec = currentTimeUsec;

    if (mask & SELECTOR_READ)
    {
        /* Accept the incoming connection */
        r = Sock_Accept(handler->base.sock, &s, &addr);

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
        h = (Http_SR_SocketData*)Strand_New( STRAND_DEBUG( HttpSocket ) &_HttpSocket_FT, sizeof(Http_SR_SocketData), STRAND_FLAG_ENTERSTRAND, NULL );

        if (!h)
        {
            trace_SocketClose_Http_SR_SocketDataAllocFailed();
            Sock_Close(s);
            return MI_TRUE;
        }

        /* Primary refount -- secondary one is for posting to protocol thread safely */
        h->refcount = 1;
        h->http = self;
        h->recvBufferSize = INITIAL_BUFFER_SIZE;
        h->recvBuffer = (char*)PAL_Calloc(1, h->recvBufferSize);
        if (!h->recvBuffer)
        {
            Strand_Delete(&h->strand);
            trace_SocketClose_recvBuffer_AllocFailed();
            Sock_Close(s);
            return MI_TRUE;
        }

        h->handler.sock = s;
        h->handler.mask = SELECTOR_READ | SELECTOR_EXCEPTION;
        h->handler.callback = _RequestCallback;
        h->handler.data = self;
        h->handler.fireTimeoutAt = currentTimeUsec + self->options.timeoutUsec;
        h->enableTracing = self->options.enableTracing;

        /* ssl support */
        if (handler->secure)
        {
            h->ssl = SSL_new(self->sslContext);

            if (!h->ssl)
            {
                trace_SSLNew_Failed();
                Strand_Delete(&h->strand);
                Sock_Close(s);
                return MI_TRUE;
            }

            if (!(SSL_set_fd(h->ssl, s) ))
            {
                trace_SSL_setfd_Failed();
                SSL_free(h->ssl);
                Strand_Delete(&h->strand);
                Sock_Close(s);
                return MI_TRUE;
            }
        }

        /* Watch for read events on the incoming connection */
        r = Selector_AddHandler(self->selector, &h->handler);

        if (r != MI_RESULT_OK)
        {
            trace_SelectorAddHandler_Failed();
            if (handler->secure)
                SSL_free(h->ssl);
            Strand_Delete(&h->strand);
            Sock_Close(s);
            return MI_TRUE;
        }

        // notify next stack layer about new connection
        // (open the interaction)
        Strand_Open(
            &h->strand,
            self->callbackOnNewConnection,
            self->callbackData,
            NULL,
            MI_TRUE );
    }

    if ((mask & SELECTOR_REMOVE) != 0 ||
        (mask & SELECTOR_DESTROY) != 0)
    {
        trace_SocketClose_REMOVEDESTROY();
        Sock_Close(handler->base.sock);
        PAL_Free(handler);
    }

    return MI_TRUE;
}

static MI_Result _New_Http(
    _Out_       Http**              selfOut,
    _In_        Selector*           selector, /*optional, maybe NULL*/
    _In_        OpenCallback        callbackOnNewConnection,
    _In_opt_    void*               callbackData)
{
    Http* self;

    /* Check parameters */
    if (!selfOut)
        return MI_RESULT_INVALID_PARAMETER;

    /* Clear output parameter */
    *selfOut = NULL;

    /* Allocate structure */
    {
        self = (Http*)PAL_Calloc(1, sizeof(Http));

        if (!self)
            return MI_RESULT_FAILED;
    }

    if (selector)
    {   /* attach the exisiting selector */
        self->selector = selector;
        self->internalSelectorUsed = MI_FALSE;
    }
    else
    {   /* creaet a new selector */
        /* Initialize the network */
        Sock_Start();

        /* Initialize the selector */
        if (Selector_Init(&self->internalSelector) != MI_RESULT_OK)
        {
            PAL_Free(self);
            return MI_RESULT_FAILED;
        }
        self->selector = &self->internalSelector;
        self->internalSelectorUsed = MI_TRUE;
    }

    /* Save the callback and callbackData */
    self->callbackOnNewConnection = callbackOnNewConnection;
    self->callbackData = callbackData;

    /* Set the magic number */
    self->magic = _MAGIC;

    /* Set output parameter */
    *selfOut = self;
    return MI_RESULT_OK;
}

#ifdef CONFIG_POSIX
static MI_Boolean _verifyPrivateKey(
    SSL_CTX *ctx,
    const char* keyPath)
{
    // Open the private key file.

    FILE* is = fopen(keyPath, "r");

    if (!is)
    {
        trace_SSL_FailedToOpenPrivateKeyFile(scs(keyPath));
        return MI_FALSE;
    }

    // Read the private key from the input stream.

    EVP_PKEY* pkey;
    pkey = PEM_read_PrivateKey(is, NULL, NULL, NULL);

    if (!pkey)
    {
        trace_SSL_FailedToCreatePrivateKey();
        return MI_FALSE;
    }

    /* Close the input stream. */

    fclose(is);

    /* Associate the new private key with the SSL context object. */

    if (SSL_CTX_use_PrivateKey(ctx, pkey) <= 0)
    {
        EVP_PKEY_free(pkey);
        trace_SSL_NoPrivateKeyFound(scs(keyPath));
        return MI_FALSE;
    }

    EVP_PKEY_free(pkey);

    /* Check private key for validity. */

    if (!SSL_CTX_check_private_key(ctx))
    {
        trace_SSL_PrivateAndPublicKeyDonotMatch();
        return MI_FALSE;
    }

    return MI_TRUE;
}

static MI_Result _CreateSSLContext(Http* self, const char* sslCipherSuite, Server_SSL_Options sslOptions)
{
    SSL_CTX* sslContext = 0;
    long options = 0;

    sslContext = SSL_CTX_new(SSLv23_method());

    if (!sslContext)
    {
        trace_SSL_CannotCreateContext();
        return MI_RESULT_FAILED;
    }

    if (sslCipherSuite != NULL)
    {
        // Set the cipher list to the user specified cipher list.
        if (SSL_CTX_set_cipher_list(sslContext, sslCipherSuite) == 0)
        {
            trace_SSL_BadCipherList(scs(sslCipherSuite));
            return MI_RESULT_FAILED;
        }
    }

    // Disable SSL_v2 and/or SSL_v3 if requested
    if ( sslOptions & DISABLE_SSL_V2 )
    {
        options |= SSL_OP_NO_SSLv2;
    }
    if ( sslOptions & DISABLE_SSL_V3 )
    {
        options |= SSL_OP_NO_SSLv3;
    }
    if ( SSL_CTX_set_options(sslContext, options) == 0 )
    {
        trace_SSL_CannotSetOptions( options );
        return MI_RESULT_FAILED;
    }

    SSL_CTX_set_quiet_shutdown(sslContext, 1);
    SSL_CTX_set_mode(sslContext, SSL_MODE_AUTO_RETRY);
    SSL_CTX_set_mode(sslContext, SSL_MODE_ENABLE_PARTIAL_WRITE);
    SSL_CTX_set_session_cache_mode(sslContext, SSL_SESS_CACHE_OFF);

    /* Check if there is a certificate file (file containing server
    ** certificate) specified. If specified, validate and load the
    ** certificate.
    */
    {
        char errorBuf[256];

        /* load the specified server certificates */
        trace_SSL_LoadingServerCert(scs(OMI_GetPath(ID_PEMFILE)));

        if (SSL_CTX_use_certificate_file(sslContext,
            OMI_GetPath(ID_PEMFILE), SSL_FILETYPE_PEM) <=0)
        {
            trace_SSL_NoServerCertFound(OMI_GetPath(ID_PEMFILE), GetSslErrorString(errorBuf, 256));
            SSL_CTX_free(sslContext);
            return MI_RESULT_FAILED;
        }
    }

    /*
    ** Check if there is a key file (file containing server
    ** private key) specified and the key was not already loaded.
    ** If specified, validate and load the key.
    */
    {
        char errorBuf[256];

        /* load the specified server certificates */
        trace_SSL_LoadingCertPrivateKey(scs(OMI_GetPath(ID_KEYFILE)));

        /* load given private key and check for validity
        */
        if (!_verifyPrivateKey(sslContext, OMI_GetPath(ID_KEYFILE)))
        {
            trace_SSL_NoServerCertFound(scs(OMI_GetPath(ID_KEYFILE)), GetSslErrorString(errorBuf, sizeof errorBuf));
            SSL_CTX_free(sslContext);
            return MI_RESULT_FAILED;
        }
    }

    self->sslContext = sslContext;
    return MI_RESULT_OK;
}
#endif

static MI_Result _CreateAddListenerSocket(
    Http* self,
    unsigned short port,
    MI_Boolean  secure
    )
{
    Addr addr;
    Sock listener;
    MI_Result r;

    /* Create listener socket */
    {
        Addr_InitAny(&addr, port);
        r = Sock_CreateListener(&listener, &addr);

        if (r != MI_RESULT_OK)
        {
            return r;
        }

        r = Sock_SetBlocking(listener, MI_FALSE);

        if (r != MI_RESULT_OK)
        {
            trace_SocketClose_SetBlockingFailed();
            Sock_Close(listener);
            return r;
        }
    }

    /* Watch for read events on the listener socket (client connections) */
    {
        Http_Listener_SocketData* h = (Http_Listener_SocketData*)PAL_Calloc(1, sizeof(Http_Listener_SocketData));

        if (!h)
        {
            trace_SocketClose_Http_Listener_SocketDataAllocFailed();
            Sock_Close(listener);
            return MI_RESULT_FAILED;
        }

        h->base.sock = listener;
        h->base.mask = SELECTOR_READ | SELECTOR_EXCEPTION;
        h->base.callback = _ListenerCallback;
        h->base.data = self;
        h->secure = secure;

        r = Selector_AddHandler(self->selector, &h->base);

        if (r != MI_RESULT_OK)
        {
            trace_SocketClose_Selector_AddHandlerFailed();
            Sock_Close(listener);
            PAL_Free(h);
            return r;
        }
    }

    return MI_RESULT_OK;
}

MI_Result Http_New_Server(
    _Out_       Http**              selfOut,
    _In_        Selector*           selector,               /* optional, maybe NULL*/
    _In_        unsigned short      http_port,              /* 0 to disable */
    _In_        unsigned short      https_port,             /* 0 to disable */
    _In_opt_z_  const char*         sslCipherSuite,         /* NULL to disable */
    _In_        Server_SSL_Options  sslOptions,             /* 0 for default options */
    _In_        OpenCallback        callbackOnNewConnection,
    _In_opt_    void*               callbackData,
    _In_opt_    const HttpOptions*  options)
{
    Http* self;
    MI_Result r;

    /* allocate this, inits selector */
    r = _New_Http(selfOut, selector, callbackOnNewConnection, callbackData);

    if (MI_RESULT_OK != r)
        return r;

    self = *selfOut;

    /* Create http listener socket */
    if (http_port)
    {
        r = _CreateAddListenerSocket(self, http_port, MI_FALSE);

        if (r != MI_RESULT_OK)
        {
            Http_Delete(self);
            return r;
        }
    }

#ifdef CONFIG_POSIX
    /* Create https listener socket */
    if (https_port)
    {
        /* init ssl */
        SSL_library_init();

        /* create context */
        r = _CreateSSLContext(self, sslCipherSuite, sslOptions);

        if (r != MI_RESULT_OK)
        {
            Http_Delete(self);
            return r;
        }

        /* create a socket */
        r = _CreateAddListenerSocket(self, https_port, MI_TRUE);

        if (r != MI_RESULT_OK)
        {
            Http_Delete(self);
            return r;
        }
    }
#else
    MI_UNUSED(https_port);
#endif

    // options
    if( NULL == options )
    {
        HttpOptions tmpOptions = DEFAULT_HTTP_OPTIONS;
        self->options = tmpOptions;
    }
    else
    {
        self->options = *options;
    }

    return MI_RESULT_OK;
}

MI_Result Http_Delete(
    Http* self)
{
    /* Check parameters */
    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

    /* Check magic number */
    if (self->magic != _MAGIC)
        return MI_RESULT_INVALID_PARAMETER;

    if (self->internalSelectorUsed)
    {
        /* Release selector;
        Note: selector-destory closes all sockets in a list including connector and listener */
        Selector_Destroy(self->selector);

        /* Shutdown the network */
        Sock_Stop();
    }

    if (self->sslContext)
        SSL_CTX_free(self->sslContext);

    /* Clear magic number */
    self->magic = 0xDDDDDDDD;

    /* Free self pointer */
    PAL_Free(self);

    return MI_RESULT_OK;
}

MI_Result Http_Run(
    Http* self,
    MI_Uint64 timeoutUsec)
{
    /* Run the selector */
    return Selector_Run(self->selector, timeoutUsec, MI_FALSE);
}
