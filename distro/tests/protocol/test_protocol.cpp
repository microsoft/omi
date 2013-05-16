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
#include <cstdlib>
#include <ut/ut.h>
#include <protocol/protocol.h>
#include <base/time.h>
#include <base/base.h>
#include <base/paths.h>
#include <tests/base/MSFT_AllTypes.h>

#if defined(CONFIG_POSIX)
# include <unistd.h>
# include <errno.h>
# include <sys/socket.h>
# include <netinet/tcp.h>
# include <netinet/in.h>
# include <sys/time.h>
# include <sys/types.h>
# include <netdb.h>
# include <fcntl.h>
# include <arpa/inet.h>
# include <signal.h>
#endif

#if defined(_MSC_VER)
# define PORTSTR "21718"
#else
# define PORTSTR GetPath(ID_SOCKETFILE)
#endif

using namespace std;
using namespace mi;

static vector<ProtocolEvent> s_events;

#if defined(_MSC_VER)
#undef BEGIN_EXTERNC
#undef END_EXTERNC
#define BEGIN_EXTERNC
#define END_EXTERNC
#endif

static void setUp()
{
    s_events.clear();
}

static void cleanup()
{
}

BEGIN_EXTERNC
static MI_Boolean _ServerCallback(
    Protocol* protocol,
    Message* message,
    void* data)
{
    // memorize request
    Message** msgOut = (Message**)data;
    UT_ASSERT( *msgOut == NULL ); // expecting only one message

    *msgOut = message;
    Message_AddRef(*msgOut);

    // send response
    NoOpReq* req = (NoOpReq*)message;
    NoOpRsp* rsp;

    /* Send NoOp response back */
    rsp = NoOpRsp_New(req->base.msgID);
    rsp->base.clientID = req->base.clientID;
    Protocol_Send(protocol, &rsp->base);
    NoOpRsp_Release(rsp);

    return MI_TRUE;
}
END_EXTERNC

BEGIN_EXTERNC
static MI_Boolean _ClientCallback(
    Protocol* protocol,
    Message* message,
    void* data)
{
    protocol = protocol;

    Message** msgOut = (Message**)data;

    UT_ASSERT( *msgOut == NULL ); // expecting only one message

    *msgOut = message;
    Message_AddRef( *msgOut );

    return MI_TRUE;
}
END_EXTERNC

static void TestHappyPass()
{
    /* send noop-rqt and recv noop-rsp */
    // create 2 protocols - listener and connector
    Protocol *listener, *connector;
    Message* recvMessageClient = NULL; // response from server
    Message* recvMessageServer = NULL; // req received by server

    UT_ASSERT( MI_RESULT_OK == Protocol_New_Listener(
        &listener, 0, PORTSTR, _ServerCallback, (void*)&recvMessageServer) );

    UT_ASSERT(MI_RESULT_OK == Protocol_New_Connector(&connector, 0,
        PORTSTR, _ClientCallback, (void*)&recvMessageClient, 0, 0, "unittest", "unittest"));


    // send noop from client
    NoOpReq* rqt = NoOpReq_New(777);
    Protocol_Send(connector, &rqt->base);
    NoOpReq_Release(rqt);

    for (int attempt = 0; attempt < 12 && !recvMessageClient; attempt++)
    {
        Protocol_Run(connector, 20000);
        Protocol_Run(listener, 20000);
    }

    // check messages
    UT_ASSERT( recvMessageServer );
    UT_ASSERT( recvMessageServer->tag == NoOpReqTag );

    UT_ASSERT( recvMessageClient );
    UT_ASSERT( recvMessageClient->tag == NoOpRspTag );
    UT_ASSERT( recvMessageClient->msgID == 777 );

    // free messages
    Message_Release(recvMessageServer);
    Message_Release(recvMessageClient);

    UT_ASSERT( MI_RESULT_OK == Protocol_Delete(listener) );
    UT_ASSERT( MI_RESULT_OK == Protocol_Delete(connector) );
}

