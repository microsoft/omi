/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#if !defined(macos)
#include <malloc.h>
#endif
#include <MI.h>
#include "miapi_common.h"
#include "SafeHandle.h"
#include <pal/atomic.h>
#include <pal/format.h>
#include <base/log.h>




/* This should never be needed anywhere else but in this file which 
 * is why it is not in the header.
 */
void ThunkHandle_Initialize(_Inout_ ThunkHandle *thunkHandle, _Inout_ ThunkHandleManager *manager, MI_Boolean firstTime);


/* PUBLIC: Initialize
 * Initialize the free-list.  Just sets up the lockless list.
 */
void ThunkHandleManager_Initialize(_Inout_ ThunkHandleManager *manager)
{
    SList_Init(&manager->freeList);
}

/* PUBLIC: DeInitialize
 * Delete all handles from the free list.
 * Word of warning:
 >   This should not be done unless all handles are really finished with.
 >   Otherwise someone will just end up adding something else and that
 >   is likely to be leaked.
 */
void ThunkHandleManager_DeInitialize(_Inout_ ThunkHandleManager *manager)
{
    SListEntry *item = NULL;
    do
    {
        item = SList_PopAtomic(&manager->freeList);
        if (item)
        {
            _aligned_free(item);
        }
    } while (item != NULL);
}

/* PRIVATE: RecycleHandle except it only called from RealHandle.
 * RecycleHandle is not called by anything but the RealHandle itself.
 * Not following this rule is likely to cause problems.  The refcount
 * on the object must get to zero before it is safe to put it back
 * in the free-list.  
 */
void ThunkHandleManager_RecycleHandle(_Inout_ ThunkHandle *thunkHandle)
{
    /* Invlidate this handle by bumping the thunk handle version */
    Atomic_Inc(&thunkHandle->version);

    /* Add thunk handle to free list */
    SList_PushAtomic(&thunkHandle->handleManager->freeList, &thunkHandle->u.freeListData);
}

/* PUBLIC: GetHandle
 * Application that needs a new handle will case this.  It will get one
 * from the free-list if one is available, otherwise it allocates and
 * initializes it.
 * There is a bootstrapping problem for the Application that means we
 * may need to allocate a handle even through there is no free-list.
 * RETURN: 0 = failed, 1 = succeeded
 */
MI_Result ThunkHandleManager_GetHandle(_Inout_ ThunkHandleManager *manager, _Outptr_ ThunkHandle **thunkHandle)
{
    /* Get handle from list if there is any there */
    *thunkHandle = (ThunkHandle*) SList_PopAtomic(&manager->freeList);
    if (*thunkHandle == NULL)
    {
        /* Not there, allocate a new one using alligned memory */
        *thunkHandle = (ThunkHandle *) _aligned_malloc(sizeof(ThunkHandle), MEMORY_ALLOCATION_ALIGNMENT);
        if (*thunkHandle)
        {
            ThunkHandle_Initialize(*thunkHandle, manager, MI_TRUE);
        }
        else
        {
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }
    }
    else
    {
        ThunkHandle_Initialize(*thunkHandle, manager, MI_FALSE);
    }

    return MI_RESULT_OK;
}

/* Defines for the RealHandle for determining if it has
 * been shutdown or not.
 */
#define ActiveBit 0x80000000
#define CountMask 0x7fffffff

/* PRIVATE: RealHandle_Initialize, except should only ever be called from free-list
 * Initialize the RealHandle structure
 */
void ThunkHandle_Initialize(_Inout_ ThunkHandle *thunkHandle, _Inout_ ThunkHandleManager *manager, MI_Boolean firstTime)
{
    ptrdiff_t version = 1;
    if (MI_FALSE == firstTime)
    {
        version = thunkHandle->version;
    }

    memset(thunkHandle, 0, sizeof(ThunkHandle));
    thunkHandle->version = version;
    thunkHandle->refcount = (ptrdiff_t)(ActiveBit + 1);
    thunkHandle->handleManager = manager;
}

/* PUBLIC: RealHandle_AddRef
 * Bump the refcount on the object.  This can fail if shutdown
 * has already been called.  Return code MUST ALWAYS be called.
 */
_Check_return_ int ThunkHandle_AddRef(_Inout_ ThunkHandle *thunkHandle)
{
    ptrdiff_t n;
    for (n = thunkHandle->refcount; n & ActiveBit; n = thunkHandle->refcount)
    {
        if (Atomic_CompareAndSwap(&thunkHandle->refcount, n, n + 1) == n)
        {
            /*We incremented the count and we weren't cancelled so return success.*/
            trace_MIIncreaseRefcountForThunkHandle(thunkHandle);
            return 1;
        }
    }
    /*Another thread called Shutdown() so return false.*/
    trace_MIThunkAfterShutdown(thunkHandle);
    return 0;
}

