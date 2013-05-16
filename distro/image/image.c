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

#include <stdio.h>
#include <stdlib.h>
#include <io/io.h>
#include <base/dir.h>

extern int servermain(int argc, const char* argv[]);

int agent_main(int argc, const char* argv[]);

int main(int argc, const char* argv[])
{
    const char* arg0 = Basename(argv[0]);

    if (!arg0)
    {
        Fzprintf(stderr, "%s: failed to get program name\n\n", argv[0]);
        exit(1);
    }

    if (strcmp(arg0, "omiserver") == 0)
    {
        return servermain(argc, argv);
    }
    else if (strcmp(arg0, "omiagent") == 0)
    {
        return agent_main(argc, argv);
    }
    else
    {
        Fzprintf(stderr, "%s: unknown program name: %s\n\n", argv[0], arg0);
        exit(1);
    }
}
