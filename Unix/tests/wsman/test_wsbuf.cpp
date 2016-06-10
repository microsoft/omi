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
#include <xml/xml.h>
#include <wsman/wsbuf.h>
#include <base/helpers.h>
#include <base/batch.h>
#include <base/field.h>
#include <pal/format.h>
extern "C" {
#include <miapi/Options.h>
}

#if defined(CONFIG_ENABLE_WCHAR)
typedef std::wstring String;
#else
typedef std::string String;
#endif

using namespace std;

WSBuf   s_buf;

NitsSetup(TestWsbufSetup)
NitsEndSetup

NitsCleanup(TestWsbufSetup)
NitsEndCleanup

#define TEST_STR_CHAR "`';\"\\!@#$%^&*()_+<>"
#define TEST_STR MI_T("`';\"\\!@#$%^&*()_+<>")
#define TEST_STR_ENCODED PAL_T("`&apos;;&quot;\\!@#$%^&amp;*()_+&lt;&gt;")

NitsTestWithSetup(TestXMLStringEncoding, TestWsbufSetup)
{
    String result;    
    
    if(!TEST_ASSERT (MI_RESULT_OK == WSBuf_Init(&s_buf, 10)))
        NitsReturn;

    for ( unsigned int i = 0; i < 100; i++ )
    {
        result += TEST_STR_ENCODED;
        TEST_ASSERT (MI_RESULT_OK == WSBuf_AddString(&s_buf, TEST_STR) );
    }

    Page* p = WSBuf_StealPage(&s_buf);
    TEST_ASSERT(0 != p);

    /* content expected to be 0-terminated */
    String buf_result( (const ZChar*) (p + 1) );
    //cout << buf_result << endl;
    TEST_ASSERT(result == buf_result);

    PAL_Free(p);

    TEST_ASSERT (MI_RESULT_OK == WSBuf_Destroy(&s_buf));    
}
NitsEndTest

NitsTestWithSetup(TestToFromXML, TestWsbufSetup)
{
    String result;
    Page* p = NULL;
    XML * xml = NULL;
    XML_Elem e;
    if(!TEST_ASSERT (MI_RESULT_OK == WSBuf_Init(&s_buf, 10)))
        NitsReturn;

    if(!TEST_ASSERT (MI_RESULT_OK == WSBuf_AddStringNoEncoding(&s_buf, PAL_T("<a>")) ))
        goto cleanup;

    for ( unsigned int i = 0; i < 100; i++ )
    {
        result += TEST_STR;
        if(!TEST_ASSERT (MI_RESULT_OK == WSBuf_AddString(&s_buf, TEST_STR) ))
            goto cleanup;
    }

    if(!TEST_ASSERT (MI_RESULT_OK == WSBuf_AddStringNoEncoding(&s_buf, PAL_T("</a>")) ))
        goto cleanup;

    p = WSBuf_StealPage(&s_buf);
    if(!TEST_ASSERT(0 != p))
        goto cleanup;


    /* create xml */
    xml = (XML *) PAL_Malloc(sizeof(XML));
    
    if(!TEST_ASSERT(xml != NULL))
        goto cleanup;
    XML_Init(xml);
    XML_SetText(xml, (ZChar*) (p + 1));

    TEST_ASSERT(0 == XML_Next(xml, &e));
    TEST_ASSERT(Tcscmp(e.data.data, PAL_T("a")) == 0);
    TEST_ASSERT(e.type == XML_START);

    TEST_ASSERT(0 == XML_Next(xml, &e));
    TEST_ASSERT(e.type == XML_CHARS);
    TEST_ASSERT(result == e.data.data);

    TEST_ASSERT(0 == XML_Next(xml, &e));
    TEST_ASSERT(Tcscmp(e.data.data, PAL_T("a")) == 0);
    TEST_ASSERT(e.type == XML_END);

cleanup:    
    if(p) PAL_Free(p);
    if(xml) PAL_Free(xml);

    TEST_ASSERT (MI_RESULT_OK == WSBuf_Destroy(&s_buf));    
}
NitsEndTest

