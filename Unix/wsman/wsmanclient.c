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
#include <pal/strings.h>
#include <base/base64.h>
#include <http/httpclient.h>
#include "wsmanclient.h"

struct _WsmanClient
{
    HttpClient *httpClient;
    void *callbackContext;
    WsmanClientStatusCallbackType callbackStatus;
    WsmanClientResponseCallbackType callbackResponse;
};
static void HttpClientCallbackOnStatusFn(
    HttpClient* http,
    void* callbackData,
    MI_Result result)
{
    WsmanClient *self = (WsmanClient*) callbackData;
    self->callbackStatus(self->callbackContext, result);
}

static MI_Boolean HttpClientCallbackOnResponseFn(
    HttpClient* http,
    void* callbackData,
    const HttpClientResponseHeader* headers,
    MI_Sint64 contentSize,
    MI_Boolean  lastChunk,
    Page** data)
{
    WsmanClient *self = (WsmanClient*) callbackData;
    return self->callbackResponse(self->callbackContext, headers, contentSize, lastChunk, data);
}
MI_Result WsmanClient_New_Connector(
        WsmanClient **selfOut,
        Selector *selector,
        const char* host,
        MI_DestinationOptions *options,
        WsmanClientStatusCallbackType callbackStatus,
        WsmanClientResponseCallbackType callbackResponse,
        void *callbackContext,
        const char* trustedCertDir,
        const char* certFile,
        const char* privateKeyFile)
{
    WsmanClient *self;
    MI_Result miresult;
    const MI_Char *transport;
    MI_Boolean secure = MI_TRUE;
    MI_Uint16 port;
    MI_Uint32 tmpPort;

    if (MI_DestinationOptions_GetTransport(options, &transport) == MI_RESULT_OK)
    {
        if (Tcscmp(transport, MI_DESTINATIONOPTIONS_TRANSPORT_HTTP) == 0)
        {
            secure = MI_FALSE;
            port = 5985;        /* Default WSMAN HTTP port */
        }
        else if (Tcscmp(transport, MI_DESTINATIONOPTIONS_TRANPSORT_HTTPS) == 0)
        {
            secure = MI_TRUE;
            port = 5986;        /* Default WSMAN HTTPS port */
        }
        else
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
    }
    if (MI_DestinationOptions_GetDestinationPort(options, &tmpPort) == MI_RESULT_OK)
    {
        /* Port exists so override default */
        port = (MI_Uint16) tmpPort;
    }

    self = (WsmanClient*) PAL_Calloc(1, sizeof(WsmanClient));
    if (!self)
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;

    self->callbackContext = callbackContext;
    self->callbackStatus = callbackStatus;
    self->callbackResponse = callbackResponse;

    miresult = HttpClient_New_Connector(
            &self->httpClient, selector,
            host, port, secure,
            HttpClientCallbackOnStatusFn, HttpClientCallbackOnResponseFn, self,
            trustedCertDir, certFile, privateKeyFile);
    if (miresult != MI_RESULT_OK)
        goto finished;

finished:
    if (miresult != MI_RESULT_OK)
    {
        PAL_Free(self);
    }
    else
    {
        *selfOut = self;
    }

    return miresult;
}

#define AUTHORIZE_HEADER_BASIC "Authorization: Basic "

MI_Result WsmanClient_Delete(WsmanClient *self)
{
    HttpClient_Delete(self->httpClient);
    PAL_Free(self);

    return MI_RESULT_OK;
}

typedef struct _PasswordEncData
{
    char *buffer;
    MI_Uint32 bufferLength;
} PasswordEncData;

static int _passwordEnc(
    const char* data,
    size_t size,
    void* callbackData)
{
    PasswordEncData *bufferData = (PasswordEncData*) callbackData;
    bufferData->bufferLength = sizeof(AUTHORIZE_HEADER_BASIC) + size;
    bufferData->buffer = (char *) PAL_Malloc(bufferData->bufferLength);
    if (bufferData->buffer == NULL)
    {
        return -1;
    }

    Strlcpy(bufferData->buffer, AUTHORIZE_HEADER_BASIC, bufferData->bufferLength);


    strncpy(bufferData->buffer+sizeof(AUTHORIZE_HEADER_BASIC)-1, data, size);
    bufferData->buffer[bufferData->bufferLength-1] = '\0';
    return 0;
}

