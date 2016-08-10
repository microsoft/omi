/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <stdio.h>
#include <nits/base/nits.h>
#include <pal/thread.h>
#include <pal/sleep.h>

NITS_EXTERN_C PAL_Uint32 THREAD_API MyThreadProc(_In_ void * param)
{
    PAL_UNUSED(param);    

    NitsTrace(PAL_T("MyThreadProc running\n"));

    Sleep_Milliseconds(1000);

    return 0;
}

void foo()
{
    Thread mythread;    
    PAL_Uint32 dummy;
    Sleep_Milliseconds(1000);
    NitsTrace(PAL_T("Foo running\n"));
    Thread_CreateJoinable_Injected(&mythread, MyThreadProc, NULL, NULL, NitsHere());    
    Thread_Join(&mythread, &dummy);
}

int PAL_CDECLAPI main()
{    
    foo(); 
    NitsTrace(PAL_T("main running\n"));
    return 0;
}

