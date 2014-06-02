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
#include "Number.h"

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
** Number
**
**==============================================================================
*/

/* property Number.Description */
static MI_CONST MI_PropertyDecl Number_Description_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E0B, /* code */
    MI_T("Description"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Number, Description), /* offset */
    MI_T("XYZ_Number"), /* origin */
    MI_T("XYZ_Number"), /* propagator */
    NULL,
};

/* property Number.Number */
static MI_CONST MI_PropertyDecl Number_Number_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E7206, /* code */
    MI_T("Number"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Number, Number), /* offset */
    MI_T("XYZ_Number"), /* origin */
    MI_T("XYZ_Number"), /* propagator */
    NULL,
};

/* property Number.NumberString */
static MI_CONST MI_PropertyDecl Number_NumberString_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E670C, /* code */
    MI_T("NumberString"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Number, NumberString), /* offset */
    MI_T("XYZ_Number"), /* origin */
    MI_T("XYZ_Number"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Number_props[] =
{
    &Number_Description_prop,
    &Number_Number_prop,
    &Number_NumberString_prop,
};

static MI_CONST MI_ProviderFT Number_funcs =
{
  (MI_ProviderFT_Load)Number_Load,
  (MI_ProviderFT_Unload)Number_Unload,
  (MI_ProviderFT_GetInstance)Number_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Number_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Number_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Number_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Number_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Number */
MI_CONST MI_ClassDecl Number_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078720A, /* code */
    MI_T("XYZ_Number"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Number_props, /* properties */
    MI_COUNT(Number_props), /* numProperties */
    sizeof(Number), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Number_funcs, /* functions */
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
    &Number_rtti,
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

