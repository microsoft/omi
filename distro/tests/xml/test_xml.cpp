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

#include <iostream>
#include <string>
#include <vector>
#include <ut/ut.h>
#include <common.h>
#include <xml/xml.h>
#include <base/strings.h>
#include <base/dir.h>
#include <base/paths.h>
#include <cstdio>
#include <io/io.h>

#if 0
# define DUMP_XML
#endif

#if defined(_MSC_VER)
/* PreFast - reviewed and believed to be false-positive*/

/* warning C6262: Function uses '21344' bytes of stack: exceeds /analyze:stacksize'16384'. Consider moving some data to heap */
//# pragma warning(disable : 6262)

#endif /* _MSC_VER */

using namespace std;

static void setUp()
{
}

static void cleanup()
{
}

static void Test0()
{
    XML * xml = (XML *) malloc(sizeof(XML));
    int r;
    XML_Elem e;
    XML_Char data[] = ZT("<a>       one         </a>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(r == 1);
    free(xml);
}

static void Test1()
{
    XML * xml = (XML *) malloc(sizeof(XML));
    int r;
    XML_Elem e;
    size_t i = 0;
    XML_Char data[] = ZT("<a><b><c></c></b></a>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
        switch (i)
        {
            case 0:
            {
                UT_ASSERT(Zcmp(e.data, ZT("a")) == 0);
                UT_ASSERT(e.type == XML_START);
                break;
            }
            case 1:
            {
                UT_ASSERT(Zcmp(e.data, ZT("b")) == 0);
                UT_ASSERT(e.type == XML_START);
                break;
            }
            case 2:
            {
                UT_ASSERT(Zcmp(e.data, ZT("c")) == 0);
                UT_ASSERT(e.type == XML_START);
                break;
            }
            case 3:
            {
                UT_ASSERT(Zcmp(e.data, ZT("c")) == 0);
                UT_ASSERT(e.type == XML_END);
                break;
            }
            case 4:
            {
                UT_ASSERT(Zcmp(e.data, ZT("b")) == 0);
                UT_ASSERT(e.type == XML_END);
                break;
            }
            case 5:
            {
                UT_ASSERT(Zcmp(e.data, ZT("a")) == 0);
                UT_ASSERT(e.type == XML_END);
                break;
            }
        }

        i++;
    }

    UT_ASSERT(r == 1);
    free(xml);
}

static void Test2()
{
    XML * xml = (XML *) malloc(sizeof(XML));
    int r;
    XML_Elem e;
    XML_Char data[] = ZT("<a>   <b>   bbb   <c>   ccc    </c> BBB</b> AAA</a>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
    }

    UT_ASSERT(r == 1);
    free(xml);
}

static void Test3()
{
    XML * xml = (XML *) malloc(sizeof(XML));
    int r;
    XML_Elem e;
    XML_Char data[] = ZT("<a><b>   &lt;&#65;&#66;&#67;&gt;&#x41;   </b></a>");
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
            UT_ASSERT(Zcmp(e.data, ZT("<ABC>A")) == 0);
        }

        i++;
    }

    UT_ASSERT(i == 5);
    UT_ASSERT(r == 1);
    free(xml);
}

