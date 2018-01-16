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
#include <miapi/Options.h>
#include <tests/util/indiprvdconfig.h>

using namespace std;

#define MAX_CLASS 10
#define TEST_MAX_PAGES 1024

/* in order to link to test_util.lib */
Batch* g_batch;
FILE* g_logfile;
char* g_dirpath;

/*
**==============================================================================
**
** Defines structure to hold each indication result
**
**==============================================================================
*/
typedef struct _IndicationResult IndicationResult;

struct _IndicationResult
{
    IndicationResult* next;
    MI_Instance *indication;
    MI_Char* machineid;
    MI_Char* bookmark;
};

/*
**==============================================================================
**
** Defines structure to hold expected results
**
**==============================================================================
*/
typedef struct _OperationResult
{
    /* common operation results */
    MI_Uint32 numInstances; /* how many instances received */
    MI_Result finalResult; /* final result of the operation */
    MI_Instance *errorDetails;
    MI_Char* errorString;

    /* Expected items */
    MI_Char* bookmark; /* bookmark of indication */

    /* Actual results from server */
    IndicationResult* head;/* list of indication result, inc. instance, bookmark, and machineid */
    IndicationResult* tail;
}OperationResult;

/*
**==============================================================================
**
** Test structure for Alert Indication end to end test
**
**==============================================================================
*/
struct AlertTestStruct
{
    /* Configurations */
    MI_Boolean sync; /* async / sync */
    const MI_Char* nameSpace; /* target namespace */
    const MI_Char* querylang;
    const MI_Char* queryexpr;
    MI_Uint32 operationTimeout; /* timeout value for the operation */
    MI_Uint32 targetclassCount;
    Config targetclassConfig[MAX_CLASS];  /* configuration of the target classes */
    const char** targetclassnames; /* list of target class names */

    /* memory allocator */
    Batch batch; /* Batch allocator for this test structure */

    /* MI objects */
    MI_Application app; /* application object */
    MI_Session session; /* test application */

    /* operation results */
    OperationResult actual;

    /* expected results */
    OperationResult expect;

    volatile ptrdiff_t finished; /* condication variable for terminating the operation */    
};

/*
**==============================================================================
**
** moudle level test setup
**
**==============================================================================
*/
NitsModuleSetup(IndicationE2ESetup)
    NitsTrace(PAL_T("IndicationE2ESetup started"));
    g_batch = Batch_New( 64 );
    NitsAssertOrReturn( g_batch != NULL, PAL_T("Failed to create batch") );
NitsEndModuleSetup

/*
**==============================================================================
**
** moudle level test cleanup
**
**==============================================================================
*/
NitsCleanup(IndicationE2ESetup)
    NitsTrace(PAL_T("IndicationE2ESetup cleaned"));
    if ( g_batch )
    {
        Batch_Delete( g_batch );
        g_batch = NULL;
    }

    NitsAssert(PAL_TRUE, PAL_T(""));
NitsEndCleanup

/*
**==============================================================================
**
** Setup function, it is called before running each test case
** NOTE: for "nits -fault" run, this function will be called once and only once
** for each test case.
**
**==============================================================================
*/
static void _setup(_In_ AlertTestStruct* ats)
{
    MI_Application *application = &ats->app;

    Batch_Init(&ats->batch, TEST_MAX_PAGES);
    ats->app.ft = NULL;
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

    ats->session.ft = NULL;
    if (NitsCompare(MI_Application_NewSession(&ats->app, NULL, NULL, NULL, NULL, NULL, &ats->session),
        MI_RESULT_OK,
        PAL_T("MI_Application_NewSession returns OK")))
    {
        NitsAssert(ats->session.ft != NULL,
            PAL_T("MI_Application_NewSession returns object with function table"));
        if (ats->session.ft == NULL)
            return;
    }
    else
        return;

    ats->finished = 0;
}

NitsSetup0(AlertTest_Setup, AlertTestStruct)
    _setup(NitsContext()->_AlertTestStruct);
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
static void _cleanup(_In_ AlertTestStruct* ats)
{
    MI_Application *application = &ats->app;
    MI_Session *session = &ats->session;

    if (NULL != session->ft)
        NitsCompare(MI_Session_Close(session, NULL, NULL), MI_RESULT_OK, PAL_T("Failed to close MI_Session"));
    if (NULL != application->ft)
    NitsCompare(MI_Application_Close(application), MI_RESULT_OK, PAL_T("Failed to close MI_Application"));

    Batch_Destroy(&ats->batch);
}

NitsCleanup(AlertTest_Setup)
    _cleanup (NitsContext()->_AlertTestStruct);   
NitsEndCleanup

