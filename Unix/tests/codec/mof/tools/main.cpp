/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <string.h>
#include <string>
#include <ctype.h>
#include <MI.h>
#include <state.h>
#include <mofyacc.h>
#include <moftoken.h>
#include <mofparser.h>
#include <tests/codec/mof/util/util.h>

using namespace std;

#define CLASSCOUNT 1000000

/*=============================================================================
**
** Define token strings
**
=============================================================================*/
static const char * ansiTokenStrings [] =
{
    // BOOLEAN VALUE
    "TOK_BOOLEAN_VALUE",
    "TOK_BOOLEAN_VALUE",
    // Null value
    "TOK_NULL",
    // DATATYPES
    "TOK_BOOLEAN",
    "TOK_SINT8",
    "TOK_UINT8",
    "TOK_SINT16",
    "TOK_UINT16",
    "TOK_SINT32",
    "TOK_UINT32",
    "TOK_SINT64",
    "TOK_UINT64",
    "TOK_REAL32",
    "TOK_REAL64",
    "TOK_DATETIME",
    "TOK_CHAR16",
    "TOK_STRING",
    // REF
    "TOK_REF",
    // SCOPE
    "TOK_SCOPE",
    "TOK_CLASS",
    "TOK_ASSOCIATION",
    "TOK_INDICATION",
    "TOK_QUALIFIER",
    "TOK_PROPERTY",
    "TOK_REFERENCE",
    "TOK_METHOD",
    "TOK_PARAMETER",
    "TOK_ANY",
    // FLAVOR
    "TOK_FLAVOR",
    "TOK_ENABLEOVERRIDE",
    "TOK_DISABLEOVERRIDE",
    "TOK_RESTRICTED",
    "TOK_TOSUBCLASS",
    "TOK_TRANSLATABLE",
    // Instance of
    "TOK_INSTANCE",
    "TOK_OF",
    // Alias
    "TOK_AS",
    // #pragma
    "TOK_PRAGMA",
    NULL
};

const wchar_t * unicodeTokenStrings [] =
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

/*=============================================================================
**
** Print token with hashcode
**
=============================================================================*/
void printTokens()
{
    const MOF_Token * s = _catokens;
    const char ** t = ansiTokenStrings;
    while(s->str.data != NULL)
    {
        size_t len = strlen(s->str.str);
        unsigned int code = 0;
        int c1 = tolower(s->str.str[0]);
        int c2 = tolower(s->str.str[len -1]);
        code += (c1 << 16);
        code += (c2 << 8);
        code += (unsigned char)(len);
        printf ("{\"%s\", 0x%08X, %s}\n", s->str.str, code, *t);
        s++;
        t++;
    }
}

/*=============================================================================
**
** Print single token char table
** These single char are treated as token in the MOF parser
**
=============================================================================*/
void printSingleCharTable()
{
    static char sc[] = {'=', '(', ')', '[',']','{', '}', ':', ';', ','};
    static char table[256];
    memset(table, 0, sizeof(table));
    printf ("{");
    for (size_t i = 0; i < sizeof(sc); i++)
    {
        table[sc[i]] = TOKEN_SINGLE_CHAR_FLAG;
    }
    for (size_t i = 0; i < sizeof(table); i++)
    {
        if ( i % 32 == 0) printf("\n");
        if ( i != 0) printf(", ");
        printf("%d", table[i]);
    }
    printf ("}");
}

/*=============================================================================
**
** Read content from file and translate to string defition in C code
**
=============================================================================*/
void file2str(const char * file, const char * opt)
{
    FILE* fp = fopen(file, "r");
    if(fp == NULL)
    {
        printf("can't open file (%s), errorno (%d).", file, errno);
        return;
    }
    static const size_t bufsize=4096;
    static const size_t linesize=1024;
    char buf[4096];
    char line[linesize];
    size_t linep=0;
    bool ansi = true;
    if (_stricmp(opt, "-u") == 0) ansi = false;
    char * fmt = ansi ? "\"%s\\\n\"\n" : "L\"%s\\n\"\n";

    while(!feof(fp))
    {
        size_t r = fread(buf, 1, sizeof(buf), fp);
        for(size_t i = 0; i < r; i++)
        {
            if (buf[i] == '\n')
            {
                _Analysis_assume_(linep < linesize);
                line[linep++] = '\0';
                printf(fmt, line);
                linep = 0;
            }
            else if (buf[i] != '\r')
            {
                if (buf[i] == '"')
                {
                    _Analysis_assume_(linep < linesize);
                    line[linep++] = '\\';
                }
                _Analysis_assume_(linep < linesize);
                line[linep++] = buf[i];
            }
        }
    }
    fclose(fp);
    if (linep > 0)
    {
        _Analysis_assume_(linep < linesize);
        line[linep++] = '\0';
        printf(fmt, line);
        linep = 0;
    }
}