BEGIN_EXTERNC
static void _TransferMessageUsingProtocol(
    Message* msg,
    Message** result,
    bool listenerUsesExternalSelect = false,
    bool connectorUsesExternalSelect = false,
    Sock* socketPair = 0)
{
    Selector internal_selector;
    Selector*   selector = 0;
    Message* recvMessageClient = 0; // response from server; assigned in _ClientCallback

    if (listenerUsesExternalSelect || connectorUsesExternalSelect)
    {
        /* Initialize the network */
        Sock_Start();

        UT_ASSERT(Selector_Init(&internal_selector) == MI_RESULT_OK);
        selector = &internal_selector;
    }

    /* send message to the server and return received message from server's callback */
    // create 2 protocols - listener and connector
    Protocol *listener, *connector;

    if (0 == socketPair)
    {
        UT_ASSERT( MI_RESULT_OK == Protocol_New_Listener(
            &listener, listenerUsesExternalSelect ? selector : 0, PORTSTR, _ServerCallback, (void*)result) );

        UT_ASSERT(MI_RESULT_OK == Protocol_New_Connector(&connector,
            connectorUsesExternalSelect ? selector : 0, PORTSTR,
            _ClientCallback, (void*)&recvMessageClient, 0, 0, "unittest", "unittest"));
    }
    else
    {
        UT_ASSERT( MI_RESULT_OK == Protocol_New_From_Socket(
            &listener,
            listenerUsesExternalSelect ? selector : 0,
            socketPair[0],
            MI_FALSE,
            _ServerCallback, (void*)result,
            0,0) );

        UT_ASSERT(MI_RESULT_OK == Protocol_New_From_Socket(
            &connector,
            connectorUsesExternalSelect ? selector : 0,
            socketPair[1],
            MI_FALSE,
            _ClientCallback, (void*)&recvMessageClient, 0, 0));
    }

    // send noop from client
    Protocol_Send(connector, msg);

    for (int attempt = 0; attempt < 12 && !*result; attempt++)
    {
        Protocol_Run(connector, 20000);
        Protocol_Run(listener, 20000);
    }

    /* remove all handlers befroe destroying protocols */
    if (selector)
        Selector_RemoveAllHandlers(selector);

    UT_ASSERT( MI_RESULT_OK == Protocol_Delete(listener) );
    UT_ASSERT( MI_RESULT_OK == Protocol_Delete(connector) );

    if (selector)
    {
        Selector_Destroy(selector);

        /* Shutdown the network */
        Sock_Stop();
    }

    if (recvMessageClient)
        Message_Release(recvMessageClient);

}
END_EXTERNC

static void TestTransferingEnumerateInstanceRequest()
{
    EnumerateInstancesReq* msg = EnumerateInstancesReq_New( 1444, BinaryProtocolFlag );
    Message* result = 0;

    msg->deepInheritance = MI_TRUE;
    msg->nameSpace = Batch_StrZdup(msg->base.batch, "name_space");
    msg->className = Batch_StrZdup(msg->base.batch, "class_name");

    _TransferMessageUsingProtocol( &msg->base, &result );

    /* free source message */
    UT_ASSERT(msg->base.refCounter == 1);
    EnumerateInstancesReq_Release(msg);

    /* check received result */
    UT_ASSERT( result );
    UT_ASSERT( result->tag == EnumerateInstancesReqTag );

    {
        EnumerateInstancesReq* rsp = (EnumerateInstancesReq*)result;
        UT_ASSERT( Zcmp(rsp->nameSpace, MI_T("name_space")) == 0 );
        UT_ASSERT( Zcmp(rsp->className, MI_T("class_name")) == 0 );
        UT_ASSERT( rsp->deepInheritance );
    }

    UT_ASSERT(result->refCounter == 1);
    Message_Release(result);
}

static void TestTransferingResult()
{
    PostResultMsg* msg = PostResultMsg_New( 1444 );
    Message* result = 0;

    msg->result = MI_RESULT_NOT_FOUND;

    _TransferMessageUsingProtocol( &msg->base, &result );

    /* free source message */
    UT_ASSERT(msg->base.refCounter == 1);
    PostResultMsg_Release(msg);

    /* check received result */
    UT_ASSERT( result );
    UT_ASSERT( result->tag == PostResultMsgTag );

    {
        PostResultMsg* rsp = (PostResultMsg*)result;
        UT_ASSERT( rsp->result == MI_RESULT_NOT_FOUND);
    }

    UT_ASSERT(result->refCounter == 1);
    Message_Release(result);
}

