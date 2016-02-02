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

#include "context.h"
#include "AggregationContext.h"
#include "SubscriptionContext.h"
#include "LifecycleContext.h"
#include "SubMgr.h"
#include <wsman/wsbuf.h>
#include <wql/wql.h>
#include <pal/format.h>
#include <pal/thread.h>
#include <pal/sleep.h>
#include "nioproc.h"
#include <omi_error/omierror.h>

STRAND_DEBUGNAME3( Context, TryPostLeft, TryPostLeftNotify, InvokeSubscribe );

static const MI_Uint32 _MAGIC = 0x35eb3d3b;

static MI_Result MI_CALL _PostError(
    _In_ MI_Context* self,
    MI_Uint32 result,
    _In_z_ const ZChar* type,
    _In_z_ const ZChar* message);

void _Context_Destroy(
    _Inout_ Context* self)
{
    RequestMsg* request = self ? self->request : 0;
    Message* loadRequest = self ? self->loadRequest : 0;

    trace_ContextDestroy( self, &self->strand, &self->strand.info.interaction );

    DEBUG_ASSERT( self );

    if (self->provider)
    {
        Provider_Release(self->provider);
    }

    memset(self, 0xFF, sizeof(Context));

    /* Context typically allocated from message's batch
     * so it may be freed right inside 'Release' call
     */
    if (request)
        Message_Release(&request->base);

    if (loadRequest)
        Message_Release(loadRequest);
}

/*
 * Post a message to the component to the left
 */
_Use_decl_annotations_
void Context_PostMessageLeft(
    Context* self,
    Message* msg)
{
    ptrdiff_t tryingToPostLeft;
// Uncomment when no longer using Selector
//#if !defined(CONFIG_OS_WINDOWS)
    ThreadID threadId = Thread_ID();
    Selector* selector = NULL;
    if (self->provider && self->provider->lib && self->provider->lib->provmgr)
        selector = self->provider->lib->provmgr->selector;
    else if (self->provmgr)
        selector = self->provmgr->selector;
//#endif

    // It is not clear if a Provider can Post concurrently in different threads (UT does)
    // so protect against it
    Lock_Acquire(&self->lock);

    DEBUG_ASSERT( NULL != self->strand.info.interaction.other );
    DEBUG_ASSERT( NULL == self->msgPostingLeft );
    DEBUG_ASSERT( 0 == self->tryingToPostLeft );

    // we dont need to add a reference to the message as
    // we are not going to leave this function on this thread until is sent
    // (event if it is actually sent in another thread)
    self->msgPostingLeft = msg;

// Uncomment when no longer using Selector
//#if !defined(CONFIG_OS_WINDOWS)
    if( Selector_IsSelectorThread( selector, &threadId ) )
    {
        Context_PostMessageLeft_IoThread( self );
        self->postingOnIoThread = MI_TRUE;
    }
//#endif
    Atomic_Swap(&self->tryingToPostLeft,(ptrdiff_t)(CONTEXT_POSTLEFT_POSTING|CONTEXT_POSTLEFT_SCHEDULED));

    Strand_ScheduleAux( &self->strand, CONTEXT_STRANDAUX_TRYPOSTLEFT );

    while( (tryingToPostLeft = ReadWithFence( &self->tryingToPostLeft )) != 0 )
    {
// Uncomment when no longer using Selector
//#if defined(CONFIG_OS_WINDOWS)
//        CondLock_Wait(
//            (ptrdiff_t)self, &self->tryingToPostLeft, tryingToPostLeft, CONDLOCK_DEFAULT_SPINCOUNT);
//#else
        if( self->postingOnIoThread )
        {
            Selector_Run( selector, TIME_NEVER, MI_TRUE );
        }
        else
        {
            CondLock_Wait(
                (ptrdiff_t)self, &self->tryingToPostLeft, tryingToPostLeft, CONDLOCK_DEFAULT_SPINCOUNT);
        }
//#endif
    }

    // Sent
    DEBUG_ASSERT( 0 == self->tryingToPostLeft );

#ifndef DISABLE_INDICATION
    if (CTX_TYPE_IND_SUBSCRIPTION == self->ctxType ||
        CTX_TYPE_IND_LIFECYCLE == self->ctxType)
    {
        SubscriptionContext* subCtx = (SubscriptionContext*)self;
        if (ReadWithFence(&subCtx->subscription->finalmsgbit) == 1)
        {
            /*
             * Release the refcount added by SubscrContext_Init
             */
            SubMgrSubscription_Release(subCtx->subscription);
        }
    }
#endif

    Lock_Release(&self->lock);
}

void Context_PostSchema(
    _In_ Context* self,
    _In_ Message* msg)
{
    Context_PostMessageLeft(self, msg);
}

_Use_decl_annotations_
void Context_Close( Context* self )
{
    // Note that some contexts are used internally (for example to load providers)
    // and therefore dont have an interaction
    if( NULL != self->strand.info.interaction.other )
    {
        Strand_ScheduleClose(&self->strand);
    }
    else
    {
        _Context_Destroy(self);
    }
}

