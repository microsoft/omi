/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <vector>
#include <cstdlib>
#include <ut/ut.h>
#include <protocol/protocol.h>
#include <pal/sleep.h>
#include <base/base.h>
#include <base/paths.h>
#include <pal/dir.h>
#include <tests/base/MSFT_AllTypes.h>
#include <base/log.h>

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

# define PORTSTR OMI_GetPath(ID_SOCKETFILE)

using namespace std;
using namespace mi;

STRAND_DEBUGNAME(TestServer);
STRAND_DEBUGNAME(TestClient);

enum ConnectEvent{ ConnectEventNone = 0, ConnectEventConnect, ConnectEventDisconnect };

typedef struct
{
    Strand serverStrand;
    Strand clientStrand;
    Message* serverReceives;
    Message* clientReceives;
    ConnectEvent connectEvent;
} TestData;

static TestData s_data;

BEGIN_EXTERNC

static void _Server_Post( _In_ Strand* self_, _In_ Message* msg)
{
    trace_Server_Post( msg->tag );
    
    Strand_Ack(self_);  // return an Ack to protocol
    
    UT_ASSERT( 0 == s_data.serverReceives ); // expecting only one message

    // memorize request
    s_data.serverReceives = msg;
    Message_AddRef( msg );

    // send response
    NoOpRsp* rsp;

    /* Send NoOp response back */
    rsp = NoOpRsp_New(msg->operationId);

    Strand_Post( self_, &rsp->base);
    NoOpRsp_Release(rsp);
}


static void _Server_Ack( _In_ Strand* self )
{
    trace_Server_Ack();
    // do nothing
}

static void _Server_Close( _In_ Strand* self_ )
{
    trace_Server_Close();
    // we cannot close here as the object are deleted manually
    //Strand_Close( self_ );
}

static void _Server_Finish( _In_ Strand* self_ )
{
    trace_Server_Finish();
    // nothing to do here, (test take care of deleting itself)
}

StrandFT _Server_InteractionFT =
{
    _Server_Post, 
    NULL, 
    _Server_Ack,
    NULL, 
    _Server_Close,
    _Server_Finish,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL 
};

NITS_EXTERN_C void _ServerCallback(
    _Inout_ InteractionOpenParams* interactionParams )
{
    UT_ASSERT( NULL != interactionParams );
    UT_ASSERT( NULL == interactionParams->msg );
    
    Strand_Init( STRAND_DEBUG( TestServer ) &s_data.serverStrand, &_Server_InteractionFT, 0, interactionParams );
}

static void _Client_Post( _In_ Strand* self_, _In_ Message* msg)
{
    trace_Client_PostMessage( msg->tag );
    
    Strand_Ack(self_);  // return an Ack to protocol
    
    UT_ASSERT( 0 == s_data.clientReceives ); // expecting only one message

    // memorize request
    s_data.clientReceives = msg;
    Message_AddRef( msg );
}

static void _Client_PostControl( _In_ Strand* self, _In_ Message* msg)
{
    ProtocolEventConnect* eventMsg = (ProtocolEventConnect*)msg;

    UT_ASSERT( ProtocolEventConnectTag == msg->tag );
    UT_ASSERT( ConnectEventNone == s_data.connectEvent );

    if( eventMsg->success )
    {
        s_data.connectEvent = ConnectEventConnect;
    }
    else
    {
        s_data.connectEvent = ConnectEventDisconnect;
    }
}

static void _Client_Ack( _In_ Strand* self )
{
    trace_Client_Ack();
    // do nothing
}

static void _Client_Close( _In_ Strand* self_ )
{
    trace_Client_Close();
    // we cannot close here as the object are deleted manually
    //Strand_Close( self_ );
}

static void _Client_Finish( _In_ Strand* self_ )
{
    trace_Client_Finish();
    // nothing to do here, (class take care of deleting itself)
}

