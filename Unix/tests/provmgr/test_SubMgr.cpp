/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <ut/ut.h>
#include <pal/palcommon.h>
#include <pal/strings.h>
#include <base/messages.h>
#include <provmgr/SubMgr.h>
#include <provmgr/SubscriptionContext.h>
#include "StrandHelper.h"
#include <provmgr/indicationSchema.h>

using namespace std;

MI_ConstString subMgrDefaultFilter = MI_T("SELECT * FROM CIM_InstCreation WHERE SourceInstanceModelPath = \"MSFT:CreationIndicationIdentifier\"");
MI_ConstString subMgrLanguageWql = MI_T("WQL");

MI_Boolean SubMgr_IsSubscribed(
    _In_opt_ const SubscriptionManager* mgr )
{
    if (!mgr)
    {
        return MI_FALSE;
    }

    if (MI_FALSE == SubMgr_IsEnabled(mgr) )
    {
        return MI_FALSE;
    }

    if (mgr->subscrList.head)
    {
        return MI_TRUE;
    }
    return MI_FALSE;
}


NitsTest(TestSubMgr_NewAndDelete)
{
    SubscriptionManager* subMgr = SubMgr_New();

    NitsAssert(NULL != subMgr, PAL_T("expected allocation of SubscriptionManager*") );
    
    if (subMgr)
    {
        SubMgr_Delete( subMgr );
    }
}
NitsEndTest

struct TestSubMgr_Struct
{
    SubscriptionManager* subMgr;
    Strand leftSideStrand;
};

TestSubMgr_Struct setupTemplate = { 0 };
STRAND_DEBUGNAME( test_SubMgr_Strand0 );

/*
 * Allocates and initializes a default SubscriptionManager for use in a variety
 * of tests.
 */
NitsSetup0(TestSubMgr_SetupSubMgr, TestSubMgr_Struct)
{
    NitsContext()->_TestSubMgr_Struct->subMgr = SubMgr_New();
    SubscriptionManager* subMgr = NitsContext()->_TestSubMgr_Struct->subMgr;
    if ( ! subMgr )
    {
        NitsAssertOrReturn(false, PAL_T("expected allocation of SubscriptionManager*") );
    }

    SubMgr_Init( subMgr, NULL );
    NitsAssert( MI_FALSE == SubMgr_IsEnabled(subMgr), PAL_T("invalid state after Init") );
}
NitsEndSetup

/*
 * Cleans up and de-allocates SubscriptionManager.
 */
NitsCleanup(TestSubMgr_SetupSubMgr)
{
    if (NitsContext()->_TestSubMgr_Struct->subMgr)
    {
        SubscriptionManager* submgr = NitsContext()->_TestSubMgr_Struct->subMgr;
        SubMgr_CancelAllSubscriptions( submgr, MI_RESULT_FAILED, NULL, NULL );
        SubMgr_Delete( NitsContext()->_TestSubMgr_Struct->subMgr );
    }
}
NitsEndCleanup

NitsTest1(TestSubMgr_IsSubscribed_failures, TestSubMgr_SetupSubMgr, setupTemplate )
{
    SubscriptionManager *subMgr = NitsContext()->_TestSubMgr_SetupSubMgr->_TestSubMgr_Struct->subMgr;
    SubscriptionManager *nullSubMgr = NULL;
    
    NitsAssert( MI_FALSE == SubMgr_IsSubscribed( nullSubMgr ), PAL_T("No support expected") );

    NitsAssert( MI_FALSE == SubMgr_IsSubscribed( subMgr ), PAL_T("Invalid state expected") );

    SubMgr_SetEnabled( subMgr, MI_TRUE );
    NitsAssert( MI_FALSE == SubMgr_IsSubscribed( subMgr ), PAL_T("No subscription detected expected") );
}
NitsEndTest

