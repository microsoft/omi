/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <vector>
#include <map>
#include <cstdlib>
#include <ut/ut.h>
#include <pal/thread.h>
#include <http/httpclient.h>
#include <http/httpcommon.h>
#include <base/result.h>
#include <base/paths.h>
#include <base/Strand.h>
#ifdef CONFIG_POSIX
# include <limits.h>
# if !defined PATH_MAX   // Some HP-UX's don't define PATH_MAX in <limits.h> unless you specify several symbols before including it
#  define PATH_MAX _XOPEN_PATH_MAX
# endif
#endif

using namespace std;

#define TEST_BASICAUTH_BASE64 "dGVzdDpwYXNzd29yZA=="
#define TEST_USERNAME "test"
#define TEST_PASSWORD "password"

/*********************************** http server ***************************/

/* local data */
static  Http* s_http;
static bool s_stop;
static Thread s_t;
static MI_Uint16 PORT = ut::getUnittestPortNumber() + 10;
static string s_contentType;
static string s_charset;
static string s_content;
static string s_response;
static bool s_delayServerResponse = false;

// received data
static int s_httpCode;
static map< string, string > s_headers;
static string s_contentReceivedFromServer;
static int s_cxxError;

//static bool s_httpConnectReceived;
static bool s_httpResponseReceived;

#if defined(_MSC_VER)
#undef BEGIN_EXTERNC
#undef END_EXTERNC
#define BEGIN_EXTERNC
#define END_EXTERNC
#endif

 /* helper functions */
BEGIN_EXTERNC
static void* MI_CALL _HTTPServerProc(void* )
{
    Sock_Start();
    // pump messages
    for (; !s_stop; )
        Http_Run(s_http, SELECT_BASE_TIMEOUT_MSEC * 1000);

    Sock_Stop();
    return 0;
}
END_EXTERNC

BEGIN_EXTERNC
static void _StartHTTP_Server(
    OpenCallback callbackOnNewConnection,
    void* callbackData,
    const HttpOptions* options = 0)
{
    /* create a server */
    TEST_ASSERT( MI_RESULT_OK == Http_New_Server(
        &s_http, 0, PORT, PORT + 1, NULL, (Server_SSL_Options) 0,
        callbackOnNewConnection,
        callbackData, options) );

    /* create a thread for message consumption */
    s_stop = false;

    TEST_ASSERT(MI_RESULT_OK == Thread_CreateJoinable(
        &s_t, (ThreadProc)_HTTPServerProc, NULL, 0));

}
END_EXTERNC

BEGIN_EXTERNC
static void _StopHTTP_Server()
{
    s_stop = true;
    PAL_Uint32 ret;
    TEST_ASSERT( Thread_Join( &s_t, &ret ) == 0 );
    Thread_Destroy( &s_t );
    TEST_ASSERT( MI_RESULT_OK == Http_Delete(s_http) );

    memset(&s_t, 0, sizeof(Thread));
    s_http = 0;
    s_stop = false;
}
END_EXTERNC

struct TestClientCallbackStruct
{
    Strand strand;

    TestClientCallbackStruct() {}
};

BEGIN_EXTERNC
void _StrandTestClientPost( _In_ Strand* self_, _In_ Message* msg )
{
    TestClientCallbackStruct* data = (TestClientCallbackStruct*)self_;
    HttpRequestMsg* request = (HttpRequestMsg *)msg;
    HttpResponseMsg* msgRsp;

    TEST_ASSERT( HttpRequestMsgTag == msg->tag );

    if (request->headers->contentType)
        s_contentType = request->headers->contentType;
    else
        s_contentType = "";

    if (request->headers->charset)
        s_charset = request->headers->charset;
    else
        s_charset = "";

    if (request->page)
        s_content = string( (char*) ((request->page)+1), (size_t) + (request->page)->u.s.size);
    else
        s_content.clear();

    Page* rsp = (Page*)PAL_Malloc(sizeof(Page) + s_response.size());

    TEST_ASSERT(rsp);
    if(rsp == NULL)
        return;

    rsp->u.s.size = s_response.size();
    memcpy(rsp+1, s_response.c_str(), s_response.size());

    if (s_delayServerResponse)
        ut::sleep_ms(175);

    msgRsp = HttpResponseMsg_New(rsp, HTTP_ERROR_CODE_OK);

    TEST_ASSERT( NULL != msg );

    Strand_Post( &data->strand, &msgRsp->base );
}

