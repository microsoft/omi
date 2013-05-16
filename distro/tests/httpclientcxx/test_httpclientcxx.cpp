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

#include <stdio.h>
#include <limits.h>
#include <sys/socket.h>

#include <vector>
#include <map>
#include <cstdlib>

#include <ut/ut.h>
#include <http/httpclient.h>
#include <http/http.h>
#include <sock/thread.h>
#include <base/paths.h>
#include <base/result.h>
#ifdef CONFIG_POSIX
#include <httpclientcxx/httpclientcxx.h>
#endif

#ifdef CONFIG_POSIX

using namespace std;

#if !defined PATH_MAX   // Some HP-UX's don't define PATH_MAX in <limits.h> unless you specify several symbols before including it
# define PATH_MAX _XOPEN_PATH_MAX
#endif
#endif

/*********************************** HTTP server ***************************/

#if defined(_MSC_VER)
#undef BEGIN_EXTERNC
#undef END_EXTERNC
#define BEGIN_EXTERNC
#define END_EXTERNC
#endif

/* local data */
static Http* s_http;
static bool s_stop;
static ThreadHandle s_t;
static MI_Uint16 PORT = ut::getUnittestPortNumber() + 100;
static string s_contentType;
static string s_charset;
static string s_content;
static string s_response;
static bool s_delayServerResponse = false;
static int s_httpCode;

static map< string, string > s_headers;
static string s_contentReceivedFromServer;
static int s_cxxError;
static bool s_httpResponseReceived;

static void setUp()
{
    s_httpResponseReceived = false;
    s_response = "";
    s_contentType = "";
    s_delayServerResponse = false;

    s_httpCode = 0;
    s_headers.clear();
    s_contentReceivedFromServer.clear();
    s_cxxError = -1;
}

static void cleanup()
{
}

/* helper functions */
static int lockIsInitialized = 0;
static pthread_mutex_t serverProcLock;

BEGIN_EXTERNC
static void* MI_CALL _HTTPServerProc(void*)
{
    if (lockIsInitialized == 0)
    {
        pthread_mutex_init(&serverProcLock, NULL);
        lockIsInitialized = 1;
    }

    pthread_mutex_lock(&serverProcLock);

    Sock_Start();

    // pump messages.  Make sure we do at least 1000 to try and get an asnwer back
    for (int i = 0; i < 1000 && !s_stop; i++)
    {
        if (i % 100 == 0)
        {
            printf("Be patient. HTTPServerProc processing checking result try %d / 1,000\n", i);
        }

        MI_Result res = Http_Run(s_http, 20000);

        if (res != MI_RESULT_OK && res != MI_RESULT_TIME_OUT)
        {
            printf("Gnarly, dude. HTTPServerProc breaking for result = %d on iteration %d\n", res, i);
            break;
        }
    }

    Sock_Stop();

    pthread_mutex_unlock(&serverProcLock);
    return 0;
}
END_EXTERNC

BEGIN_EXTERNC
static void _StartHTTP_Server(
    HttpCallbackOnNewConnection callbackOnNewConnection,
    HttpCallbackOnCloseConnection callbackOnCloseConnection,
    HttpCallbackOnRequest callbackOnRequest,
    void* callbackData,
    const HttpOptions* options = NULL)
{
    /* create a server */
    UT_ASSERT( MI_RESULT_OK == Http_New_Server(
        &s_http, 0, PORT, PORT + 1, NULL,
        callbackOnNewConnection,
        callbackOnCloseConnection,
        callbackOnRequest, callbackData) );

    if (options != NULL)
    {
        UT_ASSERT( MI_RESULT_OK == Http_SetOptions(s_http, options) );
    }

    /* create a thread for message consumption */
    s_stop = false;

    UT_ASSERT(MI_RESULT_OK == Thread_Create(_HTTPServerProc, 0, &s_t));
}
END_EXTERNC

