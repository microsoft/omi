/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _subscription_manager_h
#define _subscription_manager_h

#include "context.h"
#include "filter.h"
#include "SubscriptionContext.h"
#include "AggregationContext.h"
#include "LifecycleContext.h"
#include <common.h>
#include <base/list.h>
#include <indication/common/indicommon.h>
#include <pal/sem.h>

BEGIN_EXTERNC

/*
**==============================================================================
**
** Describes the various states of a SubscriptionContext
**
**==============================================================================
*/
typedef enum _SubscriptionState
{
    SubscriptionState_NotInitialized    = 0,
    SubscriptionState_Initialized       = 1,
    SubscriptionState_Subscribed        = 2,
    SubscriptionState_Unsubscribing     = 3,
    SubscriptionState_Unsubscribed      = 4
} SubscriptionState;

/*
**==============================================================================
**
** Define SubMgrSubscription, one object represents one indication subscription 
**
**==============================================================================
*/
typedef struct _SubMgrSubscription
{
    /* This struct holds the same initial members as ListElem, so it conforms
     * to the ListElem interface (for use of the ListElem API. */
    struct _SubMgrSubscription* next;
    struct _SubMgrSubscription* prev;

    /* The original subscription request. */
    SubscribeReq* msg;// TODO: Needed?

    /* Ptrs to the two possible contexts in use by this subscription.
     * These are needed for clean up during Post* handling. */
    SubscriptionContext* subscribeCtx;

    /* Current state of the SubscriptionContext */
    SubscriptionState state;

    /* Saved from SubscribeReq msg for use during PostIndicationMsg */
    MI_Uint64 subscriptionID; // TODO: Not needed if keep SubscribeReq ptr here

    /* Keeps filtering function and state for indication evaluation. */
    InstanceFilter* filter;

    /* Ref count of the object */
    volatile ptrdiff_t refcount;

    /* final msg sent or not, 0 - not, 1 - sent */
    volatile ptrdiff_t finalmsgbit;

    /* unsubscribe started or not, 0 - not, 1 - started */
    volatile ptrdiff_t unsubscribebit;

    /* lock to ensure one message post a time to the subscription context */
    RecursiveLock postlock;

}SubMgrSubscription;

typedef SubMgrSubscription* SubMgrSubscriptionPtr;


/*
**==============================================================================
**
** Define SubMgrSubscription linked list
**
**==============================================================================
*/
typedef struct _SubscriptionList
{
    ListElem* head;
    ListElem* tail;
    ReadWriteLock lock; /* Readwrite lock to protect subscription list */
    size_t count; /* total number of subscription(s) */
    MI_Boolean allcancelled; /* all subscriptions cancelled or not */

    /*
     * aggregation context or lifecycle context take the snapshot of 
     * subscriptions' list to dispatch indication
     */
    _Field_size_(capacity) SubMgrSubscriptionPtr* subarray;
    /* the capacity of the subarray */
    size_t capacity;

} SubscriptionList;

/*
**==============================================================================
**
** Master struct for handling subscription state for a class/provider.  It 
** tracks the subscriptions is must aggregate and determines how to handle
** each AggregationContext and SubscriptionContext as it completes.
**
**==============================================================================
*/
typedef struct _SubscriptionManager
{
    /* Ptrs to the two possible contexts in use by this subscription manager.
     * These are needed for clean up during Post* handling. */
    AggregationContext* aggrCtx;

    /* Context used by providers to Post lifecycle indications.
     */
    LifecycleContext* lifecycleCtx;

    /* Prointer to provider
     */
    Provider* provider;

    /* Linked list of aggregated subscriptions */
    SubscriptionList subscrList;

    /*
     * lock to ensure EnableIndication/Subscribe/DisableIndication
     * call to provider threadsafe; also in case of termination of
     * current provider(class), make sure new subscribe request
     * wait until provider was disabled;
     */
    RecursiveLock enablelock;

    /*
     * 3 code path needs to take enablelock,
     * #1 - Subscribe request
     * #2 - post result on aggrCtx or lifecycleCtx
     * #3 - last subscription was cancelled
     *
     * #2 terminates current provider (class), which
     * set terminating to MI_TRUE, and cancel all active
     * subscriptions, in the meantime, if any #1 requests
     * would fail due to the current provider does not
     * complete the cancellation yet; upon the last
     * subscription being cancelled and removed, then
     * terminating flag is set to MI_FALSE
     *
     */
    MI_Boolean terminating;

    /* Indicates current class is enabled or not */
    MI_Boolean enabled;

    /*
     * The thread that invoke EnableIndication/Subscribe call to provider,
     * Post indication on the invoke thread will result in
     * MI_RESULT_NOT_SUPPORTED error code
     */
    ThreadID enableThreadID;
}
SubscriptionManager;

