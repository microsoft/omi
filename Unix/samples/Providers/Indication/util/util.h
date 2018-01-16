/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef __util_h
#define __util_h

#include <MI.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "nwinsal.h"
#include <stdlib.h>
#include <time.h>

#if defined(__cplusplus)
# define BEGIN_EXTERNC extern "C" {
# define END_EXTERNC }
#else
# define BEGIN_EXTERNC
# define END_EXTERNC
#endif

BEGIN_EXTERNC

# define THREAD_API /* empty */

typedef MI_Uint32 (THREAD_API *ThreadProc)(void* param);

typedef struct _Thread 
{
    pthread_t __impl;
}
Thread;

typedef struct _ThreadID
{
    pthread_t __impl;
}
ThreadID;

_Return_type_success_(return == 0) int Thread_Create(
    _Out_ Thread* self,
    _In_ ThreadProc proc,
    _In_ void* param);

MI_INLINE void Thread_Destroy(
    _Inout_ Thread* self)
{
    /* Zero out so it will fail if called before join */
    memset(self, 0, sizeof(*self));
}

_Return_type_success_(return == 0) int Thread_Join(
    _In_ Thread* self,
    _Out_ MI_Uint32* returnValue);

int Thread_Equal(
    _In_ ThreadID* thread1,
    _In_ ThreadID* thread2);

ThreadID Thread_ID();

MI_INLINE ThreadID Thread_ID_Null()
{
    ThreadID returnValue = {0};
    return returnValue;
}

void Thread_Exit(
    _In_ MI_Uint32 returnValue);


MI_INLINE void Sleep_Milliseconds(
    _In_ unsigned long milliseconds)
{
    struct timespec ts;
    ts.tv_sec = (long)(milliseconds / 1000);
    ts.tv_nsec = (long)((milliseconds % 1000) * 1000 * 1000);
    nanosleep(&ts, NULL);
}

/*
 * Set seed for rand function
 */
MI_INLINE 
void SRAND()
{
    srand( time( NULL ) );
}


/*
 * Callback function to trigger indication
 */
typedef MI_Uint32 (MI_CALL *CreatePostIndication)(
    _In_ void* callbackdata);

/*
 * Structure used to post indication
 */
typedef struct _SelfStruct
{
    void* context;
    MI_Boolean disabling;
    Thread thread;
    CreatePostIndication postindication;
    MI_Uint64 seqid;
}
SelfStruct;

/*
 * thread proc to trigger indication periodically until postindication return 0
 */
MI_Uint32 THREAD_API fireIndication(void* param);

#define CHECKR_POST_RETURN(ctx, r) \
    if (r != MI_RESULT_OK) \
    {\
        MI_Context_PostResult(ctx, r);\
        return 0;\
    }\

#define CHECKR_POST_RETURN_VOID(ctx, r) \
    if (r != MI_RESULT_OK) \
    {\
        MI_Context_PostResult(ctx, r);\
        return;\
    }\


/*
 * Defines Lock structure
 */
typedef struct _Lock
{
    pthread_mutex_t lock;
}
Lock;

void Lock_Init(_Out_ Lock* self);
void Lock_Finalize(_In_ _Post_invalid_ Lock* self);

_Requires_lock_not_held_(self)
_Acquires_lock_(self)
void Lock_Acquire(_Inout_ Lock* self);
_Requires_lock_held_(self)
_Releases_lock_(self)
void Lock_Release(_Inout_ Lock* self);

/*
 * Duplicate string
 */
MI_Result MI_StringDup(const MI_Char* src, _Outptr_result_z_ MI_Char** dest);

END_EXTERNC

#endif /* __util_h */
