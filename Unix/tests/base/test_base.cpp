/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <vector>
#include <algorithm>
#include <ut/ut.h>
#include <base/base.h>
#include <base/buf.h>
#include <base/batch.h>
#include <pal/strings.h>
#include <base/paths.h>
#include <base/conf.h>
#include <pal/dir.h>
#include <base/log.h>
#include <pal/format.h>
#include <pal/file.h>
#include <pal/dir.h>
#include <base/strarr.h>
#include <base/omigetopt.h>
#include <pal/hashmap.h>
#include <base/miextras.h>
#include <base/base64.h>
#include "MSFT_AllTypes.h"
#include "MSFT_Process.h"
#include "Octet.h"
#include <base/ptrarray.h>
#include <base/naming.h>
#include <base/Strand.h>
#include <nits/base/nits.h>

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 20076)
#endif

using namespace std;
using namespace mi;

#if 0
# define ENABLE_PRINT
#endif

#if defined(_MSC_VER)
/* warning C6309: Argument '3' is null: this does not adhere to function specification of 'MI_Instance_AddElement' */
# pragma warning(disable : 6309)
#endif

extern "C" 
{
extern MI_SchemaDecl test_repos_classDecl;
}

static FILE* outStream = NULL;

static string srcdir;

NitsSetup(TestBaseSetup)
{
#if defined(ENABLE_PRINT)
    outStream = stdout;
#else
    outStream = File_Open(NULL_FILE, "w");
#endif
    srcdir = OMI_GetPath(ID_SRCDIR);
}
NitsEndSetup

NitsCleanup(TestBaseSetup)
{
#if defined(ENABLE_PRINT)
    outStream = NULL;
#else
    fclose(outStream);
    outStream = NULL;
#endif
    srcdir.clear();
}
NitsEndCleanup

static void MemTest(const char* data, char ch, size_t size)
{
    size_t i;

    for (i = 0; i < size; i++)
    {
        if (data[i] != ch)
            UT_ASSERT_FAILED_MSG("Memcheck failed");
    }
}

NitsTestWithSetup(TestAllocator1, TestBaseSetup)
{
    Batch a;
    char data[256];
    // make this member static, since pprefast does not like stack usage more 
    // than 16K
    static char* blocks[4096];
    const size_t N = sizeof(blocks) / sizeof(blocks[0]);
    size_t i;

    Batch_InitFromBuffer(&a, data, sizeof(data), BATCH_MAX_PAGES);

    for (i = 1; i < N; i++)
    {
        char* p = (char*)Batch_Get(&a, i);
        if(!TEST_ASSERT(p != NULL))
            goto End;
        memset(p, i % 256, i);
        blocks[i] = p;
    }

    // First chunk is 1 bytes as offset 0:
    TEST_ASSERT(data[0] == 1);

    // Second chunk is 2 bytes as offset 8:
    TEST_ASSERT(data[8+0] == 2);
    TEST_ASSERT(data[8+1] == 2);

    // Third chunk is 3 bytes as offset 16:
    TEST_ASSERT(data[16+0] == 3);
    TEST_ASSERT(data[16+1] == 3);

    // Fourth chunk is 4 bytes as offset 24:
    TEST_ASSERT(data[24+0] == 4);
    TEST_ASSERT(data[24+1] == 4);

    // Fifth chunk is 5 bytes as offset 32:
    TEST_ASSERT(data[32+0] == 5);
    TEST_ASSERT(data[32+1] == 5);

    for (i = 1; i < N; i++)
    {
        char* p = blocks[i];
        TEST_ASSERT(p != NULL);

        MemTest(p, i % 256, i);
    }
End:
    Batch_Destroy(&a);
}
NitsEndTest

NitsTestWithSetup(TestAllocator2, TestBaseSetup)
{
    Batch batch = BATCH_INITIALIZER;
    char* blocks[512];
    const size_t N = sizeof(blocks) / sizeof(blocks[0]);
    size_t i;

    for (i = 1; i < N; i++)
    {
        char* p = (char*)Batch_Get(&batch, i);
        if(!TEST_ASSERT(p != NULL))
            goto End;
        memset(p, i % 256, i);
        blocks[i] = p;
    }

    for (i = 1; i < N; i++)
    {
        char* p = blocks[i];
        TEST_ASSERT(p != NULL);

        MemTest(p, i % 256, i);
    }
End:
    Batch_Destroy(&batch);
    memset(&batch, 0, sizeof(batch));
}
NitsEndTest

NitsTestWithSetup(TestAllocator3, TestBaseSetup)
{
    Batch* batch;
    char* blocks[512];
    const size_t N = sizeof(blocks) / sizeof(blocks[0]);
    size_t i;

    batch = Batch_New(8);
    if(!TEST_ASSERT(batch != NULL))
        NitsReturn;

    for (i = 1; i < N; i++)
    {
        char* p = (char*)Batch_Get(batch, i);
        if(!TEST_ASSERT(p != NULL))
            goto End;

        memset(p, i % 256, i);
        blocks[i] = p;
    }

    for (i = 1; i < N; i++)
    {
        char* p = blocks[i];
        TEST_ASSERT(p != NULL);

        MemTest(p, i % 256, i);
    }
End:
    Batch_Delete(batch);
}
NitsEndTest

NitsTestWithSetup(TestGetName, TestBaseSetup)
{
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_BOOLEAN), PAL_T("BOOLEAN")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_UINT8), PAL_T("UINT8")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_SINT8), PAL_T("SINT8")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_UINT16), PAL_T("UINT16")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_SINT16), PAL_T("SINT16")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_UINT32), PAL_T("UINT32")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_SINT32), PAL_T("SINT32")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_UINT64), PAL_T("UINT64")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_SINT64), PAL_T("SINT64")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_REAL32), PAL_T("REAL32")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_REAL64), PAL_T("REAL64")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_CHAR16), PAL_T("CHAR16")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_DATETIME), PAL_T("DATETIME")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_STRING), PAL_T("STRING")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_REFERENCE), PAL_T("REFERENCE")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_INSTANCE), PAL_T("INSTANCE")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_BOOLEANA), PAL_T("BOOLEANA")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_UINT8A), PAL_T("UINT8A")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_SINT8A), PAL_T("SINT8A")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_UINT16A), PAL_T("UINT16A")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_SINT16A), PAL_T("SINT16A")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_UINT32A), PAL_T("UINT32A")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_SINT32A), PAL_T("SINT32A")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_UINT64A), PAL_T("UINT64A")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_SINT64A), PAL_T("SINT64A")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_REAL32A), PAL_T("REAL32A")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_REAL64A), PAL_T("REAL64A")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_CHAR16A), PAL_T("CHAR16A")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_DATETIMEA), PAL_T("DATETIMEA")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_STRINGA), PAL_T("STRINGA")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_REFERENCEA), PAL_T("REFERENCEA")) == 0);
    TEST_ASSERT(Tcscmp(Type_NameOf(MI_INSTANCEA), PAL_T("INSTANCEA")) == 0);
}
NitsEndTest

NitsTestWithSetup(TestGetSize, TestBaseSetup)
{
    TEST_ASSERT(Type_SizeOf(MI_BOOLEAN) == sizeof(MI_Boolean));
    TEST_ASSERT(Type_SizeOf(MI_UINT8) == sizeof(MI_Uint8));
    TEST_ASSERT(Type_SizeOf(MI_SINT8) == sizeof(MI_Sint8));
    TEST_ASSERT(Type_SizeOf(MI_UINT16) == sizeof(MI_Uint16));
    TEST_ASSERT(Type_SizeOf(MI_SINT16) == sizeof(MI_Sint16));
    TEST_ASSERT(Type_SizeOf(MI_UINT32) == sizeof(MI_Uint32));
    TEST_ASSERT(Type_SizeOf(MI_SINT32) == sizeof(MI_Sint32));
    TEST_ASSERT(Type_SizeOf(MI_UINT64) == sizeof(MI_Uint64));
    TEST_ASSERT(Type_SizeOf(MI_SINT64) == sizeof(MI_Sint64));
    TEST_ASSERT(Type_SizeOf(MI_REAL32) == sizeof(MI_Real32));
    TEST_ASSERT(Type_SizeOf(MI_REAL64) == sizeof(MI_Real64));
    TEST_ASSERT(Type_SizeOf(MI_CHAR16) == sizeof(MI_Char16));
    TEST_ASSERT(Type_SizeOf(MI_DATETIME) == sizeof(MI_Datetime));
    TEST_ASSERT(Type_SizeOf(MI_STRING) == sizeof(MI_String));
    TEST_ASSERT(Type_SizeOf(MI_REFERENCE) == sizeof(MI_Instance*));
    TEST_ASSERT(Type_SizeOf(MI_INSTANCE) == sizeof(MI_Instance*));
    TEST_ASSERT(Type_SizeOf(MI_BOOLEANA) == sizeof(MI_BooleanA));
    TEST_ASSERT(Type_SizeOf(MI_UINT8A) == sizeof(MI_Uint8A));
    TEST_ASSERT(Type_SizeOf(MI_SINT8A) == sizeof(MI_Sint8A));
    TEST_ASSERT(Type_SizeOf(MI_UINT16A) == sizeof(MI_Uint16A));
    TEST_ASSERT(Type_SizeOf(MI_SINT16A) == sizeof(MI_Sint16A));
    TEST_ASSERT(Type_SizeOf(MI_UINT32A) == sizeof(MI_Uint32A));
    TEST_ASSERT(Type_SizeOf(MI_SINT32A) == sizeof(MI_Sint32A));
    TEST_ASSERT(Type_SizeOf(MI_UINT64A) == sizeof(MI_Uint64A));
    TEST_ASSERT(Type_SizeOf(MI_SINT64A) == sizeof(MI_Sint64A));
    TEST_ASSERT(Type_SizeOf(MI_REAL32A) == sizeof(MI_Real32A));
    TEST_ASSERT(Type_SizeOf(MI_REAL64A) == sizeof(MI_Real64A));
    TEST_ASSERT(Type_SizeOf(MI_CHAR16A) == sizeof(MI_Char16A));
    TEST_ASSERT(Type_SizeOf(MI_DATETIMEA) == sizeof(MI_DatetimeA));
    TEST_ASSERT(Type_SizeOf(MI_STRINGA) == sizeof(MI_StringA));
    TEST_ASSERT(Type_SizeOf(MI_REFERENCEA) == sizeof(MI_ReferenceA));
    TEST_ASSERT(Type_SizeOf(MI_INSTANCEA) == sizeof(MI_InstanceA));
}
NitsEndTest

static MI_Instance* NewPerson(
    MI_Uint32 key,
    const ZChar* first,
    const ZChar* last,
    Batch* batch)
{
    MI_Value value;
    MI_Instance* inst;
    MI_Result r;
    const MI_ClassDecl* cd;
    
    /* Find class decl for MSFT_Person */
    cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Person"));
    TEST_ASSERT(cd != NULL);

    /* Create instance of MSFT_Person */
    r = Instance_New(&inst, cd, batch);
    TEST_ASSERT(r == MI_RESULT_OK);

    /* CIM_Person.Key */
    value.uint32 = key;
    r = MI_Instance_SetElement(inst, MI_T("Key"), &value, MI_UINT32, 0);
    TEST_ASSERT(r == MI_RESULT_OK);

    /* CIM_Person.First */
    value.string = (ZChar*)first;
    r = MI_Instance_SetElement(inst, MI_T("First"), &value, MI_STRING, 0);
    TEST_ASSERT(r == MI_RESULT_OK);

    /* CIM_Person.Last */
    value.string = (ZChar*)last;
    r = MI_Instance_SetElement(inst, MI_T("Last"), &value, MI_STRING, 0);
    TEST_ASSERT(r == MI_RESULT_OK);

    return inst;
}

NitsTestWithSetup(TestStringArray1, TestBaseSetup)
{
    Batch batch = BATCH_INITIALIZER;
    StringArray sa;
    MI_Result r;
    static const ZChar* data[] = 
    {
        MI_T("Monday"), 
        MI_T("Tuesday"),
        MI_T("Wednesday"),
        MI_T("Thursday"),
        MI_T("Friday"),
        MI_T("Saturday"),
        MI_T("Sunday"),
    };
    static const size_t size = MI_COUNT(data);
    size_t i;

    if(!TEST_ASSERT(StringArray_Init(&sa, size, &batch) == MI_RESULT_OK))
        goto Error;

    for (i = 0; i < size; i++)
    {
        r = StringArray_Add(&sa, data[i]);
        TEST_ASSERT(r == MI_RESULT_OK);
    }

    TEST_ASSERT(sa.size == size);
    r = StringArray_Add(&sa, MI_T("Never"));
    TEST_ASSERT(r == MI_RESULT_FAILED);

#if 0
    StringArray_Print(&sa, stdout);
#endif

    for (i = 0; i < size; i++)
    {
        TEST_ASSERT(Tcscasecmp(sa.data[i], data[i]) == 0);
    }

Error:
    Batch_Destroy(&batch);
}
NitsEndTest

NitsTestWithSetup(TestStringArray2, TestBaseSetup)
{
    Batch batch = BATCH_INITIALIZER;
    StringArray sa;
    static const size_t N = 12345;
    size_t i;

    if(!TEST_ASSERT(StringArray_Init(&sa, N, &batch) == MI_RESULT_OK))
        goto Error;

    for (i = 0; i < N; i++)
    {
        MI_Result r;
        ZChar buf[32];
        Stprintf(buf, MI_COUNT(buf), MI_T("%d"), (int)i);
        r = StringArray_Add(&sa, buf);
        if(!TEST_ASSERT(r == MI_RESULT_OK))
            goto Error;
    }

    TEST_ASSERT(sa.size == N);

    for (i = 0; i < N; i++)
    {
        ZChar buf[32];
        Stprintf(buf, MI_COUNT(buf), MI_T("%d"), (int)i);
        Tcscasecmp(sa.data[i], buf);
    }
Error:
    Batch_Destroy(&batch);
}
NitsEndTest

NitsTestWithSetup(TestMessages, TestBaseSetup)
{
    MI_Result r;
    MI_Instance* instanceName;
    GetInstanceReq* req;
    PostInstanceMsg* rsp;
    MI_Value value;
    MI_Uint64 operationId;
    StringArray propertySet;
    const MI_ClassDecl* cd;
    Batch* b = NULL;

    /* Set the operationId */
    operationId = 12345;

    /* Build GetInstance message */
    req = GetInstanceReq_New(operationId, BinaryProtocolFlag);
    if(!TEST_ASSERT(req))
        NitsReturn;

    /* Use the message's batch for all allocations */
    b = req->base.base.batch;
    TEST_ASSERT(b);

    /* Create an instance name */
    {
        cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, 
            PAL_T("MSFT_Person"));
        TEST_ASSERT(cd != NULL);

        r = Instance_New(&instanceName, cd, b);
        TEST_ASSERT(r == MI_RESULT_OK);

        value.string = (ZChar*)MI_T("CIM_Person");
        MI_Instance_SetElement(instanceName, MI_T("__CLASS"), &value, MI_STRING, 0);

        value.uint32 = 1234;
        MI_Instance_SetElement(instanceName, MI_T("Key"), &value, MI_UINT32, 0);
    }

    /* Build a property list */
    {
        StringArray_Init(&propertySet, 2, b);
        r = StringArray_Add(&propertySet, MI_T("First"));
        TEST_ASSERT(r == MI_RESULT_OK);
        r = StringArray_Add(&propertySet, MI_T("Last"));
        TEST_ASSERT(r == MI_RESULT_OK);
    }

    req->instanceName = instanceName;
    req->propertySet = &propertySet;

    GetInstanceReq_Print(req, outStream);

    /* Create response */
    rsp = PostInstanceMsg_New(operationId);
    if(!TEST_ASSERT(rsp))
        goto Error;
    rsp->instance = NewPerson(1, MI_T("George"), MI_T("Washington"), b);
    TEST_ASSERT(rsp);

    PostInstanceMsg_Print(rsp, outStream);
Error:
    /* Destroy instances */
    if(instanceName)
        MI_Instance_Delete(instanceName);
    if(rsp && rsp->instance)
        MI_Instance_Delete(rsp->instance);

    /* Destroy the messages */
    if(req)
        GetInstanceReq_Release(req);
    if(rsp)
        PostInstanceMsg_Release(rsp);
}
NitsEndTest

NitsTestWithSetup(TestMessages2, TestBaseSetup)
{
    EnumerateInstancesReq* req;
    MI_Uint64 operationId;
    StringArray propertySet;
    Batch* b = NULL;

    /* Set the operationId */
    operationId = 45678;

    /* EnumerateInstancesReq */
    req = EnumerateInstancesReq_New(operationId, BinaryProtocolFlag);
    if(!TEST_ASSERT(req))
        NitsReturn;

    /* Use the messages's batch for all allocations */
    b = req->base.base.batch;

    /* EnumerateInstancesReq.className */
    req->className = (ZChar*)Batch_Tcsdup(b, MI_T("CIM_Person"));

    if (!req->className)
    {
        TEST_ASSERT("Out of memory" && NULL);
        EnumerateInstancesReq_Release(req);
        NitsReturn;
    }

    /* EnumerateInstancesReq.deepInheritance */
    req->deepInheritance = MI_TRUE;

    /* EnumerateInstancesReq.propertySet */
    {
        MI_Result r;
        StringArray_Init(&propertySet, 3, b);
        r = StringArray_Add(&propertySet, MI_T("Key"));
        TEST_ASSERT(r == MI_RESULT_OK);
        r = StringArray_Add(&propertySet, MI_T("First"));
        TEST_ASSERT(r == MI_RESULT_OK);
        r = StringArray_Add(&propertySet, MI_T("Last"));
        TEST_ASSERT(r == MI_RESULT_OK);
        req->propertySet = &propertySet;
    }

    EnumerateInstancesReq_Print(req, outStream);

    /* Destroy the message */
    EnumerateInstancesReq_Release(req);
}
NitsEndTest

