/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <ut/ut.h>
#include <MI.h>
#include <miapi/Application.h>
#include <pal/lock.h>
#include <pal/atomic.h>
#include <pal/sem.h>
#include <miapi/Options.h>
#include <tests/util/util.h>

extern "C"
{
MI_Result OperationOptions_MigrateOptions(
    _In_opt_ MI_OperationOptions *sourceOperation, 
    _Out_ MI_OperationOptions *destination);
}

struct _TestProtocolHandler
{
    const char *protocolHandlerName;
    const MI_Char *protocolHandlerName_w;
    const char *protocolHandlerDll;
    const char *protocolHandlerEntryPoint;
};

const struct _TestProtocolHandler g_test1Transport =
{
    "Test1",
    PAL_T("Test1"),
#if defined(_MSC_VER)
    "test_miapi.dll",
#else
    "libtest_miapi." CONFIG_SHLIBEXT,
#endif
    "Test1_Application_Initialize"
} ;

const struct _TestProtocolHandler g_test2Transport =
{
    "Test2",
    PAL_T("Test2"),
#if defined(_MSC_VER)
    "test_miapi.dll",
#else
    "libtest_miapi." CONFIG_SHLIBEXT,
#endif
    "Test2_Application_Initialize"
} ;


MI_OperationCallback_ResponseType g_WriteErrorResponseType = MI_OperationCallback_ResponseType_Yes;
MI_OperationCallback_ResponseType g_PromptUserResponseType = MI_OperationCallback_ResponseType_Yes;

extern "C" MI_CONST MI_ClassDecl MyClass_rtti;

/* in order to link to test_util.lib */
Batch* g_batch;
FILE* g_logfile;
char* g_dirpath;

MI_Instance *TestCreateInstance(_Inout_ MI_Application *application, _In_z_ const MI_Char *className)
{
    MI_Instance *instance = NULL;
    if (NitsAssert(MI_Application_NewInstance(application, className, NULL, &instance) == MI_RESULT_OK, PAL_T("failed to create instance")))
    {
        MI_Value value;
        value.uint32 = 1;

        NitsAssert(MI_Instance_AddElement(instance, PAL_T("key"), &value, MI_UINT32, MI_FLAG_KEY)==MI_RESULT_OK, PAL_T("Failed to add property to instance"));
    }
    return instance;
}

extern "C" MI_Module* MI_MAIN_CALL MyProvFunction(MI_Server* server)
{
    return NULL;
}

struct RuntimeTestData
{
    const struct _TestProtocolHandler *transport;

    MI_Application application;
    MI_Session session;
    MI_Instance *testInstance;

    ptrdiff_t sessionCloseFinished;
    volatile ptrdiff_t operationFinished;
    MI_Result finialResult;

    ptrdiff_t session_writeErrorCount;
    ptrdiff_t session_writeMessageCount;

    ptrdiff_t instanceCount;
    ptrdiff_t classCount;
    ptrdiff_t indicationCount;
    ptrdiff_t methodCount;
    ptrdiff_t promptUserCount;
    ptrdiff_t writeErrorCount;
    ptrdiff_t writeMessageCount;
    ptrdiff_t writeProgressCount;
    ptrdiff_t streamedParameterCount;
};

// This function resets all counters/flags inside runtime test data
// it is called from beginning of test body for every test which uses this data
// Ideally it should not be required but since nits does not run setup fixtures during fault injection
// we need to initialize this data ourselves again in the body
// supporting running entire test including setup's is a TODO feature request for nits
extern "C" void ResetRuntimeTestData(struct RuntimeTestData *data)
{
    data->sessionCloseFinished = 0;
    data->operationFinished = 0;
    data->finialResult = MI_RESULT_OK;
    data->session_writeErrorCount = 0;
    data->session_writeMessageCount = 0;
    data->instanceCount = 0;
    data->classCount = 0;
    data->indicationCount = 0;
    data->methodCount = 0;
    data->promptUserCount = 0;
    data->writeErrorCount = 0;
    data->writeMessageCount = 0;
    data->writeProgressCount = 0;
    data->streamedParameterCount = 0;
}

NitsSetup0(BaseSetup, RuntimeTestData)
{
}
NitsEndSetup

struct RuntimeApplicationSetup
{
    const struct _TestProtocolHandler *transport;
};
struct RuntimeApplicationSetup g_RuntimeApplicationSetup_Test1 = { &g_test1Transport };
struct RuntimeApplicationSetup g_RuntimeApplicationSetup_Test2 = { &g_test2Transport };

NitsSetup1(SetupDefaultApplication, RuntimeApplicationSetup,
            BaseSetup, BaseSetupDefaults)
{
    MI_Application *application = &NitsContext()->_BaseSetup->_RuntimeTestData->application;
    const struct _TestProtocolHandler *transport = NitsContext()->_RuntimeApplicationSetup->transport;

    NitsContext()->_BaseSetup->_RuntimeTestData->transport = transport;

    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, application), MI_RESULT_OK, PAL_T("MI_Application_Initialize returns OK")))
    {
        if (NitsAssert(application->ft != NULL, PAL_T("MI_Application_Initialize returns object with function table")))
        {
            NitsCompare(Application_SetTestTransport(application, transport->protocolHandlerName, transport->protocolHandlerDll, transport->protocolHandlerEntryPoint, 1, 1, MI_TRUE, MI_TRUE), MI_RESULT_OK, PAL_T("Failed to set test transport"));
        }
    }
}
NitsEndSetup

NitsCleanup(SetupDefaultApplication)
{
    MI_Application *application = &NitsContext()->_BaseSetup->_RuntimeTestData->application;
    NitsCompare(MI_Application_Close(application), MI_RESULT_OK, PAL_T("Failed to close MI_Application"));
}
NitsEndCleanup


