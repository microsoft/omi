#include <stdlib.h>
#include "lock.h"
#include "cpu.h"
#include "atomic.h"
#include "sem.h"
#include "sleep.h"

#define CACHE_LINE_SIZE 128

#if defined(CONFIG_FAVORSIZE)
#define WAIT_BUCKETS 16
#else
#define WAIT_BUCKETS 1024
#endif /* defined(CONFIG_FAVORSIZE) */

#define WAIT_BUCKET_MASK (WAIT_BUCKETS - 1)
#define WAIT_RESETTING 1
#define WAIT_BROADCASTING 0x80000000
#define WAIT_COUNT 0x7fffffff
#define SEM_POOL_SIZE 64

#define KEY_EMPTY     0
#define KEY_COLLISION -1

#define SPIN_SIGN 0x80
#define SPIN_MAX  0xff

#define SLEEP_MIN 5 
#define SLEEP_MAX 1500

typedef struct _WaitRefs
{
    volatile ptrdiff_t sem;  /* Assumes Sem is isomorphic to ptrdiff_t! */
    volatile ptrdiff_t refs; /* Counts threads that call Sem_Wait. */
    volatile ptrdiff_t key;  /* Detects hash collisions. */
} WaitRefs;

typedef struct _WaitBucket
{
    WaitRefs state[2];
    volatile ptrdiff_t signals;
    unsigned char spinState;

    char padding[CACHE_LINE_SIZE
        - 2*sizeof(WaitRefs)
        - 2*sizeof(ptrdiff_t)];
} WaitBucket;

typedef enum _WaitPoolState
{
    Unloaded,
    Loaded,
} WaitPoolState;

static WaitBucket s_waitPool[WAIT_BUCKETS] = {{{{0}}}};
static size_t s_highSpinCount = 32768;
static size_t s_lowSpinCount = 1024;
static volatile ptrdiff_t s_waitPoolState = Unloaded;

static ptrdiff_t s_semPool[SEM_POOL_SIZE] = {0};
static volatile ptrdiff_t s_semPoolCount = 0;

static void ATEXIT_API ShutdownWaitPool(void)
{
    /* Possible this function could be run multiple times. */
    ptrdiff_t count = Atomic_Swap(&s_semPoolCount, 0);
    ptrdiff_t i;

    for (i = 0; i < count; i++)
        Sem_Destroy((Sem *)&s_semPool[i]);
}

static void InitializeWaitPool()
{
    if (CPU_GetCount() == 1)
    {
        /* Spinning is useless on single-CPU machines. */
        s_highSpinCount = 0;
        s_lowSpinCount = 0;
    }

    /* Possible multiple threads could get here, but that's okay. */
    PAL_Atexit(ShutdownWaitPool);

    /* Atomic swap used as memory barrier. */
    Atomic_Swap(&s_waitPoolState, Loaded);
}

static ptrdiff_t GetPooledSemaphore()
{
    ptrdiff_t oldCount, newCount, swapCount;
    ptrdiff_t temp;

    for(;;)
    {
        oldCount = PAL_PREFETCH(&s_semPoolCount);

        if (oldCount == 0)
        {
            /* The pool is empty. Create the semaphore the normal way. */
            if (Sem_Init((Sem*)&temp, SEM_USER_ACCESS_DEFAULT, 0) != 0)
                return 0;
            return temp;
        }

        newCount = oldCount - 1;
        temp = PAL_PREFETCH(s_semPool + newCount);

        /* Check to see if the slot is NULL. If so, spin. */
        if (temp == 0)
            continue;

        /* Try to take ownership of the semaphore. */
        temp = Atomic_Swap(s_semPool + newCount, 0);
        if (temp == 0)
            continue;

        /* Got ownership. Try to decrement the count. */
        swapCount = Atomic_CompareAndSwap(&s_semPoolCount, oldCount, newCount);
        if (swapCount != oldCount)
        {
            /* The count changed. Put the semaphore back and retry. */
            s_semPool[newCount] = temp;
            continue;
        }

        /* Successfully decremented the count. */
        return temp;
    }
}

