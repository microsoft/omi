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
#include "Test_Class.h"
#include "L_Lifecycle.h"
#include "R_Lifecycle.h"
#include "L_LifecycleC1.h"
#include "L_LifecycleC2.h"
#include "R_LifecycleC1.h"
#include "R_LifecycleC2.h"
#include "Test_Indication.h"
#include "L_IndicationC1.h"
#include "L_IndicationC2.h"
#include "L_IndicationC3.h"
#include "R_IndicationC1.h"
#include "R_IndicationC2.h"
#include "R_IndicationC3.h"
#include "Test_IndicationConfig.h"

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
** Test_Class
**
**==============================================================================
*/

/* property Test_Class.key */
static MI_CONST MI_PropertyDecl Test_Class_key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Class, key), /* offset */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    NULL,
};

/* property Test_Class.value */
static MI_CONST MI_PropertyDecl Test_Class_value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00766505, /* code */
    MI_T("value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Class, value), /* offset */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Test_Class_props[] =
{
    &Test_Class_key_prop,
    &Test_Class_value_prop,
};

/* parameter Test_Class.GenericInstMethod(): MIReturn */
static MI_CONST MI_ParameterDecl Test_Class_GenericInstMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Class_GenericInstMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Test_Class_GenericInstMethod_params[] =
{
    &Test_Class_GenericInstMethod_MIReturn_param,
};

/* method Test_Class.GenericInstMethod() */
MI_CONST MI_MethodDecl Test_Class_GenericInstMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00676411, /* code */
    MI_T("GenericInstMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Test_Class_GenericInstMethod_params, /* parameters */
    MI_COUNT(Test_Class_GenericInstMethod_params), /* numParameters */
    sizeof(Test_Class_GenericInstMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Test_Class_Invoke_GenericInstMethod, /* method */
};

/* parameter Test_Class.GenericMethod(): MIReturn */
static MI_CONST MI_ParameterDecl Test_Class_GenericMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Class_GenericMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Test_Class_GenericMethod_params[] =
{
    &Test_Class_GenericMethod_MIReturn_param,
};

/* method Test_Class.GenericMethod() */
MI_CONST MI_MethodDecl Test_Class_GenericMethod_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0067640D, /* code */
    MI_T("GenericMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Test_Class_GenericMethod_params, /* parameters */
    MI_COUNT(Test_Class_GenericMethod_params), /* numParameters */
    sizeof(Test_Class_GenericMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Test_Class_Invoke_GenericMethod, /* method */
};

/* parameter Test_Class.ThreadControl(): operation */
static MI_CONST MI_ParameterDecl Test_Class_ThreadControl_operation_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006F6E09, /* code */
    MI_T("operation"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Class_ThreadControl, operation), /* offset */
};

/* parameter Test_Class.ThreadControl(): MIReturn */
static MI_CONST MI_ParameterDecl Test_Class_ThreadControl_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Class_ThreadControl, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Test_Class_ThreadControl_params[] =
{
    &Test_Class_ThreadControl_MIReturn_param,
    &Test_Class_ThreadControl_operation_param,
};

/* method Test_Class.ThreadControl() */
MI_CONST MI_MethodDecl Test_Class_ThreadControl_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746C0D, /* code */
    MI_T("ThreadControl"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Test_Class_ThreadControl_params, /* parameters */
    MI_COUNT(Test_Class_ThreadControl_params), /* numParameters */
    sizeof(Test_Class_ThreadControl), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Test_Class_Invoke_ThreadControl, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST Test_Class_meths[] =
{
    &Test_Class_GenericInstMethod_rtti,
    &Test_Class_GenericMethod_rtti,
    &Test_Class_ThreadControl_rtti,
};

static MI_CONST MI_ProviderFT Test_Class_funcs =
{
  (MI_ProviderFT_Load)Test_Class_Load,
  (MI_ProviderFT_Unload)Test_Class_Unload,
  (MI_ProviderFT_GetInstance)Test_Class_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Test_Class_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Test_Class_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Test_Class_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Test_Class_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Test_Class */
MI_CONST MI_ClassDecl Test_Class_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0074730A, /* code */
    MI_T("Test_Class"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Test_Class_props, /* properties */
    MI_COUNT(Test_Class_props), /* numProperties */
    sizeof(Test_Class), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    Test_Class_meths, /* methods */
    MI_COUNT(Test_Class_meths), /* numMethods */
    &schemaDecl, /* schema */
    &Test_Class_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** L_Lifecycle
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST L_Lifecycle_props[] =
{
    &Test_Class_key_prop,
    &Test_Class_value_prop,
};

/* parameter L_Lifecycle.GenericInstMethod(): MIReturn */
static MI_CONST MI_ParameterDecl L_Lifecycle_GenericInstMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(L_Lifecycle_GenericInstMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST L_Lifecycle_GenericInstMethod_params[] =
{
    &L_Lifecycle_GenericInstMethod_MIReturn_param,
};

/* method L_Lifecycle.GenericInstMethod() */
MI_CONST MI_MethodDecl L_Lifecycle_GenericInstMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00676411, /* code */
    MI_T("GenericInstMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    L_Lifecycle_GenericInstMethod_params, /* parameters */
    MI_COUNT(L_Lifecycle_GenericInstMethod_params), /* numParameters */
    sizeof(L_Lifecycle_GenericInstMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)L_Lifecycle_Invoke_GenericInstMethod, /* method */
};

/* parameter L_Lifecycle.GenericMethod(): MIReturn */
static MI_CONST MI_ParameterDecl L_Lifecycle_GenericMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(L_Lifecycle_GenericMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST L_Lifecycle_GenericMethod_params[] =
{
    &L_Lifecycle_GenericMethod_MIReturn_param,
};

/* method L_Lifecycle.GenericMethod() */
MI_CONST MI_MethodDecl L_Lifecycle_GenericMethod_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0067640D, /* code */
    MI_T("GenericMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    L_Lifecycle_GenericMethod_params, /* parameters */
    MI_COUNT(L_Lifecycle_GenericMethod_params), /* numParameters */
    sizeof(L_Lifecycle_GenericMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)L_Lifecycle_Invoke_GenericMethod, /* method */
};

/* parameter L_Lifecycle.ThreadControl(): operation */
static MI_CONST MI_ParameterDecl L_Lifecycle_ThreadControl_operation_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006F6E09, /* code */
    MI_T("operation"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(L_Lifecycle_ThreadControl, operation), /* offset */
};

/* parameter L_Lifecycle.ThreadControl(): MIReturn */
static MI_CONST MI_ParameterDecl L_Lifecycle_ThreadControl_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(L_Lifecycle_ThreadControl, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST L_Lifecycle_ThreadControl_params[] =
{
    &L_Lifecycle_ThreadControl_MIReturn_param,
    &L_Lifecycle_ThreadControl_operation_param,
};

/* method L_Lifecycle.ThreadControl() */
MI_CONST MI_MethodDecl L_Lifecycle_ThreadControl_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746C0D, /* code */
    MI_T("ThreadControl"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    L_Lifecycle_ThreadControl_params, /* parameters */
    MI_COUNT(L_Lifecycle_ThreadControl_params), /* numParameters */
    sizeof(L_Lifecycle_ThreadControl), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)L_Lifecycle_Invoke_ThreadControl, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST L_Lifecycle_meths[] =
{
    &L_Lifecycle_GenericInstMethod_rtti,
    &L_Lifecycle_GenericMethod_rtti,
    &L_Lifecycle_ThreadControl_rtti,
};

static MI_CONST MI_ProviderFT L_Lifecycle_funcs =
{
  (MI_ProviderFT_Load)L_Lifecycle_Load,
  (MI_ProviderFT_Unload)L_Lifecycle_Unload,
  (MI_ProviderFT_GetInstance)L_Lifecycle_GetInstance,
  (MI_ProviderFT_EnumerateInstances)L_Lifecycle_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)L_Lifecycle_CreateInstance,
  (MI_ProviderFT_ModifyInstance)L_Lifecycle_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)L_Lifecycle_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class L_Lifecycle */
MI_CONST MI_ClassDecl L_Lifecycle_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006C650B, /* code */
    MI_T("L_Lifecycle"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    L_Lifecycle_props, /* properties */
    MI_COUNT(L_Lifecycle_props), /* numProperties */
    sizeof(L_Lifecycle), /* size */
    MI_T("Test_Class"), /* superClass */
    &Test_Class_rtti, /* superClassDecl */
    L_Lifecycle_meths, /* methods */
    MI_COUNT(L_Lifecycle_meths), /* numMethods */
    &schemaDecl, /* schema */
    &L_Lifecycle_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** R_Lifecycle
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST R_Lifecycle_props[] =
{
    &Test_Class_key_prop,
    &Test_Class_value_prop,
};

/* parameter R_Lifecycle.GenericInstMethod(): MIReturn */
static MI_CONST MI_ParameterDecl R_Lifecycle_GenericInstMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(R_Lifecycle_GenericInstMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST R_Lifecycle_GenericInstMethod_params[] =
{
    &R_Lifecycle_GenericInstMethod_MIReturn_param,
};

/* method R_Lifecycle.GenericInstMethod() */
MI_CONST MI_MethodDecl R_Lifecycle_GenericInstMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00676411, /* code */
    MI_T("GenericInstMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    R_Lifecycle_GenericInstMethod_params, /* parameters */
    MI_COUNT(R_Lifecycle_GenericInstMethod_params), /* numParameters */
    sizeof(R_Lifecycle_GenericInstMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)R_Lifecycle_Invoke_GenericInstMethod, /* method */
};

/* parameter R_Lifecycle.GenericMethod(): MIReturn */
static MI_CONST MI_ParameterDecl R_Lifecycle_GenericMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(R_Lifecycle_GenericMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST R_Lifecycle_GenericMethod_params[] =
{
    &R_Lifecycle_GenericMethod_MIReturn_param,
};

/* method R_Lifecycle.GenericMethod() */
MI_CONST MI_MethodDecl R_Lifecycle_GenericMethod_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0067640D, /* code */
    MI_T("GenericMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    R_Lifecycle_GenericMethod_params, /* parameters */
    MI_COUNT(R_Lifecycle_GenericMethod_params), /* numParameters */
    sizeof(R_Lifecycle_GenericMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)R_Lifecycle_Invoke_GenericMethod, /* method */
};

/* parameter R_Lifecycle.ThreadControl(): operation */
static MI_CONST MI_ParameterDecl R_Lifecycle_ThreadControl_operation_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006F6E09, /* code */
    MI_T("operation"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(R_Lifecycle_ThreadControl, operation), /* offset */
};

/* parameter R_Lifecycle.ThreadControl(): MIReturn */
static MI_CONST MI_ParameterDecl R_Lifecycle_ThreadControl_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(R_Lifecycle_ThreadControl, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST R_Lifecycle_ThreadControl_params[] =
{
    &R_Lifecycle_ThreadControl_MIReturn_param,
    &R_Lifecycle_ThreadControl_operation_param,
};

/* method R_Lifecycle.ThreadControl() */
MI_CONST MI_MethodDecl R_Lifecycle_ThreadControl_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746C0D, /* code */
    MI_T("ThreadControl"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    R_Lifecycle_ThreadControl_params, /* parameters */
    MI_COUNT(R_Lifecycle_ThreadControl_params), /* numParameters */
    sizeof(R_Lifecycle_ThreadControl), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)R_Lifecycle_Invoke_ThreadControl, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST R_Lifecycle_meths[] =
{
    &R_Lifecycle_GenericInstMethod_rtti,
    &R_Lifecycle_GenericMethod_rtti,
    &R_Lifecycle_ThreadControl_rtti,
};

static MI_CONST MI_ProviderFT R_Lifecycle_funcs =
{
  (MI_ProviderFT_Load)R_Lifecycle_Load,
  (MI_ProviderFT_Unload)R_Lifecycle_Unload,
  (MI_ProviderFT_GetInstance)R_Lifecycle_GetInstance,
  (MI_ProviderFT_EnumerateInstances)R_Lifecycle_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)R_Lifecycle_CreateInstance,
  (MI_ProviderFT_ModifyInstance)R_Lifecycle_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)R_Lifecycle_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class R_Lifecycle */
MI_CONST MI_ClassDecl R_Lifecycle_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0072650B, /* code */
    MI_T("R_Lifecycle"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    R_Lifecycle_props, /* properties */
    MI_COUNT(R_Lifecycle_props), /* numProperties */
    sizeof(R_Lifecycle), /* size */
    MI_T("Test_Class"), /* superClass */
    &Test_Class_rtti, /* superClassDecl */
    R_Lifecycle_meths, /* methods */
    MI_COUNT(R_Lifecycle_meths), /* numMethods */
    &schemaDecl, /* schema */
    &R_Lifecycle_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** L_LifecycleC1
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST L_LifecycleC1_props[] =
{
    &Test_Class_key_prop,
    &Test_Class_value_prop,
};

/* parameter L_LifecycleC1.GenericInstMethod(): MIReturn */
static MI_CONST MI_ParameterDecl L_LifecycleC1_GenericInstMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(L_LifecycleC1_GenericInstMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST L_LifecycleC1_GenericInstMethod_params[] =
{
    &L_LifecycleC1_GenericInstMethod_MIReturn_param,
};

/* method L_LifecycleC1.GenericInstMethod() */
MI_CONST MI_MethodDecl L_LifecycleC1_GenericInstMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00676411, /* code */
    MI_T("GenericInstMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    L_LifecycleC1_GenericInstMethod_params, /* parameters */
    MI_COUNT(L_LifecycleC1_GenericInstMethod_params), /* numParameters */
    sizeof(L_LifecycleC1_GenericInstMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)L_LifecycleC1_Invoke_GenericInstMethod, /* method */
};

/* parameter L_LifecycleC1.GenericMethod(): MIReturn */
static MI_CONST MI_ParameterDecl L_LifecycleC1_GenericMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(L_LifecycleC1_GenericMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST L_LifecycleC1_GenericMethod_params[] =
{
    &L_LifecycleC1_GenericMethod_MIReturn_param,
};

/* method L_LifecycleC1.GenericMethod() */
MI_CONST MI_MethodDecl L_LifecycleC1_GenericMethod_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0067640D, /* code */
    MI_T("GenericMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    L_LifecycleC1_GenericMethod_params, /* parameters */
    MI_COUNT(L_LifecycleC1_GenericMethod_params), /* numParameters */
    sizeof(L_LifecycleC1_GenericMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)L_LifecycleC1_Invoke_GenericMethod, /* method */
};

/* parameter L_LifecycleC1.ThreadControl(): operation */
static MI_CONST MI_ParameterDecl L_LifecycleC1_ThreadControl_operation_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006F6E09, /* code */
    MI_T("operation"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(L_LifecycleC1_ThreadControl, operation), /* offset */
};

/* parameter L_LifecycleC1.ThreadControl(): MIReturn */
static MI_CONST MI_ParameterDecl L_LifecycleC1_ThreadControl_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(L_LifecycleC1_ThreadControl, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST L_LifecycleC1_ThreadControl_params[] =
{
    &L_LifecycleC1_ThreadControl_MIReturn_param,
    &L_LifecycleC1_ThreadControl_operation_param,
};

/* method L_LifecycleC1.ThreadControl() */
MI_CONST MI_MethodDecl L_LifecycleC1_ThreadControl_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746C0D, /* code */
    MI_T("ThreadControl"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    L_LifecycleC1_ThreadControl_params, /* parameters */
    MI_COUNT(L_LifecycleC1_ThreadControl_params), /* numParameters */
    sizeof(L_LifecycleC1_ThreadControl), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)L_LifecycleC1_Invoke_ThreadControl, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST L_LifecycleC1_meths[] =
{
    &L_LifecycleC1_GenericInstMethod_rtti,
    &L_LifecycleC1_GenericMethod_rtti,
    &L_LifecycleC1_ThreadControl_rtti,
};

static MI_CONST MI_ProviderFT L_LifecycleC1_funcs =
{
  (MI_ProviderFT_Load)L_LifecycleC1_Load,
  (MI_ProviderFT_Unload)L_LifecycleC1_Unload,
  (MI_ProviderFT_GetInstance)L_LifecycleC1_GetInstance,
  (MI_ProviderFT_EnumerateInstances)L_LifecycleC1_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)L_LifecycleC1_CreateInstance,
  (MI_ProviderFT_ModifyInstance)L_LifecycleC1_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)L_LifecycleC1_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class L_LifecycleC1 */
MI_CONST MI_ClassDecl L_LifecycleC1_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006C310D, /* code */
    MI_T("L_LifecycleC1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    L_LifecycleC1_props, /* properties */
    MI_COUNT(L_LifecycleC1_props), /* numProperties */
    sizeof(L_LifecycleC1), /* size */
    MI_T("L_Lifecycle"), /* superClass */
    &L_Lifecycle_rtti, /* superClassDecl */
    L_LifecycleC1_meths, /* methods */
    MI_COUNT(L_LifecycleC1_meths), /* numMethods */
    &schemaDecl, /* schema */
    &L_LifecycleC1_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** L_LifecycleC2
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST L_LifecycleC2_props[] =
{
    &Test_Class_key_prop,
    &Test_Class_value_prop,
};

/* parameter L_LifecycleC2.GenericInstMethod(): MIReturn */
static MI_CONST MI_ParameterDecl L_LifecycleC2_GenericInstMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(L_LifecycleC2_GenericInstMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST L_LifecycleC2_GenericInstMethod_params[] =
{
    &L_LifecycleC2_GenericInstMethod_MIReturn_param,
};

/* method L_LifecycleC2.GenericInstMethod() */
MI_CONST MI_MethodDecl L_LifecycleC2_GenericInstMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00676411, /* code */
    MI_T("GenericInstMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    L_LifecycleC2_GenericInstMethod_params, /* parameters */
    MI_COUNT(L_LifecycleC2_GenericInstMethod_params), /* numParameters */
    sizeof(L_LifecycleC2_GenericInstMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)L_LifecycleC2_Invoke_GenericInstMethod, /* method */
};

/* parameter L_LifecycleC2.GenericMethod(): MIReturn */
static MI_CONST MI_ParameterDecl L_LifecycleC2_GenericMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(L_LifecycleC2_GenericMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST L_LifecycleC2_GenericMethod_params[] =
{
    &L_LifecycleC2_GenericMethod_MIReturn_param,
};

/* method L_LifecycleC2.GenericMethod() */
MI_CONST MI_MethodDecl L_LifecycleC2_GenericMethod_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0067640D, /* code */
    MI_T("GenericMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    L_LifecycleC2_GenericMethod_params, /* parameters */
    MI_COUNT(L_LifecycleC2_GenericMethod_params), /* numParameters */
    sizeof(L_LifecycleC2_GenericMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)L_LifecycleC2_Invoke_GenericMethod, /* method */
};

/* parameter L_LifecycleC2.ThreadControl(): operation */
static MI_CONST MI_ParameterDecl L_LifecycleC2_ThreadControl_operation_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006F6E09, /* code */
    MI_T("operation"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(L_LifecycleC2_ThreadControl, operation), /* offset */
};

/* parameter L_LifecycleC2.ThreadControl(): MIReturn */
static MI_CONST MI_ParameterDecl L_LifecycleC2_ThreadControl_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(L_LifecycleC2_ThreadControl, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST L_LifecycleC2_ThreadControl_params[] =
{
    &L_LifecycleC2_ThreadControl_MIReturn_param,
    &L_LifecycleC2_ThreadControl_operation_param,
};

/* method L_LifecycleC2.ThreadControl() */
MI_CONST MI_MethodDecl L_LifecycleC2_ThreadControl_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746C0D, /* code */
    MI_T("ThreadControl"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    L_LifecycleC2_ThreadControl_params, /* parameters */
    MI_COUNT(L_LifecycleC2_ThreadControl_params), /* numParameters */
    sizeof(L_LifecycleC2_ThreadControl), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)L_LifecycleC2_Invoke_ThreadControl, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST L_LifecycleC2_meths[] =
{
    &L_LifecycleC2_GenericInstMethod_rtti,
    &L_LifecycleC2_GenericMethod_rtti,
    &L_LifecycleC2_ThreadControl_rtti,
};

static MI_CONST MI_ProviderFT L_LifecycleC2_funcs =
{
  (MI_ProviderFT_Load)L_LifecycleC2_Load,
  (MI_ProviderFT_Unload)L_LifecycleC2_Unload,
  (MI_ProviderFT_GetInstance)L_LifecycleC2_GetInstance,
  (MI_ProviderFT_EnumerateInstances)L_LifecycleC2_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)L_LifecycleC2_CreateInstance,
  (MI_ProviderFT_ModifyInstance)L_LifecycleC2_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)L_LifecycleC2_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class L_LifecycleC2 */
MI_CONST MI_ClassDecl L_LifecycleC2_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006C320D, /* code */
    MI_T("L_LifecycleC2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    L_LifecycleC2_props, /* properties */
    MI_COUNT(L_LifecycleC2_props), /* numProperties */
    sizeof(L_LifecycleC2), /* size */
    MI_T("L_LifecycleC1"), /* superClass */
    &L_LifecycleC1_rtti, /* superClassDecl */
    L_LifecycleC2_meths, /* methods */
    MI_COUNT(L_LifecycleC2_meths), /* numMethods */
    &schemaDecl, /* schema */
    &L_LifecycleC2_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** R_LifecycleC1
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST R_LifecycleC1_props[] =
{
    &Test_Class_key_prop,
    &Test_Class_value_prop,
};

/* parameter R_LifecycleC1.GenericInstMethod(): MIReturn */
static MI_CONST MI_ParameterDecl R_LifecycleC1_GenericInstMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(R_LifecycleC1_GenericInstMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST R_LifecycleC1_GenericInstMethod_params[] =
{
    &R_LifecycleC1_GenericInstMethod_MIReturn_param,
};

/* method R_LifecycleC1.GenericInstMethod() */
MI_CONST MI_MethodDecl R_LifecycleC1_GenericInstMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00676411, /* code */
    MI_T("GenericInstMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    R_LifecycleC1_GenericInstMethod_params, /* parameters */
    MI_COUNT(R_LifecycleC1_GenericInstMethod_params), /* numParameters */
    sizeof(R_LifecycleC1_GenericInstMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)R_LifecycleC1_Invoke_GenericInstMethod, /* method */
};

/* parameter R_LifecycleC1.GenericMethod(): MIReturn */
static MI_CONST MI_ParameterDecl R_LifecycleC1_GenericMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(R_LifecycleC1_GenericMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST R_LifecycleC1_GenericMethod_params[] =
{
    &R_LifecycleC1_GenericMethod_MIReturn_param,
};

/* method R_LifecycleC1.GenericMethod() */
MI_CONST MI_MethodDecl R_LifecycleC1_GenericMethod_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0067640D, /* code */
    MI_T("GenericMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    R_LifecycleC1_GenericMethod_params, /* parameters */
    MI_COUNT(R_LifecycleC1_GenericMethod_params), /* numParameters */
    sizeof(R_LifecycleC1_GenericMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)R_LifecycleC1_Invoke_GenericMethod, /* method */
};

/* parameter R_LifecycleC1.ThreadControl(): operation */
static MI_CONST MI_ParameterDecl R_LifecycleC1_ThreadControl_operation_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006F6E09, /* code */
    MI_T("operation"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(R_LifecycleC1_ThreadControl, operation), /* offset */
};

/* parameter R_LifecycleC1.ThreadControl(): MIReturn */
static MI_CONST MI_ParameterDecl R_LifecycleC1_ThreadControl_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(R_LifecycleC1_ThreadControl, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST R_LifecycleC1_ThreadControl_params[] =
{
    &R_LifecycleC1_ThreadControl_MIReturn_param,
    &R_LifecycleC1_ThreadControl_operation_param,
};

/* method R_LifecycleC1.ThreadControl() */
MI_CONST MI_MethodDecl R_LifecycleC1_ThreadControl_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746C0D, /* code */
    MI_T("ThreadControl"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    R_LifecycleC1_ThreadControl_params, /* parameters */
    MI_COUNT(R_LifecycleC1_ThreadControl_params), /* numParameters */
    sizeof(R_LifecycleC1_ThreadControl), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)R_LifecycleC1_Invoke_ThreadControl, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST R_LifecycleC1_meths[] =
{
    &R_LifecycleC1_GenericInstMethod_rtti,
    &R_LifecycleC1_GenericMethod_rtti,
    &R_LifecycleC1_ThreadControl_rtti,
};

static MI_CONST MI_ProviderFT R_LifecycleC1_funcs =
{
  (MI_ProviderFT_Load)R_LifecycleC1_Load,
  (MI_ProviderFT_Unload)R_LifecycleC1_Unload,
  (MI_ProviderFT_GetInstance)R_LifecycleC1_GetInstance,
  (MI_ProviderFT_EnumerateInstances)R_LifecycleC1_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)R_LifecycleC1_CreateInstance,
  (MI_ProviderFT_ModifyInstance)R_LifecycleC1_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)R_LifecycleC1_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class R_LifecycleC1 */
MI_CONST MI_ClassDecl R_LifecycleC1_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0072310D, /* code */
    MI_T("R_LifecycleC1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    R_LifecycleC1_props, /* properties */
    MI_COUNT(R_LifecycleC1_props), /* numProperties */
    sizeof(R_LifecycleC1), /* size */
    MI_T("R_Lifecycle"), /* superClass */
    &R_Lifecycle_rtti, /* superClassDecl */
    R_LifecycleC1_meths, /* methods */
    MI_COUNT(R_LifecycleC1_meths), /* numMethods */
    &schemaDecl, /* schema */
    &R_LifecycleC1_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** R_LifecycleC2
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST R_LifecycleC2_props[] =
{
    &Test_Class_key_prop,
    &Test_Class_value_prop,
};

/* parameter R_LifecycleC2.GenericInstMethod(): MIReturn */
static MI_CONST MI_ParameterDecl R_LifecycleC2_GenericInstMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(R_LifecycleC2_GenericInstMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST R_LifecycleC2_GenericInstMethod_params[] =
{
    &R_LifecycleC2_GenericInstMethod_MIReturn_param,
};

/* method R_LifecycleC2.GenericInstMethod() */
MI_CONST MI_MethodDecl R_LifecycleC2_GenericInstMethod_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00676411, /* code */
    MI_T("GenericInstMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    R_LifecycleC2_GenericInstMethod_params, /* parameters */
    MI_COUNT(R_LifecycleC2_GenericInstMethod_params), /* numParameters */
    sizeof(R_LifecycleC2_GenericInstMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)R_LifecycleC2_Invoke_GenericInstMethod, /* method */
};

/* parameter R_LifecycleC2.GenericMethod(): MIReturn */
static MI_CONST MI_ParameterDecl R_LifecycleC2_GenericMethod_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(R_LifecycleC2_GenericMethod, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST R_LifecycleC2_GenericMethod_params[] =
{
    &R_LifecycleC2_GenericMethod_MIReturn_param,
};

/* method R_LifecycleC2.GenericMethod() */
MI_CONST MI_MethodDecl R_LifecycleC2_GenericMethod_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0067640D, /* code */
    MI_T("GenericMethod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    R_LifecycleC2_GenericMethod_params, /* parameters */
    MI_COUNT(R_LifecycleC2_GenericMethod_params), /* numParameters */
    sizeof(R_LifecycleC2_GenericMethod), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)R_LifecycleC2_Invoke_GenericMethod, /* method */
};

/* parameter R_LifecycleC2.ThreadControl(): operation */
static MI_CONST MI_ParameterDecl R_LifecycleC2_ThreadControl_operation_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006F6E09, /* code */
    MI_T("operation"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(R_LifecycleC2_ThreadControl, operation), /* offset */
};

/* parameter R_LifecycleC2.ThreadControl(): MIReturn */
static MI_CONST MI_ParameterDecl R_LifecycleC2_ThreadControl_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(R_LifecycleC2_ThreadControl, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST R_LifecycleC2_ThreadControl_params[] =
{
    &R_LifecycleC2_ThreadControl_MIReturn_param,
    &R_LifecycleC2_ThreadControl_operation_param,
};

/* method R_LifecycleC2.ThreadControl() */
MI_CONST MI_MethodDecl R_LifecycleC2_ThreadControl_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746C0D, /* code */
    MI_T("ThreadControl"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    R_LifecycleC2_ThreadControl_params, /* parameters */
    MI_COUNT(R_LifecycleC2_ThreadControl_params), /* numParameters */
    sizeof(R_LifecycleC2_ThreadControl), /* size */
    MI_UINT32, /* returnType */
    MI_T("Test_Class"), /* origin */
    MI_T("Test_Class"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)R_LifecycleC2_Invoke_ThreadControl, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST R_LifecycleC2_meths[] =
{
    &R_LifecycleC2_GenericInstMethod_rtti,
    &R_LifecycleC2_GenericMethod_rtti,
    &R_LifecycleC2_ThreadControl_rtti,
};

static MI_CONST MI_ProviderFT R_LifecycleC2_funcs =
{
  (MI_ProviderFT_Load)R_LifecycleC2_Load,
  (MI_ProviderFT_Unload)R_LifecycleC2_Unload,
  (MI_ProviderFT_GetInstance)R_LifecycleC2_GetInstance,
  (MI_ProviderFT_EnumerateInstances)R_LifecycleC2_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)R_LifecycleC2_CreateInstance,
  (MI_ProviderFT_ModifyInstance)R_LifecycleC2_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)R_LifecycleC2_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class R_LifecycleC2 */
MI_CONST MI_ClassDecl R_LifecycleC2_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0072320D, /* code */
    MI_T("R_LifecycleC2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    R_LifecycleC2_props, /* properties */
    MI_COUNT(R_LifecycleC2_props), /* numProperties */
    sizeof(R_LifecycleC2), /* size */
    MI_T("R_LifecycleC1"), /* superClass */
    &R_LifecycleC1_rtti, /* superClassDecl */
    R_LifecycleC2_meths, /* methods */
    MI_COUNT(R_LifecycleC2_meths), /* numMethods */
    &schemaDecl, /* schema */
    &R_LifecycleC2_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** Test_Indication
**
**==============================================================================
*/

/* property Test_Indication.id */
static MI_CONST MI_PropertyDecl Test_Indication_id_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00696402, /* code */
    MI_T("id"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, id), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.message */
static MI_CONST MI_PropertyDecl Test_Indication_message_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D6507, /* code */
    MI_T("message"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, message), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.sbool */
static MI_CONST MI_PropertyDecl Test_Indication_sbool_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736C05, /* code */
    MI_T("sbool"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, sbool), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.suint8 */
static MI_CONST MI_PropertyDecl Test_Indication_suint8_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733806, /* code */
    MI_T("suint8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, suint8), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.ssint8 */
static MI_CONST MI_PropertyDecl Test_Indication_ssint8_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733806, /* code */
    MI_T("ssint8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, ssint8), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.sUINT16 */
static MI_CONST MI_PropertyDecl Test_Indication_sUINT16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733607, /* code */
    MI_T("sUINT16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, sUINT16), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.ssint16 */
static MI_CONST MI_PropertyDecl Test_Indication_ssint16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733607, /* code */
    MI_T("ssint16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, ssint16), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.suint32 */
static MI_CONST MI_PropertyDecl Test_Indication_suint32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733207, /* code */
    MI_T("suint32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, suint32), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.ssint32 */
static MI_CONST MI_PropertyDecl Test_Indication_ssint32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733207, /* code */
    MI_T("ssint32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, ssint32), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.suint64 */
static MI_CONST MI_PropertyDecl Test_Indication_suint64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733407, /* code */
    MI_T("suint64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, suint64), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.ssint64 */
static MI_CONST MI_PropertyDecl Test_Indication_ssint64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733407, /* code */
    MI_T("ssint64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, ssint64), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.srEal32 */
static MI_CONST MI_PropertyDecl Test_Indication_srEal32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733207, /* code */
    MI_T("srEal32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, srEal32), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.sREAL64 */
static MI_CONST MI_PropertyDecl Test_Indication_sREAL64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733407, /* code */
    MI_T("sREAL64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, sREAL64), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.schar16 */
static MI_CONST MI_PropertyDecl Test_Indication_schar16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733607, /* code */
    MI_T("schar16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, schar16), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.sstring */
static MI_CONST MI_PropertyDecl Test_Indication_sstring_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736707, /* code */
    MI_T("sstring"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, sstring), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.sDATETIME */
static MI_CONST MI_PropertyDecl Test_Indication_sDATETIME_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736509, /* code */
    MI_T("sDATETIME"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, sDATETIME), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.a_bool */
static MI_CONST MI_PropertyDecl Test_Indication_a_bool_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00616C06, /* code */
    MI_T("a_bool"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, a_bool), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.a_uint8 */
static MI_CONST MI_PropertyDecl Test_Indication_a_uint8_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613807, /* code */
    MI_T("a_uint8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, a_uint8), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.a_sint8 */
static MI_CONST MI_PropertyDecl Test_Indication_a_sint8_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613807, /* code */
    MI_T("a_sint8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, a_sint8), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.a_UINT16 */
static MI_CONST MI_PropertyDecl Test_Indication_a_UINT16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613608, /* code */
    MI_T("a_UINT16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, a_UINT16), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.a_sint16 */
static MI_CONST MI_PropertyDecl Test_Indication_a_sint16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613608, /* code */
    MI_T("a_sint16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, a_sint16), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.a_uint32 */
static MI_CONST MI_PropertyDecl Test_Indication_a_uint32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613208, /* code */
    MI_T("a_uint32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, a_uint32), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.a_sint32 */
static MI_CONST MI_PropertyDecl Test_Indication_a_sint32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613208, /* code */
    MI_T("a_sint32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, a_sint32), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.a_uint64 */
static MI_CONST MI_PropertyDecl Test_Indication_a_uint64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613408, /* code */
    MI_T("a_uint64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, a_uint64), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.a_sint64 */
static MI_CONST MI_PropertyDecl Test_Indication_a_sint64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613408, /* code */
    MI_T("a_sint64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, a_sint64), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.a_rEal32 */
static MI_CONST MI_PropertyDecl Test_Indication_a_rEal32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613208, /* code */
    MI_T("a_rEal32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, a_rEal32), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.a_REAL64 */
static MI_CONST MI_PropertyDecl Test_Indication_a_REAL64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613408, /* code */
    MI_T("a_REAL64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, a_REAL64), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.a_char16 */
static MI_CONST MI_PropertyDecl Test_Indication_a_char16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613608, /* code */
    MI_T("a_char16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, a_char16), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.a_string */
static MI_CONST MI_PropertyDecl Test_Indication_a_string_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00616708, /* code */
    MI_T("a_string"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, a_string), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.a_DATETIME */
static MI_CONST MI_PropertyDecl Test_Indication_a_DATETIME_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0061650A, /* code */
    MI_T("a_DATETIME"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, a_DATETIME), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.a_octetBytes */
static MI_CONST MI_PropertyDecl Test_Indication_a_octetBytes_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0061730C, /* code */
    MI_T("a_octetBytes"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, a_octetBytes), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.a_octetStrings */
static MI_CONST MI_PropertyDecl Test_Indication_a_octetStrings_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0061730E, /* code */
    MI_T("a_octetStrings"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, a_octetStrings), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* Test_Indication_embeddedinstance_EmbeddedInstance_qual_value = MI_T("Test_Class");

static MI_CONST MI_Qualifier Test_Indication_embeddedinstance_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &Test_Indication_embeddedinstance_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Test_Indication_embeddedinstance_quals[] =
{
    &Test_Indication_embeddedinstance_EmbeddedInstance_qual,
};

/* property Test_Indication.embeddedinstance */
static MI_CONST MI_PropertyDecl Test_Indication_embeddedinstance_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656510, /* code */
    MI_T("embeddedinstance"), /* name */
    Test_Indication_embeddedinstance_quals, /* qualifiers */
    MI_COUNT(Test_Indication_embeddedinstance_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("Test_Class"), /* className */
    0, /* subscript */
    offsetof(Test_Indication, embeddedinstance), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* Test_Indication_embeddedinstancearray_EmbeddedInstance_qual_value = MI_T("Test_Class");

static MI_CONST MI_Qualifier Test_Indication_embeddedinstancearray_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &Test_Indication_embeddedinstancearray_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Test_Indication_embeddedinstancearray_quals[] =
{
    &Test_Indication_embeddedinstancearray_EmbeddedInstance_qual,
};

/* property Test_Indication.embeddedinstancearray */
static MI_CONST MI_PropertyDecl Test_Indication_embeddedinstancearray_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00657915, /* code */
    MI_T("embeddedinstancearray"), /* name */
    Test_Indication_embeddedinstancearray_quals, /* qualifiers */
    MI_COUNT(Test_Indication_embeddedinstancearray_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("Test_Class"), /* className */
    0, /* subscript */
    offsetof(Test_Indication, embeddedinstancearray), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.embeddedobject */
static MI_CONST MI_PropertyDecl Test_Indication_embeddedobject_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065740E, /* code */
    MI_T("embeddedobject"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, embeddedobject), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

/* property Test_Indication.embeddedobjectarray */
static MI_CONST MI_PropertyDecl Test_Indication_embeddedobjectarray_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00657913, /* code */
    MI_T("embeddedobjectarray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_Indication, embeddedobjectarray), /* offset */
    MI_T("Test_Indication"), /* origin */
    MI_T("Test_Indication"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Test_Indication_props[] =
{
    &Test_Indication_id_prop,
    &Test_Indication_message_prop,
    &Test_Indication_sbool_prop,
    &Test_Indication_suint8_prop,
    &Test_Indication_ssint8_prop,
    &Test_Indication_sUINT16_prop,
    &Test_Indication_ssint16_prop,
    &Test_Indication_suint32_prop,
    &Test_Indication_ssint32_prop,
    &Test_Indication_suint64_prop,
    &Test_Indication_ssint64_prop,
    &Test_Indication_srEal32_prop,
    &Test_Indication_sREAL64_prop,
    &Test_Indication_schar16_prop,
    &Test_Indication_sstring_prop,
    &Test_Indication_sDATETIME_prop,
    &Test_Indication_a_bool_prop,
    &Test_Indication_a_uint8_prop,
    &Test_Indication_a_sint8_prop,
    &Test_Indication_a_UINT16_prop,
    &Test_Indication_a_sint16_prop,
    &Test_Indication_a_uint32_prop,
    &Test_Indication_a_sint32_prop,
    &Test_Indication_a_uint64_prop,
    &Test_Indication_a_sint64_prop,
    &Test_Indication_a_rEal32_prop,
    &Test_Indication_a_REAL64_prop,
    &Test_Indication_a_char16_prop,
    &Test_Indication_a_string_prop,
    &Test_Indication_a_DATETIME_prop,
    &Test_Indication_a_octetBytes_prop,
    &Test_Indication_a_octetStrings_prop,
    &Test_Indication_embeddedinstance_prop,
    &Test_Indication_embeddedinstancearray_prop,
    &Test_Indication_embeddedobject_prop,
    &Test_Indication_embeddedobjectarray_prop,
};

static MI_CONST MI_ProviderFT Test_Indication_funcs =
{
  (MI_ProviderFT_Load)Test_Indication_Load,
  (MI_ProviderFT_Unload)Test_Indication_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)NULL,
  (MI_ProviderFT_CreateInstance)NULL,
  (MI_ProviderFT_ModifyInstance)NULL,
  (MI_ProviderFT_DeleteInstance)NULL,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)Test_Indication_EnableIndications,
  (MI_ProviderFT_DisableIndications)Test_Indication_DisableIndications,
  (MI_ProviderFT_Subscribe)Test_Indication_Subscribe,
  (MI_ProviderFT_Unsubscribe)Test_Indication_Unsubscribe,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Test_Indication */
MI_CONST MI_ClassDecl Test_Indication_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x00746E0F, /* code */
    MI_T("Test_Indication"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Test_Indication_props, /* properties */
    MI_COUNT(Test_Indication_props), /* numProperties */
    sizeof(Test_Indication), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Test_Indication_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_Indication
**
**==============================================================================
*/

/* property CIM_Indication.IndicationIdentifier */
static MI_CONST MI_PropertyDecl CIM_Indication_IndicationIdentifier_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00697214, /* code */
    MI_T("IndicationIdentifier"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, IndicationIdentifier), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.CorrelatedIndications */
static MI_CONST MI_PropertyDecl CIM_Indication_CorrelatedIndications_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637315, /* code */
    MI_T("CorrelatedIndications"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, CorrelatedIndications), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.IndicationTime */
static MI_CONST MI_PropertyDecl CIM_Indication_IndicationTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069650E, /* code */
    MI_T("IndicationTime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, IndicationTime), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.PerceivedSeverity */
static MI_CONST MI_PropertyDecl CIM_Indication_PerceivedSeverity_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00707911, /* code */
    MI_T("PerceivedSeverity"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, PerceivedSeverity), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.OtherSeverity */
static MI_CONST MI_PropertyDecl CIM_Indication_OtherSeverity_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F790D, /* code */
    MI_T("OtherSeverity"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, OtherSeverity), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.IndicationFilterName */
static MI_CONST MI_PropertyDecl CIM_Indication_IndicationFilterName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00696514, /* code */
    MI_T("IndicationFilterName"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, IndicationFilterName), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.SequenceContext */
static MI_CONST MI_PropertyDecl CIM_Indication_SequenceContext_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073740F, /* code */
    MI_T("SequenceContext"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, SequenceContext), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.SequenceNumber */
static MI_CONST MI_PropertyDecl CIM_Indication_SequenceNumber_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073720E, /* code */
    MI_T("SequenceNumber"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, SequenceNumber), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Indication_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
};

static MI_CONST MI_Char* CIM_Indication_Version_qual_value = MI_T("2.24.0");

static MI_CONST MI_Qualifier CIM_Indication_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Indication_Version_qual_value
};

static MI_CONST MI_Char* CIM_Indication_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier CIM_Indication_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Indication_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Indication_quals[] =
{
    &CIM_Indication_Version_qual,
    &CIM_Indication_UMLPackagePath_qual,
};

/* class CIM_Indication */
MI_CONST MI_ClassDecl CIM_Indication_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_ABSTRACT, /* flags */
    0x00636E0E, /* code */
    MI_T("CIM_Indication"), /* name */
    CIM_Indication_quals, /* qualifiers */
    MI_COUNT(CIM_Indication_quals), /* numQualifiers */
    CIM_Indication_props, /* properties */
    MI_COUNT(CIM_Indication_props), /* numProperties */
    sizeof(CIM_Indication), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** L_Indication
**
**==============================================================================
*/

/* property L_Indication.id */
static MI_CONST MI_PropertyDecl L_Indication_id_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00696402, /* code */
    MI_T("id"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(L_Indication, id), /* offset */
    MI_T("L_Indication"), /* origin */
    MI_T("L_Indication"), /* propagator */
    NULL,
};

/* property L_Indication.message */
static MI_CONST MI_PropertyDecl L_Indication_message_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D6507, /* code */
    MI_T("message"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(L_Indication, message), /* offset */
    MI_T("L_Indication"), /* origin */
    MI_T("L_Indication"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST L_Indication_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
    &L_Indication_id_prop,
    &L_Indication_message_prop,
};

static MI_CONST MI_Char* L_Indication_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier L_Indication_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &L_Indication_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST L_Indication_quals[] =
{
    &L_Indication_UMLPackagePath_qual,
};

/* class L_Indication */
MI_CONST MI_ClassDecl L_Indication_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_ABSTRACT, /* flags */
    0x006C6E0C, /* code */
    MI_T("L_Indication"), /* name */
    L_Indication_quals, /* qualifiers */
    MI_COUNT(L_Indication_quals), /* numQualifiers */
    L_Indication_props, /* properties */
    MI_COUNT(L_Indication_props), /* numProperties */
    sizeof(L_Indication), /* size */
    MI_T("CIM_Indication"), /* superClass */
    &CIM_Indication_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** L_IndicationC1
**
**==============================================================================
*/

/* property L_IndicationC1.lcode1 */
static MI_CONST MI_PropertyDecl L_IndicationC1_lcode1_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C3106, /* code */
    MI_T("lcode1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(L_IndicationC1, lcode1), /* offset */
    MI_T("L_IndicationC1"), /* origin */
    MI_T("L_IndicationC1"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST L_IndicationC1_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
    &L_Indication_id_prop,
    &L_Indication_message_prop,
    &L_IndicationC1_lcode1_prop,
};

static MI_CONST MI_ProviderFT L_IndicationC1_funcs =
{
  (MI_ProviderFT_Load)L_IndicationC1_Load,
  (MI_ProviderFT_Unload)L_IndicationC1_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)NULL,
  (MI_ProviderFT_CreateInstance)NULL,
  (MI_ProviderFT_ModifyInstance)NULL,
  (MI_ProviderFT_DeleteInstance)NULL,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)L_IndicationC1_EnableIndications,
  (MI_ProviderFT_DisableIndications)L_IndicationC1_DisableIndications,
  (MI_ProviderFT_Subscribe)L_IndicationC1_Subscribe,
  (MI_ProviderFT_Unsubscribe)L_IndicationC1_Unsubscribe,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* L_IndicationC1_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier L_IndicationC1_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &L_IndicationC1_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST L_IndicationC1_quals[] =
{
    &L_IndicationC1_UMLPackagePath_qual,
};

/* class L_IndicationC1 */
MI_CONST MI_ClassDecl L_IndicationC1_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x006C310E, /* code */
    MI_T("L_IndicationC1"), /* name */
    L_IndicationC1_quals, /* qualifiers */
    MI_COUNT(L_IndicationC1_quals), /* numQualifiers */
    L_IndicationC1_props, /* properties */
    MI_COUNT(L_IndicationC1_props), /* numProperties */
    sizeof(L_IndicationC1), /* size */
    MI_T("L_Indication"), /* superClass */
    &L_Indication_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &L_IndicationC1_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** L_IndicationC2
**
**==============================================================================
*/

/* property L_IndicationC2.lcode2 */
static MI_CONST MI_PropertyDecl L_IndicationC2_lcode2_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C3206, /* code */
    MI_T("lcode2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(L_IndicationC2, lcode2), /* offset */
    MI_T("L_IndicationC2"), /* origin */
    MI_T("L_IndicationC2"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST L_IndicationC2_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
    &L_Indication_id_prop,
    &L_Indication_message_prop,
    &L_IndicationC1_lcode1_prop,
    &L_IndicationC2_lcode2_prop,
};

static MI_CONST MI_ProviderFT L_IndicationC2_funcs =
{
  (MI_ProviderFT_Load)L_IndicationC2_Load,
  (MI_ProviderFT_Unload)L_IndicationC2_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)NULL,
  (MI_ProviderFT_CreateInstance)NULL,
  (MI_ProviderFT_ModifyInstance)NULL,
  (MI_ProviderFT_DeleteInstance)NULL,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)L_IndicationC2_EnableIndications,
  (MI_ProviderFT_DisableIndications)L_IndicationC2_DisableIndications,
  (MI_ProviderFT_Subscribe)L_IndicationC2_Subscribe,
  (MI_ProviderFT_Unsubscribe)L_IndicationC2_Unsubscribe,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* L_IndicationC2_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier L_IndicationC2_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &L_IndicationC2_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST L_IndicationC2_quals[] =
{
    &L_IndicationC2_UMLPackagePath_qual,
};

/* class L_IndicationC2 */
MI_CONST MI_ClassDecl L_IndicationC2_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x006C320E, /* code */
    MI_T("L_IndicationC2"), /* name */
    L_IndicationC2_quals, /* qualifiers */
    MI_COUNT(L_IndicationC2_quals), /* numQualifiers */
    L_IndicationC2_props, /* properties */
    MI_COUNT(L_IndicationC2_props), /* numProperties */
    sizeof(L_IndicationC2), /* size */
    MI_T("L_IndicationC1"), /* superClass */
    &L_IndicationC1_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &L_IndicationC2_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** L_IndicationC3
**
**==============================================================================
*/

/* property L_IndicationC3.lcode3 */
static MI_CONST MI_PropertyDecl L_IndicationC3_lcode3_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C3306, /* code */
    MI_T("lcode3"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(L_IndicationC3, lcode3), /* offset */
    MI_T("L_IndicationC3"), /* origin */
    MI_T("L_IndicationC3"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST L_IndicationC3_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
    &L_Indication_id_prop,
    &L_Indication_message_prop,
    &L_IndicationC1_lcode1_prop,
    &L_IndicationC2_lcode2_prop,
    &L_IndicationC3_lcode3_prop,
};

static MI_CONST MI_ProviderFT L_IndicationC3_funcs =
{
  (MI_ProviderFT_Load)L_IndicationC3_Load,
  (MI_ProviderFT_Unload)L_IndicationC3_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)NULL,
  (MI_ProviderFT_CreateInstance)NULL,
  (MI_ProviderFT_ModifyInstance)NULL,
  (MI_ProviderFT_DeleteInstance)NULL,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)L_IndicationC3_EnableIndications,
  (MI_ProviderFT_DisableIndications)L_IndicationC3_DisableIndications,
  (MI_ProviderFT_Subscribe)L_IndicationC3_Subscribe,
  (MI_ProviderFT_Unsubscribe)L_IndicationC3_Unsubscribe,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* L_IndicationC3_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier L_IndicationC3_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &L_IndicationC3_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST L_IndicationC3_quals[] =
{
    &L_IndicationC3_UMLPackagePath_qual,
};

/* class L_IndicationC3 */
MI_CONST MI_ClassDecl L_IndicationC3_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x006C330E, /* code */
    MI_T("L_IndicationC3"), /* name */
    L_IndicationC3_quals, /* qualifiers */
    MI_COUNT(L_IndicationC3_quals), /* numQualifiers */
    L_IndicationC3_props, /* properties */
    MI_COUNT(L_IndicationC3_props), /* numProperties */
    sizeof(L_IndicationC3), /* size */
    MI_T("L_IndicationC2"), /* superClass */
    &L_IndicationC2_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &L_IndicationC3_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** R_Indication
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST R_Indication_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
    &L_Indication_id_prop,
    &L_Indication_message_prop,
};

static MI_CONST MI_Char* R_Indication_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier R_Indication_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &R_Indication_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST R_Indication_quals[] =
{
    &R_Indication_UMLPackagePath_qual,
};

/* class R_Indication */
MI_CONST MI_ClassDecl R_Indication_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_ABSTRACT, /* flags */
    0x00726E0C, /* code */
    MI_T("R_Indication"), /* name */
    R_Indication_quals, /* qualifiers */
    MI_COUNT(R_Indication_quals), /* numQualifiers */
    R_Indication_props, /* properties */
    MI_COUNT(R_Indication_props), /* numProperties */
    sizeof(R_Indication), /* size */
    MI_T("L_Indication"), /* superClass */
    &L_Indication_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** R_IndicationC1
**
**==============================================================================
*/

/* property R_IndicationC1.rcode1 */
static MI_CONST MI_PropertyDecl R_IndicationC1_rcode1_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00723106, /* code */
    MI_T("rcode1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(R_IndicationC1, rcode1), /* offset */
    MI_T("R_IndicationC1"), /* origin */
    MI_T("R_IndicationC1"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST R_IndicationC1_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
    &L_Indication_id_prop,
    &L_Indication_message_prop,
    &R_IndicationC1_rcode1_prop,
};

static MI_CONST MI_ProviderFT R_IndicationC1_funcs =
{
  (MI_ProviderFT_Load)R_IndicationC1_Load,
  (MI_ProviderFT_Unload)R_IndicationC1_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)NULL,
  (MI_ProviderFT_CreateInstance)NULL,
  (MI_ProviderFT_ModifyInstance)NULL,
  (MI_ProviderFT_DeleteInstance)NULL,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)R_IndicationC1_EnableIndications,
  (MI_ProviderFT_DisableIndications)R_IndicationC1_DisableIndications,
  (MI_ProviderFT_Subscribe)R_IndicationC1_Subscribe,
  (MI_ProviderFT_Unsubscribe)R_IndicationC1_Unsubscribe,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* R_IndicationC1_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier R_IndicationC1_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &R_IndicationC1_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST R_IndicationC1_quals[] =
{
    &R_IndicationC1_UMLPackagePath_qual,
};

/* class R_IndicationC1 */
MI_CONST MI_ClassDecl R_IndicationC1_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x0072310E, /* code */
    MI_T("R_IndicationC1"), /* name */
    R_IndicationC1_quals, /* qualifiers */
    MI_COUNT(R_IndicationC1_quals), /* numQualifiers */
    R_IndicationC1_props, /* properties */
    MI_COUNT(R_IndicationC1_props), /* numProperties */
    sizeof(R_IndicationC1), /* size */
    MI_T("R_Indication"), /* superClass */
    &R_Indication_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &R_IndicationC1_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** R_IndicationC2
**
**==============================================================================
*/

/* property R_IndicationC2.rcode2 */
static MI_CONST MI_PropertyDecl R_IndicationC2_rcode2_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00723206, /* code */
    MI_T("rcode2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(R_IndicationC2, rcode2), /* offset */
    MI_T("R_IndicationC2"), /* origin */
    MI_T("R_IndicationC2"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST R_IndicationC2_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
    &L_Indication_id_prop,
    &L_Indication_message_prop,
    &R_IndicationC1_rcode1_prop,
    &R_IndicationC2_rcode2_prop,
};

static MI_CONST MI_ProviderFT R_IndicationC2_funcs =
{
  (MI_ProviderFT_Load)R_IndicationC2_Load,
  (MI_ProviderFT_Unload)R_IndicationC2_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)NULL,
  (MI_ProviderFT_CreateInstance)NULL,
  (MI_ProviderFT_ModifyInstance)NULL,
  (MI_ProviderFT_DeleteInstance)NULL,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)R_IndicationC2_EnableIndications,
  (MI_ProviderFT_DisableIndications)R_IndicationC2_DisableIndications,
  (MI_ProviderFT_Subscribe)R_IndicationC2_Subscribe,
  (MI_ProviderFT_Unsubscribe)R_IndicationC2_Unsubscribe,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* R_IndicationC2_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier R_IndicationC2_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &R_IndicationC2_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST R_IndicationC2_quals[] =
{
    &R_IndicationC2_UMLPackagePath_qual,
};

/* class R_IndicationC2 */
MI_CONST MI_ClassDecl R_IndicationC2_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x0072320E, /* code */
    MI_T("R_IndicationC2"), /* name */
    R_IndicationC2_quals, /* qualifiers */
    MI_COUNT(R_IndicationC2_quals), /* numQualifiers */
    R_IndicationC2_props, /* properties */
    MI_COUNT(R_IndicationC2_props), /* numProperties */
    sizeof(R_IndicationC2), /* size */
    MI_T("R_IndicationC1"), /* superClass */
    &R_IndicationC1_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &R_IndicationC2_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** R_IndicationC3
**
**==============================================================================
*/

/* property R_IndicationC3.rcode3 */
static MI_CONST MI_PropertyDecl R_IndicationC3_rcode3_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00723306, /* code */
    MI_T("rcode3"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(R_IndicationC3, rcode3), /* offset */
    MI_T("R_IndicationC3"), /* origin */
    MI_T("R_IndicationC3"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST R_IndicationC3_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
    &L_Indication_id_prop,
    &L_Indication_message_prop,
    &R_IndicationC1_rcode1_prop,
    &R_IndicationC2_rcode2_prop,
    &R_IndicationC3_rcode3_prop,
};

static MI_CONST MI_ProviderFT R_IndicationC3_funcs =
{
  (MI_ProviderFT_Load)R_IndicationC3_Load,
  (MI_ProviderFT_Unload)R_IndicationC3_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)NULL,
  (MI_ProviderFT_CreateInstance)NULL,
  (MI_ProviderFT_ModifyInstance)NULL,
  (MI_ProviderFT_DeleteInstance)NULL,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)R_IndicationC3_EnableIndications,
  (MI_ProviderFT_DisableIndications)R_IndicationC3_DisableIndications,
  (MI_ProviderFT_Subscribe)R_IndicationC3_Subscribe,
  (MI_ProviderFT_Unsubscribe)R_IndicationC3_Unsubscribe,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* R_IndicationC3_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier R_IndicationC3_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &R_IndicationC3_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST R_IndicationC3_quals[] =
{
    &R_IndicationC3_UMLPackagePath_qual,
};

/* class R_IndicationC3 */
MI_CONST MI_ClassDecl R_IndicationC3_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x0072330E, /* code */
    MI_T("R_IndicationC3"), /* name */
    R_IndicationC3_quals, /* qualifiers */
    MI_COUNT(R_IndicationC3_quals), /* numQualifiers */
    R_IndicationC3_props, /* properties */
    MI_COUNT(R_IndicationC3_props), /* numProperties */
    sizeof(R_IndicationC3), /* size */
    MI_T("R_IndicationC2"), /* superClass */
    &R_IndicationC2_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &R_IndicationC3_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** Test_IndicationConfig
**
**==============================================================================
*/

/* property Test_IndicationConfig.className */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_className_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00636509, /* code */
    MI_T("className"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, className), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.configFilepath */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_configFilepath_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063680E, /* code */
    MI_T("configFilepath"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, configFilepath), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.testGroup */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_testGroup_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00747009, /* code */
    MI_T("testGroup"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, testGroup), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.intervalMS */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_intervalMS_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069730A, /* code */
    MI_T("intervalMS"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, intervalMS), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.failAfterCount */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_failAfterCount_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0066740E, /* code */
    MI_T("failAfterCount"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, failAfterCount), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.failResult */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_failResult_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0066740A, /* code */
    MI_T("failResult"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, failResult), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.initBehavior */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_initBehavior_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069720C, /* code */
    MI_T("initBehavior"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, initBehavior), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.initResultCode */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_initResultCode_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069650E, /* code */
    MI_T("initResultCode"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, initResultCode), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.initTimeoutMS */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_initTimeoutMS_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069730D, /* code */
    MI_T("initTimeoutMS"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, initTimeoutMS), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.finalizeBehavior */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_finalizeBehavior_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00667210, /* code */
    MI_T("finalizeBehavior"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, finalizeBehavior), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.finalizeResultCode */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_finalizeResultCode_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00666512, /* code */
    MI_T("finalizeResultCode"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, finalizeResultCode), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.postBehavior */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_postBehavior_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070720C, /* code */
    MI_T("postBehavior"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, postBehavior), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.miscTestSubGroup */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_miscTestSubGroup_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D7010, /* code */
    MI_T("miscTestSubGroup"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, miscTestSubGroup), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.subscribeBookmark */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_subscribeBookmark_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736B11, /* code */
    MI_T("subscribeBookmark"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, subscribeBookmark), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.providerBookmark */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_providerBookmark_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706B10, /* code */
    MI_T("providerBookmark"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, providerBookmark), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.dialect */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_dialect_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00647407, /* code */
    MI_T("dialect"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, dialect), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.expression */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_expression_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656E0A, /* code */
    MI_T("expression"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, expression), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.evalResult */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_evalResult_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065740A, /* code */
    MI_T("evalResult"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, evalResult), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.logLoadUnloadCall */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_logLoadUnloadCall_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C6C11, /* code */
    MI_T("logLoadUnloadCall"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, logLoadUnloadCall), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.supportedSubscriptionTypes */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_supportedSubscriptionTypes_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073731A, /* code */
    MI_T("supportedSubscriptionTypes"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, supportedSubscriptionTypes), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.currentSubscriptionTypes */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_currentSubscriptionTypes_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637318, /* code */
    MI_T("currentSubscriptionTypes"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, currentSubscriptionTypes), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

/* property Test_IndicationConfig.apicallseq */
static MI_CONST MI_PropertyDecl Test_IndicationConfig_apicallseq_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0061710A, /* code */
    MI_T("apicallseq"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_IndicationConfig, apicallseq), /* offset */
    MI_T("Test_IndicationConfig"), /* origin */
    MI_T("Test_IndicationConfig"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Test_IndicationConfig_props[] =
{
    &Test_IndicationConfig_className_prop,
    &Test_IndicationConfig_configFilepath_prop,
    &Test_IndicationConfig_testGroup_prop,
    &Test_IndicationConfig_intervalMS_prop,
    &Test_IndicationConfig_failAfterCount_prop,
    &Test_IndicationConfig_failResult_prop,
    &Test_IndicationConfig_initBehavior_prop,
    &Test_IndicationConfig_initResultCode_prop,
    &Test_IndicationConfig_initTimeoutMS_prop,
    &Test_IndicationConfig_finalizeBehavior_prop,
    &Test_IndicationConfig_finalizeResultCode_prop,
    &Test_IndicationConfig_postBehavior_prop,
    &Test_IndicationConfig_miscTestSubGroup_prop,
    &Test_IndicationConfig_subscribeBookmark_prop,
    &Test_IndicationConfig_providerBookmark_prop,
    &Test_IndicationConfig_dialect_prop,
    &Test_IndicationConfig_expression_prop,
    &Test_IndicationConfig_evalResult_prop,
    &Test_IndicationConfig_logLoadUnloadCall_prop,
    &Test_IndicationConfig_supportedSubscriptionTypes_prop,
    &Test_IndicationConfig_currentSubscriptionTypes_prop,
    &Test_IndicationConfig_apicallseq_prop,
};

static MI_CONST MI_ProviderFT Test_IndicationConfig_funcs =
{
  (MI_ProviderFT_Load)Test_IndicationConfig_Load,
  (MI_ProviderFT_Unload)Test_IndicationConfig_Unload,
  (MI_ProviderFT_GetInstance)Test_IndicationConfig_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Test_IndicationConfig_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Test_IndicationConfig_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Test_IndicationConfig_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Test_IndicationConfig_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Test_IndicationConfig */
MI_CONST MI_ClassDecl Test_IndicationConfig_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00746715, /* code */
    MI_T("Test_IndicationConfig"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Test_IndicationConfig_props, /* properties */
    MI_COUNT(Test_IndicationConfig_props), /* numProperties */
    sizeof(Test_IndicationConfig), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Test_IndicationConfig_funcs, /* functions */
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
    &CIM_Indication_rtti,
    &L_Indication_rtti,
    &L_IndicationC1_rtti,
    &L_IndicationC2_rtti,
    &L_IndicationC3_rtti,
    &L_Lifecycle_rtti,
    &L_LifecycleC1_rtti,
    &L_LifecycleC2_rtti,
    &R_Indication_rtti,
    &R_IndicationC1_rtti,
    &R_IndicationC2_rtti,
    &R_IndicationC3_rtti,
    &R_Lifecycle_rtti,
    &R_LifecycleC1_rtti,
    &R_LifecycleC2_rtti,
    &Test_Class_rtti,
    &Test_Indication_rtti,
    &Test_IndicationConfig_rtti,
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

