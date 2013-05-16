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

#include <ctype.h>
#include "httpclient.h"
#include <sock/addr.h>
#include <sock/sock.h>
#include <sock/selector.h>
#include <base/time.h>
#include <base/buf.h>
#include <base/log.h>
#include <base/result.h>
#include <base/strings.h>
#include <io/io.h>
#include <base/paths.h>
#include <strings.h>
#include <sys/types.h>

#ifdef CONFIG_POSIX
#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <openssl/err.h>
#include <pthread.h>

#else
/* SSL not supported in this configuration; just make compiler happy */
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

#define T MI_T

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

static const MI_Uint32 _MAGIC = 0x5FC7B966;
static const MI_Uint32 MAX_HEADER_SIZE = 2 * 1024;
static const MI_Uint32 INITIAL_BUFFER_SIZE = 2 * 1024;
static const MI_Uint32 DEFAULT_HTTP_TIMEOUT_USEC = 10000000;

typedef enum _Http_RecvState
{
    RECV_STATE_HEADER,
    RECV_STATE_CONTENT,
    RECV_STATE_CHUNKHEADER,
    RECV_STATE_CHUNKDATA
}
Http_RecvState;

typedef struct _Http_SR_SocketData
{
    /* based member */
    Handler     base;
#define CHILD_TYPE_HTTPCLIENT_SR_CLIENT_SOCKETDATA    0x43534358

    /* timeout */
    MI_Uint64   timeoutUsec;

    /* SSL part */
    SSL* ssl;
    MI_Boolean  reverseOperations;  /*reverse read/write Events/Handlers*/
    MI_Boolean  connectDone;

    /* receiving data */
    char*       recvBuffer;
    size_t      recvBufferSize;
    size_t      receivedSize;
    Http_RecvState      receivingState;
    HttpClientHeaderField recvHeaderFields[64];
    HttpClientResponseHeader   recvHeaders;
    MI_Sint64   contentLength;
    Page*   recvPage;

    /* flag for a response from HEAD request */
    MI_Boolean  headVerb;

    /* sending part */
    Page*   sendPage;
    Page*   sendHeader;
    size_t      sentSize;
    Http_RecvState  sendingState;

    /* general operation status */
    MI_Result status;
}
Http_SR_SocketData;

struct _HttpClient
{
    MI_Uint32       magic;
    Selector        internalSelector;
    Selector*       selector;
    HttpClientCallbackOnStatus     callbackOnStatus;
    HttpClientCallbackOnResponse   callbackOnResponse;
    void*           callbackData;
    SSL_CTX*    sslContext;

    Http_SR_SocketData* connector;

    MI_Boolean  internalSelectorUsed;
};

/* helper functions result */
typedef enum _Http_CallbackResult
{
    PRT_CONTINUE,
    PRT_RETURN_TRUE,
    PRT_RETURN_FALSE
}
Http_CallbackResult;


/* locks */

static pthread_mutex_t deleteMutexLock;

void doHttpclientMutexStuff(int Lock)
{
    static pthread_mutex_t thisMethodLock;
    static pthread_mutex_t httpClientLock;
    static int mutexInitialized = 0;
    static int mutexlocked = 0;
    int failedTries = 0;

    if (mutexInitialized == 0)
    {
        pthread_mutex_init(&httpClientLock, NULL);
        pthread_mutex_init(&thisMethodLock, NULL);
        pthread_mutex_init(&deleteMutexLock, NULL);

        mutexInitialized = 1;
    }

try_again:
    pthread_mutex_lock(&thisMethodLock);

    if (Lock != 0)
    {
        int iStat = pthread_mutex_trylock(&httpClientLock);
        if (iStat != 0)
        {
            if (iStat != EBUSY)
            {
               perror("   ** ERROR LOCKING MUTEX: ");
            }
            else
            {
               LOGE2((ZT("dpHttpClientMutexStuff - Attempt to lock locked mutex")));
               failedTries++;
               if ((failedTries % 100) == 0)
               {
#if defined(CONFIG_ENABLE_DEBUG)
                   LOGE2((ZT("doHttpClientMutexStuff - POTENTIAL DEADLOCK DETECTED!!  ATTACH TO ME NOW!")));
#else
                   LOGE2((ZT("doHttpClientMutexStuff - POTENTIAL DEADLOCK DETECTED!!  Exiting..")));
                   exit(-1);
#endif
               }
               pthread_mutex_unlock(&thisMethodLock);
               usleep(50);
               goto try_again;
            }
        }
        else
        {
            mutexlocked++;
        }
    }
    else
    {
        if (0 != pthread_mutex_unlock(&httpClientLock))
        {
            perror("   ** ERROR UNLOCKING MUTEX: ");
        }
        mutexlocked--;
    }

    LOGD2((ZT("doMutexStuff - OK Exit. mutexlocked: %d"), mutexlocked));
    pthread_mutex_unlock(&thisMethodLock);
    return;
}

void lockHttpClientMutex(void)
{
    LOGD2((ZT("lockHttpClientMutex - Begin")));
    (void)doHttpclientMutexStuff(1);
}

void unlockHttpClientMutex(void)
{
    LOGD2((ZT("unlockHttpClientMutex - Begin")));
    (void)doHttpclientMutexStuff(0);
}

MI_INLINE MI_Uint8 _ToLower(MI_Uint8 x)
{
    return (MI_Uint8)tolower(x);
}

#define _HashCode(first,last,len) ( (((MI_Uint8)first) << 16) | (((MI_Uint8)last) << 8)  | (((MI_Uint16)len)) )

static MI_Boolean _getNameValuePair(
    char ** line,
    char ** value,
    int*  nameHashCode)
{
    int len = 0;
    char* p;

    /* find name end /hash-code */

    *nameHashCode = _ToLower((MI_Uint8)(*line)[0])<<16;

    for (len = 1; (*line)[len] != ':' && (*line)[len] != '\r'; len++)
        ;

    if ((*line)[len] != ':')
        return MI_FALSE;

    *nameHashCode |=  (len) | _ToLower((MI_Uint8)(*line)[len-1])<<8;
    (*line)[len] = '\0';
    p = *line + len + 1;

    /* skip spaces in value */
    while (p[0] == ' ' || p[0] == '\t')
    {
        p++;
    }

    *value = p;

    /* skip to end of line */
    for ( ; ; )
    {
        if (p[0] == '\r' && p[1] == '\n' &&
            p[2] != ' ' && p[2] != '\t')
        {
            p[0] = '\0';
            (*line) = p + 2;
            break;
        }
        p ++;
    }

    /* remove trailing spaces */
    p--;
    while (p[0] == ' ' || p[0] == '\t')
        p--;

    p[1] = '\0';

    return MI_TRUE;
}

static MI_Boolean _getHeaderField(
    Http_SR_SocketData* handler,
    char ** line)
{
    /* expecting  Request-Line = Method SP Request-URI SP HTTP-Version CRLF
        Read more: http://www.faqs.org/rfcs/rfc2616.html#ixzz0jKdjJdZv
    */
    char* name = *line;
    char* value = NULL;
    int nameHashCode;

    if (!_getNameValuePair(line, &value, &nameHashCode))
        return MI_FALSE;

    if (nameHashCode == _HashCode('c','h',14) && /*Content-Length*/
        Strcasecmp(name,"Content-Length") == 0)
    {
            handler->contentLength = Strtoull(value, NULL, 10);
            /*if (handler->contentLength > HTTP_MAX_CONTENT)
                return MI_FALSE;*/
    }
    else if (nameHashCode == _HashCode('t','g',17) && /*Transfer-Encoding*/
        Strcasecmp(name,"Transfer-Encoding") == 0)
    {
            handler->contentLength = -1;
    }

    // Add fields to the header name/value map
    if (handler->recvHeaders.sizeHeaders < MI_COUNT(handler->recvHeaderFields))
    {
        handler->recvHeaderFields[handler->recvHeaders.sizeHeaders].name = name;
        handler->recvHeaderFields[handler->recvHeaders.sizeHeaders].value = value;
        handler->recvHeaders.sizeHeaders++;
    }
    else
    {
        LOGW((ZT("_GetHeaderField - Too many HTTP headers. Skipping %s: %s"), name, value));
        LOGW2((ZT("_GetHeaderField - Too many HTTP headers. Skipping %s: %s"), name, value));
    }

    return MI_TRUE;
}

