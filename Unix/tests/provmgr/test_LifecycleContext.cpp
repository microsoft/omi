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
#include <pal/sleep.h>
#include <pal/atomic.h>
#include <indication/common/indicommon.h>
#include <provmgr/LifecycleContext.h>
#include <provmgr/indicationSchema.h>
#include <provmgr/SubscriptionContext.h>
#include <provmgr/SubMgr.h>
#include <base/messages.h>
#include <provmgr/CIM_InstCreation.h>
#include "StrandHelper.h"
#include <pal/thread.h>
#include <provmgr/nioproc.h>
#include <base/schemadecl.h>
#include "XYZ_Test.h"

NitsTest(Test_LifecycleContext_ConvertSupportedType)
{
    NitsAssert( MI_LIFECYCLE_INDICATION_NONE == LifeContext_ConvertSupportedType( SUBSCRIP_TARGET_UNSUPPORTED ), PAL_T("Unsupported convert failed") );
    NitsAssert( MI_LIFECYCLE_INDICATION_NONE == LifeContext_ConvertSupportedType( SUBSCRIP_TARGET_DEFAULT ), PAL_T("Default convert failed") );
    NitsAssert( MI_LIFECYCLE_INDICATION_ALL == LifeContext_ConvertSupportedType( SUBSCRIP_TARGET_LIFECYCLE_ALL ), PAL_T("ALL convert failed") );
    NitsAssert( MI_LIFECYCLE_INDICATION_CREATE == LifeContext_ConvertSupportedType( SUBSCRIP_TARGET_LIFECYCLE_CREATE ), PAL_T("Create convert failed") );
    NitsAssert( MI_LIFECYCLE_INDICATION_MODIFY == LifeContext_ConvertSupportedType( SUBSCRIP_TARGET_LIFECYCLE_MODIFY ), PAL_T("Modify convert failed") );
    NitsAssert( MI_LIFECYCLE_INDICATION_DELETE == LifeContext_ConvertSupportedType( SUBSCRIP_TARGET_LIFECYCLE_DELETE ), PAL_T("Delete convert failed") );
    NitsAssert( MI_LIFECYCLE_INDICATION_READ == LifeContext_ConvertSupportedType( SUBSCRIP_TARGET_LIFECYCLE_READ ), PAL_T("Read convert failed") );
    NitsAssert( MI_LIFECYCLE_INDICATION_METHODCALL == LifeContext_ConvertSupportedType( SUBSCRIP_TARGET_LIFECYCLE_METHODCALL ), PAL_T("MethodCall convert failed") );
}
NitsEndTest

LifecycleContext* lifeContext = NULL;

MI_Boolean indicationPosted = MI_FALSE;

MI_Boolean unsubscribeLifeCtxCompletedSemActive = MI_FALSE;
Sem unsubscribeLifeCtxCompletedSem;

//
// This initializes the Finish semaphore to cause the test case to wait for 
// the unsubscribe thread to complete prior to exiting.
//
void _InitializeTestLifeCtxSemaphore()
{
    NitsAssert( NULL != lifeContext, PAL_T("Expected initialization in setup function") );
    NitsAssert( Sem_Init(&unsubscribeLifeCtxCompletedSem, SEM_USER_ACCESS_ALLOW_ALL, 0) == 0, PAL_T("Unable to initialize unsubscribe semaphore") );
    unsubscribeLifeCtxCompletedSemActive = MI_TRUE;
}

void _ReleaseTestLifeCtxSemaphore()
{
    if (unsubscribeLifeCtxCompletedSemActive)
    {
        // This means the unsubscribe thread has completed its cleanup
        // and it is safe to allow the test to proceed with its cleanup.
        NitsAssert( 0 == Sem_Post( &unsubscribeLifeCtxCompletedSem, 1 ), PAL_T("Unexpected semaphore Post status") );
    }
}

void _CleanupTestLifeCtxSemaphore()
{
   if (unsubscribeLifeCtxCompletedSemActive)
   {
       // This forces the test to wait for the unsubscribe thread to complete prior to exiting the test
       Sem_Wait(&unsubscribeLifeCtxCompletedSem);
       unsubscribeLifeCtxCompletedSemActive = MI_FALSE;
       Sem_Destroy(&unsubscribeLifeCtxCompletedSem);
   }
}