NitsTestWithSetup(TestStrings, TestBaseSetup)
{
    char buf[1024];
    size_t n;

    memset(buf, 0xFF, sizeof(buf));
    n = Strlcpy(buf, "abc", 8);
    TEST_ASSERT(strcmp(buf, "abc") == 0);
    TEST_ASSERT(n == 3);

    memset(buf, 0xFF, sizeof(buf));
    n = Strlcpy(buf, "abc", 3);
    TEST_ASSERT(strcmp(buf, "ab") == 0);
    TEST_ASSERT(n == 3);

    memset(buf, 0xFF, sizeof(buf));
    n = Strlcpy(buf, "", 1);
    TEST_ASSERT(strcmp(buf, "") == 0);
    TEST_ASSERT(n == 0);

    memset(buf, 0xFF, sizeof(buf));
    n = Strlcpy(buf, "a", 2);
    TEST_ASSERT(strcmp(buf, "a") == 0);
    TEST_ASSERT(n == 1);

    memset(buf, 0xFF, sizeof(buf));
    Strlcpy(buf, "aaa", 8);
    Strlcat(buf, "bbb", 8);
    n = Strlcat(buf, "ccc", 8);
    TEST_ASSERT(strcmp(buf, "aaabbbc") == 0);
    TEST_ASSERT(n == 3);

    n = Strlcat(buf, "ccddd", 10);
    TEST_ASSERT(strcmp(buf, "aaabbbccc") == 0);
    TEST_ASSERT(n == 5);
}
NitsEndTest

typedef struct _Elem
{
    struct _Elem* next;
    struct _Elem* prev;
    int num;
}
Elem;

NitsTestWithSetup(TestList, TestBaseSetup)
{
    Elem* head = NULL;
    Elem* tail = NULL;
    Elem* p;

    /* Insert some elements */
    {
        Elem* e = (Elem*)PAL_Malloc(sizeof(Elem));
        TEST_ASSERT(e != NULL);
        if(e == NULL)
            NitsReturn;
        e->num = 1;
        List_Prepend(
            (ListElem**)&head, (ListElem**)&tail, (ListElem*)e);
    }
    {
        Elem* e = (Elem*)PAL_Malloc(sizeof(Elem));
        TEST_ASSERT(e != NULL);
        if(e == NULL)
            NitsReturn;
        e->num = 2;
        List_Prepend(
            (ListElem**)&head, (ListElem**)&tail, (ListElem*)e);
    }
    {
        Elem* e = (Elem*)PAL_Malloc(sizeof(Elem));
        TEST_ASSERT(e != NULL);
        if(e == NULL)
            NitsReturn;
        e->num = 3;
        List_Append(
            (ListElem**)&head, (ListElem**)&tail, (ListElem*)e);
    }

    /* Test contents */
    {
        int i;

        for (i = 0, p = head; p; p = p->next, i++)
        {
            switch (i)
            {
                case 0:
                    TEST_ASSERT(p->num == 2);
                    break;
                case 1:
                    TEST_ASSERT(p->num == 1);
                    break;
                case 2:
                    TEST_ASSERT(p->num == 3);
                    break;
                default:
                    UT_ASSERT_FAILED_MSG("unexpected");
            }
        }
    }

    /* Remove head */
    {
        Elem* tmp = head;
        List_Remove(
            (ListElem**)&head, (ListElem**)&tail, (ListElem*)head);
        PAL_Free(tmp);
    }

    /* Test contents */
    {
        int i;

        for (i = 0, p = head; p; p = p->next, i++)
        {
            switch (i)
            {
                case 0:
                    TEST_ASSERT(p->num == 1);
                    break;
                case 1:
                    TEST_ASSERT(p->num == 3);
                    break;
                default:
                    UT_ASSERT_FAILED_MSG("unexpected");
            }
        }
    }

    /* Remove tail */
    {
        Elem* tmp = tail;
        List_Remove(
            (ListElem**)&head, (ListElem**)&tail, (ListElem*)tail);
        PAL_Free(tmp);
    }

#ifdef _PREFAST_
/* head is initialized at this point */
#pragma prefast (push)
#pragma prefast (disable: 6001)
#endif

    /* Test contents */
    {
        int i;

        for (i = 0, p = head; p; p = p->next, i++)
        {
            switch (i)
            {
                case 0:
                    TEST_ASSERT(p->num == 1);
                    break;
                default:
                    UT_ASSERT_FAILED_MSG("unexpected");
            }
        }
    }
#ifdef _PREFAST_
#pragma prefast (pop)
#endif


    TEST_ASSERT(head == tail);

    /* Remove final element */
    {
        Elem* tmp = head;
        List_Remove(
            (ListElem**)&head, (ListElem**)&tail, (ListElem*)head);
        PAL_Free(tmp);
    }

    TEST_ASSERT(head == tail);
    TEST_ASSERT(head == NULL);
    TEST_ASSERT(tail == NULL);
}
NitsEndTest

NitsTestWithSetup(TestFindClassDecl, TestBaseSetup)
{
    MI_ClassDecl* cd;
    MI_MethodDecl* md;

    cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Person"));
    TEST_ASSERT(cd != NULL);

    md = ClassDecl_FindMethodDecl(cd, PAL_T("NoSuchMethod"));
    TEST_ASSERT(md == NULL);
    cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("NoSuchClass"));
    TEST_ASSERT(cd == NULL);

    md = ClassDecl_FindMethodDecl(cd, PAL_T("NoSuchMethod"));
    TEST_ASSERT(md == NULL);

    md = ClassDecl_FindMethodDecl(0, 0);
    TEST_ASSERT(md == NULL);
}
NitsEndTest

static MI_Result AddString(
    MI_Instance* inst, 
    const ZChar* name, 
    const ZChar* str)
{
    MI_Value value;
    value.string = (ZChar*)str;

    return MI_Instance_AddElement(
        inst,
        name,
        &value,
        MI_STRING,
        0);
}

