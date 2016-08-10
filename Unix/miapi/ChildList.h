/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _miapi_childlist_h_
#define _miapi_childlist_h_
#include <MI.h>
#include "SafeHandle.h"
#include <pal/lock.h>
#include <pal/atomic.h>

typedef struct _ChildListNode
{
    struct _ChildListNode *left;
    struct _ChildListNode *right;
    GenericHandle clientHandle;     /* Client handle for object so Cancel can be called on it */
}
ChildListNode;

typedef struct _ChildListOutstandingHandles
{
    GenericHandle clientHandle;     /* Client handle for object so Cancel can be called on it */
    GenericHandle *debugHandlePointer;  /* Pointer of original for debugging purposes only, do not dereference it as it may be invalid */
} 
ChildListOutstandingHandles;

typedef struct _ChildList
{
    ChildListNode *headNode;
    volatile ptrdiff_t childCount;
    volatile MI_Boolean shutdown;
    CachedLock lock;

    void (*shutdownCompleteCallback)(void *context);
    void *shutdownCompleteCallbackContext;
}
ChildList;

MI_INLINE MI_Result ChildList_Initialize(_Out_ ChildList *list)
{
    memset(list, 0, sizeof(ChildList));
    if (CachedLock_Init(&list->lock, CACHEDLOCK_FLAG_SHARED) == 0)
    {
        return MI_RESULT_OK;
    }
    else
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
}
MI_INLINE void ChildList_DeInitialize(_Inout_ ChildList *list)
{
    CachedLock_Destroy(&list->lock);
}

MI_INLINE MI_Result ChildList_AddNode(_Inout_ ChildList *list, _Inout_ ChildListNode *newNode)
{
    MI_Result retValue = MI_RESULT_OK;

    if (!list->shutdown)
    {
        CachedLock_AcquireWrite(&list->lock);

        if (!list->shutdown)
        {
            Atomic_Inc(&list->childCount);

            /* previous head point left points to new node */
            if (list->headNode)
            {
                list->headNode->left = newNode;
            }
            /* new node point to previous head */
            newNode->left = NULL;
            newNode->right = list->headNode;

            /* set list head node to new node */
            list->headNode = newNode;
        }
        else
        {
            retValue = MI_RESULT_SERVER_IS_SHUTTING_DOWN;
        }

        CachedLock_ReleaseWrite(&list->lock);
    }
    else
    {
        retValue = MI_RESULT_SERVER_IS_SHUTTING_DOWN;
    }

    return retValue;
}

MI_INLINE void ChildList_RemoveNode(_Inout_ ChildList *list, _In_ ChildListNode *removeNode)
{
    int makeShutdownCallbackNow = 0;

    CachedLock_AcquireWrite(&list->lock);

    if (list->headNode == removeNode)
    {
        list->headNode = removeNode->right;
    }
    if (removeNode->left)
    {
        removeNode->left->right = removeNode->right;
    }
    if (removeNode->right)
    {
        removeNode->right->left = removeNode->left;
    }

    if ((Atomic_Dec(&list->childCount) == 0) &&
        list->shutdown &&
        list->shutdownCompleteCallback)
    {
        makeShutdownCallbackNow = 1;
    }

    CachedLock_ReleaseWrite(&list->lock);

    if (makeShutdownCallbackNow)
    {
        list->shutdownCompleteCallback(list->shutdownCompleteCallbackContext);
    }
}

/* Shutdown returns a list of generic handles that are still in the list.  These are not pointers to th handles (except the debug pointer)
 * so if the handle gets closed these handles will not cause a crashes
 */
MI_INLINE int ChildList_Shutdown(_Inout_ ChildList *list)
{
    int returnVal = 0;
    CachedLock_AcquireWrite(&list->lock);

    if (list->shutdown == MI_FALSE)
    {
        list->shutdown = MI_TRUE;
        returnVal = 1;
    }

    CachedLock_ReleaseWrite(&list->lock);

    return returnVal;
}

_Success_(return == 1)
MI_INLINE int ChildList_GetCurrentList(_Inout_ ChildList *list, _Out_cap_post_count_(inboundSize, *outboundUsed) ChildListOutstandingHandles *outstandingHandles, ptrdiff_t inboundSize, _Out_ ptrdiff_t *outboundUsed)
{
    int returnVal = 0;
    CachedLock_AcquireWrite(&list->lock);

    *outboundUsed = 0;

    if (inboundSize >=  list->childCount)
    {
        ChildListNode *currentNode = list->headNode;
        (*outboundUsed) = 0;
        while (currentNode && 
            ((*outboundUsed) < inboundSize))    //redumbdant check to shut prefast up, it does not know list->childCount is how many items in list
        {
            outstandingHandles[*outboundUsed].clientHandle = currentNode->clientHandle;
            outstandingHandles[*outboundUsed].debugHandlePointer = &currentNode->clientHandle;
            
            currentNode = currentNode->right;
            (*outboundUsed) ++;
        }
        if ((*outboundUsed) < inboundSize)
        {
            returnVal = 1;
        }
        else
        {
            //never happen!
            (*outboundUsed) = 0;
        }
    }
    else
    {
        *outboundUsed = list->childCount;
    }

    CachedLock_ReleaseWrite(&list->lock);

    return returnVal;
}


MI_INLINE void ChildList_RegisterShutdownCallback(
    _Inout_ ChildList *list,
    _In_ void (*shutdownCompleteCallback)(void *context),
    _In_ void *shutdownCompleteCallbackContext)
{
    int makeShutdownCallbackNow = 0;

    CachedLock_AcquireWrite(&list->lock);

    if ((list->shutdown == MI_TRUE) &&
        (list->childCount == 0))
    {
        makeShutdownCallbackNow = 1;
    }
    else
    {
        list->shutdownCompleteCallbackContext = shutdownCompleteCallbackContext;
        list->shutdownCompleteCallback = shutdownCompleteCallback;
    }

    CachedLock_ReleaseWrite(&list->lock);

    if (makeShutdownCallbackNow)
    {
        shutdownCompleteCallback(shutdownCompleteCallbackContext);
    }

}
#endif /* _miapi_childlist_h_ */
