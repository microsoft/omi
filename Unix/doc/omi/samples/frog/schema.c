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
#include "XYZ_Frog.h"

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
** XYZ_Frog
**
**==============================================================================
*/

/* property XYZ_Frog.Name */
static MI_CONST MI_PropertyDecl XYZ_Frog_Name_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(XYZ_Frog, Name), /* offset */
    MI_T("XYZ_Frog"), /* origin */
    MI_T("XYZ_Frog"), /* propagator */
    NULL,
};

/* property XYZ_Frog.Weight */
static MI_CONST MI_PropertyDecl XYZ_Frog_Weight_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00777406, /* code */
    MI_T("Weight"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(XYZ_Frog, Weight), /* offset */
    MI_T("XYZ_Frog"), /* origin */
    MI_T("XYZ_Frog"), /* propagator */
    NULL,
};

/* property XYZ_Frog.Color */
static MI_CONST MI_PropertyDecl XYZ_Frog_Color_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637205, /* code */
    MI_T("Color"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(XYZ_Frog, Color), /* offset */
    MI_T("XYZ_Frog"), /* origin */
    MI_T("XYZ_Frog"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST XYZ_Frog_props[] =
{
    &XYZ_Frog_Name_prop,
    &XYZ_Frog_Weight_prop,
    &XYZ_Frog_Color_prop,
};

static MI_CONST MI_ProviderFT XYZ_Frog_funcs =
{
  (MI_ProviderFT_Load)XYZ_Frog_Load,
  (MI_ProviderFT_Unload)XYZ_Frog_Unload,
  (MI_ProviderFT_GetInstance)XYZ_Frog_GetInstance,
  (MI_ProviderFT_EnumerateInstances)XYZ_Frog_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)XYZ_Frog_CreateInstance,
  (MI_ProviderFT_ModifyInstance)XYZ_Frog_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)XYZ_Frog_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class XYZ_Frog */
MI_CONST MI_ClassDecl XYZ_Frog_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00786708, /* code */
    MI_T("XYZ_Frog"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    XYZ_Frog_props, /* properties */
    MI_COUNT(XYZ_Frog_props), /* numProperties */
    sizeof(XYZ_Frog), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &XYZ_Frog_funcs, /* functions */
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
    &XYZ_Frog_rtti,
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

