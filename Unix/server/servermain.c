/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <common.h>

int servermain(int argc, _In_reads_(argc) CharPtr* argv, CharPtr *enpv);

int main(int argc, char** argv, char **envp)
{
    /* believe it or not but optimized MS compiler produces warning 4702 
     * (warning C4702: unreachable code) for the next line.
     */
    return servermain(argc,argv,envp);
}
