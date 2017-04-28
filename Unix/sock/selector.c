/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "selector.h"
#include <pal/sleep.h>
#include <pal/thread.h>
#include <pal/sleep.h>
#include <pal/lock.h>
#include <base/log.h>
#include <base/result.h>
#include <pal/atomic.h>

//#define  ENABLE_TRACING 1
#ifdef ENABLE_TRACING
//# define TRACING_LEVEL 4
#include <base/result.h>
#include <base/logbase.h>
#include <base/log.h>
#define LOGE2 __LOGE
#define LOGW2 __LOGW
#define LOGD2 __LOGD
#define mistrerror Result_ToString

static char FmtBuf[256];
static const char* FmtTime(MI_Uint64 Time)
{
    char* TmBuf;
    unsigned long Sec;
    unsigned long uSec;
    unsigned long Min;
    unsigned long Hr;

    if (Time == 0)
    {
        return "None";
	}

    Sec = (unsigned long)(Time / 1000000);
    uSec = (unsigned long)(Time % 1000000);
    Min = Sec / 60;
    Sec -= Min * 60;
    Hr = Min / 60;
    Min -= Hr * 60;
    Hr %= 24;
    TmBuf = FmtBuf;
    sprintf(TmBuf, "%02lu:%02lu:%02lu.%03lu", Hr, Min, Sec, uSec / 1000);
    return TmBuf;
}

#else
# define LOGE2(a)
# define LOGW2(a)
# define LOGD2(a)
# define LOGX2(a)
#endif

/* maximum number of items in the list */
#define LIST_SIZE_LIMIT     321

/* maximum instances that can be allocated */
#define MAX_ALLOCATED_INSTANCES 500

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
    Selector_NotificationCallback  callback;
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
    Lock listLock;
    ListElem* head;
    ListElem* tail;

    /* notifications channel */
    int notificationSockets[2];

    /* flag to stop running */
    MI_Boolean keepRunning;
    MI_Boolean keepRunningNoReadsMode;

    /* flag to retry a dispatch loop */
    MI_Boolean keepDispatching;
    
    /* flag that allows empty selector running 
        when empty selector runs, it only can be interrupted by
        internal funcitons, since it has no sockets to monitor
        */
    MI_Boolean allowEmptySelector;

    /* io thread id */
    ThreadID    ioThreadHandle;
}
SelectorRep;

static int _Select(
    fd_set* readSet,
    fd_set* writeSet,
    fd_set* exceptSet,
    MI_Uint64 timeoutUsec,
    MI_Boolean* keepRunning)
{
    int n = FD_SETSIZE;
    int r;
    struct timeval tv;
    struct timeval* _tv = 0;

    if ((MI_Uint64)-1 != timeoutUsec)
    {
        tv.tv_sec = (long)(timeoutUsec / 1000000);
        tv.tv_usec = (long)(timeoutUsec % 1000000);
        _tv = &tv;
    }

    do
    {
        r = select(n, readSet, writeSet, exceptSet, _tv);
    }
    while( (*keepRunning == MI_TRUE) && ( -1 == r ) && ( errno == EINTR ) );

    return r;
}

MI_INLINE void _FDSet(Sock sock, fd_set* set)
{
    FD_SET(sock, set);
}

MI_INLINE void _FDClr(Sock sock, fd_set* set)
{
    FD_CLR(sock, set);
}

MI_Result Selector_Init(
    Selector* self)
{
    self->rep = (SelectorRep*)PAL_Calloc(1, sizeof(SelectorRep));

    if (!self->rep)
        return MI_RESULT_FAILED;

    Lock_Init(&self->rep->listLock);

    if (pipe(self->rep->notificationSockets) != 0)
        return MI_RESULT_FAILED;

    /* set non-blocking for reader [0] */
    Sock_SetBlocking( self->rep->notificationSockets[0], MI_FALSE);

    /* Protect notification sockets from child processes */
    if (MI_RESULT_OK != Sock_SetCloseOnExec(self->rep->notificationSockets[0],MI_TRUE) ||
        MI_RESULT_OK != Sock_SetCloseOnExec(self->rep->notificationSockets[1],MI_TRUE))
    {
        trace_fcntl_failed( errno );
    }

    return MI_RESULT_OK;
}