static MI_Result _ProcessResult(
    MI_Context* self_,
    MI_Result result,
    const ZChar* errorMessage,
    const MI_Instance* cimError)
{
    Context* self = (Context*)self_;

    if (!self || self->magic != _MAGIC)
        return MI_RESULT_INVALID_PARAMETER;

    trace_Provider_PostResult(result);

    if (result == MI_RESULT_NOT_SUPPORTED &&
        self->request && self->request->base.tag == ModifyInstanceReqTag &&
        self->postedModifyInstance == MI_FALSE &&
        self->postedModifyGetInstance == MI_TRUE &&
        self->postedModifyEnumInstance != MI_TRUE)
    {
        /* Provider does not support GetInstance so we need to do an Enumerate instead */
        if (self->provider->classDecl->providerFT->EnumerateInstances)
        {
            ModifyInstanceReq* request = (ModifyInstanceReq*)self->request;

            /* convert this into a filtering enum because GetInstance is not implemented. */
            self->inst = self->keyInstance;
            self->instanceName = NULL;
            self->postedModifyEnumInstance = MI_TRUE;
            self->provider->classDecl->providerFT->EnumerateInstances(self->provider->self, self_, request->nameSpace, self->keyInstance->classDecl->name, NULL, MI_FALSE, NULL);
            return MI_RESULT_OK;
        }
        else
        {
            /* We cannot handle the contract, we we need to fail. Fall through to send an error */
        }
    }
    else if (result == MI_RESULT_OK && self->request && self->request->base.tag == ModifyInstanceReqTag && self->postedModifyInstance == MI_FALSE)
    {
        ModifyInstanceReq* request = (ModifyInstanceReq*) self->request;
        /* Need to re-send the request now as a GetInstance so we can get the final result. */
        if (self->provider->classDecl->providerFT->GetInstance)
        {
            self->postedModifyGetInstance = MI_TRUE;
            self->provider->classDecl->providerFT->GetInstance(self->provider->self, self_, request->nameSpace, self->keyInstance->classDecl->name, self->keyInstance, NULL);
            return MI_RESULT_OK;
        }
        else if (self->provider->classDecl->providerFT->EnumerateInstances)
        {
            /* convert this into a filtering enum because GetInstance is not implemented. */
            self->inst = self->keyInstance;
            self->instanceName = NULL;
            self->postedModifyEnumInstance = MI_TRUE;
            self->postedModifyGetInstance = MI_TRUE; /* For state management need to think we tried a GetInst */
            self->provider->classDecl->providerFT->EnumerateInstances(self->provider->self, self_, request->nameSpace, self->keyInstance->classDecl->name, NULL, MI_FALSE, NULL);
            return MI_RESULT_OK;
        }
        else
        {
            /* Cannot complete the operation because neither Get or Enum is supported. */
            result = MI_RESULT_NOT_SUPPORTED;
        }
    }

    /* If no instances matched during GetInstance over EnumerateInstance */
    if (self->instanceName && !self->matchedInstanceName)
    {
        if (result == MI_RESULT_OK)
            result = MI_RESULT_NOT_FOUND;
    }

    if (self->request && !self->cancelled)
    {
        PostResultMsg* resp = PostResultMsg_New( self->request->base.operationId );

        if (!resp)
            return MI_RESULT_FAILED;

        if (self->request->base.flags & WSMANFlag)
        {
            /* Need to clone this in case we need to thread switch. Not the most efficient,
             * but this is consumed in the error packet creation code and seems to be the
             * best way to achieve this for now.
             */
            resp->cimError = cimError;

            if (cimError)
            {
                WSBuf_InstanceToBuf(
                    self->request->userAgent,
                    cimError,
                    NULL, /* filterProperty */
                    NULL, /* filterPropertyData */
                    cimError->classDecl,
                    resp->base.batch,
                    WSMAN_ObjectFlag | WSMAN_IsCimError,
                    &resp->packedInstancePtr,
                    &resp->packedInstanceSize);

                resp->cimErrorClassName = Batch_Tcsdup(resp->base.batch, cimError->classDecl->name);
            }
            else
            {
                resp->packedInstancePtr = NULL;
                resp->packedInstanceSize = 0;
                resp->cimErrorClassName = NULL;
            }

            /* Need to clone this in case we need to thread switch */
            if (errorMessage)
            {
                resp->errorMessage = Batch_Tcsdup(resp->base.batch, errorMessage);
            }
            else
            {
                resp->errorMessage = NULL;
            }

            resp->result = result;

            resp->base.flags |= self->request->base.flags;
        }
        else /* Binary protocol */
        {
            resp->cimError = cimError;
            if (cimError)
            {
                InstanceToBatch(cimError, NULL, NULL, resp->base.batch, &resp->packedInstancePtr, &resp->packedInstanceSize);
                /* If the serialization fails we should just send the original error back. Seems bad to overrite it with this error */

                resp->cimErrorClassName = Batch_Tcsdup(resp->base.batch, cimError->classDecl->name);
            }
            else
            {
                resp->packedInstancePtr = NULL;
                resp->packedInstanceSize = 0;
                resp->cimErrorClassName = NULL;
            }
            if (errorMessage)
            {
                resp->errorMessage = Batch_Tcsdup(resp->base.batch, errorMessage);
            }
            else
            {
                resp->errorMessage = NULL;
            }
            resp->result = result;
            resp->base.flags |= BinaryProtocolFlag;
        }

        Context_PostMessageLeft( self, &resp->base);
        PostResultMsg_Release(resp);
    }

    if (self->result)
        *self->result = result;

    /* close/destroy context */
    Context_Close(self);

    return MI_RESULT_OK;
}

static MI_Boolean _FilterProperty(const ZChar* name, void *data)
{
    WQL* wql = (WQL*)data;

    if (WQL_ContainsProperty(wql, name))
        return MI_FALSE;
    else
        return MI_TRUE;
}

/*
 * This is an internal helper function that should be called from wrappers
 * that manage the lifecycle of the instance getting posted.
 */
static MI_Result _PostInstanceToCallback_Common(
    _In_ Context* self,
    _In_ const MI_Instance* instance,
    _In_ PostInstanceMsg* resp)
{
    MI_Result r = MI_RESULT_OK;

    if (self->request->base.flags & WSMANFlag)
    {
        const MI_ClassDecl* castToClassDecl = 0;

        /* Enumerate response with 'base-properties-only' option
            may require instance conversion */
        if (EnumerateInstancesReqTag == self->request->base.tag)
        {
            EnumerateInstancesReq* req = (EnumerateInstancesReq*)self->request;

            if (req->requestClassName)
            {
                castToClassDecl = instance->classDecl;

                while (castToClassDecl &&
                    Tcscasecmp(req->requestClassName, castToClassDecl->name) != 0)
                {
                    castToClassDecl = castToClassDecl->superClassDecl;
                }
            }
        }

        {
            EnumerateInstancesReq* req = NULL;

            if (EnumerateInstancesReqTag == self->request->base.tag)
                req = (EnumerateInstancesReq*)self->request;

            if (req && req->wql)
            {
                r = WSBuf_InstanceToBuf(
                    self->request->userAgent,
                    instance,
                    _FilterProperty,
                    req->wql,
                    castToClassDecl,
                    resp->base.batch,
                    self->request->base.flags,
                    &resp->packedInstancePtr,
                    &resp->packedInstanceSize);
            }
            else
            {
                r = WSBuf_InstanceToBuf(
                    self->request->userAgent,
                    instance,
                    NULL, /* filterProperty */
                    NULL, /* filterPropertyData */
                    castToClassDecl,
                    resp->base.batch,
                    self->request->base.flags,
                    &resp->packedInstancePtr,
                    &resp->packedInstanceSize);
            }
        }

        resp->base.flags |= self->request->base.flags;
    }
    else
    {
        EnumerateInstancesReq* req = NULL;

        if (EnumerateInstancesReqTag == self->request->base.tag)
            req = (EnumerateInstancesReq*)self->request;

        if (req && req->wql)
        {
            r = InstanceToBatch(
                instance,
                _FilterProperty,
                req->wql,
                resp->base.batch,
                &resp->packedInstancePtr,
                &resp->packedInstanceSize);
        }
        else
        {
            r = InstanceToBatch(
                instance,
                NULL,
                NULL,
                resp->base.batch,
                &resp->packedInstancePtr,
                &resp->packedInstanceSize);
        }

        resp->base.flags |= BinaryProtocolFlag;
    }


    if (r != MI_RESULT_OK)
        trace_PackInstanceFailed(r);
    else
        Context_PostMessageLeft( self, &resp->base);

    return r;
}

static MI_Result _PostInstanceToCallback(
    _In_ Context* self,
    _In_ const MI_Instance* instance)
{
    MI_Result result = MI_RESULT_OK;
    PostInstanceMsg* resp = PostInstanceMsg_New(self->request->base.operationId);

    if (!resp)
        return MI_RESULT_FAILED;

    result = _PostInstanceToCallback_Common( self, instance, resp );

    PostInstanceMsg_Release(resp);

    return result;
}

/* successfully received instance from 'gi' - call invoke with this instance now */
static void _CallInvoke(
    Context* self,
    const MI_Instance* instance)
{
    Context* ctx = (Context*)Batch_GetClear(self->request->base.batch, sizeof(Context));;

    // This is an internal context so it doesn't need an interaction
    Context_Init(ctx, self->provider->lib->provmgr, self->provider, NULL);

    ctx->request = self->request;
    /* message will be freed in context release*/
    Message_AddRef(&ctx->request->base);

    /* disregard all other messages for this context */
    self->cancelled = MI_TRUE;
    /* ATTN! clone instance, since invoke can overlive instance (if it's async)!!! */
    (*self->md->function)(self->prov_self, &ctx->base,
        __nameSpace, __className, __methodName, instance, self->instParams);
}

static MI_Result MI_CALL _PostResult(
    MI_Context* self_,
    MI_Result result)
{
    Context* self = (Context*)self_;

    /* Suppress MI_RESULT_NOT_SUPPORTED errors for operations which involve
     * multiple provdiders. For example, suppose the operation is handled by
     * providers A, B, and C. If providers A and B post MI_RESULT_OK but
     * provider C posts MI_RESULT_NOT_SUPPORTED, we must translate this error
     * to a MI_RESULT_OK to prevent the client from receiving it. The client
     * is only concerned with receiving valid instances, not with whether a
     * particular provider implements the operation.
     */
    if (result == MI_RESULT_NOT_SUPPORTED)
    {
        switch (self->request->base.tag)
        {
            case AssociatorsOfReqTag:
            case ReferencesOfReqTag:
                result = MI_RESULT_OK;
                break;
            default:
                break;
        }
    }

    if (result == MI_RESULT_OK)
        return _ProcessResult(self_, result, NULL, NULL);
    else
        return _PostError(self_, result, MI_RESULT_TYPE_MI, NULL);
}