/*
**==============================================================================
**
** SubscriptionList Functions
**
**==============================================================================
*/
void SubscriptionList_Init(
    _Out_ SubscriptionList* self);

void SubscriptionList_Finalize(
    _In_ _Post_invalid_ SubscriptionList* self);

void SubscriptionList_AddSubscription(
    _Inout_ SubscriptionList* self,
    _In_ SubMgrSubscription* subscription);

MI_Result SubscriptionList_DeleteSubscription(
    _Inout_ SubscriptionList* self,
    _In_ SubMgrSubscription* subscription,
    _In_ SubscriptionManager* mgr );

MI_Result SubscriptionList_CancelAllSubscription(
    _Inout_ SubscriptionList* self );

MI_Result SubscriptionList_GetList(
    _In_ const SubscriptionList* self,
    _In_ MI_Boolean addref,
    _Outptr_result_buffer_(*count) SubMgrSubscriptionPtr** subs,
    _Out_ size_t* count);

void SubscriptionList_SetAllCancelled(
    _Inout_ SubscriptionList* self,
    _In_ MI_Boolean allcancelled);

void SubscriptionList_SetAllCancelledSafe(
    _Inout_ SubscriptionList* self,
    _In_ MI_Boolean allcancelled);

/*
**==============================================================================
**
** SubscriptionManager Functions
**
**==============================================================================
*/
SubscriptionManager* SubMgr_New();

void SubMgr_Delete(
    _In_ _Post_invalid_ SubscriptionManager* pMgr );

void SubMgr_Init(
    _Inout_ SubscriptionManager* mgr,
    _In_ Provider* provider );

void SubMgr_Finalize(
    _In_ _Post_invalid_ SubscriptionManager* mgr);

MI_Boolean SubMgr_IsEnabled(
    _In_ const SubscriptionManager* mgr );

void SubMgr_SetEnabled(
    _Inout_ SubscriptionManager* mgr,
    _In_ MI_Boolean enabled);

MI_Boolean SubMgr_IsTerminating(
    _In_ const SubscriptionManager* mgr );

void SubMgr_SetTerminating(
    _Inout_ SubscriptionManager* mgr,
    _In_ MI_Boolean terminating);

void SubMgr_SetAllCancelledSafe(
    _Inout_ SubscriptionManager* mgr,
    _In_ MI_Boolean allcancelled);

MI_Boolean SubMgr_IsSubListEmpty(
    _Inout_ SubscriptionManager* mgr );

MI_Result SubMgr_CreateSubscription(
    _Inout_ SubscriptionManager* mgr,
    _In_ Provider* provider,
    _In_ InteractionOpenParams* interactionParams,
    _Out_ SubscriptionContext** subscrContext );
    
MI_Result SubMgr_DeleteSubscription(
    _Inout_ SubscriptionManager* mgr,
    _In_ SubMgrSubscription* subscription );

MI_Result SubMgr_CancelAllSubscriptions(
    _Inout_ SubscriptionManager* mgr,
    _In_ MI_Result result, 
    _In_opt_ const ZChar* errorMessage,
    _In_opt_ const MI_Instance* cimError);