void _StrandTestClientAck( _In_ Strand* self)
{
    // do nothing
}

void _StrandTestClientFinished( _In_ Strand* self)
{
    // do nothing
}

StrandFT testClientUserFT = {
        _StrandTestClientPost,
        NULL,
        _StrandTestClientAck,
        NULL,
        NULL,
        _StrandTestClientFinished,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL };

STRAND_DEBUGNAME( TestHttpCli );

static void _callbackTestClient(
    _Inout_     InteractionOpenParams*    interactionParams)
{
    TestClientCallbackStruct* data = (TestClientCallbackStruct*)interactionParams->callbackData;

    UT_ASSERT (data != NULL);
    UT_ASSERT (interactionParams->msg == NULL);

    Strand_Init( STRAND_DEBUG( TestHttpCli ) &data->strand, &testClientUserFT, 0, interactionParams );
}

END_EXTERNC

TestClientCallbackStruct serverCallback;

NitsSetup(TestHttpClientSetup)
{
    IgnoreAuthCalls(1);

    Sock_Start();
    _StartHTTP_Server(
        _callbackTestClient,
        &serverCallback,
        0);

    s_httpResponseReceived = false;
    s_response = "";
    s_contentType = "";
    s_delayServerResponse = false;

    s_httpCode = 0;
    s_headers.clear();
    s_contentReceivedFromServer.clear();
    s_cxxError = -1;
}
NitsEndSetup

NitsCleanup(TestHttpClientSetup)
{
    _StopHTTP_Server();
    Sock_Stop();
}
NitsEndCleanup

/************************************* http client **********************/



BEGIN_EXTERNC
#if 0
static void _HttpClientCallbackOnConnect(
    HttpClient* http,
    void* callbackData)
{
    MI_UNUSED(http);
    MI_UNUSED(callbackData);
    s_httpConnectReceived = true;

}
#endif
static void _HttpClientCallbackOnStatus(
    HttpClient* http,
    void* callbackData,
    MI_Result result)
{
    MI_UNUSED(http);
    MI_UNUSED(callbackData);
    MI_UNUSED(result);
    s_httpResponseReceived = true;

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

    if (headers)
    {
        s_httpCode = headers->httpError;
        for (unsigned int i = 0; i < headers->sizeHeaders; i++)
        {
            s_headers[headers->headers[i].name] = headers->headers[i].value;
        }
    }

    if (data && *data)
    {
        s_contentReceivedFromServer +=
            string( (char*) ((*data)+1), ((char*)((*data)+1)) + (*data)->u.s.size);
    }

    return MI_TRUE;
}
END_EXTERNC


/* Simplified http client for chunked stuff testing */
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

