/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <pal/atomic.h>
#include <base/batch.h>
#include <omi_error/omierror.h>
#include "nioproc.h"
#include "SubMgr.h"
#include "provmgr.h"

#define THREAD_NOT_JOINED 0
#define THREAD_JOINED 1

#define THREAD_NOT_RUNNING 0
#define THREAD_RUNNING 1

RequestHandler g_requesthandler;

static RequestItem* RequestList_RemoveItem(_Inout_ RequestList* list);
static MI_Result RequestList_RemoveSpecificItem(_Inout_ RequestList* list, _In_ RequestItem* item);

//
// A proc running from a spawned thread to unsuscribe the indication opertion(s)
//
PAL_Uint32 THREAD_API noniothread_proc(void* p);

_Use_decl_annotations_
void RequestList_Init(RequestList* list)
{
    list->head = NULL;
    list->tail = NULL;
    ReadWriteLock_Init( &list->lock );
}

_Use_decl_annotations_
void RequestHandler_Init(RequestHandler* handler)
{
    RequestList_Init(&handler->list);
    Lock_Init(&handler->lock);
    handler->running = THREAD_NOT_RUNNING;
    handler->joined = THREAD_NOT_JOINED;
}

//
// shutdown handler, i.e. wait for unsubscribe thread to exit
//
static void RequestHandler_Shutdown(RequestHandler* handler)
{
    // wait for unsubscribe thread to exit
    Thread unsubThread;
    ptrdiff_t joined = THREAD_NOT_JOINED;
    PAL_Uint32 ret;
    Lock_Acquire( &handler->lock );
    if ( handler->running == THREAD_RUNNING )
    {
        joined = THREAD_JOINED;
        handler->joined = joined;
        unsubThread = handler->thread;
    }
    Lock_Release( &handler->lock );
    if ( joined == THREAD_JOINED )
    {
        Thread_Join( &unsubThread, &ret );
        Thread_Destroy( &unsubThread );
        trace_ProvMgr_Destroy_Join_nonioThread( ret );
    }
}

_Use_decl_annotations_
void RequestHandler_Finalize(RequestHandler* self)
{
    DEBUG_ASSERT( self );
    RequestHandler_Shutdown( self );
    {
        RequestItem* ui = NULL;
        while (NULL != (ui = RequestList_RemoveItem( &self->list )))
        {
            if (ui->type == REQUEST_SUBSCRIBE )
            {
                SubscribeProviderItem* spi = (SubscribeProviderItem*) ui;
                Message_Release( &spi->msg->base.base );
            }

            trace_nioproc_FreeRequestItem(ui);
            PAL_Free(ui);
        }
    }
    self->joined = THREAD_NOT_JOINED;
    self->running = THREAD_NOT_RUNNING; 
}


//
// Create unsubscribe RequestItem
//
static RequestItem* _CreateUnsubscribeProviderItem(
    _In_opt_ SubscriptionContext* ctx,
    _In_ MI_Boolean invokeRequest,
    _In_ MI_Result finalResult )
{
    UnsubscribeProviderItem* ui = (UnsubscribeProviderItem*)PAL_Malloc(sizeof(UnsubscribeProviderItem));
    if (ui)
    {
        ui->base.type = REQUEST_UNSUBSCRIBE;
        ui->base.next = NULL;
        ui->ctx = ctx;
        ui->invokeRequest = invokeRequest;
        ui->finalResult = finalResult;
    }
    
    return (RequestItem*)ui;
}

//
// Create subscribe RequestItem
//
static RequestItem* _CreateSubscribeProviderItem(
    _In_ Provider* provider,
    _In_ SubscribeReq* msg,
    _In_ SubscriptionContext* subscrContext )
{
    SubscribeProviderItem* ui = (SubscribeProviderItem*)PAL_Malloc(sizeof(SubscribeProviderItem));
    if (ui)
    {
        ui->base.type = REQUEST_SUBSCRIBE;
        ui->base.next = NULL;
        ui->provider = provider;
        ui->msg = msg;
        Message_AddRef( &msg->base.base );  // this reference is removed once the scheduled method (_Context_Aux_InvokeSubscribe) is executed
        ui->subscrContext = subscrContext;
    }
    
    trace_nioproc_CreateRequestItem((RequestItem*)ui);

    return (RequestItem*)ui;
}

