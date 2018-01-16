/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <MI.h>
#include <common.h>
#include <codec/mof/parser/state.h>
#include <codec/mof/parser/mofyacc.h>
#include "consts.h"


const wchar_t * TOKEN_STR [] =
{
    L"TOK_ERROR",
    L"TOK_BOOLEAN",
    L"TOK_SINT8",
    L"TOK_UINT8",
    L"TOK_SINT16",
    L"TOK_UINT16",
    L"TOK_SINT32",
    L"TOK_UINT32",
    L"TOK_SINT64",
    L"TOK_UINT64",
    L"TOK_REAL32",
    L"TOK_REAL64",
    L"TOK_DATETIME",
    L"TOK_CHAR16",
    L"TOK_STRING",
    L"TOK_BOOLEAN_VALUE",
    L"TOK_REF",
    L"TOK_SCOPE",
    L"TOK_CLASS",
    L"TOK_ASSOCIATION",
    L"TOK_INDICATION",
    L"TOK_QUALIFIER",
    L"TOK_PROPERTY",
    L"TOK_REFERENCE",
    L"TOK_METHOD",
    L"TOK_PARAMETER",
    L"TOK_ANY",
    L"TOK_FLAVOR",
    L"TOK_ENABLEOVERRIDE",
    L"TOK_DISABLEOVERRIDE",
    L"TOK_RESTRICTED",
    L"TOK_TOSUBCLASS",
    L"TOK_TRANSLATABLE",
    L"TOK_INSTANCE",
    L"TOK_OF",
    L"TOK_AS",
    L"TOK_PRAGMA",
    L"TOK_SCHEMA",
    L"TOK_INTEGER_VALUE",
    L"TOK_REAL_VALUE",
    L"TOK_STRING_VALUE",
    L"TOK_CHAR_VALUE",
    L"TOK_IDENT",
    L"TOK_ALIAS_IDENTIFIER",
    L"TOK_NULL",
    NULL
};

/* With KEY qualifier (have to define KEY qualifier some where)
class testclass
{
[Key]STRING k;
Uint8 p;
};
*/
const unsigned char ansi1[]={
0x63, 0x6C, 0x61, 0x73, 0x73, 0x20, 0x74, 0x65, 0x73, 0x74, 0x63, 0x6C, 0x61, 0x73, 0x73, 0x0D,
0x0A, 0x7B, 0x0D, 0x0A, 0x5B, 0x4B, 0x65, 0x79, 0x5D, 0x53, 0x54, 0x52, 0x49, 0x4E, 0x47, 0x20,
0x6B, 0x3B, 0x0D, 0x0A, 0x55, 0x69, 0x6E, 0x74, 0x38, 0x20, 0x70, 0x3B, 0x0D, 0x0A, 0x7D, 0x3B,
0x00
};

const unsigned char utf81[]={
0xEF, 0xBB, 0xBF, 0x63, 0x6C, 0x61, 0x73, 0x73, 0x20, 0x74, 0x65, 0x73, 0x74, 0x63, 0x6C, 0x61,
0x73, 0x73, 0x0D, 0x0A, 0x7B, 0x0D, 0x0A, 0x5B, 0x4B, 0x65, 0x79, 0x5D, 0x53, 0x54, 0x52, 0x49,
0x4E, 0x47, 0x20, 0x6B, 0x3B, 0x0D, 0x0A, 0x55, 0x69, 0x6E, 0x74, 0x38, 0x20, 0x70, 0x3B, 0x0D,
0x0A, 0x7D, 0x3B, 0x6B, 0x3B, 0x0D, 0x0A, 0x55, 0x69, 0x6E, 0x74, 0x38, 0x20, 0x70, 0x3B, 0x0D,
0x00
};

