#ifndef _pal_thread_h
#define _pal_thread_h

#include <string.h>
#include <nits/base/nits.h>

#if defined(PAL_HAVE_PTHREADS)
# include <pthread.h>
#endif

#if defined(linux)
# include <unistd.h>
# include <syscall.h>
#endif

PAL_BEGIN_EXTERNC

#if defined(_MSC_VER)
# define THREAD_API WINAPI
#else
# define THREAD_API /* empty */
#endif

typedef PAL_Uint32 (THREAD_API *ThreadProc)(void* param);

typedef struct _Thread 
{
#if defined(_MSC_VER)
    ptrdiff_t __impl;
#elif defined(PAL_HAVE_PTHREADS)
    pthread_t __impl;
#endif
}
Thread;

typedef struct _ThreadID
{
#if defined(_MSC_VER)
    DWORD __impl;
#elif defined(PAL_HAVE_PTHREADS)
    pthread_t __impl;
#endif
}
ThreadID;

_Return_type_success_(return == 0) int Thread_CreateDetached_Injected(
    _In_ ThreadProc threadProcCallback,
    _In_opt_ ThreadProc threadProcDestructor,
    _In_ void* threadProcParam,
    _In_ NitsCallSite cs);

#define Thread_CreateDetached(threadProcCallback, threadProcDestructor, threadProcParam) \
    Thread_CreateDetached_Injected(threadProcCallback, threadProcDestructor, threadProcParam, NitsHere())

_Return_type_success_(return == 0) int Thread_CreateJoinable_Injected(
    _Out_ Thread* self,
    _In_ ThreadProc threadProcCallback,
    _In_opt_ ThreadProc threadProcDestructor,
    _In_ void* threadProcParam,
    NitsCallSite cs);

#define Thread_CreateJoinable(self, threadProcCallback, threadProcDestructor, threadProcParam) Thread_CreateJoinable_Injected(self, threadProcCallback, threadProcDestructor, threadProcParam, NitsHere())

#if defined(_MSC_VER)
void Thread_Destroy(
    _Inout_ Thread* self);
#else
PAL_INLINE void Thread_Destroy(
    _Inout_ Thread* self)
{
    /* Zero out so it will fail if called before join */
    memset(self, 0, sizeof(*self));
}
#endif

_Return_type_success_(return == 0) int Thread_Join(
    _In_ Thread* self,
    _Out_ PAL_Uint32* returnValue);

#if defined(_MSC_VER)
PAL_INLINE 
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
PAL_INLINE 
ThreadID Thread_ID()
{
    ThreadID self;
    self.__impl = GetCurrentThreadId();
    return self;
}
#else
ThreadID Thread_ID();
#endif

PAL_INLINE
PAL_Uint64 Thread_TID()
{
#if defined(_MSC_VER)
    return (PAL_Uint64)GetCurrentThreadId();
#elif defined(CONFIG_OS_LINUX)
    return (PAL_Uint64)syscall(SYS_gettid);
#elif defined(macos)
    __uint64_t threadid;
    pthread_threadid_np(pthread_self(), &threadid);
    return threadid;
#else
    // Avoid using a cast here since pthread_self() may return a structure.
    // If so, we need to discover that and provide an alternative for that
    // platform.
    return pthread_self();
#endif
}

void Thread_Yield();

PAL_INLINE ThreadID Thread_ID_Null()
{
    ThreadID returnValue = {0};
    return returnValue;
}

PAL_END_EXTERNC

#endif /* _pal_thread_h */
