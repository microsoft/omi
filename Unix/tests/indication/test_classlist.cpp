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
#include <indication/indimgr/classlist.h>
#include <indication/indimgr/host.h>
#include <pal/strings.h>
#include <pal/dir.h>
#include <base/paths.h>
#include <omi_error/OMI_Error.h>
#include "util.h"

using namespace std;

struct Test_ClasslistStruct
{
    MI_ConstString query;
    MI_ConstString queryDialect;
    MI_ConstString nameSpace;
    Filter* filter;
    MI_Boolean pregInited;
    ProvReg* preg;
    MI_Result lastErrorCode;
    MI_Instance* lastError;
};

NITS_EXTERN_C void _ClassList_SetLastError(
    _In_opt_ void* context,
    _In_ MI_Instance* error,
    MI_Result result)
{
    Test_ClasslistStruct* tcs = (Test_ClasslistStruct*)context;
    tcs->lastError = error;
    tcs->lastErrorCode = result;
}

int _Filter_SetOneNamespace(_Inout_ Filter* self,
    _In_ MI_ConstString nameSpace)
{
    MI_StringA nsa;
    MI_String data[1];
    nsa.size = 1;
    nsa.data = data;
    data[0] = (MI_Char*)nameSpace;
    /* Clean _container field to workaround limitation of Filter_SetNamespace */
    void* container = self->base.base._container;
    self->base.base._container = NULL;
    int r = Filter_SetNamespace(self, &nsa);
    /* Reset _container field */
    self->base.base._container = container;
    return r;
}

void Test_ClasslistStruct_ResetLastError(
    _In_ Test_ClasslistStruct* tcs)
{
    if (tcs->lastError)
        MI_Instance_Delete(tcs->lastError);
    tcs->lastError = NULL;
    tcs->lastErrorCode = MI_RESULT_OK;
}

IndicationHost g_HostDefault = {NULL, NULL, NULL};


NitsSetup0(Test_Setup, Test_ClasslistStruct)
    Test_ClasslistStruct* tcs = NitsContext()->_Test_ClasslistStruct;
    tcs->lastError = NULL;
    tcs->lastErrorCode = MI_RESULT_OK;

    string root = OMI_GetPath(ID_PREFIX);
    string omiregdir = root + "/tests/provreg/omiregister";
    ProvReg* preg = (ProvReg*)PAL_Malloc(sizeof(ProvReg));
    NitsAssert(NULL != preg, PAL_T("Failed to create ProgReg object"));
    if (NULL == preg)
        return;

    tcs->preg = preg;
    MI_Result r = ProvReg_Init(tcs->preg, omiregdir.c_str());
    NitsAssert(r == MI_RESULT_OK, PAL_T("Failed to initialize ProgReg"));
    tcs->pregInited = (r == MI_RESULT_OK) ? MI_TRUE : MI_FALSE;
    Filter* filter = Filter_New(tcs->query, tcs->queryDialect, &tcs->lastError);
    NitsAssert(NULL != filter, PAL_T("Failed to create filter object"));
    if (filter)
    {
        int r = _Filter_SetOneNamespace(filter, tcs->nameSpace);
        NitsAssert(0 == r, PAL_T("Failed to set namespaces to filter object"));
        filter->base.errhandler.context = (void*)tcs;
        filter->base.errhandler.setlasterror = _ClassList_SetLastError;
        filter->base.base._container = &g_HostDefault;

        if (r == 0)
            tcs->filter = filter;
    }
NitsEndSetup


NitsCleanup(Test_Setup)
    Test_ClasslistStruct* tcs = NitsContext()->_Test_ClasslistStruct;
    if (MI_TRUE == tcs->pregInited)
    {
        ProvReg_Destroy(tcs->preg);
        tcs->pregInited = MI_FALSE;
    }
    if (NULL != tcs->preg)
    {
        PAL_Free(tcs->preg);
        tcs->preg = NULL;
    }
    if (tcs->filter)
    {
        Filter_Release(tcs->filter);
        tcs->filter = NULL;
    }
    if (tcs->lastError)
    {
        MI_Instance_Delete(tcs->lastError);
        tcs->lastError = NULL;
    }
