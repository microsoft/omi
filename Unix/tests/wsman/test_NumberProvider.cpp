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
#include "utils.h"
#include <protocol/protocol.h>
#include <sock/sock.h>
#include <base/base.h>
#include <base/paths.h>
#include <base/miextras.h>
#include <pal/format.h>
#include <base/log.h>
#include <omiclient/client.h>

#define STATIC
#define SELECT_RUN_TIMEOUT 500000  // 500 msecs
using namespace std;
//using namespace mi;

/* extern definitions - these functions are declared in test_wsman.cpp */
void WSMAN_Tests_With_Server();

#ifdef _PREFAST_                        // these tests are IPv4-specific, so disable OACR warnings
# pragma prefast (push)
# pragma prefast (disable: 24001)
# pragma prefast (disable: 24002)
#endif

static ProtocolSocketAndBase* s_protocol;
static int trace = 0;
static vector<MI_Result> s_results;
static vector<PostInstanceMsg*> s_instances;
static string  s_nsPrefix;

static MI_Uint64 _NextOperationId()
{
    static MI_Uint64 _operationId = 10000;
    return _operationId++;
}

STRAND_DEBUGNAME( NumberTestClient );

BEGIN_EXTERNC
static void _StrandTestPost( _In_ Strand* self, _In_ Message* msg ) 
{
    switch (msg->tag)
    {
        case NoOpRspTag:
        {
            if (trace)
            {
                NoOpRsp* rsp = (NoOpRsp*)msg;
                NoOpRsp_Print(rsp , stdout);
            }
            break;
        }
        case PostInstanceMsgTag:
        {
            PostInstanceMsg* rsp = (PostInstanceMsg*)msg;

            s_instances.push_back(rsp);
            Message_AddRef(&rsp->base);

            if (trace)
            {
                PostInstanceMsg_Print(rsp, stdout);
            }
            break;
        }
        case PostResultMsgTag:
        {
            {
                PostResultMsg* rsp = (PostResultMsg*)msg;

                s_results.push_back( rsp->result );
                if (trace)
                    PostResultMsg_Print(rsp, stdout);
            }
            break;
        }
        default:
        {
            Tprintf(ZT("unsupported msg: tag=%u\n"), msg->tag);
            break;
        }
    }

    Strand_Ack( self );
}

static void _StrandTestPostControl( _In_ Strand* self, _In_ Message* msg ) 
{
    // do nothing
}

static void _StrandTestAck( _In_ Strand* self) 
{
    // do nothing
}

static void _StrandTestFinished( _In_ Strand* self) 
{
    // do nothing
}

static StrandFT strandUserFT1 = { 
        _StrandTestPost, 
        _StrandTestPostControl, 
        _StrandTestAck, 
        NULL, 
        NULL, 
        _StrandTestFinished,
        NULL,
        NULL, 
        NULL, 
        NULL, 
        NULL, 
        NULL };
        
static Strand simpleResult;
END_EXTERNC

void SetupHelper()
{
    Sock_Start();
    Strand_Init( STRAND_DEBUG( NumberTestClient ) &simpleResult, &strandUserFT1, STRAND_FLAG_ENTERSTRAND, NULL );

    NitsCompare(StartServerAndConnect(true, &simpleResult, &s_protocol), 0, MI_T("omiserver failed to start"));
}

void CleanupHelper()
{
    StopServerAndDisconnect(&simpleResult, &s_protocol);
    Sock_Stop();
}

static void CleanupStaticState()
{
    s_results.clear();

    for ( unsigned int i = 0; i < s_instances.size(); i++ )
        PostInstanceMsg_Release(s_instances[i]);
    
    s_instances.clear();
}

static void TestNumberProviderSetup()
{
    s_nsPrefix = "";

    SetupHelper();

    s_instances.reserve( 11000 );

    CleanupStaticState();
}


static void TestNumberProviderCleanup()
{
    CleanupStaticState();
    CleanupHelper();
}


static void TestNumberProviderSetupOOPNamespace()
{    
    TestNumberProviderSetup();
    s_nsPrefix = "oop/requestor/";
}

NitsSetup(NumberProvTestSetup)
    TestNumberProviderSetup();
NitsEndSetup

NitsCleanup(NumberProvTestSetup)
    TestNumberProviderCleanup();
NitsEndCleanup

NitsSetup(NumberProvTestSetupOOPNamespace)
    TestNumberProviderSetupOOPNamespace();
NitsEndSetup

NitsCleanup(NumberProvTestSetupOOPNamespace)
    TestNumberProviderCleanup();
NitsEndCleanup

static const ZChar* MI_strchr(const ZChar* s, unsigned int c)
{
    while (s && *s)
    {
        if (c == (unsigned int)*s)
            return s;

        s++;
    }
    return 0;
}

/* parses part Key1=Value1[,Key2=value2...]*/
STATIC void _GetKeysFromCmd(
    MI_Instance* dynamicInstance,
    _In_z_ ZChar* whole_line)
{
    MI_String current_segment = whole_line;

    while (current_segment)
    {
        MI_String next_segment = (MI_String)MI_strchr(current_segment, ',');
        /* replace ',' with \0, remember next segment */
        if (next_segment)
        {
            *next_segment = 0;
            next_segment++;
        }

        {
            MI_String pos = (MI_String)MI_strchr(current_segment, '=');
            MI_String name = current_segment;
            MI_Value value;
            MI_Result r;

            // Split key and value.
            TEST_ASSERT(pos);

            *pos = 0;
            pos++;
            value.string = pos;

            // Set the property.
            r = MI_Instance_AddElement(dynamicInstance, name, &value, 
                MI_STRING, MI_FLAG_KEY|MI_FLAG_BORROW);

            TEST_ASSERT(r == MI_RESULT_OK);
        }

        current_segment = next_segment;
    }
}

/* converts string CLASSNAME.KEY1=VALUE1[,Key2=Value2...] to dynamic instance;
    returns CLASSNAME only if ".KEY.." part is missing */
static MI_Instance* _ReferenceStringToInstance(
    Batch* batch,
    const char* cmdArg,
    MI_ConstString* cnOut)
{
    MI_String cn, keys;
    MI_Result r;
    MI_Instance* dynamicInstance;

    /* extract class-name */
    cn = Batch_StrTcsdup(batch, cmdArg);
    keys = (MI_String)MI_strchr(cn, '.');

    if ( !keys )
    {
        /* cn - only - return */
        if (cnOut)
            *cnOut = cn;

        return 0;
    }

    *keys = 0;
    keys++;

    if (cnOut)
        *cnOut = cn;

    r = Instance_NewDynamic(&dynamicInstance, cn, MI_FLAG_CLASS, batch);

    if(!TEST_ASSERT(MI_RESULT_OK == r))
        return dynamicInstance;

    // Set keys from key-value pairs.
    _GetKeysFromCmd(dynamicInstance,keys);
    return  dynamicInstance;
}


STATIC MI_Result _CallGetInstance( const char* ns_, const char* ref )
{
    GetInstanceReq* msg;
    MI_Result r;
    MI_Instance* dynamicInstance;
    Batch batch = BATCH_INITIALIZER;
    string ns = s_nsPrefix + ns_;

    msg = GetInstanceReq_New(_NextOperationId(), BinaryProtocolFlag);

    if(!TEST_ASSERT(msg))
        return MI_RESULT_FAILED;

    msg->nameSpace = Batch_StrTcsdup(msg->base.base.batch, ns.c_str());

    /* create dynamic instance */
    dynamicInstance = _ReferenceStringToInstance(&batch, ref, 0);

    if(!TEST_ASSERT(dynamicInstance))
        return MI_RESULT_FAILED;

    if (trace)
        MI_Instance_Print(dynamicInstance, stdout, 0);

    /* pack instance */
    r = InstanceToBatch(dynamicInstance, NULL, NULL, msg->base.base.batch, 
            &msg->packedInstanceNamePtr, &msg->packedInstanceNameSize);

    if(!TEST_ASSERT(MI_RESULT_OK == r))
        return MI_RESULT_FAILED;

    Strand_SchedulePost( &simpleResult, &msg->base.base);

    GetInstanceReq_Release(msg);
    Batch_Destroy(&batch);

    // process send/recv loop
    // run loop with 1 ms increment until result received or 5 sec elapsed

    for ( int i = 0; i < 15000 && s_results.empty(); i++ )
        Protocol_Run( &s_protocol->internalProtocolBase, SELECT_RUN_TIMEOUT);

    return MI_RESULT_OK;
}

STATIC MI_Result _CallEnumerate( const char* ns_, const char* cn, MI_Boolean deep )
{
    EnumerateInstancesReq* msg;
    int i;
    string ns = s_nsPrefix + ns_;

    // Create new request.
    msg = EnumerateInstancesReq_New(_NextOperationId(), BinaryProtocolFlag);
    if(!TEST_ASSERT(msg))
        return MI_RESULT_FAILED;
    msg->nameSpace = Batch_StrTcsdup(msg->base.base.batch, ns.c_str());
    msg->className = Batch_StrTcsdup(msg->base.base.batch, cn);
    msg->deepInheritance = deep;

    Strand_SchedulePost( &simpleResult, &msg->base.base);

    EnumerateInstancesReq_Release(msg);

    // process send/recv loop
    // run loop with 1 ms increment until result received or 5 sec elapsed
    for ( i = 0; i < 20000 && s_results.empty(); i++ )
        Protocol_Run(&s_protocol->internalProtocolBase, SELECT_RUN_TIMEOUT);

    TEST_ASSERT( i < 20000 );

    return MI_RESULT_OK;
}

