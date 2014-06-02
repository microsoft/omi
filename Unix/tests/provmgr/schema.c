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
#include "XYZ_Test.h"

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
** XYZ_Test
**
**==============================================================================
*/

/* property XYZ_Test.detailmessage */
static MI_CONST MI_PropertyDecl XYZ_Test_detailmessage_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0064650D, /* code */
    MI_T("detailmessage"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(XYZ_Test, detailmessage), /* offset */
    MI_T("XYZ_Test"), /* origin */
    MI_T("XYZ_Test"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST XYZ_Test_props[] =
{
    &XYZ_Test_detailmessage_prop,
};

/* parameter XYZ_Test.Create(): CommandLine */
static MI_CONST MI_ParameterDecl XYZ_Test_Create_CommandLine_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0063650B, /* code */
    MI_T("CommandLine"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(XYZ_Test_Create, CommandLine), /* offset */
};

/* parameter XYZ_Test.Create(): result */
static MI_CONST MI_ParameterDecl XYZ_Test_Create_result_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00727406, /* code */
    MI_T("result"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(XYZ_Test_Create, result), /* offset */
};

/* parameter XYZ_Test.Create(): MIReturn */
static MI_CONST MI_ParameterDecl XYZ_Test_Create_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(XYZ_Test_Create, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST XYZ_Test_Create_params[] =
{
    &XYZ_Test_Create_MIReturn_param,
    &XYZ_Test_Create_CommandLine_param,
    &XYZ_Test_Create_result_param,
};

/* method XYZ_Test.Create() */
MI_CONST MI_MethodDecl XYZ_Test_Create_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00636506, /* code */
    MI_T("Create"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    XYZ_Test_Create_params, /* parameters */
    MI_COUNT(XYZ_Test_Create_params), /* numParameters */
    sizeof(XYZ_Test_Create), /* size */
    MI_UINT32, /* returnType */
    MI_T("XYZ_Test"), /* origin */
    MI_T("XYZ_Test"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)XYZ_Test_Invoke_Create, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST XYZ_Test_meths[] =
{
    &XYZ_Test_Create_rtti,
};

static MI_CONST MI_ProviderFT XYZ_Test_funcs =
{
  (MI_ProviderFT_Load)XYZ_Test_Load,
  (MI_ProviderFT_Unload)XYZ_Test_Unload,
  (MI_ProviderFT_GetInstance)XYZ_Test_GetInstance,
  (MI_ProviderFT_EnumerateInstances)XYZ_Test_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)XYZ_Test_CreateInstance,
  (MI_ProviderFT_ModifyInstance)XYZ_Test_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)XYZ_Test_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class XYZ_Test */
MI_CONST MI_ClassDecl XYZ_Test_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00787408, /* code */
    MI_T("XYZ_Test"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    XYZ_Test_props, /* properties */
    MI_COUNT(XYZ_Test_props), /* numProperties */
    sizeof(XYZ_Test), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    XYZ_Test_meths, /* methods */
    MI_COUNT(XYZ_Test_meths), /* numMethods */
    &schemaDecl, /* schema */
    &XYZ_Test_funcs, /* functions */
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
    &XYZ_Test_rtti,
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