StrandFT _Client_InteractionFT =
{
    _Client_Post, 
    _Client_PostControl, 
    _Client_Ack,
    NULL, 
    _Client_Close,
    _Client_Finish,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL 
};

END_EXTERNC

static void SetupHelper()
{
#if defined(CONFIG_POSIX)
    /* Disable Auth for unit-tests */
    IgnoreAuthCalls(1);
#endif
    memset( &s_data, 0, sizeof(TestData) );
    s_data.clientReceives = NULL; // response from server
    s_data.serverReceives = NULL; // req received by server
    Strand_Init( STRAND_DEBUG( TestClient ) &s_data.clientStrand, &_Client_InteractionFT, STRAND_FLAG_ENTERSTRAND, NULL );
}

// The Strand is init only in setup and not in the body
// but NITS runs only body of the test during fault iterations and so
// the strand setup is missed causing the tests to fail
NitsSetup(TestProtocolSetup)
{
    NitsDisableFaultSim;
    SetupHelper();
}
NitsEndSetup

NitsTestWithSetup(TestHappyPass, TestProtocolSetup)
{
    /* send noop-rqt and recv noop-rsp */
    // create 2 protocols - listener and connector
    ProtocolBase *listener = NULL;
    ProtocolSocketAndBase *connector = NULL;
    MI_Result r;

    r = ProtocolBase_New_Listener(
        &listener, 0, PORTSTR, _ServerCallback, NULL );
    UT_ASSERT( MI_RESULT_OK == r );
    if (MI_RESULT_OK != r)
    {
        printf("\nProtocolBase_New_Listener failed with error (%d).\n", r);
        NitsReturn;
    }
    
    InteractionOpenParams params;
    
    Strand_OpenPrepare(&s_data.clientStrand,&params,NULL,NULL,MI_TRUE);

    r = ProtocolSocketAndBase_New_Connector(&connector, 0, PORTSTR, &params, "unittest", "unittest" );
    UT_ASSERT(MI_RESULT_OK == r);
    if (MI_RESULT_OK != r)
    {
        printf("\nProtocolSocket_New_Connector failed with error (%d).\n", r);
        ProtocolBase_Delete(listener);
        NitsReturn;
    }

    // send noop from client
    NoOpReq* rqt = NoOpReq_New(777);
    Strand_SchedulePost( &s_data.clientStrand, &rqt->base.base);
    NoOpReq_Release(rqt);

    for ( int attempt = 0; attempt < 12 && !s_data.clientReceives; attempt++)
    {
        Protocol_Run( &connector->internalProtocolBase, 100 * SELECT_BASE_TIMEOUT_MSEC * 1000);
        Protocol_Run( listener, 100 * SELECT_BASE_TIMEOUT_MSEC * 1000);
    }

    // check messages
    UT_ASSERT( s_data.serverReceives );
    UT_ASSERT( s_data.serverReceives->tag == NoOpReqTag );

    UT_ASSERT( s_data.clientReceives );
    UT_ASSERT( s_data.clientReceives->tag == NoOpRspTag );
    UT_ASSERT( s_data.clientReceives->operationId == 777 );

    // free messages
    Message_Release(s_data.serverReceives);
    Message_Release(s_data.clientReceives);

    ProtocolSocketAndBase_ReadyToFinish(connector);
    UT_ASSERT( MI_RESULT_OK == ProtocolBase_Delete(listener) );
}
NitsEndTest

