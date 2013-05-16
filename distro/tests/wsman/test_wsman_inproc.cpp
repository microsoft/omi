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
#include <wsman/wsman.h>
#include <sock/sock.h>
#include <sock/thread.h>
#include <io/io.h>
#include <base/user.h>
#include "utils.h"

using namespace std;
//using namespace mi;

static WSMAN* s_wsman;
static bool      s_running;
static ThreadHandle s_t;
static Selector    s_selector;
static MI_Uint16 PORT = ut::getUnittestPortNumber() + 30;

#if defined(_MSC_VER)
#undef BEGIN_EXTERNC
#undef END_EXTERNC
#define BEGIN_EXTERNC
#define END_EXTERNC
#endif

static void _StopWSMAN()
{
    if (s_running)
    {
        s_running = false;

        if (s_t)
        {
            UT_ASSERT(MI_RESULT_OK == Thread_Destroy( s_t, MI_TRUE ));
        }

        UT_ASSERT( MI_RESULT_OK == Selector_RemoveAllHandlers(&s_selector) );
        UT_ASSERT( MI_RESULT_OK == WSMAN_Delete(s_wsman) );

        s_t = 0;
        s_wsman = 0;
    }
}

static void setUp()
{
    //PORT++;

    Sock_Start();
    Selector_Init(&s_selector);
}

static void cleanup()
{
    _StopWSMAN();

    Selector_Destroy(&s_selector);
    Sock_Stop();
}

BEGIN_EXTERNC
static void* MI_CALL _WSMANServerProc(void* )
{
    // pump messages
    for (; s_running; )
        WSMAN_Run(s_wsman, 50000);

    return 0;
}
END_EXTERNC

static void _StartWSMAN(
    WSMANCallback callback, 
    void* callbackData, 
    WSMAN_Options* options = 0)
{
    if (s_running)
        return;

    s_running = true;

    UT_ASSERT( MI_RESULT_OK ==  WSMAN_New_Listener(
        &s_wsman,
        &s_selector,
        PORT,
        0,
        NULL,
        callback, 
        callbackData));

    if (options)
    {
        UT_ASSERT( MI_RESULT_OK ==  WSMAN_SetOptions(s_wsman,options));
    }

    UT_ASSERT(MI_RESULT_OK == Thread_Create(
        _WSMANServerProc, 0, &s_t));

}

BEGIN_EXTERNC
static string _CreateEnumRequestXML()
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
static string _CreatePullRequestXML(const string& ctxID)
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
"<a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/enumeration/Pull</a:Action>"
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
"<n:Pull>"
"<wsen:EnumerationContext xmlns:wsen=\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\">";
    
    res += ctxID;
    res += 
"</wsen:EnumerationContext>"
"<n:MaxElements>10000</n:MaxElements>"
"</n:Pull>"
"</s:Body></s:Envelope>"
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
static string _GetCtxID(const string& s)
{
    // llok for <wsen:EnumerationContext>NNN</wsen:EnumerationContext> 
    // and return NNN (or empty string if not found)
    string::size_type pos = s.find("<wsen:EnumerationContext>");
    string::size_type posEnd = s.find("</wsen:EnumerationContext>");

    if ( pos == string::npos ||
        posEnd == string::npos ||
        pos > posEnd )
        return string();

    return s.substr(pos + 25, posEnd - pos -25);
}
END_EXTERNC

BEGIN_EXTERNC
static MI_Boolean _callback(
    WSMAN* protocol,
    Message* message,
    void* data)
{
    // reply with result 
    MI_Result r = (MI_Result) (long)data;

    PostResultMsg* resp;

    resp = PostResultMsg_New( message->msgID );
    resp->base.clientID = message->clientID;

    UT_ASSERT (resp != 0);

    resp->result = r;
    UT_ASSERT(MI_RESULT_OK == WSMAN_Send(protocol, &resp->base));

    PostResultMsg_Release(resp);
    return MI_TRUE;
}
END_EXTERNC


