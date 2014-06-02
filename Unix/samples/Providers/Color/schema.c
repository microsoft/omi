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
#include "ColorBase.h"
#include "Color.h"

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
** ColorBase
**
**==============================================================================
*/

/* property ColorBase.Id */
static MI_CONST MI_PropertyDecl ColorBase_Id_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00696402, /* code */
    MI_T("Id"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ColorBase, Id), /* offset */
    MI_T("XYZ_ColorBase"), /* origin */
    MI_T("XYZ_ColorBase"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST ColorBase_props[] =
{
    &ColorBase_Id_prop,
};

static MI_CONST MI_ProviderFT ColorBase_funcs =
{
  (MI_ProviderFT_Load)ColorBase_Load,
  (MI_ProviderFT_Unload)ColorBase_Unload,
  (MI_ProviderFT_GetInstance)ColorBase_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ColorBase_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ColorBase_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ColorBase_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ColorBase_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class ColorBase */
MI_CONST MI_ClassDecl ColorBase_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078650D, /* code */
    MI_T("XYZ_ColorBase"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ColorBase_props, /* properties */
    MI_COUNT(ColorBase_props), /* numProperties */
    sizeof(ColorBase), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &ColorBase_funcs, /* functions */
};

/*
**==============================================================================
**
** Color
**
**==============================================================================
*/

/* property Color.Caption */
static MI_CONST MI_PropertyDecl Color_Caption_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00636E07, /* code */
    MI_T("Caption"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Color, Caption), /* offset */
    MI_T("XYZ_Color"), /* origin */
    MI_T("XYZ_Color"), /* propagator */
    NULL,
};

/* property Color.Name */
static MI_CONST MI_PropertyDecl Color_Name_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Color, Name), /* offset */
    MI_T("XYZ_Color"), /* origin */
    MI_T("XYZ_Color"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Color_props[] =
{
    &ColorBase_Id_prop,
    &Color_Caption_prop,
    &Color_Name_prop,
};

static MI_CONST MI_ProviderFT Color_funcs =
{
  (MI_ProviderFT_Load)Color_Load,
  (MI_ProviderFT_Unload)Color_Unload,
  (MI_ProviderFT_GetInstance)Color_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Color_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Color_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Color_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Color_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Color */
MI_CONST MI_ClassDecl Color_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00787209, /* code */
    MI_T("XYZ_Color"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Color_props, /* properties */
    MI_COUNT(Color_props), /* numProperties */
    sizeof(Color), /* size */
    MI_T("XYZ_ColorBase"), /* superClass */
    &ColorBase_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Color_funcs, /* functions */
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
    &Color_rtti,
    &ColorBase_rtti,
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

