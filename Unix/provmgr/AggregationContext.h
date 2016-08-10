/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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

