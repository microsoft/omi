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

#ifndef _context_h
#define _context_h

#include <common.h>
#include <base/base.h>
#include <base/Strand.h>
#include <pal/thread.h>
#include "provmgr.h"
#include <pal/lock.h>

BEGIN_EXTERNC

#define CONTEXT_STRANDAUX_TRYPOSTLEFT           0
#define CONTEXT_STRANDAUX_TRYPOSTLEFT_NOTIFY    1
#define CONTEXT_STRANDAUX_INVOKESUBSCRIBE       2

typedef enum _Context_Type
{
    CTX_TYPE_SINGLE_ITEM = 0,       /* regular execution, post results to the caller */
    CTX_TYPE_IND_AGGREGATION,       /* indication context (AggregationContext) */
    CTX_TYPE_IND_SUBSCRIPTION,      /* indication context (SubscriptionContext) */
    CTX_TYPE_IND_LIFECYCLE,         /* indication context (LifecycleContext) */
    CTX_TYPE_IND_SUB_UNSUB,         /* indication context for invoking Subscribe and Unsubscribe */
    CTX_TYPE_INVOKE_WITH_INSTANCE   /* calling get before invoke - call invoke with result instance */
}
Context_Type;

// for Context.tryingToPostLeft
#define CONTEXT_POSTLEFT_POSTING    1   // If Context_PostMessageLeft is trying to post to the left
#define CONTEXT_POSTLEFT_SCHEDULED  2   // If CONTEXT_STRANDAUX_POSTLEFT is currently scheduled

typedef struct _Context
{
    MI_Context base;
    MI_Uint32 magic;

    Strand              strand;                     // manages interaction with the component to the left (dispatcher, agent, etc.)
    Lock                lock;
    Message *           msgPostingLeft;
    volatile ptrdiff_t  tryingToPostLeft;           // CONTEXT_POSTLEFT_* flags

    /* Pointer to the request message (containing the callback) */
    RequestMsg*         request;
    Message*            loadRequest;

    /* chain processing */
    Context_Type        ctxType;

    /* delayed invoke parameters */
    MI_MethodDecl*      md;
    MI_Instance*        inst;
    MI_Instance*        instParams;
    void *              prov_self;

    /* Cancelled flag */
    MI_Boolean          cancelled;

    ProvMgr*            provmgr;

    /* Reference to Provider */
    Provider*           provider;

    /* Result to caller */
    MI_Result*          result;

    /* If non-null, PostInstance() only forwards 1st matching instance. */
    MI_Instance*        instanceName;

    /* Whether instanceName has been matched yet. */
    MI_Boolean          matchedInstanceName;

// Uncomment when no longer using Selector
// #if !defined(CONFIG_OS_WINDOWS)
    /* If Context_PostMessageLeft is trying to post from the IO thread */
    MI_Boolean          postingOnIoThread;
// #endif

    /* Information needed if provider does not post a response instance as part of a modify command*/
    MI_Instance *       keyInstance;
    MI_Boolean          postedModifyGetInstance;
    MI_Boolean          postedModifyEnumInstance;
    MI_Boolean          postedModifyInstance;
}
Context;

typedef enum _ContextInitOptions
{
    ContextInit_CompleteOpen    = 0,
    ContextInit_DelayOpen       = 1,
    ContextInit_DontLeaveStrand = 2,
    ContextInit_NoInteraction   = 3
}
ContextInitOptions;


MI_Result _Context_Init(
    _Out_ Context* self,
    _In_ ProvMgr* provmgr,
    _In_opt_ Provider* provider,
    _Inout_opt_ InteractionOpenParams* interactionParams,
    ContextInitOptions options,
    Context_Type ctxType );

void _Context_Destroy(
    _Inout_ Context* self);

MI_INLINE
MI_Result Context_Init(
    _Out_ Context* self,
    _In_ ProvMgr* provmgr,
    _In_opt_ Provider* provider,
    _Inout_opt_ InteractionOpenParams* interactionParams)
{
    ContextInitOptions option = (NULL == interactionParams) ? ContextInit_NoInteraction : ContextInit_CompleteOpen;
    return _Context_Init( self, provmgr, provider, interactionParams, option, CTX_TYPE_SINGLE_ITEM );
}

MI_INLINE
MI_Result Context_Init_ByType(
    _Out_ Context* self,
    _In_ Provider* provider,
    _Inout_ InteractionOpenParams* interactionParams,
    _In_ Context_Type ctxType )
{
    ProvMgr *provmgr = NULL;
    if (provider && provider->lib)
    {
        provmgr = provider->lib->provmgr;
    }
    return _Context_Init( self, provmgr, provider, interactionParams, ContextInit_DontLeaveStrand, ctxType );
}

MI_INLINE
MI_Result Context_PartialInit(
    _Out_ Context* self,
    _In_ Provider* provider,
    _Inout_ InteractionOpenParams* interactionParams)
{
    ProvMgr *provmgr = NULL;
    if (provider && provider->lib)
    {
        provmgr = provider->lib->provmgr;
    }
    return _Context_Init( self, provmgr, provider, interactionParams, ContextInit_DelayOpen, CTX_TYPE_SINGLE_ITEM );
}

void Context_CompleteOpen(
    _In_ Context* self,
    _In_ InteractionOpenParams* params,
         MI_Result result);

void Context_Close(
    _In_ _Post_invalid_ Context* self );

// this is to be used by provmgr to post schema; not exposed to the provider
void Context_PostSchema(
    _In_ Context* self,
    _In_ Message* msg);

// Post a message to the component to the left
void Context_PostMessageLeft(
    _In_ Context* self,
    _In_ Message* msg);

extern MI_ContextFT __mi_contextFT;

//
// Initialize subscribe/unsubscribe context
//
MI_Result Subunsub_Context_Init(
    _Out_ Context* self,
    _In_ MI_Result* result,
    _In_ RequestMsg* msg);

END_EXTERNC

#endif /* _context_h */
