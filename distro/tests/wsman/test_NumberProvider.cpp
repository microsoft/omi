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
#include <io/io.h>
#include <omiclient/client.h>

#define STATIC

using namespace std;
//using namespace mi;

/* extern definitions - these functions are declared in test_wsman.cpp */
void WSMAN_Tests_With_Server();

static Protocol* s_protocol;
static int trace = 0;
static vector<MI_Result> s_results;
static vector<PostInstanceMsg*> s_instances;
static string  s_nsPrefix;

static MI_Uint64 _NextMsgID()
{
    static MI_Uint64 _msgID = 10000;
    return _msgID++;
}

BEGIN_EXTERNC
static MI_Boolean _Callback(
    Protocol* protocol,
    Message* msg,
    void* data)
{
    data=data;
    protocol = protocol;

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
            Zprintf(ZT("unsupported msg: tag=%u\n"), msg->tag);
            break;
        }
    }

    return MI_TRUE;
}
END_EXTERNC

void SetupHelper()
{
    Sock_Start();
    StartServerAndConnect(true, _Callback, &s_protocol);
}

void CleanupHelper()
{
    StopServerAndDisconnect(&s_protocol);
    Sock_Stop();
}

static void setUp()
{
    SetupHelper();

    s_instances.reserve(11000);
}

static void cleanup()
{
    s_results.clear();

    for ( unsigned int i = 0; i < s_instances.size(); i++ )
        PostInstanceMsg_Release(s_instances[i]);
    
    s_instances.clear();

    CleanupHelper();
}

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
            UT_ASSERT(pos);

            *pos = 0;
            pos++;
            value.string = pos;

            // Set the property.
            r = MI_Instance_AddElement(dynamicInstance, name, &value, 
                MI_STRING, MI_FLAG_KEY|MI_FLAG_BORROW);

            UT_ASSERT(r == MI_RESULT_OK);
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
    cn = Batch_StrZdup(batch, cmdArg);
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

    UT_ASSERT(MI_RESULT_OK == r);

    // Set keys from key-value pairs.
    _GetKeysFromCmd(dynamicInstance,keys);
    return  dynamicInstance;
}


STATIC void _CallGetInstance( const char* ns_, const char* ref )
{
    GetInstanceReq* msg;
    MI_Result r;
    MI_Instance* dynamicInstance;
    Batch batch = BATCH_INITIALIZER;
    string ns = s_nsPrefix + ns_;

    msg = GetInstanceReq_New(_NextMsgID(), BinaryProtocolFlag);

    msg->nameSpace = Batch_StrZdup(msg->base.batch, ns.c_str());

    /* create dynamic instance */
    dynamicInstance = _ReferenceStringToInstance(&batch, ref, 0);

    UT_ASSERT(dynamicInstance);

    if (trace)
        MI_Instance_Print(dynamicInstance, stdout, 0);

    /* pack instance */
    r = InstanceToBatch(dynamicInstance, NULL, NULL, msg->base.batch, 
            &msg->packedInstanceNamePtr, &msg->packedInstanceNameSize);

    UT_ASSERT(MI_RESULT_OK == r);

    r = Protocol_Send(s_protocol, &msg->base);

    UT_ASSERT(MI_RESULT_OK == r);

    GetInstanceReq_Release(msg);
    Batch_Destroy(&batch);

    // process send/recv loop
    // run loop with 20 ms increment until result received or 20 sec elapsed

    for (int i = 0; i < 1000 && s_results.empty(); i++)
        Protocol_Run(s_protocol, 20000);
}

STATIC void _CallEnumerate( const char* ns_, const char* cn, MI_Boolean deep )
{
    EnumerateInstancesReq* msg;
    MI_Result r;
    string ns = s_nsPrefix + ns_;

    // Create new request.
    msg = EnumerateInstancesReq_New(_NextMsgID(), BinaryProtocolFlag);

    msg->nameSpace = Batch_StrZdup(msg->base.batch, ns.c_str());
    msg->className = Batch_StrZdup(msg->base.batch, cn);
    msg->deepInheritance = deep;

    r = Protocol_Send(s_protocol, &msg->base);

    UT_ASSERT(MI_RESULT_OK == r);

    EnumerateInstancesReq_Release(msg);

    // process send/recv loop
    // run loop with 20 ms increment until result received or 20 sec elapsed
    for (int i = 0; i < 1000 && s_results.empty(); i++)
        Protocol_Run(s_protocol, 20000);
}

STATIC void _CallInvoke( 
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
    msg = InvokeReq_New(_NextMsgID(), BinaryProtocolFlag);

    // Extract arguments.
    msg->nameSpace = Batch_StrZdup(msg->base.batch, ns.c_str());

    if (!msg->nameSpace)
    {
        UT_ASSERT("Out of memory" && NULL);
        return;
    }

    /* create dynamic instance */
    {
        dynamicInstance = _ReferenceStringToInstance( &dynamicBatch, ref, &cn );

        msg->className = Batch_Zdup(msg->base.batch, cn);

        if (trace && dynamicInstance)
            MI_Instance_Print(dynamicInstance, stdout, 0);

        /* pack instance */
        if (dynamicInstance)
        {
            r = InstanceToBatch(dynamicInstance, NULL, NULL, msg->base.batch, 
                    &msg->packedInstancePtr, &msg->packedInstanceSize);

            UT_ASSERT(MI_RESULT_OK == r);
        }
    }

    msg->function = Batch_StrZdup(msg->base.batch, fn);

    /* params */
    if (char_params)
    {
        /* parameters instance classname is ignored, but has to have valid syntax */
        params_cn = Batch_StrZdup(&dynamicBatch, "param");

        r = Instance_NewDynamic(
            &dynamicInstanceParams,
            params_cn,
            MI_FLAG_CLASS,
            &dynamicBatch);

        UT_ASSERT (MI_RESULT_OK == r);

        // Set keys from key-value pairs.
        params = Batch_StrZdup(&dynamicBatch, char_params);
        _GetKeysFromCmd(dynamicInstanceParams,params);

        if (trace)
            MI_Instance_Print(dynamicInstanceParams, stdout, 0);

        /* pack instance */
        r = InstanceToBatch(dynamicInstanceParams, NULL, NULL, msg->base.batch, 
                &msg->packedInstanceParamsPtr, &msg->packedInstanceParamsSize);
        UT_ASSERT (MI_RESULT_OK == r);
    }
    else if (outParam)
    {
        /* pack instance */
        r = InstanceToBatch(outParam, NULL, NULL, msg->base.batch, 
                &msg->packedInstanceParamsPtr, &msg->packedInstanceParamsSize);
        UT_ASSERT (MI_RESULT_OK == r);
    }

    r = Protocol_Send(s_protocol, &msg->base);
    UT_ASSERT (MI_RESULT_OK == r);

    InvokeReq_Release(msg);
    Batch_Destroy(&dynamicBatch);

    // process send/recv loop
    // run loop with 20 ms increment until result received or 20 sec elapsed
    for (int i = 0; i < 1000 && s_results.empty(); i++)
        Protocol_Run(s_protocol, 20000);
}