/* Test more than one root element */
static void Test4()
{
    XML * xml = (XML *) malloc(sizeof(XML));
    int r;
    XML_Elem e;
    XML_Char data[] = ZT("<a></a><a></a>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
        ;

    UT_ASSERT(r == -1);
    free(xml);
}

/* Test attributes */
static void Test5()
{
    XML * xml = (XML *) malloc(sizeof(XML));
    int r;
    XML_Elem e;
    XML_Char data[] = ZT("<a x=\"1\" y = \"22\" zzz = \"1234\">Stuff</a>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(r == 1);
    free(xml);
}

/* Test empty tags */
static void Test6()
{
    XML * xml = (XML *) malloc(sizeof(XML));
    int r;
    XML_Elem e;
    XML_Char data[] = ZT("<a><b/></a>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(r == 1);
    free(xml);
}

/* Test Person example */
static void Test7()
{
    XML * xml = (XML *) malloc(sizeof(XML));
    int r;
    XML_Elem e;
    const XML_Char* tag = NULL;
    const XML_Char* first = NULL;
    const XML_Char* last = NULL;
    size_t i;
    XML_Char data[] = 
        ZT("<Person First='George' Last='Washington' Char='&lt;'>\n")
        ZT("</Person>\n");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
        if (e.type == XML_START && Zcmp(e.data, ZT("Person")) == 0)
        {
            tag = e.data;

            for (i = 0; i < e.attrsSize; i++)
            {
                if (Zcmp(e.attrs[i].name, ZT("First")) == 0)
                    first = e.attrs[i].value;
                if (Zcmp(e.attrs[i].name, ZT("Last")) == 0)
                    last = e.attrs[i].value;
            }
        }
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(tag != 0 && Zcmp(tag, ZT("Person")) == 0);
    UT_ASSERT(Zcmp(first, ZT("George")) == 0);
    UT_ASSERT(Zcmp(last, ZT("Washington")) == 0);

    UT_ASSERT(r == 1);
    free(xml);
}

/* Test comments */
static void Test8()
{
    XML * xml = (XML *) malloc(sizeof(XML));
    int r;
    XML_Elem e;
    XML_Char data[] = 
        ZT("<!-- blah blah blah --><a><!--hello-->Stuff</a>");
    bool foundComment1 = false;
    bool foundComment2 = false;

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
        if (e.type == XML_COMMENT)
        {
            if (Zcmp(e.data, ZT(" blah blah blah ")) == 0)
            {
                foundComment1 = true;
            }
            else if (Zcmp(e.data, ZT("hello")) == 0)
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
    free(xml);
}

/* Test <![CDATA[...]]> */
static void Test9()
{
    XML * xml = (XML *) malloc(sizeof(XML));
    int r;
    XML_Elem e;
    XML_Char data[] = ZT("<a><![CDATA[blah]]></a>");
    bool found = false;

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
        if (e.type == XML_CHARS)
        {
            if (Zcmp(e.data, ZT("blah")) == 0)
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
    free(xml);
}

/* Test DOCTYPE element */
static void Test10()
{
    XML * xml = (XML *) malloc(sizeof(XML));
    int r;
    XML_Elem e;
    XML_Char data[] = ZT("<!DOCTYPE ingore me><a><!DOCTYPE ingore me></a>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(r == 1);
    free(xml);
}

/* Test processing instruction */
static void Test11()
{
    XML * xml = (XML *) malloc(sizeof(XML));
    int r;
    XML_Elem e;
    XML_Char data[] = 
        ZT("<?xml version='1.0' encoding='UTF-8' standalone='yes'?>")
        ZT("<a>content</a>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(r == 1);
    free(xml);
}

/* Test tag names */
static void Test12()
{
    XML * xml = (XML *) malloc(sizeof(XML));
    int r;
    XML_Elem e;
    XML_Char data[] = 
        ZT("<b-c.d></b-c.d>");

    XML_Init(xml);
    XML_SetText(xml, data);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(r == 1);
    free(xml);
}

/* Test tag names */
static void Test13()
{
    XML * xml = (XML *) malloc(sizeof(XML));
    int r;
    XML_Elem e;
    XML_Char data[] = 
        ZT("<ns1:tag xmlns:ns1='http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd'>")
        ZT("    <ns2:tag xmlns:ns2='http://microsoft.com/ns2'>")
        ZT("    </ns2:tag>")
        ZT("</ns1:tag>");

    XML_Init(xml);
    XML_SetText(xml, data);

    XML_RegisterNameSpace(xml, 'w',
        ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd"));

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(r == 1);
    free(xml);
}

static bool Inhale(const char* path, vector<XML_Char>& wdata)
{
    vector<char> data;
    string tmp = GetPath(ID_SRCDIR);
    tmp += "/tests/xml/";
    tmp += path;
    FILE* is = Fopen(tmp.c_str(), "r");

    if (!is)
        return false;

    size_t n;
    char buf[4096];

    while ((n = fread(buf, 1, sizeof(buf), is)) != 0)
    {
        data.insert(data.end(), buf, buf + n);
    }

    data.push_back('\0');

    fclose(is);

    for (size_t i = 0; i < data.size(); i++)
        wdata.push_back(data[i]);

    return true;
}

static void Test14()
{
    XML * xml = (XML *) malloc(sizeof(XML));
    int r;
    XML_Elem e;
    vector<XML_Char> data;
    vector<XML_Elem> elems;

    UT_ASSERT(Inhale("test14.xml", data));

    XML_Init(xml);
    XML_SetText(xml, &data[0]);

    r = XML_RegisterNameSpace(xml, 'a', ZT("auri"));
    UT_ASSERT(r == 0);
    r = XML_RegisterNameSpace(xml, 'b', ZT("buri"));
    UT_ASSERT(r == 0);
    r = XML_RegisterNameSpace(xml, 'c', ZT("curi"));
    UT_ASSERT(r == 0);

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
        elems.push_back(e);
    }

    UT_ASSERT(r == 1);
    UT_ASSERT(elems.size() == 14);

    UT_ASSERT(Zcmp(elems[0].data, ZT("root")) == 0);
    UT_ASSERT(Zcmp(elems[1].data, ZT("a:anvil")) == 0);

    UT_ASSERT(Zcmp(elems[2].data, ZT("a:apple")) == 0);
    UT_ASSERT(elems[2].attrsSize == 2);
    UT_ASSERT(Zcmp(elems[2].attrs[0].name, ZT("a:color")) == 0);
    UT_ASSERT(Zcmp(elems[2].attrs[0].value, ZT("Red")) == 0);
    UT_ASSERT(Zcmp(elems[2].attrs[1].name, ZT("a:size")) == 0);
    UT_ASSERT(Zcmp(elems[2].attrs[1].value, ZT("100")) == 0);

    UT_ASSERT(Zcmp(elems[3].data, ZT("b:bat")) == 0);
    UT_ASSERT(Zcmp(elems[4].data, ZT("c:cat")) == 0);
    UT_ASSERT(Zcmp(elems[5].data, ZT("ddd:dog")) == 0);
    UT_ASSERT(Zcmp(elems[6].data, ZT("eee:egg")) == 0);
    UT_ASSERT(Zcmp(elems[7].data, ZT("eee:egg")) == 0);
    UT_ASSERT(Zcmp(elems[8].data, ZT("ddd:dog")) == 0);
    UT_ASSERT(Zcmp(elems[9].data, ZT("c:cat")) == 0);
    UT_ASSERT(Zcmp(elems[10].data, ZT("b:bat")) == 0);
    UT_ASSERT(Zcmp(elems[11].data, ZT("a:apple")) == 0);
    UT_ASSERT(Zcmp(elems[12].data, ZT("a:anvil")) == 0);
    UT_ASSERT(Zcmp(elems[13].data, ZT("root")) == 0);

    free(xml);
}

/* Test tag names */
static void Test15()
{
    XML * xml = (XML *) malloc(sizeof(XML));
    int r;
    XML_Elem e;
    XML_Char data[] = 
        ZT("<apple:root xmlns:apple='http://ns.com/a'>")
        ZT("    <apple:part apple:color='Red'>")
        ZT("    </apple:part>")
        ZT("</apple:root>");

    XML_Init(xml);
    XML_SetText(xml, data);

    XML_RegisterNameSpace(xml, 'a', ZT("http://ns.com/a"));

    while ((r = XML_Next(xml, &e)) == 0)
    {
#if defined(DUMP_XML)
        XML_Elem_Dump(&e);
#endif
    }

    UT_ASSERT(r == 1);
    free(xml);
}

static void TestFile(const char* path, _Out_writes_z_(size) XML_Char* msg, _In_ size_t size)
{
    XML * xml = (XML *) malloc(sizeof(XML));
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
    free(xml);
}

static void Test16()
{
    XML_Char msg[1024];
    TestFile("test16.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Zcmp(msg, ZT("4: error: expected attribute name")) == 0);
}

static void Test17()
{
    XML_Char msg[1024];
    TestFile("test17.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Zcmp(msg, ZT("1: error: expected '=' character")) == 0);
}

static void Test18()
{
    XML_Char msg[1024];
    TestFile("test18.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Zcmp(msg, ZT("2: error: expected opening quote")) == 0);
}

static void Test19()
{
    XML_Char msg[1024];
    TestFile("test19.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Zcmp(msg, ZT("2: error: bad entity reference")) == 0);
}

static void Test20()
{
    XML_Char msg[1024];
    TestFile("test20.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Zcmp(msg, ZT("3: error: bad character reference")) == 0);
}

static void Test21()
{
    XML_Char msg[1024];
    TestFile("test21.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Zcmp(msg, ZT("6: error: expected closing quote")) == 0);
}

static void Test22()
{
    XML_Char msg[1024];
    TestFile("test22.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Zcmp(msg, 
        ZT("1: error: default namespaces not supported: xmlns")) == 0);
}

static void Test23()
{
    XML_Char msg[1024];
    TestFile("test23.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Zcmp(msg, ZT("33: error: too many namespaces (>32)")) == 0);
}

static void Test24()
{
    XML_Char msg[1024];
    TestFile("test24.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Zcmp(msg, ZT("34: error: too many attributes (>32)")) == 0);
}

static void Test25()
{
    XML_Char msg[1024];
    TestFile("test25.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Zcmp(msg, ZT("5: error: open/close tag mismatch: a/root")) == 0);
}

static void Test26()
{
    XML_Char msg[1024];
    TestFile("test26.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Zcmp(msg, ZT("3: error: open/close tag mismatch: a/b")) == 0);
}

static void Test27()
{
    XML_Char msg[1024];
    TestFile("test27.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Zcmp(msg, ZT("8: error: markup outside root element")) == 0);
}

static void Test28()
{
    XML_Char msg[1024];
    TestFile("test28.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Zcmp(msg, ZT("5: error: expected opening angle bracket")) == 0);
}

static void Test29()
{
    XML_Char msg[1024];
    TestFile("test29.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Zcmp(msg, ZT("1: error: expected opening angle bracket")) == 0);
}

static void Test30()
{
    XML * xml = (XML *) malloc(sizeof(XML));
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
        if (i == 1)
        {
            UT_ASSERT(Zcmp(e.data, ZT("{{{<a><b></b></a>}}}")) == 0);
        }
        i++;
    }

    assert(i == 3);

    assert(r == 1);

    free(xml);
}

static void Test31()
{
    XML_Char msg[1024];
    TestFile("test31.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Zcmp(msg, ZT("")) == 0);
}

static void Test32()
{
    XML_Char msg[1024];
    TestFile("test32.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Zcmp(msg, ZT("29: error: open/close tag mismatch: a/b")) == 0);
}

static void Test33()
{
    XML_Char msg[1024];
    TestFile("test33.xml", msg, MI_COUNT(msg));
    UT_ASSERT(Zcmp(msg, ZT("28: error: expected attribute name")) == 0);
}

static void RunTests()
{
    UT_TEST(Test0);
    UT_TEST(Test1);
    UT_TEST(Test2);
    UT_TEST(Test3);
    UT_TEST(Test4);
    UT_TEST(Test5);
    UT_TEST(Test6);
    UT_TEST(Test7);
    UT_TEST(Test8);
    UT_TEST(Test9);
    UT_TEST(Test10);
    UT_TEST(Test11);
    UT_TEST(Test12);
    UT_TEST(Test13);
    UT_TEST(Test14);
    UT_TEST(Test15);
    UT_TEST(Test16);
    UT_TEST(Test17);
    UT_TEST(Test18);
    UT_TEST(Test19);
    UT_TEST(Test20);
    UT_TEST(Test21);
    UT_TEST(Test22);
    UT_TEST(Test23);
    UT_TEST(Test24);
    UT_TEST(Test25);
    UT_TEST(Test26);
    UT_TEST(Test27);
    UT_TEST(Test28);
    UT_TEST(Test29);
    UT_TEST(Test30);
    UT_TEST(Test31);
    UT_TEST(Test32);
    UT_TEST(Test33);
}

UT_ENTRY_POINT(RunTests);