const unsigned char unicode1[]={
0x63, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x73, 0x00, 0x20, 0x00, 0x74, 0x00,
0x65, 0x00, 0x73, 0x00, 0x74, 0x00, 0x63, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x73, 0x00,
0x0D, 0x00, 0x0A, 0x00, 0x7B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x5B, 0x00, 0x4B, 0x00, 0x65, 0x00,
0x79, 0x00, 0x5D, 0x00, 0x53, 0x00, 0x54, 0x00, 0x52, 0x00, 0x49, 0x00, 0x4E, 0x00, 0x47, 0x00,
0x20, 0x00, 0x6B, 0x00, 0x3B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x55, 0x00, 0x69, 0x00, 0x6E, 0x00,
0x74, 0x00, 0x38, 0x00, 0x20, 0x00, 0x70, 0x00, 0x3B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x7D, 0x00,
0x3B, 0x00, 0x00, 0x00
};

const unsigned char utf16LE1[]={
0xFF, 0xFE, 0x63, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x73, 0x00, 0x20, 0x00, 0x74, 0x00,
0x65, 0x00, 0x73, 0x00, 0x74, 0x00, 0x63, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x73, 0x00,
0x0D, 0x00, 0x0A, 0x00, 0x7B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x5B, 0x00, 0x4B, 0x00, 0x65, 0x00,
0x79, 0x00, 0x5D, 0x00, 0x53, 0x00, 0x54, 0x00, 0x52, 0x00, 0x49, 0x00, 0x4E, 0x00, 0x47, 0x00,
0x20, 0x00, 0x6B, 0x00, 0x3B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x55, 0x00, 0x69, 0x00, 0x6E, 0x00,
0x74, 0x00, 0x38, 0x00, 0x20, 0x00, 0x70, 0x00, 0x3B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x7D, 0x00,
0x3B, 0x00, 0x00, 0x00
};

const unsigned char utf16BE1[]={
0xFE, 0xFF, 0x00, 0x63, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x73, 0x00, 0x20, 0x00, 0x74,
0x00, 0x65, 0x00, 0x73, 0x00, 0x74, 0x00, 0x63, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x73,
0x00, 0x0D, 0x00, 0x0A, 0x00, 0x7B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x5B, 0x00, 0x4B, 0x00, 0x65, 
0x00, 0x79, 0x00, 0x5D, 0x00, 0x53, 0x00, 0x54, 0x00, 0x52, 0x00, 0x49, 0x00, 0x4E, 0x00, 0x47, 
0x00, 0x20, 0x00, 0x6B, 0x00, 0x3B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x55, 0x00, 0x69, 0x00, 0x6E, 
0x00, 0x74, 0x00, 0x38, 0x00, 0x20, 0x00, 0x70, 0x00, 0x3B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x7D, 
0x00, 0x3B, 0x00, 0x00
};

/* w/o KEY qualifier
class testclass
{
STRING k;
Uint8 p;
};
*/
const unsigned char ansi[]={
0x63, 0x6C, 0x61, 0x73, 0x73, 0x20, 0x74, 0x65, 0x73, 0x74, 0x63, 0x6C, 0x61, 0x73, 0x73, 0x0D,
0x0A, 0x7B, 0x0D, 0x0A, 0x53, 0x54, 0x52, 0x49, 0x4E, 0x47, 0x20,
0x6B, 0x3B, 0x0D, 0x0A, 0x55, 0x69, 0x6E, 0x74, 0x38, 0x20, 0x70, 0x3B, 0x0D, 0x0A, 0x7D, 0x3B,
0x00
};

const unsigned char utf8[]={
0xEF, 0xBB, 0xBF, 0x63, 0x6C, 0x61, 0x73, 0x73, 0x20, 0x74, 0x65, 0x73, 0x74, 0x63, 0x6C, 0x61,
0x73, 0x73, 0x0D, 0x0A, 0x7B, 0x0D, 0x0A, 0x53, 0x54, 0x52, 0x49,
0x4E, 0x47, 0x20, 0x6B, 0x3B, 0x0D, 0x0A, 0x55, 0x69, 0x6E, 0x74, 0x38, 0x20, 0x70, 0x3B, 0x0D,
0x0A, 0x7D, 0x3B, 0x0D, 0x00
};

