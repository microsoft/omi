/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <ut/ut.h>
#include <provmgr/SubscriptionContext.h>
#include <provmgr/AggregationContext.h>
#include <provmgr/SubMgr.h>
#include <pal/strings.h>
#include "StrandHelper.h"
#include <provmgr/CIM_InstCreation.h>
#include <provmgr/indicationSchema.h>
#include <provmgr/provmgr.h>
#include <sock/selector.h>
#include <pal/sleep.h>
#include <pal/sem.h>
#include "StrandHelper.h"

using namespace std;

struct TestContext_Struct
{
    SubscribeReq *req;
    Context context;
    SubscriptionContext* subContext;
    AggregationContext aggrContext;
    Provider provider;
    Strand leftSideStrand;
    SubMgrSubscription dummySubscription;
    CIM_InstCreation instCreation;
    Library library;
    ProvMgr provMgr;

    Sem semFinalMessagePosted;
};

TestContext_Struct genericContextTemplate = { 0 };

typedef enum _ShutdownState
{
    ShutdownState_None = 0,
    ShutdownState_Released
}
ShutdownState;

int sleepTimeInMs = 5;
volatile ShutdownState disableState = ShutdownState_None;

void MI_CALL __Unload(
    _In_opt_ void* self,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL __DisableIndications(
    _In_opt_ void* self,
    _In_ MI_Context* indicationsContext,
    _In_z_ const MI_Char* nameSpace,
    _In_z_ const MI_Char* className)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_Context_PostResult(indicationsContext, MI_RESULT_OK);
    disableState = ShutdownState_Released;
}

MI_CONST MI_ProviderFT g_pft =
{
    NULL, //MI_ProviderFT_Load Load;
    __Unload, //MI_ProviderFT_Unload Unload;
    NULL, //MI_ProviderFT_GetInstance GetInstance;
    NULL, //MI_ProviderFT_EnumerateInstances EnumerateInstances;
    NULL, //MI_ProviderFT_CreateInstance CreateInstance;
    NULL, //MI_ProviderFT_ModifyInstance ModifyInstance;
    NULL, //MI_ProviderFT_DeleteInstance DeleteInstance;
    NULL, //MI_ProviderFT_AssociatorInstances AssociatorInstances;
    NULL, //MI_ProviderFT_ReferenceInstances ReferenceInstances;
    NULL, //MI_ProviderFT_EnableIndications EnableIndications;
    __DisableIndications, //MI_ProviderFT_DisableIndications DisableIndications;
    NULL, //MI_ProviderFT_Subscribe Subscribe;
    NULL, //MI_ProviderFT_Unsubscribe Unsubscribe;
    NULL //MI_ProviderFT_Invoke Invoke;
};

MI_ClassDecl g_cdTest;

STRAND_DEBUGNAME( test_Context_Strand );

NitsSetup0(TestContext_SetupProvider, TestContext_Struct)
{
    // SubscriptionContext initialization
    NitsContext()->_TestContext_Struct->subContext = NULL;

    NitsDisableFaultSim;

    // Strand initialization
    Strand_Init( STRAND_DEBUG(test_Context_Strand) &NitsContext()->_TestContext_Struct->leftSideStrand, &ContextTest_Left_InteractionFT, 0, NULL );
    // Simulate opening with message mode
    NitsContext()->_TestContext_Struct->leftSideStrand.info.opened = MI_TRUE;
    NitsContext()->_TestContext_Struct->leftSideStrand.info.thisAckPending = MI_TRUE;

    // Provider initialization
    memset( &NitsContext()->_TestContext_Struct->provider, 0, sizeof(Provider) );
    NitsContext()->_TestContext_Struct->provider.refusedUnload = MI_TRUE;  /* Done to prevent de-referencing a NULL lib ptr */
}
NitsEndSetup

NitsCleanup(TestContext_SetupProvider)
{
}
NitsEndCleanup

NitsTest1(TestContext_InitAndClose, TestContext_SetupProvider, genericContextTemplate)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_SetupProvider->_TestContext_Struct;

    NitsAssert( MI_RESULT_OK == Context_Init( &setupStruct->context, NULL, &setupStruct->provider, NULL ), PAL_T("Init failed") );
    NitsAssert( NULL != setupStruct->context.base.ft, PAL_T("Context not initialized") );
    NitsAssert( 1 == setupStruct->provider.refCounter, PAL_T("Expected provider refCount increment in Init") );

    Context_Close( &setupStruct->context );
    NitsAssert( 0 == setupStruct->provider.refCounter, PAL_T("Provider refCount not reset") );
    NitsAssert( 0xFFFFFFFF == setupStruct->context.magic, PAL_T("Expected overwrite of Context struct") );
}
NitsEndTest

NitsTest1(TestContext_IndPostInstance, TestContext_SetupProvider, genericContextTemplate)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_SetupProvider->_TestContext_Struct;

    MI_Instance nullInstance;
    memset( &nullInstance, 0, sizeof(MI_Instance) );

    // Same code works for lifecycle, subscription, and aggregation, so it is OK to just use subscription here.
    NitsAssert( MI_RESULT_OK == Context_Init_ByType( &setupStruct->context, &setupStruct->provider, NULL, CTX_TYPE_IND_SUBSCRIPTION ), PAL_T("Init failed") );
    NitsAssert( NULL != setupStruct->context.base.ft, PAL_T("Context not initialized") );

    // Case 1: NULL context, bad magic, NULL instance -> invalid param
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_Context_PostInstance( &(setupStruct->context.base), NULL ), PAL_T("NULL indication") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_Context_PostInstance( NULL, &nullInstance ), PAL_T("NULL context") );
    MI_Uint32 existingMagic = setupStruct->context.magic;
    setupStruct->context.magic = 0x12345678; // Invalid value
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_Context_PostInstance( &(setupStruct->context.base), &nullInstance ), PAL_T("Invalid magic number failure expected") );
    setupStruct->context.magic = existingMagic;

    // Case 2: All other uses are not supported
    NitsAssert( MI_RESULT_NOT_SUPPORTED == MI_Context_PostInstance( &(setupStruct->context.base), &nullInstance ), PAL_T("Not supported for non-indication contexts") );

    Context_Close( &setupStruct->context );
}
NitsEndTest

NitsTest1(TestContext_IndPostIndication_GenericFailures, TestContext_SetupProvider, genericContextTemplate)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_SetupProvider->_TestContext_Struct;

    MI_Instance nullInstance;
    memset( &nullInstance, 0, sizeof(MI_Instance) );

    // Case 1: Base case to establish that indications are not processed on regular contexts
    NitsAssert( MI_RESULT_OK == Context_Init_ByType( &setupStruct->context, &setupStruct->provider, NULL, CTX_TYPE_SINGLE_ITEM ), PAL_T("Init failed") );
    NitsAssert( NULL != setupStruct->context.base.ft, PAL_T("Context not initialized") );
    NitsAssert( MI_RESULT_NOT_SUPPORTED == MI_Context_PostIndication( &(setupStruct->context.base), &nullInstance, 0, NULL), PAL_T("Not supported for non-indication contexts") );
    Context_Close( &setupStruct->context );

    // Same code works for lifecycle, subscription, and aggregation, so it is OK to just use subscription here.
    NitsAssert( MI_RESULT_OK == Context_Init_ByType( &setupStruct->context, &setupStruct->provider, NULL, CTX_TYPE_IND_SUBSCRIPTION ), PAL_T("Init failed") );
    NitsAssert( NULL != setupStruct->context.base.ft, PAL_T("Context not initialized") );

    // Case 2: NULL context, bad magic, NULL instance -> invalid param
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_Context_PostIndication( &(setupStruct->context.base), NULL, 0, NULL), PAL_T("NULL indication") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_Context_PostIndication( NULL, &nullInstance, 0, NULL), PAL_T("NULL context") );
    MI_Uint32 existingMagic = setupStruct->context.magic;
    setupStruct->context.magic = 0x12345678; // Invalid value
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_Context_PostIndication( &(setupStruct->context.base), &nullInstance, 0, NULL), PAL_T("Invalid magic number failure expected") );
    setupStruct->context.magic = existingMagic;

    // Case 3: Cancelled makes it a NO-OP
    setupStruct->context.cancelled = MI_TRUE;
    NitsAssert( MI_RESULT_OK == MI_Context_PostIndication( &(setupStruct->context.base), &nullInstance, 0, NULL), PAL_T("Context cancelled") );
    setupStruct->context.cancelled = MI_FALSE;

    // Case 4: Invalid context type (manually set to unknown value)
    Context_Type existingType = setupStruct->context.ctxType;
    setupStruct->context.ctxType = CTX_TYPE_INVOKE_WITH_INSTANCE; // Invalid value
    NitsAssert( MI_RESULT_NOT_FOUND == MI_Context_PostIndication( &(setupStruct->context.base), &nullInstance, 0, NULL), PAL_T("Invalid context type") );
    setupStruct->context.ctxType = existingType;

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 6001) // OACR complains this context was invalid due to previous Context_Close, but it get re-initialized again by Context_Init_ByType
#endif
    Context_Close( &setupStruct->context );
