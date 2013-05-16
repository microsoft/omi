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
#include <protocol/protocol.h>
#include <sock/sock.h>
#include <io/io.h>
#include "utils.h"

using namespace std;

/* Local data */
static Sock s = INVALID_SOCK;
static const char* s_currentNamespace = "";
static bool s_DisconnectAfterEachTest = false;

void SetupHelper();
void CleanupHelper();

static void setUp()
{
    SetupHelper();

    if (INVALID_SOCK == s)
    {
#if defined(_MSC_VER)
        s = SockConnectLocal(7778);
#else
        s = SockConnectLocal(ut::getUnittestPortNumberWSMANHTTP());
#endif
    }
}

static void cleanup()
{
    if (s_DisconnectAfterEachTest)
    {
        if (INVALID_SOCK != s) Sock_Close(s);

        s = INVALID_SOCK;
    }
    CleanupHelper();
}

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

static void TestWSMAN_CDATARequest()
{
    string r_b, r_h;

	// use utf16 encoding header
    SockSendRecvHTTP(s, true, _CreateCDATARequestXML("test/cpp").c_str(), r_h, r_b );
    // send invalid xml; expecting http 500 back
    UT_ASSERT(r_h.find("500") != string::npos);
}

static void TestWSMANemptyRequest()
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false, "", r_h, r_b );
    // send invalid xml; expecting http 500 back
    UT_ASSERT(r_h.find("500") != string::npos);
}

static void TestWSMANInvalidXML()
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false, "invalid xml", r_h, r_b );
    // send invalid xml; expecting http 500 back
    UT_ASSERT(r_h.find("500") != string::npos);
}

static void TestWSMAN_NotSupportedEncoding()
{
    string r_b, r_h;

    // use utf16 encoding header
    SockSendRecvHTTP(s, true, _CreateRequestXML("X_number", "test/cpp").c_str(), r_h, r_b );
    // send not-supported encoding; expecting http 500 back
    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;
    UT_ASSERT(r_h.find("500") != string::npos);
}

static void TestWSMAN_Fault_invalidNamespace()
{
    string r_b, r_h;
    SockSendRecvHTTP(s, false, _CreateRequestXML("X_number", "invlaid/namespace").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    // send invalid request; expecting http 500 back
    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());
    UT_ASSERT(r_b.find("wsa:DestinationUnreachable") != string::npos);
    UT_ASSERT(r_b.find("CIM ERROR:INVALID_NAMESPACE") != string::npos);
}

#if 0
static void TestWSMAN_Fault_instanceBiggerThaEnvelope()
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
#endif

static void TestWSMAN_Fault_invalidClass()
{
    string r_b, r_h;
    SockSendRecvHTTP(s, false, _CreateRequestXML("InvalidClassname", "test/cpp").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    // send invalid request; expecting http 500 back
    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());
    UT_ASSERT(r_b.find("wsa:DestinationUnreachable") != string::npos);
    UT_ASSERT(r_b.find("CIM ERROR:INVALID_CLASS") != string::npos);
}

static void TestWSMAN_Enumerate_XProfile()
{
    string r_b, r_h;
    SockSendRecvHTTP(s, false, _CreateRequestXML("X_Profile", "interop").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("200") != string::npos);
    UT_ASSERT(!r_b.empty());
    UT_ASSERT(r_b.find("World") != string::npos);
    UT_ASSERT(r_b.find("Huge Numbers") != string::npos);
}

static void TestWSMAN_Enumerate_XProfile_EPR_Only()
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

static void TestWSMAN_Enumerate_XProfile_EPRAndObject()
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

static void TestWSMAN_Enumerate_X_SingletonWithAllTypes()
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
    UT_ASSERT(r_b.find(":type=\"MSFT_Person_Type\"") != string::npos);
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
    UT_ASSERT(r_b.find(":type=\"X_TestObject_Type\"") != string::npos);
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

static void TestWSMAN_Enumerate_X_HugeNumberConformsToProfile()
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

