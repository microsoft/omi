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
