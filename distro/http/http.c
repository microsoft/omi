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
#include "http.h"
#include <sock/addr.h>
#include <sock/sock.h>
#include <sock/selector.h>
#include <base/time.h>
#include <base/buf.h>
#include <base/log.h>
#include <base/result.h>
#include <base/strings.h>
#include <base/paths.h>
#include <io/io.h>

#ifdef CONFIG_POSIX

#include <openssl/ssl.h>
#include <openssl/err.h>

#else
/* SSL not supported in this configuration; just make compiler happy */
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

static const MI_Uint32 _MAGIC = 0xE0BB5FD3;
static const MI_Uint32 MAX_HEADER_SIZE = 2 * 1024;
static const MI_Uint32 INITIAL_BUFFER_SIZE = 2 * 1024;
static const size_t HTTP_MAX_CONTENT = 1024 * 1024;

struct _Http
{
    MI_Uint32           magic;
    Selector        internalSelector;
    Selector*       selector;
    HttpCallbackOnNewConnection     callbackOnNewConnection;
    HttpCallbackOnCloseConnection   callbackOnCloseConnection;
    HttpCallbackOnRequest           callbackOnRequest;
    void*                               callbackData;
    SSL_CTX*    sslContext;
    /* options: timeouts etc */
    HttpOptions     options;
    MI_Boolean  internalSelectorUsed;
};

