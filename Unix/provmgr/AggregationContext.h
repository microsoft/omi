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

#ifndef _aggregationcontext_h
#define _aggregationcontext_h

#include "context.h"
#include "provmgr.h"
#include <common.h>

BEGIN_EXTERNC

struct _SubscriptionManager;

/*
 * Master context for handling subscriptions to a class/provider.  It holds the
 * MI_Context passed during Enable and Disable indications calls to registered
 * MI providers.
 */
typedef struct _AggregationContext
{
    Context baseCtx;
    struct _SubscriptionManager* mgr;

} AggregationContext;

AggregationContext* AggrContext_New();

void AggrContext_Delete(
    _In_ _Post_invalid_ AggregationContext* self );

MI_Result AggrContext_Init(
    _Inout_ AggregationContext* self,
    _In_ Provider* provider,
    _In_  struct _SubscriptionManager* mgr );

void AggrContext_Close(
    _Inout_ AggregationContext* self );

struct _SubscriptionManager* AggrContext_GetManager(
    _In_ AggregationContext* self );

END_EXTERNC

#endif /* _aggregationcontext_h */

