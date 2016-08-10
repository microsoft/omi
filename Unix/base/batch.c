/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <assert.h>
#include "batch.h"
#include <pal/strings.h>
#include <pal/intsafe.h>

#define BATCH_PAGE_SIZE ((size_t)(BLOCK_SIZE * 2))
#define BLOCK_SIZE ((size_t)512)

void* Batch_Get(
    Batch* self,
    size_t size)
{
    size_t size8;

    /* Round request size to a multiple of eight */
    size8 = (size + 7) & ~7;

    /* Attempt to obtain the block from the available storage */
    if (size8 <= BLOCK_SIZE && size8 <= (size_t)(self->end - self->avail))
    {
        char* ptr = self->avail;
        self->avail += size8;
        return ptr;
    }

    /* Allocate a new page and carve new block from that page */
    if (size8 <= BLOCK_SIZE && self->numPages < self->maxPages)
    {
        Page* page = PAL_Malloc(BATCH_PAGE_SIZE);
        char* ptr;

        if (!page)
            return NULL;

        memset(page, 0, sizeof(page->u.s));
        page->u.s.independent = 0;
        page->u.s.size = BATCH_PAGE_SIZE - sizeof(Page);
#ifdef CONFIG_ENABLE_DEBUG
        memset(page + 1,0xAA, page->u.s.size);
#endif

        /* Link new page onto list */
        page->u.s.next = self->pages;
        self->pages = page;

        /* Calculate pointer (skip over Page.next field) */
        ptr = (char*)(page + 1);

        /* Set the available memory pointers */
        self->avail = ptr + size8;
        self->end = (char*)page + BATCH_PAGE_SIZE;

        /* Update number of pages */
        self->numPages++;

        /* Return pointer to memory */
        return ptr;
    }

    /* Chunk is larger than the block size or maximum batch size has been
     * exceeded (so obtain it from the heap and place it on the individual
     * blocks list)
     */
    {
        Page* page = PAL_Malloc(sizeof(Page) + size8);

        if (!page)
            return NULL;

        /* Set the size of the page */
        memset(page, 0, sizeof(page->u.s));
        page->u.s.independent = 1;
        page->u.s.size = (unsigned int)size8;
#ifdef CONFIG_ENABLE_DEBUG
        memset(page + 1,0xAA, page->u.s.size);
#endif

        page->u.s.next = self->pages;
        self->pages = page;

        /* Return pointer to memory */
        return page + 1;
    }
}

void Batch_Destroy(
    Batch* self)
{
    Page* p;
    void* selfPtr = NULL;

    /* Free batch pages */
    for (p = self->pages; p; )
    {
        Page* next = p->u.s.next;

        /* If memory object contains this batch, delete it last */
        if ((char*)self>=(char*)(p + 1) && (char*)self<(char*)p + p->u.s.size)
            selfPtr = p;
        else
            PAL_Free(p);

        p = next;
    }

    if (selfPtr)
        PAL_Free(selfPtr);
}

void Batch_InitFromBuffer(
    Batch* self,
    void* data,
    size_t size,
    size_t maxPages)
{
    self->avail = data;
    self->end = (char*)data + size;
    self->pages = NULL;
    self->numPages = 0;
    self->maxPages = maxPages;
}

Batch* Batch_New(
    size_t maxPages)
{
    Batch batch;
    Batch* self;

    /* Construct batch on the stack. Next allocate space for batch within
     * the batch itself. Finally, copy the batch from the stack onto the
     * batch itself. Now the batch contains itself. This avoids an extra
     * allocation.
     */

    Batch_Init(&batch, maxPages);
    self = (Batch*)Batch_Get(&batch, sizeof(Batch));

    if (!self)
    {
        Batch_Destroy(&batch);
        return NULL;
    }

    return memcpy(self, &batch, sizeof(Batch));
}

void Batch_Delete(
    Batch* self)
{
    /* Destroying the batch frees the batch object on heap (since batch
     * contains itself.
     */
    Batch_Destroy(self);
}

void Batch_Put(
    Batch* self,
    void* ptr)
{
    Page* p;
    Page* page;
    Page* prev = NULL;
#if defined (CONFIG_ENABLE_DEBUG)
    int found = 0;
#endif

    if (!ptr)
        return;

    /* Get pointer to start of page */
    page = (Page*)ptr - 1;

    /* Free independent pages */
    for (p = self->pages; p; p = p->u.s.next)
    {
        if (p == page)
        {
            /* Skip if page is not independent */
            if (!page->u.s.independent)
                return;

            /* Remove from linked list */
            if (prev)
                prev->u.s.next = p->u.s.next;
            else
                self->pages = p->u.s.next;

            PAL_Free(p);
            return;
        }
#if defined (CONFIG_ENABLE_DEBUG)
        else
        {
            void* start = (char*)p + sizeof(Page);
            void* end = (char*)start + p->u.s.size;

            if (ptr >= start && ptr < end)
                found = 1;
        }
#endif


        prev = p;
    }

    /* ATTN: put debug assert here */

#if defined (CONFIG_ENABLE_DEBUG)
    if (!found)
        DEBUG_ASSERT(0);
#endif
}

_Use_decl_annotations_
ZChar* Batch_Tcsdup(
    Batch* self,
    const ZChar* str)
{
    ZChar* p;
    size_t size;

    size = (Tcslen(str) + 1) * sizeof(ZChar);

    p = Batch_Get(self, size);

    if (!p)
        return NULL;

    return memcpy(p, str, size);
}

