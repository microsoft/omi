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

#include "util.h"

/*
**==============================================================================
**
** Windows version
**
**==============================================================================
*/

#if defined(_MSC_VER)

#pragma warning(disable:4057)

_Return_type_success_(return == 0) int Thread_Create(
    _Out_ Thread* self,
    _In_ ThreadProc proc,
    _In_ void* param)
{
    /* Create the thread */

    self->__impl = CreateThread(NULL, 0, proc, param, 0, NULL);

    return self->__impl ? 0 : -1;
}

_Return_type_success_(return == 0) int Thread_Join(
    _In_ Thread* self,
    _Out_ MI_Uint32* returnValue)
{
    /* Wait for thread to exit */

    if (WaitForSingleObject(self->__impl, INFINITE) != WAIT_OBJECT_0)
    {
        return -1;
    }

    /* Get the return code */

    if (!GetExitCodeThread(self->__impl, returnValue))
    {
        return -1;
    }

    return 0;
}

void Thread_Exit(
    _In_ MI_Uint32 returnValue)
{
    ExitThread(returnValue);
}

#else /* defined(_MSC_VER) */

/*
**==============================================================================
**
** POSIX threads version
**
**==============================================================================
*/

typedef struct _ThreadData
{
    ThreadProc proc;
    void* param;
}
ThreadData;

static void* _Wrapper(void* param) 
{
    ThreadData* data = (ThreadData*)param;
    void* result;

    result = (void*)(ptrdiff_t)(*data->proc)(data->param);

    free(data);

    return result;
}

int Thread_Create(
    _Out_ Thread* self,
    _In_ ThreadProc proc,
    _In_ void* param)
{
    int r;

    /* Create the thread */
    {
        ThreadData* data = (ThreadData*)malloc(sizeof(ThreadData));

        if (!data)
            return -1;

        data->proc = proc;
        data->param = param;
        r = pthread_create(&self->__impl, NULL, _Wrapper, data);
    }

    return r == 0 ? 0 : -1;
}

void Thread_Exit(
    _In_ MI_Uint32 returnValue)
{
    pthread_exit((void*)(ptrdiff_t)returnValue);
}

int Thread_Join(
    _In_ Thread* self,
    _Out_ MI_Uint32* returnValue)
{
    int r;
    void* returnValuePtr;
    
    r = pthread_join(self->__impl, &returnValuePtr);

    if (r == 0 && returnValue)
    {
        *returnValue = (MI_Uint32)(ptrdiff_t)returnValuePtr;
        return 0;
    }

    return -1;
}

int Thread_Equal(
    _In_ ThreadID* thread1,
    _In_ ThreadID* thread2)
{
    return pthread_equal(thread1->__impl, thread2->__impl) == 0 ? 0 : -1;
}

ThreadID Thread_ID()
{
    ThreadID self;
    self.__impl = pthread_self();
    return self;
}



#endif /* defined(_MSC_VER) */



/*
**==============================================================================
**
** Thread proc to post indication periodically
**
**==============================================================================
*/
MI_Uint32 THREAD_API fireIndication(void* param)
{
    SelfStruct* self = (SelfStruct*)param;
    MI_Uint32 exitvalue = 1;

    if ( !self || !self->context || !self->postindication )
    {
        exitvalue = 0;
        goto EXIT;
    }

    /* initialize random seed: */
    SRAND();

    /* produce and post indication */
    while( MI_TRUE != self->disabling )
    {
        if ( 0 == self->postindication(self) )
            break;

        /* randomly sleep */
        Sleep_Milliseconds(rand() % 1000 + 500);
    }

EXIT:
    Thread_Exit(exitvalue);
    return exitvalue;
}

void Lock_Init(
    _Out_ Lock* self)
{
#if defined(_MSC_VER)
    InitializeCriticalSection(&self->lock);
#else
    pthread_mutex_t tmp = PTHREAD_MUTEX_INITIALIZER;
    memcpy(&self->lock, &tmp, sizeof(tmp));
#endif
}

void Lock_Finalize(_In_ _Post_invalid_ Lock* self)
{
#if defined(_MSC_VER)
    DeleteCriticalSection(&self->lock);
#else
    memset(&self->lock, 0, sizeof(self->lock));
#endif
}


_Requires_lock_not_held_(self)
_Acquires_lock_(self)
void Lock_Acquire(
    _Inout_ Lock* self)
{
#if defined(_MSC_VER)
    EnterCriticalSection(&self->lock);
#else
    pthread_mutex_lock(&self->lock);
#endif
}

_Requires_lock_held_(self)
_Releases_lock_(self)
void Lock_Release(
    _Inout_ Lock* self)
{
#if defined(_MSC_VER)
    LeaveCriticalSection(&self->lock);
#else
    pthread_mutex_unlock(&self->lock);
#endif
}


/*
**==============================================================================
**
** Sem
**
**==============================================================================
*/

#ifdef _MSC_VER
SECURITY_DESCRIPTOR g_utilSecurityDescriptor = {
    SECURITY_DESCRIPTOR_REVISION,
    0,
    SE_DACL_PRESENT,
    NULL,
    NULL,
    NULL,
    NULL,
};

SECURITY_ATTRIBUTES g_utilSecurityAttributes = {
    sizeof(SECURITY_ATTRIBUTES),
    &g_utilSecurityDescriptor,
    FALSE,
};
#endif

_Success_(return == 0) int Sem_Init(
    _Out_ Sem* self,
    SemUserAccess userAccess,
    unsigned int count)
{
#if defined(_MSC_VER)

    self->handle = CreateSemaphoreEx(
        (userAccess == SEM_USER_ACCESS_ALLOW_ALL) ? &g_utilSecurityAttributes : NULL,
        count,
        0xFFFF,
        NULL,
        0,
        SEMAPHORE_ALL_ACCESS);

    if (!self->handle)
        return -1;

    return 0;

#else

    if (!(self->sem = (sem_t*)calloc(1, sizeof(sem_t))))
        return -1;

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

MI_Result MI_StringDup(const MI_Char* src, _Outptr_result_z_ MI_Char** dest)
{
    MI_Result r = MI_RESULT_OK;
#if (MI_CHAR_TYPE == 1)
    *dest = strdup(src);
#else
# if defined(_MSC_VER)
    *dest = _wcsdup(src);
# else
    *dest = wcsdup(src);
# endif
#endif
    if (!(*dest))
        r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
    return r;
}

