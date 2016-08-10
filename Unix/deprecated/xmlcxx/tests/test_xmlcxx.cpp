/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <iostream>
#include <string>
#include <vector>
#include <ut/ut.h>
#include <common.h>
#include <xmlcxx/xmlcxx.h>
#include <pal/strings.h>
#include <base/dir.h>
#include <base/paths.h>
#include <cstdio>

using namespace xmlcxx;


#if defined(_MSC_VER)
/* PreFast - reviewed and believed to be false-positive*/

/* warning C6262: Function uses '21344' bytes of stack: exceeds /analyze:stacksize'16384'. Consider moving some data to heap */
//# pragma warning(disable : 6262)

#endif /* _MSC_VER */

using namespace std;

NitsSetup(TestXmlCxxSetup)
NitsEndSetup

NitsCleanup(TestXmlCxxSetup)
NitsEndCleanup

NitsTestWithSetup(Test0, TestXmlCxxSetup)
{
    XMLReader xml;
    XMLElement e;
    char data[] = "<a>       one         </a>";

    xml.SetText(data);

    while (xml.GetNext(e))
    {
#if 0
        e.Dump();
#endif
    }

    UT_ASSERT(xml.GetError() == false);
}
NitsEndTest

NitsTestWithSetup(Test1, TestXmlCxxSetup)
{
    XMLReader xml;
    XMLElement e;
    size_t i = 0;
    char data[] = "<a><b><c></c></b></a>";

    xml.SetText(data);

    while (xml.GetNext(e))
    {
        switch (i)
        {
            case 0:
            {
                UT_ASSERT(strcmp(e.GetData(), "a") == 0);
                UT_ASSERT(e.GetType() == XMLElement::START);
                break;
            }
            case 1:
            {
                UT_ASSERT(strcmp(e.GetData(), "b") == 0);
                UT_ASSERT(e.GetType() == XMLElement::START);
                break;
            }
            case 2:
            {
                UT_ASSERT(strcmp(e.GetData(), "c") == 0);
                UT_ASSERT(e.GetType() == XMLElement::START);
                break;
            }
            case 3:
            {
                UT_ASSERT(strcmp(e.GetData(), "c") == 0);
                UT_ASSERT(e.GetType() == XMLElement::END);
                break;
            }
            case 4:
            {
                UT_ASSERT(strcmp(e.GetData(), "b") == 0);
                UT_ASSERT(e.GetType() == XMLElement::END);
                break;
            }
            case 5:
            {
                UT_ASSERT(strcmp(e.GetData(), "a") == 0);
                UT_ASSERT(e.GetType() == XMLElement::END);
                break;
            }
        }

        i++;
    }

    UT_ASSERT(xml.GetError() == false);
}
NitsEndTest

NitsTestWithSetup(Test2, TestXmlCxxSetup)
{
    XMLReader xml;
    XMLElement e;
    char data[] = "<a>   <b>   bbb   <c>   ccc    </c> BBB</b> AAA</a>";

    xml.SetText(data);

    while (xml.GetNext(e))
    {
    }

    UT_ASSERT(xml.GetError() == false);
}
NitsEndTest

NitsTestWithSetup(Test3, TestXmlCxxSetup)
{
    XMLReader xml;
    XMLElement e;
    char data[] = "<a><b>   &lt;&#65;&#66;&#67;&gt;&#x41;   </b></a>";
    size_t i = 0;

    xml.SetText(data);

    while (xml.GetNext(e))
    {
#if 0
        XMLElement_Dump(&e);
#endif
        if (i == 2)
        {
            UT_ASSERT(e.GetType() == XMLElement::CHARS);
            UT_ASSERT(strcmp(e.GetData(), "<ABC>A") == 0);
        }

        i++;
    }

    UT_ASSERT(i == 5);
    UT_ASSERT(xml.GetError() == false);
}
NitsEndTest

/* Test more than one root element */
NitsTestWithSetup(Test4, TestXmlCxxSetup)
{
    XMLReader xml;
    XMLElement e;
    char data[] = "<a></a><a></a>";

    xml.SetText(data);

    while (xml.GetNext(e))
        ;

    UT_ASSERT(xml.GetError() == true);
}
NitsEndTest

