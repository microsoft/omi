/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _pal_lockposix_h
#define _pal_lockposix_h

#if !defined(_pal_lock_h)
#error "Include pal/lock.h (Atomic version available)"
#endif

#include "palcommon.h"
#include "thread.h"
#include <pthread.h>

PAL_BEGIN_EXTERNC

/*
**==============================================================================
**
** ReadWriteLock -- read/write lock (non-recursive)
**
**==============================================================================
*/

#define READWRITELOCK_INITIALIZER PTHREAD_RWLOCK_INITIALIZER

typedef struct _ReadWriteLock
{
    pthread_rwlock_t lock;
} 
ReadWriteLock;

PAL_INLINE void ReadWriteLock_Init(_Out_ ReadWriteLock* self)
{
    pthread_rwlock_t tmp = PTHREAD_RWLOCK_INITIALIZER;
    memcpy(&self->lock, &tmp, sizeof(tmp));
}

PAL_INLINE void ReadWriteLock_AcquireRead(
    _Inout_ ReadWriteLock* self)
{
    pthread_rwlock_rdlock(&self->lock);
}

PAL_INLINE int ReadWriteLock_TryAcquireRead(
    _Inout_ ReadWriteLock* self)
{
    return pthread_rwlock_tryrdlock(&self->lock) == 0 ? 1 : 0;
}

PAL_INLINE void ReadWriteLock_AcquireWrite(
    _Inout_ ReadWriteLock* self)
{
    pthread_rwlock_wrlock(&self->lock);
}

PAL_INLINE int ReadWriteLock_TryAcquireWrite(
    _Inout_ ReadWriteLock* self)
{
    return pthread_rwlock_trywrlock(&self->lock) == 0 ? 1 : 0;
}

PAL_INLINE void ReadWriteLock_ReleaseRead(
    _Inout_ ReadWriteLock* self)
{
    pthread_rwlock_unlock(&self->lock);
}

PAL_INLINE void ReadWriteLock_ReleaseWrite(
    _Inout_ ReadWriteLock* self)
{
    pthread_rwlock_unlock(&self->lock);
}

/*
**==============================================================================
**
** Lock -- simple non-recursive lock
**
**==============================================================================
*/

#define LOCK_INITIALIZER { PTHREAD_MUTEX_INITIALIZER }

typedef struct _Lock
{
    pthread_mutex_t lock;
} Lock;

PAL_INLINE void Lock_Init(
    _Out_ Lock* self)
{
    pthread_mutex_t tmp = PTHREAD_MUTEX_INITIALIZER;
    memcpy(&self->lock, &tmp, sizeof(tmp));
}

PAL_INLINE void Lock_Acquire(
    _Inout_ Lock* self)
{
    pthread_mutex_lock(&self->lock);
}

PAL_INLINE int Lock_TryAcquire(
    _Inout_ Lock* self)
{
    return pthread_mutex_trylock(&self->lock) == 0 ? 1 : 0;
}

PAL_INLINE void Lock_Release(
    _Inout_ Lock* self)
{
    pthread_mutex_unlock(&self->lock);
}

/*
**==============================================================================
**
** RecursiveLock -- recursive lock
**
**==============================================================================
*/

#define RECURSIVELOCK_INITIALIZER {LOCK_INITIALIZER, 0}

typedef struct _RecursiveLock
{
    Lock lock;
    ptrdiff_t count;
    ThreadID owner;
} RecursiveLock;

PAL_INLINE void RecursiveLock_Init(
    _Out_ RecursiveLock* self)
{
    Lock_Init(&self->lock);
    self->count = 0;
    self->owner = Thread_ID_Null();
}

void RecursiveLock_Acquire(
    _Inout_ RecursiveLock* self);

PAL_INLINE void RecursiveLock_Release(
    _Inout_ RecursiveLock* self)
{
    if (--self->count > 0)
        return;

    self->owner = Thread_ID_Null();
    Lock_Release(&self->lock);
}

/*
**==============================================================================
**
** CachedLock -- cached lock
**
**==============================================================================
*/

typedef ReadWriteLock CachedLock;

#define CACHEDLOCK_FLAG_SHARED (1 << 0)

_Return_type_success_(return == 0) 
PAL_INLINE int CachedLock_Init(
    _Out_ CachedLock* self,
    unsigned long flags)
{ 
    ReadWriteLock_Init(self); 
    return 0; 
}

#define CachedLock_Destroy(self) 

#define CachedLock_AcquireRead(self, token) ReadWriteLock_AcquireRead(self)

#define CachedLock_AcquireWrite(self) ReadWriteLock_AcquireWrite(self)

#define CachedLock_ReleaseRead(self, token) ReadWriteLock_ReleaseRead(self)

#define CachedLock_ReleaseWrite(self) ReadWriteLock_ReleaseWrite(self)

/*
**==============================================================================
**
** CondLock -- condition variable
**
**==============================================================================
*/

#define CONDLOCK_DEFAULT_SPINCOUNT ((size_t)-1)
#define CONDLOCK_HIGH_SPINCOUNT    ((size_t)-2)
#define CONDLOCK_LOW_SPINCOUNT     ((size_t)-3)

int CondLock_Wait(
    ptrdiff_t key,
    _In_ volatile const ptrdiff_t* destination,
    ptrdiff_t comparand,
    size_t spinCount);

void CondLock_Broadcast(
    ptrdiff_t key);

void CondLock_BroadcastSpinners(
    ptrdiff_t key);

void CondLock_Signal(
    ptrdiff_t key);

PAL_END_EXTERNC

#endif /* _pal_lockposix_h */
