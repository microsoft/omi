/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <base/Strand.h>
#include <base/log.h>
#include <omi_error/errorutil.h>

//------------------------------------------------------------------------------------------------------------
// Debugging aid
//------------------------------------------------------------------------------------------------------------

#if defined(STRAND_ENABLE_DEBUG)
StrandBaseDebugInfo _Strand_BaseNameDebugInfo[Strand_NumMethods+5] = {
    {"<unnamed>",           '@' },
    {"S",                   '*' },
    {"CompleteOpenAsync",   '$' },
    {"Timer",               '&' },
    {"Cancel",              'N' },
    {"CancelSelf",          'n' },
    {"PostControl",         'T' },
    {"Post",                'P' },
    {"PostOther",           'p' },
    {"Ack",                 'A' },
    {"AckOther",            'a' },
    {"Close",               'C' },
    {"CloseOther",          'c' },
    {"<Aux0>",              '0' },
    {"<Aux1>",              '1' },
    {"<Aux2>",              '2' },
    {"<Aux3>",              '3' },
    {"<Aux4>",              '4' },
    {"ERROR!",              '!' },
    {"ERROR!",              '!' },
    {"ERROR!",              '!' } };
StrandBaseDebugInfo _StrandBoth_BaseNameDebugInfo[StrandBoth_NumMethods+5] = {
    {"<unnamed(both)>",     '@' },
    {"SB",                  '*' },
    {"CompleteOpenAsync",   '$' },
    {"Timer",               '&' },
    {"Cancel_Left",         'N' },
    {"Cancel_Right",        'E' },
    {"CancelSelf_Both",     'n' },
    {"PostControl_Left",    'T' },
    {"PostControl_Right",   'R' },
    {"Post_Left",           'P' },
    {"Post_Right",          'S' },
    {"PostOther_Left",      'p' },
    {"PostOther_Right",     's' },
    {"Ack_Left",            'A' },
    {"Ack_Right",           'K' },
    {"AckOther_Left",       'a' },
    {"AckOther_Right",      'k' },
    {"Close_Left",          'C' },
    {"Close_Right",         'L' },
    {"CloseOther_Left",     'c' },
    {"CloseOther_Right",    'l' },
    {"<Aux0_Left>",         '0' },
    {"<Aux1_Left>",         '1' },
    {"<Aux2_Left>",         '2' },
    {"<Aux3_Left>",         '3' },
    {"<Aux4_Left>",         '4' },
    {"<Aux0_Right>",        '5' },
    {"<Aux1_Right>",        '6' },
    {"<Aux2_Right>",        '7' },
    {"<Aux3_Right>",        '8' },
    {"<Aux4_Right>",        '9' },
    {"ERROR!",              '!' },
    {"ERROR!",              '!' },
    {"ERROR!",              '!' } };
StrandBaseDebugInfo _StrandMany_BaseNameDebugInfo[StrandMany_NumMethods+5] = {
    {"<unnamed(many)>",     '@' },
    {"SM",                  '*' },
    {"CompleteOpenAsync",   '$' },
    {"Timer",               '&' },
    {"Cancel(M)",           'N' },
    {"CancelSelf(M)",       'n' },
    {"CancelInternal",      'E' },
    {"PostControl(M)",      'T' },
    {"PostControlInternal", 't' },
    {"Post(M)",             'P' },
    {"PostOther(M)",        'p' },
    {"PostInternal",        'S' },
    {"Ack(M)",              'A' },
    {"AckOther(M)",         'a' },
    {"AckInternal",         'K' },
    {"EntryOperation",      '#' },
    {"Close(M)",            'C' },
    {"CloseOther(M)",       'c' },
    {"CloseInternal",       'L' },
    {"<Aux0(M)>",           '0' },
    {"<Aux1(M)>",           '1' },
    {"<Aux2(M)>",           '2' },
    {"<Aux3(M)>",           '3' },
    {"<Aux4(M)>",           '4' },
    {"ERROR!",              '!' },
    {"ERROR!",              '!' },
    {"ERROR!",              '!' } };
char * _StrandMany_BaseEntryOperationDebugInfo[StrandMany_NumEntryOperations+3] = {
    "Add",
    "Cancel",
    "PostControl",
    "Post",
    "Close",
    "<Aux0>",
    "<Aux1>",
    "<Aux2>",
    "<Aux3>",
    "<Aux4>",
    "Deleted",
    "ERROR!",
    "ERROR!",
    "ERROR!" };

#define SPRINTF_FUNC                    snprintf
#define STRCPY_FUNC(orig, size, dest)   strncpy( (orig), (dest), (size) )

static char * _StrandLogScheduledState(
    _In_                    ptrdiff_t                   state,
    _In_                    StrandBaseDebugInfo const * baseDebugInfo,
                            size_t                      size,
    _Out_writes_(size+4)    char *                      buffer )
{
    ptrdiff_t mask = 1;
    size_t pos = 0;
    size_t bufferPos = 0;

    buffer[bufferPos++] = baseDebugInfo[1].name[0];
    if( '\0' != baseDebugInfo[1].name[1] )
    {
        buffer[bufferPos++] = baseDebugInfo[1].name[1];
    }
    buffer[bufferPos++] = ':';

    while( pos < size )
    {
        if( ( mask & state ) != 0 )
        {
            buffer[bufferPos++] = baseDebugInfo[pos+1].letter;
        }
        mask <<= 1;
        ++pos;
    }
    buffer[bufferPos] = '\0';

    return buffer;
}

#define _STRANDLOGINFOSTATE_SIZE    33                                  // 15 + 16 digits(pointer) + possible 0x prefix
#define _STRANDLOGINFOSTATE_MAXSIZE ((_STRANDLOGINFOSTATE_SIZE*2)+13)   // + two state characters + 10 digits(parent) + terminator

MI_INLINE int _StrandLogInfoState( _In_ InteractionInfo * info, _Out_writes_z_(_STRANDLOGINFOSTATE_SIZE+1) char * buffer )
{
    return SPRINTF_FUNC( buffer, _STRANDLOGINFOSTATE_SIZE, ", %c t:%c%c%co:%c%c %p",
        info->opened ? 'O' : '-',
        info->thisClosedOther ? 'C' : '-',
        info->thisAckPending ? 'A' : '-',
        info->ackPassthru  ? 'P' : ' ',
        info->otherClosedThis ? 'C' : '-',
        info->otherAckPending ? 'A' : '-',
        info->interaction.other );
}

MI_INLINE int _StrandLogStrandState( _In_ Strand* self, _Out_writes_(2) char * buffer )
{
    int written = 0;
    if( self->canceled )
    {
        buffer[written++] = 'N';
    }
    if( self->delayFinish )
    {
        buffer[written++] = 'D';
    }
    if( 0 == written )
    {
        buffer[written++] = '-';
    }

    return written;
}

MI_INLINE int _StrandLogStrandStateParent( _In_ StrandMany* self, _Out_writes_(10) char * buffer )
{
    return SPRINTF_FUNC( buffer, 10, "%d", (unsigned int)self->numEntries );
}

MI_INLINE int _StrandLogInfoStateSingle( _In_ Strand* self, _Out_writes_z_(_STRANDLOGINFOSTATE_MAXSIZE) char * buffer )
{
    int written = _StrandLogStrandState( self, buffer );
    DEBUG_ASSERT( written > 0 && written <= 2 );
    return _StrandLogInfoState( &self->info, buffer+written ) + written;
}

MI_INLINE int _StrandLogInfoStateBoth( _In_ StrandBoth* self, _Out_writes_z_(_STRANDLOGINFOSTATE_MAXSIZE) char * buffer )
{
    int written = _StrandLogStrandState( &self->base, buffer );
    DEBUG_ASSERT( written > 0 && written <= 2 );
    written += _StrandLogInfoState( &self->base.info, buffer+written );
    DEBUG_ASSERT( written > 1 && written <= _STRANDLOGINFOSTATE_SIZE+2 );
    return _StrandLogInfoState( &self->infoRight, buffer+written ) + written;
}

MI_INLINE int _StrandLogInfoStateParent( _In_ StrandMany* self, _Out_writes_z_(_STRANDLOGINFOSTATE_MAXSIZE) char * buffer )
{
    int written = _StrandLogStrandStateParent( self, buffer );
    DEBUG_ASSERT( written > 0 && written <= 10 );
    written += _StrandLogStrandState( &self->strand, buffer+written );
    DEBUG_ASSERT( written > 1 && written <= 12 );
    return _StrandLogInfoState( &self->strand.info, buffer+written ) + written;
}

MI_INLINE void _StrandLogInfoState_Store( _In_ Strand* strand, _Out_writes_z_(_STRANDLOGINFOSTATE_MAXSIZE) char * buffer )
{
    if( STRAND_TYPE_MIDDLE == (strand)->strandType )
    {
        _StrandLogInfoStateBoth( (StrandBoth*)(strand), buffer);
    }
    else if( STRAND_ISTYPE_PARENT( strand ) )
    {
        _StrandLogInfoStateParent( FromOffset(StrandMany,strand,strand), buffer );
    }
    else
    {
        _StrandLogInfoStateSingle( strand, buffer );
    }
}

void _StrandLogWithName( _In_ Strand* self, _In_ const char * operation )
{
    trace_Strand_Action( self, STRAND_DEBUG_GETNAME(self), operation );
}

void _Strand_AssertOnStrand( _In_ Strand* strand )
{
    ThreadID threadId = Thread_ID();
    if( !Thread_Equal(&threadId,&((strand)->testThreadId)) )
    {
        DEBUG_ASSERT( Thread_Equal(&threadId,&((strand)->threadId)) );
        STRAND_ASSERTEXECUTING( strand ); \
    }
}
#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_DEBUG_GETSTATE_USED   \
    char _buffer_STRAND_DEBUG_GETSTATE[StrandBoth_NumMethods+6]
#define STRAND_DEBUG_GETSTATE( strand, state ) \
    _StrandLogScheduledState( state, STRAND_DEBUG_GETBASEINFO(strand), STRAND_DEBUG_GETINFOSIZE(strand)+1, _buffer_STRAND_DEBUG_GETSTATE )
#define STRAND_DEBUG_GETINFOSTATE_USED \
    char _buffer_STRAND_DEBUG_GETINFOSTATE[_STRANDLOGINFOSTATE_MAXSIZE]
#define STRAND_DEBUG_GETINFOSTATE_STORE(strand) \
    _StrandLogInfoState_Store( strand,_buffer_STRAND_DEBUG_GETINFOSTATE)
#define STRAND_DEBUG_GETINFOSTATE_STORED        (_buffer_STRAND_DEBUG_GETINFOSTATE)
// Note that this uses same buffer as STRAND_DEBUG_GETSTATE
#define STRAND_DEBUG_GETNAME_STORE( strand ) \
    STRCPY_FUNC( _buffer_STRAND_DEBUG_GETSTATE, StrandBoth_NumMethods+6, STRAND_DEBUG_GETNAME(strand) )
#define STRAND_DEBUG_GETNAME_STORED             (_buffer_STRAND_DEBUG_GETSTATE)

MI_INLINE
void _Strand_TracePostMsg( _In_ Strand* self, _In_ Message* msg, _In_ const char * info )
{
    DEBUG_ASSERT( NULL != self );
    DEBUG_ASSERT( NULL != msg );
    // TODO why is linux crashing when passing info into the trace function on x86?
    MI_UNUSED(info);
    if( PostResultMsgTag == msg->tag )
    {
        PostResultMsg* msgResult = (PostResultMsg*)msg;
        trace_Strand_TracePostResult(self, msg, msg->tag, msg->operationId, msgResult->result);
    }
    else
    {
        trace_Strand_TracePost(self, msg, msg->tag, MessageName(msg->tag), msg->operationId);
    }
}

#else
#define STRAND_DEBUG_GETSTATE_USED
#define STRAND_DEBUG_GETSTATE( strand, state )  ""
#define STRAND_DEBUG_GETINFOSTATE_USED
#define STRAND_DEBUG_GETINFOSTATE_STORE(strand)
#define STRAND_DEBUG_GETINFOSTATE_STORED        ""
#define STRAND_DEBUG_GETNAME_STORE( strand )
#define STRAND_DEBUG_GETNAME_STORED             ""

MI_INLINE
void _Strand_TracePostMsg( _In_ Strand* self, _In_ Message* msg, _In_ const char * info )
{
}

#endif

#if defined(STRAND_ENABLE_DEBUG)
#define STRAND_SETDEBUG( strand, strandDebugInfo )   (strand)->debug = strandDebugInfo; STRAND_LOGWITHNAME( strand, "Initialize Itself" )
#else
#define STRAND_SETDEBUG( strand, strandDebugInfo )
#endif

#if STRAND_ENABLE_DEBUG == 2
static void _StrandLogState( _In_ Strand* self, _In_ const char * infoName, _In_ InteractionInfo * info )
{
    trace_StrandFlags(
        self,
        STRAND_DEBUG_GETNAME(self),
        infoName,
        info->interaction.other,
        info->opened,
        info->thisClosedOther,
        info->thisAckPending,
        info->otherClosedThis,
        info->otherAckPending,
        info->ackPassthru );
}