STATIC void _CallAssociators(const char* ns_, const char* ref, const char* ac, const char* rc, const char* role, const char* rrole)
{
    AssociationsOfReq* msg;
    MI_Result r;
    MI_Instance* dynamicInstance = 0;
    Batch   dynamicBatch = BATCH_INITIALIZER;
    string ns = s_nsPrefix + ns_;

    // Create new request.
    msg = AssociationsOfReq_New(_NextMsgID(), BinaryProtocolFlag, AssociatorsOfReqTag);

    // Extract arguments.
    msg->nameSpace = Batch_StrZdup(msg->base.batch, ns.c_str());

    /* create dynamic instance */
    /* create dynamic instance */
    dynamicInstance = _ReferenceStringToInstance( &dynamicBatch, ref, 0 );

    UT_ASSERT(dynamicInstance);

    if (trace)
        MI_Instance_Print(dynamicInstance, stdout, 0);

    /* pack instance */
    r = InstanceToBatch(dynamicInstance, NULL, NULL, msg->base.batch, 
            &msg->packedInstancePtr, &msg->packedInstanceSize);

    UT_ASSERT(MI_RESULT_OK == r);

    // optional params
    if (ac)
        msg->assocClass = Batch_StrZdup(msg->base.batch, ac);

    if (rc)
        msg->resultClass = Batch_StrZdup(msg->base.batch, rc);

    if (role)
        msg->role = Batch_StrZdup(msg->base.batch, role);

    if (rrole)
        msg->resultRole = Batch_StrZdup(msg->base.batch, rrole);

    r = Protocol_Send(s_protocol, &msg->base);

    UT_ASSERT(MI_RESULT_OK == r);

    AssociationsOfReq_Release(msg);
    Batch_Destroy(&dynamicBatch);


    // process send/recv loop
    // run loop with 20 ms increment until result received or 20 sec elapsed
    for (int i = 0; i < 1000 && s_results.empty(); i++)
        Protocol_Run(s_protocol, 20000);
}

STATIC void _CallReferences( const char* ns_, const char* ref, const char* ac, const char* role )
{
    AssociationsOfReq* msg;
    MI_Result r;
    MI_Instance* dynamicInstance = 0;
    Batch   dynamicBatch = BATCH_INITIALIZER;
    string ns = s_nsPrefix + ns_;

    // Create new request.
    msg = AssociationsOfReq_New(_NextMsgID(), BinaryProtocolFlag, ReferencesOfReqTag);

    // Extract arguments.
    msg->nameSpace = Batch_StrZdup(msg->base.batch, ns.c_str());

    /* create dynamic instance */
    /* create dynamic instance */
    dynamicInstance = _ReferenceStringToInstance( &dynamicBatch, ref, 0 );

    UT_ASSERT(dynamicInstance);

    if (trace)
        MI_Instance_Print(dynamicInstance, stdout, 0);

    /* pack instance */
    r = InstanceToBatch(dynamicInstance, NULL, NULL, msg->base.batch, 
            &msg->packedInstancePtr, &msg->packedInstanceSize);

    UT_ASSERT(MI_RESULT_OK == r);

    // optional params
    if (ac)
        msg->assocClass = Batch_StrZdup(msg->base.batch, ac);

    if (role)
        msg->role = Batch_StrZdup(msg->base.batch, role);

    r = Protocol_Send(s_protocol, &msg->base);

    UT_ASSERT(MI_RESULT_OK == r);

    AssociationsOfReq_Release(msg);
    Batch_Destroy(&dynamicBatch);


    // process send/recv loop
    // run loop with 20 ms increment until result received or 20 sec elapsed
    for (int i = 0; i < 1000 && s_results.empty(); i++)
        Protocol_Run(s_protocol, 20000);
}

STATIC void TestGetInstanceSmallNumber()
{
    // omicli gi test/cpp X_SmallNumber.Number=1093
    //instance of X_SmallNumber
    //{
    //    Number=1093
    //    SpelledNumber=one thousand ninety three
    //}
    _CallGetInstance("test/cpp", "X_SmallNumber.Number=1093");

    // validate response
    UT_ASSERT_EQUAL(s_results.size(), 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Number"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT64);
    UT_ASSERT(value.uint64 == 1093);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("SpelledNumber"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_STRING);
    UT_ASSERT(value.string == ut::String(ZT("one thousand ninety three")));
    UT_ASSERT(!(flags & MI_FLAG_NULL));
}

STATIC void TestGetInstanceHugeNumberWithEmbeddedInstance()
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

    _CallGetInstance("test/cpp", "X_HugeNumber.Number=1000000");

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Value value, value_instance;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Number"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT64);
    UT_ASSERT(value.uint64 == 1000000);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Magnitude"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT32);
    UT_ASSERT(value.uint32 == 6);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    {   // embedded-instance: MagnitudeObj
        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("MagnitudeObj"), &value_instance, &type, &flags, 0));
        UT_ASSERT(type == MI_INSTANCE);
        UT_ASSERT(value_instance.instance != NULL);
        UT_ASSERT(!(flags & MI_FLAG_NULL));

        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instance, ZT("Number"), &value, &type, &flags, 0));
        UT_ASSERT(type == MI_UINT64);
        UT_ASSERT(value.uint64 == 6);
        UT_ASSERT(!(flags & MI_FLAG_NULL));

        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instance, ZT("SpelledNumber"), &value, &type, &flags, 0));
        UT_ASSERT(type == MI_STRING);
        UT_ASSERT(value.string == ut::String(ZT("six")));
        UT_ASSERT(!(flags & MI_FLAG_NULL));
    }

    {   // embedded-instance[]: Numbers123
        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Numbers123"), &value_instance, &type, &flags, 0));
        UT_ASSERT(type == MI_INSTANCEA);
        UT_ASSERT(value_instance.instancea.size == 3);
        UT_ASSERT(!(flags & MI_FLAG_NULL));

        for ( int num = 0; num < 3; num++ )
        {
            UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[num], ZT("Number"), &value, &type, &flags, 0));
            UT_ASSERT(type == MI_UINT64);
            UT_ASSERT(value.uint64 == (MI_Uint64)(1 + num));
            UT_ASSERT(!(flags & MI_FLAG_NULL));
        }

        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[0], ZT("SpelledNumber"), &value, &type, &flags, 0));
        UT_ASSERT(type == MI_STRING);
        UT_ASSERT(value.string == ut::String(ZT("one")));
        UT_ASSERT(!(flags & MI_FLAG_NULL));
    }

    {   // embedded-object Numbers0 - expecting X_Halves there
        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Number0"), &value_instance, &type, &flags, 0));
        UT_ASSERT(type == MI_INSTANCE);
        UT_ASSERT(value_instance.instance != NULL);
        UT_ASSERT(!(flags & MI_FLAG_NULL));

        MI_ConstString cn = 0;
        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(value_instance.instance, &cn));
        UT_ASSERT(cn == ut::String(ZT("X_Halves")));
        

        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instance, ZT("number"), &value, &type, &flags, 0));
        UT_ASSERT(type == MI_REFERENCE);
        UT_ASSERT(value.instance != NULL);
        UT_ASSERT(!(flags & MI_FLAG_NULL));

        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instance, ZT("half"), &value, &type, &flags, 0));
        UT_ASSERT(type == MI_REFERENCE);
        UT_ASSERT(value.instance != NULL);
        UT_ASSERT(!(flags & MI_FLAG_NULL));
    }

    {   // embedded-objects[]: TwoTestObjects
        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("TwoTestObjects"), &value_instance, &type, &flags, 0));
        UT_ASSERT(type == MI_INSTANCEA);
        UT_ASSERT(value_instance.instancea.size == 2);
        UT_ASSERT(!(flags & MI_FLAG_NULL));

        for ( int num = 0; num < 2; num++ )
        {
            MI_ConstString cn = 0;
            UT_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(value_instance.instancea.data[num], &cn));

            if (cn == ut::String(ZT("X_TestObject")))
            {
                UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[num], ZT("id"), &value, &type, &flags, 0));
                UT_ASSERT(type == MI_UINT64);
                UT_ASSERT(value.uint64 == 17);
                UT_ASSERT(!(flags & MI_FLAG_NULL));
            }
            else if (cn == ut::String(ZT("X_Profile")))
            {
                UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[num], ZT("Registeredname"), &value, &type, &flags, 0));
                UT_ASSERT(type == MI_STRING);
                UT_ASSERT(value.string == ut::String(ZT("embedded object")));
                UT_ASSERT(!(flags & MI_FLAG_NULL));
            }
            else
            {
                UT_ASSERT_FAILED_MSG( (string("unexcpected class name ") + ut::StrToChar(cn)).c_str() );
            }
        }
    }

}

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

    _CallGetInstance(ns, "TestEmbeddedOperations.Key=1");

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Value value, value_instance;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("key"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT32);
    UT_ASSERT(value.uint32 == 1);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    {   // embedded-instance: person
        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("person"), &value_instance, &type, &flags, 0));
        UT_ASSERT(type == MI_INSTANCE);
        UT_ASSERT(value_instance.instance != NULL);
        UT_ASSERT(!(flags & MI_FLAG_NULL));

        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instance, ZT("Last"), &value, &type, &flags, 0));
        UT_ASSERT(type == MI_STRING);
        UT_ASSERT(value.string == ut::String(ZT("Smith")));
        UT_ASSERT(!(flags & MI_FLAG_NULL));

        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instance, ZT("First"), &value, &type, &flags, 0));
        UT_ASSERT(type == MI_STRING);
        UT_ASSERT(value.string == ut::String(ZT("John")));
        UT_ASSERT(!(flags & MI_FLAG_NULL));
    }

    {   // embedded-instance[]: threePersons
        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("threePersons"), &value_instance, &type, &flags, 0));
        UT_ASSERT(type == MI_INSTANCEA);
        UT_ASSERT(value_instance.instancea.size == 3);
        UT_ASSERT(!(flags & MI_FLAG_NULL));

        for ( int num = 0; num < 3; num++ )
        {
            UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[num], ZT("key"), &value, &type, &flags, 0));
            UT_ASSERT(type == MI_UINT32);
            UT_ASSERT(value.uint32 == (MI_Uint64)(7 + num));
            UT_ASSERT(!(flags & MI_FLAG_NULL));
        }

        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[0], ZT("First"), &value, &type, &flags, 0));
        UT_ASSERT(type == MI_STRING);
        UT_ASSERT(value.string == ut::String(ZT("John")));
        UT_ASSERT(!(flags & MI_FLAG_NULL));
        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[1], ZT("First"), &value, &type, &flags, 0));
        UT_ASSERT(type == MI_STRING);
        UT_ASSERT(value.string == ut::String(ZT("Bill")));
        UT_ASSERT(!(flags & MI_FLAG_NULL));
        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[2], ZT("First"), &value, &type, &flags, 0));
        UT_ASSERT(type == MI_STRING);
        UT_ASSERT(value.string == ut::String(ZT("Ben")));
        UT_ASSERT(!(flags & MI_FLAG_NULL));
    }
}