static MI_Instance* NewAllTypes(Batch* batch)
{
    MI_Instance* base;
    MSFT_AllTypes* inst;
    MI_ClassDecl* cd;
    MI_Result r;

    cd = SchemaDecl_FindClassDecl(
        &test_repos_classDecl, PAL_T("MSFT_AllTypes"));
    TEST_ASSERT(cd != NULL);

    r = Instance_New(&base, cd, batch);
    if(!TEST_ASSERT(r == MI_RESULT_OK))
        return NULL;
    inst = (MSFT_AllTypes*)base;

    /* Key*/
#if 0
    r = Instance_SetElementFromString(base, PAL_T("Key"), PAL_T("1234"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Key.exists == 1);
    TEST_ASSERT(inst->Key.value == 1234);
#endif

    /* BooleanValue */
    r = Instance_SetElementFromString(base, PAL_T("BooleanValue"), PAL_T("TRUE"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->BooleanValue.exists == 1);
    TEST_ASSERT(inst->BooleanValue.value == 1);

    /* BooleanValue */
    r = Instance_SetElementFromString(base, PAL_T("BooleanValue"), PAL_T("FALSE"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->BooleanValue.exists == 1);
    TEST_ASSERT(inst->BooleanValue.value == 0);

    /* Uint8Value */
    r = Instance_SetElementFromString(base, PAL_T("Uint8Value"), PAL_T("8"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Uint8Value.exists == 1);
    TEST_ASSERT(inst->Uint8Value.value == 8);

    /* Sint8Value */
    r = Instance_SetElementFromString(base, PAL_T("Sint8Value"), PAL_T("-8"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Sint8Value.exists == 1);
    TEST_ASSERT(inst->Sint8Value.value == -8);

    /* Uint16Value */
    r = Instance_SetElementFromString(base, PAL_T("Uint16Value"), PAL_T("16"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Uint16Value.exists == 1);
    TEST_ASSERT(inst->Uint16Value.value == 16);

    /* Sint16Value */
    r = Instance_SetElementFromString(base, PAL_T("Sint16Value"), PAL_T("-16"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Sint16Value.exists == 1);
    TEST_ASSERT(inst->Sint16Value.value == -16);

    /* Uint32Value */
    r = Instance_SetElementFromString(base, PAL_T("Uint32Value"), PAL_T("32"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Uint32Value.exists == 1);
    TEST_ASSERT(inst->Uint32Value.value == 32);

    /* Sint32Value */
    r = Instance_SetElementFromString(base, PAL_T("Sint32Value"), PAL_T("-32"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Sint32Value.exists == 1);
    TEST_ASSERT(inst->Sint32Value.value == -32);

    /* Uint64Value */
    r = Instance_SetElementFromString(base, PAL_T("Uint64Value"), PAL_T("64"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Uint64Value.exists == 1);
    TEST_ASSERT(inst->Uint64Value.value == 64);

    /* Sint64Value */
    r = Instance_SetElementFromString(base, PAL_T("Sint64Value"), PAL_T("-64"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Sint64Value.exists == 1);
    TEST_ASSERT(inst->Sint64Value.value == -64);

    /* Real32Value */
    r = Instance_SetElementFromString(base, PAL_T("Real32Value"), PAL_T("32.32"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Real32Value.exists == 1);
    TEST_ASSERT(inst->Real32Value.value > 32 && inst->Real32Value.value < 33);

    /* Real64Value */
    r = Instance_SetElementFromString(base, PAL_T("Real64Value"), PAL_T("64.64"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Real64Value.exists == 1);
    TEST_ASSERT(inst->Real64Value.value > 64 && inst->Real64Value.value < 65);

    /* DatetimeValue */
    r = Instance_SetElementFromString(base, PAL_T("TimestampValue"), 
        PAL_T("20051225120000.123456-360"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->TimestampValue.exists == 1);

    /* Char16Value */
    r = Instance_SetElementFromString(base, PAL_T("Char16Value"), PAL_T("1234"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Char16Value.exists == 1);
    TEST_ASSERT(inst->Char16Value.value == 1234);

    /* DatetimeValue */
    r = Instance_SetElementFromString(base, PAL_T("IntervalValue"), 
        PAL_T("12345678010101.123456:000"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->IntervalValue.exists == 1);

    /* StringValue */
    r = Instance_SetElementFromString(base, PAL_T("StringValue"), PAL_T("Hello"), 0);
    if(TEST_ASSERT(r == MI_RESULT_OK))
    {
        TEST_ASSERT(inst->StringValue.exists == 1);
        TEST_ASSERT(Tcscmp(inst->StringValue.value, PAL_T("Hello")) == 0);
    }

    /* Uint32Array */
    {
        MI_Uint32 data[] = { 10, 20, 30 };
        MI_Value value;
        value.uint32a.data = data;
        value.uint32a.size = MI_COUNT(data);
        r = MI_Instance_SetElement(base, PAL_T("Uint32Array"), &value, MI_UINT32A, 0);
        TEST_ASSERT(r == MI_RESULT_OK);
        TEST_ASSERT(inst->Uint32Array.value.data[0] == 10);
        TEST_ASSERT(inst->Uint32Array.value.data[1] == 20);
        TEST_ASSERT(inst->Uint32Array.value.data[2] == 30);
    }

    /* Uint16Array */
    {
        MI_Uint16 data[1];
        MI_Value value;
        value.uint16a.data = data;
        value.uint16a.size = 0;
        r = MI_Instance_SetElement(base, PAL_T("Uint16Array"), &value, MI_UINT16A, 0);
        TEST_ASSERT(r == MI_RESULT_OK);
        TEST_ASSERT(inst->Uint16Array.exists);
    }

    /* StringArray */
    {
        ZChar* data[] = { (ZChar*)PAL_T("RED"), (ZChar*)PAL_T("GREEN"), (ZChar*)PAL_T("BLUE") };
        MI_Value value;
        value.stringa.data = data;
        value.stringa.size = MI_COUNT(data);
        r = MI_Instance_SetElement(base, PAL_T("StringArray"), &value, MI_STRINGA, 0);
        TEST_ASSERT(r == MI_RESULT_OK);
        TEST_ASSERT(Tcscmp(inst->StringArray.value.data[0], PAL_T("RED")) == 0);
        TEST_ASSERT(Tcscmp(inst->StringArray.value.data[1], PAL_T("GREEN")) == 0);
        TEST_ASSERT(Tcscmp(inst->StringArray.value.data[2], PAL_T("BLUE")) == 0);
    }

    return base;
}

NitsTestWithSetup(TestAllTypes, TestBaseSetup)
{
    MI_Instance* base;
    MSFT_AllTypes* inst;
    MI_ClassDecl* cd;
    MI_Result r;
    FILE* os;
    Batch batch = BATCH_INITIALIZER;

    cd = SchemaDecl_FindClassDecl(
        &test_repos_classDecl, PAL_T("MSFT_AllTypes"));
    TEST_ASSERT(cd != NULL);

    r = Instance_New(&base, cd, &batch);
    if(!TEST_ASSERT(r == MI_RESULT_OK))
        NitsReturn;
    inst = (MSFT_AllTypes*)base;

    /* BooleanValue */
    r = Instance_SetElementFromString(base, PAL_T("BooleanValue"), PAL_T("TRUE"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);   
    TEST_ASSERT(inst->BooleanValue.exists == 1);
    TEST_ASSERT(inst->BooleanValue.value == 1);    

    /* BooleanValue */
    r = Instance_SetElementFromString(base, PAL_T("BooleanValue"), PAL_T("FALSE"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->BooleanValue.exists == 1);
    TEST_ASSERT(inst->BooleanValue.value == 0);

    /* Uint8Value */
    r = Instance_SetElementFromString(base, PAL_T("Uint8Value"), PAL_T("8"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Uint8Value.exists == 1);
    TEST_ASSERT(inst->Uint8Value.value == 8);

    /* Sint8Value */
    r = Instance_SetElementFromString(base, PAL_T("Sint8Value"), PAL_T("-8"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Sint8Value.exists == 1);
    TEST_ASSERT(inst->Sint8Value.value == -8);

    /* Uint16Value */
    r = Instance_SetElementFromString(base, PAL_T("Uint16Value"), PAL_T("16"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Uint16Value.exists == 1);
    TEST_ASSERT(inst->Uint16Value.value == 16);

    /* Sint16Value */
    r = Instance_SetElementFromString(base, PAL_T("Sint16Value"), PAL_T("-16"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Sint16Value.exists == 1);
    TEST_ASSERT(inst->Sint16Value.value == -16);

    /* Uint32Value */
    r = Instance_SetElementFromString(base, PAL_T("Uint32Value"), PAL_T("32"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Uint32Value.exists == 1);
    TEST_ASSERT(inst->Uint32Value.value == 32);

    /* Sint32Value */
    r = Instance_SetElementFromString(base, PAL_T("Sint32Value"), PAL_T("-32"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Sint32Value.exists == 1);
    TEST_ASSERT(inst->Sint32Value.value == -32);

    /* Uint64Value */
    r = Instance_SetElementFromString(base, PAL_T("Uint64Value"), PAL_T("64"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Uint64Value.exists == 1);
    TEST_ASSERT(inst->Uint64Value.value == 64);

    /* Sint64Value */
    r = Instance_SetElementFromString(base, PAL_T("Sint64Value"), PAL_T("-64"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Sint64Value.exists == 1);
    TEST_ASSERT(inst->Sint64Value.value == -64);

    /* Real32Value */
    r = Instance_SetElementFromString(base, PAL_T("Real32Value"), PAL_T("32.32"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Real32Value.exists == 1);
    TEST_ASSERT(inst->Real32Value.value > 32 && inst->Real32Value.value < 33);

    /* Real64Value */
    r = Instance_SetElementFromString(base, PAL_T("Real64Value"), PAL_T("64.64"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Real64Value.exists == 1);
    TEST_ASSERT(inst->Real64Value.value > 64 && inst->Real64Value.value < 65);

    /* DatetimeValue */
    r = Instance_SetElementFromString(base, PAL_T("TimestampValue"), 
        PAL_T("20051225120000.123456-360"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->TimestampValue.exists == 1);

    /* Char16Value */
    r = Instance_SetElementFromString(base, PAL_T("Char16Value"), PAL_T("1234"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->Char16Value.exists == 1);
    TEST_ASSERT(inst->Char16Value.value == 1234);

    /* DatetimeValue */
    r = Instance_SetElementFromString(base, PAL_T("IntervalValue"), 
        PAL_T("12345678010101.123456:000"), 0);
    TEST_ASSERT(r == MI_RESULT_OK);
    TEST_ASSERT(inst->IntervalValue.exists == 1);

    /* StringValue */
    r = Instance_SetElementFromString(base, PAL_T("StringValue"), PAL_T("Hello"), 0);
    if(TEST_ASSERT(r == MI_RESULT_OK))
    {
        TEST_ASSERT(inst->StringValue.exists == 1);
        TEST_ASSERT(Tcscmp(inst->StringValue.value, PAL_T("Hello")) == 0);
    }

    /* Uint32Array */
    {
        MI_Uint32 data[] = { 10, 20, 30 };
        MI_Value value;
        value.uint32a.data = data;
        value.uint32a.size = MI_COUNT(data);
        r = MI_Instance_SetElement(base, PAL_T("Uint32Array"), &value, MI_UINT32A, 0);
        TEST_ASSERT(r == MI_RESULT_OK);
        TEST_ASSERT(inst->Uint32Array.value.data[0] == 10);
        TEST_ASSERT(inst->Uint32Array.value.data[1] == 20);
        TEST_ASSERT(inst->Uint32Array.value.data[2] == 30);
    }

    /* StringArray */
    {
        ZChar* data[] = { (ZChar*)PAL_T("RED"), (ZChar*)PAL_T("GREEN"), (ZChar*)PAL_T("BLUE") };
        MI_Value value;
        value.stringa.data = data;
        value.stringa.size = MI_COUNT(data);
        r = MI_Instance_SetElement(base, PAL_T("StringArray"), &value, MI_STRINGA, 0);
        TEST_ASSERT(r == MI_RESULT_OK);
        TEST_ASSERT(Tcscmp(inst->StringArray.value.data[0], PAL_T("RED")) == 0);
        TEST_ASSERT(Tcscmp(inst->StringArray.value.data[1], PAL_T("GREEN")) == 0);
        TEST_ASSERT(Tcscmp(inst->StringArray.value.data[2], PAL_T("BLUE")) == 0);
    }

    /* Print */
    os = outStream;
    TEST_ASSERT(os);
    MI_Instance_Print(base, os, 0);

    /* Convert */
    {
        MSFT_AllTypes conv;
        memset(&conv, 0, sizeof(MSFT_AllTypes));
        r = Instance_InitConvert(
            (MI_Instance*)&conv, 
            cd, 
            base, 
            MI_FALSE, /* Keys only */
            MI_FALSE, /* allow-keyless */
            MI_FALSE, /* copy */
            &batch, 0);
        TEST_ASSERT(r == MI_RESULT_OK);
        if(r != MI_RESULT_OK)
            NitsReturn;
        MI_Instance_Destruct((MI_Instance*)&conv);
    }

    /* Convert */
    {
        MSFT_AllTypes conv;
        memset(&conv, 0, sizeof(MSFT_AllTypes));
        r = Instance_InitConvert(
            (MI_Instance*)&conv, 
            cd, 
            base, 
            MI_FALSE,  /* Keys only */
            MI_FALSE, /* allow-keyless */
            MI_TRUE, /* copy */
            &batch, 0);
        TEST_ASSERT(r == MI_RESULT_OK);
        if(r != MI_RESULT_OK)
            NitsReturn;
        MI_Instance_Destruct((MI_Instance*)&conv);
    }

    {
        MI_Instance* dinst = NULL;
        MSFT_AllTypes sinst;
        memset(&sinst, 0, sizeof(sinst));

        /* Create a dynamic instance will all string properties */
        r = Instance_NewDynamic(&dinst, PAL_T("MSFT_AllTypes"), MI_FLAG_CLASS,
            &batch);
        TEST_ASSERT(r == MI_RESULT_OK);
        if(TEST_ASSERT(dinst != NULL))
        {
            r = AddString(dinst, PAL_T("Key"), PAL_T("999"));
            TEST_ASSERT(r == MI_RESULT_OK);
            r = AddString(dinst, PAL_T("BooleanValue"), PAL_T("FALSE"));
            TEST_ASSERT(r == MI_RESULT_OK);
            r = AddString(dinst, PAL_T("Uint8Value"), PAL_T("8"));
            TEST_ASSERT(r == MI_RESULT_OK);
            r = AddString(dinst, PAL_T("Sint8Value"), PAL_T("-8"));
            TEST_ASSERT(r == MI_RESULT_OK);
            r = AddString(dinst, PAL_T("Uint16Value"), PAL_T("16"));
            TEST_ASSERT(r == MI_RESULT_OK);
            r = AddString(dinst, PAL_T("Sint16Value"), PAL_T("-16"));
            TEST_ASSERT(r == MI_RESULT_OK);
            r = AddString(dinst, PAL_T("Uint32Value"), PAL_T("32"));
            TEST_ASSERT(r == MI_RESULT_OK);
            r = AddString(dinst, PAL_T("Sint32Value"), PAL_T("-32"));
            TEST_ASSERT(r == MI_RESULT_OK);
            r = AddString(dinst, PAL_T("Uint64Value"), PAL_T("64"));
            TEST_ASSERT(r == MI_RESULT_OK);
            r = AddString(dinst, PAL_T("Sint64Value"), PAL_T("-64"));
            TEST_ASSERT(r == MI_RESULT_OK);
            r = AddString(dinst, PAL_T("Real32Value"), PAL_T("32.32"));
            TEST_ASSERT(r == MI_RESULT_OK);
            r = AddString(dinst, PAL_T("Real64Value"), PAL_T("64.64"));
            TEST_ASSERT(r == MI_RESULT_OK);
            r = AddString(dinst, PAL_T("TimestampValue"), 
                PAL_T("20051225120000.123456-360"));
            TEST_ASSERT(r == MI_RESULT_OK);
            r = AddString(dinst, PAL_T("Char16Value"), PAL_T("1234"));
            TEST_ASSERT(r == MI_RESULT_OK);
            r = AddString(dinst, PAL_T("IntervalValue"), 
                PAL_T("12345678010101.123456:000"));
            TEST_ASSERT(r == MI_RESULT_OK);
            r = AddString(dinst, PAL_T("StringValue"), PAL_T("Hello"));
            TEST_ASSERT(r == MI_RESULT_OK);

    #if 0
            MI_Instance_Print(dinst, stdout, 0);
    #endif
            /* Convert to static instance */
            r = Instance_InitConvert(
                (MI_Instance*)&sinst, 
                cd, 
                dinst, 
                MI_FALSE, /* Keys only */
                MI_FALSE, /* allow-keyless */
                MI_TRUE,  /* copy */
                &batch, 0);
            TEST_ASSERT(r == MI_RESULT_OK);        
    #if 0
            MI_Instance_Print(&sinst.__instance, stdout, 0);
    #endif

            TEST_ASSERT(sinst.BooleanValue.exists == 1);
            TEST_ASSERT(sinst.BooleanValue.value == 0);
            TEST_ASSERT(sinst.Uint8Value.exists == 1);
            TEST_ASSERT(sinst.Uint8Value.value == 8);
            TEST_ASSERT(sinst.Sint8Value.exists == 1);
            TEST_ASSERT(sinst.Sint8Value.value == -8);
            TEST_ASSERT(sinst.Uint16Value.exists == 1);
            TEST_ASSERT(sinst.Uint16Value.value == 16);
            TEST_ASSERT(sinst.Sint16Value.exists == 1);
            TEST_ASSERT(sinst.Sint16Value.value == -16);
            TEST_ASSERT(sinst.Uint32Value.exists == 1);
            TEST_ASSERT(sinst.Uint32Value.value == 32);
            TEST_ASSERT(sinst.Sint32Value.exists == 1);
            TEST_ASSERT(sinst.Sint32Value.value == -32);
            TEST_ASSERT(sinst.Uint64Value.exists == 1);
            TEST_ASSERT(sinst.Uint64Value.value == 64);
            TEST_ASSERT(sinst.Sint64Value.exists == 1);
            TEST_ASSERT(sinst.Sint64Value.value == -64);
            TEST_ASSERT(sinst.Real32Value.exists == 1);
            TEST_ASSERT(sinst.Real32Value.value > 32 && sinst.Real32Value.value < 33);
            TEST_ASSERT(sinst.Real64Value.exists == 1);
            TEST_ASSERT(sinst.Real64Value.value > 64 && sinst.Real64Value.value < 65);
            TEST_ASSERT(sinst.TimestampValue.exists == 1);
            TEST_ASSERT(sinst.Char16Value.exists == 1);
            TEST_ASSERT(sinst.Char16Value.value == 1234);
            TEST_ASSERT(sinst.IntervalValue.exists == 1);
            TEST_ASSERT(sinst.StringValue.exists == 1);
            TEST_ASSERT((sinst.StringValue.value != NULL) && Tcscmp(sinst.StringValue.value, PAL_T("Hello")) == 0);

            MI_Instance_Destruct((MI_Instance*)&sinst);
            MI_Instance_Delete(dinst);
        }
    }

    MI_Instance_Delete(base);

    Batch_Destroy(&batch);
}
NitsEndTest

#if 0
static bool Test(MI_Result r, const ZChar* str)
{
    return Tcscmp(Result_ToString(r), str) == 0;
}
#endif

#if 0
NitsTestWithSetup(TestLib1, TestBaseSetup)
{
    char path[MAX_PATH];

    Lib_Format(path, NULL, "PersonProvider");
#if defined(CONFIG_OS_LINUX)
    TEST_ASSERT(strcmp(path, "libPersonProvider."CONFIG_SHLIBEXT) == 0);
#elif defined(_MSC_VER)
    TEST_ASSERT(strcmp(path, "PersonProvider.dll") == 0);
#endif
}
NitsEndTest

NitsTestWithSetup(TestLib2, TestBaseSetup)
{
#define DIRNAME "../" CONFIG_LIBDIR
    char path[MAX_PATH];
    Shlib* handle;
    void* sym;
    MI_Result r;

    /* Format path */
    Lib_Format(path, DIRNAME, "PersonProvider");
#if defined(CONFIG_OS_LINUX)
    TEST_ASSERT(strcmp(path, DIRNAME "/libPersonProvider."CONFIG_SHLIBEXT) == 0);
#elif defined(_MSC_VER)
    TEST_ASSERT(strcmp(path, DIRNAME "/PersonProvider.dll") == 0);
#endif

    /* Load library */
    handle = Shlib_Open(path);

    if(!handle)
    {
        handle = Shlib_Open("PersonProvider");
    }

    TEST_ASSERT(handle != NULL);

    /* Get 'MI_Main' symbol */
    sym = Shlib_Sym(handle, "MI_Main");
    TEST_ASSERT(sym != NULL);

    /* Close the library */
    r = Shlib_Close(handle);
    TEST_ASSERT(r == MI_RESULT_OK);
}
NitsEndTest
#endif

NitsTestWithSetup(TestInstances, TestBaseSetup)
{
    MI_Result r;
    MI_Instance* inst;
    MI_Value value;
    const MI_ClassDecl* cd;
    Batch batch = BATCH_INITIALIZER;
    
    /* Find class decl */
    cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));
    TEST_ASSERT(cd != NULL);

    /* Create instance of MSFT_Numbers */
    r = Instance_New(&inst, cd, &batch);
    TEST_ASSERT(r == MI_RESULT_OK);

    /* CIM_Person.Key */
    value.uint64 = 1234;
    r = MI_Instance_SetElement(inst, MI_T("WorkingSetSize"), &value, MI_UINT64, 0);
    TEST_ASSERT(r == MI_RESULT_OK);

    /* Check value */
    for (size_t i = 0; i < 1000000; i++)
    {
        MI_Value v;
        MI_Type t;
        MI_Uint32 f;
        r = MI_Instance_GetElement(inst, MI_T("WorkingSetSize"), &v, &t, &f, 0);
        TEST_ASSERT(r == MI_RESULT_OK);
        TEST_ASSERT(v.uint64 == 1234);
        TEST_ASSERT(t == MI_UINT64);
        TEST_ASSERT(!(f & MI_FLAG_NULL));
    }

    MI_Instance_Delete(inst);
    Batch_Destroy(&batch);
}
NitsEndTest

NitsTestWithSetup(TestDynamicInstances, TestBaseSetup)
{
    MI_Instance* inst = NULL;
    MI_Instance* clone = NULL;
    MI_Result r;
    MI_Value v;
    Batch batch = BATCH_INITIALIZER;
    Batch* b = &batch;

    r = Instance_NewDynamic(&inst, PAL_T("MSFT_Person"), MI_FLAG_CLASS, b);
    if(!TEST_ASSERT(r == MI_RESULT_OK))
        goto Error;

    v.uint32 = 1;
    r = MI_Instance_AddElement(inst, PAL_T("Key"), &v, MI_UINT32, MI_FLAG_KEY);
    TEST_ASSERT(r == MI_RESULT_OK);

    v.string = (ZChar*)PAL_T("George");
    r = MI_Instance_AddElement(inst, PAL_T("First"), &v, MI_STRING, 0);
    TEST_ASSERT(r == MI_RESULT_OK);

    v.string = (ZChar*)PAL_T("Washington");
    r = MI_Instance_AddElement(inst, PAL_T("Last"), &v, MI_STRING, 0);
    TEST_ASSERT(r == MI_RESULT_OK);

    /* Check "Key" */
    {
        MI_Type t;
        MI_Uint32 f;
        r = MI_Instance_GetElement(inst, PAL_T("Key"), &v, &t, &f, 0);
        TEST_ASSERT(r == MI_RESULT_OK);
        TEST_ASSERT(v.uint32 == 1);
        TEST_ASSERT(t == MI_UINT32);
        TEST_ASSERT(!(f & MI_FLAG_NULL));
    }

    /* Check "First" */
    {
        MI_Type t;
        MI_Uint32 f;
        r = MI_Instance_GetElement(inst, PAL_T("First"), &v, &t, &f, 0);
        TEST_ASSERT(r == MI_RESULT_OK);
        TEST_ASSERT(Tcscmp(v.string, PAL_T("George")) == 0);
        TEST_ASSERT(t == MI_STRING);
        TEST_ASSERT(!(f & MI_FLAG_NULL));
    }

    /* Check "Last" */
    {
        MI_Type t;
        MI_Uint32 f;
        r = MI_Instance_GetElement(inst, PAL_T("Last"), &v, &t, &f, 0);
        TEST_ASSERT(r == MI_RESULT_OK);
        TEST_ASSERT(Tcscmp(v.string, PAL_T("Washington")) == 0);
        TEST_ASSERT(t == MI_STRING);
        TEST_ASSERT(!(f & MI_FLAG_NULL));
    }

#if 0
    MI_Instance_Print(inst, stdout, 0);
#endif

    // Test cloning.
    
    r = MI_Instance_Clone(inst, &clone);
    if(!TEST_ASSERT(r == MI_RESULT_OK))
        goto Error;

#if 0
    MI_Instance_Print(clone, stdout, 0);
#endif

    /* Check "Key" */
    {
        MI_Type t;
        MI_Uint32 f;
        r = MI_Instance_GetElement(clone, PAL_T("Key"), &v, &t, &f, 0);
        TEST_ASSERT(r == MI_RESULT_OK);
        TEST_ASSERT(v.uint32 == 1);
        TEST_ASSERT(t == MI_UINT32);
        TEST_ASSERT(!(f & MI_FLAG_NULL));
    }

    /* Check "First" */
    {
        MI_Type t;
        MI_Uint32 f;
        r = MI_Instance_GetElement(clone, PAL_T("First"), &v, &t, &f, 0);
        TEST_ASSERT(r == MI_RESULT_OK);
        TEST_ASSERT(Tcscmp(v.string, PAL_T("George")) == 0);
        TEST_ASSERT(t == MI_STRING);
        TEST_ASSERT(!(f & MI_FLAG_NULL));
    }

    /* Check "Last" */
    {
        MI_Type t;
        MI_Uint32 f;
        r = MI_Instance_GetElement(clone, PAL_T("Last"), &v, &t, &f, 0);
        TEST_ASSERT(r == MI_RESULT_OK);
        TEST_ASSERT(Tcscmp(v.string, PAL_T("Washington")) == 0);
        TEST_ASSERT(t == MI_STRING);
        TEST_ASSERT(!(f & MI_FLAG_NULL));
    }


    /* Pack/unpack the instance */
    {
        Buf buf = BUF_INITIALIZER;
        MI_Instance* newInst;

        if(!TEST_ASSERT(Buf_Init(&buf, 4096) == MI_RESULT_OK))
            goto Error;

        /* Pack */
        r = Instance_Pack(inst, MI_FALSE, NULL, NULL, &buf);
        TEST_ASSERT(r == MI_RESULT_OK);

        /* Unpack */
        r = Instance_Unpack(&newInst, &buf, b, MI_FALSE);
        TEST_ASSERT(r == MI_RESULT_OK);

#if 0
        MI_Instance_Print(newInst, stdout, 0);
#endif

        MI_Instance_Delete(newInst);
        Buf_Destroy(&buf);
    }


    // Add many properties:
    for (size_t i = 0; i < 1000; i++)
    {
        ZChar buf[32];
        Stprintf(buf, MI_COUNT(buf), PAL_T("P%d"), (int)i);
        v.string = (ZChar*)PAL_T("Junk");
        r = MI_Instance_AddElement(inst, buf, &v, MI_STRING, 0);
        TEST_ASSERT(r == MI_RESULT_OK);
    }

    // Test basd name:
    r = MI_Instance_AddElement(inst, PAL_T(""), NULL, MI_UINT32, 0);
    TEST_ASSERT(r == MI_RESULT_INVALID_PARAMETER);

    // Test reference array:
    {
        MI_Instance* data[2];

        for (size_t i = 0; i < 2; i++)
        {
            MI_Instance* tmp = NULL;
            r = MI_Instance_Clone(inst, &tmp);
            TEST_ASSERT(r == MI_RESULT_OK);
            TEST_ASSERT(tmp != NULL);
            data[i] = tmp;
        }

        v.instancea.data = data;
        v.instancea.size = 2;
        r = MI_Instance_AddElement(inst, PAL_T("RefArray"), &v, MI_REFERENCEA, 0);
        TEST_ASSERT(r == MI_RESULT_OK);

        for (size_t i = 0; i < 2; i++)
            MI_Instance_Delete(data[i]);
    }

    MI_Instance_Print(inst, outStream, 0);

    // Clone again
    {
        MI_Instance* tmp = NULL;
        r = MI_Instance_Clone(inst, &tmp);
        TEST_ASSERT(r == MI_RESULT_OK);
        MI_Instance_Delete(tmp);
    }

Error:
    if(clone)    
        MI_Instance_Delete(clone);
    if(inst)
        MI_Instance_Delete(inst);
    if(b)
        Batch_Destroy(b);
}
NitsEndTest

/*
**==============================================================================
**
** TestBuf()
**
**     This test excercises the Buf implementation. It packs and unpacks
**     integer values of lengths 8-bit, 16-bit, 32-bit, and 64-bit. The values
**     and the lengths are selected randomly. The unpacked values are compared
**     with the original packed values (the original values are save in a 
**     vector).
**
**==============================================================================
*/
NitsTestWithSetup(TestBuf, TestBaseSetup)
{
    Buf b;
    vector<MI_Uint8> buf8;
    vector<MI_Uint16> buf16;
    vector<MI_Uint32> buf32;
    vector<MI_Uint64> buf64;
    vector<MI_Uint32> indices;
    MI_Uint64 sum1 = 0;
    MI_Uint64 sum2 = 0;
    const size_t N = 100000;
    MI_Result r;

    if(!TEST_ASSERT(MI_RESULT_OK == Buf_Init(&b, 256)))
        NitsReturn;

    for (size_t i = 0; i < N; i++)
    {
        buf8.push_back(rand() % 0xFF);
        buf16.push_back(rand() % 0xFFFF);
        buf32.push_back(rand() % 0xFFFFFFFF);
        buf64.push_back(rand() % 0xFFFFFFFF);
        indices.push_back((MI_Uint32)rand() % 3);

        switch (indices[i])
        {
            case 0:
                r = Buf_PackU8(&b, buf8[i]);
                TEST_ASSERT(r == MI_RESULT_OK);
                sum1 += buf8[i];
                break;
            case 1:
                r = Buf_PackU16(&b, buf16[i]);
                TEST_ASSERT(r == MI_RESULT_OK);
                sum1 += buf16[i];
                break;
            case 2:
                r = Buf_PackU32(&b, buf32[i]);
                TEST_ASSERT(r == MI_RESULT_OK);
                sum1 += buf32[i];
                break;
            case 3:
                r = Buf_PackU64(&b, buf64[i]);
                sum1 += buf64[i];
                TEST_ASSERT(r == MI_RESULT_OK);
                break;
        }
    }

    for (size_t i = 0; i < N; i++)
    {
        switch (indices[i])
        {
            case 0:
            {
                MI_Uint8 x = 0;
                r = Buf_UnpackU8(&b, &x);
                TEST_ASSERT(r == MI_RESULT_OK);
                TEST_ASSERT(x == buf8[i]);
                sum2 += buf8[i];
                break;
            }
            case 1:
            {
                MI_Uint16 x = 0;
                r = Buf_UnpackU16(&b, &x);
                TEST_ASSERT(r == MI_RESULT_OK);
                TEST_ASSERT(x == buf16[i]);
                sum2 += buf16[i];
                break;
            }
            case 2:
            {
                MI_Uint32 x = 0;
                r = Buf_UnpackU32(&b, &x);
                TEST_ASSERT(r == MI_RESULT_OK);
                TEST_ASSERT(x == buf32[i]);
                sum2 += buf32[i];
                break;
            }
            case 3:
            {
                MI_Uint64 x = 0;
                r = Buf_UnpackU64(&b, &x);
                TEST_ASSERT(r == MI_RESULT_OK);
                TEST_ASSERT(x == buf64[i]);
                sum2 += buf64[i];
                break;
            }
        }
    }

    /* Verify that the check sums are the same */
    TEST_ASSERT(sum1 == sum2);

    Buf_Destroy(&b);
}
NitsEndTest

/*
**==============================================================================
**
** TestBuf2()
**
**     This test excercises the string pack/unpack functions of Buf.
**     It packs N decimal formatted strings and then unpacks them, comparing
**     that backed and unpacked forms are consistent.
**
**==============================================================================
*/
NitsTestWithSetup(TestBuf2, TestBaseSetup)
{
    Buf b;
    MI_Result r;
    MI_Uint32 i;
    const MI_Uint32 N = 10000;

    if(!TEST_ASSERT(Buf_Init(&b, 256) == MI_RESULT_OK))
        NitsReturn;

    for (i = 0; i < N; i++)
    {
        ZChar buf[32];
        Stprintf(buf, MI_COUNT(buf), PAL_T("%u"), i);
        r = Buf_PackStr(&b, buf);
        TEST_ASSERT(r == MI_RESULT_OK);
    }

    for (i = 0; i < N; i++)
    {
        ZChar buf[32];
        const ZChar* str = NULL;

        Stprintf(buf, MI_COUNT(buf), PAL_T("%u"), i);
        r = Buf_UnpackStr(&b, &str);
        TEST_ASSERT(r == MI_RESULT_OK);
    }

    Buf_Destroy(&b);
}
NitsEndTest

/*
**==============================================================================
**
** TestBuf3()
**
**     This test excercises the integer array pack/unpack functions of Buf.
**     It packs N arrays of various lengths and attempts to unpack them and
**     compare the results.
**
**==============================================================================
*/
NitsTestWithSetup(TestBuf3, TestBaseSetup)
{
    Buf b;
    MI_Uint32 i;
    const MI_Uint32 N = 100;
    MI_Result r;
    vector<MI_Uint8> a8;
    vector<MI_Uint16> a16;
    vector<MI_Uint32> a32;
    vector<MI_Uint64> a64;
    vector<MI_Uint8> b8;
    vector<MI_Uint16> b16;
    vector<MI_Uint32> b32;
    vector<MI_Uint64> b64;

    if(!TEST_ASSERT(Buf_Init(&b, 256) == MI_RESULT_OK))
        NitsReturn;

    for (i = 0; i < N; i++)
    {
        a8.push_back((MI_Uint8)i);
        a16.push_back((MI_Uint16)i);
        a32.push_back((MI_Uint32)i);
        a64.push_back((MI_Uint64)i);
        {
            r = Buf_PackU8A(&b, &a8[0], (MI_Uint32)a8.size());
            if(!TEST_ASSERT(r == MI_RESULT_OK))
                goto Error;
        }
        {
            r = Buf_PackU16A(&b, &a16[0], (MI_Uint32)a16.size());
            if(!TEST_ASSERT(r == MI_RESULT_OK))
                goto Error;            
        }
        {
            r = Buf_PackU32A(&b, &a32[0], (MI_Uint32)a32.size());
            if(!TEST_ASSERT(r == MI_RESULT_OK))
                goto Error;            
        }
        {
            r = Buf_PackU64A(&b, &a64[0], (MI_Uint32)a64.size());
            if(!TEST_ASSERT(r == MI_RESULT_OK))
                goto Error;            
        }
    }

    for (i = 0; i < N; i++)
    {
        b8.push_back((MI_Uint8)i);
        b16.push_back((MI_Uint16)i);
        b32.push_back((MI_Uint32)i);
        b64.push_back((MI_Uint64)i);
        {
            const MI_Uint8* data;
            MI_Uint32 size;

            r = Buf_UnpackU8A(&b, &data, &size);
            if(TEST_ASSERT(r == MI_RESULT_OK))
            {
                TEST_ASSERT((MI_Uint32)b8.size() == size);
                TEST_ASSERT(memcmp(data, &b8[0], i * sizeof(MI_Uint8)) == 0);
            }
        }
        {
            const MI_Uint16* data;
            MI_Uint32 size;

            r = Buf_UnpackU16A(&b, &data, &size);
            if(TEST_ASSERT(r == MI_RESULT_OK))
            {
                TEST_ASSERT((MI_Uint32)b16.size() == size);
                TEST_ASSERT(memcmp(data, &b16[0], i * sizeof(MI_Uint16)) == 0);
            }
        }
        {
            const MI_Uint32* data;
            MI_Uint32 size;

            r = Buf_UnpackU32A(&b, &data, &size);
            if(TEST_ASSERT(r == MI_RESULT_OK))
            {
                TEST_ASSERT((MI_Uint32)b32.size() == size);
                TEST_ASSERT(memcmp(data, &b32[0], i * sizeof(MI_Uint32)) == 0);
            }
        }
        {
            const MI_Uint64* data;
            MI_Uint32 size;

            r = Buf_UnpackU64A(&b, &data, &size);
            if(TEST_ASSERT(r == MI_RESULT_OK))
            {
                TEST_ASSERT((MI_Uint32)b64.size() == size);
                TEST_ASSERT(memcmp(data, &b64[0], i * sizeof(MI_Uint64)) == 0);
            }
        }
    }
Error:
    Buf_Destroy(&b);
}
NitsEndTest

/*
**==============================================================================
**
** TestBuf4()
**
**     This test excercises the string array pack/unpack functions of Buf.
**
**==============================================================================
*/
NitsTestWithSetup(TestBuf4, TestBaseSetup)
{
    Buf b;
    MI_Result r;
    const ZChar* DATA[5][7] =
    {
        {
            PAL_T("Sunday"),
            PAL_T("Monday"),
            PAL_T("Tuesday"),
            PAL_T("Wednesday"),
            PAL_T("Thursday"),
            PAL_T("Friday"),
            PAL_T("Saturday")
        },
        {},
        {
            PAL_T("Unicorn")
        },
        {
            PAL_T("")
        },
        {
            PAL_T(""),
            PAL_T(""),
            PAL_T("")
        }
    };
    int arrayIndex;
    const int DATA_size[5] = {7,0,1,1,3};

    for (arrayIndex = 0; arrayIndex < 5; arrayIndex++)
    {
        const MI_Uint32 SIZE = DATA_size[arrayIndex];
        const ZChar** data;
        MI_Uint32 size;
        MI_Uint32 i;

        {
            if(TEST_ASSERT(MI_RESULT_OK == Buf_Init(&b, 256)))
            {
                r = Buf_PackStrA(&b, DATA[arrayIndex], SIZE);
                if(TEST_ASSERT(r == MI_RESULT_OK))
                {
                    r = Buf_UnpackStrA(&b, &data, &size);
                    TEST_ASSERT(r == MI_RESULT_OK);
                    TEST_ASSERT(size == SIZE);

                    for (i = 0; i < size; i++)
                        TEST_ASSERT(Tcscmp(data[i], DATA[arrayIndex][i]) == 0);
                }

                Buf_Destroy(&b);
            }
        }
        {
            MI_Uint32 j;
            const MI_Uint32 N = 100;
            MI_Boolean packingSuccess = MI_TRUE;

            if(TEST_ASSERT(MI_RESULT_OK == Buf_Init(&b, 256)))
            {
                for (j = 0; j < N; j++)
                {
                    r = Buf_PackStrA(&b, DATA[arrayIndex], SIZE);
                    if(!TEST_ASSERT(r == MI_RESULT_OK))
                    {
                        packingSuccess = MI_FALSE;
                        break;
                    }
                }

                if(packingSuccess)
                {
                    for (j = 0; j < N; j++)
                    {
                        r = Buf_UnpackStrA(&b, &data, &size);
                        TEST_ASSERT(r == MI_RESULT_OK);

                        TEST_ASSERT(size == SIZE);

                        for (i = 0; i < size; i++)
                            TEST_ASSERT(Tcscmp(data[i], DATA[arrayIndex][i]) == 0);
                    }
                }

                Buf_Destroy(&b);
            }
        }
    }
}
NitsEndTest

NitsTestWithSetup(TestPackInstance, TestBaseSetup)
{
    MI_Instance* inst1 = NULL;
    MI_Instance* inst2 = NULL;
    Batch batch = BATCH_INITIALIZER;
    Buf buf = BUF_INITIALIZER;
    MI_Result r;

    /* Create new instance of MSFT_AllTypes */
    inst1 = NewAllTypes(&batch);
    if(!TEST_ASSERT(inst1 != NULL))
        goto Error;

    /* Pack instance */
    r = Instance_Pack(inst1, MI_FALSE, NULL, NULL, &buf);
    TEST_ASSERT(r == MI_RESULT_OK);

    /* Unpack instance */
    r = Instance_Unpack(&inst2, &buf, &batch, MI_FALSE);
    if(TEST_ASSERT(r == MI_RESULT_OK))
    {
        TEST_ASSERT(inst2 != NULL);

    #if 0
        MI_Instance_Print(inst1, stdout, 0);
        MI_Instance_Print(inst2, stdout, 0);
    #endif

        /* Steal buffer memory and attach it to the batch. */
        {
            Page* page = Buf_StealPage(&buf);
            TEST_ASSERT(page != NULL);
            Batch_AttachPage(&batch, page);
        }
    }
Error:
    if(inst1)
        MI_Instance_Delete(inst1);
    if(inst2)
        MI_Instance_Delete(inst2);
    Buf_Destroy(&buf);
    Batch_Destroy(&batch);
}
NitsEndTest

NitsTestWithSetup(TestPage, TestBaseSetup)
{
    size_t n = sizeof (Page);
    TEST_ASSERT(n % 8 == 0);
}
NitsEndTest

// this test is driving OACR crazy; it consumes 15+ GB of memory; takes more than 15 mins to analyze this file
// and on x86 it fails with internal error; I am keeping this linux specific till this issue is resolved
#ifndef _MSC_VER

#define TestOneCppProp(prop,valueParam)             \
    {  \
    /* test auto-generated setters/getters/copy/assignment operators  */  \
    MSFT_AllTypes_Class inst1;                   \
                                                \
    TEST_ASSERT(!inst1.prop().exists);            \
    inst1.prop##_value(valueParam);             \
    TEST_ASSERT(inst1.prop().exists);             \
    TEST_ASSERT(inst1.prop().value == valueParam);   \
                                                \
    /* copy ctor of instance */                 \
    MSFT_AllTypes_Class inst2( inst1 );          \
                                                \
    TEST_ASSERT(inst1.prop() == inst2.prop());    \
    TEST_ASSERT(inst1.prop##_value() == inst2.prop##_value());    \
                                                \
    /* assignment operator */                   \
    MSFT_AllTypes_Class inst3;                   \
                                                \
    TEST_ASSERT(inst1.prop().exists != inst3.prop().exists);    \
    TEST_ASSERT(!inst3.prop().exists);            \
                                                \
    inst3 = inst1;                              \
    TEST_ASSERT(inst1.prop().exists == inst3.prop().exists);    \
    TEST_ASSERT(inst1.prop().value == inst3.prop().value);    \
    TEST_ASSERT(inst1.prop##_value() == inst3.prop##_value());    \
                                                \
    /* copy data using setters  */              \
    MSFT_AllTypes_Class inst4;                   \
                                                \
    TEST_ASSERT(inst1.prop().exists != inst4.prop().exists);    \
                                                \
    inst4.prop(inst1.prop());                   \
    TEST_ASSERT(inst1.prop() == inst4.prop());    \
    TEST_ASSERT(inst1.prop##_value() == inst4.prop##_value());    \
                                                \
    /* test null assignment */                  \
    MSFT_AllTypes_Class inst_null;               \
                                                \
    TEST_ASSERT(inst4.prop() != inst_null.prop());    \
    inst4 = inst_null;                          \
    TEST_ASSERT(inst4.prop() == inst_null.prop());\
    }

NitsTestWithSetup(TestBaseCppAllTypes, TestBaseSetup)
{

    TestOneCppProp(BooleanValue,MI_TRUE);
    TestOneCppProp(BooleanValue,MI_FALSE);
    TestOneCppProp(Uint8Value,0);
    TestOneCppProp(Uint8Value,88);
    TestOneCppProp(Sint8Value,0);
    TestOneCppProp(Sint8Value,-88);
    TestOneCppProp(Uint16Value,0);
    TestOneCppProp(Uint16Value,1616);
    TestOneCppProp(Sint16Value,0);
    TestOneCppProp(Sint16Value,-1616);
    TestOneCppProp(Uint32Value,0);
    TestOneCppProp(Uint32Value,3232);
    TestOneCppProp(Sint32Value,0);
    TestOneCppProp(Sint32Value,-3232);
    TestOneCppProp(Uint64Value,0);
    TestOneCppProp(Uint64Value,6464);
    TestOneCppProp(Sint64Value,0);
    TestOneCppProp(Sint64Value,-6464);

    TestOneCppProp(StringValue,MI_T("123"));
    TestOneCppProp(StringValue,String(MI_T("123")));
    TestOneCppProp(StringValue,String());

    StringA sa;  sa.PushBack(MI_T("123")); sa.PushBack(MI_T("321"));

    //ATTN: add == in vector !! TestOneCppProp(StringArray,sa);
    //TestOneCppProp(StringArray,StringA());
}
NitsEndTest
#endif

NitsTestWithSetup(TestDir, TestBaseSetup)
{
    string path = srcdir + "/tests/base/testdir";
    Dir* dir = Dir_Open(path.c_str());
    if(!TEST_ASSERT(dir != NULL))
        NitsReturn;

    vector<string> names1;

    for (;;)
    {
        DirEnt* ent = Dir_Read(dir);
        if (!ent)
            break;

        if (strcmp(ent->name, "..") == 0 || strcmp(ent->name, ".") == 0)
            continue;

        if (strcmp(ent->name, "CVS") == 0)
            continue;

        names1.push_back(ent->name);
    }

    sort(names1.begin(), names1.end());

    vector<string> names2;
    names2.push_back("dir1");
    names2.push_back("dir2");
    names2.push_back("file1");
    names2.push_back("file2");
    names2.push_back("file3");

    TEST_ASSERT(names1.size() == 5);
    TEST_ASSERT(names2.size() == 5);
    TEST_ASSERT(names1 == names2);

    Dir_Close(dir);
}
NitsEndTest

NitsTestWithSetup(TestStrArr, TestBaseSetup)
{
    char** data;
    
    data = StrArr();
    if (!TEST_ASSERT(data != NULL))
        NitsReturn;

    TEST_ASSERT(StrArrLen(data) == 0);

    StrArrCat(&data, "Red");
    if (!TEST_ASSERT(data != NULL))
        NitsReturn;
    TEST_ASSERT(StrArrLen(data) == 1);
    StrArrCat(&data, "Green");
    if (!TEST_ASSERT(data != NULL))
        NitsReturn;
    TEST_ASSERT(StrArrLen(data) == 2);
    StrArrCat(&data, "Blue");
    if (!TEST_ASSERT(data != NULL))
        NitsReturn;
    TEST_ASSERT(StrArrLen(data) == 3);

    char ** tmp = data;
    TEST_ASSERT(strcmp(*tmp, "Red") == 0);
    if (*tmp)
    {
        tmp++;
        TEST_ASSERT(strcmp(*tmp, "Green") == 0);
    }
    else
    {
        TEST_ASSERT("unexpected end of array" && NULL);
    }
    if (*tmp)
    {
        tmp++;
        TEST_ASSERT(strcmp(*tmp, "Blue") == 0);
    }
    else
    {
        TEST_ASSERT("unexpected end of array" && NULL);
    }

    StrArrFree(data);
}
NitsEndTest

NitsTestWithSetup(TestConf1, TestBaseSetup)
{
    char path[PAL_MAX_PATH_SIZE];
    Conf* conf;
    size_t n = 1;

    Strlcpy(path, OMI_GetPath(ID_SRCDIR), sizeof(path));
    Strlcat(path, "/tests/base/file1.conf", sizeof(path));

    /* Open configuration file */
    conf = Conf_Open(path);
    if(!TEST_ASSERT(conf != NULL))
        NitsReturn;

    for (;;)
    {
        const char* key;
        const char* value;
        int r = Conf_Read(conf, &key, &value);

        if (r == 1)
            break;

        TEST_ASSERT(r == 0);

        switch (n)
        {
            case 1:
                TEST_ASSERT(strcmp(key, "Key1") == 0);
                TEST_ASSERT(strcmp(value, "Value1") == 0);
                break;
            case 2:
                TEST_ASSERT(strcmp(key, "Key2") == 0);
                TEST_ASSERT(strcmp(value, "Value2") == 0);
                break;
            case 3:
                TEST_ASSERT(strcmp(key, "Key3") == 0);
                TEST_ASSERT(strcmp(value, "Value3") == 0);
                break;
            case 4:
                TEST_ASSERT(strcmp(key, "Key4") == 0);
                TEST_ASSERT(strcmp(value, "Value4") == 0);
                break;
            case 5:
                TEST_ASSERT(strcmp(key, "Key5") == 0);
                TEST_ASSERT(strcmp(value, "Value5") == 0);
                break;
            case 6:
                TEST_ASSERT(strcmp(key, "Key6") == 0);
                TEST_ASSERT(strcmp(value, "") == 0);
                break;
            case 7:
                TEST_ASSERT(strcmp(key, "Key7") == 0);
                TEST_ASSERT(strcmp(value, "") == 0);
                break;
            default:
                TEST_ASSERT(UT_FALSE);
        }

        n++;
    }

    Conf_Close(conf);
}
NitsEndTest

NitsTestWithSetup(TestConf2, TestBaseSetup)
{
    char path[PAL_MAX_PATH_SIZE];
    Conf* conf;
    size_t n = 1;

    Strlcpy(path, OMI_GetPath(ID_SRCDIR), sizeof(path));
    Strlcat(path, "/tests/base/file2.conf", sizeof(path));

    /* Open configuration file */
    conf = Conf_Open(path);
    if(!TEST_ASSERT(conf != NULL))
        NitsReturn;

    for (;;)
    {
        const char* key;
        const char* value;
        int r = Conf_Read(conf, &key, &value);

        if (r == -1)
        {
            const char* err = Conf_Error(conf);

            if (n == 1)
            {
                TEST_ASSERT(strcmp(err, "expected '='") == 0);
                TEST_ASSERT(Conf_Line(conf) == 2);
            }
            else if (n == 2)
            {
                TEST_ASSERT(strcmp(err, "expected keyword") == 0);
                TEST_ASSERT(Conf_Line(conf) == 3);
            }
            else if (n == 3)
            {
                TEST_ASSERT(strcmp(err, "expected keyword") == 0);
                TEST_ASSERT(Conf_Line(conf) == 4);
            }
            else
                TEST_ASSERT(UT_FALSE);
        }
        else if (r == 0)
        {
            TEST_ASSERT(n == 4);
            TEST_ASSERT(strcmp(key, "KEY1") == 0);
            TEST_ASSERT(strcmp(value, "VALUE1") == 0);
        }
        else
            break;

        n++;
    }

    Conf_Close(conf);
}
NitsEndTest

NitsTestWithSetup(TestMkdirhier, TestBaseSetup)
{
    char tmp[PAL_MAX_PATH_SIZE];
    Mkdirhier(TempPath(tmp, "/aaa/bbb/ccc/ddd"), 0755);
    TEST_ASSERT(Isdir(tmp));
}
NitsEndTest

NitsTestWithSetup(TestIntToStr, TestBaseSetup)
{
    for (MI_Uint32 i = 0; i < 1000; i++)
    {
        char buf1[11];
        size_t size1;
        const char* str = Uint32ToStr(buf1, i, &size1);

        char buf2[11];
        size_t size2 = Snprintf(buf2, sizeof(buf2), "%u", i);

        TEST_ASSERT(str != NULL);
        TEST_ASSERT(size1 == size2);
        TEST_ASSERT(strcmp(str, buf2) == 0);
    }

    for (MI_Uint64 i = 0; i < 1000; i++)
    {
        char buf1[21];
        size_t size1;
        const char* str = NULL;
        Uint64ToStr(buf1, i, &str, &size1);

        char buf2[21];
        size_t size2 = Snprintf(buf2, sizeof(buf2), UINT64_FMT, i);

        TEST_ASSERT(str != NULL);
        TEST_ASSERT(size1 == size2);
        TEST_ASSERT(strcmp(str, buf2) == 0);
    }
}
NitsEndTest

NitsTestWithSetup(TestGetOpt, TestBaseSetup)
{
    GetOptState state = GETOPTSTATE_INITIALIZER;

    const char* argv[] =
    {
        "aaa",
        "bbb",
        "--help",
        "--infile=/tmp/infile",
        "--outfile",
        "/tmp/outfile",
        "-x=abc",
        "ccc",
        NULL,
    };
    int argc = sizeof(argv) / sizeof(argv[0]) - 1;

    static const char* opts[] =
    {
        "--help",
        "--infile:",
        "--outfile:",
        "-x:",
        NULL,
    };

    int r;
    bool help = false;
    string infile;
    string outfile;
    string x;

    for (;;)
    {
        r = GetOpt(&argc, argv, opts, &state);

        if (r == -1)
        {
            Ftprintf(stderr, PAL_T("GetOpt() failed: %s\n"), scs(state.err));
            UT_ASSERT_FAILED_MSG("GetOpt failed");
        }

        if (r != 0)
            break;

        if (strcmp(state.opt, "--help") == 0)
            help = true;
        else if (strcmp(state.opt, "--infile") == 0)
            infile = state.arg;
        else if (strcmp(state.opt, "--outfile") == 0)
            outfile = state.arg;
        else if (strcmp(state.opt, "-x") == 0)
            x = state.arg;
    }

    TEST_ASSERT(argc == 3);
    TEST_ASSERT(strcmp(argv[0], "aaa") == 0);
    TEST_ASSERT(strcmp(argv[1], "bbb") == 0);
    TEST_ASSERT(strcmp(argv[2], "ccc") == 0);
    TEST_ASSERT(argv[3] == NULL);
    TEST_ASSERT(help == true);
    TEST_ASSERT(infile == "/tmp/infile");
    TEST_ASSERT(outfile == "/tmp/outfile");
    TEST_ASSERT(x == "abc");
}
NitsEndTest

NitsTestWithSetup(TestGetOptErr, TestBaseSetup)
{
    GetOptState state = GETOPTSTATE_INITIALIZER;

    const char* argv[] =
    {
        "aaa",
        "--help",
        "bbb",
        "--outfile", /* missing option argument */
        NULL,
    };
    int argc = sizeof(argv) / sizeof(argv[0]) - 1;

    static const char* opts[] =
    {
        "--help",
        "--outfile:",
        NULL,
    };

    bool help = false;
    string outfile;
    string error;

    for (;;)
    {
        int r = GetOpt(&argc, argv, opts, &state);

        if (r == 1)
            break;

        if (r == 0)
        {
            if (strcmp(state.opt, "--help") == 0)
                help = true;
            else if (strcmp(state.opt, "--outfile") == 0)
                outfile = state.arg;
        }
        if (r == -1)
        {
            error = state.err;
            break;
        }
    }

    TEST_ASSERT(help == true);
    TEST_ASSERT(error == "missing option argument: --outfile");
    TEST_ASSERT(outfile == "");
}
NitsEndTest

NitsTestWithSetup(TestMatchKeys, TestBaseSetup)
{
    MI_Result r;
    MI_Instance* inst1 = NULL;
    MI_Instance* inst2 = NULL;
    MI_Instance* ref = NULL;
    MI_Value value;

    r = Instance_NewDynamic(&ref, PAL_T("MyRef"), MI_FLAG_CLASS, 0);
    if(!TEST_ASSERT(r == MI_RESULT_OK))
        goto Error;

    value.uint32 = 57789;
    r = MI_Instance_AddElement(ref, PAL_T("Key1"), &value, MI_UINT32, MI_FLAG_KEY);
    TEST_ASSERT(r == MI_RESULT_OK);

    value.string = (ZChar*)PAL_T("Bye");
    r = MI_Instance_AddElement(ref, PAL_T("Key2"), &value, MI_STRING, MI_FLAG_KEY);
    TEST_ASSERT(r == MI_RESULT_OK);
    
    r = Instance_NewDynamic(&inst1, PAL_T("MyClass"), MI_FLAG_ASSOCIATION, 0);
    if(!TEST_ASSERT(r == MI_RESULT_OK))
        goto Error;

    r = Instance_NewDynamic(&inst2, PAL_T("MyClass"), MI_FLAG_CLASS, 0);
    if(!TEST_ASSERT(r == MI_RESULT_OK))
        goto Error;

    TEST_ASSERT(Instance_MatchKeys(inst1, inst2) == MI_FALSE);

    value.uint32 = 1234;
    r = MI_Instance_AddElement(inst1, PAL_T("Key1"), &value,MI_UINT32, MI_FLAG_KEY);
    TEST_ASSERT(r == MI_RESULT_OK);

    value.string = (ZChar*)PAL_T("Hello");
    r = MI_Instance_AddElement(inst1, PAL_T("Key2"), &value, MI_STRING,MI_FLAG_KEY);
    TEST_ASSERT(r == MI_RESULT_OK);

    TEST_ASSERT(Instance_MatchKeys(inst1, inst2) == MI_FALSE);

    value.uint32 = 1234;
    r = MI_Instance_AddElement(inst2, PAL_T("Key1"), &value, MI_UINT32,MI_FLAG_KEY);
    TEST_ASSERT(r == MI_RESULT_OK);

    TEST_ASSERT(Instance_MatchKeys(inst1, inst2) == MI_FALSE);

    value.string = (ZChar*)PAL_T("Hello");
    r = MI_Instance_AddElement(inst2, PAL_T("Key2"), &value, MI_STRING,MI_FLAG_KEY);
    TEST_ASSERT(r == MI_RESULT_OK);

    TEST_ASSERT(Instance_MatchKeys(inst1, inst2) == MI_TRUE);

    value.reference = ref;
    r = MI_Instance_AddElement(inst1, PAL_T("Key3"), &value, 
        MI_REFERENCE,MI_FLAG_KEY);
    TEST_ASSERT(r == MI_RESULT_OK);

    TEST_ASSERT(Instance_MatchKeys(inst1, inst2) == MI_FALSE);

    value.reference = ref;
    r = MI_Instance_AddElement(inst2, PAL_T("Key3"), &value, 
        MI_REFERENCE,MI_FLAG_KEY);
    TEST_ASSERT(r == MI_RESULT_OK);

    TEST_ASSERT(Instance_MatchKeys(inst1, inst2) == MI_TRUE);

#if 0
    __MI_Instance_Print(inst1, stdout, 0);
    __MI_Instance_Print(inst2, stdout, 0);
#endif
Error:
    if(inst1)
        __MI_Instance_Delete(inst1);
    if(inst2)
        __MI_Instance_Delete(inst2);
    if(ref)
        __MI_Instance_Delete(ref);
}
NitsEndTest

NitsTestWithSetup(TestInstance_ValidateNonNullKeys_Static, TestBaseSetup)
{
    MI_Result r;
    MI_Instance* inst = NULL;
    MI_Value value;
    const MI_ClassDecl* cd = NULL;
    Batch batch = BATCH_INITIALIZER;
    
    /* Find class decl */
    cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, PAL_T("MSFT_Process"));
    TEST_ASSERT(cd != NULL);
    if (!cd)
        goto VNNK_Static_CleanUp;

    /* Create instance of MSFT_Process */
    r = Instance_New(&inst, cd, &batch);
    TEST_ASSERT(r == MI_RESULT_OK);
    if (MI_RESULT_OK != r)
        goto VNNK_Static_CleanUp;

    /* Fill 5 of the 6 key properties */
    value.string = (ZChar*)PAL_T("csccn");
    r = MI_Instance_SetElement(inst, PAL_T("CSCreationClassName"), &value, MI_STRING, 0);
    TEST_ASSERT(r == MI_RESULT_OK);

    value.string = (ZChar*)PAL_T("csn");
    r = MI_Instance_SetElement(inst, PAL_T("CSName"), &value, MI_STRING, 0);
    TEST_ASSERT(r == MI_RESULT_OK);

    value.string = (ZChar*)PAL_T("osccn");
    r = MI_Instance_SetElement(inst, PAL_T("OSCreationClassName"), &value, MI_STRING, 0);
    TEST_ASSERT(r == MI_RESULT_OK);

    value.string = (ZChar*)PAL_T("osn");
    r = MI_Instance_SetElement(inst, PAL_T("OSName"), &value, MI_STRING, 0);
    TEST_ASSERT(r == MI_RESULT_OK);

    value.string = (ZChar*)PAL_T("ccn");
    r = MI_Instance_SetElement(inst, PAL_T("CreationClassName"), &value, MI_STRING, 0);
    TEST_ASSERT(r == MI_RESULT_OK);

    /* Expect failure because only 5 of the 6 key properties are non-NULL */
    TEST_ASSERT(MI_FALSE == Instance_ValidateNonNullKeys(inst));

    /* Populate the last key property and expect success */
    value.string = (ZChar*)PAL_T("h");
    r = MI_Instance_SetElement(inst, PAL_T("Handle"), &value, MI_STRING, 0);
    TEST_ASSERT(r == MI_RESULT_OK);

    TEST_ASSERT(MI_TRUE == Instance_ValidateNonNullKeys(inst));

VNNK_Static_CleanUp:
    if (inst)
        MI_Instance_Delete(inst);
    Batch_Destroy(&batch);
}
NitsEndTest

NitsTestWithSetup(TestInstance_ValidateNonNullKeys_Dynamic, TestBaseSetup)
{
    MI_Instance* inst = NULL;
    MI_Result r;
    MI_Value v;
    Batch batch = BATCH_INITIALIZER;
    Batch* b = &batch;

    r = Instance_NewDynamic(&inst, PAL_T("MSFT_TestDynamic"), MI_FLAG_CLASS, b);
    TEST_ASSERT(r == MI_RESULT_OK);
    if(MI_RESULT_OK != r)
        goto VNNK_Dynamic_CleanUp;

    /* No properties succeeds */
    TEST_ASSERT(MI_TRUE == Instance_ValidateNonNullKeys(inst));

    v.uint32 = 1;
    r = MI_Instance_AddElement(inst, PAL_T("Key"), &v, MI_UINT32, MI_FLAG_KEY);
    TEST_ASSERT(r == MI_RESULT_OK);

    /* Non-NULL key property succeeds */
    TEST_ASSERT(MI_TRUE == Instance_ValidateNonNullKeys(inst));

    v.string = NULL;
    r = MI_Instance_AddElement(inst, PAL_T("StringKey"), &v, MI_STRING, MI_FLAG_KEY | MI_FLAG_NULL);
    TEST_ASSERT(r == MI_RESULT_OK);

    /* NULL key property triggers failure */
    TEST_ASSERT(MI_FALSE == Instance_ValidateNonNullKeys(inst));

VNNK_Dynamic_CleanUp:
    if(inst)
        MI_Instance_Delete(inst);
    if(b)
        Batch_Destroy(b);
}
NitsEndTest

NitsTestWithSetup(TestWSManDatetime, TestBaseSetup)
{
    ZChar buf[64];

    {
        MI_Datetime x;
        MI_Uint64 inUsec = 0;
        TEST_ASSERT(ParseWSManDatetime(PAL_T("P5Y"), &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 1826);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 0);
        TEST_ASSERT(x.u.interval.seconds == 0);
        TEST_ASSERT(x.u.interval.microseconds == 0);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, PAL_T("P1826D")) == 0);

        UT_ASSERT(DatetimeToUsec( &x, &inUsec) == 0);
        UT_ASSERT(inUsec == 157766400000000ULL);

        UT_ASSERT(UsecToDatetime(inUsec, &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 1826);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 0);
        TEST_ASSERT(x.u.interval.seconds == 0);
        TEST_ASSERT(x.u.interval.microseconds == 0);
    }
    {
        MI_Datetime x;
        MI_Uint64 inUsec = 0;
        TEST_ASSERT(ParseWSManDatetime(PAL_T("P1Y1M22D"), &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 417);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 0);
        TEST_ASSERT(x.u.interval.seconds == 0);
        TEST_ASSERT(x.u.interval.microseconds == 0);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, PAL_T("P417D")) == 0);
        
        UT_ASSERT(DatetimeToUsec( &x, &inUsec) == 0);
        UT_ASSERT(inUsec == 36028800000000ULL);

        UT_ASSERT(UsecToDatetime(inUsec, &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 417);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 0);
        TEST_ASSERT(x.u.interval.seconds == 0);
        TEST_ASSERT(x.u.interval.microseconds == 0);

    }
    {
        MI_Datetime x;
        MI_Uint64 inUsec = 0;
        TEST_ASSERT(ParseWSManDatetime(PAL_T("P1Y1M22DT10H11M12S"), &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 417);
        TEST_ASSERT(x.u.interval.hours == 10);
        TEST_ASSERT(x.u.interval.minutes == 11);
        TEST_ASSERT(x.u.interval.seconds == 12);
        TEST_ASSERT(x.u.interval.microseconds == 0);
        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, PAL_T("P417DT10H11M12S")) == 0);

        UT_ASSERT(DatetimeToUsec( &x, &inUsec) == 0);
        UT_ASSERT(inUsec == 36065472000000ULL);

        UT_ASSERT(UsecToDatetime(inUsec, &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 417);
        TEST_ASSERT(x.u.interval.hours == 10);
        TEST_ASSERT(x.u.interval.minutes == 11);
        TEST_ASSERT(x.u.interval.seconds == 12);
        TEST_ASSERT(x.u.interval.microseconds == 0);
    }
    {
        MI_Datetime x;
        MI_Uint64 inUsec = 0;
        TEST_ASSERT(ParseWSManDatetime(PAL_T("PT31S"), &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 0);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 0);
        TEST_ASSERT(x.u.interval.seconds == 31);
        TEST_ASSERT(x.u.interval.microseconds == 0);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, PAL_T("PT31S")) == 0);

        TEST_ASSERT(DatetimeToUsec( &x, &inUsec) == 0);
        TEST_ASSERT(inUsec == 31000000);

        UT_ASSERT(UsecToDatetime(inUsec, &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 0);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 0);
        TEST_ASSERT(x.u.interval.seconds == 31);
        TEST_ASSERT(x.u.interval.microseconds == 0);
    }
    {
        MI_Datetime x;
        MI_Uint64 inUsec = 0;
        TEST_ASSERT(ParseWSManDatetime(PAL_T("PT66S"), &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 0);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 1);
        TEST_ASSERT(x.u.interval.seconds == 6);
        TEST_ASSERT(x.u.interval.microseconds == 0);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, PAL_T("PT1M6S")) == 0);

        TEST_ASSERT(DatetimeToUsec( &x, &inUsec) == 0);
        TEST_ASSERT(inUsec == 66000000);

        UT_ASSERT(UsecToDatetime(inUsec, &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 0);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 1);
        TEST_ASSERT(x.u.interval.seconds == 6);
        TEST_ASSERT(x.u.interval.microseconds == 0);
    }
    {
        MI_Datetime x;
        MI_Uint64 inUsec = 0;
        TEST_ASSERT(ParseWSManDatetime(PAL_T("PT60S"), &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 0);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 1);
        TEST_ASSERT(x.u.interval.seconds == 0);
        TEST_ASSERT(x.u.interval.microseconds == 0);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, PAL_T("PT1M")) == 0);

        TEST_ASSERT(DatetimeToUsec( &x, &inUsec) == 0);
        TEST_ASSERT(inUsec == 60000000);

        UT_ASSERT(UsecToDatetime(inUsec, &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 0);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 1);
        TEST_ASSERT(x.u.interval.seconds == 0);
        TEST_ASSERT(x.u.interval.microseconds == 0);
    }
    {
        MI_Datetime x;
        MI_Uint64 inUsec = 0;
        TEST_ASSERT(ParseWSManDatetime(PAL_T("PT5.5S"), &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 0);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 0);
        TEST_ASSERT(x.u.interval.seconds == 5);
        TEST_ASSERT(x.u.interval.microseconds == 500000);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, PAL_T("PT5.500000S")) == 0);

        TEST_ASSERT(DatetimeToUsec( &x, &inUsec) == 0);
        TEST_ASSERT(inUsec == 5500000);

        UT_ASSERT(UsecToDatetime(inUsec, &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 0);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 0);
        TEST_ASSERT(x.u.interval.seconds == 5);
        TEST_ASSERT(x.u.interval.microseconds == 500000);
    }
    {
        MI_Datetime x;
        MI_Uint64 inUsec = 0;
        TEST_ASSERT(ParseWSManDatetime(PAL_T("PT5.123456S"), &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 0);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 0);
        TEST_ASSERT(x.u.interval.seconds == 5);
        TEST_ASSERT(x.u.interval.microseconds == 123456);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, PAL_T("PT5.123456S")) == 0);

        TEST_ASSERT(DatetimeToUsec( &x, &inUsec) == 0);
        TEST_ASSERT(inUsec == 5123456);

        UT_ASSERT(UsecToDatetime(inUsec, &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 0);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 0);
        TEST_ASSERT(x.u.interval.seconds == 5);
        TEST_ASSERT(x.u.interval.microseconds == 123456);
    }
    {
        MI_Datetime x;
        MI_Uint64 inUsec = 0;
        TEST_ASSERT(ParseWSManDatetime(PAL_T("P1Y2M3DT10H30M"), &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 429);
        TEST_ASSERT(x.u.interval.hours == 10);
        TEST_ASSERT(x.u.interval.minutes == 30);
        TEST_ASSERT(x.u.interval.seconds == 0);
        TEST_ASSERT(x.u.interval.microseconds == 0);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, PAL_T("P429DT10H30M")) == 0);

        UT_ASSERT(DatetimeToUsec( &x, &inUsec) == 0);
        UT_ASSERT(inUsec == 37103400000000ULL);

        UT_ASSERT(UsecToDatetime(inUsec, &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 429);
        TEST_ASSERT(x.u.interval.hours == 10);
        TEST_ASSERT(x.u.interval.minutes == 30);
        TEST_ASSERT(x.u.interval.seconds == 0);
        TEST_ASSERT(x.u.interval.microseconds == 0);
    }
    {
        MI_Datetime x;
        MI_Uint64 inUsec = 0;
        TEST_ASSERT(ParseWSManDatetime(PAL_T("P1Y2MT"), &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 426);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 0);
        TEST_ASSERT(x.u.interval.seconds == 0);
        TEST_ASSERT(x.u.interval.microseconds == 0);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, PAL_T("P426D")) == 0);

        UT_ASSERT(DatetimeToUsec( &x, &inUsec) == 0);
        UT_ASSERT(inUsec == 36806400000000ULL);

        UT_ASSERT(UsecToDatetime(inUsec, &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 426);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 0);
        TEST_ASSERT(x.u.interval.seconds == 0);
        TEST_ASSERT(x.u.interval.microseconds == 0);
    }
    {
        MI_Datetime x;
        MI_Uint64 inUsec = 0;
        TEST_ASSERT(ParseWSManDatetime(PAL_T("PT0.000001S"), &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 0);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 0);
        TEST_ASSERT(x.u.interval.seconds == 0);
        TEST_ASSERT(x.u.interval.microseconds == 1);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, PAL_T("PT0.000001S")) == 0);

        TEST_ASSERT(DatetimeToUsec( &x, &inUsec) == 0);
        TEST_ASSERT(inUsec == 1);

        UT_ASSERT(UsecToDatetime(inUsec, &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 0);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 0);
        TEST_ASSERT(x.u.interval.seconds == 0);
        TEST_ASSERT(x.u.interval.microseconds == 1);
    }
    {
        MI_Datetime x;
        MI_Uint64 inUsec = 0;
        TEST_ASSERT(ParseWSManDatetime(PAL_T("2010-12-31T00:00:00Z"), &x) == 0);
        TEST_ASSERT(x.isTimestamp == 1);
        TEST_ASSERT(x.u.timestamp.year == 2010);
        TEST_ASSERT(x.u.timestamp.month == 12);
        TEST_ASSERT(x.u.timestamp.day == 31);
        TEST_ASSERT(x.u.timestamp.hour == 0);
        TEST_ASSERT(x.u.timestamp.minute == 0);
        TEST_ASSERT(x.u.timestamp.second == 0);
        TEST_ASSERT(x.u.timestamp.microseconds == 0);
        TEST_ASSERT(x.u.timestamp.utc == 0);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, PAL_T("2010-12-31T00:00:00Z")) == 0);

        TEST_ASSERT(DatetimeToUsec( &x, &inUsec) == -1);
    }
    {
        MI_Datetime x;
        TEST_ASSERT(ParseWSManDatetime(PAL_T("2010-1-1"), &x) == -1);
    }
    {
        MI_Datetime x;
        const ZChar STR[] = PAL_T("2010-12-31T00:00:00+06:33");
        TEST_ASSERT(ParseWSManDatetime(STR, &x) == 0);
        TEST_ASSERT(x.isTimestamp == 1);
        TEST_ASSERT(x.u.timestamp.year == 2010);
        TEST_ASSERT(x.u.timestamp.month == 12);
        TEST_ASSERT(x.u.timestamp.day == 31);
        TEST_ASSERT(x.u.timestamp.hour == 0);
        TEST_ASSERT(x.u.timestamp.minute == 0);
        TEST_ASSERT(x.u.timestamp.second == 0);
        TEST_ASSERT(x.u.timestamp.microseconds == 0);
        TEST_ASSERT(x.u.timestamp.utc == 393);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, STR) == 0);
    }
    {
        MI_Datetime x;
        const ZChar STR[] = PAL_T("2010-12-31T00:00:00-06:20");
        TEST_ASSERT(ParseWSManDatetime(STR, &x) == 0);
        TEST_ASSERT(x.isTimestamp == 1);
        TEST_ASSERT(x.u.timestamp.year == 2010);
        TEST_ASSERT(x.u.timestamp.month == 12);
        TEST_ASSERT(x.u.timestamp.day == 31);
        TEST_ASSERT(x.u.timestamp.hour == 0);
        TEST_ASSERT(x.u.timestamp.minute == 0);
        TEST_ASSERT(x.u.timestamp.second == 0);
        TEST_ASSERT(x.u.timestamp.microseconds == 0);
        TEST_ASSERT(x.u.timestamp.utc == -380);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, STR) == 0);
    }
    {
        MI_Datetime x;
        const ZChar STR[] = PAL_T("2010-12-31T00:00:00Z");
        TEST_ASSERT(ParseWSManDatetime(STR, &x) == 0);
        TEST_ASSERT(x.isTimestamp == 1);
        TEST_ASSERT(x.u.timestamp.year == 2010);
        TEST_ASSERT(x.u.timestamp.month == 12);
        TEST_ASSERT(x.u.timestamp.day == 31);
        TEST_ASSERT(x.u.timestamp.hour == 0);
        TEST_ASSERT(x.u.timestamp.minute == 0);
        TEST_ASSERT(x.u.timestamp.second == 0);
        TEST_ASSERT(x.u.timestamp.microseconds == 0);
        TEST_ASSERT(x.u.timestamp.utc == 0);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, STR) == 0);
    }
    {
        MI_Datetime x;
        TEST_ASSERT(ParseWSManDatetime(PAL_T("2010-12-31T12:30:03Z"), &x) == 0);
        TEST_ASSERT(x.isTimestamp == 1);
        TEST_ASSERT(x.u.timestamp.year == 2010);
        TEST_ASSERT(x.u.timestamp.month == 12);
        TEST_ASSERT(x.u.timestamp.day == 31);
        TEST_ASSERT(x.u.timestamp.hour == 12);
        TEST_ASSERT(x.u.timestamp.minute == 30);
        TEST_ASSERT(x.u.timestamp.second == 03);
        TEST_ASSERT(x.u.timestamp.microseconds == 0);
        TEST_ASSERT(x.u.timestamp.utc == 0);
    }
    {
        MI_Datetime x;
        const ZChar STR[] = PAL_T("2010-12-31T12:30:03+06:23");
        TEST_ASSERT(ParseWSManDatetime(STR, &x) == 0);

        TEST_ASSERT(x.isTimestamp == 1);
        TEST_ASSERT(x.u.timestamp.year == 2010);
        TEST_ASSERT(x.u.timestamp.month == 12);
        TEST_ASSERT(x.u.timestamp.day == 31);
        TEST_ASSERT(x.u.timestamp.hour == 12);
        TEST_ASSERT(x.u.timestamp.minute == 30);
        TEST_ASSERT(x.u.timestamp.second == 03);
        TEST_ASSERT(x.u.timestamp.microseconds == 0);
        TEST_ASSERT(x.u.timestamp.utc == 383);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, STR) == 0);
    }
    {
        MI_Datetime x;
        const ZChar STR[] = PAL_T("0000-00-00T12:30:03+06:23");
        TEST_ASSERT(ParseWSManDatetime(STR, &x) == 0);
        TEST_ASSERT(x.isTimestamp == 1);
        TEST_ASSERT(x.u.timestamp.year == 0);
        TEST_ASSERT(x.u.timestamp.month == 0);
        TEST_ASSERT(x.u.timestamp.day == 0);
        TEST_ASSERT(x.u.timestamp.hour == 12);
        TEST_ASSERT(x.u.timestamp.minute == 30);
        TEST_ASSERT(x.u.timestamp.second == 03);
        TEST_ASSERT(x.u.timestamp.microseconds == 0);
        TEST_ASSERT(x.u.timestamp.utc == 383);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, STR) == 0);
    }
    {
        MI_Datetime x;
        const ZChar STR[] = PAL_T("0000-00-00T12:30:03.123456+06:23");
        TEST_ASSERT(ParseWSManDatetime(STR, &x) == 0);
        TEST_ASSERT(x.isTimestamp == 1);
        TEST_ASSERT(x.u.timestamp.year == 0);
        TEST_ASSERT(x.u.timestamp.month == 0);
        TEST_ASSERT(x.u.timestamp.day == 0);
        TEST_ASSERT(x.u.timestamp.hour == 12);
        TEST_ASSERT(x.u.timestamp.minute == 30);
        TEST_ASSERT(x.u.timestamp.second == 03);
        TEST_ASSERT(x.u.timestamp.microseconds == 123456);
        TEST_ASSERT(x.u.timestamp.utc == 383);
        //PrintDatetime(&x);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, PAL_T("0000-00-00T12:30:03.123456+06:23")) == 0);
    }
    {
        MI_Datetime x;
        const ZChar STR[] = PAL_T("2010-12-31T12:30:03.123456+06:23");
        TEST_ASSERT(ParseWSManDatetime(STR, &x) == 0);
        TEST_ASSERT(x.isTimestamp == 1);
        TEST_ASSERT(x.u.timestamp.year == 2010);
        TEST_ASSERT(x.u.timestamp.month == 12);
        TEST_ASSERT(x.u.timestamp.day == 31);
        TEST_ASSERT(x.u.timestamp.hour == 12);
        TEST_ASSERT(x.u.timestamp.minute == 30);
        TEST_ASSERT(x.u.timestamp.second == 03);
        TEST_ASSERT(x.u.timestamp.microseconds == 123456);
        TEST_ASSERT(x.u.timestamp.utc == 383);
        //PrintDatetime(&x);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, STR) == 0);
    }
    {
        MI_Datetime x;
        TEST_ASSERT(ParseWSManDatetime( PAL_T("P4294967295D"), &x) == 0);
        TEST_ASSERT(x.isTimestamp == 0);
        TEST_ASSERT(x.u.interval.days == 4294967295U);
        TEST_ASSERT(x.u.interval.hours == 0);
        TEST_ASSERT(x.u.interval.minutes == 0);
        TEST_ASSERT(x.u.interval.seconds == 0);
        TEST_ASSERT(x.u.interval.microseconds == 0);

        FormatWSManDatetime(&x, buf);
        TEST_ASSERT(Tcscmp(buf, PAL_T("P4294967295D")) == 0);
    }
}
NitsEndTest