static void TestWSMAN_Enumerate_MissingNamespace()
{
    string r_b, r_h;
    /* namespace param is missing - expecting error back */
    SockSendRecvHTTP(s, false, _CreateRequestXML("X_Profile", "interop", 0, 0, false).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(r_b.find(">wsman:InternalError<") != string::npos);
    UT_ASSERT(r_b.find(">mandatory parameters") != string::npos);
}

#if 0
static void _PrintBuffer(const char* str)
{
    Zprintf(MI_T("\n=========================\n"));
    Zprintf(MI_T("%s\n"), zcs(str));
    Zprintf(MI_T("=========================\n\n"));
}
#endif

static void TestWSMAN_Enumerate_X_HugeNumber_Deep()
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

static void TestWSMAN_Enumerate_X_HugeNumber_BasicProps()
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

static void TestWSMAN_Enumerate_X_HugeNumber_Shallow()
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

static void TestWSMAN_Invoke_SmallNumber_SpellNumber()
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

static void TestWSMAN_Invoke_MissingNamespace()
{
    string r_b, r_h;
    SockSendRecvHTTP(s, false, 
        _CreateInvokeRequestXML("X_Smallnumber", "test/cpp", "spellNumber", "<p:num>77</p:num>", "", false).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data 
    UT_ASSERT(r_b.find(">wsman:InternalError<") != string::npos);
    UT_ASSERT(r_b.find("CIM ERROR:INVALID_PARAMETER") != string::npos);
}

static void TestWSMAN_Invoke_SmallNumber_SpellNumber_OOP()
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

static void TestWSMAN_Invoke_TestEmbeddedObjectReturnKey20100609()
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

static void TestWSMAN_Invoke_TestEmbeddedObjectReturnKey20100609_OOP()
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

static void TestWSMAN_Invoke_TestEmbedded()
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

static void TestWSMAN_Invoke_TestEmbeddedWithArray()
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

static void TestWSMAN_Invoke_TestEmbeddedWithMultipleArrays()
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

static void TestWSMAN_Invoke_TestAllTypesWithSingleItemArray()
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

/* verify array buffer re-allocation (16 items boundary)*/
static void TestWSMAN_Invoke_TestAllTypesWith17ItemsArray()
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

/* verify array two buffer re-allocations (16 items boundary)*/
static void TestWSMAN_Invoke_TestAllTypesWith33ItemsArray()
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

/* verify u64 type operations */
static void TestWSMAN_Invoke_TestAllTypesU64Max()
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

static void TestWSMAN_Invoke_TestAllTypesStringArray()
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

static void TestWSMAN_Invoke_TestAllTypesReference()
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

static void TestWSMAN_Get_SmallNumber_17()
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

static void TestWSMAN_Get_SmallNumber_NotFound()
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
}

static void TestWSMAN_Get_Person_CimError()
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false, 
        _CreateGetRequestXML("MSFT_Person", "test/c", "<w:Selector Name=\"key\">9999</w:Selector>").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data for some CIM_Error type stuff
    UT_ASSERT(r_b.find("CIM ERROR:NOT_FOUND") != string::npos);
}

static void TestWSMAN_Get_MissingNamespace()
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false, 
        _CreateGetRequestXML("X_smallNumber", "test/cpp", "<w:Selector Name=\"Number\">17</w:Selector>", false).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find(">CIM ERROR:INVALID_PARAMETER") != string::npos);
    UT_ASSERT(r_b.find("Value>wsman:InternalError<") != string::npos);
}

static void TestWSMAN_Delete_SmallNumber_7()
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

static void TestWSMAN_Delete_SmallNumber_17_NotFound()
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false, 
        _CreateDeleteRequestXML("X_smallNumber", "test/cpp", "<w:Selector Name=\"Number\">17</w:Selector>").c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find("CIM ERROR:NOT_FOUND") != string::npos);
    UT_ASSERT(r_b.find("Value>wsa:DestinationUnreachable<") != string::npos);
}