BEGIN_EXTERNC
static void _TransferMessageUsingProtocol(
    Message* msg,
    Message** result,
    bool listenerUsesExternalSelect = false, 
    bool connectorUsesExternalSelect = false,
    Sock* socketPair = 0)
{
    Selector internal_selector; // note that is is "external" selector from connector/serverSocket point of view
    Selector*   selector = 0;
    MI_Result r;

    if (listenerUsesExternalSelect || connectorUsesExternalSelect)
    {
        /* Initialize the network */
        Sock_Start();

        r = Selector_Init(&internal_selector);
        UT_ASSERT(r == MI_RESULT_OK);
        if(r != MI_RESULT_OK)
            return;
        selector = &internal_selector;
    }

    /* send message to the server and return received message from server's callback */
    // create 2 protocols - listener/serverSocket and connector
    ProtocolSocketAndBase *connector = NULL;
    ProtocolBase *listener = NULL;
    ProtocolSocketAndBase *serverSocket = NULL;    

    if (0 == socketPair)
    {
        UT_ASSERT( MI_RESULT_OK == ProtocolBase_New_Listener(
            &listener, listenerUsesExternalSelect ? selector : 0, PORTSTR, _ServerCallback, NULL) );        

        InteractionOpenParams params;
        
        Strand_OpenPrepare(&s_data.clientStrand,&params,NULL,NULL,MI_TRUE);

        r = ProtocolSocketAndBase_New_Connector(&connector, connectorUsesExternalSelect ? selector : 0, PORTSTR, &params, "unittest", "unittest" );
        UT_ASSERT(MI_RESULT_OK == r);
        if (MI_RESULT_OK != r)
        {
            printf("\nProtocolSocket_New_Connector failed with error (%d).\n", r);
            ProtocolBase_Delete(listener);
            return;
        }
    }
    else
    {
        r = ProtocolSocketAndBase_New_Agent(
            &serverSocket, 
            listenerUsesExternalSelect ? selector : 0, 
            socketPair[0], 
            _ServerCallback, NULL);
        UT_ASSERT( MI_RESULT_OK == r);
        if(r != MI_RESULT_OK)
            return;

        InteractionOpenParams interactionParams;
        
        Strand_OpenPrepare(&s_data.clientStrand,&interactionParams,NULL,NULL,MI_TRUE);
        
        r = ProtocolSocketAndBase_New_AgentConnector(
            &connector, 
            connectorUsesExternalSelect ? selector : 0, 
            socketPair[1],
            &interactionParams);
        UT_ASSERT(MI_RESULT_OK == r);
        if (MI_RESULT_OK != r)
        {
            printf("\nProtocolSocketAndBase_New_AgentConnector failed with error (%d).\n", r);
            return;
        }
    }

    // send message from client
    Strand_SchedulePost( &s_data.clientStrand, msg);

    for ( int attempt = 0; attempt < 12 && !s_data.clientReceives; attempt++)
    {
        Protocol_Run( &connector->internalProtocolBase, 100 * SELECT_BASE_TIMEOUT_MSEC * 1000);
        if (0 == socketPair)
        {
            Protocol_Run(listener, 100 * SELECT_BASE_TIMEOUT_MSEC * 1000);
        }
        else
        {
            Protocol_Run( &serverSocket->internalProtocolBase, 100 * SELECT_BASE_TIMEOUT_MSEC * 1000);
        }
    }

    /* remove all handlers befroe destroying protocols */
    if (selector)
        Selector_RemoveAllHandlers(selector);

    if (0 == socketPair)
    {
        UT_ASSERT( MI_RESULT_OK == ProtocolBase_Delete(listener) );
    }
    else
    {
        ProtocolSocketAndBase_ReadyToFinish(serverSocket);
    }
    ProtocolSocketAndBase_ReadyToFinish(connector);

    if (selector)
    {
        Selector_Destroy(selector);

        /* Shutdown the network */
        Sock_Stop();
    }

    *result = s_data.serverReceives;
    
    if (s_data.clientReceives)
        Message_Release(s_data.clientReceives);

}
END_EXTERNC

