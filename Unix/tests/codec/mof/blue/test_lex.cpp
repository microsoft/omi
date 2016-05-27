/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *============================================================================
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

using namespace std;

static void TestLexParser(LEX_TEST *test)
{
    MOF_Parser * parser = MI_MOFParser_Init((void*)test->buf, (MI_Uint32)test->size, NULL);
    MOF_State * state = (MOF_State*)parser->state;
    LEX_RESULT *r = test->expected;
    int t = MI_MOFParser_Lex(parser);

//    TTRACE(test->testName);

    while (t !=0)
    {
        NitsAssert(r->tok == t, MI_T("Token is wrong"));

        if (t == TOK_IDENT)
        {
            int c = Tcscasecmp((MI_Char*)r->data, state->ystate.moflval.string);
            NitsAssert(c == 0, MI_T("Identifier value is wrong"));
        }
        else if (t == TOK_CHAR_VALUE)
        {
            MI_Char16 c = state->ystate.moflval.character;
            MI_Char16 d = (MI_Char16)r->data;
            NitsAssert(c == d, MI_T("Char16 value is wrong"));
        }
        else if (t == TOK_INTEGER_VALUE)
        {
            MI_Sint64 c = state->ystate.moflval.integer;
            MI_Sint64 d = (MI_Sint64)r->data;
            NitsAssert(c == d, MI_T("Integer value is wrong"));
        }
        else if (t == TOK_REAL_VALUE)
        {
            // todo:
            NitsAssert(1, MI_T("Real value is wrong"));
        }
        
        if (r->tok != 0)
            r++;

        if (t != TOK_ERROR)
        {
            t = MI_MOFParser_Lex(parser);
        }
        else
        {
            break;
        }
    }
    MI_Boolean fr = MI_FALSE;
    if ((r->tok ==0) && ((t == 0)||(t == TOK_ERROR)))
        fr = MI_TRUE;
    NitsAssert(fr, MI_T("Lexical parser error"));
    MI_MOFParser_Delete(parser);
}

NitsTest(TestLex)
    LEX_TEST *t = lextest;
    while(t->buf != 0)
    {
        TestLexParser(t++);
    }
    NitsAssert(t->buf == 0, MI_T("test lex"));
NitsEndTest