#define STRAND_DEBUGSTATE( strand )         _StrandLogState( (strand), "S.:", &((strand)->info) )
#define STRAND_DEBUGSTATE_LEFT( strand )    _StrandLogState( &((strand)->base), "S.Left", &((strand)->base.info) ); \
                                            _StrandLogState( &((strand)->base), "S.(Right)", &((strand)->infoRight) )
#define STRAND_DEBUGSTATE_RIGHT( strand )   _StrandLogState( &((strand)->base), "S.Right", &((strand)->infoRight) ); \
                                            _StrandLogState( &((strand)->base), "S.(Left)", &((strand)->base.info) )
#else
#define STRAND_DEBUGSTATE( strand )
#define STRAND_DEBUGSTATE_LEFT( strand )
#define STRAND_DEBUGSTATE_RIGHT( strand )
#endif

//------------------------------------------------------------------------------------------------------------
#define _GetMethodBit( bitIndex )   ((ptrdiff_t)1 << ((bitIndex)-1))

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Cancel( _In_ Interaction* interaction )
{
    Strand* self = Strand_FromInteraction( interaction );
    _Strand_Schedule( self, BitCancel );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_PostControl( _In_ Interaction* interaction, _In_ Message* msg )
{
    Strand* self = Strand_FromInteraction( interaction );
    Message_AddRef( msg );  // since the actual message use can be delayed
    self->info.stored.controlMsg = msg;
    _Strand_Schedule( self, BitPostControl );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Post( _In_ Interaction* interaction, _In_ Message* msg )
{
    Strand* self = Strand_FromInteraction( interaction );
    Message_AddRef( msg );  // since the actual message use can be delayed
    self->info.stored.msg = msg;
    _Strand_Schedule( self, BitPost );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Ack( _In_ Interaction* interaction )
{
    Strand* self = Strand_FromInteraction( interaction );
    _Strand_Schedule( self, BitAck );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Close( _In_ Interaction* interaction )
{
    Strand* self = Strand_FromInteraction( interaction );
    _Strand_Schedule( self, BitClose );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Left_Cancel( _In_ Interaction* interaction )
{
    Strand* self = Strand_FromInteraction( interaction );
    _Strand_Schedule( self, BitCancel_Left );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Left_PostControl( _In_ Interaction* interaction, _In_ Message* msg )
{
    Strand* self = Strand_FromInteraction( interaction );
    Message_AddRef( msg );  // since the actual message use can be delayed
    self->info.stored.controlMsg = msg;
    _Strand_Schedule( self, BitPostControl_Left );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Left_Post( _In_ Interaction* interaction, _In_ Message* msg )
{
    Strand* self = Strand_FromInteraction( interaction );
    Message_AddRef( msg );  // since the actual message use can be delayed
    self->info.stored.msg = msg;
    _Strand_Schedule( self, BitPost_Left );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Left_Ack( _In_ Interaction* interaction )
{
    Strand* self = Strand_FromInteraction( interaction );
    _Strand_Schedule( self, BitAck_Left );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Left_Close( _In_ Interaction* interaction )
{
    Strand* self = Strand_FromInteraction( interaction );
    _Strand_Schedule( self, BitClose_Left );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Right_Cancel( _In_ Interaction* interaction )
{
    StrandBoth* self = Strand_FromInteractionRight( interaction );
    _Strand_Schedule( (Strand*)self, BitCancel_Right );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Right_PostControl( _In_ Interaction* interaction, _In_ Message* msg )
{
    StrandBoth* self = Strand_FromInteractionRight( interaction );
    Message_AddRef( msg );  // since the actual message use can be delayed
    self->infoRight.stored.controlMsg = msg;
    _Strand_Schedule( (Strand*)self, BitPostControl_Right );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Right_Post( _In_ Interaction* interaction, _In_ Message* msg )
{
    StrandBoth* self = Strand_FromInteractionRight( interaction );
    Message_AddRef( msg );  // since the actual message use can be delayed
    self->infoRight.stored.msg = msg;
    _Strand_Schedule( (Strand*)self, BitPost_Right );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Right_Ack( _In_ Interaction* interaction )
{
    StrandBoth* self = Strand_FromInteractionRight( interaction );
    _Strand_Schedule( (Strand*)self, BitAck_Right );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Right_Close( _In_ Interaction* interaction )
{
    StrandBoth* self = Strand_FromInteractionRight( interaction );
    _Strand_Schedule( (Strand*)self, BitClose_Right );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Many_Cancel( _In_ Interaction* interaction )
{
    Strand* self = Strand_FromInteraction( interaction );
    _Strand_Schedule( self, BitCancel_Many );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Many_PostControl( _In_ Interaction* interaction, _In_ Message* msg )
{
    Strand* self = Strand_FromInteraction( interaction );
    Message_AddRef( msg );  // since the actual message use can be delayed
    self->info.stored.controlMsg = msg;
    _Strand_Schedule( self, BitPostControl_Many );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Many_Post( _In_ Interaction* interaction, _In_ Message* msg )
{
    Strand* self = Strand_FromInteraction( interaction );
    Message_AddRef( msg );  // since the actual message use can be delayed
    self->info.stored.msg = msg;
    _Strand_Schedule( self, BitPost_Many );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Many_Ack( _In_ Interaction* interaction )
{
    Strand* self = Strand_FromInteraction( interaction );
    _Strand_Schedule( self, BitAck_Many );
}

//------------------------------------------------------------------------------------------------------------
void _StrandInteraction_Many_Close( _In_ Interaction* interaction )
{
    Strand* self = Strand_FromInteraction( interaction );
    _Strand_Schedule( self, BitClose_Many );
}

//------------------------------------------------------------------------------------------------------------
MI_INLINE
MI_Boolean _StrandMethodImp_CheckFinished( _In_ InteractionInfo* info )
{
    return
        info->thisClosedOther
        && !info->thisAckPending
        && info->otherClosedThis
        && !info->otherAckPending;
}

//------------------------------------------------------------------------------------------------------------
MI_INLINE
MI_Boolean _StrandMethodImp_Cancel( _In_ Strand* self, _In_ InteractionInfo* info)
{
    DEBUG_ASSERT( !self->canceled );

    self->canceled = MI_TRUE;

    if( NULL != info->userFT->Cancel )
    {
        (*info->userFT->Cancel)(self);
    }

    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_INLINE
MI_Boolean _StrandMethodImp_PostControl( _In_ Strand* self, _In_ InteractionInfo* info)
{
    DEBUG_ASSERT( info->opened );
    DEBUG_ASSERT( !info->otherClosedThis );
    DEBUG_ASSERT( NULL != info->userFT->PostControl );
    DEBUG_ASSERT( NULL != info->stored.controlMsg );

    info->userFT->PostControl( self, info->stored.controlMsg );
    Message_Release( info->stored.controlMsg );  // now we can remove the reference added on _StrandInteraction_*

    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_INLINE
MI_Boolean _StrandMethodImp_Post( _In_ Strand* self, _In_ InteractionInfo* info)
{
    DEBUG_ASSERT( info->opened );
    DEBUG_ASSERT( !info->otherClosedThis );
    DEBUG_ASSERT( NULL != info->userFT->Post );
    DEBUG_ASSERT( NULL != info->stored.msg );
    DEBUG_ASSERT( !info->otherAckPending );

    info->otherAckPending = MI_TRUE;
    info->userFT->Post( self, info->stored.msg );
    Message_Release( info->stored.msg );  // now we can remove the reference added on _StrandInteraction_*

    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_INLINE
MI_Boolean _StrandMethodImp_Ack( _In_ Strand* self, _In_ InteractionInfo* info)
{
    // note that info->otherClosedThis may be true here
    DEBUG_ASSERT( info->thisAckPending );
    DEBUG_ASSERT( info->opened );

    info->thisAckPending = MI_FALSE;

    if( NULL != info->userFT->Ack )
    {
        info->userFT->Ack( self );
    }

    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_INLINE
MI_Boolean _StrandMethodImp_Close( _In_ Strand* self, _In_ InteractionInfo* info)
{
    DEBUG_ASSERT( info->opened );
    DEBUG_ASSERT( !info->otherClosedThis );

    info->otherClosedThis = MI_TRUE;

    if( NULL != info->userFT->Close )
    {
        (*info->userFT->Close)(self);
    }

    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_INLINE
MI_Boolean _StrandMethodImp_PostOther( _In_ InteractionInfo* info)
{
    _Strand_Post_Imp( info, info->otherMsg );
    Message_Release( info->otherMsg );  // now we can remove the reference added on Strand_SchedulePost*
    info->otherMsg = NULL;
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_CheckFinished( _In_ Strand* self )
{
    return _StrandMethodImp_CheckFinished( &self->info ) && !self->delayFinish;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Timer( _In_ Strand* self)
{
    TimerReason reason;

    DEBUG_ASSERT( NULL != self->timer );
    DEBUG_ASSERT( NULL != self->info.userFT->Timer );

    STRAND_DEBUGSTATE( self );

    reason = self->timer->reason;

    Timer_Close(self->timer);
    self->timer = NULL;
    (*self->info.userFT->Timer)(self, reason);

    // A canceled timer shouldn't be re-started
    DEBUG_ASSERT( NULL == self->timer || reason != TimerReason_Canceled );

    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
// Internal use
void _Strand_CancelPropagate(
    _In_ Strand *   self);

// Internal use
MI_INLINE
void _Strand_CompleteOpenAsyncImp(
    _In_        Strand *            self,
    _In_        InteractionInfo*    info )
{
    STRAND_ASSERTONSTRAND(self);
    DEBUG_ASSERT( !info->opened );

    info->opened = MI_TRUE;

    if( self->canceled )
    {
        _Strand_CancelPropagate( self );
    }
}

MI_Boolean _StrandMethod_CompleteOpenAsync( _In_ Strand* self)
{
    STRAND_DEBUGSTATE( self );

    _Strand_CompleteOpenAsyncImp( self, &self->info );
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Cancel( _In_ Strand* self)
{
    STRAND_DEBUGSTATE( self );

    if( !self->canceled )
    {
        if( STRAND_TYPE_RIGHTMOST == self->strandType && self->info.opened && !self->info.thisClosedOther )
        {
            // return it to the other side
            self->info.interaction.other->ft->Cancel( self->info.interaction.other );
        }

        _StrandMethodImp_Cancel(self, &self->info );
    }
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_PostControl( _In_ Strand* self)
{
    _Strand_TracePostMsg(self, self->info.stored.controlMsg, "(Control)");
    STRAND_DEBUGSTATE( self );

    return _StrandMethodImp_PostControl(self, &self->info );
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Post( _In_ Strand* self)
{
    _Strand_TracePostMsg(self, self->info.stored.msg, "");
    STRAND_DEBUGSTATE( self );

    return _StrandMethodImp_Post(self, &self->info );
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Ack( _In_ Strand* self)
{
    STRAND_DEBUGSTATE( self );

    return _StrandMethodImp_Ack(self, &self->info );
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Close( _In_ Strand* self)
{
    STRAND_DEBUGSTATE( self );

    return _StrandMethodImp_Close(self, &self->info );
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_PostOther( _In_ Strand* self)
{
    MI_Boolean res = _StrandMethodImp_PostOther( &self->info );
    STRAND_LOGWITHNAME( self, "Returning from PostOther" );
    return res;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_AckOther( _In_ Strand* self)
{
    _Strand_Ack_Imp( &self->info );
    STRAND_LOGWITHNAME( self, "Returning from AckOther" );
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_CloseOther( _In_ Strand* self)
{
    _Strand_Close_Imp( &self->info );
    STRAND_LOGWITHNAME( self, "Returning from CloseOther" );
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_CancelSelf( _In_ Strand* self)
{
    Strand_Cancel( self );
    STRAND_LOGWITHNAME( self, "Returning from CancelSelf" );
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Aux0( _In_ Strand* self)
{
    DEBUG_ASSERT( NULL != self->info.userFT->Aux0 );
    self->info.userFT->Aux0( self );
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Aux1( _In_ Strand* self)
{
    DEBUG_ASSERT( NULL != self->info.userFT->Aux1 );
    self->info.userFT->Aux1( self );
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Aux2( _In_ Strand* self)
{
    DEBUG_ASSERT( NULL != self->info.userFT->Aux2 );
    self->info.userFT->Aux2( self );
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Aux3( _In_ Strand* self)
{
    DEBUG_ASSERT( NULL != self->info.userFT->Aux3 );
    self->info.userFT->Aux3( self );
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Aux4( _In_ Strand* self)
{
    DEBUG_ASSERT( NULL != self->info.userFT->Aux4 );
    self->info.userFT->Aux4( self );
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Both_CheckFinished( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;

    if (self->asyncOpenInProgress)
        return MI_FALSE;

    return _StrandMethodImp_CheckFinished( &self->base.info )
        && ((!self->infoRight.opened) ||  _StrandMethodImp_CheckFinished( &self->infoRight )) //check right interation state only if its opeened
        && !self->base.delayFinish;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Both_CompleteOpenAsync( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;
    STRAND_DEBUGSTATE( self );

    _Strand_CompleteOpenAsyncImp( &self->base, &self->infoRight );
    self->asyncOpenInProgress = MI_FALSE;
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Left_Cancel( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;

    STRAND_DEBUGSTATE_LEFT( self );

    if( !self->base.canceled  )
    {
        // We pass to the right only if we have not been cancel already becase in that case it has go to the right already
        // (cancelations always flow to the right first)
        // Note that we need to check this first as the canceled below may close the interaction with the right side
        if( self->infoRight.opened && !self->infoRight.thisClosedOther )
        {
            self->infoRight.interaction.other->ft->Cancel( self->infoRight.interaction.other );
        }

        _StrandMethodImp_Cancel(self_, &self->base.info );
    }
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Left_PostControl( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;

    _Strand_TracePostMsg(self_, self->base.info.stored.controlMsg, "(Control Left)");
    STRAND_DEBUGSTATE_LEFT( self );

    if( NULL == self->base.info.userFT->PostControl && self->infoRight.opened )
    {
        DEBUG_ASSERT( !self->infoRight.thisClosedOther );
        // post passing thru to the other side
        StrandBoth_PostControlRight( self, self->base.info.stored.controlMsg );
        Message_Release( self->base.info.stored.controlMsg );  // now we can remove the reference added on _StrandInteraction_*
        return MI_FALSE;
    }
    else
    {
        return _StrandMethodImp_PostControl(self_, &self->base.info );
    }
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Left_Post( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;

    _Strand_TracePostMsg(self_, self->base.info.stored.msg, "Left");
    STRAND_DEBUGSTATE_LEFT( self );

    if( NULL == self->base.info.userFT->Post && self->infoRight.opened )
    {
        DEBUG_ASSERT( !self->infoRight.thisClosedOther );
        // post passing thru to the other side
        StrandBoth_PostPassthruRight( self, self->base.info.stored.msg );
        Message_Release( self->base.info.stored.msg );  // now we can remove the reference added on _StrandInteraction_*
        return MI_FALSE;
    }
    else
    {
        return _StrandMethodImp_Post(self_, &self->base.info );
    }
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Left_Ack( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;

    STRAND_DEBUGSTATE_LEFT( self );
    DEBUG_ASSERT( self->base.info.opened );

    if( self->base.info.ackPassthru || NULL == self->base.info.userFT->Ack )
    {
        DEBUG_ASSERT( self->base.info.thisAckPending );
        self->base.info.thisAckPending = MI_FALSE;

        if( self->infoRight.otherAckPending )
        {
            self->base.info.ackPassthru = MI_FALSE;
            StrandBoth_AckRight( self );
        }
        else
        {
            DEBUG_ASSERT( !self->base.info.ackPassthru );
        }

        return MI_FALSE;
    }
    else
    {
        return _StrandMethodImp_Ack(self_, &self->base.info );
    }
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Left_Close( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;

    STRAND_DEBUGSTATE_LEFT( self );

    if( NULL == self->base.info.userFT->Close )
    {
        // we take care of sending the close as passthru
        if( self->infoRight.opened && !self->infoRight.thisClosedOther )
        {
            StrandBoth_CloseRight( self );
        }
    }

    return _StrandMethodImp_Close(self_, &self->base.info );
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Right_Cancel( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;

    STRAND_DEBUGSTATE_RIGHT( self );

    // We need to check this first as the canceled below may close the interaction with the left side
    if( self->base.info.opened && !self->base.info.thisClosedOther && !self->leftCanceled )
    {
        self->leftCanceled = MI_TRUE;
        // We pass to the left even if we have been cancel already becase thet should be the cancelation coming back from the right
        self->base.info.interaction.other->ft->Cancel( self->base.info.interaction.other );
    }

    if( !self->base.canceled )
    {
        _StrandMethodImp_Cancel(self_, &self->infoRight );
    }
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Right_PostControl( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;

    _Strand_TracePostMsg(self_, self->infoRight.stored.controlMsg, "(Control Right)");
    STRAND_DEBUGSTATE_RIGHT( self );

    if( NULL == self->infoRight.userFT->PostControl && self->base.info.opened )
    {
        DEBUG_ASSERT( !self->base.info.thisClosedOther );
        // post passing thru to the other side
        StrandBoth_PostControlLeft( self, self->infoRight.stored.controlMsg );
        Message_Release( self->infoRight.stored.controlMsg );  // now we can remove the reference added on _StrandInteraction_*
        return MI_FALSE;
    }
    else
    {
        return _StrandMethodImp_PostControl(self_, &self->infoRight );
    }
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Right_Post( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;

    _Strand_TracePostMsg(self_, self->infoRight.stored.msg, "Right");
    STRAND_DEBUGSTATE_RIGHT( self );

    if( NULL == self->infoRight.userFT->Post && self->base.info.opened )
    {
        DEBUG_ASSERT( !self->base.info.thisClosedOther );
        // post passing thru to the other side
        StrandBoth_PostPassthruLeft( self, self->infoRight.stored.msg );
        Message_Release( self->infoRight.stored.msg );  // now we can remove the reference added on _StrandInteraction_*
        return MI_FALSE;
    }
    else
    {
        return _StrandMethodImp_Post(self_, &self->infoRight );
    }
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Right_Ack( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;

    STRAND_DEBUGSTATE_RIGHT( self );
    DEBUG_ASSERT( self->infoRight.opened );

    if( self->infoRight.ackPassthru || NULL == self->infoRight.userFT->Ack )
    {
        DEBUG_ASSERT( self->infoRight.thisAckPending );

        self->infoRight.thisAckPending = MI_FALSE;

        if( self->base.info.otherAckPending )
        {
            self->infoRight.ackPassthru = MI_FALSE;
            StrandBoth_AckLeft( self );
        }
        else
        {
            DEBUG_ASSERT( !self->infoRight.ackPassthru );
        }

        return MI_FALSE;
    }
    else
    {
        return _StrandMethodImp_Ack(self_, &self->infoRight );
    }
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Right_Close( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;

    STRAND_DEBUGSTATE_RIGHT( self );

    if( NULL == self->infoRight.userFT->Close )
    {
        // we take care of sending the close as passthru
        if( self->base.info.opened && !self->base.info.thisClosedOther )
        {
            StrandBoth_CloseLeft( self );
        }
    }

    return _StrandMethodImp_Close(self_, &self->infoRight );
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Right_PostOther( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;

    MI_Boolean res = _StrandMethodImp_PostOther( &self->infoRight );
    STRAND_LOGWITHNAME( self_, "Returning from PostOther(Right)" );
    return res;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Right_AckOther( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;

    _Strand_Ack_Imp( &self->infoRight );
    STRAND_LOGWITHNAME( self_, "Returning from AckOther(Right)" );
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Right_CloseOther( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;

    _Strand_Close_Imp( &self->infoRight );
    STRAND_LOGWITHNAME( self_, "Returning from CloseOther(Right)" );
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Both_CancelSelf( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;

    Strand_Cancel( &self->base );
    STRAND_LOGWITHNAME( self_, "Returning from CancelSelf(Both)" );
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Right_Aux0( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;
    DEBUG_ASSERT( NULL != self->infoRight.userFT->Aux0 );

    self->infoRight.userFT->Aux0( self_ );
    return MI_FALSE;
}

MI_Boolean _StrandMethod_Right_Aux1( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;
    DEBUG_ASSERT( NULL != self->infoRight.userFT->Aux1 );

    self->infoRight.userFT->Aux1( self_ );
    return MI_FALSE;
}

MI_Boolean _StrandMethod_Right_Aux2( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;
    DEBUG_ASSERT( NULL != self->infoRight.userFT->Aux2 );

    self->infoRight.userFT->Aux2( self_ );
    return MI_FALSE;
}

MI_Boolean _StrandMethod_Right_Aux3( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;
    DEBUG_ASSERT( NULL != self->infoRight.userFT->Aux3 );

    self->infoRight.userFT->Aux3( self_ );
    return MI_FALSE;
}

MI_Boolean _StrandMethod_Right_Aux4( _In_ Strand* self_)
{
    StrandBoth* self = (StrandBoth*)self_;
    DEBUG_ASSERT( NULL != self->infoRight.userFT->Aux4 );

    self->infoRight.userFT->Aux4( self_ );
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
typedef enum _EntryOperationAction
{
    EOContinue,
    EORetry,
    EODeleted
} EntryOperationAction;

typedef EntryOperationAction (*StrandEntryOperation)( _In_ StrandMany* );

EntryOperationAction _StrandEntryOperation_Add( _In_ StrandMany* self )
{
    MI_Boolean failed = MI_FALSE;
    MI_Boolean added = MI_FALSE;
    Message * msg = self->currentEntry->strand.info.stored.msg;

    DEBUG_ASSERT( NULL != self->userInternalFT->NewEntry );

    if( self->strand.canceled  )
    {
        trace_StrandEntryOperation_AddCanceled(
            (unsigned int)self->numEntries,
            self,
            STRAND_DEBUG_GETNAME(&self->strand),
            &self->currentEntry->strand,
            STRAND_DEBUG_GETNAME(&self->currentEntry->strand) );
        failed = MI_TRUE;
        // we dont even call the user method in this case
    }
    else
    {
        if( HashMap_Insert( &self->many, &self->currentEntry->bucket ) )
        {
            trace_StrandEntryOperation_AddFailed(
                (unsigned int)self->numEntries,
                self,
                STRAND_DEBUG_GETNAME(&self->strand),
                &self->currentEntry->strand,
                STRAND_DEBUG_GETNAME(&self->currentEntry->strand) );
            failed = MI_TRUE;
        }
        else
        {
            ++(self->numEntries);

            trace_StrandEntryOperation_Add(
                (unsigned int)self->numEntries,
                self,
                STRAND_DEBUG_GETNAME(&self->strand),
                &self->currentEntry->strand,
                STRAND_DEBUG_GETNAME(&self->currentEntry->strand) );

            added = MI_TRUE;
        }

        if( NULL != self->userInternalFT && NULL != self->userInternalFT->NewEntry )
        {
            self->userInternalFT->NewEntry( self, self->currentEntry, msg, &failed );
        }
    }

    if( NULL != msg )
    {
        if( failed || NULL == self->userInternalFT || NULL == self->userInternalFT->AddedToParent )
        {
            self->currentEntry->strand.info.stored.msg = NULL;
            Message_Release(msg);
        }
        // Else: We dont release the message in this case (we keep it on 'stored')
        // It will be deleted once the AddedToParent method is executed
    }

    if( failed )
    {
        if( added )
        {
            StrandMany_DeleteEntry( self->currentEntry );
        }
        else
        {
            SList_Free( self->currentEntry );
        }
        return EODeleted;
    }

    return EOContinue;
}

EntryOperationAction _StrandEntryOperation_Cancel( _In_ StrandMany* self )
{
    trace_StrandEntryOperation_Cancel( self, STRAND_DEBUG_GETNAME(&self->strand),self->strand.canceled );

    if( !self->strand.canceled )
    {
        // since we are in the middle, always forward to the other side
        self->strand.info.interaction.other->ft->Cancel( self->strand.info.interaction.other );
        _StrandMethodImp_Cancel( &self->strand, &self->strand.info );
    }
    else if( self->strand.strandType == STRAND_TYPE_PARENTLEFT )
    {
        // since we are in the left-middle this can be cancelation coming back from right,
        // so pass back to the left
        self->strand.info.interaction.other->ft->Cancel( self->strand.info.interaction.other );
    }

    return EOContinue;
}

EntryOperationAction _StrandEntryOperation_PostControl( _In_ StrandMany* self )
{
    DEBUG_ASSERT( NULL != self->currentEntry->toParent.controlMsg );

    if( self->strand.info.thisClosedOther )
    {
        trace_StrandEntryOperation_PostControl_PostIgnored(
            self,
            STRAND_DEBUG_GETNAME(&self->strand),
            self->currentEntry->toParent.controlMsg);
    }
    else
    {
        trace_StrandEntryOperation_PostControl_ToParent(
            self,
            STRAND_DEBUG_GETNAME(&self->strand),
            self->currentEntry->toParent.controlMsg);

        if( NULL != self->userInternalFT && NULL != self->userInternalFT->EntryPostControl )
        {
            self->userInternalFT->EntryPostControl( self, self->currentEntry->toParent.controlMsg );
        }
        else
        {
            Strand_Post( &self->strand, self->currentEntry->toParent.controlMsg );
        }
    }
    Message_Release( self->currentEntry->toParent.controlMsg ); // ref added on StrandEntry_PostControlParent
    self->currentEntry->toParent.controlMsg = NULL;
    return EOContinue;
}

EntryOperationAction _StrandEntryOperation_Post( _In_ StrandMany* self )
{
    DEBUG_ASSERT( NULL != self->currentEntry->toParent.msg );

    if( self->strand.info.thisClosedOther )
    {
        trace_StrandEntryOperation_Post_IgnoredAfterClose(
            self,
            STRAND_DEBUG_GETNAME(&self->strand),
            self->currentEntry->toParent.msg);
        Message_Release( self->currentEntry->toParent.msg ); // ref added on StrandEntry_PostParent
        self->currentEntry->toParent.msg = NULL;
        return EOContinue;
    }

    if( !self->strand.info.thisAckPending )
    {
        trace_StrandEntryOperation_Post_ToParent(
            self,
            STRAND_DEBUG_GETNAME(&self->strand),
            self->currentEntry->toParent.msg);

        if( NULL != self->userInternalFT && NULL != self->userInternalFT->EntryPost )
        {
            self->userInternalFT->EntryPost( self, self->currentEntry->toParent.msg );
        }
        else
        {
            Strand_Post( &self->strand, self->currentEntry->toParent.msg );
        }
        Message_Release( self->currentEntry->toParent.msg ); // ref added on StrandEntry_PostParent
        self->currentEntry->toParent.msg = NULL;
        return EOContinue;
    }
    else
    {
//        trace_StrandEntryOperation_Post_CannotPostWaitingOnAck(
//            self,
//            STRAND_DEBUG_GETNAME(&self->strand),
//            self->currentEntry->toParent.msg);
        return EORetry;
    }
}

EntryOperationAction _StrandEntryOperation_Close( _In_ StrandMany* self )
{
    trace_StrandEntryOperation_Close(
        self,
        STRAND_DEBUG_GETNAME(&self->strand),
        self->strand.info.thisClosedOther );

    if( !self->strand.info.thisClosedOther )
    {
        if( NULL != self->userInternalFT && NULL != self->userInternalFT->EntryClose )
        {
            self->userInternalFT->EntryClose( self );
        }
        else
        {
            Strand_Close( &self->strand );
        }
    }

    return EOContinue;
}

EntryOperationAction _StrandEntryOperation_Deleted( _In_ StrandMany* self )
{
    trace_StrandEntryOperation_Deleted(
        self,
        STRAND_DEBUG_GETNAME(&self->strand),
        self->currentEntry,
        STRAND_DEBUG_GETNAME(&self->currentEntry->strand) );

    StrandMany_DeleteEntry(self->currentEntry);

    if( NULL != self->userInternalFT && NULL != self->userInternalFT->EntryDeleted )
    {
        self->userInternalFT->EntryDeleted( self );
    }

    return EODeleted;
}

EntryOperationAction _StrandEntryOperation_Aux0( _In_ StrandMany* self )
{
    DEBUG_ASSERT( NULL != self->strand.info.userFT->Aux0 );
    self->strand.info.userFT->Aux0( &self->strand );
    return EOContinue;
}

EntryOperationAction _StrandEntryOperation_Aux1( _In_ StrandMany* self )
{
    DEBUG_ASSERT( NULL != self->strand.info.userFT->Aux1 );
    self->strand.info.userFT->Aux1( &self->strand );
    return EOContinue;
}

EntryOperationAction _StrandEntryOperation_Aux2( _In_ StrandMany* self )
{
    DEBUG_ASSERT( NULL != self->strand.info.userFT->Aux2 );
    self->strand.info.userFT->Aux2( &self->strand );
    return EOContinue;
}

EntryOperationAction _StrandEntryOperation_Aux3( _In_ StrandMany* self )
{
    DEBUG_ASSERT( NULL != self->strand.info.userFT->Aux3 );
    self->strand.info.userFT->Aux3( &self->strand );
    return EOContinue;
}

EntryOperationAction _StrandEntryOperation_Aux4( _In_ StrandMany* self )
{
    DEBUG_ASSERT( NULL != self->strand.info.userFT->Aux4 );
    self->strand.info.userFT->Aux4( &self->strand );
    return EOContinue;
}

//------------------------------------------------------------------------------------------------------------
static StrandEntryOperation _StrandEntryOperations_FT[] = {
    _StrandEntryOperation_Add,
    _StrandEntryOperation_Cancel,
    _StrandEntryOperation_PostControl,
    _StrandEntryOperation_Post,
    _StrandEntryOperation_Close,
    _StrandEntryOperation_Aux0,
    _StrandEntryOperation_Aux1,
    _StrandEntryOperation_Aux2,
    _StrandEntryOperation_Aux3,
    _StrandEntryOperation_Aux4,
    _StrandEntryOperation_Deleted,
    NULL, // just give some overflow NULL methods for safety
    NULL,
    NULL };

//------------------------------------------------------------------------------------------------------------
size_t _StrandMany_HashMapHashProc(const HashBucket* bucket)
{
    return (size_t)bucket;
}

int _StrandMany_HashMapEqualProc(_In_ const HashBucket* bucket1, _In_ const HashBucket* bucket2)
{
    return bucket1 == bucket2;
}

void _StrandMany_HashMapReleaseProc(_In_ HashBucket* bucket1)
{
    // nothing to do here (entry is deleted on _StrandMethod_RunPendingOperations)
}

//------------------------------------------------------------------------------------------------------------
void StrandMany_CancelAllEntries( _In_ StrandMany* self )
{
    StrandEntry* entry;
    STRAND_ASSERTONSTRAND( &self->strand );

    StrandMany_BeginIteration( self );
    while( NULL != (entry = StrandMany_Iterate( self )) )
    {
        StrandMany_CancelEntry( entry );
    }
}

void StrandMany_CloseAllEntries( _In_ StrandMany* self )
{
    StrandEntry* entry;
    STRAND_ASSERTONSTRAND( &self->strand );

    StrandMany_BeginIteration( self );
    while( NULL != (entry = StrandMany_Iterate( self )) )
    {
        StrandMany_CloseEntry( entry );
    }
}

void StrandMany_PostEntry( _In_ StrandEntry* entry, _In_ Message* msg )
{
    STRAND_ASSERTONSTRAND( &entry->parent->strand );

    Message_AddRef( msg );  // add ref before assigning and scheduling
    entry->fromParent.msg = msg;
    _Strand_Schedule( &entry->strand, BitPostInternal );
}

void StrandMany_PostAll( _In_ StrandMany* self, _In_ Message* msg )
{
    StrandEntry* entry;

    STRAND_ASSERTONSTRAND( &self->strand );

    StrandMany_BeginIteration( self );
    while( NULL != (entry = StrandMany_Iterate( self )) )
    {
        StrandMany_PostEntry( entry, msg );
    }
}

MI_Boolean StrandMany_PostFindEntry( _In_ StrandMany* self, _In_ Message* msg )
{
    StrandEntry* entry;

    STRAND_ASSERTONSTRAND( &self->strand );
    DEBUG_ASSERT( NULL != self->findEntryProc );

    entry = self->findEntryProc( self, msg );
    if( NULL != entry )
    {
        StrandMany_PostEntry( entry, msg );
        return MI_TRUE;
    }
    else
    {
        return MI_FALSE;
    }
}

void StrandMany_PostControlEntry( _In_ StrandEntry* entry, _In_ Message* msg )
{
    STRAND_ASSERTONSTRAND( &entry->parent->strand );

    Message_AddRef( msg );  // add ref before assigning and scheduling
    entry->fromParent.controlMsg = msg;
    _Strand_Schedule( &entry->strand, BitPostControlInternal );
}

void StrandMany_PostControlAll( _In_ StrandMany* self, _In_ Message* msg )
{
    StrandEntry* entry;

    STRAND_ASSERTONSTRAND( &self->strand );

    StrandMany_BeginIteration( self );
    while( NULL != (entry = StrandMany_Iterate( self )) )
    {
        StrandMany_PostControlEntry( entry, msg );
    }
}

MI_Boolean StrandMany_PostControlFindEntry( _In_ StrandMany* self, _In_ Message* msg )
{
    StrandEntry* entry;

    STRAND_ASSERTONSTRAND( &self->strand );
    DEBUG_ASSERT( NULL != self->findEntryProc );

    entry = self->findEntryProc( self, msg );
    if( NULL != entry )
    {
        StrandMany_PostControlEntry( entry, msg );
        return MI_TRUE;
    }
    else
    {
        return MI_FALSE;
    }
}

//------------------------------------------------------------------------------------------------------------
void _StrandEntry_ScheduleParent( _In_ StrandEntry* self, EntryOperationMaskType entryOperationBit )
{
    // this can be called during creation (StrandEntry_ScheduleAdd) so we cannot call STRAND_ASSERTONSTRAND( &self->strand );
    if( 0 == self->operationScheduled )
    {
        self->operationScheduled = entryOperationBit;
        SList_PushAtomic( &self->parent->pending, &self->entry );
        _Strand_ScheduleEntryOperation( &self->parent->strand, MI_TRUE, &self->strand, entryOperationBit );
    }
    else
    {
        DEBUG_ASSERT( 0 == (self->operationsPending & entryOperationBit) );
        self->operationsPending |= entryOperationBit;
    }
}

void StrandEntry_PostParent( _In_ StrandEntry* self, _In_ Message* msg )
{
    STRAND_ASSERTONSTRAND( &self->strand );
    DEBUG_ASSERT( NULL == self->toParent.msg );
    Message_AddRef( msg );
    self->toParent.msg = msg;
    _StrandEntry_ScheduleParent( self, BitEntryPost );
}

void StrandEntry_PostParentPassthru( _In_ StrandEntry* self, _In_ Message* msg )
{
    DEBUG_ASSERT( !self->ackPassthru );
    self->ackPassthru = MI_TRUE;
    StrandEntry_PostParent( self, msg );
}

void StrandEntry_PostControlParent( _In_ StrandEntry* self, _In_ Message* msg )
{
    STRAND_ASSERTONSTRAND( &self->strand );
    DEBUG_ASSERT( NULL == self->toParent.controlMsg );
    Message_AddRef( msg );
    self->toParent.controlMsg = msg;
    _StrandEntry_ScheduleParent( self, BitEntryPostControl );
}

//------------------------------------------------------------------------------------------------------------
#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26001) // bogus "we know the strand points to the middle of the StrandMany struct" and Linux sal parser doesnt recognize something like _Readable_elements_(_Inexpressible_(StrandMany))
#endif /* _PREFAST_ */

MI_Boolean _StrandMethod_Parent_CheckFinished( _In_ Strand* self_ )
{
    StrandMany* self = StrandMany_FromStrand(self_);

    return ( 0 == self->numEntries ) && _StrandMethodImp_CheckFinished( &self->strand.info ) && !self->strand.delayFinish;
}

MI_Boolean _StrandMethod_Parent_Cancel( _In_ Strand* self_)
{
    StrandMany* self = StrandMany_FromStrand(self_);

    STRAND_DEBUGSTATE( self_ );

    if( !self->strand.canceled )
    {
        // if it is on the right, we dont need to pass cancel to the right
        // if it is on the left, canceling entries passes cancel to the right

        // now cancel all entries
        StrandMany_CancelAllEntries( self );

        _StrandMethodImp_Cancel( &self->strand, &self->strand.info );
    }

    return MI_FALSE;
}

MI_Boolean _StrandMethod_Parent_PostControl( _In_ Strand* self_)
{
    StrandMany* self = StrandMany_FromStrand(self_);

    _Strand_TracePostMsg(self_, self->strand.info.stored.controlMsg, "(Control Parent)");
    STRAND_DEBUGSTATE( self_ );
    DEBUG_ASSERT( NULL != self->strand.info.stored.controlMsg );

    if( NULL != self->strand.info.userFT->PostControl )
    {
        self->strand.info.userFT->PostControl( &self->strand, self->strand.info.stored.controlMsg );
    }
    else
    {
        if( NULL == self->findEntryProc )
        {
            // Since we dont have true searching capabilities sent to all entries
            StrandMany_PostControlAll( self, self->strand.info.stored.controlMsg );
        }
        else
        {
            MI_Boolean ret = StrandMany_PostControlFindEntry( self, self->strand.info.stored.controlMsg );
            if (!ret)
            {
                DEBUG_ASSERT( ret );
            }
        }
    }

    Message_Release( self->strand.info.stored.controlMsg );  // now we can remove the reference added on _StrandInteraction_*
    self->strand.info.stored.controlMsg = NULL;

    return MI_FALSE;
}

MI_Boolean _StrandMethod_Parent_Post( _In_ Strand* self_)
{
    StrandMany* self = StrandMany_FromStrand( self_);
    Message* storedmsg = self->strand.info.stored.msg;
    _Strand_TracePostMsg(self_, storedmsg, "(Parent)");
    STRAND_DEBUGSTATE( self_ );
    DEBUG_ASSERT( !self->strand.info.otherAckPending );
    DEBUG_ASSERT( NULL != storedmsg );

    self->strand.info.stored.msg = NULL;
    self->strand.info.otherAckPending = MI_TRUE;

    if( NULL != self->strand.info.userFT->Post )
    {
        self->strand.info.userFT->Post( &self->strand, storedmsg );
    }
    else
    {
        if( NULL == self->findEntryProc )
        {
            // Since we dont have true searching capabilities sent to all entries
            StrandMany_PostAll( self, storedmsg );
        }
        else
        {
            MI_Boolean ret = StrandMany_PostFindEntry( self, storedmsg );
            if (!ret)
            {
                DEBUG_ASSERT( ret );
            }
        }

        Strand_Ack( &self->strand );
    }

    Message_Release( storedmsg );  // now we can remove the reference added on _StrandInteraction_*

    return MI_FALSE;
}

#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */

void _StrandMethod_Parent_RunPendingOperations( _In_ StrandMany * self )
{
    unsigned long bitIndex;
    SListHead retryList;
    SListEntry * retryEntry;

    DEBUG_ASSERT( NULL == self->currentEntry );

    SList_Init( &retryList );
    self->pendingRetry = MI_FALSE;

    while( NULL != ( self->currentEntry = (StrandEntry*)SList_PopAtomic( &self->pending ) ) )
    {
        bitIndex = GetFirstSetLSB( self->currentEntry->operationScheduled );
        DEBUG_ASSERT( bitIndex );

//        trace_Strand_RunPendingOp(
//            &self->strand,
//            STRAND_DEBUG_GETNAME(&self->strand),
//            bitIndex,
//            STRAND_DEBUG_GETOPERATIONINDEX(&self->strand,bitIndex) );

        switch( (*_StrandEntryOperations_FT[ bitIndex-1 ])(self) )
        {
        case EORetry:
//            trace_Strand_RunPendingOp_CannotComplete(
//                &self->strand,
//                STRAND_DEBUG_GETNAME(&self->strand),
//                bitIndex,
//                STRAND_DEBUG_GETOPERATIONINDEX(&self->strand,bitIndex) );

            // We will retry when ack arrives
            self->pendingRetry = MI_TRUE;
            SList_PushAtomic( &retryList, &self->currentEntry->entry );
            break;
        case EODeleted:
            // Special case, we delete the entry here and we do not send back any completion to the entry
            trace_Strand_RunPendingOp_EntryDeleted(
                &self->strand,
                STRAND_DEBUG_GETNAME(&self->strand),
                bitIndex,
                STRAND_DEBUG_GETOPERATIONINDEX(&self->strand,bitIndex) );
            break;
        case EOContinue:
            // schedule completion to entry
            _Strand_ScheduleEntryOperation( &self->currentEntry->strand, MI_FALSE, &self->strand, self->currentEntry->operationScheduled );
            break;
        default:
            DEBUG_ASSERT( MI_FALSE );
        }
    }

    // push back into the list the ones we couldn't execute
    while( NULL != ( retryEntry = SList_PopAtomic( &retryList ) ) )
    {
        SList_PushAtomic( &self->pending, retryEntry );
    }

    self->currentEntry = NULL;
}

MI_Boolean _StrandMethod_Parent_Ack( _In_ Strand* self_)
{
    StrandMany* self = StrandMany_FromStrand(self_);

    STRAND_DEBUGSTATE( self_ );

    _StrandMethodImp_Ack( &self->strand, &self->strand.info );

    // Check if there is any entry waiting to be processed
    if( self->pendingRetry )
    {
        // Can't run _StrandMethod_RunPendingOperations directly,
        // because otherwise that can do a Post and then
        // the Ack to that post may come while we have not leave
        // the current Ack (and therefore schedule will assert
        // because it would try to schedule an Ack while other is
        // already running)
        _Strand_ScheduleEntryOperation(&self->strand, MI_TRUE, NULL, 0 );
    }
    // Note that there is no problem if some entry race to insert something in the list
    // after the check, as that entry will also schedule the EntryOperation itself

    return MI_FALSE;
}

MI_Boolean _StrandMethod_Parent_EntryOperation( _In_ Strand* self_)
{
    StrandMany* self = StrandMany_FromStrand(self_);

    _StrandMethod_Parent_RunPendingOperations( self );

    return MI_FALSE;
}

MI_Boolean _StrandMethod_Parent_Close( _In_ Strand* self_)
{
    StrandMany* self = StrandMany_FromStrand(self_);

    STRAND_DEBUGSTATE( self_ );

    _StrandMethodImp_Close( &self->strand, &self->strand.info );

    // now if there is no method close all entries
    if( NULL == self->strand.info.userFT->Close )
    {
        StrandMany_CloseAllEntries( self );
    }

    return MI_FALSE;
}

MI_Boolean _StrandMethod_Parent_CancelInternal( _In_ Strand* self_)
{
    DEBUG_ASSERT( MI_FALSE );    // this should never be scheduled on the parent but a EntryOperation should be used instead
    return MI_FALSE;
}

MI_Boolean _StrandMethod_Parent_PostControlInternal( _In_ Strand* self_)
{
    DEBUG_ASSERT( MI_FALSE );    // this should never be scheduled on the parent but a EntryOperation should be used instead
    return MI_FALSE;
}

MI_Boolean _StrandMethod_Parent_PostInternal( _In_ Strand* self_)
{
    DEBUG_ASSERT( MI_FALSE );    // this should never be scheduled on the parent but a EntryOperation should be used instead
    return MI_FALSE;
}

MI_Boolean _StrandMethod_Parent_AckInternal( _In_ Strand* self_)
{
    DEBUG_ASSERT( MI_FALSE );    // this should never be scheduled on the parent (EntryOperation cannot be used either)
    return MI_FALSE;
}

MI_Boolean _StrandMethod_Parent_CloseInternal( _In_ Strand* self_)
{
    DEBUG_ASSERT( MI_FALSE );    // this should never be scheduled on the parent but a EntryOperation should be used instead
    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
MI_Boolean _StrandMethod_Entry_CheckFinished( _In_ Strand* self_ )
{
    StrandEntry* self = StrandEntry_FromStrand(self_);

    return ( 0 == self->operationScheduled ) && ( 0 == self->operationsPending ) && _StrandMethodImp_CheckFinished( &self->strand.info ) && !self->strand.delayFinish;
}

MI_Boolean _StrandMethod_Entry_Cancel( _In_ Strand* self_)
{
    StrandEntry* self = StrandEntry_FromStrand(self_);

    STRAND_DEBUGSTATE( self_ );

    if( !self->strand.canceled )
    {
        self->strand.canceled = MI_TRUE;

        // if it is on the right, we dont need to pass cancel to the right
        // if it is on the left, canceling parent passes cancel to the right

        if( NULL != self->strand.info.userFT->Cancel )
        {
            (*self->strand.info.userFT->Cancel)(self_);
        }
        else
        {
            StrandEntry_CancelParent(self);
        }
    }

    return MI_FALSE;
}

MI_Boolean _StrandMethod_Entry_PostControl( _In_ Strand* self_)
{
    StrandEntry* self = StrandEntry_FromStrand(self_);

    _Strand_TracePostMsg(self_, self->strand.info.stored.controlMsg, "(Control Entry)");
    STRAND_DEBUGSTATE( self_ );
    DEBUG_ASSERT( NULL != self->strand.info.stored.controlMsg );

    if( NULL != self->strand.info.userFT->PostControl )
    {
        self->strand.info.userFT->PostControl( &self->strand, self->strand.info.stored.controlMsg );
    }
    else
    {
        StrandEntry_PostControlParent( self, self->strand.info.stored.controlMsg );
    }

    Message_Release( self->strand.info.stored.controlMsg );  // now we can remove the reference added on _StrandInteraction_*
    self->strand.info.stored.controlMsg = NULL;

    return MI_FALSE;
}

MI_Boolean _StrandMethod_Entry_Post( _In_ Strand* self_)
{
    StrandEntry* self = StrandEntry_FromStrand(self_);
    Message* storedmsg = self->strand.info.stored.msg;
    _Strand_TracePostMsg(self_, storedmsg, "(Entry)");
    STRAND_DEBUGSTATE( self_ );
    DEBUG_ASSERT( !self->strand.info.otherAckPending );
    DEBUG_ASSERT( NULL != storedmsg );
    self->strand.info.stored.msg = NULL;
    self->strand.info.otherAckPending = MI_TRUE;

    if( NULL != self->strand.info.userFT->Post )
    {
        self->strand.info.userFT->Post( &self->strand, storedmsg );
    }
    else
    {
        StrandEntry_PostParentPassthru( self, storedmsg );
    }

    Message_Release( storedmsg );  // now we can remove the reference added on _StrandInteraction_*

    return MI_FALSE;
}

MI_Boolean _StrandMethod_Entry_Ack( _In_ Strand* self_)
{
    STRAND_DEBUGSTATE( self_ );

    _StrandMethodImp_Ack( self_, &self_->info );

    return MI_FALSE;
}

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26001) // bogus "we know the strand points to the middle of the StrandEntry struct" and Linux sal parser doesnt recognize something like _Readable_elements_(_Inexpressible_(StrandEntry))
#endif /* _PREFAST_ */

MI_Boolean _StrandMethod_Entry_EntryOperation( _In_ Strand* self_)
{
    StrandEntry* self = StrandEntry_FromStrand(self_);
    EntryOperationMaskType operationLastScheduled = self->operationScheduled;

    if( 0 != self->operationsPending )
    {
        // schedule the next one
        unsigned long bitIndex;
        EntryOperationMaskType entryOperationBit;

        bitIndex = GetFirstSetLSB( self->operationsPending );
        DEBUG_ASSERT( bitIndex );
        entryOperationBit = (EntryOperationMaskType)_GetMethodBit( bitIndex );

        self->operationScheduled = entryOperationBit;
        self->operationsPending &= (~entryOperationBit);

        SList_PushAtomic( &self->parent->pending, &self->entry );
        _Strand_ScheduleEntryOperation( &self->parent->strand, MI_TRUE, &self->strand, entryOperationBit );
    }
    else
    {
        self->operationScheduled = 0;
    }

    if( BitEntryPost == operationLastScheduled )
    {
        if( NULL != self->parent->userInternalFT && NULL != self->parent->userInternalFT->ParentAck )
        {
            self->parent->userInternalFT->ParentAck( self );
        }
        else if( self->ackPassthru )
        {
            // Now we can send the Ack to the interaction
            Strand_Ack(self_);
        }
        self->ackPassthru = MI_FALSE;
    }
    else if( BitEntryAdd == operationLastScheduled && NULL != self->parent->userInternalFT && NULL != self->parent->userInternalFT->AddedToParent )
    {
        Message* storedmsg = self->strand.info.stored.msg;
        self->strand.info.stored.msg = NULL;
        self->parent->userInternalFT->AddedToParent( self, storedmsg );
        if( NULL != storedmsg )
        {
            _Strand_TracePostMsg(self_, storedmsg, "(EntryAddedToParent)");
            Message_Release( storedmsg );  // now we can finally remove the reference added on ScheduleAdd
        }
    }

    return MI_FALSE;
}

MI_Boolean _StrandMethod_Entry_Close( _In_ Strand* self_)
{
    STRAND_DEBUGSTATE( self_ );

    _StrandMethodImp_Close( self_, &self_->info );

    return MI_FALSE;
}

MI_Boolean _StrandMethod_Entry_CancelInternal( _In_ Strand* self_)
{
    StrandEntry* self = StrandEntry_FromStrand(self_);

    trace_StrandMethod_Entry_CancelInternal( self_, STRAND_DEBUG_GETNAME(self_) );

    if( !self_->canceled )
    {
        if( self_->info.opened )
        {
            if( !self_->info.thisClosedOther )
            {
                // since we are in the middle, forward to the other side
                self_->info.interaction.other->ft->Cancel( self_->info.interaction.other );
            }
            _StrandMethodImp_Cancel( self_, &self_->info );
        }
        else
        {
            // If it was not even opened we dont even call the cancel method
            self_->canceled = MI_TRUE;
        }
    }
    else if( self->parent->strand.strandType == STRAND_TYPE_PARENTRIGHT && self_->info.opened && !self_->info.thisClosedOther )
    {
        // since we are in the left-middle this can be cancelation coming back from right,
        // so pass back to the left
        self_->info.interaction.other->ft->Cancel( self_->info.interaction.other );
    }
    return MI_FALSE;
}

MI_Boolean _StrandMethod_Entry_PostControlInternal( _In_ Strand* self_)
{
    StrandEntry* self = StrandEntry_FromStrand(self_);

    DEBUG_ASSERT( NULL != self->fromParent.controlMsg );

    trace_StrandMethod_Entry_PostControlInternal(self_, STRAND_DEBUG_GETNAME(self_), self->fromParent.controlMsg);

    if( NULL != self->parent->userInternalFT && NULL != self->parent->userInternalFT->ParentPostControl )
    {
        self->parent->userInternalFT->ParentPostControl( self, self->fromParent.controlMsg );
    }
    else
    {
        Strand_PostControl( self_, self->fromParent.controlMsg );
    }

    Message_Release( self->fromParent.controlMsg ); // ref added on StrandMany_PostControlEntry
    self->fromParent.controlMsg = NULL;

    return MI_FALSE;
}

MI_Boolean _StrandMethod_Entry_PostInternal( _In_ Strand* self_)
{
    StrandEntry* self = StrandEntry_FromStrand( self_);

    DEBUG_ASSERT( NULL != self->fromParent.msg );
    DEBUG_ASSERT( !self->strand.info.thisAckPending );  // user is responsible to manage flow control if there are secondary messages

    trace_StrandMethod_Entry_PostInternal(self_, STRAND_DEBUG_GETNAME(self_), self->fromParent.msg);

    if( NULL != self->parent->userInternalFT && NULL != self->parent->userInternalFT->ParentPost )
    {
        self->parent->userInternalFT->ParentPost( self, self->fromParent.msg );
    }
    else
    {
        Strand_Post( self_, self->fromParent.msg );
    }

    Message_Release( self->fromParent.msg ); // ref added on StrandMany_PostEntry
    self->fromParent.msg = NULL;

    return MI_FALSE;
}

#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */

MI_Boolean _StrandMethod_Entry_AckInternal( _In_ Strand* self_)
{
    trace_StrandMethod_Entry_AckInternal( self_, STRAND_DEBUG_GETNAME(self_) );

    Strand_Ack( self_ );

    return MI_FALSE;
}

MI_Boolean _StrandMethod_Entry_CloseInternal( _In_ Strand* self_)
{
    StrandEntry* self = StrandEntry_FromStrand(self_);

    trace_StrandMethod_Entry_CloseInternal(
        self_,
        STRAND_DEBUG_GETNAME(self_),
        self_->info.opened,
        self_->info.thisClosedOther );

    if( NULL != self->parent->userInternalFT && NULL != self->parent->userInternalFT->ParentClose )
    {
        self->parent->userInternalFT->ParentClose( self );
    }
    else if( self_->info.opened && !self_->info.thisClosedOther )
    {
        Strand_Close( self_ );
    }

    return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
static InteractionFT _StrandInteraction_FT = {
    _StrandInteraction_Post,
    _StrandInteraction_PostControl,
    _StrandInteraction_Ack,
    _StrandInteraction_Cancel,
    _StrandInteraction_Close };

//------------------------------------------------------------------------------------------------------------
static InteractionFT _StrandInteraction_Left_FT = {
    _StrandInteraction_Left_Post,
    _StrandInteraction_Left_PostControl,
    _StrandInteraction_Left_Ack,
    _StrandInteraction_Left_Cancel,
    _StrandInteraction_Left_Close };

//------------------------------------------------------------------------------------------------------------
static InteractionFT _StrandInteraction_Right_FT = {
    _StrandInteraction_Right_Post,
    _StrandInteraction_Right_PostControl,
    _StrandInteraction_Right_Ack,
    _StrandInteraction_Right_Cancel,
    _StrandInteraction_Right_Close };

//------------------------------------------------------------------------------------------------------------
static InteractionFT _StrandInteraction_Many_FT = {
    _StrandInteraction_Many_Post,
    _StrandInteraction_Many_PostControl,
    _StrandInteraction_Many_Ack,
    _StrandInteraction_Many_Cancel,
    _StrandInteraction_Many_Close };

//------------------------------------------------------------------------------------------------------------
static StrandMethod _StrandMethods_FT[] = {
    _StrandMethod_CheckFinished,
    _StrandMethod_CompleteOpenAsync,
    _StrandMethod_Timer,
    _StrandMethod_Cancel,
    _StrandMethod_CancelSelf,
    _StrandMethod_PostControl,
    _StrandMethod_Post,
    _StrandMethod_PostOther,
    _StrandMethod_Ack,
    _StrandMethod_AckOther,
    _StrandMethod_Close,
    _StrandMethod_CloseOther,
    _StrandMethod_Aux0,
    _StrandMethod_Aux1,
    _StrandMethod_Aux2,
    _StrandMethod_Aux3,
    _StrandMethod_Aux4,
    NULL, // just give some overflow NULL methods for safety
    NULL,
    NULL };

//------------------------------------------------------------------------------------------------------------
static StrandMethod _StrandMethods_Both_FT[] = {
    _StrandMethod_Both_CheckFinished,
    _StrandMethod_Both_CompleteOpenAsync,
    _StrandMethod_Timer,
    _StrandMethod_Left_Cancel,
    _StrandMethod_Right_Cancel,
    _StrandMethod_Both_CancelSelf,
    _StrandMethod_Left_PostControl,
    _StrandMethod_Right_PostControl,
    _StrandMethod_Left_Post,
    _StrandMethod_Right_Post,
    _StrandMethod_PostOther,
    _StrandMethod_Right_PostOther,
    _StrandMethod_Left_Ack,
    _StrandMethod_Right_Ack,
    _StrandMethod_AckOther,
    _StrandMethod_Right_AckOther,
    _StrandMethod_Left_Close,
    _StrandMethod_Right_Close,
    _StrandMethod_CloseOther,
    _StrandMethod_Right_CloseOther,
    _StrandMethod_Aux0,
    _StrandMethod_Aux1,
    _StrandMethod_Aux2,
    _StrandMethod_Aux3,
    _StrandMethod_Aux4,
    _StrandMethod_Right_Aux0,
    _StrandMethod_Right_Aux1,
    _StrandMethod_Right_Aux2,
    _StrandMethod_Right_Aux3,
    _StrandMethod_Right_Aux4,
    NULL, // just give some overflow NULL methods for safety
    NULL,
    NULL };

//------------------------------------------------------------------------------------------------------------
static StrandMethod _StrandMethods_Parent_FT[] = {
    _StrandMethod_Parent_CheckFinished,
    _StrandMethod_CompleteOpenAsync,
    _StrandMethod_Timer,
    _StrandMethod_Parent_Cancel,
    _StrandMethod_CancelSelf,
    _StrandMethod_Parent_CancelInternal,
    _StrandMethod_Parent_PostControl,
    _StrandMethod_Parent_PostControlInternal,
    _StrandMethod_Parent_Post,
    _StrandMethod_PostOther,
    _StrandMethod_Parent_PostInternal,
    _StrandMethod_Parent_Ack,
    _StrandMethod_AckOther,
    _StrandMethod_Parent_AckInternal,
    _StrandMethod_Parent_EntryOperation,
    _StrandMethod_Parent_Close,
    _StrandMethod_CloseOther,
    _StrandMethod_Parent_CloseInternal,
    _StrandMethod_Aux0,
    _StrandMethod_Aux1,
    _StrandMethod_Aux2,
    _StrandMethod_Aux3,
    _StrandMethod_Aux4,
    NULL, // just give some overflow NULL methods for safety
    NULL,
    NULL };

//------------------------------------------------------------------------------------------------------------
static StrandMethod _StrandMethods_Entry_FT[] = {
    _StrandMethod_Entry_CheckFinished,
    _StrandMethod_CompleteOpenAsync,
    _StrandMethod_Timer,
    _StrandMethod_Entry_Cancel,
    _StrandMethod_CancelSelf,
    _StrandMethod_Entry_CancelInternal,
    _StrandMethod_Entry_PostControl,
    _StrandMethod_Entry_PostControlInternal,
    _StrandMethod_Entry_Post,
    _StrandMethod_PostOther,
    _StrandMethod_Entry_PostInternal,
    _StrandMethod_Entry_Ack,
    _StrandMethod_AckOther,
    _StrandMethod_Entry_AckInternal,
    _StrandMethod_Entry_EntryOperation,
    _StrandMethod_Entry_Close,
    _StrandMethod_CloseOther,
    _StrandMethod_Entry_CloseInternal,
    _StrandMethod_Aux0,
    _StrandMethod_Aux1,
    _StrandMethod_Aux2,
    _StrandMethod_Aux3,
    _StrandMethod_Aux4,
    NULL, // just give some overflow NULL methods for safety
    NULL,
    NULL };

//------------------------------------------------------------------------------------------------------------
MI_INLINE
void _Strand_EnterStrand( _In_ Strand* self )
{
    trace_Strand_EnterStrand( self, STRAND_DEBUG_GETNAME(self) );

    DEBUG_ASSERT( NULL == self->strandStealedFlag );
    DEBUG_ASSERT( 0 == self->stateScheduled );
    self->stateScheduled = BitExecuting;

    _Strand_SetCurrentStrandThread( self );
}

// Only used internally
MI_INLINE
void _Strand_ExitStrand( _In_ Strand* self )
{
    trace_Strand_ExitStrand( self, STRAND_DEBUG_GETNAME(self) );

    DEBUG_ASSERT( NULL == self->strandStealedFlag );
    DEBUG_ASSERT( BitExecuting == self->stateScheduled );
    self->stateScheduled = 0;

    _Strand_ExitCurrentStrandThread( self );
}

MI_INLINE
Strand* _Strand_Create(
                    size_t          structSize,
    _Inout_         StrandFlags*    flags )
{
    Strand* self;

    DEBUG_ASSERT( structSize >= sizeof(Strand) );

    /* Allocate heap space for Strand */
    if( 0 != (*flags & STRAND_FLAG_NOZEROALLOCATED) )
    {
        *flags &= (~STRAND_FLAG_NOZEROALLOCATED);    // To indicate Strand*_Init that it does need to zero the strand fields
        self = PAL_Malloc( structSize );
    }
    else
    {
        *flags |= STRAND_FLAG_NOZEROALLOCATED;       // To indicate Strand*_Init that it doesnt need to zero the strand fields
        self = PAL_Calloc( 1, structSize );
    }

    return self;
}

MI_INLINE
void _Strand_CreateEnterStrand(
#if defined(STRAND_ENABLE_DEBUG)
    _In_        StrandDebugInfo debug,
#endif
    _In_        Strand*         self)
{
    STRAND_SETDEBUG( self, debug );

    _Strand_EnterStrand(self);
}

MI_INLINE
void _Strand_CreateExitStrand(
    _In_        Strand*         self)
{
    if( 0 == (self->flags & STRAND_FLAG_ENTERSTRAND) )
    {
        _Strand_ExitStrand(self);
    }
}

//------------------------------------------------------------------------------------------------------------
Strand* Strand_New(
#if defined(STRAND_ENABLE_DEBUG)
    _In_        StrandDebugInfo         debug,
#endif
    _In_        StrandFT *              userFT,
                size_t                  structSize,
                StrandFlags             flags,
    _In_opt_    InteractionOpenParams*  interactionOpenParams )
{
    Strand* self;

    if( 0 == structSize )
        structSize = sizeof( Strand );

    self = _Strand_Create( structSize, &flags );

    if( self )
    {
        Strand_Init( STRAND_PASSDEBUG(debug) self, userFT, flags, interactionOpenParams );
    }

    return self;
}

void Strand_Init(
#if defined(STRAND_ENABLE_DEBUG)
    _In_        StrandDebugInfo         debug,
#endif
    _Out_       Strand*                 self,
    _In_        StrandFT*               userFT,
                StrandFlags             flags,
    _In_opt_    InteractionOpenParams*  interactionOpenParams )
{
    DEBUG_ASSERT(self);
    DEBUG_ASSERT(userFT);

    if( 0 == (flags & STRAND_FLAG_NOZEROALLOCATED) )
    {
        // Clear all fields in case previously they have not been cleared
        memset(self, 0, sizeof(Strand) );
    }

    self->strandMethods = _StrandMethods_FT;
    self->flags = flags;
    self->info.interaction.ft = &_StrandInteraction_FT;
    self->info.userFT = userFT;

    _Strand_CreateEnterStrand( STRAND_PASSDEBUG(debug) self );

    if( NULL != interactionOpenParams || 0 != (flags & STRAND_FLAG_DELAYACCEPTOPEN) )
    {
        // we are being opened on the right most
        self->strandType = STRAND_TYPE_RIGHTMOST;
        if( 0 == (flags & STRAND_FLAG_DELAYACCEPTOPEN) )
        {
            Strand_AcceptOpen( self, interactionOpenParams );
        }
    }
    else
    {
        if( ( flags & STRAND_FLAG_NOINTERACTION ) != 0 )
        {
            self->strandType = STRAND_TYPE_NOINTERACTION;
            self->info.thisClosedOther = self->info.otherClosedThis = MI_TRUE;
        }
        else
        {
            self->strandType = STRAND_TYPE_LEFTMOST;
        }
    }

    _Strand_CreateExitStrand( self );
}

//------------------------------------------------------------------------------------------------------------
StrandBoth* StrandBoth_New(
#if defined(STRAND_ENABLE_DEBUG)
    _In_        StrandDebugInfo         debug,
#endif
    _In_        StrandFT*               userLeftFT,
    _In_        StrandFT*               userRightFT,
                size_t                  structSize,
                StrandFlags             flags,
    _In_opt_    InteractionOpenParams*  interactionOpenParams )
{
    StrandBoth* self;

    if( 0 == structSize )
        structSize = sizeof( StrandBoth );

    DEBUG_ASSERT( structSize >= sizeof(StrandBoth) );

    self = (StrandBoth*) _Strand_Create( structSize, &flags );

    if( NULL != self )
    {
        StrandBoth_Init( STRAND_PASSDEBUG(debug) self, userLeftFT, userRightFT, flags, interactionOpenParams );
    }

    return self;
}

//------------------------------------------------------------------------------------------------------------
void StrandBoth_Init(
#if defined(STRAND_ENABLE_DEBUG)
    _In_        StrandDebugInfo         debug,
#endif
    _Out_       StrandBoth*             self,
    _In_        StrandFT*               userLeftFT,
    _In_        StrandFT*               userRightFT,
                StrandFlags             flags,
    _In_opt_    InteractionOpenParams*  interactionOpenParams )
{
    DEBUG_ASSERT(userLeftFT);
    DEBUG_ASSERT(userRightFT);
    // close should be the same for both
    DEBUG_ASSERT( userLeftFT->Finish == userRightFT->Finish || NULL == userRightFT->Finish );
    DEBUG_ASSERT( NULL != interactionOpenParams || 0 != (flags & STRAND_FLAG_DELAYACCEPTOPEN) );

    if( 0 == (flags & STRAND_FLAG_NOZEROALLOCATED) )
    {
        // Clear all fields in case previously they have not been cleared
        memset(self, 0, sizeof(StrandBoth) );
    }

    self->base.strandType = STRAND_TYPE_MIDDLE;
    self->base.strandMethods = _StrandMethods_Both_FT;
    self->base.flags = flags;

    self->base.info.interaction.ft = &_StrandInteraction_Left_FT;
    self->base.info.userFT = userLeftFT;

    self->infoRight.interaction.ft = &_StrandInteraction_Right_FT;
    self->infoRight.userFT = userRightFT;

    _Strand_CreateEnterStrand( STRAND_PASSDEBUG(debug) &self->base );

    if( 0 == (flags & STRAND_FLAG_DELAYACCEPTOPEN) )
    {
        DEBUG_ASSERT( NULL != interactionOpenParams );
        Strand_AcceptOpen( &self->base, interactionOpenParams );
    }

    _Strand_CreateExitStrand( &self->base );
}

//------------------------------------------------------------------------------------------------------------
StrandMany* StrandMany_New(
#if defined(STRAND_ENABLE_DEBUG)
    _In_        StrandDebugInfo         debug,
#endif
    _In_        StrandFT*               userParentFT,
    _In_opt_    StrandManyInternalFT*   userInternalFT,
                size_t                  structSize,
                StrandFlags             flags,
    _In_opt_    InteractionOpenParams*  interactionOpenParams,  // if STRAND_FLAG_NOINTERACTION is not used and interactionOpenParams is NULL it is assumed it will open an interaction on the right
                size_t                  numLists,               // numlist for the underlying Hash table, use 1 if it is not going to be searched
    _In_opt_    HashMapHashProc         hash,                   // hashing func for the underlying Hash table, if NULL will use the StrandEntry pointer
    _In_opt_    HashMapEqualProc        equal,                  // equal func for the underlying Hash table, can be NULL if it is not going to be searched or entry ptr comparison is ok
    _In_opt_    FindEntryProc           findEntryProc )         // finds a entry based on a message, can be NULL if msg should not be automatically redirected to entries
{
    StrandMany* self;

    DEBUG_ASSERT(userParentFT);

    if( 0 == structSize )
        structSize = sizeof( StrandMany );

    DEBUG_ASSERT( structSize >= sizeof(StrandMany) );

    self = (StrandMany*) SList_Alloc( structSize );

    if( NULL != self )
    {
        if( 0 != (flags & STRAND_FLAG_NOZEROALLOCATED) )
        {
            // Clear only strand fields
            memset(self, 0, sizeof(StrandMany) );
        }
        else
        {
            // Clear all allocated fields
            memset(self, 0, structSize );
        }

        if( NULL == hash )
            hash = _StrandMany_HashMapHashProc;
        if( NULL == equal )
            equal = _StrandMany_HashMapEqualProc;

        if( HashMap_Init( &self->many, numLists, hash, equal, _StrandMany_HashMapReleaseProc ) )
        {
            SList_Free( self );
            return NULL;
        }

        SList_Init( &self->pending );
        self->findEntryProc = findEntryProc;

        self->userInternalFT = userInternalFT;
        self->strand.flags = flags;
        self->strand.strandMethods = _StrandMethods_Parent_FT;
        self->strand.info.interaction.ft = &_StrandInteraction_Many_FT;
        self->strand.info.userFT = userParentFT;

        _Strand_CreateEnterStrand( STRAND_PASSDEBUG(debug) &self->strand );

        if( 0 == (flags&STRAND_FLAG_NOINTERACTION) )
        {
            if( NULL != interactionOpenParams || 0 != (flags & STRAND_FLAG_DELAYACCEPTOPEN) )
            {
                // Parent is being opened (it is on the left)
                self->strand.strandType = STRAND_TYPE_PARENTLEFT;
                if( 0 == (flags & STRAND_FLAG_DELAYACCEPTOPEN) )
                {
                    Strand_AcceptOpen( &self->strand, interactionOpenParams );
                }
            }
            else
            {
                self->strand.strandType = STRAND_TYPE_PARENTRIGHT;
            }
        }
        else
        {
            DEBUG_ASSERT( NULL == interactionOpenParams );
            self->strand.strandType = STRAND_TYPE_PARENTNOINTERACTION;
            self->strand.info.thisClosedOther = self->strand.info.otherClosedThis = MI_TRUE;
        }

        _Strand_CreateExitStrand( &self->strand );
    }

    return self;
}

StrandEntry* StrandEntry_New(
#if defined(STRAND_ENABLE_DEBUG)
    _In_        StrandDebugInfo         debug,
#endif
    _In_        StrandMany*             parent,
    _In_        StrandFT*               userEntryFT,
                size_t                  structSize,
                StrandFlags             flags,
    _In_opt_    InteractionOpenParams*  interactionOpenParams )
{
    StrandEntry* self;

    DEBUG_ASSERT( NULL != parent );
    DEBUG_ASSERT( NULL != userEntryFT );

    if( 0 == structSize )
        structSize = sizeof( StrandEntry );

    DEBUG_ASSERT( structSize >= sizeof(StrandEntry) );

    self = (StrandEntry*) SList_Alloc( structSize );

    if( NULL != self )
    {
        if( 0 != (flags & STRAND_FLAG_NOZEROALLOCATED) )
        {
            // Clear only strand fields
            memset(self, 0, sizeof(StrandEntry) );
        }
        else
        {
            // Clear all allocated fields
            memset(self, 0, structSize );
        }

        self->parent = parent;

        self->strand.strandMethods = _StrandMethods_Entry_FT;
        self->strand.flags = flags;
        self->strand.info.interaction.ft = &_StrandInteraction_Many_FT;
        self->strand.info.userFT = userEntryFT;
        self->strand.strandType = STRAND_TYPE_ENTRY;

        _Strand_CreateEnterStrand( STRAND_PASSDEBUG(debug) &self->strand );

        if( NULL != interactionOpenParams || 0 != (flags & STRAND_FLAG_DELAYACCEPTOPEN) )
        {
            // Entry is being opened (it is on the left)
            DEBUG_ASSERT( ( flags & STRAND_FLAG_NOINTERACTION ) == 0 );
            DEBUG_ASSERT( parent->strand.strandType == STRAND_TYPE_PARENTRIGHT || parent->strand.strandType == STRAND_TYPE_PARENTNOINTERACTION );
            if( 0 == (flags & STRAND_FLAG_DELAYACCEPTOPEN) )
            {
                Strand_AcceptOpen( &self->strand, interactionOpenParams );
            }
        }
        else
        {
            if( ( flags & STRAND_FLAG_NOINTERACTION ) != 0 )
            {
                self->strand.info.thisClosedOther = self->strand.info.otherClosedThis = MI_TRUE;
            }
            else
            {
                DEBUG_ASSERT( parent->strand.strandType == STRAND_TYPE_PARENTLEFT || parent->strand.strandType == STRAND_TYPE_PARENTNOINTERACTION );
            }
        }

        _Strand_CreateExitStrand( &self->strand );
    }

    return self;
}

MI_Result StrandMany_AddEntry(
    _In_        StrandEntry*            self )
{
    STRAND_ASSERTONSTRAND( &self->parent->strand );
    DEBUG_ASSERT( self->strand.info.stored.msg == NULL );
    if( HashMap_Insert( &self->parent->many, &self->bucket ) )
    {
        SList_Free( self );
        return MI_RESULT_FAILED;
    }

    ++(self->parent->numEntries);

    if( NULL != self->parent->userInternalFT && NULL != self->parent->userInternalFT->AddedToParent )
    {
        STRAND_ASSERTONSTRAND( &self->strand );
        self->parent->userInternalFT->AddedToParent( self, NULL );
    }

    return MI_RESULT_OK;
}

void StrandEntry_ScheduleAdd(
    _In_        StrandEntry*            self,
    _In_opt_    Message *               msg )           // optional initial message
{
    DEBUG_ASSERT( NULL != self );

    if( NULL != msg )
    {
        Message_AddRef(msg);
        self->strand.info.stored.msg = msg;
    }
    _StrandEntry_ScheduleParent(self,BitEntryAdd);
}

void Strand_Delete( _In_ Strand* self )
{
    if( STRAND_ISTYPE_ENTRY(self) )
    {
        StrandEntry_Delete( StrandEntry_FromStrand(self) );
    }
    else if( STRAND_ISTYPE_PARENT(self) )
    {
        StrandMany_Delete( StrandMany_FromStrand(self) );
    }
    else
    {
        STRAND_LOGWITHNAME( self, "Deleting Strand" );
        PAL_Free( self );
    }
}

void StrandMany_Delete( _In_ StrandMany* self )
{
    SListEntry* entry;

    STRAND_LOGWITHNAME( &self->strand, "Deleting StrandMany" );

    DEBUG_ASSERT( 0 == self->numEntries );
    DEBUG_ASSERT( NULL == self->currentEntry );

    HashMap_Destroy( &self->many );

    entry = SList_FlushAtomic( &self->pending );

    if (entry != NULL)
    {
        DEBUG_ASSERT( NULL == entry );
    }

    SList_Free( self );
}

void StrandMany_DeleteEntry( _In_ StrandEntry* entry )
{
    StrandMany* self = entry->parent;

    STRAND_ASSERTONSTRAND( &self->strand );

    trace_Strand_DeletedEntry( &self->strand, STRAND_DEBUG_GETNAME(&self->strand), &entry->strand, STRAND_DEBUG_GETNAME(&entry->strand) );

    DEBUG_ASSERT( self->numEntries >= 1 );
    --(self->numEntries);

    if( HashMap_Remove( &self->many, &entry->bucket ) )
    {
        trace_Strand_CannotDelete( &self->strand, STRAND_DEBUG_GETNAME(&self->strand), &entry->strand, STRAND_DEBUG_GETNAME(&entry->strand) );
        DEBUG_ASSERT( MI_FALSE );   // should not happen
    }

    SList_Free( entry );
}

void StrandEntry_Delete( _In_ StrandEntry* self )
{
    STRAND_LOGWITHNAME( &self->strand, "Scheduling deletion of StrandEntry" );

    DEBUG_ASSERT( 0 == self->operationScheduled );

    _StrandEntry_ScheduleParent( self, BitEntryDeleted );
}

//------------------------------------------------------------------------------------------------------------
void _Strand_CancelPropagate(
    _In_ Strand *   self)
{
    STRAND_ASSERTONSTRAND( self );

    switch( self->strandType )
    {
    case STRAND_TYPE_MIDDLE:
        {
            StrandBoth * selfBoth = (StrandBoth*)self;

            if( selfBoth->infoRight.opened && !selfBoth->infoRight.thisClosedOther )
            {
                STRAND_LOGWITHNAME( self, "Canceling to the right" );

                // first go to the right
                selfBoth->infoRight.interaction.other->ft->Cancel( selfBoth->infoRight.interaction.other );
            }
        }
        break;
    case STRAND_TYPE_LEFTMOST:
    case STRAND_TYPE_RIGHTMOST:
    case STRAND_TYPE_PARENTRIGHT:
        {
            if( self->info.opened && !self->info.thisClosedOther )
            {
                STRAND_LOGWITHNAME( self, "Canceling" );

                // just go to the other side (start going right or initiate return to the left)
                self->info.interaction.other->ft->Cancel( self->info.interaction.other );
            }
        }
        break;
    case STRAND_TYPE_PARENTLEFT:
        {
            StrandMany* stranMany = StrandMany_FromStrand(self);

            STRAND_LOGWITHNAME( self, "Canceling all entries to the left" );

            StrandMany_CancelAllEntries( stranMany );
        }
    case STRAND_TYPE_ENTRY:
        {
            StrandEntry* entry = StrandEntry_FromStrand(self);

            if( entry->parent->strand.strandType == STRAND_TYPE_PARENTRIGHT )
            {
                if( NULL == self->info.userFT->Cancel )
                {
                    STRAND_LOGWITHNAME( self, "Canceling parent from entry" );

                    StrandEntry_CancelParent( entry );
                }
            }
            else
            {
                if( self->info.opened && !self->info.thisClosedOther )
                {
                    STRAND_LOGWITHNAME( self, "Canceling interaction from entry" );

                    // start going right
                    self->info.interaction.other->ft->Cancel( self->info.interaction.other );
                }
            }
        }
        break;
    case STRAND_TYPE_PARENTNOINTERACTION:
    default:
        DEBUG_ASSERT(MI_FALSE);
    }
    STRAND_LOGWITHNAME( self, "Returning from Canceling other (would cancel method if existent) " );
}

void Strand_Cancel(
    _In_ Strand *   self)
{
    STRAND_ASSERTONSTRAND( self );

    if( !self->canceled )
    {
        _Strand_CancelPropagate( self );

        _StrandMethodImp_Cancel(self, &self->info );
    }
}

//------------------------------------------------------------------------------------------------------------
ptrdiff_t _EnableMethodBit( _In_ Strand* self, ptrdiff_t methodBit )
{
    ptrdiff_t initialState, newState = ReadWithFence( &self->stateScheduled );

    do
    {
        initialState = newState;

        // check if bit already set
        DEBUG_ASSERT( (initialState & methodBit) == 0 );
    }
    while( (newState = Atomic_CompareAndSwap( &self->stateScheduled, initialState, initialState|methodBit )) != initialState );

    return initialState|methodBit;
}

//------------------------------------------------------------------------------------------------------------
MI_INLINE ptrdiff_t _DisableMethodBit( _In_ Strand* self, ptrdiff_t methodBit )
{
    return Atomic_And( &self->stateScheduled, ~methodBit ) & (~methodBit);
}

//------------------------------------------------------------------------------------------------------------
void _Strand_ExecuteLoop( _In_ Strand* self, ptrdiff_t state )
{
    unsigned long bitIndex;
    MI_Boolean strandStealedFlag;
    STRAND_DEBUG_GETSTATE_USED;
    STRAND_DEBUG_GETINFOSTATE_USED;

    _Strand_SetCurrentStrandThread( self );

    for(;;)   // check new state loop
    {
        DEBUG_ASSERT( ( state & BitExecuting ) != 0 );

        // we dont want to check on BitExecuting
        bitIndex = GetFirstSetLSB( state & (~BitExecuting) );
        if( bitIndex )
        {
            ptrdiff_t methodBit = _GetMethodBit( bitIndex );

            strandStealedFlag = MI_FALSE;
            self->strandStealedFlag = &strandStealedFlag;
            self->currentMethodBit = methodBit;

            DEBUG_ASSERT( bitIndex > FirstRealMethodBit );

            STRAND_DEBUG_GETINFOSTATE_STORE(self);
            trace_Strand_ExecLoop(
                self,
                STRAND_DEBUG_GETNAME(self),
                state,
                STRAND_DEBUG_GETSTATE(self, state ),
                bitIndex,
                STRAND_DEBUG_GETMETHODINDEX(self,bitIndex),
                STRAND_DEBUG_GETINFOSTATE_STORED );

            (*self->strandMethods[ bitIndex-FirstRealMethodBit ])(self);

            if( strandStealedFlag )
            {
                // if someone stealed the strand synchronously (Strand_Leave)
                // while the function was being executed then just bail out
                trace_Strand_ExecLoop_Leave(
                    self,
                    state,
                    bitIndex,
                    methodBit);
                return;
            }
            else
            {
                state = _DisableMethodBit( self, methodBit );
                if( BitTimer == methodBit && NULL != self->timer )
                {
                    // timer was restarted inside the timer method, start it now
                    Timer_Start( self->timer, self );
                }
                else if( STRAND_ISTYPE_PARENT( self ) && BitEntryOperation == methodBit  )
                {
                    _StrandMethod_Parent_RunPendingOperations( StrandMany_FromStrand(self) );
                }
            }
        }
        else
        {
            ptrdiff_t newState;

            // Nothing else scheduled, we are going to stop executing (if nothing else has changed)

            MI_Boolean aboutToFinish = _Strand_ShouldFinish(self);

            DEBUG_ASSERT( BitExecuting == state );

            /* trace_Strand_ExecLoop( self, state, aboutToFinish ); */

            _Strand_ExitCurrentStrandThread( self );

            // Get these two before the Atomic_CompareAndSwap (strand may be deleted after that)
            STRAND_DEBUG_GETNAME_STORE(self);
            STRAND_DEBUG_GETINFOSTATE_STORE(self);

            newState = Atomic_CompareAndSwap( &self->stateScheduled, state, 0 );
            // If the state has not changed (no new method was scheduled) we can stop now
            if( newState == state )
            {
                trace_Strand_ExecLoop_Exits(
                    self,
                    STRAND_DEBUG_GETNAME_STORED,
                    state,
                    aboutToFinish,
                    STRAND_DEBUG_GETINFOSTATE_STORED );
                if( aboutToFinish )
                {
                    _Strand_Finish( self );
                }
                return;
            }
            else
            {
                trace_Strand_ExecLoop_DoesntExit(
                    self,
                    STRAND_DEBUG_GETNAME(self),
                    state,
                    newState,
                    STRAND_DEBUG_GETSTATE(self, newState),
                    aboutToFinish,
                    STRAND_DEBUG_GETINFOSTATE_STORED );
                state = newState;

                // revert this
                _Strand_SetCurrentStrandThread( self );
            }
        }
    }
}

//------------------------------------------------------------------------------------------------------------
// Schedules a method in the strand
//------------------------------------------------------------------------------------------------------------
#if defined(STRAND_ENABLE_DEBUG)
void _Strand_ScheduleImp(
    _In_        Strand*                 self,
                unsigned int            methodBit,
                MI_Boolean              allowMultiSchedule,
    _In_opt_    Strand*                 fromStrand,
                EntryOperationMaskType  entryOperationBit )
#else
void _Strand_ScheduleImp(
    _In_        Strand*                 self,
                unsigned int            methodBit )
#endif
{
    ptrdiff_t initialState, newState = ReadWithFence( &self->stateScheduled );
    STRAND_DEBUG_GETSTATE_USED;

    DEBUG_ASSERT( methodBit > 0 );

#if defined(STRAND_ENABLE_DEBUG)
    if( allowMultiSchedule && BitTimer != methodBit )
    {
        trace_Strand_ScheduleParent(
            self,
            STRAND_DEBUG_GETNAME(self),
            newState,
            STRAND_DEBUG_GETSTATE(self, newState),
            entryOperationBit,
            0 == entryOperationBit ? "<re-scheduled>" : STRAND_DEBUG_GETOPERATION(self, entryOperationBit ),
            fromStrand,
            NULL == fromStrand ? "<self>" : STRAND_DEBUG_GETNAME(fromStrand),
            methodBit,
            STRAND_DEBUG_GETMETHOD(self,methodBit) );
    }
    else if( NULL != fromStrand )
    {
        trace_Strand_ScheduleEntry(
            self,
            STRAND_DEBUG_GETNAME(self),
            newState,
            STRAND_DEBUG_GETSTATE(self, newState),
            entryOperationBit,
            STRAND_DEBUG_GETOPERATION(fromStrand, entryOperationBit ),
            fromStrand,
            STRAND_DEBUG_GETNAME(fromStrand),
            methodBit,
            STRAND_DEBUG_GETMETHOD(self,methodBit) );
    }
    else
    {
        trace_Strand_Schedule(
            self,
            STRAND_DEBUG_GETNAME(self),
            newState,
            STRAND_DEBUG_GETSTATE(self, newState),
            methodBit,
            STRAND_DEBUG_GETMETHOD(self,methodBit) );
    }
#else
    trace_Strand_Schedule2(
        self,
        newState,
        methodBit );
#endif

    do
    {
        initialState = newState;

#if defined(STRAND_ENABLE_DEBUG)
        // check if bit already set
        // otherwise Caller is violating the contract!
        DEBUG_ASSERT( allowMultiSchedule || (initialState & methodBit) == 0 );
#endif
    }
    while( (newState = Atomic_CompareAndSwap( &self->stateScheduled, initialState, initialState|methodBit|BitExecuting )) != initialState );

    // Check if nobody was executing before now, then start executing
    if( ( initialState & BitExecuting ) == 0 )
    {
        _Strand_ExecuteLoop(self, initialState|methodBit|BitExecuting);
    }
}

//------------------------------------------------------------------------------------------------------------
void Strand_Leave( _In_ Strand* self )
{
    STRAND_ASSERTONSTRAND( self );

    trace_Strand_Leave( self, STRAND_DEBUG_GETNAME(self), self->strandStealedFlag );

    // If there is an encompasing loop, then set this to false so it will bail out
    if( NULL != self->strandStealedFlag )
    {
        *(self->strandStealedFlag) = MI_TRUE;
    }

    _Strand_ExecuteLoop( self, _DisableMethodBit( self, self->currentMethodBit ) );
}

//------------------------------------------------------------------------------------------------------------
void Strand_StartTimer( _In_ Strand* self, _In_ Timer* timer, _In_ MI_Uint64 timeusecs )
{
    STRAND_ASSERTONSTRAND( self );
    DEBUG_ASSERT( NULL == self->timer );
    DEBUG_ASSERT( timer );

    self->timer = timer;
    Timer_SetTime( timer, timeusecs );   // doesnt start the actual timer
    if( BitTimer != self->currentMethodBit )
    {
        TimerResult result = Timer_Start( timer, self );
        if (TimerResult_Success != result)
        {
            // Cancel timer start request
            self->timer = NULL;
            trace_Strand_Cannot_Start_Timer( timer, self );
        }
    }
    else
    {
        trace_Strand_Cannot_Start_Timer( timer, self );
    }
}

void Strand_FireTimer( _In_ Strand* self )
{
    STRAND_ASSERTONSTRAND( self );

    if( NULL != self->timer )
    {
        Timer_Fire( self->timer, self, TimerReason_ManuallyFired );
    }
    else
    {
        trace_Strand_Cannot_Fire_Timer( self );
    }
}

MI_Boolean Strand_HaveTimer( _In_ Strand* self )
{
    STRAND_ASSERTONSTRAND( self );

    if ( self->timer )
        return MI_TRUE;
    else
        return MI_FALSE;
}

//------------------------------------------------------------------------------------------------------------
void _Strand_AcceptOpenCommon(
    _In_        Strand*                 self,
    _In_        Interaction*            interaction )
{
    STRAND_ASSERTONSTRAND( self );

    DEBUG_ASSERT( !self->info.otherAckPending );
    DEBUG_ASSERT( !self->info.thisAckPending );
    DEBUG_ASSERT( !self->info.ackPassthru );

    self->info.interaction.other = interaction;
    interaction->other = &self->info.interaction;
    self->info.opened = MI_TRUE;
    self->info.thisClosedOther = MI_FALSE;
    self->info.otherClosedThis = MI_FALSE;
}

void Strand_AcceptOpenAsync(
    _In_        Strand*                 self,
    _In_        Strand*                 otherStrand )
{
    DEBUG_ASSERT( !STRAND_ISTYPE_MIDDLE( otherStrand ) );
    _Strand_AcceptOpenCommon( self, &otherStrand->info.interaction);

    _Strand_Schedule( otherStrand, BitCompleteOpenAsync );
}

void Strand_AcceptOpenAsyncFromStrandBoth(
    _In_        Strand*                 self,
    _In_        StrandBoth*             otherStrand )
{
    DEBUG_ASSERT( STRAND_ISTYPE_MIDDLE( &otherStrand->base ) );
    _Strand_AcceptOpenCommon( self, &otherStrand->infoRight.interaction );
    otherStrand->asyncOpenInProgress = MI_TRUE;
    _Strand_Schedule( &otherStrand->base, BitCompleteOpenAsync );
}

void Strand_AcceptOpen(
    _In_        Strand*                 self,
    _In_        InteractionOpenParams*  params )
{
    _Strand_AcceptOpenCommon( self, params->interaction );

    if( NULL != params->msg )
    {
        self->info.otherAckPending = MI_TRUE;
    }
    if( NULL != params->origin )
    {
        Strand_Leave( params->origin );
    }
}

static void _DoNothingPost( _In_ Interaction* self, _In_ Message* msg )
{
    MI_UNUSED( self );
    MI_UNUSED( msg );
}

static void _DoNothingOther( _In_ Interaction* self )
{
    MI_UNUSED( self );
}

static InteractionFT _failOpenInteractionFT = {
    _DoNothingPost,
    _DoNothingPost,
    _DoNothingOther,
    _DoNothingOther,
    _DoNothingOther };

static Interaction _failOpenInteraction = { &_failOpenInteractionFT, NULL };

void Strand_FailOpenWithMsg(
    _In_        InteractionOpenParams*  params,
    _In_opt_    Message*                msg)
{
    params->interaction->other = &_failOpenInteraction;

    if( NULL != params->origin )
    {
        Strand_Leave( params->origin );
    }

    if( NULL != msg )
    {
        params->interaction->ft->Post( params->interaction, msg );
    }
    else
    {
        if( NULL != params->msg )
        {
            DEBUG_ASSERT( Message_IsRequest( params->msg ) );
            //TODO convert the original request to ResultMsg and post it back
            //params->interaction->ft->Post( params->interaction, params->msg );
            // Cancel in the meantime:
        }
        //TODO else
        {
            params->interaction->ft->Cancel( params->interaction );
        }
    }
    if( NULL != params->msg )
    {
        params->interaction->ft->Ack( params->interaction );
    }
    params->interaction->ft->Close( params->interaction );
}

void Strand_FailOpenWithResult(
    _In_ InteractionOpenParams*  params,
    MI_Result result,
    _In_ MakeResultMessageCallback callback)
{
    PostResultMsg* resultMsg;

    resultMsg = (*callback)( params->msg, NULL, NULL, MI_RESULT_TYPE_MI, result);

    if( NULL != resultMsg )
    {
        Strand_FailOpenWithMsg( params, &resultMsg->base );
        PostResultMsg_Release(resultMsg);
    }
    else
    {
        Strand_FailOpen( params );
    }
}
