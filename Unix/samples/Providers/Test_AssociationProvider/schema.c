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
#include "Test_PhysicalDisk.h"
#include "Test_LogicalDisk.h"
#include "Test_VirtualDisk.h"
#include "Test_AssociationPhysicalLogicalDisk.h"
#include "Test_AssociationLogicalVirtualDisk.h"

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
** Test_PhysicalDisk
**
**==============================================================================
*/

/* property Test_PhysicalDisk.serialNumber */
static MI_CONST MI_PropertyDecl Test_PhysicalDisk_serialNumber_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0073720C, /* code */
    MI_T("serialNumber"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_PhysicalDisk, serialNumber), /* offset */
    MI_T("Test_PhysicalDisk"), /* origin */
    MI_T("Test_PhysicalDisk"), /* propagator */
    NULL,
};

/* property Test_PhysicalDisk.numSectors */
static MI_CONST MI_PropertyDecl Test_PhysicalDisk_numSectors_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E730A, /* code */
    MI_T("numSectors"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_PhysicalDisk, numSectors), /* offset */
    MI_T("Test_PhysicalDisk"), /* origin */
    MI_T("Test_PhysicalDisk"), /* propagator */
    NULL,
};

/* property Test_PhysicalDisk.sectorSize */
static MI_CONST MI_PropertyDecl Test_PhysicalDisk_sectorSize_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073650A, /* code */
    MI_T("sectorSize"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_PhysicalDisk, sectorSize), /* offset */
    MI_T("Test_PhysicalDisk"), /* origin */
    MI_T("Test_PhysicalDisk"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Test_PhysicalDisk_props[] =
{
    &Test_PhysicalDisk_serialNumber_prop,
    &Test_PhysicalDisk_numSectors_prop,
    &Test_PhysicalDisk_sectorSize_prop,
};

static MI_CONST MI_ProviderFT Test_PhysicalDisk_funcs =
{
  (MI_ProviderFT_Load)Test_PhysicalDisk_Load,
  (MI_ProviderFT_Unload)Test_PhysicalDisk_Unload,
  (MI_ProviderFT_GetInstance)Test_PhysicalDisk_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Test_PhysicalDisk_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Test_PhysicalDisk_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Test_PhysicalDisk_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Test_PhysicalDisk_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Test_PhysicalDisk */
MI_CONST MI_ClassDecl Test_PhysicalDisk_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00746B11, /* code */
    MI_T("Test_PhysicalDisk"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Test_PhysicalDisk_props, /* properties */
    MI_COUNT(Test_PhysicalDisk_props), /* numProperties */
    sizeof(Test_PhysicalDisk), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Test_PhysicalDisk_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** Test_LogicalDisk
**
**==============================================================================
*/

/* property Test_LogicalDisk.diskID */
static MI_CONST MI_PropertyDecl Test_LogicalDisk_diskID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00646406, /* code */
    MI_T("diskID"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_LogicalDisk, diskID), /* offset */
    MI_T("Test_LogicalDisk"), /* origin */
    MI_T("Test_LogicalDisk"), /* propagator */
    NULL,
};

/* property Test_LogicalDisk.driveLetter */
static MI_CONST MI_PropertyDecl Test_LogicalDisk_driveLetter_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0064720B, /* code */
    MI_T("driveLetter"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_LogicalDisk, driveLetter), /* offset */
    MI_T("Test_LogicalDisk"), /* origin */
    MI_T("Test_LogicalDisk"), /* propagator */
    NULL,
};

/* property Test_LogicalDisk.sizeInGb */
static MI_CONST MI_PropertyDecl Test_LogicalDisk_sizeInGb_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736208, /* code */
    MI_T("sizeInGb"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_LogicalDisk, sizeInGb), /* offset */
    MI_T("Test_LogicalDisk"), /* origin */
    MI_T("Test_LogicalDisk"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Test_LogicalDisk_props[] =
{
    &Test_LogicalDisk_diskID_prop,
    &Test_LogicalDisk_driveLetter_prop,
    &Test_LogicalDisk_sizeInGb_prop,
};

static MI_CONST MI_ProviderFT Test_LogicalDisk_funcs =
{
  (MI_ProviderFT_Load)Test_LogicalDisk_Load,
  (MI_ProviderFT_Unload)Test_LogicalDisk_Unload,
  (MI_ProviderFT_GetInstance)Test_LogicalDisk_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Test_LogicalDisk_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Test_LogicalDisk_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Test_LogicalDisk_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Test_LogicalDisk_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Test_LogicalDisk */
MI_CONST MI_ClassDecl Test_LogicalDisk_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00746B10, /* code */
    MI_T("Test_LogicalDisk"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Test_LogicalDisk_props, /* properties */
    MI_COUNT(Test_LogicalDisk_props), /* numProperties */
    sizeof(Test_LogicalDisk), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Test_LogicalDisk_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** Test_VirtualDisk
**
**==============================================================================
*/

/* property Test_VirtualDisk.filePath */
static MI_CONST MI_PropertyDecl Test_VirtualDisk_filePath_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00666808, /* code */
    MI_T("filePath"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Test_VirtualDisk, filePath), /* offset */
    MI_T("Test_VirtualDisk"), /* origin */
    MI_T("Test_VirtualDisk"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Test_VirtualDisk_props[] =
{
    &Test_PhysicalDisk_serialNumber_prop,
    &Test_PhysicalDisk_numSectors_prop,
    &Test_PhysicalDisk_sectorSize_prop,
    &Test_VirtualDisk_filePath_prop,
};

static MI_CONST MI_ProviderFT Test_VirtualDisk_funcs =
{
  (MI_ProviderFT_Load)Test_VirtualDisk_Load,
  (MI_ProviderFT_Unload)Test_VirtualDisk_Unload,
  (MI_ProviderFT_GetInstance)Test_VirtualDisk_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Test_VirtualDisk_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Test_VirtualDisk_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Test_VirtualDisk_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Test_VirtualDisk_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Test_VirtualDisk */
MI_CONST MI_ClassDecl Test_VirtualDisk_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00746B10, /* code */
    MI_T("Test_VirtualDisk"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Test_VirtualDisk_props, /* properties */
    MI_COUNT(Test_VirtualDisk_props), /* numProperties */
    sizeof(Test_VirtualDisk), /* size */
    MI_T("Test_PhysicalDisk"), /* superClass */
    &Test_PhysicalDisk_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Test_VirtualDisk_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** Test_AssociationPhysicalLogicalDisk
**
**==============================================================================
*/

/* property Test_AssociationPhysicalLogicalDisk.antecedent */
static MI_CONST MI_PropertyDecl Test_AssociationPhysicalLogicalDisk_antecedent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0061740A, /* code */
    MI_T("antecedent"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Test_PhysicalDisk"), /* className */
    0, /* subscript */
    offsetof(Test_AssociationPhysicalLogicalDisk, antecedent), /* offset */
    MI_T("Test_AssociationPhysicalLogicalDisk"), /* origin */
    MI_T("Test_AssociationPhysicalLogicalDisk"), /* propagator */
    NULL,
};

/* property Test_AssociationPhysicalLogicalDisk.dependent */
static MI_CONST MI_PropertyDecl Test_AssociationPhysicalLogicalDisk_dependent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00647409, /* code */
    MI_T("dependent"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Test_LogicalDisk"), /* className */
    0, /* subscript */
    offsetof(Test_AssociationPhysicalLogicalDisk, dependent), /* offset */
    MI_T("Test_AssociationPhysicalLogicalDisk"), /* origin */
    MI_T("Test_AssociationPhysicalLogicalDisk"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Test_AssociationPhysicalLogicalDisk_props[] =
{
    &Test_AssociationPhysicalLogicalDisk_antecedent_prop,
    &Test_AssociationPhysicalLogicalDisk_dependent_prop,
};

static void MI_CALL Test_AssociationPhysicalLogicalDisk_AssociatorInstances(
    Test_AssociationPhysicalLogicalDisk_Self* self,
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
    if (Test_PhysicalDisk_IsA(instanceName))
    {
        if (_Match(role, MI_T("antecedent")) && 
            _Match(resultRole, MI_T("dependent")))
        {
            Test_AssociationPhysicalLogicalDisk_AssociatorInstancesantecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (Test_PhysicalDisk*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (Test_LogicalDisk_IsA(instanceName))
    {
        if (_Match(role, MI_T("dependent")) && 
            _Match(resultRole, MI_T("antecedent")))
        {
            Test_AssociationPhysicalLogicalDisk_AssociatorInstancesdependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (Test_LogicalDisk*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL Test_AssociationPhysicalLogicalDisk_ReferenceInstances(
    Test_AssociationPhysicalLogicalDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (Test_PhysicalDisk_IsA(instanceName))
    {
        if (_Match(role, MI_T("antecedent")))
        {
            Test_AssociationPhysicalLogicalDisk_ReferenceInstancesantecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (Test_PhysicalDisk*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (Test_LogicalDisk_IsA(instanceName))
    {
        if (_Match(role, MI_T("dependent")))
        {
            Test_AssociationPhysicalLogicalDisk_ReferenceInstancesdependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (Test_LogicalDisk*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT Test_AssociationPhysicalLogicalDisk_funcs =
{
  (MI_ProviderFT_Load)Test_AssociationPhysicalLogicalDisk_Load,
  (MI_ProviderFT_Unload)Test_AssociationPhysicalLogicalDisk_Unload,
  (MI_ProviderFT_GetInstance)Test_AssociationPhysicalLogicalDisk_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Test_AssociationPhysicalLogicalDisk_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Test_AssociationPhysicalLogicalDisk_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Test_AssociationPhysicalLogicalDisk_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Test_AssociationPhysicalLogicalDisk_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)Test_AssociationPhysicalLogicalDisk_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)Test_AssociationPhysicalLogicalDisk_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Test_AssociationPhysicalLogicalDisk */
MI_CONST MI_ClassDecl Test_AssociationPhysicalLogicalDisk_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00746B23, /* code */
    MI_T("Test_AssociationPhysicalLogicalDisk"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Test_AssociationPhysicalLogicalDisk_props, /* properties */
    MI_COUNT(Test_AssociationPhysicalLogicalDisk_props), /* numProperties */
    sizeof(Test_AssociationPhysicalLogicalDisk), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Test_AssociationPhysicalLogicalDisk_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** Test_AssociationLogicalVirtualDisk
**
**==============================================================================
*/

/* property Test_AssociationLogicalVirtualDisk.antecedent */
static MI_CONST MI_PropertyDecl Test_AssociationLogicalVirtualDisk_antecedent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0061740A, /* code */
    MI_T("antecedent"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Test_LogicalDisk"), /* className */
    0, /* subscript */
    offsetof(Test_AssociationLogicalVirtualDisk, antecedent), /* offset */
    MI_T("Test_AssociationLogicalVirtualDisk"), /* origin */
    MI_T("Test_AssociationLogicalVirtualDisk"), /* propagator */
    NULL,
};

/* property Test_AssociationLogicalVirtualDisk.dependent */
static MI_CONST MI_PropertyDecl Test_AssociationLogicalVirtualDisk_dependent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00647409, /* code */
    MI_T("dependent"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("Test_VirtualDisk"), /* className */
    0, /* subscript */
    offsetof(Test_AssociationLogicalVirtualDisk, dependent), /* offset */
    MI_T("Test_AssociationLogicalVirtualDisk"), /* origin */
    MI_T("Test_AssociationLogicalVirtualDisk"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Test_AssociationLogicalVirtualDisk_props[] =
{
    &Test_AssociationLogicalVirtualDisk_antecedent_prop,
    &Test_AssociationLogicalVirtualDisk_dependent_prop,
};

static void MI_CALL Test_AssociationLogicalVirtualDisk_AssociatorInstances(
    Test_AssociationLogicalVirtualDisk_Self* self,
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
    if (Test_LogicalDisk_IsA(instanceName))
    {
        if (_Match(role, MI_T("antecedent")) && 
            _Match(resultRole, MI_T("dependent")))
        {
            Test_AssociationLogicalVirtualDisk_AssociatorInstancesantecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (Test_LogicalDisk*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (Test_VirtualDisk_IsA(instanceName))
    {
        if (_Match(role, MI_T("dependent")) && 
            _Match(resultRole, MI_T("antecedent")))
        {
            Test_AssociationLogicalVirtualDisk_AssociatorInstancesdependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (Test_VirtualDisk*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL Test_AssociationLogicalVirtualDisk_ReferenceInstances(
    Test_AssociationLogicalVirtualDisk_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (Test_LogicalDisk_IsA(instanceName))
    {
        if (_Match(role, MI_T("antecedent")))
        {
            Test_AssociationLogicalVirtualDisk_ReferenceInstancesantecedent(
                self, 
                context, 
                nameSpace, 
                className, 
                (Test_LogicalDisk*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (Test_VirtualDisk_IsA(instanceName))
    {
        if (_Match(role, MI_T("dependent")))
        {
            Test_AssociationLogicalVirtualDisk_ReferenceInstancesdependent(
                self, 
                context, 
                nameSpace, 
                className, 
                (Test_VirtualDisk*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT Test_AssociationLogicalVirtualDisk_funcs =
{
  (MI_ProviderFT_Load)Test_AssociationLogicalVirtualDisk_Load,
  (MI_ProviderFT_Unload)Test_AssociationLogicalVirtualDisk_Unload,
  (MI_ProviderFT_GetInstance)Test_AssociationLogicalVirtualDisk_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Test_AssociationLogicalVirtualDisk_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Test_AssociationLogicalVirtualDisk_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Test_AssociationLogicalVirtualDisk_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Test_AssociationLogicalVirtualDisk_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)Test_AssociationLogicalVirtualDisk_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)Test_AssociationLogicalVirtualDisk_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Test_AssociationLogicalVirtualDisk */
MI_CONST MI_ClassDecl Test_AssociationLogicalVirtualDisk_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00746B22, /* code */
    MI_T("Test_AssociationLogicalVirtualDisk"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Test_AssociationLogicalVirtualDisk_props, /* properties */
    MI_COUNT(Test_AssociationLogicalVirtualDisk_props), /* numProperties */
    sizeof(Test_AssociationLogicalVirtualDisk), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Test_AssociationLogicalVirtualDisk_funcs, /* functions */
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
    &Test_AssociationLogicalVirtualDisk_rtti,
    &Test_AssociationPhysicalLogicalDisk_rtti,
    &Test_LogicalDisk_rtti,
    &Test_PhysicalDisk_rtti,
    &Test_VirtualDisk_rtti,
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

