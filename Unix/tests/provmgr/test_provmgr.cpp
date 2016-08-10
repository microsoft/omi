/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <vector>
#include <set>
#include <cstdlib>
#include <iostream>
#include <ut/ut.h>
#include <provmgr/provmgr.h>
#include <pal/thread.h>
#include <pal/format.h>
#include <pal/sleep.h>
#include <pal/atomic.h>
#include <base/user.h>
#include <base/paths.h>
#include <base/process.h>
#include <omiclient/client.h>
#include <pal/sleep.h>
#include <base/Strand.h>
#include <base/log.h>
#include <pal/strings.h>
#include "StrandHelper.h"
#include <provmgr/CIM_InstCreation.h>
#include <provmgr/indicationSchema.h>
#include <provmgr/nioproc.h>
#include <provreg/provreg.h>
#include <provmgr/LifecycleContext.h>
#include <provmgr/AggregationContext.h>

using namespace std;

static ProvMgr s_provmgr;
static Selector    s_selector;

#if defined(_MSC_VER)
#undef BEGIN_EXTERNC
#undef END_EXTERNC
#define BEGIN_EXTERNC
#define END_EXTERNC
#endif

NitsSetup(TestProvmg_SetUp)
{
    NitsDisableFaultSim;

    Sock_Start();
    Selector_Init(&s_selector);
}
NitsEndSetup

NitsCleanup(TestProvmg_SetUp)
{
    Sock_Stop();
    Selector_Destroy(&s_selector);
}
NitsEndCleanup

BEGIN_EXTERNC

static void _idleCallback(
    ProvMgr* mgr,
    void* callbackData)
{
    int* p = (int*)callbackData;

    MI_UNUSED(mgr);

    (*p)++;
}

STRAND_DEBUGNAME( TestStrand );

static MI_Result S_FinalResult;

static void _StrandTestPost( _In_ Strand* self, _In_ Message* msg ) 
{
    if( PostResultMsgTag == msg->tag )
    {
        PostResultMsg* resultMsg = (PostResultMsg*)msg;

        S_FinalResult = resultMsg->result;
    }
    
    // no need to do anything else except acking
    Strand_Ack( self );
}

static void _StrandTestAck( _In_ Strand* self) 
{
    // do nothing
}

static void _StrandTestClose( _In_ Strand* self) 
{
    Strand_Close( self );
}

static void _StrandTestFinished( _In_ Strand* self) 
{
    // do nothing
}

static StrandFT strandUserFT = { 
        _StrandTestPost, 
        NULL, 
        _StrandTestAck, 
        NULL, 
        _StrandTestClose, 
        _StrandTestFinished,
        NULL,
        NULL, 
        NULL, 
        NULL, 
        NULL, 
        NULL };
        
static Strand testStrand;
END_EXTERNC

static MI_Result _PostMessage(const char* cn, MI_Result expectedResult = MI_RESULT_OK )
{
    EnumerateInstancesReq* msg;
    ProvMgr_OpenCallbackData data;
    ProvRegEntry entry;

    memset(&entry, 0, sizeof(entry));
    entry.libraryName = "PersonProviderCXX";
    
    // Create new request to send to provider
    msg = EnumerateInstancesReq_New(0, 0);
    if(msg)
    {
        msg->nameSpace = Batch_Tcsdup(msg->base.base.batch, MI_T("test/cpp"));
        msg->className = Batch_StrTcsdup(msg->base.base.batch, cn);
    }

    if (!msg || !msg->nameSpace || !msg->className)
    {
        NitsAssert("Out of memory" && NULL, PAL_T("_PostMessage unable to allocate msg or copy strings"));
        if(msg)
            EnumerateInstancesReq_Release(msg);
        return MI_RESULT_FAILED;
    }

    Strand_Init( STRAND_DEBUG( TestStrand ) &testStrand, &strandUserFT, STRAND_FLAG_ENTERSTRAND, NULL);

    // Send the request to provider manager
    data.self = &s_provmgr;
    data.provRegEntry = &entry;
    S_FinalResult = MI_RESULT_OK;

    Strand_Open(&testStrand,ProvMgr_OpenCallback,&data,&msg->base.base,MI_TRUE);

    NitsAssert(S_FinalResult == expectedResult, PAL_T("ProvMgr_NewRequest failed"));

    // Release the original message
    EnumerateInstancesReq_Release(msg);

    return MI_RESULT_OK;
}

static void _PostInvokeMessage(const char* fn)
{
    InvokeReq* msg;
    MI_Result r;
    MI_Instance* dynamicInstanceParams = 0;
    Batch   dynamicBatch = BATCH_INITIALIZER;
    MI_String params_cn;
    ProvRegEntry entry;
    ProvMgr_OpenCallbackData data;

    memset(&entry, 0, sizeof(entry));
    entry.libraryName = "PersonProviderCXX";

    // Create new request.
    msg = InvokeReq_New(0, 0);

    // Extract arguments.
    msg->nameSpace = Batch_StrTcsdup(msg->base.base.batch, "test/cpp");
    msg->className = Batch_StrTcsdup(msg->base.base.batch, "X_RefuseUnload");
    msg->function = Batch_StrTcsdup(msg->base.base.batch, fn);


    // params
    {
        // parameters instance classname is ignored, but has to have valid syntax
        params_cn = Batch_StrTcsdup(&dynamicBatch, "param");

        r = Instance_NewDynamic(
            &dynamicInstanceParams,
            params_cn,
            MI_FLAG_CLASS,
            &dynamicBatch);

        NitsAssert(r == MI_RESULT_OK, PAL_T("Instance_NewDynamic failed"));

        msg->instanceParams = dynamicInstanceParams;
    }

    Strand_Init( STRAND_DEBUG( TestStrand ) &testStrand, &strandUserFT, STRAND_FLAG_ENTERSTRAND, NULL);

    // Send the request to provider manager
    data.self = &s_provmgr;
    data.provRegEntry = &entry;
    Strand_Open(&testStrand,ProvMgr_OpenCallback,&data,&msg->base.base,MI_TRUE);

    NitsAssert(r == MI_RESULT_OK, PAL_T("ProvMgr_NewRequest failed"));

    InvokeReq_Release(msg);
    Batch_Destroy(&dynamicBatch);
}

