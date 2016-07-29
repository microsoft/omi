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

#ifndef _omi_wsman_wsman_h
#define _omi_wsman_wsman_h

#include "config.h"
#include <string.h>
#include <common.h>
#include <base/messages.h>
#include <sock/selector.h>
#include <http/httpcommon.h>

BEGIN_EXTERNC

typedef struct _WSMAN WSMAN;

void _HttpCallbackOnNewConnection(_Inout_     InteractionOpenParams*  interactionParams );
void _HttpCallbackOnNewConnection_ChangeProtocol(_Inout_     InteractionOpenParams*  interactionParams );

/* WSMAN options.
    mostly used for unit-testing; default values
    are hard-coded but can be overwritten by
    unit-tests/config modules   */
typedef struct _WSMAN_Options
{
    /* timeout for enumerate context expiration
     * (time between enum/pull/pull/.. requests)
     */
    MI_Uint64 timeoutEnumContextUsec;

    /* Whether to trace to standard output or not */
    MI_Boolean enableTracing;

    /* Whether to do HTTP-leavel tracing */
    MI_Boolean enableHTTPTracing;
}
WSMAN_Options;

/* default WSMAN options */
#define DEFAULT_WSMAN_OPTIONS  { (10 * 60 * 1000000), MI_FALSE, MI_FALSE }

MI_Result WSMAN_New_Listener(
    _Out_       WSMAN**                 self,
    _In_opt_    Selector*               selector,       /* optional, maybe NULL */
    _In_opt_    unsigned short          http_port,      /* 0 to disable */
    _In_opt_    unsigned short          https_port,     /* 0 to disable */
    _In_opt_z_  const char*             sslCipherSuite, /* NULL to disable */
    _In_        Server_SSL_Options      sslOptions,     /* 0 for default options */
    _In_        OpenCallback            callback,
    _In_        void*                   callbackData,
    _In_opt_    const WSMAN_Options*    options);

MI_Result WSMAN_New_Listener_With_Socket(
    _Out_       WSMAN**                 self,
    _In_opt_    Selector*               selector,       /* optional, maybe NULL */
    _In_        int                     sock);          /* Socket to use */

MI_Result WSMAN_Delete(
    WSMAN* self);

MI_Result WSMAN_Run(
    WSMAN* self,
    MI_Uint64 timeoutUsec);

// Defined on server.c
void PrintProviderMsg( _In_ Message* msg);

void *CreateWSManObject( void );

END_EXTERNC

#endif /* _omi_wsman_wsman_h */
