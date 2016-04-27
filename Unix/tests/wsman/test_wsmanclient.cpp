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
#include <pal/memory.h>
#include <pal/strings.h>
#include <nits/base/nits.h>
#include <ut/ut.h>
#include <wsman/wsmanclient.h>
#include "utils.h"
#include <pal/lock.h>

static MI_Uint16 PORT = ut::getUnittestPortNumber() + 30;
STRAND_DEBUGNAME( TestWsmanClient );

typedef struct _TestData
{
    const char *requestXml;
    MI_Result result;
    MI_Result expectedResult;
    bool gotRequest;
    MI_Sint64 contentSize;
    MI_Boolean lastChunk;
    MI_Uint32 statusCalled;
    ptrdiff_t completed;
} TestData;
static Strand simpleResult;

typedef struct _StrandTest
{
    size_t numPost;
    size_t numMiddlePost;
    size_t numPostControl;
    size_t numAck;
    size_t numCancel;
    size_t numFinished;
    size_t numAux;
    size_t numEntryPost;
    size_t numParentPost;
} StrandTest;
static StrandTest strandTest;

NITS_EXTERN_C void _StrandTestPost( _In_ Strand* self, _In_ Message* msg)
{
    ++strandTest.numPost;
}

NITS_EXTERN_C void _StrandTestMiddlePost( _In_ Strand* self_, _In_ Message* msg)
{
    StrandBoth* self = (StrandBoth*)self_;
    ++strandTest.numMiddlePost;
    StrandBoth_PostPassthruLeft( self, msg );
}

NITS_EXTERN_C void _StrandTestPostControl( _In_ Strand* self, _In_ Message* msg)
{
    ++strandTest.numPostControl;
}

NITS_EXTERN_C void _StrandTestAck( _In_ Strand* self)
{
    ++strandTest.numAck;
}

NITS_EXTERN_C void _StrandTestCancel( _In_ Strand* self)
{
    ++strandTest.numCancel;
}

NITS_EXTERN_C void _StrandTestFinished( _In_ Strand* self)
{
    Strand_Delete( self );
    ++strandTest.numFinished;
}

NITS_EXTERN_C void _StrandTestAux( _In_ Strand* self)
{
    ++strandTest.numAux;
}

static StrandFT strandUserFT1 = {
        _StrandTestPost,
        _StrandTestPostControl,
        _StrandTestAck,
        _StrandTestCancel,
        NULL,
        _StrandTestFinished,
        NULL,
        _StrandTestAux,
        _StrandTestAux,
        _StrandTestAux,
        _StrandTestAux,
        _StrandTestAux };

static void wsmanServerInprocCallback(
    _Inout_     InteractionOpenParams*    interactionParams )
{
    TestData *testData = (TestData*) interactionParams->callbackData;

    printf("wsmanServerInprocCallback - server-side callback, %p\n", testData);

    PostResultMsg* resp = NULL;

    if (!NitsAssert(interactionParams->msg != 0, MI_T("We should have a message")))
    {
        Strand_FailOpen(interactionParams);
        return;
    }

    resp = PostResultMsg_New( interactionParams->msg->operationId );

    UT_ASSERT (resp != 0);

    resp->result = testData->result;

    Strand_Init( STRAND_DEBUG( TestWsmanClient ) &simpleResult, &strandUserFT1, STRAND_FLAG_ENTERSTRAND, interactionParams );

    Strand_Ack( &simpleResult );   // Ack open
    Strand_Post( &simpleResult, &resp->base );
    Strand_Close( &simpleResult );

    PostResultMsg_Release(resp);
}
void TestWsmanClientStatusCallback(void *callbackData, MI_Result result)
{
    TestData *testData = (TestData*) callbackData;
    testData->statusCalled ++;
    testData->result = result;

    printf("TestWsmanClientStatusCallback, result=%d\n", result);

    NitsCompare(result, testData->expectedResult, MI_T("Expected client protocol callback result"));
    testData->completed = 1;
    CondLock_Broadcast((ptrdiff_t) testData);
}

MI_Result WaitForCompletionCallback(TestData *testData)
{
    while (testData->completed != 1)
    {
        CondLock_Wait((ptrdiff_t) testData, &testData->completed, 0, CONDLOCK_DEFAULT_SPINCOUNT);
    }
    return testData->result;
}

