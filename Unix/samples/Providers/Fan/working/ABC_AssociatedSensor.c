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
#include "ABC_AssociatedSensor.h"
#include "utils.h"

static void PostInstance(
    MI_Context* context,
    const Fan* fanData,
    const Sensor* sensorData)
{
    ABC_Fan fan;
    ABC_NumericSensor sensor;
    ABC_AssociatedSensor conforms;

    /* ManagedElement */
    ConstructFan(&fan, context, fanData, MI_TRUE);

    /* ConformantStandard */
    ConstructSensor(&sensor, context, sensorData, MI_TRUE);

    /* AssociatedSensor */
    ABC_AssociatedSensor_Construct(&conforms, context);
    ABC_AssociatedSensor_Set_Antecedent(&conforms, &sensor);
    ABC_AssociatedSensor_Set_Dependent(&conforms, &fan);

    /* Post the instance */
    ABC_AssociatedSensor_Post(&conforms, context);
}

void MI_CALL ABC_AssociatedSensor_Load(
    ABC_AssociatedSensor_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_AssociatedSensor_Unload(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_AssociatedSensor_EnumerateInstances(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    size_t i;

    for (i = 0; i < fansSize; i++)
    {
        PostInstance(context, &fans[i], &sensors[i]);
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_AssociatedSensor_GetInstance(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_AssociatedSensor* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_AssociatedSensor_CreateInstance(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_AssociatedSensor* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_AssociatedSensor_ModifyInstance(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_AssociatedSensor* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_AssociatedSensor_DeleteInstance(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_AssociatedSensor* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_AssociatedSensor_AssociatorInstancesAntecedent(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_NumericSensor* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    size_t i = 0;

    for (i = 0; i < sensorsSize; i++)
    {
        if (MatchSensor(instanceName, &sensors[i]))
        {
            ABC_Fan inst;
            ConstructFan(&inst, context, &fans[i], MI_FALSE);
            ABC_Fan_Post(&inst, context);
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_AssociatedSensor_AssociatorInstancesDependent(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Fan* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    size_t i = 0;

    for (i = 0; i < fansSize; i++)
    {
        if (MatchFan(instanceName, &fans[i]))
        {
            ABC_NumericSensor inst;
            ConstructSensor(&inst, context, &sensors[i], MI_FALSE);
            ABC_NumericSensor_Post(&inst, context);
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_AssociatedSensor_ReferenceInstancesAntecedent(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_NumericSensor* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_AssociatedSensor_ReferenceInstancesDependent(
    ABC_AssociatedSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Fan* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

