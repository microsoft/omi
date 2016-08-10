/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pal/format.h>
#include <pal/dir.h>

extern int servermain(int argc, const char* argv[]);

int agent_main(int argc, const char* argv[]);

int main(int argc, const char* argv[])
{
    const char* arg0 = Basename(argv[0]);

    if (!arg0)
    {
        Ftprintf(stderr, "%s: failed to get program name\n\n", argv[0]);
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
        Ftprintf(stderr, "%s: unknown program name: %s\n\n", argv[0], arg0);
        exit(1);
    }
}