NitsEndCleanup

static struct Test_ClasslistStruct sTestCS1 = {
    MI_T("select * from XYZ_ChildIndication1"),
    QUERY_LANGUAGE_WQL,
    MI_T("root/indication"),
    NULL,
    MI_FALSE,
    NULL};

NitsTest1(TestClassList_Success_OneClass, Test_Setup, sTestCS1)
    ProvReg* preg = NitsContext()->_Test_Setup->_Test_ClasslistStruct->preg;
    Filter* filter = NitsContext()->_Test_Setup->_Test_ClasslistStruct->filter;

    IndicationClassList* clist = IndicationClassList_NewByFilter(preg, filter);
    NitsAssert(NULL != clist, PAL_T("failed to create classlist"));
    if (NULL == clist)
        return;
    IndicationClassEntry* pce = clist->head;
    NitsAssert(NULL != pce, PAL_T("ClassList is empty"));
    if (pce)
    {
        NitsAssert(Tcscasecmp(pce->regentry->className, MI_T("XYZ_ChildIndication1")) == 0, PAL_T("Unexpected class was found"));
        NitsAssert(NULL == pce->next, PAL_T("ClassList contains more than 1 class"));
    }
    IndicationClassList_Delete(clist);
NitsEndTest

void _VerifyIndicaitonClassDiscoveryResult(
    _In_ Test_ClasslistStruct* tcs,
    _In_opt_ StringTagElement* ste,
    _In_ MI_Uint32 steSize,
    _In_ MI_Result errorCode = MI_RESULT_OK)
{
    ProvReg* preg = tcs->preg;
    Filter* filter = tcs->filter;
    Test_ClasslistStruct_ResetLastError(tcs);
    IndicationClassList* clist = IndicationClassList_NewByFilter(preg, filter);
    if (errorCode == MI_RESULT_OK)
    {
        NitsAssert(NULL != clist, PAL_T("failed to create classlist"));
    }
    else
    {
        NitsCompare(errorCode, tcs->lastErrorCode, PAL_T("Unexpected error code"));
    }

    if (NULL == clist)
        return;

    NitsAssert(NULL != clist->head, PAL_T("ClassList is empty"));
    IndicationClassEntry* pce = clist->head;

    /* copy sTestCS2_ClassList to classlist */
    MI_Uint32 steBytesSize = sizeof(StringTagElement) * steSize;
    StringTagElement* classlist = (StringTagElement*)PAL_Malloc(steBytesSize);
    if (classlist == NULL)
    {
        NitsAssert(false, PAL_T("Allocate memory for classlist failed"));
        IndicationClassList_Delete(clist);
        return;
    }

    memcpy(classlist, ste, steBytesSize);
    while(pce)
    {
        NitsAssert(1 == IsInArray(pce->regentry->className, classlist, steSize), PAL_T("Unexpected class was found"));
        pce = pce->next;
    }
    for (MI_Uint32 i = 0; i < steSize; i++)
    {
        if (classlist[i].tag != 1)
            NitsAssert(false, PAL_T("Some class was not in classlist"));
    }
    PAL_Free(classlist);
    IndicationClassList_Delete(clist);
}

static StringTagElement sTestCS2_ClassList[] =
{
    { MI_T("XYZ_Indication"),0, 0},
    { MI_T("XYZ_ChildIndication1"),0, 0},
    { MI_T("XYZ_ChildIndication2"),0, 0},
    { MI_T("XYZ_ChildIndication3"),0, 0},
    { MI_T("XYZ_ChildIndication4"),0, 0},
};

static struct Test_ClasslistStruct sTestCS2 = {
    MI_T("select * from CIM_IndicatiON"),
    QUERY_LANGUAGE_CQL,
    MI_T("root/indication"),
    NULL,
    MI_FALSE,
    NULL};