STATIC void TestGetInstancePersonWithEmbeddedInstance_c()
{
    _TestGetInstancePersonWithEmbeddedInstance("test/c");
}

STATIC void TestGetInstancePersonWithEmbeddedInstance_cpp()
{
    _TestGetInstancePersonWithEmbeddedInstance("test/cpp");
}

STATIC void TestGetInstanceSmallNumberNotFound()
{
    //omicli gi test/cpp X_SmallNumber.Number=10001
    //PostResultMsg
    //{
    //    tag=4
    //    msgID=10000
    //    clientID=12128856
    //    result=7 [NOT_FOUND]
    //    request=NULL
    //}
    _CallGetInstance("test/cpp", "X_SmallNumber.Number=10001");

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_NOT_FOUND);

    UT_ASSERT(s_instances.size() == 0);
}

STATIC void TestGetInstanceInvalidNameSpace()
{
    //omicli gi non/exisiting/namespace X_SmallNumber.Number=11
    //PostResultMsg
    //{
    //    tag=4
    //    msgID=10000
    //    clientID=12128856
    //    result=7 [INVALID_NAMESPACE]
    //    request=NULL
    //}
    _CallGetInstance("non/exisiting/namespace", "X_SmallNumber.Number=11");

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_INVALID_NAMESPACE);

    UT_ASSERT(s_instances.size() == 0);
}

STATIC void TestEnumerateHugeNumber()
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

    _CallEnumerate("test/cpp", "X_HugeNumber", MI_FALSE);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == 2);
    if (s_instances.size() < 2) return;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Number"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT64);
    UT_ASSERT(value.uint64 == 1000000 || value.uint64 == 1000000000);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Magnitude"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT32);
    UT_ASSERT(value.uint32 == 6 || value.uint32 == 9);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[1]->instance, ZT("Number"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT64);
    UT_ASSERT(value.uint64 == 1000000 || value.uint64 == 1000000000);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[1]->instance, ZT("Magnitude"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT32);
    UT_ASSERT(value.uint32 == 6 || value.uint32 == 9);
    UT_ASSERT(!(flags & MI_FLAG_NULL));
}

STATIC void TestEnumerateX_Number1000001()
{
    //omicli ei test/cpp X_Number1000001

    _CallEnumerate("test/cpp", "X_Number1000001", MI_FALSE);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT_EQUAL(s_instances.size(), 1);

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Number"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT64);
    UT_ASSERT(value.uint64 == 1000001);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Magnitude"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT32);
    UT_ASSERT(value.uint32 == 6);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Property0"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT32);
    UT_ASSERT(value.uint32 == 9);
    UT_ASSERT(!(flags & MI_FLAG_NULL));
}

STATIC void TestEnumerateNumberShallow_NotFound()
{
    //omicli ei test/cpp X_Number
    //PostResultMsg
    //{
    //    tag=4
    //    msgID=10000
    //    clientID=12194392
    //    result=7 [NOT_FOUND]
    //    request=NULL
    //}

    _CallEnumerate("test/cpp", "X_Number", MI_FALSE);

    // validate response
    UT_ASSERT_EQUAL(s_results.size(), 1);
    UT_ASSERT(s_results[0] == MI_RESULT_NOT_FOUND);

    UT_ASSERT(s_instances.size() == 0);
}

STATIC void TestEnumerateNumberDeep()
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

    _CallEnumerate("test/cpp", "X_Number", MI_TRUE);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    // 2 Huge + 10000 small
    UT_ASSERT_EQUAL(s_instances.size(), 10003);
}