NITS_EXTERN_C void _TestLifeCtx_Post( _In_ Strand* self, _In_ Message* msg ) 
{
    if (PostResultMsgTag == msg->tag)
    {
         /* close self upon receiving final message */
        Strand_Close(self);
    }
    else if (PostIndicationMsgTag == msg->tag)
    {
        indicationPosted = MI_TRUE;
    }
 
    Strand_Ack( self );
}

NITS_EXTERN_C void _TestLifeCtx_Finish( _In_ Strand* self_ )
{
    MI_UNUSED( self_ );

    _ReleaseTestLifeCtxSemaphore();
}

static StrandFT TestLifecycleContext_InteractionFT =
{
    _TestLifeCtx_Post, 
    ContextTest_PostControl_NO_OP, 
    ContextTest_Ack_NO_OP,
    ContextTest_Cancel_NO_OP,
    ContextTest_Close_NO_OP,
    _TestLifeCtx_Finish,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL 
};

NitsSetup(Test_LifecycleContext_Setup)
{
    lifeContext = LifeContext_New( );

    NitsAssertOrReturn(NULL != lifeContext, PAL_T("Failed to allocate LifecycleContext*"));
}
NitsEndSetup

NitsCleanup(Test_LifecycleContext_Setup)
{
    if (lifeContext)
    {
        LifeContext_Delete( lifeContext );
        lifeContext = NULL;
    }
}
NitsEndCleanup

MI_ConstString filterForPostTest = MI_T("SELECT * FROM CIM_InstIndication WHERE IndicationIdentifier = \"MSFT:IndicationIdentifier\"");
MI_ConstString languageWql = MI_T("WQL");

struct Test_LifecycleContext_Struct
{
    // Subscription input requirements
    SubscribeReq* msg;
    SubscriptionContext* context;

    CIM_InstCreation sourceInstance;

    // Special fields for OMI -> Provider callback
    MI_Uint32 typesFromCallback;
    MI_Boolean callbackCalled;

    // Note: I encountered this error when this structure was the first within Test_LifecycleContext_Struct.
    // Moving it later in the struct resolve the compile error.
    // test_LifecycleContext.cpp:76: error: missing braces around initializer for "Provider"
    Provider provider;
    Library library;
    ProvMgr provMgr;
    
    MI_ClassDecl tempClass;
    //
    // Left side strand
    //
    Strand leftSideStrand;
};

NITS_EXTERN_C void Local_MI_LifecycleIndicationCallback(
    _In_ MI_Uint32 types,
    _In_opt_ void* callbackData)
{
    if (callbackData)
    {
        Test_LifecycleContext_Struct* testStruct = (Test_LifecycleContext_Struct*)callbackData;
        testStruct->typesFromCallback = types;
        testStruct->callbackCalled = MI_TRUE;
    }
}

Test_LifecycleContext_Struct filterStruct;

void _Initialize_ProviderStruct(
    Test_LifecycleContext_Struct* setupStruct )
{
    // Simulating provider load
    memset( &setupStruct->provider, 0, sizeof(Provider) );
    memset( &setupStruct->library, 0, sizeof(Library) );
    memset( &setupStruct->provMgr, 0, sizeof(ProvMgr) );

    memcpy( &setupStruct->tempClass, &CIM_InstCreation_rtti, sizeof(MI_ClassDecl));

    /*
     * Provider_InvokeDisable check MI_FLAG_INDICATION on class.Flags
     * to decide either invoke DisableIndication function to provider or
     * just finalize lifecycle context
     */
    setupStruct->tempClass.flags &= ~MI_FLAG_INDICATION;
    setupStruct->provider.classDecl = &setupStruct->tempClass;
    setupStruct->provider.refCounter = 1;
    setupStruct->provider.refusedUnload = MI_TRUE;

    setupStruct->provider.lib = &setupStruct->library;
    setupStruct->library.provmgr = &setupStruct->provMgr;

    // Simulates that the test thread is the "IO" thread
    setupStruct->provMgr.ioThreadId = Thread_ID();
}

STRAND_DEBUGNAME( test_LifecycleContext_Strand );
STRAND_DEBUGNAME( test_LifecycleContext_Strand2 );

NitsSetup1(Test_LifecycleContext_Setup_Init, Test_LifecycleContext_Struct, Test_LifecycleContext_Setup, NitsEmptyValue)
{
    Test_LifecycleContext_Struct* tls = NitsContext()->_Test_LifecycleContext_Struct;
    Provider* provider = &tls->provider;

    NitsAssertOrReturn(MI_RESULT_OK == Test_Provider_Init( provider ), PAL_T("Failed to initialize subscription manager") );
    LifeContext_Init( lifeContext, provider );
    NitsAssertOrReturn(lifeContext->provider == provider, PAL_T("LifeContext_Init failed") );
}
NitsEndSetup