/* Test attributes */
NitsTestWithSetup(Test5, TestXmlCxxSetup)
{
    XMLReader xml;
    XMLElement e;
    char data[] = "<a x=\"1\" y = \"22\" zzz = \"1234\">Stuff</a>";

    xml.SetText(data);

    while (xml.GetNext(e))
    {
#if 0
        XMLElement_Dump(&e);
#endif
    }

    UT_ASSERT(xml.GetError() == false);
}
NitsEndTest

/* Test empty tags */
NitsTestWithSetup(Test6, TestXmlCxxSetup)
{
    XMLReader xml;
    XMLElement e;
    char data[] = "<a><b/></a>";

    xml.SetText(data);

    while (xml.GetNext(e))
    {
#if 0
        XMLElement_Dump(&e);
#endif
    }

    UT_ASSERT(xml.GetError() == false);
}
NitsEndTest

/* Test Person example */
NitsTestWithSetup(Test7, TestXmlCxxSetup)
{
    XMLReader xml;
    XMLElement e;
    const char* tag = NULL;
    const char* first = NULL;
    const char* last = NULL;
    size_t i;
    char data[] = 
        "<Person First='George' Last='Washington' Char='&lt;'>\n"
        "</Person>\n";

    xml.SetText(data);

    while (xml.GetNext(e))
    {
        if (e.GetType() == XMLElement::START && strcmp(e.GetData(), "Person") == 0)
        {
            tag = e.GetData();

            for (i = 0; i < e.GetAttributeCount(); i++)
            {
                if (strcmp(e.GetAttributeName(i), "First") == 0)
                    first = e.GetAttributeValue(i);
                if (strcmp(e.GetAttributeName(i), "Last") == 0)
                    last = e.GetAttributeValue(i);
            }
        }
#if 0
        XMLElement_Dump(&e);
#endif
    }

    UT_ASSERT(tag != 0 && strcmp(tag, "Person") == 0);
    UT_ASSERT(strcmp(first, "George") == 0);
    UT_ASSERT(strcmp(last, "Washington") == 0);

    UT_ASSERT(xml.GetError() == false);
}
NitsEndTest

/* Test comments */
NitsTestWithSetup(Test8, TestXmlCxxSetup)
{
    XMLReader xml;
    XMLElement e;
    char data[] = 
        "<!-- blah blah blah --><a><!--hello-->Stuff</a>";
    bool foundComment1 = false;
    bool foundComment2 = false;

    xml.SetText(data);

    while (xml.GetNext(e))
    {
        if (e.GetType() == XMLElement::COMMENT)
        {
            if (strcmp(e.GetData(), " blah blah blah ") == 0)
            {
                foundComment1 = true;
            }
            else if (strcmp(e.GetData(), "hello") == 0)
            {
                foundComment2 = true;
            }
        }
#if 0
        XMLElement_Dump(&e);
#endif
    }

    UT_ASSERT(foundComment1);
    UT_ASSERT(foundComment2);
    UT_ASSERT(xml.GetError() == false);
}
NitsEndTest

/* Test <![CDATA[...]]> */
NitsTestWithSetup(Test9, TestXmlCxxSetup)
{
    XMLReader xml;
    XMLElement e;
    char data[] = "<a><![CDATA[blah]]></a>";
    bool found = false;

    xml.SetText(data);

    while (xml.GetNext(e))
    {
        if (e.GetType() == XMLElement::CHARS)
        {
            if (strcmp(e.GetData(), "blah") == 0)
            {
                found = true;
            }
        }
#if 0
        XMLElement_Dump(&e);
#endif
    }

    UT_ASSERT(found);
    UT_ASSERT(xml.GetError() == false);
}
NitsEndTest

/* Test DOCTYPE element */
NitsTestWithSetup(Test10, TestXmlCxxSetup)
{
    XMLReader xml;
    XMLElement e;
    char data[] = "<!DOCTYPE ingore me><a><!DOCTYPE ingore me></a>";

    xml.SetText(data);

    while (xml.GetNext(e))
    {
#if 0
        XMLElement_Dump(&e);
#endif
    }

    UT_ASSERT(xml.GetError() == false);
}
NitsEndTest