#ifdef _PREFAST_
#pragma prefast (pop)
#endif
}
NitsEndTest

//
// Create a generic CIM_Error instance for use with PostCimError
//
MI_Result _CreateCimError(
    MI_Context* context,
    MI_Instance** errorInstance )
{
    if ( ! context ||
         ! errorInstance )
    {
        return MI_RESULT_FAILED;
    }

    NitsAssert( MI_RESULT_OK == MI_Context_NewDynamicInstance( context, MI_T("CIM_Error"), 0, errorInstance), PAL_T("Failed to create CIM_Error instance") );
    if ( ! NitsAssert( NULL != *errorInstance, PAL_T("No CIM_Error instance created") ) )
    {
        return MI_RESULT_FAILED;
    }

    MI_Value value;
    value.uint32 = 1;
    NitsAssert( MI_RESULT_OK == MI_Instance_AddElement( *errorInstance, MI_T("CIMStatusCode"), &value, MI_UINT32, 0 ), PAL_T("Failed to set CIMStatusCode on CIM_Error") );

    value.string = (MI_Char*)MI_T("ErrorString");
    NitsAssert( MI_RESULT_OK == MI_Instance_AddElement( *errorInstance, MI_T("Message"), &value, MI_STRING, 0 ), PAL_T("Failed to set Message on CIM_Error") );

    return MI_RESULT_OK;
}

NitsTest1(TestContext_IndPost_ResultErrorCimError_Errors, TestContext_SetupProvider, genericContextTemplate)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_SetupProvider->_TestContext_Struct;

    MI_Instance* errorInstance = NULL;

    // Same code works for lifecycle, subscription, and aggregation, so it is OK to just use subscription here.
    NitsAssert( MI_RESULT_OK == Context_Init_ByType( &setupStruct->context, &setupStruct->provider, NULL, CTX_TYPE_IND_SUBSCRIPTION ), PAL_T("Init failed") );
    NitsAssert( NULL != setupStruct->context.base.ft, PAL_T("Context not initialized") );

    NitsAssert( MI_RESULT_OK == _CreateCimError( &setupStruct->context.base, &errorInstance ), PAL_T("Failed to create CIM_Error") );

    // Case 1: NULL context OR bad magic -> invalid param
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_Context_PostResult( NULL, MI_RESULT_OK ), PAL_T("NULL context") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_Context_PostError( NULL, MI_RESULT_OK, MI_T("MI"), NULL ), PAL_T("NULL context") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_Context_PostCimError( NULL, errorInstance ), PAL_T("NULL context") );

    MI_Uint32 existingMagic = setupStruct->context.magic;
    setupStruct->context.magic = 0x12345678; // Invalid value
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_Context_PostResult( &(setupStruct->context.base), MI_RESULT_OK), PAL_T("Invalid magic number failure expected") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_Context_PostError( &(setupStruct->context.base), MI_RESULT_OK, MI_T("MI"), NULL), PAL_T("Invalid magic number failure expected") );
    NitsAssert( MI_RESULT_INVALID_PARAMETER == MI_Context_PostCimError( &(setupStruct->context.base), errorInstance ), PAL_T("NULL context") );
    setupStruct->context.magic = existingMagic;

    // Case 2: Cancelled makes it a NO-OP
    setupStruct->context.cancelled = MI_TRUE;
    NitsAssert( MI_RESULT_OK == MI_Context_PostResult( &(setupStruct->context.base), MI_RESULT_INVALID_CLASS), PAL_T("Context cancelled") );
    NitsAssert( MI_RESULT_OK == MI_Context_PostError( &(setupStruct->context.base), MI_RESULT_INVALID_CLASS, MI_T("MI"), NULL), PAL_T("Context cancelled") );
    NitsAssert( MI_RESULT_OK == MI_Context_PostCimError( &(setupStruct->context.base), errorInstance ), PAL_T("NULL context") );
    setupStruct->context.cancelled = MI_FALSE;

    // Case 3: Invalid context types (manually set to unknown value)
    Context_Type existingType = setupStruct->context.ctxType;
    setupStruct->context.ctxType = CTX_TYPE_INVOKE_WITH_INSTANCE; // Invalid value
    NitsAssert( MI_RESULT_NOT_FOUND == MI_Context_PostResult( &(setupStruct->context.base), MI_RESULT_OK), PAL_T("Invalid context type") );
    NitsAssert( MI_RESULT_NOT_FOUND == MI_Context_PostError( &(setupStruct->context.base), MI_RESULT_OK, MI_T("MI"), NULL), PAL_T("Invalid context type") );
    NitsAssert( MI_RESULT_NOT_FOUND == MI_Context_PostCimError( &(setupStruct->context.base), errorInstance ), PAL_T("NULL context") );
    setupStruct->context.ctxType = existingType;

    if (errorInstance)
    {
        NitsAssert( MI_RESULT_OK == MI_Instance_Delete( errorInstance ), PAL_T("Unable to clean up errorInstance") );
    }
    Context_Close( &setupStruct->context );
}
NitsEndTest

//
// Return an Ack to caller.  No other processing is required since this is
// designed to simulate reception and processing of a message.
//
static const size_t TEST_CTX_ERROR_STRING_SIZE = 64;
struct ReceivedMessage
{
    MI_Boolean isReceived;
    MI_Result result;
    MI_Char errorStr[TEST_CTX_ERROR_STRING_SIZE];
    MI_Instance* cimError;
    MI_Uint32 indicationCount;
};

static ReceivedMessage latestMessage = { 0 };
static Sem* g_sem;

static void _ClearReceivedMessage()
{
    if (latestMessage.cimError)
    {
        NitsAssert( MI_RESULT_OK == MI_Instance_Delete( latestMessage.cimError ), PAL_T("Unable to release cloned CIM_Error") );
    }
    memset( &latestMessage, 0, sizeof(ReceivedMessage) );
}

NITS_EXTERN_C void ContextTest_Post_CheckedAck( _In_ Strand* self_, _In_ Message* msg)
{
    latestMessage.isReceived = MI_TRUE;

    if (PostResultMsgTag == msg->tag)
    {
        PostResultMsg* msgAsPostResult = (PostResultMsg*)msg;

        latestMessage.result = msgAsPostResult->result;

        if (msgAsPostResult->errorMessage)
        {
            size_t msgStrSize = Tcslen(msgAsPostResult->errorMessage) + 1;  // Include '\0'
            size_t sizeToCopy = (msgStrSize > TEST_CTX_ERROR_STRING_SIZE ? TEST_CTX_ERROR_STRING_SIZE : msgStrSize );
            Tcslcpy( latestMessage.errorStr, msgAsPostResult->errorMessage, sizeToCopy );
        }

        if (msgAsPostResult->cimError)
        {
            NitsAssert( MI_RESULT_OK == MI_Instance_Clone( msgAsPostResult->cimError, &latestMessage.cimError ), PAL_T("Unable to clone instance") );
        }
    }
    else if (PostIndicationMsgTag == msg->tag)
    {
        latestMessage.indicationCount++;
    }
    Strand_Ack(self_);

    if (PostResultMsgTag == msg->tag)
    {
        /* close self upon receiving final message, it will close the other side stand */
        Strand_Close(self_);

        DEBUG_ASSERT( g_sem );
        Sem_Post( g_sem, 1 );
    }
}

