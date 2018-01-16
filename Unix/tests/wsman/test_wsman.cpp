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
#include <protocol/protocol.h>
#include <sock/sock.h>
#include <pal/format.h>
#include "utils.h"
#include <base/log.h>

using namespace std;

/* Local data */
static Sock s = INVALID_SOCK;
static const char* s_currentNamespace = "";

void SetupHelper();
void CleanupHelper();

NitsSetup(TestWsmanSetup)
{
    s_currentNamespace = "";

    SetupHelper();

    if (INVALID_SOCK == s)
    {
        s = SockConnectLocal(ut::getUnittestPortNumberWSMANHTTP());
    }
}
NitsEndSetup

NitsCleanup(TestWsmanSetup)
{        
    if (INVALID_SOCK != s) Sock_Close(s);

    s = INVALID_SOCK;
    
    CleanupHelper();
}
NitsEndCleanup

static string _CreateRequestXML(
    const char* cn,
    const char* ns,
    const char* enumerationMode = 0,
    const char* maxEnvelopeSize = 0,
    bool    specifyNamespace = true)
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
    res += "</w:ResourceURI>"
"<a:ReplyTo>"
"<a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address>"
"</a:ReplyTo>"
"<a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/enumeration/Enumerate</a:Action>"
"<w:MaxEnvelopeSize s:mustUnderstand=\"true\">";
    
    if (maxEnvelopeSize)
    {
        res += maxEnvelopeSize;
    }
    else
    {
/*
ATTN: try different sizes 
*/
#if 0
        res += "10240";
#else
        res += "102400";
#endif
    }
    
    res += "</w:MaxEnvelopeSize>"
"<a:MessageID>uuid:FEF3DF41-FFEC-4ABE-ADFC-A8305DAB71C9</a:MessageID>"
"<w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><w:SelectorSet>";

    if (specifyNamespace)
    {
        res += 
            "<w:Selector Name=\"__cimnamespace\">";
        res += s_currentNamespace;
        res += ns;
        res += "</w:Selector>";
    }
    else
    {
        res += 
            "<w:Selector Name=\"something\">value</w:Selector>";
    }

    res += 
"</w:SelectorSet>"
"<w:OperationTimeout>PT60.000S</w:OperationTimeout>"
"</s:Header>"
"<s:Body>"
"<n:Enumerate>"
"<w:OptimizeEnumeration/>"
"<w:MaxElements>10</w:MaxElements>";
    if (enumerationMode)
        res += enumerationMode;

    res +=
"</n:Enumerate></s:Body></s:Envelope>"
;
  
    return res;
}

static string _CreateInvokeRequestXML(
    const char* cn,
    const char* ns,
    const char* method, 
    const char* params,
    const char* keys,
    bool    specifyNamespace = true)
{
    string res = 
"<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\""
" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\""
" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\""
" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\">"
"<s:Header><a:To>http://localhost:7778/wsman</a:To><w:ResourceURI s:mustUnderstand=\"true\">"
"http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/";
    
    res += cn;
    res += "</w:ResourceURI><a:ReplyTo><a:Address s:mustUnderstand=\"true\">"
"http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo>"
"<a:Action s:mustUnderstand=\"true\">http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/";
    
    res += cn;
    res += "/";
    res += method;
    res += 
"</a:Action><w:MaxEnvelopeSize s:mustUnderstand=\"true\">32768</w:MaxEnvelopeSize><a:MessageID>"
"uuid:E8928068-D73B-4206-9E95-894088B96288</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" />"
"<p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><w:SelectorSet>";
    
    
    if (specifyNamespace)
    {
        res += 
            "<w:Selector Name=\"__cimnamespace\">";
        res += s_currentNamespace;
        res += ns;
        res += "</w:Selector>";
    }
    else
    {
        res += 
            "<w:Selector Name=\"something\">value</w:Selector>";
    }

    if (keys)
        res += keys;

    res += "</w:SelectorSet><w:OperationTimeout>PT60.000S</w:OperationTimeout></s:Header><s:Body>"
"<p:SpellNumber_INPUT xmlns:p=\"http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/X_smallNumber\">";

    res += params;
    res +=
        "</p:SpellNumber_INPUT></s:Body></s:Envelope>";

    return res;
}

static string _CreateGetRequestXML(
    const char* cn,
    const char* ns,
    const char* keys,
    bool    specifyNamespace = true)
{
    string res = 
"<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\""
" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\""
" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\""
" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\">"
"<s:Header><a:To>http://localhost:7778/wsman</a:To>"
"<w:ResourceURI s:mustUnderstand=\"true\">"
"http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/";
    
    res += cn;
    res += "</w:ResourceURI>"
"<a:ReplyTo><a:Address s:mustUnderstand=\"true\">"
"http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo>"
"<a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Get"
"</a:Action>"
/*
ATTN: remove?
*/
/*"<w:MaxEnvelopeSize s:mustUnderstand=\"true\">327680</w:MaxEnvelopeSize>"*/
"<w:MaxEnvelopeSize s:mustUnderstand=\"true\">327680</w:MaxEnvelopeSize>"
"<a:MessageID>uuid:E8928068-D73B-4206-9E95-894088B96288</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" />"
"<p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" />"
"<w:SelectorSet>";

    if (specifyNamespace)
    {
        res += 
            "<w:Selector Name=\"__cimnamespace\">";
        res += s_currentNamespace;
        res += ns;
        res += "</w:Selector>";
    }
    else
    {
        res += 
            "<w:Selector Name=\"something\">value</w:Selector>";
    }

    if (keys)
        res += keys;

    res += "</w:SelectorSet><w:OperationTimeout>PT60.000S</w:OperationTimeout></s:Header><s:Body>"
"</s:Body></s:Envelope>";

    return res;
}

static string _CreateDeleteRequestXML(
    const char* cn,
    const char* ns,
    const char* keys,
    bool    specifyNamespace = true)
{
    string res = 
"<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\""
" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\""
" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\""
" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\">"
"<s:Header><a:To>http://localhost:7778/wsman</a:To>"
"<w:ResourceURI s:mustUnderstand=\"true\">"
"http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/";
    
    res += cn;
    res += "</w:ResourceURI>"
"<a:ReplyTo><a:Address s:mustUnderstand=\"true\">"
"http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo>"
"<a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Delete"
"</a:Action>"
"<w:MaxEnvelopeSize s:mustUnderstand=\"true\">32768</w:MaxEnvelopeSize>"
"<a:MessageID>uuid:E8928068-D73B-4206-9E95-894088B96288</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" />"
"<p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" />"
"<w:SelectorSet>";

    if (specifyNamespace)
    {
        res += 
            "<w:Selector Name=\"__cimnamespace\">";
        res += s_currentNamespace;
        res += ns;
        res += "</w:Selector>";
    }
    else
    {
        res += 
            "<w:Selector Name=\"something\">value</w:Selector>";
    }

    if (keys)
        res += keys;

    res += "</w:SelectorSet><w:OperationTimeout>PT60.000S</w:OperationTimeout></s:Header><s:Body>"
"</s:Body></s:Envelope>";

    return res;
}

static string _CreateCDATARequestXML(
    const char* ns)
{
    string res = 
        "<env:Envelope xmlns:wsman=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\"" 
              "xmlns:env=\"http://www.w3.org/2003/05/soap-envelope\"" 
              "xmlns:wsa=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\"" 
              "xmlns:wsen=\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\"" 
              "xmlns:tst=\"http://schemas.microsoft.com/2005/02/wsman/test\">"
        "<env:Header><wsa:To env:mustUnderstand=\"true\">http://localhost:7778/wsman</wsa:To>"
        "<wsa:ReplyTo>"
            "<wsa:Address>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:Address>"
            "</wsa:ReplyTo>"
            "<wsa:Action env:mustUnderstand=\"true\"><![CDATA[http://schemas.xmlsoap.org/ws/2004/09/enumeration/Enumerate]]></wsa:Action>"
            "<wsa:MessageID env:mustUnderstand=\"true\">uuid:e953e956-b44d-460e-a1af-4e484a5e5346</wsa:MessageID>"
            "<wsman:ResourceURI env:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/TestClass_AllDMTFTypes</wsman:ResourceURI>"
            "<wsman:OperationTimeout env:mustUnderstand=\"false\">PT30.0S</wsman:OperationTimeout>"
            "<wsman:MaxEnvelopeSize env:mustUnderstand=\"true\">32768</wsman:MaxEnvelopeSize>"
            "<wsman:Locale xml:lang=\"en-US\" env:mustUnderstand=\"false\" />"
            "<wsman:SelectorSet>"
            "<wsman:Selector Name=\"__cimnamespace\">";

    res += ns;
    res += "</wsman:Selector>"
            "</wsman:SelectorSet>"
              "</env:Header>"
              "<env:Body>"
                "<wsen:Enumerate>"
                  "<wsen:Filter Dialect=\"http://schemas.microsoft.com/win/2004/08/events/eventquery\">/node/node[@attribue='']</wsen:Filter>"
                  "<wsen:Enumerate>"
                    "<wsman:OptimizeEnumeration />"
                    "<wsman:MaxElements>32000</wsman:MaxElements>"
                    "<wsman:EnumerationMode>EnumerateObjectAndEPR</wsman:EnumerationMode>"
                  "</wsen:Enumerate>"
                "</wsen:Enumerate>"
              "</env:Body>"
            "</env:Envelope>";

    return res;
}


static string _CreateCreateRequestXML(
    const char* cn,
    const char* ns,
    const char* props,
    bool    specifyNamespace = true)
{
    string res = 
"<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\""
" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\""
" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\""
" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\">"
"<s:Header><a:To>http://localhost:7778/wsman</a:To>"
"<w:ResourceURI s:mustUnderstand=\"true\">"
"http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/";
    
    res += cn;
    res += "</w:ResourceURI>"
"<a:ReplyTo><a:Address s:mustUnderstand=\"true\">"
"http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo>"
"<a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Create"
"</a:Action>"
"<w:MaxEnvelopeSize s:mustUnderstand=\"true\">32768</w:MaxEnvelopeSize>"
"<a:MessageID>uuid:E8928068-D73B-4206-9E95-894088B96288</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" />"
"<p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" />"
"<w:SelectorSet>";

    if (specifyNamespace)
    {
        res += 
            "<w:Selector Name=\"__cimnamespace\">";
        res += s_currentNamespace;
        res += ns;
        res += "</w:Selector>";
    }
    else
    {
        res += 
            "<w:Selector Name=\"something\">value</w:Selector>";
    }


    res += "</w:SelectorSet><w:OperationTimeout>PT60.000S</w:OperationTimeout></s:Header><s:Body>";

    res += props;

    res +=
"</s:Body></s:Envelope>";

    return res;
}

static string _CreateModifyRequestXML(
    const char* cn,
    const char* ns,
    const char* keys,
    const char* props,
    bool    specifyNamespace = true)
{
    string res = 
"<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\""
" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\""
" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\""
" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\">"
"<s:Header><a:To>http://localhost:7778/wsman</a:To>"
"<w:ResourceURI s:mustUnderstand=\"true\">"
"http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/";
    
    res += cn;
    res += "</w:ResourceURI>"
"<a:ReplyTo><a:Address s:mustUnderstand=\"true\">"
"http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo>"
"<a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Put"
"</a:Action>"
"<w:MaxEnvelopeSize s:mustUnderstand=\"true\">32768</w:MaxEnvelopeSize>"
"<a:MessageID>uuid:E8928068-D73B-4206-9E95-894088B96288</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" />"
"<p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" />"
"<w:SelectorSet>";

    if (specifyNamespace)
    {
        res += 
            "<w:Selector Name=\"__cimnamespace\">";
        res += s_currentNamespace;
        res += ns;
        res += "</w:Selector>";
    }
    else
    {
        res += 
            "<w:Selector Name=\"something\">value</w:Selector>";
    }

    if (keys)
        res += keys;

    res += "</w:SelectorSet><w:OperationTimeout>PT60.000S</w:OperationTimeout></s:Header><s:Body>";

    res += props;

    res +=
"</s:Body></s:Envelope>";

    return res;
}

NitsTestWithSetup(TestWSMAN_CDATARequest, TestWsmanSetup)
{
    string r_b, r_h;

    // use utf16 encoding header
    SockSendRecvHTTP(s, true, _CreateCDATARequestXML("test/cpp").c_str(), r_h, r_b );
    // send invalid xml; expecting http 500 back
    UT_ASSERT(r_h.find("500") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMANemptyRequest, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false, "", r_h, r_b );
    // send invalid xml; expecting http 500 back
    UT_ASSERT(r_h.find("500") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMANInvalidXML, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false, "invalid xml", r_h, r_b );
    // send invalid xml; expecting http 500 back
    UT_ASSERT(r_h.find("500") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_NotSupportedEncoding, TestWsmanSetup)
{
    string r_b, r_h;

    // use utf16 encoding header
    SockSendRecvHTTP(s, true, _CreateRequestXML("X_number", "test/cpp").c_str(), r_h, r_b );
    // send not-supported encoding; expecting http 500 back
    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;
    UT_ASSERT(r_h.find("500") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Fault_invalidNamespace, TestWsmanSetup)
{
    string r_b, r_h;
    SockSendRecvHTTP(s, false, _CreateRequestXML("X_number", "invlaid/namespace").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    // send invalid request; expecting http 500 back
    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());
    UT_ASSERT(r_b.find("wsa:DestinationUnreachable") != string::npos);
    UT_ASSERT(r_b.find("OMI:MI_Result:3") != string::npos);
    UT_ASSERT(r_b.find("The target namespace does not exist") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Code xsi:type=\"cim:cimUnsignedInt\">3</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Type xsi:type=\"cim:cimString\">MI</") != string::npos);
}
NitsEndTest

#if 0
NitsTestWithSetup(TestWSMAN_Fault_instanceBiggerThaEnvelope, TestWsmanSetup)
{
    string r_b, r_h;
    SockSendRecvHTTP(s, false, _CreateRequestXML("X_SingletonWithAllTypes", "test/cpp", 0, "8200").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    // send envelope size is not enough to hold one instance; expecting http 500 back
    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());
    UT_ASSERT(r_b.find("wsman:EncodingLimit") != string::npos);
    UT_ASSERT(r_b.find("insufficient envelope size") != string::npos);
}
NitsEndTest
#endif

NitsTestWithSetup(TestWSMAN_Fault_invalidClass, TestWsmanSetup)
{
    string r_b, r_h;
    SockSendRecvHTTP(s, false, _CreateRequestXML("InvalidClassname", "test/cpp").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    // send invalid request; expecting http 500 back
    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());
    UT_ASSERT(r_b.find("wsa:DestinationUnreachable") != string::npos);
    UT_ASSERT(r_b.find("OMI:MI_Result:5") != string::npos);
    UT_ASSERT(r_b.find("The specified class does not exist.") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Code xsi:type=\"cim:cimUnsignedInt\">5</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Type xsi:type=\"cim:cimString\">MI</") != string::npos);
}
NitsEndTest

static void TestWSMAN_Enumerate_XProfileHelper()
{
    string r_b, r_h;
    SockSendRecvHTTP(s, false, _CreateRequestXML("X_Profile", "interop").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());
    UT_ASSERT(r_b.find("World") != string::npos);
    UT_ASSERT(r_b.find("Huge Numbers") != string::npos);
}

