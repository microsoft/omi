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
#include "Gadget.h"
#include "Widget.h"
#include "Connector.h"

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
** Gadget
**
**==============================================================================
*/

/* property Gadget.Key */
static MI_CONST MI_PropertyDecl Gadget_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Gadget, Key), /* offset */
    MI_T("XYZ_Gadget"), /* origin */
    MI_T("XYZ_Gadget"), /* propagator */
    NULL,
};

/* property Gadget.ModelNumber */
static MI_CONST MI_PropertyDecl Gadget_ModelNumber_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D720B, /* code */
    MI_T("ModelNumber"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Gadget, ModelNumber), /* offset */
    MI_T("XYZ_Gadget"), /* origin */
    MI_T("XYZ_Gadget"), /* propagator */
    NULL,
};

/* property Gadget.Size */
static MI_CONST MI_PropertyDecl Gadget_Size_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736504, /* code */
    MI_T("Size"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Gadget, Size), /* offset */
    MI_T("XYZ_Gadget"), /* origin */
    MI_T("XYZ_Gadget"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Gadget_props[] =
{
    &Gadget_Key_prop,
    &Gadget_ModelNumber_prop,
    &Gadget_Size_prop,
};

/* parameter Gadget.ChangeState(): NewState */
static MI_CONST MI_ParameterDecl Gadget_ChangeState_NewState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x006E6508, /* code */
    MI_T("NewState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Gadget_ChangeState, NewState), /* offset */
};

/* parameter Gadget.ChangeState(): OldState */
static MI_CONST MI_ParameterDecl Gadget_ChangeState_OldState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006F6508, /* code */
    MI_T("OldState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Gadget_ChangeState, OldState), /* offset */
};

/* parameter Gadget.ChangeState(): MIReturn */
static MI_CONST MI_ParameterDecl Gadget_ChangeState_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Gadget_ChangeState, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Gadget_ChangeState_params[] =
{
    &Gadget_ChangeState_MIReturn_param,
    &Gadget_ChangeState_NewState_param,
    &Gadget_ChangeState_OldState_param,
};

/* method Gadget.ChangeState() */
MI_CONST MI_MethodDecl Gadget_ChangeState_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x0063650B, /* code */
    MI_T("ChangeState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Gadget_ChangeState_params, /* parameters */
    MI_COUNT(Gadget_ChangeState_params), /* numParameters */
    sizeof(Gadget_ChangeState), /* size */
    MI_UINT32, /* returnType */
    MI_T("XYZ_Gadget"), /* origin */
    MI_T("XYZ_Gadget"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Gadget_Invoke_ChangeState, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST Gadget_meths[] =
{
    &Gadget_ChangeState_rtti,
};

static MI_CONST MI_ProviderFT Gadget_funcs =
{
  (MI_ProviderFT_Load)Gadget_Load,
  (MI_ProviderFT_Unload)Gadget_Unload,
  (MI_ProviderFT_GetInstance)Gadget_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Gadget_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Gadget_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Gadget_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Gadget_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Gadget */
MI_CONST MI_ClassDecl Gadget_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078740A, /* code */
    MI_T("XYZ_Gadget"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Gadget_props, /* properties */
    MI_COUNT(Gadget_props), /* numProperties */
    sizeof(Gadget), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    Gadget_meths, /* methods */
    MI_COUNT(Gadget_meths), /* numMethods */
    &schemaDecl, /* schema */
    &Gadget_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** Widget
**
**==============================================================================
*/

/* property Widget.Key */
static MI_CONST MI_PropertyDecl Widget_Key_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006B7903, /* code */
    MI_T("Key"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, Key), /* offset */
    MI_T("XYZ_Widget"), /* origin */
    MI_T("XYZ_Widget"), /* propagator */
    NULL,
};

/* property Widget.ModelNumber */
static MI_CONST MI_PropertyDecl Widget_ModelNumber_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D720B, /* code */
    MI_T("ModelNumber"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, ModelNumber), /* offset */
    MI_T("XYZ_Widget"), /* origin */
    MI_T("XYZ_Widget"), /* propagator */
    NULL,
};

/* property Widget.Color */
static MI_CONST MI_PropertyDecl Widget_Color_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637205, /* code */
    MI_T("Color"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, Color), /* offset */
    MI_T("XYZ_Widget"), /* origin */
    MI_T("XYZ_Widget"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Widget_props[] =
{
    &Widget_Key_prop,
    &Widget_ModelNumber_prop,
    &Widget_Color_prop,
};

static MI_CONST MI_ProviderFT Widget_funcs =
{
  (MI_ProviderFT_Load)Widget_Load,
  (MI_ProviderFT_Unload)Widget_Unload,
  (MI_ProviderFT_GetInstance)Widget_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Widget_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Widget_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Widget_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Widget_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Widget */
MI_CONST MI_ClassDecl Widget_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078740A, /* code */
    MI_T("XYZ_Widget"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Widget_props, /* properties */
    MI_COUNT(Widget_props), /* numProperties */
    sizeof(Widget), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Widget_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** Connector
**
**==============================================================================
*/

/* property Connector.Left */
static MI_CONST MI_PropertyDecl Connector_Left_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006C7404, /* code */
    MI_T("Left"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("XYZ_Widget"), /* className */
    0, /* subscript */
    offsetof(Connector, Left), /* offset */
    MI_T("XYZ_Connector"), /* origin */
    MI_T("XYZ_Connector"), /* propagator */
    NULL,
};

/* property Connector.Right */
static MI_CONST MI_PropertyDecl Connector_Right_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00727405, /* code */
    MI_T("Right"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("XYZ_Gadget"), /* className */
    0, /* subscript */
    offsetof(Connector, Right), /* offset */
    MI_T("XYZ_Connector"), /* origin */
    MI_T("XYZ_Connector"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Connector_props[] =
{
    &Connector_Left_prop,
    &Connector_Right_prop,
};

static void MI_CALL Connector_AssociatorInstances(
    Connector_Self* self,
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
    if (Widget_IsA(instanceName))
    {
        if (_Match(role, MI_T("Left")) && 
            _Match(resultRole, MI_T("Right")))
        {
            Connector_AssociatorInstancesLeft(
                self, 
                context, 
                nameSpace, 
                className, 
                (Widget*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (Gadget_IsA(instanceName))
    {
        if (_Match(role, MI_T("Right")) && 
            _Match(resultRole, MI_T("Left")))
        {
            Connector_AssociatorInstancesRight(
                self, 
                context, 
                nameSpace, 
                className, 
                (Gadget*)instanceName, 
                resultClass, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_Context_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL Connector_ReferenceInstances(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Instance* instanceName,
    const MI_Char* role,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (Widget_IsA(instanceName))
    {
        if (_Match(role, MI_T("Left")))
        {
            Connector_ReferenceInstancesLeft(
                self, 
                context, 
                nameSpace, 
                className, 
                (Widget*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    if (Gadget_IsA(instanceName))
    {
        if (_Match(role, MI_T("Right")))
        {
            Connector_ReferenceInstancesRight(
                self, 
                context, 
                nameSpace, 
                className, 
                (Gadget*)instanceName, 
                propertySet, 
                keysOnly, 
                filter);
            return;
        }
    }

    MI_Context_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT Connector_funcs =
{
  (MI_ProviderFT_Load)Connector_Load,
  (MI_ProviderFT_Unload)Connector_Unload,
  (MI_ProviderFT_GetInstance)Connector_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Connector_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Connector_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Connector_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Connector_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)Connector_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)Connector_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Connector */
MI_CONST MI_ClassDecl Connector_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x0078720D, /* code */
    MI_T("XYZ_Connector"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Connector_props, /* properties */
    MI_COUNT(Connector_props), /* numProperties */
    sizeof(Connector), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Connector_funcs, /* functions */
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
    &Connector_rtti,
    &Gadget_rtti,
    &Widget_rtti,
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