NitsCleanup(Test_LifecycleContext_Setup_Init)
{
    Provider* provider = &NitsContext()->_Test_LifecycleContext_Struct->provider;
    SubscriptionManager* subMgr = provider->subMgr;
    NitsAssert( NULL != subMgr, PAL_T("Expected initialized subMgr") );
    Test_Provider_Finalize( provider );
}
NitsEndCleanup

NitsTest1(Test_LifecycleContext_Init_Success, Test_LifecycleContext_Setup_Init, filterStruct)
{
    NitsAssertOrReturn(NULL != lifeContext, PAL_T("Called with NULL LifecycleContext*"));

    // Bail out if this fails because there will be no point to further checks.
    Provider* provider = &(NitsContext()->_Test_LifecycleContext_Setup_Init->_Test_LifecycleContext_Struct->provider);
    LifeContext_Init( lifeContext, provider );
    NitsAssertOrReturn(lifeContext->provider == provider, PAL_T("LifeContext_Init failed") );

    NitsAssert( 0xFEEDCAFE == lifeContext->magic, PAL_T("Invalid magic #") );
    NitsAssert( provider == lifeContext->provider, PAL_T("Uninitialized Provider") );
    NitsAssert( NULL != lifeContext->base.ft, PAL_T("Uninitialized base function table") );
    NitsAssert( MI_LIFECYCLE_INDICATION_ALL == lifeContext->supportedTypesFromProv, PAL_T("Incorrect default supportedTypes") );
    NitsAssert( MI_FALSE == SubMgr_IsEnabled(lifeContext->provider->subMgr), PAL_T("Incorrect subscription state") );
}
NitsEndTest

NitsTest1(Test_LifecycleContext_IsTypeSupported, Test_LifecycleContext_Setup, NitsEmptyValue)
{
    // Tests against ALL
    lifeContext->supportedTypesFromProv = MI_LIFECYCLE_INDICATION_ALL;
    NitsAssert( MI_FALSE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_UNSUPPORTED ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_FALSE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_DEFAULT ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_TRUE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_ALL ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_TRUE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_CREATE ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_TRUE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_MODIFY ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_TRUE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_DELETE ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_TRUE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_READ ), PAL_T("Unsupported subscriptionType") );    
    NitsAssert( MI_TRUE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_METHODCALL ), PAL_T("Unsupported subscriptionType") );

    // Tests against NONE
    lifeContext->supportedTypesFromProv = MI_LIFECYCLE_INDICATION_NONE;
    NitsAssert( MI_FALSE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_UNSUPPORTED ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_FALSE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_DEFAULT ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_FALSE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_ALL ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_FALSE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_CREATE ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_FALSE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_MODIFY ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_FALSE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_DELETE ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_FALSE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_READ ), PAL_T("Unsupported subscriptionType") );    
    NitsAssert( MI_FALSE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_METHODCALL ), PAL_T("Unsupported subscriptionType") );

    // Tests against CREATE
    lifeContext->supportedTypesFromProv = MI_LIFECYCLE_INDICATION_CREATE;
    NitsAssert( MI_FALSE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_UNSUPPORTED ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_FALSE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_DEFAULT ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_TRUE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_ALL ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_TRUE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_CREATE ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_FALSE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_MODIFY ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_FALSE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_DELETE ), PAL_T("Unsupported subscriptionType") );
    NitsAssert( MI_FALSE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_READ ), PAL_T("Unsupported subscriptionType") );    
    NitsAssert( MI_FALSE == LifeContext_IsTypeSupported( lifeContext, SUBSCRIP_TARGET_LIFECYCLE_METHODCALL ), PAL_T("Unsupported subscriptionType") );

    // The logic holds for the rest of the types, so it is redundant to exhaustively list them.
}
NitsEndTest