NitsTestWithSetup(TestWSMAN_Enumerate_XProfile, TestWsmanSetup)
{
    TestWSMAN_Enumerate_XProfileHelper();
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Enumerate_XProfile1, TestWsmanSetup)
{
    TestWSMAN_Enumerate_XProfileHelper();
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Enumerate_XProfile_EPR_Only, TestWsmanSetup)
{
    string r_b, r_h;
    SockSendRecvHTTP(s, false, _CreateRequestXML("X_Profile", "interop", "<w:EnumerationMode>EnumerateEPR</w:EnumerationMode>").c_str(), r_h, r_b );

    // cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    /* expect EPR back */
    UT_ASSERT(r_b.find("<wsa:EndpointReference>") != string::npos);
    UT_ASSERT(r_b.find("Name=\"InstanceID\">world<") != string::npos);
    UT_ASSERT(r_b.find("Name=\"InstanceID\">number<") != string::npos);

    /* regular properties shuld not be specified */
    UT_ASSERT(r_b.find("World") == string::npos);
    UT_ASSERT(r_b.find("Huge Numbers") == string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Enumerate_XProfile_EPRAndObject, TestWsmanSetup)
{
    string r_b, r_h;
    SockSendRecvHTTP(s, false, _CreateRequestXML("X_Profile", "interop", "<w:EnumerationMode>EnumerateObjectAndEPR</w:EnumerationMode>").c_str(), r_h, r_b );

    // cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    /* expect EPR back */
    UT_ASSERT(r_b.find("<wsa:EndpointReference>") != string::npos);
    UT_ASSERT(r_b.find("Name=\"InstanceID\">world<") != string::npos);
    UT_ASSERT(r_b.find("Name=\"InstanceID\">number<") != string::npos);

    /* and regular properties */
    UT_ASSERT(r_b.find("World") != string::npos);
    UT_ASSERT(r_b.find("Huge Numbers") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Enumerate_X_SingletonWithAllTypes, TestWsmanSetup)
{
    string r_b, r_h;
    SockSendRecvHTTP(s, false, _CreateRequestXML("X_SingletonWithAllTypes", "test/cpp", 0, "640000").c_str(), r_h, r_b );

    // cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data 
    // (see X_SingletonWithAllTypes_Class_Provider.cpp to see how it was created)
    UT_ASSERT(r_b.find("id>1<") != string::npos);
    UT_ASSERT(r_b.find("b>TRUE<") != string::npos);
    UT_ASSERT(r_b.find("u8>172<") != string::npos);
    UT_ASSERT(r_b.find("u16>1745<") != string::npos);

    //    inst.c16_value(1044);
    // in utf8 it's -48, -108 or 0xd0, 0x94
#if 0
    UT_ASSERT(r_b.find("c16>\xd0\x94<") != string::npos);
#else
    UT_ASSERT(r_b.find("c16>1044<") != string::npos);
#endif

    UT_ASSERT(r_b.find("s8>-123<") != string::npos);
    UT_ASSERT(r_b.find("u16>1745<") != string::npos);
    UT_ASSERT(r_b.find("s16>-1746<") != string::npos);
    UT_ASSERT(r_b.find("u32>17567<") != string::npos);
    UT_ASSERT(r_b.find("s32>-17568<") != string::npos);

    UT_ASSERT(r_b.find("u64>18446744073709551613<") != string::npos);
    UT_ASSERT(r_b.find("s64>-9223372036854775805<") != string::npos);
    UT_ASSERT(r_b.find("s>string value<") != string::npos);

    /* due to truncation feature of float numbers, 
        skip comparison of last digit */
    UT_ASSERT(r_b.find("r32>32.3") != string::npos);
    UT_ASSERT(r_b.find("r64>64.646") != string::npos);
    UT_ASSERT(r_b.find("dt>2010-07-14T11:35:11.900675-00:07<") != string::npos);

    // person
    UT_ASSERT(r_b.find("<p:person") != string::npos);
    UT_ASSERT(r_b.find("cim-schema/2/MSFT_Person") != string::npos);
    UT_ASSERT(r_b.find("MSFT_Person_Type\"") != string::npos);
    UT_ASSERT(r_b.find("Last>Smith<") != string::npos);
    UT_ASSERT(r_b.find("First>John<") != string::npos);
    UT_ASSERT(r_b.find("Key>7<") != string::npos);
    UT_ASSERT(r_b.find("</p:person>") != string::npos);

    // fourobjects
    UT_ASSERT(r_b.find("<p:fourObjects") != string::npos);
    UT_ASSERT(r_b.find("</p:fourObjects>") != string::npos);

    // object
    UT_ASSERT(r_b.find("<p:objectSingle") != string::npos);
    UT_ASSERT(r_b.find("cim-schema/2/X_TestObject") != string::npos);
    UT_ASSERT(r_b.find("X_TestObject_Type\"") != string::npos);
    UT_ASSERT(r_b.find("id>9000<") != string::npos);
    //UT_ASSERT(r_b.find("operation>?<") != string::npos);
    UT_ASSERT(r_b.find("right_operand xsi:nil=\"true\"/>") != string::npos);

    // test array values
    UT_ASSERT(r_b.find("bA>TRUE<") != string::npos);
    UT_ASSERT(r_b.find("bA>FALSE<") != string::npos);
    UT_ASSERT(r_b.find("u8A>0<") != string::npos);
    UT_ASSERT(r_b.find("u8A>255<") != string::npos);
    UT_ASSERT(r_b.find("u8A>128<") != string::npos);
    UT_ASSERT(r_b.find("s8A>0<") != string::npos);
    UT_ASSERT(r_b.find("s8A>127<") != string::npos);
    UT_ASSERT(r_b.find("s8A>-128<") != string::npos);
    UT_ASSERT(r_b.find("u16A>0<") != string::npos);
    UT_ASSERT(r_b.find("u16A>64000<") != string::npos);
    UT_ASSERT(r_b.find("s16A>0<") != string::npos);
    UT_ASSERT(r_b.find("s16A>-1216<") != string::npos);
    UT_ASSERT(r_b.find("s16A>258<") != string::npos);

}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Enumerate_X_HugeNumberConformsToProfile, TestWsmanSetup)
{
    // Enumerate Assoc class and verify references are returned properly
    string r_b, r_h;
    SockSendRecvHTTP(s, false, _CreateRequestXML("X_HugeNumberConformsToProfile", "test/cpp").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data 
    UT_ASSERT(r_b.find(":Profile>") != string::npos);
    UT_ASSERT(r_b.find("Name=\"InstanceID\">number<") != string::npos);

    UT_ASSERT(r_b.find("<wsman:Selector Name=\"Number\">1000000</wsman:Selector>") != string::npos);
}
NitsEndTest

/*
 * Missing namespace will default to "interop" namespace
 */
NitsTestWithSetup(TestWSMAN_Enumerate_MissingNamespace, TestWsmanSetup)
{
    string r_b, r_h;
    /* namespace param is missing - expecting error back */
    SockSendRecvHTTP(s, false, _CreateRequestXML("CIM_NonExistClass", "interop", 0, 0, false).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(r_b.find("OMI:MI_Result:5") != string::npos);
    UT_ASSERT(r_b.find("The specified class does not exist.") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Code xsi:type=\"cim:cimUnsignedInt\">5</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Type xsi:type=\"cim:cimString\">MI</") != string::npos);
}
NitsEndTest

#if 0
static void _PrintBuffer(const char* str)
{
    Tprintf(MI_T("\n=========================\n"));
    Tprintf(MI_T("%s\n"), tcs(str));
    Tprintf(MI_T("=========================\n\n"));
}
#endif

NitsTestWithSetup(TestWSMAN_Enumerate_X_HugeNumber_Deep, TestWsmanSetup)
{
    // Enumerate X_HugeNumber - expecting back 3 instances
    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateRequestXML("X_HugeNumber", "test/cpp",
            "<b:PolymorphismMode xmlns:b=\"http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd\">IncludeSubClassProperties</b:PolymorphismMode>"
            ).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    //_PrintBuffer(r_h.c_str());

    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data: expecting three items and property 'Property0'
    // all should present
    UT_ASSERT(r_b.find("Number>1000000<") != string::npos);
    UT_ASSERT(r_b.find("Number>1000000000<") != string::npos);
    UT_ASSERT(r_b.find("Number>1000001<") != string::npos);
    UT_ASSERT(r_b.find("Property0>9<") != string::npos);
    UT_ASSERT(r_b.find("<p:X_Number1000001") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Enumerate_X_HugeNumber_BasicProps, TestWsmanSetup)
{
    // Enumerate X_HugeNumber - expecting back 3 instances
    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateRequestXML("X_HugeNumber", "test/cpp",
            "<b:PolymorphismMode xmlns:b=\"http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd\">ExcludeSubClassProperties</b:PolymorphismMode>"
            ).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data: expecting three items and property 'Property0'
    // 3 instances are expected, but no sub-class properties/sub-class name
    UT_ASSERT(r_b.find("Number>1000000<") != string::npos);
    UT_ASSERT(r_b.find("Number>1000000000<") != string::npos);
    UT_ASSERT(r_b.find("Number>1000001<") != string::npos);

    UT_ASSERT(r_b.find("Property0>9<") == string::npos);
    UT_ASSERT(r_b.find("<p:X_Number1000001") == string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Enumerate_X_HugeNumber_Shallow, TestWsmanSetup)
{
    // Enumerate X_HugeNumber - expecting back 3 instances
    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateRequestXML("X_HugeNumber", "test/cpp",
            "<b:PolymorphismMode xmlns:b=\"http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd\">None</b:PolymorphismMode>"
            ).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data: expecting three items and property 'Property0'
    // only 2 instances are expected - exact class match
    UT_ASSERT(r_b.find("Number>1000000<") != string::npos);
    UT_ASSERT(r_b.find("Number>1000000000<") != string::npos);

    UT_ASSERT(r_b.find("Number>1000001<") == string::npos);
    UT_ASSERT(r_b.find("Property0>9<") == string::npos);
    UT_ASSERT(r_b.find("<p:X_Number1000001") == string::npos);
}
NitsEndTest

static void TestWSMAN_Invoke_SmallNumber_SpellNumberHelper()
{
    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateInvokeRequestXML("X_Smallnumber", "test/cpp", "spellNumber", "<p:num>77</p:num>", "").c_str(), r_h, r_b );

    // cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data 
    UT_ASSERT(r_b.find("ReturnValue>seventy seven<") != string::npos);
}

NitsTestWithSetup(TestWSMAN_Invoke_SmallNumber_SpellNumber, TestWsmanSetup)
{
    TestWSMAN_Invoke_SmallNumber_SpellNumberHelper();
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Invoke_SmallNumber_SpellNumber1, TestWsmanSetup)
{
    TestWSMAN_Invoke_SmallNumber_SpellNumberHelper();
}
NitsEndTest

/*
 * Missing namespace will default to "interop" namespace
 */
NitsTestWithSetup(TestWSMAN_Invoke_MissingNamespace, TestWsmanSetup)
{
    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateInvokeRequestXML("CIM_NonExistClass", "test/cpp", "spellNumber", "<p:num>77</p:num>", "", false).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data 
    UT_ASSERT(r_b.find("OMI:MI_Result:5") != string::npos);
    UT_ASSERT(r_b.find("The specified class does not exist.") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Code xsi:type=\"cim:cimUnsignedInt\">5</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Type xsi:type=\"cim:cimString\">MI</") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Invoke_SmallNumber_SpellNumber_OOP, TestWsmanSetup)
{
    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateInvokeRequestXML("X_Smallnumber", "oop/requestor/test/cpp", "spellNumber", "<p:num>77</p:num>", "").c_str(), r_h, r_b );

    // cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data 
    UT_ASSERT(r_b.find("ReturnValue>seventy seven<") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Invoke_TestEmbeddedObjectReturnKey20100609, TestWsmanSetup)
{
    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateInvokeRequestXML("TestEmbeddedOperations", "test/cpp", "TestEmbeddedObjectReturnKey20100609", "", "<w:Selector Name=\"key\">1</w:Selector>").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;
    if (r_h.find("200") == string::npos)
        cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    // _PrintBuffer(r_h.c_str());

    // send invalid request; expecting http 500 back
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // _PrintBuffer(r_b.c_str());

    // check data 
    UT_ASSERT(r_b.find("ObjectID>20100609<") != string::npos);
    UT_ASSERT(r_b.find("X_TestEmbeddedObjectNotReferenced") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Invoke_TestEmbeddedObjectReturnKey20100609_OOP, TestWsmanSetup)
{
    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateInvokeRequestXML("TestEmbeddedOperations", "oop/requestor/test/cpp", "TestEmbeddedObjectReturnKey20100609", "", "<w:Selector Name=\"key\">1</w:Selector>").c_str(), r_h, r_b );

    // cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    // send invalid request; expecting http 500 back
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data 
    UT_ASSERT(r_b.find("ObjectID>20100609<") != string::npos);
    UT_ASSERT(r_b.find("X_TestEmbeddedObjectNotReferenced") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Invoke_TestEmbedded, TestWsmanSetup)
{
const char* c_embeddedInstance = 
"<p:objectsArray xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\
        xmlns:q=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/MSFT_Base\" xsi:type=\"MSFT_Base_Type\">\
      <q:Key>101</q:Key>\
  </p:objectsArray>";

    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateInvokeRequestXML("TestEmbeddedOperations", "test/cpp", "TestEmbedded", c_embeddedInstance, "<w:Selector Name=\"key\">1</w:Selector>").c_str(), r_h, r_b );

    // cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data 
    UT_ASSERT(r_b.find("Key>101<") != string::npos);
    UT_ASSERT(r_b.find("Species>test<") != string::npos);
    UT_ASSERT(r_b.find("MSFT_Animal") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Invoke_TestEmbeddedWithArray, TestWsmanSetup)
{
const char* c_embeddedInstance = 
"\
        <p:objectsArray xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:q=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/MSFT_Base\" xsi:type=\"MSFT_Base_Type\">\
            <q:Key>101</q:Key>\
        </p:objectsArray>\
        <p:objectsArray xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:q=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/MSFT_Base\" xsi:type=\"MSFT_Base_Type\">\
            <q:Key>102</q:Key>\
        </p:objectsArray>\
        <p:objectsArray xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:q=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/MSFT_Base\" xsi:type=\"MSFT_Base_Type\">\
            <q:Key>103</q:Key>\
        </p:objectsArray>\
  ";

    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateInvokeRequestXML("TestEmbeddedOperations", "test/cpp", "TestEmbedded", c_embeddedInstance, "<w:Selector Name=\"key\">1</w:Selector>").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data 
    UT_ASSERT(r_b.find("Key>101<") != string::npos);
    UT_ASSERT(r_b.find("Key>102<") != string::npos);
    UT_ASSERT(r_b.find("Key>103<") != string::npos);
    UT_ASSERT(r_b.find("Species>test<") != string::npos);
    UT_ASSERT(r_b.find("MSFT_Animal") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Invoke_TestEmbeddedWithMultipleArrays, TestWsmanSetup)
{
const char* c_embeddedInstance = 
"\
<p:objectsArray xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\
        xmlns:q=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/MSFT_Base\" xsi:type=\"MSFT_Base_Type\">\
      <q:Key>101</q:Key>\
  </p:objectsArray>\
<p:objectsArray xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\
        xmlns:q=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/MSFT_Base\" xsi:type=\"MSFT_Base_Type\">\
      <q:Key>102</q:Key>\
  </p:objectsArray>\
<p:objectsArray xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\
        xmlns:q=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/MSFT_Base\" xsi:type=\"MSFT_Base_Type\">\
      <q:Key>103</q:Key>\
  </p:objectsArray>\
\
  <p:testObjectsArray xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\
        xmlns:q=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/MSFT_Base\" xsi:type=\"X_TestObject_Type\">\
      <q:id>9000109</q:id>\
  </p:testObjectsArray>\
  <p:testObjectsArray xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\
        xmlns:q=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/MSFT_Base\" xsi:type=\"X_TestObject_Type\">\
      <q:str>some string</q:str>\
      <q:id>9000209</q:id>\
  </p:testObjectsArray>\
  <p:testObjectsArray xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\
        xmlns:q=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/MSFT_Base\" xsi:type=\"X_TestObject_Type\">\
      <q:id>9000309</q:id>\
      <q:str>+</q:str>\
      <q:result>1719</q:result>\
  </p:testObjectsArray>\
  ";

    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateInvokeRequestXML("TestEmbeddedOperations", "test/cpp", "TestEmbedded", c_embeddedInstance, "<w:Selector Name=\"key\">1</w:Selector>").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data 
    UT_ASSERT(r_b.find("Key>101<") != string::npos);
    UT_ASSERT(r_b.find("Key>102<") != string::npos);
    UT_ASSERT(r_b.find("Key>103<") != string::npos);
    UT_ASSERT(r_b.find("Species>test<") != string::npos);
    UT_ASSERT(r_b.find("MSFT_Animal") != string::npos);

    UT_ASSERT(r_b.find("ReturnValue") != string::npos);
    UT_ASSERT(r_b.find("X_TestObject") != string::npos);
    UT_ASSERT(r_b.find("id>27000627<") != string::npos);
    UT_ASSERT(r_b.find("id>9000309<") != string::npos);
    UT_ASSERT(r_b.find("result>1719<") != string::npos);
    UT_ASSERT(r_b.find("str>some string<") != string::npos);

}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Invoke_TestAllTypesWithSingleItemArray, TestWsmanSetup)
{
const char* c_Params = 
"\
  <p:b>false</p:b>\
  <p:u8>90</p:u8>\
  <p:u8A>13</p:u8A>\
  <p:u8A>14</p:u8A>\
  <p:s16A>-9</p:s16A>\
  ";

    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateInvokeRequestXML("MSFT_Person", "test/cpp", "TestAllTypes", c_Params, "<w:Selector Name=\"key\">777</w:Selector>").c_str(), r_h, r_b );

    // cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data 
    UT_ASSERT(r_b.find("u8A>2<") != string::npos);
    UT_ASSERT(r_b.find("u8A>27<") != string::npos);
    UT_ASSERT(r_b.find("u8>91<") != string::npos);
    UT_ASSERT(r_b.find("b>TRUE<") != string::npos);
    UT_ASSERT(r_b.find("s16A>1<") != string::npos);
    UT_ASSERT(r_b.find("s16A>-9<") != string::npos);
}
NitsEndTest

/* verify array buffer re-allocation (16 items boundary)*/
NitsTestWithSetup(TestWSMAN_Invoke_TestAllTypesWith17ItemsArray, TestWsmanSetup)
{
const char* c_Params = 
"\
  <p:u64A>1</p:u64A>\
  <p:u64A>2</p:u64A>\
  <p:u64A>3</p:u64A>\
  <p:u64A>4</p:u64A>\
  <p:u64A>5</p:u64A>\
  <p:u64A>6</p:u64A>\
  <p:u64A>7</p:u64A>\
  <p:u64A>8</p:u64A>\
  <p:u64A>9</p:u64A>\
  <p:u64A>10</p:u64A>\
  <p:u64A>11</p:u64A>\
  <p:u64A>12</p:u64A>\
  <p:u64A>13</p:u64A>\
  <p:u64A>14</p:u64A>\
  <p:u64A>15</p:u64A>\
  <p:u64A>16</p:u64A>\
  <p:u64A>17</p:u64A>\
  ";

    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateInvokeRequestXML("MSFT_Person", "test/cpp", "TestAllTypes", c_Params, "<w:Selector Name=\"key\">777</w:Selector>").c_str(), r_h, r_b );

    // cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find("u64A>17<") != string::npos);
    UT_ASSERT(r_b.find("u64A>153<") != string::npos);
}
NitsEndTest

/* verify array two buffer re-allocations (16 items boundary)*/
NitsTestWithSetup(TestWSMAN_Invoke_TestAllTypesWith33ItemsArray, TestWsmanSetup)
{
const char* c_Params = 
"\
  <p:u64A>1</p:u64A>\
  <p:u64A>2</p:u64A>\
  <p:u64A>3</p:u64A>\
  <p:u64A>4</p:u64A>\
  <p:u64A>5</p:u64A>\
  <p:u64A>6</p:u64A>\
  <p:u64A>7</p:u64A>\
  <p:u64A>8</p:u64A>\
  <p:u64A>9</p:u64A>\
  <p:u64A>10</p:u64A>\
  <p:u64A>11</p:u64A>\
  <p:u64A>12</p:u64A>\
  <p:u64A>13</p:u64A>\
  <p:u64A>14</p:u64A>\
  <p:u64A>15</p:u64A>\
  <p:u64A>16</p:u64A>\
  <p:u64A>17</p:u64A>\
  <p:u64A>18</p:u64A>\
  <p:u64A>19</p:u64A>\
  <p:u64A>20</p:u64A>\
  <p:u64A>21</p:u64A>\
  <p:u64A>22</p:u64A>\
  <p:u64A>23</p:u64A>\
  <p:u64A>24</p:u64A>\
  <p:u64A>25</p:u64A>\
  <p:u64A>26</p:u64A>\
  <p:u64A>27</p:u64A>\
  <p:u64A>28</p:u64A>\
  <p:u64A>29</p:u64A>\
  <p:u64A>30</p:u64A>\
  <p:u64A>31</p:u64A>\
  <p:u64A>32</p:u64A>\
  <p:u64A>33</p:u64A>\
  ";

    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateInvokeRequestXML("MSFT_Person", "test/cpp", "TestAllTypes", c_Params, "<w:Selector Name=\"key\">777</w:Selector>").c_str(), r_h, r_b );

    // cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find("u64A>33<") != string::npos);
    UT_ASSERT(r_b.find("u64A>561<") != string::npos);
}
NitsEndTest

/* verify u64 type operations */
NitsTestWithSetup(TestWSMAN_Invoke_TestAllTypesU64Max, TestWsmanSetup)
{
    /*u64 max is 18446744073709551615; expect it as sum of two items */
const char* c_Params = 
"\
  <p:u64A>18446744073709551610</p:u64A>\
  <p:u64A>5</p:u64A>\
  ";

    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateInvokeRequestXML("MSFT_Person", "test/cpp", "TestAllTypes", c_Params, "<w:Selector Name=\"key\">777</w:Selector>").c_str(), r_h, r_b );

    // cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find("u64A>2<") != string::npos);
    UT_ASSERT(r_b.find("u64A>18446744073709551615<") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Invoke_TestAllTypesStringArray, TestWsmanSetup)
{
    /* unit-test expects exactly two strings and retunr 3 strings: substrings form first two plus '*'*/
const char* c_Params = 
"\
  <p:sA>123456</p:sA>\
  <p:sA>abcdef</p:sA>\
  ";

    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateInvokeRequestXML("MSFT_Person", "test/cpp", "TestAllTypes", c_Params, "<w:Selector Name=\"key\">777</w:Selector>").c_str(), r_h, r_b );

    // cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find("sA>456<") != string::npos);
    UT_ASSERT(r_b.find("sA>def<") != string::npos);
    UT_ASSERT(r_b.find("sA>*<") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Invoke_TestAllTypesReference, TestWsmanSetup)
{
    /* unit-test expects a reference parameter and returns reference to the same class with key++ */
const char* c_Params = 
"\
  <p:rf>\
    <a:Address xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\">\
      http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous\
    </a:Address>\
    <a:ReferenceParameters xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\">\
      <w:ResourceURI>\
        http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/MSFT_Base\
      </w:ResourceURI>\
      <w:SelectorSet>\
        <w:Selector Name=\"Key\">89</w:Selector>\
      </w:SelectorSet>\
    </a:ReferenceParameters>\
  </p:rf>\
  ";

    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateInvokeRequestXML("MSFT_Person", "test/cpp", "TestAllTypes", c_Params, "<w:Selector Name=\"key\">777</w:Selector>").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find("Selector Name=\"Key\">90<") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Get_SmallNumber_17, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false, 
        _CreateGetRequestXML("X_smallNumber", "test/cpp", "<w:Selector Name=\"Number\">17</w:Selector>").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // _PrintBuffer(r_h.c_str());
    // _PrintBuffer(r_b.c_str());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse</") != string::npos);
    UT_ASSERT(r_b.find("Number>17<") != string::npos);
    UT_ASSERT(r_b.find("SpelledNumber>seventeen<") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Get_SmallNumber_NotFound, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false, 
        _CreateGetRequestXML("X_smallNumber", "test/cpp", "<w:Selector Name=\"Number\">17000</w:Selector>").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find("CIM ERROR:NOT_FOUND") != string::npos);
    UT_ASSERT(r_b.find("Value>wsa:DestinationUnreachable<") != string::npos);
    
    UT_ASSERT(r_b.find("OMI:MI_Result:6") != string::npos);
    UT_ASSERT(r_b.find("The requested object cannot be found.") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Code xsi:type=\"cim:cimUnsignedInt\">6</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Type xsi:type=\"cim:cimString\">MI</") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Get_Person_CimError, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false, 
        _CreateGetRequestXML("MSFT_Person", "test/c", "<w:Selector Name=\"key\">9999</w:Selector>").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data for some CIM_Error type stuff
    UT_ASSERT(r_b.find("CIM_ERR_SERVER_IS_SHUTTING_DOWN") != string::npos);
    UT_ASSERT(r_b.find("This is a test CIM Error") != string::npos);
    UT_ASSERT(r_b.find("Value>wsman:InternalError<") != string::npos);
    UT_ASSERT(r_b.find("<p:CIM_Error") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Get_Person_CustomCimError, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false, 
        _CreateGetRequestXML("MSFT_Person", "test/c", "<w:Selector Name=\"key\">9998</w:Selector>").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data for some CIM_Error type stuff
    UT_ASSERT(r_b.find("CIM_ERR_SERVER_IS_SHUTTING_DOWN") != string::npos);
    UT_ASSERT(r_b.find("This is a test CIM Error") != string::npos);
    UT_ASSERT(r_b.find("Value>wsman:InternalError<") != string::npos);
    UT_ASSERT(r_b.find("<p:My_CIM_Error") != string::npos);
}
NitsEndTest

/*
 * Missing namespace will default to "interop" namespace
 */
NitsTestWithSetup(TestWSMAN_Get_MissingNamespace, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false, 
        _CreateGetRequestXML("CIM_NonExistClass", "test/cpp", "<w:Selector Name=\"Number\">17</w:Selector>", false).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find("OMI:MI_Result:5") != string::npos);
    UT_ASSERT(r_b.find("The specified class does not exist.") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Code xsi:type=\"cim:cimUnsignedInt\">5</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Type xsi:type=\"cim:cimString\">MI</") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Delete_SmallNumber_7, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false, 
        _CreateDeleteRequestXML("X_smallNumber", "test/cpp", "<w:Selector Name=\"Number\">7</w:Selector>").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/DeleteResponse</") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Delete_SmallNumber_17_NotFound, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false, 
        _CreateDeleteRequestXML("X_smallNumber", "test/cpp", "<w:Selector Name=\"Number\">17</w:Selector>").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find("Value>wsa:DestinationUnreachable<") != string::npos);
    UT_ASSERT(r_b.find("OMI:MI_Result:6") != string::npos);
    UT_ASSERT(r_b.find("The requested object cannot be found.") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Code xsi:type=\"cim:cimUnsignedInt\">6</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Type xsi:type=\"cim:cimString\">MI</") != string::npos);
}
NitsEndTest