/* Test processing instruction */
NitsTestWithSetup(Test11, TestXmlCxxSetup)
{
    XMLReader xml;
    XMLElement e;
    char data[] = 
        "<?xml version='1.0' encoding='UTF-8' standalone='yes'?>"
        "<a>content</a>";

    xml.SetText(data);

    while (xml.GetNext(e))
    {
#if 0
        XMLElement_Dump(&e);
#endif
    }

    UT_ASSERT(xml.GetError() == false);
}
NitsEndTest

/* Test tag names */
NitsTestWithSetup(Test12, TestXmlCxxSetup)
{
    XMLReader xml;
    XMLElement e;
    char data[] = 
        "<b-c.d></b-c.d>";

    xml.SetText(data);

    while (xml.GetNext(e))
    {
#if 0
        XMLElement_Dump(&e);
#endif
    }

    UT_ASSERT(xml.GetError() == false);
}
NitsEndTest

/* Test tag names */
NitsTestWithSetup(Test13, TestXmlCxxSetup)
{
    XMLReader xml;
    XMLElement e;
    char data[] = 
        "<ns1:tag xmlns:ns1='http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd'>"
        "    <ns2:tag xmlns:ns2='http://microsoft.com/ns2'>"
        "    </ns2:tag>"
        "</ns1:tag>";

    xml.SetText(data);

    xml.RegisterNameSpace('w',
        "http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd");

    while (xml.GetNext(e))
    {
#if 0
        XMLElement_Dump(&e);
#endif
    }

    UT_ASSERT(xml.GetError() == false);
}
NitsEndTest

static bool Inhale(const char* path, vector<char>& data)
{
    string tmp = GetPath(ID_PREFIX);
    tmp += "/xml/tests/";
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

    return true;
}

NitsTestWithSetup(Test14, TestXmlCxxSetup)
{
    XMLReader xml;
    bool flag;
    XMLElement e;
    vector<char> data;
    vector<XMLElement> elems;

    UT_ASSERT(Inhale("test14.xml", data));

    xml.SetText(&data[0]);

    flag = xml.RegisterNameSpace('a', "auri");
    UT_ASSERT(flag == true);
    flag = xml.RegisterNameSpace('b', "buri");
    UT_ASSERT(flag == true);
    flag = xml.RegisterNameSpace('c', "curi");
    UT_ASSERT(flag == true);

    while (xml.GetNext(e))
    {
#if 0
        printf("i=%d\n", (int)i);
        XMLElement_Dump(&e);
        i++;
#endif
        elems.push_back(e);
    }

    UT_ASSERT(xml.GetError() == false);
    UT_ASSERT(elems.size() == 14);

    UT_ASSERT(strcmp(elems[0].GetData(), "root") == 0);
    UT_ASSERT(strcmp(elems[1].GetData(), "a:anvil") == 0);

    UT_ASSERT(strcmp(elems[2].GetData(), "a:apple") == 0);
    UT_ASSERT(elems[2].GetAttributeCount() == 2);
    UT_ASSERT(strcmp(elems[2].GetAttributeName(0), "a:color") == 0);
    UT_ASSERT(strcmp(elems[2].GetAttributeValue(0), "Red") == 0);
    UT_ASSERT(strcmp(elems[2].GetAttributeName(1), "a:size") == 0);
    UT_ASSERT(strcmp(elems[2].GetAttributeValue(1), "100") == 0);

    UT_ASSERT(strcmp(elems[3].GetData(), "b:bat") == 0);
    UT_ASSERT(strcmp(elems[4].GetData(), "c:cat") == 0);
    UT_ASSERT(strcmp(elems[5].GetData(), "ddd:dog") == 0);
    UT_ASSERT(strcmp(elems[6].GetData(), "eee:egg") == 0);
    UT_ASSERT(strcmp(elems[7].GetData(), "eee:egg") == 0);
    UT_ASSERT(strcmp(elems[8].GetData(), "ddd:dog") == 0);
    UT_ASSERT(strcmp(elems[9].GetData(), "c:cat") == 0);
    UT_ASSERT(strcmp(elems[10].GetData(), "b:bat") == 0);
    UT_ASSERT(strcmp(elems[11].GetData(), "a:apple") == 0);
    UT_ASSERT(strcmp(elems[12].GetData(), "a:anvil") == 0);
    UT_ASSERT(strcmp(elems[13].GetData(), "root") == 0);
}
NitsEndTest

