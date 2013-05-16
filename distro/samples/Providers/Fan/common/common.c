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

#include "capabilities.h"
#include "fan.h"
#include "profile.h"
#include "sensor.h"

/*
**==============================================================================
**
** capabilities
**
**==============================================================================
*/

Capabilities capabilities[] =
{
    {
        "CAPABILITIES:1", /* InstanceID */
        "Fan Capabilities", /* Caption */
        { 2, 3, 11 }, /* RequestedStatesSupportedSize (Enabled, Disabled) */
        3,
    },
    {
        "CAPABILITIES:2", /* InstanceID */
        "Fan Capabilities", /* Caption */
        { 2, 3, 11 }, /* RequestedStatesSupportedSize (Enabled, Disabled) */
        3,
    },
    {
        "CAPABILITIES:3", /* InstanceID */
        "Fan Capabilities", /* Caption */
        { 2, 3, 11 }, /* RequestedStatesSupportedSize (Enabled, Disabled) */
        3,
    },
    {
        "CAPABILITIES:4", /* InstanceID */
        "Fan Capabilities", /* Caption */
        { 2, 3, 11 }, /* RequestedStatesSupportedSize (Enabled, Disabled) */
        3,
    },
};

size_t capabilitiesSize = MI_COUNT(capabilities);

/*
**==============================================================================
**
** fans
**
**==============================================================================
*/

Fan fans[] =
{
    {
        "root/omi",
        "ABC_ComputerSystem",
        "ABC_Fan",
        "linux-22",
        "FAN:1", /* InstallDate */
        "CPU FAN", /* ElementName */
        MI_TRUE, /* VariableSpeed */
        10000, /* DesiredSpeed */
        { 2 }, 1, /* OperatingStatus */
        5, /* HealthState */
        2 /* EnabledState */
    },
    {
        "root/omi",
        "ABC_ComputerSystem",
        "ABC_Fan",
        "linux-22",
        "FAN:2", /* InstallDate */
        "CPU FAN", /* ElementName */
        MI_TRUE, /* VariableSpeed */
        10000, /* DesiredSpeed */
        { 2 }, 1, /* OperatingStatus */
        5, /* HealthState */
        2 /* EnabledState */
    },
    {
        "root/omi",
        "ABC_ComputerSystem",
        "ABC_Fan",
        "linux-22",
        "FAN:3", /* InstallDate */
        "CHASIS FAN", /* ElementName */
        MI_TRUE, /* VariableSpeed */
        20000, /* DesiredSpeed */
        { 2 }, 1, /* OperatingStatus */
        5, /* HealthState */
        2 /* EnabledState */
    },
    {
        "root/omi",
        "ABC_ComputerSystem",
        "ABC_Fan",
        "linux-22",
        "FAN:4", /* InstallDate */
        "CHASIS FAN", /* ElementName */
        MI_TRUE, /* VariableSpeed */
        20000, /* DesiredSpeed */
        { 2 }, 1, /* OperatingStatus */
        5, /* HealthState */
        2 /* EnabledState */
    },
};

size_t fansSize = MI_COUNT(fans);

/*
**==============================================================================
**
** profiles
**
**==============================================================================
*/

Profile profiles[] =
{
    {
        FAN_PROFILE_INSTANCEID,
        "Fan",
        "1.0.1",
        2,
    },
};

size_t profilesSize = MI_COUNT(profiles);

/*
**==============================================================================
**
** sensors
**
**==============================================================================
*/

Sensor sensors[] =
{
    {
        "ABC_ComputerSystem", /* SystemCreationClassName */
        "linux-22", /* SystemName */
        "ABC_NumericSensor", /* CreationClassName */
        "SENSOR:1", /* DeviceID */
        19, /* BaseUnits (RPM) */
        3, /* UnitModifier */
        0, /* RateUnits (None) */
        5, /* CurrentReading */
        5, /* SensorType (Tachometer) */
        { "OK", "Lower Non Critical", "Upper Non Critical", "Lower Critical", "Upper Critical"},  /* PossibleStatesSize */
        5, /* PossibleStatesSizeSize */
        "OK", /* CurrentState */
        { 2, }, /* OperationalStatus (OK) */
        1, /* OperationalStatusSize */
        5, /* HealthState (OK) */
    },
    {
        "ABC_ComputerSystem", /* SystemCreationClassName */
        "linux-22", /* SystemName */
        "ABC_NumericSensor", /* CreationClassName */
        "SENSOR:2", /* DeviceID */
        19, /* BaseUnits (RPM) */
        3, /* UnitModifier */
        0, /* RateUnits (None) */
        5, /* CurrentReading */
        5, /* SensorType (Tachometer) */
        { "OK", "Lower Non Critical", "Upper Non Critical", "Lower Critical", "Upper Critical"},  /* PossibleStatesSize */
        5, /* PossibleStatesSizeSize */
        "OK", /* CurrentState */
        { 2, }, /* OperationalStatus (OK) */
        1, /* OperationalStatusSize */
        5, /* HealthState (OK) */
    },
    {
        "ABC_ComputerSystem", /* SystemCreationClassName */
        "linux-22", /* SystemName */
        "ABC_NumericSensor", /* CreationClassName */
        "SENSOR:3", /* DeviceID */
        19, /* BaseUnits (RPM) */
        3, /* UnitModifier */
        0, /* RateUnits (None) */
        5, /* CurrentReading */
        5, /* SensorType (Tachometer) */
        { "OK", "Lower Non Critical", "Upper Non Critical", "Lower Critical", "Upper Critical"},  /* PossibleStatesSize */
        5, /* PossibleStatesSizeSize */
        "OK", /* CurrentState */
        { 2, }, /* OperationalStatus (OK) */
        1, /* OperationalStatusSize */
        5, /* HealthState (OK) */
    },
    {
        "ABC_ComputerSystem", /* SystemCreationClassName */
        "linux-22", /* SystemName */
        "ABC_NumericSensor", /* CreationClassName */
        "SENSOR:4", /* DeviceID */
        19, /* BaseUnits (RPM) */
        3, /* UnitModifier */
        0, /* RateUnits (None) */
        5, /* CurrentReading */
        5, /* SensorType (Tachometer) */
        { "OK", "Lower Non Critical", "Upper Non Critical", "Lower Critical", "Upper Critical"},  /* PossibleStatesSize */
        5, /* PossibleStatesSizeSize */
        "OK", /* CurrentState */
        { 2, }, /* OperationalStatus (OK) */
        1, /* OperationalStatusSize */
        5, /* HealthState (OK) */
    },
};

size_t sensorsSize = MI_COUNT(sensors);
