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
#include "ABC_ElementCapabilities.h"
#include "utils.h"

static void PostInstance(
    MI_Context* context,
    const Fan* fanData,
    const Capabilities* capabilitiesData)
{
    ABC_Fan fan;
    ABC_EnabledLogicalElementCapabilities capabilities;
    ABC_ElementCapabilities assoc;

    /* ManagedElement */
    ConstructFan(&fan, context, fanData, MI_TRUE);

    /* ConformantStandard */
    ConstructCapabilities(&capabilities, context, capabilitiesData, MI_TRUE);

    /* EnabledLogicalElementCapabilities */
    ABC_ElementCapabilities_Construct(&assoc, context);
    ABC_ElementCapabilities_Set_Capabilities(&assoc, &capabilities);
    ABC_ElementCapabilities_Set_ManagedElement(&assoc, &fan);

    /* Post the instance */
    ABC_ElementCapabilities_Post(&assoc, context);
}

void MI_CALL ABC_ElementCapabilities_Load(
    ABC_ElementCapabilities_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_ElementCapabilities_Unload(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_ElementCapabilities_EnumerateInstances(
    ABC_ElementCapabilities_Self* self,
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
        PostInstance(context, &fans[i], &capabilities[i]);
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_ElementCapabilities_GetInstance(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ElementCapabilities* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_ElementCapabilities_CreateInstance(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ElementCapabilities* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_ElementCapabilities_ModifyInstance(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ElementCapabilities* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_ElementCapabilities_DeleteInstance(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ElementCapabilities* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_ElementCapabilities_AssociatorInstancesManagedElement(
    ABC_ElementCapabilities_Self* self,
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
            ABC_EnabledLogicalElementCapabilities inst;
            ConstructCapabilities(&inst, context, &capabilities[i], MI_FALSE);
            ABC_EnabledLogicalElementCapabilities_Post(&inst, context);
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_ElementCapabilities_AssociatorInstancesCapabilities(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EnabledLogicalElementCapabilities* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    size_t i = 0;

    for (i = 0; i < capabilitiesSize; i++)
    {
        if (MatchCapabilities(instanceName, &capabilities[i]))
        {
            ABC_Fan inst;
            ConstructFan(&inst, context, &fans[i], MI_FALSE);
            ABC_Fan_Post(&inst, context);
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_ElementCapabilities_ReferenceInstancesManagedElement(
    ABC_ElementCapabilities_Self* self,
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

void MI_CALL ABC_ElementCapabilities_ReferenceInstancesCapabilities(
    ABC_ElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EnabledLogicalElementCapabilities* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

