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
#include <nits/base/nits.h>
#include <ut/ut.h>
#include <wsman/wsmanclient.h>
#include "utils.h"

static MI_Uint16 PORT = ut::getUnittestPortNumber() + 30;

typedef struct _TestData
{
    char *requestXml;
    char *responseXml;
} TestData;

static void wsmanServerInprocCallback(
    _Inout_     InteractionOpenParams*    interactionParams )
{
    TestData *testData = (TestData*) interactionParams->callbackData;

    printf("wsmanServerInprocCallback, %p\n", testData);
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

NitsTest(TestWSManClient_CreateDelete)
{
    NitsDisableFaultSim;

    WsmanClient *wsmanclient;
    MI_Result miresult;

    if (!NitsCompare(StartWSManInproc(wsmanServerInprocCallback, NULL, 0), MI_RESULT_OK, MI_T("Failed to start wsman server in-process")))
	goto cleanup;

    miresult = WsmanClient_New_Connector(&wsmanclient, "localhost", PORT, MI_FALSE, NULL, NULL, NULL);
    if (!NitsCompare(miresult, MI_RESULT_OK, MI_T("wsmanclient creation should succeed")))
	goto cleanup;

    miresult = WsmanClient_Delete(wsmanclient);
    NitsCompare(miresult, MI_RESULT_OK, MI_T("wsmanclient should be deleted"));

cleanup:
    StopWSManInproc();
}
NitsEndTest

#if 0
#define TEST_SENDBODY_STRING "<xml>something</xml>"

NitsTest(TestWSManClient_SendBody)
{
    NitsDisableFaultSim;

    WsmanClient *wsmanclient;
    MI_Result miresult;
    Page *page = NULL;
    char *text = NULL;

    miresult = WsmanClient_New_Connector(&wsmanclient, "localhost", PORT, MI_FALSE, NULL, NULL, NULL);
    if (!NitsCompare(miresult, MI_RESULT_OK, "wsmanclient creation should succeed"))
	goto cleanup;

    page = (Page*) PAL_Malloc(sizeof(Page) + sizeof(TEST_SENDBODY_STRING) - 1);
    if (!NitsAssert(page != NULL, "memory alloc failure"))
	goto cleanup;
    memset(page, 0, sizeof(Page));
    page->u.s.size = sizeof(TEST_SENDBODY_STRING)-1;

    text = (char*) page + 1;
    memcpy(text, TEST_SENDBODY_STRING, sizeof(TEST_SENDBODY_STRING) - 1);

    miresult = WsmanClient_StartRequest(wsmanclient, &page);
    if (!NitsCompare(miresult, MI_RESULT_OK, "WsmanClient_StartRequest should succeed"))
	goto cleanup;

    miresult = WsmanClient_Delete(wsmanclient);
    NitsCompare(miresult, MI_RESULT_OK, "wsmanclient should be deleted");

cleanup:
    StopWSManInproc();
}
NitsEndTest
#endif
