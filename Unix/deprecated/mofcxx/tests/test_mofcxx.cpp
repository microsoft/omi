/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <mofcxx/mofcxx.h>
#include <pal/strings.h>
#include <base/paths.h>
#include <base/helpers.h>
#include <ut/ut.h>

using namespace mofcxx;
using namespace std;

NitsSetup(TestMofCxxSetup)
NitsEndSetup

NitsCleanup(TestMofCxxSetup)
NitsEndCleanup

static size_t numClasses = 0;
static size_t numInstances = 0;

const MI_PropertyDecl* _FindPropertyDecl(
    const MI_InstanceDecl* decl, 
    const char* name)
{
    MI_Uint32 i;

    for (i = 0; i < decl->numProperties; i++)
    {
        if (Strcasecmp(decl->properties[i]->name, name) == 0)
        {
            return decl->properties[i];
        }
    }

    return NULL;
}

MI_Boolean _MatchDatetime(const MI_Datetime x, const char* str)
{
    char buf[26];
    DatetimeToStr(&x, buf);

    if (strcmp(buf, str) == 0)
        return MI_TRUE;

    return MI_FALSE;
}

class Handler : public MOFParserHandler
{
public:

    virtual ~Handler()
    {
    }

    virtual void HandleError(const char* msg)
    {
        UT_ASSERT(0);
    }

    virtual void HandleWarning(const char* msg)
    {
        UT_ASSERT(0);
    }

    virtual void HandlePragma(const char* name, const char* value)
    {
        printf("PRAGMA: %s %s\n", name, value);
    }

    virtual void HandleClassDecl(const MI_ClassDecl* decl)
    {
        numClasses++;
        UT_ASSERT(Strcasecmp(decl->name, "X") == 0);
    }

    virtual void HandleInstanceDecl(const MI_InstanceDecl* decl)
    {
        numInstances++;
        UT_ASSERT(Strcasecmp(decl->name, "X") == 0);

        const MI_PropertyDecl* pd;
        pd = _FindPropertyDecl(decl, "b");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_BOOLEAN);
        UT_ASSERT(*((MI_Boolean*)pd->value) == MI_TRUE);

