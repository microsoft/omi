/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <pal/sleep.h>
#include <pal/atomic.h>
#include <ut/ut.h>
#include <provmgr/SubscriptionContext.h>
#include <provmgr/SubMgr.h>
#include <provmgr/provmgr.h>
#include <provmgr/nioproc.h>
#include <indication/common/indicommon.h>
#include <provmgr/indicationSchema.h>
#include "StrandHelper.h"

using namespace std;

SubscriptionContext context;
SubscriptionContext* testContext;
SubMgrSubscription* subscription = NULL;
Provider provider;
Library g_library;
ProvMgr g_provMgr;
SubscribeReq* request = NULL;
MI_Boolean unsubscribeCalled = MI_FALSE;
Strand leftSideStrand;
MI_ClassDecl modifiedRtti;

/*
 *
 * MI_ProviderFT functions and table
 *
 */

/*
void _SubscrContextTest_EnableIndications(
    _In_opt_ void* self,
    _In_ MI_Context* indicationsContext,
    _In_z_ const MI_Char* nameSpace,
    _In_z_ const MI_Char* className)
{

}
*/
void _SubscrContextTest_DisableIndications(
    _In_opt_ void* self,
    _In_ MI_Context* indicationsContext,
    _In_z_ const MI_Char* nameSpace,
    _In_z_ const MI_Char* className)
{
    MI_UNUSED(self);
    MI_UNUSED(indicationsContext);
    MI_UNUSED(nameSpace);
    MI_UNUSED(className);
}
/*
void _SubscrContextTest_Subscribe(
    _In_opt_ void* self,
    _In_ MI_Context* context,
    _In_z_ const MI_Char* nameSpace,
    _In_z_ const MI_Char* className,
    _In_opt_ const MI_Filter* filter,
    _In_opt_z_ const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    _Outptr_result_maybenull_ void** subscriptionSelf)
{

}
*/
void _SubscrContextTest_Unsubscribe(
    _In_opt_ void* self,
    _In_ MI_Context* context,
    _In_z_ const MI_Char* nameSpace,
    _In_z_ const MI_Char* className,
    MI_Uint64  subscriptionID,
    _In_opt_ void* subscriptionSelf)
{
    MI_UNUSED(self);
    MI_UNUSED(context);
    MI_UNUSED(nameSpace);
    MI_UNUSED(className);
    MI_UNUSED(subscriptionID);
    MI_UNUSED(subscriptionSelf);

    unsubscribeCalled = MI_TRUE;
}

MI_ProviderFT _SubscrContextTest_provFT = 
{
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
    _SubscrContextTest_DisableIndications,
    NULL,
    _SubscrContextTest_Unsubscribe,
    NULL,
};

STRAND_DEBUGNAME( TestContext );

//
// Close right side upon closing
//
NITS_EXTERN_C void _ContextTest_Close( _In_ Strand* self_ )
{
    Strand_Close( self_ );
}

/*
 * StrandFT functions and table for a faked "Left" side of an interaction.
 */
