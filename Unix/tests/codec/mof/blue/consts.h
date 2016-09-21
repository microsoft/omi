/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _mof_test_consts_h
#define _mof_test_consts_h

#ifdef __cplusplus
extern "C" {
#endif

#include "MI.h"

typedef struct _PARSER_TEST
{
    char *testName;
    const void *ansi;
    const void *utf8;
    const void *unicode;
    const void *utf16LE;
    const void *utf16BE;
}PARSER_TEST;


#define MAX_TOKEN 128
typedef struct _LEX_RESULT
{
    int tok;
    ptrdiff_t data;
}LEX_RESULT;

typedef struct _LEX_TEST
{
    char *testName;
    const void *buf;
    size_t size;
    LEX_RESULT expected[MAX_TOKEN];
}LEX_TEST;

extern const wchar_t * TOKEN_STR [];

extern const unsigned char ansi1[];

extern const unsigned char utf81[];

extern const unsigned char unicode1[];

extern const unsigned char utf16LE1[];

extern const unsigned char utf16BE1[];

extern const unsigned char ansi[];

extern const unsigned char utf8[];

extern const unsigned char unicode[];

extern const unsigned char utf16LE[];

extern const unsigned char utf16BE[];

extern const MI_Char cWalias[];

extern const MI_Char cWstr[];

extern const MI_Char cWChar16HEX[];

extern const MI_Char cWChar16Escape[];

extern const MI_Char cWChar16Invalid[];

extern const MI_Char cWIntHEX[];

extern const MI_Char cWIntReal[];

extern const MI_Char cWReal[];

extern const MI_Char cWRealInvalid[];

extern const MI_Char cWIntOctal[];

extern const MI_Char cWIntOctalInvalid[];

extern const MI_Char cWIntHEXOverflow[];

extern const MI_Char cWIntHEXMAX[];

extern const char cAintstr[];

extern const char cACcomments[];

extern const MI_Char cWCppComments[];

extern const char cAClass[];

extern const char cAInstanceAlias[];

extern const char cAqualifier[];

extern const char cAinstalias[];

extern LEX_TEST lextest[];

extern const MI_Uint32 cMintSchemaCount;
extern const MI_ClassDecl cMintSchema[];

extern const MI_Uint32 cDscSchemaCount;
extern const MI_ClassDecl cDscSchema[];

typedef struct _InvalidMofResult
{
    void* mofdata;
    MI_Uint32 mofdatalen;

    MI_Result r;
    MI_Uint32 errcode;
    MI_Uint16 errorcategory;
    const MI_Char * errtype;
    const MI_Char *errmsg;
    const MI_Char *errclassname;
}InvalidMofResult;
extern InvalidMofResult InvalidMofs[];

void FinalizeTestData();

#ifdef __cplusplus
}
#endif

#endif /* _mof_test_consts_h */
