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
#include "MSFT_Alert.h"
#include "MSFT_Friends.h"
#include "MSFT_Person.h"
#include "TestSP_Method.h"
#include "TestEmbeddedOperations.h"
#include "X_SingletonWithAllTypes.h"
#include "X_FailedAtLoad.h"
#include "X_RefuseUnload.h"
#include "X_TestEmbeddedObjectNotReferenced.h"

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

static MI_CONST MI_Boolean Stream_qual_decl_value = 0;

static MI_CONST MI_QualifierDecl Stream_qual_decl =
{
    MI_T("Stream"), /* name */
    MI_BOOLEAN, /* type */
    MI_FLAG_PARAMETER, /* scope */
    0, /* flavor */
    0, /* subscript */
    &Stream_qual_decl_value, /* value */
};

static MI_QualifierDecl MI_CONST* MI_CONST qualifierDecls[] =
{
    &Stream_qual_decl,
};

/*
**==============================================================================
**
** MSFT_Alert
**
**==============================================================================
*/

/* property MSFT_Alert.Message */
static MI_CONST MI_PropertyDecl MSFT_Alert_Message_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D6507, /* code */
    MI_T("Message"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Alert, Message), /* offset */
    MI_T("MSFT_Alert"), /* origin */
    MI_T("MSFT_Alert"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_Alert_props[] =
{
    &MSFT_Alert_Message_prop,
};

static MI_CONST MI_ProviderFT MSFT_Alert_funcs =
{
  (MI_ProviderFT_Load)MSFT_Alert_Load,
  (MI_ProviderFT_Unload)MSFT_Alert_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)NULL,
  (MI_ProviderFT_CreateInstance)NULL,
  (MI_ProviderFT_ModifyInstance)NULL,
  (MI_ProviderFT_DeleteInstance)NULL,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)MSFT_Alert_EnableIndications,
  (MI_ProviderFT_DisableIndications)MSFT_Alert_DisableIndications,
  (MI_ProviderFT_Subscribe)MSFT_Alert_Subscribe,
  (MI_ProviderFT_Unsubscribe)MSFT_Alert_Unsubscribe,
  (MI_ProviderFT_Invoke)NULL,
};

/* class MSFT_Alert */
MI_CONST MI_ClassDecl MSFT_Alert_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x006D740A, /* code */
    MI_T("MSFT_Alert"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_Alert_props, /* properties */
    MI_COUNT(MSFT_Alert_props), /* numProperties */
    sizeof(MSFT_Alert), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MSFT_Alert_funcs, /* functions */
};

/*
**==============================================================================
**
** MSFT_Base
**
**==============================================================================
*/

/* property MSFT_Base.Key */
static MI_CONST MI_PropertyDecl MSFT_Base_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Base, Key), /* offset */
    MI_T("MSFT_Base"), /* origin */
    MI_T("MSFT_Base"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_Base_props[] =
{
    &MSFT_Base_Key_prop,
};

/* class MSFT_Base */
MI_CONST MI_ClassDecl MSFT_Base_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D6509, /* code */
    MI_T("MSFT_Base"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_Base_props, /* properties */
    MI_COUNT(MSFT_Base_props), /* numProperties */
    sizeof(MSFT_Base), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** MSFT_Animal
**
**==============================================================================
*/

/* property MSFT_Animal.Species */
static MI_CONST MI_PropertyDecl MSFT_Animal_Species_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737307, /* code */
    MI_T("Species"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Animal, Species), /* offset */
    MI_T("MSFT_Animal"), /* origin */
    MI_T("MSFT_Animal"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_Animal_props[] =
{
    &MSFT_Base_Key_prop,
    &MSFT_Animal_Species_prop,
};

/* class MSFT_Animal */
MI_CONST MI_ClassDecl MSFT_Animal_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D6C0B, /* code */
    MI_T("MSFT_Animal"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_Animal_props, /* properties */
    MI_COUNT(MSFT_Animal_props), /* numProperties */
    sizeof(MSFT_Animal), /* size */
    MI_T("MSFT_Base"), /* superClass */
    &MSFT_Base_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** MSFT_Person
**
**==============================================================================
*/

/* property MSFT_Person.Key */
static MI_CONST MI_PropertyDecl MSFT_Person_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person, Key), /* offset */
    MI_T("MSFT_Base"), /* origin */
    MI_T("MSFT_Person"), /* propagator */
    NULL,
};

/* property MSFT_Person.Last */
static MI_CONST MI_PropertyDecl MSFT_Person_Last_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C7404, /* code */
    MI_T("Last"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person, Last), /* offset */
    MI_T("MSFT_Person"), /* origin */
    MI_T("MSFT_Person"), /* propagator */
    NULL,
};

/* property MSFT_Person.First */
static MI_CONST MI_PropertyDecl MSFT_Person_First_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00667405, /* code */
    MI_T("First"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person, First), /* offset */
    MI_T("MSFT_Person"), /* origin */
    MI_T("MSFT_Person"), /* propagator */
    NULL,
};

/* property MSFT_Person.ExpensiveProperty */
static MI_CONST MI_PropertyDecl MSFT_Person_ExpensiveProperty_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_EXPENSIVE, /* flags */
    0x00657911, /* code */
    MI_T("ExpensiveProperty"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person, ExpensiveProperty), /* offset */
    MI_T("MSFT_Person"), /* origin */
    MI_T("MSFT_Person"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_Person_props[] =
{
    &MSFT_Person_Key_prop,
    &MSFT_Animal_Species_prop,
    &MSFT_Person_Last_prop,
    &MSFT_Person_First_prop,
    &MSFT_Person_ExpensiveProperty_prop,
};

/* parameter MSFT_Person.Add(): X */
static MI_CONST MI_ParameterDecl MSFT_Person_Add_X_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00787801, /* code */
    MI_T("X"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_Add, X), /* offset */
};

/* parameter MSFT_Person.Add(): Y */
static MI_CONST MI_ParameterDecl MSFT_Person_Add_Y_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00797901, /* code */
    MI_T("Y"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_Add, Y), /* offset */
};

/* parameter MSFT_Person.Add(): Z */
static MI_CONST MI_ParameterDecl MSFT_Person_Add_Z_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x007A7A01, /* code */
    MI_T("Z"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_Add, Z), /* offset */
};