NitsTest1(Test_LifecycleContext_FT_with_invalid_input, Test_LifecycleContext_Setup_Init, filterStruct)
{
    // Needed for access to the function table
    NitsAssertOrReturn(NULL != lifeContext, PAL_T("Called with NULL LifecycleContext*"));

    LifecycleContext uninitializedContext;
    MI_LifecycleIndicationContext* uninitAsMi = (MI_LifecycleIndicationContext*)&uninitializedContext;
    MI_Instance dummyInstance;
    MI_Uint32 types = MI_LIFECYCLE_INDICATION_CREATE;
    
    memset( &uninitializedContext, 0, sizeof(LifecycleContext) );

    // Create
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_PostCreate( NULL, &dummyInstance ), PAL_T("Expected invalid param") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_PostCreate( (MI_LifecycleIndicationContext*)lifeContext, NULL ), PAL_T("Expected invalid param") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_PostCreate( uninitAsMi, &dummyInstance ), PAL_T("Expected invalid param") );

    // Modify
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_PostModify( NULL, &dummyInstance, &dummyInstance ), PAL_T("Expected invalid param") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_PostModify( (MI_LifecycleIndicationContext*)lifeContext, NULL, &dummyInstance ), PAL_T("Expected invalid param") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_PostModify( (MI_LifecycleIndicationContext*)lifeContext, &dummyInstance, NULL ), PAL_T("Expected invalid param") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_PostModify( uninitAsMi, &dummyInstance, &dummyInstance ), PAL_T("Expected invalid param") );

    // Delete
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_PostDelete( NULL, &dummyInstance ), PAL_T("Expected invalid param") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_PostDelete( (MI_LifecycleIndicationContext*)lifeContext, NULL ), PAL_T("Expected invalid param") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_PostDelete( uninitAsMi, &dummyInstance ), PAL_T("Expected invalid param") );

    // Read
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_PostRead( NULL, &dummyInstance ), PAL_T("Expected invalid param") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_PostRead( (MI_LifecycleIndicationContext*)lifeContext, NULL ), PAL_T("Expected invalid param") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_PostRead( uninitAsMi, &dummyInstance ), PAL_T("Expected invalid param") );

    // MethodCall
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_PostMethodCall_After( NULL, &dummyInstance, MI_T("Unknown"), NULL, NULL ), PAL_T("Expected invalid param") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_PostMethodCall_After( (MI_LifecycleIndicationContext*)lifeContext, NULL, MI_T("Unknown"), NULL, NULL ), PAL_T("Expected invalid param") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_PostMethodCall_After( uninitAsMi, &dummyInstance, MI_T("Unknown"), NULL, NULL ), PAL_T("Expected invalid param") );

    // SetSupportedTypes
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_SetSupportedTypes( NULL, types ), PAL_T("Expected invalid param") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_SetSupportedTypes( uninitAsMi, types ), PAL_T("Expected invalid param") );

    // GetTypes
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_GetTypes( NULL, &types ), PAL_T("Expected invalid param") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_GetTypes( (MI_LifecycleIndicationContext*)lifeContext, NULL ), PAL_T("Expected invalid param") );

    // RegisterCallback
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_RegisterCallback( NULL, &Local_MI_LifecycleIndicationCallback, NULL ), PAL_T("Expected invalid param") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_RegisterCallback( (MI_LifecycleIndicationContext*)lifeContext, NULL, NULL ), PAL_T("Expected invalid param") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_LifecycleIndicationContext_RegisterCallback( uninitAsMi, &Local_MI_LifecycleIndicationCallback, NULL ), PAL_T("Expected invalid param") );
}
NitsEndTest

NitsTest1(Test_LifecycleContext_Post_With_No_Subscription, Test_LifecycleContext_Setup_Init, filterStruct)
{
    Test_LifecycleContext_Struct* setupStruct = NitsContext()->_Test_LifecycleContext_Setup_Init->_Test_LifecycleContext_Struct;
    MI_Instance* srcInst = &(setupStruct->sourceInstance.__instance);

    if (NitsAssert( MI_RESULT_OK == Instance_Construct( srcInst, &CIM_InstCreation_rtti, NULL ), PAL_T("Unable to create instance") ))
    {
        /* MI_ConstStringField IndicationIdentifier */
        MI_Value value;
        value.string = (MI_Char*)PAL_T("DummyInstanceCreatedForEaseOfTesting");
        NitsAssert( MI_RESULT_OK == MI_Instance_SetElement( srcInst, PAL_T("IndicationIdentifier"), &value, MI_STRING, 0 ), PAL_T("Unable to set identifier") );

        // Case 1: Create
        NitsAssert( MI_RESULT_FAILED == MI_LifecycleIndicationContext_PostCreate( (MI_LifecycleIndicationContext*)lifeContext, srcInst ), PAL_T("Expected failure") );

        // Case 2: Modify
        NitsAssert( MI_RESULT_FAILED == MI_LifecycleIndicationContext_PostModify( (MI_LifecycleIndicationContext*)lifeContext, srcInst, srcInst ), PAL_T("Expected invalid param") );

        // Case 3: Delete
        NitsAssert( MI_RESULT_FAILED == MI_LifecycleIndicationContext_PostDelete( (MI_LifecycleIndicationContext*)lifeContext, srcInst ), PAL_T("Expected invalid param") );

        // Case 4: Read
        NitsAssert( MI_RESULT_FAILED == MI_LifecycleIndicationContext_PostRead( (MI_LifecycleIndicationContext*)lifeContext, srcInst ), PAL_T("Expected invalid param") );

        // Case 5: MethodCall
        NitsAssert( MI_RESULT_FAILED == MI_LifecycleIndicationContext_PostMethodCall_After( (MI_LifecycleIndicationContext*)lifeContext, srcInst, MI_T("Unknown"), NULL, NULL ), PAL_T("Expected invalid param") );

        MI_Instance_Destruct( &setupStruct->sourceInstance.__instance );
    }
}
NitsEndTest

