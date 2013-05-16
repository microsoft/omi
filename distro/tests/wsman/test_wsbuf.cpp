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
#include <xml/xml.h>
#include <wsman/wsbuf.h>
#include <ut/ut.h>

using namespace std;

#if defined(CONFIG_ENABLE_WCHAR)
typedef std::wstring String;
#else
typedef std::string String;
#endif

WSBuf   s_buf;

static void setUp()
{
    UT_ASSERT (MI_RESULT_OK == WSBuf_Init(&s_buf, 10));
}

static void cleanup()
{
    UT_ASSERT (MI_RESULT_OK == WSBuf_Destroy(&s_buf));
}

#define TEST_STR_CHAR "`';\"\\!@#$%^&*()_+<>"
#define TEST_STR MI_T("`';\"\\!@#$%^&*()_+<>")
#define TEST_STR_ENCODED ZT("`&apos;;&quot;\\!@#$%^&amp;*()_+&lt;&gt;")

#if defined(CONFIG_ENABLE_WCHAR)
typedef std::wstring String;
#else
typedef std::string String;
#endif

static void TestXMLStringEncoding()
{
    String result;

    for ( unsigned int i = 0; i < 100; i++ )
    {
        result += TEST_STR_ENCODED;
        UT_ASSERT (MI_RESULT_OK == WSBuf_AddString(&s_buf, TEST_STR) );
    }

    Page* p = WSBuf_StealPage(&s_buf);
    UT_ASSERT(0 != p);

    /* content expected to be 0-terminated */
    String buf_result( (const ZChar*) (p + 1) );
    //cout << buf_result << endl;
    UT_ASSERT(result == buf_result);

    free(p);
}

static void TestToFromXML()
{
    String result;

    UT_ASSERT (MI_RESULT_OK == WSBuf_AddStringNoEncoding(&s_buf, MI_T("<a>")) );

    for ( unsigned int i = 0; i < 100; i++ )
    {
        result += TEST_STR;
        UT_ASSERT (MI_RESULT_OK == WSBuf_AddString(&s_buf, TEST_STR) );
    }

    UT_ASSERT (MI_RESULT_OK == WSBuf_AddStringNoEncoding(&s_buf, MI_T("</a>")) );

    Page* p = WSBuf_StealPage(&s_buf);
    UT_ASSERT(0 != p);


    /* create xml */
    XML * xml = (XML *) malloc(sizeof(XML));
    XML_Elem e;

    XML_Init(xml);
    XML_SetText(xml, (ZChar*) (p + 1));

    UT_ASSERT(0 == XML_Next(xml, &e));
    UT_ASSERT(Zcmp(e.data, ZT("a")) == 0);
    UT_ASSERT(e.type == XML_START);

    UT_ASSERT(0 == XML_Next(xml, &e));
    UT_ASSERT(e.type == XML_CHARS);
    UT_ASSERT(result == e.data);

    UT_ASSERT(0 == XML_Next(xml, &e));
    UT_ASSERT(Zcmp(e.data, ZT("a")) == 0);
    UT_ASSERT(e.type == XML_END);

    free(p);
    free(xml);
}

static void TestWSBuf()
{
    // general errors
    UT_TEST(TestXMLStringEncoding);
    UT_TEST(TestToFromXML);
}

UT_ENTRY_POINT(TestWSBuf);
