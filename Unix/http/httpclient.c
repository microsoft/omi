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
#include "httpclient.h"
#include <sock/addr.h>
#include <sock/sock.h>
#include <sock/selector.h>
#include <pal/sleep.h>
#include <base/buf.h>
#include <base/log.h>
#include <base/result.h>
#include <pal/intsafe.h>
#include <pal/strings.h>
#include <pal/format.h>
#include <pal/sleep.h>
#include <base/paths.h>

// #define ENABLE_TRACING 1
#ifdef ENABLE_TRACING
# define TRACING_LEVEL 4
# include <deprecated/logging/logging.h>
#else
# define LOGE2(a)
# define LOGW2(a)
# define LOGD2(a)
# define LOGX2(a)
#endif
#define FORCE_TRACING 1

#ifdef CONFIG_POSIX
#include <openssl/ssl.h>
#include <openssl/err.h>
#else
/* ssl not supported in this configuration; just make compiler happy */
typedef void SSL;
typedef void SSL_CTX;
#define SSL_CTX_free(c)
#define SSL_new(c) 0
#define SSL_free(c)
#define SSL_set_connect_state(c)
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
#define SSL_connect(c) 0

#endif

#include "httpclient_private.h"


MI_INLINE MI_Uint8 _ToLower(MI_Uint8 x)
{
    return (MI_Uint8)tolower(x);
}

#define _HashCode(first,last,len) ( (((MI_Uint8)first) << 16) | (((MI_Uint8)last) << 8)  | (((MI_Uint16)len)) )

_Return_type_success_(return == MI_TRUE)
static MI_Boolean _getNameValuePair(
    _Inout_ CharPtr* line,
    _Out_ CharPtr* value,
    _Out_ int*  nameHashCode)
{
    int len = 0;
    char* p;
    /* find name end /hash-code */

    if ((*line)[0] == '\0')
    {
        return MI_FALSE;
    }

    *nameHashCode =  _ToLower((MI_Uint8)(*line)[0])<<16;

    for (len = 1; (*line)[len] != '\0' && (*line)[len] != ':' && (*line)[len] != '\r'; len++)
        ;

    if ((*line)[len] != ':')
        return MI_FALSE;

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
        if (p[0] != '\0' && p[1] != '\0' && p[2] != '\0' &&
            p[0] == '\r' && p[1] == '\n' &&
            p[2] != ' '  && p[2] != '\t')
        {
            p[0] = '\0';
            (*line) = p + 2;
            break;
        }
        p++;
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

    p[1] = '\0';

    return MI_TRUE;
}

static MI_Boolean _getHeaderField(
    HttpClient_SR_SocketData* handler,
    _Inout_ CharPtr* line)
{
    /* expecting  Request-Line = Method SP Request-URI SP HTTP-Version CRLF
        Read more: http://www.faqs.org/rfcs/rfc2616.html#ixzz0jKdjJdZv
    */
    char* name = *line;
    char* value = NULL;
    int nameHashCode;

    if (!_getNameValuePair(line, &value, &nameHashCode))
        return MI_FALSE;

    if (nameHashCode == _HashCode('c', 'h', 14) && /*Content-Length*/
        Strcasecmp(name,"Content-Length") == 0)
    {
        handler->contentLength = Strtoull(value, NULL, 10);
        /*if (handler->contentLength > HTTP_MAX_CONTENT)
        handler->contentBegin = -1;
        handler->contentEnd = -1;
        handler->contentTotalLength = -1;
        return MI_FALSE;*/
    }
    else if (nameHashCode == _HashCode('t', 'g', 17) && /*Transfer-Encoding*/
        Strcasecmp(name,"Transfer-Encoding") == 0)
    {
        handler->contentLength = -1;
        handler->contentBegin = -1;
        handler->contentEnd = -1;
        handler->contentTotalLength = -1;
    }
    else if (nameHashCode == _HashCode('c','e',13) && /*Content-Range*/
        Strcasecmp(name, "Content-Range") == 0)
    {
        char* delimptr;
        char* endptr;
        handler->contentEnd = -1;
        handler->contentBegin = (MI_Sint64)Strtoull(value, NULL, 10);
        delimptr = strchr(value, '-');
        endptr = strchr(value, '\n');
        if (delimptr != NULL && (endptr == NULL || endptr > delimptr))
            handler->contentEnd = Strtoull(++delimptr, NULL, 10);
        delimptr = strchr(value, '/');
        if (delimptr != NULL && (endptr == NULL || endptr > delimptr))
            handler->contentTotalLength = Strtoull(++delimptr, NULL, 10);
    }
    if (handler->recvHeaders.sizeHeaders < MI_COUNT(handler->recvHeaderFields))
    {
        handler->recvHeaderFields[handler->recvHeaders.sizeHeaders].name = name;
        handler->recvHeaderFields[handler->recvHeaders.sizeHeaders].value = value;
        handler->recvHeaders.sizeHeaders++;
    }
    else
    {
        trace_TooManyHttpHeaders(scs(name), scs(value));
    }

    return MI_TRUE;
}

static MI_Boolean _getChunkSize(
    const char * line,
    MI_Uint32* chunkSize)
{
    *chunkSize = 0;

    while (*line)
    {
        char c = *line;

        if (c >= '0' && c <= '9')
            *chunkSize = *chunkSize * 16 + (c - '0');
        else if (c >= 'a' && c <= 'f')
            *chunkSize = *chunkSize * 16 + (c - 'a' + 10);
        else if (c >= 'A' && c <= 'F')
            *chunkSize = *chunkSize * 16 + (c - 'A' + 10);
        else
            break;

        line++;
    }

    return MI_TRUE;
}


static MI_Boolean _getRequestLine(
    HttpClient_SR_SocketData* handler,
    _Inout_ CharPtr* line)
{
    size_t index;
    /* expecting  Request-Line = Method SP Request-URI SP HTTP-Version CRLF
        Read more: http://www.faqs.org/rfcs/rfc2616.html#ixzz0jKdjJdZv
    */

    /* initialize header */
    handler->recvHeaders.sizeHeaders = 0;
    handler->recvHeaders.headers = handler->recvHeaderFields;

    /* find http code */
    {
        /* skip http version, that is in format
                HTTP-Version   = "HTTP" "/" 1*DIGIT "." 1*DIGIT
                http://www.w3.org/Protocols/rfc2616/rfc2616-sec3.html#sec3.1

                Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF
        */
        const char* s = *line; /*+ HTTP/1.1<sp>*/
        size_t skips = 9;
        for (; skips > 0; s++)
        {
            skips--;
            if (!*s)
            {
                return MI_FALSE;
            }
        }

        handler->recvHeaders.httpError = Strtoul(s, NULL, 10);
    }

    /* skip to end of line */
    for (index = 1; (*line)[index] && index < handler->receivedSize; index++)
    {
        if ((*line)[index-1] == '\r' && (*line)[index] == '\n')
        {
            (*line) = (*line) + index + 1;
            return MI_TRUE;
        }
    }

    return MI_FALSE;
}

static MI_Result _Sock_Read(
    HttpClient_SR_SocketData* handler,
    void* buf,
    size_t buf_size,
    size_t* sizeRead)
{
    int res;
    int sslError;

    if (handler->ssl == NULL)
    {
        MI_Result res = Sock_Read(handler->base.sock, buf, buf_size, sizeRead);

        LOGD2((ZT("_Sock_Read - After regular read. socket: %d, result: %d (%s), bytes read: %u / %u"), handler->base.sock, (int)res, mistrerror(res), (unsigned int)*sizeRead, (unsigned int)buf_size));
        return res;
    }

    handler->base.mask &= ~SELECTOR_WRITE;
    handler->base.mask |= SELECTOR_READ;
    handler->reverseOperations = MI_FALSE;

    *sizeRead = 0;

    res = SSL_read(handler->ssl, buf, buf_size);
    LOGD2((ZT("_Sock_Read - SSL_Read returned: %d (< 0 for error) / %u bytes read, errno: %d (%s)"), res, (unsigned int)buf_size, errno, strerror(errno)));
    if (res == 0)
    {
        LOGW2((ZT("_Sock_Read - SSL socket connection closed. socket: %d"), handler->base.sock));
        return MI_RESULT_OK;    /* connection closed */
    }

    if (res > 0)
    {
        LOGD2((ZT("_Sock_read - Bytes read: %d"), res));
        *sizeRead = res;
        return MI_RESULT_OK;    /* ok */
    }

    sslError = SSL_get_error(handler->ssl, res);
    switch (sslError)
    {
    case SSL_ERROR_WANT_WRITE:
        handler->reverseOperations = MI_TRUE;   /* wait until write is allowed */
        handler->base.mask &= ~SELECTOR_READ;
        handler->base.mask |= SELECTOR_WRITE;
        LOGD2((ZT("_Sock_Read - SSL_read/accept returned WANT_WRITE")));
        return MI_RESULT_WOULD_BLOCK;

    case SSL_ERROR_WANT_READ:
        LOGD2((ZT("Sock_Read - SSL_read/accept returned WANT_READ")));
        return MI_RESULT_WOULD_BLOCK;

    case SSL_ERROR_SYSCALL:
        if (EAGAIN == errno ||
            EWOULDBLOCK == errno ||
            EINPROGRESS == errno)
            return MI_RESULT_WOULD_BLOCK;

        LOGE2((ZT("Sock_Read - SSL_read returned OS error %d (%s)"), errno, strerror(errno)));
        trace_SSLRead_UnexpectedSysError(errno);
        break;

    default:
        /* print Open SSL error stack */
        {
            unsigned long err;
            while ((err = ERR_get_error()) != 0)
            {
                char err_txt[200];

                ERR_error_string_n(err, err_txt, sizeof (err_txt));
                LOGE2((ZT("_Sock_Read - SSL_read returned OpenSSL error: %lu (%s)"), err, err_txt));
            }
        }
        break;
    }
    return MI_RESULT_FAILED;
}

