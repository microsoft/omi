/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "state.h"

/* The MAC compiler complains that this struct is unresolved, unless we
 * initialize at least some of it.
 */
MOF_State mofstate = 
{ 
    { NULL }
};