MI_Boolean TestWsmanClientResponseCallback(void *callbackData, const HttpClientResponseHeader *headers, MI_Sint64 contentSize, MI_Boolean lastChunk, Page** data)
{
    TestData *testData = (TestData*) callbackData;
    testData->contentSize += contentSize;
    testData->lastChunk = lastChunk;

    printf("TestWsmanClientResponseCallback, lastChunk=%s\n", lastChunk?"true":"false");
    if (headers)
    {
        
        printf("TestWsmanClientResponseCallback, httpError=%u, Num-headers=%u\n", headers->httpError, headers->sizeHeaders);
    }
    else
    {
        printf("TestWsmanClientResponseCallback, no headers\n");
    }

    if (data)
    {
        printf("TestWsmanClientResponseCallback, Buffer=%.*s\n", (*data)->u.s.size, (const char*)((*data)+1));
    }
    else
    {
        printf("TestWsmanClientResponseCallback, Buffer=<null>\n");
    }


    return MI_TRUE;
}


#if 0
NitsSetup(Wsmanclient_Inproc_Setup)
{
    NitsCompare(StartWSManInproc(wsmanServerInprocCallback, NULL, 0), MI_RESULT_OK, "Failed to start wsman server in-process");
}
NitsEndSetup

NitsCleanup(Wsmanclient_Inproc_Setup)
{
    StopWSManInproc();
}
NitsEndCleanup
#endif


static MI_Result CreateDefaultDestinationOptions(MI_Application *application, MI_DestinationOptions *options)
{
    MI_UserCredentials creds;
    if (!NitsCompare(MI_Application_NewDestinationOptions(application, options), MI_RESULT_OK, MI_T("Create destination options")))
    {
        return MI_RESULT_FAILED;
    }

    creds.authenticationType = MI_AUTH_TYPE_BASIC;
    creds.credentials.usernamePassword.username = MI_T("username");
    creds.credentials.usernamePassword.password = MI_T("password");
    if (!NitsCompare(MI_DestinationOptions_AddDestinationCredentials(options, &creds), MI_RESULT_OK, MI_T("Add credentials")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_DestinationOptions_SetDestinationPort(options, PORT), MI_RESULT_OK, MI_T("Setting port number")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_DestinationOptions_SetTransport(options, MI_T("HTTP")), MI_RESULT_OK, MI_T("Setting transport")))
    {
        goto cleanup;
    }
    return MI_RESULT_OK;

cleanup:
    MI_DestinationOptions_Delete(options);
    return MI_RESULT_FAILED;

}

