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
#include "Hosts.h"

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
** Hosts
**
**==============================================================================
*/

/* property Hosts.FQDN */
static MI_CONST MI_PropertyDecl Hosts_FQDN_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00666E04, /* code */
    MI_T("FQDN"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Hosts, FQDN), /* offset */
    MI_T("Hosts"), /* origin */
    MI_T("Hosts"), /* propagator */
    NULL,
};

/* property Hosts.IPAddress */
static MI_CONST MI_PropertyDecl Hosts_IPAddress_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00697309, /* code */
    MI_T("IPAddress"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Hosts, IPAddress), /* offset */
    MI_T("Hosts"), /* origin */
    MI_T("Hosts"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Hosts_props[] =
{
    &Hosts_FQDN_prop,
    &Hosts_IPAddress_prop,
};

/* parameter Hosts.Ping(): MIReturn */
static MI_CONST MI_ParameterDecl Hosts_Ping_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Hosts_Ping, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Hosts_Ping_params[] =
{
    &Hosts_Ping_MIReturn_param,
};

/* method Hosts.Ping() */
MI_CONST MI_MethodDecl Hosts_Ping_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00706704, /* code */
    MI_T("Ping"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Hosts_Ping_params, /* parameters */
    MI_COUNT(Hosts_Ping_params), /* numParameters */
    sizeof(Hosts_Ping), /* size */
    MI_UINT64, /* returnType */
    MI_T("Hosts"), /* origin */
    MI_T("Hosts"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Hosts_Invoke_Ping, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST Hosts_meths[] =
{
    &Hosts_Ping_rtti,
};

static MI_CONST MI_ProviderFT Hosts_funcs =
{
  (MI_ProviderFT_Load)Hosts_Load,
  (MI_ProviderFT_Unload)Hosts_Unload,
  (MI_ProviderFT_GetInstance)Hosts_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Hosts_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Hosts_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Hosts_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Hosts_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Hosts */
MI_CONST MI_ClassDecl Hosts_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00687305, /* code */
    MI_T("Hosts"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Hosts_props, /* properties */
    MI_COUNT(Hosts_props), /* numProperties */
    sizeof(Hosts), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    Hosts_meths, /* methods */
    MI_COUNT(Hosts_meths), /* numMethods */
    &schemaDecl, /* schema */
    &Hosts_funcs, /* functions */
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
    &Hosts_rtti,
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

