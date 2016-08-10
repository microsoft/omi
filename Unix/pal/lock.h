/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _pal_lock_h
#define _pal_lock_h

#include "palcommon.h"

#if defined(CONFIG_HAVE_ATOMIC_INTRINSICS)
# include "lockatomic.h"
#else
# include "lockposix.h"
#endif

#endif /* _pal_lock_h */