typedef struct _TestBucket /* derives from HashBucket */
{
    struct _TestBucket* next;
    ZChar* key;
    long data;
}
TestBucket;

NITS_EXTERN_C size_t TestHash(
    const HashBucket* bucket_)
{
    /* Note: this algorithm has a poor distribution */
    TestBucket* bucket = (TestBucket*)bucket_;
    size_t h = 0;
    ZChar* key = bucket->key;

    while (*key)
    {
        h += 5 * *key++;
    }

    return h;
}

NITS_EXTERN_C int TestEqual(
    const HashBucket* bucket1_,
    const HashBucket* bucket2_)
{
    TestBucket* bucket1 = (TestBucket*)bucket1_;
    TestBucket* bucket2 = (TestBucket*)bucket2_;
    return Tcscmp(bucket1->key, bucket2->key) == 0;
}

NITS_EXTERN_C void TestRelease(
    HashBucket* bucket_)
{
    TestBucket* bucket = (TestBucket*)bucket_;

    PAL_Free(bucket->key);
    PAL_Free(bucket);
}

NITS_EXTERN_C int TestBase64EncCallback(const char* data, size_t size, void* callbackData)
{
    vector<char>& buf = *((vector<char>*)callbackData);
    buf.insert(buf.end(), data, data + size);
    return 0;
}

