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

#include "selector.h"
#include <base/time.h>
#include "thread.h"
#include <base/log.h>
#include <base/result.h>
#include <base/atomic.h>

#include "config.h"
#include <common.h>
#include <base/batch.h>

// #define ENABLE_TRACING
// #define TRACING_LEVEL 4
#include <logging.h>

/* maximum number of items in the list */
#define LIST_SIZE_LIMIT 321

/* maximum instances that can be allocated */
#define MAX_ALLOCATED_INSTANCES 500

// The socket error
extern int LastSocketError;

/*
**==============================================================================
**
**
** Windows Implementation
**
**
**==============================================================================
*/
#if defined(CONFIG_OS_WINDOWS)
# include <winsock2.h>

/* Notification internal datastructure */
typedef struct _SelectorCallbacksItem
{
    /* Links for inserting messages onto linked-lists */
    struct _SelectorCallbacksItem* next;
    struct _SelectorCallbacksItem* prev;

    Selector_NotificationCallback callback;
    void* callback_self;
    /* message has to be add-refed when added and dec-refed upon callback invocation */
    Message* message;
}
SelectorCallbacksItem;

typedef struct _SelectorCallbacksList
{
    /* Linked list of callbacks to call */
    ListElem* head;
    ListElem* tail;
    int numberOfItem;    /**/
}
SelectorCallbacksList;

typedef struct _SelectorRep
{
    /* Linked list of event watchers */
    ListElem* head;
    ListElem* tail;

    /* Object for detecting socket events */
    WSAEVENT event;

    /* other thread notification */
    HANDLE  callbacksAreAvailable;

    /* list object - never referred directly - only using a pointer */
    SelectorCallbacksList __callback_list_object;
    /* list of callbacks to notify ;
    storing pointer here, so we can use interlock funciotns for list updating
    */
    SelectorCallbacksList*  callbacksList;

    /* Number of alive instance */
    AtomicInt outstandingInstances;

    /* io thread id */
    ThreadHandle ioThreadHandle;

    /* flag to stop running */
    MI_Boolean keepRunning;

    /* flag that allows empty selector running
        when empty selector runs, it only can be interrupted by
        internal funcitons, since it has no sockets to monitor
        */
    MI_Boolean allowEmptySelector;
}
SelectorRep;

static SelectorCallbacksList* _GetList(
    SelectorRep* rep)
{
    SelectorCallbacksList* list;

    list = InterlockedExchangePointer(&rep->callbacksList, 0);

    while (list == NULL)
    {
        usleep(50);
        list = InterlockedExchangePointer(&rep->callbacksList, 0);
    }

    return list;
}

static void _SetList(
    SelectorRep* rep, SelectorCallbacksList* list)
{
    InterlockedExchangePointer(&rep->callbacksList, list);
}

