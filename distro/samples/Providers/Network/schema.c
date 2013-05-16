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
#include "ABC_EthernetPort.h"
#include "ABC_VLANEndpoint.h"

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
** CIM_ManagedElement
**
**==============================================================================
*/

/* property CIM_ManagedElement.InstanceID */
static MI_CONST MI_PropertyDecl CIM_ManagedElement_InstanceID_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069640A, /* code */
    MI_T("InstanceID"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedElement, InstanceID), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_ManagedElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_ManagedElement_Caption_MaxLen_qual_value = 64U;

static MI_CONST MI_Qualifier CIM_ManagedElement_Caption_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ManagedElement_Caption_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedElement_Caption_quals[] =
{
    &CIM_ManagedElement_Caption_MaxLen_qual,
};

/* property CIM_ManagedElement.Caption */
static MI_CONST MI_PropertyDecl CIM_ManagedElement_Caption_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00636E07, /* code */
    MI_T("Caption"), /* name */
    CIM_ManagedElement_Caption_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedElement_Caption_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedElement, Caption), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_ManagedElement"), /* propagator */
    NULL,
};

/* property CIM_ManagedElement.Description */
static MI_CONST MI_PropertyDecl CIM_ManagedElement_Description_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E0B, /* code */
    MI_T("Description"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedElement, Description), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_ManagedElement"), /* propagator */
    NULL,
};

/* property CIM_ManagedElement.ElementName */
static MI_CONST MI_PropertyDecl CIM_ManagedElement_ElementName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065650B, /* code */
    MI_T("ElementName"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedElement, ElementName), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_ManagedElement"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_ManagedElement_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
};

static MI_CONST MI_Char* CIM_ManagedElement_Version_qual_value = MI_T("2.19.0");

static MI_CONST MI_Qualifier CIM_ManagedElement_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_ManagedElement_Version_qual_value
};

static MI_CONST MI_Char* CIM_ManagedElement_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_ManagedElement_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_ManagedElement_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedElement_quals[] =
{
    &CIM_ManagedElement_Version_qual,
    &CIM_ManagedElement_UMLPackagePath_qual,
};

/* class CIM_ManagedElement */
MI_CONST MI_ClassDecl CIM_ManagedElement_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00637412, /* code */
    MI_T("CIM_ManagedElement"), /* name */
    CIM_ManagedElement_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedElement_quals), /* numQualifiers */
    CIM_ManagedElement_props, /* properties */
    MI_COUNT(CIM_ManagedElement_props), /* numProperties */
    sizeof(CIM_ManagedElement), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_ManagedSystemElement
**
**==============================================================================
*/

/* property CIM_ManagedSystemElement.InstallDate */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_InstallDate_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069650B, /* code */
    MI_T("InstallDate"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, InstallDate), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_ManagedSystemElement_Name_MaxLen_qual_value = 1024U;

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_Name_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ManagedSystemElement_Name_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_Name_quals[] =
{
    &CIM_ManagedSystemElement_Name_MaxLen_qual,
};

/* property CIM_ManagedSystemElement.Name */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_Name_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    CIM_ManagedSystemElement_Name_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_Name_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, Name), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_OperationalStatus_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_OperationalStatus_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_ManagedSystemElement_OperationalStatus_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_OperationalStatus_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ManagedSystemElement.StatusDescriptions"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_OperationalStatus_ModelCorrespondence_qual_value =
{
    CIM_ManagedSystemElement_OperationalStatus_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_OperationalStatus_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_OperationalStatus_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_OperationalStatus_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_OperationalStatus_quals[] =
{
    &CIM_ManagedSystemElement_OperationalStatus_ArrayType_qual,
    &CIM_ManagedSystemElement_OperationalStatus_ModelCorrespondence_qual,
};

/* property CIM_ManagedSystemElement.OperationalStatus */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_OperationalStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F7311, /* code */
    MI_T("OperationalStatus"), /* name */
    CIM_ManagedSystemElement_OperationalStatus_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_OperationalStatus_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, OperationalStatus), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_StatusDescriptions_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_StatusDescriptions_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_ManagedSystemElement_StatusDescriptions_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_StatusDescriptions_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ManagedSystemElement.OperationalStatus"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_StatusDescriptions_ModelCorrespondence_qual_value =
{
    CIM_ManagedSystemElement_StatusDescriptions_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_StatusDescriptions_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_StatusDescriptions_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_StatusDescriptions_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_StatusDescriptions_quals[] =
{
    &CIM_ManagedSystemElement_StatusDescriptions_ArrayType_qual,
    &CIM_ManagedSystemElement_StatusDescriptions_ModelCorrespondence_qual,
};

/* property CIM_ManagedSystemElement.StatusDescriptions */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_StatusDescriptions_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737312, /* code */
    MI_T("StatusDescriptions"), /* name */
    CIM_ManagedSystemElement_StatusDescriptions_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_StatusDescriptions_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, StatusDescriptions), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_Status_Deprecated_qual_data_value[] =
{
    MI_T("CIM_ManagedSystemElement.OperationalStatus"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_Status_Deprecated_qual_value =
{
    CIM_ManagedSystemElement_Status_Deprecated_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_Status_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_Status_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ManagedSystemElement_Status_Deprecated_qual_value
};

static MI_CONST MI_Uint32 CIM_ManagedSystemElement_Status_MaxLen_qual_value = 10U;

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_Status_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ManagedSystemElement_Status_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_Status_quals[] =
{
    &CIM_ManagedSystemElement_Status_Deprecated_qual,
    &CIM_ManagedSystemElement_Status_MaxLen_qual,
};

/* property CIM_ManagedSystemElement.Status */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_Status_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737306, /* code */
    MI_T("Status"), /* name */
    CIM_ManagedSystemElement_Status_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_Status_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, Status), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

/* property CIM_ManagedSystemElement.HealthState */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_HealthState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0068650B, /* code */
    MI_T("HealthState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, HealthState), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

/* property CIM_ManagedSystemElement.CommunicationStatus */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_CommunicationStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637313, /* code */
    MI_T("CommunicationStatus"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, CommunicationStatus), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_DetailedStatus_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.PrimaryStatus"),
    MI_T("CIM_ManagedSystemElement.HealthState"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_DetailedStatus_ModelCorrespondence_qual_value =
{
    CIM_ManagedSystemElement_DetailedStatus_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_DetailedStatus_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_DetailedStatus_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_DetailedStatus_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_DetailedStatus_quals[] =
{
    &CIM_ManagedSystemElement_DetailedStatus_ModelCorrespondence_qual,
};

/* property CIM_ManagedSystemElement.DetailedStatus */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_DetailedStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064730E, /* code */
    MI_T("DetailedStatus"), /* name */
    CIM_ManagedSystemElement_DetailedStatus_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_DetailedStatus_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, DetailedStatus), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_OperatingStatus_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.EnabledState"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_OperatingStatus_ModelCorrespondence_qual_value =
{
    CIM_ManagedSystemElement_OperatingStatus_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_OperatingStatus_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_OperatingStatus_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_OperatingStatus_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_OperatingStatus_quals[] =
{
    &CIM_ManagedSystemElement_OperatingStatus_ModelCorrespondence_qual,
};

/* property CIM_ManagedSystemElement.OperatingStatus */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_OperatingStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F730F, /* code */
    MI_T("OperatingStatus"), /* name */
    CIM_ManagedSystemElement_OperatingStatus_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_OperatingStatus_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, OperatingStatus), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_PrimaryStatus_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ManagedSystemElement.DetailedStatus"),
    MI_T("CIM_ManagedSystemElement.HealthState"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_PrimaryStatus_ModelCorrespondence_qual_value =
{
    CIM_ManagedSystemElement_PrimaryStatus_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_PrimaryStatus_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_PrimaryStatus_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_ManagedSystemElement_PrimaryStatus_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_PrimaryStatus_quals[] =
{
    &CIM_ManagedSystemElement_PrimaryStatus_ModelCorrespondence_qual,
};

/* property CIM_ManagedSystemElement.PrimaryStatus */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_PrimaryStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070730D, /* code */
    MI_T("PrimaryStatus"), /* name */
    CIM_ManagedSystemElement_PrimaryStatus_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_PrimaryStatus_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, PrimaryStatus), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_ManagedSystemElement_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_ManagedSystemElement_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_Version_qual_value = MI_T("2.28.0");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_ManagedSystemElement_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_quals[] =
{
    &CIM_ManagedSystemElement_UMLPackagePath_qual,
    &CIM_ManagedSystemElement_Version_qual,
};

/* class CIM_ManagedSystemElement */
MI_CONST MI_ClassDecl CIM_ManagedSystemElement_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00637418, /* code */
    MI_T("CIM_ManagedSystemElement"), /* name */
    CIM_ManagedSystemElement_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_quals), /* numQualifiers */
    CIM_ManagedSystemElement_props, /* properties */
    MI_COUNT(CIM_ManagedSystemElement_props), /* numProperties */
    sizeof(CIM_ManagedSystemElement), /* size */
    MI_T("CIM_ManagedElement"), /* superClass */
    &CIM_ManagedElement_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_LogicalElement
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST CIM_LogicalElement_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
};

static MI_CONST MI_Char* CIM_LogicalElement_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_LogicalElement_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_LogicalElement_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_LogicalElement_Version_qual_value = MI_T("2.6.0");

static MI_CONST MI_Qualifier CIM_LogicalElement_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_LogicalElement_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalElement_quals[] =
{
    &CIM_LogicalElement_UMLPackagePath_qual,
    &CIM_LogicalElement_Version_qual,
};

/* class CIM_LogicalElement */
MI_CONST MI_ClassDecl CIM_LogicalElement_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00637412, /* code */
    MI_T("CIM_LogicalElement"), /* name */
    CIM_LogicalElement_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalElement_quals), /* numQualifiers */
    CIM_LogicalElement_props, /* properties */
    MI_COUNT(CIM_LogicalElement_props), /* numProperties */
    sizeof(CIM_LogicalElement), /* size */
    MI_T("CIM_ManagedSystemElement"), /* superClass */
    &CIM_ManagedSystemElement_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_Job
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_Job_JobStatus_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ManagedSystemElement.OperationalStatus"),
};

static MI_CONST MI_ConstStringA CIM_Job_JobStatus_ModelCorrespondence_qual_value =
{
    CIM_Job_JobStatus_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_JobStatus_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_JobStatus_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_JobStatus_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_JobStatus_quals[] =
{
    &CIM_Job_JobStatus_ModelCorrespondence_qual,
};

/* property CIM_Job.JobStatus */
static MI_CONST MI_PropertyDecl CIM_Job_JobStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006A7309, /* code */
    MI_T("JobStatus"), /* name */
    CIM_Job_JobStatus_quals, /* qualifiers */
    MI_COUNT(CIM_Job_JobStatus_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, JobStatus), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.TimeSubmitted */
static MI_CONST MI_PropertyDecl CIM_Job_TimeSubmitted_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0074640D, /* code */
    MI_T("TimeSubmitted"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, TimeSubmitted), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_ScheduledStartTime_Deprecated_qual_data_value[] =
{
    MI_T("CIM_Job.RunMonth"),
    MI_T("CIM_Job.RunDay"),
    MI_T("CIM_Job.RunDayOfWeek"),
    MI_T("CIM_Job.RunStartInterval"),
};

static MI_CONST MI_ConstStringA CIM_Job_ScheduledStartTime_Deprecated_qual_value =
{
    CIM_Job_ScheduledStartTime_Deprecated_qual_data_value,
    MI_COUNT(CIM_Job_ScheduledStartTime_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_ScheduledStartTime_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_Job_ScheduledStartTime_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_ScheduledStartTime_quals[] =
{
    &CIM_Job_ScheduledStartTime_Deprecated_qual,
};

/* property CIM_Job.ScheduledStartTime */
static MI_CONST MI_PropertyDecl CIM_Job_ScheduledStartTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736512, /* code */
    MI_T("ScheduledStartTime"), /* name */
    CIM_Job_ScheduledStartTime_quals, /* qualifiers */
    MI_COUNT(CIM_Job_ScheduledStartTime_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, ScheduledStartTime), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.StartTime */
static MI_CONST MI_PropertyDecl CIM_Job_StartTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736509, /* code */
    MI_T("StartTime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, StartTime), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.ElapsedTime */
static MI_CONST MI_PropertyDecl CIM_Job_ElapsedTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065650B, /* code */
    MI_T("ElapsedTime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, ElapsedTime), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_Job_JobRunTimes_value = 1U;

/* property CIM_Job.JobRunTimes */
static MI_CONST MI_PropertyDecl CIM_Job_JobRunTimes_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006A730B, /* code */
    MI_T("JobRunTimes"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, JobRunTimes), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    &CIM_Job_JobRunTimes_value,
};

static MI_CONST MI_Char* CIM_Job_RunMonth_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.RunDay"),
    MI_T("CIM_Job.RunDayOfWeek"),
    MI_T("CIM_Job.RunStartInterval"),
};

static MI_CONST MI_ConstStringA CIM_Job_RunMonth_ModelCorrespondence_qual_value =
{
    CIM_Job_RunMonth_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_RunMonth_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_RunMonth_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_RunMonth_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_RunMonth_quals[] =
{
    &CIM_Job_RunMonth_ModelCorrespondence_qual,
};

/* property CIM_Job.RunMonth */
static MI_CONST MI_PropertyDecl CIM_Job_RunMonth_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726808, /* code */
    MI_T("RunMonth"), /* name */
    CIM_Job_RunMonth_quals, /* qualifiers */
    MI_COUNT(CIM_Job_RunMonth_quals), /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, RunMonth), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Sint64 CIM_Job_RunDay_MinValue_qual_value = -MI_LL(31);

static MI_CONST MI_Qualifier CIM_Job_RunDay_MinValue_qual =
{
    MI_T("MinValue"),
    MI_SINT64,
    0,
    &CIM_Job_RunDay_MinValue_qual_value
};

static MI_CONST MI_Sint64 CIM_Job_RunDay_MaxValue_qual_value = MI_LL(31);

static MI_CONST MI_Qualifier CIM_Job_RunDay_MaxValue_qual =
{
    MI_T("MaxValue"),
    MI_SINT64,
    0,
    &CIM_Job_RunDay_MaxValue_qual_value
};

static MI_CONST MI_Char* CIM_Job_RunDay_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.RunMonth"),
    MI_T("CIM_Job.RunDayOfWeek"),
    MI_T("CIM_Job.RunStartInterval"),
};

static MI_CONST MI_ConstStringA CIM_Job_RunDay_ModelCorrespondence_qual_value =
{
    CIM_Job_RunDay_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_RunDay_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_RunDay_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_RunDay_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_RunDay_quals[] =
{
    &CIM_Job_RunDay_MinValue_qual,
    &CIM_Job_RunDay_MaxValue_qual,
    &CIM_Job_RunDay_ModelCorrespondence_qual,
};

/* property CIM_Job.RunDay */
static MI_CONST MI_PropertyDecl CIM_Job_RunDay_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00727906, /* code */
    MI_T("RunDay"), /* name */
    CIM_Job_RunDay_quals, /* qualifiers */
    MI_COUNT(CIM_Job_RunDay_quals), /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, RunDay), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_RunDayOfWeek_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.RunMonth"),
    MI_T("CIM_Job.RunDay"),
    MI_T("CIM_Job.RunStartInterval"),
};

static MI_CONST MI_ConstStringA CIM_Job_RunDayOfWeek_ModelCorrespondence_qual_value =
{
    CIM_Job_RunDayOfWeek_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_RunDayOfWeek_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_RunDayOfWeek_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_RunDayOfWeek_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_RunDayOfWeek_quals[] =
{
    &CIM_Job_RunDayOfWeek_ModelCorrespondence_qual,
};

/* property CIM_Job.RunDayOfWeek */
static MI_CONST MI_PropertyDecl CIM_Job_RunDayOfWeek_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726B0C, /* code */
    MI_T("RunDayOfWeek"), /* name */
    CIM_Job_RunDayOfWeek_quals, /* qualifiers */
    MI_COUNT(CIM_Job_RunDayOfWeek_quals), /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, RunDayOfWeek), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_RunStartInterval_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.RunMonth"),
    MI_T("CIM_Job.RunDay"),
    MI_T("CIM_Job.RunDayOfWeek"),
    MI_T("CIM_Job.RunStartInterval"),
};

static MI_CONST MI_ConstStringA CIM_Job_RunStartInterval_ModelCorrespondence_qual_value =
{
    CIM_Job_RunStartInterval_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_RunStartInterval_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_RunStartInterval_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_RunStartInterval_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_RunStartInterval_quals[] =
{
    &CIM_Job_RunStartInterval_ModelCorrespondence_qual,
};

/* property CIM_Job.RunStartInterval */
static MI_CONST MI_PropertyDecl CIM_Job_RunStartInterval_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726C10, /* code */
    MI_T("RunStartInterval"), /* name */
    CIM_Job_RunStartInterval_quals, /* qualifiers */
    MI_COUNT(CIM_Job_RunStartInterval_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, RunStartInterval), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.LocalOrUtcTime */
static MI_CONST MI_PropertyDecl CIM_Job_LocalOrUtcTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C650E, /* code */
    MI_T("LocalOrUtcTime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, LocalOrUtcTime), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_UntilTime_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.LocalOrUtcTime"),
};

static MI_CONST MI_ConstStringA CIM_Job_UntilTime_ModelCorrespondence_qual_value =
{
    CIM_Job_UntilTime_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_UntilTime_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_UntilTime_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_UntilTime_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_UntilTime_quals[] =
{
    &CIM_Job_UntilTime_ModelCorrespondence_qual,
};

/* property CIM_Job.UntilTime */
static MI_CONST MI_PropertyDecl CIM_Job_UntilTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756509, /* code */
    MI_T("UntilTime"), /* name */
    CIM_Job_UntilTime_quals, /* qualifiers */
    MI_COUNT(CIM_Job_UntilTime_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, UntilTime), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.Notify */
static MI_CONST MI_PropertyDecl CIM_Job_Notify_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E7906, /* code */
    MI_T("Notify"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, Notify), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_Owner_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_OwningJobElement"),
};

static MI_CONST MI_ConstStringA CIM_Job_Owner_ModelCorrespondence_qual_value =
{
    CIM_Job_Owner_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_Owner_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_Owner_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_Owner_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_Owner_quals[] =
{
    &CIM_Job_Owner_ModelCorrespondence_qual,
};

/* property CIM_Job.Owner */
static MI_CONST MI_PropertyDecl CIM_Job_Owner_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F7205, /* code */
    MI_T("Owner"), /* name */
    CIM_Job_Owner_quals, /* qualifiers */
    MI_COUNT(CIM_Job_Owner_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, Owner), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.Priority */
static MI_CONST MI_PropertyDecl CIM_Job_Priority_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00707908, /* code */
    MI_T("Priority"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, Priority), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_PercentComplete_Units_qual_value = MI_T("Percent");

static MI_CONST MI_Qualifier CIM_Job_PercentComplete_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_PercentComplete_Units_qual_value
};

static MI_CONST MI_Sint64 CIM_Job_PercentComplete_MinValue_qual_value = MI_LL(0);

static MI_CONST MI_Qualifier CIM_Job_PercentComplete_MinValue_qual =
{
    MI_T("MinValue"),
    MI_SINT64,
    0,
    &CIM_Job_PercentComplete_MinValue_qual_value
};

static MI_CONST MI_Sint64 CIM_Job_PercentComplete_MaxValue_qual_value = MI_LL(101);

static MI_CONST MI_Qualifier CIM_Job_PercentComplete_MaxValue_qual =
{
    MI_T("MaxValue"),
    MI_SINT64,
    0,
    &CIM_Job_PercentComplete_MaxValue_qual_value
};

static MI_CONST MI_Char* CIM_Job_PercentComplete_PUnit_qual_value = MI_T("percent");

static MI_CONST MI_Qualifier CIM_Job_PercentComplete_PUnit_qual =
{
    MI_T("PUnit"),
    MI_STRING,
    0,
    &CIM_Job_PercentComplete_PUnit_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_PercentComplete_quals[] =
{
    &CIM_Job_PercentComplete_Units_qual,
    &CIM_Job_PercentComplete_MinValue_qual,
    &CIM_Job_PercentComplete_MaxValue_qual,
    &CIM_Job_PercentComplete_PUnit_qual,
};

/* property CIM_Job.PercentComplete */
static MI_CONST MI_PropertyDecl CIM_Job_PercentComplete_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070650F, /* code */
    MI_T("PercentComplete"), /* name */
    CIM_Job_PercentComplete_quals, /* qualifiers */
    MI_COUNT(CIM_Job_PercentComplete_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, PercentComplete), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.DeleteOnCompletion */
static MI_CONST MI_PropertyDecl CIM_Job_DeleteOnCompletion_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E12, /* code */
    MI_T("DeleteOnCompletion"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, DeleteOnCompletion), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_ErrorCode_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.ErrorDescription"),
};

static MI_CONST MI_ConstStringA CIM_Job_ErrorCode_ModelCorrespondence_qual_value =
{
    CIM_Job_ErrorCode_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_ErrorCode_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_ErrorCode_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_ErrorCode_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_ErrorCode_quals[] =
{
    &CIM_Job_ErrorCode_ModelCorrespondence_qual,
};

/* property CIM_Job.ErrorCode */
static MI_CONST MI_PropertyDecl CIM_Job_ErrorCode_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656509, /* code */
    MI_T("ErrorCode"), /* name */
    CIM_Job_ErrorCode_quals, /* qualifiers */
    MI_COUNT(CIM_Job_ErrorCode_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, ErrorCode), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_ErrorDescription_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.ErrorCode"),
};

static MI_CONST MI_ConstStringA CIM_Job_ErrorDescription_ModelCorrespondence_qual_value =
{
    CIM_Job_ErrorDescription_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_ErrorDescription_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_ErrorDescription_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_ErrorDescription_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_ErrorDescription_quals[] =
{
    &CIM_Job_ErrorDescription_ModelCorrespondence_qual,
};

/* property CIM_Job.ErrorDescription */
static MI_CONST MI_PropertyDecl CIM_Job_ErrorDescription_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656E10, /* code */
    MI_T("ErrorDescription"), /* name */
    CIM_Job_ErrorDescription_quals, /* qualifiers */
    MI_COUNT(CIM_Job_ErrorDescription_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, ErrorDescription), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_RecoveryAction_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.OtherRecoveryAction"),
};

static MI_CONST MI_ConstStringA CIM_Job_RecoveryAction_ModelCorrespondence_qual_value =
{
    CIM_Job_RecoveryAction_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_RecoveryAction_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_RecoveryAction_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_RecoveryAction_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_RecoveryAction_quals[] =
{
    &CIM_Job_RecoveryAction_ModelCorrespondence_qual,
};

/* property CIM_Job.RecoveryAction */
static MI_CONST MI_PropertyDecl CIM_Job_RecoveryAction_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726E0E, /* code */
    MI_T("RecoveryAction"), /* name */
    CIM_Job_RecoveryAction_quals, /* qualifiers */
    MI_COUNT(CIM_Job_RecoveryAction_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, RecoveryAction), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_OtherRecoveryAction_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Job.RecoveryAction"),
};