NITS_EXTERN_C int TestBase64DecCallback(const void* data, size_t size, void* callbackData)
{
    vector<unsigned char>& buf = *((vector<unsigned char>*)callbackData);
    buf.insert(buf.end(), (unsigned char*)data, (unsigned char*)data + size);
    return 0;
}

static bool TestBase64Str(
    const char* str,
    const char* expect)
{
    vector<char> buf;

    int r = Base64Enc(
        str, 
        strlen(str), 
        TestBase64EncCallback,
        &buf);

    if (r != 0)
        return false;

    return memcmp(&buf[0], expect, buf.size()) == 0;
}

static int TestBase64Aux(const void* data, size_t size)
{
    // Encode:

    vector<char> enc;

    if (Base64Enc(data, size, TestBase64EncCallback, &enc) != 0)
        return -1;

#if 0
    printf("enc{%.*s}\n", (int)enc.size(), &enc[0]);
#endif

    // Decode:

    vector<unsigned char> dec;

    if (Base64Dec(&enc[0], enc.size(), TestBase64DecCallback, &dec) == -1)
        return -1;

#if 0
    printf("dec{%.*s}\n", (int)dec.size(), &dec[0]);
#endif

    // Verify:

    if (dec.size() != size)
        return -1;

    if (memcmp(&dec[0], data, size) != 0)
        return -1;

    return 0;
}