void Selector_Destroy(Selector* self)
{
    SelectorRep* rep = (SelectorRep*)self->rep;
    Handler* p;
    Handler* next;

    /* Free all watchers */
    for (p = (Handler*)rep->head; p; p = next)
    {
        next = (Handler*)p->next;

        (*p->callback)(self, p, SELECTOR_DESTROY, 0);
        p = next;
    }

    Sock_Close(rep->notificationSockets[0]);
    Sock_Close(rep->notificationSockets[1]);

    PAL_Free(rep);
}

MI_Result Selector_AddHandler(
    Selector* self,
    Handler* handler)
{
    SelectorRep* rep = (SelectorRep*)self->rep;
    Handler* p;
    MI_Uint64 currentTimeUsec = 0;

    if (PAL_TRUE != PAL_Time(&currentTimeUsec))
        return MI_RESULT_FAILED;

    Lock_Acquire(&rep->listLock);

    /* Reject duplicates */
    for (p = (Handler*)rep->head; p; p = (Handler*)p->next)
    {
        if (p == handler)
        {
            Lock_Release(&rep->listLock);
            trace_Selector_AddHandler_AlreadyThere(self, p, p->handlerName);
            return MI_RESULT_ALREADY_EXISTS;
        }
    }

    trace_Selector_AddHandler(self, handler, handler->handlerName);

    /* Add new handler to list */
    List_Append(&rep->head, &rep->tail, (ListElem*)handler);

    Lock_Release(&rep->listLock);

    (*handler->callback)(self, handler, SELECTOR_ADD, currentTimeUsec);

    return MI_RESULT_OK;
}

MI_Result Selector_RemoveHandler(
    Selector* self,
    Handler* handler)
{
    SelectorRep* rep = (SelectorRep*)self->rep;
    Handler* p;

    Lock_Acquire(&rep->listLock);

    /* Find and remove handler from list */
    for (p = (Handler*)rep->head; p; p = (Handler*)p->next)
    {
        if (p == handler)
        {
            trace_Selector_RemoveHandler(self, handler, handler->handlerName);
            /* Remove handler */
            List_Remove(&rep->head, &rep->tail, (ListElem*)p);

            Lock_Release(&rep->listLock);

            /* Notify handler of removal */
            (*handler->callback)(self, p, SELECTOR_REMOVE, 0);

            return MI_RESULT_OK;
        }
    }

    Lock_Release(&rep->listLock);

    trace_Selector_RemoveHandler_NotThere(self, handler, handler->handlerName);
    return MI_RESULT_NOT_FOUND;
}

MI_Result Selector_RemoveAllHandlers(
    Selector* self)
{
    SelectorRep* rep = (SelectorRep*)self->rep;
    Handler* p;

    Lock_Acquire(&rep->listLock);

    p = (Handler*)rep->head;

    while (p)
    {
        trace_Selector_RemoveAllHandlers(self, p, p->handlerName);

        /* Remove handler */
        List_Remove(&rep->head, &rep->tail, (ListElem*)p);

        Lock_Release(&rep->listLock);

        /* Notify handler of removal */
        (*p->callback)(self, p, SELECTOR_REMOVE, 0);

        Lock_Acquire(&rep->listLock);

        p = (Handler*)rep->head;
    }

    Lock_Release(&rep->listLock);

    return MI_RESULT_OK;
}

static void _ProcessCallbacks(
    SelectorRep* rep)
{
    SelectorCallbacksItem* item = NULL;
    size_t read = 0;
    MI_Result r;

    LOGD2((ZT("_ProcessCallbacks - Begin. notification socket: %d"), rep->notificationSockets[0]));
    while( (r = Sock_Read(rep->notificationSockets[0], &item, sizeof(item), &read)) == MI_RESULT_OK &&
           read == sizeof(item) )
    {
        if (item)
        {
            LOGD2((ZT("_ProcessCallbacks - Calling item callback")));
            (*item->callback) (item->callback_self, item->message);
            Message_Release(item->message);
            //Atomic_Dec( &rep->queueLength );
        }
    }
    LOGD2((ZT("_ProcessCallbacks - End. last result: %d (%s)"), r, mistrerror(r)));
}

void _Selector_WakeupFromWait(
    SelectorRep* rep)
{
    void* p = 0;
    size_t sent = 0;

    Sock_Write( rep->notificationSockets[1], &p, sizeof(p), &sent);
}