/*
 * Missing namespace will default to "interop" namespace
 */
NitsTestWithSetup(TestWSMAN_Delete_MissingNamespace, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false, 
        _CreateDeleteRequestXML("CIM_NonExistClass", "test/cpp", "<w:Selector Name=\"Number\">7</w:Selector>", false).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find("OMI:MI_Result:5") != string::npos);
    UT_ASSERT(r_b.find("The specified class does not exist.") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Code xsi:type=\"cim:cimUnsignedInt\">5</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Type xsi:type=\"cim:cimString\">MI</") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Create_SmallNumber_ok, TestWsmanSetup)
{
    string r_b, r_h;
    const char* props = 
"<p:X_smallNumber xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/X_smallNumber\">"
"      <p:Description>text</p:Description>"
"  </p:X_smallNumber>";

    SockSendRecvHTTP(s, false, 
        _CreateCreateRequestXML("X_smallNumber", "test/cpp", props).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/CreateResponse</") != string::npos);
    UT_ASSERT(r_b.find("Name=\"Number\">10000<") != string::npos);
    UT_ASSERT(r_b.find("wxf:ResourceCreated>") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Create_SmallNumber_failed_invalid_prop, TestWsmanSetup)
{
    /* invalid property set */
    string r_b, r_h;
    const char* props = 
"<p:X_smallNumber xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/X_smallNumber\">"
"      <p:Description>text</p:Description>"
"      <p:InvalidProp>text</p:InvalidProp>"
"  </p:X_smallNumber>";

    SockSendRecvHTTP(s, false, 
        _CreateCreateRequestXML("X_smallNumber", "test/cpp", props).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find(">OMI:MI_Result:12</") != string::npos);
    UT_ASSERT(r_b.find(">The specified property does not exist.</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Code xsi:type=\"cim:cimUnsignedInt\">12</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Type xsi:type=\"cim:cimString\">MI</") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Create_SmallNumber_failed_no_description, TestWsmanSetup)
{
    string r_b, r_h;
    const char* props = 
"<p:X_smallNumber xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/X_smallNumber\">"
"      <p:Number>7</p:Number>"
"  </p:X_smallNumber>";

    SockSendRecvHTTP(s, false, 
        _CreateCreateRequestXML("X_smallNumber", "test/cpp", props).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    /* when description is not specified, provider returns 'not-found' */
    // check data - 
    UT_ASSERT(r_b.find("OMI:MI_Result:6") != string::npos);
    UT_ASSERT(r_b.find("The requested object cannot be found.") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Code xsi:type=\"cim:cimUnsignedInt\">6</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Type xsi:type=\"cim:cimString\">MI</") != string::npos);
}
NitsEndTest

/*
 * Missing namespace will default to "interop" namespace
 */
NitsTestWithSetup(TestWSMAN_Create_SmallNumber_MissingNamespace, TestWsmanSetup)
{
    string r_b, r_h;
    const char* props = 
"<p:CIM_NonExistClass xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/CIM_NonExistClass\">"
"      <p:Description>text</p:Description>"
"  </p:CIM_NonExistClass>";

    SockSendRecvHTTP(s, false, 
        _CreateCreateRequestXML("CIM_NonExistClass", "test/cpp", props, false).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find("OMI:MI_Result:5") != string::npos);
    UT_ASSERT(r_b.find("The specified class does not exist.") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Code xsi:type=\"cim:cimUnsignedInt\">5</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Type xsi:type=\"cim:cimString\">MI</") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Modify_SmallNumber_ok, TestWsmanSetup)
{
    string r_b, r_h;
    const char* props = 
"<p:X_smallNumber xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/X_smallNumber\">"
"      <p:Description>text</p:Description>"
"  </p:X_smallNumber>";
    const char* keys = "<w:Selector Name=\"Number\">7</w:Selector>";

    SockSendRecvHTTP(s, false, 
        _CreateModifyRequestXML("X_smallNumber", "test/cpp", keys, props).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/PutResponse</") != string::npos);
    UT_ASSERT(r_b.find("Number>10000<") != string::npos);
    UT_ASSERT(r_b.find("Description>text<") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Modify_ProviderPostsInstance, TestWsmanSetup)
{
    string r_b, r_h;
    const char* props = "<p:MSFT_Person xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/MSFT_Person\">"
"      <p:Species>Monkey</p:Species>"
"  </p:MSFT_Person>";
    const char* keys = "<w:Selector Name=\"key\">1234</w:Selector>";

    SockSendRecvHTTP(s, false, 
        _CreateModifyRequestXML("MSFT_Person", "test/c", keys, props).c_str(), r_h, r_b );

    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/PutResponse</") != string::npos);
    UT_ASSERT(r_b.find("Key>1234<") != string::npos);
    UT_ASSERT(r_b.find("Species>Monkey<") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Modify_RelyOnGetForPostInstance, TestWsmanSetup)
{
    string r_b, r_h;
    const char* props = "<p:MSFT_Person xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/MSFT_Person\">"
        "      <p:Species>Monkey</p:Species>"
        "  </p:MSFT_Person>";
    const char* keys = "<w:Selector Name=\"key\">1235</w:Selector>";

    SockSendRecvHTTP(s, false,
        _CreateModifyRequestXML("MSFT_Person", "test/c", keys, props).c_str(), r_h, r_b);

    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());

    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/PutResponse</") != string::npos);
    UT_ASSERT(r_b.find("Key>1235<") != string::npos);
    UT_ASSERT(r_b.find("Species>GetForModify<") != string::npos);
}
NitsEndTest


NitsTestWithSetup(TestWSMAN_Modify_SmallNumber_failed_invalid_prop, TestWsmanSetup)
{
    /* invalid property set */
    string r_b, r_h;
    const char* props = 
"<p:X_smallNumber xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/X_smallNumber\">"
"      <p:Description>text</p:Description>"
"      <p:InvalidProp>text</p:InvalidProp>"
"  </p:X_smallNumber>";
    const char* keys = "<w:Selector Name=\"Number\">7</w:Selector>";

    SockSendRecvHTTP(s, false, 
        _CreateModifyRequestXML("X_smallNumber", "test/cpp", keys, props).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find(">OMI:MI_Result:12</") != string::npos);
    UT_ASSERT(r_b.find("The specified property does not exist.") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Code xsi:type=\"cim:cimUnsignedInt\">12</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Type xsi:type=\"cim:cimString\">MI</") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_Modify_SmallNumber_failed_no_description, TestWsmanSetup)
{
    string r_b, r_h;
    const char* props = 
"<p:X_smallNumber xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/X_smallNumber\">"
"      <p:SpelledNumber>Seven</p:SpelledNumber>"
"  </p:X_smallNumber>";
    const char* keys = "<w:Selector Name=\"Number\">7</w:Selector>";

    SockSendRecvHTTP(s, false, 
        _CreateModifyRequestXML("X_smallNumber", "test/cpp", keys, props).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    /* when description is not specified, provider returns 'not-found' */
    // check data - 
    UT_ASSERT(r_b.find("OMI:MI_Result:6") != string::npos);
    UT_ASSERT(r_b.find("The requested object cannot be found.") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Code xsi:type=\"cim:cimUnsignedInt\">6</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Type xsi:type=\"cim:cimString\">MI</") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_TestImproperXsiType, TestWsmanSetup)
{
    /* Case 1: xsi:type ="" */

    string r_b, r_h;
    string res = "<env:Envelope xmlns:wsman=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" \
     xmlns:env=\"http://www.w3.org/2003/05/soap-envelope\" \
     xmlns:wsa=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" \
     xmlns:tst=\"http://schemas.microsoft.com/2005/02/wsman/test\"> \
     <env:Header><wsa:To env:mustUnderstand=\"true\">http://localhost:7778/wsman</wsa:To> \
     <wsa:ReplyTo><wsa:Address>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:Address></wsa:ReplyTo> \
     <wsa:Action env:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Create</wsa:Action> \
     <wsa:MessageID env:mustUnderstand=\"true\">uuid:cd965798-cc09-4b8f-b176-22d98390b34e</wsa:MessageID> \
     <wsman:ResourceURI env:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/TestClass_AllDMTFTypes</wsman:ResourceURI> \
     <wsman:OperationTimeout env:mustUnderstand=\"false\">PT30.0S</wsman:OperationTimeout> \
     <wsman:MaxEnvelopeSize env:mustUnderstand=\"true\">32768</wsman:MaxEnvelopeSize> \
     <wsman:Locale env:mustUnderstand=\"false\" xml:lang=\"en-US\"/> \
     <wsman:SelectorSet><wsman:Selector Name=\"__cimnamespace\">root/cimv2</wsman:Selector></wsman:SelectorSet> \
     <wsman:OptionSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><wsman:Option Type=\"xs:string\" Name=\"wmiarray:__MIInstanceModifiedPropertiesList\">v_Key</wsman:Option> \
     <wsman:Option Type=\"xs:int\" Name=\"__MI_CallbackRegistration\">11</wsman:Option><wsman:Option Type=\"xs:unsignedInt\" Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\">0</wsman:Option> \
     <wsman:Option Type=\"xs:unsignedInt\" Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\">1</wsman:Option><wsman:Option Type=\"xs:unsignedInt\" Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\">2</wsman:Option> \
     <wsman:Option Type=\"xs:unsignedInt\" Name=\"wmi:__MI_OPERATIONOPTIONS_WRITEERRORMODE\">1</wsman:Option><wsman:Option Type=\"xs:boolean\" Name=\"msftwinrm:UsePreciseArrays\">true</wsman:Option> \
     <wsman:Option Type=\"xs:boolean\" Name=\"msftwinrm:includepropertymetadata\">true</wsman:Option></wsman:OptionSet></env:Header> \
     <env:Body><p0:TestClass_AllDMTFTypes xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" \
     xmlns:p0=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/TestClass_AllDMTFTypes\" \
     xsi:type=\"\"><p0:v_Key xsi:type=\"cim:cimUnsignedLong\">100</p0:v_Key></p0:TestClass_AllDMTFTypes></env:Body></env:Envelope>" ;

    SockSendRecvHTTP(s, false, res.c_str(), r_h, r_b );
    UT_ASSERT(r_h.find("500") != string::npos);

    /* Case 2: xsi:type ="<content>" */

    res = "<env:Envelope xmlns:wsman=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" \
     xmlns:env=\"http://www.w3.org/2003/05/soap-envelope\" \
     xmlns:wsa=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" \
     xmlns:tst=\"http://schemas.microsoft.com/2005/02/wsman/test\"> \
     <env:Header><wsa:To env:mustUnderstand=\"true\">http://localhost:7778/wsman</wsa:To> \
     <wsa:ReplyTo><wsa:Address>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:Address></wsa:ReplyTo> \
     <wsa:Action env:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Create</wsa:Action> \
     <wsa:MessageID env:mustUnderstand=\"true\">uuid:cd965798-cc09-4b8f-b176-22d98390b34e</wsa:MessageID> \
     <wsman:ResourceURI env:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/TestClass_AllDMTFTypes</wsman:ResourceURI> \
     <wsman:OperationTimeout env:mustUnderstand=\"false\">PT30.0S</wsman:OperationTimeout> \
     <wsman:MaxEnvelopeSize env:mustUnderstand=\"true\">32768</wsman:MaxEnvelopeSize> \
     <wsman:Locale env:mustUnderstand=\"false\" xml:lang=\"en-US\"/> \
     <wsman:SelectorSet><wsman:Selector Name=\"__cimnamespace\">root/cimv2</wsman:Selector></wsman:SelectorSet> \
     <wsman:OptionSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><wsman:Option Type=\"xs:string\" Name=\"wmiarray:__MIInstanceModifiedPropertiesList\">v_Key</wsman:Option> \
     <wsman:Option Type=\"xs:int\" Name=\"__MI_CallbackRegistration\">11</wsman:Option><wsman:Option Type=\"xs:unsignedInt\" Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\">0</wsman:Option> \
     <wsman:Option Type=\"xs:unsignedInt\" Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\">1</wsman:Option><wsman:Option Type=\"xs:unsignedInt\" Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\">2</wsman:Option> \
     <wsman:Option Type=\"xs:unsignedInt\" Name=\"wmi:__MI_OPERATIONOPTIONS_WRITEERRORMODE\">1</wsman:Option><wsman:Option Type=\"xs:boolean\" Name=\"msftwinrm:UsePreciseArrays\">true</wsman:Option> \
     <wsman:Option Type=\"xs:boolean\" Name=\"msftwinrm:includepropertymetadata\">true</wsman:Option></wsman:OptionSet></env:Header> \
     <env:Body><p0:TestClass_AllDMTFTypes xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" \
     xmlns:p0=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/TestClass_AllDMTFTypes\" \
     xsi:type=\"Test\"><p0:v_Key xsi:type=\"cim:cimUnsignedLong\">100</p0:v_Key></p0:TestClass_AllDMTFTypes></env:Body></env:Envelope>" ;

    SockSendRecvHTTP(s, false, res.c_str(), r_h, r_b );
    UT_ASSERT(r_h.find("500") != string::npos);

    /* Case 2: xsi:type ="<content>_<content>" */

    res = "<env:Envelope xmlns:wsman=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" \
     xmlns:env=\"http://www.w3.org/2003/05/soap-envelope\" \
     xmlns:wsa=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" \
     xmlns:tst=\"http://schemas.microsoft.com/2005/02/wsman/test\"> \
     <env:Header><wsa:To env:mustUnderstand=\"true\">http://localhost:7778/wsman</wsa:To> \
     <wsa:ReplyTo><wsa:Address>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:Address></wsa:ReplyTo> \
     <wsa:Action env:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Create</wsa:Action> \
     <wsa:MessageID env:mustUnderstand=\"true\">uuid:cd965798-cc09-4b8f-b176-22d98390b34e</wsa:MessageID> \
     <wsman:ResourceURI env:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/TestClass_AllDMTFTypes</wsman:ResourceURI> \
     <wsman:OperationTimeout env:mustUnderstand=\"false\">PT30.0S</wsman:OperationTimeout> \
     <wsman:MaxEnvelopeSize env:mustUnderstand=\"true\">32768</wsman:MaxEnvelopeSize> \
     <wsman:Locale env:mustUnderstand=\"false\" xml:lang=\"en-US\"/> \
     <wsman:SelectorSet><wsman:Selector Name=\"__cimnamespace\">root/cimv2</wsman:Selector></wsman:SelectorSet> \
     <wsman:OptionSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><wsman:Option Type=\"xs:string\" Name=\"wmiarray:__MIInstanceModifiedPropertiesList\">v_Key</wsman:Option> \
     <wsman:Option Type=\"xs:int\" Name=\"__MI_CallbackRegistration\">11</wsman:Option><wsman:Option Type=\"xs:unsignedInt\" Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\">0</wsman:Option> \
     <wsman:Option Type=\"xs:unsignedInt\" Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\">1</wsman:Option><wsman:Option Type=\"xs:unsignedInt\" Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\">2</wsman:Option> \
     <wsman:Option Type=\"xs:unsignedInt\" Name=\"wmi:__MI_OPERATIONOPTIONS_WRITEERRORMODE\">1</wsman:Option><wsman:Option Type=\"xs:boolean\" Name=\"msftwinrm:UsePreciseArrays\">true</wsman:Option> \
     <wsman:Option Type=\"xs:boolean\" Name=\"msftwinrm:includepropertymetadata\">true</wsman:Option></wsman:OptionSet></env:Header> \
     <env:Body><p0:TestClass_AllDMTFTypes xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" \
     xmlns:p0=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/TestClass_AllDMTFTypes\" \
     xsi:type=\"Test_type\"><p0:v_Key xsi:type=\"cim:cimUnsignedLong\">100</p0:v_Key></p0:TestClass_AllDMTFTypes></env:Body></env:Envelope>" ;

    SockSendRecvHTTP(s, false, res.c_str(), r_h, r_b );
    UT_ASSERT(r_h.find("500") != string::npos);
}
NitsEndTest

/*
 * Missing namespace will default to "interop" namespace
 */
NitsTestWithSetup(TestWSMAN_Modify_SmallNumber_MissingNamespace, TestWsmanSetup)
{
    string r_b, r_h;
    const char* props = 
"<p:CIM_NonExistClass xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/CIM_NonExistClass\">"
"      <p:Description>text</p:Description>"
"  </p:CIM_NonExistClass>";
    const char* keys = "<w:Selector Name=\"Number\">7</w:Selector>";

    SockSendRecvHTTP(s, false, 
        _CreateModifyRequestXML("CIM_NonExistClass", "test/cpp", keys, props, false).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find("OMI:MI_Result:5") != string::npos);
    UT_ASSERT(r_b.find("The specified class does not exist.") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Code xsi:type=\"cim:cimUnsignedInt\">5</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Type xsi:type=\"cim:cimString\">MI</") != string::npos);
}
NitsEndTest



// general errors

// wsman faults
#if 0
#endif



// enumeration

// enumeration: deep/shallow/basic-props 

// invoke


// get


// delete

// create


// Put/Set/Modify


// Other

// test out-of-process invocation static/non-static


NitsTestWithSetup(TestWSMAN_GetClass_InvalidClassname, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false,
            "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\"><s:Header><a:To>http://157.59.85.74:7778/wsman</a:To><w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/cim-xml/2/cim-schema/2/*</w:ResourceURI><a:ReplyTo><a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo><a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Get</a:Action><w:MaxEnvelopeSize s:mustUnderstand=\"true\">1048576</w:MaxEnvelopeSize><a:MessageID>uuid:B60F3103-A48A-408E-BC11-998452D82D2F</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:SessionId s:mustUnderstand=\"false\">uuid:9802F98B-CD2D-4260-82AD-D6FCAB5E1B19</p:SessionId><p:OperationID s:mustUnderstand=\"false\">uuid:48E05E94-2337-474E-8D6C-22484C00940A</p:OperationID><p:SequenceId s:mustUnderstand=\"false\">1</p:SequenceId><w:SelectorSet><w:Selector Name=\"__cimnamespace\">test/cpp</w:Selector><w:Selector Name=\"ClassName\">InvalidClass</w:Selector></w:SelectorSet><w:OptionSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><w:Option Name=\"IncludeInheritanceHierarchy\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeInheritedElements\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeQualifiers\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"msftwinrm:UsePreciseArrays\" Type=\"xs:boolean\">true</w:Option></w:OptionSet></s:Header><s:Body></s:Body></s:Envelope>"
            , r_h, r_b, false );

    NitsTraceExA(r_b.c_str(), NitsHere(), NitsAutomatic);
    UT_ASSERT(r_h.find("500") != string::npos);

    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/08/addressing/fault</wsa:Action>") != string::npos);
    UT_ASSERT(r_b.find("wsa:DestinationUnreachable") != string::npos);
    UT_ASSERT(r_b.find("OMI:MI_Result:5") != string::npos);
    UT_ASSERT(r_b.find("The specified class does not exist.") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Code xsi:type=\"cim:cimUnsignedInt\">5</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Type xsi:type=\"cim:cimString\">MI</") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_GetClass_InvalidNamespace, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false,
            "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\"><s:Header><a:To>http://157.59.85.74:7778/wsman</a:To><w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/cim-xml/2/cim-schema/2/*</w:ResourceURI><a:ReplyTo><a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo><a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Get</a:Action><w:MaxEnvelopeSize s:mustUnderstand=\"true\">1048576</w:MaxEnvelopeSize><a:MessageID>uuid:B60F3103-A48A-408E-BC11-998452D82D2F</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:SessionId s:mustUnderstand=\"false\">uuid:9802F98B-CD2D-4260-82AD-D6FCAB5E1B19</p:SessionId><p:OperationID s:mustUnderstand=\"false\">uuid:48E05E94-2337-474E-8D6C-22484C00940A</p:OperationID><p:SequenceId s:mustUnderstand=\"false\">1</p:SequenceId><w:SelectorSet><w:Selector Name=\"__cimnamespace\">test/invalid</w:Selector><w:Selector Name=\"ClassName\">X_HugeNumber</w:Selector></w:SelectorSet><w:OptionSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><w:Option Name=\"IncludeInheritanceHierarchy\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeInheritedElements\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeQualifiers\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"msftwinrm:UsePreciseArrays\" Type=\"xs:boolean\">true</w:Option></w:OptionSet></s:Header><s:Body></s:Body></s:Envelope>"
            , r_h, r_b, false );

    NitsTraceExA(r_b.c_str(), NitsHere(), NitsAutomatic);
    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/08/addressing/fault</wsa:Action>") != string::npos);
    UT_ASSERT(r_b.find("wsa:DestinationUnreachable") != string::npos);
    UT_ASSERT(r_b.find("OMI:MI_Result:3") != string::npos);
    UT_ASSERT(r_b.find("The target namespace does not exist.") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Code xsi:type=\"cim:cimUnsignedInt\">3</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Type xsi:type=\"cim:cimString\">MI</") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_GetClass_MissingSelectorSet, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false,
            "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\"><s:Header><a:To>http://157.59.85.74:7778/wsman</a:To><w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/cim-xml/2/cim-schema/2/*</w:ResourceURI><a:ReplyTo><a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo><a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Get</a:Action><w:MaxEnvelopeSize s:mustUnderstand=\"true\">1048576</w:MaxEnvelopeSize><a:MessageID>uuid:B60F3103-A48A-408E-BC11-998452D82D2F</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:SessionId s:mustUnderstand=\"false\">uuid:9802F98B-CD2D-4260-82AD-D6FCAB5E1B19</p:SessionId><p:OperationID s:mustUnderstand=\"false\">uuid:48E05E94-2337-474E-8D6C-22484C00940A</p:OperationID><p:SequenceId s:mustUnderstand=\"false\">1</p:SequenceId><w:SelectorSet><w:Selector Name=\"__cimnamespace\">test/cpp</w:Selector></w:SelectorSet><w:OptionSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><w:Option Name=\"IncludeInheritanceHierarchy\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeInheritedElements\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeQualifiers\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"msftwinrm:UsePreciseArrays\" Type=\"xs:boolean\">true</w:Option></w:OptionSet></s:Header><s:Body></s:Body></s:Envelope>"
            , r_h, r_b, false );

    NitsTraceExA(r_b.c_str(), NitsHere(), NitsAutomatic);

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/08/addressing/fault</wsa:Action>") != string::npos);
    UT_ASSERT(r_b.find("wsa:DestinationUnreachable") != string::npos);
    UT_ASSERT(r_b.find("OMI:MI_Result:5") != string::npos);
    UT_ASSERT(r_b.find("The specified class does not exist.") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Code xsi:type=\"cim:cimUnsignedInt\">5</") != string::npos);
    UT_ASSERT(r_b.find(":OMI_Type xsi:type=\"cim:cimString\">MI</") != string::npos);
}
NitsEndTest


NitsTestWithSetup(TestWSMAN_GetClass_Unsupported_WS_CIM_URI, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false,
            "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\"><s:Header><a:To>http://157.59.85.74:7778/wsman</a:To><w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/ws-cim/1/cim-schema/2/*</w:ResourceURI><a:ReplyTo><a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo><a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Get</a:Action><w:MaxEnvelopeSize s:mustUnderstand=\"true\">1048576</w:MaxEnvelopeSize><a:MessageID>uuid:B60F3103-A48A-408E-BC11-998452D82D2F</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:SessionId s:mustUnderstand=\"false\">uuid:9802F98B-CD2D-4260-82AD-D6FCAB5E1B19</p:SessionId><p:OperationID s:mustUnderstand=\"false\">uuid:48E05E94-2337-474E-8D6C-22484C00940A</p:OperationID><p:SequenceId s:mustUnderstand=\"false\">1</p:SequenceId><w:SelectorSet><w:Selector Name=\"__cimnamespace\">test/cpp</w:Selector><w:Selector Name=\"ClassName\">X_HugeNumber</w:Selector></w:SelectorSet><w:OptionSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><w:Option Name=\"IncludeInheritanceHierarchy\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeInheritedElements\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeQualifiers\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"msftwinrm:UsePreciseArrays\" Type=\"xs:boolean\">true</w:Option></w:OptionSet></s:Header><s:Body></s:Body></s:Envelope>"
            , r_h, r_b, false );

    NitsTraceExA(r_b.c_str(), NitsHere(), NitsAutomatic);

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.dmtf.org/wbem/wsman/1/wsman/fault</wsa:Action>") != string::npos);
    UT_ASSERT(r_b.find("wsman:UnsupportedFeature") != string::npos);
    UT_ASSERT(r_b.find("GetClass not Supported in WS-CIM format") != string::npos);
}
NitsEndTest


