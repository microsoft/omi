/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _unsubscribe_h
#define _unsubscribe_h

#include <common.h>
#include <pal/lock.h>
#include <pal/thread.h>
#include "SubscriptionContext.h"
#include "provmgr.h"

BEGIN_EXTERNC

typedef struct _RequestItem     RequestItem;
typedef struct _RequestList     RequestList;
typedef struct _RequestHandler  RequestHandler;

typedef enum _RequestType
{
    REQUEST_UNSUBSCRIBE      =  1,
    REQUEST_SUBSCRIBE        =  2
}
RequestType;

struct _RequestItem
{
    struct _RequestItem* next;
    RequestType type;
};

typedef struct _UnsubscribeProviderItem
{
    RequestItem base;
    SubscriptionContext* ctx;
    MI_Boolean invokeRequest;
    MI_Result finalResult;
}
UnsubscribeProviderItem;

typedef struct _SubscribeProviderItem
{
    RequestItem base;
    Provider* provider;
    SubscribeReq* msg;
    SubscriptionContext* subscrContext;
}
SubscribeProviderItem;

struct _RequestList
{
    // Linked list of pending unsubscribe requests
    struct _RequestItem* head;
    struct _RequestItem* tail;

    // Protect the linked list
    ReadWriteLock lock;
};

struct _RequestHandler
{
    Lock lock; // thread safely create unsubscribe thread
    volatile ptrdiff_t running; // indication the thread is running (1) or not (0)
    Thread thread; // the unsubscribe thread
    volatile ptrdiff_t joined; // indication the thread is joined by other thread (1) or not (0)
    RequestList list; // pending unsubscribe requests
};

extern RequestHandler g_requesthandler;

void RequestList_Init(_Out_ RequestList* list);

void RequestHandler_Init(_Out_ RequestHandler* handler);
void RequestHandler_Finalize(_Inout_ RequestHandler* handler);

//
// Queue the unsubscribe request and spawn a new thread to
// perform the unsubscribe operation if not created yet
//
MI_Result Schedule_UnsubscribeProvider(
    _In_ SubscriptionContext* ctx,
    _In_ MI_Boolean invokeRequest,
    _In_ MI_Result finalResult);

//
// Queue sending final result request and spawn a new thread to
// perform the unsubscribe operation if not created yet
//
MI_Result Schedule_SendFinalResult(
    _In_ SubscriptionContext* ctx,
    _In_ MI_Result finalResult);

//
// Queue subscribe request and spawn a new thread to
// perform the unsubscribe operation if not created yet
//
MI_Result Schedule_SubscribeRequest(
    _In_ Provider* provider,
    _In_ SubscribeReq* msg,
    _In_ SubscriptionContext* subscrContext );

END_EXTERNC

#endif /* _unsubscribe_h */