SubMgrSubscription* SubMgr_GetSubscription(
    _In_ const SubscriptionManager* mgr,
    _In_ MI_Uint64 subscriptionID );

/* search subscription based on subctx, add refcount to subscription if found */
SubMgrSubscription* SubMgr_GetSubscriptionByContext(
    _In_ const SubscriptionManager* mgr,
    _In_ SubscriptionContext* subCtx);

/* read subscription context list snapshot into an array */
MI_Result SubMgr_GetSubscriptionList(
    _In_ const SubscriptionManager* mgr,
    _Outptr_result_buffer_(*count) SubMgrSubscriptionPtr** subs,
    _Out_ size_t* count);

void SubMgr_SetEnableThread(
    _Inout_ SubscriptionManager* mgr);

MI_Boolean SubMgr_IsEnableThread(
    _In_ const SubscriptionManager* mgr);

MI_Boolean SubMgr_CanPostIndication(
    _In_ const SubscriptionManager* mgr);

/*
 * Three scenarios require the enablelock,
 * #1 - Subscribe request
 * #2 - post result on aggrCtx or lifecycleCtx
 * #3 - last subscription was cancelled
 *
 */
typedef enum AcquireEnableLockOperationType
{
    AcquireFromSubscribe = 0,
    AcquireFromDisable = 1,
    AcquireFromTerminate = 2
}
AcquireEnableLockOperationType;

MI_Boolean SubMgr_AcquireEnableLock(
    _In_ SubscriptionManager* self,
    _In_ AcquireEnableLockOperationType optype);

void SubMgr_ReleaseEnableLock(
    _In_ SubscriptionManager* self);

AggregationContext* SubMgr_CreateAggrContext(
    _In_ SubscriptionManager* self);

AggregationContext* SubMgr_RemoveAggrContext(
    _In_ SubscriptionManager* self);



/*
**==============================================================================
**
** SubMgrSubscription Functions
**
**==============================================================================
*/
SubMgrSubscription* _SubMgrSubscription_New(
    _In_ SubscribeReq* msg,
    CallSite cs);
#define SubMgrSubscription_New(msg) \
    _SubMgrSubscription_New((msg), CALLSITE)

void _SubMgrSubscription_Addref(
    _Inout_ SubMgrSubscription* subscription,
    CallSite cs);
#define SubMgrSubscription_Addref(subscription) \
    _SubMgrSubscription_Addref((subscription), CALLSITE)

void _SubMgrSubscription_Release(
    _Inout_ SubMgrSubscription* subscription,
    CallSite cs);
#define SubMgrSubscription_Release(subscription) \
    _SubMgrSubscription_Release((subscription), CALLSITE)

MI_Result SubMgrSubscription_SetState(
    _Inout_ SubMgrSubscription* subscription,
    _In_ SubscriptionState state );

SubscriptionTargetType SubMgrSubscription_GetSupportedTypes(
    _In_ SubMgrSubscription* subscription );

void SubMgrSubscription_AcuquirePostLock(
    _In_ SubMgrSubscription* self);

void SubMgrSubscription_ReleasePostLock(
    _In_ SubMgrSubscription* self);

MI_Boolean SubMgrSubscription_ShouldCallUnsubscribe(
    _In_ SubMgrSubscription* self);

MI_Boolean SubMgrSubscription_ShouldSendFinalMsg(
    _In_ SubMgrSubscription* self);

MI_Boolean SubMgrSubscription_CancelStarted(
    _In_ SubMgrSubscription* self);

MI_Boolean SubMgrSubscription_IsQueryValid(
    _In_ SubMgrSubscription* self,
    _In_ const MI_ClassDecl* cd );

/*
**==============================================================================
**
** MISC. Functions
**
**==============================================================================
*/
/* Get unsigned int represent of current thread ID */
unsigned int UintThreadID();

END_EXTERNC

#endif /* _subscription_manager_h */

