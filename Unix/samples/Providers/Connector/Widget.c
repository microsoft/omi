/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#include <stdlib.h>
#include <pal/palcommon.h>
#include <MI.h>
#include "Widget.h"

void MI_CALL Widget_Load(
    Widget_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Widget_Unload(
    Widget_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

static void SetArray(Widget* widget)
{
    const size_t n = 10; /* *4096; */
    MI_Uint32* data = PAL_Calloc(n, sizeof(MI_Uint32));
    size_t i;

    if (!data)
    {
        fprintf(stderr, "PAL_Calloc() failed\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        data[i] = (MI_Uint32)i;
    }

    Widget_Set_Array(widget, data, n);
    PAL_Free(data);
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
    Widget w;

    if (context && context->ft)
    {
        /* Widget.SerialNumber=1001 */
        Widget_Construct(&w, context);
        Widget_Set_SerialNumber(&w, 1001);
        Widget_Set_ModelNumber(&w, 1);
        Widget_Set_Color(&w, MI_T("Red"));
        SetArray(&w);
        Widget_Post(&w, context);
        Widget_Destruct(&w);
    }  
    
    if (context && context->ft)
    {
        /* Widget.SerialNumber=1002 */
        Widget_Construct(&w, context);
        Widget_Set_SerialNumber(&w, 1002);
        Widget_Set_ModelNumber(&w, 2);
        Widget_Set_Color(&w, MI_T("Blue"));
        SetArray(&w);
        Widget_Post(&w, context);
        Widget_Destruct(&w);
    }
    
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Widget_GetInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* instanceName,
    const MI_PropertySet* propertySet)
{
    Widget w;

    /* Widget.SerialNumber=1001 */
    if (context && context->ft && instanceName->SerialNumber.value == 1001)
    {
        Widget_Construct(&w, context);
        Widget_Set_SerialNumber(&w, 1001);
        Widget_Set_ModelNumber(&w, 1);
        Widget_Set_Color(&w, MI_T("Red"));
        Widget_Post(&w, context);
        Widget_Destruct(&w);
        MI_PostResult(context, MI_RESULT_OK);
        return;
    }

    /* Widget.SerialNumber=1002 */
    if (context && context->ft && instanceName->SerialNumber.value == 1002)
    {
        Widget_Construct(&w, context);
        Widget_Set_SerialNumber(&w, 1002);
        Widget_Set_ModelNumber(&w, 2);
        Widget_Set_Color(&w, MI_T("Blue"));
        Widget_Post(&w, context);
        Widget_Destruct(&w);
        MI_PostResult(context, MI_RESULT_OK);
        return;
    }

    MI_PostResult(context, MI_RESULT_NOT_FOUND);
}

void MI_CALL Widget_CreateInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Widget_ModifyInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Widget_DeleteInstance(
    Widget_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Widget* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