STATIC MI_Result _CallInvoke( 
    const char* ns_, 
    const char* ref, 
    const char* fn, 
    const char* char_params, 
    MI_Instance* outParam = 0 )
{
    InvokeReq* msg;
    MI_Result r;
    MI_Instance* dynamicInstance = 0;
    MI_Instance* dynamicInstanceParams = 0;
    Batch   dynamicBatch = BATCH_INITIALIZER;
    MI_ConstString cn;
    MI_String params_cn, params;
    string ns = s_nsPrefix + ns_;

    // Create new request.
    msg = InvokeReq_New(_NextOperationId(), BinaryProtocolFlag);
    if(!TEST_ASSERT(msg))
        return MI_RESULT_FAILED;
    // Extract arguments.
    msg->nameSpace = Batch_StrTcsdup(msg->base.base.batch, ns.c_str());

    if (!msg->nameSpace)
    {
        TEST_ASSERT((ptrdiff_t)"Out of memory" && (ptrdiff_t)NULL);
        return MI_RESULT_FAILED;
    }

    /* create dynamic instance */
    {
        dynamicInstance = _ReferenceStringToInstance( &dynamicBatch, ref, &cn );
        if(!TEST_ASSERT(cn != NULL))
            return MI_RESULT_FAILED;
        msg->className = Batch_Tcsdup(msg->base.base.batch, cn);

        if (trace && dynamicInstance)
            MI_Instance_Print(dynamicInstance, stdout, 0);

        /* pack instance */
        if (dynamicInstance)
        {
            r = InstanceToBatch(dynamicInstance, NULL, NULL, msg->base.base.batch, 
                    &msg->packedInstancePtr, &msg->packedInstanceSize);

            if(!TEST_ASSERT(MI_RESULT_OK == r))
                return MI_RESULT_FAILED;
        }
    }

    msg->function = Batch_StrTcsdup(msg->base.base.batch, fn);

    /* params */
    if (char_params)
    {
        /* parameters instance classname is ignored, but has to have valid syntax */
        params_cn = Batch_StrTcsdup(&dynamicBatch, "param");

        r = Instance_NewDynamic(
            &dynamicInstanceParams,
            params_cn,
            MI_FLAG_CLASS,
            &dynamicBatch);

        if(!TEST_ASSERT (MI_RESULT_OK == r))
            return MI_RESULT_FAILED;

        // Set keys from key-value pairs.
        params = Batch_StrTcsdup(&dynamicBatch, char_params);
        _GetKeysFromCmd(dynamicInstanceParams,params);

        if (trace)
            MI_Instance_Print(dynamicInstanceParams, stdout, 0);

        /* pack instance */
        r = InstanceToBatch(dynamicInstanceParams, NULL, NULL, msg->base.base.batch, 
                &msg->packedInstanceParamsPtr, &msg->packedInstanceParamsSize);
        if(!TEST_ASSERT (MI_RESULT_OK == r))
            return MI_RESULT_FAILED;
    }
    else if (outParam)
    {
        /* pack instance */
        r = InstanceToBatch(outParam, NULL, NULL, msg->base.base.batch, 
                &msg->packedInstanceParamsPtr, &msg->packedInstanceParamsSize);
        if(!TEST_ASSERT (MI_RESULT_OK == r))
            return MI_RESULT_FAILED;
    }

    Strand_SchedulePost( &simpleResult, &msg->base.base);

    InvokeReq_Release(msg);
    Batch_Destroy(&dynamicBatch);

    // process send/recv loop
    // run loop with 1 ms increment until result received or 5 sec elapsed
    for ( int i = 0; i < 15000 && s_results.empty(); i++ )
        Protocol_Run(&s_protocol->internalProtocolBase, SELECT_RUN_TIMEOUT);

    return MI_RESULT_OK;
}

STATIC MI_Result _CallAssociators( const char* ns_, const char* ref, const char* ac, const char* rc, const char* role, const char* rrole )
{
    AssociationsOfReq* msg;
    MI_Result r;
    MI_Instance* dynamicInstance = 0;
    Batch   dynamicBatch = BATCH_INITIALIZER;
    string ns = s_nsPrefix + ns_;

    // Create new request.
    msg = AssociationsOfReq_New(_NextOperationId(), BinaryProtocolFlag, AssociatorsOfReqTag);

    if(!TEST_ASSERT(msg))
        return MI_RESULT_FAILED;

    // Extract arguments.
    msg->nameSpace = Batch_StrTcsdup(msg->base.base.batch, ns.c_str());

    /* create dynamic instance */
    /* create dynamic instance */
    dynamicInstance = _ReferenceStringToInstance( &dynamicBatch, ref, 0 );

    if(!TEST_ASSERT(dynamicInstance))
        return MI_RESULT_FAILED;

    if (trace)
        MI_Instance_Print(dynamicInstance, stdout, 0);

    /* pack instance */
    r = InstanceToBatch(dynamicInstance, NULL, NULL, msg->base.base.batch, 
            &msg->packedInstancePtr, &msg->packedInstanceSize);

    if(!TEST_ASSERT(MI_RESULT_OK == r))
        return MI_RESULT_FAILED;

    // optional params
    if (ac)
        msg->assocClass = Batch_StrTcsdup(msg->base.base.batch, ac);

    if (rc)
        msg->resultClass = Batch_StrTcsdup(msg->base.base.batch, rc);

    if (role)
        msg->role = Batch_StrTcsdup(msg->base.base.batch, role);

    if (rrole)
        msg->resultRole = Batch_StrTcsdup(msg->base.base.batch, rrole);

    Strand_SchedulePost( &simpleResult, &msg->base.base);

    AssociationsOfReq_Release(msg);
    Batch_Destroy(&dynamicBatch);


    // process send/recv loop
    // run loop with 1 ms increment until result received or 5 sec elapsed
    for ( int i = 0; i < 15000 && s_results.empty(); i++ )
        Protocol_Run(&s_protocol->internalProtocolBase, SELECT_RUN_TIMEOUT);

    return MI_RESULT_OK;
}

STATIC MI_Result _CallReferences( const char* ns_, const char* ref, const char* ac, const char* role )
{
    AssociationsOfReq* msg;
    MI_Result r;
    MI_Instance* dynamicInstance = 0;
    Batch   dynamicBatch = BATCH_INITIALIZER;
    string ns = s_nsPrefix + ns_;

    // Create new request.
    msg = AssociationsOfReq_New(_NextOperationId(), BinaryProtocolFlag, ReferencesOfReqTag);

    if(!TEST_ASSERT(msg))
        return MI_RESULT_FAILED;

    // Extract arguments.
    msg->nameSpace = Batch_StrTcsdup(msg->base.base.batch, ns.c_str());

    /* create dynamic instance */
    /* create dynamic instance */
    dynamicInstance = _ReferenceStringToInstance( &dynamicBatch, ref, 0 );

    if(!TEST_ASSERT(dynamicInstance))
        return MI_RESULT_FAILED;

    if (trace)
        MI_Instance_Print(dynamicInstance, stdout, 0);

    /* pack instance */
    r = InstanceToBatch(dynamicInstance, NULL, NULL, msg->base.base.batch, 
            &msg->packedInstancePtr, &msg->packedInstanceSize);

    if(!TEST_ASSERT(MI_RESULT_OK == r))
        return MI_RESULT_FAILED;

    // optional params
    if (ac)
        msg->resultClass = Batch_StrTcsdup(msg->base.base.batch, ac);

    if (role)
        msg->role = Batch_StrTcsdup(msg->base.base.batch, role);

    Strand_SchedulePost( &simpleResult, &msg->base.base);

    AssociationsOfReq_Release(msg);
    Batch_Destroy(&dynamicBatch);


    // process send/recv loop
    // run loop with 1 ms increment until result received or 5 sec elapsed
    for ( int i = 0; i < 15000 && s_results.empty(); i++ )
        Protocol_Run(&s_protocol->internalProtocolBase, SELECT_RUN_TIMEOUT);
    
    return MI_RESULT_OK;
}