/*=============================================================================
**
** Parse file and print all TOKEN(s)
**
=============================================================================*/
MOF_Parser* CreateParser(_In_z_ const char * file, _Outptr_result_maybenull_ char** ppbuf)
{
    char * mofbuffer;
    size_t length;
    int r0 = getFileContent((char *)file, &mofbuffer, &length);
    if (r0 != 0)
    {
        printf("can't open file (%s), errorno (%d).", file, errno);
        *ppbuf = NULL;
        return NULL;
    }
    *ppbuf = mofbuffer;
    return MOF_Parser_Init(mofbuffer, (MI_Uint32)length, NULL, NULL);
}

/*=============================================================================
**
** Parse file and print all TOKEN(s)
**
=============================================================================*/
static void LexParse(_In_z_ const char * file)
{
    char *buf = NULL;
    MOF_Parser * parser = CreateParser(file, &buf);
    if (parser == NULL)
    {
        printf("failed to create the parser from file (%s).\n", file);
        return;
    }
    MOF_State * state = (MOF_State*)parser->state;
    int t = MOF_Parser_ParseLex(parser);
    while (t !=0)
    {
        if (t >=257 && t < 302)
        {
            const wchar_t* tokstr = unicodeTokenStrings[t-257];
            if (t == TOK_ERROR)
            {
                wprintf(L"            {%s, 0},\n", tokstr);
                break;
            }
            if (t == TOK_IDENT)
            {
                wprintf(L"            {%s, (ptrdiff_t)MI_T(\"%s\")},\n", tokstr, state->ystate.moflval.string);
            }
            else if (t == TOK_CHAR_VALUE)
            {
                wprintf(L"            {%s, 0X%X},\n", tokstr, state->ystate.moflval.character);
            }
            else if (t == TOK_INTEGER_VALUE)
            {
                wprintf(L"            {%s, 0X%016llX},\n", tokstr, state->ystate.moflval.integer);
            }
            else if (t == TOK_REAL_VALUE)
            {
                wprintf(L"            {%s, (ptrdiff_t)(%LG)},\n", tokstr, state->ystate.moflval.real);
            }
            else
                wprintf(L"            {%s, 0},\n", tokstr);
        }
        else if ( t >0 && t < 255)
        {
            wprintf(L"            {\'%c\', 0},\n", t);
        }
        t = MOF_Parser_ParseLex(parser);
    }
    wprintf(L"            {0, 0},\n");
    if (buf) free(buf);
    MOF_Parser_Delete(parser);
}

/*=============================================================================
**
** Parse given mof file and print all qualifiers definitions in C,
** in MI_QualifierDecl format.
**
=============================================================================*/
void printQualifier(_In_z_ const char * file)
{
    char* buf;
    MOF_Parser * parser = CreateParser(file, &buf);
    if (parser == NULL)
    {
        printf("failed to create the parser from file (%s).\n", file);
        return;
    }
    MOF_State * state = (MOF_State*)parser->state;
    int r = MOF_Parser_Parse(parser);
    if (r != 0)
    {
        printf("failed to parse the file (%s).\n", file);
        if (buf) free(buf);
        return;
    }
    if (state->qualifierDecls.size > 0)
    {
        MI_Uint32 c = 0;
        static char * gQualval = "gQualval";
        printf ("MI_Boolean %s%d = %s;\n", gQualval, c++, "MI_TRUE");
        printf ("MI_Boolean %s%d = %s;\n", gQualval, c++, "MI_FALSE");

        for (MI_Uint32 i=0; i <state->qualifierDecls.size; i ++)
        {
            MI_QualifierDecl * decl = state->qualifierDecls.data[i];
            if(decl->value != NULL)
            {
                if (decl->type == MI_BOOLEAN)
                {                    
                }
                else if (decl->type == MI_UINT32)
                {
                    printf ("MI_Uint32 %s%d = %d;\n", gQualval, c++, *(MI_Uint32*)decl->value);
                }
                else if (decl->type == MI_STRING)
                {
                    printf ("MI_Char*  %s%d = MI_T(\"%S\");\n", gQualval, c++, *(MI_Char**)decl->value);
                }
                else {printf ("\t\tUnsupported qualifier value type!\n");}
            }
        }

        MI_Uint32 vindex = 0;
        MI_Uint32 d = 2;
        for (MI_Uint32 i=0; i <state->qualifierDecls.size; i ++)
        {
            MI_QualifierDecl * decl = state->qualifierDecls.data[i];
            if(decl->value != NULL)
            {
                if (decl->type == MI_BOOLEAN)
                {
                    MI_Boolean x = *(MI_Boolean*)decl->value;
                    vindex = (x) ? 0 : 1;
                }
                else if (decl->type == MI_UINT32)
                {
                    vindex = d++;
                }
                else if (decl->type == MI_STRING)
                {
                    vindex = d++;
                }
                wprintf(L"    {MI_T(\"%s\"), 0x%08X, 0x%08X, 0x%08X, 0x%08X, (void*)&%S%d},\n",
                        decl->name, decl->type, decl->scope, decl->flavor, decl->subscript, gQualval, vindex);
            }
            else
            {
                wprintf(L"    {MI_T(\"%s\"), 0x%08X, 0x%08X, 0x%08X, 0x%08X, NULL},\n",
                        decl->name, decl->type, decl->scope, decl->flavor, decl->subscript);
            }
        }
    }
    if (buf) free(buf);
}

