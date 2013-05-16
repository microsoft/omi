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
#include "Datetime.h"

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
** Datetime
**
**==============================================================================
*/

/* property Datetime.Key */
static MI_CONST MI_PropertyDecl Datetime_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Datetime, Key), /* offset */
    MI_T("OMI_Datetime"), /* origin */
    MI_T("OMI_Datetime"), /* propagator */
    NULL,
};

/* property Datetime.timestamp */
static MI_CONST MI_PropertyDecl Datetime_timestamp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00747009, /* code */
    MI_T("timestamp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Datetime, timestamp), /* offset */
    MI_T("OMI_Datetime"), /* origin */
    MI_T("OMI_Datetime"), /* propagator */
    NULL,
};

/* property Datetime.interval */
static MI_CONST MI_PropertyDecl Datetime_interval_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00696C08, /* code */
    MI_T("interval"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Datetime, interval), /* offset */
    MI_T("OMI_Datetime"), /* origin */
    MI_T("OMI_Datetime"), /* propagator */
    NULL,
};

/* property Datetime.timestamps */
static MI_CONST MI_PropertyDecl Datetime_timestamps_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0074730A, /* code */
    MI_T("timestamps"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Datetime, timestamps), /* offset */
    MI_T("OMI_Datetime"), /* origin */
    MI_T("OMI_Datetime"), /* propagator */
    NULL,
};

/* property Datetime.intervals */
static MI_CONST MI_PropertyDecl Datetime_intervals_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00697309, /* code */
    MI_T("intervals"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Datetime, intervals), /* offset */
    MI_T("OMI_Datetime"), /* origin */
    MI_T("OMI_Datetime"), /* propagator */
    NULL,
};

/* property Datetime.mixed */
static MI_CONST MI_PropertyDecl Datetime_mixed_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D6405, /* code */
    MI_T("mixed"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Datetime, mixed), /* offset */
    MI_T("OMI_Datetime"), /* origin */
    MI_T("OMI_Datetime"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Datetime_props[] =
{
    &Datetime_Key_prop,
    &Datetime_timestamp_prop,
    &Datetime_interval_prop,
    &Datetime_timestamps_prop,
    &Datetime_intervals_prop,
    &Datetime_mixed_prop,
};

static MI_CONST MI_ProviderFT Datetime_funcs =
{
  (MI_ProviderFT_Load)Datetime_Load,
  (MI_ProviderFT_Unload)Datetime_Unload,
  (MI_ProviderFT_GetInstance)Datetime_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Datetime_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Datetime_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Datetime_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Datetime_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Datetime */
MI_CONST MI_ClassDecl Datetime_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006F650C, /* code */
    MI_T("OMI_Datetime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Datetime_props, /* properties */
    MI_COUNT(Datetime_props), /* numProperties */
    sizeof(Datetime), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Datetime_funcs, /* functions */
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
    &Datetime_rtti,
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

