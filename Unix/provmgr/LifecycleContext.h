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

#ifndef _lifecyclecontext_h
#define _lifecyclecontext_h

#include "context.h"
#include "provmgr.h"
#include <common.h>
#include <indication/common/indicommon.h>

BEGIN_EXTERNC

/* Defines internal lifecycle indication context type */
struct _LifecycleContext
{
    MI_LifecycleIndicationContext base;
    MI_Uint32 magic;

    /* Reference to Provider */
    Provider* provider;

    /* Holds provider's callback data */
    MI_LifecycleIndicationCallback lifecycleCallback;
    void* callbackData;

    MI_Uint32 supportedTypesAggr;
    MI_Uint32 supportedTypesFromProv;
};
typedef struct _LifecycleContext LifecycleContext;

/*
 * Converts internal enum to MI indication type
 */
MI_Uint32 LifeContext_ConvertSupportedType(
    _In_ SubscriptionTargetType type );

/*
 * Aggregates the supportedTypes from all current subscriptions and notifies
 * the provider of a supportedTypes change.
 */
void LifeContext_UpdateSupportedTypes(
    _In_ LifecycleContext* context );

/*
 * Compares the specified type with that advertised by the provider to
 * confirm if they are compatible.
 */
MI_Boolean LifeContext_IsTypeSupported(
    _In_ LifecycleContext* context,
    _In_ MI_Uint32 supportedTypeToCheck );

/*
 * Allocates a new structure in the heap.
 */
LifecycleContext* LifeContext_New();

/*
 * De-allocates memory used by the context pointer.
 */
void LifeContext_Delete(
    _Pre_valid_ _Post_ptr_invalid_ LifecycleContext* context );

void LifeContext_Init(
    _In_ LifecycleContext* context,
    _In_ Provider* provider );

END_EXTERNC

#endif /* _lifecyclecontext_h */

