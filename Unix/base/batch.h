/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_batch_h
#define _omi_batch_h

#include "config.h"
#include <string.h>
#include <common.h>

BEGIN_EXTERNC

/*
**==============================================================================
**
** Batch
**
**     This type defines a fast O(1) batch allocator. Chunks are allocated
**     incrementally and then released as a batch. Clients of this interface 
**     allocate and deallocate memory as shown here.
**
**         Batch batch;
**         char* ptr; 
**
**         SystemAlloc_Init(&batch);
**         ptr = Batch_Get(&batch, 16);
**
**     Chunks are released all at once (in batch) like this.
**
**         Batch_Destroy(&batch);
**
**     All allocations exceeding the maximum block size or maximum total size
**     of the batch are allocated on the heap. These blocks can be released
**     released individually with:
**
**         Batch_Put(&batch, ptr);
**
**     Pointers passed to this function that are not on the heap are ignored,
**     so it is safe to call Put() in the general case.
**
**==============================================================================
*/

#define BATCH_MAX_PAGES INFINITE

#define BATCH_INITIALIZER { NULL, NULL, NULL, 0, BATCH_MAX_PAGES }

/* Represents a page of memory */
typedef struct _Page
{
    union
    {
        struct _Page_s
        {
            struct _Page* next;

            /* If non-zero, this page may be independenty released (contains
             * a single block). If so, then passing it to Batch_Put() will
             * pass this block to PAL_Free(). Otherwise, calling Batch_Put()
             * has no effect.
             */
            unsigned int independent:1;

            /* Size of the allocation (not including page header) */
            unsigned int size:31;
        }
        s;
        char alignment[(sizeof(struct _Page_s) + 7) & ~7];
    }
    u;
}
Page;

typedef struct _Batch
{
    /* Pointer to next available byte of current page */
    char* avail;

    /* Pointer to last byte of available memory */
    char* end;

    /* Pointer to page list */
    Page* pages;

    /* Number of pages */
    size_t numPages;

    /* Maximum number of pages */
    size_t maxPages;
}
Batch;

MI_INLINE void Batch_Init(
    Batch* self,
    size_t maxPages)
{
    memset(self, 0, sizeof(Batch));
    self->maxPages = maxPages;
}

void Batch_InitFromBuffer(
    Batch* self, 
    void* data,
    size_t size,
    size_t maxPages);

void Batch_Destroy(
    Batch* self);

void Batch_Delete(
    Batch* self);

#if defined(CONFIG_ENABLE_DEBUG) && defined(CONFIG_OS_LINUX)

#define BATCH_CALLSITE , __FILE__, __LINE__, __FUNCTION__
#define BATCH_CALLSITE_DEF , const char* file, size_t line, const char* func
#define BATCH_CALLSITE_PASSTHROUGH , file, line, func

#else

#define BATCH_CALLSITE
#define BATCH_CALLSITE_DEF
#define BATCH_CALLSITE_PASSTHROUGH

#endif

#define Batch_New(pages) __Batch_New(pages BATCH_CALLSITE)
#define Batch_Get(self, size) __Batch_Get(self, size BATCH_CALLSITE)
#define Batch_GetClear(self, size) __Batch_GetClear(self, size BATCH_CALLSITE)
#define Batch_Tcsdup(self, str) __Batch_Tcsdup(self, str BATCH_CALLSITE)
#define Batch_Strdup(self, str) __Batch_Strdup(self, str BATCH_CALLSITE)
#define Batch_StrTcsdup(self, str) __Batch_StrTcsdup(self, str BATCH_CALLSITE)
#define Batch_ZStrdup(self, str) __Batch_ZStrdup(self, str BATCH_CALLSITE)

Batch* __Batch_New(
    size_t maxPages 
    BATCH_CALLSITE_DEF);

void* __Batch_Get(
    Batch* self, 
    size_t size 
    BATCH_CALLSITE_DEF);

MI_INLINE void* __Batch_GetClear(
    Batch* self, 
    size_t size 
    BATCH_CALLSITE_DEF)
{
    void* ptr = __Batch_Get(self, size BATCH_CALLSITE_PASSTHROUGH);

    if (ptr)
        memset(ptr, 0, size);

    return ptr;
}

_Check_return_
ZChar* __Batch_Tcsdup(
    Batch* self, 
    const ZChar* str 
    BATCH_CALLSITE_DEF);

_Check_return_
char* __Batch_Strdup(
    Batch* self, 
    const char* str 
    BATCH_CALLSITE_DEF);

MI_INLINE ZChar* __Batch_StrTcsdup(
    Batch* self, 
    const char* str 
    BATCH_CALLSITE_DEF)
{
    return __Batch_Strdup(self, str BATCH_CALLSITE_PASSTHROUGH);
}

MI_INLINE char* __Batch_ZStrdup(
    Batch* self,
    const ZChar* str
    BATCH_CALLSITE_DEF)
{
    return __Batch_Strdup(self, str BATCH_CALLSITE_PASSTHROUGH);
}

void Batch_Put(
    Batch* self,
    void* ptr);

/* protocol support */
typedef struct _Header_BatchInfoItem
{
    void*   pagePointer;
    size_t  pageSize;
}
Header_BatchInfoItem;

size_t Batch_GetPageCount(
    Batch* self);

void* Batch_GetPageByIndex(
    Batch* self,
    size_t index);

size_t Batch_GetPageInfo(
    Batch* self,
    Header_BatchInfoItem* buffer);

MI_Boolean Batch_CreateBatchByPageInfo(
    Batch** self,
    const Header_BatchInfoItem* buffer,
    size_t pages);

MI_Boolean Batch_FixPointer(
    Batch* batch,
    const Header_BatchInfoItem* ptrAdjustmentInfo,
    size_t ptrAdjustmentInfoCount,
    void** ptrInOut);

/* Add this block to list of individual blocks */
MI_INLINE void Batch_AttachPage(
    Batch* self,
    Page* page)
{
    page->u.s.next = self->pages;
    self->pages = page;
    page->u.s.independent = 0;
}

END_EXTERNC

#endif /* _omi_batch_h */