static void TestGetInstanceSmallNumberHelper()
{
    // omicli gi test/cpp X_SmallNumber.Number=1093
    //instance of X_SmallNumber
    //{
    //    Number=1093
    //    SpelledNumber=one thousand ninety three
    //}
    if(!TEST_ASSERT(MI_RESULT_OK == _CallGetInstance("test/cpp", "X_SmallNumber.Number=1093")))
        return;

    // validate response
    UT_ASSERT_EQUAL(s_results.size(), 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Number"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_UINT64);
    TEST_ASSERT(value.uint64 == 1093);
    TEST_ASSERT(!(flags & MI_FLAG_NULL));

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("SpelledNumber"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_STRING);
    TEST_ASSERT(value.string == ut::String(ZT("one thousand ninety three")));
    TEST_ASSERT(!(flags & MI_FLAG_NULL));
}

NitsTestWithSetup(TestGetInstanceSmallNumber, NumberProvTestSetup)
{
    NitsDisableFaultSim;
    TestGetInstanceSmallNumberHelper();
}
NitsEndTest

#if defined(CONFIG_POSIX)
NitsTestWithSetup(TestGetInstanceSmallNumber1, NumberProvTestSetupOOPNamespace)
{
    NitsDisableFaultSim;
    TestGetInstanceSmallNumberHelper();
}
NitsEndTest
#endif

NitsTestWithSetup(TestGetInstanceHugeNumberWithEmbeddedInstance, NumberProvTestSetup)
{
    //omicli gi test/cpp X_HugeNumber.Number=1000000
    //instance of test/cpp/X_HugeNumber
    //{
    //    Description=NULL
    //    Number=1000000
    //    Magnitude=6
    //    MagnitudeObj=instance of test/cpp/X_SmallNumber
    //    {
    //        Description=NULL
    //        Number=6
    //        SpelledNumber=six
    //    }
    //    Numbers123=[3]{
    //        instance of test/cpp/X_SmallNumber
    //        {
    //            Description=NULL
    //            Number=1
    //            SpelledNumber=one
    //        },
    //        instance of test/cpp/X_SmallNumber
    //        {
    //            Description=NULL
    //            Number=2
    //            SpelledNumber=two
    //        },
    //        instance of test/cpp/X_SmallNumber
    //        {
    //            Description=NULL
    //            Number=3
    //            SpelledNumber=three
    //        }
    //    }
    //    Number0=instance of X_Halves
    //    {
    //        number= REF instance of test/cpp/X_SmallNumber
    //        {
    //            Description=NULL
    //            Number=0
    //            SpelledNumber=zero
    //        }
    //        half= REF instance of test/cpp/X_SmallNumber
    //        {
    //            Description=NULL
    //            Number=0
    //            SpelledNumber=zero
    //        }
    //    }
    //    TwoTestObjects=[2]{
    //        instance of X_TestObject
    //        {
    //            id=17
    //            str=a string
    //        },
    //        instance of interop/X_Profile
    //        {
    //            InstanceID=a profile
    //            RegisteredName=embedded object
    //        }
    //    }
    //    TestObject=NULL
    //}
    
    // TODO: When this test is run with injecting the server process by specifying it binary in the target switch
    // there is an unexpected fault sim success when some server callsite is fault injected but client test code is already on its cleanup path 
    // Solution will be to restructure the test not to deal with any server communication in the cleanup path
    // Adding this as TODO for future and disabling fault sim on this
    NitsDisableFaultSim;

    if(!TEST_ASSERT(MI_RESULT_OK == _CallGetInstance("test/cpp", "X_HugeNumber.Number=1000000")))
        return;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Value value, value_instance;
    MI_Type type;
    MI_Uint32 flags = 0;

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Number"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_UINT64);
    TEST_ASSERT(value.uint64 == 1000000);
    TEST_ASSERT(!(flags & MI_FLAG_NULL));

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Magnitude"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_UINT32);
    TEST_ASSERT(value.uint32 == 6);
    TEST_ASSERT(!(flags & MI_FLAG_NULL));

    {   // embedded-instance: MagnitudeObj
        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("MagnitudeObj"), &value_instance, &type, &flags, 0));
        TEST_ASSERT(type == MI_INSTANCE);
        TEST_ASSERT(value_instance.instance != NULL);
        TEST_ASSERT(!(flags & MI_FLAG_NULL));

        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instance, ZT("Number"), &value, &type, &flags, 0));
        TEST_ASSERT(type == MI_UINT64);
        TEST_ASSERT(value.uint64 == 6);
        TEST_ASSERT(!(flags & MI_FLAG_NULL));

        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instance, ZT("SpelledNumber"), &value, &type, &flags, 0));
        TEST_ASSERT(type == MI_STRING);
        TEST_ASSERT(value.string == ut::String(ZT("six")));
        TEST_ASSERT(!(flags & MI_FLAG_NULL));
    }

    {   // embedded-instance[]: Numbers123
        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Numbers123"), &value_instance, &type, &flags, 0));
        TEST_ASSERT(type == MI_INSTANCEA);
        TEST_ASSERT(value_instance.instancea.size == 3);
        TEST_ASSERT(!(flags & MI_FLAG_NULL));

        for ( int num = 0; num < 3; num++ )
        {
            TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[num], ZT("Number"), &value, &type, &flags, 0));
            TEST_ASSERT(type == MI_UINT64);
            TEST_ASSERT(value.uint64 == (MI_Uint64)(1 + num));
            TEST_ASSERT(!(flags & MI_FLAG_NULL));
        }

        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[0], ZT("SpelledNumber"), &value, &type, &flags, 0));
        TEST_ASSERT(type == MI_STRING);
        TEST_ASSERT(value.string == ut::String(ZT("one")));
        TEST_ASSERT(!(flags & MI_FLAG_NULL));
    }

    {   // embedded-object Numbers0 - expecting X_Halves there
        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Number0"), &value_instance, &type, &flags, 0));
        TEST_ASSERT(type == MI_INSTANCE);
        TEST_ASSERT(value_instance.instance != NULL);
        TEST_ASSERT(!(flags & MI_FLAG_NULL));

        MI_ConstString cn = 0;
        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(value_instance.instance, &cn));
        TEST_ASSERT(cn == ut::String(ZT("X_Halves")));
        

        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instance, ZT("number"), &value, &type, &flags, 0));
        TEST_ASSERT(type == MI_REFERENCE);
        TEST_ASSERT(value.instance != NULL);
        TEST_ASSERT(!(flags & MI_FLAG_NULL));

        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instance, ZT("half"), &value, &type, &flags, 0));
        TEST_ASSERT(type == MI_REFERENCE);
        TEST_ASSERT(value.instance != NULL);
        TEST_ASSERT(!(flags & MI_FLAG_NULL));
    }

    {   // embedded-objects[]: TwoTestObjects
        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("TwoTestObjects"), &value_instance, &type, &flags, 0));
        TEST_ASSERT(type == MI_INSTANCEA);
        TEST_ASSERT(value_instance.instancea.size == 2);
        TEST_ASSERT(!(flags & MI_FLAG_NULL));

        for ( int num = 0; num < 2; num++ )
        {
            MI_ConstString cn = 0;
            TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(value_instance.instancea.data[num], &cn));

            if (cn == ut::String(ZT("X_TestObject")))
            {
                TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[num], ZT("id"), &value, &type, &flags, 0));
                TEST_ASSERT(type == MI_UINT64);
                TEST_ASSERT(value.uint64 == 17);
                TEST_ASSERT(!(flags & MI_FLAG_NULL));
            }
            else if (cn == ut::String(ZT("X_Profile")))
            {
                TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[num], ZT("Registeredname"), &value, &type, &flags, 0));
                TEST_ASSERT(type == MI_STRING);
                TEST_ASSERT(value.string == ut::String(ZT("embedded object")));
                TEST_ASSERT(!(flags & MI_FLAG_NULL));
            }
            else
            {
                UT_ASSERT_FAILED_MSG( (string("unexcpected class name ") + ut::StrToChar(cn)).c_str() );
            }
        }
    }

}
NitsEndTest

STATIC void _TestGetInstancePersonWithEmbeddedInstance(const char* ns)
{
    //omicli gi test/cpp TestEmbeddedOperations.Key=1
    //instance of TestEmbeddedOperations
    //{
    //    key=1
    //    person=instance of MSFT_Person
    //    {
    //        Key=7
    //        Species=NULL
    //        Last=Smith
    //        First=John
    //        ExpensiveProperty=NULL
    //    }
    //    threePersons=[3]{
    //        instance of MSFT_Person
    //        {
    //            Key=7
    //            Species=NULL
    //            Last=Black
    //            First=John
    //            ExpensiveProperty=NULL
    //        },
    //        instance of MSFT_Person
    //        {
    //            Key=8
    //            Species=NULL
    //            Last=White
    //            First=Bill
    //            ExpensiveProperty=NULL
    //        },
    //        instance of MSFT_Person
    //        {
    //            Key=8
    //            Species=NULL
    //            Last=Brown
    //            First=Ben
    //            ExpensiveProperty=NULL
    //        }
    //    }
    //}

    if(!TEST_ASSERT(MI_RESULT_OK == _CallGetInstance(ns, "TestEmbeddedOperations.Key=1")))
        return;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Value value, value_instance;
    MI_Type type;
    MI_Uint32 flags = 0;

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("key"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_UINT32);
    TEST_ASSERT(value.uint32 == 1);
    TEST_ASSERT(!(flags & MI_FLAG_NULL));

    {   // embedded-instance: person
        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("person"), &value_instance, &type, &flags, 0));
        TEST_ASSERT(type == MI_INSTANCE);
        TEST_ASSERT(value_instance.instance != NULL);
        TEST_ASSERT(!(flags & MI_FLAG_NULL));

        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instance, ZT("Last"), &value, &type, &flags, 0));
        TEST_ASSERT(type == MI_STRING);
        TEST_ASSERT(value.string == ut::String(ZT("Smith")));
        TEST_ASSERT(!(flags & MI_FLAG_NULL));

        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instance, ZT("First"), &value, &type, &flags, 0));
        TEST_ASSERT(type == MI_STRING);
        TEST_ASSERT(value.string == ut::String(ZT("John")));
        TEST_ASSERT(!(flags & MI_FLAG_NULL));
    }

    {   // embedded-instance[]: threePersons
        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("threePersons"), &value_instance, &type, &flags, 0));
        TEST_ASSERT(type == MI_INSTANCEA);
        TEST_ASSERT(value_instance.instancea.size == 3);
        TEST_ASSERT(!(flags & MI_FLAG_NULL));

        for ( int num = 0; num < 3; num++ )
        {
            TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[num], ZT("key"), &value, &type, &flags, 0));
            TEST_ASSERT(type == MI_UINT32);
            TEST_ASSERT(value.uint32 == (MI_Uint64)(7 + num));
            TEST_ASSERT(!(flags & MI_FLAG_NULL));
        }

        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[0], ZT("First"), &value, &type, &flags, 0));
        TEST_ASSERT(type == MI_STRING);
        TEST_ASSERT(value.string == ut::String(ZT("John")));
        TEST_ASSERT(!(flags & MI_FLAG_NULL));
        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[1], ZT("First"), &value, &type, &flags, 0));
        TEST_ASSERT(type == MI_STRING);
        TEST_ASSERT(value.string == ut::String(ZT("Bill")));
        TEST_ASSERT(!(flags & MI_FLAG_NULL));
        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[2], ZT("First"), &value, &type, &flags, 0));
        TEST_ASSERT(type == MI_STRING);
        TEST_ASSERT(value.string == ut::String(ZT("Ben")));
        TEST_ASSERT(!(flags & MI_FLAG_NULL));
    }
}

