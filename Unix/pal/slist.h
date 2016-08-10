/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _pal_slist_h
#define _pal_slist_h

#include <stddef.h>
#include <string.h>
#include "palcommon.h"

#if !defined(_MSC_VER)
# include "atomic.h"
#endif

/*
**==============================================================================
**
** Windows Version
**
**==============================================================================
*/

#if defined(_MSC_VER)

PAL_BEGIN_EXTERNC

#define SList_Alloc( size )     (_aligned_malloc( (size), MEMORY_ALLOCATION_ALIGNMENT ))
#define SList_Free( ptr )       (_aligned_free( ptr ))

typedef struct _SListEntry 
{
    /* Private field! */
    SLIST_ENTRY __private;
}
SListEntry;

typedef struct _SListHead
{
    /* Private field! */
    SLIST_HEADER __private;
}
SListHead;

PAL_INLINE void SList_Init(
    _Out_ SListHead* head)
{
    InitializeSListHead(&head->__private);
}

PAL_INLINE SListEntry* SList_FlushAtomic(
    _Inout_ SListHead* head)
{
    return (SListEntry*)InterlockedFlushSList(&head->__private);
}

PAL_INLINE SListEntry* SList_PushAtomic(
    _Inout_ SListHead* head,
    _Inout_ SListEntry* entry)
{
    return (SListEntry*)InterlockedPushEntrySList(
        &head->__private, 
        &entry->__private);
}

PAL_INLINE SListEntry* SList_PopAtomic(
    _Inout_ SListHead* head)
{
    return (SListEntry*)InterlockedPopEntrySList(&head->__private);
}

PAL_INLINE SListEntry* SList_Next(
    _Inout_ SListEntry* entry)
{
    return (SListEntry*)entry->__private.Next;
}

PAL_END_EXTERNC

#endif /* defined(_MSC_VER) */

/*
**==============================================================================
**
** Non-Windows Version
**
**==============================================================================
*/

#if !defined(_MSC_VER)

PAL_BEGIN_EXTERNC

#define SList_Alloc( size )     (PAL_Malloc( size ))
#define SList_Free( ptr )       (PAL_Free( ptr ))

typedef struct ___SListEntryRep
{
    struct _SListEntry* next;
}
__SListEntryRep;

typedef struct ___SListHeadRep
{
    struct _SListEntry* next;
    ptrdiff_t lock;
}
__SListHeadRep;

typedef struct _SListEntry 
{
    /* Private field! */
    __SListEntryRep __private;
}
SListEntry;

typedef struct _SListHead 
{
    /* Private field! */
    __SListHeadRep __private;
}
SListHead;

PAL_INLINE void SList_Init(
    _Inout_ SListHead* head)
{
    head->__private.next = NULL;
    head->__private.lock = 0;
}

SListEntry* SList_FlushAtomic(
    _Inout_ SListHead* head);

SListEntry* SList_PushAtomic(
    _Inout_ SListHead* head,
    _Inout_ SListEntry* entry);

SListEntry* SList_PopAtomic(
    _Inout_ SListHead* head);

PAL_INLINE SListEntry* SList_Next(
    _Inout_ SListEntry* entry)
{
    return entry->__private.next;
}

PAL_END_EXTERNC

#endif /* !defined(_MSC_VER) */

#endif /* _pal_slist_h */
