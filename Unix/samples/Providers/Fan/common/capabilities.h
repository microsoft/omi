/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _capabilities_h
#define _capabilities_h

#include <MI.h>

typedef struct _Capabilities
{
    const char* InstanceID; /* Key */
    const char* Caption;
    unsigned short RequestedStatesSupported[8];
    size_t RequestedStatesSupportedSize;
}
Capabilities;

extern Capabilities capabilities[];

extern size_t capabilitiesSize;

#endif /* _capabilities_h */
