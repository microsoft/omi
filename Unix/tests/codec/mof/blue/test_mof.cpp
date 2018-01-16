/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <string>
#include <stdio.h>
#include <MI.h>
#include <common.h>
#include <codec/mof/parser/state.h>
#include <codec/mof/parser/mofyacc.h>
#include <codec/mof/parser/mofparser.h>
#include <codec/mof/parser/stringids.h>
#include <codec/common/micodec.h>
#include <nits/base/nits.h>
#include <pal/format.h>

#include "consts.h"
#include <tests/codec/mof/util/util.h>

#define TEST_ASSERT(x) NitsAssert(x, L"")

using namespace std;

void MI_Instance_DeleteHelper(MI_Instance* inst)
{
    if (inst)
        MI_Instance_Delete(inst);
}

NitsTest(TestClassArrayDeserializer)
    char classmof[] = "class A {string P1; uint8 P2;};"
        "class B {Sint64 P1; uint8 P2;};";
    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r!=MI_RESULT_OK) goto CleanUp;

    MI_ClassA *ca;
    r = MI_Deserializer_DeserializeClassArray(&codecer.de, 0, &codecer.options, 0, (MI_Uint8*)classmof, sizeof(classmof), NULL, NULL, NULL, NULL, &ca, NULL);
    if (r!=MI_RESULT_OK) goto CleanUp;

    _Analysis_assume_(ca != NULL);

    NitsAssert( r==MI_RESULT_OK, L"deserialize class mof failed");
    NitsAssert( ca->size == 2, L"deserialize class mof failed");

    int c = Tcscasecmp(ca->data[0]->classDecl->name, MI_T("A"));
    NitsAssert(c == 0, L"Class name error");

    c = Tcscasecmp(ca->data[1]->classDecl->name, MI_T("B"));
    NitsAssert(c == 0, L"Class name error");
    MI_Deserializer_ReleaseClassArray(ca);

CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

NitsTest(TestClassArrayDeserializer_HEXString)
    wchar_t classmof[] = L"[Description(\"\\xDCFFsdf\")] class A {string P1; uint8 P2;};";
    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r!=MI_RESULT_OK) goto CleanUp;

    MI_ClassA *ca;
    r = MI_Deserializer_DeserializeClassArray(&codecer.de, 0, &codecer.options, 0, (MI_Uint8*)classmof, sizeof(classmof), NULL, NULL, NULL, NULL, &ca, NULL);
    NitsAssert( r==MI_RESULT_OK, L"deserialize class mof failed");
    if (r!=MI_RESULT_OK) goto CleanUp;

    _Analysis_assume_(ca != NULL);

    NitsAssert( ca->size == 1, L"deserialize class mof failed");

    int c = Tcscasecmp(ca->data[0]->classDecl->name, MI_T("A"));
    NitsAssert(c == 0, L"Class name error");

    NitsAssert(ca->data[0]->classDecl->numQualifiers == 1, L"Class should have 1 qualifer");
    MI_Value *qv = (MI_Value *)ca->data[0]->classDecl->qualifiers[0]->value;
    MI_Char qvc[5] = {(MI_Char)0xDCFF, (MI_Char)'s', (MI_Char)'d', (MI_Char)'f', 0};
    c = Tcscasecmp(qv->string, (ZChar*)qvc);
    NitsAssert(c == 0, L"Description value is not as expected");

    MI_Deserializer_ReleaseClassArray(ca);

CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

NitsTest(TestClassArrayDeserializer_SyntaxError)
    char classmof[] = "class A {string P1; uint8 P2};";
    MofCodecer codecer = {0};
    MI_Result r = CreateMofCodecer(&codecer);
    NitsAssert( r == MI_RESULT_OK, L"Create mof deserializer failed");
    if (r!=MI_RESULT_OK) goto CleanUp;
    MI_ClassA *ca;
    r = MI_Deserializer_DeserializeClassArray(&codecer.de, 0, 0, 0, (MI_Uint8*)classmof, sizeof(classmof), NULL, NULL, NULL, NULL, &ca, NULL);
    NitsAssert( r == MI_RESULT_FAILED, L"deserialize class mof should failed with MI_RESULT_FAILED");
    NitsAssert( ca==NULL, L"deserialize class mof should get NULL MI_ClassA");

CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest


/*=============================================================================
**
** Test mint schema & instance
** NOTE: The unit test has to be running under parent folder of WINOMI
**
=============================================================================*/
const char* OptionDirs[] =
{
    "WinOMI\\tests\\codec\\mof\\",
    "tests\\codec\\mof\\",
    "..\\tests\\codec\\mof\\",
    ".\\",
    "",
    NULL
};

extern "C" HMODULE g_hModule;

_Success_(return == 0)
int _GetFileContentHelper(
    _In_z_ char *fileName,
    _Outptr_result_bytebuffer_(*length) char** content,
    _Out_ size_t *length)
{
    string filepath;
    int i = 0;
    while (OptionDirs[i] != NULL)
    {
        filepath = OptionDirs[i];
        filepath += fileName;
        int r0 = getFileContent((char*)filepath.c_str(), content, length);
        if (r0 == 0)
        {
            return 0;
        }
        i++;
    }
    char path[MAX_PATH];
    DWORD pathlen;
    if ((pathlen = GetModuleFileNameA(g_hModule, path, MI_COUNT(path)))> 0)
    {
        //
        // test_mimofcodec.dll sits under dir like winomi\tests\bin\,
        // remove last 2 slashes from the DLL path and get winomi\test,
        // mof file sits under directory like winomi\tests\codec\mof\
        //
        pathlen--;
        while(pathlen && path[pathlen] != '\\')
            pathlen--;
        while(pathlen && path[pathlen] == '\\')
            pathlen--;
        while(pathlen && path[pathlen] != '\\')
            pathlen--;
        while(pathlen && path[pathlen] == '\\')
            pathlen--;
        if (pathlen)
        {
            path[pathlen + 1] = 0;
            filepath = path;
            filepath += "\\codec\\mof\\";
            filepath += fileName;
            return getFileContent((char*)filepath.c_str(), content, length);
        }
    }
    return -1;
}

MI_Result DeserializerSchema_Instance(
    _In_z_ char * schemafile,
    _In_z_ char * instancefile,
    _In_ MofCodecer * codecer,
    _Outptr_result_maybenull_ MI_ClassA **classa,
    _Outptr_result_maybenull_ MI_InstanceA **instancea)
{
    MI_ClassA *ca = NULL;
    MI_InstanceA *ia = NULL;
    MI_Result r = MI_RESULT_OK;
    char *classmof = NULL;
    char *instmof = NULL;
    size_t lengthClass = 0;
    size_t lengthInst = 0;
    *classa = NULL;
    *instancea = NULL;

    {
        char * file = schemafile;
        int r0 = _GetFileContentHelper(file, &classmof, &lengthClass);
        NitsAssert( r0 == 0, L"Read schema file failed");
        if (r0 != 0) return MI_RESULT_FAILED;

        r = MI_Application_NewDeserializer_Mof(&codecer->app, 0, MOFCODEC_FORMAT, &codecer->de);
        NitsAssert( r == MI_RESULT_OK, L"Create mof deserializer failed");
        if (r != MI_RESULT_OK)
            goto FAILED;
        MI_Uint32 readBytes;
        r = MI_Deserializer_DeserializeClassArray(&codecer->de, 0, &codecer->options, 0, (MI_Uint8*)classmof, (MI_Uint32)lengthClass, NULL, NULL, NULL, &readBytes, &ca, NULL);
        NitsAssert( r == MI_RESULT_OK, L"deserialize schema failed");
        if (r != MI_RESULT_OK)
            goto FAILED;
        NitsAssert( readBytes == lengthClass, L"deserialize schema failed");
    }
    {
        char * file = instancefile;
        int r0 = _GetFileContentHelper(file, &instmof, &lengthInst);
        NitsAssert( r0 == 0, L"Read instance file failed");
        if (r0 != 0) return MI_RESULT_FAILED;

        r = MI_Application_NewDeserializer_Mof(&codecer->app, 0, MOFCODEC_FORMAT, &codecer->de);
        NitsAssert( r == MI_RESULT_OK, L"Create mof deserializer failed");
        if (r != MI_RESULT_OK)
            goto FAILED;

        MI_Uint32 readBytes;
        r = MI_Deserializer_DeserializeInstanceArray(&codecer->de, 0, &codecer->options, 0, (MI_Uint8*)instmof, (MI_Uint32)lengthInst, ca, &readBytes, &ia, NULL);
        NitsAssert( r == MI_RESULT_OK, L"deserialize instance failed");
        if (r != MI_RESULT_OK)
            goto FAILED;

        NitsAssert( readBytes == lengthInst, L"deserialize instance failed");
    }
    *classa = ca;
    *instancea = ia;

FAILED:
    if (instmof)
        freeFileContent(instmof, lengthInst);
    if (classmof)
        freeFileContent(classmof, lengthClass);
    if (r != MI_RESULT_OK)
    {
        if (ca)
            MI_Deserializer_ReleaseClassArray(ca);
        if (ia)
            MI_Deserializer_ReleaseInstanceArray(ia);
    }
    return r;
}

/*=============================================================================
**
** Test Mint Expression sample mof
**
=============================================================================*/
NitsTest(TestMintSchema_Instance)
    MofCodecer codecer = {0};
    MI_ClassA *ca = NULL;
    MI_InstanceA *ia = NULL;

    MI_Result r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r!=MI_RESULT_OK) goto CleanUp;

    r = DeserializerSchema_Instance(
        "mintschema.mof",
        "mintinstance.mof",
        &codecer,
        &ca,
        &ia);
    NitsAssert(r== MI_RESULT_OK, L"Deserializer mint schema/instance failed");
    if (r == MI_RESULT_OK)
    {
        /* verify schema */
        _Analysis_assume_(ca != NULL);
        NitsAssert( ca->size == cMintSchemaCount, L"mint schema mof should contains 40 classes");
        for (MI_Uint32 i = 0; i < cMintSchemaCount; i++)
        {
            int c = Tcscasecmp(ca->data[i]->classDecl->name, cMintSchema[i].name);
            NitsAssert(c == 0, L"class name is wrong");
            NitsAssert(ca->data[i]->classDecl->numProperties == cMintSchema[i].numProperties, L"class property count is wrong");
        }

        /* verify instance */
        _Analysis_assume_(ia != NULL);

        NitsAssert( ia->size == 1, L"mint instance mof should contains 1 instance");
        int c = Tcscasecmp(ia->data[0]->classDecl->name, MI_T("MSFT_ExpressionLambda"));
        NitsAssert(c == 0, L"Class name should be MSFT_ExpressionLambda");

        MI_Instance *inst = ia->data[0];
        NitsAssert(inst != NULL, L"Instance should not be NULL");
        MI_Value value;
        MI_Type type;
        r = MI_Instance_GetElement(inst, MI_T("parameters"), &value, &type, NULL, NULL);
        NitsAssert( r == MI_RESULT_OK, L"Read 'parameters' from instance failed");
        NitsAssert( value.instancea.size == 1, L"'parameters' property should have 1 instance");
        NitsAssert( type == MI_INSTANCEA, L"'parameters' property type should be MI_INSTANCEA");

        r = MI_Instance_GetElement(inst, MI_T("body"), &value, &type, NULL, NULL);
        NitsAssert( r == MI_RESULT_OK, L"Read 'body' from instance failed");
        NitsAssert( value.instance != NULL, L"'body' property should not be null");
    }
    if (ia) MI_Deserializer_ReleaseInstanceArray(ia);
    if (ca) MI_Deserializer_ReleaseClassArray(ca);

CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