static MI_CONST MI_ConstStringA CIM_Job_OtherRecoveryAction_ModelCorrespondence_qual_value =
{
    CIM_Job_OtherRecoveryAction_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Job_OtherRecoveryAction_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_OtherRecoveryAction_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Job_OtherRecoveryAction_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_OtherRecoveryAction_quals[] =
{
    &CIM_Job_OtherRecoveryAction_ModelCorrespondence_qual,
};

/* property CIM_Job.OtherRecoveryAction */
static MI_CONST MI_PropertyDecl CIM_Job_OtherRecoveryAction_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6E13, /* code */
    MI_T("OtherRecoveryAction"), /* name */
    CIM_Job_OtherRecoveryAction_quals, /* qualifiers */
    MI_COUNT(CIM_Job_OtherRecoveryAction_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, OtherRecoveryAction), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Job_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_Job_JobStatus_prop,
    &CIM_Job_TimeSubmitted_prop,
    &CIM_Job_ScheduledStartTime_prop,
    &CIM_Job_StartTime_prop,
    &CIM_Job_ElapsedTime_prop,
    &CIM_Job_JobRunTimes_prop,
    &CIM_Job_RunMonth_prop,
    &CIM_Job_RunDay_prop,
    &CIM_Job_RunDayOfWeek_prop,
    &CIM_Job_RunStartInterval_prop,
    &CIM_Job_LocalOrUtcTime_prop,
    &CIM_Job_UntilTime_prop,
    &CIM_Job_Notify_prop,
    &CIM_Job_Owner_prop,
    &CIM_Job_Priority_prop,
    &CIM_Job_PercentComplete_prop,
    &CIM_Job_DeleteOnCompletion_prop,
    &CIM_Job_ErrorCode_prop,
    &CIM_Job_ErrorDescription_prop,
    &CIM_Job_RecoveryAction_prop,
    &CIM_Job_OtherRecoveryAction_prop,
};

static MI_CONST MI_Char* CIM_Job_KillJob_Deprecated_qual_data_value[] =
{
    MI_T("CIM_ConcreteJob.RequestStateChange()"),
};

static MI_CONST MI_ConstStringA CIM_Job_KillJob_Deprecated_qual_value =
{
    CIM_Job_KillJob_Deprecated_qual_data_value,
    MI_COUNT(CIM_Job_KillJob_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_KillJob_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_Job_KillJob_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_KillJob_quals[] =
{
    &CIM_Job_KillJob_Deprecated_qual,
};

/* parameter CIM_Job.KillJob(): DeleteOnKill */
static MI_CONST MI_ParameterDecl CIM_Job_KillJob_DeleteOnKill_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00646C0C, /* code */
    MI_T("DeleteOnKill"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job_KillJob, DeleteOnKill), /* offset */
};

static MI_CONST MI_Char* CIM_Job_KillJob_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_ConcreteJob.RequestStateChange()"),
};

static MI_CONST MI_ConstStringA CIM_Job_KillJob_MIReturn_Deprecated_qual_value =
{
    CIM_Job_KillJob_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(CIM_Job_KillJob_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_KillJob_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_Job_KillJob_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_KillJob_MIReturn_quals[] =
{
    &CIM_Job_KillJob_MIReturn_Deprecated_qual,
};

/* parameter CIM_Job.KillJob(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_Job_KillJob_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    CIM_Job_KillJob_MIReturn_quals, /* qualifiers */
    MI_COUNT(CIM_Job_KillJob_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job_KillJob, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_Job_KillJob_params[] =
{
    &CIM_Job_KillJob_MIReturn_param,
    &CIM_Job_KillJob_DeleteOnKill_param,
};

/* method CIM_Job.KillJob() */
MI_CONST MI_MethodDecl CIM_Job_KillJob_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006B6207, /* code */
    MI_T("KillJob"), /* name */
    CIM_Job_KillJob_quals, /* qualifiers */
    MI_COUNT(CIM_Job_KillJob_quals), /* numQualifiers */
    CIM_Job_KillJob_params, /* parameters */
    MI_COUNT(CIM_Job_KillJob_params), /* numParameters */
    sizeof(CIM_Job_KillJob), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_Job_meths[] =
{
    &CIM_Job_KillJob_rtti,
};

static MI_CONST MI_Char* CIM_Job_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_Job_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Job_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_Job_Version_qual_value = MI_T("2.10.0");

static MI_CONST MI_Qualifier CIM_Job_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Job_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_quals[] =
{
    &CIM_Job_UMLPackagePath_qual,
    &CIM_Job_Version_qual,
};

/* class CIM_Job */
MI_CONST MI_ClassDecl CIM_Job_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00636207, /* code */
    MI_T("CIM_Job"), /* name */
    CIM_Job_quals, /* qualifiers */
    MI_COUNT(CIM_Job_quals), /* numQualifiers */
    CIM_Job_props, /* properties */
    MI_COUNT(CIM_Job_props), /* numProperties */
    sizeof(CIM_Job), /* size */
    MI_T("CIM_LogicalElement"), /* superClass */
    &CIM_LogicalElement_rtti, /* superClassDecl */
    CIM_Job_meths, /* methods */
    MI_COUNT(CIM_Job_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_Error
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_Error_ErrorType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.OtherErrorType"),
};

static MI_CONST MI_ConstStringA CIM_Error_ErrorType_ModelCorrespondence_qual_value =
{
    CIM_Error_ErrorType_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_ErrorType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ErrorType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Error_ErrorType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ErrorType_quals[] =
{
    &CIM_Error_ErrorType_ModelCorrespondence_qual,
};

/* property CIM_Error.ErrorType */
static MI_CONST MI_PropertyDecl CIM_Error_ErrorType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656509, /* code */
    MI_T("ErrorType"), /* name */
    CIM_Error_ErrorType_quals, /* qualifiers */
    MI_COUNT(CIM_Error_ErrorType_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ErrorType), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_OtherErrorType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ErrorType"),
};

static MI_CONST MI_ConstStringA CIM_Error_OtherErrorType_ModelCorrespondence_qual_value =
{
    CIM_Error_OtherErrorType_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_OtherErrorType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_OtherErrorType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Error_OtherErrorType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_OtherErrorType_quals[] =
{
    &CIM_Error_OtherErrorType_ModelCorrespondence_qual,
};

/* property CIM_Error.OtherErrorType */
static MI_CONST MI_PropertyDecl CIM_Error_OtherErrorType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F650E, /* code */
    MI_T("OtherErrorType"), /* name */
    CIM_Error_OtherErrorType_quals, /* qualifiers */
    MI_COUNT(CIM_Error_OtherErrorType_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, OtherErrorType), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

/* property CIM_Error.OwningEntity */
static MI_CONST MI_PropertyDecl CIM_Error_OwningEntity_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F790C, /* code */
    MI_T("OwningEntity"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, OwningEntity), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_MessageID_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.Message"),
    MI_T("CIM_Error.MessageArguments"),
};

static MI_CONST MI_ConstStringA CIM_Error_MessageID_ModelCorrespondence_qual_value =
{
    CIM_Error_MessageID_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_MessageID_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_MessageID_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Error_MessageID_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_MessageID_quals[] =
{
    &CIM_Error_MessageID_ModelCorrespondence_qual,
};

/* property CIM_Error.MessageID */
static MI_CONST MI_PropertyDecl CIM_Error_MessageID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
    0x006D6409, /* code */
    MI_T("MessageID"), /* name */
    CIM_Error_MessageID_quals, /* qualifiers */
    MI_COUNT(CIM_Error_MessageID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, MessageID), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_Message_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.MessageID"),
    MI_T("CIM_Error.MessageArguments"),
};

static MI_CONST MI_ConstStringA CIM_Error_Message_ModelCorrespondence_qual_value =
{
    CIM_Error_Message_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_Message_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_Message_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Error_Message_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_Message_quals[] =
{
    &CIM_Error_Message_ModelCorrespondence_qual,
};

/* property CIM_Error.Message */
static MI_CONST MI_PropertyDecl CIM_Error_Message_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D6507, /* code */
    MI_T("Message"), /* name */
    CIM_Error_Message_quals, /* qualifiers */
    MI_COUNT(CIM_Error_Message_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, Message), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_MessageArguments_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.MessageID"),
    MI_T("CIM_Error.Message"),
};

static MI_CONST MI_ConstStringA CIM_Error_MessageArguments_ModelCorrespondence_qual_value =
{
    CIM_Error_MessageArguments_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_MessageArguments_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_MessageArguments_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Error_MessageArguments_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_MessageArguments_quals[] =
{
    &CIM_Error_MessageArguments_ModelCorrespondence_qual,
};

/* property CIM_Error.MessageArguments */
static MI_CONST MI_PropertyDecl CIM_Error_MessageArguments_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D7310, /* code */
    MI_T("MessageArguments"), /* name */
    CIM_Error_MessageArguments_quals, /* qualifiers */
    MI_COUNT(CIM_Error_MessageArguments_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, MessageArguments), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

/* property CIM_Error.PerceivedSeverity */
static MI_CONST MI_PropertyDecl CIM_Error_PerceivedSeverity_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00707911, /* code */
    MI_T("PerceivedSeverity"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, PerceivedSeverity), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_ProbableCause_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ProbableCauseDescription"),
};

static MI_CONST MI_ConstStringA CIM_Error_ProbableCause_ModelCorrespondence_qual_value =
{
    CIM_Error_ProbableCause_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_ProbableCause_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ProbableCause_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Error_ProbableCause_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ProbableCause_quals[] =
{
    &CIM_Error_ProbableCause_ModelCorrespondence_qual,
};

/* property CIM_Error.ProbableCause */
static MI_CONST MI_PropertyDecl CIM_Error_ProbableCause_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070650D, /* code */
    MI_T("ProbableCause"), /* name */
    CIM_Error_ProbableCause_quals, /* qualifiers */
    MI_COUNT(CIM_Error_ProbableCause_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ProbableCause), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ProbableCause"),
};

static MI_CONST MI_ConstStringA CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual_value =
{
    CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ProbableCauseDescription_quals[] =
{
    &CIM_Error_ProbableCauseDescription_ModelCorrespondence_qual,
};

/* property CIM_Error.ProbableCauseDescription */
static MI_CONST MI_PropertyDecl CIM_Error_ProbableCauseDescription_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706E18, /* code */
    MI_T("ProbableCauseDescription"), /* name */
    CIM_Error_ProbableCauseDescription_quals, /* qualifiers */
    MI_COUNT(CIM_Error_ProbableCauseDescription_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ProbableCauseDescription), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

/* property CIM_Error.RecommendedActions */
static MI_CONST MI_PropertyDecl CIM_Error_RecommendedActions_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00727312, /* code */
    MI_T("RecommendedActions"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, RecommendedActions), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_ErrorSource_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ErrorSourceFormat"),
};

static MI_CONST MI_ConstStringA CIM_Error_ErrorSource_ModelCorrespondence_qual_value =
{
    CIM_Error_ErrorSource_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_ErrorSource_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ErrorSource_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Error_ErrorSource_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ErrorSource_quals[] =
{
    &CIM_Error_ErrorSource_ModelCorrespondence_qual,
};

/* property CIM_Error.ErrorSource */
static MI_CONST MI_PropertyDecl CIM_Error_ErrorSource_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065650B, /* code */
    MI_T("ErrorSource"), /* name */
    CIM_Error_ErrorSource_quals, /* qualifiers */
    MI_COUNT(CIM_Error_ErrorSource_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ErrorSource), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ErrorSource"),
    MI_T("CIM_Error.OtherErrorSourceFormat"),
};

static MI_CONST MI_ConstStringA CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual_value =
{
    CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_ErrorSourceFormat_quals[] =
{
    &CIM_Error_ErrorSourceFormat_ModelCorrespondence_qual,
};

static MI_CONST MI_Uint16 CIM_Error_ErrorSourceFormat_value = 0;

/* property CIM_Error.ErrorSourceFormat */
static MI_CONST MI_PropertyDecl CIM_Error_ErrorSourceFormat_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00657411, /* code */
    MI_T("ErrorSourceFormat"), /* name */
    CIM_Error_ErrorSourceFormat_quals, /* qualifiers */
    MI_COUNT(CIM_Error_ErrorSourceFormat_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ErrorSourceFormat), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    &CIM_Error_ErrorSourceFormat_value,
};

static MI_CONST MI_Char* CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.ErrorSourceFormat"),
};

static MI_CONST MI_ConstStringA CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual_value =
{
    CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_OtherErrorSourceFormat_quals[] =
{
    &CIM_Error_OtherErrorSourceFormat_ModelCorrespondence_qual,
};

/* property CIM_Error.OtherErrorSourceFormat */
static MI_CONST MI_PropertyDecl CIM_Error_OtherErrorSourceFormat_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F7416, /* code */
    MI_T("OtherErrorSourceFormat"), /* name */
    CIM_Error_OtherErrorSourceFormat_quals, /* qualifiers */
    MI_COUNT(CIM_Error_OtherErrorSourceFormat_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, OtherErrorSourceFormat), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_CIMStatusCode_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.CIMStatusCodeDescription"),
};

static MI_CONST MI_ConstStringA CIM_Error_CIMStatusCode_ModelCorrespondence_qual_value =
{
    CIM_Error_CIMStatusCode_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_CIMStatusCode_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_CIMStatusCode_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Error_CIMStatusCode_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_CIMStatusCode_quals[] =
{
    &CIM_Error_CIMStatusCode_ModelCorrespondence_qual,
};

/* property CIM_Error.CIMStatusCode */
static MI_CONST MI_PropertyDecl CIM_Error_CIMStatusCode_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063650D, /* code */
    MI_T("CIMStatusCode"), /* name */
    CIM_Error_CIMStatusCode_quals, /* qualifiers */
    MI_COUNT(CIM_Error_CIMStatusCode_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, CIMStatusCode), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Error.CIMStatusCode"),
};

static MI_CONST MI_ConstStringA CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual_value =
{
    CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_CIMStatusCodeDescription_quals[] =
{
    &CIM_Error_CIMStatusCodeDescription_ModelCorrespondence_qual,
};

/* property CIM_Error.CIMStatusCodeDescription */
static MI_CONST MI_PropertyDecl CIM_Error_CIMStatusCodeDescription_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00636E18, /* code */
    MI_T("CIMStatusCodeDescription"), /* name */
    CIM_Error_CIMStatusCodeDescription_quals, /* qualifiers */
    MI_COUNT(CIM_Error_CIMStatusCodeDescription_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, CIMStatusCodeDescription), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Error_props[] =
{
    &CIM_Error_ErrorType_prop,
    &CIM_Error_OtherErrorType_prop,
    &CIM_Error_OwningEntity_prop,
    &CIM_Error_MessageID_prop,
    &CIM_Error_Message_prop,
    &CIM_Error_MessageArguments_prop,
    &CIM_Error_PerceivedSeverity_prop,
    &CIM_Error_ProbableCause_prop,
    &CIM_Error_ProbableCauseDescription_prop,
    &CIM_Error_RecommendedActions_prop,
    &CIM_Error_ErrorSource_prop,
    &CIM_Error_ErrorSourceFormat_prop,
    &CIM_Error_OtherErrorSourceFormat_prop,
    &CIM_Error_CIMStatusCode_prop,
    &CIM_Error_CIMStatusCodeDescription_prop,
};

static MI_CONST MI_Char* CIM_Error_Version_qual_value = MI_T("2.22.1");

static MI_CONST MI_Qualifier CIM_Error_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Error_Version_qual_value
};

static MI_CONST MI_Char* CIM_Error_UMLPackagePath_qual_value = MI_T("CIM::Interop");

static MI_CONST MI_Qualifier CIM_Error_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Error_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_quals[] =
{
    &CIM_Error_Version_qual,
    &CIM_Error_UMLPackagePath_qual,
};

/* class CIM_Error */
MI_CONST MI_ClassDecl CIM_Error_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x00637209, /* code */
    MI_T("CIM_Error"), /* name */
    CIM_Error_quals, /* qualifiers */
    MI_COUNT(CIM_Error_quals), /* numQualifiers */
    CIM_Error_props, /* properties */
    MI_COUNT(CIM_Error_props), /* numProperties */
    sizeof(CIM_Error), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_ConcreteJob
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_ConcreteJob_InstanceID_Override_qual_value = MI_T("InstanceID");

static MI_CONST MI_Qualifier CIM_ConcreteJob_InstanceID_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ConcreteJob_InstanceID_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_InstanceID_quals[] =
{
    &CIM_ConcreteJob_InstanceID_Override_qual,
};

/* property CIM_ConcreteJob.InstanceID */
static MI_CONST MI_PropertyDecl CIM_ConcreteJob_InstanceID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0069640A, /* code */
    MI_T("InstanceID"), /* name */
    CIM_ConcreteJob_InstanceID_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_InstanceID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob, InstanceID), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_ConcreteJob_Name_MaxLen_qual_value = 1024U;

static MI_CONST MI_Qualifier CIM_ConcreteJob_Name_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ConcreteJob_Name_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_Name_Override_qual_value = MI_T("Name");

static MI_CONST MI_Qualifier CIM_ConcreteJob_Name_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ConcreteJob_Name_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_Name_quals[] =
{
    &CIM_ConcreteJob_Name_MaxLen_qual,
    &CIM_ConcreteJob_Name_Override_qual,
};

/* property CIM_ConcreteJob.Name */
static MI_CONST MI_PropertyDecl CIM_ConcreteJob_Name_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    CIM_ConcreteJob_Name_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_Name_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob, Name), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    NULL,
};

