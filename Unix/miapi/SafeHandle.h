/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _miapi_safehandle_h_
#define _miapi_safehandle_h_
#include <MI.h>
#include <common/linux/sal.h>
#include <pal/slist.h>

/* Thunk handle manager */
typedef struct _ThunkHandleManager 
{
    SListHead freeList;
}
ThunkHandleManager;

/* Generic version of the client handle */
typedef struct _GenericHandle
{
    MI_Uint64  version;
    struct _ThunkHandle *thunkHandle;
    void *functionTable;
} 
GenericHandle;

/* Thunk handle sits inbetween the clients handle and the real object that the handle represents */

typedef struct _ThunkHandle ThunkHandle;
struct _ThunkHandle
{
    union
    {
        SListEntry freeListData; /* When free, object is in free list  */
        void *object; /* When allocated, object points to real session/operation/etc */
    } u;

    /* Handle version number.  When accessing handle this is compared with generic handle version to make sure it matches */
    volatile ptrdiff_t version; 

    ThunkHandleManager *handleManager; /* So we know where this object goes when freed */

    volatile ptrdiff_t refcount; /* Refcount & shutdown */

    /* Called when the recount goes to zero which means it was also cancelled (shutdown) */
    void (*destructor)(_In_ ThunkHandle *thunkHandle);
};

/* PUBLIC functions for RealHandleFreeList */
void ThunkHandleManager_Initialize(_Inout_ ThunkHandleManager *freeList);
void ThunkHandleManager_DeInitialize(_Inout_ ThunkHandleManager *freeList);

MI_Result ThunkHandleManager_GetHandle(_Inout_ ThunkHandleManager *self, _Outptr_ ThunkHandle **thunkHandle);

/* PUBLIC functions for RealHandle */
_Check_return_ int ThunkHandle_AddRef(_Inout_ ThunkHandle *thunkHandle);
long ThunkHandle_Release(_Inout_ ThunkHandle *thunkHandle);
int ThunkHandle_Shutdown(_Inout_ ThunkHandle *thunkHandle, _In_opt_ void (*destructor)(_In_ ThunkHandle *thunkHandle));

/* Safely return thunk handle from a generic form.  Call ThunkHandle_Release when finished */
void ThunkHandle_FromGeneric(_Inout_ GenericHandle *genericHandle, _Outptr_result_maybenull_ ThunkHandle **thunkHandle);
void ThunkHandle_FromGeneric_ForCompletionCallback(_Inout_ GenericHandle *genericHandle, _Outptr_result_maybenull_ ThunkHandle **thunkHandle);

#endif /* _miapi_safehandle_h_ */

