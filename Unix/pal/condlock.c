#include "palcommon.h"

#if defined(CONFIG_HAVE_ATOMIC_INTRINSICS)
# include "condlockatomic.c"
#else
# include "condlockposix.c"
#endif