static MI_Boolean _getChunkSize(
    const char* line,
    MI_Uint32* chunkSize)
{
    *chunkSize = 0;

    while(*line)
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
    Http_SR_SocketData* handler,
    char ** line)
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
        const char* s = *line + 9; /*+ HTTP/1.1<sp>*/

        handler->recvHeaders.httpError = Strtoul(s, NULL, 10);
    }

    /* skip to end of line */
    for (index = 1; index < handler->receivedSize; index++)
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
    Http_SR_SocketData* handler,
    void* buf,
    size_t buf_size,
    size_t* sizeRead)
{
    int res;
    int sslError;

    if (handler == NULL || buf == NULL)
    {
        return MI_RESULT_FAILED;
    }

    if (handler->ssl == NULL)
    {
        LOGD2((ZT("_Sock_Read - Beginning regular read. socket %d"), handler->base.sock));
        MI_Result res = Sock_Read(handler->base.sock, buf, buf_size, sizeRead);
        LOGD2((ZT("_Sock_Read - After regular read. socket: %d, result: %d (%s), bytes read: %u / %u"), handler->base.sock, (int)res, mistrerror(res), (unsigned int)*sizeRead, (unsigned int)buf_size));
        return res;
    }

    LOGD2((ZT("_Sock_read - SSL_read. socket: %d"), handler->base.sock));

    handler->base.mask &= ~SELECTOR_WRITE;
    handler->base.mask |= SELECTOR_READ;
    handler->reverseOperations = MI_FALSE;

    *sizeRead = 0;

    errno = 0;
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

    case SSL_ERROR_SSL:
        {
            unsigned long err = ERR_get_error();

            LOGW((ZT("_Sock_Read - SSL_read returned OpenSSL error %d (%s)"), err, ERR_error_string(err, NULL)));
            LOGD2((ZT("_Sock_Read - SSL_read returned OpenSSL error %d (%s)"), err, sslstrerror(sslError)));
		}
        break;

    case SSL_ERROR_SYSCALL:
        if (EAGAIN == errno ||
            EWOULDBLOCK == errno ||
            EINPROGRESS == errno)
        {
            return MI_RESULT_WOULD_BLOCK;
        }

        LOGW((ZT("_Sock_Read - SSL_read returned OS error %d (%s)"), errno, strerror(errno)));
        LOGE2((ZT("Sock_Read - SSL_read returned OS error %d (%s)"), errno, strerror(errno)));
        break;

    default:
        /* print Open SSL error stack */
        {
            unsigned long err;
            while ((err = ERR_get_error()) != 0)
            {
                char err_txt[200];

                ERR_error_string_n(err, err_txt, sizeof (err_txt));
                LOGW((ZT("_Sock_Read - SSL_read returned OpenSSL error: %lu (%s)"), err, err_txt));
                LOGE2((ZT("_Sock_Read - SSL_read returend OpenSSL error: %lu (%s)"), err, err_txt));
            }
        }
        break;
    }

    return MI_RESULT_FAILED;
}

static MI_Result _Sock_Write(
    Http_SR_SocketData* handler,
    void* buf,
    size_t buf_size,
    size_t* sizeWritten)
{
    int res;
    int sslError;

    if (handler->ssl == NULL)
    {
        LOGD2((ZT("_Sock_Write - Non SSL write. socket: %d, bytes: %u"), handler->base.sock, (unsigned int)buf_size));
        MI_Result res = Sock_Write(handler->base.sock, buf, buf_size, sizeWritten);
        LOGD2((ZT("_Sock_Write - Sock_Write returned %d. %u / %u bytes sent"), res, (unsigned int)*sizeWritten, (unsigned int)buf_size));
        return res;
    }

    LOGD2((ZT("_Sock_Write - SSL %s on socket: %d"), handler->connectDone ? "write" : "connect", handler->base.sock));

    /* Do not clear READ flag, since 'close' notification is delivered as READ event */
    handler->base.mask &= ~SELECTOR_READ;
    handler->base.mask |= SELECTOR_WRITE;
    handler->reverseOperations = MI_FALSE;

    *sizeWritten = 0;

    if (handler->connectDone)
    {
        errno = 0;
        res = SSL_write(handler->ssl, buf, buf_size);
        LOGD2((ZT("_Sock_Write - SSL_write returned %d (< 0 for error) / %u bytes written, errno: %d (%s)"), res, (unsigned int)buf_size, errno, strerror(errno)));
    }
    else
    {
        errno = 0;
        res = SSL_connect(handler->ssl);
        LOGD2((ZT("_Sock_Write - SSL connect returned result: %d, errno: %d (%s)"), res, errno, strerror(errno)));
        if (res > 0)
        {
            /* we are done with accept */
            handler->connectDone = MI_TRUE;
            LOGD2((ZT("_Sock_Write - SSL recursive write. socket: %d"), handler->base.sock));
            return _Sock_Write(handler, buf, buf_size, sizeWritten);
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
        LOGD2((ZT("_Sock_Write - SSL socket successful write of %d / %u bytes"), res, (unsigned int)buf_size));
        *sizeWritten = res;
        return MI_RESULT_OK;    /* ok */
    }

    // Handle errors
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

    case SSL_ERROR_SSL:
        {
            LOGW((ZT("_Sock_Write - SSL_write/connect returned OpenSSL error %d (%s)"), sslError, ERR_error_string(sslError, NULL)));
            LOGE2((ZT("_Sock_Write - SSL_write/connect returned OpenSSL error %d (%s)"), sslError, ERR_error_string(sslError, NULL)));
        }
        break;

    case SSL_ERROR_SYSCALL:
        if (EAGAIN == errno ||
            EWOULDBLOCK == errno ||
            EINPROGRESS == errno)
        {
            handler->reverseOperations = MI_TRUE;   /* wait until write is allowed */
            handler->base.mask |= SELECTOR_READ;
            handler->base.mask &= ~SELECTOR_WRITE;

            LOGD2((ZT("_Sock_Write - Returning WOULD_BLOCK. errno: %d (%s)"), errno, strerror(errno)));
            return MI_RESULT_WOULD_BLOCK;
        }

        LOGW((ZT("_Sock_Write - SSL_write/connect returned unexpected OS error %d (%s)"), errno, strerror(errno)));
        LOGE2((ZT("_Sock_Write - SSL_write/connect returned unexpected OS error %d (%s)"), errno, strerror(errno)));
        break;

    default:
        LOGD2((ZT("_Sock_Write - SSL_write/connect returned uncategorized OpenSSL error: %d"), res));
        break;
    }
    LOGE2((ZT("_Sock_Write - Returning FAILED. errno: %d (%s)"), errno, strerror(errno)));
    return MI_RESULT_FAILED;
}