//
// Get one request item and remove it from list
//
static RequestItem* RequestList_RemoveItem(_Inout_ RequestList* list)
{
    RequestItem* ui = NULL;
    ReadWriteLock_AcquireWrite(&list->lock);
    if (list->head)
    {
        DEBUG_ASSERT(NULL != list->tail);
        ui = list->head;
        list->head = ui->next;
        if (list->head == NULL)
            list->tail = NULL;
    }
    ReadWriteLock_ReleaseWrite(&list->lock);
    return ui;
}

static MI_Result RequestList_RemoveSpecificItem(_Inout_ RequestList* list, _In_ RequestItem* item)
{
    RequestItem* current = NULL;
    RequestItem* prev = NULL;
    MI_Result result = MI_RESULT_NOT_FOUND;

    DEBUG_ASSERT(NULL != list->head);

    if(item == NULL || list == NULL)    
        return MI_RESULT_NOT_FOUND;
    
    ReadWriteLock_AcquireWrite(&list->lock);

    current = list->head;

    while (current)
    {
        if(current == item)
        {
            if(!prev)
            {
                // The item is on the head of the list
                list->head = current->next;

                if(list->head == NULL)
                    list->tail = NULL;
            }
            else 
            {
                // The item is on the middle or the end of the list
                prev->next = current->next;
                
                if(prev->next == NULL)
                    list->tail = prev;
            }

            current->next = NULL;
            result = MI_RESULT_OK;
            break;
        }

        prev = current;
        current = current->next;
    }

    ReadWriteLock_ReleaseWrite(&list->lock);

    return result;
}

//
// Queue the request and spawn a new thread to perform the operation if not
// created yet.
//
static MI_Result RequestList_ScheduleItem(
    _Inout_ RequestList* list,
    _In_ RequestItem* item )
{
    RequestHandler* handler = &g_requesthandler;
    MI_Result finalResult = MI_RESULT_OK;
    
    // insert request into list
    ReadWriteLock_AcquireWrite(&list->lock);
    if (list->tail)
    {
        DEBUG_ASSERT(NULL != list->head);        
        list->tail->next = item;
        list->tail = item;
    }
    else
    {
        DEBUG_ASSERT(NULL == list->head);
        list->head = list->tail = item;
    }
    ReadWriteLock_ReleaseWrite(&list->lock);
    
    // create thread if needed
    Lock_Acquire( &handler->lock );
    if (g_requesthandler.running == THREAD_NOT_RUNNING)
    {
        //
        // OMI has only one IO thread, which might be blocked if call Request to provider here,
        // thus create another thread to invoke Request to provider
        //
        int r = Thread_CreateJoinable(&handler->thread, noniothread_proc, NULL, (void*)handler);
        if ( r != 0 )
        {
            MI_Char buffer[128];
            int err = errno;
            trace_RequestList_ScheduleItem_CreateNonIOThreadFailed(err, ErrnoToString((MI_Uint32)err, buffer, MI_COUNT(buffer)));
            finalResult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }
        else
        {
            g_requesthandler.running = THREAD_RUNNING;
        }
    }
    Lock_Release( &handler->lock );

    if (finalResult != MI_RESULT_OK)
    {        
        // Since result is not OK, remove the item that we just added 
        RequestList_RemoveSpecificItem(list, item);
    }

    return finalResult;
}

