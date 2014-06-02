#include "sem.h"
#include <stdio.h>
#include <pal/palcommon.h>
#include <pal/strings.h>

#ifndef __MSC_VER
# ifndef SEM_FAILED
#  define SEM_FAILED (sem_t*)-1
# endif
#endif

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
#if defined(USE_ALLOCATOR)
    if (cs.file && NitsShouldFault(cs, NitsAutomatic))
        return -1;
#else
    if (NitsShouldFault(cs, NitsAutomatic))
        return -1;
#endif

#if defined(_MSC_VER)

    self->handle = CreateSemaphoreEx(
        (userAccess == SEM_USER_ACCESS_ALLOW_ALL) ? &g_SecurityAttributes : NULL,
        count,
        0xFFFF,
        NULL,
        0,
        SEMAPHORE_ALL_ACCESS);

    if (!self->handle)
        return -1;

    return 0;

#else

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

    return sem_init(self->sem, 0, count) == 0 ? 0 : -1;

#endif
}

int Sem_Post(
    _Inout_ Sem* self,
    unsigned int count)
{
#if defined(_MSC_VER)
    ReleaseSemaphore(self->handle, count, NULL);
    return 0;
#else
    while (count--)
    {
        if (sem_post(self->sem) != 0)
            return -1;
    }

    return 0;
#endif
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

#if defined(_MSC_VER)
    PAL_UNUSED(flags);

    if (flags & NAMEDSEM_FLAG_CREATE)
    {
        self->handle = CreateSemaphoreEx(
            (userAccess == SEM_USER_ACCESS_ALLOW_ALL) ? &g_SecurityAttributes : NULL,
            count,
            0xFFFF,
            name,
            0,
            SEMAPHORE_ALL_ACCESS);
    }
    else
    {   
    	self->handle = OpenSemaphoreW(
            SEMAPHORE_ALL_ACCESS, 
            FALSE, 
            name);
    }
    
    if (!self->handle)
        return -1;

    return 0;

#else

    int tflags = 0;

    /*
        *  This is done since the sem_open is only defined for char * and does not take wchar_t
        */
    if (!name)
        return -1;
    
#if defined(CONFIG_ENABLE_WCHAR)
    StrWcslcpy(self->semname, name, PAL_MAX_PATH_SIZE);
#else
    Strlcpy(self->semname, name, PAL_MAX_PATH_SIZE);
#endif

    if (flags & NAMEDSEM_FLAG_CREATE)
        tflags |= O_CREAT;

    if (flags & NAMEDSEM_FLAG_EXCLUSIVE)
        tflags |= O_EXCL;

    self->sem = sem_open(self->semname, tflags, 0600, count);

    if (self->sem == SEM_FAILED)
        return -1;

    return 0;

#endif
}

void NamedSem_Close(
    _Inout_ NamedSem* self)
{
#if defined(_MSC_VER)
    CloseHandle(self->handle);
#else
    sem_close(self->sem);
#endif
}

int NamedSem_Post(
    _Inout_ NamedSem* self,
    unsigned int count)
{
#if defined(_MSC_VER)
    return ReleaseSemaphore(self->handle, count, NULL) ? 0 : -1;
#else

    while (count--)
    {
        if (sem_post(self->sem) != 0)
            return -1;
    }

    return 0;

#endif
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

