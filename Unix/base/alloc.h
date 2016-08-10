/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_alloc_h
#define _omi_alloc_h

#include "config.h"
#include <common.h>
#include "batch.h"

BEGIN_EXTERNC

MI_INLINE void* BAlloc(
    Batch* batch, 
    size_t size,
    CallSite callSite)
{
    MI_UNUSED(callSite);
    return Batch_Get(batch, size);
}

MI_INLINE void BFree(
    Batch* batch, 
    void* ptr,
    CallSite callSite)
{
    MI_UNUSED(callSite);
    Batch_Put(batch, ptr);
}

MI_INLINE void* BRealloc(
    Batch* batch, 
    void* ptr, 
    size_t oldSize, 
    size_t newSize,
    CallSite callSite)
{
    if (!ptr)
        return Batch_Get(batch, newSize);
    else
    {
        void* p = Batch_Get(batch, newSize);
        MI_UNUSED(callSite);

        if (!p)
            return NULL;

        if (oldSize < newSize)
        {
            memcpy(p, ptr, oldSize);
            memset((char*)p + oldSize, 0, newSize - oldSize);
        }
        else
            memcpy(p, ptr, newSize);

        return p;
    }
}

MI_INLINE void* BCalloc(
    Batch* batch, 
    size_t size,
    CallSite callSite)
{
    MI_UNUSED(callSite);
    return Batch_GetClear(batch, size);
}

MI_INLINE ZChar* BStrdup(
    Batch* batch, 
    const ZChar* str,
    CallSite callSite)
{
    MI_UNUSED(callSite);
    return Batch_Tcsdup(batch, str);
}

END_EXTERNC

#endif /* _omi_alloc_h */