StrandFT ContextTest_Left_InteractionFT2 = 
{
    ContextTest_Post_ImmediateAck, 
    ContextTest_PostControl_NO_OP, 
    ContextTest_Ack_NO_OP,
    NULL, 
    _ContextTest_Close,
    ContextTest_Finish_NO_OP,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

NITS_EXTERN_C void _ContextTest_Post_CloseUponFinalMsg( _In_ Strand* self_, _In_ Message* msg)
{
    Strand_Ack(self_);

    if (PostResultMsgTag == msg->tag)
    {
        /* close self upon receiving final message, it will close the other side stand */
        Strand_Close(self_);
    }
}

/*
 * StrandFT functions and table for a faked "Left" side of an interaction.
 */
StrandFT ContextTest_Left_InteractionFT3 = 
{
    _ContextTest_Post_CloseUponFinalMsg, 
    ContextTest_PostControl_NO_OP, 
    ContextTest_Ack_NO_OP,
    NULL, 
    ContextTest_Close_NO_OP,
    ContextTest_Finish_NO_OP,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

//
// Release the request message upon finished
//
NITS_EXTERN_C void _ContextTest_Finish_ReleaseRequestMsg( _In_ Strand* self_ )
{
    Context* self = FromOffset(Context, strand, self_);
    if (self->request)
        Message_Release(&self->request->base);
}

/*
 * StrandFT functions and table for a faked "Right" side of an interaction that
 * sits within the SubscriptionContext's Context.
 */
StrandFT ContextTest_Right_InteractionFT2 = 
{
    ContextTest_Post_NO_OP, 
    ContextTest_PostControl_NO_OP, 
    ContextTest_Ack_ForSubscriptionContext,
    ContextTest_Cancel_NO_OP, 
    ContextTest_Close_NO_OP,
    _ContextTest_Finish_ReleaseRequestMsg,
    NULL,
    ContextTest_Aux_PostLeft_ForSubscriptionContext,
    NULL,
    NULL,
    NULL,
    NULL
};

NitsSetup(TestSubscriptionContextSetup)
{
    unsubscribeCalled = MI_FALSE;
    testContext = NULL;

    memset( &context, 0, sizeof(SubscriptionContext));
    memset( &provider, 0, sizeof(Provider) );
    memset( &leftSideStrand, 0, sizeof(Strand) );
    memset( &modifiedRtti, 0, sizeof(MI_ClassDecl) );

    /* Strand initialization */
    Strand_Init( STRAND_DEBUG(TestContext) &leftSideStrand, &ContextTest_Left_InteractionFT2, 0, NULL );

    /* Provider initialization */
    memcpy( &modifiedRtti, &CIM_InstCreation_rtti, sizeof(MI_ClassDecl) );
    modifiedRtti.providerFT = (MI_CONST MI_ProviderFT*)&_SubscrContextTest_provFT;
    provider.classDecl = &modifiedRtti;

    //
    // Initialize provider
    //
    NitsAssertOrReturn(MI_RESULT_OK == Test_Provider_Init( &provider ), PAL_T("Failed to initialize subscription manager") );

    memset(&g_library, 0, sizeof(Library));
    memset(&g_provMgr, 0, sizeof(ProvMgr));
    provider.lib = &g_library;
    provider.lib->provmgr = &g_provMgr;

    /* Message initialization */
    request = SubscribeReq_New( 1, 0 );
    if (request)
    {
        request->subscriptionID = 1;
        request->language = QUERY_LANGUAGE_WQL;
        request->filter = PAL_T("SELECT * FROM CIM_SomeClass");
    }
    else
    {
        UT_ASSERT(false);
    }

    subscription = SubMgrSubscription_New(request);
    NitsAssert( NULL != subscription, PAL_T("Unable to initialize subscription") );
}
NitsEndSetup

NitsCleanup(TestSubscriptionContextSetup)
{
    if (subscription)
    {
        NitsAssert( 1 == subscription->refcount, PAL_T("Unexpected issue with subscription refCount") );
        SubMgrSubscription_Release(subscription);
        subscription = NULL;
    }
    if (request)
    {
        NitsCompare( 1, (size_t)request->base.base.refCounter, PAL_T("Incorrect Refcount of SubscribeReq msg, leaking memory") );
        SubscribeReq_Release(request);
        request = NULL;
    }
    Test_Provider_Finalize(&provider);
}
NitsEndCleanup

void RequestHandler_LocalInit()
{
    //
    // Initialize unsubscribe handler
    // unsubscribe must happen on separate thread
    //
    RequestHandler_Init(&g_requesthandler);
}

void RequestHandler_LocalFinalize()
{
    //
    // Initialize unsubscribe handler
    // unsubscribe must happen on separate thread
    // wait for that thread to finish the unsubscribe call
    //
    while ( Atomic_Read( &g_requesthandler.running ) == 1 )
    {
        Sleep_Milliseconds( 10 );
    }
    RequestHandler_Finalize(&g_requesthandler);
}

NitsTestWithSetup(TestSubscriptionContext_InitAndClose, TestSubscriptionContextSetup)
{
    NitsDisableFaultSim;
    
    InteractionOpenParams params;

    InteractionOpenParams_Init(&params);
    leftSideStrand.info.thisAckPending = MI_TRUE;
    leftSideStrand.info.opened = MI_TRUE;
    params.interaction = &leftSideStrand.info.interaction;
    params.msg = &request->base.base;
    
    UT_ASSERT_EQUAL( MI_RESULT_OK, SubscrContext_Init( &context, NULL, CTX_TYPE_IND_SUBSCRIPTION, &params, subscription ) );

    /* Needed to free the refCount added by SubscrContext_Init */
    NitsAssert( 2 == subscription->refcount, PAL_T("Unexpected refcount change") );
    SubMgrSubscription_Release(subscription);

    // Manually leave the context 
    Strand_Leave( &context.baseCtx.strand );
    
    /* Sanity checks on initialized context */
    UT_ASSERT_EQUAL(subscription, context.subscription);
    UT_ASSERT_EQUAL(CTX_TYPE_IND_SUBSCRIPTION, context.baseCtx.ctxType);
    UT_ASSERT(NULL != context.baseCtx.base.ft);

    SubscrContext_Close( &context );

    /* Verify destroyed */
    UT_ASSERT_EQUAL((MI_Uint32)0xFFFFFFFF, context.baseCtx.magic );
}
NitsEndTest

NitsTestWithSetup(TestSubscriptionContext_GetSubscription, TestSubscriptionContextSetup)
{
    context.subscription = subscription;

    UT_ASSERT_EQUAL( subscription, SubscrContext_GetSubscription( &context ) );
}
NitsEndTest

NitsTestWithSetup(TestSubscriptionContext_SendMsg, TestSubscriptionContextSetup)
{
    NitsDisableFaultSim;

    InteractionOpenParams params;

    InteractionOpenParams_Init(&params);
    leftSideStrand.info.thisAckPending = MI_TRUE;
    leftSideStrand.info.opened = MI_TRUE;
    //
    // need to close right side upon get final message, thus use ContextTest_Left_InteractionFT3
    //
    leftSideStrand.info.userFT = &ContextTest_Left_InteractionFT3;
    params.interaction = &leftSideStrand.info.interaction;
    params.msg = &request->base.base;

    MI_Result r = CreateAndAddSubscriptionHelper( provider.subMgr, &provider, &params, &testContext);
    UT_ASSERT_EQUAL( MI_RESULT_OK, r );
    if (r != MI_RESULT_OK)
        return;

    /* Overwrite the strand FT to prevent the message from getting sent out */
    testContext->baseCtx.strand.info.userFT = &ContextTest_Right_InteractionFT2;

    /* Check each of the message types. Send SubscribeResponse first since the final msg will clean up the subscription. */
    UT_ASSERT_EQUAL( MI_RESULT_OK, SubscrContext_SendSubscribeResponseMsg( testContext ) );

    UT_ASSERT_EQUAL( MI_RESULT_OK, SubscrContext_SendFinalResultMsg( testContext, MI_RESULT_NOT_FOUND, NULL, NULL ) );

    //
    // Remove subscription from submgr, otherwise SubMgrSubscription leaked
    //
    SubscriptionManager* submgr = testContext->baseCtx.provider->subMgr;
    SubMgrSubscription* sub = testContext->subscription;
    SubMgr_DeleteSubscription(submgr, sub);
}
NitsEndTest

NitsTestWithSetup(TestSubscriptionContext_Unsubscribe_Success, TestSubscriptionContextSetup)
{
    NitsDisableFaultSim;

    InteractionOpenParams params;

    InteractionOpenParams_Init(&params);
    leftSideStrand.info.thisAckPending = MI_TRUE;
    leftSideStrand.info.opened = MI_TRUE;
    //
    // need to close right side upon get final message, thus use ContextTest_Left_InteractionFT3
    //
    leftSideStrand.info.userFT = &ContextTest_Left_InteractionFT3;
    params.interaction = &leftSideStrand.info.interaction;
    params.msg = &request->base.base;

    RequestHandler_LocalInit();

    UT_ASSERT_EQUAL( MI_RESULT_OK, SubscrContext_Init( &context, &provider, CTX_TYPE_IND_SUBSCRIPTION, &params, subscription ) );

    //
    // context.c:Context_PostMessageLeft frees the refCount added by SubscrContext_Init
    //
    NitsAssert( 2 == subscription->refcount, PAL_T("Unexpected refcount change") );

    //
    // Manually leave the context
    //
    Strand_Leave( &context.baseCtx.strand );


    unsubscribeCalled = MI_FALSE;
    subscription->state = SubscriptionState_Subscribed;

    //
    // Call Unsubscribe within the context of the "left" side strand so that 
    // its internal Strand_LeaveStrand() call will work in debug mode.
    //
    Strand_ScheduleCancel( &leftSideStrand );

    RequestHandler_LocalFinalize();

    UT_ASSERT( unsubscribeCalled );
    UT_ASSERT_EQUAL( SubscriptionState_Unsubscribing, subscription->state );

    //
    // Manually release the reference to request message due to subscription->subContext is set to NULL
    // and context will not be closed
    //
    if (context.baseCtx.request)
    {
        Message_Release( &context.baseCtx.request->base );
        context.baseCtx.request = NULL;
    }
}
NitsEndTest

NitsTestWithSetup(TestSubscriptionContext_Unsubscribe_InvalidSubState, TestSubscriptionContextSetup)
{
    NitsDisableFaultSim;

    /* The setUp function will not set the subscription state, so it will immediately fail */
    context.baseCtx.ctxType = CTX_TYPE_IND_SUBSCRIPTION;
    context.subscription = subscription; /* Prevents AV during the call since it is expected to be set up during init */
    context.baseCtx.provider = &provider; /* Prevents DEBUG_ASSERT during the call*/

    RequestHandler_LocalInit();

    UT_ASSERT_EQUAL( MI_RESULT_FAILED, SubscrContext_Unsubscribe( &context ) ); 

    RequestHandler_LocalFinalize();
    
    NitsIgnoringError(); // same error in OOM case or otherwise
}
NitsEndTest

NitsTestWithSetup(TestSubscriptionContext_Unsubscribe_AlreadyUnsubscribing, TestSubscriptionContextSetup)
{
    NitsDisableFaultSim;

    context.baseCtx.ctxType = CTX_TYPE_IND_SUBSCRIPTION;
    context.subscription = subscription; /* Prevents AV during call since it is expected to be set up during init */
    context.baseCtx.provider = &provider; /* Prevents DEBUG_ASSERT during the call*/

    RequestHandler_LocalInit();

    subscription->state = SubscriptionState_Unsubscribing;
    UT_ASSERT_EQUAL( MI_RESULT_FAILED, SubscrContext_Unsubscribe( &context ) );    

    subscription->state = SubscriptionState_Unsubscribed;
    UT_ASSERT_EQUAL( MI_RESULT_FAILED, SubscrContext_Unsubscribe( &context ) );   

    RequestHandler_LocalFinalize();

    NitsIgnoringError(); // same error in OOM case or otherwise
}
NitsEndTest

/*
NitsTestWithSetup(TestSubscriptionContext_Unsubscribe_NoProviderClassDecl, TestSubscriptionContextSetup)
{
    modifiedRtti.providerFT = NULL; / * undo generic setup * /

    UT_ASSERT_EQUAL( MI_RESULT_OK, SubscrContext_Init( &context, &request->base, &provider, CTX_TYPE_IND_SUBSCRIPTION, NULL, subscription ) );

    subscription->state = SubscriptionState_Subscribed;
    UT_ASSERT_EQUAL( MI_RESULT_INVALID_CLASS, SubscrContext_Unsubscribe( &context ) );

}
NitsEndTest
*/