NitsTestWithSetup(TestWSMAN_GetClass_X_HugeNumber_StandardRttiNonWinRMClient, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false,
            "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\"><s:Header><a:To>http://157.59.85.74:7778/wsman</a:To><w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/cim-xml/2/cim-schema/2/*</w:ResourceURI><a:ReplyTo><a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo><a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Get</a:Action><w:MaxEnvelopeSize s:mustUnderstand=\"true\">1048576</w:MaxEnvelopeSize><a:MessageID>uuid:B60F3103-A48A-408E-BC11-998452D82D2F</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:SessionId s:mustUnderstand=\"false\">uuid:9802F98B-CD2D-4260-82AD-D6FCAB5E1B19</p:SessionId><p:OperationID s:mustUnderstand=\"false\">uuid:48E05E94-2337-474E-8D6C-22484C00940A</p:OperationID><p:SequenceId s:mustUnderstand=\"false\">1</p:SequenceId><w:SelectorSet><w:Selector Name=\"__cimnamespace\">test/cpp</w:Selector><w:Selector Name=\"ClassName\">X_HugeNumber</w:Selector></w:SelectorSet><w:OptionSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><w:Option Name=\"IncludeInheritanceHierarchy\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeInheritedElements\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeQualifiers\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"msftwinrm:UsePreciseArrays\" Type=\"xs:boolean\">true</w:Option></w:OptionSet></s:Header><s:Body></s:Body></s:Envelope>"
            , r_h, r_b, false );

    NitsTraceExA(r_b.c_str(), NitsHere(), NitsAutomatic);
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(r_b.find("CLASSORIGIN") == string::npos);
    UT_ASSERT(r_b.find("DERIVATION") != string::npos);
    UT_ASSERT(r_b.find("PROPAGATED") != string::npos);
    UT_ASSERT(r_b.find("QUALIFIER") != string::npos);
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse</wsa:Action>") != string::npos);
    UT_ASSERT(r_b.find("<CLASS NAME=\"X_HugeNumber\" SUPERCLASS=\"X_Number\" DERIVATION=\"X_Number,X_ManagedElement\"><PROPERTY NAME=\"Description\" TYPE=\"string\" PROPAGATED=\"true\"></PROPERTY><PROPERTY NAME=\"Number\" TYPE=\"uint64\" PROPAGATED=\"true\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY NAME=\"Magnitude\" TYPE=\"uint32\"></PROPERTY><PROPERTY NAME=\"MagnitudeObj\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_SmallNumber</VALUE></QUALIFIER></PROPERTY><PROPERTY.ARRAY NAME=\"Numbers123\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_SmallNumber</VALUE></QUALIFIER></PROPERTY.ARRAY><PROPERTY NAME=\"Number0\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY.ARRAY NAME=\"TwoTestObjects\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.ARRAY><PROPERTY NAME=\"TestObject\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_TestObject</VALUE></QUALIFIER></PROPERTY><METHOD NAME=\"SpellMagnitude\" TYPE=\"string\"></METHOD><METHOD NAME=\"TestEmbedded\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_TestObject</VALUE></QUALIFIER><QUALIFIER NAME=\"static\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><PARAMETER.ARRAY NAME=\"objectsArray\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"out\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY><PARAMETER NAME=\"objectSingle\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"out\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER><PARAMETER.ARRAY NAME=\"testObjectsArray\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_TestObject</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"out\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY><PARAMETER NAME=\"testObjectSingle\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_TestObject</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"out\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>") != string::npos);
}
NitsEndTest

#if !defined(hpux)
static char desiredStandardRttiErrorString[] =
    "<CLASS NAME=\"CIM_Error\" DERIVATION=\"\"><QUALIFIER NAME=\"Version\" TYPE=\"string\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\"><VALUE>177</VALUE>"
    "</QUALIFIER><QUALIFIER NAME=\"UMLPackagePath\" TYPE=\"string\"><VALUE>CIM::Interop</VALUE></QUALIFIER>"
    "<QUALIFIER NAME=\"indication\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER>"
    "<PROPERTY NAME=\"ErrorType\" TYPE=\"uint16\" CLASSORIGIN=\"CIM_Error\"><QUALIFIER NAME=\"ValueMap\" TYPE=\"string\"><VALUE.ARRAY><VALUE>0</VALUE>"
    "<VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE><VALUE>4</VALUE><VALUE>5</VALUE><VALUE>6</VALUE><VALUE>7</VALUE><VALUE>8</VALUE><VALUE>9</VALUE>"
    "<VALUE>10</VALUE><VALUE>..</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"Values\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>1</VALUE>"
    "<VALUE>2</VALUE><VALUE>3</VALUE><VALUE>4</VALUE><VALUE>5</VALUE><VALUE>6</VALUE><VALUE>7</VALUE><VALUE>8</VALUE><VALUE>9</VALUE><VALUE>10</VALUE>"
    "<VALUE>11</VALUE><VALUE>12</VALUE></VALUE.ARRAY></QUALIFIER>"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\"><VALUE.ARRAY><VALUE>CIM_Error.OtherErrorType</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>"
    "<PROPERTY NAME=\"OtherErrorType\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\"><VALUE.ARRAY><VALUE>CIM_Error.ErrorType</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>"
    "<PROPERTY NAME=\"OwningEntity\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\"></PROPERTY>"
    "<PROPERTY NAME=\"MessageID\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\"><QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\">"
    "<VALUE.ARRAY><VALUE>CIM_Error.Message</VALUE><VALUE>CIM_Error.MessageArguments</VALUE></VALUE.ARRAY></QUALIFIER>"
    "<QUALIFIER NAME=\"required\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY>"
    "<PROPERTY NAME=\"Message\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\">"
    "<VALUE.ARRAY><VALUE>CIM_Error.MessageID</VALUE><VALUE>CIM_Error.MessageArguments</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>"
    "<PROPERTY.ARRAY NAME=\"MessageArguments\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\"><QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\">"
    "<VALUE.ARRAY><VALUE>CIM_Error.MessageID</VALUE><VALUE>CIM_Error.Message</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY.ARRAY>"
    "<PROPERTY NAME=\"PerceivedSeverity\" TYPE=\"uint16\" CLASSORIGIN=\"CIM_Error\"><QUALIFIER NAME=\"ValueMap\" TYPE=\"string\">"
    "<VALUE.ARRAY><VALUE>0</VALUE><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE><VALUE>4</VALUE><VALUE>5</VALUE><VALUE>6</VALUE>"
    "<VALUE>7</VALUE><VALUE>..</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"Values\" TYPE=\"string\" TRANSLATABLE=\"true\">"
    "<VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>13</VALUE><VALUE>14</VALUE><VALUE>15</VALUE><VALUE>16</VALUE>"
    "<VALUE>17</VALUE><VALUE>18</VALUE><VALUE>12</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>"
    "<PROPERTY NAME=\"ProbableCause\" TYPE=\"uint16\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ValueMap\" TYPE=\"string\"><VALUE.ARRAY><VALUE>0</VALUE>"
    "<VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE><VALUE>4</VALUE><VALUE>5</VALUE><VALUE>6</VALUE><VALUE>7</VALUE><VALUE>8</VALUE>"
    "<VALUE>9</VALUE><VALUE>10</VALUE><VALUE>11</VALUE><VALUE>12</VALUE><VALUE>13</VALUE><VALUE>14</VALUE><VALUE>15</VALUE><VALUE>16</VALUE>"
    "<VALUE>17</VALUE><VALUE>18</VALUE><VALUE>19</VALUE><VALUE>20</VALUE><VALUE>21</VALUE><VALUE>22</VALUE><VALUE>23</VALUE><VALUE>24</VALUE>"
    "<VALUE>25</VALUE><VALUE>26</VALUE><VALUE>27</VALUE><VALUE>28</VALUE><VALUE>29</VALUE><VALUE>30</VALUE><VALUE>31</VALUE><VALUE>32</VALUE>"
    "<VALUE>33</VALUE><VALUE>34</VALUE><VALUE>35</VALUE><VALUE>36</VALUE><VALUE>37</VALUE><VALUE>38</VALUE><VALUE>39</VALUE><VALUE>40</VALUE>"
    "<VALUE>41</VALUE><VALUE>42</VALUE><VALUE>43</VALUE><VALUE>44</VALUE><VALUE>45</VALUE><VALUE>46</VALUE><VALUE>47</VALUE><VALUE>48</VALUE>"
    "<VALUE>49</VALUE><VALUE>50</VALUE><VALUE>51</VALUE><VALUE>52</VALUE><VALUE>53</VALUE><VALUE>54</VALUE><VALUE>55</VALUE><VALUE>56</VALUE>"
    "<VALUE>57</VALUE><VALUE>58</VALUE><VALUE>59</VALUE><VALUE>60</VALUE><VALUE>61</VALUE><VALUE>62</VALUE><VALUE>63</VALUE><VALUE>64</VALUE>"
    "<VALUE>65</VALUE><VALUE>66</VALUE><VALUE>67</VALUE><VALUE>68</VALUE><VALUE>69</VALUE><VALUE>70</VALUE><VALUE>71</VALUE><VALUE>72</VALUE>"
    "<VALUE>73</VALUE><VALUE>74</VALUE><VALUE>75</VALUE><VALUE>76</VALUE><VALUE>77</VALUE><VALUE>78</VALUE><VALUE>79</VALUE><VALUE>80</VALUE>"
    "<VALUE>81</VALUE><VALUE>82</VALUE><VALUE>83</VALUE><VALUE>84</VALUE><VALUE>85</VALUE><VALUE>86</VALUE><VALUE>87</VALUE><VALUE>88</VALUE>"
    "<VALUE>89</VALUE><VALUE>90</VALUE><VALUE>91</VALUE><VALUE>92</VALUE><VALUE>93</VALUE><VALUE>94</VALUE><VALUE>95</VALUE><VALUE>96</VALUE>"
    "<VALUE>97</VALUE><VALUE>98</VALUE><VALUE>99</VALUE><VALUE>100</VALUE><VALUE>101</VALUE><VALUE>102</VALUE><VALUE>103</VALUE><VALUE>104</VALUE>"
    "<VALUE>105</VALUE><VALUE>106</VALUE><VALUE>107</VALUE><VALUE>108</VALUE><VALUE>109</VALUE><VALUE>110</VALUE><VALUE>111</VALUE><VALUE>112</VALUE>"
    "<VALUE>113</VALUE><VALUE>114</VALUE><VALUE>115</VALUE><VALUE>116</VALUE><VALUE>117</VALUE><VALUE>118</VALUE><VALUE>119</VALUE><VALUE>120</VALUE>"
    "<VALUE>121</VALUE><VALUE>122</VALUE><VALUE>123</VALUE><VALUE>124</VALUE><VALUE>125</VALUE><VALUE>126</VALUE><VALUE>127</VALUE><VALUE>128</VALUE>"
    "<VALUE>129</VALUE><VALUE>130</VALUE><VALUE>..</VALUE></VALUE.ARRAY></QUALIFIER>"
    "<QUALIFIER NAME=\"Values\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE>"
    "<VALUE>19</VALUE><VALUE>20</VALUE><VALUE>21</VALUE><VALUE>22</VALUE><VALUE>23</VALUE><VALUE>24</VALUE><VALUE>25</VALUE><VALUE>26</VALUE>"
    "<VALUE>27</VALUE><VALUE>28</VALUE><VALUE>29</VALUE><VALUE>30</VALUE><VALUE>31</VALUE><VALUE>32</VALUE><VALUE>33</VALUE><VALUE>34</VALUE>"
    "<VALUE>35</VALUE><VALUE>36</VALUE><VALUE>37</VALUE><VALUE>38</VALUE><VALUE>39</VALUE><VALUE>40</VALUE><VALUE>41</VALUE><VALUE>42</VALUE>"
    "<VALUE>43</VALUE><VALUE>44</VALUE><VALUE>45</VALUE><VALUE>46</VALUE><VALUE>47</VALUE><VALUE>48</VALUE><VALUE>49</VALUE><VALUE>50</VALUE>"
    "<VALUE>51</VALUE><VALUE>52</VALUE><VALUE>53</VALUE><VALUE>54</VALUE><VALUE>55</VALUE><VALUE>56</VALUE><VALUE>57</VALUE><VALUE>58</VALUE>"
    "<VALUE>59</VALUE><VALUE>60</VALUE><VALUE>61</VALUE><VALUE>62</VALUE><VALUE>63</VALUE><VALUE>5</VALUE><VALUE>64</VALUE><VALUE>65</VALUE>"
    "<VALUE>66</VALUE><VALUE>67</VALUE><VALUE>68</VALUE><VALUE>69</VALUE><VALUE>70</VALUE><VALUE>71</VALUE><VALUE>72</VALUE><VALUE>73</VALUE>"
    "<VALUE>74</VALUE><VALUE>75</VALUE><VALUE>76</VALUE><VALUE>77</VALUE><VALUE>78</VALUE><VALUE>79</VALUE><VALUE>80</VALUE><VALUE>81</VALUE>"
    "<VALUE>82</VALUE><VALUE>83</VALUE><VALUE>84</VALUE><VALUE>85</VALUE><VALUE>86</VALUE><VALUE>87</VALUE><VALUE>88</VALUE><VALUE>89</VALUE>"
    "<VALUE>90</VALUE><VALUE>91</VALUE><VALUE>92</VALUE><VALUE>93</VALUE><VALUE>94</VALUE><VALUE>95</VALUE><VALUE>96</VALUE><VALUE>97</VALUE>"
    "<VALUE>98</VALUE><VALUE>99</VALUE><VALUE>100</VALUE><VALUE>101</VALUE><VALUE>102</VALUE><VALUE>103</VALUE><VALUE>104</VALUE>"
    "<VALUE>105</VALUE><VALUE>106</VALUE><VALUE>107</VALUE><VALUE>108</VALUE><VALUE>109</VALUE><VALUE>110</VALUE><VALUE>111</VALUE>"
    "<VALUE>112</VALUE><VALUE>113</VALUE><VALUE>114</VALUE><VALUE>115</VALUE><VALUE>116</VALUE><VALUE>117</VALUE><VALUE>118</VALUE>"
    "<VALUE>119</VALUE><VALUE>120</VALUE><VALUE>121</VALUE><VALUE>122</VALUE><VALUE>123</VALUE><VALUE>124</VALUE><VALUE>125</VALUE>"
    "<VALUE>126</VALUE><VALUE>127</VALUE><VALUE>128</VALUE><VALUE>129</VALUE><VALUE>130</VALUE><VALUE>131</VALUE><VALUE>132</VALUE>"
    "<VALUE>133</VALUE><VALUE>134</VALUE><VALUE>135</VALUE><VALUE>136</VALUE><VALUE>137</VALUE><VALUE>138</VALUE><VALUE>139</VALUE>"
    "<VALUE>140</VALUE><VALUE>141</VALUE><VALUE>142</VALUE><VALUE>143</VALUE><VALUE>144</VALUE><VALUE>145</VALUE><VALUE>146</VALUE>"
    "<VALUE>12</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\">"
    "<VALUE.ARRAY><VALUE>CIM_Error.ProbableCauseDescription</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>"
    "<PROPERTY NAME=\"ProbableCauseDescription\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\"><VALUE.ARRAY><VALUE>CIM_Error.ProbableCause</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>"
    "<PROPERTY.ARRAY NAME=\"RecommendedActions\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\"></PROPERTY.ARRAY>"
    "<PROPERTY NAME=\"ErrorSource\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\"><QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\">"
    "<VALUE.ARRAY><VALUE>CIM_Error.ErrorSourceFormat</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>"
    "<PROPERTY NAME=\"ErrorSourceFormat\" TYPE=\"uint16\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ValueMap\" TYPE=\"string\"><VALUE.ARRAY><VALUE>0</VALUE><VALUE>1</VALUE><VALUE>2</VALUE>"
    "<VALUE>..</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"Values\" TYPE=\"string\" TRANSLATABLE=\"true\">"
    "<VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>147</VALUE><VALUE>12</VALUE></VALUE.ARRAY></QUALIFIER>"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\"><VALUE.ARRAY><VALUE>CIM_Error.ErrorSource</VALUE>"
    "<VALUE>CIM_Error.OtherErrorSourceFormat</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>0</VALUE></PROPERTY>"
    "<PROPERTY NAME=\"OtherErrorSourceFormat\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\"><VALUE.ARRAY>"
    "<VALUE>CIM_Error.ErrorSourceFormat</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>"
    "<PROPERTY NAME=\"CIMStatusCode\" TYPE=\"uint32\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ValueMap\" TYPE=\"string\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE><VALUE>4</VALUE>"
    "<VALUE>5</VALUE><VALUE>6</VALUE><VALUE>7</VALUE><VALUE>8</VALUE><VALUE>9</VALUE><VALUE>10</VALUE><VALUE>11</VALUE>"
    "<VALUE>12</VALUE><VALUE>13</VALUE><VALUE>14</VALUE><VALUE>15</VALUE><VALUE>16</VALUE><VALUE>17</VALUE><VALUE>18</VALUE>"
    "<VALUE>19</VALUE><VALUE>20</VALUE><VALUE>21</VALUE><VALUE>22</VALUE><VALUE>23</VALUE><VALUE>24</VALUE><VALUE>25</VALUE>"
    "<VALUE>26</VALUE><VALUE>27</VALUE><VALUE>28</VALUE><VALUE>29</VALUE><VALUE>..</VALUE></VALUE.ARRAY></QUALIFIER>"
    "<QUALIFIER NAME=\"Values\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>148</VALUE><VALUE>149</VALUE>"
    "<VALUE>150</VALUE><VALUE>151</VALUE><VALUE>152</VALUE><VALUE>153</VALUE><VALUE>154</VALUE><VALUE>155</VALUE>"
    "<VALUE>156</VALUE><VALUE>157</VALUE><VALUE>158</VALUE><VALUE>159</VALUE><VALUE>160</VALUE><VALUE>161</VALUE>"
    "<VALUE>162</VALUE><VALUE>163</VALUE><VALUE>164</VALUE><VALUE>165</VALUE><VALUE>166</VALUE><VALUE>167</VALUE>"
    "<VALUE>168</VALUE><VALUE>169</VALUE><VALUE>170</VALUE><VALUE>171</VALUE><VALUE>172</VALUE><VALUE>173</VALUE>"
    "<VALUE>174</VALUE><VALUE>175</VALUE><VALUE>176</VALUE><VALUE>12</VALUE></VALUE.ARRAY></QUALIFIER>"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\"><VALUE.ARRAY><VALUE>CIM_Error.CIMStatusCodeDescription</VALUE>"
    "</VALUE.ARRAY></QUALIFIER></PROPERTY><PROPERTY NAME=\"CIMStatusCodeDescription\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\"><VALUE.ARRAY><VALUE>CIM_Error.CIMStatusCode</VALUE>"
    "</VALUE.ARRAY></QUALIFIER></PROPERTY></CLASS>";

NitsTestWithSetup(TestWSMAN_GetClass_CIM_Error_StandardRtti, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false,
            "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\"><s:Header><a:To>http://157.59.86.37:7778/wsman</a:To><w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/cim-xml/2/cim-schema/2/*</w:ResourceURI><a:ReplyTo><a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo><a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Get</a:Action><w:MaxEnvelopeSize s:mustUnderstand=\"true\">1048576</w:MaxEnvelopeSize><a:MessageID>uuid:DFCFFC30-89CA-4C3F-8E8C-4DA843C58615</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:SessionId s:mustUnderstand=\"false\">uuid:3091788F-6729-47C1-8A9C-CF6F387170E7</p:SessionId><p:OperationID s:mustUnderstand=\"false\">uuid:45B3AA8E-7853-4E1C-8437-FE5546D0D08E</p:OperationID><p:SequenceId s:mustUnderstand=\"false\">1</p:SequenceId><w:SelectorSet><w:Selector Name=\"__cimnamespace\">root/test</w:Selector><w:Selector Name=\"ClassName\">CIM_Error</w:Selector></w:SelectorSet><w:OptionSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><w:Option Name=\"IncludeInheritanceHierarchy\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeInheritedElements\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeQualifiers\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"__MI_CallbackRegistration\" Type=\"xs:int\">11</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">0</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">1</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">2</w:Option><w:Option Name=\"wmi:__MI_OPERATIONOPTIONS_WRITEERRORMODE\" Type=\"xs:unsignedInt\">1</w:Option><w:Option Name=\"msftwinrm:UsePreciseArrays\" Type=\"xs:boolean\">true</w:Option></w:OptionSet></s:Header><s:Body></s:Body></s:Envelope>"
            , r_h, r_b, true );

    NitsTraceExA(r_b.c_str(), NitsHere(), NitsAutomatic);
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(r_b.find("CLASSORIGIN") != string::npos);
    UT_ASSERT(r_b.find("DERIVATION") != string::npos);
    UT_ASSERT(r_b.find("QUALIFIER") != string::npos);
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse</wsa:Action>") != string::npos);
    UT_ASSERT(r_b.find(desiredStandardRttiErrorString) != string::npos);
}
NitsEndTest
#endif