/* simple http client */
static void* MI_CALL _http_server_proc(void* param)
{
    ThreadSrvParam* p = (ThreadSrvParam*)param;

    Addr addr;
    Sock sock, listener;
    MI_Result r;

    Sock_Start();

    // Initialize address (connect using loopback).
    Addr_InitAny(&addr, PORT+2);

    r = Sock_CreateListener(&listener, &addr);
    UT_ASSERT_EQUAL(r, MI_RESULT_OK);
    if(r != MI_RESULT_OK)
    {
        throw(ut::UnittestException("test_httpclient.cpp", 0, "_http_server_proc", "Listener creation failed"));
    }
    UT_ASSERT_EQUAL(Sock_SetBlocking(listener, MI_FALSE), MI_RESULT_OK);

    p->started = true;

    // accept incoming request
    for (int i = 0; ; i++)
    {
        // check if we waited too long
        TEST_ASSERT(i < 1000);

        r = Sock_Accept(listener, &sock, &addr);

        if (MI_RESULT_WOULD_BLOCK == r)
        {
            ut::sleep_ms(1);
            continue;
        }

        UT_ASSERT_EQUAL(r, MI_RESULT_OK);
        break;
    }

    // close listener
    Sock_Close(listener);


    // read and ignore http request
    char r_buf[1024];
    size_t read = 0;
    r = Sock_Read(sock, r_buf, sizeof(r_buf), &read);

    //if (r) printf("s,r: %d, err %d\n", (int)read, Sock_GetLastError());

    // send pre-defined response

    size_t sent = 0;
    size_t size_left = p->messageToSend.size();
    const char* buf = p->messageToSend.c_str();

    while ( size_left )
    {
        ut::sleep_ms( 1 );

        size_t wantToSend = min(p->bytesToSendPerOperation, size_left);
        r = Sock_Write(sock, buf, wantToSend, &sent);

        //printf("size_left %d, r %d, sent %d, want-send %d\n", size_left, r, sent, wantToSend);
        if ( r != MI_RESULT_OK)
        {
            // printf("size_left %d, r %d, want write %d, sent %d, le %d\n", (int)size_left, (int)r, (int)wantToSend, (int)sent, Sock_GetLastError());
            ut::sleep_ms( 7000 );
        }

        TEST_ASSERT(r == MI_RESULT_OK);
//        printf("s: %d\n", (int)sent);
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
        ex.m_testcase = "--http_server_proc"; UT_ASSERT_FAILED_MSG(ex.m_testcase.c_str());
    }
    return 0;
}
END_EXTERNC

// All the tests which are having NitsDisableFaultSim; are disabled for fault injection
// in order to re-enable fault injection, it requires too many changes in test code and
// it is not worth it since other tests are already testing these code paths in http with fault injection.

NitsTestWithSetup(TestHttpClient_BasicOperations, TestHttpClientSetup)
{
    NitsDisableFaultSim;

    HttpClient* http = 0;
    //const char* header_strings[] = {
    //    "Content-Type: text/html",
    //    //"User-Agent: xplat http cleint" ,
    //    "Host: host"
    //};

    /* content to send to the client */
    s_response = "Test";

    //HttpClientRequestHeaders headers = {
    //    header_strings,
    //    MI_COUNT(header_strings) };

    MI_Application miApplication = MI_APPLICATION_NULL;
    MI_DestinationOptions *miDestinationOptions = NULL;
    MI_DestinationOptions _miDestinationOptions = MI_DESTINATIONOPTIONS_NULL;
    MI_UserCredentials miUserCredentials = {0};

    UT_ASSERT_EQUAL(MI_RESULT_OK,
                    MI_Application_Initialize(0, NULL, NULL, &miApplication));

    miDestinationOptions = &_miDestinationOptions;
    UT_ASSERT_EQUAL(MI_RESULT_OK,
                    MI_Application_NewDestinationOptions(&miApplication, miDestinationOptions));

    miUserCredentials.authenticationType = MI_AUTH_TYPE_BASIC;
    miUserCredentials.credentials.usernamePassword.domain = MI_T("localhost");
   
    miUserCredentials.credentials.usernamePassword.username = TEST_USERNAME;
    miUserCredentials.credentials.usernamePassword.password = TEST_PASSWORD;
    UT_ASSERT_EQUAL(MI_RESULT_OK,
                    MI_DestinationOptions_AddDestinationCredentials(miDestinationOptions, &miUserCredentials));

        /* content to send to the client */
    if(!TEST_ASSERT(MI_RESULT_OK ==
        HttpClient_New_Connector(&http, 0, "127.0.0.1", PORT, MI_FALSE,
        _HttpClientCallbackOnStatus,
        _HttpClientCallbackOnResponse, 
        NULL, miDestinationOptions)))
        return;

    if(!TEST_ASSERT(MI_RESULT_OK ==
        HttpClient_StartRequest(http, "GET", "/", "Content-Type: text/html", 0)))
        goto cleanup;

    for (int i = 0; i < 1000 && !s_httpResponseReceived; i++)
        HttpClient_Run(http, SELECT_BASE_TIMEOUT_MSEC * 1000);

    // verify results:
    NitsCompare(s_httpCode, 200, MI_T("success http code"));
    NitsCompareStringExA(s_headers["Content-Type"].c_str(), "application/soap+xml;charset=UTF-8", "Content type", TLINE, NitsAutomatic);
    NitsCompareStringExA(s_contentReceivedFromServer.c_str(), "Test", "http body", TLINE, NitsAutomatic);
    NitsCompareStringExA(s_contentType.c_str(), "text/html", "content type", TLINE, NitsAutomatic);

cleanup:
    if (http)
        NitsCompare(MI_RESULT_OK, HttpClient_Delete(http), MI_T("Deleting http client"));

    if (miDestinationOptions)
        MI_DestinationOptions_Delete(miDestinationOptions);

    MI_Application_Close(&miApplication);

}
NitsEndTest