/* property CIM_ConcreteJob.JobState */
static MI_CONST MI_PropertyDecl CIM_ConcreteJob_JobState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006A6508, /* code */
    MI_T("JobState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob, JobState), /* offset */
    MI_T("CIM_ConcreteJob"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    NULL,
};

/* property CIM_ConcreteJob.TimeOfLastStateChange */
static MI_CONST MI_PropertyDecl CIM_ConcreteJob_TimeOfLastStateChange_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00746515, /* code */
    MI_T("TimeOfLastStateChange"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob, TimeOfLastStateChange), /* offset */
    MI_T("CIM_ConcreteJob"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    NULL,
};

static MI_CONST MI_Datetime CIM_ConcreteJob_TimeBeforeRemoval_value = {0,{{0,0,5,0,0}}};

/* property CIM_ConcreteJob.TimeBeforeRemoval */
static MI_CONST MI_PropertyDecl CIM_ConcreteJob_TimeBeforeRemoval_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
    0x00746C11, /* code */
    MI_T("TimeBeforeRemoval"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob, TimeBeforeRemoval), /* offset */
    MI_T("CIM_ConcreteJob"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    &CIM_ConcreteJob_TimeBeforeRemoval_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_ConcreteJob_props[] =
{
    &CIM_ConcreteJob_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ConcreteJob_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_Job_JobStatus_prop,
    &CIM_Job_TimeSubmitted_prop,
    &CIM_Job_ScheduledStartTime_prop,
    &CIM_Job_StartTime_prop,
    &CIM_Job_ElapsedTime_prop,
    &CIM_Job_JobRunTimes_prop,
    &CIM_Job_RunMonth_prop,
    &CIM_Job_RunDay_prop,
    &CIM_Job_RunDayOfWeek_prop,
    &CIM_Job_RunStartInterval_prop,
    &CIM_Job_LocalOrUtcTime_prop,
    &CIM_Job_UntilTime_prop,
    &CIM_Job_Notify_prop,
    &CIM_Job_Owner_prop,
    &CIM_Job_Priority_prop,
    &CIM_Job_PercentComplete_prop,
    &CIM_Job_DeleteOnCompletion_prop,
    &CIM_Job_ErrorCode_prop,
    &CIM_Job_ErrorDescription_prop,
    &CIM_Job_RecoveryAction_prop,
    &CIM_Job_OtherRecoveryAction_prop,
    &CIM_ConcreteJob_JobState_prop,
    &CIM_ConcreteJob_TimeOfLastStateChange_prop,
    &CIM_ConcreteJob_TimeBeforeRemoval_prop,
};

/* parameter CIM_ConcreteJob.RequestStateChange(): RequestedState */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_RequestStateChange_RequestedState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0072650E, /* code */
    MI_T("RequestedState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_RequestStateChange, RequestedState), /* offset */
};

/* parameter CIM_ConcreteJob.RequestStateChange(): TimeoutPeriod */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_RequestStateChange_TimeoutPeriod_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0074640D, /* code */
    MI_T("TimeoutPeriod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_RequestStateChange, TimeoutPeriod), /* offset */
};

/* parameter CIM_ConcreteJob.RequestStateChange(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_RequestStateChange_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_RequestStateChange, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_ConcreteJob_RequestStateChange_params[] =
{
    &CIM_ConcreteJob_RequestStateChange_MIReturn_param,
    &CIM_ConcreteJob_RequestStateChange_RequestedState_param,
    &CIM_ConcreteJob_RequestStateChange_TimeoutPeriod_param,
};

/* method CIM_ConcreteJob.RequestStateChange() */
MI_CONST MI_MethodDecl CIM_ConcreteJob_RequestStateChange_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00726512, /* code */
    MI_T("RequestStateChange"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    CIM_ConcreteJob_RequestStateChange_params, /* parameters */
    MI_COUNT(CIM_ConcreteJob_RequestStateChange_params), /* numParameters */
    sizeof(CIM_ConcreteJob_RequestStateChange), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_ConcreteJob"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_CONST MI_Char* CIM_ConcreteJob_GetError_Deprecated_qual_data_value[] =
{
    MI_T("CIM_ConcreteJob.GetErrors"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_GetError_Deprecated_qual_value =
{
    CIM_ConcreteJob_GetError_Deprecated_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_GetError_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_GetError_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ConcreteJob_GetError_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_GetError_quals[] =
{
    &CIM_ConcreteJob_GetError_Deprecated_qual,
};

static MI_CONST MI_Char* CIM_ConcreteJob_GetError_Error_EmbeddedInstance_qual_value = MI_T("CIM_Error");

static MI_CONST MI_Qualifier CIM_ConcreteJob_GetError_Error_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &CIM_ConcreteJob_GetError_Error_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_GetError_Error_quals[] =
{
    &CIM_ConcreteJob_GetError_Error_EmbeddedInstance_qual,
};

/* parameter CIM_ConcreteJob.GetError(): Error */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_GetError_Error_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00657205, /* code */
    MI_T("Error"), /* name */
    CIM_ConcreteJob_GetError_Error_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_GetError_Error_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("CIM_Error"), /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_GetError, Error), /* offset */
};

static MI_CONST MI_Char* CIM_ConcreteJob_GetError_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_ConcreteJob.GetErrors"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_GetError_MIReturn_Deprecated_qual_value =
{
    CIM_ConcreteJob_GetError_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_GetError_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_GetError_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ConcreteJob_GetError_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_GetError_MIReturn_quals[] =
{
    &CIM_ConcreteJob_GetError_MIReturn_Deprecated_qual,
};

/* parameter CIM_ConcreteJob.GetError(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_GetError_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    CIM_ConcreteJob_GetError_MIReturn_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_GetError_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_GetError, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_ConcreteJob_GetError_params[] =
{
    &CIM_ConcreteJob_GetError_MIReturn_param,
    &CIM_ConcreteJob_GetError_Error_param,
};

/* method CIM_ConcreteJob.GetError() */
MI_CONST MI_MethodDecl CIM_ConcreteJob_GetError_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00677208, /* code */
    MI_T("GetError"), /* name */
    CIM_ConcreteJob_GetError_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_GetError_quals), /* numQualifiers */
    CIM_ConcreteJob_GetError_params, /* parameters */
    MI_COUNT(CIM_ConcreteJob_GetError_params), /* numParameters */
    sizeof(CIM_ConcreteJob_GetError), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_ConcreteJob"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_CONST MI_Char* CIM_ConcreteJob_GetErrors_Errors_EmbeddedInstance_qual_value = MI_T("CIM_Error");

static MI_CONST MI_Qualifier CIM_ConcreteJob_GetErrors_Errors_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &CIM_ConcreteJob_GetErrors_Errors_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_GetErrors_Errors_quals[] =
{
    &CIM_ConcreteJob_GetErrors_Errors_EmbeddedInstance_qual,
};

/* parameter CIM_ConcreteJob.GetErrors(): Errors */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_GetErrors_Errors_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00657306, /* code */
    MI_T("Errors"), /* name */
    CIM_ConcreteJob_GetErrors_Errors_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_GetErrors_Errors_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("CIM_Error"), /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_GetErrors, Errors), /* offset */
};

/* parameter CIM_ConcreteJob.GetErrors(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_GetErrors_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_GetErrors, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_ConcreteJob_GetErrors_params[] =
{
    &CIM_ConcreteJob_GetErrors_MIReturn_param,
    &CIM_ConcreteJob_GetErrors_Errors_param,
};

/* method CIM_ConcreteJob.GetErrors() */
MI_CONST MI_MethodDecl CIM_ConcreteJob_GetErrors_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00677309, /* code */
    MI_T("GetErrors"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    CIM_ConcreteJob_GetErrors_params, /* parameters */
    MI_COUNT(CIM_ConcreteJob_GetErrors_params), /* numParameters */
    sizeof(CIM_ConcreteJob_GetErrors), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_ConcreteJob"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_ConcreteJob_meths[] =
{
    &CIM_Job_KillJob_rtti,
    &CIM_ConcreteJob_RequestStateChange_rtti,
    &CIM_ConcreteJob_GetError_rtti,
    &CIM_ConcreteJob_GetErrors_rtti,
};

static MI_CONST MI_Char* CIM_ConcreteJob_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_ConcreteJob_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_ConcreteJob_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_Deprecated_qual_data_value[] =
{
    MI_T("CIM_ConcreteJob.GetErrors"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_Deprecated_qual_value =
{
    CIM_ConcreteJob_Deprecated_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ConcreteJob_Deprecated_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_Version_qual_value = MI_T("2.31.1");

static MI_CONST MI_Qualifier CIM_ConcreteJob_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_ConcreteJob_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_quals[] =
{
    &CIM_ConcreteJob_UMLPackagePath_qual,
    &CIM_ConcreteJob_Deprecated_qual,
    &CIM_ConcreteJob_Version_qual,
};

/* class CIM_ConcreteJob */
MI_CONST MI_ClassDecl CIM_ConcreteJob_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0063620F, /* code */
    MI_T("CIM_ConcreteJob"), /* name */
    CIM_ConcreteJob_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_quals), /* numQualifiers */
    CIM_ConcreteJob_props, /* properties */
    MI_COUNT(CIM_ConcreteJob_props), /* numProperties */
    sizeof(CIM_ConcreteJob), /* size */
    MI_T("CIM_Job"), /* superClass */
    &CIM_Job_rtti, /* superClassDecl */
    CIM_ConcreteJob_meths, /* methods */
    MI_COUNT(CIM_ConcreteJob_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_EnabledLogicalElement
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_EnabledLogicalElement_EnabledState_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.OtherEnabledState"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_EnabledState_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElement_EnabledState_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_EnabledState_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_EnabledState_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_EnabledState_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_EnabledState_quals[] =
{
    &CIM_EnabledLogicalElement_EnabledState_ModelCorrespondence_qual,
};

static MI_CONST MI_Uint16 CIM_EnabledLogicalElement_EnabledState_value = 5;

/* property CIM_EnabledLogicalElement.EnabledState */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_EnabledState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065650C, /* code */
    MI_T("EnabledState"), /* name */
    CIM_EnabledLogicalElement_EnabledState_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_EnabledState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, EnabledState), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &CIM_EnabledLogicalElement_EnabledState_value,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_OtherEnabledState_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.EnabledState"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_OtherEnabledState_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElement_OtherEnabledState_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_OtherEnabledState_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_OtherEnabledState_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_OtherEnabledState_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_OtherEnabledState_quals[] =
{
    &CIM_EnabledLogicalElement_OtherEnabledState_ModelCorrespondence_qual,
};

/* property CIM_EnabledLogicalElement.OtherEnabledState */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_OtherEnabledState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6511, /* code */
    MI_T("OtherEnabledState"), /* name */
    CIM_EnabledLogicalElement_OtherEnabledState_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_OtherEnabledState_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, OtherEnabledState), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestedState_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.EnabledState"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_RequestedState_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElement_RequestedState_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_RequestedState_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestedState_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_RequestedState_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_RequestedState_quals[] =
{
    &CIM_EnabledLogicalElement_RequestedState_ModelCorrespondence_qual,
};

static MI_CONST MI_Uint16 CIM_EnabledLogicalElement_RequestedState_value = 12;

/* property CIM_EnabledLogicalElement.RequestedState */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_RequestedState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072650E, /* code */
    MI_T("RequestedState"), /* name */
    CIM_EnabledLogicalElement_RequestedState_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_RequestedState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, RequestedState), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &CIM_EnabledLogicalElement_RequestedState_value,
};

static MI_CONST MI_Uint16 CIM_EnabledLogicalElement_EnabledDefault_value = 2;

/* property CIM_EnabledLogicalElement.EnabledDefault */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_EnabledDefault_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065740E, /* code */
    MI_T("EnabledDefault"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, EnabledDefault), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &CIM_EnabledLogicalElement_EnabledDefault_value,
};

/* property CIM_EnabledLogicalElement.TimeOfLastStateChange */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_TimeOfLastStateChange_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00746515, /* code */
    MI_T("TimeOfLastStateChange"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, TimeOfLastStateChange), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_AvailableRequestedStates_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
    MI_T("CIM_EnabledLogicalElementCapabilities.RequestedStatesSupported"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_AvailableRequestedStates_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElement_AvailableRequestedStates_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_AvailableRequestedStates_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_AvailableRequestedStates_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_AvailableRequestedStates_quals[] =
{
    &CIM_EnabledLogicalElement_AvailableRequestedStates_ModelCorrespondence_qual,
};

/* property CIM_EnabledLogicalElement.AvailableRequestedStates */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_AvailableRequestedStates_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00617318, /* code */
    MI_T("AvailableRequestedStates"), /* name */
    CIM_EnabledLogicalElement_AvailableRequestedStates_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_AvailableRequestedStates_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, AvailableRequestedStates), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_TransitioningToState_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
    MI_T("CIM_EnabledLogicalElement.EnabledState"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_TransitioningToState_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElement_TransitioningToState_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_TransitioningToState_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_TransitioningToState_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_TransitioningToState_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_TransitioningToState_quals[] =
{
    &CIM_EnabledLogicalElement_TransitioningToState_ModelCorrespondence_qual,
};

static MI_CONST MI_Uint16 CIM_EnabledLogicalElement_TransitioningToState_value = 12;

/* property CIM_EnabledLogicalElement.TransitioningToState */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_TransitioningToState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00746514, /* code */
    MI_T("TransitioningToState"), /* name */
    CIM_EnabledLogicalElement_TransitioningToState_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_TransitioningToState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, TransitioningToState), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &CIM_EnabledLogicalElement_TransitioningToState_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_EnabledLogicalElement_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_EnabledLogicalElement_EnabledState_prop,
    &CIM_EnabledLogicalElement_OtherEnabledState_prop,
    &CIM_EnabledLogicalElement_RequestedState_prop,
    &CIM_EnabledLogicalElement_EnabledDefault_prop,
    &CIM_EnabledLogicalElement_TimeOfLastStateChange_prop,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_prop,
    &CIM_EnabledLogicalElement_TransitioningToState_prop,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestStateChange_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_RequestStateChange_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElement_RequestStateChange_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestStateChange_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_RequestStateChange_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_RequestStateChange_quals[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_ModelCorrespondence_qual,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_RequestStateChange_RequestedState_quals[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_RequestedState_ModelCorrespondence_qual,
};

/* parameter CIM_EnabledLogicalElement.RequestStateChange(): RequestedState */
static MI_CONST MI_ParameterDecl CIM_EnabledLogicalElement_RequestStateChange_RequestedState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0072650E, /* code */
    MI_T("RequestedState"), /* name */
    CIM_EnabledLogicalElement_RequestStateChange_RequestedState_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_RequestedState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement_RequestStateChange, RequestedState), /* offset */
};

/* parameter CIM_EnabledLogicalElement.RequestStateChange(): Job */
static MI_CONST MI_ParameterDecl CIM_EnabledLogicalElement_RequestStateChange_Job_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006A6203, /* code */
    MI_T("Job"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ConcreteJob"), /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement_RequestStateChange, Job), /* offset */
};