NitsTestWithSetup(TestWSMAN_GetClass_MSFT_Animal_StandardRtti, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false,
            "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\"><s:Header><a:To>http://157.59.86.37:7778/wsman</a:To><w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/cim-xml/2/cim-schema/2/*</w:ResourceURI><a:ReplyTo><a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo><a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Get</a:Action><w:MaxEnvelopeSize s:mustUnderstand=\"true\">1048576</w:MaxEnvelopeSize><a:MessageID>uuid:D3F422F5-574D-40CD-A610-FFF8FBDF5F83</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:SessionId s:mustUnderstand=\"false\">uuid:3091788F-6729-47C1-8A9C-CF6F387170E7</p:SessionId><p:OperationID s:mustUnderstand=\"false\">uuid:18D51124-A440-45B1-B4B1-CC085A5F9A32</p:OperationID><p:SequenceId s:mustUnderstand=\"false\">1</p:SequenceId><w:SelectorSet><w:Selector Name=\"__cimnamespace\">root/test</w:Selector><w:Selector Name=\"ClassName\">MSFT_Animal</w:Selector></w:SelectorSet><w:OptionSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><w:Option Name=\"IncludeInheritanceHierarchy\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeInheritedElements\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeQualifiers\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"__MI_CallbackRegistration\" Type=\"xs:int\">11</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">0</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">1</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">2</w:Option><w:Option Name=\"wmi:__MI_OPERATIONOPTIONS_WRITEERRORMODE\" Type=\"xs:unsignedInt\">1</w:Option><w:Option Name=\"msftwinrm:UsePreciseArrays\" Type=\"xs:boolean\">true</w:Option></w:OptionSet></s:Header><s:Body></s:Body></s:Envelope>"
            , r_h, r_b, true );

    NitsTraceExA(r_b.c_str(), NitsHere(), NitsAutomatic);
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(r_b.find("CLASSORIGIN") != string::npos);
    UT_ASSERT(r_b.find("DERIVATION") != string::npos);
    UT_ASSERT(r_b.find("PROPAGATED") != string::npos);
    UT_ASSERT(r_b.find("QUALIFIER") != string::npos);
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse</wsa:Action>") != string::npos);

    UT_ASSERT(r_b.find("<CLASS NAME=\"MSFT_Animal\" SUPERCLASS=\"MSFT_Base\" DERIVATION=\"MSFT_Base\"><PROPERTY NAME=\"Key\" TYPE=\"uint32\" CLASSORIGIN=\"MSFT_Base\" PROPAGATED=\"true\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY NAME=\"Species\" TYPE=\"string\" CLASSORIGIN=\"MSFT_Animal\"></PROPERTY></CLASS>") != string::npos);
}
NitsEndTest

