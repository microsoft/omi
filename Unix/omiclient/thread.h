/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _mi_thread_h
#define _mi_thread_h

#include <pal/thread.h>

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