typedef struct _MofCodecerEx
{
    MofCodecer * codecer;
    _Field_z_ char * root;
}MofCodecerEx;

/* Global flag indicate use cache schema or use flie */

#if 0
int g_usecache = 0;
class strless: public std::binary_function<string, string, bool>
{
    public:
        bool operator()(const string& s1, const string& s2) const
        {
            return _stricmp(s1.c_str(), s2.c_str()) < 0;
        }
};
map<string, char*, strless> g_cache;
map<string, size_t, strless> g_cache2;
#endif

/* Define a callback function that provides included file buffer */
MI_Result MI_CALL GetIncludedFileBufferCallback(
    _In_opt_ void *context,
    _In_z_ const MI_Char *fileName,
    _Outptr_result_buffer_(*bufferLength) MI_Uint8 **fileBuffer,
    _Out_ MI_Uint32 *bufferLength)
{
    MofCodecerEx* codecerex = (MofCodecerEx*)context;
    MofCodecer * codecer = codecerex->codecer;
    if (codecer == NULL)
    {
        printf("%s", "invalid codecer");
        return MI_RESULT_FAILED;
    }
    if (codecer->stackpos >= INCLUDE_STACK_SIZE)
    {
        printf("codecer included buffer overflowed");
        return MI_RESULT_FAILED;
    }

    codecer->includeFileCalledTimes ++;

    /* Try to load required file */
    {
        string filename = "";
        if (codecerex->root)
        {
            filename += codecerex->root;
            filename += '\\';
        }
        const MI_Char *pc = fileName;
        while (*pc)
        {
            filename += (char)(*pc);
            pc++;
        }
        printf("__open included file(%s)\n", filename.c_str());
        char * mofbuffer;
        size_t length;
#if 0
        if (g_usecache)
        {
            if (g_cache.find(filename) == g_cache.end())
            {
                return MI_RESULT_NOT_FOUND;
            }
            mofbuffer = g_cache[filename];
            length = g_cache2[filename];
        }
        else
#endif
        {
            int r0 = getFileContent((char *)filename.c_str(), &mofbuffer, &length);
            if (r0 != 0)
            {
                printf("can't open file (%s), errorno (%d)\n", filename.c_str(), errno);
                return MI_RESULT_FAILED;
            }
        }
        *fileBuffer = (MI_Uint8*)mofbuffer;
        *bufferLength = (MI_Uint32)length;
        codecer->includebufferstack[codecer->stackpos] = *fileBuffer;
        codecer->stackpos++;
        return MI_RESULT_OK;
    }
}

/* Define a callback function that free the included file buffer */
void MI_CALL FreeIncludedFileBufferCallback(
    _In_opt_ void *context,
    _In_ MI_Uint8 *Buffer)
{
    MI_UNREFERENCED_PARAMETER(Buffer);
    MofCodecerEx* codecerex = (MofCodecerEx*)context;
    MofCodecer * codecer = codecerex->codecer;
    if (codecer == NULL)
    {
        printf("%s", "invalid codecer");
        return;
    }
    if (codecer->stackpos == 0)
    {
        printf("codecer included buffer underflowed");
        return;
    }
    codecer->stackpos--;
    codecer->freeincludeFileCalledTimes ++;
    free(Buffer);
}

