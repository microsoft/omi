/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "slist.h"

#if !defined(_MSC_VER)

PAL_INLINE void Atomic_Lock(
    _Inout_ volatile ptrdiff_t* dest)
{
    while (Atomic_Swap(dest, 1) == 1)
        while (*dest)
            ;
}

PAL_INLINE void Atomic_Unlock(
    _Inout_ volatile ptrdiff_t* dest)
{
    Atomic_Swap(dest, 0);
}

SListEntry* SList_FlushAtomic(
    _Inout_ SListHead* head)
{
    Atomic_Lock(&head->__private.lock);
    SListEntry* p = head->__private.next;
    head->__private.next = NULL;
    Atomic_Unlock(&head->__private.lock);
    return p;
}

SListEntry* SList_PushAtomic(
    _Inout_ SListHead* head,
    _Inout_ SListEntry* entry)
{
    SListEntry* p;

    Atomic_Lock(&head->__private.lock);

    entry->__private.next = head->__private.next;
    p = head->__private.next;
    head->__private.next = entry;

    Atomic_Unlock(&head->__private.lock);

    return p;
}

SListEntry* SList_PopAtomic(
    _Inout_ SListHead* head)
{
    Atomic_Lock(&head->__private.lock);

    SListEntry* p = head->__private.next;

    if (p)
    {
        head->__private.next = p->__private.next;
    }

    Atomic_Unlock(&head->__private.lock);

    return p;
}

#endif /* !defined(_MSC_VER) */
