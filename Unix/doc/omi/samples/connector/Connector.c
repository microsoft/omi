/* @migen@ */
#include <MI.h>
#include "Connector.h"

void MI_CALL Connector_Load(
    Connector_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Connector_Unload(
    Connector_Self* self,
    MI_Context* context)
{
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Connector_EnumerateInstances(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Widget widget; 
    Gadget gadget; 
    Connector connector;

    Widget_Construct(&widget, context);
    Gadget_Construct(&gadget, context);
    Connector_Construct(&connector, context);

    // Connector.Left="Widget.Key=1001",Right="Gadget.Key=1003"
    Widget_Set_Key(&widget, 1001);
    Gadget_Set_Key(&gadget, 1003);
    Connector_Set_Left(&connector, &widget);
    Connector_Set_Right(&connector, &gadget);
    Connector_Post(&connector, context);

    // Connector.Left="Widget.Key=1002",Right="Gadget.Key=1004"
    Widget_Set_Key(&widget, 1002);
    Gadget_Set_Key(&gadget, 1004);
    Connector_Set_Left(&connector, &widget);
    Connector_Set_Right(&connector, &gadget);
    Connector_Post(&connector, context);

    Widget_Destruct(&widget);
    Gadget_Destruct(&gadget);
    Connector_Destruct(&connector);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Connector_GetInstance(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Connector* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_Result r = MI_RESULT_OK;
    Widget widget; 
    Gadget gadget;
    Connector connector;

    Widget_Construct(&widget, context);
    Gadget_Construct(&gadget, context);
    Connector_Construct(&connector, context);

    if (instanceName->Left.value->Key.value == 1001 && 
        instanceName->Right.value->Key.value == 1003)
    {
        // Connector.Left="Widget.Key=1001",Right="Gadget.Key=1003"
        Widget_Set_Key(&widget, 1001);
        Gadget_Set_Key(&gadget, 1003);
        Connector_Set_Left(&connector, &widget);
        Connector_Set_Right(&connector, &gadget);
        Connector_Post(&connector, context);
    }
    else if (instanceName->Left.value->Key.value == 1002 &&
        instanceName->Right.value->Key.value == 1004)
    {
        // Connector.Left="Widget.Key=1002",Right="Gadget.Key=1004"
        Widget_Set_Key(&widget, 1002);
        Gadget_Set_Key(&gadget, 1004);
        Connector_Set_Left(&connector, &widget);
        Connector_Set_Right(&connector, &gadget);
        Connector_Post(&connector, context);
    }
    else
    {
        r = MI_RESULT_NOT_FOUND;
    }

    Widget_Destruct(&widget);
    Gadget_Destruct(&gadget);
    Connector_Destruct(&connector);

    MI_Context_PostResult(context, r);
}

void MI_CALL Connector_CreateInstance(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Connector* newInstance)
{
    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Connector_ModifyInstance(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Connector* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Connector_DeleteInstance(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Connector* instanceName)
{
    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Connector_AssociatorInstancesLeft(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_Result r = MI_RESULT_OK;
    Gadget gadget;
    Gadget_Construct(&gadget, context);

    if (instanceName->Key.value == 1001)
    {
        // Gadget.Key=1003
        Gadget_Set_Key(&gadget, 1003);
        Gadget_Set_ModelNumber(&gadget, 3);
        Gadget_Set_Size(&gadget, 33);
        Gadget_Post(&gadget, context);
    }
    else if (instanceName->Key.value == 1002)
    {
        // Gadget.Key=1004
        Gadget_Set_Key(&gadget, 1004);
        Gadget_Set_ModelNumber(&gadget, 4);
        Gadget_Set_Size(&gadget, 43);
        Gadget_Post(&gadget, context);
    }
    else 
    {
        r = MI_RESULT_NOT_FOUND;
    }

    Gadget_Destruct(&gadget);
    MI_Context_PostResult(context, r);
}

void MI_CALL Connector_AssociatorInstancesRight(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_Result r = MI_RESULT_OK;
    Widget widget;
    Widget_Construct(&widget, context);
    
    if (instanceName->Key.value == 1003)
    {
        // Widget.Key=1001
        Widget_Set_Key(&widget, 1001);
        Widget_Set_ModelNumber(&widget, 1);
        Widget_Set_Color(&widget, MI_T("Red"));
        Widget_Post(&widget, context);
    }
    else if (instanceName->Key.value == 1004)
    {
        // Widget.Key=1002
        Widget_Set_Key(&widget, 1002);
        Widget_Set_ModelNumber(&widget, 2);
        Widget_Set_Color(&widget, MI_T("Green"));
        Widget_Post(&widget, context);
    }
    else
    {
        r = MI_RESULT_NOT_FOUND;
    }

    Widget_Destruct(&widget);

    MI_Context_PostResult(context, r);
}

void MI_CALL Connector_ReferenceInstancesLeft(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_Result r = MI_RESULT_OK;
    Widget widget;
    Gadget gadget; 
    Connector connector;

    Widget_Construct(&widget, context);
    Gadget_Construct(&gadget, context);
    Connector_Construct(&connector, context);

    if (instanceName->Key.value == 1001)
    {
        // Connector.Left="Widget.Key=1001",Right="Gadget.Key=1003"
        Widget_Set_Key(&widget, 1001);
        Gadget_Set_Key(&gadget, 1003);
        Connector_Set_Left(&connector, &widget);
        Connector_Set_Right(&connector, &gadget);
        Connector_Post(&connector, context);
    }
    else if (instanceName->Key.value == 1002)
    {
        // Connector.Left="Widget.Key=1002",Right="Gadget.Key=1004"
        Widget_Set_Key(&widget, 1002);
        Gadget_Set_Key(&gadget, 1004);
        Connector_Set_Left(&connector, &widget);
        Connector_Set_Right(&connector, &gadget);
        Connector_Post(&connector, context);
    }
    else
    {
        r = MI_RESULT_NOT_FOUND;
    }

    Widget_Destruct(&widget);
    Gadget_Destruct(&gadget);
    Connector_Destruct(&connector);
    
    MI_Context_PostResult(context, r);
}

void MI_CALL Connector_ReferenceInstancesRight(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Gadget* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_Result r = MI_RESULT_OK;
    Widget widget;
    Gadget gadget; 
    Connector connector;

    Widget_Construct(&widget, context);
    Gadget_Construct(&gadget, context);
    Connector_Construct(&connector, context);

    if (instanceName->Key.value == 1003)
    {
        // Connector.Left="Widget.Key=1001",Right="Gadget.Key=1003"
        Widget_Set_Key(&widget, 1001);
        Gadget_Set_Key(&gadget, 1003);
        Connector_Set_Left(&connector, &widget);
        Connector_Set_Right(&connector, &gadget);
        Connector_Post(&connector, context);
    }
    else if (instanceName->Key.value == 1004)
    {
        // Connector.Left="Widget.Key=1002",Right="Gadget.Key=1004"
        Widget_Set_Key(&widget, 1002);
        Gadget_Set_Key(&gadget, 1004);
        Connector_Set_Left(&connector, &widget);
        Connector_Set_Right(&connector, &gadget);
        Connector_Post(&connector, context);
    }
    else
    {
        r = MI_RESULT_NOT_FOUND;
    }

    Widget_Destruct(&widget);
    Gadget_Destruct(&gadget);
    Connector_Destruct(&connector);
    
    MI_Context_PostResult(context, r);
}

