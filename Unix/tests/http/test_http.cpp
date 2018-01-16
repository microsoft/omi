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
#include <pal/thread.h>
#include <http/httpcommon.h>
#include <base/result.h>
#include <base/Strand.h>
#include <base/log.h>
#include <http/http_private.h>

static MI_Uint16 PORT = ut::getUnittestPortNumber() + 10;

#define TEST_BASICAUTH_BASE64 "dGVzdDpwYXNzd29yZA=="
#define TEST_USERNAME "test"
#define TEST_PASSWORD "password"

using namespace std;

STRAND_DEBUGNAME( TestHttp );

/*************************************/
/* local data */
static Http* s_http;
static bool s_stop;
static Thread s_t;

NitsSetup(TestHttpSetup)
{
    Sock_Start();
    PORT++;
    IgnoreAuthCalls(1);
}

NitsEndSetup

NitsCleanup(TestHttpSetup)
{
    Sock_Stop();
}
NitsEndCleanup

 /* helper functions */
BEGIN_EXTERNC
static void* MI_CALL _HTTPServerProc(void* )
{
    Sock_Start();
    // pump messages
    for (; !s_stop; )
        Http_Run( s_http, SELECT_BASE_TIMEOUT_MSEC * 1000 );

    Sock_Stop();
    return 0;
}
END_EXTERNC

BEGIN_EXTERNC
static void _DeleteHttp()
{
    TEST_ASSERT( MI_RESULT_OK == Http_Delete(s_http) );

    memset(&s_t, 0, sizeof(Thread));
    s_http = 0;
    s_stop = false;
}