NitsTest1(TestProvMgr_UnloadIdle, TestProvmg_SetUp, NitsEmptyValue)
{
    int num = 0;
    
    NitsAssertOrReturn(
        ProvMgr_Init(&s_provmgr, &s_selector, _idleCallback, &num, OMI_GetPath(ID_PROVIDERDIR)) ==
        MI_RESULT_OK,
        PAL_T("ProvMgr_Init failed"));

    s_provmgr.idleTimeoutUsec = SELECT_BASE_TIMEOUT_MSEC * 1000;

    // post message
    if(MI_RESULT_OK != _PostMessage("MSFT_Person"))
        goto testend;

    // run selector to catch timeout
    for (int attempt = 0; attempt < 500 && 0 == num; attempt++)
    {
        Selector_Run(&s_selector, SELECT_BASE_TIMEOUT_MSEC * 1000, MI_FALSE);
    }

    // expect idle callback to be invoked once
    NitsAssert( 1 == num, PAL_T("expect idle callback to be invoked once"));

    NitsAssert( MI_RESULT_OK == Selector_RemoveAllHandlers(&s_selector), PAL_T("Unable to remove handlers") );
testend:
    NitsAssert(ProvMgr_Destroy(&s_provmgr) == MI_RESULT_OK, PAL_T("ProvMgr_Destroy failed"));
}
NitsEndTest

NitsTest1(TestProvMgr_RefuseRequestUnload, TestProvmg_SetUp, NitsEmptyValue)    
{
    int num = 0;

    NitsAssert(
        ProvMgr_Init(&s_provmgr, &s_selector, _idleCallback, &num, OMI_GetPath(ID_PROVIDERDIR)) ==
        MI_RESULT_OK,
        PAL_T("ProvMgr_Init failed"));

    s_provmgr.idleTimeoutUsec = SELECT_BASE_TIMEOUT_MSEC * 1000;

    // post message
    _PostMessage("X_RefuseUnload", MI_RESULT_NOT_SUPPORTED );

    // run selector to catch timeout
    for (int attempt = 0; attempt < 500 && 0 == num; attempt++)
    {
        Selector_Run(&s_selector, SELECT_BASE_TIMEOUT_MSEC * 1000, MI_FALSE);
    }

    // expect idle callback not to be invoked
    NitsAssert( 0 == num, PAL_T("expect idle callback not to be invoked") );

    // call 'request-unload'
    _PostInvokeMessage("RequestUnload");

    // run selector to catch timeout
    for (int attempt = 0; attempt < 500 && 0 == num; attempt++)
    {
        Selector_Run(&s_selector, SELECT_BASE_TIMEOUT_MSEC * 1000, MI_FALSE);
    }

    // expect idle provider to be unloaded by now
    NitsAssert( 1 == num, PAL_T("expect idle provider to be unloaded by now") );
    NitsAssert( MI_RESULT_OK == Selector_RemoveAllHandlers(&s_selector), PAL_T("Unable to remove handlers") );
    NitsAssert(ProvMgr_Destroy(&s_provmgr) == MI_RESULT_OK, PAL_T("ProvMgr_Destroy failed"));
}
NitsEndTest

static Process serverProcess;
MI_Char s_socketFile[PAL_MAX_PATH_SIZE];
char s_socketFile_a[PAL_MAX_PATH_SIZE];

// TODO:- Refactor these tests to start server in a common fixture instead of at multiple places like now
// have most of the tests start server in proc both on windows and non-windows
static int StartServer()
{
    const char* path = OMI_GetPath(ID_SERVERPROGRAM);
    const char* argv[17];
    char http[32];
    char https[32];
    std::string v;

    Snprintf(http, sizeof(http),"%d", ut::getUnittestPortNumberWSMANHTTP());
    Snprintf(https, sizeof(https),"%d", ut::getUnittestPortNumberWSMANHTTPS());

    Strlcpy(s_socketFile_a, OMI_GetPath(ID_SOCKETFILE), sizeof(s_socketFile_a)/sizeof(s_socketFile_a[0]));
    TcsStrlcpy(s_socketFile, s_socketFile_a, sizeof(s_socketFile)/sizeof(s_socketFile[0]));

    if (ut::testGetAttr("skipServer", v))
        return 0;

    argv[0] = path;
    argv[1] = "--rundir";
#if defined(CONFIG_OS_WINDOWS)
    argv[2] = "..";
#else
    argv[2] = OMI_GetPath(ID_PREFIX);
#endif
    argv[3] = "--ignoreAuthentication";
    argv[4] = "--socketfile";
    argv[5] = s_socketFile_a;
    argv[6] = "--httpport";
    argv[7] = http;
    argv[8] = "--httpsport";
    argv[9] = https;
    argv[10] = "--livetime";
    argv[11] = "300";

    argv[12] = "--loglevel";
    argv[13] = Log_GetLevelString(Log_GetLevel());
    argv[14] = NULL;

    if (Process_StartChild(&serverProcess, path, (char**)argv) != 0)
        return -1;

    Sleep_Milliseconds(2000);
    
    int connected = 0;

    // wait for server to start
    // trying to connect in a loop:
    // since connect may fail quickly if server is not running
    // keep doing it in  a loop
    for (int i = 0; i < 400; i++)
    {
        mi::Client cl;
        const MI_Uint64 TIMEOUT = 1 * 1000 * 1000;  // 1 second

        if (cl.Connect(
            s_socketFile,
            PAL_T("unittest"), 
            PAL_T("unittest"), 
            TIMEOUT))
        {
            connected = 1;
            break;
        }

        Sleep_Milliseconds(10);
    }
    NitsAssert(connected == 1, PAL_T("socket connected"));

    if (connected == 1)
        return 0;
    else
        return -1;
}

