/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _memory_man_h
#define _memory_man_h

#include <common.h>
# include <sys/mman.h>

BEGIN_EXTERNC

MI_INLINE void MemoryLock(void* addr, size_t len)
{
    mlock(addr, len);
}

MI_INLINE void MemoryUnlock(void* addr, size_t len)
{
    munlock(addr, len);
}

_Check_return_ _Ret_maybenull_ _Post_writable_byte_size_(size)
MI_INLINE void *MemoryRealloc(
    _Pre_valid_ _Post_ptr_invalid_ void ** ptr,
    _In_ size_t size)
{
    void * _newptr = PAL_Realloc(*ptr, size);
    if (!_newptr)
    {
        // To avoid memory leak, release the memory *ptr
        PAL_Free(*ptr);
    }
    // Set *ptr to NULL, caller should not double release it
    *ptr = NULL;
    return _newptr;
}

END_EXTERNC

#endif /* _memory_man_h */