NitsTestWithSetup(TestTransferingEnumerateInstanceRequest, TestProtocolSetup)
{
    EnumerateInstancesReq* msg = EnumerateInstancesReq_New( 1444, BinaryProtocolFlag );
    Message* result = 0;

    msg->deepInheritance = MI_TRUE;
    msg->nameSpace = Batch_StrTcsdup(msg->base.base.batch, "name_space");
    msg->className = Batch_StrTcsdup(msg->base.base.batch, "class_name");

    _TransferMessageUsingProtocol( &msg->base.base, &result );

    /* free source message */
    UT_ASSERT(msg->base.base.refCounter == 1);
    EnumerateInstancesReq_Release(msg);

    /* check received result */
    UT_ASSERT( result );
    UT_ASSERT( result->tag == EnumerateInstancesReqTag );

    {
        EnumerateInstancesReq* rsp = (EnumerateInstancesReq*)result;
        UT_ASSERT( Tcscmp(rsp->nameSpace, MI_T("name_space")) == 0 );
        UT_ASSERT( Tcscmp(rsp->className, MI_T("class_name")) == 0 );
        UT_ASSERT( rsp->deepInheritance );
    }

    UT_ASSERT(result->refCounter == 1);
    Message_Release(result);
}
NitsEndTest

NitsTestWithSetup(TestTransferingResult, TestProtocolSetup)
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
NitsEndTest

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
        batch,
        0);

    UT_ASSERT( MI_RESULT_OK == r );

    inst = MSFT_AllTypes_Class((const MSFT_AllTypes *)instOut, false);
}
END_EXTERNC

NitsTestWithSetup(TestTransferingGetInstanceReqt, TestProtocolSetup)
{
    GetInstanceReq* msg = GetInstanceReq_New( 1444, BinaryProtocolFlag );
    Message* result = 0;

    msg->nameSpace = Batch_StrTcsdup(msg->base.base.batch, "name_space");

    // instance - reuse cxx sample instance
    MSFT_AllTypes_Class inst;

    // note - get-instance transfers keys only
    inst.Key_value(8);

    UT_ASSERT( MI_RESULT_OK == InstanceToBatch(
        *((MI_Instance**)&inst), NULL, NULL, msg->base.base.batch, 
            &msg->packedInstanceNamePtr, &msg->packedInstanceNameSize));

    msg->includeClassOrigin = MI_TRUE;

    _TransferMessageUsingProtocol( &msg->base.base, &result );

    /* free source message */
    UT_ASSERT(msg->base.base.refCounter == 1);
    GetInstanceReq_Release(msg);

    /* check received result */
    UT_ASSERT( result );
    UT_ASSERT( result->tag == GetInstanceReqTag );

    {
        GetInstanceReq* rsp = (GetInstanceReq*)result;
        UT_ASSERT( Tcscmp(rsp->nameSpace, MI_T("name_space")) == 0 );
        UT_ASSERT( rsp->includeClassOrigin );

        // instance
        UT_ASSERT(rsp->instanceName);
        //MSFT_AllTypesClass recv_inst((const MSFT_AllTypes *)rsp->instanceName, false);
        MSFT_AllTypes_Class recv_inst;
        _DynamicToStatikInstance( rsp->instanceName, rsp->base.base.batch, recv_inst );

        UT_ASSERT(recv_inst.Key_value() == 8);
    }

    UT_ASSERT(result->refCounter == 1);
    Message_Release(result);
}
NitsEndTest

NitsTestWithSetup(TestTransferingPostInstance, TestProtocolSetup)
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
NitsEndTest

