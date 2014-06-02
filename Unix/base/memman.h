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

#ifndef _memory_man_h
#define _memory_man_h

#include <common.h>

#if defined(CONFIG_OS_WINDOWS)
# include <winbase.h>
#else
# include <sys/mman.h>
#endif

BEGIN_EXTERNC

MI_INLINE void MemoryLock(void* addr, size_t len)
{
#if defined(CONFIG_OS_WINDOWS)
    VirtualLock(addr, len);
#else
    mlock(addr, len);
#endif
}

MI_INLINE void MemoryUnlock(void* addr, size_t len)
{
#if defined(CONFIG_OS_WINDOWS)
    VirtualUnlock(addr, len);
#else
    munlock(addr, len);
#endif
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
