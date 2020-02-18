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
#include <pal/once.h>
#include <base/paths.h>
#include <sys/time.h>
#include "sessionmap.h"

#define ENABLE_TRACING 1
#define FORCE_TRACING 1

#ifndef CONFIG_POSIX
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


#ifdef ENABLE_TRACING
# define TRACING_LEVEL 4
#include <base/result.h>
#include <base/logbase.h>
#include <base/log.h>
#define LOGE2 __LOGE
#define LOGW2 __LOGW
#define LOGD2 __LOGD
#define mistrerror Result_ToString

#if (__GNUC__==4 && __GNUC_MINOR__==3 && __OPTIMIZE__)
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif 

static char FmtBuf[256];
static const char* FmtInterval(MI_Sint64 Time)
{
    char* TmBufBase = FmtBuf;
    char* TmBuf = TmBufBase;
    unsigned long Sec;
    unsigned long uSec;
    unsigned long Min;
    unsigned long Hr;

    if (Time < 0)
    {
        *TmBuf++ = '-';
        Time = -Time;
    }
    Sec = (unsigned long)(Time / 1000000);
    uSec = (unsigned long)(Time % 1000000);
    Min = (unsigned long)Sec / 60;
    Sec -= Min * 60;
    Hr = Min / 60;
    Min -= Hr * 60;
    Hr %= 60;
    if (Hr != 0)
    {
        sprintf(TmBuf, "%02lu:%02lu:%02lu.%03lu", Hr, Min, Sec, uSec / 1000);
    }
    else if (Min != 0)
    {
        sprintf(TmBuf, "%02lu:%02lu.%03lu", Min, Sec, uSec / 1000);
    }
    else if (Sec == 0 && uSec == 0)
    {
        sprintf(TmBuf, "0.0");
    }
    else if (Sec != 0 || uSec >= 1000)
    {
        sprintf(TmBuf, "%lu.%03lu", Sec, uSec / 1000);
    }
    else
    {
        sprintf(TmBuf, "%lu.%06lu", Sec, uSec);
    }

    return TmBufBase;
}


static const char* sslstrerror(unsigned long SslError)
{
    char* buf = FmtBuf;

    ERR_error_string_n(SslError, buf, 256);
    return buf;
}
#else
# define LOGE2(a)
# define LOGW2(a)
# define LOGD2(a)
# define LOGX2(a)
#endif

#include "httpclient_private.h"

