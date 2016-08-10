/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <nits/base/nits.h>
#include "strings.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>

#if !defined(_MSC_VER)
# include <pthread.h>
#endif

#if defined(USE_ALLOCATOR)
# define ALLOC_MAGIC 0x89ABCDEF
# define ENABLE_FILLING
# define ENABLE_CLEARING

static AllocStats _stats;
static pthread_mutex_t _mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct _AllocHeader AllocHeader;

struct _AllocHeader
{
    struct _AllocHeader* prev;
    struct _AllocHeader* next;
    const char* file;
    unsigned int line;
    unsigned int id;
    unsigned int magic;
    unsigned int size;
};

static unsigned int _id;

static AllocHeader* _list;

typedef struct _AllocTrailer
{
    unsigned int magic;
}
AllocTrailer;

static size_t _GetSize(void* ptr)
{
    AllocHeader* h = (AllocHeader*)ptr - 1;
    AllocTrailer* t;

    if (h->magic != ALLOC_MAGIC || h->size == 0)
        return (size_t)-1;

    t = (AllocTrailer*)((char*)ptr + h->size);

    if (t->magic != ALLOC_MAGIC)
        return (size_t)-1;

    return (size_t)h->size;
}

AllocStats PAL_GetAllocStats()
{
    AllocStats stats;
    pthread_mutex_lock(&_mutex);
    stats = _stats;
    pthread_mutex_unlock(&_mutex);
    return stats;
}

size_t PAL_GetBlocksAllocated()
{
    AllocStats stats;
    pthread_mutex_lock(&_mutex);
    stats = _stats;
    pthread_mutex_unlock(&_mutex);
    return (size_t)(stats.numAllocs - stats.numFrees);
}

void PAL_CheckBlocksAllocated(
    size_t oldBlocksAllocated,
    const char* file,
    size_t line,
    const char* function)
{
    size_t blocksAllocated = PAL_GetBlocksAllocated();
    size_t nblocks;

    if (blocksAllocated <= oldBlocksAllocated)
        return;

    nblocks = blocksAllocated - oldBlocksAllocated;

    printf("\nWARNING: %s(%u): %s(): %u blocks were leaked\n\n",
        file, (int)line, function, (int)nblocks); 
}

void PAL_DumpAllocStats()
{
    AllocStats stats = PAL_GetAllocStats();

    printf("=== PAL_DumpAllocStats:\n");
    printf("usage: %d\n", (int)stats.usage);
    printf("peakUsage: %d\n", (int)stats.peakUsage);
    printf("numAllocs: %d\n", (int)stats.numAllocs);
    printf("numFrees: %d\n", (int)stats.numFrees);
    printf("\n");
}

void PAL_DumpAllocList()
{
    AllocHeader* p;

    if (!_list)
        return;

    printf("\nWARNING: one or more blocks still allocated!\n");

    for (p = _list; p; p = p->next)
    {
        printf("BLOCK: %s(%u): ptr=%p: magic=%08X id=%u size=%u\n",
            p->file, (int)p->line, p, p->magic, p->id, p->size);
    }

    printf("\n");
    printf("\n");
}

static void* _Alloc(
    const char* file,
    size_t line,
    const char* func,
    size_t size)
{
    AllocHeader* h;
    AllocTrailer* t;
    void* p;

    /* Be sure size will fit into h->size field */
    assert(size <= UINT_MAX);

    /* Return null if request size is zero */
    if (size == 0)
    {
        assert(0);
        return NULL;
    }

    /* Allocate the block of memory with room for header and trailer */
    if (!(h = SystemMalloc(sizeof(AllocHeader) + size + sizeof(AllocTrailer))))
    {
        assert(0);
        return NULL;
    }

    /* Initialize the header */
    h->prev = NULL;
    h->next = NULL;
    h->file = file;
    h->line = line;
    h->magic = ALLOC_MAGIC;
    h->size = (unsigned int)size;

    /* Initialize the user block (fill with 0xAA bytes) */
    p = h + 1;
#if defined(ENABLE_FILLING)
    memset(p, 0xAA, size);
#else
    memset(p, 0x00, size);
#endif

    /* Initialize the trailer */
    t = (AllocTrailer*)((char*)p + size);
    t->magic = ALLOC_MAGIC;

    /* Check that this function created a valid block */
    assert(_GetSize(p) == size);

    /* Update statistics and add block to glboal list */
    pthread_mutex_lock(&_mutex);
    {
        _stats.usage += size;
        _stats.numAllocs++;

        if (_stats.usage > _stats.peakUsage)
            _stats.peakUsage = _stats.usage;

        /* Prepend block to list */
        {
            if (_list)
                _list->prev = h;

            h->prev = NULL;
            h->next = _list;
            _list = h;
        }

        h->id = _id++;
    }
    pthread_mutex_unlock(&_mutex);

    return p;
}

void* __PAL_Malloc(
    const char* file,
    size_t line,
    const char* func,
    size_t size)
{
#if defined(ENABLE_ALLOC_FAULT_INJECTION)
    if (file && 
        NitsShouldFault(NitsMakeCallSite(-1, func, file, line), NitsAutomatic))
        return NULL;
#endif

    return _Alloc(file, line, func, size);
}

void* __PAL_MallocCallsite(
    NitsCallSite callsite,
    size_t size)
{
#if defined(ENABLE_ALLOC_FAULT_INJECTION)
    if (NitsShouldFault(callsite, NitsAutomatic))
        return NULL;
#endif

    return _Alloc(callsite.file, callsite.line, callsite.function, size);
}

