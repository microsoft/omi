/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifdef _MSC_VER
#include <windows.h>
#endif

#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

#include <MI.h>
#include <common.h>
#include <codec/mof/parser/state.h>
#include <codec/mof/parser/mofyacc.h>
#include <codec/mof/parser/mofparser.h>
#include <codec/mof/codecimpl.h>
#include <nits.h>

#include "consts.h"

#define TEST_ASSERT(x) NitsAssert(x, MI_T(""))

#define TEST_PARSER(sz) {NULL, (sz), (MI_Uint32) (sizeof(sz))}

using namespace std;

PARSER_TEST parser_encodingtest[] = {
    {(char*)"ENCODING Test1",  (const void*)ansi,  (const void*)utf8,  (const void*)unicode,  (const void*)utf16LE,  (const void*)utf16BE},
#if !defined(aix) && !defined(hpux)
// This test fails on aix and hpux . It appears to be related to the parser callback needsQualifier. The problem appears to be isolated to the test case

    {(char*)"ENCODING Test2",  (const void*)ansi1,  (const void*)utf81,  (const void*)unicode1,  (const void*)utf16LE1,  (const void*)utf16BE1},
#endif
    {(char *) NULL, (const void*)0,  (const void*)0,  (const void*)0,  (const void*)0,  (const void*)0}
};

struct Test_ParserStruct
{
    MOF_Parser * parser;
    const char * mofbuffer;
    MI_Uint32 sizeofbuffer;
};

int ParseBuffer(
    _In_reads_bytes_(size) void *buf,
    _In_ size_t size,
    _Outptr_ MOF_Parser ** parser)
{
    *parser = MI_MOFParser_Init((void*)buf, (MI_Uint32)size, NULL);
    return MI_MOFParser_Parse(*parser);
}

NitsSetup0(test_parser_Setup, Test_ParserStruct)  
    int res = ParseBuffer(
        (void*) NitsContext()->_Test_ParserStruct->mofbuffer,
        NitsContext()->_Test_ParserStruct->sizeofbuffer,
        &NitsContext()->_Test_ParserStruct->parser);
    NitsAssert(0 == res, MI_T("Create Mof parser failed"));
NitsEndSetup

NitsCleanup(test_parser_Setup)
    if (NitsContext()->_Test_ParserStruct->parser != NULL)
    {
        MI_MOFParser_Delete(NitsContext()->_Test_ParserStruct->parser);
    }
NitsEndCleanup

//
// buf have to be null terminated
//
void TestEncoding(_In_ void *buf, _In_ const char * testname, int expected)
{ 
    MOF_Parser * parser = NULL;
    int res = ParseBuffer(buf, 0x400, &parser);
    NitsAssert(expected == res, MI_T("Mof parser error"));
    MI_MOFParser_Delete(parser);
}

NitsTest(TestMofParserEncoding)
    PARSER_TEST *t = parser_encodingtest;
    while(t->testName != 0)
    {
        if (t->ansi)
            TestEncoding((void*)t->ansi, "ansi", 0);
        if (t->unicode)
            TestEncoding((void*)t->ansi, "unicode", 0);
        if (t->utf16BE)
            TestEncoding((void*)t->ansi, "utf16BE", 0);
        if (t->utf16LE)
            TestEncoding((void*)t->ansi, "utf16LE", 0);
        if (t->utf8)
            TestEncoding((void*)t->ansi, "utf8", 0);
        t++;
    }
    NitsAssert(t->testName == 0, MI_T("test parser"));
NitsEndTest

struct Test_ParserStruct sTestAlias = TEST_PARSER("instance of A as $abc {P=1;}; instance of B {P1=$abc;};");

NitsTest1(TestAlias, test_parser_Setup, sTestAlias)
    MOF_State * state = (MOF_State*)(NitsContext()->_test_parser_Setup->_Test_ParserStruct->parser->state);
    NitsAssert(state->instanceDecls.size == 2, MI_T("Instance size error"));

    int c = Tcscasecmp(state->instanceDecls.data[0]->alias, MI_T("abc"));
    NitsAssert(c==0, MI_T("Instance alias name error"));

    NitsAssert(state->instanceAliases.size==1, MI_T("Alias decl size error"));

    NitsAssert(state->instanceDecls.data[0]->refs == 1, MI_T("Alias ref count error"));
NitsEndTest