// LifeContext_UpdateSupportedTypes
NitsTest1(Test_LifecycleContext_UpdateSupportedTypes_No_Subscriptions, Test_LifecycleContext_Setup_Init, filterStruct)
{
    NitsAssertOrReturn(NULL != lifeContext, PAL_T("Called with NULL LifecycleContext*"));

    Test_LifecycleContext_Struct* setupStruct = NitsContext()->_Test_LifecycleContext_Setup_Init->_Test_LifecycleContext_Struct;
    lifeContext->supportedTypesFromProv = MI_LIFECYCLE_INDICATION_ALL;

    // Test 1: No subscriptions and no callback
    LifeContext_UpdateSupportedTypes( lifeContext );
    NitsAssert( MI_FALSE == setupStruct->callbackCalled, PAL_T("Callback call not expected") );

    // Setup internal fake for provider callback function handler
    lifeContext->lifecycleCallback = &Local_MI_LifecycleIndicationCallback;
    lifeContext->callbackData = setupStruct;

    // Test 2: No subscriptions, but a callback
    LifeContext_UpdateSupportedTypes( lifeContext );
    NitsAssert( MI_FALSE == setupStruct->callbackCalled, PAL_T("Callback call not expected") );
}
NitsEndTest

NitsSetup1(Test_LifecycleContext_Setup_ForFtVerification, Test_LifecycleContext_Struct, Test_LifecycleContext_Setup, NitsEmptyValue)
{
    Test_LifecycleContext_Struct* tls = NitsContext()->_Test_LifecycleContext_Struct;
    Provider* provider = &(tls->provider);
    LifecycleContext* lifeCtx = NULL;

    //
    // Initialize unsubscribe handler
    // single threaded platform require that unsubsribe happen on a separate thread
    //
    RequestHandler_Init(&g_requesthandler);

    _Initialize_ProviderStruct( tls );

    NitsAssertOrReturn(MI_RESULT_OK == Test_Provider_Init( provider ), PAL_T("Failed to initialize subscription manager") );

    // LifecycleContext initialization
    ((SubscriptionManager*)provider->subMgr)->lifecycleCtx = LifeContext_New( );
    lifeCtx = ((SubscriptionManager*)provider->subMgr)->lifecycleCtx;
    NitsAssertOrReturn(NULL != ((SubscriptionManager*)provider->subMgr)->lifecycleCtx, PAL_T("Failed to allocate LifecycleContext*"));

    LifeContext_Init( lifeCtx, provider );
    NitsAssertOrReturn(lifeCtx->provider == provider, PAL_T("LifeContext_Init failed") );

    // Setup internal fake for provider callback function handler
    lifeCtx->lifecycleCallback = &Local_MI_LifecycleIndicationCallback;
    lifeCtx->callbackData = &(NitsContext()->_Test_LifecycleContext_Struct);

    // Create a subscription to verify handling of Post calls
    tls->msg = SubscribeReq_New( 0, 0 );
    SubscribeReq* msg = tls->msg;

    msg->targetType = SUBSCRIP_TARGET_LIFECYCLE_ALL;
    msg->filter = filterForPostTest;
    msg->language = languageWql;

    _InitializeTestLifeCtxSemaphore();

    // Strand initialization
    Strand_Init( STRAND_DEBUG(test_LifecycleContext_Strand) &tls->leftSideStrand, &TestLifecycleContext_InteractionFT, 0, NULL );
    // Simulate opening with message mode 
    tls->leftSideStrand.info.opened = MI_TRUE;
    tls->leftSideStrand.info.thisAckPending = MI_TRUE;

    InteractionOpenParams params;

    InteractionOpenParams_Init(&params);
    params.interaction = &tls->leftSideStrand.info.interaction;
    params.msg = &msg->base.base;

    // Add subscription
    CreateAndAddSubscriptionHelper(
        provider->subMgr,
        provider,
        &params,
        &(tls->context));
        
    SubMgr_SetEnabled(provider->subMgr, MI_TRUE);

    MI_Instance* srcInst = &(tls->sourceInstance.__instance);
    if (NitsAssert( MI_RESULT_OK == Instance_Construct( srcInst, &CIM_InstCreation_rtti, NULL ), PAL_T("Unable to create instance") ))
    {
        /* MI_ConstStringField IndicationIdentifier */
        MI_Value value;
        value.string = (MI_Char*)PAL_T("DummyInstanceCreatedForEaseOfTesting");
        NitsAssert( MI_RESULT_OK == MI_Instance_SetElement( srcInst, PAL_T("IndicationIdentifier"), &value, MI_STRING, 0 ), PAL_T("Unable to set identifier") );
    }

    // Set global variables
    indicationPosted = MI_FALSE;
    tls->callbackCalled = MI_FALSE;
}
NitsEndSetup

