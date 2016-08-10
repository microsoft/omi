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
#include "ABC_RegisteredProfile.h"
#include "utils.h"

void MI_CALL ABC_RegisteredProfile_Load(
    ABC_RegisteredProfile_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_RegisteredProfile_Unload(
    ABC_RegisteredProfile_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_RegisteredProfile_EnumerateInstances(
    ABC_RegisteredProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    size_t i;

    for (i = 0; i < profilesSize; i++)
    {
        ABC_RegisteredProfile inst;
        ConstructProfile(&inst, context, &profiles[i], keysOnly);
        ABC_RegisteredProfile_Post(&inst, context);
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_RegisteredProfile_GetInstance(
    ABC_RegisteredProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_RegisteredProfile* instanceName,
    const MI_PropertySet* propertySet)
{
    size_t i;

    for (i = 0; i < profilesSize; i++)
    {
        if (MatchProfile(instanceName, &profiles[i]))
        {
            ABC_RegisteredProfile inst;
            ConstructProfile(&inst, context, &profiles[i], MI_FALSE);
            ABC_RegisteredProfile_Post(&inst, context);
            MI_PostResult(context, MI_RESULT_OK);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_RegisteredProfile_CreateInstance(
    ABC_RegisteredProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_RegisteredProfile* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_RegisteredProfile_ModifyInstance(
    ABC_RegisteredProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_RegisteredProfile* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_RegisteredProfile_DeleteInstance(
    ABC_RegisteredProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_RegisteredProfile* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