const unsigned char unicode[]={
0x63, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x73, 0x00, 0x20, 0x00, 0x74, 0x00,
0x65, 0x00, 0x73, 0x00, 0x74, 0x00, 0x63, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x73, 0x00,
0x0D, 0x00, 0x0A, 0x00, 0x7B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 
0x53, 0x00, 0x54, 0x00, 0x52, 0x00, 0x49, 0x00, 0x4E, 0x00, 0x47, 0x00,
0x20, 0x00, 0x6B, 0x00, 0x3B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x55, 0x00, 0x69, 0x00, 0x6E, 0x00,
0x74, 0x00, 0x38, 0x00, 0x20, 0x00, 0x70, 0x00, 0x3B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x7D, 0x00,
0x3B, 0x00, 0x00, 0x00
};

const unsigned char utf16LE[]={
0xFF, 0xFE, 0x63, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x73, 0x00, 0x20, 0x00, 0x74, 0x00,
0x65, 0x00, 0x73, 0x00, 0x74, 0x00, 0x63, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x73, 0x00,
0x0D, 0x00, 0x0A, 0x00, 0x7B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 
0x53, 0x00, 0x54, 0x00, 0x52, 0x00, 0x49, 0x00, 0x4E, 0x00, 0x47, 0x00,
0x20, 0x00, 0x6B, 0x00, 0x3B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x55, 0x00, 0x69, 0x00, 0x6E, 0x00,
0x74, 0x00, 0x38, 0x00, 0x20, 0x00, 0x70, 0x00, 0x3B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x7D, 0x00,
0x3B, 0x00, 0x00, 0x00
};

const unsigned char utf16BE[]={
0xFE, 0xFF, 0x00, 0x63, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x73, 0x00, 0x20, 0x00, 0x74,
0x00, 0x65, 0x00, 0x73, 0x00, 0x74, 0x00, 0x63, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x73,
0x00, 0x0D, 0x00, 0x0A, 0x00, 0x7B, 0x00, 0x0D, 0x00, 0x0A, 
0x00, 0x53, 0x00, 0x54, 0x00, 0x52, 0x00, 0x49, 0x00, 0x4E, 0x00, 0x47, 
0x00, 0x20, 0x00, 0x6B, 0x00, 0x3B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x55, 0x00, 0x69, 0x00, 0x6E, 
0x00, 0x74, 0x00, 0x38, 0x00, 0x20, 0x00, 0x70, 0x00, 0x3B, 0x00, 0x0D, 0x00, 0x0A, 0x00, 0x7D, 
0x00, 0x3B, 0x00, 0x00
};

const MI_Char cWalias[] =
    MI_T("instance of C   \n")
    MI_T("//test comment \n")
    MI_T("{P1=1, p2=\"abcd\"} AS $abc;");

const MI_Char cWstr[] =
    MI_T("instance of C   \n")
    MI_T("{P1='c', p2=\"abcd\"       };");

const MI_Char cWChar16HEX[] =
    MI_T("instance of C   \n")
    MI_T("{P1='\\XABCD', p2=\"abcd\"       };");

const MI_Char cWChar16Escape[] =
    MI_T("instance of C   \n")
    MI_T("{P1='\\r', p2=\"abcd\"       };");

const MI_Char cWChar16Invalid[] =
    MI_T("instance of C   \n")
    MI_T("{P1='\\r', p2='ab'       };");

const MI_Char cWIntHEX[] =
    MI_T("instance of C   \n")
    MI_T("{P1=0, p2=0xFFFF };");

const MI_Char cWIntReal[] =
    MI_T("instance of C   \n")
    MI_T("{P1=+56, p2=-12.123E-019};");

const MI_Char cWReal[] =
    MI_T("instance of C   \n")
    MI_T("{p2=1212112.121231233};");

const MI_Char cWRealInvalid[] =
    MI_T("instance of C   \n")
    MI_T("{p2=1212112.121231233E};");

