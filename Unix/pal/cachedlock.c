#include <stdlib.h>
#include <malloc.h>
#include "lock.h"
#include "atomic.h"
#include "sleep.h"
#include "cpu.h"
#include "memory.h"

#define CPU_MASK_UNINITIALIZED -1
#define CACHE_LINE_SIZE 128
#define LATCHES_PER_LINE 16
#define POOL_FULL_MASK 0xffff
#define POOL_LINES (s_cpuMask + 1)
#define POOL_SIZE (sizeof(CachedLock_Pool) + CACHE_LINE_SIZE * (POOL_LINES + 1))

#define ALIGN(x, size) (((x) + (size) - 1) & -(size))

/* Number of separate cache lines, minus 1, for easy masking. */
static int s_cpuMask = CPU_MASK_UNINITIALIZED;
static ptrdiff_t s_masterMask = 0;
static Lock s_latchPoolLock = LOCK_INITIALIZER;
static CachedLock_Pool* s_currentPool = NULL;

#ifdef PAL_64BIT
# define MASTER_INCREMENT ((ptrdiff_t)1 << 32)
#else
# define MASTER_INCREMENT ((ptrdiff_t)1 << 16)
#endif

#define MASTER_MASK (MASTER_INCREMENT - 1)

static CachedLock_Pool* Pool_New()
{
    CachedLock_Pool* pool;
    ptrdiff_t buffer;

    /* The pool and all the latch lines are one block. */
    pool = (CachedLock_Pool*)PAL_Malloc(POOL_SIZE);
    if (pool == NULL)
        return NULL;

    /* buffer contains an extra cache line for manual alignment. */
    buffer = (ptrdiff_t)(pool + 1);
    buffer = ALIGN(buffer, CACHE_LINE_SIZE);

    pool->latches = (ptrdiff_t*)buffer;
    pool->mask = 0;

    return pool;
}

static void Pool_Delete(
    _In_ CachedLock_Pool* self
)
{
    PAL_Free(self);
}

static void ATEXIT_API ShutdownCachePool(void)
{
    if (s_currentPool)
        Pool_Delete(s_currentPool);
    s_currentPool = NULL;
}

static void InitializeCachePool()
{
    int cpus = CPU_GetCount();

    /* Round up to the next power of two. */
    if (cpus <= 1)
        cpus = 1;
    else if (cpus <= 2)
        cpus = 2;
    else if (cpus <= 4)
        cpus = 4;
    else if (cpus <= 8)
        cpus = 8;
#ifdef PAL_64BIT
    else if (cpus > 16)
        cpus = 32;
#endif
    else
        cpus = 16;

    /* Everyone needs to mask off higher bits in case CPU_GetCurrent ever
     * returns a number higher than it did now, or in case there are more than
     * 32 CPUs. */
    s_cpuMask = cpus - 1;
    s_masterMask = ((ptrdiff_t)1 << cpus) - 1;
    PAL_Atexit(ShutdownCachePool);
}

_Return_type_success_(return == 0) int CachedLock_Init_Checked(
    _Out_ CachedLock* self,
    unsigned long flags,
    NitsCallSite cs
)
{
    CachedLock_Pool* pool;
    int index;
    ReadWriteLock temp = READWRITELOCK_INITIALIZER;

    /* One-time initialization. Doesn't matter if called several times. */
    if (s_cpuMask == CPU_MASK_UNINITIALIZED)
        InitializeCachePool();

    if (flags & CACHEDLOCK_FLAG_SHARED)
    {
        Lock_Acquire(&s_latchPoolLock);

        if (NitsShouldFault(cs, NitsAutomatic))
            return -1;

        if (s_currentPool == NULL ||
            s_currentPool->mask == POOL_FULL_MASK)
        {
            /* The current pool is full. */
            s_currentPool = Pool_New();
            if (s_currentPool == NULL)
                return -1;
        }

        /* Search the pool for a zero bit. */
        pool = s_currentPool;
        for (index = 0; index < POOL_LINES; index++)
            if ((pool->mask & ((ptrdiff_t)1 << index)) == 0)
                break;

        /* Take ownership of this index. */
        pool->mask |= ((ptrdiff_t)1 << index);
        Lock_Release(&s_latchPoolLock);
    }
    else
    {
        pool = Pool_New();
        if (pool == NULL)
            return -1;
        pool->mask = 1;
        index = 0;
    }

    self->pool = pool;
    self->latches = pool->latches + index;
    self->lock = temp;
    self->master = 0;

    return 0;
}

void CachedLock_Destroy(
    _Inout_ CachedLock* self
)
{
    CachedLock_Pool* pool = self->pool;
    ptrdiff_t index = self->latches - self->pool->latches;

    Lock_Acquire(&s_latchPoolLock);

    /* Release ownership of our bit. */
    pool->mask &= ~((ptrdiff_t)1 << index);

    /* Determine if this pool has been orphaned. */
    if (pool->mask == 0 && pool != s_currentPool)
        Pool_Delete(pool);

    Lock_Release(&s_latchPoolLock);
}

