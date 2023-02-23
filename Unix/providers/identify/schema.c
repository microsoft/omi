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
#include "Identify.h"

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
** Identify
**
**==============================================================================
*/

/* property Identify.InstanceID */
static MI_CONST MI_PropertyDecl Identify_InstanceID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0069640A, /* code */
    MI_T("InstanceID"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, InstanceID), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.SystemName */
static MI_CONST MI_PropertyDecl Identify_SystemName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073650A, /* code */
    MI_T("SystemName"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, SystemName), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ProductName */
static MI_CONST MI_PropertyDecl Identify_ProductName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070650B, /* code */
    MI_T("ProductName"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ProductName), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ProductVendor */
static MI_CONST MI_PropertyDecl Identify_ProductVendor_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070720D, /* code */
    MI_T("ProductVendor"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ProductVendor), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ProductVersionMajor */
static MI_CONST MI_PropertyDecl Identify_ProductVersionMajor_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00707213, /* code */
    MI_T("ProductVersionMajor"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ProductVersionMajor), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ProductVersionMinor */
static MI_CONST MI_PropertyDecl Identify_ProductVersionMinor_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00707213, /* code */
    MI_T("ProductVersionMinor"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ProductVersionMinor), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ProductVersionRevision */
static MI_CONST MI_PropertyDecl Identify_ProductVersionRevision_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706E16, /* code */
    MI_T("ProductVersionRevision"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ProductVersionRevision), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ProductVersionString */
static MI_CONST MI_PropertyDecl Identify_ProductVersionString_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706714, /* code */
    MI_T("ProductVersionString"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ProductVersionString), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.Platform */
static MI_CONST MI_PropertyDecl Identify_Platform_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706D08, /* code */
    MI_T("Platform"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, Platform), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.OperatingSystem */
static MI_CONST MI_PropertyDecl Identify_OperatingSystem_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6D0F, /* code */
    MI_T("OperatingSystem"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, OperatingSystem), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.Architecture */
static MI_CONST MI_PropertyDecl Identify_Architecture_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0061650C, /* code */
    MI_T("Architecture"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, Architecture), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.Compiler */
static MI_CONST MI_PropertyDecl Identify_Compiler_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637208, /* code */
    MI_T("Compiler"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, Compiler), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ConfigPrefix */
static MI_CONST MI_PropertyDecl Identify_ConfigPrefix_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063780C, /* code */
    MI_T("ConfigPrefix"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ConfigPrefix), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ConfigLibDir */
static MI_CONST MI_PropertyDecl Identify_ConfigLibDir_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063720C, /* code */
    MI_T("ConfigLibDir"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ConfigLibDir), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ConfigBinDir */
static MI_CONST MI_PropertyDecl Identify_ConfigBinDir_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063720C, /* code */
    MI_T("ConfigBinDir"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ConfigBinDir), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ConfigIncludeDir */
static MI_CONST MI_PropertyDecl Identify_ConfigIncludeDir_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637210, /* code */
    MI_T("ConfigIncludeDir"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ConfigIncludeDir), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ConfigDataDir */
static MI_CONST MI_PropertyDecl Identify_ConfigDataDir_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063720D, /* code */
    MI_T("ConfigDataDir"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ConfigDataDir), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ConfigLocalStateDir */
static MI_CONST MI_PropertyDecl Identify_ConfigLocalStateDir_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637213, /* code */
    MI_T("ConfigLocalStateDir"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ConfigLocalStateDir), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ConfigSysConfDir */
static MI_CONST MI_PropertyDecl Identify_ConfigSysConfDir_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637210, /* code */
    MI_T("ConfigSysConfDir"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ConfigSysConfDir), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ConfigProviderDir */
static MI_CONST MI_PropertyDecl Identify_ConfigProviderDir_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637211, /* code */
    MI_T("ConfigProviderDir"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ConfigProviderDir), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ConfigLogFile */
static MI_CONST MI_PropertyDecl Identify_ConfigLogFile_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063650D, /* code */
    MI_T("ConfigLogFile"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ConfigLogFile), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ConfigPIDFile */
static MI_CONST MI_PropertyDecl Identify_ConfigPIDFile_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063650D, /* code */
    MI_T("ConfigPIDFile"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ConfigPIDFile), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ConfigRegisterDir */
static MI_CONST MI_PropertyDecl Identify_ConfigRegisterDir_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637211, /* code */
    MI_T("ConfigRegisterDir"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ConfigRegisterDir), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ConfigSchemaDir */
static MI_CONST MI_PropertyDecl Identify_ConfigSchemaDir_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063720F, /* code */
    MI_T("ConfigSchemaDir"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ConfigSchemaDir), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

/* property Identify.ConfigNameSpaces */
static MI_CONST MI_PropertyDecl Identify_ConfigNameSpaces_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637310, /* code */
    MI_T("ConfigNameSpaces"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Identify, ConfigNameSpaces), /* offset */
    MI_T("OMI_Identify"), /* origin */
    MI_T("OMI_Identify"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Identify_props[] =
{
    &Identify_InstanceID_prop,
    &Identify_SystemName_prop,
    &Identify_ProductName_prop,
    &Identify_ProductVendor_prop,
    &Identify_ProductVersionMajor_prop,
    &Identify_ProductVersionMinor_prop,
    &Identify_ProductVersionRevision_prop,
    &Identify_ProductVersionString_prop,
    &Identify_Platform_prop,
    &Identify_OperatingSystem_prop,
    &Identify_Architecture_prop,
    &Identify_Compiler_prop,
    &Identify_ConfigPrefix_prop,
    &Identify_ConfigLibDir_prop,
    &Identify_ConfigBinDir_prop,
    &Identify_ConfigIncludeDir_prop,
    &Identify_ConfigDataDir_prop,
    &Identify_ConfigLocalStateDir_prop,
    &Identify_ConfigSysConfDir_prop,
    &Identify_ConfigProviderDir_prop,
    &Identify_ConfigLogFile_prop,
    &Identify_ConfigPIDFile_prop,
    &Identify_ConfigRegisterDir_prop,
    &Identify_ConfigSchemaDir_prop,
    &Identify_ConfigNameSpaces_prop,
};

static MI_CONST MI_ProviderFT Identify_funcs =
{
  (MI_ProviderFT_Load)Identify_Load,
  (MI_ProviderFT_Unload)Identify_Unload,
  (MI_ProviderFT_GetInstance)Identify_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Identify_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Identify_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Identify_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Identify_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Identify */
MI_CONST MI_ClassDecl Identify_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006F790C, /* code */
    MI_T("OMI_Identify"), /* name */
	(struct _MI_Qualifier**)NULL, /* qualifiers */
    0, /* numQualifiers */
    (struct _MI_PropertyDecl**)Identify_props, /* properties */
    MI_COUNT(Identify_props), /* numProperties */
    sizeof(Identify), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Identify_funcs, /* functions */
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
    &Identify_rtti,
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