static int StopServer()
{
    std::string v;

    if (ut::testGetAttr("skipServer", v))
        return 0;

    if (Process_StopChild(&serverProcess) != 0)
        return -1;
    Sleep_Milliseconds(2000);

    return 0;
}


NitsTest1(TestProvMgr_GetLocalSession, TestProvmg_SetUp, NitsEmptyValue)
{
    MI_Result miResult;
    
    StartServer();

    miResult = ProvMgr_Init(&s_provmgr, &s_selector, NULL, NULL, OMI_GetPath(ID_PROVIDERDIR));
    NitsAssert(miResult == MI_RESULT_OK, PAL_T("ProvMgr_Init failed"));
    if (miResult == MI_RESULT_OK)
    {
        MI_Session localSession1;
        MI_Session localSession2;
        MI_Result expectedResult;
#if defined(DISABLE_LOCALSESSION)
        expectedResult = MI_RESULT_NOT_SUPPORTED;
#else
        expectedResult = MI_RESULT_OK;
#endif
        miResult = ProvMgr_GetLocalSesson(&s_provmgr, &localSession1);
        NitsAssert(miResult == expectedResult, PAL_T("ProvMgr_GetLocalSession failed"));

        if (miResult == MI_RESULT_OK)
        {
            MI_Operation miOperation = MI_OPERATION_NULL;
            const MI_Instance *miInstance;
            MI_Boolean moreResults;

            miResult = ProvMgr_GetLocalSesson(&s_provmgr, &localSession2);
            NitsAssert(miResult == MI_RESULT_OK, PAL_T("ProvMgr_GetLocalSession failed"));

            if (miResult == MI_RESULT_OK)
            {
                NitsAssert(memcmp(&localSession1, &localSession2, sizeof(localSession1)) == 0, PAL_T("Unmatched session names"));
            }

            MI_Session_EnumerateInstances(&localSession1, 0, NULL, MI_T("root/test"), MI_T("MSFT_President"), MI_FALSE, NULL, &miOperation);

            do
            {
                MI_Result _tmpResult;
                _tmpResult = MI_Operation_GetInstance(&miOperation, &miInstance, &moreResults, &miResult, NULL, NULL);
                NitsAssert(_tmpResult == MI_RESULT_OK, PAL_T("Unexpected result"));
                NitsAssert(miResult == MI_RESULT_OK, PAL_T("Unexpected result"));

            }while (moreResults && (miResult == MI_RESULT_OK));

            MI_Operation_Close(&miOperation);

        }

        NitsAssert( MI_RESULT_OK == Selector_RemoveAllHandlers(&s_selector), PAL_T("Unable to remove handlers") );
        NitsAssert(ProvMgr_Destroy(&s_provmgr) == MI_RESULT_OK, PAL_T("ProvMgr_Destroy failed"));
    }

    StopServer();
}
NitsEndTest

//----------------------------------------------------------------------------
//
// Subscription tests
//
//----------------------------------------------------------------------------

static MI_LifecycleIndicationContext* g_testLifecycleContext = NULL;

static void MI_CALL __Load(
    _Outptr_ void** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_Result result = MI_RESULT_OK;

    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = &g_testLifecycleContext; // Done to satisfy OACR

    result = MI_Context_GetLifecycleIndicationContext( context, &g_testLifecycleContext );
    
    MI_Context_PostResult(context, result);
}

static void MI_CALL __Unload(
    _In_opt_ void* self,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_Context_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL __EnableIndications(
    _In_opt_ void* self,
    _In_ MI_Context* indicationsContext,
    _In_z_ const MI_Char* nameSpace,
    _In_z_ const MI_Char* className)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(indicationsContext);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
}

static void MI_CALL __DisableIndications(
    _In_opt_ void* self,
    _In_ MI_Context* indicationsContext,
    _In_z_ const MI_Char* nameSpace,
    _In_z_ const MI_Char* className)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    
    MI_Context_PostResult(indicationsContext, MI_RESULT_OK);
}

static void MI_CALL __Subscribe(
    _In_opt_ void* self,
    _In_ MI_Context* context,
    _In_z_ const MI_Char* nameSpace,
    _In_z_ const MI_Char* className,
    _In_opt_ const MI_Filter* filter,
    _In_opt_z_ const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    _Outptr_result_maybenull_ void** subscriptionSelf)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(context);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);    
    MI_UNREFERENCED_PARAMETER(filter);
    MI_UNREFERENCED_PARAMETER(bookmark);
    MI_UNREFERENCED_PARAMETER(subscriptionID);
    *subscriptionSelf = NULL;
}

static void MI_CALL __Unsubscribe(
    _In_opt_ void* self,
    _In_ MI_Context* context,
    _In_z_ const MI_Char* nameSpace,
    _In_z_ const MI_Char* className,
    MI_Uint64  subscriptionID,
    _In_opt_ void* subscriptionSelf)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);    
    MI_UNREFERENCED_PARAMETER(subscriptionID);
    MI_UNREFERENCED_PARAMETER(subscriptionSelf);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

MI_CONST MI_ProviderFT g_dummyTestProvider_FT =
{
    __Load, //MI_ProviderFT_Load Load;
    __Unload, //MI_ProviderFT_Unload Unload;
    NULL, //MI_ProviderFT_GetInstance GetInstance;
    NULL, //MI_ProviderFT_EnumerateInstances EnumerateInstances;
    NULL, //MI_ProviderFT_CreateInstance CreateInstance;
    NULL, //MI_ProviderFT_ModifyInstance ModifyInstance;
    NULL, //MI_ProviderFT_DeleteInstance DeleteInstance;
    NULL, //MI_ProviderFT_AssociatorInstances AssociatorInstances;
    NULL, //MI_ProviderFT_ReferenceInstances ReferenceInstances;
    __EnableIndications, //MI_ProviderFT_EnableIndications EnableIndications;
    __DisableIndications, //MI_ProviderFT_DisableIndications DisableIndications;
    __Subscribe, //MI_ProviderFT_Subscribe Subscribe;
    __Unsubscribe, //MI_ProviderFT_Unsubscribe Unsubscribe;
    NULL //MI_ProviderFT_Invoke Invoke;
};

