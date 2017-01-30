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
#include <pal/strings.h>
#include <http/httpclient.h>
#include <http/httpcommon.h>
#include <base/result.h>
#include <base/paths.h>
#include <base/Strand.h>
#include <wsman/wsmanclient.h>
#ifdef CONFIG_POSIX
# include <limits.h>
# if !defined PATH_MAX   // Some HP-UX's don't define PATH_MAX in <limits.h> unless you specify several symbols before including it
#  define PATH_MAX _XOPEN_PATH_MAX
# endif
#endif


// Wsman client does not support wide chars right now 
#if !defined(CONFIG_ENABLE_WCHAR)
using namespace std;

STRAND_DEBUGNAME(wsmanTestClient)

#define TEST_BASICAUTH_BASE64 "dGVzdDpwYXNzd29yZA=="
#if defined(CONFIG_ENABLE_WCHAR)
#define TEST_USERNAME L"test"
#define TEST_PASSWORD L"password"
#else
#define TEST_USERNAME "test"
#define TEST_PASSWORD "password"
#endif

static MI_Uint16 PORT = ut::getUnittestPortNumber() + 10;

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
    Addr_InitAny(&addr, PORT);

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
        if (!NitsAssert(i < 1000, MI_T("no one sent server any request")))
            break;

        r = Sock_Accept(listener, &sock, &addr);

        if (MI_RESULT_WOULD_BLOCK == r)
        {
            ut::sleep_ms(1);
            continue;
        }

        NitsCompare(r, MI_RESULT_OK, MI_T("Failed to accept connection"));
        break;
    }

    // close listener
    Sock_Close(listener);


    // read and ignore http request
    char r_buf[1024];
    size_t read = 0;
    
    do
    {
        r = Sock_Read(sock, r_buf, sizeof(r_buf), &read);
    }
    while (r != MI_RESULT_OK && Sock_GetLastError() == 11 /*EAGAIN*/);
    if (r != MI_RESULT_OK && r != MI_RESULT_WOULD_BLOCK)
    {
        NitsCompare(r, MI_RESULT_OK, MI_T("Failed to read request on socket"));
    }

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
        NitsCompare(r, MI_RESULT_OK, MI_T("Failed to write response data"));
        if ( r != MI_RESULT_OK)
        {
             printf("size_left %d, r %d, want write %d, sent %d, le %d\n", (int)size_left, (int)r, (int)wantToSend, (int)sent, Sock_GetLastError());
            ut::sleep_ms( 7000 );
            break;
        }

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

NitsSetup(TestWsmanClientChunkSetup)
{
}
NitsEndSetup

NitsCleanup(TestWsmanClientChunkSetup)
{
}
NitsEndCleanup



