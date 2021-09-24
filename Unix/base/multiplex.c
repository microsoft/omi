/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "multiplex.h"
#include <omi_error/errorutil.h>

#define MUX_HASHTABLESIZE   100

/*
**==============================================================================
**
** Data structures
**
**==============================================================================
*/

typedef struct _ConnectionIn
{
    StrandMany      strand;

    MuxIn*          mux;
    // nothing else for now
}
ConnectionIn;

typedef struct _OperationOut
{
    // managing outgoint interaction to dispatcher,providerMgr,etc.
    StrandEntry     strand;  

    MI_Uint64       key;  // for now OperationOut address
} 
OperationOut;

/*
**==============================================================================
*/

STRAND_DEBUGNAME( ConnectionIn )
STRAND_DEBUGNAME( OperationOut )

/*
**==============================================================================
*/

void _OperationOut_Ack( _In_ Strand* self_)
{
    //OperationOut* self = (OperationOut*)StrandEntry_FromStrand(self_);
    DEBUG_ASSERT( NULL != self_ );
    trace_OperationOut_Ack( &self_->info.interaction, self_->info.interaction.other );

    // for now do nothing
    //TODO eventually multiplexer should take care of flow control here
}

void _OperationOut_Cancel( _In_ Strand* self)
{
    trace_OperationOut_Cancel( self );
    // for now do nothing
}

void _OperationOut_Close( _In_ Strand* self_)
{
    //OperationOut* self = (OperationOut*)StrandEntry_FromStrand(self_);
    DEBUG_ASSERT( NULL != self_ );
    trace_OperationOut_Close( &self_->info.interaction, self_->info.interaction.other );

    // Just close the other side
    if( !self_->info.thisClosedOther )
        Strand_Close( self_ );
}

/*
    Object that implements a single operation coming out of a binary protocol 
    connection. Uses that one-to-many interface to multiplex multiple operations
    in a single connection.

    Behavior:
    - Uses the default many-to-one post implementation that just enqueue messages
       on the ConnectionIn
    - Ack does nothing currently as there is not an explicit in-the-wire flow control 
       protocol implemented yet.
    - Cancel is not currently implemented
    - Close check if the connection has already been closed and if not
       just closes the other side
    - Shutdown: 
       The objects are deleted thru the normal Strand logic. That is,
       once the interaction is closed on both sides the object is auto-deleted.
*/
static StrandFT _OperationOut_FT = { 
    NULL, 
    NULL, 
    _OperationOut_Ack, 
    _OperationOut_Cancel, 
    _OperationOut_Close,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL };

/*
**==============================================================================
*/