static Http_CallbackResult _ReadHeader(
    Http_SR_SocketData* handler)
{
    char* buf;
    char* currentLine;
    char* data;
    size_t buf_size, received, index;
    size_t contentSize;
    MI_Result r;
    MI_Boolean fullHeaderReceived = MI_FALSE;

    lockHttpClientMutex();
    LOGD2((ZT("_ReadHeader - Locked mutex")));

    /* are we done with header? */
    if (handler->receivingState != RECV_STATE_HEADER)
    {
        unlockHttpClientMutex();
        return PRT_CONTINUE;
    }

    buf = handler->recvBuffer + handler->receivedSize;
    buf_size = handler->recvBufferSize - handler->receivedSize;
    received = 0;

    handler->status = MI_RESULT_OK;
    r = _Sock_Read(handler, buf, buf_size, &received);
    LOGD2((ZT("_ReadHeader - _Sock_read result: %d (%s), socket: %d, %u / %u bytes read, reverse: %d"), (int)r, mistrerror(r), (int)handler->base.sock, (unsigned int)received, (unsigned int)buf_size, (int)handler->reverseOperations));

    if (r == MI_RESULT_OK && received == 0)
    {
        unlockHttpClientMutex();
        LOGW2((ZT("_ReadHeader - 0 bytes received without error. Socket closed?")));
        return PRT_RETURN_FALSE; /* connection closed */
    }

    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        unlockHttpClientMutex();
        LOGE2((ZT("_ReadHeader - Error %d (%s)"), r, mistrerror(r)));
        return PRT_RETURN_FALSE;
    }

    if (received == 0)
    {
        unlockHttpClientMutex();
        LOGD2((ZT("_ReadHeader - 0 bytes received. Waiting...")));
        return PRT_RETURN_TRUE;
    }

    handler->receivedSize += received;

    /* check header */
    LOGD2((ZT("_ReadHeader - Received buffer: %s"), buf));

    /* did we get full header? */
    buf = handler->recvBuffer;
    LOGD2((ZT("_ReadHeader - Checking for full header...")));
    for (index = 3; index < handler->receivedSize; index++)
    {
        if (buf[index-3] == '\r' && buf[index-1] == '\r' &&
            buf[index-2] == '\n' && buf[index] == '\n' )
        {
            fullHeaderReceived = MI_TRUE;
            LOGD2((ZT("_ReadHeader - Full header has been recieved")));
            break;
        }
    }

    if (!fullHeaderReceived)
    {
        if (handler->receivedSize <  handler->recvBufferSize)
        {
            unlockHttpClientMutex();
            LOGD2((ZT("_ReadHeader - Full header not received. Waiting...")));
            return PRT_RETURN_TRUE; /* continue reading */
        }

        if (handler->recvBufferSize < MAX_HEADER_SIZE)
        {
            LOGD2((ZT("_ReadHeader - Reallocating buffer...")));
            buf = realloc(handler->recvBuffer, handler->recvBufferSize * 2);

            if (!buf)
            {
                unlockHttpClientMutex();
                LOGE2((ZT("_ReadHeader - Cannot allocate memory for larger header")));
                return PRT_RETURN_FALSE;
            }

            handler->recvBufferSize *= 2;
            handler->recvBuffer = buf;
            unlockHttpClientMutex();
            LOGD2((ZT("_ReadHeader - Going recursive...")));
            return _ReadHeader(handler);
        }
        else
        {
            /* HTTP header is too big - drop connection */
            LOGW((ZT("_ReadHeader - HTTP header is too big; dropping connection")));
            LOGE2((ZT("_ReadHeader - HTTP header is too big. Dropping connection")));
            unlockHttpClientMutex();
            return PRT_RETURN_FALSE;
        }
    }

    /* consume data */
    currentLine = buf;
    data = buf + index + 1; /* pointer to data in case we got some */
    LOGD2((ZT("_ReadHeader - Begin consuming data")));

    if (!_getRequestLine(handler, &currentLine))
    {
        unlockHttpClientMutex();
        LOGE2((ZT("_ReadHeader - Cannot find request line in HTTP header")));
        return PRT_RETURN_FALSE;
    }

    while (data - currentLine > 3)
    {
        if (!_getHeaderField(handler, &currentLine))
        {
            unlockHttpClientMutex();
            LOGE2((ZT("_ReadHeader - Cannot find HTTP header field")));
            return PRT_RETURN_FALSE;
        }
    }

    /* Check if we have to deal with chunked-encoded data */
    if (handler->contentLength < 0)
    {
        LOGE2((ZT("_ReadHeader - Dealing with chunked data")));
        handler->receivedSize -= index + 1;

        /* Invoke user's callback with header information */
        {
            HttpClient* self = (HttpClient*)handler->base.data;
            LOGD2((ZT("_ReadHeader - Calling user callback")));

            if (!(*self->callbackOnResponse)(self, self->callbackData, &handler->recvHeaders,
                                             handler->contentLength, handler->contentLength == 0, 0))
            {
                unlockHttpClientMutex();
                LOGD2((ZT("_ReadHeader - On response callback for chunked data header failed")));
                return PRT_RETURN_FALSE;
            }
        }

        /* remove consumed header part */
        memmove(handler->recvBuffer, data, handler->receivedSize);

        handler->receivingState = RECV_STATE_CHUNKHEADER;
        unlockHttpClientMutex();
        return PRT_CONTINUE;
    }

    contentSize = (size_t)handler->contentLength;
    if (handler->headVerb)
    {
        LOGD2((ZT("_ReadHeader - HEAD response received. Download will contain %ld bytes"), (long)handler->contentLength));
        contentSize = 0;
    }

    LOGD2((ZT("_ReadHeader - Allocating new memory")));

    /* Allocate zero-terminated buffer */
    handler->recvPage = (Page*)malloc(sizeof(Page) + contentSize + 1);

    if (handler->recvPage == NULL)
    {
        unlockHttpClientMutex();
        LOGD2((ZT("_ReadHeader - Cannot allocate memory for received page")));
        return PRT_RETURN_FALSE;
    }

    memset(handler->recvPage, 0, sizeof (Page) + contentSize + 1);
    *((char*)(handler->recvPage + 1) + contentSize) = '\0';
    handler->recvPage->u.s.size = (unsigned int)contentSize;
    handler->recvPage->u.s.next = 0;
    handler->receivedSize -= index + 1;
    LOGD2((ZT("_ReadHeader - Checking content length")));

    /* Verify that we have not more than 'content-length' bytes in buffer left
       If we have more, assume that HTTP client is invalid and drop connection */
    if (handler->receivedSize > (size_t)handler->contentLength)
    {
        unlockHttpClientMutex();
        LOGW((ZT("_ReadHeader - HTTP payload is bigger than content-length")));
        LOGE2((ZT("_ReadHeader - HTTP payload is bigger than content-length")));
        return PRT_RETURN_FALSE;
    }

    if (handler->receivedSize != 0)
    {
        memcpy(handler->recvPage + 1, data, handler->receivedSize);
	}
    handler->receivingState = RECV_STATE_CONTENT;

    LOGD2((ZT("_ReadHeader - Full header read. page size: %d, position: %d"), handler->recvPage->u.s.size, handler->receivedSize));

    /* Invoke user's callback with header information */
    {
        HttpClient* self = (HttpClient*)handler->base.data;

        if (!(*self->callbackOnResponse)(self, self->callbackData, &handler->recvHeaders,
                                         handler->contentLength, handler->contentLength == 0, NULL))
        {
            unlockHttpClientMutex();
            LOGE2((ZT("_ReadHeader - On response callback for header failed")));
            return PRT_RETURN_FALSE;
        }
    }

    unlockHttpClientMutex();
    return PRT_CONTINUE;
}

static Http_CallbackResult _ReadData(
    Http_SR_SocketData* handler)
{
    //HttpClient* self = (HttpClient*)handler->base.data;
    char* buf;
    size_t buf_size, received;
    MI_Result r;

    lockHttpClientMutex();
    LOGD2((ZT("_ReadData - locked mutex")));

    /* are we in the right state? */
    if (handler->receivingState != RECV_STATE_CONTENT)
    {
        unlockHttpClientMutex();
        return PRT_RETURN_FALSE;
    }
    if (!handler->headVerb)
    {
        buf = ((char*)(handler->recvPage + 1)) + handler->receivedSize;
        buf_size = (size_t)(handler->contentLength - handler->receivedSize);
        received = 0;

        if (buf_size != 0)
        {
            r = _Sock_Read(handler, buf, buf_size, &received);

            LOGD2((ZT("_ReadData - _Sock_Read result: %d (%s), socket: %d, recv: %u"), (int)r, mistrerror(r), (int)handler->base.sock, (unsigned int)received));

            if (r == MI_RESULT_OK && 0 == received)
            {
                unlockHttpClientMutex();
                return PRT_RETURN_FALSE; /* connection closed */
            }

            if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
            {
                unlockHttpClientMutex();
                return PRT_RETURN_FALSE;
            }

            handler->receivedSize += received;
        }

        /* did we get all data? */
        LOGD2((ZT("_ReadData - Received size: %d / %u"), (int)handler->receivedSize, (unsigned int)handler->contentLength));

        if (handler->receivedSize != (size_t)handler->contentLength)
        {
            unlockHttpClientMutex();
            return PRT_RETURN_TRUE;
        }
    }

    /* Invoke user's callback with data */
    {
        HttpClient* self = (HttpClient*)handler->base.data;

        if (!(*self->callbackOnResponse)(self, self->callbackData, NULL,
                                         handler->contentLength, MI_TRUE, &handler->recvPage))
        {
            unlockHttpClientMutex();
            return PRT_RETURN_FALSE;
        }

        /* status callback */
        handler->status = MI_RESULT_OK;
        (*self->callbackOnStatus)(self, self->callbackData, MI_RESULT_OK);
    }

    if (handler->recvPage != NULL)
    {
        LOGD2((ZT("_ReadData - Freeing recvPage. socket: %d"), (int)handler->base.sock));
        free(handler->recvPage);
        handler->recvPage = NULL;
    }

    handler->recvPage = NULL;
    handler->receivedSize = 0;
    memset(&handler->recvHeaders, 0, sizeof (handler->recvHeaders));
    handler->receivingState = RECV_STATE_HEADER;
    unlockHttpClientMutex();
    return PRT_CONTINUE;
}