static MI_Result _Sock_Write(
    HttpClient_SR_SocketData* handler,
    void* buf,
    size_t buf_size,
    size_t* sizeWritten)
{
    int res;
    int sslError;

    if (!handler->ssl)
    {
        MI_Result res = Sock_Write(handler->base.sock, buf, buf_size, sizeWritten);
        LOGD2((ZT("_Sock_Write - Non-SSS write. Sock_Write returned %d (%s). %u / %u bytes sent"), res, mistrerror(res), (unsigned int)*sizeWritten, (unsigned int)buf_size));
        return res;
    }

    /* Do not clear READ flag, since 'close' notification
       delivered as READ event */
    handler->base.mask &= ~SELECTOR_READ;
    handler->base.mask |= SELECTOR_WRITE;
    handler->reverseOperations = MI_FALSE;

    *sizeWritten = 0;

    if (handler->connectDone)
    {
        res = SSL_write(handler->ssl, buf, buf_size);
        LOGD2((ZT("_Sock_Write - SSL_write using socket %d returned %d (< 0 for error) / %u bytes written, errno: %d (%s)"), handler->base.sock, res, (unsigned int)buf_size, errno, strerror(errno)));
    }
    else
    {
        res = SSL_connect(handler->ssl);
        LOGD2((ZT("_Sock_Write - SSL connect using socket %d returned result: %d, errno: %d (%s)"), handler->base.sock, res, errno, strerror(errno)));
        if (res > 0)
        {
            /* we are done with accept */
            handler->connectDone = MI_TRUE;
            return _Sock_Write(handler,buf,buf_size,sizeWritten);
        }
        /* perform regular error checking */
    }


    if (res == 0)
    {
        LOGW2((ZT("_Sock_Write - SSL socket connection closed")));
        return MI_RESULT_OK;    /* connection closed */
    }

    if (res > 0)
    {
        *sizeWritten = res;
        LOGD2((ZT("_Sock_Write - SSL socket successful write of %d / %u bytes"), res, (unsigned int)buf_size));
        return MI_RESULT_OK;    /* ok */
    }

    sslError = SSL_get_error(handler->ssl, res);
    switch (sslError)
    {
    case SSL_ERROR_WANT_WRITE:
        LOGD2((ZT("_Sock_Write - SSL_write/connect returned WANT_WRITE")));
        return MI_RESULT_WOULD_BLOCK;

    case SSL_ERROR_WANT_READ:
        LOGD2((ZT("_Sock_Write - SSL_write/connect returned WANT_READ")));
        handler->reverseOperations = MI_TRUE;   /* wait until write is allowed */
        handler->base.mask |= SELECTOR_READ;
        handler->base.mask &= ~SELECTOR_WRITE;
        return MI_RESULT_WOULD_BLOCK;

    case SSL_ERROR_SYSCALL:
        if (EAGAIN == errno ||
            EWOULDBLOCK == errno ||
            EINPROGRESS == errno)
        {
            LOGD2((ZT("_Sock_Write - Returning WOULD_BLOCK. errno: %d (%s)"), errno, strerror(errno)));
            return MI_RESULT_WOULD_BLOCK;
        }

        LOGE2((ZT("_Sock_Write - SSL_write/connect returned unexpected OS error %d (%s)"), errno, strerror(errno)));
        trace_SSLWrite_UnexpectedSysError(errno);
        break;

    case SSL_ERROR_SSL:
        LOGE2((ZT("_Sock_Write - SSL_write/connect returned OpenSSL error %d (%s)"), sslError, ERR_error_string(sslError, NULL)));
        break;

    default:
        LOGD2((ZT("_Sock_Write - SSL_write/connect returned uncategorized OpenSSL error: %d"), res));
        break;
    }

    return MI_RESULT_FAILED;
}

static Http_CallbackResult _ReadHeader(
    HttpClient_SR_SocketData* handler)
{
    char* buf;
    char* currentLine;
    char* data;
    size_t contentSize;
    size_t buf_size, received, index;
    MI_Result r;
    MI_Boolean fullHeaderReceived = MI_FALSE;
    Http_CallbackResult rslt = PRT_CONTINUE;

    /* are we done with header? */
    if (handler->recvingState != RECV_STATE_HEADER)
        return PRT_CONTINUE;

    buf = handler->recvBuffer + handler->receivedSize;
    buf_size = handler->recvBufferSize - handler->receivedSize;
    received = 0;

    r = _Sock_Read(handler, buf, buf_size, &received);
    LOGD2((ZT("_ReadHeader - Begin. _Sock_read result: %d (%s), socket: %d, %u / %u bytes read, reverse: %d"), (int)r, mistrerror(r), (int)handler->base.sock, (unsigned int)received, (unsigned int)buf_size, (int)handler->reverseOperations));

    if (r == MI_RESULT_OK && 0 == received)
    {
        LOGW2((ZT("_ReadHeader - 0 bytes received without error. Socket closed?")));
        return PRT_RETURN_FALSE; /* connection closed */
    }

    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        LOGE2((ZT("_ReadHeader - Error %d (%s)"), r, mistrerror(r)));
        return PRT_RETURN_FALSE;
    }

    if (received == 0)
    {
        LOGD2((ZT("_ReadHeader - 0 bytes received. Waiting...")));
        return PRT_RETURN_TRUE;
    }

    handler->receivedSize += received;

    /* check header */
    LOGD2((ZT("_ReadHeader - Received buffer: %s"), buf));

    /* did we get full header? */
    buf = handler->recvBuffer;
    LOGD2((ZT("_ReadHeader - Checking for full header...")));
    for ( index = 3; index < handler->receivedSize; index++ )
    {
        _Analysis_assume_(handler->recvBufferSize > 3);
        if (buf[index-3] == '\r' && buf[index-1] == '\r' &&
            buf[index-2] == '\n' && buf[index] == '\n' )
        {
            fullHeaderReceived = MI_TRUE;
            LOGD2((ZT("_ReadHeader - Full header has been received")));
            break;
        }
    }

    if (!fullHeaderReceived)
    {
        if (handler->receivedSize <  handler->recvBufferSize)
        {
            LOGD2((ZT("_ReadHeader - Full header not received. Waiting...")));
            return PRT_RETURN_TRUE; /* continue reading */
        }

        if (handler->recvBufferSize < MAX_HEADER_SIZE)
        {
            LOGD2((ZT("_ReadHeader - Reallocating buffer...")));
            buf = PAL_Realloc(handler->recvBuffer, handler->recvBufferSize * 2);

            if (!buf)
            {
                LOGE2((ZT("_ReadHeader - Cannot allocate memory for larger header")));
                return PRT_RETURN_FALSE;
            }

            handler->recvBufferSize *= 2;
            handler->recvBuffer = buf;
            LOGD2((ZT("_ReadHeader - Going recursive...")));
            return _ReadHeader(handler);
        }
        else
        {
            /* Http header is too big - drop connection */
            trace_HttpHeaderIsTooBig();
            LOGE2((ZT("_ReadHeader - HTTP header is too big. Dropping connection")));
            return PRT_RETURN_FALSE;
        }
    }

    /* consume data */
    currentLine = buf;
    data = buf + index + 1; /* pointer to data in case we got some */

    if (!_getRequestLine(handler, &currentLine))
    {
        LOGE2((ZT("_ReadHeader - Cannot find request line in HTTP header")));
        return PRT_RETURN_FALSE;
    }

    while ((data - currentLine) > 3)
    {
        if (!_getHeaderField(handler, &currentLine))
        {
            LOGE2((ZT("_ReadHeader - Cannot find HTTP header field")));
            return PRT_RETURN_FALSE;
        }
    }

    /* Check if we have to deal with chunked-encoded data */
    if (handler->contentLength < 0)
    {
        handler->receivedSize -= index + 1;

        /* Invoke user's callback with header information */
        {
            HttpClient* self = (HttpClient*)handler->base.data;

            if (!(*self->callbackOnResponse)(self, self->callbackData, &handler->recvHeaders,
                handler->contentLength, handler->contentLength == 0, 0))
            {
                LOGD2((ZT("_ReadHeader - On response callback for chunked data header failed")));
                return PRT_RETURN_FALSE;
            }
        }

        /* remove consumed header part */
        memmove(handler->recvBuffer, data, handler->receivedSize);

        handler->recvingState = RECV_STATE_CHUNKHEADER;
        return PRT_CONTINUE;
    }

    contentSize = (size_t)handler->contentLength;
    if (handler->headVerb)
    {
        LOGD2((ZT("_ReadHeader - HEAD response received. Download will contain %u bytes"), (unsigned int)contentSize));
        contentSize = 0;
    }

    size_t allocSize = 0;
    if (SizeTAdd(sizeof(Page), contentSize, &allocSize) == S_OK &&
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

    if (handler->recvPage == NULL)
    {
        LOGD2((ZT("_ReadHeader - Cannot allocate memory for received page")));
        return PRT_RETURN_FALSE;
    }
    ((char*)(handler->recvPage + 1))[contentSize] = '\0';

    handler->recvPage->u.s.size = (unsigned int)contentSize;
    handler->recvPage->u.s.next = 0;
    handler->receivedSize -= index + 1;

    /* Verify that we have not more than 'content-length' bytes in buffer left
        If we have more, assuming http client is invalid and drop connection */
    if (handler->receivedSize > contentSize)
    {
        trace_HttpPayloadIsBiggerThanContentLength();
        LOGE2((ZT("_ReadHeader - HTTP payload is bigger than content-length (%u > %u bytes)"), (unsigned int)handler->receivedSize, (unsigned int)contentSize));
        return PRT_RETURN_FALSE;
    }

    if (handler->receivedSize != 0)
        memcpy(handler->recvPage + 1, data, handler->receivedSize);
    handler->recvingState = RECV_STATE_CONTENT;

    /* Check the authentication. If we need to recycle, send a response to the response. */

    if (!handler->isAuthorized) 
    {
        rslt = HttpClient_IsAuthorized(handler);
    }

    if (handler->isAuthorized && PRT_CONTINUE != rslt) 
    {
        HttpClient* self = (HttpClient*)handler->base.data;

        /* Invoke user's callback with header information of there is no content expected. 
         * Else we will do so when we have read the data */

        if (!(*self->callbackOnResponse)(self, 
                                         self->callbackData,
                                         &handler->recvHeaders,
                                         handler->contentLength,
                                         handler->contentLength == 0, 0))
        {
            LOGE2((ZT("_ReadHeader - On response callback for header failed")));
            return PRT_RETURN_FALSE;
        }
    }

    

    LOGD2((ZT("_ReadHeader - OK exit")));
    return rslt;
}

