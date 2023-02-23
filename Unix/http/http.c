/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
#include <string.h>

#ifdef CONFIG_POSIX
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

#include "http_private.h"

#define FORCE_TRACING 0
#define TIMESTAMP_SIZE 128

#ifndef SSL3_FLAGS_NO_RENEGOTIATE_CIPHERS
# define SSL3_FLAGS_NO_RENEGOTIATE_CIPHERS               0x0001
#endif

#define INVALID_ID ((uid_t)-1)

int GetTimeStamp(_Pre_writable_size_(TIMESTAMP_SIZE) char buf[TIMESTAMP_SIZE]);

//------------------------------------------------------------------------------

STRAND_DEBUGNAME1( HttpSocket, NewRequest )



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
        case (_HashCode('h','t', 4)): /*Host*/
        {
            if (Strcasecmp(name,"Host") == 0)
            {
                handler->recvHeaders.host = value;
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
        else
        {
            SSL_load_error_strings(); // registers the error strings for all libcrypto and libssl functions.
            SSL_get_error(handler->ssl, res);
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
    {
        return Sock_Write(handler->handler.sock, buf, buf_size, sizeWritten);
    }

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

void _WriteTraceFile(PathID id, const void* data, size_t size)
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
            fwrite("\n", 1, 1, out);
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

    if (FORCE_TRACING || (r == MI_RESULT_OK && (*sizeRead>0) && handler->enableTracing))
    {
        char startTime[TIMESTAMP_SIZE]={'\0'};
        GetTimeStamp(startTime);
        _WriteTraceFile(ID_HTTPRECVTRACEFILE, &startTime, strlen(startTime));
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
        char startTime[TIMESTAMP_SIZE]={'\0'};
        GetTimeStamp(startTime);
        _WriteTraceFile(ID_HTTPSENDTRACEFILE, &startTime, strlen(startTime));
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
        SizeTAdd(allocSize, 1, &allocSize) == S_OK &&
        allocSize <= HTTP_ALLOCATION_LIMIT)
    {
        /* Allocate zero-terminated buffer */
        handler->recvPage = (Page*)PAL_Malloc(allocSize);
    }
    else
    {
        // Overflow
        trace_Http_Malloc_Error(allocSize);
        return PRT_RETURN_FALSE;
    }

    if (!handler->recvPage)
        return PRT_RETURN_FALSE;

    memset(handler->recvPage, 0, allocSize);
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


    /* If we are authorised, but the client is sending an auth header, then 
     * we need to tear down all of the auth state and authorise again.
     * NeedsReauthorization does the teardown
     */

    if(handler->recvHeaders.authorization)
    {
        Http_CallbackResult authorized;
        handler->requestIsBeingProcessed = MI_TRUE;

        if (handler->isAuthorised)
        { 
            Deauthorize(handler);
        }

        authorized = IsClientAuthorized(handler);

        if (PRT_RETURN_FALSE == authorized)
        {
            goto Done;
        }
        else if (PRT_CONTINUE == authorized)
        {
            return PRT_CONTINUE;
        }
    }
    else 
    {
        /* Once we are unauthorised we remain unauthorised until the client
           starts the auth process again */

        if (handler->authFailed)
        {
            handler->httpErrorCode = HTTP_ERROR_CODE_UNAUTHORIZED;
            return PRT_RETURN_FALSE;
        }
    }

    if (handler->isAuthorised)
    {
        r = Process_Authorized_Message(handler);
        if (MI_RESULT_OK != r)
        {
            return PRT_RETURN_FALSE;
        }
    }

Done:
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
static const char* _HttpErrorCodeDescription(
    int httpErrorCode, int *pdesclen )
{
    static const char STATUS_OK[] = "OK";
    static const char STATUS_BAD_REQUEST[] = "Bad Request";
    static const char STATUS_UNAUTHORIZED[] = "Unauthorized";
    static const char STATUS_INTERNAL_SERVER_ERROR[] = "Internal Server Error";
    static const char STATUS_UNKNOWN_ERROR[] = "Error";

    switch (httpErrorCode)
    {
    case 200:
        if (pdesclen)
        {
            *pdesclen = MI_COUNT(STATUS_OK)-1;
        }
        return STATUS_OK;

    case 400:
        if (pdesclen)
        {
            *pdesclen = MI_COUNT(STATUS_BAD_REQUEST)-1;
        }
        return STATUS_BAD_REQUEST;

    case 401:
        if (pdesclen)
        {
            *pdesclen = MI_COUNT(STATUS_UNAUTHORIZED)-1;
        }
        return STATUS_UNAUTHORIZED;

    case 500:
        if (pdesclen)
        {
            *pdesclen = MI_COUNT(STATUS_INTERNAL_SERVER_ERROR)-1;
        }
        return STATUS_INTERNAL_SERVER_ERROR;
    }

    if (pdesclen)
    {
        *pdesclen = MI_COUNT(STATUS_UNKNOWN_ERROR)-1;
    }
    return STATUS_UNKNOWN_ERROR;
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

    if (socketData->sendHeader)
    {
        PAL_Free(socketData->sendHeader);
        socketData->sendHeader = 0;
    }

    socketData->httpErrorCode = 0;
    socketData->authFailed     = FALSE;
    socketData->sentSize = 0;
    socketData->sendingState = RECV_STATE_HEADER;
    socketData->handler.mask &= ~SELECTOR_WRITE;
    socketData->handler.mask |= SELECTOR_READ;
}



/*
 * Creates a header, allocating as needed.
 * returns NULL if fault.
 *  
 */

static const char HTTP_PROTOCOL_HEADER[]   = "HTTP/1.1 ";
#define HTTP_PROTOCOL_HEADER_LEN  (MI_COUNT(HTTP_PROTOCOL_HEADER)-1)

static const char CONTENT_LENGTH_HEADER[]     = "Content-Length: ";
#define CONTENT_LENGTH_HEADER_LEN  (MI_COUNT(CONTENT_LENGTH_HEADER)-1)

static const char CONNECTION_HEADER[] = "Connection: ";
#define CONNECTION_HEADER_LEN  (MI_COUNT(CONNECTION_HEADER)-1)

static const char CONTENT_TYPE_HEADER[] = "Content-Type: ";
#define CONTENT_TYPE_HEADER_LEN  (MI_COUNT(CONTENT_TYPE_HEADER)-1)

static Page *
_BuildHeader( Http_SR_SocketData* handler, int contentLen, 
                                          int connectionActionLen, const char *connectionAction,
                                          int contentTypeLen,      const char *contentType)

{

    int  errorcode_strlen = 0;
    char errorcode_buff[16] = {0};
    char *perrorcode = int64_to_a(errorcode_buff, sizeof(errorcode_buff), handler->httpErrorCode, &errorcode_strlen);

    int  errcode_desc_len = 0;
    const char *perrcode_desc = _HttpErrorCodeDescription(handler->httpErrorCode, &errcode_desc_len);
    
    int  content_len_strlen = 0;
	char content_len_buff[16] = { 0 };
    char *pcontent_len = int64_to_a(content_len_buff, sizeof(content_len_buff), contentLen, &content_len_strlen);

    int needed_size = HTTP_PROTOCOL_HEADER_LEN  + errorcode_strlen + 1 + errcode_desc_len + 2 + // HTTP/1.1 0 200 Success\r\n
                      CONTENT_LENGTH_HEADER_LEN + content_len_strlen + 2;                       // Content-Length: 214

    if (connectionAction)
    {
        needed_size += CONNECTION_HEADER_LEN + connectionActionLen + 2;
    }

    if (contentType)
    {
        needed_size += CONTENT_TYPE_HEADER_LEN + contentTypeLen + 2;
    }

    if (handler->pSendAuthHeader)
    {
        needed_size += handler->sendAuthHeaderLen;
    }
    needed_size += 2;  // \r\n
                      
    Page *pHeaderPage = (Page*)PAL_Malloc(sizeof(Page) + needed_size + 1); // 1 for a final null
    if (!pHeaderPage) return NULL;
    char *bufp = (char *)(pHeaderPage+1);

    memset(pHeaderPage, 0, sizeof(Page)); // Zero page header fields.

    // HTTP/1.1 200 Success\r\n
    memcpy(bufp, HTTP_PROTOCOL_HEADER, HTTP_PROTOCOL_HEADER_LEN);
    bufp += HTTP_PROTOCOL_HEADER_LEN;

    if(perrorcode)
    {
        memcpy(bufp, perrorcode, errorcode_strlen);
        bufp += errorcode_strlen;
    }

    *bufp++ = ' ';

    memcpy(bufp, perrcode_desc, errcode_desc_len);
    bufp += errcode_desc_len;
    memcpy(bufp, "\r\n", 2);
    bufp += 2;
 
    // Content-Length: 2035\r\n

    memcpy(bufp, CONTENT_LENGTH_HEADER, CONTENT_LENGTH_HEADER_LEN);
    bufp += CONTENT_LENGTH_HEADER_LEN;

    if(pcontent_len)
    {
        memcpy(bufp, pcontent_len, content_len_strlen);
        bufp += content_len_strlen;
    }

    memcpy(bufp, "\r\n", 2);
    bufp += 2;

    if (connectionAction)
    {
        // Connection: Keep-Alive\r\n
        memcpy(bufp, CONNECTION_HEADER, CONNECTION_HEADER_LEN);
        bufp += CONNECTION_HEADER_LEN;

        memcpy(bufp, connectionAction, connectionActionLen);
        bufp += connectionActionLen;

        memcpy(bufp, "\r\n", 2);
        bufp += 2;
    }
    if (contentType)
    {

        // Content-Type: application/soap+xml;charset=UTF-8\r\n"
        memcpy(bufp, CONTENT_TYPE_HEADER, CONTENT_TYPE_HEADER_LEN);
        bufp += CONTENT_TYPE_HEADER_LEN;

        memcpy(bufp, contentType, contentTypeLen);
        bufp += contentTypeLen;

        memcpy(bufp, "\r\n", 2);
        bufp += 2;
    }

    if (handler->pSendAuthHeader)
    {

        // Kerberos: blah bla blah \r\n
        memcpy(bufp, handler->pSendAuthHeader, handler->sendAuthHeaderLen);
        bufp += handler->sendAuthHeaderLen;

        PAL_Free(handler->pSendAuthHeader);
        handler->pSendAuthHeader   = NULL;
        handler->sendAuthHeaderLen = 0;
    }

    memcpy(bufp, "\r\n", 2);
    bufp += 2;
    *bufp = '\0';

    pHeaderPage->u.s.size = (bufp-((char*)(pHeaderPage+1)));
    DEBUG_ASSERT(strlen((char*)(pHeaderPage+1)) == pHeaderPage->u.s.size);

    return pHeaderPage;
}

static Http_CallbackResult _WriteHeader( Http_SR_SocketData* handler)
{

/*    "SOAPAction: http://schemas.xmlsoap.org/ws/2004/08/addressing/fault\r\n"\ */

    size_t sent;
    MI_Result r;

    /* Do we have any data to send? */
    if (!handler->sendPage && 0 == handler->httpErrorCode)
        return PRT_RETURN_TRUE;

    /* are we done with header? */
    if (handler->sendingState == RECV_STATE_CONTENT)
        return PRT_CONTINUE;

    if (!handler->sendHeader)
    {
        static const char CONNECTION_KEEPALIVE[] = "Keep-Alive";
        static const char CONNECTION_KEEPALIVE_LEN = MI_COUNT(CONNECTION_KEEPALIVE)-1;
    
        static const char CONTENT_TYPE_APPLICATION_SOAP[] = "application/soap+xml;charset=UTF-8";
        static const char CONTENT_TYPE_APPLICATION_SOAP_LEN = MI_COUNT(CONTENT_TYPE_APPLICATION_SOAP)-1;
    
        static const char MULTIPART_ENCRYPTED_SPNEGO[] = "multipart/encrypted;"
                       "protocol=\"application/HTTP-SPNEGO-session-encrypted\";" "boundary=\"Encrypted Boundary\"";

        static const char MULTIPART_ENCRYPTED_KERBEROS[] = "multipart/encrypted;"
                       "protocol=\"application/HTTP-Kerberos-session-encrypted\";" "boundary=\"Encrypted Boundary\"";

        char *content_type    = (char*)CONTENT_TYPE_APPLICATION_SOAP;
        int  content_type_len = CONTENT_TYPE_APPLICATION_SOAP_LEN;
        int  content_len      = 0;
    
        if (handler->sendPage)
        {
            content_len = handler->sendPage->u.s.size;
        }

    #if ENCRYPT_DECRYPT
        if (handler->encryptedTransaction)
        {
            Page *pOldPage = handler->sendPage;

            if (!Http_EncryptData(handler, content_len, content_type_len, content_type, &handler->sendPage) )
            {

                // If we fail it was an error. Not encrypting counts as failure Complain and bail

                trace_HTTP_EncryptionFailed();
                return PRT_RETURN_FALSE;
            }
            else
            {
                if (FORCE_TRACING || handler->enableTracing)
                {
                    char startTime[TIMESTAMP_SIZE]={'\0'};
                    static const char before_encrypt[] = "\n------------ Before Encryption ---------------\n";
                    static const char before_encrypt_end[] = "\n------------ End Before ---------------\n";

                    if (pOldPage && pOldPage != handler->sendPage )
                    {
                        GetTimeStamp(startTime);
                        _WriteTraceFile(ID_HTTPSENDTRACEFILE, &startTime, strlen(startTime));
						_WriteTraceFile(ID_HTTPSENDTRACEFILE, (void *) &before_encrypt, sizeof(before_encrypt));
                        _WriteTraceFile(ID_HTTPSENDTRACEFILE, (char *)(pOldPage+1), pOldPage->u.s.size);
						_WriteTraceFile(ID_HTTPSENDTRACEFILE, (void *) &before_encrypt_end, sizeof(before_encrypt_end));
                    }
                }

                // Can we delete this or is it part of a batch and must be deleted separately?
                if (pOldPage != handler->sendPage)
                {
                    PAL_Free(pOldPage);
                }
            }

            // If it was encrypted,
            content_len = handler->sendPage->u.s.size;
            switch(handler->httpAuthType)
            {
            case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
            case AUTH_METHOD_NEGOTIATE:
                content_type     = (char*)MULTIPART_ENCRYPTED_SPNEGO;
                content_type_len = MI_COUNT(MULTIPART_ENCRYPTED_SPNEGO)-1;
                break;

            case AUTH_METHOD_KERBEROS:
                content_type     = (char*)MULTIPART_ENCRYPTED_KERBEROS;
                content_type_len = MI_COUNT(MULTIPART_ENCRYPTED_KERBEROS)-1;
                break;

            default:
                // We cant actually get here
                trace_Wsman_UnsupportedAuthentication("Unknown");
                return PRT_RETURN_FALSE;
            }
        }
    #endif

        handler->sendHeader = _BuildHeader(handler, content_len,
                                          CONNECTION_KEEPALIVE_LEN, CONNECTION_KEEPALIVE,
                                          content_type_len, content_type);
    }

    sent = 0;

    char *bufp = (char*)(handler->sendHeader+1);
    bufp += handler->sentSize;

    r = _Sock_Write(handler, bufp, handler->sendHeader->u.s.size - handler->sentSize, &sent);

    if ( r == MI_RESULT_OK && 0 == sent )
    {
        return PRT_RETURN_FALSE; /* conection closed */
    }

    if ( r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK )
    {
        return PRT_RETURN_FALSE;
    }

    if (!sent)
    {
        return PRT_RETURN_TRUE;
    }

    handler->sentSize += sent;
    if (handler->sentSize < handler->sendHeader->u.s.size)
    {
        // We didn't send all of the header, so keep sending
        return PRT_RETURN_TRUE;
    }

    // We sent the entire header successfully and can move on to the content
    handler->sentSize = 0;

    PAL_Free(handler->sendHeader);
    handler->sendHeader = NULL;

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

	r = _Sock_Write(handler, (void*)(buf), buf_size, &sent);

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
    MI_UNUSED(sel);

    Http_SR_SocketData* handler = FromOffset( Http_SR_SocketData, handler, handlerIn );

    if ( ((mask & SELECTOR_READ) != 0 && !handler->reverseOperations) ||
        ((mask & SELECTOR_WRITE) != 0 && handler->reverseOperations) )
    {
        if (!_RequestCallbackRead(handler))
        {
            trace_RequestCallbackRead_Failed(ENGINE_TYPE, handler);
            return MI_FALSE;
        }
    }

    if ( ((mask & SELECTOR_WRITE) != 0 && !handler->reverseOperations) ||
        ((mask & SELECTOR_READ) != 0 && handler->reverseOperations) )
    {
        if (!_RequestCallbackWrite(handler))
        {
            trace_RequestCallbackWrite_Failed(ENGINE_TYPE, handler);
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

        HttpAuth_Close(handlerIn);
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

    MI_UNUSED(sel);
    MI_UNUSED(mask);
    MI_UNUSED(currentTimeUsec);

    if (mask & SELECTOR_READ)
    {
        /* Accept the incoming connection */
        r = Sock_Accept(handler->base.sock, &s, &addr);

        if (MI_RESULT_WOULD_BLOCK == r)
            return MI_TRUE;


        if (r != MI_RESULT_OK)
        {
            trace_SockAccept_Failed(ENGINE_TYPE, Sock_GetLastError());
            return MI_TRUE;
        }

        r = Sock_SetBlocking(s, MI_FALSE);
        if (r != MI_RESULT_OK)
        {
            trace_SockSetBlocking_Failed(ENGINE_TYPE);
            HttpAuth_Close(handler_);
            Sock_Close(s);
            return MI_TRUE;
        }

        /* Create handler */
        h = (Http_SR_SocketData*)Strand_New( STRAND_DEBUG( HttpSocket ) &_HttpSocket_FT, sizeof(Http_SR_SocketData), STRAND_FLAG_ENTERSTRAND, NULL );

        if (!h)
        {
            trace_SocketClose_Http_SR_SocketDataAllocFailed();
            HttpAuth_Close(handler_);
            Sock_Close(s);
            return MI_TRUE;
        }

        /* Primary refount -- secondary one is for posting to protocol thread safely */
        h->refcount = 1;
        h->http = self;
        h->pAuthContext  = NULL;
        h->pVerifierCred = NULL;
        h->isAuthorised = FALSE;
        h->authFailed   = FALSE;
        h->encryptedTransaction = FALSE;
        h->pSendAuthHeader = NULL;
        h->sendAuthHeaderLen = 0;
        h->authInfo.uid= INVALID_ID;
        h->authInfo.gid= INVALID_ID;

        h->recvBufferSize = INITIAL_BUFFER_SIZE;
        h->recvBuffer = (char*)PAL_Calloc(1, h->recvBufferSize);
        if (!h->recvBuffer)
        {
            Strand_Delete(&h->strand);
            trace_SocketClose_recvBuffer_AllocFailed();
            HttpAuth_Close(handler_);
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
                HttpAuth_Close(handler_);
                Sock_Close(s);
                return MI_TRUE;
            }

            if (!(SSL_set_fd(h->ssl, s) ))
            {
                trace_SSL_setfd_Failed();
                SSL_free(h->ssl);
                Strand_Delete(&h->strand);
                HttpAuth_Close(handler_);
                Sock_Close(s);
                return MI_TRUE;
            }

#if OPENSSL_VERSION_NUMBER < 0x10100000L
            h->ssl->s3->flags |= SSL3_FLAGS_NO_RENEGOTIATE_CIPHERS;
#endif
        }

        /* Watch for read events on the incoming connection */
        r = Selector_AddHandler(self->selector, &h->handler);

        if (r != MI_RESULT_OK)
        {
            trace_SelectorAddHandler_Failed(ENGINE_TYPE);
            if (handler->secure)
                SSL_free(h->ssl);
            Strand_Delete(&h->strand);
            HttpAuth_Close(handler_);
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

static MI_Result _CreateSSLContext(Http* self, const char* sslCipherSuite, SSL_Options sslOptions)
{
    SSL_CTX *sslContext;

    if (CreateSSLContext(&sslContext, sslOptions) != MI_RESULT_OK)
        return MI_RESULT_FAILED;

    if (sslCipherSuite != NULL)
    {
        // Set the cipher list to the user specified cipher list.
        if (SSL_CTX_set_cipher_list(sslContext, sslCipherSuite) == 0)
        {
            trace_SSL_BadCipherList(scs(sslCipherSuite));
            return MI_RESULT_FAILED;
        }
    }

    /* Check if there is a certificate file (file containing server
    ** certificate) specified. If specified, validate and load the
    ** certificate.
    */
    {
		char errorBuf[256] = { 0 };

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
		char errorBuf[256] = { 0 };

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
        /* Try IPv6 at first */
        trace_Trying_IPv6();
        Addr_InitAnyIPv6(&addr, port);
        r = Sock_CreateListener(&listener, &addr);
        if (r != MI_RESULT_OK)
        {
            /* When IPv6 fail, try IPv4. */
            trace_Trying_IPv4();
            Addr_InitAny(&addr, port);
            r = Sock_CreateListener(&listener, &addr);
        }
        if (r != MI_RESULT_OK)
        {
            trace_Listen_Failed();
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
        if (secure)
        {
            h->base.handlerName = MI_T("HTTPS_SERVER");
        }
        else
        {
            h->base.handlerName = MI_T("HTTP_SERVER");
        }
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
    _In_        SSL_Options         sslOptions,             /* 0 for default options */
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