static Http_CallbackResult _ReadChunkHeader(
    Http_SR_SocketData* handler)
{
    char* buf;
    char* currentLine;
    char* data;
    size_t buf_size, received, index;
    MI_Result r;
    MI_Boolean fullHeaderReceived = MI_FALSE;
    MI_Uint32   chunkSize = 0;
    MI_Boolean connectionClosed = MI_FALSE;

    lockHttpClientMutex();
    LOGD2((ZT("_ReadChunkHeader - Locked mutex")));

    /* are we done with header? */
    if (handler->receivingState != RECV_STATE_CHUNKHEADER)
    {
        unlockHttpClientMutex();
        LOGD2((ZT("_ReadChunkHeader - Proceeding to reading of chunk data")));
        return PRT_CONTINUE;
    }

    buf = handler->recvBuffer + handler->receivedSize;
    buf_size = handler->recvBufferSize - handler->receivedSize;
    received = 0;

    errno = 0;
    r = _Sock_Read(handler, buf, buf_size, &received);
    LOGD2((ZT("_ReadChunkHeader - _Sock_Read result: %d (%s), socket: %d, read %u / %u bytes, errno: %d (%s), reverse: %d"), (int)r, mistrerror(r), (int)handler->base.sock, (unsigned int)received, (unsigned int)buf_size, errno, strerror(errno), (int)handler->reverseOperations));
    if (r == MI_RESULT_OK && received == 0)
    {
        if (handler->recvBufferSize == 0)
        {
            unlockHttpClientMutex();
            LOGE2((ZT("_ReadChunkHeader - 0 bytes read. connection closed")));
            return PRT_RETURN_FALSE;
        }

        LOGW2((ZT("_ReadChunkHeader - Partial read. connection closed")));
        connectionClosed = MI_TRUE;
    }

    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        unlockHttpClientMutex();
        LOGE2((ZT("_ReadChunkHeader - Partial read. connection closed")));
        return PRT_RETURN_FALSE;
    }

    if (received == 0 && handler->recvBufferSize == 0)
    {
        unlockHttpClientMutex();
        LOGD2((ZT("_ReadChunkHeader - 0 / 0 bytes read. Continuing")));
        return PRT_RETURN_TRUE;
    }

    handler->receivedSize += received;

    /* check header */
    LOGD2((ZT("_ReadChunkHeader - Buffer: %s"), buf));

    /* did we get full header? */
    buf = handler->recvBuffer;
    for (index = 1; index < handler->receivedSize; index++)
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
        {
            unlockHttpClientMutex();
            LOGE2((ZT("_ReadChunkHeader - Partial read. Connection was closed")));
            return PRT_RETURN_FALSE; /* connection closed */
        }

        if (handler->receivedSize <  handler->recvBufferSize)
        {
            unlockHttpClientMutex();
            LOGD2((ZT("_ReadChunkHeader - Partial read")));
            return PRT_RETURN_TRUE; /* continue reading */
        }

        if (handler->recvBufferSize < MAX_HEADER_SIZE)
        {
            buf = realloc(handler->recvBuffer, handler->recvBufferSize * 2);
            if (!buf)
            {
                unlockHttpClientMutex();
                LOGE2((ZT("_ReadChunkHeader - Cannot reallocate larger buffer")));
                return PRT_RETURN_FALSE;
            }

            handler->recvBufferSize *= 2;
            handler->recvBuffer = buf;
            unlockHttpClientMutex();
            return _ReadChunkHeader(handler);
        }
        else
        {
            /* http chunk header is too big - drop connection */
            LOGW((ZT("_ReadChunkHeader - HTTP chunk header is too big. Dropping connection")));
            LOGE2((ZT("_ReadChunkHeader - HTTP chunk header is too big. Dropping connection")));
            unlockHttpClientMutex();
            return PRT_RETURN_FALSE;
        }
    }

    /* consume data */
    currentLine = buf;
    data = buf + index + 1; /* pointer to data in case we got some */

    if (!_getChunkSize(currentLine, &chunkSize))
    {
        unlockHttpClientMutex();
        LOGE2((ZT("_ReadChunkHeader - _getChunkSize failed")));
        return PRT_RETURN_FALSE;
    }

    if (0 == chunkSize)
    {
        /* last chunk received */

        /* Invoke user's callback with header information */
        {
            HttpClient* self = (HttpClient*)handler->base.data;
            if (!(*self->callbackOnResponse)(self, self->callbackData, NULL,
                                             handler->contentLength, MI_TRUE, NULL))
            {
                unlockHttpClientMutex();
                return PRT_RETURN_FALSE;
            }

            /* status callback */
            handler->status = MI_RESULT_OK;
            (*self->callbackOnStatus)(self, self->callbackData, MI_RESULT_OK);
        }

        /* clean up state */
        handler->recvPage = NULL;
        handler->receivedSize = 0;
        memset(&handler->recvHeaders, 0, sizeof(handler->recvHeaders));
        handler->receivingState = RECV_STATE_HEADER;

        unlockHttpClientMutex();

        if (connectionClosed)
        {
            LOGE2((ZT("_ReadChunkHeader - Connection was closed")));
            return PRT_RETURN_FALSE; /* connection closed */
        }

        return PRT_CONTINUE;
    }

    /* Allocate zero-terminated buffer */
    handler->recvPage = (Page*)malloc(sizeof (Page) + (size_t)chunkSize + 2 /*CR-LF*/ + 1 /* \0 */);

    if (!handler->recvPage)
    {
        unlockHttpClientMutex();
        LOGE2((ZT("_ReadChunkHeader - Malloc of received page buffer failed")));
        return PRT_RETURN_FALSE;
    }

    memset(handler->recvPage, 0, sizeof (Page) + (size_t)chunkSize + 2 /*CR-LF*/ + 1 /* \0 */);

    ((char*)(handler->recvPage + 1))[chunkSize + 2] = '\0';

    handler->recvPage->u.s.size = (unsigned int)chunkSize;
    handler->recvPage->u.s.next = 0;

    /* subtract header size */
    handler->receivedSize -= index + 1;

    /* in case of small chunks we may receive more than one chunk already */
    if (handler->receivedSize > (size_t)(chunkSize + 2))
    {
        /* copy page size to page */
        memcpy(handler->recvPage + 1, data, chunkSize + 2);

        /* notify user */
        {
            HttpClient* self = (HttpClient*)handler->base.data;

            if (!(*self->callbackOnResponse)(self, self->callbackData, 0,
                                             handler->contentLength, MI_FALSE, &handler->recvPage))
            {
                unlockHttpClientMutex();
                LOGE2((ZT("_ReadChunkHeader - callbackOnResponse failed")));
                return PRT_RETURN_FALSE;
            }

            if (handler->recvPage != NULL)
            {
                LOGD2((ZT("_ReadChunkHeader - Freeing RecvPage for socket %d"), (int)handler->base.sock));
                free(handler->recvPage);
                handler->recvPage = NULL;
            }

            handler->recvPage = NULL;
        }

        /* remove consumed part */
        memmove(handler->recvBuffer, data + (chunkSize + 2), handler->receivedSize - (chunkSize + 2));
        handler->receivedSize -= (chunkSize + 2);

        /* consume next chunk */
        unlockHttpClientMutex();
        LOGD2((ZT("_ReadChunkHeader - Recursively reading next chunk")));
        return _ReadChunkHeader(handler);
    }

    memcpy(handler->recvPage + 1, data, handler->receivedSize);
    handler->receivingState = RECV_STATE_CHUNKDATA;

    unlockHttpClientMutex();

    if (connectionClosed)
    {
        LOGE2((ZT("_ReadChunkHeader - Connection was closed")));
        return PRT_RETURN_FALSE; /* connection closed */
    }

    return PRT_CONTINUE;
}

static Http_CallbackResult _ReadChunkData(
    Http_SR_SocketData* handler)
{
    //HttpClient* self = (HttpClient*)handler->base.data;
    char* buf;
    size_t buf_size, received;
    MI_Result r;

    lockHttpClientMutex();
    LOGD2((ZT("_ReadChunkData - Begin. socket: %d. Locked mutex"), (int)handler->base.sock));

    /* are we in the right state? */
    if (handler->receivingState != RECV_STATE_CHUNKDATA)
    {
        unlockHttpClientMutex();
        LOGE2((ZT("_ReadChunkData - State not RECV_STATE_CHUNKDATA")));
        return PRT_RETURN_FALSE;
    }

    buf = ((char*)(handler->recvPage + 1)) + handler->receivedSize;
    buf_size = (size_t)(handler->recvPage->u.s.size + 2 /* CR-LF */ - handler->receivedSize);
    received = 0;
    LOGD2((ZT("_ReadChunkData - Before. Have read %u / %u bytes in page. %u bytes remain"), (unsigned int)handler->receivedSize, (unsigned int)(handler->recvPage->u.s.size + 2), (unsigned int)buf_size));

    if (buf_size != 0)
    {
        r = _Sock_Read(handler, buf, buf_size, &received);
        LOGD2((ZT("_ReadChunkData - _Sock_Read result: %d (%s), socket: %d, %u / %u bytes received"), (int)r, mistrerror(r), (int)handler->base.sock, (unsigned int)buf_size, (unsigned int)received));

        if (r == MI_RESULT_OK && received == 0)
        {
            unlockHttpClientMutex();
            LOGE2((ZT("_ReadChunkData - Connection closed")));
            return PRT_RETURN_FALSE; /* connection closed */
        }

        if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
        {
            unlockHttpClientMutex();
            LOGE2((ZT("_ReadChunkData - Error: %d (%s)"), (int)r, mistrerror(r)));
            return PRT_RETURN_FALSE;
        }

        handler->receivedSize += received;
    }

    /* did we get all data? */
    if (handler->receivedSize < (size_t)(handler->recvPage->u.s.size + 2 /* CR-LF */))
    {
        unlockHttpClientMutex();
        LOGD2((ZT("_ReadChunkData - Read %u / %u bytes"), (unsigned int)handler->receivedSize, (unsigned int)(handler->recvPage->u.s.size + 2)));
        return PRT_RETURN_TRUE;
    }

    /* Invoke user's callback with header information */
    {
        HttpClient* self = (HttpClient*)handler->base.data;

        if (!(*self->callbackOnResponse)(self, self->callbackData, 0,
                                         handler->contentLength, MI_FALSE, &handler->recvPage))
        {
            unlockHttpClientMutex();
            LOGE2((ZT("_ReadChunkData - callbackOnResponse failed")));
            return PRT_RETURN_FALSE;
        }
    }

    if (handler->recvPage != NULL)
    {
        LOGD2((ZT("_ReadChunkHeader - Freeing RecvPage for socket %d"), (int)handler->base.sock));
        free(handler->recvPage);
        handler->recvPage = NULL;
    }

    handler->recvPage = NULL;
    handler->receivedSize = 0;
    memset(&handler->recvHeaders, 0, sizeof (handler->recvHeaders));
    handler->receivingState = RECV_STATE_CHUNKHEADER;
    unlockHttpClientMutex();

    return PRT_CONTINUE;
}