NitsTestWithSetup(TestGetRequest, TestWsbufSetup)
{
    MI_Char expected[1024];
    MI_Char interval[64];
    const MI_Char *output = NULL;
    const MI_Char *action = ZT("http://schemas.xmlsoap.org/ws/2004/09/transfer/Get");
    const MI_Char *className = ZT("X_Number");

    GetInstanceReq request = {{{0}}};
    Batch *batch = NULL;

    WsmanClient_Headers cliHeaders;  
    cliHeaders.maxEnvelopeSize = 32761;
    cliHeaders.protocol = const_cast<MI_Char*>(ZT("http"));
    cliHeaders.hostname = const_cast<MI_Char*>(ZT("localhost"));
    cliHeaders.port = 5985;
    cliHeaders.httpUrl = const_cast<MI_Char*>(ZT("/wsman"));
    cliHeaders.locale = const_cast<MI_Char*>(ZT("en-US"));
    cliHeaders.dataLocale = const_cast<MI_Char*>(ZT("de-DE"));
    memset(&cliHeaders.operationTimeout, 0, sizeof(MI_Interval));
    cliHeaders.operationTimeout.seconds = 30;
    cliHeaders.resourceUri = const_cast<MI_Char*>(ZT("http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/X_smallNumber"));
    cliHeaders.operationOptions = NULL;

    MI_Datetime dt;
    dt.isTimestamp = 0;
    memcpy(&dt.u.interval, &cliHeaders.operationTimeout, sizeof(MI_Interval));
    FormatWSManDatetime(&dt, interval);

    if (!NitsCompare(MI_RESULT_OK, WSBuf_Init(&s_buf, 1024), PAL_T("Unable to initialize buffer")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&request.instanceName, className, MI_FLAG_CLASS, batch), 
                     PAL_T("Unable to create new instance")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, GetMessageRequest(&s_buf, &cliHeaders, &request), PAL_T ("Create Get request failed.")))
    {
        goto cleanup;
    } 

    output = BufData(&s_buf);

    Tcslcpy(expected, ZT("<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" ")
            ZT("xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" ")
            ZT("xmlns:n=\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\" ")
            ZT("xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" ")
            ZT("xmlns:x=\"http://www.w3.org/2001/XMLSchema\" ")
            ZT("xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\" >")
            ZT("<s:Header>"),
            MI_COUNT(expected)
);
    NitsCompareSubstring(output, expected, ZT("Envelope and Header"));

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<a:To>%T://%T:%d%T</a:To>"),
             cliHeaders.protocol, cliHeaders.hostname, cliHeaders.port, cliHeaders.httpUrl);
    NitsCompareSubstring(output, expected, ZT("To Address"));

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<w:ResourceURI s:mustUnderstand=\"true\">%T</w:ResourceURI>"),
             cliHeaders.resourceUri);
    NitsCompareSubstring(output, expected, ZT("ResourceURI"));

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<a:ReplyTo><a:Address s:mustUnderstand=\"true\">%T</a:Address></a:ReplyTo>"),
             ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous"));
    NitsCompareSubstring(output, expected, ZT("ReplyTo"));

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<a:Action>%T</a:Action>"),
             action);
    NitsCompareSubstring(output, expected, ZT("Action"));

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<w:MaxEnvelopeSize s:mustUnderstand=\"true\">%d</w:MaxEnvelopeSize>"),
             cliHeaders.maxEnvelopeSize);
    NitsCompareSubstring(output, expected, ZT("MaxEnvelopeSize"));

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<w:OperationTimeout>%T</w:OperationTimeout>"),
             interval);
    NitsCompareSubstring(output, expected, ZT("OperationTimeout"));

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<w:Locale xml:lang=\"%T\" s:mustUnderstand=\"false\"/>"),
             cliHeaders.locale);
    NitsCompareSubstring(output, expected, ZT("Locale"));

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<p:DataLocale xml:lang=\"%T\" s:mustUnderstand=\"false\"/>"),
             cliHeaders.dataLocale);
    NitsCompareSubstring(output, expected, ZT("Locale"));

    Tcslcpy(expected, LIT(ZT("</s:Header><s:Body></s:Body></s:Envelope>")));
    NitsCompareSubstring(output, expected, ZT("End Tags"));

