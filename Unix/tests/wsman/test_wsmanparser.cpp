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
#include <wsman/wsmanerrorhandling.h>


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
    if (!NitsCompare(MI_RESULT_OK, WS_ParseInstanceBody(&xml, batch, &instance, 0), PAL_T("Unable to retrieve instance")))
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
    if (!NitsCompare(MI_RESULT_OK, WS_ParseInstanceBody(&xml, batch, &instance, 0), PAL_T("Unable to retrieve instance")))
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
    Error_Types errorType;
    MI_Char *errorTypeStr;

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

    XML_RegisterNameSpace(&xml, 'b',
                          ZT("http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd"));

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
    if (!NitsCompare(wsheaders.rqtAction, WSMANTAG_ACTION_FAULT_WSMAN, PAL_T("Action is not Fault Response")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, WS_ParseFaultBody(&xml, &fault), PAL_T("Unable to retrieve fault")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.code, PAL_T("http://www.w3.org/2003/05/soap-envelope:Receiver"), 
                           PAL_T("Mismatch of fault code")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.subcode, 
                           PAL_T("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd:InternalError"), 
                           PAL_T("Mismatch of fault subcode")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.reason, PAL_T("The specified property does not exist."), PAL_T("Mismatch of fault reason")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.detail, NULL, PAL_T("Mismatch of fault detail")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_RESULT_OK, GetWsmanErrorFromSoapFault(fault.code, fault.subcode, fault.detail, &errorType, &errorTypeStr),
                     PAL_T("Cannot determine errorCode")))
    {
        goto cleanup;
    }
    if (!NitsCompare(ERROR_INTERNAL_ERROR, errorType, PAL_T("Wrong error type")))
    {
        goto cleanup;
    }

    if (!NitsCompare(12, fault.mi_result, PAL_T("Wrong result code")))     // MI_RESULT_NO_SUCH_PROPERTY
    {
        goto cleanup;
    }


    cleanup:
    ;
}
NitsEndTest

