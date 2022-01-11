/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _provmgr_h
#define _provmgr_h

#include <common.h>
#include <pal/shlib.h>
#include <pal/lock.h>
#include <base/base.h>
#include <base/messages.h>
#include <base/interaction.h>
#include <sock/selector.h>
#include <provreg/provreg.h>
#include <omi_error/errorutil.h>

BEGIN_EXTERNC

#define PROVMGR_IDLE_TIMEOUT_USEC   (MI_ULL(90) * MI_ULL(1000000))

typedef struct _ProvMgr     ProvMgr;
struct _SubscriptionManager;
typedef struct _SubscriptionContext SubscriptionContext;

/*
    Callback to notify that prov-mgr unloaded all libraries
*/
typedef void (*ProvMgrCallbackOnIdle)(
    ProvMgr* mgr,
    void* callbackData);

struct _ProvMgr
{
    char providerDir[PAL_MAX_PATH_SIZE];

    /* Linked list of loaded providers */
    struct _Library* head;
    struct _Library* tail;
    /* make library list threadsafe */
    Lock liblock;

    /* timer notification */
    Handler     timeoutHandler;
    MI_Uint64   idleTimeoutUsec;

    /* idle notifications */
    ProvMgrCallbackOnIdle   idleCallback;
    void*                   idleCallbackData;

    /* selector (for timeouts support) */
    Selector* selector;

    /* Support for local session */
    MI_Application localApplication;
    MI_Session localSession;
    ptrdiff_t localSessionInitialized; /* 0 =  no, 1 = initializing, 2 = initialized */

    ThreadID ioThreadId;
};

MI_Result ProvMgr_Init(
    ProvMgr* self,
    Selector* selector,
    ProvMgrCallbackOnIdle idleCallback,
    void* idleCallbackData,
    const char* providerDir);

MI_Result ProvMgr_Destroy(
    ProvMgr* self);

MI_Result ProvMgr_NewRequest(
    _In_ ProvMgr* self,
    _In_ const ProvRegEntry* proventry,
    _Inout_ InteractionOpenParams* params );

typedef struct _ProvMgr_OpenCallbackData
{
    ProvMgr*        self;
    ProvRegEntry*   provRegEntry;
} ProvMgr_OpenCallbackData;

MI_INLINE
void ProvMgr_OpenCallback(
    _Inout_ InteractionOpenParams* params )
{
    MI_Result result;
    ProvMgr_OpenCallbackData* data =  (ProvMgr_OpenCallbackData*)params->callbackData;

    result = ProvMgr_NewRequest( data->self, data->provRegEntry, params );
    if( MI_RESULT_OK != result )
    {
        Strand_FailOpenWithResult(params, result, PostResultMsg_NewAndSerialize);
    }
}

/* MI_ServerFT is preceded directly by one of these. Providers may
 * internally case backwards to find this structure but they should verify
 * the magic number.
 */
typedef struct _ProvMgrFT
{
    MI_Uint32 magic;
    void* (*FindSymbol)(const char* name);
}
ProvMgrFT;

#define PROVMGRFT_MAGIC 0xF19768D7

/*
    Provider access
*/

typedef struct _Library Library;

typedef struct _Provider
{
    struct _Provider* next;
    struct _Provider* prev;

    MI_CONST MI_ClassDecl* classDecl;
    void* self;

    /* number of outstanding requests */
    volatile ptrdiff_t   refCounter;

    /* time when last outstanding request was handled */
    MI_Uint64   idleSince;

    /* indicator if Provider refused idle-unload */
    MI_Boolean  refusedUnload;

    /* pointer to lib object */
    Library* lib;

#ifndef DISABLE_INDICATION
    /* memory of subMgr was allocated along with Provider object */
    /* which will be released upon freeing Provider */
    struct _SubscriptionManager* subMgr;
#endif /* #ifndef DISABLE_INDICATION */

}Provider;

struct _Library
{
    struct _Library* next;
    struct _Library* prev;
    char libraryName[PAL_MAX_PATH_SIZE];
    Shlib* handle;
    const MI_Module* module;
    MI_Module_Self* self;
    struct _Provider* head;
    struct _Provider* tail;
    /* make provider list threadsafe */
    Lock provlock;
    ProvMgr* provmgr;
    int instanceLifetimeContext;
};

/*
    Adding reference to the provider:
    used by context functions
*/
void Provider_Addref(Provider* provider);

/*
 * Finalize provider before free memory
 */
void Provider_Finalize(_In_ _Post_invalid_ Provider* provider);

/*
    Decrementing provider's reference
    so prov mgr knows when provider becomes idle
*/
void Provider_Release(Provider* provider);

/*
    Sets 'refuse-unload' provider option
*/
void Provider_SetRefuseUnloadFlag(Provider* provider, MI_Boolean flag);


#ifndef DISABLE_INDICATION

/*
 * Disables indications on the specified provider.  Must be called once the
 * last subscription has been removed from the provider.
 */
MI_Result Provider_TerminateIndication(
    _In_ Provider* provider,
    _In_ MI_Result result,
    _In_opt_ const ZChar* errorMessage,
    _In_opt_ const MI_Instance* cimError );

/*
 * Invoke EnableIndication if not called yet;
 * and invoke Subscribe call to provider;
 *
 * To ensure enable/disable thread-safe, and since
 * OMI has single IO thread, this function has to be scheduled
 * on separate thread for OMI.
 * TODO: remove separate thread if have multi-IO threads implemented
 */
void Provider_InvokeSubscribe(
    _In_ Provider* provider,
    _In_ SubscribeReq* msg,
    _In_ SubscriptionContext* subscrContext);

MI_Result Provider_InvokeDisable(
    _Inout_ Provider* provider);

/*
 * Deletes the specified subscription.  This should only be called from a
 * SubscriptionContext's Post handler.  Calls DisableIndications if it is the
 * last subscription for a provider.
 */
MI_Result Provider_RemoveSubscription(
    _Inout_ Provider* provider,
    _In_ MI_Uint64 subscriptionID);

/*
 * For Internal use only
 *
 * Designed for use by Context handlers for invoking Unsubscribe requests on
 * the specified provider
 */
MI_Result Provider_ContextInvokeUnsubscribe(
    _Inout_ Provider* provider,
    _Inout_ SubscribeReq* originalMsg,
    _In_ MI_Uint64 subscriptionID);

#endif /* #ifndef DISABLE_INDICATION */


/* Implementation for MI_Context_GetLocalSession as the actual session is owned by the ProvMgr */
MI_Result ProvMgr_GetLocalSesson(
    _Inout_ ProvMgr* self,
    _Out_ MI_Session *localSession);

END_EXTERNC

#endif /* _provmgr_h */