NitsTestWithSetup(TestHttpClient_BasicHeadOperation, TestHttpClientSetup)
{
    NitsDisableFaultSim;

    HttpClient* http = 0;
    //const char* header_strings[] = {
    //    "Content-Type: text/html",
    //    "Host: host"
    //};

    /* content to send to the client */
    s_response = "";

    //HttpClientRequestHeaders headers = {
    //    header_strings,
    //    MI_COUNT(header_strings) };

    MI_Application miApplication = MI_APPLICATION_NULL;
    MI_DestinationOptions *miDestinationOptions = NULL;
    MI_DestinationOptions _miDestinationOptions = MI_DESTINATIONOPTIONS_NULL;
    MI_UserCredentials miUserCredentials = {0};

    UT_ASSERT_EQUAL(MI_RESULT_OK,
                    MI_Application_Initialize(0, NULL, NULL, &miApplication));

    miDestinationOptions = &_miDestinationOptions;
    UT_ASSERT_EQUAL(MI_RESULT_OK,
                    MI_Application_NewDestinationOptions(&miApplication, miDestinationOptions));

    miUserCredentials.authenticationType = MI_AUTH_TYPE_BASIC;
    miUserCredentials.credentials.usernamePassword.domain = MI_T("localhost");
   
    miUserCredentials.credentials.usernamePassword.username = TEST_USERNAME;
    miUserCredentials.credentials.usernamePassword.password = TEST_PASSWORD;
    UT_ASSERT_EQUAL(MI_RESULT_OK,
                    MI_DestinationOptions_AddDestinationCredentials(miDestinationOptions, &miUserCredentials));

    if(!TEST_ASSERT(MI_RESULT_OK ==
        HttpClient_New_Connector(&http, 0, "127.0.0.1", PORT, MI_FALSE,
        _HttpClientCallbackOnStatus,
        _HttpClientCallbackOnResponse, 
        NULL, miDestinationOptions)))
        return;

    if(!TEST_ASSERT(MI_RESULT_OK ==
        HttpClient_StartRequest(http, "HEAD", "/", "Content-Type: text/html", 0)))
        goto cleanup;

    for (int i = 0; i < 1000 && !s_httpResponseReceived; i++)
        HttpClient_Run(http, SELECT_BASE_TIMEOUT_MSEC * 1000);

    // verify results:
    UT_ASSERT_EQUAL(s_httpCode, 200);
    UT_ASSERT_EQUAL(s_headers["Content-Type"], "application/soap+xml;charset=UTF-8");
    UT_ASSERT_EQUAL(s_contentType, string("text/html"));

cleanup:
    if (http)
        UT_ASSERT_EQUAL(MI_RESULT_OK, HttpClient_Delete(http));
}
NitsEndTest

#ifdef CONFIG_POSIX

