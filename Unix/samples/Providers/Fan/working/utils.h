/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _utils_h
#define _utils_h

#include "ABC_Fan.h"
#include "ABC_EnabledLogicalElementCapabilities.h"
#include "ABC_RegisteredProfile.h"
#include "ABC_NumericSensor.h"
#include "common/fan.h"
#include "common/profile.h"
#include "common/capabilities.h"
#include "common/sensor.h"

void ConstructCapabilities(
    ABC_EnabledLogicalElementCapabilities* inst,
    MI_Context* context,
    const Capabilities* capabilities,
    int keysOnly);

MI_Boolean MatchCapabilities(
    const ABC_EnabledLogicalElementCapabilities* inst,
    const Capabilities* capabilities);

void ConstructFan(
    ABC_Fan* inst,
    MI_Context* context,
    const Fan* fan,
    int keysOnly);

MI_Boolean MatchFan(
    const ABC_Fan* inst,
    const Fan* fan);

void ConstructProfile(
    ABC_RegisteredProfile* inst,
    MI_Context* context,
    const Profile* profile,
    int keysOnly);

MI_Boolean MatchProfile(
    const ABC_RegisteredProfile* inst,
    const Profile* profile);

void ConstructSensor(
    ABC_NumericSensor* inst,
    MI_Context* context,
    const Sensor* sensor,
    int keysOnly);

MI_Boolean MatchSensor(
    const ABC_NumericSensor* inst,
    const Sensor* sensor);

#endif /* _utils_h */