STATIC void TestEnumerateHugeNumberConformsToProfile()
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

    _CallEnumerate("test/cpp", "X_HugeNumberConformsToProfile", MI_TRUE);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == 2);
    if (s_instances.size() < 2) return;

    MI_Value value, value_instance;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Profile"), &value_instance, &type, &flags, 0));
    UT_ASSERT(type == MI_REFERENCE);
    UT_ASSERT(value_instance.instance != NULL);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    {   // verify first instance
        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instance, ZT("instanceID"), &value, &type, &flags, 0));
        UT_ASSERT(type == MI_STRING);
        UT_ASSERT(value.string == ut::String(ZT("number")));
        UT_ASSERT(!(flags & MI_FLAG_NULL));

        MI_Uint32 count = 0;

        // Verify that only one property is returned - key ('InstanceID')
        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElementCount(value_instance.instance, &count));
        UT_ASSERT(count == 1);
    }
}

STATIC void TestEnumerateInvalidClass()
{
    //omicli ei test/cpp NonExisitingClass
    //PostResultMsg
    //{
    //    tag=4
    //    msgID=10000
    //    clientID=10097240
    //    result=7 [NOT_FOUND]
    //    request=NULL
    //}

    _CallEnumerate("test/cpp", "NonExisitingClass", MI_FALSE);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_NOT_FOUND);

    UT_ASSERT(s_instances.size() == 0);
}

STATIC void TestEnumerateFailedToLoadProvider(const char* ns)
{
    _CallGetInstance(ns, "X_FailedAtLoad.id=1");

    // validate response
    UT_ASSERT(s_results.size() == 1);
    // expecting 'failed' result, since load failed
    UT_ASSERT_EQUAL(s_results[0], MI_RESULT_FAILED);

    UT_ASSERT(s_instances.size() == 0);
}

STATIC void TestEnumerateFailedToLoadProvider_c()
{
    TestEnumerateFailedToLoadProvider("test/c");
}

STATIC void TestEnumerateFailedToLoadProvider_cpp()
{
    TestEnumerateFailedToLoadProvider("test/cpp");
}

STATIC void TestInvokeSmallNumberSpellNumber0()
{
    //omicli iv test/cpp X_SmallNumber SpellNumber num=0
    //instance of SpellNumber
    //{
    //    MIReturn=zero
    //    num=NULL
    //}
    _CallInvoke("test/cpp", "X_SmallNumber", "SpellNumber", "num=0");

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("MIReturn"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_STRING);
    UT_ASSERT(value.string == ut::String(ZT("zero")));
    UT_ASSERT(!(flags & MI_FLAG_NULL));
}

STATIC void TestInvokeSmallNumberSpellNumber120394()
{
    //omicli iv test/cpp X_SmallNumber SpellNumber num=120394
    //instance of SpellNumber
    //{
    //    MIReturn=one hundred twenty  thousand three hundred ninety four
    //    num=NULL
    //}

    _CallInvoke("test/cpp", "X_SmallNumber", "SpellNumber", "num=120394");

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("MIReturn"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_STRING);
    UT_ASSERT(value.string == ut::String(ZT("one hundred twenty  thousand three hundred ninety four")));
    UT_ASSERT(!(flags & MI_FLAG_NULL));
}

STATIC void TestInvokeSmallNumberGetFactors_NotFound()
{
    //omicli iv test/cpp X_SmallNumber.Number=11635 GetFactors
    //PostResultMsg
    //{
    //    tag=4
    //    msgID=10000
    //    clientID=10228312
    //    result=7 [NOT_FOUND]
    //    request=NULL
    //}

    _CallInvoke("test/cpp", "X_SmallNumber.Number=11635", "GetFactors", 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_NOT_FOUND);

    UT_ASSERT(s_instances.size() == 0);
}

STATIC void TestInvokeSmallNumberGetFactors_InvalidParameter()
{
    // trying to refer to non-static funciton in 'static' way
    //omicli iv test/cpp X_SmallNumber GetFactors
    //PostResultMsg
    //{
    //    tag=4
    //    msgID=10000
    //    clientID=10752600
    //    result=4 [INVALID_PARAMETER]
    //    request=NULL
    //}

    _CallInvoke("test/cpp", "X_SmallNumber", "GetFactors", 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_INVALID_PARAMETER);

    UT_ASSERT(s_instances.size() == 0);
}

STATIC void TestInvokeSmallNumber_InvalidFn()
{
    // trying to non-exisiting function
    //omicli iv test/cpp X_SmallNumber FunciotnThatDoesnotExist
    //PostResultMsg
    //{
    //    tag=4
    //    msgID=10000
    //    clientID=10752600
    //    result=4 [FAILED]
    //    request=NULL
    //}

    _CallInvoke("test/cpp", "X_SmallNumber", "FunciotnThatDoesnotExist", 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_FAILED);

    UT_ASSERT(s_instances.size() == 0);
}

