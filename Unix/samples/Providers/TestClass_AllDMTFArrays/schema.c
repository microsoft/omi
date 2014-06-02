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
#include "TestClass_AllDMTFArrays.h"

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
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** TestClass_AllDMTFArrays
**
**==============================================================================
*/

/* property TestClass_AllDMTFArrays.a_bool */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFArrays_a_bool_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00616C06, /* code */
    MI_T("a_bool"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays, a_bool), /* offset */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFArrays.a_uint8 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFArrays_a_uint8_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613807, /* code */
    MI_T("a_uint8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays, a_uint8), /* offset */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFArrays.a_sint8 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFArrays_a_sint8_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613807, /* code */
    MI_T("a_sint8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays, a_sint8), /* offset */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFArrays.a_UINT16 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFArrays_a_UINT16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613608, /* code */
    MI_T("a_UINT16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays, a_UINT16), /* offset */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFArrays.a_sint16 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFArrays_a_sint16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613608, /* code */
    MI_T("a_sint16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays, a_sint16), /* offset */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFArrays.a_uint32 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFArrays_a_uint32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613208, /* code */
    MI_T("a_uint32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays, a_uint32), /* offset */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFArrays.a_sint32 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFArrays_a_sint32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613208, /* code */
    MI_T("a_sint32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays, a_sint32), /* offset */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFArrays.a_uint64 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFArrays_a_uint64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613408, /* code */
    MI_T("a_uint64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays, a_uint64), /* offset */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFArrays.a_sint64 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFArrays_a_sint64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613408, /* code */
    MI_T("a_sint64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays, a_sint64), /* offset */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFArrays.a_rEal32 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFArrays_a_rEal32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613208, /* code */
    MI_T("a_rEal32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays, a_rEal32), /* offset */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFArrays.a_REAL64 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFArrays_a_REAL64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613408, /* code */
    MI_T("a_REAL64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays, a_REAL64), /* offset */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFArrays.a_char16 */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFArrays_a_char16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613608, /* code */
    MI_T("a_char16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays, a_char16), /* offset */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFArrays.a_string */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFArrays_a_string_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00616708, /* code */
    MI_T("a_string"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays, a_string), /* offset */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFArrays.a_DATETIME */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFArrays_a_DATETIME_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0061650A, /* code */
    MI_T("a_DATETIME"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays, a_DATETIME), /* offset */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFArrays.embeddedReference */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFArrays_embeddedReference_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656511, /* code */
    MI_T("embeddedReference"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("TestClass_ForEmbedded"), /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays, embeddedReference), /* offset */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* TestClass_AllDMTFArrays_a_embeddedInstance_EmbeddedInstance_qual_value = MI_T("TestClass_ForEmbedded");

static MI_CONST MI_Qualifier TestClass_AllDMTFArrays_a_embeddedInstance_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &TestClass_AllDMTFArrays_a_embeddedInstance_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestClass_AllDMTFArrays_a_embeddedInstance_quals[] =
{
    &TestClass_AllDMTFArrays_a_embeddedInstance_EmbeddedInstance_qual,
};

/* property TestClass_AllDMTFArrays.a_embeddedInstance */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFArrays_a_embeddedInstance_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00616512, /* code */
    MI_T("a_embeddedInstance"), /* name */
    TestClass_AllDMTFArrays_a_embeddedInstance_quals, /* qualifiers */
    MI_COUNT(TestClass_AllDMTFArrays_a_embeddedInstance_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("TestClass_ForEmbedded"), /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays, a_embeddedInstance), /* offset */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    NULL,
};

/* property TestClass_AllDMTFArrays.a_embeddedObject */
static MI_CONST MI_PropertyDecl TestClass_AllDMTFArrays_a_embeddedObject_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00617410, /* code */
    MI_T("a_embeddedObject"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays, a_embeddedObject), /* offset */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_props[] =
{
    &TestClass_PropertyValues_v_Key_prop,
    &TestClass_AllDMTFArrays_a_bool_prop,
    &TestClass_AllDMTFArrays_a_uint8_prop,
    &TestClass_AllDMTFArrays_a_sint8_prop,
    &TestClass_AllDMTFArrays_a_UINT16_prop,
    &TestClass_AllDMTFArrays_a_sint16_prop,
    &TestClass_AllDMTFArrays_a_uint32_prop,
    &TestClass_AllDMTFArrays_a_sint32_prop,
    &TestClass_AllDMTFArrays_a_uint64_prop,
    &TestClass_AllDMTFArrays_a_sint64_prop,
    &TestClass_AllDMTFArrays_a_rEal32_prop,
    &TestClass_AllDMTFArrays_a_REAL64_prop,
    &TestClass_AllDMTFArrays_a_char16_prop,
    &TestClass_AllDMTFArrays_a_string_prop,
    &TestClass_AllDMTFArrays_a_DATETIME_prop,
    &TestClass_AllDMTFArrays_embeddedReference_prop,
    &TestClass_AllDMTFArrays_a_embeddedInstance_prop,
    &TestClass_AllDMTFArrays_a_embeddedObject_prop,
};

/* parameter TestClass_AllDMTFArrays.GetBooleanArray(): booleanArray */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetBooleanArray_booleanArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0062790C, /* code */
    MI_T("booleanArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetBooleanArray, booleanArray), /* offset */
};

/* parameter TestClass_AllDMTFArrays.GetBooleanArray(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetBooleanArray_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetBooleanArray, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetBooleanArray_params[] =
{
    &TestClass_AllDMTFArrays_GetBooleanArray_MIReturn_param,
    &TestClass_AllDMTFArrays_GetBooleanArray_booleanArray_param,
};

/* method TestClass_AllDMTFArrays.GetBooleanArray() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetBooleanArray_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067790F, /* code */
    MI_T("GetBooleanArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_GetBooleanArray_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_GetBooleanArray_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_GetBooleanArray), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_GetBooleanArray, /* method */
};

/* parameter TestClass_AllDMTFArrays.SetBooleanArray(): booleanArray */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetBooleanArray_booleanArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0062790C, /* code */
    MI_T("booleanArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetBooleanArray, booleanArray), /* offset */
};

/* parameter TestClass_AllDMTFArrays.SetBooleanArray(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetBooleanArray_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetBooleanArray, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetBooleanArray_params[] =
{
    &TestClass_AllDMTFArrays_SetBooleanArray_MIReturn_param,
    &TestClass_AllDMTFArrays_SetBooleanArray_booleanArray_param,
};

/* method TestClass_AllDMTFArrays.SetBooleanArray() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetBooleanArray_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073790F, /* code */
    MI_T("SetBooleanArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_SetBooleanArray_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_SetBooleanArray_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_SetBooleanArray), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_SetBooleanArray, /* method */
};

/* parameter TestClass_AllDMTFArrays.GetUint8Array(): uint8Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetUint8Array_uint8Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0075790A, /* code */
    MI_T("uint8Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetUint8Array, uint8Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.GetUint8Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetUint8Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetUint8Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetUint8Array_params[] =
{
    &TestClass_AllDMTFArrays_GetUint8Array_MIReturn_param,
    &TestClass_AllDMTFArrays_GetUint8Array_uint8Array_param,
};

/* method TestClass_AllDMTFArrays.GetUint8Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetUint8Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067790D, /* code */
    MI_T("GetUint8Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_GetUint8Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_GetUint8Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_GetUint8Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_GetUint8Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.SetUint8Array(): uint8Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetUint8Array_uint8Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0075790A, /* code */
    MI_T("uint8Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetUint8Array, uint8Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.SetUint8Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetUint8Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetUint8Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetUint8Array_params[] =
{
    &TestClass_AllDMTFArrays_SetUint8Array_MIReturn_param,
    &TestClass_AllDMTFArrays_SetUint8Array_uint8Array_param,
};

/* method TestClass_AllDMTFArrays.SetUint8Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetUint8Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073790D, /* code */
    MI_T("SetUint8Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_SetUint8Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_SetUint8Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_SetUint8Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_SetUint8Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.GetSint8Array(): sint8Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetSint8Array_sint8Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0073790A, /* code */
    MI_T("sint8Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetSint8Array, sint8Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.GetSint8Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetSint8Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetSint8Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetSint8Array_params[] =
{
    &TestClass_AllDMTFArrays_GetSint8Array_MIReturn_param,
    &TestClass_AllDMTFArrays_GetSint8Array_sint8Array_param,
};

/* method TestClass_AllDMTFArrays.GetSint8Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetSint8Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067790D, /* code */
    MI_T("GetSint8Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_GetSint8Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_GetSint8Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_GetSint8Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_GetSint8Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.SetSint8Array(): sint8Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetSint8Array_sint8Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0073790A, /* code */
    MI_T("sint8Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetSint8Array, sint8Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.SetSint8Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetSint8Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetSint8Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetSint8Array_params[] =
{
    &TestClass_AllDMTFArrays_SetSint8Array_MIReturn_param,
    &TestClass_AllDMTFArrays_SetSint8Array_sint8Array_param,
};

/* method TestClass_AllDMTFArrays.SetSint8Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetSint8Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073790D, /* code */
    MI_T("SetSint8Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_SetSint8Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_SetSint8Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_SetSint8Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_SetSint8Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.GetUint16Array(): uint16Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetUint16Array_uint16Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0075790B, /* code */
    MI_T("uint16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetUint16Array, uint16Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.GetUint16Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetUint16Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetUint16Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetUint16Array_params[] =
{
    &TestClass_AllDMTFArrays_GetUint16Array_MIReturn_param,
    &TestClass_AllDMTFArrays_GetUint16Array_uint16Array_param,
};

/* method TestClass_AllDMTFArrays.GetUint16Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetUint16Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067790E, /* code */
    MI_T("GetUint16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_GetUint16Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_GetUint16Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_GetUint16Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_GetUint16Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.SetUint16Array(): uint16Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetUint16Array_uint16Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0075790B, /* code */
    MI_T("uint16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetUint16Array, uint16Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.SetUint16Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetUint16Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetUint16Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetUint16Array_params[] =
{
    &TestClass_AllDMTFArrays_SetUint16Array_MIReturn_param,
    &TestClass_AllDMTFArrays_SetUint16Array_uint16Array_param,
};

/* method TestClass_AllDMTFArrays.SetUint16Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetUint16Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073790E, /* code */
    MI_T("SetUint16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_SetUint16Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_SetUint16Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_SetUint16Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_SetUint16Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.GetSint16Array(): sint16Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetSint16Array_sint16Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0073790B, /* code */
    MI_T("sint16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetSint16Array, sint16Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.GetSint16Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetSint16Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetSint16Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetSint16Array_params[] =
{
    &TestClass_AllDMTFArrays_GetSint16Array_MIReturn_param,
    &TestClass_AllDMTFArrays_GetSint16Array_sint16Array_param,
};

/* method TestClass_AllDMTFArrays.GetSint16Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetSint16Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067790E, /* code */
    MI_T("GetSint16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_GetSint16Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_GetSint16Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_GetSint16Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_GetSint16Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.SetSint16Array(): sint16Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetSint16Array_sint16Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0073790B, /* code */
    MI_T("sint16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetSint16Array, sint16Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.SetSint16Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetSint16Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetSint16Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetSint16Array_params[] =
{
    &TestClass_AllDMTFArrays_SetSint16Array_MIReturn_param,
    &TestClass_AllDMTFArrays_SetSint16Array_sint16Array_param,
};

/* method TestClass_AllDMTFArrays.SetSint16Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetSint16Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073790E, /* code */
    MI_T("SetSint16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_SetSint16Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_SetSint16Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_SetSint16Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_SetSint16Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.GetUint32Array(): uint32Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetUint32Array_uint32Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0075790B, /* code */
    MI_T("uint32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetUint32Array, uint32Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.GetUint32Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetUint32Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetUint32Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetUint32Array_params[] =
{
    &TestClass_AllDMTFArrays_GetUint32Array_MIReturn_param,
    &TestClass_AllDMTFArrays_GetUint32Array_uint32Array_param,
};

/* method TestClass_AllDMTFArrays.GetUint32Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetUint32Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067790E, /* code */
    MI_T("GetUint32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_GetUint32Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_GetUint32Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_GetUint32Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_GetUint32Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.SetUint32Array(): uint32Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetUint32Array_uint32Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0075790B, /* code */
    MI_T("uint32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetUint32Array, uint32Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.SetUint32Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetUint32Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetUint32Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetUint32Array_params[] =
{
    &TestClass_AllDMTFArrays_SetUint32Array_MIReturn_param,
    &TestClass_AllDMTFArrays_SetUint32Array_uint32Array_param,
};

/* method TestClass_AllDMTFArrays.SetUint32Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetUint32Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073790E, /* code */
    MI_T("SetUint32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_SetUint32Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_SetUint32Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_SetUint32Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_SetUint32Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.GetSint32Array(): sint32Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetSint32Array_sint32Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0073790B, /* code */
    MI_T("sint32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetSint32Array, sint32Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.GetSint32Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetSint32Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetSint32Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetSint32Array_params[] =
{
    &TestClass_AllDMTFArrays_GetSint32Array_MIReturn_param,
    &TestClass_AllDMTFArrays_GetSint32Array_sint32Array_param,
};

/* method TestClass_AllDMTFArrays.GetSint32Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetSint32Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067790E, /* code */
    MI_T("GetSint32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_GetSint32Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_GetSint32Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_GetSint32Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_GetSint32Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.SetSint32Array(): sint32Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetSint32Array_sint32Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0073790B, /* code */
    MI_T("sint32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetSint32Array, sint32Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.SetSint32Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetSint32Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetSint32Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetSint32Array_params[] =
{
    &TestClass_AllDMTFArrays_SetSint32Array_MIReturn_param,
    &TestClass_AllDMTFArrays_SetSint32Array_sint32Array_param,
};

/* method TestClass_AllDMTFArrays.SetSint32Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetSint32Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073790E, /* code */
    MI_T("SetSint32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_SetSint32Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_SetSint32Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_SetSint32Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_SetSint32Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.GetUint64Array(): uint64Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetUint64Array_uint64Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0075790B, /* code */
    MI_T("uint64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetUint64Array, uint64Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.GetUint64Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetUint64Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetUint64Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetUint64Array_params[] =
{
    &TestClass_AllDMTFArrays_GetUint64Array_MIReturn_param,
    &TestClass_AllDMTFArrays_GetUint64Array_uint64Array_param,
};

/* method TestClass_AllDMTFArrays.GetUint64Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetUint64Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067790E, /* code */
    MI_T("GetUint64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_GetUint64Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_GetUint64Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_GetUint64Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_GetUint64Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.SetUint64Array(): uint64Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetUint64Array_uint64Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0075790B, /* code */
    MI_T("uint64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetUint64Array, uint64Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.SetUint64Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetUint64Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetUint64Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetUint64Array_params[] =
{
    &TestClass_AllDMTFArrays_SetUint64Array_MIReturn_param,
    &TestClass_AllDMTFArrays_SetUint64Array_uint64Array_param,
};

/* method TestClass_AllDMTFArrays.SetUint64Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetUint64Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073790E, /* code */
    MI_T("SetUint64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_SetUint64Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_SetUint64Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_SetUint64Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_SetUint64Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.GetSint64Array(): sint64Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetSint64Array_sint64Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0073790B, /* code */
    MI_T("sint64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetSint64Array, sint64Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.GetSint64Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetSint64Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetSint64Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetSint64Array_params[] =
{
    &TestClass_AllDMTFArrays_GetSint64Array_MIReturn_param,
    &TestClass_AllDMTFArrays_GetSint64Array_sint64Array_param,
};

/* method TestClass_AllDMTFArrays.GetSint64Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetSint64Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067790E, /* code */
    MI_T("GetSint64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_GetSint64Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_GetSint64Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_GetSint64Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_GetSint64Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.SetSint64Array(): sint64Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetSint64Array_sint64Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0073790B, /* code */
    MI_T("sint64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetSint64Array, sint64Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.SetSint64Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetSint64Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetSint64Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetSint64Array_params[] =
{
    &TestClass_AllDMTFArrays_SetSint64Array_MIReturn_param,
    &TestClass_AllDMTFArrays_SetSint64Array_sint64Array_param,
};

/* method TestClass_AllDMTFArrays.SetSint64Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetSint64Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073790E, /* code */
    MI_T("SetSint64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_SetSint64Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_SetSint64Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_SetSint64Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_SetSint64Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.GetReal32Array(): real32Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetReal32Array_real32Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0072790B, /* code */
    MI_T("real32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetReal32Array, real32Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.GetReal32Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetReal32Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetReal32Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetReal32Array_params[] =
{
    &TestClass_AllDMTFArrays_GetReal32Array_MIReturn_param,
    &TestClass_AllDMTFArrays_GetReal32Array_real32Array_param,
};

/* method TestClass_AllDMTFArrays.GetReal32Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetReal32Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067790E, /* code */
    MI_T("GetReal32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_GetReal32Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_GetReal32Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_GetReal32Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_GetReal32Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.SetReal32Array(): real32Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetReal32Array_real32Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0072790B, /* code */
    MI_T("real32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetReal32Array, real32Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.SetReal32Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetReal32Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetReal32Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetReal32Array_params[] =
{
    &TestClass_AllDMTFArrays_SetReal32Array_MIReturn_param,
    &TestClass_AllDMTFArrays_SetReal32Array_real32Array_param,
};

/* method TestClass_AllDMTFArrays.SetReal32Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetReal32Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073790E, /* code */
    MI_T("SetReal32Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_SetReal32Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_SetReal32Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_SetReal32Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_SetReal32Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.GetReal64Array(): real64Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetReal64Array_real64Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0072790B, /* code */
    MI_T("real64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetReal64Array, real64Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.GetReal64Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetReal64Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetReal64Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetReal64Array_params[] =
{
    &TestClass_AllDMTFArrays_GetReal64Array_MIReturn_param,
    &TestClass_AllDMTFArrays_GetReal64Array_real64Array_param,
};

/* method TestClass_AllDMTFArrays.GetReal64Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetReal64Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067790E, /* code */
    MI_T("GetReal64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_GetReal64Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_GetReal64Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_GetReal64Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_GetReal64Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.SetReal64Array(): real64Array */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetReal64Array_real64Array_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0072790B, /* code */
    MI_T("real64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetReal64Array, real64Array), /* offset */
};

/* parameter TestClass_AllDMTFArrays.SetReal64Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetReal64Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetReal64Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetReal64Array_params[] =
{
    &TestClass_AllDMTFArrays_SetReal64Array_MIReturn_param,
    &TestClass_AllDMTFArrays_SetReal64Array_real64Array_param,
};

/* method TestClass_AllDMTFArrays.SetReal64Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetReal64Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073790E, /* code */
    MI_T("SetReal64Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_SetReal64Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_SetReal64Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_SetReal64Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_SetReal64Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.GetChar16Array(): charArray */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetChar16Array_charArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00637909, /* code */
    MI_T("charArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetChar16Array, charArray), /* offset */
};

/* parameter TestClass_AllDMTFArrays.GetChar16Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetChar16Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetChar16Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetChar16Array_params[] =
{
    &TestClass_AllDMTFArrays_GetChar16Array_MIReturn_param,
    &TestClass_AllDMTFArrays_GetChar16Array_charArray_param,
};

/* method TestClass_AllDMTFArrays.GetChar16Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetChar16Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067790E, /* code */
    MI_T("GetChar16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_GetChar16Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_GetChar16Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_GetChar16Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_GetChar16Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.SetChar16Array(): charArray */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetChar16Array_charArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00637909, /* code */
    MI_T("charArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetChar16Array, charArray), /* offset */
};

/* parameter TestClass_AllDMTFArrays.SetChar16Array(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetChar16Array_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetChar16Array, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetChar16Array_params[] =
{
    &TestClass_AllDMTFArrays_SetChar16Array_MIReturn_param,
    &TestClass_AllDMTFArrays_SetChar16Array_charArray_param,
};

/* method TestClass_AllDMTFArrays.SetChar16Array() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetChar16Array_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073790E, /* code */
    MI_T("SetChar16Array"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_SetChar16Array_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_SetChar16Array_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_SetChar16Array), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_SetChar16Array, /* method */
};

/* parameter TestClass_AllDMTFArrays.GetStringArray(): StringArray */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetStringArray_StringArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0073790B, /* code */
    MI_T("StringArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetStringArray, StringArray), /* offset */
};

/* parameter TestClass_AllDMTFArrays.GetStringArray(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetStringArray_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetStringArray, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetStringArray_params[] =
{
    &TestClass_AllDMTFArrays_GetStringArray_MIReturn_param,
    &TestClass_AllDMTFArrays_GetStringArray_StringArray_param,
};

/* method TestClass_AllDMTFArrays.GetStringArray() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetStringArray_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067790E, /* code */
    MI_T("GetStringArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_GetStringArray_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_GetStringArray_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_GetStringArray), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_GetStringArray, /* method */
};

/* parameter TestClass_AllDMTFArrays.SetStringArray(): StringArray */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetStringArray_StringArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0073790B, /* code */
    MI_T("StringArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetStringArray, StringArray), /* offset */
};

/* parameter TestClass_AllDMTFArrays.SetStringArray(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetStringArray_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetStringArray, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetStringArray_params[] =
{
    &TestClass_AllDMTFArrays_SetStringArray_MIReturn_param,
    &TestClass_AllDMTFArrays_SetStringArray_StringArray_param,
};

/* method TestClass_AllDMTFArrays.SetStringArray() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetStringArray_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073790E, /* code */
    MI_T("SetStringArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_SetStringArray_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_SetStringArray_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_SetStringArray), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_SetStringArray, /* method */
};

/* parameter TestClass_AllDMTFArrays.GetDateTimeArray(): datetimeArray */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetDateTimeArray_datetimeArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0064790D, /* code */
    MI_T("datetimeArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetDateTimeArray, datetimeArray), /* offset */
};

/* parameter TestClass_AllDMTFArrays.GetDateTimeArray(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetDateTimeArray_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetDateTimeArray, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetDateTimeArray_params[] =
{
    &TestClass_AllDMTFArrays_GetDateTimeArray_MIReturn_param,
    &TestClass_AllDMTFArrays_GetDateTimeArray_datetimeArray_param,
};

/* method TestClass_AllDMTFArrays.GetDateTimeArray() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetDateTimeArray_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00677910, /* code */
    MI_T("GetDateTimeArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_GetDateTimeArray_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_GetDateTimeArray_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_GetDateTimeArray), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_GetDateTimeArray, /* method */
};

/* parameter TestClass_AllDMTFArrays.SetdatetimeArray(): datetimeArray */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetdatetimeArray_datetimeArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0064790D, /* code */
    MI_T("datetimeArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetdatetimeArray, datetimeArray), /* offset */
};

/* parameter TestClass_AllDMTFArrays.SetdatetimeArray(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetdatetimeArray_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetdatetimeArray, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetdatetimeArray_params[] =
{
    &TestClass_AllDMTFArrays_SetdatetimeArray_MIReturn_param,
    &TestClass_AllDMTFArrays_SetdatetimeArray_datetimeArray_param,
};

/* method TestClass_AllDMTFArrays.SetdatetimeArray() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetdatetimeArray_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00737910, /* code */
    MI_T("SetdatetimeArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_SetdatetimeArray_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_SetdatetimeArray_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_SetdatetimeArray), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_SetdatetimeArray, /* method */
};

/* parameter TestClass_AllDMTFArrays.GetReferenceArray(): embeddedRefArray */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetReferenceArray_embeddedRefArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00657910, /* code */
    MI_T("embeddedRefArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCEA, /* type */
    MI_T("TestClass_ForEmbedded"), /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetReferenceArray, embeddedRefArray), /* offset */
};

/* parameter TestClass_AllDMTFArrays.GetReferenceArray(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetReferenceArray_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetReferenceArray, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetReferenceArray_params[] =
{
    &TestClass_AllDMTFArrays_GetReferenceArray_MIReturn_param,
    &TestClass_AllDMTFArrays_GetReferenceArray_embeddedRefArray_param,
};

/* method TestClass_AllDMTFArrays.GetReferenceArray() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetReferenceArray_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00677911, /* code */
    MI_T("GetReferenceArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_GetReferenceArray_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_GetReferenceArray_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_GetReferenceArray), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_GetReferenceArray, /* method */
};

/* parameter TestClass_AllDMTFArrays.SetReferenceArray(): embeddedRefArray */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetReferenceArray_embeddedRefArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00657910, /* code */
    MI_T("embeddedRefArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCEA, /* type */
    MI_T("TestClass_ForEmbedded"), /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetReferenceArray, embeddedRefArray), /* offset */
};

/* parameter TestClass_AllDMTFArrays.SetReferenceArray(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetReferenceArray_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetReferenceArray, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetReferenceArray_params[] =
{
    &TestClass_AllDMTFArrays_SetReferenceArray_MIReturn_param,
    &TestClass_AllDMTFArrays_SetReferenceArray_embeddedRefArray_param,
};

/* method TestClass_AllDMTFArrays.SetReferenceArray() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetReferenceArray_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00737911, /* code */
    MI_T("SetReferenceArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_SetReferenceArray_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_SetReferenceArray_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_SetReferenceArray), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_SetReferenceArray, /* method */
};

static MI_CONST MI_Char* TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_embeddedInstanceArray_EmbeddedInstance_qual_value = MI_T("TestClass_ForEmbedded");

static MI_CONST MI_Qualifier TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_embeddedInstanceArray_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_embeddedInstanceArray_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_embeddedInstanceArray_quals[] =
{
    &TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_embeddedInstanceArray_EmbeddedInstance_qual,
};

/* parameter TestClass_AllDMTFArrays.GetEmbeddedInstanceArray(): embeddedInstanceArray */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_embeddedInstanceArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00657915, /* code */
    MI_T("embeddedInstanceArray"), /* name */
    TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_embeddedInstanceArray_quals, /* qualifiers */
    MI_COUNT(TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_embeddedInstanceArray_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("TestClass_ForEmbedded"), /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetEmbeddedInstanceArray, embeddedInstanceArray), /* offset */
};

/* parameter TestClass_AllDMTFArrays.GetEmbeddedInstanceArray(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetEmbeddedInstanceArray, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_params[] =
{
    &TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_MIReturn_param,
    &TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_embeddedInstanceArray_param,
};

/* method TestClass_AllDMTFArrays.GetEmbeddedInstanceArray() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00677918, /* code */
    MI_T("GetEmbeddedInstanceArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_GetEmbeddedInstanceArray), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_GetEmbeddedInstanceArray, /* method */
};

static MI_CONST MI_Char* TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_embeddedInstanceArray_EmbeddedInstance_qual_value = MI_T("TestClass_ForEmbedded");

static MI_CONST MI_Qualifier TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_embeddedInstanceArray_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_embeddedInstanceArray_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_embeddedInstanceArray_quals[] =
{
    &TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_embeddedInstanceArray_EmbeddedInstance_qual,
};

/* parameter TestClass_AllDMTFArrays.SetEmbeddedInstanceArray(): embeddedInstanceArray */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_embeddedInstanceArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00657915, /* code */
    MI_T("embeddedInstanceArray"), /* name */
    TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_embeddedInstanceArray_quals, /* qualifiers */
    MI_COUNT(TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_embeddedInstanceArray_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("TestClass_ForEmbedded"), /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetEmbeddedInstanceArray, embeddedInstanceArray), /* offset */
};

/* parameter TestClass_AllDMTFArrays.SetEmbeddedInstanceArray(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetEmbeddedInstanceArray, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_params[] =
{
    &TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_MIReturn_param,
    &TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_embeddedInstanceArray_param,
};

/* method TestClass_AllDMTFArrays.SetEmbeddedInstanceArray() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00737918, /* code */
    MI_T("SetEmbeddedInstanceArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_SetEmbeddedInstanceArray), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_SetEmbeddedInstanceArray, /* method */
};

/* parameter TestClass_AllDMTFArrays.GetEmbeddedObjectArray(): embeddedObjectArray */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetEmbeddedObjectArray_embeddedObjectArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00657913, /* code */
    MI_T("embeddedObjectArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetEmbeddedObjectArray, embeddedObjectArray), /* offset */
};

/* parameter TestClass_AllDMTFArrays.GetEmbeddedObjectArray(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_GetEmbeddedObjectArray_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_GetEmbeddedObjectArray, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_GetEmbeddedObjectArray_params[] =
{
    &TestClass_AllDMTFArrays_GetEmbeddedObjectArray_MIReturn_param,
    &TestClass_AllDMTFArrays_GetEmbeddedObjectArray_embeddedObjectArray_param,
};

/* method TestClass_AllDMTFArrays.GetEmbeddedObjectArray() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_GetEmbeddedObjectArray_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00677916, /* code */
    MI_T("GetEmbeddedObjectArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_GetEmbeddedObjectArray_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_GetEmbeddedObjectArray_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_GetEmbeddedObjectArray), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_GetEmbeddedObjectArray, /* method */
};

/* parameter TestClass_AllDMTFArrays.SetEmbeddedObjectArray(): embeddedObjectArray */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetEmbeddedObjectArray_embeddedObjectArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00657913, /* code */
    MI_T("embeddedObjectArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetEmbeddedObjectArray, embeddedObjectArray), /* offset */
};

/* parameter TestClass_AllDMTFArrays.SetEmbeddedObjectArray(): MIReturn */
static MI_CONST MI_ParameterDecl TestClass_AllDMTFArrays_SetEmbeddedObjectArray_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestClass_AllDMTFArrays_SetEmbeddedObjectArray, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_SetEmbeddedObjectArray_params[] =
{
    &TestClass_AllDMTFArrays_SetEmbeddedObjectArray_MIReturn_param,
    &TestClass_AllDMTFArrays_SetEmbeddedObjectArray_embeddedObjectArray_param,
};

/* method TestClass_AllDMTFArrays.SetEmbeddedObjectArray() */
MI_CONST MI_MethodDecl TestClass_AllDMTFArrays_SetEmbeddedObjectArray_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00737916, /* code */
    MI_T("SetEmbeddedObjectArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_SetEmbeddedObjectArray_params, /* parameters */
    MI_COUNT(TestClass_AllDMTFArrays_SetEmbeddedObjectArray_params), /* numParameters */
    sizeof(TestClass_AllDMTFArrays_SetEmbeddedObjectArray), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestClass_AllDMTFArrays"), /* origin */
    MI_T("TestClass_AllDMTFArrays"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestClass_AllDMTFArrays_Invoke_SetEmbeddedObjectArray, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST TestClass_AllDMTFArrays_meths[] =
{
    &TestClass_AllDMTFArrays_GetBooleanArray_rtti,
    &TestClass_AllDMTFArrays_SetBooleanArray_rtti,
    &TestClass_AllDMTFArrays_GetUint8Array_rtti,
    &TestClass_AllDMTFArrays_SetUint8Array_rtti,
    &TestClass_AllDMTFArrays_GetSint8Array_rtti,
    &TestClass_AllDMTFArrays_SetSint8Array_rtti,
    &TestClass_AllDMTFArrays_GetUint16Array_rtti,
    &TestClass_AllDMTFArrays_SetUint16Array_rtti,
    &TestClass_AllDMTFArrays_GetSint16Array_rtti,
    &TestClass_AllDMTFArrays_SetSint16Array_rtti,
    &TestClass_AllDMTFArrays_GetUint32Array_rtti,
    &TestClass_AllDMTFArrays_SetUint32Array_rtti,
    &TestClass_AllDMTFArrays_GetSint32Array_rtti,
    &TestClass_AllDMTFArrays_SetSint32Array_rtti,
    &TestClass_AllDMTFArrays_GetUint64Array_rtti,
    &TestClass_AllDMTFArrays_SetUint64Array_rtti,
    &TestClass_AllDMTFArrays_GetSint64Array_rtti,
    &TestClass_AllDMTFArrays_SetSint64Array_rtti,
    &TestClass_AllDMTFArrays_GetReal32Array_rtti,
    &TestClass_AllDMTFArrays_SetReal32Array_rtti,
    &TestClass_AllDMTFArrays_GetReal64Array_rtti,
    &TestClass_AllDMTFArrays_SetReal64Array_rtti,
    &TestClass_AllDMTFArrays_GetChar16Array_rtti,
    &TestClass_AllDMTFArrays_SetChar16Array_rtti,
    &TestClass_AllDMTFArrays_GetStringArray_rtti,
    &TestClass_AllDMTFArrays_SetStringArray_rtti,
    &TestClass_AllDMTFArrays_GetDateTimeArray_rtti,
    &TestClass_AllDMTFArrays_SetdatetimeArray_rtti,
    &TestClass_AllDMTFArrays_GetReferenceArray_rtti,
    &TestClass_AllDMTFArrays_SetReferenceArray_rtti,
    &TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_rtti,
    &TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_rtti,
    &TestClass_AllDMTFArrays_GetEmbeddedObjectArray_rtti,
    &TestClass_AllDMTFArrays_SetEmbeddedObjectArray_rtti,
};

static MI_CONST MI_ProviderFT TestClass_AllDMTFArrays_funcs =
{
  (MI_ProviderFT_Load)TestClass_AllDMTFArrays_Load,
  (MI_ProviderFT_Unload)TestClass_AllDMTFArrays_Unload,
  (MI_ProviderFT_GetInstance)TestClass_AllDMTFArrays_GetInstance,
  (MI_ProviderFT_EnumerateInstances)TestClass_AllDMTFArrays_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)TestClass_AllDMTFArrays_CreateInstance,
  (MI_ProviderFT_ModifyInstance)TestClass_AllDMTFArrays_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)TestClass_AllDMTFArrays_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class TestClass_AllDMTFArrays */
MI_CONST MI_ClassDecl TestClass_AllDMTFArrays_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00747317, /* code */
    MI_T("TestClass_AllDMTFArrays"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestClass_AllDMTFArrays_props, /* properties */
    MI_COUNT(TestClass_AllDMTFArrays_props), /* numProperties */
    sizeof(TestClass_AllDMTFArrays), /* size */
    MI_T("TestClass_PropertyValues"), /* superClass */
    &TestClass_PropertyValues_rtti, /* superClassDecl */
    TestClass_AllDMTFArrays_meths, /* methods */
    MI_COUNT(TestClass_AllDMTFArrays_meths), /* numMethods */
    &schemaDecl, /* schema */
    &TestClass_AllDMTFArrays_funcs, /* functions */
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
    &TestClass_AllDMTFArrays_rtti,
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