//
// Queue the unsubscribe request and spawn a new thread to
// perform the unsubscribe operation if not created yet
//
_Use_decl_annotations_
MI_Result Schedule_UnsubscribeProvider(
    SubscriptionContext* ctx,
    MI_Boolean invokeRequest,
    MI_Result finalResult)
{
    SubMgrSubscription* subscription;
    RequestItem* item = NULL;
    MI_Result r;
    DEBUG_ASSERT(ctx);

    subscription = ctx->subscription;        

    item = _CreateUnsubscribeProviderItem( ctx, invokeRequest, finalResult );
    if ( NULL == item )
    {
        /*
         * FATAL error (out of memory) happened, not much we can do here,
         * restart sever is the only option
         */
        trace_OutOfMemory();

        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    trace_ScheduleRequest_UnsubscribeProvider(UintThreadID(), subscription);

    /* 
     * Add a reference to SubMgrSubscription, which will be released in
     * noniothread_proc
     */
    SubMgrSubscription_Addref( subscription );

    r = RequestList_ScheduleItem( &g_requesthandler.list, item );
    if (r != MI_RESULT_OK )
    {
        /* Decrement the ref count to balance the addref above*/
        SubMgrSubscription_Release( subscription );
        PAL_Free(item);
    }
    return r;
}

//
// Queue sending final result request and spawn a new thread to
// perform the unsubscribe operation if not created yet
//
_Use_decl_annotations_
MI_Result Schedule_SendFinalResult(
    SubscriptionContext* ctx,
    MI_Result finalResult)
{
    return Schedule_UnsubscribeProvider( ctx, MI_FALSE, finalResult );
}

//
// Queue subscribe request and spawn a new thread to
// perform the unsubscribe operation if not created yet
//
MI_Result Schedule_SubscribeRequest(
    _In_ Provider* provider,
    _In_ SubscribeReq* msg,
    _In_ SubscriptionContext* subscrContext )
{
    RequestItem* item = NULL;
    MI_Result r;
    DEBUG_ASSERT(provider);
    STRAND_ASSERTONSTRAND( &subscrContext->baseCtx.strand );

    item = _CreateSubscribeProviderItem( provider, msg, subscrContext );
    Strand_Leave( &subscrContext->baseCtx.strand );
    if ( NULL == item )
    {
        //
        // FATAL error (out of memory) happened, not much we can do here,
        // restart sever is the only option
        //
        trace_OutOfMemory();
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    trace_ScheduleRequest_SubscribeProvider(UintThreadID(), provider, msg, subscrContext);

    r = RequestList_ScheduleItem( &g_requesthandler.list, item );

    if (r != MI_RESULT_OK )
    {
        // Decrement the ref count for the message. This is to balance the Add ref in _CreateSubscribeProviderItem
        Message_Release( &msg->base.base );
        trace_nioproc_FreeRequestItem(item);
        PAL_Free(item);
    }

    return r;
}

//
// A proc running from a spawned thread to unsuscribe the indication provider
//
PAL_Uint32 THREAD_API noniothread_proc(void* p)
{
    RequestHandler* handler = (RequestHandler*)p;
    trace_noniothread_proc_start(UintThreadID());
    while ( THREAD_NOT_JOINED == Atomic_Read(&handler->joined) )
    {
        RequestItem* ui = RequestList_RemoveItem( &handler->list );
        if (NULL == ui)
        {
            PAL_Boolean quit = PAL_FALSE;
            ReadWriteLock_AcquireRead( &handler->list.lock );
            if ( NULL == handler->list.head )
            {
                // shutdown current thread
                Lock_Acquire( &handler->lock );
                handler->running = THREAD_NOT_RUNNING;
                if ( handler->joined == THREAD_NOT_JOINED)
                {
#if !defined(_MSC_VER)
                    // if not joined yet, release thread resources
                    pthread_detach(handler->thread.__impl);
# endif
                    // if not joined yet, then close
                    Thread_Destroy( &handler->thread );
                }
                Lock_Release( &handler->lock );
                quit = PAL_TRUE;
            }
            ReadWriteLock_ReleaseRead( &handler->list.lock );

            if ( PAL_TRUE == quit )
                break; // terminate current thread
            else
                continue;
        }
        else
        {
            switch( ui->type )
            {
            case REQUEST_UNSUBSCRIBE:
                {
                    UnsubscribeProviderItem* upi = (UnsubscribeProviderItem*) ui;
                    SubMgrSubscription* sub = upi->ctx->subscription;
                    DEBUG_ASSERT( sub );
                    SubscrContext_UnsubprvdOrSendfinalmsg(
                        upi->ctx,
                        upi->invokeRequest,
                        upi->finalResult);

                    /*
                     * Release the ref that was incremented prior to queueing the request
                     */
                    SubMgrSubscription_Release( sub );
                }
                break;
            case REQUEST_SUBSCRIBE:
                {
                    SubscribeProviderItem* spi = (SubscribeProviderItem*) ui;

                    spi->subscrContext->baseCtx.provider = spi->provider;
                    spi->subscrContext->baseCtx.strand.info.stored.msg = &spi->msg->base.base;  // a reference was added to this message on _CreateSubscribeProviderItem

                    Strand_ScheduleAux( &(spi->subscrContext->baseCtx.strand), CONTEXT_STRANDAUX_INVOKESUBSCRIBE );
                }
                break;
            }
            trace_nioproc_FreeRequestItem(ui);
            PAL_Free(ui);
        }
    }
    trace_noniothread_proc_end(UintThreadID());
    return 0;
}

