/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#include <ctype.h>
#include <MI.h>
#include "OMI_Tester.h"

/*
**==============================================================================
**
** Schema Declaration
**
**==============================================================================
*/

extern MI_SchemaDecl schemaDecl;

/*
**==============================================================================
**
** Qualifier declarations
**
**==============================================================================
*/

/*
**==============================================================================
**
** OMI_Tester
**
**==============================================================================
*/

/* property OMI_Tester.Key */
static MI_CONST MI_PropertyDecl OMI_Tester_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Tester, Key), /* offset */
    MI_T("OMI_Tester"), /* origin */
    MI_T("OMI_Tester"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST OMI_Tester_props[] =
{
    &OMI_Tester_Key_prop,
};

/* parameter OMI_Tester.Func1(): In1 */
static MI_CONST MI_ParameterDecl OMI_Tester_Func1_In1_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00693103, /* code */
    MI_T("In1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Tester_Func1, In1), /* offset */
};

/* parameter OMI_Tester.Func1(): In2 */
static MI_CONST MI_ParameterDecl OMI_Tester_Func1_In2_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00693203, /* code */
    MI_T("In2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Tester_Func1, In2), /* offset */
};

/* parameter OMI_Tester.Func1(): In3 */
static MI_CONST MI_ParameterDecl OMI_Tester_Func1_In3_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00693303, /* code */
    MI_T("In3"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Tester_Func1, In3), /* offset */
};

/* parameter OMI_Tester.Func1(): Out1 */
static MI_CONST MI_ParameterDecl OMI_Tester_Func1_Out1_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F3104, /* code */
    MI_T("Out1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Tester_Func1, Out1), /* offset */
};

/* parameter OMI_Tester.Func1(): Out2 */
static MI_CONST MI_ParameterDecl OMI_Tester_Func1_Out2_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F3204, /* code */
    MI_T("Out2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Tester_Func1, Out2), /* offset */
};

/* parameter OMI_Tester.Func1(): Out3 */
static MI_CONST MI_ParameterDecl OMI_Tester_Func1_Out3_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F3304, /* code */
    MI_T("Out3"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Tester_Func1, Out3), /* offset */
};

/* parameter OMI_Tester.Func1(): MIReturn */
static MI_CONST MI_ParameterDecl OMI_Tester_Func1_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(OMI_Tester_Func1, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST OMI_Tester_Func1_params[] =
{
    &OMI_Tester_Func1_MIReturn_param,
    &OMI_Tester_Func1_In1_param,
    &OMI_Tester_Func1_In2_param,
    &OMI_Tester_Func1_In3_param,
    &OMI_Tester_Func1_Out1_param,
    &OMI_Tester_Func1_Out2_param,
    &OMI_Tester_Func1_Out3_param,
};

/* method OMI_Tester.Func1() */
MI_CONST MI_MethodDecl OMI_Tester_Func1_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00663105, /* code */
    MI_T("Func1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    OMI_Tester_Func1_params, /* parameters */
    MI_COUNT(OMI_Tester_Func1_params), /* numParameters */
    sizeof(OMI_Tester_Func1), /* size */
    MI_UINT32, /* returnType */
    MI_T("OMI_Tester"), /* origin */
    MI_T("OMI_Tester"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)OMI_Tester_Invoke_Func1, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST OMI_Tester_meths[] =
{
    &OMI_Tester_Func1_rtti,
};

static MI_CONST MI_ProviderFT OMI_Tester_funcs =
{
  (MI_ProviderFT_Load)OMI_Tester_Load,
  (MI_ProviderFT_Unload)OMI_Tester_Unload,
  (MI_ProviderFT_GetInstance)OMI_Tester_GetInstance,
  (MI_ProviderFT_EnumerateInstances)OMI_Tester_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)OMI_Tester_CreateInstance,
  (MI_ProviderFT_ModifyInstance)OMI_Tester_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)OMI_Tester_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class OMI_Tester */
MI_CONST MI_ClassDecl OMI_Tester_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006F720A, /* code */
    MI_T("OMI_Tester"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    OMI_Tester_props, /* properties */
    MI_COUNT(OMI_Tester_props), /* numProperties */
    sizeof(OMI_Tester), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    OMI_Tester_meths, /* methods */
    MI_COUNT(OMI_Tester_meths), /* numMethods */
    &schemaDecl, /* schema */
    &OMI_Tester_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** __mi_server
**
**==============================================================================
*/

MI_Server* __mi_server;
/*
**==============================================================================
**
** Schema
**
**==============================================================================
*/

static MI_ClassDecl MI_CONST* MI_CONST classes[] =
{
    &OMI_Tester_rtti,
};

MI_SchemaDecl schemaDecl =
{
    NULL, /* qualifierDecls */
    0, /* numQualifierDecls */
    classes, /* classDecls */
    MI_COUNT(classes), /* classDecls */
};

/*
**==============================================================================
**
** MI_Server Methods
**
**==============================================================================
*/

MI_Result MI_CALL MI_Server_GetVersion(
    MI_Uint32* version){
    return __mi_server->serverFT->GetVersion(version);
}

MI_Result MI_CALL MI_Server_GetSystemName(
    const MI_Char** systemName)
{
    return __mi_server->serverFT->GetSystemName(systemName);
}

