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
#include "Main.h"
#include "EmbeddedInstance.h"

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
** EmbeddedInstance
**
**==============================================================================
*/

/* property EmbeddedInstance.Id */
static MI_CONST MI_PropertyDecl EmbeddedInstance_Id_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00696402, /* code */
    MI_T("Id"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(EmbeddedInstance, Id), /* offset */
    MI_T("XXX_EmbeddedInstance"), /* origin */
    MI_T("XXX_EmbeddedInstance"), /* propagator */
    NULL,
};

/* property EmbeddedInstance.Element */
static MI_CONST MI_PropertyDecl EmbeddedInstance_Element_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00657407, /* code */
    MI_T("Element"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(EmbeddedInstance, Element), /* offset */
    MI_T("XXX_EmbeddedInstance"), /* origin */
    MI_T("XXX_EmbeddedInstance"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST EmbeddedInstance_props[] =
{
    &EmbeddedInstance_Id_prop,
    &EmbeddedInstance_Element_prop,
};

static MI_CONST MI_ProviderFT EmbeddedInstance_funcs =
{
  (MI_ProviderFT_Load)EmbeddedInstance_Load,
  (MI_ProviderFT_Unload)EmbeddedInstance_Unload,
  (MI_ProviderFT_GetInstance)EmbeddedInstance_GetInstance,
  (MI_ProviderFT_EnumerateInstances)EmbeddedInstance_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)EmbeddedInstance_CreateInstance,
  (MI_ProviderFT_ModifyInstance)EmbeddedInstance_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)EmbeddedInstance_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class EmbeddedInstance */
MI_CONST MI_ClassDecl EmbeddedInstance_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00786514, /* code */
    MI_T("XXX_EmbeddedInstance"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    EmbeddedInstance_props, /* properties */
    MI_COUNT(EmbeddedInstance_props), /* numProperties */
    sizeof(EmbeddedInstance), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &EmbeddedInstance_funcs, /* functions */
};

/*
**==============================================================================
**
** Main
**
**==============================================================================
*/

/* property Main.Name */
static MI_CONST MI_PropertyDecl Main_Name_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Main, Name), /* offset */
    MI_T("XXX_Main"), /* origin */
    MI_T("XXX_Main"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* Main_FristInstance_EmbeddedInstance_qual_value = MI_T("XXX_EmbeddedInstance");

static MI_CONST MI_Qualifier Main_FristInstance_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &Main_FristInstance_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Main_FristInstance_quals[] =
{
    &Main_FristInstance_EmbeddedInstance_qual,
};

/* property Main.FristInstance */
static MI_CONST MI_PropertyDecl Main_FristInstance_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0066650D, /* code */
    MI_T("FristInstance"), /* name */
    Main_FristInstance_quals, /* qualifiers */
    MI_COUNT(Main_FristInstance_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("XXX_EmbeddedInstance"), /* className */
    0, /* subscript */
    offsetof(Main, FristInstance), /* offset */
    MI_T("XXX_Main"), /* origin */
    MI_T("XXX_Main"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* Main_SecondInstance_EmbeddedInstance_qual_value = MI_T("XXX_EmbeddedInstance");

static MI_CONST MI_Qualifier Main_SecondInstance_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &Main_SecondInstance_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Main_SecondInstance_quals[] =
{
    &Main_SecondInstance_EmbeddedInstance_qual,
};

/* property Main.SecondInstance */
static MI_CONST MI_PropertyDecl Main_SecondInstance_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073650E, /* code */
    MI_T("SecondInstance"), /* name */
    Main_SecondInstance_quals, /* qualifiers */
    MI_COUNT(Main_SecondInstance_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("XXX_EmbeddedInstance"), /* className */
    0, /* subscript */
    offsetof(Main, SecondInstance), /* offset */
    MI_T("XXX_Main"), /* origin */
    MI_T("XXX_Main"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Main_props[] =
{
    &Main_Name_prop,
    &Main_FristInstance_prop,
    &Main_SecondInstance_prop,
};

static MI_CONST MI_ProviderFT Main_funcs =
{
  (MI_ProviderFT_Load)Main_Load,
  (MI_ProviderFT_Unload)Main_Unload,
  (MI_ProviderFT_GetInstance)Main_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Main_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Main_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Main_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Main_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Main */
MI_CONST MI_ClassDecl Main_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00786E08, /* code */
    MI_T("XXX_Main"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Main_props, /* properties */
    MI_COUNT(Main_props), /* numProperties */
    sizeof(Main), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Main_funcs, /* functions */
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
    &EmbeddedInstance_rtti,
    &Main_rtti,
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

