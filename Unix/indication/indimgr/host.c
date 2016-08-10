/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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