static Http_CallbackResult _WriteHeader(
    Http_SR_SocketData* handler)
{
    char* buf;
    size_t buf_size, sent;
    MI_Result r;

    lockHttpClientMutex();

    /* are we done with header? */
    if (handler->sendingState == RECV_STATE_CONTENT)
    {
        unlockHttpClientMutex();
        LOGE2((ZT("_WriteHeader - Header write...incorrect state")));
        return PRT_CONTINUE;
    }

    /* Do we have any data to send? */
    if (!handler->sendHeader)
    {
        unlockHttpClientMutex();
        LOGE2((ZT("_WriteHeader - Header write...no data")));
        return PRT_RETURN_TRUE;
    }
    buf = ((char*)(handler->sendHeader + 1)) + handler->sentSize;
    buf_size = handler->sendHeader->u.s.size - handler->sentSize;
    sent = 0;

    LOGD2((ZT("_WriteHeader - Header: %s"), buf));
    r = _Sock_Write(handler, buf, buf_size, &sent);

    LOGD2((ZT("_WriteHeader - _Sock_Write result: %d (%s), socket: %d, sent: %d"), (int)r, mistrerror(r), (int)handler->base.sock, (int)sent));

    if (r == MI_RESULT_OK && sent == 0)
    {
        unlockHttpClientMutex();
        LOGE2((ZT("_WriteHeader - Connection closed")));
        return PRT_RETURN_FALSE; /* connection closed */
    }

    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        unlockHttpClientMutex();
        LOGE2((ZT("_WriteHeader - _Sock_Write returned error: %d (%s)"), (int)r, mistrerror(r)));
        return PRT_RETURN_FALSE;
    }

    handler->sentSize += sent;
    handler->headVerb = buf_size > 4 && strncasecmp(buf, "HEAD", 4) == 0;

    /* did we send all data? */
    if (handler->sentSize != handler->sendHeader->u.s.size)
    {
        unlockHttpClientMutex();
        LOGD2((ZT("_WriteHeader - Partial write. %u sent this time, %u / %d written, result: %d (%s)"), (unsigned int)sent, (unsigned int)handler->sentSize, (unsigned int)handler->sendHeader->u.s.size, r, mistrerror(r)));
        return PRT_RETURN_TRUE;
    }

    free(handler->sendHeader);
    handler->sendHeader = 0;
    handler->sentSize = 0;
    handler->sendingState = RECV_STATE_CONTENT;

    unlockHttpClientMutex();

    LOGD2((ZT("_WriteHeader - OK exit")));
    return PRT_CONTINUE;
}

static Http_CallbackResult _WriteData(
    Http_SR_SocketData* handler)
{
    char* buf;
    size_t buf_size, sent;
    MI_Result r;

    lockHttpClientMutex();
    LOGD2((ZT("_WriteData - Locked mutex. socket: %d"), handler->base.sock));

    /* are we in the right state? */
    if (handler->sendingState != RECV_STATE_CONTENT)
    {
        unlockHttpClientMutex();
        LOGE2((ZT("_WriteData - Error. State not RECV_STATE_CONTENT")));
        return PRT_RETURN_FALSE;
    }

    if (handler->sendPage == NULL)
    {   /* no content */
        handler->sentSize = 0;
        handler->sendingState = RECV_STATE_HEADER;
        handler->base.mask &= ~SELECTOR_WRITE;
        handler->base.mask |= SELECTOR_READ;

        unlockHttpClientMutex();
        LOGW2((ZT("_WriteData - Content is empty. Continuing")));
        return PRT_CONTINUE;
    }

    buf = (char*)(handler->sendPage + 1) + handler->sentSize;
    buf_size = handler->sendPage->u.s.size - handler->sentSize;
    sent = 0;

    LOGD2((ZT("_WriteData HTTPClient asking to send %u bytes"), (unsigned int)buf_size));
    r = _Sock_Write(handler, buf, buf_size, &sent);
    LOGD2((ZT("_WriteData - HTTPClient sent %u / %u bytes with result %d (%s)"), (unsigned int)sent, (unsigned int)buf_size, (int)r, mistrerror(r)));

    if (r == MI_RESULT_OK && sent == 0)
    {
        unlockHttpClientMutex();
        LOGE2((ZT("_WriteData exit. Connection closed")));
        return PRT_RETURN_FALSE; /* connection closed */
    }

    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        unlockHttpClientMutex();
        LOGE2((ZT("_WriteData exit - Error: %d (%s)"), r, mistrerror(r)));
        return PRT_RETURN_FALSE;
    }

    handler->sentSize += sent;

    /* did we get all data? */

    if (handler->sentSize != handler->sendPage->u.s.size)
    {
        unlockHttpClientMutex();
        LOGD2((ZT("_WriteData - Exit. Partial send. %u / %u bytes sent"), (unsigned int)handler->sentSize, (unsigned int)handler->sendPage->u.s.size));
        return PRT_RETURN_TRUE;
    }

    LOGD2((ZT("_WriteData - Completed send. %u / %u bytes sent"), (unsigned int)handler->sentSize, (unsigned int)handler->sendPage->u.s.size));
    LOGD2((ZT("_WriteData - Exit. Freeing sendPage for socket %d"), (int)handler->base.sock));
    free(handler->sendPage);
    handler->sendPage = NULL;
    handler->sentSize = 0;
    handler->sendingState = RECV_STATE_HEADER;
    handler->base.mask &= ~SELECTOR_WRITE;
    handler->base.mask |= SELECTOR_READ;

    unlockHttpClientMutex();
    return PRT_CONTINUE;
}

static MI_Boolean _RequestCallbackRead(
    Http_SR_SocketData* handler)
{
    LOGD2((ZT("_RequestCallbackRead - Begin")));
    switch (_ReadHeader(handler))
    {
        case PRT_CONTINUE:
            LOGD2((ZT("_RequestCallbackRead - _ReadHeader returned PRT_CONTINUE")));
            break;
        case PRT_RETURN_TRUE:
            LOGD2((ZT("_RequestCallbackRead - _ReadHeader returned PRT_RETURN_TRUE")));
            return MI_TRUE;
        case PRT_RETURN_FALSE:
            LOGD2((ZT("_RequestCallbackRead - _ReadHeader returned PRT_RETURN_FALSE")));
            return MI_FALSE;
    }

    if (handler->receivingState == RECV_STATE_CONTENT)
    {
        switch (_ReadData(handler))
        {
            case PRT_CONTINUE:
                LOGD2((ZT("_RequestCallbackRead - _ReadData returned PRT_CONTINUE")));
                break;
            case PRT_RETURN_TRUE:
                LOGD2((ZT("_RequestCallbackRead - _ReadData returned PRT_RETURN_TRUE")));
                return MI_TRUE;
            case PRT_RETURN_FALSE:
                LOGD2((ZT("_RequestCallbackRead - _ReadData returned PRT_RETURN_FALSE")));
                return MI_FALSE;
        }
    }

    if (handler->receivingState == RECV_STATE_CHUNKHEADER)
    {
        switch (_ReadChunkHeader(handler))
        {
            case PRT_CONTINUE:
                LOGD2((ZT("_RequestCallbackRead - _ReadChunkHeader returned PRT_CONTINUE")));
                break;
            case PRT_RETURN_TRUE:
                LOGD2((ZT("_RequestCallbackRead - _ReadChunkHeader returned PRT_RETURN_TRUE")));
                return MI_TRUE;
            case PRT_RETURN_FALSE:
                LOGD2((ZT("_RequestCallbackRead - _ReadChunkHeader returned PRT_RETURN_FALSE")));
                return MI_FALSE;
        }
    }

    if (handler->receivingState == RECV_STATE_CHUNKDATA)
    {
        switch (_ReadChunkData(handler))
        {
            case PRT_CONTINUE:
                LOGD2((ZT("_RequestCallbackRead - _ReadChunkData returned PRT_CONTINUE")));
                break;
            case PRT_RETURN_TRUE:
                LOGD2((ZT("_RequestCallbackRead - _ReadChunkData returned PRT_RETURN_TRUE")));
                return MI_TRUE;
            case PRT_RETURN_FALSE:
                LOGD2((ZT("_RequestCallbackRead - _ReadChunkData returned PRT_RETURN_FALSE")));
                return MI_FALSE;
        }
    }

    LOGD2((ZT("_RequestCallbackRead - OK exit")));
    return MI_TRUE;
}

