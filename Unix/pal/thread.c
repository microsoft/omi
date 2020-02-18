/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "thread.h"
#include "atomic.h"
#include <pal/palcommon.h>

#if defined(PAL_HAVE_PTHREADS)
# include <sched.h>
#endif

#if defined(PAL_HAVE_PTHREADS)

typedef struct _ThreadData
{
    ThreadProc proc;
    ThreadProc destructor;
    void* param;
}
ThreadData;

static void* _Wrapper(void* param) 
{
    ThreadData* data = (ThreadData*)param;
    void* result;

    result = (void*)(ptrdiff_t)(*data->proc)(data->param);

    if (data->destructor)
        data->destructor(data->param);

    PAL_Free(data);

    return result;
}

int Thread_CreateDetached_Injected(
    _In_ ThreadProc threadProcCallback,
    _In_opt_ ThreadProc threadProcDestructor,
    _In_ void* threadProcParam,
    NitsCallSite cs)
{
    pthread_attr_t attr;
    pthread_t thread;
    int r;

#if !defined(USE_ALLOCATOR)
    if (NitsShouldFault(cs, NitsAutomatic))
        return -1;
#endif

    /* Create the thread attributes and set the detached flag */

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    /* Create the thread */
    {
#if !defined(USE_ALLOCATOR)
        ThreadData* data = (ThreadData*)PAL_Malloc(sizeof(ThreadData));
#else
        ThreadData* data = (ThreadData*)__PAL_Malloc( 
            cs.file, cs.line, cs.function, sizeof(ThreadData));
#endif


        if (!data)
        {
            pthread_attr_destroy(&attr);
            return -1;
        }

        data->proc = threadProcCallback;
        data->destructor = threadProcDestructor;
        data->param = threadProcParam;
        r = pthread_create(&thread, &attr, _Wrapper, data);
        if (r != 0)
        {
            PAL_Free(data);
        }
    }

    /* Destroy thread attributes */
    pthread_attr_destroy(&attr);

    return r == 0 ? 0 : -1;
}

int Thread_CreateJoinable_Injected(
    _Out_ Thread* self,
    _In_ ThreadProc threadProcCallback,
    _In_opt_ ThreadProc threadProcDestructor,
    _In_ void* threadProcParam,
    NitsCallSite cs)
{
    int r;

#if !defined(USE_ALLOCATOR)
    if (NitsShouldFault(cs, NitsAutomatic))
        return -1;
#endif

    /* Create the thread */
    {
#if !defined(USE_ALLOCATOR)
        ThreadData* data = (ThreadData*)PAL_Malloc(sizeof(ThreadData));
#else
        ThreadData* data = (ThreadData*)__PAL_Malloc(
            cs.file, cs.line, cs.function, sizeof(ThreadData));
#endif

        if (!data)
            return -1;

        data->proc = threadProcCallback;
        data->destructor = threadProcDestructor;
        data->param = threadProcParam;
        r = pthread_create(&self->__impl, NULL, _Wrapper, data);
        if (r != 0)
        {
            PAL_Free(data);
        }
    }

    return r == 0 ? 0 : -1;
}

int Thread_Join(
    _In_ Thread* self,
    _Out_ PAL_Uint32* returnValue)
{
    int r;
    void* returnValuePtr;
    
    r = pthread_join(self->__impl, &returnValuePtr);

    if (r == 0 && returnValue)
    {
        *returnValue = (PAL_Uint32)(ptrdiff_t)returnValuePtr;
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

void Thread_Yield()
{
    sched_yield();
}


#endif /* defined(PAL_HAVE_PTHREADS) */