static MI_Result MI_CALL _PostInstance(
    MI_Context* self_,
    const MI_Instance* instance)
{
    Context* self = (Context*)self_;

    if (!self || self->magic != _MAGIC || !instance)
        return MI_RESULT_INVALID_PARAMETER;

    if (self->request && !self->cancelled)
    {
        if (self->instanceName == NULL)
        {
            if (!Instance_ValidateNonNullKeys(instance))
            {
                /* Fail the Post if it has NULL key properties.  It is an
                 * invalid object. */
                return MI_RESULT_FAILED;
            }

            if (CTX_TYPE_INVOKE_WITH_INSTANCE == self->ctxType)
            {
                _CallInvoke(self, instance);
                return MI_RESULT_OK;
            }
            else if (EnumerateInstancesReqTag == self->request->base.tag)
            {
                EnumerateInstancesReq* req =
                    (EnumerateInstancesReq*)self->request;

                if (req->wql)
                {
                    int r;

                    r = WQL_Eval(req->wql, WQL_LookupInstanceProperty,
                        (void*)instance);

                    if (r == 0)
                    {
                        /* Instance matched the query */
                        return _PostInstanceToCallback(self, instance);
                    }
                    else
                    {
                        /* Mismatch or failure */
                        return MI_RESULT_OK;
                    }
                }
            }
            else if (ModifyInstanceReqTag == self->request->base.tag)
            {
                self->postedModifyInstance = MI_TRUE;
                return _PostInstanceToCallback(self, instance);
            }

            return _PostInstanceToCallback(self, instance);
        }
        else if (Instance_MatchKeys(instance, self->instanceName))
        {
            /* Handle GetInstance through EnumerateInstances */
            if (!self->matchedInstanceName)
            {
                self->matchedInstanceName = MI_TRUE;
                return _PostInstanceToCallback(self, instance);
            }
        }
    }

    return MI_RESULT_OK;
}

static Batch* _GetBatch(Context* self)
{
    if (self->provider && self->provider->lib && self->provider->lib->instanceLifetimeContext)
    {
        if (self->request)
            return self->request->base.batch;

        if (self->loadRequest)
            return self->loadRequest->batch;
    }

    return NULL;
}

static MI_Result MI_CALL _ConstructInstance(
    MI_Context* self_,
    const MI_ClassDecl* classDecl,
    MI_Instance* instance)
{
    Batch *batch = NULL;
    Context* self = (Context*)self_;

    if (!self || self->magic != _MAGIC || !instance || !classDecl)
        return MI_RESULT_INVALID_PARAMETER;

    batch = _GetBatch(self);

    return Instance_Construct(instance, classDecl, batch);
}

static MI_Result MI_CALL _ConstructParameters(
    MI_Context* self_,
    const MI_MethodDecl* methodDecl,
    MI_Instance* instance)
{
    Batch *batch = NULL;
    Context* self = (Context*)self_;

    if (!self || self->magic != _MAGIC || !instance || !methodDecl)
        return MI_RESULT_INVALID_PARAMETER;

    batch = _GetBatch(self);

    return Parameters_Init(instance, methodDecl, batch);
}

static MI_Result MI_CALL _NewInstance(
    MI_Context* self_,
    const MI_ClassDecl* classDecl,
    MI_Instance** instance)
{
    Batch *batch = NULL;
    Context* self = (Context*)self_;

    if (!self || self->magic != _MAGIC || !classDecl || !instance)
        return MI_RESULT_INVALID_PARAMETER;

    batch = _GetBatch(self);

    return Instance_New(instance, classDecl, batch);
}

static MI_Result MI_CALL _NewDynamicInstance(
    MI_Context* self_,
    const ZChar* className,
    MI_Uint32 flags,
    MI_Instance** instance)
{
    Batch *batch = NULL;
    Context* self = (Context*)self_;

    if (!self || self->magic != _MAGIC || !className || !instance)
        return MI_RESULT_INVALID_PARAMETER;

    batch = _GetBatch(self);

    return Instance_NewDynamic(instance, className, flags,
        batch);
}

static MI_Result MI_CALL _NewParameters(
    MI_Context* self_,
    const MI_MethodDecl* methodDecl,
    MI_Instance** instance)
{
    Batch *batch = NULL;
    Context* self = (Context*)self_;

    if (!self || self->magic != _MAGIC || !methodDecl || !instance)
        return MI_RESULT_INVALID_PARAMETER;

    batch = _GetBatch(self);

    return Parameters_New(instance, methodDecl, batch);
}

static MI_Result MI_CALL _Canceled(
    const MI_Context* self_,
    MI_Boolean* flag)
{
    Context* self = (Context*)self_;

    if (!self || self->magic != _MAGIC || !flag)
        return MI_RESULT_INVALID_PARAMETER;

    *flag = self->cancelled;
    return MI_RESULT_OK;
}

#ifndef DISABLE_INDICATION

static MI_Result _PostIndicationToCallback(
    _In_ Context* self,
    _In_ const MI_Instance* instance,
    _In_opt_z_ const ZChar* bookmark )
{
    MI_Result result = MI_RESULT_OK;
    PostIndicationMsg* resp = PostIndicationMsg_New(self->request->base.operationId);

    if (!resp)
        return MI_RESULT_FAILED;

    /* Copy bookmark into the message's Batch to control its lifetime. */
    if (bookmark)
    {
        const ZChar* tmp = Batch_Tcsdup(resp->base.base.batch, bookmark);

        if (!tmp)
        {
            PostIndicationMsg_Release(resp);
            return MI_RESULT_FAILED;
        }

        resp->bookmark = tmp;
    }

    result = _PostInstanceToCallback_Common( self, instance, (PostInstanceMsg*)resp );

    PostIndicationMsg_Release(resp);

    return result;
}

/*
 * PostIndication handler for SubscriptionContext.  It evaluates an indication
 * using a pre-specified indication filter.  It is placed here so that
 * _PostInstanceToCallback remains private to Context.c.
 */
MI_Result _SubscrContext_PostIndication(
    _In_ SubscriptionContext* context,
    _In_ const MI_Instance* indication,
    _In_opt_z_ const ZChar* bookmark,
    _In_ MI_Boolean subscriptionRefcounted)
{
    MI_Result result = MI_RESULT_OK;
    SubMgrSubscription* subscription = NULL;
    MI_Boolean isMatch = MI_FALSE;
    SubscriptionManager* subMgr;

    if (!context || !indication)
    {
        trace_PostIndicationWithNullInput();
        return MI_RESULT_INVALID_PARAMETER;
    }

    subMgr = context->baseCtx.provider->subMgr;
    DEBUG_ASSERT ( subMgr );

    if ( MI_FALSE == SubMgr_CanPostIndication( subMgr ) )
        return MI_RESULT_NOT_SUPPORTED;

    /* Ref counted, release later */
    if ( MI_FALSE == subscriptionRefcounted )
        subscription = SubMgr_GetSubscriptionByContext(subMgr, context);
    else
        subscription = context->subscription;

    if ( !subscription )
    {
        return MI_RESULT_FAILED;
    }

    if (SubscriptionState_Unsubscribing == subscription->state ||
        SubscriptionState_Unsubscribed == subscription->state)
    {
        trace_PostIndicationWithUnsubscribedContext();
        if ( MI_FALSE == subscriptionRefcounted)
            SubMgrSubscription_Release(subscription);
        return MI_RESULT_OK;
    }

    if (!Instance_ValidateNonNullKeys(indication))
    {
        /* Fail the Post if it has NULL key properties.  It is an
         * invalid object. */
        if ( MI_FALSE == subscriptionRefcounted)
            SubMgrSubscription_Release(subscription);
        return MI_RESULT_FAILED;
    }

    result = InstanceFilter_Filter( subscription->filter, indication, &isMatch );

    /* Check the evaluation status.  Only forward indications that satisfied
     * a known filter. */
    if (MI_RESULT_OK == result && isMatch)
    {
        SubMgrSubscription_AcuquirePostLock(subscription);
        if ( MI_FALSE == SubMgrSubscription_CancelStarted(subscription) )
            result = _PostIndicationToCallback((Context*)context, indication, bookmark);
        else
            result = MI_RESULT_FAILED;
        SubMgrSubscription_ReleasePostLock(subscription);
    }

    if ( MI_FALSE == subscriptionRefcounted)
        SubMgrSubscription_Release(subscription);

    return result;
}

