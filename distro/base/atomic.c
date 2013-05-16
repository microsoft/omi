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

#include <common.h>
#include "atomic.h"

#if defined(MI_DEFAULT_ATOMIC_REQUIRED)
#include <pthread.h>

static pthread_mutex_t s_mutex = PTHREAD_MUTEX_INITIALIZER;

// Atomically increment x.
EXTERNC void AtomicInc(AtomicInt* x)
{
    pthread_mutex_lock(&s_mutex);
    (*x) ++;
    pthread_mutex_unlock(&s_mutex);
}

// AtomicType decrement x and return true if it becomes zero.
EXTERNC unsigned char AtomicDec(AtomicInt* x)
{
    MI_Boolean res;

    pthread_mutex_lock(&s_mutex);
    (*x) --;
    res = (*x) == 0;
    pthread_mutex_unlock(&s_mutex);

    return res;
}

#endif