const MI_Char cWIntOctal[] =
    MI_T("instance of C   \n")
    MI_T("{p2=01237};");

const MI_Char cWIntOctalInvalid[] =
    MI_T("instance of C   \n")
    MI_T("{p2=01238};");

const MI_Char cWIntHEXOverflow[] =
   MI_T("instance of C   \n")
    MI_T("{Value=0x1FFFFFFFFFFFFFFFF };");

const MI_Char cWIntHEXMAX[] =
    MI_T("instance of C   \n")
    MI_T("{Value=0x7FFFFFFFFFFFFFFF };");

const char cAintstr[] =
    "instance of C   \n"
    "{P1=1, p2=\"abcd\"       } AS $abc;";

const char cACcomments[] =
    "/*test c style comments\n"
    "test c style comments\n"
    "/**************************/"
    "instance of C   \n"
    "{P1=1, p2=\"abcd\"       } AS $abc;";

const MI_Char cWCppComments[] =
    MI_T("instance of C   \n")
    MI_T("//test comment \n")
    MI_T("//test comment \n")
    MI_T("//test comment \n")
    MI_T("{P1=1, p2=\"abcd\"} AS $abc;");

const char cAClass[] =
    "class ABCD  {[key] string P1, uint8 p2};";

const char cAInstanceAlias[] =
    "Instance of A {P1=$t};";

const char cAqualifier[] =
    "[description(\"this is a class \\n\"\n"
    "\"now what?\")]\n\n\n\n\n\n"
    "class A {[key, override] string P1};";

const char cAinstalias[] =
    "instance of C   \n"
    "{P1='1'} AS $abc;";

LEX_TEST lextest[] =
{
    {"test1", cWalias, sizeof(cWalias), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("C")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("P1")},
            {'=', 0},
            {TOK_INTEGER_VALUE, 0X0000000000000001},
            {',', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("p2")},
            {'=', 0},
            {TOK_STRING_VALUE, 0},
            {'}', 0},
            {TOK_AS, 0},
            {TOK_ALIAS_IDENTIFIER, 0},
            {';', 0},
            {0, 0},
        }},

    {"test2", cWstr, sizeof(cWstr), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("C")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("P1")},
            {'=', 0},
            {TOK_CHAR_VALUE, 0X63},
            {',', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("p2")},
            {'=', 0},
            {TOK_STRING_VALUE, 0},
            {'}', 0},
            {';', 0},
            {0, 0},
        }},

    {"test3", cWChar16HEX, sizeof(cWChar16HEX), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("C")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("P1")},
            {'=', 0},
            {TOK_CHAR_VALUE, 0XABCD},
            {',', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("p2")},
            {'=', 0},
            {TOK_STRING_VALUE, 0},
            {'}', 0},
            {';', 0},
            {0, 0},
        }},

    {"test4", cWChar16Escape, sizeof(cWChar16Escape), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("C")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("P1")},
            {'=', 0},
            {TOK_CHAR_VALUE, 0XD},
            {',', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("p2")},
            {'=', 0},
            {TOK_STRING_VALUE, 0},
            {'}', 0},
            {';', 0},
            {0, 0},
        }},

    {"test5", cWChar16Invalid, sizeof(cWChar16Invalid), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("C")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("P1")},
            {'=', 0},
            {TOK_CHAR_VALUE, 0XD},
            {',', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("p2")},
            {'=', 0},
            {TOK_ERROR, 0},
            {0, 0},
        }},

    {"test6", cWIntHEX, sizeof(cWIntHEX), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("C")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("P1")},
            {'=', 0},
            {TOK_INTEGER_VALUE, 0X0000000000000000},
            {',', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("p2")},
            {'=', 0},
            {TOK_INTEGER_VALUE, 0X000000000000FFFF},
            {'}', 0},
            {';', 0},
            {0, 0},
        }},

    {"test7", cWIntReal, sizeof(cWIntReal), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("C")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("P1")},
            {'=', 0},
            {TOK_INTEGER_VALUE, 0X0000000000000038},
            {',', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("p2")},
            {'=', 0},
            {TOK_REAL_VALUE, (ptrdiff_t)(-1.2123E-018)},
            {'}', 0},
            {';', 0},
            {0, 0},
        }},

    {"test8", cWReal, sizeof(cWReal), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("C")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("p2")},
            {'=', 0},
            {TOK_REAL_VALUE, (ptrdiff_t)(1.21211E+006)},
            {'}', 0},
            {';', 0},
            {0, 0},
        }},

    {"test9", cWRealInvalid, sizeof(cWRealInvalid), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("C")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("p2")},
            {'=', 0},
            {TOK_ERROR, 0},
            {0, 0},
        }},

    {"test10", cWIntOctal, sizeof(cWIntOctal), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("C")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("p2")},
            {'=', 0},
            {TOK_INTEGER_VALUE, 0X000000000000029F},
            {'}', 0},
            {';', 0},
            {0, 0},
        }},

    {"test11", cWIntOctalInvalid, sizeof(cWIntOctalInvalid), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("C")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("p2")},
            {'=', 0},
            {TOK_ERROR, 0},
            {0, 0},
        }},

    {"test12", cWIntHEXOverflow, sizeof(cWIntHEXOverflow), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("C")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("Value")},
            {'=', 0},
            {TOK_ERROR, 0},
            {0, 0},
        }},