NitsTest1(TestSubMgr_BasicAddAndDeleteSubscription, TestSubMgr_SetupSubMgr, setupTemplate )
{
    TestSubMgr_Struct* tss = NitsContext()->_TestSubMgr_SetupSubMgr->_TestSubMgr_Struct;
    SubscriptionManager *subMgr = tss->subMgr;

    SubscribeReq* msg = SubscribeReq_New( 0, 0 );
    SubscriptionContext* context;
    Provider provider;

    if(!NitsAssert(msg != NULL, PAL_T("failed to allocate msg")))
        NitsReturn;
    context = NULL;
    memset( &provider, 0, sizeof(Provider) );

    msg->targetType = SUBSCRIP_TARGET_LIFECYCLE_CREATE;
    msg->filter = subMgrDefaultFilter;
    msg->language = subMgrLanguageWql;
    msg->subscriptionID = 1337;

    provider.refusedUnload = MI_TRUE; // Prevents Provider_Release from releasing
    provider.classDecl = &CIM_InstCreation_rtti;

    // Strand initialization
    Strand_Init( STRAND_DEBUG(test_SubMgr_Strand0) &tss->leftSideStrand, &ContextTest_Left_InteractionFT, 0, NULL );
    // Simulate opening with message mode 
    tss->leftSideStrand.info.opened = MI_TRUE;
    tss->leftSideStrand.info.thisAckPending = MI_TRUE;

    InteractionOpenParams params;

    InteractionOpenParams_Init(&params);
    params.interaction = &tss->leftSideStrand.info.interaction;
    params.msg = &msg->base.base;

    // Add subscription
    MI_Result r = CreateAndAddSubscriptionHelper(
        subMgr,
        &provider,
        &params,
        &context);
        
    NitsAssert( MI_RESULT_OK == r, PAL_T("Failed to add subscription") );

    SubMgrSubscription* subscription = SubMgr_GetSubscription(subMgr, 1337 );
    NitsAssert( NULL != subscription, PAL_T("Failed to retrieve newly created subscription") );

    if (subscription)
    {
        NitsAssert( MI_RESULT_OK == SubMgr_DeleteSubscription( subMgr, subscription), PAL_T("Expected subscription, none found") );
        //
        // release the refcount added by by SubscrContext_Init
        //
        SubMgrSubscription_Release( subscription );
    }

    if ( context )
    {
        _Context_Destroy(&context->baseCtx);
    }

    if (msg)
    {
        SubscribeReq_Release( msg );
    }
}
NitsEndTest

struct TestSubMgr_Subscription_Struct
{
    SubscribeReq* msg1;
    SubscriptionContext* context1;

    SubscribeReq* msg2;
    SubscriptionContext* context2;

    Provider provider;

    Strand leftSideStrand1;
    Strand leftSideStrand2;
};

TestSubMgr_Subscription_Struct subMgrTemplate = { 0 };

STRAND_DEBUGNAME( test_SubMgr_Strand1 );
STRAND_DEBUGNAME( test_SubMgr_Strand2 );

