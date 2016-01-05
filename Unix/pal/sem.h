#ifndef _pal_sem_h
#define _pal_sem_h

#include <nits/base/nits.h>

#if defined(PAL_HAVE_POSIX)
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <time.h>
# include <errno.h>
#endif

PAL_BEGIN_EXTERNC

/*
**==============================================================================
**
** Sem - semaphore
**
**==============================================================================
*/

typedef struct _Sem
{
#if defined(_MSC_VER)
    HANDLE handle;
#else
    sem_t* sem;
#endif
}
Sem;

typedef enum _SemUserAccess
{
    SEM_USER_ACCESS_DEFAULT = 1,
    SEM_USER_ACCESS_ALLOW_ALL = 2
}
SemUserAccess;

_Success_(return == 0) int Sem_Init_Injected(
    _Out_ Sem* self,
    SemUserAccess userAccess,
    unsigned int count,
    NitsCallSite cs);

#define Sem_Init(self, userAccess, count) Sem_Init_Injected(self, userAccess, count, NitsHere())

PAL_INLINE void Sem_Destroy(
    _Inout_ Sem* self)
{
#if defined(_MSC_VER)
    CloseHandle(self->handle);
#else
    if (self->sem)
    {
        sem_close(self->sem);
        PAL_Free(self->sem);
        self->sem = NULL;
    }
#endif
}

/* 0 succeeded, -1 -- failed */
PAL_INLINE int Sem_Wait(
    _Inout_ Sem* self)
{
#if defined(_MSC_VER)
    return WaitForSingleObject(self->handle, INFINITE) == WAIT_OBJECT_0 ? 0 : -1;
#else
    return sem_wait(self->sem) == 0 ? 0 : -1;
#endif
}

#if !defined(CONFIG_HAVE_SEM_TIMEDWAIT)
#include <pal/sleep.h>

int __TimedWaitHelper(sem_t* sem, int milliseconds);
#endif

/* 0 -- succeeded. 1 -- timed out, -1 -- failed */
PAL_INLINE int Sem_TimedWait(
    _Inout_ Sem* self,
    int milliseconds)
{
#if defined(_MSC_VER)
    return WaitForSingleObject(self->handle, milliseconds) == WAIT_OBJECT_0 ? 0 : -1;
#else
    int ret;
#if defined(CONFIG_HAVE_SEM_TIMEDWAIT)
    struct timespec temp = 
    {
        time(0) + milliseconds / 1000,
        milliseconds % 1000 * 1000000
    };
    ret =  sem_timedwait(self->sem, &temp);
#else
    ret =  __TimedWaitHelper(self->sem, milliseconds);
#endif
    if (ret == 0)
        return 0; /* Semaphore tripped */
    if (errno == ETIMEDOUT)
        return 1; /* Semaphore wait timed out */
    return -1; /* it just failed */
#endif
}

int Sem_Post(
    _Inout_ Sem* self,
    unsigned int count);

/*
**==============================================================================
**
** NamedSem - named semaphore
**
**==============================================================================
*/

#define NAMEDSEM_FLAG_CREATE 1
#define NAMEDSEM_FLAG_EXCLUSIVE 2

typedef struct _NamedSem
{
#if defined(_MSC_VER)
    HANDLE handle;
#else
    sem_t* sem;
    char semname[PAL_MAX_PATH_SIZE];
#endif
}
NamedSem;

_Return_type_success_(return == 0) int NamedSem_Open_Injected(
    _Out_ NamedSem* self,
    SemUserAccess userAccess,
    unsigned int count,
    _In_z_ const PAL_Char *name,
    unsigned long flags,
    NitsCallSite cs);

#define NamedSem_Open(self, userAccess, count, name, flags) NamedSem_Open_Injected(self, userAccess, count, name, flags, NitsHere())

void NamedSem_Close(
    _Inout_ NamedSem* self);

PAL_INLINE int NamedSem_Wait(
    _Inout_ NamedSem* self)
{
#if defined(_MSC_VER)
    return WaitForSingleObject(self->handle, INFINITE) == WAIT_OBJECT_0 ? 0 : -1;
#else
    return sem_wait(self->sem) == 0 ? 0 : -1;
#endif
}

/*
* To be called when the semaphore is no longer needed by any user of the semaphore
*/
PAL_INLINE void NamedSem_Destroy(
    _Inout_ NamedSem* self)
{
#if defined(_MSC_VER)
    
#else
    sem_unlink(self->semname);    
#endif
}

PAL_INLINE int NamedSem_TimedWait(
    _Inout_ NamedSem* self,
    int milliseconds)
{
#if defined(_MSC_VER)
    return WaitForSingleObject(self->handle, milliseconds) == WAIT_OBJECT_0 ? 0 : -1;
#elif defined(CONFIG_HAVE_SEM_TIMEDWAIT)
    struct timespec temp = 
    {
        time(0) + milliseconds / 1000,
        milliseconds % 1000 * 1000000
    };
    return sem_timedwait(self->sem, &temp) == 0 ? 0 : -1;
#else
    return __TimedWaitHelper(self->sem, milliseconds);
#endif
}

int NamedSem_Post(
    _Inout_ NamedSem* self,
    unsigned int count);

PAL_INLINE int NamedSem_GetValue(
    _Inout_ NamedSem* self,
    _Out_ int *value)
{
#if defined(_MSC_VER)
    *value = 0;
    return 0;
#else
    return sem_getvalue(self->sem, value) == 0 ? 0 : -1;
#endif
}

PAL_END_EXTERNC

#endif /* _pal_sem_h */