static void RecyclePooledSemaphore(
    _In_ ptrdiff_t sem
)
{
    ptrdiff_t oldCount, newCount, swapCount;

    for (;;)
    {
        oldCount = PAL_PREFETCH(&s_semPoolCount);

        if (oldCount == SEM_POOL_SIZE)
        {
            /* The pool is full. Destroy the semaphore the normal way. */
            Sem_Destroy((Sem*)&sem);
            return;
        }

        newCount = oldCount + 1;

        /* Try to allocate space for the semaphore. */
        swapCount = Atomic_CompareAndSwap(&s_semPoolCount, oldCount, newCount);
        if (swapCount != oldCount)
            continue;

        /* We own this slot until we make it non-NULL. */
        s_semPool[oldCount] = sem;
        return;
    }
}

static void LeaveWaitPool(
    _Inout_ WaitRefs* state
)
{
    ptrdiff_t sem;
    ptrdiff_t newRefs;

    newRefs = Atomic_Dec(&state->refs) & WAIT_COUNT;
    if (newRefs == WAIT_RESETTING)
    {
        /* The WAIT_RESETTING state is used to clear sem/key safely.
         * No one can change states except us. */
        sem = state->sem;

        state->sem = 0;
        state->key = KEY_EMPTY;

        /* Atomic swap used as memory barrier. */
        Atomic_Swap(&state->refs, 0);

        if (sem != 0)
            RecyclePooledSemaphore(sem);
    }
}

static int EnterWaitPool(
    _Inout_ WaitRefs* state,
            int broadcast
)
{
    ptrdiff_t sem, swapSem;
    ptrdiff_t oldRefs, newRefs, swapRefs;

    /* Check for one-time initialization work. */
    if (s_waitPoolState != Loaded)
        InitializeWaitPool();

    for (;;)
    {
        oldRefs = PAL_PREFETCH(&state->refs);

        if (oldRefs & WAIT_BROADCASTING)
            return 1; /* Someone is broadcasting. Caller should yield. */
        else if (oldRefs == 0)
            newRefs = 2; /* Extra reference for WAIT_RESETTING. */
        else if (oldRefs > 1)
            newRefs = oldRefs + 1;
        else
            return 1; /* oldRefs == WAIT_RESETTING. Caller should yield. */

        if (broadcast)
            newRefs |= WAIT_BROADCASTING;

        swapRefs = Atomic_CompareAndSwap(&state->refs, oldRefs, newRefs);
        if (swapRefs == oldRefs)
            break;
    }

    if (state->sem == 0)
    {
        sem = GetPooledSemaphore();
        if (sem == 0)
        {
            /* This is not fatal. The caller should yield and try again. */            
            NitsIgnoringError();
            LeaveWaitPool(state);
            return 1;
        }

        /* Try to install the semaphore. Somebody might beat us to it. */
        swapSem = Atomic_CompareAndSwap(&state->sem, 0, sem);
        if (swapSem != 0)
            RecyclePooledSemaphore(sem);
    }

    /* The WaitRefs structure now has a valid semaphore and refs >= 2. */
    return 0;
}

#define WaitBucketHash(x)  ((x) ^ ((x) >> 3) ^ ((x) >> 12) ^ ((x) >> 22))
#define WaitBucketForKey(x) (s_waitPool + (WaitBucketHash(x) & WAIT_BUCKET_MASK))