STATIC void TestInvokeSmallNumberGetFactors135()
{
    //omicli iv test/cpp X_SmallNumber.Number=135 GetFactors
    //instance of GetFactors
    //{
    //    MIReturn=4
    //    numbers={3, 3, 3, 5}
    //    spelled_numbers={three, three, three, five}
    //}

    _CallInvoke("test/cpp", "X_SmallNumber.Number=135", "GetFactors", 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("MIReturn"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT32);
    UT_ASSERT(value.uint32 == 4);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("numbers"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT64A);
    UT_ASSERT(value.uint64a.size == 4);
    UT_ASSERT(value.uint64a.data[0] == 3);
    UT_ASSERT(value.uint64a.data[1] == 3);
    UT_ASSERT(value.uint64a.data[2] == 3);
    UT_ASSERT(value.uint64a.data[3] == 5);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("spelled_numbers"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_STRINGA);
    UT_ASSERT(value.stringa.size == 4);
    UT_ASSERT(value.stringa.data[0] == ut::String(ZT("three")));
    UT_ASSERT(value.stringa.data[1] == ut::String(ZT("three")));
    UT_ASSERT(value.stringa.data[2] == ut::String(ZT("three")));
    UT_ASSERT(value.stringa.data[3] == ut::String(ZT("five")));
    UT_ASSERT(!(flags & MI_FLAG_NULL));

}

STATIC void TestInvokeHugeNumberSpellMagnitude()
{
    //omicli iv test/cpp X_HugeNumber.Number=1000000 SpellMagnitude
    //instance of SpellMagnitude
    //{
    //    MIReturn=six
    //}

    _CallInvoke("test/cpp", "X_HugeNumber.Number=1000000", "SpellMagnitude", 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("MIReturn"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_STRING);
    UT_ASSERT(value.string == ut::String(ZT("six")));
    UT_ASSERT(!(flags & MI_FLAG_NULL));
}

#if defined(CONFIG_POSIX)
STATIC void TestInvokeTerminate()
{
    //omicli iv test/cpp X_NumberWorld Terminate
    // should terminate agent process

    _CallInvoke("test/cpp", "X_NumberWorld", "Terminate", 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_FAILED);

    UT_ASSERT(s_instances.size() == 0);
}
#endif

STATIC void TestInvokeHugeNumberTestEmbedded()
{
    //omicli iv test/cpp X_HugeNumber TestEmbedded <instance params>
    // current version of omicli does not support these parameters

    _CallInvoke("test/cpp", "X_HugeNumber", "TestEmbedded", 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("MIReturn"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_INSTANCE);
    UT_ASSERT(value.instance != NULL);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    MI_ConstString cn = 0;
    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(value.instance, &cn));
    UT_ASSERT(cn == ut::String(ZT("X_TestObject")));

}

STATIC void _TestInvokePersonTestEmbeddedInstanceReturnKey20100609(const char* ns)
{
    //omicli iv test/cpp TestEmbeddedOperations.Key=1 TestEmbeddedInstanceReturnKey20100609
    //instance of TestEmbeddedInstanceReturnKey20100609
    //{
    //    MIReturn=instance of X_TestEmbeddedInstanceMIReturnObject
    //    {
    //        id=20100609
    //        s=NULL
    //    }
    //}

    _CallInvoke(ns, "TestEmbeddedOperations.Key=1", "TestEmbeddedInstanceReturnKey20100609", 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("MIReturn"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_INSTANCE);
    UT_ASSERT(value.instance != NULL);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    MI_ConstString cn = 0;
    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(value.instance, &cn));
    UT_ASSERT(cn == ut::String(ZT("X_TestEmbeddedInstanceMIReturnObject")));

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value.instance, ZT("id"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT64);
    UT_ASSERT(value.uint64 == 20100609);
    UT_ASSERT(!(flags & MI_FLAG_NULL));
}

STATIC void TestInvokePersonTestEmbeddedInstanceReturnKey20100609_c()
{
    _TestInvokePersonTestEmbeddedInstanceReturnKey20100609("test/c");
}
STATIC void TestInvokePersonTestEmbeddedInstanceReturnKey20100609_cpp()
{
    _TestInvokePersonTestEmbeddedInstanceReturnKey20100609("test/cpp");
}

STATIC void _TestInvokePersonTestEmbeddedObjectReturnKey20100609(const char* ns)
{
    //omicli iv test/cpp TestEmbeddedOperations.Key=1 TestEmbeddedObjectReturnKey20100609
    //instance of TestEmbeddedObjectReturnKey20100609
    //{
    //    MIReturn=instance of X_TestEmbeddedObjectNotReferenced
    //    {
    //        ObjectID=20100609
    //    }
    //}

    _CallInvoke(ns, "TestEmbeddedOperations.Key=1", "TestEmbeddedObjectReturnKey20100609", 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("MIReturn"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_INSTANCE);
    UT_ASSERT(value.instance != NULL);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    MI_ConstString cn = 0;
    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(value.instance, &cn));
    UT_ASSERT(cn == ut::String(ZT("X_TestEmbeddedObjectNotReferenced")));

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value.instance, ZT("ObjectId"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT64);
    UT_ASSERT(value.uint64 == 20100609);
    UT_ASSERT(!(flags & MI_FLAG_NULL));
}


STATIC void TestInvokePersonTestEmbeddedObjectReturnKey20100609_c()
{
    _TestInvokePersonTestEmbeddedObjectReturnKey20100609("test/c");
}

STATIC void TestInvokePersonTestEmbeddedObjectReturnKey20100609_cpp()
{
    _TestInvokePersonTestEmbeddedObjectReturnKey20100609("test/cpp");
}

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

    UT_ASSERT (MI_RESULT_OK == r);

    // objectSingle
    MI_Value value;

    value.instance = _ReferenceStringToInstance(&dynamicBatch, "MSFT_Animal.Key=17", 0);
    UT_ASSERT( value.instance );

    r = MI_Instance_AddElement(dynamicInstanceParams, MI_T("objectSingle"), 
        &value, MI_INSTANCE, MI_FLAG_BORROW);
    UT_ASSERT(r == MI_RESULT_OK);

    MI_Instance* instances[3];

    instances[0] = _ReferenceStringToInstance(&dynamicBatch, "MSFT_Animal.Key=101", 0);
    instances[1] = _ReferenceStringToInstance(&dynamicBatch, "MSFT_Animal.Key=102", 0);
    value.instancea.data = instances;
    value.instancea.size = 2;

    r = MI_Instance_AddElement(dynamicInstanceParams, MI_T("objectsArray"), 
        &value, MI_INSTANCEA, MI_FLAG_BORROW);
    UT_ASSERT(r == MI_RESULT_OK);

    instances[0] = _ReferenceStringToInstance(&dynamicBatch, "X_TestObject.id=101", 0);
    instances[1] = _ReferenceStringToInstance(&dynamicBatch, "X_TestObject.id=102", 0);
    instances[2] = _ReferenceStringToInstance(&dynamicBatch, "X_TestObject.id=103", 0);
    value.instancea.data = instances;
    value.instancea.size = 3;

    r = MI_Instance_AddElement(dynamicInstanceParams, 
        MI_T("testObjectsArray"), &value, MI_INSTANCEA, MI_FLAG_BORROW);
    UT_ASSERT(r == MI_RESULT_OK);

    if (trace)
        MI_Instance_Print(dynamicInstanceParams, stdout, 0);

    _CallInvoke(ns, "TestEmbeddedOperations.Key=1", "TestEmbedded", 0, dynamicInstanceParams);

    Batch_Destroy(&dynamicBatch);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("MIReturn"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_INSTANCE);
    UT_ASSERT(value.instance != NULL);
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    MI_ConstString cn = 0;
    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(value.instance, &cn));
    UT_ASSERT(cn == ut::String(ZT("X_TestObject")));

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value.instance, ZT("id"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT64);

    UT_ASSERT(value.uint64 == (101+102+103));   /* expecting sum of keys */
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    {
        MI_Value value_instance;

        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("testObjectsArray"), &value_instance, &type, &flags, 0));
        UT_ASSERT(type == MI_INSTANCEA);
        UT_ASSERT(value_instance.instancea.size == 2);
        UT_ASSERT(!(flags & MI_FLAG_NULL));

        /* expecting last two elements */
        for ( int num = 0; num < 2; num++ )
        {
            UT_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(value_instance.instancea.data[num], &cn));
            UT_ASSERT(cn == ut::String(ZT("X_TestObject")));

            UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[num], ZT("id"), &value, &type, &flags, 0));
            UT_ASSERT(type == MI_UINT64);
            UT_ASSERT(value.uint64 == (MI_Uint64)(102 + num));
            UT_ASSERT(!(flags & MI_FLAG_NULL));
        }
    }
    {
        MI_Value value_instance;

        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("objectsArray"), &value_instance, &type, &flags, 0));
        UT_ASSERT(type == MI_INSTANCEA);
        UT_ASSERT(value_instance.instancea.size == 2);
        UT_ASSERT(!(flags & MI_FLAG_NULL));

        /* expecting last two elements */
        for ( int num = 0; num < 2; num++ )
        {
            UT_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(value_instance.instancea.data[num], &cn));
            UT_ASSERT(cn == ut::String(ZT("MSFT_Animal")));

            UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(value_instance.instancea.data[num], ZT("species"), &value, &type, &flags, 0));
            UT_ASSERT(type == MI_STRING);
            UT_ASSERT(value.string == ut::String(ZT("test")));
            UT_ASSERT(!(flags & MI_FLAG_NULL));
        }
    }

}


STATIC void TestInvokePersonTestEmbeddedParameters_c()
{
    _TestInvokePersonTestEmbeddedParameters("test/c");
}

STATIC void TestInvokePersonTestEmbeddedParameters_cpp()
{
    _TestInvokePersonTestEmbeddedParameters("test/cpp");
}