typedef struct _Test_Indication
{
    MI_Instance __instance;
    /* Test_Indication properties */
    MI_ConstStringField Identifier;
} Test_Indication;

MI_CONST MI_PropertyDecl g_testProvMgr_IdentifierDecl =
{
    MI_FLAG_PROPERTY, // MI_Uint32 flags;
    0x0069720a, // MI_Uint32 code; // first, last, length in hex
    MI_T("Identifier"), // MI_CONST MI_Char* name;
    NULL,   // MI_Qualifier MI_CONST* MI_CONST* qualifiers;
    0, // MI_Uint32 numQualifiers;
    MI_STRING, // MI_Uint32 type;
    NULL, // MI_CONST MI_Char* className;
    0, // MI_Uint32 subscript;
    offsetof(Test_Indication, Identifier), // MI_Uint32 offset;
    NULL,   // MI_CONST MI_Char* origin;
    NULL,   // MI_CONST MI_Char* propagator;
    NULL    // MI_CONST  void* value;
};

MI_PropertyDecl MI_CONST* MI_CONST g_propertyDeclArray[] =
{
    &g_testProvMgr_IdentifierDecl
};

MI_ClassDecl g_dummyTestClassDecl = {
    MI_FLAG_CLASS,//MI_Uint32 flags;
    0,//MI_Uint32 code;
    MI_T("Test_Indication"),//MI_CONST MI_Char* name;
    NULL,//struct _MI_Qualifier MI_CONST* MI_CONST* qualifiers;
    0,//MI_Uint32 numQualifiers;
    g_propertyDeclArray,//struct _MI_PropertyDecl MI_CONST* MI_CONST* properties;
    MI_COUNT(g_propertyDeclArray),//MI_Uint32 numProperties;
    0,//MI_Uint32 size;
    NULL,//MI_CONST MI_Char* superClass;
    NULL,//MI_ClassDecl MI_CONST* superClassDecl;
    NULL,//struct _MI_MethodDecl MI_CONST* MI_CONST* methods;
    0,//MI_Uint32 numMethods;
    NULL,//struct _MI_SchemaDecl MI_CONST* schema;
    &g_dummyTestProvider_FT,//MI_CONST MI_ProviderFT* providerFT;
    NULL//MI_Class *owningClass;
};

const char* TestProvMgr_LibraryName = "TestIndicationLibrary";

static MI_Result testProvMgr_MsgResult = MI_RESULT_OK;
static MI_Boolean testProvMgr_InstanceReceived = MI_FALSE;

MI_Boolean unsubscribeCompletedSemActive = MI_FALSE;
Sem unsubscribeCompletedSem;

//
// This initializes the Finish semaphore to cause the test case to wait for 
// the unsubscribe thread to complete prior to exiting.
//
void _InitializeTestProvMgrSemaphore()
{
    NitsAssert( Sem_Init(&unsubscribeCompletedSem, SEM_USER_ACCESS_ALLOW_ALL, 0) == 0, PAL_T("Unable to intialize unsubscribe semaphore") );
    unsubscribeCompletedSemActive = MI_TRUE;
}

void _ReleaseTestProvMgrSemaphore()
{
    if (unsubscribeCompletedSemActive)
    {
        // This means the unsubscribe thread has completed its cleanup
        // and it is safe to allow the test to proceed with its cleanup.
        NitsAssert( 0 == Sem_Post( &unsubscribeCompletedSem, 1 ), PAL_T("Unexpected semaphore Post status") );
    }
}

void _CleanupTestProvMgrSemaphore()
{
   if (unsubscribeCompletedSemActive)
    {
        // This forces the test to wait for the unsubscribe thread to complete prior to exiting the test
        Sem_Wait(&unsubscribeCompletedSem);
        unsubscribeCompletedSemActive = MI_FALSE;
        Sem_Destroy(&unsubscribeCompletedSem);
    }
}

STRAND_DEBUGNAME( TestProvMgrStrand );

NITS_EXTERN_C void _TestProvMgr_Post( _In_ Strand* self, _In_ Message* msg ) 
{
    if (PostResultMsgTag == msg->tag)
    {
        PostResultMsg* resMsg = (PostResultMsg*)msg;
        testProvMgr_MsgResult = resMsg->result;

        /* close self upon receiving final message */
        Strand_Close(self);
    }
    else if (SubscribeResTag == msg->tag)
    {
        //SubscribeRes* subResMsg = (SubscribeRes*)msg;
        testProvMgr_MsgResult = MI_RESULT_OK;
    }
    else if (PostIndicationMsgTag == msg->tag)
    {
        PostIndicationMsg* indication = (PostIndicationMsg*)msg;

        NitsAssert( NULL != indication->base.packedInstancePtr, PAL_T("Expected packed instance") );
        NitsAssert( 0 != indication->base.packedInstanceSize, PAL_T("Expected packed instance length") );
        testProvMgr_InstanceReceived = MI_TRUE;
    }

    Strand_Ack( self );
}

NITS_EXTERN_C void _TestProvMgr_Finish( _In_ Strand* self_ )
{
    MI_UNUSED( self_ );

    _ReleaseTestProvMgrSemaphore();
}

#ifndef DISABLE_INDICATION

static StrandFT TestProvMgr_InteractionFT =
{
    _TestProvMgr_Post, 
    ContextTest_PostControl_NO_OP, 
    ContextTest_Ack_NO_OP,
    ContextTest_Cancel_NO_OP,
    ContextTest_Close_NO_OP,
    _TestProvMgr_Finish,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL 
};

struct TestProvMgr_SetupStruct
{
    SubscribeReq* msg;
    Library library;
    Provider provider;
    SubscriptionManager subMgr;
    Strand leftSideStrand;

    // Special fields for OMI -> Provider callback
    MI_Uint32 typesFromCallback;
    MI_Boolean callbackCalled;

