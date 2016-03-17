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

#include <pal/format.h>
#include <indication/common/indilog.h>
#include "SubscriptionContext.h"
#include "SubMgr.h"
#include "filter.h"
#include "context.h"
#include "nioproc.h"
#include <omi_error/errorutil.h>

/*
 * Perform initialization of a SubscriptionContext object.
 */
_Use_decl_annotations_
MI_Result SubscrContext_Init(
    SubscriptionContext* subCtx,
    Provider* provider,
    Context_Type type,    
    InteractionOpenParams* interactionParams,
    struct _SubMgrSubscription* subscription)
{
    MI_Result r;
    if (!subCtx || !interactionParams || !interactionParams->msg || !subscription)
    {
        trace_SubscriptionContext_NullParameter();
        return MI_RESULT_INVALID_PARAMETER;
    }

    DEBUG_ASSERT( CTX_TYPE_IND_SUBSCRIPTION == type || CTX_TYPE_IND_LIFECYCLE == type );

    subCtx->subscription = subscription;

    r = Context_Init_ByType( &subCtx->baseCtx, provider, interactionParams, type );
    if ( MI_RESULT_OK != r )
        subCtx->subscription = NULL;
    else
    {
        /*
         * Add refcount to subscription before calling into Subscribe,
         * which means the provider owning one refcount to the subscription,
         * the refcount will be released released within context.c:Context_PostMessageLeft
         *
         * Lifecycle contexts do not increment here because they do not call
         * subscribe.
         *
         */
         SubMgrSubscription_Addref(subCtx->subscription);
    }
    return r;
}

_Use_decl_annotations_
void SubscrContext_Close( 
    SubscriptionContext* subCtx )
{
    if (subCtx)
    {
        /* SubsriptionContext was allocated from the SubscribeReq Batch,
         * so it will be freed when the message's batch is freed. */
        subCtx->subscription = NULL;
        Context_Close(&subCtx->baseCtx);
    }
    else
        DEBUG_ASSERT(MI_FALSE); // Double free of Context / called on a NULL context
}

void _SendMessage(
    _In_ Context* ctx,
    _In_ Message* msgToSend )
{
    if (ctx->request->base.flags & WSMANFlag)
    {
        msgToSend->flags |= ctx->request->base.flags;
    }
    else /* Binary protocol */
    {
        msgToSend->flags |= BinaryProtocolFlag;
    }

    Context_PostMessageLeft( ctx, msgToSend );
}

/*
 * Notifies the indication manager of a state change in a subscription.
 */
_Use_decl_annotations_
MI_Result SubscrContext_SendFinalResultMsg(
    SubscriptionContext* subCtx,
    MI_Result result,
    const ZChar* errorMessage,
    const MI_Instance* cimError )
{
    Context* ctx = (Context*)subCtx;
    SubMgrSubscription* sub = subCtx->subscription;
    DEBUG_ASSERT( ctx && sub && ctx->request );

    /* check if final message already sent or not */
    if ( MI_FALSE == SubMgrSubscription_ShouldSendFinalMsg(sub) )
        return MI_RESULT_FAILED;

    trace_SubscrContext_SendFinalResultMsg( subCtx, result );

    /* Send PostResultMsg Message */
    {
        PostResultMsg* resp;
        
        if (result == MI_RESULT_OK)
            resp = PostResultMsg_New( ctx->request->base.operationId );
        else
        {
            resp = PostResultMsg_NewAndSerialize(&ctx->request->base, cimError, errorMessage, MI_RESULT_TYPE_MI, result);
        }
        if (!resp)
        {
            return MI_RESULT_FAILED;
        }

        resp->requestTag = ctx->request->base.tag;
        resp->requestFlags = ctx->request->base.flags;
        _SendMessage( ctx, (Message*)resp );

        trace_SubscrContext_SendFinalResultMsg_Sent(
            subCtx, result, resp, MessageName(resp->base.tag));

        PostResultMsg_Release(resp);

        if (ctx->result)
            *ctx->result = result;
    }
    return MI_RESULT_OK;
}

_Use_decl_annotations_
MI_Result SubscrContext_SendSubscribeResponseMsg(
    SubscriptionContext* subCtx )
{
    Context* ctx = (Context*)subCtx;
    trace_SubscrContext_SendSubscribeResponseMsg( subCtx );

    DEBUG_ASSERT( ctx->request );

    /* Send SubscribeRes Message */
    {
        SubscribeRes* resp = SubscribeRes_New( ctx->request->base.operationId );
        if (!resp)
        {
            return MI_RESULT_FAILED;
        }

        _SendMessage( ctx, (Message*)resp );

        trace_SubscrContext_SendSubscribeResponseMsg_Sent(
            subCtx, resp, MessageName(resp->base.tag) );

        SubscribeRes_Release(resp);

        if (ctx->result)
            *ctx->result = MI_RESULT_OK;
    }
    return MI_RESULT_OK;
}