STATIC void TestAssociatorsFriends()
{
    //omicli a test/cpp MSFT_Person.Key=1  -ac MSFT_Friends -rc MSFT_Base
    //instance of MSFT_Person
    //{
    //    Key=2
    //    Species=NULL
    //    Last=Adams
    //    First=John
    //}

    _CallAssociators("test/cpp", "MSFT_Person.Key=1", "MSFT_Friends", "MSFT_Base", "Left", "Right");

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Last"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_STRING);
    UT_ASSERT(value.string == ut::String(ZT("Adams")));
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("First"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_STRING);
    UT_ASSERT(value.string == ut::String(ZT("John")));
    UT_ASSERT(!(flags & MI_FLAG_NULL));

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("Key"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_UINT32);
    UT_ASSERT(value.uint32 == 2);
    UT_ASSERT(!(flags & MI_FLAG_NULL));
}

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
        UT_ASSERT(MI_RESULT_OK == MI_Instance_GetClassName(s_instances[i]->instance, &cn));

        MI_Value value;
        MI_Type type;
        MI_Uint32 flags = 0;

        ut::String s(cn);
        if ( s == MI_T("X_SmallNumber") )
        {

            UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[i]->instance, ZT("Number"), &value, &type, &flags, 0));
            UT_ASSERT(type == MI_UINT64);
            UT_ASSERT(!(flags & MI_FLAG_NULL));
            if (value.uint64 % 2 == 0)
            {
                UT_ASSERT( (expected & (enumExpectSmallEven|enumExpectSmallNumber350|enumExpectSmallNumber1400|enumExpectSmallNumber0) ) != 0 );
                even.insert(value.uint64);
            }
            else
            {
                UT_ASSERT( (expected & (enumExpectSmallOdd) ) != 0 );
                odd.insert(value.uint64);
            }

            // check that SpelledNumber is not empty
            UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[i]->instance, ZT("SpelledNumber"), &value, &type, &flags, 0));
            UT_ASSERT(type == MI_STRING);
            UT_ASSERT(!(flags & MI_FLAG_NULL));
            UT_ASSERT( !ut::String(value.string).empty());

            // namespace
            MI_ConstString ns = 0;
            UT_ASSERT(MI_RESULT_OK == MI_Instance_GetNameSpace(s_instances[i]->instance, &ns));

            UT_ASSERT( ns != 0 );
            UT_ASSERT(ns == ut::String(ZT("test/cpp")));
        }
        else if ( s == MI_T("X_HugeNumber") )
        {
            UT_ASSERT( (expected & enumExpectHuge ) != 0 );

            UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[i]->instance, ZT("Number"), &value, &type, &flags, 0));
            UT_ASSERT(type == MI_UINT64);
            UT_ASSERT(!(flags & MI_FLAG_NULL));

            huge.insert(value.uint64);
        }
        else if ( s == MI_T("X_NumberWorld") )
        {
            UT_ASSERT( (expected & enumExpectWorld ) != 0 );

            UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[i]->instance, ZT("Name"), &value, &type, &flags, 0));
            UT_ASSERT(type == MI_STRING);
            UT_ASSERT(!(flags & MI_FLAG_NULL));
            UT_ASSERT(value.string == ut::String(ZT("theWorld")));
            gotWorld = true;

            // namespace
            MI_ConstString ns = 0;
            UT_ASSERT(MI_RESULT_OK == MI_Instance_GetNameSpace(s_instances[i]->instance, &ns));

            UT_ASSERT( ns != 0 );
            UT_ASSERT(ns == ut::String(ZT("test/cpp")));
        }
        else if ( s == MI_T("X_Profile") )
        {
            UT_ASSERT( (expected & (enumExpectProfileWorld|enumExpectProfileHuge) ) != 0 );

            UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[i]->instance, ZT("InstanceID"), &value, &type, &flags, 0));
            UT_ASSERT(type == MI_STRING);
            UT_ASSERT(!(flags & MI_FLAG_NULL));

            if (value.string == ut::String(ZT("world")))
            {
                UT_ASSERT( (expected & (enumExpectProfileWorld) ) != 0 );
                gotProfileWorld = true;
            }
            else if (value.string == ut::String(ZT("number")))
            {
                UT_ASSERT( (expected & (enumExpectProfileHuge) ) != 0 );
                gotProfileNumber = true;
            }
            else
                UT_ASSERT_FAILED_MSG( (string("unexpected profile ") + ut::StrToChar(value.string)).c_str() );

            // namespace
            MI_ConstString ns = 0;
            UT_ASSERT(MI_RESULT_OK == MI_Instance_GetNameSpace(s_instances[i]->instance, &ns));

            UT_ASSERT( ns != 0 );
            UT_ASSERT(ns == ut::String(ZT("interop")));

        }
        else
        {
            UT_ASSERT_FAILED_MSG( (string("unexpected class ") + ut::StrToChar(s)).c_str() );
        }
    }

    // validate results
    if (expected & enumExpectHuge)
    {
        UT_ASSERT(huge.size() == 2);
        UT_ASSERT(huge.find(1000000) != huge.end());
        UT_ASSERT(huge.find(1000000000) != huge.end());
    }

    if (expected & enumExpectSmallEven)
    {
        UT_ASSERT(even.size() == 5000);
        for ( int i = 0; i < 10000; i++ )
        {
            if ( i % 2 != 0 )
                continue;

            UT_ASSERT(even.find(i) != even.end());
        }
    }
    if (expected & enumExpectSmallNumber0)
    {
        UT_ASSERT(even.find(0) != even.end());
    }
    if (expected & enumExpectSmallNumber350)
    {
        UT_ASSERT(even.find(350) != even.end());
    }
    if (expected & enumExpectSmallNumber1400)
    {
        UT_ASSERT(even.find(1400) != even.end());
    }
    if (expected & enumExpectSmallOdd)
    {
        UT_ASSERT(odd.size() == 5000);
        for ( int i = 0; i < 10000; i++ )
        {
            if ( i % 2 == 0 )
                continue;

            UT_ASSERT(odd.find(i) != odd.end());
        }
    }

    if (expected & enumExpectProfileWorld)
    {
        UT_ASSERT(gotProfileWorld);
    }
    if (expected & enumExpectProfileHuge)
    {
        UT_ASSERT(gotProfileNumber);
    }
    if (expected & enumExpectWorld)
    {
        UT_ASSERT(gotWorld);
    }
}

STATIC void TestAssociatorsNumProv_AllOfWorld()
{
    // omicli a test/cpp X_numberWorld.Name=theWorld
    // ... gazillion of results
    _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", 0, 0, 0, 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (
        10000 /* small numbers */ + 2 /* huge numbers */ + 1 /* profile */
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectProfileWorld | enumExpectSmallEven | enumExpectSmallOdd | enumExpectHuge);
}

STATIC void TestAssociatorsNumProv_ProfileOfWorldByAssocClass()
{
    //omicli a test/cpp X_numberWorld.Name=theWorld -ac X_ElementConformsToProfile
    //instance of X_Profile
    //{
    //    InstanceID=world
    //    RegisteredName=World
    //}

   _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", "X_ElementConformsToProfile", 0, 0, 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (
        1 /* profile */
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectProfileWorld);
}

STATIC void TestAssociatorsNumProv_ProfileOfWorldByResultClass()
{
    //omicli a test/cpp X_numberWorld.Name=theWorld -rc X_Profile
    //instance of X_Profile
    //{
    //    InstanceID=world
    //    RegisteredName=World
    //}

   _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", 0, "X_Profile", 0, 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (
        1 /* profile */
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectProfileWorld);
}

