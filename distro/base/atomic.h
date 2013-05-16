/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

#ifndef _base_atomic_h
#define _base_atomic_h

#include <common.h>

BEGIN_EXTERNC

/*
**==============================================================================
**
** Windows Atomic Type
**
**==============================================================================
*/

#if !defined(HAVE_ATOMIC) && defined(_WIN32)
# define HAVE_ATOMIC
END_EXTERNC
# include <winbase.h>
BEGIN_EXTERNC

typedef long AtomicInt;

MI_INLINE void AtomicInc(AtomicInt* x)
{
    InterlockedIncrement(x);
}

MI_INLINE unsigned char AtomicDec(AtomicInt* x)
{
    return InterlockedDecrement(x) == 0;
}

#endif

/*
**==============================================================================
**
** Linux Atomic Type
**
**==============================================================================
*/

#if !defined(HAVE_ATOMIC) && defined(linux)
# define HAVE_ATOMIC

typedef volatile long AtomicInt;

MI_INLINE void AtomicInc(AtomicInt* v)
{
    __asm__ __volatile__(
        "lock ; " "incl %0"
        :"=m" (*v)
        :"m" (*v));
}

MI_INLINE unsigned char AtomicDec(AtomicInt* v)
{
    unsigned char c;

    __asm__ __volatile__(
        "lock ; " "decl %0; sete %1"
        :"=m" (*v), "=qm" (c)
        :"m" (*v) : "memory");
    return c != 0;
}

#endif

/*
**==============================================================================
**
** SunOs >= 5.10
**
**==============================================================================
*/

#if !defined(HAVE_ATOMIC) && defined(sun) && (defined(__SunOS_5_10) || defined(__SunOS_5_11))

# define HAVE_ATOMIC
END_EXTERNC
#   include <inttypes.h>
#   include <atomic.h>
BEGIN_EXTERNC

typedef volatile unsigned long long AtomicInt;

MI_INLINE void AtomicInc(AtomicInt* x)
{
    atomic_inc_64(x);
}

MI_INLINE unsigned char AtomicDec(AtomicInt* x)
{
    return atomic_dec_64_nv(x) == 0;
}

#endif

/*
**==============================================================================
**
** Sun Sparc < 5.10
**
**==============================================================================
*/

#if !defined(HAVE_ATOMIC) && defined(sun) && defined(sparc)
# define HAVE_ATOMIC

typedef long AtomicInt;

EXTERNC AtomicInt AtomicDecrement(AtomicInt* pValue);

EXTERNC AtomicInt AtomicIncrement(AtomicInt* pValue);


MI_INLINE void AtomicInc(AtomicInt* x)
{
    AtomicIncrement(x);
}

MI_INLINE unsigned char AtomicDec(AtomicInt* x)
{
    return AtomicDecrement(x) == 0;
}

#endif

/*
**==============================================================================
**
** AIX
**
**==============================================================================
*/

#if defined(aix) && !defined(HAVE_ATOMIC)
# define HAVE_ATOMIC
END_EXTERNC
# include <sys/atomic_op.h>
BEGIN_EXTERNC

typedef int AtomicInt;

MI_INLINE void AtomicInc(AtomicInt* x)
{
    fetch_and_add(x, 1);
}

MI_INLINE unsigned char AtomicDec(AtomicInt* x)
{
    return fetch_and_add(x, -1) - 1 == 0;
}

#endif

/*
**==============================================================================
**
** Generic
**
**==============================================================================
*/

#if !defined(HAVE_ATOMIC)

typedef int AtomicInt;

void AtomicInc(AtomicInt* x);

unsigned char AtomicDec(AtomicInt* x);

#define MI_DEFAULT_ATOMIC_REQUIRED

#endif

END_EXTERNC

#endif /* _base_atomic_h */