static StrandFT ContextTest_Left_CheckedInteractionFT =
{
    ContextTest_Post_CheckedAck,
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

/*****************************************************************************
 *
 * SubscriptionContext Post* Handling Tests
 *
 *****************************************************************************/
STRAND_DEBUGNAME( test_Context_SubscrContext_Strand );

NitsSetup0(TestContext_SubscrContext_Setup, TestContext_Struct)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_Struct;
    setupStruct->req = NULL;

    // SubMgrSubscription
    memset( &setupStruct->dummySubscription, 0, sizeof(SubMgrSubscription) );
    setupStruct->dummySubscription.subscriptionID = 1;
    setupStruct->dummySubscription.state = SubscriptionState_Subscribed;
    setupStruct->provider.subMgr = SubMgr_New();
    NitsAssertOrReturn(setupStruct->provider.subMgr != NULL, PAL_T("create subscribe manager failed"));
    SubMgr_Init(setupStruct->provider.subMgr, &setupStruct->provider);

    NitsDisableFaultSim;

    // Strand initialization
    memset( &setupStruct->leftSideStrand, 0, sizeof(Strand) );
    Strand_Init( STRAND_DEBUG(test_Context_SubscrContext_Strand) &setupStruct->leftSideStrand, &ContextTest_Left_CheckedInteractionFT, 0, NULL );
    // Simulate opening with message mode
    setupStruct->leftSideStrand.info.opened = MI_TRUE;
    setupStruct->leftSideStrand.info.thisAckPending = MI_TRUE;

    //
    // Create request msg
    //
    setupStruct->req = SubscribeReq_New(1, 0);
    NitsAssertOrReturn(setupStruct->req != NULL, PAL_T("create SubscribeReq message failed"));
    setupStruct->req->targetType = SUBSCRIP_TARGET_DEFAULT;
    setupStruct->req->filter = MI_T("select * from test_class");
    setupStruct->req->language = MI_QUERY_DIALECT_CQL;
    setupStruct->req->bookmark = NULL;

    NitsAssert( MI_RESULT_OK == Context_Init( &setupStruct->context, NULL, &setupStruct->provider, NULL ), PAL_T("Context init failed") );
    NitsAssertOrReturn( NULL != setupStruct->context.base.ft, PAL_T("Context not initialized") );

    memcpy( &g_cdTest, &CIM_InstCreation_rtti, sizeof(MI_ClassDecl));
    g_cdTest.providerFT = &g_pft;
    setupStruct->provider.classDecl = &g_cdTest; /* Default value so it has a class name */
    setupStruct->provider.refusedUnload = MI_TRUE;  /* Done to prevent de-referencing a NULL lib ptr */
    setupStruct->provider.lib = &setupStruct->library;
    setupStruct->provider.lib->provmgr = &setupStruct->provMgr;

    disableState = ShutdownState_None;

    Sem_Init( &setupStruct->semFinalMessagePosted, SEM_USER_ACCESS_DEFAULT, 0 );
    g_sem = &setupStruct->semFinalMessagePosted;
}
NitsEndSetup

NitsCleanup(TestContext_SubscrContext_Setup)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_Struct;

    if (setupStruct->provider.subMgr)
    {
        SubscriptionManager* submgr = setupStruct->provider.subMgr;
        SubMgr_CancelAllSubscriptions( submgr, MI_RESULT_FAILED, NULL, NULL );
        SubMgr_Delete( submgr );
    }

    if (setupStruct->req)
    {
        NitsCompare(1, (size_t)setupStruct->req->base.base.refCounter, PAL_T("RefCount of request message is wrong. Leak memory"));
        SubscribeReq_Release(setupStruct->req);
    }

    if (NULL != setupStruct->context.base.ft)
    {
        Context_Close( &setupStruct->context );
    }
    disableState = ShutdownState_None;

    Sem_Destroy( &setupStruct->semFinalMessagePosted );
    g_sem = NULL;
}
NitsEndCleanup

void _CallPostResult_SubCtx(
    TestContext_Struct* setupStruct,
    SubscriptionState stateToUse,
    MI_Result resultToPass,
    MI_Result expectedResult )
{
    ((SubMgrSubscription*)setupStruct->subContext->subscription)->state = stateToUse;
    NitsAssert( expectedResult == MI_Context_PostResult(
        &setupStruct->subContext->baseCtx.base,
        resultToPass ), PAL_T("PostResult unexpected result") );
}

void TestContext_IndPostResult_SubscriptionContext_Helper(
    _In_ TestContext_Struct* setupStruct,
    _In_ SubscriptionState state,
    _In_ MI_Result result,
    _In_ MI_Result postresult)
{
    InteractionOpenParams params;
    SubscriptionManager* subMgr = setupStruct->provider.subMgr;

    InteractionOpenParams_Init(&params);
    params.interaction = &setupStruct->leftSideStrand.info.interaction;
    params.msg = &setupStruct->req->base.base;

    //
    // SubMgr_CreateSubscription:One refcount of subscription will be release in CONTEXT_STRANDAUX_INVOKESUBSCRIBE,
    // however we are not invoking CONTEXT_STRANDAUX_INVOKESUBSCRIBE, so the refcount should be released explictly
    //
    MI_Result r = CreateAndAddSubscriptionHelper(
        subMgr,
        &setupStruct->provider,
        &params,
        &setupStruct->subContext);

    if (r != MI_RESULT_OK)
        return;

    // Overwrite the strand FT to prevent the message from getting sent out
    setupStruct->subContext->baseCtx.strand.info.userFT = &ContextTest_Right_InteractionFT;

    SubMgrSubscription* sub = setupStruct->subContext->subscription;

    SubMgr_SetEnabled( subMgr, MI_TRUE );
    SubMgr_SetTerminating( subMgr, MI_FALSE );
    SubMgr_SetAllCancelledSafe( subMgr, MI_FALSE );

    AggregationContext *ac = SubMgr_CreateAggrContext( subMgr );
    NitsAssert( ac != NULL, PAL_T("Init failed") );
    if ( ac == NULL )
    {
        SubMgr_DeleteSubscription(subMgr, sub);
        return;
    }

    _CallPostResult_SubCtx( setupStruct, state, result, postresult );

    // Waits for asynchronous Disable thread to complete
    while (ShutdownState_Released != disableState)
    {
        Sleep_Milliseconds(sleepTimeInMs);
        if (ShutdownState_Released == disableState)
        {
            break; // jump out because the first execution of the timeout already finished.
        }
    }

    // Verify message received
    NitsAssert( MI_TRUE == latestMessage.isReceived, PAL_T("Expected PostResult message from handler") );
    NitsAssert( result == latestMessage.result, PAL_T("Unexpected result message value") );
    _ClearReceivedMessage();
}

//
// _IndPostResult on SubscriptionContext
//
// Case 1: PostResult OK on all subscription states
//
NitsTest1(TestContext_IndPostResult_SubscriptionContext_OK_NotInitialized, TestContext_SubscrContext_Setup, genericContextTemplate)
{
    TestContext_IndPostResult_SubscriptionContext_Helper(
        NitsContext()->_TestContext_SubscrContext_Setup->_TestContext_Struct,
        SubscriptionState_NotInitialized,
        MI_RESULT_OK,
        MI_RESULT_OK);
}
NitsEndTest

NitsTest1(TestContext_IndPostResult_SubscriptionContext_OK_Initialized, TestContext_SubscrContext_Setup, genericContextTemplate)
{
    TestContext_IndPostResult_SubscriptionContext_Helper(
        NitsContext()->_TestContext_SubscrContext_Setup->_TestContext_Struct,
        SubscriptionState_Initialized,
        MI_RESULT_OK,
        MI_RESULT_OK);
}
NitsEndTest

NitsTest1(TestContext_IndPostResult_SubscriptionContext_OK_Subscribed, TestContext_SubscrContext_Setup, genericContextTemplate)
{
    TestContext_IndPostResult_SubscriptionContext_Helper(
        NitsContext()->_TestContext_SubscrContext_Setup->_TestContext_Struct,
        SubscriptionState_Subscribed,
        MI_RESULT_OK,
        MI_RESULT_OK);
}
NitsEndTest

NitsTest1(TestContext_IndPostResult_SubscriptionContext_OK_Unsubscribing, TestContext_SubscrContext_Setup, genericContextTemplate)
{
    TestContext_IndPostResult_SubscriptionContext_Helper(
        NitsContext()->_TestContext_SubscrContext_Setup->_TestContext_Struct,
        SubscriptionState_Unsubscribing,
        MI_RESULT_OK,
        MI_RESULT_OK);
}
NitsEndTest

NitsTest1(TestContext_IndPostResult_SubscriptionContext_OK_Unsubscribed, TestContext_SubscrContext_Setup, genericContextTemplate)
{
    TestContext_IndPostResult_SubscriptionContext_Helper(
        NitsContext()->_TestContext_SubscrContext_Setup->_TestContext_Struct,
        SubscriptionState_Unsubscribed,
        MI_RESULT_OK,
        MI_RESULT_OK);
}
NitsEndTest

