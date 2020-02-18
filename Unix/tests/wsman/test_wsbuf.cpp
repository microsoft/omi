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
#include <wsman/wstags.h>
#include <wsman/wsbuf.h>
#include <wsman/wsmanparser.h>
#include <base/helpers.h>
#include <base/batch.h>
#include <base/field.h>
#include <pal/format.h>
extern "C" {
#include <miapi/Options.h>
}

typedef std::string String;

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
    memset(&cliHeaders, 0, sizeof(cliHeaders));
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
            ZT("xmlns:xsi=\"http://www.w3.org/2001/XMLSchema\" ")
            ZT("xmlns:h=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell\" ")
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
    MI_Instance *options = NULL;

    WsmanClient_Headers cliHeaders;
    memset(&cliHeaders, 0, sizeof(cliHeaders));
    cliHeaders.maxEnvelopeSize = 32761;
    cliHeaders.protocol = const_cast<MI_Char*>(ZT("http"));
    cliHeaders.hostname = const_cast<MI_Char*>(ZT("localhost"));
    cliHeaders.port = 5985;
    cliHeaders.httpUrl = const_cast<MI_Char*>(ZT("wsman"));    // Note that there's no leading slash in this test
    cliHeaders.locale = NULL;
    cliHeaders.dataLocale = NULL;
    memset(&cliHeaders.operationTimeout, 0, sizeof(MI_Interval));
    cliHeaders.resourceUri = NULL;
    request.nameSpace = nameSpace;

    MI_Datetime dt;
    memset(&dt, 0, sizeof(MI_Datetime));
    dt.u.interval.minutes = 1;

    if (!NitsCompare(MI_RESULT_OK, WSBuf_Init(&s_buf, 1024), PAL_T("Unable to initialize buffer")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&options, MI_T("Options"), MI_FLAG_CLASS, NULL), PAL_T("Unable to create OperationOptions")))
    {
        goto cleanup;
    }
    cliHeaders.operationOptions = options;

    selectValue.string = (MI_Char*) stringVal;
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(options, optionName2, &selectValue, MI_STRING, 0),
                     PAL_T("Unable to add string")))
    {
        goto cleanup;
    }
    selectValue.uint32 = intVal;
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(options, optionName3, &selectValue, MI_UINT32, 0),
                     PAL_T("Unable to add uint32")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&request.instanceName, className, MI_FLAG_CLASS, batch),
                     PAL_T("Unable to create new instance")))
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
             ZT("<w:Option Name=\"%T\" Type=\"x:string\">%T</w:Option>")
             ZT("<w:Option Name=\"%T\" Type=\"x:unsignedInt\">%d</w:Option>")
             ZT("</w:OptionSet>"),
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
             ZT("<w:ResourceURI s:mustUnderstand=\"true\">http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/%T</w:ResourceURI>"),
             className);
    NitsCompareSubstring(output, expected, ZT("ResourceURI"));

cleanup:
    if (request.instanceName)
    {
        __MI_Instance_Delete(request.instanceName);
    }
    if (options)
    {
        __MI_Instance_Delete(options);
    }
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
    memset(&cliHeaders, 0, sizeof(cliHeaders));
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
    memset(&cliHeaders, 0, sizeof(cliHeaders));
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
    memset(&cliHeaders, 0, sizeof(cliHeaders));
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
#ifndef DISABLE_SHELL
    cliHeaders.compressionType = const_cast<MI_Char*>(ZT("xpress"));
    cliHeaders.sessionId = const_cast<MI_Char*>(ZT("SessionGuid"));
#endif

    if (!NitsCompare(MI_RESULT_OK, WSBuf_Init(&s_buf, 1024), PAL_T("Unable to initialize buffer")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&request.instance, className, MI_FLAG_CLASS, batch),
                     PAL_T("Unable to create new instance")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK,CreateMessageRequest(&s_buf, &cliHeaders, &request), PAL_T ("Create request failed.")))
    {
        goto cleanup;
    }

    output = BufData(&s_buf);

#ifndef DISABLE_SHELL
    NitsCompareSubstring(output, PAL_T("<h:CompressionType s:mustUnderstand=\"true\">xpress</h:CompressionType>"), ZT("CompressionType"));
    NitsCompareSubstring(output, PAL_T("<p:SessionId s:mustUnderstand=\"false\">SessionGuid</p:SessionId>"), ZT("SessionId"));
#endif

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

NitsTestWithSetup(TestInvokeRequest, TestWsbufSetup)
{
    MI_Char expected[1024];
    const MI_Char *output = NULL;
    const MI_Char *defaultAction = ZT("http://schemas.dmtf.org/wbem/wscim/1/cim-schema/2/");
    const MI_Char *className = ZT("X_Number");
    const MI_Char *function = ZT("myFunction");
    const MI_Char *data = ZT("<p:Create_INPUT xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wmi/root/cim/Win32_Process\">")
             ZT("<p:CommandLine>notepad.exe</p:CommandLine><p:CurrentDirectory>C:\\</p:CurrentDirectory></p:Create_INPUT>");

    InvokeReq request = {{{0}}};
    request.packedInstanceParamsPtr = (void*)data;
    request.packedInstanceParamsSize = Tcslen(data);
    request.className = className;
    request.function = function;
    Batch *batch = NULL;

    WsmanClient_Headers cliHeaders;
    memset(&cliHeaders, 0, sizeof(cliHeaders));
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
    cliHeaders.action = NULL;

    if (!NitsCompare(MI_RESULT_OK, WSBuf_Init(&s_buf, 1024), PAL_T("Unable to initialize buffer")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&request.instance, className, MI_FLAG_CLASS, batch),
                     PAL_T("Unable to create new instance")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK,InvokeMessageRequest(&s_buf, &cliHeaders, &request), PAL_T ("Create Invoke request failed.")))
    {
        goto cleanup;
    }

    output = BufData(&s_buf);

    Stprintf(expected, MI_COUNT(expected),
             ZT("<a:Action>%T%T/%T</a:Action>"),
             defaultAction, request.className, request.function );
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

