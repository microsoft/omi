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
#include "ABC_EnabledLogicalElementCapabilities.h"
#include "utils.h"

void MI_CALL ABC_EnabledLogicalElementCapabilities_Load(
    ABC_EnabledLogicalElementCapabilities_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_EnabledLogicalElementCapabilities_Unload(
    ABC_EnabledLogicalElementCapabilities_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_EnabledLogicalElementCapabilities_EnumerateInstances(
    ABC_EnabledLogicalElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    size_t i;

    for (i = 0; i < capabilitiesSize; i++)
    {
        ABC_EnabledLogicalElementCapabilities inst;
        ConstructCapabilities(&inst, context, &capabilities[i], MI_FALSE);
        ABC_EnabledLogicalElementCapabilities_Post(&inst, context);
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_EnabledLogicalElementCapabilities_GetInstance(
    ABC_EnabledLogicalElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EnabledLogicalElementCapabilities* instanceName,
    const MI_PropertySet* propertySet)
{
    size_t i;

    for (i = 0; i < capabilitiesSize; i++)
    {
        if (MatchCapabilities(instanceName, &capabilities[i]))
        {
            ABC_EnabledLogicalElementCapabilities inst;
            ConstructCapabilities(&inst, context, &capabilities[i], MI_FALSE);
            ABC_EnabledLogicalElementCapabilities_Post(&inst, context);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_NOT_FOUND);
}

void MI_CALL ABC_EnabledLogicalElementCapabilities_CreateInstance(
    ABC_EnabledLogicalElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EnabledLogicalElementCapabilities* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_EnabledLogicalElementCapabilities_ModifyInstance(
    ABC_EnabledLogicalElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EnabledLogicalElementCapabilities* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_EnabledLogicalElementCapabilities_DeleteInstance(
    ABC_EnabledLogicalElementCapabilities_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EnabledLogicalElementCapabilities* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

