/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "palcommon.h"

#if defined(CONFIG_HAVE_ATOMIC_INTRINSICS)
# include "readwritelockatomic.c"
#else
# include "readwritelockposix.c"
#endif
