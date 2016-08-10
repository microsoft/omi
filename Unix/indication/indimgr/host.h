/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
