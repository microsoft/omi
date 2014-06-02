#ifndef _pal_sleep_h
#define _pal_sleep_h

#include "palcommon.h"

#if defined(PAL_HAVE_POSIX)
# include <unistd.h>
# include <time.h>
#endif

PAL_BEGIN_EXTERNC

PAL_INLINE void Sleep_Milliseconds(
    _In_ unsigned long milliseconds)
{
#if defined(_MSC_VER)
    Sleep((DWORD)milliseconds);
#else
    struct timespec ts;
    ts.tv_sec = (long)(milliseconds / 1000);
    ts.tv_nsec = (long)((milliseconds % 1000) * 1000 * 1000);
    nanosleep(&ts, NULL);
#endif
}

/* invalid time value;
  based on 'memset(0) to init' philosophy; this value must be 0;
  do not re-assign it */
#define TIME_NEVER  0

/* returns current time in micro-sec (usec) since Epoch */
PAL_Boolean PAL_Time(
    PAL_Uint64* time_usec);

PAL_END_EXTERNC

#endif /* _pal_sleep_h */