MI_Result _SubscrContext_ProcessResult(
    _In_ Context* context,
    _In_ MI_Result result,
    _In_opt_z_ const ZChar* errorMessage,
    _In_opt_ const MI_Instance* cimError )
{
    /* subscription object is guaranteed live here since the provider owning one refcount */
    /* after this call, the refcount will be released */
    SubscriptionContext* subCtx = (SubscriptionContext*)context;
    SubMgrSubscription* subscription = SubscrContext_GetSubscription( subCtx );
    MI_Result r;

    DEBUG_ASSERT(subscription); /* This identifies any cases that may violate the refcount guarantee */

    SubMgrSubscription_Addref(subscription);

    Provider_RemoveSubscription(context->provider, subscription->subscriptionID);

#if !defined(_MSC_VER)
    {
        ThreadID tempId = Thread_ID();
        if (Thread_Equal(&tempId, &context->provider->lib->provmgr->ioThreadId))
        {
            /* For non-windows platform, there is only one IO thread in current process, */
            /* which has dead lock issue if have multi-thread (include IO thread) posting messages */
            /* simultaneously. To resolve the issue, unsubscribe has to be invoked from a separate thread */
            /* Upon implementing multi-thread IO for OMI server, this workaround should be removed */
            Schedule_SendFinalResult( subCtx, result );
            return MI_RESULT_OK;
        }
    }
#endif

    trace_SubscrContext_ProcessResult(UintThreadID(), subCtx, subscription);

    /* Handle failure responses */
    if (SubscriptionState_Subscribed == subscription->state ||
        SubscriptionState_Unsubscribing == subscription->state)
    {
        trace_SubscrContext_ProviderPostingFailure(result,
            ((subscription->state == SubscriptionState_Subscribed) ? PAL_T("subscribed") : PAL_T("unsubscribing")),
            subscription);
    }
    else
    {
        trace_SubscrContext_ProcessResult_InvalidState(UintThreadID(), subCtx, subscription, subscription->state);
    }

    SubMgrSubscription_AcuquirePostLock(subscription);
    r = SubscrContext_SendFinalResultMsg( subCtx, result, errorMessage, cimError );
    SubMgrSubscription_ReleasePostLock(subscription);

    SubMgrSubscription_Release(subscription);
    return r;
}

/*
 * PostIndication handler for AggregationContext.  It forwards an indication
 * to all known subscriptions for filter evaluation.  It is placed here so that
 * _PostInstanceToCallback remains private to Context.c.
 */
MI_Result _AggrContext_PostIndication(
    _In_ AggregationContext* context,
    _In_ const MI_Instance* indication,
    _In_opt_z_ const ZChar* bookmark )
{
    SubscriptionManager* subMgr = NULL;
    MI_Boolean atLeastOneDelivered = MI_FALSE;
    SubMgrSubscriptionPtr* sublist;
    MI_Result r;
    size_t count = 0;
    size_t i;

    if (!context || !indication)
    {
        trace_PostIndicationWithNullInput();
        return MI_RESULT_INVALID_PARAMETER;
    }

    subMgr = AggrContext_GetManager( context );

    /* Both of these states result in the same thing: the AggregationContext
     * must be cleaned up. */
    if ( (MI_FALSE == SubMgr_IsEnabled ( subMgr )) ||
         (MI_TRUE == SubMgr_IsSubListEmpty ( subMgr )))
    {
        trace_PostIndicationOnDisabledAggContext();
        return MI_RESULT_FAILED;
    }

    /* sublist holds one reference count to each subscription */
    r = SubMgr_GetSubscriptionList(subMgr, &sublist, &count);
    if ( r != MI_RESULT_OK )
        return r;

    for ( i = 0; i < count; i++ )
    {
        /*
         * This is a best-effort action
         * Intermediate failures will be ignored
         */
        r = _SubscrContext_PostIndication( sublist[i]->subscribeCtx, indication, bookmark, MI_TRUE );
        if ( MI_RESULT_OK == r )
        {
            atLeastOneDelivered = MI_TRUE;
        }
        /* release the one reference count */
        SubMgrSubscription_Release( sublist[i] );
    }

    return (atLeastOneDelivered ? MI_RESULT_OK : r);
}

/*
 * Handles AggregationContext cleanup during error scenarios derived from
 * PostResult, PostError, and PostCimError calls on the context.
 */
MI_Result _AggrContext_Terminate(
    Context* context,
    MI_Result result,
    const ZChar* errorMessage,
    const MI_Instance* cimError )
{
    return Provider_TerminateIndication(context->provider, result, errorMessage, cimError);
}

/*
 * Delegates AggregationContext Post calls depending on the state of the
 * context.
 */
MI_Result _AggrContext_ProcessResult(
    _In_ Context* context,
    _In_ MI_Result result,
    const ZChar* errorMessage,
    const MI_Instance* cimError )
{
    return _AggrContext_Terminate( context, result, errorMessage, cimError );
}

