/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _pal_cpu_h
#define _pal_cpu_h

#include "palcommon.h"

#if defined(PAL_HAVE_POSIX)
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# include <sys/types.h>
#endif

PAL_BEGIN_EXTERNC

PAL_INLINE int CPU_GetCount()
{
#if defined(_MSC_VER)
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    return info.dwNumberOfProcessors;
#elif !defined(_SC_NPROCESSORS_ONLN)
    return 1;                           /* ATTN: Not implemented */
#else
    return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}

PAL_INLINE int CPU_GetCurrent()
{
#if defined(_MSC_VER)
    return GetCurrentProcessorNumber();
#elif defined(CONFIG_HAVE_SCHED_GETCPU)
    int sched_getcpu();
    return sched_getcpu();
#else
    /* ATTN: sched_getcpu is not implemented! */
    return 0;
#endif
}

PAL_INLINE ptrdiff_t CPU_GetTimeStamp()
{
#if defined(_MSC_VER) && defined(_ARM_)
	return (ptrdiff_t)(GetTickCount64() * 1000);
#elif defined(_MSC_VER)
	return (ptrdiff_t)(ReadTimeStampCounter() >> 11);
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (ptrdiff_t)(tv.tv_sec * 1000000 + tv.tv_usec);
#endif
}

_Success_(return == 0)
int CPU_GetLocalTimestamp(
    _Out_ PAL_Datetime* current);

_Success_(return == 0)
int CPU_GetUtcTimestamp(
    _Out_ PAL_Datetime* current);

PAL_END_EXTERNC

#endif /* _pal_cpu_h */