/* parameter MSFT_Person.Add(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_Person_Add_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_Add, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_Person_Add_params[] =
{
    &MSFT_Person_Add_MIReturn_param,
    &MSFT_Person_Add_X_param,
    &MSFT_Person_Add_Y_param,
    &MSFT_Person_Add_Z_param,
};

/* method MSFT_Person.Add() */
MI_CONST MI_MethodDecl MSFT_Person_Add_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00616403, /* code */
    MI_T("Add"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_Person_Add_params, /* parameters */
    MI_COUNT(MSFT_Person_Add_params), /* numParameters */
    sizeof(MSFT_Person_Add), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_Person"), /* origin */
    MI_T("MSFT_Person"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_Person_Invoke_Add, /* method */
};

/* parameter MSFT_Person.TestAllTypes(): b */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_b_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00626201, /* code */
    MI_T("b"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, b), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): u8 */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_u8_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00753802, /* code */
    MI_T("u8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, u8), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): s8 */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_s8_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00733802, /* code */
    MI_T("s8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, s8), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): u16 */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_u16_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00753603, /* code */
    MI_T("u16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, u16), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): s16 */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_s16_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00733603, /* code */
    MI_T("s16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, s16), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): u32 */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_u32_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00753203, /* code */
    MI_T("u32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, u32), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): s32 */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_s32_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00733203, /* code */
    MI_T("s32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, s32), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): u64 */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_u64_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00753403, /* code */
    MI_T("u64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, u64), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): s64 */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_s64_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00733403, /* code */
    MI_T("s64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, s64), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): r32 */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_r32_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00723203, /* code */
    MI_T("r32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, r32), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): r64 */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_r64_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00723403, /* code */
    MI_T("r64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, r64), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): dt */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_dt_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00647402, /* code */
    MI_T("dt"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, dt), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): rf */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_rf_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00726602, /* code */
    MI_T("rf"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("MSFT_Base"), /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, rf), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): s */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_s_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00737301, /* code */
    MI_T("s"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, s), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): c16 */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_c16_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00633603, /* code */
    MI_T("c16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, c16), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): bA */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_bA_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00626102, /* code */
    MI_T("bA"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, bA), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): u8A */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_u8A_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00756103, /* code */
    MI_T("u8A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, u8A), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): s8A */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_s8A_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00736103, /* code */
    MI_T("s8A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, s8A), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): u16A */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_u16A_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00756104, /* code */
    MI_T("u16A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, u16A), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): s16A */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_s16A_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00736104, /* code */
    MI_T("s16A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, s16A), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): u32A */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_u32A_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00756104, /* code */
    MI_T("u32A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, u32A), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): s32A */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_s32A_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00736104, /* code */
    MI_T("s32A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, s32A), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): u64A */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_u64A_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00756104, /* code */
    MI_T("u64A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, u64A), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): s64A */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_s64A_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00736104, /* code */
    MI_T("s64A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, s64A), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): r32A */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_r32A_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00726104, /* code */
    MI_T("r32A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, r32A), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): r64A */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_r64A_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00726104, /* code */
    MI_T("r64A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, r64A), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): dtA */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_dtA_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00646103, /* code */
    MI_T("dtA"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, dtA), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): sA */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_sA_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00736102, /* code */
    MI_T("sA"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, sA), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): c16A */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_c16A_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00636104, /* code */
    MI_T("c16A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, c16A), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): rfA */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_rfA_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00726103, /* code */
    MI_T("rfA"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCEA, /* type */
    MI_T("MSFT_Base"), /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, rfA), /* offset */
};

/* parameter MSFT_Person.TestAllTypes(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_Person_TestAllTypes_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_TestAllTypes, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_Person_TestAllTypes_params[] =
{
    &MSFT_Person_TestAllTypes_MIReturn_param,
    &MSFT_Person_TestAllTypes_b_param,
    &MSFT_Person_TestAllTypes_u8_param,
    &MSFT_Person_TestAllTypes_s8_param,
    &MSFT_Person_TestAllTypes_u16_param,
    &MSFT_Person_TestAllTypes_s16_param,
    &MSFT_Person_TestAllTypes_u32_param,
    &MSFT_Person_TestAllTypes_s32_param,
    &MSFT_Person_TestAllTypes_u64_param,
    &MSFT_Person_TestAllTypes_s64_param,
    &MSFT_Person_TestAllTypes_r32_param,
    &MSFT_Person_TestAllTypes_r64_param,
    &MSFT_Person_TestAllTypes_dt_param,
    &MSFT_Person_TestAllTypes_rf_param,
    &MSFT_Person_TestAllTypes_s_param,
    &MSFT_Person_TestAllTypes_c16_param,
    &MSFT_Person_TestAllTypes_bA_param,
    &MSFT_Person_TestAllTypes_u8A_param,
    &MSFT_Person_TestAllTypes_s8A_param,
    &MSFT_Person_TestAllTypes_u16A_param,
    &MSFT_Person_TestAllTypes_s16A_param,
    &MSFT_Person_TestAllTypes_u32A_param,
    &MSFT_Person_TestAllTypes_s32A_param,
    &MSFT_Person_TestAllTypes_u64A_param,
    &MSFT_Person_TestAllTypes_s64A_param,
    &MSFT_Person_TestAllTypes_r32A_param,
    &MSFT_Person_TestAllTypes_r64A_param,
    &MSFT_Person_TestAllTypes_dtA_param,
    &MSFT_Person_TestAllTypes_sA_param,
    &MSFT_Person_TestAllTypes_c16A_param,
    &MSFT_Person_TestAllTypes_rfA_param,
};

/* method MSFT_Person.TestAllTypes() */
MI_CONST MI_MethodDecl MSFT_Person_TestAllTypes_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0074730C, /* code */
    MI_T("TestAllTypes"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_Person_TestAllTypes_params, /* parameters */
    MI_COUNT(MSFT_Person_TestAllTypes_params), /* numParameters */
    sizeof(MSFT_Person_TestAllTypes), /* size */
    MI_STRING, /* returnType */
    MI_T("MSFT_Person"), /* origin */
    MI_T("MSFT_Person"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_Person_Invoke_TestAllTypes, /* method */
};

/* parameter MSFT_Person.StreamParams(): InArg */
static MI_CONST MI_ParameterDecl MSFT_Person_StreamParams_InArg_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00696705, /* code */
    MI_T("InArg"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_StreamParams, InArg), /* offset */
};

/* parameter MSFT_Person.StreamParams(): OutArg */
static MI_CONST MI_ParameterDecl MSFT_Person_StreamParams_OutArg_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT|MI_FLAG_STREAM, /* flags */
    0x006F6706, /* code */
    MI_T("OutArg"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    0xFFFFFFFF, /* offset */
};

/* parameter MSFT_Person.StreamParams(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_Person_StreamParams_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Person_StreamParams, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_Person_StreamParams_params[] =
{
    &MSFT_Person_StreamParams_MIReturn_param,
    &MSFT_Person_StreamParams_InArg_param,
    &MSFT_Person_StreamParams_OutArg_param,
};

/* method MSFT_Person.StreamParams() */
MI_CONST MI_MethodDecl MSFT_Person_StreamParams_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073730C, /* code */
    MI_T("StreamParams"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_Person_StreamParams_params, /* parameters */
    MI_COUNT(MSFT_Person_StreamParams_params), /* numParameters */
    sizeof(MSFT_Person_StreamParams), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_Person"), /* origin */
    MI_T("MSFT_Person"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_Person_Invoke_StreamParams, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MSFT_Person_meths[] =
{
    &MSFT_Person_Add_rtti,
    &MSFT_Person_TestAllTypes_rtti,
    &MSFT_Person_StreamParams_rtti,
};

static MI_CONST MI_ProviderFT MSFT_Person_funcs =
{
  (MI_ProviderFT_Load)MSFT_Person_Load,
  (MI_ProviderFT_Unload)MSFT_Person_Unload,
  (MI_ProviderFT_GetInstance)MSFT_Person_GetInstance,
  (MI_ProviderFT_EnumerateInstances)MSFT_Person_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)MSFT_Person_CreateInstance,
  (MI_ProviderFT_ModifyInstance)MSFT_Person_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)MSFT_Person_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class MSFT_Person */
MI_CONST MI_ClassDecl MSFT_Person_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D6E0B, /* code */
    MI_T("MSFT_Person"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_Person_props, /* properties */
    MI_COUNT(MSFT_Person_props), /* numProperties */
    sizeof(MSFT_Person), /* size */
    MI_T("MSFT_Animal"), /* superClass */
    &MSFT_Animal_rtti, /* superClassDecl */
    MSFT_Person_meths, /* methods */
    MI_COUNT(MSFT_Person_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MSFT_Person_funcs, /* functions */
};

/*
**==============================================================================
**
** MSFT_Friends
**
**==============================================================================
*/

/* property MSFT_Friends.Left */
static MI_CONST MI_PropertyDecl MSFT_Friends_Left_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006C7404, /* code */
    MI_T("Left"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("MSFT_Person"), /* className */
    0, /* subscript */
    offsetof(MSFT_Friends, Left), /* offset */
    MI_T("MSFT_Friends"), /* origin */
    MI_T("MSFT_Friends"), /* propagator */
    NULL,
};

/* property MSFT_Friends.Right */
static MI_CONST MI_PropertyDecl MSFT_Friends_Right_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00727405, /* code */
    MI_T("Right"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("MSFT_Person"), /* className */
    0, /* subscript */
    offsetof(MSFT_Friends, Right), /* offset */
    MI_T("MSFT_Friends"), /* origin */
    MI_T("MSFT_Friends"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_Friends_props[] =
{
    &MSFT_Friends_Left_prop,
    &MSFT_Friends_Right_prop,
};

/* parameter MSFT_Friends.AddFriend(): Friend */
static MI_CONST MI_ParameterDecl MSFT_Friends_AddFriend_Friend_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00666406, /* code */
    MI_T("Friend"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("MSFT_Person"), /* className */
    0, /* subscript */
    offsetof(MSFT_Friends_AddFriend, Friend), /* offset */
};

/* parameter MSFT_Friends.AddFriend(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_Friends_AddFriend_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Friends_AddFriend, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_Friends_AddFriend_params[] =
{
    &MSFT_Friends_AddFriend_MIReturn_param,
    &MSFT_Friends_AddFriend_Friend_param,
};

/* method MSFT_Friends.AddFriend() */
MI_CONST MI_MethodDecl MSFT_Friends_AddFriend_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00616409, /* code */
    MI_T("AddFriend"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_Friends_AddFriend_params, /* parameters */
    MI_COUNT(MSFT_Friends_AddFriend_params), /* numParameters */
    sizeof(MSFT_Friends_AddFriend), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_Friends"), /* origin */
    MI_T("MSFT_Friends"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_Friends_Invoke_AddFriend, /* method */
};

/* parameter MSFT_Friends.AddFriends(): Friends */
static MI_CONST MI_ParameterDecl MSFT_Friends_AddFriends_Friends_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00667307, /* code */
    MI_T("Friends"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCEA, /* type */
    MI_T("MSFT_Person"), /* className */
    0, /* subscript */
    offsetof(MSFT_Friends_AddFriends, Friends), /* offset */
};

/* parameter MSFT_Friends.AddFriends(): MIReturn */
static MI_CONST MI_ParameterDecl MSFT_Friends_AddFriends_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Friends_AddFriends, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MSFT_Friends_AddFriends_params[] =
{
    &MSFT_Friends_AddFriends_MIReturn_param,
    &MSFT_Friends_AddFriends_Friends_param,
};

/* method MSFT_Friends.AddFriends() */
MI_CONST MI_MethodDecl MSFT_Friends_AddFriends_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0061730A, /* code */
    MI_T("AddFriends"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_Friends_AddFriends_params, /* parameters */
    MI_COUNT(MSFT_Friends_AddFriends_params), /* numParameters */
    sizeof(MSFT_Friends_AddFriends), /* size */
    MI_UINT32, /* returnType */
    MI_T("MSFT_Friends"), /* origin */
    MI_T("MSFT_Friends"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MSFT_Friends_Invoke_AddFriends, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MSFT_Friends_meths[] =
{
    &MSFT_Friends_AddFriend_rtti,
    &MSFT_Friends_AddFriends_rtti,
};

static MI_CONST MI_ProviderFT MSFT_Friends_funcs =
{
  (MI_ProviderFT_Load)MSFT_Friends_Load,
  (MI_ProviderFT_Unload)MSFT_Friends_Unload,
  (MI_ProviderFT_GetInstance)MSFT_Friends_GetInstance,
  (MI_ProviderFT_EnumerateInstances)MSFT_Friends_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)MSFT_Friends_CreateInstance,
  (MI_ProviderFT_ModifyInstance)MSFT_Friends_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)MSFT_Friends_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)MSFT_Friends_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)MSFT_Friends_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class MSFT_Friends */
MI_CONST MI_ClassDecl MSFT_Friends_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x006D730C, /* code */
    MI_T("MSFT_Friends"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_Friends_props, /* properties */
    MI_COUNT(MSFT_Friends_props), /* numProperties */
    sizeof(MSFT_Friends), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    MSFT_Friends_meths, /* methods */
    MI_COUNT(MSFT_Friends_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MSFT_Friends_funcs, /* functions */
};

/*
**==============================================================================
**
** TestSP_Method
**
**==============================================================================
*/


/* parameter TestSP_Method.MyFunc(): v */
static MI_CONST MI_ParameterDecl TestSP_Method_MyFunc_v_param =
{
    MI_FLAG_PARAMETER, /* flags */
    0x00767601, /* code */
    MI_T("v"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestSP_Method_MyFunc, v), /* offset */
};

/* parameter TestSP_Method.MyFunc(): MIReturn */
static MI_CONST MI_ParameterDecl TestSP_Method_MyFunc_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestSP_Method_MyFunc, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestSP_Method_MyFunc_params[] =
{
    &TestSP_Method_MyFunc_MIReturn_param,
    &TestSP_Method_MyFunc_v_param,
};

/* method TestSP_Method.MyFunc() */
MI_CONST MI_MethodDecl TestSP_Method_MyFunc_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006D6306, /* code */
    MI_T("MyFunc"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestSP_Method_MyFunc_params, /* parameters */
    MI_COUNT(TestSP_Method_MyFunc_params), /* numParameters */
    sizeof(TestSP_Method_MyFunc), /* size */
    MI_UINT32, /* returnType */
    MI_T("TestSP_Method"), /* origin */
    MI_T("TestSP_Method"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestSP_Method_Invoke_MyFunc, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST TestSP_Method_meths[] =
{
    &TestSP_Method_MyFunc_rtti,
};

static MI_CONST MI_ProviderFT TestSP_Method_funcs =
{
  (MI_ProviderFT_Load)TestSP_Method_Load,
  (MI_ProviderFT_Unload)TestSP_Method_Unload,
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

/* class TestSP_Method */
MI_CONST MI_ClassDecl TestSP_Method_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0074640D, /* code */
    MI_T("TestSP_Method"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    NULL, /* properties */
    0, /* numProperties */
    sizeof(TestSP_Method), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    TestSP_Method_meths, /* methods */
    MI_COUNT(TestSP_Method_meths), /* numMethods */
    &schemaDecl, /* schema */
    &TestSP_Method_funcs, /* functions */
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
};

/*
**==============================================================================
**
** X_TestEmbeddedInstanceMIReturnObject
**
**==============================================================================
*/

/* property X_TestEmbeddedInstanceMIReturnObject.id */
static MI_CONST MI_PropertyDecl X_TestEmbeddedInstanceMIReturnObject_id_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00696402, /* code */
    MI_T("id"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_TestEmbeddedInstanceMIReturnObject, id), /* offset */
    MI_T("X_TestEmbeddedInstanceMIReturnObject"), /* origin */
    MI_T("X_TestEmbeddedInstanceMIReturnObject"), /* propagator */
    NULL,
};

/* property X_TestEmbeddedInstanceMIReturnObject.s */
static MI_CONST MI_PropertyDecl X_TestEmbeddedInstanceMIReturnObject_s_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737301, /* code */
    MI_T("s"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_TestEmbeddedInstanceMIReturnObject, s), /* offset */
    MI_T("X_TestEmbeddedInstanceMIReturnObject"), /* origin */
    MI_T("X_TestEmbeddedInstanceMIReturnObject"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_TestEmbeddedInstanceMIReturnObject_props[] =
{
    &X_TestEmbeddedInstanceMIReturnObject_id_prop,
    &X_TestEmbeddedInstanceMIReturnObject_s_prop,
};

/* class X_TestEmbeddedInstanceMIReturnObject */
MI_CONST MI_ClassDecl X_TestEmbeddedInstanceMIReturnObject_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00787424, /* code */
    MI_T("X_TestEmbeddedInstanceMIReturnObject"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_TestEmbeddedInstanceMIReturnObject_props, /* properties */
    MI_COUNT(X_TestEmbeddedInstanceMIReturnObject_props), /* numProperties */
    sizeof(X_TestEmbeddedInstanceMIReturnObject), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** TestEmbeddedOperations
**
**==============================================================================
*/

/* property TestEmbeddedOperations.key */
static MI_CONST MI_PropertyDecl TestEmbeddedOperations_key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestEmbeddedOperations, key), /* offset */
    MI_T("TestEmbeddedOperations"), /* origin */
    MI_T("TestEmbeddedOperations"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* TestEmbeddedOperations_person_EmbeddedInstance_qual_value = MI_T("MSFT_Person");

static MI_CONST MI_Qualifier TestEmbeddedOperations_person_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &TestEmbeddedOperations_person_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestEmbeddedOperations_person_quals[] =
{
    &TestEmbeddedOperations_person_EmbeddedInstance_qual,
};

/* property TestEmbeddedOperations.person */
static MI_CONST MI_PropertyDecl TestEmbeddedOperations_person_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706E06, /* code */
    MI_T("person"), /* name */
    TestEmbeddedOperations_person_quals, /* qualifiers */
    MI_COUNT(TestEmbeddedOperations_person_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_Person"), /* className */
    0, /* subscript */
    offsetof(TestEmbeddedOperations, person), /* offset */
    MI_T("TestEmbeddedOperations"), /* origin */
    MI_T("TestEmbeddedOperations"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* TestEmbeddedOperations_threePersons_EmbeddedInstance_qual_value = MI_T("MSFT_Person");

static MI_CONST MI_Qualifier TestEmbeddedOperations_threePersons_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &TestEmbeddedOperations_threePersons_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestEmbeddedOperations_threePersons_quals[] =
{
    &TestEmbeddedOperations_threePersons_EmbeddedInstance_qual,
};

/* property TestEmbeddedOperations.threePersons */
static MI_CONST MI_PropertyDecl TestEmbeddedOperations_threePersons_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0074730C, /* code */
    MI_T("threePersons"), /* name */
    TestEmbeddedOperations_threePersons_quals, /* qualifiers */
    MI_COUNT(TestEmbeddedOperations_threePersons_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("MSFT_Person"), /* className */
    0, /* subscript */
    offsetof(TestEmbeddedOperations, threePersons), /* offset */
    MI_T("TestEmbeddedOperations"), /* origin */
    MI_T("TestEmbeddedOperations"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST TestEmbeddedOperations_props[] =
{
    &TestEmbeddedOperations_key_prop,
    &TestEmbeddedOperations_person_prop,
    &TestEmbeddedOperations_threePersons_prop,
};

static MI_CONST MI_Char* TestEmbeddedOperations_TestEmbedded_EmbeddedInstance_qual_value = MI_T("X_TestObject");

static MI_CONST MI_Qualifier TestEmbeddedOperations_TestEmbedded_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &TestEmbeddedOperations_TestEmbedded_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestEmbeddedOperations_TestEmbedded_quals[] =
{
    &TestEmbeddedOperations_TestEmbedded_EmbeddedInstance_qual,
};

/* parameter TestEmbeddedOperations.TestEmbedded(): objectsArray */
static MI_CONST MI_ParameterDecl TestEmbeddedOperations_TestEmbedded_objectsArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x006F790C, /* code */
    MI_T("objectsArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestEmbeddedOperations_TestEmbedded, objectsArray), /* offset */
};

/* parameter TestEmbeddedOperations.TestEmbedded(): objectSingle */
static MI_CONST MI_ParameterDecl TestEmbeddedOperations_TestEmbedded_objectSingle_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x006F650C, /* code */
    MI_T("objectSingle"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestEmbeddedOperations_TestEmbedded, objectSingle), /* offset */
};

static MI_CONST MI_Char* TestEmbeddedOperations_TestEmbedded_testObjectsArray_EmbeddedInstance_qual_value = MI_T("X_TestObject");

static MI_CONST MI_Qualifier TestEmbeddedOperations_TestEmbedded_testObjectsArray_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &TestEmbeddedOperations_TestEmbedded_testObjectsArray_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestEmbeddedOperations_TestEmbedded_testObjectsArray_quals[] =
{
    &TestEmbeddedOperations_TestEmbedded_testObjectsArray_EmbeddedInstance_qual,
};

/* parameter TestEmbeddedOperations.TestEmbedded(): testObjectsArray */
static MI_CONST MI_ParameterDecl TestEmbeddedOperations_TestEmbedded_testObjectsArray_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00747910, /* code */
    MI_T("testObjectsArray"), /* name */
    TestEmbeddedOperations_TestEmbedded_testObjectsArray_quals, /* qualifiers */
    MI_COUNT(TestEmbeddedOperations_TestEmbedded_testObjectsArray_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("X_TestObject"), /* className */
    0, /* subscript */
    offsetof(TestEmbeddedOperations_TestEmbedded, testObjectsArray), /* offset */
};

static MI_CONST MI_Char* TestEmbeddedOperations_TestEmbedded_testObjectSingle_EmbeddedInstance_qual_value = MI_T("X_TestObject");

static MI_CONST MI_Qualifier TestEmbeddedOperations_TestEmbedded_testObjectSingle_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &TestEmbeddedOperations_TestEmbedded_testObjectSingle_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestEmbeddedOperations_TestEmbedded_testObjectSingle_quals[] =
{
    &TestEmbeddedOperations_TestEmbedded_testObjectSingle_EmbeddedInstance_qual,
};

/* parameter TestEmbeddedOperations.TestEmbedded(): testObjectSingle */
static MI_CONST MI_ParameterDecl TestEmbeddedOperations_TestEmbedded_testObjectSingle_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00746510, /* code */
    MI_T("testObjectSingle"), /* name */
    TestEmbeddedOperations_TestEmbedded_testObjectSingle_quals, /* qualifiers */
    MI_COUNT(TestEmbeddedOperations_TestEmbedded_testObjectSingle_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("X_TestObject"), /* className */
    0, /* subscript */
    offsetof(TestEmbeddedOperations_TestEmbedded, testObjectSingle), /* offset */
};

static MI_CONST MI_Char* TestEmbeddedOperations_TestEmbedded_MIReturn_EmbeddedInstance_qual_value = MI_T("X_TestObject");

static MI_CONST MI_Qualifier TestEmbeddedOperations_TestEmbedded_MIReturn_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &TestEmbeddedOperations_TestEmbedded_MIReturn_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestEmbeddedOperations_TestEmbedded_MIReturn_quals[] =
{
    &TestEmbeddedOperations_TestEmbedded_MIReturn_EmbeddedInstance_qual,
};

/* parameter TestEmbeddedOperations.TestEmbedded(): MIReturn */
static MI_CONST MI_ParameterDecl TestEmbeddedOperations_TestEmbedded_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TestEmbeddedOperations_TestEmbedded_MIReturn_quals, /* qualifiers */
    MI_COUNT(TestEmbeddedOperations_TestEmbedded_MIReturn_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("X_TestObject"), /* className */
    0, /* subscript */
    offsetof(TestEmbeddedOperations_TestEmbedded, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestEmbeddedOperations_TestEmbedded_params[] =
{
    &TestEmbeddedOperations_TestEmbedded_MIReturn_param,
    &TestEmbeddedOperations_TestEmbedded_objectsArray_param,
    &TestEmbeddedOperations_TestEmbedded_objectSingle_param,
    &TestEmbeddedOperations_TestEmbedded_testObjectsArray_param,
    &TestEmbeddedOperations_TestEmbedded_testObjectSingle_param,
};

/* method TestEmbeddedOperations.TestEmbedded() */
MI_CONST MI_MethodDecl TestEmbeddedOperations_TestEmbedded_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0074640C, /* code */
    MI_T("TestEmbedded"), /* name */
    TestEmbeddedOperations_TestEmbedded_quals, /* qualifiers */
    MI_COUNT(TestEmbeddedOperations_TestEmbedded_quals), /* numQualifiers */
    TestEmbeddedOperations_TestEmbedded_params, /* parameters */
    MI_COUNT(TestEmbeddedOperations_TestEmbedded_params), /* numParameters */
    sizeof(TestEmbeddedOperations_TestEmbedded), /* size */
    MI_INSTANCE, /* returnType */
    MI_T("TestEmbeddedOperations"), /* origin */
    MI_T("TestEmbeddedOperations"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestEmbeddedOperations_Invoke_TestEmbedded, /* method */
};

static MI_CONST MI_Char* TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_EmbeddedInstance_qual_value = MI_T("X_TestEmbeddedInstanceMIReturnObject");

static MI_CONST MI_Qualifier TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_quals[] =
{
    &TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_EmbeddedInstance_qual,
};

static MI_CONST MI_Char* TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_MIReturn_EmbeddedInstance_qual_value = MI_T("X_TestEmbeddedInstanceMIReturnObject");

static MI_CONST MI_Qualifier TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_MIReturn_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_MIReturn_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_MIReturn_quals[] =
{
    &TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_MIReturn_EmbeddedInstance_qual,
};

/* parameter TestEmbeddedOperations.TestEmbeddedInstanceReturnKey20100609(): MIReturn */
static MI_CONST MI_ParameterDecl TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_MIReturn_quals, /* qualifiers */
    MI_COUNT(TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_MIReturn_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("X_TestEmbeddedInstanceMIReturnObject"), /* className */
    0, /* subscript */
    offsetof(TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_params[] =
{
    &TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_MIReturn_param,
};

/* method TestEmbeddedOperations.TestEmbeddedInstanceReturnKey20100609() */
MI_CONST MI_MethodDecl TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00743925, /* code */
    MI_T("TestEmbeddedInstanceReturnKey20100609"), /* name */
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_quals, /* qualifiers */
    MI_COUNT(TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_quals), /* numQualifiers */
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_params, /* parameters */
    MI_COUNT(TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_params), /* numParameters */
    sizeof(TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609), /* size */
    MI_INSTANCE, /* returnType */
    MI_T("TestEmbeddedOperations"), /* origin */
    MI_T("TestEmbeddedOperations"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestEmbeddedOperations_Invoke_TestEmbeddedInstanceReturnKey20100609, /* method */
};

/* parameter TestEmbeddedOperations.TestEmbeddedObjectReturnKey20100609(): MIReturn */
static MI_CONST MI_ParameterDecl TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_params[] =
{
    &TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_MIReturn_param,
};

/* method TestEmbeddedOperations.TestEmbeddedObjectReturnKey20100609() */
MI_CONST MI_MethodDecl TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00743923, /* code */
    MI_T("TestEmbeddedObjectReturnKey20100609"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_params, /* parameters */
    MI_COUNT(TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_params), /* numParameters */
    sizeof(TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609), /* size */
    MI_INSTANCE, /* returnType */
    MI_T("TestEmbeddedOperations"), /* origin */
    MI_T("TestEmbeddedOperations"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)TestEmbeddedOperations_Invoke_TestEmbeddedObjectReturnKey20100609, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST TestEmbeddedOperations_meths[] =
{
    &TestEmbeddedOperations_TestEmbedded_rtti,
    &TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_rtti,
    &TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_rtti,
};

static MI_CONST MI_ProviderFT TestEmbeddedOperations_funcs =
{
  (MI_ProviderFT_Load)TestEmbeddedOperations_Load,
  (MI_ProviderFT_Unload)TestEmbeddedOperations_Unload,
  (MI_ProviderFT_GetInstance)TestEmbeddedOperations_GetInstance,
  (MI_ProviderFT_EnumerateInstances)TestEmbeddedOperations_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)TestEmbeddedOperations_CreateInstance,
  (MI_ProviderFT_ModifyInstance)TestEmbeddedOperations_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)TestEmbeddedOperations_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class TestEmbeddedOperations */
MI_CONST MI_ClassDecl TestEmbeddedOperations_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00747316, /* code */
    MI_T("TestEmbeddedOperations"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    TestEmbeddedOperations_props, /* properties */
    MI_COUNT(TestEmbeddedOperations_props), /* numProperties */
    sizeof(TestEmbeddedOperations), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    TestEmbeddedOperations_meths, /* methods */
    MI_COUNT(TestEmbeddedOperations_meths), /* numMethods */
    &schemaDecl, /* schema */
    &TestEmbeddedOperations_funcs, /* functions */
};

/*
**==============================================================================
**
** X_SingletonWithAllTypes
**
**==============================================================================
*/

/* property X_SingletonWithAllTypes.id */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_id_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00696402, /* code */
    MI_T("id"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, id), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.b */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_b_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00626201, /* code */
    MI_T("b"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, b), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.u8 */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_u8_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00753802, /* code */
    MI_T("u8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, u8), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.s8 */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_s8_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733802, /* code */
    MI_T("s8"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, s8), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.u16 */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_u16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00753603, /* code */
    MI_T("u16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, u16), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.s16 */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_s16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733603, /* code */
    MI_T("s16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, s16), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.u32 */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_u32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00753203, /* code */
    MI_T("u32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, u32), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.s32 */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_s32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733203, /* code */
    MI_T("s32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, s32), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.u64 */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_u64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00753403, /* code */
    MI_T("u64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, u64), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.s64 */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_s64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00733403, /* code */
    MI_T("s64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, s64), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.r32 */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_r32_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00723203, /* code */
    MI_T("r32"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, r32), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.r64 */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_r64_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00723403, /* code */
    MI_T("r64"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, r64), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.dt */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_dt_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00647402, /* code */
    MI_T("dt"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, dt), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.s */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_s_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737301, /* code */
    MI_T("s"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, s), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.c16 */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_c16_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00633603, /* code */
    MI_T("c16"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, c16), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.bA */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_bA_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00626102, /* code */
    MI_T("bA"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEANA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, bA), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.u8A */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_u8A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756103, /* code */
    MI_T("u8A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, u8A), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.s8A */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_s8A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736103, /* code */
    MI_T("s8A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, s8A), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.u16A */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_u16A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756104, /* code */
    MI_T("u16A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, u16A), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.s16A */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_s16A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736104, /* code */
    MI_T("s16A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, s16A), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.u32A */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_u32A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756104, /* code */
    MI_T("u32A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, u32A), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.s32A */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_s32A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736104, /* code */
    MI_T("s32A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, s32A), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.u64A */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_u64A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756104, /* code */
    MI_T("u64A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, u64A), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.s64A */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_s64A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736104, /* code */
    MI_T("s64A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, s64A), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.r32A */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_r32A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726104, /* code */
    MI_T("r32A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, r32A), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.r64A */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_r64A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726104, /* code */
    MI_T("r64A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, r64A), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.dtA */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_dtA_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646103, /* code */
    MI_T("dtA"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, dtA), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.sA */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_sA_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736102, /* code */
    MI_T("sA"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, sA), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.c16A */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_c16A_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00636104, /* code */
    MI_T("c16A"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_CHAR16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, c16A), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* X_SingletonWithAllTypes_person_EmbeddedInstance_qual_value = MI_T("MSFT_Person");

static MI_CONST MI_Qualifier X_SingletonWithAllTypes_person_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &X_SingletonWithAllTypes_person_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST X_SingletonWithAllTypes_person_quals[] =
{
    &X_SingletonWithAllTypes_person_EmbeddedInstance_qual,
};

/* property X_SingletonWithAllTypes.person */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_person_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706E06, /* code */
    MI_T("person"), /* name */
    X_SingletonWithAllTypes_person_quals, /* qualifiers */
    MI_COUNT(X_SingletonWithAllTypes_person_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("MSFT_Person"), /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, person), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* X_SingletonWithAllTypes_fourObjects_EmbeddedInstance_qual_value = MI_T("X_TestObject");

static MI_CONST MI_Qualifier X_SingletonWithAllTypes_fourObjects_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &X_SingletonWithAllTypes_fourObjects_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST X_SingletonWithAllTypes_fourObjects_quals[] =
{
    &X_SingletonWithAllTypes_fourObjects_EmbeddedInstance_qual,
};

/* property X_SingletonWithAllTypes.fourObjects */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_fourObjects_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0066730B, /* code */
    MI_T("fourObjects"), /* name */
    X_SingletonWithAllTypes_fourObjects_quals, /* qualifiers */
    MI_COUNT(X_SingletonWithAllTypes_fourObjects_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("X_TestObject"), /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, fourObjects), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.objectSingle */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_objectSingle_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F650C, /* code */
    MI_T("objectSingle"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCE, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, objectSingle), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

/* property X_SingletonWithAllTypes.objectsArray */
static MI_CONST MI_PropertyDecl X_SingletonWithAllTypes_objectsArray_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F790C, /* code */
    MI_T("objectsArray"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_INSTANCEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_SingletonWithAllTypes, objectsArray), /* offset */
    MI_T("X_SingletonWithAllTypes"), /* origin */
    MI_T("X_SingletonWithAllTypes"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_SingletonWithAllTypes_props[] =
{
    &X_SingletonWithAllTypes_id_prop,
    &X_SingletonWithAllTypes_b_prop,
    &X_SingletonWithAllTypes_u8_prop,
    &X_SingletonWithAllTypes_s8_prop,
    &X_SingletonWithAllTypes_u16_prop,
    &X_SingletonWithAllTypes_s16_prop,
    &X_SingletonWithAllTypes_u32_prop,
    &X_SingletonWithAllTypes_s32_prop,
    &X_SingletonWithAllTypes_u64_prop,
    &X_SingletonWithAllTypes_s64_prop,
    &X_SingletonWithAllTypes_r32_prop,
    &X_SingletonWithAllTypes_r64_prop,
    &X_SingletonWithAllTypes_dt_prop,
    &X_SingletonWithAllTypes_s_prop,
    &X_SingletonWithAllTypes_c16_prop,
    &X_SingletonWithAllTypes_bA_prop,
    &X_SingletonWithAllTypes_u8A_prop,
    &X_SingletonWithAllTypes_s8A_prop,
    &X_SingletonWithAllTypes_u16A_prop,
    &X_SingletonWithAllTypes_s16A_prop,
    &X_SingletonWithAllTypes_u32A_prop,
    &X_SingletonWithAllTypes_s32A_prop,
    &X_SingletonWithAllTypes_u64A_prop,
    &X_SingletonWithAllTypes_s64A_prop,
    &X_SingletonWithAllTypes_r32A_prop,
    &X_SingletonWithAllTypes_r64A_prop,
    &X_SingletonWithAllTypes_dtA_prop,
    &X_SingletonWithAllTypes_sA_prop,
    &X_SingletonWithAllTypes_c16A_prop,
    &X_SingletonWithAllTypes_person_prop,
    &X_SingletonWithAllTypes_fourObjects_prop,
    &X_SingletonWithAllTypes_objectSingle_prop,
    &X_SingletonWithAllTypes_objectsArray_prop,
};

static MI_CONST MI_ProviderFT X_SingletonWithAllTypes_funcs =
{
  (MI_ProviderFT_Load)X_SingletonWithAllTypes_Load,
  (MI_ProviderFT_Unload)X_SingletonWithAllTypes_Unload,
  (MI_ProviderFT_GetInstance)X_SingletonWithAllTypes_GetInstance,
  (MI_ProviderFT_EnumerateInstances)X_SingletonWithAllTypes_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)X_SingletonWithAllTypes_CreateInstance,
  (MI_ProviderFT_ModifyInstance)X_SingletonWithAllTypes_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)X_SingletonWithAllTypes_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class X_SingletonWithAllTypes */
MI_CONST MI_ClassDecl X_SingletonWithAllTypes_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00787317, /* code */
    MI_T("X_SingletonWithAllTypes"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_SingletonWithAllTypes_props, /* properties */
    MI_COUNT(X_SingletonWithAllTypes_props), /* numProperties */
    sizeof(X_SingletonWithAllTypes), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &X_SingletonWithAllTypes_funcs, /* functions */
};

/*
**==============================================================================
**
** X_FailedAtLoad
**
**==============================================================================
*/

/* property X_FailedAtLoad.id */
static MI_CONST MI_PropertyDecl X_FailedAtLoad_id_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00696402, /* code */
    MI_T("id"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_FailedAtLoad, id), /* offset */
    MI_T("X_FailedAtLoad"), /* origin */
    MI_T("X_FailedAtLoad"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_FailedAtLoad_props[] =
{
    &X_FailedAtLoad_id_prop,
};

static MI_CONST MI_ProviderFT X_FailedAtLoad_funcs =
{
  (MI_ProviderFT_Load)X_FailedAtLoad_Load,
  (MI_ProviderFT_Unload)X_FailedAtLoad_Unload,
  (MI_ProviderFT_GetInstance)X_FailedAtLoad_GetInstance,
  (MI_ProviderFT_EnumerateInstances)X_FailedAtLoad_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)X_FailedAtLoad_CreateInstance,
  (MI_ProviderFT_ModifyInstance)X_FailedAtLoad_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)X_FailedAtLoad_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class X_FailedAtLoad */
MI_CONST MI_ClassDecl X_FailedAtLoad_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078640E, /* code */
    MI_T("X_FailedAtLoad"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_FailedAtLoad_props, /* properties */
    MI_COUNT(X_FailedAtLoad_props), /* numProperties */
    sizeof(X_FailedAtLoad), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &X_FailedAtLoad_funcs, /* functions */
};

/*
**==============================================================================
**
** X_RefuseUnload
**
**==============================================================================
*/

/* property X_RefuseUnload.id */
static MI_CONST MI_PropertyDecl X_RefuseUnload_id_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00696402, /* code */
    MI_T("id"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_RefuseUnload, id), /* offset */
    MI_T("X_RefuseUnload"), /* origin */
    MI_T("X_RefuseUnload"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_RefuseUnload_props[] =
{
    &X_RefuseUnload_id_prop,
};

/* parameter X_RefuseUnload.RequestUnload(): MIReturn */
static MI_CONST MI_ParameterDecl X_RefuseUnload_RequestUnload_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_RefuseUnload_RequestUnload, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST X_RefuseUnload_RequestUnload_params[] =
{
    &X_RefuseUnload_RequestUnload_MIReturn_param,
};

/* method X_RefuseUnload.RequestUnload() */
MI_CONST MI_MethodDecl X_RefuseUnload_RequestUnload_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x0072640D, /* code */
    MI_T("RequestUnload"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_RefuseUnload_RequestUnload_params, /* parameters */
    MI_COUNT(X_RefuseUnload_RequestUnload_params), /* numParameters */
    sizeof(X_RefuseUnload_RequestUnload), /* size */
    MI_UINT32, /* returnType */
    MI_T("X_RefuseUnload"), /* origin */
    MI_T("X_RefuseUnload"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)X_RefuseUnload_Invoke_RequestUnload, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST X_RefuseUnload_meths[] =
{
    &X_RefuseUnload_RequestUnload_rtti,
};

static MI_CONST MI_ProviderFT X_RefuseUnload_funcs =
{
  (MI_ProviderFT_Load)X_RefuseUnload_Load,
  (MI_ProviderFT_Unload)X_RefuseUnload_Unload,
  (MI_ProviderFT_GetInstance)X_RefuseUnload_GetInstance,
  (MI_ProviderFT_EnumerateInstances)X_RefuseUnload_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)X_RefuseUnload_CreateInstance,
  (MI_ProviderFT_ModifyInstance)X_RefuseUnload_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)X_RefuseUnload_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class X_RefuseUnload */
MI_CONST MI_ClassDecl X_RefuseUnload_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078640E, /* code */
    MI_T("X_RefuseUnload"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_RefuseUnload_props, /* properties */
    MI_COUNT(X_RefuseUnload_props), /* numProperties */
    sizeof(X_RefuseUnload), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    X_RefuseUnload_meths, /* methods */
    MI_COUNT(X_RefuseUnload_meths), /* numMethods */
    &schemaDecl, /* schema */
    &X_RefuseUnload_funcs, /* functions */
};

/*
**==============================================================================
**
** X_TestEmbeddedObjectNotReferenced
**
**==============================================================================
*/

/* property X_TestEmbeddedObjectNotReferenced.ObjectID */
static MI_CONST MI_PropertyDecl X_TestEmbeddedObjectNotReferenced_ObjectID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006F6408, /* code */
    MI_T("ObjectID"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(X_TestEmbeddedObjectNotReferenced, ObjectID), /* offset */
    MI_T("X_TestEmbeddedObjectNotReferenced"), /* origin */
    MI_T("X_TestEmbeddedObjectNotReferenced"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST X_TestEmbeddedObjectNotReferenced_props[] =
{
    &X_TestEmbeddedObjectNotReferenced_ObjectID_prop,
};

/* class X_TestEmbeddedObjectNotReferenced */
MI_CONST MI_ClassDecl X_TestEmbeddedObjectNotReferenced_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00786421, /* code */
    MI_T("X_TestEmbeddedObjectNotReferenced"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    X_TestEmbeddedObjectNotReferenced_props, /* properties */
    MI_COUNT(X_TestEmbeddedObjectNotReferenced_props), /* numProperties */
    sizeof(X_TestEmbeddedObjectNotReferenced), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
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
    &MSFT_Alert_rtti,
    &MSFT_Animal_rtti,
    &MSFT_Base_rtti,
    &MSFT_Friends_rtti,
    &MSFT_Person_rtti,
    &TestEmbeddedOperations_rtti,
    &TestSP_Method_rtti,
    &X_FailedAtLoad_rtti,
    &X_RefuseUnload_rtti,
    &X_SingletonWithAllTypes_rtti,
    &X_TestEmbeddedInstanceMIReturnObject_rtti,
    &X_TestEmbeddedObjectNotReferenced_rtti,
    &X_TestObject_rtti,
};

MI_SchemaDecl schemaDecl =
{
    qualifierDecls, /* qualifierDecls */
    MI_COUNT(qualifierDecls), /* numQualifierDecls */
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