struct Test_ParserStruct sTestAliasEx = TEST_PARSER("instance of MSFT_ExpressionIdentifier as $x {"
    "    name = \"x\";"
    "};");

NitsTest1(TestAliasEx, test_parser_Setup, sTestAliasEx)
    MOF_State * state = (MOF_State*)(NitsContext()->_test_parser_Setup->_Test_ParserStruct->parser->state);
    NitsAssert(state->instanceDecls.size == 1, MI_T("Instance size error"));
NitsEndTest

struct Test_ParserStruct sTestAliasArray = TEST_PARSER("instance of A as $abc {P=1;};"
        "instance of A as $d {P=1;};"
        "instance of C as $x {P=1;P2=$d;};"
        "instance of B {P2={$abc, $d, $x};};");
NitsTest1(TestAliasArray, test_parser_Setup, sTestAliasArray)
    MOF_State *state = (MOF_State*)(NitsContext()->_test_parser_Setup->_Test_ParserStruct->parser->state);
    NitsAssert(state->instanceDecls.size == 4, MI_T("Instance size error"));

    int c = Tcscasecmp(state->instanceDecls.data[0]->alias, MI_T("abc"));
    NitsAssert(c == 0, MI_T("Instance alias name error"));
    NitsAssert(state->instanceDecls.data[0]->refs == 1, MI_T("alias ref count error"));
    c = Tcscasecmp(state->instanceDecls.data[0]->name, MI_T("A"));
    NitsAssert(c == 0, MI_T("Instance class name error"));

    c = Tcscasecmp(state->instanceDecls.data[1]->alias, MI_T("d"));
    NitsAssert(c == 0, MI_T("Instance alias name error"));
    NitsAssert(state->instanceDecls.data[1]->refs == 2, MI_T("alias ref count error"));
    c = Tcscasecmp(state->instanceDecls.data[1]->name, MI_T("A"));
    NitsAssert(c == 0, MI_T("Instance class name error"));

    c = Tcscasecmp(state->instanceDecls.data[2]->alias, MI_T("x"));
    NitsAssert(c == 0, MI_T("Instance alias name error"));
    NitsAssert(state->instanceDecls.data[2]->refs == 1, MI_T("alias ref count error"));
    c = Tcscasecmp(state->instanceDecls.data[2]->name, MI_T("C"));
    NitsAssert(c == 0, MI_T("Instance class name error"));

    c = Tcscasecmp(state->instanceDecls.data[3]->name, MI_T("B"));
    NitsAssert(c == 0, MI_T("Instance class name error"));
NitsEndTest


NitsTest(TestNonAlignedANSIBuffer)
    MOF_Parser * parser = NULL;
    char aliasinstance[] = "Xinstance of A as $abc {P=1;};"
        "instance of B {P1=$abc;};";
    size_t length = sizeof(aliasinstance) - 1;
    int res = ParseBuffer(
        &aliasinstance[1],
        length,
        &parser);
    NitsAssert(0 == res, MI_T("Mof parser error"));
    if (res == 0)
    {
        MOF_State * state = (MOF_State*)parser->state;
        NitsAssert(state->instanceDecls.size == 2, MI_T("Instance size error"));
        int c = Tcscasecmp(state->instanceDecls.data[0]->alias, MI_T("abc"));
        NitsAssert( c==0, MI_T("Instance size error"));
    }
    if (parser) MI_MOFParser_Delete(parser);
NitsEndTest

#if defined(_MSC_VER)
NitsTest(TestNonAlignedUnicodeBuffer)
    MOF_Parser * parser = NULL;
    wchar_t aliasinstance[] = MI_T("instance of A as $abc {P=1;};")
        MI_T("instance of B {P1=$abc;};");
    char buffer[256];
    size_t length = sizeof(aliasinstance);
    memcpy(&buffer[1], aliasinstance, length);
    buffer[length + 1] = 0;
    buffer[length + 2] = 0;
    int res = ParseBuffer(
        &buffer[1],
        length,
        &parser);
    NitsAssert(0 == res, MI_T("Mof parser error"));
    if (res == 0)
    {
        MOF_State * state = (MOF_State*)parser->state;
        NitsAssert(state->instanceDecls.size == 2, MI_T("Instance size error"));
        int c = Tcscasecmp(state->instanceDecls.data[0]->alias, MI_T("abc"));
        NitsAssert( c==0, MI_T("Instance size error"));
    }
    if (parser) MI_MOFParser_Delete(parser);
NitsEndTest
#endif