NitsTestWithSetup(TestHttpClient_MissingCertificate_https, TestHttpClientSetup)
{
    NitsDisableFaultSim;

    std::string v;

    if (!ut::testGetAttr("valgrind", v))
    {
        HttpClient* http = NULL;

        /* content to send to the client */
        s_response = "Test";
        MI_Application miApplication = MI_APPLICATION_NULL;
        MI_DestinationOptions *miDestinationOptions = NULL;
        MI_DestinationOptions _miDestinationOptions = MI_DESTINATIONOPTIONS_NULL;
        MI_UserCredentials miUserCredentials = {0};
    
        UT_ASSERT_EQUAL(MI_RESULT_OK,
                        MI_Application_Initialize(0, NULL, NULL, &miApplication));
    
        miDestinationOptions = &_miDestinationOptions;
        UT_ASSERT_EQUAL(MI_RESULT_OK,
                        MI_Application_NewDestinationOptions(&miApplication, miDestinationOptions));
    
        miUserCredentials.authenticationType = MI_AUTH_TYPE_BASIC;
        miUserCredentials.credentials.usernamePassword.domain = MI_T("localhost");
       
        miUserCredentials.credentials.usernamePassword.username = TEST_USERNAME;
        miUserCredentials.credentials.usernamePassword.password = TEST_PASSWORD;
        UT_ASSERT_EQUAL(MI_RESULT_OK,
                        MI_DestinationOptions_AddDestinationCredentials(miDestinationOptions, &miUserCredentials));

        /* load the client certificate */
        const char* pemFile = OMI_GetPath(ID_PEMFILE);
        UT_ASSERT_NOT_EQUAL(pemFile, (const char*)0);

        char derFile[PATH_MAX + 5];
        strncpy(derFile, pemFile, PATH_MAX);
        derFile[PATH_MAX] = '\0';
        size_t derLen = strlen(derFile);
        if (derLen > 5 && strcmp(&derFile[derLen - 4], ".pem") == 0)
            strcpy(&derFile[derLen - 4], ".xxx");
        else
            strcat(derFile, ".xxx");

        UT_ASSERT_EQUAL(MI_RESULT_OK, MI_DestinationOptions_SetCertFile(miDestinationOptions, derFile));
        UT_ASSERT_EQUAL(MI_RESULT_OK, MI_DestinationOptions_SetPrivateKeyFile(miDestinationOptions, derFile));

        UT_ASSERT_NOT_EQUAL(MI_RESULT_OK,
            HttpClient_New_Connector(&http, 0, "127.0.0.1", PORT + 1, MI_TRUE,
                                     _HttpClientCallbackOnStatus,
                                     _HttpClientCallbackOnResponse, 0, miDestinationOptions));
    }
}
NitsEndTest

NitsTestWithSetup(TestHttpClient_BadCertificate_https, TestHttpClientSetup)
{
    NitsDisableFaultSim;

    std::string v;

    if (!ut::testGetAttr("valgrind", v))
    {
        HttpClient* http = NULL;


        MI_Application miApplication = MI_APPLICATION_NULL;

        MI_DestinationOptions *miDestinationOptions = NULL;
        MI_DestinationOptions _miDestinationOptions = MI_DESTINATIONOPTIONS_NULL;
        MI_UserCredentials miUserCredentials = {0};

        UT_ASSERT_EQUAL(MI_RESULT_OK,
                        MI_Application_Initialize(0, NULL, NULL, &miApplication));

        miDestinationOptions = &_miDestinationOptions;
        UT_ASSERT_EQUAL(MI_RESULT_OK,
                        MI_Application_NewDestinationOptions(&miApplication, miDestinationOptions));

        miUserCredentials.authenticationType = MI_AUTH_TYPE_BASIC;
        miUserCredentials.credentials.usernamePassword.domain = MI_T("localhost");
       
        miUserCredentials.credentials.usernamePassword.username = TEST_USERNAME;
        miUserCredentials.credentials.usernamePassword.password = TEST_PASSWORD;
        UT_ASSERT_EQUAL(MI_RESULT_OK,
                        MI_DestinationOptions_AddDestinationCredentials(miDestinationOptions, &miUserCredentials));

        /* content to send to the client */
        s_response = "Test";

        /* load the client certificate */
        const char* pemFile = OMI_GetPath(ID_PEMFILE);
        UT_ASSERT_NOT_EQUAL(pemFile, (const char*)0);

        char derFile[PATH_MAX + 16];
        strncpy(derFile, pemFile, PATH_MAX);
        derFile[PATH_MAX] = '\0';
        char* baseName = strrchr(derFile, '/');
        UT_ASSERT_NOT_EQUAL(baseName, (const char*)0);
        strcpy(baseName + 1, "bad.der");

        UT_ASSERT_EQUAL(MI_RESULT_OK, MI_DestinationOptions_SetCertFile(miDestinationOptions, derFile));
        UT_ASSERT_EQUAL(MI_RESULT_OK, MI_DestinationOptions_SetPrivateKeyFile(miDestinationOptions, derFile));

        UT_ASSERT_NOT_EQUAL(MI_RESULT_OK,
            HttpClient_New_Connector(&http, 0, "127.0.0.1", PORT + 1, MI_TRUE,
                                     _HttpClientCallbackOnStatus,
                                     _HttpClientCallbackOnResponse, NULL, miDestinationOptions));
        if (miDestinationOptions)
            MI_DestinationOptions_Delete(miDestinationOptions);

        MI_Application_Close(&miApplication);
    }
}
NitsEndTest