NitsTest1(TestClassList_Success_ClassHierarchy, Test_Setup, sTestCS2)
    _VerifyIndicaitonClassDiscoveryResult(
        NitsContext()->_Test_Setup->_Test_ClasslistStruct,
        sTestCS2_ClassList,
        MI_COUNT(sTestCS2_ClassList));
NitsEndTest

NitsTest1(TestClassList_NonexistNamespace, Test_Setup, sTestCS2)
    Test_ClasslistStruct* tcs = NitsContext()->_Test_Setup->_Test_ClasslistStruct;
    ProvReg* preg = tcs->preg;
    Filter* filter = tcs->filter;
    int r = _Filter_SetOneNamespace(filter, MI_T("nonexist/namespace"));
    NitsAssert(0 == r, PAL_T("Failed to set namespaces to filter object"));
    if (r == 0)
    {
        Test_ClasslistStruct_ResetLastError(tcs);
        IndicationClassList* clist = IndicationClassList_NewByFilter(preg, filter);
        NitsAssert(NULL == clist, PAL_T("Should found no class"));
        NitsIgnoringError(); // this is negative case and OOM and the user error result in same thing
    }
NitsEndTest

static struct Test_ClasslistStruct sTestCS4 = {
    MI_T("select * from CIM_NonExistIndication"),
    QUERY_LANGUAGE_CQL,
    MI_T("root/indication"),
    NULL,
    MI_FALSE,
    NULL};
NitsTest1(TestClassList_NotFoundClass, Test_Setup, sTestCS4)
    Test_ClasslistStruct* tcs = NitsContext()->_Test_Setup->_Test_ClasslistStruct;
    ProvReg* preg = tcs->preg;
    Filter* filter = tcs->filter;
    Test_ClasslistStruct_ResetLastError(tcs);
    IndicationClassList* clist = IndicationClassList_NewByFilter(preg, filter);
    NitsAssert(NULL == clist, PAL_T("Unexpected class was discovered"));
    NitsIgnoringError(); // this is negative case and OOM and the user error result in same thing
NitsEndTest

/*
**==============================================================================
**
**  Positive test for lifecycle indication query
**
**  Following test case is designed to test discovery Indication Classes for a
**  given lifecycle query; Although the query is not a valid lifecycle query
**  since it has no isa operator; but there are explicit indication class derives
**  from CIM_InstIndication class under target namespace, so it is a supported
**  scenario
**
**==============================================================================
*/
static StringTagElement sTestCS5_ClassList[] =
{
    { MI_T("TEST_ProcessCreated"),0, 0},
    { MI_T("TEST_ProcessTerminated"),0, 0},
};
static struct Test_ClasslistStruct sTestCS5 = {
    MI_T("select * from CIM_InstIndication"),
    QUERY_LANGUAGE_CQL,
    MI_T("root/indication2"),
    NULL,
    MI_FALSE,
    NULL};
NitsTest1(TestClassList_Success_Lifecycle_IndicationClassOnly, Test_Setup, sTestCS5)
    _VerifyIndicaitonClassDiscoveryResult(
        NitsContext()->_Test_Setup->_Test_ClasslistStruct,
        sTestCS5_ClassList,
        MI_COUNT(sTestCS5_ClassList),
        MI_RESULT_OK);
NitsEndTest

/*
**==============================================================================
**
**  Positive test for lifecycle indication query
**  Following test cases are designed to test discovering Indication Classes for a
**  given lifecycle query targets to both indication & normal classes
**
**==============================================================================
*/
static StringTagElement s_ClassListMixed[] =
{
    { MI_T("TEST_ProcessCreated"),0, 0},
    { MI_T("TEST_ProcessTerminated"),0, 0},
    { MI_T("MSFT_Person"),0, 0},
    { MI_T("MSFT_Person2"),0, 0},
};
static struct Test_ClasslistStruct sTestCS_Mixed1 = {
    MI_T("select * from CIM_InstIndication where SourceInstance isa MSFT_Base"),
    QUERY_LANGUAGE_CQL,
    MI_T("root/indication2"),
    NULL,
    MI_FALSE,
    NULL};