void SetCallback(_Inout_ MofCodecerEx *codecerex)
{
    if (codecerex)
    {
        codecerex->codecer->callbacks.freeIncludedFileContent = FreeIncludedFileBufferCallback;
        codecerex->codecer->callbacks.getIncludedFileContent = GetIncludedFileBufferCallback;
        codecerex->codecer->callbacks.includedFileContext = codecerex;
    }
}

void DecodeClassMof(_In_z_ char* file, _In_opt_z_ char* root, bool single)
{
    char * mofbuffer;
    size_t length;
    int r0 = getFileContent((char *)file, &mofbuffer, &length);
    if (r0 != 0)
    {
        printf("can't open file (%s), errorno (%d).", file, errno);
        return;
    }

    MI_Result r;
    MofCodecerEx codecerex = {0};
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    if (r != MI_RESULT_OK)
    {
        printf("failed to create parser (%d).", r);
        return;
    }
    codecerex.codecer = &codecer;
    codecerex.root = root;
    SetCallback(&codecerex);
    codecer.servername = MI_T("TestServer");
    codecer.namespacename = MI_T("root/testnames/pace");
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_STRICT);

    if (!single)
    {
        MI_ClassA *ca = NULL;
        MI_Instance *err = NULL;
        r = MI_Deserializer_DeserializeClassArray(&codecer.de,
            0,
            &codecer.options,
            &codecer.callbacks,
            (MI_Uint8*)mofbuffer,
            (MI_Uint32)length,
            NULL,
            codecer.servername,
            codecer.namespacename,
            NULL,
            &ca,
            &err);
        if (r != MI_RESULT_OK)
        {
            printf("Deserialize class mof failed with error (%d).", r);
            if (err)
            {
                MI_Value v;
                MI_Instance_GetElement(err, MI_T("Message"), &v, NULL, NULL, NULL);
                wprintf(L"Detail Message:\n (%s)\n", v.string);
                MI_Instance_Delete(err);
            }
        }
        if (ca)
        {
            printf("Totally (%d) classes\n", ca->size);
            for (MI_Uint32 i = 0; i < ca->size; i++)
            {
                wprintf(L"\tNO %d Class Name: %s\n", (i+1), ca->data[i]->classDecl->name);
            }
            MI_Deserializer_ReleaseClassArray(ca);
        }
    }
    else
    {
        MI_Class *cls = NULL;
        MI_Instance *err = NULL;
        r = MI_Deserializer_DeserializeClass(&codecer.de,
            0,
            (MI_Uint8*)mofbuffer,
            (MI_Uint32)length,
            NULL,
            codecer.servername,
            codecer.namespacename,
            NULL,
            NULL,
            NULL,
            &cls,
            &err);
        if (r != MI_RESULT_OK)
        {
            printf("Deserialize class mof failed with error (%d).", r);
            if (err)
            {
                MI_Value v;
                MI_Instance_GetElement(err, MI_T("Message"), &v, NULL, NULL, NULL);
                wprintf(L"Detail Message:\n (%s)\n", v.string);
                MI_Instance_Delete(err);
            }
        }
        if (cls)
        {
            wprintf(L"\tClass Name: %s\n", cls->classDecl->name);
            MI_Class_Delete(cls);
        }
    }
    free(mofbuffer);
    DeleteMofCodecer(&codecer);
}

