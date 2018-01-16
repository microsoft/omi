/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _pal_atomic_h
#define _pal_atomic_h

#include <pal/palcommon.h>

#if !defined(CONFIG_HAVE_ATOMIC_INTRINSICS)
#if defined(PAL_HAVE_PTHREADS)
# include <pthread.h>
#endif
#if defined(PAL_HAVE_POSIX)
# include <sys/types.h>
# include <unistd.h>
#endif
#endif

PAL_BEGIN_EXTERNC

#if !defined(CONFIG_HAVE_ATOMIC_INTRINSICS)

#define PAL_ATOMIC_LOCKS_SIZE 64

extern PAL_Boolean __palInitialized;
extern pthread_mutex_t __atomicInitLock;
extern pthread_mutex_t __atomicLocks[PAL_ATOMIC_LOCKS_SIZE];

PAL_INLINE void __AcquireLock(pthread_mutex_t *lock);
PAL_INLINE void __ReleaseLock(pthread_mutex_t *lock);

PAL_INLINE void __ForkHandlerHelper(PAL_Boolean acquire)
{
    int i = 0;
    for(i = 0; i < PAL_ATOMIC_LOCKS_SIZE; i++)
    {
        if(acquire)
            __AcquireLock(&(__atomicLocks[i]));
        else
            __ReleaseLock(&(__atomicLocks[i]));
    }

    if(acquire)
    {
        pthread_mutex_lock(&__atomicInitLock);
    }
    else
    {
        pthread_mutex_unlock(&__atomicInitLock);
    }
}

PAL_INLINE void __PrepareForkHandler(void)
{
    __ForkHandlerHelper(PAL_TRUE);
}

PAL_INLINE void __ParentForkHandler(void)
{
    __ForkHandlerHelper(PAL_FALSE);
}

PAL_INLINE void __ChildForkHandler(void)
{
    __ForkHandlerHelper(PAL_FALSE);
}

PAL_INLINE void __AcquireLock(pthread_mutex_t *lock)
{
    if(__palInitialized == PAL_FALSE)
    {
        pthread_mutex_lock(&__atomicInitLock);

        if(__palInitialized == PAL_FALSE)
        {
            pthread_atfork(__PrepareForkHandler, __ParentForkHandler, __ChildForkHandler);
            __palInitialized = PAL_TRUE;
        }

        pthread_mutex_unlock(&__atomicInitLock);
    }

    pthread_mutex_lock(lock);
}

PAL_INLINE void __ReleaseLock(pthread_mutex_t *lock)
{
    pthread_mutex_unlock(lock);
}

#define __AtomicLockToUse(x) (&(__atomicLocks[(((unsigned)(((ptrdiff_t)(x)) >> 2)) % PAL_ATOMIC_LOCKS_SIZE)]))

PAL_INLINE void __AcquireAtomicLock(_In_ volatile ptrdiff_t* x)
{        
    __AcquireLock(__AtomicLockToUse(x));
}

PAL_INLINE void __ReleaseAtomicLock(_In_ volatile ptrdiff_t* x)
{
    __ReleaseLock(__AtomicLockToUse(x));
}

#endif

PAL_INLINE ptrdiff_t Atomic_Read(
    _Inout_ volatile ptrdiff_t* x)
{
#if !defined(CONFIG_HAVE_ATOMIC_INTRINSICS)
    ptrdiff_t retVal = 0;
    __AcquireAtomicLock(x);
    retVal = *x;
    __ReleaseAtomicLock(x);
    return retVal;
#else
    return __sync_add_and_fetch(x, 0);
#endif
}


PAL_INLINE ptrdiff_t Atomic_Inc(
    _Inout_ volatile ptrdiff_t* x)
{
#if !defined(CONFIG_HAVE_ATOMIC_INTRINSICS)
    ptrdiff_t retVal = 0;
    __AcquireAtomicLock(x);
    retVal = *x; 
    retVal++; 
    *x = retVal;
    __ReleaseAtomicLock(x);
    return retVal;
#else
    return __sync_add_and_fetch(x, 1);
#endif
}

PAL_INLINE ptrdiff_t Atomic_Dec(
    _Inout_ volatile ptrdiff_t* x)
{
#if !defined(CONFIG_HAVE_ATOMIC_INTRINSICS)
    ptrdiff_t retVal = 0;
    __AcquireAtomicLock(x);
    retVal = *x; 
    retVal--; 
    *x = retVal;
    __ReleaseAtomicLock(x);
    return retVal;
#else
    return __sync_sub_and_fetch(x, 1);
#endif
}

PAL_INLINE ptrdiff_t Atomic_CompareAndSwap(
    _Inout_ volatile ptrdiff_t* dest,
    _In_ ptrdiff_t comparand,
    _In_ ptrdiff_t newValue)
{
#if !defined(CONFIG_HAVE_ATOMIC_INTRINSICS)
    ptrdiff_t retVal = 0;
    __AcquireAtomicLock(dest);
    retVal = *dest;
    if(retVal == comparand)
    {
        *dest = newValue;
    }        
    __ReleaseAtomicLock(dest);
    return retVal;
#else
    return __sync_val_compare_and_swap(dest, comparand, newValue);
#endif
}

PAL_INLINE ptrdiff_t Atomic_Swap(
    _Inout_ volatile ptrdiff_t* dest,
    _In_ ptrdiff_t newValue)
{
#if !defined(CONFIG_HAVE_ATOMIC_INTRINSICS)
    ptrdiff_t retVal = 0;
    __AcquireAtomicLock(dest);
    retVal = *dest;    
    *dest = newValue;    
    __ReleaseAtomicLock(dest);
    return retVal;
#else
    return __sync_lock_test_and_set(dest, newValue);
#endif
}

PAL_INLINE ptrdiff_t Atomic_Add(
    _Inout_ volatile ptrdiff_t* x,
            ptrdiff_t value)
{
#if !defined(CONFIG_HAVE_ATOMIC_INTRINSICS)
    ptrdiff_t retVal = 0;
    __AcquireAtomicLock(x);
    retVal = *x; 
    retVal = retVal + value; 
    *x = retVal;    
    __ReleaseAtomicLock(x);
    return retVal;
#else
    return __sync_add_and_fetch(x, value);
#endif
}

PAL_INLINE ptrdiff_t Atomic_And(
    _Inout_ volatile ptrdiff_t* x,
                     ptrdiff_t value)
{
#if !defined(CONFIG_HAVE_ATOMIC_INTRINSICS)
    ptrdiff_t retVal = 0;
    __AcquireAtomicLock(x);
    retVal = *x; 
    retVal = retVal & value; 
    *x = retVal;           
    __ReleaseAtomicLock(x);
    return retVal;
#else
    return __sync_and_and_fetch(x, value);
#endif
}

/*
**==============================================================================
**
** NonX86MemoryBarrier macro
**
**==============================================================================
*/
# if defined(__i386__) || defined(__amd64__)
#  define NonX86MemoryBarrier() ((void)0)
# elif defined(CONFIG_HAVE_SYNC_SYNCHRONIZE)
#  define NonX86MemoryBarrier() __sync_synchronize()
# else
extern volatile ptrdiff_t __memoryBarrierVar;
#  define NonX86MemoryBarrier() ((void)Atomic_Swap(&__memoryBarrierVar, 0))
# endif

PAL_END_EXTERNC

#endif /* _pal_atomic_h */
