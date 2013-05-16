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

using namespace std;

#if !defined PATH_MAX   // Some HP-UX's don't define PATH_MAX in <limits.h> unless you specify several symbols before including it
# define PATH_MAX _XOPEN_PATH_MAX
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
    s_stop = true;
    UT_ASSERT(MI_RESULT_OK == Thread_Destroy(s_t, MI_TRUE));
    UT_ASSERT(MI_RESULT_OK == Http_Delete(s_http));

    s_t = 0;
    s_http = 0;
    s_stop = false;
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
static void _HttpClientCallbackOnStatus(
    HttpClient* http,
    void* callbackData,
    MI_Result result)
{
    MI_UNUSED(http);
    MI_UNUSED(callbackData);
    MI_UNUSED(result);
    s_httpResponseReceived = true;

    // printf("  HTTP Response Received.  Status is %d\n", s_httpCode);
}

static MI_Boolean _HttpClientCallbackOnResponse(
    HttpClient* http,
    void* callbackData,
    const HttpClientResponseHeader* headers,
    MI_Sint64 contentSize,
    MI_Boolean  lastChunk,
    Page** data)
{
    MI_UNUSED(http);
    MI_UNUSED(callbackData);
    MI_UNUSED(headers);
    MI_UNUSED(contentSize);
    MI_UNUSED(lastChunk);

    // printf("****************************************\n");
    // printf("Got into HttpClientCallbackOnResponse:  \n");
    if (headers != NULL)
    {
        s_httpCode = headers->httpError;
        if (s_httpCode != 200)
        {
            printf("    Error code = %d\n", s_httpCode);
        }

        for (unsigned int i = 0; i < headers->sizeHeaders; i++)
        {
            s_headers[headers->headers[i].name] = headers->headers[i].value;
        }
    }

    if (data != NULL && *data != NULL)
    {
        char *StartPos = (char *)((*data)+1);
        int  len = (*data)->u.s.size;
        // char *EndPos = StartPos + len;

        s_contentReceivedFromServer += std::string(StartPos, len);

        // printf("    Response string = %s\n", s_contentReceivedFromServer.c_str());
    }

    // printf("****************************************\n");
    return MI_TRUE;
}
END_EXTERNC

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
        UT_ASSERT(i < 10000);

        r = Sock_Accept(listener, &sock, &addr);

        if (r == MI_RESULT_WOULD_BLOCK)
        {
            sched_yield();
            ut::sleep_ms(50);
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

static void TestHttpClient_BasicOperations()
{
    HttpClient* http = 0;
    const char* header_strings[] = {
        "Content-Type: text/html",
        //"User-Agent: xplat http cleint" ,
        "Host: host"
    };

    /* content to send to the client */
    s_response = "Test";

    HttpClientRequestHeaders headers = {
        header_strings,
        MI_COUNT(header_strings) };

    UT_ASSERT_EQUAL(MI_RESULT_OK,
        HttpClient_New_Connector(&http, 0, "127.0.0.1", PORT, MI_FALSE,
                                 _HttpClientCallbackOnStatus,
                                 _HttpClientCallbackOnResponse, 0, NULL, NULL, NULL));

    UT_ASSERT_EQUAL(MI_RESULT_OK,
        HttpClient_StartRequest(http, "GET", "/", &headers, 0));

    for (int i = 0; i < 1000 && !s_httpResponseReceived; i++)
    {
        if (i % 100 == 0)
        {
            printf("TestHttpClient_BasicOperations has processed %d / 1,000 responses\n", i);
        }
        HttpClient_Run(http, 20000);

        ut::sleep_ms(50);
        sched_yield();
    }

    // verify results:
    UT_ASSERT_EQUAL(s_httpCode, 200);
    UT_ASSERT_EQUAL(s_headers["Content-Type"], "application/soap+xml;charset=UTF-8");
    UT_ASSERT_EQUAL(s_contentReceivedFromServer, string("Test"));
    UT_ASSERT_EQUAL(s_contentType, string("text/html"));

    UT_ASSERT_EQUAL(MI_RESULT_OK,
        HttpClient_Delete(http));

    http = 0;

}

static void TestHttpClient_MissingCertificate_https()
{
#ifdef CONFIG_POSIX
    std::string v;

    if (!ut::testGetAttr("valgrind", v))
    {
        HttpClient* http = NULL;

        /* content to send to the client */
        s_response = "Test";

        /* load the client certificate */
        const char* pemFile = GetPath(ID_PEMFILE);
        UT_ASSERT_NOT_EQUAL(pemFile, (const char*)0);

        char derFile[PATH_MAX + 5];
        strncpy(derFile, pemFile, PATH_MAX);
        derFile[PATH_MAX] = '\0';
        size_t derLen = strlen(derFile);
        if (derLen > 5 && strcmp(&derFile[derLen - 4], ".pem") == 0)
        {
            strcpy(&derFile[derLen - 4], ".bad");
        }
        else
        {
            strcat(derFile, ".bad");
        }

        UT_ASSERT_NOT_EQUAL(MI_RESULT_OK,
            HttpClient_New_Connector(&http, 0, "127.0.0.1", PORT + 1, MI_TRUE,
                                     _HttpClientCallbackOnStatus,
                                     _HttpClientCallbackOnResponse, 0, NULL, derFile, derFile));
    }
#endif

    return;
}

static void TestHttpClient_BadCertificate_https()
{
#ifdef CONFIG_POSIX
    std::string v;

    if (!ut::testGetAttr("valgrind", v))
    {
        HttpClient* http = NULL;

        /* content to send to the client */
        s_response = "Test";

        /* load the client certificate */
        const char* pemFile = GetPath(ID_PEMFILE);
        UT_ASSERT_NOT_EQUAL(pemFile, (const char*)0);

        char derFile[PATH_MAX + 16];
        strncpy(derFile, pemFile, PATH_MAX);
        derFile[PATH_MAX] = '\0';
        char* baseName = strrchr(derFile, '/');
        UT_ASSERT_NOT_EQUAL(baseName, (const char*)0);
        strcpy(baseName + 1, "bad.der");

        UT_ASSERT_NOT_EQUAL(MI_RESULT_OK,
            HttpClient_New_Connector(&http, 0, "127.0.0.1", PORT + 1, MI_TRUE,
                                     _HttpClientCallbackOnStatus,
                                     _HttpClientCallbackOnResponse, 0, NULL, derFile, derFile));
    }
#endif

    return;
}

static void TestHttpClient_BasicOperations_https()
{
#ifdef CONFIG_POSIX
    std::string v;

    if (!ut::testGetAttr("valgrind", v))
    {
        HttpClient* http = NULL;
        const char* header_strings[] = {
            //"Content-Type: text/html",
            //"User-Agent: xplat http client" ,
            "Host: host"
        };

        /* content to send to the client */
        s_response = "Test";

        HttpClientRequestHeaders headers = {
            header_strings,
            MI_COUNT(header_strings) };

        /* load the client certificate */
        const char* pemFile = GetPath(ID_PEMFILE);
        UT_ASSERT_NOT_EQUAL(pemFile, (const char*)0);

        /* load the client private key */
        const char* keyFile = GetPath(ID_KEYFILE);
        UT_ASSERT_NOT_EQUAL(keyFile, (const char*)0);

        UT_ASSERT_EQUAL(MI_RESULT_OK,
            HttpClient_New_Connector(&http, 0, "127.0.0.1", PORT + 1, MI_TRUE,
                                     _HttpClientCallbackOnStatus,
                                     _HttpClientCallbackOnResponse, 0, NULL, pemFile, keyFile));

        UT_ASSERT_EQUAL(MI_RESULT_OK,
            HttpClient_StartRequest(http, "GET", "/", &headers, 0));

        for (int i = 0; i < 1000 && !s_httpResponseReceived; i++)
        {
            if (i % 100 == 0)
            {
                printf("TestHttpClient_BasicOperations_https has processed %d / 1,000 responses\n", i);
            }
            HttpClient_Run(http, 20000);
            ut::sleep_ms(50);
            sched_yield();
        }

        // verify results:
        UT_ASSERT_EQUAL(s_httpCode, 200);
        UT_ASSERT_EQUAL(s_headers["Content-Type"], "application/soap+xml;charset=UTF-8");
        UT_ASSERT_EQUAL(s_contentReceivedFromServer, string("Test"));

        UT_ASSERT_EQUAL(MI_RESULT_OK,
            HttpClient_Delete(http));

        http = NULL;
    }
#endif
}

static void TestHttpClient_BasicOperations_Der_https()
{
#ifdef CONFIG_POSIX
    std::string v;

    if (!ut::testGetAttr("valgrind", v))
    {
        HttpClient* http = NULL;
        const char* header_strings[] = {
            //"Content-Type: text/html",
            //"User-Agent: xplat http client" ,
            "Host: host"
        };

        /* content to send to the client */
        s_response = "Test";

        HttpClientRequestHeaders headers = {
            header_strings,
            MI_COUNT(header_strings) };

        /* load the client certificate */
        const char* pemFile = GetPath(ID_PEMFILE);
        UT_ASSERT_NOT_EQUAL(pemFile, (const char*)0);

        char derCertFile[PATH_MAX + 5];
        strncpy(derCertFile, pemFile, PATH_MAX);
        derCertFile[PATH_MAX] = '\0';
        size_t derLen = strlen(derCertFile);
        if (derLen > 5 && strcmp(&derCertFile[derLen - 4], ".pem") == 0)
        {
            strcpy(&derCertFile[derLen - 4], ".der");
        }
        else
        {
            strcat(derCertFile, ".der");
        }

        /* load the client private key */
        const char* keyFile = GetPath(ID_KEYFILE);
        UT_ASSERT_NOT_EQUAL(pemFile, (const char*)0);

        UT_ASSERT_EQUAL(MI_RESULT_OK,
            HttpClient_New_Connector(&http, 0, "127.0.0.1", PORT + 1, MI_TRUE,
                                     _HttpClientCallbackOnStatus,
                                     _HttpClientCallbackOnResponse, 0, NULL, derCertFile, keyFile));

        UT_ASSERT_EQUAL(MI_RESULT_OK,
            HttpClient_StartRequest(http, "GET", "/", &headers, 0));

        for (int i = 0; i < 1000 && !s_httpResponseReceived; i++)
        {
            if (i % 100 == 0)
            {
                printf("TestHttpClient_BasicOperations_https has processed %d / 1,000 responses\n", i);
            }
            HttpClient_Run(http, 20000);
            sched_yield();
            ut::sleep_ms(50);
        }

        // verify results:
        UT_ASSERT_EQUAL(s_httpCode, 200);
        UT_ASSERT_EQUAL(s_headers["Content-Type"], "application/soap+xml;charset=UTF-8");
        UT_ASSERT_EQUAL(s_contentReceivedFromServer, string("Test"));

        UT_ASSERT_EQUAL(MI_RESULT_OK,
            HttpClient_Delete(http));

        http = NULL;
    }
#endif
}

static void _runClientWithSimplifiedServer(ThreadSrvParam& param)
{
    HttpClient* http = NULL;

    const char* header_strings[] = {
        "Content-Type: text/html"
    };

    /* create a server */
    ThreadHandle t;

    UT_ASSERT(MI_RESULT_OK == Thread_Create(http_server_proc, &param, &t));

    for (int i = 0; !param.started; i++)
    {
        // check if we waited too long
        UT_ASSERT(i < 1000);

        sched_yield();
        ut::sleep_ms(100);
    }

    HttpClientRequestHeaders headers = { header_strings, MI_COUNT(header_strings) };

    UT_ASSERT_EQUAL(MI_RESULT_OK,
        HttpClient_New_Connector(&http, 0, "127.0.0.1", PORT+2, MI_FALSE,
                                 _HttpClientCallbackOnStatus,
                                 _HttpClientCallbackOnResponse, 0, NULL, NULL, NULL));


    UT_ASSERT_EQUAL(MI_RESULT_OK, HttpClient_StartRequest(http, "GET", "/", &headers, 0));

    for (int i = 0; i < 1000 && !s_httpResponseReceived; i++)
    {
        if (i % 100 == 0)
        {
            printf("_runClientWithSimplifiedServer has processed %d / 1,000 responses\n", i);
        }
        HttpClient_Run(http, 20000);
        sched_yield();
        ut::sleep_ms(50);
    }

    // wait for completion and check that
    UT_ASSERT(MI_RESULT_OK == Thread_Destroy(t, MI_TRUE));

    // free client pointer
    UT_ASSERT_EQUAL(MI_RESULT_OK, HttpClient_Delete(http));

    http = NULL;
}

static void TestHttpClient_ChunkedResponse()
{
    ThreadSrvParam param;

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

    _runClientWithSimplifiedServer(param);

    // verify results:
    UT_ASSERT_EQUAL(s_httpCode, 200);
    UT_ASSERT_EQUAL(s_headers["Content-Type"], "application/soap+xml;charset=UTF-8");
    UT_ASSERT_EQUAL(s_contentReceivedFromServer, string("Test"));
}

static void TestHttpClient_ChunkedResponseByOneByte()
{
    ThreadSrvParam param;

    /* content to send to the client */
    param.messageToSend =
    /* header */
    "HTTP/1.1 200 OK\r\n"
    "transfer-encoding: chunked\r\n"
    "Connection: Keep-Alive\r\n"
    "Content-Type: application/soap+xml;charset=UTF-8\r\n"
    "\r\n"

    /* chunk 1 - 17 bytes */
    "11 \r\n"
    "1234567890abcdefT\r\n"

    /* chunk 2 - 13 bytes */
    "d \r\n"
    "est1234567890\r\n"

    /* last chunk */
    "0 \r\n"
    "\r\n"
        ;
    param.bytesToSendPerOperation = 10240;

    _runClientWithSimplifiedServer(param);

    // verify results:
    UT_ASSERT_EQUAL(s_httpCode, 200);
    UT_ASSERT_EQUAL(s_headers["Content-Type"], "application/soap+xml;charset=UTF-8");
    UT_ASSERT_EQUAL(s_contentReceivedFromServer, string("1234567890abcdefTest1234567890"));
}

static void RunTests()
{
    printf("\n------------------>> Begin test_httpclient tests\n");
    Sock_Start();
    _StartHTTP_Server(
        _HttpCallbackOnNewConnection,
        _HttpCallbackOnCloseConnection,
        _HttpCallbackOnRequest,
        0);

    UT_TEST(TestHttpClient_BasicOperations);
    UT_TEST(TestHttpClient_MissingCertificate_https);
    UT_TEST(TestHttpClient_BadCertificate_https);
    UT_TEST(TestHttpClient_BasicOperations_https);
    UT_TEST(TestHttpClient_BasicOperations_Der_https);
    UT_TEST(TestHttpClient_ChunkedResponse);
    UT_TEST(TestHttpClient_ChunkedResponseByOneByte);

    _StopHTTP_Server();
    Sock_Stop();
    printf("\n------------------>> End test_httpclient tests\n");
}

UT_ENTRY_POINT(RunTests);
