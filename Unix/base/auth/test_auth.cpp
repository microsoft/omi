/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <base/user.h>

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s username password\n", argv[0]);
        exit(1);
    }

    int r = AuthenticateUser(argv[1], argv[2]);

    if (r != 0)
    {
        fprintf(stderr, "%s: auth failed: %s\n", argv[0], argv[1]);
        exit(1);
    }

    printf("%s: auth okay\n", argv[0]);

    return 0;
}
