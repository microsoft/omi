/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "env.h"
#include <stdlib.h>

char* Dupenv(const char* var)
{
    const char* tmp = getenv(var);

    if (!tmp)
        return NULL;

    return PAL_Strdup(tmp);
}
