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
#include "Connector.h"
#include "Order.h"
#include "Base.h"
#include "Derived.h"
#include "BaseAssoc.h"
#include "DerivedAssoc.h"

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

/* property Widget.SerialNumber */
static MI_CONST MI_PropertyDecl Widget_SerialNumber_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0073720C, /* code */
    MI_T("SerialNumber"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, SerialNumber), /* offset */
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

/* property Widget.Colors */
static MI_CONST MI_PropertyDecl Widget_Colors_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637306, /* code */
    MI_T("Colors"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, Colors), /* offset */
    MI_T("XYZ_Widget"), /* origin */
    MI_T("XYZ_Widget"), /* propagator */
    NULL,
};

/* property Widget.Numbers */
static MI_CONST MI_PropertyDecl Widget_Numbers_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E7307, /* code */
    MI_T("Numbers"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, Numbers), /* offset */
    MI_T("XYZ_Widget"), /* origin */
    MI_T("XYZ_Widget"), /* propagator */
    NULL,
};

/* property Widget.Timestamp */
static MI_CONST MI_PropertyDecl Widget_Timestamp_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00747009, /* code */
    MI_T("Timestamp"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, Timestamp), /* offset */
    MI_T("XYZ_Widget"), /* origin */
    MI_T("XYZ_Widget"), /* propagator */
    NULL,
};

/* property Widget.Interval */
static MI_CONST MI_PropertyDecl Widget_Interval_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00696C08, /* code */
    MI_T("Interval"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, Interval), /* offset */
    MI_T("XYZ_Widget"), /* origin */
    MI_T("XYZ_Widget"), /* propagator */
    NULL,
};

/* property Widget.TimestampA */
static MI_CONST MI_PropertyDecl Widget_TimestampA_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0074610A, /* code */
    MI_T("TimestampA"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, TimestampA), /* offset */
    MI_T("XYZ_Widget"), /* origin */
    MI_T("XYZ_Widget"), /* propagator */
    NULL,
};

