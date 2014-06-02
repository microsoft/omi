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
#include "Widget.h"
#include "Gadget.h"
#include "Fastener.h"

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
    MI_T("MSFT_Widget"), /* origin */
    MI_T("MSFT_Widget"), /* propagator */
    NULL,
};

static MI_CONST MI_Real32 Widget_W1_value = (float)0;

/* property Widget.W1 */
static MI_CONST MI_PropertyDecl Widget_W1_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00773102, /* code */
    MI_T("W1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, W1), /* offset */
    MI_T("MSFT_Widget"), /* origin */
    MI_T("MSFT_Widget"), /* propagator */
    &Widget_W1_value,
};

static MI_CONST MI_Real32 Widget_X1_value = (float)1;

/* property Widget.X1 */
static MI_CONST MI_PropertyDecl Widget_X1_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00783102, /* code */
    MI_T("X1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, X1), /* offset */
    MI_T("MSFT_Widget"), /* origin */
    MI_T("MSFT_Widget"), /* propagator */
    &Widget_X1_value,
};

static MI_CONST MI_Real32 Widget_Y1_value = (float)2;

/* property Widget.Y1 */
static MI_CONST MI_PropertyDecl Widget_Y1_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00793102, /* code */
    MI_T("Y1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, Y1), /* offset */
    MI_T("MSFT_Widget"), /* origin */
    MI_T("MSFT_Widget"), /* propagator */
    &Widget_Y1_value,
};

static MI_CONST MI_Real32 Widget_Z1_value = (float)0.123457;

/* property Widget.Z1 */
static MI_CONST MI_PropertyDecl Widget_Z1_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x007A3102, /* code */
    MI_T("Z1"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, Z1), /* offset */
    MI_T("MSFT_Widget"), /* origin */
    MI_T("MSFT_Widget"), /* propagator */
    &Widget_Z1_value,
};

static MI_CONST MI_Real64 Widget_W2_value = (double)0;

/* property Widget.W2 */
static MI_CONST MI_PropertyDecl Widget_W2_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00773202, /* code */
    MI_T("W2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, W2), /* offset */
    MI_T("MSFT_Widget"), /* origin */
    MI_T("MSFT_Widget"), /* propagator */
    &Widget_W2_value,
};

static MI_CONST MI_Real64 Widget_X2_value = (double)1;

/* property Widget.X2 */
static MI_CONST MI_PropertyDecl Widget_X2_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00783202, /* code */
    MI_T("X2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, X2), /* offset */
    MI_T("MSFT_Widget"), /* origin */
    MI_T("MSFT_Widget"), /* propagator */
    &Widget_X2_value,
};

static MI_CONST MI_Real64 Widget_Y2_value = (double)2;

/* property Widget.Y2 */
static MI_CONST MI_PropertyDecl Widget_Y2_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00793202, /* code */
    MI_T("Y2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, Y2), /* offset */
    MI_T("MSFT_Widget"), /* origin */
    MI_T("MSFT_Widget"), /* propagator */
    &Widget_Y2_value,
};

static MI_CONST MI_Real64 Widget_Z2_value = (double)0.123457;

/* property Widget.Z2 */
static MI_CONST MI_PropertyDecl Widget_Z2_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x007A3202, /* code */
    MI_T("Z2"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REAL64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, Z2), /* offset */
    MI_T("MSFT_Widget"), /* origin */
    MI_T("MSFT_Widget"), /* propagator */
    &Widget_Z2_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST Widget_props[] =
{
    &Widget_Key_prop,
    &Widget_W1_prop,
    &Widget_X1_prop,
    &Widget_Y1_prop,
    &Widget_Z1_prop,
    &Widget_W2_prop,
    &Widget_X2_prop,
    &Widget_Y2_prop,
    &Widget_Z2_prop,
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
    0x006D740B, /* code */
    MI_T("MSFT_Widget"), /* name */
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
};

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
    MI_T("MSFT_Gadget"), /* origin */
    MI_T("MSFT_Gadget"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Gadget_props[] =
{
    &Gadget_Key_prop,
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
    0x006D740B, /* code */
    MI_T("MSFT_Gadget"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Gadget_props, /* properties */
    MI_COUNT(Gadget_props), /* numProperties */
    sizeof(Gadget), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Gadget_funcs, /* functions */
};

/*
**==============================================================================
**
** Fastener
**
**==============================================================================
*/

/* property Fastener.Left */
static MI_CONST MI_PropertyDecl Fastener_Left_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x006C7404, /* code */
    MI_T("Left"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("MSFT_Widget"), /* className */
    0, /* subscript */
    offsetof(Fastener, Left), /* offset */
    MI_T("MSFT_Fastener"), /* origin */
    MI_T("MSFT_Fastener"), /* propagator */
    NULL,
};

/* property Fastener.Right */
static MI_CONST MI_PropertyDecl Fastener_Right_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00727405, /* code */
    MI_T("Right"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("MSFT_Gadget"), /* className */
    0, /* subscript */
    offsetof(Fastener, Right), /* offset */
    MI_T("MSFT_Fastener"), /* origin */
    MI_T("MSFT_Fastener"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Fastener_props[] =
{
    &Fastener_Left_prop,
    &Fastener_Right_prop,
};

static void MI_CALL Fastener_AssociatorInstances(
    Fastener_Self* self,
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
            Fastener_AssociatorInstancesLeft(
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
            Fastener_AssociatorInstancesRight(
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

    MI_PostResult(context, MI_RESULT_OK);
}

static void MI_CALL Fastener_ReferenceInstances(
    Fastener_Self* self,
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
            Fastener_ReferenceInstancesLeft(
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
            Fastener_ReferenceInstancesRight(
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

    MI_PostResult(context, MI_RESULT_OK);
}

static MI_CONST MI_ProviderFT Fastener_funcs =
{
  (MI_ProviderFT_Load)Fastener_Load,
  (MI_ProviderFT_Unload)Fastener_Unload,
  (MI_ProviderFT_GetInstance)Fastener_GetInstance,
  (MI_ProviderFT_EnumerateInstances)Fastener_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)Fastener_CreateInstance,
  (MI_ProviderFT_ModifyInstance)Fastener_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)Fastener_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)Fastener_AssociatorInstances,
  (MI_ProviderFT_ReferenceInstances)Fastener_ReferenceInstances,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Fastener */
MI_CONST MI_ClassDecl Fastener_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ASSOCIATION, /* flags */
    0x006D720D, /* code */
    MI_T("MSFT_Fastener"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Fastener_props, /* properties */
    MI_COUNT(Fastener_props), /* numProperties */
    sizeof(Fastener), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Fastener_funcs, /* functions */
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
    &Fastener_rtti,
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