typedef struct _Http_Listener_SocketData
{
    /* based member*/
    Handler     base;
#define DATA_TAG_HTTP_LISTENER_SOCKETDATA    0x534C4854

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
    /* based member*/
    Handler     base;
#define DATA_TAG_HTTP_SR_SOCKETDATA    0x53534854

    /* ssl part */
    SSL*  ssl;
    MI_Boolean  reverseOperations;  /*reverse read/write Events/Handlers*/
    MI_Boolean  acceptDone;

    /* is server/provider is processing request
        (to disbale timeout) */
    MI_Boolean  requestIsBeingProcessed;

    /* link to next stack layer */
    void*  connectionData;

    /* receiving data */
    char*       recvBuffer;
    size_t      recvBufferSize;
    size_t      receivedSize;
    Http_RecvState  receivingState;
    HttpHeaders recvHeaders;
    Page*       recvPage;

    /* sending part */
    Page*       sendPage;
    size_t      sentSize;
    Http_RecvState  sendingState;
    int         httpErrorCode;
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

MI_INLINE MI_Uint8 _ToLower(MI_Uint8 x)
{
    return (MI_Uint8)tolower(x);
}

#define _HashCode(first,last,len) ( (((MI_Uint8)first) << 16) | (((MI_Uint8)last) << 8)  | (((MI_Uint16)len)) )

static MI_Boolean _DecodeBasicAuth(
    HttpHeaders* recvHeaders,
    const char * src,
    char* tgt)
{
    /* Please see RFC 2045 for details: http://www.ietf.org/rfc/rfc2045.txt. */

    /* decoding array 0-63 - valid value, 64-padding, 65-skip, -1-invalid */
    static const char s_decodingArray[] =
    {
        /* 0 - 31 */
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,

        /* 32 - 39  !"#$%&' */
        -1, -1, -1, -1, -1, -1, -1, -1,

        /* ()*+,-./ */
        -1, -1, -1, 62,  -1, -1, -1, 63,

        /* 0 -9 */
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61,

        /* :;<=>? */
        -1,-1,-1,64,-1,-1,

        /* @ A-Z */
        -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,

        /* []\\^_` */
        -1,-1,-1,-1,-1,-1,

        /* a-z */
        26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
        42, 43, 44, 45, 46, 47, 48, 49, 50, 51,

        /* {|} ~ 127 */
        -1, -1, -1, -1, -1
    };

    char* startBuffer = tgt;

    /* skip spaces in value */
    while (src[0] == ' ' || src[0] == '\t')
        src++;

    /* perform decoding - 4 input bytes are converted into 3 output,
        using provided pointers src/tgt
        since decoding is done in place and result is smaller than input,
        no check for buffer size is required */
    while (*src != 0)
    {
        signed char b1, b2, b3, b4;

        b1 = s_decodingArray[(*src++) & 0x7f];
        if (b1 < 0)
            return MI_FALSE;
        b2 = s_decodingArray[(*src++) & 0x7f];
        if (b2 < 0)
            return MI_FALSE;
        b3 = s_decodingArray[(*src++) & 0x7f];
        if (b3 < 0)
            return MI_FALSE;
        b4 = s_decodingArray[(*src++) & 0x7f];
        if (b4 < 0)
            return MI_FALSE;

        *tgt++ = (b1 << 2) | (b2 >> 4);

        if (b3 != 64)
        {
            *tgt++ = ((b2&0xF) << 4) | (b3 >> 2);
      }

        if (b4 != 64)
        {
            *tgt++ = ((b3&0x3) << 6) | (b4);
      }
    }
    *tgt = 0;

    /* decoded string has format:
        <uersname>[:<password>] */
    recvHeaders->username = startBuffer;
    startBuffer = strchr(startBuffer, ':');

    if (startBuffer != NULL)
    {
        *startBuffer = 0;
        recvHeaders->password = startBuffer + 1;
    }

    return MI_TRUE;
}

static MI_Boolean _getNameValuePair(
    char ** line,
    char ** value,
    int*  nameHashCode)
{
    int len = 0;
    char* p;
    /* find name end /hash-code */

    *nameHashCode =  _ToLower((MI_Uint8)(*line)[0])<<16;

    for (len = 1; (*line)[len] != ':' && (*line)[len] != '\r'; len++)
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
    for ( ; ; )
    {
        if (p[0] == '\r' && p[1] == '\n' && p[2] != ' ' && p[2] != '\t')
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
    {
        p--;
   }

    p[1] = '\0';

    return MI_TRUE;
}

static void _ParseContentType(
    HttpHeaders* recvHeaders,
    char* value)
{
    recvHeaders->contentType = value;

    /* find attribute list */
    while (value[0] != '\0' && value[0] != ';')
        value++;

    /* Check if attribute list was provided */
    if (value[0] == '\0')
        return;

    /* terminate type/subtype; move to attributes list */
    value[0] = '\0';
    value++;

    /* skip spaces in value */
    while (value[0] == ' ' || value[0] == '\t')
    {
        value++;
   }

    /* find charset attribute (if present) */
    if (Strncasecmp(value, "charset=", 8) != 0)
        return;

    value += 8;
    recvHeaders->charset = value;

    /* can be enclosed in quotes */
    if (value[0] == '"')
    {
        /* skip '"' */
        recvHeaders->charset++;
        value++;
        value = strchr(value, '"');
        if (value)
        {
            *value = '\0';
      }
        else
        {
            recvHeaders->charset = 0;
        }
    }
    else
    {
        /*skip trialing spaces */
        while (value[0] != '\0' && value[0] != ' ' && value[0] != '\t')
        {
            value++;
      }

        *value = '\0';
    }
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

    switch (nameHashCode)
    {
    case (_HashCode('c','e',12)): /*Content-Type*/
        if (Strcasecmp(name, "Content-Type") == 0)
            _ParseContentType(&handler->recvHeaders, value);

        break;

    case (_HashCode('c','h',14)): /*Content-Length*/
        if (Strcasecmp(name, "Content-Length") == 0)
        {
            handler->recvHeaders.contentLength = (size_t)Strtoull(value, NULL, 10);
            if (handler->recvHeaders.contentLength > HTTP_MAX_CONTENT)
                return MI_FALSE;
        }
        break;

    case (_HashCode('a','n',13)): /*Authorization*/
        if (Strcasecmp(name, "Authorization") == 0)
        {
            if (Strncasecmp(value, "Basic", 5) == 0)
            {
                /* since decoded string is smaller, performing decoding inplace;
                    for source skip 'Basic ' part (6 chars) */
                if (!_DecodeBasicAuth(&handler->recvHeaders, value + 6, value))
                {
                    LOGW((ZT("_getHeaderField - base64 decoding error in Basic auth: [%s]"), value));
                    return MI_FALSE;
                }
            }
            else    /* unknown authorization type */
                handler->recvHeaders.authorization = value;
        }
        break;

    default:
        break;

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

    if (handler->ssl == NULL)
    {
        MI_Result ret = Sock_Read(handler->base.sock, buf, buf_size, sizeRead);
        LOGD2((ZT("_Sock_Read - Regular read on socket %d. %u / %u bytes read"), handler->base.sock, (unsigned int)*sizeRead, (unsigned int)buf_size));
        return ret;
    }

    LOGD2((ZT("_Sock_Read - Begin. SSL read on socket %d"), handler->base.sock));

    handler->base.mask &= ~SELECTOR_WRITE;
    handler->base.mask |= SELECTOR_READ;
    handler->reverseOperations = MI_FALSE;

    *sizeRead = 0;

    if (handler->acceptDone)
    {
        res = SSL_read(handler->ssl, buf, buf_size);
        LOGD2((ZT("_Sock_Read - SSL_read returned %d (< 0 for error) / %u bytes read"), res, (unsigned int)buf_size));
    }
    else
    {
        res = SSL_accept(handler->ssl);
        LOGD2((ZT("_Sock_Read - SSL_accept returned %d"), res));
        if (res > 0)
        {
            /* we are done with accept */
            handler->acceptDone = MI_TRUE;
            LOGD2((ZT("_Sock_Read - Recursively calling _Sock_Read after accept")));
            return _Sock_Read(handler, buf, buf_size, sizeRead);
        }
        /* perform regular error checking */
    }

    if (res == 0)
    {
        LOGW2((ZT("_Sock_Read - HTTP connection closed")));
        return MI_RESULT_OK;    /* connection closed */
    }

    if (res > 0)
    {
        LOGD2((ZT("_Sock_Read - %d / %d bytes read. Returning OK"), res, (unsigned int)buf_size));
        *sizeRead = res;
        return MI_RESULT_OK;    /* ok */
    }

    switch (SSL_get_error(handler->ssl, res))
    {
    case SSL_ERROR_WANT_WRITE:
        handler->reverseOperations = MI_TRUE;   /* wait until write is allowed */
        handler->base.mask |= SELECTOR_WRITE;
        handler->base.mask &= ~SELECTOR_READ;
        LOGD2((ZT("_Sock_Read - SSL_read/accept returned WANT_WRITE")));
        return MI_RESULT_WOULD_BLOCK;

    case SSL_ERROR_WANT_READ:
        LOGD2((ZT("_Sock_Read - SSL_read/accept returned WANT_READ")));
        return MI_RESULT_WOULD_BLOCK;

    case SSL_ERROR_SYSCALL:
        if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINPROGRESS)
        {
            return MI_RESULT_WOULD_BLOCK;
        }
        if (*sizeRead == 0 && errno == ECONNRESET)
        {                               /* the client disconnected */
            return MI_RESULT_OK;
        }

        LOGW((ZT("_Sock_Read - SSL_read returned OS error: %d"), errno));
        LOGW2((ZT("_Sock_Read - SSL_read returned OS error: %d (%s)"), errno, strerror(errno)));
        break;

    default:
        {
            /* print OpenSSL error stack */
            unsigned long err = ERR_get_error();
            while (err != 0)
            {
                LOGE2((ZT("_Sock_Read - SSL_read returned OpenSSL error: %lu (%s)"), err, sslstrerror(err)));
                err = ERR_get_error();
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

    if (handler->ssl == NULL)
    {
        MI_Result ret = Sock_Write(handler->base.sock, buf, buf_size, sizeWritten);
        LOGD2((ZT("_Sock_write - Regular send of %u / %u bytes on socket %d. result: %d (%s)"), (unsigned int)*sizeWritten, (unsigned int)buf_size, (unsigned int)handler->base.sock, (int)ret, mistrerror(ret)));
        return ret;
    }

    /* Do not clear READ flag, since 'close' notification
    delivered as READ event*/
    handler->base.mask &= ~SELECTOR_READ;
    handler->base.mask |= SELECTOR_WRITE;
    handler->reverseOperations = MI_FALSE;

    *sizeWritten = 0;
    res = SSL_write(handler->ssl, buf, buf_size);
    LOGD2((ZT("_Sock_Write - SSL_write returned %d (< 0 for error) / %u bytes read"), (int)res, (unsigned int)buf_size));

    if (res == 0)
    {
        LOGW2((ZT("_Sock_Write - Connection closed")));
        return MI_RESULT_OK;    /* connection closed */
   }

    if (res > 0)
    {
        *sizeWritten = res;
        LOGD2((ZT("_SockWrite - Wrote %u / %u bytes. socket: %d"), (unsigned int)*sizeWritten, (unsigned int)buf_size, (int)handler->base.sock));
        return MI_RESULT_OK;    /* ok */
    }

    switch (SSL_get_error(handler->ssl, res))
    {
    case SSL_ERROR_WANT_WRITE:
        return MI_RESULT_WOULD_BLOCK;

    case SSL_ERROR_WANT_READ:
        handler->reverseOperations = MI_TRUE;   /* wait until write is allowed */
        handler->base.mask |= SELECTOR_READ;
        handler->base.mask &= ~SELECTOR_WRITE;
        LOGD2((ZT("_SockWrite - SSL_write returned WANT_READ")));
        return MI_RESULT_WOULD_BLOCK;

    case SSL_ERROR_SYSCALL:
        if (EAGAIN == errno ||
            EWOULDBLOCK == errno ||
            EINPROGRESS == errno)
        {
            LOGD2((ZT("_SockWrite - SSL_write returned EAGAIN")));
            return MI_RESULT_WOULD_BLOCK;
      }
        LOGW((ZT("_SockWrite - SSL_write returned OS error %d"), errno));
        LOGE2((ZT("_SockWrite - SSL_write returned OS error: %d (%s)"), errno, strerror(errno)));
        break;

    default:
        break;
    }

    return MI_RESULT_FAILED;
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
    if (handler->receivingState == RECV_STATE_CONTENT)
    {
        LOGD2((ZT("_ReadHeader - State is RECV_STATE_CONTENT")));
        return PRT_CONTINUE;
   }

    buf = handler->recvBuffer + handler->receivedSize;
    buf_size = handler->recvBufferSize - handler->receivedSize;
    received = 0;

    r = _Sock_Read(handler, buf, buf_size, &received);
    LOGD2((ZT("_ReadHeader - result: %d (%s), socket: %d, %u / %u bytes received, reverse %d"), (int)r, mistrerror(r), (int)handler->base.sock, (unsigned int)received, (unsigned int)buf_size, (int)handler->reverseOperations));

    if (r == MI_RESULT_OK && received == 0)
    {
        LOGE2((ZT("_ReadHeader - Connection closed")));
        return PRT_RETURN_FALSE; /* connection closed */
   }

    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        LOGE2((ZT("_ReadHeader - Error: %d (%s)"), (int)r, mistrerror(r)));
        return PRT_RETURN_FALSE;
   }

    if (received == 0)
    {
        LOGD2((ZT("_ReadHeader - No bytes received")));
        return PRT_RETURN_TRUE;
   }

    handler->receivedSize += received;

    /* check header */
    LOGD2((ZT("_Read_Header - Header: %s"), buf));

    /* did we get full header? */
    buf = handler->recvBuffer;
    for (index = 3; index < handler->receivedSize; index++)
    {
        if (buf[index-3] == '\r' && buf[index-1] == '\r' &&
            buf[index-2] == '\n' && buf[index] == '\n')
        {
            fullHeaderReceived = MI_TRUE;
            break;
        }
    }

    if (!fullHeaderReceived)
    {
        if (handler->receivedSize <  handler->recvBufferSize)
            return PRT_RETURN_TRUE; /* continue reading */

        if (handler->recvBufferSize < MAX_HEADER_SIZE)
        {
            buf = (char*)realloc(handler->recvBuffer, handler->recvBufferSize * 2);

            if (buf == NULL)
            {
                LOGE2((ZT("_ReadHeader - malloc failed")));
                return PRT_RETURN_FALSE;
         }

            handler->recvBufferSize *= 2;
            handler->recvBuffer = buf;
            return _ReadHeader(handler);
        }
        else
        {
            /* HTTP header is too big - drop connection */
            LOGW((ZT("_ReadHeader - HTTP header is too big; dropping connection")));
            LOGE2((ZT("_ReadHeader - HTTP header is too big; dropping connection")));
            return PRT_RETURN_FALSE;
        }
    }

    /* consume data */
    currentLine = buf;
    data = buf + index + 1; /* pointer to data in case we got some */

    if (!_getRequestLine(handler, &currentLine))
    {
        LOGE2((ZT("_ReadHeader - _getRequestLine failed")));
        return PRT_RETURN_FALSE;
    }

    while (data - currentLine > 3)
    {
        if (!_getHeaderField(handler, &currentLine))
        {
            LOGE2((ZT("_ReadHeader - _getHeaderField failed")));
            return PRT_RETURN_FALSE;
      }
    }

    /* Allocate zero-terminated buffer */
    handler->recvPage = (Page*)malloc(sizeof(Page) + handler->recvHeaders.contentLength + 1);

    if (handler->recvPage == NULL)
    {
        LOGE2((ZT("_ReadHeader - malloc failed")));
        return PRT_RETURN_FALSE;
   }

    memset(handler->recvPage, 0, sizeof(Page) + handler->recvHeaders.contentLength + 1);

    ((char*)(handler->recvPage + 1))[handler->recvHeaders.contentLength] = 0;

    handler->recvPage->u.s.size = (unsigned int)handler->recvHeaders.contentLength;
    handler->recvPage->u.s.next = 0;

    handler->receivedSize -= index + 1;

    /* Verify that we have not more than 'content-length' bytes in buffer left
        If we hvae more, assuming http client is invalid and drop connection */
    if (handler->receivedSize > handler->recvHeaders.contentLength)
    {
        LOGW((ZT("_ReadHeader - HTTP payload is bigger than content-length")));
        LOGE2((ZT("_ReadHeader - HTTP payload is bigger than content-length")));
        return PRT_RETURN_FALSE;
    }

    memcpy(handler->recvPage + 1, data, handler->receivedSize);
    handler->receivingState = RECV_STATE_CONTENT;

    LOGD2((ZT("_ReadHeader - Full header read. Page size: %d, Position: %u"), handler->recvPage->u.s.size, (unsigned int)handler->receivedSize));

    return PRT_CONTINUE;
}

static Http_CallbackResult _ReadData(
    Http_SR_SocketData* handler)
{
    Http* self = (Http*)handler->base.data;
    char* buf;
    size_t buf_size, received;
    MI_Result r;

    /* are we in the right state? */
    if (handler->receivingState != RECV_STATE_CONTENT)
    {
        LOGE2((ZT("_ReadData - State not RECV_STATE_CONTENT")));
        return PRT_RETURN_FALSE;
   }

    buf = (char*)(handler->recvPage + 1) + handler->receivedSize;
    buf_size = handler->recvHeaders.contentLength - handler->receivedSize;
    received = 0;

    if (buf_size != 0)
    {
        r = _Sock_Read(handler, buf, buf_size, &received);

        LOGD2((ZT("_Read_Data: socket: %d, MI result: %d (%s), %u / %u bytes read"), (int)handler->base.sock, (int)r, mistrerror(r), (unsigned int)received, (unsigned int)buf_size));
        if (r == MI_RESULT_OK && 0 == received)
        {
            LOGE2((ZT("_Read_Data - Connection closed")));
            return PRT_RETURN_FALSE; /* connection closed */
      }

        if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
        {
            LOGE2((ZT("_Read_Data - Connection closed")));
            return PRT_RETURN_FALSE;
      }

        handler->receivedSize += received;
    }

    /* did we get all data? */
    LOGD2((ZT("_ReadData - DT status: %d / %d"), (int)handler->receivedSize, (int)handler->recvHeaders.contentLength));

    if (handler->receivedSize != handler->recvHeaders.contentLength)
    {
        LOGD2((ZT("_Read_Data - Read %u / %u bytes"), (unsigned int)handler->receivedSize, (unsigned int)handler->recvHeaders.contentLength));
        return PRT_RETURN_TRUE;
   }

    handler->requestIsBeingProcessed = MI_TRUE;
    (*self->callbackOnRequest)(self, self->callbackData, handler->connectionData, handler, &handler->recvHeaders, &handler->recvPage);

    if (handler->recvPage != NULL)
    {
        free(handler->recvPage);
    }

    handler->recvPage = NULL;
    handler->receivedSize = 0;
    memset(&handler->recvHeaders, 0, sizeof(handler->recvHeaders));
    handler->receivingState = RECV_STATE_HEADER;
    return PRT_CONTINUE;
}

static MI_Boolean _RequestCallbackRead(
    Http_SR_SocketData* handler)
{
    switch (_ReadHeader(handler))
    {
    case PRT_CONTINUE:
        break;
    case PRT_RETURN_TRUE:
        return MI_TRUE;
    case PRT_RETURN_FALSE:
        return MI_FALSE;
    }

    switch (_ReadData(handler))
    {
    case PRT_CONTINUE:
        break;
    case PRT_RETURN_TRUE:
        return MI_TRUE;
    case PRT_RETURN_FALSE:
        return MI_FALSE;
    }
    return MI_TRUE;
}

/* length of longest description - has to be updated if descriptions are updated */
#define HTTP_LONGEST_ERROR_DESCRIPTION 50
static const char* _GetHttpErrorCodeDescription(
    int httpErrorCode)
{
    switch (httpErrorCode)
    {
    case 200:
        return "OK";

    case 400:
        return "Bad Request";

    case 401:
        return "Unauthorized";

    case 403:
        return "Forbidden";

    case 404:
        return "Not found";

    case 500:
        return "Internal Server Error";
    }
    return "Error";
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

/*    "SOAPAction: http://schemas.xmlsoap.org/ws/2004/08/addressing/fault\r\n"\ */

    char currentLine[sizeof(RESPONSE_HEADER_FMT) +
        10 /* content length */ +
        10 /*error code*/ +
        HTTP_LONGEST_ERROR_DESCRIPTION /* code descirpiton */ ];
    char* buf;
    size_t buf_size, sent;
    MI_Result r;

    /* Do we have any data to send? */
    if (handler->sendPage == NULL && handler->httpErrorCode == 0)
    {
        LOGE2((ZT("_WriteHeader - No header information")));
        return PRT_RETURN_TRUE;
   }

    /* are we done with header? */
    if (handler->sendingState == RECV_STATE_CONTENT)
    {
        LOGE2((ZT("_WriteHeader - Header already written")));
        return PRT_CONTINUE;
   }

    if (handler->sendPage != NULL)
    {
        buf_size = (size_t)Snprintf(
            currentLine,
            sizeof(currentLine),
            RESPONSE_HEADER_FMT,
            (int)handler->httpErrorCode,
            _GetHttpErrorCodeDescription(handler->httpErrorCode),
            (int)handler->sendPage->u.s.size);
    }
    else
    {
        buf_size = (size_t)Snprintf(
            currentLine,
            sizeof(currentLine),
            "HTTP/1.1 %d %s\r\n\r\n",
            (int)handler->httpErrorCode,
            _GetHttpErrorCodeDescription(handler->httpErrorCode));
    }

    buf = currentLine + handler->sentSize;

    sent = 0;

    r = _Sock_Write(handler, buf, buf_size - handler->sentSize, &sent);

    LOGD2((ZT("_WriteHeader - result: %d (%s), socket: %d, sent = %u / %u, reverse %d"), (int)r,  mistrerror(r), (int)handler->base.sock, (unsigned int)sent, (unsigned int)(buf_size - handler->sentSize), (int)handler->reverseOperations));

    if (r == MI_RESULT_OK && 0 == sent)
    {
        LOGE2((ZT("_WriteHeader - Connection closed. socket: %d, 0 bytes written"), (int)handler->base.sock));
        return PRT_RETURN_FALSE; /* connection closed */
   }

    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        LOGE2((ZT("_WriteHeader - Error: %d (%s), socket: %d"), (int)r, mistrerror(r), (int)handler->base.sock));
        return PRT_RETURN_FALSE;
   }

    if (sent == 0)
    {
        LOGW2((ZT("_WriteHeader - 0 bytes sent. socket: %d, result: %d (%s). 0 bytes sent"), (int)handler->base.sock, (int)r, mistrerror(r)));
        return PRT_RETURN_TRUE;
   }

    handler->sentSize += sent;

    LOGD2((ZT("_WriteHeader - OK exit. socket: %d, result: %d, sent: %u / %u"), (int)handler->base.sock, (int)r, (unsigned int)sent, (unsigned int)buf_size));
    if (handler->sentSize < buf_size)
    {
        return PRT_RETURN_TRUE;
   }

    /* set flags to next write is data, not header */
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
    {
        return PRT_RETURN_FALSE;
   }

    if (handler->sendPage == NULL)
    {   /* no content*/
        handler->httpErrorCode = 0;
        handler->sentSize = 0;
        handler->sendingState = RECV_STATE_HEADER;
        handler->base.mask &= ~SELECTOR_WRITE;
        handler->base.mask |= SELECTOR_READ;
        return PRT_CONTINUE;
    }

    buf = (char*)(handler->sendPage + 1) + handler->sentSize;
    buf_size = handler->sendPage->u.s.size - handler->sentSize;
    sent = 0;

    r = _Sock_Write(handler, buf, buf_size, &sent);
    if (r == MI_RESULT_OK && 0 == sent)
    {
        LOGE2((ZT("_WriteData - 0 bytes written. Connection closed. socket: %d"), (int)handler->base.sock));
        return PRT_RETURN_FALSE; /* connection closed */
   }

    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        LOGE2((ZT("_WriteData - Error: %d (%s), socket: %d"), (int)r, mistrerror(r), (int)handler->base.sock));
        return PRT_RETURN_FALSE;
   }

    handler->sentSize += sent;

    LOGD2((ZT("_WriteData - OK exit. socket: %d, result: %d, sent: %u / %u"), (int)handler->base.sock, (int)r, (unsigned int)sent, (unsigned int)buf_size));
    /* did we write all data? */
    if (handler->sentSize != handler->sendPage->u.s.size)
    {
        return PRT_RETURN_TRUE;
   }

    free(handler->sendPage);
    handler->sendPage = NULL;
    handler->httpErrorCode = 0;
    handler->sentSize = 0;
    handler->sendingState = RECV_STATE_HEADER;
    handler->base.mask &= ~SELECTOR_WRITE;
    handler->base.mask |= SELECTOR_READ;

    return PRT_CONTINUE;
}

static MI_Boolean _RequestCallbackWrite(
    Http_SR_SocketData* handler)
{
    switch (_WriteHeader(handler))
    {
    case PRT_CONTINUE:
        break;
    case PRT_RETURN_TRUE:
        return MI_TRUE;
    case PRT_RETURN_FALSE:
        return MI_FALSE;
    }

    switch (_WriteData(handler))
    {
    case PRT_CONTINUE:
        break;
    case PRT_RETURN_TRUE:
        return MI_TRUE;
    case PRT_RETURN_FALSE:
        return MI_FALSE;
    }
    return MI_TRUE;
}

static void _HttpSRSocketDataDestructor(Handler* handlerBase)
{
    Http_SR_SocketData* handler = (Http_SR_SocketData*)handlerBase;

    if (handler->ssl != NULL)
    {
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
    MI_UNUSED(sel);

    LOGD2((ZT("_RequestCallback - Begin. mask: 0x%02X (%s)"), mask, selectorflagstr(mask)));

    if (((mask & SELECTOR_READ) != 0 && !handler->reverseOperations) ||
        ((mask & SELECTOR_WRITE) != 0 && handler->reverseOperations))
    {
        if (!_RequestCallbackRead(handler))
        {
            LOGE2((ZT("_RequestCallback - Reading failed")));
            return MI_FALSE;
      }
    }

    if (((mask & SELECTOR_WRITE) != 0 && !handler->reverseOperations) ||
        ((mask & SELECTOR_READ) != 0 && handler->reverseOperations))
    {
        if (!_RequestCallbackWrite(handler))
        {
            LOGE2((ZT("_RequestCallback - Writing failed")));
            return MI_FALSE;
      }
    }

    /* reset timeout - if we performed R/W operation, set timeout depending where we are in communication */
    if ((mask & (SELECTOR_READ | SELECTOR_WRITE)) != 0)
    {
        Http* self = (Http*)handler->base.data;

        LOGD2((ZT("_RequestCallback - Resetting timeout")));
        if (handler->requestIsBeingProcessed)
        {
            /* since request is processed by server, disable timeout for this period */
            handler->base.fireTimeoutAt = TIME_NEVER;
            LOGD2((ZT("_RequestCallback - Read/write timeout disabled")));
        }
        else
        {
            /* Use configuration timeout */
            handler->base.fireTimeoutAt = currentTimeUsec + self->options.timeoutUsec;
            LOGD2((ZT("_RequestCallback - Timeout reset. socket: %d, new time: %s, %s sec. in the future"), handler->base.sock, FmtTime(handler->base.fireTimeoutAt), FmtInterval(self->options.timeoutUsec)));
        }
    }

    if ((mask & SELECTOR_TIMEOUT) != 0)
    {
        /* Close connection by timeout */
        LOGD2((ZT("_RequestCallback - Selector has returned a timeout flag")));
        return MI_FALSE;
    }

    if ((mask & SELECTOR_REMOVE) != 0 || (mask & SELECTOR_DESTROY) != 0)
    {
        LOGD2((ZT("_RequestCallback - Selector removed or destroyed")));

        Http* self = (Http*)handler->base.data;

        /* notify next stack layer */
        if (self != NULL && self->callbackOnCloseConnection != NULL)
        {
            (*self->callbackOnCloseConnection)(
                self,
                self->callbackData,
                handler->connectionData);
        }

        LOGD2((ZT("_RequestCallback - Selector remove or destroy. Closing socket: %d"), (int)handler->base.sock));

        Sock_Close(handler->base.sock);

        _HttpSRSocketDataDestructor((Handler*)handler);

        free(handler);
        handler = NULL;
    }

    return MI_TRUE;
}

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
    if ((mask & SELECTOR_READ) != 0)
    {
        int count;

        for (count = 0; count < 5; count++)
        {
            /* Accept the incoming connection */
            r = Sock_Accept(handler->base.sock, &s, &addr);

            LOGD2((ZT("_ListenerCallback - Sock_Accept returned result: %d (%s), socket: %d"), (int)r, mistrerror(r), (int)s));

            if (r == MI_RESULT_WOULD_BLOCK)
            {
                return MI_TRUE;
                        }

            if (r != MI_RESULT_OK)
            {
                LOGW((ZT("_ListenerCallback - Sock_Accept failed; err %d"), Sock_GetLastError()));
                LOGW2((ZT("_ListenerCallback - Sock_Accept failed with error: %d (%s), errno: %d"), (int)r, mistrerror(r), Sock_GetLastError()));
                return MI_TRUE;
            }

            r = Sock_SetBlocking(s, MI_FALSE);
            if (r != MI_RESULT_OK)
            {
                LOGW((ZT("_ListenerCallback - Sock_SetBlocking failed")));
                LOGW2((ZT("_ListenerCallback - Sock_SetBlocking failed with error %d (%s)"), (int)r, mistrerror(r)));
                Sock_Close(s);
                return MI_TRUE;
            }

            /* Create handler */
            h = (Http_SR_SocketData*)calloc(1, sizeof(Http_SR_SocketData));

            if (h == NULL)
            {
                Sock_Close(s);
                return MI_TRUE;
            }

            h->recvBufferSize = INITIAL_BUFFER_SIZE;
            h->recvBuffer = (char*)calloc(1, h->recvBufferSize);
            if (h->recvBuffer == NULL)
            {
                free(h);
                h = NULL;
                Sock_Close(s);
                return MI_TRUE;
            }

            h->base.type = DATA_TAG_HTTP_SR_SOCKETDATA;
            h->base.sock = s;
            h->base.mask = SELECTOR_READ | SELECTOR_EXCEPTION;
            h->base.callback = _RequestCallback;
            h->base.destructor = NULL;
            h->base.data = self;
            h->base.fireTimeoutAt = currentTimeUsec + self->options.timeoutUsec;

            /* SSL support */
            if (handler->secure)
            {
                h->ssl = SSL_new(self->sslContext);

                if (h->ssl == NULL)
                {
                    LOGW((ZT("_ListenerCallback - ssl_new failed")));
                    LOGW2((ZT("_ListenerCallback - ssl_new failed")));
                    free(h);
                    h = NULL;
                    Sock_Close(s);
                    return MI_TRUE;
                }

                if (!(SSL_set_fd(h->ssl, s)))
                {
                    LOGW((ZT("_ListenerCallback - ssl_set_fd failed")));
                    LOGW2((ZT("_ListenerCallback - ssl_set_fd failed")));
                    SSL_free(h->ssl);
                    h->ssl = NULL;
                    free(h);
                    h = NULL;
                    Sock_Close(s);
                    return MI_TRUE;
                }

            }

            /* Watch for read events on the incoming connection */
            r = Selector_AddHandler(self->selector, &h->base);

            if (r != MI_RESULT_OK)
            {
                LOGW((ZT("_ListenerCallback - Selector_AddHandler failed")));
                LOGW2((ZT("_ListenerCallback - Selector_AddHandler failed")));
                if (handler->secure)
                    SSL_free(h->ssl);
                h->ssl = NULL;
                _HttpSRSocketDataDestructor((Handler*)h);
                free(h);
                h = NULL;
                Sock_Close(s);
                return MI_TRUE;
            }

            /* notify next stack layer about new connection */
            (*self->callbackOnNewConnection)(self, self->callbackData, h, &h->connectionData);
        }
    }

    if ((mask & SELECTOR_REMOVE) != 0 || (mask & SELECTOR_DESTROY) != 0)
    {
        Sock_Close(handler->base.sock);
        free(handler);
        handler = NULL;
    }

    return MI_TRUE;
}

static MI_Result _New_Http(
    Http** selfOut,
    Selector* selector, /*optional, maybe NULL*/
    HttpCallbackOnNewConnection callbackOnNewConnection,
    HttpCallbackOnCloseConnection callbackOnCloseConnection,
    HttpCallbackOnRequest callbackOnRequest,
    void* callbackData)
{
    Http* self;

    /* Check parameters */
    if (selfOut == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    /* Clear output parameter */
    *selfOut = NULL;

    /* Allocate structure */
    self = (Http*)calloc(1, sizeof(Http));

    if (self == NULL)
    {
        LOGE2((ZT("_New_Http - malloc failed")));
        return MI_RESULT_FAILED;
    }

    if (selector != NULL)
    {   /* attach the exisiting selector */
        self->selector = selector;
        self->internalSelectorUsed = MI_FALSE;
    }
    else
    {   /* create a new selector */
        /* Initialize the network */
        Sock_Start();

        /* Initialize the selector */
        if (Selector_Init(&self->internalSelector) != MI_RESULT_OK)
        {
            free(self);
            self = NULL;
            LOGE2((ZT("_New_Http - Selector_Init failed")));
            return MI_RESULT_FAILED;
        }
        self->selector = &self->internalSelector;
        self->internalSelectorUsed = MI_TRUE;
    }

    /* Save the callback and callbackData */
    self->callbackOnRequest = callbackOnRequest;
    self->callbackOnCloseConnection = callbackOnCloseConnection;
    self->callbackOnNewConnection = callbackOnNewConnection;
    self->callbackData = callbackData;

    /* Set the magic number */
    self->magic = _MAGIC;

    /* options */
    {
        HttpOptions options = DEFAULT_HTTP_OPTIONS;

        self->options = options;
    }

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

    if (is == NULL)
    {
        LOGE((ZT("_verifyPrivateKey - Failed to open private key file: %s"), keyPath));
        LOGE2((ZT("_verifyPrivateKey - Failed to open private key file: %s"), keyPath));
        return MI_FALSE;
    }

    // Read the private key from the input stream.
    EVP_PKEY* pkey;
    pkey = PEM_read_PrivateKey(is, NULL, NULL, NULL);

    if (pkey == NULL)
    {
        LOGE((ZT("_verifyPrivateKey - Failed to create private key")));
        LOGE2((ZT("_verifyPrivateKey - Failed to create private key")));
        return MI_FALSE;
    }

    /* Close the input stream. */

    fclose(is);

    /* Associate the new private key with the SSL context object. */

    if (SSL_CTX_use_PrivateKey(ctx, pkey) <= 0)
    {
        EVP_PKEY_free(pkey);
        pkey = NULL;
        LOGE((ZT("_verifyPrivateKey - No private key found in %s"), keyPath));
        LOGE2((ZT("_verifyPrivateKey - No private key found in %s"), keyPath));
        return MI_FALSE;
    }

    EVP_PKEY_free(pkey);
    pkey = NULL;

    /* Check private key for validity. */

    if (!SSL_CTX_check_private_key(ctx))
    {
        LOGE((ZT("_verifyPrivateKey - Private and public key do not match")));
        LOGE2((ZT("_verifyPrivateKey - Private and public key do not match")));
        return MI_FALSE;
    }

    return MI_TRUE;
}

static MI_Result _CreateSSLContext(Http* self, char* sslCipherSuite)
{
    SSL_CTX* sslContext = SSL_CTX_new(SSLv23_method());
    if (sslContext == NULL)
    {
        LOGE(("_CreateSSLContext - Error creating SSL context"));
        LOGE2(("_CreateSSLContext - Error creating SSL context"));
        return MI_RESULT_FAILED;
    }

    if ( sslCipherSuite != NULL )
    {
        // Set the cipher list to the user specified cipher list.
        if ( SSL_CTX_set_cipher_list( sslContext, sslCipherSuite ) == 0 )
        {
            LOGE(("_CreateSSLContext - Error setting custom ciphers. The specified cipher list \"%s\" is invalid.", sslCipherSuite));
            LOGE2(("_CreateSSLContext - Error setting custom ciphers. The specified cipher list \"%s\" is invalid.", sslCipherSuite));
            return MI_RESULT_FAILED;
        }
    }

    SSL_CTX_set_quiet_shutdown(sslContext, 1);
    SSL_CTX_set_mode(sslContext, SSL_MODE_AUTO_RETRY);
    SSL_CTX_set_mode(sslContext, SSL_MODE_ENABLE_PARTIAL_WRITE);
    SSL_CTX_set_options(sslContext, SSL_OP_NO_SSLv2);
    SSL_CTX_set_session_cache_mode(sslContext, SSL_SESS_CACHE_OFF);

    /* Check if there is a certificate file (file containing server
    ** certificate) specified. If specified, validate and load the
    ** certificate.
    */
    {
        /* load the specified server certificates */
        LOGI((ZT("---> SSL: Loading server certificate from: %s"), GetPath(ID_PEMFILE)));
        LOGD2((ZT("---> SSL: Loading server certificate from: %s"), GetPath(ID_PEMFILE)));

        if (SSL_CTX_use_certificate_file(sslContext,
            GetPath(ID_PEMFILE), SSL_FILETYPE_PEM) <=0)
        {
            LOGE((ZT("---> SSL: No server certificate found in %s"), GetPath(ID_PEMFILE)));
            LOGE2((ZT("---> SSL: No server certificate found in %s"), GetPath(ID_PEMFILE)));
            SSL_CTX_free(sslContext);
            sslContext = NULL;
            return MI_RESULT_FAILED;
        }
    }

    /*
    ** Check if there is a key file (file containing server
    ** private key) specified and the key was not already loaded.
    ** If specified, validate and load the key.
    */
    {
        /* load the specified server certificates */
        LOGI(("---> SSL: Loading certificate's private key from: %s", GetPath(ID_KEYFILE)));

        //
        // load given private key and check for validity
        //
        if (!_verifyPrivateKey(sslContext, GetPath(ID_KEYFILE)))
        {
            LOGE((ZT("_CreateSSLContext - No SSL server certificate found in %s"), GetPath(ID_KEYFILE)));
            SSL_CTX_free(sslContext);
            sslContext = NULL;
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
    MI_Boolean secure)
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
            LOGE2((ZT("_CreateAddListenerSocket - Sock_CreateListener failed with error: %d (%s)"), (int)r, mistrerror(r)));
            return r;
        }

        r = Sock_SetBlocking(listener, MI_FALSE);
        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("_CreateAddListenerSocket - Sock_SetBlocking failed with error: %d (%s)"), (int)r, mistrerror(r)));
            Sock_Close(listener);
            return r;
        }
    }

    /* Watch for read events on the listener socket (client connections) */
    {
        Http_Listener_SocketData* h = (Http_Listener_SocketData*)calloc(1, sizeof(Http_Listener_SocketData));

        if (h == NULL)
        {
            LOGE2((ZT("_CreateAddListenerSocket - Out of memory")));
            Sock_Close(listener);
            return MI_RESULT_FAILED;
        }

        h->base.type = DATA_TAG_HTTP_LISTENER_SOCKETDATA;
        h->base.sock = listener;
        h->base.mask = SELECTOR_READ | SELECTOR_EXCEPTION;
        h->base.callback = _ListenerCallback;
        h->base.destructor = NULL;
        h->base.data = self;
        h->secure = secure;

        r = Selector_AddHandler(self->selector, &h->base);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("_CreateAddListenerSocket - Selector_AddHandler failed with error: %d (%s)"), (int)r, mistrerror(r)));
            Sock_Close(listener);
            free(h);
            h = NULL;
            return r;
        }
    }

    return MI_RESULT_OK;
}