static Http_CallbackResult _ReadData(
    HttpClient_SR_SocketData* handler)
{
    /* HttpClient* self = (HttpClient*)handler->base.data; */
    char* buf;
    size_t buf_size, received;
    MI_Result r;

    /* are we in the right state? */
    if (handler->recvingState != RECV_STATE_CONTENT)
        return PRT_RETURN_FALSE;

    LOGD2((ZT("_ReadData - Begin. Head? %d"), handler->headVerb));
    if (!handler->headVerb)
    {
        buf = (char*)(handler->recvPage + 1) + handler->receivedSize;
        buf_size = (size_t)(handler->contentLength - handler->receivedSize);
        received = 0;

        if (buf_size != 0)
        {
            r = _Sock_Read(handler, buf, buf_size, &received);
            LOGD2((ZT("_ReadData - _Sock_Read result: %d (%s), socket: %d, recv: %u"), (int)r, mistrerror(r), (int)handler->base.sock, (unsigned int)received));

            if (r == MI_RESULT_OK && 0 == received)
                return PRT_RETURN_FALSE; /* connection closed */

            if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
                return PRT_RETURN_FALSE;

            handler->receivedSize += received;

            LOGD2((ZT("_RequestCallback - Called _ReadData. %d / %d bytes read"), (int)handler->receivedSize, (int)handler->contentLength));

            if (handler->contentLength > 0 && handler->receivedSize < (size_t)handler->contentLength)
            {                           /* assume 500 bytes per millisecond transmission */
                                        /* wait to avoid spinning on _Sock_Read */
                unsigned int bytesLeft = (unsigned int)handler->contentLength - (unsigned int)handler->receivedSize;
                unsigned long msec = (unsigned long)(bytesLeft / 500 + 1);

                Sleep_Milliseconds(msec);
            }
        }

        /* did we get all data? */
        LOGD2((ZT("_ReadData - Received size: %d / %d"), (int)handler->receivedSize, (int)handler->contentLength));
        if (handler->receivedSize != (size_t)handler->contentLength)
            return PRT_RETURN_TRUE;
    }

    if (FORCE_TRACING || (r == MI_RESULT_OK && handler->enableTracing))
    {
        _WriteTraceFile(ID_HTTPRECVTRACEFILE, (char*)(handler->recvPage + 1), handler->receivedSize);
    }

    if (handler->isAuthorized) 
    {
        /* Invoke user's callback with header information */
        HttpClient* self = (HttpClient*)handler->base.data;
        MI_Boolean lastChunk = MI_TRUE;

        if (handler->contentEnd >= 0 &&
            handler->contentEnd + 1 < handler->contentTotalLength)
        {
            lastChunk = MI_FALSE;
        }

        if (!(*self->callbackOnResponse)(self, self->callbackData, &handler->recvHeaders,
            handler->contentLength, lastChunk, &handler->recvPage))
            return PRT_RETURN_FALSE;

        /* status callback */
        handler->status = MI_RESULT_OK;
        (*self->callbackOnStatus)( self, self->callbackData, MI_RESULT_OK, NULL);
    }


    if (handler->recvPage != NULL)
    {
        LOGD2((ZT("_ReadData - Freeing recvPage. socket: %d"), (int)handler->base.sock));
        PAL_Free(handler->recvPage);
    }

    
    handler->recvPage = NULL;
    handler->receivedSize = 0;
    memset(&handler->recvHeaders, 0, sizeof(handler->recvHeaders));
    handler->recvingState = RECV_STATE_HEADER;
    LOGD2((ZT("_ReadData - OK exit")));
    return PRT_CONTINUE;
}

static Http_CallbackResult _ReadChunkHeader(
    HttpClient_SR_SocketData* handler)
{
    char* buf;
    char* currentLine;
    char* data;
    size_t buf_size, received, index;
    MI_Result r;
    MI_Boolean fullHeaderReceived = MI_FALSE;
    MI_Uint32   chunkSize = 0;
    MI_Boolean connectionClosed = MI_FALSE;

    /* are we done with header? */
    if (handler->recvingState != RECV_STATE_CHUNKHEADER)
        return PRT_CONTINUE;

    buf = handler->recvBuffer + handler->receivedSize;
    buf_size = handler->recvBufferSize - handler->receivedSize;
    received = 0;

    r = _Sock_Read(handler, buf, buf_size, &received);

    if (r == MI_RESULT_OK && 0 == received)
    {
        if (!handler->recvBufferSize)
            return PRT_RETURN_FALSE; /* connection closed */

        connectionClosed = MI_TRUE;
    }

    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
        return PRT_RETURN_FALSE;

    if (!received && !handler->recvBufferSize)
        return PRT_RETURN_TRUE;

    handler->receivedSize += received;

    /* did we get full header? */
    buf = handler->recvBuffer;

    _Analysis_assume_(handler->recvBufferSize > 2);
    for (index = 1; index < handler->receivedSize && buf[index]; index++)
    {
        if (buf[index-1] == '\r' && buf[index] == '\n' )
        {
            fullHeaderReceived = MI_TRUE;
            break;
        }
    }

    if (!fullHeaderReceived)
    {
        if (connectionClosed)
            return PRT_RETURN_FALSE; /* connection closed */

        if (handler->receivedSize <  handler->recvBufferSize)
            return PRT_RETURN_TRUE; /* continue reading */

        if (handler->recvBufferSize < MAX_HEADER_SIZE)
        {
            buf = PAL_Realloc(handler->recvBuffer, handler->recvBufferSize * 2);

            if (!buf)
                return PRT_RETURN_FALSE;

            handler->recvBufferSize *= 2;
            handler->recvBuffer = buf;
            return _ReadChunkHeader(handler);
        }
        else
        {
            /* http chunk header is too big - drop connection */
            trace_HttpChunkHeaderIsTooBig();
            return PRT_RETURN_FALSE;
        }
    }

    /* consume data */
    currentLine = buf;
    data = buf + index + 1; /* pointer to data in case we got some */

    if (!_getChunkSize(currentLine, &chunkSize))
        return PRT_RETURN_FALSE;

    if (0 == chunkSize)
    {
        /* last chunk received */

        /* Invoke user's callback with header information */
        {
            HttpClient* self = (HttpClient*)handler->base.data;

            if (!(*self->callbackOnResponse)( self, self->callbackData, 0,
                handler->contentLength, MI_TRUE, 0))
                return PRT_RETURN_FALSE;

            /* status callback */
            handler->status = MI_RESULT_OK;
            (*self->callbackOnStatus)(
                self,
                self->callbackData,
                MI_RESULT_OK, NULL);
        }

        /* clean up state */
        handler->recvPage = 0;
        handler->receivedSize = 0;
        memset(&handler->recvHeaders, 0, sizeof(handler->recvHeaders));
        handler->recvingState = RECV_STATE_HEADER;

        if (connectionClosed)
            return PRT_RETURN_FALSE; /* connection closed */

        return PRT_CONTINUE;
    }

    size_t allocSize = 0;
    if (SizeTAdd(sizeof(Page), (size_t)chunkSize, &allocSize) == S_OK &&
        SizeTAdd(allocSize, 2 /*CR-LF*/ + 1 /* \0 */, &allocSize) == S_OK)
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

    ((char*)(handler->recvPage + 1))[chunkSize+2] = 0;

    handler->recvPage->u.s.size = (unsigned int)chunkSize;
    handler->recvPage->u.s.next = 0;

    /* subtract header size */
    handler->receivedSize -= index + 1;

    /* in case of small chunks we may receive more than one chunk already */
    if (handler->receivedSize > (size_t)(chunkSize+2))
    {
        /* copy page size to page */
        memcpy(handler->recvPage + 1, data, chunkSize+2);

        /* notify user */
        {
            HttpClient* self = (HttpClient*)handler->base.data;

            if (!(*self->callbackOnResponse)( self, self->callbackData, 0,
                handler->contentLength, MI_FALSE, &handler->recvPage))
                return PRT_RETURN_FALSE;

            if (handler->recvPage)
                PAL_Free(handler->recvPage);

            handler->recvPage = 0;
        }

        /* remove consumed part */
        memmove(handler->recvBuffer, data + chunkSize+2, handler->receivedSize - (chunkSize+2));
        handler->receivedSize -= (chunkSize+2);

        /* consume next chunk */
        return _ReadChunkHeader(handler);
    }

    memcpy(handler->recvPage + 1, data, handler->receivedSize);
    handler->recvingState = RECV_STATE_CHUNKDATA;

    if (connectionClosed)
        return PRT_RETURN_FALSE; /* connection closed */

    return PRT_CONTINUE;
}
static Http_CallbackResult _ReadChunkData(
    HttpClient_SR_SocketData* handler)
{
    //HttpClient* self = (HttpClient*)handler->base.data;
    char* buf;
    size_t buf_size, received;
    MI_Result r;

    /* are we in the right state? */
    if (handler->recvingState != RECV_STATE_CHUNKDATA)
        return PRT_RETURN_FALSE;

    buf = ((char*)(handler->recvPage + 1)) + handler->receivedSize;
    buf_size = (size_t)(handler->recvPage->u.s.size + 2 /* CR-LF */ - handler->receivedSize);
    received = 0;

    if (buf_size)
    {
        r = _Sock_Read(handler, buf, buf_size, &received);

        if (r == MI_RESULT_OK && 0 == received)
            return PRT_RETURN_FALSE; /* connection closed */

        if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
            return PRT_RETURN_FALSE;

        handler->receivedSize += received;
    }

    if (handler->receivedSize != (size_t)(handler->recvPage->u.s.size + 2 /* CR-LF */))
        return PRT_RETURN_TRUE;

    /* Invoke user's callback with header information */
    {
        HttpClient* self = (HttpClient*)handler->base.data;

        if (!(*self->callbackOnResponse)( self, self->callbackData, 0,
            handler->contentLength, MI_FALSE, &handler->recvPage))
            return PRT_RETURN_FALSE;

    }

    if (handler->recvPage)
        PAL_Free(handler->recvPage);

    handler->recvPage = 0;
    handler->receivedSize = 0;
    memset(&handler->recvHeaders, 0, sizeof(handler->recvHeaders));
    handler->recvingState = RECV_STATE_CHUNKHEADER;
    return PRT_CONTINUE;
}

