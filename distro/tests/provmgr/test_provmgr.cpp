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
#include <set>
#include <cstdlib>
#include <iostream>
#include <ut/ut.h>
#include <provmgr/provmgr.h>
#include <sock/thread.h>
#include <io/io.h>
#include <base/user.h>
#include <base/paths.h>

using namespace std;

static ProvMgr s_provmgr;
static Selector    s_selector;

#if defined(_MSC_VER)
#undef BEGIN_EXTERNC
#undef END_EXTERNC
#define BEGIN_EXTERNC
#define END_EXTERNC
#endif

static void setUp()
{
    Sock_Start();
    Selector_Init(&s_selector);
}

static void cleanup()
{
    Selector_Destroy(&s_selector);
    Sock_Stop();
}

BEGIN_EXTERNC
static void _idleCallback(
    ProvMgr* mgr,
    void* callbackData)
{
    int* p = (int*)callbackData;

    MI_UNUSED(mgr);

    (*p)++;
}
END_EXTERNC

BEGIN_EXTERNC
static void _ResponseCallback(
    Message* msg,
    void* callbackData)
{
    MI_UNUSED(msg);
    MI_UNUSED(callbackData);
}
END_EXTERNC

static void _PostMessage(const char* cn)
{
    EnumerateInstancesReq* msg;
    MI_Result r;

    /* Create new request to send to provider */
    msg = EnumerateInstancesReq_New(0, 0);
    msg->nameSpace = Batch_Zdup(msg->base.batch, MI_T("test/cpp"));
    msg->className = Batch_StrZdup(msg->base.batch, cn);

    if (!msg->nameSpace || !msg->className)
    {
        UT_ASSERT("Out of memory" && NULL);
        EnumerateInstancesReq_Release(msg);
        return;
    }

    /* Setup callback */
    msg->base.callback = _ResponseCallback;
    msg->base.callbackData = 0;

    /* Send the request to provider manager */
    r = ProvMgr_PostMessage(&s_provmgr, "PersonProviderCXX", &msg->base);

    UT_ASSERT_EQUAL(r, MI_RESULT_OK);

    /* Release the original message */
    EnumerateInstancesReq_Release(msg);
}

static void _PostInvokeMessage(const char* fn)
{
    InvokeReq* msg;
    MI_Result r;
    MI_Instance* dynamicInstanceParams = 0;
    Batch   dynamicBatch = BATCH_INITIALIZER;
    MI_String params_cn;

    // Create new request.
    msg = InvokeReq_New(0, 0);

    /* Setup callback */
    msg->base.callback = _ResponseCallback;
    msg->base.callbackData = 0;

    // Extract arguments.
    msg->nameSpace = Batch_StrZdup(msg->base.batch, "test/cpp");
    msg->className = Batch_StrZdup(msg->base.batch, "X_RefuseUnload");
    msg->function = Batch_StrZdup(msg->base.batch, fn);

    /* params */
    {
        /* parameters instance classname is ignored, but has to have valid syntax */
        params_cn = Batch_StrZdup(&dynamicBatch, "param");

        r = Instance_NewDynamic(
            &dynamicInstanceParams,
            params_cn,
            MI_FLAG_CLASS,
            &dynamicBatch);

        UT_ASSERT_EQUAL (MI_RESULT_OK, r);

        msg->instanceParams = dynamicInstanceParams;
    }

    /* Send the request to provider manager */
    r = ProvMgr_PostMessage(&s_provmgr, "PersonProviderCXX", &msg->base);

    UT_ASSERT_EQUAL(r, MI_RESULT_OK);

    InvokeReq_Release(msg);
    Batch_Destroy(&dynamicBatch);
}

static void TestProvmgr_UnloadIdle()
{
    int num = 0;

    UT_ASSERT_EQUAL(
        ProvMgr_Init(&s_provmgr, &s_selector, _idleCallback, &num, GetPath(ID_PROVIDERDIR)),
        MI_RESULT_OK);

    s_provmgr.idleTimeoutUsec = 20000;

    // post message
    _PostMessage("MSFT_Person");

    // run selector to catch timeout
    for (int attempt = 0; attempt < 500 && num == 0; attempt++)
    {
        Selector_Run(&s_selector, 20000);
    }

    // expect idle callback to be invoked once
    UT_ASSERT_EQUAL(1, num);

    UT_ASSERT( MI_RESULT_OK == Selector_RemoveAllHandlers(&s_selector) );
    UT_ASSERT_EQUAL(ProvMgr_Destroy(&s_provmgr), MI_RESULT_OK);
}

static void TestProvmgr_RefuseRequestUnload()
{
    int num = 0;

    UT_ASSERT_EQUAL(
        ProvMgr_Init(&s_provmgr, &s_selector, _idleCallback, &num, GetPath(ID_PROVIDERDIR)),
        MI_RESULT_OK);

    s_provmgr.idleTimeoutUsec = 20000;

    // post message
    _PostMessage("X_RefuseUnload");

    // run selector to catch timeout
    for (int attempt = 0; attempt < 500 && num == 0; attempt++)
    {
        Selector_Run(&s_selector, 20000);
    }

    // expect idle callback not to be invoked
    UT_ASSERT_EQUAL(0, num);

    // call 'request-unload'
    _PostInvokeMessage("RequestUnload");

    // run selector to catch timeout
    for (int attempt = 0; attempt < 500 && num == 0; attempt++)
    {
        Selector_Run(&s_selector, 20000);
    }

    // expect idle provider to be unloaded by now
    UT_ASSERT_EQUAL(1, num);

    UT_ASSERT( MI_RESULT_OK == Selector_RemoveAllHandlers(&s_selector) );
    UT_ASSERT_EQUAL(ProvMgr_Destroy(&s_provmgr), MI_RESULT_OK);
}

static void AllTests()
{
    // test happy-pass case
    UT_TEST(TestProvmgr_UnloadIdle);
    UT_TEST(TestProvmgr_RefuseRequestUnload);
}

UT_ENTRY_POINT(AllTests);
