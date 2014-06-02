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
#include "X_SmallNumber.h"
#include "X_HugeNumber.h"
#include "X_NumberWorld.h"
#include "X_HugeNumbers.h"
#include "X_OddSmallNumbers.h"
#include "X_EvenSmallNumbers.h"
#include "X_Halves.h"
#include "X_Profile.h"
#include "X_HugeNumberConformsToProfile.h"
#include "X_NumberWorldConformsToProfile.h"
#include "X_Number1000001.h"
#include "X_Cat.h"
#include "X_Dog.h"
#include "X_HTTPHeader.h"

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
** X_ManagedElement
**
**==============================================================================
*/

/* property X_ManagedElement.Description */
static MI_CONST MI_PropertyDecl X_ManagedElement_Description_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E0B, /* code */
    MI_T("Description"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_ManagedElement, Description), /* offset */
    MI_T("X_ManagedElement"), /* origin */
    MI_T("X_ManagedElement"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_ManagedElement_props[] =
{
    &X_ManagedElement_Description_prop,
};

/* class X_ManagedElement */
MI_CONST MI_ClassDecl X_ManagedElement_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00787410, /* code */
    MI_T("X_ManagedElement"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_ManagedElement_props, /* properties */
    MI_COUNT(X_ManagedElement_props), /* numProperties */
    sizeof(X_ManagedElement), /* size */
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
** X_Number
**
**==============================================================================
*/

/* property X_Number.Number */
static MI_CONST MI_PropertyDecl X_Number_Number_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E7206, /* code */
    MI_T("Number"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_Number, Number), /* offset */
    MI_T("X_Number"), /* origin */
    MI_T("X_Number"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_Number_props[] =
{
    &X_ManagedElement_Description_prop,
    &X_Number_Number_prop,
};

/* class X_Number */
MI_CONST MI_ClassDecl X_Number_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00787208, /* code */
    MI_T("X_Number"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_Number_props, /* properties */
    MI_COUNT(X_Number_props), /* numProperties */
    sizeof(X_Number), /* size */
    MI_T("X_ManagedElement"), /* superClass */
    &X_ManagedElement_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** X_SmallNumber
**
**==============================================================================
*/

/* property X_SmallNumber.SpelledNumber */
static MI_CONST MI_PropertyDecl X_SmallNumber_SpelledNumber_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073720D, /* code */
    MI_T("SpelledNumber"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SmallNumber, SpelledNumber), /* offset */
    MI_T("X_SmallNumber"), /* origin */
    MI_T("X_SmallNumber"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_SmallNumber_props[] =
{
    &X_ManagedElement_Description_prop,
    &X_Number_Number_prop,
    &X_SmallNumber_SpelledNumber_prop,
};

/* parameter X_SmallNumber.SpellNumber(): num */
static MI_CONST MI_ParameterDecl X_SmallNumber_SpellNumber_num_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x006E6D03, /* code */
    MI_T("num"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SmallNumber_SpellNumber, num), /* offset */
};

/* parameter X_SmallNumber.SpellNumber(): MIReturn */
static MI_CONST MI_ParameterDecl X_SmallNumber_SpellNumber_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SmallNumber_SpellNumber, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST X_SmallNumber_SpellNumber_params[] =
{
    &X_SmallNumber_SpellNumber_MIReturn_param,
    &X_SmallNumber_SpellNumber_num_param,
};

/* method X_SmallNumber.SpellNumber() */
MI_CONST MI_MethodDecl X_SmallNumber_SpellNumber_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0073720B, /* code */
    MI_T("SpellNumber"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_SmallNumber_SpellNumber_params, /* parameters */
    MI_COUNT(X_SmallNumber_SpellNumber_params), /* numParameters */
    sizeof(X_SmallNumber_SpellNumber), /* size */
    MI_STRING, /* returnType */
    MI_T("X_SmallNumber"), /* origin */
    MI_T("X_SmallNumber"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)X_SmallNumber_Invoke_SpellNumber, /* method */
};

/* parameter X_SmallNumber.GetFactors(): numbers */
static MI_CONST MI_ParameterDecl X_SmallNumber_GetFactors_numbers_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006E7307, /* code */
    MI_T("numbers"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SmallNumber_GetFactors, numbers), /* offset */
};

/* parameter X_SmallNumber.GetFactors(): spelled_numbers */
static MI_CONST MI_ParameterDecl X_SmallNumber_GetFactors_spelled_numbers_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0073730F, /* code */
    MI_T("spelled_numbers"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SmallNumber_GetFactors, spelled_numbers), /* offset */
};

/* parameter X_SmallNumber.GetFactors(): MIReturn */
static MI_CONST MI_ParameterDecl X_SmallNumber_GetFactors_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SmallNumber_GetFactors, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST X_SmallNumber_GetFactors_params[] =
{
    &X_SmallNumber_GetFactors_MIReturn_param,
    &X_SmallNumber_GetFactors_numbers_param,
    &X_SmallNumber_GetFactors_spelled_numbers_param,
};

/* method X_SmallNumber.GetFactors() */
MI_CONST MI_MethodDecl X_SmallNumber_GetFactors_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0067730A, /* code */
    MI_T("GetFactors"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_SmallNumber_GetFactors_params, /* parameters */
    MI_COUNT(X_SmallNumber_GetFactors_params), /* numParameters */
    sizeof(X_SmallNumber_GetFactors), /* size */
    MI_UINT32, /* returnType */
    MI_T("X_SmallNumber"), /* origin */
    MI_T("X_SmallNumber"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)X_SmallNumber_Invoke_GetFactors, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST X_SmallNumber_meths[] =
{
    &X_SmallNumber_SpellNumber_rtti,
    &X_SmallNumber_GetFactors_rtti,
};

static MI_CONST MI_ProviderFT X_SmallNumber_funcs =
{
  (MI_ProviderFT_Load)X_SmallNumber_Load,
  (MI_ProviderFT_Unload)X_SmallNumber_Unload,
  (MI_ProviderFT_GetInstance)X_SmallNumber_GetInstance,
  (MI_ProviderFT_EnumerateInstances)X_SmallNumber_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)X_SmallNumber_CreateInstance,
  (MI_ProviderFT_ModifyInstance)X_SmallNumber_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)X_SmallNumber_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class X_SmallNumber */
MI_CONST MI_ClassDecl X_SmallNumber_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078720D, /* code */
    MI_T("X_SmallNumber"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_SmallNumber_props, /* properties */
    MI_COUNT(X_SmallNumber_props), /* numProperties */
    sizeof(X_SmallNumber), /* size */
    MI_T("X_Number"), /* superClass */
    &X_Number_rtti, /* superClassDecl */
    X_SmallNumber_meths, /* methods */
    MI_COUNT(X_SmallNumber_meths), /* numMethods */
    &schemaDecl, /* schema */
    &X_SmallNumber_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** X_TestObject
**
**==============================================================================
*/

/* property X_TestObject.id */
static MI_CONST MI_PropertyDecl X_TestObject_id_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00696402, /* code */
    MI_T("id"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_TestObject, id), /* offset */
    MI_T("X_TestObject"), /* origin */
    MI_T("X_TestObject"), /* propagator */
    NULL,
};

/* property X_TestObject.str */
static MI_CONST MI_PropertyDecl X_TestObject_str_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737203, /* code */
    MI_T("str"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_TestObject, str), /* offset */
    MI_T("X_TestObject"), /* origin */
    MI_T("X_TestObject"), /* propagator */
    NULL,
};

/* property X_TestObject.operation */
static MI_CONST MI_PropertyDecl X_TestObject_operation_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6E09, /* code */
    MI_T("operation"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_TestObject, operation), /* offset */
    MI_T("X_TestObject"), /* origin */
    MI_T("X_TestObject"), /* propagator */
    NULL,
};

