/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifdef _MSC_VER
#include <windows.h>
#endif

#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <ut/ut.h>
#include <pal/atomic.h>
#include <pal/thread.h>
#include <pal/tls.h>
#include <pal/sleep.h>
#include <pal/once.h>
#include <pal/lock.h>
#include <pal/cpu.h>
#include <pal/shlib.h>
#include <pal/slist.h>
#include <pal/sem.h>
#include <pal/shmem.h>
#include <pal/strings.h>
#include <pal/dir.h>
#include <pal/file.h>
#include <pal/hashmap.h>
#include <pal/format.h>

#if (!(defined(linux) || defined(macos)) && !defined(CONFIG_ENABLE_WCHAR))
#include "test_pal_strings.h"
#endif


using namespace std;

//==============================================================================
//
// TestSemSize()
//
//==============================================================================

NitsTest(TestSemSize)
{
    /* Validate that Sem fits in a ptrdiff_t. Otherwise, the semaphore pool in
     * CondLock will have problems. */
    NitsAssert(sizeof(Sem) <= sizeof(ptrdiff_t), PAL_T("Check Sem size"));
}
NitsEndTest

//==============================================================================
//
// TestPal32Bit()
//
//==============================================================================

#ifdef PAL_32BIT
NitsTest(TestPal32Bit)
{
    NitsAssert(sizeof(void*) == 4, PAL_T("Check 32-bit pointer size"));
}
NitsEndTest
#endif

//==============================================================================
//
// TestPal64Bit()
//
//==============================================================================

#ifdef PAL_64BIT
NitsTest(TestPal64Bit)
{
    NitsAssert(sizeof(void*) == 8, PAL_T("Check 64-bit pointer size"));
}
NitsEndTest
#endif

//==============================================================================
//
// TestAtomic()
//
//==============================================================================

NitsTest(TestAtomic)
    // Atomic_Inc()
    {
        volatile ptrdiff_t x = 0;
        ptrdiff_t r = Atomic_Inc(&x);
        TEST_ASSERT(r == 1);
        TEST_ASSERT(x == 1);
        r = Atomic_Inc(&x);
        TEST_ASSERT(r == 2);
        TEST_ASSERT(x == 2);
    }

    // Atomic_Dec()
    {
        volatile ptrdiff_t x = 2;
        ptrdiff_t r = Atomic_Dec(&x);
        TEST_ASSERT(r == 1);
        TEST_ASSERT(x == 1);
        r = Atomic_Dec(&x);
        TEST_ASSERT(r == 0);
        TEST_ASSERT(x == 0);
    }

    // Atomic_CompareAndSwap()
    {
        volatile ptrdiff_t x = 2;
        ptrdiff_t r = Atomic_CompareAndSwap(&x, 2, 10); 
        TEST_ASSERT(r == 2);
        TEST_ASSERT(x == 10);
    }

    // Atomic_CompareAndSwap()
    {
        volatile ptrdiff_t x = 2;
        ptrdiff_t r = Atomic_CompareAndSwap(&x, 500, 10); 
        TEST_ASSERT(r == 2);
        TEST_ASSERT(x == 2);
    }

    // Atomic_Swap()
    {
        volatile ptrdiff_t x = 100;
        ptrdiff_t r = Atomic_Swap(&x, 200);
        TEST_ASSERT(r == 100);
        TEST_ASSERT(x == 200);
    }
NitsEndTest

//==============================================================================
//
// TestThread()
//
//==============================================================================

NITS_EXTERN_C PAL_Uint32 THREAD_API TestThread1(void* arg)
{
    const char* name = (const char*)arg;
    TEST_ASSERT(strcmp(name, "TestThread1") == 0);

    return 1001;
}

NITS_EXTERN_C PAL_Uint32 THREAD_API TestThread2(void* arg)
{
    const char* name = (const char*)arg;
    TEST_ASSERT(strcmp(name, "TestThread2") == 0);

    return 1002;
}

NitsTest(TestThread)
    Thread t1;
    int t1_created = PAL_FALSE;

    t1_created = (Thread_CreateJoinable(&t1, TestThread1, NULL, (char*)"TestThread1") == 0);
    TEST_ASSERT(t1_created);

    Thread t2;
    int t2_created = PAL_FALSE;

    t2_created = (Thread_CreateJoinable(&t2, TestThread2, NULL, (char*)"TestThread2") == 0);
    TEST_ASSERT(t2_created);

    if (t1_created)
    {
        PAL_Uint32 arg1;
        Thread_Join(&t1, &arg1);
        Thread_Destroy(&t1);
        TEST_ASSERT(arg1 == 1001);
    }

    if (t2_created)
    {
        PAL_Uint32 arg2;
        Thread_Join(&t2, &arg2);
        Thread_Destroy(&t2);
        TEST_ASSERT(arg2 == 1002);
    }

NitsEndTest

//==============================================================================
//
// TestTLS()
//
//==============================================================================

NITS_EXTERN_C PAL_Uint32 THREAD_API TestTLS1(void* arg)
{
    TLS* tls = (TLS*)arg;

    for (ptrdiff_t i = 0; i < 100; i++)
    {
        TLS_Set(tls, i);
        Sleep_Milliseconds(5);
        ptrdiff_t x = TLS_Get(tls);
        TEST_ASSERT(x == i);
    }

    return 0;
}

NITS_EXTERN_C PAL_Uint32 THREAD_API TestTLS2(void* arg)
{
    TLS* tls = (TLS*)arg;

    for (ptrdiff_t i = 100; i < 200; i++)
    {
        TLS_Set(tls, i);
        Sleep_Milliseconds(5);
        ptrdiff_t x = TLS_Get(tls);
        TEST_ASSERT(x == i);
    }

    return 0;
}

NitsTest(TestTLS)
    Thread t1;
    int t1_created = PAL_FALSE;
    TLS tls;

    int r = TLS_Init(&tls);
    TEST_ASSERT(r == 0);
    if (r != 0)
        return;

    t1_created = (Thread_CreateJoinable(&t1, TestTLS1, NULL, &tls) == 0);
    TEST_ASSERT(t1_created);

    Thread t2;
    int t2_created = PAL_FALSE;

    t2_created = (Thread_CreateJoinable(&t2, TestTLS2, NULL, &tls) == 0);
    TEST_ASSERT(t2_created);

    Sleep_Milliseconds(10);

    if (t1_created)
    {
        PAL_Uint32 arg1;
        Thread_Join(&t1, &arg1);
        Thread_Destroy(&t1);
    }

    if (t2_created)
    {
        PAL_Uint32 arg2;
        Thread_Join(&t2, &arg2);
        Thread_Destroy(&t2);
    }

    TLS_Destroy(&tls);
NitsEndTest

//==============================================================================
//
// TestOnce()
//
//==============================================================================

typedef struct _TestOnce_Data
{
    Once once;
    int count;
} TestOnce_Data;

_Success_(return == 0) NITS_EXTERN_C int IncrementCount(_In_ void* arg, _Outptr_result_maybenull_ void** value)
{
    TestOnce_Data* data = (TestOnce_Data*) arg;
    data->count++;
    *value = NULL;
    return 0;
}

NITS_EXTERN_C PAL_Uint32 THREAD_API TestOnce1(void* arg)
{
    TestOnce_Data* data = (TestOnce_Data*) arg;

    for (ptrdiff_t i = 0; i < 100; i++)
    {
        Sleep_Milliseconds(5);
        Once_Invoke(&data->once, IncrementCount, data);
    }

    return 0;
}

NITS_EXTERN_C PAL_Uint32 THREAD_API TestOnce2(void* arg)
{
    TestOnce_Data* data = (TestOnce_Data*) arg;

    for (ptrdiff_t i = 0; i < 100; i++)
    {
        Sleep_Milliseconds(5);
        Once_Invoke(&data->once, IncrementCount, data);
    }

    return 0;
}

NitsTest(TestOnce)
    Thread t1;
    int t1_created = PAL_FALSE;
    TestOnce_Data data = { ONCE_INITIALIZER, 0 };

    t1_created = (Thread_CreateJoinable(&t1, TestOnce1, NULL, &data) == 0);
    TEST_ASSERT(t1_created);

    Thread t2;
    int t2_created = PAL_FALSE;

    t2_created = (Thread_CreateJoinable(&t2, TestOnce2, NULL, &data) == 0);
    TEST_ASSERT(t2_created);

    Sleep_Milliseconds(10);

    if (t1_created)
    {
        PAL_Uint32 arg1;
        Thread_Join(&t1, &arg1);
        Thread_Destroy(&t1);
    }

    if (t2_created)
    {
        PAL_Uint32 arg2;
        Thread_Join(&t2, &arg2);
        Thread_Destroy(&t2);
    }

    TEST_ASSERT(data.count == 1);
NitsEndTest

