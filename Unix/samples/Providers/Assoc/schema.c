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
#include "XYZ_Widget.h"
#include "XYZ_Gadget.h"
#include "XYZ_Assoc.h"
#include "XYZ_Widget2.h"
#include "XYZ_Gadget2.h"
#include "XYZ_Assoc2.h"

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
** XYZ_Widget
**
**==============================================================================
*/

/* property XYZ_Widget.Key */
static MI_CONST MI_PropertyDecl XYZ_Widget_Key_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(XYZ_Widget, Key), /* offset */
    MI_T("XYZ_Widget"), /* origin */
    MI_T("XYZ_Widget"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST XYZ_Widget_props[] =
{
    &XYZ_Widget_Key_prop,
};

static MI_CONST MI_ProviderFT XYZ_Widget_funcs =
{
  (MI_ProviderFT_Load)XYZ_Widget_Load,
  (MI_ProviderFT_Unload)XYZ_Widget_Unload,
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

/* class XYZ_Widget */
MI_CONST MI_ClassDecl XYZ_Widget_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078740A, /* code */
    MI_T("XYZ_Widget"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    XYZ_Widget_props, /* properties */
    MI_COUNT(XYZ_Widget_props), /* numProperties */
    sizeof(XYZ_Widget), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &XYZ_Widget_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** XYZ_Gadget
**
**==============================================================================
*/

/* property XYZ_Gadget.Key */
static MI_CONST MI_PropertyDecl XYZ_Gadget_Key_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(XYZ_Gadget, Key), /* offset */
    MI_T("XYZ_Gadget"), /* origin */
    MI_T("XYZ_Gadget"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST XYZ_Gadget_props[] =
{
    &XYZ_Gadget_Key_prop,
};

static MI_CONST MI_ProviderFT XYZ_Gadget_funcs =
{
  (MI_ProviderFT_Load)XYZ_Gadget_Load,
  (MI_ProviderFT_Unload)XYZ_Gadget_Unload,
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

/* class XYZ_Gadget */
MI_CONST MI_ClassDecl XYZ_Gadget_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078740A, /* code */
    MI_T("XYZ_Gadget"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    XYZ_Gadget_props, /* properties */
    MI_COUNT(XYZ_Gadget_props), /* numProperties */
    sizeof(XYZ_Gadget), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &XYZ_Gadget_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** XYZ_Assoc
**
**==============================================================================
*/

/* property XYZ_Assoc.Left */
static MI_CONST MI_PropertyDecl XYZ_Assoc_Left_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006C7404, /* code */
    MI_T("Left"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("XYZ_Widget"), /* className */
    0, /* subscript */
    offsetof(XYZ_Assoc, Left), /* offset */
    MI_T("XYZ_Assoc"), /* origin */
    MI_T("XYZ_Assoc"), /* propagator */
    NULL,
};

/* property XYZ_Assoc.Right */
static MI_CONST MI_PropertyDecl XYZ_Assoc_Right_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00727405, /* code */
    MI_T("Right"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("XYZ_Gadget"), /* className */
    0, /* subscript */
    offsetof(XYZ_Assoc, Right), /* offset */
    MI_T("XYZ_Assoc"), /* origin */
    MI_T("XYZ_Assoc"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST XYZ_Assoc_props[] =
{
    &XYZ_Assoc_Left_prop,
    &XYZ_Assoc_Right_prop,
};

static void MI_CALL XYZ_Assoc_AssociatorInstances(
    XYZ_Assoc_Self* self,
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
    if (XYZ_Widget_IsA(instanceName))
    {
        if (_Match(role, MI_T("Left")) && 
            _Match(resultRole, MI_T("Right")))
        {
            XYZ_Assoc_AssociatorInstancesLeft(
                self, 
                context, 
                nameSpace, 
                className, 
                (XYZ_Widget*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (XYZ_Gadget_IsA(instanceName))
    {
        if (_Match(role, MI_T("Right")) && 
            _Match(resultRole, MI_T("Left")))
        {
            XYZ_Assoc_AssociatorInstancesRight(
                self, 
                context, 
                nameSpace, 
                className, 
                (XYZ_Gadget*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL XYZ_Assoc_ReferenceInstances(
    XYZ_Assoc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (XYZ_Widget_IsA(instanceName))
    {
        if (_Match(role, MI_T("Left")))
        {
            XYZ_Assoc_ReferenceInstancesLeft(
                self, 
                context, 
                nameSpace, 
                className, 
                (XYZ_Widget*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (XYZ_Gadget_IsA(instanceName))
    {
        if (_Match(role, MI_T("Right")))
        {
            XYZ_Assoc_ReferenceInstancesRight(
                self, 
                context, 
                nameSpace, 
                className, 
                (XYZ_Gadget*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT XYZ_Assoc_funcs =
{
  (MI_ProviderFT_Load)XYZ_Assoc_Load,
  (MI_ProviderFT_Unload)XYZ_Assoc_Unload,
  (MI_ProviderFT_GetInstance)XYZ_Assoc_GetInstance,
  (MI_ProviderFT_EnumerateInstances)XYZ_Assoc_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)XYZ_Assoc_CreateInstance,
  (MI_ProviderFT_ModifyInstance)XYZ_Assoc_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)XYZ_Assoc_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)XYZ_Assoc_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)XYZ_Assoc_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class XYZ_Assoc */
MI_CONST MI_ClassDecl XYZ_Assoc_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x00786309, /* code */
    MI_T("XYZ_Assoc"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    XYZ_Assoc_props, /* properties */
    MI_COUNT(XYZ_Assoc_props), /* numProperties */
    sizeof(XYZ_Assoc), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &XYZ_Assoc_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** XYZ_Widget2
**
**==============================================================================
*/

/* property XYZ_Widget2.Key */
static MI_CONST MI_PropertyDecl XYZ_Widget2_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(XYZ_Widget2, Key), /* offset */
    MI_T("XYZ_Widget"), /* origin */
    MI_T("XYZ_Widget2"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST XYZ_Widget2_props[] =
{
    &XYZ_Widget2_Key_prop,
};

static MI_CONST MI_ProviderFT XYZ_Widget2_funcs =
{
  (MI_ProviderFT_Load)XYZ_Widget2_Load,
  (MI_ProviderFT_Unload)XYZ_Widget2_Unload,
  (MI_ProviderFT_GetInstance)XYZ_Widget2_GetInstance,
  (MI_ProviderFT_EnumerateInstances)XYZ_Widget2_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)XYZ_Widget2_CreateInstance,
  (MI_ProviderFT_ModifyInstance)XYZ_Widget2_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)XYZ_Widget2_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class XYZ_Widget2 */
MI_CONST MI_ClassDecl XYZ_Widget2_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078320B, /* code */
    MI_T("XYZ_Widget2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    XYZ_Widget2_props, /* properties */
    MI_COUNT(XYZ_Widget2_props), /* numProperties */
    sizeof(XYZ_Widget2), /* size */
    MI_T("XYZ_Widget"), /* superClass */
    &XYZ_Widget_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &XYZ_Widget2_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** XYZ_Gadget2
**
**==============================================================================
*/

/* property XYZ_Gadget2.Key */
static MI_CONST MI_PropertyDecl XYZ_Gadget2_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(XYZ_Gadget2, Key), /* offset */
    MI_T("XYZ_Gadget"), /* origin */
    MI_T("XYZ_Gadget2"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST XYZ_Gadget2_props[] =
{
    &XYZ_Gadget2_Key_prop,
};

static MI_CONST MI_ProviderFT XYZ_Gadget2_funcs =
{
  (MI_ProviderFT_Load)XYZ_Gadget2_Load,
  (MI_ProviderFT_Unload)XYZ_Gadget2_Unload,
  (MI_ProviderFT_GetInstance)XYZ_Gadget2_GetInstance,
  (MI_ProviderFT_EnumerateInstances)XYZ_Gadget2_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)XYZ_Gadget2_CreateInstance,
  (MI_ProviderFT_ModifyInstance)XYZ_Gadget2_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)XYZ_Gadget2_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class XYZ_Gadget2 */
MI_CONST MI_ClassDecl XYZ_Gadget2_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078320B, /* code */
    MI_T("XYZ_Gadget2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    XYZ_Gadget2_props, /* properties */
    MI_COUNT(XYZ_Gadget2_props), /* numProperties */
    sizeof(XYZ_Gadget2), /* size */
    MI_T("XYZ_Gadget"), /* superClass */
    &XYZ_Gadget_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &XYZ_Gadget2_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** XYZ_Assoc2
**
**==============================================================================
*/

/* property XYZ_Assoc2.Left */
static MI_CONST MI_PropertyDecl XYZ_Assoc2_Left_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006C7404, /* code */
    MI_T("Left"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("XYZ_Widget2"), /* className */
    0, /* subscript */
    offsetof(XYZ_Assoc2, Left), /* offset */
    MI_T("XYZ_Assoc"), /* origin */
    MI_T("XYZ_Assoc2"), /* propagator */
    NULL,
};

/* property XYZ_Assoc2.Right */
static MI_CONST MI_PropertyDecl XYZ_Assoc2_Right_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00727405, /* code */
    MI_T("Right"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("XYZ_Gadget2"), /* className */
    0, /* subscript */
    offsetof(XYZ_Assoc2, Right), /* offset */
    MI_T("XYZ_Assoc"), /* origin */
    MI_T("XYZ_Assoc2"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST XYZ_Assoc2_props[] =
{
    &XYZ_Assoc2_Left_prop,
    &XYZ_Assoc2_Right_prop,
};

static void MI_CALL XYZ_Assoc2_AssociatorInstances(
    XYZ_Assoc2_Self* self,
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
    if (XYZ_Widget2_IsA(instanceName))
    {
        if (_Match(role, MI_T("Left")) && 
            _Match(resultRole, MI_T("Right")))
        {
            XYZ_Assoc2_AssociatorInstancesLeft(
                self, 
                context, 
                nameSpace, 
                className, 
                (XYZ_Widget2*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (XYZ_Gadget2_IsA(instanceName))
    {
        if (_Match(role, MI_T("Right")) && 
            _Match(resultRole, MI_T("Left")))
        {
            XYZ_Assoc2_AssociatorInstancesRight(
                self, 
                context, 
                nameSpace, 
                className, 
                (XYZ_Gadget2*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL XYZ_Assoc2_ReferenceInstances(
    XYZ_Assoc2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (XYZ_Widget2_IsA(instanceName))
    {
        if (_Match(role, MI_T("Left")))
        {
            XYZ_Assoc2_ReferenceInstancesLeft(
                self, 
                context, 
                nameSpace, 
                className, 
                (XYZ_Widget2*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (XYZ_Gadget2_IsA(instanceName))
    {
        if (_Match(role, MI_T("Right")))
        {
            XYZ_Assoc2_ReferenceInstancesRight(
                self, 
                context, 
                nameSpace, 
                className, 
                (XYZ_Gadget2*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT XYZ_Assoc2_funcs =
{
  (MI_ProviderFT_Load)XYZ_Assoc2_Load,
  (MI_ProviderFT_Unload)XYZ_Assoc2_Unload,
  (MI_ProviderFT_GetInstance)XYZ_Assoc2_GetInstance,
  (MI_ProviderFT_EnumerateInstances)XYZ_Assoc2_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)XYZ_Assoc2_CreateInstance,
  (MI_ProviderFT_ModifyInstance)XYZ_Assoc2_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)XYZ_Assoc2_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)XYZ_Assoc2_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)XYZ_Assoc2_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class XYZ_Assoc2 */
MI_CONST MI_ClassDecl XYZ_Assoc2_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x0078320A, /* code */
    MI_T("XYZ_Assoc2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    XYZ_Assoc2_props, /* properties */
    MI_COUNT(XYZ_Assoc2_props), /* numProperties */
    sizeof(XYZ_Assoc2), /* size */
    MI_T("XYZ_Assoc"), /* superClass */
    &XYZ_Assoc_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &XYZ_Assoc2_funcs, /* functions */
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
    &XYZ_Assoc_rtti,
    &XYZ_Assoc2_rtti,
    &XYZ_Gadget_rtti,
    &XYZ_Gadget2_rtti,
    &XYZ_Widget_rtti,
    &XYZ_Widget2_rtti,
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

