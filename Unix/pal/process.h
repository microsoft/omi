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
#include <sys/types.h>
#include <unistd.h>

PAL_BEGIN_EXTERNC

PAL_INLINE PAL_Uint32 Process_ID()
{
    return (PAL_Uint32)getpid();
}

PAL_END_EXTERNC

#endif /* _pal_process_h */