static void TestWSMAN_Delete_MissingNamespace()
{
    string r_b, r_h;

    SockSendRecvHTTP(s, false, 
        _CreateDeleteRequestXML("X_smallNumber", "test/cpp", "<w:Selector Name=\"Number\">7</w:Selector>", false).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find(">CIM ERROR:INVALID_PARAMETER") != string::npos);
    UT_ASSERT(r_b.find("Value>wsman:InternalError<") != string::npos);
}

static void TestWSMAN_Create_SmallNumber_ok()
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

static void TestWSMAN_Create_SmallNumber_failed_invalid_prop()
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
    UT_ASSERT(r_b.find("CIM ERROR:FAILED") != string::npos);
}

static void TestWSMAN_Create_SmallNumber_failed_no_description()
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
    UT_ASSERT(r_b.find("CIM ERROR:NOT_FOUND") != string::npos);
}

static void TestWSMAN_Create_SmallNumber_MissingNamespace()
{
    string r_b, r_h;
    const char* props = 
"<p:X_smallNumber xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/X_smallNumber\">"
"      <p:Description>text</p:Description>"
"  </p:X_smallNumber>";

    SockSendRecvHTTP(s, false, 
        _CreateCreateRequestXML("X_smallNumber", "test/cpp", props, false).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find(">CIM ERROR:INVALID_PARAMETER") != string::npos);
    UT_ASSERT(r_b.find("Value>wsman:InternalError<") != string::npos);
}

static void TestWSMAN_Modify_SmallNumber_ok()
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

static void TestWSMAN_Modify_SmallNumber_failed_invalid_prop()
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
    UT_ASSERT(r_b.find("CIM ERROR:FAILED") != string::npos);
}

static void TestWSMAN_Modify_SmallNumber_failed_no_description()
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
    UT_ASSERT(r_b.find("CIM ERROR:NOT_FOUND") != string::npos);
}

static void TestWSMAN_TestImproperXsiType ()
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

static void TestWSMAN_Modify_SmallNumber_MissingNamespace()
{
    string r_b, r_h;
    const char* props = 
"<p:X_smallNumber xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/X_smallNumber\">"
"      <p:Description>text</p:Description>"
"  </p:X_smallNumber>";
    const char* keys = "<w:Selector Name=\"Number\">7</w:Selector>";

    SockSendRecvHTTP(s, false, 
        _CreateModifyRequestXML("X_smallNumber", "test/cpp", keys, props, false).c_str(), r_h, r_b );

    //cout << "resp header: " << r_h << endl << endl << "body: " << r_b << endl;

    UT_ASSERT(r_h.find("500") != string::npos);
    UT_ASSERT(!r_b.empty());

    // check data - number of elements and sum
    UT_ASSERT(r_b.find(">CIM ERROR:INVALID_PARAMETER") != string::npos);
    UT_ASSERT(r_b.find("Value>wsman:InternalError<") != string::npos);
}