_Success_(return == 0) NITS_EXTERN_C int IncrementCount_FailIfCountIsZero(
    _In_ void* arg,
    _Outptr_result_maybenull_ void** value)
{
    TestOnce_Data* data = (TestOnce_Data*) arg;
    *value = NULL;
    if ((data->count++) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

NitsTest(TestOnce_ReturnValueTest)
    TestOnce_Data data = { ONCE_INITIALIZER, 0 };
    int ret;
    
    ret = Once_Invoke(&data.once, IncrementCount_FailIfCountIsZero, &data);
    NitsCompare(ret, 1, PAL_T("1st Once_Invoke should return 1"));
    NitsCompare(data.count, 1, PAL_T("1st Once_Invoke should set count=1"));

    ret = Once_Invoke(&data.once, IncrementCount_FailIfCountIsZero, &data);
    NitsCompare(ret, 0, PAL_T("2nd Once_Invoke should return 0"));
    NitsCompare(data.count, 2, PAL_T("2nd Once_Invoke should set count=2"));

    ret = Once_Invoke(&data.once, IncrementCount_FailIfCountIsZero, &data);
    NitsCompare(ret, 0, PAL_T("subsequent Once_Invoke(s) should keep returning 0"));
    NitsCompare(data.count, 2, PAL_T("subsequent Once_Invoke(s) should not increment count"));
NitsEndTest

_Success_(return == 0) NITS_EXTERN_C int IncrementCount_SlowFailIfCountIsZero(
    _In_ void* arg,
    _Outptr_result_maybenull_ void** value)
{
    TestOnce_Data* data = (TestOnce_Data*) arg;
    *value = NULL;
    Sleep_Milliseconds(1);
    if ((data->count++) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

NITS_EXTERN_C PAL_Uint32 THREAD_API TestOnce_FailureRaceTest_Thread(void* arg)
{
    TestOnce_Data* data = (TestOnce_Data*)arg;
    int ret;

    ret = Once_Invoke(&data->once, IncrementCount_SlowFailIfCountIsZero, data);
    NitsAssert((data->count == 1) || (data->count == 2), PAL_T("At most one failure and one success"));

    return (PAL_Uint32)ret;
}

NitsTest(TestOnce_FailureRaceTest)
    TestOnce_Data data = { ONCE_INITIALIZER, 0 };
    
    Thread t1;
    PAL_Uint32 t1_created = PAL_FALSE;
    PAL_Uint32 t1_result = 0;

    t1_created = (Thread_CreateJoinable(&t1, TestOnce_FailureRaceTest_Thread, NULL, &data) == 0);
    TEST_ASSERT(t1_created);

    Thread t2;
    PAL_Uint32 t2_created = PAL_FALSE;
    PAL_Uint32 t2_result = 0;

    t2_created = (Thread_CreateJoinable(&t2, TestOnce_FailureRaceTest_Thread, NULL, &data) == 0);
    TEST_ASSERT(t2_created);

    if (t1_created)
    {
        Thread_Join(&t1, &t1_result);
        Thread_Destroy(&t1);
    }

    if (t2_created)
    {
        Thread_Join(&t2, &t2_result);
        Thread_Destroy(&t2);
    }

    if (t1_created && t2_created)
    {
        NitsAssert( 
            ((t1_result == 0) && (t2_result == 1)) ||
            ((t2_result == 0) && (t1_result == 1)),
            PAL_T("One thread should fail and the other should succeed"));
    }
NitsEndTest

//==============================================================================
//
// TestMutex()
//
//==============================================================================

static Lock s_mutex = LOCK_INITIALIZER;

NITS_EXTERN_C PAL_Uint32 THREAD_API TestMutex1(void* arg)
{
    size_t* countPtr = (size_t*)arg;

    for (ptrdiff_t i = 0; i < 100; i++)
    {
        Lock_Acquire(&s_mutex);
        size_t count = *countPtr;
        Sleep_Milliseconds(1);
        count++;
        Sleep_Milliseconds(1);
        *countPtr = count;
        Lock_Release(&s_mutex);
    }

    return 0;
}

NITS_EXTERN_C PAL_Uint32 THREAD_API TestMutex2(void* arg)
{
    size_t* countPtr = (size_t*)arg;

    for (ptrdiff_t i = 0; i < 100; i++)
    {
        Lock_Acquire(&s_mutex);
        size_t count = *countPtr;
        Sleep_Milliseconds(1);
        count++;
        Sleep_Milliseconds(1);
        *countPtr = count;
        Lock_Release(&s_mutex);
    }

    return 0;
}

NitsTest(TestMutex)
{
    Thread t1;
    int t1_created = PAL_FALSE;
    size_t count = 0;

    t1_created = (Thread_CreateJoinable(&t1, TestMutex1, NULL, &count) == 0);
    TEST_ASSERT(t1_created);

    Thread t2;
    int t2_created = PAL_FALSE;

    t2_created = (Thread_CreateJoinable(&t2, TestMutex2, NULL, &count) == 0);
    TEST_ASSERT(t2_created);

    Sleep_Milliseconds(10);

    if (t1_created)
    {
        PAL_Uint32 arg1;
        Thread_Join(&t1, &arg1);
        Thread_Destroy(&t1);
    }

    if (t2_created)
    {
        PAL_Uint32 arg2;
        Thread_Join(&t2, &arg2);
        Thread_Destroy(&t2);
    }

    TEST_ASSERT(count == 200);
}
NitsEndTest

NITS_EXTERN_C PAL_Uint32 THREAD_API TestLockMiniStressWorker(void* param)
{
    static char buf1[10000];
    static char buf2[10000];

    Lock* lock = (Lock*)param;
    int i, j;
    for (i = -25; i < 50; i++)
    {
        for (j = -25; j < 50; j++)
        {
            Lock_Acquire(lock);
            if (i > 0) memcpy(buf1, buf2, i);
            Lock_Release(lock);
            if (j > 0) memcpy(buf1, buf2, j);
        }
    }
    return 0;
}

/*
 * This is a regression test for Win Blue Bugs #562349
 * (lock corruption leading to a hang)
 */
NitsTest(TestLockMiniStress)
{
    Lock lock;
    Thread t[10];
    int r[10];
    int i;

    Lock_Init(&lock);

    for (i = 0; i < 10; i++)
    {
        r[i] = Thread_CreateJoinable(
            t + i,
            TestLockMiniStressWorker,
            NULL, /* no thread destructor */
            &lock); /* no thread parameter */
        NitsCompare(r[i], 0, MI_T("Thread_CreateJoinable"));
    }

    for (i = 0; i < 10; i++)
    {
        if (r[i] == 0)
        {
            MI_Uint32 threadRet;
            MI_Uint32 joinRet;
            joinRet = Thread_Join(t + i, &threadRet);
            NitsCompare(joinRet, 0, MI_T("Thread_Join"));
            NitsCompare(threadRet, 0, MI_T("TestLockMiniStressWorker"));

            Thread_Destroy(t + i);
        }
    }
}
NitsEndTest

//==============================================================================
//
// TestReadWriteLock()
//
//==============================================================================

/* ATTN: broken */

#if 0

static ReadWriteLock s_readWriteLock = READWRITELOCK_INITIALIZER;
static unsigned long s_readWriteLockData = 0;

NITS_EXTERN_C PAL_Uint32 THREAD_API TestReadWriteLock_Writer(void* arg)
{
    for (ptrdiff_t i = 0; i < 100; i++)
    {
        ReadWriteLock_AcquireWrite(&s_readWriteLock);
        s_readWriteLockData = 1;
        Thread_Yield();
        Sleep_Milliseconds(10);
        s_readWriteLockData = 0;
        ReadWriteLock_ReleaseWrite(&s_readWriteLock);
    }

    return 0;
}

NITS_EXTERN_C PAL_Uint32 THREAD_API TestReadWriteLock_Reader(void* arg)
{
    for (ptrdiff_t i = 0; i < 100; i++)
    {
        ReadWriteLock_AcquireRead(&s_readWriteLock);
        TEST_ASSERT(s_readWriteLockData == 0);
        ReadWriteLock_ReleaseRead(&s_readWriteLock);
    }

    return 0;
}

NitsTest(TestReadWriteLock)
{
    Thread t1;

    if (Thread_CreateJoinable(&t1, TestReadWriteLock_Writer, NULL) != 0)
        TEST_ASSERT(false);

    Thread t2;

    if (Thread_CreateJoinable(&t2, TestReadWriteLock_Reader, NULL) != 0)
        TEST_ASSERT(false);

    Sleep_Milliseconds(10);

    PAL_Uint32 arg1;
    Thread_Join(&t1, &arg1);
    Thread_Destroy(&t1);

    PAL_Uint32 arg2;
    Thread_Join(&t2, &arg2);
    Thread_Destroy(&t2);
}
NitsEndTest

#endif

//==============================================================================
//
// TestCachedLock()
//
//==============================================================================

/* ATTN: broken */

#if 0

static CachedLock s_cachedLock;

NITS_EXTERN_C PAL_Uint32 THREAD_API TestCachedLock1(void* arg)
{
    size_t* countPtr = (size_t*)arg;

    for (ptrdiff_t i = 0; i < 100; i++)
    {
        CachedLock_AcquireWrite(&s_cachedLock);
        size_t count = *countPtr;
        Sleep_Milliseconds(1);
        count++;
        Sleep_Milliseconds(1);
        *countPtr = count;
        CachedLock_ReleaseWrite(&s_cachedLock);
    }

    return 0;
}

NITS_EXTERN_C PAL_Uint32 THREAD_API TestCachedLock2(void* arg)
{
    size_t* countPtr = (size_t*)arg;

    for (ptrdiff_t i = 0; i < 100; i++)
    {
        CachedLock_AcquireWrite(&s_cachedLock);
        size_t count = *countPtr;
        Sleep_Milliseconds(1);
        count++;
        Sleep_Milliseconds(1);
        *countPtr = count;
        CachedLock_ReleaseWrite(&s_cachedLock);
    }

    return 0;
}

NitsTest(TestCachedLock)
{
    Thread t1;
    size_t count = 0;

    CachedLock_Init(&s_cachedLock, 0);

    if (Thread_CreateJoinable(&t1, TestCachedLock1, &count) != 0)
        TEST_ASSERT(false);

    Thread t2;

    if (Thread_CreateJoinable(&t2, TestCachedLock2, &count) != 0)
        TEST_ASSERT(false);

    Sleep_Milliseconds(10);

    PAL_Uint32 arg1;
    Thread_Join(&t1, &arg1);
    Thread_Destroy(&t1);

    PAL_Uint32 arg2;
    Thread_Join(&t2, &arg2);
    Thread_Destroy(&t2);

    TEST_ASSERT(count == 200);

    CachedLock_Destroy(&s_cachedLock);
}
NitsEndTest

#endif

//==============================================================================
//
// TestRecursiveLock()
//
//==============================================================================

static RecursiveLock s_recursiveLock = RECURSIVELOCK_INITIALIZER;

NITS_EXTERN_C PAL_Uint32 THREAD_API TestRecursiveLock1(void* arg)
{
    size_t* countPtr = (size_t*)arg;

    for (ptrdiff_t i = 0; i < 100; i++)
    {
        RecursiveLock_Acquire(&s_recursiveLock);
        size_t count = *countPtr;
        Sleep_Milliseconds(1);
        count++;
        Sleep_Milliseconds(1);
        *countPtr = count;
        RecursiveLock_Release(&s_recursiveLock);
    }

    return 0;
}

NITS_EXTERN_C PAL_Uint32 THREAD_API TestRecursiveLock2(void* arg)
{
    size_t* countPtr = (size_t*)arg;

    for (ptrdiff_t i = 0; i < 100; i++)
    {
        RecursiveLock_Acquire(&s_recursiveLock);
        size_t count = *countPtr;
        Sleep_Milliseconds(1);
        count++;
        Sleep_Milliseconds(1);
        *countPtr = count;
        RecursiveLock_Release(&s_recursiveLock);
    }

    return 0;
}

NitsTest(TestRecursiveLock)
{
    Thread t1;
    int t1_created = PAL_FALSE;
    size_t count = 0;

    t1_created = (Thread_CreateJoinable(&t1, TestRecursiveLock1, NULL, &count) == 0);
    TEST_ASSERT(t1_created);

    Thread t2;
    int t2_created = PAL_FALSE;

    t2_created = (Thread_CreateJoinable(&t2, TestRecursiveLock2, NULL, &count) == 0);
    TEST_ASSERT(t2_created);

    Sleep_Milliseconds(10);

    if (t1_created)
    {
        PAL_Uint32 arg1;
        Thread_Join(&t1, &arg1);
        Thread_Destroy(&t1);
    }

    if (t2_created)
    {
        PAL_Uint32 arg2;
        Thread_Join(&t2, &arg2);
        Thread_Destroy(&t2);
    }

    TEST_ASSERT(count == 200);
}
NitsEndTest

//==============================================================================
//
// TestCond()
//
//==============================================================================

/* ATTN: broken */

#if 0

class Queue
{
public:

    Queue()
    {
        Lock_Init(&m_lock);
        m_size = 0;
        m_notEmpty = 0xDEADBEEF;
        m_notFull = 0xF00DFACE;
    }

    ~Queue()
    {
    }

    void Put(unsigned int x)
    {
        // Wait for size != SIZE (not full):

        for (;;)
        {
            CondLock_Wait(m_notFull, &m_size, SIZE, SPINCOUNT);

            Lock_Acquire(&m_lock);

            if (m_size == SIZE)
            {
                Lock_Release(&m_lock);
                continue;
            }
            else
            {
                m_data.push_back(x);
                m_size++;
                Lock_Release(&m_lock);
                CondLock_Signal(m_notEmpty);
                break;
            }
        }
    }

    void Get(unsigned int& x)
    {
        // Wait for size != 0 (not empty):

        for (;;)
        {
            CondLock_Wait(m_notEmpty, &m_size, 0, SPINCOUNT);

            Lock_Acquire(&m_lock);

            if (m_size == 0)
            {
                Lock_Release(&m_lock);
                continue;
            }
            else
            {
                x = m_data.front();
                m_data.pop_front();
                m_size--;
                Lock_Release(&m_lock);
                CondLock_Signal(m_notFull);
                break;
            }
        }
    }

private:

    enum { SIZE = 100 };
    Lock m_lock;
    ptrdiff_t m_notEmpty;
    ptrdiff_t m_notFull;
    ptrdiff_t m_size;
    static const size_t SPINCOUNT;
    list<unsigned int> m_data;
};

const size_t Queue::SPINCOUNT = CONDLOCK_DEFAULT_SPINCOUNT;

static const size_t NREADERS = 20;
static const size_t NPUTS = 10000;

static ptrdiff_t s_sum = 0;
static Lock s_sumLock = 0;

NITS_EXTERN_C PAL_Uint32 THREAD_API TestCondReader(void* arg)
{
    Queue* queue = (Queue*)arg;

    for (;;)
    {
        unsigned int x;

        queue->Get(x);

        if (x == 0)
            break;

        Lock_Acquire(&s_sumLock);
        s_sum += x;
        Lock_Release(&s_sumLock);
    }

    printf("TestCondReader() done\n");

    return 0;
}

NITS_EXTERN_C PAL_Uint32 THREAD_API TestCondWriter(void* arg)
{
    Queue* queue = (Queue*)arg;

    for (unsigned int i = 1; i <= NPUTS; i++)
    {
        queue->Put(i);
    }

    printf("TestCondWriter() closing down readers\n");

    for (size_t i = 0; i < NREADERS; i++)
    {
        queue->Put(0);
    }

    printf("TestCondWriter() done\n");

    return 0;
}

NitsTest(TestCond)
{
    // Create the queue:
    
    Queue queue;


    // Calculate the expected sum:

    static ptrdiff_t expectedSum = 0;

    for (unsigned int i = 1; i <= NPUTS; i++)
        expectedSum += i;
    
    // Create writer thread:
    
    Thread t1;

    if (Thread_CreateJoinable(&t1, TestCondWriter, &queue) != 0)
        TEST_ASSERT(false);

    // Create reader threads:

    vector<Thread> readers;

    for (size_t i = 0; i < NREADERS; i++)
    {
        Thread t;

        if (Thread_CreateJoinable(&t, TestCondReader, &queue) != 0)
            TEST_ASSERT(false);

        readers.push_back(t);
    }

    // Join with writer:

    PAL_Uint32 arg1;
    Thread_Join(&t1, &arg1);
    Thread_Destroy(&t1);

    // Join with readers:

    for (size_t i = 0; i < NREADERS; i++)
    {
        PAL_Uint32 arg2;
        Thread_Join(&readers[i], &arg2);
        Thread_Destroy(&readers[i]);
    }

    // Verify that the sum is right:
    
    TEST_ASSERT(s_sum == expectedSum);
}
NitsEndTest

#endif

//==============================================================================
//
// TestCPU()
//
//==============================================================================

NitsTest(TestCPU)
    int count = CPU_GetCount();
    TEST_ASSERT(count >= 1);

    int current = CPU_GetCurrent();
    TEST_ASSERT(current >= 0);

    if (count == 1)
        TEST_ASSERT(current == 0);

    PAL_Datetime now;
    int result = CPU_GetLocalTimestamp(&now);
    TEST_ASSERT(result == 0);
    TEST_ASSERT(now.isTimestamp == PAL_TRUE);
    TEST_ASSERT(now.u.timestamp.year >= 2012);
    TEST_ASSERT(now.u.timestamp.month >= 1);
    TEST_ASSERT(now.u.timestamp.month <= 12);
    TEST_ASSERT(now.u.timestamp.day <= 31);
    TEST_ASSERT(now.u.timestamp.day >= 1);
NitsEndTest

//==============================================================================
//
// TestShlib()
//
//==============================================================================

/* ATTN: fix this test */

#if 0
static void TestShlib()
{
// ATTN:
    Shlib* shlib = Shlib_Open(CONFIG_LIBDIR "/libtestshlib.so");
    TEST_ASSERT(shlib != NULL);

    typedef const char* (*Function)();
    Function func = (Function)Shlib_Sym(shlib, "TestShlib");
    TEST_ASSERT(func != NULL);

    const char* str = (*func)();
    TEST_ASSERT(strcmp(str, "TestShlib") == 0);
}
#endif

//==============================================================================
//
// TestSList()
//
//==============================================================================

static const int NINTEGERS = 10000;

struct IntegerEntry
{
    SListEntry entry;
    int x;
};

NITS_EXTERN_C PAL_Uint32 THREAD_API TestListPush(void* arg)
{
    SListHead* head = (SListHead*)arg;

    for (int i = 0; i < NINTEGERS; i++)
    {
        IntegerEntry* p = new IntegerEntry;
        p->x = i;
        SList_PushAtomic(head, &p->entry);
    }

    return 0;
}

NITS_EXTERN_C PAL_Uint32 THREAD_API TestListPop(void* arg)
{
    SListHead* head = (SListHead*)arg;

    for (int i = 0; i < NINTEGERS; i++)
    {
        IntegerEntry* p = (IntegerEntry*)SList_PopAtomic(head);
        TEST_ASSERT(p != NULL);
        if (p)
            delete p;
    }

    return 0;
}

NitsTest(TestSList)
    /* Test push */
    {
        Thread t1;
        int t1_created = PAL_FALSE;
        SListHead head;

        SList_Init(&head);

        t1_created = (Thread_CreateJoinable(&t1, TestListPush, NULL, &head) == 0);
        TEST_ASSERT(t1_created);

        Thread t2;
        int t2_created = PAL_FALSE;

        t2_created = (Thread_CreateJoinable(&t2, TestListPush, NULL, &head) == 0);
        TEST_ASSERT(t2_created);

        if (t1_created)
        {
            PAL_Uint32 arg1;
            Thread_Join(&t1, &arg1);
            Thread_Destroy(&t1);
        }

        if (t2_created)
        {
            PAL_Uint32 arg2;
            Thread_Join(&t2, &arg2);
            Thread_Destroy(&t2);
        }

        // Check the list:
        
        int expect = 0;

        for (int i = 0; i < NINTEGERS; i++)
        {
            expect += i;
            expect += i;
        }

        SListEntry* first = SList_FlushAtomic(&head);

        int total = 0;
        size_t size = 0;

        for (SListEntry* p = first; p; )
        {
            SListEntry* next = SList_Next(p);
            IntegerEntry* entry = (IntegerEntry*)p;
            total += entry->x;
            delete entry;
            p = next;
            size++;
        }

        TEST_ASSERT(size == 2 * NINTEGERS);
        TEST_ASSERT(expect == total);
    }

    /* Test pop */
    {
        SListHead head;
        SList_Init(&head);

        // Push phase:
        {
            Thread t1;
            int t1_created = PAL_FALSE;

            t1_created = (Thread_CreateJoinable(&t1, TestListPush, NULL, &head) == 0);
            TEST_ASSERT(t1_created);

            Thread t2;
            int t2_created = PAL_FALSE;

            t2_created = (Thread_CreateJoinable(&t2, TestListPush, NULL, &head) == 0);
            TEST_ASSERT(t2_created);

            if (t1_created)
            {
                PAL_Uint32 arg1;
                Thread_Join(&t1, &arg1);
                Thread_Destroy(&t1);
            }

            if (t2_created)
            {
                PAL_Uint32 arg2;
                Thread_Join(&t2, &arg2);
                Thread_Destroy(&t2);
            }
        }

        // Pop phase:
        {
            Thread t1;
            int t1_created = PAL_FALSE;

            t1_created = (Thread_CreateJoinable(&t1, TestListPop, NULL, &head) == 0);
            TEST_ASSERT(t1_created);

            Thread t2;
            int t2_created = PAL_FALSE;

            t2_created = (Thread_CreateJoinable(&t2, TestListPop, NULL, &head) == 0);
            TEST_ASSERT(t2_created);

            if (t1_created)
            {
                PAL_Uint32 arg1;
                Thread_Join(&t1, &arg1);
                Thread_Destroy(&t1);
            }

            if (t2_created)
            {
                PAL_Uint32 arg2;
                Thread_Join(&t2, &arg2);
                Thread_Destroy(&t2);
            }
        }

        // Check that the list is empty:
        SListEntry* first = SList_FlushAtomic(&head);
        TEST_ASSERT(first == NULL);
    }
NitsEndTest

//==============================================================================
//
// TestSem()
//
//==============================================================================

struct TestSemData
{
    Sem sem;
    unsigned int sum;
    unsigned int count;
};

NITS_EXTERN_C PAL_Uint32 THREAD_API TestSemThread(void* arg)
{
    TestSemData* data = (TestSemData*)arg;

    for (unsigned int i = 0; i < data->count; i++)
    {
        Sem_Wait(&data->sem);
        size_t tmp = data->sum;
        Sleep_Milliseconds(1);
        tmp++;
        Sleep_Milliseconds(1);
        data->sum = (unsigned int)tmp;
        Sleep_Milliseconds(1);
        Sem_Post(&data->sem, 1);
    }

    return 0;
}

NitsTest(TestSem)
{
    Thread t1;
    int t1_created = PAL_FALSE;
    TestSemData data;

    data.sum = 0;
    data.count = 0;

    int r = Sem_Init(&data.sem, SEM_USER_ACCESS_DEFAULT, 1);
    if(!TEST_ASSERT(r == 0))
        NitsReturn;

    t1_created = (Thread_CreateJoinable(&t1, TestSemThread, NULL, &data) == 0);
    TEST_ASSERT(t1_created);

    Thread t2;
    int t2_created = PAL_FALSE;

    t2_created = (Thread_CreateJoinable(&t2, TestSemThread, NULL, &data) == 0);
    TEST_ASSERT(t2_created);

    if (t1_created)
    {
        PAL_Uint32 arg1;
        Thread_Join(&t1, &arg1);
        Thread_Destroy(&t1);
    }

    if (t2_created)
    {
        PAL_Uint32 arg2;
        Thread_Join(&t2, &arg2);
        Thread_Destroy(&t2);
    }

    Sem_Destroy(&data.sem);

    // Check the result:
    
    TEST_ASSERT(data.sum == 2 * data.count);
}
NitsEndTest

//==============================================================================
//
// TestNamedSem()
//
//==============================================================================


#if defined(_MSC_VER)
# define SEMAPHORE_NAME PAL_T("/PALTestSem")
#else
# define SEMAPHORE_NAME PAL_T(CONFIG_SHMNAMELOCALPREFIX) PAL_T("PALTestSem")
#endif

struct TestNamedSemData
{
    unsigned int sum;
    unsigned int count;
};

NITS_EXTERN_C PAL_Uint32 THREAD_API TestNamedSemThread(void* arg)
{
    TestNamedSemData* data = (TestNamedSemData*)arg;

    // Open or create the name semaphore:

    NamedSem sem;
    const PAL_Char *semaphoreName = SEMAPHORE_NAME;

    int r = NamedSem_Open(&sem, SEM_USER_ACCESS_DEFAULT, 1, semaphoreName, NAMEDSEM_FLAG_CREATE);

    TEST_ASSERT(r == 0);
    if (r != 0)
        return 0;

    for (unsigned int i = 0; i < data->count; i++)
    {
        NamedSem_Wait(&sem);
        size_t tmp = data->sum;
        Sleep_Milliseconds(1);
        tmp++;
        Sleep_Milliseconds(1);
        data->sum = (unsigned int)tmp;
        Sleep_Milliseconds(1);
        NamedSem_Post(&sem, 1);
    }

    NamedSem_Close(&sem);
    NamedSem_Destroy(&sem);
    return 0;
}

NitsTest(TestNamedSem)
{
    Thread t1;
    int t1_created = PAL_FALSE;
    TestNamedSemData data;

    data.sum = 0;
    data.count = 0;

    t1_created = (Thread_CreateJoinable(&t1, TestNamedSemThread, NULL, &data) == 0);
    TEST_ASSERT(t1_created);

    Thread t2;
    int t2_created = PAL_FALSE;

    t2_created = (Thread_CreateJoinable(&t2, TestNamedSemThread, NULL, &data) == 0);
    TEST_ASSERT(t2_created);

    if (t1_created)
    {
        PAL_Uint32 arg1;
        Thread_Join(&t1, &arg1);
        Thread_Destroy(&t1);
    }

    if (t2_created)
    {
        PAL_Uint32 arg2;
        Thread_Join(&t2, &arg2);
        Thread_Destroy(&t2);
    }

    // Check the result:
    
    TEST_ASSERT(data.sum == 2 * data.count);
}
NitsEndTest

//==============================================================================
//
// TestShmem()
//
//==============================================================================
 

#if defined(_MSC_VER)
# define SHMEM_NAME PAL_T("/PALTestShmem")
#else
# define SHMEM_NAME PAL_T(CONFIG_SHMNAMELOCALPREFIX PAL_T("PALTestShmem"))
#endif

typedef struct _TestShmemData
{
    unsigned long sum;
}
TestShmemData;

NITS_EXTERN_C PAL_Uint32 THREAD_API TestShmemThread(void* arg)
{
    TestShmemData* data = (TestShmemData*)arg;
    Shmem shmem;

    const PAL_Char *shmemName = SHMEM_NAME;

    // Get the size size of the shared memory:

    size_t size = 16 * Shmem_Granularity();

    // Open the shared memory segment:

    int r = Shmem_Open(&shmem, 
        shmemName, 
        SHMEM_ACCESS_READWRITE, 
        SHMEM_USER_ACCESS_DEFAULT,
        size);

    TEST_ASSERT(r == 0);

    // Map a shared memory region:

    unsigned char* p = (unsigned char*)Shmem_Map(
        &shmem, 
        SHMEM_ACCESS_READWRITE, 
        0,
        size);

    TEST_ASSERT(p != NULL);

    // Write some data to the shared memory:

    for (size_t i = 0; i < size; i++)
    {
        TEST_ASSERT(p[i] == i % 256);
        data->sum += p[i];
        p[i] = 0xDD;
    }

    // Unmap the shared memory:

    Shmem_Unmap(&shmem, p, size);

    // Close the shared memory:

    Shmem_Close(&shmem);

    return 0;
}

NitsTest(TestShmem)
{
    Thread t;
    int t_created = PAL_FALSE;
    Shmem shmem;
    const PAL_Char *shmemName = SHMEM_NAME;

    size_t size = 16 * Shmem_Granularity();

    // Open the shared memory segment:

    int r = Shmem_Open(&shmem, 
        shmemName, 
        SHMEM_ACCESS_READWRITE, 
        SHMEM_USER_ACCESS_DEFAULT,        
        size);

    TEST_ASSERT(r == 0);

    // Map a shared memory region:

    unsigned char* p = (unsigned char*)Shmem_Map(
        &shmem, 
        SHMEM_ACCESS_READWRITE, 
        0,
        size);

    TEST_ASSERT(p != NULL);

    memset(p, 0xAA, size);

    // Write some data to the shared memory:

    unsigned long sum = 0;

    for (size_t i = 0; i < size; i++)
    {
        p[i] = i % 256;
        sum += p[i];
    }

    // Unmap the shared memory:
    Shmem_Unmap(&shmem, p, size);

    // Create the other thread:
    TestShmemData data;
    data.sum = 0;

    t_created = (Thread_CreateJoinable(&t, TestShmemThread, NULL, &data) == 0);
    TEST_ASSERT(t_created);

    // Join with the other thread:

    if (t_created)
    {
        PAL_Uint32 arg1;
        Thread_Join(&t, &arg1);
        Thread_Destroy(&t);
    }

    p = (unsigned char*)Shmem_Map(
        &shmem, 
        SHMEM_ACCESS_READWRITE, 
        0,
        size);

    TEST_ASSERT(p != NULL);

    // Compare the sums:

    TEST_ASSERT(data.sum == sum);

    // The other thread should have cleared the memory (to 0xDD's):

    for (size_t i = 0; i < size; i++)
    {
        TEST_ASSERT(p[i] == 0xDD);
    }

    // Unmap the shared memory:
    Shmem_Unmap(&shmem, p, size);

    // Close the shared memory:
    Shmem_Close(&shmem);
}
NitsEndTest

//==============================================================================
//
// TestStrings()
//
//==============================================================================

#define FUNCTION TestStringsStr
#define CHAR char
#define STRCMP Strcmp
#define STRLCPY Strlcpy
#define STRLCAT Strlcat
#define LIT(STR) STR
#include "TestStringsAux.h"
#undef FUNCTION
#undef CHAR
#undef STRCMP
#undef STRLCPY
#undef STRLCAT
#undef LIT

#define FUNCTION TestStringsWcs
#define CHAR wchar_t
#define STRCMP Wcscmp
#define STRLCPY Wcslcpy
#define STRLCAT Wcslcat
#define LIT(STR) L##STR
#include "TestStringsAux.h"
#undef FUNCTION
#undef CHAR
#undef STRCMP
#undef STRLCPY
#undef STRLCAT
#undef LIT

#define FUNCTION TestStringsTcs
#define CHAR TChar
#define STRCMP Tcscmp
#define STRLCPY Tcslcpy
#define STRLCAT Tcslcat
#define LIT(STR) PAL_T(STR)
#include "TestStringsAux.h"
#undef FUNCTION
#undef CHAR
#undef STRCMP
#undef STRLCPY
#undef STRLCAT
#undef LIT

NitsTest(TestStrings)
{
    TestStringsStr();
    TestStringsWcs();
    TestStringsTcs();
}
NitsEndTest

NitsTest(TestStrings_ToUpper)
{
    TEST_ASSERT(PAL_tolower(PAL_T('a')) == PAL_T('a'));
    TEST_ASSERT(PAL_tolower(PAL_T('A')) == PAL_T('a'));

    TEST_ASSERT(PAL_tolower(PAL_T('z')) == PAL_T('z'));
    TEST_ASSERT(PAL_tolower(PAL_T('Z')) == PAL_T('z'));

    /* characters before 'a','A' and after 'z','Z' */
    TEST_ASSERT(PAL_tolower(PAL_T('`')) == PAL_T('`')); 
    TEST_ASSERT(PAL_tolower(PAL_T('@')) == PAL_T('@'));
    TEST_ASSERT(PAL_tolower(PAL_T('{')) == PAL_T('{'));
    TEST_ASSERT(PAL_tolower(PAL_T('[')) == PAL_T('['));
}
NitsEndTest

//==============================================================================
//
// TestDir()
//
//==============================================================================

const char* TmpName(
    _Pre_writable_size_(PAL_MAX_PATH_SIZE) char buf[PAL_MAX_PATH_SIZE],
    const char* suffix)
{
#if defined(_MSC_VER)
    const char TMPDIR[] = "C:/Temp";
#else
    const char TMPDIR[] = "/tmp";
#endif
    Strlcpy(buf, TMPDIR, PAL_MAX_PATH_SIZE);
    Strlcat(buf, suffix, PAL_MAX_PATH_SIZE);
    return buf;
}

static void EnsureTmpExists()
{
#if defined(_MSC_VER)
    Mkdir("C:/Temp", 0700);
#endif
}

static void TestDirCleanup()
{
    char buf[PAL_MAX_PATH_SIZE];

    Rmdir(TmpName(buf, "/pal/TestDir/dir1"));
    Rmdir(TmpName(buf, "/pal/TestDir/dir2"));
    File_Remove(TmpName(buf, "/pal/TestDir/file1"));
    File_Remove(TmpName(buf, "/pal/TestDir/file2"));
    File_Remove(TmpName(buf, "/pal/TestDir/file3"));
    Rmdir(TmpName(buf, "/pal/TestDir"));
    Rmdir(TmpName(buf, "/pal"));
}

NitsTest(TestDir)
{
    char buf[PAL_MAX_PATH_SIZE];

    EnsureTmpExists();
    TestDirCleanup();

    // Create directories and files:

    TEST_ASSERT(Mkdir(TmpName(buf, "/pal/"), 0700) == 0);
    TEST_ASSERT(Mkdir(TmpName(buf, "/pal/TestDir"), 0700) == 0);
    TEST_ASSERT(Mkdir(TmpName(buf, "/pal/TestDir/dir1"), 0700) == 0);
    TEST_ASSERT(Mkdir(TmpName(buf, "/pal/TestDir/dir2"), 0700) == 0);
    TEST_ASSERT(File_Touch(TmpName(buf, "/pal/TestDir/file1")) == 0);
    TEST_ASSERT(File_Touch(TmpName(buf, "/pal/TestDir/file2")) == 0);
    TEST_ASSERT(File_Touch(TmpName(buf, "/pal/TestDir/file3")) == 0);

    Dir* dir = Dir_Open(TmpName(buf, "/pal/TestDir"));
    TEST_ASSERT(dir != NULL);

    if (dir != NULL)
    {
        vector<string> names1;

        for (;;)
        {
            DirEnt* ent = Dir_Read(dir);
            if (!ent)
                break;

            if (strcmp(ent->name, "..") == 0 || strcmp(ent->name, ".") == 0)
                continue;

            names1.push_back(ent->name);
        }

        sort(names1.begin(), names1.end());

        vector<string> names2;
        names2.push_back("dir1");
        names2.push_back("dir2");
        names2.push_back("file1");
        names2.push_back("file2");
        names2.push_back("file3");

        TEST_ASSERT(names1.size() == 5);
        TEST_ASSERT(names2.size() == 5);
        TEST_ASSERT(names1 == names2);

        Dir_Close(dir);
    }

    TestDirCleanup();
}
NitsEndTest

//==============================================================================
//
// TestFile()
//
//==============================================================================

NitsTest(TestFile)
{
    const char* FILENAME = "/PalTestFile.txt";
    char buf[PAL_MAX_PATH_SIZE];

    EnsureTmpExists();
    File_Remove(TmpName(buf, FILENAME));

    // Create a file with the contents "hello"
    {
        FILE* fp = File_Open(TmpName(buf, FILENAME), "w");
        TEST_ASSERT(fp != NULL);

        size_t n = fwrite("hello", 1, 5, fp);
        TEST_ASSERT(n == 5);

        File_Close(fp);
    }

    // Open file and read contents:
    {
        FILE* fp = File_Open(TmpName(buf, FILENAME), "r");
        TEST_ASSERT(fp != NULL);

        char data[1024];

        size_t n = fread(data, 1, sizeof(data), fp);

        TEST_ASSERT(n == 5);
        TEST_ASSERT(memcmp(data, "hello", 5) == 0);

        File_Close(fp);
    }

    // Clean up:
    
    File_Remove(TmpName(buf, FILENAME));
}
NitsEndTest

//==============================================================================
//
// TestHashMap()
//
//==============================================================================

typedef struct _TestBucket /* derives from HashBucket */
{
    struct _TestBucket* next;
    PAL_Char* key;
    long data;
}
TestBucket;

NITS_EXTERN_C size_t TestHash(
    const HashBucket* bucket_)
{
    /* Note: this algorithm has a poor distribution */
    TestBucket* bucket = (TestBucket*)bucket_;
    size_t h = 0;
    PAL_Char* key = bucket->key;

    while (*key)
    {
        h += 5 * *key++;
    }

    return h;
}

NITS_EXTERN_C int TestEqual(
    const HashBucket* bucket1_,
    const HashBucket* bucket2_)
{
    TestBucket* bucket1 = (TestBucket*)bucket1_;
    TestBucket* bucket2 = (TestBucket*)bucket2_;
    return Tcscmp(bucket1->key, bucket2->key) == 0;
}

NITS_EXTERN_C void TestRelease(
    HashBucket* bucket_)
{
    TestBucket* bucket = (TestBucket*)bucket_;

    PAL_Free(bucket->key);
    PAL_Free(bucket);
}

NitsTest(TestHashMap1)
{
    HashMap map;
    int r;
    TestBucket* b;

    r = HashMap_Init(&map, 1, TestHash, TestEqual, TestRelease);
    TEST_ASSERT(r == 0);

    /* Insert some buckets */
    {
        /* Insert RED=1 */
        {
            b = (TestBucket*)PAL_Calloc(1, sizeof(TestBucket));
            if(TEST_ASSERT(b != 0))
            {
                b->key = PAL_Tcsdup(PAL_T("RED"));
                b->data = 1;
                r = HashMap_Insert(&map, (HashBucket*)b);
                TEST_ASSERT(r == 0);
            }
        }

        /* Insert GREEN=2 */
        {
            b = (TestBucket*)PAL_Calloc(1, sizeof(TestBucket));
            if(TEST_ASSERT(b != 0))
            {
                b->key = PAL_Tcsdup(PAL_T("GREEN"));
                b->data = 2;
                r = HashMap_Insert(&map, (HashBucket*)b);
                TEST_ASSERT(r == 0);
            }
        }

        /* Insert BLUE=3 */
        {
            b = (TestBucket*)PAL_Calloc(1, sizeof(TestBucket));
            if(TEST_ASSERT(b != 0))
            {
                b->key = PAL_Tcsdup(PAL_T("BLUE"));
                b->data = 3;
                r = HashMap_Insert(&map, (HashBucket*)b);
                TEST_ASSERT(r == 0);

                /* Insert BLUE=3 again (should fail) */
                r = HashMap_Insert(&map, (HashBucket*)b);
                TEST_ASSERT(r == 1);
            }
        }


        /* Find RED=1 */
        {
            TestBucket key;
            key.key = (PAL_Char*)PAL_T("RED");
            b = (TestBucket*)HashMap_Find(&map, (const HashBucket*)&key);
            if(TEST_ASSERT(b != 0))
            {
                TEST_ASSERT(Tcscmp(b->key, PAL_T("RED")) == 0);
                TEST_ASSERT(b->data == 1);
            }
        }

        /* Find GREEN=2 */
        {
            TestBucket key;
            key.key = (PAL_Char*)PAL_T("GREEN");
            b = (TestBucket*)HashMap_Find(&map, (const HashBucket*)&key);
            if(TEST_ASSERT(b != 0))
            {
                TEST_ASSERT(Tcscmp(b->key, PAL_T("GREEN")) == 0);
                TEST_ASSERT(b->data == 2);
            }
        }

        /* Find BLUE=3 */
        {
            TestBucket key;
            key.key = (PAL_Char*)PAL_T("BLUE");
            b = (TestBucket*)HashMap_Find(&map, (const HashBucket*)&key);
            if(TEST_ASSERT(b != 0))
            {
                TEST_ASSERT(Tcscmp(b->key, PAL_T("BLUE")) == 0);
                TEST_ASSERT(b->data == 3);
            }
        }

        /* Find YELLOW=4 (should fail) */
        {
            TestBucket key;
            key.key = (PAL_Char*)PAL_T("YELLOW");
            b = (TestBucket*)HashMap_Find(&map, (const HashBucket*)&key);
            TEST_ASSERT(b == 0);
        }

        /* Remove RED */
        {
            TestBucket key;
            key.key = (PAL_Char*)PAL_T("RED");
            r = HashMap_Remove(&map, (const HashBucket*)&key);
            TEST_ASSERT(r == 0);

            /* Remove should fail now */
            r = HashMap_Remove(&map, (const HashBucket*)&key);
            TEST_ASSERT(r == -1);
        }

        /* Remove GREEN */
        {
            TestBucket key;
            key.key = (PAL_Char*)PAL_T("GREEN");
            r = HashMap_Remove(&map, (const HashBucket*)&key);
            TEST_ASSERT(r == 0);

            /* Remove should fail now */
            r = HashMap_Remove(&map, (const HashBucket*)&key);
            TEST_ASSERT(r == -1);
        }

        /* Remove BLUE */
        {
            TestBucket key;
            key.key = (PAL_Char*)PAL_T("BLUE");
            r = HashMap_Remove(&map, (const HashBucket*)&key);
            TEST_ASSERT(r == 0);

            /* Remove should fail now */
            r = HashMap_Remove(&map, (const HashBucket*)&key);
            TEST_ASSERT(r == -1);
        }

        /* Remove YELLOW (should fail) */
        {
            TestBucket key;
            key.key = (PAL_Char*)PAL_T("YELLOW");
            r = HashMap_Remove(&map, (const HashBucket*)&key);
            TEST_ASSERT(r == -1);
        }
    }

    /* Release all the memroy */
    HashMap_Destroy(&map);
}
NitsEndTest

NitsTest(TestHashMap2)
{
    HashMap map;
    int r;
    size_t i;
    const size_t N = 10000;

    /* Create the hash map */

    r = HashMap_Init(&map, 63, TestHash, TestEqual, TestRelease);
    TEST_ASSERT(r == 0);

    /* Insert N buckets into hash map */

    for (i = 0; i < N; i++)
    {
        PAL_Char buf[32];
        TestBucket* b;

        Stprintf(buf, PAL_COUNT(buf), PAL_T("%u"), (unsigned int)i);
        b = (TestBucket*)PAL_Calloc(1, sizeof(TestBucket));
        TEST_ASSERT(b != 0);
        if (b == 0) NitsReturn;
        b->key = PAL_Tcsdup(buf);
        b->data = (long)i;
        r = HashMap_Insert(&map, (HashBucket*)b);
        TEST_ASSERT(r == 0);
    }

    /* Verify that each number is in the hash map */

    for (i = 0; i < N; i++)
    {
        PAL_Char buf[32];
        TestBucket* b;
        TestBucket kb;
        kb.key = buf;
        Stprintf(buf, PAL_COUNT(buf), PAL_T("%u"), (unsigned int)i);

        /* Find it */

        b = (TestBucket*)HashMap_Find(&map, (const HashBucket*)&kb);
        TEST_ASSERT(b != 0);

        /* Check it */
        TEST_ASSERT(Tcscmp(b->key, buf) == 0);
    }

    /* Delete all the buckets */

    for (i = 0; i < N; i++)
    {
        PAL_Char buf[32];
        TestBucket kb;
        int r;

        kb.key = buf;
        Stprintf(buf, PAL_COUNT(buf), PAL_T("%u"), (unsigned int)i);

        /* Find it */

        r = HashMap_Remove(&map, (const HashBucket*)&kb);
        TEST_ASSERT(r == 0);
    }

    /* Release all the memroy */
    HashMap_Destroy(&map);
}
NitsEndTest

NitsTest(TestHashMap2_preallocated)
{
    HashMap map;
    int r;
    size_t i;
    const size_t N = 10000;
    void* hashMapBuckets[63];

    /* Create the hash map */

    HashMap_Construct(&map, 63, hashMapBuckets, TestHash, TestEqual, TestRelease);

    /* Insert N buckets into hash map */

    for (i = 0; i < N; i++)
    {
        PAL_Char buf[32];
        TestBucket* b;

        Stprintf(buf, PAL_COUNT(buf), PAL_T("%u"), (unsigned int)i);
        b = (TestBucket*)PAL_Calloc(1, sizeof(TestBucket));
        TEST_ASSERT(b != 0);
        if (b == 0) NitsReturn;
        b->key = PAL_Tcsdup(buf);
        b->data = (long)i;
        r = HashMap_Insert(&map, (HashBucket*)b);
        TEST_ASSERT(r == 0);
    }

    /* Verify that each number is in the hash map */

    for (i = 0; i < N; i++)
    {
        PAL_Char buf[32];
        TestBucket* b;
        TestBucket kb;
        kb.key = buf;
        Stprintf(buf, PAL_COUNT(buf), PAL_T("%u"), (unsigned int)i);

        /* Find it */

        b = (TestBucket*)HashMap_Find(&map, (const HashBucket*)&kb);
        TEST_ASSERT(b != 0);

        /* Check it */
        TEST_ASSERT(Tcscmp(b->key, buf) == 0);
    }

    /* Delete all the buckets */

    for (i = 0; i < N; i++)
    {
        PAL_Char buf[32];
        TestBucket kb;
        int r;

        kb.key = buf;
        Stprintf(buf, PAL_COUNT(buf), PAL_T("%u"), (unsigned int)i);

        /* Find it */

        r = HashMap_Remove(&map, (const HashBucket*)&kb);
        TEST_ASSERT(r == 0);
    }

    /* Release all the memroy */
    HashMap_Destroy(&map);
}
NitsEndTest

NitsTest(TestHashMap_HashProc_PalStringCaseInsensitive)
{
    TEST_ASSERT( HashMap_HashProc_PalStringCaseInsensitive(PAL_T("")) == HashMap_HashProc_PalStringCaseInsensitive(PAL_T("")));
    TEST_ASSERT( HashMap_HashProc_PalStringCaseInsensitive(PAL_T("foo")) == HashMap_HashProc_PalStringCaseInsensitive(PAL_T("foo")));
    TEST_ASSERT( HashMap_HashProc_PalStringCaseInsensitive(PAL_T("fooBARbaz")) == HashMap_HashProc_PalStringCaseInsensitive(PAL_T("FOObarBAZ")));
    TEST_ASSERT( HashMap_HashProc_PalStringCaseInsensitive(PAL_T("foo")) != HashMap_HashProc_PalStringCaseInsensitive(PAL_T("bar")));
}
NitsEndTest

NitsTest(TestHashMap_HashProc_AnsiString)
{
    TEST_ASSERT( HashMap_HashProc_AnsiString("") == HashMap_HashProc_AnsiString(""));
    TEST_ASSERT( HashMap_HashProc_AnsiString("foo") == HashMap_HashProc_AnsiString("foo"));
    TEST_ASSERT( HashMap_HashProc_AnsiString("fooBARbaz") != HashMap_HashProc_AnsiString("FOObarBAZ"));
    TEST_ASSERT( HashMap_HashProc_AnsiString("foo") != HashMap_HashProc_AnsiString("bar"));
}
NitsEndTest

//==============================================================================
//
// Tests for format.placeholders.h
// - PAL_PRItstr
// - PAL_PRI64d
//
//==============================================================================

NitsTest(TestFormat_64bitFormatQualifiers_d)
{
    TChar buf[1024] = {0};

    Stprintf(
        buf, 
        PAL_COUNT(buf), 
        PAL_T("%") PAL_T(PAL_PRId64),
        PAL_SINT64_MIN);

    TEST_ASSERT(Tcscmp(buf, PAL_T("-9223372036854775808")) == 0);
}
NitsEndTest

NitsTest(TestFormat_64bitFormatQualifiers_u)
{
    TChar buf[1024] = {0};

    Stprintf(
        buf, 
        PAL_COUNT(buf), 
        PAL_T("%") PAL_T(PAL_PRIu64),
        PAL_UINT64_MAX);

    TEST_ASSERT(Tcscmp(buf, PAL_T("18446744073709551615")) == 0);
}
NitsEndTest

NitsTest(TestFormat_PalCharSpecifier)
{
    TChar buf[1024] = {0};

    Stprintf(
        buf, 
        PAL_COUNT(buf), 
        PAL_T("foo=%") PAL_T(PAL_PRItstr),
        PAL_T("bar"));

    TEST_ASSERT(Tcscmp(buf, PAL_T("foo=bar")) == 0);
}
NitsEndTest

//==============================================================================
//
// Tests for format.c / format.h
// - Stprintf
// - Stprintf_StrDup
// - Stprintf_CultureInvariant
// - Stscanf
//
//==============================================================================

NitsTest(TestFormat_Stprintf)
{
    TChar buf[1024];

    Stprintf(
        buf, 
        PAL_COUNT(buf), 
        PAL_T("%T %S %s"), 
        tcs(PAL_T("Red")),
        wcs(L"Green"),
        scs("Blue"));

    TEST_ASSERT(Tcscmp(buf, PAL_T("Red Green Blue")) == 0);
}
NitsEndTest

NitsTest(TestFormat_Stprintf_Strdup)
{
    TChar* result = NULL;

    result = Stprintf_StrDup(PAL_T("test = %d"), 12345);
    TEST_ASSERT(result != NULL);
    if (result != NULL)
    {
        TEST_ASSERT(Tcscmp(result, PAL_T("test = 12345")) == 0);
    }

    PAL_Free(result);
}
NitsEndTest

#include <locale.h>
NitsTest(TestFormat_Stprintf_CultureInvariant)
{
    TChar buf[1024] = {0};

    char oldLocale[128];
    char testLocale[128];
    char *currentLocale = NULL;
    Strlcpy(oldLocale, setlocale(LC_ALL, NULL), PAL_COUNT(oldLocale));
    currentLocale = setlocale(LC_ALL, "polish");
    if(currentLocale)
    {
        Strlcpy(testLocale, currentLocale, PAL_COUNT(testLocale));

        Stprintf(
            buf, 
            PAL_COUNT(buf), 
            PAL_T("%g"), 
            1.23); 
        NitsAssert(
            Tcscmp(buf, PAL_T("1,23")) == 0, 
            PAL_T("Sanity check that polish locale uses a comma instead of a dot for decimal point"));
    }
    else
    {
        /* ATTN: alternate implementation needed to test the functionality! */
        NitsAssert(true, PAL_T("test skipped"));
    }

    Stprintf_CultureInvariant(
        buf, 
        PAL_COUNT(buf), 
        PAL_T("%g"), 
        1.23); 
    TEST_ASSERT(Tcscmp(buf, PAL_T("1.23")) == 0);

    if(currentLocale)
    {
        NitsAssert(
            0 == Strcmp(testLocale, setlocale(LC_ALL, NULL)),
            PAL_T("Invocation of Stprintf_CultureInvariant shouldn't change current locale"));
    }

    setlocale(LC_ALL, oldLocale);
}
NitsEndTest


NitsTest(TestFormat_Stscanf_CultureInvariant)
{
    int result = 0;
    double number = 0.0;

    char oldLocale[128];
    char testLocale[128];
    char *currentLocale = NULL;
    Strlcpy(oldLocale, setlocale(LC_ALL, NULL), PAL_COUNT(oldLocale));
    currentLocale = setlocale(LC_ALL, "polish");
    if(currentLocale)
    {
        Strlcpy(testLocale, currentLocale, PAL_COUNT(testLocale));

        result = Stscanf_CultureInvariant(
            PAL_T("1.23"), 
            PAL_T("%lg"), 
            &number); 
        NitsAssert(
            (1.22 < number) && (number < 1.24),
            PAL_T("Sanity check that polish locale uses a comma instead of a dot for decimal point"));
        NitsAssert(
            result == 1,
            PAL_T("Scanf should return the number of elements it consumed"));
        NitsAssert(
            0 == Strcmp(testLocale, setlocale(LC_ALL, NULL)),
            PAL_T("Invocation of Stscanf_CultureInvariant shouldn't change current locale"));
    }
    else
    {
        /* ATTN: alternate implementation needed to test the functionality! */
        NitsAssert(true, PAL_T("test skipped"));
    }

    setlocale(LC_ALL, oldLocale);
}
NitsEndTest

//==============================================================================
//
// TestCondLock()
//
//==============================================================================

struct TestCondLockData
{
    ptrdiff_t key;
    ptrdiff_t predicate;
    Lock lock;
};

NITS_EXTERN_C PAL_Uint32 THREAD_API TestCondLockReader(void* arg)
{
    TestCondLockData* data = (TestCondLockData*)arg;

    // Wait on the condition variable:

    for (;;)
    {
        // Wait while predicate == 0:

        CondLock_Wait(
            data->key, &data->predicate, 0, CONDLOCK_DEFAULT_SPINCOUNT);

        Lock_Acquire(&data->lock);

        // If predicate not satisfied, continue:

        if (data->predicate == 0)
        {
            Lock_Release(&data->lock);
            continue;
        }

        // Check the predicate:

        TEST_ASSERT(data->predicate == 12345678);
        Lock_Release(&data->lock);
        break;
    }

    return 0;
}

NITS_EXTERN_C PAL_Uint32 THREAD_API TestCondLockWriter(void* arg)
{
    TestCondLockData* data = (TestCondLockData*)arg;

    // Wait one second for reader to start:

    Sleep_Milliseconds(1000);

    // Update the predicate:

    Lock_Acquire(&data->lock);
    data->predicate = 12345678;
    Lock_Release(&data->lock);

    // Signal the reader:

    CondLock_Signal(data->key);

    return 0;
}

NitsTest(TestCondLock)
{
    // Initialize the data:

    TestCondLockData data;
    data.key = 1001;
    data.predicate = 0;
    Lock_Init(&data.lock);

    // Create writer thread:
    
    Thread writer;
    int writer_created = PAL_FALSE;

    writer_created = (Thread_CreateJoinable(&writer, TestCondLockWriter, NULL, &data) == 0);
    TEST_ASSERT(writer_created);

    // Create reader threads:

    Thread reader;
    int reader_created = PAL_FALSE;

    reader_created = (Thread_CreateJoinable(&reader, TestCondLockReader, NULL, &data) == 0);
    TEST_ASSERT(reader_created);

    if (writer_created)
    {
        PAL_Uint32 arg;
        Thread_Join(&writer, &arg);
        Thread_Destroy(&writer);
    }
    else
    {
        Lock_Acquire(&data.lock);
        data.predicate = 0xdeadbeef;
        Lock_Release(&data.lock);

        CondLock_Signal(data.key);
    }

    if (reader_created)
    {
        PAL_Uint32 arg;
        Thread_Join(&reader, &arg);
        Thread_Destroy(&reader);
    }
}
NitsEndTest

//==============================================================================
//
// Tests for Intlstr
//
//==============================================================================

#if (!(defined(linux) || defined(macos)) && !defined(CONFIG_ENABLE_WCHAR))
NitsTest(TestIntlstr_SimpleString)
{
    Intlstr result = Intlstr_Null;
    result = Intlstr_TestPal_SimpleString();
    NitsAssert(result.str != NULL, PAL_T("Could we get a localized string? (if not, double-check if mui file is deployed correctly)"));
    if (result.str != NULL)
    {
        TEST_ASSERT(Tcscmp(result.str, PAL_T("My simple string")) == 0);
    }
    Intlstr_Free(result);
}
NitsEndTest

NitsTest(TestIntlstr_ReorderablePlaceholders)
{
    Intlstr result = Intlstr_Null;
    result = Intlstr_TestPal_ReorderablePlaceholders(123, 456);
    NitsAssert(result.str != NULL, PAL_T("Could we get a localized string? (if not, double-check if mui file is deployed correctly)"));
    if (result.str != NULL)
    {
        TEST_ASSERT(Tcscmp(result.str, PAL_T("Second integer = 456,  First integer = 123")) == 0);
    }
    Intlstr_Free(result);
}
NitsEndTest

NitsTest(TestIntlstr_OnePlaceholder)
{
    Intlstr result = Intlstr_Null;
    result = Intlstr_TestPal_OnePlaceholder(1);
    NitsAssert(result.str != NULL, PAL_T("Could we get a localized string? (if not, double-check if mui file is deployed correctly)"));
    if (result.str != NULL)
    {
        TEST_ASSERT(Tcscmp(result.str, PAL_T("p1=1")) == 0);
    }
    Intlstr_Free(result);
}
NitsEndTest

NitsTest(TestIntlstr_TwoPlaceholders)
{
    Intlstr result = Intlstr_Null;
    result = Intlstr_TestPal_TwoPlaceholders(1,2);
    NitsAssert(result.str != NULL, PAL_T("Could we get a localized string? (if not, double-check if mui file is deployed correctly)"));
    if (result.str != NULL)
    {
        TEST_ASSERT(Tcscmp(result.str, PAL_T("p1=1, p2=2")) == 0);
    }
    Intlstr_Free(result);
}
NitsEndTest

NitsTest(TestIntlstr_ThreePlaceholders)
{
    Intlstr result = Intlstr_Null;
    result = Intlstr_TestPal_ThreePlaceholders(1,2,3);
    NitsAssert(result.str != NULL, PAL_T("Could we get a localized string? (if not, double-check if mui file is deployed correctly)"));
    if (result.str != NULL)
    {
        TEST_ASSERT(Tcscmp(result.str, PAL_T("p1=1, p2=2, p3=3")) == 0);
    }
    Intlstr_Free(result);
}
NitsEndTest

NitsTest(TestIntlstr_Specifier_d)
{
    Intlstr result = Intlstr_Null;
    result = Intlstr_TestPal_Specifier_d(123);
    NitsAssert(result.str != NULL, PAL_T("Could we get a localized string? (if not, double-check if mui file is deployed correctly)"));
    if (result.str != NULL)
    {
        TEST_ASSERT(Tcscmp(result.str, PAL_T("p1=123")) == 0);
    }
    Intlstr_Free(result);
}
NitsEndTest

NitsTest(TestIntlstr_Specifier_tstr)
{
    Intlstr result = Intlstr_Null;
    result = Intlstr_TestPal_Specifier_tstr(PAL_T("foo"));
    NitsAssert(result.str != NULL, PAL_T("Could we get a localized string? (if not, double-check if mui file is deployed correctly)"));
    if (result.str != NULL)
    {
        TEST_ASSERT(Tcscmp(result.str, PAL_T("p1=foo")) == 0);
    }
    Intlstr_Free(result);
}
NitsEndTest

NitsTest(TestIntlstr_Specifier_tchr)
{
    Intlstr result = Intlstr_Null;
    result = Intlstr_TestPal_Specifier_tchr(PAL_T('f'));
    NitsAssert(result.str != NULL, PAL_T("Could we get a localized string? (if not, double-check if mui file is deployed correctly)"));
    if (result.str != NULL)
    {
        TEST_ASSERT(Tcscmp(result.str, PAL_T("char=f")) == 0);
    }
    Intlstr_Free(result);
}
NitsEndTest

NitsTest(TestIntlstr_Specifier_x)
{
    Intlstr result = Intlstr_Null;
    result = Intlstr_TestPal_Specifier_x(0x12345678);
    NitsAssert(result.str != NULL, PAL_T("Could we get a localized string? (if not, double-check if mui file is deployed correctly)"));
    if (result.str != NULL)
    {
        TEST_ASSERT(Tcscmp(result.str, PAL_T("p1=0x12345678")) == 0);
    }
    Intlstr_Free(result);
}
NitsEndTest
#endif

#if defined(CONFIG_ENABLE_WCHAR)

bool TestWideCharConversion(const wchar_t *src, size_t srcSize, const char *expectedResult, int expectedDestSize)
{
    size_t firstNonAscii = 0;
    int utf8Size = 0;

#if defined(_MSC_VER)    
    int lastError = 0;
    
    SetLastError(0);
#endif

    utf8Size = ConvertWideCharToMultiByte(
                    src,
                    srcSize,
                    &firstNonAscii,
                    NULL,
                    utf8Size);

#if defined(_MSC_VER)    
    lastError = GetLastError();
    NitsAssert(lastError == 0, PAL_T("Last error not zero"));
#endif

    NitsAssert(utf8Size == (int)expectedDestSize, PAL_T("Space computed was 0"));        


    char *dest = (char *)PAL_Calloc(1, utf8Size*sizeof(char));

    if(!NitsAssert(dest, PAL_T("memory alloc failure")))
        return false;
    
    utf8Size = ConvertWideCharToMultiByte(
                    src,
                    srcSize,
                    &firstNonAscii,
                    dest,
                    utf8Size * sizeof(char));

   
    NitsAssert(utf8Size == (int)expectedDestSize, PAL_T("Space computed was 0"));
    NitsAssert(Strncmp(dest, expectedResult, utf8Size) == 0, PAL_T("Result does not match expected"));
#if defined(_MSC_VER)    
    lastError = GetLastError();    
    NitsAssert(lastError == 0, PAL_T("Last error not zero"));
#endif
    PAL_Free(dest);
    return true;
}

NitsTest(TestWideCharToMultiByteConversion1)
    const wchar_t *src = L"Mywidestring";
    size_t count = Wcslen(src);
    const char *expectedResult = "Mywidestring";   

    NitsAssert(TestWideCharConversion(src, count, expectedResult, count), PAL_T("conversion failed"));
NitsEndTest

NitsTest(TestWideCharToMultiByteConversion2)
    const wchar_t src[] = {0xE0, 0x248B, 0x61, 0x2173, 0x62, 0x1EA6, 0xFF21, 0xAA, 0x325, 0x2173, 0x249C, 0x63};
    size_t wideCharSize = sizeof(src)/sizeof(wchar_t);
    const unsigned char expectedResult[] = {0xC3, 0xA0, 0xE2, 0x92, 0x8B, 0x61, 0xE2, 0x85, 0xB3, 0x62, 0xE1, 0xBA, 0xA6, 0xEF, 0xBC, 0xA1, 0xC2, 0xAA, 0xCC, 0xA5, 0xE2, 0x85, 0xB3, 0xE2, 0x92, 0x9C, 0x63}; 
    int expectedSize = (int)(sizeof(expectedResult)/sizeof(char));
    NitsAssert(TestWideCharConversion(src, wideCharSize,(const char*) expectedResult, expectedSize), PAL_T("conversion failed"));
NitsEndTest


#if !defined(_MSC_VER) && !defined(aix) && !defined(hpux)

NitsTest(TestWideCharToMultiByteConversion3)
    const wchar_t src[] = {0x10FFFF, 0x110000};
    size_t wideCharSize = sizeof(src)/sizeof(wchar_t);
    const unsigned char expectedResult[] = {0xF4, 0x8F, 0xBF, 0xBF, '?'}; 
    int expectedSize = (int)(sizeof(expectedResult)/sizeof(char));
    NitsAssert(TestWideCharConversion(src, wideCharSize, (const char*) expectedResult, expectedSize), PAL_T("conversion failed"));
NitsEndTest

#endif

#endif /* defined(CONFIG_ENABLE_WCHAR) */

#if defined(USE_ALLOCATOR)
NitsTest(TestAlloc)
{
    void* ptrs[1024];
    size_t n = sizeof(ptrs) / sizeof(ptrs[0]);
    size_t i;
    AllocStats stats = PAL_GetAllocStats();
    size_t numAllocs = stats.numAllocs;
    size_t numFrees = stats.numFrees;
    size_t usage = stats.usage;
    size_t extraUsage = 0;

    for (i = 0; i < n; i++)
    {
        ptrs[i] = PAL_Malloc(i+1);
        extraUsage += i + 1;
    }

    stats = PAL_GetAllocStats();
    TEST_ASSERT(stats.numAllocs == numAllocs + n);
    TEST_ASSERT(stats.usage == usage + extraUsage);


    for (i = 0; i < n; i++)
    {
        PAL_Free(ptrs[i]);
    }

    stats = PAL_GetAllocStats();
    TEST_ASSERT(stats.numFrees == numFrees + n);
    TEST_ASSERT(stats.usage == usage);
}
NitsEndTest
#endif /* defined(USE_ALLOCATOR) */