#if (defined(linux) && __x86_64__) || defined(macos)
    // This breaks on solaris, hpux, aix due to limitations of their strtoull

    {"test13", cWIntHEXMAX, sizeof(cWIntHEXMAX), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("C")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("Value")},
            {'=', 0},
            {TOK_INTEGER_VALUE, (ptrdiff_t)0X7FFFFFFFFFFFFFFF},
            {'}', 0},
            {';', 0},
            {0, 0},
        }},
#endif

    {"test14", cAintstr, sizeof(cAintstr), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("C")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("P1")},
            {'=', 0},
            {TOK_INTEGER_VALUE, 0X0000000000000001},
            {',', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("p2")},
            {'=', 0},
            {TOK_STRING_VALUE, 0},
            {'}', 0},
            {TOK_AS, 0},
            {TOK_ALIAS_IDENTIFIER, 0},
            {';', 0},
            {0, 0},
        }},

    {"test15", cACcomments, sizeof(cACcomments), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("C")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("P1")},
            {'=', 0},
            {TOK_INTEGER_VALUE, 0X0000000000000001},
            {',', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("p2")},
            {'=', 0},
            {TOK_STRING_VALUE, 0},
            {'}', 0},
            {TOK_AS, 0},
            {TOK_ALIAS_IDENTIFIER, 0},
            {';', 0},
            {0, 0},
        }},

    {"test16", cWCppComments, sizeof(cWCppComments), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("C")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("P1")},
            {'=', 0},
            {TOK_INTEGER_VALUE, 0X0000000000000001},
            {',', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("p2")},
            {'=', 0},
            {TOK_STRING_VALUE, 0},
            {'}', 0},
            {TOK_AS, 0},
            {TOK_ALIAS_IDENTIFIER, 0},
            {';', 0},
            {0, 0},
        }},

    {"test17", cAClass, sizeof(cAClass), {
            {TOK_CLASS, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("ABCD")},
            {'{', 0},
            {'[', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("key")},
            {']', 0},
            {TOK_STRING, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("P1")},
            {',', 0},
            {TOK_UINT8, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("p2")},
            {'}', 0},
            {';', 0},
            {0, 0},
        }},

    {"test18", cAInstanceAlias, sizeof(cAInstanceAlias), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("A")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("P1")},
            {'=', 0},
            {TOK_ALIAS_IDENTIFIER, 0},
            {'}', 0},
            {';', 0},
            {0, 0},
        }},

    {"test19", cAqualifier, sizeof(cAqualifier), {
            {'[', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("description")},
            {'(', 0},
            {TOK_STRING_VALUE, 0},
            {TOK_STRING_VALUE, 0},
            {')', 0},
            {']', 0},
            {TOK_CLASS, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("A")},
            {'{', 0},
            {'[', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("key")},
            {',', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("override")},
            {']', 0},
            {TOK_STRING, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("P1")},
            {'}', 0},
            {';', 0},
            {0, 0},
        }},

    {"test20", cAinstalias, sizeof(cAinstalias), {
            {TOK_INSTANCE, 0},
            {TOK_OF, 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("C")},
            {'{', 0},
            {TOK_IDENT, (ptrdiff_t)MI_T("P1")},
            {'=', 0},
            {TOK_CHAR_VALUE, 0X31},
            {'}', 0},
            {TOK_AS, 0},
            {TOK_ALIAS_IDENTIFIER, 0},
            {';', 0},
            {0, 0},
        }},
    {0, 0, 0, {{0,0}}}
};