NitsTestWithSetup(TestGetInstancePersonWithEmbeddedInstance_c, NumberProvTestSetup)
{
    _TestGetInstancePersonWithEmbeddedInstance("test/c");
}
NitsEndTest

NitsTestWithSetup(TestGetInstancePersonWithEmbeddedInstance_cpp, NumberProvTestSetup)
{
    _TestGetInstancePersonWithEmbeddedInstance("test/cpp");
}
NitsEndTest

NitsTestWithSetup(TestGetInstanceSmallNumberNotFound, NumberProvTestSetup)
{
    //omicli gi test/cpp X_SmallNumber.Number=10001
    //PostResultMsg
    //{
    //    tag=4
    //    operationId=10000
    //    clientID=12128856
    //    result=7 [NOT_FOUND]
    //    request=NULL
    //}
    if(!TEST_ASSERT(MI_RESULT_OK == _CallGetInstance("test/cpp", "X_SmallNumber.Number=10001")))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_NOT_FOUND);

    TEST_ASSERT(s_instances.size() == 0);
}
NitsEndTest

NitsTestWithSetup(TestGetInstanceInvalidNameSpace, NumberProvTestSetup)
{
    //omicli gi non/exisiting/namespace X_SmallNumber.Number=11
    //PostResultMsg
    //{
    //    tag=4
    //    operationId=10000
    //    clientID=12128856
    //    result=7 [INVALID_NAMESPACE]
    //    request=NULL
    //}
    if(!TEST_ASSERT(MI_RESULT_OK == _CallGetInstance("non/exisiting/namespace", "X_SmallNumber.Number=11")))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_INVALID_NAMESPACE);

    TEST_ASSERT(s_instances.size() == 0);
}
NitsEndTest

NitsTestWithSetup(TestEnumerateHugeNumber, NumberProvTestSetup)
{
    //omicli ei test/cpp X_HugeNumber
    //instance of X_HugeNumber
    //{
    //    Number=1000000
    //    Magnitude=6
    //}
    //instance of X_HugeNumber
    //{
    //    Number=1000000000
    //    Magnitude=9
    //}

    if(!TEST_ASSERT(MI_RESULT_OK == _CallEnumerate("test/cpp", "X_HugeNumber", MI_FALSE)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == 2);
    if (s_instances.size() < 2) NitsReturn;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Number"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_UINT64);
    TEST_ASSERT(value.uint64 == 1000000 || value.uint64 == 1000000000);
    TEST_ASSERT(!(flags & MI_FLAG_NULL));

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Magnitude"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_UINT32);
    TEST_ASSERT(value.uint32 == 6 || value.uint32 == 9);
    TEST_ASSERT(!(flags & MI_FLAG_NULL));

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[1]->instance, ZT("Number"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_UINT64);
    TEST_ASSERT(value.uint64 == 1000000 || value.uint64 == 1000000000);
    TEST_ASSERT(!(flags & MI_FLAG_NULL));

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[1]->instance, ZT("Magnitude"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_UINT32);
    TEST_ASSERT(value.uint32 == 6 || value.uint32 == 9);
    TEST_ASSERT(!(flags & MI_FLAG_NULL));
}
NitsEndTest

NitsTestWithSetup(TestEnumerateX_Number1000001, NumberProvTestSetup)
{
    //omicli ei test/cpp X_Number1000001

    if(!TEST_ASSERT(MI_RESULT_OK == _CallEnumerate("test/cpp", "X_Number1000001", MI_FALSE)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT_EQUAL(s_instances.size(), 1);

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Number"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_UINT64);
    TEST_ASSERT(value.uint64 == 1000001);
    TEST_ASSERT(!(flags & MI_FLAG_NULL));

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Magnitude"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_UINT32);
    TEST_ASSERT(value.uint32 == 6);
    TEST_ASSERT(!(flags & MI_FLAG_NULL));

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Property0"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_UINT32);
    TEST_ASSERT(value.uint32 == 9);
    TEST_ASSERT(!(flags & MI_FLAG_NULL));
}
NitsEndTest

NitsTestWithSetup(TestEnumerateNumberShallow_NotFound, NumberProvTestSetup)
{
    //omicli ei test/cpp X_Number
    //PostResultMsg
    //{
    //    tag=4
    //    operationId=10000
    //    clientID=12194392
    //    result=7 [NOT_FOUND]
    //    request=NULL
    //}

    if(!TEST_ASSERT(MI_RESULT_OK == _CallEnumerate("test/cpp", "X_Number", MI_FALSE)))
        NitsReturn;

    // validate response
    UT_ASSERT_EQUAL(s_results.size(), 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_NOT_SUPPORTED);

    TEST_ASSERT(s_instances.size() == 0);
}
NitsEndTest

STATIC void TestEnumerateNumberDeepHelper()
{
    //omicli ei test/cpp X_Number -deep
    //instance of X_HugeNumber
    //{
    //    Number=1000000
    //    Magnitude=6
    //}
    //instance of X_HugeNumber
    //{
    //    Number=1000000000
    //    Magnitude=9
    //}
    //instance of X_SmallNumber
    //{
    //    Number=0
    //    SpelledNumber=zero
    //}
    //instance of X_SmallNumber
    //{
    //    Number=1
    //    SpelledNumber=one
    //}
    //....

    // NOTE!!!!!  provider has two modes of enumeration (one with threads other without)
    // they will alternate everytime the provider is called (static variable)!!!!
    if(!TEST_ASSERT(MI_RESULT_OK == _CallEnumerate("test/cpp", "X_Number", MI_TRUE)))
        return;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    // 2 Huge + 10000 small
    UT_ASSERT_EQUAL(s_instances.size(), 1003);
}

// note! provider has two modes of enumeration to exercise both
// sync and async APIs, so we have to call test twice

NitsTestWithSetup(TestEnumerateNumberDeep, NumberProvTestSetup)
{
    NitsDisableFaultSim;
    TestEnumerateNumberDeepHelper();
}
NitsEndTest

NitsTestWithSetup(TestEnumerateNumberDeep1, NumberProvTestSetup)
{
    NitsDisableFaultSim;
    TestEnumerateNumberDeepHelper();
}
NitsEndTest

NitsTestWithSetup(TestEnumerateHugeNumberConformsToProfile, NumberProvTestSetup)
{
    //omicli ei test/cpp X_HugeNumberConformsToProfile
    //instance of X_HugeNumberConformsToProfile
    //{
    //    Profile= REF     instance of interop/X_Profile
    //    {
    //        InstanceID=number
    //    }
    //    Element= REF     instance of test/cpp/X_HugeNumber
    //    {
    //        Number=1000000
    //    }
    //}
    //instance of X_HugeNumberConformsToProfile
    //{
    //    Profile= REF     instance of interop/X_Profile
    //    {
    //        InstanceID=number
    //    }
    //    Element= REF     instance of test/cpp/X_HugeNumber
    //    {
    //        Number=1000000000
    //    }
    //}

    // Verify that REF instances contin key properties only

    if(!TEST_ASSERT(MI_RESULT_OK == _CallEnumerate("test/cpp", "X_HugeNumberConformsToProfile", MI_TRUE)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == 2);
    if (s_instances.size() < 2) NitsReturn;

    MI_Value value, value_instance;
    MI_Type type;
    MI_Uint32 flags = 0;

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Profile"), &value_instance, &type, &flags, 0));
    TEST_ASSERT(type == MI_REFERENCE);
    TEST_ASSERT(value_instance.instance != NULL);
    TEST_ASSERT(!(flags & MI_FLAG_NULL));

    {   // verify first instance
        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instance, ZT("instanceID"), &value, &type, &flags, 0));
        TEST_ASSERT(type == MI_STRING);
        TEST_ASSERT(value.string == ut::String(ZT("number")));
        TEST_ASSERT(!(flags & MI_FLAG_NULL));

        MI_Uint32 count = 0;

        // Verify that only one property is returned - key ('InstanceID')
        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElementCount(value_instance.instance, &count));
        TEST_ASSERT(count == 1);
    }
}
NitsEndTest

NitsTestWithSetup(TestEnumerateInvalidClass, NumberProvTestSetup)
{
    //omicli ei test/cpp NonExisitingClass
    //PostResultMsg
    //{
    //    tag=4
    //    operationId=10000
    //    clientID=10097240
    //    result=7 [NOT_FOUND]
    //    request=NULL
    //}

    if(!TEST_ASSERT(MI_RESULT_OK == _CallEnumerate("test/cpp", "NonExisitingClass", MI_FALSE)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_INVALID_CLASS);

    TEST_ASSERT(s_instances.size() == 0);
}
NitsEndTest

STATIC void TestEnumerateFailedToLoadProvider(const char* ns)
{
    if(!TEST_ASSERT(MI_RESULT_OK == _CallGetInstance(ns, "X_FailedAtLoad.id=1")))
        return;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    // expecting 'failed' result, since load failed
    UT_ASSERT_EQUAL(s_results[0], MI_RESULT_FAILED);

    TEST_ASSERT(s_instances.size() == 0);
}

NitsTestWithSetup(TestEnumerateFailedToLoadProvider_c, NumberProvTestSetup)
{
    TestEnumerateFailedToLoadProvider("test/c");
}
NitsEndTest

NitsTestWithSetup(TestEnumerateFailedToLoadProvider_cpp, NumberProvTestSetup)
{
    TestEnumerateFailedToLoadProvider("test/cpp");
}
NitsEndTest

NitsTestWithSetup(TestInvokeSmallNumberSpellNumber0, NumberProvTestSetup)
{
    //omicli iv test/cpp X_SmallNumber SpellNumber num=0
    //instance of SpellNumber
    //{
    //    ReturnValue=zero
    //    num=NULL
    //}
    if(!TEST_ASSERT(MI_RESULT_OK == _CallInvoke("test/cpp", "X_SmallNumber", "SpellNumber", "num=0")))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) NitsReturn;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("ReturnValue"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_STRING);
    UT_ASSERT(value.string == ut::String(ZT("zero")));
    UT_ASSERT(!(flags & MI_FLAG_NULL));
}
NitsEndTest

NitsTestWithSetup(TestInvokeSmallNumberSpellNumber120394, NumberProvTestSetup)
{
    //omicli iv test/cpp X_SmallNumber SpellNumber num=120394
    //instance of SpellNumber
    //{
    //    ReturnValue=one hundred twenty  thousand three hundred ninety four
    //    num=NULL
    //}

    if(!TEST_ASSERT(MI_RESULT_OK == _CallInvoke("test/cpp", "X_SmallNumber", "SpellNumber", "num=120394")))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) NitsReturn;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("ReturnValue"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_STRING);
    UT_ASSERT(value.string == ut::String(ZT("one hundred twenty  thousand three hundred ninety four")));
    UT_ASSERT(!(flags & MI_FLAG_NULL));
}
NitsEndTest

