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

#include <vector>
#include <algorithm>
#include <ut/ut.h>
#include <base/base.h>
#include <base/buf.h>
#include <base/batch.h>
#include <base/strings.h>
#include <base/paths.h>
#include <base/conf.h>
#include <base/dir.h>
#include <base/log.h>
#include <io/io.h>
#include <base/strarr.h>
#include <base/getopt.h>
#include <base/hashtable.h>
#include <base/miextras.h>
#include <base/base64.h>
#include "MSFT_AllTypes.h"
#include "MSFT_Process.h"
#include <base/ptrarray.h>
#include <base/naming.h>

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

static void setUp()
{
#if defined(ENABLE_PRINT)
    outStream = stdout;
#else
    outStream = Fopen(NULL_FILE, "w");
#endif
    srcdir = GetPath(ID_SRCDIR);
}

static void cleanup()
{
#if defined(ENABLE_PRINT)
    outStream = NULL;
#else
    fclose(outStream);
    outStream = NULL;
#endif
}

static void MemTest(const char* data, char ch, size_t size)
{
    size_t i;

    for (i = 0; i < size; i++)
    {
        if (data[i] != ch)
            UT_ASSERT_FAILED_MSG("Memcheck failed");
    }
}

static void TestAllocator1()
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
        UT_ASSERT(p != NULL);

        memset(p, i % 256, i);
        blocks[i] = p;
    }

    // First chunk is 1 bytes as offset 0:
    UT_ASSERT(data[0] == 1);

    // Second chunk is 2 bytes as offset 8:
    UT_ASSERT(data[8+0] == 2);
    UT_ASSERT(data[8+1] == 2);

    // Third chunk is 3 bytes as offset 16:
    UT_ASSERT(data[16+0] == 3);
    UT_ASSERT(data[16+1] == 3);

    // Fourth chunk is 4 bytes as offset 24:
    UT_ASSERT(data[24+0] == 4);
    UT_ASSERT(data[24+1] == 4);

    // Fifth chunk is 5 bytes as offset 32:
    UT_ASSERT(data[32+0] == 5);
    UT_ASSERT(data[32+1] == 5);

    for (i = 1; i < N; i++)
    {
        char* p = blocks[i];
        UT_ASSERT(p != NULL);

        MemTest(p, i % 256, i);
    }

    Batch_Destroy(&a);
}

static void TestAllocator2()
{
    Batch batch = BATCH_INITIALIZER;
    char* blocks[512];
    const size_t N = sizeof(blocks) / sizeof(blocks[0]);
    size_t i;

    for (i = 1; i < N; i++)
    {
        char* p = (char*)Batch_Get(&batch, i);
        UT_ASSERT(p != NULL);

        memset(p, i % 256, i);
        blocks[i] = p;
    }

    for (i = 1; i < N; i++)
    {
        char* p = blocks[i];
        UT_ASSERT(p != NULL);

        MemTest(p, i % 256, i);
    }

    Batch_Destroy(&batch);
    memset(&batch, 0, sizeof(batch));
}

static void TestAllocator3()
{
    Batch* batch;
    char* blocks[512];
    const size_t N = sizeof(blocks) / sizeof(blocks[0]);
    size_t i;

    batch = Batch_New(8);
    UT_ASSERT(batch != NULL);

    for (i = 1; i < N; i++)
    {
        char* p = (char*)Batch_Get(batch, i);
        UT_ASSERT(p != NULL);

        memset(p, i % 256, i);
        blocks[i] = p;
    }

    for (i = 1; i < N; i++)
    {
        char* p = blocks[i];
        UT_ASSERT(p != NULL);

        MemTest(p, i % 256, i);
    }

    Batch_Delete(batch);
}

static void TestGetName()
{
    UT_ASSERT(strcmp(Type_NameOf(MI_BOOLEAN), "BOOLEAN") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_UINT8), "UINT8") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_SINT8), "SINT8") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_UINT16), "UINT16") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_SINT16), "SINT16") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_UINT32), "UINT32") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_SINT32), "SINT32") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_UINT64), "UINT64") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_SINT64), "SINT64") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_REAL32), "REAL32") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_REAL64), "REAL64") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_CHAR16), "CHAR16") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_DATETIME), "DATETIME") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_STRING), "STRING") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_REFERENCE), "REFERENCE") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_INSTANCE), "INSTANCE") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_BOOLEANA), "BOOLEANA") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_UINT8A), "UINT8A") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_SINT8A), "SINT8A") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_UINT16A), "UINT16A") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_SINT16A), "SINT16A") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_UINT32A), "UINT32A") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_SINT32A), "SINT32A") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_UINT64A), "UINT64A") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_SINT64A), "SINT64A") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_REAL32A), "REAL32A") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_REAL64A), "REAL64A") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_CHAR16A), "CHAR16A") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_DATETIMEA), "DATETIMEA") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_STRINGA), "STRINGA") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_REFERENCEA), "REFERENCEA") == 0);
    UT_ASSERT(strcmp(Type_NameOf(MI_INSTANCEA), "INSTANCEA") == 0);
}

static void TestGetSize()
{
    UT_ASSERT(Type_SizeOf(MI_BOOLEAN) == sizeof(MI_Boolean));
    UT_ASSERT(Type_SizeOf(MI_UINT8) == sizeof(MI_Uint8));
    UT_ASSERT(Type_SizeOf(MI_SINT8) == sizeof(MI_Sint8));
    UT_ASSERT(Type_SizeOf(MI_UINT16) == sizeof(MI_Uint16));
    UT_ASSERT(Type_SizeOf(MI_SINT16) == sizeof(MI_Sint16));
    UT_ASSERT(Type_SizeOf(MI_UINT32) == sizeof(MI_Uint32));
    UT_ASSERT(Type_SizeOf(MI_SINT32) == sizeof(MI_Sint32));
    UT_ASSERT(Type_SizeOf(MI_UINT64) == sizeof(MI_Uint64));
    UT_ASSERT(Type_SizeOf(MI_SINT64) == sizeof(MI_Sint64));
    UT_ASSERT(Type_SizeOf(MI_REAL32) == sizeof(MI_Real32));
    UT_ASSERT(Type_SizeOf(MI_REAL64) == sizeof(MI_Real64));
    UT_ASSERT(Type_SizeOf(MI_CHAR16) == sizeof(MI_Char16));
    UT_ASSERT(Type_SizeOf(MI_DATETIME) == sizeof(MI_Datetime));
    UT_ASSERT(Type_SizeOf(MI_STRING) == sizeof(MI_String));
    UT_ASSERT(Type_SizeOf(MI_REFERENCE) == sizeof(MI_Instance*));
    UT_ASSERT(Type_SizeOf(MI_INSTANCE) == sizeof(MI_Instance*));
    UT_ASSERT(Type_SizeOf(MI_BOOLEANA) == sizeof(MI_BooleanA));
    UT_ASSERT(Type_SizeOf(MI_UINT8A) == sizeof(MI_Uint8A));
    UT_ASSERT(Type_SizeOf(MI_SINT8A) == sizeof(MI_Sint8A));
    UT_ASSERT(Type_SizeOf(MI_UINT16A) == sizeof(MI_Uint16A));
    UT_ASSERT(Type_SizeOf(MI_SINT16A) == sizeof(MI_Sint16A));
    UT_ASSERT(Type_SizeOf(MI_UINT32A) == sizeof(MI_Uint32A));
    UT_ASSERT(Type_SizeOf(MI_SINT32A) == sizeof(MI_Sint32A));
    UT_ASSERT(Type_SizeOf(MI_UINT64A) == sizeof(MI_Uint64A));
    UT_ASSERT(Type_SizeOf(MI_SINT64A) == sizeof(MI_Sint64A));
    UT_ASSERT(Type_SizeOf(MI_REAL32A) == sizeof(MI_Real32A));
    UT_ASSERT(Type_SizeOf(MI_REAL64A) == sizeof(MI_Real64A));
    UT_ASSERT(Type_SizeOf(MI_CHAR16A) == sizeof(MI_Char16A));
    UT_ASSERT(Type_SizeOf(MI_DATETIMEA) == sizeof(MI_DatetimeA));
    UT_ASSERT(Type_SizeOf(MI_STRINGA) == sizeof(MI_StringA));
    UT_ASSERT(Type_SizeOf(MI_REFERENCEA) == sizeof(MI_ReferenceA));
    UT_ASSERT(Type_SizeOf(MI_INSTANCEA) == sizeof(MI_InstanceA));
}

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
    cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, ZT("MSFT_Person"));
    UT_ASSERT(cd != NULL);

    /* Create instance of MSFT_Person */
    r = Instance_New(&inst, cd, batch);
    UT_ASSERT(r == MI_RESULT_OK);

    /* CIM_Person.Key */
    value.uint32 = key;
    r = MI_Instance_SetElement(inst, MI_T("Key"), &value, MI_UINT32, 0);
    UT_ASSERT(r == MI_RESULT_OK);

    /* CIM_Person.First */
    value.string = (ZChar*)first;
    r = MI_Instance_SetElement(inst, MI_T("First"), &value, MI_STRING, 0);
    UT_ASSERT(r == MI_RESULT_OK);

    /* CIM_Person.Last */
    value.string = (ZChar*)last;
    r = MI_Instance_SetElement(inst, MI_T("Last"), &value, MI_STRING, 0);
    UT_ASSERT(r == MI_RESULT_OK);

    return inst;
}

static void TestStringArray1(void)
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

    StringArray_Init(&sa, size, &batch);

    for (i = 0; i < size; i++)
    {
        r = StringArray_Add(&sa, data[i]);
        UT_ASSERT(r == MI_RESULT_OK);
    }

    UT_ASSERT(sa.size == size);
    r = StringArray_Add(&sa, MI_T("Never"));
    UT_ASSERT(r == MI_RESULT_FAILED);

#if 0
    StringArray_Print(&sa, stdout);
#endif

    for (i = 0; i < size; i++)
    {
        UT_ASSERT(Zcasecmp(sa.data[i], data[i]) == 0);
    }

    Batch_Destroy(&batch);
}

static void TestStringArray2(void)
{
    Batch batch = BATCH_INITIALIZER;
    StringArray sa;
    static const size_t N = 12345;
    size_t i;

    StringArray_Init(&sa, N, &batch);

    for (i = 0; i < N; i++)
    {
        MI_Result r;
        ZChar buf[32];
        Szprintf(buf, MI_COUNT(buf), MI_T("%d"), (int)i);
        r = StringArray_Add(&sa, buf);
        UT_ASSERT(r == MI_RESULT_OK);
    }

    UT_ASSERT(sa.size == N);

    for (i = 0; i < N; i++)
    {
        ZChar buf[32];
        Szprintf(buf, MI_COUNT(buf), MI_T("%d"), (int)i);
        Zcasecmp(sa.data[i], buf);
    }

    Batch_Destroy(&batch);
}

