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
#include "ABC_NumericSensor.h"
#include "utils.h"

void MI_CALL ABC_NumericSensor_Load(
    ABC_NumericSensor_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_NumericSensor_Unload(
    ABC_NumericSensor_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_NumericSensor_EnumerateInstances(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    size_t i;

    for (i = 0; i < sensorsSize; i++)
    {
        ABC_NumericSensor inst;
        ConstructSensor(&inst, context, &sensors[i], MI_FALSE);
        ABC_NumericSensor_Post(&inst, context);
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_NumericSensor_GetInstance(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_NumericSensor* instanceName,
    const MI_PropertySet* propertySet)
{
    size_t i;

    for (i = 0; i < sensorsSize; i++)
    {
        if (MatchSensor(instanceName, &sensors[i]))
        {
            ABC_NumericSensor inst;
            ConstructSensor(&inst, context, &sensors[i], MI_FALSE);
            ABC_NumericSensor_Post(&inst, context);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_NOT_FOUND);
}

void MI_CALL ABC_NumericSensor_CreateInstance(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_NumericSensor* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_NumericSensor_ModifyInstance(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_NumericSensor* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_NumericSensor_DeleteInstance(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_NumericSensor* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_NumericSensor_Invoke_RequestStateChange(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_RequestStateChange* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_NumericSensor_Invoke_SetPowerState(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_SetPowerState* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_NumericSensor_Invoke_Reset(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_Reset* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_NumericSensor_Invoke_EnableDevice(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_EnableDevice* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_NumericSensor_Invoke_OnlineDevice(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_OnlineDevice* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_NumericSensor_Invoke_QuiesceDevice(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_QuiesceDevice* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_NumericSensor_Invoke_SaveProperties(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_SaveProperties* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_NumericSensor_Invoke_RestoreProperties(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_RestoreProperties* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_NumericSensor_Invoke_RestoreDefaultThresholds(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_RestoreDefaultThresholds* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_NumericSensor_Invoke_GetNonLinearFactors(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_GetNonLinearFactors* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

