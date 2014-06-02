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

#ifndef __util_h
#define __util_h

#include <MI.h>
#if defined (_MSC_VER)
# include <windows.h>
#else
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include "nwinsal.h"
#endif
#include <stdlib.h>
#include <time.h>

#if defined(__cplusplus)
# define BEGIN_EXTERNC extern "C" {
# define END_EXTERNC }
#else
# define BEGIN_EXTERNC
# define END_EXTERNC
#endif

BEGIN_EXTERNC

#if defined(_MSC_VER)
# define THREAD_API WINAPI
#else
# define THREAD_API /* empty */
#endif

typedef MI_Uint32 (THREAD_API *ThreadProc)(void* param);

typedef struct _Thread 
{
#if defined(_MSC_VER)
    HANDLE __impl;
#else
    pthread_t __impl;
#endif
}
Thread;

typedef struct _ThreadID
{
#if defined(_MSC_VER)
    DWORD __impl;
#else
    pthread_t __impl;
#endif
}
ThreadID;

_Return_type_success_(return == 0) int Thread_Create(
    _Out_ Thread* self,
    _In_ ThreadProc proc,
    _In_ void* param);

#if defined(_MSC_VER)
void Thread_Destroy(
    _Inout_ Thread* self);
#else
MI_INLINE void Thread_Destroy(
    _Inout_ Thread* self)
{
    /* Zero out so it will fail if called before join */
    memset(self, 0, sizeof(*self));
}
#endif

_Return_type_success_(return == 0) int Thread_Join(
    _In_ Thread* self,
    _Out_ MI_Uint32* returnValue);

#if defined(_MSC_VER)
MI_INLINE 
int Thread_Equal(
    _In_ ThreadID* thread1,
    _In_ ThreadID* thread2)
{
    return thread1->__impl == thread2->__impl;
}
#else
int Thread_Equal(
    _In_ ThreadID* thread1,
    _In_ ThreadID* thread2);
#endif

#if defined(_MSC_VER)
MI_INLINE 
ThreadID Thread_ID()
{
    ThreadID self;
    self.__impl = GetCurrentThreadId();
    return self;
}
#else
ThreadID Thread_ID();
#endif

MI_INLINE ThreadID Thread_ID_Null()
{
    ThreadID returnValue = {0};
    return returnValue;
}

void Thread_Exit(
    _In_ MI_Uint32 returnValue);


MI_INLINE void Sleep_Milliseconds(
    _In_ unsigned long milliseconds)
{
#if defined(_MSC_VER)
    Sleep((DWORD)milliseconds);
#else
    struct timespec ts;
    ts.tv_sec = (long)(milliseconds / 1000);
    ts.tv_nsec = (long)((milliseconds % 1000) * 1000 * 1000);
    nanosleep(&ts, NULL);
#endif
}

/*
 * Set seed for rand function
 */
MI_INLINE 
void SRAND()
{
#if defined(_MSC_VER)
    srand( (unsigned int)time( NULL ) );
#else
    srand( time( NULL ) );
#endif
}


/*
 * Callback function to trigger indication
 */
typedef MI_Uint32 (MI_CALL *CreatePostIndication)(
    _In_ void* callbackdata);

/*
 * Structure used to post indication
 */
typedef struct _SelfStruct
{
    void* context;
    MI_Boolean disabling;
    Thread thread;
    CreatePostIndication postindication;
    MI_Uint64 seqid;
}
SelfStruct;

/*
 * thread proc to trigger indication periodically until postindication return 0
 */
MI_Uint32 THREAD_API fireIndication(void* param);

#define CHECKR_POST_RETURN(ctx, r) \
    if (r != MI_RESULT_OK) \
    {\
        MI_Context_PostResult(ctx, r);\
        return 0;\
    }\

#define CHECKR_POST_RETURN_VOID(ctx, r) \
    if (r != MI_RESULT_OK) \
    {\
        MI_Context_PostResult(ctx, r);\
        return;\
    }\


/*
 * Defines Lock structure
 */
typedef struct _Lock
{
#if defined(_MSC_VER)
    CRITICAL_SECTION lock;
#else
    pthread_mutex_t lock;
#endif
}
Lock;

void Lock_Init(_Out_ Lock* self);
void Lock_Finalize(_In_ _Post_invalid_ Lock* self);

_Requires_lock_not_held_(self)
_Acquires_lock_(self)
void Lock_Acquire(_Inout_ Lock* self);
_Requires_lock_held_(self)
_Releases_lock_(self)
void Lock_Release(_Inout_ Lock* self);


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

_Success_(return == 0) int Sem_Init(
    _Out_ Sem* self,
    SemUserAccess userAccess,
    unsigned int count);

MI_INLINE void Sem_Destroy(
    _Inout_ Sem* self)
{
#if defined(_MSC_VER)
    CloseHandle(self->handle);
#else
    if (self->sem)
    {
        sem_close(self->sem);
        free(self->sem);
        self->sem = NULL;
    }
#endif
}

MI_INLINE int Sem_Wait(
    _Inout_ Sem* self)
{
#if defined(_MSC_VER)
    return WaitForSingleObject(self->handle, INFINITE) == WAIT_OBJECT_0 ? 0 : -1;
#else
    return sem_wait(self->sem) == 0 ? 0 : -1;
#endif
}

int Sem_Post(
    _Inout_ Sem* self,
    unsigned int count);


/*
 * Duplicate string
 */
MI_Result MI_StringDup(const MI_Char* src, _Outptr_result_z_ MI_Char** dest);

END_EXTERNC

#endif /* __util_h */
