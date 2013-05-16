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

#ifndef _omi_http_http_h
#define _omi_http_http_h

#include "config.h"
#include <common.h>
#include <base/batch.h>
#include <sock/selector.h>

BEGIN_EXTERNC

/* HTTP Error codes */
#define HTTP_ERROR_CODE_OK      200
#define HTTP_ERROR_CODE_BAD_REQUEST                 400
#define HTTP_ERROR_CODE_UNAUTHORIZED                401
#define HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR       500
#define HTTP_ERROR_CODE_NOT_SUPPORTED               501

/* ************************************************ */
/*                  Datatypes                       */
/* ************************************************ */
typedef struct _Http Http;

/* Headers strucutre is creaetd provided by http module 
    and has several pre-parsed values from http headers */
typedef struct _HttpHeaders
{
    /* required fields */
    /* content type is pre-parsed: <content-type>;charset=<charset>*/
    const char* contentType;
    const char* charset;

    /* Authorization field: */
    /* for Basic, serer decodes username/pwd */
    const char* username;
    const char* password;

    /* for other than basci, server provides entire field: */
    const char* authorization;

    /* length of http payload */
    size_t  contentLength;

    /* The User-Agent header */
    const char* userAgent;
}
HttpHeaders;

/* HTTP options.
    mostly used for unit-testing; default values
    are hard-coded but can be overwritten by 
    unit-tests/config modules   */
typedef struct _HttpOptions
{
    /* timeout for network delays and keep-alive;
    note: http does not have timeout for server/provider processing */
    MI_Uint64   timeoutUsec;

    /* Enable tracing of HTTP input and output */
    MI_Boolean enableTracing;
}
HttpOptions;

/* 30 sec timeout */
#define DEFAULT_HTTP_OPTIONS  { (30 * 1000000), MI_FALSE }

/* ************************************************ */
/*                  callbacks                       */
/* ************************************************ */
/* invoked by http server when new connection is established
    this callback is called once before any 'OnRequest' calls
    and allows next stack layer to allocate connection-specific context
    */
typedef void (*HttpCallbackOnNewConnection)(
    Http* http,
    void* callbackData,
    void* httpConnectionHandle,
    void** connectionData);

/* invoked by http server when new request received
    (data contains the entire buffer);
    if user wants to keep 'data' buffer, it has to take ownership
    of the buffer by assigning *data = 0;
    headers has to be consumed within callback (either process or make a copy)
    */
typedef void (*HttpCallbackOnRequest)(
    Http* http,
    void* callbackData,
    void* connectionData,
    void* httpConnectionHandle,
    const HttpHeaders* headers,
    Page** data);

/* invoked by http server when exisiting connection is closed
    this callback is called once 
    and allows next stack layer to free connection-specific context
    */
typedef void (*HttpCallbackOnCloseConnection)(
    Http* http,
    void* callbackData,
    void* connectionData);

MI_Result Http_New_Server(
    Http** selfOut,
    Selector* selector, /*optional, maybe NULL*/
    unsigned short http_port,   /* 0 to disable */
    unsigned short https_port,  /* 0 to disable */
    char* sslCipherSuite,       /* NULL to disable */
    HttpCallbackOnNewConnection callbackOnNewConnection,
    HttpCallbackOnCloseConnection callbackOnCloseConnection,
    HttpCallbackOnRequest callbackOnRequest,
    void* callbackData);

MI_Result Http_Delete(
    Http* self);

MI_Result Http_Run(
    Http* self,
    MI_Uint64 timeoutUsec);

/* sends http response with given error code and provided content;
 if message is accepted to be sent, on return *data == null (taking memory ownership)*/
MI_Result Http_SendResponse(
    Http* self,
    void* httpConnectionHandle,
    int httpErrorCode,
    Page** data);

MI_INLINE MI_Result Http_SendErrorResponse(
    Http* self,
    void* httpConnectionHandle,
    int httpErrorCode)
{
    return Http_SendResponse(self, httpConnectionHandle, httpErrorCode, 0);
}

/* Sets http options (mostly unit-test support) */
MI_Result Http_SetOptions(
    Http* self,
    const HttpOptions* options);

END_EXTERNC

#endif /* _omi_http_http_h */
