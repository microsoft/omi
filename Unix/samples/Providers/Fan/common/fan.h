/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _fan_h
#define _fan_h

#include <MI.h>

typedef struct _Fan
{
    const char* NameSpace;
    const char* SystemCreationClassName;
    const char* CreationClassName;
    const char* SystemName;
    const char* DeviceID;
    const char* ElementName;
    unsigned char VariableSpeed;
    unsigned long long DesiredSpeed;
    unsigned short OperationalStatus[2];
    size_t OperationalStatusSize;
    unsigned short HealthState;
    unsigned short EnabledState;
}
Fan;

extern Fan fans[];

extern size_t fansSize;

#endif /* _fan_h */
