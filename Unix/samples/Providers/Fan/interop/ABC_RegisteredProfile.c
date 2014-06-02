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

