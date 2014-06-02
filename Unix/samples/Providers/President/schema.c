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
#include "President.h"
#include "PresidentLink.h"
#include "VicePresident.h"

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
** President
**
**==============================================================================
*/

/* property President.Key */
static MI_CONST MI_PropertyDecl President_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(President, Key), /* offset */
    MI_T("MSFT_President"), /* origin */
    MI_T("MSFT_President"), /* propagator */
    NULL,
};

/* property President.First */
static MI_CONST MI_PropertyDecl President_First_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00667405, /* code */
    MI_T("First"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(President, First), /* offset */
    MI_T("MSFT_President"), /* origin */
    MI_T("MSFT_President"), /* propagator */
    NULL,
};

/* property President.Last */
static MI_CONST MI_PropertyDecl President_Last_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C7404, /* code */
    MI_T("Last"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(President, Last), /* offset */
    MI_T("MSFT_President"), /* origin */
    MI_T("MSFT_President"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST President_props[] =
{
    &President_Key_prop,
    &President_First_prop,
    &President_Last_prop,
};

static MI_CONST MI_ProviderFT President_funcs =
{
  (MI_ProviderFT_Load)President_Load,
  (MI_ProviderFT_Unload)President_Unload,
  (MI_ProviderFT_GetInstance)President_GetInstance,
  (MI_ProviderFT_EnumerateInstances)President_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)President_CreateInstance,
  (MI_ProviderFT_ModifyInstance)President_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)President_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class President */
MI_CONST MI_ClassDecl President_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D740E, /* code */
    MI_T("MSFT_President"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    President_props, /* properties */
    MI_COUNT(President_props), /* numProperties */
    sizeof(President), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &President_funcs, /* functions */
};

/*
**==============================================================================
**
** PresidentLink
**
**==============================================================================
*/

/* property PresidentLink.Prev */
static MI_CONST MI_PropertyDecl PresidentLink_Prev_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00707604, /* code */
    MI_T("Prev"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("MSFT_President"), /* className */
    0, /* subscript */
    offsetof(PresidentLink, Prev), /* offset */
    MI_T("MSFT_PresidentLink"), /* origin */
    MI_T("MSFT_PresidentLink"), /* propagator */
    NULL,
};

/* property PresidentLink.Next */
static MI_CONST MI_PropertyDecl PresidentLink_Next_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E7404, /* code */
    MI_T("Next"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("MSFT_President"), /* className */
    0, /* subscript */
    offsetof(PresidentLink, Next), /* offset */
    MI_T("MSFT_PresidentLink"), /* origin */
    MI_T("MSFT_PresidentLink"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST PresidentLink_props[] =
{
    &PresidentLink_Prev_prop,
    &PresidentLink_Next_prop,
};

static MI_CONST MI_ProviderFT PresidentLink_funcs =
{
  (MI_ProviderFT_Load)PresidentLink_Load,
  (MI_ProviderFT_Unload)PresidentLink_Unload,
  (MI_ProviderFT_GetInstance)PresidentLink_GetInstance,
  (MI_ProviderFT_EnumerateInstances)PresidentLink_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)PresidentLink_CreateInstance,
  (MI_ProviderFT_ModifyInstance)PresidentLink_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)PresidentLink_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)PresidentLink_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)PresidentLink_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class PresidentLink */
MI_CONST MI_ClassDecl PresidentLink_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x006D6B12, /* code */
    MI_T("MSFT_PresidentLink"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    PresidentLink_props, /* properties */
    MI_COUNT(PresidentLink_props), /* numProperties */
    sizeof(PresidentLink), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &PresidentLink_funcs, /* functions */
};

/*
**==============================================================================
**
** VicePresident
**
**==============================================================================
*/

/* property VicePresident.Key */
static MI_CONST MI_PropertyDecl VicePresident_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(VicePresident, Key), /* offset */
    MI_T("MSFT_VicePresident"), /* origin */
    MI_T("MSFT_VicePresident"), /* propagator */
    NULL,
};

/* property VicePresident.First */
static MI_CONST MI_PropertyDecl VicePresident_First_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00667405, /* code */
    MI_T("First"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(VicePresident, First), /* offset */
    MI_T("MSFT_VicePresident"), /* origin */
    MI_T("MSFT_VicePresident"), /* propagator */
    NULL,
};

/* property VicePresident.Last */
static MI_CONST MI_PropertyDecl VicePresident_Last_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C7404, /* code */
    MI_T("Last"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(VicePresident, Last), /* offset */
    MI_T("MSFT_VicePresident"), /* origin */
    MI_T("MSFT_VicePresident"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST VicePresident_props[] =
{
    &VicePresident_Key_prop,
    &VicePresident_First_prop,
    &VicePresident_Last_prop,
};

static MI_CONST MI_ProviderFT VicePresident_funcs =
{
  (MI_ProviderFT_Load)VicePresident_Load,
  (MI_ProviderFT_Unload)VicePresident_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)VicePresident_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)VicePresident_CreateInstance,
  (MI_ProviderFT_ModifyInstance)VicePresident_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)VicePresident_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class VicePresident */
MI_CONST MI_ClassDecl VicePresident_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7412, /* code */
    MI_T("MSFT_VicePresident"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    VicePresident_props, /* properties */
    MI_COUNT(VicePresident_props), /* numProperties */
    sizeof(VicePresident), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &VicePresident_funcs, /* functions */
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
    &President_rtti,
    &PresidentLink_rtti,
    &VicePresident_rtti,
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