/*=============================================================================
**
** Test Desired-State-Configuration sample mof
**
=============================================================================*/
NitsTest(TestDscSchema_Instance)
    MofCodecer codecer = {0};
    MI_ClassA *ca = NULL;
    MI_InstanceA *ia = NULL;

    MI_Result r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r!=MI_RESULT_OK) goto CleanUp;

    r = DeserializerSchema_Instance(
        "dscschema.mof",
        "dscinstance.mof",
        &codecer,
        &ca,
        &ia);
    NitsAssert(r== MI_RESULT_OK, L"Deserializer mint schema/instance failed");
    if (r == MI_RESULT_OK)
    {
        /* verify schema */
        NitsAssert( ca->size == cDscSchemaCount, L"DSC schema mof should contains 40 classes");
        for (MI_Uint32 i = 0; i < cDscSchemaCount; i++)
        {
            int c = Tcscasecmp(ca->data[i]->classDecl->name, cDscSchema[i].name);
            NitsAssert(c == 0, L"class name is wrong");
            NitsAssert(ca->data[i]->classDecl->numProperties == cDscSchema[i].numProperties, L"class property count is wrong");
        }

        /* verify instance */
        NitsAssert( ia->size == 2, L"DSC instance mof should contains 2 instance");

        int c = Tcscasecmp(ia->data[0]->classDecl->name, MI_T("MSFT_FileDirectoryConfiguration"));
        NitsAssert(c == 0, L"Class name should be MSFT_FileDirectoryConfiguration");

        MI_Instance *inst = ia->data[0];
        NitsAssert(inst != NULL, L"Instance should not be NULL");

        MI_Value value;
        MI_Type type;
        r = MI_Instance_GetElement(inst, MI_T("credential"), &value, &type, NULL, NULL);
        NitsAssert( r == MI_RESULT_OK, L"Read 'credential' from instance failed");
        NitsAssert( type == MI_INSTANCE, L"'credential' property type be MI_INSTANCE");

        MI_Instance * p = value.instance;
        NitsAssert(p != NULL, L"Credential instance should not be NULL");       
        r = MI_Instance_GetElement(p, MI_T("Password"), &value, &type, NULL, NULL);
        NitsAssert( r == MI_RESULT_OK, L"Read 'Password' from instance failed");
        NitsAssert( type == MI_STRING, L"'Password' property type be MI_INSTANCE");
        c = Tcscmp(value.string, MI_T("BBB"));
        NitsAssert(c == 0, L"Password should be 'BBB'");

        c = Tcscasecmp(ia->data[1]->classDecl->name, MI_T("MSFT_ConfigurationDocument"));
        NitsAssert(c == 0, L"Class name should be MSFT_ConfigurationDocument");
        inst = ia->data[1];
        NitsAssert(inst != NULL, L"Instance should not be NULL");
        r = MI_Instance_GetElement(inst, MI_T("version"), &value, &type, NULL, NULL);
        NitsAssert( r == MI_RESULT_OK, L"Read 'version' from instance failed");
        NitsAssert( type == MI_STRING, L"'version' property type be MI_STRING");
        c = Tcscasecmp(value.string, MI_T("1.0.0"));
        NitsAssert(c == 0, L"'version' property value should be '1.0.0'");
    }
    if (ia) MI_Deserializer_ReleaseInstanceArray(ia);
    if (ca) MI_Deserializer_ReleaseClassArray(ca);

CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

void ValidateErrorInstance(
    _In_ MI_Instance* err,
    _In_z_ const MI_Char* errtype,
    MI_Uint32 errcode,
    MI_Uint16 errcategory)
{
    if (!err)
    {
        NitsAssert( 0, L"Error object is NULL!");
        return;
    }

    MI_Result r;
    MI_Value msg, type, code, cat;
    MI_Type t;
    int c = Tcscasecmp(err->classDecl->name, MI_T("OMI_Error"));
    NitsAssert( c==0, L"Error object classname should be OMI_Error");

    r = MI_Instance_GetElement(err, MI_T("Message"), &msg, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read message property from ERROR object failed");
    NitsAssert( t==MI_STRING, L"Message property should be MI_STRING type");

    r = MI_Instance_GetElement(err, MI_T("error_Type"), &type, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read error_Type property from ERROR object failed");
    NitsAssert( t==MI_STRING, L"error_Type property should be MI_STRING type");
    c = Tcscasecmp(type.string, errtype);
    NitsAssert( c==0, L"error_Type mismatched");

    r = MI_Instance_GetElement(err, MI_T("error_Code"), &code, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read error_Code property from ERROR object failed");
    NitsAssert( t==MI_UINT32, L"error_Code property should be MI_UINT32 type");
    NitsCompare(code.uint32, errcode, L"error_Code value mismatch");

    r = MI_Instance_GetElement(err, MI_T("error_Category"), &cat, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read error_Category property from ERROR object failed");
    NitsAssert( t==MI_UINT16, L"error_Category property should be MI_UINT16 type");
    NitsAssert( cat.uint16 == errcategory, L"error_Category value mismatch");

    Tprintf(MI_T("Error message: %d...%T\n"), code.uint32, msg.string);
}

/*=============================================================================
**
** Test failure cases
**
=============================================================================*/
NitsTest(TestInstance_Error_Syntax)
    InvalidMofResult* testcase = InvalidMofs;
    MofCodecer codecer = {0};
    MI_Result r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r!=MI_RESULT_OK) goto CleanUp;

    MI_InstanceA *ia = NULL;
    MI_Instance *err = NULL;
    while (testcase->mofdata != NULL)
    {
        r = MI_Deserializer_DeserializeInstanceArray(&codecer.de, 0, 0, 0, (MI_Uint8*)(testcase->mofdata), testcase->mofdatalen, NULL, NULL, &ia, &err);
        NitsAssert( r==testcase->r, L"deserialize instance mof should failed as expected");
        NitsAssert( err!=NULL, L"deserialize instance mof should failed with MI_RESULT_FAILED");
        ValidateErrorInstance(err, testcase->errtype, testcase->errcode, testcase->errorcategory);
        MI_Instance_DeleteHelper(err);
        testcase++;
    }

CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest


/*=============================================================================
**
** Test data and callback definitions
**
=============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

CRITICAL_SECTION g_cs;

#ifdef __cplusplus
}
#endif

MI_ClassA *g_classes = NULL;
MI_ClassA *g_classesEx = NULL;
MofCodecer g_codecer = {0};

#define CLASS_A_MOF "CLASS A{[key]string ka; uint32 value;};"
#define CLASS_B_MOF "CLASS B{[key]string kb; uint32 value;};"
#define CLASS_C_MOF "CLASS C{[key]uint32 kc; string value;};"
#define CLASS_M_MOF "#pragma include (\"c.mof\")"\
    "CLASS M:C{string MP3;};"
#define CLASS_INCLUDE_MOF "#pragma include (\"core/b.mof\")"

#define CLASS_EXA_MOF "CLASS EXA{[key]uint32 kexa; uint32 value;};"
#define CLASS_EXB_MOF "CLASS EXB{[key]uint32 kexb; string value;};"

typedef struct _CLASSMOF
{
    _Field_z_ const MI_Char* file;
    _Field_z_ const char* mof;
    MI_Uint32 len;
}CLASSMOF;

CLASSMOF g_classmof[]={
    {MI_T("etc/a.mof"), CLASS_A_MOF, sizeof(CLASS_A_MOF) - 1},
    {MI_T("core/b.mof"), CLASS_B_MOF, sizeof(CLASS_B_MOF) - 1},
    {MI_T("c.mof"), CLASS_C_MOF, sizeof(CLASS_C_MOF) - 1},
    {MI_T("test/m.mof"), CLASS_M_MOF, sizeof(CLASS_M_MOF) - 1},
    {MI_T("test/include.mof"), CLASS_INCLUDE_MOF, sizeof(CLASS_INCLUDE_MOF) - 1},
    {NULL, NULL, 0},
};

CLASSMOF g_classmofEx[]={
    {MI_T("exa.mof"), CLASS_EXA_MOF, sizeof(CLASS_EXA_MOF) - 1},
    {MI_T("exb.mof"), CLASS_EXB_MOF, sizeof(CLASS_EXB_MOF) - 1},
    {NULL, NULL, 0},
};

#define CLASS_Invalid "Test invalid class"
#define CLASS_Include_Invalid "#pragma include (\"invalid.mof\")"

CLASSMOF g_classmofInvalid[]={
    {MI_T("invalid.mof"), CLASS_Invalid, sizeof(CLASS_Invalid) - 1},
    {MI_T("incinvalid.mof"), CLASS_Include_Invalid, sizeof(CLASS_Include_Invalid) - 1},
    {NULL, NULL, 0},
};

/*Finalize global test data*/
void FinalizeTestData()
{
    if (g_classes) MI_Deserializer_ReleaseClassArray(g_classes);
    if (g_classesEx) MI_Deserializer_ReleaseClassArray(g_classesEx);
}

MI_Result _InitializeClassesFromMof(
    _In_ CLASSMOF *gcm,
    _Outptr_result_maybenull_ MI_ClassA ** ga)
{
    MI_Result r = MI_RESULT_OK;
    MI_Uint32 tlen = 0;
    CLASSMOF *cm = gcm;
    MI_Uint8 *buf = NULL;
    r = CreateMofCodecer(&g_codecer);
    if (r!=MI_RESULT_OK) goto Return;

    while(cm->file)
    {
        tlen += cm->len;
        cm++;
    }
    buf = (MI_Uint8 *)malloc((size_t)tlen);
    if (buf==NULL)
    {
        r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        goto Return;
    }
    cm = gcm;
    MI_Uint32 p = 0;
    while(cm->file)
    {
        memcpy(&buf[p], cm->mof, cm->len);
        p += cm->len;
        cm++;
    }
    /* parse the buffer to get schema */
    r = MI_Deserializer_DeserializeClassArray(
        &g_codecer.de,
        0,
        &g_codecer.options,
        0,
        buf,
        tlen,
        NULL,
        NULL,
        NULL,
        NULL,
        ga,
        NULL);
Return:
    if (buf) free(buf);
    DeleteMofCodecer(&g_codecer);
    return r;
}

/*Initliaze global test data*/
MI_Result InitializeTestData()
{
    MI_Result r = MI_RESULT_OK;
    EnterCriticalSection(&g_cs);
    if (g_classes == NULL)
    {
        /* build a buffer contains all class defined in g_classmof */
        r = _InitializeClassesFromMof(g_classmof, &g_classes);
        if (r != MI_RESULT_OK) goto Return;
    }
    if (g_classesEx == NULL)
    {
        /* build a buffer contains all class defined in g_classmofEx */
        r = _InitializeClassesFromMof(g_classmofEx, &g_classesEx);
        if (r != MI_RESULT_OK) goto Return;
    }
Return:
    LeaveCriticalSection(&g_cs);
    return r;
}


MI_Result _FindClass(_In_ MI_ClassA *classes,
    _In_z_ const MI_Char *className, 
    _Outptr_ MI_Class **requestedClassObject)
{
    MI_Uint32 i = 0;
    for (; i < classes->size; i++)
    {
        if (Tcscasecmp(className, classes->data[i]->classDecl->name) ==0)
        {
            MI_Class *copyClass;
            MI_Result r = MI_Class_Clone(classes->data[i], &copyClass);
            if (r!=MI_RESULT_OK) return r;
            *requestedClassObject = copyClass;
            return MI_RESULT_OK;
        }
    }
    return MI_RESULT_NOT_FOUND;
}

/* Define a callback function that provides required schema */
MI_Result MI_CALL ClassObjectNeededCallback(
    _In_opt_ void *context,
    _In_opt_z_ const MI_Char *serverName, 
    _In_opt_z_ const MI_Char *namespaceName, 
    _In_z_ const MI_Char *className, 
    _Outptr_ MI_Class **requestedClassObject)
{
    MofCodecer* codecer = (MofCodecer*)context;
    NitsAssert(codecer != NULL, L"coecer is NULL");
    NitsAssert(codecer->magicnumber == cmagicnumber, L"coecer is invalid");
    if (codecer->servername)
    {
        int c = Tcscmp(serverName, codecer->servername);
        NitsAssert(c == 0, L"server name is invalid");
    }
    if(codecer->namespacename)
    {
        int c = Tcscmp(namespaceName, codecer->namespacename);
        NitsAssert(c == 0, L"namespace name is invalid");
    }

    codecer->classNeedCalledTimes ++;
    if (codecer->retvalueClassNeed != MI_RESULT_OK)
        return codecer->retvalueClassNeed;

    MI_Result r = InitializeTestData();
    if (r != MI_RESULT_OK) return r;
    
    /* Try to find required class */
    r = _FindClass(g_classes, className, requestedClassObject);
    if (r != MI_RESULT_OK)
    {
        if (codecer->classNeedCallbackOptions == 1)
        {
            r = _FindClass(g_classesEx, className, requestedClassObject);
        }
    }
    return r;
}

#ifdef _PREFAST_
# pragma prefast (push)
# pragma prefast (disable: 26045)
# pragma prefast (disable: 26018)
#endif

MI_Result _getIncludedFileBufferCallback(
    _In_ MofCodecer* codecer,
    _In_z_ const MI_Char *fileName,
    _In_ CLASSMOF *cm,
    _Outptr_result_buffer_(*bufferLength) MI_Uint8 **fileBuffer,
    _Out_ MI_Uint32 *bufferLength)
{
    *fileBuffer = NULL;
    *bufferLength = 0;
    NitsAssert(codecer->stackpos<INCLUDE_STACK_SIZE, L"coecer buffer stack is overflowed");
    if(codecer->stackpos >= INCLUDE_STACK_SIZE) return MI_RESULT_FAILED;
    while(cm->file != NULL)
    {
        if (Tcscasecmp(fileName, cm->file) ==0)
        {
            *fileBuffer = (MI_Uint8*)cm->mof;
            *bufferLength = cm->len;
            codecer->includebufferstack[codecer->stackpos++] = *fileBuffer;
            return MI_RESULT_OK;
        }
        cm++;
    }
    return MI_RESULT_NOT_FOUND;
}

#ifdef _PREFAST_
# pragma prefast (pop)
#endif

/* Define a callback function that provides included file buffer */
MI_Result MI_CALL GetIncludedFileBufferCallback(
    _In_opt_ void *context,
    _In_z_ const MI_Char *fileName,
    _Outptr_result_buffer_(*bufferLength) MI_Uint8 **fileBuffer,
    _Out_ MI_Uint32 *bufferLength)
{
    MofCodecer* codecer = (MofCodecer*)context;
    NitsAssert(codecer != NULL, L"codecer is NULL");
    if (codecer == NULL)
        return MI_RESULT_INVALID_PARAMETER;
    NitsAssert(codecer->magicnumber == cmagicnumber, L"coecer is invalid");
    NitsAssert(codecer->stackpos < INCLUDE_STACK_SIZE, L"coecer included buffer overflowed");
    codecer->includeFileCalledTimes ++;
    *fileBuffer = NULL;
    *bufferLength = 0;
    if (codecer->retvalueIncludeFile != MI_RESULT_OK)
        return codecer->retvalueIncludeFile;
    /* Try to find required file */
    {
        CLASSMOF *cm = g_classmof;
        MI_Result r = _getIncludedFileBufferCallback(codecer, fileName, cm, fileBuffer, bufferLength);
        if (r == MI_RESULT_OK) return r;
        cm = g_classmofInvalid;
        return _getIncludedFileBufferCallback(codecer, fileName, cm, fileBuffer, bufferLength);;
    }
}

/* Define a callback function that free the included file buffer */
void MI_CALL FreeIncludedFileBufferCallback(
    _In_opt_ void *context,
    _In_ MI_Uint8 *Buffer)
{
    MofCodecer* codecer = (MofCodecer*)context;
    NitsAssert(codecer != NULL, L"coecer is NULL");
    NitsAssert(codecer->magicnumber == cmagicnumber, L"coecer is invalid");
    NitsAssert(codecer->stackpos > 0, L"coecer included buffer stack is invalid");
    codecer->stackpos--;
    codecer->freeincludeFileCalledTimes ++;
    _Analysis_assume_(codecer->stackpos < INCLUDE_STACK_SIZE);
    NitsAssert(Buffer == codecer->includebufferstack[codecer->stackpos], L"buffer to freed is invalid");
}

/*=============================================================================
**
** Set callback objects
**
=============================================================================*/

void SetCallback(_Inout_ MofCodecer *codecer)
{
    if (codecer)
    {
        codecer->callbacks.freeIncludedFileContent = FreeIncludedFileBufferCallback;
        codecer->callbacks.getIncludedFileContent = GetIncludedFileBufferCallback;
        codecer->callbacks.includedFileContext = codecer;
        codecer->callbacks.classObjectNeeded = ClassObjectNeededCallback;
        codecer->callbacks.classObjectNeededContext = codecer;
        codecer->retvalueClassNeed = MI_RESULT_OK;
        codecer->retvalueIncludeFile = MI_RESULT_OK;
        codecer->classNeedCalledTimes =0;
        codecer->classNeedCallbackOptions =0;
        codecer->includeFileCalledTimes =0;
        codecer->freeincludeFileCalledTimes =0;
    }
}

/*=============================================================================
**
** Test callbacks for class deserialization
**
=============================================================================*/
NitsTest(TestClass_Callbacks)
    char classmof[] = "class D:A {string P1; uint8 P2;};";
    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r!=MI_RESULT_OK) goto CleanUp;
    codecer.servername = MI_T("TestServer");
    codecer.namespacename = MI_T("root/testnames/pace");

    SetCallback(&codecer);
    MI_ClassA *ca;
    MI_Instance *err = NULL;
    r = MI_Deserializer_DeserializeClassArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)classmof,
        sizeof(classmof),
        NULL,
        codecer.servername,
        codecer.namespacename,
        NULL,
        &ca,
        &err);
    NitsAssert( r==MI_RESULT_OK, L"deserialize class mof failed");
    if (r!=MI_RESULT_OK) goto CleanUp;
    NitsAssert( err==NULL, L"deserialize class should not output error instance");
    NitsAssert( ca!=NULL, L"deserialize class should output class arary");
    _Analysis_assume_(ca != NULL);
    NitsAssert( ca->size == 1, L"deserialize class mof failed");
    NitsAssert( codecer.classNeedCalledTimes == 1, L"deserialize classNeeded callback time is wrong");

    int c = Tcscasecmp(ca->data[0]->classDecl->name, MI_T("D"));
    NitsAssert(c == 0, L"Class name is wrong");
    NitsAssert(ca->data[0]->classDecl->numProperties == 4, L"Class property count is wrong");
    MI_Deserializer_ReleaseClassArray(ca);

CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

/*=============================================================================
**
** Test schema not found case class deserialization
**
=============================================================================*/
NitsTest(TestClass_NoParentSchema_SchemaValidateOptions)
    char classmof[] = "class D:A {string P1; uint8 P2;};";
    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r!=MI_RESULT_OK) goto CleanUp;

    SetCallback(&codecer);
    codecer.retvalueClassNeed = MI_RESULT_NOT_FOUND;
    MI_ClassA *ca;
    MI_Instance *err = NULL;
    r = MI_Deserializer_DeserializeClassArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)classmof,
        sizeof(classmof),
        NULL,
        codecer.servername,
        codecer.namespacename,
        NULL,
        &ca,
        &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize class mof should failed with MI_RESULT_FAILED");
    NitsAssert( ca == NULL, L"deserialize class mof should get NULL class array");
    NitsAssert( err != NULL, L"class deserialize error instance is NULL");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, 2, MI_ERRORCATEGORY_SYNTAX_ERROR);
    MI_Instance_DeleteHelper(err);

    /* change option will not change result for class deserialization */
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_LOOSE);
    r = MI_Deserializer_DeserializeClassArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)classmof,
        sizeof(classmof),
        NULL,
        codecer.servername,
        codecer.namespacename,
        NULL,
        &ca,
        &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize class mof should failed with MI_RESULT_FAILED");
    NitsAssert( ca == NULL, L"deserialize class mof should get NULL class array");
    NitsAssert( err != NULL, L"class deserialize error instance is NULL");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, 2, MI_ERRORCATEGORY_SYNTAX_ERROR);
    MI_Instance_DeleteHelper(err);

    /* change option to non supported value will get different error */
    SetSchemaValidationOption(&codecer, MI_T("UNKNOWN VALUE"));
    r = MI_Deserializer_DeserializeClassArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)classmof,
        sizeof(classmof),
        NULL,
        codecer.servername,
        codecer.namespacename,
        NULL,
        &ca,
        &err);
    NitsAssert( r==MI_RESULT_NOT_SUPPORTED, L"deserialize class mof should failed with MI_RESULT_NOT_SUPPORTED");
    NitsAssert( ca == NULL, L"deserialize class mof should get NULL class array");
    NitsAssert( err != NULL, L"class deserialize error instance is NULL");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MI, MI_RESULT_FAILED, MI_ERRORCATEGORY_INVALID_ARGUMENT);
    MI_Instance_DeleteHelper(err);

CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