NitsTestWithSetup(TestEnumerateRequest, TestWsbufSetup)
{
    MI_Char expected[1024];
    const MI_Char *output = NULL;
    const MI_Char *action = ZT("http://schemas.xmlsoap.org/ws/2004/09/enumeration/Enumerate");
    const MI_Uint32 maxElements = 1000;

    EnumerateInstancesReq request = {{{0}}};
    request.nameSpace = ZT("root/cimv2");
    request.className = ZT("X_SmallNumber");
    request.maxElements = maxElements;

    WsmanClient_Headers cliHeaders;
    memset(&cliHeaders, 0, sizeof(cliHeaders));
    cliHeaders.maxEnvelopeSize = 32761;
    cliHeaders.protocol = const_cast<MI_Char*>(ZT("http"));
    cliHeaders.hostname = const_cast<MI_Char*>(ZT("localhost"));
    cliHeaders.port = 5985;
    cliHeaders.httpUrl = const_cast<MI_Char*>(ZT("/wsman"));
    cliHeaders.locale = NULL;
    cliHeaders.dataLocale = NULL;
    memset(&cliHeaders.operationTimeout, 0, sizeof(MI_Interval));
    cliHeaders.resourceUri = const_cast<MI_Char*>(ZT("http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/X_SmallNumber"));
    cliHeaders.operationOptions = NULL;

    if (!NitsCompare(MI_RESULT_OK, WSBuf_Init(&s_buf, 1024), PAL_T("Unable to initialize buffer")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, EnumerateMessageRequest(&s_buf, &cliHeaders, &request), 
                     PAL_T ("Enumerate request failed.")))
    {
        goto cleanup;
    }

    output = BufData(&s_buf);

    Stprintf(expected, MI_COUNT(expected),
             ZT("<a:Action>%T</a:Action>"),
             action);
    NitsCompareSubstring(output, expected, ZT("Action"));

    Stprintf(expected, MI_COUNT(expected),
             ZT("<w:ResourceURI s:mustUnderstand=\"true\">%T</w:ResourceURI>"),
             cliHeaders.resourceUri);
    NitsCompareSubstring(output, expected, ZT("ResourceURI"));

    Stprintf(expected,
             MI_COUNT(expected),
             ZT("<w:SelectorSet>")
             ZT("<w:Selector Name=\"__cimnamespace\">%T</w:Selector>")
             ZT("</w:SelectorSet>"),
             request.nameSpace);
    NitsCompareSubstring(output, expected, ZT("SelectorSet"));

    Stprintf(expected, MI_COUNT(expected),
             ZT("<s:Body><n:Enumerate><w:OptimizeEnumeration/><w:MaxElements>%d</w:MaxElements></n:Enumerate></s:Body>"),
             maxElements);
    NitsCompareSubstring(output, expected, ZT("Body"));

cleanup:
    NitsCompare(MI_RESULT_OK, WSBuf_Destroy(&s_buf), PAL_T("WSBuf_Destroy failed"));
}
NitsEndTest

NitsTestWithSetup(TestPullRequest, TestWsbufSetup)
{
    MI_Char expected[1024];
    const MI_Char *output = NULL;
    const MI_Char *action = ZT("http://schemas.xmlsoap.org/ws/2004/09/enumeration/Pull");
    const MI_Uint32 maxElements = 1;

    PullReq request = {{{0}}};
    request.nameSpace = ZT("root/cimv2");
    request.className = ZT("X_SmallNumber");
    request.context = ZT("1164378112");
    request.maxElements = maxElements;

    WsmanClient_Headers cliHeaders;
    memset(&cliHeaders, 0, sizeof(cliHeaders));
    cliHeaders.maxEnvelopeSize = 32761;
    cliHeaders.protocol = const_cast<MI_Char*>(ZT("http"));
    cliHeaders.hostname = const_cast<MI_Char*>(ZT("localhost"));
    cliHeaders.port = 5985;
    cliHeaders.httpUrl = const_cast<MI_Char*>(ZT("/wsman"));
    cliHeaders.locale = NULL;
    cliHeaders.dataLocale = NULL;
    memset(&cliHeaders.operationTimeout, 0, sizeof(MI_Interval));
    cliHeaders.resourceUri = const_cast<MI_Char*>(ZT("http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/X_SmallNumber"));
    cliHeaders.operationOptions = NULL;

    if (!NitsCompare(MI_RESULT_OK, WSBuf_Init(&s_buf, 1024), PAL_T("Unable to initialize buffer")))
    {
        goto cleanup;
    }

    if (!NitsCompare(MI_RESULT_OK, EnumeratePullRequest(&s_buf, &cliHeaders, &request), 
                     PAL_T ("Pull request failed.")))
    {
        goto cleanup;
    }

    output = BufData(&s_buf);

    Stprintf(expected, MI_COUNT(expected),
             ZT("<a:Action>%T</a:Action>"),
             action);
    NitsCompareSubstring(output, expected, ZT("Action"));

    Stprintf(expected, MI_COUNT(expected),
             ZT("<w:ResourceURI s:mustUnderstand=\"true\">%T</w:ResourceURI>"),
             cliHeaders.resourceUri);
    NitsCompareSubstring(output, expected, ZT("ResourceURI"));

    Stprintf(expected,
             MI_COUNT(expected),
             ZT("<w:SelectorSet>")
             ZT("<w:Selector Name=\"__cimnamespace\">%T</w:Selector>")
             ZT("</w:SelectorSet>"),
             request.nameSpace);
    NitsCompareSubstring(output, expected, ZT("SelectorSet"));

    Stprintf(expected, MI_COUNT(expected),
             ZT("<s:Body><n:Pull><n:EnumerationContext>1164378112</n:EnumerationContext><n:MaxElements>%d</n:MaxElements></n:Pull></s:Body>"),
             maxElements);
    NitsCompareSubstring(output, expected, ZT("Body"));

cleanup:
    NitsCompare(MI_RESULT_OK, WSBuf_Destroy(&s_buf), PAL_T("WSBuf_Destroy failed"));
}
NitsEndTest