NitsTestWithSetup(TestWsmanClient_ChunkedResponseRedirect, TestWsmanClientChunkSetup)
{
    NitsDisableFaultSim;
    ThreadSrvParam param;
    PAL_Uint32 ret;
    Thread t;
    MI_Application miApplication = MI_APPLICATION_NULL;
    MI_DestinationOptions miDestinationOptions = MI_DESTINATIONOPTIONS_NULL;
    MI_UserCredentials miUserCredentials = {0};
    MI_Session miSession = MI_SESSION_NULL;
    MI_Operation miOperation = MI_OPERATION_NULL;
    int threadCreatedResult;
    MI_Boolean moreResults = MI_TRUE;
    const MI_Instance *miInstance = NULL;
    const MI_Char *errorMessage = NULL;
    const MI_Instance *completionDetails = NULL;
    MI_Result miResult;


#define CHUNK_REDIRECT_BODY "<html><head><title>Object moved</title></head><body>\r\n<h2>Object moved to <a href=\"https://nam03b.ps.compliance.protection.outlook.com/powershell-liveid?PSVersion=6.0.0\">here</a>.</h2>\r\n</body></html>\r\n"
 

    /* content to send to the client */
    param.messageToSend =
    /* header */
    "HTTP/1.1 302 Found\r\n"
    "Cache-Control: private\r\n"
    "Transfer-Encoding: chunked\r\n"
    "Content-Type: text/html; charset=utf-8\r\n"
    "Location: https://nam03b.ps.compliance.protection.outlook.com/powershell-liveid?PSVersion=6.0.0\r\n"
    "Server: Microsoft-IIS/7.5\r\n"
    "X-AspNet-Version: 4.0.30319\r\n"
    "X-Powered-By: ASP.NET\r\n"
    "Date: Wed, 25 Jan 2017 23:19:31 GMT\r\n"
    "\r\n"
    "ca\r\n"
    CHUNK_REDIRECT_BODY
    "\r\n"
    ;
    param.bytesToSendPerOperation = 10240;


    miUserCredentials.authenticationType = MI_AUTH_TYPE_BASIC;
    miUserCredentials.credentials.usernamePassword.domain = MI_T("localhost");
   
    miUserCredentials.credentials.usernamePassword.username = TEST_USERNAME;
    miUserCredentials.credentials.usernamePassword.password = TEST_PASSWORD;

    if (!NitsCompare(MI_RESULT_OK, MI_Application_Initialize(0, NULL, NULL, &miApplication), MI_T("Failed to initialize mi_app")) ||

        !NitsCompare(MI_RESULT_OK, MI_Application_NewDestinationOptions(&miApplication, &miDestinationOptions), MI_T("destination opts")) ||

        !NitsCompare(MI_RESULT_OK, MI_DestinationOptions_AddDestinationCredentials(&miDestinationOptions, &miUserCredentials), MI_T("Add creds to dest opts")) ||
        !NitsCompare(MI_RESULT_OK, MI_DestinationOptions_SetPacketPrivacy(&miDestinationOptions, MI_FALSE), MI_T("Set no privacy")) ||
        !NitsCompare(MI_RESULT_OK, MI_DestinationOptions_SetTransport(&miDestinationOptions, MI_DESTINATIONOPTIONS_TRANSPORT_HTTP), MI_T("Set HTTP transport")) ||
        !NitsCompare(MI_RESULT_OK, MI_DestinationOptions_SetDestinationPort(&miDestinationOptions, PORT), MI_T("setting port number")))
    {
        goto TestEnd;
    }

    threadCreatedResult = Thread_CreateJoinable(
        &t, (ThreadProc)http_server_proc, NULL, &param);

    if (!NitsCompare(MI_RESULT_OK, threadCreatedResult, MI_T("server thread creation failed")))
        goto TestEnd;

    for (int i = 0; !param.started; i++)
    {
        // check if we waited too long
        if (!NitsAssert( i < 1000, MI_T("Server did not start properly")))
            goto cleanup;

        ut::sleep_ms(1);
    }

    if (!NitsCompare(MI_RESULT_OK, MI_Application_NewSession(&miApplication, NULL, MI_T("localhost"), &miDestinationOptions, NULL, NULL, &miSession), MI_T("new session")))
        goto cleanup;

    MI_Session_Invoke(&miSession, 0, NULL, MI_T("namespace"), MI_T("className"), MI_T("methodName"), NULL, NULL, NULL, &miOperation);

    do
    {
        MI_Operation_GetInstance(&miOperation, &miInstance, &moreResults, &miResult, &errorMessage, &completionDetails);
    } while (moreResults);
    

    // verify results:
    NitsCompare(MI_RESULT_NOT_SUPPORTED, miResult, MI_T("Operation should have failed"));
    if (NitsAssert(completionDetails != NULL, MI_T("We should have completion details with redirect location")))
    {
        MI_Value value;
        MI_Type type;
        MI_Uint32 flags, index;

        if (NitsCompare(MI_RESULT_OK, MI_Instance_GetElement(completionDetails, MI_T("ProbableCauseDescription"), &value, &type, &flags, &index), MI_T("Should have probable cause descr")) &&
                NitsCompare(type, MI_STRING, MI_T("description should be string")) &&
                NitsAssert(value.string != NULL, MI_T("Should have location string")))
        {
            NitsCompareString(MI_T("REDIRECT_LOCATION: https://nam03b.ps.compliance.protection.outlook.com/powershell-liveid?PSVersion=6.0.0"), value.string, MI_T("Redirect string wrong"));
        }
    }
cleanup:
    // wait for completion and check that
    NitsCompare( Thread_Join( &t, &ret ) ,0, MI_T("Join thread failed"));
    Thread_Destroy( &t );
TestEnd:
    // free client pointer

    if (miOperation.ft)
        MI_Operation_Close(&miOperation);

    if (miSession.ft)
        MI_Session_Close(&miSession, NULL, NULL);

    if (miDestinationOptions.ft)
        MI_DestinationOptions_Delete(&miDestinationOptions);

    if (miApplication.ft)
        MI_Application_Close(&miApplication);
}
NitsEndTest

#endif /* CONFIG_ENABLE_WCHAR */
