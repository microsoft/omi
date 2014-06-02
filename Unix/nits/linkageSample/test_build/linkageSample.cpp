/*
 * Copyright (C) 2011 Microsoft Corporation
 * All rights reserved.
 */
#include <stdio.h>
#include <nits/base/nits.h>
#include <pal/thread.h>

NITS_EXTERN_C PAL_Uint32 THREAD_API MyThreadProc(_In_ void * param)
{
    PAL_UNUSED(param);
    NitsTrace(PAL_T("MyThreadProc running"));
    return 0;
}

int foo()
{
    Thread mythread;    
    PAL_Uint32 dummy;
    NitsTrace(PAL_T("foo running"));
    if(Thread_CreateJoinable(&mythread, MyThreadProc, NULL, NULL) == 0)
    {
        Thread_Join(&mythread, &dummy);
        return 0;
    }

    return -1;
}

NitsTest(SampleTest)
    int r = foo();    
    NitsTrace(PAL_T("SampleTest running"));
    NitsAssert(r == 0, PAL_T("SampleTest done"));
NitsEndTest