NitsTestWithSetup(TestHttpClient_BasicOperations_https, TestHttpClientSetup)
{
    NitsDisableFaultSim;

    std::string v;

    if (!ut::testGetAttr("valgrind", v))
    {
        HttpClient* http = NULL;
        //const char* header_strings[] = {
            //"Content-Type: text/html",
            //"User-Agent: xplat http client" ,
         //   "Host: host"
       // };

        MI_Application miApplication = MI_APPLICATION_NULL;

        MI_DestinationOptions *miDestinationOptions = NULL;
        MI_DestinationOptions _miDestinationOptions = MI_DESTINATIONOPTIONS_NULL;
        MI_UserCredentials miUserCredentials = {0};

        UT_ASSERT_EQUAL(MI_RESULT_OK,
                        MI_Application_Initialize(0, NULL, NULL, &miApplication));

        miDestinationOptions = &_miDestinationOptions;
        UT_ASSERT_EQUAL(MI_RESULT_OK,
                        MI_Application_NewDestinationOptions(&miApplication, miDestinationOptions));

        miUserCredentials.authenticationType = MI_AUTH_TYPE_BASIC;
        miUserCredentials.credentials.usernamePassword.domain = MI_T("localhost");
       
        miUserCredentials.credentials.usernamePassword.username = TEST_USERNAME;
        miUserCredentials.credentials.usernamePassword.password = TEST_PASSWORD;
        UT_ASSERT_EQUAL(MI_RESULT_OK,
                        MI_DestinationOptions_AddDestinationCredentials(miDestinationOptions, &miUserCredentials));

        /* content to send to the client */
        s_response = "Test";

        // HttpClientRequestHeaders headers = {
        //    header_strings,
        //    MI_COUNT(header_strings) };

        /* load the client certificate */
        const char* pemFile = OMI_GetPath(ID_PEMFILE);
        UT_ASSERT_NOT_EQUAL(pemFile, (const char*)0);

        /* load the client private key */
        const char* keyFile = OMI_GetPath(ID_KEYFILE);
        UT_ASSERT_NOT_EQUAL(keyFile, (const char*)0);

        UT_ASSERT_EQUAL(MI_RESULT_OK, MI_DestinationOptions_SetCertFile(miDestinationOptions, pemFile));
        UT_ASSERT_EQUAL(MI_RESULT_OK, MI_DestinationOptions_SetPrivateKeyFile(miDestinationOptions, keyFile));

        UT_ASSERT_EQUAL(MI_RESULT_OK,
            HttpClient_New_Connector(&http, 0, "127.0.0.1", PORT + 1, MI_TRUE,
                                     _HttpClientCallbackOnStatus,
                                     _HttpClientCallbackOnResponse, NULL, miDestinationOptions));

        UT_ASSERT_EQUAL(MI_RESULT_OK,
            HttpClient_StartRequest(http, "GET", "/", "Content-Type: text/html", 0));

        for (int i = 0; i < 1000 && !s_httpResponseReceived; i++)
        {
            HttpClient_Run(http, SELECT_BASE_TIMEOUT_MSEC * 1000);
            ut::sleep_ms(50);
            sched_yield();
        }

        // verify results:
        UT_ASSERT_EQUAL(s_httpCode, 200);
        UT_ASSERT_EQUAL(s_headers["Content-Type"], "application/soap+xml;charset=UTF-8");
        UT_ASSERT_EQUAL(s_contentReceivedFromServer, string("Test"));

        UT_ASSERT_EQUAL(MI_RESULT_OK, HttpClient_Delete(http));
        if (miDestinationOptions)
            MI_DestinationOptions_Delete(miDestinationOptions);

        MI_Application_Close(&miApplication);
    }
}
NitsEndTest