void WSMAN_Tests_With_Server()
{
    const char* namespaces[] = {
        "", "oop/requestor/"
    };

    for (int KeepALive = NitsIsActivated() ? 1 : 0; KeepALive < 2; KeepALive++)
    {
        if (KeepALive == 0)
            continue;

        s_DisconnectAfterEachTest = (KeepALive !=0 );

        for (unsigned int i = 0; i < (NitsIsActivated() ? 1 : MI_COUNT(namespaces)); i++)
        {
            s_currentNamespace = namespaces[i];

            // general errors
            UT_TEST(TestWSMANemptyRequest);
            UT_TEST(TestWSMANInvalidXML);
            UT_TEST(TestWSMAN_NotSupportedEncoding);

            // wsman faults
            UT_TEST(TestWSMAN_Fault_invalidNamespace);
            UT_TEST(TestWSMAN_Fault_invalidClass);
#if 0
            UT_TEST(TestWSMAN_Fault_instanceBiggerThaEnvelope);
#endif

            // enumeration
            UT_TEST(TestWSMAN_Enumerate_XProfile);
            UT_TEST(TestWSMAN_Enumerate_XProfile_EPR_Only);
            UT_TEST(TestWSMAN_Enumerate_XProfile_EPRAndObject);
            UT_TEST(TestWSMAN_Enumerate_X_SingletonWithAllTypes);
            UT_TEST(TestWSMAN_Enumerate_X_HugeNumberConformsToProfile);
            UT_TEST(TestWSMAN_Enumerate_MissingNamespace);

            // enumeration: deep/shallow/basic-props 
            UT_TEST(TestWSMAN_Enumerate_X_HugeNumber_Deep);
            UT_TEST(TestWSMAN_Enumerate_X_HugeNumber_Shallow);
            UT_TEST(TestWSMAN_Enumerate_X_HugeNumber_BasicProps);

            // invoke
            UT_TEST(TestWSMAN_Invoke_SmallNumber_SpellNumber);
            UT_TEST(TestWSMAN_Invoke_SmallNumber_SpellNumber);
            UT_TEST(TestWSMAN_Invoke_TestEmbeddedObjectReturnKey20100609);

            UT_TEST(TestWSMAN_Invoke_TestEmbedded);
            UT_TEST(TestWSMAN_Invoke_TestEmbeddedWithArray);
            UT_TEST(TestWSMAN_Invoke_TestEmbeddedWithMultipleArrays);
            UT_TEST(TestWSMAN_Invoke_TestAllTypesWithSingleItemArray);
            UT_TEST(TestWSMAN_Invoke_TestAllTypesWith17ItemsArray);
            UT_TEST(TestWSMAN_Invoke_TestAllTypesWith33ItemsArray);
            UT_TEST(TestWSMAN_Invoke_TestAllTypesU64Max);
            UT_TEST(TestWSMAN_Invoke_TestAllTypesStringArray);
            UT_TEST(TestWSMAN_Invoke_TestAllTypesReference);
            UT_TEST(TestWSMAN_Invoke_MissingNamespace);

            // get
            UT_TEST(TestWSMAN_Get_SmallNumber_17);

            UT_TEST(TestWSMAN_Get_SmallNumber_NotFound);
            UT_TEST(TestWSMAN_Get_Person_CimError);
            UT_TEST(TestWSMAN_Get_MissingNamespace);

            // delete
            UT_TEST(TestWSMAN_Delete_SmallNumber_7);
            UT_TEST(TestWSMAN_Delete_SmallNumber_17_NotFound);
            UT_TEST(TestWSMAN_Delete_MissingNamespace);

            // create
            UT_TEST(TestWSMAN_Create_SmallNumber_ok);

            UT_TEST(TestWSMAN_Create_SmallNumber_failed_invalid_prop);
            UT_TEST(TestWSMAN_Create_SmallNumber_failed_no_description);
            UT_TEST(TestWSMAN_Create_SmallNumber_MissingNamespace);

            // Put/Set/Modify
            UT_TEST(TestWSMAN_Modify_SmallNumber_ok);

            UT_TEST(TestWSMAN_Modify_SmallNumber_failed_invalid_prop);
            UT_TEST(TestWSMAN_Modify_SmallNumber_failed_no_description);
            UT_TEST(TestWSMAN_Modify_SmallNumber_MissingNamespace);

			// Other
			UT_TEST(TestWSMAN_CDATARequest);
			UT_TEST(TestWSMAN_TestImproperXsiType);
        }
    }

    s_currentNamespace = "";

    // test out-of-process invocation static/non-static
    UT_TEST(TestWSMAN_Invoke_SmallNumber_SpellNumber_OOP);
    UT_TEST(TestWSMAN_Invoke_TestEmbeddedObjectReturnKey20100609_OOP);
    UT_TEST(TestWSMAN_Enumerate_XProfile);

    if (!NitsIsActivated())
    {
        if (INVALID_SOCK != s)
            Sock_Close(s);

        s = INVALID_SOCK;
    }
}