static MI_Result _SetSockEvents(
    WSAEVENT event,
    SOCKET sock,
    MI_Uint32 mask)
{
    long e = 0;

    if ((mask & SELECTOR_READ) != 0)
    {
        e |= FD_ACCEPT | FD_READ | FD_CLOSE;
    }

    if (mask & SELECTOR_WRITE)
    {
        e |= FD_WRITE | FD_CONNECT;
    }

    if (mask & SELECTOR_EXCEPTION)
    {
        e |= FD_OOB;
    }

    if (WSAEventSelect(sock, event, e) == SOCKET_ERROR)
    {
        return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
}

static MI_Result _GetSockEvents(
    WSAEVENT event,
    SOCKET sock,
    MI_Uint32* mask)
{
    WSANETWORKEVENTS networkEvents;
    long x;

    memset(&networkEvents, 0, sizeof (networkEvents));

    if (WSAEnumNetworkEvents(sock, event, &networkEvents) != 0)
    {
        return MI_RESULT_FAILED;
    }

    x = networkEvents.lNetworkEvents;
    *mask = 0;

    if (x & FD_ACCEPT || x & FD_READ || x & FD_CLOSE || x & FD_CONNECT)
    {
        *mask |= SELECTOR_READ;
    }

    if (x & FD_WRITE)
    {
        *mask |= SELECTOR_WRITE;
    }

    if (x & FD_OOB)
    {
        *mask |= SELECTOR_EXCEPTION;
    }

    return MI_RESULT_OK;
}

MI_Result Selector_Init(
    Selector* self)
{
    SelectorRep* rep = (SelectorRep*)calloc(1, sizeof(SelectorRep));

    if (rep == NULL)
    {
        return MI_RESULT_FAILED;
    }

    rep->event = WSACreateEvent();

    if (rep->event == WSA_INVALID_EVENT)
    {
        free(rep);
        rep = NULL;
        return MI_RESULT_FAILED;
    }

    rep->callbacksList = &rep->__callback_list_object;

    rep->callbacksAreAvailable = CreateEvent(0, TRUE, FALSE, NULL);

    if (rep->callbacksAreAvailable == NULL)
    {
        CloseHandle(rep->event);
        free(rep);
        rep = NULL;
        return MI_RESULT_FAILED;
    }


    self->rep = rep;
    return MI_RESULT_OK;
}

void Selector_Destroy(
    Selector* self)
{
    SelectorRep* rep = (SelectorRep*)self->rep;
    Handler* p;
    Handler* next;

    /* Free all watchers */
    for (p = (Handler*)rep->head; p; )
    {
        next = (Handler*)p->next;

        /* Unselect events on this socket */
        _SetSockEvents(rep->event, p->sock, 0);

        /* Invoke user callback */
        if (p != NULL && p->callback != NULL && *p->callback != NULL)
        {
            (*p->callback)(self, p, SELECTOR_DESTROY, 0);
        }

        p = next;
    }

    CloseHandle(rep->event);
    CloseHandle(rep->callbacksAreAvailable);

    /* free messages in callbacks list */
    while (rep->callbacksList->head != NULL)
    {
        SelectorCallbacksItem* item = (SelectorCallbacksItem*)rep->callbacksList->head;

        List_Remove(&rep->callbacksList->head, &rep->callbacksList->tail, (ListElem*)item);
        Message_Release(item->message);
    }

    free(rep);
    rep = NULL;
}

MI_Result Selector_AddHandler(
    Selector* self,
    Handler* handler)
{
    SelectorRep* rep = (SelectorRep*)self->rep;
    Handler* p;
    MI_Uint64 currentTimeUsec;

    if (Time_Now(&currentTimeUsec) != MI_RESULT_OK)
    {
        return MI_RESULT_FAILED;
    }

    /* Reject duplicates */
    for (p = (Handler*)rep->head; p != NULL; p = (Handler*)p->next)
    {
        if (p == handler)
        {
            return MI_RESULT_ALREADY_EXISTS;
        }
    }

    /* Add new handler to list */
    List_Append(&rep->head, &rep->tail, (ListElem*)handler);

    if (handler->callback != NULL)
    {
        (*handler->callback)(self, handler, SELECTOR_ADD, currentTimeUsec);
    }

    return MI_RESULT_OK;
}

MI_Result Selector_RemoveHandler(
    Selector* self,
    Handler* handler)
{
    SelectorRep* rep = (SelectorRep*)self->rep;
    Handler* p;

    /* Find and remove handler from list */
    for (p = (Handler*)rep->head; p != NULL; p = (Handler*)p->next)
    {
        if (p == handler)
        {
            /* Remove handler */
            List_Remove(&rep->head, &rep->tail, (ListElem*)p);

            /* Unselect events on this socket */
            _SetSockEvents(rep->event, p->sock, 0);

            /* Notify handler of removal */
            if (handler->callback != NULL && p != NULL)
            {
                (*handler->callback)(self, p, SELECTOR_REMOVE, 0);
            }

            return MI_RESULT_OK;
        }
    }

    return MI_RESULT_NOT_FOUND;
}

MI_Result Selector_RemoveAllHandlers(
    Selector* self)
{
    SelectorRep* rep = (SelectorRep*)self->rep;
    Handler* p;

    /* Find and remove handler from list */
    for (p = (Handler*)rep->head; p != NULL; )
    {
        Handler* next = p->next;

        /* Remove handler */
        if (rep != NULL && rep->head != NULL && rep->tail != NULL)
        {
            List_Remove(&rep->head, &rep->tail, (ListElem*)p);
        }

        /* Unselect events on this socket */
        _SetSockEvents(rep->event, p->sock, 0);

        /* Notify handler of removal */
        if (p != NULL && p->callback != NULL)
        {
            (*p->callback)(self, p, SELECTOR_REMOVE, 0);
        }

        p = next;
    }

    return MI_RESULT_OK;
}

static void _ProcessCallbacks(
    SelectorRep* rep)
{
    SelectorCallbacksItem* item = NULL;
    SelectorCallbacksList * list;

    /* remove all items from the list */
    list = _GetList(rep);
    item = (SelectorCallbacksItem*)list->head;
    list->head = list->tail = 0;
    list->numberOfItem = 0;
    ResetEvent(rep->callbacksAreAvailable);
    _SetList(rep, list);

    /* process all items */
    while (item != NULL)
    {
        SelectorCallbacksItem* next = item->next;

        if (item->callback != NULL)
        {

            (*item->callback)(item->callback_self, item->message);
        }
        Message_Release(item->message);
        item = next;
    }
}

MI_Result Selector_Run(
    Selector* self,
    MI_Sint64 timeoutUsec)
{
    SelectorRep* rep = (SelectorRep*)self->rep;
    MI_Uint64 timeoutSelectorAt = TIME_NEVER;
    HANDLE handles[2];

    handles[0] = rep->event;
    handles[1] = rep->callbacksAreAvailable;

    LOGD2((ZT("Selector_Run - handle[0]: %d, handle[1]: %d, timeoutUsec: %ld"), handle[0], handle[1], (long)timeoutUsec));

    if (timeoutUsec > 0)
    {
        if (Time_Now(&timeoutSelectorAt) != MI_RESULT_OK)
        {
            LOGE2((ZT("Selector_Run - Time_Now failed")));
            return MI_RESULT_FAILED;
        }

        /* calculate when to terminate selector */
        LOGD2((ZT("Selector_Run - After timeout calculation. time now: %s, timeoutSelectorAt: %s"), FmtTime(timeoutSelectorAt), FmtTime(timeoutSelectorAt + timeoutUsec)));
        timeoutSelectorAt += timeoutUsec;
    }

    rep->ioThreadHandle = ThreadSelf();

    for (rep->keepRunning = MI_TRUE; rep->keepRunning != MI_FALSE;)
    {
        Handler* p;
        DWORD result;
        DWORD timeoutMsec;
        MI_Result r;
        MI_Boolean more;
        MI_Uint64 currentTimeUsec = 0;
        MI_Uint64 breakCurrentSelectAt = TIME_NEVER;

        if (MI_RESULT_OK != Time_Now(&currentTimeUsec))
        {
            LOGE2((ZT("Selector_Run - Time_Now failed")));
            return MI_RESULT_FAILED;
        }

        if (timeoutSelectorAt !=  TIME_NEVER)
        {
            if (currentTimeUsec >= timeoutSelectorAt)
            {
                LOGW2((ZT("Selector_Run - Selector timeout. current time: %s, limit time: %s, interval: %ld ms"),
                        FmtTime(timeoutSelectorAt), FmtTime(currentTimeUsec),
                        (long)(currentTimeUsed - timeoutSelectorAt)));
                return MI_RESULT_TIME_OUT;
            }

            breakCurrentSelectAt = timeoutSelectorAt;
        }

        /* calculate timeout */
        for (p = (Handler*)rep->head; p != NULL; )
        {
            Handler* next = p->next;

            /* update event mask */
            if (p->sock != INVALID_SOCK)
            {
                r = _SetSockEvents(rep->event, p->sock, p->mask);

                if (r != MI_RESULT_OK)
                {
                    LOGE2((ZT("Selector_Run - _SetSockEvents failed")));
                    return r;
                }
            }

            /* find the minimum timeout from the list */
            if (p->fireTimeoutAt != TIME_NEVER)
            {
                /* if expired - don't wait; notification will be issued later in next loop */
                if (currentTimeUsec >= p->fireTimeoutAt)
                {
                    breakCurrentSelectAt = currentTimeUsec;
                }
                else if (p->fireTimeoutAt < breakCurrentSelectAt)
                {
                    breakCurrentSelectAt = p->fireTimeoutAt;
                }
            }

            p = next;
        }

        /* empty list - return */
        if (rep->head == NULL && !rep->allowEmptySelector)
        {
            LOGE2((ZT("Selector_Run - Empty list")));
            return MI_RESULT_FAILED;
        }

        /* Wait for events on any of the sockets */

        timeoutMsec =
            (breakCurrentSelectAt == ((MI_Uint64)-1) ) ? /* do we have at least one valid timeout? */
                                        INFINITE :
                                        (DWORD)((breakCurrentSelectAt - currentTimeUsec) /
                                      1000);
        result = WaitForMultipleObjectsEx(MI_COUNT(handles), handles, FALSE, timeoutMsec, FALSE);
        if (result == WAIT_FAILED)
        {
            LOGE2((ZT("Selector_Run - Wait failed. result: %d (%s)"), (int)result, mistrerror(result)));
            return MI_RESULT_FAILED;
        }

        //if ((WAIT_OBJECT_0 + 1) == result)  /* other thread wants to call callback */
        _ProcessCallbacks(rep);

        if (MI_RESULT_OK != Time_Now(&currentTimeUsec))
        {
            LOGE2((ZT("Selector_Run - Time_Now failed")));
            return MI_RESULT_FAILED;
        }

        /* Dispatch events on each socket */
        for (p = (Handler*)rep->head; p != NULL; )
        {
            Handler* next = p->next;
            MI_Uint32 mask = 0;

            /* Get event mask for this socket */
            if (p->sock != INVALID_SOCK)
            {
                r = _GetSockEvents(rep->event, p->sock, &mask);

                if (r != MI_RESULT_OK)
                {
                    PRINTF(("Selector_Run - _GetSockEvents failed. socket: %d, error: %d (%s)"), p->sock, (int)r, mistrerror(r)));
                    return r;
                }
            }

            if (TIME_NEVER != p->fireTimeoutAt && currentTimeUsec >= p->fireTimeoutAt)
            {
                LOGE2((ZT("Selector_Run - Socket timeout. socket: %d, current time: %s, limit time: %s, difference: %ld usec."),
                      p->sock, FmtTime(currentTimeUsec), FmtTime(p->fireTimeoutAt), (long)(currentTimeUsed - timeoutSelectorAt)));
                mask |= SELECTOR_TIMEOUT;
            }

            /* If there were any events on this socket, dispatch them */
            if (mask != 0)
            {
                /*MI_Uint32 oldMask = p->mask;*/

                if (p != NULL && p->callback != NULL)
                {
                    more = (*p->callback)(self, p, mask, currentTimeUsec);

                    /* If callback wants to continue getting events */
                    if (!more)
                    {
                        /* Remove handler */
                        if (rep != NULL && rep->head != NULL && rep->tail != NULL)
                        {
                            List_Remove(&rep->head, &rep->tail, (ListElem*)p);
                        }

                        /* Unselect events on this socket */
                        _SetSockEvents(rep->event, p->sock, 0);

                        /* Notify handler of removal */
                        (*p->callback)(self, p, SELECTOR_REMOVE, currentTimeUsec);
                    }
                }
            }

            p = next;
        }
    }
    return MI_RESULT_OK;
}