int CondLock_Wait(
                        ptrdiff_t key,
    _In_ volatile const ptrdiff_t* destination,
                        ptrdiff_t comparand,
                        size_t spinCount)
{
    WaitBucket* bucket;
    WaitRefs* state;
    size_t spins;
    ptrdiff_t startValue;
    ptrdiff_t oldKey, swapKey;
    int sleep = SLEEP_MIN;

    bucket = WaitBucketForKey(key);
    startValue = bucket->signals;

    /* Read bucket->signals before reading *destination. */
    NonX86MemoryBarrier();

    /* Determine whether we already missed a state change. */
    if (*destination != comparand)
        return 1;

    /* Select a spin count. */
    if (spinCount == CONDLOCK_DEFAULT_SPINCOUNT)
        spinCount = (bucket->spinState >= SPIN_SIGN) ?
            s_lowSpinCount :
            s_highSpinCount;
    else if (spinCount == CONDLOCK_HIGH_SPINCOUNT)
        spinCount = s_highSpinCount;
    else if (spinCount == CONDLOCK_LOW_SPINCOUNT)
        spinCount = s_lowSpinCount;

    for (spins = 0; spins < spinCount; spins++)
    {
        if (bucket->signals != startValue)
        {
            /* Signal/Broadcast was called during spinning. */
            /* Deliberately imprecise. */
            bucket->spinState = (bucket->spinState > 2) ?
                (bucket->spinState - 2) : 0;
            return 1;
        }
    }

    /* Select one of the two WaitRefs structures. */
    state = bucket->state + (startValue & 1);

    for (;;)
    {
        if (bucket->signals != startValue)
            break;

        /* This prevents the semaphore from becoming invalid. */
        /* All failure paths yield, then try again. */
        if (EnterWaitPool(state, 0) != 0)
        {
            sleep += sleep;
            if (sleep > SLEEP_MAX)
                sleep = SLEEP_MAX;

            Sleep_Milliseconds(sleep);
            continue;
        }

        for (;;)
        {
            /* KEY_EMPTY is a special value meaning no key is set. */
            if (key == KEY_EMPTY)
                key++;

            /* Determine if the stored key is the same. */
            oldKey = state->key;
            if (key == oldKey)
                break;

            /* If the stored key is non-empty, we have a collision. */
            if (oldKey != KEY_EMPTY)
                key = KEY_COLLISION;

            swapKey = Atomic_CompareAndSwap(&state->key, oldKey, key);
            if (swapKey == oldKey)
                break;
        }

        if (bucket->signals == startValue)
            Sem_Wait((Sem*)&state->sem);

        LeaveWaitPool(state);
    }
    
    /* Didn't succeed with spinning; woke up later. */
    /* Deliberately imprecise. */
    bucket->spinState = (bucket->spinState < SPIN_MAX) ?
        (bucket->spinState + 1) :
        bucket->spinState;
    return 0;
}

void CondLock_Broadcast(
    ptrdiff_t key)
{
    WaitBucket* bucket;
    WaitRefs* state;
    ptrdiff_t startValue;
    ptrdiff_t refs;
    
    bucket = WaitBucketForKey(key);

    /* Bump the number of signals. Spinning Wait calls will complete. */
    startValue = Atomic_Inc(&bucket->signals) - 1;

    /* Choose the same WaitRefs that the Wait calls did. */
    state = bucket->state + (startValue & 1);

    /* Short-circuit if there is no one to wake up. */
    if (state->refs == 0)
        return;

    /* This prevents the semaphore from becoming invalid. */
    if (EnterWaitPool(state, 1) != 0)
        return;

    /* Signal everyone except us and the ref for WAIT_RESETTING. */
    /* Spurious wakeups are possible, but this is transient and rare. */
    refs = (state->refs & WAIT_COUNT) - 2;
    Sem_Post((Sem*)&state->sem, (unsigned int)refs);

    LeaveWaitPool(state);
}

void CondLock_BroadcastSpinners(
    ptrdiff_t key)
{
    WaitBucket* bucket;
    
    bucket = WaitBucketForKey(key);

    /* Bump signals without changing which semaphore gets posted next. */
    Atomic_Add(&bucket->signals, 2);
}

void CondLock_Signal(
    ptrdiff_t key)
{
    WaitBucket* bucket;
    WaitRefs* state;
    ptrdiff_t startValue;
    ptrdiff_t refs;

    bucket = WaitBucketForKey(key);

    /* Bump the number of signals. Spinning Wait calls will complete. */
    startValue = Atomic_Inc(&bucket->signals) - 1;

    /* Choose the same WaitRefs that the Wait calls did. */
    state = bucket->state + (startValue & 1);

    /* Short-circuit if there is no one to wake up. */
    if (state->refs == 0)
        return;

    /* This prevents the semaphore from becoming invalid. */
    if (EnterWaitPool(state, 0) != 0)
        return;

    Sem_Post((Sem*)&state->sem, 1);

    if (state->key == KEY_COLLISION &&
        EnterWaitPool(state, 1) == 0)
    {
        /* There is no way to prevent waking the wrong thread.
         * Fall back to waking everyone. */

        /* Cannot factor in the Post we already made, because new threads were
         * not notified of the broadcast flag until now. */
        refs = (state->refs & WAIT_COUNT) - 2;
        Sem_Post((Sem*)&state->sem, (unsigned int)refs);

        LeaveWaitPool(state);
    }

    LeaveWaitPool(state);
}