Http_CallbackResult _WriteClientHeader(
    HttpClient_SR_SocketData* handler)
{
    char* buf;
    size_t buf_size, sent;
    MI_Result r;

    /* Do we have any data to send? */
    if (!handler->sendHeader)
        return PRT_RETURN_TRUE;

    /* are we done with header? */
    if (handler->sendingState == RECV_STATE_CONTENT)
        return PRT_CONTINUE;

    LOGD2((ZT("_WriteHeader - Begin")));

    buf = ((char*)(handler->sendHeader + 1)) + handler->sentSize;
    buf_size = handler->sendHeader->u.s.size - handler->sentSize;
    sent = 0;

    r = _Sock_Write(handler, buf, buf_size, &sent);
    LOGD2((ZT("_WriteHeader - _Sock_Write result: %d (%s), socket: %d, sent: %d"), (int)r, mistrerror(r), (int)handler->base.sock, (int)sent));

    if (r == MI_RESULT_OK && 0 == sent)
    {
        LOGE2((ZT("_WriteHeader - Connection closed")));
        return PRT_RETURN_FALSE; /* connection closed */
    }

    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        LOGE2((ZT("_WriteHeader - _Sock_Write returned error: %d (%s)"), (int)r, mistrerror(r)));
        return PRT_RETURN_FALSE;
    }

    handler->sentSize += sent;
    handler->headVerb = buf_size > 4 && Strncasecmp(buf, "HEAD", 4) == 0;

    /* did we send all data? */
    if (handler->sentSize != handler->sendHeader->u.s.size)
    {
        LOGD2((ZT("_WriteHeader - Partial write. %u sent this time, %u / %d written, result: %d (%s)"), (unsigned int)sent, (unsigned int)handler->sentSize, (unsigned int)handler->sendHeader->u.s.size, r, mistrerror(r)));
        return PRT_RETURN_TRUE;
    }

    PAL_Free(handler->sendHeader);
    handler->sendHeader = 0;
    handler->sentSize = 0;
    handler->sendingState = RECV_STATE_CONTENT;

    LOGD2((ZT("_WriteHeader - OK exit")));
    return PRT_CONTINUE;
}

Http_CallbackResult _WriteClientData(
    HttpClient_SR_SocketData* handler)
{
    char* buf;
    size_t buf_size, sent;
    MI_Result r;

    LOGD2((ZT("_WriteClientData - Begin")));
    /* are we in the right state? */
    if (handler->sendingState != RECV_STATE_CONTENT)
    {
        LOGE2((ZT("_WriteClientData - Wrong state. state: %d"), handler->sendingState));
        return PRT_RETURN_FALSE;
    }

    if (!handler->sendPage)
    {   /* no content*/
        handler->sentSize = 0;
        handler->sendingState = RECV_STATE_HEADER;
        handler->base.mask &= ~SELECTOR_WRITE;
        handler->base.mask |= SELECTOR_READ;

        LOGW2((ZT("_WriteClientData - Content is empty. Continuing")));
        return PRT_CONTINUE;
    }

    buf = ((char*)(handler->sendPage + 1)) + handler->sentSize;
    buf_size = handler->sendPage->u.s.size - handler->sentSize;
    sent = 0;

    r = _Sock_Write(handler, buf, buf_size, &sent);
    LOGD2((ZT("_WriteClientData - HTTPClient sent %u / %u bytes with result %d (%s)"), (unsigned int)sent, (unsigned int)buf_size, (int)r, mistrerror(r)));

    if (r == MI_RESULT_OK && 0 == sent)
    {
        LOGE2((ZT("_WriteClientData exit. Connection closed")));
        return PRT_RETURN_FALSE; /* connection closed */
    }

    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        LOGE2((ZT("_WriteClientData exit - Error: %d (%s)"), r, mistrerror(r)));
        return PRT_RETURN_FALSE;
    }

    handler->sentSize += sent;

    /* did we send all data? */

    if (handler->sentSize != handler->sendPage->u.s.size)
    {
        LOGD2((ZT("_WriteClientData - Exit. Partial write. %u / %u bytes written"), (unsigned int)handler->sentSize, (unsigned int)handler->sendPage->u.s.size));
        return PRT_RETURN_TRUE;
    }

    if (FORCE_TRACING || (r == MI_RESULT_OK && handler->enableTracing))
    {
        _WriteTraceFile(ID_HTTPSENDTRACEFILE, (char*)(handler->sendPage + 1), handler->sentSize);
    }


    LOGD2((ZT("_WriteClientData - %u / %u bytes sent"), (unsigned int)handler->sentSize, (unsigned int)handler->sendPage->u.s.size));
    PAL_Free(handler->sendPage);
    handler->sendPage = NULL;
    handler->sentSize = 0;
    handler->sendingState = RECV_STATE_HEADER;
    handler->base.mask &= ~SELECTOR_WRITE;
    handler->base.mask |= SELECTOR_READ;

    LOGD2((ZT("_WriteClientData - OK exit. returning: %d"), PRT_CONTINUE));

    return PRT_CONTINUE;
}

static MI_Boolean _RequestCallbackRead(
    HttpClient_SR_SocketData* handler)
{
    switch (_ReadHeader(handler))
    {
    case PRT_CONTINUE: break;
    case PRT_RETURN_TRUE: return MI_TRUE;
    case PRT_RETURN_FALSE: return MI_FALSE;
    }

    if (handler->recvingState == RECV_STATE_CONTENT)
    {
        switch (_ReadData(handler))
        {
        case PRT_CONTINUE: break;
        case PRT_RETURN_TRUE: return MI_TRUE;
        case PRT_RETURN_FALSE: return MI_FALSE;
        }
    }

    if (handler->recvingState == RECV_STATE_CHUNKHEADER)
    {
        switch (_ReadChunkHeader(handler))
        {
        case PRT_CONTINUE: break;
        case PRT_RETURN_TRUE: return MI_TRUE;
        case PRT_RETURN_FALSE: return MI_FALSE;
        }
    }
    if (handler->recvingState == RECV_STATE_CHUNKDATA)
    {
        switch (_ReadChunkData(handler))
        {
        case PRT_CONTINUE: break;
        case PRT_RETURN_TRUE: return MI_TRUE;
        case PRT_RETURN_FALSE: return MI_FALSE;
        }
    }

    return MI_TRUE;
}

static MI_Boolean _RequestCallbackWrite(
    HttpClient_SR_SocketData* handler)
{
    switch (_WriteClientHeader(handler))
    {
    case PRT_CONTINUE: break;
    case PRT_RETURN_TRUE: return MI_TRUE;
    case PRT_RETURN_FALSE: return MI_FALSE;
    }

    switch (_WriteClientData(handler))
    {
    case PRT_CONTINUE: break;
    case PRT_RETURN_TRUE: return MI_TRUE;
    case PRT_RETURN_FALSE: return MI_FALSE;
    }
    return MI_TRUE;
}