MI_Result Http_New_Server(
    Http** selfOut,
    Selector* selector, /*optional, maybe NULL*/
    unsigned short http_port,   /* 0 to disable */
    unsigned short https_port,  /* 0 to disable */
    char* sslCipherSuite,       /* NULL to disable */
    HttpCallbackOnNewConnection callbackOnNewConnection,
    HttpCallbackOnCloseConnection callbackOnCloseConnection,
    HttpCallbackOnRequest callbackOnRequest,
    void* callbackData)
{
    Http* self;
    MI_Result r;

    /* allocate this, inits selector */
    r = _New_Http(selfOut, selector, callbackOnNewConnection,
        callbackOnCloseConnection, callbackOnRequest, callbackData);

    if (MI_RESULT_OK != r)
    {
        LOGE2((ZT("Http_New_Server - _Hew_Http failed with error: %d (%s)"), (int)r, mistrerror(r)));
        return r;
    }

    self = *selfOut;

    /* Create HTTP listener socket */
    if (http_port != 0)
    {
        r = _CreateAddListenerSocket(self, http_port, MI_FALSE);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("Http_New_Server - CreateAddListenerSocket failed with error %d (%s)"), (int)r, mistrerror(r)));
            Http_Delete(self);
            return r;
        }
    }

#ifdef CONFIG_POSIX
    /* Create HTTPS listener socket */
    if (https_port != 0)
    {
        /* init SSL */
        SSL_library_init();
// TODO: set up multi-threaded Open SSL environment.
        /* create context */
        r = _CreateSSLContext(self, sslCipherSuite);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("Http_New_Server - _CreateSSLCONTEXT failed with error: %d (%s)"), (int)r, mistrerror(r)));
            Http_Delete(self);
            return r;
        }

        /* create a socket */
        r = _CreateAddListenerSocket(self, https_port, MI_TRUE);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("Http_New_Server - _CreateAddListenerSocket failed with error: %d (%s)"), (int)r, mistrerror(r)));
            Http_Delete(self);
            return r;
        }
    }