cleanup:  
    if (request.instanceName)
    {
        __MI_Instance_Delete(request.instanceName);
    }
    NitsCompare(MI_RESULT_OK, WSBuf_Destroy(&s_buf), PAL_T("WSBuf_Destroy failed"));
}
NitsEndTest

NitsTestWithSetup(TestGetRequest2, TestWsbufSetup)
{
    MI_Char expected[1024];
    MI_Char interval[64];
    const MI_Char *output = NULL;
    const MI_Char *className = ZT("X_Number");
    const MI_Char *optionName1 = ZT("__MI_OPERATIONOPTIONS_TIMEOUT");   // from MI_OperationOptions_SetTimeout
    const MI_Char *optionName2 = ZT("StringOption");
    const MI_Char *optionName3 = ZT("IntOption");
    const MI_Char *stringVal = ZT("StringValue");
    const MI_Uint32 intVal = 5;
    const MI_Char *selectName = ZT("InstanceTest");
    const MI_Type selectType = MI_UINT32;
    const MI_Char *nameSpace = ZT("myNameSpace");
    MI_Value selectValue = {0};

    GetInstanceReq request = {{{0}}};
    Batch *batch = NULL;
    MI_Application app = { 0 };
    MI_OperationOptions options = { 0 };

    WsmanClient_Headers cliHeaders;  
    cliHeaders.maxEnvelopeSize = 32761;
    cliHeaders.protocol = const_cast<MI_Char*>(ZT("http"));
    cliHeaders.hostname = const_cast<MI_Char*>(ZT("localhost"));
    cliHeaders.port = 5985;
    cliHeaders.httpUrl = const_cast<MI_Char*>(ZT("wsman"));    // Note that there's no leading slash in this test
    cliHeaders.locale = NULL;
    cliHeaders.dataLocale = NULL;
    memset(&cliHeaders.operationTimeout, 0, sizeof(MI_Interval));
    cliHeaders.resourceUri = NULL;
    cliHeaders.operationOptions = &options;

    MI_Datetime dt;
    memset(&dt, 0, sizeof(MI_Datetime));
    dt.u.interval.minutes = 1;

    if (!NitsCompare(MI_RESULT_OK, WSBuf_Init(&s_buf, 1024), PAL_T("Unable to initialize buffer")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, OperationOptions_Create(&app, true, &options), PAL_T("Unable to create OperationOptions")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, MI_OperationOptions_SetTimeout(&options, &dt.u.interval), PAL_T("Unable to add time interval")))
    {
        goto cleanup;
    }
    if (!NitsCompare(MI_RESULT_OK, MI_OperationOptions_SetString(&options, optionName2, stringVal, 0), 
                     PAL_T("Unable to add string")))
    {
        goto cleanup;
    }    
    if (!NitsCompare(MI_RESULT_OK, MI_OperationOptions_SetNumber(&options, optionName3, intVal, 0), 
                     PAL_T("Unable to add uint32")))
    {
        goto cleanup;
    }    

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&request.instanceName, className, MI_FLAG_CLASS, batch), 
                     PAL_T("Unable to create new instance")))
    {
        goto cleanup;
    }

    // Set Namespace
    if (!NitsCompare(MI_RESULT_OK, MI_Instance_SetNameSpace(request.instanceName, nameSpace), 
                     PAL_T("Unable to set name space")))
    {
        goto cleanup;
    }

    // Add element to instance
    selectValue.uint32 = 10;
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(request.instanceName, selectName, &selectValue, selectType, MI_FLAG_KEY), 
                     PAL_T("Unable to add element")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, GetMessageRequest(&s_buf, &cliHeaders, &request), PAL_T ("Create Get request failed.")))
    {
        goto cleanup;
    } 

    output = BufData(&s_buf);

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<a:To>%T://%T:%d/%T</a:To>"),
             cliHeaders.protocol, cliHeaders.hostname, cliHeaders.port, cliHeaders.httpUrl);
    NitsCompareSubstring(output, expected, ZT("To Address"));

    FormatWSManDatetime(&dt, interval);
    Stprintf(expected, 
             MI_COUNT(expected), 
             ZT("<w:OptionSet s:mustUnderstand=\"true\">")
             ZT("<w:Option Name=\"%T\" Type=\"x:duration\">%T</w:Option>")
             ZT("<w:Option Name=\"%T\" Type=\"x:string\">%T</w:Option>")
             ZT("<w:Option Name=\"%T\" Type=\"x:unsignedInt\">%d</w:Option>")
             ZT("</w:OptionSet>"), 
             optionName1, interval,
             optionName2, stringVal,
             optionName3, intVal);
    NitsCompareSubstring(output, expected, ZT("OptionSet"));

    Stprintf(expected, 
             MI_COUNT(expected), 
             ZT("<w:SelectorSet>")
             ZT("<w:Selector Name=\"__cimnamespace\">%T</w:Selector>")
             ZT("<w:Selector Name=\"%T\">%d</w:Selector>")
             ZT("</w:SelectorSet>"), 
             nameSpace, selectName, selectValue.uint32);
    NitsCompareSubstring(output, expected, ZT("SelectorSet"));

    Stprintf(expected, 
             MI_COUNT(expected), 
             ZT("<w:ResourceURI s:mustUnderstand=\"true\">http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/%T</w:ResourceURI>"), 
             className);
    NitsCompareSubstring(output, expected, ZT("ResourceURI"));