BEGIN_EXTERNC
static void _TestTransferingInvoke(bool listenerUsesExternalSelect, bool connectorUsesExternalSelect, Sock* socketPair)
{
    InvokeReq* msg = InvokeReq_New( 1444, BinaryProtocolFlag );
    Message* result = 0;

    msg->nameSpace = Batch_StrTcsdup(msg->base.base.batch, "name_space");
    msg->function = Batch_StrTcsdup(msg->base.base.batch, "function");
    msg->className = Batch_StrTcsdup(msg->base.base.batch, "className");

    // instance - reuse cxx sample instance
    MSFT_AllTypes_Class inst;
    MI_ConstString test_string = MI_T("some very very very long string 1111111111111111111111111111111111111111111111111111111111111\
        12333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333");

    inst.Key_value(8);
    inst.StringValue_value(test_string);

    UT_ASSERT( MI_RESULT_OK == InstanceToBatch(
        *((MI_Instance**)&inst), NULL, NULL, msg->base.base.batch, 
            &msg->packedInstancePtr, &msg->packedInstanceSize));

    UT_ASSERT( MI_RESULT_OK == InstanceToBatch(
        *((MI_Instance**)&inst), NULL, NULL, msg->base.base.batch, 
            &msg->packedInstanceParamsPtr, &msg->packedInstanceParamsSize));

    _TransferMessageUsingProtocol( &msg->base.base, &result, listenerUsesExternalSelect, connectorUsesExternalSelect, socketPair );

    /* free source message */
    UT_ASSERT(msg->base.base.refCounter == 1);
    InvokeReq_Release(msg);

    /* check received result */
    UT_ASSERT( result );
    UT_ASSERT( result->tag == InvokeReqTag );

    {
        InvokeReq* rsp = (InvokeReq*)result;

        UT_ASSERT( Tcscmp(rsp->nameSpace, MI_T("name_space")) == 0 );
        UT_ASSERT( Tcscmp(rsp->function, MI_T("function")) == 0 );
        UT_ASSERT( Tcscmp(rsp->className, MI_T("className")) == 0 );

        // instance
        UT_ASSERT(rsp->instance);
        UT_ASSERT(rsp->instanceParams);
        MSFT_AllTypes_Class recv_inst, recv_inst_params;
        _DynamicToStatikInstance( rsp->instance, rsp->base.base.batch, recv_inst );
        _DynamicToStatikInstance( rsp->instanceParams, rsp->base.base.batch, recv_inst_params );

        UT_ASSERT(recv_inst.Key_value() == 8);
        UT_ASSERT(recv_inst.StringValue_value() == test_string);

        UT_ASSERT(recv_inst_params.Key_value() == 8);
        UT_ASSERT(recv_inst_params.StringValue_value() == test_string);
    }

    UT_ASSERT(result->refCounter == 1);
    Message_Release(result);
}
END_EXTERNC

NitsTestWithSetup(TestTransferingInvoke, TestProtocolSetup)
{
    _TestTransferingInvoke(false, false, 0);
}
NitsEndTest

NitsTestWithSetup(TestTransferingInvokeWithExternalSelector, TestProtocolSetup)
{
    _TestTransferingInvoke(true, false, 0);
    SetupHelper();
    _TestTransferingInvoke(false, true, 0);
    SetupHelper();
    _TestTransferingInvoke(true, true, 0);
}
NitsEndTest

