/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "lock.h"
#include "atomic.h"
#include "thread.h"
#include "cpu.h"

#if defined(PAL_64BIT)
# define FIELD_SIZE 13
# define FIELD_MAX 0x1fff
# define FIELD_SIGN 0x1000
# define SPIN_SIZE 8
# define SPIN_MAX 0xff
# define SPIN_SIGN 0x80
#elif defined(PAL_32BIT)
# define FIELD_SIZE 6
# define FIELD_MAX 0x3f
# define FIELD_SIGN 0x20
# define SPIN_SIZE 4
# define SPIN_MAX 0xf
# define SPIN_SIGN 0x8
#else
# error "unknown pointer size"
#endif /* 32/64 bit */

#define OWN_MAXSHARED (FIELD_MAX - 1)
#define OWN_EXCLUSIVE FIELD_MAX
#define CurrentTick() CPU_GetTimeStamp()

typedef struct _LockFields
{
    size_t owners : FIELD_SIZE;
    size_t unfair : 4;
    size_t spin   : SPIN_SIZE;
    size_t entry  : FIELD_SIZE;
    size_t writer : FIELD_SIZE;
    size_t exit   : FIELD_SIZE;
} LockFields;

#define LockState(p)  ((ptrdiff_t*)p)
#define ReadLockState(p) PAL_PREFETCH((volatile ptrdiff_t*)(p))
#define LockOwners(x) (((LockFields*)&x)->owners)
#define LockUnfair(x) (((LockFields*)&x)->unfair)
#define LockSpin(x)   (((LockFields*)&x)->spin)
#define LockEntry(x)  (((LockFields*)&x)->entry)
#define LockWriter(x) (((LockFields*)&x)->writer)
#define LockExit(x)   (((LockFields*)&x)->exit)

static int TryAcquireRead(
    _Inout_ ReadWriteLock* self
)
{
    volatile LockFields* lock = (LockFields*)self;
    size_t oldState, state, swapState;

    for(;;)
    {
        oldState = ReadLockState(lock);
        state = oldState + 1;

        /* Skipped when owners is the only active field
         * and we did not try to add too many shared owners. */
        if (state >= OWN_EXCLUSIVE)
        {
            /* Detect whether adding another shared owner is impossible. */
            if (LockOwners(oldState) >= OWN_MAXSHARED)
                return 0;

            /* If writer == exit, no writers are waiting. */
            if ((LockWriter(state) ^ LockExit(state)) != 0)
            {
                /* Writers are waiting. Acquiring would jump the queue. */
                if (((CurrentTick() - LockUnfair(oldState)) & 14) != 0)
                    return 0;
            }
        }

        /* Ready to take shared ownership. */
        swapState = Atomic_CompareAndSwap(LockState(lock), oldState, state);
        if (swapState == oldState)
            return 1;
    }
}

static int TryAcquireWrite(
    _Inout_ ReadWriteLock* self
)
{
    volatile LockFields* lock = (LockFields*)self;
    size_t oldState, state, swapState;

    for(;;)
    {
        oldState = ReadLockState(lock);
        state = oldState | OWN_EXCLUSIVE;

        /* Skipped when the lock is empty. */
        if (oldState != 0)
        {
            /* Detect whether there are existing owners. */
            if (LockOwners(oldState) != 0)
                return 0;

            /* Someone must be waiting. Acquiring would jump the queue. */
            if (((CurrentTick() - LockUnfair(oldState)) & 14) != 0)
                return 0;
        }

        /* Ready to take exclusive ownership. */
        swapState = Atomic_CompareAndSwap(LockState(lock), oldState, state);
        if (swapState == oldState)
            return 1;
    }
}