static void ClearCPU(
    _Inout_ CachedLock* self,
    _Inout_ ptrdiff_t* latch)
{
    ptrdiff_t index = (latch - self->latches) / LATCHES_PER_LINE;

    /* There are exclusive threads acquiring.
     * Mark this latch as empty in the central shared mask. */
    ptrdiff_t result = Atomic_And(&self->master, ~((ptrdiff_t)1 << index));

    if ((result & MASTER_MASK) == 0)
        CondLock_Broadcast((ptrdiff_t)self);
}

static int TryAcquireRead(
    _Inout_ CachedLock* self,
    _Out_   void** token
)
{
    volatile ptrdiff_t* master = &self->master;
    ptrdiff_t* latch;
    int cpu;

    cpu = CPU_GetCurrent() & s_cpuMask;
    latch = self->latches + LATCHES_PER_LINE * cpu;

    if (*master != 0)
    {
        /* Exclusive threads are already here. Short-circuit. */
        *token = NULL;
        return 0;
    }

    Atomic_Inc(latch);

    if (*master != 0)
    {
        /* Exclusive threads might have missed our increment. */
        if (Atomic_Dec(latch) == 0)
            ClearCPU(self, latch);
        *token = NULL;
        return 0;
    }
    
    /* Exclusive threads cannot miss that we are here. */
    *token = latch;
    return 1;
}

void CachedLock_AcquireRead(
    _Inout_ CachedLock* self,
    _Out_   void** token
)
{
    if (TryAcquireRead(self, token) != 0)
        return;

    ReadWriteLock_AcquireRead(&self->lock);
}

void CachedLock_AcquireWrite(
    _Inout_ CachedLock* self
)
{
    ptrdiff_t oldState, state, swapState;
    ptrdiff_t oldMask, zeroMask, index;
    volatile ptrdiff_t* master = &self->master;

    /* The order of steps here is important.
     *  1) Stop shared readers from racing through the latches.
     *  2) Scan the latches to find inactive ones.
     *  3) Get exclusive access to the central lock.
     *  4) Wait for existing shared readers in the latches to leave.
     *
     * Doing (3) before (1) lets readers race through the latches if the
     *   central lock is still held by a reader from previous contention.
     * Doing (3) before (2) leads to deadlock if there are no active latches
     *   and another writer gets the central lock first.
     * Doing (3) after (4) lets readers race through the central lock. */

    for (;;)
    {
        oldState = PAL_PREFETCH(master);

        /* The first thread atomically sets s_masterMask. */
        if (oldState == 0)
            state = s_masterMask + MASTER_INCREMENT;
        else
            state = oldState + MASTER_INCREMENT;

        swapState = Atomic_CompareAndSwap(master, oldState, state);
        if (swapState == oldState)
            break;
    }

    /* Reader threads will now observe that master != 0. */

    if (oldState == 0)
    {
        /* This is the thread that set s_masterMask. */
        zeroMask = 0;
        for (index = 0; index < POOL_LINES; index++)
        {
            /* Determine if all shared threads are gone. */
            if (self->latches[LATCHES_PER_LINE * index] == 0)
                zeroMask |= ((ptrdiff_t)1 << index);
        }

        /* Determine if there are any CPUs with shared threads remaining.
         * Other exclusive threads could be waiting. */
        if ((Atomic_And(master, ~zeroMask) & MASTER_MASK) == 0)
            CondLock_Broadcast((ptrdiff_t)self);
    }

    ReadWriteLock_AcquireWrite(&self->lock);

    for (;;)
    {
        /* Wait for all the latches to empty. */
        oldMask = *master;
        if ((oldMask & MASTER_MASK) == 0)
            return;

        CondLock_Wait((ptrdiff_t)self, master, oldMask, CONDLOCK_DEFAULT_SPINCOUNT);
    }
}

void CachedLock_ReleaseRead(
    _Inout_ CachedLock* self,
    _In_    void* token
)
{
    ptrdiff_t* latch = (ptrdiff_t*)token;
    ptrdiff_t state;

    if (latch == NULL)
    {
        /* This thread acquired the central lock, not a latch. */
        ReadWriteLock_ReleaseRead(&self->lock);
        return;
    }

    /* Decrement the same latch that got incremented before. */
    state = Atomic_Dec(latch);
    if (state == 0 && self->master != 0)
        ClearCPU(self, latch);
}

void CachedLock_ReleaseWrite(
    _Inout_ CachedLock* self
)
{
    ReadWriteLock_ReleaseWrite(&self->lock);

    /* Revert the increment that happened during Acquire. */
    Atomic_Add(&self->master, -MASTER_INCREMENT);
}
