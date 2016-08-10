/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _subscriptioncontext_h
#define _subscriptioncontext_h

#include "context.h"
#include "provmgr.h"
#include "filter.h"
#include <common.h>

BEGIN_EXTERNC

struct _SubMgrSubscription;

/*
 * Subscription Context that wraps an MI_Context structure for handling
 * user responses to indication operations.
 */
struct _SubscriptionContext
{
    Context baseCtx;

    struct _SubMgrSubscription* subscription;

    void* subself; // subscriptionSelf pointer

};

MI_Result SubscrContext_Init(
    _Inout_ SubscriptionContext* subCtx,
    _In_ Provider* provider,
    _In_ Context_Type type,
    _Inout_ InteractionOpenParams* interactionParams,
    _Inout_ struct _SubMgrSubscription* subscription );

void SubscrContext_Close( 
    _Pre_valid_ _Post_ptr_invalid_ SubscriptionContext* subCtx );

MI_Result SubscrContext_SendFinalResultMsg(
    _In_ SubscriptionContext* subCtx,
    _In_ MI_Result result,
    _In_opt_z_ const ZChar* errorMessage,
    _In_opt_ const MI_Instance* cimError );

MI_Result SubscrContext_SendSubscribeResponseMsg(
    _In_ SubscriptionContext* subCtx );
    
struct _SubMgrSubscription*  SubscrContext_GetSubscription(
    _In_ SubscriptionContext* subCtx );

MI_Result SubscrContext_Unsubscribe(
    _In_ SubscriptionContext* subCtx);

void SubscrContext_UnsubprvdOrSendfinalmsg(
    _In_ SubscriptionContext* subCtx,
    _In_ MI_Boolean invokeUnsubscribe,
    _In_ MI_Result finalResult);

END_EXTERNC

#endif /* _subscriptioncontext_h */