STATIC void TestAssociatorsNumProv_ProfileOfWorldByRole()
{
    //omicli a test/cpp X_numberWorld.Name=theWorld -role Element
    //instance of X_Profile
    //{
    //    InstanceID=world
    //    RegisteredName=World
    //}

   _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", 0, 0, "Element", 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (
        1 /* profile */
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectProfileWorld);
}

STATIC void TestAssociatorsNumProv_ProfileOfWorldByResultRole()
{
    //omicli a test/cpp X_numberWorld.Name=theWorld -rrole Profile
    //instance of X_Profile
    //{
    //    InstanceID=world
    //    RegisteredName=World
    //}

   _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", 0, 0, 0, "Profile");

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (
        1 /* profile */
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectProfileWorld);
}

STATIC void TestAssociatorsNumProv_AllNumbersOfWorld()
{
    // omicli a test/cpp X_numberWorld.Name=theWorld -ac x_AllNumbers
    // ... gazillion of results
    _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", "x_aLLnUMBERS", 0, 0, 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (
        10000 /* small numbers */ + 2 /* huge numbers */ 
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectSmallEven | enumExpectSmallOdd | enumExpectHuge);
}
STATIC void TestAssociatorsNumProv_AllHugeNumbersOfWorld()
{
    // omicli a test/cpp X_numberWorld.Name=theWorld -ac x_HugeNumbers
    // ... gazillion of results
    _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", "x_HugeNumbers", 0, 0, 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (
        2 /* huge numbers */ 
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectHuge);
}

STATIC void TestAssociatorsNumProv_AllEvenNumbersOfWorld()
{
    // omicli a test/cpp X_numberWorld.Name=theWorld -ac X_EvenSmallNumbers
    // ... gazillion of results
    _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", "X_EvenSmallNumbers", 0, 0, 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (
        5000 /* even small numbers */ 
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectSmallEven);
}


STATIC void TestAssociatorsNumProv_AllOddNumbersOfWorld()
{
    // omicli a test/cpp X_numberWorld.Name=theWorld -ac X_OddSmallNumbers
    // ... gazillion of results
    _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", "X_OddSmallNumbers", 0, 0, 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (
        5000 /* small numbers */ 
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectSmallOdd);
}

STATIC void TestAssociatorsNumProv_AllProfile()
{
    // omicli a test/cpp X_Profile.InstanceID=number 
    

    _CallAssociators("test/cpp", "X_Profile.InstanceID=number", 0, 0, 0, 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (
        2 /* huge numbers */ 
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectHuge);
}

STATIC void TestAssociatorsNumProv_AllOfSmallNumber()
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
    

    _CallAssociators("test/cpp", "X_smallNumber.Number=700", 0, 0, 0, 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (
        3 
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectWorld | enumExpectSmallNumber1400 | enumExpectSmallNumber350 );
}

STATIC void TestAssociatorsNumProv_AllOfSmallNumberByRoleNumber()
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

    _CallAssociators("test/cpp", "X_smallNumber.Number=700", 0, 0, "number", 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (
        2 
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectWorld | enumExpectSmallNumber350 );
}

STATIC void TestAssociatorsNumProv_AllOfSmallNumberByRoleHalf()
{
    //omicli a test/cpp X_smallNumber.Number=700  -role half
    //instance of X_SmallNumber
    //{
    //    Description=NULL
    //    Number=1400
    //    SpelledNumber=one thousand four hundred
    //}

    _CallAssociators("test/cpp", "X_smallNumber.Number=700", 0, 0, "half", 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (
        1
        ));

    // verify instances
    _ValidateNumberProvInstances(enumExpectSmallNumber1400 );
}

STATIC void TestAssociatorsNumProv_AllOfSmallNumberByAssocClassHalves()
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

    _CallAssociators("test/cpp", "X_smallNumber.Number=700", "x_halves", 0, 0, 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (
        2
        ));

    // verify instances
    _ValidateNumberProvInstances( enumExpectSmallNumber350 | enumExpectSmallNumber1400 );
}

STATIC void TestAssociatorsNumProv_DoubleZeroInstancesOfSmallNumberByAssocClassHalves()
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


    _CallAssociators("test/cpp", "X_smallNumber.Number=0", "x_halves", 0, 0, 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (
        2
        ));

    // verify instances
    _ValidateNumberProvInstances( enumExpectSmallNumber0 );
}

STATIC void TestAssociatorsNumProv_AllOfSmallNumberByAllFilters()
{
    //omicli a test/cpp X_smallNumber.Number=0 -ac x_halves -rc x_number -role half -rrole number
    //instance of X_SmallNumber
    //{
    //    Description=NULL
    //    Number=0
    //    SpelledNumber=zero
    //}

    _CallAssociators("test/cpp", "X_smallNumber.Number=0", "x_halves", "x_number", "half", "number");

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (
        1
        ));

    // verify instances
    _ValidateNumberProvInstances( enumExpectSmallNumber0 );
}

STATIC void TestAssociatorsNumProv_ProfileOfWorldByRoleRRole()
{
    //omicli a test/cpp X_numberWorld.Name=theWorld -ac X_AllNumbers -rc X_Number -role Number -rrole Number
    // 
    _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", "X_AllNumbers", "X_Number", "Number", "Number");

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (0));
}


STATIC void TestAssociatorsNumProv_ProfileOfWorldByInvalidAssocClass()
{
    // omicli a test/cpp X_numberWorld.Name=theWorld -ac x_halves
    // 
    // this assoc class is not related to X_NumberWorld class
    _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", "x_halves", 0, 0, 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_NOT_FOUND);

    UT_ASSERT(s_instances.size() == (0));
}

STATIC void TestAssociatorsNumProv_ProfileOfWorldByInvalidResultClass()
{
    // omicli a test/cpp X_numberWorld.Name=theWorld -rc SomeInvalidClass
    // 
    _CallAssociators("test/cpp", "X_numberWorld.Name=theWorld", 0, "SomeInvalidClass", 0, 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_INVALID_CLASS);

    UT_ASSERT(s_instances.size() == (0));
}

STATIC void TestAssociatorsNumProv_InvalidNameSpace()
{
    // omicli a invalid/namespace X_numberWorld.Name=theWorld
    // 
    _CallAssociators("invalid/namespace", "X_numberWorld.Name=theWorld", 0, 0, 0, 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_INVALID_NAMESPACE);

    UT_ASSERT(s_instances.size() == (0));
}

STATIC void TestAssociatorsNumProv_NoInstance()
{
    // omicli a test/cpp X_numberWorld.UnknownProp=theWorld
    // 
    _CallAssociators("test/cpp", "X_numberWorld.UnknownProp=theWorld", 0, 0, 0, 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);

    /*if (s_results[0] != MI_RESULT_NOT_FOUND)
        cout << "res " << s_results[0] << endl;*/

    //UT_ASSERT(s_results[0] == MI_RESULT_NOT_FOUND);
    UT_ASSERT(s_results[0] != MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (0));
}

STATIC void TestReferencesNumProv_ProfileByAssocClass()
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
  
    _CallReferences("test/cpp", "X_Profile.InstanceID=world", "X_NumberWorldConformsToProfile", 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT(s_results[0] == MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == (
        1
        ));

    // verify instances
    //_ValidateNumberProvInstances( enumExpectSmallNumber0 );
    // ATTN!: Add instance verification, once MI_InstanceCompare is ready
}