NitsTest1(TestClassList_Success_Lifecycle_Mixed, Test_Setup, sTestCS_Mixed1)
    _VerifyIndicaitonClassDiscoveryResult(
        NitsContext()->_Test_Setup->_Test_ClasslistStruct,
        s_ClassListMixed,
        MI_COUNT(s_ClassListMixed),
        MI_RESULT_OK);
NitsEndTest

static struct Test_ClasslistStruct sTestCS_Mixed2 = {
    MI_T("select * from CIM_InstIndication where (SourceInstance isa MSFT_Base) AND ((SourceInstanceHost <> NULL) OR (SourceInstanceHost <> \"test\"))"),
    QUERY_LANGUAGE_CQL,
    MI_T("root/indication2"),
    NULL,
    MI_FALSE,
    NULL};
NitsTest1(TestClassList_Success_Lifecycle_Mixed2, Test_Setup, sTestCS_Mixed2)
    _VerifyIndicaitonClassDiscoveryResult(
        NitsContext()->_Test_Setup->_Test_ClasslistStruct,
        s_ClassListMixed,
        MI_COUNT(s_ClassListMixed),
        MI_RESULT_OK);
NitsEndTest

/*
**==============================================================================
**
**  Positive test for lifecycle indication query
**  Following test cases are designed to test discovering Indication Classes for a
**  given lifecycle query targets to only normal classes (no indication class
**  inherits from CIM_InstModification under root/indication2
**
**==============================================================================
*/
static StringTagElement s_ClassList_NormalClassOnly[] =
{
    { MI_T("MSFT_Person"),0, 0},
    { MI_T("MSFT_Person2"),0, 0},
};
static struct Test_ClasslistStruct sTestCS_NormalClassOnly = {
    MI_T("select * from CIM_InstModification where (SourceInstance isa MSFT_Animal) AND (PreviousInstance <> NULL)"),
    QUERY_LANGUAGE_CQL,
    MI_T("root/indication2"),
    NULL,
    MI_FALSE,
    NULL};
NitsTest1(TestClassList_Success_Lifecycle_Mixed3, Test_Setup, sTestCS_NormalClassOnly)
    _VerifyIndicaitonClassDiscoveryResult(
        NitsContext()->_Test_Setup->_Test_ClasslistStruct,
        s_ClassList_NormalClassOnly,
        MI_COUNT(s_ClassList_NormalClassOnly),
        MI_RESULT_OK);
NitsEndTest

static struct Test_ClasslistStruct sTestCS_NormalClassOnly2 = {
    MI_T("select * from CIM_InstModification where (PreviousInstance isa MSFT_Base) AND ((SourceInstanceHost <> NULL) OR (SourceInstanceHost <> \"test\") OR (2>1) )"),
    QUERY_LANGUAGE_CQL,
    MI_T("root/indication2"),
    NULL,
    MI_FALSE,
    NULL};
NitsTest1(TestClassList_Success_Lifecycle_Mixed4, Test_Setup, sTestCS_NormalClassOnly2)
    _VerifyIndicaitonClassDiscoveryResult(
        NitsContext()->_Test_Setup->_Test_ClasslistStruct,
        s_ClassList_NormalClassOnly,
        MI_COUNT(s_ClassList_NormalClassOnly),
        MI_RESULT_OK);
NitsEndTest

/*
**==============================================================================
**
**  Positive test for lifecycle indication query
**  Following test cases are designed to test discovering Indication Classes for a
**  given lifecycle query targets to only one class
**
**==============================================================================
*/
static StringTagElement s_ClassList_OneClass[] =
{
    { MI_T("MSFT_Person2"),0, 0},
};
static struct Test_ClasslistStruct sTestCS_OneClass = {
    MI_T("select * from CIM_InstMethodCall where (SourceInstance ISA MSFT_Person2)"),
    QUERY_LANGUAGE_CQL,
    MI_T("root/indication2"),
    NULL,
    MI_FALSE,
    NULL};
