#include "shmem.h"
#include <stdio.h>
#include <pal/strings.h>

#ifdef _MSC_VER
SECURITY_DESCRIPTOR g_SecurityDescriptor = {
    SECURITY_DESCRIPTOR_REVISION,
    0,
    SE_DACL_PRESENT,
    NULL,
    NULL,
    NULL,
    NULL,
};

SECURITY_ATTRIBUTES g_SecurityAttributes = {
    sizeof(SECURITY_ATTRIBUTES),
    &g_SecurityDescriptor,
    FALSE,
};
#endif

int Shmem_Open(
    _Out_ Shmem* self,
    _In_z_ const PAL_Char *name,
    _In_ ShmemAccess access,
    ShmemUserAccess userAccess,
    _In_ size_t size)
{
#if defined(_MSC_VER)

    DWORD protect = 0;
    DWORD hi;
    DWORD lo;

    if (access == SHMEM_ACCESS_READWRITE)
        protect = PAGE_READWRITE;
    else if (access == SHMEM_ACCESS_READONLY)
        protect = PAGE_READONLY;
    else
    {
        self->handle = NULL;
        return -1;
    }

    hi = (DWORD)((0xFFFFFFFF00000000 & (PAL_Uint64)size) >> 32);
    lo = (DWORD)(0x00000000FFFFFFFF & (PAL_Uint64)size);

    self->handle = CreateFileMapping( 
        INVALID_HANDLE_VALUE,                                                         /* use paging file */
        (userAccess == SHMEM_USER_ACCESS_ALLOW_ALL) ? &g_SecurityAttributes : NULL,   /* default or allow all security attributes based on userAccess requested*/
        protect,                                                                      /* page access rights */
        hi,                                                                           /* size: high 32-bits */
        lo,                                                                           /* size: low 32-bits */
        name);                                                                        /* name of map object */
    
    return self->handle ? 0 : -1;

#else

    int oflag;

    /*
        *  This is done since the shm_open is only defined for char * and does not take wchar_t
        */
    if (!name)
        return -1;
        
#if defined(CONFIG_ENABLE_WCHAR)
    StrWcslcpy(self->shmname, name, PAL_MAX_PATH_SIZE);
#else
    Strlcpy(self->shmname, name, PAL_MAX_PATH_SIZE);
#endif

    /* Build the oflag */

    if (access == SHMEM_ACCESS_READWRITE)
        oflag = O_CREAT | O_RDWR;
    else if (access == SHMEM_ACCESS_READONLY)
        oflag = O_CREAT | O_RDONLY;
    else
        return -1;

    /* Open the shared memory segment */

    if ((self->shmid = shm_open(self->shmname, oflag, S_IRUSR | S_IWUSR)) == -1)
    {
        return -1;
    }

    if (ftruncate(self->shmid, size) != 0)
    {
        close(self->shmid);
        shm_unlink(self->shmname);
        return -1;
    }

    return 0;

#endif
}

void* Shmem_Map(
    _Inout_ Shmem* self,
    _In_ ShmemAccess access,
    _In_ ptrdiff_t offset,
    _In_ size_t size)
{
#if defined(_MSC_VER)

    DWORD desiredAccess = 0;
    DWORD lo;
    DWORD hi;
    void* ptr;

    if (access == SHMEM_ACCESS_READWRITE)
        desiredAccess = FILE_MAP_ALL_ACCESS;
    else if (access == SHMEM_ACCESS_READONLY)
        desiredAccess = FILE_MAP_READ;
    else
        return NULL;

    lo = (DWORD)(0x00000000FFFFFFFF & (PAL_Uint64)offset);
    hi = (DWORD)((0xFFFFFFFF00000000 & (PAL_Uint64)offset) >> 32);

    ptr = MapViewOfFile(
        self->handle,
        desiredAccess,
        hi, /* offset: high 32-bits */
        lo, /* offset: low 32-bits */
        size);

    return ptr;

#else

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

#endif
}