    MI_Result expectedResult;
    MI_Boolean expectInstance;
};

TestProvMgr_SetupStruct genericProvMgrTemplate = { 0 };

NitsTest(TestProvMgr_NewRequest_Reject_NULL_Input)
{
    InteractionOpenParams params;
    ProvRegEntry entry;

    memset(&entry, 0, sizeof(entry));
    entry.libraryName = TestProvMgr_LibraryName;

    InteractionOpenParams_Init(&params);
    
    NitsAssert( MI_RESULT_INVALID_PARAMETER == ProvMgr_NewRequest(
        NULL,
        &entry,
        NULL ),
        PAL_T("Expected invalid arg"));

    NitsAssert( MI_RESULT_INVALID_PARAMETER == ProvMgr_NewRequest(
        &s_provmgr,
        &entry,
        NULL ),
        PAL_T("Expected invalid arg"));

    NitsAssert( MI_RESULT_INVALID_PARAMETER == ProvMgr_NewRequest(
        &s_provmgr,
        &entry,
        &params ),
        PAL_T("Expected invalid arg"));
}
NitsEndTest

NitsSetup1(TestProvMgr_SetupProvider, TestProvMgr_SetupStruct, TestProvmg_SetUp, NitsEmptyValue)
{
    TestProvMgr_SetupStruct* setupStruct = NitsContext()->_TestProvMgr_SetupStruct;

    NitsAssert(MI_RESULT_OK == ProvMgr_Init(&s_provmgr, &s_selector, NULL, NULL, OMI_GetPath(ID_PROVIDERDIR)), PAL_T("ProvMgr_Init failed"));

    // Strand initialization
    memset( &setupStruct->leftSideStrand, 0, sizeof(Strand) );
    Strand_Init( STRAND_DEBUG(TestProvMgrStrand) &setupStruct->leftSideStrand, &TestProvMgr_InteractionFT, STRAND_FLAG_ENTERSTRAND, NULL );
    STRAND_SETTESTSTRANDTHREAD( &setupStruct->leftSideStrand );

    //
    // Manually create Library and Provider objects to prevent it from
    // depending on registered providers to run.
    //
    memset( &setupStruct->library, 0, sizeof(Library) );
    memset( &setupStruct->provider, 0, sizeof(Provider) );

    // Library init
    Strlcpy(setupStruct->library.libraryName, TestProvMgr_LibraryName, Strlen(TestProvMgr_LibraryName)+1); // plus one for the NULL
    setupStruct->library.provmgr = &s_provmgr;

    /* Add library to the list */
    List_Prepend(
        (ListElem**)&s_provmgr.head,
        (ListElem**)&s_provmgr.tail,
        (ListElem*)&setupStruct->library);

    // Provider init
    setupStruct->provider.refCounter = 1; // simulates one outstanding reqest to the provider (prevents Load and unload)
    setupStruct->provider.lib = &setupStruct->library;
    setupStruct->provider.classDecl = &g_dummyTestClassDecl;
    setupStruct->provider.subMgr = &setupStruct->subMgr;

    SubMgr_Init(&setupStruct->subMgr, &setupStruct->provider);

    List_Prepend(
        (ListElem**)&setupStruct->library.head,
        (ListElem**)&setupStruct->library.tail,
        (ListElem*)&setupStruct->provider);

    // Message Init
    setupStruct->msg = SubscribeReq_New( 1, BinaryProtocolFlag );

    setupStruct->msg->nameSpace = Batch_Tcsdup(setupStruct->msg->base.base.batch, PAL_T("root/cimv2"));
    setupStruct->msg->className = Batch_Tcsdup(setupStruct->msg->base.base.batch, PAL_T("Test_Indication"));
    setupStruct->msg->filter = Batch_Tcsdup(setupStruct->msg->base.base.batch, PAL_T("SELECT * FROM CIM_InstIndication WHERE SourceInstance ISA Test_Indication"));
    setupStruct->msg->language = Batch_Tcsdup(setupStruct->msg->base.base.batch, PAL_T("WQL"));
    setupStruct->msg->targetType = SUBSCRIP_TARGET_DEFAULT;

    // Reset static global variables
    testProvMgr_MsgResult = MI_RESULT_OK;
    testProvMgr_InstanceReceived = MI_FALSE;
}
NitsEndSetup

NitsCleanup(TestProvMgr_SetupProvider)
{
    TestProvMgr_SetupStruct* setupStruct = NitsContext()->_TestProvMgr_SetupStruct;
    
    SubscribeReq_Release( setupStruct->msg );

    NitsAssert( MI_RESULT_OK == Selector_RemoveAllHandlers(&s_selector), PAL_T("Unable to remove handlers") );

    // Do not call ProvMgr_Release or Destroy because the provider and library were manually initialized.  
    // This check verifies that it doesn't get decremented in the tests.
    NitsCompare( 1, (int)setupStruct->provider.refCounter, PAL_T("Unexpected or missing decrement of provider occurred") );

    SubMgr_Finalize(&setupStruct->subMgr);
}
NitsEndCleanup

//============================================================================
//
// "Lifecycle" Indications Tests
//
//============================================================================

MI_Result TestProvMgr_InvokeLoad(
    Provider* provider,
    Message* msg )
{
    Context ctx;
    MI_Result r = MI_RESULT_OK;

    Context_Init(&ctx, provider->lib->provmgr, provider, NULL);
    ctx.result = &r;
    ctx.loadRequest = msg;
    Message_AddRef(ctx.loadRequest);

    NitsAssert( NULL == g_testLifecycleContext, PAL_T("Stale LifecycleContext detected") );

    (*provider->classDecl->providerFT->Load)(&provider->self, NULL, &ctx.base);

    NitsAssert(0xFFFFFFFF == ctx.magic, PAL_T("Load handling function missing PostResult call") );
    NitsAssert( MI_RESULT_OK == r, PAL_T("Unexpected failure in Load") );
    NitsAssert( NULL != g_testLifecycleContext, PAL_T("Initialized LifecycleContext required") );
    return r;
}