_Use_decl_annotations_
char* Batch_Strdup(
    Batch* self,
    const char* str)
{
    char* p;
    size_t size = 0;

    if(!self || !str)
        return NULL;

    size = Strlen(str) + 1;

    p = (char*) Batch_Get(self, size);

    if (!p)
        return NULL;

    return memcpy(p, str, size);
}

#if defined(CONFIG_ENABLE_WCHAR)
char* Batch_ZStrdup(
    Batch* self,
    const ZChar* s)
{
    size_t size = 0;
    char* p;
    size_t i;

    if(!self || !s)
        return NULL;

    size = Tcslen(s) + 1;
    p = Batch_Get(self, size * sizeof(char));

    if (!p)
        return NULL;

    for (i = 0; i < size; i++)
        p[i] = (char)s[i];

    return p;
}
#endif

#if defined(CONFIG_ENABLE_WCHAR)
ZChar* Batch_StrTcsdup(
    Batch* self,
    const char* s)
{
    size_t size = 0;
    ZChar* p;
    size_t i;

    if(!self || !s)
        return NULL;

    size = strlen(s) + 1;
    p = Batch_Get(self, size * sizeof(ZChar));

    if (!p)
        return NULL;

    for (i = 0; i < size; i++)
        p[i] = (ZChar)s[i];

    return p;
}
#endif

size_t Batch_GetPageCount(
    Batch* self)
{
    size_t res = 0;
    Page* p;

    for (p = self->pages; p; p = p->u.s.next)
    {
        res++;
    }

    return res;
}

size_t Batch_GetPageInfo(
    Batch* self,
    Header_BatchInfoItem* buffer)
{
    size_t res = 0;
    Page* p;

    for (p = self->pages; p; p = p->u.s.next)
    {
        buffer->pagePointer = p+1;

        /* for current page we can send only part of it */
        if (self->end == ((char*)p + BATCH_PAGE_SIZE))
            buffer->pageSize = self->avail - (char*)(p + 1);
        else
            buffer->pageSize = p->u.s.size;

        buffer++;
        res++;
    }

    return res;
}

void* Batch_GetPageByIndex(
    Batch* self,
    size_t index)
{
    Page* p;

    for (p = self->pages; p && index != 0; p = p->u.s.next)
    {
        index--;
    }

    return p ? p + 1 : 0;
}

MI_Boolean Batch_CreateBatchByPageInfo(
    Batch** self,
    const Header_BatchInfoItem* buffer,
    size_t pages)
{
    Page* page;

    /*if (!(*self))
    {
        *self = Batch_New(BATCH_MAX_PAGES);

        if (! (*self))
            return MI_FALSE;
    }*/

    while (pages)
    {
        pages--;

        /* put batch inside first page */
        if (!(*self))
        {
            size_t size;
            size_t size8;
            size_t alloc_size;

            if (SizeTAdd(sizeof(Page), buffer[pages].pageSize, &size) != S_OK)
            {
                return MI_FALSE;
            }

            /* Round request size to a multiple of eight */
            size8 = (size + 7) & ~7;

            if (SizeTAdd(size8, sizeof(Batch), &alloc_size) == S_OK)
            {
                page = PAL_Malloc(alloc_size);
            }
            else
            {
                return MI_FALSE;
            }

            if (!page)
                return MI_FALSE;

            *self = (Batch*)(((char*)page) + size8);
            Batch_Init(*self, BATCH_MAX_PAGES);
        }
        else
        {
            size_t alloc_size;
            if (SizeTAdd(sizeof(Page), buffer[pages].pageSize, &alloc_size) == S_OK)
            {
                page = PAL_Malloc(alloc_size);
            }
            else
            {
                page = NULL;
            }
        }

        if (!page)
        {
            Batch_Destroy((*self));
            (*self) = 0;
            return MI_FALSE;
        }

        memset(page, 0, sizeof(page->u.s));
        page->u.s.independent = 0;
        page->u.s.size = (unsigned int)buffer[pages].pageSize;
#ifdef CONFIG_ENABLE_DEBUG
        memset(page + 1,0xAA,page->u.s.size);
#endif

        /* Link new page onto list */
        page->u.s.next = (*self)->pages;
        (*self)->pages = page;
    }

    return MI_TRUE;
}

MI_Boolean Batch_FixPointer(
    Batch* self,
    const Header_BatchInfoItem* ptrAdjustmentInfo,
    size_t ptrAdjustmentInfoCount,
    void** ptrInOut)
{
    /* see if pointer matches old blocks */
    size_t index;
    char* old_ptr = *ptrInOut;
    Page* p;

    /* since we may have now more pages than initially, skip new pages */
    p = Batch_GetPageByIndex(self,Batch_GetPageCount(self) - ptrAdjustmentInfoCount);

    if (!p)
        return MI_FALSE;
    p--;

    for (index = 0; p && index < ptrAdjustmentInfoCount; p = p->u.s.next, index++)
    {
        char* old_page = ptrAdjustmentInfo[index].pagePointer;

        if ( old_ptr >= old_page &&
            old_ptr < (old_page + ptrAdjustmentInfo[index].pageSize) )
        {
            *ptrInOut = ((char*)(p + 1)) + (old_ptr - old_page);
            return MI_TRUE;
        }
    }

    return MI_FALSE;
}
