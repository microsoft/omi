/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "lock.h"
#include "thread.h"

void RecursiveLock_Acquire(
    _Inout_ RecursiveLock* self
)
{
    ThreadID me = Thread_ID();

    if (self->count > 0)
    {
        if (Thread_Equal(&me, &self->owner) != 0)
        {
            self->count++;
            return;
        }
    }

    Lock_Acquire(&self->lock);
    self->owner = me;
    self->count = 1;
}