/* Wakes up selector's thread
    Typical usage is to recalculate timeouts on handlers
    when selector's Run is running in different thread */
MI_Result Selector_Wakeup(
    Selector* self)
{
    SelectorRep* rep = (SelectorRep*)self->rep;

    /* notify running thread (if different) */
    if (rep->ioThreadHandle != ThreadSelf())
    {
        SetEvent(rep->callbacksAreAvailable);
    }

    return MI_RESULT_OK;
}

MI_Result Selector_StopRunning(
    Selector* self)
{
    SelectorRep* rep = (SelectorRep*)self->rep;

    rep->keepRunning = MI_FALSE;

    return Selector_Wakeup(self);
}

/*
    * This function guaranties that callback is called in 'Run'/'IO' thread context,
    * so no locking is required for accessing sokcet objects, updating buffers etc
*/
MI_Result Selector_CallInIOThread(
    Selector* self,
    Selector_NotificationCallback callback,
    void* callback_self,
    Message* message)
{
    SelectorRep* rep = (SelectorRep*)self->rep;
    SelectorCallbacksItem* newItem;
    SelectorCallbacksList* list;
    int itemsInList;

    assert(callback != NULL);

    if (rep->ioThreadHandle == ThreadSelf())
    {
        /* direct call - we can write to socket instantly */
        LOGD2((ZT("Selector_CallInIOThread - Calling in same thread")));

        if (callback != NULL)
        {
            (*callback)(callback_self, message);
        }
        return MI_RESULT_OK;
    }

    /* add item to the list and set event */
    newItem = (SelectorCallbacksItem*)Batch_GetClear(message->batch, sizeof (SelectorCallbacksItem));

    if (newItem == NULL)
    {
        LOGE2((ZT("Selector_CallInIOThread - Error. Unable to find free entry in item queue")));
        return MI_RESULT_FAILED;
    }

    newItem->callback = callback;
    newItem->callback_self = callback_self;
    newItem->message = message;

    Message_AddRef(message);
    list = _GetList(rep);
    List_Append(&list->head, &list->tail, (ListElem*)newItem);
    list->numberOfItem++;
    itemsInList = list->numberOfItem;
    _SetList(rep, list);
    list = NULL;
    SetEvent(rep->callbacksAreAvailable);

    LOGD2((ZT("Selector_CallInIOThread - Queue size after adding item: %d"), rep->outstandingInstances));

    while (rep->outstandingInstances > MAX_ALLOCATED_INSTANCES)
    {
        Sleep_ms(1);
    }

#if 0
    /* wait until list is empty to avoid memory explosion */
    for (i = 0; itemsInList > LIST_SIZE_LIMIT && i < 500; i++)
    {
        Sleep(1);
        list = _GetList(rep);
        itemsInList = list->numberOfItem;
        _SetList(rep, list);
    }
#endif

    return MI_RESULT_OK;
}