const MI_ClassDecl cMintSchema[] = 
{
    {0, 0, MI_T("MSFT_Expression"),                 NULL, 0, NULL, 2, 0 },
    {0, 0, MI_T("MSFT_ExpressionIdentifier"),       NULL, 0, NULL, 3, 0 },
    {0, 0, MI_T("MSFT_ExpressionKeywordParameter"), NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionKeywordValue"),     NULL, 0, NULL, 3, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue"),            NULL, 0, NULL, 3, 0 },
    {0, 0, MI_T("MSFT_ExpressionCall"),             NULL, 0, NULL, 5, 0 },
    {0, 0, MI_T("MSFT_ExpressionLambda"),           NULL, 0, NULL, 5, 0 },
    {0, 0, MI_T("MSFT_ExpressionIf"),               NULL, 0, NULL, 5, 0 },
    {0, 0, MI_T("MSFT_ExpressionLoop"),             NULL, 0, NULL, 5, 0 },
    {0, 0, MI_T("MSFT_ExpressionAssignment"),       NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionLet"),              NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionBegin"),            NULL, 0, NULL, 3, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_boolean"),    NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_uint8"),      NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_sint8"),      NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_uint16"),     NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_sint16"),     NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_uint32"),     NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_sint32"),     NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_uint64"),     NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_sint64"),     NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_real32"),     NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_real64"),     NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_char16"),     NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_datetime"),   NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_string"),     NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_booleana"),   NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_uint8a"),     NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_sint8a"),     NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_uint16a"),    NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_sint16a"),    NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_uint32a"),    NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_sint32a"),    NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_uint64a"),    NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_sint64a"),    NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_real32a"),    NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_real64a"),    NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_char16a"),    NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_datetimea"),  NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_ExpressionValue_stringa"),    NULL, 0, NULL, 4, 0 },
};

const MI_Uint32 cMintSchemaCount = 40;


const MI_ClassDecl cDscSchema[] = 
{
    {0, 0, MI_T("MSFT_BaseCredential"),             NULL, 0, NULL, 2, 0 },
    {0, 0, MI_T("MSFT_WindowsCredential"),          NULL, 0, NULL, 3, 0 },
    {0, 0, MI_T("MSFT_BaseResourceConfiguration"),  NULL, 0, NULL, 4, 0 },
    {0, 0, MI_T("MSFT_FileDirectoryConfiguration"), NULL, 0, NULL, 17, 0 },
    {0, 0, MI_T("MSFT_ConfigurationDocument"),      NULL, 0, NULL, 4, 0 },
};

const MI_Uint32 cDscSchemaCount = 5;



/*=============================================================================
**
** Failure test cases for mof parser
**
=============================================================================*/
#define MOF_PROPERTY_NOT_CLOSED "instance of C   \n"\
 "{test=\"abc\"};"

#define MOF_PROPERTY_DOUBLE_SEMICOLON     "instance of C\n"\
    "{Value=1;; test='C'};"

#define MOF_INSTASNCE_DOUBLE_BRACKET    "instance of D {{"\
    "instane of D {{"