NitsTestWithSetup(TestBase64, TestBaseSetup)
{
    TEST_ASSERT(TestBase64Str("a", "YQ=="));
    TEST_ASSERT(TestBase64Str("ab", "YWI="));
    TEST_ASSERT(TestBase64Str("abc", "YWJj"));
    TEST_ASSERT(TestBase64Str("abcd", "YWJjZA=="));
    TEST_ASSERT(TestBase64Str("abcde", "YWJjZGU="));
    TEST_ASSERT(TestBase64Str("Hello World!", "SGVsbG8gV29ybGQh"));
    TEST_ASSERT(TestBase64Str("hello", "aGVsbG8="));
    TEST_ASSERT(TestBase64Str(
        "Come what, come may; time and the hour run through the roughest day",
        "Q29tZSB3aGF0LCBjb21lIG1heTsgdGltZSBhbmQgdGhlIGhvdXIgcnVuIHRocm91Z2ggdGhlIHJvdWdoZXN0IGRheQ=="));

    TEST_ASSERT(TestBase64Aux("a", 1) == 0);
    TEST_ASSERT(TestBase64Aux("ab", 2) == 0);
    TEST_ASSERT(TestBase64Aux("abc", 3) == 0);

    // Generate random data for varying lengths:

    for (size_t i = 0; i < 1024; i++)
    {
        vector<unsigned char> data;

        for (size_t j = 0; j < i; j++)
        {
            data.push_back(rand() % 256);
        }

        TEST_ASSERT(TestBase64Aux(&data[0], data.size()) == 0);
    }
}
NitsEndTest

NitsTestWithSetup(TestStrCopy, TestBaseSetup)
{
    TChar zbuf[64];

    Tcslcpy(zbuf, PAL_T("Hello World"), MI_COUNT(zbuf));
    TEST_ASSERT(Tcscmp(zbuf, PAL_T("Hello World")) == 0);
}
NitsEndTest

extern "C" void MI_MAIN_CALL test_base_Free(void* ptr)
{
    PAL_Free(ptr);
}

NitsTestWithSetup(TestPtrArray, TestBaseSetup)
{
    PtrArray pa;

    memset(&pa, 0, sizeof(pa));

    if(!TEST_ASSERT(PtrArray_Construct(&pa, 16, test_base_Free) == 0))
        NitsReturn;

    if(!TEST_ASSERT(PtrArray_Append(&pa, PAL_Strdup("Red")) == 0))
        goto Error;
    if(!TEST_ASSERT(PtrArray_Append(&pa, PAL_Strdup("Green")) == 0))
        goto Error;
    if(!TEST_ASSERT(PtrArray_Append(&pa, PAL_Strdup("Blue")) == 0))
        goto Error;

    TEST_ASSERT(pa.size == 3);

    for (size_t i = 0; i < pa.size; i++)
    {
        switch (i)
        {
            case 0:
                TEST_ASSERT(Strcmp((char*)pa.data[i], "Red") == 0);
                break;
            case 1:
                TEST_ASSERT(Strcmp((char*)pa.data[i], "Green") == 0);
                break;
            case 2:
                TEST_ASSERT(Strcmp((char*)pa.data[i], "Blue") == 0);
                break;
        }
    }
Error:
    PtrArray_Destruct(&pa);
}
NitsEndTest

static bool CheckNameLen(const ZChar* name)
{
    return Tcslen(name) == NameLen(name, Hash(name));
}