cleanup:  
    if (request.instanceName)
    {
        __MI_Instance_Delete(request.instanceName);
    }
    MI_OperationOptions_Delete(&options);
    NitsCompare(MI_RESULT_OK, WSBuf_Destroy(&s_buf), PAL_T("WSBuf_Destroy failed"));
}
NitsEndTest

NitsTestWithSetup(TestDeleteRequest, TestWsbufSetup)
{
    MI_Char expected[1024];
    const MI_Char *output = NULL;
    const MI_Char *action = ZT("http://schemas.xmlsoap.org/ws/2004/09/transfer/Delete");
    const MI_Char *className = ZT("X_Number");

    DeleteInstanceReq request = {{{0}}};
    Batch *batch = NULL;

    WsmanClient_Headers cliHeaders;  
    cliHeaders.maxEnvelopeSize = 32761;
    cliHeaders.protocol = const_cast<MI_Char*>(ZT("http"));
    cliHeaders.hostname = const_cast<MI_Char*>(ZT("localhost"));
    cliHeaders.port = 5985;
    cliHeaders.httpUrl = const_cast<MI_Char*>(ZT("/wsman"));
    cliHeaders.locale = NULL;
    cliHeaders.dataLocale = NULL;
    memset(&cliHeaders.operationTimeout, 0, sizeof(MI_Interval));
    cliHeaders.resourceUri = const_cast<MI_Char*>(ZT("http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/X_smallNumber"));
    cliHeaders.operationOptions = NULL;

    if (!NitsCompare(MI_RESULT_OK, WSBuf_Init(&s_buf, 1024), PAL_T("Unable to initialize buffer")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&request.instanceName, className, MI_FLAG_CLASS, batch), 
                     PAL_T("Unable to create new instance")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, DeleteMessageRequest(&s_buf, &cliHeaders, &request), PAL_T ("Create Delete request failed.")))
    {
        goto cleanup;
    } 

    output = BufData(&s_buf);

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<a:Action>%T</a:Action>"),
             action);
    NitsCompareSubstring(output, expected, ZT("Action"));

cleanup:  
    if (request.instanceName)
    {
        __MI_Instance_Delete(request.instanceName);
    }
    NitsCompare(MI_RESULT_OK, WSBuf_Destroy(&s_buf), PAL_T("WSBuf_Destroy failed"));
}
NitsEndTest