NitsSetup1(TestSubMgr_AddSubscriptions, TestSubMgr_Subscription_Struct, TestSubMgr_SetupSubMgr, setupTemplate )
{
    TestSubMgr_Subscription_Struct* subStruct = NitsContext()->_TestSubMgr_Subscription_Struct;
    SubscriptionManager* subMgr = NitsContext()->_TestSubMgr_SetupSubMgr->_TestSubMgr_Struct->subMgr;

    subStruct->msg1 = SubscribeReq_New( 0, 0 );
    subStruct->msg2 = SubscribeReq_New( 0, 0 );

    if(!NitsAssert((subStruct->msg1 != NULL) && (subStruct->msg2 != NULL), PAL_T("allocation failed")))
        NitsReturn;
    subStruct->context1 = NULL;
    subStruct->context2 = NULL;
    
    memset( &subStruct->provider, 0, sizeof(Provider) );

    subStruct->msg1->targetType = SUBSCRIP_TARGET_LIFECYCLE_CREATE;
    subStruct->msg1->filter = subMgrDefaultFilter;
    subStruct->msg1->language = subMgrLanguageWql;
    subStruct->msg1->subscriptionID = 1337;

    subStruct->msg2->targetType = SUBSCRIP_TARGET_LIFECYCLE_CREATE;
    subStruct->msg2->filter = subMgrDefaultFilter;
    subStruct->msg2->language = subMgrLanguageWql;
    subStruct->msg2->subscriptionID = 1338;

    subStruct->provider.refusedUnload = MI_TRUE; // Prevents Provider_Release from releasing
    subStruct->provider.classDecl = &CIM_InstCreation_rtti;

    // Strand initialization
    Strand_Init( STRAND_DEBUG(test_SubMgr_Strand1) &subStruct->leftSideStrand1, &ContextTest_Left_InteractionFT, 0, NULL );
    subStruct->leftSideStrand1.info.thisAckPending = MI_TRUE;
    subStruct->leftSideStrand1.info.opened = MI_TRUE;
    Strand_Init( STRAND_DEBUG(test_SubMgr_Strand2) &subStruct->leftSideStrand2, &ContextTest_Left_InteractionFT, 0, NULL );
    subStruct->leftSideStrand2.info.thisAckPending = MI_TRUE;
    subStruct->leftSideStrand2.info.opened = MI_TRUE;

    InteractionOpenParams params;

    InteractionOpenParams_Init(&params);
    params.interaction = &subStruct->leftSideStrand1.info.interaction;
    params.msg = &subStruct->msg1->base.base;

    //
    // Add subscription
    //
    MI_Result r = CreateAndAddSubscriptionHelper(
        subMgr,
        &subStruct->provider,
        &params,
        &subStruct->context1);
    NitsAssert( MI_RESULT_OK == r, PAL_T("Failed to add subscription") );

    InteractionOpenParams_Init(&params);
    params.interaction = &subStruct->leftSideStrand2.info.interaction;
    params.msg = &subStruct->msg2->base.base;

    //
    // Add subscription
    //
    r = CreateAndAddSubscriptionHelper(
        subMgr,
        &subStruct->provider,
        &params,
        &subStruct->context2);
    NitsAssert( MI_RESULT_OK == r, PAL_T("Failed to add subscription") );

    SubMgr_SetEnabled( subMgr, MI_TRUE);
    NitsAssert( MI_TRUE == SubMgr_IsEnabled( subMgr ), PAL_T("Unable to set state") );
}
NitsEndSetup

NitsCleanup(TestSubMgr_AddSubscriptions)
{
    SubscriptionManager* subMgr = NitsContext()->_TestSubMgr_SetupSubMgr->_TestSubMgr_Struct->subMgr;
    TestSubMgr_Subscription_Struct* subStruct = NitsContext()->_TestSubMgr_Subscription_Struct;

    SubMgrSubscription* subscription = SubMgr_GetSubscription(subMgr, 1337 );

    NitsAssert( NULL != subscription, PAL_T("Failed to retrieve newly created subscription") );
    if (subscription)
    {
        //
        // Simulate PostResult to subscribecontext.
        // TODO: to rely on SubMgr_CancelAllSubscriptions to clean up subscriptions,
        // which needs to setup all dependent structures
        //
        NitsAssert( MI_RESULT_OK == SubMgr_DeleteSubscription( subMgr, subscription), PAL_T("Expected subscription, none found") );
        SubMgrSubscription_Release( subscription );
    }

    subscription = SubMgr_GetSubscription(subMgr, 1338 );
    
    NitsAssert( NULL != subscription, PAL_T("Failed to retrieve newly created subscription") );
    if (subscription)
    {
        //
        // Simulate PostResult to subscribecontext
        // TODO: to rely on SubMgr_CancelAllSubscriptions to clean up subscriptions,
        // which needs to setup all dependent structures
        //
        NitsAssert( MI_RESULT_OK == SubMgr_DeleteSubscription( subMgr, subscription), PAL_T("Expected subscription, none found") );
        SubMgrSubscription_Release( subscription );
    }

    _Context_Destroy(&subStruct->context1->baseCtx);
    _Context_Destroy(&subStruct->context2->baseCtx);

    if (subStruct->msg1)
    {
        NitsCompare(1, (size_t)subStruct->msg1->base.base.refCounter, PAL_T("RefCount of request message is wrong. Leak memory"));
        SubscribeReq_Release( subStruct->msg1 );
    }

    if (subStruct->msg2)
    {
        NitsCompare(1, (size_t)subStruct->msg2->base.base.refCounter, PAL_T("RefCount of request message is wrong. Leak memory"));
        SubscribeReq_Release( subStruct->msg2 );
    }    
}
NitsEndCleanup