void TestMessages()
{
    MI_Result r;
    MI_Instance* instanceName;
    GetInstanceReq* req;
    PostInstanceMsg* rsp;
    MI_Value value;
    MI_Uint64 msgID;
    StringArray propertySet;
    const MI_ClassDecl* cd;
    Batch* b = NULL;

    /* Set the msgID */
    msgID = 12345;

    /* Build GetInstance message */
    req = GetInstanceReq_New(msgID, BinaryProtocolFlag);
    UT_ASSERT(req);

    /* Use the message's batch for all allocations */
    b = req->base.batch;
    UT_ASSERT(b);

    /* Create an instance name */
    {
        cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, 
            ZT("MSFT_Person"));
        UT_ASSERT(cd != NULL);

        r = Instance_New(&instanceName, cd, b);
        UT_ASSERT(r == MI_RESULT_OK);

        value.string = (ZChar*)MI_T("CIM_Person");
        MI_Instance_SetElement(instanceName, MI_T("__CLASS"), &value, MI_STRING, 0);

        value.uint32 = 1234;
        MI_Instance_SetElement(instanceName, MI_T("Key"), &value, MI_UINT32, 0);
    }

    /* Build a property list */
    {
        StringArray_Init(&propertySet, 2, b);
        r = StringArray_Add(&propertySet, MI_T("First"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = StringArray_Add(&propertySet, MI_T("Last"));
        UT_ASSERT(r == MI_RESULT_OK);
    }

    req->instanceName = instanceName;
    req->propertySet = &propertySet;

    GetInstanceReq_Print(req, outStream);

    /* Create response */
    rsp = PostInstanceMsg_New(msgID);
    UT_ASSERT(rsp);

    rsp->instance = NewPerson(1, MI_T("George"), MI_T("Washington"), b);
    UT_ASSERT(rsp);

    PostInstanceMsg_Print(rsp, outStream);

    /* Destroy instances */
    MI_Instance_Delete(instanceName);
    MI_Instance_Delete(rsp->instance);

    /* Destroy the messages */
    GetInstanceReq_Release(req);
    PostInstanceMsg_Release(rsp);
}

void TestMessages2()
{
    EnumerateInstancesReq* req;
    MI_Uint64 msgID;
    StringArray propertySet;
    Batch* b = NULL;

    /* Set the msgID */
    msgID = 45678;

    /* EnumerateInstancesReq */
    req = EnumerateInstancesReq_New(msgID, BinaryProtocolFlag);
    UT_ASSERT(req);

    /* Use the messages's batch for all allocations */
    b = req->base.batch;

    /* EnumerateInstancesReq.className */
    req->className = (ZChar*)Batch_Zdup(b, MI_T("CIM_Person"));

    if (!req->className)
    {
        UT_ASSERT("Out of memory" && NULL);
        EnumerateInstancesReq_Release(req);
        return;
    }

    /* EnumerateInstancesReq.deepInheritance */
    req->deepInheritance = MI_TRUE;

    /* EnumerateInstancesReq.propertySet */
    {
        MI_Result r;
        StringArray_Init(&propertySet, 3, b);
        r = StringArray_Add(&propertySet, MI_T("Key"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = StringArray_Add(&propertySet, MI_T("First"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = StringArray_Add(&propertySet, MI_T("Last"));
        UT_ASSERT(r == MI_RESULT_OK);
        req->propertySet = &propertySet;
    }

    EnumerateInstancesReq_Print(req, outStream);

    /* Destroy the message */
    EnumerateInstancesReq_Release(req);
}

static void TestStrings()
{
    char buf[1024];
    size_t n;

    memset(buf, 0xFF, sizeof(buf));
    n = Strlcpy(buf, "abc", 8);
    UT_ASSERT(strcmp(buf, "abc") == 0);
    UT_ASSERT(n == 3);

    memset(buf, 0xFF, sizeof(buf));
    n = Strlcpy(buf, "abc", 3);
    UT_ASSERT(strcmp(buf, "ab") == 0);
    UT_ASSERT(n == 3);

    memset(buf, 0xFF, sizeof(buf));
    n = Strlcpy(buf, "", 1);
    UT_ASSERT(strcmp(buf, "") == 0);
    UT_ASSERT(n == 0);

    memset(buf, 0xFF, sizeof(buf));
    n = Strlcpy(buf, "a", 2);
    UT_ASSERT(strcmp(buf, "a") == 0);
    UT_ASSERT(n == 1);

    memset(buf, 0xFF, sizeof(buf));
    Strlcpy(buf, "aaa", 8);
    Strlcat(buf, "bbb", 8);
    n = Strlcat(buf, "ccc", 8);
    UT_ASSERT(strcmp(buf, "aaabbbc") == 0);
    UT_ASSERT(n == 3);

    n = Strlcat(buf, "ccddd", 10);
    UT_ASSERT(strcmp(buf, "aaabbbccc") == 0);
    UT_ASSERT(n == 5);
}

typedef struct _Elem
{
    struct _Elem* next;
    struct _Elem* prev;
    int num;
}
Elem;

static void TestList()
{
    Elem* head = NULL;
    Elem* tail = NULL;
    Elem* p;

    /* Insert some elements */
    {
        Elem* e = (Elem*)malloc(sizeof(Elem));
        UT_ASSERT(e != NULL);
        e->num = 1;
        List_Prepend(
            (ListElem**)&head, (ListElem**)&tail, (ListElem*)e);
    }
    {
        Elem* e = (Elem*)malloc(sizeof(Elem));
        UT_ASSERT(e != NULL);
        e->num = 2;
        List_Prepend(
            (ListElem**)&head, (ListElem**)&tail, (ListElem*)e);
    }
    {
        Elem* e = (Elem*)malloc(sizeof(Elem));
        UT_ASSERT(e != NULL);
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
                    UT_ASSERT(p->num == 2);
                    break;
                case 1:
                    UT_ASSERT(p->num == 1);
                    break;
                case 2:
                    UT_ASSERT(p->num == 3);
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
        free(tmp);
    }

    /* Test contents */
    {
        int i;

        for (i = 0, p = head; p; p = p->next, i++)
        {
            switch (i)
            {
                case 0:
                    UT_ASSERT(p->num == 1);
                    break;
                case 1:
                    UT_ASSERT(p->num == 3);
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
        free(tmp);
    }

    /* Test contents */
    {
        int i;

        for (i = 0, p = head; p; p = p->next, i++)
        {
            switch (i)
            {
                case 0:
                    UT_ASSERT(p->num == 1);
                    break;
                default:
                    UT_ASSERT_FAILED_MSG("unexpected");
            }
        }
    }

    UT_ASSERT(head == tail);

    /* Remove final element */
    {
        Elem* tmp = head;
        List_Remove(
            (ListElem**)&head, (ListElem**)&tail, (ListElem*)head);
        free(tmp);
    }

    UT_ASSERT(head == tail);
    UT_ASSERT(head == NULL);
    UT_ASSERT(tail == NULL);
}

static void TestFindClassDecl()
{
    MI_ClassDecl* cd;
    MI_MethodDecl* md;

    cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, ZT("MSFT_Person"));
    UT_ASSERT(cd != NULL);

    md = ClassDecl_FindMethodDecl(cd, ZT("NoSuchMethod"));
    UT_ASSERT(md == NULL);
    cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, ZT("NoSuchClass"));
    UT_ASSERT(cd == NULL);

    md = ClassDecl_FindMethodDecl(cd, ZT("NoSuchMethod"));
    UT_ASSERT(md == NULL);

    md = ClassDecl_FindMethodDecl(0, 0);
    UT_ASSERT(md == NULL);
}

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
        &test_repos_classDecl, ZT("MSFT_AllTypes"));
    UT_ASSERT(cd != NULL);

    r = Instance_New(&base, cd, batch);
    UT_ASSERT(r == MI_RESULT_OK);
    inst = (MSFT_AllTypes*)base;

    /* Key*/
#if 0
    r = Instance_SetElementFromString(base, ZT("Key"), ZT("1234"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Key.exists == 1);
    UT_ASSERT(inst->Key.value == 1234);
#endif

    /* BooleanValue */
    r = Instance_SetElementFromString(base, ZT("BooleanValue"), ZT("TRUE"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->BooleanValue.exists == 1);
    UT_ASSERT(inst->BooleanValue.value == 1);

    /* BooleanValue */
    r = Instance_SetElementFromString(base, ZT("BooleanValue"), ZT("FALSE"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->BooleanValue.exists == 1);
    UT_ASSERT(inst->BooleanValue.value == 0);

    /* Uint8Value */
    r = Instance_SetElementFromString(base, ZT("Uint8Value"), ZT("8"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Uint8Value.exists == 1);
    UT_ASSERT(inst->Uint8Value.value == 8);

    /* Sint8Value */
    r = Instance_SetElementFromString(base, ZT("Sint8Value"), ZT("-8"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Sint8Value.exists == 1);
    UT_ASSERT(inst->Sint8Value.value == -8);

    /* Uint16Value */
    r = Instance_SetElementFromString(base, ZT("Uint16Value"), ZT("16"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Uint16Value.exists == 1);
    UT_ASSERT(inst->Uint16Value.value == 16);

    /* Sint16Value */
    r = Instance_SetElementFromString(base, ZT("Sint16Value"), ZT("-16"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Sint16Value.exists == 1);
    UT_ASSERT(inst->Sint16Value.value == -16);

    /* Uint32Value */
    r = Instance_SetElementFromString(base, ZT("Uint32Value"), ZT("32"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Uint32Value.exists == 1);
    UT_ASSERT(inst->Uint32Value.value == 32);

    /* Sint32Value */
    r = Instance_SetElementFromString(base, ZT("Sint32Value"), ZT("-32"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Sint32Value.exists == 1);
    UT_ASSERT(inst->Sint32Value.value == -32);

    /* Uint64Value */
    r = Instance_SetElementFromString(base, ZT("Uint64Value"), ZT("64"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Uint64Value.exists == 1);
    UT_ASSERT(inst->Uint64Value.value == 64);

    /* Sint64Value */
    r = Instance_SetElementFromString(base, ZT("Sint64Value"), ZT("-64"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Sint64Value.exists == 1);
    UT_ASSERT(inst->Sint64Value.value == -64);

    /* Real32Value */
    r = Instance_SetElementFromString(base, ZT("Real32Value"), ZT("32.32"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Real32Value.exists == 1);
    UT_ASSERT(inst->Real32Value.value > 32 && inst->Real32Value.value < 33);

    /* Real64Value */
    r = Instance_SetElementFromString(base, ZT("Real64Value"), ZT("64.64"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Real64Value.exists == 1);
    UT_ASSERT(inst->Real64Value.value > 64 && inst->Real64Value.value < 65);

    /* DatetimeValue */
    r = Instance_SetElementFromString(base, ZT("TimestampValue"), 
        ZT("20051225120000.123456-360"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->TimestampValue.exists == 1);

    /* Char16Value */
    r = Instance_SetElementFromString(base, ZT("Char16Value"), ZT("1234"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Char16Value.exists == 1);
    UT_ASSERT(inst->Char16Value.value == 1234);

    /* DatetimeValue */
    r = Instance_SetElementFromString(base, ZT("IntervalValue"), 
        ZT("12345678010101.123456:000"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->IntervalValue.exists == 1);

    /* StringValue */
    r = Instance_SetElementFromString(base, ZT("StringValue"), ZT("Hello"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->StringValue.exists == 1);
    UT_ASSERT(Zcmp(inst->StringValue.value, ZT("Hello")) == 0);

    /* Uint32Array */
    {
        MI_Uint32 data[] = { 10, 20, 30 };
        MI_Value value;
        value.uint32a.data = data;
        value.uint32a.size = MI_COUNT(data);
        r = MI_Instance_SetElement(base, ZT("Uint32Array"), &value, MI_UINT32A, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(inst->Uint32Array.value.data[0] == 10);
        UT_ASSERT(inst->Uint32Array.value.data[1] == 20);
        UT_ASSERT(inst->Uint32Array.value.data[2] == 30);
    }

    /* Uint16Array */
    {
        MI_Uint16 data[1];
        MI_Value value;
        value.uint16a.data = data;
        value.uint16a.size = 0;
        r = MI_Instance_SetElement(base, ZT("Uint16Array"), &value, MI_UINT16A, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(inst->Uint16Array.exists);
    }

    /* StringArray */
    {
        ZChar* data[] = { (ZChar*)ZT("RED"), (ZChar*)ZT("GREEN"), (ZChar*)ZT("BLUE") };
        MI_Value value;
        value.stringa.data = data;
        value.stringa.size = MI_COUNT(data);
        r = MI_Instance_SetElement(base, ZT("StringArray"), &value, MI_STRINGA, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(Zcmp(inst->StringArray.value.data[0], ZT("RED")) == 0);
        UT_ASSERT(Zcmp(inst->StringArray.value.data[1], ZT("GREEN")) == 0);
        UT_ASSERT(Zcmp(inst->StringArray.value.data[2], ZT("BLUE")) == 0);
    }

    return base;
}

static void TestAllTypes()
{
    MI_Instance* base;
    MSFT_AllTypes* inst;
    MI_ClassDecl* cd;
    MI_Result r;
    FILE* os;
    Batch batch = BATCH_INITIALIZER;

    cd = SchemaDecl_FindClassDecl(
        &test_repos_classDecl, ZT("MSFT_AllTypes"));
    UT_ASSERT(cd != NULL);

    r = Instance_New(&base, cd, &batch);
    UT_ASSERT(r == MI_RESULT_OK);
    inst = (MSFT_AllTypes*)base;

    /* BooleanValue */
    r = Instance_SetElementFromString(base, ZT("BooleanValue"), ZT("TRUE"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->BooleanValue.exists == 1);
    UT_ASSERT(inst->BooleanValue.value == 1);

    /* BooleanValue */
    r = Instance_SetElementFromString(base, ZT("BooleanValue"), ZT("FALSE"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->BooleanValue.exists == 1);
    UT_ASSERT(inst->BooleanValue.value == 0);

    /* Uint8Value */
    r = Instance_SetElementFromString(base, ZT("Uint8Value"), ZT("8"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Uint8Value.exists == 1);
    UT_ASSERT(inst->Uint8Value.value == 8);

    /* Sint8Value */
    r = Instance_SetElementFromString(base, ZT("Sint8Value"), ZT("-8"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Sint8Value.exists == 1);
    UT_ASSERT(inst->Sint8Value.value == -8);

    /* Uint16Value */
    r = Instance_SetElementFromString(base, ZT("Uint16Value"), ZT("16"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Uint16Value.exists == 1);
    UT_ASSERT(inst->Uint16Value.value == 16);

    /* Sint16Value */
    r = Instance_SetElementFromString(base, ZT("Sint16Value"), ZT("-16"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Sint16Value.exists == 1);
    UT_ASSERT(inst->Sint16Value.value == -16);

    /* Uint32Value */
    r = Instance_SetElementFromString(base, ZT("Uint32Value"), ZT("32"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Uint32Value.exists == 1);
    UT_ASSERT(inst->Uint32Value.value == 32);

    /* Sint32Value */
    r = Instance_SetElementFromString(base, ZT("Sint32Value"), ZT("-32"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Sint32Value.exists == 1);
    UT_ASSERT(inst->Sint32Value.value == -32);

    /* Uint64Value */
    r = Instance_SetElementFromString(base, ZT("Uint64Value"), ZT("64"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Uint64Value.exists == 1);
    UT_ASSERT(inst->Uint64Value.value == 64);

    /* Sint64Value */
    r = Instance_SetElementFromString(base, ZT("Sint64Value"), ZT("-64"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Sint64Value.exists == 1);
    UT_ASSERT(inst->Sint64Value.value == -64);

    /* Real32Value */
    r = Instance_SetElementFromString(base, ZT("Real32Value"), ZT("32.32"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Real32Value.exists == 1);
    UT_ASSERT(inst->Real32Value.value > 32 && inst->Real32Value.value < 33);

    /* Real64Value */
    r = Instance_SetElementFromString(base, ZT("Real64Value"), ZT("64.64"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Real64Value.exists == 1);
    UT_ASSERT(inst->Real64Value.value > 64 && inst->Real64Value.value < 65);

    /* DatetimeValue */
    r = Instance_SetElementFromString(base, ZT("TimestampValue"), 
        ZT("20051225120000.123456-360"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->TimestampValue.exists == 1);

    /* Char16Value */
    r = Instance_SetElementFromString(base, ZT("Char16Value"), ZT("1234"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->Char16Value.exists == 1);
    UT_ASSERT(inst->Char16Value.value == 1234);

    /* DatetimeValue */
    r = Instance_SetElementFromString(base, ZT("IntervalValue"), 
        ZT("12345678010101.123456:000"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->IntervalValue.exists == 1);

    /* StringValue */
    r = Instance_SetElementFromString(base, ZT("StringValue"), ZT("Hello"));
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst->StringValue.exists == 1);
    UT_ASSERT(Zcmp(inst->StringValue.value, ZT("Hello")) == 0);

    /* Uint32Array */
    {
        MI_Uint32 data[] = { 10, 20, 30 };
        MI_Value value;
        value.uint32a.data = data;
        value.uint32a.size = MI_COUNT(data);
        r = MI_Instance_SetElement(base, ZT("Uint32Array"), &value, MI_UINT32A, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(inst->Uint32Array.value.data[0] == 10);
        UT_ASSERT(inst->Uint32Array.value.data[1] == 20);
        UT_ASSERT(inst->Uint32Array.value.data[2] == 30);
    }

    /* StringArray */
    {
        ZChar* data[] = { (ZChar*)ZT("RED"), (ZChar*)ZT("GREEN"), (ZChar*)ZT("BLUE") };
        MI_Value value;
        value.stringa.data = data;
        value.stringa.size = MI_COUNT(data);
        r = MI_Instance_SetElement(base, ZT("StringArray"), &value, MI_STRINGA, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(Zcmp(inst->StringArray.value.data[0], ZT("RED")) == 0);
        UT_ASSERT(Zcmp(inst->StringArray.value.data[1], ZT("GREEN")) == 0);
        UT_ASSERT(Zcmp(inst->StringArray.value.data[2], ZT("BLUE")) == 0);
    }

    /* Print */
    os = outStream;
    UT_ASSERT(os);
    MI_Instance_Print(base, os, 0);

    /* Convert */
    {
        MSFT_AllTypes conv;
        r = Instance_InitConvert(
            (MI_Instance*)&conv, 
            cd, 
            base, 
            MI_FALSE, /* Keys only */
            MI_FALSE, /* allow-keyless */
            MI_FALSE, /* copy */
            &batch);  
        UT_ASSERT(r == MI_RESULT_OK);
        MI_Instance_Destruct((MI_Instance*)&conv);
    }

    /* Convert */
    {
        MSFT_AllTypes conv;
        r = Instance_InitConvert(
            (MI_Instance*)&conv, 
            cd, 
            base, 
            MI_FALSE,  /* Keys only */
            MI_FALSE, /* allow-keyless */
            MI_TRUE, /* copy */
            &batch);  
        UT_ASSERT(r == MI_RESULT_OK);
        MI_Instance_Destruct((MI_Instance*)&conv);
    }

    {
        MI_Instance* dinst = NULL;
        MSFT_AllTypes sinst;
        memset(&sinst, 0, sizeof(sinst));

        /* Create a dynamic instance will all string properties */
        r = Instance_NewDynamic(&dinst, ZT("MSFT_AllTypes"), MI_FLAG_CLASS,
            &batch);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(dinst != NULL);

        r = AddString(dinst, ZT("Key"), ZT("999"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = AddString(dinst, ZT("BooleanValue"), ZT("FALSE"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = AddString(dinst, ZT("Uint8Value"), ZT("8"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = AddString(dinst, ZT("Sint8Value"), ZT("-8"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = AddString(dinst, ZT("Uint16Value"), ZT("16"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = AddString(dinst, ZT("Sint16Value"), ZT("-16"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = AddString(dinst, ZT("Uint32Value"), ZT("32"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = AddString(dinst, ZT("Sint32Value"), ZT("-32"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = AddString(dinst, ZT("Uint64Value"), ZT("64"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = AddString(dinst, ZT("Sint64Value"), ZT("-64"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = AddString(dinst, ZT("Real32Value"), ZT("32.32"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = AddString(dinst, ZT("Real64Value"), ZT("64.64"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = AddString(dinst, ZT("TimestampValue"), 
            ZT("20051225120000.123456-360"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = AddString(dinst, ZT("Char16Value"), ZT("1234"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = AddString(dinst, ZT("IntervalValue"), 
            ZT("12345678010101.123456:000"));
        UT_ASSERT(r == MI_RESULT_OK);
        r = AddString(dinst, ZT("StringValue"), ZT("Hello"));
        UT_ASSERT(r == MI_RESULT_OK);

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
            &batch);
        UT_ASSERT(r == MI_RESULT_OK);

#if 0
        MI_Instance_Print(&sinst.__instance, stdout, 0);
#endif

        UT_ASSERT(sinst.BooleanValue.exists == 1);
        UT_ASSERT(sinst.BooleanValue.value == 0);
        UT_ASSERT(sinst.Uint8Value.exists == 1);
        UT_ASSERT(sinst.Uint8Value.value == 8);
        UT_ASSERT(sinst.Sint8Value.exists == 1);
        UT_ASSERT(sinst.Sint8Value.value == -8);
        UT_ASSERT(sinst.Uint16Value.exists == 1);
        UT_ASSERT(sinst.Uint16Value.value == 16);
        UT_ASSERT(sinst.Sint16Value.exists == 1);
        UT_ASSERT(sinst.Sint16Value.value == -16);
        UT_ASSERT(sinst.Uint32Value.exists == 1);
        UT_ASSERT(sinst.Uint32Value.value == 32);
        UT_ASSERT(sinst.Sint32Value.exists == 1);
        UT_ASSERT(sinst.Sint32Value.value == -32);
        UT_ASSERT(sinst.Uint64Value.exists == 1);
        UT_ASSERT(sinst.Uint64Value.value == 64);
        UT_ASSERT(sinst.Sint64Value.exists == 1);
        UT_ASSERT(sinst.Sint64Value.value == -64);
        UT_ASSERT(sinst.Real32Value.exists == 1);
        UT_ASSERT(sinst.Real32Value.value > 32 && sinst.Real32Value.value < 33);
        UT_ASSERT(sinst.Real64Value.exists == 1);
        UT_ASSERT(sinst.Real64Value.value > 64 && sinst.Real64Value.value < 65);
        UT_ASSERT(sinst.TimestampValue.exists == 1);
        UT_ASSERT(sinst.Char16Value.exists == 1);
        UT_ASSERT(sinst.Char16Value.value == 1234);
        UT_ASSERT(sinst.IntervalValue.exists == 1);
        UT_ASSERT(sinst.StringValue.exists == 1);
        UT_ASSERT(Zcmp(sinst.StringValue.value, ZT("Hello")) == 0);

        MI_Instance_Destruct((MI_Instance*)&sinst);
        MI_Instance_Delete(dinst);
    }

    MI_Instance_Delete(base);

    Batch_Destroy(&batch);
}

#if 0
static bool Test(MI_Result r, const ZChar* str)
{
    return Zcmp(Result_ToString(r), str) == 0;
}
#endif

#if 0
static void TestLib1()
{
    char path[MAX_PATH];

    Lib_Format(path, NULL, "PersonProvider");
#if defined(CONFIG_OS_LINUX)
    UT_ASSERT(strcmp(path, "libPersonProvider.so") == 0);
#elif defined(_MSC_VER)
    UT_ASSERT(strcmp(path, "PersonProvider.dll") == 0);
#endif
}

static void TestLib2()
{
#define DIRNAME "../" CONFIG_LIBDIR
    char path[MAX_PATH];
    void* handle;
    void* sym;
    MI_Result r;

    /* Format path */
    Lib_Format(path, DIRNAME, "PersonProvider");
#if defined(CONFIG_OS_LINUX)
    UT_ASSERT(strcmp(path, DIRNAME "/libPersonProvider.so") == 0);
#elif defined(_MSC_VER)
    UT_ASSERT(strcmp(path, DIRNAME "/PersonProvider.dll") == 0);
#endif

    /* Load library */
    handle = Lib_Open(path);

    if(!handle)
    {
        handle = Lib_Open("PersonProvider");
    }

    UT_ASSERT(handle != NULL);

    /* Get 'MI_Main' symbol */
    sym = Lib_Sym(handle, "MI_Main");
    UT_ASSERT(sym != NULL);

    /* Close the library */
    r = Lib_Close(handle);
    UT_ASSERT(r == MI_RESULT_OK);
}
#endif

void TestInstances()
{
    MI_Result r;
    MI_Instance* inst;
    MI_Value value;
    const MI_ClassDecl* cd;
    Batch batch = BATCH_INITIALIZER;
    
    /* Find class decl */
    cd = SchemaDecl_FindClassDecl(&test_repos_classDecl, ZT("MSFT_Process"));
    UT_ASSERT(cd != NULL);

    /* Create instance of MSFT_Numbers */
    r = Instance_New(&inst, cd, &batch);
    UT_ASSERT(r == MI_RESULT_OK);

    /* CIM_Person.Key */
    value.uint64 = 1234;
    r = MI_Instance_SetElement(inst, MI_T("WorkingSetSize"), &value, MI_UINT64, 0);
    UT_ASSERT(r == MI_RESULT_OK);

    /* Check value */
    for (size_t i = 0; i < 1000000; i++)
    {
        MI_Value v;
        MI_Type t;
        MI_Uint32 f;
        r = MI_Instance_GetElement(inst, MI_T("WorkingSetSize"), &v, &t, &f, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(v.uint64 == 1234);
        UT_ASSERT(t == MI_UINT64);
        UT_ASSERT(!(f & MI_FLAG_NULL));
    }

    MI_Instance_Delete(inst);
    Batch_Destroy(&batch);
}

static void TestDynamicInstances()
{
    MI_Instance* inst;
    MI_Result r;
    MI_Value v;
    Batch batch = BATCH_INITIALIZER;
    Batch* b = &batch;

    r = Instance_NewDynamic(&inst, ZT("MSFT_Person"), MI_FLAG_CLASS, b);
    UT_ASSERT(r == MI_RESULT_OK);

    v.uint32 = 1;
    r = MI_Instance_AddElement(inst, ZT("Key"), &v, MI_UINT32, MI_FLAG_KEY);
    UT_ASSERT(r == MI_RESULT_OK);

    v.string = (ZChar*)ZT("George");
    r = MI_Instance_AddElement(inst, ZT("First"), &v, MI_STRING, 0);
    UT_ASSERT(r == MI_RESULT_OK);

    v.string = (ZChar*)ZT("Washington");
    r = MI_Instance_AddElement(inst, ZT("Last"), &v, MI_STRING, 0);
    UT_ASSERT(r == MI_RESULT_OK);

    /* Check "Key" */
    {
        MI_Type t;
        MI_Uint32 f;
        r = MI_Instance_GetElement(inst, ZT("Key"), &v, &t, &f, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(v.uint32 == 1);
        UT_ASSERT(t == MI_UINT32);
        UT_ASSERT(!(f & MI_FLAG_NULL));
    }

    /* Check "First" */
    {
        MI_Type t;
        MI_Uint32 f;
        r = MI_Instance_GetElement(inst, ZT("First"), &v, &t, &f, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(Zcmp(v.string, ZT("George")) == 0);
        UT_ASSERT(t == MI_STRING);
        UT_ASSERT(!(f & MI_FLAG_NULL));
    }

    /* Check "Last" */
    {
        MI_Type t;
        MI_Uint32 f;
        r = MI_Instance_GetElement(inst, ZT("Last"), &v, &t, &f, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(Zcmp(v.string, ZT("Washington")) == 0);
        UT_ASSERT(t == MI_STRING);
        UT_ASSERT(!(f & MI_FLAG_NULL));
    }

#if 0
    MI_Instance_Print(inst, stdout, 0);
#endif

    // Test cloning.
    MI_Instance* clone = NULL;
    r = MI_Instance_Clone(inst, &clone);
    UT_ASSERT(r == MI_RESULT_OK);

#if 0
    MI_Instance_Print(clone, stdout, 0);
#endif

    /* Check "Key" */
    {
        MI_Type t;
        MI_Uint32 f;
        r = MI_Instance_GetElement(clone, ZT("Key"), &v, &t, &f, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(v.uint32 == 1);
        UT_ASSERT(t == MI_UINT32);
        UT_ASSERT(!(f & MI_FLAG_NULL));
    }

    /* Check "First" */
    {
        MI_Type t;
        MI_Uint32 f;
        r = MI_Instance_GetElement(clone, ZT("First"), &v, &t, &f, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(Zcmp(v.string, ZT("George")) == 0);
        UT_ASSERT(t == MI_STRING);
        UT_ASSERT(!(f & MI_FLAG_NULL));
    }

    /* Check "Last" */
    {
        MI_Type t;
        MI_Uint32 f;
        r = MI_Instance_GetElement(clone, ZT("Last"), &v, &t, &f, 0);
        UT_ASSERT(r == MI_RESULT_OK);
        UT_ASSERT(Zcmp(v.string, ZT("Washington")) == 0);
        UT_ASSERT(t == MI_STRING);
        UT_ASSERT(!(f & MI_FLAG_NULL));
    }


    /* Pack/unpack the instance */
    {
        Buf buf = BUF_INITIALIZER;
        MI_Instance* newInst;

        Buf_Init(&buf, 4096);

        /* Pack */
        r = Instance_Pack(inst, MI_FALSE, NULL, NULL, &buf);
        UT_ASSERT(r == MI_RESULT_OK);

        /* Unpack */
        r = Instance_Unpack(&newInst, &buf, b, MI_FALSE);
        UT_ASSERT(r == MI_RESULT_OK);

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
        Szprintf(buf, MI_COUNT(buf), ZT("P%d"), (int)i);
        v.string = (ZChar*)ZT("Junk");
        r = MI_Instance_AddElement(inst, buf, &v, MI_STRING, 0);
        UT_ASSERT(r == MI_RESULT_OK);
    }

    // Test basd name:
    r = MI_Instance_AddElement(inst, ZT(""), NULL, MI_UINT32, 0);
    UT_ASSERT(r == MI_RESULT_INVALID_PARAMETER);

    // Test reference array:
    {
        MI_Instance* data[2];

        for (size_t i = 0; i < 2; i++)
        {
            MI_Instance* tmp = NULL;
            r = MI_Instance_Clone(inst, &tmp);
            UT_ASSERT(r == MI_RESULT_OK);
            UT_ASSERT(tmp != NULL);
            data[i] = tmp;
        }

        v.instancea.data = data;
        v.instancea.size = 2;
        r = MI_Instance_AddElement(inst, ZT("RefArray"), &v, MI_REFERENCEA, 0);
        UT_ASSERT(r == MI_RESULT_OK);

        for (size_t i = 0; i < 2; i++)
            MI_Instance_Delete(data[i]);
    }

    MI_Instance_Print(inst, outStream, 0);

    // Clone again
    {
        MI_Instance* tmp = NULL;
        r = MI_Instance_Clone(inst, &tmp);
        UT_ASSERT(r == MI_RESULT_OK);
        MI_Instance_Delete(tmp);
    }

    MI_Instance_Delete(clone);
    MI_Instance_Delete(inst);
    Batch_Destroy(b);
}

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
static void TestBuf()
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

    Buf_Init(&b, 256);

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
                UT_ASSERT(r == MI_RESULT_OK);
                sum1 += buf8[i];
                break;
            case 1:
                r = Buf_PackU16(&b, buf16[i]);
                UT_ASSERT(r == MI_RESULT_OK);
                sum1 += buf16[i];
                break;
            case 2:
                r = Buf_PackU32(&b, buf32[i]);
                UT_ASSERT(r == MI_RESULT_OK);
                sum1 += buf32[i];
                break;
            case 3:
                r = Buf_PackU64(&b, buf64[i]);
                sum1 += buf64[i];
                UT_ASSERT(r == MI_RESULT_OK);
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
                UT_ASSERT(r == MI_RESULT_OK);
                UT_ASSERT(x == buf8[i]);
                sum2 += buf8[i];
                break;
            }
            case 1:
            {
                MI_Uint16 x = 0;
                r = Buf_UnpackU16(&b, &x);
                UT_ASSERT(r == MI_RESULT_OK);
                UT_ASSERT(x == buf16[i]);
                sum2 += buf16[i];
                break;
            }
            case 2:
            {
                MI_Uint32 x = 0;
                r = Buf_UnpackU32(&b, &x);
                UT_ASSERT(r == MI_RESULT_OK);
                UT_ASSERT(x == buf32[i]);
                sum2 += buf32[i];
                break;
            }
            case 3:
            {
                MI_Uint64 x = 0;
                r = Buf_UnpackU64(&b, &x);
                UT_ASSERT(r == MI_RESULT_OK);
                UT_ASSERT(x == buf64[i]);
                sum2 += buf64[i];
                break;
            }
        }
    }

    /* Verify that the check sums are the same */
    UT_ASSERT(sum1 == sum2);

    Buf_Destroy(&b);
}

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
static void TestBuf2()
{
    Buf b;
    MI_Result r;
    MI_Uint32 i;
    const MI_Uint32 N = 10000;

    Buf_Init(&b, 256);

    for (i = 0; i < N; i++)
    {
        ZChar buf[32];
        Szprintf(buf, MI_COUNT(buf), ZT("%u"), i);
        r = Buf_PackStr(&b, buf);
        UT_ASSERT(r == MI_RESULT_OK);
    }

    for (i = 0; i < N; i++)
    {
        ZChar buf[32];
        const ZChar* str = NULL;

        Szprintf(buf, MI_COUNT(buf), ZT("%u"), i);
        r = Buf_UnpackStr(&b, &str);
        UT_ASSERT(r == MI_RESULT_OK);
    }

    Buf_Destroy(&b);
}

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
static void TestBuf3()
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

    Buf_Init(&b, 256);

    for (i = 0; i < N; i++)
    {
        a8.push_back((MI_Uint8)i);
        a16.push_back((MI_Uint16)i);
        a32.push_back((MI_Uint32)i);
        a64.push_back((MI_Uint64)i);
        {
            r = Buf_PackU8A(&b, &a8[0], (MI_Uint32)a8.size());
            UT_ASSERT(r == MI_RESULT_OK);
        }
        {
            r = Buf_PackU16A(&b, &a16[0], (MI_Uint32)a16.size());
            UT_ASSERT(r == MI_RESULT_OK);
        }
        {
            r = Buf_PackU32A(&b, &a32[0], (MI_Uint32)a32.size());
            UT_ASSERT(r == MI_RESULT_OK);
        }
        {
            r = Buf_PackU64A(&b, &a64[0], (MI_Uint32)a64.size());
            UT_ASSERT(r == MI_RESULT_OK);
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
            UT_ASSERT(r == MI_RESULT_OK);
            UT_ASSERT((MI_Uint32)b8.size() == size);
            UT_ASSERT(memcmp(data, &b8[0], i * sizeof(MI_Uint8)) == 0);
        }
        {
            const MI_Uint16* data;
            MI_Uint32 size;

            r = Buf_UnpackU16A(&b, &data, &size);
            UT_ASSERT(r == MI_RESULT_OK);
            UT_ASSERT((MI_Uint32)b16.size() == size);
            UT_ASSERT(memcmp(data, &b16[0], i * sizeof(MI_Uint16)) == 0);
        }
        {
            const MI_Uint32* data;
            MI_Uint32 size;

            r = Buf_UnpackU32A(&b, &data, &size);
            UT_ASSERT(r == MI_RESULT_OK);
            UT_ASSERT((MI_Uint32)b32.size() == size);
            UT_ASSERT(memcmp(data, &b32[0], i * sizeof(MI_Uint32)) == 0);
        }
        {
            const MI_Uint64* data;
            MI_Uint32 size;

            r = Buf_UnpackU64A(&b, &data, &size);
            UT_ASSERT(r == MI_RESULT_OK);
            UT_ASSERT((MI_Uint32)b64.size() == size);
            UT_ASSERT(memcmp(data, &b64[0], i * sizeof(MI_Uint64)) == 0);
        }
    }

    Buf_Destroy(&b);
}

/*
**==============================================================================
**
** TestBuf4()
**
**     This test excercises the string array pack/unpack functions of Buf.
**
**==============================================================================
*/
static void TestBuf4()
{
    Buf b;
    MI_Result r;
    const ZChar* DATA[5][7] =
    {
		{
			ZT("Sunday"),
			ZT("Monday"),
			ZT("Tuesday"),
			ZT("Wednesday"),
			ZT("Thursday"),
			ZT("Friday"),
			ZT("Saturday")
		},
		{},
		{
			ZT("Unicorn")
		},
		{
			ZT("")
		},
		{
			ZT(""),
			ZT(""),
			ZT("")
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
			Buf_Init(&b, 256);

			r = Buf_PackStrA(&b, DATA[arrayIndex], SIZE);
			UT_ASSERT(r == MI_RESULT_OK);

			r = Buf_UnpackStrA(&b, &data, &size);
			UT_ASSERT(r == MI_RESULT_OK);

			UT_ASSERT(size == SIZE);

			for (i = 0; i < size; i++)
				UT_ASSERT(Zcmp(data[i], DATA[arrayIndex][i]) == 0);

			Buf_Destroy(&b);
		}
		{
			MI_Uint32 j;
			const MI_Uint32 N = 100;

			Buf_Init(&b, 256);

			for (j = 0; j < N; j++)
			{
				r = Buf_PackStrA(&b, DATA[arrayIndex], SIZE);
				UT_ASSERT(r == MI_RESULT_OK);
			}

			for (j = 0; j < N; j++)
			{
				r = Buf_UnpackStrA(&b, &data, &size);
				UT_ASSERT(r == MI_RESULT_OK);

				UT_ASSERT(size == SIZE);

				for (i = 0; i < size; i++)
					UT_ASSERT(Zcmp(data[i], DATA[arrayIndex][i]) == 0);
			}

			Buf_Destroy(&b);
		}
	}
}

static void TestLog()
{
    MI_Result r;
    ZChar tmp[MAX_PATH_SIZE];

#if defined(CONFIG_OS_WINDOWS)
    int tmp_i = _mkdir(GetPath(ID_TMPDIR));
    MI_UNUSED(tmp_i);
#endif

    /* Open the log (into text.log) */
    r = Log_Open(ZSTempPath(tmp, "test2.log"));
    UT_ASSERT(r == MI_RESULT_OK);

    /* Set the log level to 'INFO' */
    Log_SetLevel(LOG_INFO);

    /* Write a log message of each level */
    LOGF((ZT("fatal: %u"), 11111));
    LOGE((ZT("error: %u"), 22222));
    LOGW((ZT("warning: %u"), 33333));
    LOGI((ZT("information: %u"), 44444));
    LOGD((ZT("debug: %u"), 55555));

    /* Close the log */
    Log_Close();

    /* verify that output was correct */
    std::vector< unsigned char > content;
    UT_ASSERT(ut::readFileContent(ut::StrToChar(tmp), content));

#if 0
    ut::removeIfExist(ut::StrToChar(tmp).c_str());
#endif

    UT_ASSERT(!content.empty());

    {
        std::string s(reinterpret_cast<const char*>(&content[0]),
            reinterpret_cast<const char*>(&content[0]) + content.size());

        // expecting to find mentioning of all messages, excluding 'debug'
        UT_ASSERT(s.find("FATAL") != string::npos);
        UT_ASSERT(s.find("fatal: 11111") != string::npos);
        UT_ASSERT(s.find("ERROR") != string::npos);
        UT_ASSERT(s.find("error: 22222") != string::npos);
        UT_ASSERT(s.find("WARNING") != string::npos);
        UT_ASSERT(s.find("warning: 33333") != string::npos);
        UT_ASSERT(s.find("INFO") != string::npos);
        UT_ASSERT(s.find("information: 44444") != string::npos);

        // these should not be in the file
        UT_ASSERT(s.find("DEBUG") == string::npos);
        UT_ASSERT(s.find("debug: 55555") == string::npos);

    }

    /* Test loglevel conversions */
    {
        const char* _symbols[] = 
        {
            "Fatal",
            "Error",
            "Warning",
            "Info",
            "Debug",
        };
        const Log_Level _levels[] = 
        {
            LOG_FATAL,
            LOG_ERROR,
            LOG_WARNING,
            LOG_INFO,
            LOG_DEBUG
        };
        const size_t n = sizeof(_symbols) / sizeof(_symbols[0]);

        for (size_t i = 0; i < n; i++)
        {
            UT_ASSERT(Log_SetLevelFromString(_symbols[i]) == 0);

            UT_ASSERT(Strcasecmp(
                Log_GetLevelString(Log_GetLevel()), _symbols[i]) == 0);

            UT_ASSERT(Log_GetLevel() == _levels[i]);
        }
    }
}

static void TestPackInstance()
{
    MI_Instance* inst1 = NULL;
    MI_Instance* inst2 = NULL;
    Batch batch = BATCH_INITIALIZER;
    Buf buf = BUF_INITIALIZER;
    MI_Result r;

    /* Create new instance of MSFT_AllTypes */
    inst1 = NewAllTypes(&batch);
    UT_ASSERT(inst1 != NULL);

    /* Pack instance */
    r = Instance_Pack(inst1, MI_FALSE, NULL, NULL, &buf);
    UT_ASSERT(r == MI_RESULT_OK);

    /* Unpack instance */
    r = Instance_Unpack(&inst2, &buf, &batch, MI_FALSE);
    UT_ASSERT(r == MI_RESULT_OK);
    UT_ASSERT(inst2 != NULL);

#if 0
    MI_Instance_Print(inst1, stdout, 0);
    MI_Instance_Print(inst2, stdout, 0);
#endif

    /* Steal buffer memory and attach it to the batch. */
    {
        Page* page = Buf_StealPage(&buf);
        UT_ASSERT(page != NULL);
        Batch_AttachPage(&batch, page);
    }

    MI_Instance_Delete(inst1);
    MI_Instance_Delete(inst2);
    Buf_Destroy(&buf);
    Batch_Destroy(&batch);
}

static void TestPage()
{
    size_t n = sizeof (Page);
    UT_ASSERT(n % 8 == 0);
}

#define TestOneCppProp(prop,valueParam)             \
    {  \
    /* test auto-generated setters/getters/copy/assignment operators  */  \
    MSFT_AllTypes_Class inst1;                   \
                                                \
    UT_ASSERT(!inst1.prop().exists);            \
    inst1.prop##_value(valueParam);             \
    UT_ASSERT(inst1.prop().exists);             \
    UT_ASSERT(inst1.prop().value == valueParam);   \
                                                \
    /* copy ctor of instance */                 \
    MSFT_AllTypes_Class inst2( inst1 );          \
                                                \
    UT_ASSERT(inst1.prop() == inst2.prop());    \
    UT_ASSERT(inst1.prop##_value() == inst2.prop##_value());    \
                                                \
    /* assignment operator */                   \
    MSFT_AllTypes_Class inst3;                   \
                                                \
    UT_ASSERT(inst1.prop().exists != inst3.prop().exists);    \
    UT_ASSERT(!inst3.prop().exists);            \
                                                \
    inst3 = inst1;                              \
    UT_ASSERT(inst1.prop().exists == inst3.prop().exists);    \
    UT_ASSERT(inst1.prop().value == inst3.prop().value);    \
    UT_ASSERT(inst1.prop##_value() == inst3.prop##_value());    \
                                                \
    /* copy data using setters  */              \
    MSFT_AllTypes_Class inst4;                   \
                                                \
    UT_ASSERT(inst1.prop().exists != inst4.prop().exists);    \
                                                \
    inst4.prop(inst1.prop());                   \
    UT_ASSERT(inst1.prop() == inst4.prop());    \
    UT_ASSERT(inst1.prop##_value() == inst4.prop##_value());    \
                                                \
    /* test null assignment */                  \
    MSFT_AllTypes_Class inst_null;               \
                                                \
    UT_ASSERT(inst4.prop() != inst_null.prop());    \
    inst4 = inst_null;                          \
    UT_ASSERT(inst4.prop() == inst_null.prop());\
    }


static void TestBaseCppAllTypes()
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

static void TestDir()
{
    string path = srcdir + "/tests/base/testdir";
    Dir* dir = Dir_Open(path.c_str());
    UT_ASSERT(dir != NULL);

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

    UT_ASSERT(names1.size() == 5);
    UT_ASSERT(names2.size() == 5);
    UT_ASSERT(names1 == names2);

    Dir_Close(dir);
}

static void TestStrArr()
{
    char** data;
    
    data = StrArr();
    if (!data)
        return;

    UT_ASSERT(StrArrLen(data) == 0);

    StrArrCat(&data, "Red");
    UT_ASSERT(StrArrLen(data) == 1);
    StrArrCat(&data, "Green");
    UT_ASSERT(StrArrLen(data) == 2);
    StrArrCat(&data, "Blue");
    UT_ASSERT(StrArrLen(data) == 3);

    char ** tmp = data;
    UT_ASSERT(strcmp(*tmp, "Red") == 0);
    if (*tmp)
    {
        tmp++;
        UT_ASSERT(strcmp(*tmp, "Green") == 0);
    }
    else
    {
        UT_ASSERT("unexpected end of array" && NULL);
    }
    if (*tmp)
    {
        tmp++;
        UT_ASSERT(strcmp(*tmp, "Blue") == 0);
    }
    else
    {
        UT_ASSERT("unexpected end of array" && NULL);
    }

    StrArrFree(data);
}

static void TestConf1()
{
    char path[MAX_PATH_SIZE];
    Conf* conf;
    size_t n = 1;

    Strlcpy(path, GetPath(ID_SRCDIR), sizeof(path));
    Strlcat(path, "/tests/base/file1.conf", sizeof(path));

    /* Open configuration file */
    conf = Conf_Open(path);
    UT_ASSERT(conf != NULL);

    for (;;)
    {
        const char* key;
        const char* value;
        int r = Conf_Read(conf, &key, &value);

        if (r == 1)
            break;

        UT_ASSERT(r == 0);

        switch (n)
        {
            case 1:
                UT_ASSERT(strcmp(key, "Key1") == 0);
                UT_ASSERT(strcmp(value, "Value1") == 0);
                break;
            case 2:
                UT_ASSERT(strcmp(key, "Key2") == 0);
                UT_ASSERT(strcmp(value, "Value2") == 0);
                break;
            case 3:
                UT_ASSERT(strcmp(key, "Key3") == 0);
                UT_ASSERT(strcmp(value, "Value3") == 0);
                break;
            case 4:
                UT_ASSERT(strcmp(key, "Key4") == 0);
                UT_ASSERT(strcmp(value, "Value4") == 0);
                break;
            case 5:
                UT_ASSERT(strcmp(key, "Key5") == 0);
                UT_ASSERT(strcmp(value, "Value5") == 0);
                break;
            case 6:
                UT_ASSERT(strcmp(key, "Key6") == 0);
                UT_ASSERT(strcmp(value, "") == 0);
                break;
            case 7:
                UT_ASSERT(strcmp(key, "Key7") == 0);
                UT_ASSERT(strcmp(value, "") == 0);
                break;
            default:
                UT_ASSERT(UT_FALSE);
        }

        n++;
    }

    Conf_Close(conf);
}

static void TestConf2()
{
    char path[MAX_PATH_SIZE];
    Conf* conf;
    size_t n = 1;

    Strlcpy(path, GetPath(ID_SRCDIR), sizeof(path));
    Strlcat(path, "/tests/base/file2.conf", sizeof(path));

    /* Open configuration file */
    conf = Conf_Open(path);
    UT_ASSERT(conf != NULL);

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
                UT_ASSERT(strcmp(err, "expected '='") == 0);
                UT_ASSERT(Conf_Line(conf) == 2);
            }
            else if (n == 2)
            {
                UT_ASSERT(strcmp(err, "expected keyword") == 0);
                UT_ASSERT(Conf_Line(conf) == 3);
            }
            else if (n == 3)
            {
                UT_ASSERT(strcmp(err, "expected keyword") == 0);
                UT_ASSERT(Conf_Line(conf) == 4);
            }
            else
                UT_ASSERT(UT_FALSE);
        }
        else if (r == 0)
        {
            UT_ASSERT(n == 4);
            UT_ASSERT(strcmp(key, "KEY1") == 0);
            UT_ASSERT(strcmp(value, "VALUE1") == 0);
        }
        else
            break;

        n++;
    }

    Conf_Close(conf);
}

static void TestMkdirhier()
{
    char tmp[MAX_PATH_SIZE];
    Mkdirhier(TempPath(tmp, "/aaa/bbb/ccc/ddd"), 0755);
    UT_ASSERT(Isdir(tmp));
}

static void TestIntToStr()
{
    for (MI_Uint32 i = 0; i < 1000; i++)
    {
        char buf1[11];
        size_t size1;
        const char* str = Uint32ToStr(buf1, i, &size1);

        char buf2[11];
        size_t size2 = Snprintf(buf2, sizeof(buf2), "%u", i);

        UT_ASSERT(str != NULL);
        UT_ASSERT(size1 == size2);
        UT_ASSERT(strcmp(str, buf2) == 0);
    }

    for (MI_Uint64 i = 0; i < 1000; i++)
    {
        char buf1[21];
        size_t size1;
        const char* str = Uint64ToStr(buf1, i, &size1);

        char buf2[21];
        size_t size2 = Snprintf(buf2, sizeof(buf2), UINT64_FMT, i);

        UT_ASSERT(str != NULL);
        UT_ASSERT(size1 == size2);
        UT_ASSERT(strcmp(str, buf2) == 0);
    }
}

static void TestGetOpt()
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
            Fzprintf(stderr, ZT("GetOpt() failed: %s\n"), scs(state.err));
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

    UT_ASSERT(argc == 3);
    UT_ASSERT(strcmp(argv[0], "aaa") == 0);
    UT_ASSERT(strcmp(argv[1], "bbb") == 0);
    UT_ASSERT(strcmp(argv[2], "ccc") == 0);
    UT_ASSERT(argv[3] == NULL);
    UT_ASSERT(help == true);
    UT_ASSERT(infile == "/tmp/infile");
    UT_ASSERT(outfile == "/tmp/outfile");
    UT_ASSERT(x == "abc");
}

static void TestGetOptErr()
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

    UT_ASSERT(help == true);
    UT_ASSERT(error == "missing option argument: --outfile");
    UT_ASSERT(outfile == "");
}

static void TestMatchKeys()
{
    MI_Result r;
    MI_Instance* inst1;
    MI_Instance* inst2;
    MI_Instance* ref;
    MI_Value value;

    r = Instance_NewDynamic(&ref, ZT("MyRef"), MI_FLAG_CLASS, 0);
    UT_ASSERT(r == MI_RESULT_OK);

    value.uint32 = 57789;
    r = MI_Instance_AddElement(ref, ZT("Key1"), &value, MI_UINT32, MI_FLAG_KEY);
    UT_ASSERT(r == MI_RESULT_OK);

    value.string = (ZChar*)ZT("Bye");
    r = MI_Instance_AddElement(ref, ZT("Key2"), &value, MI_STRING, MI_FLAG_KEY);
    UT_ASSERT(r == MI_RESULT_OK);
    
    r = Instance_NewDynamic(&inst1, ZT("MyClass"), MI_FLAG_ASSOCIATION, 0);
    UT_ASSERT(r == MI_RESULT_OK);

    r = Instance_NewDynamic(&inst2, ZT("MyClass"), MI_FLAG_CLASS, 0);
    UT_ASSERT(r == MI_RESULT_OK);

    UT_ASSERT(Instance_MatchKeys(inst1, inst2) == MI_FALSE);

    value.uint32 = 1234;
    r = MI_Instance_AddElement(inst1, ZT("Key1"), &value,MI_UINT32, MI_FLAG_KEY);
    UT_ASSERT(r == MI_RESULT_OK);

    value.string = (ZChar*)ZT("Hello");
    r = MI_Instance_AddElement(inst1, ZT("Key2"), &value, MI_STRING,MI_FLAG_KEY);
    UT_ASSERT(r == MI_RESULT_OK);

    UT_ASSERT(Instance_MatchKeys(inst1, inst2) == MI_FALSE);

    value.uint32 = 1234;
    r = MI_Instance_AddElement(inst2, ZT("Key1"), &value, MI_UINT32,MI_FLAG_KEY);
    UT_ASSERT(r == MI_RESULT_OK);

    UT_ASSERT(Instance_MatchKeys(inst1, inst2) == MI_FALSE);

    value.string = (ZChar*)ZT("Hello");
    r = MI_Instance_AddElement(inst2, ZT("Key2"), &value, MI_STRING,MI_FLAG_KEY);
    UT_ASSERT(r == MI_RESULT_OK);

    UT_ASSERT(Instance_MatchKeys(inst1, inst2) == MI_TRUE);

    value.reference = ref;
    r = MI_Instance_AddElement(inst1, ZT("Key3"), &value, 
        MI_REFERENCE,MI_FLAG_KEY);
    UT_ASSERT(r == MI_RESULT_OK);

    UT_ASSERT(Instance_MatchKeys(inst1, inst2) == MI_FALSE);

    value.reference = ref;
    r = MI_Instance_AddElement(inst2, ZT("Key3"), &value, 
        MI_REFERENCE,MI_FLAG_KEY);
    UT_ASSERT(r == MI_RESULT_OK);

    UT_ASSERT(Instance_MatchKeys(inst1, inst2) == MI_TRUE);

#if 0
    __MI_Instance_Print(inst1, stdout, 0);
    __MI_Instance_Print(inst2, stdout, 0);
#endif

    __MI_Instance_Delete(inst1);
    __MI_Instance_Delete(inst2);
    __MI_Instance_Delete(ref);
}

static void TestWSManDatetime()
{
    ZChar buf[64];

    {
        MI_Datetime x;
        UT_ASSERT(ParseWSManDatetime(ZT("P5Y"), &x) == 0);
        UT_ASSERT(x.isTimestamp == 0);
        UT_ASSERT(x.u.interval.days == 1826);
        UT_ASSERT(x.u.interval.hours == 0);
        UT_ASSERT(x.u.interval.minutes == 0);
        UT_ASSERT(x.u.interval.seconds == 0);
        UT_ASSERT(x.u.interval.microseconds == 0);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, ZT("P1826D")) == 0);
    }
    {
        MI_Datetime x;
        UT_ASSERT(ParseWSManDatetime(ZT("P1Y1M22D"), &x) == 0);
        UT_ASSERT(x.isTimestamp == 0);
        UT_ASSERT(x.u.interval.days == 417);
        UT_ASSERT(x.u.interval.hours == 0);
        UT_ASSERT(x.u.interval.minutes == 0);
        UT_ASSERT(x.u.interval.seconds == 0);
        UT_ASSERT(x.u.interval.microseconds == 0);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, ZT("P417D")) == 0);
    }
    {
        MI_Datetime x;
        UT_ASSERT(ParseWSManDatetime(ZT("P1Y1M22DT10H11M12S"), &x) == 0);
        UT_ASSERT(x.isTimestamp == 0);
        UT_ASSERT(x.u.interval.days == 417);
        UT_ASSERT(x.u.interval.hours == 10);
        UT_ASSERT(x.u.interval.minutes == 11);
        UT_ASSERT(x.u.interval.seconds == 12);
        UT_ASSERT(x.u.interval.microseconds == 0);
        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, ZT("P417DT10H11M12S")) == 0);
    }
    {
        MI_Datetime x;
        UT_ASSERT(ParseWSManDatetime(ZT("PT31S"), &x) == 0);
        UT_ASSERT(x.isTimestamp == 0);
        UT_ASSERT(x.u.interval.days == 0);
        UT_ASSERT(x.u.interval.hours == 0);
        UT_ASSERT(x.u.interval.minutes == 0);
        UT_ASSERT(x.u.interval.seconds == 31);
        UT_ASSERT(x.u.interval.microseconds == 0);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, ZT("PT31S")) == 0);
    }
    {
        MI_Datetime x;
        UT_ASSERT(ParseWSManDatetime(ZT("PT66S"), &x) == 0);
        UT_ASSERT(x.isTimestamp == 0);
        UT_ASSERT(x.u.interval.days == 0);
        UT_ASSERT(x.u.interval.hours == 0);
        UT_ASSERT(x.u.interval.minutes == 1);
        UT_ASSERT(x.u.interval.seconds == 6);
        UT_ASSERT(x.u.interval.microseconds == 0);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, ZT("PT1M6S")) == 0);
    }
    {
        MI_Datetime x;
        UT_ASSERT(ParseWSManDatetime(ZT("PT60S"), &x) == 0);
        UT_ASSERT(x.isTimestamp == 0);
        UT_ASSERT(x.u.interval.days == 0);
        UT_ASSERT(x.u.interval.hours == 0);
        UT_ASSERT(x.u.interval.minutes == 1);
        UT_ASSERT(x.u.interval.seconds == 0);
        UT_ASSERT(x.u.interval.microseconds == 0);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, ZT("PT1M")) == 0);
    }
    {
        MI_Datetime x;
        UT_ASSERT(ParseWSManDatetime(ZT("PT5.5S"), &x) == 0);
        UT_ASSERT(x.isTimestamp == 0);
        UT_ASSERT(x.u.interval.days == 0);
        UT_ASSERT(x.u.interval.hours == 0);
        UT_ASSERT(x.u.interval.minutes == 0);
        UT_ASSERT(x.u.interval.seconds == 5);
        UT_ASSERT(x.u.interval.microseconds == 500000);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, ZT("PT5.500000S")) == 0);
    }
    {
        MI_Datetime x;
        UT_ASSERT(ParseWSManDatetime(ZT("PT5.123456S"), &x) == 0);
        UT_ASSERT(x.isTimestamp == 0);
        UT_ASSERT(x.u.interval.days == 0);
        UT_ASSERT(x.u.interval.hours == 0);
        UT_ASSERT(x.u.interval.minutes == 0);
        UT_ASSERT(x.u.interval.seconds == 5);
        UT_ASSERT(x.u.interval.microseconds == 123456);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, ZT("PT5.123456S")) == 0);
    }
    {
        MI_Datetime x;
        UT_ASSERT(ParseWSManDatetime(ZT("P1Y2M3DT10H30M"), &x) == 0);
        UT_ASSERT(x.isTimestamp == 0);
        UT_ASSERT(x.u.interval.days == 429);
        UT_ASSERT(x.u.interval.hours == 10);
        UT_ASSERT(x.u.interval.minutes == 30);
        UT_ASSERT(x.u.interval.seconds == 0);
        UT_ASSERT(x.u.interval.microseconds == 0);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, ZT("P429DT10H30M")) == 0);
    }
    {
        MI_Datetime x;
        UT_ASSERT(ParseWSManDatetime(ZT("P1Y2MT"), &x) == 0);
        UT_ASSERT(x.isTimestamp == 0);
        UT_ASSERT(x.u.interval.days == 426);
        UT_ASSERT(x.u.interval.hours == 0);
        UT_ASSERT(x.u.interval.minutes == 0);
        UT_ASSERT(x.u.interval.seconds == 0);
        UT_ASSERT(x.u.interval.microseconds == 0);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, ZT("P426D")) == 0);
    }
    {
        MI_Datetime x;
        UT_ASSERT(ParseWSManDatetime(ZT("PT0.000001S"), &x) == 0);
        UT_ASSERT(x.isTimestamp == 0);
        UT_ASSERT(x.u.interval.days == 0);
        UT_ASSERT(x.u.interval.hours == 0);
        UT_ASSERT(x.u.interval.minutes == 0);
        UT_ASSERT(x.u.interval.seconds == 0);
        UT_ASSERT(x.u.interval.microseconds == 1);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, ZT("PT0.000001S")) == 0);
    }
    {
        MI_Datetime x;
        UT_ASSERT(ParseWSManDatetime(ZT("2010-12-31"), &x) == 0);
        UT_ASSERT(x.isTimestamp == 1);
        UT_ASSERT(x.u.timestamp.year == 2010);
        UT_ASSERT(x.u.timestamp.month == 12);
        UT_ASSERT(x.u.timestamp.day == 31);
        UT_ASSERT(x.u.timestamp.hour == 0);
        UT_ASSERT(x.u.timestamp.minute == 0);
        UT_ASSERT(x.u.timestamp.second == 0);
        UT_ASSERT(x.u.timestamp.microseconds == 0);
        UT_ASSERT(x.u.timestamp.utc == 0);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, ZT("2010-12-31")) == 0);
    }
    {
        MI_Datetime x;
        UT_ASSERT(ParseWSManDatetime(ZT("2010-1-1"), &x) == -1);
    }
    {
        MI_Datetime x;
        const ZChar STR[] = ZT("2010-12-31+06:33");
        UT_ASSERT(ParseWSManDatetime(STR, &x) == 0);
        UT_ASSERT(x.isTimestamp == 1);
        UT_ASSERT(x.u.timestamp.year == 2010);
        UT_ASSERT(x.u.timestamp.month == 12);
        UT_ASSERT(x.u.timestamp.day == 31);
        UT_ASSERT(x.u.timestamp.hour == 0);
        UT_ASSERT(x.u.timestamp.minute == 0);
        UT_ASSERT(x.u.timestamp.second == 0);
        UT_ASSERT(x.u.timestamp.microseconds == 0);
        UT_ASSERT(x.u.timestamp.utc == 393);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, STR) == 0);
    }
    {
        MI_Datetime x;
        const ZChar STR[] = ZT("2010-12-31-06:20");
        UT_ASSERT(ParseWSManDatetime(STR, &x) == 0);
        UT_ASSERT(x.isTimestamp == 1);
        UT_ASSERT(x.u.timestamp.year == 2010);
        UT_ASSERT(x.u.timestamp.month == 12);
        UT_ASSERT(x.u.timestamp.day == 31);
        UT_ASSERT(x.u.timestamp.hour == 0);
        UT_ASSERT(x.u.timestamp.minute == 0);
        UT_ASSERT(x.u.timestamp.second == 0);
        UT_ASSERT(x.u.timestamp.microseconds == 0);
        UT_ASSERT(x.u.timestamp.utc == -380);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, STR) == 0);
    }
    {
        MI_Datetime x;
        const ZChar STR[] = ZT("2010-12-31");
        UT_ASSERT(ParseWSManDatetime(STR, &x) == 0);
        UT_ASSERT(x.isTimestamp == 1);
        UT_ASSERT(x.u.timestamp.year == 2010);
        UT_ASSERT(x.u.timestamp.month == 12);
        UT_ASSERT(x.u.timestamp.day == 31);
        UT_ASSERT(x.u.timestamp.hour == 0);
        UT_ASSERT(x.u.timestamp.minute == 0);
        UT_ASSERT(x.u.timestamp.second == 0);
        UT_ASSERT(x.u.timestamp.microseconds == 0);
        UT_ASSERT(x.u.timestamp.utc == 0);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, STR) == 0);
    }
    {
        MI_Datetime x;
        UT_ASSERT(ParseWSManDatetime(ZT("2010-12-31T12:30:03Z"), &x) == 0);
        UT_ASSERT(x.isTimestamp == 1);
        UT_ASSERT(x.u.timestamp.year == 2010);
        UT_ASSERT(x.u.timestamp.month == 12);
        UT_ASSERT(x.u.timestamp.day == 31);
        UT_ASSERT(x.u.timestamp.hour == 12);
        UT_ASSERT(x.u.timestamp.minute == 30);
        UT_ASSERT(x.u.timestamp.second == 03);
        UT_ASSERT(x.u.timestamp.microseconds == 0);
        UT_ASSERT(x.u.timestamp.utc == 0);
    }
    {
        MI_Datetime x;
        const ZChar STR[] = ZT("2010-12-31T12:30:03+06:23");
        UT_ASSERT(ParseWSManDatetime(STR, &x) == 0);

        UT_ASSERT(x.isTimestamp == 1);
        UT_ASSERT(x.u.timestamp.year == 2010);
        UT_ASSERT(x.u.timestamp.month == 12);
        UT_ASSERT(x.u.timestamp.day == 31);
        UT_ASSERT(x.u.timestamp.hour == 12);
        UT_ASSERT(x.u.timestamp.minute == 30);
        UT_ASSERT(x.u.timestamp.second == 03);
        UT_ASSERT(x.u.timestamp.microseconds == 0);
        UT_ASSERT(x.u.timestamp.utc == 383);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, STR) == 0);
    }
    {
        MI_Datetime x;
        const ZChar STR[] = ZT("12:30:03+06:23");
        UT_ASSERT(ParseWSManDatetime(STR, &x) == 0);
        UT_ASSERT(x.isTimestamp == 1);
        UT_ASSERT(x.u.timestamp.year == 0);
        UT_ASSERT(x.u.timestamp.month == 0);
        UT_ASSERT(x.u.timestamp.day == 0);
        UT_ASSERT(x.u.timestamp.hour == 12);
        UT_ASSERT(x.u.timestamp.minute == 30);
        UT_ASSERT(x.u.timestamp.second == 03);
        UT_ASSERT(x.u.timestamp.microseconds == 0);
        UT_ASSERT(x.u.timestamp.utc == 383);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, STR) == 0);
    }
    {
        MI_Datetime x;
        const ZChar STR[] = ZT("12:30:03.1234567+06:23");
        UT_ASSERT(ParseWSManDatetime(STR, &x) == 0);
        UT_ASSERT(x.isTimestamp == 1);
        UT_ASSERT(x.u.timestamp.year == 0);
        UT_ASSERT(x.u.timestamp.month == 0);
        UT_ASSERT(x.u.timestamp.day == 0);
        UT_ASSERT(x.u.timestamp.hour == 12);
        UT_ASSERT(x.u.timestamp.minute == 30);
        UT_ASSERT(x.u.timestamp.second == 03);
        UT_ASSERT(x.u.timestamp.microseconds == 123456);
        UT_ASSERT(x.u.timestamp.utc == 383);
        //PrintDatetime(&x);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, ZT("12:30:03.123456+06:23")) == 0);
    }
    {
        MI_Datetime x;
        const ZChar STR[] = ZT("2010-12-31T12:30:03.123456+06:23");
        UT_ASSERT(ParseWSManDatetime(STR, &x) == 0);
        UT_ASSERT(x.isTimestamp == 1);
        UT_ASSERT(x.u.timestamp.year == 2010);
        UT_ASSERT(x.u.timestamp.month == 12);
        UT_ASSERT(x.u.timestamp.day == 31);
        UT_ASSERT(x.u.timestamp.hour == 12);
        UT_ASSERT(x.u.timestamp.minute == 30);
        UT_ASSERT(x.u.timestamp.second == 03);
        UT_ASSERT(x.u.timestamp.microseconds == 123456);
        UT_ASSERT(x.u.timestamp.utc == 383);
        //PrintDatetime(&x);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, STR) == 0);
    }
    {
        MI_Datetime x;
        UT_ASSERT(ParseWSManDatetime( ZT("P4294967295D"), &x) == 0);
        UT_ASSERT(x.isTimestamp == 0);
        UT_ASSERT(x.u.interval.days == 4294967295U);
        UT_ASSERT(x.u.interval.hours == 0);
        UT_ASSERT(x.u.interval.minutes == 0);
        UT_ASSERT(x.u.interval.seconds == 0);
        UT_ASSERT(x.u.interval.microseconds == 0);

        FormatWSManDatetime(&x, buf);
        UT_ASSERT(Zcmp(buf, ZT("P4294967295D")) == 0);
    }
}

typedef struct _TestBucket /* derives from HashBucket */
{
    struct _TestBucket* next;
    ZChar* key;
    long data;
}
TestBucket;

static size_t TestHash(
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

static int TestEqual(
    const HashBucket* bucket1_,
    const HashBucket* bucket2_)
{
    TestBucket* bucket1 = (TestBucket*)bucket1_;
    TestBucket* bucket2 = (TestBucket*)bucket2_;
    return Zcmp(bucket1->key, bucket2->key) == 0;
}

static void TestRelease(
    HashBucket* bucket_)
{
    TestBucket* bucket = (TestBucket*)bucket_;

    free(bucket->key);
    free(bucket);
}

static void TestHashTable1()
{
    HashTable table;
    int r;
    TestBucket* b;

    r = HashTable_Init(&table, 1, TestHash, TestEqual, TestRelease);
    UT_ASSERT(r == 0);

    /* Insert some buckets */
    {
        /* Insert RED=1 */
        {
            b = (TestBucket*)calloc(1, sizeof(TestBucket));
            UT_ASSERT(b != 0);
            b->key = Zdup(ZT("RED"));
            b->data = 1;
            r = HashTable_Insert(&table, (HashBucket*)b);
            UT_ASSERT(r == 0);
        }

        /* Insert GREEN=2 */
        {
            b = (TestBucket*)calloc(1, sizeof(TestBucket));
            UT_ASSERT(b != 0);
            b->key = Zdup(ZT("GREEN"));
            b->data = 2;
            r = HashTable_Insert(&table, (HashBucket*)b);
            UT_ASSERT(r == 0);
        }

        /* Insert BLUE=3 */
        {
            b = (TestBucket*)calloc(1, sizeof(TestBucket));
            UT_ASSERT(b != 0);
            b->key = Zdup(ZT("BLUE"));
            b->data = 3;
            r = HashTable_Insert(&table, (HashBucket*)b);
            UT_ASSERT(r == 0);

            /* Insert BLUE=3 again (should fail) */
            r = HashTable_Insert(&table, (HashBucket*)b);
            UT_ASSERT(r == 1);
        }


        /* Find RED=1 */
        {
            TestBucket key;
            key.key = (ZChar*)ZT("RED");
            b = (TestBucket*)HashTable_Find(&table, (const HashBucket*)&key);
            UT_ASSERT(b != 0);
            UT_ASSERT(Zcmp(b->key, ZT("RED")) == 0);
            UT_ASSERT(b->data == 1);
        }

        /* Find GREEN=2 */
        {
            TestBucket key;
            key.key = (ZChar*)ZT("GREEN");
            b = (TestBucket*)HashTable_Find(&table, (const HashBucket*)&key);
            UT_ASSERT(b != 0);
            UT_ASSERT(Zcmp(b->key, ZT("GREEN")) == 0);
            UT_ASSERT(b->data == 2);
        }

        /* Find BLUE=3 */
        {
            TestBucket key;
            key.key = (ZChar*)ZT("BLUE");
            b = (TestBucket*)HashTable_Find(&table, (const HashBucket*)&key);
            UT_ASSERT(b != 0);
            UT_ASSERT(Zcmp(b->key, ZT("BLUE")) == 0);
            UT_ASSERT(b->data == 3);
        }

        /* Find YELLOW=4 (should fail) */
        {
            TestBucket key;
            key.key = (ZChar*)ZT("YELLOW");
            b = (TestBucket*)HashTable_Find(&table, (const HashBucket*)&key);
            UT_ASSERT(b == 0);
        }

        /* Remove RED */
        {
            TestBucket key;
            key.key = (ZChar*)ZT("RED");
            r = HashTable_Remove(&table, (const HashBucket*)&key);
            UT_ASSERT(r == 0);

            /* Remove should fail now */
            r = HashTable_Remove(&table, (const HashBucket*)&key);
            UT_ASSERT(r == -1);
        }

        /* Remove GREEN */
        {
            TestBucket key;
            key.key = (ZChar*)ZT("GREEN");
            r = HashTable_Remove(&table, (const HashBucket*)&key);
            UT_ASSERT(r == 0);

            /* Remove should fail now */
            r = HashTable_Remove(&table, (const HashBucket*)&key);
            UT_ASSERT(r == -1);
        }

        /* Remove BLUE */
        {
            TestBucket key;
            key.key = (ZChar*)ZT("BLUE");
            r = HashTable_Remove(&table, (const HashBucket*)&key);
            UT_ASSERT(r == 0);

            /* Remove should fail now */
            r = HashTable_Remove(&table, (const HashBucket*)&key);
            UT_ASSERT(r == -1);
        }

        /* Remove YELLOW (should fail) */
        {
            TestBucket key;
            key.key = (ZChar*)ZT("YELLOW");
            r = HashTable_Remove(&table, (const HashBucket*)&key);
            UT_ASSERT(r == -1);
        }
    }

    /* Release all the memroy */
    HashTable_Destroy(&table);
}

static void TestHashTable2()
{
    HashTable table;
    int r;
    size_t i;
    const size_t N = 10000;

    /* Create the hash table */

    r = HashTable_Init(&table, 63, TestHash, TestEqual, TestRelease);
    UT_ASSERT(r == 0);

    /* Insert N buckets into hash table */

    for (i = 0; i < N; i++)
    {
        ZChar buf[32];
        TestBucket* b;

        Szprintf(buf, MI_COUNT(buf), ZT("%u"), (unsigned int)i);
        b = (TestBucket*)calloc(1, sizeof(TestBucket));
        UT_ASSERT(b != 0);
        b->key = Zdup(buf);
        b->data = (long)i;
        r = HashTable_Insert(&table, (HashBucket*)b);
        UT_ASSERT(r == 0);
    }

    /* Verify that each number is in the hash table */

    for (i = 0; i < N; i++)
    {
        ZChar buf[32];
        TestBucket* b;
        TestBucket kb;
        kb.key = buf;
        Szprintf(buf, MI_COUNT(buf), ZT("%u"), (unsigned int)i);

        /* Find it */

        b = (TestBucket*)HashTable_Find(&table, (const HashBucket*)&kb);
        UT_ASSERT(b != 0);

        /* Check it */
        UT_ASSERT(Zcmp(b->key, buf) == 0);
    }

    /* Delete all the buckets */

    for (i = 0; i < N; i++)
    {
        ZChar buf[32];
        TestBucket kb;
        int r;

        kb.key = buf;
        Szprintf(buf, MI_COUNT(buf), ZT("%u"), (unsigned int)i);

        /* Find it */

        r = HashTable_Remove(&table, (const HashBucket*)&kb);
        UT_ASSERT(r == 0);
    }

    /* Release all the memroy */
    HashTable_Destroy(&table);
}

int TestBase64EncCallback(const char* data, size_t size, void* callbackData)
{
    vector<char>& buf = *((vector<char>*)callbackData);
    buf.insert(buf.end(), data, data + size);
    return 0;
}

int TestBase64DecCallback(const void* data, size_t size, void* callbackData)
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

    if (Base64Dec(&enc[0], enc.size(), TestBase64DecCallback, &dec) != 0)
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

static void TestBase64()
{
    UT_ASSERT(TestBase64Str("a", "YQ=="));
    UT_ASSERT(TestBase64Str("ab", "YWI="));
    UT_ASSERT(TestBase64Str("abc", "YWJj"));
    UT_ASSERT(TestBase64Str("abcd", "YWJjZA=="));
    UT_ASSERT(TestBase64Str("abcde", "YWJjZGU="));
    UT_ASSERT(TestBase64Str("Hello World!", "SGVsbG8gV29ybGQh"));
    UT_ASSERT(TestBase64Str("hello", "aGVsbG8="));
    UT_ASSERT(TestBase64Str(
        "Come what, come may; time and the hour run through the roughest day",
        "Q29tZSB3aGF0LCBjb21lIG1heTsgdGltZSBhbmQgdGhlIGhvdXIgcnVuIHRocm91Z2ggdGhlIHJvdWdoZXN0IGRheQ=="));

    UT_ASSERT(TestBase64Aux("a", 1) == 0);
    UT_ASSERT(TestBase64Aux("ab", 2) == 0);
    UT_ASSERT(TestBase64Aux("abc", 3) == 0);

    // Generate random data for varying lengths:

    for (size_t i = 0; i < 1024; i++)
    {
        vector<unsigned char> data;

        for (size_t j = 0; j < i; j++)
        {
            data.push_back(rand() % 256);
        }

        UT_ASSERT(TestBase64Aux(&data[0], data.size()) == 0);
    }
}

static void TestStrCopy()
{
    ZChar zbuf[64];
    char buf[64];

    ZStrlcpy(zbuf, "Hello World", MI_COUNT(zbuf));
    UT_ASSERT(Zcmp(zbuf, ZT("Hello World")) == 0);

    StrZlcpy(buf, zbuf, MI_COUNT(buf));
    UT_ASSERT(strcmp(buf, "Hello World") == 0);
}

static void TestPtrArray()
{
    PtrArray pa;

    PtrArray_Construct(&pa, 16, free);

    PtrArray_Append(&pa, Strdup("Red"));
    PtrArray_Append(&pa, Strdup("Green"));
    PtrArray_Append(&pa, Strdup("Blue"));

    UT_ASSERT(pa.size == 3);

    for (size_t i = 0; i < pa.size; i++)
    {
        switch (i)
        {
            case 0:
                UT_ASSERT(Strcmp((char*)pa.data[i], "Red") == 0);
                break;
            case 1:
                UT_ASSERT(Strcmp((char*)pa.data[i], "Green") == 0);
                break;
            case 2:
                UT_ASSERT(Strcmp((char*)pa.data[i], "Blue") == 0);
                break;
        }
    }

    PtrArray_Destruct(&pa);
}

static bool CheckNameLen(const ZChar* name)
{
    return Zlen(name) == NameLen(name, Hash(name));
}

static void TestHashCode()
{
    UT_ASSERT(CheckNameLen(ZT("a")));
    UT_ASSERT(CheckNameLen(ZT("abc")));
    UT_ASSERT(CheckNameLen(ZT("abcdefg")));
    UT_ASSERT(CheckNameLen(ZT("abcdefghijklmnopqrstuvwxyz")));

    const ZChar* str250 =
        ZT("00000000000000000000000000000000000000000000000000")
        ZT("00000000000000000000000000000000000000000000000000")
        ZT("00000000000000000000000000000000000000000000000000")
        ZT("00000000000000000000000000000000000000000000000000")
        ZT("00000000000000000000000000000000000000000000000000");

    UT_ASSERT(CheckNameLen(str250));

    const ZChar* str300 =
        ZT("00000000000000000000000000000000000000000000000000")
        ZT("00000000000000000000000000000000000000000000000000")
        ZT("00000000000000000000000000000000000000000000000000")
        ZT("00000000000000000000000000000000000000000000000000")
        ZT("00000000000000000000000000000000000000000000000000")
        ZT("00000000000000000000000000000000000000000000000000");

    UT_ASSERT(CheckNameLen(str300));
}

static void RunTests()
{
    UT_TEST(TestHashCode);
    UT_TEST(TestHashTable1);
    UT_TEST(TestHashTable2);
    UT_TEST(TestAllocator1);
    UT_TEST(TestAllocator2);
    UT_TEST(TestAllocator3);
    UT_TEST(TestGetName);
    UT_TEST(TestGetSize);
    UT_TEST(TestStringArray1);
    UT_TEST(TestStringArray2);
    UT_TEST(TestMessages);
    UT_TEST(TestMessages2);
    UT_TEST(TestStrings);
    UT_TEST(TestList);
    UT_TEST(TestFindClassDecl);
    UT_TEST(TestAllTypes);
#if 0
    UT_TEST(TestLib1);
    UT_TEST(TestLib2);
#endif
    UT_TEST(TestInstances);
    UT_TEST(TestDynamicInstances);
    UT_TEST(TestBuf);
    UT_TEST(TestBuf2);
    UT_TEST(TestBuf3);
    UT_TEST(TestBuf4);
    UT_TEST(TestPackInstance);
    UT_TEST(TestPage);
    UT_TEST(TestBaseCppAllTypes);
    UT_TEST(TestDir);
    UT_TEST(TestStrArr);
    UT_TEST(TestConf1);
    UT_TEST(TestConf2);
    UT_TEST(TestMkdirhier);
    UT_TEST(TestLog);
    UT_TEST(TestIntToStr);
    UT_TEST(TestGetOpt);
    UT_TEST(TestGetOptErr);
    UT_TEST(TestMatchKeys);
    UT_TEST(TestBase64);
    UT_TEST(TestStrCopy);
    UT_TEST(TestWSManDatetime);
    UT_TEST(TestPtrArray);
}

UT_ENTRY_POINT(RunTests);