NitsTest1(TestClassList_Success_Lifecycle_OneClass, Test_Setup, sTestCS_OneClass)
    _VerifyIndicaitonClassDiscoveryResult(
        NitsContext()->_Test_Setup->_Test_ClasslistStruct,
        s_ClassList_OneClass,
        MI_COUNT(s_ClassList_OneClass),
        MI_RESULT_OK);
NitsEndTest

/*
**==============================================================================
**
**  Negative test for lifecycle indication query,
**  no indication class found
**
**==============================================================================
*/
static struct Test_ClasslistStruct sTestCS_NOTFOUND = {
    MI_T("select * from CIM_InstRead where SourceInstance isa NON_EXIST_CLASS"),
    QUERY_LANGUAGE_CQL,
    MI_T("root/indication2"),
    NULL,
    MI_FALSE,
    NULL};
NitsTest1(TestClassList_Fail_Lifecycle_NOT_FOUND, Test_Setup, sTestCS_NOTFOUND)
    Test_ClasslistStruct* tcs = NitsContext()->_Test_Setup->_Test_ClasslistStruct;
    _VerifyIndicaitonClassDiscoveryResult(
        tcs,
        NULL,
        0,
        MI_RESULT_NOT_FOUND);
NitsEndTest

/*
**==============================================================================
**
**  Negative test for lifecycle indication query,
**  Invalid lifecycle indication query: ISA operator WITHIN OR sub-clause
**
**==============================================================================
*/
static struct Test_ClasslistStruct sTestCS_InvalidQuery1 = {
    MI_T("select * from CIM_InstRead where (SourceInstance isa UnkownClass) OR (2>1)"),
    QUERY_LANGUAGE_CQL,
    MI_T("root/indication2"),
    NULL,
    MI_FALSE,
    NULL};
NitsTest1(TestClassList_Fail_Lifecycle_InvalidQuery1, Test_Setup, sTestCS_InvalidQuery1)
    Test_ClasslistStruct* tcs = NitsContext()->_Test_Setup->_Test_ClasslistStruct;
    _VerifyIndicaitonClassDiscoveryResult(
        tcs,
        NULL,
        0,
        MI_RESULT_NOT_SUPPORTED);
NitsEndTest

/*
**==============================================================================
**
**  Negative test for lifecycle indication query,
**  Invalid lifecycle indication query: Non-exist embedded property name
**
**==============================================================================
*/
static struct Test_ClasslistStruct sTestCS_InvalidQuery2 = {
    MI_T("select * from CIM_InstRead where (UnknownProperty isa MSFT_Base)"),
    QUERY_LANGUAGE_CQL,
    MI_T("root/indication2"),
    NULL,
    MI_FALSE,
    NULL};
NitsTest1(TestClassList_Fail_Lifecycle_InvalidQuery2, Test_Setup, sTestCS_InvalidQuery2)
    Test_ClasslistStruct* tcs = NitsContext()->_Test_Setup->_Test_ClasslistStruct;
    _VerifyIndicaitonClassDiscoveryResult(
        tcs,
        NULL,
        0,
        MI_RESULT_INVALID_QUERY);
NitsEndTest

/*
**==============================================================================
**
**  Negative test for lifecycle indication query,
**  Invalid lifecycle indication query: ISA operator WITHIN OR clause
**
**==============================================================================
*/
static struct Test_ClasslistStruct sTestCS_InvalidQuery3 = {
    MI_T("select * from CIM_InstModification where (PreviousInstance isa MSFT_Base) AND ((SourceInstanceHost <> NULL) AND (SourceInstanceHost <> \"test\")) OR (2>1)"),
    QUERY_LANGUAGE_CQL,
    MI_T("root/indication2"),
    NULL,
    MI_FALSE,
    NULL};
NitsTest1(TestClassList_Fail_Lifecycle_InvalidQuery3, Test_Setup, sTestCS_InvalidQuery3)
    Test_ClasslistStruct* tcs = NitsContext()->_Test_Setup->_Test_ClasslistStruct;
    _VerifyIndicaitonClassDiscoveryResult(
        tcs,
        NULL,
        0,
        MI_RESULT_NOT_SUPPORTED);
NitsEndTest