BEGIN_EXTERNC
static void _DynamicToStatikInstance(
    MI_Instance* dynamicInst,
    Batch* batch,
    MSFT_AllTypes_Class& inst)
{
    MI_Instance* instOut = 0;

    /* Allocate the instance for the provider */
    instOut = (MI_Instance*)Batch_GetClear(batch,
        MSFT_AllTypes_rtti.size);

    /* Convert instance name to provider's format (borrow storage) */
    MI_Result r = Instance_InitConvert(
        instOut,
        &MSFT_AllTypes_rtti,
        dynamicInst,
        MI_FALSE,
        MI_FALSE,
        MI_FALSE,
        batch);

    UT_ASSERT( MI_RESULT_OK == r );

    inst = MSFT_AllTypes_Class((const MSFT_AllTypes *)instOut, false);
}
END_EXTERNC

static void TestTransferingGetInstanceReqt()
{
    GetInstanceReq* msg = GetInstanceReq_New( 1444, BinaryProtocolFlag );
    Message* result = 0;

    msg->nameSpace = Batch_StrZdup(msg->base.batch, "name_space");

    // instance - reuse cxx sample instance
    MSFT_AllTypes_Class inst;

    // note - get-instance transfers keys only
    inst.Key_value(8);

    UT_ASSERT( MI_RESULT_OK == InstanceToBatch(
        *((MI_Instance**)&inst), NULL, NULL, msg->base.batch,
            &msg->packedInstanceNamePtr, &msg->packedInstanceNameSize));

    msg->includeClassOrigin = MI_TRUE;

    _TransferMessageUsingProtocol( &msg->base, &result );

    /* free source message */
    UT_ASSERT(msg->base.refCounter == 1);
    GetInstanceReq_Release(msg);

    /* check received result */
    UT_ASSERT( result );
    UT_ASSERT( result->tag == GetInstanceReqTag );

    {
        GetInstanceReq* rsp = (GetInstanceReq*)result;
        UT_ASSERT( Zcmp(rsp->nameSpace, MI_T("name_space")) == 0 );
        UT_ASSERT( rsp->includeClassOrigin );

        // instance
        UT_ASSERT(rsp->instanceName);
        //MSFT_AllTypesClass recv_inst((const MSFT_AllTypes *)rsp->instanceName, false);
        MSFT_AllTypes_Class recv_inst;
        _DynamicToStatikInstance( rsp->instanceName, rsp->base.batch, recv_inst );

        UT_ASSERT(recv_inst.Key_value() == 8);
    }

    UT_ASSERT(result->refCounter == 1);
    Message_Release(result);
}

static void TestTransferingPostInstance()
{
    PostInstanceMsg* msg = PostInstanceMsg_New( 1444 );
    Message* result = 0;

    // instance - reuse cxx sample instance
    MSFT_AllTypes_Class inst;
    MI_ConstString test_string = MI_T("some very very very long string 1111111111111111111111111111111111111111111111111111111111111\
        12333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333");

    inst.Key_value(8);
    inst.StringValue_value(test_string);

    UT_ASSERT( MI_RESULT_OK == InstanceToBatch(
        *((MI_Instance**)&inst), NULL, NULL, msg->base.batch,
            &msg->packedInstancePtr, &msg->packedInstanceSize));

    _TransferMessageUsingProtocol( &msg->base, &result );

    /* free source message */
    UT_ASSERT(msg->base.refCounter == 1);
    PostInstanceMsg_Release(msg);

    /* check received result */
    UT_ASSERT( result );
    UT_ASSERT( result->tag == PostInstanceMsgTag );

    {
        PostInstanceMsg* rsp = (PostInstanceMsg*)result;

        // instance
        UT_ASSERT(rsp->instance);
        //MSFT_AllTypesClass recv_inst((const MSFT_AllTypes *)rsp->instance, false);
        MSFT_AllTypes_Class recv_inst;
        _DynamicToStatikInstance( rsp->instance, rsp->base.batch, recv_inst );

        UT_ASSERT(recv_inst.Key_value() == 8);
        UT_ASSERT(recv_inst.StringValue_value() == test_string);
    }

    UT_ASSERT(result->refCounter == 1);
    Message_Release(result);
}

