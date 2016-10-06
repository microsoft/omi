/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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

// Call this once it is out of the selector run loop
void WsmanClient_ReadyToFinish( WsmanClient* self);

END_EXTERNC

#endif /* _omi_wsman_wsmanclient_h */
