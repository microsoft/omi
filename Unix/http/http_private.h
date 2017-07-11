/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_http_http_private_h
#define _omi_http_http_private_h

/*
**==============================================================================
**
** Local definitions:
**
**==============================================================================
*/
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
#undef EWOULDBLOCK
#endif
#define EWOULDBLOCK 0

#ifdef EINPROGRESS
#undef EINPROGRESS
#endif
#define EINPROGRESS 0

#define ERR_get_error() 0
#define ERR_error_string_n(c,a,b) a[0]=0
#define SSL_accept(c) 0

#endif

static const MI_Uint32 _MAGIC = 0xE0BB5FD3;
static const MI_Uint32 MAX_HEADER_SIZE     = 4 * 1024;
static const MI_Uint32 INITIAL_BUFFER_SIZE = 4 * 1024;
static const size_t HTTP_MAX_CONTENT = 1024 * 1024;

struct _Http {
    MI_Uint32 magic;
    Selector internalSelector;
    Selector *selector;
    OpenCallback callbackOnNewConnection;
    void *callbackData;
    SSL_CTX *sslContext;
    /* options: timeouts etc */
    HttpOptions options;
    MI_Boolean internalSelectorUsed;
};

typedef struct _Http_Listener_SocketData {
    /* based member */
    Handler base;

    MI_Boolean secure;
} Http_Listener_SocketData;

typedef enum _Http_RecvState {
    RECV_STATE_HEADER,
    RECV_STATE_CONTENT
} Http_RecvState;

typedef struct _Http_SR_SocketData {
    Strand strand;

    Handler handler;            // Used on selector

    Http *http;

    /* ssl part */
    SSL *ssl;
    MI_Boolean reverseOperations;   /*reverse read/write Events/Handlers */
    MI_Boolean acceptDone;

    /* is server/provider is processing request
       (to disbale timeout) */
    MI_Boolean requestIsBeingProcessed;

    /* receiving data */
    char *recvBuffer;
    size_t recvBufferSize;
    size_t receivedSize;
    Http_RecvState recvingState;
    HttpHeaders recvHeaders;
    Page *recvPage;
    HttpRequestMsg *request;    // request msg with the request page

    /* sending part */
    Page *sendPage;
    Page *sendHeader;
    size_t sentSize;
    Http_RecvState sendingState;

    int httpErrorCode;

    /* Enumeration saying what type (HTTP_AUTH_TYPE). */
    AuthMethod httpAuthType;

    /* Set true when auth has passed */
    MI_Boolean isAuthorised;

    /* Set true when auth has failed */
    MI_Boolean authFailed;

    /* Set true when received encrypted request data */
    MI_Boolean encryptedTransaction;

    /* Context for gss */
    void *pAuthContext;

    /* Context for gss */
    void *pVerifierCred;

    /* flags from gss_accept_seq_context  */
    MI_Uint32 negFlags;

    /* Requestor information */
    AuthInfo authInfo;

    /* pending send message */
    Message *savedSendMsg;

    char *pSendAuthHeader;
    int  sendAuthHeaderLen; // We know the len of the auth header when we build it.

    /* Enable tracing */
    MI_Boolean enableTracing;

    volatile ptrdiff_t refcount;
} Http_SR_SocketData;

/* helper functions result */
typedef enum _Http_CallbackResult {
    PRT_CONTINUE,
    PRT_RETURN_TRUE,
    PRT_RETURN_FALSE
} Http_CallbackResult;

MI_Boolean IsClientAuthorized(_In_ Http_SR_SocketData * handler);
void       Deauthorize(_In_ Http_SR_SocketData * handler);

MI_Boolean Http_DecryptData(_In_ Http_SR_SocketData * handler, _Out_ HttpHeaders * pHeaders,
                            _Out_ Page ** pData);
MI_Boolean 
Http_EncryptData(_In_ Http_SR_SocketData *handler, int contentLen, int contentTypeLen, char *contentType, _Out_ Page ** pData);

void HttpAuth_Close(_In_ Handler *handlerIn);

//struct gss_buffer_desc_struct;
//char *DecodeToken(struct gss_buffer_desc_struct *token);
#endif
