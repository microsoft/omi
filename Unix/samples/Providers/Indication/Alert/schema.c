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
#include "XYZ_DiskFault.h"

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
** CIM_Indication
**
**==============================================================================
*/

/* property CIM_Indication.IndicationIdentifier */
static MI_CONST MI_PropertyDecl CIM_Indication_IndicationIdentifier_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00697214, /* code */
    MI_T("IndicationIdentifier"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, IndicationIdentifier), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.CorrelatedIndications */
static MI_CONST MI_PropertyDecl CIM_Indication_CorrelatedIndications_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637315, /* code */
    MI_T("CorrelatedIndications"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, CorrelatedIndications), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.IndicationTime */
static MI_CONST MI_PropertyDecl CIM_Indication_IndicationTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069650E, /* code */
    MI_T("IndicationTime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, IndicationTime), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.PerceivedSeverity */
static MI_CONST MI_PropertyDecl CIM_Indication_PerceivedSeverity_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00707911, /* code */
    MI_T("PerceivedSeverity"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, PerceivedSeverity), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.OtherSeverity */
static MI_CONST MI_PropertyDecl CIM_Indication_OtherSeverity_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F790D, /* code */
    MI_T("OtherSeverity"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, OtherSeverity), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.IndicationFilterName */
static MI_CONST MI_PropertyDecl CIM_Indication_IndicationFilterName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00696514, /* code */
    MI_T("IndicationFilterName"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, IndicationFilterName), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.SequenceContext */
static MI_CONST MI_PropertyDecl CIM_Indication_SequenceContext_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073740F, /* code */
    MI_T("SequenceContext"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, SequenceContext), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

/* property CIM_Indication.SequenceNumber */
static MI_CONST MI_PropertyDecl CIM_Indication_SequenceNumber_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073720E, /* code */
    MI_T("SequenceNumber"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Indication, SequenceNumber), /* offset */
    MI_T("CIM_Indication"), /* origin */
    MI_T("CIM_Indication"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Indication_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
};

static MI_CONST MI_Char* CIM_Indication_Version_qual_value = MI_T("2.24.0");

static MI_CONST MI_Qualifier CIM_Indication_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Indication_Version_qual_value
};

static MI_CONST MI_Char* CIM_Indication_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier CIM_Indication_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Indication_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Indication_quals[] =
{
    &CIM_Indication_Version_qual,
    &CIM_Indication_UMLPackagePath_qual,
};

/* class CIM_Indication */
MI_CONST MI_ClassDecl CIM_Indication_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION|MI_FLAG_ABSTRACT, /* flags */
    0x00636E0E, /* code */
    MI_T("CIM_Indication"), /* name */
    CIM_Indication_quals, /* qualifiers */
    MI_COUNT(CIM_Indication_quals), /* numQualifiers */
    CIM_Indication_props, /* properties */
    MI_COUNT(CIM_Indication_props), /* numProperties */
    sizeof(CIM_Indication), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** XYZ_DiskFault
**
**==============================================================================
*/

/* property XYZ_DiskFault.detailmessage */
static MI_CONST MI_PropertyDecl XYZ_DiskFault_detailmessage_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064650D, /* code */
    MI_T("detailmessage"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(XYZ_DiskFault, detailmessage), /* offset */
    MI_T("XYZ_DiskFault"), /* origin */
    MI_T("XYZ_DiskFault"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST XYZ_DiskFault_props[] =
{
    &CIM_Indication_IndicationIdentifier_prop,
    &CIM_Indication_CorrelatedIndications_prop,
    &CIM_Indication_IndicationTime_prop,
    &CIM_Indication_PerceivedSeverity_prop,
    &CIM_Indication_OtherSeverity_prop,
    &CIM_Indication_IndicationFilterName_prop,
    &CIM_Indication_SequenceContext_prop,
    &CIM_Indication_SequenceNumber_prop,
    &XYZ_DiskFault_detailmessage_prop,
};

static MI_CONST MI_ProviderFT XYZ_DiskFault_funcs =
{
  (MI_ProviderFT_Load)XYZ_DiskFault_Load,
  (MI_ProviderFT_Unload)XYZ_DiskFault_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)NULL,
  (MI_ProviderFT_CreateInstance)NULL,
  (MI_ProviderFT_ModifyInstance)NULL,
  (MI_ProviderFT_DeleteInstance)NULL,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)XYZ_DiskFault_EnableIndications,
  (MI_ProviderFT_DisableIndications)XYZ_DiskFault_DisableIndications,
  (MI_ProviderFT_Subscribe)XYZ_DiskFault_Subscribe,
  (MI_ProviderFT_Unsubscribe)XYZ_DiskFault_Unsubscribe,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* XYZ_DiskFault_UMLPackagePath_qual_value = MI_T("CIM::Event");

static MI_CONST MI_Qualifier XYZ_DiskFault_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &XYZ_DiskFault_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST XYZ_DiskFault_quals[] =
{
    &XYZ_DiskFault_UMLPackagePath_qual,
};

/* class XYZ_DiskFault */
MI_CONST MI_ClassDecl XYZ_DiskFault_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x0078740D, /* code */
    MI_T("XYZ_DiskFault"), /* name */
    XYZ_DiskFault_quals, /* qualifiers */
    MI_COUNT(XYZ_DiskFault_quals), /* numQualifiers */
    XYZ_DiskFault_props, /* properties */
    MI_COUNT(XYZ_DiskFault_props), /* numProperties */
    sizeof(XYZ_DiskFault), /* size */
    MI_T("CIM_Indication"), /* superClass */
    &CIM_Indication_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &XYZ_DiskFault_funcs, /* functions */
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
    &CIM_Indication_rtti,
    &XYZ_DiskFault_rtti,
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