#if !defined(hpux)
static char desiredStandardRttiOOPErrorString[] =
    "<CLASS NAME=\"CIM_Error\" DERIVATION=\"\"><QUALIFIER NAME=\"Version\" TYPE=\"string\" TOSUBCLASS=\"false\" TRANSLATABLE=\"true\">"
    "<VALUE>177</VALUE></QUALIFIER><QUALIFIER NAME=\"UMLPackagePath\" TYPE=\"string\"><VALUE>CIM::Interop</VALUE></QUALIFIER>"
    "<QUALIFIER NAME=\"indication\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><PROPERTY NAME=\"ErrorType\" TYPE=\"uint16\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ValueMap\" TYPE=\"string\"><VALUE.ARRAY><VALUE>0</VALUE><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE>"
    "<VALUE>4</VALUE><VALUE>5</VALUE><VALUE>6</VALUE><VALUE>7</VALUE><VALUE>8</VALUE><VALUE>9</VALUE><VALUE>10</VALUE>"
    "<VALUE>..</VALUE></VALUE.ARRAY></QUALIFIER><QUALIFIER NAME=\"Values\" TYPE=\"string\" TRANSLATABLE=\"true\">"
    "<VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE><VALUE>4</VALUE><VALUE>5</VALUE><VALUE>6</VALUE><VALUE>7</VALUE><VALUE>8</VALUE>"
    "<VALUE>9</VALUE><VALUE>10</VALUE><VALUE>11</VALUE><VALUE>12</VALUE></VALUE.ARRAY></QUALIFIER>"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\">"
    "<VALUE.ARRAY><VALUE>CIM_Error.OtherErrorType</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>"
    "<PROPERTY NAME=\"OtherErrorType\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\"><VALUE.ARRAY><VALUE>CIM_Error.ErrorType</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>"
    "<PROPERTY NAME=\"OwningEntity\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\"></PROPERTY>"
    "<PROPERTY NAME=\"MessageID\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\">"
    "<VALUE.ARRAY><VALUE>CIM_Error.Message</VALUE><VALUE>CIM_Error.MessageArguments</VALUE></VALUE.ARRAY></QUALIFIER>"
    "<QUALIFIER NAME=\"required\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY>"
    "<PROPERTY NAME=\"Message\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\"><QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\">"
    "<VALUE.ARRAY><VALUE>CIM_Error.MessageID</VALUE><VALUE>CIM_Error.MessageArguments</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>"
    "<PROPERTY.ARRAY NAME=\"MessageArguments\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\"><VALUE.ARRAY><VALUE>CIM_Error.MessageID</VALUE>"
    "<VALUE>CIM_Error.Message</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY.ARRAY>"
    "<PROPERTY NAME=\"PerceivedSeverity\" TYPE=\"uint16\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ValueMap\" TYPE=\"string\"><VALUE.ARRAY><VALUE>0</VALUE>"
    "<VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE><VALUE>4</VALUE><VALUE>5</VALUE><VALUE>6</VALUE>"
    "<VALUE>7</VALUE><VALUE>..</VALUE></VALUE.ARRAY></QUALIFIER>"
    "<QUALIFIER NAME=\"Values\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE>"
    "<VALUE>13</VALUE><VALUE>14</VALUE><VALUE>15</VALUE><VALUE>16</VALUE><VALUE>17</VALUE><VALUE>18</VALUE><VALUE>12</VALUE>"
    "</VALUE.ARRAY></QUALIFIER></PROPERTY><PROPERTY NAME=\"ProbableCause\" TYPE=\"uint16\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ValueMap\" TYPE=\"string\">"
    "<VALUE.ARRAY><VALUE>0</VALUE><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>3</VALUE><VALUE>4</VALUE>"
    "<VALUE>5</VALUE><VALUE>6</VALUE><VALUE>7</VALUE><VALUE>8</VALUE><VALUE>9</VALUE><VALUE>10</VALUE><VALUE>11</VALUE>"
    "<VALUE>12</VALUE><VALUE>13</VALUE><VALUE>14</VALUE><VALUE>15</VALUE><VALUE>16</VALUE><VALUE>17</VALUE><VALUE>18</VALUE>"
    "<VALUE>19</VALUE><VALUE>20</VALUE><VALUE>21</VALUE><VALUE>22</VALUE><VALUE>23</VALUE><VALUE>24</VALUE><VALUE>25</VALUE>"
    "<VALUE>26</VALUE><VALUE>27</VALUE><VALUE>28</VALUE><VALUE>29</VALUE><VALUE>30</VALUE><VALUE>31</VALUE><VALUE>32</VALUE>"
    "<VALUE>33</VALUE><VALUE>34</VALUE><VALUE>35</VALUE><VALUE>36</VALUE><VALUE>37</VALUE><VALUE>38</VALUE><VALUE>39</VALUE>"
    "<VALUE>40</VALUE><VALUE>41</VALUE><VALUE>42</VALUE><VALUE>43</VALUE><VALUE>44</VALUE><VALUE>45</VALUE><VALUE>46</VALUE>"
    "<VALUE>47</VALUE><VALUE>48</VALUE><VALUE>49</VALUE><VALUE>50</VALUE><VALUE>51</VALUE><VALUE>52</VALUE><VALUE>53</VALUE>"
    "<VALUE>54</VALUE><VALUE>55</VALUE><VALUE>56</VALUE><VALUE>57</VALUE><VALUE>58</VALUE><VALUE>59</VALUE><VALUE>60</VALUE>"
    "<VALUE>61</VALUE><VALUE>62</VALUE><VALUE>63</VALUE><VALUE>64</VALUE><VALUE>65</VALUE><VALUE>66</VALUE><VALUE>67</VALUE>"
    "<VALUE>68</VALUE><VALUE>69</VALUE><VALUE>70</VALUE><VALUE>71</VALUE><VALUE>72</VALUE><VALUE>73</VALUE><VALUE>74</VALUE>"
    "<VALUE>75</VALUE><VALUE>76</VALUE><VALUE>77</VALUE><VALUE>78</VALUE><VALUE>79</VALUE><VALUE>80</VALUE><VALUE>81</VALUE>"
    "<VALUE>82</VALUE><VALUE>83</VALUE><VALUE>84</VALUE><VALUE>85</VALUE><VALUE>86</VALUE><VALUE>87</VALUE><VALUE>88</VALUE>"
    "<VALUE>89</VALUE><VALUE>90</VALUE><VALUE>91</VALUE><VALUE>92</VALUE><VALUE>93</VALUE><VALUE>94</VALUE><VALUE>95</VALUE>"
    "<VALUE>96</VALUE><VALUE>97</VALUE><VALUE>98</VALUE><VALUE>99</VALUE><VALUE>100</VALUE><VALUE>101</VALUE><VALUE>102</VALUE>"
    "<VALUE>103</VALUE><VALUE>104</VALUE><VALUE>105</VALUE><VALUE>106</VALUE><VALUE>107</VALUE><VALUE>108</VALUE>"
    "<VALUE>109</VALUE><VALUE>110</VALUE><VALUE>111</VALUE><VALUE>112</VALUE><VALUE>113</VALUE><VALUE>114</VALUE>"
    "<VALUE>115</VALUE><VALUE>116</VALUE><VALUE>117</VALUE><VALUE>118</VALUE><VALUE>119</VALUE><VALUE>120</VALUE>"
    "<VALUE>121</VALUE><VALUE>122</VALUE><VALUE>123</VALUE><VALUE>124</VALUE><VALUE>125</VALUE><VALUE>126</VALUE>"
    "<VALUE>127</VALUE><VALUE>128</VALUE><VALUE>129</VALUE><VALUE>130</VALUE><VALUE>..</VALUE></VALUE.ARRAY></QUALIFIER>"
    "<QUALIFIER NAME=\"Values\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE>"
    "<VALUE>19</VALUE><VALUE>20</VALUE><VALUE>21</VALUE><VALUE>22</VALUE><VALUE>23</VALUE><VALUE>24</VALUE><VALUE>25</VALUE>"
    "<VALUE>26</VALUE><VALUE>27</VALUE><VALUE>28</VALUE><VALUE>29</VALUE><VALUE>30</VALUE><VALUE>31</VALUE><VALUE>32</VALUE>"
    "<VALUE>33</VALUE><VALUE>34</VALUE><VALUE>35</VALUE><VALUE>36</VALUE><VALUE>37</VALUE><VALUE>38</VALUE><VALUE>39</VALUE>"
    "<VALUE>40</VALUE><VALUE>41</VALUE><VALUE>42</VALUE><VALUE>43</VALUE><VALUE>44</VALUE><VALUE>45</VALUE><VALUE>46</VALUE>"
    "<VALUE>47</VALUE><VALUE>48</VALUE><VALUE>49</VALUE><VALUE>50</VALUE><VALUE>51</VALUE><VALUE>52</VALUE><VALUE>53</VALUE>"
    "<VALUE>54</VALUE><VALUE>55</VALUE><VALUE>56</VALUE><VALUE>57</VALUE><VALUE>58</VALUE><VALUE>59</VALUE><VALUE>60</VALUE>"
    "<VALUE>61</VALUE><VALUE>62</VALUE><VALUE>63</VALUE><VALUE>5</VALUE><VALUE>64</VALUE><VALUE>65</VALUE><VALUE>66</VALUE>"
    "<VALUE>67</VALUE><VALUE>68</VALUE><VALUE>69</VALUE><VALUE>70</VALUE><VALUE>71</VALUE><VALUE>72</VALUE><VALUE>73</VALUE>"
    "<VALUE>74</VALUE><VALUE>75</VALUE><VALUE>76</VALUE><VALUE>77</VALUE><VALUE>78</VALUE><VALUE>79</VALUE><VALUE>80</VALUE>"
    "<VALUE>81</VALUE><VALUE>82</VALUE><VALUE>83</VALUE><VALUE>84</VALUE><VALUE>85</VALUE><VALUE>86</VALUE><VALUE>87</VALUE>"
    "<VALUE>88</VALUE><VALUE>89</VALUE><VALUE>90</VALUE><VALUE>91</VALUE><VALUE>92</VALUE><VALUE>93</VALUE><VALUE>94</VALUE>"
    "<VALUE>95</VALUE><VALUE>96</VALUE><VALUE>97</VALUE><VALUE>98</VALUE><VALUE>99</VALUE><VALUE>100</VALUE><VALUE>101</VALUE>"
    "<VALUE>102</VALUE><VALUE>103</VALUE><VALUE>104</VALUE><VALUE>105</VALUE><VALUE>106</VALUE><VALUE>107</VALUE>"
    "<VALUE>108</VALUE><VALUE>109</VALUE><VALUE>110</VALUE><VALUE>111</VALUE><VALUE>112</VALUE><VALUE>113</VALUE>"
    "<VALUE>114</VALUE><VALUE>115</VALUE><VALUE>116</VALUE><VALUE>117</VALUE><VALUE>118</VALUE><VALUE>119</VALUE>"
    "<VALUE>120</VALUE><VALUE>121</VALUE><VALUE>122</VALUE><VALUE>123</VALUE><VALUE>124</VALUE><VALUE>125</VALUE>"
    "<VALUE>126</VALUE><VALUE>127</VALUE><VALUE>128</VALUE><VALUE>129</VALUE><VALUE>130</VALUE><VALUE>131</VALUE>"
    "<VALUE>132</VALUE><VALUE>133</VALUE><VALUE>134</VALUE><VALUE>135</VALUE><VALUE>136</VALUE><VALUE>137</VALUE>"
    "<VALUE>138</VALUE><VALUE>139</VALUE><VALUE>140</VALUE><VALUE>141</VALUE><VALUE>142</VALUE><VALUE>143</VALUE>"
    "<VALUE>144</VALUE><VALUE>145</VALUE><VALUE>146</VALUE><VALUE>12</VALUE></VALUE.ARRAY></QUALIFIER>"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\">"
    "<VALUE.ARRAY><VALUE>CIM_Error.ProbableCauseDescription</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>"
    "<PROPERTY NAME=\"ProbableCauseDescription\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\">"
    "<VALUE.ARRAY><VALUE>CIM_Error.ProbableCause</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>"
    "<PROPERTY.ARRAY NAME=\"RecommendedActions\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\"></PROPERTY.ARRAY>"
    "<PROPERTY NAME=\"ErrorSource\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\">"
    "<VALUE.ARRAY><VALUE>CIM_Error.ErrorSourceFormat</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>"
    "<PROPERTY NAME=\"ErrorSourceFormat\" TYPE=\"uint16\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ValueMap\" TYPE=\"string\"><VALUE.ARRAY><VALUE>0</VALUE>"
    "<VALUE>1</VALUE><VALUE>2</VALUE><VALUE>..</VALUE></VALUE.ARRAY></QUALIFIER>"
    "<QUALIFIER NAME=\"Values\" TYPE=\"string\" TRANSLATABLE=\"true\">"
    "<VALUE.ARRAY><VALUE>1</VALUE><VALUE>2</VALUE><VALUE>147</VALUE><VALUE>12</VALUE></VALUE.ARRAY></QUALIFIER>"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\"><VALUE.ARRAY><VALUE>CIM_Error.ErrorSource</VALUE>"
    "<VALUE>CIM_Error.OtherErrorSourceFormat</VALUE></VALUE.ARRAY></QUALIFIER><VALUE>0</VALUE></PROPERTY>"
    "<PROPERTY NAME=\"OtherErrorSourceFormat\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\">"
    "<VALUE.ARRAY><VALUE>CIM_Error.ErrorSourceFormat</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>"
    "<PROPERTY NAME=\"CIMStatusCode\" TYPE=\"uint32\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ValueMap\" TYPE=\"string\"><VALUE.ARRAY><VALUE>1</VALUE>"
    "<VALUE>2</VALUE><VALUE>3</VALUE><VALUE>4</VALUE><VALUE>5</VALUE><VALUE>6</VALUE>"
    "<VALUE>7</VALUE><VALUE>8</VALUE><VALUE>9</VALUE><VALUE>10</VALUE><VALUE>11</VALUE>"
    "<VALUE>12</VALUE><VALUE>13</VALUE><VALUE>14</VALUE><VALUE>15</VALUE><VALUE>16</VALUE>"
    "<VALUE>17</VALUE><VALUE>18</VALUE><VALUE>19</VALUE><VALUE>20</VALUE><VALUE>21</VALUE>"
    "<VALUE>22</VALUE><VALUE>23</VALUE><VALUE>24</VALUE><VALUE>25</VALUE><VALUE>26</VALUE>"
    "<VALUE>27</VALUE><VALUE>28</VALUE><VALUE>29</VALUE><VALUE>..</VALUE></VALUE.ARRAY></QUALIFIER>"
    "<QUALIFIER NAME=\"Values\" TYPE=\"string\" TRANSLATABLE=\"true\"><VALUE.ARRAY><VALUE>148</VALUE>"
    "<VALUE>149</VALUE><VALUE>150</VALUE><VALUE>151</VALUE><VALUE>152</VALUE><VALUE>153</VALUE>"
    "<VALUE>154</VALUE><VALUE>155</VALUE><VALUE>156</VALUE><VALUE>157</VALUE><VALUE>158</VALUE>"
    "<VALUE>159</VALUE><VALUE>160</VALUE><VALUE>161</VALUE><VALUE>162</VALUE><VALUE>163</VALUE>"
    "<VALUE>164</VALUE><VALUE>165</VALUE><VALUE>166</VALUE><VALUE>167</VALUE><VALUE>168</VALUE>"
    "<VALUE>169</VALUE><VALUE>170</VALUE><VALUE>171</VALUE><VALUE>172</VALUE><VALUE>173</VALUE>"
    "<VALUE>174</VALUE><VALUE>175</VALUE><VALUE>176</VALUE><VALUE>12</VALUE></VALUE.ARRAY></QUALIFIER>"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\">"
    "<VALUE.ARRAY><VALUE>CIM_Error.CIMStatusCodeDescription</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY>"
    "<PROPERTY NAME=\"CIMStatusCodeDescription\" TYPE=\"string\" CLASSORIGIN=\"CIM_Error\">"
    "<QUALIFIER NAME=\"ModelCorrespondence\" TYPE=\"string\">"
    "<VALUE.ARRAY><VALUE>CIM_Error.CIMStatusCode</VALUE></VALUE.ARRAY></QUALIFIER></PROPERTY></CLASS>";

