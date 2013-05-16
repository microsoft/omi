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
#include "PS_Module.h"
#include "PS_ModuleFile.h"
#include "PS_ModuleToModuleFile.h"

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

static MI_CONST MI_QualifierDecl ClassVersion_qual_decl =
{
    MI_T("ClassVersion"), /* name */
    MI_STRING, /* type */
    MI_FLAG_ASSOCIATION|MI_FLAG_CLASS|MI_FLAG_INDICATION, /* scope */
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED, /* flavor */
    0, /* subscript */
    NULL, /* value */
};

static MI_QualifierDecl MI_CONST* MI_CONST qualifierDecls[] =
{
    &ClassVersion_qual_decl,
};

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

static MI_CONST MI_Boolean CIM_ManagedElement_Abstract_qual_value = 1;

static MI_CONST MI_Qualifier CIM_ManagedElement_Abstract_qual =
{
    MI_T("Abstract"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ManagedElement_Abstract_qual_value
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
    &CIM_ManagedElement_Abstract_qual,
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
** PS_Module
**
**==============================================================================
*/

static MI_CONST MI_Boolean PS_Module_InstanceID_Key_qual_value = 1;

static MI_CONST MI_Qualifier PS_Module_InstanceID_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &PS_Module_InstanceID_Key_qual_value
};

static MI_CONST MI_Char* PS_Module_InstanceID_Override_qual_value = MI_T("instanceID");

static MI_CONST MI_Qualifier PS_Module_InstanceID_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &PS_Module_InstanceID_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST PS_Module_InstanceID_quals[] =
{
    &PS_Module_InstanceID_Key_qual,
    &PS_Module_InstanceID_Override_qual,
};

/* property PS_Module.InstanceID */
static MI_CONST MI_PropertyDecl PS_Module_InstanceID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0069640A, /* code */
    MI_T("InstanceID"), /* name */
    PS_Module_InstanceID_quals, /* qualifiers */
    MI_COUNT(PS_Module_InstanceID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(PS_Module, InstanceID), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("PS_Module"), /* propagator */
    NULL,
};

/* property PS_Module.ModuleName */
static MI_CONST MI_PropertyDecl PS_Module_ModuleName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D650A, /* code */
    MI_T("ModuleName"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(PS_Module, ModuleName), /* offset */
    MI_T("PS_Module"), /* origin */
    MI_T("PS_Module"), /* propagator */
    NULL,
};

/* property PS_Module.moduleType */
static MI_CONST MI_PropertyDecl PS_Module_moduleType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D650A, /* code */
    MI_T("moduleType"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(PS_Module, moduleType), /* offset */
    MI_T("PS_Module"), /* origin */
    MI_T("PS_Module"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean PS_Module_moduleManifestFileData_Octetstring_qual_value = 1;

static MI_CONST MI_Qualifier PS_Module_moduleManifestFileData_Octetstring_qual =
{
    MI_T("Octetstring"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &PS_Module_moduleManifestFileData_Octetstring_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST PS_Module_moduleManifestFileData_quals[] =
{
    &PS_Module_moduleManifestFileData_Octetstring_qual,
};

/* property PS_Module.moduleManifestFileData */
static MI_CONST MI_PropertyDecl PS_Module_moduleManifestFileData_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D6116, /* code */
    MI_T("moduleManifestFileData"), /* name */
    PS_Module_moduleManifestFileData_quals, /* qualifiers */
    MI_COUNT(PS_Module_moduleManifestFileData_quals), /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(PS_Module, moduleManifestFileData), /* offset */
    MI_T("PS_Module"), /* origin */
    MI_T("PS_Module"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST PS_Module_props[] =
{
    &PS_Module_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &PS_Module_ModuleName_prop,
    &PS_Module_moduleType_prop,
    &PS_Module_moduleManifestFileData_prop,
};

static MI_CONST MI_ProviderFT PS_Module_funcs =
{
  (MI_ProviderFT_Load)PS_Module_Load,
  (MI_ProviderFT_Unload)PS_Module_Unload,
  (MI_ProviderFT_GetInstance)PS_Module_GetInstance,
  (MI_ProviderFT_EnumerateInstances)PS_Module_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)PS_Module_CreateInstance,
  (MI_ProviderFT_ModifyInstance)PS_Module_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)PS_Module_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* PS_Module_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier PS_Module_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &PS_Module_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* PS_Module_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier PS_Module_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &PS_Module_ClassVersion_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST PS_Module_quals[] =
{
    &PS_Module_UMLPackagePath_qual,
    &PS_Module_ClassVersion_qual,
};

/* class PS_Module */
MI_CONST MI_ClassDecl PS_Module_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00706509, /* code */
    MI_T("PS_Module"), /* name */
    PS_Module_quals, /* qualifiers */
    MI_COUNT(PS_Module_quals), /* numQualifiers */
    PS_Module_props, /* properties */
    MI_COUNT(PS_Module_props), /* numProperties */
    sizeof(PS_Module), /* size */
    MI_T("CIM_ManagedElement"), /* superClass */
    &CIM_ManagedElement_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &PS_Module_funcs, /* functions */
};

/*
**==============================================================================
**
** PS_ModuleFile
**
**==============================================================================
*/

static MI_CONST MI_Boolean PS_ModuleFile_InstanceID_Key_qual_value = 1;

static MI_CONST MI_Qualifier PS_ModuleFile_InstanceID_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &PS_ModuleFile_InstanceID_Key_qual_value
};

static MI_CONST MI_Char* PS_ModuleFile_InstanceID_Override_qual_value = MI_T("instanceID");

static MI_CONST MI_Qualifier PS_ModuleFile_InstanceID_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &PS_ModuleFile_InstanceID_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST PS_ModuleFile_InstanceID_quals[] =
{
    &PS_ModuleFile_InstanceID_Key_qual,
    &PS_ModuleFile_InstanceID_Override_qual,
};

/* property PS_ModuleFile.InstanceID */
static MI_CONST MI_PropertyDecl PS_ModuleFile_InstanceID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0069640A, /* code */
    MI_T("InstanceID"), /* name */
    PS_ModuleFile_InstanceID_quals, /* qualifiers */
    MI_COUNT(PS_ModuleFile_InstanceID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(PS_ModuleFile, InstanceID), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("PS_ModuleFile"), /* propagator */
    NULL,
};

/* property PS_ModuleFile.FileName */
static MI_CONST MI_PropertyDecl PS_ModuleFile_FileName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00666508, /* code */
    MI_T("FileName"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(PS_ModuleFile, FileName), /* offset */
    MI_T("PS_ModuleFile"), /* origin */
    MI_T("PS_ModuleFile"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean PS_ModuleFile_FileData_Octetstring_qual_value = 1;

static MI_CONST MI_Qualifier PS_ModuleFile_FileData_Octetstring_qual =
{
    MI_T("Octetstring"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &PS_ModuleFile_FileData_Octetstring_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST PS_ModuleFile_FileData_quals[] =
{
    &PS_ModuleFile_FileData_Octetstring_qual,
};

/* property PS_ModuleFile.FileData */
static MI_CONST MI_PropertyDecl PS_ModuleFile_FileData_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00666108, /* code */
    MI_T("FileData"), /* name */
    PS_ModuleFile_FileData_quals, /* qualifiers */
    MI_COUNT(PS_ModuleFile_FileData_quals), /* numQualifiers */
    MI_UINT8A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(PS_ModuleFile, FileData), /* offset */
    MI_T("PS_ModuleFile"), /* origin */
    MI_T("PS_ModuleFile"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST PS_ModuleFile_props[] =
{
    &PS_ModuleFile_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &PS_ModuleFile_FileName_prop,
    &PS_ModuleFile_FileData_prop,
};

static MI_CONST MI_ProviderFT PS_ModuleFile_funcs =
{
  (MI_ProviderFT_Load)PS_ModuleFile_Load,
  (MI_ProviderFT_Unload)PS_ModuleFile_Unload,
  (MI_ProviderFT_GetInstance)PS_ModuleFile_GetInstance,
  (MI_ProviderFT_EnumerateInstances)PS_ModuleFile_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)PS_ModuleFile_CreateInstance,
  (MI_ProviderFT_ModifyInstance)PS_ModuleFile_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)PS_ModuleFile_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* PS_ModuleFile_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier PS_ModuleFile_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &PS_ModuleFile_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* PS_ModuleFile_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier PS_ModuleFile_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &PS_ModuleFile_ClassVersion_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST PS_ModuleFile_quals[] =
{
    &PS_ModuleFile_UMLPackagePath_qual,
    &PS_ModuleFile_ClassVersion_qual,
};

/* class PS_ModuleFile */
MI_CONST MI_ClassDecl PS_ModuleFile_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0070650D, /* code */
    MI_T("PS_ModuleFile"), /* name */
    PS_ModuleFile_quals, /* qualifiers */
    MI_COUNT(PS_ModuleFile_quals), /* numQualifiers */
    PS_ModuleFile_props, /* properties */
    MI_COUNT(PS_ModuleFile_props), /* numProperties */
    sizeof(PS_ModuleFile), /* size */
    MI_T("CIM_ManagedElement"), /* superClass */
    &CIM_ManagedElement_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &PS_ModuleFile_funcs, /* functions */
};

/*
**==============================================================================
**
** CIM_Dependency
**
**==============================================================================
*/

static MI_CONST MI_Boolean CIM_Dependency_Antecedent_Key_qual_value = 1;

static MI_CONST MI_Qualifier CIM_Dependency_Antecedent_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Dependency_Antecedent_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Dependency_Antecedent_quals[] =
{
    &CIM_Dependency_Antecedent_Key_qual,
};

/* property CIM_Dependency.Antecedent */
static MI_CONST MI_PropertyDecl CIM_Dependency_Antecedent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0061740A, /* code */
    MI_T("Antecedent"), /* name */
    CIM_Dependency_Antecedent_quals, /* qualifiers */
    MI_COUNT(CIM_Dependency_Antecedent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ManagedElement"), /* className */
    0, /* subscript */
    offsetof(CIM_Dependency, Antecedent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("CIM_Dependency"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean CIM_Dependency_Dependent_Key_qual_value = 1;

static MI_CONST MI_Qualifier CIM_Dependency_Dependent_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Dependency_Dependent_Key_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Dependency_Dependent_quals[] =
{
    &CIM_Dependency_Dependent_Key_qual,
};

/* property CIM_Dependency.Dependent */
static MI_CONST MI_PropertyDecl CIM_Dependency_Dependent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00647409, /* code */
    MI_T("Dependent"), /* name */
    CIM_Dependency_Dependent_quals, /* qualifiers */
    MI_COUNT(CIM_Dependency_Dependent_quals), /* numQualifiers */
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

static MI_CONST MI_Boolean CIM_Dependency_Association_qual_value = 1;

static MI_CONST MI_Qualifier CIM_Dependency_Association_qual =
{
    MI_T("Association"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_Dependency_Association_qual_value
};

static MI_CONST MI_Boolean CIM_Dependency_Abstract_qual_value = 1;

static MI_CONST MI_Qualifier CIM_Dependency_Abstract_qual =
{
    MI_T("Abstract"),
    MI_BOOLEAN,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_Dependency_Abstract_qual_value
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
    &CIM_Dependency_Association_qual,
    &CIM_Dependency_Abstract_qual,
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
};

/*
**==============================================================================
**
** PS_ModuleToModuleFile
**
**==============================================================================
*/

static MI_CONST MI_Boolean PS_ModuleToModuleFile_Antecedent_Key_qual_value = 1;

static MI_CONST MI_Qualifier PS_ModuleToModuleFile_Antecedent_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &PS_ModuleToModuleFile_Antecedent_Key_qual_value
};

static MI_CONST MI_Char* PS_ModuleToModuleFile_Antecedent_Override_qual_value = MI_T("Antecedent");

static MI_CONST MI_Qualifier PS_ModuleToModuleFile_Antecedent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &PS_ModuleToModuleFile_Antecedent_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST PS_ModuleToModuleFile_Antecedent_quals[] =
{
    &PS_ModuleToModuleFile_Antecedent_Key_qual,
    &PS_ModuleToModuleFile_Antecedent_Override_qual,
};

/* property PS_ModuleToModuleFile.Antecedent */
static MI_CONST MI_PropertyDecl PS_ModuleToModuleFile_Antecedent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0061740A, /* code */
    MI_T("Antecedent"), /* name */
    PS_ModuleToModuleFile_Antecedent_quals, /* qualifiers */
    MI_COUNT(PS_ModuleToModuleFile_Antecedent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("PS_Module"), /* className */
    0, /* subscript */
    offsetof(PS_ModuleToModuleFile, Antecedent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("PS_ModuleToModuleFile"), /* propagator */
    NULL,
};

static MI_CONST MI_Boolean PS_ModuleToModuleFile_Dependent_Key_qual_value = 1;

static MI_CONST MI_Qualifier PS_ModuleToModuleFile_Dependent_Key_qual =
{
    MI_T("Key"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &PS_ModuleToModuleFile_Dependent_Key_qual_value
};

static MI_CONST MI_Char* PS_ModuleToModuleFile_Dependent_Override_qual_value = MI_T("Dependent");

static MI_CONST MI_Qualifier PS_ModuleToModuleFile_Dependent_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &PS_ModuleToModuleFile_Dependent_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST PS_ModuleToModuleFile_Dependent_quals[] =
{
    &PS_ModuleToModuleFile_Dependent_Key_qual,
    &PS_ModuleToModuleFile_Dependent_Override_qual,
};

/* property PS_ModuleToModuleFile.Dependent */
static MI_CONST MI_PropertyDecl PS_ModuleToModuleFile_Dependent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00647409, /* code */
    MI_T("Dependent"), /* name */
    PS_ModuleToModuleFile_Dependent_quals, /* qualifiers */
    MI_COUNT(PS_ModuleToModuleFile_Dependent_quals), /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("PS_ModuleFile"), /* className */
    0, /* subscript */
    offsetof(PS_ModuleToModuleFile, Dependent), /* offset */
    MI_T("CIM_Dependency"), /* origin */
    MI_T("PS_ModuleToModuleFile"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST PS_ModuleToModuleFile_props[] =
{
    &PS_ModuleToModuleFile_Antecedent_prop,
    &PS_ModuleToModuleFile_Dependent_prop,
};

static void MI_CALL PS_ModuleToModuleFile_AssociatorInstances(
    PS_ModuleToModuleFile_Self* self,
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
    if (PS_Module_IsA(instanceName))
    {
        if (_Match(role, MI_T("Antecedent")) && 
            _Match(resultRole, MI_T("Dependent")))
        {
            PS_ModuleToModuleFile_AssociatorInstancesAntecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (PS_Module*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (PS_ModuleFile_IsA(instanceName))
    {
        if (_Match(role, MI_T("Dependent")) && 
            _Match(resultRole, MI_T("Antecedent")))
        {
            PS_ModuleToModuleFile_AssociatorInstancesDependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (PS_ModuleFile*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL PS_ModuleToModuleFile_ReferenceInstances(
    PS_ModuleToModuleFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (PS_Module_IsA(instanceName))
    {
        if (_Match(role, MI_T("Antecedent")))
        {
            PS_ModuleToModuleFile_ReferenceInstancesAntecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (PS_Module*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (PS_ModuleFile_IsA(instanceName))
    {
        if (_Match(role, MI_T("Dependent")))
        {
            PS_ModuleToModuleFile_ReferenceInstancesDependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (PS_ModuleFile*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT PS_ModuleToModuleFile_funcs =
{
  (MI_ProviderFT_Load)PS_ModuleToModuleFile_Load,
  (MI_ProviderFT_Unload)PS_ModuleToModuleFile_Unload,
  (MI_ProviderFT_GetInstance)PS_ModuleToModuleFile_GetInstance,
  (MI_ProviderFT_EnumerateInstances)PS_ModuleToModuleFile_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)PS_ModuleToModuleFile_CreateInstance,
  (MI_ProviderFT_ModifyInstance)PS_ModuleToModuleFile_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)PS_ModuleToModuleFile_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)PS_ModuleToModuleFile_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)PS_ModuleToModuleFile_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Boolean PS_ModuleToModuleFile_Association_qual_value = 1;

static MI_CONST MI_Qualifier PS_ModuleToModuleFile_Association_qual =
{
    MI_T("Association"),
    MI_BOOLEAN,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &PS_ModuleToModuleFile_Association_qual_value
};

static MI_CONST MI_Char* PS_ModuleToModuleFile_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier PS_ModuleToModuleFile_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &PS_ModuleToModuleFile_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* PS_ModuleToModuleFile_ClassVersion_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier PS_ModuleToModuleFile_ClassVersion_qual =
{
    MI_T("ClassVersion"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &PS_ModuleToModuleFile_ClassVersion_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST PS_ModuleToModuleFile_quals[] =
{
    &PS_ModuleToModuleFile_Association_qual,
    &PS_ModuleToModuleFile_UMLPackagePath_qual,
    &PS_ModuleToModuleFile_ClassVersion_qual,
};

/* class PS_ModuleToModuleFile */
MI_CONST MI_ClassDecl PS_ModuleToModuleFile_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00706515, /* code */
    MI_T("PS_ModuleToModuleFile"), /* name */
    PS_ModuleToModuleFile_quals, /* qualifiers */
    MI_COUNT(PS_ModuleToModuleFile_quals), /* numQualifiers */
    PS_ModuleToModuleFile_props, /* properties */
    MI_COUNT(PS_ModuleToModuleFile_props), /* numProperties */
    sizeof(PS_ModuleToModuleFile), /* size */
    MI_T("CIM_Dependency"), /* superClass */
    &CIM_Dependency_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &PS_ModuleToModuleFile_funcs, /* functions */
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
    &CIM_Dependency_rtti,
    &CIM_ManagedElement_rtti,
    &PS_Module_rtti,
    &PS_ModuleFile_rtti,
    &PS_ModuleToModuleFile_rtti,
};

MI_SchemaDecl schemaDecl =
{
    qualifierDecls, /* qualifierDecls */
    MI_COUNT(qualifierDecls), /* numQualifierDecls */
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

