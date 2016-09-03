/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the PAL_T("License")); you may not 
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

#include <iostream>
#include <string>
#include <vector>
#include <ut/ut.h>
#include <common.h>
#include <xml/xml.h>
#include <pal/strings.h>
#include <wsman/wstags.h>
#include <wsman/wsmanparser.h>
#include <wsman/wsbuf.h>


using namespace std;

NitsSetup(TestParserSetup)
NitsEndSetup

NitsCleanup(TestParserSetup)
NitsEndCleanup

NitsTestWithSetup(TestGetResponse, TestParserSetup)
{
    MI_Uint32 count = 0;
    MI_Value value;
    MI_Type type;
    const MI_Char *name;
    MI_Uint32 flags;
    WSMAN_WSHeader wsheaders;
    XML xml;
    MI_Instance *instance = NULL;
    Batch *batch = NULL;

    // Sample GetResponse from https://msdn.microsoft.com/en-us/library/cc251505.aspx
    XML_Char data[] = PAL_T("<s:Envelope xml:lang=\"en-US\" ")
        PAL_T("xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" ")
        PAL_T("xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" ") 
        PAL_T("xmlns:w=\"http://schemas.xmlsoap.org/ws/2005/06/management\">")
        PAL_T("<s:Header>")
        PAL_T("<a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse</a:Action>")
        PAL_T("<a:MessageID s:mustUnderstand=\"true\">uuid:2DAB718A-0103-4E0A-AB17-06C8A5530D2B</a:MessageID>")
        PAL_T("<a:To>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:To>")
        PAL_T("<a:RelatesTo s:mustUnderstand=\"true\">uuid:5E6FD101-710A-4EEA-A50D-70C0BF863AA3</a:RelatesTo>")
        PAL_T("</s:Header>")
        PAL_T("<s:Body>")
        PAL_T("<p:myclass xmlns:p=\"http://schemas.microsoft.com/wsman/2005/06/wmi/root/mynamespace/myclass\">")
        PAL_T("<p:Data1>Hello World</p:Data1>")
        PAL_T("<p:id>1</p:id>")
        PAL_T("<cim:Location ")
        PAL_T("xmlns:cim=\"http://schemas.dmtf.org/wsman/2005/06/base\" ")
        PAL_T("xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" ")
        PAL_T("xmlns:w=\"http://schemas.xmlsoap.org/ws/2005/06/management\">")
        PAL_T("<a:Address>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address>")
        PAL_T("<a:ReferenceParameters>")
        PAL_T("<w:ResourceURI>http://schemas.microsoft.com/wsman/2005/06/wmi/root/mynamespace/myclass</w:ResourceURI>")
        PAL_T("<w:SelectorSet>")
        PAL_T("<w:Selector Name=\"id\">1</w:Selector>")
        PAL_T("</w:SelectorSet>")
        PAL_T("</a:ReferenceParameters>")
        PAL_T("</cim:Location>")
        PAL_T("</p:myclass>")
        PAL_T("</s:Body>")
        PAL_T("</s:Envelope>");

    memset(&wsheaders, 0, sizeof(wsheaders));

    XML_Init(&xml);

    XML_RegisterNameSpace(&xml, 's',
                          ZT("http://www.w3.org/2003/05/soap-envelope"));
    
    XML_RegisterNameSpace(&xml, 'a',
                          ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing"));

    XML_RegisterNameSpace(&xml, 'w',
                          ZT("http://schemas.xmlsoap.org/ws/2005/06/management"));

    XML_SetText(&xml, data);

    if (!NitsCompare(MI_RESULT_OK, WS_ParseSoapEnvelope(&xml), PAL_T("Parse soap envelope error")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, WS_ParseWSHeader(&xml, &wsheaders, USERAGENT_UNKNOWN), PAL_T("Parse header error")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_TRUE, wsheaders.foundAction, PAL_T("No action in header")))
    {
        goto cleanup;
    }
    if (!NitsCompare(wsheaders.rqtAction, WSMANTAG_ACTION_GET_RESPONSE, PAL_T("Action is not Get Response")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(wsheaders.rqtMessageID, PAL_T("uuid:2DAB718A-0103-4E0A-AB17-06C8A5530D2B"), PAL_T("Message ID error")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(wsheaders.rspRelatesTo, PAL_T("uuid:5E6FD101-710A-4EEA-A50D-70C0BF863AA3"), PAL_T("RelatesTo error")))
    {
        goto cleanup;
    }

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Unable to create new batch")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_RESULT_OK, WS_ParseInstanceBody(&xml, batch, &instance), PAL_T("Unable to retrieve instance")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_RESULT_OK, xml.status, PAL_T("Retrieve instance returned error xml status")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementCount(instance, &count), PAL_T("Unable to get element count")))
    {
        goto cleanup;
    }
    if (!NitsCompare(count, 3, PAL_T("Element count error")))
    {
        goto cleanup;
    }
    
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementAt(instance, 0, &name, &value, &type, &flags), PAL_T("Unable to get element 1")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(name, PAL_T("Data1"), PAL_T("Invalid element #1 name")))
    {
        goto cleanup;
    }
    if (!NitsCompare(type, MI_STRING, PAL_T("Invalid element #1 type")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(value.string, PAL_T("Hello World"), PAL_T("Invalid element #1 value")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementAt(instance, 1, &name, &value, &type, &flags), PAL_T("Unable to get element 2")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(name, PAL_T("id"), PAL_T("Invalid element #2 name")))
    {
        goto cleanup;
    }
    if (!NitsCompare(type, MI_STRING, PAL_T("Invalid element #2 type")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(value.string, PAL_T("1"), PAL_T("Invalid element #2 value")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementAt(instance, 2, &name, &value, &type, &flags), PAL_T("Unable to get element 3")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(name, PAL_T("Location"), PAL_T("Invalid element #3 name")))
    {
        goto cleanup;
    }

    cleanup:
    if (batch)
    {
        Batch_Delete(batch);
    }
}
NitsEndTest

NitsTestWithSetup(TestGetResponse2, TestParserSetup)
{
    MI_Uint32 count = 0;
    MI_Value value;
    MI_Type type;
    const MI_Char *name;
    MI_Uint32 flags;
    WSMAN_WSHeader wsheaders;
    XML xml;
    MI_Instance *instance = NULL;
    Batch *batch = NULL;

    // Sample GetResponse from https://msdn.microsoft.com/en-us/library/cc251505.aspx, but with added newline chars
    XML_Char data[] = PAL_T("<s:Envelope xml:lang=\"en-US\" ")
        PAL_T("xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" ")
        PAL_T("xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" ") 
        PAL_T("xmlns:w=\"http://schemas.xmlsoap.org/ws/2005/06/management\">\n")
        PAL_T("<s:Header>\n")
        PAL_T("<a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse</a:Action>\n")
        PAL_T("<a:MessageID s:mustUnderstand=\"true\">uuid:2DAB718A-0103-4E0A-AB17-06C8A5530D2B</a:MessageID>\n")
        PAL_T("<a:To>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:To>\n")
        PAL_T("<a:RelatesTo s:mustUnderstand=\"true\">uuid:5E6FD101-710A-4EEA-A50D-70C0BF863AA3</a:RelatesTo>\n")
        PAL_T("</s:Header>\n")
        PAL_T("<s:Body>\n")
        PAL_T("<p:myclass xmlns:p=\"http://schemas.microsoft.com/wsman/2005/06/wmi/root/mynamespace/myclass\">\n")
        PAL_T("<p:Data1>Hello World</p:Data1>\n")
        PAL_T("<p:id>1</p:id>\n")
        PAL_T("<cim:Location ")
        PAL_T("xmlns:cim=\"http://schemas.dmtf.org/wsman/2005/06/base\" ")
        PAL_T("xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" ")
        PAL_T("xmlns:w=\"http://schemas.xmlsoap.org/ws/2005/06/management\">\n")
        PAL_T("<a:Address>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address>\n")
        PAL_T("<a:ReferenceParameters>\n")
        PAL_T("<w:ResourceURI>http://schemas.microsoft.com/wsman/2005/06/wmi/root/mynamespace/myclass</w:ResourceURI>\n")
        PAL_T("<w:SelectorSet>\n")
        PAL_T("<w:Selector Name=\"id\">1</w:Selector>\n")
        PAL_T("</w:SelectorSet>\n")
        PAL_T("</a:ReferenceParameters>\n")
        PAL_T("</cim:Location>\n")
        PAL_T("</p:myclass>\n")
        PAL_T("</s:Body>\n")
        PAL_T("</s:Envelope>\n");

    memset(&wsheaders, 0, sizeof(wsheaders));

    XML_Init(&xml);

    XML_RegisterNameSpace(&xml, 's',
                          ZT("http://www.w3.org/2003/05/soap-envelope"));
    
    XML_RegisterNameSpace(&xml, 'a',
                          ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing"));

    XML_RegisterNameSpace(&xml, 'w',
                          ZT("http://schemas.xmlsoap.org/ws/2005/06/management"));

    XML_SetText(&xml, data);

    if (!NitsCompare(MI_RESULT_OK, WS_ParseSoapEnvelope(&xml), PAL_T("Parse soap envelope error")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, WS_ParseWSHeader(&xml, &wsheaders, USERAGENT_UNKNOWN), PAL_T("Parse header error")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_TRUE, wsheaders.foundAction, PAL_T("No action in header")))
    {
        goto cleanup;
    }
    if (!NitsCompare(wsheaders.rqtAction, WSMANTAG_ACTION_GET_RESPONSE, PAL_T("Action is not Get Response")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(wsheaders.rqtMessageID, PAL_T("uuid:2DAB718A-0103-4E0A-AB17-06C8A5530D2B"), PAL_T("Message ID error")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(wsheaders.rspRelatesTo, PAL_T("uuid:5E6FD101-710A-4EEA-A50D-70C0BF863AA3"), PAL_T("RelatesTo error")))
    {
        goto cleanup;
    }

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Unable to create new batch")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_RESULT_OK, WS_ParseInstanceBody(&xml, batch, &instance), PAL_T("Unable to retrieve instance")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_RESULT_OK, xml.status, PAL_T("Retrieve instance returned error xml status")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementCount(instance, &count), PAL_T("Unable to get element count")))
    {
        goto cleanup;
    }
    if (!NitsCompare(count, 3, PAL_T("Element count error")))
    {
        goto cleanup;
    }
    
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementAt(instance, 0, &name, &value, &type, &flags), PAL_T("Unable to get element 1")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(name, PAL_T("Data1"), PAL_T("Invalid element #1 name")))
    {
        goto cleanup;
    }
    if (!NitsCompare(type, MI_STRING, PAL_T("Invalid element #1 type")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(value.string, PAL_T("Hello World"), PAL_T("Invalid element #1 value")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementAt(instance, 1, &name, &value, &type, &flags), PAL_T("Unable to get element 2")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(name, PAL_T("id"), PAL_T("Invalid element #2 name")))
    {
        goto cleanup;
    }
    if (!NitsCompare(type, MI_STRING, PAL_T("Invalid element #2 type")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(value.string, PAL_T("1"), PAL_T("Invalid element #2 value")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementAt(instance, 2, &name, &value, &type, &flags), PAL_T("Unable to get element 3")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(name, PAL_T("Location"), PAL_T("Invalid element #3 name")))
    {
        goto cleanup;
    }

    cleanup:
    if (batch)
    {
        Batch_Delete(batch);
    }
}
NitsEndTest

NitsTestWithSetup(TestFaultResponse, TestParserSetup)
{
    WSMAN_WSHeader wsheaders;
    XML xml;
    WSMAN_WSFault fault;
    MI_Result resultCode;
    WSBUF_FAULT_CODE faultCode;

    // Sample FaultResponse from command "omicli ci -u u -p p --auth Basic --hostname localhost test/cpp { MSFT_Person Key 8 monster }"

    XML_Char data[] = PAL_T("<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://www.w3.org/2003/05/soap-envelope\" ")
        PAL_T("xmlns:wsa=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" ")
        PAL_T("xmlns:wsen=\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\" ")
        PAL_T("xmlns:e=\"http://schemas.xmlsoap.org/ws/2004/08/eventing\" ")
        PAL_T("xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ")
        PAL_T("xmlns:wsmb=\"http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd\" ") 
        PAL_T("xmlns:wsman=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" ")
        PAL_T("xmlns:wxf=\"http://schemas.xmlsoap.org/ws/2004/09/transfer\" ")
        PAL_T("xmlns:cim=\"http://schemas.dmtf.org/wbem/wscim/1/common\" ")
        PAL_T("xmlns:msftwinrm=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\" ")
        PAL_T("xmlns:wsmid=\"http://schemas.dmtf.org/wbem/wsman/identity/1/wsmanidentity.xsd\">\n")
        PAL_T("<SOAP-ENV:Header>\n")
        PAL_T("<wsa:To>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:To>\n")
        PAL_T("<wsa:Action>http://schemas.dmtf.org/wbem/wsman/1/wsman/fault</wsa:Action>\n")
        PAL_T("<wsa:MessageID>uuid:B1C29099-3649-0005-0000-000000010000</wsa:MessageID>\n")
        PAL_T("<wsa:RelatesTo>uuid:B1C28C85-3649-0005-0000-000000010000</wsa:RelatesTo>\n")
        PAL_T("</SOAP-ENV:Header>\n\n")
        PAL_T("<SOAP-ENV:Body>\n")
        PAL_T("<SOAP-ENV:Fault>\n<SOAP-ENV:Code>\n<SOAP-ENV:Value>SOAP-ENV:Receiver</SOAP-ENV:Value>\n")
        PAL_T("<SOAP-ENV:Subcode>\n<SOAP-ENV:Value>wsman:InternalError</SOAP-ENV:Value>\n</SOAP-ENV:Subcode>\n</SOAP-ENV:Code>\n")
        PAL_T("<SOAP-ENV:Reason>\n<SOAP-ENV:Text xml:lang=\"en-US\">The specified property does not exist.</SOAP-ENV:Text>\n</SOAP-ENV:Reason>\n")
        PAL_T("<SOAP-ENV:Detail>\n<p:OMI_Error wsmb:IsCIM_Error=\"true\" ")
        PAL_T("xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ")
        PAL_T("xmlns:wsmb=\"http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd\" ") 
        PAL_T("xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/OMI_Error\" ")
        PAL_T("xmlns:cim=\"http://schemas.dmtf.org/wbem/wscim/1/common\"><p:ErrorType xsi:nil=\"true\"/>\n")
        PAL_T("<p:OtherErrorType xsi:nil=\"true\"/>\n<p:OwningEntity xsi:type=\"cim:cimString\">OMI:CIMOM</p:OwningEntity>\n")
        PAL_T("<p:MessageID xsi:type=\"cim:cimString\">OMI:MI_Result:12</p:MessageID>\n")
        PAL_T("<p:Message xsi:type=\"cim:cimString\">The specified property does not exist.</p:Message>\n")
        PAL_T("<p:PerceivedSeverity xsi:type=\"cim:cimUnsignedInt\">7</p:PerceivedSeverity>\n")
        PAL_T("<p:ProbableCause xsi:type=\"cim:cimUnsignedInt\">0</p:ProbableCause>\n")
        PAL_T("<p:ProbableCauseDescription xsi:type=\"cim:cimString\">Unknown</p:ProbableCauseDescription>\n")
        PAL_T("<p:RecommendedActions xsi:nil=\"true\"/>\n")
        PAL_T("<p:ErrorSource xsi:nil=\"true\"/>\n<p:ErrorSourceFormat xsi:nil=\"true\"/>\n<p:OtherErrorSourceFormat xsi:nil=\"true\"/>\n")
        PAL_T("<p:CIMStatusCode xsi:type=\"cim:cimUnsignedInt\">12</p:CIMStatusCode>\n")
        PAL_T("<p:CIMStatusCodeDescription xsi:nil=\"true\"/>\n<p:OMI_Code xsi:type=\"cim:cimUnsignedInt\">12</p:OMI_Code>\n")
        PAL_T("<p:OMI_Category xsi:type=\"cim:cimUnsignedInt\">10</p:OMI_Category>\n")
        PAL_T("<p:OMI_Type xsi:type=\"cim:cimString\">MI</p:OMI_Type>\n")
        PAL_T("<p:OMI_ErrorMessage xsi:type=\"cim:cimString\">The specified property does not exist.</p:OMI_ErrorMessage>\n</p:OMI_Error>\n")
        PAL_T("</SOAP-ENV:Detail>\n</SOAP-ENV:Fault>\n</SOAP-ENV:Body>\n</SOAP-ENV:Envelope>\n");

    memset(&wsheaders, 0, sizeof(wsheaders));

    XML_Init(&xml);

    XML_RegisterNameSpace(&xml, 's',
                          ZT("http://www.w3.org/2003/05/soap-envelope"));
    
    XML_RegisterNameSpace(&xml, 'a',
                          ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing"));

    XML_RegisterNameSpace(&xml, 'w',
                          ZT("http://schemas.xmlsoap.org/ws/2005/06/management"));

    XML_SetText(&xml, data);

    if (!NitsCompare(MI_RESULT_OK, WS_ParseSoapEnvelope(&xml), PAL_T("Parse soap envelope error")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, WS_ParseWSHeader(&xml, &wsheaders, USERAGENT_UNKNOWN), PAL_T("Parse header error")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_TRUE, wsheaders.foundAction, PAL_T("No action in header")))
    {
        goto cleanup;
    }
    if (!NitsCompare(wsheaders.rqtAction, WSMANTAG_ACTION_WSMAN_FAULT, PAL_T("Action is not Get Response")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, WS_ParseFaultBody(&xml, &fault), PAL_T("Unable to retrieve fault")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.code, PAL_T("SOAP-ENV:Receiver"), PAL_T("Mismatch of fault code")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.subcode, PAL_T("wsman:InternalError"), PAL_T("Mismatch of fault subcode")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.reason, PAL_T("The specified property does not exist."), PAL_T("Mismatch of fault subcode")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, FindErrorCode(&faultCode, &resultCode, wsheaders.rqtAction, "SOAP-ENV:Receiver",
                                                 "wsman:InternalError", fault.reason), PAL_T("Cannot determine errorCode")))
    {
        goto cleanup;
    }
    if (!NitsCompare(0, faultCode, PAL_T("Wrong fault code")))        // WSBUF_FAULT_INTERNAL_ERROR
    {
        goto cleanup;
    }
    if (!NitsCompare(12, resultCode, PAL_T("Wrong result code")))     // MI_RESULT_NO_SUCH_PROPERTY
    {
        goto cleanup;
    }
    

    cleanup:
    ;
}
NitsEndTest

/* 

"<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:wsa=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" xmlns:wsen=\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\" xmlns:e=\"http://schemas.xmlsoap.org/ws/2004/08/eventing\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:wsmb=\"http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd\" xmlns:wsman=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" xmlns:wxf=\"http://schemas.xmlsoap.org/ws/2004/09/transfer\" xmlns:cim=\"http://schemas.dmtf.org/wbem/wscim/1/common\" xmlns:msftwinrm=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\" xmlns:wsmid=\"http://schemas.dmtf.org/wbem/wsman/identity/1/wsmanidentity.xsd\">\n<SOAP-ENV:Header>\n<wsa:To>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:To>\n<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/CreateResponse</wsa:Action>\n<wsa:MessageID>uuid:B1C29099-3649-0005-0000-000000020000</wsa:MessageID>\n<wsa:RelatesTo>uuid:20EC5EEA-364A-0005-0000-000000010000</wsa:RelatesTo>\n</SOAP-ENV:Header><SOAP-ENV:Body><wxf:ResourceCreated>\n<wsa:Address>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:Address>\n<wsa:ReferenceParameters>\n<wsman:ResourceURI>http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/MSFT_Person</wsman:ResourceURI>\n<wsman:SelectorSet>\n<wsman:Selector Name=\"Key\">8</wsman:Selector></wsman:SelectorSet>\n</wsa:ReferenceParameters>\n</wxf:ResourceCreated>\n</SOAP-ENV:Body></SOAP-ENV:Envelope>"

*/
