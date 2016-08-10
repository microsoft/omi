/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _profile_h
#define _profile_h

#include <MI.h>

#define FAN_PROFILE_INSTANCEID "DMTF:Fan:1.0.1"

typedef struct _Profile
{
    const char* InstanceID;
    const char* RegisteredName;
    const char* RegisteredVersion;
    unsigned short RegisteredOrganization;
}
Profile;

extern Profile profiles[];

extern size_t profilesSize;

#endif /* _profile_h */
