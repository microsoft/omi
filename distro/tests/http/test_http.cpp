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
#include <sock/thread.h>
#include <http/http.h>
#include <base/result.h>

static MI_Uint16 PORT = ut::getUnittestPortNumber() + 10;

using namespace std;

/*************************************/
/* local data */
static  Http* s_http;
static bool s_stop;
static ThreadHandle s_t;

#if defined(_MSC_VER)
#undef BEGIN_EXTERNC
#undef END_EXTERNC
#define BEGIN_EXTERNC
#define END_EXTERNC
#endif

static void setUp()
{
    PORT++;
}

static void cleanup()
{
}
 /* helper functions */
BEGIN_EXTERNC
static void* MI_CALL _HTTPServerProc(void* )
{
    Sock_Start();
    // pump messages
    for (; !s_stop; )
        Http_Run(s_http, 20000);

    Sock_Stop();
    return 0;
}
END_EXTERNC

BEGIN_EXTERNC
static void _StartHTTP_Server(
    HttpCallbackOnNewConnection callbackOnNewConnection,
    HttpCallbackOnCloseConnection callbackOnCloseConnection,
    HttpCallbackOnRequest callbackOnRequest,
    void* callbackData,
    const HttpOptions* options = 0)
{
    /* create a server */
    UT_ASSERT( MI_RESULT_OK == Http_New_Server(
        &s_http, 0, PORT, 0, NULL,
        callbackOnNewConnection,
        callbackOnCloseConnection,
        callbackOnRequest, callbackData) );

    if (options)
    {
        UT_ASSERT( MI_RESULT_OK == Http_SetOptions(
            s_http, options) );
    }

    /* create a thread for message consumption */
    s_stop = false;

    UT_ASSERT(MI_RESULT_OK == Thread_Create(
        _HTTPServerProc, 0, &s_t));

}
END_EXTERNC

BEGIN_EXTERNC
static void _StopHTTP_Server()
{
    s_stop = true;
    UT_ASSERT(MI_RESULT_OK == Thread_Destroy( s_t, MI_TRUE ));
    UT_ASSERT( MI_RESULT_OK == Http_Delete(s_http) );

    s_t = 0;
    s_http = 0;
    s_stop = false;
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
    UT_ASSERT(r == MI_RESULT_OK);

    // Create client socket.
    r = Sock_Create(&sock, MI_FALSE);
    UT_ASSERT(r == MI_RESULT_OK);

    r = Sock_Connect(sock, &addr);
    UT_ASSERT(r == MI_RESULT_OK);
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
            printf("size_left %d, r %d, want write %d, sent %d, le %d\n", (int)size_left, (int)r, (int)wantToSend, (int)sent, Sock_GetLastError());
        ut::sleep_ms( 7000 );

        }

        UT_ASSERT(r == MI_RESULT_OK);
//        printf("s: %d\n", (int)sent);
        size_left -= sent;
        buf += sent;
        ut::sleep_ms( 1 );
    }

    // read response
    char r_buf[1024];
    size_t read = 0;
    r = Sock_Read(sock, r_buf, sizeof(r_buf), &read);


    if (r) printf("s,r: %d, err %d\n", (int)read, Sock_GetLastError());

    UT_ASSERT(r == MI_RESULT_OK);

    p->response = string(r_buf, r_buf + read);

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
        ex.m_testcase = "--http_client_proc"; testFailed(ex);
    }
    return 0;
}
END_EXTERNC