NitsTestWithSetup(TestInvokeSmallNumberGetFactors_NotFound, NumberProvTestSetup)
{
    //omicli iv test/cpp X_SmallNumber.Number=11635 GetFactors
    //PostResultMsg
    //{
    //    tag=4
    //    operationId=10000
    //    clientID=10228312
    //    result=7 [NOT_FOUND]
    //    request=NULL
    //}

    if(!TEST_ASSERT(MI_RESULT_OK == _CallInvoke("test/cpp", "X_SmallNumber.Number=11635", "GetFactors", 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_NOT_FOUND);

    TEST_ASSERT(s_instances.size() == 0);
}
NitsEndTest

NitsTestWithSetup(TestInvokeSmallNumberGetFactors_InvalidParameter, NumberProvTestSetup)
{
    // trying to refer to non-static funciton in 'static' way
    //omicli iv test/cpp X_SmallNumber GetFactors
    //PostResultMsg
    //{
    //    tag=4
    //    operationId=10000
    //    clientID=10752600
    //    result=4 [INVALID_PARAMETER]
    //    request=NULL
    //}

    if(!TEST_ASSERT(MI_RESULT_OK == _CallInvoke("test/cpp", "X_SmallNumber", "GetFactors", 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_INVALID_PARAMETER);

    TEST_ASSERT(s_instances.size() == 0);
}
NitsEndTest

NitsTestWithSetup(TestInvokeSmallNumber_InvalidFn, NumberProvTestSetup)
{
    // trying to non-exisiting function
    //omicli iv test/cpp X_SmallNumber FunciotnThatDoesNotExist
    //PostResultMsg
    //{
    //    tag=4
    //    operationId=10000
    //    clientID=10752600
    //    result=4 [FAILED]
    //    request=NULL
    //}

    if(!TEST_ASSERT(MI_RESULT_OK == _CallInvoke("test/cpp", "X_SmallNumber", "FunciotnThatDoesNotExist", 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_FAILED);

    TEST_ASSERT(s_instances.size() == 0);
}
NitsEndTest

NitsTestWithSetup(TestInvokeSmallNumberGetFactors135, NumberProvTestSetup)
{
    //omicli iv test/cpp X_SmallNumber.Number=135 GetFactors
    //instance of GetFactors
    //{
    //    ReturnValue=4
    //    numbers={3, 3, 3, 5}
    //    spelled_numbers={three, three, three, five}
    //}

    if(!TEST_ASSERT(MI_RESULT_OK == _CallInvoke("test/cpp", "X_SmallNumber.Number=135", "GetFactors", 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) NitsReturn;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("ReturnValue"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT32);
    UT_ASSERT(value.uint32 == 4);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("numbers"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_UINT64A);
    TEST_ASSERT(value.uint64a.size == 4);
    TEST_ASSERT(value.uint64a.data[0] == 3);
    TEST_ASSERT(value.uint64a.data[1] == 3);
    TEST_ASSERT(value.uint64a.data[2] == 3);
    TEST_ASSERT(value.uint64a.data[3] == 5);
    TEST_ASSERT(!(flags & MI_FLAG_NULL));

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("spelled_numbers"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_STRINGA);
    TEST_ASSERT(value.stringa.size == 4);
    TEST_ASSERT(value.stringa.data[0] == ut::String(ZT("three")));
    TEST_ASSERT(value.stringa.data[1] == ut::String(ZT("three")));
    TEST_ASSERT(value.stringa.data[2] == ut::String(ZT("three")));
    TEST_ASSERT(value.stringa.data[3] == ut::String(ZT("five")));
    TEST_ASSERT(!(flags & MI_FLAG_NULL));

}
NitsEndTest

NitsTestWithSetup(TestInvokeHugeNumberSpellMagnitude, NumberProvTestSetup)
{
    //omicli iv test/cpp X_HugeNumber.Number=1000000 SpellMagnitude
    //instance of SpellMagnitude
    //{
    //    ReturnValue=six
    //}

    if(!TEST_ASSERT(MI_RESULT_OK == _CallInvoke("test/cpp", "X_HugeNumber.Number=1000000", "SpellMagnitude", 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) NitsReturn;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("ReturnValue"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_STRING);
    UT_ASSERT(value.string == ut::String(ZT("six")));
    UT_ASSERT(!(flags & MI_FLAG_NULL));

}
NitsEndTest

#if defined(CONFIG_POSIX)
NitsTestWithSetup(TestInvokeTerminate, NumberProvTestSetupOOPNamespace)
{
    NitsDisableFaultSim;
    //omicli iv test/cpp X_NumberWorld Terminate
    // should terminate agent process

    if(!TEST_ASSERT(MI_RESULT_OK == _CallInvoke("test/cpp", "X_NumberWorld", "Terminate", 0)))
        return;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_FAILED);

    TEST_ASSERT(s_instances.size() == 0);
}
NitsEndTest
#endif

NitsTestWithSetup(TestInvokeHugeNumberTestEmbedded, NumberProvTestSetup)
{
    //omicli iv test/cpp X_HugeNumber TestEmbedded <instance params>
    // current version of omicli does not support these parameters

    if(!TEST_ASSERT(MI_RESULT_OK == _CallInvoke("test/cpp", "X_HugeNumber", "TestEmbedded", 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) NitsReturn;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("ReturnValue"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_INSTANCE);
    UT_ASSERT(value.instance != NULL);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    MI_ConstString cn = 0;
    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(value.instance, &cn));
    TEST_ASSERT(cn == ut::String(ZT("X_TestObject")));

}
NitsEndTest

STATIC void _TestInvokePersonTestEmbeddedInstanceReturnKey20100609(const char* ns)
{
    //omicli iv test/cpp TestEmbeddedOperations.Key=1 TestEmbeddedInstanceReturnKey20100609
    //instance of TestEmbeddedInstanceReturnKey20100609
    //{
    //    ReturnValue=instance of X_TestEmbeddedInstanceMIReturnObject
    //    {
    //        id=20100609
    //        s=NULL
    //    }
    //}

    if(!TEST_ASSERT(MI_RESULT_OK == _CallInvoke(ns, "TestEmbeddedOperations.Key=1", "TestEmbeddedInstanceReturnKey20100609", 0)))
        return;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;
    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("ReturnValue"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_INSTANCE);
    UT_ASSERT(value.instance != NULL);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    MI_ConstString cn = 0;
    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(value.instance, &cn));
    TEST_ASSERT(cn == ut::String(ZT("X_TestEmbeddedInstanceMIReturnObject")));

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value.instance, ZT("id"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_UINT64);
    TEST_ASSERT(value.uint64 == 20100609);
    TEST_ASSERT(!(flags & MI_FLAG_NULL));
}

NitsTestWithSetup(TestInvokePersonTestEmbeddedInstanceReturnKey20100609_c, NumberProvTestSetup)
{
    _TestInvokePersonTestEmbeddedInstanceReturnKey20100609("test/c");
}
NitsEndTest
NitsTestWithSetup(TestInvokePersonTestEmbeddedInstanceReturnKey20100609_cpp, NumberProvTestSetup)
{
    _TestInvokePersonTestEmbeddedInstanceReturnKey20100609("test/cpp");
}
NitsEndTest

STATIC void _TestInvokePersonTestEmbeddedObjectReturnKey20100609(const char* ns)
{
    //omicli iv test/cpp TestEmbeddedOperations.Key=1 TestEmbeddedObjectReturnKey20100609
    //instance of TestEmbeddedObjectReturnKey20100609
    //{
    //    ReturnValue=instance of X_TestEmbeddedObjectNotReferenced
    //    {
    //        ObjectID=20100609
    //    }
    //}

    if(!TEST_ASSERT(MI_RESULT_OK == _CallInvoke(ns, "TestEmbeddedOperations.Key=1", "TestEmbeddedObjectReturnKey20100609", 0)))
        return;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("ReturnValue"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_INSTANCE);
    UT_ASSERT(value.instance != NULL);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    MI_ConstString cn = 0;
    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(value.instance, &cn));
    TEST_ASSERT(cn == ut::String(ZT("X_TestEmbeddedObjectNotReferenced")));

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value.instance, ZT("ObjectId"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_UINT64);
    TEST_ASSERT(value.uint64 == 20100609);
    TEST_ASSERT(!(flags & MI_FLAG_NULL));
}


NitsTestWithSetup(TestInvokePersonTestEmbeddedObjectReturnKey20100609_c, NumberProvTestSetup)
{
    _TestInvokePersonTestEmbeddedObjectReturnKey20100609("test/c");
}
NitsEndTest

NitsTestWithSetup(TestInvokePersonTestEmbeddedObjectReturnKey20100609_cpp, NumberProvTestSetup)
{
    _TestInvokePersonTestEmbeddedObjectReturnKey20100609("test/cpp");
}
NitsEndTest

STATIC void _TestInvokePersonTestEmbeddedParameters(const char* ns)
{
    //omicli iv test/cpp TestEmbeddedOperations.Key=1 TestEmbedded
    // omicli does not support it yet ([in] embedded objects params)


    // INPUT:
    // objectsArray - 2 instances of MSFT_Base
    // objectSingle - MSFT_Person
    // testObjectsArray - 3 objects
    // testObjectSingle - not set

    // OUTPUT
    // objectsArray - 2 instances of MSFT_Animal with the same keys and species "test"
    // objectSingle - the same
    // testObjectsArray - last 2 objects of input
    // testObjectSingle - key is a sum of input objects

    //[static, EmbeddedInstance("X_TestObject")]
    //ut::String TestEmbedded(
    //    [EmbeddedObject, IN, OUT]
    //    ut::String objectsArray[],
    //    [EmbeddedObject, IN, OUT]
    //    ut::String objectSingle,
    //    
    //    [EmbeddedInstance("X_TestObject"), in,out]
    //    ut::String testObjectsArray[],
    //    [EmbeddedInstance("X_TestObject"), in,out]
    //    ut::String testObjectSingle
    //);


    MI_Result r;
    MI_Instance* dynamicInstanceParams = 0;
    Batch   dynamicBatch = BATCH_INITIALIZER;

    r = Instance_NewDynamic(
        &dynamicInstanceParams,
        MI_T("params"),
        MI_FLAG_CLASS,
        &dynamicBatch);

    if(!TEST_ASSERT (MI_RESULT_OK == r))
        return;

    // objectSingle
    MI_Value value;

    value.instance = _ReferenceStringToInstance(&dynamicBatch, "MSFT_Animal.Key=17", 0);
    if(!TEST_ASSERT( value.instance ))
        return;

    r = MI_Instance_AddElement(dynamicInstanceParams, MI_T("objectSingle"), 
        &value, MI_INSTANCE, MI_FLAG_BORROW);
    if(!TEST_ASSERT(r == MI_RESULT_OK))
        return;

    MI_Instance* instances[3];

    instances[0] = _ReferenceStringToInstance(&dynamicBatch, "MSFT_Animal.Key=101", 0);
    
    instances[1] = _ReferenceStringToInstance(&dynamicBatch, "MSFT_Animal.Key=102", 0);
    
    if(!TEST_ASSERT((instances[0] != NULL) && (instances[1] != NULL)))
        return;

    value.instancea.data = instances;
    value.instancea.size = 2;

    r = MI_Instance_AddElement(dynamicInstanceParams, MI_T("objectsArray"), 
        &value, MI_INSTANCEA, MI_FLAG_BORROW);
    if(!TEST_ASSERT(r == MI_RESULT_OK))
        return;

    instances[0] = _ReferenceStringToInstance(&dynamicBatch, "X_TestObject.id=101", 0);
    instances[1] = _ReferenceStringToInstance(&dynamicBatch, "X_TestObject.id=102", 0);
    instances[2] = _ReferenceStringToInstance(&dynamicBatch, "X_TestObject.id=103", 0);

    if(!TEST_ASSERT((instances[0] != NULL) && (instances[1] != NULL) && (instances[2] != NULL)))
        return;

    value.instancea.data = instances;
    value.instancea.size = 3;

    r = MI_Instance_AddElement(dynamicInstanceParams, 
        MI_T("testObjectsArray"), &value, MI_INSTANCEA, MI_FLAG_BORROW);
    if(!TEST_ASSERT(r == MI_RESULT_OK))
        return;

    if (trace)
        MI_Instance_Print(dynamicInstanceParams, stdout, 0);

    if(!TEST_ASSERT(MI_RESULT_OK == _CallInvoke(ns, "TestEmbeddedOperations.Key=1", "TestEmbedded", 0, dynamicInstanceParams)))
        return;

    Batch_Destroy(&dynamicBatch);

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("ReturnValue"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_INSTANCE);
    UT_ASSERT(value.instance != NULL);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    MI_ConstString cn = 0;
    if(!TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(value.instance, &cn)))
        return;
    if(!TEST_ASSERT(cn == ut::String(ZT("X_TestObject"))))
        return;

    if(!TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value.instance, ZT("id"), &value, &type, &flags, 0)))
        return;
    TEST_ASSERT(type == MI_UINT64);

    TEST_ASSERT(value.uint64 == (101+102+103));   /* expecting sum of keys */
    TEST_ASSERT(!(flags & MI_FLAG_NULL));

    {
        MI_Value value_instance;

        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("testObjectsArray"), &value_instance, &type, &flags, 0));
        TEST_ASSERT(type == MI_INSTANCEA);
        TEST_ASSERT(value_instance.instancea.size == 2);
        TEST_ASSERT(!(flags & MI_FLAG_NULL));

        /* expecting last two elements */
        for ( int num = 0; num < 2; num++ )
        {
            TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(value_instance.instancea.data[num], &cn));
            TEST_ASSERT(cn == ut::String(ZT("X_TestObject")));

            TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[num], ZT("id"), &value, &type, &flags, 0));
            TEST_ASSERT(type == MI_UINT64);
            TEST_ASSERT(value.uint64 == (MI_Uint64)(102 + num));
            TEST_ASSERT(!(flags & MI_FLAG_NULL));
        }
    }
    {
        MI_Value value_instance;

        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("objectsArray"), &value_instance, &type, &flags, 0));
        TEST_ASSERT(type == MI_INSTANCEA);
        TEST_ASSERT(value_instance.instancea.size == 2);
        TEST_ASSERT(!(flags & MI_FLAG_NULL));

        /* expecting last two elements */
        for ( int num = 0; num < 2; num++ )
        {
            TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(value_instance.instancea.data[num], &cn));
            TEST_ASSERT(cn == ut::String(ZT("MSFT_Animal")));

            TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[num], ZT("species"), &value, &type, &flags, 0));
            TEST_ASSERT(type == MI_STRING);
            TEST_ASSERT(value.string == ut::String(ZT("test")));
            TEST_ASSERT(!(flags & MI_FLAG_NULL));
        }
    }

}