#endif /* defined(CONFIG_OS_WINDOWS) */

/*
**==============================================================================
**
**
** POSIX Implementation
**
**
**==============================================================================
*/

#if defined(CONFIG_POSIX)
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <sys/socket.h>
# include <netinet/tcp.h>
# include <netinet/in.h>
# include <sys/time.h>
# include <sys/types.h>
# include <netdb.h>
# include <fcntl.h>
# include <arpa/inet.h>

typedef struct _SelectorCallbacksItem
{
    Selector_NotificationCallback callback;
    void* callback_self;
    /* message has to be add-refed when added and dec-refed upon callback invocation */
    Message* message;
}
SelectorCallbacksItem;

typedef struct _SelectorRep
{
    /* File descriptor sets */
    fd_set readSet;
    fd_set writeSet;
    fd_set exceptSet;

    /* Linked list of event watchers */
    ListElem* head;
    ListElem* tail;

    /* notifications channel */
    int notificationSockets[2];

    /* Number of notification items in a queue */
    //AtomicInt queueLength;

    /* Number of alive instance */
    AtomicInt outstandingInstances;

    /* flag to stop running */
    MI_Boolean keepRunning;

    /* flag that allows empty selector running
        when empty selector runs, it only can be interrupted by
        internal funcitons, since it has no sockets to monitor
        */
    MI_Boolean allowEmptySelector;

    /* io thread id */
    ThreadHandle ioThreadHandle;
}
SelectorRep;

static int _Select(
    fd_set* readSet,
    fd_set* writeSet,
    fd_set* exceptSet,
    MI_Sint64 timeoutUsec)
{
    int n = FD_SETSIZE;
    struct timeval tv = {0, 0};
    struct timeval* _tv = NULL;         // wait for socket ready without timing out
    int numReady = -1;

    LOGX2((ZT("_Select - Selecting %d maximum sockets. timeout: %ld usec., R: {%s}, W: {%s}, E: {%s}"), n, (long)timeoutUsec, bitnumberstr(*(unsigned long*)readSet), bitnumberstr(*(unsigned long*)writeSet), bitnumberstr(*(unsigned long*)exceptSet)));
    if (timeoutUsec >= 0)
    {                                   // return on first ready socket or at timeout time
        LOGX2((ZT("_Select - Using timeout: %ld"), (long)timeoutUsec));
        // JWF -- If it's 1/100 second or less, make it 1/100 second.  Yes, this is a hack.  We don't want to poll.
        if (timeoutUsec < 10000)
        {
            LOGW2((ZT("_Select - timeout was less than 10 msec.  Resetting to 10 msec.")));
            timeoutUsec = 10000;
        }
        tv.tv_sec = (long)(timeoutUsec / 1000000);
        tv.tv_usec = timeoutUsec % 1000000;
        _tv = &tv;
    }

    if (_tv != NULL)
    {
        LOGX2((ZT("_Select - Selecting with timeout: %u.%06u sec."), (unsigned int)_tv->tv_sec, (unsigned int)_tv->tv_usec));
    }
    else
    {
        LOGD2((ZT("_Select - Selecting with timeout NULL")));
    }

    errno = 0;
    numReady = select(n, readSet, writeSet, exceptSet, _tv);
    LastSocketError = errno;
    if (_tv != NULL)
    {
        LOGX2((ZT("_Select - numReady: %d, timeout: %u.%06u sec."), numReady, (unsigned int)_tv->tv_sec, (unsigned int)_tv->tv_usec));
    }
    else
    {
        LOGD2((ZT("_Select - numReady: %d, timeout: NULL"), numReady));
    }

    return numReady;
}

void doSelectorMutexStuff(int Lock)
{
    static pthread_mutex_t thisMethodLock;
    static pthread_mutex_t selectorlock;
    static int mutexInitialized = 0;
    if (mutexInitialized == 0)
    {
        pthread_mutex_init(&selectorlock, NULL);
        pthread_mutex_init(&thisMethodLock, NULL);

        mutexInitialized = 1;
    }

try_again:
    pthread_mutex_lock(&thisMethodLock);

    if (Lock != 0)
    {
        int iStat = pthread_mutex_trylock(&selectorlock);
        if (iStat != 0)
        {
            if (iStat != EBUSY)
            {
                perror("   ** ERROR LOCKING SELECTOR MUTEX: ");
            }
            else
            {
                // printf("*** Attempt to lock locked mutex\n");
                pthread_mutex_unlock(&thisMethodLock);
                usleep(100);
                goto try_again;
            }
        }
    }
    else
    {
        if (0 != pthread_mutex_unlock(&selectorlock))
        {
            perror("   ** ERROR UNLOCKING MUTEX: ");
        }
    }

    pthread_mutex_unlock(&thisMethodLock);
}

void lockSelectorMutex()
{
    // printf("Entered --> lockMutex for socket %d.\n", Sock);
    doSelectorMutexStuff(1);
}

void unlockSelectorMutex()
{
    doSelectorMutexStuff(0);
}

void _FDSet(
    Sock sock,
    fd_set* set)
{
    if (sock != INVALID_SOCK)
    {
        FD_SET(sock, set);
    }
}

void _FDClr(Sock sock, fd_set* set)
{
    if (sock != INVALID_SOCK)
    {
        FD_CLR(sock, set);
    }
}

MI_Result Selector_Init(
    Selector* self)
{
    lockSelectorMutex();

    self->rep = (SelectorRep*)calloc(1, sizeof(SelectorRep));

    if (self->rep == NULL)
    {
        unlockSelectorMutex();
        return MI_RESULT_FAILED;
    }

    if (pipe(self->rep->notificationSockets) != 0)
    {
        unlockSelectorMutex();
        return MI_RESULT_FAILED;
    }

    /* set non-blocking for reader [0] */
    Sock_SetBlocking(self->rep->notificationSockets[0], MI_FALSE);

    /* Protect notification sockets from child processes */
    if (MI_RESULT_OK != Sock_SetCloseOnExec(self->rep->notificationSockets[0],MI_TRUE) ||
        MI_RESULT_OK != Sock_SetCloseOnExec(self->rep->notificationSockets[1],MI_TRUE))
    {
        LOGW((ZT("fcntl(F_SETFD) failed")));
    }

    unlockSelectorMutex();
    return MI_RESULT_OK;
}

