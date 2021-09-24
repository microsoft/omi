/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "SubMgr.h"
#include <indication/common/indilog.h>
#include <pal/intsafe.h>

unsigned int UintThreadID()
{
    ThreadID id = Thread_ID();
    return *((unsigned int*)(void*)&id);
}

/*
 *
 * SubscriptionManager Functions
 *
 */

SubscriptionManager* SubMgr_New()
{
    SubscriptionManager* subMgr = (SubscriptionManager*)PAL_Calloc(1, sizeof(SubscriptionManager));
    if (!subMgr)
        LOGD_ALLOC_OOM;
    return subMgr;
}

_Use_decl_annotations_
void SubMgr_Delete(SubscriptionManager* mgr )
{
    SubMgr_Finalize( mgr );
    PAL_Free(mgr);
}

/*
 * Perform generic initialization of a SubscriptionManager object.
 */
_Use_decl_annotations_
void SubMgr_Init(
    SubscriptionManager* mgr,
    Provider* provider )
{
    DEBUG_ASSERT (mgr);
    RecursiveLock_Init( &mgr->enablelock );
    mgr->terminating = MI_FALSE;
    mgr->enabled = MI_FALSE;
    mgr->provider = provider;
    SubscriptionList_Init( &mgr->subscrList );
}

_Use_decl_annotations_
void SubMgr_Finalize(
    SubscriptionManager* self)
{
    DEBUG_ASSERT( self );
    if (self->aggrCtx)
    {
        AggrContext_Delete(self->aggrCtx);
        self->aggrCtx = NULL;
    }
    if (self->lifecycleCtx)
    {
        LifeContext_Delete(self->lifecycleCtx);
        self->lifecycleCtx = NULL;
    }
    SubscriptionList_Finalize( &self->subscrList );
}