/*
**==============================================================================
**
** Store indication result for validation purpose
**
**==============================================================================
*/
static void _CacheIndicationResult(
    _In_ AlertTestStruct* ats,
    _In_opt_ const MI_Instance* inst,
    _In_opt_z_ const MI_Char* bookmark,
    _In_opt_z_ const MI_Char* machineid,
    _In_ MI_Boolean moreResults,
    _In_ MI_Result result,
    _In_opt_z_ const MI_Char* errorString,
    _In_opt_ const MI_Instance* errorDetails)
{
    if (inst)
    {
        ats->actual.numInstances++;

        IndicationResult* ir = (IndicationResult*)Batch_GetClear(&ats->batch, sizeof(IndicationResult));
        NitsAssert(ir != NULL, PAL_T("Failed to create IndicationResult, out of memory"));
        if ( ir )
        {
            if (bookmark)
                ir->bookmark = Batch_Tcsdup(&ats->batch, bookmark);
            if (machineid)
                ir->machineid = Batch_Tcsdup(&ats->batch, machineid);
            MI_Result r = MI_Instance_Clone(inst, &ir->indication);
            NitsCompare(r, MI_RESULT_OK, PAL_T("Clone errorDetails failed"));
            ir->next = NULL;
            if (NULL == ats->actual.tail)
                ats->actual.head = ir;
            else
                ats->actual.tail->next = ir;
            ats->actual.tail = ir;
        }
    }

    if (moreResults == MI_FALSE)
    {
        if (result != MI_RESULT_OK)
        {
            if (errorString)
            {
                ats->actual.errorString = Batch_Tcsdup(&ats->batch, errorString);
                NitsAssert(ats->actual.errorString != NULL, PAL_T("out of memory"));
            }
            if (errorDetails)
            {
                MI_Result r = Instance_Clone(errorDetails, &ats->actual.errorDetails, &ats->batch);
                NitsCompare(r, MI_RESULT_OK, PAL_T("Clone errorDetails failed"));
            }
        }
        ats->actual.finalResult = result;
        ats->finished = 1;
    }
}

/*
**==============================================================================
**
** Consume indication result
**
**==============================================================================
*/
static MI_Result _ConsumeIndicationResults(
    _In_ AlertTestStruct* ats,
    _In_ MI_Operation *miOperation)
{
    MI_Result miResult;

    if (ats->sync == MI_TRUE)
    {
        MI_Boolean moreResults = MI_FALSE;
        do
        {
            const MI_Instance *miInstanceResult = NULL;
            MI_Result _miResult;
            const MI_Char *errorString = NULL;
            const MI_Instance *errorDetails = NULL;
            const MI_Char *bookmark;
            const MI_Char *machineid;

            _miResult = MI_Operation_GetIndication(miOperation, &miInstanceResult, &bookmark, &machineid, &moreResults, &miResult, &errorString, &errorDetails);
            if (_miResult != MI_RESULT_OK)
            {
                miResult = _miResult;
            }
            _CacheIndicationResult(ats, miInstanceResult, bookmark, machineid, moreResults, miResult, errorString, errorDetails);
            
        } while ((miResult == MI_RESULT_OK) && (moreResults == MI_TRUE));
    }
    else
    {
        ptrdiff_t finished;
        finished = ats->finished;
        while (!finished)
        {
            CondLock_Wait((ptrdiff_t)&ats->finished, &ats->finished, finished, CONDLOCK_DEFAULT_SPINCOUNT);
            finished = ats->finished;
        }
        miResult = ats->actual.finalResult;
    }
    return miResult;
}

/*
**==============================================================================
**
** Create operation options, such as time out
**
**==============================================================================
*/
static MI_Result _CreateOperationOptions(
    _In_ AlertTestStruct* ats,
    _Out_ MI_OperationOptions *options)
{
    MI_Application application;
    MI_Result miResult;
    MI_Interval timeoutInterval;
    MI_Uint64 currentTimeout = ats->operationTimeout * 1000;

    miResult = MI_Session_GetApplication(&ats->session, &application);
    if (miResult != MI_RESULT_OK)
        return miResult;

    miResult = MI_Application_NewOperationOptions(&application, MI_FALSE, options);
    if (miResult != MI_RESULT_OK)
        return miResult;

    memset((void*)&timeoutInterval, 0, sizeof(timeoutInterval));

    timeoutInterval.microseconds = currentTimeout%1000000;
    currentTimeout /= 1000000;

    timeoutInterval.seconds = currentTimeout % 60;
    currentTimeout /= 60;

    timeoutInterval.minutes = currentTimeout % 60;
    currentTimeout /= 60;

    timeoutInterval.hours = currentTimeout % 24;
    currentTimeout /= 24;

    timeoutInterval.days = (MI_Uint32) currentTimeout;

    miResult = MI_OperationOptions_SetTimeout(options, &timeoutInterval);
    if (miResult != MI_RESULT_OK)
    {
        goto cleanup;
    }

    return miResult;

cleanup:
    MI_OperationOptions_Delete(options);
    memset(options, 0, sizeof(*options));
    return miResult;
}

/*
**==============================================================================
**
** Async operation, the callback to receive indication results
**
**==============================================================================
*/
NITS_EXTERN_C void MI_CALL _IndicationResultCallback(
    _In_opt_     MI_Operation *operation,
    _In_     void *callbackContext,
    _In_opt_ const MI_Instance *instance,
    _In_opt_z_ const MI_Char *bookmark,
    _In_opt_z_ const MI_Char *machineID,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char *errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    AlertTestStruct* ats = (AlertTestStruct*)callbackContext;
    _CacheIndicationResult(ats, instance, bookmark, machineID, moreResults, resultCode, errorString, errorDetails);
    if (moreResults == MI_FALSE)
        CondLock_Broadcast((ptrdiff_t)&ats->finished);
}