void Selector_Destroy(Selector* self)
{
    lockSelectorMutex();

    SelectorRep* rep = (SelectorRep*)self->rep;
    Handler* p;
    Handler* next;

    /* Free all watchers */
    for (p = (Handler*)rep->head; p != NULL; )
    {
        next = (Handler*)p->next;
        if (p->callback != NULL)
        {
            (*p->callback)(self, p, SELECTOR_DESTROY, 0);
        }
        p = next;
    }

    // printf("Selector closing notification sockets %d and %d.", rep->notificationSockets[0], rep->notificationSockets[1]);
    Sock_Close(rep->notificationSockets[0]);
    Sock_Close(rep->notificationSockets[1]);

    free(rep);
    rep = NULL;
    unlockSelectorMutex();
}

MI_Result Selector_AddHandler(
    Selector* self,
    Handler* handler)
{
    SelectorRep* rep = (SelectorRep*)self->rep;
    Handler* p;
    MI_Uint64 currentTimeUsec;


    if (MI_RESULT_OK != Time_Now(&currentTimeUsec))
    {
        return MI_RESULT_FAILED;
    }

    /* Reject duplicates */
    for (p = (Handler*)rep->head; p != NULL; p = (Handler*)p->next)
    {
        if (p == handler)
        {
            return MI_RESULT_ALREADY_EXISTS;
        }
    }

    /* Add new handler to list */
    List_Append(&rep->head, &rep->tail, (ListElem*)handler);
    if (handler->callback != NULL)
    {
        (*handler->callback)(self, handler, SELECTOR_ADD, currentTimeUsec);
    }

    return MI_RESULT_OK;
}

MI_Result Selector_RemoveHandler(
    Selector* self,
    Handler* handler)
{
    SelectorRep* rep = (SelectorRep*)self->rep;
    Handler* p;

    /* Find and remove handler from list */
    for (p = (Handler*)rep->head; p != NULL; p = (Handler*)p->next)
    {
        if (p == handler)
        {
            /* Remove handler */
            if (rep != NULL && rep->head != NULL && rep->tail != NULL)
            {
                List_Remove(&rep->head, &rep->tail, (ListElem*)p);
            }

            /* Notify handler of removal */
            if (handler->callback != NULL && p != NULL)
            {
                (*handler->callback)(self, p, SELECTOR_REMOVE, 0);
            }

            return MI_RESULT_OK;
        }
    }

    return MI_RESULT_NOT_FOUND;
}

MI_Result Selector_RemoveAllHandlers(
    Selector* self)
{
    SelectorRep* rep = (SelectorRep*)self->rep;
    Handler* p;

    /* Find and remove handler from list */
    for (p = (Handler*)rep->head; p != NULL; )
    {
        Handler* next = p->next;

        /* Remove handler */
        if (rep != NULL && rep->head != NULL && rep->tail != NULL)
        {
            List_Remove(&rep->head, &rep->tail, (ListElem*)p);
        }

        /* Notify handler of removal */
        if (p->callback != NULL)
        {
            (*p->callback)(self, p, SELECTOR_REMOVE, 0);
        }

        p = next;
    }


    return MI_RESULT_OK;
}

static void _ProcessCallbacks(
    SelectorRep* rep)
{
    // This code implements a callback mechanism for passing data between
    // threads in a process and synchronizing the data ready event between
    // them. Instead of serializing the data, the code allocates memory and
    // writes the address of the allocated memory to the pipe. This receiving
    // method knows the structure of the data that it's going to read from
    // the pipe, so it allocates memory for a pointer to a struct of the right
    // type. The value read from the pipe is then stuffed into the pointer.
    // Thus, the address of the memory allocated in the writer is becomes the
    // contents of a simple pointer (not a **) on this side, and the members
    // of the struct in shared memory can be accessed using the -> operator.
    // Since the pointer can be mixed in with large amounts of other data
    // begin sent over the same pipe, care must be taken that the entire
    // pointer is read if the pipe fills during the communication, before
    // it is used to access the structure data.

    // The pointer sent is NULL if it was sent by Selector_Wakeup and is not NULL if sent by
    // CallInIOThread.

    SelectorCallbacksItem *item = NULL;
    size_t amtRead = 0;
    int shortReadCount = 0;
    static int processShortReadCount = -1;
    int retryCount;
    MI_Result r;

    if (processShortReadCount < 0)
    {                                   // output a line that we are logging _ProcessCallbacks
        LOGD2((ZT("_ProcessCallbacks screen logging ver 1.0")));
        processShortReadCount = 0;
    }

    LOGD2((ZT("_ProcessCallbacks - Attempting read on notification socket[0]: %d"), rep->notificationSockets[0]));
    while ((r = Sock_Read(rep->notificationSockets[0], &item, sizeof item, &amtRead)) == MI_RESULT_OK)
    {
        // Only continue processing if we received the entire thing. This
        // really should be fast except when the pipe was full when the
        // attempt was made to send the pointer.  If that happens, this may
        // block or only part of the pointer may be read.
        LOGD2((ZT("_ProcessCallbacks - Read complete with OK result. %i / %u bytes read."), (unsigned int)amtRead, (unsigned int)sizeof item));
        if (amtRead > sizeof item)
        {
            LOGW((ZT("_ProcessCallbacs - Long read. %u / %u bytes read"), (unsigned int)amtRead, (unsigned int)sizeof item));
            LOGE2((ZT("_ProcessCallbacks - Long read. %u / %u bytes read"), (unsigned int)amtRead, (unsigned int)sizeof item));
            break;
        }
        else if (amtRead == sizeof item)
        {
            if (shortReadCount != 0)
            {
                LOGW((ZT("_ProcessCallbacks - Success on read after a short read. It took %d tries. item: %p"), shortReadCount, item));
                LOGD2((ZT("_ProcessCallbacks - Success on read after short. It took %d tries. item: %p"), shortReadCount, item));
            }
            shortReadCount = 0;
            LOGD2((ZT("_ProcessCallbacks - Pipe read. item: %p, callback: %p"), item, item != NULL ? item->callback : NULL));
            if (item != NULL)               // if the call came from Selector_Wakeup, do no more
            {
                if (item->callback != NULL) // if the call came from CallInIOThread, call the callback if present
                {
                    (*item->callback)(item->callback_self, item->message);
                }
                Message_Release(item->message);
            }
        }
        else // (amtRead < sizeof item)
        {
            // we must retry because we don't have a full pointer
            LOGW((ZT("_ProcessRead - Short read. socket: %d. %u / %u bytes read. Pointer: %p. Retrying"), rep->notificationSockets[0], (unsigned int)amtRead, (unsigned int)sizeof item, item));
            LOGD2((ZT("_ProcessRead - Short read. socket: %d. %u / %u bytes read. Pointer: %p. Retrying"), rep->notificationSockets[0], (unsigned int)amtRead, (unsigned int)sizeof item, item));
            processShortReadCount++;
            shortReadCount++;
            for (retryCount = 0; retryCount < 3 && amtRead < sizeof item; retryCount++)
            {
                size_t amtRead2;

                usleep(100000);      // wait 1/10 second for the pipe to empty
                r = Sock_Read(rep->notificationSockets[0], (unsigned char*)&item + amtRead, sizeof item - amtRead, &amtRead2);
                if (r != MI_RESULT_OK)
                {
                    LOGW2((ZT("_ProcessRead - result %d (%s) on retry"), (int)r, mistrerror(r)));
                    continue;
                }
                amtRead += amtRead2;
                LOGD2((ZT("_ProcessRead - Success on retry. %u / %u bytes read"), (unsigned int)amtRead, (unsigned int)sizeof item));
                if (amtRead < sizeof item)
                {
                    LOGE((ZT("_ProcessRead - Pointer read failure after %d retries"), retryCount));
                    LOGE2((ZT("_ProcessRead - Pointer read failure after %d retries"), retryCount));
                    break;
                }
            }
        }
    }
    return;
}