// _IndPostResult on SubscriptionContext
//
// Case 2: PostResult NOT OK on all subscription states
//
NitsTest1(TestContext_IndPostResult_SubscriptionContext_FAIL_NotInitialized, TestContext_SubscrContext_Setup, genericContextTemplate)
{
    TestContext_IndPostResult_SubscriptionContext_Helper(
        NitsContext()->_TestContext_SubscrContext_Setup->_TestContext_Struct,
        SubscriptionState_NotInitialized,
        MI_RESULT_INVALID_CLASS,
        MI_RESULT_OK);

}
NitsEndTest

NitsTest1(TestContext_IndPostResult_SubscriptionContext_FAIL_Initialized, TestContext_SubscrContext_Setup, genericContextTemplate)
{
    TestContext_IndPostResult_SubscriptionContext_Helper(
        NitsContext()->_TestContext_SubscrContext_Setup->_TestContext_Struct,
        SubscriptionState_Initialized,
        MI_RESULT_INVALID_CLASS,
        MI_RESULT_OK);
}
NitsEndTest

NitsTest1(TestContext_IndPostResult_SubscriptionContext_FAIL_Subscribed, TestContext_SubscrContext_Setup, genericContextTemplate)
{
    TestContext_IndPostResult_SubscriptionContext_Helper(
        NitsContext()->_TestContext_SubscrContext_Setup->_TestContext_Struct,
        SubscriptionState_Subscribed,
        MI_RESULT_INVALID_CLASS,
        MI_RESULT_OK);
}
NitsEndTest

NitsTest1(TestContext_IndPostResult_SubscriptionContext_FAIL_Unsubscribing, TestContext_SubscrContext_Setup, genericContextTemplate)
{
    TestContext_IndPostResult_SubscriptionContext_Helper(
        NitsContext()->_TestContext_SubscrContext_Setup->_TestContext_Struct,
        SubscriptionState_Unsubscribing,
        MI_RESULT_INVALID_CLASS,
        MI_RESULT_OK);
}
NitsEndTest

NitsTest1(TestContext_IndPostResult_SubscriptionContext_FAIL_Unsubscribed, TestContext_SubscrContext_Setup, genericContextTemplate)
{
    TestContext_IndPostResult_SubscriptionContext_Helper(
        NitsContext()->_TestContext_SubscrContext_Setup->_TestContext_Struct,
        SubscriptionState_Unsubscribed,
        MI_RESULT_INVALID_CLASS,
        MI_RESULT_OK);
}
NitsEndTest

// _IndPostError on SubscriptionContext
//
// All error cases are common with PostResult except the incorrect type case here
//
void TestContext_IndPostError_SubscriptionContext_Helper(
    _In_ TestContext_Struct* setupStruct,
    _In_ SubscriptionState state,
    _In_ MI_Result result,
    _In_z_ const MI_Char* type,
    _In_z_ const MI_Char* errmsg)
{
    InteractionOpenParams params;
    SubscriptionManager* subMgr = setupStruct->provider.subMgr;

    InteractionOpenParams_Init(&params);
    params.interaction = &setupStruct->leftSideStrand.info.interaction;
    params.msg = &setupStruct->req->base.base;

    //
    // SubMgr_CreateSubscription:One refcount of subscription will be release in CONTEXT_STRANDAUX_INVOKESUBSCRIBE,
    // however we are not invoking CONTEXT_STRANDAUX_INVOKESUBSCRIBE, so the refcount should be released explictly
    //
    MI_Result r = CreateAndAddSubscriptionHelper(
        subMgr,
        &setupStruct->provider,
        &params,
        &setupStruct->subContext);

    if (r != MI_RESULT_OK)
        return;

    // Overwrite the strand FT to prevent the message from getting sent out
    setupStruct->subContext->baseCtx.strand.info.userFT = &ContextTest_Right_InteractionFT;

    SubMgrSubscription* sub = setupStruct->subContext->subscription;

    ((SubMgrSubscription*)setupStruct->subContext->subscription)->state = state;

    SubMgr_SetEnabled( subMgr, MI_TRUE );
    SubMgr_SetTerminating( subMgr, MI_FALSE );
    SubMgr_SetAllCancelledSafe( subMgr, MI_FALSE );

    AggregationContext *ac = SubMgr_CreateAggrContext( subMgr );
    NitsAssert( ac != NULL, PAL_T("Init failed") );
    if ( ac == NULL )
    {
        SubMgr_DeleteSubscription(subMgr, sub);
        return;
    }

    NitsAssert( MI_RESULT_OK == MI_Context_PostError(
        &setupStruct->subContext->baseCtx.base,
        result,
        type,
        errmsg),
        PAL_T("PostError unexpected result") );

    // Waits for asynchronous Disable thread to complete
    while (ShutdownState_Released != disableState)
    {
        Sleep_Milliseconds(sleepTimeInMs);
        if (ShutdownState_Released == disableState)
        {
            break; // jump out because the first execution of the timeout already finished.
        }
    }

    // Verify message received.  The result should be overwritten because of bad type
    NitsAssert( MI_TRUE == latestMessage.isReceived, PAL_T("Expected PostResult message from handler") );
    NitsAssert( MI_RESULT_FAILED == latestMessage.result, PAL_T("Unexpected result message value") );
    _ClearReceivedMessage();
}

NitsTest1(TestContext_IndPostError_SubscriptionContext_IncorrectType, TestContext_SubscrContext_Setup, genericContextTemplate)
{
    const MI_Char* type = (const MI_Char*) (void*)0;
    TestContext_IndPostError_SubscriptionContext_Helper(
        NitsContext()->_TestContext_SubscrContext_Setup->_TestContext_Struct,
        SubscriptionState_Unsubscribing,
        MI_RESULT_FAILED,
        type,
        PAL_T("ErrorStringForUser"));

}
NitsEndTest

// _IndPostError on SubscriptionContext
//
// All error cases are common with PostResult except the incorrect type case here
//
NitsTest1(TestContext_IndPostError_SubscriptionContext_OK, TestContext_SubscrContext_Setup, genericContextTemplate)
{
    TestContext_IndPostError_SubscriptionContext_Helper(
        NitsContext()->_TestContext_SubscrContext_Setup->_TestContext_Struct,
        SubscriptionState_Unsubscribing,
        MI_RESULT_FAILED,
        MI_RESULT_TYPE_MI,
        PAL_T("ErrorStringForUser"));
}
NitsEndTest


// _IndPostCimError on SubscriptionContext
// Helper
void TestContext_IndPostCimError_SubscriptionContext_Helper(
    _In_ TestContext_Struct* setupStruct,
    _In_ SubscriptionState state,
    _In_ MI_Instance* err,
    _In_ MI_Result expected)
{
    InteractionOpenParams params;
    SubscriptionManager* subMgr = setupStruct->provider.subMgr;

    InteractionOpenParams_Init(&params);
    params.interaction = &setupStruct->leftSideStrand.info.interaction;
    params.msg = &setupStruct->req->base.base;

    //
    // SubMgr_CreateSubscription:One refcount of subscription will be release in CONTEXT_STRANDAUX_INVOKESUBSCRIBE,
    // however we are not invoking CONTEXT_STRANDAUX_INVOKESUBSCRIBE, so the refcount should be released explictly
    //
    MI_Result r = CreateAndAddSubscriptionHelper(
        subMgr,
        &setupStruct->provider,
        &params,
        &setupStruct->subContext);

    if (r != MI_RESULT_OK)
        return;

    // Overwrite the strand FT to prevent the message from getting sent out
    setupStruct->subContext->baseCtx.strand.info.userFT = &ContextTest_Right_InteractionFT;

    SubMgrSubscription* sub = setupStruct->subContext->subscription;

    ((SubMgrSubscription*)setupStruct->subContext->subscription)->state = state;

    SubMgr_SetEnabled( subMgr, MI_TRUE );
    SubMgr_SetTerminating( subMgr, MI_FALSE );
    SubMgr_SetAllCancelledSafe( subMgr, MI_FALSE );

    AggregationContext *ac = SubMgr_CreateAggrContext( subMgr );
    NitsAssert( ac != NULL, PAL_T("Init failed") );
    if ( ac == NULL )
    {
        SubMgr_DeleteSubscription(subMgr, sub);
        return;
    }

    NitsAssert( MI_RESULT_OK == MI_Context_PostCimError(
        &setupStruct->subContext->baseCtx.base, err),
        PAL_T("PostCimError unexpected result") );

    while (ShutdownState_Released != disableState)
    {
        Sleep_Milliseconds(sleepTimeInMs);
        if (ShutdownState_Released == disableState)
        {
            break; // jump out because the first execution of the timeout already finished.
        }
    }

    // Verify message received.  The result should be overwritten because of bad type
    NitsAssert( MI_TRUE == latestMessage.isReceived, PAL_T("Expected PostResult message from handler") );
    NitsAssert( expected == latestMessage.result, PAL_T("Unexpected result message value") );
}