struct CallbackStruct
{
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
static void _HttpCallbackOnNewConnection(
    Http* /*http*/,
    void* /*callbackData*/,
    void* httpConnectionHandle,
    void** connectionData)
{
    *connectionData = httpConnectionHandle;
}
END_EXTERNC

BEGIN_EXTERNC
static void _HttpCallbackOnCloseConnection(
    Http* /*http*/,
    void* /*callbackData*/,
    void* /*connectionData*/)
{
}
END_EXTERNC

BEGIN_EXTERNC
static void _HttpCallbackOnRequest(
    Http* http,
    void* callbackData,
    void* connectionData,
    void* httpConnectionHandle,
    const HttpHeaders* headers,
    Page** page)
{
    CallbackStruct* data = (CallbackStruct*)callbackData;

    UT_ASSERT(httpConnectionHandle == connectionData);

    if (headers->contentType)
        data->contentType = headers->contentType;

    if (headers->charset)
        data->charset = headers->charset;

    if (headers->authorization)
        data->authorization = headers->authorization;
    if (headers->username)
        data->username = headers->username;
    if (headers->password)
        data->password = headers->password;

    data->contentLength = headers->contentLength;

    data->data = string( (char*) ((*page)+1), ((char*)((*page)+1)) + (*page)->u.s.size);

    Page* rsp = (Page*)malloc(sizeof(Page) + data->response.size());

    UT_ASSERT(rsp);

    rsp->u.s.size = data->response.size();
    memcpy(rsp+1, data->response.c_str(), data->response.size());

    Http_SendResponse( http, httpConnectionHandle, HTTP_ERROR_CODE_OK, &rsp );

    if (rsp )
        free(rsp);
}
END_EXTERNC

static void TestHttpHappyPass()
{
    Http* http = 0;
    CallbackStruct cb;

    cb.response = "Response";

    /* create a server */
    UT_ASSERT( MI_RESULT_OK == Http_New_Server(
        &http, 0, PORT, 0, NULL,
        _HttpCallbackOnNewConnection,
        _HttpCallbackOnCloseConnection,
        _HttpCallbackOnRequest, &cb) );


    /* create a client */
    ThreadParam param;
    ThreadHandle t;

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

    UT_ASSERT(MI_RESULT_OK == Thread_Create(
        http_client_proc, &param, &t));


    // pump messages
    for (int i = 0; !param.gotRsp && i < 1000; i++ )
        Http_Run(http, 20000);

    // wait for completion and check that
    UT_ASSERT(MI_RESULT_OK == Thread_Destroy( t, MI_TRUE ));


    // check messages

    UT_ASSERT( cb.authorization == "auth" );
    UT_ASSERT( cb.contentType == "application/soap+xml" );
    UT_ASSERT( cb.charset == "UTF-8" );
    UT_ASSERT( cb.contentLength == 5 );
    UT_ASSERT( cb.data == "Hello" );

    //UT_ASSERT( param.response.find("Response") != string::npos );

    UT_ASSERT( MI_RESULT_OK == Http_Delete(http) );
}

static void TestHttp_BigLoad()
{
    Http* http = 0;
    CallbackStruct cb;

    cb.response = string(256 * 1024, '*');


    /* create a server */
    UT_ASSERT( MI_RESULT_OK == Http_New_Server(
        &http, 0, PORT, 0, NULL,
        _HttpCallbackOnNewConnection,
        _HttpCallbackOnCloseConnection,
        _HttpCallbackOnRequest, &cb) );


    /* create a client */
    ThreadParam param;
    ThreadHandle t;

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

    UT_ASSERT(MI_RESULT_OK == Thread_Create(
        http_client_proc, &param, &t));


    // pump messages
    for (int i = 0; !param.gotRsp && i < 1000; i++ )
        Http_Run(http, 20000);

    //printf("out of run\n");

    // wait for completion and check that
    UT_ASSERT(MI_RESULT_OK == Thread_Destroy( t, MI_TRUE ));


    // check messages

    UT_ASSERT( cb.authorization == "auth" );
    UT_ASSERT( cb.password == "" );
    UT_ASSERT( cb.username == "" );
    UT_ASSERT( cb.contentType == "text" );
    UT_ASSERT( cb.charset == "" );
    UT_ASSERT( cb.contentLength == 32999 );
    UT_ASSERT( cb.data == string(32999, '.') );

    //UT_ASSERT( param.response.find("Response") != string::npos );

    UT_ASSERT( MI_RESULT_OK == Http_Delete(http) );
}

static void TestHttp_QuotedCharset()
{
    Http* http = 0;
    CallbackStruct cb;

    cb.response = "Response";

    /* create a server */
    UT_ASSERT( MI_RESULT_OK == Http_New_Server(
        &http, 0, PORT, 0, NULL,
        _HttpCallbackOnNewConnection,
        _HttpCallbackOnCloseConnection,
        _HttpCallbackOnRequest, &cb) );


    /* create a client */
    ThreadParam param;
    ThreadHandle t;

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

    UT_ASSERT(MI_RESULT_OK == Thread_Create(
        http_client_proc, &param, &t));


    // pump messages
    for (int i = 0; !param.gotRsp && i < 1000; i++ )
        Http_Run(http, 20000);

    // wait for completion and check that
    UT_ASSERT(MI_RESULT_OK == Thread_Destroy( t, MI_TRUE ));


    // check messages

    UT_ASSERT( cb.authorization == "auth" );
    UT_ASSERT( cb.contentType == "application/soap+xml" );
    UT_ASSERT( cb.charset == "UTF-16" );
    UT_ASSERT( cb.contentLength == 5 );
    UT_ASSERT( cb.data == "aloha" );

    //UT_ASSERT( param.response.find("Response") != string::npos );

    UT_ASSERT( MI_RESULT_OK == Http_Delete(http) );
}

static void TestHttp_Base64Decoding()
{
    Http* http = 0;
    CallbackStruct cb;

    cb.response = "Response";

    /* create a server */
    UT_ASSERT( MI_RESULT_OK == Http_New_Server(
        &http, 0, PORT, 0, NULL,
        _HttpCallbackOnNewConnection,
        _HttpCallbackOnCloseConnection,
        _HttpCallbackOnRequest, &cb) );


    /* create a client */
    ThreadParam param;
    ThreadHandle t;

    param.messageToSend =
        "POST /wsman HTTP/1.1\r\n"
        "Content-Type: application/soap+xml;  \tcharset=\"UTF-16\"\t \r\n"
        "User-Agent: Microsoft WinRM Client\r\n"
        "Host: localhost:7778\r\n"
        "Content-Length: 5\r\n"
        "Authorization:    Basic \t \tcm9vdDpPcHNNZ3IyMDA3UjI=\t \r\n"
        "\r\n"
        "aloha";
    param.bytesToSendPerOperation = 30000;
    param.gotRsp = false;

    UT_ASSERT(MI_RESULT_OK == Thread_Create(
        http_client_proc, &param, &t));


    // pump messages
    for (int i = 0; !param.gotRsp && i < 1000; i++ )
        Http_Run(http, 20000);

    // wait for completion and check that
    UT_ASSERT(MI_RESULT_OK == Thread_Destroy( t, MI_TRUE ));


    // check messages

    UT_ASSERT( cb.authorization == "" );
    UT_ASSERT( cb.username == "root" );
    UT_ASSERT( cb.password == "OpsMgr2007R2" );
    UT_ASSERT( cb.contentType == "application/soap+xml" );
    UT_ASSERT( cb.charset == "UTF-16" );
    UT_ASSERT( cb.contentLength == 5 );
    UT_ASSERT( cb.data == "aloha" );

    //UT_ASSERT( param.response.find("Response") != string::npos );

    UT_ASSERT( MI_RESULT_OK == Http_Delete(http) );
}

static void TestHttp_InvalidBase64Data()
{
    Http* http = 0;
    CallbackStruct cb;

    cb.response = "Response";

    /* create a server */
    UT_ASSERT( MI_RESULT_OK == Http_New_Server(
        &http, 0, PORT, 0, NULL,
        _HttpCallbackOnNewConnection,
        _HttpCallbackOnCloseConnection,
        _HttpCallbackOnRequest, &cb) );


    /* create a client */
    ThreadParam param;
    ThreadHandle t;

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

    UT_ASSERT(MI_RESULT_OK == Thread_Create(
        http_client_proc, &param, &t));


    // pump messages
    for (int i = 0; !param.gotRsp && i < 1000; i++ )
        Http_Run(http, 20000);

    // wait for completion and check that
    UT_ASSERT(MI_RESULT_OK == Thread_Destroy( t, MI_TRUE ));

    // check messages

    UT_ASSERT( param.response.empty() );
    UT_ASSERT( cb.authorization == "" );
    UT_ASSERT( cb.username == "" );
    UT_ASSERT( cb.password == "" );
    UT_ASSERT( cb.contentType == "" );
    UT_ASSERT( cb.charset == "" );
    UT_ASSERT( cb.contentLength == 0 );
    UT_ASSERT( cb.data == "" );

    UT_ASSERT( MI_RESULT_OK == Http_Delete(http) );
}

BEGIN_EXTERNC
static void _HttpCallbackOnRequest_NeverCalled(
    Http* ,
    void* ,
    void* ,
    void* ,
    const HttpHeaders* ,
    Page** )
{
    UT_ASSERT_FAILED_MSG("should be never called");
}
END_EXTERNC

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