static MI_Boolean _RequestCallbackWrite(
    Http_SR_SocketData* handler)
{
    switch (_WriteHeader(handler))
    {
       case PRT_CONTINUE:
            LOGD2((ZT("CallbackWrite - _WriteHeader returned PTR_CONTINUE")));
            break;
       case PRT_RETURN_TRUE:
            LOGD2((ZT("CallbackWrite - _WriteHeader returned PRT_RETURN_TRUE")));
            return MI_TRUE;
       case PRT_RETURN_FALSE:
            LOGD2((ZT("CallbackWrite - _WriteHeader returned PTR_RETURN_FALSE")));
            return MI_FALSE;
    }

    LOGD2((ZT("_RequestCallbackWrite - Writing data")));
    switch (_WriteData(handler))
    {
       case PRT_CONTINUE:
            LOGD2((ZT("CallbackWrite - _WriteData returned PRT_CONTINUE")));
            break;
       case PRT_RETURN_TRUE:
            LOGD2((ZT("CallbackWrite - _WriteData returned PRT_RETURN_TRUE")));
            return MI_TRUE;
       case PRT_RETURN_FALSE:
            LOGD2((ZT("CallbackWrite - _WriteData returned PRT_RETURN_FALSE")));
            return MI_FALSE;
    }

    LOGD2((ZT("_RequestCallbackWrite - OK exit")));
    return MI_TRUE;
}

static void _HttpSRSocketDataDestructor(Handler* handlerBase)
{
    Http_SR_SocketData* handler = (Http_SR_SocketData*)handlerBase;

    if (handler->ssl != NULL)
    {
        SSL_shutdown(handler->ssl);
        SSL_free(handler->ssl);
        handler->ssl = NULL;
    }

    if (handler->recvPage != NULL)
    {
        free(handler->recvPage);
        handler->recvPage = NULL;
    }

    if (handler->sendPage != NULL)
    {
        free(handler->sendPage);
        handler->sendPage = NULL;
    }

    if (handler->recvBuffer != NULL)
    {
        free(handler->recvBuffer);
        handler->recvBuffer = NULL;
    }

    return;
}

static MI_Boolean _RequestCallback(
    Selector* sel,
    Handler* handlerBase,
    MI_Uint32 mask,
    MI_Uint64 currentTimeUsec)
{
    Http_SR_SocketData* handler = (Http_SR_SocketData*)handlerBase;
    sel=sel;
    LOGD2((ZT("_RequestCallback - Begin. mask: 0x%02X (%s), initial status: %d (%s), handler->reverseOperations: %d"), mask, selectorflagstr(mask), handler->status, mistrerror(handler->status), handler->reverseOperations));
    if (((mask & SELECTOR_READ) != 0 && !handler->reverseOperations) ||
        ((mask & SELECTOR_WRITE) != 0 && handler->reverseOperations))
    {
        if (!_RequestCallbackRead(handler))
        {
            LOGE2((ZT("_RequestCallback - RequestCallbackRead failed")));
            return MI_FALSE;
        }
        LOGD2((ZT("_RequestCallback - RequestCallbackRead succeeded")));
    }

    if (((mask & SELECTOR_WRITE) != 0 && !handler->reverseOperations) ||
        ((mask & SELECTOR_READ) != 0 && handler->reverseOperations))
    {
        if (!_RequestCallbackWrite(handler))
        {
            LOGE2((ZT("_RequestCallback - _RequestCallbackWrite failed")));
            return MI_FALSE;
        }

        handler->status = MI_RESULT_OK;
        LOGD2((ZT("_RequestCallback - _RequestCallbackWrite succeeded")));
    }

    LOGD2((ZT("_RequestCallback - End check. MI result: %d (%s), mask: 0x%02X (%s). Locking mutex"), (int)handler->status, mistrerror(handler->status), mask, selectorflagstr(mask)));
    lockHttpClientMutex();

    /* reset timeout - if we performed R/W operation, set timeout depending where we are in communication */
    if ((mask & (SELECTOR_READ | SELECTOR_WRITE)) != 0)
    {
        Time_Now(&currentTimeUsec);
        handler->base.fireTimeoutAt = (currentTimeUsec + handler->timeoutUsec);
        LOGD2((ZT("_RequestCallback - Timeout reset. socket: %d, new time: %s, %s sec. in the future"), handler->base.sock, FmtTime(handler->base.fireTimeoutAt), FmtInterval(handler->timeoutUsec)));
    }

    if ((mask & SELECTOR_TIMEOUT) != 0)
    {
        /* Close connection because of timeout */
        if (handler->status != MI_RESULT_OK)
        {
            handler->recvHeaders.httpError = 408;
            handler->status = MI_RESULT_TIME_OUT;
        }
        unlockHttpClientMutex();
        LOGE2((ZT("_RequestCallback - Timed out. socket: %d, result: %d (%s)"), handler->base.sock, handler->status, mistrerror(handler->status)));
        return MI_FALSE;
    }

    if ((mask & SELECTOR_REMOVE) != 0 || (mask & SELECTOR_DESTROY) != 0)
    {
        LOGD2((ZT("_RequestCallback - Destroy socket: %d, MI result: %d (%s), HTTP status: %d"), handler->base.sock, (int)handler->status, mistrerror(handler->status), handler->recvHeaders.httpError));
        HttpClient* self = (HttpClient*)handler->base.data;

        if (handler->status == MI_RESULT_FAILED)
        {
            if (handler->recvHeaders.httpError == 404)
            {
                handler->status = MI_RESULT_NOT_FOUND;
            }
        }

        /* notify next stack layer */
        if (handler->status != MI_RESULT_OK)
        {
            (*self->callbackOnStatus)(self, self->callbackData, handler->status);
		}
        self->connector = NULL;

        // Yeah, this is hokey, but we need to sleep here to let the subsystems have the opportunity to
        // send the data before we close the socket, or we'll get a broken pipe/connection reset
        unlockHttpClientMutex();
        usleep(50);
        lockHttpClientMutex();
        LOGD2((ZT("_RequestCallback - Locked mutex")));

        if (handler == NULL)
        {
            unlockHttpClientMutex();
            LOGE2((ZT("_RequestCallback - The handler object was free'd under us!")));
            return MI_TRUE;
        }

        LOGD2((ZT("_RequestCallback - Closing socket: %d"), (int)handler->base.sock));
        Sock_Close(handler->base.sock);
        _HttpSRSocketDataDestructor((Handler*)handler);
        free(handler);
        handler = NULL;
    }

    unlockHttpClientMutex();
    LOGD2((ZT("_RequestCallback - OK Exit")));
    return MI_TRUE;
}

#ifdef CONFIG_POSIX

