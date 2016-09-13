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

int main(int argc, char** argv)
{
    int i;

    for (i = 0; i < argc; i++)
    {
        printf("argv[%u]=%s\n", i, argv[i]);
    }

    exit(0);
//    return 0;
}
