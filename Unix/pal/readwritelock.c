#include "palcommon.h"

#if defined(CONFIG_HAVE_ATOMIC_INTRINSICS)
# include "readwritelockatomic.c"
#else
# include "readwritelockposix.c"
#endif