void _ConnectionIn_Post( _In_ Strand* self_, _In_ Message* msg )
{
    ConnectionIn* self = (ConnectionIn*)StrandMany_FromStrand(self_);
    DEBUG_ASSERT( NULL != self_ );
    trace_ConnectionIn_Post(
        self,
        msg,
        msg->tag,
        MessageName(msg->tag),
        msg->operationId,
        &self->strand.strand.info.interaction, 
        self->strand.strand.info.interaction.other );

    // For now ack immediately
    //TODO eventually refined multiplexer should take care of flow control here
    // Need to schedule (so no other Post occurs during Post)
    StrandMany_ScheduleAck( &self->strand );
    
    if( CancelMsgTag == msg->tag )
    {
        StrandEntry* entry;
        
        trace_ConnectionIn_PostCancel(
            self_,
            msg,
            msg->tag,
            MessageName(msg->tag),
            msg->operationId,
            &self->strand.strand.info.interaction, 
            self->strand.strand.info.interaction.other );
        
        entry = self->strand.findEntryProc( &self->strand, msg );
        if( NULL != entry )
        {
            StrandMany_CancelEntry( entry );
        }
        else
        {
            trace_ConnectionIn_PostCancelError(
                self_,
                msg,
                msg->tag,
                MessageName(msg->tag),
                msg->operationId,
                &self->strand.strand.info.interaction, 
                self->strand.strand.info.interaction.other );
        }
    }
    else
    {
        if( !StrandMany_PostFindEntry( &self->strand, msg ) )
        {
            OperationOut* newOperation;
            PostResultMsg* resp;
            MI_Result result = MI_RESULT_OK;

            trace_ConnectionInPost_NewOp( Uint64ToPtr(msg->operationId), msg, MessageName(msg->tag) );

            if( msg->tag == UnsubscribeReqTag )
            {
                // TODO we can remove this once client uses cancelation instead of UnsubscribeReq
                trace_ConnectionInPost_IgnoreUnsubscribeReq( msg, msg->operationId );
                return;
            }

            newOperation = (OperationOut*)StrandEntry_New( 
                STRAND_DEBUG( OperationOut ) 
                &self->strand, 
                &_OperationOut_FT, 
                sizeof(OperationOut),
                STRAND_FLAG_ENTERSTRAND,
                NULL);

            if( NULL == newOperation )
            {
                trace_ConnectionInPost_NewOpFailed( Uint64ToPtr(msg->operationId) );
                DEBUG_ASSERT( MI_FALSE );
                result = MI_RESULT_FAILED;
            }
            else
            {
                // we have to set up the key before actually adding the entry
                newOperation->key = msg->operationId;
                
                result = StrandMany_AddEntry( &newOperation->strand );
                // We are about to call into open into the components on the right that may
                // steal the thread synchronously and start posting back, 
                // therefore we need to leave the ConnectionIn strand that may be posted upon
                // (see additional comment on OperationOut below)
                Strand_Leave( &self->strand.strand );   

                if( MI_RESULT_OK != result )
                {
                    trace_ConnectionInPost_CannotAddNewOp( Uint64ToPtr(msg->operationId) );
                    DEBUG_ASSERT( MI_FALSE );
                }
                else
                {
                    // open interaction to the right
                    // Leave also OperationOut strand on open, otherwise any Post in the same thread will be delayed
                    // and the stack will eventually deadlock on in-proc providers that send
                    // several posts in the same open thread
                    Strand_Open(
                        &newOperation->strand.strand, 
                        self->mux->callback,
                        self->mux->callbackData,
                        msg,
                        MI_TRUE);
                }
            }

            if( MI_RESULT_OK != result )
            {
                resp = (*self->mux->makeResultMessageCallback)( msg, NULL, NULL, MI_RESULT_TYPE_MI, result);
                
                if (resp)
                {
                    // We can be outside the strand here so use this SchedulePost instead of Post
                    StrandMany_SchedulePost( &self->strand, &resp->base );
                }
                else
                {
                    trace_ConnectionInPost_MessageAllocFailed( result );
                    // TODO: return a pre-allocated msg once we have that change
                }
            }
        }
    }
}

void _ConnectionIn_PostControl( _In_ Strand* self_, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // not used yet
}

void _ConnectionIn_Ack( _In_ Strand* self_)
{
    trace_OperationIn_Ack( &self_->info.interaction, self_->info.interaction.other );
    // Nothing to do here
    //TODO eventually multiplexer should take care of flow control here
}

void _ConnectionIn_Cancel( _In_ Strand* self_)
{
    DEBUG_ASSERT( MI_FALSE );  // not used yet
}

void _ConnectionIn_Close( _In_ Strand* self_)
{
    ConnectionIn* self = (ConnectionIn*)StrandMany_FromStrand(self_);
    DEBUG_ASSERT( NULL != self_ );
    trace_ConnectionInClose( &self->strand.strand.info.interaction, self->strand.strand.info.interaction.other );

    StrandMany_CloseAllEntries( &self->strand );
    // Close back the protocol if there are no entries/operations
    if (self->strand.numEntries == 0)
        Strand_Close( &self->strand.strand );

    if( self->mux->onCloseCallback )
    {
        (*self->mux->onCloseCallback)(self);
    }
}

void _ConnectionIn_EntryDeleted( _In_ StrandMany* self )
{
    //if we are already closed and all operations on mux are closed
    if ((self->strand.info.otherClosedThis) && (self->numEntries == 0))
        Strand_Close( &self->strand );
}