/* property X_TestObject.left_operand */
static MI_CONST MI_PropertyDecl X_TestObject_left_operand_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C640C, /* code */
    MI_T("left_operand"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_TestObject, left_operand), /* offset */
    MI_T("X_TestObject"), /* origin */
    MI_T("X_TestObject"), /* propagator */
    NULL,
};

/* property X_TestObject.right_operand */
static MI_CONST MI_PropertyDecl X_TestObject_right_operand_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072640D, /* code */
    MI_T("right_operand"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_TestObject, right_operand), /* offset */
    MI_T("X_TestObject"), /* origin */
    MI_T("X_TestObject"), /* propagator */
    NULL,
};

/* property X_TestObject.result */
static MI_CONST MI_PropertyDecl X_TestObject_result_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00727406, /* code */
    MI_T("result"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_TestObject, result), /* offset */
    MI_T("X_TestObject"), /* origin */
    MI_T("X_TestObject"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_TestObject_props[] =
{
    &X_TestObject_id_prop,
    &X_TestObject_str_prop,
    &X_TestObject_operation_prop,
    &X_TestObject_left_operand_prop,
    &X_TestObject_right_operand_prop,
    &X_TestObject_result_prop,
};

/* class X_TestObject */
MI_CONST MI_ClassDecl X_TestObject_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078740C, /* code */
    MI_T("X_TestObject"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_TestObject_props, /* properties */
    MI_COUNT(X_TestObject_props), /* numProperties */
    sizeof(X_TestObject), /* size */
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
** X_HugeNumber
**
**==============================================================================
*/

/* property X_HugeNumber.Magnitude */
static MI_CONST MI_PropertyDecl X_HugeNumber_Magnitude_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D6509, /* code */
    MI_T("Magnitude"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_HugeNumber, Magnitude), /* offset */
    MI_T("X_HugeNumber"), /* origin */
    MI_T("X_HugeNumber"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* X_HugeNumber_MagnitudeObj_EmbeddedInstance_qual_value = MI_T("X_SmallNumber");

static MI_CONST MI_Qualifier X_HugeNumber_MagnitudeObj_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &X_HugeNumber_MagnitudeObj_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST X_HugeNumber_MagnitudeObj_quals[] =
{
    &X_HugeNumber_MagnitudeObj_EmbeddedInstance_qual,
};

/* property X_HugeNumber.MagnitudeObj */
static MI_CONST MI_PropertyDecl X_HugeNumber_MagnitudeObj_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D6A0C, /* code */
    MI_T("MagnitudeObj"), /* name */
    X_HugeNumber_MagnitudeObj_quals, /* qualifiers */
    MI_COUNT(X_HugeNumber_MagnitudeObj_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("X_SmallNumber"), /* className */
    0, /* subscript */
    offsetof(X_HugeNumber, MagnitudeObj), /* offset */
    MI_T("X_HugeNumber"), /* origin */
    MI_T("X_HugeNumber"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* X_HugeNumber_Numbers123_EmbeddedInstance_qual_value = MI_T("X_SmallNumber");

static MI_CONST MI_Qualifier X_HugeNumber_Numbers123_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &X_HugeNumber_Numbers123_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST X_HugeNumber_Numbers123_quals[] =
{
    &X_HugeNumber_Numbers123_EmbeddedInstance_qual,
};

/* property X_HugeNumber.Numbers123 */
static MI_CONST MI_PropertyDecl X_HugeNumber_Numbers123_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E330A, /* code */
    MI_T("Numbers123"), /* name */
    X_HugeNumber_Numbers123_quals, /* qualifiers */
    MI_COUNT(X_HugeNumber_Numbers123_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("X_SmallNumber"), /* className */
    0, /* subscript */
    offsetof(X_HugeNumber, Numbers123), /* offset */
    MI_T("X_HugeNumber"), /* origin */
    MI_T("X_HugeNumber"), /* propagator */
    NULL,
};

/* property X_HugeNumber.Number0 */
static MI_CONST MI_PropertyDecl X_HugeNumber_Number0_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E3007, /* code */
    MI_T("Number0"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_HugeNumber, Number0), /* offset */
    MI_T("X_HugeNumber"), /* origin */
    MI_T("X_HugeNumber"), /* propagator */
    NULL,
};

/* property X_HugeNumber.TwoTestObjects */
static MI_CONST MI_PropertyDecl X_HugeNumber_TwoTestObjects_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0074730E, /* code */
    MI_T("TwoTestObjects"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_HugeNumber, TwoTestObjects), /* offset */
    MI_T("X_HugeNumber"), /* origin */
    MI_T("X_HugeNumber"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* X_HugeNumber_TestObject_EmbeddedInstance_qual_value = MI_T("X_TestObject");

static MI_CONST MI_Qualifier X_HugeNumber_TestObject_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &X_HugeNumber_TestObject_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST X_HugeNumber_TestObject_quals[] =
{
    &X_HugeNumber_TestObject_EmbeddedInstance_qual,
};

/* property X_HugeNumber.TestObject */
static MI_CONST MI_PropertyDecl X_HugeNumber_TestObject_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0074740A, /* code */
    MI_T("TestObject"), /* name */
    X_HugeNumber_TestObject_quals, /* qualifiers */
    MI_COUNT(X_HugeNumber_TestObject_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("X_TestObject"), /* className */
    0, /* subscript */
    offsetof(X_HugeNumber, TestObject), /* offset */
    MI_T("X_HugeNumber"), /* origin */
    MI_T("X_HugeNumber"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_HugeNumber_props[] =
{
    &X_ManagedElement_Description_prop,
    &X_Number_Number_prop,
    &X_HugeNumber_Magnitude_prop,
    &X_HugeNumber_MagnitudeObj_prop,
    &X_HugeNumber_Numbers123_prop,
    &X_HugeNumber_Number0_prop,
    &X_HugeNumber_TwoTestObjects_prop,
    &X_HugeNumber_TestObject_prop,
};

/* parameter X_HugeNumber.SpellMagnitude(): MIReturn */
static MI_CONST MI_ParameterDecl X_HugeNumber_SpellMagnitude_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_HugeNumber_SpellMagnitude, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST X_HugeNumber_SpellMagnitude_params[] =
{
    &X_HugeNumber_SpellMagnitude_MIReturn_param,
};

/* method X_HugeNumber.SpellMagnitude() */
MI_CONST MI_MethodDecl X_HugeNumber_SpellMagnitude_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650E, /* code */
    MI_T("SpellMagnitude"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_HugeNumber_SpellMagnitude_params, /* parameters */
    MI_COUNT(X_HugeNumber_SpellMagnitude_params), /* numParameters */
    sizeof(X_HugeNumber_SpellMagnitude), /* size */
    MI_STRING, /* returnType */
    MI_T("X_HugeNumber"), /* origin */
    MI_T("X_HugeNumber"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)X_HugeNumber_Invoke_SpellMagnitude, /* method */
};

static MI_CONST MI_Char* X_HugeNumber_TestEmbedded_EmbeddedInstance_qual_value = MI_T("X_TestObject");

static MI_CONST MI_Qualifier X_HugeNumber_TestEmbedded_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &X_HugeNumber_TestEmbedded_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST X_HugeNumber_TestEmbedded_quals[] =
{
    &X_HugeNumber_TestEmbedded_EmbeddedInstance_qual,
};

/* parameter X_HugeNumber.TestEmbedded(): objectsArray */
static MI_CONST MI_ParameterDecl X_HugeNumber_TestEmbedded_objectsArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x006F790C, /* code */
    MI_T("objectsArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_HugeNumber_TestEmbedded, objectsArray), /* offset */
};

/* parameter X_HugeNumber.TestEmbedded(): objectSingle */
static MI_CONST MI_ParameterDecl X_HugeNumber_TestEmbedded_objectSingle_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x006F650C, /* code */
    MI_T("objectSingle"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_HugeNumber_TestEmbedded, objectSingle), /* offset */
};

static MI_CONST MI_Char* X_HugeNumber_TestEmbedded_testObjectsArray_EmbeddedInstance_qual_value = MI_T("X_TestObject");

static MI_CONST MI_Qualifier X_HugeNumber_TestEmbedded_testObjectsArray_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &X_HugeNumber_TestEmbedded_testObjectsArray_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST X_HugeNumber_TestEmbedded_testObjectsArray_quals[] =
{
    &X_HugeNumber_TestEmbedded_testObjectsArray_EmbeddedInstance_qual,
};

/* parameter X_HugeNumber.TestEmbedded(): testObjectsArray */
static MI_CONST MI_ParameterDecl X_HugeNumber_TestEmbedded_testObjectsArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00747910, /* code */
    MI_T("testObjectsArray"), /* name */
    X_HugeNumber_TestEmbedded_testObjectsArray_quals, /* qualifiers */
    MI_COUNT(X_HugeNumber_TestEmbedded_testObjectsArray_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("X_TestObject"), /* className */
    0, /* subscript */
    offsetof(X_HugeNumber_TestEmbedded, testObjectsArray), /* offset */
};

static MI_CONST MI_Char* X_HugeNumber_TestEmbedded_testObjectSingle_EmbeddedInstance_qual_value = MI_T("X_TestObject");

static MI_CONST MI_Qualifier X_HugeNumber_TestEmbedded_testObjectSingle_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &X_HugeNumber_TestEmbedded_testObjectSingle_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST X_HugeNumber_TestEmbedded_testObjectSingle_quals[] =
{
    &X_HugeNumber_TestEmbedded_testObjectSingle_EmbeddedInstance_qual,
};

/* parameter X_HugeNumber.TestEmbedded(): testObjectSingle */
static MI_CONST MI_ParameterDecl X_HugeNumber_TestEmbedded_testObjectSingle_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00746510, /* code */
    MI_T("testObjectSingle"), /* name */
    X_HugeNumber_TestEmbedded_testObjectSingle_quals, /* qualifiers */
    MI_COUNT(X_HugeNumber_TestEmbedded_testObjectSingle_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("X_TestObject"), /* className */
    0, /* subscript */
    offsetof(X_HugeNumber_TestEmbedded, testObjectSingle), /* offset */
};

static MI_CONST MI_Char* X_HugeNumber_TestEmbedded_MIReturn_EmbeddedInstance_qual_value = MI_T("X_TestObject");

static MI_CONST MI_Qualifier X_HugeNumber_TestEmbedded_MIReturn_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &X_HugeNumber_TestEmbedded_MIReturn_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST X_HugeNumber_TestEmbedded_MIReturn_quals[] =
{
    &X_HugeNumber_TestEmbedded_MIReturn_EmbeddedInstance_qual,
};

/* parameter X_HugeNumber.TestEmbedded(): MIReturn */
static MI_CONST MI_ParameterDecl X_HugeNumber_TestEmbedded_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    X_HugeNumber_TestEmbedded_MIReturn_quals, /* qualifiers */
    MI_COUNT(X_HugeNumber_TestEmbedded_MIReturn_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("X_TestObject"), /* className */
    0, /* subscript */
    offsetof(X_HugeNumber_TestEmbedded, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST X_HugeNumber_TestEmbedded_params[] =
{
    &X_HugeNumber_TestEmbedded_MIReturn_param,
    &X_HugeNumber_TestEmbedded_objectsArray_param,
    &X_HugeNumber_TestEmbedded_objectSingle_param,
    &X_HugeNumber_TestEmbedded_testObjectsArray_param,
    &X_HugeNumber_TestEmbedded_testObjectSingle_param,
};

/* method X_HugeNumber.TestEmbedded() */
MI_CONST MI_MethodDecl X_HugeNumber_TestEmbedded_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0074640C, /* code */
    MI_T("TestEmbedded"), /* name */
    X_HugeNumber_TestEmbedded_quals, /* qualifiers */
    MI_COUNT(X_HugeNumber_TestEmbedded_quals), /* numQualifiers */
    X_HugeNumber_TestEmbedded_params, /* parameters */
    MI_COUNT(X_HugeNumber_TestEmbedded_params), /* numParameters */
    sizeof(X_HugeNumber_TestEmbedded), /* size */
    MI_INSTANCE, /* returnType */
    MI_T("X_HugeNumber"), /* origin */
    MI_T("X_HugeNumber"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)X_HugeNumber_Invoke_TestEmbedded, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST X_HugeNumber_meths[] =
{
    &X_HugeNumber_SpellMagnitude_rtti,
    &X_HugeNumber_TestEmbedded_rtti,
};

static MI_CONST MI_ProviderFT X_HugeNumber_funcs =
{
  (MI_ProviderFT_Load)X_HugeNumber_Load,
  (MI_ProviderFT_Unload)X_HugeNumber_Unload,
  (MI_ProviderFT_GetInstance)X_HugeNumber_GetInstance,
  (MI_ProviderFT_EnumerateInstances)X_HugeNumber_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)X_HugeNumber_CreateInstance,
  (MI_ProviderFT_ModifyInstance)X_HugeNumber_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)X_HugeNumber_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class X_HugeNumber */
MI_CONST MI_ClassDecl X_HugeNumber_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078720C, /* code */
    MI_T("X_HugeNumber"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_HugeNumber_props, /* properties */
    MI_COUNT(X_HugeNumber_props), /* numProperties */
    sizeof(X_HugeNumber), /* size */
    MI_T("X_Number"), /* superClass */
    &X_Number_rtti, /* superClassDecl */
    X_HugeNumber_meths, /* methods */
    MI_COUNT(X_HugeNumber_meths), /* numMethods */
    &schemaDecl, /* schema */
    &X_HugeNumber_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** X_NumberWorld
**
**==============================================================================
*/

/* property X_NumberWorld.Name */
static MI_CONST MI_PropertyDecl X_NumberWorld_Name_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_NumberWorld, Name), /* offset */
    MI_T("X_NumberWorld"), /* origin */
    MI_T("X_NumberWorld"), /* propagator */
    NULL,
};

/* property X_NumberWorld.Version */
static MI_CONST MI_PropertyDecl X_NumberWorld_Version_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00766E07, /* code */
    MI_T("Version"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_NumberWorld, Version), /* offset */
    MI_T("X_NumberWorld"), /* origin */
    MI_T("X_NumberWorld"), /* propagator */
    NULL,
};

/* property X_NumberWorld.pid */
static MI_CONST MI_PropertyDecl X_NumberWorld_pid_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706403, /* code */
    MI_T("pid"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_NumberWorld, pid), /* offset */
    MI_T("X_NumberWorld"), /* origin */
    MI_T("X_NumberWorld"), /* propagator */
    NULL,
};

/* property X_NumberWorld.uid */
static MI_CONST MI_PropertyDecl X_NumberWorld_uid_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756403, /* code */
    MI_T("uid"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_NumberWorld, uid), /* offset */
    MI_T("X_NumberWorld"), /* origin */
    MI_T("X_NumberWorld"), /* propagator */
    NULL,
};

/* property X_NumberWorld.gid */
static MI_CONST MI_PropertyDecl X_NumberWorld_gid_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00676403, /* code */
    MI_T("gid"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_NumberWorld, gid), /* offset */
    MI_T("X_NumberWorld"), /* origin */
    MI_T("X_NumberWorld"), /* propagator */
    NULL,
};

/* property X_NumberWorld.user */
static MI_CONST MI_PropertyDecl X_NumberWorld_user_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00757204, /* code */
    MI_T("user"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_NumberWorld, user), /* offset */
    MI_T("X_NumberWorld"), /* origin */
    MI_T("X_NumberWorld"), /* propagator */
    NULL,
};

/* property X_NumberWorld.group */
static MI_CONST MI_PropertyDecl X_NumberWorld_group_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00677005, /* code */
    MI_T("group"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_NumberWorld, group), /* offset */
    MI_T("X_NumberWorld"), /* origin */
    MI_T("X_NumberWorld"), /* propagator */
    NULL,
};