NitsTestWithSetup(TestWSMAN_GetClass_CIM_Error_StandardRtti_OOP, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false,
            "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\"><s:Header><a:To>http://157.59.86.37:7778/wsman</a:To><w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/cim-xml/2/cim-schema/2/*</w:ResourceURI><a:ReplyTo><a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo><a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Get</a:Action><w:MaxEnvelopeSize s:mustUnderstand=\"true\">1048576</w:MaxEnvelopeSize><a:MessageID>uuid:DFCFFC30-89CA-4C3F-8E8C-4DA843C58615</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:SessionId s:mustUnderstand=\"false\">uuid:3091788F-6729-47C1-8A9C-CF6F387170E7</p:SessionId><p:OperationID s:mustUnderstand=\"false\">uuid:45B3AA8E-7853-4E1C-8437-FE5546D0D08E</p:OperationID><p:SequenceId s:mustUnderstand=\"false\">1</p:SequenceId><w:SelectorSet><w:Selector Name=\"__cimnamespace\">oop/requestor/test/c</w:Selector><w:Selector Name=\"ClassName\">CIM_Error</w:Selector></w:SelectorSet><w:OptionSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><w:Option Name=\"IncludeInheritanceHierarchy\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeInheritedElements\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeQualifiers\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"__MI_CallbackRegistration\" Type=\"xs:int\">11</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">0</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">1</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">2</w:Option><w:Option Name=\"wmi:__MI_OPERATIONOPTIONS_WRITEERRORMODE\" Type=\"xs:unsignedInt\">1</w:Option><w:Option Name=\"msftwinrm:UsePreciseArrays\" Type=\"xs:boolean\">true</w:Option></w:OptionSet></s:Header><s:Body></s:Body></s:Envelope>"
            , r_h, r_b, true );

    NitsTraceExA(r_b.c_str(), NitsHere(), NitsAutomatic);
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(r_b.find("CLASSORIGIN") != string::npos);
    UT_ASSERT(r_b.find("DERIVATION") != string::npos);
    UT_ASSERT(r_b.find("QUALIFIER") != string::npos);
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse</wsa:Action>") != string::npos);

    UT_ASSERT(r_b.find(desiredStandardRttiOOPErrorString) != string::npos);
}
NitsEndTest
#endif

NitsTestWithSetup(TestWSMAN_GetClass_MSFT_Animal_StandardRtti_OOP, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false,
            "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\"><s:Header><a:To>http://157.59.86.37:7778/wsman</a:To><w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/cim-xml/2/cim-schema/2/*</w:ResourceURI><a:ReplyTo><a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo><a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Get</a:Action><w:MaxEnvelopeSize s:mustUnderstand=\"true\">1048576</w:MaxEnvelopeSize><a:MessageID>uuid:D3F422F5-574D-40CD-A610-FFF8FBDF5F83</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:SessionId s:mustUnderstand=\"false\">uuid:3091788F-6729-47C1-8A9C-CF6F387170E7</p:SessionId><p:OperationID s:mustUnderstand=\"false\">uuid:18D51124-A440-45B1-B4B1-CC085A5F9A32</p:OperationID><p:SequenceId s:mustUnderstand=\"false\">1</p:SequenceId><w:SelectorSet><w:Selector Name=\"__cimnamespace\">oop/requestor/test/c</w:Selector><w:Selector Name=\"ClassName\">MSFT_Animal</w:Selector></w:SelectorSet><w:OptionSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><w:Option Name=\"IncludeInheritanceHierarchy\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeInheritedElements\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeQualifiers\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"__MI_CallbackRegistration\" Type=\"xs:int\">11</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">0</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">1</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">2</w:Option><w:Option Name=\"wmi:__MI_OPERATIONOPTIONS_WRITEERRORMODE\" Type=\"xs:unsignedInt\">1</w:Option><w:Option Name=\"msftwinrm:UsePreciseArrays\" Type=\"xs:boolean\">true</w:Option></w:OptionSet></s:Header><s:Body></s:Body></s:Envelope>"
            , r_h, r_b, true );

    NitsTraceExA(r_b.c_str(), NitsHere(), NitsAutomatic);
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(r_b.find("CLASSORIGIN") != string::npos);
    UT_ASSERT(r_b.find("DERIVATION") != string::npos);
    UT_ASSERT(r_b.find("PROPAGATED") != string::npos);
    UT_ASSERT(r_b.find("QUALIFIER") != string::npos);
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse</wsa:Action>") != string::npos);

    UT_ASSERT(r_b.find("<CLASS NAME=\"MSFT_Animal\" SUPERCLASS=\"MSFT_Base\" DERIVATION=\"MSFT_Base\"><PROPERTY NAME=\"Key\" TYPE=\"uint32\" CLASSORIGIN=\"MSFT_Base\" PROPAGATED=\"true\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY NAME=\"Species\" TYPE=\"string\" CLASSORIGIN=\"MSFT_Animal\"></PROPERTY></CLASS>") != string::npos);
}
NitsEndTest