NitsTestWithSetup(TestHttpClient_BasicOperations_Der_https, TestHttpClientSetup)
{
    NitsDisableFaultSim;

    std::string v;

    if (!ut::testGetAttr("valgrind", v))
    {
        HttpClient* http = NULL;

        //const char* header_strings[] = {
            //"Content-Type: text/html",
            //"User-Agent: xplat http client" ,
         //   "Host: host"
       // };

        /* content to send to the client */
        s_response = "Test";

        MI_Application miApplication = MI_APPLICATION_NULL;
        MI_DestinationOptions *miDestinationOptions = NULL;
        MI_DestinationOptions _miDestinationOptions = MI_DESTINATIONOPTIONS_NULL;
        MI_UserCredentials miUserCredentials = {0};
    
        UT_ASSERT_EQUAL(MI_RESULT_OK,
                        MI_Application_Initialize(0, NULL, NULL, &miApplication));
    
        miDestinationOptions = &_miDestinationOptions;
        UT_ASSERT_EQUAL(MI_RESULT_OK,
                        MI_Application_NewDestinationOptions(&miApplication, miDestinationOptions));
    
        miUserCredentials.authenticationType = MI_AUTH_TYPE_BASIC;
        miUserCredentials.credentials.usernamePassword.domain = MI_T("localhost");
       
        miUserCredentials.credentials.usernamePassword.username = TEST_USERNAME;
        miUserCredentials.credentials.usernamePassword.password = TEST_PASSWORD;
        UT_ASSERT_EQUAL(MI_RESULT_OK,
                        MI_DestinationOptions_AddDestinationCredentials(miDestinationOptions, &miUserCredentials));

        //HttpClientRequestHeaders headers = {
        //    header_strings,
        //    MI_COUNT(header_strings) };

        /* load the client certificate */
        const char* pemFile = OMI_GetPath(ID_PEMFILE);
        UT_ASSERT_NOT_EQUAL(pemFile, (const char*)0);

        char derCertFile[PATH_MAX + 5];
        strncpy(derCertFile, pemFile, PATH_MAX);
        derCertFile[PATH_MAX] = '\0';
        size_t derLen = strlen(derCertFile);
        if (derLen > 5 && strcmp(&derCertFile[derLen - 4], ".pem") == 0)
            strcpy(&derCertFile[derLen - 4], ".der");
        else
            strcat(derCertFile, ".der");

        /* load the client private key */
        const char* keyFile = OMI_GetPath(ID_KEYFILE);
        UT_ASSERT_NOT_EQUAL(pemFile, (const char*)0);

        UT_ASSERT_EQUAL(MI_RESULT_OK, MI_DestinationOptions_SetCertFile(miDestinationOptions, derCertFile));
        UT_ASSERT_EQUAL(MI_RESULT_OK, MI_DestinationOptions_SetPrivateKeyFile(miDestinationOptions, keyFile));

        /* put derCertFile and keyFile into the options object
                                     _HttpClientCallbackOnResponse, 0, NULL, derCertFile, keyFile)); */
        UT_ASSERT_EQUAL(MI_RESULT_OK,
            HttpClient_New_Connector(&http, 0, "127.0.0.1", PORT + 1, MI_TRUE,
                                     _HttpClientCallbackOnStatus,
                                     _HttpClientCallbackOnResponse, 0, miDestinationOptions));

        UT_ASSERT_EQUAL(MI_RESULT_OK,
            HttpClient_StartRequest(http, "GET", "/", "Content-Type: text/html", 0));

        for (int i = 0; i < 1000 && !s_httpResponseReceived; i++)
        {
            HttpClient_Run(http, SELECT_BASE_TIMEOUT_MSEC * 1000);
            sched_yield();
            ut::sleep_ms(50);
        }

        // verify results:
        UT_ASSERT_EQUAL(s_httpCode, 200);
        UT_ASSERT_EQUAL(s_headers["Content-Type"], "application/soap+xml;charset=UTF-8");
        UT_ASSERT_EQUAL(s_contentReceivedFromServer, string("Test"));

        UT_ASSERT_EQUAL(MI_RESULT_OK, HttpClient_Delete(http));
        if (miDestinationOptions)
            MI_DestinationOptions_Delete(miDestinationOptions);

        MI_Application_Close(&miApplication);
    }
}
NitsEndTest

