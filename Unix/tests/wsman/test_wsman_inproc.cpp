/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <vector>
#include <set>
#include <cstdlib>
#include <iostream>
#include <ut/ut.h>
#include <wsman/wsman.h>
#include <sock/sock.h>
#include <pal/thread.h>
#include <pal/format.h>
#include <base/user.h>
#include "utils.h"
#include <base/log.h>

using namespace std;
//using namespace mi;

static WSMAN* s_wsman;
static bool      s_running;
static Thread s_t;
static Selector    s_selector;
static MI_Uint16 PORT = ut::getUnittestPortNumber() + 30;
static bool s_initSelector = false;

#if defined(_MSC_VER)
#undef BEGIN_EXTERNC
#undef END_EXTERNC
#define BEGIN_EXTERNC
#define END_EXTERNC
#endif

void StopWSManInproc()
{
    if (s_running)
    {
        s_running = false;

        PAL_Uint32 ret;
        UT_ASSERT(Thread_Join(&s_t, &ret) == 0);
        Thread_Destroy( &s_t );

        UT_ASSERT( MI_RESULT_OK == Selector_RemoveAllHandlers(&s_selector) );
        UT_ASSERT( MI_RESULT_OK == WSMAN_Delete(s_wsman) );

        s_wsman = 0;
    }
}

static void InitSelector()
{
    if (!s_initSelector)
    {
#if defined(CONFIG_POSIX)
        /* Disable Auth for unit-tests */
        IgnoreAuthCalls(1);
#endif
        //PORT++;

        Sock_Start();
        Selector_Init(&s_selector);
        Timer_SetSelector(&s_selector);
        s_initSelector = true;
    }
}
static void DeinitSelector()
{
    if (s_initSelector)
    {
        Selector_Destroy(&s_selector);
        Sock_Stop();
        s_initSelector = false;
    }
}


NitsSetup(Wsman_Inproc_Setup)
{
    InitSelector();
}

NitsEndSetup

NitsCleanup(Wsman_Inproc_Setup)
{
    StopWSManInproc();
    DeinitSelector();
}

NitsEndCleanup

BEGIN_EXTERNC
static void* MI_CALL _WSMANServerProc(void* )
{
    // pump messages
    for (; s_running; )
        WSMAN_Run( s_wsman, SELECT_BASE_TIMEOUT_MSEC * 1000 );

    return 0;
}
END_EXTERNC

MI_Result StartWSManInproc(
    OpenCallback callback,
    void* callbackData,
    WSMAN_Options* options)
{
    MI_Result result;

    InitSelector();

    if (s_running)
        return MI_RESULT_OK;

    s_running = true;

    result = WSMAN_New_Listener(
        &s_wsman,
        &s_selector,
        PORT,
        0,
        NULL,
        (Server_SSL_Options) 0,
        callback,
        callbackData,
        options);
    if (NitsCompare( MI_RESULT_OK, result, MI_T("Should be able to start listener")))
    {
        NitsCompare(
                MI_RESULT_OK,
                Thread_CreateJoinable( &s_t, (ThreadProc)_WSMANServerProc, NULL, 0),
                MI_T("Failed to create thread"));
    }
    return result;
}

BEGIN_EXTERNC
static string _CreateEnumRequestXML(
    const char* cn )
{
    string res =
"<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\""
"   xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\""
"   xmlns:n=\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\""
"   xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\">"
"<s:Header>"
"<a:To>http://linux-22kv:22000/wsman</a:To>"
"<w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/";

    res += cn;
    res +=
"</w:ResourceURI>"
"<a:ReplyTo>"
"<a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address>"
"</a:ReplyTo>"
"<a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/enumeration/Enumerate</a:Action>"
"<w:MaxEnvelopeSize s:mustUnderstand=\"true\">10240</w:MaxEnvelopeSize>"
"<a:MessageID>uuid:FEF3DF41-FFEC-4ABE-ADFC-A8305DAB71C9</a:MessageID>"
"<w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><w:SelectorSet>"
"<w:Selector Name=\"__cimnamespace\">"
"ns"
"</w:Selector>"
"</w:SelectorSet>"
"<w:OperationTimeout>PT60.000S</w:OperationTimeout>"
"</s:Header>"
"<s:Body>"
"<n:Enumerate>"
"<w:MaxElements>10</w:MaxElements>"
"</n:Enumerate></s:Body></s:Envelope>"
;

    return res;
}
END_EXTERNC

BEGIN_EXTERNC
static string _CreateReleaseRequestXML(const string& ctxID)
{
    string res =
"<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\""
"   xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\""
"   xmlns:n=\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\""
"   xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\">"
"<s:Header>"
"<a:To>http://linux-22kv:22000/wsman</a:To>"
"<w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/"
"cn"
"</w:ResourceURI>"
"<a:ReplyTo>"
"<a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address>"
"</a:ReplyTo>"
"<a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/enumeration/Release</a:Action>"
"<w:MaxEnvelopeSize s:mustUnderstand=\"true\">10240</w:MaxEnvelopeSize>"
"<a:MessageID>uuid:FEF3DF41-FFEC-4ABE-ADFC-A8305DAB71C9</a:MessageID>"
"<w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><w:SelectorSet>"
"<w:Selector Name=\"__cimnamespace\">"
"ns"
"</w:Selector>"
"</w:SelectorSet>"
"<w:OperationTimeout>PT60.000S</w:OperationTimeout>"
"</s:Header>"
"<s:Body>"
"<n:Release>"
"<wsen:EnumerationContext xmlns:wsen=\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\">";

    res += ctxID;
    res +=
"</wsen:EnumerationContext>"
"</n:Release>"
"</s:Body></s:Envelope>"
;

    return res;
}
END_EXTERNC