static MI_Boolean _RequestCallback(
    Selector* sel,
    Handler* handlerIn,
    MI_Uint32 mask,
    MI_Uint64 currentTimeUsec)
{
    HttpClient_SR_SocketData* handler = (HttpClient_SR_SocketData*)handlerIn;
    HttpClient* self = (HttpClient*)handler->base.data;
    MI_UNUSED(sel);

    if (((mask & SELECTOR_READ) != 0 && !handler->reverseOperations) ||
        ((mask & SELECTOR_WRITE) != 0 && handler->reverseOperations))
    {
        if (!_RequestCallbackRead(handler))
        {
            LOGE2((ZT("_RequestCallback - RequestCallbackRead failed")));
            return MI_FALSE;
        }
        LOGD2((ZT("_RequestCallback - Called _RequestCallbackRead. %u / %u bytes read"), (unsigned int)handler->receivedSize, handler->recvPage == NULL ? 0 : (unsigned int)handler->recvPage->u.s.size));
    }

    if (((mask & SELECTOR_WRITE) != 0 && !handler->reverseOperations) ||
        ((mask & SELECTOR_READ) != 0 && handler->reverseOperations))
    {
        if (self->callbackOnConnect && (handler->sendingState == RECV_STATE_CONNECT))
        {

            /* We are taking over the first write as a notification that the
             * connection completed properly. Notify the caller of the fact if
             * there is a callback
             */
            HttpClientCallbackOnConnect onConnect = self->callbackOnConnect;
            self->callbackOnConnect = NULL;
            handler->sendingState = RECV_STATE_HEADER;

            trace_RequestCallback_Connect_OnFirstRead(handler);

            onConnect(self, self->callbackData);
        }
        else
        {
            if (!_RequestCallbackWrite(handler))
            {
                LOGE2((ZT("_RequestCallback - _RequestCallbackWrite failed")));
                return MI_FALSE;
            }
            LOGD2((ZT("_RequestCallback - Called _RequestCallbackWrite. %u / %u bytes sent"), (unsigned int)handler->sentSize, handler->sendPage == NULL ? 0 : (unsigned int)handler->sendPage->u.s.size));
            while (handler->sendPage != NULL && handler->sentSize < handler->sendPage->u.s.size)
            {                               /* assume 500 bytes per millisecond transmission */
                                            /* wait after to avoid spinning too much on _WriteClientData */
                unsigned int bytesLeft = (unsigned int)handler->sendPage->u.s.size - (unsigned int)handler->sentSize;
                unsigned long msec = (unsigned long)(bytesLeft / 500 + 1);

                LOGD2((ZT("_RequestCallback - Called _WriteClientData. %u / %u bytes sent"), (unsigned int)handler->sentSize, handler->sendPage == NULL ? 0 : (unsigned int)handler->sendPage->u.s.size));
                if (_WriteClientData(handler) == MI_FALSE)
                {
                    LOGE2((ZT("_RequestCallback - _WriteClientData failed")));
                    return MI_FALSE;
                }
                LOGD2((ZT("_RequestCallback - Called _WriteClientData. %u bytes written, %u bytes left"), (unsigned int)handler->sentSize, handler->sendPage == NULL ? 0 : (unsigned int)handler->sendPage->u.s.size));
                Sleep_Milliseconds(msec);
            }
            LOGD2((ZT("_RequestCallback - Called _RequestCallbackWrite. %u / %u bytes sent"), (unsigned int)handler->sentSize, handler->sendPage == NULL ? 0 : (unsigned int)handler->sendPage->u.s.size));
        }
    }

    /* re-set timeout - if we performed R/W operation, set timeout depending where we are in communication */
    if (mask & (SELECTOR_READ | SELECTOR_WRITE))
    {
        handler->base.fireTimeoutAt = currentTimeUsec + handler->timeoutUsec;
    }

    /* Close connection by timeout */
    if ((mask & SELECTOR_TIMEOUT) != 0)
    {
        if (handler->status != MI_RESULT_OK)
        {
            handler->recvHeaders.httpError = 408;
            handler->status = MI_RESULT_TIME_OUT;
        }
        LOGE2((ZT("_RequestCallback - Timed out. socket: %d, result: %d (%s)"), handler->base.sock, handler->status, mistrerror(handler->status)));
        return MI_FALSE;
    }

    if ((mask & SELECTOR_REMOVE) != 0 || (mask & SELECTOR_DESTROY) != 0)
    {
        HttpClient* self = (HttpClient*)handler->base.data;

        /* notify next stack layer */
        if (handler->status != MI_RESULT_OK)
            (*self->callbackOnStatus)(self, self->callbackData, handler->status, NULL);

        /* Yeah, this is hokey, but we need to sleep here to let the */
                /* subsystems have the opportunity to send the data before we close */
                /* the socket, or we'll get a broken pipe/connection reset */
#if defined(CONFIG_OS_WINDOWS)
        Sleep_Milliseconds(1);
#else
        usleep(50);
#endif

        if (handler == NULL)
        {
            LOGE2((ZT("_RequestCallback - The handler object was free'd under us!")));
            return MI_TRUE;
        }

        if (self->connector)
        {
            if (self->connector->username)
            {
                PAL_Free(self->connector->username);
                self->connector->username = NULL;
            }
        
            if (self->connector->password)
            {
                PAL_Free(self->connector->password);
                self->connector->password = NULL;
            }

            self->connector = NULL;
        }

        if (handler->ssl)
            SSL_free(handler->ssl);

        Sock_Close(handler->base.sock);

        if (handler->recvPage)
            PAL_Free(handler->recvPage);

        if (handler->sendPage)
            PAL_Free(handler->sendPage);

        if (handler->sendHeader)
            PAL_Free(handler->sendHeader);

        PAL_Free(handler->recvBuffer);
        PAL_Free(handler);
    }

    return MI_TRUE;
}

#ifdef CONFIG_POSIX

/*
 Verify callback when the server authentication certificate's chain of trust is checked. This
 is the same as the Open SSL verify callback function (return preverify_ok), except that it
 logs a diagnostic message when preverify_ok has a failed status.
*/
static int _ctxVerify(
    int preverify_ok,
    X509_STORE_CTX* ctx)
{
    if (preverify_ok <= 0)
    {
        X509* certWithError = X509_STORE_CTX_get_current_cert(ctx);
        int error = X509_STORE_CTX_get_error(ctx);
        char nameBuf[256];

        X509_NAME_oneline(X509_get_subject_name(certWithError), nameBuf, 256);
        trace_SSL_VerifyFailed(error, nameBuf);
    }
    return preverify_ok;
}

/*
 Create an Open SSL context that will be used for secure communication. Set up server and client
 certificate authentication if specified.
*/
static MI_Result _CreateSSLContext(
    HttpClient* self,
    const char* trustedCertsDir,
    const char* certFile,
    const char* privateKeyFile)
{
    SSL_CTX* sslContext = SSL_CTX_new(SSLv23_method());
    if (sslContext == NULL)
    {
        LOGE2((ZT("_CreateSSLContext - Cannot create SSL context")));
        trace_SSL_CannotCreateContext();
        return MI_RESULT_FAILED;
    }
    SSL_CTX_set_quiet_shutdown(sslContext, 1);
    (void)SSL_CTX_set_mode(sslContext, SSL_MODE_AUTO_RETRY | SSL_MODE_ENABLE_PARTIAL_WRITE);
    SSL_CTX_set_session_cache_mode(sslContext, SSL_SESS_CACHE_OFF);
    SSL_CTX_sess_set_remove_cb(sslContext, NULL);

    if (trustedCertsDir != NULL)
    {
        /* Cause Open SSL to check the server certificate Subject against its FQDN and
        ** to check the server certificate chain against the contents of *trustedCertsDir.
        */
        if (SSL_CTX_load_verify_locations(sslContext, NULL, trustedCertsDir) < 0)
        {
            LOGE2((ZT("_CreateSSLContext - Cannot set directory containing trusted certificate(s) to %s"), trustedCertsDir));
            trace_SSL_BadTrustDir(trustedCertsDir);
        }
        SSL_CTX_set_verify(sslContext, SSL_VERIFY_PEER, _ctxVerify);
    }

    /* Check if there is a client certificate file (file containing client authentication
    ** certificate) specified. If specified, validate and load the certificate.
    */
    if (certFile != NULL && *certFile != '\0')
    {
        int err;

        /* load the specified client certificates */
        LOGD2((ZT("_CreateSSLContext - Loading server certificate from: %s"), certFile));

        err = SSL_CTX_use_certificate_file(sslContext,
                                           certFile,
                                           strcmp(certFile + strlen(certFile) - 4, ".pem") == 0 ? SSL_FILETYPE_PEM :  SSL_FILETYPE_ASN1);
        if (err <= 0)
        {
#if defined(ENABLE_TRACING)
            unsigned long error = ERR_peek_last_error();
#endif

            LOGE2((ZT("_CreateSSLContext - No client certificate found in %s"), certFile));
            LOGE2((ZT("_CreateSSLContext - OpenSSL Error 0x%lX (%s) in SSL_CTX_use_certificate_file"), error, sslstrerror(error)));
            SSL_CTX_free(sslContext);
            sslContext = NULL;
            return MI_RESULT_FAILED;
        }

        if (privateKeyFile != NULL && *privateKeyFile != '\0')
        {
            /* load the specified private key */
            LOGD2((ZT("_CreateSSLContext - SSL Loading client private key from: %s"), privateKeyFile));

            err = SSL_CTX_use_RSAPrivateKey_file(sslContext,
                                                 privateKeyFile,
                                                 strcmp(privateKeyFile + strlen(privateKeyFile) - 4, ".pem") == 0 ? SSL_FILETYPE_PEM :  SSL_FILETYPE_ASN1);
            if (err <= 0)
            {
#if defined(ENABLE_TRACING)
                unsigned long error = ERR_peek_last_error();
#endif
                LOGE2((ZT("_CreateSSLContext - Invalid private key found in %s"), privateKeyFile));
                LOGE2((ZT("_CreateSSLContext - OpenSSL error 0x%lX (%s) in SSL_CTX_use_PrivateKey_file"), error, sslstrerror(error)));
                SSL_CTX_free(sslContext);
                sslContext = NULL;
                return MI_RESULT_FAILED;
            }
        }
    }

    self->sslContext = sslContext;
    return MI_RESULT_OK;
}

#endif

static MI_Result _CreateSocketAndConnect(
    Sock* s,
    Addr* addr)
{
    MI_Result r;

    LOGD2((ZT("_CreateSocketAndConnect - Begin")));

    /* Create client socket. */
    r = Sock_Create(s, addr->is_ipv6);
    if (r != MI_RESULT_OK)
    {
        LOGE2((ZT("_CreateSocketAndConnect - Sock_Create failed. result: %d (%s)"), r, mistrerror(r)));
        return r;
    }

    /* set the socket to be non-blocking */
    r = Sock_SetBlocking(*s, MI_FALSE);
    if (r != MI_RESULT_OK)
    {
        LOGE2((ZT("_CreateSocketAndConnect - Sock_SetBlocking failed. result: %d (%s)"), r, mistrerror(r)));
        return r;
    }

    /* connect the socket to the IP address */
    r = Sock_Connect(*s, addr);
    if (r != MI_RESULT_OK)
    {
        LOGE2((ZT("_CreateSocketAndConnect - Sock_Connect failed. result: %d (%s)"), r, mistrerror(r)));
        return r;
    }

    LOGD2((ZT("_CreateSocketAndConnect - OK exit")));

    return MI_RESULT_WOULD_BLOCK;
}