BEGIN_EXTERNC
static void _TestTransferingInvoke(bool listenerUsesExternalSelect, bool connectorUsesExternalSelect, Sock* socketPair)
{
    InvokeReq* msg = InvokeReq_New( 1444, BinaryProtocolFlag );
    Message* result = 0;

    msg->nameSpace = Batch_StrZdup(msg->base.batch, "name_space");
    msg->function = Batch_StrZdup(msg->base.batch, "function");
    msg->className = Batch_StrZdup(msg->base.batch, "className");

    // instance - reuse cxx sample instance
    MSFT_AllTypes_Class inst;
    MI_ConstString test_string = MI_T("some very very very long string 1111111111111111111111111111111111111111111111111111111111111\
        12333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333");

    inst.Key_value(8);
    inst.StringValue_value(test_string);

    UT_ASSERT( MI_RESULT_OK == InstanceToBatch(
        *((MI_Instance**)&inst), NULL, NULL, msg->base.batch,
            &msg->packedInstancePtr, &msg->packedInstanceSize));

    UT_ASSERT( MI_RESULT_OK == InstanceToBatch(
        *((MI_Instance**)&inst), NULL, NULL, msg->base.batch,
            &msg->packedInstanceParamsPtr, &msg->packedInstanceParamsSize));

    _TransferMessageUsingProtocol( &msg->base, &result, listenerUsesExternalSelect, connectorUsesExternalSelect, socketPair );

    /* free source message */
    UT_ASSERT(msg->base.refCounter == 1);
    InvokeReq_Release(msg);

    /* check received result */
    UT_ASSERT( result );
    UT_ASSERT( result->tag == InvokeReqTag );

    {
        InvokeReq* rsp = (InvokeReq*)result;

        UT_ASSERT( Zcmp(rsp->nameSpace, MI_T("name_space")) == 0 );
        UT_ASSERT( Zcmp(rsp->function, MI_T("function")) == 0 );
        UT_ASSERT( Zcmp(rsp->className, MI_T("className")) == 0 );

        // instance
        UT_ASSERT(rsp->instance);
        UT_ASSERT(rsp->instanceParams);
        MSFT_AllTypes_Class recv_inst, recv_inst_params;
        _DynamicToStatikInstance( rsp->instance, rsp->base.batch, recv_inst );
        _DynamicToStatikInstance( rsp->instanceParams, rsp->base.batch, recv_inst_params );

        UT_ASSERT(recv_inst.Key_value() == 8);
        UT_ASSERT(recv_inst.StringValue_value() == test_string);

        UT_ASSERT(recv_inst_params.Key_value() == 8);
        UT_ASSERT(recv_inst_params.StringValue_value() == test_string);
    }

    UT_ASSERT(result->refCounter == 1);
    Message_Release(result);
}
END_EXTERNC

static void TestTransferingInvoke()
{
    _TestTransferingInvoke(false, false, 0);
}

static void TestTransferingInvokeWithExternalSelector()
{
    _TestTransferingInvoke(true, false, 0);
    _TestTransferingInvoke(false, true, 0);
    _TestTransferingInvoke(true, true, 0);
}

BEGIN_EXTERNC
static void _ProtocolEventCallback(
    Protocol* protocol,
    ProtocolEvent event,
    void* data)
{
    MI_UNUSED(protocol);
    MI_UNUSED(data);

    s_events.push_back(event);
}
END_EXTERNC