MI_Result Selector_Run(
    Selector* self,
    MI_Sint64 timeoutUsec)
{
    lockSelectorMutex();

    SelectorRep* rep = self->rep;
    MI_Uint64 timeoutSelectorAt = TIME_NEVER;

    LOGX2((ZT("Selector_Run - Begin. timeout (<= 0 for none): %ld"), (long)timeoutUsec));
    rep->ioThreadHandle = ThreadSelf();

    if (timeoutUsec > 0)
    {
        if (Time_Now(&timeoutSelectorAt) != MI_RESULT_OK)
        {
            unlockSelectorMutex();
            LOGE2((ZT("Selector_Run - Time_Now failed")));
            return MI_RESULT_FAILED;
        }

        /* calculate when to terminate selector */
        LOGX2((ZT("Selector_Run - After timeout calculation. time now: %s, timeoutSelectorAt: %s"), FmtTime(timeoutSelectorAt), FmtTime(timeoutSelectorAt + timeoutUsec)));
        timeoutSelectorAt += timeoutUsec;
    }

    /* Loop while detecting and dispatching events */
    for (rep->keepRunning = MI_TRUE; rep->keepRunning != MI_FALSE; )
    {
        Handler* p;
        MI_Uint64 currentTimeUsec;
        MI_Uint64 breakCurrentSelectAt = TIME_NEVER;
        int n;
        MI_Uint32 count = 0;
        MI_Boolean stressed = Selector_IsStressed(self);
        MI_Result r;

        // Let the other threads get some time
        unlockSelectorMutex();

        sched_yield();
        usleep(200);

        // Since we let it go, we should get it back.
        lockSelectorMutex();

        if (!rep->keepRunning)
        {
            LOGD2((ZT("Selector_Run - keepRunning is false. Done.")));
            break;
        }

        r = Time_Now(&currentTimeUsec);
        if (r != MI_RESULT_OK)
        {
            unlockSelectorMutex();
            LOGE2((ZT("Selector_Run - Time_Now failed with result: %d (%s)"), (int)r, mistrerror(r)));
            return MI_RESULT_FAILED;
        }

        LOGX2((ZT("Selector_Run - currentTimeUsec: %s"), FmtTime(currentTimeUsec)));

        if (timeoutSelectorAt != TIME_NEVER)
        {
            if (currentTimeUsec >= timeoutSelectorAt)
            {
                unlockSelectorMutex();
                LOGX2((ZT("Selector_Run - Selector timeout. limit time: %s, current time: %s, interval: %ld"), FmtTime(timeoutSelectorAt), FmtTime(currentTimeUsec), (long)(currentTimeUsec - timeoutSelectorAt)));
                return MI_RESULT_TIME_OUT;
            }
            breakCurrentSelectAt = timeoutSelectorAt;
        }

        /* Set up FD sets from handlers */
        memset(&rep->readSet, 0, sizeof (rep->readSet));
        memset(&rep->writeSet, 0, sizeof (rep->writeSet));
        memset(&rep->exceptSet, 0, sizeof (rep->exceptSet));

        for (p = (Handler*)rep->head; p != NULL; p = (Handler*)p->next)
        {
            LOGX2((ZT("Selector_Run - Evaluating masks. socket: %d, mask: 0x%02X (%s)"), p->sock, p->mask, selectorflagstr(p->mask)));
            if (p->sock != INVALID_SOCK && (!stressed || (p->mask & SELECTOR_IGNORE_READ_OVERLOAD) == 0))
            {
                if (p->mask & SELECTOR_READ)
                {
                    _FDSet(p->sock, &rep->readSet);
                    LOGX2((ZT("Selector_Run - Added socket %d to READ set"), p->sock));
                    count++;
                }
                if (p->mask & SELECTOR_WRITE)
                {
                    _FDSet(p->sock, &rep->writeSet);
                    LOGX2((ZT("Selector_Run - Added socket %d to WRITE set"), p->sock));
                    count++;
                }
                if (p->mask & SELECTOR_EXCEPTION)
                {
                    _FDSet(p->sock, &rep->exceptSet);
                    LOGX2((ZT("Selector_Run - Added socket %d to EXCEPTION set"), p->sock));
                    count++;
                }
            }

            if (p->fireTimeoutAt != TIME_NEVER)
            {
                /* find the minimum timeout from the list */
                /* if expired - don't wait; notification will be issued later in next loop */
                if (currentTimeUsec >= p->fireTimeoutAt)
                {
                    breakCurrentSelectAt = currentTimeUsec;
                    LOGX2((ZT("Selector_Run - For socket %d, current selector break time %s is GREATER than timeout time %s by %ld usec."),
                           p->sock, FmtTime(breakCurrentSelectAt), FmtTime(p->fireTimeoutAt), (long)(breakCurrentSelectAt - p->fireTimeoutAt)));
                }
                else
                {
                    breakCurrentSelectAt = p->fireTimeoutAt;
                    LOGX2((ZT("Selector_Run - For socket %d, current selector break time %s is LESS than timeout time %s by %ld usec."),
                           p->sock, FmtTime(breakCurrentSelectAt), FmtTime(p->fireTimeoutAt), (long)(breakCurrentSelectAt - p->fireTimeoutAt)));
                }
            }
        }

        _FDSet(rep->notificationSockets[0], &rep->readSet);
        LOGX2((ZT("Selector_Run - Added notification socket[0]: %d to READ set"), rep->notificationSockets[0]));

        /* empty list - return */
        if (rep->head == NULL && !rep->allowEmptySelector)
        {
            unlockSelectorMutex();
            LOGE2((ZT("Selector_Run - Failed. Empty selector not permitted")));
            return MI_RESULT_FAILED;
        }

        // We must unlock for the duration of the select so we don't block someone
        // when we've got a blocking socket
        MI_Sint64 TimeOut = 0;
        int ReleasedMutex = 0;
        if (breakCurrentSelectAt == TIME_NEVER)
        {
            LOGD2((ZT("Selector_Run - Timeout was NEVER; blocking select")));
            TimeOut = -1;
            unlockSelectorMutex();
            ReleasedMutex = 1;
        }
        else
        {
            TimeOut = breakCurrentSelectAt - currentTimeUsec;
            if (TimeOut < 10000)
            {                           // the low-level code interprets TimeOut < 0 as never, so
                TimeOut = 10000;        // use 1/100 second if timeout has already happened
            }
            LOGX2((ZT("Selector_Run - Calculated timeout is %ld usec."), (long)TimeOut));
        }

        LOGD2((ZT("Selector_Run - Selecting on socket(s) R: {%s}, W: {%s}, E: {%s}. interval: %ld usec."), bitnumberstr(*(unsigned long*)&rep->readSet), bitnumberstr(*(unsigned long*)&rep->writeSet), bitnumberstr(*(unsigned long*)&rep->exceptSet), TimeOut < 0 ? -1 : (long)TimeOut));

        n = _Select(&rep->readSet, &rep->writeSet, &rep->exceptSet, TimeOut /* timeoutUsec */);

        LOGX2((ZT("Selector_Run - _Select returned that there were %d socket(s) ready. R: {%s}, W: {%s}, E: {%s}"), n, bitnumberstr(*(unsigned long*)&rep->readSet), bitnumberstr(*(unsigned long*)&rep->writeSet), bitnumberstr(*(unsigned long*)&rep->exceptSet)));
        if (ReleasedMutex)
        {
            lockSelectorMutex();
        }

        /* ignore signals, since they can be raised as part of normal operation */
        if (n < 0 && LastSocketError != EINTR && LastSocketError != EBADF)
        {
            unlockSelectorMutex();
            LOGE2((ZT("Selector_Run - Failed on OS error: %d (%s)"), LastSocketError, strerror(LastSocketError)));
            return MI_RESULT_FAILED;
        }

        if (FD_ISSET(rep->notificationSockets[0], &rep->readSet))
        {
            LOGD2((ZT("Selector_Run - Notification socket[0]: %d was set after select. Processing callbacks"), rep->notificationSockets[0]));
            _ProcessCallbacks(rep);
        }

        /* Notify handlers of outstanding events */
        for (p = (Handler*)rep->head; p != NULL; )
        {
            MI_Uint32 mask = 0;
            Handler* next = p->next;

            if ((!stressed || (p->mask & SELECTOR_IGNORE_READ_OVERLOAD) == 0))
            {
                if (p->sock != INVALID_SOCK && (p->mask & (SELECTOR_READ | SELECTOR_WRITE | SELECTOR_EXCEPTION)) != 0)
                {
                    /* Check for read event */
                    if (FD_ISSET(p->sock, &rep->readSet))
                    {
                        LOGD2((ZT("Selector_Run - Got read flag")));
                        mask |= SELECTOR_READ;
                        _FDClr(p->sock, &rep->readSet);
                    }

                    /* Check for write event */
                    if (FD_ISSET(p->sock, &rep->writeSet))
                    {
                        LOGD2((ZT("Selector_Run - Got write flag")));
                        mask |= SELECTOR_WRITE;
                        _FDClr(p->sock, &rep->writeSet);
                    }

                    /* Check for exception event */
                    if (FD_ISSET(p->sock, &rep->exceptSet))
                    {
                        LOGD2((ZT("Selector_Run - Got exception flag")));
                        mask |= SELECTOR_EXCEPTION;
                        _FDClr(p->sock, &rep->exceptSet);
                    }
                }
            }

            // if communicating with wsman or if this entry is for a dummy pipe (used to check for process timeout),
            // check for timeout
//            if (p->type == WSMAN_HANDLER || p->sock < 0)
            {
                if (p->fireTimeoutAt != TIME_NEVER && currentTimeUsec >= p->fireTimeoutAt)
                {
                    LOGD2((ZT("Selector_Run - Socket timeout. socket: %d, current time: %s, limit time: %s, interval: %ld usec."), p->sock, FmtTime(currentTimeUsec), FmtTime(p->fireTimeoutAt), (long)(currentTimeUsec - p->fireTimeoutAt)));
                    mask |= SELECTOR_TIMEOUT;
                }
            }

            /* If any events, notify watcher */
            if (mask != 0)
            {
                MI_Boolean more;

                if (p->callback != NULL)
                {
                    LOGD2((ZT("Selector_Run - Executing the callback for handler: %p. socket: %d, mask: 0x%02X (%s)"), self, p->sock, mask, selectorflagstr(mask)));
                    more = (*p->callback)(self, p, mask, currentTimeUsec);
                    if (!more)
                    {
                        /* Remove handler */
                        if (rep != NULL && rep->head != NULL && rep->tail != NULL)
                        {
                            List_Remove(&rep->head, &rep->tail, (ListElem*)p);
                        }

                        /* Notify handler of removal */
                        if (p->callback != NULL)
                        {
                            (*p->callback)(self, p, SELECTOR_REMOVE, currentTimeUsec);
                        }
                    }
                }
            }
            /* Advance to next handler */
            p = next;
        }
    }

    unlockSelectorMutex();
    LOGX2((ZT("Selector_Run - OK exit")));
    return MI_RESULT_OK;
}

