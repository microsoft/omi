/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