BEGIN_EXTERNC
static void _StopHTTP_Server()
{
    MI_Result r;

    s_stop = true;
    r = Thread_Destroy(s_t, MI_TRUE);
    if (r != MI_RESULT_OK)
    {
        printf("_StopHTTP_Server - Thread_Destroy returned error: %d\n", r);
    }
    r = Http_Delete(s_http);
    if (r != MI_RESULT_OK)
    {
        printf("_StopHTTP_Server - Http_Delete returned error: %d\n", r);
    }

    s_t = 0;
    s_http = 0;
    s_stop = false;
    return;
}
END_EXTERNC

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
    void* /*callbackData*/,
    void* connectionData,
    void* httpConnectionHandle,
    const HttpHeaders* headers,
    Page** page)
{
    UT_ASSERT(httpConnectionHandle == connectionData);

    // printf("cbt, %s\n", headers->authorization);

    if (headers->contentType != NULL)
        s_contentType = headers->contentType;
    else
        s_contentType = "";

    if (headers->charset != NULL)
        s_charset = headers->charset;
    else
        s_charset = "";

    if (page != NULL && *page != NULL)
        s_content = string( (char*) ((*page)+1), ((char*)((*page)+1)) + (*page)->u.s.size);
    else
        s_content.clear();

    Page* rsp = (Page*)malloc(sizeof(Page) + s_response.size());

    UT_ASSERT(rsp != NULL);

    rsp->u.s.size = s_response.size();
    memcpy(rsp + 1, s_response.c_str(), s_response.size());

    if (s_delayServerResponse)
    {
        sched_yield();
        ut::sleep_ms(175);
    }

    Http_SendResponse(http, httpConnectionHandle, HTTP_ERROR_CODE_OK, &rsp);

    if (rsp != NULL)
    {
        free(rsp);
        rsp = NULL;
    }
}
END_EXTERNC

/************************************* HTTP client **********************/

BEGIN_EXTERNC
static void SetHttpHeaderInformation(map< string, string > headers, int httpCode)
{
    s_headers = headers;
    s_httpCode = httpCode;
    return;
}

static int GetHttpCode()
{
    return s_httpCode;
}
END_EXTERNC

#if 0

/* Simplified HTTP client for chunked stuff testing */
struct ThreadSrvParam
{
    string messageToSend;
    size_t  bytesToSendPerOperation;
    bool started;

    ThreadSrvParam():
        bytesToSendPerOperation(0),
        started(false)
    {
    }
};

/* simple HTTP server */
static void* MI_CALL _http_server_proc(void* param)
{
    ThreadSrvParam* p = (ThreadSrvParam*)param;

    Addr addr;
    Sock sock, listener;
    MI_Result r;

    Sock_Start();

    // Initialize address (connect using loopback).
    Addr_InitAny(&addr, PORT+2);
    UT_ASSERT_EQUAL(Sock_CreateListener(&listener, &addr), MI_RESULT_OK);
    UT_ASSERT_EQUAL(Sock_SetBlocking(listener, MI_FALSE), MI_RESULT_OK);

    p->started = true;

    // accept incoming request
    for (int i = 0; ; i++)
    {
        // check if we waited too long
        UT_ASSERT(i < 1000);

        r = Sock_Accept(listener, &sock, &addr);

        if (r == MI_RESULT_WOULD_BLOCK)
        {
            ut::sleep_ms(20);
            continue;
        }

        UT_ASSERT_EQUAL(r, MI_RESULT_OK);

        r = Sock_SetBlocking(sock, false);
        UT_ASSERT_EQUAL(r, MI_RESULT_OK);

        break;
    }

    // close listener
    Sock_Close(listener);

    // read and ignore HTTP request
    char r_buf[1024];
    size_t read = 0;
    r = Sock_Read(sock, r_buf, sizeof(r_buf), &read);
    // if (r) printf("s,r: %d, err %d\n", (int)read, Sock_GetLastError());

    // send pre-defined response

    size_t sent = 0;
    size_t size_left = p->messageToSend.size();
    const char* buf = p->messageToSend.c_str();

    while (size_left != 0)
    {
        ut::sleep_ms(1);

        size_t wantToSend = min(p->bytesToSendPerOperation, size_left);
        r = Sock_Write(sock, buf, wantToSend, &sent);

        // printf("size_left %lu, r %d, sent %lu, want-send %lu\n", size_left, r, sent, wantToSend);
        if (r != MI_RESULT_OK)
        {
            break;
        }

        UT_ASSERT(r == MI_RESULT_OK);
        size_left -= sent;
        buf += sent;
    }

    Sock_Close(sock);

    Sock_Stop();
    return 0;
}

