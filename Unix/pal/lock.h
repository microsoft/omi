#ifndef _pal_lock_h
#define _pal_lock_h

#include "palcommon.h"

#if defined(CONFIG_HAVE_ATOMIC_INTRINSICS)
# include "lockatomic.h"
#else
# include "lockposix.h"
#endif

#endif /* _pal_lock_h */