static MI_Result _StartHTTP_Server(
    OpenCallback callbackOnNewConnection,
    void* callbackData,
    const char* sslCipherSuite,
    const HttpOptions* options = 0)
{
    /* create a server */
    if (!TEST_ASSERT( MI_RESULT_OK == Http_New_Server(
        &s_http, 0, PORT, 0, sslCipherSuite, (SSL_Options) 0,
        callbackOnNewConnection,
        callbackData, options) ))
        return MI_RESULT_FAILED;

    /* create a thread for message consumption */
    s_stop = false;

    if (!TEST_ASSERT(MI_RESULT_OK == Thread_CreateJoinable(
        &s_t, (ThreadProc) _HTTPServerProc,  NULL, 0)))
    {
        _DeleteHttp();
        return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
}

static void _StopHTTP_Server()
{
    PAL_Uint32 ret;

    s_stop = true;
    TEST_ASSERT( Thread_Join(&s_t, &ret) == 0 );
    Thread_Destroy(&s_t);
    _DeleteHttp();
}
END_EXTERNC

struct ThreadParam
{
    string messageToSend;
    size_t  bytesToSendPerOperation;
    string response;
    bool gotRsp;
};

static Sock SockConnectLocal(unsigned short port)
{
    Sock sock;
    Addr addr;
    MI_Result r;

    Sock_Start();

    // Initialize address (connect using loopback).
    r = Addr_Init(&addr, "127.0.0.1", port, MI_FALSE);
    TEST_ASSERT(r == MI_RESULT_OK);

    // Create client socket.
    r = Sock_Create(&sock, MI_FALSE);
    TEST_ASSERT(r == MI_RESULT_OK);
 
    r = Sock_Connect(sock, &addr);
    TEST_ASSERT(r == MI_RESULT_OK);
    return sock;
}

/* simple http client */
BEGIN_EXTERNC
static void* MI_CALL _http_client_proc(void* param)
{
    ThreadParam* p = (ThreadParam*)param;

    Sock sock;
    MI_Result r;

    Sock_Start();

    // Initialize address (connect using loopback).
    sock = SockConnectLocal(PORT);

    size_t sent = 0;
    size_t size_left = p->messageToSend.size();
    const char* buf = p->messageToSend.c_str();

    while ( size_left )
    {
        size_t wantToSend = min(p->bytesToSendPerOperation, size_left);
        r = Sock_Write(sock, buf, wantToSend, &sent);

        //printf("size_left %d, r %d, sent %d, want-send %d\n", size_left, r, sent, wantToSend);
        if ( r != MI_RESULT_OK)
        {
            //printf("size_left %d, r %d, want write %d, sent %d, le %d\n", (int)size_left, (int)r, (int)wantToSend, (int)sent, Sock_GetLastError());
        ut::sleep_ms( 7000 );

        }

        TEST_ASSERT(r == MI_RESULT_OK);
//        printf("s: %d\n", (int)sent);
        size_left -= sent;
        buf += sent;
        ut::sleep_ms( 1 );
    }

    // read response
    char r_buf[1024];
    size_t read = 0;
    int err;

    do
    {
        r = Sock_Read(sock, r_buf, sizeof(r_buf), &read);
        err = Sock_GetLastError();
    }
#if defined(macos)
    while (r != MI_RESULT_OK && (err == EAGAIN || err == EDEADLK));
#else
    while (r != MI_RESULT_OK && err == EAGAIN);
#endif
    
    //if (r) printf("s,r: %d, err %d\n", (int)read, err);

    TEST_ASSERT(r == MI_RESULT_OK);

    p->response = string(r_buf, read);

    p->gotRsp = true;
    Sock_Close(sock);

    Sock_Stop();
    return 0;
}
END_EXTERNC

BEGIN_EXTERNC
static void* MI_CALL http_client_proc(void* param)
{
    try
    {
        return _http_client_proc(param);
    }
    catch (ut::UnittestException ex)
    {
        ex.m_testcase = "--http_client_proc"; UT_ASSERT_FAILED_MSG(ex.m_testcase.c_str());
    }  
    return 0;
}
END_EXTERNC

struct CallbackStruct
{
    Strand strand;
    
    string contentType;
    string charset;
    string authorization;
    string username;
    string password;
    size_t  contentLength;
    string data;
    string response;

    CallbackStruct() : contentLength(0){}
};

BEGIN_EXTERNC
static void _StrandTestPost( _In_ Strand* self_, _In_ Message* msg ) 
{
    CallbackStruct* data = (CallbackStruct*)self_;
    HttpRequestMsg* request = (HttpRequestMsg *)msg;
    HttpResponseMsg* msgRsp = NULL;

    TEST_ASSERT( HttpRequestMsgTag == msg->tag );

    if (request->headers->contentType)
        data->contentType = request->headers->contentType;

    if (request->headers->charset)
        data->charset = request->headers->charset;

    if (request->headers->authorization)
        data->authorization = request->headers->authorization;
    if (request->headers->username)
        data->username = request->headers->username;
    if (request->headers->password)
        data->password = request->headers->password;

    data->contentLength = request->headers->contentLength;

    data->data = string( (char*) ((request->page)+1), (size_t)(request->page)->u.s.size);

    Page* rsp = (Page*)PAL_Malloc(sizeof(Page) + data->response.size());
    
    TEST_ASSERT(rsp);

    if(rsp)
    {
        rsp->u.s.size = data->response.size();
        memcpy(rsp+1, data->response.c_str(), data->response.size());

        msgRsp = HttpResponseMsg_New(rsp, HTTP_ERROR_CODE_OK);

        TEST_ASSERT( NULL != msg );
    }
    Strand_Ack( &data->strand );
    if(msgRsp)
    {
        Strand_Post( &data->strand, &msgRsp->base );
        HttpResponseMsg_Release( msgRsp );
    }
    else
    {        
        Strand_Close(&data->strand);
    }
}
    
static void _StrandTestAck( _In_ Strand* self) 
{
    // do nothing
}

static void _StrandTestClose( _In_ Strand* self) 
{
    // close other
    Strand_Close( self );
}

static void _StrandTestFinished( _In_ Strand* self) 
{
    // do nothing
}

static StrandFT strandUserFT1 = { 
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
        
static void _callback(
    _Inout_     InteractionOpenParams* interactionParams )
{
    CallbackStruct* data = (CallbackStruct*)interactionParams->callbackData;
    
    UT_ASSERT (data != NULL);
    UT_ASSERT (interactionParams->msg == NULL);
    
    Strand_Init( STRAND_DEBUG( TestHttp ) &data->strand, &strandUserFT1, 0, interactionParams );
}

static void _StrandTestPost2( _In_ Strand* self_, _In_ Message* msg ) 
{
    UT_ASSERT_FAILED_MSG("should be never called");
}
    
static StrandFT strandUserFT2 = { 
        _StrandTestPost2, 
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
        
static void _callback2(
    _Inout_     InteractionOpenParams*    interactionParams )
{
    CallbackStruct* data = (CallbackStruct*)interactionParams->callbackData;
    
    UT_ASSERT (data != NULL);
    UT_ASSERT (interactionParams->msg == NULL);
    
    Strand_Init( STRAND_DEBUG( TestHttp ) &data->strand, &strandUserFT2, 0, interactionParams );
}
END_EXTERNC

NitsTestWithSetup(TestHttpHappyPass, TestHttpSetup)
{
    NitsDisableFaultSim;

    Http* http = 0;
    CallbackStruct cb;

    cb.response = "Response";

    /* create a server */
    if(!TEST_ASSERT( MI_RESULT_OK == Http_New_Server(
        &http, 0, PORT, 0, NULL, (SSL_Options) 0,
        _callback,
        &cb,
        NULL) ))
        return;

    /* create a client */
    ThreadParam param;
    Thread t;

    param.messageToSend = 
        "POST /wsman HTTP/1.1\r\n"
        "Content-Type: application/soap+xml;charset=UTF-8\r\n"
        "User-Agent: Microsoft WinRM Client\r\n"
        "Host: localhost:7778\r\n"
        "Content-Length: 5\r\n"
        "Authorization: auth\r\n"
        "\r\n"
        "Hello";
    param.bytesToSendPerOperation = 30000;
    param.gotRsp = false;

    int threadCreatedResult = Thread_CreateJoinable(
        &t, (ThreadProc)http_client_proc, NULL, &param);
    TEST_ASSERT(MI_RESULT_OK == threadCreatedResult);
    if(threadCreatedResult != MI_RESULT_OK)
        goto EndTest;


    // pump messages
    for (int i = 0; !param.gotRsp && i < 10000; i++ )
        Http_Run( http, SELECT_BASE_TIMEOUT_MSEC * 1000 );

    // wait for completion and check that
    PAL_Uint32 ret;
    TEST_ASSERT( Thread_Join( &t, &ret ) == 0 );
    Thread_Destroy( &t );

    // check messages

    TEST_ASSERT( cb.authorization == "auth" );
    TEST_ASSERT( cb.contentType == "application/soap+xml" );
    TEST_ASSERT( cb.charset == "UTF-8" );
    TEST_ASSERT( cb.contentLength == 5 );
    TEST_ASSERT( cb.data == "Hello" );

EndTest:
    //TEST_ASSERT( param.response.find("Response") != string::npos );

    TEST_ASSERT( MI_RESULT_OK == Http_Delete(http) );
}
NitsEndTest

NitsTestWithSetup(TestHttp_BigLoad, TestHttpSetup)
{
    NitsDisableFaultSim;

    Http* http = 0;
    CallbackStruct cb;

    cb.response = string(256 * 1024, '*');
    

    /* create a server */
    if(!TEST_ASSERT( MI_RESULT_OK == Http_New_Server(
        &http, 0, PORT, 0, NULL, (SSL_Options) 0,
        _callback,
        &cb,
        NULL) ))
        return;

    /* create a client */
    ThreadParam param;
    Thread t;

    param.messageToSend = 
        "POST /wsman HTTP/1.1\r\n"
        "Content-Type: text\r\n"
        "User-Agent: Microsoft WinRM Client\r\n"
        "Host: localhost:7778\r\n"
        "Content-Length: 32999\r\n"
        "Authorization: auth\r\n"
        "\r\n";
        
    param.messageToSend += string(32999, '.');

    param.bytesToSendPerOperation = 8000;
    param.gotRsp = false;
    int threadCreatedResult = Thread_CreateJoinable(
        &t, (ThreadProc)http_client_proc, NULL, &param);
    TEST_ASSERT(MI_RESULT_OK == threadCreatedResult);
    if(threadCreatedResult != MI_RESULT_OK)
        goto TestEnd;

    // pump messages
    for (int i = 0; !param.gotRsp && i < 10000; i++ )
        Http_Run( http, SELECT_BASE_TIMEOUT_MSEC * 1000 );

    //printf("out of run\n");

    // wait for completion and check that
    PAL_Uint32 ret;
    TEST_ASSERT( Thread_Join( &t, &ret ) == 0 );
    Thread_Destroy( &t );


    // check messages

    TEST_ASSERT( cb.authorization == "auth" );
    TEST_ASSERT( cb.password == "" );
    TEST_ASSERT( cb.username == "" );
    TEST_ASSERT( cb.contentType == "text" );
    TEST_ASSERT( cb.charset == "" );
    TEST_ASSERT( cb.contentLength == 32999 );
    TEST_ASSERT( cb.data == string(32999, '.') );

    //TEST_ASSERT( param.response.find("Response") != string::npos );
TestEnd:
    TEST_ASSERT( MI_RESULT_OK == Http_Delete(http) );
}
NitsEndTest

NitsTestWithSetup(TestHttp_QuotedCharset, TestHttpSetup)
{
    NitsDisableFaultSim;

    Http* http = 0;
    CallbackStruct cb;

    cb.response = "Response";

    /* create a server */
    if(!TEST_ASSERT( MI_RESULT_OK == Http_New_Server(
        &http, 0, PORT, 0, NULL, (SSL_Options) 0,
        _callback,
        &cb,
        NULL) ))
        return;

    /* create a client */
    ThreadParam param;
    Thread t;

    param.messageToSend = 
        "POST /wsman HTTP/1.1\r\n"
        "Content-Type: application/soap+xml;  \tcharset=\"UTF-16\"\t \r\n"
        "User-Agent: Microsoft WinRM Client\r\n"
        "Host: localhost:7778\r\n"
        "Content-Length: 5\r\n"
        "Authorization: auth\r\n"
        "\r\n"
        "aloha";
    param.bytesToSendPerOperation = 30000;
    param.gotRsp = false;

    int threadCreatedResult = Thread_CreateJoinable(
        &t, (ThreadProc)http_client_proc, NULL, &param);
    TEST_ASSERT(MI_RESULT_OK == threadCreatedResult);
    if(threadCreatedResult != MI_RESULT_OK)
        goto TestEnd;
    // pump messages
    for (int i = 0; !param.gotRsp && i < 10000; i++ )
        Http_Run( http, SELECT_BASE_TIMEOUT_MSEC * 1000 );

    // wait for completion and check that
    PAL_Uint32 ret;
    TEST_ASSERT( Thread_Join( &t, &ret ) == 0 );
    Thread_Destroy( &t );

    // check messages

    TEST_ASSERT( cb.authorization == "auth" );
    TEST_ASSERT( cb.contentType == "application/soap+xml" );
    TEST_ASSERT( cb.charset == "UTF-16" );
    TEST_ASSERT( cb.contentLength == 5 );
    TEST_ASSERT( cb.data == "aloha" );

    //TEST_ASSERT( param.response.find("Response") != string::npos );
TestEnd:
    TEST_ASSERT( MI_RESULT_OK == Http_Delete(http) );
}
NitsEndTest

NitsTestWithSetup(TestHttp_Base64Decoding, TestHttpSetup)
{
    NitsDisableFaultSim;

    Http* http = 0;
    CallbackStruct cb;

    cb.response = "Response";

    /* create a server */
    if(!TEST_ASSERT( MI_RESULT_OK == Http_New_Server(
        &http, 0, PORT, 0, NULL, (SSL_Options) 0,
        _callback,
        &cb,
        NULL) ))
        return;

    /* create a client */
    ThreadParam param;
    Thread t;

    param.messageToSend = 
        "POST /wsman HTTP/1.1\r\n"
        "Content-Type: application/soap+xml;  \tcharset=\"UTF-16\"\t \r\n"
        "User-Agent: Microsoft WinRM Client\r\n"
        "Host: localhost:7778\r\n"
        "Content-Length: 5\r\n"
        "Authorization:    Basic \t \t" TEST_BASICAUTH_BASE64 "\t \r\n"
        "\r\n"
        "aloha";
    param.bytesToSendPerOperation = 30000;
    param.gotRsp = false;

    int threadCreatedResult = Thread_CreateJoinable(
        &t, (ThreadProc)http_client_proc, NULL, &param);
    TEST_ASSERT(MI_RESULT_OK == threadCreatedResult);
    if(threadCreatedResult != MI_RESULT_OK)
        goto TestEnd;
    // pump messages
    for (int i = 0; !param.gotRsp && i < 10000; i++ )
        Http_Run( http, SELECT_BASE_TIMEOUT_MSEC * 1000 );

    // wait for completion and check that
    PAL_Uint32 ret;
    TEST_ASSERT( Thread_Join( &t, &ret ) == 0 );
    Thread_Destroy( &t );


    // check messages

    TEST_ASSERT( cb.authorization == "Basic" );
    TEST_ASSERT( cb.username == TEST_USERNAME );
    TEST_ASSERT( cb.password == TEST_PASSWORD );
    TEST_ASSERT( cb.contentType == "application/soap+xml" );
    TEST_ASSERT( cb.charset == "UTF-16" );
    TEST_ASSERT( cb.contentLength == 5 );
    TEST_ASSERT( cb.data == "aloha" );

    //TEST_ASSERT( param.response.find("Response") != string::npos );
TestEnd:
    TEST_ASSERT( MI_RESULT_OK == Http_Delete(http) );
}
NitsEndTest

NitsTestWithSetup(TestHttp_InvalidBase64Data, TestHttpSetup)
{
    NitsDisableFaultSim;

    Http* http = 0;
    CallbackStruct cb;

    cb.response = "Response";

    /* create a server */
    if(!TEST_ASSERT( MI_RESULT_OK == Http_New_Server(
        &http, 0, PORT, 0, NULL, (SSL_Options) 0,
        _callback,
        &cb,
        NULL) ))
        return;

    /* create a client */
    ThreadParam param;
    Thread t;

    /* send request with invalid base64 data; server should close connection */
    param.messageToSend = 
        "POST /wsman HTTP/1.1\r\n"
        "Content-Type: application/soap+xml;  \tcharset=\"UTF-16\"\t \r\n"
        "User-Agent: Microsoft WinRM Client\r\n"
        "Host: localhost:7778\r\n"
        "Content-Length: 5\r\n"
        "Authorization:    Basic \t \tcm9vd\xFE\xFF==\t \r\n"
        "\r\n"
        "aloha";
    param.bytesToSendPerOperation = 30000;
    param.gotRsp = false;
    int threadCreatedResult = Thread_CreateJoinable(
        &t, (ThreadProc)http_client_proc, NULL, &param);
    TEST_ASSERT(MI_RESULT_OK == threadCreatedResult);
    if(threadCreatedResult != MI_RESULT_OK)
        goto TestEnd;

    // pump messages
    for (int i = 0; !param.gotRsp && i < 10000; i++ )
        Http_Run( http, SELECT_BASE_TIMEOUT_MSEC * 1000 );

    // wait for completion and check that
    PAL_Uint32 ret;
    TEST_ASSERT( Thread_Join( &t, &ret ) == 0 );
    Thread_Destroy( &t );


    // check messages
    TEST_ASSERT( param.response.empty() );
    TEST_ASSERT( cb.authorization == "" );
    TEST_ASSERT( cb.username == "" );
    TEST_ASSERT( cb.password == "" );
    TEST_ASSERT( cb.contentType == "" );
    TEST_ASSERT( cb.charset == "" );
    TEST_ASSERT( cb.contentLength == 0 );
    TEST_ASSERT( cb.data == "" );
TestEnd:
    TEST_ASSERT( MI_RESULT_OK == Http_Delete(http) );
}
NitsEndTest

BEGIN_EXTERNC
static void _ConnectToServerExpectConnectionDrop(const string& data, MI_Uint32 sleepInsideSendMS)
{
    Sock sock;
    MI_Result r;

    // Initialize address (connect using loopback).
    sock = SockConnectLocal(PORT);

    size_t sent = 0;
    size_t size_left = data.size();
    const char* buf = data.c_str();

    while ( size_left )
    {
        size_t wantToSend = size_left;

        /* send all but last bytes; sleep before sending last byte */
        if (wantToSend > 1)
        {
            wantToSend--;
        }
        else
        {
            /* sleep before sending last byte */
            ut::sleep_ms(sleepInsideSendMS);
        }

        r = Sock_Write(sock, buf, wantToSend, &sent);
        
        //if (r != MI_RESULT_OK)
            //printf("errno %d\n", errno);

        TEST_ASSERT(r == MI_RESULT_OK ||
            (r == MI_RESULT_FAILED && 1 == wantToSend) );
        //printf("s: %d\n", (int)sent);

        if (0 == sent)
            break;

        size_left -= sent;
        buf += sent;
    }


    if (sent != 0)
    {
        // read response
        char r_buf[1024];
        size_t read = 0;
        int err;

        do
        {
            r = Sock_Read(sock, r_buf, sizeof(r_buf), &read);
            err = Sock_GetLastError();
        }
#if defined(macos)
        while (r != MI_RESULT_OK && (err == EAGAIN || err == EDEADLK));
#else
        while (r != MI_RESULT_OK && err == EAGAIN);
#endif
        //printf("s,r: %d, res = %d\n", (int)read, (int)r);

        TEST_ASSERT(r == MI_RESULT_OK || r == MI_RESULT_FAILED);
        TEST_ASSERT(read == 0);
    }

    // this is a negative case; so as long as we did not crash or hang
    // we are fine to ignore the error
    NitsIgnoringError();

    Sock_Close(sock);
}
END_EXTERNC


NitsTestWithSetup(TestHttp_HeaderTooBig, TestHttpSetup)
{    
    CallbackStruct cb;
    
    // send huge http header and expecting connection to be dropped
    if(!TEST_ASSERT(MI_RESULT_OK == _StartHTTP_Server(        
        _callback2,
        &cb,
        NULL,
        0)))
        return;

    string data = 
        "POST /wsman HTTP/1.1\r\n"
        "Content-Type: ct\r\n"
        "User-Agent: Microsoft WinRM Client\r\n"
        "Host: localhost:7778\r\n"
        "Content-Length: 5\r\n"
        "Authorization: auth\r\n";

    data += string("hugeAttribute: ") + string(MAX_HEADER_SIZE, 'x') + string("\r\n");
    data += "\r\n"
        "Hello";

    _ConnectToServerExpectConnectionDrop(data, 0);

    _StopHTTP_Server();
}
NitsEndTest

NitsTestWithSetup(TestHttp_TimeoutMidPacket, TestHttpSetup)
{
    CallbackStruct cb;
    HttpOptions options = {1000};   /* 1 ms */

    // send http header with delay in the middle of the package and expecting connection to be dropped
    if (!TEST_ASSERT(MI_RESULT_OK == _StartHTTP_Server(        
        _callback2,
        &cb,
        NULL,
        &options)))
        return;

    string data = 
        "POST /wsman HTTP/1.1\r\n"
        "Content-Type: ct\r\n"
        "User-Agent: Microsoft WinRM Client\r\n"
        "Host: localhost:7778\r\n"
        "Content-Length: 5\r\n"
        "Authorization: auth\r\n"
        "\r\n"
        "Hello";

    _ConnectToServerExpectConnectionDrop(data, 1000);

    _StopHTTP_Server();
}
NitsEndTest

NitsTestWithSetup(TestHttp_LongContent, TestHttpSetup)
{
    CallbackStruct cb;
    HttpOptions options = {1000};   /* 1 ms */

    // send http header with delay in the middle of the package and expecting connection to be dropped
    if (!TEST_ASSERT(MI_RESULT_OK == _StartHTTP_Server(        
        _callback2,
        &cb,
        NULL,
        &options)))
        return;

    string data = 
        "POST /wsman HTTP/1.1\r\n"
        "Content-Type: ct\r\n"
        "User-Agent: Microsoft WinRM Client\r\n"
        "Host: localhost:7778\r\n"
        "Content-Length: 5\r\n"
        "Authorization: auth\r\n"
        "\r\n"
        "Hello (this part of the message is not accounted for n content-length and may cause buffer overrun)";

    _ConnectToServerExpectConnectionDrop(data, 100);

    _StopHTTP_Server();
}
NitsEndTest

#ifdef CONFIG_POSIX

NitsTestWithSetup(TestHttp_ValidCipherList, TestHttpSetup)
{
    CallbackStruct cb;
    HttpOptions options = {1000};   /* 1 ms */

    if (!TEST_ASSERT(MI_RESULT_OK == _StartHTTP_Server(        
        _callback2,
        &cb,
        "DES-CBC3-SHA:AES256-SHA256",
        &options)))
        NitsReturn;

    _StopHTTP_Server();

    NitsReturn;
}
NitsEndTest

#endif