#endif // CONFIG_POSIX

static void _runClientWithSimplifiedServer(ThreadSrvParam& param)
{
    HttpClient* http = 0;

    //const char* header_strings[] = {
    //    "Content-Type: text/html"
    //};
    //HttpClientRequestHeaders headers = {
     //   header_strings,
      //  MI_COUNT(header_strings) };
    PAL_Uint32 ret;

    /* create a server */
    Thread t;


    MI_Application miApplication = MI_APPLICATION_NULL;
    MI_DestinationOptions *miDestinationOptions = NULL;
    MI_DestinationOptions _miDestinationOptions = MI_DESTINATIONOPTIONS_NULL;
    MI_UserCredentials miUserCredentials = {0};

    UT_ASSERT_EQUAL(MI_RESULT_OK,
                    MI_Application_Initialize(0, NULL, NULL, &miApplication));

    miDestinationOptions = &_miDestinationOptions;
    UT_ASSERT_EQUAL(MI_RESULT_OK,
                    MI_Application_NewDestinationOptions(&miApplication, miDestinationOptions));

    miUserCredentials.authenticationType = MI_AUTH_TYPE_BASIC;
    miUserCredentials.credentials.usernamePassword.domain = MI_T("localhost");
   
    miUserCredentials.credentials.usernamePassword.username = TEST_USERNAME;
    miUserCredentials.credentials.usernamePassword.password = TEST_PASSWORD;
    UT_ASSERT_EQUAL(MI_RESULT_OK,
                    MI_DestinationOptions_AddDestinationCredentials(miDestinationOptions, &miUserCredentials));

    int threadCreatedResult = Thread_CreateJoinable(
        &t, (ThreadProc)http_server_proc, NULL, &param);

    TEST_ASSERT(MI_RESULT_OK == threadCreatedResult);
    if(threadCreatedResult != MI_RESULT_OK)
        goto TestEnd;
    for (int i = 0; !param.started; i++)
    {
        // check if we waited too long
        TEST_ASSERT(i < 1000);

        ut::sleep_ms(1);
    }

    if(!TEST_ASSERT(MI_RESULT_OK ==
        HttpClient_New_Connector(&http, 0, "127.0.0.1", PORT+2, MI_FALSE,
        _HttpClientCallbackOnStatus,
        _HttpClientCallbackOnResponse, 
        NULL, miDestinationOptions)))
        goto cleanup;

    if(!TEST_ASSERT(MI_RESULT_OK ==
        HttpClient_StartRequest(http, "GET", "/", "text/html", NULL)))
        goto cleanup;

    for (int i = 0; i < 10000 && !s_httpResponseReceived; i++)
        HttpClient_Run(http, SELECT_BASE_TIMEOUT_MSEC * 1000);

cleanup:
    // wait for completion and check that
    TEST_ASSERT( Thread_Join( &t, &ret ) == 0 );
    Thread_Destroy( &t );
TestEnd:
    // free client pointer
    UT_ASSERT_EQUAL(MI_RESULT_OK,
        HttpClient_Delete(http));

    if (miDestinationOptions)
        MI_DestinationOptions_Delete(miDestinationOptions);

    MI_Application_Close(&miApplication);
}

NitsTestWithSetup(TestHttpClient_ChunkedResponse, TestHttpClientSetup)
{
    NitsDisableFaultSim;

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
NitsEndTest

NitsTestWithSetup(TestHttpClient_ChunkedResponseByOneByte, TestHttpClientSetup)
{
    NitsDisableFaultSim;

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
    param.bytesToSendPerOperation = 1;

    _runClientWithSimplifiedServer(param);

    // verify results:
    UT_ASSERT_EQUAL(s_httpCode, 200);
    UT_ASSERT_EQUAL(s_headers["Content-Type"], "application/soap+xml;charset=UTF-8");
    UT_ASSERT_EQUAL(s_contentReceivedFromServer, string("1234567890abcdefTest1234567890"));

}
NitsEndTest