/*=============================================================================
**
** Test various callbacks for instance deserialization
**
=============================================================================*/
NitsTest(TestInstance_Callbacks)
    char mof[] = "INSTAnce of A {ka=\"abcd\"; value=2;};" \
        "INSTAnce of C {kc=123456; value=\"A test '\\\"value\";};";
    MI_Result r;
    MI_Value v;
    MI_Type t;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r!=MI_RESULT_OK) goto CleanUp;

    SetCallback(&codecer);
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_STRICT);
    MI_InstanceA *ia;
    MI_Instance *err = NULL;
    MI_Uint32 readbytes;
    MI_Uint32 moflen = sizeof(mof);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_OK, L"deserialize failed");
    if (r!=MI_RESULT_OK) goto CleanUp;

    NitsAssert( err==NULL, L"deserialize should not output error instance");
    NitsAssert( ia!=NULL, L"deserialize should output instance arary");
    NitsAssert( ia->size == 2, L"deserialize class mof failed");
    NitsAssert( readbytes == (moflen-1), L"deserializer read length is wrong");
    NitsAssert( codecer.classNeedCalledTimes == 2, L"deserialize classNeeded callback count is wrong");

    int c = Tcscasecmp(ia->data[0]->classDecl->name, MI_T("A"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[0], MI_T("ka"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read ka property failed");
    NitsAssert( t==MI_STRING, L"ka property should be MI_STRING type");
    c = Tcscmp(v.string, MI_T("abcd"));
    NitsAssert(c == 0, L"ka property value is wrong");
    r = MI_Instance_GetElement(ia->data[0], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_UINT32, L"value property should be MI_UINT32");
    NitsAssert( v.uint32 == 2, L"value property value is wrong");

    c = Tcscasecmp(ia->data[1]->classDecl->name, MI_T("C"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("kc"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read kc property failed");
    NitsAssert( t==MI_UINT32, L"kc property should be MI_UINT32 type");
    NitsAssert( v.uint32 == 123456, L"kc property value is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_STRING, L"value property should be MI_STRING");
    c = Tcscmp(v.string, MI_T("A test '\"value"));
    NitsAssert(c == 0, L"value property value is wrong");

    MI_Deserializer_ReleaseInstanceArray(ia);
CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest


/*=============================================================================
**
** Test schema validation option for instance deserialization
**
=============================================================================*/
NitsTest(TestInstance_SchemaValidationOptions_OneClassUndefined)
    char mof[] = "INSTAnce of A {ka=\"abcd\"; value=2;};" \
        "INSTAnce of UnknownCLASS {kd=123456; value=\"A test '\\\"value\";};";
    MI_Result r;
    MI_Value v;
    MI_Type t;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        return;

    SetCallback(&codecer);

    MI_InstanceA *ia;
    MI_Instance *err = NULL;
    MI_Uint32 readbytes;
    MI_Uint32 moflen = sizeof(mof);

    /* Default */
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_DEFAULT);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize should fail");
    NitsAssert( err!=NULL, L"deserialize should not output error instance");
    NitsAssert( ia==NULL, L"deserialize should output instance arary");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, ID_UNDEFINED_CLASS, MI_ERRORCATEGORY_SYNTAX_ERROR);
    NitsAssert( codecer.classNeedCalledTimes == 2, L"deserialize classNeeded callback count is wrong");
    MI_Instance_DeleteHelper(err);
    DeleteMofCodecer(&codecer);
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);

    /* Ignore property type */
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_IGNORE_PROPERTYTYPE);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize should fail");
    NitsAssert( err!=NULL, L"deserialize should not output error instance");
    NitsAssert( ia==NULL, L"deserialize should output instance arary");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, ID_UNDEFINED_CLASS, MI_ERRORCATEGORY_SYNTAX_ERROR);
    NitsAssert( codecer.classNeedCalledTimes == 2, L"deserialize classNeeded callback count is wrong");
    MI_Instance_DeleteHelper(err);
    DeleteMofCodecer(&codecer);
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);

    /* Strict */
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_STRICT);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize should fail");
    NitsAssert( err!=NULL, L"deserialize should not output error instance");
    NitsAssert( ia==NULL, L"deserialize should output instance arary");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, ID_UNDEFINED_CLASS, MI_ERRORCATEGORY_SYNTAX_ERROR);
    NitsAssert( codecer.classNeedCalledTimes == 2, L"deserialize classNeeded callback count is wrong");
    MI_Instance_DeleteHelper(err);
    DeleteMofCodecer(&codecer);
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);

    /* Loose */
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_LOOSE);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize should fail");
    NitsAssert( err!=NULL, L"deserialize should not output error instance");
    NitsAssert( ia==NULL, L"deserialize should output instance arary");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, ID_UNDEFINED_CLASS, MI_ERRORCATEGORY_SYNTAX_ERROR);
    NitsAssert( codecer.classNeedCalledTimes == 2, L"deserialize classNeeded callback count is wrong");
    MI_Instance_DeleteHelper(err);
    DeleteMofCodecer(&codecer);
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);

    /* Ignore - success */
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_IGNORE);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_OK, L"deserialize fail");
    if ( r!=MI_RESULT_OK )
        goto CleanUp;
    NitsAssert( err==NULL, L"deserialize should not output error instance");
    NitsAssert( ia!=NULL, L"deserialize should output instance arary");
    NitsAssert( ia->size == 2, L"deserialize class mof failed");
    NitsAssert( readbytes == (moflen-1), L"deserializer read length is wrong");
    NitsAssert( codecer.classNeedCalledTimes == 2, L"deserialize classNeeded callback count is wrong");

    int c = Tcscasecmp(ia->data[0]->classDecl->name, MI_T("A"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[0], MI_T("ka"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read ka property failed");
    NitsAssert( t==MI_STRING, L"ka property should be MI_STRING type");
    c = Tcscmp(v.string, MI_T("abcd"));
    NitsAssert(c == 0, L"ka property value is wrong");
    r = MI_Instance_GetElement(ia->data[0], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_UINT32, L"value property should be MI_UINT32");
    NitsAssert( v.uint32 == 2, L"value property value is wrong");

    c = Tcscasecmp(ia->data[1]->classDecl->name, MI_T("UnknownCLASS"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("kd"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read kd property failed");
    NitsAssert( t==MI_SINT64, L"kd property should be MI_SINT64 type");
    NitsAssert( v.sint64 == 123456, L"kd property value is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_STRING, L"value property should be MI_STRING");
    c = Tcscmp(v.string, MI_T("A test '\"value"));
    NitsAssert(c == 0, L"value property value is wrong");
    MI_Deserializer_ReleaseInstanceArray(ia);

CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

NitsTest(TestInstance_SchemaValidationOptions_OnePropertyMissedFromClass)
    char mof[] = "INSTAnce of A {ka=\"abcd\"; value=2;};" \
        "INSTAnce of C {kc=123456; value=\"A test '\\\"value\"; p3=123;};";
    MI_Result r;
    MI_Value v;
    MI_Type t;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);

    MI_InstanceA *ia;
    MI_Instance *err = NULL;
    MI_Uint32 readbytes;
    MI_Uint32 moflen = sizeof(mof);

    /* Default */
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_DEFAULT);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize should fail");
    NitsAssert( err!=NULL, L"deserialize should not output error instance");
    NitsAssert( ia==NULL, L"deserialize should output instance arary");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, ID_UNDEFINED_PROPERTY, MI_ERRORCATEGORY_SYNTAX_ERROR);
    NitsAssert( codecer.classNeedCalledTimes == 2, L"deserialize classNeeded callback count is wrong");
    MI_Instance_DeleteHelper(err);
    DeleteMofCodecer(&codecer);
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);

    /* Ignore property type */
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_IGNORE_PROPERTYTYPE);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize should fail");
    NitsAssert( err!=NULL, L"deserialize should not output error instance");
    NitsAssert( ia==NULL, L"deserialize should output instance arary");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, ID_UNDEFINED_PROPERTY, MI_ERRORCATEGORY_SYNTAX_ERROR);
    NitsAssert( codecer.classNeedCalledTimes == 2, L"deserialize classNeeded callback count is wrong");
    MI_Instance_DeleteHelper(err);
    DeleteMofCodecer(&codecer);
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);

    /* Strict */
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_STRICT);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize should fail");
    NitsAssert( err!=NULL, L"deserialize should not output error instance");
    NitsAssert( ia==NULL, L"deserialize should output instance arary");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, ID_UNDEFINED_PROPERTY, MI_ERRORCATEGORY_SYNTAX_ERROR);
    NitsAssert( codecer.classNeedCalledTimes == 2, L"deserialize classNeeded callback count is wrong");
    MI_Instance_DeleteHelper(err);
    DeleteMofCodecer(&codecer);
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);

    /* Loose - success */
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_LOOSE);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_OK, L"deserialize failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( err==NULL, L"deserialize should not output error instance");
    NitsAssert( ia!=NULL, L"deserialize should output instance arary");
    NitsAssert( ia->size == 2, L"deserialize class mof failed");
    NitsAssert( readbytes == (moflen-1), L"deserializer read length is wrong");
    NitsAssert( codecer.classNeedCalledTimes == 2, L"deserialize classNeeded callback count is wrong");

    int c = Tcscasecmp(ia->data[1]->classDecl->name, MI_T("C"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("kc"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read kc property failed");
    NitsAssert( t==MI_UINT32, L"kc property should be MI_UINT32 type");
    NitsAssert( v.uint32 == 123456, L"kc property value is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_STRING, L"value property should be MI_STRING");
    c = Tcscmp(v.string, MI_T("A test '\"value"));
    NitsAssert(c == 0, L"value property value is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("P3"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read P3 property failed");
    NitsAssert( t==MI_SINT64, L"P3 property should be MI_SINT64 type");
    NitsAssert( v.sint64 == 123, L"P3 property value is wrong");
    MI_Deserializer_ReleaseInstanceArray(ia);
    DeleteMofCodecer(&codecer);
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);

    /* Ignore - success */
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_IGNORE);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_OK, L"deserialize failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( err==NULL, L"deserialize should not output error instance");
    NitsAssert( ia!=NULL, L"deserialize should output instance arary");
    NitsAssert( ia->size == 2, L"deserialize class mof failed");
    NitsAssert( readbytes == (moflen-1), L"deserializer read length is wrong");
    NitsAssert( codecer.classNeedCalledTimes == 2, L"deserialize classNeeded callback count is wrong");

    c = Tcscasecmp(ia->data[1]->classDecl->name, MI_T("C"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("kc"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read kc property failed");
    NitsAssert( t==MI_UINT32, L"kc property should be MI_UINT32 type");
    NitsAssert( v.uint32 == 123456, L"kc property value is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_STRING, L"value property should be MI_STRING");
    c = Tcscmp(v.string, MI_T("A test '\"value"));
    NitsAssert(c == 0, L"value property value is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("P3"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read P3 property failed");
    NitsAssert( t==MI_SINT64, L"P3 property should be MI_SINT64 type");
    NitsAssert( v.sint64 == 123, L"P3 property value is wrong");

    MI_Deserializer_ReleaseInstanceArray(ia);

CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

NitsTest(TestInstance_SchemaValidationOptions_WrongPropertyType)
    char mof[] = "INSTAnce of A {ka=\"abcd\"; value=2;};" \
        "INSTAnce of C {kc=\"dir\"; value=\"A test '\\\"value\";};";
    MI_Result r;
    MI_Value v;
    MI_Type t;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);

    MI_InstanceA *ia;
    MI_Instance *err = NULL;
    MI_Uint32 readbytes;
    MI_Uint32 moflen = sizeof(mof);

    /* Default */
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_DEFAULT);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize should fail");
    NitsAssert( err!=NULL, L"deserialize should not output error instance");
    NitsAssert( ia==NULL, L"deserialize should output instance arary");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, ID_CONVERT_PROPERTY_VALUE_FAILED, MI_ERRORCATEGORY_SYNTAX_ERROR);
    NitsAssert( codecer.classNeedCalledTimes == 2, L"deserialize classNeeded callback count is wrong");
    MI_Instance_DeleteHelper(err);
    DeleteMofCodecer(&codecer);
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);

    /* Loose */
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_LOOSE);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize should fail");
    NitsAssert( err!=NULL, L"deserialize should not output error instance");
    NitsAssert( ia==NULL, L"deserialize should output instance arary");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, ID_CONVERT_PROPERTY_VALUE_FAILED, MI_ERRORCATEGORY_SYNTAX_ERROR);
    NitsAssert( codecer.classNeedCalledTimes == 2, L"deserialize classNeeded callback count is wrong");
    MI_Instance_DeleteHelper(err);
    DeleteMofCodecer(&codecer);
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);

    /* Strict */
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_STRICT);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize should fail");
    NitsAssert( err!=NULL, L"deserialize should not output error instance");
    NitsAssert( ia==NULL, L"deserialize should output instance arary");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, ID_CONVERT_PROPERTY_VALUE_FAILED, MI_ERRORCATEGORY_SYNTAX_ERROR);
    NitsAssert( codecer.classNeedCalledTimes == 2, L"deserialize classNeeded callback count is wrong");
    MI_Instance_DeleteHelper(err);
    DeleteMofCodecer(&codecer);
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);

    /* Ignore property type -success */
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_IGNORE_PROPERTYTYPE);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_OK, L"deserialize failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( err==NULL, L"deserialize should not output error instance");
    NitsAssert( ia!=NULL, L"deserialize should output instance arary");
    NitsAssert( ia->size == 2, L"deserialize class mof failed");
    NitsAssert( readbytes == (moflen-1), L"deserializer read length is wrong");
    NitsAssert( codecer.classNeedCalledTimes == 2, L"deserialize classNeeded callback count is wrong");

    int c = Tcscasecmp(ia->data[1]->classDecl->name, MI_T("C"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("kc"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read kc property failed");
    NitsAssert( t==MI_STRING, L"kc property should be MI_STRING type");
    c = Tcscmp(v.string, MI_T("dir"));
    NitsAssert( c == 0, L"kc property value is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_STRING, L"value property should be MI_STRING");
    c = Tcscmp(v.string, MI_T("A test '\"value"));
    NitsAssert(c == 0, L"value property value is wrong");
    MI_Deserializer_ReleaseInstanceArray(ia);
    DeleteMofCodecer(&codecer);
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);

    /* Ignore - success */
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_IGNORE);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_OK, L"deserialize failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( err==NULL, L"deserialize should not output error instance");
    NitsAssert( ia!=NULL, L"deserialize should output instance arary");
    _Analysis_assume_(ia != NULL);
    NitsAssert( ia->size == 2, L"deserialize class mof failed");
    NitsAssert( readbytes == (moflen-1), L"deserializer read length is wrong");
    NitsAssert( codecer.classNeedCalledTimes == 2, L"deserialize classNeeded callback count is wrong");

    c = Tcscasecmp(ia->data[1]->classDecl->name, MI_T("C"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("kc"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read kc property failed");
    NitsAssert( t==MI_STRING, L"kc property should be MI_STRING type");
    c = Tcscmp(v.string, MI_T("dir"));
    NitsAssert( c == 0, L"kc property value is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_STRING, L"value property should be MI_STRING");
    c = Tcscmp(v.string, MI_T("A test '\"value"));
    NitsAssert(c == 0, L"value property value is wrong");

    MI_Deserializer_ReleaseInstanceArray(ia);
CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest


/*=============================================================================
**
** Test different schema inputs for instance deserialization
**
=============================================================================*/
NitsTest(TestInstance_Schema_Miscs)
    /* Class schema provided via classes parameter */
    char mof[] = "INSTAnce of A {ka=\"abcd\"; value=2;};" \
        "INSTAnce of C {kc=123456; value=\"A test '\\\"value\";};";
    MI_Result r;
    MI_Value v;
    MI_Type t;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_STRICT);
    MI_InstanceA *ia;
    MI_Instance *err = NULL;
    MI_Uint32 readbytes;
    MI_Uint32 moflen = sizeof(mof);
    r = InitializeTestData();
    NitsAssert( r==MI_RESULT_OK, L"Global data failed to initialized");
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        g_classes,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_OK, L"deserialize failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( err==NULL, L"deserialize should not output error instance");
    NitsAssert( ia!=NULL, L"deserialize should output instance arary");
    NitsAssert( ia->size == 2, L"deserialize class mof failed");
    NitsAssert( readbytes == (moflen-1), L"deserializer read length is wrong");

    /* It should use g_classes instead of callback*/
    NitsAssert( codecer.classNeedCalledTimes == 0, L"deserialize classNeeded callback count is wrong");

    int c = Tcscasecmp(ia->data[0]->classDecl->name, MI_T("A"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[0], MI_T("ka"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read ka property failed");
    NitsAssert( t==MI_STRING, L"ka property should be MI_STRING type");
    c = Tcscmp(v.string, MI_T("abcd"));
    NitsAssert(c == 0, L"ka property value is wrong");
    r = MI_Instance_GetElement(ia->data[0], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_UINT32, L"value property should be MI_UINT32");
    NitsAssert( v.uint32 == 2, L"value property value is wrong");

    c = Tcscasecmp(ia->data[1]->classDecl->name, MI_T("C"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("kc"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read kc property failed");
    NitsAssert( t==MI_UINT32, L"kc property should be MI_UINT32 type");
    NitsAssert( v.uint32 == 123456, L"kc property value is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_STRING, L"value property should be MI_STRING");
    c = Tcscmp(v.string, MI_T("A test '\"value"));
    NitsAssert(c == 0, L"value property value is wrong");

    MI_Deserializer_ReleaseInstanceArray(ia);
    ia = NULL;
    DeleteMofCodecer(&codecer);
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);

    /* Call classobjectneeded callback for non-found class*/
    SetCallback(&codecer);
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_STRICT);
    /* Ask ClassObjectNeededCallback to search extended class also */
    codecer.classNeedCallbackOptions = 1;
    char mof2[] = "INSTAnce of A {ka=\"abcd\"; value=2;};" \
        "INSTAnce of C {kc=123456; value=\"A test '\\\"value\";};"\
        "INSTAnce of EXA {kexa=876543; value=123;};";
    MI_Uint32 mof2len = sizeof(mof2);

    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof2,
        mof2len,
        g_classes,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_OK, L"deserialize failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( err==NULL, L"deserialize should not output error instance");
    NitsAssert( ia!=NULL, L"deserialize should output instance arary");
    NitsAssert( ia->size == 3, L"deserialize class mof failed");
    NitsAssert( readbytes == (mof2len-1), L"deserializer read length is wrong");

    /* It should callback once for EXA class */
    NitsAssert( codecer.classNeedCalledTimes == 1, L"deserialize classNeeded callback count is wrong");

    c = Tcscasecmp(ia->data[0]->classDecl->name, MI_T("A"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[0], MI_T("ka"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read ka property failed");
    NitsAssert( t==MI_STRING, L"ka property should be MI_STRING type");
    c = Tcscmp(v.string, MI_T("abcd"));
    NitsAssert(c == 0, L"ka property value is wrong");
    r = MI_Instance_GetElement(ia->data[0], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_UINT32, L"value property should be MI_UINT32");
    NitsAssert( v.uint32 == 2, L"value property value is wrong");

    c = Tcscasecmp(ia->data[1]->classDecl->name, MI_T("C"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("kc"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read kc property failed");
    NitsAssert( t==MI_UINT32, L"kc property should be MI_UINT32 type");
    NitsAssert( v.uint32 == 123456, L"kc property value is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_STRING, L"value property should be MI_STRING");
    c = Tcscmp(v.string, MI_T("A test '\"value"));
    NitsAssert(c == 0, L"value property value is wrong");

    c = Tcscasecmp(ia->data[2]->classDecl->name, MI_T("EXa"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[2], MI_T("kexa"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read kexa property failed");
    NitsAssert( t==MI_UINT32, L"kexa property should be MI_UINT32 type");
    NitsAssert( v.uint32 == 876543, L"kexa property value is wrong");
    r = MI_Instance_GetElement(ia->data[2], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_UINT32, L"value property should be MI_UINT32");
    NitsAssert( v.uint32 == 123, L"value property value is wrong");

    MI_Deserializer_ReleaseInstanceArray(ia);
    DeleteMofCodecer(&codecer);
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;

    /* Use self-contained schema */
    SetCallback(&codecer);
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_STRICT);
    /* Ask ClassObjectNeededCallback to search extended class also */
    codecer.classNeedCallbackOptions = 1;
    char mof3[] = "class EXa {uint8 idkey; sint16 value;};" \
        "INSTAnce of A {ka=\"abcd\"; value=2;};" \
        "INSTAnce of C {kc=123456; value=\"A test '\\\"value\";};"\
        "INSTAnce of EXA {idkey=250; value=32767;};";
    MI_Uint32 mof3len = sizeof(mof3);

    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof3,
        mof3len,
        g_classes,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_OK, L"deserialize failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( err==NULL, L"deserialize should not output error instance");
    NitsAssert( ia!=NULL, L"deserialize should output instance arary");
    NitsAssert( ia->size == 3, L"deserialize class mof failed");
    NitsAssert( readbytes == (mof3len-1), L"deserializer read length is wrong");

    /* It should callback once for EXA class */
    NitsAssert( codecer.classNeedCalledTimes == 0, L"deserialize classNeeded callback count is wrong");

    c = Tcscasecmp(ia->data[0]->classDecl->name, MI_T("A"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[0], MI_T("ka"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read ka property failed");
    NitsAssert( t==MI_STRING, L"ka property should be MI_STRING type");
    c = Tcscmp(v.string, MI_T("abcd"));
    NitsAssert(c == 0, L"ka property value is wrong");
    r = MI_Instance_GetElement(ia->data[0], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_UINT32, L"value property should be MI_UINT32");
    NitsAssert( v.uint32 == 2, L"value property value is wrong");

    c = Tcscasecmp(ia->data[1]->classDecl->name, MI_T("C"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("kc"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read kc property failed");
    NitsAssert( t==MI_UINT32, L"kc property should be MI_UINT32 type");
    NitsAssert( v.uint32 == 123456, L"kc property value is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_STRING, L"value property should be MI_STRING");
    c = Tcscmp(v.string, MI_T("A test '\"value"));
    NitsAssert(c == 0, L"value property value is wrong");

    /* schema come from buf buffer */
    c = Tcscasecmp(ia->data[2]->classDecl->name, MI_T("EXa"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[2], MI_T("idkey"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read idkey property failed");
    NitsAssert( t==MI_UINT8, L"idkey property should be MI_UINT8 type");
    NitsAssert( v.uint8 == 250, L"idkey property value is wrong");
    r = MI_Instance_GetElement(ia->data[2], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_SINT16, L"value property should be MI_SINT16");
    MI_Sint16 s16v = 32767;
    NitsAssert( v.sint16 == s16v, L"value property value is wrong");

    MI_Deserializer_ReleaseInstanceArray(ia);
CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

/*=============================================================================
**
** Test different scenario of alias(es)
**
=============================================================================*/
NitsTest(TestInstance_AliasMiscs)
    /* Undefined alias */
    char mof[] = "INSTAnce of A as $x{ka=\"abcd\"; value=2;};" \
        "INSTAnce of C as $y{kc=123456; value=\"A test '\\\"value\";};" \
        "INSTAnce of D {P1=$x;p2=$y;p3=$z;};";

    MI_Result r;
    MI_Value v;
    MI_Type t;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_IGNORE);
    MI_InstanceA *ia;
    MI_Instance *err = NULL;
    MI_Uint32 readbytes;
    MI_Uint32 moflen = sizeof(mof);
    r = InitializeTestData();
    NitsAssert( r==MI_RESULT_OK, L"Global data failed to initialized");
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        g_classes,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize should failed");
    NitsAssert( err!=NULL, L"deserialize should generate error instance");
    NitsAssert( ia==NULL, L"deserialize should output no instance");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, ID_UNDEFINED_INSTANCE_ALIAS, MI_ERRORCATEGORY_SYNTAX_ERROR);
    MI_Instance_DeleteHelper(err);
    DeleteMofCodecer(&codecer);
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);

    /* Duplicate alias defined */
    char mof2[] = "INSTAnce of A as $x{ka=\"abcd\"; value=2;};" \
        "INSTAnce of C as $x{kc=123456; value=\"A test '\\\"value\";};";
    moflen = sizeof(mof2);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof2,
        moflen,
        g_classes,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize should failed");
    NitsAssert( err!=NULL, L"deserialize should generate error instance");
    NitsAssert( ia==NULL, L"deserialize should output no instance");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, ID_ALIAS_DECL_ALREADY_DEFINED, MI_ERRORCATEGORY_SYNTAX_ERROR);
    MI_Instance_DeleteHelper(err);

    /* Unreferenced alias should be returned */
    char mof3[] = "INSTAnce of A as $x{ka=\"abcd\"; value=2;};" \
        "INSTAnce of C as $y{kc=123456; value=\"A test '\\\"value\";};" \
        "INSTAnce of D {P1=$x;};";
    moflen = sizeof(mof3);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof3,
        moflen,
        g_classes,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_OK, L"deserialize failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( err==NULL, L"deserialize should not output error instance");
    NitsAssert( ia!=NULL, L"deserialize should output instance arary");
    NitsAssert( ia->size == 2, L"deserialize mof failed");
    NitsAssert( readbytes == (moflen-1), L"deserializer read length is wrong");

    /* It should callback once for D class */
    NitsAssert( codecer.classNeedCalledTimes == 1, L"deserialize classNeeded callback count is wrong");

    int c = Tcscasecmp(ia->data[0]->classDecl->name, MI_T("C"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[0], MI_T("kc"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read kc property failed");
    NitsAssert( t==MI_UINT32, L"kc property should be MI_UINT32 type");
    NitsAssert( v.uint32 == 123456, L"kc property value is wrong");
    r = MI_Instance_GetElement(ia->data[0], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_STRING, L"value property should be MI_STRING");
    c = Tcscmp(v.string, MI_T("A test '\"value"));
    NitsAssert(c == 0, L"value property value is wrong");

    c = Tcscasecmp(ia->data[1]->classDecl->name, MI_T("D"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("P1"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read P1 property failed");
    NitsAssert( t==MI_INSTANCE, L"P1 property should be MI_INSTANCE type");
    NitsAssert( v.instance !=NULL, L"P1 property value is NULL");

    MI_Instance *p1=v.instance;
    c = Tcscasecmp(p1->classDecl->name, MI_T("A"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(p1, MI_T("ka"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read ka property failed");
    NitsAssert( t==MI_STRING, L"ka property should be MI_STRING type");
    c = Tcscmp(v.string, MI_T("abcd"));
    NitsAssert(c == 0, L"ka property value is wrong");
    r = MI_Instance_GetElement(p1, MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_UINT32, L"value property should be MI_UINT32");
    NitsAssert( v.uint32 == 2, L"value property value is wrong");

    MI_Deserializer_ReleaseInstanceArray(ia);

CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest


/*=============================================================================
**
** Test include mof (schema) for class deserialization
**
=============================================================================*/
NitsTest(TestClass_IncludeMof_SingleInclude)
char classmof[] = "#pragma include (\"etc/a.mof\")"\
    "class D:A {string PD;};";
    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    codecer.servername = MI_T("TestServer");
    codecer.namespacename = MI_T("root/testnames/pace");
    SetCallback(&codecer);
    MI_ClassA *ca;
    MI_Instance *err = NULL;
    r = MI_Deserializer_DeserializeClassArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)classmof,
        sizeof(classmof),
        NULL,
        codecer.servername,
        codecer.namespacename,
        NULL,
        &ca,
        &err);
    NitsAssert( r==MI_RESULT_OK, L"deserialize class mof failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( err==NULL, L"deserialize class should not output error instance");
    NitsAssert( ca!=NULL, L"deserialize class should output class arary");
    _Analysis_assume_(ca != NULL);
    NitsAssert( ca->size == 2, L"deserialize class mof failed");
    NitsAssert( codecer.classNeedCalledTimes == 0, L"deserialize classNeeded callback time is wrong");
    NitsAssert( codecer.includeFileCalledTimes == 1, L"deserialize includefile callback time is wrong");
    NitsAssert( codecer.freeincludeFileCalledTimes == 1, L"deserialize freeincludefile callback time is wrong");

    int c = Tcscasecmp(ca->data[0]->classDecl->name, MI_T("A"));
    NitsAssert(c == 0, L"Class name is wrong");
    NitsAssert(ca->data[0]->classDecl->numProperties == 2, L"Class property count is wrong");

    c = Tcscasecmp(ca->data[1]->classDecl->name, MI_T("D"));
    NitsAssert(c == 0, L"Class name is wrong");
    NitsAssert(ca->data[1]->classDecl->numProperties == 3, L"Class property count is wrong");
    MI_Deserializer_ReleaseClassArray(ca);
CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

NitsTest(TestClass_IncludeMof_RecurseInclude)
    char classmof[] =
    "#pragma include (\"test/include.mof\")"\
    "#pragma include (\"test/m.mof\")"\
    "class D:M {string PD;};" \
    "class E:B {string PE;};";
    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    codecer.servername = MI_T("TestServer");
    codecer.namespacename = MI_T("root/testnames/pace");
    SetCallback(&codecer);
    MI_ClassA *ca;
    MI_Instance *err = NULL;
    r = MI_Deserializer_DeserializeClassArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)classmof,
        sizeof(classmof),
        NULL,
        codecer.servername,
        codecer.namespacename,
        NULL,
        &ca,
        &err);
    NitsAssert( r==MI_RESULT_OK, L"deserialize class mof failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( err==NULL, L"deserialize class should not output error instance");
    NitsAssert( ca!=NULL, L"deserialize class should output class arary");
    _Analysis_assume_(ca != NULL);
    NitsAssert( ca->size == 5, L"deserialize class mof failed");
    NitsAssert( codecer.classNeedCalledTimes == 0, L"deserialize classNeeded callback time is wrong");
    NitsAssert( codecer.includeFileCalledTimes == 4, L"deserialize includefile callback time is wrong");
    NitsAssert( codecer.freeincludeFileCalledTimes == 4, L"deserialize freeincludefile callback time is wrong");

    int c = Tcscasecmp(ca->data[0]->classDecl->name, MI_T("B"));
    NitsAssert(c == 0, L"Class name is wrong");
    NitsAssert(ca->data[0]->classDecl->numProperties == 2, L"Class property count is wrong");

    c = Tcscasecmp(ca->data[1]->classDecl->name, MI_T("C"));
    NitsAssert(c == 0, L"Class name is wrong");
    NitsAssert(ca->data[1]->classDecl->numProperties == 2, L"Class property count is wrong");

    c = Tcscasecmp(ca->data[2]->classDecl->name, MI_T("M"));
    NitsAssert(c == 0, L"Class name is wrong");
    NitsAssert(ca->data[2]->classDecl->numProperties == 3, L"Class property count is wrong");

    c = Tcscasecmp(ca->data[3]->classDecl->name, MI_T("D"));
    NitsAssert(c == 0, L"Class name is wrong");
    NitsAssert(ca->data[3]->classDecl->numProperties == 4, L"Class property count is wrong");

    c = Tcscasecmp(ca->data[4]->classDecl->name, MI_T("E"));
    NitsAssert(c == 0, L"Class name is wrong");
    NitsAssert(ca->data[4]->classDecl->numProperties == 3, L"Class property count is wrong");

    MI_Deserializer_ReleaseClassArray(ca);
CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

NitsTest(TestClass_IncludeMof_CallbackReturnError)
char classmof[] = "#pragma include (\"etc/a.mof\")"\
    "class D {string PD;};";
    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    codecer.servername = MI_T("TestServer");
    codecer.namespacename = MI_T("root/testnames/pace");
    SetCallback(&codecer);
    /* Ask callback to return a failure code to parse */
    codecer.retvalueIncludeFile = MI_RESULT_NOT_FOUND;
    MI_ClassA *ca;
    MI_Instance *err = NULL;
    r = MI_Deserializer_DeserializeClassArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)classmof,
        sizeof(classmof),
        NULL,
        codecer.servername,
        codecer.namespacename,
        NULL,
        &ca,
        &err);
    NitsAssert( r==MI_RESULT_OK, L"deserialize class mof failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( err==NULL, L"deserialize class should not output error instance");
    NitsAssert( ca!=NULL, L"deserialize class should output class arary");
    _Analysis_assume_(ca != NULL);
    NitsAssert( ca->size == 1, L"deserialize class mof failed");
    NitsAssert( codecer.classNeedCalledTimes == 0, L"deserialize classNeeded callback time is wrong");
    NitsAssert( codecer.includeFileCalledTimes == 1, L"deserialize includefile callback time is wrong");
    NitsAssert( codecer.freeincludeFileCalledTimes == 0, L"deserialize freeincludefile callback time is wrong");

    int c = Tcscasecmp(ca->data[0]->classDecl->name, MI_T("D"));
    NitsAssert(c == 0, L"Class name is wrong");
    NitsAssert(ca->data[0]->classDecl->numProperties == 1, L"Class property count is wrong");
    MI_Deserializer_ReleaseClassArray(ca);
CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

/*=============================================================================
**
** Test include mof (schema) for instance deserialization
**
=============================================================================*/
NitsTest(TestInstance_IncludeSimpleMof)
    char mof[] =
    "#pragma include (\"c.mof\")"\
    "INSTAnce of C {kc=0XFFFF; value=\"A test '\\\"value\";};"\
    "INSTAnce of C {kc=0XFFFE; value=\"A test '\\\"value\";};"\
    "INSTAnce of C {kc=0XFFFD; value=\"A test '\\\"value\";};"\
    "INSTAnce of C {kc=0XFFFC; value=\"A test '\\\"value\";};"\
    "INSTAnce of C {kc=0XFFFB; value=\"A test '\\\"value\";};";
    MI_Result r;
    MI_Value v;
    MI_Type t;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_STRICT);
    MI_InstanceA *ia;
    MI_Instance *err = NULL;
    MI_Uint32 readbytes;
    MI_Uint32 moflen = sizeof(mof);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_OK, L"deserialize failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( err==NULL, L"deserialize should not output error instance");
    NitsAssert( ia!=NULL, L"deserialize should output instance arary");
    _Analysis_assume_(ia != NULL);
    NitsAssert( ia->size == 5, L"deserialize class mof failed");
    NitsAssert( readbytes == (moflen-1), L"deserializer read length is wrong");
    NitsAssert( codecer.classNeedCalledTimes == 0, L"deserialize classNeeded callback count is wrong");
    NitsAssert( codecer.includeFileCalledTimes == 1, L"deserialize include file callback count is wrong");
    NitsAssert( codecer.freeincludeFileCalledTimes == 1, L"deserialize free include file count is wrong");

    int c = Tcscasecmp(ia->data[0]->classDecl->name, MI_T("C"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[0], MI_T("kc"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read kc property failed");
    NitsAssert( t==MI_UINT32, L"kc property should be MI_UINT32 type");
    NitsAssert( v.uint32 == 0xFFFF, L"kc property value is wrong");
    r = MI_Instance_GetElement(ia->data[0], MI_T("value"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read value property failed");
    NitsAssert( t==MI_STRING, L"value property should be MI_STRING");
    c = Tcscmp(v.string, MI_T("A test '\"value"));
    NitsAssert(c == 0, L"value property value is wrong");

    const MI_ClassDecl* cd = ia->data[0]->classDecl;
    for(MI_Uint32 i = 1; i < 5; i++)
    {
        NitsAssert(ia->data[i]->classDecl == cd, L"class decl of instance should be same");
    }
    MI_Deserializer_ReleaseInstanceArray(ia);
CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

NitsTest(TestInstance_IncludeRecurseMof)
    char mof[] =
    "#pragma include (\"test/include.mof\")"\
    "#pragma include (\"test/m.mof\")"\
    "class D:M {string PD;};" \
    "class E:B {string PE;};" \
    "INSTAnce of D {pd=\"PD\";};" \
    "INSTAnce of E {PE=\"PE\";};";
    MI_Result r;
    MI_Value v;
    MI_Type t;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);
    SetSchemaValidationOption(&codecer, MOFCODEC_SCHEMA_VALIDATION_STRICT);
    MI_InstanceA *ia;
    MI_Instance *err = NULL;
    MI_Uint32 readbytes;
    MI_Uint32 moflen = sizeof(mof);
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)mof,
        moflen,
        NULL,
        &readbytes,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_OK, L"deserialize failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( err==NULL, L"deserialize should not output error instance");
    NitsAssert( ia!=NULL, L"deserialize should output instance arary");
    _Analysis_assume_(ia != NULL);
    NitsAssert( ia->size == 2, L"deserialize class mof failed");
    NitsAssert( readbytes == (moflen-1), L"deserializer read length is wrong");
    NitsAssert( codecer.classNeedCalledTimes == 0, L"deserialize classNeeded callback count is wrong");
    NitsAssert( codecer.includeFileCalledTimes == 4, L"deserialize include file callback count is wrong");
    NitsAssert( codecer.freeincludeFileCalledTimes == 4, L"deserialize free include file count is wrong");

    int c = Tcscasecmp(ia->data[0]->classDecl->name, MI_T("D"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[0], MI_T("PD"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read PD property failed");
    NitsAssert( t==MI_STRING, L"PD property should be MI_STRING");
    c = Tcscmp(v.string, MI_T("PD"));
    NitsAssert(c == 0, L"PD property value is wrong");

    c = Tcscasecmp(ia->data[1]->classDecl->name, MI_T("E"));
    NitsAssert(c == 0, L"Class name is wrong");
    r = MI_Instance_GetElement(ia->data[1], MI_T("PE"), &v, &t, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"Read PE property failed");
    NitsAssert( t==MI_STRING, L"PE property should be MI_STRING");
    c = Tcscmp(v.string, MI_T("PE"));
    NitsAssert(c == 0, L"PE property value is wrong");

    MI_Deserializer_ReleaseInstanceArray(ia);
CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest


NitsTest(TestClass_IncludeMof_InvalidMof1_Ensure_NoMemoryLeak)
    char classmof[] =
    "#pragma include (\"invalid.mof\")"\
    "class E {string PE;};";
    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);
    MI_ClassA *ca;
    MI_Instance *err = NULL;
    r = MI_Deserializer_DeserializeClassArray(&codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)classmof,
        sizeof(classmof),
        NULL,
        codecer.servername,
        codecer.namespacename,
        NULL,
        &ca,
        &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize class mof failed");
    NitsAssert( codecer.includeFileCalledTimes == 1, L"deserialize include file callback count is wrong");
    NitsAssert( codecer.freeincludeFileCalledTimes == 1, L"deserialize free include file count is wrong");
    NitsAssert( err != NULL, L"error instance is null");
    MI_Instance_DeleteHelper(err);
CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest


NitsTest(TestClass_IncludeMof_InvalidMof2_Ensure_NoMemoryLeak)
    char classmof[] =
    "#pragma include (\"incinvalid.mof\")"\
    "class E {string PE;};";
    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    SetCallback(&codecer);
    MI_InstanceA *ia;
    MI_Instance *err = NULL;
    r = MI_Deserializer_DeserializeInstanceArray(
        &codecer.de,
        0,
        &codecer.options,
        &codecer.callbacks,
        (MI_Uint8*)classmof,
        sizeof(classmof),
        NULL,
        NULL,
        &ia,
        &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize class mof failed");
    NitsAssert( codecer.includeFileCalledTimes == 2, L"deserialize include file callback count is wrong");
    NitsAssert( codecer.freeincludeFileCalledTimes == 2, L"deserialize free include file count is wrong");
    NitsAssert( err != NULL, L"error instance is null");
    MI_Instance_DeleteHelper(err);
CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

NitsTest(TestClass_BLUEBUG_61179_61201_61218)
    char classmof[] =
    "Class ReferenceClass"\
    "{"\
    "    [KEY]"\
    "    String key;"\
    "};"\
    "\n"\
    "[dynamic: ToInstance, provider(\"TestClass_AllDMTFTypes\"): ToInstance]"\
    "class Test_EmbeddedObjectType"\
    "{"\
    "    [EmbeddedObject]"\
    "    String p_Object;"\
    "    [EmbeddedInstance(\"ReferenceClass\")]"\
    "    String p_ObjectReferenceClass;"\
    "    [EmbeddedObject]"\
    "    String pA_Object[];"\
    "    [EmbeddedInstance(\"ReferenceClass\")]"\
    "    String pA_ObjectReferenceClass[];"\
    "    [KEY]"\
    "    Sint64 v_key;"\
    "    [ID(0)]"\
    "    String v_test = \"abc\r\";"\
    "    [implemented] uint32 SetSint64Value([in] sint64 Sint64Val);"\
    "};";

    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    MI_ClassA *ca;
    r = MI_Deserializer_DeserializeClassArray(&codecer.de, 0, &codecer.options, 0, (MI_Uint8*)classmof, sizeof(classmof), NULL, NULL, NULL, NULL, &ca, NULL);
    NitsAssert( r==MI_RESULT_OK, L"deserialize class mof failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( ca->size == 2, L"deserialize class mof failed");

    int c = Tcscasecmp(ca->data[0]->classDecl->name, MI_T("ReferenceClass"));
    NitsAssert(c == 0, L"Class name error");

    MI_Value v;
    MI_Boolean exist;
    MI_Uint32 flag;
    r = MI_Class_GetElement(ca->data[0], MI_T("key"), &v, &exist, NULL, NULL, NULL, &flag, NULL);
    NitsAssert( r==MI_RESULT_OK, L"get key property failed");
    NitsAssert( exist == MI_FALSE, L"get key property failed");
    MI_Uint32 f = flag & MI_FLAG_NULL;
    NitsAssert( f == MI_FLAG_NULL, L"key property does not have MI_FLAG_NULL set");

    c = Tcscasecmp(ca->data[1]->classDecl->name, MI_T("Test_EmbeddedObjectType"));
    NitsAssert(c == 0, L"Class name error");
    MI_QualifierSet set;
    r = MI_Class_GetElement(ca->data[1], MI_T("p_ObjectReferenceClass"), &v, &exist, NULL, NULL, &set, &flag, NULL);
    NitsAssert( r==MI_RESULT_OK, L"get p_ObjectReferenceClass property failed");
    NitsAssert( exist == MI_FALSE, L"p_ObjectReferenceClass valus should not exist");
    f = flag & MI_FLAG_NULL;
    NitsAssert( f == MI_FLAG_NULL, L"p_ObjectReferenceClass property does not have MI_FLAG_NULL set");
    MI_Type t;
    MI_Uint32 qflag;
    MI_Uint32 index;
    r = MI_QualifierSet_GetQualifier(&set, MI_T("EmbeddedInstance"), &t, &qflag, &v, &index);
    NitsAssert( r==MI_RESULT_OK, L"get EmbeddedInstance qualifer failed");
    NitsAssert( t==MI_STRING, L"EmbeddedInstance qualifer type should be MI_STRING");
    f = qflag & MI_FLAG_TOSUBCLASS;
    NitsAssert( f ==MI_FLAG_TOSUBCLASS, L"EmbeddedInstance qualifer should have MI_FLAG_TOSUBCLASS flag");
    f = qflag & MI_FLAG_ENABLEOVERRIDE;
    NitsAssert( f ==MI_FLAG_ENABLEOVERRIDE, L"EmbeddedInstance qualifer should have MI_FLAG_ENABLEOVERRIDE flag");
    c = Tcscasecmp(v.string, MI_T("ReferenceClass"));
    NitsAssert(c == 0, L"EmbeddedInstance qualifer value should be 'ReferenceClass'");

    r = MI_Class_GetElement(ca->data[1], MI_T("v_test"), &v, &exist, NULL, NULL, NULL, &flag, NULL);
    NitsAssert( r==MI_RESULT_OK, L"get v_test property failed");
    NitsAssert( exist == MI_TRUE, L"get key property failed");
    f = flag & MI_FLAG_NULL;
    NitsAssert( f == 0, L"v_test property have MI_FLAG_NULL set");
    c = Tcscasecmp(v.string, MI_T("abc\r"));
    NitsAssert(c == 0, L"v_test property default value should be 'abc\\r'");

    MI_Deserializer_ReleaseClassArray(ca);
CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

NitsTest(TestClass_BLUEBUG_61176)
    char classmof[] =
        "class A"\
        "{ string k;"\
        "};"\
        "\n"\
        "instance of A as $x"\
        "{"\
        "k = \"abc\";"\
        "};";

    char classmof_multi[] =
        "class A"\
        "{ string k;"\
        "};"\
        "\n"\
        "instance of A as $x"\
        "{"\
        "k = \"abc\";"\
        "};"\
        "class AA"\
        "{ string k;"\
        "};"\
        "\n"\
        "instance of AA as $y"\
        "{"\
        "k = \"abc\";"\
        "};";

    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;

    MI_Class *cls;
    r = MI_Deserializer_DeserializeClass(&codecer.de, 0, (MI_Uint8*)classmof, sizeof(classmof), NULL, NULL, NULL, NULL, NULL, NULL, &cls, NULL);
    NitsAssert( r==MI_RESULT_OK, L"deserialize class mof failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( cls!= NULL, L"deserialize class mof failed");

    int c = Tcscasecmp(cls->classDecl->name, MI_T("A"));
    NitsAssert(c == 0, L"Class name error");
    MI_Class_Delete(cls);

    DeleteMofCodecer(&codecer);

    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    MI_Instance *inst;
    r = MI_Deserializer_DeserializeInstance(&codecer.de, 0, (MI_Uint8*)classmof, sizeof(classmof), NULL, 0, NULL, NULL, NULL, &inst, NULL);
    NitsAssert( r==MI_RESULT_OK, L"deserialize instance mof failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( inst!= NULL, L"deserialize instance mof failed");
    c = Tcscasecmp(inst->classDecl->name, MI_T("A"));
    NitsAssert(c == 0, L"Class name error");
    MI_Instance_DeleteHelper(inst);

    DeleteMofCodecer(&codecer);
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    MI_Instance *err = NULL;
    r = MI_Deserializer_DeserializeClass(&codecer.de, 0, (MI_Uint8*)classmof_multi, sizeof(classmof_multi), NULL, NULL, NULL, NULL, NULL, NULL, &cls, &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize class mof should failed");
    NitsAssert( cls== NULL, L"deserialize class mof should failed");
    NitsAssert( err!= NULL, L"Error instance should not be null");
    MI_Value v;
    r = MI_Instance_GetElement(err, MI_T("error_Code"), &v, NULL, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"get error_Code failed");
    NitsAssert( v.uint32 == ID_PARAMETER_UNEXPECTED_RESULTCLASSCOUNT, L"error code should be ID_PARAMETER_UNEXPECTED_RESULTCLASSCOUNT");
    MI_Instance_DeleteHelper(err);
    DeleteMofCodecer(&codecer);

    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    r = MI_Deserializer_DeserializeInstance(&codecer.de, 0, (MI_Uint8*)classmof_multi, sizeof(classmof_multi), NULL, 0, NULL, NULL, NULL, &inst, &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize class mof should failed");
    NitsAssert( inst== NULL, L"deserialize class mof should failed");
    NitsAssert( err!= NULL, L"Error instance should not be null");
    r= MI_Instance_GetElement(err, MI_T("error_Code"), &v, NULL, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"get error_Code failed");
    NitsAssert( v.uint32 == ID_PARAMETER_UNEXPECTED_RESULTINSTANCECOUNT, L"error code should be ID_PARAMETER_UNEXPECTED_RESULTINSTANCECOUNT");
    MI_Instance_DeleteHelper(err);
CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

NitsTest(TestClass_BLUEBUG_366961)
    char classmof[] =
        "class A"\
        "{ string k;"\
        "};"\
        "\n"\
        "instance of B"\
        "{"\
        "m = \"abc\";"\
        "};";

    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;

    MI_Class *cls;
    MI_Instance *err = NULL;
    r = MI_Deserializer_DeserializeClass(&codecer.de, 0, (MI_Uint8*)classmof, sizeof(classmof), NULL, NULL, NULL, NULL, NULL, NULL, &cls, &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize class mof should failed");
    NitsAssert( cls== NULL, L"deserialize class mof should failed");
    NitsAssert( err!= NULL, L"Error instance should not be null");
    MI_Value v;
    r = MI_Instance_GetElement(err, MI_T("error_Code"), &v, NULL, NULL, NULL);
    NitsAssert( r==MI_RESULT_OK, L"get error_Code failed");
    NitsAssert( v.uint32 == ID_UNDEFINED_CLASS, L"error code should be ID_UNDEFINED_CLASS");
    MI_Instance_DeleteHelper(err);

CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

/* qualifer callback */
static MI_QualifierDecl dscversionQualifier = {MI_T("DSCVersion"), 0x0000000D, 0x00000031, 0x00000A80, 0x00000000, NULL};
typedef struct _QCBContext
{
    MI_QualifierDecl * qd;
    MI_Uint32 calltime;
}QCBContext;
MI_Result MI_CALL Callback_QualifierDeclNeeded(
    _In_opt_ void *context,
    _Inout_ MI_QualifierDecl *decl)
{
    QCBContext * c = (QCBContext *)context;
    MI_QualifierDecl *d = c->qd;
    c->calltime ++;
    decl->flavor = d->flavor;
    decl->scope = d->scope;
    decl->subscript = d->subscript;
    decl->type = d->type;
    decl->value = d->value;
    return MI_RESULT_OK;
}

NitsTest(TestClass_QualiferCallback)
    char classmof[] =
        "[DSCVersion(\"1\")] class A"\
        "{ string k;"\
        "};"\
        "[DSCVersion(\"2.0\")] class B"\
        "{ string m;"\
        "};";
    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    QCBContext ctx;
    ctx.qd = &dscversionQualifier;
    ctx.calltime = 0;
    codecer.callbacks.qualifierDeclNeeded = Callback_QualifierDeclNeeded;
    codecer.callbacks.qualifierDeclNeededContext = &ctx;
    MI_ClassA *cls;
    r = MI_Deserializer_DeserializeClassArray(
        &codecer.de, 0, NULL, &codecer.callbacks, (MI_Uint8*)classmof, sizeof(classmof), NULL, NULL, NULL, NULL, &cls, NULL);
    NitsAssert( r==MI_RESULT_OK, L"deserialize class mof failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    _Analysis_assume_(cls != NULL);
    NitsAssert( cls->size == 2, L"deserialize class mof failed");
    NitsAssert( ctx.calltime == 1, L"callback should be called only once");

    int c = Tcscasecmp(cls->data[0]->classDecl->name, MI_T("A"));
    NitsAssert(c == 0, L"Class name error");
    NitsAssert(cls->data[0]->classDecl->numQualifiers == 1, L"Class qualifers count is wrong");
    NitsAssert(cls->data[0]->classDecl->qualifiers[0]->value != NULL, L"Class qualifers value is NULL");
    NitsAssert(Tcscasecmp(cls->data[0]->classDecl->qualifiers[0]->name, MI_T("dscversion")) == 0, L"Class DSCVersion qualifier name is wrong");
    MI_Char * v = *((MI_Char**)cls->data[0]->classDecl->qualifiers[0]->value);
    NitsAssert(Tcscasecmp(v, MI_T("1")) == 0, L"Class DSCVersion qualifier value is wrong");

    v = *((MI_Char**)cls->data[1]->classDecl->qualifiers[0]->value);
    NitsAssert(Tcscasecmp(v, MI_T("2.0")) == 0, L"Class DSCVersion qualifier value is wrong");

    MI_Deserializer_ReleaseClassArray(cls);

CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

NitsTest(TestClass_Ref_EmbeddedClass)
    char classmof[] =
        "class A"\
        "{ string k;"\
        "};"\
        "class B"\
        "{ string m; A ref a; B ref b; C ref c; [EmbeddedObject] string o; [EmbeddedInstance(\"D\")] string d;"\
        " uint32 testmethod(C ref c, E ref e[], [EmbeddedObject] string o[], [EmbeddedInstance(\"F\")] string f[]);"\
        "};";
    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    MI_ClassA *cls;
    r = MI_Deserializer_DeserializeClassArray(
        &codecer.de, 0, NULL, NULL, (MI_Uint8*)classmof, sizeof(classmof), NULL, NULL, NULL, NULL, &cls, NULL);
    NitsAssert( r==MI_RESULT_OK, L"deserialize failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( cls->size == 2, L"deserialize should get 2 class");

    int c = Tcscasecmp(cls->data[0]->classDecl->name, MI_T("A"));
    NitsAssert(c == 0, L"Class name error");

    NitsAssert(Tcscasecmp(cls->data[1]->classDecl->name, MI_T("B")) == 0, L"Class name error");
    MI_Value v;
    MI_Boolean exist;
    MI_Uint32 flag;
    MI_Char* refclsname;

    r = MI_Class_GetElement(cls->data[1], MI_T("a"), &v, &exist, NULL, &refclsname, NULL, &flag, NULL);
    NitsAssert( r==MI_RESULT_OK, L"get a property failed");
    NitsAssert(Tcscasecmp(refclsname, MI_T("A")) == 0, L"reference Class name error");

    r = MI_Class_GetElement(cls->data[1], MI_T("b"), &v, &exist, NULL, &refclsname, NULL, &flag, NULL);
    NitsAssert( r==MI_RESULT_OK, L"get b property failed");
    NitsAssert(Tcscasecmp(refclsname, MI_T("B")) == 0, L"reference Class name error");

    r = MI_Class_GetElement(cls->data[1], MI_T("C"), &v, &exist, NULL, &refclsname, NULL, &flag, NULL);
    NitsAssert( r==MI_RESULT_OK, L"get c property failed");
    NitsAssert(Tcscasecmp(refclsname, MI_T("C")) == 0, L"reference Class name error");

    r = MI_Class_GetElement(cls->data[1], MI_T("O"), &v, &exist, NULL, &refclsname, NULL, &flag, NULL);
    NitsAssert( r==MI_RESULT_OK, L"get o property failed");
    NitsAssert(refclsname == NULL, L"reference Class name error");

    r = MI_Class_GetElement(cls->data[1], MI_T("d"), &v, &exist, NULL, &refclsname, NULL, &flag, NULL);
    NitsAssert( r==MI_RESULT_OK, L"get d property failed");
    NitsAssert(Tcscasecmp(refclsname, MI_T("d")) == 0, L"reference Class name error");

    /* Validate method */
    MI_ParameterSet pset;
    r = MI_Class_GetMethod(cls->data[1], MI_T("testmethod"), NULL, &pset, NULL);
    NitsAssert( r==MI_RESULT_OK, L"get testmethod failed");
    MI_Type parameterType;
    MI_QualifierSet qualifierSet;
    MI_Uint32 index;
    r = MI_ParameterSet_GetParameter(&pset, MI_T("c"), &parameterType, &refclsname, &qualifierSet, &index);
    NitsAssert( r==MI_RESULT_OK, L"get parameter c failed");
    NitsAssert(Tcscasecmp(refclsname, MI_T("C")) == 0, L"reference Class name error");

    r = MI_ParameterSet_GetParameter(&pset, MI_T("e"), &parameterType, &refclsname, &qualifierSet, &index);
    NitsAssert( r==MI_RESULT_OK, L"get parameter c failed");
    NitsAssert(Tcscasecmp(refclsname, MI_T("E")) == 0, L"reference Class name error");

    r = MI_ParameterSet_GetParameter(&pset, MI_T("o"), &parameterType, &refclsname, &qualifierSet, &index);
    NitsAssert( r==MI_RESULT_OK, L"get parameter c failed");
    NitsAssert(refclsname == 0, L"reference Class name should be NULL");

    r = MI_ParameterSet_GetParameter(&pset, MI_T("f"), &parameterType, &refclsname, &qualifierSet, &index);
    NitsAssert( r==MI_RESULT_OK, L"get parameter c failed");
    NitsAssert(Tcscasecmp(refclsname, MI_T("F")) == 0, L"reference Class name error");

    MI_Deserializer_ReleaseClassArray(cls);
CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

NitsTest(TestInstance_Ref_InvalidReferencePropertyValue)
    char classmof[] =
        "class A"\
        "{ string k;"\
        "};"\
        "class B"\
        "{ A ref a;"\
        "};"\
        "instance of B as $b1"\
        "{a=NULL;};"\
        "instance of B as $b2"\
        "{ a=$b1;"\
        "};";
    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    MI_InstanceA *insta;
    MI_Instance *err = NULL;
    r = MI_Deserializer_DeserializeInstanceArray(
        &codecer.de, 0, NULL, NULL, (MI_Uint8*)classmof, sizeof(classmof), NULL, NULL, &insta, &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize should fail");
    NitsAssert( err != NULL, L"deserialize should get error");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, 69, MI_ERRORCATEGORY_SYNTAX_ERROR);
    MI_Instance_DeleteHelper(err);
CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

NitsTest(TestInstance_Ref_InvalidEmbeddedPropertyValue)
    char classmof[] =
        "class A"\
        "{ string k;"\
        "};"\
        "class B"\
        "{ [embeddedinstance(\"A\")]string a;"\
        "};"\
        "instance of B as $b1"\
        "{a=NULL;};"\
        "instance of B as $b2"\
        "{ a=$b1;"\
        "};";
    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    MI_InstanceA *insta;
    MI_Instance *err = NULL;
    r = MI_Deserializer_DeserializeInstanceArray(
        &codecer.de, 0, NULL, NULL, (MI_Uint8*)classmof, sizeof(classmof), NULL, NULL, &insta, &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize should fail");
    NitsAssert( err != NULL, L"deserialize should get error");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, 69, MI_ERRORCATEGORY_SYNTAX_ERROR);
    MI_Instance_DeleteHelper(err);
CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

NitsTest(TestInstance_Ref_InvalidEmbeddedArrayPropertyValue)
    char classmof[] =
        "class A"\
        "{ string k;"\
        "};"\
        "class B"\
        "{ [embeddedinstance(\"A\")]string a[];"\
        "};"\
        "instance of B as $b1"\
        "{a=NULL;};"\
        "instance of A as $a1"\
        "{k=\"1\";};"\
        "instance of B as $b2"\
        "{ a={$a1,$b1};"\
        "};";
    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
        goto CleanUp;
    MI_InstanceA *insta;
    MI_Instance *err = NULL;
    r = MI_Deserializer_DeserializeInstanceArray(
        &codecer.de, 0, NULL, NULL, (MI_Uint8*)classmof, sizeof(classmof), NULL, NULL, &insta, &err);
    NitsAssert( r==MI_RESULT_FAILED, L"deserialize should fail");
    NitsAssert( err != NULL, L"deserialize should get error");
    ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, 69, MI_ERRORCATEGORY_SYNTAX_ERROR);
    MI_Instance_DeleteHelper(err);
CleanUp:
    DeleteMofCodecer(&codecer);
NitsEndTest

#define INVALID_DT_MOF1 "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"99991301000000.012345+720\";};"
#define INVALID_DT_MOF2 "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"20000132000000.012345+720\";};"
#define INVALID_DT_MOF3 "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"20130229000000.012345+720\";};"
#define INVALID_DT_MOF4 "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"99991301000000.012345+720\";};"
#define INVALID_DT_MOF5 "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"21000229000000.012345+720\";};"
#define INVALID_DT_MOF6 "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"20000230000000.012345+720\";};"
#define INVALID_DT_MOF7 "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"20000229240000.012345+720\";};"
#define INVALID_DT_MOF8 "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"20000229006000.012345+720\";};"
#define INVALID_DT_MOF9 "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"20000229000060.012345+720\";};"
#define INVALID_DT_MOF10 "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"200002290000-1.012345+720\";};"
#define INVALID_DT_MOF11 "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"20000229000000.000000+1000\";};"
#define INVALID_DT_MOF12 "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"20000229000000.000000-1000\";};"
#define INVALID_DT_MOF13 "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"00000001240000.000000:000\";};"
#define INVALID_DT_MOF14 "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"00000001236000.000000:000\";};"
#define INVALID_DT_MOF15 "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"00000001235960.000000:000\";};"

#define VALID_DT_MOF1   "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"20000229000000.012345+720\";};"
#define VALID_DT_MOF2   "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"20000229000000.012345-720\";};"
#define VALID_DT_MOF3   "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"20080229000000.000000+000\";};"
#define VALID_DT_MOF4   "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"20080229235959.999999+900\";};"
#define VALID_DT_MOF5   "CLASS A{DATETIME P;}; INSTANCE OF A{P=\"20080229235959.999999-900\";};"

typedef struct _CLASSMOF2
{
    _Field_z_ const char* mof;
    MI_Uint32 len;
    MI_Uint32 errorcode;
}CLASSMOF2;

CLASSMOF2 g_invalidatetimemof[]={
    {INVALID_DT_MOF1, sizeof(INVALID_DT_MOF1) - 1, 70},
    {INVALID_DT_MOF2, sizeof(INVALID_DT_MOF2) - 1, 70},
    {INVALID_DT_MOF3, sizeof(INVALID_DT_MOF3) - 1, 70},
    {INVALID_DT_MOF4, sizeof(INVALID_DT_MOF4) - 1, 70},
    {INVALID_DT_MOF5, sizeof(INVALID_DT_MOF5) - 1, 70},
    {INVALID_DT_MOF6, sizeof(INVALID_DT_MOF6) - 1, 70},
    {INVALID_DT_MOF7, sizeof(INVALID_DT_MOF7) - 1, 70},
    {INVALID_DT_MOF8, sizeof(INVALID_DT_MOF8) - 1, 70},
    {INVALID_DT_MOF9, sizeof(INVALID_DT_MOF9) - 1, 70},
    {INVALID_DT_MOF10, sizeof(INVALID_DT_MOF10) - 1, 70},
    {INVALID_DT_MOF11, sizeof(INVALID_DT_MOF11) - 1, 45},
    {INVALID_DT_MOF12, sizeof(INVALID_DT_MOF12) - 1, 45},
    {INVALID_DT_MOF13, sizeof(INVALID_DT_MOF13) - 1, 70},
    {INVALID_DT_MOF14, sizeof(INVALID_DT_MOF14) - 1, 70},
    {INVALID_DT_MOF15, sizeof(INVALID_DT_MOF15) - 1, 70},
    {NULL, 0, 0},
};
CLASSMOF2 g_validatetimemof[]={
    {VALID_DT_MOF1, sizeof(VALID_DT_MOF1) - 1, 0},
    {VALID_DT_MOF2, sizeof(VALID_DT_MOF2) - 1, 0},
    {VALID_DT_MOF3, sizeof(VALID_DT_MOF3) - 1, 0},
    {VALID_DT_MOF4, sizeof(VALID_DT_MOF4) - 1, 0},
    {VALID_DT_MOF5, sizeof(VALID_DT_MOF5) - 1, 0},
    {NULL, 0, 0},
};

NitsTest(TestInstance_DatetimeValue)
    MI_Result r;
    MofCodecer codecer = {0};
    for (CLASSMOF2* p = g_invalidatetimemof; p->mof; p++)
    {
        r = CreateMofCodecer(&codecer);
        NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
        if (r != MI_RESULT_OK)
        {
            DeleteMofCodecer(&codecer);
            return;
        }
        MI_InstanceA *insta;
        MI_Instance *err = NULL;
        r = MI_Deserializer_DeserializeInstanceArray(
            &codecer.de, 0, NULL, NULL, (MI_Uint8*)p->mof, p->len, NULL, NULL, &insta, &err);
        NitsAssert( r==MI_RESULT_FAILED, L"deserialize failed");
        NitsAssert( err != NULL, L"deserialize failed");
        ValidateErrorInstance(err, MI_RESULT_TYPE_MOF_PARSER, p->errorcode, MI_ERRORCATEGORY_SYNTAX_ERROR);
        MI_Instance_DeleteHelper(err);
        DeleteMofCodecer(&codecer);
    }
    for (CLASSMOF2* p = g_validatetimemof; p->mof; p++)
    {
        r = CreateMofCodecer(&codecer);
        NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
        if (r != MI_RESULT_OK)
        {
            DeleteMofCodecer(&codecer);
            return;
        }
        MI_InstanceA *insta;
        MI_Instance *err = NULL;
        r = MI_Deserializer_DeserializeInstanceArray(
            &codecer.de, 0, NULL, NULL, (MI_Uint8*)p->mof, p->len, NULL, NULL, &insta, &err);
        NitsAssert( r==MI_RESULT_OK, L"deserialize failed");
        if (r != MI_RESULT_OK)
        {
            DeleteMofCodecer(&codecer);
            return;
        }
        NitsAssert( err == NULL, L"deserialize gets error instance");
        NitsAssert( insta->size == 1, L"deserialize should get 1 instance");
        MI_Deserializer_ReleaseInstanceArray(insta);
        DeleteMofCodecer(&codecer);
    }
NitsEndTest


NitsTest(TestClassArrayDeserializer_GetParentClass)
    char classmof[] = "class A {string P1; uint8 P2;};"
        "class B:A {Sint64 P3;};"
        "class C:B {};"
        "class D:C {Sint64 P5;};";

    MI_Result r;
    MofCodecer codecer = {0};
    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    MI_ClassA *ca;
    r = MI_Deserializer_DeserializeClassArray(&codecer.de, 0, &codecer.options, 0, (MI_Uint8*)classmof, sizeof(classmof), NULL, NULL, NULL, NULL, &ca, NULL);
    NitsAssert( r==MI_RESULT_OK, L"deserialize class mof failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    NitsAssert( ca->size == 4, L"deserialize class mof failed");

    int c = Tcscasecmp(ca->data[0]->classDecl->name, MI_T("A"));
    NitsAssert(c == 0, L"Class name error");

    c = Tcscasecmp(ca->data[1]->classDecl->name, MI_T("B"));
    NitsAssert(c == 0, L"Class name should be B");
    c = Tcscasecmp(ca->data[2]->classDecl->name, MI_T("C"));
    NitsAssert(c == 0, L"Class name should be C");
    c = Tcscasecmp(ca->data[3]->classDecl->name, MI_T("D"));
    NitsAssert(c == 0, L"Class name should be D");

    MI_Class *pb = NULL, *pc = NULL, *pd = NULL, *ppc = NULL, *ppd = NULL, *pppd = NULL;
    r = MI_Class_GetParentClass(ca->data[1], &pb);
    NitsAssert( r==MI_RESULT_OK, L"Get parent class of B failed");
    r = MI_Class_GetParentClass(ca->data[2], &pc);
    NitsAssert( r==MI_RESULT_OK, L"Get parent class of C failed");
    r = MI_Class_GetParentClass(ca->data[3], &pd);
    NitsAssert( r==MI_RESULT_OK, L"Get parent class of D failed");
    if (pc)
    {
        r = MI_Class_GetParentClass(pc, &ppc);
        NitsAssert( r==MI_RESULT_OK, L"Get parent of parent class of C failed");
    }
    if (pd)
    {
        r = MI_Class_GetParentClass(pd, &ppd);
        NitsAssert( r==MI_RESULT_OK, L"Get parent of parent class of D failed");
    }
    if (ppd)
    {
        r = MI_Class_GetParentClass(ppd, &pppd);
        NitsAssert( r==MI_RESULT_OK, L"Get parent of parent of parent class of D failed");
    }

    MI_Deserializer_ReleaseClassArray(ca);
    DeleteMofCodecer(&codecer);

    if (pb)
        NitsAssert(Tcscasecmp(pb->classDecl->name, MI_T("A")) == 0, L"Class name incorrect");
    if (pc)
        NitsAssert(Tcscasecmp(pc->classDecl->name, MI_T("B")) == 0, L"Class name incorrect");
    if (pd)
        NitsAssert(Tcscasecmp(pd->classDecl->name, MI_T("C")) == 0, L"Class name incorrect");
    if (ppc)
        NitsAssert(Tcscasecmp(ppc->classDecl->name, MI_T("A")) == 0, L"Class name incorrect");
    if (ppd)
        NitsAssert(Tcscasecmp(ppd->classDecl->name, MI_T("B")) == 0, L"Class name incorrect");
    if (pppd)
        NitsAssert(Tcscasecmp(pppd->classDecl->name, MI_T("A")) == 0, L"Class name incorrect");

    if (pb)
        MI_Class_Delete(pb);
    if (pc)
        MI_Class_Delete(pc);
    if (pd)
        MI_Class_Delete(pd);
    if (ppc)
        MI_Class_Delete(ppc);
    if (ppd)
        MI_Class_Delete(ppd);
    if (pppd)
        MI_Class_Delete(pppd);

NitsEndTest

NitsTest(TestInstance_EmptyArray_BLUEBUG_148688)
    char mof[] =
        "class A"\
        "{string key; string k[];"\
        "};"\
        "\n"\
        "instance of A as $x"\
        "{key=NULL;};" \
        "instance of A"\
        "{k={};};";

    MI_Result r;
    MofCodecer codecer = {0};

    r = CreateMofCodecer(&codecer);
    NitsAssert( r==MI_RESULT_OK, L"Create mof deserializer failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    MI_InstanceA *ia;
    r = MI_Deserializer_DeserializeInstanceArray(&codecer.de, 0, NULL, 0, (MI_Uint8*)mof, (MI_Uint32)sizeof(mof), NULL, NULL, &ia, NULL);
    NitsAssert( r==MI_RESULT_OK, L"deserialize instance mof failed");
    if (r != MI_RESULT_OK)
    {
        DeleteMofCodecer(&codecer);
        return;
    }
    _Analysis_assume_(ia != NULL);
    NitsAssert( ia->size == 2, L"deserialize instance mof failed");

    MI_Uint32 flag;
    MI_Value value;
    int c = Tcscasecmp(ia->data[0]->classDecl->name, MI_T("A"));
    NitsAssert(c == 0, L"Class name error");

    r = MI_Instance_GetElement(ia->data[0], MI_T("k"), NULL, NULL, &flag, NULL);
    NitsAssert( r == MI_RESULT_OK, L"Read 'k' from instance failed");
    NitsAssert( (flag &  MI_FLAG_NULL) == MI_FLAG_NULL, L"'k' should be NULL");

    c = Tcscasecmp(ia->data[1]->classDecl->name, MI_T("A"));
    NitsAssert(c == 0, L"Class name error");

    r = MI_Instance_GetElement(ia->data[1], MI_T("k"), &value, NULL, &flag, NULL);
    NitsAssert( r == MI_RESULT_OK, L"Read 'k' from instance failed");
    NitsAssert( value.stringa.data == 0, L"'k' data should not be NULL");
    NitsAssert( value.stringa.size == 0, L"'k' size should not be 0");

    if (ia) MI_Deserializer_ReleaseInstanceArray(ia);
    DeleteMofCodecer(&codecer);
NitsEndTest