#define MOF_INSTASNCE_WRONG_ALIAS_VALUE    "INSTANCe of MSFT_STOCK {price=$40, "

#define MOF_INSTASNCE_WRONG_ROPERTY_NAME    "INSTANCe of MSFT_STOCK {123ABC=A, "

#define MOF_INSTASNCE_WRONG_PROPERTY_NAME_LINE    "\n\nINSTANCe \n\nof \n\n\nMSFT_STOCK {123ABC=A, "

#define MOF_INSTASNCE_WRONG_PRAGMA_TOKEN    "#pragmax include \"x.mof\""

#define MOF_INSTASNCE_WRONG_PRAGMA_VALUE    "#pragma INVALID \"x.mof\""

#define MOF_INSTASNCE_STRING_INCOMPLETE    "[description(\"this is a test) ]class A{string key;};"

#define MOF_INSTASNCE_CHAR16_EMPTY    "instance of A{key='';};"

#define MOF_INSTASNCE_CHAR16_ESCAPED_INCOMPLETE    "instance of A{key='\\;};"

#define MOF_INSTASNCE_CHAR16_ESCAPED_HEX_LONG    "instance of A{key='\\x123456';};"

#define MOF_INSTASNCE_CHAR16_ESCAPED_HEX_NON_NUMBER    "instance of A{key='\\xZGD';};"

#define MOF_INSTASNCE_CHAR16_ESCAPED_TWO_CHAR    "instance of A{key='\\rr';};"

#define MOF_INSTASNCE_CHAR16_ESCAPED_INVALID_CHAR    "instance of A{key='\\m';};"

#define MOF_INSTASNCE_CHAR16_INVALID_CHAR    "instance of A{key='cc';};"

#define MOF_INSTASNCE_CHAR16_EOF_BUFFER    "instance of A{key='"

#define MOF_INVALID_COMMENT_NON_CLOSED "/*asnfasdfsdf instance of C"

#define MOF_INVALID_COMMENT_INVALID "/asnfasdfsdf instance of C"

#define MOF_ERROR_TYPE MI_RESULT_TYPE_MOF_PARSER

