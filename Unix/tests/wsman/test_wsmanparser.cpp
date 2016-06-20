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
//    PostInstanceMsg *msg = NULL;

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
                          ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd"));

    XML_SetText(&xml, data);

//    if (NitsAssert((msg = PostInstanceMsg_New(0)), PAL_T("Unable to post new instance")))
//    {
//        goto cleanup;
//    }
//    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&instance, MI_T("test"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
//    {
//        goto cleanup;
//    }

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

    if (NitsAssert((batch = Batch_New(BATCH_MAX_PAGES)), PAL_T("Unable to create new batch")))
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
    if (!NitsCompare((flags & MI_FLAG_NULL), MI_FLAG_NULL, PAL_T("Invalid element #3 flags")))
    {
        goto cleanup;
    }

    cleanup:
    if (batch)
    {
        Batch_Delete(batch);
    }
//    if (msg)
//    {
//        PostInstanceMsg_Release(msg);
//    }
}
NitsEndTest

/*
NitsTestWithSetup(TestGetResponse2, TestParserSetup)
{
    MI_Uint32 count = 0;
    MI_Value value;
    MI_Type type;
    const MI_Char *name;
    MI_Uint32 flags;
    MI_Uint32 i;
    Batch *batch = Batch_New(INFINITE);
    WSMAN_WSHeader wsheaders;
    MI_Instance *instance = NULL;
    XML xml;

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
                          ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd"));

    XML_SetText(&xml, data);

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&instance, MI_T("test"), MI_FLAG_CLASS, batch) == 0);

    if (!NitsCompare(MI_RESULT_OK, WS_ParseSoapEnvelope(&xml) == 0);
    if (!NitsCompare(MI_RESULT_OK, xml.status == 0);

    if (!NitsCompare(MI_RESULT_OK, WS_ParseWSHeader(&xml, &wsheaders, USERAGENT_UNKNOWN) == 0);
    if (!NitsCompare(MI_RESULT_OK, xml.status == 0);

    if (!NitsCompare(MI_RESULT_OK, wsheaders.foundAction);
    if (!NitsCompare(MI_RESULT_OK, wsheaders.rqtAction == WSMANTAG_ACTION_GET_RESPONSE);
    if (!NitsCompare(MI_RESULT_OK, Tcscmp(wsheaders.rqtMessageID, PAL_T("uuid:2DAB718A-0103-4E0A-AB17-06C8A5530D2B")) == 0);
    if (!NitsCompare(MI_RESULT_OK, Tcscmp(wsheaders.rspRelatesTo, PAL_T("uuid:5E6FD101-710A-4EEA-A50D-70C0BF863AA3")) == 0);

    if (!NitsCompare(MI_RESULT_OK, WS_ParseInstanceBody(&xml, batch, &instance) == 0);
    if (!NitsCompare(MI_RESULT_OK, xml.status == 0);

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElementCount(instance, &count) == 0);
    if (!NitsCompare(MI_RESULT_OK, count == 3);    
    
    for (i=0; i<count; i++)
    {
        UT_ASSERT(__MI_Instance_GetElementAt(instance, i, &name, &value, &type, &flags) == 0);
        switch(i)
        {
          case 0:
            UT_ASSERT(Tcscmp(name, PAL_T("Data1")) == 0);
            UT_ASSERT(type == MI_STRING);
            UT_ASSERT(Tcscmp((MI_String)value.string, PAL_T("Hello World")) == 0);
            break;
          case 1:
            UT_ASSERT(Tcscmp(name, PAL_T("id")) == 0);
            UT_ASSERT(type == MI_STRING);
            UT_ASSERT(Tcscmp((MI_String)value.string, PAL_T("1")) == 0);
            break;
          case 2:
            UT_ASSERT((flags & MI_FLAG_NULL) == MI_FLAG_NULL);
            break;
        }
    }

    if (instance)
    {
        __MI_Instance_Delete(instance);
    }
    if (batch)
    {
        Batch_Delete(batch);
    }
}
NitsEndTest

*/
