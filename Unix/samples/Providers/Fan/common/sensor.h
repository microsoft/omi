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

#ifndef _sensor_h
#define _sensor_h

#include <MI.h>

typedef struct _Sensor
{
    const char* SystemCreationClassName;
    const char* SystemName;
    const char* CreationClassName;
    const char* DeviceID;
    unsigned short BaseUnits;
    signed int UnitModifier;
    unsigned short RateUnits;
    signed int CurrentReading;
    unsigned short SensorType;
    const MI_Char* PossibleStates[8];
    size_t PossibleStatesSize;
    const char* CurrentState;
    unsigned short OperationalStatus[8];
    size_t OperationalStatusSize;
    unsigned short HealthState;
}
Sensor;

extern Sensor sensors[];

extern size_t sensorsSize;

#endif /* _sensor_h */
