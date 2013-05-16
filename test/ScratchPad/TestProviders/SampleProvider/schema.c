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
#include "Frog.h"

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
** Frog
**
**==============================================================================
*/

/* property Frog.id */
static MI_CONST MI_PropertyDecl Frog_id_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00696402, /* code */
    MI_T("id"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Frog, id), /* offset */
    MI_T("Frog"), /* origin */
    MI_T("Frog"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Frog_props[] =
{
    &Frog_id_prop,
};

static MI_CONST MI_ProviderFT Frog_funcs =
{
  (MI_ProviderFT_Load)Frog_Load,
  (MI_ProviderFT_Unload)Frog_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)Frog_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Frog_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Frog_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Frog_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Frog */
MI_CONST MI_ClassDecl Frog_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00666704, /* code */
    MI_T("Frog"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Frog_props, /* properties */
    MI_COUNT(Frog_props), /* numProperties */
    sizeof(Frog), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Frog_funcs, /* functions */
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
    &Frog_rtti,
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