NitsSetup1(SetupDefaultSession, NitsEmptyStruct,
            BaseSetup, BaseSetupDefaults)
{
    MI_Application *application = &NitsContext()->_BaseSetup->_RuntimeTestData->application;
    MI_Session *session = &NitsContext()->_BaseSetup->_RuntimeTestData->session;
    const struct _TestProtocolHandler *transport = NitsContext()->_BaseSetup->_RuntimeTestData->transport;

    if (NitsCompare(MI_Application_NewSession(application, transport->protocolHandlerName_w, NULL, NULL, NULL, NULL, session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
        NitsAssert(session->ft != NULL, PAL_T("MI_Session function table should not be NULL")))
    {
    }
}
NitsEndSetup

NitsCleanup(SetupDefaultSession)
{
    MI_Session *session = &NitsContext()->_BaseSetup->_RuntimeTestData->session;
    NitsCompare(MI_Session_Close(session, NULL, NULL), MI_RESULT_OK, PAL_T("Failed to close MI_Session"));
}
NitsEndCleanup


struct SetupTestInstance_Data
{
    const MI_Char *className;
};

SetupTestInstance_Data g_SetupTestInstance_test = { PAL_T("test") };
SetupTestInstance_Data g_SetupTestInstance_DeliverResultDifferentThread = { PAL_T("DeliverResultDifferentThread") };
SetupTestInstance_Data g_SetupTestInstance_NoResult = { PAL_T("NoResult") };

NitsSetup1(SetupTestInstance, SetupTestInstance_Data,
            BaseSetup, BaseSetupDefaults)
{
    MI_Application *application = &NitsContext()->_BaseSetup->_RuntimeTestData->application;
    const MI_Char *className = NitsContext()->_SetupTestInstance_Data->className;
    NitsContext()->_BaseSetup->_RuntimeTestData->testInstance = TestCreateInstance(application, className);
}
NitsEndSetup

NitsCleanup(SetupTestInstance)
{
    MI_Instance *instance = NitsContext()->_BaseSetup->_RuntimeTestData->testInstance;
    NitsCompare(MI_Instance_Delete(instance), MI_RESULT_OK, PAL_T("Failed to delete instace"));
}
NitsEndCleanup

/*==========================================================================================*/
/*==========================================================================================*/
/*==========================================================================================*/
/*============================= MI_Application tests =======================================*/
/*==========================================================================================*/
/*==========================================================================================*/
/*==========================================================================================*/

/* Manually test successful MI_Application_Initialize and then close it */
NitsTest(MI_Application_Initialize_Success)
{
    MI_Application application = MI_APPLICATION_NULL;
    NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("MI_Application_Initialize returns OK"));
    NitsAssert(application.ft != NULL, PAL_T("MI_Application function table should not be NULL"));
    MI_Application_Close(&application);

    NitsCompare(MI_Application_Initialize(0, PAL_T("My application ID"), NULL, &application), MI_RESULT_OK, PAL_T("MI_Application_Initialize returns OK"));
    NitsAssert(application.ft != NULL, PAL_T("MI_Application function table should not be NULL"));
    MI_Application_Close(&application);
}
NitsEndTest

/* Test invalid parameters for MI_Application_Initialize */
NitsTest(MI_Application_Initialize_InvalidParameters)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Instance *extendedError = NULL;

#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
    NitsCompare(MI_Application_Initialize(0, NULL, NULL, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Application_Initialize returns INVALID_PARAMETER"));
    NitsCompare(MI_Application_Initialize(25, NULL, NULL, &application), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Application_Initialize returns INVALID_PARAMETER"));
    MI_Application_Close(&application);
    NitsCompare(MI_Application_InitializeV1(25, NULL, &extendedError, &application), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Application_Initialize returns INVALID_PARAMETER"));
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif
    if (extendedError)
    {
        MI_Instance_Delete(extendedError);
    }
    MI_Application_Close(&application);
}
NitsEndTest

/* Test invalid parameters for MI_Application_Close */
NitsTest(MI_Application_Close_InvalidParameters)
{
    MI_Application application = MI_APPLICATION_NULL;
    NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("MI_Application_Initialize returns OK"));
    NitsAssert(application.ft != NULL, PAL_T("MI_Application function table should not be NULL"));

    if (application.ft == NULL)
        NitsReturn;

    const MI_ApplicationFT * const copyFT = application.ft;

#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
    MI_Application_Close(NULL);
    application.ft->Close(NULL);
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif

    MI_Application_Close(&application);

    NitsAssert(application.ft == NULL, PAL_T("MI_Application function table should be NULL"));

#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
    copyFT->Close(&application);
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif
}
NitsEndTest

/*==========================================================================================*/
/*==========================================================================================*/
/*==========================================================================================*/
/*===================== MI_Application_NewHostedProvider tests =============================*/
/*==========================================================================================*/
/*==========================================================================================*/
/*==========================================================================================*/

/* Test success case for MI_Application_NewHostedProvider */
NitsTest1(MI_Application_NewHostedProvider_Success, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    MI_Application *application = &NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData->application;
    MI_HostedProvider hostedProvider = MI_HOSTEDPROVIDER_NULL;
    MI_Application parentApplication = MI_APPLICATION_NULL;

    if (NitsCompare(MI_Application_NewHostedProvider(application, PAL_T("root\\cimv2"), PAL_T("MyProvider"), MyProvFunction, NULL, &hostedProvider), MI_RESULT_OK, PAL_T("MI_Application_NewHostedProvider returns OK")))
    {
        MI_HostedProvider_GetApplication(&hostedProvider, &parentApplication);
        NitsAssert(application->ft == parentApplication.ft, PAL_T("function tables should be same"));
        NitsAssert(application->reserved1 == parentApplication.reserved1, PAL_T("reserved1 should be same"));
        NitsAssert(application->reserved2 == parentApplication.reserved2, PAL_T("reserved2 should be same"));
        MI_HostedProvider_Close(&hostedProvider);
    }
}
NitsEndTest

/* Test invalid parameter cases for MI_Application_NewHostedProvider */
NitsTest1(MI_Application_NewHostedProvider_InvalidParameters, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    MI_Application *application = &NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData->application;
    MI_HostedProvider hostedProvider = MI_HOSTEDPROVIDER_NULL;
    MI_Application parentApplication = MI_APPLICATION_NULL;

    NitsCompare(application->ft->NewHostedProvider(NULL, PAL_T("root\\cimv2"), PAL_T("MyProvider"), MyProvFunction, NULL, &hostedProvider), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Application_NewHostedProvider invalid parameter"));
    NitsCompare(application->ft->NewHostedProvider(application, NULL, PAL_T("MyProvider"), MyProvFunction, NULL, &hostedProvider), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Application_NewHostedProvider invalid parameter"));
    NitsCompare(application->ft->NewHostedProvider(application, PAL_T("root\\cimv2"), NULL, MyProvFunction, NULL, &hostedProvider), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Application_NewHostedProvider invalid parameter"));
    NitsCompare(application->ft->NewHostedProvider(application, PAL_T("root\\cimv2"), PAL_T("MyProvider"), NULL, NULL, &hostedProvider), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Application_NewHostedProvider invalid parameter"));
    NitsCompare(application->ft->NewHostedProvider(application, PAL_T("root\\cimv2"), PAL_T("MyProvider"), MyProvFunction, NULL, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("MI_Application_NewHostedProvider invalid parameter"));
        
        
    if (NitsCompare(application->ft->NewHostedProvider(application, PAL_T("root\\cimv2"), PAL_T("MyProvider"), MyProvFunction, NULL, &hostedProvider), MI_RESULT_OK, PAL_T("MI_Application_NewHostedProvider Succeeds")) &&
        NitsAssert(hostedProvider.ft != NULL, PAL_T("Failed to get function table")))
    {
#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6011)
#endif
        hostedProvider.ft->GetApplication(NULL, &parentApplication);
        hostedProvider.ft->GetApplication(&hostedProvider, NULL);
        hostedProvider.ft->Close(&hostedProvider);
        hostedProvider.ft->Close(NULL);
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif
    }
}
NitsEndTest

/*==========================================================================================*/
/*==========================================================================================*/
/*==========================================================================================*/
/*================================= MI_Session tests =======================================*/
/*==========================================================================================*/
/*==========================================================================================*/
/*==========================================================================================*/

/* Test creation of a session, then close it synchronously */
NitsTest1(MI_Application_NewSession_Success_CloseSync, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    MI_Application *application = &NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData->application;
    MI_Session session = MI_SESSION_NULL;

    NitsCompare(MI_Application_NewSession(application, PAL_T("Test1"), NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK"));
    NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL"));

    MI_Session_Close(&session, NULL, NULL);
}
NitsEndTest

/* Test creation of session, then close asynchronously */
extern "C" void MI_CALL Test_Sesson_CloseAync_Callback(void *context)
{
    ptrdiff_t *wait = (ptrdiff_t*) context;
    *wait = 1;
    CondLock_Broadcast((ptrdiff_t) &wait);
}

NitsTest1(MI_Application_NewSession_Success_CloseAsync, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    MI_Application *application = &NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData->application;
    MI_Session session = MI_SESSION_NULL;
    volatile ptrdiff_t wait = 0;

    NitsCompare(MI_Application_NewSession(application, PAL_T("Test1"), NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK"));
    NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL"));

    MI_Session_Close(&session, (void*) &wait, Test_Sesson_CloseAync_Callback);
    
    ptrdiff_t currentWait = wait;
    while (!currentWait)
    {
        CondLock_Wait((ptrdiff_t)&wait, &wait, currentWait, CONDLOCK_DEFAULT_SPINCOUNT);
        currentWait = wait;
    }
}
NitsEndTest

/* Test creation of session with destination options */
NitsTest1(MI_Application_NewSession_Success_Options, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    MI_Application *application = &NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData->application;
    MI_Session session = MI_SESSION_NULL;
    MI_DestinationOptions options = MI_DESTINATIONOPTIONS_NULL;

    if (NitsCompare(MI_Application_NewDestinationOptions(application, &options), MI_RESULT_OK, PAL_T("NewDestinationOptions should succeed")))
    {
        if (NitsAssert(options.ft != NULL, PAL_T("Should have options function table")))
        {
            MI_UserCredentials creds = { 0 };
            creds.authenticationType = MI_AUTH_TYPE_BASIC;
            creds.credentials.usernamePassword.username = PAL_T("username");
            creds.credentials.usernamePassword.domain = PAL_T("domain");
            creds.credentials.usernamePassword.password = PAL_T("password");

            NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
            NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
            NitsCompare(options.ft->AddCredentials(&options, PAL_T("option3"), &creds, 0), MI_RESULT_OK, PAL_T("AddCredentials should work"));

            NitsCompare(MI_Application_NewSession(application, PAL_T("Test1"), NULL, &options, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK"));
            NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL"));

            MI_Session_Close(&session, NULL, NULL);
        }
        MI_DestinationOptions_Delete(&options);
    }
}
NitsEndTest

/* test session creation with a destination machine name */
NitsTest1(MI_Application_NewSession_WithRemoteMachine, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    MI_Application *application = &NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData->application;
    MI_Session session = MI_SESSION_NULL;

    NitsCompare(MI_Application_NewSession(application, PAL_T("Test1"), PAL_T("destination"), NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK"));
    NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL"));

    MI_Session_Close(&session, NULL, NULL);
}
NitsEndTest

/* test session creation with invalid parameters */
NitsTest1(MI_Application_NewSession_InvalidParameters, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    MI_Application *application = &NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData->application;
    MI_Session session = MI_SESSION_NULL;

    NitsCompare(application->ft->NewSession(NULL, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_INVALID_PARAMETER, PAL_T("NewSession should fail due to null application"));
    MI_Session_Close(&session, NULL, NULL);

    NitsCompare(application->ft->NewSession(application, NULL, NULL, NULL, NULL, NULL, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("NewSession should fail due to null session"));
}
NitsEndTest

extern "C" void MI_CALL Application_NewSession_PSSemantics_writeMessage(
    _In_     MI_Application *application,
    _In_opt_ void *callbackContext, 
                MI_Uint32 channel,
    _In_z_   const MI_Char *  message)
{
    NitsAssert(application != NULL, PAL_T("session_writeMessage: application null"));
    NitsAssert(message != NULL, PAL_T("session_writeMessage: message null"));
}

extern "C" void MI_CALL Application_NewSession_PSSemantics_writeError(
    _In_     MI_Application *application,
    _In_opt_ void *callbackContext, 
    _In_ MI_Instance *instance)
{
    NitsAssert(application != NULL, PAL_T("session_writeMessage: application null"));
}

NitsTest1(Application_NewSession_PSSemantics, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    MI_Application *application = &NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData->application;
    MI_Session session = MI_SESSION_NULL;
    MI_SessionCallbacks callbacks = MI_SESSIONCALLBACKS_NULL;
    callbacks.writeError = Application_NewSession_PSSemantics_writeError;
    callbacks.writeMessage = Application_NewSession_PSSemantics_writeMessage;


    if(NitsCompare(application->ft->NewSession(application, PAL_T("Test1"), NULL, NULL, &callbacks, NULL, &session), MI_RESULT_OK, PAL_T("NewSession should succeed")))
    {
        MI_Session_Close(&session, NULL, NULL);
    }
}
NitsEndTest

NitsTest1(MI_Session_GetParent, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    MI_Application *application = &NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData->application;
    MI_Application testApplication = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;

    if (NitsCompare(MI_Application_NewSession(application, PAL_T("Test1"), NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")))
    {
        NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL"));

        MI_Session_GetApplication(&session, &testApplication);

        NitsAssert(memcmp(application, &testApplication, sizeof(MI_Application))==0, PAL_T("applications should be same"));

        MI_Session_Close(&session, NULL, NULL);
    }
}
NitsEndTest

/*==========================================================================================*/
/*==========================================================================================*/
/*==========================================================================================*/
/*======================= MI_Application_NewInstance tests =================================*/
/*==========================================================================================*/
/*==========================================================================================*/
/*==========================================================================================*/

NitsTest1(MI_Application_NewInstance_Success, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    MI_Application *application = &NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData->application;
    MI_Instance *instance;

    instance = TestCreateInstance(application, PAL_T("MyClass"));
    if (NitsAssert(instance!=NULL, PAL_T("MI_Application_NewInstance should succeed")))
    {
        NitsAssert(instance->ft != NULL, PAL_T("MI_instance function table should not be NULL"));

        MI_Instance_Delete(instance);
    }
}
NitsEndTest

NitsTest1(MI_Application_NewInstance_WithRTTI_Success, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    MI_Application *application = &NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData->application;
    MI_Instance *instance = NULL;

    if (NitsCompare(MI_Application_NewInstance(application, PAL_T("MyClass"), &MyClass_rtti, &instance), MI_RESULT_OK, PAL_T("MI_Application_NewInstance returns OK")))
    {
        NitsAssert(instance->ft != NULL, PAL_T("MI_instance function table should not be NULL"));

        MI_Instance_Delete(instance);
    }
}
NitsEndTest

NitsTest1(MI_Application_NewInstance_InvalidParameters, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    MI_Application *application = &NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData->application;
    MI_Instance *instance;

    NitsCompare(application->ft->NewInstance(NULL, PAL_T("MyClass"), NULL, &instance), MI_RESULT_INVALID_PARAMETER, PAL_T("NewInstance should fail due to null application"));
    NitsCompare(application->ft->NewInstance(application, NULL, NULL, &instance), MI_RESULT_INVALID_PARAMETER, PAL_T("NewInstance should fail due to null class name"));
    NitsCompare(application->ft->NewInstance(application, PAL_T("MyClass"), NULL, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("NewInstance should fail due to null instance"));
}
NitsEndTest


/*==========================================================================================*/
/*==========================================================================================*/
/*==========================================================================================*/
/*================== MI_Application_NewDestinationOptions tests ============================*/
/*==========================================================================================*/
/*==========================================================================================*/
/*==========================================================================================*/

NitsTest1(MI_Application_NewDestinationOptions_All, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    MI_Application *application = &NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData->application;
    MI_DestinationOptions options = MI_DESTINATIONOPTIONS_NULL;
        
#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
    NitsCompare(MI_Application_NewDestinationOptions(NULL, &options), MI_RESULT_INVALID_PARAMETER, PAL_T("NewDestinationOptions invalid parameter"));
    NitsCompare(MI_Application_NewDestinationOptions(application, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("NewDestinationOptions invalid parameter"));
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif

    if (NitsCompare(MI_Application_NewDestinationOptions(application, &options), MI_RESULT_OK, PAL_T("NewDestinationOptions should succeed")))
    {
        NitsAssert(options.ft != NULL, PAL_T("Should have options function table"));
        if (options.ft != NULL)
        {
            NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
            NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
            NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
            NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value22"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
            NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 22), MI_RESULT_INVALID_PARAMETER, PAL_T("SetString invalid parameter"));
            NitsCompare(options.ft->SetString(&options, PAL_T("option1"), NULL, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("SetString invalid parameter"));
            NitsCompare(options.ft->SetString(&options, NULL, PAL_T("value1"), 0), MI_RESULT_INVALID_PARAMETER, PAL_T("SetString invalid parameter"));
                
            NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 33, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
            NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
            NitsCompare(options.ft->SetNumber(&options, NULL, 22, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("SetNumber invalid parameter"));
            NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 22), MI_RESULT_INVALID_PARAMETER, PAL_T("SetNumber invalid parameter"));
                
            {
                NitsCompare(options.ft->AddCredentials(&options, PAL_T("option3"), NULL, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("AddCredentials should fail"));
            }
            {
                MI_UserCredentials creds = { MI_AUTH_TYPE_BASIC, {{ PAL_T("domain"), NULL, PAL_T("password") } }};
                NitsCompare(options.ft->AddCredentials(&options, PAL_T("option3"), &creds, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("AddCredentials invalid parameter"));
            }
            {
                MI_UserCredentials creds = { MI_AUTH_TYPE_BASIC, { { PAL_T("domain"), PAL_T("username"), PAL_T("password") } } };
                NitsCompare(options.ft->AddCredentials(&options, PAL_T("option3"), &creds, 0), MI_RESULT_OK, PAL_T("AddCredentials should work"));
            }
            {
                MI_UserCredentials creds = { MI_AUTH_TYPE_BASIC, {{ PAL_T("domain2"), PAL_T("username2"), PAL_T("password2") }} };
                NitsCompare(options.ft->AddCredentials(&options, PAL_T("option3"), &creds, 0), MI_RESULT_FAILED, PAL_T("AddCredentials should fail because namne and type already exist"));
            }
            {
                MI_UserCredentials creds = { MI_AUTH_TYPE_BASIC, {{ PAL_T("domain"), PAL_T("username"), PAL_T("password") }} };
                NitsCompare(options.ft->AddCredentials(&options, NULL, &creds, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("AddCredentials invalid parameter"));
            }
            {
                MI_UserCredentials creds = { NULL, {{ PAL_T("domain"), PAL_T("username"), PAL_T("password") } }};
                NitsCompare(options.ft->AddCredentials(&options, PAL_T("option3"), &creds, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("AddCredentials invalid parameter"));
            }
            {
                MI_UserCredentials creds = { MI_AUTH_TYPE_BASIC, {{ NULL, PAL_T("username"), PAL_T("password") }} };
                NitsCompare(options.ft->AddCredentials(&options, PAL_T("option5"), &creds, 0), MI_RESULT_OK, PAL_T("AddCredentials should work"));
            }
            {
                MI_UserCredentials creds = { MI_AUTH_TYPE_BASIC, {{ PAL_T("domain"), PAL_T("username"), NULL }} };
                NitsCompare(options.ft->AddCredentials(&options, PAL_T("option4"), &creds, 0), MI_RESULT_OK, PAL_T("AddCredentials should work"));
            }
            {
                MI_UserCredentials creds = { MI_AUTH_TYPE_BASIC, {{ PAL_T("domain"), PAL_T("username"), PAL_T("password") } }};
                NitsCompare(options.ft->AddCredentials(&options, PAL_T("option3"), &creds, 22), MI_RESULT_INVALID_PARAMETER, PAL_T("AddCredentials invalid parameter"));
            }
            options.ft->Delete(NULL);

            MI_DestinationOptions_Delete(&options);
        }
    }
}
NitsEndTest

/*==========================================================================================*/
/*==========================================================================================*/
/*==========================================================================================*/
/*==================== MI_Application_NewOperationOptions tests ============================*/
/*==========================================================================================*/
/*==========================================================================================*/
/*==========================================================================================*/

NitsTest1(MI_Application_NewOperationOptions_All, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    MI_Application *application = &NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData->application;
    MI_OperationOptions options = MI_DESTINATIONOPTIONS_NULL;
    MI_OperationOptions newOptions = MI_DESTINATIONOPTIONS_NULL;

#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
    NitsCompare(MI_Application_NewOperationOptions(NULL, MI_FALSE, &options), MI_RESULT_INVALID_PARAMETER, PAL_T("NewOperationOptions invalid parameter"));
    NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("NewOperationOptions invalid parameter"));
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif

    if (NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, &options), MI_RESULT_OK, PAL_T("NewOperationOptions should succeed")))
    {
        NitsAssert(options.ft != NULL, PAL_T("Should have options function table"));
        if (options.ft != NULL)
        {
            NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
            NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value2"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
            NitsCompare(options.ft->SetString(&options, NULL, PAL_T("value1"), 0), MI_RESULT_INVALID_PARAMETER, PAL_T("SetString invalid parameter"));
            NitsCompare(options.ft->SetString(&options, PAL_T("option1"), NULL, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("SetString invalid parameter"));
            NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 22), MI_RESULT_INVALID_PARAMETER, PAL_T("SetString invalid parameter"));

            NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
            NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 33, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
            NitsCompare(options.ft->SetNumber(&options, NULL, 22, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("SetNumber invalid parameter"));
            NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 22), MI_RESULT_INVALID_PARAMETER, PAL_T("SetNumber invalid parameter"));

            {
                MI_Uint8 valueArray[2];
                MI_Value value;
                value.uint8 = 10;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("uint8"), MI_UINT8, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(uint8) should work"));

                valueArray[0] = 10;
                valueArray[1] = 20;
                value.uint8a.data = valueArray;
                value.uint8a.size = 2;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("uint8a"), MI_UINT8A, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(uint8a) should work"));
            }
            {
                MI_Sint8 valueArray[2];
                MI_Value value;
                value.sint8 = -10;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("sint8"), MI_SINT8, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(sint8) should work"));

                valueArray[0] = -10;
                valueArray[1] = -20;
                value.sint8a.data = valueArray;
                value.sint8a.size = 2;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("sint8a"), MI_SINT8A, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(sint8a) should work"));
            }
            {
                MI_Boolean valueArray[2];
                MI_Value value;
                value.boolean = MI_TRUE;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("boolean"), MI_BOOLEAN, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(boolean) should work"));

                valueArray[0] = MI_TRUE;
                valueArray[1] = MI_FALSE;
                value.booleana.data = valueArray;
                value.booleana.size = 2;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("booleana"), MI_BOOLEANA, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(booleana) should work"));
            }
            {
                MI_Uint16 valueArray[2];
                MI_Value value;
                value.uint16 = 20;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("uint16"), MI_UINT16, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(uint16) should work"));

                valueArray[0] = 20;
                valueArray[1] = 40;
                value.uint16a.data = valueArray;
                value.uint16a.size = 2;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("uint16a"), MI_UINT16A, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(uint16a) should work"));
            }
            {
                MI_Sint16 valueArray[2];
                MI_Value value;
                value.sint16 = -20;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("sint16"), MI_SINT16, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(sint16) should work"));

                valueArray[0] = -20;
                valueArray[1] = -40;
                value.sint16a.data = valueArray;
                value.sint16a.size = 2;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("sint16a"), MI_SINT16A, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(sint16a) should work"));
            }
            {
                MI_Char16 valueArray[2];
                MI_Value value;
                value.char16 = L'a';
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("char16"), MI_CHAR16, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(char16) should work"));

                valueArray[0] = L'a';
                valueArray[1] = L'b';
                value.char16a.data = valueArray;
                value.char16a.size = 2;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("char16a"), MI_CHAR16A, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(char16a) should work"));
            }
            {
                MI_Uint32 valueArray[2];
                MI_Value value;
                value.uint32 = 32;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("uint32"), MI_UINT32, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(uint32) should work"));

                valueArray[0] = 32;
                valueArray[1] = 54;
                value.uint32a.data = valueArray;
                value.uint32a.size = 2;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("uint32a"), MI_UINT32A, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(uint32a) should work"));
            }
            {
                MI_Sint32 valueArray[2];
                MI_Value value;
                value.sint32 = -32;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("sint32"), MI_SINT32, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(sint32) should work"));

                valueArray[0] = -32;
                valueArray[1] = -54;
                value.sint32a.data = valueArray;
                value.sint32a.size = 2;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("sint32a"), MI_SINT32A, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(sint32a) should work"));
            }
            {
                MI_Real32 valueArray[2];
                MI_Value value;
                value.real32 = 32.32f;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("real32"), MI_REAL32, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(real32) should work"));

                valueArray[0] = 32.32f;
                valueArray[1] = -32.32f;
                value.real32a.data = valueArray;
                value.real32a.size = 2;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("real32a"), MI_REAL32A, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(real32a) should work"));
            }
            {
                MI_Real64 valueArray[2];
                MI_Value value;
                value.real64 = 64.64;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("real64"), MI_REAL64, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(real64) should work"));

                valueArray[0] = 64.64;
                valueArray[1] = -64.64;
                value.real64a.data = valueArray;
                value.real64a.size = 2;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("real64a"), MI_REAL64A, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(real64a) should work"));
            }
            {
                MI_Uint64 valueArray[2];
                MI_Value value;
                value.uint64 = 64;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("uint64"), MI_UINT64, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(uint64) should work"));

                valueArray[0] = 64;
                valueArray[1] = 64;
                value.uint64a.data = valueArray;
                value.uint64a.size = 2;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("uint64a"), MI_UINT64A, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(uint64a) should work"));
            }
            {
                MI_Sint64 valueArray[2];
                MI_Value value;
                value.sint64 = -64;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("sint64"), MI_SINT64, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(sint64) should work"));

                valueArray[0] = 64;
                valueArray[1] = -64;
                value.sint64a.data = valueArray;
                value.sint64a.size = 2;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("sint64a"), MI_SINT64A, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(sint64a) should work"));
            }
            {
                MI_Datetime valueArray[2];
                MI_Value value;
                value.datetime.isTimestamp = MI_TRUE;
                value.datetime.u.timestamp.day = 11;
                value.datetime.u.timestamp.hour = 13;
                value.datetime.u.timestamp.microseconds = 323;
                value.datetime.u.timestamp.minute = 55;
                value.datetime.u.timestamp.month = 10;
                value.datetime.u.timestamp.second = 43;
                value.datetime.u.timestamp.utc = 8;
                value.datetime.u.timestamp.year = 2010;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("datetime"), MI_DATETIME, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(datetime) should work"));

                valueArray[0].isTimestamp = MI_TRUE;
                valueArray[0].u.timestamp.day = 11;
                valueArray[0].u.timestamp.hour = 13;
                valueArray[0].u.timestamp.microseconds = 323;
                valueArray[0].u.timestamp.minute = 55;
                valueArray[0].u.timestamp.month = 10;
                valueArray[0].u.timestamp.second = 43;
                valueArray[0].u.timestamp.utc = 8;
                valueArray[0].u.timestamp.year = 2010;
                valueArray[1].isTimestamp = MI_TRUE;
                valueArray[1].u.timestamp.day = 11;
                valueArray[1].u.timestamp.hour = 13;
                valueArray[1].u.timestamp.microseconds = 323;
                valueArray[1].u.timestamp.minute = 55;
                valueArray[1].u.timestamp.month = 10;
                valueArray[1].u.timestamp.second = 43;
                valueArray[1].u.timestamp.utc = 8;
                valueArray[1].u.timestamp.year = 2010;
                value.datetimea.data = valueArray;
                value.datetimea.size = 2;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("datetimea"), MI_DATETIMEA, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(datetimea) should work"));
            }
            {
                const MI_Char *valueArray[3];
                MI_Value value;
                value.string = (MI_Char*) PAL_T("Hello world");
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("string"), MI_STRING, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(string) should work"));

                valueArray[0] = PAL_T("Hello world");
                valueArray[1] = PAL_T("Goodbye");
                valueArray[2] = PAL_T("Good night");
                value.stringa.data = (MI_Char**)valueArray;
                value.stringa.size = 3;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("stringa"), MI_STRINGA, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(stringa) should work"));
            }
                
            /*============================================*/
                
            {
                MI_Value value;
                value.string = (MI_Char*)PAL_T("Hello world");
                NitsCompare(options.ft->SetCustomOption(&options, NULL, MI_STRING, &value, MI_FALSE, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("SetCustomOption(string ) should fail due to invalid parameter"));
            }
            NitsCompare(options.ft->SetCustomOption(&options, PAL_T("option3_invalid1"), MI_STRING, NULL, MI_FALSE, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("SetCustomString invalid parameter"));
            {
                MI_Value value;
                value.string = (MI_Char*)PAL_T("Hello world");
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("string_invalid2 "), MI_STRING, &value, MI_FALSE, 22), MI_RESULT_INVALID_PARAMETER, PAL_T("SetCustomOption(string ) should fail due to invalid flags"));
            }
            {
                MI_Value value;
                value.string = (MI_Char*)PAL_T("Hello world");
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("uint8"), MI_STRING, &value, MI_FALSE, 0), MI_RESULT_TYPE_MISMATCH, PAL_T("SetCustomOption(string ) should fail due to duplicate item existing with different type"));
            }
            {
                MI_Value value;
                value.uint8 = 10;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("uint8"), MI_UINT8, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(uint8) should succeed even when option already exists"));
            }

            NitsCompare(options.ft->SetNumber(&options, PAL_T("option1"), 22, 0), MI_RESULT_TYPE_MISMATCH, PAL_T("SetNumber should fail due to changing type of option"));
            NitsCompare(options.ft->SetString(&options, PAL_T("option2"), PAL_T("value2"), 0), MI_RESULT_TYPE_MISMATCH, PAL_T("SetString should fail due to changing type of option"));

            if (NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, &newOptions), MI_RESULT_OK, PAL_T("NewOperationOptions should succeed")))
            {
                NitsCompare(OperationOptions_MigrateOptions(&options, &newOptions), MI_RESULT_OK, PAL_T("Migration should succeed"));
                MI_OperationOptions_Delete(&newOptions);
            }
            options.ft->Delete(NULL);

            MI_OperationOptions_Delete(&options);
        }
    }
}
NitsEndTest

extern "C" void MI_CALL GetInstanceResult_Fail(
    _In_     MI_Operation *operation,
    _In_     void *callbackContext, 
    _In_opt_ const MI_Instance *instance,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char * errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    RuntimeTestData *runtimeData = (RuntimeTestData *)callbackContext;
    NitsAssert(resultCode!= MI_RESULT_OK, PAL_T("should get error"));
    NitsAssert(instance==NULL, PAL_T("Should not have result instance"));
    if (resultAcknowledgement)
    {
        resultAcknowledgement(operation);
    }
    if (!moreResults)
    {
        MI_Operation_Close(operation);

        runtimeData->finialResult = resultCode;
        runtimeData->operationFinished = MI_TRUE;

        CondLock_Broadcast((ptrdiff_t) callbackContext);
    }
}
extern "C" void MI_CALL GetClassResult_Fail(
    _In_     MI_Operation *operation,
    _In_     void *callbackContext, 
    _In_opt_ const MI_Class *className,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char * errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    RuntimeTestData *runtimeData = (RuntimeTestData *)callbackContext;
    NitsAssert(resultCode!= MI_RESULT_OK, PAL_T("should get error"));
    NitsAssert(className==NULL, PAL_T("Should not have result instance"));
    if (resultAcknowledgement)
    {
        resultAcknowledgement(operation);
    }
    if (!moreResults)
    {
        MI_Operation_Close(operation);

        runtimeData->finialResult = resultCode;
        runtimeData->operationFinished = MI_TRUE;

        CondLock_Broadcast((ptrdiff_t) callbackContext);
    }
}

ptrdiff_t g_maximumInstanceCount = 1;

extern "C" void MI_CALL GetInstanceResult(
    _In_     MI_Operation *operation,
    _In_     void *callbackContext, 
    _In_opt_ const MI_Instance *instance,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char * errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    RuntimeTestData *runtimeData = (RuntimeTestData *)callbackContext;
    MI_Session session = MI_SESSION_NULL;
    NitsCompare(resultCode, MI_RESULT_OK, PAL_T("Error instance returned to client"));

    if (instance)
        Atomic_Inc(&runtimeData->instanceCount);

    if (g_maximumInstanceCount)
    {
        NitsAssert(instance!=NULL, PAL_T("Should have result instance"));
        if (!NitsAssert(runtimeData->instanceCount <=  g_maximumInstanceCount, PAL_T("too many results")))
        {
            /* try and kill the request early */
            moreResults = FALSE;
        }
    }

    if (resultAcknowledgement)
    {
        resultAcknowledgement(NULL);
        resultAcknowledgement(operation);
    }

    if (!moreResults)
    {
        /* Get parent session */
        MI_Operation_GetSession(operation, &session);

        /* Some invalid parameter validation */
        operation->ft->Cancel(NULL, MI_REASON_NONE);
        operation->ft->Close(NULL);

        MI_Operation_Close(operation);

        /* Cancel after close */
        MI_Operation_Cancel(operation, MI_REASON_NONE);
   
        /* Get results after closed */
        MI_Operation_GetInstance(operation, &instance, &moreResults, &resultCode, &errorString, &errorDetails);

        /* Get parent session after closed */
        MI_Operation_GetSession(operation, &session);

        runtimeData->finialResult = resultCode;
        runtimeData->operationFinished = MI_TRUE;

        CondLock_Broadcast((ptrdiff_t) callbackContext);

    }
}

extern "C" void MI_CALL GetIndicationResult(
    _In_     MI_Operation *operation,
    _In_     void *callbackContext, 
    _In_opt_ const MI_Instance *instance,
    _In_opt_ const MI_Char *bookmark,
    _In_opt_ const MI_Char *machineID,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char * errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    RuntimeTestData *runtimeData = (RuntimeTestData *)callbackContext;
    MI_Session session = MI_SESSION_NULL;
    NitsCompare(resultCode, MI_RESULT_OK, PAL_T("Error instance returned to client"));
    NitsAssert(instance!=NULL, PAL_T("Should have result instance"));

    if (resultAcknowledgement)
    {
        resultAcknowledgement(NULL);
        resultAcknowledgement(operation);
    }
    if (instance)
        Atomic_Inc(&runtimeData->indicationCount);

    if (!NitsAssert(runtimeData->indicationCount <=  g_maximumInstanceCount, PAL_T("too many results")))
    {
        /* try and kill the request early */
        moreResults = FALSE;
    }

    if (!moreResults)
    {
        /* Get parent session */
        MI_Operation_GetSession(operation, &session);

        /* Some invalid parameter validation */
        operation->ft->Cancel(NULL, MI_REASON_NONE);
        operation->ft->Close(NULL);

        MI_Operation_Close(operation);

        /* Cancel after close */
        MI_Operation_Cancel(operation, MI_REASON_NONE);
   
        /* Get results after closed */
        MI_Operation_GetIndication(operation, &instance, &bookmark, &machineID, &moreResults, &resultCode, &errorString, &errorDetails);

        /* Get parent session after closed */
        MI_Operation_GetSession(operation, &session);

        runtimeData->finialResult = resultCode;
        runtimeData->operationFinished = MI_TRUE;

        CondLock_Broadcast((ptrdiff_t) callbackContext);
    }
}
extern "C" void MI_CALL GetClassResult(
    _In_     MI_Operation *operation,
    _In_     void *callbackContext, 
    _In_opt_ const MI_Class *classResult,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char * errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    RuntimeTestData *runtimeData = (RuntimeTestData *)callbackContext;
    MI_Session session = MI_SESSION_NULL;
    NitsCompare(resultCode, MI_RESULT_OK, PAL_T("Error instance returned to client"));
    NitsAssert(classResult!=NULL, PAL_T("Should have result class"));

    if (resultAcknowledgement)
    {
        resultAcknowledgement(NULL);
        resultAcknowledgement(operation);
    }
    if (classResult)
        Atomic_Inc(&runtimeData->classCount);

    if (!NitsAssert(runtimeData->classCount <=  g_maximumInstanceCount, PAL_T("too many results")))
    {
        /* try and kill the request early */
        moreResults = FALSE;
    }

    if (!moreResults)
    {
        /* Get parent session */
        MI_Operation_GetSession(operation, &session);

        /* Some invalid parameter validation */
        operation->ft->Cancel(NULL, MI_REASON_NONE);
        operation->ft->Close(NULL);

        MI_Operation_Close(operation);

        /* Cancel after close */
        MI_Operation_Cancel(operation, MI_REASON_NONE);
   
        /* Get results after closed */
        MI_Operation_GetClass(operation, &classResult, &moreResults, &resultCode, &errorString, &errorDetails);

        /* Get parent session after closed */
        MI_Operation_GetSession(operation, &session);

        runtimeData->finialResult = resultCode;
        runtimeData->operationFinished = MI_TRUE;

        CondLock_Broadcast((ptrdiff_t) callbackContext);
    }
}

extern "C" void MI_CALL InvokeResult(
    _In_     MI_Operation *operation,
    _In_     void *callbackContext, 
    _In_opt_ const MI_Instance *instance,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char * errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    RuntimeTestData *runtimeData = (RuntimeTestData *)callbackContext;
    MI_Session session = MI_SESSION_NULL;
    NitsCompare(resultCode, MI_RESULT_OK, PAL_T("Error instance returned to client"));
    if (resultAcknowledgement)
    {
        resultAcknowledgement(NULL);
        resultAcknowledgement(operation);
    }

    if (instance)
        Atomic_Inc(&runtimeData->methodCount);

    if (!moreResults)
    {
        /* Get parent session */
        MI_Operation_GetSession(operation, &session);

        /* Some invalid parameter validation */
        operation->ft->Cancel(NULL, MI_REASON_NONE);
        operation->ft->Close(NULL);

        MI_Operation_Close(operation);

        /* Cancel after close */
        MI_Operation_Cancel(operation, MI_REASON_NONE);
   
        /* Get results after closed */
        MI_Operation_GetInstance(operation, &instance, &moreResults, &resultCode, &errorString, &errorDetails);

        /* Get parent session after closed */
        MI_Operation_GetSession(operation, &session);

        runtimeData->finialResult = resultCode;
        runtimeData->operationFinished = MI_TRUE;

        CondLock_Broadcast((ptrdiff_t) callbackContext);
    }
}

void WaitForOperationToComplete(RuntimeTestData *testData)
{
    ptrdiff_t operationFinished = testData->operationFinished;
    while (!operationFinished)
    {
        CondLock_Wait((ptrdiff_t)testData, &testData->operationFinished, operationFinished, CONDLOCK_DEFAULT_SPINCOUNT);
        operationFinished = testData->operationFinished;
    }
}

NitsTest3(MI_Session_GetInstance_Async_AutoAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{    
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 1;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult;

    MI_Session_GetInstance(session, 0, NULL, NULL, testInstance, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsAssert(testData->instanceCount == g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

NitsTest3(MI_Session_GetInstance_Async_ManualAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 1;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult;

    MI_Session_GetInstance(session, MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, NULL, NULL, testInstance, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsAssert(testData->instanceCount == g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

NitsTest3(MI_Session_GetInstance_Sync, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    const MI_Instance *resultInstance;
    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_GetInstance(session, 0, NULL, NULL, testInstance, NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation testInstance table null"));

    MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
    NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest2(MI_Session_GetInstance_Sync_WithOptions, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    MI_Instance *testInstance = testData->testInstance;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;

    MI_DestinationOptions destOptions = MI_DESTINATIONOPTIONS_NULL;
    if (NitsCompare(MI_Application_NewDestinationOptions(application, &destOptions), MI_RESULT_OK, PAL_T("create destoptions failed")))
    {
        MI_UserCredentials creds = { MI_AUTH_TYPE_BASIC, {{PAL_T("domain"), PAL_T("username"), PAL_T("password") }}};

        NitsCompare(destOptions.ft->SetString(&destOptions, PAL_T("option111"), PAL_T("value111"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
        NitsCompare(destOptions.ft->SetNumber(&destOptions, PAL_T("option222"), 22, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
        NitsCompare(destOptions.ft->AddCredentials(&destOptions, PAL_T("option333"), &creds, 0), MI_RESULT_OK, PAL_T("AddCredentials should work"));

        MI_OperationOptions options = MI_DESTINATIONOPTIONS_NULL;
        if (NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, &options), MI_RESULT_OK, PAL_T("NewOperationOptions should succeed")))
        {
            NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
            NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
            {
                MI_Value value;
                value.string = (MI_Char*) PAL_T("hello world");
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("option3"), MI_STRING, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomString should work"));
            }

            if (NitsCompare(MI_Application_NewSession(application, PAL_T("Test1"), NULL, &destOptions, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
                NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL")))
            {
                const MI_Instance *resultInstance;
                MI_Boolean moreResults;
                MI_Result result;
                const MI_Char *errorMessage;
                const MI_Instance *completionDetails;

                MI_Session_GetInstance(&session, 0, &options, NULL, testInstance, NULL, &operation);
                NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

                MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
                NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
                NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

                MI_Operation_Close(&operation);

                MI_Session_Close(&session, NULL, NULL);
            }
            MI_OperationOptions_Delete(&options);
        }
        MI_DestinationOptions_Delete(&destOptions);
    }
}
NitsEndTest

NitsTest3(MI_Session_GetInstance_Sync_ResultDeliverDifferentThread, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_DeliverResultDifferentThread)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;

    const MI_Instance *resultInstance;
    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_GetInstance(session, 0, NULL, NULL, testInstance, NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
    NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

    MI_Operation_Close(&operation);
}
NitsEndTest

extern "C" void MI_CALL MI_Session_GetInstance_Async_PS_Semantics_PromptUser(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext, 
    _In_z_   const MI_Char *message,
    MI_PromptType promptType,
    _In_     MI_Result (MI_CALL * promptUserResult)(_In_ MI_Operation *operation, 
                                                      MI_OperationCallback_ResponseType response))

{
    /* Do an invalid handle version */
    MI_Operation tmpOp = *operation;
    tmpOp.reserved1=0;
    if( promptUserResult)
    {
        promptUserResult(&tmpOp, MI_OperationCallback_ResponseType_Yes);
        promptUserResult(NULL, MI_OperationCallback_ResponseType_Yes);

        /* do valid handle */
        promptUserResult(operation, g_PromptUserResponseType);
    }

    RuntimeTestData *runtimeData = (RuntimeTestData *)callbackContext;
    Atomic_Inc(&runtimeData->promptUserCount);
}

extern "C" void MI_CALL MI_Session_GetInstance_Async_PS_Semantics_WriteError(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext, 
    _In_ MI_Instance *instance,
    _In_     MI_Result (MI_CALL * writeErrorResult)(_In_ MI_Operation *operation, MI_OperationCallback_ResponseType response))
{
    /* Do an invalid handle version */
    MI_Operation tmpOp = *operation;
    tmpOp.reserved1=0;
    if(writeErrorResult)
    {
        writeErrorResult(&tmpOp, MI_OperationCallback_ResponseType_Yes);
        writeErrorResult(NULL, MI_OperationCallback_ResponseType_Yes);

        /* do valid handle */
        writeErrorResult(operation, g_WriteErrorResponseType);
    }

    RuntimeTestData *runtimeData = (RuntimeTestData *)callbackContext;
    Atomic_Inc(&runtimeData->writeErrorCount);
}

extern "C" void MI_CALL MI_Session_GetInstance_Async_PS_Semantics_WriteMessage(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext, 
             MI_Uint32 channel,
    _In_z_   const MI_Char *message)
{
    RuntimeTestData *runtimeData = (RuntimeTestData *)callbackContext;
    Atomic_Inc(&runtimeData->writeMessageCount);
}

extern "C" void MI_CALL MI_Session_GetInstance_Async_PS_Semantics_WriteProgress(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext, 
    _In_z_   const MI_Char *activity,
    _In_z_   const MI_Char *currentOperation,
    _In_z_   const MI_Char *statusDescription,
             MI_Uint32 percentageComplete,
             MI_Uint32 secondsRemaining)
{
    RuntimeTestData *runtimeData = (RuntimeTestData *)callbackContext;
    Atomic_Inc(&runtimeData->writeProgressCount);
}

extern "C" void MI_CALL MI_Session_GetInstance_Async_PS_Semantics_Sesson_WriteMessage(
    _In_     MI_Application *application,
    _In_opt_ void *callbackContext, 
                MI_Uint32 channel,
    _In_z_   const MI_Char *  message)
{
    RuntimeTestData *runtimeData = (RuntimeTestData *)callbackContext;
    Atomic_Inc(&runtimeData->session_writeMessageCount);
}

extern "C" void MI_CALL MI_Session_GetInstance_Async_PS_Semantics_Sesson_WriteError(
    _In_     MI_Application *application,
    _In_opt_ void *callbackContext, 
    _In_ MI_Instance *instance)
{
    RuntimeTestData *runtimeData = (RuntimeTestData *)callbackContext;
    Atomic_Inc(&runtimeData->session_writeErrorCount);
}

extern "C" void MI_CALL _MI_OperationCallback_StreamedParameter(
    _In_ MI_Operation *operation,
    _In_ void *callbackContext,
    _In_z_ const MI_Char * parameterName,
    _In_ MI_Type resultType,
    _In_ const MI_Value *result,
    _In_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    if (resultAcknowledgement)
    {
        resultAcknowledgement(NULL);
        resultAcknowledgement(operation);
    }

    RuntimeTestData *runtimeData = (RuntimeTestData *)callbackContext;
    Atomic_Inc(&runtimeData->streamedParameterCount);
}

NitsTest3(MI_Session_GetInstance_Async_PS_Semantics, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Instance *testInstance = testData->testInstance;
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 1;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult;
    callbacks.promptUser = MI_Session_GetInstance_Async_PS_Semantics_PromptUser;
    callbacks.writeError = MI_Session_GetInstance_Async_PS_Semantics_WriteError;
    callbacks.writeMessage = MI_Session_GetInstance_Async_PS_Semantics_WriteMessage;
    callbacks.writeProgress = MI_Session_GetInstance_Async_PS_Semantics_WriteProgress;

    MI_Session_GetInstance(session, MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, NULL, NULL, testInstance, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    NitsAssert(testData->instanceCount == g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

NitsTest2(MI_Session_GetInstance_Sync_InvalidParameters, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    MI_Session session = MI_SESSION_NULL;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    const MI_Instance *result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    MI_Result returnValue;
    const MI_Char *errorMessage;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult_Fail;

    {
        if (NitsCompare(MI_Application_NewSession(application, PAL_T("Test1"), NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
            NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL")))
        {
            if (session.ft == NULL)
                NitsReturn;

            {
                session.ft->GetInstance(&session, 0, NULL, NULL, testInstance, NULL, &operation);
                MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
                NitsCompare(resultCode, MI_RESULT_OK, PAL_T("GetInstance should succeed"));

                returnValue = operation.ft->GetInstance(NULL, &result, NULL, &resultCode, NULL, NULL);
                NitsCompare(returnValue, MI_RESULT_INVALID_PARAMETER, PAL_T("Operation_GetInstance should fail due to NULL operation"));

                returnValue = operation.ft->GetInstance(&operation, NULL, NULL, &resultCode, NULL, NULL);
                NitsCompare(returnValue, MI_RESULT_INVALID_PARAMETER, PAL_T("Operation_GetInstance should fail due to NULL instance"));

                returnValue = operation.ft->GetInstance(&operation, NULL, NULL, NULL, NULL, NULL);
                NitsCompare(returnValue, MI_RESULT_INVALID_PARAMETER, PAL_T("Operation_GetInstance should fail due to NULL instance"));

                MI_Operation_Close(&operation);

                session.ft->GetInstance(NULL, 0, NULL, NULL, testInstance, NULL, &operation);
                MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
                NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetInstance should faul due to NULL session"));
                MI_Operation_Close(&operation);

                session.ft->GetInstance(&session, 0, NULL, NULL, NULL, NULL, &operation);
                MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
                NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetInstance should fail due to NULL instance key"));
                MI_Operation_Close(&operation);

                session.ft->GetInstance(&session, 0, NULL, NULL, testInstance, &callbacks, NULL);
                MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
                NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetInstance should fail due to null operation, has callbacks"));
                MI_Operation_Close(&operation);

                session.ft->GetInstance(&session, 0, NULL, NULL, testInstance, NULL, NULL);
                /* Validate it doesn't crash only as nowhere for failure to go */
            }
            MI_Session_Close(&session, NULL, NULL);

            session.ft->GetInstance(&session, 0, NULL, NULL, testInstance, NULL, &operation);
            MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
            NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetInstance should fail because session is already closed"));
            MI_Operation_Close(&operation);

        }
    }
}
NitsEndTest

NitsTest3(MI_Session_GetInstance_TransportNotSupported, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test2,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    const MI_Instance *resultInstance;
    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_GetInstance(session, 0, NULL, NULL, testInstance, NULL, &operation);

    MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_NOT_SUPPORTED, PAL_T("Operation should succeed"));
    NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest3(MI_Session_Invoke_Async_NonStatic, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 1;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = InvokeResult;

    MI_Session_Invoke(session, 0, NULL, NULL, PAL_T("testClass"), PAL_T("TestMethod"), testInstance, NULL, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->methodCount,  (MI_Uint32)g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

NitsTest2(MI_Session_Invoke_Async_Static, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 1;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = InvokeResult;

    MI_Session_Invoke(session, 0, NULL, NULL, PAL_T("testClass"), PAL_T("TestMethod"), NULL, NULL, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->methodCount,  (MI_Uint32)g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

NitsTest2(MI_Session_Invoke_Async_Static_PsSemantics, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 1;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = InvokeResult;
    callbacks.promptUser = MI_Session_GetInstance_Async_PS_Semantics_PromptUser;
    callbacks.writeError = MI_Session_GetInstance_Async_PS_Semantics_WriteError;
    callbacks.writeMessage = MI_Session_GetInstance_Async_PS_Semantics_WriteMessage;
    callbacks.writeProgress = MI_Session_GetInstance_Async_PS_Semantics_WriteProgress;

    MI_Session_Invoke(session, 0, NULL, NULL, PAL_T("testClass"), PAL_T("TestMethod"), NULL, NULL, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->methodCount, (MI_Uint32)g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
    NitsCompare((MI_Uint32)testData->writeErrorCount, 2, PAL_T("Correct PS semantic count"));
    NitsCompare((MI_Uint32)testData->writeMessageCount, 1, PAL_T("Correct PS semantic count"));
    NitsCompare((MI_Uint32)testData->writeProgressCount, 1, PAL_T("Correct PS semantic count"));
    NitsCompare((MI_Uint32)testData->promptUserCount, 2, PAL_T("Correct PS semantic count"));
}
NitsEndTest

NitsTest2(MI_Session_Invoke_Async_Static_StreamedParameter, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 1;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = InvokeResult;
    callbacks.promptUser = MI_Session_GetInstance_Async_PS_Semantics_PromptUser;
    callbacks.writeError = MI_Session_GetInstance_Async_PS_Semantics_WriteError;
    callbacks.writeMessage = MI_Session_GetInstance_Async_PS_Semantics_WriteMessage;
    callbacks.writeProgress = MI_Session_GetInstance_Async_PS_Semantics_WriteProgress;
    callbacks.streamedParameterResult = _MI_OperationCallback_StreamedParameter;

    MI_Session_Invoke(session, 0, NULL, NULL, PAL_T("testClass"), PAL_T("TestMethod"), NULL, NULL, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->methodCount, 0, PAL_T("Number of results callbacks received"));
    NitsCompare((MI_Uint32)testData->writeErrorCount, 2, PAL_T("Correct PS semantic count"));
    NitsCompare((MI_Uint32)testData->writeMessageCount, 1, PAL_T("Correct PS semantic count"));
    NitsCompare((MI_Uint32)testData->writeProgressCount, 1, PAL_T("Correct PS semantic count"));
    NitsCompare((MI_Uint32)testData->promptUserCount, 2, PAL_T("Correct PS semantic count"));
    NitsCompare((MI_Uint32)testData->streamedParameterCount, 5, PAL_T("Correct PS semantic count"));
}
NitsEndTest

NitsTest2(MI_Session_Invoke_Async_Static_StreamedParameter_ManualAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 1;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = InvokeResult;
    callbacks.promptUser = MI_Session_GetInstance_Async_PS_Semantics_PromptUser;
    callbacks.writeError = MI_Session_GetInstance_Async_PS_Semantics_WriteError;
    callbacks.writeMessage = MI_Session_GetInstance_Async_PS_Semantics_WriteMessage;
    callbacks.writeProgress = MI_Session_GetInstance_Async_PS_Semantics_WriteProgress;
    callbacks.streamedParameterResult = _MI_OperationCallback_StreamedParameter;

    MI_Session_Invoke(session, MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, NULL, NULL, PAL_T("testClass"), PAL_T("TestMethod"), NULL, NULL, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->methodCount, 0, PAL_T("Number of results callbacks received"));
    NitsCompare((MI_Uint32)testData->writeErrorCount, 2, PAL_T("Correct PS semantic count"));
    NitsCompare((MI_Uint32)testData->writeMessageCount, 1, PAL_T("Correct PS semantic count"));
    NitsCompare((MI_Uint32)testData->writeProgressCount, 1, PAL_T("Correct PS semantic count"));
    NitsCompare((MI_Uint32)testData->promptUserCount, 2, PAL_T("Correct PS semantic count"));
    NitsCompare((MI_Uint32)testData->streamedParameterCount, 5, PAL_T("Correct PS semantic count"));
}
NitsEndTest

NitsTest3(MI_Session_Invoke_Sync_Success, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    const MI_Instance *result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    const MI_Char *errorMessage;

    session->ft->Invoke(session, 0, NULL, NULL,  PAL_T("testClass"), PAL_T("TestMethod"), NULL, NULL, NULL, &operation);
    MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
    NitsCompare(resultCode, MI_RESULT_OK, PAL_T("Invoke should succeed"));
    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest3(MI_Session_Invoke_Sync_WithOptions, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    const MI_Instance *result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    const MI_Char *errorMessage;
    MI_OperationOptions options = MI_DESTINATIONOPTIONS_NULL;

    if (NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, &options), MI_RESULT_OK, PAL_T("NewOperationOptions should succeed")))
    {
        NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
        NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
        {
            MI_Value value;
            value.string = (MI_Char*) PAL_T("hello world");
            NitsCompare(options.ft->SetCustomOption(&options, PAL_T("option3"), MI_STRING, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomString should work"));
        }

        session->ft->Invoke(session, 0, &options, NULL,  PAL_T("testClass"), PAL_T("TestMethod"), NULL, NULL, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_OK, PAL_T("Invoke should succeed"));
        MI_Operation_Close(&operation);

        MI_OperationOptions_Delete(&options);
    }
}
NitsEndTest


NitsTest2(MI_Session_Invoke_Sync_InvalidParameters, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    const MI_Instance *result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    const MI_Char *errorMessage;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;

    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult_Fail;

    if (NitsCompare(MI_Application_NewSession(application, PAL_T("Test1"), NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
        NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL")))
    {
        if (session.ft == NULL)
            NitsReturn;

        session.ft->Invoke(&session, 0, NULL, NULL,  PAL_T("testClass"), PAL_T("TestMethod"), NULL, NULL, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_OK, PAL_T("Invoke should succeed"));
        MI_Operation_Close(&operation);

        session.ft->Invoke(&session, 11, NULL, NULL,  PAL_T("testClass"), PAL_T("TestMethod"), NULL, NULL, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_OK, PAL_T("Invoke should fail due to invalid flag"));
        MI_Operation_Close(&operation);

        session.ft->Invoke(NULL, 0, NULL, NULL, PAL_T("testClass"), PAL_T("TestMethod"), NULL, NULL, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("Invoke should fail due to invalid session"));
        MI_Operation_Close(&operation);

        session.ft->Invoke(&session, 0, NULL, NULL,  PAL_T("testClass"), NULL, NULL, NULL, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("Invoke should fail due to invalid method name"));

        operation.ft->GetInstance(NULL, &result, NULL, &resultCode, NULL, NULL);
        operation.ft->GetInstance(&operation, NULL, NULL, &resultCode, NULL, NULL);

        operation.ft->Close(NULL);
        MI_Operation_Close(&operation);

        session.ft->Invoke(&session, 0, NULL, NULL, PAL_T("testClass"), PAL_T("TestMethod"), NULL, NULL, &callbacks, NULL);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("Invoke should fail due to null operation, has callbacks"));
        MI_Operation_Close(&operation);

        session.ft->Invoke(&session, 0, NULL, NULL,  PAL_T("testClass"), PAL_T("TestMethod"), NULL, NULL, NULL, NULL);
        /* Nothing to validate, just make sure it doesn't crash! */

        MI_Session_Close(&session, NULL, NULL);

        session.ft->Invoke(&session, 0, NULL, NULL,  PAL_T("testClass"), PAL_T("TestMethod"), NULL, NULL, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("Invoke should fail because session is already closed"));
        MI_Operation_Close(&operation);
    }

}
NitsEndTest

NitsTest3(MI_Session_Invoke_Sync_TransportNotSupported, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test2,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    const MI_Instance *result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    const MI_Char *errorMessage;

    session->ft->Invoke(session, 0, NULL, NULL,  PAL_T("testClass"), PAL_T("TestMethod"), NULL, NULL, NULL, &operation);
    MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
    NitsCompare(resultCode, MI_RESULT_NOT_SUPPORTED, PAL_T("Invoke should fail"));
    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest3(MI_Session_ModifyInstance_Async_AutoAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 1;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult;

    MI_Session_ModifyInstance(session, 0, NULL, NULL, testInstance, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->instanceCount,  (MI_Uint32)g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

NitsTest3(MI_Session_ModifyInstance_Async_ManualAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 1;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult;

    MI_Session_ModifyInstance(session, MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, NULL, NULL, testInstance, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->instanceCount,  (MI_Uint32)g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

NitsTest3(MI_Session_ModifyInstance_Sync, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;

    const MI_Instance *resultInstance;
    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_ModifyInstance(session, 0, NULL, NULL, testInstance, NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
    NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest3(MI_Session_ModifyInstance_Sync_WithOptions, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;

    MI_OperationOptions options = MI_OPERATIONOPTIONS_NULL;
    if (NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, &options), MI_RESULT_OK, PAL_T("NewOperationOptions should succeed")))
    {
        NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
        NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
        {
            MI_Value value;
            value.string = (MI_Char *)PAL_T("hello world");
            NitsCompare(options.ft->SetCustomOption(&options, PAL_T("option3"), MI_STRING, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomString should work"));
        }

        {
            const MI_Instance *resultInstance;
            MI_Boolean moreResults;
            MI_Result result;
            const MI_Char *errorMessage;
            const MI_Instance *completionDetails;

            MI_Session_ModifyInstance(session, 0, &options, NULL, testInstance, NULL, &operation);
            NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

            MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
            NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
            NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

            MI_Operation_Close(&operation);

        }
        MI_OperationOptions_Delete(&options);
    }
}
NitsEndTest

NitsTest2(MI_Session_ModifyInstance_Sync_InvalidParameters, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    MI_Session session = MI_SESSION_NULL;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    const MI_Instance *result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    const MI_Char *errorMessage;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_Result returnValue;
    
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult_Fail;

    if (NitsCompare(MI_Application_NewSession(application, PAL_T("Test1"), NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
        NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL")))
    {
        if (session.ft == NULL)
            NitsReturn;

        session.ft->ModifyInstance(&session, 0, NULL, NULL, testInstance, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_OK, PAL_T("GetInstance should succeed"));

        returnValue = operation.ft->GetInstance(NULL, &result, NULL, &resultCode, NULL, NULL);
        NitsCompare(returnValue, MI_RESULT_INVALID_PARAMETER, PAL_T("Operation_GetInstance should fail due to NULL operation"));

        returnValue = operation.ft->GetInstance(&operation, NULL, NULL, &resultCode, NULL, NULL);
        NitsCompare(returnValue, MI_RESULT_INVALID_PARAMETER, PAL_T("Operation_GetInstance should fail due to NULL instance"));

        operation.ft->GetInstance(&operation, NULL, NULL, NULL, NULL, NULL);
        /* no where for result to go but may add code coverage for scenario */

        MI_Operation_Close(&operation);

        session.ft->ModifyInstance(NULL, 0, NULL, NULL, testInstance, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetInstance should faul due to NULL session"));
        MI_Operation_Close(&operation);

        session.ft->ModifyInstance(&session, 0, NULL, NULL, NULL, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetInstance should fail due to NULL instance key"));
        MI_Operation_Close(&operation);

        session.ft->ModifyInstance(&session, 0, NULL, NULL, testInstance, NULL, NULL);
        /* Validate it doesn't crash only as nowhere for failure to go */

        session.ft->ModifyInstance(&session, 0, NULL, NULL, testInstance, &callbacks, NULL);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetInstance should fail due to null operation, has callbacks"));
        MI_Operation_Close(&operation);

        MI_Session_Close(&session, NULL, NULL);

        session.ft->ModifyInstance(&session, 0, NULL, NULL, testInstance, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetInstance should fail because session is already closed"));
        MI_Operation_Close(&operation);
    }
}
NitsEndTest

NitsTest3(MI_Session_ModifyInstance_TransportNotSupported, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test2,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    
    const MI_Instance *resultInstance;
    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_ModifyInstance(session, 0, NULL, NULL, testInstance, NULL, &operation);

    MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_NOT_SUPPORTED, PAL_T("Operation should succeed"));
    NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest3(MI_Session_CreateInstance_Async_AutoAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 1;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult;

    MI_Session_CreateInstance(session, 0, NULL, NULL, testInstance, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->instanceCount,  (MI_Uint32)g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

NitsTest3(MI_Session_CreateInstance_Async_ManualAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 1;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult;

    MI_Session_CreateInstance(session, MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, NULL, NULL, testInstance, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->instanceCount,  (MI_Uint32)g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

NitsTest3(MI_Session_CreateInstance_Sync, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;

    const MI_Instance *resultInstance;
    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_CreateInstance(session, 0, NULL, NULL, testInstance, NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
    NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest3(MI_Session_CreateInstance_Sync_WithOptions, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;

    MI_OperationOptions options = MI_OPERATIONOPTIONS_NULL;
    if (NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, &options), MI_RESULT_OK, PAL_T("NewOperationOptions should succeed")))
    {
        NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
        NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
        {
            MI_Value value;
            value.string = (MI_Char*) PAL_T("hello world");
            NitsCompare(options.ft->SetCustomOption(&options, PAL_T("option3"), MI_STRING, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomString should work"));
        }

        const MI_Instance *resultInstance;
        MI_Boolean moreResults;
        MI_Result result;
        const MI_Char *errorMessage;
        const MI_Instance *completionDetails;

        MI_Session_CreateInstance(session, 0, &options, NULL, testInstance, NULL, &operation);
        NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

        MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
        NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
        NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

        MI_Operation_Close(&operation);

        MI_OperationOptions_Delete(&options);
    }
}
NitsEndTest

NitsTest2(MI_Session_CreateInstance_Sync_InvalidParameters, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    MI_Session session = MI_SESSION_NULL;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    const MI_Instance *result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    MI_Result returnValue;
    const MI_Char *errorMessage;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult_Fail;

    if (NitsCompare(MI_Application_NewSession(application, PAL_T("Test1"), NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
        NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL")))
    {
        if (session.ft == NULL)
            NitsReturn;

        session.ft->CreateInstance(&session, 0, NULL, NULL, testInstance, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_OK, PAL_T("GetInstance should succeed"));

        returnValue = operation.ft->GetInstance(NULL, &result, NULL, &resultCode, NULL, NULL);
        NitsCompare(returnValue, MI_RESULT_INVALID_PARAMETER, PAL_T("Operation_GetInstance should fail due to NULL operation"));

        returnValue = operation.ft->GetInstance(&operation, NULL, NULL, &resultCode, NULL, NULL);
        NitsCompare(returnValue, MI_RESULT_INVALID_PARAMETER, PAL_T("Operation_GetInstance should fail due to NULL instance"));

        operation.ft->GetInstance(&operation, NULL, NULL, NULL, NULL, NULL);
        /* no where for result to go but may add code coverage for scenario */

        MI_Operation_Close(&operation);

        session.ft->CreateInstance(NULL, 0, NULL, NULL, testInstance, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetInstance should faul due to NULL session"));
        MI_Operation_Close(&operation);

        session.ft->CreateInstance(&session, 0, NULL, NULL, NULL, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetInstance should fail due to NULL instance key"));
        MI_Operation_Close(&operation);

        session.ft->CreateInstance(&session, 0, NULL, NULL, testInstance, NULL, NULL);
        /* Validate it doesn't crash only as nowhere for failure to go */

        session.ft->CreateInstance(&session, 0, NULL, NULL, testInstance, &callbacks, NULL);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetInstance should fail due to null operation, has callbacks"));
        MI_Operation_Close(&operation);

        MI_Session_Close(&session, NULL, NULL);

        session.ft->CreateInstance(&session, 0, NULL, NULL, testInstance, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetInstance should fail because session is already closed"));
        MI_Operation_Close(&operation);

    }
}
NitsEndTest

NitsTest3(MI_Session_CreateInstance_TransportNotSupported, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test2,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;

    const MI_Instance *resultInstance;
    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_CreateInstance(session, 0, NULL, NULL, testInstance, NULL, &operation);

    MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_NOT_SUPPORTED, PAL_T("Operation should succeed"));
    NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

    MI_Operation_Close(&operation);

}
NitsEndTest

NitsTest3(MI_Session_DeleteInstance_Async_AutoAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 1;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult;

    MI_Session_DeleteInstance(session, 0, NULL, NULL, testInstance, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->instanceCount,  (MI_Uint32)g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

NitsTest3(MI_Session_DeleteInstance_Async_ManualAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 1;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult;

    MI_Session_DeleteInstance(session, MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, NULL, NULL, testInstance, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->instanceCount,  (MI_Uint32)g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

NitsTest3(MI_Session_DeleteInstance_Sync, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;

    const MI_Instance *resultInstance;
    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_DeleteInstance(session, 0, NULL, NULL, testInstance, NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
    NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest3(MI_Session_DeleteInstance_Sync_WithOptions, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationOptions options = MI_OPERATIONOPTIONS_NULL;

    if (NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, &options), MI_RESULT_OK, PAL_T("NewOperationOptions should succeed")))
    {
        NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
        NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
        {
            MI_Value value;
            value.string = (MI_Char*) PAL_T("hello world");
            NitsCompare(options.ft->SetCustomOption(&options, PAL_T("option3"), MI_STRING, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomString should work"));
        }

        const MI_Instance *resultInstance;
        MI_Boolean moreResults;
        MI_Result result;
        const MI_Char *errorMessage;
        const MI_Instance *completionDetails;

        MI_Session_DeleteInstance(session, 0, &options, NULL, testInstance, NULL, &operation);
        NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

        MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
        NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
        NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

        MI_Operation_Close(&operation);
        MI_OperationOptions_Delete(&options);
    }
}
NitsEndTest

NitsTest3(MI_Session_DeleteInstance_Sync_InvalidParameters, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    MI_Instance *testInstance = testData->testInstance;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    const MI_Instance *result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    MI_Result returnValue;
    const MI_Char *errorMessage;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult_Fail;

    if (NitsCompare(MI_Application_NewSession(application, PAL_T("Test1"), NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
        NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL")))
    {
        if (session.ft == NULL)
            NitsReturn;

        session.ft->DeleteInstance(&session, 0, NULL, NULL, testInstance, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_OK, PAL_T("GetInstance should succeed"));

        returnValue = operation.ft->GetInstance(NULL, &result, NULL, &resultCode, NULL, NULL);
        NitsCompare(returnValue, MI_RESULT_INVALID_PARAMETER, PAL_T("Operation_GetInstance should fail due to NULL operation"));

        returnValue = operation.ft->GetInstance(&operation, NULL, NULL, &resultCode, NULL, NULL);
        NitsCompare(returnValue, MI_RESULT_INVALID_PARAMETER, PAL_T("Operation_GetInstance should fail due to NULL instance"));

        operation.ft->GetInstance(&operation, NULL, NULL, NULL, NULL, NULL);
        /* no where for result to go but may add code coverage for scenario */

        MI_Operation_Close(&operation);

        session.ft->DeleteInstance(NULL, 0, NULL, NULL, testInstance, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetInstance should faul due to NULL session"));
        MI_Operation_Close(&operation);

        session.ft->DeleteInstance(&session, 0, NULL, NULL, NULL, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetInstance should fail due to NULL instance key"));
        MI_Operation_Close(&operation);

        session.ft->DeleteInstance(&session, 0, NULL, NULL, testInstance, NULL, NULL);
        /* Validate it doesn't crash only as nowhere for failure to go */
            
        session.ft->DeleteInstance(&session, 0, NULL, NULL, testInstance, &callbacks, NULL);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetInstance should fail due to null operation, has callbacks"));
        MI_Operation_Close(&operation);

        MI_Session_Close(&session, NULL, NULL);

        session.ft->DeleteInstance(&session, 0, NULL, NULL, testInstance, NULL, &operation);
        MI_Operation_GetInstance(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
        NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetInstance should fail because session is already closed"));
        MI_Operation_Close(&operation);

    }
}
NitsEndTest

NitsTest3(MI_Session_DeleteInstance_TransportNotSupported, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test2,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;

    const MI_Instance *resultInstance;
    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_DeleteInstance(session, 0, NULL, NULL, testInstance, NULL, &operation);

    MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_NOT_SUPPORTED, PAL_T("Operation should succeed"));
    NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

    MI_Operation_Close(&operation);
}
NitsEndTest

#if 0
extern "C" void MI_CALL MI_Session_GetInstance_Async_CancelBeforeClose_Result(
    _In_     MI_Operation *operation,
    _In_     void *callbackContext, 
    _In_opt_ const MI_Instance *instance,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char * errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    NitsCompare(resultCode, MI_RESULT_OK, PAL_T("Operation should have succeeded"));

    MI_Operation_Cancel(operation, MI_REASON_NONE);

    if (resultAcknowledgement)
    {
        resultAcknowledgement(operation);
    }

    if (!moreResults)
    {
        MI_Operation_Close(operation);
        CondLock_Broadcast((ptrdiff_t) callbackContext);
    }
}


NitsTest3(MI_Session_GetInstance_Async_CancelBeforeClose, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    callbacks.callbackContext = testData;
    callbacks.instanceResult = MI_Session_GetInstance_Async_CancelBeforeClose_Result;

    MI_Session_GetInstance(session, 0, NULL, NULL, testInstance, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));
    
    WaitForOperationToComplete(testData);

}
NitsEndTest

extern "C" void MI_CALL MI_Session_GetInstance_Async_CancelBeforeResult_Result(
    _In_     MI_Operation *operation,
    _In_     void *callbackContext, 
    _In_opt_ const MI_Instance *instance,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char * errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    NitsCompare(resultCode, MI_RESULT_FAILED, PAL_T("Operation should have failed"));

    if (!moreResults)
    {
        MI_Operation_Close(operation);
    }
    if (resultAcknowledgement)
    {
        resultAcknowledgement(operation);
    }
    if (!moreResults)
    {
        CondLock_Broadcast((ptrdiff_t) callbackContext);
    }
}

NitsTest3(MI_Session_GetInstance_Async_CancelBeforeResult, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_NoResult)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    callbacks.callbackContext = testData;
    callbacks.instanceResult = MI_Session_GetInstance_Async_CancelBeforeResult_Result;

    MI_Session_GetInstance(session, 0, NULL, NULL, testInstance, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    MI_Operation_Cancel(&operation, MI_REASON_NONE);

    WaitForOperationToComplete(testData);
}
NitsEndTest

NitsTest(MI_Session_GetInstance_Async_CloseSessionBeforeResult)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    callbacks.instanceResult = MI_Session_GetInstance_Async_CancelBeforeResult_Result;

    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("MI_Application_Initialize returns OK")) &&
        NitsAssert(application.ft != NULL, PAL_T("MI_Application function table should not be NULL")))
    {
        MI_Instance *instance = TestCreateInstance(&application, PAL_T("NoResult"));
        if (NitsAssert(instance != NULL, PAL_T("failed to create instance")))
        {
            if (NitsCompare(MI_Application_NewSession(&application, PAL_T("Test1"), NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
                NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL")))
            {
                MI_Session_GetInstance(&session, 0, NULL, NULL, instance, &callbacks, &operation);
                NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

                MI_Session_Close(&session, NULL, NULL);
            }
            MI_Instance_Delete(instance);
        }

        MI_Application_Close(&application);
    }
}
NitsEndTest

NitsTest(MI_Session_GetInstance_Async_CloseSessionBeforeResult_ResultOnDifferentThread)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    callbacks.instanceResult = MI_Session_GetInstance_Async_CancelBeforeResult_Result;

    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("MI_Application_Initialize returns OK")) &&
        NitsAssert(application.ft != NULL, PAL_T("MI_Application function table should not be NULL")))
    {
        MI_Instance *instance = TestCreateInstance(&application, PAL_T("NoResultDifferentThread"));
        if (NitsAssert(instance != NULL, PAL_T("failed to create instance")))
        {
            if (NitsCompare(MI_Application_NewSession(&application, PAL_T("Test1"), NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
                NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL")))
            {
                MI_Session_GetInstance(&session, 0, NULL, NULL, instance, &callbacks, &operation);
                NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

                MI_Session_Close(&session, NULL, NULL);
            }
            MI_Instance_Delete(instance);
        }

        MI_Application_Close(&application);
    }
}
NitsEndTest

extern "C" void MI_CALL MI_Session_GetInstance_Async_CloseApplicationBeforeResult_ResultOnDifferentThread_Result_SessionClosed(_In_opt_ void *completionContext)
{
}
extern "C" void MI_CALL MI_Session_GetInstance_Async_CloseApplicationBeforeResult_ResultOnDifferentThread_Result(
    _In_     MI_Operation *operation,
    _In_     void *callbackContext, 
    _In_opt_ const MI_Instance *instance,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char * errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    MI_Session session = MI_SESSION_NULL;
    NitsCompare(resultCode, MI_RESULT_FAILED, PAL_T("Operation should have failed"));
    MI_Operation_GetSession(operation, &session);

    if (resultAcknowledgement)
    {
        resultAcknowledgement(operation);
    }

    if (!moreResults)
    {
        MI_Operation_Close(operation);
        MI_Session_Close(&session, NULL, MI_Session_GetInstance_Async_CloseApplicationBeforeResult_ResultOnDifferentThread_Result_SessionClosed);
    }

}


NitsTest(MI_Session_GetInstance_Async_CloseApplicationBeforeResult_ResultOnDifferentThread)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    callbacks.instanceResult = MI_Session_GetInstance_Async_CloseApplicationBeforeResult_ResultOnDifferentThread_Result;

    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("MI_Application_Initialize returns OK")) &&
        NitsAssert(application.ft != NULL, PAL_T("MI_Application function table should not be NULL")))
    {
        MI_Instance *instance = TestCreateInstance(&application, PAL_T("NoResultDifferentThread"));
        if (NitsAssert(instance != NULL, PAL_T("failed to create instance")))
        {
            if (NitsCompare(MI_Application_NewSession(&application, PAL_T("Test1"), NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
                NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL")))
            {
                MI_Session_GetInstance(&session, 0, NULL, NULL, instance, &callbacks, &operation);
                NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));
                /* session cleaned up in callback */
            }
            MI_Instance_Delete(instance);
        }

        MI_Application_Close(&application);
    }
}
NitsEndTest

#endif
/*==========================================================================================*/
/*=================================== Enumerate Instances ==================================*/
/*==========================================================================================*/

NitsTest2(MI_Session_EnumerateInstances_Sync, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    
    const MI_Instance *resultInstance;
    MI_Boolean moreResults = MI_TRUE;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;
    unsigned int resultCount = 0;

    MI_Session_EnumerateInstances(session, 0, NULL, NULL, PAL_T("testClass"), MI_FALSE, NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    while (moreResults && (++resultCount <= 10))
    {
        MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
        NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
    }
    NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest2(MI_Session_EnumerateInstances_Sync_WithOptions, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationOptions options = MI_DESTINATIONOPTIONS_NULL;

    if (NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, &options), MI_RESULT_OK, PAL_T("NewOperationOptions should succeed")))
    {
        NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
        NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
        {
            MI_Value value;
            value.string = (MI_Char*) PAL_T("hello world");
            NitsCompare(options.ft->SetCustomOption(&options, PAL_T("option3"), MI_STRING, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomString should work"));
        }

        const MI_Instance *resultInstance;
        MI_Boolean moreResults = MI_TRUE;
        MI_Result result;
        const MI_Char *errorMessage;
        const MI_Instance *completionDetails;
        unsigned int resultCount = 0;

        MI_Session_EnumerateInstances(session, 0, &options, NULL, PAL_T("testClass"), MI_FALSE, NULL, &operation);
        NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

        while (moreResults && (++resultCount <= 10))
        {
            MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
            NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
        }
        NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
        MI_Operation_Close(&operation);

        MI_OperationOptions_Delete(&options);
    }
}
NitsEndTest

NitsTest2(MI_Session_EnumerateInstances_Sync_InvalidParameters, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    
    const MI_Instance *resultInstance;
    MI_Boolean moreResults = MI_TRUE;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;
    unsigned int resultCount = 0;

    {/* success */
        MI_Session_EnumerateInstances(session, 0, NULL, NULL, PAL_T("testClass"), MI_FALSE, NULL, &operation);
        NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

        while (moreResults && (++resultCount <= 10))
        {
            MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
            NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
        }
        NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
        MI_Operation_Close(&operation);
    }
    {/* no opertion */
#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
        MI_Session_EnumerateInstances(session, 0, NULL, NULL, PAL_T("testClass"), MI_FALSE, NULL, NULL);
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif
        /* nothing more we can do as no where for result to go */
    }
}
NitsEndTest

NitsTest2(MI_Session_EnumerateInstances_Sync_TransportNotSupported, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test2,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    
    const MI_Instance *resultInstance;
    MI_Boolean moreResults = MI_TRUE;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_EnumerateInstances(session, 0, NULL, NULL, PAL_T("testClass"), MI_FALSE, NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_NOT_SUPPORTED, PAL_T("Operation should fail with not supported"));
    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest2(MI_Session_EnumerateInstances_Async_AutoAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 10;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult;

    MI_Session_EnumerateInstances(session, 0, NULL, NULL, PAL_T("testClass"), MI_FALSE, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->instanceCount,  (MI_Uint32)g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

/*==========================================================================================*/
/*===================================== Query Instances ====================================*/
/*==========================================================================================*/

NitsTest2(MI_Session_QueryInstances_Sync, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    
    const MI_Instance *resultInstance;
    MI_Boolean moreResults = MI_TRUE;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;
    unsigned int resultCount = 0;

    MI_Session_QueryInstances(session, 0, NULL, PAL_T("namespace"), PAL_T("dialect"), PAL_T("filter"), NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    while (moreResults && (++resultCount <= 10))
    {
        MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
        NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
    }
    NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest2(MI_Session_QueryInstances_Sync_WithOptions, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    
    MI_OperationOptions options = MI_DESTINATIONOPTIONS_NULL;
    if (NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, &options), MI_RESULT_OK, PAL_T("NewOperationOptions should succeed")))
    {
        NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
        NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
        {
            MI_Value value;
            value.string = (MI_Char*) PAL_T("hello world");
            NitsCompare(options.ft->SetCustomOption(&options, PAL_T("option3"), MI_STRING, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomString should work"));
        }

        const MI_Instance *resultInstance;
        MI_Boolean moreResults = MI_TRUE;
        MI_Result result;
        const MI_Char *errorMessage;
        const MI_Instance *completionDetails;
        unsigned int resultCount = 0;

        MI_Session_QueryInstances(session, 0, &options, PAL_T("namespace"), PAL_T("dialect"), PAL_T("filter"), NULL, &operation);
        NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

        while (moreResults && (++resultCount <= 10))
        {
            MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
            NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
        }
        NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
        MI_Operation_Close(&operation);

        MI_OperationOptions_Delete(&options);
    }
}
NitsEndTest

NitsTest2(MI_Session_QueryInstances_Sync_InvalidParameters, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    
    const MI_Instance *resultInstance;
    MI_Boolean moreResults = MI_TRUE;
    MI_Result result = MI_RESULT_FAILED;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;
    unsigned int resultCount = 0;

    {/* success */
        MI_Session_QueryInstances(session, 0, NULL, PAL_T("namespace"), PAL_T("dialect"), PAL_T("filter"), NULL, &operation);
        NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

        while (moreResults && (++resultCount <= 10))
        {
            MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
            NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
        }
        NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
        MI_Operation_Close(&operation);
    }
    {/* no filter */
        MI_Session_QueryInstances(session, 0, NULL, PAL_T("namespace"), NULL, NULL, NULL, &operation);
        NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));
        resultCount = 0;
        moreResults = MI_TRUE;
        while (moreResults && (++resultCount <= 10))
        {
            MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
            NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
        }
        NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
        MI_Operation_Close(&operation);
    }
    {/* no opertion */
#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
        MI_Session_QueryInstances(session, 0, NULL, NULL, PAL_T("dialect"), PAL_T("filter"), NULL, NULL);
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif
        /* nothing more we can do as no where for result to go */
    }

}
NitsEndTest

NitsTest2(MI_Session_QueryInstances_Sync_TransportNotSupported, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test2,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    
    const MI_Instance *resultInstance;
    MI_Boolean moreResults = MI_TRUE;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_QueryInstances(session, 0, NULL, PAL_T("namespace"), PAL_T("dialect"), PAL_T("filter"), NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_NOT_SUPPORTED, PAL_T("Operation should fail with not supported"));
    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest2(MI_Session_QueryInstances_Async_AutoAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 10;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult;

    MI_Session_QueryInstances(session, 0, NULL, PAL_T("namespace"), PAL_T("dialect"), PAL_T("filter"), &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->instanceCount,  (MI_Uint32)g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

/*==========================================================================================*/
/*=================================== ASSOCIATOR INSTANCE ==================================*/
/*==========================================================================================*/

NitsTest3(MI_Session_AssociatorInstances_Sync, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    
    const MI_Instance *resultInstance;
    MI_Boolean moreResults = MI_TRUE;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;
    unsigned int resultCount = 0;

    MI_Session_AssociatorInstances(session, 0, NULL, NULL, testInstance, NULL, PAL_T("test"), NULL, NULL, MI_FALSE, NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    while (moreResults && (++resultCount <= 10))
    {
        MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
        NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
    }
    NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest3(MI_Session_AssociatorInstances_Sync_WithOptions, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    
    MI_OperationOptions options = MI_OPERATIONOPTIONS_NULL;
    if (NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, &options), MI_RESULT_OK, PAL_T("NewOperationOptions should succeed")))
    {
        NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
        NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
        {
            MI_Value value;
            value.string = (MI_Char*)PAL_T("hello world");
            NitsCompare(options.ft->SetCustomOption(&options, PAL_T("option3"), MI_STRING, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomString should work"));
        }

        const MI_Instance *resultInstance;
        MI_Boolean moreResults = MI_TRUE;
        MI_Result result;
        const MI_Char *errorMessage;
        const MI_Instance *completionDetails;
        unsigned int resultCount = 0;

        MI_Session_AssociatorInstances(session, 0, &options, NULL, testInstance, NULL, PAL_T("test"), NULL, NULL, MI_FALSE, NULL, &operation);
        NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

        while (moreResults && (++resultCount <= 10))
        {
            MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
            NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
        }
        NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
        MI_Operation_Close(&operation);

        MI_OperationOptions_Delete(&options);
    }
}
NitsEndTest


NitsTest3(MI_Session_AssociatorInstances_Sync_InvalidParameters, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    
    const MI_Instance *resultInstance;
    MI_Boolean moreResults = MI_TRUE;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;
    unsigned int resultCount = 0;

    {/* success */
        MI_Session_AssociatorInstances(session, 0, NULL, NULL, testInstance, NULL, PAL_T("test"), NULL, NULL, MI_FALSE, NULL, &operation);
        NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

        while (moreResults && (++resultCount <= 10))
        {
            MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
            NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
        }
        NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
        MI_Operation_Close(&operation);
    }
    {/* no class */
#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
        MI_Session_AssociatorInstances(session, 0, NULL, NULL, NULL, NULL, PAL_T("test"), NULL, NULL, MI_FALSE, NULL, &operation);
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif
        NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

        MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
        NitsCompare(result, MI_RESULT_INVALID_PARAMETER, PAL_T("Operation should succeed"));
        MI_Operation_Close(&operation);
    }
    {/* no opertion */
#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
        MI_Session_AssociatorInstances(session, 0, NULL, NULL, testInstance, NULL, PAL_T("test"), NULL, NULL, MI_FALSE, NULL, NULL);
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif
        /* nothing more we can do as no where for result to go */
    }
}
NitsEndTest

NitsTest3(MI_Session_AssociatorInstances_Sync_TransportNotSupported, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test2,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    
    const MI_Instance *resultInstance;
    MI_Boolean moreResults = MI_TRUE;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_AssociatorInstances(session, 0, NULL, NULL, testInstance, NULL, PAL_T("test"), NULL, NULL, MI_FALSE, NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_NOT_SUPPORTED, PAL_T("Operation should fail with not supported"));
    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest3(MI_Session_AssociatorInstances_Async_AutoAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 10;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult;

    MI_Session_AssociatorInstances(session, 0, NULL, NULL, testInstance, NULL, PAL_T("test"), NULL, NULL, MI_FALSE, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsAssert(testData->instanceCount == g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

/*==========================================================================================*/
/*=================================== REFERENCE INSTANCE ===================================*/
/*==========================================================================================*/

NitsTest3(MI_Session_ReferenceInstances_Sync, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    
    const MI_Instance *resultInstance;
    MI_Boolean moreResults = MI_TRUE;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;
    unsigned int resultCount = 0;

    MI_Session_ReferenceInstances(session, 0, NULL, NULL, testInstance, PAL_T("test"), NULL, MI_FALSE, NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    while (moreResults && (++resultCount <= 10))
    {
        MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
        NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
    }
    NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest3(MI_Session_ReferenceInstances_Sync_WithOptions, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    
    MI_OperationOptions options = MI_OPERATIONOPTIONS_NULL;
    if (NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, &options), MI_RESULT_OK, PAL_T("NewOperationOptions should succeed")))
    {
        NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
        NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
        {
            MI_Value value;
            value.string = (MI_Char *) PAL_T("hello world");
            NitsCompare(options.ft->SetCustomOption(&options, PAL_T("option3"), MI_STRING, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomString should work"));
        }

        const MI_Instance *resultInstance;
        MI_Boolean moreResults = MI_TRUE;
        MI_Result result;
        const MI_Char *errorMessage;
        const MI_Instance *completionDetails;
        unsigned int resultCount = 0;

        MI_Session_ReferenceInstances(session, 0, &options, NULL, testInstance, PAL_T("test"), NULL, MI_FALSE, NULL, &operation);
        NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

        while (moreResults && (++resultCount <= 10))
        {
            MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
            NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
        }
        NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
        MI_Operation_Close(&operation);

        MI_OperationOptions_Delete(&options);
    }
}
NitsEndTest

NitsTest3(MI_Session_ReferenceInstances_Sync_InvalidParameters, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    
    const MI_Instance *resultInstance;
    MI_Boolean moreResults = MI_TRUE;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;
    unsigned int resultCount = 0;

    {/* success */
        MI_Session_ReferenceInstances(session, 0, NULL, NULL, testInstance, PAL_T("test"), NULL, MI_FALSE, NULL, &operation);
        NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

        while (moreResults && (++resultCount <= 10))
        {
            MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
            NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
        }
        NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
        MI_Operation_Close(&operation);
    }
    {/* no class */
#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
        MI_Session_ReferenceInstances(session, 0, NULL, NULL, NULL , PAL_T("test"), NULL, MI_FALSE, NULL, &operation);
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif
        NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

        MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
        NitsCompare(result, MI_RESULT_INVALID_PARAMETER, PAL_T("Operation should succeed"));
        MI_Operation_Close(&operation);
    }
    {/* no opertion */
#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
        MI_Session_ReferenceInstances(session, 0, NULL, NULL, testInstance, PAL_T("test"), NULL, MI_FALSE, NULL, NULL);
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif
        /* nothing more we can do as no where for result to go */
    }
}
NitsEndTest

NitsTest3(MI_Session_ReferenceInstances_Sync_TransportNotSupported, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test2,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    
    const MI_Instance *resultInstance;
    MI_Boolean moreResults = MI_TRUE;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_ReferenceInstances(session, 0, NULL, NULL, testInstance, PAL_T("test"), NULL, MI_FALSE, NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_NOT_SUPPORTED, PAL_T("Operation should fail with not supported"));
    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest3(MI_Session_ReferenceInstances_Async_AutoAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults,
          SetupTestInstance, g_SetupTestInstance_test)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Instance *testInstance = testData->testInstance;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 10;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult;

    MI_Session_ReferenceInstances(session, 0, NULL, NULL, testInstance, PAL_T("test"), NULL, MI_FALSE, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsAssert(testData->instanceCount == g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

/*==========================================================================================*/
/*======================================== Get Class =======================================*/
/*==========================================================================================*/

NitsTest2(MI_Session_GetClass_Sync, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;

    const MI_Class *resultClass;
    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_GetClass(session, 0, NULL, PAL_T("namespace"), PAL_T("myClass"), NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    MI_Operation_GetClass(&operation, &resultClass, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
    NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

    MI_Operation_Close(&operation);
}
NitsEndTest


NitsTest2(MI_Session_GetClass_Async_AutoAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 1;
    callbacks.callbackContext = testData;
    callbacks.classResult = GetClassResult;

    MI_Session_GetClass(session, 0, NULL, PAL_T("Namespace"), PAL_T("MyClass"), &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->classCount, (MI_Uint32)g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

NitsTest2(MI_Session_GetClass_Async_ManualAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 1;
    callbacks.callbackContext = testData;
    callbacks.classResult = GetClassResult;

    MI_Session_GetClass(session, MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, NULL, PAL_T("namespace"), PAL_T("myClass"), &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->classCount, (MI_Uint32)g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

NitsTest2(MI_Session_GetClass_Sync_WithOptions, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationOptions options = MI_OPERATIONOPTIONS_NULL;

    if (NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, &options), MI_RESULT_OK, PAL_T("NewOperationOptions should succeed")))
    {
        NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
        NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
        {
            MI_Value value;
            value.string = (MI_Char *)PAL_T("hello world");
            NitsCompare(options.ft->SetCustomOption(&options, PAL_T("option3"), MI_STRING, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomString should work"));
        }

        const MI_Class *resultClass;
        MI_Boolean moreResults;
        MI_Result result;
        const MI_Char *errorMessage;
        const MI_Instance *completionDetails;

        MI_Session_GetClass(session, 0, &options, PAL_T("mynamespace"), PAL_T("myclass"), NULL, &operation);
        NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

        MI_Operation_GetClass(&operation, &resultClass, &moreResults, &result, &errorMessage, &completionDetails);
        NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
        NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

        MI_Operation_Close(&operation);

        MI_OperationOptions_Delete(&options);
    }
}
NitsEndTest

#if 0
NitsTest(MI_Session_GetClass_Sync_InvalidParameters)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    const MI_Class*result;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    MI_Result returnValue;
    const MI_Char *errorMessage;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    callbacks.classResult = GetClassResult_Fail;

    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("MI_Application_Initialize returns OK")) &&
        NitsAssert(application.ft != NULL, PAL_T("MI_Application function table should not be NULL")))
    {
        if (NitsCompare(MI_Application_NewSession(&application, PAL_T("Test1"), NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
            NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL")))
        {
            session.ft->GetClass(&session, 0, NULL, PAL_T("namespace"), PAL_T("myclass"), NULL, &operation);
            MI_Operation_GetClass(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
            NitsCompare(resultCode, MI_RESULT_OK, PAL_T("GetClass should succeed"));

            returnValue = operation.ft->GetClass(NULL, &result, NULL, &resultCode, NULL, NULL);
            NitsCompare(returnValue, MI_RESULT_INVALID_PARAMETER, PAL_T("Operation_GetClass should fail due to NULL operation"));

            returnValue = operation.ft->GetClass(&operation, NULL, NULL, &resultCode, NULL, NULL);
            NitsCompare(returnValue, MI_RESULT_INVALID_PARAMETER, PAL_T("Operation_GetClass should fail due to NULL instance"));

            operation.ft->GetClass(&operation, NULL, NULL, NULL, NULL, NULL);
            /* no where for result to go but may add code coverage for scenario */

            MI_Operation_Close(&operation);

            session.ft->GetClass(NULL, 0, NULL, PAL_T("namespace"), PAL_T("className"), NULL, &operation);
            MI_Operation_GetClass(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
            NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetClass should faul due to NULL session"));
            MI_Operation_Close(&operation);

            session.ft->GetClass(&session, 0, NULL, PAL_T("namespace"), PAL_T("className"), &callbacks, NULL);
            MI_Operation_GetClass(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
            NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetClass should fail due to null operation, has callbacks"));
            MI_Operation_Close(&operation);

            session.ft->GetClass(&session, 0, NULL, PAL_T("namespace"), PAL_T("myclass"), NULL, NULL);
            /* Validate it doesn't crash only as nowhere for failure to go */
            MI_Session_Close(&session, NULL, NULL);

            session.ft->GetClass(&session, 0, NULL, PAL_T("mynamespace"), PAL_T("myclass"), NULL, &operation);
            MI_Operation_GetClass(&operation, &result, &moreResults, &resultCode, &errorMessage, &extendedInfo);
            NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetClass should fail because session is already closed"));
            MI_Operation_Close(&operation);

        }
        MI_Application_Close(&application);
    }
}
NitsEndTest
#endif

NitsTest2(MI_Session_GetClass_TransportNotSupported, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test2,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;

    const MI_Class *resultClass;
    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_GetClass(session, 0, NULL, PAL_T("mynamespace"), PAL_T("myclass"), NULL, &operation);

    MI_Operation_GetClass(&operation, &resultClass, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_NOT_SUPPORTED, PAL_T("Operation should succeed"));
    NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

    MI_Operation_Close(&operation);
}
NitsEndTest

/*==========================================================================================*/
/*==================================== Enumerate Classes ===================================*/
/*==========================================================================================*/

NitsTest2(MI_Session_EnumerateClasses_Sync, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    
    const MI_Class *resultClass;
    MI_Boolean moreResults = MI_TRUE;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;
    unsigned int resultCount = 0;

    MI_Session_EnumerateClasses(session, 0, NULL, PAL_T("namespace"), PAL_T("testClass"), MI_FALSE, NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    while (moreResults && (++resultCount <= 10))
    {
        MI_Operation_GetClass(&operation, &resultClass, &moreResults, &result, &errorMessage, &completionDetails);
        NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
    }
    NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest2(MI_Session_EnumerateClasses_Sync_WithOptions, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationOptions options = MI_OPERATIONOPTIONS_NULL;

    if (NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, &options), MI_RESULT_OK, PAL_T("NewOperationOptions should succeed")))
    {
        NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
        NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
        {
            MI_Value value;
            value.string = (MI_Char*)PAL_T("hello world");
            NitsCompare(options.ft->SetCustomOption(&options, PAL_T("option3"), MI_STRING, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomString should work"));
        }

        const MI_Class *resultClass;
        MI_Boolean moreResults = MI_TRUE;
        MI_Result result;
        const MI_Char *errorMessage;
        const MI_Instance *completionDetails;
        unsigned int resultCount = 0;

        MI_Session_EnumerateClasses(session, 0, &options, PAL_T("namespace"), PAL_T("testClass"), MI_FALSE, NULL, &operation);
        NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

        while (moreResults && (++resultCount <= 10))
        {
            MI_Operation_GetClass(&operation, &resultClass, &moreResults, &result, &errorMessage, &completionDetails);
            NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
        }
        NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
        MI_Operation_Close(&operation);

        MI_OperationOptions_Delete(&options);
    }
}
NitsEndTest

#if 0
NitsTest(MI_Session_EnumerateClasses_Sync_InvalidParameters)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("MI_Application_Initialize returns OK")) &&
        NitsAssert(application.ft != NULL, PAL_T("MI_Application function table should not be NULL")))
    {
        if (NitsCompare(MI_Application_NewSession(&application, PAL_T("Test1"), NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
            NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL")))
        {
            const MI_Class *resultClass;
            MI_Boolean moreResults = MI_TRUE;
            MI_Result result = MI_RESULT_FAILED;
            const MI_Char *errorMessage;
            const MI_Instance *completionDetails;
            unsigned int resultCount = 0;

            {/* success */
                MI_Session_EnumerateClasses(&session, 0, NULL, PAL_T("namespace"), PAL_T("testClass"), MI_FALSE, NULL, &operation);
                NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

                while (moreResults && (++resultCount <= 10))
                {
                    MI_Operation_GetClass(&operation, &resultClass, &moreResults, &result, &errorMessage, &completionDetails);
                    NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
                }
                NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
                MI_Operation_Close(&operation);
            }
            {/* no class */
                MI_Session_EnumerateClasses(&session, 0, NULL, PAL_T("namespace"), NULL, MI_FALSE, NULL, &operation);
                NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));
                resultCount = 0;
                moreResults = MI_TRUE;
                while (moreResults && (++resultCount <= 10))
                {
                    MI_Operation_GetClass(&operation, &resultClass, &moreResults, &result, &errorMessage, &completionDetails);
                    NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
                }
                NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
                MI_Operation_Close(&operation);
            }
            {/* no opertion */
#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
                MI_Session_EnumerateClasses(&session, 0, NULL, PAL_T("namespace"), PAL_T("testClass"), MI_FALSE, NULL, NULL);
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif
                /* nothing more we can do as no where for result to go */
            }

            MI_Session_Close(&session, NULL, NULL);
        }

        MI_Application_Close(&application);
    }
}
NitsEndTest
#endif

NitsTest2(MI_Session_EnumerateClasses_Sync_TransportNotSupported, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test2,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    
    const MI_Class *resultClass;
    MI_Boolean moreResults = MI_TRUE;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_EnumerateClasses(session, 0, NULL, PAL_T("namespace"), PAL_T("testClass"), MI_FALSE, NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    MI_Operation_GetClass(&operation, &resultClass, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_NOT_SUPPORTED, PAL_T("Operation should fail with not supported"));
    MI_Operation_Close(&operation);

}
NitsEndTest

NitsTest2(MI_Session_EnumerateClasses_Async_AutoAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 10;
    callbacks.callbackContext = testData;
    callbacks.classResult = GetClassResult;

    MI_Session_EnumerateClasses(session, 0, NULL, PAL_T("namespace"), PAL_T("testClass"), MI_FALSE, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->classCount, (MI_Uint32)g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

/*==========================================================================================*/
/*=================================== Subscribe Instances ==================================*/
/*==========================================================================================*/

NitsTest2(MI_Session_Subscribe_Sync, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    
    const MI_Instance *resultInstance;
    const MI_Char *bookmark;
    const MI_Char *machineID;
    MI_Boolean moreResults = MI_TRUE;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;
    unsigned int resultCount = 0;

    MI_Session_Subscribe(session, 0, NULL, PAL_T("namespace"), PAL_T("dialect"), PAL_T("filter"), NULL, NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    while (moreResults && (++resultCount <= 10))
    {
        MI_Operation_GetIndication(&operation, &resultInstance, &bookmark, &machineID, &moreResults, &result, &errorMessage, &completionDetails);
        NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
    }
    NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest2(MI_Session_Subscribe_Sync_WithOptions, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    
    MI_OperationOptions options = MI_OPERATIONOPTIONS_NULL;
    if (NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, &options), MI_RESULT_OK, PAL_T("NewOperationOptions should succeed")))
    {
        const MI_Instance *resultInstance;
        const MI_Char *bookmark;
        const MI_Char *machineID;
        MI_Boolean moreResults = MI_TRUE;
        MI_Result result;
        const MI_Char *errorMessage;
        const MI_Instance *completionDetails;
        unsigned int resultCount = 0;

        NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
        NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
        {
            MI_Value value;
            value.string = (MI_Char*) PAL_T("hello world");
            NitsCompare(options.ft->SetCustomOption(&options, PAL_T("option3"), MI_STRING, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomString should work"));
        }

        MI_Session_Subscribe(session, 0, &options, PAL_T("namespace"), PAL_T("dialect"), PAL_T("filter"), NULL, NULL, &operation);
        NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

        while (moreResults && (++resultCount <= 10))
        {
            MI_Operation_GetIndication(&operation, &resultInstance, &bookmark, &machineID, &moreResults, &result, &errorMessage, &completionDetails);
            NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
        }
        NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
        MI_Operation_Close(&operation);

        MI_OperationOptions_Delete(&options);
    }
}
NitsEndTest

#if 0
NitsTest(MI_Session_Subscribe_Sync_WithDeliveryOptions)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("MI_Application_Initialize returns OK")) &&
        NitsAssert(application.ft != NULL, PAL_T("MI_Application function table should not be NULL")))
    {
        MI_SubscriptionDeliveryOptions options = MI_SUBSCRIPTIONDELIVERYOPTIONS_NULL;
        if (NitsCompare(MI_Application_NewSubscriptionDeliveryOptions(&application, MI_SubscriptionDeliveryType_Push, &options), MI_RESULT_OK, PAL_T("NewSubscribeDeliveryOptions should succeed")))
        {
            NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
            NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 22, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
            {
                MI_Datetime datetime;
                NitsCompare(options.ft->SetDateTime(&options, PAL_T("option3"), &datetime, 0), MI_RESULT_OK, PAL_T("SetDateTime should work"));
            }
            {
                MI_Interval interval;
                NitsCompare(options.ft->SetInterval(&options, PAL_T("option4"), &interval, 0), MI_RESULT_OK, PAL_T("SetInterval should work"));
            }
            {
                MI_UserCredentials creds = { 0 };
                creds.authenticationType = MI_AUTH_TYPE_BASIC;
                creds.credentials.usernamePassword.username = PAL_T("username");
                creds.credentials.usernamePassword.domain = PAL_T("domain");
                creds.credentials.usernamePassword.password = PAL_T("password");
                NitsCompare(options.ft->AddCredentials(&options, PAL_T("option5"), &creds, 0), MI_RESULT_OK, PAL_T("AddCredentials should work"));
            }

            if (NitsCompare(MI_Application_NewSession(&application, PAL_T("Test1"), NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
                NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL")))
            {
                const MI_Instance *resultInstance;
                const MI_Char *bookmark;
                const MI_Char *machineID;
                MI_Boolean moreResults = MI_TRUE;
                MI_Result result;
                const MI_Char *errorMessage;
                const MI_Instance *completionDetails;
                unsigned int resultCount = 0;

                MI_Session_Subscribe(&session, 0, NULL, PAL_T("namespace"), PAL_T("dialect"), PAL_T("filter"), &options, NULL, &operation);
                NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

                while (moreResults && (++resultCount <= 10))
                {
                    MI_Operation_GetIndication(&operation, &resultInstance, &bookmark, &machineID, &moreResults, &result, &errorMessage, &completionDetails);
                    NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
                }
                NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
                MI_Operation_Close(&operation);

                MI_Session_Close(&session, NULL, NULL);
            }
            MI_SubscriptionDeliveryOptions_Delete(&options);
        }
        MI_Application_Close(&application);
    }
}
NitsEndTest

NitsTest(MI_Session_Subscribe_Sync_InvalidParameters)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("MI_Application_Initialize returns OK")) &&
        NitsAssert(application.ft != NULL, PAL_T("MI_Application function table should not be NULL")))
    {
        if (NitsCompare(MI_Application_NewSession(&application, PAL_T("Test1"), NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
            NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL")))
        {
            const MI_Instance *resultInstance;
            const MI_Char *bookmark;
            const MI_Char *machineID;
            MI_Boolean moreResults = MI_TRUE;
            MI_Result result;
            MI_Result returnValue;
            const MI_Char *errorMessage;
            const MI_Instance *completionDetails;
            unsigned int resultCount = 0;

            {/* success */
                MI_Session_Subscribe(&session, 0, NULL, PAL_T("namespace"), PAL_T("dialect"), PAL_T("filter"), NULL, NULL, &operation);
                NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

                while (moreResults && (++resultCount <= 10))
                {
                    MI_Operation_GetIndication(&operation, &resultInstance, &bookmark, &machineID, &moreResults, &result, &errorMessage, &completionDetails);
                    NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
                }
                NitsCompare(resultCount, 10, PAL_T("Should have 10 results"));
                NitsCompare(moreResults, MI_FALSE, PAL_T("Need no more results for operation close to work properly"));

#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
                returnValue = MI_Operation_GetIndication(NULL, &resultInstance, &bookmark, &machineID, &moreResults, &result, &errorMessage, &completionDetails);
                NitsCompare(returnValue, MI_RESULT_INVALID_PARAMETER, PAL_T("Should get invalid parameter"));
                returnValue = MI_Operation_GetIndication(&operation, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
                NitsCompare(returnValue, MI_RESULT_INVALID_PARAMETER, PAL_T("Should get invalid parameter"));
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif

                MI_Operation_Close(&operation);
            }
            {/* no filter */
                MI_Session_Subscribe(&session, 0, NULL, PAL_T("namespace"), PAL_T("dialect"), NULL, NULL, NULL, &operation);

                NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

                MI_Operation_GetIndication(&operation, &resultInstance, &bookmark, &machineID, &moreResults, &result, &errorMessage, &completionDetails);
                NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
                if (moreResults)
                {
                    MI_Operation_Cancel(&operation, MI_REASON_NONE);
                    while (moreResults)
                    {
                        MI_Operation_GetIndication(&operation, &resultInstance, &bookmark, &machineID, &moreResults, &result, &errorMessage, &completionDetails);
                    }
                }
                MI_Operation_Close(&operation);
            }
            {/* no opertion */
#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
                MI_Session_Subscribe(&session, 0, NULL, PAL_T("namespace"), PAL_T("dialect"), PAL_T("filter"), NULL, NULL, NULL);
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif
                /* nothing more we can do as no where for result to go */
            }
            {
                MI_SubscriptionDeliveryOptions options = MI_SUBSCRIPTIONDELIVERYOPTIONS_NULL;
                if (NitsCompare(MI_Application_NewSubscriptionDeliveryOptions(&application, MI_SubscriptionDeliveryType_Push, &options), MI_RESULT_OK, PAL_T("NewSubscribeDeliveryOptions should succeed")))
                {
                    {
                        MI_Datetime datetime;
                        NitsCompare(options.ft->SetDateTime(NULL, PAL_T("option3"), &datetime, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("SetDateTime should fail"));
                        NitsCompare(options.ft->SetDateTime(&options, NULL, &datetime, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("SetDateTime should fail"));
                        NitsCompare(options.ft->SetDateTime(&options, PAL_T("option3"), NULL, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("SetDateTime should fail"));
                        NitsCompare(options.ft->SetDateTime(&options, PAL_T("option3"), &datetime, 42), MI_RESULT_INVALID_PARAMETER, PAL_T("SetDateTime should fail"));
                    }
                    {
                        MI_Interval interval;
                        NitsCompare(options.ft->SetInterval(NULL, PAL_T("option4"), &interval, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("SetInterval should fail"));
                        NitsCompare(options.ft->SetInterval(&options, NULL, &interval, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("SetInterval should fail"));
                        NitsCompare(options.ft->SetInterval(&options, PAL_T("option4"), NULL, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("SetInterval should fail"));
                        NitsCompare(options.ft->SetInterval(&options, PAL_T("option4"), &interval, 32), MI_RESULT_INVALID_PARAMETER, PAL_T("SetInterval should fail"));
                    }
                    MI_SubscriptionDeliveryOptions_Delete(&options);
                }
            }
            MI_Session_Close(&session, NULL, NULL);
        }

        MI_Application_Close(&application);
    }
}
NitsEndTest
#endif

NitsTest2(MI_Session_Subscribe_Sync_TransportNotSupported, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test2,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    
    const MI_Instance *resultInstance;
    const MI_Char *bookmark;
    const MI_Char *machineID;
    MI_Boolean moreResults = MI_TRUE;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_Subscribe(session, 0, NULL, PAL_T("namespace"), PAL_T("dialect"), PAL_T("filter"), NULL, NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    MI_Operation_GetIndication(&operation, &resultInstance, &bookmark, &machineID, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_NOT_SUPPORTED, PAL_T("Operation should fail with not supported"));
    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest2(MI_Session_Subscribe_Async_AutoAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 10;
    callbacks.callbackContext = testData;
    callbacks.indicationResult = GetIndicationResult;

    MI_Session_Subscribe(session, 0, NULL, PAL_T("namespace"), PAL_T("dialect"), PAL_T("filter"), NULL, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->indicationCount, (MI_Uint32)g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

#if 0
extern "C" void ValidateCondition(MI_CallbackMode writeErrorMode, MI_CallbackMode promptUserMode,
                          MI_OperationCallback_ResponseType writeErrorResponse, MI_OperationCallback_ResponseType promptUserResponse)
{
    NitsAssert(g_PSSemanticsProgressObject.WriteErrorCalled== 2, PAL_T(" WriteError not called"));    
    if( writeErrorMode == MI_CALLBACKMODE_INQUIRE )
    {
        if(writeErrorResponse == MI_OperationCallback_ResponseType_YesToAll)
        {
            NitsCompare(g_PSSemanticsProgressObject.writeErrorCallback, 1, PAL_T(" writeErrorCallback is not 1"));   
        }
        else
        {
            NitsAssert(g_PSSemanticsProgressObject.writeErrorCallback == 2, PAL_T(" writeErrorCallback is not 2"));               
        }
    }
    else
    {
        NitsAssert(g_PSSemanticsProgressObject.writeErrorCallback == 0, PAL_T(" writeErrorCallback is not 0"));
    }

    if( promptUserMode == MI_CALLBACKMODE_INQUIRE)
    {
        NitsAssert(g_PSSemanticsProgressObject.PromptUserCalled== 2, PAL_T(" PromptUser not called twice"));
    }
    else if( promptUserMode == MI_CALLBACKMODE_REPORT)
    {
        NitsAssert(g_PSSemanticsProgressObject.PromptUserCalled== 2, PAL_T(" PromptUser not called twice"));
     
    }
    else
    {
        NitsAssert(g_PSSemanticsProgressObject.PromptUserCalled== 1, PAL_T(" PromptUser not called once"));
    }
}
extern "C" void Helper_MI_Session_Invoke_Async_PSSemantics_Part2(
                                                MI_OperationCallback_ResponseType writeErrorResponse = MI_OperationCallback_ResponseType_Yes,
                                                MI_OperationCallback_ResponseType promptUserResponse = MI_OperationCallback_ResponseType_Yes,
                                                MI_CallbackMode writeErrorMode = MI_CALLBACKMODE_REPORT, 
                                                MI_CallbackMode promptUserMode = MI_CALLBACKMODE_INQUIRE)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationOptions options = MI_OPERATIONOPTIONS_NULL;
    g_WriteErrorResponseType = writeErrorResponse;
    g_PromptUserResponseType = promptUserResponse;

    memset(&g_PSSemanticsProgressObject, 0 , sizeof(PSSemanticsProgressResult));    
    
    callbacks.instanceResult = GetInstanceResult;
    callbacks.promptUser = MI_Session_GetInstance_Async_PS_Semantics_PromptUser;
    callbacks.writeError = MI_Session_GetInstance_Async_PS_Semantics_WriteError;
    callbacks.writeMessage = MI_Session_GetInstance_Async_PS_Semantics_WriteMessage;
    callbacks.writeProgress = MI_Session_GetInstance_Async_PS_Semantics_WriteProgress;

    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("MI_Application_Initialize returns OK")) &&
        NitsAssert(application.ft != NULL, PAL_T("MI_Application function table should not be NULL")))
    {
        if (NitsCompare(MI_Application_NewOperationOptions(&application, MI_FALSE, &options), MI_RESULT_OK, PAL_T("NewOperationOptions should succeed")))
        {
            NitsAssert( MI_OperationOptions_SetWriteErrorMode(&options, writeErrorMode) == MI_RESULT_OK, PAL_T("Unable to ser Write Error mode"));
            NitsAssert( MI_OperationOptions_SetPromptUserMode(&options, promptUserMode) == MI_RESULT_OK, PAL_T("Unable to ser Prompt User mode"));    
            if (NitsCompare(MI_Application_NewSession(&application, PAL_T("Test1"), NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
                NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL")))
            {
                MI_Session_Invoke(&session, 0, &options, NULL, PAL_T("testClass"), PAL_T("TestMethod"), NULL, NULL, &callbacks, &operation);
                NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

                MI_Session_Close(&session, NULL, NULL);
                //Validate the condition
                ValidateCondition(writeErrorMode, promptUserMode, writeErrorResponse, promptUserResponse);
            }
            MI_OperationOptions_Delete(&options);
        }

        MI_Application_Close(&application);
    }
}

NitsTest(MI_Session_Invoke_Async_PSSemantics_Part2)
{
    NitsTrace(PAL_T("Executing operation 1"));
    Helper_MI_Session_Invoke_Async_PSSemantics_Part2();
    NitsTrace(PAL_T("Executing operation 2"));    
    Helper_MI_Session_Invoke_Async_PSSemantics_Part2(MI_OperationCallback_ResponseType_YesToAll, MI_OperationCallback_ResponseType_YesToAll);
    NitsTrace(PAL_T("Executing operation 3"));    
    Helper_MI_Session_Invoke_Async_PSSemantics_Part2(MI_OperationCallback_ResponseType_YesToAll, MI_OperationCallback_ResponseType_YesToAll, MI_CALLBACKMODE_INQUIRE,
                MI_CALLBACKMODE_REPORT);        
    NitsTrace(PAL_T("Executing operation 4"));    
    Helper_MI_Session_Invoke_Async_PSSemantics_Part2(MI_OperationCallback_ResponseType_YesToAll, MI_OperationCallback_ResponseType_YesToAll, MI_CALLBACKMODE_REPORT,
                MI_CALLBACKMODE_REPORT);    
    NitsTrace(PAL_T("Executing operation 5"));    
    Helper_MI_Session_Invoke_Async_PSSemantics_Part2(MI_OperationCallback_ResponseType_YesToAll, MI_OperationCallback_ResponseType_YesToAll, MI_CALLBACKMODE_REPORT,
                MI_CALLBACKMODE_IGNORE);     
}
NitsEndTest
#endif
/*==========================================================================================*/
/*===================================== TestConnection =====================================*/
/*==========================================================================================*/

NitsTest2(MI_Session_TestConnection_Sync, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;

    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;
    const MI_Instance *resultInstance;

    MI_Session_TestConnection(session, 0, NULL, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_OK, PAL_T("Operation should succeed"));
    NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest2(MI_Session_TestConnection_Async_AutoAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 0;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult;

    MI_Session_TestConnection(session, 0, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->instanceCount, (MI_Uint32)g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

NitsTest2(MI_Session_TestConnection_Async_ManualAck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    
    g_maximumInstanceCount = 0;
    callbacks.callbackContext = testData;
    callbacks.instanceResult = GetInstanceResult;

    MI_Session_TestConnection(session, MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, &callbacks, &operation);
    NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

    WaitForOperationToComplete(testData);

    NitsCompare((MI_Uint32)testData->instanceCount, (MI_Uint32)g_maximumInstanceCount, PAL_T("Number of results callbacks received"));
}
NitsEndTest

#if 0

NitsTest(MI_Session_TestConnection_Sync_InvalidParameters)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;
    const MI_Instance *extendedInfo;
    MI_Boolean moreResults;
    MI_Result resultCode;
    MI_Result returnValue;
    const MI_Char *errorMessage;
    MI_OperationCallbacks callbacks = MI_OPERATIONCALLBACKS_NULL;
    callbacks.instanceResult = GetInstanceResult_Fail;
    const MI_Instance *resultInstance = NULL;

    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("MI_Application_Initialize returns OK")) &&
        NitsAssert(application.ft != NULL, PAL_T("MI_Application function table should not be NULL")))
    {
        if (NitsCompare(MI_Application_NewSession(&application, PAL_T("Test1"), NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
            NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL")))
        {
            session.ft->TestConnection(&session, 0, NULL, &operation);
            MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &resultCode, &errorMessage, &extendedInfo);
            NitsCompare(resultCode, MI_RESULT_OK, PAL_T("GetInstance should succeed"));

            returnValue = operation.ft->GetInstance(NULL, &resultInstance, NULL, &resultCode, NULL, NULL);
            NitsCompare(returnValue, MI_RESULT_INVALID_PARAMETER, PAL_T("Operation_GetClass should fail due to NULL operation"));

            returnValue = operation.ft->GetInstance(&operation, NULL, NULL, &resultCode, NULL, NULL);
            NitsCompare(returnValue, MI_RESULT_INVALID_PARAMETER, PAL_T("Operation_GetClass should fail due to NULL instance"));

            MI_Operation_Close(&operation);

            session.ft->TestConnection(NULL, 0, NULL, &operation);
            MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &resultCode, &errorMessage, &extendedInfo);
            NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetClass should faul due to NULL session"));
            MI_Operation_Close(&operation);

            session.ft->TestConnection(&session, 0, NULL, &operation);
            MI_Operation_GetInstance(&operation, NULL, &moreResults, &resultCode, &errorMessage, &extendedInfo);
            NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetInstance should fail due to NULL instance key"));
            MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &resultCode, &errorMessage, &extendedInfo);
            NitsCompare(resultCode, MI_RESULT_OK, PAL_T("GetInstances hould succeed"));
            MI_Operation_Close(&operation);

            session.ft->TestConnection(&session, 0, &callbacks, NULL);
            returnValue = MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &resultCode, &errorMessage, &extendedInfo);
            NitsCompare(returnValue, MI_RESULT_INVALID_PARAMETER, PAL_T("GetClass should fail due to closed operation"));
            MI_Operation_Close(&operation);

            session.ft->TestConnection(&session, 0, NULL, NULL);
            /* Validate it doesn't crash only as nowhere for failure to go */
            MI_Session_Close(&session, NULL, NULL);

            session.ft->TestConnection(&session, 0, NULL, &operation);
            MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &resultCode, &errorMessage, &extendedInfo);
            NitsCompare(resultCode, MI_RESULT_INVALID_PARAMETER, PAL_T("GetClass should fail because session is already closed"));
            MI_Operation_Close(&operation);

        }
        MI_Application_Close(&application);
    }
}
NitsEndTest
#endif

NitsTest2(MI_Session_TestConnection_TransportNotSupported, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test2,
          SetupDefaultSession, SetupDefaultSessionDefaults)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Session *session = &testData->session;
    MI_Operation operation = MI_OPERATION_NULL;

    const MI_Instance *resultInstance;
    MI_Boolean moreResults;
    MI_Result result;
    const MI_Char *errorMessage;
    const MI_Instance *completionDetails;

    MI_Session_TestConnection(session, 0, NULL, &operation);

    MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
    NitsCompare(result, MI_RESULT_NOT_SUPPORTED, PAL_T("Operation should succeed"));
    NitsAssert(moreResults==MI_FALSE, PAL_T("Should be no more results"));

    MI_Operation_Close(&operation);
}
NitsEndTest

NitsTest(TestMapErrorToMiErrorCategory)
{
    MI_ErrorCategory errorCategory;
    
#if defined(_MSC_VER)
    errorCategory = MI_Utilities_MapErrorToMiErrorCategory(MI_RESULT_TYPE_WIN32, ERROR_NOT_SUPPORTED);
    NitsAssert(errorCategory==MI_ERRORCATEGORY_INVALID_OPERATION, PAL_T("ErrorCategory is not MI_ERRORCATEGORY_INVALID_OPERATION"));
#endif

    errorCategory = MI_Utilities_MapErrorToMiErrorCategory(MI_RESULT_TYPE_MI, MI_RESULT_ACCESS_DENIED);
    NitsAssert(errorCategory==MI_ERRORCATEGORY_ACCESS_DENIED, PAL_T("ErrorCategory is not MI_ERRORCATEGORY_ACCESS_DENIED"));
}
NitsEndTest

NitsTest(TestCimErrorFromErrorCode)
{
    MI_Value value;
#if defined(_MSC_VER)
    MI_Instance *pInst = NULL;
    LANGID idLang = GetSystemDefaultLangID();

    if(NitsCompare(MI_Utilities_CimErrorFromErrorCode(ERROR_FILE_NOT_FOUND, MI_RESULT_TYPE_WIN32, NULL, &pInst), MI_RESULT_OK,PAL_T("Got an error")))
    {
        if(NitsCompare( MI_Instance_GetElement( pInst, PAL_T("MessageID"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("MessageID is not there")) )
        {
            NitsTrace((MI_String)value.string);
            NitsCompareString((MI_String)value.string, PAL_T("Windows System Error 2"), PAL_T("MessageID != Windows System Error 2"));
        }
        if(NitsCompare( MI_Instance_GetElement( pInst, PAL_T("Message"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("Message is not there")) )
        {
            NitsTrace((MI_String)value.string);        
            //Process only for en-us
            if( idLang == 0x0409) 
            {
                NitsCompareString((MI_String)value.string, PAL_T("The system cannot find the file specified. "), PAL_T("Message != The system cannot find the file specified."));
            }
        }   
        if(NitsCompare( MI_Instance_GetElement( pInst, PAL_T("OMI_ErrorMessage"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("OMI_ErrorMessage is not there")) )
        {
            NitsTrace((MI_String)value.string);        
            //Process only for en-us
            if( idLang == 0x0409) 
            {
                NitsCompareString((MI_String)value.string, PAL_T("The system cannot find the file specified. "), PAL_T("OMI_ErrorMessage != The system cannot find the file specified."));
            }
        }          
        if(NitsCompare( MI_Instance_GetElement( pInst, PAL_T("OMI_Category"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("Error_Category is not there")) )
        {
            NitsCompare(value.uint16, MI_ERRORCATEGORY_OBJECT_NOT_FOUND,PAL_T("OMI_Category != MI_ERRORCATEGORY_OBJECT_NOT_FOUND"));
        } 
        if(NitsCompare( MI_Instance_GetElement( pInst, PAL_T("OMI_Type"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("OMI_Type is not there")) )
        {
            NitsTrace((MI_String)value.string);
            NitsCompareString((MI_String)value.string, PAL_T("Win32"), PAL_T("error_Type != Win32"));
        }        
        if(NitsCompare( MI_Instance_GetElement( pInst, PAL_T("OMI_Code"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("OMI_Code is not there")) )
        {
            NitsCompare(value.uint32, ERROR_FILE_NOT_FOUND, PAL_T("OMI_Code != ERROR_FILE_NOT_FOUND"));
        }    
        if(NitsCompare( MI_Instance_GetElement( pInst, PAL_T("CIMStatusCode"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("ErrorType is not there")) )
        {
            NitsCompare(value.uint32, MI_RESULT_NOT_FOUND,PAL_T("CIMStatusCode != MI_RESULT_FAILED"));
        }     
    }
    MI_Instance_Delete(pInst);
#endif

    MI_Instance* pInst3 = NULL;
    if(NitsCompare(MI_Utilities_CimErrorFromErrorCode(MI_RESULT_INVALID_CLASS, MI_RESULT_TYPE_MI, PAL_T("Testing MI"), &pInst3), MI_RESULT_OK,PAL_T("Got an error")))
    {
        if(NitsCompare( MI_Instance_GetElement( pInst3, PAL_T("MessageID"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("MessageID is not there")) )
        {
            NitsTrace((MI_String)value.string);  
            NitsCompareString((MI_String)value.string, PAL_T("OMI:MI_Result:5"), PAL_T("MessageID != MI RESULT 5"));
        }
        if(NitsCompare( MI_Instance_GetElement( pInst3, PAL_T("Message"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("Expect Message is there")) )
        {
            NitsTrace((MI_String)value.string);
            NitsCompareString((MI_String)value.string, PAL_T("Testing MI"), PAL_T("Message != Testing MI"));
        }
        if(NitsAssert( MI_Instance_GetElement( pInst3, PAL_T("OMI_ErrorMessage"), &value, NULL, NULL, NULL) == MI_RESULT_OK, PAL_T("Expect Message is there")) )
        {
            NitsTrace((MI_String)value.string);        
            //Process only for en-us
#if defined(_MSC_VER)
            if( idLang == 0x0409) 
#endif
            {
                NitsCompareString((MI_String)value.string, PAL_T("The specified class does not exist."), PAL_T("OMI_ErrorMessage != The specified Class does not exist."));
            }

        }            
        if(NitsCompare( MI_Instance_GetElement( pInst3, PAL_T("OMI_Category"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("OMI_Category is not there")) )
        {
            NitsCompare(value.uint16, MI_ERRORCATEGORY_METADATA_ERROR,PAL_T("OMI_Category != MI_ERRORCATEGORY_METADATA_ERROR"));
        } 
        if(NitsCompare( MI_Instance_GetElement( pInst3, PAL_T("OMI_Type"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("OMI_Type is not there")) )
        {
            NitsTrace((MI_String)value.string);
            NitsCompareString((MI_String)value.string, PAL_T("MI"), PAL_T("OMI_Type != MI"));
        }          
        if(NitsCompare( MI_Instance_GetElement( pInst3, PAL_T("OMI_Code"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("OMI_Code is not there")) )
        {
            NitsCompare(value.uint32, MI_RESULT_INVALID_CLASS,PAL_T("OMI_Code != MI_RESULT_INVALID_CLASS"));
        }    
        if(NitsCompare( MI_Instance_GetElement( pInst3, PAL_T("CIMStatusCode"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("CIMStatusCode is not there")) )
        {
            NitsCompare(value.uint32, MI_RESULT_INVALID_CLASS,PAL_T("CIMStatusCode != MI_RESULT_INVALID_CLASS"));
        }    
    }
    MI_Instance_Delete(pInst3);

    MI_Instance* pInst4 = NULL;
    if(NitsCompare(MI_Utilities_CimErrorFromErrorCode(E2BIG, MI_RESULT_TYPE_ERRNO, PAL_T("Testing MI"), &pInst4), MI_RESULT_OK,PAL_T("Got an error")))
    {
        if(NitsCompare( MI_Instance_GetElement( pInst4, PAL_T("MessageID"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("MessageID is not there")) )
        {
            NitsTrace((MI_String)value.string);  
            NitsCompareString((MI_String)value.string, PAL_T("CRT errno 7"), PAL_T("MessageID != MI RESULT 7"));
        }
        if(NitsCompare( MI_Instance_GetElement( pInst4, PAL_T("Message"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("Expect Message is there")) )
        {
            NitsTrace((MI_String)value.string);
            NitsCompareString((MI_String)value.string, PAL_T("Testing MI"), PAL_T("Message != Testing MI"));
        }
        if(NitsAssert( MI_Instance_GetElement( pInst4, PAL_T("OMI_ErrorMessage"), &value, NULL, NULL, NULL) == MI_RESULT_OK, PAL_T("Expect Message is there")) )
        {
            NitsTrace((MI_String)value.string);        
            //Process only for en-us
#if defined(_MSC_VER)
            if( idLang == 0x0409) 
#endif
            {
#if !defined(CONFIG_HAVE_STRERROR_R)
                NitsCompareString((MI_String)value.string, PAL_T("Argument list too long"), PAL_T("OMI_ErrorMessage != Argument list too long."));
#endif
            }

        }            
        if(NitsCompare( MI_Instance_GetElement( pInst4, PAL_T("OMI_Category"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("OMI_Category is not there")) )
        {
            NitsCompare(value.uint16, MI_ERRORCATEGORY_NOT_SPECIFIED,PAL_T("OMI_Category != MI_ERRORCATEGORY_METADATA_ERROR"));
        } 
        if(NitsCompare( MI_Instance_GetElement( pInst4, PAL_T("OMI_Type"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("OMI_Type is not there")) )
        {
            NitsTrace((MI_String)value.string);
            NitsCompareString((MI_String)value.string, PAL_T("ERRNO"), PAL_T("OMI_Type != ERRNO"));
        }          
        if(NitsCompare( MI_Instance_GetElement( pInst4, PAL_T("OMI_Code"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("OMI_Code is not there")) )
        {
            NitsCompare(value.uint32, E2BIG,PAL_T("OMI_Code != E2BIG"));
        }    
        if(NitsCompare( MI_Instance_GetElement( pInst4, PAL_T("CIMStatusCode"), &value, NULL, NULL, NULL) , MI_RESULT_OK, PAL_T("CIMStatusCode is not there")) )
        {
            NitsCompare(value.uint32, MI_RESULT_FAILED,PAL_T("CIMStatusCode != MI_RESULT_FAILED"));
        }    
        MI_Instance_Delete(pInst4);
    }
}
NitsEndTest

#if 0
NitsTest(TestPassingParametersToMethodThatNeedsNoParameters)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;

    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("MI_Application_Initialize returns OK")) &&
        NitsAssert(application.ft != NULL, PAL_T("MI_Application function table should not be NULL")))
    {
        MI_Instance *instance = NULL;
        MI_Instance *parameter = NULL;
        MI_Value value;
        value.string = PAL_T("0");

        if (NitsCompare(MI_Application_NewInstance(&application, PAL_T("Win32_Process"), NULL, &instance), MI_RESULT_OK, PAL_T("instance")) &&
            NitsAssert(instance != NULL, PAL_T("failed to create instance")) &&
            NitsCompare(MI_Instance_AddElement(instance, PAL_T("Handle"), &value, MI_STRING, MI_FLAG_KEY), MI_RESULT_OK, PAL_T("Add instance handle key")) && 
            NitsCompare(MI_Application_NewParameterSet(&application, NULL, &parameter), MI_RESULT_OK, PAL_T("parameter")) &&
            NitsAssert(parameter != NULL, PAL_T("failed to create parameter")))
        {
            if (NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
                NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL")))
            {
                MI_Session_Invoke(&session, 0, NULL, PAL_T("root\\cimv2"), PAL_T("Win32_Process"), PAL_T("GetOwner"), instance, parameter, NULL, &operation);
                NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

                const MI_Instance *resultInstance;
                MI_Boolean moreResults;
                MI_Result result;
                const MI_Char *errorMessage;
                const MI_Instance *completionDetails;

                MI_Operation_GetInstance(&operation, &resultInstance, &moreResults, &result, &errorMessage, &completionDetails);
                NitsCompare(result, MI_RESULT_INVALID_PARAMETER, PAL_T("Should fail with invalid parameter"));

                MI_Operation_Close(&operation);

                MI_Session_Close(&session, NULL, NULL);
            }
            MI_Instance_Delete(instance);
            MI_Instance_Delete(parameter);
        }

        MI_Application_Close(&application);
    }
}
NitsEndTest
#endif

void MI_OperationOptions_ReadOperations_Internal(
    MI_OperationOptions& options,
    bool cloned = false)
{
    MI_OperationOptions *nullOptions = NULL;
    const MI_Char *nullString = NULL;
    const MI_Char **nullStringPtr = NULL;
    MI_Uint32 *nullNumberPtr = 0;
    MI_Uint32 *nullIndex = 0;
    MI_Uint32 index = 0;
    MI_Value *nullMIValuePtr = NULL;
    MI_Type *nullMITypePtr = 0;
    MI_Uint32 flag;

    // Read string
    {
        const MI_Char * stringValue = NULL;
        const MI_Char * optionName = PAL_T("option1");
        NitsCompare(options.ft->GetString(&options, optionName, &stringValue, nullIndex, &flag), MI_RESULT_OK, PAL_T("GetString should work"));
        NitsCompare(options.ft->GetString(&options, optionName, &stringValue, &index, 0), MI_RESULT_OK, PAL_T("GetString should work"));
        NitsCompareString(stringValue, PAL_T("value1"), PAL_T("GetString should work"));
        if (!cloned) NitsCompare(index, 1, PAL_T("GetString should work"));

        NitsCompare(options.ft->GetString(&options, PAL_T("option2"), &stringValue, nullIndex, 0), MI_RESULT_TYPE_MISMATCH, PAL_T("GetString should return MI_RESULT_TYPE_MISMATCH"));
        NitsCompare(options.ft->GetString(&options, PAL_T("optionbla"), &stringValue, nullIndex, 0), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("GetString should return MI_RESULT_NO_SUCH_PROPERTY"));
        NitsCompare(options.ft->GetString(nullOptions, optionName, &stringValue, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetString should fail"));
        NitsCompare(options.ft->GetString(&options, nullString, &stringValue, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetString should fail"));
        NitsCompare(options.ft->GetString(&options, optionName, nullStringPtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetString should fail"));
    }
    // Read number
    {
        MI_Uint32 int32Value = 0;
        const MI_Char * optionName = PAL_T("option2");
        NitsCompare(options.ft->GetNumber(&options, optionName, &int32Value, nullIndex, 0), MI_RESULT_OK, PAL_T("GetNumber should work"));
        NitsCompare(options.ft->GetNumber(&options, optionName, &int32Value, &index, 0), MI_RESULT_OK, PAL_T("GetNumber should work"));
        NitsCompare(int32Value, 33, PAL_T("GetNumber should work"));
        if (!cloned) NitsCompare(index, 2, PAL_T("GetNumber should work"));

        NitsCompare(options.ft->GetNumber(&options, PAL_T("option1"), &int32Value, nullIndex, 0), MI_RESULT_TYPE_MISMATCH, PAL_T("GetNumber return MI_RESULT_TYPE_MISMATCH"));
        NitsCompare(options.ft->GetNumber(&options, PAL_T("optionBla"), &int32Value, nullIndex, 0), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("GetNumber return MI_RESULT_NOT_FOUND"));
        NitsCompare(options.ft->GetNumber(nullOptions, optionName, &int32Value, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetNumber should fail"));
        NitsCompare(options.ft->GetNumber(&options, nullString, &int32Value, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetNumber should fail"));
        NitsCompare(options.ft->GetNumber(&options, optionName, nullNumberPtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetNumber should fail"));
    }

    // GetOptionCount
    {
        MI_Uint32 optionCount = 0;
        NitsCompare(options.ft->GetOptionCount(nullOptions, &optionCount), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionCount should fail"));
        NitsCompare(options.ft->GetOptionCount(&options, nullNumberPtr), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionCount should fail"));

        NitsCompare(options.ft->GetOptionCount(&options, &optionCount), MI_RESULT_OK, PAL_T("GetOptionCount should success"));
        MI_Uint32 expectedCount = 5;
        NitsCompare(optionCount, expectedCount, PAL_T("GetOptionCount should success"));
        if (optionCount == expectedCount)
        {
            for(MI_Uint32 i = 0; i < optionCount; i++)
            {
                MI_Value value = {0};
                MI_Type type = MI_BOOLEAN;
                const MI_Char * optionName = NULL;
                NitsCompare(options.ft->GetOptionAt(&options, i, &optionName, &value, &type, 0), MI_RESULT_OK, PAL_T("GetOptionAt should success"));
            }
        }
    }

    // GetOptionAt
    if (!cloned)
    {
        MI_Value value = {0};
        MI_Type type = MI_BOOLEAN;
        const MI_Char * optionName = NULL;
        NitsCompare(options.ft->GetOptionAt(nullOptions, 0, &optionName, &value, nullMITypePtr, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionAt should fail"));
        NitsCompare(options.ft->GetOptionAt(&options, 0, &optionName, &value, nullMITypePtr, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionAt should fail"));
        NitsCompare(options.ft->GetOptionAt(&options, 0, nullStringPtr, nullMIValuePtr, nullMITypePtr, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionAt should fail"));
        NitsCompare(options.ft->GetOptionAt(&options, 0, &optionName, &value, nullMITypePtr, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionAt should fail"));

        NitsCompare(options.ft->GetOptionAt(&options, 0x100, &optionName, &value, &type, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionAt should return MI_RESULT_INVALID_PARAMETER"));

        NitsCompare(options.ft->GetOptionAt(&options, 1, &optionName, &value, &type, 0), MI_RESULT_OK, PAL_T("GetOptionAt should success"));
        if (NitsCompare(type, MI_STRING, PAL_T("GetOptionAt should success")))
        {
            NitsCompareString(value.string, PAL_T("value1"), PAL_T("GetOptionAt should success"));
        }
    }

    // GetOption
    {
        MI_Value value = {0};
        MI_Type type = MI_BOOLEAN;
        const MI_Char * optionName = PAL_T("option1");
        NitsCompare(options.ft->GetOption(nullOptions, optionName, &value, nullMITypePtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOption should fail"));
        NitsCompare(options.ft->GetOption(&options, nullString, &value, nullMITypePtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOption should fail"));
        NitsCompare(options.ft->GetOption(&options, optionName, nullMIValuePtr, nullMITypePtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOption should fail"));
        NitsCompare(options.ft->GetOption(&options, optionName, &value, nullMITypePtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOption should fail"));
        NitsCompare(options.ft->GetOption(&options, PAL_T("optionbla"), &value, &type, &index, 0), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("GetOption should return MI_RESULT_NOT_FOUND"));

        NitsCompare(options.ft->GetOption(&options, optionName, &value, &type, &index, 0), MI_RESULT_OK, PAL_T("GetOption should success"));
        if (NitsCompare(type, MI_STRING, PAL_T("GetOption should success")))
        {
            NitsCompareString(value.string, PAL_T("value1"), PAL_T("GetOption should success"));
        }
        if (!cloned) NitsCompare(index, 1, PAL_T("GetOption should success"));
    }

    // GetEnabledChannels
    {
        const MI_Char * optionName = PAL_T("option1");
        MI_Uint32 channels[3] = {0};
        MI_Uint32 channelCount = 0;
        NitsCompare(options.ft->GetEnabledChannels(nullOptions, optionName, channels, 1, nullNumberPtr, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetEnabledChannels should fail"));
        NitsCompare(options.ft->GetEnabledChannels(&options, nullString, channels, 1, nullNumberPtr, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetEnabledChannels should fail"));
        NitsCompare(options.ft->GetEnabledChannels(&options, optionName, channels, 1, nullNumberPtr, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetEnabledChannels should fail"));

        NitsCompare(options.ft->GetEnabledChannels(&options, optionName, channels, 1, &channelCount, 0), MI_RESULT_TYPE_MISMATCH, PAL_T("GetEnabledChannels should return MI_RESULT_NOT_FOUND"));

        // too small buffer
        NitsCompare(MI_OperationOptions_GetEnabledChannels(&options, channels, 1, &channelCount, 0), MI_RESULT_FAILED, PAL_T("GetEnabledChannels should return MI_RESULT_FAILED"));

        MI_Uint32 expectedCount = 3;
        NitsCompare(MI_OperationOptions_GetEnabledChannels(&options, channels, expectedCount, &channelCount, 0), MI_RESULT_OK, PAL_T("GetEnabledChannels should success"));
        NitsCompare(MI_OperationOptions_GetEnabledChannels(&options, channels, expectedCount, &channelCount, &flag), MI_RESULT_OK, PAL_T("GetEnabledChannels should success"));

        NitsCompare(channelCount, expectedCount, PAL_T("GetEnabledChannels should success"));

        NitsCompare(channels[0], 0, PAL_T("GetEnabledChannels should success"));
        NitsCompare(channels[1], 2, PAL_T("GetEnabledChannels should success"));
        NitsCompare(channels[2], 3, PAL_T("GetEnabledChannels should success"));
    }
}

NitsTest1(MI_OperationOptions_ReadOperations, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;

    MI_OperationOptions options = MI_OPERATIONOPTIONS_NULL;

#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
    NitsCompare(MI_Application_NewOperationOptions(NULL, MI_FALSE, &options), MI_RESULT_INVALID_PARAMETER, PAL_T("NewOperationOptions invalid parameter"));
    NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("NewOperationOptions invalid parameter"));
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif

    if (NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, &options), MI_RESULT_OK, PAL_T("NewOperationOptions should succeed")))
    {
        if (NitsAssert(options.ft != NULL, PAL_T("Should have options function table")))
        {
            NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
            NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 33, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
            {
                MI_Uint8 valueArray[2];
                MI_Value value;
                value.uint8 = 10;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("uint8"), MI_UINT8, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(uint8) should work"));

                valueArray[0] = 10;
                valueArray[1] = 20;
                value.uint8a.data = valueArray;
                value.uint8a.size = 2;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("uint8a"), MI_UINT8A, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(uint8a) should work"));
            }
            {
                NitsCompare(MI_OperationOptions_EnableChannel(&options, 1), MI_RESULT_OK, PAL_T("MI_OperationOptions_EnableChannel should work"));
                NitsCompare(MI_OperationOptions_EnableChannel(&options, 2), MI_RESULT_OK, PAL_T("MI_OperationOptions_EnableChannel should work"));
                NitsCompare(MI_OperationOptions_EnableChannel(&options, 3), MI_RESULT_OK, PAL_T("MI_OperationOptions_EnableChannel should work"));
                NitsCompare(MI_OperationOptions_DisableChannel(&options, 1), MI_RESULT_OK, PAL_T("MI_OperationOptions_DisableChannel should work"));
            }

            MI_OperationOptions_ReadOperations_Internal(options);
        }
#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6011)
#endif
        options.ft->Delete(NULL);
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif
        MI_OperationOptions_Delete(&options);
    }
}
NitsEndTest

NitsTest1(MI_OperationOptions_CloneTest, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;

    MI_OperationOptions options = MI_OPERATIONOPTIONS_NULL;

#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
    NitsCompare(MI_Application_NewOperationOptions(NULL, MI_FALSE, &options), MI_RESULT_INVALID_PARAMETER, PAL_T("NewOperationOptions invalid parameter"));
    NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("NewOperationOptions invalid parameter"));
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif

    if (NitsCompare(MI_Application_NewOperationOptions(application, MI_FALSE, &options), MI_RESULT_OK, PAL_T("NewOperationOptions should succeed")))
    {
        if (NitsAssert(options.ft != NULL, PAL_T("Should have options function table")))
        {
            NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
            NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 33, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
            {
                MI_Uint8 valueArray[2];
                MI_Value value;
                value.uint8 = 10;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("uint8"), MI_UINT8, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(uint8) should work"));

                valueArray[0] = 10;
                valueArray[1] = 20;
                value.uint8a.data = valueArray;
                value.uint8a.size = 2;
                NitsCompare(options.ft->SetCustomOption(&options, PAL_T("uint8a"), MI_UINT8A, &value, MI_FALSE, 0), MI_RESULT_OK, PAL_T("SetCustomOption(uint8a) should work"));
            }
            {
                NitsCompare(MI_OperationOptions_EnableChannel(&options, 1), MI_RESULT_OK, PAL_T("MI_OperationOptions_EnableChannel should work"));
                NitsCompare(MI_OperationOptions_EnableChannel(&options, 2), MI_RESULT_OK, PAL_T("MI_OperationOptions_EnableChannel should work"));
                NitsCompare(MI_OperationOptions_EnableChannel(&options, 3), MI_RESULT_OK, PAL_T("MI_OperationOptions_EnableChannel should work"));
                NitsCompare(MI_OperationOptions_DisableChannel(&options, 1), MI_RESULT_OK, PAL_T("MI_OperationOptions_DisableChannel should work"));
            }
            MI_OperationOptions clonedOptions = MI_OPERATIONOPTIONS_NULL;
            if (NitsCompare(MI_OperationOptions_Clone(&options, &clonedOptions), MI_RESULT_OK, PAL_T("MI_OperationOptions_Clone returns OK")) &&
            NitsAssert(clonedOptions.ft != NULL, PAL_T("MI_OperationOptions function table should not be NULL")))
            {
                NitsCompare((MI_Uint32)options.reserved1, (MI_Uint32)clonedOptions.reserved1, PAL_T("Cloned options should has same mustUnderstand value"));
                MI_OperationOptions_ReadOperations_Internal(clonedOptions, true);
                MI_OperationOptions_Delete(&clonedOptions);
            }
        }
#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6011)
#endif
        options.ft->Delete(NULL);
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif
        MI_OperationOptions_Delete(&options);
    }
}
NitsEndTest

void MI_DestinationOptions_ReadOperations_Internal(
    MI_DestinationOptions& options,
    MI_UserCredentials& creds,
    bool cloned = false)
{
    MI_DestinationOptions *nullOptions = NULL;
    const MI_Char *nullString = NULL;
    const MI_Char **nullStringPtr = NULL;
    MI_Uint32 *nullNumberPtr = 0;
    MI_Uint32 *nullIndex = 0;
    MI_Uint32 index = 0;
    MI_Value *nullMIValuePtr = NULL;
    MI_Type *nullMITypePtr = 0;
    MI_Uint32 flag;

    // Read string
    {
        const MI_Char * stringValue = NULL;
        const MI_Char * optionName = PAL_T("option1");
        NitsCompare(options.ft->GetString(&options, optionName, &stringValue, nullIndex, &flag), MI_RESULT_OK, PAL_T("GetString should work"));
        NitsCompare(options.ft->GetString(&options, optionName, &stringValue, &index, 0), MI_RESULT_OK, PAL_T("GetString should work"));
        NitsCompareString(stringValue, PAL_T("value1"), PAL_T("GetString should work"));

#if defined (_MSC_VER)
        if (!cloned) NitsCompare(index, 2, PAL_T("GetString should work"));
#else
        if (!cloned) NitsCompare(index, 0, PAL_T("GetString should work"));
#endif

        NitsCompare(options.ft->GetString(&options, PAL_T("option2"), &stringValue, nullIndex, 0), MI_RESULT_TYPE_MISMATCH, PAL_T("GetString should return MI_RESULT_TYPE_MISMATCH"));
        NitsCompare(options.ft->GetString(&options, PAL_T("optionbla"), &stringValue, nullIndex, 0), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("GetString should return MI_RESULT_NOT_FOUND"));
        NitsCompare(options.ft->GetString(nullOptions, optionName, &stringValue, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetString should fail"));
        NitsCompare(options.ft->GetString(&options, nullString, &stringValue, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetString should fail"));
        NitsCompare(options.ft->GetString(&options, optionName, nullStringPtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetString should fail"));
    }

    // Read default Locale
#if defined(_MSC_VER)
    {
        ULONG numLangs = 0;
        ULONG lenBuffer = MI_MAX_LOCALE_SIZE;
        WCHAR buffer[MI_MAX_LOCALE_SIZE];
        if (GetThreadPreferredUILanguages(0, &numLangs, buffer, &lenBuffer))
        {
            const MI_Char * strLocale = NULL;
            MI_Result r = MI_DestinationOptions_GetUILocale(&options, &strLocale);
            NitsCompare(r, MI_RESULT_OK, PAL_T("MI_DestinationOptions_GetUILocale should success"));
            if (r == MI_RESULT_OK)
            {
                NitsCompareString(strLocale, buffer, PAL_T("MI_DestinationOptions_GetUILocale should success"));
            }
            r = MI_DestinationOptions_GetDataLocale(&options, &strLocale);
            NitsCompare(r, MI_RESULT_OK, PAL_T("MI_DestinationOptions_GetDataLocale should success"));
            if (r == MI_RESULT_OK)
            {
                NitsCompareString(strLocale, buffer, PAL_T("MI_DestinationOptions_GetDataLocale should success"));
            }
        }
        else
        {
            NitsCompare(1, 0, PAL_T("GetThreadPreferredUILanguages failed"));
        }
    }
#endif

    // Read number
    {
        MI_Uint32 int32Value = 0;
        const MI_Char * optionName = PAL_T("option2");
        NitsCompare(options.ft->GetNumber(&options, optionName, &int32Value, nullIndex, 0), MI_RESULT_OK, PAL_T("GetNumber should work"));
        NitsCompare(options.ft->GetNumber(&options, optionName, &int32Value, &index, &flag), MI_RESULT_OK, PAL_T("GetNumber should work"));
        NitsCompare(int32Value, 33, PAL_T("GetNumber should work"));
#if defined (_MSC_VER)
        if (!cloned) NitsCompare(index, 3, PAL_T("GetString should work"));
#else
        if (!cloned) NitsCompare(index, 1, PAL_T("GetString should work"));
#endif

        NitsCompare(options.ft->GetNumber(&options, PAL_T("option1"), &int32Value, nullIndex, 0), MI_RESULT_TYPE_MISMATCH, PAL_T("GetNumber return MI_RESULT_TYPE_MISMATCH"));
        NitsCompare(options.ft->GetNumber(&options, PAL_T("optionBla"), &int32Value, nullIndex, 0), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("GetNumber return MI_RESULT_NOT_FOUND"));
        NitsCompare(options.ft->GetNumber(nullOptions, optionName, &int32Value, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetNumber should fail"));
        NitsCompare(options.ft->GetNumber(&options, nullString, &int32Value, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetNumber should fail"));
        NitsCompare(options.ft->GetNumber(&options, optionName, nullNumberPtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetNumber should fail"));
    }

    // GetOptionCount
    {
        MI_Uint32 optionCount = 0;
        NitsCompare(options.ft->GetOptionCount(nullOptions, &optionCount), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionCount should fail"));
        NitsCompare(options.ft->GetOptionCount(&options, nullNumberPtr), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionCount should fail"));

        NitsCompare(options.ft->GetOptionCount(&options, &optionCount), MI_RESULT_OK, PAL_T("GetOptionCount should success"));

#if defined(_MSC_VER)
        NitsCompare(optionCount, 4, PAL_T("GetOptionCount should success"));
#else
        /* No locale items yet */
        NitsCompare(optionCount, 2, PAL_T("GetOptionCount should success"));
#endif
    }

    // GetOptionAt
    if (!cloned)
    {
        MI_Value value = {0};
        MI_Type type = MI_BOOLEAN;
        const MI_Char * optionName = NULL;
        NitsCompare(options.ft->GetOptionAt(nullOptions, 0, &optionName, &value, nullMITypePtr, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionAt should fail"));
        NitsCompare(options.ft->GetOptionAt(&options, 0, &optionName, &value, nullMITypePtr, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionAt should fail"));
        NitsCompare(options.ft->GetOptionAt(&options, 0, nullStringPtr, nullMIValuePtr, nullMITypePtr, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionAt should fail"));
        NitsCompare(options.ft->GetOptionAt(&options, 0, &optionName, &value, nullMITypePtr, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionAt should fail"));

        NitsCompare(options.ft->GetOptionAt(&options, 0x100, &optionName, &value, &type, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionAt should return MI_RESULT_NOT_FOUND"));

#if defined (_MSC_VER)
        NitsCompare(options.ft->GetOptionAt(&options, 2, &optionName, &value, &type, &flag), MI_RESULT_OK, PAL_T("GetOptionAt should success"));
#else
        NitsCompare(options.ft->GetOptionAt(&options, 0, &optionName, &value, &type, &flag), MI_RESULT_OK, PAL_T("GetOptionAt should success"));
#endif
        if (NitsCompare(type, MI_STRING, PAL_T("GetOptionAt should success")))
            NitsCompareString(value.string, PAL_T("value1"), PAL_T("GetOptionAt should success"));
    }

    // GetOption
    {
        MI_Value value = {0};
        MI_Type type = MI_BOOLEAN;
        const MI_Char * optionName = PAL_T("option1");
        NitsCompare(options.ft->GetOption(nullOptions, optionName, &value, nullMITypePtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOption should fail"));
        NitsCompare(options.ft->GetOption(&options, nullString, &value, nullMITypePtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOption should fail"));
        NitsCompare(options.ft->GetOption(&options, optionName, nullMIValuePtr, nullMITypePtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOption should fail"));
        NitsCompare(options.ft->GetOption(&options, optionName, &value, nullMITypePtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOption should fail"));
        NitsCompare(options.ft->GetOption(&options, PAL_T("optionbla"), &value, &type, &index, 0), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("GetOption should return MI_RESULT_NOT_FOUND"));

        NitsCompare(options.ft->GetOption(&options, optionName, &value, &type, &index, 0), MI_RESULT_OK, PAL_T("GetOption should success"));
        if (NitsCompare(type, MI_STRING, PAL_T("GetOption should success")))
            NitsCompareString(value.string, PAL_T("value1"), PAL_T("GetOption should success"));
#if defined(_MSC_VER)
        if (!cloned) NitsCompare(index, 2, PAL_T("GetOption should success"));
#else
        if (!cloned) NitsCompare(index, 0, PAL_T("GetOption should success"));
#endif
    }

    // GetCredentials
    {
        MI_Uint32 credentialCount = 0;
        NitsCompare(options.ft->GetCredentialsCount(&options, &credentialCount), MI_RESULT_OK, PAL_T("GetCredentialsCount should work"));
        NitsCompare(credentialCount, 1, PAL_T("GetCredentialsCount should work"));

        MI_UserCredentials credential = {0};
        const MI_Char *credentialOptionName = NULL;
        NitsCompare(options.ft->GetCredentialsAt(&options, 0, &credentialOptionName, &credential, &flag), MI_RESULT_OK, PAL_T("GetCredentialsAt should work"));
        NitsCompareString(credential.authenticationType, creds.authenticationType, PAL_T("GetCredentialsAt authenticationType should correct"));
        NitsCompareString(credential.credentials.usernamePassword.domain, creds.credentials.usernamePassword.domain, PAL_T("GetCredentialsAt domain should correct"));
        NitsCompareString(credential.credentials.usernamePassword.password, PAL_T("******"), PAL_T("GetCredentialsAt password should correct"));
        NitsCompareString(credential.credentials.usernamePassword.username, creds.credentials.usernamePassword.username, PAL_T("GetCredentialsAt username should correct"));
        NitsCompareString(credentialOptionName, PAL_T("option3"), PAL_T("GetCredentialsAt option name should correct"));

        MI_Uint32 passwordLength = 0;
        MI_Char password[9];
        MI_Result r = options.ft->GetCredentialsPasswordAt(&options, 0, &credentialOptionName, password, 9, &passwordLength, &flag);
        NitsCompare(r, MI_RESULT_OK, PAL_T("GetCredentialsPasswordAt should work"));
        if (r == MI_RESULT_OK)
        {
            NitsCompareString(credentialOptionName, PAL_T("option3"), PAL_T("GetCredentialsPasswordAt option name should correct"));

#ifdef _PREFAST_
    #pragma prefast(push)
    #pragma prefast(disable:26035) 
#endif
            NitsCompareString(password, creds.credentials.usernamePassword.password, PAL_T("GetCredentialsPasswordAt should work"));
#ifdef _PREFAST_
    #pragma prefast(pop)
#endif
            NitsCompare(passwordLength, 9, PAL_T("GetCredentialsPasswordAt should work"));
        }

        NitsCompare(options.ft->GetCredentialsPasswordAt(&options, 1, &credentialOptionName, password, 9, &passwordLength, 0), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("GetCredentialsPasswordAt should return MI_RESULT_NOT_FOUND"));
        NitsCompare(options.ft->GetCredentialsPasswordAt(nullOptions, 0, &credentialOptionName, password, 9, &passwordLength, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetCredentialsPasswordAt should return MI_RESULT_INVALID_PARAMETER"));
        NitsCompare(options.ft->GetCredentialsPasswordAt(&options, 0, nullStringPtr, password, 9, &passwordLength, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetCredentialsPasswordAt should return MI_RESULT_INVALID_PARAMETER"));
        NitsCompare(options.ft->GetCredentialsPasswordAt(&options, 0, &credentialOptionName, password, 9, nullNumberPtr, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetCredentialsPasswordAt should return MI_RESULT_INVALID_PARAMETER"));
        NitsCompare(options.ft->GetCredentialsPasswordAt(&options, 0, &credentialOptionName, password, 8, &passwordLength, 0), MI_RESULT_FAILED, PAL_T("GetCredentialsPasswordAt should return MI_RESULT_FAILED"));

        MI_UserCredentials *nullCredentials = NULL;
        NitsCompare(options.ft->GetCredentialsAt(&options, 1, &credentialOptionName, &credential, 0), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("GetCredentialsAt should return MI_RESULT_NOT_FOUND"));
        NitsCompare(options.ft->GetCredentialsAt(nullOptions, 0, &credentialOptionName, &credential, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetCredentialsAt should return MI_RESULT_INVALID_PARAMETER"));
        NitsCompare(options.ft->GetCredentialsAt(&options, 0, nullStringPtr, &credential, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetCredentialsAt should return MI_RESULT_INVALID_PARAMETER"));
        NitsCompare(options.ft->GetCredentialsAt(&options, 0, &credentialOptionName, nullCredentials, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetCredentialsAt should return MI_RESULT_INVALID_PARAMETER"));
    }
}

NitsTest1(MI_DestinationOptions_ReadOperations, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;

    MI_DestinationOptions options = MI_DESTINATIONOPTIONS_NULL;
        
#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
    NitsCompare(MI_Application_NewDestinationOptions(NULL, &options), MI_RESULT_INVALID_PARAMETER, PAL_T("NewDestinationOptions invalid parameter"));
    NitsCompare(MI_Application_NewDestinationOptions(application, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("NewDestinationOptions invalid parameter"));
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif

    if (NitsCompare(MI_Application_NewDestinationOptions(application, &options), MI_RESULT_OK, PAL_T("NewDestinationOptions should succeed")))
    {
        if (NitsAssert(options.ft != NULL, PAL_T("Should have options function table")))
        {
            NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));

            NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 33, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));

            MI_UserCredentials creds = { MI_AUTH_TYPE_BASIC, {{ PAL_T("domain"), PAL_T("username"), PAL_T("password") }}};
            NitsCompare(options.ft->AddCredentials(&options, PAL_T("option3"), &creds, 0), MI_RESULT_OK, PAL_T("AddCredentials should work"));

            MI_DestinationOptions_ReadOperations_Internal(options, creds);
        }
#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6011)
#endif
        options.ft->Delete(NULL);
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif
        MI_DestinationOptions_Delete(&options);
    }
}
NitsEndTest

NitsTest1(MI_DestinationOptions_CloneTest, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;

    MI_DestinationOptions options = MI_DESTINATIONOPTIONS_NULL;
        
#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6309)
#endif
    NitsCompare(MI_Application_NewDestinationOptions(NULL, &options), MI_RESULT_INVALID_PARAMETER, PAL_T("NewDestinationOptions invalid parameter"));
    NitsCompare(MI_Application_NewDestinationOptions(application, NULL), MI_RESULT_INVALID_PARAMETER, PAL_T("NewDestinationOptions invalid parameter"));
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif

    if (NitsCompare(MI_Application_NewDestinationOptions(application, &options), MI_RESULT_OK, PAL_T("NewDestinationOptions should succeed")))
    {
        if (NitsAssert(options.ft != NULL, PAL_T("Should have options function table")))
        {
            NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));

            NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 33, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));

            MI_UserCredentials creds = { MI_AUTH_TYPE_BASIC, {{PAL_T("domain"), PAL_T("username"), PAL_T("password") }}};
            NitsCompare(options.ft->AddCredentials(&options, PAL_T("option3"), &creds, 0), MI_RESULT_OK, PAL_T("AddCredentials should work"));

            MI_DestinationOptions clonedOptions = MI_DESTINATIONOPTIONS_NULL;
            if (NitsCompare(MI_DestinationOptions_Clone(&options, &clonedOptions), MI_RESULT_OK, PAL_T("MI_DestinationOptions_Clone returns OK")) &&
            NitsAssert(clonedOptions.ft != NULL, PAL_T("MI_DestinationOptions function table should not be NULL")))
            {
                MI_DestinationOptions_ReadOperations_Internal(clonedOptions, creds, true);
                MI_DestinationOptions_Delete(&clonedOptions);
            }
        }
#if defined (_MSC_VER)
#pragma prefast(push)
#pragma prefast(disable: 6011)
#endif
        options.ft->Delete(NULL);
#if defined (_MSC_VER)
#pragma prefast(pop)
#endif
        MI_DestinationOptions_Delete(&options);
    }
}
NitsEndTest

void MI_SubscriptionDeliveryOptions_ReadOperations_Internal(
    MI_SubscriptionDeliveryOptions& options,
    MI_UserCredentials& creds,
    bool cloned = false)
{
    MI_SubscriptionDeliveryOptions *nullOptions = NULL;
    const MI_Char *nullString = NULL;
    const MI_Char **nullStringPtr = NULL;
    MI_Uint32 *nullNumberPtr = 0;
    MI_Uint32 *nullIndex = 0;
    MI_Uint32 index = 0;
    MI_Value *nullMIValuePtr = NULL;
    MI_Type *nullMITypePtr = 0;
    MI_Uint32 flag = 0;

    // Read string
    {
        const MI_Char * stringValue = NULL;
        const MI_Char * optionName = PAL_T("option1");
        NitsCompare(options.ft->GetString(&options, optionName, &stringValue, nullIndex, 0), MI_RESULT_OK, PAL_T("GetString should work"));
        NitsCompare(options.ft->GetString(&options, optionName, &stringValue, &index, &flag), MI_RESULT_OK, PAL_T("GetString should work"));
        NitsCompareString(stringValue, PAL_T("value1"), PAL_T("GetString should work"));
        if (!cloned) NitsCompare(index, 0, PAL_T("GetString should work"));

        NitsCompare(options.ft->GetString(&options, PAL_T("option2"), &stringValue, nullIndex, 0), MI_RESULT_TYPE_MISMATCH, PAL_T("GetString should return MI_RESULT_TYPE_MISMATCH"));
        NitsCompare(options.ft->GetString(&options, PAL_T("optionbla"), &stringValue, nullIndex, 0), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("GetString should return MI_RESULT_NOT_FOUND"));
        NitsCompare(options.ft->GetString(nullOptions, optionName, &stringValue, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetString should fail"));
        NitsCompare(options.ft->GetString(&options, nullString, &stringValue, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetString should fail"));
        NitsCompare(options.ft->GetString(&options, optionName, nullStringPtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetString should fail"));
    }
    // Read number
    {
        MI_Uint32 int32Value = 0;
        const MI_Char * optionName = PAL_T("option2");
        NitsCompare(options.ft->GetNumber(&options, optionName, &int32Value, nullIndex, 0), MI_RESULT_OK, PAL_T("GetNumber should work"));
        NitsCompare(options.ft->GetNumber(&options, optionName, &int32Value, &index, &flag), MI_RESULT_OK, PAL_T("GetNumber should work"));
        NitsCompare(int32Value, 33, PAL_T("GetNumber should work"));
        if (!cloned) NitsCompare(index, 1, PAL_T("GetNumber should work"));

        NitsCompare(options.ft->GetNumber(&options, PAL_T("option1"), &int32Value, nullIndex, 0), MI_RESULT_TYPE_MISMATCH, PAL_T("GetNumber return MI_RESULT_TYPE_MISMATCH"));
        NitsCompare(options.ft->GetNumber(&options, PAL_T("optionBla"), &int32Value, nullIndex, 0), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("GetNumber return MI_RESULT_NOT_FOUND"));
        NitsCompare(options.ft->GetNumber(nullOptions, optionName, &int32Value, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetNumber should fail"));
        NitsCompare(options.ft->GetNumber(&options, nullString, &int32Value, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetNumber should fail"));
        NitsCompare(options.ft->GetNumber(&options, optionName, nullNumberPtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetNumber should fail"));
    }
    // Read datetime
    {
        MI_Datetime datetimeRead = {0};
        MI_Datetime * nullDatetimeRead = (MI_Datetime *)0;
        const MI_Char * optionName = PAL_T("option3");

        NitsCompare(options.ft->GetDateTime(&options, optionName, &datetimeRead, nullIndex, 0), MI_RESULT_OK, PAL_T("GetDateTime should work"));
        NitsCompare(options.ft->GetDateTime(&options, optionName, &datetimeRead, &index, &flag), MI_RESULT_OK, PAL_T("GetDateTime should work"));
        if (!cloned) NitsCompare(index, 2, PAL_T("GetDateTime should work"));
        NitsCompare(datetimeRead.isTimestamp, MI_TRUE, PAL_T("GetDateTime should work"));
        NitsCompare(datetimeRead.u.timestamp.day, 10, PAL_T("GetDateTime should work"));
        NitsCompare(datetimeRead.u.timestamp.hour, 11, PAL_T("GetDateTime should work"));
        NitsCompare(datetimeRead.u.timestamp.minute, 12, PAL_T("GetDateTime should work"));
        NitsCompare(datetimeRead.u.timestamp.second, 13, PAL_T("GetDateTime should work"));
        NitsCompare(datetimeRead.u.timestamp.microseconds, 14, PAL_T("GetDateTime should work"));

        NitsCompare(options.ft->GetDateTime(&options, PAL_T("option1"), &datetimeRead, nullIndex, 0), MI_RESULT_TYPE_MISMATCH, PAL_T("GetDateTime return MI_RESULT_TYPE_MISMATCH"));
        NitsCompare(options.ft->GetDateTime(&options, PAL_T("optionBla"), &datetimeRead, nullIndex, 0), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("GetDateTime return MI_RESULT_NOT_FOUND"));

        NitsCompare(options.ft->GetDateTime(nullOptions, optionName, &datetimeRead, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetDateTime should fail"));
        NitsCompare(options.ft->GetDateTime(&options, nullString, &datetimeRead, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetDateTime should fail"));
        NitsCompare(options.ft->GetDateTime(&options, optionName, nullDatetimeRead, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetDateTime should fail"));
    }
    // Read interval
    {
        MI_Interval intervalRead = {0};
        MI_Interval * nullIntervalRead = (MI_Interval *)0;
        const MI_Char * optionName = PAL_T("option4");
        NitsCompare(options.ft->GetInterval(&options, optionName, &intervalRead, nullIndex, 0), MI_RESULT_OK, PAL_T("GetInterval should work"));
        NitsCompare(options.ft->GetInterval(&options, optionName, &intervalRead, &index, &flag), MI_RESULT_OK, PAL_T("GetInterval should work"));
        if (!cloned) NitsCompare(index, 3, PAL_T("GetInterval should work"));
        NitsCompare(intervalRead.days, 8, PAL_T("GetInterval should work"));
        NitsCompare(intervalRead.hours, 9, PAL_T("GetInterval should work"));
        NitsCompare(intervalRead.minutes, 10, PAL_T("GetInterval should work"));
        NitsCompare(intervalRead.seconds, 11, PAL_T("GetInterval should work"));
        NitsCompare(intervalRead.microseconds, 12, PAL_T("GetInterval should work"));

        NitsCompare(options.ft->GetInterval(&options, PAL_T("option1"), &intervalRead, nullIndex, 0), MI_RESULT_TYPE_MISMATCH, PAL_T("GetInterval return MI_RESULT_TYPE_MISMATCH"));
        // Option3 is a datetime not interval
        NitsCompare(options.ft->GetInterval(&options, PAL_T("option3"), &intervalRead, nullIndex, 0), MI_RESULT_TYPE_MISMATCH, PAL_T("GetInterval return MI_RESULT_TYPE_MISMATCH"));
        NitsCompare(options.ft->GetInterval(&options, PAL_T("optionBla"), &intervalRead, nullIndex, 0), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("GetInterval return MI_RESULT_NOT_FOUND"));

        NitsCompare(options.ft->GetInterval(nullOptions, optionName, &intervalRead, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetInterval should fail"));
        NitsCompare(options.ft->GetInterval(&options, nullString, &intervalRead, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetInterval should fail"));
        NitsCompare(options.ft->GetInterval(&options, optionName, nullIntervalRead, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetInterval should fail"));
    }
    // GetOptionCount
    {
        MI_Uint32 optionCount = 0;
        NitsCompare(options.ft->GetOptionCount(nullOptions, &optionCount), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionCount should fail"));
        NitsCompare(options.ft->GetOptionCount(&options, nullNumberPtr), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionCount should fail"));

        NitsCompare(options.ft->GetOptionCount(&options, &optionCount), MI_RESULT_OK, PAL_T("GetOptionCount should success"));
        NitsCompare(optionCount, 4, PAL_T("GetOptionCount should success"));
    }
    // GetOptionAt
    if (!cloned)
    {
        MI_Value value = {0};
        MI_Type type = MI_BOOLEAN;
        const MI_Char * optionName = NULL;
        NitsCompare(options.ft->GetOptionAt(nullOptions, 0, &optionName, &value, nullMITypePtr, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionAt should fail"));
        NitsCompare(options.ft->GetOptionAt(&options, 0, &optionName, &value, nullMITypePtr, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionAt should fail"));
        NitsCompare(options.ft->GetOptionAt(&options, 0, nullStringPtr, nullMIValuePtr, nullMITypePtr, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionAt should fail"));
        NitsCompare(options.ft->GetOptionAt(&options, 0, &optionName, &value, nullMITypePtr, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionAt should fail"));

        NitsCompare(options.ft->GetOptionAt(&options, 0x100, &optionName, &value, &type, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOptionAt should return MI_RESULT_NOT_FOUND"));

        NitsCompare(options.ft->GetOptionAt(&options, 0, &optionName, &value, &type, &flag), MI_RESULT_OK, PAL_T("GetOptionAt should success"));
        if (NitsCompare(type, MI_STRING, PAL_T("GetOptionAt should success")))
            NitsCompareString(value.string, PAL_T("value1"), PAL_T("GetOptionAt should success"));
    }
    // GetOption
    {
        MI_Value value = {0};
        MI_Type type = MI_BOOLEAN;
        const MI_Char * optionName = PAL_T("option1");
        NitsCompare(options.ft->GetOption(nullOptions, optionName, &value, nullMITypePtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOption should fail"));
        NitsCompare(options.ft->GetOption(&options, nullString, &value, nullMITypePtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOption should fail"));
        NitsCompare(options.ft->GetOption(&options, optionName, nullMIValuePtr, nullMITypePtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOption should fail"));
        NitsCompare(options.ft->GetOption(&options, optionName, &value, nullMITypePtr, 0, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetOption should fail"));
        NitsCompare(options.ft->GetOption(&options, PAL_T("optionbla"), &value, &type, &index, 0), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("GetOption should return MI_RESULT_NOT_FOUND"));

        NitsCompare(options.ft->GetOption(&options, optionName, &value, &type, &index, &flag), MI_RESULT_OK, PAL_T("GetOption should success"));
        if (NitsCompare(type, MI_STRING, PAL_T("GetOption should success")))
            NitsCompareString(value.string, PAL_T("value1"), PAL_T("GetOption should success"));
        if (!cloned) NitsCompare(index, 0, PAL_T("GetOption should success"));
    }
    // GetCredentials
    {
        MI_Uint32 credentialCount = 0;
        NitsCompare(options.ft->GetCredentialsCount(&options, &credentialCount), MI_RESULT_OK, PAL_T("GetCredentialsCount should work"));
        NitsCompare(credentialCount, 1, PAL_T("GetCredentialsCount should work"));

        MI_UserCredentials credential = {0};
        const MI_Char *credentialOptionName = NULL;
        NitsCompare(options.ft->GetCredentialsAt(&options, 0, &credentialOptionName, &credential, &flag), MI_RESULT_OK, PAL_T("GetCredentialsAt should work"));
        NitsCompareString(credential.authenticationType, creds.authenticationType, PAL_T("GetCredentialsAt authenticationType should correct"));
        NitsCompareString(credential.credentials.usernamePassword.domain, creds.credentials.usernamePassword.domain, PAL_T("GetCredentialsAt domain should correct"));
        NitsCompareString(credential.credentials.usernamePassword.password, PAL_T("******"), PAL_T("GetCredentialsAt password should correct"));
        NitsCompareString(credential.credentials.usernamePassword.username, creds.credentials.usernamePassword.username, PAL_T("GetCredentialsAt username should correct"));
        NitsCompareString(credentialOptionName, PAL_T("option5"), PAL_T("GetCredentialsAt option name should correct"));

        MI_Uint32 passwordLength = 0;
        MI_Char password[9];
        MI_Result r = options.ft->GetCredentialsPasswordAt(&options, 0, &credentialOptionName, password, 9, &passwordLength, &flag);
        NitsCompare(r, MI_RESULT_OK, PAL_T("GetCredentialsPasswordAt should work"));
        if (r == MI_RESULT_OK)
        {
            NitsCompareString(credentialOptionName, PAL_T("option5"), PAL_T("GetCredentialsPasswordAt option name should correct"));

#ifdef _PREFAST_
    #pragma prefast(push)
    #pragma prefast(disable:26035) 
#endif
            NitsCompareString(password, creds.credentials.usernamePassword.password, PAL_T("GetCredentialsPasswordAt should work"));
#ifdef _PREFAST_
    #pragma prefast(pop)
#endif

            NitsCompare(passwordLength, 9, PAL_T("GetCredentialsPasswordAt should work"));
        }
        NitsCompare(options.ft->GetCredentialsPasswordAt(&options, 1, &credentialOptionName, password, 9, &passwordLength, 0), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("GetCredentialsPasswordAt should return MI_RESULT_NOT_FOUND"));
        NitsCompare(options.ft->GetCredentialsPasswordAt(nullOptions, 0, &credentialOptionName, password, 9, &passwordLength, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetCredentialsPasswordAt should return MI_RESULT_INVALID_PARAMETER"));
        NitsCompare(options.ft->GetCredentialsPasswordAt(&options, 0, nullStringPtr, password, 9, &passwordLength, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetCredentialsPasswordAt should return MI_RESULT_INVALID_PARAMETER"));
        NitsCompare(options.ft->GetCredentialsPasswordAt(&options, 0, &credentialOptionName, password, 9, nullNumberPtr, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetCredentialsPasswordAt should return MI_RESULT_INVALID_PARAMETER"));
        NitsCompare(options.ft->GetCredentialsPasswordAt(&options, 0, &credentialOptionName, password, 8, &passwordLength, 0), MI_RESULT_FAILED, PAL_T("GetCredentialsPasswordAt should return MI_RESULT_FAILED"));

        MI_UserCredentials *nullCredentials = NULL;
        NitsCompare(options.ft->GetCredentialsAt(&options, 1, &credentialOptionName, &credential, 0), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("GetCredentialsAt should return MI_RESULT_NOT_FOUND"));
        NitsCompare(options.ft->GetCredentialsAt(nullOptions, 0, &credentialOptionName, &credential, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetCredentialsAt should return MI_RESULT_INVALID_PARAMETER"));
        NitsCompare(options.ft->GetCredentialsAt(&options, 0, nullStringPtr, &credential, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetCredentialsAt should return MI_RESULT_INVALID_PARAMETER"));
        NitsCompare(options.ft->GetCredentialsAt(&options, 0, &credentialOptionName, nullCredentials, 0), MI_RESULT_INVALID_PARAMETER, PAL_T("GetCredentialsAt should return MI_RESULT_INVALID_PARAMETER"));
    }
}

NitsTest1(MI_SubscriptionDeliveryOptions_ReadOperations, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application= &testData->application;
    
    MI_SubscriptionDeliveryOptions options = MI_SUBSCRIPTIONDELIVERYOPTIONS_NULL;
    if (NitsCompare(MI_Application_NewSubscriptionDeliveryOptions(application, MI_SubscriptionDeliveryType_Push, &options), MI_RESULT_OK, PAL_T("NewSubscribeDeliveryOptions should succeed")))
    {
        NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
        NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 33, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
        MI_Datetime datetime = {0};
        {
            datetime.isTimestamp = true;
            datetime.u.timestamp.day = 10;
            datetime.u.timestamp.hour = 11;
            datetime.u.timestamp.minute = 12;
            datetime.u.timestamp.second = 13;
            datetime.u.timestamp.microseconds = 14;
            NitsCompare(options.ft->SetDateTime(&options, PAL_T("option3"), &datetime, 0), MI_RESULT_OK, PAL_T("SetDateTime should work"));
        }
        MI_Interval interval = {0};
        {
            interval.days = 8;
            interval.hours = 9;
            interval.minutes = 10;
            interval.seconds = 11;
            interval.microseconds = 12;
            NitsCompare(options.ft->SetInterval(&options, PAL_T("option4"), &interval, 0), MI_RESULT_OK, PAL_T("SetInterval should work"));
        }
        MI_UserCredentials creds = { 0 };
        {
            creds.authenticationType = MI_AUTH_TYPE_BASIC;
            creds.credentials.usernamePassword.username = PAL_T("username");
            creds.credentials.usernamePassword.domain = PAL_T("domain");
            creds.credentials.usernamePassword.password = PAL_T("password");
            NitsCompare(options.ft->AddCredentials(&options, PAL_T("option5"), &creds, 0), MI_RESULT_OK, PAL_T("AddCredentials should work"));
        }

        MI_SubscriptionDeliveryOptions_ReadOperations_Internal(options, creds);
        MI_SubscriptionDeliveryOptions_Delete(&options);
    }
}
NitsEndTest

NitsTest1(MI_SubscriptionDeliveryOptions_CloneTest, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;
    
    MI_SubscriptionDeliveryOptions options = MI_SUBSCRIPTIONDELIVERYOPTIONS_NULL;
    if (NitsCompare(MI_Application_NewSubscriptionDeliveryOptions(application, MI_SubscriptionDeliveryType_Push, &options), MI_RESULT_OK, PAL_T("NewSubscribeDeliveryOptions should succeed")))
    {
        NitsCompare(options.ft->SetString(&options, PAL_T("option1"), PAL_T("value1"), 0), MI_RESULT_OK, PAL_T("SetString should work"));
        NitsCompare(options.ft->SetNumber(&options, PAL_T("option2"), 33, 0), MI_RESULT_OK, PAL_T("SetNumber should work"));
        MI_Datetime datetime = {0};
        {
            datetime.isTimestamp = true;
            datetime.u.timestamp.day = 10;
            datetime.u.timestamp.hour = 11;
            datetime.u.timestamp.minute = 12;
            datetime.u.timestamp.second = 13;
            datetime.u.timestamp.microseconds = 14;
            NitsCompare(options.ft->SetDateTime(&options, PAL_T("option3"), &datetime, 0), MI_RESULT_OK, PAL_T("SetDateTime should work"));
        }
        MI_Interval interval = {0};
        {
            interval.days = 8;
            interval.hours = 9;
            interval.minutes = 10;
            interval.seconds = 11;
            interval.microseconds = 12;
            NitsCompare(options.ft->SetInterval(&options, PAL_T("option4"), &interval, 0), MI_RESULT_OK, PAL_T("SetInterval should work"));
        }
        MI_UserCredentials creds = { 0 };
        {
            creds.authenticationType = MI_AUTH_TYPE_BASIC;
            creds.credentials.usernamePassword.username = PAL_T("username");
            creds.credentials.usernamePassword.domain = PAL_T("domain");
            creds.credentials.usernamePassword.password = PAL_T("password");
            NitsCompare(options.ft->AddCredentials(&options, PAL_T("option5"), &creds, 0), MI_RESULT_OK, PAL_T("AddCredentials should work"));
        }
        MI_SubscriptionDeliveryOptions clonedOptions = MI_SUBSCRIPTIONDELIVERYOPTIONS_NULL;
        if (NitsCompare(MI_SubscriptionDeliveryOptions_Clone(&options, &clonedOptions), MI_RESULT_OK, PAL_T("MI_SubscriptionDeliveryOptions_Clone returns OK")) &&
            NitsAssert(clonedOptions.ft != NULL, PAL_T("MI_SubscriptionDeliveryOptions function table should not be NULL")))
        {
            NitsCompare((MI_Uint32)options.reserved1, (MI_Uint32)clonedOptions.reserved1, PAL_T("Cloned options should has same deliveryType"));
            MI_SubscriptionDeliveryOptions_ReadOperations_Internal(clonedOptions, creds, true);
            MI_SubscriptionDeliveryOptions_Delete(&clonedOptions);
        }
        MI_SubscriptionDeliveryOptions_Delete(&options);
    }
}
NitsEndTest

NitsTest1(MI_SubscriptionDeliveryOptions_StronglyTypedCheck, 
          SetupDefaultApplication, g_RuntimeApplicationSetup_Test1)
{
    RuntimeTestData *testData = NitsContext()->_SetupDefaultApplication->_BaseSetup->_RuntimeTestData;
    ResetRuntimeTestData(testData);
    MI_Application *application = &testData->application;

    MI_SubscriptionDeliveryOptions sdo = MI_SUBSCRIPTIONDELIVERYOPTIONS_NULL;

    if (NitsCompare(MI_Application_NewSubscriptionDeliveryOptions(application, MI_SubscriptionDeliveryType_Pull, &sdo), MI_RESULT_OK, PAL_T("Subscribe delivery options created")))
    {
        MI_Interval value = {0};
        value.days = 1;
        NitsCompare(MI_SubscriptionDeliveryOptions_GetDeliveryRetryInterval(&sdo, &value), MI_RESULT_NO_SUCH_PROPERTY, PAL_T("Get delivery retry interval should be not found"));
        NitsCompare(MI_SubscriptionDeliveryOptions_SetDeliveryRetryInterval(&sdo, &value), MI_RESULT_OK, PAL_T("Set delivery retry interval"));
        NitsCompare(MI_SubscriptionDeliveryOptions_GetDeliveryRetryInterval(&sdo, &value), MI_RESULT_OK, PAL_T("Get delivery retry interval should work"));
        NitsCompare(value.days, 1, PAL_T("validate get value same as set"));

        NitsCompare(MI_SubscriptionDeliveryOptions_Delete(&sdo), MI_RESULT_OK, PAL_T("subscribe delivery options delete failed"));
    }
}
NitsEndTest
#if 0
NitsTest(Session_GetInstance_Sync_OperationAck)
{
    MI_Application application = MI_APPLICATION_NULL;
    MI_Session session = MI_SESSION_NULL;
    MI_Operation operation = MI_OPERATION_NULL;

    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, &application), MI_RESULT_OK, PAL_T("MI_Application_Initialize returns OK")) &&
        NitsAssert(application.ft != NULL, PAL_T("MI_Application function table should not be NULL")))
    {
        MI_Instance *instance = NULL;
        if (NitsAssert(MI_Application_NewInstance(&application, PAL_T("Win32_OperatingSystem"), NULL, &instance) == MI_RESULT_OK, PAL_T("failed to create instance")))
        {
            if (NitsCompare(MI_Application_NewSession(&application, NULL, NULL, NULL, NULL, NULL, &session), MI_RESULT_OK, PAL_T("MI_Application_NewSession returns OK")) &&
                NitsAssert(session.ft != NULL, PAL_T("MI_Session function table should not be NULL")))
            {
                MI_Session_GetInstance(&session, MI_OPERATIONFLAGS_REPORT_OPERATION_STARTED, NULL, PAL_T("root\\cimv2"), instance, NULL, &operation);
                NitsAssert(operation.ft != NULL, PAL_T("operation function table null"));

                const MI_Instance *newInst = NULL;
                MI_Boolean moreResults = MI_TRUE;
                MI_Result miResult;
                MI_Operation_GetInstance(&operation, &newInst, &moreResults, &miResult, NULL, NULL);
                if (NitsCompare(moreResults, MI_TRUE, PAL_T("result ACK should mean more results available")))
                {
                    MI_Uint32 count = 0;
                    NitsAssert(newInst == NULL, PAL_T("First result should be NULL as it is an ACK"));
                    NitsCompare(miResult, MI_RESULT_OK, PAL_T("Should get success for ACK"));
                    while (moreResults)
                    {
                        MI_Operation_GetInstance(&operation, &newInst, &moreResults, &miResult, NULL, NULL);
                        if (NitsCompare(miResult, MI_RESULT_OK, PAL_T("operation should succeed")))
                            count++;
                    }
                    NitsCompare(count, 1, PAL_T("singleton so should be only 1 real response"));
                }
                MI_Operation_Close(&operation);

                MI_Session_Close(&session, NULL, NULL);
            }
            MI_Instance_Delete(instance);
        }

        MI_Application_Close(&application);
    }

}
NitsEndTest
#endif

/*
**==============================================================================
**
** Test structure for MIAPI end to end test
**
**==============================================================================
*/
struct MIAPITestStruct
{
    /* Configurations */
    const MI_Char* nameSpace; /* target namespace */
    const MI_Char* className;

    /* expected results */
    MI_Uint32 expectedInstanceCount;

    InstanceOperationStruct ios;
};

/*
**==============================================================================
**
** Setup function, it is called before running each test case
** NOTE: for "nits -fault" run, this function will be called once and only once
** for each test case.
**
**==============================================================================
*/
static void _setup(_In_ MIAPITestStruct* mts)
{
    MI_Application *application = &mts->ios.app;
    mts->ios.app.ft = NULL;
    if (NitsCompare(MI_Application_Initialize(0, NULL, NULL, application),
        MI_RESULT_OK,
        PAL_T("MI_Application_Initialize returns OK")))
    {
        NitsAssert(application->ft != NULL,
            PAL_T("MI_Application_Initialize returns object with function table"));
        if (application->ft == NULL)
            return;
    }
    else
        return;

    mts->ios.session.ft = NULL;
    if (NitsCompare(MI_Application_NewSession(&mts->ios.app, NULL, NULL, NULL, NULL, NULL, &mts->ios.session),
        MI_RESULT_OK,
        PAL_T("MI_Application_NewSession returns OK")))
    {
        NitsAssert(mts->ios.session.ft != NULL,
            PAL_T("MI_Application_NewSession returns object with function table"));
        if (mts->ios.session.ft == NULL)
            return;
    }
    else
        return;

    mts->ios.finished = 0;
}

NitsSetup0(MIAPITest_Setup, MIAPITestStruct)
    /*
     * MI_Application_Intialize create global log file handler _os
     * MI_Application_Close closes it,
     * thus the test case needs to make sure not close _os while
     * there are active MI_Application(s) objects
     */
    NitsAssert( StartServer_Assert() == MI_RESULT_OK, PAL_T(" Failed to start server "));
    _setup(NitsContext()->_MIAPITestStruct);
NitsEndSetup

/*
**==============================================================================
**
** Cleanup function, it is called after run each test case
** NOTE: for "nits -fault" run, this function will be called once and only once
** for each test case.
**
**==============================================================================
*/
static void _cleanup(_In_ MIAPITestStruct* mts)
{
    MI_Application *application = &mts->ios.app;
    MI_Session *session = &mts->ios.session;

    if (NULL != session->ft)
        NitsCompare(MI_Session_Close(session, NULL, NULL), MI_RESULT_OK, PAL_T("Failed to close MI_Session"));
    if (NULL != application->ft)
    NitsCompare(MI_Application_Close(application), MI_RESULT_OK, PAL_T("Failed to close MI_Application"));
}

NitsCleanup(MIAPITest_Setup)
    /*
     * MI_Application_Intialize create global log file handler _os
     * MI_Application_Close closes it,
     * thus the test case needs to make sure not close _os while
     * there are active MI_Application(s) objects
     */
    NitsAssert( StopServer_Assert() == MI_RESULT_OK, PAL_T("Failed to stop server"));
    _cleanup (NitsContext()->_MIAPITestStruct);
NitsEndCleanup

/*
**==============================================================================
**
** Default test structure
**
**==============================================================================
*/
static struct MIAPITestStruct MTS1 = {
    MI_T("test/cpp"),
    MI_T("X_SmallNumber"),
    0,
    {MI_FALSE, 0, 0}
};


/*
**==============================================================================
**
** Enumerate instance and validate results
**
**==============================================================================
*/
static MI_Boolean _Enumerate_Validate(_In_ MIAPITestStruct* mts)
{
    MI_Result miResult;

    /* Cleanup actual result */
    mts->ios.count = 0;

    miResult = EnumerateInstance(&mts->ios, mts->nameSpace, mts->className);
    NitsCompare(miResult, MI_RESULT_OK, PAL_T("Unexpected enumerate result"));

    /* Validate subscribe result */
    NitsCompare(mts->ios.count, mts->expectedInstanceCount, PAL_T("Unexpected instance count"));

    if (mts->ios.count == mts->expectedInstanceCount)
        return MI_TRUE;
    return MI_FALSE;
}


/*
**==============================================================================
**
** For following tests, each test case needs to run twice w.r.t.
** sync and async consume result instances
**
** To avoid the duplicate test code, following structure was introduced to
** indicate the way of deliver indication
**
**==============================================================================
*/
struct Sync_Struct
{
    MI_Boolean sync;
};

NitsSetup1(ConsumeInstance_Sync, Sync_Struct, MIAPITest_Setup, MTS1)
    NitsContext()->_Sync_Struct->sync = MI_TRUE;
NitsEndSetup

NitsSetup1(ConsumeInstance_Async, Sync_Struct, MIAPITest_Setup, MTS1)
    NitsContext()->_Sync_Struct->sync = MI_FALSE;
NitsEndSetup

NitsSplit2(ConsumeInstance_Approach, Sync_Struct, ConsumeInstance_Sync, ConsumeInstance_Async)
NitsEndSplit

typedef struct _ThreadStruct
{
    MIAPITestStruct mts;
    Sem sem;
    MI_Uint32* threadCount;
    Thread threadHandle;
}ThreadStruct;

NITS_EXTERN_C PAL_Uint32 THREAD_API EnumerateInstanceProc(void* param)
{
    ThreadStruct* ts = (ThreadStruct*)param;
    if ( MI_TRUE == _Enumerate_Validate(&ts->mts))
    {
        *ts->threadCount = (*ts->threadCount) + 1;
    }
    Sem_Post(&ts->sem, 1);
    return 0;
}

#if !defined(_MSC_VER)

NitsTest1(Test_SingleThread_Enumerate, ConsumeInstance_Approach, ConsumeInstance_ApproachDefaults)
{
    NitsDisableFaultSim;
    MIAPITestStruct* mts = NitsContext()->_ConsumeInstance_Approach->_ConsumeInstance_Sync->_MIAPITest_Setup->_MIAPITestStruct;
    MI_Boolean sync = NitsContext()->_ConsumeInstance_Approach->_Sync_Struct->sync;
    mts->ios.sync = sync;
    mts->ios.count = 0;
    mts->expectedInstanceCount = 1000;
    _Enumerate_Validate(mts);
}
NitsEndTest


NitsTest1(Test_MultiThreads_Enumerate, ConsumeInstance_Approach, ConsumeInstance_ApproachDefaults)
{
    NitsDisableFaultSim;
    MIAPITestStruct* mts = NitsContext()->_ConsumeInstance_Approach->_ConsumeInstance_Sync->_MIAPITest_Setup->_MIAPITestStruct;
    MI_Boolean sync = NitsContext()->_ConsumeInstance_Approach->_Sync_Struct->sync;
    mts->ios.sync = sync;
    mts->ios.count = 0;
    mts->expectedInstanceCount = 1000;

    static const MI_Uint32 sthreadCount = 8;
    ThreadStruct* tsarray[sthreadCount];
    MI_Uint32 successThreadCount = 0;
    for (MI_Uint32 i = 0; i < sthreadCount; i++)
    {
        ThreadStruct* ts = (ThreadStruct*)PAL_Malloc(sizeof(ThreadStruct));
        tsarray[i] = NULL;
        if (ts)
        {
            Sem_Init(&ts->sem, SEM_USER_ACCESS_ALLOW_ALL, 0);
            ts->mts = *mts;
            ts->threadCount = &successThreadCount;            
            int code = Thread_CreateJoinable(&ts->threadHandle, 
                                            EnumerateInstanceProc, 
                                            NULL, (void*)ts);
            NitsAssert( (code == 0), PAL_T("failed to create thread"));
            if (code == 0)
                tsarray[i] = ts;
            else
                PAL_Free(ts);
        }
        else
            NitsAssert(0, PAL_T("failed to create ThreadStruct"));
    }
    for (MI_Uint32 i = 0; i < sthreadCount; i++)
    {
        if (tsarray[i])
        {
            PAL_Uint32 result = 0;

            Sem_Wait(&tsarray[i]->sem);
            Sem_Destroy(&tsarray[i]->sem);

            Thread_Join(&tsarray[i]->threadHandle, &result);
            Thread_Destroy(&tsarray[i]->threadHandle);

            PAL_Free(tsarray[i]);
            tsarray[i] = NULL;
        }
    }
    NitsCompare(successThreadCount, sthreadCount, PAL_T("Some enumerate threads failed"));
}
NitsEndTest

#endif