        pd = _FindPropertyDecl(decl, "u8");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_UINT8);
        UT_ASSERT(*((MI_Uint8*)pd->value) == 8);

        pd = _FindPropertyDecl(decl, "s8");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_SINT8);
        UT_ASSERT(*((MI_Sint8*)pd->value) == -8);

        pd = _FindPropertyDecl(decl, "u16");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_UINT16);
        UT_ASSERT(*((MI_Uint16*)pd->value) == 16);

        pd = _FindPropertyDecl(decl, "s16");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_SINT16);
        UT_ASSERT(*((MI_Sint16*)pd->value) == -16);

        pd = _FindPropertyDecl(decl, "u32");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_UINT32);
        UT_ASSERT(*((MI_Uint32*)pd->value) == 32);

        pd = _FindPropertyDecl(decl, "s32");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_SINT32);
        UT_ASSERT(*((MI_Sint32*)pd->value) == -32);

        pd = _FindPropertyDecl(decl, "u64");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_UINT64);
        UT_ASSERT(*((MI_Uint64*)pd->value) == 64);

        pd = _FindPropertyDecl(decl, "s64");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_SINT64);
        UT_ASSERT(*((MI_Sint64*)pd->value) == -64);

        pd = _FindPropertyDecl(decl, "r32");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_REAL32);
        UT_ASSERT(*((MI_Real32*)pd->value) > 32);
        UT_ASSERT(*((MI_Real32*)pd->value) < 33);

        pd = _FindPropertyDecl(decl, "r64");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_REAL64);
        UT_ASSERT(*((MI_Real64*)pd->value) > 64);
        UT_ASSERT(*((MI_Real64*)pd->value) < 65);

        pd = _FindPropertyDecl(decl, "c16");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_CHAR16);
        UT_ASSERT(*((MI_Char16*)pd->value) == 'A');

        pd = _FindPropertyDecl(decl, "s");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_STRING);
        UT_ASSERT(strcmp((char*)pd->value, "String") == 0);

        pd = _FindPropertyDecl(decl, "dt");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_DATETIME);
        UT_ASSERT(_MatchDatetime(*((MI_Datetime*)pd->value), 
            "20101231120000.123456+360"));

        pd = _FindPropertyDecl(decl, "ba");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_BOOLEANA);
        UT_ASSERT(((MI_BooleanA*)pd->value)->size == 3);
        UT_ASSERT(((MI_BooleanA*)pd->value)->data[0] == MI_TRUE);
        UT_ASSERT(((MI_BooleanA*)pd->value)->data[1] == MI_FALSE);
        UT_ASSERT(((MI_BooleanA*)pd->value)->data[2] == MI_TRUE);

        pd = _FindPropertyDecl(decl, "u8a");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_UINT8A);
        UT_ASSERT(((MI_Uint8A*)pd->value)->size == 3);
        UT_ASSERT(((MI_Uint8A*)pd->value)->data[0] == 8);
        UT_ASSERT(((MI_Uint8A*)pd->value)->data[1] == 8+1);
        UT_ASSERT(((MI_Uint8A*)pd->value)->data[2] == 8+2);

        pd = _FindPropertyDecl(decl, "s8a");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_SINT8A);
        UT_ASSERT(((MI_Sint8A*)pd->value)->size == 3);
        UT_ASSERT(((MI_Sint8A*)pd->value)->data[0] == -8);
        UT_ASSERT(((MI_Sint8A*)pd->value)->data[1] == -8-1);
        UT_ASSERT(((MI_Sint8A*)pd->value)->data[2] == -8-2);

        pd = _FindPropertyDecl(decl, "u16a");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_UINT16A);
        UT_ASSERT(((MI_Uint16A*)pd->value)->size == 2);
        UT_ASSERT(((MI_Uint16A*)pd->value)->data[0] == 16);
        UT_ASSERT(((MI_Uint16A*)pd->value)->data[1] == 16+1);

        pd = _FindPropertyDecl(decl, "s16a");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_SINT16A);
        UT_ASSERT(((MI_Sint16A*)pd->value)->size == 2);
        UT_ASSERT(((MI_Sint16A*)pd->value)->data[0] == -16);
        UT_ASSERT(((MI_Sint16A*)pd->value)->data[1] == -16-1);

        pd = _FindPropertyDecl(decl, "u32a");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_UINT32A);
        UT_ASSERT(((MI_Uint32A*)pd->value)->size == 2);
        UT_ASSERT(((MI_Uint32A*)pd->value)->data[0] == 32);
        UT_ASSERT(((MI_Uint32A*)pd->value)->data[1] == 32+1);

        pd = _FindPropertyDecl(decl, "s32a");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_SINT32A);
        UT_ASSERT(((MI_Sint32A*)pd->value)->size == 2);
        UT_ASSERT(((MI_Sint32A*)pd->value)->data[0] == -32);
        UT_ASSERT(((MI_Sint32A*)pd->value)->data[1] == -32-1);

        pd = _FindPropertyDecl(decl, "u64a");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_UINT64A);
        UT_ASSERT(((MI_Uint64A*)pd->value)->size == 2);
        UT_ASSERT(((MI_Uint64A*)pd->value)->data[0] == 64);
        UT_ASSERT(((MI_Uint64A*)pd->value)->data[1] == 64+1);

        pd = _FindPropertyDecl(decl, "s64a");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_SINT64A);
        UT_ASSERT(((MI_Sint64A*)pd->value)->size == 2);
        UT_ASSERT(((MI_Sint64A*)pd->value)->data[0] == -64);
        UT_ASSERT(((MI_Sint64A*)pd->value)->data[1] == -64-1);

        pd = _FindPropertyDecl(decl, "r32a");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_REAL32A);
        UT_ASSERT(((MI_Real32A*)pd->value)->size == 2);
        UT_ASSERT(((MI_Real32A*)pd->value)->data[0] > 32);
        UT_ASSERT(((MI_Real32A*)pd->value)->data[0] < 32+1);
        UT_ASSERT(((MI_Real32A*)pd->value)->data[1] > 32+1);
        UT_ASSERT(((MI_Real32A*)pd->value)->data[1] < 32+2);

        pd = _FindPropertyDecl(decl, "r64a");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_REAL64A);
        UT_ASSERT(((MI_Real64A*)pd->value)->size == 2);
        UT_ASSERT(((MI_Real64A*)pd->value)->data[0] > 64);
        UT_ASSERT(((MI_Real64A*)pd->value)->data[0] < 64+1);
        UT_ASSERT(((MI_Real64A*)pd->value)->data[1] > 64+1);
        UT_ASSERT(((MI_Real64A*)pd->value)->data[1] < 64+2);

        pd = _FindPropertyDecl(decl, "c16a");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_CHAR16A);
        UT_ASSERT(((MI_Char16A*)pd->value)->size == 3);
        UT_ASSERT(((MI_Char16A*)pd->value)->data[0] == 'A');
        UT_ASSERT(((MI_Char16A*)pd->value)->data[1] == 'B');
        UT_ASSERT(((MI_Char16A*)pd->value)->data[2] == 'C');

        pd = _FindPropertyDecl(decl, "sa");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_STRINGA);
        UT_ASSERT(((MI_StringA*)pd->value)->size == 3);
        UT_ASSERT(strcmp(((MI_StringA*)pd->value)->data[0], "Red") == 0);
        UT_ASSERT(strcmp(((MI_StringA*)pd->value)->data[1], "Green") == 0);
        UT_ASSERT(strcmp(((MI_StringA*)pd->value)->data[2], "Blue") == 0);

        pd = _FindPropertyDecl(decl, "dta");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_DATETIMEA);
        UT_ASSERT(((MI_StringA*)pd->value)->size == 1);
        UT_ASSERT(_MatchDatetime(((MI_DatetimeA*)pd->value)->data[0],
            "20101231120000.123456+360"));

        pd = _FindPropertyDecl(decl, "empty");
        UT_ASSERT(pd != NULL);
        UT_ASSERT(pd->type == MI_STRINGA);
        UT_ASSERT(pd->value == NULL);
    }

    virtual void HandleQualifierDecl(const MI_QualifierDecl* decl)
    {
    }
};

NitsTestWithSetup(Test1, TestMofCxxSetup)
{
    vector<string> paths;
    paths.push_back(".");

    /* Create handler */
    Handler* handler = new Handler;

    /* Create parser */
    MOFParser parser(paths, handler);

    /* Form path to MOF file */
    char path[MAX_PATH_SIZE];
    Strlcpy(path, GetPath(ID_PREFIX), sizeof(path));
    Strlcat(path, "/mofcxx/tests/sample.mof", sizeof(path));

    /* Parse document */
    int r = parser.Parse(path);
    UT_ASSERT(r == 0);

    UT_ASSERT(numClasses == 1);
    UT_ASSERT(numInstances == 1);

#if 0
    /* Dump */
    parser.Dump();
#endif

    /* Delete handler */
    delete handler;
}
NitsEndTest
