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
#ifndef _omi_wsman_wsmanclient_h
#define _omi_wsman_wsmanclient_h
#include "config.h"
#include <common.h>
#include <base/Strand.h>
#include <base/batch.h>
#include <base/interaction.h>
#include <sock/selector.h>
#include <http/httpclient.h>

BEGIN_EXTERNC

/* These callbacks will be replaced wuth interaction interface calls */
typedef void (*WsmanClientStatusCallbackType)(void *callbackData, MI_Result result);
typedef MI_Boolean (*WsmanClientResponseCallbackType)(void *callbackData, const HttpClientResponseHeader*headers, MI_Sint64 contentSize, MI_Boolean lastChunk, Page** date);

typedef struct _WsmanClient WsmanClient;

/* Create a connection to a remote machine */
MI_Result WsmanClient_New_Connector(
        WsmanClient **selfOut,
        Selector *selector, /* Either null for a global selector loop, or null to use our own */
        const MI_Char* host,
        MI_DestinationOptions *destinationOptions,
        InteractionOpenParams *params);

/* Protocol run loop that is used if a selector is not passed in to WsmanClient_New_Connector */
MI_Result WsmanClient_Run(WsmanClient* self, MI_Uint64 timeoutUsec);

/* Rest of these will be consumed by interaction interface */
MI_Result WsmanClient_Delete(WsmanClient *self);
MI_Result WsmanClient_StartRequest(WsmanClient* self, Page** data);


END_EXTERNC

#endif /* _omi_wsman_wsmanclient_h */
