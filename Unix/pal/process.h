/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _pal_process_h
#define _pal_process_h

#include "palcommon.h"
#ifndef _MSC_VER
#include <sys/types.h>
#include <unistd.h>
#endif

PAL_BEGIN_EXTERNC

PAL_INLINE PAL_Uint32 Process_ID()
{
#ifdef _MSC_VER
    return GetCurrentProcessId();
#else
    return (PAL_Uint32)getpid();
#endif
}

PAL_END_EXTERNC

#endif /* _pal_process_h */