void DecodeInstanceMof(_In_z_ char* file, _In_opt_z_ char* root, bool single)
{
    char * mofbuffer;
    size_t length;
    int r0 = getFileContent((char *)file, &mofbuffer, &length);
    if (r0 != 0)
    {
        printf("can't open file (%s), errorno (%d).", file, errno);
        return;
    }

    MI_Result r;
    MofCodecerEx codecerex = {0};
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    if (r != MI_RESULT_OK)
    {
        printf("failed to create parser (%d).", r);
        return;
    }
    codecerex.codecer = &codecer;
    codecerex.root = root;
    SetCallback(&codecerex);
    codecer.servername = MI_T("TestServer");
    codecer.namespacename = MI_T("root/testnames/pace");
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_STRICT);

    if (!single)
    {
        MI_InstanceA *ia = NULL;
        MI_Instance *err = NULL;
        r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
            0,
            &codecer.options,
            &codecer.callbacks,
            (MI_Uint8*)mofbuffer,
            (MI_Uint32)length,
            NULL,
            NULL,
            &ia,
            &err);
        if (r != MI_RESULT_OK)
        {
            printf("Deserialize instance mof failed with error (%d).", r);
            if (err)
            {
                MI_Value v;
                MI_Instance_GetElement(err, MI_T("Message"), &v, NULL, NULL, NULL);
                wprintf(L"Detail Message:\n (%s)\n", v.string);
                MI_Instance_Delete(err);
            }
        }
        if (ia)
        {
            printf("Totally (%d) instances\n", ia->size);
            for (MI_Uint32 i = 0; i < ia->size; i++)
            {
                wprintf(L"\tNO %d instance's class Name: %s\n", (i+1), ia->data[i]->classDecl->name);
            }
            MI_Deserializer_ReleaseInstanceArray(ia);
        }
    }
    else
    {
        MI_Instance *inst = NULL;
        MI_Instance *err = NULL;
        r = MI_Deserializer_DeserializeInstance(&codecer.de,
            0,
            (MI_Uint8*)mofbuffer,
            (MI_Uint32)length,
            NULL,
            0,
            NULL,
            NULL,
            NULL,
            &inst,
            &err);
        if (r != MI_RESULT_OK)
        {
            printf("Deserialize instance mof failed with error (%d).", r);
            if (err)
            {
                MI_Value v;
                MI_Instance_GetElement(err, MI_T("Message"), &v, NULL, NULL, NULL);
                wprintf(L"Detail Message:\n (%s)\n", v.string);
                MI_Instance_Delete(err);
            }
        }
        if (inst)
        {
            wprintf(L"\tInstance Name: %s\n", inst->classDecl->name);
            MI_Instance_Delete(inst);
        }
    }
    free(mofbuffer);
    DeleteMofCodecer(&codecer);
}

typedef enum _MOFFILETYPE
{
    CLASSONLY,
    INSTANCE_ONECLASS,
    CLASS_INSTANCE
}MOFFILETYPE;

void CreateMOF(_In_ size_t n, _In_z_ char *fileName, _In_ MOFFILETYPE type)
{
    FILE* fp = fopen(fileName, "w"); /* binary mode */
    if (fp == NULL)
    {
        printf("Cannot create file %s\n", fileName);
        return;
    }
    char buf[128];
    switch (type)
    {
    case CLASSONLY:
    case CLASS_INSTANCE:
        for(size_t i = 0; i < n; i++)
        {
            sprintf_s(buf, sizeof(buf), "class c%d{string p1;};\n", (int)i);
            fputs(buf, fp);
        }
        break;
    case INSTANCE_ONECLASS:
        sprintf_s(buf, sizeof(buf), "class c%d{string p1;};\n", 0);
        fputs(buf, fp);
        break;
    }
    switch (type)
    {
        case CLASS_INSTANCE:
            for(size_t i = 0; i < n; i++)
            {
                sprintf_s(buf, sizeof(buf), "instance of c%d as $alias%d{p1=\"%d\";};\n", (int)i, (int)i, (int)i);
                fputs(buf, fp);
            }
            break;
        case INSTANCE_ONECLASS:
            for(size_t i = 0; i < n; i++)
            {
                sprintf_s(buf, sizeof(buf), "instance of c0 as $alias%d{p1=\"%d\";};\n", (int)i, (int)i);
                fputs(buf, fp);
            }
            break;
    }
    fclose(fp);
}

/*=============================================================================
**
** Usage print
**
=============================================================================*/
void printUsage()
{
    printf("Usage: moftool [token] [sctable] [file2str filename [-a -u]]\n\t[file2lex filename] [printqual filename]\n\t[parse filename [-c -i] -incroot dir [-pause]]\n\t[createmof filename]");
    printf("    [token] - print token table with hash code\n");
    printf("    [sctable] - print single char table. The chars are treated as separate token for mof LALR(1) grammar\n");
    printf("    [file2str] - read text from file and print out in const string format. -a output ANSI string, -u outputs UNICODE string\n");
    printf("    [file2lex] - parse mof file and print out tokens.\n");
    printf("    [printqual filename] - parse mof file and print out qualifiers declarasions.\n");
    printf("    [parse filename [-c -i] -incroot dir [-pause]] - parse mof file and print out result. [-incrootpath] is a root path for search and load file(s), default is current folder.\n");
    printf("    [sparse filename [-c -i] - parse mof file with one class / instance and print result.\n");
    printf("    [createmof filename [-instance] [-count <number>]] - create a large class or instance mof file, contains 10K classes and 10K instances\n");
}