NitsTest1(TestSubMgr_IsSubscribed_success, TestSubMgr_AddSubscriptions, subMgrTemplate )
{
    SubscriptionManager *subMgr = NitsContext()->_TestSubMgr_AddSubscriptions->_TestSubMgr_SetupSubMgr->_TestSubMgr_Struct->subMgr;

    NitsAssert( MI_TRUE == SubMgr_IsSubscribed( subMgr ), PAL_T("No subscription detected expected") );
}
NitsEndTest

NitsTest1(TestSubMgr_GetSubscription_NotFound, TestSubMgr_AddSubscriptions, subMgrTemplate )
{
    SubscriptionManager *subMgr = NitsContext()->_TestSubMgr_AddSubscriptions->_TestSubMgr_SetupSubMgr->_TestSubMgr_Struct->subMgr;

    NitsAssert( NULL == SubMgr_GetSubscription( subMgr, 2000 ), PAL_T("Subscription ID present when not expected") );
}
NitsEndTest

NitsTest1(TestSubMgr_GetSubscription_NotPresent, TestSubMgr_SetupSubMgr, setupTemplate )
{
    SubscriptionManager *subMgr = NitsContext()->_TestSubMgr_SetupSubMgr->_TestSubMgr_Struct->subMgr;
    NitsAssert( NULL == SubMgr_GetSubscription( subMgr, 1337 ), PAL_T("Subscription ID present when not expected (empty list)") );
}
NitsEndTest

void Verify_SubMgrSubscription_New_Input(
    MI_ConstString filter,
    MI_ConstString language,
    MI_Boolean shouldSucceed)
{
    SubscribeReq* msg = SubscribeReq_New( 0, 0 );

    if(!NitsAssert(msg != NULL, PAL_T("msg alloc failed")))
        return;
    
    msg->targetType = SUBSCRIP_TARGET_LIFECYCLE_CREATE;
    msg->filter = filter;
    msg->language = language;
    msg->subscriptionID = 1337;

    SubMgrSubscription* testSub = SubMgrSubscription_New( msg );

    if (shouldSucceed)
        NitsAssert( NULL != testSub, PAL_T("Subscription allocation failure not expected") );
    else
        NitsAssert( NULL == testSub, PAL_T("Subscription allocation succeeded.  Failure expected") );

    NitsIgnoringError(); // negative test case; same failure in OOM or otherwise
    if ( testSub)
    {
        SubMgrSubscription_Release( testSub );
    }
    if (msg)
    {
        SubscribeReq_Release( msg );
    }
}

NitsTest(TestSubMgrSubscription_New_Fails_if_FilterError)
{
    // NULL filter and lanugage will trigger a failure
    Verify_SubMgrSubscription_New_Input( NULL, NULL, MI_FALSE );
}
NitsEndTest

NitsTest(TestSubMgrSubscription_New_Success)
{
    // CIM_InstCreation matches SourceInstanceModelPath in class decl's 
    // property list
    Verify_SubMgrSubscription_New_Input( subMgrDefaultFilter, subMgrLanguageWql, MI_TRUE );
}
NitsEndTest


struct TestSubMgrSubscription_Struct
{
    SubscribeReq* msg;
    SubMgrSubscription* testSubscription;
};

TestSubMgrSubscription_Struct subscriptionTemplate = { 0 };


NitsSetup0(TestSubMgrSubscription_Setup, TestSubMgrSubscription_Struct)
{
    TestSubMgrSubscription_Struct *setupStruct = NitsContext()->_TestSubMgrSubscription_Struct;

    setupStruct->msg = SubscribeReq_New( 0, 0 );

    setupStruct->msg->targetType = SUBSCRIP_TARGET_LIFECYCLE_CREATE;
    setupStruct->msg->filter = subMgrDefaultFilter;
    setupStruct->msg->language = subMgrLanguageWql;
    setupStruct->msg->subscriptionID = 1337;

    setupStruct->testSubscription = SubMgrSubscription_New( setupStruct->msg );
}
NitsEndSetup