NITS_EXTERN_C void TestProvMgr_MI_LifecycleIndicationCallback(
    _In_ MI_Uint32 types,
    _In_opt_ void* callbackData)
{
    if (callbackData)
    {
        TestProvMgr_SetupStruct* testStruct = (TestProvMgr_SetupStruct*)callbackData;
        testStruct->typesFromCallback = types;
        testStruct->callbackCalled = MI_TRUE;
    }
}

// Initializes an already intialized provider struct for lifecycle indications
NitsSetup1(TestProvMgr_SetupLifecycle, NitsEmptyStruct, TestProvMgr_SetupProvider, genericProvMgrTemplate)
{
    TestProvMgr_SetupStruct* setupStruct = NitsContext()->_TestProvMgr_SetupProvider->_TestProvMgr_SetupStruct;

    NitsAssertOrReturn( MI_RESULT_OK == TestProvMgr_InvokeLoad( &setupStruct->provider, &setupStruct->msg->base.base ), PAL_T("Load failed") );

    // Initialize flags and properties that are used in the tests
    testProvMgr_InstanceReceived = MI_FALSE;
    testProvMgr_MsgResult = MI_RESULT_OK;

    setupStruct->typesFromCallback = 0;
    setupStruct->callbackCalled = MI_FALSE;

    NitsAssert( MI_RESULT_OK == MI_LifecycleIndicationContext_RegisterCallback( 
        g_testLifecycleContext, 
        TestProvMgr_MI_LifecycleIndicationCallback,
        setupStruct
        ), PAL_T("Unable to register callback") );

    //
    // Initialize unsubscribe handler
    // single threaded platform require that unsubsribe happen on a separate thread
    //
    RequestHandler_Init(&g_requesthandler);
}
NitsEndSetup

NitsCleanup(TestProvMgr_SetupLifecycle)
{
    TestProvMgr_SetupStruct* setupStruct = NitsContext()->_TestProvMgr_SetupProvider->_TestProvMgr_SetupStruct;
    Provider_TerminateIndication( &setupStruct->provider, MI_RESULT_FAILED, NULL, NULL );
    g_testLifecycleContext = NULL;
    LifecycleContext* lifeCtx = setupStruct->provider.subMgr->lifecycleCtx;
    _CleanupTestProvMgrSemaphore();

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

    NitsAssert( testProvMgr_MsgResult == setupStruct->expectedResult, PAL_T("Expected different PostResult") );
    NitsAssert( testProvMgr_InstanceReceived == setupStruct->expectInstance, PAL_T("Expected instance") );

    if ( lifeCtx )
    {
        setupStruct->provider.subMgr->lifecycleCtx = NULL;
        LifeContext_Delete(lifeCtx);
    }
}
NitsEndCleanup

NitsTest1(TestProvMgr_LifeSubscribe_NotSupported_If_Message_Type_Not_Supported, TestProvMgr_SetupLifecycle, NitsEmptyValue)
{
    ProvMgr_OpenCallbackData data;
    TestProvMgr_SetupStruct* setupStruct = NitsContext()->_TestProvMgr_SetupLifecycle->_TestProvMgr_SetupProvider->_TestProvMgr_SetupStruct;
    ProvRegEntry entry;

    memset(&entry, 0, sizeof(entry));
    entry.libraryName = TestProvMgr_LibraryName;

    setupStruct->msg->targetType = SUBSCRIP_TARGET_UNSUPPORTED;

    data.self = &s_provmgr;
    data.provRegEntry = &entry;

    Strand_Open(&setupStruct->leftSideStrand,ProvMgr_OpenCallback,&data,&setupStruct->msg->base.base,MI_TRUE);

    NitsAssert( SUBSCRIP_TARGET_UNSUPPORTED == setupStruct->msg->targetType, PAL_T("Unexpected change to messsage") );
    
    // The result is returned in another thread, so it cannot be checked directly here
    setupStruct->expectedResult = MI_RESULT_FAILED;
}
NitsEndTest

NitsTest1(TestProvMgr_LifeSubscribe_NotSupported_If_Provider_Doesnt_Support_Message_Type, TestProvMgr_SetupLifecycle, NitsEmptyValue)
{
    ProvMgr_OpenCallbackData data;
    TestProvMgr_SetupStruct* setupStruct = NitsContext()->_TestProvMgr_SetupLifecycle->_TestProvMgr_SetupProvider->_TestProvMgr_SetupStruct;
    ProvRegEntry entry;

    memset(&entry, 0, sizeof(entry));
    entry.libraryName = TestProvMgr_LibraryName;

    // Set subscribe request to ask for CREATE
    setupStruct->msg->targetType = SUBSCRIP_TARGET_LIFECYCLE_CREATE;

    // Set provider to ONLY support DELETE
    NitsAssert( MI_RESULT_OK == MI_LifecycleIndicationContext_SetSupportedTypes( g_testLifecycleContext, MI_LIFECYCLE_INDICATION_DELETE ), PAL_T("Setting DELETE failed") );
    NitsAssert( MI_FALSE == setupStruct->callbackCalled, PAL_T("Callback not called during SetSupportedTypes") );

    // Run test
    data.self = &s_provmgr;
    data.provRegEntry = &entry;
    Strand_Open(&setupStruct->leftSideStrand,ProvMgr_OpenCallback,&data,&setupStruct->msg->base.base,MI_TRUE);

    // The result is returned in another thread, so it cannot be checked directly here
    setupStruct->expectedResult = MI_RESULT_NOT_SUPPORTED;
}
NitsEndTest

//
// Initializes a CIM_InstCreation object that was created on the stack.
// It should be freed with MI_Instance_Destruct.
//
MI_Result _ConstructTestIndication(
    Test_Indication* indication )
{
    MI_Instance* instance = &indication->__instance;
    if (NitsAssert( MI_RESULT_OK == Instance_Construct( instance, &g_dummyTestClassDecl, NULL ), PAL_T("Unable to create instance") ))
    {
        /* MI_ConstStringField IndicationIdentifier */
        MI_Value value;
        value.string = (MI_Char*)PAL_T("DummyInstanceCreatedForEaseOfTesting");
        NitsAssert( MI_RESULT_OK == MI_Instance_SetElement( instance, PAL_T("Identifier"), &value, MI_STRING, 0 ), PAL_T("Unable to set identifier") );

        return MI_RESULT_OK;
    }
    else
    {
        return MI_RESULT_FAILED;
    }
}