/*=============================================================================
**
** Entry of the application
**
=============================================================================*/
int MI_MAIN_CALL main(int argc, __in_ecount(argc) LPSTR* argv)
{
    int r = 0;
    if (argc <= 1)
    {
        r = 1;
        goto PrintUsage;
    }
    if (_stricmp(argv[1], "token") == 0) printTokens();
    else if (_stricmp(argv[1], "sctable") == 0) printSingleCharTable();
    else if (_stricmp(argv[1], "file2str") == 0)
    {
        const char * opt = "-a";
        if (argc < 3) {
            r = 1;
            goto PrintUsage;
        }
        if (argc == 4) opt = argv[3];
        file2str(argv[2], opt);
    }
    else if (_stricmp(argv[1], "file2lex") == 0)
    {
        if (argc < 3) {
            r = 1;
            goto PrintUsage;
        }
        LexParse(argv[2]);
    }
    else if (_stricmp(argv[1], "printqual") == 0)
    {
        if (argc < 3) {
            r = 1;
            goto PrintUsage;
        }
        printQualifier(argv[2]);
    }
    else if (_stricmp(argv[1], "createmof") == 0)
    {
        MOFFILETYPE type = CLASSONLY;
        int count = CLASSCOUNT;
        if (argc < 3) {
            r = 1;
            goto PrintUsage;
        }
        else if (argc > 3)
        {
            if (_stricmp(argv[3], "-instance") == 0)
            {
                if (argc>5 && _stricmp(argv[4], "-count") == 0)
                {
                    count = strtol(argv[5], NULL, 10);
                }
                type = CLASS_INSTANCE;
            }
            if (_stricmp(argv[3], "-insto") == 0)
            {
                if (argc>5 && _stricmp(argv[4], "-count") == 0)
                {
                    count = strtol(argv[5], NULL, 10);
                }
                type = INSTANCE_ONECLASS;
            }
            else if(argc > 4)
            {
                if (_stricmp(argv[3], "-count") == 0)
                {
                    count = strtol(argv[4], NULL, 10);
                }
            }
        }
        CreateMOF(count, argv[2], type);
    }
    else if (_stricmp(argv[1], "sparse") == 0)
    {
        if (argc < 4) {
            r = 1;
            goto PrintUsage;
        }
        char * file = argv[2];
        char * opt = argv[3];
        if (_stricmp(opt, "-c") == 0)
        {           
            DecodeClassMof(file, NULL, true);
        }
        else if (_stricmp(opt, "-i") == 0)
        {
            DecodeInstanceMof(file, NULL, true);
        }
        else
        {
            r = 1;
            goto PrintUsage;
        }
    }
    else if (_stricmp(argv[1], "parse") == 0)
    {
        ULONGLONG x, y;
        if (argc < 4) {
            r = 1;
            goto PrintUsage;
        }
        char * file = argv[2];
        char * opt = argv[3];
        char * root = NULL;
        bool pause = false;
        if (argc > 5)
        {
            if (_stricmp(argv[4], "-incroot") == 0)
            {
               root = argv[5];
            }
        }
        if (argc > 6)
        {
            if (_stricmp(argv[6], "-pause") == 0)
            {
                pause = true;
            }
        }
        if (pause)
        {
            char c;
            printf("Press any key to continue...");
            if (scanf_s("%c", &c, 1)==0)
            {
                return 0;
            }
        }
        x = GetTickCount64();
        if (_stricmp(opt, "-c") == 0)
        {
#if 0
            g_cache.clear();
            g_usecache = 0;
#endif
            
            DecodeClassMof(file, root, false);
#if 0
            g_usecache = 1;
            DecodeClassMof(file, root);
#endif
        }
        else if (_stricmp(opt, "-i") == 0)
        {
            DecodeInstanceMof(file, root, false);
        }
        else
        {
            r = 1;
            goto PrintUsage;
        }
        y = GetTickCount64();
        fprintf(stderr, "tickcount (1) %d\n", (int)(y-x));
    }
    else
    {
        r = 1;
        goto PrintUsage;
    }
    if (r == 0)
    {
        goto Return;
    }
PrintUsage:
    printUsage();
Return:
    return r;
}
