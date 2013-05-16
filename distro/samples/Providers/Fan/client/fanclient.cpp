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

#include <cstdlib>
#include <cstdio>
#include <omiclient/client.h>
#include <base/paths.h>

using namespace mi;

const char* arg0;

bool Connect(Client& client)
{
    const Uint64 TIMEOUT = 10 * 1000000;
    return client.Connect(
        GetPath(ID_SOCKETFILE),
        String(),
        String(),
        TIMEOUT);
}

Result FindFanProfile(Client& client, DInstance& fanProfile)
{
    // Enumerate instances of CIM_RegisteredProfile:

    const Uint64 TIMEOUT = 10 * 1000000;
    Array<DInstance> instances;
    Result result;

    if (!client.EnumerateInstances(
        "interop",
        "CIM_RegisteredProfile",
        true,
        TIMEOUT,
        instances,
        String(),
        String(),
        result))
    {
        return result;
    }

    if (result != MI_RESULT_OK)
    {
        return result;
    }

    // Find the Fan profile with these keys:
    //     RegisteredOrganization=2
    //     RegisteredName=Fan
    //     RegisteredVersion=1.0.1

    for (size_t i = 0; i < instances.GetSize(); i++)
    {
        const DInstance& inst = instances[i];

        Uint16 RegisteredOrganization; 

        if (!inst.GetUint16("RegisteredOrganization", RegisteredOrganization))
        {
            continue;
        }

        String RegisteredName;

        if (!inst.GetString("RegisteredName", RegisteredName))
        {
            continue;
        }

        String RegisteredVersion;

        if (!inst.GetString("RegisteredVersion", RegisteredVersion))
        {
            continue;
        }

        if (RegisteredOrganization != 2 ||
            RegisteredName != "Fan" ||
            RegisteredVersion != "1.0.1")
        {
            continue;
        }

        fanProfile = inst;
        return MI_RESULT_OK;
    }

    // Not found!
    return MI_RESULT_NOT_FOUND;
}

Result FindConformingFans(
    Client& client, 
    const DInstance& fanProfile,    
    Array<DInstance>& fans)
{
    const Uint64 TIMEOUT = 10 * 1000000;
    Result result;

    // Find associated fans:

    if (!client.AssociatorInstances(
        "interop",
        fanProfile,
        "CIM_ElementConformsToProfile",
        "CIM_Fan",
        "ConformantStandard",
        "ManagedElement",
        TIMEOUT,
        fans,
        result))
    {
        return result;
    }

    if (result != MI_RESULT_OK)
    {
        return result;
    }

    return MI_RESULT_OK;
}

Result ResetFan(
    Client& client,
    const DInstance& fan)
{
    // Find associated capability:

    const Uint64 TIMEOUT = 10 * 1000000;
    Result result;
    Array<DInstance> capabilities;

    if (!client.AssociatorInstances(
        fan.GetNamespace(),
        fan,
        "CIM_ElementCapabilities",
        "CIM_EnabledLogicalElementCapabilities",
        "ManagedElement",
        "Capabilities",
        TIMEOUT,
        capabilities,
        result))
    {
        return result;
    }

    if (result != MI_RESULT_OK)
    {
        return result;
    }

    if (capabilities.GetSize() != 1)
    {
        return MI_RESULT_NOT_SUPPORTED;
    }

    const DInstance& caps = capabilities[0];

    // Check whether Reset is supported:

    Array<Uint16> states;

    if (!caps.GetUint16A("RequestedStatesSupported", states))
    {
        return MI_RESULT_NOT_SUPPORTED;
    }

    bool resetSupported = false;

    for (size_t i = 0; i < states.GetSize(); i++)
    {
        if (states[i] == 11)
            resetSupported = true;
    }

    if (!resetSupported)
    {
        return MI_RESULT_NOT_SUPPORTED;
    }

    // Invoke CIM_Fan.RequestStateChange(RequestedState=11)

    DInstance in;
    in.AddUint16("RequestedState", 11);
    DInstance out;

    if (!client.Invoke(
        fan.GetNamespace(),
        fan,
        "RequestStateChange",
        in,
        TIMEOUT,
        out,
        result))
    {
        return result;
    }

    if (result != MI_RESULT_OK)
    {
        return result;
    }

    return result;
}

Result GetFanSpeed(
    Client& client, 
    const DInstance& fan,
    Sint32& Speed)
{
    const Uint64 TIMEOUT = 10 * 1000000;
    Result result;
    Array<DInstance> sensors;

    if (!client.AssociatorInstances(
        fan.GetNamespace(),
        fan,
        "CIM_AssociatedSensor",
        "CIM_NumericSensor",
        "Dependent",
        "Antecedent",
        TIMEOUT,
        sensors,
        result))
    {
        return result;
    }

    if (result != MI_RESULT_OK)
    {
        return result;
    }

    if (sensors.GetSize() != 1)
    {
        return MI_RESULT_FAILED;
    }

    const DInstance& sensor = sensors[0];

    // Fan.SensorType=5 (Tachometer)
    {
        Uint16 SensorType;

        if (!sensor.GetUint16("SensorType", SensorType) || SensorType != 5)
        {
            return MI_RESULT_NOT_SUPPORTED;
        }
    }

    // Fan.BaseUnits=19?
    {
        Uint16 BaseUnits;

        if (!sensor.GetUint16("BaseUnits", BaseUnits) || BaseUnits != 19)
        {
            return MI_RESULT_NOT_SUPPORTED;
        }
    }

    // Fan.RateUnits=19?
    {
        Uint16 RateUnits;

        if (!sensor.GetUint16("RateUnits", RateUnits) || RateUnits != 0)
        {
            return MI_RESULT_NOT_SUPPORTED;
        }
    }

    // CurrentReading:

    if (!sensor.GetSint32("CurrentReading", Speed))
    {
        return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
}

int main(int argc, char** argv)
{
    arg0 = argv[0];

    // Connect to the server:

    Client client;

    if (!Connect(client))
    {
        fprintf(stderr, "%s: Connect() failed\n", arg0);
        exit(1);
    }

    // Find the Fan profile:

    DInstance fanProfile;
    {
        Result result = FindFanProfile(client, fanProfile);

        if (result != MI_RESULT_OK)
        {
            fprintf(stderr, "%s: FindFanProfile(): result=%u\n", arg0,
                result);
            exit(1);
        }
    }

    // Find associated fans in the other namespace:

    Array<DInstance> fans;
    {
        Result result = FindConformingFans(client, fanProfile, fans);

        if (result != MI_RESULT_OK)
        {
            fprintf(stderr, "%s: FindConformingFans(): result=%u\n", 
                arg0, result);
            exit(1);
        }
    }

    // Reset all these fans:

    for (size_t i = 0; i < fans.GetSize(); i++)
    {
        Result result = ResetFan(client, fans[i]);

        if (result != MI_RESULT_OK)
        {
            fprintf(stderr, "ResetFan(): result=%u\n", result);
        }
    }

    // Print the sensor speed for each fan:

    printf("success!\n");

    for (size_t i = 0; i < fans.GetSize(); i++)
    {
        Sint32 Speed;
        Result result = GetFanSpeed(client, fans[i], Speed);

        if (result != MI_RESULT_OK)
        {
            fprintf(stderr, "GetFanSpeed(): result=%u\n", result);
            continue;
        }

        printf("Speed: %d\n", Speed);
    }

    // Reset all the fans:

    return 0;
}