#else
    MI_UNUSED(https_port);
#endif

    return MI_RESULT_OK;
}

MI_Result Http_Delete(
    Http* self)
{
    /* Check parameters */
    if (self == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
   }

    /* Check magic number */
    if (self->magic != _MAGIC)
    {
        return MI_RESULT_INVALID_PARAMETER;
   }

    if (self->internalSelectorUsed)
    {
        /* Release selector;
        Note: selector-destory closes all sockects in a list including connector and listener */
        Selector_Destroy(self->selector);

        /* Shutdown the network */
        Sock_Stop();
    }

    if (self->sslContext != NULL)
    {
        SSL_CTX_free(self->sslContext);
   }
    self->sslContext = NULL;

    /* Clear magic number */
    self->magic = 0xDDDDDDDD;

    /* Free self pointer */
    free(self);
    self = NULL;

    return MI_RESULT_OK;
}

MI_Result Http_Run(
    Http* self,
    MI_Uint64 timeoutUsec)
{
    LOGD2((ZT("Http_Run - self: %p, timeout: %lu usec."), self, (unsigned long)timeoutUsec));

    if (self == NULL)
    {
        LOGE2((ZT("Http_Run - Parameter is NULL\n")));
        return MI_RESULT_FAILED;
    }

    /* Run the selector */
    return Selector_Run(self->selector, timeoutUsec);
}

