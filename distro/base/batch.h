/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
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

#define BATCH_MAX_PAGES 64

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
             * pass this block to free(). Otherwise, calling Batch_Put()
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

Batch* Batch_New(
    size_t maxPages);

void Batch_Delete(
    Batch* self);

void* Batch_Get(
    Batch* self,
    size_t size);

MI_INLINE void* Batch_GetClear(
    Batch* self,
    size_t size)
{
    void* ptr = Batch_Get(self, size);

    if (ptr)
        memset(ptr, 0, size);

    return ptr;
}

void Batch_Put(
    Batch* self,
    void* ptr);

ZChar* Batch_Zdup(
    Batch* self,
    const ZChar* str);

char* Batch_Strdup(
    Batch* self,
    const char* str);

#if defined(CONFIG_ENABLE_WCHAR)
ZChar* Batch_StrZdup(
    Batch* self,
    const char* str);
#else
MI_INLINE ZChar* Batch_StrZdup(
    Batch* self,
    const char* str)
{
    return Batch_Strdup(self, str);
}
#endif

#if defined(CONFIG_ENABLE_WCHAR)
char* Batch_ZStrdup(
    Batch* self,
    const ZChar* str);
#else
MI_INLINE char* Batch_ZStrdup(
    Batch* self,
    const ZChar* str)
{
    return Batch_Strdup(self, str);
}
#endif

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