/*
 Verify callback when the server authentication certificate's chain of trust is checked. This
 is the same as the Open SSL verify callback function (return preverify_ok), except that it
 logs a diagnostic message when preverify_ok has a failed status.
*/
static int ctxVerify(
    int preverify_ok,
    X509_STORE_CTX* ctx)
{
    if (preverify_ok <= 0)
    {
        LOGE((ZT("ctxVerify - Cannot verify trust of certificate")));
        LOGE2((ZT("ctxVerify - Cannot verify trust of certificate")));
        X509* certWithError = X509_STORE_CTX_get_current_cert(ctx);
        int error = X509_STORE_CTX_get_error(ctx);
        char nameBuf[256];
        X509_NAME_oneline(X509_get_subject_name(certWithError), nameBuf, 256);
        LOGE((ZT("ctxVerify - Error %d in certificate %s"), error, nameBuf));
        LOGE2((ZT("ctxVerify - Error %d in certificate %s"), error, nameBuf));
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
        LOGE((ZT("_CreateSSLContext - Cannot create SSL context")));
        LOGE2((ZT("_CreateSSLContext - Cannot create SSL context")));
        return MI_RESULT_FAILED;
    }
    SSL_CTX_set_quiet_shutdown(sslContext, 1);
    SSL_CTX_set_mode(sslContext, SSL_MODE_AUTO_RETRY);
    SSL_CTX_set_mode(sslContext, SSL_MODE_ENABLE_PARTIAL_WRITE);
    SSL_CTX_set_session_cache_mode(sslContext, SSL_SESS_CACHE_OFF);
    SSL_CTX_sess_set_remove_cb(sslContext, NULL);

    if (trustedCertsDir != NULL)
    {
        // Cause Open SSL to check the server certificate Subject against its FQDN and
        // to check the server certificate chain against the contents of *trustedCertsDir.
        if (SSL_CTX_load_verify_locations(sslContext, NULL, trustedCertsDir) < 0)
        {
            LOGE((ZT("_CreateSSLContext - Cannot set directory containing trusted certificate(s)")));
            LOGE2((ZT("_CreateSSLContext - Cannot set directory containing trusted certificate(s) to %s"), trustedCertsDir));
        }
        SSL_CTX_set_verify(sslContext, SSL_VERIFY_PEER, ctxVerify);
    }

    /* Check if there is a client certificate file (file containing client authentication
    ** certificate) specified. If specified, validate and load the certificate.
    */
    if (certFile != NULL && *certFile != '\0')
    {
        int err;

        /* load the specified client certificates */
        LOGI((ZT("_CreateSSLContext - Loading server certificate from: %s"), certFile));

        err = SSL_CTX_use_certificate_file(sslContext,
                                           certFile,
                                           strcmp(certFile + strlen(certFile) - 4, ".pem") == 0 ? SSL_FILETYPE_PEM :  SSL_FILETYPE_ASN1);
        if (err <= 0)
        {
#if defined(ENABLE_TRACING)
            unsigned long error = ERR_peek_last_error();
#endif

            LOGE((ZT("_CreateSSLContext - No client certificate found in %s"), certFile));
            LOGE2((ZT("_CreateSSLContext - No client certificate found in %s"), certFile));
            LOGE2((ZT("_CreateSSLContext - OpenSSL Error 0x%lX (%s) in SSL_CTX_use_certificate_file"), error, sslstrerror(error)));
            SSL_CTX_free(sslContext);
            sslContext = NULL;
            return MI_RESULT_FAILED;
        }

        if (privateKeyFile != NULL && *privateKeyFile != '\0')
        {
            /* load the specified private key */
            LOGI((ZT("_CreateSSLContext - SSL Loading client private key from: %s"), privateKeyFile));

            err = SSL_CTX_use_RSAPrivateKey_file(sslContext,
                                                 privateKeyFile,
                                                 strcmp(privateKeyFile + strlen(privateKeyFile) - 4, ".pem") == 0 ? SSL_FILETYPE_PEM :  SSL_FILETYPE_ASN1);
            if (err <= 0)
            {
#if defined(ENABLE_TRACING)
                unsigned long error = ERR_peek_last_error();
#endif
                LOGE((ZT("_CreateSSLContext - Invalid private key found in %s"), privateKeyFile));
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
        LOGE2((ZT("_CreateSocketAndConnect - Sock_SetBlocking returned error: %d (%s)"), (int)r, mistrerror(r)));
        return r;
	}

    r = Sock_Connect(*s, addr);
#ifdef ENABLE_TRACING
    if (r != MI_RESULT_OK)
    {
        LOGE2((ZT("_CreateSocketAndConnect - Sock_Connect returned error: %d (%s)"), (int)r, mistrerror(r)));
	}
#endif

    return r;
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
    Http_SR_SocketData* h;
    MI_Uint64 currentTimeUsec;

    /* timeout calculation */
    r = Time_Now(&currentTimeUsec);
    if (r != MI_RESULT_OK)
    {
        LOGE2((ZT("_CreateConnectorSocket - Time_Now returned error: %d (%s)"), (int)r, mistrerror(r)));
        return r;
    }

    // This code tries to connect using the preferred addressing family (IPv4 or IPv6). If that
    // fails and Addr_Init has a secondary addressing family, a connection with the secondary
    // family, it tries using the secondary family next.

    // Initialize preferred address.
    r = Addr_Init(&addr, host, port, MI_FALSE);
    if (r != MI_RESULT_OK)
    {
        LOGE2((ZT("_CreateConnectorSocket - Addr_Init returned error: %d (%s)"), (int)r, mistrerror(r)));
        return r;
    }

    // Connect to the server
    r = _CreateSocketAndConnect(&s, &addr);
    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        MI_Result r2;

        Sock_Close(s);

        // Initialize secondary address
        r2 = Addr_Init(&addr, host, port, MI_TRUE);
        if (r2 != MI_RESULT_OK)
        {
            return r;                   // on error, return original failure
		}
        r2 = _CreateSocketAndConnect(&s, &addr);
        if (r2 != MI_RESULT_OK && r2 != MI_RESULT_WOULD_BLOCK)
        {
            Sock_Close(s);

            return r;                   // on error, return original failure
		}
        r = r2;
    }
    LOGD2((ZT("_CreateConnectorSocket - Connection successful. result: %d (%s)"), (int)r, mistrerror(r)));

    // Create handler
    h = (Http_SR_SocketData*)calloc(1, sizeof (Http_SR_SocketData));
    if (h == NULL)
    {
        Sock_Close(s);
        LOGE2((ZT("_CreateConnectorSocket - calloc failed")));
        return MI_RESULT_FAILED;
    }

    h->recvBufferSize = INITIAL_BUFFER_SIZE;
    h->recvBuffer = (char*)calloc(1, h->recvBufferSize);
    if (h->recvBuffer == NULL)
    {
        free(h);
        h = NULL;
        Sock_Close(s);
        LOGE2((ZT("_CreateConnectorSocket - calloc failed")));
        return MI_RESULT_FAILED;
    }

    h->base.type = CHILD_TYPE_HTTPCLIENT_SR_CLIENT_SOCKETDATA;
    h->base.sock = s;
    h->base.mask = SELECTOR_EXCEPTION;
    h->base.callback = _RequestCallback;
    h->base.data = self;
    h->timeoutUsec = DEFAULT_HTTP_TIMEOUT_USEC;
    h->base.fireTimeoutAt = currentTimeUsec + h->timeoutUsec;

    /* SSL support */
    if (secure)
    {
        h->ssl = SSL_new(self->sslContext);

        if (h->ssl == NULL)
        {
            LOGW((ZT("_CreateConnectorSocket - SSL_new failed")));
            LOGE2((ZT("_CreateConnectorSocket - SSL_new failed")));
            free(h);
            h = NULL;
            Sock_Close(s);
            return MI_RESULT_FAILED;
        }

        if (!SSL_set_fd(h->ssl, s))
        {
            LOGW((ZT("_CreateConnectorSocket - SSL_set_fd failed")));
            LOGW2((ZT("_CreateConnectorSocket - SSL_set_fd failed")));
            SSL_shutdown(h->ssl);
            SSL_free(h->ssl);
            h->ssl = NULL;
            free(h);
            h = NULL;
            Sock_Close(s);
            return MI_RESULT_FAILED;
        }

        SSL_set_connect_state(h->ssl);
    }
    h->base.destructor = _HttpSRSocketDataDestructor;

    /* Watch for read events on the incoming connection */
    r = Selector_AddHandler(self->selector, &h->base);

    if (r != MI_RESULT_OK)
    {
        LOGW((ZT("_CreateConnectorSocket - Selector_AddHandler failed")));
        LOGE2((ZT("_CreateConnectorSocket - Selector_AddHandler failed with error: %d (%s)"), (int)r, mistrerror(r)));
        if (secure)
        {
            SSL_free(h->ssl);
        }
        h->ssl = NULL;
        _HttpSRSocketDataDestructor((Handler*)h);
        free(h);
        h = NULL;
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
    HttpClientCallbackOnStatus statusCallback,
    HttpClientCallbackOnResponse  responseCallback,
    void* callbackData)
{
    HttpClient* self;

    /* Check parameters */
    if (selfOut == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    /* Clear output parameter */
    *selfOut = NULL;

    /* Allocate structure */
    {
        self = (HttpClient*)calloc(1, sizeof(HttpClient));

        if (self == NULL)
        {
            LOGE2((ZT("_New_Http - calloc failed")));
            return MI_RESULT_FAILED;
        }
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
            LOGE2((ZT("_New_Http - Selector_Init failed")));
            if (self != NULL)
            {
                free(self);
            }
            self = NULL;
            return MI_RESULT_FAILED;
        }
        self->selector = &self->internalSelector;
        self->internalSelectorUsed = MI_TRUE;
    }

    /* Save the callback and callbackData */
    self->callbackOnResponse = responseCallback;
    self->callbackOnStatus = statusCallback;
    self->callbackData = callbackData;

    /* Set the magic number */
    self->magic = _MAGIC;

    /* Set output parameter */
    *selfOut = self;
    return MI_RESULT_OK;
}

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

static Page* _CreateHttpHeader(
    const char* verb,
    const char* uri,
    const HttpClientRequestHeaders* headers,
    size_t size)
{
    Page* page = NULL;
    size_t pageSize = 0;
    int r;
    char* p;

#define HTTP_HEADER_FORMAT "%s %s HTTP/1.1\r\n" \
    "Content-Length: %d\r\n"\
    "Connection: Keep-Alive\r\n" \
    "Host: host\r\n"

#define HTTP_HEADER_FORMAT_NOCL "%s %s HTTP/1.1\r\n" \
    "Connection: Keep-Alive\r\n" \
    "Host: host\r\n"

    /* calculate approximate page size */
    if (verb == NULL)
    {
        verb = "POST";
	}
    pageSize += sizeof(HTTP_HEADER_FORMAT) + 10; /* format + 10 digits of content length */
    pageSize += Strlen(verb);
    pageSize += Strlen(uri);

    if (headers)
    {
        pageSize += _GetHeadersSize(headers);
    }

    page = (Page*)malloc(pageSize + sizeof(Page));

    if (page == NULL)
    {
        LOGE2((ZT("_CreateHttpHeader - malloc failed")));
        return NULL;
    }

    /* clear header */
    memset(page, 0, sizeof(Page));

    p = (char*)(page + 1);

    if (size != 0)
    {
        r = Snprintf(p, pageSize, HTTP_HEADER_FORMAT, verb, uri, (int)size);
    }
    else
    {
        r = Snprintf(p, pageSize, HTTP_HEADER_FORMAT_NOCL, verb, uri);
    }

    if (r < 0)
    {
        LOGE2((ZT("_CreateHttpHeader - Freeing general page in _CreateHttpHeader due to failure")));
        free(page);
        page = NULL;
        return NULL;
    }

    p += r;
    pageSize -= r;

    if (headers)
    {
        size_t index = 0;

        while (index < headers->size)
        {
            r = (int)Strlcpy(p, headers->data[index], pageSize);
            p += r;
            pageSize -= r;
            r = (int)Strlcpy(p, "\r\n", pageSize);
            p += r;
            pageSize -= r;
            index++;
        }
    }

    /* add trailing \r\n */
    r = (int)Strlcpy(p, "\r\n", pageSize);
    p += r;
    pageSize -= r;
    page->u.s.size = (unsigned int)(p - (char*)(page + 1));

    return page;
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
MI_Result MI_EXPORT HttpClient_New_Connector(
    HttpClient** selfOut,
    Selector* selector, /*optional, maybe NULL*/
    const char* host,
    unsigned short port,
    MI_Boolean secure,
    HttpClientCallbackOnStatus statusCallback,
    HttpClientCallbackOnResponse responseCallback,
    void* callbackData,
    const char* trustedCertsDir,
    const char* certFile,
    const char* privateKeyFile)
{
    HttpClient* self;
    MI_Result r;

    LOGD2((ZT("HttpClient_New_Connector: Begin")));

    *selfOut = NULL;

    /* allocate this, inits selector */
    r = _New_Http(selfOut, selector, statusCallback, responseCallback, callbackData);

    LOGD2((ZT("HttpClient_New_Connector: _New_Http allocated. result: %d (%s)"), (int)r, mistrerror(r)));

    if (MI_RESULT_OK != r)
        return r;

    self = *selfOut;

#ifdef CONFIG_POSIX
    /* Allocate SSL context and create an HTTPS connector socket */
    if (secure)
    {
        LOGD2((ZT("HttpClient_New_Connector: _New_Http allocated. Creating SSL context")));

        /* create SSL context */
        r = _CreateSSLContext(self, trustedCertsDir, certFile, privateKeyFile);
        if (r != MI_RESULT_OK)
        {
            HttpClient_Delete(self);
            LOGE2((ZT("HttpClient_New_Connector - Failed to create SSL context. error: %d (%s)"), (int)r, mistrerror(r)));
            return r;
        }
    }
#else
    MI_UNUSED(secure);
#endif

    /* Create HTTP connector socket */
    {
        r = _CreateConnectorSocket(self, host, port, secure);
        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("HttpClient_New_Connector: _CreateConnectorSocket failed. result: %d (%s)"), (int)r, mistrerror(r)));
            HttpClient_Delete(self);
            return r;
        }
    }

    LOGD2((ZT("HttpClient_New_Connector - OK exit")));
    return MI_RESULT_OK;
}