/* property X_NumberWorld.ns */
static MI_CONST MI_PropertyDecl X_NumberWorld_ns_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E7302, /* code */
    MI_T("ns"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_NumberWorld, ns), /* offset */
    MI_T("X_NumberWorld"), /* origin */
    MI_T("X_NumberWorld"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_NumberWorld_props[] =
{
    &X_ManagedElement_Description_prop,
    &X_NumberWorld_Name_prop,
    &X_NumberWorld_Version_prop,
    &X_NumberWorld_pid_prop,
    &X_NumberWorld_uid_prop,
    &X_NumberWorld_gid_prop,
    &X_NumberWorld_user_prop,
    &X_NumberWorld_group_prop,
    &X_NumberWorld_ns_prop,
};

/* parameter X_NumberWorld.Terminate(): MIReturn */
static MI_CONST MI_ParameterDecl X_NumberWorld_Terminate_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_NumberWorld_Terminate, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST X_NumberWorld_Terminate_params[] =
{
    &X_NumberWorld_Terminate_MIReturn_param,
};

/* method X_NumberWorld.Terminate() */
MI_CONST MI_MethodDecl X_NumberWorld_Terminate_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00746509, /* code */
    MI_T("Terminate"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_NumberWorld_Terminate_params, /* parameters */
    MI_COUNT(X_NumberWorld_Terminate_params), /* numParameters */
    sizeof(X_NumberWorld_Terminate), /* size */
    MI_UINT32, /* returnType */
    MI_T("X_NumberWorld"), /* origin */
    MI_T("X_NumberWorld"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)X_NumberWorld_Invoke_Terminate, /* method */
};

/* parameter X_NumberWorld.ReturnNamespace(): MIReturn */
static MI_CONST MI_ParameterDecl X_NumberWorld_ReturnNamespace_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_NumberWorld_ReturnNamespace, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST X_NumberWorld_ReturnNamespace_params[] =
{
    &X_NumberWorld_ReturnNamespace_MIReturn_param,
};

/* method X_NumberWorld.ReturnNamespace() */
MI_CONST MI_MethodDecl X_NumberWorld_ReturnNamespace_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0072650F, /* code */
    MI_T("ReturnNamespace"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_NumberWorld_ReturnNamespace_params, /* parameters */
    MI_COUNT(X_NumberWorld_ReturnNamespace_params), /* numParameters */
    sizeof(X_NumberWorld_ReturnNamespace), /* size */
    MI_STRING, /* returnType */
    MI_T("X_NumberWorld"), /* origin */
    MI_T("X_NumberWorld"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)X_NumberWorld_Invoke_ReturnNamespace, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST X_NumberWorld_meths[] =
{
    &X_NumberWorld_Terminate_rtti,
    &X_NumberWorld_ReturnNamespace_rtti,
};

static MI_CONST MI_ProviderFT X_NumberWorld_funcs =
{
  (MI_ProviderFT_Load)X_NumberWorld_Load,
  (MI_ProviderFT_Unload)X_NumberWorld_Unload,
  (MI_ProviderFT_GetInstance)X_NumberWorld_GetInstance,
  (MI_ProviderFT_EnumerateInstances)X_NumberWorld_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)X_NumberWorld_CreateInstance,
  (MI_ProviderFT_ModifyInstance)X_NumberWorld_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)X_NumberWorld_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class X_NumberWorld */
MI_CONST MI_ClassDecl X_NumberWorld_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078640D, /* code */
    MI_T("X_NumberWorld"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_NumberWorld_props, /* properties */
    MI_COUNT(X_NumberWorld_props), /* numProperties */
    sizeof(X_NumberWorld), /* size */
    MI_T("X_ManagedElement"), /* superClass */
    &X_ManagedElement_rtti, /* superClassDecl */
    X_NumberWorld_meths, /* methods */
    MI_COUNT(X_NumberWorld_meths), /* numMethods */
    &schemaDecl, /* schema */
    &X_NumberWorld_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** X_AllNumbers
**
**==============================================================================
*/

/* property X_AllNumbers.number */
static MI_CONST MI_PropertyDecl X_AllNumbers_number_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E7206, /* code */
    MI_T("number"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("X_Number"), /* className */
    0, /* subscript */
    offsetof(X_AllNumbers, number), /* offset */
    MI_T("X_AllNumbers"), /* origin */
    MI_T("X_AllNumbers"), /* propagator */
    NULL,
};

/* property X_AllNumbers.world */
static MI_CONST MI_PropertyDecl X_AllNumbers_world_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00776405, /* code */
    MI_T("world"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("X_NumberWorld"), /* className */
    0, /* subscript */
    offsetof(X_AllNumbers, world), /* offset */
    MI_T("X_AllNumbers"), /* origin */
    MI_T("X_AllNumbers"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_AllNumbers_props[] =
{
    &X_AllNumbers_number_prop,
    &X_AllNumbers_world_prop,
};

/* class X_AllNumbers */
MI_CONST MI_ClassDecl X_AllNumbers_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x0078730C, /* code */
    MI_T("X_AllNumbers"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_AllNumbers_props, /* properties */
    MI_COUNT(X_AllNumbers_props), /* numProperties */
    sizeof(X_AllNumbers), /* size */
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
** X_HugeNumbers
**
**==============================================================================
*/

/* property X_HugeNumbers.number */
static MI_CONST MI_PropertyDecl X_HugeNumbers_number_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E7206, /* code */
    MI_T("number"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("X_HugeNumber"), /* className */
    0, /* subscript */
    offsetof(X_HugeNumbers, number), /* offset */
    MI_T("X_AllNumbers"), /* origin */
    MI_T("X_HugeNumbers"), /* propagator */
    NULL,
};

/* property X_HugeNumbers.world */
static MI_CONST MI_PropertyDecl X_HugeNumbers_world_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00776405, /* code */
    MI_T("world"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("X_NumberWorld"), /* className */
    0, /* subscript */
    offsetof(X_HugeNumbers, world), /* offset */
    MI_T("X_AllNumbers"), /* origin */
    MI_T("X_HugeNumbers"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_HugeNumbers_props[] =
{
    &X_HugeNumbers_number_prop,
    &X_HugeNumbers_world_prop,
};

static MI_CONST MI_ProviderFT X_HugeNumbers_funcs =
{
  (MI_ProviderFT_Load)X_HugeNumbers_Load,
  (MI_ProviderFT_Unload)X_HugeNumbers_Unload,
  (MI_ProviderFT_GetInstance)X_HugeNumbers_GetInstance,
  (MI_ProviderFT_EnumerateInstances)X_HugeNumbers_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)X_HugeNumbers_CreateInstance,
  (MI_ProviderFT_ModifyInstance)X_HugeNumbers_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)X_HugeNumbers_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)X_HugeNumbers_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)X_HugeNumbers_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class X_HugeNumbers */
MI_CONST MI_ClassDecl X_HugeNumbers_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x0078730D, /* code */
    MI_T("X_HugeNumbers"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_HugeNumbers_props, /* properties */
    MI_COUNT(X_HugeNumbers_props), /* numProperties */
    sizeof(X_HugeNumbers), /* size */
    MI_T("X_AllNumbers"), /* superClass */
    &X_AllNumbers_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &X_HugeNumbers_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** X_OddSmallNumbers
**
**==============================================================================
*/

/* property X_OddSmallNumbers.number */
static MI_CONST MI_PropertyDecl X_OddSmallNumbers_number_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E7206, /* code */
    MI_T("number"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("X_SmallNumber"), /* className */
    0, /* subscript */
    offsetof(X_OddSmallNumbers, number), /* offset */
    MI_T("X_AllNumbers"), /* origin */
    MI_T("X_OddSmallNumbers"), /* propagator */
    NULL,
};

/* property X_OddSmallNumbers.world */
static MI_CONST MI_PropertyDecl X_OddSmallNumbers_world_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00776405, /* code */
    MI_T("world"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("X_NumberWorld"), /* className */
    0, /* subscript */
    offsetof(X_OddSmallNumbers, world), /* offset */
    MI_T("X_AllNumbers"), /* origin */
    MI_T("X_OddSmallNumbers"), /* propagator */
    NULL,
};

/* property X_OddSmallNumbers.factors */
static MI_CONST MI_PropertyDecl X_OddSmallNumbers_factors_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00667307, /* code */
    MI_T("factors"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_OddSmallNumbers, factors), /* offset */
    MI_T("X_OddSmallNumbers"), /* origin */
    MI_T("X_OddSmallNumbers"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_OddSmallNumbers_props[] =
{
    &X_OddSmallNumbers_number_prop,
    &X_OddSmallNumbers_world_prop,
    &X_OddSmallNumbers_factors_prop,
};

static MI_CONST MI_ProviderFT X_OddSmallNumbers_funcs =
{
  (MI_ProviderFT_Load)X_OddSmallNumbers_Load,
  (MI_ProviderFT_Unload)X_OddSmallNumbers_Unload,
  (MI_ProviderFT_GetInstance)X_OddSmallNumbers_GetInstance,
  (MI_ProviderFT_EnumerateInstances)X_OddSmallNumbers_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)X_OddSmallNumbers_CreateInstance,
  (MI_ProviderFT_ModifyInstance)X_OddSmallNumbers_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)X_OddSmallNumbers_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)X_OddSmallNumbers_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)X_OddSmallNumbers_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class X_OddSmallNumbers */
MI_CONST MI_ClassDecl X_OddSmallNumbers_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00787311, /* code */
    MI_T("X_OddSmallNumbers"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_OddSmallNumbers_props, /* properties */
    MI_COUNT(X_OddSmallNumbers_props), /* numProperties */
    sizeof(X_OddSmallNumbers), /* size */
    MI_T("X_AllNumbers"), /* superClass */
    &X_AllNumbers_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &X_OddSmallNumbers_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** X_EvenSmallNumbers
**
**==============================================================================
*/

/* property X_EvenSmallNumbers.number */
static MI_CONST MI_PropertyDecl X_EvenSmallNumbers_number_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E7206, /* code */
    MI_T("number"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("X_SmallNumber"), /* className */
    0, /* subscript */
    offsetof(X_EvenSmallNumbers, number), /* offset */
    MI_T("X_AllNumbers"), /* origin */
    MI_T("X_EvenSmallNumbers"), /* propagator */
    NULL,
};

/* property X_EvenSmallNumbers.world */
static MI_CONST MI_PropertyDecl X_EvenSmallNumbers_world_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00776405, /* code */
    MI_T("world"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("X_NumberWorld"), /* className */
    0, /* subscript */
    offsetof(X_EvenSmallNumbers, world), /* offset */
    MI_T("X_AllNumbers"), /* origin */
    MI_T("X_EvenSmallNumbers"), /* propagator */
    NULL,
};

/* property X_EvenSmallNumbers.factors */
static MI_CONST MI_PropertyDecl X_EvenSmallNumbers_factors_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00667307, /* code */
    MI_T("factors"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_EvenSmallNumbers, factors), /* offset */
    MI_T("X_EvenSmallNumbers"), /* origin */
    MI_T("X_EvenSmallNumbers"), /* propagator */
    NULL,
};

/* property X_EvenSmallNumbers.prime */
static MI_CONST MI_PropertyDecl X_EvenSmallNumbers_prime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706505, /* code */
    MI_T("prime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_EvenSmallNumbers, prime), /* offset */
    MI_T("X_EvenSmallNumbers"), /* origin */
    MI_T("X_EvenSmallNumbers"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_EvenSmallNumbers_props[] =
{
    &X_EvenSmallNumbers_number_prop,
    &X_EvenSmallNumbers_world_prop,
    &X_EvenSmallNumbers_factors_prop,
    &X_EvenSmallNumbers_prime_prop,
};

static MI_CONST MI_ProviderFT X_EvenSmallNumbers_funcs =
{
  (MI_ProviderFT_Load)X_EvenSmallNumbers_Load,
  (MI_ProviderFT_Unload)X_EvenSmallNumbers_Unload,
  (MI_ProviderFT_GetInstance)X_EvenSmallNumbers_GetInstance,
  (MI_ProviderFT_EnumerateInstances)X_EvenSmallNumbers_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)X_EvenSmallNumbers_CreateInstance,
  (MI_ProviderFT_ModifyInstance)X_EvenSmallNumbers_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)X_EvenSmallNumbers_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)X_EvenSmallNumbers_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)X_EvenSmallNumbers_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class X_EvenSmallNumbers */
MI_CONST MI_ClassDecl X_EvenSmallNumbers_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00787312, /* code */
    MI_T("X_EvenSmallNumbers"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_EvenSmallNumbers_props, /* properties */
    MI_COUNT(X_EvenSmallNumbers_props), /* numProperties */
    sizeof(X_EvenSmallNumbers), /* size */
    MI_T("X_AllNumbers"), /* superClass */
    &X_AllNumbers_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &X_EvenSmallNumbers_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** X_Halves
**
**==============================================================================
*/

/* property X_Halves.number */
static MI_CONST MI_PropertyDecl X_Halves_number_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E7206, /* code */
    MI_T("number"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("X_SmallNumber"), /* className */
    0, /* subscript */
    offsetof(X_Halves, number), /* offset */
    MI_T("X_Halves"), /* origin */
    MI_T("X_Halves"), /* propagator */
    NULL,
};

/* property X_Halves.half */
static MI_CONST MI_PropertyDecl X_Halves_half_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00686604, /* code */
    MI_T("half"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("X_SmallNumber"), /* className */
    0, /* subscript */
    offsetof(X_Halves, half), /* offset */
    MI_T("X_Halves"), /* origin */
    MI_T("X_Halves"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_Halves_props[] =
{
    &X_Halves_number_prop,
    &X_Halves_half_prop,
};

static MI_CONST MI_ProviderFT X_Halves_funcs =
{
  (MI_ProviderFT_Load)X_Halves_Load,
  (MI_ProviderFT_Unload)X_Halves_Unload,
  (MI_ProviderFT_GetInstance)X_Halves_GetInstance,
  (MI_ProviderFT_EnumerateInstances)X_Halves_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)X_Halves_CreateInstance,
  (MI_ProviderFT_ModifyInstance)X_Halves_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)X_Halves_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)X_Halves_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)X_Halves_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class X_Halves */
MI_CONST MI_ClassDecl X_Halves_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00787308, /* code */
    MI_T("X_Halves"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_Halves_props, /* properties */
    MI_COUNT(X_Halves_props), /* numProperties */
    sizeof(X_Halves), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &X_Halves_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** X_Profile
**
**==============================================================================
*/

/* property X_Profile.InstanceID */
static MI_CONST MI_PropertyDecl X_Profile_InstanceID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0069640A, /* code */
    MI_T("InstanceID"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_Profile, InstanceID), /* offset */
    MI_T("X_Profile"), /* origin */
    MI_T("X_Profile"), /* propagator */
    NULL,
};

/* property X_Profile.RegisteredName */
static MI_CONST MI_PropertyDecl X_Profile_RegisteredName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072650E, /* code */
    MI_T("RegisteredName"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_Profile, RegisteredName), /* offset */
    MI_T("X_Profile"), /* origin */
    MI_T("X_Profile"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_Profile_props[] =
{
    &X_Profile_InstanceID_prop,
    &X_Profile_RegisteredName_prop,
};

static MI_CONST MI_ProviderFT X_Profile_funcs =
{
  (MI_ProviderFT_Load)X_Profile_Load,
  (MI_ProviderFT_Unload)X_Profile_Unload,
  (MI_ProviderFT_GetInstance)X_Profile_GetInstance,
  (MI_ProviderFT_EnumerateInstances)X_Profile_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)X_Profile_CreateInstance,
  (MI_ProviderFT_ModifyInstance)X_Profile_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)X_Profile_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class X_Profile */
MI_CONST MI_ClassDecl X_Profile_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00786509, /* code */
    MI_T("X_Profile"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_Profile_props, /* properties */
    MI_COUNT(X_Profile_props), /* numProperties */
    sizeof(X_Profile), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &X_Profile_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** X_ElementConformsToProfile
**
**==============================================================================
*/

/* property X_ElementConformsToProfile.Profile */
static MI_CONST MI_PropertyDecl X_ElementConformsToProfile_Profile_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00706507, /* code */
    MI_T("Profile"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("X_Profile"), /* className */
    0, /* subscript */
    offsetof(X_ElementConformsToProfile, Profile), /* offset */
    MI_T("X_ElementConformsToProfile"), /* origin */
    MI_T("X_ElementConformsToProfile"), /* propagator */
    NULL,
};

/* property X_ElementConformsToProfile.Element */
static MI_CONST MI_PropertyDecl X_ElementConformsToProfile_Element_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00657407, /* code */
    MI_T("Element"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("X_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(X_ElementConformsToProfile, Element), /* offset */
    MI_T("X_ElementConformsToProfile"), /* origin */
    MI_T("X_ElementConformsToProfile"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_ElementConformsToProfile_props[] =
{
    &X_ElementConformsToProfile_Profile_prop,
    &X_ElementConformsToProfile_Element_prop,
};

/* class X_ElementConformsToProfile */
MI_CONST MI_ClassDecl X_ElementConformsToProfile_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x0078651A, /* code */
    MI_T("X_ElementConformsToProfile"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_ElementConformsToProfile_props, /* properties */
    MI_COUNT(X_ElementConformsToProfile_props), /* numProperties */
    sizeof(X_ElementConformsToProfile), /* size */
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
** X_HugeNumberConformsToProfile
**
**==============================================================================
*/

/* property X_HugeNumberConformsToProfile.Profile */
static MI_CONST MI_PropertyDecl X_HugeNumberConformsToProfile_Profile_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00706507, /* code */
    MI_T("Profile"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("X_Profile"), /* className */
    0, /* subscript */
    offsetof(X_HugeNumberConformsToProfile, Profile), /* offset */
    MI_T("X_ElementConformsToProfile"), /* origin */
    MI_T("X_HugeNumberConformsToProfile"), /* propagator */
    NULL,
};

/* property X_HugeNumberConformsToProfile.Element */
static MI_CONST MI_PropertyDecl X_HugeNumberConformsToProfile_Element_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00657407, /* code */
    MI_T("Element"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("X_HugeNumber"), /* className */
    0, /* subscript */
    offsetof(X_HugeNumberConformsToProfile, Element), /* offset */
    MI_T("X_ElementConformsToProfile"), /* origin */
    MI_T("X_HugeNumberConformsToProfile"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_HugeNumberConformsToProfile_props[] =
{
    &X_HugeNumberConformsToProfile_Profile_prop,
    &X_HugeNumberConformsToProfile_Element_prop,
};

static MI_CONST MI_ProviderFT X_HugeNumberConformsToProfile_funcs =
{
  (MI_ProviderFT_Load)X_HugeNumberConformsToProfile_Load,
  (MI_ProviderFT_Unload)X_HugeNumberConformsToProfile_Unload,
  (MI_ProviderFT_GetInstance)X_HugeNumberConformsToProfile_GetInstance,
  (MI_ProviderFT_EnumerateInstances)X_HugeNumberConformsToProfile_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)X_HugeNumberConformsToProfile_CreateInstance,
  (MI_ProviderFT_ModifyInstance)X_HugeNumberConformsToProfile_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)X_HugeNumberConformsToProfile_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)X_HugeNumberConformsToProfile_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)X_HugeNumberConformsToProfile_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class X_HugeNumberConformsToProfile */
MI_CONST MI_ClassDecl X_HugeNumberConformsToProfile_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x0078651D, /* code */
    MI_T("X_HugeNumberConformsToProfile"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_HugeNumberConformsToProfile_props, /* properties */
    MI_COUNT(X_HugeNumberConformsToProfile_props), /* numProperties */
    sizeof(X_HugeNumberConformsToProfile), /* size */
    MI_T("X_ElementConformsToProfile"), /* superClass */
    &X_ElementConformsToProfile_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &X_HugeNumberConformsToProfile_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** X_NumberWorldConformsToProfile
**
**==============================================================================
*/

/* property X_NumberWorldConformsToProfile.Profile */
static MI_CONST MI_PropertyDecl X_NumberWorldConformsToProfile_Profile_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00706507, /* code */
    MI_T("Profile"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("X_Profile"), /* className */
    0, /* subscript */
    offsetof(X_NumberWorldConformsToProfile, Profile), /* offset */
    MI_T("X_ElementConformsToProfile"), /* origin */
    MI_T("X_NumberWorldConformsToProfile"), /* propagator */
    NULL,
};

/* property X_NumberWorldConformsToProfile.Element */
static MI_CONST MI_PropertyDecl X_NumberWorldConformsToProfile_Element_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00657407, /* code */
    MI_T("Element"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("X_NumberWorld"), /* className */
    0, /* subscript */
    offsetof(X_NumberWorldConformsToProfile, Element), /* offset */
    MI_T("X_ElementConformsToProfile"), /* origin */
    MI_T("X_NumberWorldConformsToProfile"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_NumberWorldConformsToProfile_props[] =
{
    &X_NumberWorldConformsToProfile_Profile_prop,
    &X_NumberWorldConformsToProfile_Element_prop,
};

static MI_CONST MI_ProviderFT X_NumberWorldConformsToProfile_funcs =
{
  (MI_ProviderFT_Load)X_NumberWorldConformsToProfile_Load,
  (MI_ProviderFT_Unload)X_NumberWorldConformsToProfile_Unload,
  (MI_ProviderFT_GetInstance)X_NumberWorldConformsToProfile_GetInstance,
  (MI_ProviderFT_EnumerateInstances)X_NumberWorldConformsToProfile_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)X_NumberWorldConformsToProfile_CreateInstance,
  (MI_ProviderFT_ModifyInstance)X_NumberWorldConformsToProfile_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)X_NumberWorldConformsToProfile_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)X_NumberWorldConformsToProfile_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)X_NumberWorldConformsToProfile_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class X_NumberWorldConformsToProfile */
MI_CONST MI_ClassDecl X_NumberWorldConformsToProfile_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x0078651E, /* code */
    MI_T("X_NumberWorldConformsToProfile"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_NumberWorldConformsToProfile_props, /* properties */
    MI_COUNT(X_NumberWorldConformsToProfile_props), /* numProperties */
    sizeof(X_NumberWorldConformsToProfile), /* size */
    MI_T("X_ElementConformsToProfile"), /* superClass */
    &X_ElementConformsToProfile_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &X_NumberWorldConformsToProfile_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** X_Number1000001
**
**==============================================================================
*/

/* property X_Number1000001.Property0 */
static MI_CONST MI_PropertyDecl X_Number1000001_Property0_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00703009, /* code */
    MI_T("Property0"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_Number1000001, Property0), /* offset */
    MI_T("X_Number1000001"), /* origin */
    MI_T("X_Number1000001"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_Number1000001_props[] =
{
    &X_ManagedElement_Description_prop,
    &X_Number_Number_prop,
    &X_HugeNumber_Magnitude_prop,
    &X_HugeNumber_MagnitudeObj_prop,
    &X_HugeNumber_Numbers123_prop,
    &X_HugeNumber_Number0_prop,
    &X_HugeNumber_TwoTestObjects_prop,
    &X_HugeNumber_TestObject_prop,
    &X_Number1000001_Property0_prop,
};

/* parameter X_Number1000001.SpellMagnitude(): MIReturn */
static MI_CONST MI_ParameterDecl X_Number1000001_SpellMagnitude_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_Number1000001_SpellMagnitude, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST X_Number1000001_SpellMagnitude_params[] =
{
    &X_Number1000001_SpellMagnitude_MIReturn_param,
};

/* method X_Number1000001.SpellMagnitude() */
MI_CONST MI_MethodDecl X_Number1000001_SpellMagnitude_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650E, /* code */
    MI_T("SpellMagnitude"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_Number1000001_SpellMagnitude_params, /* parameters */
    MI_COUNT(X_Number1000001_SpellMagnitude_params), /* numParameters */
    sizeof(X_Number1000001_SpellMagnitude), /* size */
    MI_STRING, /* returnType */
    MI_T("X_HugeNumber"), /* origin */
    MI_T("X_HugeNumber"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)X_Number1000001_Invoke_SpellMagnitude, /* method */
};

static MI_CONST MI_Char* X_Number1000001_TestEmbedded_EmbeddedInstance_qual_value = MI_T("X_TestObject");

static MI_CONST MI_Qualifier X_Number1000001_TestEmbedded_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &X_Number1000001_TestEmbedded_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST X_Number1000001_TestEmbedded_quals[] =
{
    &X_Number1000001_TestEmbedded_EmbeddedInstance_qual,
};

/* parameter X_Number1000001.TestEmbedded(): objectsArray */
static MI_CONST MI_ParameterDecl X_Number1000001_TestEmbedded_objectsArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x006F790C, /* code */
    MI_T("objectsArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_Number1000001_TestEmbedded, objectsArray), /* offset */
};

/* parameter X_Number1000001.TestEmbedded(): objectSingle */
static MI_CONST MI_ParameterDecl X_Number1000001_TestEmbedded_objectSingle_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x006F650C, /* code */
    MI_T("objectSingle"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_Number1000001_TestEmbedded, objectSingle), /* offset */
};

static MI_CONST MI_Char* X_Number1000001_TestEmbedded_testObjectsArray_EmbeddedInstance_qual_value = MI_T("X_TestObject");

static MI_CONST MI_Qualifier X_Number1000001_TestEmbedded_testObjectsArray_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &X_Number1000001_TestEmbedded_testObjectsArray_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST X_Number1000001_TestEmbedded_testObjectsArray_quals[] =
{
    &X_Number1000001_TestEmbedded_testObjectsArray_EmbeddedInstance_qual,
};

/* parameter X_Number1000001.TestEmbedded(): testObjectsArray */
static MI_CONST MI_ParameterDecl X_Number1000001_TestEmbedded_testObjectsArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00747910, /* code */
    MI_T("testObjectsArray"), /* name */
    X_Number1000001_TestEmbedded_testObjectsArray_quals, /* qualifiers */
    MI_COUNT(X_Number1000001_TestEmbedded_testObjectsArray_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("X_TestObject"), /* className */
    0, /* subscript */
    offsetof(X_Number1000001_TestEmbedded, testObjectsArray), /* offset */
};

static MI_CONST MI_Char* X_Number1000001_TestEmbedded_testObjectSingle_EmbeddedInstance_qual_value = MI_T("X_TestObject");

static MI_CONST MI_Qualifier X_Number1000001_TestEmbedded_testObjectSingle_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &X_Number1000001_TestEmbedded_testObjectSingle_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST X_Number1000001_TestEmbedded_testObjectSingle_quals[] =
{
    &X_Number1000001_TestEmbedded_testObjectSingle_EmbeddedInstance_qual,
};

/* parameter X_Number1000001.TestEmbedded(): testObjectSingle */
static MI_CONST MI_ParameterDecl X_Number1000001_TestEmbedded_testObjectSingle_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00746510, /* code */
    MI_T("testObjectSingle"), /* name */
    X_Number1000001_TestEmbedded_testObjectSingle_quals, /* qualifiers */
    MI_COUNT(X_Number1000001_TestEmbedded_testObjectSingle_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("X_TestObject"), /* className */
    0, /* subscript */
    offsetof(X_Number1000001_TestEmbedded, testObjectSingle), /* offset */
};

static MI_CONST MI_Char* X_Number1000001_TestEmbedded_MIReturn_EmbeddedInstance_qual_value = MI_T("X_TestObject");

static MI_CONST MI_Qualifier X_Number1000001_TestEmbedded_MIReturn_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &X_Number1000001_TestEmbedded_MIReturn_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST X_Number1000001_TestEmbedded_MIReturn_quals[] =
{
    &X_Number1000001_TestEmbedded_MIReturn_EmbeddedInstance_qual,
};

/* parameter X_Number1000001.TestEmbedded(): MIReturn */
static MI_CONST MI_ParameterDecl X_Number1000001_TestEmbedded_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    X_Number1000001_TestEmbedded_MIReturn_quals, /* qualifiers */
    MI_COUNT(X_Number1000001_TestEmbedded_MIReturn_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("X_TestObject"), /* className */
    0, /* subscript */
    offsetof(X_Number1000001_TestEmbedded, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST X_Number1000001_TestEmbedded_params[] =
{
    &X_Number1000001_TestEmbedded_MIReturn_param,
    &X_Number1000001_TestEmbedded_objectsArray_param,
    &X_Number1000001_TestEmbedded_objectSingle_param,
    &X_Number1000001_TestEmbedded_testObjectsArray_param,
    &X_Number1000001_TestEmbedded_testObjectSingle_param,
};

/* method X_Number1000001.TestEmbedded() */
MI_CONST MI_MethodDecl X_Number1000001_TestEmbedded_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0074640C, /* code */
    MI_T("TestEmbedded"), /* name */
    X_Number1000001_TestEmbedded_quals, /* qualifiers */
    MI_COUNT(X_Number1000001_TestEmbedded_quals), /* numQualifiers */
    X_Number1000001_TestEmbedded_params, /* parameters */
    MI_COUNT(X_Number1000001_TestEmbedded_params), /* numParameters */
    sizeof(X_Number1000001_TestEmbedded), /* size */
    MI_INSTANCE, /* returnType */
    MI_T("X_HugeNumber"), /* origin */
    MI_T("X_HugeNumber"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)X_Number1000001_Invoke_TestEmbedded, /* method */
};

/* parameter X_Number1000001.Method1(): MIReturn */
static MI_CONST MI_ParameterDecl X_Number1000001_Method1_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_Number1000001_Method1, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST X_Number1000001_Method1_params[] =
{
    &X_Number1000001_Method1_MIReturn_param,
};

/* method X_Number1000001.Method1() */
MI_CONST MI_MethodDecl X_Number1000001_Method1_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x006D3107, /* code */
    MI_T("Method1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_Number1000001_Method1_params, /* parameters */
    MI_COUNT(X_Number1000001_Method1_params), /* numParameters */
    sizeof(X_Number1000001_Method1), /* size */
    MI_STRING, /* returnType */
    MI_T("X_Number1000001"), /* origin */
    MI_T("X_Number1000001"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)X_Number1000001_Invoke_Method1, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST X_Number1000001_meths[] =
{
    &X_Number1000001_SpellMagnitude_rtti,
    &X_Number1000001_TestEmbedded_rtti,
    &X_Number1000001_Method1_rtti,
};

static MI_CONST MI_ProviderFT X_Number1000001_funcs =
{
  (MI_ProviderFT_Load)X_Number1000001_Load,
  (MI_ProviderFT_Unload)X_Number1000001_Unload,
  (MI_ProviderFT_GetInstance)X_Number1000001_GetInstance,
  (MI_ProviderFT_EnumerateInstances)X_Number1000001_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)X_Number1000001_CreateInstance,
  (MI_ProviderFT_ModifyInstance)X_Number1000001_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)X_Number1000001_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class X_Number1000001 */
MI_CONST MI_ClassDecl X_Number1000001_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078310F, /* code */
    MI_T("X_Number1000001"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_Number1000001_props, /* properties */
    MI_COUNT(X_Number1000001_props), /* numProperties */
    sizeof(X_Number1000001), /* size */
    MI_T("X_HugeNumber"), /* superClass */
    &X_HugeNumber_rtti, /* superClassDecl */
    X_Number1000001_meths, /* methods */
    MI_COUNT(X_Number1000001_meths), /* numMethods */
    &schemaDecl, /* schema */
    &X_Number1000001_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** X_Cat
**
**==============================================================================
*/

/* property X_Cat.Key */
static MI_CONST MI_PropertyDecl X_Cat_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_Cat, Key), /* offset */
    MI_T("X_Cat"), /* origin */
    MI_T("X_Cat"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_Cat_props[] =
{
    &X_Cat_Key_prop,
};

static MI_CONST MI_ProviderFT X_Cat_funcs =
{
  (MI_ProviderFT_Load)X_Cat_Load,
  (MI_ProviderFT_Unload)X_Cat_Unload,
  (MI_ProviderFT_GetInstance)X_Cat_GetInstance,
  (MI_ProviderFT_EnumerateInstances)X_Cat_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)X_Cat_CreateInstance,
  (MI_ProviderFT_ModifyInstance)X_Cat_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)X_Cat_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class X_Cat */
MI_CONST MI_ClassDecl X_Cat_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00787405, /* code */
    MI_T("X_Cat"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_Cat_props, /* properties */
    MI_COUNT(X_Cat_props), /* numProperties */
    sizeof(X_Cat), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &X_Cat_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** X_Dog
**
**==============================================================================
*/


/* parameter X_Dog.Fight(): CatsIn */
static MI_CONST MI_ParameterDecl X_Dog_Fight_CatsIn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00636E06, /* code */
    MI_T("CatsIn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCEA, /* type */
    MI_T("X_Cat"), /* className */
    0, /* subscript */
    offsetof(X_Dog_Fight, CatsIn), /* offset */
};

/* parameter X_Dog.Fight(): CatsOut */
static MI_CONST MI_ParameterDecl X_Dog_Fight_CatsOut_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00637407, /* code */
    MI_T("CatsOut"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCEA, /* type */
    MI_T("X_Cat"), /* className */
    0, /* subscript */
    offsetof(X_Dog_Fight, CatsOut), /* offset */
};

/* parameter X_Dog.Fight(): MIReturn */
static MI_CONST MI_ParameterDecl X_Dog_Fight_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_Dog_Fight, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST X_Dog_Fight_params[] =
{
    &X_Dog_Fight_MIReturn_param,
    &X_Dog_Fight_CatsIn_param,
    &X_Dog_Fight_CatsOut_param,
};

/* method X_Dog.Fight() */
MI_CONST MI_MethodDecl X_Dog_Fight_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00667405, /* code */
    MI_T("Fight"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_Dog_Fight_params, /* parameters */
    MI_COUNT(X_Dog_Fight_params), /* numParameters */
    sizeof(X_Dog_Fight), /* size */
    MI_UINT32, /* returnType */
    MI_T("X_Dog"), /* origin */
    MI_T("X_Dog"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)X_Dog_Invoke_Fight, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST X_Dog_meths[] =
{
    &X_Dog_Fight_rtti,
};

static MI_CONST MI_ProviderFT X_Dog_funcs =
{
  (MI_ProviderFT_Load)X_Dog_Load,
  (MI_ProviderFT_Unload)X_Dog_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)NULL,
  (MI_ProviderFT_CreateInstance)NULL,
  (MI_ProviderFT_ModifyInstance)NULL,
  (MI_ProviderFT_DeleteInstance)NULL,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class X_Dog */
MI_CONST MI_ClassDecl X_Dog_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00786705, /* code */
    MI_T("X_Dog"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(X_Dog), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    X_Dog_meths, /* methods */
    MI_COUNT(X_Dog_meths), /* numMethods */
    &schemaDecl, /* schema */
    &X_Dog_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** X_HTTPHeader
**
**==============================================================================
*/

/* property X_HTTPHeader.Name */
static MI_CONST MI_PropertyDecl X_HTTPHeader_Name_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_HTTPHeader, Name), /* offset */
    MI_T("X_HTTPHeader"), /* origin */
    MI_T("X_HTTPHeader"), /* propagator */
    NULL,
};

/* property X_HTTPHeader.Value */
static MI_CONST MI_PropertyDecl X_HTTPHeader_Value_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00766505, /* code */
    MI_T("Value"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_HTTPHeader, Value), /* offset */
    MI_T("X_HTTPHeader"), /* origin */
    MI_T("X_HTTPHeader"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_HTTPHeader_props[] =
{
    &X_HTTPHeader_Name_prop,
    &X_HTTPHeader_Value_prop,
};

static MI_CONST MI_ProviderFT X_HTTPHeader_funcs =
{
  (MI_ProviderFT_Load)X_HTTPHeader_Load,
  (MI_ProviderFT_Unload)X_HTTPHeader_Unload,
  (MI_ProviderFT_GetInstance)X_HTTPHeader_GetInstance,
  (MI_ProviderFT_EnumerateInstances)X_HTTPHeader_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)X_HTTPHeader_CreateInstance,
  (MI_ProviderFT_ModifyInstance)X_HTTPHeader_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)X_HTTPHeader_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class X_HTTPHeader */
MI_CONST MI_ClassDecl X_HTTPHeader_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078720C, /* code */
    MI_T("X_HTTPHeader"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_HTTPHeader_props, /* properties */
    MI_COUNT(X_HTTPHeader_props), /* numProperties */
    sizeof(X_HTTPHeader), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &X_HTTPHeader_funcs, /* functions */
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
    &X_AllNumbers_rtti,
    &X_Cat_rtti,
    &X_Dog_rtti,
    &X_ElementConformsToProfile_rtti,
    &X_EvenSmallNumbers_rtti,
    &X_HTTPHeader_rtti,
    &X_Halves_rtti,
    &X_HugeNumber_rtti,
    &X_HugeNumberConformsToProfile_rtti,
    &X_HugeNumbers_rtti,
    &X_ManagedElement_rtti,
    &X_Number_rtti,
    &X_Number1000001_rtti,
    &X_NumberWorld_rtti,
    &X_NumberWorldConformsToProfile_rtti,
    &X_OddSmallNumbers_rtti,
    &X_Profile_rtti,
    &X_SmallNumber_rtti,
    &X_TestObject_rtti,
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

