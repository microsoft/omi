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
#include "ABC_ElementConformsToProfile.h"
#include "utils.h"

static void PostInstance(
    MI_Context* context,
    const Fan* fanData,
    const Profile* profileData)
{
    ABC_Fan fan;
    ABC_RegisteredProfile profile;
    ABC_ElementConformsToProfile conforms;

    /* ManagedElement */
    ConstructFan(&fan, context, fanData, MI_TRUE);

    /* ConformantStandard */
    ConstructProfile(&profile, context, profileData, MI_TRUE);

    /* ElementConformsToProfile */
    ABC_ElementConformsToProfile_Construct(&conforms, context);
    ABC_ElementConformsToProfile_Set_ConformantStandard(&conforms,&profile);
    ABC_ElementConformsToProfile_Set_ManagedElement(&conforms, &fan);

    /* Post the instance */
    ABC_ElementConformsToProfile_Post(&conforms, context);
}

void MI_CALL ABC_ElementConformsToProfile_Load(
    ABC_ElementConformsToProfile_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_ElementConformsToProfile_Unload(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_ElementConformsToProfile_EnumerateInstances(
    ABC_ElementConformsToProfile_Self* self,
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
        PostInstance(context, &fans[i], &profiles[i]);
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_ElementConformsToProfile_GetInstance(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ElementConformsToProfile* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_ElementConformsToProfile_CreateInstance(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ElementConformsToProfile* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_ElementConformsToProfile_ModifyInstance(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ElementConformsToProfile* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_ElementConformsToProfile_DeleteInstance(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ElementConformsToProfile* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_ElementConformsToProfile_AssociatorInstancesConformantStandard(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_RegisteredProfile* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    if (strcmp(instanceName->InstanceID.value, FAN_PROFILE_INSTANCEID) == 0)
    {
        size_t i;

        for (i = 0; i < fansSize; i++)
        {
            ABC_Fan inst;
            ConstructFan(&inst, context, &fans[i], MI_FALSE);
            ABC_Fan_Post(&inst, context);
        }

        MI_PostResult(context, MI_RESULT_OK);
        return;
    }
    else
    {
        MI_PostResult(context, MI_RESULT_NOT_FOUND);
        return;
    }
}

void MI_CALL ABC_ElementConformsToProfile_AssociatorInstancesManagedElement(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Fan* instanceName,
    const MI_Char* resultClass,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    /* No fan instances in this namespace */
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL ABC_ElementConformsToProfile_ReferenceInstancesConformantStandard(
    ABC_ElementConformsToProfile_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_RegisteredProfile* instanceName,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL ABC_ElementConformsToProfile_ReferenceInstancesManagedElement(
    ABC_ElementConformsToProfile_Self* self,
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