_Use_decl_annotations_
MI_Result SubMgr_CreateSubscription(
    SubscriptionManager* mgr,
    Provider* provider,
    InteractionOpenParams* interactionParams,
    SubscriptionContext** subscrContext )
{
    SubMgrSubscription* subscription = NULL;
    MI_Result result = MI_RESULT_OK;
    Context_Type ctxType;
    SubscribeReq* msg = (SubscribeReq*)interactionParams->msg;
    SubscriptionContext* subContext;

    DEBUG_ASSERT ( mgr && provider && interactionParams && interactionParams->msg && subscrContext );
    DEBUG_ASSERT( SubscribeReqTag == interactionParams->msg->tag );

    /*
     * Create the SubscriptionContext and prepare it for use in case the
     * provider attempts to PostIndication immediately after
     * EnableIndications without waiting for Subscribe.
     */
    subContext = (SubscriptionContext*)Batch_GetClear(msg->base.base.batch, sizeof(SubscriptionContext));
    if (!subContext)
    {
        trace_SubscrContextFailed();
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    /* This refCount is released in CONTEXT_STRANDAUX_INVOKESUBSCRIBE. */
    subscription = SubMgrSubscription_New(msg);
    if (!subscription)
    {
        trace_SubMgrSubscription_AllocFailed();
        return MI_RESULT_FAILED;
    }

    if (SubMgrSubscription_IsQueryValid(subscription, provider->classDecl) == MI_FALSE)
    {
        SubMgrSubscription_Release(subscription);
        return MI_RESULT_INVALID_QUERY;
    }

    *subscrContext = subContext;

    subscription->subscribeCtx = *subscrContext; // TODO: should this action be wrapped?

    ctxType = SubscriptionTargetType_IsLifecycle((SubscriptionTargetType)msg->targetType ) ? CTX_TYPE_IND_LIFECYCLE : CTX_TYPE_IND_SUBSCRIPTION; // TODO: Move to Context.h?
    result = SubscrContext_Init( *subscrContext, provider, ctxType, interactionParams, subscription);
    if ( MI_RESULT_OK != result)
    {
        trace_SubscriptionContext_InitFailed();
        subscription->subscribeCtx = NULL;
        SubMgrSubscription_Release(subscription);
        return result;
    }
    SubMgrSubscription_SetState( subscription, SubscriptionState_Initialized );

    return MI_RESULT_OK;
}

_Use_decl_annotations_
MI_Result SubMgr_DeleteSubscription(
    SubscriptionManager* mgr,
    SubMgrSubscription* subscription )
{
    MI_Result r;
    DEBUG_ASSERT ( mgr && subscription );

    trace_SubMgr_DeleteSubscription_Start(UintThreadID(), mgr, subscription, (MI_Uint32)mgr->subscrList.count, mgr->subscrList.head, mgr->subscrList.tail);

    r = SubscriptionList_DeleteSubscription( &mgr->subscrList, subscription, mgr );

    return r;
}

_Use_decl_annotations_
MI_Result SubMgr_CancelAllSubscriptions(
    SubscriptionManager* mgr,
    MI_Result result,
    const ZChar* errorMessage,
    const MI_Instance* cimError )
{
    DEBUG_ASSERT (mgr);
    trace_SubMgr_CancelAllSubscriptions( UintThreadID(), mgr);

    return SubscriptionList_CancelAllSubscription( &mgr->subscrList );
}

static SubMgrSubscription* _SubscriptionList_GetSubscription(
    _In_ const SubscriptionList* self,
    _In_ MI_Uint64 subscriptionID)
{
    SubMgrSubscription* subscription;
    SubscriptionList* list = (SubscriptionList*)self;
    ReadWriteLock_AcquireRead(&list->lock);
    for (subscription = (SubMgrSubscription*)self->head; subscription; subscription = subscription->next)
    {
        if (subscription->subscriptionID == subscriptionID)
        {
            break;
        }
    }
    ReadWriteLock_ReleaseRead(&list->lock);

    return subscription;
}

static SubMgrSubscription* _SubscriptionList_GetSubscriptionByContext(
    _In_ const SubscriptionList* self,
    _In_ SubscriptionContext* subCtx )
{
    SubMgrSubscription* subscription;
    SubscriptionList* list = (SubscriptionList*)self;

    /* thread safely get subscriptions and add ref count */
    ReadWriteLock_AcquireRead( &list->lock );
    subscription = (SubMgrSubscription*) self->head;
    while( subscription && (subscription->subscribeCtx != subCtx) )
    {
        subscription = subscription->next;
    }
    if (subscription)
        SubMgrSubscription_Addref(subscription);
    ReadWriteLock_ReleaseRead( &list->lock );

    return subscription;
}

/*
 * Examines the SubscriptionManager to determine if it has any matching
 * subscriptions.
 */
_Use_decl_annotations_
SubMgrSubscription* SubMgr_GetSubscription(
    const SubscriptionManager* mgr,
    MI_Uint64 subscriptionID )
{
    DEBUG_ASSERT( mgr );
    return _SubscriptionList_GetSubscription( &mgr->subscrList, subscriptionID);
}

/* search subscription based on subctx, add refcount to subscription if found */
_Use_decl_annotations_
SubMgrSubscription* SubMgr_GetSubscriptionByContext(
    const SubscriptionManager* mgr,
    SubscriptionContext* subCtx)
{
    SubMgrSubscription* subscription;

    DEBUG_ASSERT( mgr && subCtx );

    subscription = _SubscriptionList_GetSubscriptionByContext( &mgr->subscrList, subCtx );

    if ( NULL == subscription )
        trace_SubMgr_GetSubscriptionByContext_NotFound(UintThreadID(), (void*)mgr, subCtx);

    return subscription;
}

/* read subscription list snapshot into an array, no refcount added to subscription(s) */
_Use_decl_annotations_
MI_Result SubMgr_GetSubscriptionList(
    const SubscriptionManager* mgr,
    SubMgrSubscriptionPtr** subs,
    size_t* count)
{
    return SubscriptionList_GetList( & mgr->subscrList, MI_TRUE, subs, count );
}


/*
 * Perform generic initialization of an SubscriptionManager object.
 */
_Use_decl_annotations_
SubMgrSubscription* _SubMgrSubscription_New(
    SubscribeReq* msg,
    CallSite cs)
{
    SubMgrSubscription* subscription = (SubMgrSubscription*)PAL_Calloc(1, sizeof(SubMgrSubscription));
    const char* file = "";
    size_t line = 0;

#if defined(CONFIG_ENABLE_DEBUG)
    file = cs.file;
    line = cs.line;
#endif /* defined(CONFIG_ENABLE_DEBUG) */

    if (!subscription)
    {
        LOGD_ALLOC_OOM;
        return NULL;
    }

    /*
     * Set refcount to 1, which will be released in context.c:CONTEXT_STRANDAUX_INVOKESUBSCRIBE.
     */
    subscription->refcount = 1;
    subscription->finalmsgbit = 0;
    subscription->unsubscribebit = 0;

    SubMgrSubscription_SetState( subscription, SubscriptionState_Initialized );

    subscription->msg = msg;
    subscription->subscriptionID = msg->subscriptionID;

    subscription->filter = InstanceFilter_New( &(msg->base.base) );
    if (!subscription->filter)
    {
        trace_InstanceFilter_AllocFailed();
        SubMgrSubscription_Release( subscription );
        return NULL;
    }

    RecursiveLock_Init(&subscription->postlock);

    trace_SubMgrSubscription_New(file, (MI_Uint32)line, (void*)subscription, tcs(msg->className), (unsigned int)subscription->refcount);

    /* filter must be initialized separately based on the request message. */
    return subscription;
}

_Use_decl_annotations_
void _SubMgrSubscription_Addref(
    SubMgrSubscription* subscription,
    CallSite cs)
{
    ptrdiff_t count = Atomic_Inc(&subscription->refcount);
    const char* file = "";
    size_t line = 0;

#if defined(CONFIG_ENABLE_DEBUG)
    file = cs.file;
    line = cs.line;
#endif /* defined(CONFIG_ENABLE_DEBUG) */

    trace_SubMgrSubscription_Addref(file, (MI_Uint32)line, (void*)subscription, (unsigned int)count);
}


_Use_decl_annotations_
void _SubMgrSubscription_Release(
    SubMgrSubscription* subscription,
    CallSite cs)
{
    void *sub = subscription;
    const char* file = "";
    size_t line = 0;

#if defined(CONFIG_ENABLE_DEBUG)
    file = cs.file;
    line = cs.line;
#endif /* defined(CONFIG_ENABLE_DEBUG) */

    if (subscription)
    {
        /* Finalize the subscription if ref count decreased to 0 */
        ptrdiff_t count = Atomic_Dec(&subscription->refcount);
        if (count == 0)
        {
            trace_SubMgrSubscription_Release_Finalized( UintThreadID(), subscription );

            if (subscription->filter)
            {
                InstanceFilter_Destroy( subscription->filter );
            }

            if (subscription->subscribeCtx)
            {
                SubscrContext_Close(subscription->subscribeCtx);
                subscription->subscribeCtx = NULL;
            }
            PAL_Free(subscription);
        }
        trace_SubMgrSubscription_Release(file, (MI_Uint32)line, sub, (unsigned int)count);
    }

    /* Done to satisfy OACR since it doesn't detect a change to subscription when
     * it is free'd. This just modified the local variable subscription, not the
     * actual ptr in the caller. */
    subscription = NULL;
}

_Use_decl_annotations_
MI_Result SubMgrSubscription_SetState(
    SubMgrSubscription* subscription,
    SubscriptionState state )
{
    subscription->state = state;
    return MI_RESULT_OK;
}

_Use_decl_annotations_
SubscriptionTargetType SubMgrSubscription_GetSupportedTypes(
    SubMgrSubscription* subscription )
{
    if (subscription &&
        subscription->msg)
    {
        return (SubscriptionTargetType)subscription->msg->targetType;
    }
    else
    {
        return SUBSCRIP_TARGET_UNSUPPORTED;
    }
}

_Use_decl_annotations_
void SubMgrSubscription_AcquirePostLock(SubMgrSubscription* self)
{
    RecursiveLock_Acquire(&self->postlock);

    trace_SubMgrSubscription_AcquirePostLock(UintThreadID(), (void*)self, self->subscribeCtx);
}

_Use_decl_annotations_
void SubMgrSubscription_ReleasePostLock(SubMgrSubscription* self)
{
    trace_SubMgrSubscription_ReleasePostLock(UintThreadID(), (void*)self, self->subscribeCtx);

    RecursiveLock_Release(&self->postlock);
}

_Use_decl_annotations_
MI_Boolean SubMgrSubscription_ShouldCallUnsubscribe(
    SubMgrSubscription* self)
{
    MI_Boolean shouldunsubscribe = MI_FALSE;

    if ( Atomic_CompareAndSwap(&self->unsubscribebit, 0, 1) == 0 )
        shouldunsubscribe = MI_TRUE;
    else
        trace_SubMgrSubscription_ShouldCallUnsubscribe_AlreadyUnsubscribed( UintThreadID(), self );

    trace_SubMgrSubscription_ShouldCallUnsubscribe(UintThreadID(), self, shouldunsubscribe);

    return shouldunsubscribe;
}

_Use_decl_annotations_
MI_Boolean SubMgrSubscription_ShouldSendFinalMsg(
    SubMgrSubscription* self)
{
    MI_Boolean shouldsendfinalmsg = MI_FALSE;
    if ( Atomic_CompareAndSwap(&self->finalmsgbit, 0, 1) == 0 )
        shouldsendfinalmsg = MI_TRUE;
    else
        trace_SubMgrSubscription_ShouldSendFinalMsg_AlreadySent( UintThreadID(), self );

    trace_SubMgrSubscription_ShouldSendFinalMsg(UintThreadID(), self, shouldsendfinalmsg);

    return shouldsendfinalmsg;
}

_Use_decl_annotations_
MI_Boolean SubMgrSubscription_CancelStarted(
    SubMgrSubscription* self)
{
    MI_Boolean cancelstarted = MI_FALSE;
    if ( ReadWithFence(&self->unsubscribebit) == 1 )
        cancelstarted = MI_TRUE;
    else if ( ReadWithFence(&self->finalmsgbit) == 1 )
        cancelstarted = MI_TRUE;
    return cancelstarted;
}

/* Validate the filter using the provided class decl. */
_Use_decl_annotations_
MI_Boolean SubMgrSubscription_IsQueryValid(
    SubMgrSubscription* self,
    const MI_ClassDecl* cd )
{
    WQL* wql = InstanceFilter_GetWQL(self->filter);
    if (wql)
    {
        if (WQL_Validate(wql, cd) == 0)
        {
            return MI_TRUE;
        }
        trace_QueryValidationFailed(tcs(wql->text));
    }
    return MI_FALSE;
}

/*
 * There are 3 places needs to take enablelock
 * 1- Subscribe request
 * 2- post result on aggregation context
 * 3- last subscription was removed
 *
 * For 2 & 3, enablebit to make sure only take the lock once
 *
 * parameters:
 *  terminate -- MI_TRUE means being called by Provider_TerminateIndication
 *
 * return value:
 *  MI_TRUE -- acquired the lock, otherwise no lock acquired
 *
 */
const TChar* _OpNames[] = {
    PAL_T("SubscribeProvider"),
    PAL_T("DisableProvider"),
    PAL_T("Terminate")
};

_Use_decl_annotations_
MI_Boolean SubMgr_AcquireEnableLock(
    SubscriptionManager* self,
    AcquireEnableLockOperationType optype)
{
    trace_SubscriptionManager_AcquireEnableLock_Start(UintThreadID(), (void*)self, _OpNames[(int)optype]);

    RecursiveLock_Acquire( &self->enablelock );

    switch( optype )
    {
    case AcquireFromSubscribe:
        if ( MI_TRUE == SubMgr_IsTerminating( self ) )
        {
            trace_SubscriptionManager_AcquireEnableLock_AlreadyTerminated( UintThreadID(), self );
            RecursiveLock_Release( &self->enablelock );
            return MI_FALSE;
        }
        break;
    case AcquireFromDisable:
        if ( MI_FALSE == SubMgr_IsSubListEmpty( self ) )
        {
            if ( MI_FALSE == SubMgr_IsTerminating( self ) )
            {
                trace_SubscriptionManager_AcquireEnableLock_IgnoreDisableCall( UintThreadID(), self );
                RecursiveLock_Release( &self->enablelock );
                return MI_FALSE;
            }
            else
                DEBUG_ASSERT (0);
        }
        break;
    case AcquireFromTerminate:
        if ( MI_FALSE == SubMgr_IsTerminating( self ) )
        {
            SubMgr_SetTerminating( self, MI_TRUE );
            if ( MI_FALSE == SubMgr_IsSubListEmpty( self ) )
            {
                trace_SubscriptionManager_AcquireEnableLock_CancelAll( UintThreadID(), self );
                SubMgr_CancelAllSubscriptions( self, MI_RESULT_FAILED, NULL, NULL );
            }
            /* no subscription added yet, can happen during first subscribe */
            else
            {
                Provider_InvokeDisable( self->provider );
            }
        }
        if ( MI_TRUE == SubMgr_IsEnabled(self) )
            SubMgr_SetEnabled( self, MI_FALSE );
        break;
    }

    trace_SubscriptionManager_AcquireEnableLock_Complete(UintThreadID(), (void*)self, _OpNames[(int)optype]);

    return MI_TRUE;
}

_Use_decl_annotations_
void SubMgr_ReleaseEnableLock(
    SubscriptionManager* self)
{
    trace_SubscriptionManager_ReleaseEnableLock(UintThreadID(), (void*)self);
    RecursiveLock_Release(&self->enablelock);
}

_Use_decl_annotations_
AggregationContext* SubMgr_CreateAggrContext(
    SubscriptionManager* self)
{
    MI_Result result;
    Provider* provider = self->provider;
    AggregationContext* aggrContext = AggrContext_New();
    DEBUG_ASSERT( !self->aggrCtx );

    if (!aggrContext)
    {
        trace_OutOfMemory();
        return NULL;
    }

    result = AggrContext_Init(aggrContext, provider, self);
    if (MI_RESULT_OK != result)
    {
        trace_AggregationContext_InitFailed();
        AggrContext_Delete(aggrContext);
        return NULL;
    }

    self->aggrCtx = aggrContext;
    return aggrContext;
}

_Use_decl_annotations_
AggregationContext* SubMgr_RemoveAggrContext(
    SubscriptionManager* self)
{
    AggregationContext* aggrctx = self->aggrCtx;
    if ( aggrctx )
        self->aggrCtx = NULL;
    return aggrctx;
}

_Use_decl_annotations_
MI_Boolean SubMgr_IsSubListEmpty(
    SubscriptionManager* mgr )
{
    return (mgr->subscrList.count == 0);
}

_Use_decl_annotations_
MI_Boolean SubMgr_IsEnabled(
    const SubscriptionManager* mgr )
{
    return mgr->enabled;
}

_Use_decl_annotations_
void SubMgr_SetEnabled(
    SubscriptionManager* mgr,
    MI_Boolean enabled)
{
    mgr->enabled = enabled;
}

_Use_decl_annotations_
MI_Boolean SubMgr_IsTerminating(
    const SubscriptionManager* mgr )
{
    return mgr->terminating;
}

_Use_decl_annotations_
void SubMgr_SetTerminating(
    SubscriptionManager* mgr,
    MI_Boolean terminating)
{
    mgr->terminating = terminating;
}

_Use_decl_annotations_
void SubMgr_SetAllCancelledSafe(
    SubscriptionManager* mgr,
    MI_Boolean allcancelled)
{
    DEBUG_ASSERT ( mgr );
    SubscriptionList_SetAllCancelledSafe( &mgr->subscrList, allcancelled );
}

_Use_decl_annotations_
void SubMgr_SetEnableThread(
    SubscriptionManager* mgr)
{
    mgr->enableThreadID = Thread_ID();
}

_Use_decl_annotations_
MI_Boolean SubMgr_IsEnableThread(
    const SubscriptionManager* mgr)
{
    ThreadID threadId = Thread_ID();
    return Thread_Equal( &threadId, (ThreadID*)&mgr->enableThreadID ) ? MI_TRUE : MI_FALSE;
}

_Use_decl_annotations_
MI_Boolean SubMgr_CanPostIndication(
    const SubscriptionManager* mgr)
{
    MI_Boolean isEnableThread = SubMgr_IsEnableThread(mgr);
    MI_Boolean canPostIndication = isEnableThread ? MI_FALSE : MI_TRUE;
    if ( MI_FALSE == canPostIndication )
        trace_SubMgr_CanPostIndication_Fail( UintThreadID() );
    return canPostIndication;
}

static MI_Result _SubscriptionList_EnsureArray(
    _In_ SubscriptionList* self)
{
    size_t capacity = self->capacity;
    SubMgrSubscriptionPtr* subarray = NULL;
    if ( self->count <= capacity )
        return MI_RESULT_OK;

    if ( capacity == 0 )
        capacity = 32;
    else
        capacity *= 2;

    if ( capacity < self->count )
    {
        /* integer overflow */
        trace_SubscriptionList_EnsureArray_Overflow( UintThreadID() );
        return MI_RESULT_FAILED;
    }

    if ( self->subarray )
    {
        PAL_Free(self->subarray);
        self->subarray = NULL;
        self->capacity = 0;
    }

    size_t allocSize = 0;
    if (SizeTMult(sizeof (SubMgrSubscriptionPtr), capacity, &allocSize) == S_OK)
    {
        subarray = (SubMgrSubscriptionPtr*)PAL_Malloc( allocSize );
    }

    if (subarray == NULL)
    {
        trace_OutOfMemory();
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    self->subarray = subarray;
    self->capacity = capacity;
    return MI_RESULT_OK;
}

_Use_decl_annotations_
void SubscriptionList_Init(
    SubscriptionList* self)
{
    memset( self, 0, sizeof( SubscriptionList ) );
    ReadWriteLock_Init( &self->lock );
}

_Use_decl_annotations_
void SubscriptionList_Finalize(
    SubscriptionList* self)
{
    if ( self->subarray )
    {
        PAL_Free(self->subarray);
        self->subarray = NULL;
        self->capacity = 0;
    }
}

_Use_decl_annotations_
void SubscriptionList_AddSubscription(
    SubscriptionList* self,
    SubMgrSubscription* subscription)
{
    DEBUG_ASSERT ( self );
    /* thread safely add subscription to list */
    ReadWriteLock_AcquireWrite(&self->lock);
    DEBUG_ASSERT ( MI_FALSE == self->allcancelled );
    List_Append( &self->head, &self->tail, (ListElem*)subscription );
    SubMgrSubscription_Addref(subscription);
    self->count++;
    ReadWriteLock_ReleaseWrite(&self->lock);
}

_Use_decl_annotations_
MI_Result SubscriptionList_DeleteSubscription(
    SubscriptionList* self,
    SubMgrSubscription* subscription,
    SubscriptionManager* mgr )
{
    SubMgrSubscription* sub;
    /* thread safely remove the subscription from list */
    ReadWriteLock_AcquireWrite( &self->lock );
    sub = (SubMgrSubscription*) self->head;
    /* find the subscription first */
    while( sub )
    {
        if ( sub == subscription )
            break;
        sub = sub->next;
    }

    /* Remove from the list if found */
    if ( sub )
    {
        List_Remove( &self->head, &self->tail, (ListElem*)sub );
        self->count--;

        /* Done after remove so that it can operate on the updated list */
        if (mgr->lifecycleCtx)
        {
            LifeContext_UpdateSupportedTypes(mgr->lifecycleCtx);
        }
    }

    ReadWriteLock_ReleaseWrite( &self->lock );

    if (sub)
    {
        SubMgrSubscription_Release(sub);
        return MI_RESULT_OK;
    }
    return MI_RESULT_NOT_FOUND;
}

_Use_decl_annotations_
MI_Result SubscriptionList_CancelAllSubscription(
    SubscriptionList* self )
{
    SubMgrSubscriptionPtr* sublist;
    size_t i, count;
    MI_Result r;

    DEBUG_ASSERT ( MI_FALSE == self->allcancelled );

    r = SubscriptionList_GetList( self, MI_TRUE, &sublist, &count );
    if ( r != MI_RESULT_OK )
        return r;

    SubscriptionList_SetAllCancelledSafe( self, MI_TRUE );

    for ( i = 0; i < count; i++ )
    {
        /*TODO: what if a subscription was being cancelled. confirm */
        Strand_ScheduleCancel( &sublist[i]->subscribeCtx->baseCtx.strand );
        SubMgrSubscription_Release( sublist[i] );
    }

    return MI_RESULT_OK;
}

_Use_decl_annotations_
MI_Result SubscriptionList_GetList(
    const SubscriptionList* self,
    MI_Boolean addref,
    SubMgrSubscriptionPtr** subs,
    size_t* count)
{
    MI_Result r;
    SubscriptionList* list = (SubscriptionList*)self;

    *subs = NULL;
    *count = 0;

    //
    // thread safely read subscriptions
    //
    ReadWriteLock_AcquireRead( &list->lock );

    r = _SubscriptionList_EnsureArray( list );

    if ( r == MI_RESULT_OK )
    {
        size_t i = 0;
        SubMgrSubscription* subscription = (SubMgrSubscription*) list->head;
        while(subscription)
        {
            if ( MI_TRUE == addref )
                SubMgrSubscription_Addref( subscription );
            list->subarray[i++] = subscription;
            subscription = subscription->next;
        }
        DEBUG_ASSERT( i == list->count );
        *count = list->count;
        *subs = list->subarray;
    }

    ReadWriteLock_ReleaseRead( &list->lock );

    return r;
}

_Use_decl_annotations_
void SubscriptionList_SetAllCancelled(
    SubscriptionList* self,
    MI_Boolean allcancelled)
{
    self->allcancelled = allcancelled;
}

void SubscriptionList_SetAllCancelledSafe(
    _Inout_ SubscriptionList* self,
    _In_ MI_Boolean allcancelled)
{
    ReadWriteLock_AcquireWrite( &self->lock );
    SubscriptionList_SetAllCancelled(self, allcancelled);
    ReadWriteLock_ReleaseWrite( &self->lock );
}

