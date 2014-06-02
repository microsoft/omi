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

#include <disp/agentmgr.h>
#include <disp/disp.h>
#include "host.h"

/* Get ProvReg object from Dispatcher */
static ProvReg* _DISP_GetProvReg(_In_ void* disp)
{
    DEBUG_ASSERT(disp);
    return &((Disp*)disp)->provreg;
}

/*
* Handles request by Dispatcher, 
* i.e., relies on AgentMgr to send the request to provider
*/
static void _DISP_HandleRequest(
    _In_ void* disp,
    _Inout_ InteractionOpenParams* interactionParams, 
    _In_ const ProvRegEntry* proventry)
{
    AgentMgr_OpenCallbackData data;
    
    DEBUG_ASSERT(disp);

    data.self = &((Disp*)disp)->agentmgr;
    data.proventry = proventry;
    interactionParams->callbackData = &data;
    
    AgentMgr_OpenCallback(interactionParams);
}

/* Initialize host object from disp object */
_Use_decl_annotations_
int IndicationHost_InitFromDisp(
    void* disp,
    IndicationHost* host)
{
    return IndicationHost_Init(disp, _DISP_GetProvReg, _DISP_HandleRequest, host);
}

/* Initialize host object from given context and functions */
_Use_decl_annotations_
int IndicationHost_Init(
    void* context,
    fnGetProvReg getprovreg,
    fnHandleRequest handlerequest,
    IndicationHost* host)
{
    DEBUG_ASSERT(host);
    host->context = context;
    host->getProvReg = getprovreg;
    host->handleRequest = handlerequest;
    return 0;
}

/* Get ProvReg object from host */
ProvReg* IndicationHost_GetProvReg(_In_ IndicationHost* host)
{
    DEBUG_ASSERT(host);
    return host->getProvReg(host->context);
}

/* Ask host to handle request */
void IndicationHost_HandleRequest(
    _Inout_ InteractionOpenParams* interactionParams )
{
    IndicationHost_Data* data = (IndicationHost_Data*)interactionParams->callbackData;
    IndicationHost* host = data->host;
    const ProvRegEntry* proventry = data->proventry;
    
    DEBUG_ASSERT(host);
    host->handleRequest(host->context, interactionParams, proventry);
}