#ifndef DISABLE_SHELL

void InitXml(XML *xml, MI_Char *xmlText)
{
    /* Initialize xml parser */
    XML_Init(xml);

    XML_RegisterNameSpace(xml, 's',
        ZT("http://www.w3.org/2003/05/soap-envelope"));

    XML_RegisterNameSpace(xml, 'a',
        ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing"));

    XML_RegisterNameSpace(xml, 'w',
        ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd"));

    XML_RegisterNameSpace(xml, 'n',
        ZT("http://schemas.xmlsoap.org/ws/2004/09/enumeration"));

    XML_RegisterNameSpace(xml, 'b',
        ZT("http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd"));

    XML_RegisterNameSpace(xml, 'p',
        ZT("http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd"));

    XML_RegisterNameSpace(xml, 'i',
        ZT("http://schemas.dmtf.org/wbem/wsman/identity/1/wsmanidentity.xsd"));

    XML_RegisterNameSpace(xml, 'x',
        ZT("http://www.w3.org/2001/XMLSchema-instance"));

    XML_RegisterNameSpace(xml, MI_T('e'),
        ZT("http://schemas.xmlsoap.org/ws/2004/08/eventing"));

#ifndef DISABLE_SHELL
    XML_RegisterNameSpace(xml, MI_T('h'),
        ZT("http://schemas.microsoft.com/wbem/wsman/1/windows/shell"));
#endif

    XML_SetText(xml, xmlText);
}
NitsTest(TestShellCreateRequest)
{
    Batch *batch = NULL;
    MI_Instance *instance = NULL;
    MI_Instance *parsedInstance = NULL;
    MI_Value value;
    MI_Type type;
    void *instanceBuf = NULL;
    MI_Uint32 instanceBufSize;
    MI_Char expectedInstanceBuf[] =
        ZT("<p:Shell Name=\"Session1\" ShellId=\"2AC58C86-496E-45AE-8648-A2526B5DB7FF\" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell\">")
        ZT("<p:InputStreams>in1 int2</p:InputStreams>")
        ZT("<p:OutputStreams>out</p:OutputStreams>")
        ZT("<creationXml xmlns=\"http://schemas.microsoft.com/powershell\">Lots Of XML</creationXml>")
        ZT("</p:Shell>");
    XML xml;
    XML_Elem xmlstart;

    InitXml(&xml, expectedInstanceBuf);

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Need a batch")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&instance, PAL_T("Shell"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("2AC58C86-496E-45AE-8648-A2526B5DB7FF");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("ShellId"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("Session1");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("Name"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("in1 int2");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("InputStreams"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("out");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("OutputStreams"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

     value.string = (MI_Char*) PAL_T("<creationXml xmlns=\"http://schemas.microsoft.com/powershell\">Lots Of XML</creationXml>");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("CreationXml"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, WSBuf_InstanceToBuf(USERAGENT_UNKNOWN, instance, NULL, NULL, NULL, batch, WSMAN_ObjectFlag|WSMAN_IsShellRequest, &instanceBuf, &instanceBufSize), PAL_T("Serializing instance")))
        goto cleanup;

    if (!NitsCompareString((MI_Char*) instanceBuf, expectedInstanceBuf, PAL_T("Expected serialized instance")))
        goto cleanup;

    if (!NitsCompare(0, XML_Next(&xml, &xmlstart), PAL_T("Parsing first xml tag")))
        goto cleanup;

    if (!NitsCompare(0, WS_ParseCreateShellBody(&xml, &xmlstart, batch, &parsedInstance), PAL_T("Parsing of instance")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("ShellId"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("2AC58C86-496E-45AE-8648-A2526B5DB7FF"), value.string, PAL_T("Validating shellId")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("Name"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

     if (!NitsCompareString(PAL_T("Session1"), value.string, PAL_T("Validating shell name")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("InputStreams"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

     if (!NitsCompareString(PAL_T("in1 int2"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("OutputStreams"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

     if (!NitsCompareString(PAL_T("out"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

cleanup:
    if (batch)
        Batch_Delete(batch);

}
NitsEndTest

NitsTest(TestShellCreateResponse)
{
    Batch *batch = NULL;
    MI_Instance *instance = NULL;
    MI_Instance *parsedInstance = NULL;
    MI_Char *epr = NULL;
    MI_Value value;
    MI_Type type;
    void *instanceBuf = NULL;
    MI_Uint32 instanceBufSize;
    MI_Char expectedInstanceBuf[] =
        ZT("<wxf:ResourceCreated>")
        ZT("<wsa:Address>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:Address>")
        ZT("<wsa:ReferenceParameters>")
        ZT("<wsman:ResourceURI>http://schemas.microsoft.com/powershell/Microsoft.PowerShell</wsman:ResourceURI>")
        ZT("<wsman:SelectorSet>")
        ZT("<wsman:Selector Name=\"ShellId\">2AC58C86-496E-45AE-8648-A2526B5DB7FF</wsman:Selector>")
        ZT("</wsman:SelectorSet>")
        ZT("</wsa:ReferenceParameters>")
        ZT("</wxf:ResourceCreated>");
    MI_Char bufferToParse[] =
        ZT("<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" xmlns:wsa=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\"   xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:wsmb=\"http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd\" xmlns:wsman=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" xmlns:wxf=\"http://schemas.xmlsoap.org/ws/2004/09/transfer\">")
        ZT("<s:Body>")
        ZT("<wxf:ResourceCreated>")
        ZT("<wsa:Address>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:Address>")
        ZT("<wsa:ReferenceParameters>")
        ZT("<wsman:ResourceURI>http://schemas.microsoft.com/powershell/Microsoft.PowerShell</wsman:ResourceURI>")
        ZT("<wsman:SelectorSet>")
        ZT("<wsman:Selector Name=\"ShellId\">2AC58C86-496E-45AE-8648-A2526B5DB7FF</wsman:Selector>")
        ZT("</wsman:SelectorSet>")
        ZT("</wsa:ReferenceParameters>")
        ZT("</wxf:ResourceCreated>")
        ZT("</s:Body>")
        ZT("</s:Envelope>");
     XML xml;
    XML_Elem xmlstart;
    InitXml(&xml, bufferToParse);

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Need a batch")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&instance, PAL_T("Shell"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("2AC58C86-496E-45AE-8648-A2526B5DB7FF");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("ShellId"), &value, MI_STRING, MI_FLAG_KEY), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("Session1");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("Name"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("in1 int2");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("InputStreams"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("out");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("OutputStreams"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("http://schemas.microsoft.com/powershell/Microsoft.PowerShell");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("ResourceUri"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("<creationXml xmlns=\"http://schemas.microsoft.com/powershell\">Lots Of XML</creationXml>");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("CreationXml"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, WSBuf_InstanceToBuf(USERAGENT_UNKNOWN, instance, NULL, NULL, NULL, batch, WSMAN_CreatedEPRFlag|WSMAN_IsShellResponse, &instanceBuf, &instanceBufSize), PAL_T("Serializing instance")))
        goto cleanup;

    if (!NitsCompareString((MI_Char*) instanceBuf, expectedInstanceBuf, PAL_T("Expected serialized instance")))
        goto cleanup;

    if (!NitsCompare(0, XML_Next(&xml, &xmlstart), PAL_T("Parsing first xml tag")))
        goto cleanup;

    if (!NitsCompare(0, WS_ParseCreateResponseBody(&xml, batch, &epr, &parsedInstance, MI_TRUE), PAL_T("Parsing of instance")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("ShellId"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("2AC58C86-496E-45AE-8648-A2526B5DB7FF"), value.string, PAL_T("Validating shellId")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("ResourceUri"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

     if (!NitsCompareString(PAL_T("http://schemas.microsoft.com/powershell/Microsoft.PowerShell"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

cleanup:
    if (batch)
        Batch_Delete(batch);

}
NitsEndTest


NitsTest(TestShellCommandRequest)
{
    Batch *batch = NULL;
    MI_Instance *instance = NULL;
    MI_Instance *parsedInstance = NULL;
    MI_Value value;
    MI_Type type;
    const MI_Char* valueArray[2] = { ZT("Arg1"), ZT("Arg2") };
    void *instanceBuf = NULL;
    MI_Uint32 instanceBufSize;
    MI_Char expectedInstanceBuf[] =
        ZT("<p:CommandLine CommandId=\"685F47FF-64C7-46A4-BCCD-6D68B92BD405\" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell\">")
        ZT("<p:Command>MyCommand</p:Command>")
        ZT("<p:Arguments>Arg1</p:Arguments>")
        ZT("<p:Arguments>Arg2</p:Arguments>")
        ZT("</p:CommandLine>");
    XML xml;
    XML_Elem xmlstart;

    InitXml(&xml, expectedInstanceBuf);

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Need a batch")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&instance, PAL_T("CommandLine"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("685F47FF-64C7-46A4-BCCD-6D68B92BD405");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("CommandId"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("MyCommand");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("Command"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.stringa.size = 2;
    value.stringa.data = (MI_Char**) valueArray;
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("Arguments"), &value, MI_STRINGA, 0), PAL_T("Add properties")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, WSBuf_InstanceToBuf(USERAGENT_UNKNOWN, instance, NULL, NULL, NULL, batch, WSMAN_ObjectFlag|WSMAN_IsShellRequest, &instanceBuf, &instanceBufSize), PAL_T("Serializing instance")))
        goto cleanup;

    if (!NitsCompareString((MI_Char*) instanceBuf, expectedInstanceBuf, PAL_T("Expected serialized instance")))
        goto cleanup;

    if (!NitsCompare(0, XML_Next(&xml, &xmlstart), PAL_T("Parsing first xml tag")))
        goto cleanup;

    if (!NitsCompare(0, WS_GetInstance(&xml, &xmlstart, batch, &parsedInstance, WSMANTAG_ACTION_SHELL_COMMAND), PAL_T("Parsing command instance")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("CommandId"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("685F47FF-64C7-46A4-BCCD-6D68B92BD405"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("Command"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("MyCommand"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("Arguments"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompare(MI_STRINGA, type, PAL_T("Arguments should be a string array")))
        goto cleanup;

    if (!NitsCompare(2, value.stringa.size, PAL_T("Arguments array should be 2 items")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("Arg1"), value.stringa.data[0], PAL_T("Validating arguments")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("Arg2"), value.stringa.data[1], PAL_T("Validating arguments")))
        goto cleanup;


cleanup:
    if (batch)
        Batch_Delete(batch);

}
NitsEndTest

NitsTest(TestShellReceiveForShellRequest)
{
    Batch *batch = NULL;
    MI_Instance *instance = NULL;
    MI_Instance *parsedInstance = NULL;
    MI_Instance *parsedInstanceDesiredState = NULL;
    MI_Value value;
    MI_Type type;
    MI_Uint32 flags;
    void *instanceBuf = NULL;
    MI_Uint32 instanceBufSize;
    MI_Char expectedInstanceBuf[] =
        ZT("<p:Receive xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell\">")
        ZT("<p:DesiredStream>out1</p:DesiredStream>")
        ZT("</p:Receive>");
    MI_Char bufferToParse[] =
        ZT("<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\">")
        ZT("<s:Body>")
        ZT("<p:Receive xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell\">")
        ZT("<p:DesiredStream>out1</p:DesiredStream>")
        ZT("</p:Receive>")
        ZT("</s:Body>")
        ZT("</s:Envelope>");
    XML xml;
    XML_Elem xmlstart;

    InitXml(&xml, bufferToParse);

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Need a batch")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&instance, PAL_T("Receive"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("out1");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("DesiredStream"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, WSBuf_InstanceToBuf(USERAGENT_UNKNOWN, instance, NULL, NULL, NULL, batch, WSMAN_ObjectFlag|WSMAN_IsShellRequest, &instanceBuf, &instanceBufSize), PAL_T("Serializing instance")))
        goto cleanup;

    if (!NitsCompareString((MI_Char*) instanceBuf, expectedInstanceBuf, PAL_T("Expected serialized instance")))
        goto cleanup;

    XML_Next(&xml, &xmlstart);
    if (!NitsCompare(0, WS_ParseReceiveBody(&xml, batch, &parsedInstance), PAL_T("Parsing receive instance")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("DesiredStream"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompare(MI_INSTANCE, type, PAL_T("Desired state is not an instance")))
        goto cleanup;

    parsedInstanceDesiredState = value.instance;
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstanceDesiredState, PAL_T("CommandId"), &value, &type, &flags, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsAssert(MI_FLAG_NULL & flags, PAL_T("Validating input streams")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstanceDesiredState, PAL_T("StreamName"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("out1"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

cleanup:
    if (batch)
        Batch_Delete(batch);
}
NitsEndTest

NitsTest(TestShellReceiveForShellResponse)
{
    Batch *batch = NULL;
    MI_Instance *instance = NULL;
    MI_Instance *streamInstance = NULL;
    MI_Instance *commandStateInstance = NULL;
    MI_Instance *parsedInstance = NULL;
    MI_Instance *parsedEmbeddedInstance = NULL;
    MI_Value value;
    MI_Type type;
    MI_Uint32 flags;
    void *instanceBuf = NULL;
    MI_Uint32 instanceBufSize;
    MI_Char expectedInstanceBuf[] =
        ZT("<p:ReceiveResponse xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell\">")
        ZT("<p:Stream Name=\"out1\">streamData</p:Stream>")
        ZT("<p:CommandState State=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell/CommandState/Done\"></p:CommandState>")
        ZT("</p:ReceiveResponse>");
    XML xml;
    XML_Elem xmlstart;

    InitXml(&xml, expectedInstanceBuf);

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Need a batch")))
        goto cleanup;

   if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&streamInstance, PAL_T("Stream"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("out1");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(streamInstance, PAL_T("streamName"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("streamData");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(streamInstance, PAL_T("data"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&commandStateInstance, PAL_T("CommandState"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("http://schemas.microsoft.com/wbem/wsman/1/windows/shell/CommandState/Done");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(commandStateInstance, PAL_T("state"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&instance, PAL_T("Receive"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
        goto cleanup;

    value.instance = streamInstance;
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("Stream"), &value, MI_INSTANCE, MI_FLAG_BORROW), PAL_T("Add properties")))
        goto cleanup;

    value.instance = commandStateInstance;
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("CommandState"), &value, MI_INSTANCE, MI_FLAG_BORROW), PAL_T("Add properties")))
        goto cleanup;


    if (!NitsCompare(MI_RESULT_OK, WSBuf_InstanceToBuf(USERAGENT_UNKNOWN, instance, NULL, NULL, NULL, batch, WSMAN_ObjectFlag|WSMAN_IsShellResponse, &instanceBuf, &instanceBufSize), PAL_T("Serializing instance")))
        goto cleanup;

    if (!NitsCompareString((MI_Char*) instanceBuf, expectedInstanceBuf, PAL_T("Expected serialized instance")))
        goto cleanup;

    XML_Next(&xml, &xmlstart);
    if (!NitsCompare(0, WS_GetInstance(&xml, &xmlstart, batch, &parsedInstance, WSMANTAG_ACTION_SHELL_RECEIVE_RESPONSE), PAL_T("Parsing receive instance")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("Stream"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompare(MI_INSTANCE, type, PAL_T("Desired state is not an instance")))
        goto cleanup;

    parsedEmbeddedInstance = value.instance;
    if (!NitsCompare(MI_RESULT_NO_SUCH_PROPERTY, __MI_Instance_GetElement(parsedEmbeddedInstance, PAL_T("CommandId"), &value, &type, &flags, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedEmbeddedInstance, PAL_T("streamName"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("out1"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("CommandState"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompare(MI_INSTANCE, type, PAL_T("Desired state is not an instance")))
        goto cleanup;

    parsedEmbeddedInstance = value.instance;
    if (!NitsCompare(MI_RESULT_NO_SUCH_PROPERTY, __MI_Instance_GetElement(parsedEmbeddedInstance, PAL_T("CommandId"), &value, &type, &flags, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedEmbeddedInstance, PAL_T("state"), &value, &type, NULL, NULL), PAL_T("Validating command state")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("http://schemas.microsoft.com/wbem/wsman/1/windows/shell/CommandState/Done"), value.string, PAL_T("Validating command state")))
        goto cleanup;

cleanup:
    if (batch)
        Batch_Delete(batch);
}
NitsEndTest

NitsTest(TestShellReceiveForCommandRequest)
{
    Batch *batch = NULL;
    MI_Instance *instance = NULL;
    MI_Instance *parsedInstance = NULL;
    MI_Instance *parsedInstanceDesiredState = NULL;
    MI_Value value;
    MI_Type type;
    void *instanceBuf = NULL;
    MI_Uint32 instanceBufSize;
    MI_Char expectedInstanceBuf[] =
        ZT("<p:Receive xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell\">")
        ZT("<p:DesiredStream CommandId=\"685F47FF-64C7-46A4-BCCD-6D68B92BD405\">out1</p:DesiredStream>")
        ZT("</p:Receive>");
    MI_Char bufferToParse[] =
        ZT("<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\">")
        ZT("<s:Body>")
        ZT("<p:Receive xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell\">")
        ZT("<p:DesiredStream CommandId=\"685F47FF-64C7-46A4-BCCD-6D68B92BD405\">out1</p:DesiredStream>")
        ZT("</p:Receive>")
        ZT("</s:Body>")
        ZT("</s:Envelope>");
    XML xml;
    XML_Elem xmlstart;

    InitXml(&xml, bufferToParse);

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Need a batch")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&instance, PAL_T("Receive"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("685F47FF-64C7-46A4-BCCD-6D68B92BD405");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("CommandId"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("out1");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("DesiredStream"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, WSBuf_InstanceToBuf(USERAGENT_UNKNOWN, instance, NULL, NULL, NULL, batch, WSMAN_ObjectFlag|WSMAN_IsShellRequest, &instanceBuf, &instanceBufSize), PAL_T("Serializing instance")))
        goto cleanup;

    if (!NitsCompareString((MI_Char*) instanceBuf, expectedInstanceBuf, PAL_T("Expected serialized instance")))
        goto cleanup;

    XML_Next(&xml, &xmlstart);
    if (!NitsCompare(0, WS_ParseReceiveBody(&xml, batch, &parsedInstance), PAL_T("Parsing receive instance")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("DesiredStream"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompare(MI_INSTANCE, type, PAL_T("Desired state is not an instance")))
        goto cleanup;

    parsedInstanceDesiredState = value.instance;
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstanceDesiredState, PAL_T("CommandId"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("685F47FF-64C7-46A4-BCCD-6D68B92BD405"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstanceDesiredState, PAL_T("StreamName"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("out1"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

cleanup:
    if (batch)
        Batch_Delete(batch);

}
NitsEndTest

NitsTest(TestShellReceiveForCommandResponse)
{
    Batch *batch = NULL;
    MI_Instance *instance = NULL;
    MI_Instance *streamInstance = NULL;
    MI_Instance *commandStateInstance = NULL;
    MI_Instance *parsedInstance = NULL;
    MI_Instance *parsedEmbeddedInstance = NULL;
    MI_Value value;
    MI_Type type;
    MI_Uint32 flags;
    void *instanceBuf = NULL;
    MI_Uint32 instanceBufSize;
    MI_Char expectedInstanceBuf[] =
        ZT("<p:ReceiveResponse xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell\">")
        ZT("<p:Stream CommandId=\"685F47FF-64C7-46A4-BCCD-6D68B92BD405\" Name=\"out1\">streamData</p:Stream>")
        ZT("<p:CommandState CommandId=\"685F47FF-64C7-46A4-BCCD-6D68B92BD406\" State=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell/CommandState/Done\"></p:CommandState>")
        ZT("</p:ReceiveResponse>");
    XML xml;
    XML_Elem xmlstart;

    InitXml(&xml, expectedInstanceBuf);

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Need a batch")))
        goto cleanup;

   if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&streamInstance, PAL_T("Stream"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("685F47FF-64C7-46A4-BCCD-6D68B92BD405");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(streamInstance, PAL_T("CommandId"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("out1");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(streamInstance, PAL_T("streamName"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("streamData");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(streamInstance, PAL_T("data"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&commandStateInstance, PAL_T("CommandState"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("685F47FF-64C7-46A4-BCCD-6D68B92BD406");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(commandStateInstance, PAL_T("CommandId"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("http://schemas.microsoft.com/wbem/wsman/1/windows/shell/CommandState/Done");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(commandStateInstance, PAL_T("state"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&instance, PAL_T("Receive"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
        goto cleanup;

    value.instance = streamInstance;
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("Stream"), &value, MI_INSTANCE, MI_FLAG_BORROW), PAL_T("Add properties")))
        goto cleanup;

    value.instance = commandStateInstance;
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("CommandState"), &value, MI_INSTANCE, MI_FLAG_BORROW), PAL_T("Add properties")))
        goto cleanup;


    if (!NitsCompare(MI_RESULT_OK, WSBuf_InstanceToBuf(USERAGENT_UNKNOWN, instance, NULL, NULL, NULL, batch, WSMAN_ObjectFlag|WSMAN_IsShellResponse, &instanceBuf, &instanceBufSize), PAL_T("Serializing instance")))
        goto cleanup;

    if (!NitsCompareString((MI_Char*) instanceBuf, expectedInstanceBuf, PAL_T("Expected serialized instance")))
        goto cleanup;

    XML_Next(&xml, &xmlstart);
    if (!NitsCompare(0, WS_GetInstance(&xml, &xmlstart, batch, &parsedInstance, WSMANTAG_ACTION_SHELL_RECEIVE_RESPONSE), PAL_T("Parsing receive instance")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("Stream"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompare(MI_INSTANCE, type, PAL_T("Desired state is not an instance")))
        goto cleanup;

    parsedEmbeddedInstance = value.instance;
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedEmbeddedInstance, PAL_T("CommandId"), &value, &type, &flags, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("685F47FF-64C7-46A4-BCCD-6D68B92BD405"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedEmbeddedInstance, PAL_T("streamName"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("out1"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedEmbeddedInstance, PAL_T("data"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("streamData"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("CommandState"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompare(MI_INSTANCE, type, PAL_T("Desired state is not an instance")))
        goto cleanup;

    parsedEmbeddedInstance = value.instance;
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedEmbeddedInstance, PAL_T("CommandId"), &value, &type, &flags, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("685F47FF-64C7-46A4-BCCD-6D68B92BD406"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedEmbeddedInstance, PAL_T("state"), &value, &type, NULL, NULL), PAL_T("Validating command state")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("http://schemas.microsoft.com/wbem/wsman/1/windows/shell/CommandState/Done"), value.string, PAL_T("Validating command state")))
        goto cleanup;

cleanup:
    if (batch)
        Batch_Delete(batch);
}
NitsEndTest

NitsTest(TestShellSendForShellRequest)
{
    Batch *batch = NULL;
    MI_Instance *instance = NULL;
    MI_Instance *streamInstance = NULL;
    MI_Instance *parsedInstance = NULL;
    MI_Instance *parsedStream = NULL;
    MI_Value value;
    MI_Type type;
    void *instanceBuf = NULL;
    MI_Uint32 instanceBufSize;
    MI_Char expectedInstanceBuf[] =
        ZT("<p:Send xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell\">")
        ZT("<p:Stream Name=\"in1\">streamData</p:Stream>")
        ZT("</p:Send>");
    MI_Char bufferToParse[] =
        ZT("<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\">")
        ZT("<s:Body>")
        ZT("<p:Send xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell\">")
        ZT("<p:Stream Name=\"in1\">streamData</p:Stream>")
        ZT("</p:Send>")
        ZT("</s:Body>")
        ZT("</s:Envelope>");
    XML xml;
    XML_Elem xmlstart;

    InitXml(&xml, bufferToParse);

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Need a batch")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&instance, PAL_T("Send"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&streamInstance, PAL_T("Stream"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("in1");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(streamInstance, PAL_T("streamName"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("streamData");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(streamInstance, PAL_T("data"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.instance = streamInstance;
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("Stream"), &value, MI_INSTANCE, 0), PAL_T("Add properties")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, WSBuf_InstanceToBuf(USERAGENT_UNKNOWN, instance, NULL, NULL, NULL, batch, WSMAN_ObjectFlag|WSMAN_IsShellRequest, &instanceBuf, &instanceBufSize), PAL_T("Serializing instance")))
        goto cleanup;

    if (!NitsCompareString((MI_Char*) instanceBuf, expectedInstanceBuf, PAL_T("Expected serialized instance")))
        goto cleanup;

    XML_Next(&xml, &xmlstart);
    if (!NitsCompare(0, WS_ParseSendBody(&xml, batch, &parsedInstance), PAL_T("Parsing send instance")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("streamData"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompare(MI_INSTANCE, type, PAL_T("stream is not an instance")))
        goto cleanup;

    parsedStream = value.instance;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedStream, PAL_T("streamName"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("in1"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedStream, PAL_T("data"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("streamData"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

cleanup:
    if (batch)
        Batch_Delete(batch);
}
NitsEndTest

NitsTest(TestShellSendForCommandRequest)
{
    Batch *batch = NULL;
    MI_Instance *instance = NULL;
    MI_Instance *streamInstance = NULL;
    MI_Instance *parsedInstance = NULL;
    MI_Instance *parsedStream = NULL;
    MI_Value value;
    MI_Type type;
    void *instanceBuf = NULL;
    MI_Uint32 instanceBufSize;
    MI_Char expectedInstanceBuf[] =
        ZT("<p:Send xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell\">")
        ZT("<p:Stream CommandId=\"685F47FF-64C7-46A4-BCCD-6D68B92BD405\" Name=\"in1\">streamData</p:Stream>")
        ZT("</p:Send>");
    MI_Char bufferToParse[] =
        ZT("<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\">")
        ZT("<s:Body>")
        ZT("<p:Send xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell\">")
        ZT("<p:Stream CommandId=\"685F47FF-64C7-46A4-BCCD-6D68B92BD405\" Name=\"in1\">streamData</p:Stream>")
        ZT("</p:Send>")
        ZT("</s:Body>")
        ZT("</s:Envelope>");
    XML xml;
    XML_Elem xmlstart;

    InitXml(&xml, bufferToParse);

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Need a batch")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&instance, PAL_T("Send"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&streamInstance, PAL_T("Stream"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("685F47FF-64C7-46A4-BCCD-6D68B92BD405");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(streamInstance, PAL_T("CommandId"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("in1");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(streamInstance, PAL_T("streamName"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("streamData");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(streamInstance, PAL_T("data"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.instance = streamInstance;
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("Stream"), &value, MI_INSTANCE, 0), PAL_T("Add properties")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, WSBuf_InstanceToBuf(USERAGENT_UNKNOWN, instance, NULL, NULL, NULL, batch, WSMAN_ObjectFlag|WSMAN_IsShellRequest, &instanceBuf, &instanceBufSize), PAL_T("Serializing instance")))
        goto cleanup;

    if (!NitsCompareString((MI_Char*) instanceBuf, expectedInstanceBuf, PAL_T("Expected serialized instance")))
        goto cleanup;

    XML_Next(&xml, &xmlstart);
    if (!NitsCompare(0, WS_ParseSendBody(&xml, batch, &parsedInstance), PAL_T("Parsing send instance")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("streamData"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompare(MI_INSTANCE, type, PAL_T("stream is not an instance")))
        goto cleanup;

    parsedStream = value.instance;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedStream, PAL_T("CommandId"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("685F47FF-64C7-46A4-BCCD-6D68B92BD405"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedStream, PAL_T("streamName"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("in1"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedStream, PAL_T("data"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("streamData"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

cleanup:
    if (batch)
        Batch_Delete(batch);
}
NitsEndTest

NitsTest(TestShellSignalForShellRequest)
{
    Batch *batch = NULL;
    MI_Instance *instance = NULL;
    MI_Instance *parsedInstance = NULL;
    MI_Value value;
    MI_Type type;
    MI_Uint32 flag;
    void *instanceBuf = NULL;
    MI_Uint32 instanceBufSize;
    MI_Char expectedInstanceBuf[] =
        ZT("<p:Signal xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell\">")
        ZT("<p:Code>http://schemas.microsoft.com/wbem/wsman/1/windows/shell/signal/terminate</p:Code>")
        ZT("</p:Signal>");
    MI_Char bufferToParse[] =
        ZT("<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\">")
        ZT("<s:Body>")
        ZT("<p:Signal xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell\">")
        ZT("<p:Code>http://schemas.microsoft.com/wbem/wsman/1/windows/shell/signal/terminate</p:Code>")
        ZT("</p:Signal>")
        ZT("</s:Body>")
        ZT("</s:Envelope>");
    XML xml;
    XML_Elem xmlstart;

    InitXml(&xml, bufferToParse);

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Need a batch")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&instance, PAL_T("Signal"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("http://schemas.microsoft.com/wbem/wsman/1/windows/shell/signal/terminate");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("Code"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, WSBuf_InstanceToBuf(USERAGENT_UNKNOWN, instance, NULL, NULL, NULL, batch, WSMAN_ObjectFlag|WSMAN_IsShellRequest, &instanceBuf, &instanceBufSize), PAL_T("Serializing instance")))
        goto cleanup;

    if (!NitsCompareString((MI_Char*) instanceBuf, expectedInstanceBuf, PAL_T("Expected serialized instance")))
        goto cleanup;

    XML_Next(&xml, &xmlstart);
    if (!NitsCompare(0, WS_ParseSignalBody(&xml, batch, &parsedInstance), PAL_T("Parsing signal instance")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("CommandId"), &value, &type, &flag, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsAssert(MI_FLAG_NULL & flag, PAL_T("Validating input streams")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("Code"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("http://schemas.microsoft.com/wbem/wsman/1/windows/shell/signal/terminate"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

cleanup:
    if (batch)
        Batch_Delete(batch);

}
NitsEndTest

NitsTest(TestShellSignalForCommandRequest)
{
    Batch *batch = NULL;
    MI_Instance *instance = NULL;
    MI_Instance *parsedInstance = NULL;
    MI_Value value;
    MI_Type type;
    void *instanceBuf = NULL;
    MI_Uint32 instanceBufSize;
    MI_Char expectedInstanceBuf[] =
        ZT("<p:Signal CommandId=\"685F47FF-64C7-46A4-BCCD-6D68B92BD405\" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell\">")
        ZT("<p:Code>http://schemas.microsoft.com/wbem/wsman/1/windows/shell/signal/terminate</p:Code>")
        ZT("</p:Signal>");
    MI_Char bufferToParse[] =
        ZT("<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\">")
        ZT("<s:Body>")
        ZT("<p:Signal CommandId=\"685F47FF-64C7-46A4-BCCD-6D68B92BD405\" xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/windows/shell\">")
        ZT("<p:Code>http://schemas.microsoft.com/wbem/wsman/1/windows/shell/signal/terminate</p:Code>")
        ZT("</p:Signal>")
        ZT("</s:Body>")
        ZT("</s:Envelope>");
    XML xml;
    XML_Elem xmlstart;

    InitXml(&xml, bufferToParse);

    batch = Batch_New(BATCH_MAX_PAGES);
    if (!NitsAssert(batch != NULL, PAL_T("Need a batch")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, Instance_NewDynamic(&instance, PAL_T("Signal"), MI_FLAG_CLASS, batch), PAL_T("Unable to create new instance")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("685F47FF-64C7-46A4-BCCD-6D68B92BD405");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("CommandId"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    value.string = (MI_Char*) PAL_T("http://schemas.microsoft.com/wbem/wsman/1/windows/shell/signal/terminate");
    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_AddElement(instance, PAL_T("Code"), &value, MI_STRING, 0), PAL_T("Add properties")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, WSBuf_InstanceToBuf(USERAGENT_UNKNOWN, instance, NULL, NULL, NULL, batch, WSMAN_ObjectFlag|WSMAN_IsShellRequest, &instanceBuf, &instanceBufSize), PAL_T("Serializing instance")))
        goto cleanup;

    if (!NitsCompareString((MI_Char*) instanceBuf, expectedInstanceBuf, PAL_T("Expected serialized instance")))
        goto cleanup;

    XML_Next(&xml, &xmlstart);
    if (!NitsCompare(0, WS_ParseSignalBody(&xml, batch, &parsedInstance), PAL_T("Parsing signal instance")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("CommandId"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("685F47FF-64C7-46A4-BCCD-6D68B92BD405"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

    if (!NitsCompare(MI_RESULT_OK, __MI_Instance_GetElement(parsedInstance, PAL_T("Code"), &value, &type, NULL, NULL), PAL_T("Validating property")))
        goto cleanup;

    if (!NitsCompareString(PAL_T("http://schemas.microsoft.com/wbem/wsman/1/windows/shell/signal/terminate"), value.string, PAL_T("Validating input streams")))
        goto cleanup;

cleanup:
    if (batch)
        Batch_Delete(batch);

}
NitsEndTest

#endif