static void TestWSMAN_EnumPull()
{
    _StartWSMAN( _callback, (void*)MI_RESULT_OK);

    // send enum request, expect enum context back (since no OptimzeEnum tag specified)
    Sock s = SockConnectLocal(PORT);
    string r_b, r_h;

    SockSendRecvHTTP(s, false, _CreateEnumRequestXML(), r_h, r_b );

    UT_ASSERT(r_b.find("wsen:EnumerationContext") != string::npos);

    string ctxID = _GetCtxID(r_b);

    //cout << r_h << endl << r_b <<endl << ctxID << endl;
    UT_ASSERT(!ctxID.empty());

    // sedn pull request, expecting 'ok' back
    SockSendRecvHTTP(s, false, _CreatePullRequestXML(ctxID), r_h, r_b );

    //cout << r_h << endl << r_b <<endl << ctxID << endl;
    UT_ASSERT(r_b.find("wsen:EndOfSequence") != string::npos);

    Sock_Close(s);
}

static void TestWSMAN_EnumRelease()
{
    _StartWSMAN( _callback, (void*)MI_RESULT_OK);

    // send enum request, expect enum context back (since no OptimzeEnum tag specified)
    Sock s = SockConnectLocal(PORT);
    string r_b, r_h;

    SockSendRecvHTTP(s, false, _CreateEnumRequestXML(), r_h, r_b );
   
   
    UT_ASSERT(r_b.find("wsen:EnumerationContext") != string::npos);

    string ctxID = _GetCtxID(r_b);

    //cout << r_h << endl << r_b <<endl << ctxID << endl;
    UT_ASSERT(!ctxID.empty());

    // sedn release request, expecting 'ok' back
    SockSendRecvHTTP(s, false, _CreateReleaseRequestXML(ctxID), r_h, r_b );

    //cout << r_h << endl << r_b <<endl << ctxID << endl;
    UT_ASSERT(r_b.find("ReleaseResponse") != string::npos);

    // send pull and verify context is invalid
    SockSendRecvHTTP(s, false, _CreatePullRequestXML(ctxID), r_h, r_b );

    UT_ASSERT(r_b.find("wsa:DestinationUnreachable") != string::npos);
    UT_ASSERT(r_b.find("Enumeration context not found") != string::npos);

    Sock_Close(s);
}

static void TestWSMAN_PullWithInvalidCtxID()
{
    _StartWSMAN( _callback, (void*)MI_RESULT_OK);

    // send enum request, expect enum context back (since no OptimzeEnum tag specified)
    Sock s = SockConnectLocal(PORT);
    string r_b, r_h;

    // sedn pull request with invalid ctx id, expecting 'error' back
    SockSendRecvHTTP(s, false, _CreatePullRequestXML("invalid"), r_h, r_b );
    UT_ASSERT(r_b.find("wsa:DestinationUnreachable") != string::npos);
    UT_ASSERT(r_b.find("Enumeration context not found") != string::npos);

    //cout << r_h << endl << r_b <<endl;
    Sock_Close(s);
}

static void TestWSMAN_PullWithExpiredCtxID()
{
    WSMAN_Options options = {1000}; // 1 ms

    _StartWSMAN( _callback, (void*)MI_RESULT_OK, &options);

    // send enum request, expect enum context back (since no OptimzeEnum tag specified)
    Sock s = SockConnectLocal(PORT);
    string r_b, r_h;

    SockSendRecvHTTP(s, false, _CreateEnumRequestXML(), r_h, r_b );
   
    UT_ASSERT(r_b.find("wsen:EnumerationContext") != string::npos);

    string ctxID = _GetCtxID(r_b);

    //cout << r_h << endl << r_b <<endl << ctxID << endl;
    UT_ASSERT(!ctxID.empty());

    // sleep enough time for context ot expire 
    ut::sleep_ms(50);

    // sedn pull request, expecting 'error' back
    SockSendRecvHTTP(s, false, _CreatePullRequestXML(ctxID), r_h, r_b );

    //cout << r_h << endl << r_b <<endl << ctxID << endl;
    UT_ASSERT(r_b.find("wsa:DestinationUnreachable") != string::npos);
    UT_ASSERT(r_b.find("Enumeration context not found") != string::npos);

    Sock_Close(s);
}

static void TestWSManInproc()
{
#if defined(CONFIG_POSIX)
    /* Disable Auth for unit-tests */
    IgnoreAuthCalls(1);
#endif

    // test happy-pass case
    UT_TEST(TestWSMAN_EnumPull);
    UT_TEST(TestWSMAN_EnumRelease);

    // general errors
    UT_TEST(TestWSMAN_PullWithInvalidCtxID);
    UT_TEST(TestWSMAN_PullWithExpiredCtxID);
}

UT_ENTRY_POINT(TestWSManInproc);