NitsCleanup(Test_LifecycleContext_Setup_ForFtVerification)
{
    Test_LifecycleContext_Struct* setupStruct = NitsContext()->_Test_LifecycleContext_Struct;

    // Reset global variables
    indicationPosted = MI_FALSE;
    setupStruct->callbackCalled = MI_FALSE;

    // Clean up subscriptions to avoid a memory leak
    setupStruct->provider.refusedUnload = MI_TRUE;  // Prevents Provider_Release from releasing
    Provider_TerminateIndication( &setupStruct->provider, MI_RESULT_FAILED, NULL, NULL );

    _CleanupTestLifeCtxSemaphore();

    if (setupStruct->sourceInstance.__instance.ft)
    {
        MI_Instance_Destruct( &setupStruct->sourceInstance.__instance );
    }

    //
    // Wait for the unsubscribe handler to complete.
    // Single threaded platform require that unsubsribe happen on a separate thread
    // wait for that thread to finish the unsubscribe call
    //
    while ( Atomic_Read( &g_requesthandler.running ) == 1 )
    {
        Sleep_Milliseconds( 10 );
    }
    RequestHandler_Finalize(&g_requesthandler);

    if (setupStruct->msg)
    {
        SubscribeReq_Release( setupStruct->msg );
    }

    Test_Provider_Finalize( &setupStruct->provider );
}
NitsEndCleanup

//
// Happy path: use PostCreate to post an indication to a subscription
//
NitsTest1(Test_LifecycleContext_PostCreate, Test_LifecycleContext_Setup_ForFtVerification, filterStruct)
{
    NitsDisableFaultSim;

    Test_LifecycleContext_Struct* setupStruct = NitsContext()->_Test_LifecycleContext_Setup_ForFtVerification->_Test_LifecycleContext_Struct;
    MI_Instance* srcInst = &(setupStruct->sourceInstance.__instance);
    LifecycleContext* lifeCtx = setupStruct->provider.subMgr->lifecycleCtx;

    NitsAssert( MI_RESULT_OK == MI_LifecycleIndicationContext_PostCreate( (MI_LifecycleIndicationContext*)lifeCtx, srcInst ), PAL_T("Expected Post success") );

    NitsAssert( MI_TRUE == indicationPosted, PAL_T("expected call to faked PostIndication") );
}
NitsEndTest

//
// Happy path: use PostModify to post an indication to a subscription
//
NitsTest1(Test_LifecycleContext_PostModify, Test_LifecycleContext_Setup_ForFtVerification, filterStruct)
{
    NitsDisableFaultSim;

    Test_LifecycleContext_Struct* setupStruct = NitsContext()->_Test_LifecycleContext_Setup_ForFtVerification->_Test_LifecycleContext_Struct;
    MI_Instance* srcInst = &(setupStruct->sourceInstance.__instance);
    LifecycleContext* lifeCtx = setupStruct->provider.subMgr->lifecycleCtx;

    NitsAssert( MI_RESULT_OK == MI_LifecycleIndicationContext_PostModify( (MI_LifecycleIndicationContext*)lifeCtx, srcInst, srcInst ), PAL_T("Expected Post success") );

    NitsAssert( MI_TRUE == indicationPosted, PAL_T("expected call to faked PostIndication") );
}
NitsEndTest