/* Test tag names */
NitsTestWithSetup(Test15, TestXmlCxxSetup)
{
    XMLReader xml;
    XMLElement e;
    char data[] = 
        "<apple:root xmlns:apple='http://ns.com/a'>"
        "    <apple:part apple:color='Red'>"
        "    </apple:part>"
        "</apple:root>";

    xml.SetText(data);

    xml.RegisterNameSpace('a', "http://ns.com/a");

    while (xml.GetNext(e))
    {
#if 0
        XMLElement_Dump(&e);
#endif
    }

    UT_ASSERT(xml.GetError() == false);
}
NitsEndTest

static void TestFile(const char* path, char* msg, size_t size)
{
    XMLReader xml;
    XMLElement e;
    vector<char> data;

    bool flag = Inhale(path, data);
    UT_ASSERT(flag == true);

    UT_ASSERT(data.size() != 0);

    xml.SetText(&data[0]);

    while (xml.GetNext(e))
    {
#if 0
        XMLElement_Dump(&e);
#endif
    }

    xml.GetErrorMessage(msg, size);
}

NitsTestWithSetup(Test16, TestXmlCxxSetup)
{
    char msg[1024];
    TestFile("test16.xml", msg, sizeof(msg));
    UT_ASSERT(strcmp(msg, "4: error: expected attribute name") == 0);
}
NitsEndTest

NitsTestWithSetup(Test17, TestXmlCxxSetup)
{
    char msg[1024];
    TestFile("test17.xml", msg, sizeof(msg));
    UT_ASSERT(strcmp(msg, "1: error: expected '=' character") == 0);
}
NitsEndTest

NitsTestWithSetup(Test18, TestXmlCxxSetup)
{
    char msg[1024];
    TestFile("test18.xml", msg, sizeof(msg));
    UT_ASSERT(strcmp(msg, "2: error: expected opening quote") == 0);
}
NitsEndTest

NitsTestWithSetup(Test19, TestXmlCxxSetup)
{
    char msg[1024];
    TestFile("test19.xml", msg, sizeof(msg));
    UT_ASSERT(strcmp(msg, "2: error: bad entity reference") == 0);
}
NitsEndTest

NitsTestWithSetup(Test20, TestXmlCxxSetup)
{
    char msg[1024];
    TestFile("test20.xml", msg, sizeof(msg));
    UT_ASSERT(strcmp(msg, "3: error: bad character reference") == 0);
}
NitsEndTest

NitsTestWithSetup(Test21, TestXmlCxxSetup)
{
    char msg[1024];
    TestFile("test21.xml", msg, sizeof(msg));
    UT_ASSERT(strcmp(msg, "6: error: expected closing quote") == 0);
}
NitsEndTest

NitsTestWithSetup(Test22, TestXmlCxxSetup)
{
    char msg[1024];
    TestFile("test22.xml", msg, sizeof(msg));
    UT_ASSERT(strcmp(msg, 
        "1: error: default namespaces not supported: xmlns") == 0);
}
NitsEndTest

NitsTestWithSetup(Test23, TestXmlCxxSetup)
{
    char msg[1024];
    TestFile("test23.xml", msg, sizeof(msg));
    UT_ASSERT(strcmp(msg, "33: error: too many namespaces (>32)") == 0);
}
NitsEndTest

NitsTestWithSetup(Test24, TestXmlCxxSetup)
{
    char msg[1024];
    TestFile("test24.xml", msg, sizeof(msg));
    UT_ASSERT(strcmp(msg, "34: error: too many attributes (>32)") == 0);
}
NitsEndTest

NitsTestWithSetup(Test25, TestXmlCxxSetup)
{
    char msg[1024];
    TestFile("test25.xml", msg, sizeof(msg));
    UT_ASSERT(strcmp(msg, "5: error: open/close tag mismatch: a/root") == 0);
}
NitsEndTest

NitsTestWithSetup(Test26, TestXmlCxxSetup)
{
    char msg[1024];
    TestFile("test26.xml", msg, sizeof(msg));
    UT_ASSERT(strcmp(msg, "3: error: open/close tag mismatch: a/b") == 0);
}
NitsEndTest

NitsTestWithSetup(Test27, TestXmlCxxSetup)
{
    char msg[1024];
    TestFile("test27.xml", msg, sizeof(msg));
    UT_ASSERT(strcmp(msg, "8: error: markup outside root element") == 0);
}
NitsEndTest