static MI_Result _CreateConnectorSocket(
    HttpClient* self,
    const char* host,
    unsigned short port,
    MI_Boolean secure,
    AuthMethod authType,
    const char* username,
    const char* password,
    const MI_Uint32 password_len)
{
    Addr addr;
    MI_Result r;
    Sock s;
    HttpClient_SR_SocketData* h;
    MI_Uint64 currentTimeUsec;

    LOGD2((ZT("_CreateConnectorSocket - Begin. host: %s, port: %d, secure? %d"), host, port, secure));

    /* timeout calculation */
    if (PAL_Time(&currentTimeUsec) != PAL_TRUE)
    {
        LOGE2((ZT("_CreateConnectorSocket - PAL_Time failed")));
        return MI_RESULT_FAILED;
    }

    /* This code tries to connect using the preferred addressing family (IPv4 */
        /* or IPv6). If that fails and Addr_Init has a secondary addressing */
        /* family, a connection with the secondary family, it tries using the */
        /* secondary family next. */

    /* Initialize preferred address */
    r = Addr_Init(&addr, host, port, MI_FALSE);
    if (r != MI_RESULT_OK)
    {
        LOGE2((ZT("_CreateConnectorSocket - Addr_Init failed. result: %d (%s)"), r, mistrerror(r)));
        return r;
    }

    /* Connect to the server */
    r = _CreateSocketAndConnect(&s, &addr);
    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        MI_Result r2;

        Sock_Close(s);

        LOGW2((ZT("_CreateConnectorSocket - _CreateSocketAndConnect of primary address failed. result: %d (%s)"), r, mistrerror(r)));

        /* Initialize secondary address */
        r2 = Addr_Init(&addr, host, port, MI_TRUE);
        if (r2 != MI_RESULT_OK)
            return r;                   /* on error, return original failure */
        r2 = _CreateSocketAndConnect(&s, &addr);
        if (r2 != MI_RESULT_OK && r2 != MI_RESULT_WOULD_BLOCK)
        {
            Sock_Close(s);

            LOGE2((ZT("_CreateConnectorSocket - Addr_Init failed. result: %d (%s)"), r, mistrerror(r)));

            return r;                   /* on error, return original failure */
        }
        r = r2;
    }

    /* Create handler */
    h = (HttpClient_SR_SocketData*)PAL_Calloc(1, sizeof(HttpClient_SR_SocketData));

    if (h == NULL)
    {
        Sock_Close(s);
        LOGE2((ZT("_CreateConnectorSocket - calloc failed")));
        return MI_RESULT_FAILED;
    }
    h->hostAddr = addr;
    h->port     = port;

    // If we have an authorisation method, eg Basic, Negotiate, etc, we are not yet authorised. But if there is none, then
    // go ahead if the server will let you, Hint, it probably won't

    h->isAuthorized = (authType == AUTH_METHOD_NONE);
    h->authorizing  = FALSE;

    h->authType = authType;
    h->username = (char*)username;
    h->password = (char*)password;
    h->passwordLen = password_len;
    h->authContext = NULL;
    h->cred        = NULL;

    /* Destination info. We use this in the authorisation transaction */

    if (self->callbackOnConnect)
        h->sendingState = RECV_STATE_CONNECT;
    else
        h->sendingState = RECV_STATE_HEADER;
    h->recvBufferSize = INITIAL_BUFFER_SIZE;
    h->recvBuffer = (char*)PAL_Calloc(1, h->recvBufferSize);
    if (!h->recvBuffer)
    {
        PAL_Free(h);
        Sock_Close(s);
        LOGE2((ZT("_CreateConnectorSocket - calloc failed")));
        return MI_RESULT_FAILED;
    }

    h->base.sock = s;
    if (self->callbackOnConnect)
        h->base.mask = SELECTOR_WRITE | SELECTOR_EXCEPTION;
    else
        h->base.mask = SELECTOR_EXCEPTION;
    h->base.callback = _RequestCallback;
    h->base.data = self;
    h->timeoutUsec = DEFAULT_HTTP_TIMEOUT_USEC;
    h->base.fireTimeoutAt = currentTimeUsec + h->timeoutUsec;

    /* SSL support */
    if (secure)
    {
        h->ssl = SSL_new(self->sslContext);

        if (!h->ssl)
        {
            LOGW2((ZT("_CreateConnectorSocket - SSL_new failed")));
            trace_SSLNew_Failed();
            PAL_Free(h);
            Sock_Close(s);
            return MI_RESULT_FAILED;
        }

        Sock_SetBlocking(s, MI_TRUE);
        if (!(SSL_set_fd(h->ssl, s) ))
        {
            LOGW2((ZT("_CreateConnectorSocket - SSL_set_fd failed")));
            trace_SSL_setfd_Failed();
            SSL_free(h->ssl);
            PAL_Free(h);
            Sock_Close(s);
            return MI_RESULT_FAILED;
        }

        SSL_set_connect_state(h->ssl);
    }

    /* Watch for read events on the incoming connection */
    r = Selector_AddHandler(self->selector, &h->base);

    if (r != MI_RESULT_OK)
    {
        LOGE2((ZT("_CreateConnectorSocket - Selector_AddHandler failed with error: %d (%s)"), (int)r, mistrerror(r)));
        trace_SelectorAddHandler_Failed();
        if (secure)
            SSL_free(h->ssl);
        PAL_Free(h);
        Sock_Close(s);
        return MI_RESULT_FAILED;
    }

    self->connector = h;

    LOGD2((ZT("_CreateConnectorSocket - OK exit. socket: %d, secure: %d, timeout: %s"), h->base.sock, secure, FmtInterval(h->base.fireTimeoutAt - currentTimeUsec)));

    return MI_RESULT_OK;
}

static MI_Result _New_Http(
    HttpClient** selfOut,
    Selector* selector, /*optional, maybe NULL*/
    HttpClientCallbackOnConnect statusConnect,
    HttpClientCallbackOnStatus2 statusCallback,
    HttpClientCallbackOnResponse  responseCallback,
    void* callbackData)
{
    HttpClient* self;

    /* Check parameters */
    if (!selfOut)
        return MI_RESULT_INVALID_PARAMETER;

    /* Clear output parameter */
    *selfOut = NULL;

    /* Allocate structure */
    {
        self = (HttpClient*)PAL_Calloc(1, sizeof(HttpClient));

        if (!self)
            return MI_RESULT_FAILED;
    }

    if (selector)
    {   /* attach the existing selector */
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
            LOGE2((ZT("_NewHttp - Selector_Init failed")));
            return MI_RESULT_FAILED;
        }
        self->selector = &self->internalSelector;
        self->internalSelectorUsed = MI_TRUE;
    }

    /* Save the callback and callbackData */
    self->callbackOnConnect = statusConnect;
    self->callbackOnResponse = responseCallback;
    self->callbackOnStatus = statusCallback;
    self->callbackData = callbackData;

    /* Set the magic number */
    self->magic = _MAGIC;

    /* Set output parameter */
    *selfOut = self;
    return MI_RESULT_OK;
}



#if 0
static size_t _GetHeadersSize(
    const HttpClientRequestHeaders* headers)
{
    size_t res = 0;
    size_t index = 0;

    while (index < headers->size)
    {
        res += Strlen(headers->data[index]);
        res += 2; /* \r \n pair */
        index++;
    }

    return res;
}
#endif

Page* _CreateHttpHeader(
    const char* verb,
    const char* uri,
    const char* contentType,
    const char* authHeader,
    size_t size)
{
    Page* page = 0;
    size_t pageSize = 0;
    int r;
    char* p;

#define HTTP_HEADER_FORMAT "%s %s HTTP/1.1\r\n" \
    "Content-Length: %d\r\n"\
    "Connection: Keep-Alive\r\n" \
    "Host: host\r\n"

#if 0
#define HTTP_HEADER_FORMAT_NOCL "%s %s HTTP/1.1\r\n" \
    "Connection: Keep-Alive\r\n" \
    "Host: host\r\n"
#endif

    /* calculate approximate page size */
    if (!verb)
        verb = "POST";

    pageSize += sizeof(HTTP_HEADER_FORMAT) + 10; /* format + 10 digits of content length */

    if (SizeTAdd(pageSize, Strlen(verb), &pageSize) != S_OK ||
        SizeTAdd(pageSize, Strlen(uri),  &pageSize) != S_OK ||
        SizeTAdd(pageSize, sizeof(Page), &pageSize) != S_OK ||
        (contentType && SizeTAdd(pageSize, Strlen(contentType), &pageSize) != S_OK) ||
        (authHeader  && SizeTAdd(pageSize, Strlen(authHeader), &pageSize) != S_OK) )
    {
        // Overflow
        return 0;
    }

    page = (Page*)PAL_Malloc(pageSize);

    if (!page)
        return 0;

    /* clear header */
    memset(page, 0, sizeof(Page));

    p = (char*)(page + 1);

    // if (size)
        r = Snprintf(p, pageSize, HTTP_HEADER_FORMAT, verb, uri, (int)size);
   // else
    //    r = Snprintf(p, pageSize, HTTP_HEADER_FORMAT_NOCL, verb, uri);

    if (r < 0)
    {
        PAL_Free(page);
        return 0;
    }

    p += r;
    pageSize -= r;

    if (contentType)
    {
        r = (int)Strlcpy(p, contentType, pageSize);
        p += r;
        pageSize -= r;
        r = (int)Strlcpy(p,"\r\n", pageSize);
        p += r;
        pageSize -= r;
    }

    if (authHeader)
        {
        r = (int)Strlcpy(p, authHeader, pageSize);
        p += r;
        pageSize -= r;
        r = (int)Strlcpy(p,"\r\n", pageSize);
        p += r;
        pageSize -= r;

    }

    /* add trailing \r\n */
    r = (int)Strlcpy(p,"\r\n", pageSize);
    p += r;
    pageSize -= r;

    page->u.s.size = (unsigned int)(p - (char*)(page+1));

    return page;
}