static MI_Result _Ind_Common_ProcessResult(
    _In_ MI_Context* context,
    _In_ MI_Result result,
    const ZChar* errorMessage,
    const MI_Instance* cimError )
{
    Context* self = (Context*)context;
    MI_Result toReturn = MI_RESULT_OK;

    if (!self || self->magic != _MAGIC)
    {
        trace_PostCalledWithInvalidContext();
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (!self->cancelled)
    {
        /* Engages filter handlers to determine if the indication instance is
         * appropriate for forwarding to clients. */
        switch (self->ctxType)
        {
            case CTX_TYPE_IND_AGGREGATION:
                toReturn = _AggrContext_ProcessResult( self, result, errorMessage, cimError );
                break;
            case CTX_TYPE_IND_SUBSCRIPTION:
            case CTX_TYPE_IND_LIFECYCLE:    /* Fallthrough expected */
                toReturn = _SubscrContext_ProcessResult( self, result, errorMessage, cimError );
                break;
            default:
                trace_UnknownIndicationContextType((int)self->ctxType);
                toReturn = MI_RESULT_NOT_FOUND;
                break;
        }
    }
    /* else: invalid indication post, so do nothing */

    return toReturn;
}

/* TODO: attach bookmark to PostIndicationMsg */
static MI_Result MI_CALL _Ind_PostIndication(
    MI_Context* context,
    const MI_Instance* indication,
    MI_Uint32 subscriptionIDCount,
    const ZChar* bookmark)
{
    MI_Result result = MI_RESULT_OK;
    Context* self = (Context*)context;
    MI_UNUSED(subscriptionIDCount);

    if (!self || self->magic != _MAGIC || !indication)
    {
        trace_PostCalledWithInvalidContext();
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (!self->cancelled)
    {
        /* Engages filter handlers to determine if the indication instance is
         * appropriate for forwarding to clients. */
        switch (self->ctxType)
        {
            case CTX_TYPE_IND_AGGREGATION:
                result = _AggrContext_PostIndication( (AggregationContext*)self, indication, bookmark );
                break;
            case CTX_TYPE_IND_SUBSCRIPTION: /* Fallthrough expected */
            case CTX_TYPE_IND_LIFECYCLE:
                result = _SubscrContext_PostIndication( (SubscriptionContext*)self, indication, bookmark, MI_FALSE );
                break;
            default:
                trace_UnknownIndicationContextType((int)self->ctxType);
                result = MI_RESULT_NOT_FOUND;
                break;
        }
    }
    /* else: invalid indication post, so do nothing */

    return result;
}

/*
 *_PostInstance is not supported for indication contexts.  Indications
 * must be posted using _PostIndication.
 */
static MI_Result MI_CALL _Ind_PostInstance(
    MI_Context* self_,
    const MI_Instance* instance)
{
    Context* self = (Context*)self_;

    if (!self || self->magic != _MAGIC || !instance)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
    return MI_RESULT_NOT_SUPPORTED;
 }

static MI_Result MI_CALL _Ind_PostResult(
    MI_Context* self_,
    MI_Result result)
{
    return _Ind_Common_ProcessResult( self_, result, NULL, NULL );
}

static MI_Result MI_CALL _Ind_PostError(
    _In_ MI_Context* self,
    MI_Uint32 result,
    _In_z_ const ZChar* type,
    _In_z_ const ZChar* message)
{
    if (NULL == type ||
        Tcscmp(type, MI_RESULT_TYPE_MI) != 0)
    {
        result = MI_RESULT_FAILED;
    }
    return _Ind_Common_ProcessResult(self, result, message, NULL);
}

static MI_Result MI_CALL _Ind_PostCimError(
    _In_ MI_Context* self,
    _In_ const MI_Instance *error)
{
    MI_Value value;
    MI_Type type;
    MI_Result result;

    result = MI_Instance_GetElement(error, MI_T("CIMStatusCode"), &value, &type, NULL, NULL);
    if ((MI_RESULT_OK != result) || (MI_UINT32 != type))
    {
        return _Ind_Common_ProcessResult(self, MI_RESULT_INVALID_CLASS_HIERARCHY, MI_T("Invalid CIM_Error object posted from provider"), NULL);
    }
    else
    {
        MI_Value messageValue;
        MI_Type messageType;

        result = MI_Instance_GetElement(error, MI_T("Message"), &messageValue, &messageType, NULL, NULL);
        if ((MI_RESULT_OK != result) || (MI_STRING != messageType))
        {
            messageValue.string = NULL;
        }
        return _Ind_Common_ProcessResult(self, value.uint32, messageValue.string, error);
    }
}

#endif /* ifndef DISABLE_INDICATION */

static MI_Result MI_CALL _PostIndication(
    MI_Context* context,
    const MI_Instance* indication,
    MI_Uint32 subscriptionIDCount,
    const ZChar* bookmark)
{
    MI_UNUSED(context);
    MI_UNUSED(indication);
    MI_UNUSED(subscriptionIDCount);
    MI_UNUSED(bookmark);

    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _GetLocale(
    const MI_Context* context,
    MI_LocaleType localeType,
    _Pre_writable_size_(MI_MAX_LOCALE_SIZE) ZChar locale[MI_MAX_LOCALE_SIZE])
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _RegisterCancel(
    MI_Context* context,
    MI_CancelCallback callback,
    void* callbackData)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _RequestUnload(
    MI_Context* self_)
{
    Context* self = (Context*)self_;

    if (!self || self->magic != _MAGIC || !self->provider)
        return MI_RESULT_INVALID_PARAMETER;

    Provider_SetRefuseUnloadFlag(self->provider, MI_FALSE);
    return MI_RESULT_OK;
}

static MI_Result MI_CALL _RefuseUnload(
    MI_Context* self_)
{
    Context* self = (Context*)self_;

    if (!self || self->magic != _MAGIC || !self->provider)
        return MI_RESULT_INVALID_PARAMETER;

    Provider_SetRefuseUnloadFlag(self->provider, MI_TRUE);
    return MI_RESULT_OK;
}

static MI_Result MI_CALL _GetLocalSession(
    _In_ const MI_Context* self_,
    _Out_ MI_Session* session)
{
#if defined(DISABLE_LOCALSESSION)
    MI_UNREFERENCED_PARAMETER(self_);
    MI_UNREFERENCED_PARAMETER(session);

    return MI_RESULT_NOT_SUPPORTED;
#else
    Context* self = (Context*)self_;

    if (!self || self->magic != _MAGIC || !self->provider || !self->provider->lib || !self->provider->lib->provmgr)
        return MI_RESULT_INVALID_PARAMETER;

    return ProvMgr_GetLocalSesson(self->provider->lib->provmgr, session);
#endif /* defined(DISABLE_LOCALSESSION) */
}

static MI_Result MI_CALL _SetStringOption(
    _In_ MI_Context* context,
    _In_z_ const ZChar* name,
    _In_z_ const ZChar* value)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _GetCustomOption(
    _In_  MI_Context* context_,
    _In_z_ const ZChar* name,
    _Out_opt_  MI_Type* valueType,
    _Out_opt_  MI_Value* value)
{
    Context* context = (Context*)context_;

    /* Check parameters */
    if (!context || !context->request)
        return MI_RESULT_INVALID_PARAMETER;

    /* Return zero if no option object */
    if (!context->request->options)
        return MI_RESULT_NO_SUCH_PROPERTY;

    return __MI_Instance_GetElement(
        context->request->options,
        name,
        value,
        valueType,
        NULL,
        NULL);
}

static MI_Result MI_CALL _GetCustomOptionCount(
    _In_  MI_Context* context_,
    _Out_opt_ MI_Uint32* count)
{
    Context* context = (Context*)context_;

    /* Check parameters */
    if (!context || !context->request)
        return MI_RESULT_INVALID_PARAMETER;

    /* Return zero if no option object */
    if (!context->request->options)
    {
        if (count)
            *count = 0;
        return MI_RESULT_OK;
    }

    return __MI_Instance_GetElementCount(context->request->options, count);
}

static MI_Result MI_CALL _GetCustomOptionAt(
    _In_  MI_Context* context_,
    _In_ MI_Uint32 index,
    _Outptr_opt_result_maybenull_z_  const ZChar** name,
    _Out_opt_  MI_Type* valueType,
    _Out_opt_  MI_Value* value)
{
    Context* context = (Context*)context_;

    /* Check parameters */
    if (!context || !context->request)
        return MI_RESULT_INVALID_PARAMETER;

    if (!context->request->options)
        return MI_RESULT_FAILED;

    return __MI_Instance_GetElementAt(
        context->request->options,
        index,
        name,
        value,
        valueType,
        0);
}

static MI_Result MI_CALL _GetStringOption(
    _In_  MI_Context* context,
    _In_z_ const ZChar* name,
    _Outptr_result_z_  const ZChar** valueOut)
{
    MI_Type type;
    MI_Value value;
    MI_Result r;

    r = _GetCustomOption(
        context,
        name,
        &type,
        &value);

    if (r != MI_RESULT_OK)
        return r;

    if (type != MI_STRING)
        return MI_RESULT_NO_SUCH_PROPERTY;

    if (valueOut)
        *valueOut = value.string;

    return MI_RESULT_OK;
}

static MI_Result MI_CALL _GetNumberOption(
    _In_  MI_Context* context,
    _In_z_ const ZChar *name,
    _Out_opt_  MI_Uint32* valueOut)
{
    MI_Type type;
    MI_Value value;
    MI_Result r;

    r = _GetCustomOption(
        context,
        name,
        &type,
        &value);

    if (r != MI_RESULT_OK)
        return r;

    if (type != MI_UINT32)
        return MI_RESULT_NO_SUCH_PROPERTY;

    if (valueOut)
        *valueOut = value.uint32;

    return MI_RESULT_OK;
}

static MI_Result MI_CALL _WriteMessage(
    _In_ MI_Context* context,
    MI_Uint32 channel,
    _In_z_ const ZChar* message)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _WriteProgress(
    _In_ MI_Context* context,
    _In_z_ const ZChar* activity,
    _In_z_ const ZChar* currentOperation,
    _In_z_ const ZChar* statusDescription,
    MI_Uint32 percentComplete,
    MI_Uint32 secondsRemaining)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _WriteStreamParameter(
    _In_ MI_Context* context,
    _In_z_ const ZChar* name,
    _In_ const MI_Value* value,
    _In_ MI_Type type,
    _In_ MI_Uint32 flags)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _WriteCimError(
    _In_ MI_Context* context,
    _In_ const MI_Instance *error,
    _Out_ MI_Boolean *flag)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _PromptUser(
    _In_ MI_Context* context,
    _In_z_ const ZChar* message,
    MI_PromptType promptType,
    _Out_ MI_Boolean* result)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _ShouldProcess(
    _In_ MI_Context* context,
    _In_z_ const ZChar* target,
    _In_z_ const ZChar* action,
    _Out_ MI_Boolean* result)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _ShouldContinue(
    _In_ MI_Context* context,
    _In_z_ const ZChar* message,
    _Out_ MI_Boolean* result)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _PostError(
    _In_ MI_Context* self,
    MI_Uint32 result,
    _In_z_ const ZChar* type,
    _In_z_ const ZChar* message)
{
    OMI_Error *omiError = NULL;
    MI_Result returnVal;

    if (NULL == type)
    {
        /* Don't know the error type so just use failed */
        type = MI_RESULT_TYPE_MI;
        result = MI_RESULT_FAILED;
    }
    returnVal = OMI_ErrorFromErrorCode(NULL, result, type, message, &omiError);
    if (returnVal == MI_RESULT_INVALID_PARAMETER)
    {
        /* invalid error type */
        type = MI_RESULT_TYPE_MI;
        result = MI_RESULT_FAILED;
    }
    if (returnVal != MI_RESULT_FAILED)
    {
        /* We ignore this error as we need to fail the operation */
        returnVal = _ProcessResult(self, result, message, (MI_Instance*)omiError);
    }
    else
    {
        if (message == NULL)
        {
            MI_Value messageValue;
            MI_Type messageType;

            returnVal = MI_Instance_GetElement(&omiError->__instance, MI_T("Message"), &messageValue, &messageType, NULL, NULL);
            if ((MI_RESULT_OK == returnVal) && (MI_STRING == messageType))
            {
                message = messageValue.string;
            }
        }
        returnVal = _ProcessResult(self, result, message, &omiError->__instance);
    }

    if ( omiError )
        MI_Instance_Delete(&omiError->__instance);

    return returnVal;
}

static MI_Result MI_CALL _PostCimError(
    _In_ MI_Context* self,
    _In_ const MI_Instance *error)
{
    MI_Value value;
    MI_Type type;
    MI_Result result;

    result = MI_Instance_GetElement(error, MI_T("CIMStatusCode"), &value, &type, NULL, NULL);
    if ((MI_RESULT_OK != result) || (MI_UINT32 != type))
    {
        return _ProcessResult(self, MI_RESULT_INVALID_CLASS_HIERARCHY, MI_T("Invalid CIM_Error object posted from provider"), NULL);
    }
    else
    {
        MI_Value messageValue;
        MI_Type messageType;

        result = MI_Instance_GetElement(error, MI_T("Message"), &messageValue, &messageType, NULL, NULL);
        if ((MI_RESULT_OK != result) || (MI_STRING != messageType))
        {
            messageValue.string = NULL;
        }
        return _ProcessResult(self, value.uint32, messageValue.string, error);
    }
}

static MI_Result MI_CALL _WriteError(
    _In_ MI_Context* context,
    MI_Uint32 resultCode,
    _In_z_ const ZChar* resultType,
    _In_z_ const ZChar* errorMessage,
    _Out_ MI_Boolean *flag)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result _GetLifecycleIndicationContext_NotSupported(
    _In_ const MI_Context* context,
    _Outptr_ MI_LifecycleIndicationContext** lifecycleContext)
{
    MI_UNREFERENCED_PARAMETER(context);
    *lifecycleContext = NULL;
    return MI_RESULT_NOT_SUPPORTED;
}

/*
 * Initializes lifecycle indication handling for a provider and populates the
 * lifecycleContext ptr if everything goes well.  Returns existing
 * LifecycleContext if it has already been initialized.
 */
static MI_Result _GetLifecycleIndicationContext(
    _In_ const MI_Context* context,
    _Outptr_ MI_LifecycleIndicationContext** lifecycleContext)
{
#ifdef DISABLE_INDICATION
    return _GetLifecycleIndicationContext_NotSupported(context, lifecycleContext);
#else

    Context* internalContext = (Context*)context;
    LifecycleContext* lifeCtx = NULL;

    /* Check if indication support has been enabled for this _Provider.  If
     * not, activate it.  Previously initialized support means that either
     * this provider is an Indication class or that a subscription already
     * exists.
     */
    lifeCtx = internalContext->provider->subMgr->lifecycleCtx;
    if (NULL == lifeCtx)
    {
        lifeCtx = LifeContext_New();
        if (NULL == lifeCtx)
        {
            return MI_RESULT_FAILED;
        }
        LifeContext_Init( lifeCtx, internalContext->provider );
        internalContext->provider->subMgr->lifecycleCtx = lifeCtx;
    }

    *lifecycleContext = (MI_LifecycleIndicationContext*)lifeCtx;

    return MI_RESULT_OK;
#endif
}

MI_ContextFT __mi_contextFT =
{
    // MI_Context_FT
    _PostResult,
    _PostInstance,
    _PostIndication,
    _ConstructInstance,
    _ConstructParameters,
    _NewInstance,
    _NewDynamicInstance,
    _NewParameters,
    _Canceled,
    _GetLocale,
    _RegisterCancel,
    _RequestUnload,
    _RefuseUnload,
    _GetLocalSession,
    _SetStringOption,
    _GetStringOption,
    _GetNumberOption,
    _GetCustomOption,
    _GetCustomOptionCount,
    _GetCustomOptionAt,
    _WriteMessage,
    _WriteProgress,
    _WriteStreamParameter,
    _WriteCimError,
    _PromptUser,
    _ShouldProcess,
    _ShouldContinue,
    _PostError,
    _PostCimError,
    _WriteError,
    _GetLifecycleIndicationContext,
};

#ifndef DISABLE_INDICATION

/*
 * Alternate MI_Context function table for handling indication functions.
 */
MI_ContextFT __mi_indication_contextFT =
{
    _Ind_PostResult,
    _Ind_PostInstance,
    _Ind_PostIndication,
    _ConstructInstance,
    _ConstructParameters,
    _NewInstance,
    _NewDynamicInstance,
    _NewParameters,
    _Canceled,
    _GetLocale,
    _RegisterCancel,
    _RequestUnload,
    _RefuseUnload,
    _GetLocalSession,
    _SetStringOption,
    _GetStringOption,
    _GetNumberOption,
    _GetCustomOption,
    _GetCustomOptionCount,
    _GetCustomOptionAt,
    _WriteMessage,
    _WriteProgress,
    _WriteStreamParameter,
    _WriteCimError,
    _PromptUser,
    _ShouldProcess,
    _ShouldContinue,
    _Ind_PostError,
    _Ind_PostCimError,
    _WriteError,
    _GetLifecycleIndicationContext_NotSupported,
};

/*
 * Alternate MI_Context function table for invoking subscribe and unsubscribe
 */

static MI_Result _subunsub_ProcessResult(
    MI_Context* self_,
    MI_Result result,
    const ZChar* errorMessage,
    const MI_Instance* cimError)
{
    Context* self = (Context*)self_;
    MI_UNREFERENCED_PARAMETER(errorMessage);
    MI_UNREFERENCED_PARAMETER(cimError);
    if (!self || self->magic != _MAGIC)
        return MI_RESULT_INVALID_PARAMETER;
    *self->result = result;
    return MI_RESULT_OK;
}

static MI_Result MI_CALL _subunsub_PostResult(
    MI_Context* self_,
    MI_Result result)
{
    return _subunsub_ProcessResult(self_, result, NULL, NULL);
}

static MI_Result MI_CALL _subunsub_PostError(
    _In_ MI_Context* self,
    MI_Uint32 result,
    _In_z_ const ZChar* type,
    _In_z_ const ZChar* message)
{
    if (NULL == type ||
        Tcscmp(type, MI_RESULT_TYPE_MI) != 0)
    {
        result = MI_RESULT_FAILED;
    }
    return _subunsub_ProcessResult(self, (MI_Result)result, message, NULL);
}

static MI_Result MI_CALL _subunsub_PostCimError(
    _In_ MI_Context* self,
    _In_ const MI_Instance *error)
{
    return _subunsub_ProcessResult(self, MI_RESULT_FAILED, NULL, error);
}

MI_ContextFT __mi_indication_subunsub_contextFT =
{
    _subunsub_PostResult,
    _Ind_PostInstance,
    _PostIndication,
    _ConstructInstance,
    _ConstructParameters,
    _NewInstance,
    _NewDynamicInstance,
    _NewParameters,
    _Canceled,
    _GetLocale,
    _RegisterCancel,
    _RequestUnload,
    _RefuseUnload,
    _GetLocalSession,
    _SetStringOption,
    _GetStringOption,
    _GetNumberOption,
    _GetCustomOption,
    _GetCustomOptionCount,
    _GetCustomOptionAt,
    _WriteMessage,
    _WriteProgress,
    _WriteStreamParameter,
    _WriteCimError,
    _PromptUser,
    _ShouldProcess,
    _ShouldContinue,
    _subunsub_PostError,
    _subunsub_PostCimError,
    _WriteError,
    _GetLifecycleIndicationContext_NotSupported,
};

/*
 * The Context that uses this table does not get exposed
 * to a _Provider, so it is considered "internal."
 */
MI_ContextFT __mi_lifecycleIndication_contextFT =
{
    _Ind_PostResult,
    NULL,
    _Ind_PostIndication,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

#endif /* ifndef DISABLE_INDICATION */

static void _Context_Post( _In_ Strand* self_, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // not used yet (no secondary "semantic" messages)
}

static void _Context_PostControl( _In_ Strand* self, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // not used yet
}

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26001) // bogus "we know the interaction points to the middle of the InteractionDispBase struct"
#endif /* _PREFAST_ */

static void _Context_Ack( _In_ Strand* self_)
{
    Context* self = FromOffset(Context,strand,self_);
    ptrdiff_t tryingToPostLeftValue = ReadWithFence(&self->tryingToPostLeft);

    trace_ContextAck(
        self_,
        self->strand.info.interaction.other,
        &self->strand.info.interaction,
        self->strand.info.thisClosedOther,
        self->strand.info.otherClosedThis,
        tryingToPostLeftValue );

    // al management done by strand implementation except broadcasting cond var

    // wake up Context_PostMessageLeft if appropiate
    // (no point on waking up Context_PostMessageLeft if CONTEXT_STRANDAUX_TRYPOSTLEFT is scheduled to run after us)
    if( CONTEXT_POSTLEFT_POSTING == Atomic_CompareAndSwap( &self->tryingToPostLeft, (ptrdiff_t)CONTEXT_POSTLEFT_POSTING, (ptrdiff_t)(CONTEXT_POSTLEFT_POSTING|CONTEXT_POSTLEFT_SCHEDULED)) )
    {
        // Schedule it again
        Strand_ScheduleAux( &self->strand, CONTEXT_STRANDAUX_TRYPOSTLEFT );
        // again we get a memory barrier on tryingToPostLeft/tryingToPostLeftScheduled after this
    }
}

static void _Context_Cancel( _In_ Strand* self )
{
    trace_ContextCancel( self );
}

static void _Context_Close( _In_ Strand* self_ )
{
    Context* self = FromOffset(Context,strand,self_);
    trace_ContextClose(
        self_,
        self->strand.info.interaction.other,
        &self->strand.info.interaction );
}

static void _Context_Finish( _In_ Strand* self_ )
{
    Context* self = FromOffset(Context,strand,self_);

    trace_ContextFinish( self_ );
    _Context_Destroy(self);
}

// CONTEXT_STRANDAUX_TRYPOSTLEFT
static void _Context_Aux_TryPostLeft( _In_ Strand* self_ )
{
    Context* self = FromOffset(Context,strand,self_);
    ptrdiff_t oldValue;

    trace_ContextAuxPostLeft( self_, self->strand.info.thisAckPending );

    if( !self->strand.info.thisAckPending )
    {
        if (!self->strand.info.thisClosedOther)  // TODO: Is this correct, or is it indiciative of a different problem?
        {
            /* Only post the message if this Context has not "closed"
             * the connection.  Another thread may have done so on the
             * context while this thread was waiting. */
            Strand_Post( &self->strand, self->msgPostingLeft );
        }
        self->msgPostingLeft = NULL;
        Strand_ScheduleAux(self_, CONTEXT_STRANDAUX_TRYPOSTLEFT_NOTIFY);
    }
    else
    {
        oldValue = Atomic_Swap(&self->tryingToPostLeft,(ptrdiff_t)CONTEXT_POSTLEFT_POSTING);
        if (oldValue != (CONTEXT_POSTLEFT_POSTING|CONTEXT_POSTLEFT_SCHEDULED))
        {
            DEBUG_ASSERT( (CONTEXT_POSTLEFT_POSTING|CONTEXT_POSTLEFT_SCHEDULED) == oldValue );
        }
    }
}

// CONTEXT_STRANDAUX_TRYPOSTLEFT_NOTIFY
static void _Context_Aux_TryPostLeft_Notify( _In_ Strand* self_ )
{
    Context* self = FromOffset(Context,strand,self_);
    ptrdiff_t oldValue;
    Selector* selector = NULL;
    if (self->provider && self->provider->lib && self->provider->lib->provmgr)
        selector = self->provider->lib->provmgr->selector;
    else if (self->provmgr)
        selector = self->provmgr->selector;

    oldValue = Atomic_Swap(&self->tryingToPostLeft,(ptrdiff_t)0);
    // wake up _Context_PostMessageLeft

// Uncomment when no longer using Selector
//#if defined(CONFIG_OS_WINDOWS)
//    trace_ContextAuxPostLeftNotify( self_ );
//    CondLock_Broadcast((ptrdiff_t)self);
//#else
    if( self->postingOnIoThread )
    {
        trace_ContextAuxPostLeftNotify_IoThread( self_ );
        self->postingOnIoThread = MI_FALSE;
        Selector_StopRunningNoReadsMode( selector );
    }
    else
    {
        trace_ContextAuxPostLeftNotify( self_ );
        CondLock_Broadcast((ptrdiff_t)self);
    }
//#endif

    if (oldValue  != (CONTEXT_POSTLEFT_POSTING|CONTEXT_POSTLEFT_SCHEDULED))
    {
        DEBUG_ASSERT( (CONTEXT_POSTLEFT_POSTING|CONTEXT_POSTLEFT_SCHEDULED) == oldValue );
    }
}


#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */

/*
 * This represents a standard Context object.  It mediates access to the
 * internal strands from providers so that a provider can have only one
 * operation outstanding at a time.  Provider Posts (Result, Indication,
 * Error, CimError, and Instance) are routed through 'TryPostLeft' so that
 * they can be handled within a post lock and in the context of a strand
 * action.  Providers may post from multiple threads to the same Context,
 * but only one post will be handled at a time.  An ACK releases the
 * tryingToPostLeft flag to allow another Post to occur.
 *
 * Shutdown behavior:
 *     Cancel and Close do nothing.  The strand cannot be finished until it
 *     schedules a close on itself.  This will happen when the Context or
 *     ProvMgr determine that a connection to a provider should be closed.
 *     Typically this happens after a provider calls PostResult, PostError,
 *     or PostCimError.
 */
StrandFT _Context_leftInteractionFT =
{
    _Context_Post,
    _Context_PostControl,
    _Context_Ack,
    _Context_Cancel,
    _Context_Close,
    _Context_Finish,
    NULL,
    _Context_Aux_TryPostLeft,
    _Context_Aux_TryPostLeft_Notify,
    NULL,
    NULL,
    NULL
};


#ifndef DISABLE_INDICATION

/*
 * IndicationManager cancels the operations upon get cancelled call from protocol or
 * received unsubscribe message.
 *
 * This function works for both Lifecycle and regular subscription contexts
 */
static void _SubscribeContext_Cancel(_In_ Strand* self_)
{
    SubscriptionContext* self = (SubscriptionContext*)((char*)self_ - offsetof(Context,strand));
    trace_SubscribeContext_Cancel(self);

    if (NULL == self->subscription ||
        SubMgrSubscription_CancelStarted(self->subscription))
    {
        /* The subscription has already posted a final result, so there is
         * nothing to do here. */
        return;
    }
    SubscrContext_Unsubscribe(self);
    trace_SubscribeContext_CancelDone(self);
}


// CONTEXT_STRANDAUX_INVOKESUBSCRIBE
static void _Context_Aux_InvokeSubscribe( _In_ Strand* self_ )
{
    Context* self = FromOffset(Context,strand,self_);
    Message* msg = self->strand.info.stored.msg;

    DEBUG_ASSERT( NULL != msg );

    self->strand.info.stored.msg = NULL;

    Provider_InvokeSubscribe(
        self->provider,
        (SubscribeReq*)msg,
        (SubscriptionContext*)self);

    /*
     * release the reference count from _SubMgrSubscription_New
     */
    SubMgrSubscription_Release(((SubscriptionContext*)self)->subscription);

    Message_Release( msg );
}

/*
 * This represents a SubscriptionContext object.  It functions the same way as
 * a normal Context (follows the same behavioral pattern), but is designed to
 * handle indications.  It also includes an AUX subscribe method so that
 * subscription requests happen within the protections of a strand invocation.
 */
StrandFT _SubscribeContext_leftInteractionFT =
{
    _Context_Post,
    _Context_PostControl,
    _Context_Ack,
    _SubscribeContext_Cancel,
    _Context_Close,
    _Context_Finish,
    NULL,
    _Context_Aux_TryPostLeft,
    _Context_Aux_TryPostLeft_Notify,
    _Context_Aux_InvokeSubscribe,
    NULL,
    NULL
};

#endif /* ifndef DISABLE_INDICATION */

_Use_decl_annotations_
MI_Result _Context_Init(
    Context* self,
    ProvMgr* provmgr,
    Provider* provider,
    InteractionOpenParams* interactionParams,
    ContextInitOptions options,
    Context_Type ctxType )
{
    StrandFT *ft = NULL;

    if( NULL == self )
        return MI_RESULT_FAILED;

    memset(self, 0, sizeof(Context));

    trace_ContextNew( self, interactionParams ? interactionParams->interaction : NULL, &self->strand.info.interaction );

    Lock_Init(&self->lock);

    self->ctxType = ctxType;

    if( NULL != interactionParams && NULL != interactionParams->msg )
    {
        DEBUG_ASSERT( Message_IsRequest( interactionParams->msg ) );
        /* release inside _Context_Destroy */
        Message_AddRef( interactionParams->msg );
        self->request = (RequestMsg*)interactionParams->msg;
    }

#ifndef DISABLE_INDICATION
    /*
     * Conditionally set function table based on desired context type.
     */
    if (CTX_TYPE_IND_AGGREGATION == ctxType ||
        CTX_TYPE_IND_SUBSCRIPTION == ctxType)
    {
        self->base.ft = &__mi_indication_contextFT;
        ft = &_SubscribeContext_leftInteractionFT;
    }
    else if (CTX_TYPE_IND_LIFECYCLE == ctxType)
    {
        self->base.ft = &__mi_lifecycleIndication_contextFT;
        ft = &_SubscribeContext_leftInteractionFT;
    }
    else if (CTX_TYPE_IND_SUB_UNSUB == ctxType)
    {
        DEBUG_ASSERT( provider == NULL );
        DEBUG_ASSERT( interactionParams == NULL );
        DEBUG_ASSERT( ContextInit_NoInteraction == options );
        self->base.ft = &__mi_indication_subunsub_contextFT;
    }
    else
#endif /* ifndef DISABLE_INDICATION */
    {
        self->base.ft = &__mi_contextFT;
        ft = &_Context_leftInteractionFT;
    }

    self->magic = _MAGIC;
    self->provmgr = provmgr;
    self->provider = provider;

    if( ContextInit_DelayOpen == options )
    {
        DEBUG_ASSERT( NULL != interactionParams );
        Strand_Init( STRAND_DEBUG( Context ) &self->strand, ft, STRAND_FLAG_ENTERSTRAND|STRAND_FLAG_DELAYACCEPTOPEN, interactionParams );
    }
    else if ( ContextInit_NoInteraction != options )
    {
        Strand_Init( STRAND_DEBUG( Context ) &self->strand, ft, STRAND_FLAG_ENTERSTRAND, interactionParams );
        if( NULL != interactionParams )
        {
            DEBUG_ASSERT( NULL != interactionParams->msg );
            Strand_Ack( &self->strand );
        }
        if( ContextInit_DontLeaveStrand  != options  )
        {
            Strand_Leave( &self->strand );
        }
    }

    if (self->provider)
        Provider_Addref(self->provider);

    return MI_RESULT_OK;
}

void Context_CompleteOpen(
    _In_ Context* self,
    _In_ InteractionOpenParams* params,
         MI_Result result)
{
    DEBUG_ASSERT( NULL != params->msg );

    if( MI_RESULT_OK == result )
    {
        Strand_AcceptOpen( &self->strand, params );
        Strand_Ack( &self->strand );
        Strand_Leave( &self->strand );
    }
    else
    {
        // Just destroy the context
        _Context_Destroy(self);
        Strand_FailOpenWithResult(params, result, PostResultMsg_NewAndSerialize);
    }
}

//
// Initialize subscribe/unsubscribe context
//
MI_Result Subunsub_Context_Init(
    _Out_ Context* self,
    _In_ MI_Result* result,
    _In_ RequestMsg* msg)
{
    MI_Result r;
    DEBUG_ASSERT( msg && result );
    r = _Context_Init(self, NULL, NULL, NULL, ContextInit_NoInteraction, CTX_TYPE_IND_SUB_UNSUB);
    if ( r == MI_RESULT_OK )
    {
        Message_AddRef( &msg->base );
        self->request = msg;
        self->result = result;
    }
    return r;
}
