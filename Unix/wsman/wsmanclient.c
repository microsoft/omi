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
#include "wsmanclient.h"
#include <http/httpclient.h>

struct _WsmanClient
{
    HttpClient *httpClient;
};
static void HttpClientCallbackOnStatusFn(
    HttpClient* http,
    void* callbackData,
    MI_Result result)
{
}

static MI_Boolean HttpClientCallbackOnResponseFn(
    HttpClient* http,
    void* callbackData,
    const HttpClientResponseHeader* headers,
    MI_Sint64 contentSize,
    MI_Boolean  lastChunk,
    Page** data)
{
    return MI_TRUE;
}

MI_Result WsmanClient_New_Connector(
        WsmanClient **selfOut,
        const char* host,
        unsigned short port,
        MI_Boolean secure,
        const char* trustedCertDir,
        const char* certFile,
        const char* privateKeyFile)
{
    WsmanClient *self;
    MI_Result miresult;

    self = (WsmanClient*) PAL_Calloc(1, sizeof(WsmanClient));
    if (!self)
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;

    miresult = HttpClient_New_Connector(
            &self->httpClient, NULL,
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

MI_Result WsmanClient_Delete(WsmanClient *self)
{
    HttpClient_Delete(self->httpClient);
    PAL_Free(self);

    return MI_RESULT_OK;
}

MI_Result WsmanClient_StartRequest(WsmanClient* self, Page** data)
{
    return HttpClient_StartRequest(self->httpClient, "POST", "\\wsman", NULL, data);
}

MI_Result WsmanClient_Run(WsmanClient* self, MI_Uint64 timeoutUsec)
{
    return HttpClient_Run(self->httpClient, timeoutUsec);
}