static Page* _CreateHttpAuthRequest(
    const char* verb,
    const char* uri,
    const char* contentType,
    const char* authHeader)
{
    Page* page = 0;
    size_t pageSize = 0;
    int r;
    char* p;

#define HTTP_HEADER_FORMAT_NOCL "%s %s HTTP/1.1\r\n" \
    "Connection: Keep-Alive\r\n" \
    "Content-Length: 0\r\n" \
    "Host: host\r\n"

    /* calculate approximate page size */
    if (!verb)
        verb = "POST";

    pageSize += sizeof(HTTP_HEADER_FORMAT) + 10; /* format + 10 digits of content length */

    if (SizeTAdd(pageSize, Strlen(verb), &pageSize) != S_OK ||
        SizeTAdd(pageSize, Strlen(uri),  &pageSize) != S_OK ||
        SizeTAdd(pageSize, sizeof(Page), &pageSize) != S_OK ||
        (contentType && SizeTAdd(pageSize, Strlen(contentType), &pageSize) != S_OK) ||
        (authHeader  && SizeTAdd(pageSize, Strlen(authHeader), &pageSize) != S_OK) )
    {
        // Overflow
        return 0;
    }

    page = (Page*)PAL_Malloc(pageSize);

    if (!page)
        return 0;

    /* clear header */
    memset(page, 0, sizeof(Page));

    p = (char*)(page + 1);

    r = Snprintf(p, pageSize, HTTP_HEADER_FORMAT_NOCL, verb, uri);

    if (r < 0)
    {
        PAL_Free(page);
        return 0;
    }

    p += r;
    pageSize -= r;

    if (contentType)
    {
        r = (int)Strlcpy(p, contentType, pageSize);
        p += r;
        pageSize -= r;
        r = (int)Strlcpy(p,"\r\n", pageSize);
        p += r;
        pageSize -= r;
    }

    if (authHeader)
        {
        r = (int)Strlcpy(p, authHeader, pageSize);
        p += r;
        pageSize -= r;
        r = (int)Strlcpy(p,"\r\n", pageSize);
        p += r;
        pageSize -= r;

    }

    /* add trailing \r\n */
    r = (int)Strlcpy(p,"\r\n", pageSize);
    p += r;
    pageSize -= r;

    page->u.s.size = (unsigned int)(p - (char*)(page+1));

    return page;
}


/**
 * _UnpackDestinationOptions 
 *
 * returns: 
 *   pUserName and pPassword are from a credential. That is only deleted at the end of the session
 *   pTrustedCertsDir, pCertsFile, pPrivateKeyfile return allocated data that must be freed
 *
 **/
MI_Result _UnpackDestinationOptions(
    _In_ MI_DestinationOptions *pDestOptions,
    _Out_opt_ AuthMethod *pAuthType,
    _Out_opt_ char **pUsername,
    _Out_opt_ char **pPassword,
    _Out_opt_ MI_Uint32 *pPasswordLen,
    _Out_opt_ char **pTrustedCertsDir,
    _Out_opt_ char **pCertFile,
    _Out_opt_ char **pPrivateKeyFile )

{
  static const MI_Char   AUTH_NAME_BASIC[]   = MI_AUTH_TYPE_BASIC;
  //static const MI_Uint32 AUTH_NAME_BASIC_LEN = sizeof(AUTH_NAME_BASIC)/sizeof(MI_Char);

  static const MI_Char   AUTH_NAME_NEGOTIATE[] = MI_AUTH_TYPE_NEGO_NO_CREDS;
  //static const MI_Uint32 AUTH_NAME_NEGOTIATE_LEN = sizeof(AUTH_NAME_NEGOTIATE)/sizeof(MI_Char);

  static const MI_Char   AUTH_NAME_NEGOTIATE_WITH_CREDS[] = MI_AUTH_TYPE_NEGO_WITH_CREDS;
  //static const MI_Uint32 AUTH_NAME_NEGOTIATE_WITH_CREDS_LEN = sizeof(AUTH_NAME_NEGOTIATE_WITH_CREDS)/sizeof(MI_Char);

  static const MI_Char   AUTH_NAME_KERBEROS[]   = MI_AUTH_TYPE_KERBEROS;
  //static const MI_Uint32 AUTH_NAME_KERBEROS_LEN = sizeof(AUTH_NAME_KERBEROS)/sizeof(MI_Char);

  MI_Uint32 cred_count = 0;
  MI_Char *optionName = NULL;
  MI_UserCredentials userCredentials;
  MI_Uint32 username_len = 0;
  MI_Uint32 password_len = 0;
  char *username = NULL;
  char *password = NULL;
  MI_Result result = MI_RESULT_OK;

  AuthMethod method = AUTH_METHOD_NONE;

   // Unpack the destination options
   /* Must have one and only one credential */

    if ((MI_DestinationOptions_GetCredentialsCount(pDestOptions, &cred_count) != MI_RESULT_OK) ||
            (cred_count != 1))
    {
        result = MI_RESULT_ACCESS_DENIED;
        goto Done;
    }

    /* Get username pointer from options.
     */

    if (MI_DestinationOptions_GetCredentialsAt(pDestOptions, 0, (const MI_Char **)&optionName, &userCredentials, NULL) 
          != MI_RESULT_OK)
    {
        // Log here
        LOGE2((ZT("_UnpackDestinationOptions: No credentials available.")));
        result = MI_RESULT_INVALID_PARAMETER;
        goto Done;
    }         


    /* First delivery. pAuthType. We convert the string into an enum */
    
    method = AUTH_METHOD_NONE;
    if (userCredentials.authenticationType)
    {
        method = AUTH_METHOD_UNSUPPORTED;
    }

    if (Tcscasecmp(userCredentials.authenticationType, AUTH_NAME_BASIC) == 0)
    {
        method = AUTH_METHOD_BASIC;
    }
   
    if (Tcscasecmp(userCredentials.authenticationType, AUTH_NAME_NEGOTIATE) == 0) 
    {
        method = AUTH_METHOD_NEGOTIATE;
    }
    
    if (Tcscasecmp(userCredentials.authenticationType, AUTH_NAME_NEGOTIATE_WITH_CREDS) == 0) 
    {
        method = AUTH_METHOD_NEGOTIATE_WITH_CREDS;
    }
    
    if (Tcscasecmp(userCredentials.authenticationType,  AUTH_NAME_KERBEROS) == 0) 
    {
        method = AUTH_METHOD_KERBEROS;
    }

    // We only output it if it is wanted.

    if (pAuthType) {
        *pAuthType = method;
    }

    if (method == AUTH_METHOD_UNSUPPORTED)
    {
        // Log here
        LOGE2((ZT("_UnpackDestinationOptions: Authorisation type (%s) is not supported."), userCredentials.authenticationType));
        result = MI_RESULT_INVALID_PARAMETER;
        goto Done;
    }         


    if (userCredentials.credentials.usernamePassword.username) {
        username_len = Tcslen(userCredentials.credentials.usernamePassword.username);
        username = (char*) PAL_Malloc(username_len+1);
        if (username == NULL)
        {
            result = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            goto Done;
        }
        memcpy(username, userCredentials.credentials.usernamePassword.username, username_len+1);
        username[username_len] = 0;
    }
    else {
        if (method == AUTH_METHOD_BASIC) {
            LOGE2((ZT("_UnpackDestinationOptions: Authorisation type Basic requires username.")));
            return MI_RESULT_INVALID_PARAMETER;
        }
    }

    if (pUsername) {
        *pUsername = username;
    }

    /* We need to allocate a buffer for the password.
     * Get length of it, allocate and then retrieve it.
     */

    if (MI_DestinationOptions_GetCredentialsPasswordAt(pDestOptions, 0, (const MI_Char **)&optionName, NULL, 0, &password_len, NULL) != MI_RESULT_OK)
    {
        if (method == AUTH_METHOD_BASIC) {
            LOGE2((ZT("_UnpackDestinationOptions: Authorisation type requires password.")));
            return MI_RESULT_INVALID_PARAMETER;
        }
    }

    if (password_len <= 0) {
        if (method == AUTH_METHOD_BASIC) {
            LOGE2((ZT("_UnpackDestinationOptions: Authorisation type requires password.")));
            return MI_RESULT_INVALID_PARAMETER;
        }
    }
    else 
    {
        password = (char*) PAL_Malloc(password_len);
        if (password == NULL)
        {
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }
    
        if (MI_DestinationOptions_GetCredentialsPasswordAt(pDestOptions, 0, (const MI_Char **)&optionName, (MI_Char *)password, password_len, &password_len, NULL) != MI_RESULT_OK)
        {
            result = MI_RESULT_FAILED;
            goto Done;
        }
    }

    if (pPassword) {
        *pPassword = password;
    }
    

    if (pPasswordLen) {
        *pPasswordLen = password_len;
    }

 
    if (pTrustedCertsDir)
    { 
        const MI_Char *tmpval = NULL;

        *pTrustedCertsDir = NULL;

        if (MI_DestinationOptions_GetTrustedCertsDir(pDestOptions, &tmpval) == MI_RESULT_OK)
        {
        

            // Copy the string into a char array because an MI_Char can be 1,2, or 4 bytes wide depending on 
            // the build options. We need it to be specificly char

            *pTrustedCertsDir = PAL_Malloc(Tcslen(tmpval)+1);
            TcsStrlcpy(*pTrustedCertsDir, tmpval, Tcslen(tmpval)+1);
        }
    }

    if (pCertFile)
    {
        const MI_Char *tmpval = NULL;

        *pCertFile = NULL;
        if (MI_DestinationOptions_GetCertFile(pDestOptions, &tmpval) == MI_RESULT_OK)
        {
        
            // Copy the string into a char array because an MI_Char can be 1,2, or 4 bytes wide depending on 
            // the build options. We need it to be specificly char

            *pCertFile = PAL_Malloc(Tcslen(tmpval)+1);
            TcsStrlcpy(*pCertFile, tmpval, Tcslen(tmpval)+1);
        }
    }

    if (pPrivateKeyFile)
    {
        const MI_Char *tmpval = NULL;

        *pPrivateKeyFile = NULL;
        if (MI_DestinationOptions_GetPrivateKeyFile(pDestOptions, &tmpval) == MI_RESULT_OK)
        {

            // Copy the string into a char array because an MI_Char can be 1,2, or 4 bytes wide depending on 
            // the build options. We need it to be specificly char
            *pPrivateKeyFile = PAL_Malloc(Tcslen(tmpval)+1);
            TcsStrlcpy(*pPrivateKeyFile, tmpval, Tcslen(tmpval)+1);
        }
    }

Done:

    if (result != MI_RESULT_OK) {
        if (username) {
            PAL_Free(username);
        }

        if (password) {
            PAL_Free(password);
        }
    }

    return result;
}



