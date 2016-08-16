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
static const MI_Uint32 MAX_HEADER_SIZE = 2 * 1024;
static const MI_Uint32 INITIAL_BUFFER_SIZE = 2 * 1024;
static const MI_Uint32 DEFAULT_HTTP_TIMEOUT_USEC = 60 * 1000000;

typedef enum _Http_RecvState
{
    RECV_STATE_HEADER,
    RECV_STATE_CONTENT,
    RECV_STATE_CHUNKHEADER,
    RECV_STATE_CHUNKDATA,
    RECV_STATE_CONNECT
}
Http_RecvState;

typedef struct _HttpClient_SR_SocketData
{
    /* based member*/
    Handler     base;

    /* timeout */
    MI_Uint64   timeoutUsec;

    /* ssl part */
    SSL*  ssl;
    MI_Boolean  reverseOperations;  /*reverse read/write Events/Handlers*/
    MI_Boolean  connectDone;

    /* receiving data */
    __field_ecount(recvBufferSize) char* recvBuffer;
    size_t      recvBufferSize;
    size_t      receivedSize;
    Http_RecvState      recvingState;
    HttpClientHeaderField recvHeaderFields[64];
    HttpClientResponseHeader   recvHeaders;
    MI_Sint64   contentLength;
    MI_Sint64   contentBegin;
    MI_Sint64   contentEnd;
    MI_Sint64   contentTotalLength;
    Page*   recvPage;

    /* flag for a response from a HEAD request */
    MI_Boolean  headVerb;

    /* sending part */
    Page*   sendPage;
    Page*   sendHeader;
    size_t      sentSize;
    Http_RecvState  sendingState;

    /* general operation status */
    MI_Result status;

    /* Enable tracing */
    MI_Boolean enableTracing;

    /* Authorisation state */
    MI_Boolean isAuthorized;  // We don't have to do any more authorising
    MI_Boolean authorizing; // We are in the middle of the authorising process

    AuthMethod authType;
    MI_Char*   username;
    MI_Char*   password;
    MI_Uint32  passwordLen;

    void *authContext;

    /* Destination info. We use this in the authorisation transaction */
    
    Addr      hostAddr; // host address (resolved)
    MI_Uint32 port;     // port
    MI_Uint32 secure;   // Http or Https

}
HttpClient_SR_SocketData;

struct _HttpClient
{
    MI_Uint32       magic;
    Selector        internalSelector;
    Selector*       selector;
    HttpClientCallbackOnConnect    callbackOnConnect;
    HttpClientCallbackOnStatus     callbackOnStatus;
    HttpClientCallbackOnResponse   callbackOnResponse;
    void*                          callbackData;
    SSL_CTX*    sslContext;

    HttpClient_SR_SocketData* connector;

    MI_Boolean  internalSelectorUsed;
};


/* helper functions result */
typedef enum _Http_CallbackResult
{
    PRT_RETURN_FALSE,
    PRT_RETURN_TRUE,
    PRT_CONTINUE
}
Http_CallbackResult;

Http_CallbackResult HttpClient_RequestAuthorization( _In_    struct _HttpClient_SR_SocketData *self, _Out_ const MI_Char **pAuthHeader );
Http_CallbackResult HttpClient_IsAuthorized( _In_ struct _HttpClient_SR_SocketData *self );

#endif