NitsTestWithSetup(TestCreateResponse, TestParserSetup)
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
    MI_Char *epr;

    // Sample CreateResponse from command "omicli ci -u u -p p --auth Basic --hostname localhost test/cpp { MSFT_Person Key 8 Species monster }"

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
        PAL_T("<SOAP-ENV:Header>\n<wsa:To>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:To>\n")
        PAL_T("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/CreateResponse</wsa:Action>\n")
        PAL_T("<wsa:MessageID>uuid:B1C29099-3649-0005-0000-000000020000</wsa:MessageID>\n")
        PAL_T("<wsa:RelatesTo>uuid:20EC5EEA-364A-0005-0000-000000010000</wsa:RelatesTo>\n")
        PAL_T("</SOAP-ENV:Header>")
        PAL_T("<SOAP-ENV:Body>")
        PAL_T("<wxf:ResourceCreated>\n<wsa:Address>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:Address>\n")
        PAL_T("<wsa:ReferenceParameters>\n<wsman:ResourceURI>http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/MSFT_Person</wsman:ResourceURI>\n")
        PAL_T("<wsman:SelectorSet>\n<wsman:Selector Name=\"Key\">8</wsman:Selector></wsman:SelectorSet>\n</wsa:ReferenceParameters>\n")
        PAL_T("</wxf:ResourceCreated>\n</SOAP-ENV:Body></SOAP-ENV:Envelope>");

    memset(&wsheaders, 0, sizeof(wsheaders));

    XML_Init(&xml);

    XML_RegisterNameSpace(&xml, 's',
                          ZT("http://www.w3.org/2003/05/soap-envelope"));
    
    XML_RegisterNameSpace(&xml, 'a',
                          ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing"));

    XML_RegisterNameSpace(&xml, 'w',
                          ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd"));

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
    if (!NitsCompare(wsheaders.rqtAction, WSMANTAG_ACTION_CREATE_RESPONSE, PAL_T("Action is not Create Response")))
    {
        goto cleanup;
    }

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Unable to create new batch")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_RESULT_OK, WS_ParseCreateResponseBody(&xml, batch, &epr, &instance, MI_FALSE), PAL_T("Unable to retrieve reference")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_RESULT_OK, xml.status, PAL_T("Retrieve instance returned error xml status")))
    {
        goto cleanup;
    }

    if (!NitsCompareString(epr, PAL_T("http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous"), PAL_T("Invalid end-point reference")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementCount(instance, &count), PAL_T("Unable to get element count")))
    {
        goto cleanup;
    }
    if (!NitsCompare(count, 1, PAL_T("Element count error")))
    {
        goto cleanup;
    }
    
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementAt(instance, 0, &name, &value, &type, &flags), PAL_T("Unable to get element 1")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(name, PAL_T("Key"), PAL_T("Invalid element #1 name")))
    {
        goto cleanup;
    }
    if (!NitsCompare(type, MI_STRING, PAL_T("Invalid element #1 type")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(value.string, PAL_T("8"), PAL_T("Invalid element #1 value")))
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

NitsTestWithSetup(TestInvokeResponse, TestParserSetup)
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

    // Sample CreateResponse from command "omicli iv -u u -p p --auth Basic --hostname localhost test/cpp { X_SmallNumber } SpellNumber { num 123 }

    XML_Char data[] = PAL_T("<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://www.w3.org/2003/05/soap-envelope\" ")
        PAL_T("xmlns:wsa=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" ")
        PAL_T("xmlns:wsen=\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\" ")
        PAL_T("xmlns:e=\"http://schemas.xmlsoap.org/ws/2004/08/eventing\" ")
        PAL_T("xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ")
        PAL_T("xmlns:wsmb=\"http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd\"") 
        PAL_T("xmlns:wsman=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" ")
        PAL_T("xmlns:wxf=\"http://schemas.xmlsoap.org/ws/2004/09/transfer\" ")
        PAL_T("xmlns:cim=\"http://schemas.dmtf.org/wbem/wscim/1/common\" ")
        PAL_T("xmlns:msftwinrm=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\" ")
        PAL_T("xmlns:wsmid=\"http://schemas.dmtf.org/wbem/wsman/identity/1/wsmanidentity.xsd\">\n")
        PAL_T("<SOAP-ENV:Header>\n<wsa:To>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:To>\n")
        PAL_T("<wsa:Action>http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/X_SmallNumber/SpellNumber</wsa:Action>\n")
        PAL_T("<wsa:MessageID>uuid:2F28B906-3672-0005-0000-000000050000</wsa:MessageID>\n")
        PAL_T("<wsa:RelatesTo>uuid:CE7C6EB2-3672-0005-0000-000000010000</wsa:RelatesTo>\n")
        PAL_T("</SOAP-ENV:Header><SOAP-ENV:Body><p:X_SmallNumber_OUTPUT xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/X_SmallNumber\"\n>\n")
        PAL_T("<p:ReturnValue>one hundred twenty three</p:ReturnValue>\n")
        PAL_T("</p:X_SmallNumber_OUTPUT>\n</SOAP-ENV:Body></SOAP-ENV:Envelope>");

    memset(&wsheaders, 0, sizeof(wsheaders));

    XML_Init(&xml);

    XML_RegisterNameSpace(&xml, 's',
                          ZT("http://www.w3.org/2003/05/soap-envelope"));
    
    XML_RegisterNameSpace(&xml, 'a',
                          ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing"));

    XML_RegisterNameSpace(&xml, 'w',
                          ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd"));

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
    if (!NitsCompare(wsheaders.rqtAction, 0, PAL_T("Action is not an invoke Response")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(wsheaders.rqtClassname, PAL_T("X_SmallNumber"), PAL_T("Incorrect class name")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(wsheaders.rqtMethod, PAL_T("SpellNumber"), PAL_T("Incorrect method")))
    {
        goto cleanup;
    }

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Unable to create new batch")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_RESULT_OK, WS_ParseInstanceBody(&xml, batch, &instance, 0), PAL_T("Unable to retrieve instance")))
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
    if (!NitsCompare(count, 1, PAL_T("Element count error")))
    {
        goto cleanup;
    }
    
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementAt(instance, 0, &name, &value, &type, &flags), PAL_T("Unable to get element 1")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(name, PAL_T("ReturnValue"), PAL_T("Invalid element #1 name")))
    {
        goto cleanup;
    }
    if (!NitsCompare(type, MI_STRING, PAL_T("Invalid element #1 type")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(value.string, PAL_T("one hundred twenty three"), PAL_T("Invalid element #1 value")))
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

NitsTestWithSetup(TestPutResponse, TestParserSetup)
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



    // Sample CreateResponse from command "omicli mi -u u -p p --auth Basic --hostname localhost root/cimv2 
    //                                            { MSFT_Person Key 1234 First "George" Last "Patton" }
    XML_Char data[] = PAL_T("<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://www.w3.org/2003/05/soap-envelope\" ")
        PAL_T("xmlns:wsa=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" ")
        PAL_T("xmlns:wsen=\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\" ")
        PAL_T("xmlns:e=\"http://schemas.xmlsoap.org/ws/2004/08/eventing\" ")
        PAL_T("xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ")
        PAL_T("xmlns:wsmb=\"http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd\"") 
        PAL_T("xmlns:wsman=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" ")
        PAL_T("xmlns:wxf=\"http://schemas.xmlsoap.org/ws/2004/09/transfer\" ")
        PAL_T("xmlns:cim=\"http://schemas.dmtf.org/wbem/wscim/1/common\" ")
        PAL_T("xmlns:msftwinrm=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\" ")
        PAL_T("xmlns:wsmid=\"http://schemas.dmtf.org/wbem/wsman/identity/1/wsmanidentity.xsd\">\n")
        PAL_T("<SOAP-ENV:Header>\n<wsa:To>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:To>\n")
        PAL_T("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/transfer/PutResponse</wsa:Action>\n")
        PAL_T("<wsa:MessageID>uuid:9EDB2C85-3685-0005-0000-000000030000</wsa:MessageID>\n")
        PAL_T("<wsa:RelatesTo>uuid:A62FCF89-3685-0005-0000-000000010000</wsa:RelatesTo>\n</SOAP-ENV:Header>")
        PAL_T("<SOAP-ENV:Body>")
        PAL_T("<p:MSFT_Person xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/MSFT_Person\"\n>\n")
        PAL_T("<p:Key>1234</p:Key>\n")
        PAL_T("<p:Species xsi:nil=\"true\"/>\n")
        PAL_T("<p:Last>Patton</p:Last>\n<p:First>George</p:First>\n")
        PAL_T("<p:ExpensiveProperty xsi:nil=\"true\"/>\n")
        PAL_T("</p:MSFT_Person>\n</SOAP-ENV:Body></SOAP-ENV:Envelope>");

    memset(&wsheaders, 0, sizeof(wsheaders));

    XML_Init(&xml);

    XML_RegisterNameSpace(&xml, 's',
                          ZT("http://www.w3.org/2003/05/soap-envelope"));
    
    XML_RegisterNameSpace(&xml, 'a',
                          ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing"));

    XML_RegisterNameSpace(&xml, 'w',
                          ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd"));

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
    if (!NitsCompare(wsheaders.rqtAction, WSMANTAG_ACTION_PUT_RESPONSE, PAL_T("Action is not a Put Response")))
    {
        goto cleanup;
    }

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Unable to create new batch")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_RESULT_OK, WS_ParseInstanceBody(&xml, batch, &instance, 0), PAL_T("Unable to retrieve instance")))
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
    if (!NitsCompare(count, 5, PAL_T("Element count error")))
    {
        goto cleanup;
    }
    
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementAt(instance, 0, &name, &value, &type, &flags), PAL_T("Unable to get element 1")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(name, PAL_T("Key"), PAL_T("Invalid element #1 name")))
    {
        goto cleanup;
    }
    if (!NitsCompare(type, MI_STRING, PAL_T("Invalid element #1 type")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(value.string, PAL_T("1234"), PAL_T("Invalid element #1 value")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementAt(instance, 2, &name, &value, &type, &flags), PAL_T("Unable to get element 3")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(name, PAL_T("Last"), PAL_T("Invalid element #3 name")))
    {
        goto cleanup;
    }
    if (!NitsCompare(type, MI_STRING, PAL_T("Invalid element #3 type")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(value.string, PAL_T("Patton"), PAL_T("Invalid element #3 value")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementAt(instance, 3, &name, &value, &type, &flags), PAL_T("Unable to get element 4")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(name, PAL_T("First"), PAL_T("Invalid element #4 name")))
    {
        goto cleanup;
    }
    if (!NitsCompare(type, MI_STRING, PAL_T("Invalid element #4 type")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(value.string, PAL_T("George"), PAL_T("Invalid element #4 value")))
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

NitsTestWithSetup(TestEnumerateResponse, TestParserSetup)
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
    const MI_Char *context = NULL;
    MI_Boolean endOfSequence = MI_FALSE;
    MI_Boolean getNextInstance = MI_FALSE;
    XML_Elem e;

    // Sample EnumerateResponse from command "omicli ei -u u -p p --auth Basic --hostname localhost root/cimv2 X_SmallNumber 

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
        PAL_T("xmlns:wsmid=\"http://schemas.dmtf.org/wbem/wsman/identity/1/wsmanidentity.xsd\">")
        PAL_T("<SOAP-ENV:Header>")
        PAL_T("<wsa:To>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:To>")
        PAL_T("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/enumeration/EnumerateResponse</wsa:Action>")
        PAL_T("<wsa:MessageID>uuid:E0469555-3BF0-0005-0000-000000010000</wsa:MessageID>")
        PAL_T("<wsa:RelatesTo>uuid:E046918C-3BF0-0005-0000-000000010000</wsa:RelatesTo>")
        PAL_T("</SOAP-ENV:Header><SOAP-ENV:Body>")
        PAL_T("<wsen:EnumerateResponse><wsen:EnumerationContext>1164378112</wsen:EnumerationContext>")
        PAL_T("<wsman:Items>")
        PAL_T("<p:X_SmallNumber xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/X_SmallNumber\">")
        PAL_T("<p:Description xsi:nil=\"true\"/>")
        PAL_T("<p:Number>0</p:Number>")
        PAL_T("<p:SpelledNumber>zero</p:SpelledNumber>")
        PAL_T("</p:X_SmallNumber></wsman:Items></wsen:EnumerateResponse></SOAP-ENV:Body></SOAP-ENV:Envelope>");

    memset(&wsheaders, 0, sizeof(wsheaders));

    XML_Init(&xml);

    XML_RegisterNameSpace(&xml, 's',
                          ZT("http://www.w3.org/2003/05/soap-envelope"));
    
    XML_RegisterNameSpace(&xml, 'a',
                          ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing"));

    XML_RegisterNameSpace(&xml, 'w',
                          ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd"));

    XML_RegisterNameSpace(&xml, 'n',
                          ZT("http://schemas.xmlsoap.org/ws/2004/09/enumeration"));

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
    if (!NitsCompare(wsheaders.rqtAction, WSMANTAG_ACTION_ENUMERATE_RESPONSE, 
                     PAL_T("Action is not an Enumeration Response")))
    {
        goto cleanup;
    }

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Unable to create new batch")))
    {
        goto cleanup;
    }
    if (!NitsCompare(0, WS_ParseEnumerateResponse(&xml, &context, &endOfSequence, batch, &instance, MI_TRUE, &getNextInstance, &e), 
                     PAL_T("Unable to retrieve instance")))
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
    
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementAt(instance, 2, &name, &value, &type, &flags), PAL_T("Unable to get element 3")))
    {
        goto cleanup;
    }

    if (!NitsCompareString(name, PAL_T("SpelledNumber"), PAL_T("Invalid element #2 name")))
    {
        goto cleanup;
    }
    if (!NitsCompare(type, MI_STRING, PAL_T("Invalid element #2 type")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(value.string, PAL_T("Zero"), PAL_T("Invalid element #2 value")))
    {
        goto cleanup;
    }

    if (!NitsCompareString(context, PAL_T("1164378112"), PAL_T("Invalid context")))
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

NitsTestWithSetup(TestPullResponse, TestParserSetup)
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
    const MI_Char *context = NULL;
    MI_Boolean endOfSequence = MI_FALSE;
    MI_Boolean getNextInstance = MI_FALSE;
    XML_Elem e;

    // Sample PullResponse from command "omicli ei -u u -p p --auth Basic --hostname localhost root/cimv2 X_SmallNumber 

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
        PAL_T("xmlns:wsmid=\"http://schemas.dmtf.org/wbem/wsman/identity/1/wsmanidentity.xsd\">")
        PAL_T("<SOAP-ENV:Header>")
        PAL_T("<wsa:To>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:To>")
        PAL_T("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/enumeration/PullResponse</wsa:Action>")
        PAL_T("<wsa:MessageID>uuid:E0469555-3BF0-0005-0000-000003E80000</wsa:MessageID>")
        PAL_T("<wsa:RelatesTo>uuid:E046918C-3BF0-0005-0000-000003E80000</wsa:RelatesTo>")
        PAL_T("</SOAP-ENV:Header><SOAP-ENV:Body>")
        PAL_T("<wsen:PullResponse><wsen:EnumerationContext>1164378112</wsen:EnumerationContext>")
        PAL_T("<wsen:Items>")
        PAL_T("<p:X_SmallNumber xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/X_SmallNumber\">")
        PAL_T("<p:Description xsi:nil=\"true\"/>")
        PAL_T("<p:Number>999</p:Number>")
        PAL_T("<p:SpelledNumber>nine hundred ninety nine</p:SpelledNumber>")
        PAL_T("</p:X_SmallNumber>")
        PAL_T("</wsen:Items><wsen:EndOfSequence/></wsen:PullResponse></SOAP-ENV:Body></SOAP-ENV:Envelope>");



    memset(&wsheaders, 0, sizeof(wsheaders));

    XML_Init(&xml);

    XML_RegisterNameSpace(&xml, 's',
                          ZT("http://www.w3.org/2003/05/soap-envelope"));
    
    XML_RegisterNameSpace(&xml, 'a',
                          ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing"));

    XML_RegisterNameSpace(&xml, 'w',
                          ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd"));

    XML_RegisterNameSpace(&xml, 'n',
                          ZT("http://schemas.xmlsoap.org/ws/2004/09/enumeration"));

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
    if (!NitsCompare(wsheaders.rqtAction, WSMANTAG_ACTION_PULL_RESPONSE, 
                     PAL_T("Action is not an Pull Response")))
    {
        goto cleanup;
    }

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Unable to create new batch")))
    {
        goto cleanup;
    }
    if (!NitsCompare(0, WS_ParseEnumerateResponse(&xml, &context, &endOfSequence, batch, &instance, MI_FALSE, &getNextInstance, &e), 
                     PAL_T("Unable to retrieve instance")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_RESULT_OK, xml.status, PAL_T("Retrieve instance returned error xml status")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_FALSE, getNextInstance, PAL_T("Incorrect getNextInstance")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_TRUE, endOfSequence, PAL_T("Incorrect endOfSequence")))
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
    
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementAt(instance, 2, &name, &value, &type, &flags), PAL_T("Unable to get element 3")))
    {
        goto cleanup;
    }

    if (!NitsCompareString(name, PAL_T("SpelledNumber"), PAL_T("Invalid element #2 name")))
    {
        goto cleanup;
    }
    if (!NitsCompare(type, MI_STRING, PAL_T("Invalid element #2 type")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(value.string, PAL_T("nine hundred ninety nine"), PAL_T("Invalid element #2 value")))
    {
        goto cleanup;
    }

    if (!NitsCompareString(context, PAL_T("1164378112"), PAL_T("Invalid context")))
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

NitsTestWithSetup(TestPullResponse2, TestParserSetup)
{
    MI_Uint32 count = 0;
    MI_Value value;
    MI_Type type;
    const MI_Char *name;
    MI_Uint32 flags;
    WSMAN_WSHeader wsheaders;
    XML xml;
    MI_Instance *instance = NULL;
    MI_Instance *instance2 = NULL;
    Batch *batch = NULL;
    const MI_Char *context = NULL;
    MI_Boolean endOfSequence = MI_FALSE;
    MI_Boolean getNextInstance = MI_FALSE;
    XML_Elem e;

    // Sample PullResponse from command "omicli ei -u u -p p --auth Basic --hostname localhost root/cimv2 X_SmallNumber 

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
        PAL_T("xmlns:wsmid=\"http://schemas.dmtf.org/wbem/wsman/identity/1/wsmanidentity.xsd\">")
        PAL_T("<SOAP-ENV:Header>")
        PAL_T("<wsa:To>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:To>")
        PAL_T("<wsa:Action>http://schemas.xmlsoap.org/ws/2004/09/enumeration/PullResponse</wsa:Action>")
        PAL_T("<wsa:MessageID>uuid:E0469555-3BF0-0005-0000-000003E80000</wsa:MessageID>")
        PAL_T("<wsa:RelatesTo>uuid:E046918C-3BF0-0005-0000-000003E80000</wsa:RelatesTo>")
        PAL_T("</SOAP-ENV:Header><SOAP-ENV:Body>")
        PAL_T("<wsen:PullResponse><wsen:EnumerationContext>1164378112</wsen:EnumerationContext>")
        PAL_T("<wsen:Items>")
        PAL_T("<p:X_SmallNumber xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/X_SmallNumber\">")
        PAL_T("<p:Description xsi:nil=\"true\"/>")
        PAL_T("<p:Number>999</p:Number>")
        PAL_T("<p:SpelledNumber>nine hundred ninety nine</p:SpelledNumber>")
        PAL_T("</p:X_SmallNumber>")
        PAL_T("<p:X_SmallNumber xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/X_SmallNumber\">")
        PAL_T("<p:Description xsi:nil=\"true\"/>")
        PAL_T("<p:Number>333</p:Number>")
        PAL_T("<p:SpelledNumber>three hundred thirty three</p:SpelledNumber>")
        PAL_T("</p:X_SmallNumber>")
        PAL_T("</wsen:Items><wsen:EndOfSequence/></wsen:PullResponse></SOAP-ENV:Body></SOAP-ENV:Envelope>");

    memset(&wsheaders, 0, sizeof(wsheaders));

    XML_Init(&xml);

    XML_RegisterNameSpace(&xml, 's',
                          ZT("http://www.w3.org/2003/05/soap-envelope"));
    
    XML_RegisterNameSpace(&xml, 'a',
                          ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing"));

    XML_RegisterNameSpace(&xml, 'w',
                          ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd"));

    XML_RegisterNameSpace(&xml, 'n',
                          ZT("http://schemas.xmlsoap.org/ws/2004/09/enumeration"));

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
    if (!NitsCompare(wsheaders.rqtAction, WSMANTAG_ACTION_PULL_RESPONSE, 
                     PAL_T("Action is not an Pull Response")))
    {
        goto cleanup;
    }

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Unable to create new batch")))
    {
        goto cleanup;
    }
    if (!NitsCompare(0, WS_ParseEnumerateResponse(&xml, &context, &endOfSequence, batch, &instance, MI_FALSE, &getNextInstance, &e), 
                     PAL_T("Unable to retrieve instance")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_RESULT_OK, xml.status, PAL_T("Retrieve instance returned error xml status")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_TRUE, getNextInstance, PAL_T("Incorrect getNextInstance")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_FALSE, endOfSequence, PAL_T("Incorrect endOfSequence")))
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
    
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementAt(instance, 2, &name, &value, &type, &flags), PAL_T("Unable to get element 3")))
    {
        goto cleanup;
    }

    if (!NitsCompareString(name, PAL_T("SpelledNumber"), PAL_T("Invalid element #2 name")))
    {
        goto cleanup;
    }
    if (!NitsCompare(type, MI_STRING, PAL_T("Invalid element #2 type")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(value.string, PAL_T("nine hundred ninety nine"), PAL_T("Invalid element #2 value")))
    {
        goto cleanup;
    }

// now second item

    if (!NitsCompare(0, WS_ParseEnumerateResponse(&xml, &context, &endOfSequence, batch, &instance2, MI_FALSE, &getNextInstance, &e), 
                     PAL_T("Unable to retrieve instance")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_RESULT_OK, xml.status, PAL_T("Retrieve instance returned error xml status")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_FALSE, getNextInstance, PAL_T("Incorrect getNextInstance")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_TRUE, endOfSequence, PAL_T("Incorrect endOfSequence")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementCount(instance2, &count), PAL_T("Unable to get element count")))
    {
        goto cleanup;
    }
    if (!NitsCompare(count, 3, PAL_T("Element count error of instance 2")))
    {
        goto cleanup;
    }
    
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementAt(instance2, 2, &name, &value, &type, &flags), PAL_T("Unable to get element 3")))
    {
        goto cleanup;
    }

    if (!NitsCompareString(name, PAL_T("SpelledNumber"), PAL_T("Invalid element #2 name")))
    {
        goto cleanup;
    }
    if (!NitsCompare(type, MI_STRING, PAL_T("Invalid element #2 type")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(value.string, PAL_T("three hundred thirty three"), PAL_T("Invalid element #2 value")))
    {
        goto cleanup;
    }


    if (!NitsCompareString(context, PAL_T("1164378112"), PAL_T("Invalid context")))
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
NitsTestWithSetup(TestFaultResponse2, TestParserSetup)
{
    WSMAN_WSHeader wsheaders;
    XML xml;
    WSMAN_WSFault fault;
    Error_Types errorType;
    MI_Char *errorTypeStr;

    XML_Char data[] = PAL_T("<s:Envelope xml:lang=\"en-US\" xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" ")
        PAL_T("xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" ")
        PAL_T("xmlns:x=\"http://schemas.xmlsoap.org/ws/2004/09/transfer\" ")
        PAL_T("xmlns:e=\"http://schemas.xmlsoap.org/ws/2004/08/eventing\" ")
        PAL_T("xmlns:n=\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\" ")
        PAL_T("xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" ")
        PAL_T("xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\">")
        PAL_T("<s:Header><a:Action>http://schemas.dmtf.org/wbem/wsman/1/wsman/fault</a:Action>")
        PAL_T("<a:MessageID>uuid:CAF5C605-1941-47D1-A94F-27A70663AC7A</a:MessageID>")
        PAL_T("<p:ActivityId>36C7E17B-0864-0007-E2F2-CB366408D201</p:ActivityId>")
        PAL_T("<a:To>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:To>")
        PAL_T("<a:RelatesTo>uuid:B9F09F70-3C1A-0005-0000-000000070000</a:RelatesTo>")
        PAL_T("</s:Header><s:Body>")
        PAL_T("<s:Fault><s:Code><s:Value>s:Receiver</s:Value><s:Subcode><s:Value>w:InternalError</s:Value></s:Subcode></s:Code>")
        PAL_T("<s:Reason><s:Text xml:lang=\"\"></s:Text></s:Reason>")
        PAL_T("<s:Detail><f:WSManFault xmlns:f=\"http://schemas.microsoft.com/wbem/wsman/1/wsmanfault\" Code=\"2152992672\" Machine=\"10.123.175.205\">")
        PAL_T("<f:Message><f:ProviderFault provider=\"microsoft.powershell\" path=\"C:\\WINDOWS\\system32\\pwrshplugin.dll\">")
        PAL_T("Error with error code -2144108472 occurred while calling method WSManPluginReceiveResult.</f:ProviderFault>")
        PAL_T("</f:Message></f:WSManFault></s:Detail></s:Fault></s:Body></s:Envelope>");

    memset(&wsheaders, 0, sizeof(wsheaders));

    XML_Init(&xml);

    XML_RegisterNameSpace(&xml, 's',
                          ZT("http://www.w3.org/2003/05/soap-envelope"));
    
    XML_RegisterNameSpace(&xml, 'a',
                          ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing"));

    XML_RegisterNameSpace(&xml, 'w',
                          ZT("http://schemas.xmlsoap.org/ws/2005/06/management"));

    XML_RegisterNameSpace(&xml, 'b',
                          ZT("http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd"));

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
    if (!NitsCompare(wsheaders.rqtAction, WSMANTAG_ACTION_FAULT_WSMAN, PAL_T("Action is not Fault Response")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, WS_ParseFaultBody(&xml, &fault), PAL_T("Unable to retrieve fault")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.code, PAL_T("http://www.w3.org/2003/05/soap-envelope:Receiver"), 
                           PAL_T("Mismatch of fault code")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.subcode, 
                           PAL_T("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd:InternalError"), 
                           PAL_T("Mismatch of fault subcode")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.reason, NULL, PAL_T("Mismatch of fault reason")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.detail, PAL_T("Error with error code -2144108472 occurred while calling method WSManPluginReceiveResult."), 
                           PAL_T("Invalid fault detail")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_RESULT_OK, GetWsmanErrorFromSoapFault(fault.code, fault.subcode, fault.detail, &errorType, &errorTypeStr),
                     PAL_T("Cannot determine errorCode")))
    {
        goto cleanup;
    }
    if (!NitsCompare(ERROR_INTERNAL_ERROR, errorType, PAL_T("Wrong error type")))
    {
        goto cleanup;
    }

    if (!NitsCompare(0, fault.mi_result, PAL_T("Wrong result code")))     // MI_RESULT_NO_SUCH_PROPERTY
    {
        goto cleanup;
    }


    cleanup:
    ;
}
NitsEndTest

NitsTestWithSetup(TestInnerMessageFaultResponse, TestParserSetup)
{
    WSMAN_WSHeader wsheaders;
    XML xml;
    WSMAN_WSFault fault;
    Error_Types errorType;
    MI_Char *errorTypeStr;

    XML_Char data[] = PAL_T("<s:Envelope xml:lang=\"en-US\" xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" ")
        PAL_T("xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" ")
        PAL_T("xmlns:x=\"http://schemas.xmlsoap.org/ws/2004/09/transfer\" ")
        PAL_T("xmlns:e=\"http://schemas.xmlsoap.org/ws/2004/08/eventing\" ")
        PAL_T("xmlns:n=\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\" ")
        PAL_T("xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" ")
        PAL_T("xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\">")
        PAL_T("<s:Header><a:Action>http://schemas.xmlsoap.org/ws/2004/08/addressing/fault</a:Action>")
        PAL_T("<a:MessageID>uuid:6B0D1C4A-BCED-4CAE-981B-8DDA57181C9F</a:MessageID>")
        PAL_T("<a:To>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:To>")
        PAL_T("<a:RelatesTo>uuid:48ABB925-4C64-0005-0000-000000010000</a:RelatesTo>")
        PAL_T("</s:Header>")
        PAL_T("<s:Body>")
        PAL_T("<s:Fault>")
        PAL_T("<s:Code>")
        PAL_T("<s:Value>s:Sender</s:Value>")
        PAL_T("<s:Subcode><s:Value>a:DestinationUnreachable</s:Value></s:Subcode>")
        PAL_T("</s:Code>")
        PAL_T("<s:Reason>")
        PAL_T("<s:Text xml:lang=\"en-US\">The WS-Management service cannot process the request. The service cannot find the resource identified by the resource URI and selectors. </s:Text>")
        PAL_T("</s:Reason>")
        PAL_T("<s:Detail>")
        PAL_T("<w:FaultDetail>http://schemas.dmtf.org/wbem/wsman/1/wsman/faultDetail/InvalidResourceURI</w:FaultDetail>")
        PAL_T("<f:WSManFault xmlns:f=\"http://schemas.microsoft.com/wbem/wsman/1/wsmanfault\" Code=\"2150858752\" Machine=\"10.68.240.26\">")
        PAL_T("<f:Message>")
        PAL_T("<f:ProviderFault provider=\"WMI Provider\" path=\"C:\\Windows\\system32\\WsmWmiPl.dll\">")
        PAL_T("<f:WSManFault xmlns:f=\"http://schemas.microsoft.com/wbem/wsman/1/wsmanfault\" Code=\"2150858752\" Machine=\"VMMUR-W12R2-02.SCX.com\">")
        PAL_T("<f:Message>The WS-Management service cannot process the request. The service cannot find the resource identified by the resource URI and selectors. </f:Message>")
        PAL_T("</f:WSManFault>")
        PAL_T("<f:ExtendedError>")
        PAL_T("<p:__ExtendedStatus xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ")
        PAL_T("xmlns:p=\"http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/__ExtendedStatus\" ")
        PAL_T("xmlns:cim=\"http://schemas.dmtf.org/wbem/wscim/1/common\" ")
        PAL_T("xsi:type=\"p:__ExtendedStatus_Type\">")
        PAL_T("<p:Description xsi:nil=\"true\" xsi:type=\"cim:cimString\"/>")
        PAL_T("<p:Operation xsi:type=\"cim:cimString\">GetObject</p:Operation>")
        PAL_T("<p:ParameterInfo xsi:type=\"cim:cimString\">Win32_Process.Handle=&quot;29&quot;</p:ParameterInfo>")
        PAL_T("<p:ProviderName xsi:type=\"cim:cimString\">CIMWin32</p:ProviderName><p:StatusCode xsi:nil=\"true\" xsi:type=\"cim:cimUnsignedInt\"/>")
        PAL_T("</p:__ExtendedStatus></f:ExtendedError></f:ProviderFault>")
        PAL_T("</f:Message></f:WSManFault></s:Detail></s:Fault></s:Body></s:Envelope>");

    memset(&wsheaders, 0, sizeof(wsheaders));

    XML_Init(&xml);

    XML_RegisterNameSpace(&xml, 's',
                          ZT("http://www.w3.org/2003/05/soap-envelope"));
    
    XML_RegisterNameSpace(&xml, 'a',
                          ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing"));

    XML_RegisterNameSpace(&xml, 'w',
                          ZT("http://schemas.xmlsoap.org/ws/2005/06/management"));

    XML_RegisterNameSpace(&xml, 'b',
                          ZT("http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd"));

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
    if (!NitsCompare(wsheaders.rqtAction, WSMANTAG_ACTION_FAULT_ADDRESSING, PAL_T("Action is not Fault ADDRESSING Response")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, WS_ParseFaultBody(&xml, &fault), PAL_T("Unable to retrieve fault")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.code, PAL_T("http://www.w3.org/2003/05/soap-envelope:Sender"), 
                           PAL_T("Mismatch of fault code")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.subcode, 
                           PAL_T("http://schemas.xmlsoap.org/ws/2004/08/addressing:DestinationUnreachable"), 
                           PAL_T("Mismatch of fault subcode")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.reason, PAL_T("The WS-Management service cannot process the request. The service cannot find the resource identified by the resource URI and selectors. "), PAL_T("Mismatch of fault reason")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.detail, PAL_T("CIMWin32"), 
                           PAL_T("Invalid fault detail")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_RESULT_OK, GetWsmanErrorFromSoapFault(fault.code, fault.subcode, fault.detail, &errorType, &errorTypeStr),
                     PAL_T("Cannot determine errorCode")))
    {
        goto cleanup;
    }
    if (!NitsCompare(ERROR_WSMAN_DESTINATION_UNREACHABLE, errorType, PAL_T("Wrong error type")))
    {
        goto cleanup;
    }

    if (!NitsCompare(0, fault.mi_result, PAL_T("Wrong result code")))
    {
        goto cleanup;
    }
    

    cleanup:
    ;
}
NitsEndTest

NitsTestWithSetup(TestTimeoutResponse, TestParserSetup)
{
    WSMAN_WSHeader wsheaders;
    XML xml;
    WSMAN_WSFault fault;
    Error_Types errorType;
    MI_Char *errorTypeStr;
    const Probable_Cause_Data *cause;

    XML_Char data[] = PAL_T("<s:Envelope xml:lang=\"en-US\" xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" ")
        PAL_T("xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" ")
        PAL_T("xmlns:x=\"http://schemas.xmlsoap.org/ws/2004/09/transfer\" ")
        PAL_T("xmlns:e=\"http://schemas.xmlsoap.org/ws/2004/08/eventing\" ")
        PAL_T("xmlns:n=\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\" ")
        PAL_T("xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" ")
        PAL_T("xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\">")
        PAL_T("<s:Header>")
        PAL_T("<a:Action>http://schemas.dmtf.org/wbem/wsman/1/wsman/fault</a:Action>")
        PAL_T("<a:MessageID>uuid:413D86F0-DE73-4264-ABEE-197B21D867F9</a:MessageID>")
        PAL_T("<p:ActivityId>36C7E17B-0864-0004-13E4-CD366408D201</p:ActivityId>")
        PAL_T("<a:To>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:To>")
        PAL_T("<a:RelatesTo>uuid:F894590C-3C1B-0005-0000-000000040000</a:RelatesTo>")
        PAL_T("</s:Header><s:Body><s:Fault>")
        PAL_T("<s:Code><s:Value>s:Receiver</s:Value>")
        PAL_T("<s:Subcode><s:Value>w:TimedOut</s:Value></s:Subcode>")
        PAL_T("</s:Code><s:Reason>")
        PAL_T("<s:Text xml:lang=\"\">The WS-Management service cannot complete the operation within the time specified in OperationTimeout.</s:Text>")
        PAL_T("</s:Reason><s:Detail>")
        PAL_T("<f:WSManFault xmlns:f=\"http://schemas.microsoft.com/wbem/wsman/1/wsmanfault\" Code=\"2150858793\" Machine=\"10.123.175.205\">")
        PAL_T("<f:Message>The WS-Management service cannot complete the operation within the time specified in OperationTimeout.</f:Message>")
        PAL_T("</f:WSManFault></s:Detail></s:Fault></s:Body></s:Envelope>");

    memset(&wsheaders, 0, sizeof(wsheaders));

    XML_Init(&xml);

    XML_RegisterNameSpace(&xml, 's',
                          ZT("http://www.w3.org/2003/05/soap-envelope"));
    
    XML_RegisterNameSpace(&xml, 'a',
                          ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing"));

    XML_RegisterNameSpace(&xml, 'w',
                          ZT("http://schemas.xmlsoap.org/ws/2005/06/management"));

    XML_RegisterNameSpace(&xml, 'b',
                          ZT("http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd"));

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
    if (!NitsCompare(wsheaders.rqtAction, WSMANTAG_ACTION_FAULT_WSMAN, PAL_T("Action is not Fault Response")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, WS_ParseFaultBody(&xml, &fault), PAL_T("Unable to retrieve fault")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.code, PAL_T("http://www.w3.org/2003/05/soap-envelope:Receiver"), 
                           PAL_T("Mismatch of fault code")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.subcode, 
                           PAL_T("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd:TimedOut"), 
                           PAL_T("Mismatch of fault subcode")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.reason, PAL_T("The WS-Management service cannot complete the operation within the time specified in OperationTimeout."), 
                           PAL_T("Mismatch of fault reason")))
    {
        goto cleanup;
    }
    if (!NitsCompareString(fault.detail, PAL_T("The WS-Management service cannot complete the operation within the time specified in OperationTimeout."),
                           PAL_T("Invalid fault detail")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_RESULT_OK, GetWsmanErrorFromSoapFault(fault.code, fault.subcode, fault.detail, &errorType, &errorTypeStr),
                     PAL_T("Cannot determine errorCode")))
    {
        goto cleanup;
    }
    if (!NitsCompare(ERROR_WSMAN_OPERATION_TIMEDOUT, errorType, PAL_T("Wrong error type")))
    {
        goto cleanup;
    }

    if (!NitsCompare(0, fault.mi_result, PAL_T("Wrong result code")))
    {
        goto cleanup;
    }

    cause = GetWsmanCimError(errorType);
    if (NitsCompare(111, cause->probable_cause_id, PAL_T("Incorrect probable cause")))
    {
        goto cleanup;
    }

    cleanup:
    ;
}
NitsEndTest