/* Wakes up selector's thread
  Typical usage is to recalculate timeouts on handlers
  when selector's Run is running in different thread
 */
MI_Result Selector_Wakeup(
    Selector* self)
{
    SelectorRep* rep = (SelectorRep*)self->rep;

    /* notify running thread */
    {
        void* p = NULL;
        size_t sent = 0;

        Sock_Write(rep->notificationSockets[1], &p, sizeof (void *), &sent);
        if (sent != sizeof(p))
        {
            // Short write.  Since this is a blocking socket, this would be a serious issue.
            LOGE2((ZT("Selector_Wakeup - Short write")));
            return MI_RESULT_FAILED;
        }
    }

    return MI_RESULT_OK;
}

MI_Result Selector_StopRunning(
    Selector* self)
{
    SelectorRep* rep = (SelectorRep*)self->rep;

    rep->keepRunning = MI_FALSE;

    return Selector_Wakeup(self);
}

/*
 * This function guarantees that callback is called in 'Run'/'IO' thread context,
 * so locking is required for accessing socket objects, updating buffers, etc.
*/
MI_Result Selector_CallInIOThread(
    Selector* self,
    Selector_NotificationCallback  callback,
    void* callback_self,
    Message* message)
{
    SelectorRep* rep = (SelectorRep*)self->rep;
    SelectorCallbacksItem* newItem;
    MI_Result r;
    size_t sent = 0;

    if (rep->ioThreadHandle == ThreadSelf())
    {
        /* direct call - we can write to socket instantly */

        if (callback != NULL)
        {
            (*callback)(callback_self, message);
        }
        return MI_RESULT_OK;
    }

    /* add item to the list and set event */
    newItem = (SelectorCallbacksItem*)Batch_GetClear(message->batch, sizeof(SelectorCallbacksItem));
    if (newItem == NULL)
    {
        LOGW((ZT("Selector_CallInIOThread - Batch_GetClear failed")));
        return MI_RESULT_FAILED;
    }

    assert(callback);
    newItem->callback = callback;
    newItem->callback_self = callback_self;
    newItem->message = message;

    //AtomicInc(&rep->queueLength);

    while (rep->outstandingInstances > MAX_ALLOCATED_INSTANCES)
        Sleep_ms(1);

#if 0
    {
        int counter = 0;

        while (rep->queueLength > LIST_SIZE_LIMIT)
        {
            counter++;
            /* give system a chance to clear backlog */
            Sleep_ms(1);

            if (counter > 1000)
            {
                LOGW((ZT("Selector_CallInIOThread - timeout sending message")));
                return MI_RESULT_FAILED;
            }
        }
    }
#endif

    Message_AddRef(message);

    r = Sock_Write(rep->notificationSockets[1], &newItem, sizeof(newItem), &sent);
    if (r == MI_RESULT_OK && sent != sizeof(newItem))
    {
        // Short write.  Since this is a blocking socket, this would be a serious issue.
        LOGE2((ZT("Selector_CallInIOThread - Cannot send message. Queue overflow")));
        r = MI_RESULT_FAILED;
    }

    if (MI_RESULT_OK != r)
    {
        Message_Release(message);
    }

    return r;
}