/* property Widget.IntervalA */
static MI_CONST MI_PropertyDecl Widget_IntervalA_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00696109, /* code */
    MI_T("IntervalA"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIMEA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Widget, IntervalA), /* offset */
    MI_T("XYZ_Widget"), /* origin */
    MI_T("XYZ_Widget"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Widget_props[] =
{
    &Widget_SerialNumber_prop,
    &Widget_ModelNumber_prop,
    &Widget_Color_prop,
    &Widget_Colors_prop,
    &Widget_Numbers_prop,
    &Widget_Timestamp_prop,
    &Widget_Interval_prop,
    &Widget_TimestampA_prop,
    &Widget_IntervalA_prop,
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
};

/*
**==============================================================================
**
** Gadget
**
**==============================================================================
*/

/* property Gadget.SerialNumber */
static MI_CONST MI_PropertyDecl Gadget_SerialNumber_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0073720C, /* code */
    MI_T("SerialNumber"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Gadget, SerialNumber), /* offset */
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

/* property Gadget.State */
static MI_CONST MI_PropertyDecl Gadget_State_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736505, /* code */
    MI_T("State"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Gadget, State), /* offset */
    MI_T("XYZ_Gadget"), /* origin */
    MI_T("XYZ_Gadget"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* Gadget_Embedded_EmbeddedInstance_qual_value = MI_T("XYZ_Widget");

static MI_CONST MI_Qualifier Gadget_Embedded_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &Gadget_Embedded_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Gadget_Embedded_quals[] =
{
    &Gadget_Embedded_EmbeddedInstance_qual,
};

/* property Gadget.Embedded */
static MI_CONST MI_PropertyDecl Gadget_Embedded_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656408, /* code */
    MI_T("Embedded"), /* name */
    Gadget_Embedded_quals, /* qualifiers */
    MI_COUNT(Gadget_Embedded_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("XYZ_Widget"), /* className */
    0, /* subscript */
    offsetof(Gadget, Embedded), /* offset */
    MI_T("XYZ_Gadget"), /* origin */
    MI_T("XYZ_Gadget"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Gadget_props[] =
{
    &Gadget_SerialNumber_prop,
    &Gadget_ModelNumber_prop,
    &Gadget_Size_prop,
    &Gadget_State_prop,
    &Gadget_Embedded_prop,
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

static MI_CONST MI_Char* Gadget_Foo_Arg_EmbeddedInstance_qual_value = MI_T("XYZ_Gadget");

static MI_CONST MI_Qualifier Gadget_Foo_Arg_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &Gadget_Foo_Arg_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Gadget_Foo_Arg_quals[] =
{
    &Gadget_Foo_Arg_EmbeddedInstance_qual,
};

/* parameter Gadget.Foo(): Arg */
static MI_CONST MI_ParameterDecl Gadget_Foo_Arg_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00616703, /* code */
    MI_T("Arg"), /* name */
    Gadget_Foo_Arg_quals, /* qualifiers */
    MI_COUNT(Gadget_Foo_Arg_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("XYZ_Gadget"), /* className */
    0, /* subscript */
    offsetof(Gadget_Foo, Arg), /* offset */
};

/* parameter Gadget.Foo(): MIReturn */
static MI_CONST MI_ParameterDecl Gadget_Foo_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Gadget_Foo, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Gadget_Foo_params[] =
{
    &Gadget_Foo_MIReturn_param,
    &Gadget_Foo_Arg_param,
};

/* method Gadget.Foo() */
MI_CONST MI_MethodDecl Gadget_Foo_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00666F03, /* code */
    MI_T("Foo"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Gadget_Foo_params, /* parameters */
    MI_COUNT(Gadget_Foo_params), /* numParameters */
    sizeof(Gadget_Foo), /* size */
    MI_UINT32, /* returnType */
    MI_T("XYZ_Gadget"), /* origin */
    MI_T("XYZ_Gadget"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Gadget_Invoke_Foo, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST Gadget_meths[] =
{
    &Gadget_ChangeState_rtti,
    &Gadget_Foo_rtti,
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

    MI_PostResult(context, MI_RESULT_OK);
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

    MI_PostResult(context, MI_RESULT_OK);
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
};

/*
**==============================================================================
**
** Order
**
**==============================================================================
*/

/* property Order.SerialNumber */
static MI_CONST MI_PropertyDecl Order_SerialNumber_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073720C, /* code */
    MI_T("SerialNumber"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Order, SerialNumber), /* offset */
    MI_T("XYZ_Order"), /* origin */
    MI_T("XYZ_Order"), /* propagator */
    NULL,
};

/* property Order.Quantity */
static MI_CONST MI_PropertyDecl Order_Quantity_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00717908, /* code */
    MI_T("Quantity"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Order, Quantity), /* offset */
    MI_T("XYZ_Order"), /* origin */
    MI_T("XYZ_Order"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Order_props[] =
{
    &Order_SerialNumber_prop,
    &Order_Quantity_prop,
};

static MI_CONST MI_ProviderFT Order_funcs =
{
  (MI_ProviderFT_Load)Order_Load,
  (MI_ProviderFT_Unload)Order_Unload,
  (MI_ProviderFT_GetInstance)NULL,
  (MI_ProviderFT_EnumerateInstances)NULL,
  (MI_ProviderFT_CreateInstance)NULL,
  (MI_ProviderFT_ModifyInstance)NULL,
  (MI_ProviderFT_DeleteInstance)NULL,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)Order_EnableIndications,
  (MI_ProviderFT_DisableIndications)Order_DisableIndications,
  (MI_ProviderFT_Subscribe)Order_Subscribe,
  (MI_ProviderFT_Unsubscribe)Order_Unsubscribe,
  (MI_ProviderFT_Invoke)NULL,
};

/* class Order */
MI_CONST MI_ClassDecl Order_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x00787209, /* code */
    MI_T("XYZ_Order"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Order_props, /* properties */
    MI_COUNT(Order_props), /* numProperties */
    sizeof(Order), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &Order_funcs, /* functions */
};

/*
**==============================================================================
**
** Base
**
**==============================================================================
*/

/* property Base.X */
static MI_CONST MI_PropertyDecl Base_X_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00787801, /* code */
    MI_T("X"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Base, X), /* offset */
    MI_T("XYZ_Base"), /* origin */
    MI_T("XYZ_Base"), /* propagator */
    NULL,
};

/* property Base.Property */
static MI_CONST MI_PropertyDecl Base_Property_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00707908, /* code */
    MI_T("Property"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Base, Property), /* offset */
    MI_T("XYZ_Base"), /* origin */
    MI_T("XYZ_Base"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Base_props[] =
{
    &Base_X_prop,
    &Base_Property_prop,
};

/* parameter Base.Foo(): MIReturn */
static MI_CONST MI_ParameterDecl Base_Foo_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Base_Foo, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Base_Foo_params[] =
{
    &Base_Foo_MIReturn_param,
};

/* method Base.Foo() */
MI_CONST MI_MethodDecl Base_Foo_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00666F03, /* code */
    MI_T("Foo"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Base_Foo_params, /* parameters */
    MI_COUNT(Base_Foo_params), /* numParameters */
    sizeof(Base_Foo), /* size */
    MI_UINT32, /* returnType */
    MI_T("XYZ_Base"), /* origin */
    MI_T("XYZ_Base"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Base_Invoke_Foo, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST Base_meths[] =
{
    &Base_Foo_rtti,
};

static MI_CONST MI_ProviderFT Base_funcs =
{
  (MI_ProviderFT_Load)Base_Load,
  (MI_ProviderFT_Unload)Base_Unload,
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

/* class Base */
MI_CONST MI_ClassDecl Base_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00786508, /* code */
    MI_T("XYZ_Base"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Base_props, /* properties */
    MI_COUNT(Base_props), /* numProperties */
    sizeof(Base), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    Base_meths, /* methods */
    MI_COUNT(Base_meths), /* numMethods */
    &schemaDecl, /* schema */
    &Base_funcs, /* functions */
};

/*
**==============================================================================
**
** Derived
**
**==============================================================================
*/

/* property Derived.X */
static MI_CONST MI_PropertyDecl Derived_X_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00787801, /* code */
    MI_T("X"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Derived, X), /* offset */
    MI_T("XYZ_Base"), /* origin */
    MI_T("XYZ_Derived"), /* propagator */
    NULL,
};

/* property Derived.Property */
static MI_CONST MI_PropertyDecl Derived_Property_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00707908, /* code */
    MI_T("Property"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Derived, Property), /* offset */
    MI_T("XYZ_Base"), /* origin */
    MI_T("XYZ_Derived"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST Derived_props[] =
{
    &Derived_X_prop,
    &Derived_Property_prop,
};

/* parameter Derived.Foo(): MIReturn */
static MI_CONST MI_ParameterDecl Derived_Foo_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(Derived_Foo, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST Derived_Foo_params[] =
{
    &Derived_Foo_MIReturn_param,
};

/* method Derived.Foo() */
MI_CONST MI_MethodDecl Derived_Foo_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00666F03, /* code */
    MI_T("Foo"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    Derived_Foo_params, /* parameters */
    MI_COUNT(Derived_Foo_params), /* numParameters */
    sizeof(Derived_Foo), /* size */
    MI_UINT32, /* returnType */
    MI_T("XYZ_Base"), /* origin */
    MI_T("XYZ_Derived"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)Derived_Invoke_Foo, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST Derived_meths[] =
{
    &Derived_Foo_rtti,
};

static MI_CONST MI_ProviderFT Derived_funcs =
{
  (MI_ProviderFT_Load)Derived_Load,
  (MI_ProviderFT_Unload)Derived_Unload,
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

static MI_CONST MI_Char* Derived_Description_qual_value = MI_T("Oops");

static MI_CONST MI_Qualifier Derived_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &Derived_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST Derived_quals[] =
{
    &Derived_Description_qual,
};

/* class Derived */
MI_CONST MI_ClassDecl Derived_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078640B, /* code */
    MI_T("XYZ_Derived"), /* name */
    Derived_quals, /* qualifiers */
    MI_COUNT(Derived_quals), /* numQualifiers */
    Derived_props, /* properties */
    MI_COUNT(Derived_props), /* numProperties */
    sizeof(Derived), /* size */
    MI_T("XYZ_Base"), /* superClass */
    &Base_rtti, /* superClassDecl */
    Derived_meths, /* methods */
    MI_COUNT(Derived_meths), /* numMethods */
    &schemaDecl, /* schema */
    &Derived_funcs, /* functions */
};

/*
**==============================================================================
**
** BaseAssoc
**
**==============================================================================
*/

/* property BaseAssoc.Left */
static MI_CONST MI_PropertyDecl BaseAssoc_Left_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C7404, /* code */
    MI_T("Left"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("XYZ_Widget"), /* className */
    0, /* subscript */
    offsetof(BaseAssoc, Left), /* offset */
    MI_T("XYZ_BaseAssoc"), /* origin */
    MI_T("XYZ_BaseAssoc"), /* propagator */
    NULL,
};

/* property BaseAssoc.Right */
static MI_CONST MI_PropertyDecl BaseAssoc_Right_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00727405, /* code */
    MI_T("Right"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("XYZ_Gadget"), /* className */
    0, /* subscript */
    offsetof(BaseAssoc, Right), /* offset */
    MI_T("XYZ_BaseAssoc"), /* origin */
    MI_T("XYZ_BaseAssoc"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST BaseAssoc_props[] =
{
    &BaseAssoc_Left_prop,
    &BaseAssoc_Right_prop,
};

static MI_CONST MI_ProviderFT BaseAssoc_funcs =
{
  (MI_ProviderFT_Load)BaseAssoc_Load,
  (MI_ProviderFT_Unload)BaseAssoc_Unload,
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

/* class BaseAssoc */
MI_CONST MI_ClassDecl BaseAssoc_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0078630D, /* code */
    MI_T("XYZ_BaseAssoc"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    BaseAssoc_props, /* properties */
    MI_COUNT(BaseAssoc_props), /* numProperties */
    sizeof(BaseAssoc), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &BaseAssoc_funcs, /* functions */
};

/*
**==============================================================================
**
** DerivedAssoc
**
**==============================================================================
*/

/* property DerivedAssoc.Left */
static MI_CONST MI_PropertyDecl DerivedAssoc_Left_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C7404, /* code */
    MI_T("Left"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("XYZ_Widget"), /* className */
    0, /* subscript */
    offsetof(DerivedAssoc, Left), /* offset */
    MI_T("XYZ_BaseAssoc"), /* origin */
    MI_T("XYZ_DerivedAssoc"), /* propagator */
    NULL,
};

/* property DerivedAssoc.Right */
static MI_CONST MI_PropertyDecl DerivedAssoc_Right_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00727405, /* code */
    MI_T("Right"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("XYZ_Gadget"), /* className */
    0, /* subscript */
    offsetof(DerivedAssoc, Right), /* offset */
    MI_T("XYZ_BaseAssoc"), /* origin */
    MI_T("XYZ_DerivedAssoc"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST DerivedAssoc_props[] =
{
    &DerivedAssoc_Left_prop,
    &DerivedAssoc_Right_prop,
};

static MI_CONST MI_ProviderFT DerivedAssoc_funcs =
{
  (MI_ProviderFT_Load)DerivedAssoc_Load,
  (MI_ProviderFT_Unload)DerivedAssoc_Unload,
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

static MI_CONST MI_Char* DerivedAssoc_Description_qual_value = MI_T("Oops");

static MI_CONST MI_Qualifier DerivedAssoc_Description_qual =
{
    MI_T("Description"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &DerivedAssoc_Description_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST DerivedAssoc_quals[] =
{
    &DerivedAssoc_Description_qual,
};

/* class DerivedAssoc */
MI_CONST MI_ClassDecl DerivedAssoc_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00786310, /* code */
    MI_T("XYZ_DerivedAssoc"), /* name */
    DerivedAssoc_quals, /* qualifiers */
    MI_COUNT(DerivedAssoc_quals), /* numQualifiers */
    DerivedAssoc_props, /* properties */
    MI_COUNT(DerivedAssoc_props), /* numProperties */
    sizeof(DerivedAssoc), /* size */
    MI_T("XYZ_BaseAssoc"), /* superClass */
    &BaseAssoc_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    &DerivedAssoc_funcs, /* functions */
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
    &Base_rtti,
    &BaseAssoc_rtti,
    &Connector_rtti,
    &Derived_rtti,
    &DerivedAssoc_rtti,
    &Gadget_rtti,
    &Order_rtti,
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