NitsTest(TestWSManClient_CreateDelete)
{
    NitsDisableFaultSim;

    MI_Application application;
    MI_DestinationOptions options;
    TestData testData;
    WsmanClient *wsmanclient;
    MI_Result miresult;

    memset(&testData, 0, sizeof(testData));
    testData.expectedResult = MI_RESULT_OK;


    /* Need a destination options as there is no default credential option yet */
    if (!NitsCompare(MI_Application_InitializeV1(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("Create application")))
    {
        goto end;
    }
    if (!NitsCompare(CreateDefaultDestinationOptions(&application, &options), MI_RESULT_OK, MI_T("Create default options")))
    {
        goto end1;
    }

    if (!NitsCompare(StartWSManInproc(wsmanServerInprocCallback, NULL, 0), MI_RESULT_OK, MI_T("Failed to start wsman server in-process")))
        goto cleanup;

    miresult = WsmanClient_New_Connector(&wsmanclient, NULL, "localhost", &options, TestWsmanClientStatusCallback, TestWsmanClientResponseCallback, &testData, NULL, NULL, NULL);
    if (!NitsCompare(miresult, MI_RESULT_OK, MI_T("wsmanclient creation should succeed")))
        goto cleanup;

    miresult = WsmanClient_Delete(wsmanclient);
    NitsCompare(miresult, MI_RESULT_OK, MI_T("wsmanclient should be deleted"));

cleanup:
    MI_DestinationOptions_Delete(&options);
end1:
    MI_Application_Close(&application);

end:
    StopWSManInproc();
}
NitsEndTest

#define TEST_SENDBODY_RESPONSE "<xml>response</xml>"
#define TEST_SENDBODY_REQUEST ""\
 ""\
    "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\"" \
               " xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\"" \
               " xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\"" \
               " xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\">"\
        "<s:Header>"\
            "<a:To>http://localhost:7778/wsman</a:To>"\
            "<w:ResourceURI s:mustUnderstand=\"true\">http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/X_smallNumber</w:ResourceURI>"\
            "<a:ReplyTo><a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo>"\
            "<a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Delete</a:Action>"\
            "<w:MaxEnvelopeSize s:mustUnderstand=\"true\">327680</w:MaxEnvelopeSize>"\
            "<a:MessageID>uuid:E8928068-D73B-4206-9E95-894088B96288</a:MessageID>" \
            "<w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" />"\
            "<p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" />"\
            "<w:SelectorSet>"\
                "<w:Selector Name=\"__cimnamespace\">test/cpp</w:Selector>"\
                "<w:Selector Name=\"Number\">17</w:Selector>"\
            "</w:SelectorSet>"\
            "<w:OperationTimeout>PT60.000S</w:OperationTimeout>"\
        "</s:Header>"\
        "<s:Body>"\
        "</s:Body>"\
    "</s:Envelope>"

#if !defined(CONFIG_ENABLE_WCHAR)
NitsTest(TestWSManClient_SendBody)
{
    NitsDisableFaultSim;

    MI_Application application;
    MI_DestinationOptions options;
    TestData testData;
    WsmanClient *wsmanclient;
    MI_Result miresult;
    Page *page = NULL;
    char *text = NULL;
    WSMAN_Options wsmanoptions = DEFAULT_WSMAN_OPTIONS;


#if !defined(CONFIG_FAVORSIZE)
    wsmanoptions.enableTracing = MI_TRUE;
#endif
    wsmanoptions.enableHTTPTracing = MI_TRUE;


    memset(&testData, 0, sizeof(testData));
    testData.requestXml = TEST_SENDBODY_REQUEST;

    testData.expectedResult = MI_RESULT_OK;

    /* Need a destination options as there is no default credential option yet */
    if (!NitsCompare(MI_Application_InitializeV1(0, NULL, NULL, &application), MI_RESULT_OK, MI_T("Create application")))
    {
        goto end;
    }
    if (!NitsCompare(CreateDefaultDestinationOptions(&application, &options), MI_RESULT_OK, MI_T("Create default options")))
    {
        goto end1;
    }

    /* Start test-wsman server that gets a callback after the wsman request has been processed */
    if (!NitsCompare(StartWSManInproc(wsmanServerInprocCallback, &testData, &wsmanoptions), MI_RESULT_OK, MI_T("Failed to start wsman server in-process")))
        goto cleanup;

    /* Create the session details */
    miresult = WsmanClient_New_Connector(&wsmanclient, /*shared-selector*/ NULL, "localhost", &options, TestWsmanClientStatusCallback, TestWsmanClientResponseCallback, &testData, NULL, NULL, NULL);
    if (!NitsCompare(miresult, MI_RESULT_OK, MI_T("wsmanclient creation should succeed")))
        goto cleanup;

    page = (Page*) PAL_Malloc(sizeof(Page) + sizeof(TEST_SENDBODY_REQUEST) - 1);
    if (!NitsAssert(page != NULL, MI_T("memory alloc failure")))
        goto cleanup;
    memset(page, 0, sizeof(Page));
    page->u.s.size = sizeof(TEST_SENDBODY_REQUEST)-1;

    text = (char*) (page + 1);
    memcpy(text, TEST_SENDBODY_REQUEST, sizeof(TEST_SENDBODY_REQUEST) - 1);

    miresult = WsmanClient_StartRequest(wsmanclient, &page, &options);
    if (!NitsCompare(miresult, MI_RESULT_OK, MI_T("WsmanClient_StartRequest should succeed")))
        goto cleanup;

    /* Wait until the status thread gets notified of completion */
    while ((testData.completed != 1) && ((miresult = WsmanClient_Run(wsmanclient, 100)) == MI_RESULT_TIME_OUT))
    {
    }

    NitsCompare(miresult, MI_RESULT_TIME_OUT, MI_T("WsmanClient_Run should be a timeout"));
    NitsAssert(testData.completed == 1, MI_T("Status callback should have marked it as completed"));
    NitsCompare(testData.result, MI_RESULT_OK, MI_T("Should successfully send and receive data"));

    miresult = WsmanClient_Delete(wsmanclient);
    NitsCompare(miresult, MI_RESULT_OK, MI_T("wsmanclient should be deleted"));

cleanup:
    StopWSManInproc();

    if (page)
        PAL_Free(page);

    MI_DestinationOptions_Delete(&options);

end1:
    MI_Application_Close(&application);
end:

    ;
}
NitsEndTest
#endif