NitsTestWithSetup(TestProtocolConnectOK, TestProtocolSetup)
{
    // create 2 protocols - listener and connector
    ProtocolBase *listener = NULL;
    ProtocolSocketAndBase *connector = NULL;

    UT_ASSERT( MI_RESULT_OK == ProtocolBase_New_Listener(
        &listener, 0, PORTSTR, _ServerCallback, NULL ) );
 
    InteractionOpenParams params;
 
    Strand_OpenPrepare(&s_data.clientStrand,&params,NULL,NULL,MI_TRUE);
    
    MI_Result r = ProtocolSocketAndBase_New_Connector(&connector, 0, PORTSTR, &params, "unittest", "unittest");
    UT_ASSERT(MI_RESULT_OK == r);
    if (MI_RESULT_OK != r)
    {
        printf("\nProtocolSocket_New_Connector failed with error (%d).\n", r);
        ProtocolBase_Delete(listener);
        NitsReturn;
    }

    // send noop from client
    NoOpReq* rqt = NoOpReq_New(777);
    Strand_SchedulePost( &s_data.clientStrand, &rqt->base.base);
    NoOpReq_Release(rqt);

    for ( int attempt = 0; attempt < 100 && !s_data.clientReceives; attempt++)
    {
        Protocol_Run( &connector->internalProtocolBase, 100 * SELECT_BASE_TIMEOUT_MSEC * 1000);
        Protocol_Run( listener, 100 * SELECT_BASE_TIMEOUT_MSEC * 1000);
    }

    // verify connect event
    UT_ASSERT( ConnectEventConnect == s_data.connectEvent );

    UT_ASSERT( MI_RESULT_OK == ProtocolBase_Delete(listener) );

    // verify disconnect close
    for ( int attempt = 0; attempt < 2 && !s_data.clientStrand.info.otherClosedThis; attempt++)
    {
        Protocol_Run( &connector->internalProtocolBase, 100 * SELECT_BASE_TIMEOUT_MSEC * 1000);
    }

    UT_ASSERT( s_data.clientStrand.info.otherClosedThis );

    ProtocolSocketAndBase_ReadyToFinish(connector);

    UT_ASSERT( s_data.serverReceives );
    UT_ASSERT( s_data.serverReceives->tag == NoOpReqTag );

    UT_ASSERT( s_data.clientReceives );
    UT_ASSERT( s_data.clientReceives->tag == NoOpRspTag );
    UT_ASSERT( s_data.clientReceives->operationId == 777 );

    // free messages
    Message_Release(s_data.serverReceives);
    Message_Release(s_data.clientReceives);
}
NitsEndTest

NitsTestWithSetup(TestProtocolConnectFailed, TestProtocolSetup)
{
    // create only connector - should fail to connect
    ProtocolSocketAndBase *connector;

    InteractionOpenParams params;
 
    Strand_OpenPrepare(&s_data.clientStrand,&params,NULL,NULL,MI_TRUE);
    
    MI_Result r = ProtocolSocketAndBase_New_Connector(&connector, 0, PORTSTR, &params, "unittest", "unittest");

    /* some platforms return 'failed' from connect even with non-blocking sockets */
    if (MI_RESULT_FAILED == r)
    {
        // ignoring the problem and passing the test
        UT_ASSERT(true);
        NitsReturn;
    }

    UT_ASSERT(MI_RESULT_OK == r);

    // wait for connect event
    for ( int attempt = 0; attempt < 10000 && ConnectEventNone == s_data.connectEvent; attempt++)
    {
        Protocol_Run( &connector->internalProtocolBase, SELECT_BASE_TIMEOUT_MSEC * 1000);
    }
    
    /* some platforms return 'failed' from connect even with non-blocking sockets */
    if( ConnectEventDisconnect == s_data.connectEvent || s_data.clientStrand.canceled )
    {
        // ignoring the problem and passing the test
        UT_ASSERT(true);
        NitsReturn;
    }
    
    // send noop from client
    NoOpReq* rqt = NoOpReq_New(777);
    Strand_SchedulePost( &s_data.clientStrand, &rqt->base.base);
    NoOpReq_Release(rqt);

    for ( int attempt = 0; attempt < 10000 && ConnectEventNone == s_data.connectEvent; attempt++)
    {
        Protocol_Run( &connector->internalProtocolBase, SELECT_BASE_TIMEOUT_MSEC * 1000);
    }

    // verify connect-failed event
    UT_ASSERT( ConnectEventDisconnect == s_data.connectEvent );

    ProtocolSocketAndBase_ReadyToFinish(connector);
}
NitsEndTest

#ifdef CONFIG_POSIX
NitsTestWithSetup(TestFromSocket, TestProtocolSetup)
{
    Sock s[2];

    UT_ASSERT(0 == socketpair(AF_UNIX, SOCK_STREAM, 0, s));
    UT_ASSERT( MI_RESULT_OK == Sock_SetBlocking(s[0], MI_FALSE));
    UT_ASSERT( MI_RESULT_OK == Sock_SetBlocking(s[1], MI_FALSE));

    _TestTransferingInvoke(true, true, s);
}
NitsEndTest
#endif
