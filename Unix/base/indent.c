/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "indent.h"
#include <pal/format.h>

void Indent(FILE* os, size_t level)
{
    size_t i;

    for (i = 0; i < level; i++)
        Ftprintf(os, MI_T("    "));
}