NitsTestWithSetup(TestInvokePersonTestEmbeddedParameters_c, NumberProvTestSetup)
{
    _TestInvokePersonTestEmbeddedParameters("test/c");
}
NitsEndTest

NitsTestWithSetup(TestInvokePersonTestEmbeddedParameters_cpp, NumberProvTestSetup)
{
    _TestInvokePersonTestEmbeddedParameters("test/cpp");
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsFriends, NumberProvTestSetup)
{
    //omicli a test/cpp MSFT_Person.Key=1  -ac MSFT_Friends -rc MSFT_Base
    //instance of MSFT_Person
    //{
    //    Key=2
    //    Species=NULL
    //    Last=Adams
    //    First=John
    //}

    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "MSFT_Person.Key=1", "MSFT_Friends", "MSFT_Base", "Left", "Right")))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) NitsReturn;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Last"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_STRING);
    TEST_ASSERT(value.string == ut::String(ZT("Adams")));
    TEST_ASSERT(!(flags & MI_FLAG_NULL));

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("First"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_STRING);
    TEST_ASSERT(value.string == ut::String(ZT("John")));
    TEST_ASSERT(!(flags & MI_FLAG_NULL));

    TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Key"), &value, &type, &flags, 0));
    TEST_ASSERT(type == MI_UINT32);
    TEST_ASSERT(value.uint32 == 2);
    TEST_ASSERT(!(flags & MI_FLAG_NULL));
}
NitsEndTest