/* 
    * This function guaranties that callback is called in 'Run'/'IO' thread context,
    * so locking is required for accessing sokcet objects, updating buffers etc
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
    ThreadID current = Thread_ID();

    if (Thread_Equal(&rep->ioThreadHandle, &current))
    {
        /* direct call - we can write to socket instantly */

        trace_Sock_SendingOnOwnThread(
            message,
            message->tag,
            MessageName(message->tag),
            message->operationId);
        
        (*callback)(callback_self, message);
        return MI_RESULT_OK;
    }

    /* add item to the list and set event */
    newItem = (SelectorCallbacksItem*) Batch_GetClear( message->batch, sizeof(SelectorCallbacksItem));

    if (!newItem)
        return MI_RESULT_FAILED;

    newItem->callback = callback;
    newItem->callback_self = callback_self;
    newItem->message = message;

    Message_AddRef(message);
    r = Sock_Write(rep->notificationSockets[1], &newItem, sizeof(newItem), &sent);

    trace_Sock_SentResult(
        message,
        message->tag,
        MessageName(message->tag),
        message->operationId,
        r);
    
    if ( MI_RESULT_OK != r )
        Message_Release(message);

    return r;
}

static MI_Result _SetSockEvents(SelectorRep* rep, Handler* p, MI_Uint32 mask, MI_Boolean noReadsMode )
{
    if( !noReadsMode && (mask & SELECTOR_READ) )
    {
        _FDSet(p->sock, &rep->readSet);
    }
    if (mask & SELECTOR_WRITE)
    {
        _FDSet(p->sock, &rep->writeSet);
    }

    return MI_RESULT_OK;
}

static MI_Result _GetSockEvents(SelectorRep* rep, Handler* p, MI_Uint32* mask)
{
    *mask = 0;
    if (p->mask & (SELECTOR_READ | SELECTOR_WRITE | SELECTOR_EXCEPTION))
    {
        /* Check for read event */
        if (FD_ISSET(p->sock, &rep->readSet))
        {
            *mask |= SELECTOR_READ;
            _FDClr(p->sock, &rep->readSet);
        }
    
        /* Check for write event */
        if (FD_ISSET(p->sock, &rep->writeSet))
        {
            *mask |= SELECTOR_WRITE;
            _FDClr(p->sock, &rep->writeSet);
        }
    
        /* Check for exception event */
        if (FD_ISSET(p->sock, &rep->exceptSet))
        {
            _FDClr(p->sock, &rep->exceptSet);
        }
    }

    return MI_RESULT_OK;
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

    Lock_Acquire(&rep->listLock);

    for (p = (Handler*)rep->head; p; p = (Handler*)p->next)
    {
        if (p == handler)
        {
            Lock_Release(&rep->listLock);
            return MI_RESULT_OK;
        }
    }

    Lock_Release(&rep->listLock);

    return MI_RESULT_NOT_FOUND;
}

void Selector_SetAllowEmptyFlag(
    Selector* self,
    MI_Boolean allowEmptySelector)
{
    SelectorRep* rep = (SelectorRep*)self->rep;

    rep->allowEmptySelector = allowEmptySelector;
}

/* Wakes up selector's thread 
    Typical usage is to recalculate timeouts on handlers
    when selector's Run is running in different thread */
MI_Result Selector_Wakeup(
    _In_    Selector*   self,
            MI_Boolean  retryDispatching )
{
    SelectorRep* rep = (SelectorRep*)self->rep;
    ThreadID current = Thread_ID();

    /* notify running thread (if different) */
    if( !Thread_Equal(&rep->ioThreadHandle, &current) )
    {
        _Selector_WakeupFromWait(rep);
    }
    else if( retryDispatching )
    {
        rep->keepDispatching = MI_TRUE;
    }
    
    return MI_RESULT_OK;
}

MI_Result Selector_StopRunning(
    Selector* self)
{
    SelectorRep* rep = (SelectorRep*)self->rep;

    rep->keepRunning = MI_FALSE;

    return Selector_Wakeup(self, MI_FALSE);
}

MI_Result Selector_StopRunningNoReadsMode(
    Selector* self)
{
    SelectorRep* rep = (SelectorRep*)self->rep;

    rep->keepRunningNoReadsMode = MI_FALSE;

    return Selector_Wakeup(self, MI_FALSE);
}

