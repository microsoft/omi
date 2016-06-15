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
#include <pal/dir.h>
#include <pal/file.h>
#include <base/paths.h>
#include <cstdio>

#if 0
# define DUMP_XML
#endif

#if defined(_MSC_VER)
/* PreFast - reviewed and believed to be false-positive*/

/* warning C6262: Function uses '21344' bytes of stack: exceeds /analyze:stacksize'16384'. Consider moving some data to heap */
//# pragma warning(disable : 6262)

#endif /* _MSC_VER */

using namespace std;

NitsSetup(TestXmlSetup)
NitsEndSetup

NitsCleanup(TestXmlSetup)
NitsEndCleanup

NitsTestWithSetup(Test0, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    XML_Char data[] = PAL_T("<a>       one         </a>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(r == 1);
    PAL_Free(xml);
}
NitsEndTest

NitsTestWithSetup(Test1, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    size_t i = 0;
    XML_Char data[] = PAL_T("<a><b><c></c></b></a>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
        switch (i)
        {
            case 0:
            {
                UT_ASSERT(Tcscmp(e.data.data, PAL_T("a")) == 0);
                UT_ASSERT(e.type == XML_START);
                break;
            }
            case 1:
            {
                UT_ASSERT(Tcscmp(e.data.data, PAL_T("b")) == 0);
                UT_ASSERT(e.type == XML_START);
                break;
            }
            case 2:
            {
                UT_ASSERT(Tcscmp(e.data.data, PAL_T("c")) == 0);
                UT_ASSERT(e.type == XML_START);
                break;
            }
            case 3:
            {
                UT_ASSERT(Tcscmp(e.data.data, PAL_T("c")) == 0);
                UT_ASSERT(e.type == XML_END);
                break;
            }
            case 4:
            {
                UT_ASSERT(Tcscmp(e.data.data, PAL_T("b")) == 0);
                UT_ASSERT(e.type == XML_END);
                break;
            }
            case 5:
            {
                UT_ASSERT(Tcscmp(e.data.data, PAL_T("a")) == 0);
                UT_ASSERT(e.type == XML_END);
                break;
            }
        }

        i++;
    }

    UT_ASSERT(r == 1);
	PAL_Free(xml);
}
NitsEndTest

NitsTestWithSetup(Test2, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    XML_Char data[] = PAL_T("<a>   <b>   bbb   <c>   ccc    </c> BBB</b> AAA</a>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
    }

    UT_ASSERT(r == 1);
	PAL_Free(xml);
}
NitsEndTest

NitsTestWithSetup(Test3, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    XML_Char data[] = PAL_T("<a><b>   &lt;&#65;&#66;&#67;&gt;&#x41;   </b></a>");
    size_t i = 0;

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
        if (i == 2)
        {
            UT_ASSERT(e.type == XML_CHARS);
            UT_ASSERT(Tcscmp(e.data.data, PAL_T("   <ABC>A   ")) == 0);
            UT_ASSERT(XML_StripWhitespace(&e) == 0);
            UT_ASSERT(Tcscmp(e.data.data, PAL_T("<ABC>A")) == 0);

        }

        i++;
    }

    UT_ASSERT(i == 5);
    UT_ASSERT(r == 1);
    PAL_Free(xml);
}
NitsEndTest