//
// Case 1: Bad status code type
//
// All cases are common with PostResult except the bad status code and bad message, so it is not required to specifically test AggregationContext.
NitsTest1(TestContext_IndPostCimError_SubscriptionContext_BadCIMStatusCode, TestContext_SubscrContext_Setup, genericContextTemplate)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_SubscrContext_Setup->_TestContext_Struct;

    MI_Instance* errorInstance = NULL;

    NitsAssertOrReturn( MI_RESULT_OK == MI_Context_NewDynamicInstance( &setupStruct->context.base, MI_T("CIM_Error"), 0, &errorInstance), PAL_T("Failed to create CIM_Error instance") );
    NitsAssertOrReturn( NULL != errorInstance, PAL_T("No CIM_Error instance created") );

    MI_Value value;
    value.uint64 = 1;
    NitsAssert( MI_RESULT_OK == MI_Instance_AddElement( errorInstance, MI_T("CIMStatusCode"), &value, MI_UINT64, 0 ), PAL_T("Failed to set CIMStatusCode on CIM_Error") );

    value.string = (MI_Char*)PAL_T("ErrorString");
    NitsAssert( MI_RESULT_OK == MI_Instance_AddElement( errorInstance, MI_T("Message"), &value, MI_STRING, 0 ), PAL_T("Failed to set Message on CIM_Error") );

    TestContext_IndPostCimError_SubscriptionContext_Helper(setupStruct,
        SubscriptionState_Unsubscribing,
        errorInstance,
        MI_RESULT_INVALID_CLASS_HIERARCHY);

    _ClearReceivedMessage();

    if (errorInstance)
    {
        NitsAssert( MI_RESULT_OK == MI_Instance_Delete( errorInstance ), PAL_T("Unable to clean up errorInstance") );
    }
}
NitsEndTest

// _IndPostCimError on SubscriptionContext
//
// Case 2: Bad message type
//
// All cases are common with PostResult except the bad status code and bad message, so it is not required to specifically test AggregationContext.
NitsTest1(TestContext_IndPostCimError_SubscriptionContext_BadMessageType, TestContext_SubscrContext_Setup, genericContextTemplate)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_SubscrContext_Setup->_TestContext_Struct;

    MI_Instance* errorInstance = NULL;

    NitsAssert( MI_RESULT_OK == MI_Context_NewDynamicInstance( &setupStruct->context.base, MI_T("CIM_Error"), 0, &errorInstance), PAL_T("Failed to create CIM_Error instance") );
    NitsAssertOrReturn( NULL != errorInstance, PAL_T("No CIM_Error instance created") );

    MI_Value value;
    value.uint32 = MI_RESULT_INVALID_NAMESPACE;
    NitsAssert( MI_RESULT_OK == MI_Instance_AddElement( errorInstance, MI_T("CIMStatusCode"), &value, MI_UINT32, 0 ), PAL_T("Failed to set CIMStatusCode on CIM_Error") );

    TChar* errorString = (TChar*)PAL_T("ErrorString");
    MI_StringA stringA;
    stringA.data = &errorString;
    stringA.size = 1;
    value.stringa = stringA;
    NitsAssert( MI_RESULT_OK == MI_Instance_AddElement( errorInstance, MI_T("Message"), &value, MI_STRINGA, 0 ), PAL_T("Failed to set Message on CIM_Error") );

    TestContext_IndPostCimError_SubscriptionContext_Helper(
        setupStruct,
        SubscriptionState_Unsubscribing,
        errorInstance,
        MI_RESULT_INVALID_NAMESPACE);

    // Verify message received.  The result should be overwritten because of bad type
    NitsAssert( 0 == Tcslen(latestMessage.errorStr), PAL_T("Unexpected error string") );
    NitsCompare( MI_RESULT_OK, MI_Instance_GetElement( latestMessage.cimError, MI_T("CIMStatusCode"), &value, NULL, NULL, NULL), PAL_T("Unable to access CIMStatusCode") );
    NitsCompare( MI_RESULT_INVALID_NAMESPACE, value.uint32, PAL_T("Expected value set earlier in test") );
    _ClearReceivedMessage();

    if (errorInstance)
    {
        NitsAssert( MI_RESULT_OK == MI_Instance_Delete( errorInstance ), PAL_T("Unable to clean up errorInstance") );
    }
}
NitsEndTest

// _IndPostCimError on SubscriptionContext
//
// Case 3: Message type and status code are OK
//
// All cases are common with PostResult except the bad status code and bad message, so it is not required to specifically test AggregationContext.
NitsTest1(TestContext_IndPostCimError_SubscriptionContext_OK, TestContext_SubscrContext_Setup, genericContextTemplate)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_SubscrContext_Setup->_TestContext_Struct;

    MI_Instance* errorInstance = NULL;

    NitsAssertOrReturn( MI_RESULT_OK == _CreateCimError( &setupStruct->context.base, &errorInstance ), PAL_T("Failed to create CIM_Error") );

    TestContext_IndPostCimError_SubscriptionContext_Helper(
        setupStruct,
        SubscriptionState_Unsubscribing,
        errorInstance,
        MI_RESULT_FAILED);

    // Verify message received.  The result should be overwritten because of bad type
    NitsAssert( 0 == Tcscmp(latestMessage.errorStr, PAL_T("ErrorString")), PAL_T("Unexpected error string") );
    MI_Value value;
    NitsCompare( MI_RESULT_OK ,MI_Instance_GetElement( latestMessage.cimError, MI_T("CIMStatusCode"), &value, NULL, NULL, NULL), PAL_T("Unable to access CIMStatusCode") );
    NitsCompare( 1, value.uint32, PAL_T("Expected value set earlier in test") );
    _ClearReceivedMessage();

    if (errorInstance)
    {
        NitsAssert( MI_RESULT_OK == MI_Instance_Delete( errorInstance ), PAL_T("Unable to clean up errorInstance") );
    }
}
NitsEndTest

