/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <cstdlib>
#include <cstdio>
#include <base/paths.h>
#include "FanProfile.h"

int main(int argc, char** argv)
{
    FanProfile profile;

    if (!FanProfile::Load(profile))
    {
        fprintf(stderr, "Load() failed\n");
        exit(1);
    }

    Array<Fan> fans;

    if (!profile.GetFans(fans))
    {
        fprintf(stderr, "GetFans() failed\n");
        exit(1);
    }

    for (size_t i = 0; i < fans.GetSize(); i++)
    {
        if (!fan[i].Reset())
        {
            fprintf(stderr, "failed to reset fan\n");
        }
    }

    for (size_t i = 0; i < fans.GetSize(); i++)
    {
        Sint32 speed;

        if (!fan[i].GetSpeed(speed))
        {
            fprintf(stderr, "failed to reset fan\n");
            continue;
        }

        printf("speed: %d\n", speed);
    }

    return 0;
}