int HttpClientIsConnector(HttpClient *self)
{
    if (self && self->connector)
    {
        return 1;
    }
    return 0;
}

/*
    Deletes http object, disconnects form the server
    and frees all related resources.

    Parameters:
    self - http object

    Returns:
    OK
*/
MI_Result MI_EXPORT HttpClient_Delete(
    HttpClient* self)
{
    pthread_mutex_lock(&deleteMutexLock);

    /* Check parameters */
    if (self == NULL || (self->magic != _MAGIC))
    {
        pthread_mutex_unlock(&deleteMutexLock);
        return MI_RESULT_INVALID_PARAMETER;
    }

#if TRACING_LEVEL > 3
    LOGD2((ZT("HttpClient_Delete - Begin")));

    if (self != NULL && self->connector != NULL)
    {
        LOGD2((ZT("HttpClient_Delete - Connector and socket were set. socket: %d"), self->connector->base.sock));
    }
    else
    {
        LOGW2((ZT("HttpClient_Delete - No connector set")));
    }
#endif

    if (self->internalSelectorUsed)
    {
        LOGD2((ZT("HttpClient_Delete for internal selector")));
        /* Release selector;
        Note: Selector_Destroy closes all sockets in a list including connector and listener */

        // This will call back into the _RequestCallback, so we let go of the mutex here
        Selector_Destroy(self->selector);

        if (self == NULL || self->magic != _MAGIC)
        {
            pthread_mutex_unlock(&deleteMutexLock);
            return MI_RESULT_INVALID_PARAMETER;
        }

        /* Shutdown the network */
        Sock_Stop();
    }
    else
    {
        /* remove connector from handler */
        if (self->connector != NULL)
        {
            LOGD2((ZT("HttpClient_Delete with connector - socket: %d"), self->connector->base.sock));
            Selector_RemoveHandler(self->selector, &self->connector->base);
        }
        else
        {
            LOGW2((ZT("HttpClient_Delete - No connector for this client")));
        }
    }

    if (self != NULL)
    {
        if (self->sslContext != NULL)
        {
            SSL_CTX_free(self->sslContext);
            self->sslContext = NULL;
        }

        /* Clear magic number */
        self->magic = 0xDDDDDDDD;

        /* Free self pointer */
        free(self);
        self = NULL;
    }

    pthread_mutex_unlock(&deleteMutexLock);

    return MI_RESULT_OK;
}

/*
    Send HTTP request.

    Parameters:
    self - http object
    uri - request's URI
    headers - [opt] extra headers for request.
    data - [opt] content to send. if message is accepted to be sent,
        on return *data == null (taking memory ownership)

    Returns:
    OK or appropriate error
 */
MI_Result MI_EXPORT HttpClient_StartRequest(
    HttpClient* self,
    const char* verb,
    const char* uri,
    const HttpClientRequestHeaders* headers,
    Page** data)
{
    LOGD2((ZT("HttpClient_StartRequest - Start request for verb %s. URI: %s"), verb, uri));

    /* check params */
    if (self == NULL || uri == NULL)
    {
        LOGE2((ZT("HttpClient_StartRequest - Invalid argument")));
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (self->magic != _MAGIC)
    {
        LOGW((ZT("HttpClient_StartRequest - Invalid magic number in client struct")));
        LOGE2((ZT("HttpClient_StartRequest - Invalid magic number in client struct")));
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (self->connector == NULL)
    {
        LOGW((ZT("HttpClient_StartRequest - Connection was closed due to timeout or error")));
        LOGE2((ZT("HttpClient_StartRequest - connection was closed due to timeout or error")));
        return MI_RESULT_TIME_OUT;
    }

    /* create header page */
    self->connector->sendHeader =
        _CreateHttpHeader(verb, uri, headers, (data && *data) ? (*data)->u.s.size : 0);

    if (data != NULL)
    {
        self->connector->sendPage = *data;
        *data = NULL;
    }
    else
    {
        self->connector->sendPage = NULL;
    }

    /* set status to failed, until we know more details */
    self->connector->status = MI_RESULT_FAILED;
    self->connector->sentSize = 0;
    self->connector->sendingState = RECV_STATE_HEADER;
    self->connector->base.mask |= SELECTOR_WRITE;

    LOGD2((ZT("HttpClient_StartRequest - OK exit. URI: %s"), uri));

    _RequestCallbackWrite(self->connector);
    return MI_RESULT_OK;
}

MI_Result MI_EXPORT HttpClient_Run(
    HttpClient* self,
    MI_Uint64 timeoutUsec)
{
    /* Run the selector */
    if (self)
    {
        return Selector_Run(self->selector, timeoutUsec);
    }
    else
    {
        return MI_RESULT_FAILED;
    }
}

MI_Result MI_EXPORT HttpClient_SetTimeout(
    HttpClient* self,
    MI_Uint64 timeoutUsec)
{
    MI_Uint64 currentTimeUsec;

    Time_Now(&currentTimeUsec);

    /* check params */
    if (!self)
    {
        return MI_RESULT_INVALID_PARAMETER;
	}

    if (self->magic != _MAGIC)
    {
        LOGW((ZT("_SetTimeout: invalid magic!") ));
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (!self->connector)
    {
        return MI_RESULT_INVALID_PARAMETER;
	}

    /* create header page */
    self->connector->timeoutUsec = timeoutUsec;
    self->connector->base.fireTimeoutAt = (currentTimeUsec + self->connector->timeoutUsec);
    LOGD2((ZT("_SetTimeout - Timeout reset. socket: %d, new time: %s, %s sec. in the future"), self->connector->base.sock, FmtTime(self->connector->base.fireTimeoutAt), FmtInterval(self->connector->timeoutUsec)));
    return MI_RESULT_OK;
}
