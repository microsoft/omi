/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_http_httpclient_private_h
#define _omi_http_httpclient_private_h

/*
**==============================================================================
**
** Local definitions:
**
**==============================================================================
*/

static const MI_Uint32 _MAGIC = 0x5FC7B966;
static const MI_Uint32 MAX_HEADER_SIZE     = 64 * 1024;
static const MI_Uint32 INITIAL_BUFFER_SIZE = 16 * 1024;
static const MI_Uint32 DEFAULT_HTTP_TIMEOUT_USEC = 60 * 1000000;

typedef enum _Http_RecvState {
    RECV_STATE_HEADER,
    RECV_STATE_CONTENT,
    RECV_STATE_CHUNKHEADER,
    RECV_STATE_CHUNKDATA,
    RECV_STATE_CONNECT
} Http_RecvState;

typedef struct _HttpClient_SR_SocketData {
    /* based member */
    Handler base;

    /* timeout */
    MI_Uint64 timeoutUsec;

    /* ssl part */
    SSL *ssl;
    MI_Boolean reverseOperations;   /*reverse read/write Events/Handlers */
    MI_Boolean connectDone;

    /* receiving data */
     __field_ecount(recvBufferSize) char *recvBuffer;
    size_t recvBufferSize;
    size_t receivedSize;
    Http_RecvState recvingState;
    HttpClientHeaderField recvHeaderFields[64];
    HttpClientResponseHeader recvHeaders;
    MI_Sint64 contentLength;
    MI_Sint64 contentBegin;
    MI_Sint64 contentEnd;
    MI_Sint64 contentTotalLength;
    Page *recvPage;

    /* flag for a response from a HEAD request */
    MI_Boolean headVerb;

    /* sending part */
    Page *sendPage;
    Page *sendHeader;
    size_t sentSize;
    Http_RecvState sendingState;

    /* general operation status */
    MI_Result status;

    /* Enable tracing */
    MI_Boolean enableTracing;

    /* Authorisation state */
    MI_Boolean isAuthorized;    // We don't have to do any more authorising
    MI_Boolean authorizing;     // We are in the middle of the authorising process
    MI_Boolean encrypting;      // All data transfered is being encrypted.
    MI_Boolean readyToSend;     // We can send data now. This may occur before the context is fully established depending on GSS_C_PROT_FLAG (if supported)

    AuthMethod authType;
    char *username;
    char *user_domain;
    char *password;
    MI_Uint32 passwordLen;

    void *authContext;          // gss_context_t
    void *targetName;           // gss_name_t
    void *cred;                 // gss_cred_id_t
    AuthMechanism selectedMech;    // 
    MI_Uint32 negoFlags;

    /* Destination info. We use this in the authorisation transaction */

    char *hostHeader;           // Host: hostname:port
    char *hostname;             // host name (name or ip addr)
    Addr hostAddr;              // host address (resolved)
    MI_Uint32 port;             // port
    MI_Boolean secure;          // This is an SSL connection (https)
    MI_Boolean isPrivate;         // This connection is to be encrypted

    MI_Char *errMsg;           // Has a error mesisage produced in IsAuthorized or other areas 
                               // that have interesting information for CIMerror

    /* For the authorisation loop we need to retain the components of the original message */

    char *verb;                 // For regenerating the request during authorisation
    char *uri;                  // We do not own this data, and should not release it
    char *contentType;
    Page *data;

} HttpClient_SR_SocketData;

struct _HttpClient {
    MI_Uint32 magic;
    Selector internalSelector;
    Selector *selector;
    HttpClientCallbackOnConnect callbackOnConnect;
    HttpClientCallbackOnStatus2 callbackOnStatus;
    HttpClientCallbackOnResponse callbackOnResponse;
    void *callbackData;
    SSL_CTX *sslContext;

    HttpClient_SR_SocketData *connector;
    Probable_Cause_Data      *probableCause;

    MI_Boolean internalSelectorUsed;
};

/* helper functions result */
typedef enum _Http_CallbackResult {
    PRT_RETURN_FALSE,
    PRT_RETURN_TRUE,
    PRT_CONTINUE
} Http_CallbackResult;

Page *_CreateHttpHeader(const char *verb, const char *uri, const char *contentType,
                        const char *authHeader, const char *hostHeader, HttpClientRequestHeaders *extraHeaders, size_t size);

Http_CallbackResult HttpClient_RequestAuthorization(_In_ struct _HttpClient_SR_SocketData *self,
                                                    _Out_ const char **pAuthHeader);
Http_CallbackResult HttpClient_IsAuthorized(_In_ struct _HttpClient_SR_SocketData *self);

Http_CallbackResult _WriteClientData(HttpClient_SR_SocketData * handler);
Http_CallbackResult _WriteClientHeader(HttpClient_SR_SocketData * handler);

struct gss_buffer_desc_struct;
char *DecodeToken(struct gss_buffer_desc_struct *token);


MI_Boolean HttpClient_EncryptData(_In_ HttpClient_SR_SocketData * handler, _Out_ Page **pHeader, _Out_ Page ** pData);
MI_Boolean HttpClient_DecryptData(_In_ HttpClient_SR_SocketData * handler, _Out_ HttpClientResponseHeader* pHeaders, _Out_ Page ** pData);
#endif