/* Test more than one root element */
NitsTestWithSetup(Test4, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    XML_Char data[] = PAL_T("<a></a><a></a>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
        ;

    UT_ASSERT(r == 1);
    PAL_Free(xml);
}
NitsEndTest

/* Test attributes */
NitsTestWithSetup(Test5, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    XML_Char data[] = PAL_T("<a x=\"1\" y = \"22\" zzz = \"1234\">Stuff</a>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(r == 1);
    PAL_Free(xml);
}
NitsEndTest

/* Test empty tags */
NitsTestWithSetup(Test6, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    XML_Char data[] = PAL_T("<a><b/></a>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(r == 1);
    PAL_Free(xml);
}
NitsEndTest

/* Test Person example */
NitsTestWithSetup(Test7, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    const XML_Char* tag = NULL;
    const XML_Char* first = NULL;
    const XML_Char* last = NULL;
    size_t i;
    XML_Char data[] = 
        PAL_T("<Person First='George' Last='Washington' Char='&lt;'>\n")
        PAL_T("</Person>\n");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
        if (e.type == XML_START && Tcscmp(e.data.data, PAL_T("Person")) == 0)
        {
            tag = e.data.data;

            for (i = 0; i < e.attrsSize; i++)
            {
                if (Tcscmp(e.attrs[i].name.data, PAL_T("First")) == 0)
                    first = e.attrs[i].value;
                if (Tcscmp(e.attrs[i].name.data, PAL_T("Last")) == 0)
                    last = e.attrs[i].value;
            }
        }
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(tag != 0 && Tcscmp(tag, PAL_T("Person")) == 0);
    UT_ASSERT(Tcscmp(first, PAL_T("George")) == 0);
    UT_ASSERT(Tcscmp(last, PAL_T("Washington")) == 0);

    UT_ASSERT(r == 1);
    PAL_Free(xml);
}
NitsEndTest

/* Test comments */
NitsTestWithSetup(Test8, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    XML_Char data[] = 
        PAL_T("<!-- blah blah blah --><a><!--hello-->Stuff</a>");
    bool foundComment1 = false;
    bool foundComment2 = false;

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
        if (e.type == XML_COMMENT)
        {
            if (Tcscmp(e.data.data, PAL_T(" blah blah blah ")) == 0)
            {
                foundComment1 = true;
            }
            else if (Tcscmp(e.data.data, PAL_T("hello")) == 0)
            {
                foundComment2 = true;
            }
        }
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(foundComment1);
    UT_ASSERT(foundComment2);
    UT_ASSERT(r == 1);
    PAL_Free(xml);
}
NitsEndTest

/* Test <![CDATA[...]]> */
NitsTestWithSetup(Test9, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    XML_Char data[] = PAL_T("<a><![CDATA[blah]]></a>");
    bool found = false;

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
        if (e.type == XML_CHARS)
        {
            if (Tcscmp(e.data.data, PAL_T("blah")) == 0)
            {
                found = true;
            }
        }

#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(found);
    UT_ASSERT(r == 1);
    PAL_Free(xml);
}
NitsEndTest

/* Test DOCTYPE element */
NitsTestWithSetup(Test10, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    XML_Char data[] = PAL_T("<!DOCTYPE ingore me><a><!DOCTYPE ingore me></a>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(r == 1);
    PAL_Free(xml);
}
NitsEndTest

/* Test processing instruction */
NitsTestWithSetup(Test11, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    XML_Char data[] = 
        PAL_T("<?xml version='1.0' encoding='UTF-8' standalone='yes'?>")
        PAL_T("<a>content</a>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(r == 1);
    PAL_Free(xml);
}
NitsEndTest

/* Test tag names */
NitsTestWithSetup(Test12, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    XML_Char data[] = 
        PAL_T("<b-c.d></b-c.d>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(r == 1);
    PAL_Free(xml);
}
NitsEndTest

/* Test tag names */
NitsTestWithSetup(Test13, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    XML_Char data[] = 
        PAL_T("<ns1:tag xmlns:ns1='http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd'>")
        PAL_T("    <ns2:tag xmlns:ns2='http://microsoft.com/ns2'>")
        PAL_T("    </ns2:tag>")
        PAL_T("</ns1:tag>");

    XML_Init(xml);
    XML_SetText(xml, data);

    XML_RegisterNameSpace(xml, 'w',
        PAL_T("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd"));

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(r == 1);
    PAL_Free(xml);
}
NitsEndTest

static bool Inhale(const char* path, vector<XML_Char>& wdata)
{
    vector<char> data;
    string tmp = OMI_GetPath(ID_PREFIX);
    tmp += "/tests/xml/";
    tmp += path;
    FILE* is = File_Open(tmp.c_str(), "r");

    if (!is)
        return false;

    size_t n;
    char buf[4096];

    while ((n = fread(buf, 1, sizeof(buf), is)) != 0)
    {
        data.insert(data.end(), buf, buf + n);
    }

    data.push_back('\0');

    File_Close(is);

    for (size_t i = 0; i < data.size(); i++)
        wdata.push_back(data[i]);

    return true;
}

NitsTestWithSetup(Test14, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    vector<XML_Char> data;
    vector<XML_Elem> elems;

    UT_ASSERT(Inhale("test14.xml", data));

    XML_Init(xml);
    XML_SetText(xml, &data[0]);

    r = XML_RegisterNameSpace(xml, 'a', PAL_T("auri"));
    UT_ASSERT(r == 0);
    r = XML_RegisterNameSpace(xml, 'b', PAL_T("buri"));
    UT_ASSERT(r == 0);
    r = XML_RegisterNameSpace(xml, 'c', PAL_T("curi"));
    UT_ASSERT(r == 0);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
        elems.push_back(e);
    }

    UT_ASSERT(r == 1);
    UT_ASSERT(elems.size() == 27);

    if (r == 1 && elems.size() == 27)
    {
        UT_ASSERT(elems[0].type == XML_START && Tcscmp(elems[0].data.data, PAL_T("root")) == 0);

        UT_ASSERT(elems[1].type == XML_CHARS);

        UT_ASSERT(elems[2].type == XML_START && 
                  'a' == elems[2].data.namespaceId && 
                  Tcscmp(elems[2].data.namespaceUri, PAL_T("auri")) == 0 &&
                  Tcscmp(elems[2].data.data, PAL_T("anvil")) == 0);

        UT_ASSERT(elems[3].type == XML_CHARS);

        UT_ASSERT(elems[4].type == XML_START && 
                  'a' == elems[4].data.namespaceId && 
                  Tcscmp(elems[4].data.namespaceUri, PAL_T("auri")) == 0 &&
                  Tcscmp(elems[4].data.data, PAL_T("apple")) == 0);
        UT_ASSERT(elems[4].attrsSize == 2);
        UT_ASSERT('a' == elems[4].attrs[0].name.namespaceId && 
                  Tcscmp(elems[4].attrs[0].name.namespaceUri, PAL_T("auri")) == 0 && 
                  Tcscmp(elems[4].attrs[0].name.data, PAL_T("color")) == 0);
        UT_ASSERT(Tcscmp(elems[4].attrs[0].value, PAL_T("Red")) == 0);
        UT_ASSERT('a' == elems[4].attrs[1].name.namespaceId && 
                  Tcscmp(elems[4].attrs[1].name.namespaceUri, PAL_T("auri")) == 0 && 
                  Tcscmp(elems[4].attrs[1].name.data, PAL_T("size")) == 0);
        UT_ASSERT(Tcscmp(elems[4].attrs[1].value, PAL_T("100")) == 0);

        UT_ASSERT(elems[5].type == XML_CHARS);

        UT_ASSERT(elems[6].type == XML_START && 
                  'b' == elems[6].data.namespaceId && 
                  Tcscmp(elems[6].data.data, PAL_T("bat")) == 0);
        UT_ASSERT(elems[7].type == XML_CHARS);
        UT_ASSERT(elems[8].type == XML_START && 
                  'c' == elems[8].data.namespaceId && 
                  Tcscmp(elems[8].data.data, PAL_T("cat")) == 0);
        UT_ASSERT(elems[9].type == XML_CHARS);
        UT_ASSERT(elems[10].type == XML_START && 
                  0 == elems[10].data.namespaceId  && 
                  Tcscmp(elems[10].data.namespaceUri, PAL_T("unknownuri")) == 0 && Tcscmp(elems[10].data.data, PAL_T("dog")) == 0);
        UT_ASSERT(elems[11].type == XML_CHARS);
        UT_ASSERT(elems[12].type == XML_START && 
                  0 == elems[12].data.namespaceId  && 
                  Tcscmp(elems[12].data.namespaceUri, PAL_T("euri")) == 0 && Tcscmp(elems[12].data.data, PAL_T("egg")) == 0);
        UT_ASSERT(elems[13].type == XML_CHARS);
        UT_ASSERT(elems[14].type == XML_END && 
                  0 == elems[14].data.namespaceId  && 
                  Tcscmp(elems[14].data.namespaceUri, PAL_T("euri")) == 0 && Tcscmp(elems[14].data.data, PAL_T("egg")) == 0);
        UT_ASSERT(elems[15].type == XML_CHARS);
        UT_ASSERT(elems[16].type == XML_END && 
                  0 == elems[16].data.namespaceId  && 
                  Tcscmp(elems[16].data.namespaceUri, PAL_T("unknownuri")) == 0 && Tcscmp(elems[16].data.data, PAL_T("dog")) == 0);
        UT_ASSERT(elems[17].type == XML_CHARS);
        UT_ASSERT(elems[18].type == XML_END && 
                  'c' == elems[18].data.namespaceId && 
                  Tcscmp(elems[18].data.data, PAL_T("cat")) == 0);
        UT_ASSERT(elems[19].type == XML_CHARS);
        UT_ASSERT(elems[20].type == XML_END && 
                  'b' == elems[20].data.namespaceId && 
                  Tcscmp(elems[20].data.data, PAL_T("bat")) == 0);
        UT_ASSERT(elems[21].type == XML_CHARS);
        UT_ASSERT(elems[22].type == XML_END && 
                  'a' == elems[22].data.namespaceId && 
                  Tcscmp(elems[22].data.data, PAL_T("apple")) == 0);
        UT_ASSERT(elems[23].type == XML_CHARS);
        UT_ASSERT(elems[24].type == XML_END && 
                  'a' == elems[24].data.namespaceId && 
                  Tcscmp(elems[24].data.data, PAL_T("anvil")) == 0);
        UT_ASSERT(elems[25].type == XML_CHARS);
        UT_ASSERT(elems[26].type == XML_END&& 
                  Tcscmp(elems[26].data.data, PAL_T("root")) == 0);
    }
	PAL_Free(xml);
}
NitsEndTest

/* Test tag names */
NitsTestWithSetup(Test15, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    XML_Char data[] = 
        PAL_T("<apple:root xmlns:apple='http://ns.com/a'>")
        PAL_T("    <apple:part apple:color='Red'>")
        PAL_T("    </apple:part>")
        PAL_T("</apple:root>");

    XML_Init(xml);
    XML_SetText(xml, data);

    XML_RegisterNameSpace(xml, 'a', PAL_T("http://ns.com/a"));

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(r == 1);
    PAL_Free(xml);
}
NitsEndTest

static void TestFile(const char* path, _Out_writes_z_(size) XML_Char* msg, _In_ size_t size)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); 
    if(!TEST_ASSERT(xml != NULL)) {*msg = PAL_T('\0'); return;}
    int r;
    XML_Elem e;
    vector<XML_Char> data;

    bool flag = Inhale(path, data);
    UT_ASSERT(flag == true);

    UT_ASSERT(data.size() != 0);

    XML_Init(xml);
    XML_SetText(xml, &data[0]);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    XML_FormatError(xml, msg, size);
    PAL_Free(xml);
}

NitsTestWithSetup(Test16, TestXmlSetup)
{
    XML_Char msg[1024];
    TestFile("test16.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Tcscmp(msg, PAL_T("4: error: Failed to parse XML. An attribute name was expected.")) == 0);
}
NitsEndTest

NitsTestWithSetup(Test17, TestXmlSetup)
{
    XML_Char msg[1024];
    TestFile("test17.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Tcscmp(msg, PAL_T("1: error: Failed to parse XML. An '=' character was expected while parsing attribute 'a'.")) == 0);
}
NitsEndTest

NitsTestWithSetup(Test18, TestXmlSetup)
{
    XML_Char msg[1024];
    TestFile("test18.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Tcscmp(msg, PAL_T("2: error: Failed to parse XML. An opening quote character was expected while parsing attribute 'a'.")) == 0);
}
NitsEndTest

NitsTestWithSetup(Test19, TestXmlSetup)
{
    XML_Char msg[1024];
    TestFile("test19.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Tcscmp(msg, PAL_T("2: error: Failed to parse XML. Bad entity reference. Only these are supported: '&lt;', '&gt;', '&amp;', '&quot;', '&apos;'.")) == 0);
}
NitsEndTest

NitsTestWithSetup(Test20, TestXmlSetup)
{
    XML_Char msg[1024];
    TestFile("test20.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Tcscmp(msg, PAL_T("3: error: Failed to parse XML. Bad character reference. Only character references in the range of 0 to 255 are supported.")) == 0);
}
NitsEndTest

NitsTestWithSetup(Test21, TestXmlSetup)
{
    XML_Char msg[1024];
    TestFile("test21.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Tcscmp(msg, PAL_T("6: error: Failed to parse XML. An closing quote character was expected while parsing attribute 'x'.")) == 0);
}
NitsEndTest

NitsTestWithSetup(Test22, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    XML_Char data[] = 
        PAL_T("<tag xmlns=\"URI\"></a>");

    XML_Init(xml);
    XML_SetText(xml, data);

    r = XML_Next(xml, &e);

    UT_ASSERT(r == 0 &&
              e.type == XML_START &&
              Tcscmp(e.data.namespaceUri, PAL_T("URI")) == 0);

    PAL_Free(xml);
}
NitsEndTest

NitsTestWithSetup(Test23, TestXmlSetup)
{
    XML_Char msg[1024];
    TestFile("test23.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Tcscmp(msg, PAL_T("33: error: Failed to parse XML. Too many namespaces were detected. A maximum of 32 namespaces are allowed.")) == 0);
}
NitsEndTest

NitsTestWithSetup(Test24, TestXmlSetup)
{
    XML_Char msg[1024];
    TestFile("test24.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Tcscmp(msg, PAL_T("34: error: Failed to parse XML. Too many attributes were detected on element 'a'. A maximum of 32 attributes are allowed per element.")) == 0);
}
NitsEndTest

NitsTestWithSetup(Test25, TestXmlSetup)
{
    XML_Char msg[1024];
    TestFile("test25.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Tcscmp(msg, PAL_T("5: error: Failed to parse XML. The XML element end tag expected was 'a', but what was found was 'root'.")) == 0);
}
NitsEndTest

NitsTestWithSetup(Test26, TestXmlSetup)
{
    XML_Char msg[1024];
    TestFile("test26.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Tcscmp(msg, PAL_T("3: error: Failed to parse XML. The XML element end tag expected was 'a', but what was found was 'b'.")) == 0);
}
NitsEndTest

NitsTestWithSetup(Test27, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    XML_Char data[] = PAL_T("<root></root><root></root>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(r == 1);
	PAL_Free(xml);
}
NitsEndTest

NitsTestWithSetup(Test28, TestXmlSetup)
{
    XML_Char msg[1024];
    TestFile("test28.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Tcscmp(msg, PAL_T("5: error: Failed to parse XML. While processing the element data no element end tag was discovered.")) == 0);
}
NitsEndTest

NitsTestWithSetup(Test29, TestXmlSetup)
{
    XML_Char msg[1024];
    TestFile("test29.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Tcscmp(msg, PAL_T("1: error: Failed to parse XML. An open angle bracket '<' was expected and not found.")) == 0);
}
NitsEndTest

NitsTestWithSetup(Test30, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    size_t i = 0;
    vector<XML_Char> data;

    bool flag = Inhale("test30.xml", data);
    UT_ASSERT(flag == true);

    UT_ASSERT(data.size() != 0);
    XML_Init(xml);
    XML_SetText(xml, &data[0]);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
        if (i == 2)
        {
            UT_ASSERT(Tcscmp(e.data.data, PAL_T("{{{<a><b></b></a>}}}")) == 0);
        }
        i++;
    }
    UT_ASSERT_EQUAL(i, 5);

    UT_ASSERT_EQUAL(r, 1);

	PAL_Free(xml);
}
NitsEndTest

NitsTestWithSetup(Test31, TestXmlSetup)
{
    XML_Char msg[1024];
    TestFile("test31.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Tcscmp(msg, PAL_T("")) == 0);
}
NitsEndTest

NitsTestWithSetup(Test32, TestXmlSetup)
{
    XML_Char msg[1024];
    TestFile("test32.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Tcscmp(msg, PAL_T("29: error: Failed to parse XML. The XML element end tag expected was 'a', but what was found was 'b'.")) == 0);
}
NitsEndTest

NitsTestWithSetup(Test33, TestXmlSetup)
{
    XML_Char msg[1024];
    TestFile("test33.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Tcscmp(msg, PAL_T("28: error: Failed to parse XML. An attribute name was expected.")) == 0);
}
NitsEndTest

// Test newline character
NitsTestWithSetup(Test34, TestXmlSetup)
{
    XML * xml = (XML *) PAL_Malloc(sizeof(XML)); if(!TEST_ASSERT(xml != NULL)) NitsReturn;
    int r;
    XML_Elem e;
    XML_Char data[] = PAL_T("<a>\n<b>\n   &lt;&#65;&#66;&#67;&gt;&#x41;   </b></a>");
    size_t i = 0;

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
        if (i == 2)
        {
            UT_ASSERT(e.type == XML_CHARS);
            UT_ASSERT(Tcscmp(e.data.data, PAL_T("   <ABC>A   ")) == 0);
        }

        i++;
    }

    UT_ASSERT(i == 5);
    UT_ASSERT(r == 1);
    PAL_Free(xml);
}
NitsEndTest