STATIC void TestNamespaceParameterUsingInvoke()
{

    _CallInvoke("test/cpp", "x_numberWorld", "ReturnNamespace", 0);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT_EQUAL(s_results[0], MI_RESULT_OK);

    UT_ASSERT(s_instances.size() == 1);
    if (s_instances.size() == 0) return;

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT(MI_RESULT_OK == MI_Instance_GetElement(s_instances[0]->instance, ZT("MIReturn"), &value, &type, &flags, 0));
    UT_ASSERT(type == MI_STRING);
    UT_ASSERT(!(flags & MI_FLAG_NULL));
    UT_ASSERT(value.string == ut::String(ZT("test/cpp")) || value.string == ut::String(ZT("oop/requestor/test/cpp")));
}

STATIC void TestNamespaceParameterUsingEnumerate()
{
    _CallEnumerate("test/cpp", "x_numberWorld", MI_FALSE);

    // validate response
    UT_ASSERT(s_results.size() == 1);
    UT_ASSERT_EQUAL(s_results[0], MI_RESULT_OK);

    UT_ASSERT_EQUAL(s_instances.size(), 1);

    MI_Value value;
    MI_Type type;
    MI_Uint32 flags = 0;

    UT_ASSERT_EQUAL(MI_RESULT_OK, MI_Instance_GetElement(s_instances[0]->instance, ZT("ns"), &value, &type, &flags, 0));
    UT_ASSERT_EQUAL(type, MI_STRING);
    UT_ASSERT(!(flags & MI_FLAG_NULL));
    UT_ASSERT(value.string == ut::String(ZT("test/cpp")) || value.string == ut::String(ZT("oop/requestor/test/cpp")));
}

STATIC void _RunAllTestsWithNSPrefix(const char* nsPrefix)
{
    s_nsPrefix = nsPrefix;

    // get
    UT_TEST(TestGetInstanceSmallNumber);
    UT_TEST(TestGetInstanceSmallNumberNotFound);
    UT_TEST(TestGetInstanceInvalidNameSpace);
    UT_TEST(TestGetInstanceHugeNumberWithEmbeddedInstance);
    UT_TEST(TestGetInstancePersonWithEmbeddedInstance_c);
    UT_TEST(TestGetInstancePersonWithEmbeddedInstance_cpp);


    // enumerate
    UT_TEST(TestEnumerateHugeNumber);
    UT_TEST(TestEnumerateNumberShallow_NotFound);
    UT_TEST(TestEnumerateNumberDeep);       // note! provider has two modes of enumeration to excersize both
    UT_TEST(TestEnumerateNumberDeep);       // sync and async APIs, so we have to call test twice
    UT_TEST(TestEnumerateHugeNumberConformsToProfile);       // enumerate assoc class
    UT_TEST(TestEnumerateInvalidClass);
    UT_TEST(TestEnumerateFailedToLoadProvider_c);
    UT_TEST(TestEnumerateFailedToLoadProvider_cpp);
    UT_TEST(TestEnumerateX_Number1000001);

    // invoke
    UT_TEST(TestInvokeSmallNumberSpellNumber0);

    UT_TEST(TestInvokeSmallNumberSpellNumber120394);
    UT_TEST(TestInvokeSmallNumberGetFactors_NotFound);
    UT_TEST(TestInvokeSmallNumberGetFactors_InvalidParameter);
    UT_TEST(TestInvokeSmallNumber_InvalidFn);
    UT_TEST(TestInvokeSmallNumberGetFactors135);
    UT_TEST(TestInvokeHugeNumberSpellMagnitude);
    UT_TEST(TestInvokeHugeNumberTestEmbedded);
    UT_TEST(TestInvokePersonTestEmbeddedInstanceReturnKey20100609_c);
    UT_TEST(TestInvokePersonTestEmbeddedInstanceReturnKey20100609_cpp);
    UT_TEST(TestInvokePersonTestEmbeddedObjectReturnKey20100609_c);
    UT_TEST(TestInvokePersonTestEmbeddedObjectReturnKey20100609_cpp);
    UT_TEST(TestInvokePersonTestEmbeddedParameters_c);
    UT_TEST(TestInvokePersonTestEmbeddedParameters_cpp);


    // associators
    // happy pass (return some instances)
    UT_TEST(TestAssociatorsFriends);
    UT_TEST(TestAssociatorsNumProv_AllOfWorld);
    UT_TEST(TestAssociatorsNumProv_ProfileOfWorldByAssocClass);
    UT_TEST(TestAssociatorsNumProv_ProfileOfWorldByResultClass);
    UT_TEST(TestAssociatorsNumProv_ProfileOfWorldByRole);
    UT_TEST(TestAssociatorsNumProv_ProfileOfWorldByResultRole);

    UT_TEST(TestAssociatorsNumProv_AllNumbersOfWorld);
    UT_TEST(TestAssociatorsNumProv_AllHugeNumbersOfWorld);
    UT_TEST(TestAssociatorsNumProv_AllEvenNumbersOfWorld);
    UT_TEST(TestAssociatorsNumProv_AllOddNumbersOfWorld);

    UT_TEST(TestAssociatorsNumProv_AllProfile);
    UT_TEST(TestAssociatorsNumProv_AllOfSmallNumber);
    UT_TEST(TestAssociatorsNumProv_AllOfSmallNumberByRoleNumber);
    UT_TEST(TestAssociatorsNumProv_AllOfSmallNumberByRoleHalf);
    UT_TEST(TestAssociatorsNumProv_AllOfSmallNumberByAssocClassHalves);
    UT_TEST(TestAssociatorsNumProv_DoubleZeroInstancesOfSmallNumberByAssocClassHalves);
    UT_TEST(TestAssociatorsNumProv_AllOfSmallNumberByAllFilters);

    // empty pass (return ok/0 instances)
    UT_TEST(TestAssociatorsNumProv_ProfileOfWorldByRoleRRole);

    // negative (return error back)
    UT_TEST(TestAssociatorsNumProv_ProfileOfWorldByInvalidAssocClass);
    UT_TEST(TestAssociatorsNumProv_ProfileOfWorldByInvalidResultClass);
    UT_TEST(TestAssociatorsNumProv_InvalidNameSpace);
    UT_TEST(TestAssociatorsNumProv_NoInstance);

    // references
    UT_TEST(TestReferencesNumProv_ProfileByAssocClass);


    // bug 26591
    UT_TEST(TestNamespaceParameterUsingInvoke);
    UT_TEST(TestNamespaceParameterUsingEnumerate);
}

static void TestNumberProvider()
{
    // run tests with no prefix, so providers are hosted 'in-proc'
    _RunAllTestsWithNSPrefix("");

    // run tests with 'requestor' prefix, so providers are hosted 'as-requestor' in separate process
    if (!NitsIsActivated())
        _RunAllTestsWithNSPrefix("oop/requestor/");

#if defined(CONFIG_POSIX)
    /* Special test for oop:  terminate running agent and verify that server returns error 'FAILED' for this request
        and can restart agent for next request */
    s_nsPrefix = "oop/requestor/";
    UT_TEST(TestInvokeTerminate);
    UT_TEST(TestGetInstanceSmallNumber);
#endif

    // WSMAN test (it also needs server running);
    // to speed up test execution, server started only once
    // and all tests that require server are called from this file
    WSMAN_Tests_With_Server();
}

UT_ENTRY_POINT(TestNumberProvider);