    while (size_left != 0)
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

        UT_ASSERT(r == MI_RESULT_OK || (r == MI_RESULT_FAILED && wantToSend == 1));
        //printf("s: %d\n", (int)sent);

        if (sent == 0)
            break;

        size_left -= sent;
        buf += sent;
    }


    if (sent != 0)
    {
        // read response
        char r_buf[1024];
        size_t read = 0;
        r = Sock_Read(sock, r_buf, sizeof(r_buf), &read);
        //printf("s,r: %d, res = %d\n", (int)read, (int)r);

        UT_ASSERT(r == MI_RESULT_OK || r == MI_RESULT_FAILED);
        UT_ASSERT(read == 0);
    }

    Sock_Close(sock);
}
END_EXTERNC


static void TestHttp_HeaderTooBig()
{
    // send huge http header and expecting connection to be dropped
    _StartHTTP_Server(
        _HttpCallbackOnNewConnection,
        _HttpCallbackOnCloseConnection,
        _HttpCallbackOnRequest_NeverCalled,
        0);

    string data =
        "POST /wsman HTTP/1.1\r\n"
        "Content-Type: ct\r\n"
        "User-Agent: Microsoft WinRM Client\r\n"
        "Host: localhost:7778\r\n"
        "Content-Length: 5\r\n"
        "Authorization: auth\r\n";

    data += string("hugeAttribute: ") + string(4096, 'x') + string("\r\n");
    data += "\r\n"
        "Hello";

    _ConnectToServerExpectConnectionDrop(data, 0);

    _StopHTTP_Server();
}