/*
    Object that implements a single connection coming in from binary protocol 
    Uses that one-to-many interface to fan-out multiple operations
    from the same connection.

    Behavior:
    - Post checks if the message is a cancel, and if it is then finds the
       corresponing operation by searching the built-in hash map by operationId
       then it sends a Interaction Interface cancel directly to the operation.
       If the message is NOT a cancel then it search the operation in the 
       built-in hash map by operationId and then 2 things can happen:
       * There is a existing operation in which case it just delivers the 
          secondary message to the existing interaction 
       * This is a new operation and therefore creates the OperationOut object,
          opens the interaction to the right with it and calls the callback for new
          request defined in the MuxIn.
    - Ack does nothing currently as there is not an expecific in-the-wire flow control 
       protocol implemented yet.
    - PostControl and Cancel are not currently implemented
    - Close initiates the closing of all entries and if there are no entries remained
       to be closes then closes the interaction back itself.
       It also calls the OnCloseCallback method defined in MuxIn
    - Shutdown: 
       The objects are deleted thru the normal Strand logic. That is,
       once the interaction is closed on both sides and there are no
       entries the object is auto-deleted.

    Unique features and special Behaviour:
    - _ConnectionIn_EntryDeleted is executed once an entry is deleted,
       that is to address the case where when the connection was closed not 
       all entries were deleted yet and therefore it needs to be finally closed
       once there are no more entries.
*/
static StrandFT _ConnectionIn_FT = { 
    _ConnectionIn_Post, 
    _ConnectionIn_PostControl, 
    _ConnectionIn_Ack, 
    _ConnectionIn_Cancel, 
    _ConnectionIn_Close,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL };

/*
**==============================================================================
*/

static StrandManyInternalFT _MuxIn_InternalFT = {
    NULL,
    _ConnectionIn_EntryDeleted,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL };


/*
**==============================================================================
**
** Local functions
**
**==============================================================================
*/
size_t _ConnectionIn_HashMapHashProc(const HashBucket* bucket)
{
    const OperationOut* self = (const OperationOut*)StrandEntry_FromBucketConst(bucket);
    return (size_t)self->key;
}

int _ConnectionIn_HashMapEqualProc(_In_ const HashBucket* bucket1, _In_ const HashBucket* bucket2)
{
    const OperationOut* entry1 = (const OperationOut*)StrandEntry_FromBucketConst(bucket1);
    const OperationOut* entry2 = (const OperationOut*)StrandEntry_FromBucketConst(bucket2);
    return entry1->key == entry2->key;
}

StrandEntry* _ConnectionIn_FindOperation(_In_ const StrandMany* parent_, _In_ const Message* msg)
{
    ConnectionIn* parent = (ConnectionIn*)parent_;
    OperationOut forSearch;
    HashBucket* bucket;

    forSearch.key = msg->operationId;
    
    bucket = HashMap_Find(&parent->strand.many,&forSearch.strand.bucket);

    if( NULL == bucket )
    {
        trace_ConnectionInFindRequest_CannotFind( parent, &parent->strand.strand, forSearch.key );
        return NULL;
    }
    else
    {
        OperationOut* self = (OperationOut*)StrandEntry_FromBucket(bucket);
        trace_ConnectionInFindRequest_Found( parent, &parent->strand.strand, forSearch.key, self, &self->strand.strand );
        return (StrandEntry*)self;
    }
}   

/*
**==============================================================================
**
** Public API
**
**==============================================================================
*/
void MuxIn_Open( _Inout_ InteractionOpenParams* params )
{
    MuxIn* self = (MuxIn*)params->callbackData; // callbackData is the MuxIn object
    ConnectionIn* connectionIn;
    
    DEBUG_ASSERT( NULL != params->interaction );
    DEBUG_ASSERT( NULL == params->msg );
    DEBUG_ASSERT( NULL != params->callbackData );

    connectionIn = (ConnectionIn*)StrandMany_New(
                            STRAND_DEBUG( ConnectionIn )
                            &_ConnectionIn_FT,
                            &_MuxIn_InternalFT,
                            sizeof(ConnectionIn),
                            STRAND_FLAG_ENTERSTRAND,
                            params,
                            MUX_HASHTABLESIZE,
                            _ConnectionIn_HashMapHashProc,
                            _ConnectionIn_HashMapEqualProc,
                            _ConnectionIn_FindOperation );

    if( NULL == connectionIn )
    {
        trace_MuxInOpen_AllocFailed();
        Strand_FailOpen( params );
    }
    else
    {
        connectionIn->mux = self;

        Strand_Leave( &connectionIn->strand.strand );
        // note that connectionIn is automatically deleted by strand management
    }
}

