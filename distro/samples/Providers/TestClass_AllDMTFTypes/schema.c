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
#include "TestClass_AllDMTFTypes.h"
#include "TestClass_ForEmbedded.h"

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
** TestClass_PropertyValues
**
**==============================================================================
*/

/* property TestClass_PropertyValues.v_Key */
static MI_CONST MI_PropertyDecl TestClass_PropertyValues_v_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00767905, /* code */
    MI_T("v_Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_PropertyValues, v_Key), /* offset */
    MI_T("TestClass_PropertyValues"), /* origin */
    MI_T("TestClass_PropertyValues"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST TestClass_PropertyValues_props[] =
{
    &TestClass_PropertyValues_v_Key_prop,
};

/* class TestClass_PropertyValues */
MI_CONST MI_ClassDecl TestClass_PropertyValues_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00747318, /* code */
    MI_T("TestClass_PropertyValues"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_PropertyValues_props, /* properties */
    MI_COUNT(TestClass_PropertyValues_props), /* numProperties */
    sizeof(TestClass_PropertyValues), /* size */
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
** TestClass_ForEmbedded
**
**==============================================================================
*/

/* property TestClass_ForEmbedded.embeddedStringValue */
static MI_CONST MI_PropertyDecl TestClass_ForEmbedded_embeddedStringValue_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00656513, /* code */
    MI_T("embeddedStringValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_ForEmbedded, embeddedStringValue), /* offset */
    MI_T("TestClass_ForEmbedded"), /* origin */
    MI_T("TestClass_ForEmbedded"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST TestClass_ForEmbedded_props[] =
{
    &TestClass_ForEmbedded_embeddedStringValue_prop,
};

static MI_CONST MI_ProviderFT TestClass_ForEmbedded_funcs =
{
  (MI_ProviderFT_Load)TestClass_ForEmbedded_Load,
  (MI_ProviderFT_Unload)TestClass_ForEmbedded_Unload,
  (MI_ProviderFT_GetInstance)TestClass_ForEmbedded_GetInstance,
  (MI_ProviderFT_EnumerateInstances)TestClass_ForEmbedded_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)TestClass_ForEmbedded_CreateInstance,
  (MI_ProviderFT_ModifyInstance)TestClass_ForEmbedded_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)TestClass_ForEmbedded_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class TestClass_ForEmbedded */
MI_CONST MI_ClassDecl TestClass_ForEmbedded_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00746415, /* code */
    MI_T("TestClass_ForEmbedded"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_ForEmbedded_props, /* properties */
    MI_COUNT(TestClass_ForEmbedded_props), /* numProperties */
    sizeof(TestClass_ForEmbedded), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &TestClass_ForEmbedded_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** TestClass_AllDMTFTypes
**
**==============================================================================
*/

/* property TestClass_AllDMTFTypes.v_bool */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_bool_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00766C06, /* code */
    MI_T("v_bool"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_bool), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFTypes.v_uint8 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_uint8_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00763807, /* code */
    MI_T("v_uint8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_uint8), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFTypes.v_sint8 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_sint8_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00763807, /* code */
    MI_T("v_sint8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_sint8), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFTypes.v_UINT16 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_UINT16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00763608, /* code */
    MI_T("v_UINT16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_UINT16), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFTypes.v_sint16 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_sint16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00763608, /* code */
    MI_T("v_sint16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_sint16), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFTypes.v_uint32 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_uint32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00763208, /* code */
    MI_T("v_uint32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_uint32), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFTypes.v_sint32 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_sint32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00763208, /* code */
    MI_T("v_sint32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_sint32), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFTypes.v_uint64 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_uint64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00763408, /* code */
    MI_T("v_uint64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_uint64), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFTypes.v_sint64 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_sint64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00763408, /* code */
    MI_T("v_sint64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_sint64), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFTypes.v_rEal32 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_rEal32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00763208, /* code */
    MI_T("v_rEal32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_rEal32), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFTypes.v_Real64 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_Real64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00763408, /* code */
    MI_T("v_Real64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_Real64), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFTypes.v_char16 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_char16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00763608, /* code */
    MI_T("v_char16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_char16), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFTypes.v_string */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_string_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00766708, /* code */
    MI_T("v_string"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_string), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFTypes.v_DATETIME */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_DATETIME_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0076650A, /* code */
    MI_T("v_DATETIME"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_DATETIME), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFTypes.v_embeddedObject */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_embeddedObject_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00767410, /* code */
    MI_T("v_embeddedObject"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_embeddedObject), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* TestClass_AllDMTFTypes_v_embeddedInstance_EmbeddedInstance_qual_value = MI_T("TestClass_ForEmbedded");

static MI_CONST MI_Qualifier TestClass_AllDMTFTypes_v_embeddedInstance_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &TestClass_AllDMTFTypes_v_embeddedInstance_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestClass_AllDMTFTypes_v_embeddedInstance_quals[] =
{
    &TestClass_AllDMTFTypes_v_embeddedInstance_EmbeddedInstance_qual,
};

/* property TestClass_AllDMTFTypes.v_embeddedInstance */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_embeddedInstance_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00766512, /* code */
    MI_T("v_embeddedInstance"), /* name */
    TestClass_AllDMTFTypes_v_embeddedInstance_quals, /* qualifiers */
    MI_COUNT(TestClass_AllDMTFTypes_v_embeddedInstance_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("TestClass_ForEmbedded"), /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_embeddedInstance), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFTypes.v_reference */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_reference_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0076650B, /* code */
    MI_T("v_reference"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("TestClass_ForEmbedded"), /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_reference), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFTypes.v_octetUint8 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFTypes_v_octetUint8_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0076380C, /* code */
    MI_T("v_octetUint8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes, v_octetUint8), /* offset */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_props[] =
{
    &TestClass_PropertyValues_v_Key_prop,
    &TestClass_AllDMTFTypes_v_bool_prop,
    &TestClass_AllDMTFTypes_v_uint8_prop,
    &TestClass_AllDMTFTypes_v_sint8_prop,
    &TestClass_AllDMTFTypes_v_UINT16_prop,
    &TestClass_AllDMTFTypes_v_sint16_prop,
    &TestClass_AllDMTFTypes_v_uint32_prop,
    &TestClass_AllDMTFTypes_v_sint32_prop,
    &TestClass_AllDMTFTypes_v_uint64_prop,
    &TestClass_AllDMTFTypes_v_sint64_prop,
    &TestClass_AllDMTFTypes_v_rEal32_prop,
    &TestClass_AllDMTFTypes_v_Real64_prop,
    &TestClass_AllDMTFTypes_v_char16_prop,
    &TestClass_AllDMTFTypes_v_string_prop,
    &TestClass_AllDMTFTypes_v_DATETIME_prop,
    &TestClass_AllDMTFTypes_v_embeddedObject_prop,
    &TestClass_AllDMTFTypes_v_embeddedInstance_prop,
    &TestClass_AllDMTFTypes_v_reference_prop,
    &TestClass_AllDMTFTypes_v_octetUint8_prop,
};

/* parameter TestClass_AllDMTFTypes.GetBoolValue(): boolVal */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetBoolValue_boolVal_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00626C07, /* code */
    MI_T("boolVal"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetBoolValue, boolVal), /* offset */
};

/* parameter TestClass_AllDMTFTypes.GetBoolValue(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetBoolValue_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetBoolValue, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_GetBoolValue_params[] =
{
    &TestClass_AllDMTFTypes_GetBoolValue_MIReturn_param,
    &TestClass_AllDMTFTypes_GetBoolValue_boolVal_param,
};

/* method TestClass_AllDMTFTypes.GetBoolValue() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetBoolValue_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067650C, /* code */
    MI_T("GetBoolValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_GetBoolValue_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_GetBoolValue_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_GetBoolValue), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_GetBoolValue, /* method */
};

/* parameter TestClass_AllDMTFTypes.SetBoolValue(): boolVal */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetBoolValue_boolVal_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00626C07, /* code */
    MI_T("boolVal"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetBoolValue, boolVal), /* offset */
};

/* parameter TestClass_AllDMTFTypes.SetBoolValue(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetBoolValue_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetBoolValue, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_SetBoolValue_params[] =
{
    &TestClass_AllDMTFTypes_SetBoolValue_MIReturn_param,
    &TestClass_AllDMTFTypes_SetBoolValue_boolVal_param,
};

/* method TestClass_AllDMTFTypes.SetBoolValue() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetBoolValue_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650C, /* code */
    MI_T("SetBoolValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_SetBoolValue_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_SetBoolValue_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_SetBoolValue), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_SetBoolValue, /* method */
};

/* parameter TestClass_AllDMTFTypes.GetUint8Value(): Uint8Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetUint8Value_Uint8Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00756C08, /* code */
    MI_T("Uint8Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetUint8Value, Uint8Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.GetUint8Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetUint8Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetUint8Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_GetUint8Value_params[] =
{
    &TestClass_AllDMTFTypes_GetUint8Value_MIReturn_param,
    &TestClass_AllDMTFTypes_GetUint8Value_Uint8Val_param,
};

/* method TestClass_AllDMTFTypes.GetUint8Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetUint8Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067650D, /* code */
    MI_T("GetUint8Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_GetUint8Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_GetUint8Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_GetUint8Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_GetUint8Value, /* method */
};

/* parameter TestClass_AllDMTFTypes.SetUint8Value(): Uint8Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetUint8Value_Uint8Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00756C08, /* code */
    MI_T("Uint8Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetUint8Value, Uint8Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.SetUint8Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetUint8Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetUint8Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_SetUint8Value_params[] =
{
    &TestClass_AllDMTFTypes_SetUint8Value_MIReturn_param,
    &TestClass_AllDMTFTypes_SetUint8Value_Uint8Val_param,
};

/* method TestClass_AllDMTFTypes.SetUint8Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetUint8Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650D, /* code */
    MI_T("SetUint8Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_SetUint8Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_SetUint8Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_SetUint8Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_SetUint8Value, /* method */
};

/* parameter TestClass_AllDMTFTypes.GetSint8Value(): Sint8Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetSint8Value_Sint8Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00736C08, /* code */
    MI_T("Sint8Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetSint8Value, Sint8Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.GetSint8Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetSint8Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetSint8Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_GetSint8Value_params[] =
{
    &TestClass_AllDMTFTypes_GetSint8Value_MIReturn_param,
    &TestClass_AllDMTFTypes_GetSint8Value_Sint8Val_param,
};

/* method TestClass_AllDMTFTypes.GetSint8Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetSint8Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067650D, /* code */
    MI_T("GetSint8Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_GetSint8Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_GetSint8Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_GetSint8Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_GetSint8Value, /* method */
};

/* parameter TestClass_AllDMTFTypes.SetSint8Value(): Sint8Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetSint8Value_Sint8Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00736C08, /* code */
    MI_T("Sint8Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetSint8Value, Sint8Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.SetSint8Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetSint8Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetSint8Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_SetSint8Value_params[] =
{
    &TestClass_AllDMTFTypes_SetSint8Value_MIReturn_param,
    &TestClass_AllDMTFTypes_SetSint8Value_Sint8Val_param,
};

/* method TestClass_AllDMTFTypes.SetSint8Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetSint8Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650D, /* code */
    MI_T("SetSint8Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_SetSint8Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_SetSint8Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_SetSint8Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_SetSint8Value, /* method */
};

/* parameter TestClass_AllDMTFTypes.GetUint16Value(): Uint16Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetUint16Value_Uint16Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00756C09, /* code */
    MI_T("Uint16Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetUint16Value, Uint16Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.GetUint16Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetUint16Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetUint16Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_GetUint16Value_params[] =
{
    &TestClass_AllDMTFTypes_GetUint16Value_MIReturn_param,
    &TestClass_AllDMTFTypes_GetUint16Value_Uint16Val_param,
};

/* method TestClass_AllDMTFTypes.GetUint16Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetUint16Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067650E, /* code */
    MI_T("GetUint16Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_GetUint16Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_GetUint16Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_GetUint16Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_GetUint16Value, /* method */
};

/* parameter TestClass_AllDMTFTypes.SetUint16Value(): Uint16Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetUint16Value_Uint16Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00756C09, /* code */
    MI_T("Uint16Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetUint16Value, Uint16Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.SetUint16Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetUint16Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetUint16Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_SetUint16Value_params[] =
{
    &TestClass_AllDMTFTypes_SetUint16Value_MIReturn_param,
    &TestClass_AllDMTFTypes_SetUint16Value_Uint16Val_param,
};

/* method TestClass_AllDMTFTypes.SetUint16Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetUint16Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650E, /* code */
    MI_T("SetUint16Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_SetUint16Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_SetUint16Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_SetUint16Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_SetUint16Value, /* method */
};

/* parameter TestClass_AllDMTFTypes.GetSint16Value(): Sint16Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetSint16Value_Sint16Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00736C09, /* code */
    MI_T("Sint16Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetSint16Value, Sint16Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.GetSint16Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetSint16Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetSint16Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_GetSint16Value_params[] =
{
    &TestClass_AllDMTFTypes_GetSint16Value_MIReturn_param,
    &TestClass_AllDMTFTypes_GetSint16Value_Sint16Val_param,
};

/* method TestClass_AllDMTFTypes.GetSint16Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetSint16Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067650E, /* code */
    MI_T("GetSint16Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_GetSint16Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_GetSint16Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_GetSint16Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_GetSint16Value, /* method */
};

/* parameter TestClass_AllDMTFTypes.SetSint16Value(): Sint16Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetSint16Value_Sint16Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00736C09, /* code */
    MI_T("Sint16Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetSint16Value, Sint16Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.SetSint16Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetSint16Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetSint16Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_SetSint16Value_params[] =
{
    &TestClass_AllDMTFTypes_SetSint16Value_MIReturn_param,
    &TestClass_AllDMTFTypes_SetSint16Value_Sint16Val_param,
};

/* method TestClass_AllDMTFTypes.SetSint16Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetSint16Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650E, /* code */
    MI_T("SetSint16Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_SetSint16Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_SetSint16Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_SetSint16Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_SetSint16Value, /* method */
};

/* parameter TestClass_AllDMTFTypes.GetUint32Value(): Uint32Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetUint32Value_Uint32Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00756C09, /* code */
    MI_T("Uint32Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetUint32Value, Uint32Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.GetUint32Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetUint32Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetUint32Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_GetUint32Value_params[] =
{
    &TestClass_AllDMTFTypes_GetUint32Value_MIReturn_param,
    &TestClass_AllDMTFTypes_GetUint32Value_Uint32Val_param,
};

/* method TestClass_AllDMTFTypes.GetUint32Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetUint32Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067650E, /* code */
    MI_T("GetUint32Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_GetUint32Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_GetUint32Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_GetUint32Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_GetUint32Value, /* method */
};

/* parameter TestClass_AllDMTFTypes.SetUint32Value(): Uint32Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetUint32Value_Uint32Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00756C09, /* code */
    MI_T("Uint32Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetUint32Value, Uint32Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.SetUint32Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetUint32Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetUint32Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_SetUint32Value_params[] =
{
    &TestClass_AllDMTFTypes_SetUint32Value_MIReturn_param,
    &TestClass_AllDMTFTypes_SetUint32Value_Uint32Val_param,
};

/* method TestClass_AllDMTFTypes.SetUint32Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetUint32Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650E, /* code */
    MI_T("SetUint32Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_SetUint32Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_SetUint32Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_SetUint32Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_SetUint32Value, /* method */
};

/* parameter TestClass_AllDMTFTypes.GetSint32Value(): Sint32Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetSint32Value_Sint32Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00736C09, /* code */
    MI_T("Sint32Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetSint32Value, Sint32Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.GetSint32Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetSint32Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetSint32Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_GetSint32Value_params[] =
{
    &TestClass_AllDMTFTypes_GetSint32Value_MIReturn_param,
    &TestClass_AllDMTFTypes_GetSint32Value_Sint32Val_param,
};

/* method TestClass_AllDMTFTypes.GetSint32Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetSint32Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067650E, /* code */
    MI_T("GetSint32Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_GetSint32Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_GetSint32Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_GetSint32Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_GetSint32Value, /* method */
};

/* parameter TestClass_AllDMTFTypes.SetSint32Value(): Sint32Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetSint32Value_Sint32Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00736C09, /* code */
    MI_T("Sint32Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetSint32Value, Sint32Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.SetSint32Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetSint32Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetSint32Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_SetSint32Value_params[] =
{
    &TestClass_AllDMTFTypes_SetSint32Value_MIReturn_param,
    &TestClass_AllDMTFTypes_SetSint32Value_Sint32Val_param,
};

/* method TestClass_AllDMTFTypes.SetSint32Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetSint32Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650E, /* code */
    MI_T("SetSint32Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_SetSint32Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_SetSint32Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_SetSint32Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_SetSint32Value, /* method */
};

/* parameter TestClass_AllDMTFTypes.GetUint64Value(): Uint64Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetUint64Value_Uint64Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00756C09, /* code */
    MI_T("Uint64Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetUint64Value, Uint64Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.GetUint64Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetUint64Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetUint64Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_GetUint64Value_params[] =
{
    &TestClass_AllDMTFTypes_GetUint64Value_MIReturn_param,
    &TestClass_AllDMTFTypes_GetUint64Value_Uint64Val_param,
};

/* method TestClass_AllDMTFTypes.GetUint64Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetUint64Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067650E, /* code */
    MI_T("GetUint64Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_GetUint64Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_GetUint64Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_GetUint64Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_GetUint64Value, /* method */
};

/* parameter TestClass_AllDMTFTypes.SetUint64Value(): Uint64Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetUint64Value_Uint64Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00756C09, /* code */
    MI_T("Uint64Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetUint64Value, Uint64Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.SetUint64Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetUint64Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetUint64Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_SetUint64Value_params[] =
{
    &TestClass_AllDMTFTypes_SetUint64Value_MIReturn_param,
    &TestClass_AllDMTFTypes_SetUint64Value_Uint64Val_param,
};

/* method TestClass_AllDMTFTypes.SetUint64Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetUint64Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650E, /* code */
    MI_T("SetUint64Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_SetUint64Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_SetUint64Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_SetUint64Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_SetUint64Value, /* method */
};

/* parameter TestClass_AllDMTFTypes.GetSint64Value(): Sint64Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetSint64Value_Sint64Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00736C09, /* code */
    MI_T("Sint64Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetSint64Value, Sint64Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.GetSint64Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetSint64Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetSint64Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_GetSint64Value_params[] =
{
    &TestClass_AllDMTFTypes_GetSint64Value_MIReturn_param,
    &TestClass_AllDMTFTypes_GetSint64Value_Sint64Val_param,
};

/* method TestClass_AllDMTFTypes.GetSint64Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetSint64Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067650E, /* code */
    MI_T("GetSint64Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_GetSint64Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_GetSint64Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_GetSint64Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_GetSint64Value, /* method */
};

/* parameter TestClass_AllDMTFTypes.SetSint64Value(): Sint64Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetSint64Value_Sint64Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00736C09, /* code */
    MI_T("Sint64Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetSint64Value, Sint64Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.SetSint64Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetSint64Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetSint64Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_SetSint64Value_params[] =
{
    &TestClass_AllDMTFTypes_SetSint64Value_MIReturn_param,
    &TestClass_AllDMTFTypes_SetSint64Value_Sint64Val_param,
};

/* method TestClass_AllDMTFTypes.SetSint64Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetSint64Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650E, /* code */
    MI_T("SetSint64Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_SetSint64Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_SetSint64Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_SetSint64Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_SetSint64Value, /* method */
};

/* parameter TestClass_AllDMTFTypes.GetStringCustomOption(): optionName */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetStringCustomOption_optionName_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006F650A, /* code */
    MI_T("optionName"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetStringCustomOption, optionName), /* offset */
};

/* parameter TestClass_AllDMTFTypes.GetStringCustomOption(): optionValue */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetStringCustomOption_optionValue_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F650B, /* code */
    MI_T("optionValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetStringCustomOption, optionValue), /* offset */
};

/* parameter TestClass_AllDMTFTypes.GetStringCustomOption(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetStringCustomOption_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetStringCustomOption, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_GetStringCustomOption_params[] =
{
    &TestClass_AllDMTFTypes_GetStringCustomOption_MIReturn_param,
    &TestClass_AllDMTFTypes_GetStringCustomOption_optionName_param,
    &TestClass_AllDMTFTypes_GetStringCustomOption_optionValue_param,
};

/* method TestClass_AllDMTFTypes.GetStringCustomOption() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetStringCustomOption_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00676E15, /* code */
    MI_T("GetStringCustomOption"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_GetStringCustomOption_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_GetStringCustomOption_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_GetStringCustomOption), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_GetStringCustomOption, /* method */
};

/* parameter TestClass_AllDMTFTypes.GetEmbeddedObjectValue(): EmbeddedObjectVal */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetEmbeddedObjectValue_EmbeddedObjectVal_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00656C11, /* code */
    MI_T("EmbeddedObjectVal"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetEmbeddedObjectValue, EmbeddedObjectVal), /* offset */
};

/* parameter TestClass_AllDMTFTypes.GetEmbeddedObjectValue(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetEmbeddedObjectValue_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetEmbeddedObjectValue, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_GetEmbeddedObjectValue_params[] =
{
    &TestClass_AllDMTFTypes_GetEmbeddedObjectValue_MIReturn_param,
    &TestClass_AllDMTFTypes_GetEmbeddedObjectValue_EmbeddedObjectVal_param,
};

/* method TestClass_AllDMTFTypes.GetEmbeddedObjectValue() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetEmbeddedObjectValue_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00676516, /* code */
    MI_T("GetEmbeddedObjectValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_GetEmbeddedObjectValue_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_GetEmbeddedObjectValue_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_GetEmbeddedObjectValue), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_GetEmbeddedObjectValue, /* method */
};

/* parameter TestClass_AllDMTFTypes.SetEmbeddedObjectValue(): EmbeddedObjectVal */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetEmbeddedObjectValue_EmbeddedObjectVal_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00656C11, /* code */
    MI_T("EmbeddedObjectVal"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetEmbeddedObjectValue, EmbeddedObjectVal), /* offset */
};

/* parameter TestClass_AllDMTFTypes.SetEmbeddedObjectValue(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetEmbeddedObjectValue_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetEmbeddedObjectValue, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_SetEmbeddedObjectValue_params[] =
{
    &TestClass_AllDMTFTypes_SetEmbeddedObjectValue_MIReturn_param,
    &TestClass_AllDMTFTypes_SetEmbeddedObjectValue_EmbeddedObjectVal_param,
};

/* method TestClass_AllDMTFTypes.SetEmbeddedObjectValue() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetEmbeddedObjectValue_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00736516, /* code */
    MI_T("SetEmbeddedObjectValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_SetEmbeddedObjectValue_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_SetEmbeddedObjectValue_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_SetEmbeddedObjectValue), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_SetEmbeddedObjectValue, /* method */
};

static MI_CONST MI_Char* TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_EmbeddedInstanceVal_EmbeddedInstance_qual_value = MI_T("TestClass_ForEmbedded");

static MI_CONST MI_Qualifier TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_EmbeddedInstanceVal_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_EmbeddedInstanceVal_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_EmbeddedInstanceVal_quals[] =
{
    &TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_EmbeddedInstanceVal_EmbeddedInstance_qual,
};

/* parameter TestClass_AllDMTFTypes.GetEmbeddedInstanceValue(): EmbeddedInstanceVal */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_EmbeddedInstanceVal_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00656C13, /* code */
    MI_T("EmbeddedInstanceVal"), /* name */
    TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_EmbeddedInstanceVal_quals, /* qualifiers */
    MI_COUNT(TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_EmbeddedInstanceVal_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("TestClass_ForEmbedded"), /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetEmbeddedInstanceValue, EmbeddedInstanceVal), /* offset */
};

/* parameter TestClass_AllDMTFTypes.GetEmbeddedInstanceValue(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetEmbeddedInstanceValue, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_params[] =
{
    &TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_MIReturn_param,
    &TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_EmbeddedInstanceVal_param,
};

/* method TestClass_AllDMTFTypes.GetEmbeddedInstanceValue() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00676518, /* code */
    MI_T("GetEmbeddedInstanceValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_GetEmbeddedInstanceValue), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_GetEmbeddedInstanceValue, /* method */
};

static MI_CONST MI_Char* TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_EmbeddedInstanceVal_EmbeddedInstance_qual_value = MI_T("TestClass_ForEmbedded");

static MI_CONST MI_Qualifier TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_EmbeddedInstanceVal_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_EmbeddedInstanceVal_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_EmbeddedInstanceVal_quals[] =
{
    &TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_EmbeddedInstanceVal_EmbeddedInstance_qual,
};

/* parameter TestClass_AllDMTFTypes.SetEmbeddedInstanceValue(): EmbeddedInstanceVal */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_EmbeddedInstanceVal_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00656C13, /* code */
    MI_T("EmbeddedInstanceVal"), /* name */
    TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_EmbeddedInstanceVal_quals, /* qualifiers */
    MI_COUNT(TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_EmbeddedInstanceVal_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("TestClass_ForEmbedded"), /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetEmbeddedInstanceValue, EmbeddedInstanceVal), /* offset */
};

/* parameter TestClass_AllDMTFTypes.SetEmbeddedInstanceValue(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetEmbeddedInstanceValue, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_params[] =
{
    &TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_MIReturn_param,
    &TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_EmbeddedInstanceVal_param,
};

/* method TestClass_AllDMTFTypes.SetEmbeddedInstanceValue() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00736518, /* code */
    MI_T("SetEmbeddedInstanceValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_SetEmbeddedInstanceValue), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_SetEmbeddedInstanceValue, /* method */
};

/* parameter TestClass_AllDMTFTypes.GetReferenceValue(): ReferenceVal */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetReferenceValue_ReferenceVal_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00726C0C, /* code */
    MI_T("ReferenceVal"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("TestClass_ForEmbedded"), /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetReferenceValue, ReferenceVal), /* offset */
};

/* parameter TestClass_AllDMTFTypes.GetReferenceValue(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetReferenceValue_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetReferenceValue, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_GetReferenceValue_params[] =
{
    &TestClass_AllDMTFTypes_GetReferenceValue_MIReturn_param,
    &TestClass_AllDMTFTypes_GetReferenceValue_ReferenceVal_param,
};

/* method TestClass_AllDMTFTypes.GetReferenceValue() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetReferenceValue_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00676511, /* code */
    MI_T("GetReferenceValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_GetReferenceValue_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_GetReferenceValue_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_GetReferenceValue), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_GetReferenceValue, /* method */
};

/* parameter TestClass_AllDMTFTypes.SetReferenceValue(): ReferenceVal */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetReferenceValue_ReferenceVal_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00726C0C, /* code */
    MI_T("ReferenceVal"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("TestClass_ForEmbedded"), /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetReferenceValue, ReferenceVal), /* offset */
};

/* parameter TestClass_AllDMTFTypes.SetReferenceValue(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetReferenceValue_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetReferenceValue, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_SetReferenceValue_params[] =
{
    &TestClass_AllDMTFTypes_SetReferenceValue_MIReturn_param,
    &TestClass_AllDMTFTypes_SetReferenceValue_ReferenceVal_param,
};

/* method TestClass_AllDMTFTypes.SetReferenceValue() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetReferenceValue_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00736511, /* code */
    MI_T("SetReferenceValue"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_SetReferenceValue_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_SetReferenceValue_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_SetReferenceValue), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_SetReferenceValue, /* method */
};

/* parameter TestClass_AllDMTFTypes.GetOctetUint8Value(): v_octetUint8Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetOctetUint8Value_v_octetUint8Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00766C0F, /* code */
    MI_T("v_octetUint8Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetOctetUint8Value, v_octetUint8Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.GetOctetUint8Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_GetOctetUint8Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_GetOctetUint8Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_GetOctetUint8Value_params[] =
{
    &TestClass_AllDMTFTypes_GetOctetUint8Value_MIReturn_param,
    &TestClass_AllDMTFTypes_GetOctetUint8Value_v_octetUint8Val_param,
};

/* method TestClass_AllDMTFTypes.GetOctetUint8Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_GetOctetUint8Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00676512, /* code */
    MI_T("GetOctetUint8Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_GetOctetUint8Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_GetOctetUint8Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_GetOctetUint8Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_GetOctetUint8Value, /* method */
};

/* parameter TestClass_AllDMTFTypes.SetOctetUint8Value(): v_octetUint8Val */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetOctetUint8Value_v_octetUint8Val_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00766C0F, /* code */
    MI_T("v_octetUint8Val"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetOctetUint8Value, v_octetUint8Val), /* offset */
};

/* parameter TestClass_AllDMTFTypes.SetOctetUint8Value(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFTypes_SetOctetUint8Value_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFTypes_SetOctetUint8Value, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_SetOctetUint8Value_params[] =
{
    &TestClass_AllDMTFTypes_SetOctetUint8Value_MIReturn_param,
    &TestClass_AllDMTFTypes_SetOctetUint8Value_v_octetUint8Val_param,
};

/* method TestClass_AllDMTFTypes.SetOctetUint8Value() */
MI_CONST MI_MethodDecl TestClass_AllDMTFTypes_SetOctetUint8Value_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00736512, /* code */
    MI_T("SetOctetUint8Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_SetOctetUint8Value_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFTypes_SetOctetUint8Value_params), /* numParameters */
    sizeof(TestClass_AllDMTFTypes_SetOctetUint8Value), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFTypes"), /* origin */
    MI_T("TestClass_AllDMTFTypes"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFTypes_Invoke_SetOctetUint8Value, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST TestClass_AllDMTFTypes_meths[] =
{
    &TestClass_AllDMTFTypes_GetBoolValue_rtti,
    &TestClass_AllDMTFTypes_SetBoolValue_rtti,
    &TestClass_AllDMTFTypes_GetUint8Value_rtti,
    &TestClass_AllDMTFTypes_SetUint8Value_rtti,
    &TestClass_AllDMTFTypes_GetSint8Value_rtti,
    &TestClass_AllDMTFTypes_SetSint8Value_rtti,
    &TestClass_AllDMTFTypes_GetUint16Value_rtti,
    &TestClass_AllDMTFTypes_SetUint16Value_rtti,
    &TestClass_AllDMTFTypes_GetSint16Value_rtti,
    &TestClass_AllDMTFTypes_SetSint16Value_rtti,
    &TestClass_AllDMTFTypes_GetUint32Value_rtti,
    &TestClass_AllDMTFTypes_SetUint32Value_rtti,
    &TestClass_AllDMTFTypes_GetSint32Value_rtti,
    &TestClass_AllDMTFTypes_SetSint32Value_rtti,
    &TestClass_AllDMTFTypes_GetUint64Value_rtti,
    &TestClass_AllDMTFTypes_SetUint64Value_rtti,
    &TestClass_AllDMTFTypes_GetSint64Value_rtti,
    &TestClass_AllDMTFTypes_SetSint64Value_rtti,
    &TestClass_AllDMTFTypes_GetStringCustomOption_rtti,
    &TestClass_AllDMTFTypes_GetEmbeddedObjectValue_rtti,
    &TestClass_AllDMTFTypes_SetEmbeddedObjectValue_rtti,
    &TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_rtti,
    &TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_rtti,
    &TestClass_AllDMTFTypes_GetReferenceValue_rtti,
    &TestClass_AllDMTFTypes_SetReferenceValue_rtti,
    &TestClass_AllDMTFTypes_GetOctetUint8Value_rtti,
    &TestClass_AllDMTFTypes_SetOctetUint8Value_rtti,
};

static MI_CONST MI_ProviderFT TestClass_AllDMTFTypes_funcs =
{
  (MI_ProviderFT_Load)TestClass_AllDMTFTypes_Load,
  (MI_ProviderFT_Unload)TestClass_AllDMTFTypes_Unload,
  (MI_ProviderFT_GetInstance)TestClass_AllDMTFTypes_GetInstance,
  (MI_ProviderFT_EnumerateInstances)TestClass_AllDMTFTypes_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)TestClass_AllDMTFTypes_CreateInstance,
  (MI_ProviderFT_ModifyInstance)TestClass_AllDMTFTypes_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)TestClass_AllDMTFTypes_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class TestClass_AllDMTFTypes */
MI_CONST MI_ClassDecl TestClass_AllDMTFTypes_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00747316, /* code */
    MI_T("TestClass_AllDMTFTypes"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFTypes_props, /* properties */
    MI_COUNT(TestClass_AllDMTFTypes_props), /* numProperties */
    sizeof(TestClass_AllDMTFTypes), /* size */
    MI_T("TestClass_PropertyValues"), /* superClass */
    &TestClass_PropertyValues_rtti, /* superClassDecl */
    TestClass_AllDMTFTypes_meths, /* methods */
    MI_COUNT(TestClass_AllDMTFTypes_meths), /* numMethods */
    &schemaDecl, /* schema */
    &TestClass_AllDMTFTypes_funcs, /* functions */
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
    &TestClass_AllDMTFTypes_rtti,
    &TestClass_ForEmbedded_rtti,
    &TestClass_PropertyValues_rtti,
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

