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
