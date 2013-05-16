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

#ifndef _omi_disp_h
#define _omi_disp_h

#include <common.h>
#include <base/base.h>
#include <base/messages.h>
#include <provreg/provreg.h>
#include <provmgr/provmgr.h>
#include <sock/thread.h>
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

    /* subscription part */
    /* next id - whenever it needed */
    MI_Uint64 nextID;   
    Mutex   mt;
    /* Linked list of indication provider contexts - one per ns/cn pair */
    ListElem* headIndCtx;
    ListElem* tailIndCtx;

}
Disp;

MI_Result Disp_Init(
    Disp* self, 
    Selector* selector);

MI_Result Disp_Destroy(
    Disp* self);

MI_Result Disp_HandleRequest(
    Disp* self,
    Message* msg);

#endif /* _omi_disp_h */
