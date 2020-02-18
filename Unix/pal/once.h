/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _pal_once_h
#define _pal_once_h

#include "palcommon.h"
#include "atomic.h"

PAL_BEGIN_EXTERNC

typedef struct _Once
{
    void* value;
}
Once;

#define ONCE_STATE_INVOKING         -2 
#define ONCE_STATE_NOTINVOKEDYET    -1

#define ONCE_INITIALIZER { (void*)ONCE_STATE_NOTINVOKEDYET }

typedef _Success_(return == 0) int (*OnceWorkerFunction)(
    _In_ void* data,
    _Outptr_result_maybenull_ void** value);

int __Once_Invoke(
    _Inout_ Once* self,
    _In_ OnceWorkerFunction func,
    _In_ void* data);

PAL_INLINE int Once_Invoke(
    _Inout_ Once* self,
    _In_ OnceWorkerFunction func,
    _In_ void* data)
{
    int result = 0;
    void* value = self->value;

/* To prevent confusing behavior, disallow compiler reordering. */
#if defined(__GNUC__)
    asm volatile("" ::: "memory");
#else
    /* Nothing. */
#endif

    if ((size_t)value >= (size_t)ONCE_STATE_INVOKING)
        result = __Once_Invoke(self, func, data);

    return result;
}

/* All callers to Once_Invoke (except _WithBarrier) must dereference
 * initialized data through this macro. */
#define Once_Invoke_Value(self) ((self)->value)

PAL_INLINE int Once_Invoke_WithBarrier(
    _Inout_ Once* self,
    _In_ OnceWorkerFunction func,
    _In_ void* data)
{
    int result = Once_Invoke(self, func, data);

    NonX86MemoryBarrier();
    return result;
}

PAL_END_EXTERNC

#endif /* _pal_once_h */
