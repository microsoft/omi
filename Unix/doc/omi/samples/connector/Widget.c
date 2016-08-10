/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#include <MI.h>
#include "Widget.h"

void MI_CALL Widget_Load(
    Widget_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Widget_Unload(
    Widget_Self* self,
    MI_Context* context)
{
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Widget_EnumerateInstances(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    Widget widget;
    Widget_Construct(&widget, context);

    // Widget.Key=1001
    Widget_Set_Key(&widget, 1001);
    Widget_Set_ModelNumber(&widget, 1);
    Widget_Set_Color(&widget, MI_T("Red"));
    Widget_Post(&widget, context);

    // Widget.Key=1002
    Widget_Set_Key(&widget, 1002);
    Widget_Set_ModelNumber(&widget, 2);
    Widget_Set_Color(&widget, MI_T("Green"));
    Widget_Post(&widget, context);

    Widget_Destruct(&widget);
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Widget_GetInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_Result r = MI_RESULT_OK;
    Widget widget; 
    Widget_Construct(&widget, context);
    
    if (instanceName->Key.value == 1001)
    {
        // Widget.Key=1001
        Widget_Set_Key(&widget, 1001);
        Widget_Set_ModelNumber(&widget, 1);
        Widget_Set_Color(&widget, MI_T("Red"));
        Widget_Post(&widget, context);
    }
    else if (instanceName->Key.value == 1002)
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

void MI_CALL Widget_CreateInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* newInstance)
{
    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Widget_ModifyInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Widget_DeleteInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* instanceName)
{
    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

