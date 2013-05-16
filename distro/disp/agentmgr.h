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

#ifndef _omi_agentmgr_h
#define _omi_agentmgr_h

#include <common.h>
#include <base/base.h>
#include <base/messages.h>
#include <provreg/provreg.h>
#include <provmgr/provmgr.h>
#include <sock/thread.h>
#include <sock/selector.h>

/*
**==============================================================================
**
** AgentMgr
**
**     This type implements the CIM server agent manager module, which:
**
**         (1) Spawns new agent processes
**
**         (2) Keeps track of active agent processes
**
**         (3) Retires inatcive agent processes
**
**         (4) Coordinates shutdown procedure
**
**==============================================================================
*/

typedef struct _AgentElem AgentElem;

typedef struct _AgentMgr
{
    ProvMgr provmgr;

    /* Directories */
    char* home;
    char* provDir;

    Selector* selector;

    /* Linked list of indication provider contexts - one per ns/cn pair */
    AgentElem* headAgents;
    AgentElem* tailAgents;

}
AgentMgr;

MI_Result AgentMgr_Init(
    AgentMgr* self,
    Selector* selector);

MI_Result AgentMgr_Destroy(
    AgentMgr* self);

MI_Result AgentMgr_HandleRequest(
    AgentMgr* self,
    Message* msg,
    const ProvRegEntry* proventry);

#endif /* _omi_agentmgr_h */
