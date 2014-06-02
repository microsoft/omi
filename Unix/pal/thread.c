#include "thread.h"
#include "atomic.h"
#include <pal/palcommon.h>

#if defined(PAL_HAVE_PTHREADS)
# include <sched.h>
#endif

/*
**==============================================================================
**
** Windows version
**
**==============================================================================
*/

#if defined(_MSC_VER)

#pragma warning(disable:4057)

typedef struct _ThreadWork 
{
    ThreadProc threadProcCallback;
    ThreadProc threadProcDestructor;
    void* threadProcParam;
    TP_WORK *tpWork;
    PAL_Uint32 returnCode;
    ptrdiff_t refcount;
}
ThreadWork;

VOID CALLBACK PAL_ThreadPoolCallback(
  _Inout_      PTP_CALLBACK_INSTANCE tpInstance,
  _In_         PVOID context,
  _Inout_      PTP_WORK tpWork
)
{
    ThreadWork* self = (ThreadWork*) context;
    HMODULE newHModule;

    GetModuleHandleExW(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS ,
        (LPCWSTR) self->threadProcCallback,
        &newHModule);

    CallbackMayRunLong(tpInstance);
    FreeLibraryWhenCallbackReturns(tpInstance, newHModule);

    self->returnCode = self->threadProcCallback(self->threadProcParam);

    if (self->threadProcDestructor)
        self->threadProcDestructor(self->threadProcParam);

    if (Atomic_Dec(&self->refcount) == 0)
    {
        CloseThreadpoolWork(tpWork);
        PAL_Free(self);
    }
}


_Return_type_success_(return == 0) int Thread_CreateDetached_Injected(
    _In_ ThreadProc threadProcCallback,
    _In_opt_ ThreadProc threadProcDestructor,
    _In_ void* threadProcParam,
    _In_ NitsCallSite cs)
{
    ThreadWork *thread = NULL;

#if !defined(USE_ALLOCATOR)
    if (NitsShouldFault(cs, NitsAutomatic))
        return -1;

    thread = PAL_Calloc(1, sizeof(ThreadWork));
#else
    thread = __PAL_Calloc(cs.file, cs.line, cs.function, 1, sizeof(ThreadWork));
#endif

    if (thread == NULL)
        return -1;

    thread->threadProcCallback = threadProcCallback;
    thread->threadProcDestructor = threadProcDestructor;
    thread->threadProcParam = threadProcParam;
    thread->refcount = 1;

    /* Create the thread */
    thread->tpWork = CreateThreadpoolWork(PAL_ThreadPoolCallback, thread, NULL);
    if (thread->tpWork == NULL)
    {
        PAL_Free(thread);
        return -1;
    }

    SubmitThreadpoolWork(thread->tpWork);

    return 0;
}

_Return_type_success_(return == 0) int Thread_CreateJoinable_Injected(
    _Out_ Thread* self,
    _In_ ThreadProc threadProcCallback,
    _In_opt_ ThreadProc threadProcDestructor,
    _In_ void* threadProcParam,
    NitsCallSite cs)
{
    ThreadWork *thread = NULL;

#if !defined(USE_ALLOCATOR)
    if (NitsShouldFault(cs, NitsAutomatic))
        return -1;

    thread = PAL_Calloc(1, sizeof(ThreadWork));
#else
    thread = __PAL_Calloc(
        cs.file, cs.line, cs.function, 1, sizeof(ThreadWork));
#endif

    if (thread == NULL)
        return -1;

    thread->threadProcCallback = threadProcCallback;
    thread->threadProcDestructor = threadProcDestructor;
    thread->threadProcParam = threadProcParam;
    thread->refcount = 2;

    /* Create the thread */
    thread->tpWork = CreateThreadpoolWork(PAL_ThreadPoolCallback, thread, NULL);
    if (thread->tpWork == NULL)
    {
        PAL_Free(thread);
        return -1;
    }

    self->__impl = (ptrdiff_t) thread;

    SubmitThreadpoolWork(thread->tpWork);
    
    return 0;
}

_Return_type_success_(return == 0) int Thread_Join(
    _In_ Thread* self,
    _Out_ PAL_Uint32* returnValue)
{
    ThreadWork *thread;
    if (self->__impl == 0)
    {
        *returnValue = 0;
        return 0;
    }

    thread = (ThreadWork*) self->__impl;

    /* Wait for thread to exit */
    WaitForThreadpoolWorkCallbacks(thread->tpWork,FALSE);

    /*  return code from called thread */
    *returnValue = thread->returnCode;

    return 0;
}

void Thread_Destroy(
    _Inout_ Thread* self)
{
    ThreadWork *thread;
    if (self->__impl == 0)
        return;
    thread = (ThreadWork*) self->__impl;

    if (Atomic_Dec(&thread->refcount) == 0)
    {
        CloseThreadpoolWork(thread->tpWork);
        PAL_Free(thread);
    }

    memset(self, 0, sizeof(*self));
}

void Thread_Yield()
{
    SwitchToThread();
}


#endif /* defined(_MSC_VER) */

/*
**==============================================================================
**
** POSIX threads version
**
**==============================================================================
*/

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