//
// This is a "Happy Path" test case that verifies that once a subscription 
// succeeds, the provider is notified of the new indication type, a msg gets
// posted to the upper layers, and an indication gets processed properly.
//
NitsTest1(TestProvMgr_LifeSubscribe_Success, TestProvMgr_SetupLifecycle, NitsEmptyValue)
{
    ProvMgr_OpenCallbackData data;
    TestProvMgr_SetupStruct* setupStruct = NitsContext()->_TestProvMgr_SetupLifecycle->_TestProvMgr_SetupProvider->_TestProvMgr_SetupStruct;
    ProvRegEntry entry;

    memset(&entry, 0, sizeof(entry));
    entry.libraryName = TestProvMgr_LibraryName;

    setupStruct->msg->targetType = SUBSCRIP_TARGET_LIFECYCLE_CREATE;

    _InitializeTestProvMgrSemaphore();

    data.self = &s_provmgr;
    data.provRegEntry = &entry;
    Strand_Open(&setupStruct->leftSideStrand,ProvMgr_OpenCallback,&data,&setupStruct->msg->base.base,MI_TRUE);

    NitsAssert( MI_RESULT_OK == testProvMgr_MsgResult,
        PAL_T("Expected success"));

    //
    // Wait for the subscribe handler to complete on a separate thread.
    // Resume once done.
    //
    while ( Atomic_Read( &g_requesthandler.running ) == 1 )
    {
        Sleep_Milliseconds( 10 );
    }
    RequestHandler_Finalize(&g_requesthandler);

    // Re-initialize it for handling unsubscribe later.
    RequestHandler_Init(&g_requesthandler);

    // Verify subscribe succeeded
    NitsAssert( MI_RESULT_OK == testProvMgr_MsgResult, PAL_T("Expected an OK PostResult") );

    // Verify that it notified the provider
    NitsAssert( MI_TRUE == setupStruct->callbackCalled, PAL_T("Callback call required since it is specified") );
    NitsAssert( MI_LIFECYCLE_INDICATION_CREATE == setupStruct->typesFromCallback, PAL_T("Unexpected supported types") );

    // Post an indication and verify it is received by the other side of the strand
    Test_Indication instanceCreated;

    // This guarantees that the FT is NULL initially
    memset( &instanceCreated, 0, sizeof(Test_Indication) );
    
    NitsAssert( MI_RESULT_OK == _ConstructTestIndication(&instanceCreated), PAL_T("Unable to create simple instance to post") );
    
    NitsAssert( MI_RESULT_OK == MI_LifecycleIndicationContext_PostCreate( g_testLifecycleContext, &instanceCreated.__instance ), PAL_T("Expected Post success") );

    setupStruct->expectInstance = MI_TRUE;

    if (instanceCreated.__instance.ft)
    {
        MI_Instance_Destruct( &instanceCreated.__instance );
    }
}
NitsEndTest

//
// This simulates a provider posting an indication before a subscribe request
// has been received.
//
NitsTest1(TestProvMgr_LifeSubscribe_Post_Before_Subscribe, TestProvMgr_SetupLifecycle, NitsEmptyValue)
{
    TestProvMgr_SetupStruct* setupStruct = NitsContext()->_TestProvMgr_SetupLifecycle->_TestProvMgr_SetupProvider->_TestProvMgr_SetupStruct;

    // Verify PRE state
    NitsAssert( MI_FALSE == setupStruct->callbackCalled, PAL_T("Callback call required since it is specified") );
    NitsAssert( MI_LIFECYCLE_INDICATION_NONE == setupStruct->typesFromCallback, PAL_T("Unexpected supported types") );

    // Post an indication and verify it is NOT received by the other side of the strand
    Test_Indication instanceCreated;

    // This guarantees that the FT is NULL initially
    memset( &instanceCreated, 0, sizeof(Test_Indication) );
    
    NitsAssert( MI_RESULT_OK == _ConstructTestIndication(&instanceCreated), PAL_T("Unable to create simple instance to post") );
    
    NitsAssert( MI_RESULT_FAILED == MI_LifecycleIndicationContext_PostCreate( g_testLifecycleContext, &instanceCreated.__instance ), PAL_T("Expected Post success") );

    NitsAssert( MI_FALSE == testProvMgr_InstanceReceived, PAL_T("No instance expected") );
    setupStruct->expectInstance = MI_FALSE;

    if (instanceCreated.__instance.ft)
    {
        MI_Instance_Destruct( &instanceCreated.__instance );
    }
}
NitsEndTest