NitsTestWithSetup(TestHashCode, TestBaseSetup)
{
    TEST_ASSERT(CheckNameLen(PAL_T("a")));
    TEST_ASSERT(CheckNameLen(PAL_T("abc")));
    TEST_ASSERT(CheckNameLen(PAL_T("abcdefg")));
    TEST_ASSERT(CheckNameLen(PAL_T("abcdefghijklmnopqrstuvwxyz")));

    const ZChar* str250 =
        PAL_T("00000000000000000000000000000000000000000000000000")
        PAL_T("00000000000000000000000000000000000000000000000000")
        PAL_T("00000000000000000000000000000000000000000000000000")
        PAL_T("00000000000000000000000000000000000000000000000000")
        PAL_T("00000000000000000000000000000000000000000000000000");

    TEST_ASSERT(CheckNameLen(str250));

    const ZChar* str300 =
        PAL_T("00000000000000000000000000000000000000000000000000")
        PAL_T("00000000000000000000000000000000000000000000000000")
        PAL_T("00000000000000000000000000000000000000000000000000")
        PAL_T("00000000000000000000000000000000000000000000000000")
        PAL_T("00000000000000000000000000000000000000000000000000")
        PAL_T("00000000000000000000000000000000000000000000000000");

    TEST_ASSERT(CheckNameLen(str300));
}
NitsEndTest

//------------------------------------------------------------------------------------------------------
typedef struct _StrandTest
{
    size_t numPost;
    size_t numMiddlePost;
    size_t numPostControl;
    size_t numAck;
    size_t numCancel;
    size_t numFinished;
    size_t numAux;
    size_t numEntryPost;
    size_t numParentPost;
} StrandTest;

static StrandTest strandTest;

NITS_EXTERN_C void _StrandTestPost( _In_ Strand* self, _In_ Message* msg)
{
    ++strandTest.numPost;
}

NITS_EXTERN_C void _StrandTestMiddlePost( _In_ Strand* self_, _In_ Message* msg)
{
    StrandBoth* self = (StrandBoth*)self_;
    ++strandTest.numMiddlePost;
    StrandBoth_PostPassthruLeft( self, msg );
}

NITS_EXTERN_C void _StrandTestPostControl( _In_ Strand* self, _In_ Message* msg) 
{
    ++strandTest.numPostControl;
}

NITS_EXTERN_C void _StrandTestAck( _In_ Strand* self) 
{
    ++strandTest.numAck;
}

NITS_EXTERN_C void _StrandTestCancel( _In_ Strand* self) 
{
    ++strandTest.numCancel;
}

NITS_EXTERN_C void _StrandTestFinished( _In_ Strand* self) 
{
    Strand_Delete( self );
    ++strandTest.numFinished;
}

NITS_EXTERN_C void _StrandTestAux( _In_ Strand* self) 
{
    ++strandTest.numAux;
}

static StrandFT strandUserFT1 = { 
        _StrandTestPost, 
        _StrandTestPostControl, 
        _StrandTestAck, 
        _StrandTestCancel, 
        NULL, 
        _StrandTestFinished,
        NULL,
        _StrandTestAux, 
        _StrandTestAux, 
        _StrandTestAux, 
        _StrandTestAux, 
        _StrandTestAux };

static StrandFT strandUserFT2 = { 
        _StrandTestMiddlePost, 
        _StrandTestPostControl, 
        _StrandTestAck, 
        NULL, 
        NULL, 
        _StrandTestFinished,
        NULL,
        _StrandTestAux, 
        _StrandTestAux, 
        _StrandTestAux,
        _StrandTestAux, 
        _StrandTestAux };

static StrandFT strandUserFTMany = { 
        NULL, 
        NULL, 
        NULL, 
        NULL, 
        NULL, 
        _StrandTestFinished,
        NULL,
        _StrandTestAux,
        _StrandTestAux, 
        _StrandTestAux, 
        _StrandTestAux, 
        _StrandTestAux };
        
STRAND_DEBUGNAME( Strand1 );
STRAND_DEBUGNAME( Strand2 );
STRAND_DEBUGNAME( Strand3 );
STRAND_DEBUGNAME( StrandMany );
STRAND_DEBUGNAME( StrandEntry );
STRAND_DEBUGNAME( StrandEntry2 );

NITS_EXTERN_C void TestStrandOpenCallback( _In_ InteractionOpenParams* interactionParams )
{
    Strand** newStrand = (Strand**)(interactionParams->callbackData);

    *newStrand = Strand_New( STRAND_DEBUG(Strand2) &strandUserFT1, 0, 0, interactionParams );
    if(!TEST_ASSERT( NULL != *newStrand ))
    {
        Strand_FailOpen(interactionParams);
    }
    else
    {
        STRAND_SETTESTSTRANDTHREAD( *newStrand );
    }
}

NitsTestWithSetup(TestStrandSingle, TestBaseSetup)
{
    Strand * strand1 = NULL;
    Strand * strand2 = NULL;
    Message * msg = NULL;
    
    memset( &strandTest, 0, sizeof( StrandTest ) );

    msg = __Message_New( NoOpReqTag, sizeof(Message), 0, 0, CALLSITE);
    if(!TEST_ASSERT( NULL != msg ))
        goto Error;        
    
    strand1 = Strand_New( STRAND_DEBUG(Strand1) &strandUserFT1, 0, 0, NULL );
    if(!TEST_ASSERT( NULL != strand1 ))
        goto Error;        
    STRAND_SETTESTSTRANDTHREAD( strand1 );

    Strand_Open( strand1, TestStrandOpenCallback, &strand2, NULL, MI_FALSE );
    if(!TEST_ASSERT( NULL != strand2 ))
        goto Error; 
    
    TEST_ASSERT( STRAND_TYPE_LEFTMOST == strand1->strandType );
    TEST_ASSERT( !strand1->info.thisAckPending );
    TEST_ASSERT( !strand1->info.otherAckPending );
    TEST_ASSERT( strand1->info.opened );
    TEST_ASSERT( STRAND_TYPE_RIGHTMOST == strand2->strandType );
    TEST_ASSERT( !strand2->info.thisAckPending );
    TEST_ASSERT( !strand2->info.otherAckPending );
    TEST_ASSERT( strand2->info.opened );
    
    Strand_Post( strand2, msg );

    TEST_ASSERT( strand1->info.otherAckPending );
    TEST_ASSERT( strand2->info.thisAckPending );
    TEST_ASSERT( 1 == strandTest.numPost );
    
    Strand_Ack( strand1 );

    TEST_ASSERT( !strand1->info.otherAckPending );
    TEST_ASSERT( !strand2->info.thisAckPending );
    TEST_ASSERT( 1 == strandTest.numAck );

    Strand_PostControl( strand1, msg );

    TEST_ASSERT( !strand1->info.thisAckPending );
    TEST_ASSERT( !strand2->info.otherAckPending );
    TEST_ASSERT( 1 == strandTest.numPostControl );

    Strand_ScheduleAux( strand1, 0 );
    Strand_ScheduleAux( strand1, 1 );
    Strand_ScheduleAux( strand1, 2 );

    TEST_ASSERT( 3 == strandTest.numAux );

    Strand_Close( strand1 );
    _Strand_CheckDelete( strand1 );

    UT_ASSERT( 0 == strandTest.numFinished );

    Strand_Close( strand2 );
    _Strand_CheckDelete( strand2 );

    TEST_ASSERT( 2 == strandTest.numFinished );
    
    Message_Release( msg );
    NitsReturn;
Error:
    if(msg)
        Message_Release( msg );
    if(strand1)
        _Strand_CheckDelete( strand1 );
    if(strand2)
        _Strand_CheckDelete( strand2 );
}
NitsEndTest

NITS_EXTERN_C void TestStrandBothOpenCallback( _In_ InteractionOpenParams* interactionParams )
{
    StrandBoth** newStrand = (StrandBoth**)(interactionParams->callbackData);

    *newStrand = StrandBoth_New( STRAND_DEBUG(Strand2) &strandUserFT2, &strandUserFT2, 0, 0, interactionParams );
    if(!TEST_ASSERT( NULL != *newStrand ))
    {
        Strand_FailOpen(interactionParams);
    }
    else
    {
        STRAND_SETTESTSTRANDTHREAD( &(*newStrand)->base );
    }
}

NitsTestWithSetup(TestStrandBoth, TestBaseSetup)
{
    Strand * strand1 = NULL;
    StrandBoth * strand2 = NULL;
    Strand * strand3 = NULL;
    Message * msg = NULL;
    
    memset( &strandTest, 0, sizeof( StrandTest ) );

    msg = __Message_New( NoOpReqTag, sizeof(Message), 0, 0, CALLSITE); 
    if(!TEST_ASSERT( NULL != msg ))
        goto Error;
    
    strand1 = Strand_New( STRAND_DEBUG(Strand1) &strandUserFT1, 0, 0,NULL );
    if(!TEST_ASSERT( NULL != strand1 ))
        goto Error;
    STRAND_SETTESTSTRANDTHREAD( strand1 );
    
    TEST_ASSERT( STRAND_TYPE_LEFTMOST == strand1->strandType );
    TEST_ASSERT( !strand1->info.thisAckPending );
    TEST_ASSERT( !strand1->info.otherAckPending );
    TEST_ASSERT( !strand1->info.opened );
    
    Strand_Open( strand1, TestStrandBothOpenCallback, &strand2, NULL, MI_FALSE );
    if(!TEST_ASSERT( NULL != strand2 ))
        goto Error; 
        
    TEST_ASSERT( !strand1->info.thisAckPending );
    TEST_ASSERT( !strand1->info.otherAckPending );
    TEST_ASSERT( strand1->info.opened );
    
    TEST_ASSERT( STRAND_TYPE_MIDDLE == strand2->base.strandType );
    TEST_ASSERT( !strand2->base.info.thisAckPending );
    TEST_ASSERT( !strand2->base.info.otherAckPending );
    TEST_ASSERT( strand2->base.info.opened );
    TEST_ASSERT( !strand2->infoRight.thisAckPending );
    TEST_ASSERT( !strand2->infoRight.otherAckPending );
    TEST_ASSERT( !strand2->infoRight.opened );
    
    StrandBoth_Open( strand2, TestStrandOpenCallback, &strand3, NULL, MI_FALSE, MI_FALSE );
    if(!TEST_ASSERT( NULL != strand3 ))
        goto Error; 
    DEBUG_ASSERT( NULL != strand3 );
        
    TEST_ASSERT( !strand2->infoRight.thisAckPending );
    TEST_ASSERT( !strand2->infoRight.otherAckPending );
    TEST_ASSERT( strand2->infoRight.opened );
    
    TEST_ASSERT( STRAND_TYPE_RIGHTMOST == strand3->strandType );
    TEST_ASSERT( !strand3->info.thisAckPending );
    TEST_ASSERT( !strand3->info.otherAckPending );
    TEST_ASSERT( strand3->info.opened );
    
    Strand_Post( strand3, msg );

    TEST_ASSERT( strand1->info.otherAckPending );
    TEST_ASSERT( strand2->base.info.thisAckPending );
    TEST_ASSERT( strand2->infoRight.otherAckPending );
    TEST_ASSERT( strand3->info.thisAckPending );
    TEST_ASSERT( 1 == strandTest.numMiddlePost );
    TEST_ASSERT( 1 == strandTest.numPost );
    
    Strand_Ack( strand1 );

    TEST_ASSERT( !strand1->info.otherAckPending );
    TEST_ASSERT( !strand2->base.info.thisAckPending );
    TEST_ASSERT( !strand2->infoRight.otherAckPending );
    TEST_ASSERT( !strand3->info.thisAckPending );
    TEST_ASSERT( 1 == strandTest.numAck );

    Strand_PostControl( strand1, msg );

    TEST_ASSERT( !strand1->info.thisAckPending );
    TEST_ASSERT( !strand2->base.info.otherAckPending );
    TEST_ASSERT( 1 == strandTest.numPostControl );

    StrandBoth_ScheduleAuxLeft( strand2, 0 );
    StrandBoth_ScheduleAuxLeft( strand2, 1 );
    StrandBoth_ScheduleAuxLeft( strand2, 2 );
    StrandBoth_ScheduleAuxRight( strand2, 0 );
    StrandBoth_ScheduleAuxRight( strand2, 1 );
    StrandBoth_ScheduleAuxRight( strand2, 2 );

    TEST_ASSERT( 6 == strandTest.numAux );
        
    Strand_Close( strand1 );
    _Strand_CheckDelete( strand1 );

    TEST_ASSERT( 0 == strandTest.numFinished );
    TEST_ASSERT( strand1->info.thisClosedOther );
    TEST_ASSERT( !strand1->info.otherClosedThis );
    TEST_ASSERT( !strand2->base.info.thisClosedOther );
    TEST_ASSERT( strand2->base.info.otherClosedThis );
    TEST_ASSERT( strand2->infoRight.thisClosedOther );
    TEST_ASSERT( !strand2->infoRight.otherClosedThis );
    TEST_ASSERT( !strand3->info.thisClosedOther );
    TEST_ASSERT( strand3->info.otherClosedThis );
    
    StrandBoth_CloseLeft( strand2 );
    _Strand_CheckDelete( &strand2->base );

    TEST_ASSERT( 1 == strandTest.numFinished );
    TEST_ASSERT( strand2->base.info.thisClosedOther );
    TEST_ASSERT( strand2->base.info.otherClosedThis );
    TEST_ASSERT( strand2->infoRight.thisClosedOther );
    TEST_ASSERT( !strand2->infoRight.otherClosedThis );

    Strand_Close( strand3 );
    _Strand_CheckDelete( strand3 );

    TEST_ASSERT( 3 == strandTest.numFinished );
    
    Message_Release( msg );
    NitsReturn;
Error:
    if(msg)
        Message_Release( msg );
    if(strand1)
        _Strand_CheckDelete( strand1 );    
    if(strand2)
        _Strand_CheckDelete( &strand2->base );
}
NitsEndTest

NITS_EXTERN_C void TestStrandEnterOpenCallback( _In_ InteractionOpenParams* interactionParams )
{
    Strand** newStrand = (Strand**)(interactionParams->callbackData);

    *newStrand = Strand_New( STRAND_DEBUG(Strand2) &strandUserFT1, 0, STRAND_FLAG_ENTERSTRAND, interactionParams );
    if(!TEST_ASSERT( NULL != *newStrand ))
    {
        Strand_FailOpen(interactionParams);
    }
    else
    {
        STRAND_SETTESTSTRANDTHREAD( *newStrand );
    }
}

NitsTestWithSetup(TestStrandEnter, TestBaseSetup)
{
    Strand * strand1 = NULL;
    Strand * strand2 = NULL;
    Message * msg = NULL;
    
    msg = __Message_New( NoOpReqTag, sizeof(Message), 0, 0, CALLSITE); 
    if(!TEST_ASSERT( NULL != msg ))
        NitsReturn;
    
    memset( &strandTest, 0, sizeof( StrandTest ) );

    strand1 = Strand_New( STRAND_DEBUG(Strand1) &strandUserFT1, 0, STRAND_FLAG_ENTERSTRAND, NULL );
    if(!TEST_ASSERT( NULL != strand1 ))
        NitsReturn;
    
    Strand_Open( strand1, TestStrandEnterOpenCallback, &strand2, NULL, MI_FALSE );
    if(!TEST_ASSERT( NULL != strand2 ))
        NitsReturn; 
    
    TEST_ASSERT( STRAND_TYPE_LEFTMOST == strand1->strandType );
    TEST_ASSERT( !strand1->info.thisAckPending );
    TEST_ASSERT( !strand1->info.otherAckPending );
    TEST_ASSERT( strand1->info.opened );
    TEST_ASSERT( STRAND_TYPE_RIGHTMOST == strand2->strandType );
    TEST_ASSERT( !strand2->info.thisAckPending );
    TEST_ASSERT( !strand2->info.otherAckPending );
    TEST_ASSERT( strand2->info.opened );
    
    Strand_Post( strand2, msg );

    // There should be still not pending on strand1 (because Post couldnt execute)
    TEST_ASSERT( !strand1->info.otherAckPending );
    TEST_ASSERT( strand2->info.thisAckPending );

    Strand_ScheduleAck( strand1 );

    // Thet one should run either
    TEST_ASSERT( !strand1->info.otherAckPending );
    TEST_ASSERT( strand2->info.thisAckPending );
    
    Strand_ScheduleAux( strand1, 0 );
    Strand_ScheduleAux( strand1, 1 );
    Strand_ScheduleAux( strand1, 2 );

    // There should be still pending (because Aux couldnt execute)
    TEST_ASSERT( 0 == strandTest.numAux );

    Strand_Cancel( strand2 );

    TEST_ASSERT( strand2->canceled );
    // There should be still not canceled (because cancel couldnt execute)
    TEST_ASSERT( !strand1->canceled );

    Strand_Close( strand1 );
    Strand_Leave( strand1 );

    // Previous Leave Strand gets the Post/Ack the oportunity to run
    
    TEST_ASSERT( 0 == strandTest.numFinished );

    Strand_Close( strand2 );
    Strand_Leave( strand2 );

    TEST_ASSERT( 2 == strandTest.numFinished );

    // Now we can check those
    TEST_ASSERT( 1 == strandTest.numPost );
    TEST_ASSERT( 1 == strandTest.numAck );
    TEST_ASSERT( 2 == strandTest.numCancel );
    TEST_ASSERT( 3 == strandTest.numAux );
}
NitsEndTest

NITS_EXTERN_C void TestEntryPost( _In_ StrandMany* self, _In_ Message* msg)
{
    ++strandTest.numEntryPost;
    Strand_Post( &self->strand, msg );
}

NITS_EXTERN_C void TestParentPost( _In_ StrandEntry* self, _In_ Message* msg)
{
    ++strandTest.numParentPost;
    Strand_Post( &self->strand, msg );
}

StrandManyInternalFT strandInternalFTMany = { 
        NULL,
        NULL,
        TestEntryPost, 
        NULL, 
        NULL, 
        NULL,
        TestParentPost, 
        NULL,
        NULL,
        NULL };

NITS_EXTERN_C void TestStrandManyOpenCallback( _In_ InteractionOpenParams* interactionParams )
{
    StrandMany** newStrand = (StrandMany**)(interactionParams->callbackData);

    *newStrand = StrandMany_New( STRAND_DEBUG(StrandMany) &strandUserFTMany, &strandInternalFTMany, 0, 0, interactionParams, 3, NULL, NULL, NULL );
    if(!TEST_ASSERT( NULL != *newStrand ))
    {
        Strand_FailOpen(interactionParams);
    }
    else
    {
        STRAND_SETTESTSTRANDTHREAD( &(*newStrand)->strand );
    }
}

