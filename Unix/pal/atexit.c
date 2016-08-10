/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "palcommon.h"

#if defined(USE_PAL_ATEXIT)
# include <stdlib.h>
# include <common.h>
# include <pthread.h>

typedef void (*AtexitFunc)();

/* Array of at-exit functions */
static AtexitFunc _funcs[PAL_ATEXIT_MAX];
static size_t _nfuncs;

/* Lock to synchronize access to _funcs and _nfuncs */

static pthread_mutex_t _lock = PTHREAD_MUTEX_INITIALIZER;

/* Used to detect re-entrancy errors */
static int _nesting;
static pthread_mutex_t _nestingLock = PTHREAD_MUTEX_INITIALIZER;

/* Non-zero once the system atexit() has been called */
static int _initialized;

static void _AtForkPrepare()
{
    /* Lock */
    pthread_mutex_lock(&_lock);
    pthread_mutex_lock(&_nestingLock);
}

static void _AtForkParent()
{
    /* Unlock */
    pthread_mutex_unlock(&_lock);
    pthread_mutex_unlock(&_nestingLock);
}

static void _AtForkChild()
{
    _initialized = 0;
    /* Unlock */
    pthread_mutex_unlock(&_lock);
    pthread_mutex_unlock(&_nestingLock);
}

static void _atexitFunc()
{
    PAL_AtexitCall();
}

int PAL_Atexit(void (*func)())
{
    /* Disallow if currently executing PAL_AtexitCall() */
    pthread_mutex_lock(&_nestingLock);
    {
        DEBUG_ASSERT(_nesting == 0);

        if (_nesting)
        {
            pthread_mutex_unlock(&_nestingLock);
            return -1;
        }
    }
    pthread_mutex_unlock(&_nestingLock);

    /* Install _atexitFunc() to be called on the first call */
    if (_initialized == 0)
    {
        pthread_mutex_lock(&_lock);
        {
            if (_initialized == 0)
            {
                if (atexit(_atexitFunc) != 0)
                {
                    pthread_mutex_unlock(&_lock);
                    return -1;
                }

                pthread_atfork(_AtForkPrepare, _AtForkParent, _AtForkChild);
                _initialized = 1;
            }
        }
        pthread_mutex_unlock(&_lock);
    }

    /* Add the function to the array of functions */
    pthread_mutex_lock(&_lock);
    {
        if (_nfuncs == PAL_ATEXIT_MAX)
        {
            pthread_mutex_unlock(&_lock);
            return -1;
        }

        _funcs[_nfuncs++] = func;
    }
    pthread_mutex_unlock(&_lock);

    return 0;
}

int PAL_AtexitCall()
{
    /* Disallow if currently executing PAL_AtexitCall() */
    pthread_mutex_lock(&_nestingLock);
    {
        DEBUG_ASSERT(_nesting == 0);

        if (_nesting)
        {
            pthread_mutex_unlock(&_nestingLock);
            return -1;
        }

        _nesting = 1;
    }
    pthread_mutex_unlock(&_nestingLock);

    /* Call all the functions and reset array to zero-size */
    pthread_mutex_lock(&_lock);
    {
        size_t i;

        for (i = 0; i < _nfuncs; i++)
            (*_funcs[i])();

        _nfuncs = 0;
    }
    pthread_mutex_unlock(&_lock);

    /* Reset _nesting to zero */
    pthread_mutex_lock(&_nestingLock);
    {
        _nesting = 0;
    }
    pthread_mutex_unlock(&_nestingLock);

    return 0;
}

#endif /* defined(USE_PAL_ATEXIT) */