/* ************************************************************************* *\
                                HTTP CLIENT
\* ************************************************************************* */
/*
    Creates new http client.

    Parameters:
    selfOut - [out] newly created http object (or null if failed).
    selector - [opt] selector to use for socket monitoring. If selector not specified,
            private one is created.
    host - host address
    port - port number
    secure - flag that indicates if http or https conneciton is required

    Returns:
    'OK' on success or error code otherwise
*/

MI_Result HttpClient_New_Connector(
    HttpClient** selfOut,
    Selector* selector, /*optional, maybe NULL*/
    const char* host,
    unsigned short port,
    MI_Boolean secure,
    HttpClientCallbackOnStatus statusCallback,
    HttpClientCallbackOnResponse  responseCallback,
    void* callbackData,
    MI_DestinationOptions *pDestOptions)

{
    return HttpClient_New_Connector2(
            selfOut,
            selector,
            host,
            port,
            secure,
            NULL,
            (HttpClientCallbackOnStatus2)statusCallback,
            responseCallback,
            callbackData,
            pDestOptions );
}

MI_Result HttpClient_New_Connector2(
    HttpClient** selfOut,
    Selector* selector, /*optional, maybe NULL*/
    const char* host,
    unsigned short port,
    MI_Boolean secure,
    HttpClientCallbackOnConnect statusConnect,
    HttpClientCallbackOnStatus2 statusCallback,
    HttpClientCallbackOnResponse  responseCallback,
    void* callbackData,
    MI_DestinationOptions *pDestOptions)
{
    HttpClient* self;
    MI_Result r;
    char *trustedCertsDir = NULL;
    char *certFile        = NULL;
    char *privateKeyFile  = NULL;

    AuthMethod authtype =  AUTH_METHOD_UNSUPPORTED;
    char *username = NULL;
    char *password = NULL;

    MI_Uint32 password_len = 0;

    /* allocate this, inits selector */
    r = _New_Http(selfOut, selector, statusConnect, statusCallback,
                  responseCallback, callbackData);

    if (MI_RESULT_OK != r)
    {
        LOGE2((ZT("HttpClient_New_Connector - _New_Http failed. result: %d (%s)"), r, mistrerror(r)));
        return r;
    }
    self = *selfOut;
    r = _UnpackDestinationOptions(pDestOptions, &authtype, &username, &password, &password_len, 
                                  &trustedCertsDir, &certFile, &privateKeyFile);

#ifdef CONFIG_POSIX
    /* Allocate SSL context */
    if (secure)
    {
        /* init ssl */
        SSL_library_init();

        /* create context */
        r = _CreateSSLContext(self, trustedCertsDir, certFile, privateKeyFile);

        if (r != MI_RESULT_OK)
        {
            HttpClient_Delete(self);
            *selfOut = NULL;
            LOGE2((ZT("HttpClient_New_Connector - _CreateSSLContext failed. result: %d (%s)"), r, mistrerror(r)));
            goto Cleanup;
        }
    }
#else
    MI_UNUSED(secure);
#endif

    /* Create http connector socket */
    {
        r = _CreateConnectorSocket(self, host, port, secure, authtype, username, password, password_len);

        if (r != MI_RESULT_OK)
        {
            HttpClient_Delete(self);
            LOGE2((ZT("HttpClient_New_Connector - _CreateConnectorSocket failed failed. result: %d (%s)"), r, mistrerror(r)));
            goto Cleanup;
        }
    }

Cleanup:

    if (trustedCertsDir)
    {
        PAL_Free(trustedCertsDir);
    }

    if (certFile)
    {
        PAL_Free(certFile);
    }

    if (privateKeyFile)
    {
        PAL_Free(privateKeyFile);
    }

    return r;
}

/*
    Deletes http object, disconnects form the server
    and frees all related resources.

    Parameters:
    self - http object

    Returns:
    OK
*/
MI_Result HttpClient_Delete(
    HttpClient* self)
{
    /* Check parameters */
    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

    /* Check magic number */
    if (self->magic != _MAGIC)
    {
        LOGE2((ZT("HttpClient_Delete - Bad magic number")));
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (self->internalSelectorUsed)
    {
        /* Release selector;
        Note: Selector_Destroy closes all sockets in a list including connector and listener */
        Selector_Destroy(self->selector);

        /* Shutdown the network */
        Sock_Stop();
    }
    else
    {
        /* remove connector from handler */
        if (self->connector)
        {
            if (self->connector->username)
            {
                PAL_Free(self->connector->username);
                self->connector->username = NULL;
            }
        
            if (self->connector->password)
            {
                PAL_Free(self->connector->password);
                self->connector->password = NULL;
            }
        
            Selector_RemoveHandler(self->selector, &self->connector->base);
        }
    }

    if (self->sslContext)
        SSL_CTX_free(self->sslContext);

    /* Clear magic number */
    self->magic = 0xDDDDDDDD;

    /* Free self pointer */
    PAL_Free(self);

    return MI_RESULT_OK;
}


/*
    Sends http request.

    Parameters:
    self - http object
    uri - request's URI
    headers - [opt] extra headers for request.
    data - [opt] content to send. if message is accepted to be sent,
        on return *data == null (taking memory ownership)

    Returns:
    OK or appropriate error
 */
MI_Result HttpClient_StartRequest(
    HttpClient* self,
    const char* verb,
    const char* uri,
    const char*contentType,
    Page** data)
{
    MI_Result ret;
    const char *auth_header;
    LOGD2((ZT("HttpClient_StartRequest - Begin. verb: %s, URI: %s"), verb, uri));

    /* check params */
    if (!self || !uri)
        return MI_RESULT_INVALID_PARAMETER;

    if (self->magic != _MAGIC)
    {
        LOGE2((ZT("HttpClient_Delete - Bad magic number")));
        trace_StartRequest_InvalidMagic();
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (self->connector == NULL)
    {
        LOGE2((ZT("HttpClient_Delete - Connection is not open")));
        trace_StartRequest_ConnectionClosed();
        return MI_RESULT_FAILED;
    }

    /* Do we need to authorise? */

    if (!self->connector->isAuthorized) {
        ret = HttpClient_RequestAuthorization(self->connector, &auth_header);
        switch (ret) {
        case PRT_RETURN_FALSE:
            // Not authorised. No auth header
            return MI_RESULT_FAILED;
           
        case PRT_CONTINUE:
            // We need to to the auth loop.

	    if (self->connector->authType == AUTH_METHOD_BASIC)
	    {
                 // Basic sends the payload first time

                 break;
            }
            self->connector->sendHeader =
                _CreateHttpAuthRequest(verb, uri, contentType, auth_header);

            /* We dont send the data until authorised */

            /* Save the request information until we are authorised */
            self->connector->verb = (char *)verb; // BAC Always "POST" but we keep it anyway. It seems to be a literal. Are they static?
            self->connector->uri  = (char *)uri;
            self->connector->contentType = (char *)contentType;
            self->connector->data = *data;
            self->connector->sendPage = NULL;
	    
            /* set status to failed, until we know more details */
            self->connector->status = MI_RESULT_FAILED;
            self->connector->sentSize = 0;
            self->connector->sendingState = RECV_STATE_HEADER;

            _RequestCallbackWrite(self->connector);

            return MI_RESULT_OK;

        case PRT_RETURN_TRUE:
            break;

        default:
            break;
        }
    }

    /* create header page */
    self->connector->sendHeader =
        _CreateHttpHeader(verb, uri, contentType, auth_header, (data && *data) ? (*data)->u.s.size : 0);

    if (data != NULL)
    {
        self->connector->sendPage = *data;
        *data = 0;
    }
    else
        self->connector->sendPage = NULL;

    /* set status to failed, until we know more details */
    self->connector->status = MI_RESULT_FAILED;
    self->connector->sentSize = 0;
    self->connector->sendingState = RECV_STATE_HEADER;
    self->connector->base.mask |= SELECTOR_WRITE;

    _RequestCallbackWrite(self->connector);
    if (auth_header) {
        PAL_Free((MI_Char*)auth_header);
    }

    return MI_RESULT_OK;
}

MI_Result HttpClient_Run(
    HttpClient* self,
    MI_Uint64 timeoutUsec)
{
    /* Run the selector */
    return Selector_Run(self->selector, timeoutUsec, MI_FALSE);
}

MI_Result HttpClient_SetTimeout(
    HttpClient* self,
    MI_Uint64 timeoutUsec)
{
    MI_Uint64 currentTimeUsec = 0;

    PAL_Time(&currentTimeUsec);

    /* check params */
    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

    if (self->magic != _MAGIC)
    {
        trace_Timeout_InvalidMagic();
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (!self->connector)
        return MI_RESULT_INVALID_PARAMETER;

    /* create header page */
    self->connector->timeoutUsec = timeoutUsec;
    self->connector->base.fireTimeoutAt = currentTimeUsec + self->connector->timeoutUsec;

    return MI_RESULT_OK;
}

Selector *HttpClient_GetSelector(HttpClient *self)
{
    return self->selector;
}
