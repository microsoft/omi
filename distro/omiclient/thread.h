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

#ifndef _mi_thread_h
#define _mi_thread_h

#include <sock/thread.h>

MI_BEGIN_NAMESPACE

class Mutex
{
public:

    Mutex()
    {
        Mutex_Init(&m_self);
    }

    ~Mutex()
    {
        Mutex_Destroy(&m_self);
    }

    _Requires_lock_not_held_(&m_self)
    _Acquires_lock_(&m_self)
    void Lock()
    {
        Mutex_Lock(&m_self);
    }

    _Requires_lock_held_(&m_self)
    _Releases_lock_(&m_self)
    void Unlock()
    {
        Mutex_Unlock(&m_self);
    }

private:
    Mutex(const Mutex&);
    Mutex& operator=(const Mutex&);
    ::Mutex m_self;
};

class AutoMutex
{
public:

    AutoMutex(Mutex& m) : m_self(m)
    {
        m_self.Lock();
    }

    _Requires_lock_held_(m_self)
    _Releases_lock_(m_self)
    ~AutoMutex()
    {
        m_self.Unlock();
    }

private:
    AutoMutex();
    Mutex& operator=(const Mutex&);
    Mutex& m_self;
};

MI_END_NAMESPACE

#endif /* _mi_thread_h */