/*
**==============================================================================
**
** Read modify result
**
**==============================================================================
*/
static MI_Result _ConsumeInstanceResults(_In_ MI_Operation *miOperation)
{
    MI_Result miResult;
    MI_Boolean moreResults = MI_FALSE;
    do
    {
        const MI_Instance *miInstanceResult = NULL;
        MI_Result _miResult;
        const MI_Char *errorString = NULL;
        const MI_Instance *errorDetails = NULL;

        _miResult = MI_Operation_GetInstance(
            miOperation,
            &miInstanceResult,
            &moreResults,
            &miResult,
            &errorString,
            &errorDetails);
        if (_miResult != MI_RESULT_OK)
        {
            miResult = _miResult;
        }
    } while ((miResult == MI_RESULT_OK) && (moreResults == MI_TRUE));

    return miResult;
}

/*
**==============================================================================
**
** Modify configuration instance for indication class
**
**==============================================================================
*/
static MI_Result _ModifyInstance(
    _In_ AlertTestStruct* ats,
    _In_ MI_Instance* instance)
{
    MI_Result miResult;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks *callbacks = NULL;

    MI_Session_ModifyInstance(&ats->session, 0, NULL, ats->nameSpace, instance, callbacks, &miOperation);

    miResult = _ConsumeInstanceResults(&miOperation);

    MI_Operation_Close(&miOperation);

    return miResult;
}

