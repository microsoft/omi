/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "sem.h"
#include <stdio.h>
#include <pal/palcommon.h>
#include <pal/strings.h>

#if defined(macos)
#include <semaphore.h>
#include <uuid/uuid.h>
#endif

# ifndef SEM_FAILED
#  define SEM_FAILED (sem_t*)-1
# endif

/*
**==============================================================================
**
** Sem
**
**==============================================================================
*/

_Success_(return == 0) int Sem_Init_Injected(
    _Out_ Sem* self,
    SemUserAccess userAccess,
    unsigned int count,
    NitsCallSite cs)
{
#if defined(macos)
    uuid_t uniqueUUID;
    uuid_string_t uuidString;
    uuid_string_t uuidStringNoDashes;
    size_t uuidIterator = 0;
    size_t NoDashesIterator = 0;
    char currentChar;
#endif

#if defined(USE_ALLOCATOR)
    if (cs.file && NitsShouldFault(cs, NitsAutomatic))
        return -1;
#else
    if (NitsShouldFault(cs, NitsAutomatic))
        return -1;
#endif

# if defined(USE_ALLOCATOR)
    if (!(self->sem = (sem_t*)__PAL_Calloc(
        cs.file, cs.line, cs.function, 1, sizeof(sem_t))))
    {
        return -1;
    }
# else
    if (!(self->sem = (sem_t*)PAL_Calloc(1, sizeof(sem_t))))
        return -1;
# endif

#if defined(macos)

    // The mac has a max name length of 30 characters.  Use a GUID, but truncate.  If the semaphore
    // exists, try again.
    errno = EEXIST;

    while (errno == EEXIST)
    {
        uuid_generate(uniqueUUID);

        // "unparse" the UUID into a string
        uuid_unparse(uniqueUUID, uuidString);

        // Remove the dashes and limit it to 30 characters
        uuidIterator = 0;
        NoDashesIterator = 0;
        currentChar = uuidString[uuidIterator++];

        while(currentChar != '\0' && uuidIterator < 30)
        {
            if (currentChar != '-')
            {
                uuidStringNoDashes[NoDashesIterator++] = currentChar;
            }
            
            currentChar = uuidString[uuidIterator++];
        }
        uuidStringNoDashes[NoDashesIterator] = '\0';


        // Create the semaphore as owner-write
        if ((self->sem = sem_open(uuidStringNoDashes, O_CREAT | O_EXCL, S_IWGRP | S_IWOTH, count)) != SEM_FAILED)
        {
            return 0;
        }
    }

    // We had a different failure
    return -1;
#else
    return sem_init(self->sem, 0, count) == 0 ? 0 : -1;
#endif
}

int Sem_Post(
    _Inout_ Sem* self,
    unsigned int count)
{
    while (count--)
    {
        if (sem_post(self->sem) != 0)
            return -1;
    }

    return 0;
}

/*
**==============================================================================
**
** NamedSem
**
**     (1) On Linux, sem_open("/erp", ...) creates "/dev/shm/sem.erp"
**
**==============================================================================
*/

_Return_type_success_(return == 0) int NamedSem_Open_Injected(
    _Out_ NamedSem* self,
    SemUserAccess userAccess,
    unsigned int count,
    _In_z_ const PAL_Char *name,
    unsigned long flags,
    NitsCallSite cs)
{
    PAL_UNUSED(flags);

    if (NitsShouldFault(cs, NitsAutomatic))
        return -1;

    int tflags = 0;

    /*
        *  This is done since the sem_open is only defined for char * and does not take wchar_t
        */
    if (!name)
        return -1;
    
    Strlcpy(self->semname, name, PAL_MAX_PATH_SIZE);

    if (flags & NAMEDSEM_FLAG_CREATE)
        tflags |= O_CREAT;

    if (flags & NAMEDSEM_FLAG_EXCLUSIVE)
        tflags |= O_EXCL;

    self->sem = sem_open(self->semname, tflags, 0600, count);

    if (self->sem == SEM_FAILED)
        return -1;

    return 0;
}

void NamedSem_Close(
    _Inout_ NamedSem* self)
{
    sem_close(self->sem);
}

int NamedSem_Post(
    _Inout_ NamedSem* self,
    unsigned int count)
{
    while (count--)
    {
        if (sem_post(self->sem) != 0)
            return -1;
    }

    return 0;
}

#if !defined(CONFIG_HAVE_SEM_TIMEDWAIT)
int __TimedWaitHelper(sem_t* sem, int milliseconds)
{
    PAL_Uint64 currentTimeUsec = 0;
    if (PAL_TRUE != PAL_Time(&currentTimeUsec))
        return -1;
    
    PAL_Uint64 finalTimeUsec = currentTimeUsec + (milliseconds * 1000);

    while(currentTimeUsec < finalTimeUsec)
    {
        if(sem_trywait(sem) == 0)
        {
            return 0;
        }
        else if(EAGAIN == errno)
        {
            Sleep_Milliseconds(1);
        }
        else
            return -1;

        if (PAL_TRUE != PAL_Time(&currentTimeUsec))
            return -1;
    }

    errno = ETIMEDOUT;
    
    return -1;
}
#endif

