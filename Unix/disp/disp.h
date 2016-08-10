/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_disp_h
#define _omi_disp_h

#include <common.h>
#include <base/base.h>
#include <base/messages.h>
#include <provreg/provreg.h>
#include <provmgr/provmgr.h>
#include <pal/thread.h>
#include <pal/atomic.h>
#include <indication/indimgr/mgr.h>
#include "agentmgr.h"

/*
**==============================================================================
**
** Disp
**
**     This type implements the CIM server dispatcher module, which:
**
**         (1) Accepts request messages (and a response callback).
**
**         (2) Creates sub-messages using the class relationships expressed
**             in the provider registry.
**
**         (3) Delegates messages and a response callback to the provider 
**             manager.
**
**         (4) Accepts response messages and routes them back to the requestor.
**
**==============================================================================
*/

typedef struct _Disp
{
    ProvReg     provreg;
    AgentMgr    agentmgr;

#ifndef DISABLE_INDICATION
    IndicationManager *indmgr;
#endif /* ifndef DISABLE_INDICATION */
}
Disp;

MI_Result Disp_Init(
    Disp* self, 
    Selector* selector);

MI_Result Disp_Reload(
    Disp* self);

MI_Result Disp_Destroy(
    Disp* self);


MI_Result Disp_HandleInteractionRequest(
    _In_ Disp* self,
    _Inout_ InteractionOpenParams* params );

#endif /* _omi_disp_h */