/*
**==============================================================================
**
** Modify configuration(s) of target class(es)
**
**==============================================================================
*/
static MI_Result _ConfigTargetClasses(
    _In_ AlertTestStruct* ats)
{
    MI_Instance *instance;
    MI_Uint32 i;
    for (i = 0; i < ats->targetclassCount; i++)
    {
        MI_Result r = Config_ToInstance(&ats->batch, (const Config*)&ats->targetclassConfig[i], &instance);
        NitsCompare(r, MI_RESULT_OK, PAL_T("Convert config to instance failed"));
        if (r != MI_RESULT_OK)
        {
            return r;
        }
        r = _ModifyInstance(ats, instance);
        MI_Instance_Delete(instance);
        NitsCompare(r, MI_RESULT_OK, PAL_T("Modify config instance failed"));
        if (r != MI_RESULT_OK)
        {
            return r;
        }
    }
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** Read configuration of target class
**
**==============================================================================

static MI_Result _ReadConfig(
    _In_ AlertTestStruct* ats,
    _In_z_ const MI_Char* classname,
    _Out_ Config* config)
{
    memset(config, 0, sizeof(Config));
    return MI_RESULT_OK;
}
*/

/* Sorts all the OperationResults received into HashMap buckets by class name. */
static void _BucketizeByClassName(
    StringHashMap* map,
    OperationResult* opResultList,
    MI_Uint32 expectedResultCount,
    MI_Boolean checkID )
{
    NitsAssert((opResultList->head != NULL) && (opResultList->tail != NULL), PAL_T("indication list is NULL"));
    
    MI_Uint32 expectedcount = 0;
    MI_Value v;
    MI_Result r = MI_RESULT_OK;
    IndicationResult* ir = opResultList->head;
    int rv;
    rv = StringHashMap_Init( map );
    NitsAssert( rv == 0, PAL_T("Initialize string hashmap failed") );
    if ( rv != 0 )
        return;
    opResultList->tail = opResultList->head = NULL;

    while ( ir != NULL )
    {
        expectedcount++;
        if (checkID)
        {
            r = MI_Instance_GetElement( ir->indication, MI_T("id"), &v, NULL, NULL, NULL );
            NitsCompare( r, MI_RESULT_OK, PAL_T("Unable to extract id") );
        }
        const MI_Char* classname = NULL;
        if ( r == MI_RESULT_OK )
        {
            r = MI_Instance_GetClassName( ir->indication, &classname );
            NitsCompare( r, MI_RESULT_OK, PAL_T("number of indication is not expected") );
        }

        if ( r == MI_RESULT_OK && classname )
        {
            StringBucket* b = StringHashMap_Find( map, classname );
            if ( NULL == b )
            {
                rv = StringHashMap_Insert( map, classname );
                NitsAssert( rv == 0, PAL_T("Failed to insert class to map") );
                if ( rv == 0 )
                {
                    b = StringHashMap_Find( map, classname );
                }
            }
            NitsAssert( b != NULL, PAL_T("Failed to find hash bucket for class") );
            if ( b )
            {
                b->count ++;
                //
                // Validate the id value is as expected
                //
                if (checkID)
                {
                    NitsCompare(v.uint32, b->count, PAL_T("Unexpected id property value of the indication"));
                }
            }
        }
        MI_Instance_Delete(ir->indication);
        ir->indication = NULL;
        ir = ir->next;
    }

    //
    // Validate total indication count is correct
    //
    NitsCompare(expectedcount, expectedResultCount, PAL_T("number of indication is not expected"));
}

/* Non-destructively iterates through the posted indications and attempts to match
 * posted bookmarks against their expected values. */
void _VerifyBookmarks(
    _In_ AlertTestStruct* ats )
{
    OperationResult* actual = &ats->actual;

    if (0 == actual->numInstances)
        return;

    MI_Boolean bookmarksPresent = MI_FALSE;

    for ( MI_Uint32 i = 0; i < ats->targetclassCount; i ++ )
    {
        if (NULL != ats->targetclassConfig[i].subscribeBookmark)
        {
            bookmarksPresent = MI_TRUE;
            break;
        }
    }

    // There are no bookmarks specified in the configs, so there is nothing to check against.
    if ( ! bookmarksPresent)
        return;

    // Iterate through the list of indication results and compare bookmarks against
    // expected values.
    IndicationResult* ir = actual->head;
    while (NULL != ir)
    {
        if (ir->bookmark)
        {
            const MI_Char* classname = NULL;
            MI_Result r = MI_RESULT_OK;
            MI_Boolean matchFound = MI_FALSE;
            r = MI_Instance_GetClassName( ir->indication, &classname );
            NitsCompare( r, MI_RESULT_OK, PAL_T("Unable to access classname") );

            for ( MI_Uint32 i = 0; i < ats->targetclassCount; i ++ )
            {
                if (NULL != ats->targetclassConfig[i].subscribeBookmark)
                {
                    MI_Char* bm = ansiToMI( ats->targetclassConfig[i].subscribeBookmark );
                    if (0 == Tcscmp(ir->bookmark, bm))
                    {
                        matchFound = MI_TRUE;
                        break;
                    }
                }
            }
            NitsAssert( MI_TRUE == matchFound, PAL_T("bookmark could not be matched against expected values") );
        }
        ir = ir->next;
    }
}

/*
**==============================================================================
**
** Validate subscribe result
**
**==============================================================================
*/
static void _ValidateSubscribeResult(
    _In_ AlertTestStruct* ats )
{
    OperationResult* actual = &ats->actual;
    OperationResult* expect = &ats->expect;
    NitsCompare(actual->finalResult, expect->finalResult, PAL_T("final result is not expected"));
    NitsCompare(actual->numInstances, expect->numInstances, PAL_T("number of indication is not expected"));

    /* Validate bookmarks if requested */
    _VerifyBookmarks( ats );

    /* Validate indication id property value */
    /* NOTE: All indication classes with in the test provider contains id property */
    /* the provider is located under $ROOT/samples/Providers/Test_Indication */
    if (actual->numInstances > 0)
    {
        StringHashMap map;
        
        _BucketizeByClassName( &map, actual, expect->numInstances, MI_TRUE );

        //
        // Validate each class's indication count
        //
        MI_Uint32 indicationCountPerClass = ats->expect.numInstances / ats->targetclassCount;
        for ( MI_Uint32 i = 0; i < ats->targetclassCount; i ++ )
        {
            MI_Char* cn = ansiToMI( ats->targetclassnames[i] );
            NitsAssert( cn != NULL, PAL_T("Failed to convert classname to MI_Char string") );
            StringBucket* b = StringHashMap_Find( &map, cn );
            NitsAssert( b != NULL, PAL_T("Failed to find hash bucket for class") );
            if ( b )
            {
                NitsCompare(indicationCountPerClass, b->count, PAL_T("Unexpected indication(s)' count"));
                StringHashMap_Remove( &map, cn );
            }
        }

        //
        // Validate no class was left
        //
        {
            size_t iter = 0;
            const StringBucket* b = StringHashMap_Top( &map, &iter );
            NitsAssert( b == NULL, PAL_T("Unexpect class left in the hashmap") );
        }
        StringHashMap_Destroy( &map );
    }
    /* TODO validate other results */
}

/*
**==============================================================================
**
** Config target class; Kick off subscribe request; Validate the result
**
**==============================================================================
*/
static void Config_Subscribe_Validate(_In_ AlertTestStruct* ats)
{
    MI_Result miResult;
    MI_OperationOptions miOperationOptions;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;
    const MI_Char *nameSpace;

    /* Cleanup actual result */
    memset((void*)&ats->actual, 0, sizeof(ats->actual));

    /* Configure target indciation class(es)' behavior */
    miResult = _ConfigTargetClasses(ats);
    if (miResult != MI_RESULT_OK)
    {
        NitsCompare(miResult, MI_RESULT_OK, PAL_T("Configure target class failed"));
        return;
    }

    /* Kick off subscribe request */
    if (ats->sync == MI_FALSE)
    {
        _callbacks.callbackContext = ats;
        _callbacks.indicationResult = _IndicationResultCallback;
        callbacks = &_callbacks;
        ats->finished = 0;
    }

    nameSpace = ats->nameSpace;

    miResult = _CreateOperationOptions(ats, &miOperationOptions);
    if (miResult != MI_RESULT_OK)
    {
        NitsCompare(miResult, MI_RESULT_OK, PAL_T("creat OperationOptions failed"));
        return;
    }

    MI_Session_Subscribe(&ats->session, 0, &miOperationOptions, nameSpace, ats->querylang, ats->queryexpr, NULL, callbacks, &miOperation);
    _ConsumeIndicationResults(ats, &miOperation);
    MI_Operation_Close(&miOperation);
    MI_OperationOptions_Delete(&miOperationOptions);

    /* Validate subscribe result */
    _ValidateSubscribeResult(ats);
}


/*
**==============================================================================
**
** Default test structure
**
**==============================================================================
*/
static struct AlertTestStruct ATS1 = {
    MI_FALSE,
    MI_T("root/cimv2"),
    MI_T("CQL"),
    MI_T("SELECT * FROM R_INDICATIONC3"),
    0,
    1,
};

/*
**==============================================================================
**
** For following tests, each test case needs to run twice w.r.t.
** delivering mechanism of the indication - one sync, another async;
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

NitsSetup1(IndicationDelivery_Sync, Sync_Struct, AlertTest_Setup, ATS1)
{
    NitsContext()->_Sync_Struct->sync = MI_TRUE;
}
NitsEndSetup

NitsSetup1(IndicationDelivery_Async, Sync_Struct, AlertTest_Setup, ATS1)
{
    NitsContext()->_Sync_Struct->sync = MI_FALSE;
}
NitsEndSetup

NitsSplit2(IndicationDelivery_Method, Sync_Struct, IndicationDelivery_Sync, IndicationDelivery_Async)
NitsEndSplit


/*
**==============================================================================
**
** Setup function, it is called before running each test case
** NOTE: for "nits -fault" run, this function will be called once and only once
** for each test case.
**
**==============================================================================
*/
NitsSetup0(AlertTest_StartServer_Setup, AlertTestStruct)
    /*
     * MI_Application_Intialize create global log file handler _os,
     * MI_Application_Close closes it,
     * thus the test case needs to make sure not closing _os while
     * there are active MI_Application(s) objects
     */
    NitsAssert( StartServer_Assert() == MI_RESULT_OK, PAL_T(" Failed to start server "));
    _setup(NitsContext()->_AlertTestStruct);
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
NitsCleanup(AlertTest_StartServer_Setup)
    /*
     * MI_Application_Intialize create global log file handler _os
     * MI_Application_Close closes it,
     * thus the test case needs to make sure not closing _os while
     * there are active MI_Application(s) objects
     */
    NitsAssert( StopServer_Assert() == MI_RESULT_OK, PAL_T(" Failed to stop server "));
    _cleanup (NitsContext()->_AlertTestStruct);
NitsEndCleanup

/*
**==============================================================================
**
** One alert indication class
**
**==============================================================================
*/
NitsTest1(Test_Alert_OneClass_Success, AlertTest_StartServer_Setup, ATS1)
{
    //
    // There are issues in product code (such as protocol.c:_ProtocolSocket_Aux_ConnectEvent)
    // does not handle out of memory (fault injection case), we cannot enable fault injection
    // until those issues are fixed
    //
    NitsDisableFaultSim;

    AlertTestStruct* ats = NitsContext()->_AlertTest_StartServer_Setup->_AlertTestStruct;
    ats->sync = MI_TRUE;
    const char* classname = "R_INDICATIONC3";
    ats->targetclassnames = &classname;
    MI_Uint32 indicationCount = 20;
    MI_Uint32 intervalMS = 1;

    SetConfig(&ats->targetclassConfig[0],
        (char*)classname, /* className */
        0, /* testGroup */
        intervalMS, /* intervalMS */
        indicationCount, /* failAfterCount */
        MI_RESULT_FAILED, /* failResult */
        0, /* initBehavior */
        MI_RESULT_OK, /* initResultCode */
        0, /* initTimeoutMS */
        0, /* finalizeBehavior */
        MI_RESULT_OK, /* finalizeResultCode */
        0, /* postBehavior */
        0, /* miscTestSubGroup */
        "TestSubscribeBookmark", /* subscribeBookmark */
        NULL, /* providerBookmark */
        NULL, /* dialect */
        NULL, /* expression */
        0, /* evalResult */
        0, /* logLoadUnloadCall */
        0, /* currentSubscriptionTypes */
        0 /* MI_Uint32 supportedSubscriptionTypes */);

    //
    // Final result aggregated by mgrstand.c:SubscribeElem
    // if all indication class (provider) post OK during unsubscribe call,
    // then final result is MI_RESULT_OK;
    // current Test_Indication class do post MI_RESULT_OK during unsubscribe
    //  call, thus the expected result is OK
    //
    memset((void*)&ats->expect, 0, sizeof(OperationResult));
    ats->expect.finalResult = MI_RESULT_OK;
    ats->expect.numInstances = indicationCount;
    Config_Subscribe_Validate(ats);
}
NitsEndTest

/*
**==============================================================================
**
** Complex alert indication class
**
**==============================================================================
*/
static struct AlertTestStruct ATS2 = {
    MI_FALSE,
    MI_T("root/cimv2"),
    MI_T("CQL"),
    MI_T("SELECT * FROM Test_INDICATION"),
    0,
    1,
};

NitsTest1(Test_Alert_ComplexClass_Success, AlertTest_StartServer_Setup, ATS2)
{
    //
    // There are issues in product code (such as protocol.c:_ProtocolSocket_Aux_ConnectEvent)
    // does not handle out of memory (fault injection case), we cannot enable fault injection
    // until those issues are fixed
    //
    NitsDisableFaultSim;

    AlertTestStruct* ats = NitsContext()->_AlertTest_StartServer_Setup->_AlertTestStruct;
    ats->sync = MI_TRUE;
    const char* classname = "Test_INDICATION";
    ats->targetclassnames = &classname;
    MI_Uint32 indicationCount = 10;
    MI_Uint32 intervalMS = 0;

    SetConfig(&ats->targetclassConfig[0],
        (char*)classname, /* className */
        0, /* testGroup */
        intervalMS, /* intervalMS */
        indicationCount, /* failAfterCount */
        MI_RESULT_FAILED, /* failResult */
        0, /* initBehavior */
        MI_RESULT_OK, /* initResultCode */
        0, /* initTimeoutMS */
        0, /* finalizeBehavior */
        MI_RESULT_OK, /* finalizeResultCode */
        0, /* postBehavior */
        0, /* miscTestSubGroup */
        NULL, /* subscribeBookmark */
        NULL, /* providerBookmark */
        NULL, /* dialect */
        NULL, /* expression */
        0, /* evalResult */
        0, /* logLoadUnloadCall */
        0, /* currentSubscriptionTypes */
        0 /* MI_Uint32 supportedSubscriptionTypes */);

    //
    // Final result aggregated by mgrstand.c:SubscribeElem
    // if all indication class (provider) post OK during unsubscribe call,
    // then final result is MI_RESULT_OK;
    // current Test_Indication class do post MI_RESULT_OK during unsubscribe
    //  call, thus the expected result is OK
    //
    memset((void*)&ats->expect, 0, sizeof(OperationResult));
    ats->expect.finalResult = MI_RESULT_OK;
    ats->expect.numInstances = 10;
    Config_Subscribe_Validate(ats);
}
NitsEndTest

/*
**==============================================================================
**
** Multiple class success
**
**==============================================================================
*/
NitsTest1(Test_Alert_PolymorphismClasses_Success, AlertTest_StartServer_Setup, ATS1)
{
    //
    // There are issues in product code (such as protocol.c:_ProtocolSocket_Aux_ConnectEvent)
    // does not handle out of memory (fault injection case), we cannot enable fault injection
    // until those issues are fixed
    //
    NitsDisableFaultSim;

    AlertTestStruct* ats = NitsContext()->_AlertTest_StartServer_Setup->_AlertTestStruct;
    MI_Uint32 failAfterCount = 5;
    MI_Uint32 intervalMS = 1;
    MI_Uint32 classCount = g_classcount_All;
    ats->targetclassnames = g_AlertIndicationClassNames_All;
    ats->targetclassCount = classCount;
    ats->querylang = MI_T("WQL");
    ats->queryexpr = MI_T("SELECT * FROM L_INDICATION");
    ats->sync = MI_FALSE;

    SetConfigs(classCount,
        (Config*)ats->targetclassConfig,
        ats->targetclassnames, /* className */
        0, /* testGroup */
        intervalMS, /* intervalMS */
        failAfterCount, /* failAfterCount */
        MI_RESULT_FAILED, /* failResult */
        0, /* initBehavior */
        MI_RESULT_OK, /* initResultCode */
        0, /* initTimeoutMS */
        0, /* finalizeBehavior */
        MI_RESULT_OK, /* finalizeResultCode */
        0, /* postBehavior */
        0, /* miscTestSubGroup */
        NULL, /* subscribeBookmark */
        NULL, /* providerBookmark */
        NULL, /* dialect */
        NULL, /* expression */
        0, /* evalResult */
        0, /* logLoadUnloadCall */
        0, /* currentSubscriptionTypes */
        0 /* MI_Uint32 supportedSubscriptionTypes */);

    //
    // Final result aggregated by mgrstand.c:SubscribeElem
    // if all indication class (provider) post OK during unsubscribe call,
    // then final result is MI_RESULT_OK;
    // current Test_Indication class do post MI_RESULT_OK during unsubscribe
    //  call, thus the expected result is OK
    //
    memset((void*)&ats->expect, 0, sizeof(OperationResult));
    ats->expect.finalResult = MI_RESULT_OK;
    ats->expect.numInstances = failAfterCount * classCount;

    Config_Subscribe_Validate(ats);
}
NitsEndTest

/* Synchronously invoke ThreadControl on the Lifecycle class to trigger
 * background posting of indications. */
void _Lifecycle_InvokeThreadControl(
    _In_ AlertTestStruct* ats,
    _In_ const MI_Char* className,
    _In_ const MI_Char* key,
    _In_ MI_Uint32 operation )
{
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_Result miResult = MI_RESULT_OK;
    MI_Instance* lifecycleInstance = NULL;
    MI_Instance* params = NULL;
    MI_Value value;

    /* Initialize instance to invoke method upon */
    {
        miResult = MI_Application_NewInstance( 
            &ats->app,
            className,
            NULL,
            &lifecycleInstance );
        NitsCompare( miResult, MI_RESULT_OK, PAL_T("Failed to create lifecycle instance for invoke") );
        if (MI_RESULT_OK != miResult)
            goto Life_InvokeThreadControl_DONE;

        value.string = (MI_Char*)key;
        miResult = MI_Instance_AddElement( lifecycleInstance, MI_T("key"), &value, MI_STRING, MI_FLAG_KEY );
        NitsCompare( miResult, MI_RESULT_OK, PAL_T("Failed to add operation to lifecycle instance") );
        if (MI_RESULT_OK != miResult)
            goto Life_InvokeThreadControl_DONE;
    }

    /* Initialize parameters to invoke method upon */
    {
        miResult = MI_Application_NewParameterSet( &ats->app, NULL, &params);
        NitsCompare( miResult, MI_RESULT_OK, PAL_T("Unable to allocate param set") );
        if (MI_RESULT_OK != miResult)
            goto Life_InvokeThreadControl_DONE;

        value.uint32 = operation;
        miResult = MI_Instance_AddElement( params, MI_T("operation"), &value, MI_UINT32, 0 );
        NitsCompare( miResult, MI_RESULT_OK, PAL_T("Failed to add operation to lifecycle instance") );
        if (MI_RESULT_OK != miResult)
            goto Life_InvokeThreadControl_DONE;
    }

    MI_Session_Invoke(
        &ats->session,
        0,
        NULL,
        ats->nameSpace,
        className,
        MI_T("ThreadControl"),
        lifecycleInstance,
        params,
        NULL,
        &miOperation );

    miResult = _ConsumeInstanceResults( &miOperation );
    NitsCompare( MI_RESULT_OK, miResult, PAL_T("Error while getting results from InvokeThreadControl") );
    MI_Operation_Close(&miOperation);

Life_InvokeThreadControl_DONE:
    if (lifecycleInstance)
        MI_Instance_Delete( lifecycleInstance );

    if (params)
        MI_Instance_Delete( params );
}

/*
**==============================================================================
**
** Validate subscribe result for lifecycle indications
**
**==============================================================================
*/
static void _ValidateLifecycleResult(
    _In_ AlertTestStruct* ats )
{
    OperationResult* actual = &ats->actual;
    OperationResult* expect = &ats->expect;
    NitsCompare(actual->finalResult, expect->finalResult, PAL_T("final result is not expected"));
    NitsCompare(actual->numInstances, expect->numInstances, PAL_T("number of indication is not expected"));

    /* Validate indication id property value */
    /* NOTE: All indication classes with in the test provider contains id property */
    /* the provider is located under $ROOT/samples/Providers/Test_Indication */
    if (actual->numInstances > 0)
    {
        StringHashMap map;
        
        _BucketizeByClassName( &map, actual, expect->numInstances, MI_FALSE );

        //
        // Validate each class's indication count
        //
        MI_Uint32 createCount = 0;
        for ( MI_Uint32 i = 0; i < ats->targetclassCount; i ++ )
        {
            if (ats->targetclassConfig[i].currentSubscriptionTypes & MI_LIFECYCLE_INDICATION_CREATE)
                createCount += (ats->targetclassCount * ats->targetclassConfig[i].failAfterCount);
            // TODO: Add other counts when needed
        }

        if (createCount > 0)
        {
            StringBucket* b = StringHashMap_Find( &map, MI_T("CIM_InstCreation") );
            NitsAssert( b != NULL, PAL_T("Failed to find hash bucket for CIM_InstCreation") );
            if ( b )
            {
                NitsCompare(createCount, b->count, PAL_T("Unexpected indication(s)' count"));
                StringHashMap_Remove( &map, MI_T("CIM_InstCreation") );
            }
        }

        //
        // Validate no class was left
        //
        {
            size_t iter = 0;
            const StringBucket* b = StringHashMap_Top( &map, &iter );
            NitsAssert( b == NULL, PAL_T("Unexpect class left in the hashmap") );
        }
        StringHashMap_Destroy( &map );
    }
    /* TODO validate other results */
}


/*
**==============================================================================
**
** Config target lifecycle class; Kick off subscribe request; Validate the result
**
**==============================================================================
*/
static void Lifecycle_Config_Subscribe_Validate(
    _In_ AlertTestStruct* ats,
    _In_ const MI_Char* classToFire )
{
    MI_Result miResult;
    MI_OperationOptions miOperationOptions;
    MI_Operation miOperation = MI_OPERATION_NULL;
    MI_OperationCallbacks _callbacks = MI_OPERATIONCALLBACKS_NULL;
    MI_OperationCallbacks *callbacks = NULL;
    const MI_Char *nameSpace;

    /* Cleanup actual result */
    memset((void*)&ats->actual, 0, sizeof(ats->actual));

    /* Configure target indciation class(es)' behavior */
    miResult = _ConfigTargetClasses(ats);
    if (miResult != MI_RESULT_OK)
    {
        NitsCompare(miResult, MI_RESULT_OK, PAL_T("Configure target class failed"));
        return;
    }

    /* Kick off subscribe request */
    if (ats->sync == MI_FALSE)
    {
        _callbacks.callbackContext = ats;
        _callbacks.indicationResult = _IndicationResultCallback;
        callbacks = &_callbacks;
        ats->finished = 0;
    }

    nameSpace = ats->nameSpace;

    miResult = _CreateOperationOptions(ats, &miOperationOptions);
    if (miResult != MI_RESULT_OK)
    {
        NitsCompare(miResult, MI_RESULT_OK, PAL_T("creat OperationOptions failed"));
        return;
    }

    MI_Session_Subscribe(&ats->session, 0, &miOperationOptions, nameSpace, ats->querylang, ats->queryexpr, NULL, callbacks, &miOperation);

    /* Invoke thread control to start the Lifecycle fire thread */
    _Lifecycle_InvokeThreadControl( ats, classToFire, classToFire, MI_LIFECYCLE_INDICATION_CREATE );
    
    _ConsumeIndicationResults(ats, &miOperation);
    MI_Operation_Close(&miOperation);
    MI_OperationOptions_Delete(&miOperationOptions);

    /* Validate subscribe result */
    _ValidateLifecycleResult(ats);
}


/*
**==============================================================================
**
** One lifecycle indication class
**
**==============================================================================
*/
static struct AlertTestStruct ATS_Lifecycle = {
    MI_FALSE,
    MI_T("root/cimv2"),
    MI_T("CQL"),
    MI_T("SELECT * FROM CIM_InstIndication WHERE SourceInstance ISA L_LifecycleC2"),  // Generic is Test_Class
    0,
    1,
};

NitsTest1(Test_Lifecycle_OneClass_Success, AlertTest_StartServer_Setup, ATS_Lifecycle)
{
    //
    // There are issues in product code (such as protocol.c:_ProtocolSocket_Aux_ConnectEvent)
    // does not handle out of memory (fault injection case), we cannot enable fault injection
    // until those issues are fixed
    //
    NitsDisableFaultSim;

    AlertTestStruct* ats = NitsContext()->_AlertTest_StartServer_Setup->_AlertTestStruct;
    ats->sync = MI_TRUE;
    const char* classname = "L_LifecycleC2";
    ats->targetclassnames = &classname;
    ats->targetclassCount = 1;
    MI_Uint32 indicationCount = 20;
    MI_Uint32 intervalMS = 1;

    SetConfig(&ats->targetclassConfig[0],
        (char*)classname, /* className */
        0, /* testGroup */
        intervalMS, /* intervalMS */
        indicationCount, /* failAfterCount */
        MI_RESULT_FAILED, /* failResult */
        0, /* initBehavior */
        MI_RESULT_OK, /* initResultCode */
        0, /* initTimeoutMS */
        0, /* finalizeBehavior */
        MI_RESULT_OK, /* finalizeResultCode */
        0, /* postBehavior */
        0, /* miscTestSubGroup */
        NULL, /* subscribeBookmark */
        NULL, /* providerBookmark */
        NULL, /* dialect */
        NULL, /* expression */
        0, /* evalResult */
        0, /* logLoadUnloadCall */
        MI_LIFECYCLE_INDICATION_CREATE, /* currentSubscriptionTypes */
        MI_LIFECYCLE_INDICATION_CREATE  /* MI_Uint32 supportedSubscriptionTypes */);

    //
    // Final result aggregated by mgrstand.c:SubscribeElem
    // if all indication class (provider) post OK during unsubscribe call,
    // then final result is MI_RESULT_OK;
    // current Test_Indication class do post MI_RESULT_OK during unsubscribe
    //  call, thus the expected result is OK
    //
    memset((void*)&ats->expect, 0, sizeof(OperationResult));
    ats->expect.finalResult = MI_RESULT_OK;
    ats->expect.numInstances = indicationCount;
    Lifecycle_Config_Subscribe_Validate(ats, MI_T("L_LifecycleC2"));
}
NitsEndTest

static struct AlertTestStruct ATS_Lifecycle_LeftClassC2 = {
    MI_FALSE,
    MI_T("root/cimv2"),
    MI_T("CQL"),
    MI_T("SELECT * FROM CIM_InstIndication WHERE SourceInstance ISA L_LifecycleC2"),
    0,
    1,
};

const char* g_LifecycleIndicationClassNames_Left[] =
{
    "L_IndicationC1",
    "L_IndicationC2"
};
MI_Uint32 g_LifecycleClassCount_Left = 2;

NitsTest1(Test_Lifecycle_Complex_Success, AlertTest_StartServer_Setup, ATS_Lifecycle_LeftClassC2)
{
    //
    // There are issues in product code (such as protocol.c:_ProtocolSocket_Aux_ConnectEvent)
    // does not handle out of memory (fault injection case), we cannot enable fault injection
    // until those issues are fixed
    //
    NitsDisableFaultSim;

    AlertTestStruct* ats = NitsContext()->_AlertTest_StartServer_Setup->_AlertTestStruct;
    ats->sync = MI_TRUE;
    MI_Uint32 classCount = g_LifecycleClassCount_Left;
    ats->targetclassnames = g_LifecycleIndicationClassNames_Left;
    ats->targetclassCount = classCount;
    MI_Uint32 failAfterCount = 5;
    MI_Uint32 intervalMS = 1;

    SetConfigs(classCount,
        (Config*)ats->targetclassConfig,
        ats->targetclassnames, /* className */
        0, /* testGroup */
        intervalMS, /* intervalMS */
        failAfterCount, /* failAfterCount */
        MI_RESULT_FAILED, /* failResult */
        0, /* initBehavior */
        MI_RESULT_OK, /* initResultCode */
        0, /* initTimeoutMS */
        0, /* finalizeBehavior */
        MI_RESULT_OK, /* finalizeResultCode */
        0, /* postBehavior */
        0, /* miscTestSubGroup */
        NULL, /* subscribeBookmark */
        NULL, /* providerBookmark */
        NULL, /* dialect */
        NULL, /* expression */
        0, /* evalResult */
        0, /* logLoadUnloadCall */
        MI_LIFECYCLE_INDICATION_CREATE, /* currentSubscriptionTypes */
        MI_LIFECYCLE_INDICATION_CREATE /* MI_Uint32 supportedSubscriptionTypes */);

    //
    // Final result aggregated by mgrstand.c:SubscribeElem
    // if all indication class (provider) post OK during unsubscribe call,
    // then final result is MI_RESULT_OK;
    // current Test_Indication class do post MI_RESULT_OK during unsubscribe
    //  call, thus the expected result is OK
    //
    memset((void*)&ats->expect, 0, sizeof(OperationResult));
    ats->expect.finalResult = MI_RESULT_OK;
    ats->expect.numInstances = failAfterCount * classCount * 2;
    
    Lifecycle_Config_Subscribe_Validate(ats, MI_T("L_LifecycleC2"));
}
NitsEndTest