enum ExpectedNumProvInstances
{
    enumExpectProfileWorld  = 1,
    enumExpectProfileHuge   = 2,
    enumExpectSmallEven     = 4,
    enumExpectSmallOdd      = 8,
    enumExpectHuge          = 16,
    enumExpectWorld         = 32,
    enumExpectSmallNumber350    = 64,
    enumExpectSmallNumber1400   = 128,
    enumExpectSmallNumber0  = 256
};

STATIC void _ValidateNumberProvInstances(
    int expected)
{
    set<MI_Uint64> even, odd, huge;
    bool gotWorld = false, 
        gotProfileWorld = false, 
        gotProfileNumber = false;

    for ( size_t i = 0; i < s_instances.size(); i++ )
    {
        MI_ConstString cn = 0;
        TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(s_instances[i]->instance, &cn));

        MI_Value value;
        MI_Type type;
        MI_Uint32 flags = 0;

        ut::String s(cn);
        if ( s == MI_T("X_SmallNumber") )
        {

            TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[i]->instance, ZT("Number"), &value, &type, &flags, 0));
            TEST_ASSERT(type == MI_UINT64);
            TEST_ASSERT(!(flags & MI_FLAG_NULL));
            if (value.uint64 % 2 == 0)
            {
                TEST_ASSERT( (expected & (enumExpectSmallEven|enumExpectSmallNumber350|enumExpectSmallNumber1400|enumExpectSmallNumber0) ) != 0 );
                even.insert(value.uint64);
            }
            else
            {
                TEST_ASSERT( (expected & (enumExpectSmallOdd) ) != 0 );
                odd.insert(value.uint64);
            }

            // check that SpelledNumber is not empty
            TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[i]->instance, ZT("SpelledNumber"), &value, &type, &flags, 0));
            TEST_ASSERT(type == MI_STRING);
            TEST_ASSERT(!(flags & MI_FLAG_NULL));
            TEST_ASSERT( !ut::String(value.string).empty());

            // namespace
            MI_ConstString ns = 0;
            TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetNameSpace(s_instances[i]->instance, &ns));

            TEST_ASSERT( ns != 0 );
            TEST_ASSERT(ns == ut::String(ZT("test/cpp")));
        }
        else if ( s == MI_T("X_HugeNumber") )
        {
            TEST_ASSERT( (expected & enumExpectHuge ) != 0 );

            TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[i]->instance, ZT("Number"), &value, &type, &flags, 0));
            TEST_ASSERT(type == MI_UINT64);
            TEST_ASSERT(!(flags & MI_FLAG_NULL));

            huge.insert(value.uint64);
        }
        else if ( s == MI_T("X_NumberWorld") )
        {
            TEST_ASSERT( (expected & enumExpectWorld ) != 0 );

            TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[i]->instance, ZT("Name"), &value, &type, &flags, 0));
            TEST_ASSERT(type == MI_STRING);
            TEST_ASSERT(!(flags & MI_FLAG_NULL));
            TEST_ASSERT(value.string == ut::String(ZT("theWorld")));
            gotWorld = true;

            // namespace
            MI_ConstString ns = 0;
            TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetNameSpace(s_instances[i]->instance, &ns));

            TEST_ASSERT( ns != 0 );
            TEST_ASSERT(ns == ut::String(ZT("test/cpp")));
        }
        else if ( s == MI_T("X_Profile") )
        {
            TEST_ASSERT( (expected & (enumExpectProfileWorld|enumExpectProfileHuge) ) != 0 );

            TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[i]->instance, ZT("InstanceID"), &value, &type, &flags, 0));
            TEST_ASSERT(type == MI_STRING);
            TEST_ASSERT(!(flags & MI_FLAG_NULL));

            if (value.string == ut::String(ZT("world")))
            {
                TEST_ASSERT( (expected & (enumExpectProfileWorld) ) != 0 );
                gotProfileWorld = true;
            }
            else if (value.string == ut::String(ZT("number")))
            {
                TEST_ASSERT( (expected & (enumExpectProfileHuge) ) != 0 );
                gotProfileNumber = true;
            }
            else
                UT_ASSERT_FAILED_MSG( (string("unexpected profile ") + ut::StrToChar(value.string)).c_str() );

            // namespace
            MI_ConstString ns = 0;
            TEST_ASSERT(MI_RESULT_OK == MI_Instance_GetNameSpace(s_instances[i]->instance, &ns));

            TEST_ASSERT( ns != 0 );
            TEST_ASSERT(ns == ut::String(ZT("interop")));

        }
        else
        {
            UT_ASSERT_FAILED_MSG( (string("unexpected class ") + ut::StrToChar(s)).c_str() );
        }
    }

    // validate results
    if (expected & enumExpectHuge)
    {
        TEST_ASSERT(huge.size() == 2);
        TEST_ASSERT(huge.find(1000000) != huge.end());
        TEST_ASSERT(huge.find(1000000000) != huge.end());
    }

    if (expected & enumExpectSmallEven)
    {
        TEST_ASSERT(even.size() == 5000);
        for ( int i = 0; i < 10000; i++ )
        {
            if ( i % 2 != 0 )
                continue;

            TEST_ASSERT(even.find(i) != even.end());
        }
    }
    if (expected & enumExpectSmallNumber0)
    {
        TEST_ASSERT(even.find(0) != even.end());
    }
    if (expected & enumExpectSmallNumber350)
    {
        TEST_ASSERT(even.find(350) != even.end());
    }
    if (expected & enumExpectSmallNumber1400)
    {
        TEST_ASSERT(even.find(1400) != even.end());
    }
    if (expected & enumExpectSmallOdd)
    {
        TEST_ASSERT(odd.size() == 5000);
        for ( int i = 0; i < 10000; i++ )
        {
            if ( i % 2 == 0 )
                continue;

            TEST_ASSERT(odd.find(i) != odd.end());
        }
    }

    if (expected & enumExpectProfileWorld)
    {
        TEST_ASSERT(gotProfileWorld);
    }
    if (expected & enumExpectProfileHuge)
    {
        TEST_ASSERT(gotProfileNumber);
    }
    if (expected & enumExpectWorld)
    {
        TEST_ASSERT(gotWorld);
    }
}