static void TestHttp_TimeoutMidPacket()
{
    HttpOptions options = {1000};   /* 1 ms */

    // send http header with delay in the middle of the package and expecting connection to be dropped
    _StartHTTP_Server(
        _HttpCallbackOnNewConnection,
        _HttpCallbackOnCloseConnection,
        _HttpCallbackOnRequest_NeverCalled,
        0,
        &options);

    string data =
        "POST /wsman HTTP/1.1\r\n"
        "Content-Type: ct\r\n"
        "User-Agent: Microsoft WinRM Client\r\n"
        "Host: localhost:7778\r\n"
        "Content-Length: 5\r\n"
        "Authorization: auth\r\n"
        "\r\n"
        "Hello";

    _ConnectToServerExpectConnectionDrop(data, 100);

    _StopHTTP_Server();
}

static void TestHttp_LongContent()
{
    HttpOptions options = {1000};   /* 1 ms */

    // send http header with delay in the middle of the package and expecting connection to be dropped
    _StartHTTP_Server(
        _HttpCallbackOnNewConnection,
        _HttpCallbackOnCloseConnection,
        _HttpCallbackOnRequest_NeverCalled,
        0,
        &options);

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


static void RunTests()
{
    Sock_Start();

    UT_TEST(TestHttp_BigLoad);
    UT_TEST(TestHttpHappyPass);
    UT_TEST(TestHttp_QuotedCharset);
    UT_TEST(TestHttp_Base64Decoding);
    UT_TEST(TestHttp_HeaderTooBig);
    UT_TEST(TestHttp_TimeoutMidPacket);
    UT_TEST(TestHttp_InvalidBase64Data);
    UT_TEST(TestHttp_LongContent);

    Sock_Stop();
}

UT_ENTRY_POINT(RunTests);