NitsTest1(TestContext_IndPostIndication_SubscriptionContext_ValidatesInstance, TestContext_SubscrContext_Setup, genericContextTemplate)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_SubscrContext_Setup->_TestContext_Struct;
    MI_Instance* inst = NULL;
    MI_Instance* inst2 = NULL;
    MI_Result result;
    MI_Value value;
    Batch batch = BATCH_INITIALIZER;
    Batch* b = &batch;

    result = Instance_NewDynamic(&inst, PAL_T("test_class"), MI_FLAG_CLASS, b);
    TEST_ASSERT(result == MI_RESULT_OK);
    if(MI_RESULT_OK != result)
        NitsReturn;

    value.string = NULL;
    result = MI_Instance_AddElement(inst, PAL_T("StringKey"), &value, MI_STRING, MI_FLAG_KEY | MI_FLAG_NULL);
    TEST_ASSERT(result == MI_RESULT_OK);

    InteractionOpenParams params;
    SubscriptionManager* subMgr = setupStruct->provider.subMgr;

    InteractionOpenParams_Init(&params);
    params.interaction = &setupStruct->leftSideStrand.info.interaction;
    params.msg = &setupStruct->req->base.base;

    //
    // SubMgr_CreateSubscription:One refcount of subscription will be release in CONTEXT_STRANDAUX_INVOKESUBSCRIBE,
    // however we are not invoking CONTEXT_STRANDAUX_INVOKESUBSCRIBE, so the refcount should be released explictly
    //
    result = CreateAndAddSubscriptionHelper(
        subMgr,
        &setupStruct->provider,
        &params,
        &setupStruct->subContext);

    if (result != MI_RESULT_OK)
    {
        Batch_Delete(b);
        NitsReturn;
    }
    // Overwrite the strand FT to prevent the message from getting sent out
    setupStruct->subContext->baseCtx.strand.info.userFT = &ContextTest_Right_InteractionFT;

    SubMgrSubscription* sub = setupStruct->subContext->subscription;

    SubMgr_SetEnabled( subMgr, MI_TRUE );
    SubMgr_SetTerminating( subMgr, MI_FALSE );
    SubMgr_SetAllCancelledSafe( subMgr, MI_FALSE );

    AggregationContext *ac = SubMgr_CreateAggrContext( subMgr );
    NitsAssert( ac != NULL, PAL_T("Init failed") );
    if ( ac == NULL )
    {
        SubMgr_DeleteSubscription(subMgr, sub);
        Batch_Delete(b);
        NitsReturn;
    }

    // Post the invalid indication
    NitsCompare(MI_RESULT_FAILED, MI_Context_PostIndication(&setupStruct->subContext->baseCtx.base, inst, 0, NULL ), PAL_T("Expect failure for invalid instance"));

    // Create a good indication and post it
    result = Instance_NewDynamic(&inst2, PAL_T("test_class"), MI_FLAG_CLASS, b);
    TEST_ASSERT(result == MI_RESULT_OK);
    if(MI_RESULT_OK != result)
    {
        SubMgr_DeleteSubscription(subMgr, sub);
        Batch_Delete(b);
        NitsReturn;
    }
    value.string = (ZChar*)PAL_T("somekey");
    result = MI_Instance_AddElement(inst2, PAL_T("StringKey"), &value, MI_STRING, MI_FLAG_KEY);
    TEST_ASSERT(result == MI_RESULT_OK);

    NitsCompare(MI_RESULT_OK, MI_Context_PostIndication(&setupStruct->subContext->baseCtx.base, inst2, 0, NULL ), PAL_T("Expect success for good instance"));

    _CallPostResult_SubCtx( setupStruct, SubscriptionState_Subscribed, MI_RESULT_OK, MI_RESULT_OK );

    // Waits for asynchronous Disable thread to complete
    while (ShutdownState_Released != disableState)
    {
        Sleep_Milliseconds(sleepTimeInMs);
        if (ShutdownState_Released == disableState)
        {
            break; // jump out because the first execution of the timeout already finished.
        }
    }

    // Verify message received
    NitsAssert( MI_TRUE == latestMessage.isReceived, PAL_T("Expected PostResult message from handler") );
    NitsCompare( MI_RESULT_OK, latestMessage.result, PAL_T("Unexpected result message value") );
    NitsCompare( 1, latestMessage.indicationCount, PAL_T("Unexpected indication") );
    _ClearReceivedMessage();

    Batch_Delete(b);
}
NitsEndTest

/*****************************************************************************
 *
 * AggregationContext Post* Handling Tests
 *
 *****************************************************************************/
NitsSetup0(TestContext_AggregationNoSubscr_Setup, TestContext_Struct)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_Struct;

    // SubscriptionManager initialization
    setupStruct->provider.subMgr = SubMgr_New();
    NitsAssertOrReturn( NULL != setupStruct->provider.subMgr, PAL_T("SubscriptionManager allocation failed") );
    SubMgr_Init(setupStruct->provider.subMgr, &setupStruct->provider);

    NitsAssertOrReturn( MI_RESULT_OK == AggrContext_Init(
        &setupStruct->aggrContext,
        &setupStruct->provider,
        setupStruct->provider.subMgr ), PAL_T("Init failed") );

    NitsContext()->_TestContext_Struct->provider.classDecl = &CIM_InstCreation_rtti; /* Default value so it has a class name */
    NitsContext()->_TestContext_Struct->provider.refusedUnload = MI_TRUE;  /* Done to prevent de-referencing a NULL lib ptr */
}
NitsEndSetup

NitsCleanup(TestContext_AggregationNoSubscr_Setup)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_Struct;

    AggrContext_Close( &setupStruct->aggrContext );

    if (setupStruct->provider.subMgr)
    {
        SubMgr_Delete( setupStruct->provider.subMgr );
    }
}
NitsEndCleanup

// _IndPostResult on AggregationContext
//
// Case 1: State is Disabled, result is OK
//
NitsTest1(TestContext_IndPostResult_AggregationContext_Disable_OK, TestContext_AggregationNoSubscr_Setup, genericContextTemplate)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_AggregationNoSubscr_Setup->_TestContext_Struct;

    SubMgr_SetEnabled((setupStruct->provider.subMgr), MI_FALSE);

    NitsAssert( MI_RESULT_OK == MI_Context_PostResult( &setupStruct->aggrContext.baseCtx.base, MI_RESULT_OK ), PAL_T("NULL context") );

    NitsCompare( MI_FALSE, SubMgr_IsEnabled(setupStruct->provider.subMgr), PAL_T("PostResult on aggregation context should disable the class"));
}
NitsEndTest

// _IndPostResult on AggregationContext
//
// Case 2: State is Disabled, result is NOT OK
//
NitsTest1(TestContext_IndPostResult_AggregationContext_Disable_NotOK, TestContext_AggregationNoSubscr_Setup, genericContextTemplate)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_AggregationNoSubscr_Setup->_TestContext_Struct;

    SubMgr_SetEnabled((setupStruct->provider.subMgr), MI_FALSE);

    NitsAssert( MI_RESULT_OK == MI_Context_PostResult( &setupStruct->aggrContext.baseCtx.base, MI_RESULT_FAILED ), PAL_T("NULL context") );

    NitsCompare( MI_FALSE, SubMgr_IsEnabled(setupStruct->provider.subMgr), PAL_T("PostResult on aggregation context should disable the class"));
}
NitsEndTest

// _IndPostResult on AggregationContext
//
// Case 3: Result is OK (state != disabled)
//
NitsTest1(TestContext_IndPostResult_AggregationContext_NoDisable_PostOK, TestContext_AggregationNoSubscr_Setup, genericContextTemplate)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_AggregationNoSubscr_Setup->_TestContext_Struct;

    SubMgr_SetEnabled(setupStruct->provider.subMgr, MI_TRUE);

    NitsAssert( MI_RESULT_OK == MI_Context_PostResult( &setupStruct->aggrContext.baseCtx.base, MI_RESULT_OK ), PAL_T("NULL context") );

    NitsCompare( MI_FALSE, SubMgr_IsEnabled(setupStruct->provider.subMgr), PAL_T("PostResult on aggregation context should disable the class"));
}
NitsEndTest

//
// _IndPostResult on AggregationContext
//
// Case 4: Result is NOT OK (state != disabled)
//
NitsTest1(TestContext_IndPostResult_AggregationContext_NotDisable_NotOK, TestContext_AggregationNoSubscr_Setup, genericContextTemplate)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_AggregationNoSubscr_Setup->_TestContext_Struct;

    SubMgr_SetEnabled(setupStruct->provider.subMgr, MI_TRUE);

    NitsAssert( MI_RESULT_OK == MI_Context_PostResult( &setupStruct->aggrContext.baseCtx.base, MI_RESULT_FAILED ), PAL_T("NULL context") );

    NitsCompare( MI_FALSE, SubMgr_IsEnabled(setupStruct->provider.subMgr), PAL_T("PostResult on aggregation context should disable the class"));
}
NitsEndTest


//
// Initialize a CIM_InstCreation instance for use with PostIndication that matches
// the default test filter.
//
MI_Result _InitializeCimInstCreation(
    CIM_InstCreation* indication )
{
    if ( ! indication )
    {
        return MI_RESULT_FAILED;
    }

    if(!NitsAssert( MI_RESULT_OK == Instance_Construct( &indication->__instance, &CIM_InstCreation_rtti, NULL ), PAL_T("Unable to construct indication instance") ))
        return MI_RESULT_FAILED;

    MI_Value value;
    value.string = (MI_Char*)PAL_T("MSFT:IndicationIdentifier");
    if(!NitsAssert( MI_RESULT_OK == MI_Instance_SetElement( &indication->__instance, PAL_T("IndicationIdentifier"), &value, MI_STRING, 0 ), PAL_T("Unable to set property") ))
        return MI_RESULT_FAILED;

    return MI_RESULT_OK;
}


STRAND_DEBUGNAME( test_Context_AggrSubs_Strand );

