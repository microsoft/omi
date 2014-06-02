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

#include "utils.h"

void ConstructFan(
    ABC_Fan* inst,
    MI_Context* context,
    const Fan* fan,
    int keysOnly)
{
    ABC_Fan_Construct(inst, context);

    MI_Instance_SetNameSpace(&inst->__instance, fan->NameSpace);
    ABC_Fan_Set_SystemCreationClassName(inst, fan->SystemCreationClassName);
    ABC_Fan_Set_CreationClassName(inst, fan->CreationClassName);
    ABC_Fan_Set_SystemName(inst, fan->SystemName);
    ABC_Fan_Set_DeviceID(inst, fan->DeviceID);
    ABC_Fan_Set_ElementName(inst, fan->ElementName);
    ABC_Fan_Set_VariableSpeed(inst, fan->VariableSpeed);
    ABC_Fan_Set_DesiredSpeed(inst, fan->DesiredSpeed);
    ABC_Fan_Set_OperationalStatus(
        inst,
        fan->OperationalStatus,
        fan->OperationalStatusSize);
    ABC_Fan_Set_HealthState(inst, fan->HealthState);
    ABC_Fan_Set_EnabledState(inst, fan->EnabledState);
}

MI_Boolean MatchFan(
    const ABC_Fan* inst,
    const Fan* fan)
{
    if (strcmp(inst->DeviceID.value, fan->DeviceID) == 0 &&
        strcmp(inst->SystemCreationClassName.value, fan->SystemCreationClassName) == 0 &&
        strcmp(inst->CreationClassName.value, fan->CreationClassName) == 0 &&
        strcmp(inst->SystemName.value, fan->SystemName) == 0)
    {
        return MI_TRUE;
    }

    return MI_FALSE;
}


void ConstructProfile(
    ABC_RegisteredProfile* inst,
    MI_Context* context,
    const Profile* profile,
    int keysOnly)
{
    ABC_RegisteredProfile_Construct(inst, context);
    ABC_RegisteredProfile_Set_InstanceID(inst, profile->InstanceID);

    if (!keysOnly)
    {
        ABC_RegisteredProfile_Set_RegisteredName(inst, profile->RegisteredName);
        ABC_RegisteredProfile_Set_RegisteredVersion(inst,
            profile->RegisteredVersion);
        ABC_RegisteredProfile_Set_RegisteredOrganization(inst,
            profile->RegisteredOrganization);
    }
}

MI_Boolean MatchProfile(
    const ABC_RegisteredProfile* inst,
    const Profile* profile)
{
    if (strcmp(inst->InstanceID.value, profile->InstanceID) == 0)
    {
        return MI_TRUE;
    }

    return MI_FALSE;
}
