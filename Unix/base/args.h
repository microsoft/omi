/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_args_h
#define _omi_args_h

#include "config.h"
#include <string.h>
#include <common.h>

BEGIN_EXTERNC

/* Removes the i-th argument from the argc/argv array */
MI_INLINE void Args_Remove(int* argc, char*** argv, size_t i)
{
    memmove(&(*argv)[i], &(*argv)[i+1], sizeof(char*) * ((*argc)-i-1));
    *argc -= 1;
}

END_EXTERNC

#endif /* _omi_args_h */
