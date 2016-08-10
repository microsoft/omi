/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "utils.h"

void ConstructCapabilities(
    ABC_EnabledLogicalElementCapabilities* inst,
    MI_Context* context,
    const Capabilities* capabilities,
    int keysOnly)
{
    ABC_EnabledLogicalElementCapabilities_Construct(inst, context);

    ABC_EnabledLogicalElementCapabilities_Set_InstanceID(inst,
        capabilities->InstanceID);
    ABC_EnabledLogicalElementCapabilities_Set_Caption(inst,
        capabilities->Caption);
    ABC_EnabledLogicalElementCapabilities_Set_RequestedStatesSupported(inst,
        capabilities->RequestedStatesSupported,
        capabilities->RequestedStatesSupportedSize);
}

MI_Boolean MatchCapabilities(
    const ABC_EnabledLogicalElementCapabilities* inst,
    const Capabilities* capabilities)
{
    if (strcmp(inst->InstanceID.value, capabilities->InstanceID) == 0)
    {
        return MI_TRUE;
    }

    return MI_FALSE;
}

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

void ConstructSensor(
    ABC_NumericSensor* inst,
    MI_Context* context,
    const Sensor* sensor,
    int keysOnly)
{
    ABC_NumericSensor_Construct(inst, context);

    ABC_NumericSensor_Set_SystemCreationClassName(inst, sensor->SystemCreationClassName);
    ABC_NumericSensor_Set_CreationClassName(inst, sensor->CreationClassName);
    ABC_NumericSensor_Set_SystemName(inst, sensor->SystemName);
    ABC_NumericSensor_Set_DeviceID(inst, sensor->DeviceID);

    ABC_NumericSensor_Set_BaseUnits(inst, sensor->BaseUnits);
    ABC_NumericSensor_Set_UnitModifier(inst, sensor->UnitModifier);
    ABC_NumericSensor_Set_CurrentReading(inst, sensor->CurrentReading);
    ABC_NumericSensor_Set_SensorType(inst, sensor->SensorType);
    ABC_NumericSensor_Set_PossibleStates(inst,
        (const MI_Char**)sensor->PossibleStates,
        sensor->PossibleStatesSize);
    ABC_NumericSensor_Set_CurrentState(inst, sensor->CurrentState);
    ABC_NumericSensor_Set_OperationalStatus(inst, sensor->OperationalStatus,
        sensor->OperationalStatusSize);
    ABC_NumericSensor_Set_HealthState(inst, sensor->HealthState);
}

MI_Boolean MatchSensor(
    const ABC_NumericSensor* inst,
    const Sensor* sensor)
{
    if (strcmp(inst->DeviceID.value, sensor->DeviceID) == 0 &&
        strcmp(inst->SystemCreationClassName.value, sensor->SystemCreationClassName) == 0 &&
        strcmp(inst->CreationClassName.value, sensor->CreationClassName) == 0 &&
        strcmp(inst->SystemName.value, sensor->SystemName) == 0)
    {
        return MI_TRUE;
    }

    return MI_FALSE;
}
