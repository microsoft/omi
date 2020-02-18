/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _pal_memory_h
#define _pal_memory_h

#include "nits/base/nits.h"

PAL_BEGIN_EXTERNC

/* Defining FASTER macro disables malloc injection
   to reduce overhead for manual performance benchmarking.
   It is not defined durring normal builds.
*/
#if !defined(FASTER) && !defined(USE_ALLOCATOR)

PAL_INLINE void *malloc_Injected(
    size_t length,
    NitsCallSite cs)
{
    if (NitsShouldFault(cs, NitsAutomatic))
        return NULL;

    return SystemMalloc(length);
}

#ifdef PAL_Malloc
# undef PAL_Malloc
#endif
#define PAL_Malloc(n) malloc_Injected(n, NitsHere())

PAL_INLINE void *calloc_Injected(
    size_t num,
    size_t size,
    NitsCallSite cs)
{
    if (NitsShouldFault(cs, NitsAutomatic))
        return NULL;

    return SystemCalloc(num, size);
}

#ifdef PAL_Calloc
# undef PAL_Calloc
#endif
#define PAL_Calloc(n, s) calloc_Injected(n, s, NitsHere())

PAL_INLINE void *realloc_Injected(
    _In_ void *originalBuffer,
    size_t length,
    NitsCallSite cs)
{
    if (NitsShouldFault(cs, NitsAutomatic))
        return NULL;

    return SystemRealloc(originalBuffer, length);
}

#ifdef PAL_Realloc
# undef PAL_Realloc
#endif
#define PAL_Realloc(p, n) realloc_Injected(p, n, NitsHere())

#endif

/* 
   // Required for PAL_Malloca
   //
   // (FUTURE) Defines a stack buffer for PAL_Malloca. On platforms that don't
   // support 'alloca', reserves some space for PAL_Malloca to allocate
   // from before falling back to malloc.
   PAL_MALLOCA_STACK(initialSize) 
 
   // attempts to allocate from the stack via 'alloca' if available,
   // otherwise from malloc. Must be freed by PAL_Freea.
   void* PAL_Malloca(size_t sz)
 
   // free an Alloca pointer. p may be null.
   void PAL_Freea(void *p)
*/
#if defined(__GNUC__) && !defined(PAL_NO_ALLOCA)
#include <alloca.h>
#define PAL_MALLOCA_STACK(initialSize) char _Pal_Malloca_Buffer[(initialSize)>0]
#define PAL_Malloca(sz) (&_Pal_Malloca_Buffer, NitsShouldFault(NitsHere(), NitsAutomatic) ? NULL : alloca((sz)))
#define PAL_Freea(p)
#else 
/* TODO/FIXME: add bookkeeping to support allocating from a fixed sized stack
   buffer, failing over to malloc when it runs out. */
#define PAL_MALLOCA_STACK(initialSize) char _Pal_Malloca_Buffer[(initialSize)>0]
#define PAL_Malloca(sz) (&_Pal_Malloca_Stack, PAL_Malloc((sz)))
#define PAL_Freea(p) PAL_Free((p))
#endif

PAL_END_EXTERNC

#endif /* _pal_memory_h */
