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
#include "ABC_Fan.h"
#include "ABC_SystemDevice.h"
#include "ABC_ComputerSystem.h"
#include "ABC_AssociatedCooling.h"
#include "ABC_ManagedSystemElement.h"
#include "ABC_ElementCapabilities.h"
#include "ABC_EnabledLogicalElementCapabilities.h"
#include "ABC_ElementConformsToProfile.h"
#include "ABC_RegisteredProfile.h"
#include "ABC_Realizes.h"
#include "ABC_PhysicalPackage.h"
#include "ABC_AssociatedSensor.h"
#include "ABC_Sensor.h"
#include "ABC_IsSpare.h"
#include "ABC_MemberOfCollection.h"
#include "ABC_OwningCollectionElement.h"
#include "ABC_HostedCollection.h"
#include "ABC_RedundancySet.h"
#include "ABC_NumericSensor.h"

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
** _Match()
**
**==============================================================================
*/

static int _Match(const MI_Char* p, const MI_Char* q)
{
    if (!p || !q || !p[0] || !q[0])
        return 1;

    while (*p && *q)
        if (toupper((MI_Uint16)*p++) - toupper((MI_Uint16)*q++))
            return 0;

    return *p == '\0' && *q == '\0';
}

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
    NULL, /* owningClass */
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
    NULL, /* owningClass */
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
    NULL, /* owningClass */
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
    NULL, /* owningClass */
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
    NULL, /* owningClass */
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
    NULL, /* owningClass */
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
    NULL, /* owningClass */
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
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_CoolingDevice
**
**==============================================================================
*/

