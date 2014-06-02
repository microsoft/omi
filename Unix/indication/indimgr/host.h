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

#ifndef _indication_indimgr_host_h
#define _indication_indimgr_host_h

#include <common.h>
#include <provreg/provreg.h>
#include <base/interaction.h>

BEGIN_EXTERNC

/*
**==============================================================================
**
** IndicationManager calls this function to get ProvReg object
**
**==============================================================================
*/
typedef ProvReg* (*fnGetProvReg)(_In_ void* context);


/*
**==============================================================================
**
** IndicationManager calls this function to handle requests
**
**==============================================================================
*/
typedef void (*fnHandleRequest)(
    _In_ void* context,
    _Inout_ InteractionOpenParams* interactionParams, 
    _In_ const ProvRegEntry* proventry);

/*
**==============================================================================
**
** Represents a host of indication manager
** It provides runtime support for indication manager, such as
**  ProvReg object;
**  Handles the subscribe/unsubscribe request
**
**==============================================================================
*/
typedef struct _IndicationHost
{
    fnGetProvReg getProvReg;
    fnHandleRequest handleRequest;
    void* context;
}IndicationHost;

/*
**==============================================================================
** Initialize host object from disp object
**==============================================================================
*/
int IndicationHost_InitFromDisp(
    _In_ void* disp,
    _Out_ IndicationHost* host);

/*
**==============================================================================
** Initialize host object from given context and functions
**==============================================================================
*/
int IndicationHost_Init(
    _In_ void* context,
    _In_ fnGetProvReg getprovreg,
    _In_ fnHandleRequest handlerequest,
    _Out_ IndicationHost* host);

/*
**==============================================================================
** Get ProvReg object from host
**==============================================================================
*/
ProvReg* IndicationHost_GetProvReg(_In_ IndicationHost* host);

/*
**==============================================================================
** Ask host to handle request
**==============================================================================
*/
typedef struct _IndicationHost_Data
{
    IndicationHost* host;
    const ProvRegEntry* proventry;
} IndicationHost_Data;

void IndicationHost_HandleRequest(
    _Inout_ InteractionOpenParams* interactionParams );


END_EXTERNC

#endif /* _indication_indimgr_host_h */