NitsTestWithSetup(TestAssociatorsNumProv_AllOfWorld, NumberProvTestSetup)
{
    NitsDisableFaultSim;

    // omicli a test/cpp X_numberWorld.Name=theWorld
    // ... gazillion of results
    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", 0, 0, 0, 0)))
        return;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (
        10000 /* small numbers */ + 2 /* huge numbers */ + 1 /* profile */
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectProfileWorld | enumExpectSmallEven | enumExpectSmallOdd | enumExpectHuge);
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_ProfileOfWorldByAssocClass, NumberProvTestSetup)
{
    //omicli a test/cpp X_numberWorld.Name=theWorld -ac X_ElementConformsToProfile
    //instance of X_Profile
    //{
    //    InstanceID=world
    //    RegisteredName=World
    //}

   if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", "X_ElementConformsToProfile", 0, 0, 0)))
       NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (
        1 /* profile */
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectProfileWorld);
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_ProfileOfWorldByResultClass, NumberProvTestSetup)
{
    //omicli a test/cpp X_numberWorld.Name=theWorld -rc X_Profile
    //instance of X_Profile
    //{
    //    InstanceID=world
    //    RegisteredName=World
    //}

   if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", 0, "X_Profile", 0, 0)))
       NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (
        1 /* profile */
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectProfileWorld);
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_ProfileOfWorldByRole, NumberProvTestSetup)
{
    //omicli a test/cpp X_numberWorld.Name=theWorld -role Element
    //instance of X_Profile
    //{
    //    InstanceID=world
    //    RegisteredName=World
    //}

   if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", 0, 0, "Element", 0)))
       NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (
        1 /* profile */
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectProfileWorld);
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_ProfileOfWorldByResultRole, NumberProvTestSetup)
{
    //omicli a test/cpp X_numberWorld.Name=theWorld -rrole Profile
    //instance of X_Profile
    //{
    //    InstanceID=world
    //    RegisteredName=World
    //}

   if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", 0, 0, 0, "Profile")))
       NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (
        1 /* profile */
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectProfileWorld);
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_AllNumbersOfWorld, NumberProvTestSetup)
{
    NitsDisableFaultSim;
    // omicli a test/cpp X_numberWorld.Name=theWorld -ac x_AllNumbers
    // ... gazillion of results
    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", "x_aLLnUMBERS", 0, 0, 0)))
        return;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (
        10000 /* small numbers */ + 2 /* huge numbers */ 
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectSmallEven | enumExpectSmallOdd | enumExpectHuge);
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_AllHugeNumbersOfWorld, NumberProvTestSetup)
{
    // omicli a test/cpp X_numberWorld.Name=theWorld -ac x_HugeNumbers
    // ... gazillion of results
    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", "x_HugeNumbers", 0, 0, 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (
        2 /* huge numbers */ 
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectHuge);
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_AllEvenNumbersOfWorld, NumberProvTestSetup)
{
    NitsDisableFaultSim;
    // omicli a test/cpp X_numberWorld.Name=theWorld -ac X_EvenSmallNumbers
    // ... gazillion of results
    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", "X_EvenSmallNumbers", 0, 0, 0)))
        return;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (
        5000 /* even small numbers */ 
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectSmallEven);
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_AllOddNumbersOfWorld, NumberProvTestSetup)
{
    NitsDisableFaultSim;
    // omicli a test/cpp X_numberWorld.Name=theWorld -ac X_OddSmallNumbers
    // ... gazillion of results
    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", "X_OddSmallNumbers", 0, 0, 0)))
        return;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (
        5000 /* small numbers */ 
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectSmallOdd);
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_AllProfile, NumberProvTestSetup)
{
    // omicli a test/cpp X_Profile.InstanceID=number 
    

    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_Profile.InstanceID=number", 0, 0, 0, 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (
        2 /* huge numbers */ 
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectHuge);
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_AllOfSmallNumber, NumberProvTestSetup)
{
    //omicli a test/cpp X_smallNumber.Number=700
    //instance of X_SmallNumber
    //{
    //    Description=NULL
    //    Number=350
    //    SpelledNumber=three hundred fifty
    //}
    //instance of X_SmallNumber
    //{
    //    Description=NULL
    //    Number=1400
    //    SpelledNumber=one thousand four hundred
    //}
    //instance of X_NumberWorld
    //{
    //    Description=NULL
    //    Name=theWorld
    //    Version=0.1
    //}
    

    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_smallNumber.Number=700", 0, 0, 0, 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (
        3 
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectWorld | enumExpectSmallNumber1400 | enumExpectSmallNumber350 );
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_AllOfSmallNumberByRoleNumber, NumberProvTestSetup)
{
    //omicli a test/cpp X_smallNumber.Number=700  -role number
    //instance of X_SmallNumber
    //{
    //    Description=NULL
    //    Number=350
    //    SpelledNumber=three hundred fifty
    //}
    //instance of X_NumberWorld
    //{
    //    Description=NULL
    //    Name=theWorld
    //    Version=0.1
    //}    

    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_smallNumber.Number=700", 0, 0, "number", 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (
        2 
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectWorld | enumExpectSmallNumber350 );
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_AllOfSmallNumberByRoleHalf, NumberProvTestSetup)
{
    //omicli a test/cpp X_smallNumber.Number=700  -role half
    //instance of X_SmallNumber
    //{
    //    Description=NULL
    //    Number=1400
    //    SpelledNumber=one thousand four hundred
    //}

    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_smallNumber.Number=700", 0, 0, "half", 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (
        1
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectSmallNumber1400 );
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_AllOfSmallNumberByAssocClassHalves, NumberProvTestSetup)
{
    //omicli a test/cpp X_smallNumber.Number=700  -ac x_halves
    //instance of X_SmallNumber
    //{
    //    Description=NULL
    //    Number=350
    //    SpelledNumber=three hundred fifty
    //}
    //instance of X_SmallNumber
    //{
    //    Description=NULL
    //    Number=1400
    //    SpelledNumber=one thousand four hundred
    //}

    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_smallNumber.Number=700", "x_halves", 0, 0, 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (
        2
        ));

    // verify instances
    _ValidateNumberProvInstances( enumExpectSmallNumber350 | enumExpectSmallNumber1400 );
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_DoubleZeroInstancesOfSmallNumberByAssocClassHalves, NumberProvTestSetup)
{
    //omicli a test/cpp X_smallNumber.Number=0 -ac x_halves
    //instance of X_SmallNumber
    //{
    //    Description=NULL
    //    Number=0
    //    SpelledNumber=zero
    //}
    //instance of X_SmallNumber
    //{
    //    Description=NULL
    //    Number=0
    //    SpelledNumber=zero
    //}


    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_smallNumber.Number=0", "x_halves", 0, 0, 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (
        2
        ));

    // verify instances
    _ValidateNumberProvInstances( enumExpectSmallNumber0 );
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_AllOfSmallNumberByAllFilters, NumberProvTestSetup)
{
    //omicli a test/cpp X_smallNumber.Number=0 -ac x_halves -rc x_number -role half -rrole number
    //instance of X_SmallNumber
    //{
    //    Description=NULL
    //    Number=0
    //    SpelledNumber=zero
    //}

    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_smallNumber.Number=0", "x_halves", "x_number", "half", "number")))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (
        1
        ));

    // verify instances
    _ValidateNumberProvInstances( enumExpectSmallNumber0 );
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_ProfileOfWorldByRoleRRole, NumberProvTestSetup)
{
    //omicli a test/cpp X_numberWorld.Name=theWorld -ac X_AllNumbers -rc X_Number -role Number -rrole Number
    // 
    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", "X_AllNumbers", "X_Number", "Number", "Number")))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (0));
}
NitsEndTest


NitsTestWithSetup(TestAssociatorsNumProv_ProfileOfWorldByInvalidAssocClass, NumberProvTestSetup)
{
    // omicli a test/cpp X_numberWorld.Name=theWorld -ac x_halves
    // 
    // this assoc class is not related to X_NumberWorld class
    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", "x_halves", 0, 0, 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_NOT_SUPPORTED);

    TEST_ASSERT(s_instances.size() == (0));
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_ProfileOfWorldByInvalidResultClass, NumberProvTestSetup)
{
    // omicli a test/cpp X_numberWorld.Name=theWorld -rc SomeInvalidClass
    // 
    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", 0, "SomeInvalidClass", 0, 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_INVALID_CLASS);

    TEST_ASSERT(s_instances.size() == (0));
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_InvalidNameSpace, NumberProvTestSetup)
{
    // omicli a invalid/namespace X_numberWorld.Name=theWorld
    // 
    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("invalid/namespace", "X_numberWorld.Name=theWorld", 0, 0, 0, 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_INVALID_NAMESPACE);

    TEST_ASSERT(s_instances.size() == (0));
}
NitsEndTest

NitsTestWithSetup(TestAssociatorsNumProv_NoInstance, NumberProvTestSetup)
{
    // omicli a test/cpp X_numberWorld.UnknownProp=theWorld
    // 
    if(!TEST_ASSERT(MI_RESULT_OK == _CallAssociators("test/cpp", "X_numberWorld.UnknownProp=theWorld", 0, 0, 0, 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);

    /*if (s_results[0] != MI_RESULT_NOT_FOUND)
        cout << "res " << s_results[0] << endl;*/

    //TEST_ASSERT(s_results[0] == MI_RESULT_NOT_FOUND);
    TEST_ASSERT(s_results[0] != MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (0));
}
NitsEndTest

NitsTestWithSetup(TestReferencesNumProv_ProfileByAssocClass, NumberProvTestSetup)
{
    //omicli r test/cpp X_Profile.InstanceID=world -ac X_NumberWorldConformsToProfile
    //instance of X_NumberWorldConformsToProfile
    //{
    //    Profile=    instance of interop/X_Profile
    //    {
    //        InstanceID=world
    //        RegisteredName=World
    //    }
    //
    //    Element=    instance of test/cpp/X_NumberWorld
    //    {
    //        Description=NULL
    //        Name=theWorld
    //        Version=0.1
    //    }
    //
    //}
  
    if(!TEST_ASSERT(MI_RESULT_OK == _CallReferences("test/cpp", "X_Profile.InstanceID=world", "X_NumberWorldConformsToProfile", 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    TEST_ASSERT(s_results[0] == MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == (
        1
        ));

    // verify instances
    //_ValidateNumberProvInstances( enumExpectSmallNumber0 );
    // ATTN!: Add instance verification, once MI_InstanceCompare is ready
}
NitsEndTest

NitsTestWithSetup(TestNamespaceParameterUsingInvoke, NumberProvTestSetup)
{

    if(!TEST_ASSERT(MI_RESULT_OK == _CallInvoke("test/cpp", "x_numberWorld", "ReturnNamespace", 0)))
        NitsReturn;

    // validate response
    TEST_ASSERT(s_results.size() == 1);
    UT_ASSERT_EQUAL(s_results[0], MI_RESULT_OK);

    TEST_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) NitsReturn;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("ReturnValue"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_STRING);
    UT_ASSERT(!(flags & MI_FLAG_NULL));
    UT_ASSERT(value.string == ut::String(ZT("test/cpp")) || value.string == ut::String(ZT("oop/requestor/test/cpp")));
}
NitsEndTest

NitsTestWithSetup(TestNamespaceParameterUsingEnumerate, NumberProvTestSetup)
{
    if(!TEST_ASSERT(MI_RESULT_OK == _CallEnumerate("test/cpp", "x_numberWorld", MI_FALSE)))
        NitsReturn;

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT_EQUAL(s_results[0], MI_RESULT_OK);

    UT_ASSERT_EQUAL(s_instances.size(), 1);

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT_EQUAL(MI_RESULT_OK, MI_Instance_GetElement(s_instances[0]->instance, ZT("ns"), &value, &type, &flags, 0));
    UT_ASSERT_EQUAL(type, MI_STRING);
    TEST_ASSERT(!(flags & MI_FLAG_NULL));
    TEST_ASSERT(value.string == ut::String(ZT("test/cpp")) || value.string == ut::String(ZT("oop/requestor/test/cpp")));
}
NitsEndTest

#ifdef _PREFAST_
# pragma prefast (pop)
#endif
