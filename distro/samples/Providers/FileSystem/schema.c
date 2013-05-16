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
#include "MSFT_DataFile.h"
#include "MSFT_Directory.h"
#include "MSFT_DirectoryContainsFile.h"

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
** MSFT_LogicalFile
**
**==============================================================================
*/

/* property MSFT_LogicalFile.Name */
static MI_CONST MI_PropertyDecl MSFT_LogicalFile_Name_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_LogicalFile, Name), /* offset */
    MI_T("MSFT_LogicalFile"), /* origin */
    MI_T("MSFT_LogicalFile"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_LogicalFile_props[] =
{
    &MSFT_LogicalFile_Name_prop,
};

/* class MSFT_LogicalFile */
MI_CONST MI_ClassDecl MSFT_LogicalFile_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D6510, /* code */
    MI_T("MSFT_LogicalFile"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_LogicalFile_props, /* properties */
    MI_COUNT(MSFT_LogicalFile_props), /* numProperties */
    sizeof(MSFT_LogicalFile), /* size */
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
** MSFT_DataFile
**
**==============================================================================
*/

/* property MSFT_DataFile.Size */
static MI_CONST MI_PropertyDecl MSFT_DataFile_Size_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736504, /* code */
    MI_T("Size"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_DataFile, Size), /* offset */
    MI_T("MSFT_DataFile"), /* origin */
    MI_T("MSFT_DataFile"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_DataFile_props[] =
{
    &MSFT_LogicalFile_Name_prop,
    &MSFT_DataFile_Size_prop,
};

static MI_CONST MI_ProviderFT MSFT_DataFile_funcs =
{
  (MI_ProviderFT_Load)MSFT_DataFile_Load,
  (MI_ProviderFT_Unload)MSFT_DataFile_Unload,
  (MI_ProviderFT_GetInstance)MSFT_DataFile_GetInstance,
  (MI_ProviderFT_EnumerateInstances)MSFT_DataFile_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)MSFT_DataFile_CreateInstance,
  (MI_ProviderFT_ModifyInstance)MSFT_DataFile_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)MSFT_DataFile_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class MSFT_DataFile */
MI_CONST MI_ClassDecl MSFT_DataFile_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D650D, /* code */
    MI_T("MSFT_DataFile"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_DataFile_props, /* properties */
    MI_COUNT(MSFT_DataFile_props), /* numProperties */
    sizeof(MSFT_DataFile), /* size */
    MI_T("MSFT_LogicalFile"), /* superClass */
    &MSFT_LogicalFile_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MSFT_DataFile_funcs, /* functions */
};

/*
**==============================================================================
**
** MSFT_Directory
**
**==============================================================================
*/

/* property MSFT_Directory.Count */
static MI_CONST MI_PropertyDecl MSFT_Directory_Count_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637405, /* code */
    MI_T("Count"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Directory, Count), /* offset */
    MI_T("MSFT_Directory"), /* origin */
    MI_T("MSFT_Directory"), /* propagator */
    NULL,
};

/* property MSFT_Directory.FileNames */
static MI_CONST MI_PropertyDecl MSFT_Directory_FileNames_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00667309, /* code */
    MI_T("FileNames"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MSFT_Directory, FileNames), /* offset */
    MI_T("MSFT_Directory"), /* origin */
    MI_T("MSFT_Directory"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_Directory_props[] =
{
    &MSFT_LogicalFile_Name_prop,
    &MSFT_Directory_Count_prop,
    &MSFT_Directory_FileNames_prop,
};

static MI_CONST MI_ProviderFT MSFT_Directory_funcs =
{
  (MI_ProviderFT_Load)MSFT_Directory_Load,
  (MI_ProviderFT_Unload)MSFT_Directory_Unload,
  (MI_ProviderFT_GetInstance)MSFT_Directory_GetInstance,
  (MI_ProviderFT_EnumerateInstances)MSFT_Directory_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)MSFT_Directory_CreateInstance,
  (MI_ProviderFT_ModifyInstance)MSFT_Directory_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)MSFT_Directory_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class MSFT_Directory */
MI_CONST MI_ClassDecl MSFT_Directory_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D790E, /* code */
    MI_T("MSFT_Directory"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_Directory_props, /* properties */
    MI_COUNT(MSFT_Directory_props), /* numProperties */
    sizeof(MSFT_Directory), /* size */
    MI_T("MSFT_LogicalFile"), /* superClass */
    &MSFT_LogicalFile_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MSFT_Directory_funcs, /* functions */
};

/*
**==============================================================================
**
** MSFT_DirectoryContainsFile
**
**==============================================================================
*/

/* property MSFT_DirectoryContainsFile.GroupComponent */
static MI_CONST MI_PropertyDecl MSFT_DirectoryContainsFile_GroupComponent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0067740E, /* code */
    MI_T("GroupComponent"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("MSFT_Directory"), /* className */
    0, /* subscript */
    offsetof(MSFT_DirectoryContainsFile, GroupComponent), /* offset */
    MI_T("MSFT_DirectoryContainsFile"), /* origin */
    MI_T("MSFT_DirectoryContainsFile"), /* propagator */
    NULL,
};

/* property MSFT_DirectoryContainsFile.PartComponent */
static MI_CONST MI_PropertyDecl MSFT_DirectoryContainsFile_PartComponent_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0070740D, /* code */
    MI_T("PartComponent"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("MSFT_LogicalFile"), /* className */
    0, /* subscript */
    offsetof(MSFT_DirectoryContainsFile, PartComponent), /* offset */
    MI_T("MSFT_DirectoryContainsFile"), /* origin */
    MI_T("MSFT_DirectoryContainsFile"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MSFT_DirectoryContainsFile_props[] =
{
    &MSFT_DirectoryContainsFile_GroupComponent_prop,
    &MSFT_DirectoryContainsFile_PartComponent_prop,
};

static void MI_CALL MSFT_DirectoryContainsFile_AssociatorInstances(
    MSFT_DirectoryContainsFile_Self* self,
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
    if (MSFT_Directory_IsA(instanceName))
    {
        if (_Match(role, MI_T("GroupComponent")) && 
            _Match(resultRole, MI_T("PartComponent")))
        {
            MSFT_DirectoryContainsFile_AssociatorInstancesGroupComponent(
                self, 
                context, 
                nameSpace, 
                className, 
                (MSFT_Directory*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (MSFT_LogicalFile_IsA(instanceName))
    {
        if (_Match(role, MI_T("PartComponent")) && 
            _Match(resultRole, MI_T("GroupComponent")))
        {
            MSFT_DirectoryContainsFile_AssociatorInstancesPartComponent(
                self, 
                context, 
                nameSpace, 
                className, 
                (MSFT_LogicalFile*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL MSFT_DirectoryContainsFile_ReferenceInstances(
    MSFT_DirectoryContainsFile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (MSFT_Directory_IsA(instanceName))
    {
        if (_Match(role, MI_T("GroupComponent")))
        {
            MSFT_DirectoryContainsFile_ReferenceInstancesGroupComponent(
                self, 
                context, 
                nameSpace, 
                className, 
                (MSFT_Directory*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (MSFT_LogicalFile_IsA(instanceName))
    {
        if (_Match(role, MI_T("PartComponent")))
        {
            MSFT_DirectoryContainsFile_ReferenceInstancesPartComponent(
                self, 
                context, 
                nameSpace, 
                className, 
                (MSFT_LogicalFile*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT MSFT_DirectoryContainsFile_funcs =
{
  (MI_ProviderFT_Load)MSFT_DirectoryContainsFile_Load,
  (MI_ProviderFT_Unload)MSFT_DirectoryContainsFile_Unload,
  (MI_ProviderFT_GetInstance)MSFT_DirectoryContainsFile_GetInstance,
  (MI_ProviderFT_EnumerateInstances)MSFT_DirectoryContainsFile_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)MSFT_DirectoryContainsFile_CreateInstance,
  (MI_ProviderFT_ModifyInstance)MSFT_DirectoryContainsFile_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)MSFT_DirectoryContainsFile_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)MSFT_DirectoryContainsFile_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)MSFT_DirectoryContainsFile_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class MSFT_DirectoryContainsFile */
MI_CONST MI_ClassDecl MSFT_DirectoryContainsFile_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x006D651A, /* code */
    MI_T("MSFT_DirectoryContainsFile"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MSFT_DirectoryContainsFile_props, /* properties */
    MI_COUNT(MSFT_DirectoryContainsFile_props), /* numProperties */
    sizeof(MSFT_DirectoryContainsFile), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &MSFT_DirectoryContainsFile_funcs, /* functions */
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
    &MSFT_DataFile_rtti,
    &MSFT_Directory_rtti,
    &MSFT_DirectoryContainsFile_rtti,
    &MSFT_LogicalFile_rtti,
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