static void TestProtocolConnectOK()
{
    // create 2 protocols - listener and connector
    Protocol *listener, *connector;
    Message* recvMessageClient = 0; // response from server
    Message* recvMessageServer = 0; // req received by server

    UT_ASSERT( MI_RESULT_OK == Protocol_New_Listener(
        &listener, 0, PORTSTR, _ServerCallback, (void*)&recvMessageServer) );

    UT_ASSERT(MI_RESULT_OK == Protocol_New_Connector(&connector,
        0, PORTSTR,
        _ClientCallback, (void*)&recvMessageClient, _ProtocolEventCallback, 0, "unittest", "unittest"));

    // send noop from client
    NoOpReq* rqt = NoOpReq_New(777);
    Protocol_Send(connector, &rqt->base);
    NoOpReq_Release(rqt);

    for (int attempt = 0; attempt < 100 && !recvMessageClient; attempt++)
    {
        Protocol_Run(connector, 20000);
        Protocol_Run(listener, 20000);
    }

    // verify connect event
    UT_ASSERT(s_events.size() == 1);
    UT_ASSERT(s_events[0] == PROTOCOLEVENT_CONNECT);


    UT_ASSERT( MI_RESULT_OK == Protocol_Delete(listener) );
    s_events.clear();

    // verify disconnect event
    for (int attempt = 0; attempt < 2 && s_events.empty(); attempt++)
    {
        Protocol_Run(connector, 20000);
    }

    UT_ASSERT(s_events.size() == 1);
    UT_ASSERT(s_events[0] == PROTOCOLEVENT_DISCONNECT);

    UT_ASSERT( MI_RESULT_OK == Protocol_Delete(connector) );

    // check messages
    UT_ASSERT( recvMessageServer );
    UT_ASSERT( recvMessageServer->tag == NoOpReqTag );

    UT_ASSERT( recvMessageClient );
    UT_ASSERT( recvMessageClient->tag == NoOpRspTag );
    UT_ASSERT( recvMessageClient->msgID == 777 );

    // free messages
    Message_Release(recvMessageServer);
    Message_Release(recvMessageClient);

}

static void TestProtocolConnectFailed()
{
    // create only connector - should fail to connect
    Protocol *connector;

    MI_Result r = Protocol_New_Connector(&connector,
        0, PORTSTR,
        _ClientCallback, 0, _ProtocolEventCallback, 0, "unittest", "unittest");

    /* some platforms return 'failed' from connect even with non-blocking sockets */
    if (MI_RESULT_FAILED == r)
        return;

    UT_ASSERT(MI_RESULT_OK == r);

    // send noop from client
    NoOpReq* rqt = NoOpReq_New(777);
    Protocol_Send(connector, &rqt->base);
    NoOpReq_Release(rqt);

    for (int attempt = 0; attempt < 10000 && s_events.empty(); attempt++)
    {
        Protocol_Run(connector, 20000);
    }

    // verify connect-failed event
    UT_ASSERT(s_events.size() == 1);
    UT_ASSERT(s_events[0] == PROTOCOLEVENT_CONNECT_FAILED);

    UT_ASSERT( MI_RESULT_OK == Protocol_Delete(connector) );
}

#ifdef CONFIG_POSIX
static void TestFromSocket()
{
    Sock s[2];

    UT_ASSERT(0 == socketpair(AF_UNIX, SOCK_STREAM, 0, s));
    UT_ASSERT( MI_RESULT_OK == Sock_SetBlocking(s[0], MI_FALSE));
    UT_ASSERT( MI_RESULT_OK == Sock_SetBlocking(s[1], MI_FALSE));

    _TestTransferingInvoke(true, true, s);
}
#endif

static void RunTests()
{
#if defined(CONFIG_POSIX)
    /* Disable Auth for unit-tests */
    IgnoreAuthCalls(1);
#endif

    UT_TEST(TestHappyPass);
    UT_TEST(TestTransferingEnumerateInstanceRequest);
    UT_TEST(TestTransferingResult);
    UT_TEST(TestTransferingGetInstanceReqt);
    UT_TEST(TestTransferingPostInstance);
    UT_TEST(TestTransferingInvokeWithExternalSelector);
    UT_TEST(TestTransferingInvoke);

    // Test protocol events
    UT_TEST(TestProtocolConnectFailed);
    UT_TEST(TestProtocolConnectOK);

#ifdef CONFIG_POSIX
    UT_TEST(TestFromSocket);

#endif
}

UT_ENTRY_POINT(RunTests);