#endif /* defined(CONFIG_POSIX) */

/************************************/
/* generic functionality */

MI_Result Selector_ContainsHandler(
    Selector* self,
    Handler* handler)
{
    SelectorRep* rep = (SelectorRep*)self->rep;
    Handler* p;

    for (p = (Handler*)rep->head; p != NULL; p = (Handler*)p->next)
    {
        if (p == handler)
        {
            return MI_RESULT_OK;
        }
    }

    return MI_RESULT_NOT_FOUND;
}

static void _dtor(Message* message, void* callbackData)
{
    SelectorRep* rep = (SelectorRep*)callbackData;

    MI_UNUSED(message);

    AtomicDec(&rep->outstandingInstances);
}

void Selector_NewInstanceCreated(
    Selector* self,
    Message* msg)
{
    SelectorRep* rep = (SelectorRep*)self->rep;

    msg->dtor = _dtor;
    msg->dtorData = rep;

    AtomicInc(&rep->outstandingInstances);
}

MI_Boolean  Selector_IsStressed(
    Selector* self)
{
    SelectorRep* rep = (SelectorRep*)self->rep;

    /* Are we close to be stressed? */
    if (rep->outstandingInstances >= (MAX_ALLOCATED_INSTANCES * 9 / 10))
        return MI_TRUE;

    return MI_FALSE;
}

void Selector_SetAllowEmptyFlag(
    Selector* self,
    MI_Boolean allowEmptySelector)
{
    SelectorRep* rep = (SelectorRep*)self->rep;

    rep->allowEmptySelector = allowEmptySelector;
}