/* parameter CIM_EnabledLogicalElement.RequestStateChange(): TimeoutPeriod */
static MI_CONST MI_ParameterDecl CIM_EnabledLogicalElement_RequestStateChange_TimeoutPeriod_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0074640D, /* code */
    MI_T("TimeoutPeriod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement_RequestStateChange, TimeoutPeriod), /* offset */
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_RequestStateChange_MIReturn_quals[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_MIReturn_ModelCorrespondence_qual,
};

/* parameter CIM_EnabledLogicalElement.RequestStateChange(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_EnabledLogicalElement_RequestStateChange_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    CIM_EnabledLogicalElement_RequestStateChange_MIReturn_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement_RequestStateChange, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_EnabledLogicalElement_RequestStateChange_params[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_MIReturn_param,
    &CIM_EnabledLogicalElement_RequestStateChange_RequestedState_param,
    &CIM_EnabledLogicalElement_RequestStateChange_Job_param,
    &CIM_EnabledLogicalElement_RequestStateChange_TimeoutPeriod_param,
};

/* method CIM_EnabledLogicalElement.RequestStateChange() */
MI_CONST MI_MethodDecl CIM_EnabledLogicalElement_RequestStateChange_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00726512, /* code */
    MI_T("RequestStateChange"), /* name */
    CIM_EnabledLogicalElement_RequestStateChange_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_quals), /* numQualifiers */
    CIM_EnabledLogicalElement_RequestStateChange_params, /* parameters */
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_params), /* numParameters */
    sizeof(CIM_EnabledLogicalElement_RequestStateChange), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_EnabledLogicalElement_meths[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_rtti,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_EnabledLogicalElement_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_Version_qual_value = MI_T("2.22.0");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_EnabledLogicalElement_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_quals[] =
{
    &CIM_EnabledLogicalElement_UMLPackagePath_qual,
    &CIM_EnabledLogicalElement_Version_qual,
};

/* class CIM_EnabledLogicalElement */
MI_CONST MI_ClassDecl CIM_EnabledLogicalElement_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00637419, /* code */
    MI_T("CIM_EnabledLogicalElement"), /* name */
    CIM_EnabledLogicalElement_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_quals), /* numQualifiers */
    CIM_EnabledLogicalElement_props, /* properties */
    MI_COUNT(CIM_EnabledLogicalElement_props), /* numProperties */
    sizeof(CIM_EnabledLogicalElement), /* size */
    MI_T("CIM_LogicalElement"), /* superClass */
    &CIM_LogicalElement_rtti, /* superClassDecl */
    CIM_EnabledLogicalElement_meths, /* methods */
    MI_COUNT(CIM_EnabledLogicalElement_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_LogicalDevice
**
**==============================================================================
*/

static MI_CONST MI_Uint32 CIM_LogicalDevice_SystemCreationClassName_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_LogicalDevice_SystemCreationClassName_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_LogicalDevice_SystemCreationClassName_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_LogicalDevice_SystemCreationClassName_Propagated_qual_value = MI_T("CIM_System.CreationClassName");

static MI_CONST MI_Qualifier CIM_LogicalDevice_SystemCreationClassName_Propagated_qual =
{
    MI_T("Propagated"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_LogicalDevice_SystemCreationClassName_Propagated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_SystemCreationClassName_quals[] =
{
    &CIM_LogicalDevice_SystemCreationClassName_MaxLen_qual,
    &CIM_LogicalDevice_SystemCreationClassName_Propagated_qual,
};

/* property CIM_LogicalDevice.SystemCreationClassName */
static MI_CONST MI_PropertyDecl CIM_LogicalDevice_SystemCreationClassName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00736517, /* code */
    MI_T("SystemCreationClassName"), /* name */
    CIM_LogicalDevice_SystemCreationClassName_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_SystemCreationClassName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice, SystemCreationClassName), /* offset */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_LogicalDevice_SystemName_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_LogicalDevice_SystemName_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_LogicalDevice_SystemName_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_LogicalDevice_SystemName_Propagated_qual_value = MI_T("CIM_System.Name");

static MI_CONST MI_Qualifier CIM_LogicalDevice_SystemName_Propagated_qual =
{
    MI_T("Propagated"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_LogicalDevice_SystemName_Propagated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_SystemName_quals[] =
{
    &CIM_LogicalDevice_SystemName_MaxLen_qual,
    &CIM_LogicalDevice_SystemName_Propagated_qual,
};

/* property CIM_LogicalDevice.SystemName */
static MI_CONST MI_PropertyDecl CIM_LogicalDevice_SystemName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0073650A, /* code */
    MI_T("SystemName"), /* name */
    CIM_LogicalDevice_SystemName_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_SystemName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice, SystemName), /* offset */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_LogicalDevice_CreationClassName_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_LogicalDevice_CreationClassName_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_LogicalDevice_CreationClassName_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_CreationClassName_quals[] =
{
    &CIM_LogicalDevice_CreationClassName_MaxLen_qual,
};

/* property CIM_LogicalDevice.CreationClassName */
static MI_CONST MI_PropertyDecl CIM_LogicalDevice_CreationClassName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00636511, /* code */
    MI_T("CreationClassName"), /* name */
    CIM_LogicalDevice_CreationClassName_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_CreationClassName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice, CreationClassName), /* offset */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_LogicalDevice_DeviceID_MaxLen_qual_value = 64U;

static MI_CONST MI_Qualifier CIM_LogicalDevice_DeviceID_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_LogicalDevice_DeviceID_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_DeviceID_quals[] =
{
    &CIM_LogicalDevice_DeviceID_MaxLen_qual,
};

/* property CIM_LogicalDevice.DeviceID */
static MI_CONST MI_PropertyDecl CIM_LogicalDevice_DeviceID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00646408, /* code */
    MI_T("DeviceID"), /* name */
    CIM_LogicalDevice_DeviceID_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_DeviceID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice, DeviceID), /* offset */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_LogicalDevice_PowerManagementSupported_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PowerManagementCapabilities"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_PowerManagementSupported_Deprecated_qual_value =
{
    CIM_LogicalDevice_PowerManagementSupported_Deprecated_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_PowerManagementSupported_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_PowerManagementSupported_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_LogicalDevice_PowerManagementSupported_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_PowerManagementSupported_quals[] =
{
    &CIM_LogicalDevice_PowerManagementSupported_Deprecated_qual,
};

/* property CIM_LogicalDevice.PowerManagementSupported */
static MI_CONST MI_PropertyDecl CIM_LogicalDevice_PowerManagementSupported_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706418, /* code */
    MI_T("PowerManagementSupported"), /* name */
    CIM_LogicalDevice_PowerManagementSupported_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_PowerManagementSupported_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice, PowerManagementSupported), /* offset */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_LogicalDevice_PowerManagementCapabilities_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PowerManagementCapabilities.PowerCapabilities"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_PowerManagementCapabilities_Deprecated_qual_value =
{
    CIM_LogicalDevice_PowerManagementCapabilities_Deprecated_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_PowerManagementCapabilities_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_PowerManagementCapabilities_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_LogicalDevice_PowerManagementCapabilities_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_PowerManagementCapabilities_quals[] =
{
    &CIM_LogicalDevice_PowerManagementCapabilities_Deprecated_qual,
};

/* property CIM_LogicalDevice.PowerManagementCapabilities */
static MI_CONST MI_PropertyDecl CIM_LogicalDevice_PowerManagementCapabilities_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070731B, /* code */
    MI_T("PowerManagementCapabilities"), /* name */
    CIM_LogicalDevice_PowerManagementCapabilities_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_PowerManagementCapabilities_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice, PowerManagementCapabilities), /* offset */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_LogicalDevice_Availability_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_LogicalDevice.AdditionalAvailability"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_Availability_ModelCorrespondence_qual_value =
{
    CIM_LogicalDevice_Availability_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_Availability_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_Availability_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_LogicalDevice_Availability_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_Availability_quals[] =
{
    &CIM_LogicalDevice_Availability_ModelCorrespondence_qual,
};

/* property CIM_LogicalDevice.Availability */
static MI_CONST MI_PropertyDecl CIM_LogicalDevice_Availability_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0061790C, /* code */
    MI_T("Availability"), /* name */
    CIM_LogicalDevice_Availability_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_Availability_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice, Availability), /* offset */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_LogicalDevice_StatusInfo_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.EnabledState"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_StatusInfo_Deprecated_qual_value =
{
    CIM_LogicalDevice_StatusInfo_Deprecated_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_StatusInfo_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_StatusInfo_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_LogicalDevice_StatusInfo_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_StatusInfo_quals[] =
{
    &CIM_LogicalDevice_StatusInfo_Deprecated_qual,
};

/* property CIM_LogicalDevice.StatusInfo */
static MI_CONST MI_PropertyDecl CIM_LogicalDevice_StatusInfo_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736F0A, /* code */
    MI_T("StatusInfo"), /* name */
    CIM_LogicalDevice_StatusInfo_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_StatusInfo_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice, StatusInfo), /* offset */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_LogicalDevice_LastErrorCode_Deprecated_qual_data_value[] =
{
    MI_T("CIM_DeviceErrorData.LastErrorCode"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_LastErrorCode_Deprecated_qual_value =
{
    CIM_LogicalDevice_LastErrorCode_Deprecated_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_LastErrorCode_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_LastErrorCode_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_LogicalDevice_LastErrorCode_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_LastErrorCode_quals[] =
{
    &CIM_LogicalDevice_LastErrorCode_Deprecated_qual,
};

/* property CIM_LogicalDevice.LastErrorCode */
static MI_CONST MI_PropertyDecl CIM_LogicalDevice_LastErrorCode_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C650D, /* code */
    MI_T("LastErrorCode"), /* name */
    CIM_LogicalDevice_LastErrorCode_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_LastErrorCode_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice, LastErrorCode), /* offset */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_LogicalDevice_ErrorDescription_Deprecated_qual_data_value[] =
{
    MI_T("CIM_DeviceErrorData.ErrorDescription"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_ErrorDescription_Deprecated_qual_value =
{
    CIM_LogicalDevice_ErrorDescription_Deprecated_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_ErrorDescription_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_ErrorDescription_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_LogicalDevice_ErrorDescription_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_ErrorDescription_quals[] =
{
    &CIM_LogicalDevice_ErrorDescription_Deprecated_qual,
};

/* property CIM_LogicalDevice.ErrorDescription */
static MI_CONST MI_PropertyDecl CIM_LogicalDevice_ErrorDescription_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656E10, /* code */
    MI_T("ErrorDescription"), /* name */
    CIM_LogicalDevice_ErrorDescription_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_ErrorDescription_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice, ErrorDescription), /* offset */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_LogicalDevice_ErrorCleared_Deprecated_qual_data_value[] =
{
    MI_T("CIM_ManagedSystemElement.OperationalStatus"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_ErrorCleared_Deprecated_qual_value =
{
    CIM_LogicalDevice_ErrorCleared_Deprecated_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_ErrorCleared_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_ErrorCleared_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_LogicalDevice_ErrorCleared_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_ErrorCleared_quals[] =
{
    &CIM_LogicalDevice_ErrorCleared_Deprecated_qual,
};

/* property CIM_LogicalDevice.ErrorCleared */
static MI_CONST MI_PropertyDecl CIM_LogicalDevice_ErrorCleared_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065640C, /* code */
    MI_T("ErrorCleared"), /* name */
    CIM_LogicalDevice_ErrorCleared_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_ErrorCleared_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice, ErrorCleared), /* offset */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_LogicalDevice_OtherIdentifyingInfo_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_LogicalDevice_OtherIdentifyingInfo_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_LogicalDevice_OtherIdentifyingInfo_ArrayType_qual_value
};

static MI_CONST MI_Uint32 CIM_LogicalDevice_OtherIdentifyingInfo_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_LogicalDevice_OtherIdentifyingInfo_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_LogicalDevice_OtherIdentifyingInfo_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_LogicalDevice_OtherIdentifyingInfo_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_LogicalDevice.IdentifyingDescriptions"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_OtherIdentifyingInfo_ModelCorrespondence_qual_value =
{
    CIM_LogicalDevice_OtherIdentifyingInfo_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_OtherIdentifyingInfo_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_OtherIdentifyingInfo_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_LogicalDevice_OtherIdentifyingInfo_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_OtherIdentifyingInfo_quals[] =
{
    &CIM_LogicalDevice_OtherIdentifyingInfo_ArrayType_qual,
    &CIM_LogicalDevice_OtherIdentifyingInfo_MaxLen_qual,
    &CIM_LogicalDevice_OtherIdentifyingInfo_ModelCorrespondence_qual,
};

/* property CIM_LogicalDevice.OtherIdentifyingInfo */
static MI_CONST MI_PropertyDecl CIM_LogicalDevice_OtherIdentifyingInfo_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6F14, /* code */
    MI_T("OtherIdentifyingInfo"), /* name */
    CIM_LogicalDevice_OtherIdentifyingInfo_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_OtherIdentifyingInfo_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice, OtherIdentifyingInfo), /* offset */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_LogicalDevice_PowerOnHours_Units_qual_value = MI_T("Hours");

static MI_CONST MI_Qualifier CIM_LogicalDevice_PowerOnHours_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_LogicalDevice_PowerOnHours_Units_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_PowerOnHours_quals[] =
{
    &CIM_LogicalDevice_PowerOnHours_Units_qual,
};

/* property CIM_LogicalDevice.PowerOnHours */
static MI_CONST MI_PropertyDecl CIM_LogicalDevice_PowerOnHours_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070730C, /* code */
    MI_T("PowerOnHours"), /* name */
    CIM_LogicalDevice_PowerOnHours_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_PowerOnHours_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice, PowerOnHours), /* offset */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_LogicalDevice_TotalPowerOnHours_Units_qual_value = MI_T("Hours");

static MI_CONST MI_Qualifier CIM_LogicalDevice_TotalPowerOnHours_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_LogicalDevice_TotalPowerOnHours_Units_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_TotalPowerOnHours_quals[] =
{
    &CIM_LogicalDevice_TotalPowerOnHours_Units_qual,
};

/* property CIM_LogicalDevice.TotalPowerOnHours */
static MI_CONST MI_PropertyDecl CIM_LogicalDevice_TotalPowerOnHours_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00747311, /* code */
    MI_T("TotalPowerOnHours"), /* name */
    CIM_LogicalDevice_TotalPowerOnHours_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_TotalPowerOnHours_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice, TotalPowerOnHours), /* offset */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_LogicalDevice_IdentifyingDescriptions_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_LogicalDevice_IdentifyingDescriptions_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_LogicalDevice_IdentifyingDescriptions_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_LogicalDevice_IdentifyingDescriptions_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_LogicalDevice.OtherIdentifyingInfo"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_IdentifyingDescriptions_ModelCorrespondence_qual_value =
{
    CIM_LogicalDevice_IdentifyingDescriptions_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_IdentifyingDescriptions_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_IdentifyingDescriptions_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_LogicalDevice_IdentifyingDescriptions_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_IdentifyingDescriptions_quals[] =
{
    &CIM_LogicalDevice_IdentifyingDescriptions_ArrayType_qual,
    &CIM_LogicalDevice_IdentifyingDescriptions_ModelCorrespondence_qual,
};

/* property CIM_LogicalDevice.IdentifyingDescriptions */
static MI_CONST MI_PropertyDecl CIM_LogicalDevice_IdentifyingDescriptions_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00697317, /* code */
    MI_T("IdentifyingDescriptions"), /* name */
    CIM_LogicalDevice_IdentifyingDescriptions_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_IdentifyingDescriptions_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice, IdentifyingDescriptions), /* offset */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_LogicalDevice_AdditionalAvailability_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_LogicalDevice.Availability"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_AdditionalAvailability_ModelCorrespondence_qual_value =
{
    CIM_LogicalDevice_AdditionalAvailability_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_AdditionalAvailability_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_AdditionalAvailability_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_LogicalDevice_AdditionalAvailability_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_AdditionalAvailability_quals[] =
{
    &CIM_LogicalDevice_AdditionalAvailability_ModelCorrespondence_qual,
};

/* property CIM_LogicalDevice.AdditionalAvailability */
static MI_CONST MI_PropertyDecl CIM_LogicalDevice_AdditionalAvailability_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00617916, /* code */
    MI_T("AdditionalAvailability"), /* name */
    CIM_LogicalDevice_AdditionalAvailability_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_AdditionalAvailability_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice, AdditionalAvailability), /* offset */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_LogicalDevice_MaxQuiesceTime_Deprecated_qual_data_value[] =
{
    MI_T("No value"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_MaxQuiesceTime_Deprecated_qual_value =
{
    CIM_LogicalDevice_MaxQuiesceTime_Deprecated_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_MaxQuiesceTime_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_MaxQuiesceTime_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_LogicalDevice_MaxQuiesceTime_Deprecated_qual_value
};

static MI_CONST MI_Char* CIM_LogicalDevice_MaxQuiesceTime_Units_qual_value = MI_T("MilliSeconds");

static MI_CONST MI_Qualifier CIM_LogicalDevice_MaxQuiesceTime_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_LogicalDevice_MaxQuiesceTime_Units_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_MaxQuiesceTime_quals[] =
{
    &CIM_LogicalDevice_MaxQuiesceTime_Deprecated_qual,
    &CIM_LogicalDevice_MaxQuiesceTime_Units_qual,
};

/* property CIM_LogicalDevice.MaxQuiesceTime */
static MI_CONST MI_PropertyDecl CIM_LogicalDevice_MaxQuiesceTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D650E, /* code */
    MI_T("MaxQuiesceTime"), /* name */
    CIM_LogicalDevice_MaxQuiesceTime_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_MaxQuiesceTime_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice, MaxQuiesceTime), /* offset */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_LogicalDevice_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_EnabledLogicalElement_EnabledState_prop,
    &CIM_EnabledLogicalElement_OtherEnabledState_prop,
    &CIM_EnabledLogicalElement_RequestedState_prop,
    &CIM_EnabledLogicalElement_EnabledDefault_prop,
    &CIM_EnabledLogicalElement_TimeOfLastStateChange_prop,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_prop,
    &CIM_EnabledLogicalElement_TransitioningToState_prop,
    &CIM_LogicalDevice_SystemCreationClassName_prop,
    &CIM_LogicalDevice_SystemName_prop,
    &CIM_LogicalDevice_CreationClassName_prop,
    &CIM_LogicalDevice_DeviceID_prop,
    &CIM_LogicalDevice_PowerManagementSupported_prop,
    &CIM_LogicalDevice_PowerManagementCapabilities_prop,
    &CIM_LogicalDevice_Availability_prop,
    &CIM_LogicalDevice_StatusInfo_prop,
    &CIM_LogicalDevice_LastErrorCode_prop,
    &CIM_LogicalDevice_ErrorDescription_prop,
    &CIM_LogicalDevice_ErrorCleared_prop,
    &CIM_LogicalDevice_OtherIdentifyingInfo_prop,
    &CIM_LogicalDevice_PowerOnHours_prop,
    &CIM_LogicalDevice_TotalPowerOnHours_prop,
    &CIM_LogicalDevice_IdentifyingDescriptions_prop,
    &CIM_LogicalDevice_AdditionalAvailability_prop,
    &CIM_LogicalDevice_MaxQuiesceTime_prop,
};

static MI_CONST MI_Char* CIM_LogicalDevice_SetPowerState_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PowerManagementService.SetPowerState"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_SetPowerState_Deprecated_qual_value =
{
    CIM_LogicalDevice_SetPowerState_Deprecated_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_SetPowerState_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_SetPowerState_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_LogicalDevice_SetPowerState_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_SetPowerState_quals[] =
{
    &CIM_LogicalDevice_SetPowerState_Deprecated_qual,
};

/* parameter CIM_LogicalDevice.SetPowerState(): PowerState */
static MI_CONST MI_ParameterDecl CIM_LogicalDevice_SetPowerState_PowerState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0070650A, /* code */
    MI_T("PowerState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice_SetPowerState, PowerState), /* offset */
};

/* parameter CIM_LogicalDevice.SetPowerState(): Time */
static MI_CONST MI_ParameterDecl CIM_LogicalDevice_SetPowerState_Time_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00746504, /* code */
    MI_T("Time"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice_SetPowerState, Time), /* offset */
};

static MI_CONST MI_Char* CIM_LogicalDevice_SetPowerState_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PowerManagementService.SetPowerState"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_SetPowerState_MIReturn_Deprecated_qual_value =
{
    CIM_LogicalDevice_SetPowerState_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_SetPowerState_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_SetPowerState_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_LogicalDevice_SetPowerState_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_SetPowerState_MIReturn_quals[] =
{
    &CIM_LogicalDevice_SetPowerState_MIReturn_Deprecated_qual,
};

/* parameter CIM_LogicalDevice.SetPowerState(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_LogicalDevice_SetPowerState_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    CIM_LogicalDevice_SetPowerState_MIReturn_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_SetPowerState_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice_SetPowerState, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_LogicalDevice_SetPowerState_params[] =
{
    &CIM_LogicalDevice_SetPowerState_MIReturn_param,
    &CIM_LogicalDevice_SetPowerState_PowerState_param,
    &CIM_LogicalDevice_SetPowerState_Time_param,
};

/* method CIM_LogicalDevice.SetPowerState() */
MI_CONST MI_MethodDecl CIM_LogicalDevice_SetPowerState_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650D, /* code */
    MI_T("SetPowerState"), /* name */
    CIM_LogicalDevice_SetPowerState_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_SetPowerState_quals), /* numQualifiers */
    CIM_LogicalDevice_SetPowerState_params, /* parameters */
    MI_COUNT(CIM_LogicalDevice_SetPowerState_params), /* numParameters */
    sizeof(CIM_LogicalDevice_SetPowerState), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

/* parameter CIM_LogicalDevice.Reset(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_LogicalDevice_Reset_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice_Reset, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_LogicalDevice_Reset_params[] =
{
    &CIM_LogicalDevice_Reset_MIReturn_param,
};

/* method CIM_LogicalDevice.Reset() */
MI_CONST MI_MethodDecl CIM_LogicalDevice_Reset_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00727405, /* code */
    MI_T("Reset"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    CIM_LogicalDevice_Reset_params, /* parameters */
    MI_COUNT(CIM_LogicalDevice_Reset_params), /* numParameters */
    sizeof(CIM_LogicalDevice_Reset), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_CONST MI_Char* CIM_LogicalDevice_EnableDevice_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_EnableDevice_Deprecated_qual_value =
{
    CIM_LogicalDevice_EnableDevice_Deprecated_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_EnableDevice_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_EnableDevice_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_LogicalDevice_EnableDevice_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_EnableDevice_quals[] =
{
    &CIM_LogicalDevice_EnableDevice_Deprecated_qual,
};

/* parameter CIM_LogicalDevice.EnableDevice(): Enabled */
static MI_CONST MI_ParameterDecl CIM_LogicalDevice_EnableDevice_Enabled_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00656407, /* code */
    MI_T("Enabled"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice_EnableDevice, Enabled), /* offset */
};

static MI_CONST MI_Char* CIM_LogicalDevice_EnableDevice_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_EnableDevice_MIReturn_Deprecated_qual_value =
{
    CIM_LogicalDevice_EnableDevice_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_EnableDevice_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_EnableDevice_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_LogicalDevice_EnableDevice_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_EnableDevice_MIReturn_quals[] =
{
    &CIM_LogicalDevice_EnableDevice_MIReturn_Deprecated_qual,
};

/* parameter CIM_LogicalDevice.EnableDevice(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_LogicalDevice_EnableDevice_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    CIM_LogicalDevice_EnableDevice_MIReturn_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_EnableDevice_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice_EnableDevice, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_LogicalDevice_EnableDevice_params[] =
{
    &CIM_LogicalDevice_EnableDevice_MIReturn_param,
    &CIM_LogicalDevice_EnableDevice_Enabled_param,
};

/* method CIM_LogicalDevice.EnableDevice() */
MI_CONST MI_MethodDecl CIM_LogicalDevice_EnableDevice_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0065650C, /* code */
    MI_T("EnableDevice"), /* name */
    CIM_LogicalDevice_EnableDevice_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_EnableDevice_quals), /* numQualifiers */
    CIM_LogicalDevice_EnableDevice_params, /* parameters */
    MI_COUNT(CIM_LogicalDevice_EnableDevice_params), /* numParameters */
    sizeof(CIM_LogicalDevice_EnableDevice), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_CONST MI_Char* CIM_LogicalDevice_OnlineDevice_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_OnlineDevice_Deprecated_qual_value =
{
    CIM_LogicalDevice_OnlineDevice_Deprecated_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_OnlineDevice_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_OnlineDevice_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_LogicalDevice_OnlineDevice_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_OnlineDevice_quals[] =
{
    &CIM_LogicalDevice_OnlineDevice_Deprecated_qual,
};

/* parameter CIM_LogicalDevice.OnlineDevice(): Online */
static MI_CONST MI_ParameterDecl CIM_LogicalDevice_OnlineDevice_Online_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006F6506, /* code */
    MI_T("Online"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice_OnlineDevice, Online), /* offset */
};

static MI_CONST MI_Char* CIM_LogicalDevice_OnlineDevice_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_OnlineDevice_MIReturn_Deprecated_qual_value =
{
    CIM_LogicalDevice_OnlineDevice_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_OnlineDevice_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_OnlineDevice_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_LogicalDevice_OnlineDevice_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_OnlineDevice_MIReturn_quals[] =
{
    &CIM_LogicalDevice_OnlineDevice_MIReturn_Deprecated_qual,
};

/* parameter CIM_LogicalDevice.OnlineDevice(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_LogicalDevice_OnlineDevice_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    CIM_LogicalDevice_OnlineDevice_MIReturn_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_OnlineDevice_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice_OnlineDevice, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_LogicalDevice_OnlineDevice_params[] =
{
    &CIM_LogicalDevice_OnlineDevice_MIReturn_param,
    &CIM_LogicalDevice_OnlineDevice_Online_param,
};

/* method CIM_LogicalDevice.OnlineDevice() */
MI_CONST MI_MethodDecl CIM_LogicalDevice_OnlineDevice_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006F650C, /* code */
    MI_T("OnlineDevice"), /* name */
    CIM_LogicalDevice_OnlineDevice_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_OnlineDevice_quals), /* numQualifiers */
    CIM_LogicalDevice_OnlineDevice_params, /* parameters */
    MI_COUNT(CIM_LogicalDevice_OnlineDevice_params), /* numParameters */
    sizeof(CIM_LogicalDevice_OnlineDevice), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_CONST MI_Char* CIM_LogicalDevice_QuiesceDevice_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_QuiesceDevice_Deprecated_qual_value =
{
    CIM_LogicalDevice_QuiesceDevice_Deprecated_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_QuiesceDevice_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_QuiesceDevice_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_LogicalDevice_QuiesceDevice_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_QuiesceDevice_quals[] =
{
    &CIM_LogicalDevice_QuiesceDevice_Deprecated_qual,
};

/* parameter CIM_LogicalDevice.QuiesceDevice(): Quiesce */
static MI_CONST MI_ParameterDecl CIM_LogicalDevice_QuiesceDevice_Quiesce_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00716507, /* code */
    MI_T("Quiesce"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice_QuiesceDevice, Quiesce), /* offset */
};

static MI_CONST MI_Char* CIM_LogicalDevice_QuiesceDevice_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA CIM_LogicalDevice_QuiesceDevice_MIReturn_Deprecated_qual_value =
{
    CIM_LogicalDevice_QuiesceDevice_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(CIM_LogicalDevice_QuiesceDevice_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalDevice_QuiesceDevice_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_LogicalDevice_QuiesceDevice_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_QuiesceDevice_MIReturn_quals[] =
{
    &CIM_LogicalDevice_QuiesceDevice_MIReturn_Deprecated_qual,
};

/* parameter CIM_LogicalDevice.QuiesceDevice(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_LogicalDevice_QuiesceDevice_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    CIM_LogicalDevice_QuiesceDevice_MIReturn_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_QuiesceDevice_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice_QuiesceDevice, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_LogicalDevice_QuiesceDevice_params[] =
{
    &CIM_LogicalDevice_QuiesceDevice_MIReturn_param,
    &CIM_LogicalDevice_QuiesceDevice_Quiesce_param,
};

/* method CIM_LogicalDevice.QuiesceDevice() */
MI_CONST MI_MethodDecl CIM_LogicalDevice_QuiesceDevice_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0071650D, /* code */
    MI_T("QuiesceDevice"), /* name */
    CIM_LogicalDevice_QuiesceDevice_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_QuiesceDevice_quals), /* numQualifiers */
    CIM_LogicalDevice_QuiesceDevice_params, /* parameters */
    MI_COUNT(CIM_LogicalDevice_QuiesceDevice_params), /* numParameters */
    sizeof(CIM_LogicalDevice_QuiesceDevice), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

/* parameter CIM_LogicalDevice.SaveProperties(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_LogicalDevice_SaveProperties_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice_SaveProperties, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_LogicalDevice_SaveProperties_params[] =
{
    &CIM_LogicalDevice_SaveProperties_MIReturn_param,
};

/* method CIM_LogicalDevice.SaveProperties() */
MI_CONST MI_MethodDecl CIM_LogicalDevice_SaveProperties_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073730E, /* code */
    MI_T("SaveProperties"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    CIM_LogicalDevice_SaveProperties_params, /* parameters */
    MI_COUNT(CIM_LogicalDevice_SaveProperties_params), /* numParameters */
    sizeof(CIM_LogicalDevice_SaveProperties), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

/* parameter CIM_LogicalDevice.RestoreProperties(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_LogicalDevice_RestoreProperties_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalDevice_RestoreProperties, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_LogicalDevice_RestoreProperties_params[] =
{
    &CIM_LogicalDevice_RestoreProperties_MIReturn_param,
};

/* method CIM_LogicalDevice.RestoreProperties() */
MI_CONST MI_MethodDecl CIM_LogicalDevice_RestoreProperties_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00727311, /* code */
    MI_T("RestoreProperties"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    CIM_LogicalDevice_RestoreProperties_params, /* parameters */
    MI_COUNT(CIM_LogicalDevice_RestoreProperties_params), /* numParameters */
    sizeof(CIM_LogicalDevice_RestoreProperties), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_LogicalDevice_meths[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_rtti,
    &CIM_LogicalDevice_SetPowerState_rtti,
    &CIM_LogicalDevice_Reset_rtti,
    &CIM_LogicalDevice_EnableDevice_rtti,
    &CIM_LogicalDevice_OnlineDevice_rtti,
    &CIM_LogicalDevice_QuiesceDevice_rtti,
    &CIM_LogicalDevice_SaveProperties_rtti,
    &CIM_LogicalDevice_RestoreProperties_rtti,
};

static MI_CONST MI_Char* CIM_LogicalDevice_UMLPackagePath_qual_value = MI_T("CIM::Core::Device");

static MI_CONST MI_Qualifier CIM_LogicalDevice_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_LogicalDevice_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_LogicalDevice_Version_qual_value = MI_T("2.8.0");

static MI_CONST MI_Qualifier CIM_LogicalDevice_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_LogicalDevice_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalDevice_quals[] =
{
    &CIM_LogicalDevice_UMLPackagePath_qual,
    &CIM_LogicalDevice_Version_qual,
};

/* class CIM_LogicalDevice */
MI_CONST MI_ClassDecl CIM_LogicalDevice_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00636511, /* code */
    MI_T("CIM_LogicalDevice"), /* name */
    CIM_LogicalDevice_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalDevice_quals), /* numQualifiers */
    CIM_LogicalDevice_props, /* properties */
    MI_COUNT(CIM_LogicalDevice_props), /* numProperties */
    sizeof(CIM_LogicalDevice), /* size */
    MI_T("CIM_EnabledLogicalElement"), /* superClass */
    &CIM_EnabledLogicalElement_rtti, /* superClassDecl */
    CIM_LogicalDevice_meths, /* methods */
    MI_COUNT(CIM_LogicalDevice_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_LogicalPort
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_LogicalPort_Speed_Units_qual_value = MI_T("Bits per Second");

static MI_CONST MI_Qualifier CIM_LogicalPort_Speed_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_LogicalPort_Speed_Units_qual_value
};

static MI_CONST MI_Char* CIM_LogicalPort_Speed_PUnit_qual_value = MI_T("bit / second");

static MI_CONST MI_Qualifier CIM_LogicalPort_Speed_PUnit_qual =
{
    MI_T("PUnit"),
    MI_STRING,
    0,
    &CIM_LogicalPort_Speed_PUnit_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalPort_Speed_quals[] =
{
    &CIM_LogicalPort_Speed_Units_qual,
    &CIM_LogicalPort_Speed_PUnit_qual,
};

/* property CIM_LogicalPort.Speed */
static MI_CONST MI_PropertyDecl CIM_LogicalPort_Speed_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736405, /* code */
    MI_T("Speed"), /* name */
    CIM_LogicalPort_Speed_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalPort_Speed_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalPort, Speed), /* offset */
    MI_T("CIM_LogicalPort"), /* origin */
    MI_T("CIM_LogicalPort"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_LogicalPort_MaxSpeed_Units_qual_value = MI_T("Bits per Second");

static MI_CONST MI_Qualifier CIM_LogicalPort_MaxSpeed_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_LogicalPort_MaxSpeed_Units_qual_value
};

static MI_CONST MI_Char* CIM_LogicalPort_MaxSpeed_PUnit_qual_value = MI_T("bit / second");

static MI_CONST MI_Qualifier CIM_LogicalPort_MaxSpeed_PUnit_qual =
{
    MI_T("PUnit"),
    MI_STRING,
    0,
    &CIM_LogicalPort_MaxSpeed_PUnit_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalPort_MaxSpeed_quals[] =
{
    &CIM_LogicalPort_MaxSpeed_Units_qual,
    &CIM_LogicalPort_MaxSpeed_PUnit_qual,
};

/* property CIM_LogicalPort.MaxSpeed */
static MI_CONST MI_PropertyDecl CIM_LogicalPort_MaxSpeed_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D6408, /* code */
    MI_T("MaxSpeed"), /* name */
    CIM_LogicalPort_MaxSpeed_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalPort_MaxSpeed_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalPort, MaxSpeed), /* offset */
    MI_T("CIM_LogicalPort"), /* origin */
    MI_T("CIM_LogicalPort"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_LogicalPort_RequestedSpeed_Units_qual_value = MI_T("Bits per Second");

static MI_CONST MI_Qualifier CIM_LogicalPort_RequestedSpeed_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_LogicalPort_RequestedSpeed_Units_qual_value
};

static MI_CONST MI_Char* CIM_LogicalPort_RequestedSpeed_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_LogicalPort.Speed"),
};

static MI_CONST MI_ConstStringA CIM_LogicalPort_RequestedSpeed_ModelCorrespondence_qual_value =
{
    CIM_LogicalPort_RequestedSpeed_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_LogicalPort_RequestedSpeed_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalPort_RequestedSpeed_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_LogicalPort_RequestedSpeed_ModelCorrespondence_qual_value
};

static MI_CONST MI_Char* CIM_LogicalPort_RequestedSpeed_PUnit_qual_value = MI_T("bit / second");

static MI_CONST MI_Qualifier CIM_LogicalPort_RequestedSpeed_PUnit_qual =
{
    MI_T("PUnit"),
    MI_STRING,
    0,
    &CIM_LogicalPort_RequestedSpeed_PUnit_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalPort_RequestedSpeed_quals[] =
{
    &CIM_LogicalPort_RequestedSpeed_Units_qual,
    &CIM_LogicalPort_RequestedSpeed_ModelCorrespondence_qual,
    &CIM_LogicalPort_RequestedSpeed_PUnit_qual,
};

/* property CIM_LogicalPort.RequestedSpeed */
static MI_CONST MI_PropertyDecl CIM_LogicalPort_RequestedSpeed_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072640E, /* code */
    MI_T("RequestedSpeed"), /* name */
    CIM_LogicalPort_RequestedSpeed_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalPort_RequestedSpeed_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalPort, RequestedSpeed), /* offset */
    MI_T("CIM_LogicalPort"), /* origin */
    MI_T("CIM_LogicalPort"), /* propagator */
    NULL,
};

/* property CIM_LogicalPort.UsageRestriction */
static MI_CONST MI_PropertyDecl CIM_LogicalPort_UsageRestriction_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756E10, /* code */
    MI_T("UsageRestriction"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalPort, UsageRestriction), /* offset */
    MI_T("CIM_LogicalPort"), /* origin */
    MI_T("CIM_LogicalPort"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_LogicalPort_PortType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_NetworkPort.OtherNetworkPortType"),
};

static MI_CONST MI_ConstStringA CIM_LogicalPort_PortType_ModelCorrespondence_qual_value =
{
    CIM_LogicalPort_PortType_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_LogicalPort_PortType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalPort_PortType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_LogicalPort_PortType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalPort_PortType_quals[] =
{
    &CIM_LogicalPort_PortType_ModelCorrespondence_qual,
};

/* property CIM_LogicalPort.PortType */
static MI_CONST MI_PropertyDecl CIM_LogicalPort_PortType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706508, /* code */
    MI_T("PortType"), /* name */
    CIM_LogicalPort_PortType_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalPort_PortType_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalPort, PortType), /* offset */
    MI_T("CIM_LogicalPort"), /* origin */
    MI_T("CIM_LogicalPort"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_LogicalPort_OtherPortType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_LogicalPort.PortType"),
};

static MI_CONST MI_ConstStringA CIM_LogicalPort_OtherPortType_ModelCorrespondence_qual_value =
{
    CIM_LogicalPort_OtherPortType_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_LogicalPort_OtherPortType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_LogicalPort_OtherPortType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_LogicalPort_OtherPortType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalPort_OtherPortType_quals[] =
{
    &CIM_LogicalPort_OtherPortType_ModelCorrespondence_qual,
};

/* property CIM_LogicalPort.OtherPortType */
static MI_CONST MI_PropertyDecl CIM_LogicalPort_OtherPortType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F650D, /* code */
    MI_T("OtherPortType"), /* name */
    CIM_LogicalPort_OtherPortType_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalPort_OtherPortType_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_LogicalPort, OtherPortType), /* offset */
    MI_T("CIM_LogicalPort"), /* origin */
    MI_T("CIM_LogicalPort"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_LogicalPort_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_EnabledLogicalElement_EnabledState_prop,
    &CIM_EnabledLogicalElement_OtherEnabledState_prop,
    &CIM_EnabledLogicalElement_RequestedState_prop,
    &CIM_EnabledLogicalElement_EnabledDefault_prop,
    &CIM_EnabledLogicalElement_TimeOfLastStateChange_prop,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_prop,
    &CIM_EnabledLogicalElement_TransitioningToState_prop,
    &CIM_LogicalDevice_SystemCreationClassName_prop,
    &CIM_LogicalDevice_SystemName_prop,
    &CIM_LogicalDevice_CreationClassName_prop,
    &CIM_LogicalDevice_DeviceID_prop,
    &CIM_LogicalDevice_PowerManagementSupported_prop,
    &CIM_LogicalDevice_PowerManagementCapabilities_prop,
    &CIM_LogicalDevice_Availability_prop,
    &CIM_LogicalDevice_StatusInfo_prop,
    &CIM_LogicalDevice_LastErrorCode_prop,
    &CIM_LogicalDevice_ErrorDescription_prop,
    &CIM_LogicalDevice_ErrorCleared_prop,
    &CIM_LogicalDevice_OtherIdentifyingInfo_prop,
    &CIM_LogicalDevice_PowerOnHours_prop,
    &CIM_LogicalDevice_TotalPowerOnHours_prop,
    &CIM_LogicalDevice_IdentifyingDescriptions_prop,
    &CIM_LogicalDevice_AdditionalAvailability_prop,
    &CIM_LogicalDevice_MaxQuiesceTime_prop,
    &CIM_LogicalPort_Speed_prop,
    &CIM_LogicalPort_MaxSpeed_prop,
    &CIM_LogicalPort_RequestedSpeed_prop,
    &CIM_LogicalPort_UsageRestriction_prop,
    &CIM_LogicalPort_PortType_prop,
    &CIM_LogicalPort_OtherPortType_prop,
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_LogicalPort_meths[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_rtti,
    &CIM_LogicalDevice_SetPowerState_rtti,
    &CIM_LogicalDevice_Reset_rtti,
    &CIM_LogicalDevice_EnableDevice_rtti,
    &CIM_LogicalDevice_OnlineDevice_rtti,
    &CIM_LogicalDevice_QuiesceDevice_rtti,
    &CIM_LogicalDevice_SaveProperties_rtti,
    &CIM_LogicalDevice_RestoreProperties_rtti,
};

static MI_CONST MI_Char* CIM_LogicalPort_UMLPackagePath_qual_value = MI_T("CIM::Device::Ports");

static MI_CONST MI_Qualifier CIM_LogicalPort_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_LogicalPort_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_LogicalPort_Version_qual_value = MI_T("2.10.0");

static MI_CONST MI_Qualifier CIM_LogicalPort_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_LogicalPort_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalPort_quals[] =
{
    &CIM_LogicalPort_UMLPackagePath_qual,
    &CIM_LogicalPort_Version_qual,
};

/* class CIM_LogicalPort */
MI_CONST MI_ClassDecl CIM_LogicalPort_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0063740F, /* code */
    MI_T("CIM_LogicalPort"), /* name */
    CIM_LogicalPort_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalPort_quals), /* numQualifiers */
    CIM_LogicalPort_props, /* properties */
    MI_COUNT(CIM_LogicalPort_props), /* numProperties */
    sizeof(CIM_LogicalPort), /* size */
    MI_T("CIM_LogicalDevice"), /* superClass */
    &CIM_LogicalDevice_rtti, /* superClassDecl */
    CIM_LogicalPort_meths, /* methods */
    MI_COUNT(CIM_LogicalPort_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_NetworkPort
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_NetworkPort_Speed_Units_qual_value = MI_T("Bits per Second");

static MI_CONST MI_Qualifier CIM_NetworkPort_Speed_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_NetworkPort_Speed_Units_qual_value
};

static MI_CONST MI_Char* CIM_NetworkPort_Speed_PUnit_qual_value = MI_T("bit / second");

static MI_CONST MI_Qualifier CIM_NetworkPort_Speed_PUnit_qual =
{
    MI_T("PUnit"),
    MI_STRING,
    0,
    &CIM_NetworkPort_Speed_PUnit_qual_value
};

static MI_CONST MI_Char* CIM_NetworkPort_Speed_Override_qual_value = MI_T("Speed");

static MI_CONST MI_Qualifier CIM_NetworkPort_Speed_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_NetworkPort_Speed_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_NetworkPort_Speed_quals[] =
{
    &CIM_NetworkPort_Speed_Units_qual,
    &CIM_NetworkPort_Speed_PUnit_qual,
    &CIM_NetworkPort_Speed_Override_qual,
};

/* property CIM_NetworkPort.Speed */
static MI_CONST MI_PropertyDecl CIM_NetworkPort_Speed_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736405, /* code */
    MI_T("Speed"), /* name */
    CIM_NetworkPort_Speed_quals, /* qualifiers */
    MI_COUNT(CIM_NetworkPort_Speed_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NetworkPort, Speed), /* offset */
    MI_T("CIM_LogicalPort"), /* origin */
    MI_T("CIM_NetworkPort"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_NetworkPort_OtherNetworkPortType_Deprecated_qual_data_value[] =
{
    MI_T("CIM_NetworkPort.OtherPortType"),
};

static MI_CONST MI_ConstStringA CIM_NetworkPort_OtherNetworkPortType_Deprecated_qual_value =
{
    CIM_NetworkPort_OtherNetworkPortType_Deprecated_qual_data_value,
    MI_COUNT(CIM_NetworkPort_OtherNetworkPortType_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_NetworkPort_OtherNetworkPortType_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_NetworkPort_OtherNetworkPortType_Deprecated_qual_value
};

static MI_CONST MI_Char* CIM_NetworkPort_OtherNetworkPortType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_LogicalPort.PortType"),
};

static MI_CONST MI_ConstStringA CIM_NetworkPort_OtherNetworkPortType_ModelCorrespondence_qual_value =
{
    CIM_NetworkPort_OtherNetworkPortType_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_NetworkPort_OtherNetworkPortType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_NetworkPort_OtherNetworkPortType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_NetworkPort_OtherNetworkPortType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_NetworkPort_OtherNetworkPortType_quals[] =
{
    &CIM_NetworkPort_OtherNetworkPortType_Deprecated_qual,
    &CIM_NetworkPort_OtherNetworkPortType_ModelCorrespondence_qual,
};

/* property CIM_NetworkPort.OtherNetworkPortType */
static MI_CONST MI_PropertyDecl CIM_NetworkPort_OtherNetworkPortType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6514, /* code */
    MI_T("OtherNetworkPortType"), /* name */
    CIM_NetworkPort_OtherNetworkPortType_quals, /* qualifiers */
    MI_COUNT(CIM_NetworkPort_OtherNetworkPortType_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NetworkPort, OtherNetworkPortType), /* offset */
    MI_T("CIM_NetworkPort"), /* origin */
    MI_T("CIM_NetworkPort"), /* propagator */
    NULL,
};

/* property CIM_NetworkPort.PortNumber */
static MI_CONST MI_PropertyDecl CIM_NetworkPort_PortNumber_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070720A, /* code */
    MI_T("PortNumber"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NetworkPort, PortNumber), /* offset */
    MI_T("CIM_NetworkPort"), /* origin */
    MI_T("CIM_NetworkPort"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_NetworkPort_LinkTechnology_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_NetworkPort.OtherLinkTechnology"),
};

static MI_CONST MI_ConstStringA CIM_NetworkPort_LinkTechnology_ModelCorrespondence_qual_value =
{
    CIM_NetworkPort_LinkTechnology_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_NetworkPort_LinkTechnology_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_NetworkPort_LinkTechnology_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_NetworkPort_LinkTechnology_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_NetworkPort_LinkTechnology_quals[] =
{
    &CIM_NetworkPort_LinkTechnology_ModelCorrespondence_qual,
};

/* property CIM_NetworkPort.LinkTechnology */
static MI_CONST MI_PropertyDecl CIM_NetworkPort_LinkTechnology_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C790E, /* code */
    MI_T("LinkTechnology"), /* name */
    CIM_NetworkPort_LinkTechnology_quals, /* qualifiers */
    MI_COUNT(CIM_NetworkPort_LinkTechnology_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NetworkPort, LinkTechnology), /* offset */
    MI_T("CIM_NetworkPort"), /* origin */
    MI_T("CIM_NetworkPort"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_NetworkPort_OtherLinkTechnology_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_NetworkPort.LinkTechnology"),
};

static MI_CONST MI_ConstStringA CIM_NetworkPort_OtherLinkTechnology_ModelCorrespondence_qual_value =
{
    CIM_NetworkPort_OtherLinkTechnology_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_NetworkPort_OtherLinkTechnology_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_NetworkPort_OtherLinkTechnology_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_NetworkPort_OtherLinkTechnology_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_NetworkPort_OtherLinkTechnology_quals[] =
{
    &CIM_NetworkPort_OtherLinkTechnology_ModelCorrespondence_qual,
};

/* property CIM_NetworkPort.OtherLinkTechnology */
static MI_CONST MI_PropertyDecl CIM_NetworkPort_OtherLinkTechnology_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F7913, /* code */
    MI_T("OtherLinkTechnology"), /* name */
    CIM_NetworkPort_OtherLinkTechnology_quals, /* qualifiers */
    MI_COUNT(CIM_NetworkPort_OtherLinkTechnology_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NetworkPort, OtherLinkTechnology), /* offset */
    MI_T("CIM_NetworkPort"), /* origin */
    MI_T("CIM_NetworkPort"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_NetworkPort_PermanentAddress_MaxLen_qual_value = 64U;

static MI_CONST MI_Qualifier CIM_NetworkPort_PermanentAddress_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_NetworkPort_PermanentAddress_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_NetworkPort_PermanentAddress_quals[] =
{
    &CIM_NetworkPort_PermanentAddress_MaxLen_qual,
};

/* property CIM_NetworkPort.PermanentAddress */
static MI_CONST MI_PropertyDecl CIM_NetworkPort_PermanentAddress_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00707310, /* code */
    MI_T("PermanentAddress"), /* name */
    CIM_NetworkPort_PermanentAddress_quals, /* qualifiers */
    MI_COUNT(CIM_NetworkPort_PermanentAddress_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NetworkPort, PermanentAddress), /* offset */
    MI_T("CIM_NetworkPort"), /* origin */
    MI_T("CIM_NetworkPort"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_NetworkPort_NetworkAddresses_MaxLen_qual_value = 64U;

static MI_CONST MI_Qualifier CIM_NetworkPort_NetworkAddresses_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_NetworkPort_NetworkAddresses_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_NetworkPort_NetworkAddresses_quals[] =
{
    &CIM_NetworkPort_NetworkAddresses_MaxLen_qual,
};

/* property CIM_NetworkPort.NetworkAddresses */
static MI_CONST MI_PropertyDecl CIM_NetworkPort_NetworkAddresses_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E7310, /* code */
    MI_T("NetworkAddresses"), /* name */
    CIM_NetworkPort_NetworkAddresses_quals, /* qualifiers */
    MI_COUNT(CIM_NetworkPort_NetworkAddresses_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NetworkPort, NetworkAddresses), /* offset */
    MI_T("CIM_NetworkPort"), /* origin */
    MI_T("CIM_NetworkPort"), /* propagator */
    NULL,
};

/* property CIM_NetworkPort.FullDuplex */
static MI_CONST MI_PropertyDecl CIM_NetworkPort_FullDuplex_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0066780A, /* code */
    MI_T("FullDuplex"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NetworkPort, FullDuplex), /* offset */
    MI_T("CIM_NetworkPort"), /* origin */
    MI_T("CIM_NetworkPort"), /* propagator */
    NULL,
};

/* property CIM_NetworkPort.AutoSense */
static MI_CONST MI_PropertyDecl CIM_NetworkPort_AutoSense_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00616509, /* code */
    MI_T("AutoSense"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NetworkPort, AutoSense), /* offset */
    MI_T("CIM_NetworkPort"), /* origin */
    MI_T("CIM_NetworkPort"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_NetworkPort_SupportedMaximumTransmissionUnit_Units_qual_value = MI_T("Bytes");

static MI_CONST MI_Qualifier CIM_NetworkPort_SupportedMaximumTransmissionUnit_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_NetworkPort_SupportedMaximumTransmissionUnit_Units_qual_value
};

static MI_CONST MI_Char* CIM_NetworkPort_SupportedMaximumTransmissionUnit_PUnit_qual_value = MI_T("byte");

static MI_CONST MI_Qualifier CIM_NetworkPort_SupportedMaximumTransmissionUnit_PUnit_qual =
{
    MI_T("PUnit"),
    MI_STRING,
    0,
    &CIM_NetworkPort_SupportedMaximumTransmissionUnit_PUnit_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_NetworkPort_SupportedMaximumTransmissionUnit_quals[] =
{
    &CIM_NetworkPort_SupportedMaximumTransmissionUnit_Units_qual,
    &CIM_NetworkPort_SupportedMaximumTransmissionUnit_PUnit_qual,
};

/* property CIM_NetworkPort.SupportedMaximumTransmissionUnit */
static MI_CONST MI_PropertyDecl CIM_NetworkPort_SupportedMaximumTransmissionUnit_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737420, /* code */
    MI_T("SupportedMaximumTransmissionUnit"), /* name */
    CIM_NetworkPort_SupportedMaximumTransmissionUnit_quals, /* qualifiers */
    MI_COUNT(CIM_NetworkPort_SupportedMaximumTransmissionUnit_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NetworkPort, SupportedMaximumTransmissionUnit), /* offset */
    MI_T("CIM_NetworkPort"), /* origin */
    MI_T("CIM_NetworkPort"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_NetworkPort_ActiveMaximumTransmissionUnit_Units_qual_value = MI_T("Bytes");

static MI_CONST MI_Qualifier CIM_NetworkPort_ActiveMaximumTransmissionUnit_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_NetworkPort_ActiveMaximumTransmissionUnit_Units_qual_value
};

static MI_CONST MI_Char* CIM_NetworkPort_ActiveMaximumTransmissionUnit_PUnit_qual_value = MI_T("byte");

static MI_CONST MI_Qualifier CIM_NetworkPort_ActiveMaximumTransmissionUnit_PUnit_qual =
{
    MI_T("PUnit"),
    MI_STRING,
    0,
    &CIM_NetworkPort_ActiveMaximumTransmissionUnit_PUnit_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_NetworkPort_ActiveMaximumTransmissionUnit_quals[] =
{
    &CIM_NetworkPort_ActiveMaximumTransmissionUnit_Units_qual,
    &CIM_NetworkPort_ActiveMaximumTransmissionUnit_PUnit_qual,
};

/* property CIM_NetworkPort.ActiveMaximumTransmissionUnit */
static MI_CONST MI_PropertyDecl CIM_NetworkPort_ActiveMaximumTransmissionUnit_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0061741D, /* code */
    MI_T("ActiveMaximumTransmissionUnit"), /* name */
    CIM_NetworkPort_ActiveMaximumTransmissionUnit_quals, /* qualifiers */
    MI_COUNT(CIM_NetworkPort_ActiveMaximumTransmissionUnit_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NetworkPort, ActiveMaximumTransmissionUnit), /* offset */
    MI_T("CIM_NetworkPort"), /* origin */
    MI_T("CIM_NetworkPort"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_NetworkPort_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_EnabledLogicalElement_EnabledState_prop,
    &CIM_EnabledLogicalElement_OtherEnabledState_prop,
    &CIM_EnabledLogicalElement_RequestedState_prop,
    &CIM_EnabledLogicalElement_EnabledDefault_prop,
    &CIM_EnabledLogicalElement_TimeOfLastStateChange_prop,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_prop,
    &CIM_EnabledLogicalElement_TransitioningToState_prop,
    &CIM_LogicalDevice_SystemCreationClassName_prop,
    &CIM_LogicalDevice_SystemName_prop,
    &CIM_LogicalDevice_CreationClassName_prop,
    &CIM_LogicalDevice_DeviceID_prop,
    &CIM_LogicalDevice_PowerManagementSupported_prop,
    &CIM_LogicalDevice_PowerManagementCapabilities_prop,
    &CIM_LogicalDevice_Availability_prop,
    &CIM_LogicalDevice_StatusInfo_prop,
    &CIM_LogicalDevice_LastErrorCode_prop,
    &CIM_LogicalDevice_ErrorDescription_prop,
    &CIM_LogicalDevice_ErrorCleared_prop,
    &CIM_LogicalDevice_OtherIdentifyingInfo_prop,
    &CIM_LogicalDevice_PowerOnHours_prop,
    &CIM_LogicalDevice_TotalPowerOnHours_prop,
    &CIM_LogicalDevice_IdentifyingDescriptions_prop,
    &CIM_LogicalDevice_AdditionalAvailability_prop,
    &CIM_LogicalDevice_MaxQuiesceTime_prop,
    &CIM_NetworkPort_Speed_prop,
    &CIM_LogicalPort_MaxSpeed_prop,
    &CIM_LogicalPort_RequestedSpeed_prop,
    &CIM_LogicalPort_UsageRestriction_prop,
    &CIM_LogicalPort_PortType_prop,
    &CIM_LogicalPort_OtherPortType_prop,
    &CIM_NetworkPort_OtherNetworkPortType_prop,
    &CIM_NetworkPort_PortNumber_prop,
    &CIM_NetworkPort_LinkTechnology_prop,
    &CIM_NetworkPort_OtherLinkTechnology_prop,
    &CIM_NetworkPort_PermanentAddress_prop,
    &CIM_NetworkPort_NetworkAddresses_prop,
    &CIM_NetworkPort_FullDuplex_prop,
    &CIM_NetworkPort_AutoSense_prop,
    &CIM_NetworkPort_SupportedMaximumTransmissionUnit_prop,
    &CIM_NetworkPort_ActiveMaximumTransmissionUnit_prop,
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_NetworkPort_meths[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_rtti,
    &CIM_LogicalDevice_SetPowerState_rtti,
    &CIM_LogicalDevice_Reset_rtti,
    &CIM_LogicalDevice_EnableDevice_rtti,
    &CIM_LogicalDevice_OnlineDevice_rtti,
    &CIM_LogicalDevice_QuiesceDevice_rtti,
    &CIM_LogicalDevice_SaveProperties_rtti,
    &CIM_LogicalDevice_RestoreProperties_rtti,
};

static MI_CONST MI_Char* CIM_NetworkPort_UMLPackagePath_qual_value = MI_T("CIM::Device::Ports");

static MI_CONST MI_Qualifier CIM_NetworkPort_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_NetworkPort_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_NetworkPort_Version_qual_value = MI_T("2.10.0");

static MI_CONST MI_Qualifier CIM_NetworkPort_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_NetworkPort_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_NetworkPort_quals[] =
{
    &CIM_NetworkPort_UMLPackagePath_qual,
    &CIM_NetworkPort_Version_qual,
};

/* class CIM_NetworkPort */
MI_CONST MI_ClassDecl CIM_NetworkPort_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0063740F, /* code */
    MI_T("CIM_NetworkPort"), /* name */
    CIM_NetworkPort_quals, /* qualifiers */
    MI_COUNT(CIM_NetworkPort_quals), /* numQualifiers */
    CIM_NetworkPort_props, /* properties */
    MI_COUNT(CIM_NetworkPort_props), /* numProperties */
    sizeof(CIM_NetworkPort), /* size */
    MI_T("CIM_LogicalPort"), /* superClass */
    &CIM_LogicalPort_rtti, /* superClassDecl */
    CIM_NetworkPort_meths, /* methods */
    MI_COUNT(CIM_NetworkPort_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_EthernetPort
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_EthernetPort_PortType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_NetworkPort.OtherNetworkPortType"),
};

static MI_CONST MI_ConstStringA CIM_EthernetPort_PortType_ModelCorrespondence_qual_value =
{
    CIM_EthernetPort_PortType_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EthernetPort_PortType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EthernetPort_PortType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EthernetPort_PortType_ModelCorrespondence_qual_value
};

static MI_CONST MI_Char* CIM_EthernetPort_PortType_Override_qual_value = MI_T("PortType");

static MI_CONST MI_Qualifier CIM_EthernetPort_PortType_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_EthernetPort_PortType_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EthernetPort_PortType_quals[] =
{
    &CIM_EthernetPort_PortType_ModelCorrespondence_qual,
    &CIM_EthernetPort_PortType_Override_qual,
};

/* property CIM_EthernetPort.PortType */
static MI_CONST MI_PropertyDecl CIM_EthernetPort_PortType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706508, /* code */
    MI_T("PortType"), /* name */
    CIM_EthernetPort_PortType_quals, /* qualifiers */
    MI_COUNT(CIM_EthernetPort_PortType_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EthernetPort, PortType), /* offset */
    MI_T("CIM_LogicalPort"), /* origin */
    MI_T("CIM_EthernetPort"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_EthernetPort_NetworkAddresses_MaxLen_qual_value = 64U;

static MI_CONST MI_Qualifier CIM_EthernetPort_NetworkAddresses_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_EthernetPort_NetworkAddresses_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_EthernetPort_NetworkAddresses_Override_qual_value = MI_T("NetworkAddresses");

static MI_CONST MI_Qualifier CIM_EthernetPort_NetworkAddresses_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_EthernetPort_NetworkAddresses_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EthernetPort_NetworkAddresses_quals[] =
{
    &CIM_EthernetPort_NetworkAddresses_MaxLen_qual,
    &CIM_EthernetPort_NetworkAddresses_Override_qual,
};

/* property CIM_EthernetPort.NetworkAddresses */
static MI_CONST MI_PropertyDecl CIM_EthernetPort_NetworkAddresses_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E7310, /* code */
    MI_T("NetworkAddresses"), /* name */
    CIM_EthernetPort_NetworkAddresses_quals, /* qualifiers */
    MI_COUNT(CIM_EthernetPort_NetworkAddresses_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EthernetPort, NetworkAddresses), /* offset */
    MI_T("CIM_NetworkPort"), /* origin */
    MI_T("CIM_EthernetPort"), /* propagator */
    NULL,
};

/* property CIM_EthernetPort.MaxDataSize */
static MI_CONST MI_PropertyDecl CIM_EthernetPort_MaxDataSize_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D650B, /* code */
    MI_T("MaxDataSize"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EthernetPort, MaxDataSize), /* offset */
    MI_T("CIM_EthernetPort"), /* origin */
    MI_T("CIM_EthernetPort"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_EthernetPort_Capabilities_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_EthernetPort_Capabilities_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_EthernetPort_Capabilities_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_EthernetPort_Capabilities_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EthernetPort.CapabilityDescriptions"),
};

static MI_CONST MI_ConstStringA CIM_EthernetPort_Capabilities_ModelCorrespondence_qual_value =
{
    CIM_EthernetPort_Capabilities_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EthernetPort_Capabilities_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EthernetPort_Capabilities_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EthernetPort_Capabilities_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EthernetPort_Capabilities_quals[] =
{
    &CIM_EthernetPort_Capabilities_ArrayType_qual,
    &CIM_EthernetPort_Capabilities_ModelCorrespondence_qual,
};

/* property CIM_EthernetPort.Capabilities */
static MI_CONST MI_PropertyDecl CIM_EthernetPort_Capabilities_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063730C, /* code */
    MI_T("Capabilities"), /* name */
    CIM_EthernetPort_Capabilities_quals, /* qualifiers */
    MI_COUNT(CIM_EthernetPort_Capabilities_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EthernetPort, Capabilities), /* offset */
    MI_T("CIM_EthernetPort"), /* origin */
    MI_T("CIM_EthernetPort"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_EthernetPort_CapabilityDescriptions_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_EthernetPort_CapabilityDescriptions_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_EthernetPort_CapabilityDescriptions_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_EthernetPort_CapabilityDescriptions_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EthernetPort.Capabilities"),
};

static MI_CONST MI_ConstStringA CIM_EthernetPort_CapabilityDescriptions_ModelCorrespondence_qual_value =
{
    CIM_EthernetPort_CapabilityDescriptions_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EthernetPort_CapabilityDescriptions_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EthernetPort_CapabilityDescriptions_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EthernetPort_CapabilityDescriptions_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EthernetPort_CapabilityDescriptions_quals[] =
{
    &CIM_EthernetPort_CapabilityDescriptions_ArrayType_qual,
    &CIM_EthernetPort_CapabilityDescriptions_ModelCorrespondence_qual,
};

/* property CIM_EthernetPort.CapabilityDescriptions */
static MI_CONST MI_PropertyDecl CIM_EthernetPort_CapabilityDescriptions_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637316, /* code */
    MI_T("CapabilityDescriptions"), /* name */
    CIM_EthernetPort_CapabilityDescriptions_quals, /* qualifiers */
    MI_COUNT(CIM_EthernetPort_CapabilityDescriptions_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EthernetPort, CapabilityDescriptions), /* offset */
    MI_T("CIM_EthernetPort"), /* origin */
    MI_T("CIM_EthernetPort"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_EthernetPort_EnabledCapabilities_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_EthernetPort_EnabledCapabilities_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_EthernetPort_EnabledCapabilities_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_EthernetPort_EnabledCapabilities_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EthernetPort.Capabilities"),
    MI_T("CIM_EthernetPort.OtherEnabledCapabilities"),
};

static MI_CONST MI_ConstStringA CIM_EthernetPort_EnabledCapabilities_ModelCorrespondence_qual_value =
{
    CIM_EthernetPort_EnabledCapabilities_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EthernetPort_EnabledCapabilities_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EthernetPort_EnabledCapabilities_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EthernetPort_EnabledCapabilities_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EthernetPort_EnabledCapabilities_quals[] =
{
    &CIM_EthernetPort_EnabledCapabilities_ArrayType_qual,
    &CIM_EthernetPort_EnabledCapabilities_ModelCorrespondence_qual,
};

/* property CIM_EthernetPort.EnabledCapabilities */
static MI_CONST MI_PropertyDecl CIM_EthernetPort_EnabledCapabilities_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00657313, /* code */
    MI_T("EnabledCapabilities"), /* name */
    CIM_EthernetPort_EnabledCapabilities_quals, /* qualifiers */
    MI_COUNT(CIM_EthernetPort_EnabledCapabilities_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EthernetPort, EnabledCapabilities), /* offset */
    MI_T("CIM_EthernetPort"), /* origin */
    MI_T("CIM_EthernetPort"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_EthernetPort_OtherEnabledCapabilities_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_EthernetPort_OtherEnabledCapabilities_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_EthernetPort_OtherEnabledCapabilities_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_EthernetPort_OtherEnabledCapabilities_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EthernetPort.EnabledCapabilities"),
};

static MI_CONST MI_ConstStringA CIM_EthernetPort_OtherEnabledCapabilities_ModelCorrespondence_qual_value =
{
    CIM_EthernetPort_OtherEnabledCapabilities_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EthernetPort_OtherEnabledCapabilities_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EthernetPort_OtherEnabledCapabilities_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EthernetPort_OtherEnabledCapabilities_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EthernetPort_OtherEnabledCapabilities_quals[] =
{
    &CIM_EthernetPort_OtherEnabledCapabilities_ArrayType_qual,
    &CIM_EthernetPort_OtherEnabledCapabilities_ModelCorrespondence_qual,
};

/* property CIM_EthernetPort.OtherEnabledCapabilities */
static MI_CONST MI_PropertyDecl CIM_EthernetPort_OtherEnabledCapabilities_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F7318, /* code */
    MI_T("OtherEnabledCapabilities"), /* name */
    CIM_EthernetPort_OtherEnabledCapabilities_quals, /* qualifiers */
    MI_COUNT(CIM_EthernetPort_OtherEnabledCapabilities_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EthernetPort, OtherEnabledCapabilities), /* offset */
    MI_T("CIM_EthernetPort"), /* origin */
    MI_T("CIM_EthernetPort"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_EthernetPort_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_EnabledLogicalElement_EnabledState_prop,
    &CIM_EnabledLogicalElement_OtherEnabledState_prop,
    &CIM_EnabledLogicalElement_RequestedState_prop,
    &CIM_EnabledLogicalElement_EnabledDefault_prop,
    &CIM_EnabledLogicalElement_TimeOfLastStateChange_prop,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_prop,
    &CIM_EnabledLogicalElement_TransitioningToState_prop,
    &CIM_LogicalDevice_SystemCreationClassName_prop,
    &CIM_LogicalDevice_SystemName_prop,
    &CIM_LogicalDevice_CreationClassName_prop,
    &CIM_LogicalDevice_DeviceID_prop,
    &CIM_LogicalDevice_PowerManagementSupported_prop,
    &CIM_LogicalDevice_PowerManagementCapabilities_prop,
    &CIM_LogicalDevice_Availability_prop,
    &CIM_LogicalDevice_StatusInfo_prop,
    &CIM_LogicalDevice_LastErrorCode_prop,
    &CIM_LogicalDevice_ErrorDescription_prop,
    &CIM_LogicalDevice_ErrorCleared_prop,
    &CIM_LogicalDevice_OtherIdentifyingInfo_prop,
    &CIM_LogicalDevice_PowerOnHours_prop,
    &CIM_LogicalDevice_TotalPowerOnHours_prop,
    &CIM_LogicalDevice_IdentifyingDescriptions_prop,
    &CIM_LogicalDevice_AdditionalAvailability_prop,
    &CIM_LogicalDevice_MaxQuiesceTime_prop,
    &CIM_NetworkPort_Speed_prop,
    &CIM_LogicalPort_MaxSpeed_prop,
    &CIM_LogicalPort_RequestedSpeed_prop,
    &CIM_LogicalPort_UsageRestriction_prop,
    &CIM_EthernetPort_PortType_prop,
    &CIM_LogicalPort_OtherPortType_prop,
    &CIM_NetworkPort_OtherNetworkPortType_prop,
    &CIM_NetworkPort_PortNumber_prop,
    &CIM_NetworkPort_LinkTechnology_prop,
    &CIM_NetworkPort_OtherLinkTechnology_prop,
    &CIM_NetworkPort_PermanentAddress_prop,
    &CIM_EthernetPort_NetworkAddresses_prop,
    &CIM_NetworkPort_FullDuplex_prop,
    &CIM_NetworkPort_AutoSense_prop,
    &CIM_NetworkPort_SupportedMaximumTransmissionUnit_prop,
    &CIM_NetworkPort_ActiveMaximumTransmissionUnit_prop,
    &CIM_EthernetPort_MaxDataSize_prop,
    &CIM_EthernetPort_Capabilities_prop,
    &CIM_EthernetPort_CapabilityDescriptions_prop,
    &CIM_EthernetPort_EnabledCapabilities_prop,
    &CIM_EthernetPort_OtherEnabledCapabilities_prop,
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_EthernetPort_meths[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_rtti,
    &CIM_LogicalDevice_SetPowerState_rtti,
    &CIM_LogicalDevice_Reset_rtti,
    &CIM_LogicalDevice_EnableDevice_rtti,
    &CIM_LogicalDevice_OnlineDevice_rtti,
    &CIM_LogicalDevice_QuiesceDevice_rtti,
    &CIM_LogicalDevice_SaveProperties_rtti,
    &CIM_LogicalDevice_RestoreProperties_rtti,
};

static MI_CONST MI_Char* CIM_EthernetPort_UMLPackagePath_qual_value = MI_T("CIM::Device::Ports");

static MI_CONST MI_Qualifier CIM_EthernetPort_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_EthernetPort_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_EthernetPort_Version_qual_value = MI_T("2.10.0");

static MI_CONST MI_Qualifier CIM_EthernetPort_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_EthernetPort_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EthernetPort_quals[] =
{
    &CIM_EthernetPort_UMLPackagePath_qual,
    &CIM_EthernetPort_Version_qual,
};

/* class CIM_EthernetPort */
MI_CONST MI_ClassDecl CIM_EthernetPort_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00637410, /* code */
    MI_T("CIM_EthernetPort"), /* name */
    CIM_EthernetPort_quals, /* qualifiers */
    MI_COUNT(CIM_EthernetPort_quals), /* numQualifiers */
    CIM_EthernetPort_props, /* properties */
    MI_COUNT(CIM_EthernetPort_props), /* numProperties */
    sizeof(CIM_EthernetPort), /* size */
    MI_T("CIM_NetworkPort"), /* superClass */
    &CIM_NetworkPort_rtti, /* superClassDecl */
    CIM_EthernetPort_meths, /* methods */
    MI_COUNT(CIM_EthernetPort_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** ABC_EthernetPort
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_EthernetPort_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_EnabledLogicalElement_EnabledState_prop,
    &CIM_EnabledLogicalElement_OtherEnabledState_prop,
    &CIM_EnabledLogicalElement_RequestedState_prop,
    &CIM_EnabledLogicalElement_EnabledDefault_prop,
    &CIM_EnabledLogicalElement_TimeOfLastStateChange_prop,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_prop,
    &CIM_EnabledLogicalElement_TransitioningToState_prop,
    &CIM_LogicalDevice_SystemCreationClassName_prop,
    &CIM_LogicalDevice_SystemName_prop,
    &CIM_LogicalDevice_CreationClassName_prop,
    &CIM_LogicalDevice_DeviceID_prop,
    &CIM_LogicalDevice_PowerManagementSupported_prop,
    &CIM_LogicalDevice_PowerManagementCapabilities_prop,
    &CIM_LogicalDevice_Availability_prop,
    &CIM_LogicalDevice_StatusInfo_prop,
    &CIM_LogicalDevice_LastErrorCode_prop,
    &CIM_LogicalDevice_ErrorDescription_prop,
    &CIM_LogicalDevice_ErrorCleared_prop,
    &CIM_LogicalDevice_OtherIdentifyingInfo_prop,
    &CIM_LogicalDevice_PowerOnHours_prop,
    &CIM_LogicalDevice_TotalPowerOnHours_prop,
    &CIM_LogicalDevice_IdentifyingDescriptions_prop,
    &CIM_LogicalDevice_AdditionalAvailability_prop,
    &CIM_LogicalDevice_MaxQuiesceTime_prop,
    &CIM_NetworkPort_Speed_prop,
    &CIM_LogicalPort_MaxSpeed_prop,
    &CIM_LogicalPort_RequestedSpeed_prop,
    &CIM_LogicalPort_UsageRestriction_prop,
    &CIM_EthernetPort_PortType_prop,
    &CIM_LogicalPort_OtherPortType_prop,
    &CIM_NetworkPort_OtherNetworkPortType_prop,
    &CIM_NetworkPort_PortNumber_prop,
    &CIM_NetworkPort_LinkTechnology_prop,
    &CIM_NetworkPort_OtherLinkTechnology_prop,
    &CIM_NetworkPort_PermanentAddress_prop,
    &CIM_EthernetPort_NetworkAddresses_prop,
    &CIM_NetworkPort_FullDuplex_prop,
    &CIM_NetworkPort_AutoSense_prop,
    &CIM_NetworkPort_SupportedMaximumTransmissionUnit_prop,
    &CIM_NetworkPort_ActiveMaximumTransmissionUnit_prop,
    &CIM_EthernetPort_MaxDataSize_prop,
    &CIM_EthernetPort_Capabilities_prop,
    &CIM_EthernetPort_CapabilityDescriptions_prop,
    &CIM_EthernetPort_EnabledCapabilities_prop,
    &CIM_EthernetPort_OtherEnabledCapabilities_prop,
};

static MI_CONST MI_Char* ABC_EthernetPort_RequestStateChange_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_EthernetPort_RequestStateChange_ModelCorrespondence_qual_value =
{
    ABC_EthernetPort_RequestStateChange_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_EthernetPort_RequestStateChange_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_EthernetPort_RequestStateChange_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_EthernetPort_RequestStateChange_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_EthernetPort_RequestStateChange_quals[] =
{
    &ABC_EthernetPort_RequestStateChange_ModelCorrespondence_qual,
};

static MI_CONST MI_Char* ABC_EthernetPort_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_EthernetPort_RequestStateChange_RequestedState_ModelCorrespondence_qual_value =
{
    ABC_EthernetPort_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_EthernetPort_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_EthernetPort_RequestStateChange_RequestedState_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_EthernetPort_RequestStateChange_RequestedState_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_EthernetPort_RequestStateChange_RequestedState_quals[] =
{
    &ABC_EthernetPort_RequestStateChange_RequestedState_ModelCorrespondence_qual,
};

/* parameter ABC_EthernetPort.RequestStateChange(): RequestedState */
static MI_CONST MI_ParameterDecl ABC_EthernetPort_RequestStateChange_RequestedState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0072650E, /* code */
    MI_T("RequestedState"), /* name */
    ABC_EthernetPort_RequestStateChange_RequestedState_quals, /* qualifiers */
    MI_COUNT(ABC_EthernetPort_RequestStateChange_RequestedState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_EthernetPort_RequestStateChange, RequestedState), /* offset */
};

/* parameter ABC_EthernetPort.RequestStateChange(): Job */
static MI_CONST MI_ParameterDecl ABC_EthernetPort_RequestStateChange_Job_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006A6203, /* code */
    MI_T("Job"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ConcreteJob"), /* className */
    0, /* subscript */
    offsetof(ABC_EthernetPort_RequestStateChange, Job), /* offset */
};

/* parameter ABC_EthernetPort.RequestStateChange(): TimeoutPeriod */
static MI_CONST MI_ParameterDecl ABC_EthernetPort_RequestStateChange_TimeoutPeriod_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0074640D, /* code */
    MI_T("TimeoutPeriod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_EthernetPort_RequestStateChange, TimeoutPeriod), /* offset */
};

static MI_CONST MI_Char* ABC_EthernetPort_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_EthernetPort_RequestStateChange_MIReturn_ModelCorrespondence_qual_value =
{
    ABC_EthernetPort_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_EthernetPort_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_EthernetPort_RequestStateChange_MIReturn_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_EthernetPort_RequestStateChange_MIReturn_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_EthernetPort_RequestStateChange_MIReturn_quals[] =
{
    &ABC_EthernetPort_RequestStateChange_MIReturn_ModelCorrespondence_qual,
};

/* parameter ABC_EthernetPort.RequestStateChange(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_EthernetPort_RequestStateChange_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_EthernetPort_RequestStateChange_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_EthernetPort_RequestStateChange_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_EthernetPort_RequestStateChange, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_EthernetPort_RequestStateChange_params[] =
{
    &ABC_EthernetPort_RequestStateChange_MIReturn_param,
    &ABC_EthernetPort_RequestStateChange_RequestedState_param,
    &ABC_EthernetPort_RequestStateChange_Job_param,
    &ABC_EthernetPort_RequestStateChange_TimeoutPeriod_param,
};

/* method ABC_EthernetPort.RequestStateChange() */
MI_CONST MI_MethodDecl ABC_EthernetPort_RequestStateChange_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00726512, /* code */
    MI_T("RequestStateChange"), /* name */
    ABC_EthernetPort_RequestStateChange_quals, /* qualifiers */
    MI_COUNT(ABC_EthernetPort_RequestStateChange_quals), /* numQualifiers */
    ABC_EthernetPort_RequestStateChange_params, /* parameters */
    MI_COUNT(ABC_EthernetPort_RequestStateChange_params), /* numParameters */
    sizeof(ABC_EthernetPort_RequestStateChange), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_EthernetPort_Invoke_RequestStateChange, /* method */
};

static MI_CONST MI_Char* ABC_EthernetPort_SetPowerState_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PowerManagementService.SetPowerState"),
};

static MI_CONST MI_ConstStringA ABC_EthernetPort_SetPowerState_Deprecated_qual_value =
{
    ABC_EthernetPort_SetPowerState_Deprecated_qual_data_value,
    MI_COUNT(ABC_EthernetPort_SetPowerState_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_EthernetPort_SetPowerState_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_EthernetPort_SetPowerState_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_EthernetPort_SetPowerState_quals[] =
{
    &ABC_EthernetPort_SetPowerState_Deprecated_qual,
};

/* parameter ABC_EthernetPort.SetPowerState(): PowerState */
static MI_CONST MI_ParameterDecl ABC_EthernetPort_SetPowerState_PowerState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0070650A, /* code */
    MI_T("PowerState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_EthernetPort_SetPowerState, PowerState), /* offset */
};

/* parameter ABC_EthernetPort.SetPowerState(): Time */
static MI_CONST MI_ParameterDecl ABC_EthernetPort_SetPowerState_Time_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00746504, /* code */
    MI_T("Time"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_EthernetPort_SetPowerState, Time), /* offset */
};

static MI_CONST MI_Char* ABC_EthernetPort_SetPowerState_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PowerManagementService.SetPowerState"),
};

static MI_CONST MI_ConstStringA ABC_EthernetPort_SetPowerState_MIReturn_Deprecated_qual_value =
{
    ABC_EthernetPort_SetPowerState_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_EthernetPort_SetPowerState_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_EthernetPort_SetPowerState_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_EthernetPort_SetPowerState_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_EthernetPort_SetPowerState_MIReturn_quals[] =
{
    &ABC_EthernetPort_SetPowerState_MIReturn_Deprecated_qual,
};

/* parameter ABC_EthernetPort.SetPowerState(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_EthernetPort_SetPowerState_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_EthernetPort_SetPowerState_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_EthernetPort_SetPowerState_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_EthernetPort_SetPowerState, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_EthernetPort_SetPowerState_params[] =
{
    &ABC_EthernetPort_SetPowerState_MIReturn_param,
    &ABC_EthernetPort_SetPowerState_PowerState_param,
    &ABC_EthernetPort_SetPowerState_Time_param,
};

/* method ABC_EthernetPort.SetPowerState() */
MI_CONST MI_MethodDecl ABC_EthernetPort_SetPowerState_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650D, /* code */
    MI_T("SetPowerState"), /* name */
    ABC_EthernetPort_SetPowerState_quals, /* qualifiers */
    MI_COUNT(ABC_EthernetPort_SetPowerState_quals), /* numQualifiers */
    ABC_EthernetPort_SetPowerState_params, /* parameters */
    MI_COUNT(ABC_EthernetPort_SetPowerState_params), /* numParameters */
    sizeof(ABC_EthernetPort_SetPowerState), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_EthernetPort_Invoke_SetPowerState, /* method */
};

/* parameter ABC_EthernetPort.Reset(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_EthernetPort_Reset_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_EthernetPort_Reset, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_EthernetPort_Reset_params[] =
{
    &ABC_EthernetPort_Reset_MIReturn_param,
};

/* method ABC_EthernetPort.Reset() */
MI_CONST MI_MethodDecl ABC_EthernetPort_Reset_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00727405, /* code */
    MI_T("Reset"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_EthernetPort_Reset_params, /* parameters */
    MI_COUNT(ABC_EthernetPort_Reset_params), /* numParameters */
    sizeof(ABC_EthernetPort_Reset), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_EthernetPort_Invoke_Reset, /* method */
};

static MI_CONST MI_Char* ABC_EthernetPort_EnableDevice_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_EthernetPort_EnableDevice_Deprecated_qual_value =
{
    ABC_EthernetPort_EnableDevice_Deprecated_qual_data_value,
    MI_COUNT(ABC_EthernetPort_EnableDevice_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_EthernetPort_EnableDevice_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_EthernetPort_EnableDevice_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_EthernetPort_EnableDevice_quals[] =
{
    &ABC_EthernetPort_EnableDevice_Deprecated_qual,
};

/* parameter ABC_EthernetPort.EnableDevice(): Enabled */
static MI_CONST MI_ParameterDecl ABC_EthernetPort_EnableDevice_Enabled_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00656407, /* code */
    MI_T("Enabled"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_EthernetPort_EnableDevice, Enabled), /* offset */
};

static MI_CONST MI_Char* ABC_EthernetPort_EnableDevice_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_EthernetPort_EnableDevice_MIReturn_Deprecated_qual_value =
{
    ABC_EthernetPort_EnableDevice_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_EthernetPort_EnableDevice_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_EthernetPort_EnableDevice_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_EthernetPort_EnableDevice_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_EthernetPort_EnableDevice_MIReturn_quals[] =
{
    &ABC_EthernetPort_EnableDevice_MIReturn_Deprecated_qual,
};

/* parameter ABC_EthernetPort.EnableDevice(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_EthernetPort_EnableDevice_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_EthernetPort_EnableDevice_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_EthernetPort_EnableDevice_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_EthernetPort_EnableDevice, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_EthernetPort_EnableDevice_params[] =
{
    &ABC_EthernetPort_EnableDevice_MIReturn_param,
    &ABC_EthernetPort_EnableDevice_Enabled_param,
};

/* method ABC_EthernetPort.EnableDevice() */
MI_CONST MI_MethodDecl ABC_EthernetPort_EnableDevice_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0065650C, /* code */
    MI_T("EnableDevice"), /* name */
    ABC_EthernetPort_EnableDevice_quals, /* qualifiers */
    MI_COUNT(ABC_EthernetPort_EnableDevice_quals), /* numQualifiers */
    ABC_EthernetPort_EnableDevice_params, /* parameters */
    MI_COUNT(ABC_EthernetPort_EnableDevice_params), /* numParameters */
    sizeof(ABC_EthernetPort_EnableDevice), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_EthernetPort_Invoke_EnableDevice, /* method */
};

static MI_CONST MI_Char* ABC_EthernetPort_OnlineDevice_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_EthernetPort_OnlineDevice_Deprecated_qual_value =
{
    ABC_EthernetPort_OnlineDevice_Deprecated_qual_data_value,
    MI_COUNT(ABC_EthernetPort_OnlineDevice_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_EthernetPort_OnlineDevice_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_EthernetPort_OnlineDevice_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_EthernetPort_OnlineDevice_quals[] =
{
    &ABC_EthernetPort_OnlineDevice_Deprecated_qual,
};

/* parameter ABC_EthernetPort.OnlineDevice(): Online */
static MI_CONST MI_ParameterDecl ABC_EthernetPort_OnlineDevice_Online_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006F6506, /* code */
    MI_T("Online"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_EthernetPort_OnlineDevice, Online), /* offset */
};

static MI_CONST MI_Char* ABC_EthernetPort_OnlineDevice_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_EthernetPort_OnlineDevice_MIReturn_Deprecated_qual_value =
{
    ABC_EthernetPort_OnlineDevice_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_EthernetPort_OnlineDevice_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_EthernetPort_OnlineDevice_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_EthernetPort_OnlineDevice_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_EthernetPort_OnlineDevice_MIReturn_quals[] =
{
    &ABC_EthernetPort_OnlineDevice_MIReturn_Deprecated_qual,
};

/* parameter ABC_EthernetPort.OnlineDevice(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_EthernetPort_OnlineDevice_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_EthernetPort_OnlineDevice_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_EthernetPort_OnlineDevice_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_EthernetPort_OnlineDevice, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_EthernetPort_OnlineDevice_params[] =
{
    &ABC_EthernetPort_OnlineDevice_MIReturn_param,
    &ABC_EthernetPort_OnlineDevice_Online_param,
};

/* method ABC_EthernetPort.OnlineDevice() */
MI_CONST MI_MethodDecl ABC_EthernetPort_OnlineDevice_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006F650C, /* code */
    MI_T("OnlineDevice"), /* name */
    ABC_EthernetPort_OnlineDevice_quals, /* qualifiers */
    MI_COUNT(ABC_EthernetPort_OnlineDevice_quals), /* numQualifiers */
    ABC_EthernetPort_OnlineDevice_params, /* parameters */
    MI_COUNT(ABC_EthernetPort_OnlineDevice_params), /* numParameters */
    sizeof(ABC_EthernetPort_OnlineDevice), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_EthernetPort_Invoke_OnlineDevice, /* method */
};

static MI_CONST MI_Char* ABC_EthernetPort_QuiesceDevice_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_EthernetPort_QuiesceDevice_Deprecated_qual_value =
{
    ABC_EthernetPort_QuiesceDevice_Deprecated_qual_data_value,
    MI_COUNT(ABC_EthernetPort_QuiesceDevice_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_EthernetPort_QuiesceDevice_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_EthernetPort_QuiesceDevice_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_EthernetPort_QuiesceDevice_quals[] =
{
    &ABC_EthernetPort_QuiesceDevice_Deprecated_qual,
};

/* parameter ABC_EthernetPort.QuiesceDevice(): Quiesce */
static MI_CONST MI_ParameterDecl ABC_EthernetPort_QuiesceDevice_Quiesce_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00716507, /* code */
    MI_T("Quiesce"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_EthernetPort_QuiesceDevice, Quiesce), /* offset */
};

static MI_CONST MI_Char* ABC_EthernetPort_QuiesceDevice_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_EthernetPort_QuiesceDevice_MIReturn_Deprecated_qual_value =
{
    ABC_EthernetPort_QuiesceDevice_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_EthernetPort_QuiesceDevice_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_EthernetPort_QuiesceDevice_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_EthernetPort_QuiesceDevice_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_EthernetPort_QuiesceDevice_MIReturn_quals[] =
{
    &ABC_EthernetPort_QuiesceDevice_MIReturn_Deprecated_qual,
};

/* parameter ABC_EthernetPort.QuiesceDevice(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_EthernetPort_QuiesceDevice_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_EthernetPort_QuiesceDevice_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_EthernetPort_QuiesceDevice_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_EthernetPort_QuiesceDevice, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_EthernetPort_QuiesceDevice_params[] =
{
    &ABC_EthernetPort_QuiesceDevice_MIReturn_param,
    &ABC_EthernetPort_QuiesceDevice_Quiesce_param,
};

/* method ABC_EthernetPort.QuiesceDevice() */
MI_CONST MI_MethodDecl ABC_EthernetPort_QuiesceDevice_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0071650D, /* code */
    MI_T("QuiesceDevice"), /* name */
    ABC_EthernetPort_QuiesceDevice_quals, /* qualifiers */
    MI_COUNT(ABC_EthernetPort_QuiesceDevice_quals), /* numQualifiers */
    ABC_EthernetPort_QuiesceDevice_params, /* parameters */
    MI_COUNT(ABC_EthernetPort_QuiesceDevice_params), /* numParameters */
    sizeof(ABC_EthernetPort_QuiesceDevice), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_EthernetPort_Invoke_QuiesceDevice, /* method */
};

/* parameter ABC_EthernetPort.SaveProperties(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_EthernetPort_SaveProperties_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_EthernetPort_SaveProperties, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_EthernetPort_SaveProperties_params[] =
{
    &ABC_EthernetPort_SaveProperties_MIReturn_param,
};

/* method ABC_EthernetPort.SaveProperties() */
MI_CONST MI_MethodDecl ABC_EthernetPort_SaveProperties_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073730E, /* code */
    MI_T("SaveProperties"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_EthernetPort_SaveProperties_params, /* parameters */
    MI_COUNT(ABC_EthernetPort_SaveProperties_params), /* numParameters */
    sizeof(ABC_EthernetPort_SaveProperties), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_EthernetPort_Invoke_SaveProperties, /* method */
};

/* parameter ABC_EthernetPort.RestoreProperties(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_EthernetPort_RestoreProperties_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_EthernetPort_RestoreProperties, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_EthernetPort_RestoreProperties_params[] =
{
    &ABC_EthernetPort_RestoreProperties_MIReturn_param,
};

/* method ABC_EthernetPort.RestoreProperties() */
MI_CONST MI_MethodDecl ABC_EthernetPort_RestoreProperties_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00727311, /* code */
    MI_T("RestoreProperties"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_EthernetPort_RestoreProperties_params, /* parameters */
    MI_COUNT(ABC_EthernetPort_RestoreProperties_params), /* numParameters */
    sizeof(ABC_EthernetPort_RestoreProperties), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_EthernetPort_Invoke_RestoreProperties, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST ABC_EthernetPort_meths[] =
{
    &ABC_EthernetPort_RequestStateChange_rtti,
    &ABC_EthernetPort_SetPowerState_rtti,
    &ABC_EthernetPort_Reset_rtti,
    &ABC_EthernetPort_EnableDevice_rtti,
    &ABC_EthernetPort_OnlineDevice_rtti,
    &ABC_EthernetPort_QuiesceDevice_rtti,
    &ABC_EthernetPort_SaveProperties_rtti,
    &ABC_EthernetPort_RestoreProperties_rtti,
};

static MI_CONST MI_ProviderFT ABC_EthernetPort_funcs =
{
  (MI_ProviderFT_Load)ABC_EthernetPort_Load,
  (MI_ProviderFT_Unload)ABC_EthernetPort_Unload,
  (MI_ProviderFT_GetInstance)ABC_EthernetPort_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_EthernetPort_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_EthernetPort_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_EthernetPort_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_EthernetPort_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_EthernetPort_UMLPackagePath_qual_value = MI_T("CIM::Device::Ports");

static MI_CONST MI_Qualifier ABC_EthernetPort_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_EthernetPort_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_EthernetPort_quals[] =
{
    &ABC_EthernetPort_UMLPackagePath_qual,
};

/* class ABC_EthernetPort */
MI_CONST MI_ClassDecl ABC_EthernetPort_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00617410, /* code */
    MI_T("ABC_EthernetPort"), /* name */
    ABC_EthernetPort_quals, /* qualifiers */
    MI_COUNT(ABC_EthernetPort_quals), /* numQualifiers */
    ABC_EthernetPort_props, /* properties */
    MI_COUNT(ABC_EthernetPort_props), /* numProperties */
    sizeof(ABC_EthernetPort), /* size */
    MI_T("CIM_EthernetPort"), /* superClass */
    &CIM_EthernetPort_rtti, /* superClassDecl */
    ABC_EthernetPort_meths, /* methods */
    MI_COUNT(ABC_EthernetPort_meths), /* numMethods */
    &schemaDecl, /* schema */
    &ABC_EthernetPort_funcs, /* functions */
};

/*
**==============================================================================
**
** CIM_ServiceAccessPoint
**
**==============================================================================
*/

static MI_CONST MI_Uint32 CIM_ServiceAccessPoint_Name_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_ServiceAccessPoint_Name_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ServiceAccessPoint_Name_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_ServiceAccessPoint_Name_Override_qual_value = MI_T("Name");

static MI_CONST MI_Qualifier CIM_ServiceAccessPoint_Name_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ServiceAccessPoint_Name_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ServiceAccessPoint_Name_quals[] =
{
    &CIM_ServiceAccessPoint_Name_MaxLen_qual,
    &CIM_ServiceAccessPoint_Name_Override_qual,
};

/* property CIM_ServiceAccessPoint.Name */
static MI_CONST MI_PropertyDecl CIM_ServiceAccessPoint_Name_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    CIM_ServiceAccessPoint_Name_quals, /* qualifiers */
    MI_COUNT(CIM_ServiceAccessPoint_Name_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ServiceAccessPoint, Name), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ServiceAccessPoint"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_ServiceAccessPoint_SystemCreationClassName_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_ServiceAccessPoint_SystemCreationClassName_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ServiceAccessPoint_SystemCreationClassName_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_ServiceAccessPoint_SystemCreationClassName_Propagated_qual_value = MI_T("CIM_System.CreationClassName");

static MI_CONST MI_Qualifier CIM_ServiceAccessPoint_SystemCreationClassName_Propagated_qual =
{
    MI_T("Propagated"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_ServiceAccessPoint_SystemCreationClassName_Propagated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ServiceAccessPoint_SystemCreationClassName_quals[] =
{
    &CIM_ServiceAccessPoint_SystemCreationClassName_MaxLen_qual,
    &CIM_ServiceAccessPoint_SystemCreationClassName_Propagated_qual,
};

/* property CIM_ServiceAccessPoint.SystemCreationClassName */
static MI_CONST MI_PropertyDecl CIM_ServiceAccessPoint_SystemCreationClassName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00736517, /* code */
    MI_T("SystemCreationClassName"), /* name */
    CIM_ServiceAccessPoint_SystemCreationClassName_quals, /* qualifiers */
    MI_COUNT(CIM_ServiceAccessPoint_SystemCreationClassName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ServiceAccessPoint, SystemCreationClassName), /* offset */
    MI_T("CIM_ServiceAccessPoint"), /* origin */
    MI_T("CIM_ServiceAccessPoint"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_ServiceAccessPoint_SystemName_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_ServiceAccessPoint_SystemName_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ServiceAccessPoint_SystemName_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_ServiceAccessPoint_SystemName_Propagated_qual_value = MI_T("CIM_System.Name");

static MI_CONST MI_Qualifier CIM_ServiceAccessPoint_SystemName_Propagated_qual =
{
    MI_T("Propagated"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_ServiceAccessPoint_SystemName_Propagated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ServiceAccessPoint_SystemName_quals[] =
{
    &CIM_ServiceAccessPoint_SystemName_MaxLen_qual,
    &CIM_ServiceAccessPoint_SystemName_Propagated_qual,
};

/* property CIM_ServiceAccessPoint.SystemName */
static MI_CONST MI_PropertyDecl CIM_ServiceAccessPoint_SystemName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0073650A, /* code */
    MI_T("SystemName"), /* name */
    CIM_ServiceAccessPoint_SystemName_quals, /* qualifiers */
    MI_COUNT(CIM_ServiceAccessPoint_SystemName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ServiceAccessPoint, SystemName), /* offset */
    MI_T("CIM_ServiceAccessPoint"), /* origin */
    MI_T("CIM_ServiceAccessPoint"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_ServiceAccessPoint_CreationClassName_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_ServiceAccessPoint_CreationClassName_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ServiceAccessPoint_CreationClassName_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ServiceAccessPoint_CreationClassName_quals[] =
{
    &CIM_ServiceAccessPoint_CreationClassName_MaxLen_qual,
};

/* property CIM_ServiceAccessPoint.CreationClassName */
static MI_CONST MI_PropertyDecl CIM_ServiceAccessPoint_CreationClassName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00636511, /* code */
    MI_T("CreationClassName"), /* name */
    CIM_ServiceAccessPoint_CreationClassName_quals, /* qualifiers */
    MI_COUNT(CIM_ServiceAccessPoint_CreationClassName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ServiceAccessPoint, CreationClassName), /* offset */
    MI_T("CIM_ServiceAccessPoint"), /* origin */
    MI_T("CIM_ServiceAccessPoint"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_ServiceAccessPoint_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ServiceAccessPoint_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_EnabledLogicalElement_EnabledState_prop,
    &CIM_EnabledLogicalElement_OtherEnabledState_prop,
    &CIM_EnabledLogicalElement_RequestedState_prop,
    &CIM_EnabledLogicalElement_EnabledDefault_prop,
    &CIM_EnabledLogicalElement_TimeOfLastStateChange_prop,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_prop,
    &CIM_EnabledLogicalElement_TransitioningToState_prop,
    &CIM_ServiceAccessPoint_SystemCreationClassName_prop,
    &CIM_ServiceAccessPoint_SystemName_prop,
    &CIM_ServiceAccessPoint_CreationClassName_prop,
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_ServiceAccessPoint_meths[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_rtti,
};

static MI_CONST MI_Char* CIM_ServiceAccessPoint_UMLPackagePath_qual_value = MI_T("CIM::Core::Service");

static MI_CONST MI_Qualifier CIM_ServiceAccessPoint_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_ServiceAccessPoint_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_ServiceAccessPoint_Version_qual_value = MI_T("2.10.0");

static MI_CONST MI_Qualifier CIM_ServiceAccessPoint_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_ServiceAccessPoint_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ServiceAccessPoint_quals[] =
{
    &CIM_ServiceAccessPoint_UMLPackagePath_qual,
    &CIM_ServiceAccessPoint_Version_qual,
};

/* class CIM_ServiceAccessPoint */
MI_CONST MI_ClassDecl CIM_ServiceAccessPoint_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00637416, /* code */
    MI_T("CIM_ServiceAccessPoint"), /* name */
    CIM_ServiceAccessPoint_quals, /* qualifiers */
    MI_COUNT(CIM_ServiceAccessPoint_quals), /* numQualifiers */
    CIM_ServiceAccessPoint_props, /* properties */
    MI_COUNT(CIM_ServiceAccessPoint_props), /* numProperties */
    sizeof(CIM_ServiceAccessPoint), /* size */
    MI_T("CIM_EnabledLogicalElement"), /* superClass */
    &CIM_EnabledLogicalElement_rtti, /* superClassDecl */
    CIM_ServiceAccessPoint_meths, /* methods */
    MI_COUNT(CIM_ServiceAccessPoint_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_ProtocolEndpoint
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_ProtocolEndpoint_Description_Override_qual_value = MI_T("Description");

static MI_CONST MI_Qualifier CIM_ProtocolEndpoint_Description_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ProtocolEndpoint_Description_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ProtocolEndpoint_Description_quals[] =
{
    &CIM_ProtocolEndpoint_Description_Override_qual,
};

/* property CIM_ProtocolEndpoint.Description */
static MI_CONST MI_PropertyDecl CIM_ProtocolEndpoint_Description_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E0B, /* code */
    MI_T("Description"), /* name */
    CIM_ProtocolEndpoint_Description_quals, /* qualifiers */
    MI_COUNT(CIM_ProtocolEndpoint_Description_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ProtocolEndpoint, Description), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_ProtocolEndpoint"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_ProtocolEndpoint_Name_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_ProtocolEndpoint_Name_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ProtocolEndpoint_Name_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_ProtocolEndpoint_Name_Override_qual_value = MI_T("Name");

static MI_CONST MI_Qualifier CIM_ProtocolEndpoint_Name_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ProtocolEndpoint_Name_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ProtocolEndpoint_Name_quals[] =
{
    &CIM_ProtocolEndpoint_Name_MaxLen_qual,
    &CIM_ProtocolEndpoint_Name_Override_qual,
};

/* property CIM_ProtocolEndpoint.Name */
static MI_CONST MI_PropertyDecl CIM_ProtocolEndpoint_Name_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    CIM_ProtocolEndpoint_Name_quals, /* qualifiers */
    MI_COUNT(CIM_ProtocolEndpoint_Name_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ProtocolEndpoint, Name), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ProtocolEndpoint"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ProtocolEndpoint_OperationalStatus_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_ProtocolEndpoint_OperationalStatus_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_ProtocolEndpoint_OperationalStatus_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_ProtocolEndpoint_OperationalStatus_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ManagedSystemElement.StatusDescriptions"),
};

static MI_CONST MI_ConstStringA CIM_ProtocolEndpoint_OperationalStatus_ModelCorrespondence_qual_value =
{
    CIM_ProtocolEndpoint_OperationalStatus_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_ProtocolEndpoint_OperationalStatus_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ProtocolEndpoint_OperationalStatus_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_ProtocolEndpoint_OperationalStatus_ModelCorrespondence_qual_value
};

static MI_CONST MI_Char* CIM_ProtocolEndpoint_OperationalStatus_Override_qual_value = MI_T("OperationalStatus");

static MI_CONST MI_Qualifier CIM_ProtocolEndpoint_OperationalStatus_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ProtocolEndpoint_OperationalStatus_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ProtocolEndpoint_OperationalStatus_quals[] =
{
    &CIM_ProtocolEndpoint_OperationalStatus_ArrayType_qual,
    &CIM_ProtocolEndpoint_OperationalStatus_ModelCorrespondence_qual,
    &CIM_ProtocolEndpoint_OperationalStatus_Override_qual,
};

/* property CIM_ProtocolEndpoint.OperationalStatus */
static MI_CONST MI_PropertyDecl CIM_ProtocolEndpoint_OperationalStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F7311, /* code */
    MI_T("OperationalStatus"), /* name */
    CIM_ProtocolEndpoint_OperationalStatus_quals, /* qualifiers */
    MI_COUNT(CIM_ProtocolEndpoint_OperationalStatus_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ProtocolEndpoint, OperationalStatus), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ProtocolEndpoint"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ProtocolEndpoint_EnabledState_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.OtherEnabledState"),
};

static MI_CONST MI_ConstStringA CIM_ProtocolEndpoint_EnabledState_ModelCorrespondence_qual_value =
{
    CIM_ProtocolEndpoint_EnabledState_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_ProtocolEndpoint_EnabledState_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ProtocolEndpoint_EnabledState_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_ProtocolEndpoint_EnabledState_ModelCorrespondence_qual_value
};

static MI_CONST MI_Char* CIM_ProtocolEndpoint_EnabledState_Override_qual_value = MI_T("EnabledState");

static MI_CONST MI_Qualifier CIM_ProtocolEndpoint_EnabledState_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ProtocolEndpoint_EnabledState_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ProtocolEndpoint_EnabledState_quals[] =
{
    &CIM_ProtocolEndpoint_EnabledState_ModelCorrespondence_qual,
    &CIM_ProtocolEndpoint_EnabledState_Override_qual,
};

/* property CIM_ProtocolEndpoint.EnabledState */
static MI_CONST MI_PropertyDecl CIM_ProtocolEndpoint_EnabledState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065650C, /* code */
    MI_T("EnabledState"), /* name */
    CIM_ProtocolEndpoint_EnabledState_quals, /* qualifiers */
    MI_COUNT(CIM_ProtocolEndpoint_EnabledState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ProtocolEndpoint, EnabledState), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_ProtocolEndpoint"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ProtocolEndpoint_TimeOfLastStateChange_Override_qual_value = MI_T("TimeOfLastStateChange");

static MI_CONST MI_Qualifier CIM_ProtocolEndpoint_TimeOfLastStateChange_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ProtocolEndpoint_TimeOfLastStateChange_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ProtocolEndpoint_TimeOfLastStateChange_quals[] =
{
    &CIM_ProtocolEndpoint_TimeOfLastStateChange_Override_qual,
};

/* property CIM_ProtocolEndpoint.TimeOfLastStateChange */
static MI_CONST MI_PropertyDecl CIM_ProtocolEndpoint_TimeOfLastStateChange_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00746515, /* code */
    MI_T("TimeOfLastStateChange"), /* name */
    CIM_ProtocolEndpoint_TimeOfLastStateChange_quals, /* qualifiers */
    MI_COUNT(CIM_ProtocolEndpoint_TimeOfLastStateChange_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ProtocolEndpoint, TimeOfLastStateChange), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_ProtocolEndpoint"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_ProtocolEndpoint_NameFormat_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_ProtocolEndpoint_NameFormat_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ProtocolEndpoint_NameFormat_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ProtocolEndpoint_NameFormat_quals[] =
{
    &CIM_ProtocolEndpoint_NameFormat_MaxLen_qual,
};

/* property CIM_ProtocolEndpoint.NameFormat */
static MI_CONST MI_PropertyDecl CIM_ProtocolEndpoint_NameFormat_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E740A, /* code */
    MI_T("NameFormat"), /* name */
    CIM_ProtocolEndpoint_NameFormat_quals, /* qualifiers */
    MI_COUNT(CIM_ProtocolEndpoint_NameFormat_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ProtocolEndpoint, NameFormat), /* offset */
    MI_T("CIM_ProtocolEndpoint"), /* origin */
    MI_T("CIM_ProtocolEndpoint"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ProtocolEndpoint_ProtocolType_Deprecated_qual_data_value[] =
{
    MI_T("CIM_ProtocolEndpoint.ProtocolIFType"),
};

static MI_CONST MI_ConstStringA CIM_ProtocolEndpoint_ProtocolType_Deprecated_qual_value =
{
    CIM_ProtocolEndpoint_ProtocolType_Deprecated_qual_data_value,
    MI_COUNT(CIM_ProtocolEndpoint_ProtocolType_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ProtocolEndpoint_ProtocolType_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ProtocolEndpoint_ProtocolType_Deprecated_qual_value
};

static MI_CONST MI_Char* CIM_ProtocolEndpoint_ProtocolType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ProtocolEndpoint.OtherTypeDescription"),
};

static MI_CONST MI_ConstStringA CIM_ProtocolEndpoint_ProtocolType_ModelCorrespondence_qual_value =
{
    CIM_ProtocolEndpoint_ProtocolType_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_ProtocolEndpoint_ProtocolType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ProtocolEndpoint_ProtocolType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_ProtocolEndpoint_ProtocolType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ProtocolEndpoint_ProtocolType_quals[] =
{
    &CIM_ProtocolEndpoint_ProtocolType_Deprecated_qual,
    &CIM_ProtocolEndpoint_ProtocolType_ModelCorrespondence_qual,
};

/* property CIM_ProtocolEndpoint.ProtocolType */
static MI_CONST MI_PropertyDecl CIM_ProtocolEndpoint_ProtocolType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070650C, /* code */
    MI_T("ProtocolType"), /* name */
    CIM_ProtocolEndpoint_ProtocolType_quals, /* qualifiers */
    MI_COUNT(CIM_ProtocolEndpoint_ProtocolType_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ProtocolEndpoint, ProtocolType), /* offset */
    MI_T("CIM_ProtocolEndpoint"), /* origin */
    MI_T("CIM_ProtocolEndpoint"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ProtocolEndpoint_ProtocolIFType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ProtocolEndpoint.OtherTypeDescription"),
};

static MI_CONST MI_ConstStringA CIM_ProtocolEndpoint_ProtocolIFType_ModelCorrespondence_qual_value =
{
    CIM_ProtocolEndpoint_ProtocolIFType_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_ProtocolEndpoint_ProtocolIFType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ProtocolEndpoint_ProtocolIFType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_ProtocolEndpoint_ProtocolIFType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ProtocolEndpoint_ProtocolIFType_quals[] =
{
    &CIM_ProtocolEndpoint_ProtocolIFType_ModelCorrespondence_qual,
};

/* property CIM_ProtocolEndpoint.ProtocolIFType */
static MI_CONST MI_PropertyDecl CIM_ProtocolEndpoint_ProtocolIFType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070650E, /* code */
    MI_T("ProtocolIFType"), /* name */
    CIM_ProtocolEndpoint_ProtocolIFType_quals, /* qualifiers */
    MI_COUNT(CIM_ProtocolEndpoint_ProtocolIFType_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ProtocolEndpoint, ProtocolIFType), /* offset */
    MI_T("CIM_ProtocolEndpoint"), /* origin */
    MI_T("CIM_ProtocolEndpoint"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_ProtocolEndpoint_OtherTypeDescription_MaxLen_qual_value = 64U;

static MI_CONST MI_Qualifier CIM_ProtocolEndpoint_OtherTypeDescription_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ProtocolEndpoint_OtherTypeDescription_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_ProtocolEndpoint_OtherTypeDescription_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ProtocolEndpoint.ProtocolType"),
    MI_T("CIM_ProtocolEndpoint.ProtocolIFType"),
};

static MI_CONST MI_ConstStringA CIM_ProtocolEndpoint_OtherTypeDescription_ModelCorrespondence_qual_value =
{
    CIM_ProtocolEndpoint_OtherTypeDescription_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_ProtocolEndpoint_OtherTypeDescription_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ProtocolEndpoint_OtherTypeDescription_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_ProtocolEndpoint_OtherTypeDescription_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ProtocolEndpoint_OtherTypeDescription_quals[] =
{
    &CIM_ProtocolEndpoint_OtherTypeDescription_MaxLen_qual,
    &CIM_ProtocolEndpoint_OtherTypeDescription_ModelCorrespondence_qual,
};

/* property CIM_ProtocolEndpoint.OtherTypeDescription */
static MI_CONST MI_PropertyDecl CIM_ProtocolEndpoint_OtherTypeDescription_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6E14, /* code */
    MI_T("OtherTypeDescription"), /* name */
    CIM_ProtocolEndpoint_OtherTypeDescription_quals, /* qualifiers */
    MI_COUNT(CIM_ProtocolEndpoint_OtherTypeDescription_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ProtocolEndpoint, OtherTypeDescription), /* offset */
    MI_T("CIM_ProtocolEndpoint"), /* origin */
    MI_T("CIM_ProtocolEndpoint"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_ProtocolEndpoint_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ProtocolEndpoint_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ProtocolEndpoint_Name_prop,
    &CIM_ProtocolEndpoint_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_ProtocolEndpoint_EnabledState_prop,
    &CIM_EnabledLogicalElement_OtherEnabledState_prop,
    &CIM_EnabledLogicalElement_RequestedState_prop,
    &CIM_EnabledLogicalElement_EnabledDefault_prop,
    &CIM_ProtocolEndpoint_TimeOfLastStateChange_prop,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_prop,
    &CIM_EnabledLogicalElement_TransitioningToState_prop,
    &CIM_ServiceAccessPoint_SystemCreationClassName_prop,
    &CIM_ServiceAccessPoint_SystemName_prop,
    &CIM_ServiceAccessPoint_CreationClassName_prop,
    &CIM_ProtocolEndpoint_NameFormat_prop,
    &CIM_ProtocolEndpoint_ProtocolType_prop,
    &CIM_ProtocolEndpoint_ProtocolIFType_prop,
    &CIM_ProtocolEndpoint_OtherTypeDescription_prop,
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_ProtocolEndpoint_meths[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_rtti,
};

static MI_CONST MI_Char* CIM_ProtocolEndpoint_UMLPackagePath_qual_value = MI_T("CIM::Core::Service");

static MI_CONST MI_Qualifier CIM_ProtocolEndpoint_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_ProtocolEndpoint_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_ProtocolEndpoint_Version_qual_value = MI_T("2.15.0");

static MI_CONST MI_Qualifier CIM_ProtocolEndpoint_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_ProtocolEndpoint_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ProtocolEndpoint_quals[] =
{
    &CIM_ProtocolEndpoint_UMLPackagePath_qual,
    &CIM_ProtocolEndpoint_Version_qual,
};

/* class CIM_ProtocolEndpoint */
MI_CONST MI_ClassDecl CIM_ProtocolEndpoint_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00637414, /* code */
    MI_T("CIM_ProtocolEndpoint"), /* name */
    CIM_ProtocolEndpoint_quals, /* qualifiers */
    MI_COUNT(CIM_ProtocolEndpoint_quals), /* numQualifiers */
    CIM_ProtocolEndpoint_props, /* properties */
    MI_COUNT(CIM_ProtocolEndpoint_props), /* numProperties */
    sizeof(CIM_ProtocolEndpoint), /* size */
    MI_T("CIM_ServiceAccessPoint"), /* superClass */
    &CIM_ServiceAccessPoint_rtti, /* superClassDecl */
    CIM_ProtocolEndpoint_meths, /* methods */
    MI_COUNT(CIM_ProtocolEndpoint_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** CIM_VLANEndpoint
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_VLANEndpoint_DesiredEndpointMode_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_VLANEndpoint.OperationalEndpointMode"),
    MI_T("CIM_VLANEndpoint.OtherEndpointMode"),
};

static MI_CONST MI_ConstStringA CIM_VLANEndpoint_DesiredEndpointMode_ModelCorrespondence_qual_value =
{
    CIM_VLANEndpoint_DesiredEndpointMode_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_VLANEndpoint_DesiredEndpointMode_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_VLANEndpoint_DesiredEndpointMode_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_VLANEndpoint_DesiredEndpointMode_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_VLANEndpoint_DesiredEndpointMode_quals[] =
{
    &CIM_VLANEndpoint_DesiredEndpointMode_ModelCorrespondence_qual,
};

/* property CIM_VLANEndpoint.DesiredEndpointMode */
static MI_CONST MI_PropertyDecl CIM_VLANEndpoint_DesiredEndpointMode_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646513, /* code */
    MI_T("DesiredEndpointMode"), /* name */
    CIM_VLANEndpoint_DesiredEndpointMode_quals, /* qualifiers */
    MI_COUNT(CIM_VLANEndpoint_DesiredEndpointMode_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_VLANEndpoint, DesiredEndpointMode), /* offset */
    MI_T("CIM_VLANEndpoint"), /* origin */
    MI_T("CIM_VLANEndpoint"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_VLANEndpoint_OtherEndpointMode_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_VLANEndpoint.DesiredEndpointMode"),
    MI_T("CIM_VLANEndpoint.OperationalEndpointMode"),
};

static MI_CONST MI_ConstStringA CIM_VLANEndpoint_OtherEndpointMode_ModelCorrespondence_qual_value =
{
    CIM_VLANEndpoint_OtherEndpointMode_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_VLANEndpoint_OtherEndpointMode_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_VLANEndpoint_OtherEndpointMode_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_VLANEndpoint_OtherEndpointMode_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_VLANEndpoint_OtherEndpointMode_quals[] =
{
    &CIM_VLANEndpoint_OtherEndpointMode_ModelCorrespondence_qual,
};

/* property CIM_VLANEndpoint.OtherEndpointMode */
static MI_CONST MI_PropertyDecl CIM_VLANEndpoint_OtherEndpointMode_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6511, /* code */
    MI_T("OtherEndpointMode"), /* name */
    CIM_VLANEndpoint_OtherEndpointMode_quals, /* qualifiers */
    MI_COUNT(CIM_VLANEndpoint_OtherEndpointMode_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_VLANEndpoint, OtherEndpointMode), /* offset */
    MI_T("CIM_VLANEndpoint"), /* origin */
    MI_T("CIM_VLANEndpoint"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_VLANEndpoint_OperationalEndpointMode_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_VLANEndpoint.DesiredEndpointMode"),
    MI_T("CIM_VLANEndpoint.OtherEndpointMode"),
};

static MI_CONST MI_ConstStringA CIM_VLANEndpoint_OperationalEndpointMode_ModelCorrespondence_qual_value =
{
    CIM_VLANEndpoint_OperationalEndpointMode_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_VLANEndpoint_OperationalEndpointMode_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_VLANEndpoint_OperationalEndpointMode_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_VLANEndpoint_OperationalEndpointMode_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_VLANEndpoint_OperationalEndpointMode_quals[] =
{
    &CIM_VLANEndpoint_OperationalEndpointMode_ModelCorrespondence_qual,
};

/* property CIM_VLANEndpoint.OperationalEndpointMode */
static MI_CONST MI_PropertyDecl CIM_VLANEndpoint_OperationalEndpointMode_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6517, /* code */
    MI_T("OperationalEndpointMode"), /* name */
    CIM_VLANEndpoint_OperationalEndpointMode_quals, /* qualifiers */
    MI_COUNT(CIM_VLANEndpoint_OperationalEndpointMode_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_VLANEndpoint, OperationalEndpointMode), /* offset */
    MI_T("CIM_VLANEndpoint"), /* origin */
    MI_T("CIM_VLANEndpoint"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_VLANEndpoint_DesiredVLANTrunkEncapsulation_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_VLANEndpointCapabilities.SupportsTrunkEncapsulationNegotiation"),
    MI_T("CIM_VLANEndpoint.OperationalVLANTrunkEncapsulation"),
    MI_T("CIM_VLANEndpoint.OtherTrunkEncapsulation"),
};

static MI_CONST MI_ConstStringA CIM_VLANEndpoint_DesiredVLANTrunkEncapsulation_ModelCorrespondence_qual_value =
{
    CIM_VLANEndpoint_DesiredVLANTrunkEncapsulation_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_VLANEndpoint_DesiredVLANTrunkEncapsulation_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_VLANEndpoint_DesiredVLANTrunkEncapsulation_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_VLANEndpoint_DesiredVLANTrunkEncapsulation_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_VLANEndpoint_DesiredVLANTrunkEncapsulation_quals[] =
{
    &CIM_VLANEndpoint_DesiredVLANTrunkEncapsulation_ModelCorrespondence_qual,
};

/* property CIM_VLANEndpoint.DesiredVLANTrunkEncapsulation */
static MI_CONST MI_PropertyDecl CIM_VLANEndpoint_DesiredVLANTrunkEncapsulation_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E1D, /* code */
    MI_T("DesiredVLANTrunkEncapsulation"), /* name */
    CIM_VLANEndpoint_DesiredVLANTrunkEncapsulation_quals, /* qualifiers */
    MI_COUNT(CIM_VLANEndpoint_DesiredVLANTrunkEncapsulation_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_VLANEndpoint, DesiredVLANTrunkEncapsulation), /* offset */
    MI_T("CIM_VLANEndpoint"), /* origin */
    MI_T("CIM_VLANEndpoint"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_VLANEndpoint_OtherTrunkEncapsulation_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_VLANEndpoint.DesiredVLANTrunkEncapsulation"),
    MI_T("CIM_VLANEndpoint.OperationalVLANTrunkEncapsulation"),
};

static MI_CONST MI_ConstStringA CIM_VLANEndpoint_OtherTrunkEncapsulation_ModelCorrespondence_qual_value =
{
    CIM_VLANEndpoint_OtherTrunkEncapsulation_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_VLANEndpoint_OtherTrunkEncapsulation_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_VLANEndpoint_OtherTrunkEncapsulation_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_VLANEndpoint_OtherTrunkEncapsulation_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_VLANEndpoint_OtherTrunkEncapsulation_quals[] =
{
    &CIM_VLANEndpoint_OtherTrunkEncapsulation_ModelCorrespondence_qual,
};

/* property CIM_VLANEndpoint.OtherTrunkEncapsulation */
static MI_CONST MI_PropertyDecl CIM_VLANEndpoint_OtherTrunkEncapsulation_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6E17, /* code */
    MI_T("OtherTrunkEncapsulation"), /* name */
    CIM_VLANEndpoint_OtherTrunkEncapsulation_quals, /* qualifiers */
    MI_COUNT(CIM_VLANEndpoint_OtherTrunkEncapsulation_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_VLANEndpoint, OtherTrunkEncapsulation), /* offset */
    MI_T("CIM_VLANEndpoint"), /* origin */
    MI_T("CIM_VLANEndpoint"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_VLANEndpoint_OperationalVLANTrunkEncapsulation_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_VLANEndpoint.OtherTrunkEncapsulation"),
    MI_T("CIM_VLANEndpoint.DesiredVLANTrunkEncapsulation"),
};

static MI_CONST MI_ConstStringA CIM_VLANEndpoint_OperationalVLANTrunkEncapsulation_ModelCorrespondence_qual_value =
{
    CIM_VLANEndpoint_OperationalVLANTrunkEncapsulation_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_VLANEndpoint_OperationalVLANTrunkEncapsulation_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_VLANEndpoint_OperationalVLANTrunkEncapsulation_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_VLANEndpoint_OperationalVLANTrunkEncapsulation_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_VLANEndpoint_OperationalVLANTrunkEncapsulation_quals[] =
{
    &CIM_VLANEndpoint_OperationalVLANTrunkEncapsulation_ModelCorrespondence_qual,
};

/* property CIM_VLANEndpoint.OperationalVLANTrunkEncapsulation */
static MI_CONST MI_PropertyDecl CIM_VLANEndpoint_OperationalVLANTrunkEncapsulation_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6E21, /* code */
    MI_T("OperationalVLANTrunkEncapsulation"), /* name */
    CIM_VLANEndpoint_OperationalVLANTrunkEncapsulation_quals, /* qualifiers */
    MI_COUNT(CIM_VLANEndpoint_OperationalVLANTrunkEncapsulation_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_VLANEndpoint, OperationalVLANTrunkEncapsulation), /* offset */
    MI_T("CIM_VLANEndpoint"), /* origin */
    MI_T("CIM_VLANEndpoint"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_VLANEndpoint_GVRPStatus_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_VLANEndpoint.OperationalEndpointMode"),
    MI_T("CIM_VLANEndpointCapabilities.Dot1QTagging"),
};

static MI_CONST MI_ConstStringA CIM_VLANEndpoint_GVRPStatus_ModelCorrespondence_qual_value =
{
    CIM_VLANEndpoint_GVRPStatus_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_VLANEndpoint_GVRPStatus_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_VLANEndpoint_GVRPStatus_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_VLANEndpoint_GVRPStatus_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_VLANEndpoint_GVRPStatus_quals[] =
{
    &CIM_VLANEndpoint_GVRPStatus_ModelCorrespondence_qual,
};

/* property CIM_VLANEndpoint.GVRPStatus */
static MI_CONST MI_PropertyDecl CIM_VLANEndpoint_GVRPStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0067730A, /* code */
    MI_T("GVRPStatus"), /* name */
    CIM_VLANEndpoint_GVRPStatus_quals, /* qualifiers */
    MI_COUNT(CIM_VLANEndpoint_GVRPStatus_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_VLANEndpoint, GVRPStatus), /* offset */
    MI_T("CIM_VLANEndpoint"), /* origin */
    MI_T("CIM_VLANEndpoint"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_VLANEndpoint_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ProtocolEndpoint_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ProtocolEndpoint_Name_prop,
    &CIM_ProtocolEndpoint_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_ProtocolEndpoint_EnabledState_prop,
    &CIM_EnabledLogicalElement_OtherEnabledState_prop,
    &CIM_EnabledLogicalElement_RequestedState_prop,
    &CIM_EnabledLogicalElement_EnabledDefault_prop,
    &CIM_ProtocolEndpoint_TimeOfLastStateChange_prop,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_prop,
    &CIM_EnabledLogicalElement_TransitioningToState_prop,
    &CIM_ServiceAccessPoint_SystemCreationClassName_prop,
    &CIM_ServiceAccessPoint_SystemName_prop,
    &CIM_ServiceAccessPoint_CreationClassName_prop,
    &CIM_ProtocolEndpoint_NameFormat_prop,
    &CIM_ProtocolEndpoint_ProtocolType_prop,
    &CIM_ProtocolEndpoint_ProtocolIFType_prop,
    &CIM_ProtocolEndpoint_OtherTypeDescription_prop,
    &CIM_VLANEndpoint_DesiredEndpointMode_prop,
    &CIM_VLANEndpoint_OtherEndpointMode_prop,
    &CIM_VLANEndpoint_OperationalEndpointMode_prop,
    &CIM_VLANEndpoint_DesiredVLANTrunkEncapsulation_prop,
    &CIM_VLANEndpoint_OtherTrunkEncapsulation_prop,
    &CIM_VLANEndpoint_OperationalVLANTrunkEncapsulation_prop,
    &CIM_VLANEndpoint_GVRPStatus_prop,
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_VLANEndpoint_meths[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_rtti,
};

static MI_CONST MI_Char* CIM_VLANEndpoint_UMLPackagePath_qual_value = MI_T("CIM::Network::VLAN");

static MI_CONST MI_Qualifier CIM_VLANEndpoint_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_VLANEndpoint_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_VLANEndpoint_Version_qual_value = MI_T("2.26.0");

static MI_CONST MI_Qualifier CIM_VLANEndpoint_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_VLANEndpoint_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_VLANEndpoint_quals[] =
{
    &CIM_VLANEndpoint_UMLPackagePath_qual,
    &CIM_VLANEndpoint_Version_qual,
};

/* class CIM_VLANEndpoint */
MI_CONST MI_ClassDecl CIM_VLANEndpoint_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00637410, /* code */
    MI_T("CIM_VLANEndpoint"), /* name */
    CIM_VLANEndpoint_quals, /* qualifiers */
    MI_COUNT(CIM_VLANEndpoint_quals), /* numQualifiers */
    CIM_VLANEndpoint_props, /* properties */
    MI_COUNT(CIM_VLANEndpoint_props), /* numProperties */
    sizeof(CIM_VLANEndpoint), /* size */
    MI_T("CIM_ProtocolEndpoint"), /* superClass */
    &CIM_ProtocolEndpoint_rtti, /* superClassDecl */
    CIM_VLANEndpoint_meths, /* methods */
    MI_COUNT(CIM_VLANEndpoint_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
};

/*
**==============================================================================
**
** ABC_VLANEndpoint
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_VLANEndpoint_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ProtocolEndpoint_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ProtocolEndpoint_Name_prop,
    &CIM_ProtocolEndpoint_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_ProtocolEndpoint_EnabledState_prop,
    &CIM_EnabledLogicalElement_OtherEnabledState_prop,
    &CIM_EnabledLogicalElement_RequestedState_prop,
    &CIM_EnabledLogicalElement_EnabledDefault_prop,
    &CIM_ProtocolEndpoint_TimeOfLastStateChange_prop,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_prop,
    &CIM_EnabledLogicalElement_TransitioningToState_prop,
    &CIM_ServiceAccessPoint_SystemCreationClassName_prop,
    &CIM_ServiceAccessPoint_SystemName_prop,
    &CIM_ServiceAccessPoint_CreationClassName_prop,
    &CIM_ProtocolEndpoint_NameFormat_prop,
    &CIM_ProtocolEndpoint_ProtocolType_prop,
    &CIM_ProtocolEndpoint_ProtocolIFType_prop,
    &CIM_ProtocolEndpoint_OtherTypeDescription_prop,
    &CIM_VLANEndpoint_DesiredEndpointMode_prop,
    &CIM_VLANEndpoint_OtherEndpointMode_prop,
    &CIM_VLANEndpoint_OperationalEndpointMode_prop,
    &CIM_VLANEndpoint_DesiredVLANTrunkEncapsulation_prop,
    &CIM_VLANEndpoint_OtherTrunkEncapsulation_prop,
    &CIM_VLANEndpoint_OperationalVLANTrunkEncapsulation_prop,
    &CIM_VLANEndpoint_GVRPStatus_prop,
};

static MI_CONST MI_Char* ABC_VLANEndpoint_RequestStateChange_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_VLANEndpoint_RequestStateChange_ModelCorrespondence_qual_value =
{
    ABC_VLANEndpoint_RequestStateChange_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_VLANEndpoint_RequestStateChange_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_VLANEndpoint_RequestStateChange_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_VLANEndpoint_RequestStateChange_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_VLANEndpoint_RequestStateChange_quals[] =
{
    &ABC_VLANEndpoint_RequestStateChange_ModelCorrespondence_qual,
};

static MI_CONST MI_Char* ABC_VLANEndpoint_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_VLANEndpoint_RequestStateChange_RequestedState_ModelCorrespondence_qual_value =
{
    ABC_VLANEndpoint_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_VLANEndpoint_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_VLANEndpoint_RequestStateChange_RequestedState_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_VLANEndpoint_RequestStateChange_RequestedState_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_VLANEndpoint_RequestStateChange_RequestedState_quals[] =
{
    &ABC_VLANEndpoint_RequestStateChange_RequestedState_ModelCorrespondence_qual,
};

/* parameter ABC_VLANEndpoint.RequestStateChange(): RequestedState */
static MI_CONST MI_ParameterDecl ABC_VLANEndpoint_RequestStateChange_RequestedState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0072650E, /* code */
    MI_T("RequestedState"), /* name */
    ABC_VLANEndpoint_RequestStateChange_RequestedState_quals, /* qualifiers */
    MI_COUNT(ABC_VLANEndpoint_RequestStateChange_RequestedState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_VLANEndpoint_RequestStateChange, RequestedState), /* offset */
};

/* parameter ABC_VLANEndpoint.RequestStateChange(): Job */
static MI_CONST MI_ParameterDecl ABC_VLANEndpoint_RequestStateChange_Job_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006A6203, /* code */
    MI_T("Job"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ConcreteJob"), /* className */
    0, /* subscript */
    offsetof(ABC_VLANEndpoint_RequestStateChange, Job), /* offset */
};

/* parameter ABC_VLANEndpoint.RequestStateChange(): TimeoutPeriod */
static MI_CONST MI_ParameterDecl ABC_VLANEndpoint_RequestStateChange_TimeoutPeriod_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0074640D, /* code */
    MI_T("TimeoutPeriod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_VLANEndpoint_RequestStateChange, TimeoutPeriod), /* offset */
};

static MI_CONST MI_Char* ABC_VLANEndpoint_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_VLANEndpoint_RequestStateChange_MIReturn_ModelCorrespondence_qual_value =
{
    ABC_VLANEndpoint_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_VLANEndpoint_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_VLANEndpoint_RequestStateChange_MIReturn_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_VLANEndpoint_RequestStateChange_MIReturn_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_VLANEndpoint_RequestStateChange_MIReturn_quals[] =
{
    &ABC_VLANEndpoint_RequestStateChange_MIReturn_ModelCorrespondence_qual,
};

/* parameter ABC_VLANEndpoint.RequestStateChange(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_VLANEndpoint_RequestStateChange_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_VLANEndpoint_RequestStateChange_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_VLANEndpoint_RequestStateChange_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_VLANEndpoint_RequestStateChange, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_VLANEndpoint_RequestStateChange_params[] =
{
    &ABC_VLANEndpoint_RequestStateChange_MIReturn_param,
    &ABC_VLANEndpoint_RequestStateChange_RequestedState_param,
    &ABC_VLANEndpoint_RequestStateChange_Job_param,
    &ABC_VLANEndpoint_RequestStateChange_TimeoutPeriod_param,
};

/* method ABC_VLANEndpoint.RequestStateChange() */
MI_CONST MI_MethodDecl ABC_VLANEndpoint_RequestStateChange_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00726512, /* code */
    MI_T("RequestStateChange"), /* name */
    ABC_VLANEndpoint_RequestStateChange_quals, /* qualifiers */
    MI_COUNT(ABC_VLANEndpoint_RequestStateChange_quals), /* numQualifiers */
    ABC_VLANEndpoint_RequestStateChange_params, /* parameters */
    MI_COUNT(ABC_VLANEndpoint_RequestStateChange_params), /* numParameters */
    sizeof(ABC_VLANEndpoint_RequestStateChange), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_VLANEndpoint_Invoke_RequestStateChange, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST ABC_VLANEndpoint_meths[] =
{
    &ABC_VLANEndpoint_RequestStateChange_rtti,
};

static MI_CONST MI_ProviderFT ABC_VLANEndpoint_funcs =
{
  (MI_ProviderFT_Load)ABC_VLANEndpoint_Load,
  (MI_ProviderFT_Unload)ABC_VLANEndpoint_Unload,
  (MI_ProviderFT_GetInstance)ABC_VLANEndpoint_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_VLANEndpoint_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_VLANEndpoint_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_VLANEndpoint_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_VLANEndpoint_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_VLANEndpoint_UMLPackagePath_qual_value = MI_T("CIM::Network::VLAN");

static MI_CONST MI_Qualifier ABC_VLANEndpoint_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_VLANEndpoint_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_VLANEndpoint_quals[] =
{
    &ABC_VLANEndpoint_UMLPackagePath_qual,
};

/* class ABC_VLANEndpoint */
MI_CONST MI_ClassDecl ABC_VLANEndpoint_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00617410, /* code */
    MI_T("ABC_VLANEndpoint"), /* name */
    ABC_VLANEndpoint_quals, /* qualifiers */
    MI_COUNT(ABC_VLANEndpoint_quals), /* numQualifiers */
    ABC_VLANEndpoint_props, /* properties */
    MI_COUNT(ABC_VLANEndpoint_props), /* numProperties */
    sizeof(ABC_VLANEndpoint), /* size */
    MI_T("CIM_VLANEndpoint"), /* superClass */
    &CIM_VLANEndpoint_rtti, /* superClassDecl */
    ABC_VLANEndpoint_meths, /* methods */
    MI_COUNT(ABC_VLANEndpoint_meths), /* numMethods */
    &schemaDecl, /* schema */
    &ABC_VLANEndpoint_funcs, /* functions */
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
    &ABC_EthernetPort_rtti,
    &ABC_VLANEndpoint_rtti,
    &CIM_ConcreteJob_rtti,
    &CIM_EnabledLogicalElement_rtti,
    &CIM_Error_rtti,
    &CIM_EthernetPort_rtti,
    &CIM_Job_rtti,
    &CIM_LogicalDevice_rtti,
    &CIM_LogicalElement_rtti,
    &CIM_LogicalPort_rtti,
    &CIM_ManagedElement_rtti,
    &CIM_ManagedSystemElement_rtti,
    &CIM_NetworkPort_rtti,
    &CIM_ProtocolEndpoint_rtti,
    &CIM_ServiceAccessPoint_rtti,
    &CIM_VLANEndpoint_rtti,
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