void* _Calloc(
    const char* file,
    size_t line,
    const char* func,
    size_t count,
    size_t size)
{
    void* p;
    size_t n = count * size; 

    if (n == 0)
        return NULL;
    
    if (!(p = _Alloc(file, line, func, n)))
        return NULL;

    return memset(p, 0x00, n);    
}

void* __PAL_Calloc(
    const char* file,
    size_t line,
    const char* func,
    size_t count,
    size_t size)
{

#if defined(ENABLE_ALLOC_FAULT_INJECTION)
    if (file && 
        NitsShouldFault(NitsMakeCallSite(-1, func, file, line), NitsAutomatic))
        return NULL;
#endif

    return _Calloc( file, line, func, count, size);
}

void* __PAL_CallocCallsite(
    NitsCallSite callsite,
    size_t count,
    size_t size)
{

#if defined(ENABLE_ALLOC_FAULT_INJECTION)
    if (NitsShouldFault(callsite, NitsAutomatic))
        return NULL;
#endif
    
    return _Calloc(callsite.file, callsite.line, callsite.function, count, size);
}


void* _Realloc(
    const char* file,
    size_t line,
    const char* func,
    void* ptr,
    size_t size)
{
    size_t n;
    void* p;

    /* Fail if request size is zero */
    if (size == 0)
    {
        assert(0);
        return NULL;
    }

    /* If ptr is null, then just pass to _Alloc() */
    if (!ptr)
        return _Alloc(file, line, func, size);

    /* Get the size of the old block (assert if invalid block) */
    n = _GetSize(ptr);
    assert(n != (size_t)-1);

    /* Allocate the new block */
    if (!(p = _Alloc(file, line, func, size)))
    {
        assert(0);
        return NULL;
    }
    
    /* Copy over data from the old block */
    if (n < size)
    {
        memcpy(p, ptr, n);

        /* Fill unused part with 0xAA bytes */
#if defined(ENABLE_FILLING)
        memset((char*)p + n, 0xAA, size - n);
#else
        memset((char*)p + n, 0x00, size - n);
#endif
    }
    else
        memcpy(p, ptr, size);

    /* Free the old block */
    __PAL_Free(file, line, func, ptr);

    return p;    
}

void* __PAL_Realloc(
    const char* file,
    size_t line,
    const char* func,
    void* ptr,
    size_t size)
{

#if defined(ENABLE_ALLOC_FAULT_INJECTION)
    if (file && 
        NitsShouldFault(NitsMakeCallSite(-1, func, file, line), NitsAutomatic))
        return NULL;
#endif

    return _Realloc(file, line, func, ptr, size);
}


void* __PAL_ReallocCallsite(
    NitsCallSite callsite,
    void* ptr,
    size_t size)
{
#if defined(ENABLE_ALLOC_FAULT_INJECTION)
    if (NitsShouldFault(callsite, NitsAutomatic))
        return NULL;
#endif

    return _Realloc(callsite.file, callsite.line, callsite.function, ptr, size);
}

void __PAL_Free(
    const char* file,
    size_t line,
    const char* func,
    void* ptr)
{
    if (ptr)
    {
        size_t n;
        AllocHeader* h;

        /* Get size of this block */
        n = _GetSize(ptr);
        assert(n != (size_t)-1);

        /* Fill the block with 0xDD bytes */
#if defined(ENABLE_CLEARING)
        memset(ptr, 0xDD, n);
#endif

        /* Get pointer to header */
        h = (AllocHeader*)ptr - 1;

        /* Update statistics and remove block from list */
        pthread_mutex_lock(&_mutex);
        {
            _stats.usage -= n;
            _stats.numFrees++;

            /* Remove block from the list */
            if (h == _list)
            {
                _list = h->next;

                if (_list)
                    _list->prev = NULL;
            }
            else
            {
                if (h->prev)
                    h->prev->next = h->next;
                if (h->next)
                    h->next->prev = h->prev;
            }

        }
        pthread_mutex_unlock(&_mutex);

        /* Free the block */
        SystemFree(h);
    }
}

char* __PAL_Strdup(
    const char* file,
    size_t line,
    const char* func,
    const char* str)
{
    char* p;
    size_t n;

    assert(str != NULL);

    n = (strlen(str) + 1) * sizeof(char);

    if (!(p = _Alloc(file, line, func, n)))
        return NULL;

    return memcpy(p, str, n);
}

wchar_t* __PAL_Wcsdup(
    const char* file,
    size_t line,
    const char* func,
    const wchar_t* str)
{
    wchar_t* p;
    size_t n;

    assert(str != NULL);

    n = (wcslen(str) + 1) * sizeof(wchar_t);

    if (!(p = _Alloc(file, line, func, n)))
        return NULL;

    return memcpy(p, str, n);
}

PAL_Char* __PAL_Tcsdup(
    const char* file,
    size_t line,
    const char* func,
    const PAL_Char* str)
{
    PAL_Char* p;
    size_t n;

    assert(str != NULL);

    n = (Tcslen(str) + 1) * sizeof(PAL_Char);

    if (!(p = _Alloc(file, line, func, n)))
        return NULL;

    return memcpy(p, str, n);
}

#endif /* defined(USE_ALLOCATOR) */