/* sends 'ok' response with provided content;
 if message is accepted to be sent, on return *data == null (taking memory ownership)*/
MI_Result Http_SendResponse(
    Http* self,
    void* httpConnectionHandle,
    int httpErrorCode,
    Page** data)
{
    Http_SR_SocketData* sendSock;

    /* check params */
    if (self == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
   }

    if (self->magic != _MAGIC)
    {
        LOGW((ZT("_SendIN_IO_thread: invalid magic number")));
        return MI_RESULT_INVALID_PARAMETER;
    }

    sendSock = (Http_SR_SocketData*)httpConnectionHandle;

    /* validate handler */

    if (MI_RESULT_OK != Selector_ContainsHandler(
            self->selector, (Handler*)sendSock))
    {
        LOGW((ZT("cannot send message: invalid handler (msg->clientID) %p"), sendSock));
        return MI_RESULT_INVALID_PARAMETER;
    }

    sendSock->requestIsBeingProcessed = MI_FALSE;

    sendSock->base.mask |= SELECTOR_WRITE;
    sendSock->base.mask &= ~SELECTOR_READ;

    if (data != NULL)
    {
        sendSock->sendPage = *data;
        *data = NULL;
    }
    else
    {
        sendSock->sendPage = NULL;
    }
    sendSock->httpErrorCode = httpErrorCode;

    sendSock->sentSize = 0;
    sendSock->sendingState = RECV_STATE_HEADER;
    _RequestCallbackWrite(sendSock);

    return MI_RESULT_OK;
}

/* Sets http options (mostly unit-test support) */
MI_Result Http_SetOptions(
    Http* self,
    const HttpOptions* options)
{
    /* check params */
    if (self == NULL || options == NULL)
        return MI_RESULT_INVALID_PARAMETER;

    if (self->magic != _MAGIC)
    {
        LOGW((ZT("Http_SetOptions: invalid magic number")));
        LOGW2((ZT("Http_SetOptions: invalid magic number")));
        return MI_RESULT_INVALID_PARAMETER;
    }

    self->options = *options;
    return MI_RESULT_OK;
}
