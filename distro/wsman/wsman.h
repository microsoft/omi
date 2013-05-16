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
#include <http/http.h>

BEGIN_EXTERNC

typedef struct _WSMAN WSMAN;

/*
    Callback for processing new message.
    Parameters:
    protocol - pointer to a protocol object that received a message
    message - message; consumer ahs to call 'AddRef' to keep message around
        longer than callback's lifetime
    data - user-provided callback data
    Return:
        return value is ignored by wsman object;
        added for consistency with bin Protocol
        however, all callbacks should retunr MI_TRUE for now
*/
typedef MI_Boolean (*WSMANCallback)(
    WSMAN* protocol,
    Message* message,
    void* data);

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
    WSMAN** self,
    Selector* selector, /*optional, maybe NULL*/
    unsigned short http_port,   /* 0 to disable */
    unsigned short https_port,  /* 0 to disable */
    char* sslCipherSuite,       /* NULL to disable */
    WSMANCallback callback,
    void* callbackData);

MI_Result WSMAN_Delete(
    WSMAN* self);

MI_Result WSMAN_Run(
    WSMAN* self,
    MI_Uint64 timeoutUsec);

MI_Result WSMAN_Send(
    WSMAN* self,
    Message* message);

/* Sets wsman options (mostly unit-test support) */
MI_Result WSMAN_SetOptions(
    WSMAN* self,
    const WSMAN_Options* options);

END_EXTERNC

#endif /* _omi_wsman_wsman_h */