NITS_EXTERN_C void TestStrandEntryOpenCallback( _In_ InteractionOpenParams* interactionParams )
{
    Strand** newStrand = (Strand**)(interactionParams->callbackData);

    *newStrand = Strand_New( STRAND_DEBUG(Strand3) &strandUserFT1, 0, 0, interactionParams );
    if(!TEST_ASSERT( NULL != *newStrand ))
    {
        Strand_FailOpen(interactionParams);
    }
    else
    {
        STRAND_SETTESTSTRANDTHREAD( *newStrand );
    }
}

NitsTestWithSetup(TestStrandMany, TestBaseSetup)
{
    Strand * strand1 = NULL;
    StrandMany * strandMany = NULL;
    StrandEntry * strandEntry = NULL;
    StrandEntry * strandEntry2 = NULL;
    Strand * strand3 = NULL;
    Message * msg = NULL;
    MI_Result result;
    
    memset( &strandTest, 0, sizeof( StrandTest ) );

    msg = __Message_New( NoOpReqTag, sizeof(Message), 0, 0, CALLSITE); 
    if(!TEST_ASSERT( NULL != msg ))
        goto Error;
    
    strand1 = Strand_New( STRAND_DEBUG(Strand1) &strandUserFT1, 0, 0, NULL );
    if(!TEST_ASSERT( NULL != strand1 ))
        goto Error; 

    STRAND_SETTESTSTRANDTHREAD( strand1 );
    
    Strand_Open( strand1, TestStrandManyOpenCallback, &strandMany, NULL, MI_FALSE );
    if(!TEST_ASSERT( NULL != strandMany ))
        goto Error; 
    DEBUG_ASSERT( NULL != strandMany );
    
    strandEntry = StrandEntry_New( STRAND_DEBUG(StrandEntry) strandMany, &strandUserFTMany, 0, 0, NULL );
    if(!TEST_ASSERT( NULL != strandEntry ))
        goto Error;
    result = StrandMany_AddEntry( strandEntry );
    TEST_ASSERT( MI_RESULT_OK == result );
    STRAND_SETTESTSTRANDTHREAD( &strandEntry->strand );
    
    Strand_Open( &strandEntry->strand, TestStrandEntryOpenCallback, &strand3, NULL, MI_FALSE );
    if(!TEST_ASSERT( NULL != strand3 ))
        goto Error; 
    
    TEST_ASSERT( STRAND_TYPE_LEFTMOST == strand1->strandType );
    TEST_ASSERT( !strand1->info.thisAckPending );
    TEST_ASSERT( !strand1->info.otherAckPending );
    TEST_ASSERT( strand1->info.opened );
    TEST_ASSERT( STRAND_TYPE_PARENTLEFT == strandMany->strand.strandType );
    TEST_ASSERT( !strandMany->strand.info.thisAckPending );
    TEST_ASSERT( !strandMany->strand.info.otherAckPending );
    TEST_ASSERT( strandMany->strand.info.opened );
    TEST_ASSERT( STRAND_TYPE_ENTRY == strandEntry->strand.strandType );
    TEST_ASSERT( !strandEntry->strand.info.thisAckPending );
    TEST_ASSERT( !strandEntry->strand.info.otherAckPending );
    TEST_ASSERT( strandEntry->strand.info.opened );
    TEST_ASSERT( STRAND_TYPE_RIGHTMOST == strand3->strandType );
    TEST_ASSERT( !strand3->info.thisAckPending );
    TEST_ASSERT( !strand3->info.otherAckPending );
    TEST_ASSERT( strand3->info.opened );
    
    Strand_Post( strand3, msg );

    TEST_ASSERT( strand1->info.otherAckPending );
    TEST_ASSERT( strandMany->strand.info.thisAckPending );
    TEST_ASSERT( !strandEntry->strand.info.otherAckPending );
    TEST_ASSERT( !strand3->info.thisAckPending );
    TEST_ASSERT( 1 == strandTest.numEntryPost );
    TEST_ASSERT( 1 == strandTest.numPost );
    
    Strand_Ack( strand1 );

    TEST_ASSERT( !strand1->info.otherAckPending );
    TEST_ASSERT( !strandMany->strand.info.thisAckPending );
    TEST_ASSERT( 1 == strandTest.numAck );

    Strand_PostControl( strand1, msg );

    TEST_ASSERT( !strand1->info.thisAckPending );
    TEST_ASSERT( !strandMany->strand.info.otherAckPending );
    TEST_ASSERT( 1 == strandTest.numPostControl );

    StrandMany_ScheduleAux( strandMany, 0 );
    StrandMany_ScheduleAux( strandMany, 1 );
    StrandEntry_ScheduleAux( strandEntry, 0 );
    StrandEntry_ScheduleAux( strandEntry, 1 );
    StrandEntry_ScheduleAuxParent( strandEntry, 2 );

    TEST_ASSERT( 5 == strandTest.numAux );

    Strand_Cancel( strand1 );

    TEST_ASSERT( strand1->canceled );
    TEST_ASSERT( strandMany->strand.canceled );
    TEST_ASSERT( strandEntry->strand.canceled );
    TEST_ASSERT( strand3->canceled );

    strandEntry2 = StrandEntry_New( STRAND_DEBUG(StrandEntry2) strandMany, &strandUserFTMany, 0, 0, NULL );
    if(!TEST_ASSERT( NULL != strandEntry2 ))
        goto Error;
    result = StrandMany_AddEntry( strandEntry2 );
    TEST_ASSERT( MI_RESULT_OK == result );
    STRAND_SETTESTSTRANDTHREAD( &strandEntry2->strand );

    TEST_ASSERT( strandMany->numEntries == 2 );

    StrandEntry_Delete( strandEntry2 );
    
    TEST_ASSERT( strandMany->numEntries == 1 );

    Strand_Close( strand1 );
    _Strand_CheckDelete( strand1 );

    TEST_ASSERT( 0 == strandTest.numFinished );
    TEST_ASSERT( strand1->info.thisClosedOther );
    TEST_ASSERT( !strand1->info.otherClosedThis );
    TEST_ASSERT( !strandMany->strand.info.thisClosedOther );
    TEST_ASSERT( strandMany->strand.info.otherClosedThis );
    TEST_ASSERT( strandEntry->strand.info.thisClosedOther );
    TEST_ASSERT( !strandEntry->strand.info.otherClosedThis );
    TEST_ASSERT( !strand3->info.thisClosedOther );
    TEST_ASSERT( strand3->info.otherClosedThis );

    Strand_Close( &strandMany->strand );
    _Strand_CheckDelete( &strandMany->strand );

    TEST_ASSERT( 1 == strandTest.numFinished );
    TEST_ASSERT( strandMany->strand.info.thisClosedOther );
    TEST_ASSERT( strandMany->strand.info.otherClosedThis );
    TEST_ASSERT( strandEntry->strand.info.thisClosedOther );
    TEST_ASSERT( !strandEntry->strand.info.otherClosedThis );

    Strand_Close( strand3 );
    _Strand_CheckDelete( strand3 );

    TEST_ASSERT( 4 == strandTest.numFinished );

    Message_Release( msg );
    NitsReturn;
Error:
    if(msg) Message_Release( msg );
    if(strand1) _Strand_CheckDelete( strand1 );
    if(strandMany) _Strand_CheckDelete( &strandMany->strand );
    if(strand3) _Strand_CheckDelete( strand3 );
    if(strandEntry) StrandEntry_Delete( strandEntry );
    if(strandEntry2) StrandEntry_Delete( strandEntry2 );    
}
NitsEndTest

NitsTestWithSetup(TestOctet, TestBaseSetup)
{
    MI_Instance* base;
    Octet* inst;
    MI_ClassDecl* cd;
    MI_Result r;
    FILE* os;
    Batch batch = BATCH_INITIALIZER;

    cd = SchemaDecl_FindClassDecl(
        &test_repos_classDecl, PAL_T("Octet"));
    TEST_ASSERT(cd != NULL);

    Batch_Init(&batch, BATCH_MAX_PAGES);
    r = Instance_New(&base, cd, &batch);
    if(!TEST_ASSERT(r == MI_RESULT_OK))
        NitsReturn;
    inst = (Octet*)base;


    /* Octet uint8 string */
    {
        MI_Char data[] = PAL_T("YQ=="); // "a" encoded
        r = Instance_SetElementFromString(base, PAL_T("array"), data, WSMANFlag);
        TEST_ASSERT(r == MI_RESULT_OK);
        if (r == MI_RESULT_OK)
        {
            TEST_ASSERT(inst->array.value.size == 5);
            if (inst->array.value.size == 5)
            {
                TEST_ASSERT(inst->array.value.data[0] == 0);
                TEST_ASSERT(inst->array.value.data[1] == 0);
                TEST_ASSERT(inst->array.value.data[2] == 0);
                TEST_ASSERT(inst->array.value.data[3] == 5);
                TEST_ASSERT(inst->array.value.data[4] == 'a');
            }
        }
    }

    /* Print */
    os = outStream;
    TEST_ASSERT(os);
    MI_Instance_Print(base, os, 0);

    /* Convert */
    {
        Octet conv;
        memset(&conv, 0, sizeof(Octet));
        r = Instance_InitConvert(
            (MI_Instance*)&conv, 
            cd, 
            base, 
            MI_FALSE,  /* Keys only */
            MI_FALSE, /* allow-keyless */
            MI_TRUE, /* copy */
            &batch, WSMANFlag);
        TEST_ASSERT(r == MI_RESULT_OK);
        if(r != MI_RESULT_OK)
            NitsReturn;
        MI_Instance_Destruct((MI_Instance*)&conv);
    }

    {
        MI_Instance* dinst = NULL;
        Octet sinst;
        memset(&sinst, 0, sizeof(sinst));

        /* Create a dynamic instance will all string properties */
        r = Instance_NewDynamic(&dinst, PAL_T("Octet"), MI_FLAG_CLASS,
            &batch);
        TEST_ASSERT(r == MI_RESULT_OK);
        if(TEST_ASSERT(dinst != NULL))
        {
            r = AddString(dinst, PAL_T("array"), PAL_T("YQ=="));
            TEST_ASSERT(r == MI_RESULT_OK);

    #if 0
            MI_Instance_Print(dinst, stdout, 0);
    #endif
            /* Convert to static instance */
            r = Instance_InitConvert(
                (MI_Instance*)&sinst, 
                cd, 
                dinst, 
                MI_FALSE, /* Keys only */
                MI_FALSE, /* allow-keyless */
                MI_TRUE,  /* copy */
                &batch, WSMANFlag);
            TEST_ASSERT(r == MI_RESULT_OK);        
    #if 0
            MI_Instance_Print(&sinst.__instance, stdout, 0);
    #endif

            TEST_ASSERT(sinst.array.exists == 1);
            TEST_ASSERT(sinst.array.value.size == 5);
            if (sinst.array.value.size == 5)
            {
                TEST_ASSERT(sinst.array.value.data[0] == 0);
                TEST_ASSERT(sinst.array.value.data[1] == 0);
                TEST_ASSERT(sinst.array.value.data[2] == 0);
                TEST_ASSERT(sinst.array.value.data[3] == 5);
                TEST_ASSERT(sinst.array.value.data[4] == 'a');
            }

            MI_Instance_Destruct((MI_Instance*)&sinst);
            MI_Instance_Delete(dinst);
        }
    }

    MI_Instance_Delete(base);

    Batch_Destroy(&batch);
}
NitsEndTest

NitsTestWithSetup(TestOctet_Empty, TestBaseSetup)
{
    MI_Instance* base;
    Octet* inst;
    MI_ClassDecl* cd;
    MI_Result r;
    Batch batch = BATCH_INITIALIZER;

    cd = SchemaDecl_FindClassDecl(
        &test_repos_classDecl, PAL_T("Octet"));
    TEST_ASSERT(cd != NULL);

    Batch_Init(&batch, BATCH_MAX_PAGES);
    r = Instance_New(&base, cd, &batch);
    if (!TEST_ASSERT(r == MI_RESULT_OK))
        NitsReturn;
    inst = (Octet*)base;

    /* Octet uint8 string */
    {
        MI_Char data[] = PAL_T(""); // an empty array
        r = Instance_SetElementFromString(base, PAL_T("array"), data, WSMANFlag);
        TEST_ASSERT(r == MI_RESULT_OK);
        if (r == MI_RESULT_OK)
        {
            TEST_ASSERT(inst->array.value.size == 4);
            if (inst->array.value.size == 4)
            {
                TEST_ASSERT(inst->array.value.data[0] == 0);
                TEST_ASSERT(inst->array.value.data[1] == 0);
                TEST_ASSERT(inst->array.value.data[2] == 0);
                TEST_ASSERT(inst->array.value.data[3] == 4);
            }
        }
    }

    MI_Instance_Delete(base);

    Batch_Destroy(&batch);
}
NitsEndTest

NitsTestWithSetup(TestDatetime_Asterisk, TestBaseSetup)
{
    /* a timestamp (YYYYMMDDHHMMSS.MMMMMMSUTC) */
    {
        MI_Value v;
        int x = StrToDatetime(PAL_T("20141231120101.123456+360"), &v.datetime);
        TEST_ASSERT(x == 0);
        TEST_ASSERT(v.datetime.u.timestamp.year == 2014);
        TEST_ASSERT(v.datetime.u.timestamp.month == 12);
        TEST_ASSERT(v.datetime.u.timestamp.day == 31);
        TEST_ASSERT(v.datetime.u.timestamp.hour == 12);
        TEST_ASSERT(v.datetime.u.timestamp.minute == 1);
        TEST_ASSERT(v.datetime.u.timestamp.second == 1);
        TEST_ASSERT(v.datetime.u.timestamp.microseconds == 123456);
        TEST_ASSERT(v.datetime.u.timestamp.utc == 360);
    }
    {
        MI_Value v;
        int x = StrToDatetime(PAL_T("****1231120101.123456+360"), &v.datetime);
        TEST_ASSERT(x == 0);
        TEST_ASSERT(v.datetime.u.timestamp.year == 0); //
        TEST_ASSERT(v.datetime.u.timestamp.month == 12);
        TEST_ASSERT(v.datetime.u.timestamp.day == 31);
        TEST_ASSERT(v.datetime.u.timestamp.hour == 12);
        TEST_ASSERT(v.datetime.u.timestamp.minute == 1);
        TEST_ASSERT(v.datetime.u.timestamp.second == 1);
        TEST_ASSERT(v.datetime.u.timestamp.microseconds == 123456);
        TEST_ASSERT(v.datetime.u.timestamp.utc == 360);
    }
    {
        MI_Value v;
        int x = StrToDatetime(PAL_T("****12**120101.123456+360"), &v.datetime);
        TEST_ASSERT(x == 0);
        TEST_ASSERT(v.datetime.u.timestamp.year == 0); //
        TEST_ASSERT(v.datetime.u.timestamp.month == 12);
        TEST_ASSERT(v.datetime.u.timestamp.day == 0); //
        TEST_ASSERT(v.datetime.u.timestamp.hour == 12);
        TEST_ASSERT(v.datetime.u.timestamp.minute == 1);
        TEST_ASSERT(v.datetime.u.timestamp.second == 1);
        TEST_ASSERT(v.datetime.u.timestamp.microseconds == 123456);
        TEST_ASSERT(v.datetime.u.timestamp.utc == 360);
    }
    {
        MI_Value v;
        int x = StrToDatetime(PAL_T("**********0101.123456-360"), &v.datetime);
        TEST_ASSERT(x == 0);
        TEST_ASSERT(v.datetime.u.timestamp.year == 0); //
        TEST_ASSERT(v.datetime.u.timestamp.month == 0); //
        TEST_ASSERT(v.datetime.u.timestamp.day == 0); //
        TEST_ASSERT(v.datetime.u.timestamp.hour == 0); //
        TEST_ASSERT(v.datetime.u.timestamp.minute == 1);
        TEST_ASSERT(v.datetime.u.timestamp.second == 1);
        TEST_ASSERT(v.datetime.u.timestamp.microseconds == 123456);
        TEST_ASSERT(v.datetime.u.timestamp.utc == -360);
    }

    /* an interval (DDDDDDDDHHMMSS.MMMMMM:000) */
    {
        MI_Value v;
        int x = StrToDatetime(PAL_T("00000022113344.123456:000"), &v.datetime);
        TEST_ASSERT(x == 0);
        TEST_ASSERT(v.datetime.u.interval.days == 22);
        TEST_ASSERT(v.datetime.u.interval.hours == 11);
        TEST_ASSERT(v.datetime.u.interval.minutes == 33);
        TEST_ASSERT(v.datetime.u.interval.seconds == 44);
        TEST_ASSERT(v.datetime.u.interval.microseconds == 123456);
    }
    {
        MI_Value v;
        int x = StrToDatetime(PAL_T("********113344.123456:000"), &v.datetime);
        TEST_ASSERT(x == 0);
        TEST_ASSERT(v.datetime.u.interval.days == 0); //
        TEST_ASSERT(v.datetime.u.interval.hours == 11);
        TEST_ASSERT(v.datetime.u.interval.minutes == 33);
        TEST_ASSERT(v.datetime.u.interval.seconds == 44);
        TEST_ASSERT(v.datetime.u.interval.microseconds == 123456);
    }
    {
        MI_Value v;
        int x = StrToDatetime(PAL_T("************44.123456:000"), &v.datetime);
        TEST_ASSERT(x == 0);
        TEST_ASSERT(v.datetime.u.interval.days == 0); //
        TEST_ASSERT(v.datetime.u.interval.hours == 0); //
        TEST_ASSERT(v.datetime.u.interval.minutes == 0); //
        TEST_ASSERT(v.datetime.u.interval.seconds == 44);
        TEST_ASSERT(v.datetime.u.interval.microseconds == 123456);
    }
    {
        MI_Value v;
        int x = StrToDatetime(PAL_T("**************.******:000"), &v.datetime);
        TEST_ASSERT(x == 0);
        TEST_ASSERT(v.datetime.u.interval.days == 0); //
        TEST_ASSERT(v.datetime.u.interval.hours == 0); //
        TEST_ASSERT(v.datetime.u.interval.minutes == 0); //
        TEST_ASSERT(v.datetime.u.interval.seconds == 0); //
        TEST_ASSERT(v.datetime.u.interval.microseconds == 0); //
    }
}
NitsEndTest

#ifdef _PREFAST_
#pragma prefast (pop)
#endif