BEGIN_EXTERNC
static void* MI_CALL http_server_proc(void* param)
{
    try
    {
        return _http_server_proc(param);
    }
    catch (ut::UnittestException ex)
    {
        ex.m_testcase = "--http_server_proc"; testFailed(ex);
    }
    return 0;
}
END_EXTERNC

#endif

class OnData : public httpclient::HttpClientCallback
{
public:
    virtual void OnStatus(
        httpclient::Result res)
    {
        // printf("on status %d\n", (int)res);
        s_cxxError = (int)res;
    }

    virtual bool OnResponseHeader(
        int httpError,
        const std::map< std::string, std::string >& headers,
        int contentLength)
    {
        SetHttpHeaderInformation(headers, httpError);
        return true;
    }

    virtual bool OnResponseData(
        const std::vector< unsigned char >& data,
        bool lastChunk)
    {
        if (!data.empty())
            s_contentReceivedFromServer +=
                string( (const char*)&data[0], (const char*)&data[0] + data.size());

        return true;
    }

    virtual ~OnData()
    {
    }
};

static void TestHttpClientCxx_BasicOperations()
{
    OnData handler;
    httpclient::HttpClient cl(&handler);

    std::map< std::string, std::string > headers;

    headers["Host"] = "host";
    headers["Content-Type"] = "text/html";

    /* content to send to the client */
    s_response = "Test";

    UT_ASSERT_EQUAL(httpclient::OKAY, cl.Connect("127.0.0.1", PORT, false, NULL, NULL, NULL));

    std::vector< unsigned char > data;
    data.clear();
    UT_ASSERT_EQUAL(httpclient::OKAY, cl.StartRequest("GET", "/", headers, data, true));
    sched_yield();
    usleep(300000);

    // verify results:
    UT_ASSERT_EQUAL(GetHttpCode(), 200);
    UT_ASSERT_EQUAL(s_headers["Content-Type"], "application/soap+xml;charset=UTF-8");
    UT_ASSERT_EQUAL(s_contentReceivedFromServer, string("Test"));
    UT_ASSERT_EQUAL(s_contentType, string("text/html"));
}

static void TestHttpClientCxx_PostData()
{
    OnData handler;
    httpclient::HttpClient cl(&handler);

    std::map< std::string, std::string > headers;
    const unsigned char c_msg[] = "Hello";

    headers["Host"] = "host";

    /* content to send to the client */
    s_response = "Test";

    UT_ASSERT_EQUAL(httpclient::OKAY, cl.Connect("127.0.0.1", PORT, false, NULL, NULL, NULL));

    std::vector< unsigned char > data;
    data.push_back('H');
    data.push_back('e');
    data.push_back('l');
    data.push_back('l');
    data.push_back('o');
    data.push_back('\0');
    UT_ASSERT_EQUAL(httpclient::OKAY, cl.StartRequest("POST", "/", headers, data, true));

    /*
    for (int i = 0; i < 1000 && !s_httpResponseReceived; i++)
        HttpClient_Run(http, 20000);
    */

    // verify results:
    UT_ASSERT_EQUAL(s_httpCode, 200);
    UT_ASSERT_EQUAL(s_headers["Content-Type"], "application/soap+xml;charset=UTF-8");
    UT_ASSERT_EQUAL(s_content, string((const char*)c_msg, ((const char*)c_msg) + sizeof(c_msg)));
/*
    UT_ASSERT_EQUAL(MI_RESULT_OK, HttpClient_Delete(http));

    http = NULL;
*/

}

static void TestHttpClientCxx_TestObjectDtor()
{
    OnData handler;
    httpclient::HttpClient cl(&handler);

    std::map< std::string, std::string > headers;
    // const unsigned char c_msg[] = "Hello";

    headers["Host"] = "host";

    UT_ASSERT_EQUAL(httpclient::OKAY, cl.Connect("127.0.0.1", PORT, false, NULL, NULL, NULL));

    std::vector< unsigned char > data;
    data.push_back('H');
    data.push_back('e');
    data.push_back('l');
    data.push_back('l');
    data.push_back('o');
    data.push_back('\0');
    UT_ASSERT_EQUAL(httpclient::OKAY, cl.StartRequest("POST", "/", headers, data, false));

    // in case if dtor does not close HTTP handle properly, test will crash
}