NitsTestWithSetup(TestPutRequest, TestWsbufSetup)
{
    MI_Char expected[1024];
    const MI_Char *output = NULL;
    const MI_Char *action = ZT("http://schemas.xmlsoap.org/ws/2004/09/transfer/Put");
    const MI_Char *className = ZT("X_Number");
    const MI_Char *data = ZT("<p:myclass xmlns:p=\"http://schemas.microsoft.com/wsman/2005/06/wmi/root/mynamespace/myclass\">")
        ZT("<p:Data1>Test Message</p:Data1><p:id>1</p:id>");

    ModifyInstanceReq request = {{{0}}};
    request.packedInstancePtr = (void*)data;
    request.packedInstanceSize = Tcslen(data);
    Batch *batch = NULL;

    WsmanClient_Headers cliHeaders;  
    cliHeaders.maxEnvelopeSize = 32761;
    cliHeaders.protocol = const_cast<MI_Char*>(ZT("http"));
    cliHeaders.hostname = const_cast<MI_Char*>(ZT("localhost"));
    cliHeaders.port = 5985;
    cliHeaders.httpUrl = const_cast<MI_Char*>(ZT("/wsman"));
    cliHeaders.locale = NULL;
    cliHeaders.dataLocale = NULL;
    memset(&cliHeaders.operationTimeout, 0, sizeof(MI_Interval));
    cliHeaders.resourceUri = const_cast<MI_Char*>(ZT("http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/X_smallNumber"));
    cliHeaders.operationOptions = NULL;

    if (!NitsCompare(MI_RESULT_OK, WSBuf_Init(&s_buf, 1024), PAL_T("Unable to initialize buffer")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&request.instance, className, MI_FLAG_CLASS, batch), 
                     PAL_T("Unable to create new instance")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, PutMessageRequest(&s_buf, &cliHeaders, &request), PAL_T ("Create Delete request failed.")))
    {
        goto cleanup;
    } 

    output = BufData(&s_buf);

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<a:Action>%T</a:Action>"),
             action);
    NitsCompareSubstring(output, expected, ZT("Action"));

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<s:Body>%T</s:Body>"),
             data);
    NitsCompareSubstring(output, expected, ZT("Body"));

cleanup:  
    if (request.instance)
    {
        __MI_Instance_Delete(request.instance);
    }
    NitsCompare(MI_RESULT_OK, WSBuf_Destroy(&s_buf), PAL_T("WSBuf_Destroy failed"));
}
NitsEndTest

NitsTestWithSetup(TestCreateRequest, TestWsbufSetup)
{
    MI_Char expected[1024];
    const MI_Char *output = NULL;
    const MI_Char *action = ZT("http://schemas.xmlsoap.org/ws/2004/09/transfer/Create");
    const MI_Char *className = ZT("X_Number");
    const MI_Char *data = ZT("<p:myclass xmlns:p=\"http://schemas.microsoft.com/wsman/2005/06/wmi/root/mynamespace/myclass\">")
        ZT("<p:Data1>Test Message</p:Data1><p:id>1</p:id>");

    CreateInstanceReq request = {{{0}}};
    request.packedInstancePtr = (void*)data;
    request.packedInstanceSize = Tcslen(data);
    Batch *batch = NULL;

    WsmanClient_Headers cliHeaders;  
    cliHeaders.maxEnvelopeSize = 32761;
    cliHeaders.protocol = const_cast<MI_Char*>(ZT("http"));
    cliHeaders.hostname = const_cast<MI_Char*>(ZT("localhost"));
    cliHeaders.port = 5985;
    cliHeaders.httpUrl = const_cast<MI_Char*>(ZT("/wsman"));
    cliHeaders.locale = NULL;
    cliHeaders.dataLocale = NULL;
    memset(&cliHeaders.operationTimeout, 0, sizeof(MI_Interval));
    cliHeaders.resourceUri = const_cast<MI_Char*>(ZT("http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/X_smallNumber"));
    cliHeaders.operationOptions = NULL;

    if (!NitsCompare(MI_RESULT_OK, WSBuf_Init(&s_buf, 1024), PAL_T("Unable to initialize buffer")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&request.instance, className, MI_FLAG_CLASS, batch), 
                     PAL_T("Unable to create new instance")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK,CreateMessageRequest(&s_buf, &cliHeaders, &request), PAL_T ("Create Delete request failed.")))
    {
        goto cleanup;
    } 

    output = BufData(&s_buf);

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<a:Action>%T</a:Action>"),
             action);
    NitsCompareSubstring(output, expected, ZT("Action"));

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<s:Body>%T</s:Body>"),
             data);
    NitsCompareSubstring(output, expected, ZT("Body"));

cleanup:  
    if (request.instance)
    {
        __MI_Instance_Delete(request.instance);
    }
    NitsCompare(MI_RESULT_OK, WSBuf_Destroy(&s_buf), PAL_T("WSBuf_Destroy failed"));
}
NitsEndTest