NitsTestWithSetup(Test28, TestXmlCxxSetup)
{
    char msg[1024];
    TestFile("test28.xml", msg, sizeof(msg));
    UT_ASSERT(strcmp(msg, "5: error: expected opening angle bracket") == 0);
}
NitsEndTest

NitsTestWithSetup(Test29, TestXmlCxxSetup)
{
    char msg[1024];
    TestFile("test29.xml", msg, sizeof(msg));
    UT_ASSERT(strcmp(msg, "1: error: expected opening angle bracket") == 0);
}
NitsEndTest

NitsTestWithSetup(Test30, TestXmlCxxSetup)
{
    XMLReader xml;
    XMLElement e;
    size_t i = 0;
    vector<char> data;

    bool flag = Inhale("test30.xml", data);
    UT_ASSERT(flag == true);

    UT_ASSERT(data.size() != 0);
    xml.SetText(&data[0]);

    while (xml.GetNext(e))
    {
#if 0
        XMLElement_Dump(&e);
#endif
        if (i == 1)
        {
            UT_ASSERT(strcmp(e.GetData(), "{{{<a><b></b></a>}}}") == 0);
        }
        i++;
    }

    UT_ASSERT(i == 3);

    UT_ASSERT(xml.GetError() == false);
}
NitsEndTest

NitsTestWithSetup(Test31, TestXmlCxxSetup)
{
    char msg[1024];
    TestFile("test31.xml", msg, sizeof(msg));
    UT_ASSERT(strcmp(msg, "") == 0);
}
NitsEndTest

NitsTestWithSetup(Test32, TestXmlCxxSetup)
{
    char msg[1024];
    TestFile("test32.xml", msg, sizeof(msg));
    UT_ASSERT(strcmp(msg, "29: error: open/close tag mismatch: a/b") == 0);
}
NitsEndTest

NitsTestWithSetup(Test33, TestXmlCxxSetup)
{
    char msg[1024];
    TestFile("test33.xml", msg, sizeof(msg));
    UT_ASSERT(strcmp(msg, "28: error: expected attribute name") == 0);
}
NitsEndTest

NitsTestWithSetup(Test34, TestXmlCxxSetup)
{
    XMLWriter w;
    bool f;

    w.EnableLineSeparators();

    // <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
    f = w.PutProcessingInstruction("xml",
        MakeAttrs("version", "1.0", "encoding", "UTF-8", "standalone", "yes"));
    UT_ASSERT(f == true);

    // <p:aaa color="red" size="10">
    f = w.PutStartTag("p:aaa", MakeAttrs("color", "red", "size", "10"));
    UT_ASSERT(f == true);

    // <p:bbb content="&lt;&gt;/>
    f = w.PutEmptyTag("p:bbb", MakeAttrs("content", "<>"));
    UT_ASSERT(f == true);

    // </p:ccc>
    f = w.PutStartTag("p:ccc");
    UT_ASSERT(f == true);

    // Some character data.
    w.PutCharacterData("Some character data");

    // </p:ccc>
    f = w.PutEndTag("p:ccc");
    UT_ASSERT(f == true);

    // <!-- blah blah blah -->
    w.PutComment(" blah blah blah ");

    // <![CDATA[WXYZ]]>
    w.PutCDATA("WXYZ");

    // </p:aaa>
    f = w.PutEndTag("p:aaa");
    UT_ASSERT(f == true);

    // Check result.
    {
        const char TEXT[] =
            "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\r\n"
            "<p:aaa color=\"red\" size=\"10\">\r\n"
            "<p:bbb content=\"&lt;&gt;\"/>\r\n"
            "<p:ccc>\r\n"
            "Some character data\r\n"
            "</p:ccc>\r\n"
            "<!-- blah blah blah -->\r\n"
            "<![CDATA[WXYZ]]>\r\n"
            "</p:aaa>\r\n";

        UT_ASSERT(strcmp(w.GetText().c_str(), TEXT) == 0);
    }

    // Validate the document now.
    {
        XMLReader r;
        XMLElement e;

        r.SetText(w.GetText().c_str());

        while (r.GetNext(e))
            ;

        UT_ASSERT(r.GetError() == false);
    }
}
NitsEndTest

