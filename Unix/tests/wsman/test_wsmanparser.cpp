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
    XML *xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    MI_Uint32 count = 0;
    MI_Value value;
    MI_Type type;
    const MI_Char *name;
    MI_Uint32 flags;
    MI_Uint32 i;

    /* Sample GetResponse from https://msdn.microsoft.com/en-us/library/cc251505.aspx */
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

    WSMAN_WSHeader wsheaders;
    memset(&wsheaders, 0, sizeof(wsheaders));

    PostInstanceMsg *msg = PostInstanceMsg_New(0);
    Instance_NewDynamic(&msg->instance, MI_T("data"), MI_FLAG_CLASS, msg->base.batch);

    printf("0");

    XML_Init(xml);

    XML_RegisterNameSpace(xml, 's',
                          ZT("http://www.w3.org/2003/05/soap-envelope"));
    
    XML_RegisterNameSpace(xml, 'a',
                          ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing"));

    XML_RegisterNameSpace(xml, 'w',
                          ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd"));


    XML_SetText(xml, data);

    printf("1\n");

    UT_ASSERT(WS_ParseSoapEnvelope(xml) == 0);
    UT_ASSERT(xml->status == 0);

    UT_ASSERT(WS_ParseWSHeader(xml, &wsheaders, USERAGENT_UNKNOWN) == 0);
    UT_ASSERT(xml->status == 0);

    UT_ASSERT(wsheaders.foundAction);
    UT_ASSERT(wsheaders.rqtAction == WSMANTAG_ACTION_GET_RESPONSE);
    UT_ASSERT(Tcscmp(wsheaders.rqtMessageID, PAL_T("uuid:2DAB718A-0103-4E0A-AB17-06C8A5530D2B")) == 0);
    UT_ASSERT(Tcscmp(wsheaders.rspRelatesTo, PAL_T("uuid:5E6FD101-710A-4EEA-A50D-70C0BF863AA3")) == 0);

    UT_ASSERT(WS_ParseGetResponseBody(xml, msg->base.batch, &msg->instance) == 0);
    UT_ASSERT(xml->status == 0);

    printf("2\n");

    UT_ASSERT(__MI_Instance_GetElementCount(msg->instance, &count) == 0);
    UT_ASSERT(count == 3);    
    
    for (i=0; i<count; i++)
    {
        printf("%d\n", i+3);

        UT_ASSERT(__MI_Instance_GetElementAt(msg->instance, i, &name, &value, &type, &flags) == 0);
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

    printf("6\n");

    PAL_Free(xml);
    PostInstanceMsg_Release(msg);
}
NitsEndTest

NitsTestWithSetup(TestGetResponse2, TestParserSetup)
{
    XML *xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    MI_Uint32 count = 0;
    MI_Value value;
    MI_Type type;
    const MI_Char *name;
    MI_Uint32 flags;
    MI_Uint32 i;

    /* Sample GetResponse from https://msdn.microsoft.com/en-us/library/cc251505.aspx, but with added newline chars */
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

    WSMAN_WSHeader wsheaders;
    memset(&wsheaders, 0, sizeof(wsheaders));

    PostInstanceMsg *msg = PostInstanceMsg_New(0);
    Instance_NewDynamic(&msg->instance, MI_T("data"), MI_FLAG_CLASS, msg->base.batch);

    XML_Init(xml);

    XML_RegisterNameSpace(xml, 's',
                          ZT("http://www.w3.org/2003/05/soap-envelope"));
    
    XML_RegisterNameSpace(xml, 'a',
                          ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing"));

    XML_RegisterNameSpace(xml, 'w',
                          ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd"));


    XML_SetText(xml, data);

    UT_ASSERT(WS_ParseSoapEnvelope(xml) == 0);
    UT_ASSERT(xml->status == 0);

    UT_ASSERT(WS_ParseWSHeader(xml, &wsheaders, USERAGENT_UNKNOWN) == 0);
    UT_ASSERT(xml->status == 0);

    UT_ASSERT(wsheaders.foundAction);
    UT_ASSERT(wsheaders.rqtAction == WSMANTAG_ACTION_GET_RESPONSE);
    UT_ASSERT(Tcscmp(wsheaders.rqtMessageID, PAL_T("uuid:2DAB718A-0103-4E0A-AB17-06C8A5530D2B")) == 0);
    UT_ASSERT(Tcscmp(wsheaders.rspRelatesTo, PAL_T("uuid:5E6FD101-710A-4EEA-A50D-70C0BF863AA3")) == 0);

    UT_ASSERT(WS_ParseGetResponseBody(xml, msg->base.batch, &msg->instance) == 0);
    UT_ASSERT(xml->status == 0);

    UT_ASSERT(__MI_Instance_GetElementCount(msg->instance, &count) == 0);
    UT_ASSERT(count == 3);    
    
    for (i=0; i<count; i++)
    {
        UT_ASSERT(__MI_Instance_GetElementAt(msg->instance, i, &name, &value, &type, &flags) == 0);
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

    PAL_Free(xml);
    PostInstanceMsg_Release(msg);
}
NitsEndTest