/* 
    NOTE: Initialize the session map
*/
static SessionMap _sessionMap = SESSIONMAP_INIT;



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
static const char* MS_WSMAN_COOKIE_PREFIX = "MS-WSMAN=";
#define MS_WSMAN_COOKIE_PREFIX_LEN (MI_COUNT(MS_WSMAN_COOKIE_PREFIX)-1)

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
    else if (nameHashCode == _HashCode('s', 'e', 10) &&
        Strcasecmp(name, "Set-Cookie") == 0)
    {
        if (handler->sessionId && Strncmp(value, MS_WSMAN_COOKIE_PREFIX, MS_WSMAN_COOKIE_PREFIX_LEN) == 0)
        {
            SessionMap_SetCookie(&_sessionMap, handler->sessionId, value);
        }
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

/* 
    Writes a session id and timestamp to a trace file
    using _WriteTraceFile.

    Parameters:
        pathId - the identifier for the trace file
        sessionId - the string session id (HttpClient_SR_SocketData.sessionId and HttpClient.sessionId)

    NOTES: This is called by _WriteClientHeader using ID_HTTPCLIENTRECVTRACEFILE
    and _ReadHeader using ID_HTTPCLIENTSENDTRACEFILE.
    It provides a marker to indicate the start of a request or response in the omiclient-*.trc 
    file as well as aiding in correlating messages to a given session.
*/
static void _WriteTraceSessionTimestamp(_In_ PathID pathId, _In_opt_z_ const char* sessionId)
{
    // session id: 20, timestamp: 29, whitespace and static text:19, zero terminator
    // [Session: NNNNN Date: YYYY/MM/DD HH:MM:SS.1234567Z]
    #define SESSION_DATETIME_SIZE 70
    const char FMT[] = "[Session: %s Date: %04d-%02d-%02d %02d:%02d:%02d.%07dZ]";
    char buf[SESSION_DATETIME_SIZE];

    struct timeval tv;
    struct tm tm;

    gettimeofday(&tv, NULL);
    gmtime_r(&tv.tv_sec, &tm);
    if (!sessionId)
    {
        sessionId = "None";
    }
    Stprintf(buf, SESSION_DATETIME_SIZE, FMT,
        sessionId,
        tm.tm_year + 1900,
        tm.tm_mon + 1,
        tm.tm_mday,
        tm.tm_hour,
        tm.tm_min,
        tm.tm_sec,
        tv.tv_usec);
    _WriteTraceFile(pathId, buf, Strlen(buf));
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
    HttpClient* client = (HttpClient*)handler->base.data;
    size_t allocSize = 0;

    /* are we done with header? */
    if (handler->recvingState != RECV_STATE_HEADER)
    {
        return PRT_CONTINUE;
    }

    buf = handler->recvBuffer + handler->receivedSize;
    buf_size = handler->recvBufferSize - handler->receivedSize;
    received = 0;

    r = _Sock_Read(handler, buf, buf_size, &received);
    LOGD2((ZT("_ReadHeader - Begin. _Sock_read result: %d (%s), socket: %d, %u / %u bytes read, reverse: %d"),
          (int)r, mistrerror(r), (int)handler->base.sock, (unsigned int)received, (unsigned int)buf_size, (int)handler->reverseOperations));

    if (r == MI_RESULT_OK && 0 == received)
    {
        LOGW2((ZT("_ReadHeader - 0 bytes received without error. Socket closed?")));
        goto Error; /* connection closed */
    }

    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        LOGE2((ZT("_ReadHeader - Error %d (%s)"), r, mistrerror(r)));
        goto Error;
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
                r = MI_RESULT_FAILED;
                goto Error;
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
            r = MI_RESULT_FAILED;
            goto Error;
        }
    }

    if (FORCE_TRACING || (r == MI_RESULT_OK && handler->enableTracing))
    {
        _WriteTraceSessionTimestamp(ID_HTTPCLIENTRECVTRACEFILE, handler->sessionId);
        _WriteTraceFile(ID_HTTPCLIENTRECVTRACEFILE, buf, handler->receivedSize);
    }

    /* consume data */
    currentLine = buf;
    data = buf + index + 1; /* pointer to data in case we got some */

    if (!_getRequestLine(handler, &currentLine))
    {
        LOGE2((ZT("_ReadHeader - Cannot find request line in HTTP header")));
        r = MI_RESULT_INVALID_PARAMETER;
        goto Error;
    }

    while ((data - currentLine) > 3)
    {
        if (!_getHeaderField(handler, &currentLine))
        {
            LOGE2((ZT("_ReadHeader - Cannot find HTTP header field")));
            r = MI_RESULT_INVALID_PARAMETER;
            goto Error;
        }
    }

    /* Check if we have to deal with chunked-encoded data */
    if (handler->contentLength < 0)
    {
        handler->receivedSize -= index + 1;

        /* Invoke user's callback with header information */
        {
            if (!(*client->callbackOnResponse)(client, client->callbackData, &handler->recvHeaders,
                handler->contentLength, handler->contentLength == 0, 0))
            {
                LOGD2((ZT("_ReadHeader - On response callback for header returned false -- we are done")));
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

    if (SizeTAdd(sizeof(Page), contentSize, &allocSize) == S_OK &&
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
        r = MI_RESULT_FAILED;
        goto Error;
    }

    if (handler->recvPage == NULL)
    {
        LOGD2((ZT("_ReadHeader - Cannot allocate memory for received page")));
        r = MI_RESULT_FAILED;
        goto Error;
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
        r = MI_RESULT_FAILED;
        goto Error;
    }

    if (handler->receivedSize != 0)
        memcpy(handler->recvPage + 1, data, handler->receivedSize);
    handler->recvingState = RECV_STATE_CONTENT;

    /* Check the authentication. If we need to recycle, send a response to the response. */

    if (!handler->isAuthorized) 
    {
        LOGD2((ZT("_ReadHeader - check authorization")));
        rslt = HttpClient_IsAuthorized(handler);

        switch (rslt) 
        {
        case PRT_RETURN_TRUE:
            LOGD2((ZT("_ReadHeader - not (yet) authorized. reslt = %d"), rslt));
            return rslt;

        case PRT_RETURN_FALSE:
            if (!handler->authorizing)
            {
                LOGD2((ZT("_ReadHeader - ACCESS DENIED reslt = %d"), rslt));
                r = MI_RESULT_ACCESS_DENIED; 
                goto Error;
            }
            break;

        case PRT_CONTINUE:
            LOGD2((ZT("_ReadHeader - is authorized. continue")));
         
        }
    }

    if (handler->isAuthorized && PRT_CONTINUE != rslt)
    {
        /* Invoke user's callback with header information of there is no content expected. 
         * Else we will do so when we have read the data */

        if (!(*client->callbackOnResponse)(client, 
                                         client->callbackData,
                                         &handler->recvHeaders,
                                         handler->contentLength,
                                         handler->contentLength == 0, 0))
        {
            LOGD2((ZT("_ReadHeader - On response callback for header returned false -- we are done")));
            return PRT_RETURN_FALSE;
        }
    }

    LOGD2((ZT("_ReadHeader - OK exit")));
    return rslt;
Error:
    (*(HttpClientCallbackOnStatus2)(client->callbackOnStatus)) (client, client->callbackData, r, client->connector->errMsg, client->probableCause );
    return PRT_RETURN_FALSE;
}


static Http_CallbackResult _ReadData(
    HttpClient_SR_SocketData* handler)
{
    HttpClient* client = (HttpClient*)handler->base.data;
    char* buf;
    size_t buf_size, received;
    MI_Result r = MI_RESULT_FAILED;
#if defined(ENCRYPT_DECRYPT)
     Page *pOldRecvPage = NULL;
#endif


    /* are we in the right state? */
    if (handler->recvingState != RECV_STATE_CONTENT)
    {
        LOGD2((ZT("_ReadData - recv state:skip")));
        return PRT_RETURN_FALSE;
    }

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
            {
                goto Error; /* connection closed */
            }

            if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
            {
                goto Error;
            }

            handler->receivedSize += received;

            LOGD2((ZT("_ReadData. %d / %d bytes read"), (int)handler->receivedSize, (int)handler->contentLength));

            if (handler->contentLength > 0 && handler->receivedSize < (size_t)handler->contentLength)
            {                           /* assume 500 bytes per millisecond transmission */
                                        /* wait to avoid spinning on _Sock_Read */
                //unsigned int bytesLeft = (unsigned int)handler->contentLength - (unsigned int)handler->receivedSize;
                /* unsigned long msec = (unsigned long)(bytesLeft / 500 + 1); */

                Sleep_Milliseconds(10);
            }
        }

        /* did we get all data? */
        LOGD2((ZT("_ReadData - Received size: %d / %d"), (int)handler->receivedSize, (int)handler->contentLength));
        if (handler->receivedSize != (size_t)handler->contentLength)
        {
            return PRT_RETURN_TRUE;
        }
    }

    if (FORCE_TRACING || (r == MI_RESULT_OK && handler->enableTracing))
    {
        _WriteTraceFile(ID_HTTPCLIENTRECVTRACEFILE, (char*)(handler->recvPage + 1), handler->receivedSize);
    }


    if (handler->encrypting)
    {

#if ENCRYPT_DECRYPT
        pOldRecvPage = handler->recvPage;

        if (!HttpClient_DecryptData(handler, &handler->recvHeaders, &handler->recvPage) )
        {
            // Failed decrypt. No encryption counts as success. So this is an error in the decrpytion, probably 
            // bad credential

            handler->recvPage = 0;
            handler->receivedSize = 0;
            memset(&handler->recvHeaders, 0, sizeof(handler->recvHeaders));
            handler->recvingState = RECV_STATE_HEADER;
            goto Error;
        }
        else 
        {
            if (FORCE_TRACING || handler->enableTracing)
            {
                char after_decrypt[] = "\n------------ After Decryption ---------------\n";
                char after_decrypt_end[] = "\n-------------- End Decrypt ------------------\n";
                _WriteTraceFile(ID_HTTPRECVTRACEFILE, &after_decrypt, sizeof(after_decrypt));
                _WriteTraceFile(ID_HTTPRECVTRACEFILE, (char *)(handler->recvPage+1), handler->recvPage->u.s.size);
                _WriteTraceFile(ID_HTTPRECVTRACEFILE, &after_decrypt_end, sizeof(after_decrypt_end));
            }
        }
#endif
    }
    if (handler->isAuthorized) 
    {
        /* Invoke user's callback with header information */
        MI_Boolean lastChunk = MI_TRUE;
        HttpClientCallbackOnStatus2 statusCallback = client->callbackOnStatus;
        void *callbackContext = client->callbackData;

        if (handler->contentEnd >= 0 &&
            handler->contentEnd + 1 < handler->contentTotalLength)
        {
            lastChunk = MI_FALSE;
        }

        handler->status = MI_RESULT_OK;

        LOGD2((ZT("_ReadData - call response callback")));
        if (!(*client->callbackOnResponse)(client, callbackContext, &handler->recvHeaders, handler->contentLength, lastChunk, &handler->recvPage))
        {
            LOGD2((ZT("_ReadData - response callback returned FALSE indicating it is done with the http request")));
            return PRT_RETURN_FALSE;
        }
        (*(HttpClientCallbackOnStatus2)(statusCallback)) (client, callbackContext, MI_RESULT_OK, NULL, NULL );
    }

#if ENCRYPT_DECRYPT
    if (0 && pOldRecvPage && pOldRecvPage != handler->recvPage)
    {
        LOGD2((ZT("_ReadData - Freeing recvPage. socket: %d"), (int)handler->base.sock));
        PAL_Free(pOldRecvPage);
        pOldRecvPage = NULL;
    }
#endif
    if (handler->recvPage != NULL)
    {
        LOGD2((ZT("_ReadData - Freeing recvPage. socket: %d"), (int)handler->base.sock));
        PAL_Free(handler->recvPage);
        handler->recvPage = NULL;
    }

    handler->recvPage = NULL;
    handler->receivedSize = 0;
    memset(&handler->recvHeaders, 0, sizeof(handler->recvHeaders));
    handler->recvingState = RECV_STATE_HEADER; /* TODO: We are needing to send new headers to server, not get headers from them */
    LOGD2((ZT("_ReadData - OK exit")));

    return PRT_CONTINUE;

Error:
    (*(HttpClientCallbackOnStatus2)(client->callbackOnStatus)) (client, client->callbackData, r, client->connector->errMsg, client->probableCause );
    return PRT_RETURN_FALSE;
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
        HttpClient* self = (HttpClient*)handler->base.data;
        /* last chunk received */

        /* Invoke user's callback with header information */

        if (!(*self->callbackOnResponse)( self, self->callbackData, 0,
            handler->contentLength, MI_TRUE, 0))
            return PRT_RETURN_FALSE;

        /* clean up state */
        handler->recvPage = 0;
        handler->receivedSize = 0;
        memset(&handler->recvHeaders, 0, sizeof(handler->recvHeaders));
        handler->recvingState = RECV_STATE_HEADER;

        if (connectionClosed)
        {
            /* status callback */
            handler->status = MI_RESULT_OK;
            (*self->callbackOnStatus)(
                self,
                self->callbackData,
                MI_RESULT_OK, NULL, NULL);

            return PRT_RETURN_FALSE; /* connection closed */
        }

        return PRT_CONTINUE;
    }

    size_t allocSize = 0;
    if (SizeTAdd(sizeof(Page), (size_t)chunkSize, &allocSize) == S_OK &&
        SizeTAdd(allocSize, 2 /*CR-LF*/ + 1 /* \0 */, &allocSize) == S_OK &&
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

    if (FORCE_TRACING || (r == MI_RESULT_OK && handler->enableTracing))
    {
        _WriteTraceFile(ID_HTTPCLIENTSENDTRACEFILE, (char*)(handler->recvPage + 1), handler->receivedSize);
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

Http_CallbackResult _WriteClientHeader(HttpClient_SR_SocketData* handler)

{
    char* buf;
    size_t buf_size, sent;
    MI_Result r;

    /* are we done with header? */
    if (handler->sendingState == RECV_STATE_CONTENT)
    {
        return PRT_CONTINUE;
    }

    /* Do we have any data to send? */
    if (!handler->sendHeader)
    {
        goto Error;
    }

    LOGD2((ZT("_WriteHeader - Begin")));

#if ENCRYPT_DECRYPT

    if (handler->encrypting && handler->readyToSend)
    {
        if (handler->sentSize == 0)
        {
            // We only do this once per buffer. If we have to retransmit we don't have to re-encrypt

            Page *pOldPage   = handler->sendPage;
            Page *pOldHeader = handler->sendHeader;
    
            if (!HttpClient_EncryptData(handler, &handler->sendHeader, &handler->sendPage) )
            {
                 
                // If we fail it was an error. Not encrypting counts as failure Complain and bail
    
                trace_HTTP_EncryptionFailed();
                goto Error;
            }
            else
            {
                if (FORCE_TRACING || handler->enableTracing) 
                {
                    char before_encrypt[] = "\n------------ Before Encryption ---------------\n";
                    char before_encrypt_end[] = "\n------------ End Before ---------------\n";
                    _WriteTraceFile(ID_HTTPCLIENTSENDTRACEFILE, &before_encrypt, sizeof(before_encrypt));
                    _WriteTraceFile(ID_HTTPCLIENTSENDTRACEFILE, (char *)(pOldHeader+1), pOldHeader->u.s.size);
                    if (pOldPage) 
                    {
                        _WriteTraceFile(ID_HTTPCLIENTSENDTRACEFILE, (char *)(pOldPage+1), pOldPage->u.s.size);
                    }
                    _WriteTraceFile(ID_HTTPCLIENTSENDTRACEFILE, &before_encrypt_end, sizeof(before_encrypt_end));
                }
    
                // Can we delete these or are they part of a batch and must be deleted separately?
                if (pOldHeader != handler->sendHeader)
                {    
                    PAL_Free(pOldHeader);
                }
                if (pOldPage && pOldPage != handler->sendPage)
                {
                    PAL_Free(pOldPage);
                }        
            }
        }
    }

#endif
    buf = ((char*)(handler->sendHeader + 1)) + handler->sentSize;
    buf_size = handler->sendHeader->u.s.size - handler->sentSize;
    sent = 0;

    if (FORCE_TRACING || handler->enableTracing)
    {
        // log a date/time stamp
        _WriteTraceSessionTimestamp(ID_HTTPCLIENTSENDTRACEFILE, handler->sessionId);
        // log the headers
        _WriteTraceFile(ID_HTTPCLIENTSENDTRACEFILE, buf, buf_size);
    }

    r = _Sock_Write(handler, buf, buf_size, &sent);
    LOGD2((ZT("_WriteHeader - _Sock_Write result: %d (%s), socket: %d, sent: %d"), (int)r, mistrerror(r), (int)handler->base.sock, (int)sent));

    if (r == MI_RESULT_OK && 0 == sent)
    {
        LOGE2((ZT("_WriteHeader - Connection closed")));
        goto Error;
    }

    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        LOGE2((ZT("_WriteHeader - _Sock_Write returned error: %d (%s)"), (int)r, mistrerror(r)));
        goto Error;
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

Error:
    return PRT_RETURN_FALSE;
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
        
        goto Error;
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
        goto Error;
    }

    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        LOGE2((ZT("_WriteClientData exit - Error: %d (%s)"), r, mistrerror(r)));
        goto Error;
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
        _WriteTraceFile(ID_HTTPCLIENTSENDTRACEFILE, (char*)(handler->sendPage + 1), handler->sentSize);
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

Error:

    return PRT_RETURN_FALSE;
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

            trace_RequestCallback_Connect_OnFirstRead(ENGINE_TYPE, handler);

            onConnect(self, self->callbackData);
        }
        else
        {
            if (!_RequestCallbackWrite(handler))
            {
                LOGD2((ZT("_RequestCallback - _RequestCallbackWrite failed")));
                return MI_FALSE;
            }
            LOGD2((ZT("_RequestCallback - Called _RequestCallbackWrite. %u / %u bytes sent"),
                          (unsigned int)handler->sentSize, handler->sendPage == NULL ? 0 : (unsigned int)handler->sendPage->u.s.size));
            while (handler->sendPage != NULL && handler->sentSize < handler->sendPage->u.s.size)
            {                               /* assume 500 bytes per millisecond transmission */
                                            /* wait after to avoid spinning too much on _WriteData */
                /* unsigned int bytesLeft = (unsigned int)handler->sendPage->u.s.size - (unsigned int)handler->sentSize; */
                /* unsigned long msec = (unsigned long)(bytesLeft / 500 + 1); */

                LOGD2((ZT("_RequestCallback - Called _WriteClientData. %u / %u bytes sent"), 
                              (unsigned int)handler->sentSize, handler->sendPage == NULL ? 0 : (unsigned int)handler->sendPage->u.s.size));
                if (_WriteClientData(handler) == MI_FALSE)
                {
                    LOGE2((ZT("_RequestCallback - _WriteClientData failed")));
                    return MI_FALSE;
                }
                LOGD2((ZT("_RequestCallback - Called _WriteClientData. %u bytes written, %u bytes left"), 
                              (unsigned int)handler->sentSize, handler->sendPage == NULL ? 0 : (unsigned int)handler->sendPage->u.s.size));
                Sleep_Milliseconds(10);
            }
            LOGD2((ZT("_RequestCallback - Called _RequestCallbackWrite. %u / %u bytes sent"), 
                              (unsigned int)handler->sentSize, handler->sendPage == NULL ? 0 : (unsigned int)handler->sendPage->u.s.size));
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
        /* Yeah, this is hokey, but we need to sleep here to let the */
        /* subsystems have the opportunity to send the data before we close */
        /* the socket, or we'll get a broken pipe/connection reset */
        usleep(50);

        if (handler->username)
        {
            PAL_Free(handler->username);
            handler->username = NULL;
        }
    
        if (handler->user_domain)
        {
            PAL_Free(handler->user_domain);
            handler->user_domain = NULL;
        }
    
        if (handler->password)
        {
            PAL_Free(handler->password);
            handler->password = NULL;
        }

        if (handler->hostname)
        {
            PAL_Free(handler->hostname);
            handler->hostname = NULL;
        }

        if (handler->hostHeader)
        {
            PAL_Free(handler->hostHeader);
            handler->hostname = NULL;
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
    const char* privateKeyFile,
    SSL_Options sslOptions)
{
    SSL_CTX *sslContext;

    if (CreateSSLContext(&sslContext, sslOptions) != MI_RESULT_OK)
        return MI_RESULT_FAILED;

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
    MI_Boolean secure)
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
    h->sessionId = self->sessionId;

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
    h->base.handlerName = MI_T("HTTP_CLIENT");

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
        trace_SelectorAddHandler_Failed(ENGINE_TYPE);
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
        {
            return MI_RESULT_FAILED;
        }
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



Page* _CreateHttpHeader(
    const char* verb,
    const char* uri,
    const char* contentType,
    const char* authHeader,
    const char* hostHeader,
    const char* sessionCookie,
    HttpClientRequestHeaders *extraHeaders,
    size_t size)
{
    Page* page = 0;
    size_t pageSize = 0;
    int r;
    char* p;
    size_t sessionCookieLen = 0;

    static const char HTTP_PROTOCOL_HEADER[]     = "HTTP/1.1";
    static const char HTTP_PROTOCOL_HEADER_LEN = MI_COUNT(HTTP_PROTOCOL_HEADER)-1;

    static const char CONTENT_LENGTH_HEADER[]     = "Content-Length: ";
    static const char CONTENT_LENGTH_HEADER_LEN = MI_COUNT(CONTENT_LENGTH_HEADER)-1;

    static const char CONNECTION_HEADER[] = "Connection: ";
    static const char CONNECTION_HEADER_LEN = MI_COUNT(CONNECTION_HEADER)-1;

    static const char CONNECTION_KEEPALIVE[] = "Keep-Alive";
    static const char CONNECTION_KEEPALIVE_LEN = MI_COUNT(CONNECTION_KEEPALIVE)-1;

    static const char COOKIE_HEADER[] = "Cookie: ";
    #define COOKIE_HEADER_LEN (MI_COUNT(COOKIE_HEADER)-1)

    pageSize += Strlen(hostHeader) + 2;
    if (extraHeaders)
    {
        int i;
        for (i = 0; i < extraHeaders->size; ++i)
        {
            pageSize += Strlen(extraHeaders->data[i]) + 2;
        }
    }

    if (sessionCookie)
    {
        sessionCookieLen = Strlen(sessionCookie);
        pageSize += sessionCookieLen + COOKIE_HEADER_LEN + 2;
    }

    /* calculate approximate page size */
    if (!verb)
        verb = "POST";

    int verb_len = Strlen(verb);
    int uri_len  = Strlen(uri);

    pageSize += HTTP_PROTOCOL_HEADER_LEN + 2 +
                CONTENT_LENGTH_HEADER_LEN + 10 + 2 +
                CONNECTION_HEADER_LEN+CONNECTION_KEEPALIVE_LEN+2; /* format + 10 digits of content length */

    if (SizeTAdd(pageSize, verb_len, &pageSize) != S_OK ||
        SizeTAdd(pageSize, uri_len,  &pageSize) != S_OK ||
        SizeTAdd(pageSize, sizeof(Page), &pageSize) != S_OK ||
        (contentType && SizeTAdd(pageSize, Strlen(contentType), &pageSize) != S_OK) ||
        (authHeader  && SizeTAdd(pageSize, Strlen(authHeader), &pageSize) != S_OK)  || 
        SizeTAdd(pageSize, 2, &pageSize) != S_OK )
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

    // r = Snprintf(p, pageSize, HTTP_HEADER_FORMAT, verb, uri, (int)size);

    // POST http://something-wonderful/blah HTTP/1.1\r\n

    memcpy(p, verb, verb_len);
    p += verb_len;
 
    *p++ = ' ';

    memcpy(p, uri, uri_len);
    p += uri_len;
 
    *p++ = ' ';

    memcpy(p, HTTP_PROTOCOL_HEADER, HTTP_PROTOCOL_HEADER_LEN);
    p += HTTP_PROTOCOL_HEADER_LEN;

    memcpy(p, "\r\n", 2);
    p += 2;

    // Connection: KeepAlive\r\n
    memcpy(p, CONNECTION_HEADER, CONNECTION_HEADER_LEN);
    p += CONNECTION_HEADER_LEN;

    memcpy(p, CONNECTION_KEEPALIVE, CONNECTION_KEEPALIVE_LEN);
    p += CONNECTION_KEEPALIVE_LEN;

    memcpy(p, "\r\n", 2);
    p += 2;

    // Content-Length: 256\r\n
    memcpy(p, CONTENT_LENGTH_HEADER, CONTENT_LENGTH_HEADER_LEN);
    p += CONTENT_LENGTH_HEADER_LEN;

    {
        char numbuff[16] = {0};
        int  numstr_len = 0;
        char *pnumstr = int64_to_a(numbuff, sizeof(numbuff), size, &numstr_len);

        memcpy(p, pnumstr, numstr_len);
        p += numstr_len;
    }

    memcpy(p, "\r\n", 2);
    p += 2;

    pageSize -= (p-((char*)(page+1)));

    if (contentType)
    {
        r = (int)Strlcpy(p, contentType, pageSize);
        p += r;
        pageSize -= r;
        memcpy(p, "\r\n", 2);
        p += 2;
        pageSize -= 2;
    }

    if (authHeader)
    {
        r = (int)Strlcpy(p, authHeader, pageSize);
        p += r;
        pageSize -= r;
        memcpy(p, "\r\n", 2);
        p += 2;
        pageSize -= 2;
    }

    if (hostHeader)
    {
        r = (int)Strlcpy(p, hostHeader, pageSize);
        p += r;
        pageSize -= r;
    }

    if (sessionCookie)
    {
        memcpy(p, COOKIE_HEADER, COOKIE_HEADER_LEN);
        p += COOKIE_HEADER_LEN;
        
        memcpy(p, sessionCookie, sessionCookieLen);
        p += sessionCookieLen;

        memcpy(p, "\r\n", 2);
        p += 2;
        
        pageSize -= COOKIE_HEADER_LEN + sessionCookieLen + 2;
    }

    if (extraHeaders)
    {
        int i;
        for (i = 0; i < extraHeaders->size; ++i)
        {
            r = (int)Strlcpy(p, extraHeaders->data[i], pageSize);
            p += r;
            pageSize -= r;
            memcpy(p, "\r\n", 2);
            p += 2;
            pageSize -= 2;
        }
    }

    /* add trailing \r\n */
    memcpy(p, "\r\n", 2);
    p += 2;
    pageSize -= 2;

    page->u.s.size = (unsigned int)(p - (char*)(page+1));

    return page;
}


static Page* _CreateHttpAuthRequest(
    const char* verb,
    const char* uri,
    const char* contentType,
    const char* authHeader,
    const char*hostHeader)
{
    Page* page = 0;
    size_t pageSize = 0;
    int r;
    char* p;

#define HTTP_HEADER_FORMAT_NOCL "%s %s HTTP/1.1\r\n" \
    "Connection: Keep-Alive\r\n" \
    "Content-Length: 0\r\n" \

    /* calculate approximate page size */
    if (!verb)
        verb = "POST";

    pageSize += sizeof(HTTP_HEADER_FORMAT_NOCL) + 10; /* format + 10 digits of content length */

    if (SizeTAdd(pageSize, Strlen(verb), &pageSize) != S_OK ||
        SizeTAdd(pageSize, Strlen(uri),  &pageSize) != S_OK ||
        SizeTAdd(pageSize, sizeof(Page), &pageSize) != S_OK ||
        (contentType && SizeTAdd(pageSize, Strlen(contentType), &pageSize) != S_OK) ||
        (authHeader  && SizeTAdd(pageSize, Strlen(authHeader), &pageSize) != S_OK) ||
        (hostHeader  && SizeTAdd(pageSize, Strlen(hostHeader), &pageSize) != S_OK) )
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

    if (hostHeader)
        {
        r = (int)Strlcpy(p, hostHeader, pageSize);
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
    _Out_opt_ MI_Boolean *pPrivacy,
    _Out_opt_ const MI_Char **pTransport,
    _Out_opt_ char **pTrustedCertsDir,
    _Out_opt_ char **pCertFile,
    _Out_opt_ char **pPrivateKeyFile,
    _Out_opt_ char **pSessionId,
    SSL_Options *sslOptions)
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

    MI_Uint32 option;
    if (MI_DestinationOptions_GetSslOptions(pDestOptions, &option) == MI_RESULT_OK)
    {
        *sslOptions = (SSL_Options)option;
    }
    else
    {
        *sslOptions = 0;
    }

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
    else if (Tcscasecmp(userCredentials.authenticationType, AUTH_NAME_NEGOTIATE) == 0) 
    {
        method = AUTH_METHOD_NEGOTIATE;
    }
    else if (Tcscasecmp(userCredentials.authenticationType, AUTH_NAME_NEGOTIATE_WITH_CREDS) == 0) 
    {
        method = AUTH_METHOD_NEGOTIATE_WITH_CREDS;
    }
    else if (Tcscasecmp(userCredentials.authenticationType,  AUTH_NAME_KERBEROS) == 0) 
    {
        method = AUTH_METHOD_KERBEROS;
    }

    // We only output it if it is wanted.

    if (pAuthType)
    {
        *pAuthType = method;
    }

    if (method == AUTH_METHOD_UNSUPPORTED)
    {
        // Log here
        LOGE2((ZT("_UnpackDestinationOptions: Authorisation type (%s) is not supported."), userCredentials.authenticationType));
        result = MI_RESULT_ACCESS_DENIED;
        goto Done;
    }         


    if (userCredentials.credentials.usernamePassword.username)
    {
        username_len = Tcslen(userCredentials.credentials.usernamePassword.username);
        if (username_len > USERNAME_LIMIT)
        {
            result = MI_RESULT_INVALID_PARAMETER;
            trace_Username_Error(username_len);
            goto Done;
        }
        
        username = (char*) PAL_Malloc(username_len+1);
        if (username == NULL)
        {
            result = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            goto Done;
        }
        memcpy(username, userCredentials.credentials.usernamePassword.username, username_len+1);
        username[username_len] = 0;
    }
    else
    {
        if (method == AUTH_METHOD_BASIC)
        {
            LOGE2((ZT("_UnpackDestinationOptions: Authorisation type Basic requires username.")));
            result = MI_RESULT_ACCESS_DENIED;
            goto Done;
        }
    }

    if (pUsername) 
    {
        *pUsername = username;
    }

    /* We need to allocate a buffer for the password.
     * Get length of it, allocate and then retrieve it.
     */

    if (MI_DestinationOptions_GetCredentialsPasswordAt(pDestOptions, 0, (const MI_Char **)&optionName, NULL, 0, &password_len, NULL) != MI_RESULT_OK)
    {
        if (method == AUTH_METHOD_BASIC)
        {
            LOGE2((ZT("_UnpackDestinationOptions: Authorisation type requires password.")));
            result = MI_RESULT_ACCESS_DENIED;
            goto Done;
        }
    }

    if (password_len <= 0)
    {
        if (method == AUTH_METHOD_BASIC)
        {
            LOGE2((ZT("_UnpackDestinationOptions: Authorisation type requires password.")));
            result = MI_RESULT_ACCESS_DENIED;
            goto Done;
        }
    }
    else 
    {
        if (password_len > PASSWORD_LIMIT)
        {
           result = MI_RESULT_INVALID_PARAMETER;
           trace_Password_Error(password_len);
           goto Done;
        }
        password = (char*) PAL_Malloc(password_len);
        if (password == NULL)
        {
            result = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            goto Done;
        }

        if (MI_DestinationOptions_GetCredentialsPasswordAt(pDestOptions, 0, (const MI_Char **)&optionName, (MI_Char *)password, password_len, &password_len, NULL) != MI_RESULT_OK)
        {
            result = MI_RESULT_FAILED;
            goto Done;
        }
    }

    if (pPassword)
    {
        *pPassword = password;
    }
    

    if (pPasswordLen)
    {
        *pPasswordLen = password_len;
    }

    if (pTransport)
    {
        // We just return the string and do the processing later using tcscasecmp
   
        if (MI_DestinationOptions_GetTransport(pDestOptions, pTransport) == MI_RESULT_OK)
        {
            *pTransport = MI_T("HTTPS");
        }
    }

    if (pPrivacy)
    {
        if (MI_DestinationOptions_GetPacketPrivacy(pDestOptions, pPrivacy) != MI_RESULT_OK)
        {
            *pPrivacy = FALSE;
        }
    }

    if (pTrustedCertsDir)
    { 
        const MI_Char *tmpval = NULL;

        *pTrustedCertsDir = NULL;

        if (MI_DestinationOptions_GetTrustedCertsDir(pDestOptions, &tmpval) == MI_RESULT_OK)
        {
        

            // Copy the string into a char array because an MI_Char can be 1,2, or 4 bytes wide depending on 
            // the build options. We need it to be specificly char

            *pTrustedCertsDir = PAL_Malloc(Tcslen(tmpval)+1   + 10); // Add slop
            StrTcslcpy(*pTrustedCertsDir, tmpval, Tcslen(tmpval)+1);
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

            *pCertFile = PAL_Malloc(Tcslen(tmpval)+1    +10);  // Add slop
            StrTcslcpy(*pCertFile, tmpval, Tcslen(tmpval)+1);
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
            *pPrivateKeyFile = PAL_Malloc(Tcslen(tmpval)+1);       // Add slop
            StrTcslcpy(*pPrivateKeyFile, tmpval, Tcslen(tmpval)+1);
        }
    }

  if (pSessionId)
    {
        const MI_Char *tmpval = NULL;

        *pSessionId = NULL;
        if (MI_DestinationOptions_GetString(pDestOptions, MI_T("WSMAN_SESSION_ID"), &tmpval, NULL) == MI_RESULT_OK)
        {
            size_t len = Tcslen(tmpval) + 1;
            // Copy the string into a char array because an MI_Char can be 1,2, or 4 bytes wide depending on 
            // the build options. We need it to be specificly char
            *pSessionId = PAL_Malloc(len);  
            StrTcslcpy(*pSessionId, tmpval, len);
        }
    }
Done:

    if (result != MI_RESULT_OK)
    {
        if (username)
        {
            PAL_Free(username);
        }

        if (password)
        {
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

    The old interface did not do authorisation. It only used SSL and handled 
    authentication outboard via request and response callbacks

    The new interface carries the all of the options for authorisation and ssl provisioning via 
    MiDestinationOptions.

    compatibility arguments (null otherwise): 
       const char* trustedCertsDir,
       const char* certFile,
       const char* privateKeyFile
       MI_DestinationOptions *pDestOptions = NULL
    

    new style arguments:
       const char* trustedCertsDir == NULL, ignored
       const char* certFile        == NULL, ignored
       const char* privateKeyFile  == NULL, ignored
       MI_DestinationOptions *pDestOptions

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
    const char* trustedCertsDir,
    const char* certFile,
    const char* privateKeyFile)

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
            trustedCertsDir,
            certFile,
            privateKeyFile,
            NULL );
}

int SSL_Init_Fn(
    _In_ void* data,
    _Outptr_result_maybenull_ void** value)
{
    SSL_library_init();
    return 0;
}

MI_Result HttpClient_New_Connector2(
    HttpClient** clientOut,
    Selector* selector, /*optional, maybe NULL*/
    const char* host,
    unsigned short port,
    MI_Boolean secure,
    HttpClientCallbackOnConnect statusConnect,
    HttpClientCallbackOnStatus2 statusCallback,
    HttpClientCallbackOnResponse  responseCallback,
    void* callbackData,
    const char* trustedCertsDir,
    const char* certFile,
    const char* privateKeyFile,
    MI_DestinationOptions *pDestOptions)

{
    HttpClient* client;
    MI_Result r;
    char* trusted_certs_dir = (char*)trustedCertsDir;
    char* cert_file         = (char*)certFile;
    char* private_key_file  = (char*)privateKeyFile;
    static Once sslInit = ONCE_INITIALIZER;
 
    MI_Boolean privacy      = TRUE;
    const MI_Char *transport = MI_T("HTTPS");

    AuthMethod authtype =  AUTH_METHOD_BYPASS;
    char *username = NULL;
    char *user_domain = NULL;
    char *password    = NULL;
    MI_Uint32 password_len = 0;
    SSL_Options sslOptions;

    static const Probable_Cause_Data CONNECT_ERROR = {
                     ERROR_WSMAN_DESTINATION_UNREACHABLE,
                     WSMAN_CIMERROR_PROBABLE_CAUSE_CONNECTION_ERROR,
                     MI_T("Could not connect") 
               };

    const static Probable_Cause_Data ENCRYPTION_NOT_AVAILABLE_ERROR = {
          ERROR_ACCESS_DENIED,
          WSMAN_CIMERROR_PROBABLE_CAUSE_AUTHENTICATION_FAILURE,
          MI_T("Encryption available only in Kerberos or SPNEGO authentication"),
          NULL
    };

    /* allocate this, inits selector */
    r = _New_Http(clientOut, selector, statusConnect, statusCallback,
                  responseCallback, callbackData);
    client = *clientOut;
    if (MI_RESULT_OK != r)
    {
        client->probableCause = (Probable_Cause_Data *)&CONNECT_ERROR;
        LOGE2((ZT("HttpClient_New_Connector - _New_Http failed. result: %d (%s)"), r, mistrerror(r)));
        goto Error;
    }

    if (pDestOptions)
    {
        r = _UnpackDestinationOptions(pDestOptions, &authtype, &username, &password, &password_len, &privacy, &transport,
                                      &trusted_certs_dir, &cert_file, &private_key_file, &client->sessionId, &sslOptions);

        if (MI_RESULT_OK != r)
        {
            client->probableCause = (Probable_Cause_Data *)&CONNECT_ERROR;
            LOGE2((ZT("HttpClient_New_Connector - _UnpackDestinationOptions failed. result: %d (%s)"), r, mistrerror(r)));
            goto Error;
        }
        
        if (privacy && !secure)
        {
            switch(authtype)
            {
            case AUTH_METHOD_NEGOTIATE:
            case AUTH_METHOD_NEGOTIATE_WITH_CREDS:
            case AUTH_METHOD_KERBEROS:
                // Gss encryption is legal
                break;
            default:
                // Basic auth and anything esle so far implemented, http encryption is not allowed/possible
                client->probableCause = (Probable_Cause_Data *)&ENCRYPTION_NOT_AVAILABLE_ERROR;
                LOGE2((ZT("HttpClient_New_Connector - _UnpackDestinationOptions invalid option combination. HTTP encryption is only available with Negotiate, NegoWithCrreds or Kerberos auth types.")));
                r = MI_RESULT_ACCESS_DENIED;
                goto Error;
            }
        }
    }

#ifdef CONFIG_POSIX
    /* Allocate SSL context */
    if (secure)
    {
        /* init ssl */
        Once_Invoke(&sslInit, SSL_Init_Fn, NULL);

        /* create context */
        r = _CreateSSLContext(client, trusted_certs_dir, cert_file, private_key_file, sslOptions);

        if (r != MI_RESULT_OK)
        {
            client->probableCause =(Probable_Cause_Data*) &CONNECT_ERROR;
            LOGE2((ZT("HttpClient_New_Connector - _CreateSSLContext failed. result: %d (%s)"), r, mistrerror(r)));
            goto Error;
        }
    }
#else
    MI_UNUSED(secure);
#endif

    /* Create http connector socket. This also creates the HttpClient_SR_Data */
    {
        r = _CreateConnectorSocket(client, host, port, secure);

        if (r != MI_RESULT_OK)
        {
            client->probableCause = (Probable_Cause_Data*)&CONNECT_ERROR;
            LOGE2((ZT("HttpClient_New_Connector - _CreateConnectorSocket failed. result: %d (%s)"), r, mistrerror(r)));
            goto Error;
        }

        // If we have an authorisation method, eg Basic, Negotiate, etc, we are not yet authorised. But if there is none, then
        // go ahead if the server will let you, Hint, it probably won't

        if (!client->connector)
        {
            client->probableCause = (Probable_Cause_Data*)&CONNECT_ERROR;
            LOGE2((ZT("HttpClient_New_Connector - _CreateConnectorSocket did not initialise.")));
            goto Error;
        }

        client->connector->isAuthorized = (authtype == AUTH_METHOD_NONE);
        client->connector->authorizing  = FALSE;

        // Never encrypt when the auth method doesn't allow for a gss context.
        // Never encrypt over https.
        //
        client->connector->isPrivate    = privacy && !secure; // We already checked the authtype
        client->connector->encrypting   = FALSE; // The auth will establish this
        client->connector->readyToSend  = FALSE;
        client->connector->negoFlags    = FALSE;
        client->connector->hostname     = PAL_Strdup(host);

        static const char HOST_HEADER[] = "Host: ";
        int host_header_size_required = strlen(host)+sizeof(HOST_HEADER)+10; // 10 == max length of port plus CRLF

        client->connector->hostHeader = PAL_Malloc(host_header_size_required);
        char *h_hdr_p = client->connector->hostHeader+sizeof(HOST_HEADER)-1;

        memcpy(client->connector->hostHeader, HOST_HEADER, sizeof(HOST_HEADER));

        if (client->connector->hostname)
        {
            Strlcpy(h_hdr_p, host, host_header_size_required);
            h_hdr_p += strlen(host);
        }
        else
        {
            Strlcpy(h_hdr_p, "host", host_header_size_required);
            h_hdr_p += strlen(host);
        }

        *h_hdr_p++ = ':';
        char port_str[10] = {0};
        sprintf(port_str, "%u", port);
        strcpy(h_hdr_p, port_str);
        h_hdr_p += strlen(port_str);
        *h_hdr_p++ = '\r';
        *h_hdr_p++ = '\n';
        *h_hdr_p++ = '\0';

        // Parse the user name to separate the domain/host from the username. This is either in the form
        // domain\user or user@domain or just user. mit krb5 can handle either, but heimdal doesn't.
        // Once we have the domain sorted out we can use it later on in generating the target name so
        // it isn't a waste either way. Basic auth doesn't need parsing because PAM does the work there.

        if (username)
        { 

            if ( authtype == AUTH_METHOD_BASIC)
            {
                client->connector->username    = username;
                client->connector->user_domain = NULL;
            }
            else if ( authtype == AUTH_METHOD_NEGOTIATE ||
                      authtype == AUTH_METHOD_NEGOTIATE_WITH_CREDS ||
                      authtype == AUTH_METHOD_KERBEROS) 
            {
                user_domain = strchr(username, '\\');
                if (user_domain)
                {
                    // The form would be "domain\user'
                    *user_domain = '\0';
                    client->connector->username    = PAL_Strdup(user_domain+1);
                    client->connector->user_domain = username;
                }
                else
                {
                    user_domain = strchr(username, '@');
                    if (user_domain)
                    {
                        *user_domain = '\0';
                        client->connector->username    = username;
                        client->connector->user_domain = PAL_Strdup(user_domain+1);
                    }
                    else
                    {
                        // No credential domain specified
                        client->connector->username    = username;
                        client->connector->user_domain = PAL_Strdup((char*)host);
                    }
                }
            }
        }
        
        client->connector->authType = authtype;
        client->connector->password = (char*)password;
        client->connector->passwordLen = password_len;
        client->connector->authContext = NULL;
        client->connector->cred         = NULL;
        client->connector->selectedMech = AUTH_MECH_NONE;
        client->connector->errMsg       = NULL;
        if (Log_GetLevel() >= LOG_DEBUG)
        {    
            client->connector->enableTracing = TRUE;
        }    
        else 
        {
            client->connector->enableTracing = FALSE;
        }    
    }

    if (pDestOptions) 
    {
        if (trusted_certs_dir)
        {
            PAL_Free(trusted_certs_dir);
        }

        if (cert_file)
        {
            PAL_Free(cert_file);
        }

        if (private_key_file)
        {
            PAL_Free(private_key_file);
        }
    }

    return r;

Error:
    if (pDestOptions) 
    {
        if (trusted_certs_dir)
        {
            PAL_Free(trusted_certs_dir);
        }

        if (cert_file)
        {
            PAL_Free(cert_file);
        }

        if (private_key_file)
        {
            PAL_Free(private_key_file);
        }
    }
    *clientOut = NULL;
    ZChar *errmsg = NULL;

    if (client->connector)
    {
        if (password)
        {
            PAL_Free(password);
        }
        if (username)
        {
            PAL_Free(username);
        }
        errmsg = client->connector->errMsg;
    }

    if (client)
    {
         (*statusCallback)(client, client->callbackData, r, errmsg, client->probableCause );
         HttpClient_Delete(client);
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

    if (self->sslContext)
        SSL_CTX_free(self->sslContext);

    /* Clear magic number */
    self->magic = 0xDDDDDDDD;

    if (self->sessionId)
    {
        PAL_Free(self->sessionId);
    }

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
    HttpClientRequestHeaders *headers,
    Page** data)

{  char *content_type = NULL;
   char *auth_header  = NULL;
   HttpClientRequestHeaders extra_headers = { NULL, 0 };
   const char** tmp_headers = NULL;
   MI_Result rtnval = MI_RESULT_OK;

   static const char CONTENT_TYPE_HDR[]   = "Content-Type:";
   const size_t      CONTENT_TYPE_HDR_LEN = MI_COUNT(CONTENT_TYPE_HDR) - 1;
   static const char AUTH_HDR[]           = "Authorization:";
   const size_t      AUTH_HDR_LEN         = MI_COUNT(AUTH_HDR) - 1;

   if (headers)
   {
       tmp_headers = (headers->size != 0) ? (const char **)PAL_Malloc(sizeof(char *) * headers->size) : NULL;

       int i = 0;
       int j = 0;
       for (i = 0; i < headers->size; i++ ) 
       {
           if (Strncasecmp(headers->data[i], CONTENT_TYPE_HDR, CONTENT_TYPE_HDR_LEN) == 0)
           {
               content_type = (char *)headers->data[i];    
           }
           else if (Strncasecmp(headers->data[i],AUTH_HDR, AUTH_HDR_LEN) == 0)
           {
               auth_header = (char *)headers->data[i];
           }
           else 
           {
               tmp_headers[j] = (char *)headers->data[i];
               j++;
           }
       }

       extra_headers.data = tmp_headers;
       extra_headers.size = j;
   }

   if (extra_headers.size > 0 )
   {
       headers = &extra_headers;
   }
   else
   {
       headers = NULL;
   }

   if (auth_header) 
   {
       self->connector->authType = AUTH_METHOD_BYPASS;
   }
    
   rtnval = HttpClient_StartRequestV2(self, verb, uri, content_type, auth_header, headers, data, NULL  );
   
   if (tmp_headers != NULL)
   {
       // When extra_headers are used properly, please reassess whether this PAL_Free belongs here. 
       // This exists for now to prevent a memory leak.
       PAL_Free(tmp_headers);
   }

   return rtnval;
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

MI_Result HttpClient_StartRequestV2(
    HttpClient* client,
    const char* verb,
    const char* uri,
    const char*contentType,
    const char*authHeader,
    HttpClientRequestHeaders *extraHeaders,
    Page** data,
    const Probable_Cause_Data **cause)
{
    Http_CallbackResult ret;
    MI_Result           r;
    const char *auth_header = NULL;
    const char* sessionCookie = NULL;

    // Get the session cookie from the last response, if available
    sessionCookie = SessionMap_GetCookie(&_sessionMap, client->sessionId);

    LOGD2((ZT("HttpClient_StartRequest - Begin. verb: %s, URI: %s"), verb, uri));

    /* check params */
    if (!client || !uri)
    {
        r = MI_RESULT_INVALID_PARAMETER;
        goto Error;
    }

    if (!verb)
    {
        verb = "POST";
    }

    if (client->magic != _MAGIC)
    {
        LOGE2((ZT("HttpClient_StartRequest - Bad magic number")));
        trace_StartRequest_InvalidMagic();
        r = MI_RESULT_INVALID_PARAMETER;
        goto Error;
    }

    if (client->connector == NULL)
    {
        LOGE2((ZT("HttpClient_StartRequest - Connection is not open")));
        trace_StartRequest_ConnectionClosed();
        r = MI_RESULT_FAILED;
        goto Error;
    }

    if ( AUTH_METHOD_BASIC == client->connector->authType )
    {
        // Basic auth is only good for one request, then has to be reauthenticated

        client->connector->isAuthorized = FALSE;
    }    
    else if ( AUTH_METHOD_BYPASS == client->connector->authType )
    {
        // We are always authorized if we're bypassing authorization
        client->connector->isAuthorized = TRUE;
        auth_header = authHeader;
    }
            
    /* Do we need to authorise? */

    if (!client->connector->isAuthorized && !authHeader)
    {
        ret = HttpClient_RequestAuthorization(client->connector, &auth_header);
        switch (ret)
        {
        case PRT_RETURN_FALSE:
            // Not authorised. No auth header
            r = MI_RESULT_ACCESS_DENIED;
            goto Error;
           
        case PRT_CONTINUE:
            // We need to to the auth loop.

            if (client->connector->authType == AUTH_METHOD_BASIC)
            {
                 // Basic sends the payload first time

                 break;
            }

            client->connector->sendHeader =
                _CreateHttpAuthRequest(verb, uri, contentType, auth_header, client->connector->hostHeader);

            /* Save the request information until we are authorised */
            client->connector->verb = (char *)verb; // BAC Always "POST" but we keep it anyway. It seems to be a literal. Are they static?
            client->connector->uri  = (char *)uri;
            client->connector->contentType = (char *)contentType;

            /* We dont send the data until authorised */
            client->connector->data     = *data;
            client->connector->sendPage = NULL;

            /* set status to failed, until we know more details */
            client->connector->status = MI_RESULT_FAILED;
            client->connector->sentSize = 0;
            client->connector->sendingState = RECV_STATE_HEADER;

            if (_RequestCallbackWrite(client->connector) == MI_FALSE)
            {
                r = MI_RESULT_FAILED;
                goto Error;
            }

            return MI_RESULT_OK;

        case PRT_RETURN_TRUE:
            break;

        default:
            break;
        }
    }

    /* create header page */
    client->connector->sendHeader =
        _CreateHttpHeader(verb, uri, contentType, auth_header, client->connector->hostHeader, sessionCookie, extraHeaders, (data && *data) ? (*data)->u.s.size : 0);

    if (data != NULL)
    {
        client->connector->sendPage = *data;
        *data = 0;
    }
    else
    {
        client->connector->sendPage = NULL;
    }

    /* set status to failed, until we know more details */
    client->connector->status = MI_RESULT_FAILED;
    client->connector->sentSize = 0;
    client->connector->sendingState = RECV_STATE_HEADER;
    client->connector->base.mask |= SELECTOR_WRITE;

    if (_RequestCallbackWrite(client->connector) == MI_FALSE)
    {
        r = MI_RESULT_FAILED;
        goto Error;
    }

    if (auth_header && !authHeader)
    {
        PAL_Free((MI_Char*)auth_header);
    }

    return MI_RESULT_OK;

Error:

    if (cause)
    {
        *cause = client->probableCause;
    }
    (*(HttpClientCallbackOnStatus2)(client->callbackOnStatus)) (client, client->callbackData, r, client->connector->errMsg, client->probableCause );
    return r;

}

MI_Result HttpClient_Run(
    HttpClient* client,
    MI_Uint64 timeoutUsec)
{
    /* Run the selector */
    return Selector_Run(client->selector, timeoutUsec, MI_FALSE);
}

MI_Result HttpClient_SetTimeout(
    HttpClient* client,
    MI_Uint64 timeoutUsec)
{
    MI_Uint64 currentTimeUsec = 0;

    PAL_Time(&currentTimeUsec);

    /* check params */
    if (!client)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (client->magic != _MAGIC)
    {
        trace_Timeout_InvalidMagic();
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (!client->connector)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    /* create header page */
    client->connector->timeoutUsec = timeoutUsec;
    client->connector->base.fireTimeoutAt = currentTimeUsec + client->connector->timeoutUsec;

    return MI_RESULT_OK;
}

Selector *HttpClient_GetSelector(HttpClient *client)
{
    return client->selector;
}

MI_Result HttpClient_WakeUpSelector(HttpClient *client, MI_Uint64 whenTime)
{
    if (client->connector)
    {
        client->connector->base.fireTimeoutAt = whenTime;
        Selector_Wakeup(client->selector, MI_TRUE );
    }
    return MI_RESULT_OK;
}

int HttpClient_RemoveSession(_In_ const char * sessionId)
{
    return SessionMap_Remove(&_sessionMap, sessionId);
}
