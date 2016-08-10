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
#include "Connector.h"

void MI_CALL Connector_Load(
    Connector_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Connector_Unload(
    Connector_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
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
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Connector_GetInstance(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Connector* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Connector_CreateInstance(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Connector* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Connector_ModifyInstance(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Connector* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Connector_DeleteInstance(
    Connector_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Connector* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
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
    /* Find hardcoded associators of Widget.SerialNumber=1001 */
    if (instanceName->SerialNumber.value == 1001)
    {
        Gadget g;

        /* Gadget.SerialNumber=3007 */
        Gadget_Construct(&g, context);
        Gadget_Set_SerialNumber(&g, 3007);
        Gadget_Post(&g, context);
        Gadget_Destruct(&g);

        /* Gadget.SerialNumber=3008 */
        Gadget_Construct(&g, context);
        Gadget_Set_SerialNumber(&g, 3008);
        Gadget_Post(&g, context);
        Gadget_Destruct(&g);
    }

    MI_PostResult(context, MI_RESULT_OK);
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
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
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
    /* Find hardcoded references of Widget.SerialNumber=1001 */
    if (instanceName->SerialNumber.value == 1001)
    {
        Widget left;

        /* Widget.SerialNumber=1001 */
        Widget_Construct(&left, context);
        Widget_Set_SerialNumber(&left, 1001);

        /*Connector.Left="Widget.SerialNumber=1001","Gadget.SerialNumber=3007"*/
        {
            Gadget right;
            Connector c;
            Gadget_Construct(&right, context);
            Gadget_Set_SerialNumber(&right, 3007);
            Connector_Construct(&c, context);
            Connector_Set_Left(&c, &left);
            Connector_Set_Right(&c, &right);
            Connector_Post(&c, context);
            Connector_Destruct(&c);
            Gadget_Destruct(&right);
        }

        /*Connector.Left="Widget.SerialNumber=1001","Gadget.SerialNumber=3008"*/
        {
            Gadget right;
            Connector c;
            Gadget_Construct(&right, context);
            Gadget_Set_SerialNumber(&right, 3008);
            Connector_Construct(&c, context);
            Connector_Set_Left(&c, &left);
            Connector_Set_Right(&c, &right);
            Connector_Post(&c, context);
            Connector_Destruct(&c);
            Gadget_Destruct(&right);
        }

        Widget_Destruct(&left);
    }

    MI_PostResult(context, MI_RESULT_OK);
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
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