static void QueueAcquireRead(
    _Inout_ ReadWriteLock* self
)
{
    volatile LockFields* lock = (LockFields*)self;
    size_t oldState, state, swapState, preQueuedState;
    size_t waitFor, diff, key, spinState, spinCount;

    for (;;)
    {
        oldState = ReadLockState(lock);
        state = oldState;

        /* If there is no queue, we are the first one to wait;
         * allow unfairness for the current timer tick. */
        if (state <= OWN_EXCLUSIVE)
            LockUnfair(state) = CurrentTick();

        /* Insert a barrier every half revolution.
         * This stops writer arithmetic from wrapping. */
        if ((LockEntry(state) & ~FIELD_SIGN) == 0)
            LockWriter(state) = LockEntry(state);

        if (++LockEntry(state) == LockExit(state))
        {
            /* The queue arithmetic will wrap if we continue. */
            Thread_Yield();
            continue;
        }

        swapState = Atomic_CompareAndSwap(LockState(lock), oldState, state);
        if (swapState == oldState)
            break;
    }

    /* This thread now has a place in the queue.
     * Threads behind us may be depending on us to wake them up. */

    /* Wait for the most recent writer to enter the queue. */
    waitFor = LockWriter(state);
    key = (size_t)lock ^ waitFor;
    preQueuedState = oldState;
    spinState = LockSpin(oldState);

    for (;;)
    {
        /* Avoid write prefetching since we expect to wait. */
        oldState = *(ptrdiff_t*)lock;

        diff = LockExit(oldState) - waitFor;
        if ((diff & FIELD_SIGN) == 0)
        {
            /* The writer ahead of us in line already acquired.
             * Someone could have beat us unfairly.
             * Just wait for the current owner. */
            waitFor = LockExit(oldState);
            key = (size_t)lock ^ waitFor;
        }

        if ((diff & FIELD_SIGN) != 0 || (LockOwners(oldState) == OWN_EXCLUSIVE))
        {
            /* The writer ahead of us still hasn't acquired,
             * or someone owns the lock exclusively right now. */
            if (((CurrentTick() - LockUnfair(oldState)) & 14) == 0 &&
                LockEntry(oldState) - LockExit(oldState) >= 2 &&
                LockEntry(oldState) == LockEntry(preQueuedState) + 1 &&
                (LockOwners(oldState) < OWN_MAXSHARED))
            {
                /* Under certain conditions, we can acquire immediately if we
                 * are the last thread in line and undo joining the queue. */
                if (preQueuedState <= OWN_EXCLUSIVE)
                    state = LockOwners(oldState) + 1;
                else
                {
                    state = oldState + 1;
                    LockEntry(state) = LockEntry(preQueuedState);
                    LockWriter(state) = LockWriter(preQueuedState);
                }

                /* Atomically de-queue and acquire unfairly. */
                swapState = Atomic_CompareAndSwap(LockState(lock), oldState, state);
                if (swapState == oldState)
                    return;
                continue;
            }

            /* spinState being low means spinning usually works.
             * Use a high count if it has been working recently. */
            spinCount = (spinState & SPIN_SIGN) ?
                CONDLOCK_LOW_SPINCOUNT :
                CONDLOCK_HIGH_SPINCOUNT;

            /* Spin and/or block until something changes.
             * Adjust the spin field based on whether spinning worked. */
            if (CondLock_Wait(key, (ptrdiff_t*)lock, oldState, spinCount))
                spinState = (spinState > 2) ? (spinState - 2) : 0;
            else
                spinState = (spinState < SPIN_MAX) ? (spinState + 1) : spinState;
            continue;
        }
        
        if (LockOwners(oldState) == OWN_MAXSHARED)
        {
            /* The owner arithmetic will overflow if we continue. */
            Thread_Yield();
            continue;
        }

        state = oldState + 1;

        /* Bump the exit ticket number. We're leaving the queue. */
        LockExit(state)++;

        /* Zero the top 4 fields if the queue is now empty. */
        if (LockExit(state) == LockEntry(state))
            state = LockOwners(state);
        else
        {
            /* Not empty, but we just acquired fairly.
             * Allow unfairness for a while. */
            LockUnfair(state) = CurrentTick();
            LockSpin(state) = spinState;
        }

        /* Ready to take shared ownership. */
        swapState = Atomic_CompareAndSwap(LockState(lock), oldState, state);
        if (swapState == oldState)
            break;
    }

    if ((LockExit(state) & ~FIELD_SIGN) == 0)
    {
        /* Wakes those waiting on the artificial barrier inserted each half
         * revolution (see above). */
        key = (size_t)lock ^ LockExit(state);
        CondLock_Broadcast(key);
    }
}

