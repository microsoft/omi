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

#ifndef _omi_thread_h
#define _omi_thread_h

#include "config.h"
//#include <string.h>
#include <common.h>

#if !defined(CONFIG_OS_WINDOWS)
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
#endif

BEGIN_EXTERNC

typedef void* (MI_CALL *ThreadProc)(void* param);

#if defined(CONFIG_OS_WINDOWS)
typedef MI_Uint32           ThreadHandle;
typedef CRITICAL_SECTION    Mutex; 
#else
typedef pthread_t           ThreadHandle;
typedef pthread_mutex_t     Mutex; 
#endif

/* creates a thread; returns a handle. 
    each successful 'create-thread' has to be followed by 'close-thread-handle' */
MI_Result Thread_Create(
    ThreadProc proc,
    void*  proc_param,
    ThreadHandle*  selfOut);

/* closes thread handle and frees related system resources;
    optionally, may wait for thread to complete */
MI_Result Thread_Destroy(
    ThreadHandle  self,
    MI_Boolean wait );

/* returns ID of the current thread */
ThreadHandle  ThreadSelf();

/* Mutex operations */
MI_INLINE MI_Result Mutex_Init( Mutex* self )
{
#if defined(CONFIG_OS_WINDOWS)
    InitializeCriticalSection(self);
#else
    if (0 != pthread_mutex_init(self, NULL))
        return MI_RESULT_FAILED;
#endif
    return MI_RESULT_OK;
}

MI_INLINE MI_Result Mutex_Destroy( Mutex* self )
{
#if defined(CONFIG_OS_WINDOWS)
    DeleteCriticalSection(self);
#else
    if (0 != pthread_mutex_destroy(self))
        return MI_RESULT_FAILED;
#endif
    return MI_RESULT_OK;
}

MI_INLINE void Mutex_Lock( Mutex* self )
{
#if defined(CONFIG_OS_WINDOWS)
    EnterCriticalSection(self);
#else
    pthread_mutex_lock(self);
#endif
}

MI_INLINE void Mutex_Unlock( Mutex* self )
{
#if defined(CONFIG_OS_WINDOWS)
    LeaveCriticalSection(self);
#else
    pthread_mutex_unlock(self);
#endif
}

MI_INLINE void Sleep_ms(MI_Uint64 ms_sec)
{
#if defined(CONFIG_OS_WINDOWS)
    Sleep((DWORD)ms_sec);
#else
    struct timespec rqtp;

    rqtp.tv_sec = (long)(ms_sec/1000);
    rqtp.tv_nsec = (long)((ms_sec%1000)*1000*1000);

    nanosleep(&rqtp, NULL);
#endif
}

END_EXTERNC

#endif /* _omi_thread_h */
