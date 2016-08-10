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
#include "ABC_RegisteredProfile.h"
#include "common/fan.h"
#include "common/profile.h"

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

#endif /* _utils_h */