NitsTestWithSetup(TestWSMAN_GetClass_X_HugeNumber_StandardRtti, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false,
            "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\"><s:Header><a:To>http://157.59.85.74:7778/wsman</a:To><w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/cim-xml/2/cim-schema/2/*</w:ResourceURI><a:ReplyTo><a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo><a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Get</a:Action><w:MaxEnvelopeSize s:mustUnderstand=\"true\">1048576</w:MaxEnvelopeSize><a:MessageID>uuid:B60F3103-A48A-408E-BC11-998452D82D2F</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:SessionId s:mustUnderstand=\"false\">uuid:9802F98B-CD2D-4260-82AD-D6FCAB5E1B19</p:SessionId><p:OperationID s:mustUnderstand=\"false\">uuid:48E05E94-2337-474E-8D6C-22484C00940A</p:OperationID><p:SequenceId s:mustUnderstand=\"false\">1</p:SequenceId><w:SelectorSet><w:Selector Name=\"__cimnamespace\">test/cpp</w:Selector><w:Selector Name=\"ClassName\">X_HugeNumber</w:Selector></w:SelectorSet><w:OptionSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><w:Option Name=\"IncludeInheritanceHierarchy\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeInheritedElements\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeQualifiers\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"msftwinrm:UsePreciseArrays\" Type=\"xs:boolean\">true</w:Option></w:OptionSet></s:Header><s:Body></s:Body></s:Envelope>"
            , r_h, r_b, true );

    NitsTraceExA(r_b.c_str(), NitsHere(), NitsAutomatic);
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(r_b.find("CLASSORIGIN") != string::npos);
    UT_ASSERT(r_b.find("DERIVATION") != string::npos);
    UT_ASSERT(r_b.find("PROPAGATED") != string::npos);
    UT_ASSERT(r_b.find("QUALIFIER") != string::npos);
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse</wsa:Action>") != string::npos);

    UT_ASSERT(r_b.find("<CLASS NAME=\"X_HugeNumber\" SUPERCLASS=\"X_Number\" DERIVATION=\"X_Number,X_ManagedElement\"><PROPERTY NAME=\"Description\" TYPE=\"string\" CLASSORIGIN=\"X_ManagedElement\" PROPAGATED=\"true\"></PROPERTY><PROPERTY NAME=\"Number\" TYPE=\"uint64\" CLASSORIGIN=\"X_Number\" PROPAGATED=\"true\"><QUALIFIER NAME=\"key\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY NAME=\"Magnitude\" TYPE=\"uint32\" CLASSORIGIN=\"X_HugeNumber\"></PROPERTY><PROPERTY NAME=\"MagnitudeObj\" TYPE=\"string\" CLASSORIGIN=\"X_HugeNumber\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_SmallNumber</VALUE></QUALIFIER></PROPERTY><PROPERTY.ARRAY NAME=\"Numbers123\" TYPE=\"string\" CLASSORIGIN=\"X_HugeNumber\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_SmallNumber</VALUE></QUALIFIER></PROPERTY.ARRAY><PROPERTY NAME=\"Number0\" TYPE=\"string\" CLASSORIGIN=\"X_HugeNumber\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY.ARRAY NAME=\"TwoTestObjects\" TYPE=\"string\" CLASSORIGIN=\"X_HugeNumber\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.ARRAY><PROPERTY NAME=\"TestObject\" TYPE=\"string\" CLASSORIGIN=\"X_HugeNumber\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_TestObject</VALUE></QUALIFIER></PROPERTY><METHOD NAME=\"SpellMagnitude\" TYPE=\"string\" CLASSORIGIN=\"X_HugeNumber\"></METHOD><METHOD NAME=\"TestEmbedded\" TYPE=\"string\" CLASSORIGIN=\"X_HugeNumber\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_TestObject</VALUE></QUALIFIER><QUALIFIER NAME=\"static\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><PARAMETER.ARRAY NAME=\"objectsArray\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"out\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY><PARAMETER NAME=\"objectSingle\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"out\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER><PARAMETER.ARRAY NAME=\"testObjectsArray\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_TestObject</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"out\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY><PARAMETER NAME=\"testObjectSingle\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_TestObject</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"out\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_GetClass_X_HugeNumber_FullRttiNonWinRMClient, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false,
            "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\"><s:Header><a:To>http://157.59.85.74:7778/wsman</a:To><w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/cim-xml/2/cim-schema/2/*</w:ResourceURI><a:ReplyTo><a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo><a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Get</a:Action><w:MaxEnvelopeSize s:mustUnderstand=\"true\">1048576</w:MaxEnvelopeSize><a:MessageID>uuid:C9E3315D-B056-441D-A6C8-0E8D5CD5F73F</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:SessionId s:mustUnderstand=\"false\">uuid:9802F98B-CD2D-4260-82AD-D6FCAB5E1B19</p:SessionId><p:OperationID s:mustUnderstand=\"false\">uuid:3A1A4B66-9803-46AA-9044-DB92F46B6F05</p:OperationID><p:SequenceId s:mustUnderstand=\"false\">1</p:SequenceId><w:SelectorSet><w:Selector Name=\"__cimnamespace\">test/cpp</w:Selector><w:Selector Name=\"ClassName\">X_HugeNumber</w:Selector></w:SelectorSet><w:OptionSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><w:Option Name=\"IncludeInheritanceHierarchy\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeInheritedElements\" Type=\"xs:boolean\">false</w:Option><w:Option Name=\"IncludeQualifiers\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">0</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">1</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">2</w:Option><w:Option Name=\"msftwinrm:UsePreciseArrays\" Type=\"xs:boolean\">true</w:Option></w:OptionSet></s:Header><s:Body></s:Body></s:Envelope>"
            , r_h, r_b, false );

    NitsTraceExA(r_b.c_str(), NitsHere(), NitsAutomatic);
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(r_b.find("CLASSORIGIN") == string::npos);
    UT_ASSERT(r_b.find("DERIVATION") != string::npos);
    UT_ASSERT(r_b.find("PROPAGATED") == string::npos);
    UT_ASSERT(r_b.find("QUALIFIER") != string::npos);
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse</wsa:Action>") != string::npos);
    UT_ASSERT(r_b.find("<CLASS NAME=\"X_HugeNumber\" SUPERCLASS=\"X_Number\" DERIVATION=\"X_Number,X_ManagedElement\"><PROPERTY NAME=\"Magnitude\" TYPE=\"uint32\"></PROPERTY><PROPERTY NAME=\"MagnitudeObj\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_SmallNumber</VALUE></QUALIFIER></PROPERTY><PROPERTY.ARRAY NAME=\"Numbers123\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_SmallNumber</VALUE></QUALIFIER></PROPERTY.ARRAY><PROPERTY NAME=\"Number0\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY.ARRAY NAME=\"TwoTestObjects\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.ARRAY><PROPERTY NAME=\"TestObject\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_TestObject</VALUE></QUALIFIER></PROPERTY><METHOD NAME=\"SpellMagnitude\" TYPE=\"string\"></METHOD><METHOD NAME=\"TestEmbedded\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_TestObject</VALUE></QUALIFIER><QUALIFIER NAME=\"static\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><PARAMETER.ARRAY NAME=\"objectsArray\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"out\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY><PARAMETER NAME=\"objectSingle\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"out\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER><PARAMETER.ARRAY NAME=\"testObjectsArray\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_TestObject</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"out\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY><PARAMETER NAME=\"testObjectSingle\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_TestObject</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"out\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_GetClass_X_HugeNumber_FullRtti, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false,
            "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\"><s:Header><a:To>http://157.59.85.74:7778/wsman</a:To><w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/cim-xml/2/cim-schema/2/*</w:ResourceURI><a:ReplyTo><a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo><a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Get</a:Action><w:MaxEnvelopeSize s:mustUnderstand=\"true\">1048576</w:MaxEnvelopeSize><a:MessageID>uuid:C9E3315D-B056-441D-A6C8-0E8D5CD5F73F</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:SessionId s:mustUnderstand=\"false\">uuid:9802F98B-CD2D-4260-82AD-D6FCAB5E1B19</p:SessionId><p:OperationID s:mustUnderstand=\"false\">uuid:3A1A4B66-9803-46AA-9044-DB92F46B6F05</p:OperationID><p:SequenceId s:mustUnderstand=\"false\">1</p:SequenceId><w:SelectorSet><w:Selector Name=\"__cimnamespace\">test/cpp</w:Selector><w:Selector Name=\"ClassName\">X_HugeNumber</w:Selector></w:SelectorSet><w:OptionSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><w:Option Name=\"IncludeInheritanceHierarchy\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"IncludeInheritedElements\" Type=\"xs:boolean\">false</w:Option><w:Option Name=\"IncludeQualifiers\" Type=\"xs:boolean\">true</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">0</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">1</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">2</w:Option><w:Option Name=\"msftwinrm:UsePreciseArrays\" Type=\"xs:boolean\">true</w:Option></w:OptionSet></s:Header><s:Body></s:Body></s:Envelope>"
            , r_h, r_b, true );

    NitsTraceExA(r_b.c_str(), NitsHere(), NitsAutomatic);
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(r_b.find("CLASSORIGIN") != string::npos);
    UT_ASSERT(r_b.find("DERIVATION") != string::npos);
    UT_ASSERT(r_b.find("PROPAGATED") == string::npos);
    UT_ASSERT(r_b.find("QUALIFIER") != string::npos);
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse</wsa:Action>") != string::npos);
    UT_ASSERT(r_b.find("<CLASS NAME=\"X_HugeNumber\" SUPERCLASS=\"X_Number\" DERIVATION=\"X_Number,X_ManagedElement\"><PROPERTY NAME=\"Magnitude\" TYPE=\"uint32\" CLASSORIGIN=\"X_HugeNumber\"></PROPERTY><PROPERTY NAME=\"MagnitudeObj\" TYPE=\"string\" CLASSORIGIN=\"X_HugeNumber\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_SmallNumber</VALUE></QUALIFIER></PROPERTY><PROPERTY.ARRAY NAME=\"Numbers123\" TYPE=\"string\" CLASSORIGIN=\"X_HugeNumber\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_SmallNumber</VALUE></QUALIFIER></PROPERTY.ARRAY><PROPERTY NAME=\"Number0\" TYPE=\"string\" CLASSORIGIN=\"X_HugeNumber\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY><PROPERTY.ARRAY NAME=\"TwoTestObjects\" TYPE=\"string\" CLASSORIGIN=\"X_HugeNumber\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PROPERTY.ARRAY><PROPERTY NAME=\"TestObject\" TYPE=\"string\" CLASSORIGIN=\"X_HugeNumber\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_TestObject</VALUE></QUALIFIER></PROPERTY><METHOD NAME=\"SpellMagnitude\" TYPE=\"string\" CLASSORIGIN=\"X_HugeNumber\"></METHOD><METHOD NAME=\"TestEmbedded\" TYPE=\"string\" CLASSORIGIN=\"X_HugeNumber\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_TestObject</VALUE></QUALIFIER><QUALIFIER NAME=\"static\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><PARAMETER.ARRAY NAME=\"objectsArray\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"out\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY><PARAMETER NAME=\"objectSingle\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedObject\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"out\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER><PARAMETER.ARRAY NAME=\"testObjectsArray\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_TestObject</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"out\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER.ARRAY><PARAMETER NAME=\"testObjectSingle\" TYPE=\"string\"><QUALIFIER NAME=\"EmbeddedInstance\" TYPE=\"string\"><VALUE>X_TestObject</VALUE></QUALIFIER><QUALIFIER NAME=\"in\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER><QUALIFIER NAME=\"out\" TYPE=\"boolean\"><VALUE>true</VALUE></QUALIFIER></PARAMETER></METHOD></CLASS>") != string::npos);
}
NitsEndTest

NitsTestWithSetup(TestWSMAN_GetClass_X_HugeNumber_AllOptionsTurnedOff, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false,
            "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\"><s:Header><a:To>http://157.59.85.74:7778/wsman</a:To><w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/cim-xml/2/cim-schema/2/*</w:ResourceURI><a:ReplyTo><a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo><a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Get</a:Action><w:MaxEnvelopeSize s:mustUnderstand=\"true\">1048576</w:MaxEnvelopeSize><a:MessageID>uuid:E1675FFB-B761-402F-B9A0-DDA950E2D744</a:MessageID><w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><p:SessionId s:mustUnderstand=\"false\">uuid:E519A3F9-FAB7-4E0A-A34A-08CEE460A713</p:SessionId><p:OperationID s:mustUnderstand=\"false\">uuid:C13B6D08-E35C-465A-BCC1-05122A00CE1B</p:OperationID><p:SequenceId s:mustUnderstand=\"false\">1</p:SequenceId><w:SelectorSet><w:Selector Name=\"__cimnamespace\">test/cpp</w:Selector><w:Selector Name=\"ClassName\">X_HugeNumber</w:Selector></w:SelectorSet><w:OptionSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><w:Option Name=\"wmi:IncludeClassOrigin\" Type=\"xs:boolean\">false</w:Option><w:Option Name=\"wmi:IncludeInheritanceHierarchy\" Type=\"xs:boolean\">false</w:Option><w:Option Name=\"wmi:IncludeInheritedElements\" Type=\"xs:boolean\">false</w:Option><w:Option Name=\"wmi:IncludeQualifiers\" Type=\"xs:boolean\">false</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">0</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">1</w:Option><w:Option Name=\"wmiarray:__MI_OPERATIONOPTIONS_CHANNELVALUE\" Type=\"xs:unsignedInt\">2</w:Option><w:Option Name=\"msftwinrm:UsePreciseArrays\" Type=\"xs:boolean\">true</w:Option></w:OptionSet></s:Header><s:Body></s:Body></s:Envelope>"
            , r_h, r_b, true );

    NitsTraceExA(r_b.c_str(), NitsHere(), NitsAutomatic);
    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(r_b.find("CLASSORIGIN") == string::npos);
    UT_ASSERT(r_b.find("DERIVATION") == string::npos);
    UT_ASSERT(r_b.find("PROPAGATED") == string::npos);
    UT_ASSERT(r_b.find("QUALIFIER") == string::npos);
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse</wsa:Action>") != string::npos);
    UT_ASSERT(r_b.find("<CLASS NAME=\"X_HugeNumber\" SUPERCLASS=\"X_Number\"><PROPERTY NAME=\"Magnitude\" TYPE=\"uint32\"></PROPERTY><PROPERTY NAME=\"MagnitudeObj\" TYPE=\"string\"></PROPERTY><PROPERTY.ARRAY NAME=\"Numbers123\" TYPE=\"string\"></PROPERTY.ARRAY><PROPERTY NAME=\"Number0\" TYPE=\"string\"></PROPERTY><PROPERTY.ARRAY NAME=\"TwoTestObjects\" TYPE=\"string\"></PROPERTY.ARRAY><PROPERTY NAME=\"TestObject\" TYPE=\"string\"></PROPERTY><METHOD NAME=\"SpellMagnitude\" TYPE=\"string\"></METHOD><METHOD NAME=\"TestEmbedded\" TYPE=\"string\"><PARAMETER.ARRAY NAME=\"objectsArray\" TYPE=\"string\"></PARAMETER.ARRAY><PARAMETER NAME=\"objectSingle\" TYPE=\"string\"></PARAMETER><PARAMETER.ARRAY NAME=\"testObjectsArray\" TYPE=\"string\"></PARAMETER.ARRAY><PARAMETER NAME=\"testObjectSingle\" TYPE=\"string\"></PARAMETER></METHOD></CLASS>") != string::npos);
}
NitsEndTest

#ifndef DISABLE_INDICATION


static string _CreateSubscribeRequestXML(
    const char* cn,
    const char* ns,
    string  opTimeout,
    bool    specifyNamespace = true )
{
    string res = 
"<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\""
"   xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\""
"   xmlns:n=\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\""
"   xmlns:e=\"http://schemas.xmlsoap.org/ws/2004/08/eventing\""
"   xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\">"
"<s:Header>"
"<a:To>http://linux-22kv:22000/wsman</a:To>"
"<w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/";

    res += cn;
    res += "</w:ResourceURI>"
"<a:ReplyTo>"
"<a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address>"
"</a:ReplyTo>"
"<a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/eventing/Subscribe</a:Action>"
"<w:MaxEnvelopeSize s:mustUnderstand=\"true\">102400</w:MaxEnvelopeSize>"
"<a:MessageID>uuid:FEF3DF41-FFEC-4ABE-ADFC-A8305DAB71C9</a:MessageID>"
"<w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" /><w:SelectorSet>";

    if (specifyNamespace)
    {
        res += 
            "<w:Selector Name=\"__cimnamespace\">";
        res += s_currentNamespace;
        res += ns;
        res += "</w:Selector>";
    }
    else
    {
        res += 
            "<w:Selector Name=\"something\">value</w:Selector>";
    }

    res += 
"</w:SelectorSet>"
"<w:OperationTimeout>";
    res += opTimeout;
    res += 
"</w:OperationTimeout>"
"</s:Header>"
"<s:Body>"
"<e:Subscribe>"
"<e:Delivery Mode=\"http://schemas.dmtf.org/wbem/wsman/1/wsman/Pull\">http://linux-22kv:22000</e:Delivery>"
"<w:Filter Dialect=\"http://schemas.microsoft.com/wbem/wsman/1/WQL\">Select * from L_IndicationC3</w:Filter>"
"</e:Subscribe></s:Body></s:Envelope>";

    return res;
}

//
// Good value example: PT5.000S (positive xs:duration)
//
// Bad examples:    -PT5.000S (negative value)
//                  01:23:45 (xs:time not supported)
//
NitsTestWithSetup(TestWSMAN_Subscribe_Specifies_Invalid_OperationTimeout, TestWsmanSetup)
{
    string r_b, r_h;

    SockSendRecvHTTP(
        s, 
        false, 
        _CreateSubscribeRequestXML("R_IndicationC3", "root/cimv2", "-PT5.000S", true).c_str(), 
        r_h, 
        r_b );

    // Check for InternalError.  This indicates a parsing error because the value is negative.    
    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.dmtf.org/wbem/wsman/1/wsman/fault</wsa:Action>") != string::npos);
    UT_ASSERT(r_b.find("wsman:InternalError") != string::npos);

    r_b.clear();
    r_h.clear();

    SockSendRecvHTTP(
        s, 
        false, 
        _CreateSubscribeRequestXML("R_IndicationC3", "root/cimv2", "01:23:45", true).c_str(), 
        r_h, 
        r_b );

    // Check for InvalidMessageInformationHeader.  This means that xs:datetime is not supported
    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(r_b.find("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/08/addressing/fault</wsa:Action>") != string::npos);
    UT_ASSERT(r_b.find("wsa:InvalidMessageInformationHeader") != string::npos);
}
NitsEndTest


#endif

