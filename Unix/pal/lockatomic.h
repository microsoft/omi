#ifndef _pal_lockatomic_h
#define _pal_lockatomic_h

#if !defined(_pal_lock_h)
#error "Include pal/lock.h (Atomic version not available)"
#endif

#include "palcommon.h"
#include "thread.h"

PAL_BEGIN_EXTERNC

/*
**==============================================================================
**
** ReadWriteLock -- read/write lock (non-recursive)
**
**==============================================================================
*/

#define READWRITELOCK_INITIALIZER { 0 }

typedef struct _ReadWriteLock
{
    ptrdiff_t state;
} ReadWriteLock;

PAL_INLINE void ReadWriteLock_Init(
    _Out_ ReadWriteLock* self)
{
    self->state = 0;
}


void ReadWriteLock_AcquireRead(
    _Inout_ ReadWriteLock* self);

int ReadWriteLock_TryAcquireRead(
    _Inout_ ReadWriteLock* self);

void ReadWriteLock_AcquireWrite(
    _Inout_ ReadWriteLock* self);

int ReadWriteLock_TryAcquireWrite(
    _Inout_ ReadWriteLock* self);

void ReadWriteLock_ReleaseRead(
    _Inout_ ReadWriteLock* self);

void ReadWriteLock_ReleaseWrite(
    _Inout_ ReadWriteLock* self);

/*
**==============================================================================
**
** Lock -- simple non-recursive lock
**
**==============================================================================
*/

#define LOCK_INITIALIZER { READWRITELOCK_INITIALIZER }

typedef struct _Lock
{
    ReadWriteLock lock;
} Lock;

PAL_INLINE void Lock_Init(
    _Out_ Lock* self)
{
    ReadWriteLock_Init(&self->lock);
}

PAL_INLINE void Lock_Acquire(
    _Inout_ Lock* self)
{
    ReadWriteLock_AcquireWrite(&self->lock);
}

PAL_INLINE int Lock_TryAcquire(
    _Inout_ Lock* self)
{
    return ReadWriteLock_TryAcquireWrite(&self->lock);
}

PAL_INLINE void Lock_Release(
    _Inout_ Lock* self)
{
    ReadWriteLock_ReleaseWrite(&self->lock);
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

/* Temporary disable of cached lock */
#if 0
typedef struct _CachedLock_Pool
{
    ptrdiff_t* latches;         /* Aligned set of cache lines. */
    volatile ptrdiff_t mask;    /* Bits indicate used parts of each line. */
} CachedLock_Pool;

typedef struct _CachedLock
{
    CachedLock_Pool* pool;      /* Could be shared or not. */
    ptrdiff_t* latches;         /* Set of latches, one cache line apart. */
    ReadWriteLock lock;         /* Used when there are exclusive threads. */
    volatile ptrdiff_t master;  /* Counts exclusive threads; masks latches. */
} CachedLock;

#define CACHEDLOCK_FLAG_SHARED (1 << 0)

_Return_type_success_(return == 0) 
int CachedLock_Init_Checked(
    _Out_ CachedLock* self,
    unsigned long flags,
    NitsCallSite cs);

#define CachedLock_Init(self, flags) \
    CachedLock_Init_Checked(self, flags, NitsHere())

void CachedLock_Destroy(
    _Inout_ CachedLock* self);

void CachedLock_AcquireRead(
    _Inout_ CachedLock* self,
    _Out_   void** token);

void CachedLock_AcquireWrite(
    _Inout_ CachedLock* self);

void CachedLock_ReleaseRead(
    _Inout_ CachedLock* self,
    _In_    void* token);

void CachedLock_ReleaseWrite(
    _Inout_ CachedLock* self);
#else

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

#endif
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

#endif /* _pal_lockatomic_h */
