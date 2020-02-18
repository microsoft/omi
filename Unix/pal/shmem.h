/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _pal_shmem_h
#define _pal_shmem_h


#include <stddef.h>
#include "palcommon.h"

#if defined(PAL_HAVE_POSIX)
# include <unistd.h>
# include <sys/mman.h>
# include <sys/shm.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
#endif

PAL_BEGIN_EXTERNC

typedef struct _Shmem 
{
    int shmid;
    char shmname[PAL_MAX_PATH_SIZE];
} 
Shmem;

typedef enum _ShmemUserAccess
{
    SHMEM_USER_ACCESS_DEFAULT = 1,
    SHMEM_USER_ACCESS_ALLOW_ALL = 2
} 
ShmemUserAccess;

typedef enum _ShmemAccess
{
    SHMEM_ACCESS_READONLY = 1,
    SHMEM_ACCESS_READWRITE = 2
}
ShmemAccess;

int Shmem_Open(
    _Out_ Shmem* self,
    _In_z_ const PAL_Char* name,
    _In_ ShmemAccess access,
    ShmemUserAccess userAccess,
    _In_ size_t size);

PAL_INLINE int Shmem_Close(
    _Inout_ Shmem* self)
{
    int status;

    status = close(self->shmid) == 0 ? 0 : -1;
    shm_unlink(self->shmname);
    return status;
}

void* Shmem_Map(
    _Inout_ Shmem* self,
    _In_ ShmemAccess access,
    _In_ ptrdiff_t offset,
    _In_ size_t size);

PAL_INLINE int Shmem_Unmap(
    _Inout_ Shmem* self,
    _In_ void* ptr,
    _In_ size_t size)
{
    PAL_UNUSED(self);
    PAL_UNUSED(ptr);
    PAL_UNUSED(size);

    return munmap(ptr, size) == 0 ? 0 : -1;
}

PAL_INLINE size_t Shmem_Granularity()
{
    return sysconf(_SC_PAGESIZE);
}

PAL_END_EXTERNC

#endif /* _pal_shmem_h */