NitsCleanup(TestSubMgrSubscription_Setup)
{
    TestSubMgrSubscription_Struct *setupStruct = NitsContext()->_TestSubMgrSubscription_Struct;

    if ( setupStruct->testSubscription)
    {
        SubMgrSubscription_Release( setupStruct->testSubscription );
    }
    
    if (setupStruct->msg)
    {
        SubscribeReq_Release( setupStruct->msg );
    }
}
NitsEndCleanup

NitsTest1(TestSubMgrSubscription_NewAndDelete, TestSubMgrSubscription_Setup, subscriptionTemplate)
{
    TestSubMgrSubscription_Struct *setupStruct = NitsContext()->_TestSubMgrSubscription_Setup->_TestSubMgrSubscription_Struct;
    NitsAssert( NULL != setupStruct->testSubscription, PAL_T("Subscription allocation failed") );
}
NitsEndTest

NitsTest1(TestSubMgrSubscription_SetState, TestSubMgrSubscription_Setup, subscriptionTemplate)
{
    TestSubMgrSubscription_Struct *setupStruct = NitsContext()->_TestSubMgrSubscription_Setup->_TestSubMgrSubscription_Struct;

    SubscriptionState originalState = setupStruct->testSubscription->state;
    NitsAssert( MI_RESULT_OK == SubMgrSubscription_SetState( setupStruct->testSubscription, SubscriptionState_Unsubscribed ), PAL_T("Failed to set state") );
    NitsAssert( SubscriptionState_Unsubscribed == setupStruct->testSubscription->state, PAL_T("Unexpected subscription state") );
    NitsAssert( MI_RESULT_OK == SubMgrSubscription_SetState( setupStruct->testSubscription, originalState ), PAL_T("Failed to set state") );  // reset the original state for cleanup
}
NitsEndTest

NitsTest1(TestSubMgrSubscription_GetSupportedTypes, TestSubMgrSubscription_Setup, subscriptionTemplate)
{
    TestSubMgrSubscription_Struct *setupStruct = NitsContext()->_TestSubMgrSubscription_Setup->_TestSubMgrSubscription_Struct;
    // Default case based on test setup
    NitsAssert( SUBSCRIP_TARGET_LIFECYCLE_CREATE == SubMgrSubscription_GetSupportedTypes( setupStruct->testSubscription ), PAL_T("Failed to get supported types") );

    // Base cases
    NitsAssert( SUBSCRIP_TARGET_UNSUPPORTED == SubMgrSubscription_GetSupportedTypes( NULL ), PAL_T("Unexpected supported types") );

    SubMgrSubscription emptySub;
    memset( &emptySub, 0, sizeof(SubMgrSubscription) );
    NitsAssert( SUBSCRIP_TARGET_UNSUPPORTED == SubMgrSubscription_GetSupportedTypes( &emptySub ), PAL_T("Unexpected supported types") );
}
NitsEndTest

NitsTest1(TestSubMgrSubscription_IsQueryValid, TestSubMgrSubscription_Setup, subscriptionTemplate)
{
    TestSubMgrSubscription_Struct *setupStruct = NitsContext()->_TestSubMgrSubscription_Setup->_TestSubMgrSubscription_Struct;

    // Returns MI_TRUE for valid queries:
    // CIM_InstCreation matches SourceInstanceModelPath in class decl's 
    // property list
    NitsAssert( MI_TRUE == SubMgrSubscription_IsQueryValid( setupStruct->testSubscription, &CIM_InstCreation_rtti), PAL_T("Invalid subscription query.  Valid expected") );


    // Returns MI_FALSE for invalid queries
    // CIM_InstCreation doesn't match SourceInstanceModelPath in class decl's 
    // property list
    NitsAssert( MI_FALSE == SubMgrSubscription_IsQueryValid( setupStruct->testSubscription, &CIM_Indication_rtti), PAL_T("Valid subscription query.  Invalid expected") );    
}
NitsEndTest