//
// Sets up an AggregationContext for calls, initializes a SubscriptionManager, and
// adds a SubMgrSubscription for sending messages to upper layers within OMI.
//
NitsSetup0(TestContext_AggregationWithSubscr_Setup, TestContext_Struct)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_Struct;

    //
    // Initialize provider
    //
    NitsAssertOrReturn(MI_RESULT_OK == Test_Provider_Init( &setupStruct->provider ), PAL_T("Failed to initialize subscription manager") );

    NitsDisableFaultSim;

    // Strand initialization
    memset( &setupStruct->leftSideStrand, 0, sizeof(Strand) );
    Strand_Init( STRAND_DEBUG(test_Context_AggrSubs_Strand) &setupStruct->leftSideStrand, &ContextTest_Left_CheckedInteractionFT, 0, NULL );

    // Simulate opening with message mode
    setupStruct->leftSideStrand.info.opened = MI_TRUE;
    setupStruct->leftSideStrand.info.thisAckPending = MI_TRUE;

    AggregationContext* ac = SubMgr_CreateAggrContext(setupStruct->provider.subMgr);
    NitsAssertOrReturn( NULL != ac, PAL_T("AggregationContext must be initialized") );

    //
    // Create request msg
    //
    NitsContext()->_TestContext_Struct->req = SubscribeReq_New( 1, 0 );
    SubscribeReq* msg = NitsContext()->_TestContext_Struct->req;

    static MI_ConstString filter = MI_T("SELECT * FROM CIM_InstIndication WHERE IndicationIdentifier = \"MSFT:IndicationIdentifier\"");
    static MI_ConstString language = MI_T("WQL");

    msg->targetType = SUBSCRIP_TARGET_LIFECYCLE_ALL;
    msg->filter = filter;
    msg->language = language;
    msg->subscriptionID = 1337;

    InteractionOpenParams params;

    InteractionOpenParams_Init(&params);
    params.interaction = &setupStruct->leftSideStrand.info.interaction;
    params.msg = &msg->base.base;

    memcpy( &g_cdTest, &CIM_InstCreation_rtti, sizeof(MI_ClassDecl));
    g_cdTest.providerFT = &g_pft;
    setupStruct->provider.classDecl = &g_cdTest; /* Default value so it has a class name */
    setupStruct->provider.refusedUnload = MI_TRUE;  /* Done to prevent de-referencing a NULL lib ptr */
    setupStruct->provider.lib = &setupStruct->library;
    setupStruct->provider.lib->provmgr = &setupStruct->provMgr;

    //
    // create subscription
    //
    MI_Result r = CreateAndAddSubscriptionHelper(
        setupStruct->provider.subMgr,
        &setupStruct->provider,
        &params,
        &setupStruct->subContext);

    NitsCompare( MI_RESULT_OK, r, PAL_T("Failed to add subscription") );

    //
    // Additional settings to tweak to simulate subscription
    //
    SubscriptionManager* localSubMgr = setupStruct->provider.subMgr;
    ((SubMgrSubscription*)localSubMgr->subscrList.head)->state = SubscriptionState_Subscribed;

    //
    // Overwrite the strand FT to prevent the message from getting sent out
    // !! This replaces the original interaction function table of subscription context,
    // !! so all provider functions will not be invoked
    //
    setupStruct->subContext->baseCtx.strand.info.userFT = &SimSubscribeContext_Right_InteractionFT;

    Sem_Init( &setupStruct->semFinalMessagePosted, SEM_USER_ACCESS_DEFAULT, 0 );
    g_sem = &setupStruct->semFinalMessagePosted;
}
NitsEndSetup


NitsCleanup(TestContext_AggregationWithSubscr_Setup)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_Struct;

    AggregationContext* ac = SubMgr_RemoveAggrContext(setupStruct->provider.subMgr);
    if (ac)
        AggrContext_Delete(ac);

    setupStruct->provider.refusedUnload = MI_TRUE;  // Prevents Provider_Release from releasing
    Provider_TerminateIndication( &setupStruct->provider, MI_RESULT_FAILED, NULL, NULL );

    Test_Provider_Finalize( &setupStruct->provider );

    if (setupStruct->req)
    {
        NitsCompare(1, (size_t)setupStruct->req->base.base.refCounter, PAL_T("RefCount of request message is wrong. Leak memory"));
        SubscribeReq_Release( setupStruct->req );
    }

    Sem_Destroy ( &setupStruct->semFinalMessagePosted );
    g_sem = NULL;
}
NitsEndCleanup

//
// _IndPostError on AggregationContext
// Result is NOT OK (state != disabled), message returned
//
NitsTest1(TestContext_IndPostError_AggregationContext_NotDisable_NotOK, TestContext_AggregationWithSubscr_Setup, genericContextTemplate)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_AggregationWithSubscr_Setup->_TestContext_Struct;

    SubMgr_SetEnabled(setupStruct->provider.subMgr, MI_TRUE);
    MI_Context* context = &setupStruct->provider.subMgr->aggrCtx->baseCtx.base;

    NitsAssert( MI_RESULT_OK == MI_Context_PostError(
        context,
        MI_RESULT_INVALID_NAMESPACE,
        MI_RESULT_TYPE_MI,
        MI_T("ErrorString") ), PAL_T("Unexpected result") );

    Sem_Wait( & setupStruct->semFinalMessagePosted );
    NitsCompare( MI_FALSE, SubMgr_IsEnabled(setupStruct->provider.subMgr), PAL_T("PostError on aggregation context should disable the class"));

    //
    // Verify message received.  The result should be overwritten because of bad type
    // (lastestMessage came from ContextTest_Cancel_SimulateUnsubscribeProvider function
    //
    NitsAssert( MI_TRUE == latestMessage.isReceived, PAL_T("Expected PostError message from handler") );
    NitsAssert( MI_RESULT_SERVER_LIMITS_EXCEEDED == latestMessage.result, PAL_T("Unexpected result message value") );
    NitsAssert( 0 == Tcscmp(latestMessage.errorStr, SERVER_EXCEEDED_LIMIT_MSG), PAL_T("Unexpected error string") );
    _ClearReceivedMessage();
}
NitsEndTest

// _IndPostCimError on AggregationContext
//
// Result is NOT OK (state != disabled), message returned with ErrorString and ErrorCode
//
NitsTest1(TestContext_IndPostCimError_AggregationContext_MsgReceived, TestContext_AggregationWithSubscr_Setup, genericContextTemplate)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_AggregationWithSubscr_Setup->_TestContext_Struct;

    MI_Instance* errorInstance = NULL;
    MI_Context* context = &setupStruct->provider.subMgr->aggrCtx->baseCtx.base;
    NitsAssert( MI_RESULT_OK == _CreateCimError( context, &errorInstance ), PAL_T("Failed to create CIM_Error") );

    SubMgr_SetEnabled(setupStruct->provider.subMgr, MI_TRUE);

    NitsAssert( MI_RESULT_OK == MI_Context_PostCimError(
        context,
        errorInstance ), PAL_T("PostCimError unexpected result") );

    Sem_Wait( & setupStruct->semFinalMessagePosted );
    NitsCompare( MI_FALSE, SubMgr_IsEnabled(setupStruct->provider.subMgr), PAL_T("PostError on aggregation context should disable the class"));

    //
    // Verify message received.  The result should be overwritten because of bad type
    // (lastestMessage came from ContextTest_Cancel_SimulateUnsubscribeProvider function
    //
    NitsAssert( MI_TRUE == latestMessage.isReceived, PAL_T("Expected PostError message from handler") );
    NitsAssert( MI_RESULT_SERVER_LIMITS_EXCEEDED == latestMessage.result, PAL_T("Unexpected result message value") );
    NitsAssert( 0 == Tcscmp(latestMessage.errorStr, SERVER_EXCEEDED_LIMIT_MSG), PAL_T("Unexpected error string") );
    _ClearReceivedMessage();

    if (errorInstance)
        NitsAssert( MI_RESULT_OK == MI_Instance_Delete( errorInstance ), PAL_T("Unable to clean up errorInstance") );
}
NitsEndTest