#if 0

static void TestHttpClientCxx_ChunkedResponse()
{
    OnData handler;
    httpclient::HttpClient cl(&handler);

    std::map< std::string, std::string > headers;

    /* create a server */
    ThreadSrvParam param;
    ThreadHandle t;

    /* content to send to the client */
    param.messageToSend =
    /* header */
    "HTTP/1.1 200 OK\r\n"
    "transfer-encoding: chunked\r\n"
    "Connection: Keep-Alive\r\n"
    "Content-Type: application/soap+xml;charset=UTF-8\r\n"
    "\r\n"

    /* chunk 1 */
    "1 \r\n"
    "T\r\n"

    /* chunk 2 */
    "3 \r\n"
    "est\r\n"

    /* last chunk */
    "0 \r\n"
    "\r\n"
        ;

    param.bytesToSendPerOperation = 10240;

    UT_ASSERT(MI_RESULT_OK == Thread_Create(http_server_proc, &param, &t));

    for (int i = 0; !param.started; i++)
    {
        // check if we waited too long
        UT_ASSERT(i < 1000);

        ut::sleep_ms(20);
    }

    UT_ASSERT_EQUAL(httpclient::OKAY,cl.Connect("127.0.0.1", PORT + 2, false, NULL));

    std::vector< unsigned char > data;
    data.clear();
    UT_ASSERT_EQUAL(httpclient::OKAY, cl.StartRequest("GET", "/", headers, data, true));

    // wait for completion and check that
    UT_ASSERT(MI_RESULT_OK == Thread_Destroy(t, MI_TRUE));

    // verify results:
    UT_ASSERT_EQUAL(s_httpCode, 200);
    UT_ASSERT_EQUAL(s_headers["Content-Type"], "application/soap+xml;charset=UTF-8");
    UT_ASSERT_EQUAL(s_contentReceivedFromServer, string("Test"));
}

static void TestHttpClientCxx_TestTimeout()
{
    OnData handler;
    {
    httpclient::HttpClient cl(&handler);

    std::map< std::string, std::string > headers;
    const unsigned char c_msg[] = "Hello";

    headers["Host"] = "host";

    /* content to send to the client */
    s_response = "Test";
    s_delayServerResponse = true;

    cl.SetOperationTimeout(500);
    UT_ASSERT_EQUAL(httpclient::OKAY, cl.Connect("127.0.0.1", PORT, false, NULL, NULL, NULL));

    std::vector< unsigned char > data(c_msg, c_msg + sizeof(c_msg));
    UT_ASSERT_EQUAL(httpclient::OKAY, cl.StartRequest("POST", "/", headers, data, false));

    for (int i = 0; i < 1000 && s_cxxError == -1; i++)
    {
        sched_yield();
        ut::ms_sleep(20000);
    }

    // verify results:
    UT_ASSERT(s_cxxError == httpclient::TIMEOUT || s_cxxError == httpclient::FAILED);
    }
    usleep(100000);     // let the destructor for cl called by the '}' finish
}

#endif

static void RunTests()
{
#ifdef CONFIG_POSIX
    Sock_Start();
    _StartHTTP_Server(
        _HttpCallbackOnNewConnection,
        _HttpCallbackOnCloseConnection,
        _HttpCallbackOnRequest,
        0);
    UT_TEST(TestHttpClientCxx_BasicOperations);
    UT_TEST(TestHttpClientCxx_PostData);
#if 0
    UT_TEST(TestHttpClientCxx_TestObjectDtor);
    UT_TEST(TestHttpClientCxx_TestTimeout);
    UT_TEST(TestHttpClientCxx_ChunkedResponse);
#endif

    _StopHTTP_Server();
    Sock_Stop();

#endif
}

UT_ENTRY_POINT(RunTests);
