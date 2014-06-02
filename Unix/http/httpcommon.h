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

#ifndef _omi_http_httpcommon_h
#define _omi_http_httpcommon_h

#include <stddef.h>

#include "config.h"
#include <common.h>
#include <base/batch.h>
#include <base/interaction.h>
#include <sock/selector.h>

BEGIN_EXTERNC

/* HTTP Error codes */
#define HTTP_ERROR_CODE_OK                          200
#define HTTP_ERROR_CODE_BAD_REQUEST                 400
#define HTTP_ERROR_CODE_UNAUTHORIZED                401
#define HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR       500
#define HTTP_ERROR_CODE_NOT_SUPPORTED               501

/*
**==============================================================================
**
** Define supported Authentication and other related fields.
**
**==============================================================================
*/
#define AUTHENTICATION_BASIC            "Basic"
#define AUTHENTICATION_BASIC_LENGTH     5 /*This is the length of "Basic"*/
#define HTTP_WWWAUTHENTICATE_BASIC      "WWW-Authenticate: Basic realm=\"WSMAN\""

/* ************************************************ */
/*                  Datatypes                       */
/* ************************************************ */
typedef struct _Http Http;

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

//------------------------------------------------------------------------------------------------------------------

/* 60 sec timeout */
#define DEFAULT_HTTP_OPTIONS  { (60 * 1000000), MI_FALSE }

MI_Result Http_New_Server(
    _Out_       Http**              selfOut,
    _In_        Selector*           selector,               /*optional, maybe NULL*/
    _In_        unsigned short      http_port,              /* 0 to disable */
    _In_        unsigned short      https_port,             /* 0 to disable */
    _In_opt_z_  const char*         sslCipherSuite,         /* NULL to disable */
    _In_        OpenCallback        callbackOnNewConnection,
    _In_opt_    void*               callbackData,
    _In_opt_    const HttpOptions*  options );              /* Sets http options (mostly unit-test support) */

MI_Result Http_Delete(
    Http* self);

MI_Result Http_Run(
    Http* self,
    MI_Uint64 timeoutUsec);

//------------------------------------------------------------------------------------------------------------------
// Auxiliary methods

MI_Boolean ParseAuthorization(
    _Inout_     HttpHeaders*    recvHeaders,
    _In_        CharPtr         value );

void ParseContentType(
    _Inout_     HttpHeaders*    recvHeaders,
    _In_        CharPtr         value );
    
#ifdef CONFIG_POSIX

char* GetSslErrorString(
    _Out_       char* buf,
    _In_        size_t bufLen);

#endif

END_EXTERNC

#endif /* _omi_http_httpcommon_h */
