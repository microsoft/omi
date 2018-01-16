/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <pal/palcommon.h>
#include <pal/atomic.h>
#include <pal/lock.h>
#include <pal/sleep.h>
#include <base/Strand.h>
#include <base/log.h>

#if defined(CONFIG_POSIX)

static Selector* timerSelector = NULL;

void Timer_SetSelector(
    _In_ Selector* selector )
{
    timerSelector = selector;
}

MI_Boolean _HandlerTimerCallback(
    Selector* sel,
    Handler* handler,
    MI_Uint32 mask, 
    MI_Uint64 currentTimeUsec)
{
    if (mask & SELECTOR_TIMEOUT)
    {
        /* Returns MI_FALSE to signal it is OK to remove the Handler.
         * actual handling will occur once the Selector calls this func
         * again with SELECTOR_REMOVE.  This is expected to happen 
         * immediately. */
        return MI_FALSE;
    }
    else if (mask & SELECTOR_REMOVE || mask & SELECTOR_DESTROY)
    {
        _Strand_ScheduleTimer( (Strand*)handler->data );
    }
    else if (mask & SELECTOR_ADD)
    {
        trace_Timer_Selector_Added();
    }
    else
    {
        /* No other mask values should be passed.  If so, this will catch them. */
        trace_Timer_Unexpected_Selector_Mask( mask );
        DEBUG_ASSERT(MI_FALSE);
    }

    return MI_TRUE;
}

/* State checks have already been performed.  This function just needs to
 * perform the requested action according to its OS type. */
_Use_decl_annotations_
TimerResult Timer_Start( 
    Timer* timer, 
    Strand* strand )
{
    PAL_Uint64 currentTimeUsec = 0;

    DEBUG_ASSERT( timer );
    DEBUG_ASSERT( strand );

    timer->selector = timerSelector; /* Keeping it as a member allows it to be checked once */

    if (NULL == timer->selector ||
        NULL == timer->selector->rep)
    {
        trace_Timer_Selector_Missing( timer->selector );
        return TimerResult_InvalidArgument;
    }

    if (MI_RESULT_OK == Selector_ContainsHandler(timer->selector, &timer->handler))
    {
        trace_Timer_CannotStartTimer_AlreadyRunning( timer );
        return TimerResult_InvalidArgument;
    }
    
    if (PAL_TRUE != PAL_Time(&currentTimeUsec))
    {
        trace_Timer_Cannot_AccessCurrentTime();
        return TimerResult_Failed;
    }

    timer->reason = TimerReason_Expired;

    timer->handler.fireTimeoutAt = currentTimeUsec + timer->timeoutInUsec;
    timer->handler.sock = INVALID_SOCK;
    timer->handler.data = strand;
    timer->handler.callback = _HandlerTimerCallback;
    timer->handler.handlerName = MI_T("Timer");

    if (MI_RESULT_OK != Selector_AddHandler( timer->selector, &timer->handler ))
    {
        trace_Timer_Cannot_AddHandlerToSelector( timer->selector );
        return TimerResult_Failed;
    }

    trace_Timer_Started_POSIX( timer->timeoutInUsec );
    return TimerResult_Success;
}

_Use_decl_annotations_
void Timer_Fire(
    Timer* timer,
    Strand* strand,
    TimerReason reason )
{
    DEBUG_ASSERT( timer );
    DEBUG_ASSERT( strand );

    /* Handler is zero'd during Timer_Start and Timer_Close.  A NULL callback
     * means that this timer is not active. */
    if (NULL != timer->handler.callback) // TODO: Selector_ContainsHandler is a more thorough check, but less efficient
    {
        PAL_Uint64 currentTimeUsec = 0;

        if (PAL_TRUE != PAL_Time(&currentTimeUsec))
        {
            /* Guarantee it will be a time in the past if current time is not accessible. */
            currentTimeUsec = TIME_NEVER + 1;
            trace_Timer_Cannot_AccessCurrentTime();
        }

        if ( TimerReason_Canceled == reason || timer->handler.fireTimeoutAt > currentTimeUsec )
        {
            /* Due to how Selector works, Selector will not check for timeouts 
             * during long running operations.  In those instances, the time
             * of fireTimeoutAt will have already occurred, but the Selector
             * will have not gotten a chance to detect it yet. That is treated
             * as the default scenario.  This signals that the timeout is treated
             * as a manuallly triggered timeout. */
            timer->reason = reason;
        }
        timer->handler.fireTimeoutAt = currentTimeUsec;

        trace_Timer_ManualTrigger( timer, strand );
        
        Selector_Wakeup( timer->selector, MI_TRUE );
    }
 }

_Use_decl_annotations_
void Timer_Close(
    Timer* timer )
{
    DEBUG_ASSERT( timer );

    if (NULL == timer->handler.callback)
    {
        trace_Timer_Double_Close( timer );
    }
    else
    {
        /* Handler is not present in the Selector's list since this will only 
         * trigger, if SELECTOR_REMOVE has gone through _HandlerTimerCallback,
         * so it is OK to zero out.
         */
        memset( &timer->handler, 0, sizeof(Handler) );
        timer->reason = TimerReason_Expired;

        trace_Timer_Close( timer );
    }
}

#endif /* defined(CONFIG_POSIX) */