BEGIN_EXTERNC
void PrintProviderMsg( _In_ Message* msg)
{
}

static void _StrandTestAck( _In_ Strand* self)
{
    // do nothing
}

static void _StrandTestFinished( _In_ Strand* self)
{
    // do nothing
}

static StrandFT strandUserFT1 = {
        NULL,
        NULL,
        _StrandTestAck,
        NULL,
        NULL,
        _StrandTestFinished,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL };

static Strand simpleResult;

STRAND_DEBUGNAME( TestWsman );

static void _callback(
    _Inout_     InteractionOpenParams*    interactionParams )
{
    // reply with result
    MI_Result r = (MI_Result) (long)interactionParams->callbackData;

    PostResultMsg* resp = NULL;

    UT_ASSERT (interactionParams->msg != 0);
    if(interactionParams->msg == 0)
    {
        Strand_FailOpen(interactionParams);
        return;
    }

    resp = PostResultMsg_New( interactionParams->msg->operationId );

    UT_ASSERT (resp != 0);

    resp->result = r;

    Strand_Init( STRAND_DEBUG( TestWsman ) &simpleResult, &strandUserFT1, STRAND_FLAG_ENTERSTRAND, interactionParams );

    Strand_Ack( &simpleResult );   // Ack open
    Strand_Post( &simpleResult, &resp->base );
    Strand_Close( &simpleResult );

    PostResultMsg_Release(resp);
}
END_EXTERNC

// These tests startup wsman for 1 second and
// try to send receive packets within that
// when run with fault injection, it will take lot of test code synchronization
// for these to work; i am not adding that since other tests already cover these code paths
// and so just doing lot of test code changes for fault injecting these tests does not seem worth
NitsTestWithSetup(TestWSMAN_EnumPull, Wsman_Inproc_Setup)
{
    NitsDisableFaultSim;

    StartWSManInproc( _callback, (void*)MI_RESULT_OK);

    // send enum request, expect enum context back (since no OptimzeEnum tag specified)
    Sock s = SockConnectLocal(PORT);
    string r_b, r_h;

    SockSendRecvHTTP(s, false, _CreateEnumRequestXML("InvalidClassname"), r_h, r_b );

    UT_ASSERT(r_b.find("wsen:EnumerationContext") != string::npos);

    string ctxID = GetCtxID(r_b);

    UT_ASSERT(!ctxID.empty());

    // send pull request, expecting 'ok' back
    SockSendRecvHTTP(s, false, CreatePullRequestXML(ctxID), r_h, r_b );

    UT_ASSERT(r_b.find("wsen:EndOfSequence") != string::npos);

    Sock_Close(s);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_EnumRelease, Wsman_Inproc_Setup)
{
    NitsDisableFaultSim;

    StartWSManInproc( _callback, (void*)MI_RESULT_OK);

    // send enum request, expect enum context back (since no OptimzeEnum tag specified)
    Sock s = SockConnectLocal(PORT);
    string r_b, r_h;

    SockSendRecvHTTP(s, false, _CreateEnumRequestXML("InvalidClassname"), r_h, r_b );

    UT_ASSERT(r_b.find("wsen:EnumerationContext") != string::npos);

    string ctxID = GetCtxID(r_b);

    UT_ASSERT(!ctxID.empty());

    // send release request, expecting 'ok' back
    SockSendRecvHTTP(s, false, _CreateReleaseRequestXML(ctxID), r_h, r_b );

    UT_ASSERT(r_b.find("ReleaseResponse") != string::npos);

    // send pull and verify context is invalid
    SockSendRecvHTTP(s, false, CreatePullRequestXML(ctxID), r_h, r_b );

    UT_ASSERT(r_b.find("wsa:DestinationUnreachable") != string::npos);
    UT_ASSERT(r_b.find("Enumeration context not found") != string::npos);

    Sock_Close(s);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_PullWithInvalidCtxID, Wsman_Inproc_Setup)
{
    NitsDisableFaultSim;

    StartWSManInproc( _callback, (void*)MI_RESULT_OK);

    // send enum request, expect enum context back (since no OptimzeEnum tag specified)
    Sock s = SockConnectLocal(PORT);
    string r_b, r_h;

    // sedn pull request with invalid ctx id, expecting 'error' back
    SockSendRecvHTTP(s, false, CreatePullRequestXML("invalid"), r_h, r_b );
    UT_ASSERT(r_b.find("wsa:DestinationUnreachable") != string::npos);
    UT_ASSERT(r_b.find("Enumeration context not found") != string::npos);

    //cout << r_h << endl << r_b <<endl;
    Sock_Close(s);
}
NitsEndTest

