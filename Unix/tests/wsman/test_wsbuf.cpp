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
  WSBuf buf;    
  MI_Uint32 maxEnvelopeSize = 32761;    
  const MI_Char* language = ZT("en-US");
  const MI_Char* toAddress = ZT("http://localhost:5985/wsman");
  const MI_Char* uri = ZT("http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/X_smallNumber");

  MI_Datetime timeout;
  memset((void*)&timeout, 0, sizeof(MI_Datetime));
  timeout.u.interval.seconds = 30;

  GetInstanceReq *msg = NULL;

  if(!NitsAssert (MI_RESULT_OK == WSBuf_Init(&buf, 1024), PAL_T("Unable to initialize buffer")))
  {
      goto cleanup;
  }

  //Create the WsmanCliHeaders structure to pass into the header creation 
  WsmanCliHeaders cliHeaders;  
  cliHeaders.maxEnvelopeSize = maxEnvelopeSize;
  cliHeaders.toAddress = toAddress;
  cliHeaders.locale = language; 
  cliHeaders.datalocale = NULL;
  cliHeaders.operationTimeout = &timeout;
  cliHeaders.action = ZT("http://schemas.xmlsoap.org/ws/2004/09/transfer/Get");
  cliHeaders.flags = 1; 
  cliHeaders.resourceUri = uri;

  if(!NitsAssert( MI_RESULT_OK == GetMessageRequest(&buf, &cliHeaders, msg), PAL_T ("Create Get request failed.")))
  {
      goto cleanup;
  } 

  //printf("buffer in TestGetRequest: %s", BufData(&buf));       

 cleanup:  
  NitsAssert (MI_RESULT_OK == WSBuf_Destroy(&s_buf), PAL_T("WSBuf_Destroy failed"));        //destroy buff
    
}
NitsEndTest