//
// TODO: Uncomment once cleanup of TestContext_AggregationNoSubscr_Setup issue is resolved
// _IndPostIndication on AggregationContext
//
// Disabled state OR no subscriptions means no action
//
NitsTest1(TestContext_IndPostIndication_AggrContext_Errors, TestContext_AggregationNoSubscr_Setup, genericContextTemplate)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_AggregationNoSubscr_Setup->_TestContext_Struct;

    // Prepare Indication to send
    NitsAssertOrReturn( MI_RESULT_OK == _InitializeCimInstCreation( &setupStruct->instCreation ), PAL_T("Unable to create indication") );

    // Case 1: Disabled State
    SubMgr_SetEnabled(setupStruct->provider.subMgr, MI_FALSE);

    MI_Context* context = &setupStruct->aggrContext.baseCtx.base;
    NitsAssert( MI_RESULT_FAILED == MI_Context_PostIndication(
        context,
        &setupStruct->instCreation.__instance,
        0,
        NULL ), PAL_T("Unexpected PostIndication result") );

    // Verify message not sent.
    NitsAssert( MI_FALSE == latestMessage.isReceived, PAL_T("Expected PostResult message from handler") );
    _ClearReceivedMessage();

    // Case 2: no subscriptions present
    SubMgr_SetEnabled(setupStruct->provider.subMgr, MI_TRUE);

    NitsAssert( MI_RESULT_FAILED == MI_Context_PostIndication(
        context,
        &setupStruct->instCreation.__instance,
        0,
        NULL ), PAL_T("Unexpected PostIndication result") );

    // Verify message not sent.
    NitsAssert( MI_FALSE == latestMessage.isReceived, PAL_T("Expected PostResult message from handler") );
    _ClearReceivedMessage();

    NitsAssert( MI_RESULT_OK == MI_Instance_Destruct( &setupStruct->instCreation.__instance ), PAL_T("Unable to clean up indication") );
}
NitsEndTest

// _IndPostIndication on AggregationContext
//
// Filter failure
//
NitsTest1(TestContext_IndPostIndication_FilterFailure, TestContext_AggregationWithSubscr_Setup, genericContextTemplate)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_AggregationWithSubscr_Setup->_TestContext_Struct;

    // Prepare non-matching Indication to send
    MI_Instance* errorInstance = NULL;
    MI_Context* context = &setupStruct->provider.subMgr->aggrCtx->baseCtx.base;
    NitsAssert( MI_RESULT_OK == _CreateCimError( context, &errorInstance ), PAL_T("Failed to create CIM_Error") );

    // Set state and post the indication
    SubMgr_SetEnabled(setupStruct->provider.subMgr, MI_TRUE);

    NitsAssert( MI_RESULT_OK == MI_Context_PostIndication(
        context,
        errorInstance,
        0,
        NULL ), PAL_T("Unexpected PostIndication result") );

    // Verify message not sent.
    NitsAssert( MI_FALSE == latestMessage.isReceived, PAL_T("Expected PostResult message from handler") );
    _ClearReceivedMessage();

    if (errorInstance)
    {
        NitsAssert( MI_RESULT_OK == MI_Instance_Delete( errorInstance ), PAL_T("Unable to clean up errorInstance") );
    }
}
NitsEndTest

//
// _IndPostIndication on AggregationContext
//
// Filter matches, indication sent
//
NitsTest1(TestContext_IndPostIndication_FilterMatches, TestContext_AggregationWithSubscr_Setup, genericContextTemplate)
{
    TestContext_Struct* setupStruct = NitsContext()->_TestContext_AggregationWithSubscr_Setup->_TestContext_Struct;

    //
    // work around Provider_NewInstanceCreated issue
    //
    Selector* selector;
    Batch batch;
    {
        size_t selectorsize = sizeof(Selector);
        size_t provmgrsize = sizeof(ProvMgr);
        size_t librarysize = sizeof(Library);
        Batch_Init( &batch, BATCH_MAX_PAGES );
        char* buf = (char*)Batch_GetClear(&batch, (selectorsize + provmgrsize + librarysize));
        selector = (Selector*) buf;
        NitsAssertOrReturn( MI_RESULT_OK == Selector_Init( selector ), PAL_T("Unable to initialize selector") );
        buf += selectorsize;
        ProvMgr* provmgr = (ProvMgr*)buf;
        provmgr->selector = selector;
        buf += provmgrsize;
        Library* library = (Library*)buf;
        library->provmgr = provmgr;
        setupStruct->subContext->baseCtx.provider->lib = library;
    }

    // Prepare Indication to send
    NitsAssertOrReturn( MI_RESULT_OK == _InitializeCimInstCreation( &setupStruct->instCreation ), PAL_T("Unable to create indication") );

    // Additional setup tweaks to hit the desired code path
    SubMgr_SetEnabled(setupStruct->provider.subMgr, MI_TRUE);

    MI_Context* context = &setupStruct->provider.subMgr->aggrCtx->baseCtx.base;
    NitsAssert( MI_RESULT_OK == MI_Context_PostIndication(
        context,
        &setupStruct->instCreation.__instance,
        0,
        NULL ), PAL_T("Unexpected PostIndication result") );

    // Verify message sent.
    NitsAssert( MI_TRUE == latestMessage.isReceived, PAL_T("Expected Indication message from handler") );
    // TODO: Decode instance and validate
    // NitsAssert( NULL != latestMessage.indication, PAL_T("Expected PostIndication message from handler") );

    /*
    // TODO: The message must be unpacked in the Post handler before I can read the instance
    MI_Value value;
    value.uint64 = 0;
    NitsAssert( MI_RESULT_OK == MI_Instance_GetElement( latestMessage.indication, MI_T("IndicationIdentifier"), &value, NULL, NULL, NULL), PAL_T("Unable to access IndicationIdentifier") );
    if (value.string)
    {
        NitsAssert( 0 == Tcscmp(value.string, PAL_T("MSFT:IndicationIdentifier")), PAL_T("Unexpected identifier") );
    }
    else
    {
        NitsAssert( false, PAL_T("Expected property within indication") );
    }
    */

    _ClearReceivedMessage();

    //
    // Restore lib ptr prior to clean up
    //
    setupStruct->subContext->baseCtx.provider->lib = NULL;
    Selector_Destroy( selector );
    Batch_Destroy( &batch );

    NitsAssert( MI_RESULT_OK == MI_Instance_Destruct( &setupStruct->instCreation.__instance ), PAL_T("Unable to clean up indication") );
}
NitsEndTest

// TODO: PostIndication_SubscriptionContext scenarios


/*
**==============================================================================
**
** Test CTX_TYPE_IND_SUB_UNSUB
**
**==============================================================================
*/
NitsTest(TestSubUnsubContext)
    Context ctx;
    MI_Result r;
    MI_Result finalresult = MI_RESULT_OK;
    SubscribeReq* req = SubscribeReq_New(1, 0);
    NitsAssertOrReturn( req != NULL, PAL_T("failed to allocate SubscribeReq"));
    r = Subunsub_Context_Init(&ctx, &finalresult, &req->base);
    NitsCompare(r, MI_RESULT_OK, PAL_T("failed to initialize subunsub context"));
    if ( r != MI_RESULT_OK )
    {
        SubscribeReq_Release(req);
        NitsReturn;
    }

    //
    // validate post result
    //
    MI_Instance x = {0};
    r = MI_Context_PostIndication(&ctx.base, &x, 1, NULL);
    NitsCompare(r, MI_RESULT_NOT_SUPPORTED, PAL_T("Unexpected PostIndication result"));

    r = MI_Context_PostInstance(&ctx.base, &x);
    NitsCompare(r, MI_RESULT_NOT_SUPPORTED, PAL_T("Unexpected PostInstance result"));

    r = MI_Context_PostResult(&ctx.base, MI_RESULT_ACCESS_DENIED);
    NitsCompare(r, MI_RESULT_OK, PAL_T("Unexpected PostResult result"));
    NitsCompare(finalresult, MI_RESULT_ACCESS_DENIED, PAL_T("Unexpected PostResult final result"));

    r = MI_Context_PostCimError(&ctx.base, &x);
    NitsCompare(r, MI_RESULT_OK, PAL_T("Unexpected PostCimError result"));
    NitsCompare(finalresult, MI_RESULT_FAILED, PAL_T("Unexpected PostCimError final result"));

    r = MI_Context_PostError(&ctx.base, MI_RESULT_INVALID_CLASS, MI_T("MI"), MI_T("error details"));
    NitsCompare(r, MI_RESULT_OK, PAL_T("Unexpected PostError result"));
    NitsCompare(finalresult, MI_RESULT_INVALID_CLASS, PAL_T("Unexpected PostError final result"));

    CIM_InstCreation instcreate;
    r = MI_Context_ConstructInstance(&ctx.base, &CIM_InstCreation_rtti, &instcreate.__instance);
    NitsCompare(r, MI_RESULT_OK, PAL_T("Failed to construct instance"));
    if (r == MI_RESULT_OK)
    {
        MI_Instance_Destruct(&instcreate.__instance);
    }

    //
    // Clean up
    //
    Context_Close(&ctx);
    SubscribeReq_Release(req);

NitsEndTest