InvalidMofResult InvalidMofs[] =
{
    {
        MOF_PROPERTY_NOT_CLOSED,
        sizeof(MOF_PROPERTY_NOT_CLOSED),
        MI_RESULT_FAILED,
        ID_SYNTAX_ERROR,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL},
    {
        MOF_PROPERTY_DOUBLE_SEMICOLON,
        sizeof(MOF_PROPERTY_DOUBLE_SEMICOLON),
        MI_RESULT_FAILED,
        ID_SYNTAX_ERROR,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL},
    {
        MOF_INSTASNCE_DOUBLE_BRACKET,
        sizeof(MOF_INSTASNCE_DOUBLE_BRACKET),
        MI_RESULT_FAILED,
        ID_SYNTAX_ERROR,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL},
    {
        MOF_INSTASNCE_WRONG_ALIAS_VALUE,
        sizeof(MOF_INSTASNCE_WRONG_ALIAS_VALUE),
        MI_RESULT_FAILED,
        ID_SYNTAX_ERROR_INVALID_TOKEN,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL},
    {
        MOF_INSTASNCE_WRONG_ROPERTY_NAME,
        sizeof(MOF_INSTASNCE_WRONG_ROPERTY_NAME),
        MI_RESULT_FAILED,
        ID_SYNTAX_ERROR_INVALID_NUMBER_VALUE,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL},
    {
        MOF_INSTASNCE_WRONG_PROPERTY_NAME_LINE,
        sizeof(MOF_INSTASNCE_WRONG_PROPERTY_NAME_LINE),
        MI_RESULT_FAILED,
        ID_SYNTAX_ERROR_INVALID_NUMBER_VALUE, 
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL},
    {
        MOF_INSTASNCE_WRONG_PRAGMA_TOKEN,
        sizeof(MOF_INSTASNCE_WRONG_PRAGMA_TOKEN),
        MI_RESULT_FAILED,
        ID_SYNTAX_ERROR_INVALID_TOKEN,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL},
    {
        MOF_INSTASNCE_WRONG_PRAGMA_VALUE,
        sizeof(MOF_INSTASNCE_WRONG_PRAGMA_VALUE),
        MI_RESULT_FAILED,
        ID_SYNTAX_ERROR,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL
    },

    {
        MOF_INSTASNCE_STRING_INCOMPLETE,
        sizeof(MOF_INSTASNCE_STRING_INCOMPLETE),
        MI_RESULT_FAILED,
        ID_SYNTAX_ERROR_INCOMPLETE_STRING_VALUE,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL
    },
    
    {
        MOF_INSTASNCE_CHAR16_EMPTY,
        sizeof(MOF_INSTASNCE_CHAR16_EMPTY),
        MI_RESULT_FAILED,
        ID_SYNTAX_ERROR_INVALID_CHAR16_VALUE,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL
    },

    {
        MOF_INSTASNCE_CHAR16_ESCAPED_INCOMPLETE,
        sizeof(MOF_INSTASNCE_CHAR16_ESCAPED_INCOMPLETE),
        MI_RESULT_FAILED,
        ID_SYNTAX_ERROR_INCOMPLETE_ESCAPED_CHAR16_VALUE,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL
    },

    {
        MOF_INSTASNCE_CHAR16_ESCAPED_HEX_LONG,
        sizeof(MOF_INSTASNCE_CHAR16_ESCAPED_HEX_LONG),
        MI_RESULT_FAILED,
        ID_ILLEGAL_HEX_CHARACTER,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL
    },

    {
        MOF_INSTASNCE_CHAR16_ESCAPED_HEX_NON_NUMBER,
        sizeof(MOF_INSTASNCE_CHAR16_ESCAPED_HEX_NON_NUMBER),
        MI_RESULT_FAILED,
        ID_ILLEGAL_HEX_CHARACTER,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL
    },

    {
        MOF_INSTASNCE_CHAR16_ESCAPED_TWO_CHAR,
        sizeof(MOF_INSTASNCE_CHAR16_ESCAPED_TWO_CHAR),
        MI_RESULT_FAILED,
        ID_SYNTAX_ERROR_INVALID_ESCAPED_CHAR16_VALUE,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL
    },
    
    {
        MOF_INSTASNCE_CHAR16_ESCAPED_INVALID_CHAR,
        sizeof(MOF_INSTASNCE_CHAR16_ESCAPED_INVALID_CHAR),
        MI_RESULT_FAILED,
        ID_SYNTAX_ERROR_INVALID_ESCAPED_CHAR,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL
    },
    
    {
        MOF_INSTASNCE_CHAR16_INVALID_CHAR,
        sizeof(MOF_INSTASNCE_CHAR16_INVALID_CHAR),
        MI_RESULT_FAILED,
        ID_SYNTAX_ERROR_INVALID_CHAR16_VALUE,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL
    },
    
    {
        MOF_INSTASNCE_CHAR16_EOF_BUFFER,
        sizeof(MOF_INSTASNCE_CHAR16_EOF_BUFFER),
        MI_RESULT_FAILED,
        ID_SYNTAX_ERROR_INVALID_CHAR16_VALUE,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL
    },
    
    {
        MOF_INVALID_COMMENT_NON_CLOSED,
        sizeof(MOF_INVALID_COMMENT_NON_CLOSED),
        MI_RESULT_FAILED,
        ID_SYNTAX_ERROR_INVALID_COMMENT,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL
    },

    {
        MOF_INVALID_COMMENT_INVALID,
        sizeof(MOF_INVALID_COMMENT_INVALID),
        MI_RESULT_FAILED,
        ID_SYNTAX_ERROR,
        MI_ERRORCATEGORY_SYNTAX_ERROR,
        MOF_ERROR_TYPE,
        NULL,
        NULL
    },

    {NULL, 0, MI_RESULT_OK, 0, 0, NULL, NULL, NULL}
};
