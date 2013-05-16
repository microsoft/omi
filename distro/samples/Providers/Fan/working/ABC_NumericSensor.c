/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
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

