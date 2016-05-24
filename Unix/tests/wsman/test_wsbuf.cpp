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
#include <xml/xml.h>
#include <wsman/wsbuf.h>
#include <base/helpers.h>
#include <pal/format.h>

using namespace std;

#if defined(CONFIG_ENABLE_WCHAR)
typedef std::wstring String;
#else
typedef std::string String;
#endif

WSBuf   s_buf;

NitsSetup(TestWsbufSetup)
NitsEndSetup

NitsCleanup(TestWsbufSetup)
NitsEndCleanup

#define TEST_STR_CHAR "`';\"\\!@#$%^&*()_+<>"
#define TEST_STR MI_T("`';\"\\!@#$%^&*()_+<>")
#define TEST_STR_ENCODED PAL_T("`&apos;;&quot;\\!@#$%^&amp;*()_+&lt;&gt;")

#if defined(CONFIG_ENABLE_WCHAR)
typedef std::wstring String;
#else
typedef std::string String;
#endif

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
    ZChar expected[1024];
    ZChar interval[64];

    const MI_Char *output;

    MI_Datetime timeout;
    memset((void*)&timeout, 0, sizeof(MI_Datetime));
    timeout.u.interval.seconds = 30;

    if(!NitsAssert (MI_RESULT_OK == WSBuf_Init(&s_buf, 1024), PAL_T("Unable to initialize buffer")))
    {
        goto cleanup;
    }

    //Create the WsmanCliHeaders structure to pass into the header creation 
    WsmanCliHeaders cliHeaders;  
    cliHeaders.maxEnvelopeSize = 32761;
    cliHeaders.toAddress = ZT("http://localhost:5985/wsman");
    cliHeaders.locale = ZT("en-US");
    cliHeaders.datalocale = NULL;
    cliHeaders.operationTimeout = &timeout;
    cliHeaders.action = ZT("http://schemas.xmlsoap.org/ws/2004/09/transfer/Get");
    cliHeaders.flags = 1; 
    cliHeaders.resourceUri = ZT("http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/X_smallNumber");

    if(!NitsAssert( MI_RESULT_OK == GetMessageRequest(&s_buf, &cliHeaders), PAL_T ("Create Get request failed.")))
    {
        goto cleanup;
    } 

    output = BufData(&s_buf);

    FormatWSManDatetime(cliHeaders.operationTimeout, interval);

    Tcslcpy(expected, LIT(ZT("<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\" ")
                          ZT("xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" ")
                          ZT("xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" ")
                          ZT("xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\" >")
                          ZT("<s:Header>")));
    NitsCompareSubstring(output, expected, "Envelope and Header");

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<a:To><a:Address s:mustUnderstand=\"true\">%s</a:Address></a:To>"),
             cliHeaders.toAddress);
    NitsCompareSubstring(output, expected, "To Address");

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<w:ResourceURI s:mustUnderstand=\"true\">%s</w:ResourceURI>"),
             cliHeaders.resourceUri);
    NitsCompareSubstring(output, expected, "ResourceURI");

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<a:ReplyTo><a:Address s:mustUnderstand=\"true\">%s</a:Address></a:ReplyTo>"),
             ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous"));
    NitsCompareSubstring(output, expected, "ReplyTo");

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<a:Action>%s</a:Action>"),
             cliHeaders.action);
    NitsCompareSubstring(output, expected, "Action");

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<w:MaxEnvelopeSize s:mustUnderstand=\"true\">%d</w:MaxEnvelopeSize>"),
             cliHeaders.maxEnvelopeSize);
    NitsCompareSubstring(output, expected, "MaxEnvelopeSize");

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<w:OperationTimeout>%s</w:OperationTimeout>"),
             interval);
    NitsCompareSubstring(output, expected, "OperationTimeout");

    Stprintf(expected, MI_COUNT(expected), 
             ZT("<w:Locale xml:lang=\"%s\" s:mustUnderstand=\"false\"/>"),
             cliHeaders.locale);
    NitsCompareSubstring(output, expected, "Locale");

    Tcslcpy(expected, LIT(ZT("</s:Header><s:Body></s:Body></s:Envelope>")));
    NitsCompareSubstring(output, expected, "End Tags");

cleanup:  
    NitsAssert (MI_RESULT_OK == WSBuf_Destroy(&s_buf), PAL_T("WSBuf_Destroy failed"));        //destroy buff
    
}
NitsEndTest