//
// This simulates a provider invoking PostCreate after notification of
// subscirption to MI_LIFECYCLE_INDICATION_DELETE.  This is a wrong post
// type test.
//
NitsTest1(TestProvMgr_LifeSubscribe_Post_To_Wrong_Type, TestProvMgr_SetupLifecycle, NitsEmptyValue)
{
    ProvMgr_OpenCallbackData data;
    TestProvMgr_SetupStruct* setupStruct = NitsContext()->_TestProvMgr_SetupLifecycle->_TestProvMgr_SetupProvider->_TestProvMgr_SetupStruct;
    ProvRegEntry entry;

    memset(&entry, 0, sizeof(entry));
    entry.libraryName = TestProvMgr_LibraryName;

    // Client subscribes to DELETE
    setupStruct->msg->targetType = SUBSCRIP_TARGET_LIFECYCLE_DELETE;

    _InitializeTestProvMgrSemaphore();

    data.self = &s_provmgr;
    data.provRegEntry = &entry;
    Strand_Open(&setupStruct->leftSideStrand,ProvMgr_OpenCallback,&data,&setupStruct->msg->base.base,MI_TRUE);

    NitsAssert( MI_RESULT_OK == testProvMgr_MsgResult,
        PAL_T("Expected success"));

    //
    // Wait for the subscribe handler to complete on a separate thread.
    // Resume once done.
    //
    while ( Atomic_Read( &g_requesthandler.running ) == 1 )
    {
        Sleep_Milliseconds( 10 );
    }
    RequestHandler_Finalize(&g_requesthandler);

    // Re-initialize it for handling unsubscribe later.
    RequestHandler_Init(&g_requesthandler);

    // Verify subscribe succeeded
    NitsAssert( MI_RESULT_OK == testProvMgr_MsgResult, PAL_T("Expected an OK PostResult") );

    // Verify that it notified the provider
    NitsAssert( MI_TRUE == setupStruct->callbackCalled, PAL_T("Callback call required since it is specified") );
    NitsAssert( MI_LIFECYCLE_INDICATION_DELETE == setupStruct->typesFromCallback, PAL_T("Unexpected supported types") );

    // Post an indication of the wrong type (CREATE) and verify it is NOT 
    // received by the other side of the strand
    Test_Indication instanceCreated;

    // This guarantees that the FT is NULL initially
    memset( &instanceCreated, 0, sizeof(Test_Indication) );
    
    NitsAssert( MI_RESULT_OK == _ConstructTestIndication(&instanceCreated), PAL_T("Unable to create simple instance to post") );
    
    NitsAssert( MI_RESULT_FAILED == MI_LifecycleIndicationContext_PostCreate( g_testLifecycleContext, &instanceCreated.__instance), PAL_T("Expected Post success") );

    NitsAssert( MI_FALSE == testProvMgr_InstanceReceived, PAL_T("No instance expected") );
    setupStruct->expectInstance = MI_FALSE;

    if (instanceCreated.__instance.ft)
    {
        MI_Instance_Destruct( &instanceCreated.__instance );
    }
}
NitsEndTest

//
// Unsubscribe / shutdown test:
//
// Strand_Cancel unsubscribes a subscription and updates the provider's active types.
// This is a simple test where there is only one subscription, so removing it should
// clear the provider's current callback types
//
NitsTest1(TestProvMgr_LifeSubscribe_StrandCancel_Removes_TargetType, TestProvMgr_SetupLifecycle, NitsEmptyValue)
{
    ProvMgr_OpenCallbackData data;
    TestProvMgr_SetupStruct* setupStruct = NitsContext()->_TestProvMgr_SetupLifecycle->_TestProvMgr_SetupProvider->_TestProvMgr_SetupStruct;
    ProvRegEntry entry;

    memset(&entry, 0, sizeof(entry));
    entry.libraryName = TestProvMgr_LibraryName;

    // Client subscribes to CREATE
    setupStruct->msg->targetType = SUBSCRIP_TARGET_LIFECYCLE_CREATE;

    _InitializeTestProvMgrSemaphore();

    data.self = &s_provmgr;
    data.provRegEntry = &entry;
    Strand_Open(&setupStruct->leftSideStrand,ProvMgr_OpenCallback,&data,&setupStruct->msg->base.base,MI_TRUE);

    NitsAssert( MI_RESULT_OK == testProvMgr_MsgResult,
        PAL_T("Expected success"));

    //
    // Wait for the subscribe handler to complete on a separate thread.
    // Resume once done.
    //
    while ( Atomic_Read( &g_requesthandler.running ) == 1 )
    {
        Sleep_Milliseconds( 10 );
    }
    RequestHandler_Finalize(&g_requesthandler);

    // Re-initialize it for handling unsubscribe later.
    RequestHandler_Init(&g_requesthandler);

    // Verify subscribe succeeded
    NitsAssert( MI_RESULT_OK == testProvMgr_MsgResult, PAL_T("Expected an OK SubscribeRes") );

    // Verify that it notified the provider
    NitsAssert( MI_TRUE == setupStruct->callbackCalled, PAL_T("Callback call required since it is specified") );
    NitsAssert( MI_LIFECYCLE_INDICATION_CREATE == setupStruct->typesFromCallback, PAL_T("Unexpected supported types") );

    // Reset globals to prepare for the unsubscribe action:
    testProvMgr_MsgResult = MI_RESULT_OK;
    setupStruct->callbackCalled = MI_FALSE;

    // Triggers the "unsubscribe" action by destroying the underlying
    // SubscriptionContext associated with the subscription.
    Strand_ScheduleCancel(&setupStruct->leftSideStrand);

    // Don't wait for it in the cleanup func.  The strand and context should 
    // be cleaned up immediately via the Strand_Cancel call (and wait for 
    // unsubscribe).
    _CleanupTestProvMgrSemaphore();

    //
    // Wait for the unsubscribe handler to complete on a separate thread.
    //
    while ( Atomic_Read( &g_requesthandler.running ) == 1 )
    {
        Sleep_Milliseconds( 10 );
    }
    RequestHandler_Finalize(&g_requesthandler);

    // Check to make sure that the expected actions took place and produced the
    // expected results:
    // 1. The provider is notified of the change in its subscriptions
    // 2. The context sends a PostResult to signify that the subscription is over.
    // 3. The SubscriptionManager is disabled because the last subscription has been removed
    NitsAssert( MI_TRUE == setupStruct->callbackCalled, PAL_T("Callback call required since it is specified") );
    NitsAssert( MI_LIFECYCLE_INDICATION_NONE == setupStruct->typesFromCallback, PAL_T("Unexpected supported types") );

    NitsAssert( MI_RESULT_OK == testProvMgr_MsgResult, PAL_T("Expected an OK PostResult") );
    NitsAssert( MI_FALSE == testProvMgr_InstanceReceived, PAL_T("No instance expected") );
}
NitsEndTest

// Other scenarios to test:
//
// Complete cleans up all subscriptions
// Subscribe AFTER complete occurs fails
// Complete while PostCreate pending occurs after post

#endif

