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
#include "Dog.h"

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
** Dog
**
**==============================================================================
*/

/* property Dog.Key */
static MI_CONST MI_PropertyDecl Dog_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Dog, Key), /* offset */
    MI_T("XYZ_Dog"), /* origin */
    MI_T("XYZ_Dog"), /* propagator */
    NULL,
};

/* property Dog.Array1 */
static MI_CONST MI_PropertyDecl Dog_Array1_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613106, /* code */
    MI_T("Array1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Dog, Array1), /* offset */
    MI_T("XYZ_Dog"), /* origin */
    MI_T("XYZ_Dog"), /* propagator */
    NULL,
};

/* property Dog.Array2 */
static MI_CONST MI_PropertyDecl Dog_Array2_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613206, /* code */
    MI_T("Array2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Dog, Array2), /* offset */
    MI_T("XYZ_Dog"), /* origin */
    MI_T("XYZ_Dog"), /* propagator */
    NULL,
};

/* property Dog.Array3 */
static MI_CONST MI_PropertyDecl Dog_Array3_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00613306, /* code */
    MI_T("Array3"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Dog, Array3), /* offset */
    MI_T("XYZ_Dog"), /* origin */
    MI_T("XYZ_Dog"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Dog_props[] =
{
    &Dog_Key_prop,
    &Dog_Array1_prop,
    &Dog_Array2_prop,
    &Dog_Array3_prop,
};

static MI_CONST MI_ProviderFT Dog_funcs =
{
  (MI_ProviderFT_Load)Dog_Load,
  (MI_ProviderFT_Unload)Dog_Unload,
  (MI_ProviderFT_GetInstance)Dog_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Dog_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Dog_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Dog_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Dog_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Dog */
MI_CONST MI_ClassDecl Dog_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00786707, /* code */
    MI_T("XYZ_Dog"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Dog_props, /* properties */
    MI_COUNT(Dog_props), /* numProperties */
    sizeof(Dog), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Dog_funcs, /* functions */
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
    &Dog_rtti,
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