MI_Result Selector_Run(
    Selector* self,
    MI_Uint64 timeoutUsec,
    MI_Boolean noReadsMode )
{
    SelectorRep* rep = (SelectorRep*)self->rep;
    MI_Uint64 timeoutSelectorAt = TIME_NEVER;
    MI_Boolean* keepRunningVar;
#if defined(CONFIG_OS_WINDOWS)
    HANDLE handles[2];
    
    trace_SelectorRun_Enter( self, timeoutUsec, noReadsMode );
    
    handles[0] = rep->event;
    handles[1] = rep->callbacksAreAvailable;
#endif // defined(CONFIG_OS_WINDOWS)

    if( noReadsMode )
    {
        keepRunningVar = &rep->keepRunningNoReadsMode;
    }
    else
    {
        keepRunningVar = &rep->keepRunning;
    }
    
    LOGD2((ZT("Selector_Run - Begin. timeoutUsec: %ld"), (long)timeoutUsec));

    if ( TIME_NEVER != timeoutUsec )
    {
        if (PAL_TRUE != PAL_Time(&timeoutSelectorAt))
        {
            trace_SelectorRun_InitPALTIME_Error( self );
            return MI_RESULT_FAILED;
        }
        
        /* calculate when to terminate selector */
        LOGD2((ZT("Selector_Run - After timeout calculation. time now: %s, timeoutSelectorAt: %s"), FmtTime(timeoutSelectorAt), FmtTime(timeoutSelectorAt + timeoutUsec)));
        timeoutSelectorAt += timeoutUsec;
    }

    rep->ioThreadHandle = Thread_ID();

    /* Loop while detecting and dispatching events */
    for (*keepRunningVar = MI_TRUE; *keepRunningVar; )
    {
        Handler* p;
        MI_Uint64 currentTimeUsec = 0;
        MI_Uint64 breakCurrentSelectAt = (MI_Uint64)-1;
        MI_Boolean more;
        MI_Result r;
#if defined(CONFIG_OS_WINDOWS)
        DWORD result;
        DWORD timeoutMsec;
#else
        int n;
#endif 

        if (PAL_TRUE != PAL_Time(&currentTimeUsec))
        {
            trace_SelectorRun_InitPALTIME_Error( self );
            LOGE2((ZT("Selector_Run - PAL_Time failed")));
            return MI_RESULT_FAILED;
        }

        if (TIME_NEVER != timeoutSelectorAt)
        {
            if (currentTimeUsec >= timeoutSelectorAt)
            {
                LOGW2((ZT("Selector_Run - Selector timeout. current time: %s, limit time: %s, interval: %ld ms"),
                        FmtTime(timeoutSelectorAt), FmtTime(currentTimeUsec),
                        (long)(currentTimeUsec - timeoutSelectorAt)));
                return MI_RESULT_TIME_OUT;
            }

            breakCurrentSelectAt = timeoutSelectorAt;
        }

#if defined(CONFIG_POSIX)
        /* Set up FD sets from handlers */
        memset(&rep->readSet, 0, sizeof(rep->readSet));
        memset(&rep->writeSet, 0, sizeof(rep->writeSet));
        memset(&rep->exceptSet, 0, sizeof(rep->exceptSet));
#endif /* defined(CONFIG_POSIX) */
        
        /* calculate timeout */
        Lock_Acquire(&rep->listLock);
        for (p = (Handler*)rep->head; p; )
        {
            Handler* next = p->next;

            /* update event mask */
#if defined(CONFIG_OS_WINDOWS)
            if( p->sock != INVALID_SOCK )
#endif
            {
                r = _SetSockEvents(rep, p, p->mask, noReadsMode );
                
                if (r != MI_RESULT_OK)
                {
                    LOGE2((ZT("Selector_Run - _SetSockEvents failed")));
                    trace_SelectorRun_SetSocketEventsError( self, r, p );
                    Lock_Release(&rep->listLock);
                    return r;
                }
            }

            /* find the minimum timeout form the list */
            if (TIME_NEVER != p->fireTimeoutAt)
            {
                /* if expired - don't wait; notification will be issued later in next loop */
                if (currentTimeUsec >= p->fireTimeoutAt)
                    breakCurrentSelectAt = currentTimeUsec;
                else if ( p->fireTimeoutAt < breakCurrentSelectAt)
                    breakCurrentSelectAt = p->fireTimeoutAt;
            }

            p = next;
        }
        Lock_Release(&rep->listLock);

#if defined(CONFIG_POSIX)
        _FDSet(rep->notificationSockets[0], &rep->readSet);
#endif /* defined(CONFIG_POSIX) */

        /* empty list - return */
        if (!rep->head && !rep->allowEmptySelector)
        {
            LOGE2((ZT("Selector_Run - Empty list")));
            trace_SelectorRun_EmptyList( self );
            return MI_RESULT_FAILED;
        }
        
#if defined(CONFIG_OS_WINDOWS)
        /* Wait for events on any of the sockets */
        timeoutMsec = 
            (breakCurrentSelectAt == ((MI_Uint64)-1) ) ? /* do we have t least one valid timeout? */
            INFINITE : (DWORD)((breakCurrentSelectAt - currentTimeUsec) / 1000);
        result = WaitForMultipleObjectsEx(MI_COUNT(handles), handles, FALSE, timeoutMsec, FALSE);

        if (result == WAIT_FAILED)
        {
            trace_SelectorRun_WaitError( self, result );
            return MI_RESULT_FAILED;
        }
#else
        /* Perform system select */
        n = _Select(&rep->readSet, &rep->writeSet, NULL, 
            breakCurrentSelectAt == (MI_Uint64)-1 ? (MI_Uint64)-1: breakCurrentSelectAt - currentTimeUsec,
            keepRunningVar);

        /* ignore signals, since it canbe part of normal operation */
        if (-1 == n && errno != EINTR)
        {
            LOGE2((ZT("Selector_Run - _Select failed. errno: %d (%s)"), errno, strerror(errno)));
            trace_SelectorRun_WaitError( self, errno );
            return MI_RESULT_FAILED;
        }
#endif

        do
        {
            rep->keepDispatching = MI_FALSE;

#if defined(CONFIG_OS_WINDOWS)
            //if ((WAIT_OBJECT_0 + 1) == result)  /* other thread wants to call callback */
#else
            if (FD_ISSET(rep->notificationSockets[0], &rep->readSet))
#endif
            {
                _ProcessCallbacks(rep);
            }
            
            /* Dispatch events on each socket */
            for (p = (Handler*)rep->head; p; )
            {
                Handler* next = p->next;
                MI_Uint32 mask = 0;

                /* Refresh current time stamp */
                if (PAL_TRUE != PAL_Time(&currentTimeUsec))
                {
                    LOGE2((ZT("Selector_Run - PAL_Time failed")));
                    trace_SelectorRun_PALTimeError( self );
                    return MI_RESULT_FAILED;
                }
                
                /* Get event mask for this socket */
#if defined(CONFIG_OS_WINDOWS)
                if (p->sock != INVALID_SOCK)
#endif            
                {
                    r = _GetSockEvents(rep, p, &mask);

                    if (r != MI_RESULT_OK)
                    {
                        LOGE2((ZT("Selector_Run - _GetSockEvents failed with result: %d (%s)"), (int)r, mistrerror(r)));
                        trace_SelectorRun_GetSocketEventsError( self, r, p );
                        return r;
                    }
                }

                if (TIME_NEVER != p->fireTimeoutAt && currentTimeUsec >= p->fireTimeoutAt)
                {
                    mask |= SELECTOR_TIMEOUT;
                }

                /* If there were any events on this socket, dispatch them */
                if (mask)
                {
                    LOGD2((ZT("Selector_Run - Calling event dispatcher, handler = %p, rep = %p, mask = %u"), p, rep,  mask));
                    /*MI_Uint32 oldMask = p->mask;*/
                    more = (*p->callback)(self, p, mask, currentTimeUsec);

                    /* If callback wants to continue getting events */
                    if (!more)
                    {
                        /* Remove handler */
                        Selector_RemoveHandler(self, p);

                        /* Refresh current time stamp */
                        if (PAL_TRUE != PAL_Time(&currentTimeUsec))
                        {
                            LOGE2((ZT("Selector_Run - PAL_Time failed")));
                            trace_SelectorRun_PALTimeError( self );
                            return MI_RESULT_FAILED;
                        }

#if defined(CONFIG_OS_WINDOWS)
                        /* Unselect events on this socket */
                        _SetSockEvents(rep, p, 0, noReadsMode);
#endif

                        /* Notify handler of removal */
                        LOGD2((ZT("Selector_Run - Calling event dispatcher, handler = %p, rep = %p, mask = SELECTOR_REMOVE"), p, rep));
                    }
                }

                p = next;
            }
        }
        while( rep->keepDispatching );
    }

    LOGE2((ZT("Selector_Run - OK exit")));
    trace_SelectorRun_Exit( self );
    return MI_RESULT_OK;
}

int Selector_IsSelectorThread(Selector* self, ThreadID *id)
{
    if( NULL == self || NULL == self->rep )
    {
        // Some UTs may not have an actual selector
        return 0;
    }
    else
    {
        SelectorRep* rep = (SelectorRep*)self->rep;
        return Thread_Equal(&rep->ioThreadHandle, id);
    }
}
