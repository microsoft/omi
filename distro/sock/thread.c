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

#include "thread.h"

#if defined(CONFIG_OS_WINDOWS)
# include <time.h>
#else
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <pthread.h>
#endif

/* creates a thread; returns a handle. 
    each successful 'create-thread' has to be followed by 'close-thread-handle' */
MI_Result Thread_Create(
    ThreadProc proc,
    void* proc_param,
    ThreadHandle* selfOut)
{
    MI_Result r;
#if defined(CONFIG_OS_WINDOWS)
    HANDLE h = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)proc, proc_param, 0, 0);

    if (h != NULL)
    {
        r = MI_RESULT_OK;
        *selfOut = GetThreadId(h);
        CloseHandle(h);
    }
    else
    {
        r = MI_RESULT_FAILED;
    }
#else
    r = MI_RESULT_OK;
    if (pthread_create(selfOut, NULL, proc, proc_param) != 0)
        r = MI_RESULT_FAILED;
#endif
    return r;
}

/* closes thread handle and frees related system resources;
    optionally, may wait for thread to complete */
MI_Result Thread_Destroy(
    ThreadHandle self,
    MI_Boolean wait)
{
    MI_Result r = MI_RESULT_OK;
#if defined(CONFIG_OS_WINDOWS)
    if (wait)
    {
        HANDLE h = OpenThread( SYNCHRONIZE, FALSE, self);
        if (h != NULL)
        {
            DWORD res = WaitForSingleObject(h, INFINITE);
            r = (WAIT_OBJECT_0 == res) ? MI_RESULT_OK : MI_RESULT_FAILED;
            CloseHandle(h);
        }
        else
            r = MI_RESULT_OK;
    }
#else
    if (wait)
    {
        pthread_join(self, NULL);
	}
    else
    {
        pthread_detach(self);
	}
#endif
    return r;
}

/* returns ID of the current thread */
ThreadHandle  ThreadSelf()
{
#if defined(CONFIG_OS_WINDOWS)
    return GetCurrentThreadId();
#else
    return pthread_self();
#endif
}