//
// Happy path: use PostDelete to post an indication to a subscription
//
NitsTest1(Test_LifecycleContext_PostDelete, Test_LifecycleContext_Setup_ForFtVerification, filterStruct)
{
    NitsDisableFaultSim;

    Test_LifecycleContext_Struct* setupStruct = NitsContext()->_Test_LifecycleContext_Setup_ForFtVerification->_Test_LifecycleContext_Struct;
    MI_Instance* srcInst = &(setupStruct->sourceInstance.__instance);
    LifecycleContext* lifeCtx = setupStruct->provider.subMgr->lifecycleCtx;

    NitsAssert( MI_RESULT_OK == MI_LifecycleIndicationContext_PostDelete( (MI_LifecycleIndicationContext*)lifeCtx, srcInst ), PAL_T("Expected Post success") );

    NitsAssert( MI_TRUE == indicationPosted, PAL_T("expected call to faked PostIndication") );
}
NitsEndTest

//
// Happy path: use PostRead to post an indication to a subscription
//
NitsTest1(Test_LifecycleContext_PostRead, Test_LifecycleContext_Setup_ForFtVerification, filterStruct)
{
    NitsDisableFaultSim;

    Test_LifecycleContext_Struct* setupStruct = NitsContext()->_Test_LifecycleContext_Setup_ForFtVerification->_Test_LifecycleContext_Struct;
    MI_Instance* srcInst = &(setupStruct->sourceInstance.__instance);
    LifecycleContext* lifeCtx = setupStruct->provider.subMgr->lifecycleCtx;

    NitsAssert( MI_RESULT_OK == MI_LifecycleIndicationContext_PostRead( (MI_LifecycleIndicationContext*)lifeCtx, srcInst ), PAL_T("Expected Post success") );

    NitsAssert( MI_TRUE == indicationPosted, PAL_T("expected call to faked PostIndication") );
}
NitsEndTest

//
// Happy path: use PostMethodCall to post an indication to a subscription
//
NitsTest1(Test_LifecycleContext_PostMethodCall, Test_LifecycleContext_Setup_ForFtVerification, filterStruct)
{
    NitsDisableFaultSim;

    Test_LifecycleContext_Struct* setupStruct = NitsContext()->_Test_LifecycleContext_Setup_ForFtVerification->_Test_LifecycleContext_Struct;
    MI_Instance* srcInst = &(setupStruct->sourceInstance.__instance);
    LifecycleContext* lifeCtx = setupStruct->provider.subMgr->lifecycleCtx;

    NitsAssert( MI_RESULT_OK == MI_LifecycleIndicationContext_PostMethodCall_Before( (MI_LifecycleIndicationContext*)lifeCtx, srcInst, MI_T("SomeMethodName"), NULL), PAL_T("Expected Post success") );

    NitsAssert( MI_TRUE == indicationPosted, PAL_T("expected call to faked PostIndication") );
}
NitsEndTest

// ft._PostResult
NitsTest1(Test_LifecycleContext_PostResult, Test_LifecycleContext_Setup_ForFtVerification, filterStruct)
{
    NitsDisableFaultSim;

    Test_LifecycleContext_Struct* setupStruct = NitsContext()->_Test_LifecycleContext_Setup_ForFtVerification->_Test_LifecycleContext_Struct;
    LifecycleContext* lifeCtx = setupStruct->provider.subMgr->lifecycleCtx;

    // Additional setup to avoid release issues.
    setupStruct->provider.refusedUnload = MI_TRUE;  // Prevents Provider_Release from releasing

    NitsAssert( MI_RESULT_OK == MI_LifecycleIndicationContext_PostResult( (MI_LifecycleIndicationContext*)lifeCtx, MI_RESULT_OK ), PAL_T("Expected Post success") );

    NitsAssert( MI_FALSE == SubMgr_IsEnabled(setupStruct->provider.subMgr), PAL_T("Expected disabling of indications") );
}
NitsEndTest