SubMgrSubscription* SubscrContext_GetSubscription(
    _In_ SubscriptionContext* subCtx )
{
    return subCtx->subscription;
}

_Use_decl_annotations_
void SubscrContext_UnsubprvdOrSendfinalmsg(
    SubscriptionContext* subCtx,
    MI_Boolean invokeUnsubscribe,
    MI_Result finalResult)
{
    Provider* provider = subCtx->baseCtx.provider;
    SubMgrSubscription* subscription = subCtx->subscription;

    trace_SubscrContext_UnsubprvdOrSendfinalmsgStart( subCtx, provider, subscription, invokeUnsubscribe );

    if ( MI_TRUE == invokeUnsubscribe )
    {
        /*
         * Invoke Unsubscribe and get final result
         */
        Context ctx;
        MI_Result r = MI_RESULT_OK;
        Subunsub_Context_Init(&ctx, &r, subCtx->baseCtx.request);
        (*provider->classDecl->providerFT->Unsubscribe)(
            provider->self,
            &ctx.base,
            subscription->msg->nameSpace,
            subscription->msg->className,
            subscription->msg->subscriptionID,
            subCtx->subself);
        Context_Close(&ctx);
        finalResult = r;
    }

    /*
     * PostResult to Unsubscribe context does not send final result message,
     * thus send final result message explicitly
     */
    MI_Context_PostResult ( &subCtx->baseCtx.base, finalResult );

    trace_SubscrContext_UnsubprvdOrSendfinalmsgFinish( subCtx, provider, subscription, invokeUnsubscribe );
}

_Use_decl_annotations_
MI_Result SubscrContext_Unsubscribe(
    SubscriptionContext* subCtx)
{
    MI_Boolean invokeUnsubscribe = MI_FALSE;
    MI_Result result = MI_RESULT_OK;
    Provider* provider = subCtx->baseCtx.provider;
    SubMgrSubscription* subscription = subCtx->subscription;

    trace_SubscrContext_Unsubscribe( subCtx, provider, subscription );

    DEBUG_ASSERT(provider && subscription);
    DEBUG_ASSERT( (subCtx->baseCtx.ctxType == CTX_TYPE_IND_SUBSCRIPTION) ||
                  (subCtx->baseCtx.ctxType == CTX_TYPE_IND_LIFECYCLE) );

    if (subCtx->baseCtx.ctxType == CTX_TYPE_IND_LIFECYCLE)
    {
        goto DONE;
    }

    if (subscription->state == SubscriptionState_Unsubscribing ||
        subscription->state == SubscriptionState_Unsubscribed)
    {
        trace_SubscrContext_AlreadyUnsubscribed( subscription );
        result = MI_RESULT_FAILED;
        goto DONE;
    }
    else if (SubscriptionState_Subscribed != subscription->state)
    {
        trace_SubscrState_InvalidForUnsubscribe(
            (int)subscription->state, tcs(subscription->msg->className));
        result = MI_RESULT_FAILED;
        goto DONE;
    }

    DEBUG_ASSERT (provider->classDecl->providerFT &&
        provider->classDecl->providerFT->DisableIndications &&
        provider->classDecl->providerFT->Unsubscribe );

    SubMgrSubscription_SetState(subscription, SubscriptionState_Unsubscribing);

    if ( MI_FALSE == SubMgrSubscription_ShouldCallUnsubscribe(subscription) )
    {
        result = MI_RESULT_FAILED;
        goto DONE;
    }

    /* Leave strand here due to provider could post result on same thread */
    /* Otherwise could cause deadlock */
    Strand_Leave(&subCtx->baseCtx.strand);

    invokeUnsubscribe = MI_TRUE;

DONE:
    /* There is only one IO thread in current process, */
    /* which has dead lock issue if have multi-thread (include IO thread) posting messages */
    /* simultaneously. To resolve the issue, unsubscribe has to be invoked from a separate thread */
    /* Upon implementing multi-thread IO for OMI server, this workaround should be removed */
    Schedule_UnsubscribeProvider( subCtx, invokeUnsubscribe, result );

    trace_SubscrContext_UnsubscribeDone(subCtx, provider, subscription);
    return result;
}