static void QueueAcquireWrite(
    _Inout_ ReadWriteLock* self
)
{
    volatile LockFields* lock = (LockFields*)self;
    size_t oldState, state, swapState, preQueuedState;
    size_t waitFor, key, spinState, spinCount;

    for (;;)
    {
        oldState = ReadLockState(lock);
        state = oldState;

        /* If there is no queue, we are the first one to wait;
         * allow unfairness for the current timer tick. */
        if (state <= OWN_EXCLUSIVE)
            LockUnfair(state) = CurrentTick();

        /* Wait for the most recent thread to enter the queue. */
        waitFor = LockEntry(state);

        if (++LockEntry(state) == LockExit(state))
        {
            /* The queue arithmetic will wrap if we continue. */
            Thread_Yield();
            continue;
        }

        /* Make reader threads coming in wait for us. */
        LockWriter(state) = LockEntry(state);

        swapState = Atomic_CompareAndSwap(LockState(lock), oldState, state);
        if (swapState == oldState)
            break;
    }

    /* This thread now has a place in the queue.
     * Threads behind us may be depending on us to wake them up. */

    preQueuedState = oldState;
    key = (size_t)lock ^ waitFor;
    spinState = LockSpin(oldState);

    for (;;)
    {
        /* Avoid write prefetching since we expect to wait. */
        oldState = *(ptrdiff_t*)lock;

        if (LockExit(oldState) != waitFor || LockOwners(oldState) != 0)
        {
            /* The thread ahead of us still hasn't acquired,
             * or some reader or writer owns the lock right now. */
            if (((CurrentTick() - LockUnfair(oldState)) & 14) == 0 &&
                LockEntry(oldState) - LockExit(oldState) >= 2 &&
                LockEntry(oldState) == LockEntry(preQueuedState) + 1 &&
                LockOwners(oldState) == 0)
            {
                /* Under certain conditions, we can acquire immediately if we
                 * are the last thread in line and undo joining the queue. */
                if (preQueuedState <= OWN_EXCLUSIVE)
                    state = OWN_EXCLUSIVE;
                else
                {
                    state = oldState + OWN_EXCLUSIVE;
                    LockEntry(state) = LockEntry(preQueuedState);
                    LockWriter(state) = LockWriter(preQueuedState);
                }

                /* Atomically de-queue and acquire unfairly. */
                swapState = Atomic_CompareAndSwap(LockState(lock), oldState, state);
                if (swapState == oldState)
                    return;
                continue;
            }

            /* spinState being low means spinning usually works.
             * Use a high count if it has been working recently. */
            spinCount = (spinState & SPIN_SIGN) ?
                CONDLOCK_LOW_SPINCOUNT :
                CONDLOCK_HIGH_SPINCOUNT;

            /* Spin and/or block until something changes.
             * Adjust the spin field based on whether spinning worked. */
            if (CondLock_Wait(key, (ptrdiff_t*)lock, oldState, spinCount))
                spinState = (spinState > 2) ? (spinState - 2) : 0;
            else
                spinState = (spinState < SPIN_MAX) ? (spinState + 1) : spinState;
            continue;
        }

        state = oldState + OWN_EXCLUSIVE;

        /* Bump the exit ticket number. We're leaving the queue. */
        LockExit(state)++;

        /* Zero the top 4 fields if the queue is now empty. */
        if (LockExit(state) == LockEntry(state))
            state = LockOwners(state);
        else
        {
            /* Not empty, but we just acquired fairly.
             * Allow unfairness for a while. */
            LockUnfair(state) = CurrentTick();
            LockSpin(state) = spinState;
        }

        /* Ready to take exclusive ownership. */
        swapState = Atomic_CompareAndSwap(LockState(lock), oldState, state);
        if (swapState == oldState)
            return;
    }
}

int ReadWriteLock_TryAcquireRead(
    _Inout_ ReadWriteLock* self
)
{
    return TryAcquireRead(self);
}

void ReadWriteLock_AcquireRead(
    _Inout_ ReadWriteLock* self
)
{
    if (TryAcquireRead(self) != 0)
        return;

    QueueAcquireRead(self);
}

int ReadWriteLock_TryAcquireWrite(
    _Inout_ ReadWriteLock* self
)
{
    return TryAcquireWrite(self);
}

void ReadWriteLock_AcquireWrite(
    _Inout_ ReadWriteLock* self)
{
    if (TryAcquireWrite(self) != 0)
        return;

    QueueAcquireWrite(self);
}

void ReadWriteLock_ReleaseRead(
    _Inout_ ReadWriteLock* self)
{
    volatile LockFields* lock = (LockFields*)self;
    size_t state, key;

    state = Atomic_Dec(LockState(lock));
    if (state >= OWN_EXCLUSIVE && LockOwners(state) == 0)
    {
        /* There is a queue.
         * Writers may be blocked waiting for us to leave. */
        key = (size_t)lock ^ LockExit(state);
        CondLock_Broadcast(key);

        //if (((LockEntry(state) - LockExit(state)) & (FIELD_SIZE - 1)) == 2 &&
        if (LockEntry(state) - LockExit(state) >= 2 &&
            ((CurrentTick() - LockUnfair(state)) & 14) == 0)
        {
            /* Under certain conditions, encourage the last group of threads in
             * line to stop spinning and acquire unfairly. */
            if (LockEntry(state) == LockWriter(state))
                key = (size_t)lock ^ (LockEntry(state) - 1);
            else
                key = (size_t)lock ^ LockWriter(state);
            CondLock_BroadcastSpinners(key);
        }
    }
}

void ReadWriteLock_ReleaseWrite(
    _Inout_ ReadWriteLock* self)
{
    volatile LockFields* lock = (LockFields*)self;
    size_t state, key;

    state = Atomic_Add(LockState(lock), -OWN_EXCLUSIVE);
    if (state != 0)
    {
        /* There is a queue.
         * Threads may be blocked waiting for us to leave. */
        key = (size_t)lock ^ LockExit(state);
        CondLock_Broadcast(key);

        //if (((LockEntry(state) - LockExit(state)) & (FIELD_SIZE - 1)) == 2 &&
        if (LockEntry(state) - LockExit(state) >= 2 &&
            ((CurrentTick() - LockUnfair(state)) & 14) == 0)
        {
            /* Under certain conditions, encourage the last group of threads in
             * line to stop spinning and acquire unfairly. */
            if (LockEntry(state) == LockWriter(state))
                key = (size_t)lock ^ (LockEntry(state) - 1);
            else
                key = (size_t)lock ^ LockWriter(state);
            CondLock_BroadcastSpinners(key);
        }
    }
}
