/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "shmem.h"
#include <stdio.h>
#include <pal/strings.h>

int Shmem_Open(
    _Out_ Shmem* self,
    _In_z_ const PAL_Char *name,
    _In_ ShmemAccess access,
    ShmemUserAccess userAccess,
    _In_ size_t size)
{
    int oflag;

    /*
        *  This is done since the shm_open is only defined for char * and does not take wchar_t
        */
    if (!name)
        return -1;
        
    Strlcpy(self->shmname, name, PAL_MAX_PATH_SIZE);

    /* Build the oflag */

    if (access == SHMEM_ACCESS_READWRITE)
    {
        oflag = O_CREAT | O_RDWR;
    }
    else if (access == SHMEM_ACCESS_READONLY)
    {
        oflag = O_CREAT | O_RDONLY;
    }
    else
    {
        return -1;
    }

    /* Open the shared memory segment */
    if ((self->shmid = shm_open(self->shmname, oflag, S_IRUSR | S_IWUSR)) == -1)
    {
        return -1;
    }


#if !defined(is_macos)
    if (ftruncate(self->shmid, size) != 0)
    {
        close(self->shmid);
        shm_unlink(self->shmname);
        return -1;
    }
#else
    // On the mac, you can apparently only truncate on creation.
    struct stat currentMap;

    if (-1 != fstat(self->shmid, &currentMap) && currentMap.st_size == 0)
    {
        if (ftruncate(self->shmid, size) != 0)
        {
            close(self->shmid);
            shm_unlink(self->shmname);
            return -1;
        }
    }
#endif

    return 0;
}

void* Shmem_Map(
    _Inout_ Shmem* self,
    _In_ ShmemAccess access,
    _In_ ptrdiff_t offset,
    _In_ size_t size)
{
    int mprot;
    int mflags;
    void* ptr;

    if (access == SHMEM_ACCESS_READWRITE)
        mprot = PROT_READ | PROT_WRITE;
    else if (access == SHMEM_ACCESS_READONLY)
        mprot = PROT_READ;
    else
        return NULL;
        
    mflags = MAP_SHARED;
#if !defined(sun)
    mflags |= MAP_FILE;
#endif

    ptr = mmap(NULL, size, mprot, mflags, self->shmid, offset);

    if (ptr == MAP_FAILED)
        return NULL;

    return ptr;
}