/* property CIM_CoolingDevice.ActiveCooling */
static MI_CONST MI_PropertyDecl CIM_CoolingDevice_ActiveCooling_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0061670D, /* code */
    MI_T("ActiveCooling"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_CoolingDevice, ActiveCooling), /* offset */
    MI_T("CIM_CoolingDevice"), /* origin */
    MI_T("CIM_CoolingDevice"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_CoolingDevice_props[] =
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
    &CIM_CoolingDevice_ActiveCooling_prop,
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_CoolingDevice_meths[] =
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

static MI_CONST MI_Char* CIM_CoolingDevice_UMLPackagePath_qual_value = MI_T("CIM::Device::CoolingAndPower");

static MI_CONST MI_Qualifier CIM_CoolingDevice_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_CoolingDevice_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_CoolingDevice_Version_qual_value = MI_T("2.10.0");

static MI_CONST MI_Qualifier CIM_CoolingDevice_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_CoolingDevice_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_CoolingDevice_quals[] =
{
    &CIM_CoolingDevice_UMLPackagePath_qual,
    &CIM_CoolingDevice_Version_qual,
};

/* class CIM_CoolingDevice */
MI_CONST MI_ClassDecl CIM_CoolingDevice_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00636511, /* code */
    MI_T("CIM_CoolingDevice"), /* name */
    CIM_CoolingDevice_quals, /* qualifiers */
    MI_COUNT(CIM_CoolingDevice_quals), /* numQualifiers */
    CIM_CoolingDevice_props, /* properties */
    MI_COUNT(CIM_CoolingDevice_props), /* numProperties */
    sizeof(CIM_CoolingDevice), /* size */
    MI_T("CIM_LogicalDevice"), /* superClass */
    &CIM_LogicalDevice_rtti, /* superClassDecl */
    CIM_CoolingDevice_meths, /* methods */
    MI_COUNT(CIM_CoolingDevice_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_Fan
**
**==============================================================================
*/

/* property CIM_Fan.VariableSpeed */
static MI_CONST MI_PropertyDecl CIM_Fan_VariableSpeed_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0076640D, /* code */
    MI_T("VariableSpeed"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Fan, VariableSpeed), /* offset */
    MI_T("CIM_Fan"), /* origin */
    MI_T("CIM_Fan"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Fan_DesiredSpeed_Units_qual_value = MI_T("Revolutions per Minute");

static MI_CONST MI_Qualifier CIM_Fan_DesiredSpeed_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Fan_DesiredSpeed_Units_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Fan_DesiredSpeed_quals[] =
{
    &CIM_Fan_DesiredSpeed_Units_qual,
};

/* property CIM_Fan.DesiredSpeed */
static MI_CONST MI_PropertyDecl CIM_Fan_DesiredSpeed_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064640C, /* code */
    MI_T("DesiredSpeed"), /* name */
    CIM_Fan_DesiredSpeed_quals, /* qualifiers */
    MI_COUNT(CIM_Fan_DesiredSpeed_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Fan, DesiredSpeed), /* offset */
    MI_T("CIM_Fan"), /* origin */
    MI_T("CIM_Fan"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Fan_props[] =
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
    &CIM_CoolingDevice_ActiveCooling_prop,
    &CIM_Fan_VariableSpeed_prop,
    &CIM_Fan_DesiredSpeed_prop,
};

/* parameter CIM_Fan.SetSpeed(): DesiredSpeed */
static MI_CONST MI_ParameterDecl CIM_Fan_SetSpeed_DesiredSpeed_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0064640C, /* code */
    MI_T("DesiredSpeed"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Fan_SetSpeed, DesiredSpeed), /* offset */
};

/* parameter CIM_Fan.SetSpeed(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_Fan_SetSpeed_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Fan_SetSpeed, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_Fan_SetSpeed_params[] =
{
    &CIM_Fan_SetSpeed_MIReturn_param,
    &CIM_Fan_SetSpeed_DesiredSpeed_param,
};

/* method CIM_Fan.SetSpeed() */
MI_CONST MI_MethodDecl CIM_Fan_SetSpeed_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00736408, /* code */
    MI_T("SetSpeed"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    CIM_Fan_SetSpeed_params, /* parameters */
    MI_COUNT(CIM_Fan_SetSpeed_params), /* numParameters */
    sizeof(CIM_Fan_SetSpeed), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_Fan"), /* origin */
    MI_T("CIM_Fan"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_Fan_meths[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_rtti,
    &CIM_LogicalDevice_SetPowerState_rtti,
    &CIM_LogicalDevice_Reset_rtti,
    &CIM_LogicalDevice_EnableDevice_rtti,
    &CIM_LogicalDevice_OnlineDevice_rtti,
    &CIM_LogicalDevice_QuiesceDevice_rtti,
    &CIM_LogicalDevice_SaveProperties_rtti,
    &CIM_LogicalDevice_RestoreProperties_rtti,
    &CIM_Fan_SetSpeed_rtti,
};

static MI_CONST MI_Char* CIM_Fan_UMLPackagePath_qual_value = MI_T("CIM::Device::CoolingAndPower");

static MI_CONST MI_Qualifier CIM_Fan_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Fan_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_Fan_Version_qual_value = MI_T("2.6.0");

static MI_CONST MI_Qualifier CIM_Fan_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Fan_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Fan_quals[] =
{
    &CIM_Fan_UMLPackagePath_qual,
    &CIM_Fan_Version_qual,
};

/* class CIM_Fan */
MI_CONST MI_ClassDecl CIM_Fan_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00636E07, /* code */
    MI_T("CIM_Fan"), /* name */
    CIM_Fan_quals, /* qualifiers */
    MI_COUNT(CIM_Fan_quals), /* numQualifiers */
    CIM_Fan_props, /* properties */
    MI_COUNT(CIM_Fan_props), /* numProperties */
    sizeof(CIM_Fan), /* size */
    MI_T("CIM_CoolingDevice"), /* superClass */
    &CIM_CoolingDevice_rtti, /* superClassDecl */
    CIM_Fan_meths, /* methods */
    MI_COUNT(CIM_Fan_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ABC_Fan
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_Fan_props[] =
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
    &CIM_CoolingDevice_ActiveCooling_prop,
    &CIM_Fan_VariableSpeed_prop,
    &CIM_Fan_DesiredSpeed_prop,
};

static MI_CONST MI_Char* ABC_Fan_RequestStateChange_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_Fan_RequestStateChange_ModelCorrespondence_qual_value =
{
    ABC_Fan_RequestStateChange_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_Fan_RequestStateChange_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Fan_RequestStateChange_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_Fan_RequestStateChange_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Fan_RequestStateChange_quals[] =
{
    &ABC_Fan_RequestStateChange_ModelCorrespondence_qual,
};

static MI_CONST MI_Char* ABC_Fan_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_Fan_RequestStateChange_RequestedState_ModelCorrespondence_qual_value =
{
    ABC_Fan_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_Fan_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Fan_RequestStateChange_RequestedState_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_Fan_RequestStateChange_RequestedState_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Fan_RequestStateChange_RequestedState_quals[] =
{
    &ABC_Fan_RequestStateChange_RequestedState_ModelCorrespondence_qual,
};

/* parameter ABC_Fan.RequestStateChange(): RequestedState */
static MI_CONST MI_ParameterDecl ABC_Fan_RequestStateChange_RequestedState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0072650E, /* code */
    MI_T("RequestedState"), /* name */
    ABC_Fan_RequestStateChange_RequestedState_quals, /* qualifiers */
    MI_COUNT(ABC_Fan_RequestStateChange_RequestedState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Fan_RequestStateChange, RequestedState), /* offset */
};

/* parameter ABC_Fan.RequestStateChange(): Job */
static MI_CONST MI_ParameterDecl ABC_Fan_RequestStateChange_Job_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006A6203, /* code */
    MI_T("Job"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ConcreteJob"), /* className */
    0, /* subscript */
    offsetof(ABC_Fan_RequestStateChange, Job), /* offset */
};

/* parameter ABC_Fan.RequestStateChange(): TimeoutPeriod */
static MI_CONST MI_ParameterDecl ABC_Fan_RequestStateChange_TimeoutPeriod_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0074640D, /* code */
    MI_T("TimeoutPeriod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Fan_RequestStateChange, TimeoutPeriod), /* offset */
};

static MI_CONST MI_Char* ABC_Fan_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_Fan_RequestStateChange_MIReturn_ModelCorrespondence_qual_value =
{
    ABC_Fan_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_Fan_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Fan_RequestStateChange_MIReturn_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_Fan_RequestStateChange_MIReturn_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Fan_RequestStateChange_MIReturn_quals[] =
{
    &ABC_Fan_RequestStateChange_MIReturn_ModelCorrespondence_qual,
};

/* parameter ABC_Fan.RequestStateChange(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_Fan_RequestStateChange_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_Fan_RequestStateChange_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_Fan_RequestStateChange_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Fan_RequestStateChange, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_Fan_RequestStateChange_params[] =
{
    &ABC_Fan_RequestStateChange_MIReturn_param,
    &ABC_Fan_RequestStateChange_RequestedState_param,
    &ABC_Fan_RequestStateChange_Job_param,
    &ABC_Fan_RequestStateChange_TimeoutPeriod_param,
};

/* method ABC_Fan.RequestStateChange() */
MI_CONST MI_MethodDecl ABC_Fan_RequestStateChange_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00726512, /* code */
    MI_T("RequestStateChange"), /* name */
    ABC_Fan_RequestStateChange_quals, /* qualifiers */
    MI_COUNT(ABC_Fan_RequestStateChange_quals), /* numQualifiers */
    ABC_Fan_RequestStateChange_params, /* parameters */
    MI_COUNT(ABC_Fan_RequestStateChange_params), /* numParameters */
    sizeof(ABC_Fan_RequestStateChange), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_Fan_Invoke_RequestStateChange, /* method */
};

static MI_CONST MI_Char* ABC_Fan_SetPowerState_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PowerManagementService.SetPowerState"),
};

static MI_CONST MI_ConstStringA ABC_Fan_SetPowerState_Deprecated_qual_value =
{
    ABC_Fan_SetPowerState_Deprecated_qual_data_value,
    MI_COUNT(ABC_Fan_SetPowerState_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Fan_SetPowerState_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_Fan_SetPowerState_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Fan_SetPowerState_quals[] =
{
    &ABC_Fan_SetPowerState_Deprecated_qual,
};

/* parameter ABC_Fan.SetPowerState(): PowerState */
static MI_CONST MI_ParameterDecl ABC_Fan_SetPowerState_PowerState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0070650A, /* code */
    MI_T("PowerState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Fan_SetPowerState, PowerState), /* offset */
};

/* parameter ABC_Fan.SetPowerState(): Time */
static MI_CONST MI_ParameterDecl ABC_Fan_SetPowerState_Time_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00746504, /* code */
    MI_T("Time"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Fan_SetPowerState, Time), /* offset */
};

static MI_CONST MI_Char* ABC_Fan_SetPowerState_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PowerManagementService.SetPowerState"),
};

static MI_CONST MI_ConstStringA ABC_Fan_SetPowerState_MIReturn_Deprecated_qual_value =
{
    ABC_Fan_SetPowerState_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_Fan_SetPowerState_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Fan_SetPowerState_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_Fan_SetPowerState_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Fan_SetPowerState_MIReturn_quals[] =
{
    &ABC_Fan_SetPowerState_MIReturn_Deprecated_qual,
};

/* parameter ABC_Fan.SetPowerState(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_Fan_SetPowerState_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_Fan_SetPowerState_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_Fan_SetPowerState_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Fan_SetPowerState, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_Fan_SetPowerState_params[] =
{
    &ABC_Fan_SetPowerState_MIReturn_param,
    &ABC_Fan_SetPowerState_PowerState_param,
    &ABC_Fan_SetPowerState_Time_param,
};

/* method ABC_Fan.SetPowerState() */
MI_CONST MI_MethodDecl ABC_Fan_SetPowerState_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650D, /* code */
    MI_T("SetPowerState"), /* name */
    ABC_Fan_SetPowerState_quals, /* qualifiers */
    MI_COUNT(ABC_Fan_SetPowerState_quals), /* numQualifiers */
    ABC_Fan_SetPowerState_params, /* parameters */
    MI_COUNT(ABC_Fan_SetPowerState_params), /* numParameters */
    sizeof(ABC_Fan_SetPowerState), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_Fan_Invoke_SetPowerState, /* method */
};

/* parameter ABC_Fan.Reset(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_Fan_Reset_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Fan_Reset, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_Fan_Reset_params[] =
{
    &ABC_Fan_Reset_MIReturn_param,
};

/* method ABC_Fan.Reset() */
MI_CONST MI_MethodDecl ABC_Fan_Reset_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00727405, /* code */
    MI_T("Reset"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_Fan_Reset_params, /* parameters */
    MI_COUNT(ABC_Fan_Reset_params), /* numParameters */
    sizeof(ABC_Fan_Reset), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_Fan_Invoke_Reset, /* method */
};

static MI_CONST MI_Char* ABC_Fan_EnableDevice_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_Fan_EnableDevice_Deprecated_qual_value =
{
    ABC_Fan_EnableDevice_Deprecated_qual_data_value,
    MI_COUNT(ABC_Fan_EnableDevice_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Fan_EnableDevice_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_Fan_EnableDevice_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Fan_EnableDevice_quals[] =
{
    &ABC_Fan_EnableDevice_Deprecated_qual,
};

/* parameter ABC_Fan.EnableDevice(): Enabled */
static MI_CONST MI_ParameterDecl ABC_Fan_EnableDevice_Enabled_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00656407, /* code */
    MI_T("Enabled"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Fan_EnableDevice, Enabled), /* offset */
};

static MI_CONST MI_Char* ABC_Fan_EnableDevice_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_Fan_EnableDevice_MIReturn_Deprecated_qual_value =
{
    ABC_Fan_EnableDevice_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_Fan_EnableDevice_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Fan_EnableDevice_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_Fan_EnableDevice_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Fan_EnableDevice_MIReturn_quals[] =
{
    &ABC_Fan_EnableDevice_MIReturn_Deprecated_qual,
};

/* parameter ABC_Fan.EnableDevice(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_Fan_EnableDevice_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_Fan_EnableDevice_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_Fan_EnableDevice_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Fan_EnableDevice, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_Fan_EnableDevice_params[] =
{
    &ABC_Fan_EnableDevice_MIReturn_param,
    &ABC_Fan_EnableDevice_Enabled_param,
};

/* method ABC_Fan.EnableDevice() */
MI_CONST MI_MethodDecl ABC_Fan_EnableDevice_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0065650C, /* code */
    MI_T("EnableDevice"), /* name */
    ABC_Fan_EnableDevice_quals, /* qualifiers */
    MI_COUNT(ABC_Fan_EnableDevice_quals), /* numQualifiers */
    ABC_Fan_EnableDevice_params, /* parameters */
    MI_COUNT(ABC_Fan_EnableDevice_params), /* numParameters */
    sizeof(ABC_Fan_EnableDevice), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_Fan_Invoke_EnableDevice, /* method */
};

static MI_CONST MI_Char* ABC_Fan_OnlineDevice_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_Fan_OnlineDevice_Deprecated_qual_value =
{
    ABC_Fan_OnlineDevice_Deprecated_qual_data_value,
    MI_COUNT(ABC_Fan_OnlineDevice_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Fan_OnlineDevice_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_Fan_OnlineDevice_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Fan_OnlineDevice_quals[] =
{
    &ABC_Fan_OnlineDevice_Deprecated_qual,
};

/* parameter ABC_Fan.OnlineDevice(): Online */
static MI_CONST MI_ParameterDecl ABC_Fan_OnlineDevice_Online_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006F6506, /* code */
    MI_T("Online"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Fan_OnlineDevice, Online), /* offset */
};

static MI_CONST MI_Char* ABC_Fan_OnlineDevice_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_Fan_OnlineDevice_MIReturn_Deprecated_qual_value =
{
    ABC_Fan_OnlineDevice_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_Fan_OnlineDevice_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Fan_OnlineDevice_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_Fan_OnlineDevice_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Fan_OnlineDevice_MIReturn_quals[] =
{
    &ABC_Fan_OnlineDevice_MIReturn_Deprecated_qual,
};

/* parameter ABC_Fan.OnlineDevice(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_Fan_OnlineDevice_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_Fan_OnlineDevice_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_Fan_OnlineDevice_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Fan_OnlineDevice, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_Fan_OnlineDevice_params[] =
{
    &ABC_Fan_OnlineDevice_MIReturn_param,
    &ABC_Fan_OnlineDevice_Online_param,
};

/* method ABC_Fan.OnlineDevice() */
MI_CONST MI_MethodDecl ABC_Fan_OnlineDevice_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006F650C, /* code */
    MI_T("OnlineDevice"), /* name */
    ABC_Fan_OnlineDevice_quals, /* qualifiers */
    MI_COUNT(ABC_Fan_OnlineDevice_quals), /* numQualifiers */
    ABC_Fan_OnlineDevice_params, /* parameters */
    MI_COUNT(ABC_Fan_OnlineDevice_params), /* numParameters */
    sizeof(ABC_Fan_OnlineDevice), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_Fan_Invoke_OnlineDevice, /* method */
};

static MI_CONST MI_Char* ABC_Fan_QuiesceDevice_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_Fan_QuiesceDevice_Deprecated_qual_value =
{
    ABC_Fan_QuiesceDevice_Deprecated_qual_data_value,
    MI_COUNT(ABC_Fan_QuiesceDevice_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Fan_QuiesceDevice_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_Fan_QuiesceDevice_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Fan_QuiesceDevice_quals[] =
{
    &ABC_Fan_QuiesceDevice_Deprecated_qual,
};

/* parameter ABC_Fan.QuiesceDevice(): Quiesce */
static MI_CONST MI_ParameterDecl ABC_Fan_QuiesceDevice_Quiesce_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00716507, /* code */
    MI_T("Quiesce"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Fan_QuiesceDevice, Quiesce), /* offset */
};

static MI_CONST MI_Char* ABC_Fan_QuiesceDevice_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_Fan_QuiesceDevice_MIReturn_Deprecated_qual_value =
{
    ABC_Fan_QuiesceDevice_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_Fan_QuiesceDevice_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Fan_QuiesceDevice_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_Fan_QuiesceDevice_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Fan_QuiesceDevice_MIReturn_quals[] =
{
    &ABC_Fan_QuiesceDevice_MIReturn_Deprecated_qual,
};

/* parameter ABC_Fan.QuiesceDevice(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_Fan_QuiesceDevice_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_Fan_QuiesceDevice_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_Fan_QuiesceDevice_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Fan_QuiesceDevice, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_Fan_QuiesceDevice_params[] =
{
    &ABC_Fan_QuiesceDevice_MIReturn_param,
    &ABC_Fan_QuiesceDevice_Quiesce_param,
};

/* method ABC_Fan.QuiesceDevice() */
MI_CONST MI_MethodDecl ABC_Fan_QuiesceDevice_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0071650D, /* code */
    MI_T("QuiesceDevice"), /* name */
    ABC_Fan_QuiesceDevice_quals, /* qualifiers */
    MI_COUNT(ABC_Fan_QuiesceDevice_quals), /* numQualifiers */
    ABC_Fan_QuiesceDevice_params, /* parameters */
    MI_COUNT(ABC_Fan_QuiesceDevice_params), /* numParameters */
    sizeof(ABC_Fan_QuiesceDevice), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_Fan_Invoke_QuiesceDevice, /* method */
};

/* parameter ABC_Fan.SaveProperties(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_Fan_SaveProperties_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Fan_SaveProperties, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_Fan_SaveProperties_params[] =
{
    &ABC_Fan_SaveProperties_MIReturn_param,
};

/* method ABC_Fan.SaveProperties() */
MI_CONST MI_MethodDecl ABC_Fan_SaveProperties_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073730E, /* code */
    MI_T("SaveProperties"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_Fan_SaveProperties_params, /* parameters */
    MI_COUNT(ABC_Fan_SaveProperties_params), /* numParameters */
    sizeof(ABC_Fan_SaveProperties), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_Fan_Invoke_SaveProperties, /* method */
};

/* parameter ABC_Fan.RestoreProperties(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_Fan_RestoreProperties_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Fan_RestoreProperties, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_Fan_RestoreProperties_params[] =
{
    &ABC_Fan_RestoreProperties_MIReturn_param,
};

/* method ABC_Fan.RestoreProperties() */
MI_CONST MI_MethodDecl ABC_Fan_RestoreProperties_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00727311, /* code */
    MI_T("RestoreProperties"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_Fan_RestoreProperties_params, /* parameters */
    MI_COUNT(ABC_Fan_RestoreProperties_params), /* numParameters */
    sizeof(ABC_Fan_RestoreProperties), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_Fan_Invoke_RestoreProperties, /* method */
};

/* parameter ABC_Fan.SetSpeed(): DesiredSpeed */
static MI_CONST MI_ParameterDecl ABC_Fan_SetSpeed_DesiredSpeed_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0064640C, /* code */
    MI_T("DesiredSpeed"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Fan_SetSpeed, DesiredSpeed), /* offset */
};

/* parameter ABC_Fan.SetSpeed(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_Fan_SetSpeed_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Fan_SetSpeed, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_Fan_SetSpeed_params[] =
{
    &ABC_Fan_SetSpeed_MIReturn_param,
    &ABC_Fan_SetSpeed_DesiredSpeed_param,
};

/* method ABC_Fan.SetSpeed() */
MI_CONST MI_MethodDecl ABC_Fan_SetSpeed_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00736408, /* code */
    MI_T("SetSpeed"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_Fan_SetSpeed_params, /* parameters */
    MI_COUNT(ABC_Fan_SetSpeed_params), /* numParameters */
    sizeof(ABC_Fan_SetSpeed), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_Fan"), /* origin */
    MI_T("CIM_Fan"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_Fan_Invoke_SetSpeed, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST ABC_Fan_meths[] =
{
    &ABC_Fan_RequestStateChange_rtti,
    &ABC_Fan_SetPowerState_rtti,
    &ABC_Fan_Reset_rtti,
    &ABC_Fan_EnableDevice_rtti,
    &ABC_Fan_OnlineDevice_rtti,
    &ABC_Fan_QuiesceDevice_rtti,
    &ABC_Fan_SaveProperties_rtti,
    &ABC_Fan_RestoreProperties_rtti,
    &ABC_Fan_SetSpeed_rtti,
};

static MI_CONST MI_ProviderFT ABC_Fan_funcs =
{
  (MI_ProviderFT_Load)ABC_Fan_Load,
  (MI_ProviderFT_Unload)ABC_Fan_Unload,
  (MI_ProviderFT_GetInstance)ABC_Fan_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_Fan_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_Fan_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_Fan_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_Fan_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_Fan_UMLPackagePath_qual_value = MI_T("CIM::Device::CoolingAndPower");

static MI_CONST MI_Qualifier ABC_Fan_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_Fan_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Fan_quals[] =
{
    &ABC_Fan_UMLPackagePath_qual,
};

/* class ABC_Fan */
MI_CONST MI_ClassDecl ABC_Fan_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00616E07, /* code */
    MI_T("ABC_Fan"), /* name */
    ABC_Fan_quals, /* qualifiers */
    MI_COUNT(ABC_Fan_quals), /* numQualifiers */
    ABC_Fan_props, /* properties */
    MI_COUNT(ABC_Fan_props), /* numProperties */
    sizeof(ABC_Fan), /* size */
    MI_T("CIM_Fan"), /* superClass */
    &CIM_Fan_rtti, /* superClassDecl */
    ABC_Fan_meths, /* methods */
    MI_COUNT(ABC_Fan_meths), /* numMethods */
    &schemaDecl, /* schema */
    &ABC_Fan_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_Component
**
**==============================================================================
*/

/* property CIM_Component.GroupComponent */
static MI_CONST MI_PropertyDecl CIM_Component_GroupComponent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0067740E, /* code */
    MI_T("GroupComponent"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(CIM_Component, GroupComponent), /* offset */
    MI_T("CIM_Component"), /* origin */
    MI_T("CIM_Component"), /* propagator */
    NULL,
};

/* property CIM_Component.PartComponent */
static MI_CONST MI_PropertyDecl CIM_Component_PartComponent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0070740D, /* code */
    MI_T("PartComponent"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(CIM_Component, PartComponent), /* offset */
    MI_T("CIM_Component"), /* origin */
    MI_T("CIM_Component"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Component_props[] =
{
    &CIM_Component_GroupComponent_prop,
    &CIM_Component_PartComponent_prop,
};

static MI_CONST MI_Char* CIM_Component_Version_qual_value = MI_T("2.7.0");

static MI_CONST MI_Qualifier CIM_Component_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Component_Version_qual_value
};

static MI_CONST MI_Char* CIM_Component_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_Component_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Component_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Component_quals[] =
{
    &CIM_Component_Version_qual,
    &CIM_Component_UMLPackagePath_qual,
};

/* class CIM_Component */
MI_CONST MI_ClassDecl CIM_Component_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION|MI_FLAG_ABSTRACT, /* flags */
    0x0063740D, /* code */
    MI_T("CIM_Component"), /* name */
    CIM_Component_quals, /* qualifiers */
    MI_COUNT(CIM_Component_quals), /* numQualifiers */
    CIM_Component_props, /* properties */
    MI_COUNT(CIM_Component_props), /* numProperties */
    sizeof(CIM_Component), /* size */
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
** CIM_System
**
**==============================================================================
*/

static MI_CONST MI_Uint32 CIM_System_Name_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_System_Name_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_System_Name_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_System_Name_Override_qual_value = MI_T("Name");

static MI_CONST MI_Qualifier CIM_System_Name_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_System_Name_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_System_Name_quals[] =
{
    &CIM_System_Name_MaxLen_qual,
    &CIM_System_Name_Override_qual,
};

/* property CIM_System.Name */
static MI_CONST MI_PropertyDecl CIM_System_Name_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    CIM_System_Name_quals, /* qualifiers */
    MI_COUNT(CIM_System_Name_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_System, Name), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_System"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_System_CreationClassName_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_System_CreationClassName_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_System_CreationClassName_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_System_CreationClassName_quals[] =
{
    &CIM_System_CreationClassName_MaxLen_qual,
};

/* property CIM_System.CreationClassName */
static MI_CONST MI_PropertyDecl CIM_System_CreationClassName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00636511, /* code */
    MI_T("CreationClassName"), /* name */
    CIM_System_CreationClassName_quals, /* qualifiers */
    MI_COUNT(CIM_System_CreationClassName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_System, CreationClassName), /* offset */
    MI_T("CIM_System"), /* origin */
    MI_T("CIM_System"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_System_NameFormat_MaxLen_qual_value = 64U;

static MI_CONST MI_Qualifier CIM_System_NameFormat_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_System_NameFormat_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_System_NameFormat_quals[] =
{
    &CIM_System_NameFormat_MaxLen_qual,
};

/* property CIM_System.NameFormat */
static MI_CONST MI_PropertyDecl CIM_System_NameFormat_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E740A, /* code */
    MI_T("NameFormat"), /* name */
    CIM_System_NameFormat_quals, /* qualifiers */
    MI_COUNT(CIM_System_NameFormat_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_System, NameFormat), /* offset */
    MI_T("CIM_System"), /* origin */
    MI_T("CIM_System"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_System_PrimaryOwnerName_MaxLen_qual_value = 64U;

static MI_CONST MI_Qualifier CIM_System_PrimaryOwnerName_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_System_PrimaryOwnerName_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_System_PrimaryOwnerName_quals[] =
{
    &CIM_System_PrimaryOwnerName_MaxLen_qual,
};

/* property CIM_System.PrimaryOwnerName */
static MI_CONST MI_PropertyDecl CIM_System_PrimaryOwnerName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706510, /* code */
    MI_T("PrimaryOwnerName"), /* name */
    CIM_System_PrimaryOwnerName_quals, /* qualifiers */
    MI_COUNT(CIM_System_PrimaryOwnerName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_System, PrimaryOwnerName), /* offset */
    MI_T("CIM_System"), /* origin */
    MI_T("CIM_System"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_System_PrimaryOwnerContact_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_System_PrimaryOwnerContact_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_System_PrimaryOwnerContact_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_System_PrimaryOwnerContact_quals[] =
{
    &CIM_System_PrimaryOwnerContact_MaxLen_qual,
};

/* property CIM_System.PrimaryOwnerContact */
static MI_CONST MI_PropertyDecl CIM_System_PrimaryOwnerContact_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00707413, /* code */
    MI_T("PrimaryOwnerContact"), /* name */
    CIM_System_PrimaryOwnerContact_quals, /* qualifiers */
    MI_COUNT(CIM_System_PrimaryOwnerContact_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_System, PrimaryOwnerContact), /* offset */
    MI_T("CIM_System"), /* origin */
    MI_T("CIM_System"), /* propagator */
    NULL,
};

/* property CIM_System.Roles */
static MI_CONST MI_PropertyDecl CIM_System_Roles_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00727305, /* code */
    MI_T("Roles"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_System, Roles), /* offset */
    MI_T("CIM_System"), /* origin */
    MI_T("CIM_System"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_System_OtherIdentifyingInfo_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_System_OtherIdentifyingInfo_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_System_OtherIdentifyingInfo_ArrayType_qual_value
};

static MI_CONST MI_Uint32 CIM_System_OtherIdentifyingInfo_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_System_OtherIdentifyingInfo_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_System_OtherIdentifyingInfo_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_System_OtherIdentifyingInfo_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_System.IdentifyingDescriptions"),
};

static MI_CONST MI_ConstStringA CIM_System_OtherIdentifyingInfo_ModelCorrespondence_qual_value =
{
    CIM_System_OtherIdentifyingInfo_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_System_OtherIdentifyingInfo_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_System_OtherIdentifyingInfo_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_System_OtherIdentifyingInfo_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_System_OtherIdentifyingInfo_quals[] =
{
    &CIM_System_OtherIdentifyingInfo_ArrayType_qual,
    &CIM_System_OtherIdentifyingInfo_MaxLen_qual,
    &CIM_System_OtherIdentifyingInfo_ModelCorrespondence_qual,
};

/* property CIM_System.OtherIdentifyingInfo */
static MI_CONST MI_PropertyDecl CIM_System_OtherIdentifyingInfo_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6F14, /* code */
    MI_T("OtherIdentifyingInfo"), /* name */
    CIM_System_OtherIdentifyingInfo_quals, /* qualifiers */
    MI_COUNT(CIM_System_OtherIdentifyingInfo_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_System, OtherIdentifyingInfo), /* offset */
    MI_T("CIM_System"), /* origin */
    MI_T("CIM_System"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_System_IdentifyingDescriptions_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_System_IdentifyingDescriptions_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_System_IdentifyingDescriptions_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_System_IdentifyingDescriptions_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_System.OtherIdentifyingInfo"),
};

static MI_CONST MI_ConstStringA CIM_System_IdentifyingDescriptions_ModelCorrespondence_qual_value =
{
    CIM_System_IdentifyingDescriptions_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_System_IdentifyingDescriptions_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_System_IdentifyingDescriptions_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_System_IdentifyingDescriptions_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_System_IdentifyingDescriptions_quals[] =
{
    &CIM_System_IdentifyingDescriptions_ArrayType_qual,
    &CIM_System_IdentifyingDescriptions_ModelCorrespondence_qual,
};

/* property CIM_System.IdentifyingDescriptions */
static MI_CONST MI_PropertyDecl CIM_System_IdentifyingDescriptions_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00697317, /* code */
    MI_T("IdentifyingDescriptions"), /* name */
    CIM_System_IdentifyingDescriptions_quals, /* qualifiers */
    MI_COUNT(CIM_System_IdentifyingDescriptions_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_System, IdentifyingDescriptions), /* offset */
    MI_T("CIM_System"), /* origin */
    MI_T("CIM_System"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_System_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_System_Name_prop,
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
    &CIM_System_CreationClassName_prop,
    &CIM_System_NameFormat_prop,
    &CIM_System_PrimaryOwnerName_prop,
    &CIM_System_PrimaryOwnerContact_prop,
    &CIM_System_Roles_prop,
    &CIM_System_OtherIdentifyingInfo_prop,
    &CIM_System_IdentifyingDescriptions_prop,
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_System_meths[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_rtti,
};

static MI_CONST MI_Char* CIM_System_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_System_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_System_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_System_Version_qual_value = MI_T("2.15.0");

static MI_CONST MI_Qualifier CIM_System_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_System_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_System_quals[] =
{
    &CIM_System_UMLPackagePath_qual,
    &CIM_System_Version_qual,
};

/* class CIM_System */
MI_CONST MI_ClassDecl CIM_System_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00636D0A, /* code */
    MI_T("CIM_System"), /* name */
    CIM_System_quals, /* qualifiers */
    MI_COUNT(CIM_System_quals), /* numQualifiers */
    CIM_System_props, /* properties */
    MI_COUNT(CIM_System_props), /* numProperties */
    sizeof(CIM_System), /* size */
    MI_T("CIM_EnabledLogicalElement"), /* superClass */
    &CIM_EnabledLogicalElement_rtti, /* superClassDecl */
    CIM_System_meths, /* methods */
    MI_COUNT(CIM_System_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_SystemComponent
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_SystemComponent_GroupComponent_Override_qual_value = MI_T("GroupComponent");

static MI_CONST MI_Qualifier CIM_SystemComponent_GroupComponent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_SystemComponent_GroupComponent_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_SystemComponent_GroupComponent_quals[] =
{
    &CIM_SystemComponent_GroupComponent_Override_qual,
};

/* property CIM_SystemComponent.GroupComponent */
static MI_CONST MI_PropertyDecl CIM_SystemComponent_GroupComponent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0067740E, /* code */
    MI_T("GroupComponent"), /* name */
    CIM_SystemComponent_GroupComponent_quals, /* qualifiers */
    MI_COUNT(CIM_SystemComponent_GroupComponent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_System"), /* className */
    0, /* subscript */
    offsetof(CIM_SystemComponent, GroupComponent), /* offset */
    MI_T("CIM_Component"), /* origin */
    MI_T("CIM_SystemComponent"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_SystemComponent_PartComponent_Override_qual_value = MI_T("PartComponent");

static MI_CONST MI_Qualifier CIM_SystemComponent_PartComponent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_SystemComponent_PartComponent_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_SystemComponent_PartComponent_quals[] =
{
    &CIM_SystemComponent_PartComponent_Override_qual,
};

/* property CIM_SystemComponent.PartComponent */
static MI_CONST MI_PropertyDecl CIM_SystemComponent_PartComponent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0070740D, /* code */
    MI_T("PartComponent"), /* name */
    CIM_SystemComponent_PartComponent_quals, /* qualifiers */
    MI_COUNT(CIM_SystemComponent_PartComponent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedSystemElement"), /* className */
    0, /* subscript */
    offsetof(CIM_SystemComponent, PartComponent), /* offset */
    MI_T("CIM_Component"), /* origin */
    MI_T("CIM_SystemComponent"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_SystemComponent_props[] =
{
    &CIM_SystemComponent_GroupComponent_prop,
    &CIM_SystemComponent_PartComponent_prop,
};

static MI_CONST MI_Char* CIM_SystemComponent_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_SystemComponent_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_SystemComponent_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_SystemComponent_Version_qual_value = MI_T("2.10.0");

static MI_CONST MI_Qualifier CIM_SystemComponent_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_SystemComponent_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_SystemComponent_quals[] =
{
    &CIM_SystemComponent_UMLPackagePath_qual,
    &CIM_SystemComponent_Version_qual,
};

/* class CIM_SystemComponent */
MI_CONST MI_ClassDecl CIM_SystemComponent_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00637413, /* code */
    MI_T("CIM_SystemComponent"), /* name */
    CIM_SystemComponent_quals, /* qualifiers */
    MI_COUNT(CIM_SystemComponent_quals), /* numQualifiers */
    CIM_SystemComponent_props, /* properties */
    MI_COUNT(CIM_SystemComponent_props), /* numProperties */
    sizeof(CIM_SystemComponent), /* size */
    MI_T("CIM_Component"), /* superClass */
    &CIM_Component_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_SystemDevice
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_SystemDevice_GroupComponent_Override_qual_value = MI_T("GroupComponent");

static MI_CONST MI_Qualifier CIM_SystemDevice_GroupComponent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_SystemDevice_GroupComponent_Override_qual_value
};

static MI_CONST MI_Uint32 CIM_SystemDevice_GroupComponent_Min_qual_value = 1U;

static MI_CONST MI_Qualifier CIM_SystemDevice_GroupComponent_Min_qual =
{
    MI_T("Min"),
    MI_UINT32,
    0,
    &CIM_SystemDevice_GroupComponent_Min_qual_value
};

static MI_CONST MI_Uint32 CIM_SystemDevice_GroupComponent_Max_qual_value = 1U;

static MI_CONST MI_Qualifier CIM_SystemDevice_GroupComponent_Max_qual =
{
    MI_T("Max"),
    MI_UINT32,
    0,
    &CIM_SystemDevice_GroupComponent_Max_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_SystemDevice_GroupComponent_quals[] =
{
    &CIM_SystemDevice_GroupComponent_Override_qual,
    &CIM_SystemDevice_GroupComponent_Min_qual,
    &CIM_SystemDevice_GroupComponent_Max_qual,
};

/* property CIM_SystemDevice.GroupComponent */
static MI_CONST MI_PropertyDecl CIM_SystemDevice_GroupComponent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0067740E, /* code */
    MI_T("GroupComponent"), /* name */
    CIM_SystemDevice_GroupComponent_quals, /* qualifiers */
    MI_COUNT(CIM_SystemDevice_GroupComponent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_System"), /* className */
    0, /* subscript */
    offsetof(CIM_SystemDevice, GroupComponent), /* offset */
    MI_T("CIM_Component"), /* origin */
    MI_T("CIM_SystemDevice"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_SystemDevice_PartComponent_Override_qual_value = MI_T("PartComponent");

static MI_CONST MI_Qualifier CIM_SystemDevice_PartComponent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_SystemDevice_PartComponent_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_SystemDevice_PartComponent_quals[] =
{
    &CIM_SystemDevice_PartComponent_Override_qual,
};

/* property CIM_SystemDevice.PartComponent */
static MI_CONST MI_PropertyDecl CIM_SystemDevice_PartComponent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0070740D, /* code */
    MI_T("PartComponent"), /* name */
    CIM_SystemDevice_PartComponent_quals, /* qualifiers */
    MI_COUNT(CIM_SystemDevice_PartComponent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_LogicalDevice"), /* className */
    0, /* subscript */
    offsetof(CIM_SystemDevice, PartComponent), /* offset */
    MI_T("CIM_Component"), /* origin */
    MI_T("CIM_SystemDevice"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_SystemDevice_props[] =
{
    &CIM_SystemDevice_GroupComponent_prop,
    &CIM_SystemDevice_PartComponent_prop,
};

static MI_CONST MI_Char* CIM_SystemDevice_UMLPackagePath_qual_value = MI_T("CIM::Core::Device");

static MI_CONST MI_Qualifier CIM_SystemDevice_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_SystemDevice_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_SystemDevice_Version_qual_value = MI_T("2.10.0");

static MI_CONST MI_Qualifier CIM_SystemDevice_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_SystemDevice_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_SystemDevice_quals[] =
{
    &CIM_SystemDevice_UMLPackagePath_qual,
    &CIM_SystemDevice_Version_qual,
};

/* class CIM_SystemDevice */
MI_CONST MI_ClassDecl CIM_SystemDevice_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00636510, /* code */
    MI_T("CIM_SystemDevice"), /* name */
    CIM_SystemDevice_quals, /* qualifiers */
    MI_COUNT(CIM_SystemDevice_quals), /* numQualifiers */
    CIM_SystemDevice_props, /* properties */
    MI_COUNT(CIM_SystemDevice_props), /* numProperties */
    sizeof(CIM_SystemDevice), /* size */
    MI_T("CIM_SystemComponent"), /* superClass */
    &CIM_SystemComponent_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ABC_SystemDevice
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_SystemDevice_props[] =
{
    &CIM_SystemDevice_GroupComponent_prop,
    &CIM_SystemDevice_PartComponent_prop,
};

static void MI_CALL ABC_SystemDevice_AssociatorInstances(
    ABC_SystemDevice_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (CIM_System_IsA(instanceName))
    {
        if (_Match(role, MI_T("GroupComponent")) && 
            _Match(resultRole, MI_T("PartComponent")))
        {
            ABC_SystemDevice_AssociatorInstancesGroupComponent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_System*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (CIM_LogicalDevice_IsA(instanceName))
    {
        if (_Match(role, MI_T("PartComponent")) && 
            _Match(resultRole, MI_T("GroupComponent")))
        {
            ABC_SystemDevice_AssociatorInstancesPartComponent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_LogicalDevice*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL ABC_SystemDevice_ReferenceInstances(
    ABC_SystemDevice_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (CIM_System_IsA(instanceName))
    {
        if (_Match(role, MI_T("GroupComponent")))
        {
            ABC_SystemDevice_ReferenceInstancesGroupComponent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_System*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (CIM_LogicalDevice_IsA(instanceName))
    {
        if (_Match(role, MI_T("PartComponent")))
        {
            ABC_SystemDevice_ReferenceInstancesPartComponent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_LogicalDevice*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT ABC_SystemDevice_funcs =
{
  (MI_ProviderFT_Load)ABC_SystemDevice_Load,
  (MI_ProviderFT_Unload)ABC_SystemDevice_Unload,
  (MI_ProviderFT_GetInstance)ABC_SystemDevice_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_SystemDevice_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_SystemDevice_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_SystemDevice_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_SystemDevice_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)ABC_SystemDevice_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)ABC_SystemDevice_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_SystemDevice_UMLPackagePath_qual_value = MI_T("CIM::Core::Device");

static MI_CONST MI_Qualifier ABC_SystemDevice_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_SystemDevice_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_SystemDevice_quals[] =
{
    &ABC_SystemDevice_UMLPackagePath_qual,
};

/* class ABC_SystemDevice */
MI_CONST MI_ClassDecl ABC_SystemDevice_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00616510, /* code */
    MI_T("ABC_SystemDevice"), /* name */
    ABC_SystemDevice_quals, /* qualifiers */
    MI_COUNT(ABC_SystemDevice_quals), /* numQualifiers */
    ABC_SystemDevice_props, /* properties */
    MI_COUNT(ABC_SystemDevice_props), /* numProperties */
    sizeof(ABC_SystemDevice), /* size */
    MI_T("CIM_SystemDevice"), /* superClass */
    &CIM_SystemDevice_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &ABC_SystemDevice_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_ComputerSystem
**
**==============================================================================
*/

static MI_CONST MI_Uint32 CIM_ComputerSystem_NameFormat_MaxLen_qual_value = 64U;

static MI_CONST MI_Qualifier CIM_ComputerSystem_NameFormat_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ComputerSystem_NameFormat_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_ComputerSystem_NameFormat_Override_qual_value = MI_T("NameFormat");

static MI_CONST MI_Qualifier CIM_ComputerSystem_NameFormat_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ComputerSystem_NameFormat_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ComputerSystem_NameFormat_quals[] =
{
    &CIM_ComputerSystem_NameFormat_MaxLen_qual,
    &CIM_ComputerSystem_NameFormat_Override_qual,
};

/* property CIM_ComputerSystem.NameFormat */
static MI_CONST MI_PropertyDecl CIM_ComputerSystem_NameFormat_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E740A, /* code */
    MI_T("NameFormat"), /* name */
    CIM_ComputerSystem_NameFormat_quals, /* qualifiers */
    MI_COUNT(CIM_ComputerSystem_NameFormat_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ComputerSystem, NameFormat), /* offset */
    MI_T("CIM_System"), /* origin */
    MI_T("CIM_ComputerSystem"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ComputerSystem_Dedicated_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_ComputerSystem_Dedicated_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_ComputerSystem_Dedicated_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_ComputerSystem_Dedicated_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ComputerSystem.OtherDedicatedDescriptions"),
};

static MI_CONST MI_ConstStringA CIM_ComputerSystem_Dedicated_ModelCorrespondence_qual_value =
{
    CIM_ComputerSystem_Dedicated_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_ComputerSystem_Dedicated_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ComputerSystem_Dedicated_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_ComputerSystem_Dedicated_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ComputerSystem_Dedicated_quals[] =
{
    &CIM_ComputerSystem_Dedicated_ArrayType_qual,
    &CIM_ComputerSystem_Dedicated_ModelCorrespondence_qual,
};

/* property CIM_ComputerSystem.Dedicated */
static MI_CONST MI_PropertyDecl CIM_ComputerSystem_Dedicated_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646409, /* code */
    MI_T("Dedicated"), /* name */
    CIM_ComputerSystem_Dedicated_quals, /* qualifiers */
    MI_COUNT(CIM_ComputerSystem_Dedicated_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ComputerSystem, Dedicated), /* offset */
    MI_T("CIM_ComputerSystem"), /* origin */
    MI_T("CIM_ComputerSystem"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ComputerSystem_OtherDedicatedDescriptions_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_ComputerSystem_OtherDedicatedDescriptions_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_ComputerSystem_OtherDedicatedDescriptions_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_ComputerSystem_OtherDedicatedDescriptions_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ComputerSystem.Dedicated"),
};

static MI_CONST MI_ConstStringA CIM_ComputerSystem_OtherDedicatedDescriptions_ModelCorrespondence_qual_value =
{
    CIM_ComputerSystem_OtherDedicatedDescriptions_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_ComputerSystem_OtherDedicatedDescriptions_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ComputerSystem_OtherDedicatedDescriptions_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_ComputerSystem_OtherDedicatedDescriptions_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ComputerSystem_OtherDedicatedDescriptions_quals[] =
{
    &CIM_ComputerSystem_OtherDedicatedDescriptions_ArrayType_qual,
    &CIM_ComputerSystem_OtherDedicatedDescriptions_ModelCorrespondence_qual,
};

/* property CIM_ComputerSystem.OtherDedicatedDescriptions */
static MI_CONST MI_PropertyDecl CIM_ComputerSystem_OtherDedicatedDescriptions_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F731A, /* code */
    MI_T("OtherDedicatedDescriptions"), /* name */
    CIM_ComputerSystem_OtherDedicatedDescriptions_quals, /* qualifiers */
    MI_COUNT(CIM_ComputerSystem_OtherDedicatedDescriptions_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ComputerSystem, OtherDedicatedDescriptions), /* offset */
    MI_T("CIM_ComputerSystem"), /* origin */
    MI_T("CIM_ComputerSystem"), /* propagator */
    NULL,
};

/* property CIM_ComputerSystem.ResetCapability */
static MI_CONST MI_PropertyDecl CIM_ComputerSystem_ResetCapability_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072790F, /* code */
    MI_T("ResetCapability"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ComputerSystem, ResetCapability), /* offset */
    MI_T("CIM_ComputerSystem"), /* origin */
    MI_T("CIM_ComputerSystem"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ComputerSystem_PowerManagementCapabilities_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PowerManagementCapabilities.PowerCapabilities"),
};

static MI_CONST MI_ConstStringA CIM_ComputerSystem_PowerManagementCapabilities_Deprecated_qual_value =
{
    CIM_ComputerSystem_PowerManagementCapabilities_Deprecated_qual_data_value,
    MI_COUNT(CIM_ComputerSystem_PowerManagementCapabilities_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ComputerSystem_PowerManagementCapabilities_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ComputerSystem_PowerManagementCapabilities_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ComputerSystem_PowerManagementCapabilities_quals[] =
{
    &CIM_ComputerSystem_PowerManagementCapabilities_Deprecated_qual,
};

/* property CIM_ComputerSystem.PowerManagementCapabilities */
static MI_CONST MI_PropertyDecl CIM_ComputerSystem_PowerManagementCapabilities_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070731B, /* code */
    MI_T("PowerManagementCapabilities"), /* name */
    CIM_ComputerSystem_PowerManagementCapabilities_quals, /* qualifiers */
    MI_COUNT(CIM_ComputerSystem_PowerManagementCapabilities_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ComputerSystem, PowerManagementCapabilities), /* offset */
    MI_T("CIM_ComputerSystem"), /* origin */
    MI_T("CIM_ComputerSystem"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_ComputerSystem_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_System_Name_prop,
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
    &CIM_System_CreationClassName_prop,
    &CIM_ComputerSystem_NameFormat_prop,
    &CIM_System_PrimaryOwnerName_prop,
    &CIM_System_PrimaryOwnerContact_prop,
    &CIM_System_Roles_prop,
    &CIM_System_OtherIdentifyingInfo_prop,
    &CIM_System_IdentifyingDescriptions_prop,
    &CIM_ComputerSystem_Dedicated_prop,
    &CIM_ComputerSystem_OtherDedicatedDescriptions_prop,
    &CIM_ComputerSystem_ResetCapability_prop,
    &CIM_ComputerSystem_PowerManagementCapabilities_prop,
};

static MI_CONST MI_Char* CIM_ComputerSystem_SetPowerState_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PowerManagementService.SetPowerState"),
};

static MI_CONST MI_ConstStringA CIM_ComputerSystem_SetPowerState_Deprecated_qual_value =
{
    CIM_ComputerSystem_SetPowerState_Deprecated_qual_data_value,
    MI_COUNT(CIM_ComputerSystem_SetPowerState_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ComputerSystem_SetPowerState_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ComputerSystem_SetPowerState_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ComputerSystem_SetPowerState_quals[] =
{
    &CIM_ComputerSystem_SetPowerState_Deprecated_qual,
};

/* parameter CIM_ComputerSystem.SetPowerState(): PowerState */
static MI_CONST MI_ParameterDecl CIM_ComputerSystem_SetPowerState_PowerState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0070650A, /* code */
    MI_T("PowerState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ComputerSystem_SetPowerState, PowerState), /* offset */
};

/* parameter CIM_ComputerSystem.SetPowerState(): Time */
static MI_CONST MI_ParameterDecl CIM_ComputerSystem_SetPowerState_Time_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00746504, /* code */
    MI_T("Time"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ComputerSystem_SetPowerState, Time), /* offset */
};

static MI_CONST MI_Char* CIM_ComputerSystem_SetPowerState_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PowerManagementService.SetPowerState"),
};

static MI_CONST MI_ConstStringA CIM_ComputerSystem_SetPowerState_MIReturn_Deprecated_qual_value =
{
    CIM_ComputerSystem_SetPowerState_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(CIM_ComputerSystem_SetPowerState_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ComputerSystem_SetPowerState_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ComputerSystem_SetPowerState_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ComputerSystem_SetPowerState_MIReturn_quals[] =
{
    &CIM_ComputerSystem_SetPowerState_MIReturn_Deprecated_qual,
};

/* parameter CIM_ComputerSystem.SetPowerState(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_ComputerSystem_SetPowerState_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    CIM_ComputerSystem_SetPowerState_MIReturn_quals, /* qualifiers */
    MI_COUNT(CIM_ComputerSystem_SetPowerState_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ComputerSystem_SetPowerState, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_ComputerSystem_SetPowerState_params[] =
{
    &CIM_ComputerSystem_SetPowerState_MIReturn_param,
    &CIM_ComputerSystem_SetPowerState_PowerState_param,
    &CIM_ComputerSystem_SetPowerState_Time_param,
};

/* method CIM_ComputerSystem.SetPowerState() */
MI_CONST MI_MethodDecl CIM_ComputerSystem_SetPowerState_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650D, /* code */
    MI_T("SetPowerState"), /* name */
    CIM_ComputerSystem_SetPowerState_quals, /* qualifiers */
    MI_COUNT(CIM_ComputerSystem_SetPowerState_quals), /* numQualifiers */
    CIM_ComputerSystem_SetPowerState_params, /* parameters */
    MI_COUNT(CIM_ComputerSystem_SetPowerState_params), /* numParameters */
    sizeof(CIM_ComputerSystem_SetPowerState), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_ComputerSystem"), /* origin */
    MI_T("CIM_ComputerSystem"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_ComputerSystem_meths[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_rtti,
    &CIM_ComputerSystem_SetPowerState_rtti,
};

static MI_CONST MI_Char* CIM_ComputerSystem_UMLPackagePath_qual_value = MI_T("CIM::System::SystemElements");

static MI_CONST MI_Qualifier CIM_ComputerSystem_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_ComputerSystem_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_ComputerSystem_Version_qual_value = MI_T("2.28.0");

static MI_CONST MI_Qualifier CIM_ComputerSystem_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_ComputerSystem_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ComputerSystem_quals[] =
{
    &CIM_ComputerSystem_UMLPackagePath_qual,
    &CIM_ComputerSystem_Version_qual,
};

/* class CIM_ComputerSystem */
MI_CONST MI_ClassDecl CIM_ComputerSystem_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00636D12, /* code */
    MI_T("CIM_ComputerSystem"), /* name */
    CIM_ComputerSystem_quals, /* qualifiers */
    MI_COUNT(CIM_ComputerSystem_quals), /* numQualifiers */
    CIM_ComputerSystem_props, /* properties */
    MI_COUNT(CIM_ComputerSystem_props), /* numProperties */
    sizeof(CIM_ComputerSystem), /* size */
    MI_T("CIM_System"), /* superClass */
    &CIM_System_rtti, /* superClassDecl */
    CIM_ComputerSystem_meths, /* methods */
    MI_COUNT(CIM_ComputerSystem_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ABC_ComputerSystem
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_ComputerSystem_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_System_Name_prop,
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
    &CIM_System_CreationClassName_prop,
    &CIM_ComputerSystem_NameFormat_prop,
    &CIM_System_PrimaryOwnerName_prop,
    &CIM_System_PrimaryOwnerContact_prop,
    &CIM_System_Roles_prop,
    &CIM_System_OtherIdentifyingInfo_prop,
    &CIM_System_IdentifyingDescriptions_prop,
    &CIM_ComputerSystem_Dedicated_prop,
    &CIM_ComputerSystem_OtherDedicatedDescriptions_prop,
    &CIM_ComputerSystem_ResetCapability_prop,
    &CIM_ComputerSystem_PowerManagementCapabilities_prop,
};

static MI_CONST MI_Char* ABC_ComputerSystem_RequestStateChange_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_ComputerSystem_RequestStateChange_ModelCorrespondence_qual_value =
{
    ABC_ComputerSystem_RequestStateChange_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_ComputerSystem_RequestStateChange_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_ComputerSystem_RequestStateChange_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_ComputerSystem_RequestStateChange_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_ComputerSystem_RequestStateChange_quals[] =
{
    &ABC_ComputerSystem_RequestStateChange_ModelCorrespondence_qual,
};

static MI_CONST MI_Char* ABC_ComputerSystem_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_ComputerSystem_RequestStateChange_RequestedState_ModelCorrespondence_qual_value =
{
    ABC_ComputerSystem_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_ComputerSystem_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_ComputerSystem_RequestStateChange_RequestedState_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_ComputerSystem_RequestStateChange_RequestedState_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_ComputerSystem_RequestStateChange_RequestedState_quals[] =
{
    &ABC_ComputerSystem_RequestStateChange_RequestedState_ModelCorrespondence_qual,
};

/* parameter ABC_ComputerSystem.RequestStateChange(): RequestedState */
static MI_CONST MI_ParameterDecl ABC_ComputerSystem_RequestStateChange_RequestedState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0072650E, /* code */
    MI_T("RequestedState"), /* name */
    ABC_ComputerSystem_RequestStateChange_RequestedState_quals, /* qualifiers */
    MI_COUNT(ABC_ComputerSystem_RequestStateChange_RequestedState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_ComputerSystem_RequestStateChange, RequestedState), /* offset */
};

/* parameter ABC_ComputerSystem.RequestStateChange(): Job */
static MI_CONST MI_ParameterDecl ABC_ComputerSystem_RequestStateChange_Job_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006A6203, /* code */
    MI_T("Job"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ConcreteJob"), /* className */
    0, /* subscript */
    offsetof(ABC_ComputerSystem_RequestStateChange, Job), /* offset */
};

/* parameter ABC_ComputerSystem.RequestStateChange(): TimeoutPeriod */
static MI_CONST MI_ParameterDecl ABC_ComputerSystem_RequestStateChange_TimeoutPeriod_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0074640D, /* code */
    MI_T("TimeoutPeriod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_ComputerSystem_RequestStateChange, TimeoutPeriod), /* offset */
};

static MI_CONST MI_Char* ABC_ComputerSystem_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_ComputerSystem_RequestStateChange_MIReturn_ModelCorrespondence_qual_value =
{
    ABC_ComputerSystem_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_ComputerSystem_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_ComputerSystem_RequestStateChange_MIReturn_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_ComputerSystem_RequestStateChange_MIReturn_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_ComputerSystem_RequestStateChange_MIReturn_quals[] =
{
    &ABC_ComputerSystem_RequestStateChange_MIReturn_ModelCorrespondence_qual,
};

/* parameter ABC_ComputerSystem.RequestStateChange(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_ComputerSystem_RequestStateChange_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_ComputerSystem_RequestStateChange_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_ComputerSystem_RequestStateChange_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_ComputerSystem_RequestStateChange, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_ComputerSystem_RequestStateChange_params[] =
{
    &ABC_ComputerSystem_RequestStateChange_MIReturn_param,
    &ABC_ComputerSystem_RequestStateChange_RequestedState_param,
    &ABC_ComputerSystem_RequestStateChange_Job_param,
    &ABC_ComputerSystem_RequestStateChange_TimeoutPeriod_param,
};

/* method ABC_ComputerSystem.RequestStateChange() */
MI_CONST MI_MethodDecl ABC_ComputerSystem_RequestStateChange_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00726512, /* code */
    MI_T("RequestStateChange"), /* name */
    ABC_ComputerSystem_RequestStateChange_quals, /* qualifiers */
    MI_COUNT(ABC_ComputerSystem_RequestStateChange_quals), /* numQualifiers */
    ABC_ComputerSystem_RequestStateChange_params, /* parameters */
    MI_COUNT(ABC_ComputerSystem_RequestStateChange_params), /* numParameters */
    sizeof(ABC_ComputerSystem_RequestStateChange), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_ComputerSystem_Invoke_RequestStateChange, /* method */
};

static MI_CONST MI_Char* ABC_ComputerSystem_SetPowerState_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PowerManagementService.SetPowerState"),
};

static MI_CONST MI_ConstStringA ABC_ComputerSystem_SetPowerState_Deprecated_qual_value =
{
    ABC_ComputerSystem_SetPowerState_Deprecated_qual_data_value,
    MI_COUNT(ABC_ComputerSystem_SetPowerState_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_ComputerSystem_SetPowerState_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_ComputerSystem_SetPowerState_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_ComputerSystem_SetPowerState_quals[] =
{
    &ABC_ComputerSystem_SetPowerState_Deprecated_qual,
};

/* parameter ABC_ComputerSystem.SetPowerState(): PowerState */
static MI_CONST MI_ParameterDecl ABC_ComputerSystem_SetPowerState_PowerState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0070650A, /* code */
    MI_T("PowerState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_ComputerSystem_SetPowerState, PowerState), /* offset */
};

/* parameter ABC_ComputerSystem.SetPowerState(): Time */
static MI_CONST MI_ParameterDecl ABC_ComputerSystem_SetPowerState_Time_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00746504, /* code */
    MI_T("Time"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_ComputerSystem_SetPowerState, Time), /* offset */
};

static MI_CONST MI_Char* ABC_ComputerSystem_SetPowerState_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PowerManagementService.SetPowerState"),
};

static MI_CONST MI_ConstStringA ABC_ComputerSystem_SetPowerState_MIReturn_Deprecated_qual_value =
{
    ABC_ComputerSystem_SetPowerState_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_ComputerSystem_SetPowerState_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_ComputerSystem_SetPowerState_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_ComputerSystem_SetPowerState_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_ComputerSystem_SetPowerState_MIReturn_quals[] =
{
    &ABC_ComputerSystem_SetPowerState_MIReturn_Deprecated_qual,
};

/* parameter ABC_ComputerSystem.SetPowerState(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_ComputerSystem_SetPowerState_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_ComputerSystem_SetPowerState_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_ComputerSystem_SetPowerState_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_ComputerSystem_SetPowerState, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_ComputerSystem_SetPowerState_params[] =
{
    &ABC_ComputerSystem_SetPowerState_MIReturn_param,
    &ABC_ComputerSystem_SetPowerState_PowerState_param,
    &ABC_ComputerSystem_SetPowerState_Time_param,
};

/* method ABC_ComputerSystem.SetPowerState() */
MI_CONST MI_MethodDecl ABC_ComputerSystem_SetPowerState_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650D, /* code */
    MI_T("SetPowerState"), /* name */
    ABC_ComputerSystem_SetPowerState_quals, /* qualifiers */
    MI_COUNT(ABC_ComputerSystem_SetPowerState_quals), /* numQualifiers */
    ABC_ComputerSystem_SetPowerState_params, /* parameters */
    MI_COUNT(ABC_ComputerSystem_SetPowerState_params), /* numParameters */
    sizeof(ABC_ComputerSystem_SetPowerState), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_ComputerSystem"), /* origin */
    MI_T("CIM_ComputerSystem"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_ComputerSystem_Invoke_SetPowerState, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST ABC_ComputerSystem_meths[] =
{
    &ABC_ComputerSystem_RequestStateChange_rtti,
    &ABC_ComputerSystem_SetPowerState_rtti,
};

static MI_CONST MI_ProviderFT ABC_ComputerSystem_funcs =
{
  (MI_ProviderFT_Load)ABC_ComputerSystem_Load,
  (MI_ProviderFT_Unload)ABC_ComputerSystem_Unload,
  (MI_ProviderFT_GetInstance)ABC_ComputerSystem_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_ComputerSystem_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_ComputerSystem_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_ComputerSystem_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_ComputerSystem_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_ComputerSystem_UMLPackagePath_qual_value = MI_T("CIM::System::SystemElements");

static MI_CONST MI_Qualifier ABC_ComputerSystem_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_ComputerSystem_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_ComputerSystem_quals[] =
{
    &ABC_ComputerSystem_UMLPackagePath_qual,
};

/* class ABC_ComputerSystem */
MI_CONST MI_ClassDecl ABC_ComputerSystem_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00616D12, /* code */
    MI_T("ABC_ComputerSystem"), /* name */
    ABC_ComputerSystem_quals, /* qualifiers */
    MI_COUNT(ABC_ComputerSystem_quals), /* numQualifiers */
    ABC_ComputerSystem_props, /* properties */
    MI_COUNT(ABC_ComputerSystem_props), /* numProperties */
    sizeof(ABC_ComputerSystem), /* size */
    MI_T("CIM_ComputerSystem"), /* superClass */
    &CIM_ComputerSystem_rtti, /* superClassDecl */
    ABC_ComputerSystem_meths, /* methods */
    MI_COUNT(ABC_ComputerSystem_meths), /* numMethods */
    &schemaDecl, /* schema */
    &ABC_ComputerSystem_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_Dependency
**
**==============================================================================
*/

/* property CIM_Dependency.Antecedent */
static MI_CONST MI_PropertyDecl CIM_Dependency_Antecedent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0061740A, /* code */
    MI_T("Antecedent"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(CIM_Dependency, Antecedent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("CIM_Dependency"), /* propagator */
    NULL,
};

/* property CIM_Dependency.Dependent */
static MI_CONST MI_PropertyDecl CIM_Dependency_Dependent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00647409, /* code */
    MI_T("Dependent"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(CIM_Dependency, Dependent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("CIM_Dependency"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Dependency_props[] =
{
    &CIM_Dependency_Antecedent_prop,
    &CIM_Dependency_Dependent_prop,
};

static MI_CONST MI_Char* CIM_Dependency_Version_qual_value = MI_T("2.10.0");

static MI_CONST MI_Qualifier CIM_Dependency_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Dependency_Version_qual_value
};

static MI_CONST MI_Char* CIM_Dependency_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_Dependency_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Dependency_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Dependency_quals[] =
{
    &CIM_Dependency_Version_qual,
    &CIM_Dependency_UMLPackagePath_qual,
};

/* class CIM_Dependency */
MI_CONST MI_ClassDecl CIM_Dependency_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION|MI_FLAG_ABSTRACT, /* flags */
    0x0063790E, /* code */
    MI_T("CIM_Dependency"), /* name */
    CIM_Dependency_quals, /* qualifiers */
    MI_COUNT(CIM_Dependency_quals), /* numQualifiers */
    CIM_Dependency_props, /* properties */
    MI_COUNT(CIM_Dependency_props), /* numProperties */
    sizeof(CIM_Dependency), /* size */
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
** CIM_AssociatedCooling
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_AssociatedCooling_Antecedent_Override_qual_value = MI_T("Antecedent");

static MI_CONST MI_Qualifier CIM_AssociatedCooling_Antecedent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_AssociatedCooling_Antecedent_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_AssociatedCooling_Antecedent_quals[] =
{
    &CIM_AssociatedCooling_Antecedent_Override_qual,
};

/* property CIM_AssociatedCooling.Antecedent */
static MI_CONST MI_PropertyDecl CIM_AssociatedCooling_Antecedent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0061740A, /* code */
    MI_T("Antecedent"), /* name */
    CIM_AssociatedCooling_Antecedent_quals, /* qualifiers */
    MI_COUNT(CIM_AssociatedCooling_Antecedent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_CoolingDevice"), /* className */
    0, /* subscript */
    offsetof(CIM_AssociatedCooling, Antecedent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("CIM_AssociatedCooling"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_AssociatedCooling_Dependent_Override_qual_value = MI_T("Dependent");

static MI_CONST MI_Qualifier CIM_AssociatedCooling_Dependent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_AssociatedCooling_Dependent_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_AssociatedCooling_Dependent_quals[] =
{
    &CIM_AssociatedCooling_Dependent_Override_qual,
};

/* property CIM_AssociatedCooling.Dependent */
static MI_CONST MI_PropertyDecl CIM_AssociatedCooling_Dependent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00647409, /* code */
    MI_T("Dependent"), /* name */
    CIM_AssociatedCooling_Dependent_quals, /* qualifiers */
    MI_COUNT(CIM_AssociatedCooling_Dependent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedSystemElement"), /* className */
    0, /* subscript */
    offsetof(CIM_AssociatedCooling, Dependent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("CIM_AssociatedCooling"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_AssociatedCooling_props[] =
{
    &CIM_AssociatedCooling_Antecedent_prop,
    &CIM_AssociatedCooling_Dependent_prop,
};

static MI_CONST MI_Char* CIM_AssociatedCooling_UMLPackagePath_qual_value = MI_T("CIM::Device::CoolingAndPower");

static MI_CONST MI_Qualifier CIM_AssociatedCooling_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_AssociatedCooling_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_AssociatedCooling_Version_qual_value = MI_T("2.19.1");

static MI_CONST MI_Qualifier CIM_AssociatedCooling_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_AssociatedCooling_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_AssociatedCooling_quals[] =
{
    &CIM_AssociatedCooling_UMLPackagePath_qual,
    &CIM_AssociatedCooling_Version_qual,
};

/* class CIM_AssociatedCooling */
MI_CONST MI_ClassDecl CIM_AssociatedCooling_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00636715, /* code */
    MI_T("CIM_AssociatedCooling"), /* name */
    CIM_AssociatedCooling_quals, /* qualifiers */
    MI_COUNT(CIM_AssociatedCooling_quals), /* numQualifiers */
    CIM_AssociatedCooling_props, /* properties */
    MI_COUNT(CIM_AssociatedCooling_props), /* numProperties */
    sizeof(CIM_AssociatedCooling), /* size */
    MI_T("CIM_Dependency"), /* superClass */
    &CIM_Dependency_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ABC_AssociatedCooling
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_AssociatedCooling_props[] =
{
    &CIM_AssociatedCooling_Antecedent_prop,
    &CIM_AssociatedCooling_Dependent_prop,
};

static void MI_CALL ABC_AssociatedCooling_AssociatorInstances(
    ABC_AssociatedCooling_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (CIM_CoolingDevice_IsA(instanceName))
    {
        if (_Match(role, MI_T("Antecedent")) && 
            _Match(resultRole, MI_T("Dependent")))
        {
            ABC_AssociatedCooling_AssociatorInstancesAntecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_CoolingDevice*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (CIM_ManagedSystemElement_IsA(instanceName))
    {
        if (_Match(role, MI_T("Dependent")) && 
            _Match(resultRole, MI_T("Antecedent")))
        {
            ABC_AssociatedCooling_AssociatorInstancesDependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_ManagedSystemElement*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL ABC_AssociatedCooling_ReferenceInstances(
    ABC_AssociatedCooling_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (CIM_CoolingDevice_IsA(instanceName))
    {
        if (_Match(role, MI_T("Antecedent")))
        {
            ABC_AssociatedCooling_ReferenceInstancesAntecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_CoolingDevice*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (CIM_ManagedSystemElement_IsA(instanceName))
    {
        if (_Match(role, MI_T("Dependent")))
        {
            ABC_AssociatedCooling_ReferenceInstancesDependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_ManagedSystemElement*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT ABC_AssociatedCooling_funcs =
{
  (MI_ProviderFT_Load)ABC_AssociatedCooling_Load,
  (MI_ProviderFT_Unload)ABC_AssociatedCooling_Unload,
  (MI_ProviderFT_GetInstance)ABC_AssociatedCooling_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_AssociatedCooling_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_AssociatedCooling_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_AssociatedCooling_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_AssociatedCooling_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)ABC_AssociatedCooling_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)ABC_AssociatedCooling_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_AssociatedCooling_UMLPackagePath_qual_value = MI_T("CIM::Device::CoolingAndPower");

static MI_CONST MI_Qualifier ABC_AssociatedCooling_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_AssociatedCooling_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_AssociatedCooling_quals[] =
{
    &ABC_AssociatedCooling_UMLPackagePath_qual,
};

/* class ABC_AssociatedCooling */
MI_CONST MI_ClassDecl ABC_AssociatedCooling_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00616715, /* code */
    MI_T("ABC_AssociatedCooling"), /* name */
    ABC_AssociatedCooling_quals, /* qualifiers */
    MI_COUNT(ABC_AssociatedCooling_quals), /* numQualifiers */
    ABC_AssociatedCooling_props, /* properties */
    MI_COUNT(ABC_AssociatedCooling_props), /* numProperties */
    sizeof(ABC_AssociatedCooling), /* size */
    MI_T("CIM_AssociatedCooling"), /* superClass */
    &CIM_AssociatedCooling_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &ABC_AssociatedCooling_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ABC_ManagedSystemElement
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_ManagedSystemElement_props[] =
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

static MI_CONST MI_ProviderFT ABC_ManagedSystemElement_funcs =
{
  (MI_ProviderFT_Load)ABC_ManagedSystemElement_Load,
  (MI_ProviderFT_Unload)ABC_ManagedSystemElement_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)NULL,
  (MI_ProviderFT_CreateInstance)NULL,
  (MI_ProviderFT_ModifyInstance)NULL,
  (MI_ProviderFT_DeleteInstance)NULL,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_ManagedSystemElement_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier ABC_ManagedSystemElement_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_ManagedSystemElement_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_ManagedSystemElement_quals[] =
{
    &ABC_ManagedSystemElement_UMLPackagePath_qual,
};

/* class ABC_ManagedSystemElement */
MI_CONST MI_ClassDecl ABC_ManagedSystemElement_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00617418, /* code */
    MI_T("ABC_ManagedSystemElement"), /* name */
    ABC_ManagedSystemElement_quals, /* qualifiers */
    MI_COUNT(ABC_ManagedSystemElement_quals), /* numQualifiers */
    ABC_ManagedSystemElement_props, /* properties */
    MI_COUNT(ABC_ManagedSystemElement_props), /* numProperties */
    sizeof(ABC_ManagedSystemElement), /* size */
    MI_T("CIM_ManagedSystemElement"), /* superClass */
    &CIM_ManagedSystemElement_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &ABC_ManagedSystemElement_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_Capabilities
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_Capabilities_InstanceID_Override_qual_value = MI_T("InstanceID");

static MI_CONST MI_Qualifier CIM_Capabilities_InstanceID_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_Capabilities_InstanceID_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Capabilities_InstanceID_quals[] =
{
    &CIM_Capabilities_InstanceID_Override_qual,
};

/* property CIM_Capabilities.InstanceID */
static MI_CONST MI_PropertyDecl CIM_Capabilities_InstanceID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0069640A, /* code */
    MI_T("InstanceID"), /* name */
    CIM_Capabilities_InstanceID_quals, /* qualifiers */
    MI_COUNT(CIM_Capabilities_InstanceID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Capabilities, InstanceID), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_Capabilities"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Capabilities_ElementName_Override_qual_value = MI_T("ElementName");

static MI_CONST MI_Qualifier CIM_Capabilities_ElementName_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_Capabilities_ElementName_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Capabilities_ElementName_quals[] =
{
    &CIM_Capabilities_ElementName_Override_qual,
};

/* property CIM_Capabilities.ElementName */
static MI_CONST MI_PropertyDecl CIM_Capabilities_ElementName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
    0x0065650B, /* code */
    MI_T("ElementName"), /* name */
    CIM_Capabilities_ElementName_quals, /* qualifiers */
    MI_COUNT(CIM_Capabilities_ElementName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Capabilities, ElementName), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_Capabilities"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Capabilities_props[] =
{
    &CIM_Capabilities_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_Capabilities_ElementName_prop,
};

static MI_CONST MI_Char* CIM_Capabilities_UMLPackagePath_qual_value = MI_T("CIM::Core::Capabilities");

static MI_CONST MI_Qualifier CIM_Capabilities_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Capabilities_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_Capabilities_Version_qual_value = MI_T("2.19.0");

static MI_CONST MI_Qualifier CIM_Capabilities_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Capabilities_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Capabilities_quals[] =
{
    &CIM_Capabilities_UMLPackagePath_qual,
    &CIM_Capabilities_Version_qual,
};

/* class CIM_Capabilities */
MI_CONST MI_ClassDecl CIM_Capabilities_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00637310, /* code */
    MI_T("CIM_Capabilities"), /* name */
    CIM_Capabilities_quals, /* qualifiers */
    MI_COUNT(CIM_Capabilities_quals), /* numQualifiers */
    CIM_Capabilities_props, /* properties */
    MI_COUNT(CIM_Capabilities_props), /* numProperties */
    sizeof(CIM_Capabilities), /* size */
    MI_T("CIM_ManagedElement"), /* superClass */
    &CIM_ManagedElement_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_ElementCapabilities
**
**==============================================================================
*/

static MI_CONST MI_Uint32 CIM_ElementCapabilities_ManagedElement_Min_qual_value = 1U;

static MI_CONST MI_Qualifier CIM_ElementCapabilities_ManagedElement_Min_qual =
{
    MI_T("Min"),
    MI_UINT32,
    0,
    &CIM_ElementCapabilities_ManagedElement_Min_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ElementCapabilities_ManagedElement_quals[] =
{
    &CIM_ElementCapabilities_ManagedElement_Min_qual,
};

/* property CIM_ElementCapabilities.ManagedElement */
static MI_CONST MI_PropertyDecl CIM_ElementCapabilities_ManagedElement_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006D740E, /* code */
    MI_T("ManagedElement"), /* name */
    CIM_ElementCapabilities_ManagedElement_quals, /* qualifiers */
    MI_COUNT(CIM_ElementCapabilities_ManagedElement_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(CIM_ElementCapabilities, ManagedElement), /* offset */
    MI_T("CIM_ElementCapabilities"), /* origin */
    MI_T("CIM_ElementCapabilities"), /* propagator */
    NULL,
};

/* property CIM_ElementCapabilities.Capabilities */
static MI_CONST MI_PropertyDecl CIM_ElementCapabilities_Capabilities_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0063730C, /* code */
    MI_T("Capabilities"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_Capabilities"), /* className */
    0, /* subscript */
    offsetof(CIM_ElementCapabilities, Capabilities), /* offset */
    MI_T("CIM_ElementCapabilities"), /* origin */
    MI_T("CIM_ElementCapabilities"), /* propagator */
    NULL,
};

/* property CIM_ElementCapabilities.Characteristics */
static MI_CONST MI_PropertyDecl CIM_ElementCapabilities_Characteristics_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063730F, /* code */
    MI_T("Characteristics"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ElementCapabilities, Characteristics), /* offset */
    MI_T("CIM_ElementCapabilities"), /* origin */
    MI_T("CIM_ElementCapabilities"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_ElementCapabilities_props[] =
{
    &CIM_ElementCapabilities_ManagedElement_prop,
    &CIM_ElementCapabilities_Capabilities_prop,
    &CIM_ElementCapabilities_Characteristics_prop,
};

static MI_CONST MI_Char* CIM_ElementCapabilities_Version_qual_value = MI_T("2.24.0");

static MI_CONST MI_Qualifier CIM_ElementCapabilities_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_ElementCapabilities_Version_qual_value
};

static MI_CONST MI_Char* CIM_ElementCapabilities_UMLPackagePath_qual_value = MI_T("CIM::Core::Capabilities");

static MI_CONST MI_Qualifier CIM_ElementCapabilities_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_ElementCapabilities_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ElementCapabilities_quals[] =
{
    &CIM_ElementCapabilities_Version_qual,
    &CIM_ElementCapabilities_UMLPackagePath_qual,
};

/* class CIM_ElementCapabilities */
MI_CONST MI_ClassDecl CIM_ElementCapabilities_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00637317, /* code */
    MI_T("CIM_ElementCapabilities"), /* name */
    CIM_ElementCapabilities_quals, /* qualifiers */
    MI_COUNT(CIM_ElementCapabilities_quals), /* numQualifiers */
    CIM_ElementCapabilities_props, /* properties */
    MI_COUNT(CIM_ElementCapabilities_props), /* numProperties */
    sizeof(CIM_ElementCapabilities), /* size */
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
** CIM_EnabledLogicalElementCapabilities
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_EnabledLogicalElementCapabilities_ElementNameEditSupported_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ManagedElement.ElementName"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElementCapabilities_ElementNameEditSupported_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElementCapabilities_ElementNameEditSupported_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElementCapabilities_ElementNameEditSupported_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElementCapabilities_ElementNameEditSupported_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElementCapabilities_ElementNameEditSupported_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElementCapabilities_ElementNameEditSupported_quals[] =
{
    &CIM_EnabledLogicalElementCapabilities_ElementNameEditSupported_ModelCorrespondence_qual,
};

/* property CIM_EnabledLogicalElementCapabilities.ElementNameEditSupported */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElementCapabilities_ElementNameEditSupported_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656418, /* code */
    MI_T("ElementNameEditSupported"), /* name */
    CIM_EnabledLogicalElementCapabilities_ElementNameEditSupported_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElementCapabilities_ElementNameEditSupported_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElementCapabilities, ElementNameEditSupported), /* offset */
    MI_T("CIM_EnabledLogicalElementCapabilities"), /* origin */
    MI_T("CIM_EnabledLogicalElementCapabilities"), /* propagator */
    NULL,
};

static MI_CONST MI_Sint64 CIM_EnabledLogicalElementCapabilities_MaxElementNameLen_MaxValue_qual_value = MI_LL(256);

static MI_CONST MI_Qualifier CIM_EnabledLogicalElementCapabilities_MaxElementNameLen_MaxValue_qual =
{
    MI_T("MaxValue"),
    MI_SINT64,
    0,
    &CIM_EnabledLogicalElementCapabilities_MaxElementNameLen_MaxValue_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElementCapabilities_MaxElementNameLen_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_FCSwitchCapabilities.ElementNameEditSupported"),
    MI_T("CIM_EnabledLogicalElementCapabilities.ElementNameMask"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElementCapabilities_MaxElementNameLen_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElementCapabilities_MaxElementNameLen_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElementCapabilities_MaxElementNameLen_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElementCapabilities_MaxElementNameLen_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElementCapabilities_MaxElementNameLen_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElementCapabilities_MaxElementNameLen_quals[] =
{
    &CIM_EnabledLogicalElementCapabilities_MaxElementNameLen_MaxValue_qual,
    &CIM_EnabledLogicalElementCapabilities_MaxElementNameLen_ModelCorrespondence_qual,
};

/* property CIM_EnabledLogicalElementCapabilities.MaxElementNameLen */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElementCapabilities_MaxElementNameLen_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D6E11, /* code */
    MI_T("MaxElementNameLen"), /* name */
    CIM_EnabledLogicalElementCapabilities_MaxElementNameLen_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElementCapabilities_MaxElementNameLen_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElementCapabilities, MaxElementNameLen), /* offset */
    MI_T("CIM_EnabledLogicalElementCapabilities"), /* origin */
    MI_T("CIM_EnabledLogicalElementCapabilities"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElementCapabilities_RequestedStatesSupported_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElementCapabilities_RequestedStatesSupported_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElementCapabilities_RequestedStatesSupported_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElementCapabilities_RequestedStatesSupported_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElementCapabilities_RequestedStatesSupported_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElementCapabilities_RequestedStatesSupported_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElementCapabilities_RequestedStatesSupported_quals[] =
{
    &CIM_EnabledLogicalElementCapabilities_RequestedStatesSupported_ModelCorrespondence_qual,
};

/* property CIM_EnabledLogicalElementCapabilities.RequestedStatesSupported */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElementCapabilities_RequestedStatesSupported_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726418, /* code */
    MI_T("RequestedStatesSupported"), /* name */
    CIM_EnabledLogicalElementCapabilities_RequestedStatesSupported_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElementCapabilities_RequestedStatesSupported_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElementCapabilities, RequestedStatesSupported), /* offset */
    MI_T("CIM_EnabledLogicalElementCapabilities"), /* origin */
    MI_T("CIM_EnabledLogicalElementCapabilities"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElementCapabilities_ElementNameMask_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElementCapabilities.MaxElementNameLen"),
};

static MI_CONST MI_ConstStringA CIM_EnabledLogicalElementCapabilities_ElementNameMask_ModelCorrespondence_qual_value =
{
    CIM_EnabledLogicalElementCapabilities_ElementNameMask_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_EnabledLogicalElementCapabilities_ElementNameMask_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_EnabledLogicalElementCapabilities_ElementNameMask_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_EnabledLogicalElementCapabilities_ElementNameMask_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElementCapabilities_ElementNameMask_quals[] =
{
    &CIM_EnabledLogicalElementCapabilities_ElementNameMask_ModelCorrespondence_qual,
};

/* property CIM_EnabledLogicalElementCapabilities.ElementNameMask */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElementCapabilities_ElementNameMask_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656B0F, /* code */
    MI_T("ElementNameMask"), /* name */
    CIM_EnabledLogicalElementCapabilities_ElementNameMask_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElementCapabilities_ElementNameMask_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElementCapabilities, ElementNameMask), /* offset */
    MI_T("CIM_EnabledLogicalElementCapabilities"), /* origin */
    MI_T("CIM_EnabledLogicalElementCapabilities"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_EnabledLogicalElementCapabilities_props[] =
{
    &CIM_Capabilities_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_Capabilities_ElementName_prop,
    &CIM_EnabledLogicalElementCapabilities_ElementNameEditSupported_prop,
    &CIM_EnabledLogicalElementCapabilities_MaxElementNameLen_prop,
    &CIM_EnabledLogicalElementCapabilities_RequestedStatesSupported_prop,
    &CIM_EnabledLogicalElementCapabilities_ElementNameMask_prop,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElementCapabilities_UMLPackagePath_qual_value = MI_T("CIM::Core::Capabilities");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElementCapabilities_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_EnabledLogicalElementCapabilities_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElementCapabilities_Version_qual_value = MI_T("2.22.0");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElementCapabilities_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_EnabledLogicalElementCapabilities_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElementCapabilities_quals[] =
{
    &CIM_EnabledLogicalElementCapabilities_UMLPackagePath_qual,
    &CIM_EnabledLogicalElementCapabilities_Version_qual,
};

/* class CIM_EnabledLogicalElementCapabilities */
MI_CONST MI_ClassDecl CIM_EnabledLogicalElementCapabilities_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00637325, /* code */
    MI_T("CIM_EnabledLogicalElementCapabilities"), /* name */
    CIM_EnabledLogicalElementCapabilities_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElementCapabilities_quals), /* numQualifiers */
    CIM_EnabledLogicalElementCapabilities_props, /* properties */
    MI_COUNT(CIM_EnabledLogicalElementCapabilities_props), /* numProperties */
    sizeof(CIM_EnabledLogicalElementCapabilities), /* size */
    MI_T("CIM_Capabilities"), /* superClass */
    &CIM_Capabilities_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ABC_EnabledLogicalElementCapabilities
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_EnabledLogicalElementCapabilities_props[] =
{
    &CIM_Capabilities_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_Capabilities_ElementName_prop,
    &CIM_EnabledLogicalElementCapabilities_ElementNameEditSupported_prop,
    &CIM_EnabledLogicalElementCapabilities_MaxElementNameLen_prop,
    &CIM_EnabledLogicalElementCapabilities_RequestedStatesSupported_prop,
    &CIM_EnabledLogicalElementCapabilities_ElementNameMask_prop,
};

static MI_CONST MI_ProviderFT ABC_EnabledLogicalElementCapabilities_funcs =
{
  (MI_ProviderFT_Load)ABC_EnabledLogicalElementCapabilities_Load,
  (MI_ProviderFT_Unload)ABC_EnabledLogicalElementCapabilities_Unload,
  (MI_ProviderFT_GetInstance)ABC_EnabledLogicalElementCapabilities_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_EnabledLogicalElementCapabilities_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_EnabledLogicalElementCapabilities_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_EnabledLogicalElementCapabilities_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_EnabledLogicalElementCapabilities_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_EnabledLogicalElementCapabilities_UMLPackagePath_qual_value = MI_T("CIM::Core::Capabilities");

static MI_CONST MI_Qualifier ABC_EnabledLogicalElementCapabilities_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_EnabledLogicalElementCapabilities_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_EnabledLogicalElementCapabilities_quals[] =
{
    &ABC_EnabledLogicalElementCapabilities_UMLPackagePath_qual,
};

/* class ABC_EnabledLogicalElementCapabilities */
MI_CONST MI_ClassDecl ABC_EnabledLogicalElementCapabilities_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00617325, /* code */
    MI_T("ABC_EnabledLogicalElementCapabilities"), /* name */
    ABC_EnabledLogicalElementCapabilities_quals, /* qualifiers */
    MI_COUNT(ABC_EnabledLogicalElementCapabilities_quals), /* numQualifiers */
    ABC_EnabledLogicalElementCapabilities_props, /* properties */
    MI_COUNT(ABC_EnabledLogicalElementCapabilities_props), /* numProperties */
    sizeof(ABC_EnabledLogicalElementCapabilities), /* size */
    MI_T("CIM_EnabledLogicalElementCapabilities"), /* superClass */
    &CIM_EnabledLogicalElementCapabilities_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &ABC_EnabledLogicalElementCapabilities_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ABC_ElementCapabilities
**
**==============================================================================
*/

static MI_CONST MI_Uint32 ABC_ElementCapabilities_ManagedElement_Min_qual_value = 1U;

static MI_CONST MI_Qualifier ABC_ElementCapabilities_ManagedElement_Min_qual =
{
    MI_T("Min"),
    MI_UINT32,
    0,
    &ABC_ElementCapabilities_ManagedElement_Min_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_ElementCapabilities_ManagedElement_quals[] =
{
    &ABC_ElementCapabilities_ManagedElement_Min_qual,
};

/* property ABC_ElementCapabilities.ManagedElement */
static MI_CONST MI_PropertyDecl ABC_ElementCapabilities_ManagedElement_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006D740E, /* code */
    MI_T("ManagedElement"), /* name */
    ABC_ElementCapabilities_ManagedElement_quals, /* qualifiers */
    MI_COUNT(ABC_ElementCapabilities_ManagedElement_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("ABC_Fan"), /* className */
    0, /* subscript */
    offsetof(ABC_ElementCapabilities, ManagedElement), /* offset */
    MI_T("CIM_ElementCapabilities"), /* origin */
    MI_T("ABC_ElementCapabilities"), /* propagator */
    NULL,
};

/* property ABC_ElementCapabilities.Capabilities */
static MI_CONST MI_PropertyDecl ABC_ElementCapabilities_Capabilities_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0063730C, /* code */
    MI_T("Capabilities"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("ABC_EnabledLogicalElementCapabilities"), /* className */
    0, /* subscript */
    offsetof(ABC_ElementCapabilities, Capabilities), /* offset */
    MI_T("CIM_ElementCapabilities"), /* origin */
    MI_T("ABC_ElementCapabilities"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST ABC_ElementCapabilities_props[] =
{
    &ABC_ElementCapabilities_ManagedElement_prop,
    &ABC_ElementCapabilities_Capabilities_prop,
    &CIM_ElementCapabilities_Characteristics_prop,
};

static void MI_CALL ABC_ElementCapabilities_AssociatorInstances(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (ABC_Fan_IsA(instanceName))
    {
        if (_Match(role, MI_T("ManagedElement")) && 
            _Match(resultRole, MI_T("Capabilities")))
        {
            ABC_ElementCapabilities_AssociatorInstancesManagedElement(
                self, 
                context, 
                nameSpace, 
                className, 
                (ABC_Fan*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (ABC_EnabledLogicalElementCapabilities_IsA(instanceName))
    {
        if (_Match(role, MI_T("Capabilities")) && 
            _Match(resultRole, MI_T("ManagedElement")))
        {
            ABC_ElementCapabilities_AssociatorInstancesCapabilities(
                self, 
                context, 
                nameSpace, 
                className, 
                (ABC_EnabledLogicalElementCapabilities*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL ABC_ElementCapabilities_ReferenceInstances(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (ABC_Fan_IsA(instanceName))
    {
        if (_Match(role, MI_T("ManagedElement")))
        {
            ABC_ElementCapabilities_ReferenceInstancesManagedElement(
                self, 
                context, 
                nameSpace, 
                className, 
                (ABC_Fan*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (ABC_EnabledLogicalElementCapabilities_IsA(instanceName))
    {
        if (_Match(role, MI_T("Capabilities")))
        {
            ABC_ElementCapabilities_ReferenceInstancesCapabilities(
                self, 
                context, 
                nameSpace, 
                className, 
                (ABC_EnabledLogicalElementCapabilities*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT ABC_ElementCapabilities_funcs =
{
  (MI_ProviderFT_Load)ABC_ElementCapabilities_Load,
  (MI_ProviderFT_Unload)ABC_ElementCapabilities_Unload,
  (MI_ProviderFT_GetInstance)ABC_ElementCapabilities_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_ElementCapabilities_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_ElementCapabilities_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_ElementCapabilities_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_ElementCapabilities_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)ABC_ElementCapabilities_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)ABC_ElementCapabilities_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_ElementCapabilities_UMLPackagePath_qual_value = MI_T("CIM::Core::Capabilities");

static MI_CONST MI_Qualifier ABC_ElementCapabilities_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_ElementCapabilities_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_ElementCapabilities_quals[] =
{
    &ABC_ElementCapabilities_UMLPackagePath_qual,
};

/* class ABC_ElementCapabilities */
MI_CONST MI_ClassDecl ABC_ElementCapabilities_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00617317, /* code */
    MI_T("ABC_ElementCapabilities"), /* name */
    ABC_ElementCapabilities_quals, /* qualifiers */
    MI_COUNT(ABC_ElementCapabilities_quals), /* numQualifiers */
    ABC_ElementCapabilities_props, /* properties */
    MI_COUNT(ABC_ElementCapabilities_props), /* numProperties */
    sizeof(ABC_ElementCapabilities), /* size */
    MI_T("CIM_ElementCapabilities"), /* superClass */
    &CIM_ElementCapabilities_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &ABC_ElementCapabilities_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_RegisteredProfile
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_RegisteredProfile_InstanceID_Override_qual_value = MI_T("InstanceID");

static MI_CONST MI_Qualifier CIM_RegisteredProfile_InstanceID_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_RegisteredProfile_InstanceID_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RegisteredProfile_InstanceID_quals[] =
{
    &CIM_RegisteredProfile_InstanceID_Override_qual,
};

/* property CIM_RegisteredProfile.InstanceID */
static MI_CONST MI_PropertyDecl CIM_RegisteredProfile_InstanceID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0069640A, /* code */
    MI_T("InstanceID"), /* name */
    CIM_RegisteredProfile_InstanceID_quals, /* qualifiers */
    MI_COUNT(CIM_RegisteredProfile_InstanceID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile, InstanceID), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_RegisteredProfile"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_RegisteredProfile_RegisteredOrganization_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_RegisteredProfile.OtherRegisteredOrganization"),
};

static MI_CONST MI_ConstStringA CIM_RegisteredProfile_RegisteredOrganization_ModelCorrespondence_qual_value =
{
    CIM_RegisteredProfile_RegisteredOrganization_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_RegisteredProfile_RegisteredOrganization_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_RegisteredProfile_RegisteredOrganization_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_RegisteredProfile_RegisteredOrganization_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RegisteredProfile_RegisteredOrganization_quals[] =
{
    &CIM_RegisteredProfile_RegisteredOrganization_ModelCorrespondence_qual,
};

/* property CIM_RegisteredProfile.RegisteredOrganization */
static MI_CONST MI_PropertyDecl CIM_RegisteredProfile_RegisteredOrganization_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
    0x00726E16, /* code */
    MI_T("RegisteredOrganization"), /* name */
    CIM_RegisteredProfile_RegisteredOrganization_quals, /* qualifiers */
    MI_COUNT(CIM_RegisteredProfile_RegisteredOrganization_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile, RegisteredOrganization), /* offset */
    MI_T("CIM_RegisteredProfile"), /* origin */
    MI_T("CIM_RegisteredProfile"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_RegisteredProfile_OtherRegisteredOrganization_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_RegisteredProfile_OtherRegisteredOrganization_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_RegisteredProfile_OtherRegisteredOrganization_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_RegisteredProfile_OtherRegisteredOrganization_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_RegisteredProfile.RegisteredOrganization"),
};

static MI_CONST MI_ConstStringA CIM_RegisteredProfile_OtherRegisteredOrganization_ModelCorrespondence_qual_value =
{
    CIM_RegisteredProfile_OtherRegisteredOrganization_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_RegisteredProfile_OtherRegisteredOrganization_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_RegisteredProfile_OtherRegisteredOrganization_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_RegisteredProfile_OtherRegisteredOrganization_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RegisteredProfile_OtherRegisteredOrganization_quals[] =
{
    &CIM_RegisteredProfile_OtherRegisteredOrganization_MaxLen_qual,
    &CIM_RegisteredProfile_OtherRegisteredOrganization_ModelCorrespondence_qual,
};

/* property CIM_RegisteredProfile.OtherRegisteredOrganization */
static MI_CONST MI_PropertyDecl CIM_RegisteredProfile_OtherRegisteredOrganization_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6E1B, /* code */
    MI_T("OtherRegisteredOrganization"), /* name */
    CIM_RegisteredProfile_OtherRegisteredOrganization_quals, /* qualifiers */
    MI_COUNT(CIM_RegisteredProfile_OtherRegisteredOrganization_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile, OtherRegisteredOrganization), /* offset */
    MI_T("CIM_RegisteredProfile"), /* origin */
    MI_T("CIM_RegisteredProfile"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_RegisteredProfile_RegisteredName_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_RegisteredProfile_RegisteredName_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_RegisteredProfile_RegisteredName_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RegisteredProfile_RegisteredName_quals[] =
{
    &CIM_RegisteredProfile_RegisteredName_MaxLen_qual,
};

/* property CIM_RegisteredProfile.RegisteredName */
static MI_CONST MI_PropertyDecl CIM_RegisteredProfile_RegisteredName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
    0x0072650E, /* code */
    MI_T("RegisteredName"), /* name */
    CIM_RegisteredProfile_RegisteredName_quals, /* qualifiers */
    MI_COUNT(CIM_RegisteredProfile_RegisteredName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile, RegisteredName), /* offset */
    MI_T("CIM_RegisteredProfile"), /* origin */
    MI_T("CIM_RegisteredProfile"), /* propagator */
    NULL,
};

/* property CIM_RegisteredProfile.RegisteredVersion */
static MI_CONST MI_PropertyDecl CIM_RegisteredProfile_RegisteredVersion_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
    0x00726E11, /* code */
    MI_T("RegisteredVersion"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile, RegisteredVersion), /* offset */
    MI_T("CIM_RegisteredProfile"), /* origin */
    MI_T("CIM_RegisteredProfile"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_RegisteredProfile_AdvertiseTypes_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_RegisteredProfile_AdvertiseTypes_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_RegisteredProfile_AdvertiseTypes_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_RegisteredProfile_AdvertiseTypes_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_RegisteredProfile.AdvertiseTypeDescriptions"),
};

static MI_CONST MI_ConstStringA CIM_RegisteredProfile_AdvertiseTypes_ModelCorrespondence_qual_value =
{
    CIM_RegisteredProfile_AdvertiseTypes_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_RegisteredProfile_AdvertiseTypes_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_RegisteredProfile_AdvertiseTypes_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_RegisteredProfile_AdvertiseTypes_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RegisteredProfile_AdvertiseTypes_quals[] =
{
    &CIM_RegisteredProfile_AdvertiseTypes_ArrayType_qual,
    &CIM_RegisteredProfile_AdvertiseTypes_ModelCorrespondence_qual,
};

/* property CIM_RegisteredProfile.AdvertiseTypes */
static MI_CONST MI_PropertyDecl CIM_RegisteredProfile_AdvertiseTypes_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
    0x0061730E, /* code */
    MI_T("AdvertiseTypes"), /* name */
    CIM_RegisteredProfile_AdvertiseTypes_quals, /* qualifiers */
    MI_COUNT(CIM_RegisteredProfile_AdvertiseTypes_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile, AdvertiseTypes), /* offset */
    MI_T("CIM_RegisteredProfile"), /* origin */
    MI_T("CIM_RegisteredProfile"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_RegisteredProfile_AdvertiseTypeDescriptions_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_RegisteredProfile_AdvertiseTypeDescriptions_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_RegisteredProfile_AdvertiseTypeDescriptions_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_RegisteredProfile_AdvertiseTypeDescriptions_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_RegisteredProfile.AdvertiseTypes"),
};

static MI_CONST MI_ConstStringA CIM_RegisteredProfile_AdvertiseTypeDescriptions_ModelCorrespondence_qual_value =
{
    CIM_RegisteredProfile_AdvertiseTypeDescriptions_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_RegisteredProfile_AdvertiseTypeDescriptions_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_RegisteredProfile_AdvertiseTypeDescriptions_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_RegisteredProfile_AdvertiseTypeDescriptions_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RegisteredProfile_AdvertiseTypeDescriptions_quals[] =
{
    &CIM_RegisteredProfile_AdvertiseTypeDescriptions_ArrayType_qual,
    &CIM_RegisteredProfile_AdvertiseTypeDescriptions_ModelCorrespondence_qual,
};

/* property CIM_RegisteredProfile.AdvertiseTypeDescriptions */
static MI_CONST MI_PropertyDecl CIM_RegisteredProfile_AdvertiseTypeDescriptions_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00617319, /* code */
    MI_T("AdvertiseTypeDescriptions"), /* name */
    CIM_RegisteredProfile_AdvertiseTypeDescriptions_quals, /* qualifiers */
    MI_COUNT(CIM_RegisteredProfile_AdvertiseTypeDescriptions_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile, AdvertiseTypeDescriptions), /* offset */
    MI_T("CIM_RegisteredProfile"), /* origin */
    MI_T("CIM_RegisteredProfile"), /* propagator */
    NULL,
};

/* property CIM_RegisteredProfile.ImplementedFeatures */
static MI_CONST MI_PropertyDecl CIM_RegisteredProfile_ImplementedFeatures_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00697313, /* code */
    MI_T("ImplementedFeatures"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile, ImplementedFeatures), /* offset */
    MI_T("CIM_RegisteredProfile"), /* origin */
    MI_T("CIM_RegisteredProfile"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_RegisteredProfile_props[] =
{
    &CIM_RegisteredProfile_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_RegisteredProfile_RegisteredOrganization_prop,
    &CIM_RegisteredProfile_OtherRegisteredOrganization_prop,
    &CIM_RegisteredProfile_RegisteredName_prop,
    &CIM_RegisteredProfile_RegisteredVersion_prop,
    &CIM_RegisteredProfile_AdvertiseTypes_prop,
    &CIM_RegisteredProfile_AdvertiseTypeDescriptions_prop,
    &CIM_RegisteredProfile_ImplementedFeatures_prop,
};

/* parameter CIM_RegisteredProfile.CloseConformantInstances(): EnumerationContext */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_CloseConformantInstances_EnumerationContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00657412, /* code */
    MI_T("EnumerationContext"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_CloseConformantInstances, EnumerationContext), /* offset */
};

/* parameter CIM_RegisteredProfile.CloseConformantInstances(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_CloseConformantInstances_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_CloseConformantInstances, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_RegisteredProfile_CloseConformantInstances_params[] =
{
    &CIM_RegisteredProfile_CloseConformantInstances_MIReturn_param,
    &CIM_RegisteredProfile_CloseConformantInstances_EnumerationContext_param,
};

/* method CIM_RegisteredProfile.CloseConformantInstances() */
MI_CONST MI_MethodDecl CIM_RegisteredProfile_CloseConformantInstances_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00637318, /* code */
    MI_T("CloseConformantInstances"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    CIM_RegisteredProfile_CloseConformantInstances_params, /* parameters */
    MI_COUNT(CIM_RegisteredProfile_CloseConformantInstances_params), /* numParameters */
    sizeof(CIM_RegisteredProfile_CloseConformantInstances), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_RegisteredProfile"), /* origin */
    MI_T("CIM_RegisteredProfile"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

/* parameter CIM_RegisteredProfile.OpenConformantInstances(): ResultClass */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_OpenConformantInstances_ResultClass_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0072730B, /* code */
    MI_T("ResultClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_OpenConformantInstances, ResultClass), /* offset */
};

/* parameter CIM_RegisteredProfile.OpenConformantInstances(): IncludedPropertyList */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_OpenConformantInstances_IncludedPropertyList_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00697414, /* code */
    MI_T("IncludedPropertyList"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_OpenConformantInstances, IncludedPropertyList), /* offset */
};

/* parameter CIM_RegisteredProfile.OpenConformantInstances(): OperationTimeout */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_OpenConformantInstances_OperationTimeout_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006F7410, /* code */
    MI_T("OperationTimeout"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_OpenConformantInstances, OperationTimeout), /* offset */
};

/* parameter CIM_RegisteredProfile.OpenConformantInstances(): ContinueOnError */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_OpenConformantInstances_ContinueOnError_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0063720F, /* code */
    MI_T("ContinueOnError"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_OpenConformantInstances, ContinueOnError), /* offset */
};

/* parameter CIM_RegisteredProfile.OpenConformantInstances(): MaxObjectCount */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_OpenConformantInstances_MaxObjectCount_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006D740E, /* code */
    MI_T("MaxObjectCount"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_OpenConformantInstances, MaxObjectCount), /* offset */
};

/* parameter CIM_RegisteredProfile.OpenConformantInstances(): EnumerationContext */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_OpenConformantInstances_EnumerationContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00657412, /* code */
    MI_T("EnumerationContext"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_OpenConformantInstances, EnumerationContext), /* offset */
};

/* parameter CIM_RegisteredProfile.OpenConformantInstances(): EndOfSequence */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_OpenConformantInstances_EndOfSequence_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0065650D, /* code */
    MI_T("EndOfSequence"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_OpenConformantInstances, EndOfSequence), /* offset */
};

static MI_CONST MI_Char* CIM_RegisteredProfile_OpenConformantInstances_InstanceType_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_RegisteredProfile_OpenConformantInstances_InstanceType_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_RegisteredProfile_OpenConformantInstances_InstanceType_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_RegisteredProfile_OpenConformantInstances_InstanceType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ProfileRegistration.OpenConformantInstances(InstanceWithPathList)"),
};

static MI_CONST MI_ConstStringA CIM_RegisteredProfile_OpenConformantInstances_InstanceType_ModelCorrespondence_qual_value =
{
    CIM_RegisteredProfile_OpenConformantInstances_InstanceType_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_RegisteredProfile_OpenConformantInstances_InstanceType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_RegisteredProfile_OpenConformantInstances_InstanceType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_RegisteredProfile_OpenConformantInstances_InstanceType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RegisteredProfile_OpenConformantInstances_InstanceType_quals[] =
{
    &CIM_RegisteredProfile_OpenConformantInstances_InstanceType_ArrayType_qual,
    &CIM_RegisteredProfile_OpenConformantInstances_InstanceType_ModelCorrespondence_qual,
};

/* parameter CIM_RegisteredProfile.OpenConformantInstances(): InstanceType */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_OpenConformantInstances_InstanceType_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0069650C, /* code */
    MI_T("InstanceType"), /* name */
    CIM_RegisteredProfile_OpenConformantInstances_InstanceType_quals, /* qualifiers */
    MI_COUNT(CIM_RegisteredProfile_OpenConformantInstances_InstanceType_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_OpenConformantInstances, InstanceType), /* offset */
};

static MI_CONST MI_Char* CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_EmbeddedInstance_qual_value = MI_T("CIM_ManagedElement");

static MI_CONST MI_Qualifier CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ProfileRegistration.OpenConformantInstances(InstanceType)"),
};

static MI_CONST MI_ConstStringA CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_value =
{
    CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_quals[] =
{
    &CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_EmbeddedInstance_qual,
    &CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ArrayType_qual,
    &CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ModelCorrespondence_qual,
};

/* parameter CIM_RegisteredProfile.OpenConformantInstances(): InstanceWithPathList */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00697414, /* code */
    MI_T("InstanceWithPathList"), /* name */
    CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_quals, /* qualifiers */
    MI_COUNT(CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_OpenConformantInstances, InstanceWithPathList), /* offset */
};

/* parameter CIM_RegisteredProfile.OpenConformantInstances(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_OpenConformantInstances_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_OpenConformantInstances, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_RegisteredProfile_OpenConformantInstances_params[] =
{
    &CIM_RegisteredProfile_OpenConformantInstances_MIReturn_param,
    &CIM_RegisteredProfile_OpenConformantInstances_ResultClass_param,
    &CIM_RegisteredProfile_OpenConformantInstances_IncludedPropertyList_param,
    &CIM_RegisteredProfile_OpenConformantInstances_OperationTimeout_param,
    &CIM_RegisteredProfile_OpenConformantInstances_ContinueOnError_param,
    &CIM_RegisteredProfile_OpenConformantInstances_MaxObjectCount_param,
    &CIM_RegisteredProfile_OpenConformantInstances_EnumerationContext_param,
    &CIM_RegisteredProfile_OpenConformantInstances_EndOfSequence_param,
    &CIM_RegisteredProfile_OpenConformantInstances_InstanceType_param,
    &CIM_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_param,
};

/* method CIM_RegisteredProfile.OpenConformantInstances() */
MI_CONST MI_MethodDecl CIM_RegisteredProfile_OpenConformantInstances_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006F7317, /* code */
    MI_T("OpenConformantInstances"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    CIM_RegisteredProfile_OpenConformantInstances_params, /* parameters */
    MI_COUNT(CIM_RegisteredProfile_OpenConformantInstances_params), /* numParameters */
    sizeof(CIM_RegisteredProfile_OpenConformantInstances), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_RegisteredProfile"), /* origin */
    MI_T("CIM_RegisteredProfile"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

/* parameter CIM_RegisteredProfile.PullConformantInstances(): MaxObjectCount */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_PullConformantInstances_MaxObjectCount_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006D740E, /* code */
    MI_T("MaxObjectCount"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_PullConformantInstances, MaxObjectCount), /* offset */
};

/* parameter CIM_RegisteredProfile.PullConformantInstances(): EnumerationContext */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_PullConformantInstances_EnumerationContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00657412, /* code */
    MI_T("EnumerationContext"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_PullConformantInstances, EnumerationContext), /* offset */
};

/* parameter CIM_RegisteredProfile.PullConformantInstances(): EndOfSequence */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_PullConformantInstances_EndOfSequence_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0065650D, /* code */
    MI_T("EndOfSequence"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_PullConformantInstances, EndOfSequence), /* offset */
};

static MI_CONST MI_Char* CIM_RegisteredProfile_PullConformantInstances_InstanceType_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_RegisteredProfile_PullConformantInstances_InstanceType_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_RegisteredProfile_PullConformantInstances_InstanceType_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_RegisteredProfile_PullConformantInstances_InstanceType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ProfileRegistration.PullConformantInstances(InstanceWithPathList)"),
};

static MI_CONST MI_ConstStringA CIM_RegisteredProfile_PullConformantInstances_InstanceType_ModelCorrespondence_qual_value =
{
    CIM_RegisteredProfile_PullConformantInstances_InstanceType_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_RegisteredProfile_PullConformantInstances_InstanceType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_RegisteredProfile_PullConformantInstances_InstanceType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_RegisteredProfile_PullConformantInstances_InstanceType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RegisteredProfile_PullConformantInstances_InstanceType_quals[] =
{
    &CIM_RegisteredProfile_PullConformantInstances_InstanceType_ArrayType_qual,
    &CIM_RegisteredProfile_PullConformantInstances_InstanceType_ModelCorrespondence_qual,
};

/* parameter CIM_RegisteredProfile.PullConformantInstances(): InstanceType */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_PullConformantInstances_InstanceType_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0069650C, /* code */
    MI_T("InstanceType"), /* name */
    CIM_RegisteredProfile_PullConformantInstances_InstanceType_quals, /* qualifiers */
    MI_COUNT(CIM_RegisteredProfile_PullConformantInstances_InstanceType_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_PullConformantInstances, InstanceType), /* offset */
};

static MI_CONST MI_Char* CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_EmbeddedInstance_qual_value = MI_T("CIM_ManagedElement");

static MI_CONST MI_Qualifier CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ProfileRegistration.PullConformantInstances(InstanceType)"),
};

static MI_CONST MI_ConstStringA CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_value =
{
    CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_quals[] =
{
    &CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_EmbeddedInstance_qual,
    &CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ArrayType_qual,
    &CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ModelCorrespondence_qual,
};

/* parameter CIM_RegisteredProfile.PullConformantInstances(): InstanceWithPathList */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00697414, /* code */
    MI_T("InstanceWithPathList"), /* name */
    CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_quals, /* qualifiers */
    MI_COUNT(CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_PullConformantInstances, InstanceWithPathList), /* offset */
};

/* parameter CIM_RegisteredProfile.PullConformantInstances(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_RegisteredProfile_PullConformantInstances_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RegisteredProfile_PullConformantInstances, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_RegisteredProfile_PullConformantInstances_params[] =
{
    &CIM_RegisteredProfile_PullConformantInstances_MIReturn_param,
    &CIM_RegisteredProfile_PullConformantInstances_MaxObjectCount_param,
    &CIM_RegisteredProfile_PullConformantInstances_EnumerationContext_param,
    &CIM_RegisteredProfile_PullConformantInstances_EndOfSequence_param,
    &CIM_RegisteredProfile_PullConformantInstances_InstanceType_param,
    &CIM_RegisteredProfile_PullConformantInstances_InstanceWithPathList_param,
};

/* method CIM_RegisteredProfile.PullConformantInstances() */
MI_CONST MI_MethodDecl CIM_RegisteredProfile_PullConformantInstances_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00707317, /* code */
    MI_T("PullConformantInstances"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    CIM_RegisteredProfile_PullConformantInstances_params, /* parameters */
    MI_COUNT(CIM_RegisteredProfile_PullConformantInstances_params), /* numParameters */
    sizeof(CIM_RegisteredProfile_PullConformantInstances), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_RegisteredProfile"), /* origin */
    MI_T("CIM_RegisteredProfile"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_RegisteredProfile_meths[] =
{
    &CIM_RegisteredProfile_CloseConformantInstances_rtti,
    &CIM_RegisteredProfile_OpenConformantInstances_rtti,
    &CIM_RegisteredProfile_PullConformantInstances_rtti,
};

static MI_CONST MI_Char* CIM_RegisteredProfile_UMLPackagePath_qual_value = MI_T("CIM::Interop");

static MI_CONST MI_Qualifier CIM_RegisteredProfile_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_RegisteredProfile_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_RegisteredProfile_Version_qual_value = MI_T("2.27.0");

static MI_CONST MI_Qualifier CIM_RegisteredProfile_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_RegisteredProfile_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RegisteredProfile_quals[] =
{
    &CIM_RegisteredProfile_UMLPackagePath_qual,
    &CIM_RegisteredProfile_Version_qual,
};

/* class CIM_RegisteredProfile */
MI_CONST MI_ClassDecl CIM_RegisteredProfile_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00636515, /* code */
    MI_T("CIM_RegisteredProfile"), /* name */
    CIM_RegisteredProfile_quals, /* qualifiers */
    MI_COUNT(CIM_RegisteredProfile_quals), /* numQualifiers */
    CIM_RegisteredProfile_props, /* properties */
    MI_COUNT(CIM_RegisteredProfile_props), /* numProperties */
    sizeof(CIM_RegisteredProfile), /* size */
    MI_T("CIM_ManagedElement"), /* superClass */
    &CIM_ManagedElement_rtti, /* superClassDecl */
    CIM_RegisteredProfile_meths, /* methods */
    MI_COUNT(CIM_RegisteredProfile_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_ElementConformsToProfile
**
**==============================================================================
*/

/* property CIM_ElementConformsToProfile.ConformantStandard */
static MI_CONST MI_PropertyDecl CIM_ElementConformsToProfile_ConformantStandard_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00636412, /* code */
    MI_T("ConformantStandard"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_RegisteredProfile"), /* className */
    0, /* subscript */
    offsetof(CIM_ElementConformsToProfile, ConformantStandard), /* offset */
    MI_T("CIM_ElementConformsToProfile"), /* origin */
    MI_T("CIM_ElementConformsToProfile"), /* propagator */
    NULL,
};

/* property CIM_ElementConformsToProfile.ManagedElement */
static MI_CONST MI_PropertyDecl CIM_ElementConformsToProfile_ManagedElement_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006D740E, /* code */
    MI_T("ManagedElement"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(CIM_ElementConformsToProfile, ManagedElement), /* offset */
    MI_T("CIM_ElementConformsToProfile"), /* origin */
    MI_T("CIM_ElementConformsToProfile"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_ElementConformsToProfile_props[] =
{
    &CIM_ElementConformsToProfile_ConformantStandard_prop,
    &CIM_ElementConformsToProfile_ManagedElement_prop,
};

static MI_CONST MI_Char* CIM_ElementConformsToProfile_Version_qual_value = MI_T("2.8.0");

static MI_CONST MI_Qualifier CIM_ElementConformsToProfile_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_ElementConformsToProfile_Version_qual_value
};

static MI_CONST MI_Char* CIM_ElementConformsToProfile_UMLPackagePath_qual_value = MI_T("CIM::Interop");

static MI_CONST MI_Qualifier CIM_ElementConformsToProfile_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_ElementConformsToProfile_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ElementConformsToProfile_quals[] =
{
    &CIM_ElementConformsToProfile_Version_qual,
    &CIM_ElementConformsToProfile_UMLPackagePath_qual,
};

/* class CIM_ElementConformsToProfile */
MI_CONST MI_ClassDecl CIM_ElementConformsToProfile_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x0063651C, /* code */
    MI_T("CIM_ElementConformsToProfile"), /* name */
    CIM_ElementConformsToProfile_quals, /* qualifiers */
    MI_COUNT(CIM_ElementConformsToProfile_quals), /* numQualifiers */
    CIM_ElementConformsToProfile_props, /* properties */
    MI_COUNT(CIM_ElementConformsToProfile_props), /* numProperties */
    sizeof(CIM_ElementConformsToProfile), /* size */
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
** ABC_ElementConformsToProfile
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_ElementConformsToProfile_props[] =
{
    &CIM_ElementConformsToProfile_ConformantStandard_prop,
    &CIM_ElementConformsToProfile_ManagedElement_prop,
};

static void MI_CALL ABC_ElementConformsToProfile_AssociatorInstances(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (CIM_RegisteredProfile_IsA(instanceName))
    {
        if (_Match(role, MI_T("ConformantStandard")) && 
            _Match(resultRole, MI_T("ManagedElement")))
        {
            ABC_ElementConformsToProfile_AssociatorInstancesConformantStandard(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_RegisteredProfile*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (CIM_ManagedElement_IsA(instanceName))
    {
        if (_Match(role, MI_T("ManagedElement")) && 
            _Match(resultRole, MI_T("ConformantStandard")))
        {
            ABC_ElementConformsToProfile_AssociatorInstancesManagedElement(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_ManagedElement*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL ABC_ElementConformsToProfile_ReferenceInstances(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (CIM_RegisteredProfile_IsA(instanceName))
    {
        if (_Match(role, MI_T("ConformantStandard")))
        {
            ABC_ElementConformsToProfile_ReferenceInstancesConformantStandard(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_RegisteredProfile*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (CIM_ManagedElement_IsA(instanceName))
    {
        if (_Match(role, MI_T("ManagedElement")))
        {
            ABC_ElementConformsToProfile_ReferenceInstancesManagedElement(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_ManagedElement*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT ABC_ElementConformsToProfile_funcs =
{
  (MI_ProviderFT_Load)ABC_ElementConformsToProfile_Load,
  (MI_ProviderFT_Unload)ABC_ElementConformsToProfile_Unload,
  (MI_ProviderFT_GetInstance)ABC_ElementConformsToProfile_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_ElementConformsToProfile_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_ElementConformsToProfile_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_ElementConformsToProfile_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_ElementConformsToProfile_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)ABC_ElementConformsToProfile_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)ABC_ElementConformsToProfile_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_ElementConformsToProfile_UMLPackagePath_qual_value = MI_T("CIM::Interop");

static MI_CONST MI_Qualifier ABC_ElementConformsToProfile_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_ElementConformsToProfile_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_ElementConformsToProfile_quals[] =
{
    &ABC_ElementConformsToProfile_UMLPackagePath_qual,
};

/* class ABC_ElementConformsToProfile */
MI_CONST MI_ClassDecl ABC_ElementConformsToProfile_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x0061651C, /* code */
    MI_T("ABC_ElementConformsToProfile"), /* name */
    ABC_ElementConformsToProfile_quals, /* qualifiers */
    MI_COUNT(ABC_ElementConformsToProfile_quals), /* numQualifiers */
    ABC_ElementConformsToProfile_props, /* properties */
    MI_COUNT(ABC_ElementConformsToProfile_props), /* numProperties */
    sizeof(ABC_ElementConformsToProfile), /* size */
    MI_T("CIM_ElementConformsToProfile"), /* superClass */
    &CIM_ElementConformsToProfile_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &ABC_ElementConformsToProfile_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ABC_RegisteredProfile
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_RegisteredProfile_props[] =
{
    &CIM_RegisteredProfile_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_RegisteredProfile_RegisteredOrganization_prop,
    &CIM_RegisteredProfile_OtherRegisteredOrganization_prop,
    &CIM_RegisteredProfile_RegisteredName_prop,
    &CIM_RegisteredProfile_RegisteredVersion_prop,
    &CIM_RegisteredProfile_AdvertiseTypes_prop,
    &CIM_RegisteredProfile_AdvertiseTypeDescriptions_prop,
    &CIM_RegisteredProfile_ImplementedFeatures_prop,
};

/* parameter ABC_RegisteredProfile.CloseConformantInstances(): EnumerationContext */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_CloseConformantInstances_EnumerationContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00657412, /* code */
    MI_T("EnumerationContext"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_CloseConformantInstances, EnumerationContext), /* offset */
};

/* parameter ABC_RegisteredProfile.CloseConformantInstances(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_CloseConformantInstances_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_CloseConformantInstances, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_RegisteredProfile_CloseConformantInstances_params[] =
{
    &ABC_RegisteredProfile_CloseConformantInstances_MIReturn_param,
    &ABC_RegisteredProfile_CloseConformantInstances_EnumerationContext_param,
};

/* method ABC_RegisteredProfile.CloseConformantInstances() */
MI_CONST MI_MethodDecl ABC_RegisteredProfile_CloseConformantInstances_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00637318, /* code */
    MI_T("CloseConformantInstances"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_RegisteredProfile_CloseConformantInstances_params, /* parameters */
    MI_COUNT(ABC_RegisteredProfile_CloseConformantInstances_params), /* numParameters */
    sizeof(ABC_RegisteredProfile_CloseConformantInstances), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_RegisteredProfile"), /* origin */
    MI_T("CIM_RegisteredProfile"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_RegisteredProfile_Invoke_CloseConformantInstances, /* method */
};

/* parameter ABC_RegisteredProfile.OpenConformantInstances(): ResultClass */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_OpenConformantInstances_ResultClass_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0072730B, /* code */
    MI_T("ResultClass"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_OpenConformantInstances, ResultClass), /* offset */
};

/* parameter ABC_RegisteredProfile.OpenConformantInstances(): IncludedPropertyList */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_OpenConformantInstances_IncludedPropertyList_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00697414, /* code */
    MI_T("IncludedPropertyList"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_OpenConformantInstances, IncludedPropertyList), /* offset */
};

/* parameter ABC_RegisteredProfile.OpenConformantInstances(): OperationTimeout */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_OpenConformantInstances_OperationTimeout_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006F7410, /* code */
    MI_T("OperationTimeout"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_OpenConformantInstances, OperationTimeout), /* offset */
};

/* parameter ABC_RegisteredProfile.OpenConformantInstances(): ContinueOnError */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_OpenConformantInstances_ContinueOnError_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0063720F, /* code */
    MI_T("ContinueOnError"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_OpenConformantInstances, ContinueOnError), /* offset */
};

/* parameter ABC_RegisteredProfile.OpenConformantInstances(): MaxObjectCount */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_OpenConformantInstances_MaxObjectCount_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006D740E, /* code */
    MI_T("MaxObjectCount"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_OpenConformantInstances, MaxObjectCount), /* offset */
};

/* parameter ABC_RegisteredProfile.OpenConformantInstances(): EnumerationContext */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_OpenConformantInstances_EnumerationContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00657412, /* code */
    MI_T("EnumerationContext"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_OpenConformantInstances, EnumerationContext), /* offset */
};

/* parameter ABC_RegisteredProfile.OpenConformantInstances(): EndOfSequence */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_OpenConformantInstances_EndOfSequence_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0065650D, /* code */
    MI_T("EndOfSequence"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_OpenConformantInstances, EndOfSequence), /* offset */
};

static MI_CONST MI_Char* ABC_RegisteredProfile_OpenConformantInstances_InstanceType_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier ABC_RegisteredProfile_OpenConformantInstances_InstanceType_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &ABC_RegisteredProfile_OpenConformantInstances_InstanceType_ArrayType_qual_value
};

static MI_CONST MI_Char* ABC_RegisteredProfile_OpenConformantInstances_InstanceType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ProfileRegistration.OpenConformantInstances(InstanceWithPathList)"),
};

static MI_CONST MI_ConstStringA ABC_RegisteredProfile_OpenConformantInstances_InstanceType_ModelCorrespondence_qual_value =
{
    ABC_RegisteredProfile_OpenConformantInstances_InstanceType_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_RegisteredProfile_OpenConformantInstances_InstanceType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_RegisteredProfile_OpenConformantInstances_InstanceType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_RegisteredProfile_OpenConformantInstances_InstanceType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_RegisteredProfile_OpenConformantInstances_InstanceType_quals[] =
{
    &ABC_RegisteredProfile_OpenConformantInstances_InstanceType_ArrayType_qual,
    &ABC_RegisteredProfile_OpenConformantInstances_InstanceType_ModelCorrespondence_qual,
};

/* parameter ABC_RegisteredProfile.OpenConformantInstances(): InstanceType */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_OpenConformantInstances_InstanceType_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0069650C, /* code */
    MI_T("InstanceType"), /* name */
    ABC_RegisteredProfile_OpenConformantInstances_InstanceType_quals, /* qualifiers */
    MI_COUNT(ABC_RegisteredProfile_OpenConformantInstances_InstanceType_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_OpenConformantInstances, InstanceType), /* offset */
};

static MI_CONST MI_Char* ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_EmbeddedInstance_qual_value = MI_T("CIM_ManagedElement");

static MI_CONST MI_Qualifier ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ArrayType_qual_value
};

static MI_CONST MI_Char* ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ProfileRegistration.OpenConformantInstances(InstanceType)"),
};

static MI_CONST MI_ConstStringA ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_value =
{
    ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_quals[] =
{
    &ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_EmbeddedInstance_qual,
    &ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ArrayType_qual,
    &ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_ModelCorrespondence_qual,
};

/* parameter ABC_RegisteredProfile.OpenConformantInstances(): InstanceWithPathList */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00697414, /* code */
    MI_T("InstanceWithPathList"), /* name */
    ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_quals, /* qualifiers */
    MI_COUNT(ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_OpenConformantInstances, InstanceWithPathList), /* offset */
};

/* parameter ABC_RegisteredProfile.OpenConformantInstances(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_OpenConformantInstances_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_OpenConformantInstances, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_RegisteredProfile_OpenConformantInstances_params[] =
{
    &ABC_RegisteredProfile_OpenConformantInstances_MIReturn_param,
    &ABC_RegisteredProfile_OpenConformantInstances_ResultClass_param,
    &ABC_RegisteredProfile_OpenConformantInstances_IncludedPropertyList_param,
    &ABC_RegisteredProfile_OpenConformantInstances_OperationTimeout_param,
    &ABC_RegisteredProfile_OpenConformantInstances_ContinueOnError_param,
    &ABC_RegisteredProfile_OpenConformantInstances_MaxObjectCount_param,
    &ABC_RegisteredProfile_OpenConformantInstances_EnumerationContext_param,
    &ABC_RegisteredProfile_OpenConformantInstances_EndOfSequence_param,
    &ABC_RegisteredProfile_OpenConformantInstances_InstanceType_param,
    &ABC_RegisteredProfile_OpenConformantInstances_InstanceWithPathList_param,
};

/* method ABC_RegisteredProfile.OpenConformantInstances() */
MI_CONST MI_MethodDecl ABC_RegisteredProfile_OpenConformantInstances_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006F7317, /* code */
    MI_T("OpenConformantInstances"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_RegisteredProfile_OpenConformantInstances_params, /* parameters */
    MI_COUNT(ABC_RegisteredProfile_OpenConformantInstances_params), /* numParameters */
    sizeof(ABC_RegisteredProfile_OpenConformantInstances), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_RegisteredProfile"), /* origin */
    MI_T("CIM_RegisteredProfile"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_RegisteredProfile_Invoke_OpenConformantInstances, /* method */
};

/* parameter ABC_RegisteredProfile.PullConformantInstances(): MaxObjectCount */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_PullConformantInstances_MaxObjectCount_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006D740E, /* code */
    MI_T("MaxObjectCount"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_PullConformantInstances, MaxObjectCount), /* offset */
};

/* parameter ABC_RegisteredProfile.PullConformantInstances(): EnumerationContext */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_PullConformantInstances_EnumerationContext_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN|MI_FLAG_OUT, /* flags */
    0x00657412, /* code */
    MI_T("EnumerationContext"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_PullConformantInstances, EnumerationContext), /* offset */
};

/* parameter ABC_RegisteredProfile.PullConformantInstances(): EndOfSequence */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_PullConformantInstances_EndOfSequence_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0065650D, /* code */
    MI_T("EndOfSequence"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_PullConformantInstances, EndOfSequence), /* offset */
};

static MI_CONST MI_Char* ABC_RegisteredProfile_PullConformantInstances_InstanceType_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier ABC_RegisteredProfile_PullConformantInstances_InstanceType_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &ABC_RegisteredProfile_PullConformantInstances_InstanceType_ArrayType_qual_value
};

static MI_CONST MI_Char* ABC_RegisteredProfile_PullConformantInstances_InstanceType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ProfileRegistration.PullConformantInstances(InstanceWithPathList)"),
};

static MI_CONST MI_ConstStringA ABC_RegisteredProfile_PullConformantInstances_InstanceType_ModelCorrespondence_qual_value =
{
    ABC_RegisteredProfile_PullConformantInstances_InstanceType_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_RegisteredProfile_PullConformantInstances_InstanceType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_RegisteredProfile_PullConformantInstances_InstanceType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_RegisteredProfile_PullConformantInstances_InstanceType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_RegisteredProfile_PullConformantInstances_InstanceType_quals[] =
{
    &ABC_RegisteredProfile_PullConformantInstances_InstanceType_ArrayType_qual,
    &ABC_RegisteredProfile_PullConformantInstances_InstanceType_ModelCorrespondence_qual,
};

/* parameter ABC_RegisteredProfile.PullConformantInstances(): InstanceType */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_PullConformantInstances_InstanceType_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0069650C, /* code */
    MI_T("InstanceType"), /* name */
    ABC_RegisteredProfile_PullConformantInstances_InstanceType_quals, /* qualifiers */
    MI_COUNT(ABC_RegisteredProfile_PullConformantInstances_InstanceType_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_PullConformantInstances, InstanceType), /* offset */
};

static MI_CONST MI_Char* ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_EmbeddedInstance_qual_value = MI_T("CIM_ManagedElement");

static MI_CONST MI_Qualifier ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_EmbeddedInstance_qual_value
};

static MI_CONST MI_Char* ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ArrayType_qual_value
};

static MI_CONST MI_Char* ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_ProfileRegistration.PullConformantInstances(InstanceType)"),
};

static MI_CONST MI_ConstStringA ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_value =
{
    ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_quals[] =
{
    &ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_EmbeddedInstance_qual,
    &ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ArrayType_qual,
    &ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_ModelCorrespondence_qual,
};

/* parameter ABC_RegisteredProfile.PullConformantInstances(): InstanceWithPathList */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00697414, /* code */
    MI_T("InstanceWithPathList"), /* name */
    ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_quals, /* qualifiers */
    MI_COUNT(ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_PullConformantInstances, InstanceWithPathList), /* offset */
};

/* parameter ABC_RegisteredProfile.PullConformantInstances(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_RegisteredProfile_PullConformantInstances_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_RegisteredProfile_PullConformantInstances, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_RegisteredProfile_PullConformantInstances_params[] =
{
    &ABC_RegisteredProfile_PullConformantInstances_MIReturn_param,
    &ABC_RegisteredProfile_PullConformantInstances_MaxObjectCount_param,
    &ABC_RegisteredProfile_PullConformantInstances_EnumerationContext_param,
    &ABC_RegisteredProfile_PullConformantInstances_EndOfSequence_param,
    &ABC_RegisteredProfile_PullConformantInstances_InstanceType_param,
    &ABC_RegisteredProfile_PullConformantInstances_InstanceWithPathList_param,
};

/* method ABC_RegisteredProfile.PullConformantInstances() */
MI_CONST MI_MethodDecl ABC_RegisteredProfile_PullConformantInstances_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00707317, /* code */
    MI_T("PullConformantInstances"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_RegisteredProfile_PullConformantInstances_params, /* parameters */
    MI_COUNT(ABC_RegisteredProfile_PullConformantInstances_params), /* numParameters */
    sizeof(ABC_RegisteredProfile_PullConformantInstances), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_RegisteredProfile"), /* origin */
    MI_T("CIM_RegisteredProfile"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_RegisteredProfile_Invoke_PullConformantInstances, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST ABC_RegisteredProfile_meths[] =
{
    &ABC_RegisteredProfile_CloseConformantInstances_rtti,
    &ABC_RegisteredProfile_OpenConformantInstances_rtti,
    &ABC_RegisteredProfile_PullConformantInstances_rtti,
};

static MI_CONST MI_ProviderFT ABC_RegisteredProfile_funcs =
{
  (MI_ProviderFT_Load)ABC_RegisteredProfile_Load,
  (MI_ProviderFT_Unload)ABC_RegisteredProfile_Unload,
  (MI_ProviderFT_GetInstance)ABC_RegisteredProfile_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_RegisteredProfile_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_RegisteredProfile_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_RegisteredProfile_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_RegisteredProfile_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_RegisteredProfile_UMLPackagePath_qual_value = MI_T("CIM::Interop");

static MI_CONST MI_Qualifier ABC_RegisteredProfile_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_RegisteredProfile_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_RegisteredProfile_quals[] =
{
    &ABC_RegisteredProfile_UMLPackagePath_qual,
};

/* class ABC_RegisteredProfile */
MI_CONST MI_ClassDecl ABC_RegisteredProfile_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00616515, /* code */
    MI_T("ABC_RegisteredProfile"), /* name */
    ABC_RegisteredProfile_quals, /* qualifiers */
    MI_COUNT(ABC_RegisteredProfile_quals), /* numQualifiers */
    ABC_RegisteredProfile_props, /* properties */
    MI_COUNT(ABC_RegisteredProfile_props), /* numProperties */
    sizeof(ABC_RegisteredProfile), /* size */
    MI_T("CIM_RegisteredProfile"), /* superClass */
    &CIM_RegisteredProfile_rtti, /* superClassDecl */
    ABC_RegisteredProfile_meths, /* methods */
    MI_COUNT(ABC_RegisteredProfile_meths), /* numMethods */
    &schemaDecl, /* schema */
    &ABC_RegisteredProfile_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_PhysicalElement
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_PhysicalElement_Description_Override_qual_value = MI_T("Description");

static MI_CONST MI_Qualifier CIM_PhysicalElement_Description_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_PhysicalElement_Description_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalElement_Description_quals[] =
{
    &CIM_PhysicalElement_Description_Override_qual,
};

/* property CIM_PhysicalElement.Description */
static MI_CONST MI_PropertyDecl CIM_PhysicalElement_Description_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E0B, /* code */
    MI_T("Description"), /* name */
    CIM_PhysicalElement_Description_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalElement_Description_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalElement, Description), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_PhysicalElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_PhysicalElement_ElementName_Override_qual_value = MI_T("ElementName");

static MI_CONST MI_Qualifier CIM_PhysicalElement_ElementName_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_PhysicalElement_ElementName_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalElement_ElementName_quals[] =
{
    &CIM_PhysicalElement_ElementName_Override_qual,
};

/* property CIM_PhysicalElement.ElementName */
static MI_CONST MI_PropertyDecl CIM_PhysicalElement_ElementName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065650B, /* code */
    MI_T("ElementName"), /* name */
    CIM_PhysicalElement_ElementName_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalElement_ElementName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalElement, ElementName), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_PhysicalElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_PhysicalElement_Tag_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_PhysicalElement_Tag_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_PhysicalElement_Tag_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalElement_Tag_quals[] =
{
    &CIM_PhysicalElement_Tag_MaxLen_qual,
};

/* property CIM_PhysicalElement.Tag */
static MI_CONST MI_PropertyDecl CIM_PhysicalElement_Tag_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00746703, /* code */
    MI_T("Tag"), /* name */
    CIM_PhysicalElement_Tag_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalElement_Tag_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalElement, Tag), /* offset */
    MI_T("CIM_PhysicalElement"), /* origin */
    MI_T("CIM_PhysicalElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_PhysicalElement_CreationClassName_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_PhysicalElement_CreationClassName_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_PhysicalElement_CreationClassName_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalElement_CreationClassName_quals[] =
{
    &CIM_PhysicalElement_CreationClassName_MaxLen_qual,
};

/* property CIM_PhysicalElement.CreationClassName */
static MI_CONST MI_PropertyDecl CIM_PhysicalElement_CreationClassName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00636511, /* code */
    MI_T("CreationClassName"), /* name */
    CIM_PhysicalElement_CreationClassName_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalElement_CreationClassName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalElement, CreationClassName), /* offset */
    MI_T("CIM_PhysicalElement"), /* origin */
    MI_T("CIM_PhysicalElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_PhysicalElement_Manufacturer_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_PhysicalElement_Manufacturer_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_PhysicalElement_Manufacturer_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalElement_Manufacturer_quals[] =
{
    &CIM_PhysicalElement_Manufacturer_MaxLen_qual,
};

/* property CIM_PhysicalElement.Manufacturer */
static MI_CONST MI_PropertyDecl CIM_PhysicalElement_Manufacturer_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D720C, /* code */
    MI_T("Manufacturer"), /* name */
    CIM_PhysicalElement_Manufacturer_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalElement_Manufacturer_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalElement, Manufacturer), /* offset */
    MI_T("CIM_PhysicalElement"), /* origin */
    MI_T("CIM_PhysicalElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_PhysicalElement_Model_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_PhysicalElement_Model_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_PhysicalElement_Model_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalElement_Model_quals[] =
{
    &CIM_PhysicalElement_Model_MaxLen_qual,
};

/* property CIM_PhysicalElement.Model */
static MI_CONST MI_PropertyDecl CIM_PhysicalElement_Model_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D6C05, /* code */
    MI_T("Model"), /* name */
    CIM_PhysicalElement_Model_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalElement_Model_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalElement, Model), /* offset */
    MI_T("CIM_PhysicalElement"), /* origin */
    MI_T("CIM_PhysicalElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_PhysicalElement_SKU_MaxLen_qual_value = 64U;

static MI_CONST MI_Qualifier CIM_PhysicalElement_SKU_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_PhysicalElement_SKU_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalElement_SKU_quals[] =
{
    &CIM_PhysicalElement_SKU_MaxLen_qual,
};

/* property CIM_PhysicalElement.SKU */
static MI_CONST MI_PropertyDecl CIM_PhysicalElement_SKU_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737503, /* code */
    MI_T("SKU"), /* name */
    CIM_PhysicalElement_SKU_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalElement_SKU_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalElement, SKU), /* offset */
    MI_T("CIM_PhysicalElement"), /* origin */
    MI_T("CIM_PhysicalElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_PhysicalElement_SerialNumber_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_PhysicalElement_SerialNumber_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_PhysicalElement_SerialNumber_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalElement_SerialNumber_quals[] =
{
    &CIM_PhysicalElement_SerialNumber_MaxLen_qual,
};

/* property CIM_PhysicalElement.SerialNumber */
static MI_CONST MI_PropertyDecl CIM_PhysicalElement_SerialNumber_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073720C, /* code */
    MI_T("SerialNumber"), /* name */
    CIM_PhysicalElement_SerialNumber_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalElement_SerialNumber_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalElement, SerialNumber), /* offset */
    MI_T("CIM_PhysicalElement"), /* origin */
    MI_T("CIM_PhysicalElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_PhysicalElement_Version_MaxLen_qual_value = 64U;

static MI_CONST MI_Qualifier CIM_PhysicalElement_Version_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_PhysicalElement_Version_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalElement_Version_quals[] =
{
    &CIM_PhysicalElement_Version_MaxLen_qual,
};

/* property CIM_PhysicalElement.Version */
static MI_CONST MI_PropertyDecl CIM_PhysicalElement_Version_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00766E07, /* code */
    MI_T("Version"), /* name */
    CIM_PhysicalElement_Version_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalElement_Version_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalElement, Version), /* offset */
    MI_T("CIM_PhysicalElement"), /* origin */
    MI_T("CIM_PhysicalElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_PhysicalElement_PartNumber_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_PhysicalElement_PartNumber_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_PhysicalElement_PartNumber_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalElement_PartNumber_quals[] =
{
    &CIM_PhysicalElement_PartNumber_MaxLen_qual,
};

/* property CIM_PhysicalElement.PartNumber */
static MI_CONST MI_PropertyDecl CIM_PhysicalElement_PartNumber_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070720A, /* code */
    MI_T("PartNumber"), /* name */
    CIM_PhysicalElement_PartNumber_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalElement_PartNumber_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalElement, PartNumber), /* offset */
    MI_T("CIM_PhysicalElement"), /* origin */
    MI_T("CIM_PhysicalElement"), /* propagator */
    NULL,
};

/* property CIM_PhysicalElement.OtherIdentifyingInfo */
static MI_CONST MI_PropertyDecl CIM_PhysicalElement_OtherIdentifyingInfo_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6F14, /* code */
    MI_T("OtherIdentifyingInfo"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalElement, OtherIdentifyingInfo), /* offset */
    MI_T("CIM_PhysicalElement"), /* origin */
    MI_T("CIM_PhysicalElement"), /* propagator */
    NULL,
};

/* property CIM_PhysicalElement.PoweredOn */
static MI_CONST MI_PropertyDecl CIM_PhysicalElement_PoweredOn_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706E09, /* code */
    MI_T("PoweredOn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalElement, PoweredOn), /* offset */
    MI_T("CIM_PhysicalElement"), /* origin */
    MI_T("CIM_PhysicalElement"), /* propagator */
    NULL,
};

/* property CIM_PhysicalElement.ManufactureDate */
static MI_CONST MI_PropertyDecl CIM_PhysicalElement_ManufactureDate_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D650F, /* code */
    MI_T("ManufactureDate"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalElement, ManufactureDate), /* offset */
    MI_T("CIM_PhysicalElement"), /* origin */
    MI_T("CIM_PhysicalElement"), /* propagator */
    NULL,
};

/* property CIM_PhysicalElement.VendorEquipmentType */
static MI_CONST MI_PropertyDecl CIM_PhysicalElement_VendorEquipmentType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00766513, /* code */
    MI_T("VendorEquipmentType"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalElement, VendorEquipmentType), /* offset */
    MI_T("CIM_PhysicalElement"), /* origin */
    MI_T("CIM_PhysicalElement"), /* propagator */
    NULL,
};

/* property CIM_PhysicalElement.UserTracking */
static MI_CONST MI_PropertyDecl CIM_PhysicalElement_UserTracking_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075670C, /* code */
    MI_T("UserTracking"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalElement, UserTracking), /* offset */
    MI_T("CIM_PhysicalElement"), /* origin */
    MI_T("CIM_PhysicalElement"), /* propagator */
    NULL,
};

/* property CIM_PhysicalElement.CanBeFRUed */
static MI_CONST MI_PropertyDecl CIM_PhysicalElement_CanBeFRUed_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063640A, /* code */
    MI_T("CanBeFRUed"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalElement, CanBeFRUed), /* offset */
    MI_T("CIM_PhysicalElement"), /* origin */
    MI_T("CIM_PhysicalElement"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_PhysicalElement_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_PhysicalElement_Description_prop,
    &CIM_PhysicalElement_ElementName_prop,
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
    &CIM_PhysicalElement_Tag_prop,
    &CIM_PhysicalElement_CreationClassName_prop,
    &CIM_PhysicalElement_Manufacturer_prop,
    &CIM_PhysicalElement_Model_prop,
    &CIM_PhysicalElement_SKU_prop,
    &CIM_PhysicalElement_SerialNumber_prop,
    &CIM_PhysicalElement_Version_prop,
    &CIM_PhysicalElement_PartNumber_prop,
    &CIM_PhysicalElement_OtherIdentifyingInfo_prop,
    &CIM_PhysicalElement_PoweredOn_prop,
    &CIM_PhysicalElement_ManufactureDate_prop,
    &CIM_PhysicalElement_VendorEquipmentType_prop,
    &CIM_PhysicalElement_UserTracking_prop,
    &CIM_PhysicalElement_CanBeFRUed_prop,
};

static MI_CONST MI_Char* CIM_PhysicalElement_UMLPackagePath_qual_value = MI_T("CIM::Core::Physical");

static MI_CONST MI_Qualifier CIM_PhysicalElement_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_PhysicalElement_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_PhysicalElement_Version_qual_value = MI_T("2.10.0");

static MI_CONST MI_Qualifier CIM_PhysicalElement_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_PhysicalElement_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalElement_quals[] =
{
    &CIM_PhysicalElement_UMLPackagePath_qual,
    &CIM_PhysicalElement_Version_qual,
};

/* class CIM_PhysicalElement */
MI_CONST MI_ClassDecl CIM_PhysicalElement_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00637413, /* code */
    MI_T("CIM_PhysicalElement"), /* name */
    CIM_PhysicalElement_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalElement_quals), /* numQualifiers */
    CIM_PhysicalElement_props, /* properties */
    MI_COUNT(CIM_PhysicalElement_props), /* numProperties */
    sizeof(CIM_PhysicalElement), /* size */
    MI_T("CIM_ManagedSystemElement"), /* superClass */
    &CIM_ManagedSystemElement_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_Realizes
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_Realizes_Antecedent_Override_qual_value = MI_T("Antecedent");

static MI_CONST MI_Qualifier CIM_Realizes_Antecedent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_Realizes_Antecedent_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Realizes_Antecedent_quals[] =
{
    &CIM_Realizes_Antecedent_Override_qual,
};

/* property CIM_Realizes.Antecedent */
static MI_CONST MI_PropertyDecl CIM_Realizes_Antecedent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0061740A, /* code */
    MI_T("Antecedent"), /* name */
    CIM_Realizes_Antecedent_quals, /* qualifiers */
    MI_COUNT(CIM_Realizes_Antecedent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_PhysicalElement"), /* className */
    0, /* subscript */
    offsetof(CIM_Realizes, Antecedent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("CIM_Realizes"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Realizes_Dependent_Override_qual_value = MI_T("Dependent");

static MI_CONST MI_Qualifier CIM_Realizes_Dependent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_Realizes_Dependent_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Realizes_Dependent_quals[] =
{
    &CIM_Realizes_Dependent_Override_qual,
};

/* property CIM_Realizes.Dependent */
static MI_CONST MI_PropertyDecl CIM_Realizes_Dependent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00647409, /* code */
    MI_T("Dependent"), /* name */
    CIM_Realizes_Dependent_quals, /* qualifiers */
    MI_COUNT(CIM_Realizes_Dependent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_LogicalDevice"), /* className */
    0, /* subscript */
    offsetof(CIM_Realizes, Dependent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("CIM_Realizes"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Realizes_props[] =
{
    &CIM_Realizes_Antecedent_prop,
    &CIM_Realizes_Dependent_prop,
};

static MI_CONST MI_Char* CIM_Realizes_UMLPackagePath_qual_value = MI_T("CIM::Core::Device");

static MI_CONST MI_Qualifier CIM_Realizes_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Realizes_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_Realizes_Version_qual_value = MI_T("2.6.0");

static MI_CONST MI_Qualifier CIM_Realizes_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Realizes_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Realizes_quals[] =
{
    &CIM_Realizes_UMLPackagePath_qual,
    &CIM_Realizes_Version_qual,
};

/* class CIM_Realizes */
MI_CONST MI_ClassDecl CIM_Realizes_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x0063730C, /* code */
    MI_T("CIM_Realizes"), /* name */
    CIM_Realizes_quals, /* qualifiers */
    MI_COUNT(CIM_Realizes_quals), /* numQualifiers */
    CIM_Realizes_props, /* properties */
    MI_COUNT(CIM_Realizes_props), /* numProperties */
    sizeof(CIM_Realizes), /* size */
    MI_T("CIM_Dependency"), /* superClass */
    &CIM_Dependency_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ABC_Realizes
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_Realizes_props[] =
{
    &CIM_Realizes_Antecedent_prop,
    &CIM_Realizes_Dependent_prop,
};

static void MI_CALL ABC_Realizes_AssociatorInstances(
    ABC_Realizes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (CIM_PhysicalElement_IsA(instanceName))
    {
        if (_Match(role, MI_T("Antecedent")) && 
            _Match(resultRole, MI_T("Dependent")))
        {
            ABC_Realizes_AssociatorInstancesAntecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_PhysicalElement*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (CIM_LogicalDevice_IsA(instanceName))
    {
        if (_Match(role, MI_T("Dependent")) && 
            _Match(resultRole, MI_T("Antecedent")))
        {
            ABC_Realizes_AssociatorInstancesDependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_LogicalDevice*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL ABC_Realizes_ReferenceInstances(
    ABC_Realizes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (CIM_PhysicalElement_IsA(instanceName))
    {
        if (_Match(role, MI_T("Antecedent")))
        {
            ABC_Realizes_ReferenceInstancesAntecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_PhysicalElement*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (CIM_LogicalDevice_IsA(instanceName))
    {
        if (_Match(role, MI_T("Dependent")))
        {
            ABC_Realizes_ReferenceInstancesDependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_LogicalDevice*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT ABC_Realizes_funcs =
{
  (MI_ProviderFT_Load)ABC_Realizes_Load,
  (MI_ProviderFT_Unload)ABC_Realizes_Unload,
  (MI_ProviderFT_GetInstance)ABC_Realizes_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_Realizes_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_Realizes_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_Realizes_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_Realizes_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)ABC_Realizes_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)ABC_Realizes_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_Realizes_UMLPackagePath_qual_value = MI_T("CIM::Core::Device");

static MI_CONST MI_Qualifier ABC_Realizes_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_Realizes_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Realizes_quals[] =
{
    &ABC_Realizes_UMLPackagePath_qual,
};

/* class ABC_Realizes */
MI_CONST MI_ClassDecl ABC_Realizes_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x0061730C, /* code */
    MI_T("ABC_Realizes"), /* name */
    ABC_Realizes_quals, /* qualifiers */
    MI_COUNT(ABC_Realizes_quals), /* numQualifiers */
    ABC_Realizes_props, /* properties */
    MI_COUNT(ABC_Realizes_props), /* numProperties */
    sizeof(ABC_Realizes), /* size */
    MI_T("CIM_Realizes"), /* superClass */
    &CIM_Realizes_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &ABC_Realizes_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_PhysicalPackage
**
**==============================================================================
*/

static MI_CONST MI_Uint16 CIM_PhysicalPackage_RemovalConditions_value = 2;

/* property CIM_PhysicalPackage.RemovalConditions */
static MI_CONST MI_PropertyDecl CIM_PhysicalPackage_RemovalConditions_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00727311, /* code */
    MI_T("RemovalConditions"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalPackage, RemovalConditions), /* offset */
    MI_T("CIM_PhysicalPackage"), /* origin */
    MI_T("CIM_PhysicalPackage"), /* propagator */
    &CIM_PhysicalPackage_RemovalConditions_value,
};

static MI_CONST MI_Char* CIM_PhysicalPackage_Removable_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PhysicalPackage.RemovalConditions"),
};

static MI_CONST MI_ConstStringA CIM_PhysicalPackage_Removable_Deprecated_qual_value =
{
    CIM_PhysicalPackage_Removable_Deprecated_qual_data_value,
    MI_COUNT(CIM_PhysicalPackage_Removable_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_PhysicalPackage_Removable_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_PhysicalPackage_Removable_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalPackage_Removable_quals[] =
{
    &CIM_PhysicalPackage_Removable_Deprecated_qual,
};

/* property CIM_PhysicalPackage.Removable */
static MI_CONST MI_PropertyDecl CIM_PhysicalPackage_Removable_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726509, /* code */
    MI_T("Removable"), /* name */
    CIM_PhysicalPackage_Removable_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalPackage_Removable_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalPackage, Removable), /* offset */
    MI_T("CIM_PhysicalPackage"), /* origin */
    MI_T("CIM_PhysicalPackage"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_PhysicalPackage_Replaceable_Deprecated_qual_data_value[] =
{
    MI_T("No value"),
};

static MI_CONST MI_ConstStringA CIM_PhysicalPackage_Replaceable_Deprecated_qual_value =
{
    CIM_PhysicalPackage_Replaceable_Deprecated_qual_data_value,
    MI_COUNT(CIM_PhysicalPackage_Replaceable_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_PhysicalPackage_Replaceable_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_PhysicalPackage_Replaceable_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalPackage_Replaceable_quals[] =
{
    &CIM_PhysicalPackage_Replaceable_Deprecated_qual,
};

/* property CIM_PhysicalPackage.Replaceable */
static MI_CONST MI_PropertyDecl CIM_PhysicalPackage_Replaceable_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072650B, /* code */
    MI_T("Replaceable"), /* name */
    CIM_PhysicalPackage_Replaceable_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalPackage_Replaceable_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalPackage, Replaceable), /* offset */
    MI_T("CIM_PhysicalPackage"), /* origin */
    MI_T("CIM_PhysicalPackage"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_PhysicalPackage_HotSwappable_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PhysicalPackage.RemovalConditions"),
};

static MI_CONST MI_ConstStringA CIM_PhysicalPackage_HotSwappable_Deprecated_qual_value =
{
    CIM_PhysicalPackage_HotSwappable_Deprecated_qual_data_value,
    MI_COUNT(CIM_PhysicalPackage_HotSwappable_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_PhysicalPackage_HotSwappable_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_PhysicalPackage_HotSwappable_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalPackage_HotSwappable_quals[] =
{
    &CIM_PhysicalPackage_HotSwappable_Deprecated_qual,
};

/* property CIM_PhysicalPackage.HotSwappable */
static MI_CONST MI_PropertyDecl CIM_PhysicalPackage_HotSwappable_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0068650C, /* code */
    MI_T("HotSwappable"), /* name */
    CIM_PhysicalPackage_HotSwappable_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalPackage_HotSwappable_quals), /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalPackage, HotSwappable), /* offset */
    MI_T("CIM_PhysicalPackage"), /* origin */
    MI_T("CIM_PhysicalPackage"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_PhysicalPackage_Height_Units_qual_value = MI_T("Inches");

static MI_CONST MI_Qualifier CIM_PhysicalPackage_Height_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_PhysicalPackage_Height_Units_qual_value
};

static MI_CONST MI_Char* CIM_PhysicalPackage_Height_PUnit_qual_value = MI_T("inch");

static MI_CONST MI_Qualifier CIM_PhysicalPackage_Height_PUnit_qual =
{
    MI_T("PUnit"),
    MI_STRING,
    0,
    &CIM_PhysicalPackage_Height_PUnit_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalPackage_Height_quals[] =
{
    &CIM_PhysicalPackage_Height_Units_qual,
    &CIM_PhysicalPackage_Height_PUnit_qual,
};

/* property CIM_PhysicalPackage.Height */
static MI_CONST MI_PropertyDecl CIM_PhysicalPackage_Height_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00687406, /* code */
    MI_T("Height"), /* name */
    CIM_PhysicalPackage_Height_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalPackage_Height_quals), /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalPackage, Height), /* offset */
    MI_T("CIM_PhysicalPackage"), /* origin */
    MI_T("CIM_PhysicalPackage"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_PhysicalPackage_Depth_Units_qual_value = MI_T("Inches");

static MI_CONST MI_Qualifier CIM_PhysicalPackage_Depth_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_PhysicalPackage_Depth_Units_qual_value
};

static MI_CONST MI_Char* CIM_PhysicalPackage_Depth_PUnit_qual_value = MI_T("inch");

static MI_CONST MI_Qualifier CIM_PhysicalPackage_Depth_PUnit_qual =
{
    MI_T("PUnit"),
    MI_STRING,
    0,
    &CIM_PhysicalPackage_Depth_PUnit_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalPackage_Depth_quals[] =
{
    &CIM_PhysicalPackage_Depth_Units_qual,
    &CIM_PhysicalPackage_Depth_PUnit_qual,
};

/* property CIM_PhysicalPackage.Depth */
static MI_CONST MI_PropertyDecl CIM_PhysicalPackage_Depth_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646805, /* code */
    MI_T("Depth"), /* name */
    CIM_PhysicalPackage_Depth_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalPackage_Depth_quals), /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalPackage, Depth), /* offset */
    MI_T("CIM_PhysicalPackage"), /* origin */
    MI_T("CIM_PhysicalPackage"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_PhysicalPackage_Width_Units_qual_value = MI_T("Inches");

static MI_CONST MI_Qualifier CIM_PhysicalPackage_Width_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_PhysicalPackage_Width_Units_qual_value
};

static MI_CONST MI_Char* CIM_PhysicalPackage_Width_PUnit_qual_value = MI_T("inch");

static MI_CONST MI_Qualifier CIM_PhysicalPackage_Width_PUnit_qual =
{
    MI_T("PUnit"),
    MI_STRING,
    0,
    &CIM_PhysicalPackage_Width_PUnit_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalPackage_Width_quals[] =
{
    &CIM_PhysicalPackage_Width_Units_qual,
    &CIM_PhysicalPackage_Width_PUnit_qual,
};

/* property CIM_PhysicalPackage.Width */
static MI_CONST MI_PropertyDecl CIM_PhysicalPackage_Width_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00776805, /* code */
    MI_T("Width"), /* name */
    CIM_PhysicalPackage_Width_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalPackage_Width_quals), /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalPackage, Width), /* offset */
    MI_T("CIM_PhysicalPackage"), /* origin */
    MI_T("CIM_PhysicalPackage"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_PhysicalPackage_Weight_Units_qual_value = MI_T("Pounds");

static MI_CONST MI_Qualifier CIM_PhysicalPackage_Weight_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_PhysicalPackage_Weight_Units_qual_value
};

static MI_CONST MI_Char* CIM_PhysicalPackage_Weight_PUnit_qual_value = MI_T("pound");

static MI_CONST MI_Qualifier CIM_PhysicalPackage_Weight_PUnit_qual =
{
    MI_T("PUnit"),
    MI_STRING,
    0,
    &CIM_PhysicalPackage_Weight_PUnit_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalPackage_Weight_quals[] =
{
    &CIM_PhysicalPackage_Weight_Units_qual,
    &CIM_PhysicalPackage_Weight_PUnit_qual,
};

/* property CIM_PhysicalPackage.Weight */
static MI_CONST MI_PropertyDecl CIM_PhysicalPackage_Weight_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00777406, /* code */
    MI_T("Weight"), /* name */
    CIM_PhysicalPackage_Weight_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalPackage_Weight_quals), /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalPackage, Weight), /* offset */
    MI_T("CIM_PhysicalPackage"), /* origin */
    MI_T("CIM_PhysicalPackage"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_PhysicalPackage_PackageType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_PhysicalPackage.OtherPackageType"),
};

static MI_CONST MI_ConstStringA CIM_PhysicalPackage_PackageType_ModelCorrespondence_qual_value =
{
    CIM_PhysicalPackage_PackageType_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_PhysicalPackage_PackageType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_PhysicalPackage_PackageType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_PhysicalPackage_PackageType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalPackage_PackageType_quals[] =
{
    &CIM_PhysicalPackage_PackageType_ModelCorrespondence_qual,
};

/* property CIM_PhysicalPackage.PackageType */
static MI_CONST MI_PropertyDecl CIM_PhysicalPackage_PackageType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070650B, /* code */
    MI_T("PackageType"), /* name */
    CIM_PhysicalPackage_PackageType_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalPackage_PackageType_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalPackage, PackageType), /* offset */
    MI_T("CIM_PhysicalPackage"), /* origin */
    MI_T("CIM_PhysicalPackage"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_PhysicalPackage_OtherPackageType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_PhysicalPackage.PackageType"),
};

static MI_CONST MI_ConstStringA CIM_PhysicalPackage_OtherPackageType_ModelCorrespondence_qual_value =
{
    CIM_PhysicalPackage_OtherPackageType_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_PhysicalPackage_OtherPackageType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_PhysicalPackage_OtherPackageType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_PhysicalPackage_OtherPackageType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalPackage_OtherPackageType_quals[] =
{
    &CIM_PhysicalPackage_OtherPackageType_ModelCorrespondence_qual,
};

/* property CIM_PhysicalPackage.OtherPackageType */
static MI_CONST MI_PropertyDecl CIM_PhysicalPackage_OtherPackageType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6510, /* code */
    MI_T("OtherPackageType"), /* name */
    CIM_PhysicalPackage_OtherPackageType_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalPackage_OtherPackageType_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalPackage, OtherPackageType), /* offset */
    MI_T("CIM_PhysicalPackage"), /* origin */
    MI_T("CIM_PhysicalPackage"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_PhysicalPackage_VendorCompatibilityStrings_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Slot.VendorCompatibilityStrings"),
};

static MI_CONST MI_ConstStringA CIM_PhysicalPackage_VendorCompatibilityStrings_ModelCorrespondence_qual_value =
{
    CIM_PhysicalPackage_VendorCompatibilityStrings_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_PhysicalPackage_VendorCompatibilityStrings_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_PhysicalPackage_VendorCompatibilityStrings_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_PhysicalPackage_VendorCompatibilityStrings_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalPackage_VendorCompatibilityStrings_quals[] =
{
    &CIM_PhysicalPackage_VendorCompatibilityStrings_ModelCorrespondence_qual,
};

/* property CIM_PhysicalPackage.VendorCompatibilityStrings */
static MI_CONST MI_PropertyDecl CIM_PhysicalPackage_VendorCompatibilityStrings_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0076731A, /* code */
    MI_T("VendorCompatibilityStrings"), /* name */
    CIM_PhysicalPackage_VendorCompatibilityStrings_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalPackage_VendorCompatibilityStrings_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalPackage, VendorCompatibilityStrings), /* offset */
    MI_T("CIM_PhysicalPackage"), /* origin */
    MI_T("CIM_PhysicalPackage"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_PhysicalPackage_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_PhysicalElement_Description_prop,
    &CIM_PhysicalElement_ElementName_prop,
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
    &CIM_PhysicalElement_Tag_prop,
    &CIM_PhysicalElement_CreationClassName_prop,
    &CIM_PhysicalElement_Manufacturer_prop,
    &CIM_PhysicalElement_Model_prop,
    &CIM_PhysicalElement_SKU_prop,
    &CIM_PhysicalElement_SerialNumber_prop,
    &CIM_PhysicalElement_Version_prop,
    &CIM_PhysicalElement_PartNumber_prop,
    &CIM_PhysicalElement_OtherIdentifyingInfo_prop,
    &CIM_PhysicalElement_PoweredOn_prop,
    &CIM_PhysicalElement_ManufactureDate_prop,
    &CIM_PhysicalElement_VendorEquipmentType_prop,
    &CIM_PhysicalElement_UserTracking_prop,
    &CIM_PhysicalElement_CanBeFRUed_prop,
    &CIM_PhysicalPackage_RemovalConditions_prop,
    &CIM_PhysicalPackage_Removable_prop,
    &CIM_PhysicalPackage_Replaceable_prop,
    &CIM_PhysicalPackage_HotSwappable_prop,
    &CIM_PhysicalPackage_Height_prop,
    &CIM_PhysicalPackage_Depth_prop,
    &CIM_PhysicalPackage_Width_prop,
    &CIM_PhysicalPackage_Weight_prop,
    &CIM_PhysicalPackage_PackageType_prop,
    &CIM_PhysicalPackage_OtherPackageType_prop,
    &CIM_PhysicalPackage_VendorCompatibilityStrings_prop,
};

static MI_CONST MI_Char* CIM_PhysicalPackage_IsCompatible_Deprecated_qual_data_value[] =
{
    MI_T("No value"),
};

static MI_CONST MI_ConstStringA CIM_PhysicalPackage_IsCompatible_Deprecated_qual_value =
{
    CIM_PhysicalPackage_IsCompatible_Deprecated_qual_data_value,
    MI_COUNT(CIM_PhysicalPackage_IsCompatible_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_PhysicalPackage_IsCompatible_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_PhysicalPackage_IsCompatible_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalPackage_IsCompatible_quals[] =
{
    &CIM_PhysicalPackage_IsCompatible_Deprecated_qual,
};

/* parameter CIM_PhysicalPackage.IsCompatible(): ElementToCheck */
static MI_CONST MI_ParameterDecl CIM_PhysicalPackage_IsCompatible_ElementToCheck_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00656B0E, /* code */
    MI_T("ElementToCheck"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_PhysicalElement"), /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalPackage_IsCompatible, ElementToCheck), /* offset */
};

static MI_CONST MI_Char* CIM_PhysicalPackage_IsCompatible_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("No value"),
};

static MI_CONST MI_ConstStringA CIM_PhysicalPackage_IsCompatible_MIReturn_Deprecated_qual_value =
{
    CIM_PhysicalPackage_IsCompatible_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(CIM_PhysicalPackage_IsCompatible_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_PhysicalPackage_IsCompatible_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_PhysicalPackage_IsCompatible_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalPackage_IsCompatible_MIReturn_quals[] =
{
    &CIM_PhysicalPackage_IsCompatible_MIReturn_Deprecated_qual,
};

/* parameter CIM_PhysicalPackage.IsCompatible(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_PhysicalPackage_IsCompatible_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    CIM_PhysicalPackage_IsCompatible_MIReturn_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalPackage_IsCompatible_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_PhysicalPackage_IsCompatible, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_PhysicalPackage_IsCompatible_params[] =
{
    &CIM_PhysicalPackage_IsCompatible_MIReturn_param,
    &CIM_PhysicalPackage_IsCompatible_ElementToCheck_param,
};

/* method CIM_PhysicalPackage.IsCompatible() */
MI_CONST MI_MethodDecl CIM_PhysicalPackage_IsCompatible_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0069650C, /* code */
    MI_T("IsCompatible"), /* name */
    CIM_PhysicalPackage_IsCompatible_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalPackage_IsCompatible_quals), /* numQualifiers */
    CIM_PhysicalPackage_IsCompatible_params, /* parameters */
    MI_COUNT(CIM_PhysicalPackage_IsCompatible_params), /* numParameters */
    sizeof(CIM_PhysicalPackage_IsCompatible), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_PhysicalPackage"), /* origin */
    MI_T("CIM_PhysicalPackage"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_PhysicalPackage_meths[] =
{
    &CIM_PhysicalPackage_IsCompatible_rtti,
};

static MI_CONST MI_Char* CIM_PhysicalPackage_UMLPackagePath_qual_value = MI_T("CIM::Physical::Package");

static MI_CONST MI_Qualifier CIM_PhysicalPackage_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_PhysicalPackage_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_PhysicalPackage_Version_qual_value = MI_T("2.18.0");

static MI_CONST MI_Qualifier CIM_PhysicalPackage_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_PhysicalPackage_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_PhysicalPackage_quals[] =
{
    &CIM_PhysicalPackage_UMLPackagePath_qual,
    &CIM_PhysicalPackage_Version_qual,
};

/* class CIM_PhysicalPackage */
MI_CONST MI_ClassDecl CIM_PhysicalPackage_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00636513, /* code */
    MI_T("CIM_PhysicalPackage"), /* name */
    CIM_PhysicalPackage_quals, /* qualifiers */
    MI_COUNT(CIM_PhysicalPackage_quals), /* numQualifiers */
    CIM_PhysicalPackage_props, /* properties */
    MI_COUNT(CIM_PhysicalPackage_props), /* numProperties */
    sizeof(CIM_PhysicalPackage), /* size */
    MI_T("CIM_PhysicalElement"), /* superClass */
    &CIM_PhysicalElement_rtti, /* superClassDecl */
    CIM_PhysicalPackage_meths, /* methods */
    MI_COUNT(CIM_PhysicalPackage_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ABC_PhysicalPackage
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_PhysicalPackage_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_PhysicalElement_Description_prop,
    &CIM_PhysicalElement_ElementName_prop,
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
    &CIM_PhysicalElement_Tag_prop,
    &CIM_PhysicalElement_CreationClassName_prop,
    &CIM_PhysicalElement_Manufacturer_prop,
    &CIM_PhysicalElement_Model_prop,
    &CIM_PhysicalElement_SKU_prop,
    &CIM_PhysicalElement_SerialNumber_prop,
    &CIM_PhysicalElement_Version_prop,
    &CIM_PhysicalElement_PartNumber_prop,
    &CIM_PhysicalElement_OtherIdentifyingInfo_prop,
    &CIM_PhysicalElement_PoweredOn_prop,
    &CIM_PhysicalElement_ManufactureDate_prop,
    &CIM_PhysicalElement_VendorEquipmentType_prop,
    &CIM_PhysicalElement_UserTracking_prop,
    &CIM_PhysicalElement_CanBeFRUed_prop,
    &CIM_PhysicalPackage_RemovalConditions_prop,
    &CIM_PhysicalPackage_Removable_prop,
    &CIM_PhysicalPackage_Replaceable_prop,
    &CIM_PhysicalPackage_HotSwappable_prop,
    &CIM_PhysicalPackage_Height_prop,
    &CIM_PhysicalPackage_Depth_prop,
    &CIM_PhysicalPackage_Width_prop,
    &CIM_PhysicalPackage_Weight_prop,
    &CIM_PhysicalPackage_PackageType_prop,
    &CIM_PhysicalPackage_OtherPackageType_prop,
    &CIM_PhysicalPackage_VendorCompatibilityStrings_prop,
};

static MI_CONST MI_Char* ABC_PhysicalPackage_IsCompatible_Deprecated_qual_data_value[] =
{
    MI_T("No value"),
};

static MI_CONST MI_ConstStringA ABC_PhysicalPackage_IsCompatible_Deprecated_qual_value =
{
    ABC_PhysicalPackage_IsCompatible_Deprecated_qual_data_value,
    MI_COUNT(ABC_PhysicalPackage_IsCompatible_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_PhysicalPackage_IsCompatible_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_PhysicalPackage_IsCompatible_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_PhysicalPackage_IsCompatible_quals[] =
{
    &ABC_PhysicalPackage_IsCompatible_Deprecated_qual,
};

/* parameter ABC_PhysicalPackage.IsCompatible(): ElementToCheck */
static MI_CONST MI_ParameterDecl ABC_PhysicalPackage_IsCompatible_ElementToCheck_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00656B0E, /* code */
    MI_T("ElementToCheck"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_PhysicalElement"), /* className */
    0, /* subscript */
    offsetof(ABC_PhysicalPackage_IsCompatible, ElementToCheck), /* offset */
};

static MI_CONST MI_Char* ABC_PhysicalPackage_IsCompatible_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("No value"),
};

static MI_CONST MI_ConstStringA ABC_PhysicalPackage_IsCompatible_MIReturn_Deprecated_qual_value =
{
    ABC_PhysicalPackage_IsCompatible_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_PhysicalPackage_IsCompatible_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_PhysicalPackage_IsCompatible_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_PhysicalPackage_IsCompatible_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_PhysicalPackage_IsCompatible_MIReturn_quals[] =
{
    &ABC_PhysicalPackage_IsCompatible_MIReturn_Deprecated_qual,
};

/* parameter ABC_PhysicalPackage.IsCompatible(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_PhysicalPackage_IsCompatible_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_PhysicalPackage_IsCompatible_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_PhysicalPackage_IsCompatible_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_PhysicalPackage_IsCompatible, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_PhysicalPackage_IsCompatible_params[] =
{
    &ABC_PhysicalPackage_IsCompatible_MIReturn_param,
    &ABC_PhysicalPackage_IsCompatible_ElementToCheck_param,
};

/* method ABC_PhysicalPackage.IsCompatible() */
MI_CONST MI_MethodDecl ABC_PhysicalPackage_IsCompatible_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0069650C, /* code */
    MI_T("IsCompatible"), /* name */
    ABC_PhysicalPackage_IsCompatible_quals, /* qualifiers */
    MI_COUNT(ABC_PhysicalPackage_IsCompatible_quals), /* numQualifiers */
    ABC_PhysicalPackage_IsCompatible_params, /* parameters */
    MI_COUNT(ABC_PhysicalPackage_IsCompatible_params), /* numParameters */
    sizeof(ABC_PhysicalPackage_IsCompatible), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_PhysicalPackage"), /* origin */
    MI_T("CIM_PhysicalPackage"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_PhysicalPackage_Invoke_IsCompatible, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST ABC_PhysicalPackage_meths[] =
{
    &ABC_PhysicalPackage_IsCompatible_rtti,
};

static MI_CONST MI_ProviderFT ABC_PhysicalPackage_funcs =
{
  (MI_ProviderFT_Load)ABC_PhysicalPackage_Load,
  (MI_ProviderFT_Unload)ABC_PhysicalPackage_Unload,
  (MI_ProviderFT_GetInstance)ABC_PhysicalPackage_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_PhysicalPackage_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_PhysicalPackage_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_PhysicalPackage_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_PhysicalPackage_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_PhysicalPackage_UMLPackagePath_qual_value = MI_T("CIM::Physical::Package");

static MI_CONST MI_Qualifier ABC_PhysicalPackage_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_PhysicalPackage_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_PhysicalPackage_quals[] =
{
    &ABC_PhysicalPackage_UMLPackagePath_qual,
};

/* class ABC_PhysicalPackage */
MI_CONST MI_ClassDecl ABC_PhysicalPackage_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00616513, /* code */
    MI_T("ABC_PhysicalPackage"), /* name */
    ABC_PhysicalPackage_quals, /* qualifiers */
    MI_COUNT(ABC_PhysicalPackage_quals), /* numQualifiers */
    ABC_PhysicalPackage_props, /* properties */
    MI_COUNT(ABC_PhysicalPackage_props), /* numProperties */
    sizeof(ABC_PhysicalPackage), /* size */
    MI_T("CIM_PhysicalPackage"), /* superClass */
    &CIM_PhysicalPackage_rtti, /* superClassDecl */
    ABC_PhysicalPackage_meths, /* methods */
    MI_COUNT(ABC_PhysicalPackage_meths), /* numMethods */
    &schemaDecl, /* schema */
    &ABC_PhysicalPackage_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_Sensor
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_Sensor_SensorType_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Sensor.OtherSensorTypeDescription"),
};

static MI_CONST MI_ConstStringA CIM_Sensor_SensorType_ModelCorrespondence_qual_value =
{
    CIM_Sensor_SensorType_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Sensor_SensorType_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Sensor_SensorType_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Sensor_SensorType_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Sensor_SensorType_quals[] =
{
    &CIM_Sensor_SensorType_ModelCorrespondence_qual,
};

/* property CIM_Sensor.SensorType */
static MI_CONST MI_PropertyDecl CIM_Sensor_SensorType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073650A, /* code */
    MI_T("SensorType"), /* name */
    CIM_Sensor_SensorType_quals, /* qualifiers */
    MI_COUNT(CIM_Sensor_SensorType_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Sensor, SensorType), /* offset */
    MI_T("CIM_Sensor"), /* origin */
    MI_T("CIM_Sensor"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_Sensor_OtherSensorTypeDescription_MaxLen_qual_value = 128U;

static MI_CONST MI_Qualifier CIM_Sensor_OtherSensorTypeDescription_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_Sensor_OtherSensorTypeDescription_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_Sensor_OtherSensorTypeDescription_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_Sensor.SensorType"),
};

static MI_CONST MI_ConstStringA CIM_Sensor_OtherSensorTypeDescription_ModelCorrespondence_qual_value =
{
    CIM_Sensor_OtherSensorTypeDescription_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_Sensor_OtherSensorTypeDescription_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Sensor_OtherSensorTypeDescription_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_Sensor_OtherSensorTypeDescription_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Sensor_OtherSensorTypeDescription_quals[] =
{
    &CIM_Sensor_OtherSensorTypeDescription_MaxLen_qual,
    &CIM_Sensor_OtherSensorTypeDescription_ModelCorrespondence_qual,
};

/* property CIM_Sensor.OtherSensorTypeDescription */
static MI_CONST MI_PropertyDecl CIM_Sensor_OtherSensorTypeDescription_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6E1A, /* code */
    MI_T("OtherSensorTypeDescription"), /* name */
    CIM_Sensor_OtherSensorTypeDescription_quals, /* qualifiers */
    MI_COUNT(CIM_Sensor_OtherSensorTypeDescription_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Sensor, OtherSensorTypeDescription), /* offset */
    MI_T("CIM_Sensor"), /* origin */
    MI_T("CIM_Sensor"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_Sensor_PossibleStates_MaxLen_qual_value = 128U;

static MI_CONST MI_Qualifier CIM_Sensor_PossibleStates_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_Sensor_PossibleStates_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Sensor_PossibleStates_quals[] =
{
    &CIM_Sensor_PossibleStates_MaxLen_qual,
};

/* property CIM_Sensor.PossibleStates */
static MI_CONST MI_PropertyDecl CIM_Sensor_PossibleStates_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070730E, /* code */
    MI_T("PossibleStates"), /* name */
    CIM_Sensor_PossibleStates_quals, /* qualifiers */
    MI_COUNT(CIM_Sensor_PossibleStates_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Sensor, PossibleStates), /* offset */
    MI_T("CIM_Sensor"), /* origin */
    MI_T("CIM_Sensor"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_Sensor_CurrentState_MaxLen_qual_value = 128U;

static MI_CONST MI_Qualifier CIM_Sensor_CurrentState_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_Sensor_CurrentState_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Sensor_CurrentState_quals[] =
{
    &CIM_Sensor_CurrentState_MaxLen_qual,
};

/* property CIM_Sensor.CurrentState */
static MI_CONST MI_PropertyDecl CIM_Sensor_CurrentState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063650C, /* code */
    MI_T("CurrentState"), /* name */
    CIM_Sensor_CurrentState_quals, /* qualifiers */
    MI_COUNT(CIM_Sensor_CurrentState_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Sensor, CurrentState), /* offset */
    MI_T("CIM_Sensor"), /* origin */
    MI_T("CIM_Sensor"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Sensor_PollingInterval_Units_qual_value = MI_T("NanoSeconds");

static MI_CONST MI_Qualifier CIM_Sensor_PollingInterval_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Sensor_PollingInterval_Units_qual_value
};

static MI_CONST MI_Char* CIM_Sensor_PollingInterval_PUnit_qual_value = MI_T("second * 10^-9");

static MI_CONST MI_Qualifier CIM_Sensor_PollingInterval_PUnit_qual =
{
    MI_T("PUnit"),
    MI_STRING,
    0,
    &CIM_Sensor_PollingInterval_PUnit_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Sensor_PollingInterval_quals[] =
{
    &CIM_Sensor_PollingInterval_Units_qual,
    &CIM_Sensor_PollingInterval_PUnit_qual,
};

/* property CIM_Sensor.PollingInterval */
static MI_CONST MI_PropertyDecl CIM_Sensor_PollingInterval_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706C0F, /* code */
    MI_T("PollingInterval"), /* name */
    CIM_Sensor_PollingInterval_quals, /* qualifiers */
    MI_COUNT(CIM_Sensor_PollingInterval_quals), /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Sensor, PollingInterval), /* offset */
    MI_T("CIM_Sensor"), /* origin */
    MI_T("CIM_Sensor"), /* propagator */
    NULL,
};

/* property CIM_Sensor.SensorContext */
static MI_CONST MI_PropertyDecl CIM_Sensor_SensorContext_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073740D, /* code */
    MI_T("SensorContext"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Sensor, SensorContext), /* offset */
    MI_T("CIM_Sensor"), /* origin */
    MI_T("CIM_Sensor"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Sensor_props[] =
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
    &CIM_Sensor_SensorType_prop,
    &CIM_Sensor_OtherSensorTypeDescription_prop,
    &CIM_Sensor_PossibleStates_prop,
    &CIM_Sensor_CurrentState_prop,
    &CIM_Sensor_PollingInterval_prop,
    &CIM_Sensor_SensorContext_prop,
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_Sensor_meths[] =
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

static MI_CONST MI_Char* CIM_Sensor_UMLPackagePath_qual_value = MI_T("CIM::Device::Sensors");

static MI_CONST MI_Qualifier CIM_Sensor_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Sensor_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_Sensor_Version_qual_value = MI_T("2.32.0");

static MI_CONST MI_Qualifier CIM_Sensor_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Sensor_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Sensor_quals[] =
{
    &CIM_Sensor_UMLPackagePath_qual,
    &CIM_Sensor_Version_qual,
};

/* class CIM_Sensor */
MI_CONST MI_ClassDecl CIM_Sensor_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0063720A, /* code */
    MI_T("CIM_Sensor"), /* name */
    CIM_Sensor_quals, /* qualifiers */
    MI_COUNT(CIM_Sensor_quals), /* numQualifiers */
    CIM_Sensor_props, /* properties */
    MI_COUNT(CIM_Sensor_props), /* numProperties */
    sizeof(CIM_Sensor), /* size */
    MI_T("CIM_LogicalDevice"), /* superClass */
    &CIM_LogicalDevice_rtti, /* superClassDecl */
    CIM_Sensor_meths, /* methods */
    MI_COUNT(CIM_Sensor_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_AssociatedSensor
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_AssociatedSensor_Antecedent_Override_qual_value = MI_T("Antecedent");

static MI_CONST MI_Qualifier CIM_AssociatedSensor_Antecedent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_AssociatedSensor_Antecedent_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_AssociatedSensor_Antecedent_quals[] =
{
    &CIM_AssociatedSensor_Antecedent_Override_qual,
};

/* property CIM_AssociatedSensor.Antecedent */
static MI_CONST MI_PropertyDecl CIM_AssociatedSensor_Antecedent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0061740A, /* code */
    MI_T("Antecedent"), /* name */
    CIM_AssociatedSensor_Antecedent_quals, /* qualifiers */
    MI_COUNT(CIM_AssociatedSensor_Antecedent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_Sensor"), /* className */
    0, /* subscript */
    offsetof(CIM_AssociatedSensor, Antecedent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("CIM_AssociatedSensor"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_AssociatedSensor_Dependent_Override_qual_value = MI_T("Dependent");

static MI_CONST MI_Qualifier CIM_AssociatedSensor_Dependent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_AssociatedSensor_Dependent_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_AssociatedSensor_Dependent_quals[] =
{
    &CIM_AssociatedSensor_Dependent_Override_qual,
};

/* property CIM_AssociatedSensor.Dependent */
static MI_CONST MI_PropertyDecl CIM_AssociatedSensor_Dependent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00647409, /* code */
    MI_T("Dependent"), /* name */
    CIM_AssociatedSensor_Dependent_quals, /* qualifiers */
    MI_COUNT(CIM_AssociatedSensor_Dependent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedSystemElement"), /* className */
    0, /* subscript */
    offsetof(CIM_AssociatedSensor, Dependent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("CIM_AssociatedSensor"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_AssociatedSensor_props[] =
{
    &CIM_AssociatedSensor_Antecedent_prop,
    &CIM_AssociatedSensor_Dependent_prop,
};

static MI_CONST MI_Char* CIM_AssociatedSensor_UMLPackagePath_qual_value = MI_T("CIM::Device::Sensors");

static MI_CONST MI_Qualifier CIM_AssociatedSensor_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_AssociatedSensor_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_AssociatedSensor_Version_qual_value = MI_T("2.19.1");

static MI_CONST MI_Qualifier CIM_AssociatedSensor_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_AssociatedSensor_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_AssociatedSensor_quals[] =
{
    &CIM_AssociatedSensor_UMLPackagePath_qual,
    &CIM_AssociatedSensor_Version_qual,
};

/* class CIM_AssociatedSensor */
MI_CONST MI_ClassDecl CIM_AssociatedSensor_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00637214, /* code */
    MI_T("CIM_AssociatedSensor"), /* name */
    CIM_AssociatedSensor_quals, /* qualifiers */
    MI_COUNT(CIM_AssociatedSensor_quals), /* numQualifiers */
    CIM_AssociatedSensor_props, /* properties */
    MI_COUNT(CIM_AssociatedSensor_props), /* numProperties */
    sizeof(CIM_AssociatedSensor), /* size */
    MI_T("CIM_Dependency"), /* superClass */
    &CIM_Dependency_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_NumericSensor
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_NumericSensor_BaseUnits_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_NumericSensor.UnitModifier"),
    MI_T("CIM_NumericSensor.RateUnits"),
};

static MI_CONST MI_ConstStringA CIM_NumericSensor_BaseUnits_ModelCorrespondence_qual_value =
{
    CIM_NumericSensor_BaseUnits_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_NumericSensor_BaseUnits_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_NumericSensor_BaseUnits_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_NumericSensor_BaseUnits_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_NumericSensor_BaseUnits_quals[] =
{
    &CIM_NumericSensor_BaseUnits_ModelCorrespondence_qual,
};

/* property CIM_NumericSensor.BaseUnits */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_BaseUnits_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00627309, /* code */
    MI_T("BaseUnits"), /* name */
    CIM_NumericSensor_BaseUnits_quals, /* qualifiers */
    MI_COUNT(CIM_NumericSensor_BaseUnits_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, BaseUnits), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_NumericSensor_UnitModifier_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_NumericSensor.BaseUnits"),
    MI_T("CIM_NumericSensor.RateUnits"),
};

static MI_CONST MI_ConstStringA CIM_NumericSensor_UnitModifier_ModelCorrespondence_qual_value =
{
    CIM_NumericSensor_UnitModifier_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_NumericSensor_UnitModifier_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_NumericSensor_UnitModifier_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_NumericSensor_UnitModifier_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_NumericSensor_UnitModifier_quals[] =
{
    &CIM_NumericSensor_UnitModifier_ModelCorrespondence_qual,
};

/* property CIM_NumericSensor.UnitModifier */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_UnitModifier_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0075720C, /* code */
    MI_T("UnitModifier"), /* name */
    CIM_NumericSensor_UnitModifier_quals, /* qualifiers */
    MI_COUNT(CIM_NumericSensor_UnitModifier_quals), /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, UnitModifier), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_NumericSensor_RateUnits_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_NumericSensor.UnitModifier"),
    MI_T("CIM_NumericSensor.BaseUnits"),
};

static MI_CONST MI_ConstStringA CIM_NumericSensor_RateUnits_ModelCorrespondence_qual_value =
{
    CIM_NumericSensor_RateUnits_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_NumericSensor_RateUnits_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_NumericSensor_RateUnits_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_NumericSensor_RateUnits_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_NumericSensor_RateUnits_quals[] =
{
    &CIM_NumericSensor_RateUnits_ModelCorrespondence_qual,
};

/* property CIM_NumericSensor.RateUnits */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_RateUnits_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00727309, /* code */
    MI_T("RateUnits"), /* name */
    CIM_NumericSensor_RateUnits_quals, /* qualifiers */
    MI_COUNT(CIM_NumericSensor_RateUnits_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, RateUnits), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.CurrentReading */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_CurrentReading_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063670E, /* code */
    MI_T("CurrentReading"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, CurrentReading), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.NominalReading */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_NominalReading_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E670E, /* code */
    MI_T("NominalReading"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, NominalReading), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.NormalMax */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_NormalMax_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E7809, /* code */
    MI_T("NormalMax"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, NormalMax), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.NormalMin */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_NormalMin_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E6E09, /* code */
    MI_T("NormalMin"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, NormalMin), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.MaxReadable */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_MaxReadable_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D650B, /* code */
    MI_T("MaxReadable"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, MaxReadable), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.MinReadable */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_MinReadable_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D650B, /* code */
    MI_T("MinReadable"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, MinReadable), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.Resolution */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_Resolution_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726E0A, /* code */
    MI_T("Resolution"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, Resolution), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_NumericSensor_Tolerance_Deprecated_qual_data_value[] =
{
    MI_T("CIM_NumericSensor.Resolution"),
    MI_T("CIM_NumericSensor.Accuracy"),
};

static MI_CONST MI_ConstStringA CIM_NumericSensor_Tolerance_Deprecated_qual_value =
{
    CIM_NumericSensor_Tolerance_Deprecated_qual_data_value,
    MI_COUNT(CIM_NumericSensor_Tolerance_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_NumericSensor_Tolerance_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_NumericSensor_Tolerance_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_NumericSensor_Tolerance_quals[] =
{
    &CIM_NumericSensor_Tolerance_Deprecated_qual,
};

/* property CIM_NumericSensor.Tolerance */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_Tolerance_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00746509, /* code */
    MI_T("Tolerance"), /* name */
    CIM_NumericSensor_Tolerance_quals, /* qualifiers */
    MI_COUNT(CIM_NumericSensor_Tolerance_quals), /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, Tolerance), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_NumericSensor_Accuracy_Units_qual_value = MI_T("Hundredths of Percent");

static MI_CONST MI_Qualifier CIM_NumericSensor_Accuracy_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_NumericSensor_Accuracy_Units_qual_value
};

static MI_CONST MI_Char* CIM_NumericSensor_Accuracy_PUnit_qual_value = MI_T("percent * 10^-2");

static MI_CONST MI_Qualifier CIM_NumericSensor_Accuracy_PUnit_qual =
{
    MI_T("PUnit"),
    MI_STRING,
    0,
    &CIM_NumericSensor_Accuracy_PUnit_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_NumericSensor_Accuracy_quals[] =
{
    &CIM_NumericSensor_Accuracy_Units_qual,
    &CIM_NumericSensor_Accuracy_PUnit_qual,
};

/* property CIM_NumericSensor.Accuracy */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_Accuracy_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00617908, /* code */
    MI_T("Accuracy"), /* name */
    CIM_NumericSensor_Accuracy_quals, /* qualifiers */
    MI_COUNT(CIM_NumericSensor_Accuracy_quals), /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, Accuracy), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.IsLinear */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_IsLinear_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00697208, /* code */
    MI_T("IsLinear"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, IsLinear), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.Hysteresis */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_Hysteresis_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0068730A, /* code */
    MI_T("Hysteresis"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, Hysteresis), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.LowerThresholdNonCritical */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_LowerThresholdNonCritical_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C6C19, /* code */
    MI_T("LowerThresholdNonCritical"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, LowerThresholdNonCritical), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.UpperThresholdNonCritical */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_UpperThresholdNonCritical_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756C19, /* code */
    MI_T("UpperThresholdNonCritical"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, UpperThresholdNonCritical), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.LowerThresholdCritical */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_LowerThresholdCritical_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C6C16, /* code */
    MI_T("LowerThresholdCritical"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, LowerThresholdCritical), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.UpperThresholdCritical */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_UpperThresholdCritical_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756C16, /* code */
    MI_T("UpperThresholdCritical"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, UpperThresholdCritical), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.LowerThresholdFatal */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_LowerThresholdFatal_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C6C13, /* code */
    MI_T("LowerThresholdFatal"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, LowerThresholdFatal), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.UpperThresholdFatal */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_UpperThresholdFatal_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756C13, /* code */
    MI_T("UpperThresholdFatal"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, UpperThresholdFatal), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.SupportedThresholds */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_SupportedThresholds_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737313, /* code */
    MI_T("SupportedThresholds"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, SupportedThresholds), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.EnabledThresholds */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_EnabledThresholds_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00657311, /* code */
    MI_T("EnabledThresholds"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, EnabledThresholds), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

/* property CIM_NumericSensor.SettableThresholds */
static MI_CONST MI_PropertyDecl CIM_NumericSensor_SettableThresholds_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737312, /* code */
    MI_T("SettableThresholds"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor, SettableThresholds), /* offset */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_NumericSensor_props[] =
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
    &CIM_Sensor_SensorType_prop,
    &CIM_Sensor_OtherSensorTypeDescription_prop,
    &CIM_Sensor_PossibleStates_prop,
    &CIM_Sensor_CurrentState_prop,
    &CIM_Sensor_PollingInterval_prop,
    &CIM_Sensor_SensorContext_prop,
    &CIM_NumericSensor_BaseUnits_prop,
    &CIM_NumericSensor_UnitModifier_prop,
    &CIM_NumericSensor_RateUnits_prop,
    &CIM_NumericSensor_CurrentReading_prop,
    &CIM_NumericSensor_NominalReading_prop,
    &CIM_NumericSensor_NormalMax_prop,
    &CIM_NumericSensor_NormalMin_prop,
    &CIM_NumericSensor_MaxReadable_prop,
    &CIM_NumericSensor_MinReadable_prop,
    &CIM_NumericSensor_Resolution_prop,
    &CIM_NumericSensor_Tolerance_prop,
    &CIM_NumericSensor_Accuracy_prop,
    &CIM_NumericSensor_IsLinear_prop,
    &CIM_NumericSensor_Hysteresis_prop,
    &CIM_NumericSensor_LowerThresholdNonCritical_prop,
    &CIM_NumericSensor_UpperThresholdNonCritical_prop,
    &CIM_NumericSensor_LowerThresholdCritical_prop,
    &CIM_NumericSensor_UpperThresholdCritical_prop,
    &CIM_NumericSensor_LowerThresholdFatal_prop,
    &CIM_NumericSensor_UpperThresholdFatal_prop,
    &CIM_NumericSensor_SupportedThresholds_prop,
    &CIM_NumericSensor_EnabledThresholds_prop,
    &CIM_NumericSensor_SettableThresholds_prop,
};

/* parameter CIM_NumericSensor.RestoreDefaultThresholds(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_NumericSensor_RestoreDefaultThresholds_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor_RestoreDefaultThresholds, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_NumericSensor_RestoreDefaultThresholds_params[] =
{
    &CIM_NumericSensor_RestoreDefaultThresholds_MIReturn_param,
};

/* method CIM_NumericSensor.RestoreDefaultThresholds() */
MI_CONST MI_MethodDecl CIM_NumericSensor_RestoreDefaultThresholds_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00727318, /* code */
    MI_T("RestoreDefaultThresholds"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    CIM_NumericSensor_RestoreDefaultThresholds_params, /* parameters */
    MI_COUNT(CIM_NumericSensor_RestoreDefaultThresholds_params), /* numParameters */
    sizeof(CIM_NumericSensor_RestoreDefaultThresholds), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_CONST MI_Char* CIM_NumericSensor_GetNonLinearFactors_Deprecated_qual_data_value[] =
{
    MI_T("No value"),
};

static MI_CONST MI_ConstStringA CIM_NumericSensor_GetNonLinearFactors_Deprecated_qual_value =
{
    CIM_NumericSensor_GetNonLinearFactors_Deprecated_qual_data_value,
    MI_COUNT(CIM_NumericSensor_GetNonLinearFactors_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_NumericSensor_GetNonLinearFactors_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_NumericSensor_GetNonLinearFactors_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_NumericSensor_GetNonLinearFactors_quals[] =
{
    &CIM_NumericSensor_GetNonLinearFactors_Deprecated_qual,
};

/* parameter CIM_NumericSensor.GetNonLinearFactors(): SensorReading */
static MI_CONST MI_ParameterDecl CIM_NumericSensor_GetNonLinearFactors_SensorReading_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0073670D, /* code */
    MI_T("SensorReading"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor_GetNonLinearFactors, SensorReading), /* offset */
};

/* parameter CIM_NumericSensor.GetNonLinearFactors(): Accuracy */
static MI_CONST MI_ParameterDecl CIM_NumericSensor_GetNonLinearFactors_Accuracy_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00617908, /* code */
    MI_T("Accuracy"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor_GetNonLinearFactors, Accuracy), /* offset */
};

/* parameter CIM_NumericSensor.GetNonLinearFactors(): Resolution */
static MI_CONST MI_ParameterDecl CIM_NumericSensor_GetNonLinearFactors_Resolution_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00726E0A, /* code */
    MI_T("Resolution"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor_GetNonLinearFactors, Resolution), /* offset */
};

/* parameter CIM_NumericSensor.GetNonLinearFactors(): Tolerance */
static MI_CONST MI_ParameterDecl CIM_NumericSensor_GetNonLinearFactors_Tolerance_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00746509, /* code */
    MI_T("Tolerance"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor_GetNonLinearFactors, Tolerance), /* offset */
};

/* parameter CIM_NumericSensor.GetNonLinearFactors(): Hysteresis */
static MI_CONST MI_ParameterDecl CIM_NumericSensor_GetNonLinearFactors_Hysteresis_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0068730A, /* code */
    MI_T("Hysteresis"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor_GetNonLinearFactors, Hysteresis), /* offset */
};

static MI_CONST MI_Char* CIM_NumericSensor_GetNonLinearFactors_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("No value"),
};

static MI_CONST MI_ConstStringA CIM_NumericSensor_GetNonLinearFactors_MIReturn_Deprecated_qual_value =
{
    CIM_NumericSensor_GetNonLinearFactors_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(CIM_NumericSensor_GetNonLinearFactors_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_NumericSensor_GetNonLinearFactors_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_NumericSensor_GetNonLinearFactors_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_NumericSensor_GetNonLinearFactors_MIReturn_quals[] =
{
    &CIM_NumericSensor_GetNonLinearFactors_MIReturn_Deprecated_qual,
};

/* parameter CIM_NumericSensor.GetNonLinearFactors(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_NumericSensor_GetNonLinearFactors_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    CIM_NumericSensor_GetNonLinearFactors_MIReturn_quals, /* qualifiers */
    MI_COUNT(CIM_NumericSensor_GetNonLinearFactors_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_NumericSensor_GetNonLinearFactors, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_NumericSensor_GetNonLinearFactors_params[] =
{
    &CIM_NumericSensor_GetNonLinearFactors_MIReturn_param,
    &CIM_NumericSensor_GetNonLinearFactors_SensorReading_param,
    &CIM_NumericSensor_GetNonLinearFactors_Accuracy_param,
    &CIM_NumericSensor_GetNonLinearFactors_Resolution_param,
    &CIM_NumericSensor_GetNonLinearFactors_Tolerance_param,
    &CIM_NumericSensor_GetNonLinearFactors_Hysteresis_param,
};

/* method CIM_NumericSensor.GetNonLinearFactors() */
MI_CONST MI_MethodDecl CIM_NumericSensor_GetNonLinearFactors_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00677313, /* code */
    MI_T("GetNonLinearFactors"), /* name */
    CIM_NumericSensor_GetNonLinearFactors_quals, /* qualifiers */
    MI_COUNT(CIM_NumericSensor_GetNonLinearFactors_quals), /* numQualifiers */
    CIM_NumericSensor_GetNonLinearFactors_params, /* parameters */
    MI_COUNT(CIM_NumericSensor_GetNonLinearFactors_params), /* numParameters */
    sizeof(CIM_NumericSensor_GetNonLinearFactors), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_NumericSensor_meths[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_rtti,
    &CIM_LogicalDevice_SetPowerState_rtti,
    &CIM_LogicalDevice_Reset_rtti,
    &CIM_LogicalDevice_EnableDevice_rtti,
    &CIM_LogicalDevice_OnlineDevice_rtti,
    &CIM_LogicalDevice_QuiesceDevice_rtti,
    &CIM_LogicalDevice_SaveProperties_rtti,
    &CIM_LogicalDevice_RestoreProperties_rtti,
    &CIM_NumericSensor_RestoreDefaultThresholds_rtti,
    &CIM_NumericSensor_GetNonLinearFactors_rtti,
};

static MI_CONST MI_Char* CIM_NumericSensor_UMLPackagePath_qual_value = MI_T("CIM::Device::Sensors");

static MI_CONST MI_Qualifier CIM_NumericSensor_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_NumericSensor_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_NumericSensor_Version_qual_value = MI_T("2.16.0");

static MI_CONST MI_Qualifier CIM_NumericSensor_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_NumericSensor_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_NumericSensor_quals[] =
{
    &CIM_NumericSensor_UMLPackagePath_qual,
    &CIM_NumericSensor_Version_qual,
};

/* class CIM_NumericSensor */
MI_CONST MI_ClassDecl CIM_NumericSensor_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00637211, /* code */
    MI_T("CIM_NumericSensor"), /* name */
    CIM_NumericSensor_quals, /* qualifiers */
    MI_COUNT(CIM_NumericSensor_quals), /* numQualifiers */
    CIM_NumericSensor_props, /* properties */
    MI_COUNT(CIM_NumericSensor_props), /* numProperties */
    sizeof(CIM_NumericSensor), /* size */
    MI_T("CIM_Sensor"), /* superClass */
    &CIM_Sensor_rtti, /* superClassDecl */
    CIM_NumericSensor_meths, /* methods */
    MI_COUNT(CIM_NumericSensor_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ABC_NumericSensor
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_NumericSensor_props[] =
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
    &CIM_Sensor_SensorType_prop,
    &CIM_Sensor_OtherSensorTypeDescription_prop,
    &CIM_Sensor_PossibleStates_prop,
    &CIM_Sensor_CurrentState_prop,
    &CIM_Sensor_PollingInterval_prop,
    &CIM_Sensor_SensorContext_prop,
    &CIM_NumericSensor_BaseUnits_prop,
    &CIM_NumericSensor_UnitModifier_prop,
    &CIM_NumericSensor_RateUnits_prop,
    &CIM_NumericSensor_CurrentReading_prop,
    &CIM_NumericSensor_NominalReading_prop,
    &CIM_NumericSensor_NormalMax_prop,
    &CIM_NumericSensor_NormalMin_prop,
    &CIM_NumericSensor_MaxReadable_prop,
    &CIM_NumericSensor_MinReadable_prop,
    &CIM_NumericSensor_Resolution_prop,
    &CIM_NumericSensor_Tolerance_prop,
    &CIM_NumericSensor_Accuracy_prop,
    &CIM_NumericSensor_IsLinear_prop,
    &CIM_NumericSensor_Hysteresis_prop,
    &CIM_NumericSensor_LowerThresholdNonCritical_prop,
    &CIM_NumericSensor_UpperThresholdNonCritical_prop,
    &CIM_NumericSensor_LowerThresholdCritical_prop,
    &CIM_NumericSensor_UpperThresholdCritical_prop,
    &CIM_NumericSensor_LowerThresholdFatal_prop,
    &CIM_NumericSensor_UpperThresholdFatal_prop,
    &CIM_NumericSensor_SupportedThresholds_prop,
    &CIM_NumericSensor_EnabledThresholds_prop,
    &CIM_NumericSensor_SettableThresholds_prop,
};

static MI_CONST MI_Char* ABC_NumericSensor_RequestStateChange_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_NumericSensor_RequestStateChange_ModelCorrespondence_qual_value =
{
    ABC_NumericSensor_RequestStateChange_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_NumericSensor_RequestStateChange_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_NumericSensor_RequestStateChange_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_NumericSensor_RequestStateChange_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_NumericSensor_RequestStateChange_quals[] =
{
    &ABC_NumericSensor_RequestStateChange_ModelCorrespondence_qual,
};

static MI_CONST MI_Char* ABC_NumericSensor_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_NumericSensor_RequestStateChange_RequestedState_ModelCorrespondence_qual_value =
{
    ABC_NumericSensor_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_NumericSensor_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_NumericSensor_RequestStateChange_RequestedState_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_NumericSensor_RequestStateChange_RequestedState_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_NumericSensor_RequestStateChange_RequestedState_quals[] =
{
    &ABC_NumericSensor_RequestStateChange_RequestedState_ModelCorrespondence_qual,
};

/* parameter ABC_NumericSensor.RequestStateChange(): RequestedState */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_RequestStateChange_RequestedState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0072650E, /* code */
    MI_T("RequestedState"), /* name */
    ABC_NumericSensor_RequestStateChange_RequestedState_quals, /* qualifiers */
    MI_COUNT(ABC_NumericSensor_RequestStateChange_RequestedState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_RequestStateChange, RequestedState), /* offset */
};

/* parameter ABC_NumericSensor.RequestStateChange(): Job */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_RequestStateChange_Job_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006A6203, /* code */
    MI_T("Job"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ConcreteJob"), /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_RequestStateChange, Job), /* offset */
};

/* parameter ABC_NumericSensor.RequestStateChange(): TimeoutPeriod */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_RequestStateChange_TimeoutPeriod_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0074640D, /* code */
    MI_T("TimeoutPeriod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_RequestStateChange, TimeoutPeriod), /* offset */
};

static MI_CONST MI_Char* ABC_NumericSensor_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_NumericSensor_RequestStateChange_MIReturn_ModelCorrespondence_qual_value =
{
    ABC_NumericSensor_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_NumericSensor_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_NumericSensor_RequestStateChange_MIReturn_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_NumericSensor_RequestStateChange_MIReturn_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_NumericSensor_RequestStateChange_MIReturn_quals[] =
{
    &ABC_NumericSensor_RequestStateChange_MIReturn_ModelCorrespondence_qual,
};

/* parameter ABC_NumericSensor.RequestStateChange(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_RequestStateChange_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_NumericSensor_RequestStateChange_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_NumericSensor_RequestStateChange_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_RequestStateChange, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_NumericSensor_RequestStateChange_params[] =
{
    &ABC_NumericSensor_RequestStateChange_MIReturn_param,
    &ABC_NumericSensor_RequestStateChange_RequestedState_param,
    &ABC_NumericSensor_RequestStateChange_Job_param,
    &ABC_NumericSensor_RequestStateChange_TimeoutPeriod_param,
};

/* method ABC_NumericSensor.RequestStateChange() */
MI_CONST MI_MethodDecl ABC_NumericSensor_RequestStateChange_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00726512, /* code */
    MI_T("RequestStateChange"), /* name */
    ABC_NumericSensor_RequestStateChange_quals, /* qualifiers */
    MI_COUNT(ABC_NumericSensor_RequestStateChange_quals), /* numQualifiers */
    ABC_NumericSensor_RequestStateChange_params, /* parameters */
    MI_COUNT(ABC_NumericSensor_RequestStateChange_params), /* numParameters */
    sizeof(ABC_NumericSensor_RequestStateChange), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_NumericSensor_Invoke_RequestStateChange, /* method */
};

static MI_CONST MI_Char* ABC_NumericSensor_SetPowerState_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PowerManagementService.SetPowerState"),
};

static MI_CONST MI_ConstStringA ABC_NumericSensor_SetPowerState_Deprecated_qual_value =
{
    ABC_NumericSensor_SetPowerState_Deprecated_qual_data_value,
    MI_COUNT(ABC_NumericSensor_SetPowerState_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_NumericSensor_SetPowerState_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_NumericSensor_SetPowerState_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_NumericSensor_SetPowerState_quals[] =
{
    &ABC_NumericSensor_SetPowerState_Deprecated_qual,
};

/* parameter ABC_NumericSensor.SetPowerState(): PowerState */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_SetPowerState_PowerState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0070650A, /* code */
    MI_T("PowerState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_SetPowerState, PowerState), /* offset */
};

/* parameter ABC_NumericSensor.SetPowerState(): Time */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_SetPowerState_Time_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00746504, /* code */
    MI_T("Time"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_SetPowerState, Time), /* offset */
};

static MI_CONST MI_Char* ABC_NumericSensor_SetPowerState_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PowerManagementService.SetPowerState"),
};

static MI_CONST MI_ConstStringA ABC_NumericSensor_SetPowerState_MIReturn_Deprecated_qual_value =
{
    ABC_NumericSensor_SetPowerState_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_NumericSensor_SetPowerState_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_NumericSensor_SetPowerState_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_NumericSensor_SetPowerState_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_NumericSensor_SetPowerState_MIReturn_quals[] =
{
    &ABC_NumericSensor_SetPowerState_MIReturn_Deprecated_qual,
};

/* parameter ABC_NumericSensor.SetPowerState(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_SetPowerState_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_NumericSensor_SetPowerState_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_NumericSensor_SetPowerState_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_SetPowerState, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_NumericSensor_SetPowerState_params[] =
{
    &ABC_NumericSensor_SetPowerState_MIReturn_param,
    &ABC_NumericSensor_SetPowerState_PowerState_param,
    &ABC_NumericSensor_SetPowerState_Time_param,
};

/* method ABC_NumericSensor.SetPowerState() */
MI_CONST MI_MethodDecl ABC_NumericSensor_SetPowerState_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650D, /* code */
    MI_T("SetPowerState"), /* name */
    ABC_NumericSensor_SetPowerState_quals, /* qualifiers */
    MI_COUNT(ABC_NumericSensor_SetPowerState_quals), /* numQualifiers */
    ABC_NumericSensor_SetPowerState_params, /* parameters */
    MI_COUNT(ABC_NumericSensor_SetPowerState_params), /* numParameters */
    sizeof(ABC_NumericSensor_SetPowerState), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_NumericSensor_Invoke_SetPowerState, /* method */
};

/* parameter ABC_NumericSensor.Reset(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_Reset_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_Reset, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_NumericSensor_Reset_params[] =
{
    &ABC_NumericSensor_Reset_MIReturn_param,
};

/* method ABC_NumericSensor.Reset() */
MI_CONST MI_MethodDecl ABC_NumericSensor_Reset_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00727405, /* code */
    MI_T("Reset"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_NumericSensor_Reset_params, /* parameters */
    MI_COUNT(ABC_NumericSensor_Reset_params), /* numParameters */
    sizeof(ABC_NumericSensor_Reset), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_NumericSensor_Invoke_Reset, /* method */
};

static MI_CONST MI_Char* ABC_NumericSensor_EnableDevice_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_NumericSensor_EnableDevice_Deprecated_qual_value =
{
    ABC_NumericSensor_EnableDevice_Deprecated_qual_data_value,
    MI_COUNT(ABC_NumericSensor_EnableDevice_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_NumericSensor_EnableDevice_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_NumericSensor_EnableDevice_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_NumericSensor_EnableDevice_quals[] =
{
    &ABC_NumericSensor_EnableDevice_Deprecated_qual,
};

/* parameter ABC_NumericSensor.EnableDevice(): Enabled */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_EnableDevice_Enabled_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00656407, /* code */
    MI_T("Enabled"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_EnableDevice, Enabled), /* offset */
};

static MI_CONST MI_Char* ABC_NumericSensor_EnableDevice_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_NumericSensor_EnableDevice_MIReturn_Deprecated_qual_value =
{
    ABC_NumericSensor_EnableDevice_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_NumericSensor_EnableDevice_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_NumericSensor_EnableDevice_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_NumericSensor_EnableDevice_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_NumericSensor_EnableDevice_MIReturn_quals[] =
{
    &ABC_NumericSensor_EnableDevice_MIReturn_Deprecated_qual,
};

/* parameter ABC_NumericSensor.EnableDevice(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_EnableDevice_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_NumericSensor_EnableDevice_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_NumericSensor_EnableDevice_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_EnableDevice, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_NumericSensor_EnableDevice_params[] =
{
    &ABC_NumericSensor_EnableDevice_MIReturn_param,
    &ABC_NumericSensor_EnableDevice_Enabled_param,
};

/* method ABC_NumericSensor.EnableDevice() */
MI_CONST MI_MethodDecl ABC_NumericSensor_EnableDevice_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0065650C, /* code */
    MI_T("EnableDevice"), /* name */
    ABC_NumericSensor_EnableDevice_quals, /* qualifiers */
    MI_COUNT(ABC_NumericSensor_EnableDevice_quals), /* numQualifiers */
    ABC_NumericSensor_EnableDevice_params, /* parameters */
    MI_COUNT(ABC_NumericSensor_EnableDevice_params), /* numParameters */
    sizeof(ABC_NumericSensor_EnableDevice), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_NumericSensor_Invoke_EnableDevice, /* method */
};

static MI_CONST MI_Char* ABC_NumericSensor_OnlineDevice_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_NumericSensor_OnlineDevice_Deprecated_qual_value =
{
    ABC_NumericSensor_OnlineDevice_Deprecated_qual_data_value,
    MI_COUNT(ABC_NumericSensor_OnlineDevice_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_NumericSensor_OnlineDevice_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_NumericSensor_OnlineDevice_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_NumericSensor_OnlineDevice_quals[] =
{
    &ABC_NumericSensor_OnlineDevice_Deprecated_qual,
};

/* parameter ABC_NumericSensor.OnlineDevice(): Online */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_OnlineDevice_Online_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006F6506, /* code */
    MI_T("Online"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_OnlineDevice, Online), /* offset */
};

static MI_CONST MI_Char* ABC_NumericSensor_OnlineDevice_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_NumericSensor_OnlineDevice_MIReturn_Deprecated_qual_value =
{
    ABC_NumericSensor_OnlineDevice_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_NumericSensor_OnlineDevice_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_NumericSensor_OnlineDevice_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_NumericSensor_OnlineDevice_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_NumericSensor_OnlineDevice_MIReturn_quals[] =
{
    &ABC_NumericSensor_OnlineDevice_MIReturn_Deprecated_qual,
};

/* parameter ABC_NumericSensor.OnlineDevice(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_OnlineDevice_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_NumericSensor_OnlineDevice_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_NumericSensor_OnlineDevice_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_OnlineDevice, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_NumericSensor_OnlineDevice_params[] =
{
    &ABC_NumericSensor_OnlineDevice_MIReturn_param,
    &ABC_NumericSensor_OnlineDevice_Online_param,
};

/* method ABC_NumericSensor.OnlineDevice() */
MI_CONST MI_MethodDecl ABC_NumericSensor_OnlineDevice_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006F650C, /* code */
    MI_T("OnlineDevice"), /* name */
    ABC_NumericSensor_OnlineDevice_quals, /* qualifiers */
    MI_COUNT(ABC_NumericSensor_OnlineDevice_quals), /* numQualifiers */
    ABC_NumericSensor_OnlineDevice_params, /* parameters */
    MI_COUNT(ABC_NumericSensor_OnlineDevice_params), /* numParameters */
    sizeof(ABC_NumericSensor_OnlineDevice), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_NumericSensor_Invoke_OnlineDevice, /* method */
};

static MI_CONST MI_Char* ABC_NumericSensor_QuiesceDevice_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_NumericSensor_QuiesceDevice_Deprecated_qual_value =
{
    ABC_NumericSensor_QuiesceDevice_Deprecated_qual_data_value,
    MI_COUNT(ABC_NumericSensor_QuiesceDevice_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_NumericSensor_QuiesceDevice_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_NumericSensor_QuiesceDevice_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_NumericSensor_QuiesceDevice_quals[] =
{
    &ABC_NumericSensor_QuiesceDevice_Deprecated_qual,
};

/* parameter ABC_NumericSensor.QuiesceDevice(): Quiesce */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_QuiesceDevice_Quiesce_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00716507, /* code */
    MI_T("Quiesce"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_QuiesceDevice, Quiesce), /* offset */
};

static MI_CONST MI_Char* ABC_NumericSensor_QuiesceDevice_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_NumericSensor_QuiesceDevice_MIReturn_Deprecated_qual_value =
{
    ABC_NumericSensor_QuiesceDevice_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_NumericSensor_QuiesceDevice_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_NumericSensor_QuiesceDevice_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_NumericSensor_QuiesceDevice_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_NumericSensor_QuiesceDevice_MIReturn_quals[] =
{
    &ABC_NumericSensor_QuiesceDevice_MIReturn_Deprecated_qual,
};

/* parameter ABC_NumericSensor.QuiesceDevice(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_QuiesceDevice_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_NumericSensor_QuiesceDevice_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_NumericSensor_QuiesceDevice_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_QuiesceDevice, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_NumericSensor_QuiesceDevice_params[] =
{
    &ABC_NumericSensor_QuiesceDevice_MIReturn_param,
    &ABC_NumericSensor_QuiesceDevice_Quiesce_param,
};

/* method ABC_NumericSensor.QuiesceDevice() */
MI_CONST MI_MethodDecl ABC_NumericSensor_QuiesceDevice_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0071650D, /* code */
    MI_T("QuiesceDevice"), /* name */
    ABC_NumericSensor_QuiesceDevice_quals, /* qualifiers */
    MI_COUNT(ABC_NumericSensor_QuiesceDevice_quals), /* numQualifiers */
    ABC_NumericSensor_QuiesceDevice_params, /* parameters */
    MI_COUNT(ABC_NumericSensor_QuiesceDevice_params), /* numParameters */
    sizeof(ABC_NumericSensor_QuiesceDevice), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_NumericSensor_Invoke_QuiesceDevice, /* method */
};

/* parameter ABC_NumericSensor.SaveProperties(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_SaveProperties_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_SaveProperties, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_NumericSensor_SaveProperties_params[] =
{
    &ABC_NumericSensor_SaveProperties_MIReturn_param,
};

/* method ABC_NumericSensor.SaveProperties() */
MI_CONST MI_MethodDecl ABC_NumericSensor_SaveProperties_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073730E, /* code */
    MI_T("SaveProperties"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_NumericSensor_SaveProperties_params, /* parameters */
    MI_COUNT(ABC_NumericSensor_SaveProperties_params), /* numParameters */
    sizeof(ABC_NumericSensor_SaveProperties), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_NumericSensor_Invoke_SaveProperties, /* method */
};

/* parameter ABC_NumericSensor.RestoreProperties(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_RestoreProperties_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_RestoreProperties, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_NumericSensor_RestoreProperties_params[] =
{
    &ABC_NumericSensor_RestoreProperties_MIReturn_param,
};

/* method ABC_NumericSensor.RestoreProperties() */
MI_CONST MI_MethodDecl ABC_NumericSensor_RestoreProperties_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00727311, /* code */
    MI_T("RestoreProperties"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_NumericSensor_RestoreProperties_params, /* parameters */
    MI_COUNT(ABC_NumericSensor_RestoreProperties_params), /* numParameters */
    sizeof(ABC_NumericSensor_RestoreProperties), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_NumericSensor_Invoke_RestoreProperties, /* method */
};

/* parameter ABC_NumericSensor.RestoreDefaultThresholds(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_RestoreDefaultThresholds_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_RestoreDefaultThresholds, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_NumericSensor_RestoreDefaultThresholds_params[] =
{
    &ABC_NumericSensor_RestoreDefaultThresholds_MIReturn_param,
};

/* method ABC_NumericSensor.RestoreDefaultThresholds() */
MI_CONST MI_MethodDecl ABC_NumericSensor_RestoreDefaultThresholds_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00727318, /* code */
    MI_T("RestoreDefaultThresholds"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_NumericSensor_RestoreDefaultThresholds_params, /* parameters */
    MI_COUNT(ABC_NumericSensor_RestoreDefaultThresholds_params), /* numParameters */
    sizeof(ABC_NumericSensor_RestoreDefaultThresholds), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_NumericSensor_Invoke_RestoreDefaultThresholds, /* method */
};

static MI_CONST MI_Char* ABC_NumericSensor_GetNonLinearFactors_Deprecated_qual_data_value[] =
{
    MI_T("No value"),
};

static MI_CONST MI_ConstStringA ABC_NumericSensor_GetNonLinearFactors_Deprecated_qual_value =
{
    ABC_NumericSensor_GetNonLinearFactors_Deprecated_qual_data_value,
    MI_COUNT(ABC_NumericSensor_GetNonLinearFactors_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_NumericSensor_GetNonLinearFactors_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_NumericSensor_GetNonLinearFactors_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_NumericSensor_GetNonLinearFactors_quals[] =
{
    &ABC_NumericSensor_GetNonLinearFactors_Deprecated_qual,
};

/* parameter ABC_NumericSensor.GetNonLinearFactors(): SensorReading */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_GetNonLinearFactors_SensorReading_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0073670D, /* code */
    MI_T("SensorReading"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_GetNonLinearFactors, SensorReading), /* offset */
};

/* parameter ABC_NumericSensor.GetNonLinearFactors(): Accuracy */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_GetNonLinearFactors_Accuracy_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00617908, /* code */
    MI_T("Accuracy"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_GetNonLinearFactors, Accuracy), /* offset */
};

/* parameter ABC_NumericSensor.GetNonLinearFactors(): Resolution */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_GetNonLinearFactors_Resolution_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00726E0A, /* code */
    MI_T("Resolution"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_GetNonLinearFactors, Resolution), /* offset */
};

/* parameter ABC_NumericSensor.GetNonLinearFactors(): Tolerance */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_GetNonLinearFactors_Tolerance_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00746509, /* code */
    MI_T("Tolerance"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_GetNonLinearFactors, Tolerance), /* offset */
};

/* parameter ABC_NumericSensor.GetNonLinearFactors(): Hysteresis */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_GetNonLinearFactors_Hysteresis_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x0068730A, /* code */
    MI_T("Hysteresis"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_GetNonLinearFactors, Hysteresis), /* offset */
};

static MI_CONST MI_Char* ABC_NumericSensor_GetNonLinearFactors_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("No value"),
};

static MI_CONST MI_ConstStringA ABC_NumericSensor_GetNonLinearFactors_MIReturn_Deprecated_qual_value =
{
    ABC_NumericSensor_GetNonLinearFactors_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_NumericSensor_GetNonLinearFactors_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_NumericSensor_GetNonLinearFactors_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_NumericSensor_GetNonLinearFactors_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_NumericSensor_GetNonLinearFactors_MIReturn_quals[] =
{
    &ABC_NumericSensor_GetNonLinearFactors_MIReturn_Deprecated_qual,
};

/* parameter ABC_NumericSensor.GetNonLinearFactors(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_NumericSensor_GetNonLinearFactors_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_NumericSensor_GetNonLinearFactors_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_NumericSensor_GetNonLinearFactors_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_NumericSensor_GetNonLinearFactors, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_NumericSensor_GetNonLinearFactors_params[] =
{
    &ABC_NumericSensor_GetNonLinearFactors_MIReturn_param,
    &ABC_NumericSensor_GetNonLinearFactors_SensorReading_param,
    &ABC_NumericSensor_GetNonLinearFactors_Accuracy_param,
    &ABC_NumericSensor_GetNonLinearFactors_Resolution_param,
    &ABC_NumericSensor_GetNonLinearFactors_Tolerance_param,
    &ABC_NumericSensor_GetNonLinearFactors_Hysteresis_param,
};

/* method ABC_NumericSensor.GetNonLinearFactors() */
MI_CONST MI_MethodDecl ABC_NumericSensor_GetNonLinearFactors_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00677313, /* code */
    MI_T("GetNonLinearFactors"), /* name */
    ABC_NumericSensor_GetNonLinearFactors_quals, /* qualifiers */
    MI_COUNT(ABC_NumericSensor_GetNonLinearFactors_quals), /* numQualifiers */
    ABC_NumericSensor_GetNonLinearFactors_params, /* parameters */
    MI_COUNT(ABC_NumericSensor_GetNonLinearFactors_params), /* numParameters */
    sizeof(ABC_NumericSensor_GetNonLinearFactors), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_NumericSensor"), /* origin */
    MI_T("CIM_NumericSensor"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_NumericSensor_Invoke_GetNonLinearFactors, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST ABC_NumericSensor_meths[] =
{
    &ABC_NumericSensor_RequestStateChange_rtti,
    &ABC_NumericSensor_SetPowerState_rtti,
    &ABC_NumericSensor_Reset_rtti,
    &ABC_NumericSensor_EnableDevice_rtti,
    &ABC_NumericSensor_OnlineDevice_rtti,
    &ABC_NumericSensor_QuiesceDevice_rtti,
    &ABC_NumericSensor_SaveProperties_rtti,
    &ABC_NumericSensor_RestoreProperties_rtti,
    &ABC_NumericSensor_RestoreDefaultThresholds_rtti,
    &ABC_NumericSensor_GetNonLinearFactors_rtti,
};

static MI_CONST MI_ProviderFT ABC_NumericSensor_funcs =
{
  (MI_ProviderFT_Load)ABC_NumericSensor_Load,
  (MI_ProviderFT_Unload)ABC_NumericSensor_Unload,
  (MI_ProviderFT_GetInstance)ABC_NumericSensor_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_NumericSensor_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_NumericSensor_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_NumericSensor_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_NumericSensor_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_NumericSensor_UMLPackagePath_qual_value = MI_T("CIM::Device::Sensors");

static MI_CONST MI_Qualifier ABC_NumericSensor_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_NumericSensor_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_NumericSensor_quals[] =
{
    &ABC_NumericSensor_UMLPackagePath_qual,
};

/* class ABC_NumericSensor */
MI_CONST MI_ClassDecl ABC_NumericSensor_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00617211, /* code */
    MI_T("ABC_NumericSensor"), /* name */
    ABC_NumericSensor_quals, /* qualifiers */
    MI_COUNT(ABC_NumericSensor_quals), /* numQualifiers */
    ABC_NumericSensor_props, /* properties */
    MI_COUNT(ABC_NumericSensor_props), /* numProperties */
    sizeof(ABC_NumericSensor), /* size */
    MI_T("CIM_NumericSensor"), /* superClass */
    &CIM_NumericSensor_rtti, /* superClassDecl */
    ABC_NumericSensor_meths, /* methods */
    MI_COUNT(ABC_NumericSensor_meths), /* numMethods */
    &schemaDecl, /* schema */
    &ABC_NumericSensor_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ABC_AssociatedSensor
**
**==============================================================================
*/

/* property ABC_AssociatedSensor.Antecedent */
static MI_CONST MI_PropertyDecl ABC_AssociatedSensor_Antecedent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0061740A, /* code */
    MI_T("Antecedent"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("ABC_NumericSensor"), /* className */
    0, /* subscript */
    offsetof(ABC_AssociatedSensor, Antecedent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("ABC_AssociatedSensor"), /* propagator */
    NULL,
};

/* property ABC_AssociatedSensor.Dependent */
static MI_CONST MI_PropertyDecl ABC_AssociatedSensor_Dependent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00647409, /* code */
    MI_T("Dependent"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("ABC_Fan"), /* className */
    0, /* subscript */
    offsetof(ABC_AssociatedSensor, Dependent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("ABC_AssociatedSensor"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST ABC_AssociatedSensor_props[] =
{
    &ABC_AssociatedSensor_Antecedent_prop,
    &ABC_AssociatedSensor_Dependent_prop,
};

static void MI_CALL ABC_AssociatedSensor_AssociatorInstances(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (ABC_NumericSensor_IsA(instanceName))
    {
        if (_Match(role, MI_T("Antecedent")) && 
            _Match(resultRole, MI_T("Dependent")))
        {
            ABC_AssociatedSensor_AssociatorInstancesAntecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (ABC_NumericSensor*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (ABC_Fan_IsA(instanceName))
    {
        if (_Match(role, MI_T("Dependent")) && 
            _Match(resultRole, MI_T("Antecedent")))
        {
            ABC_AssociatedSensor_AssociatorInstancesDependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (ABC_Fan*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL ABC_AssociatedSensor_ReferenceInstances(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (ABC_NumericSensor_IsA(instanceName))
    {
        if (_Match(role, MI_T("Antecedent")))
        {
            ABC_AssociatedSensor_ReferenceInstancesAntecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (ABC_NumericSensor*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (ABC_Fan_IsA(instanceName))
    {
        if (_Match(role, MI_T("Dependent")))
        {
            ABC_AssociatedSensor_ReferenceInstancesDependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (ABC_Fan*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT ABC_AssociatedSensor_funcs =
{
  (MI_ProviderFT_Load)ABC_AssociatedSensor_Load,
  (MI_ProviderFT_Unload)ABC_AssociatedSensor_Unload,
  (MI_ProviderFT_GetInstance)ABC_AssociatedSensor_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_AssociatedSensor_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_AssociatedSensor_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_AssociatedSensor_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_AssociatedSensor_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)ABC_AssociatedSensor_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)ABC_AssociatedSensor_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_AssociatedSensor_UMLPackagePath_qual_value = MI_T("CIM::Device::Sensors");

static MI_CONST MI_Qualifier ABC_AssociatedSensor_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_AssociatedSensor_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_AssociatedSensor_quals[] =
{
    &ABC_AssociatedSensor_UMLPackagePath_qual,
};

/* class ABC_AssociatedSensor */
MI_CONST MI_ClassDecl ABC_AssociatedSensor_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00617214, /* code */
    MI_T("ABC_AssociatedSensor"), /* name */
    ABC_AssociatedSensor_quals, /* qualifiers */
    MI_COUNT(ABC_AssociatedSensor_quals), /* numQualifiers */
    ABC_AssociatedSensor_props, /* properties */
    MI_COUNT(ABC_AssociatedSensor_props), /* numProperties */
    sizeof(ABC_AssociatedSensor), /* size */
    MI_T("CIM_AssociatedSensor"), /* superClass */
    &CIM_AssociatedSensor_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &ABC_AssociatedSensor_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ABC_Sensor
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_Sensor_props[] =
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
    &CIM_Sensor_SensorType_prop,
    &CIM_Sensor_OtherSensorTypeDescription_prop,
    &CIM_Sensor_PossibleStates_prop,
    &CIM_Sensor_CurrentState_prop,
    &CIM_Sensor_PollingInterval_prop,
    &CIM_Sensor_SensorContext_prop,
};

static MI_CONST MI_Char* ABC_Sensor_RequestStateChange_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_Sensor_RequestStateChange_ModelCorrespondence_qual_value =
{
    ABC_Sensor_RequestStateChange_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_Sensor_RequestStateChange_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Sensor_RequestStateChange_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_Sensor_RequestStateChange_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Sensor_RequestStateChange_quals[] =
{
    &ABC_Sensor_RequestStateChange_ModelCorrespondence_qual,
};

static MI_CONST MI_Char* ABC_Sensor_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_Sensor_RequestStateChange_RequestedState_ModelCorrespondence_qual_value =
{
    ABC_Sensor_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_Sensor_RequestStateChange_RequestedState_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Sensor_RequestStateChange_RequestedState_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_Sensor_RequestStateChange_RequestedState_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Sensor_RequestStateChange_RequestedState_quals[] =
{
    &ABC_Sensor_RequestStateChange_RequestedState_ModelCorrespondence_qual,
};

/* parameter ABC_Sensor.RequestStateChange(): RequestedState */
static MI_CONST MI_ParameterDecl ABC_Sensor_RequestStateChange_RequestedState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0072650E, /* code */
    MI_T("RequestedState"), /* name */
    ABC_Sensor_RequestStateChange_RequestedState_quals, /* qualifiers */
    MI_COUNT(ABC_Sensor_RequestStateChange_RequestedState_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Sensor_RequestStateChange, RequestedState), /* offset */
};

/* parameter ABC_Sensor.RequestStateChange(): Job */
static MI_CONST MI_ParameterDecl ABC_Sensor_RequestStateChange_Job_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006A6203, /* code */
    MI_T("Job"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ConcreteJob"), /* className */
    0, /* subscript */
    offsetof(ABC_Sensor_RequestStateChange, Job), /* offset */
};

/* parameter ABC_Sensor.RequestStateChange(): TimeoutPeriod */
static MI_CONST MI_ParameterDecl ABC_Sensor_RequestStateChange_TimeoutPeriod_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0074640D, /* code */
    MI_T("TimeoutPeriod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Sensor_RequestStateChange, TimeoutPeriod), /* offset */
};

static MI_CONST MI_Char* ABC_Sensor_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestedState"),
};

static MI_CONST MI_ConstStringA ABC_Sensor_RequestStateChange_MIReturn_ModelCorrespondence_qual_value =
{
    ABC_Sensor_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value,
    MI_COUNT(ABC_Sensor_RequestStateChange_MIReturn_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Sensor_RequestStateChange_MIReturn_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &ABC_Sensor_RequestStateChange_MIReturn_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Sensor_RequestStateChange_MIReturn_quals[] =
{
    &ABC_Sensor_RequestStateChange_MIReturn_ModelCorrespondence_qual,
};

/* parameter ABC_Sensor.RequestStateChange(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_Sensor_RequestStateChange_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_Sensor_RequestStateChange_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_Sensor_RequestStateChange_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Sensor_RequestStateChange, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_Sensor_RequestStateChange_params[] =
{
    &ABC_Sensor_RequestStateChange_MIReturn_param,
    &ABC_Sensor_RequestStateChange_RequestedState_param,
    &ABC_Sensor_RequestStateChange_Job_param,
    &ABC_Sensor_RequestStateChange_TimeoutPeriod_param,
};

/* method ABC_Sensor.RequestStateChange() */
MI_CONST MI_MethodDecl ABC_Sensor_RequestStateChange_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00726512, /* code */
    MI_T("RequestStateChange"), /* name */
    ABC_Sensor_RequestStateChange_quals, /* qualifiers */
    MI_COUNT(ABC_Sensor_RequestStateChange_quals), /* numQualifiers */
    ABC_Sensor_RequestStateChange_params, /* parameters */
    MI_COUNT(ABC_Sensor_RequestStateChange_params), /* numParameters */
    sizeof(ABC_Sensor_RequestStateChange), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_Sensor_Invoke_RequestStateChange, /* method */
};

static MI_CONST MI_Char* ABC_Sensor_SetPowerState_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PowerManagementService.SetPowerState"),
};

static MI_CONST MI_ConstStringA ABC_Sensor_SetPowerState_Deprecated_qual_value =
{
    ABC_Sensor_SetPowerState_Deprecated_qual_data_value,
    MI_COUNT(ABC_Sensor_SetPowerState_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Sensor_SetPowerState_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_Sensor_SetPowerState_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Sensor_SetPowerState_quals[] =
{
    &ABC_Sensor_SetPowerState_Deprecated_qual,
};

/* parameter ABC_Sensor.SetPowerState(): PowerState */
static MI_CONST MI_ParameterDecl ABC_Sensor_SetPowerState_PowerState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0070650A, /* code */
    MI_T("PowerState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Sensor_SetPowerState, PowerState), /* offset */
};

/* parameter ABC_Sensor.SetPowerState(): Time */
static MI_CONST MI_ParameterDecl ABC_Sensor_SetPowerState_Time_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00746504, /* code */
    MI_T("Time"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Sensor_SetPowerState, Time), /* offset */
};

static MI_CONST MI_Char* ABC_Sensor_SetPowerState_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_PowerManagementService.SetPowerState"),
};

static MI_CONST MI_ConstStringA ABC_Sensor_SetPowerState_MIReturn_Deprecated_qual_value =
{
    ABC_Sensor_SetPowerState_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_Sensor_SetPowerState_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Sensor_SetPowerState_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_Sensor_SetPowerState_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Sensor_SetPowerState_MIReturn_quals[] =
{
    &ABC_Sensor_SetPowerState_MIReturn_Deprecated_qual,
};

/* parameter ABC_Sensor.SetPowerState(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_Sensor_SetPowerState_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_Sensor_SetPowerState_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_Sensor_SetPowerState_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Sensor_SetPowerState, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_Sensor_SetPowerState_params[] =
{
    &ABC_Sensor_SetPowerState_MIReturn_param,
    &ABC_Sensor_SetPowerState_PowerState_param,
    &ABC_Sensor_SetPowerState_Time_param,
};

/* method ABC_Sensor.SetPowerState() */
MI_CONST MI_MethodDecl ABC_Sensor_SetPowerState_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073650D, /* code */
    MI_T("SetPowerState"), /* name */
    ABC_Sensor_SetPowerState_quals, /* qualifiers */
    MI_COUNT(ABC_Sensor_SetPowerState_quals), /* numQualifiers */
    ABC_Sensor_SetPowerState_params, /* parameters */
    MI_COUNT(ABC_Sensor_SetPowerState_params), /* numParameters */
    sizeof(ABC_Sensor_SetPowerState), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_Sensor_Invoke_SetPowerState, /* method */
};

/* parameter ABC_Sensor.Reset(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_Sensor_Reset_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Sensor_Reset, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_Sensor_Reset_params[] =
{
    &ABC_Sensor_Reset_MIReturn_param,
};

/* method ABC_Sensor.Reset() */
MI_CONST MI_MethodDecl ABC_Sensor_Reset_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00727405, /* code */
    MI_T("Reset"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_Sensor_Reset_params, /* parameters */
    MI_COUNT(ABC_Sensor_Reset_params), /* numParameters */
    sizeof(ABC_Sensor_Reset), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_Sensor_Invoke_Reset, /* method */
};

static MI_CONST MI_Char* ABC_Sensor_EnableDevice_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_Sensor_EnableDevice_Deprecated_qual_value =
{
    ABC_Sensor_EnableDevice_Deprecated_qual_data_value,
    MI_COUNT(ABC_Sensor_EnableDevice_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Sensor_EnableDevice_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_Sensor_EnableDevice_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Sensor_EnableDevice_quals[] =
{
    &ABC_Sensor_EnableDevice_Deprecated_qual,
};

/* parameter ABC_Sensor.EnableDevice(): Enabled */
static MI_CONST MI_ParameterDecl ABC_Sensor_EnableDevice_Enabled_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00656407, /* code */
    MI_T("Enabled"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Sensor_EnableDevice, Enabled), /* offset */
};

static MI_CONST MI_Char* ABC_Sensor_EnableDevice_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_Sensor_EnableDevice_MIReturn_Deprecated_qual_value =
{
    ABC_Sensor_EnableDevice_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_Sensor_EnableDevice_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Sensor_EnableDevice_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_Sensor_EnableDevice_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Sensor_EnableDevice_MIReturn_quals[] =
{
    &ABC_Sensor_EnableDevice_MIReturn_Deprecated_qual,
};

/* parameter ABC_Sensor.EnableDevice(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_Sensor_EnableDevice_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_Sensor_EnableDevice_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_Sensor_EnableDevice_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Sensor_EnableDevice, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_Sensor_EnableDevice_params[] =
{
    &ABC_Sensor_EnableDevice_MIReturn_param,
    &ABC_Sensor_EnableDevice_Enabled_param,
};

/* method ABC_Sensor.EnableDevice() */
MI_CONST MI_MethodDecl ABC_Sensor_EnableDevice_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0065650C, /* code */
    MI_T("EnableDevice"), /* name */
    ABC_Sensor_EnableDevice_quals, /* qualifiers */
    MI_COUNT(ABC_Sensor_EnableDevice_quals), /* numQualifiers */
    ABC_Sensor_EnableDevice_params, /* parameters */
    MI_COUNT(ABC_Sensor_EnableDevice_params), /* numParameters */
    sizeof(ABC_Sensor_EnableDevice), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_Sensor_Invoke_EnableDevice, /* method */
};

static MI_CONST MI_Char* ABC_Sensor_OnlineDevice_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_Sensor_OnlineDevice_Deprecated_qual_value =
{
    ABC_Sensor_OnlineDevice_Deprecated_qual_data_value,
    MI_COUNT(ABC_Sensor_OnlineDevice_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Sensor_OnlineDevice_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_Sensor_OnlineDevice_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Sensor_OnlineDevice_quals[] =
{
    &ABC_Sensor_OnlineDevice_Deprecated_qual,
};

/* parameter ABC_Sensor.OnlineDevice(): Online */
static MI_CONST MI_ParameterDecl ABC_Sensor_OnlineDevice_Online_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006F6506, /* code */
    MI_T("Online"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Sensor_OnlineDevice, Online), /* offset */
};

static MI_CONST MI_Char* ABC_Sensor_OnlineDevice_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_Sensor_OnlineDevice_MIReturn_Deprecated_qual_value =
{
    ABC_Sensor_OnlineDevice_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_Sensor_OnlineDevice_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Sensor_OnlineDevice_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_Sensor_OnlineDevice_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Sensor_OnlineDevice_MIReturn_quals[] =
{
    &ABC_Sensor_OnlineDevice_MIReturn_Deprecated_qual,
};

/* parameter ABC_Sensor.OnlineDevice(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_Sensor_OnlineDevice_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_Sensor_OnlineDevice_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_Sensor_OnlineDevice_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Sensor_OnlineDevice, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_Sensor_OnlineDevice_params[] =
{
    &ABC_Sensor_OnlineDevice_MIReturn_param,
    &ABC_Sensor_OnlineDevice_Online_param,
};

/* method ABC_Sensor.OnlineDevice() */
MI_CONST MI_MethodDecl ABC_Sensor_OnlineDevice_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006F650C, /* code */
    MI_T("OnlineDevice"), /* name */
    ABC_Sensor_OnlineDevice_quals, /* qualifiers */
    MI_COUNT(ABC_Sensor_OnlineDevice_quals), /* numQualifiers */
    ABC_Sensor_OnlineDevice_params, /* parameters */
    MI_COUNT(ABC_Sensor_OnlineDevice_params), /* numParameters */
    sizeof(ABC_Sensor_OnlineDevice), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_Sensor_Invoke_OnlineDevice, /* method */
};

static MI_CONST MI_Char* ABC_Sensor_QuiesceDevice_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_Sensor_QuiesceDevice_Deprecated_qual_value =
{
    ABC_Sensor_QuiesceDevice_Deprecated_qual_data_value,
    MI_COUNT(ABC_Sensor_QuiesceDevice_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Sensor_QuiesceDevice_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_Sensor_QuiesceDevice_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Sensor_QuiesceDevice_quals[] =
{
    &ABC_Sensor_QuiesceDevice_Deprecated_qual,
};

/* parameter ABC_Sensor.QuiesceDevice(): Quiesce */
static MI_CONST MI_ParameterDecl ABC_Sensor_QuiesceDevice_Quiesce_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00716507, /* code */
    MI_T("Quiesce"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Sensor_QuiesceDevice, Quiesce), /* offset */
};

static MI_CONST MI_Char* ABC_Sensor_QuiesceDevice_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_EnabledLogicalElement.RequestStateChange"),
};

static MI_CONST MI_ConstStringA ABC_Sensor_QuiesceDevice_MIReturn_Deprecated_qual_value =
{
    ABC_Sensor_QuiesceDevice_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(ABC_Sensor_QuiesceDevice_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier ABC_Sensor_QuiesceDevice_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &ABC_Sensor_QuiesceDevice_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Sensor_QuiesceDevice_MIReturn_quals[] =
{
    &ABC_Sensor_QuiesceDevice_MIReturn_Deprecated_qual,
};

/* parameter ABC_Sensor.QuiesceDevice(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_Sensor_QuiesceDevice_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    ABC_Sensor_QuiesceDevice_MIReturn_quals, /* qualifiers */
    MI_COUNT(ABC_Sensor_QuiesceDevice_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Sensor_QuiesceDevice, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_Sensor_QuiesceDevice_params[] =
{
    &ABC_Sensor_QuiesceDevice_MIReturn_param,
    &ABC_Sensor_QuiesceDevice_Quiesce_param,
};

/* method ABC_Sensor.QuiesceDevice() */
MI_CONST MI_MethodDecl ABC_Sensor_QuiesceDevice_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0071650D, /* code */
    MI_T("QuiesceDevice"), /* name */
    ABC_Sensor_QuiesceDevice_quals, /* qualifiers */
    MI_COUNT(ABC_Sensor_QuiesceDevice_quals), /* numQualifiers */
    ABC_Sensor_QuiesceDevice_params, /* parameters */
    MI_COUNT(ABC_Sensor_QuiesceDevice_params), /* numParameters */
    sizeof(ABC_Sensor_QuiesceDevice), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_Sensor_Invoke_QuiesceDevice, /* method */
};

/* parameter ABC_Sensor.SaveProperties(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_Sensor_SaveProperties_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Sensor_SaveProperties, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_Sensor_SaveProperties_params[] =
{
    &ABC_Sensor_SaveProperties_MIReturn_param,
};

/* method ABC_Sensor.SaveProperties() */
MI_CONST MI_MethodDecl ABC_Sensor_SaveProperties_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0073730E, /* code */
    MI_T("SaveProperties"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_Sensor_SaveProperties_params, /* parameters */
    MI_COUNT(ABC_Sensor_SaveProperties_params), /* numParameters */
    sizeof(ABC_Sensor_SaveProperties), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_Sensor_Invoke_SaveProperties, /* method */
};

/* parameter ABC_Sensor.RestoreProperties(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_Sensor_RestoreProperties_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_Sensor_RestoreProperties, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_Sensor_RestoreProperties_params[] =
{
    &ABC_Sensor_RestoreProperties_MIReturn_param,
};

/* method ABC_Sensor.RestoreProperties() */
MI_CONST MI_MethodDecl ABC_Sensor_RestoreProperties_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00727311, /* code */
    MI_T("RestoreProperties"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_Sensor_RestoreProperties_params, /* parameters */
    MI_COUNT(ABC_Sensor_RestoreProperties_params), /* numParameters */
    sizeof(ABC_Sensor_RestoreProperties), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_LogicalDevice"), /* origin */
    MI_T("CIM_LogicalDevice"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_Sensor_Invoke_RestoreProperties, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST ABC_Sensor_meths[] =
{
    &ABC_Sensor_RequestStateChange_rtti,
    &ABC_Sensor_SetPowerState_rtti,
    &ABC_Sensor_Reset_rtti,
    &ABC_Sensor_EnableDevice_rtti,
    &ABC_Sensor_OnlineDevice_rtti,
    &ABC_Sensor_QuiesceDevice_rtti,
    &ABC_Sensor_SaveProperties_rtti,
    &ABC_Sensor_RestoreProperties_rtti,
};

static MI_CONST MI_ProviderFT ABC_Sensor_funcs =
{
  (MI_ProviderFT_Load)ABC_Sensor_Load,
  (MI_ProviderFT_Unload)ABC_Sensor_Unload,
  (MI_ProviderFT_GetInstance)ABC_Sensor_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_Sensor_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_Sensor_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_Sensor_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_Sensor_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_Sensor_UMLPackagePath_qual_value = MI_T("CIM::Device::Sensors");

static MI_CONST MI_Qualifier ABC_Sensor_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_Sensor_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_Sensor_quals[] =
{
    &ABC_Sensor_UMLPackagePath_qual,
};

/* class ABC_Sensor */
MI_CONST MI_ClassDecl ABC_Sensor_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0061720A, /* code */
    MI_T("ABC_Sensor"), /* name */
    ABC_Sensor_quals, /* qualifiers */
    MI_COUNT(ABC_Sensor_quals), /* numQualifiers */
    ABC_Sensor_props, /* properties */
    MI_COUNT(ABC_Sensor_props), /* numProperties */
    sizeof(ABC_Sensor), /* size */
    MI_T("CIM_Sensor"), /* superClass */
    &CIM_Sensor_rtti, /* superClassDecl */
    ABC_Sensor_meths, /* methods */
    MI_COUNT(ABC_Sensor_meths), /* numMethods */
    &schemaDecl, /* schema */
    &ABC_Sensor_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_Collection
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Collection_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
};

static MI_CONST MI_Char* CIM_Collection_UMLPackagePath_qual_value = MI_T("CIM::Core::Collection");

static MI_CONST MI_Qualifier CIM_Collection_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Collection_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_Collection_Version_qual_value = MI_T("2.6.0");

static MI_CONST MI_Qualifier CIM_Collection_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Collection_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Collection_quals[] =
{
    &CIM_Collection_UMLPackagePath_qual,
    &CIM_Collection_Version_qual,
};

/* class CIM_Collection */
MI_CONST MI_ClassDecl CIM_Collection_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00636E0E, /* code */
    MI_T("CIM_Collection"), /* name */
    CIM_Collection_quals, /* qualifiers */
    MI_COUNT(CIM_Collection_quals), /* numQualifiers */
    CIM_Collection_props, /* properties */
    MI_COUNT(CIM_Collection_props), /* numProperties */
    sizeof(CIM_Collection), /* size */
    MI_T("CIM_ManagedElement"), /* superClass */
    &CIM_ManagedElement_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_SystemSpecificCollection
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_SystemSpecificCollection_InstanceID_Override_qual_value = MI_T("InstanceID");

static MI_CONST MI_Qualifier CIM_SystemSpecificCollection_InstanceID_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_SystemSpecificCollection_InstanceID_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_SystemSpecificCollection_InstanceID_quals[] =
{
    &CIM_SystemSpecificCollection_InstanceID_Override_qual,
};

/* property CIM_SystemSpecificCollection.InstanceID */
static MI_CONST MI_PropertyDecl CIM_SystemSpecificCollection_InstanceID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0069640A, /* code */
    MI_T("InstanceID"), /* name */
    CIM_SystemSpecificCollection_InstanceID_quals, /* qualifiers */
    MI_COUNT(CIM_SystemSpecificCollection_InstanceID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_SystemSpecificCollection, InstanceID), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_SystemSpecificCollection"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_SystemSpecificCollection_props[] =
{
    &CIM_SystemSpecificCollection_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
};

static MI_CONST MI_Char* CIM_SystemSpecificCollection_UMLPackagePath_qual_value = MI_T("CIM::Core::Collection");

static MI_CONST MI_Qualifier CIM_SystemSpecificCollection_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_SystemSpecificCollection_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_SystemSpecificCollection_Version_qual_value = MI_T("2.19.0");

static MI_CONST MI_Qualifier CIM_SystemSpecificCollection_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_SystemSpecificCollection_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_SystemSpecificCollection_quals[] =
{
    &CIM_SystemSpecificCollection_UMLPackagePath_qual,
    &CIM_SystemSpecificCollection_Version_qual,
};

/* class CIM_SystemSpecificCollection */
MI_CONST MI_ClassDecl CIM_SystemSpecificCollection_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00636E1C, /* code */
    MI_T("CIM_SystemSpecificCollection"), /* name */
    CIM_SystemSpecificCollection_quals, /* qualifiers */
    MI_COUNT(CIM_SystemSpecificCollection_quals), /* numQualifiers */
    CIM_SystemSpecificCollection_props, /* properties */
    MI_COUNT(CIM_SystemSpecificCollection_props), /* numProperties */
    sizeof(CIM_SystemSpecificCollection), /* size */
    MI_T("CIM_Collection"), /* superClass */
    &CIM_Collection_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_RedundancySet
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_RedundancySet_RedundancyStatus_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_RedundancySet.MinNumberNeeded"),
};

static MI_CONST MI_ConstStringA CIM_RedundancySet_RedundancyStatus_ModelCorrespondence_qual_value =
{
    CIM_RedundancySet_RedundancyStatus_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_RedundancySet_RedundancyStatus_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_RedundancySet_RedundancyStatus_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_RedundancySet_RedundancyStatus_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RedundancySet_RedundancyStatus_quals[] =
{
    &CIM_RedundancySet_RedundancyStatus_ModelCorrespondence_qual,
};

/* property CIM_RedundancySet.RedundancyStatus */
static MI_CONST MI_PropertyDecl CIM_RedundancySet_RedundancyStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00727310, /* code */
    MI_T("RedundancyStatus"), /* name */
    CIM_RedundancySet_RedundancyStatus_quals, /* qualifiers */
    MI_COUNT(CIM_RedundancySet_RedundancyStatus_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RedundancySet, RedundancyStatus), /* offset */
    MI_T("CIM_RedundancySet"), /* origin */
    MI_T("CIM_RedundancySet"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_RedundancySet_TypeOfSet_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_RedundancySet_TypeOfSet_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_RedundancySet_TypeOfSet_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_RedundancySet_TypeOfSet_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_RedundancySet.OtherTypeOfSet"),
};

static MI_CONST MI_ConstStringA CIM_RedundancySet_TypeOfSet_ModelCorrespondence_qual_value =
{
    CIM_RedundancySet_TypeOfSet_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_RedundancySet_TypeOfSet_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_RedundancySet_TypeOfSet_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_RedundancySet_TypeOfSet_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RedundancySet_TypeOfSet_quals[] =
{
    &CIM_RedundancySet_TypeOfSet_ArrayType_qual,
    &CIM_RedundancySet_TypeOfSet_ModelCorrespondence_qual,
};

/* property CIM_RedundancySet.TypeOfSet */
static MI_CONST MI_PropertyDecl CIM_RedundancySet_TypeOfSet_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00747409, /* code */
    MI_T("TypeOfSet"), /* name */
    CIM_RedundancySet_TypeOfSet_quals, /* qualifiers */
    MI_COUNT(CIM_RedundancySet_TypeOfSet_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RedundancySet, TypeOfSet), /* offset */
    MI_T("CIM_RedundancySet"), /* origin */
    MI_T("CIM_RedundancySet"), /* propagator */
    NULL,
};

static MI_CONST MI_Sint64 CIM_RedundancySet_MinNumberNeeded_MinValue_qual_value = MI_LL(0);

static MI_CONST MI_Qualifier CIM_RedundancySet_MinNumberNeeded_MinValue_qual =
{
    MI_T("MinValue"),
    MI_SINT64,
    0,
    &CIM_RedundancySet_MinNumberNeeded_MinValue_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RedundancySet_MinNumberNeeded_quals[] =
{
    &CIM_RedundancySet_MinNumberNeeded_MinValue_qual,
};

/* property CIM_RedundancySet.MinNumberNeeded */
static MI_CONST MI_PropertyDecl CIM_RedundancySet_MinNumberNeeded_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D640F, /* code */
    MI_T("MinNumberNeeded"), /* name */
    CIM_RedundancySet_MinNumberNeeded_quals, /* qualifiers */
    MI_COUNT(CIM_RedundancySet_MinNumberNeeded_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RedundancySet, MinNumberNeeded), /* offset */
    MI_T("CIM_RedundancySet"), /* origin */
    MI_T("CIM_RedundancySet"), /* propagator */
    NULL,
};

/* property CIM_RedundancySet.MaxNumberSupported */
static MI_CONST MI_PropertyDecl CIM_RedundancySet_MaxNumberSupported_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D6412, /* code */
    MI_T("MaxNumberSupported"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RedundancySet, MaxNumberSupported), /* offset */
    MI_T("CIM_RedundancySet"), /* origin */
    MI_T("CIM_RedundancySet"), /* propagator */
    NULL,
};

/* property CIM_RedundancySet.VendorIdentifyingInfo */
static MI_CONST MI_PropertyDecl CIM_RedundancySet_VendorIdentifyingInfo_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00766F15, /* code */
    MI_T("VendorIdentifyingInfo"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RedundancySet, VendorIdentifyingInfo), /* offset */
    MI_T("CIM_RedundancySet"), /* origin */
    MI_T("CIM_RedundancySet"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_RedundancySet_OtherTypeOfSet_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_RedundancySet_OtherTypeOfSet_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_RedundancySet_OtherTypeOfSet_ArrayType_qual_value
};

static MI_CONST MI_Char* CIM_RedundancySet_OtherTypeOfSet_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_RedundancySet.TypeOfSet"),
};

static MI_CONST MI_ConstStringA CIM_RedundancySet_OtherTypeOfSet_ModelCorrespondence_qual_value =
{
    CIM_RedundancySet_OtherTypeOfSet_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_RedundancySet_OtherTypeOfSet_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_RedundancySet_OtherTypeOfSet_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_RedundancySet_OtherTypeOfSet_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RedundancySet_OtherTypeOfSet_quals[] =
{
    &CIM_RedundancySet_OtherTypeOfSet_ArrayType_qual,
    &CIM_RedundancySet_OtherTypeOfSet_ModelCorrespondence_qual,
};

/* property CIM_RedundancySet.OtherTypeOfSet */
static MI_CONST MI_PropertyDecl CIM_RedundancySet_OtherTypeOfSet_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F740E, /* code */
    MI_T("OtherTypeOfSet"), /* name */
    CIM_RedundancySet_OtherTypeOfSet_quals, /* qualifiers */
    MI_COUNT(CIM_RedundancySet_OtherTypeOfSet_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RedundancySet, OtherTypeOfSet), /* offset */
    MI_T("CIM_RedundancySet"), /* origin */
    MI_T("CIM_RedundancySet"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_RedundancySet_LoadBalanceAlgorithm_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_RedundancySet.OtherLoadBalanceAlgorithm"),
};

static MI_CONST MI_ConstStringA CIM_RedundancySet_LoadBalanceAlgorithm_ModelCorrespondence_qual_value =
{
    CIM_RedundancySet_LoadBalanceAlgorithm_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_RedundancySet_LoadBalanceAlgorithm_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_RedundancySet_LoadBalanceAlgorithm_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_RedundancySet_LoadBalanceAlgorithm_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RedundancySet_LoadBalanceAlgorithm_quals[] =
{
    &CIM_RedundancySet_LoadBalanceAlgorithm_ModelCorrespondence_qual,
};

static MI_CONST MI_Uint16 CIM_RedundancySet_LoadBalanceAlgorithm_value = 2;

/* property CIM_RedundancySet.LoadBalanceAlgorithm */
static MI_CONST MI_PropertyDecl CIM_RedundancySet_LoadBalanceAlgorithm_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C6D14, /* code */
    MI_T("LoadBalanceAlgorithm"), /* name */
    CIM_RedundancySet_LoadBalanceAlgorithm_quals, /* qualifiers */
    MI_COUNT(CIM_RedundancySet_LoadBalanceAlgorithm_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RedundancySet, LoadBalanceAlgorithm), /* offset */
    MI_T("CIM_RedundancySet"), /* origin */
    MI_T("CIM_RedundancySet"), /* propagator */
    &CIM_RedundancySet_LoadBalanceAlgorithm_value,
};

static MI_CONST MI_Char* CIM_RedundancySet_OtherLoadBalanceAlgorithm_ModelCorrespondence_qual_data_value[] =
{
    MI_T("CIM_RedundancySet.LoadBalanceAlgorithm"),
};

static MI_CONST MI_ConstStringA CIM_RedundancySet_OtherLoadBalanceAlgorithm_ModelCorrespondence_qual_value =
{
    CIM_RedundancySet_OtherLoadBalanceAlgorithm_ModelCorrespondence_qual_data_value,
    MI_COUNT(CIM_RedundancySet_OtherLoadBalanceAlgorithm_ModelCorrespondence_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_RedundancySet_OtherLoadBalanceAlgorithm_ModelCorrespondence_qual =
{
    MI_T("ModelCorrespondence"),
    MI_STRINGA,
    0,
    &CIM_RedundancySet_OtherLoadBalanceAlgorithm_ModelCorrespondence_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RedundancySet_OtherLoadBalanceAlgorithm_quals[] =
{
    &CIM_RedundancySet_OtherLoadBalanceAlgorithm_ModelCorrespondence_qual,
};

/* property CIM_RedundancySet.OtherLoadBalanceAlgorithm */
static MI_CONST MI_PropertyDecl CIM_RedundancySet_OtherLoadBalanceAlgorithm_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6D19, /* code */
    MI_T("OtherLoadBalanceAlgorithm"), /* name */
    CIM_RedundancySet_OtherLoadBalanceAlgorithm_quals, /* qualifiers */
    MI_COUNT(CIM_RedundancySet_OtherLoadBalanceAlgorithm_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RedundancySet, OtherLoadBalanceAlgorithm), /* offset */
    MI_T("CIM_RedundancySet"), /* origin */
    MI_T("CIM_RedundancySet"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_RedundancySet_props[] =
{
    &CIM_SystemSpecificCollection_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_RedundancySet_RedundancyStatus_prop,
    &CIM_RedundancySet_TypeOfSet_prop,
    &CIM_RedundancySet_MinNumberNeeded_prop,
    &CIM_RedundancySet_MaxNumberSupported_prop,
    &CIM_RedundancySet_VendorIdentifyingInfo_prop,
    &CIM_RedundancySet_OtherTypeOfSet_prop,
    &CIM_RedundancySet_LoadBalanceAlgorithm_prop,
    &CIM_RedundancySet_OtherLoadBalanceAlgorithm_prop,
};

/* parameter CIM_RedundancySet.Failover(): FailoverFrom */
static MI_CONST MI_ParameterDecl CIM_RedundancySet_Failover_FailoverFrom_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00666D0C, /* code */
    MI_T("FailoverFrom"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(CIM_RedundancySet_Failover, FailoverFrom), /* offset */
};

/* parameter CIM_RedundancySet.Failover(): FailoverTo */
static MI_CONST MI_ParameterDecl CIM_RedundancySet_Failover_FailoverTo_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00666F0A, /* code */
    MI_T("FailoverTo"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(CIM_RedundancySet_Failover, FailoverTo), /* offset */
};

/* parameter CIM_RedundancySet.Failover(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_RedundancySet_Failover_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_RedundancySet_Failover, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_RedundancySet_Failover_params[] =
{
    &CIM_RedundancySet_Failover_MIReturn_param,
    &CIM_RedundancySet_Failover_FailoverFrom_param,
    &CIM_RedundancySet_Failover_FailoverTo_param,
};

/* method CIM_RedundancySet.Failover() */
MI_CONST MI_MethodDecl CIM_RedundancySet_Failover_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00667208, /* code */
    MI_T("Failover"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    CIM_RedundancySet_Failover_params, /* parameters */
    MI_COUNT(CIM_RedundancySet_Failover_params), /* numParameters */
    sizeof(CIM_RedundancySet_Failover), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_RedundancySet"), /* origin */
    MI_T("CIM_RedundancySet"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_RedundancySet_meths[] =
{
    &CIM_RedundancySet_Failover_rtti,
};

static MI_CONST MI_Char* CIM_RedundancySet_UMLPackagePath_qual_value = MI_T("CIM::Core::Redundancy");

static MI_CONST MI_Qualifier CIM_RedundancySet_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_RedundancySet_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_RedundancySet_Version_qual_value = MI_T("2.18.0");

static MI_CONST MI_Qualifier CIM_RedundancySet_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_RedundancySet_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_RedundancySet_quals[] =
{
    &CIM_RedundancySet_UMLPackagePath_qual,
    &CIM_RedundancySet_Version_qual,
};

/* class CIM_RedundancySet */
MI_CONST MI_ClassDecl CIM_RedundancySet_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00637411, /* code */
    MI_T("CIM_RedundancySet"), /* name */
    CIM_RedundancySet_quals, /* qualifiers */
    MI_COUNT(CIM_RedundancySet_quals), /* numQualifiers */
    CIM_RedundancySet_props, /* properties */
    MI_COUNT(CIM_RedundancySet_props), /* numProperties */
    sizeof(CIM_RedundancySet), /* size */
    MI_T("CIM_SystemSpecificCollection"), /* superClass */
    &CIM_SystemSpecificCollection_rtti, /* superClassDecl */
    CIM_RedundancySet_meths, /* methods */
    MI_COUNT(CIM_RedundancySet_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_IsSpare
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_IsSpare_Antecedent_Override_qual_value = MI_T("Antecedent");

static MI_CONST MI_Qualifier CIM_IsSpare_Antecedent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_IsSpare_Antecedent_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_IsSpare_Antecedent_quals[] =
{
    &CIM_IsSpare_Antecedent_Override_qual,
};

/* property CIM_IsSpare.Antecedent */
static MI_CONST MI_PropertyDecl CIM_IsSpare_Antecedent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0061740A, /* code */
    MI_T("Antecedent"), /* name */
    CIM_IsSpare_Antecedent_quals, /* qualifiers */
    MI_COUNT(CIM_IsSpare_Antecedent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(CIM_IsSpare, Antecedent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("CIM_IsSpare"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_IsSpare_Dependent_Override_qual_value = MI_T("Dependent");

static MI_CONST MI_Qualifier CIM_IsSpare_Dependent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_IsSpare_Dependent_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_IsSpare_Dependent_quals[] =
{
    &CIM_IsSpare_Dependent_Override_qual,
};

/* property CIM_IsSpare.Dependent */
static MI_CONST MI_PropertyDecl CIM_IsSpare_Dependent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00647409, /* code */
    MI_T("Dependent"), /* name */
    CIM_IsSpare_Dependent_quals, /* qualifiers */
    MI_COUNT(CIM_IsSpare_Dependent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_RedundancySet"), /* className */
    0, /* subscript */
    offsetof(CIM_IsSpare, Dependent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("CIM_IsSpare"), /* propagator */
    NULL,
};

/* property CIM_IsSpare.SpareStatus */
static MI_CONST MI_PropertyDecl CIM_IsSpare_SpareStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073730B, /* code */
    MI_T("SpareStatus"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_IsSpare, SpareStatus), /* offset */
    MI_T("CIM_IsSpare"), /* origin */
    MI_T("CIM_IsSpare"), /* propagator */
    NULL,
};

/* property CIM_IsSpare.FailoverSupported */
static MI_CONST MI_PropertyDecl CIM_IsSpare_FailoverSupported_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00666411, /* code */
    MI_T("FailoverSupported"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_IsSpare, FailoverSupported), /* offset */
    MI_T("CIM_IsSpare"), /* origin */
    MI_T("CIM_IsSpare"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_IsSpare_props[] =
{
    &CIM_IsSpare_Antecedent_prop,
    &CIM_IsSpare_Dependent_prop,
    &CIM_IsSpare_SpareStatus_prop,
    &CIM_IsSpare_FailoverSupported_prop,
};

static MI_CONST MI_Char* CIM_IsSpare_UMLPackagePath_qual_value = MI_T("CIM::Core::Redundancy");

static MI_CONST MI_Qualifier CIM_IsSpare_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_IsSpare_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_IsSpare_Version_qual_value = MI_T("2.10.0");

static MI_CONST MI_Qualifier CIM_IsSpare_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_IsSpare_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_IsSpare_quals[] =
{
    &CIM_IsSpare_UMLPackagePath_qual,
    &CIM_IsSpare_Version_qual,
};

/* class CIM_IsSpare */
MI_CONST MI_ClassDecl CIM_IsSpare_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x0063650B, /* code */
    MI_T("CIM_IsSpare"), /* name */
    CIM_IsSpare_quals, /* qualifiers */
    MI_COUNT(CIM_IsSpare_quals), /* numQualifiers */
    CIM_IsSpare_props, /* properties */
    MI_COUNT(CIM_IsSpare_props), /* numProperties */
    sizeof(CIM_IsSpare), /* size */
    MI_T("CIM_Dependency"), /* superClass */
    &CIM_Dependency_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ABC_IsSpare
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_IsSpare_props[] =
{
    &CIM_IsSpare_Antecedent_prop,
    &CIM_IsSpare_Dependent_prop,
    &CIM_IsSpare_SpareStatus_prop,
    &CIM_IsSpare_FailoverSupported_prop,
};

static void MI_CALL ABC_IsSpare_AssociatorInstances(
    ABC_IsSpare_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (CIM_ManagedElement_IsA(instanceName))
    {
        if (_Match(role, MI_T("Antecedent")) && 
            _Match(resultRole, MI_T("Dependent")))
        {
            ABC_IsSpare_AssociatorInstancesAntecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_ManagedElement*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (CIM_RedundancySet_IsA(instanceName))
    {
        if (_Match(role, MI_T("Dependent")) && 
            _Match(resultRole, MI_T("Antecedent")))
        {
            ABC_IsSpare_AssociatorInstancesDependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_RedundancySet*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL ABC_IsSpare_ReferenceInstances(
    ABC_IsSpare_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (CIM_ManagedElement_IsA(instanceName))
    {
        if (_Match(role, MI_T("Antecedent")))
        {
            ABC_IsSpare_ReferenceInstancesAntecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_ManagedElement*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (CIM_RedundancySet_IsA(instanceName))
    {
        if (_Match(role, MI_T("Dependent")))
        {
            ABC_IsSpare_ReferenceInstancesDependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_RedundancySet*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT ABC_IsSpare_funcs =
{
  (MI_ProviderFT_Load)ABC_IsSpare_Load,
  (MI_ProviderFT_Unload)ABC_IsSpare_Unload,
  (MI_ProviderFT_GetInstance)ABC_IsSpare_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_IsSpare_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_IsSpare_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_IsSpare_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_IsSpare_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)ABC_IsSpare_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)ABC_IsSpare_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_IsSpare_UMLPackagePath_qual_value = MI_T("CIM::Core::Redundancy");

static MI_CONST MI_Qualifier ABC_IsSpare_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_IsSpare_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_IsSpare_quals[] =
{
    &ABC_IsSpare_UMLPackagePath_qual,
};

/* class ABC_IsSpare */
MI_CONST MI_ClassDecl ABC_IsSpare_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x0061650B, /* code */
    MI_T("ABC_IsSpare"), /* name */
    ABC_IsSpare_quals, /* qualifiers */
    MI_COUNT(ABC_IsSpare_quals), /* numQualifiers */
    ABC_IsSpare_props, /* properties */
    MI_COUNT(ABC_IsSpare_props), /* numProperties */
    sizeof(ABC_IsSpare), /* size */
    MI_T("CIM_IsSpare"), /* superClass */
    &CIM_IsSpare_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &ABC_IsSpare_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_MemberOfCollection
**
**==============================================================================
*/

/* property CIM_MemberOfCollection.Collection */
static MI_CONST MI_PropertyDecl CIM_MemberOfCollection_Collection_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00636E0A, /* code */
    MI_T("Collection"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_Collection"), /* className */
    0, /* subscript */
    offsetof(CIM_MemberOfCollection, Collection), /* offset */
    MI_T("CIM_MemberOfCollection"), /* origin */
    MI_T("CIM_MemberOfCollection"), /* propagator */
    NULL,
};

/* property CIM_MemberOfCollection.Member */
static MI_CONST MI_PropertyDecl CIM_MemberOfCollection_Member_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006D7206, /* code */
    MI_T("Member"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(CIM_MemberOfCollection, Member), /* offset */
    MI_T("CIM_MemberOfCollection"), /* origin */
    MI_T("CIM_MemberOfCollection"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_MemberOfCollection_props[] =
{
    &CIM_MemberOfCollection_Collection_prop,
    &CIM_MemberOfCollection_Member_prop,
};

static MI_CONST MI_Char* CIM_MemberOfCollection_Version_qual_value = MI_T("2.6.0");

static MI_CONST MI_Qualifier CIM_MemberOfCollection_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_MemberOfCollection_Version_qual_value
};

static MI_CONST MI_Char* CIM_MemberOfCollection_UMLPackagePath_qual_value = MI_T("CIM::Core::Collection");

static MI_CONST MI_Qualifier CIM_MemberOfCollection_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_MemberOfCollection_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_MemberOfCollection_quals[] =
{
    &CIM_MemberOfCollection_Version_qual,
    &CIM_MemberOfCollection_UMLPackagePath_qual,
};

/* class CIM_MemberOfCollection */
MI_CONST MI_ClassDecl CIM_MemberOfCollection_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00636E16, /* code */
    MI_T("CIM_MemberOfCollection"), /* name */
    CIM_MemberOfCollection_quals, /* qualifiers */
    MI_COUNT(CIM_MemberOfCollection_quals), /* numQualifiers */
    CIM_MemberOfCollection_props, /* properties */
    MI_COUNT(CIM_MemberOfCollection_props), /* numProperties */
    sizeof(CIM_MemberOfCollection), /* size */
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
** ABC_MemberOfCollection
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_MemberOfCollection_props[] =
{
    &CIM_MemberOfCollection_Collection_prop,
    &CIM_MemberOfCollection_Member_prop,
};

static void MI_CALL ABC_MemberOfCollection_AssociatorInstances(
    ABC_MemberOfCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (CIM_Collection_IsA(instanceName))
    {
        if (_Match(role, MI_T("Collection")) && 
            _Match(resultRole, MI_T("Member")))
        {
            ABC_MemberOfCollection_AssociatorInstancesCollection(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_Collection*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (CIM_ManagedElement_IsA(instanceName))
    {
        if (_Match(role, MI_T("Member")) && 
            _Match(resultRole, MI_T("Collection")))
        {
            ABC_MemberOfCollection_AssociatorInstancesMember(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_ManagedElement*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL ABC_MemberOfCollection_ReferenceInstances(
    ABC_MemberOfCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (CIM_Collection_IsA(instanceName))
    {
        if (_Match(role, MI_T("Collection")))
        {
            ABC_MemberOfCollection_ReferenceInstancesCollection(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_Collection*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (CIM_ManagedElement_IsA(instanceName))
    {
        if (_Match(role, MI_T("Member")))
        {
            ABC_MemberOfCollection_ReferenceInstancesMember(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_ManagedElement*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT ABC_MemberOfCollection_funcs =
{
  (MI_ProviderFT_Load)ABC_MemberOfCollection_Load,
  (MI_ProviderFT_Unload)ABC_MemberOfCollection_Unload,
  (MI_ProviderFT_GetInstance)ABC_MemberOfCollection_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_MemberOfCollection_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_MemberOfCollection_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_MemberOfCollection_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_MemberOfCollection_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)ABC_MemberOfCollection_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)ABC_MemberOfCollection_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_MemberOfCollection_UMLPackagePath_qual_value = MI_T("CIM::Core::Collection");

static MI_CONST MI_Qualifier ABC_MemberOfCollection_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_MemberOfCollection_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_MemberOfCollection_quals[] =
{
    &ABC_MemberOfCollection_UMLPackagePath_qual,
};

/* class ABC_MemberOfCollection */
MI_CONST MI_ClassDecl ABC_MemberOfCollection_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00616E16, /* code */
    MI_T("ABC_MemberOfCollection"), /* name */
    ABC_MemberOfCollection_quals, /* qualifiers */
    MI_COUNT(ABC_MemberOfCollection_quals), /* numQualifiers */
    ABC_MemberOfCollection_props, /* properties */
    MI_COUNT(ABC_MemberOfCollection_props), /* numProperties */
    sizeof(ABC_MemberOfCollection), /* size */
    MI_T("CIM_MemberOfCollection"), /* superClass */
    &CIM_MemberOfCollection_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &ABC_MemberOfCollection_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_OwningCollectionElement
**
**==============================================================================
*/

static MI_CONST MI_Uint32 CIM_OwningCollectionElement_OwningElement_Max_qual_value = 1U;

static MI_CONST MI_Qualifier CIM_OwningCollectionElement_OwningElement_Max_qual =
{
    MI_T("Max"),
    MI_UINT32,
    0,
    &CIM_OwningCollectionElement_OwningElement_Max_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_OwningCollectionElement_OwningElement_quals[] =
{
    &CIM_OwningCollectionElement_OwningElement_Max_qual,
};

/* property CIM_OwningCollectionElement.OwningElement */
static MI_CONST MI_PropertyDecl CIM_OwningCollectionElement_OwningElement_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006F740D, /* code */
    MI_T("OwningElement"), /* name */
    CIM_OwningCollectionElement_OwningElement_quals, /* qualifiers */
    MI_COUNT(CIM_OwningCollectionElement_OwningElement_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(CIM_OwningCollectionElement, OwningElement), /* offset */
    MI_T("CIM_OwningCollectionElement"), /* origin */
    MI_T("CIM_OwningCollectionElement"), /* propagator */
    NULL,
};

/* property CIM_OwningCollectionElement.OwnedElement */
static MI_CONST MI_PropertyDecl CIM_OwningCollectionElement_OwnedElement_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006F740C, /* code */
    MI_T("OwnedElement"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_Collection"), /* className */
    0, /* subscript */
    offsetof(CIM_OwningCollectionElement, OwnedElement), /* offset */
    MI_T("CIM_OwningCollectionElement"), /* origin */
    MI_T("CIM_OwningCollectionElement"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_OwningCollectionElement_props[] =
{
    &CIM_OwningCollectionElement_OwningElement_prop,
    &CIM_OwningCollectionElement_OwnedElement_prop,
};

static MI_CONST MI_Char* CIM_OwningCollectionElement_Version_qual_value = MI_T("2.18.0");

static MI_CONST MI_Qualifier CIM_OwningCollectionElement_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_OwningCollectionElement_Version_qual_value
};

static MI_CONST MI_Char* CIM_OwningCollectionElement_UMLPackagePath_qual_value = MI_T("CIM::Core::Collection");

static MI_CONST MI_Qualifier CIM_OwningCollectionElement_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_OwningCollectionElement_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_OwningCollectionElement_quals[] =
{
    &CIM_OwningCollectionElement_Version_qual,
    &CIM_OwningCollectionElement_UMLPackagePath_qual,
};

/* class CIM_OwningCollectionElement */
MI_CONST MI_ClassDecl CIM_OwningCollectionElement_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x0063741B, /* code */
    MI_T("CIM_OwningCollectionElement"), /* name */
    CIM_OwningCollectionElement_quals, /* qualifiers */
    MI_COUNT(CIM_OwningCollectionElement_quals), /* numQualifiers */
    CIM_OwningCollectionElement_props, /* properties */
    MI_COUNT(CIM_OwningCollectionElement_props), /* numProperties */
    sizeof(CIM_OwningCollectionElement), /* size */
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
** ABC_OwningCollectionElement
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_OwningCollectionElement_props[] =
{
    &CIM_OwningCollectionElement_OwningElement_prop,
    &CIM_OwningCollectionElement_OwnedElement_prop,
};

static void MI_CALL ABC_OwningCollectionElement_AssociatorInstances(
    ABC_OwningCollectionElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (CIM_ManagedElement_IsA(instanceName))
    {
        if (_Match(role, MI_T("OwningElement")) && 
            _Match(resultRole, MI_T("OwnedElement")))
        {
            ABC_OwningCollectionElement_AssociatorInstancesOwningElement(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_ManagedElement*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (CIM_Collection_IsA(instanceName))
    {
        if (_Match(role, MI_T("OwnedElement")) && 
            _Match(resultRole, MI_T("OwningElement")))
        {
            ABC_OwningCollectionElement_AssociatorInstancesOwnedElement(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_Collection*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL ABC_OwningCollectionElement_ReferenceInstances(
    ABC_OwningCollectionElement_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (CIM_ManagedElement_IsA(instanceName))
    {
        if (_Match(role, MI_T("OwningElement")))
        {
            ABC_OwningCollectionElement_ReferenceInstancesOwningElement(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_ManagedElement*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (CIM_Collection_IsA(instanceName))
    {
        if (_Match(role, MI_T("OwnedElement")))
        {
            ABC_OwningCollectionElement_ReferenceInstancesOwnedElement(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_Collection*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT ABC_OwningCollectionElement_funcs =
{
  (MI_ProviderFT_Load)ABC_OwningCollectionElement_Load,
  (MI_ProviderFT_Unload)ABC_OwningCollectionElement_Unload,
  (MI_ProviderFT_GetInstance)ABC_OwningCollectionElement_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_OwningCollectionElement_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_OwningCollectionElement_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_OwningCollectionElement_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_OwningCollectionElement_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)ABC_OwningCollectionElement_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)ABC_OwningCollectionElement_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_OwningCollectionElement_UMLPackagePath_qual_value = MI_T("CIM::Core::Collection");

static MI_CONST MI_Qualifier ABC_OwningCollectionElement_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_OwningCollectionElement_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_OwningCollectionElement_quals[] =
{
    &ABC_OwningCollectionElement_UMLPackagePath_qual,
};

/* class ABC_OwningCollectionElement */
MI_CONST MI_ClassDecl ABC_OwningCollectionElement_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x0061741B, /* code */
    MI_T("ABC_OwningCollectionElement"), /* name */
    ABC_OwningCollectionElement_quals, /* qualifiers */
    MI_COUNT(ABC_OwningCollectionElement_quals), /* numQualifiers */
    ABC_OwningCollectionElement_props, /* properties */
    MI_COUNT(ABC_OwningCollectionElement_props), /* numProperties */
    sizeof(ABC_OwningCollectionElement), /* size */
    MI_T("CIM_OwningCollectionElement"), /* superClass */
    &CIM_OwningCollectionElement_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &ABC_OwningCollectionElement_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_HostedDependency
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_HostedDependency_Antecedent_Override_qual_value = MI_T("Antecedent");

static MI_CONST MI_Qualifier CIM_HostedDependency_Antecedent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_HostedDependency_Antecedent_Override_qual_value
};

static MI_CONST MI_Uint32 CIM_HostedDependency_Antecedent_Max_qual_value = 1U;

static MI_CONST MI_Qualifier CIM_HostedDependency_Antecedent_Max_qual =
{
    MI_T("Max"),
    MI_UINT32,
    0,
    &CIM_HostedDependency_Antecedent_Max_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_HostedDependency_Antecedent_quals[] =
{
    &CIM_HostedDependency_Antecedent_Override_qual,
    &CIM_HostedDependency_Antecedent_Max_qual,
};

/* property CIM_HostedDependency.Antecedent */
static MI_CONST MI_PropertyDecl CIM_HostedDependency_Antecedent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0061740A, /* code */
    MI_T("Antecedent"), /* name */
    CIM_HostedDependency_Antecedent_quals, /* qualifiers */
    MI_COUNT(CIM_HostedDependency_Antecedent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(CIM_HostedDependency, Antecedent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("CIM_HostedDependency"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_HostedDependency_Dependent_Override_qual_value = MI_T("Dependent");

static MI_CONST MI_Qualifier CIM_HostedDependency_Dependent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_HostedDependency_Dependent_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_HostedDependency_Dependent_quals[] =
{
    &CIM_HostedDependency_Dependent_Override_qual,
};

/* property CIM_HostedDependency.Dependent */
static MI_CONST MI_PropertyDecl CIM_HostedDependency_Dependent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00647409, /* code */
    MI_T("Dependent"), /* name */
    CIM_HostedDependency_Dependent_quals, /* qualifiers */
    MI_COUNT(CIM_HostedDependency_Dependent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(CIM_HostedDependency, Dependent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("CIM_HostedDependency"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_HostedDependency_props[] =
{
    &CIM_HostedDependency_Antecedent_prop,
    &CIM_HostedDependency_Dependent_prop,
};

static MI_CONST MI_Char* CIM_HostedDependency_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_HostedDependency_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_HostedDependency_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_HostedDependency_Version_qual_value = MI_T("2.8.0");

static MI_CONST MI_Qualifier CIM_HostedDependency_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_HostedDependency_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_HostedDependency_quals[] =
{
    &CIM_HostedDependency_UMLPackagePath_qual,
    &CIM_HostedDependency_Version_qual,
};

/* class CIM_HostedDependency */
MI_CONST MI_ClassDecl CIM_HostedDependency_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00637914, /* code */
    MI_T("CIM_HostedDependency"), /* name */
    CIM_HostedDependency_quals, /* qualifiers */
    MI_COUNT(CIM_HostedDependency_quals), /* numQualifiers */
    CIM_HostedDependency_props, /* properties */
    MI_COUNT(CIM_HostedDependency_props), /* numProperties */
    sizeof(CIM_HostedDependency), /* size */
    MI_T("CIM_Dependency"), /* superClass */
    &CIM_Dependency_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_HostedCollection
**
**==============================================================================
*/

static MI_CONST MI_Uint32 CIM_HostedCollection_Antecedent_Max_qual_value = 1U;

static MI_CONST MI_Qualifier CIM_HostedCollection_Antecedent_Max_qual =
{
    MI_T("Max"),
    MI_UINT32,
    0,
    &CIM_HostedCollection_Antecedent_Max_qual_value
};

static MI_CONST MI_Char* CIM_HostedCollection_Antecedent_Override_qual_value = MI_T("Antecedent");

static MI_CONST MI_Qualifier CIM_HostedCollection_Antecedent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_HostedCollection_Antecedent_Override_qual_value
};

static MI_CONST MI_Uint32 CIM_HostedCollection_Antecedent_Min_qual_value = 1U;

static MI_CONST MI_Qualifier CIM_HostedCollection_Antecedent_Min_qual =
{
    MI_T("Min"),
    MI_UINT32,
    0,
    &CIM_HostedCollection_Antecedent_Min_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_HostedCollection_Antecedent_quals[] =
{
    &CIM_HostedCollection_Antecedent_Max_qual,
    &CIM_HostedCollection_Antecedent_Override_qual,
    &CIM_HostedCollection_Antecedent_Min_qual,
};

/* property CIM_HostedCollection.Antecedent */
static MI_CONST MI_PropertyDecl CIM_HostedCollection_Antecedent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0061740A, /* code */
    MI_T("Antecedent"), /* name */
    CIM_HostedCollection_Antecedent_quals, /* qualifiers */
    MI_COUNT(CIM_HostedCollection_Antecedent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_System"), /* className */
    0, /* subscript */
    offsetof(CIM_HostedCollection, Antecedent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("CIM_HostedCollection"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_HostedCollection_Dependent_Override_qual_value = MI_T("Dependent");

static MI_CONST MI_Qualifier CIM_HostedCollection_Dependent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_HostedCollection_Dependent_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_HostedCollection_Dependent_quals[] =
{
    &CIM_HostedCollection_Dependent_Override_qual,
};

/* property CIM_HostedCollection.Dependent */
static MI_CONST MI_PropertyDecl CIM_HostedCollection_Dependent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00647409, /* code */
    MI_T("Dependent"), /* name */
    CIM_HostedCollection_Dependent_quals, /* qualifiers */
    MI_COUNT(CIM_HostedCollection_Dependent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_SystemSpecificCollection"), /* className */
    0, /* subscript */
    offsetof(CIM_HostedCollection, Dependent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("CIM_HostedCollection"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_HostedCollection_props[] =
{
    &CIM_HostedCollection_Antecedent_prop,
    &CIM_HostedCollection_Dependent_prop,
};

static MI_CONST MI_Char* CIM_HostedCollection_UMLPackagePath_qual_value = MI_T("CIM::Core::Collection");

static MI_CONST MI_Qualifier CIM_HostedCollection_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_HostedCollection_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_HostedCollection_Version_qual_value = MI_T("2.10.0");

static MI_CONST MI_Qualifier CIM_HostedCollection_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_HostedCollection_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_HostedCollection_quals[] =
{
    &CIM_HostedCollection_UMLPackagePath_qual,
    &CIM_HostedCollection_Version_qual,
};

/* class CIM_HostedCollection */
MI_CONST MI_ClassDecl CIM_HostedCollection_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00636E14, /* code */
    MI_T("CIM_HostedCollection"), /* name */
    CIM_HostedCollection_quals, /* qualifiers */
    MI_COUNT(CIM_HostedCollection_quals), /* numQualifiers */
    CIM_HostedCollection_props, /* properties */
    MI_COUNT(CIM_HostedCollection_props), /* numProperties */
    sizeof(CIM_HostedCollection), /* size */
    MI_T("CIM_HostedDependency"), /* superClass */
    &CIM_HostedDependency_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ABC_HostedCollection
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_HostedCollection_props[] =
{
    &CIM_HostedCollection_Antecedent_prop,
    &CIM_HostedCollection_Dependent_prop,
};

static void MI_CALL ABC_HostedCollection_AssociatorInstances(
    ABC_HostedCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* resultClass,
    const MI_Char* role,
    const MI_Char* resultRole,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (CIM_System_IsA(instanceName))
    {
        if (_Match(role, MI_T("Antecedent")) && 
            _Match(resultRole, MI_T("Dependent")))
        {
            ABC_HostedCollection_AssociatorInstancesAntecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_System*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (CIM_SystemSpecificCollection_IsA(instanceName))
    {
        if (_Match(role, MI_T("Dependent")) && 
            _Match(resultRole, MI_T("Antecedent")))
        {
            ABC_HostedCollection_AssociatorInstancesDependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_SystemSpecificCollection*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL ABC_HostedCollection_ReferenceInstances(
    ABC_HostedCollection_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (CIM_System_IsA(instanceName))
    {
        if (_Match(role, MI_T("Antecedent")))
        {
            ABC_HostedCollection_ReferenceInstancesAntecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_System*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (CIM_SystemSpecificCollection_IsA(instanceName))
    {
        if (_Match(role, MI_T("Dependent")))
        {
            ABC_HostedCollection_ReferenceInstancesDependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (CIM_SystemSpecificCollection*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT ABC_HostedCollection_funcs =
{
  (MI_ProviderFT_Load)ABC_HostedCollection_Load,
  (MI_ProviderFT_Unload)ABC_HostedCollection_Unload,
  (MI_ProviderFT_GetInstance)ABC_HostedCollection_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_HostedCollection_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_HostedCollection_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_HostedCollection_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_HostedCollection_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)ABC_HostedCollection_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)ABC_HostedCollection_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_HostedCollection_UMLPackagePath_qual_value = MI_T("CIM::Core::Collection");

static MI_CONST MI_Qualifier ABC_HostedCollection_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_HostedCollection_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_HostedCollection_quals[] =
{
    &ABC_HostedCollection_UMLPackagePath_qual,
};

/* class ABC_HostedCollection */
MI_CONST MI_ClassDecl ABC_HostedCollection_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00616E14, /* code */
    MI_T("ABC_HostedCollection"), /* name */
    ABC_HostedCollection_quals, /* qualifiers */
    MI_COUNT(ABC_HostedCollection_quals), /* numQualifiers */
    ABC_HostedCollection_props, /* properties */
    MI_COUNT(ABC_HostedCollection_props), /* numProperties */
    sizeof(ABC_HostedCollection), /* size */
    MI_T("CIM_HostedCollection"), /* superClass */
    &CIM_HostedCollection_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &ABC_HostedCollection_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** ABC_RedundancySet
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST ABC_RedundancySet_props[] =
{
    &CIM_SystemSpecificCollection_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_RedundancySet_RedundancyStatus_prop,
    &CIM_RedundancySet_TypeOfSet_prop,
    &CIM_RedundancySet_MinNumberNeeded_prop,
    &CIM_RedundancySet_MaxNumberSupported_prop,
    &CIM_RedundancySet_VendorIdentifyingInfo_prop,
    &CIM_RedundancySet_OtherTypeOfSet_prop,
    &CIM_RedundancySet_LoadBalanceAlgorithm_prop,
    &CIM_RedundancySet_OtherLoadBalanceAlgorithm_prop,
};

/* parameter ABC_RedundancySet.Failover(): FailoverFrom */
static MI_CONST MI_ParameterDecl ABC_RedundancySet_Failover_FailoverFrom_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00666D0C, /* code */
    MI_T("FailoverFrom"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(ABC_RedundancySet_Failover, FailoverFrom), /* offset */
};

/* parameter ABC_RedundancySet.Failover(): FailoverTo */
static MI_CONST MI_ParameterDecl ABC_RedundancySet_Failover_FailoverTo_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00666F0A, /* code */
    MI_T("FailoverTo"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(ABC_RedundancySet_Failover, FailoverTo), /* offset */
};

/* parameter ABC_RedundancySet.Failover(): MIReturn */
static MI_CONST MI_ParameterDecl ABC_RedundancySet_Failover_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(ABC_RedundancySet_Failover, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST ABC_RedundancySet_Failover_params[] =
{
    &ABC_RedundancySet_Failover_MIReturn_param,
    &ABC_RedundancySet_Failover_FailoverFrom_param,
    &ABC_RedundancySet_Failover_FailoverTo_param,
};

/* method ABC_RedundancySet.Failover() */
MI_CONST MI_MethodDecl ABC_RedundancySet_Failover_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00667208, /* code */
    MI_T("Failover"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    ABC_RedundancySet_Failover_params, /* parameters */
    MI_COUNT(ABC_RedundancySet_Failover_params), /* numParameters */
    sizeof(ABC_RedundancySet_Failover), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_RedundancySet"), /* origin */
    MI_T("CIM_RedundancySet"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)ABC_RedundancySet_Invoke_Failover, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST ABC_RedundancySet_meths[] =
{
    &ABC_RedundancySet_Failover_rtti,
};

static MI_CONST MI_ProviderFT ABC_RedundancySet_funcs =
{
  (MI_ProviderFT_Load)ABC_RedundancySet_Load,
  (MI_ProviderFT_Unload)ABC_RedundancySet_Unload,
  (MI_ProviderFT_GetInstance)ABC_RedundancySet_GetInstance,
  (MI_ProviderFT_EnumerateInstances)ABC_RedundancySet_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)ABC_RedundancySet_CreateInstance,
  (MI_ProviderFT_ModifyInstance)ABC_RedundancySet_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)ABC_RedundancySet_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* ABC_RedundancySet_UMLPackagePath_qual_value = MI_T("CIM::Core::Redundancy");

static MI_CONST MI_Qualifier ABC_RedundancySet_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &ABC_RedundancySet_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST ABC_RedundancySet_quals[] =
{
    &ABC_RedundancySet_UMLPackagePath_qual,
};

/* class ABC_RedundancySet */
MI_CONST MI_ClassDecl ABC_RedundancySet_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00617411, /* code */
    MI_T("ABC_RedundancySet"), /* name */
    ABC_RedundancySet_quals, /* qualifiers */
    MI_COUNT(ABC_RedundancySet_quals), /* numQualifiers */
    ABC_RedundancySet_props, /* properties */
    MI_COUNT(ABC_RedundancySet_props), /* numProperties */
    sizeof(ABC_RedundancySet), /* size */
    MI_T("CIM_RedundancySet"), /* superClass */
    &CIM_RedundancySet_rtti, /* superClassDecl */
    ABC_RedundancySet_meths, /* methods */
    MI_COUNT(ABC_RedundancySet_meths), /* numMethods */
    &schemaDecl, /* schema */
    &ABC_RedundancySet_funcs, /* functions */
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
    &ABC_AssociatedCooling_rtti,
    &ABC_AssociatedSensor_rtti,
    &ABC_ComputerSystem_rtti,
    &ABC_ElementCapabilities_rtti,
    &ABC_ElementConformsToProfile_rtti,
    &ABC_EnabledLogicalElementCapabilities_rtti,
    &ABC_Fan_rtti,
    &ABC_HostedCollection_rtti,
    &ABC_IsSpare_rtti,
    &ABC_ManagedSystemElement_rtti,
    &ABC_MemberOfCollection_rtti,
    &ABC_NumericSensor_rtti,
    &ABC_OwningCollectionElement_rtti,
    &ABC_PhysicalPackage_rtti,
    &ABC_Realizes_rtti,
    &ABC_RedundancySet_rtti,
    &ABC_RegisteredProfile_rtti,
    &ABC_Sensor_rtti,
    &ABC_SystemDevice_rtti,
    &CIM_AssociatedCooling_rtti,
    &CIM_AssociatedSensor_rtti,
    &CIM_Capabilities_rtti,
    &CIM_Collection_rtti,
    &CIM_Component_rtti,
    &CIM_ComputerSystem_rtti,
    &CIM_ConcreteJob_rtti,
    &CIM_CoolingDevice_rtti,
    &CIM_Dependency_rtti,
    &CIM_ElementCapabilities_rtti,
    &CIM_ElementConformsToProfile_rtti,
    &CIM_EnabledLogicalElement_rtti,
    &CIM_EnabledLogicalElementCapabilities_rtti,
    &CIM_Error_rtti,
    &CIM_Fan_rtti,
    &CIM_HostedCollection_rtti,
    &CIM_HostedDependency_rtti,
    &CIM_IsSpare_rtti,
    &CIM_Job_rtti,
    &CIM_LogicalDevice_rtti,
    &CIM_LogicalElement_rtti,
    &CIM_ManagedElement_rtti,
    &CIM_ManagedSystemElement_rtti,
    &CIM_MemberOfCollection_rtti,
    &CIM_NumericSensor_rtti,
    &CIM_OwningCollectionElement_rtti,
    &CIM_PhysicalElement_rtti,
    &CIM_PhysicalPackage_rtti,
    &CIM_Realizes_rtti,
    &CIM_RedundancySet_rtti,
    &CIM_RegisteredProfile_rtti,
    &CIM_Sensor_rtti,
    &CIM_System_rtti,
    &CIM_SystemComponent_rtti,
    &CIM_SystemDevice_rtti,
    &CIM_SystemSpecificCollection_rtti,
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