_Check_return_ int ThunkHandle_AddRef_ForCompletionCallback(_Inout_ ThunkHandle *thunkHandle)
{
    ptrdiff_t n;
    /* Checking for atleast one reference before increasing the refcount, irrespective of acitve bit set or not */
    for (n = thunkHandle->refcount; n & (~ActiveBit); n = thunkHandle->refcount)
    {
        if (Atomic_CompareAndSwap(&thunkHandle->refcount, n, n + 1) == n)
        {
            /*We incremented the count and we weren't cancelled so return success.*/
            trace_MIIncreaseRefcountForThunkHandle(thunkHandle);
            return 1;
        }
    }
    /*Another thread called Shutdown() so return false.*/
    trace_MIThunkAfterShutdown(thunkHandle);
    return 0;
}

/* PUBLIC: RealHandle_Release
 * Atomically releases a reference.
 * Once all AddRef() calls have been released and Shutdown() is called,
 * the last thread out recycles the handle
 */
long ThunkHandle_Release(_Inout_ ThunkHandle *thunkHandle)
{
    ptrdiff_t n;

    //NitsAssert(thunkHandle->refcount, L"invalid refcount");
    
    n = Atomic_Dec(&thunkHandle->refcount);

    if (n == 0)
    {
        trace_MIReleaseThunkHandle(thunkHandle);

        /* Copy so can recycle before calling destructor */
        ThunkHandle tmpHandle = *thunkHandle;

        /* Object is now free to add back to pool and bump version number */
        ThunkHandleManager_RecycleHandle(thunkHandle);

        /* Call the destructor to tear down the thunked object */
        if (tmpHandle.destructor)
        {
            tmpHandle.destructor(&tmpHandle);
        }

    }

    trace_MIDecreaseRefcountWithoutReleaseThunkHandle(thunkHandle);

    return n & CountMask;
}

/* PUBLIC: RealHandle_Shutdown
 * Atomically sets the object to the cancelled state.
 * The first thread releases the reference from the
 * constructor. 
 */
int ThunkHandle_Shutdown(
    _Inout_ ThunkHandle *handle, 
    _In_opt_ void (*destructor)(_In_ ThunkHandle *thunkHandle))
{
    ptrdiff_t n;
    
    trace_MIShuttingDownThunkHandle(handle);

    for (n = handle->refcount; n & ActiveBit; n = handle->refcount)
    {
        if (Atomic_CompareAndSwap(&handle->refcount, n, n & CountMask) == n)
        {
            /* We cleared ActiveBit. This code runs only once. */
            handle->destructor = destructor;
            ThunkHandle_Release(handle);
            return 1;
        }
    }

    /*Another thread cleared ActiveBit.*/
    trace_MIThunkAfterThunkHandleRelease(handle);
    return 0;
}


void ThunkHandle_FromGeneric(_Inout_ GenericHandle *genericHandle, _Outptr_result_maybenull_ ThunkHandle **thunkHandle)
{
    *thunkHandle = NULL;

    if (genericHandle->thunkHandle == NULL)
    {
        /* invalid handle */
        trace_MIThunk_InvalidHandle(genericHandle);
        return;
    }
    if (genericHandle->version != genericHandle->thunkHandle->version)
    {
        /* invalid handle version */
        trace_MIThunk_OldVersion(genericHandle);
        return;
    }

    if (!ThunkHandle_AddRef(genericHandle->thunkHandle))
    {
        /* Handle is shutdown */
        trace_MIThunk_AlreadyShutdown(genericHandle);
        return;
    }

    if (genericHandle->version != genericHandle->thunkHandle->version)
    {
        /* Need another version check */
        trace_MIThunk_OldVersion(genericHandle);
        return;
    }

    *thunkHandle = genericHandle->thunkHandle;
    trace_MIGetThunkHandleFromGenericHandle(thunkHandle, genericHandle);
}

void ThunkHandle_FromGeneric_ForCompletionCallback(_Inout_ GenericHandle *genericHandle, _Outptr_result_maybenull_ ThunkHandle **thunkHandle)
{
    *thunkHandle = NULL;

    if (genericHandle->thunkHandle == NULL)
    {
        /* invalid handle */
        trace_MIThunk_InvalidHandle(genericHandle);
        return;
    }
    if (genericHandle->version != genericHandle->thunkHandle->version)
    {
        /* invalid handle version */
        trace_MIThunk_OldVersion(genericHandle);
        return;
    }

    if (!ThunkHandle_AddRef_ForCompletionCallback(genericHandle->thunkHandle))
    {
        /* Handle is shutdown */
        trace_MIThunk_AlreadyShutdown(genericHandle);
        return;
    }

    if (genericHandle->version != genericHandle->thunkHandle->version)
    {
        /* Need another version check */
        trace_MIThunk_OldVersion(genericHandle);
        return;
    }

    *thunkHandle = genericHandle->thunkHandle;
    trace_MIGetThunkHandleFromGenericHandle(thunkHandle, genericHandle);
}