static MI_Result WsmanClient_CreateAuthHeader(MI_DestinationOptions *options, char **finalAuthHeader)
{
    MI_Uint32 credCount;
    const MI_Char *optionName;
    MI_UserCredentials userCredentials;
    MI_Uint32 passwordLength;
    MI_Char *password; /* password from options */
    const MI_Char *username; /* username from option */
    char *authUsernamePassword; /* <username>:<password> in ansi ready for base64-encoding */
    MI_Uint32 authUsernamePasswordLength;
    PasswordEncData base64EncData;

    /* Must have one and only one credential */
    if ((MI_DestinationOptions_GetCredentialsCount(options, &credCount) != MI_RESULT_OK) ||
            (credCount != 1))
    {
        return MI_RESULT_ACCESS_DENIED;
    }

    /* Get username pointer from options.
     * Auth scheme must be basic as only one we support.
     * Option name must be __MI_DESTINATIONOPTIONS_DESTINATION_CREDENTIALS
     */
    if ((MI_DestinationOptions_GetCredentialsAt(options, 0, &optionName, &userCredentials, NULL) != MI_RESULT_OK) ||
        (Tcscmp(optionName, MI_T("__MI_DESTINATIONOPTIONS_DESTINATION_CREDENTIALS")) != 0) ||
        (Tcscmp(userCredentials.authenticationType, MI_AUTH_TYPE_BASIC) != 0))
    {
        return MI_RESULT_ACCESS_DENIED;
    }

    username = userCredentials.credentials.usernamePassword.username;

    /* We need to allocate a buffer for the password.
     * Get length of it, allocate and then retrieve it.
     */
    if (MI_DestinationOptions_GetCredentialsPasswordAt(options, 0, &optionName, NULL, 0, &passwordLength, NULL) != MI_RESULT_OK)
    {
        return MI_RESULT_ACCESS_DENIED;
    }

    password = (MI_Char*) PAL_Malloc(passwordLength * sizeof(MI_Char));
    if (password == NULL)
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    if (MI_DestinationOptions_GetCredentialsPasswordAt(options, 0, &optionName, password, passwordLength, &passwordLength, NULL) != MI_RESULT_OK)
    {
        PAL_Free(password);
        return MI_RESULT_FAILED;
    }

    /* Convert username and password into format needed for auth "<username>:<password>" as ANSI string */
    authUsernamePasswordLength = Tcslen(username) + 1 /* : */ + Tcslen(password);
    authUsernamePassword = (char*) PAL_Malloc(authUsernamePasswordLength + 1);
    if (authUsernamePassword == NULL)
    {
        PAL_Free(password);
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    StrTcslcpy(authUsernamePassword, username, authUsernamePasswordLength+1);
    Strlcat(authUsernamePassword, ":", authUsernamePasswordLength+1);
    StrTcslcat(authUsernamePassword, password, authUsernamePasswordLength+1);

    PAL_Free(password);

    /* Now we need to base64 encode the username:password string. We may as well
     * put the result in the final buffer
     */
    if (Base64Enc(authUsernamePassword, authUsernamePasswordLength, _passwordEnc, &base64EncData) == -1)
    {
        PAL_Free(authUsernamePassword);
        return MI_RESULT_FAILED;
    }

    /* Free up extra memory and set out parameter. We are done. */
    PAL_Free(authUsernamePassword);
    *finalAuthHeader = base64EncData.buffer;

    return MI_RESULT_OK;
}

MI_Result WsmanClient_StartRequest(WsmanClient* self, Page** data, MI_DestinationOptions *options)
{
    char *authorizationHeader = NULL;
    MI_Result miResult;
    const MI_Char *packetEncoding;
    const char *headerItems[2];
    const MI_Char *httpUrl_t = MI_T("\\wsman");
    char *httpUrl = "\\wsman";
    char *httpUrl_alloc = NULL;
    HttpClientRequestHeaders headers = { headerItems, MI_COUNT(headerItems) };

    if (options == NULL)
        return MI_RESULT_INVALID_PARAMETER;

#if defined(CONFIG_ENABLE_WCHAR)
    /* If packet encoding is in options then it must be UTF16 until we implement the conversion */
    if ((MI_DestinationOptions_GetPacketEncoding(options, &packetEncoding) == MI_RESULT_OK) &&
            (Tcscmp(packetEncoding, MI_DESTINATIONOPTIONS_PACKET_ENCODING_UTF16) != 0))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    headerItems[0] = "Content-Type: application/soap+xml;charset=UTF-16";
    return MI_RESULT_INVALID_PARAMETER; /* We cannot add a UTF-16 BOM to the front yet so need to fail */
#else
    /* If packet encoding is in options then it must be UTF8 until we implement the conversion */
    if ((MI_DestinationOptions_GetPacketEncoding(options, &packetEncoding) == MI_RESULT_OK) &&
            (Tcscmp(packetEncoding, MI_DESTINATIONOPTIONS_PACKET_ENCODING_UTF8) != 0))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    headerItems[0] = "Content-Type: application/soap+xml;charset=UTF-8";
#endif

    miResult = WsmanClient_CreateAuthHeader(options, &authorizationHeader);
    if (miResult != MI_RESULT_OK)
    {
        return miResult;
    }
    headerItems[1] = authorizationHeader;

    /* Retrieve custom http URL if one exists and convert to utf8 */
    miResult = MI_DestinationOptions_GetHttpUrlPrefix(options, &httpUrl_t);
    if ( miResult == MI_RESULT_OK)
    {
        MI_Uint32 len = Tcslen(httpUrl_t+1);
        httpUrl = PAL_Malloc(len);
        if (httpUrl == NULL)
        {
            miResult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            goto cleanup;
        }
        httpUrl_alloc = httpUrl;
        StrTcslcpy(httpUrl, httpUrl_t, len);
    }
    else if (miResult != MI_RESULT_NO_SUCH_PROPERTY)
    {
        goto cleanup;
    }

    miResult = HttpClient_StartRequest(self->httpClient, "POST", httpUrl, &headers, data);

cleanup:
    if (authorizationHeader)
        PAL_Free(authorizationHeader);
    if (httpUrl_alloc)
        PAL_Free(httpUrl_alloc);
    return miResult;
}

MI_Result WsmanClient_Run(WsmanClient* self, MI_Uint64 timeoutUsec)
{
    return HttpClient_Run(self->httpClient, timeoutUsec);
}
