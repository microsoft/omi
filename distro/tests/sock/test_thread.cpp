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

#include <vector>
#include <cstdlib>
#include <ut/ut.h>
#include <sock/thread.h>
#include <base/result.h>

/* Include network headers */
#if defined(CONFIG_OS_WINDOWS)
#elif defined(CONFIG_POSIX)
# include <unistd.h>
# include <errno.h>
#endif

#if defined(_MSC_VER)
#undef BEGIN_EXTERNC
#undef END_EXTERNC
#define BEGIN_EXTERNC
#define END_EXTERNC
#endif

using namespace std;

static void setUp()
{
}

static void cleanup()
{
}

struct ThreadParam
{
    int args[2];
    bool thread_id_match;
    ThreadHandle t;
};

BEGIN_EXTERNC
static void* MI_CALL proc(void* param)
{
    ThreadParam* p = (ThreadParam*)param;

    ut::sleep_ms( 1 );
    // delay comparison
    p->thread_id_match = (ThreadSelf() == p->t);
    p->args[0] = 1;   // thread started
    ut::sleep_ms( 40 );
    p->args[1] = 1;  // done with sleep

    return 0;
}
END_EXTERNC

static void TestThreadCreateWait()
{
    ThreadParam param = {{0,0},false};

    UT_ASSERT(MI_RESULT_OK == Thread_Create(
        proc, &param, &param.t));

    UT_ASSERT(ThreadSelf() != param.t);

    for( int i = 0; !param.args[0]; i++ )
    {
        ut::sleep_ms( 1 );

        // give 1/2 of a sec to start
        UT_ASSERT( i < 500 );
    }

    // wait for completion and check that
    UT_ASSERT(MI_RESULT_OK == Thread_Destroy( param.t, MI_TRUE ));
    UT_ASSERT( 1 == param.args[1] );
    UT_ASSERT(param.thread_id_match);
}

static void TestThreadCreateDontWait()
{
    ThreadParam param = {{0,0},false};

    UT_ASSERT(MI_RESULT_OK == Thread_Create(
        proc, &param, &param.t));

    UT_ASSERT(ThreadSelf() != param.t);

    for( int i = 0; !param.args[0]; i++ )
    {
        ut::sleep_ms( 1 );

        // give 1/2 of a sec to start
        UT_ASSERT( i < 500 );
    }
    //UT_ASSERT( 0 == param.args[1] );

    // don't wait for completion and check that
    UT_ASSERT(MI_RESULT_OK == Thread_Destroy( param.t, MI_FALSE ));
    //UT_ASSERT( 0 == param.args[1] );


    // keep local variable alive until thread is done with it
    for( int i = 0; !param.args[1]; i++ )
    {
        ut::sleep_ms( 1 );

        // give 1/2 of a sec to finish
        UT_ASSERT( i < 500 );
    }
    UT_ASSERT(param.thread_id_match);
}

struct ThreadMutexParam
{
    int args[2];
    Mutex mt;
};

BEGIN_EXTERNC
static void* MI_CALL procMutext(void* param)
{
    ThreadMutexParam* p = (ThreadMutexParam*)param;

    ut::sleep_ms( 1 );

    for ( int i = 0; i < 10000; i++ )
    {
        Mutex_Lock(&p->mt);
        // args has to be identical if mutext works properly 
        UT_ASSERT(p->args[0] == p->args[1]);
        p->args[1] = rand();
        p->args[0] = p->args[1];

        Mutex_Unlock(&p->mt);
    }

    return 0;
}
END_EXTERNC

static void TestMutex()
{
    ThreadMutexParam param = {{0,0}};

    UT_ASSERT(MI_RESULT_OK == Mutex_Init(&param.mt));

    ThreadHandle t[2];

    UT_ASSERT(MI_RESULT_OK == Thread_Create(
        procMutext, &param, &t[0]));
    UT_ASSERT(MI_RESULT_OK == Thread_Create(
        procMutext, &param, &t[1]));

    // don't wait for completion and check that
    UT_ASSERT(MI_RESULT_OK == Thread_Destroy( t[0], MI_TRUE ));
    UT_ASSERT(MI_RESULT_OK == Thread_Destroy( t[1], MI_TRUE ));
    UT_ASSERT(MI_RESULT_OK == Mutex_Destroy(&param.mt));
}


static void RunTests()
{
    UT_TEST(TestThreadCreateWait);
    UT_TEST(TestThreadCreateDontWait);
    UT_TEST(TestMutex);
}

UT_ENTRY_POINT(RunTests);