// ft._SetSupportedTypes
// ft._GetLifecycleIndicationTypes
NitsTest1(Test_LifecycleContext_SetAndGetSupportedTypes, Test_LifecycleContext_Setup_Init, filterStruct)
{
    MI_Uint32 typesFromContext = MI_LIFECYCLE_INDICATION_NONE;

    NitsAssert( MI_RESULT_OK == MI_LifecycleIndicationContext_SetSupportedTypes( (MI_LifecycleIndicationContext*)lifeContext, MI_LIFECYCLE_INDICATION_CREATE), PAL_T("Expected SetSupportedTypes success") );
    NitsAssert( MI_RESULT_OK == MI_LifecycleIndicationContext_GetTypes( (MI_LifecycleIndicationContext*)lifeContext, &typesFromContext), PAL_T("Expected GetSupportedTypes success") );
    NitsAssert( MI_LIFECYCLE_INDICATION_CREATE == typesFromContext, PAL_T("Incorrect supportedTypes") );
}
NitsEndTest

// ft._RegisterLifecycleCallback
NitsTest1(Test_LifecycleContext_RegisterLifecycleCallback, Test_LifecycleContext_Setup_Init, filterStruct)
{
    MI_Uint32 data = 0x12345678;
    NitsAssert( MI_RESULT_OK == MI_LifecycleIndicationContext_RegisterCallback( (MI_LifecycleIndicationContext*)lifeContext, &Local_MI_LifecycleIndicationCallback, &data), PAL_T("Expected RegisterLifecycleCallback success") );
    NitsAssert( &Local_MI_LifecycleIndicationCallback == lifeContext->lifecycleCallback, PAL_T("Incorrect callback address") );
    NitsAssert( &data == lifeContext->callbackData, PAL_T("Incorrect callback data") );
}
NitsEndTest

//
// Test factories methods of MI_LifecycleIndicationContextFT 
//
MI_EXTERN_C MI_CONST MI_ClassDecl XYZ_Test_rtti;
MI_EXTERN_C MI_CONST MI_MethodDecl XYZ_Test_Create_rtti;

NitsTest1(Test_LifecycleContext_FactoryMethods, Test_LifecycleContext_Setup_Init, filterStruct)
{
    XYZ_Test x;
    MI_LifecycleIndicationContext* lic = (MI_LifecycleIndicationContext*)lifeContext;
    MI_Result r;
    r = MI_LifecycleIndicationContext_ConstructInstance( lic, &XYZ_Test_rtti, &x.__instance);
    NitsAssertOrReturn( MI_RESULT_OK == r, PAL_T("Expected ConstructInstance success"));
    r = XYZ_Test_Destruct(&x);
    NitsAssertOrReturn( MI_RESULT_OK == r, PAL_T("Expected XYZ_Test_Destruct success"));

    XYZ_Test_Create param;
    r = MI_LifecycleIndicationContext_ConstructParameters( lic, &XYZ_Test_Create_rtti, &param.__instance);
    NitsAssertOrReturn( MI_RESULT_OK == r, PAL_T("Expected ConstructParameters success"));
    r = MI_Instance_Destruct(&param.__instance);
    NitsAssertOrReturn( MI_RESULT_OK == r, PAL_T("Expected MI_Instance_Destruct success"));

    MI_Instance* instanceptr;
    r = MI_LifecycleIndicationContext_NewInstance( lic, &XYZ_Test_rtti, &instanceptr);
    NitsAssertOrReturn( MI_RESULT_OK == r, PAL_T("Expected NewInstance success"));
    r = MI_Instance_Delete(instanceptr);
    NitsAssertOrReturn( MI_RESULT_OK == r, PAL_T("Expected MI_Instance_Delete success"));

    r = MI_LifecycleIndicationContext_NewDynamicInstance( lic, MI_T("XYZ_Test"), 0, &instanceptr);
    NitsAssertOrReturn( MI_RESULT_OK == r, PAL_T("Expected NewDynamicInstance success"));
    r = MI_Instance_Delete(instanceptr);
    NitsAssertOrReturn( MI_RESULT_OK == r, PAL_T("Expected MI_Instance_Delete success"));

    r = MI_LifecycleIndicationContext_NewParameters( lic, &XYZ_Test_Create_rtti, &instanceptr);
    NitsAssertOrReturn( MI_RESULT_OK == r, PAL_T("Expected NewParameters success"));
    r = MI_Instance_Delete(instanceptr);
    NitsAssertOrReturn( MI_RESULT_OK == r, PAL_T("Expected MI_Instance_Delete success"));
}
NitsEndTest

