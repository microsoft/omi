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

#include <pal/strings.h>
#include <base/messages.h>
#include <base/log.h>
#include <pal/strings.h>
#include <base/paths.h>
#include <pal/format.h>
#include <base/Strand.h>
#include <protocol/protocol.h>
#include "agentmgr.h"
#include <omi_error/errorutil.h>
#include <provmgr/context.h>

#if defined(CONFIG_POSIX)
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
# include <signal.h>
# include <sys/wait.h>
#endif

#ifndef DISABLE_SHELL
MI_Result AgentMgr_EnumerateShellInstances(_In_ AgentMgr* self,_In_ const ProvRegEntry* proventry, _Inout_ InteractionOpenParams* params);
MI_Result AgentMgr_GetShellInstances(_In_ AgentMgr* self, _Inout_ InteractionOpenParams* params);
#endif

/*
**==============================================================================
**
** Data structures
**
**==============================================================================
*/

#if defined(CONFIG_POSIX)

/*
    RequestItem - stores information about request sent to the agent/provider;
    this item stores original request's operationId (has to be substituted) and request pointer
    In case of agent disconnection, agent-mgr uses this list to send error responses to
    outstanding requests.
*/

typedef enum _RequestItemFinishState
{
    RequestItemFinishState_None = 0,
    RequestItemFinishState_PendingFinishOnError,
    RequestItemFinishState_ProcessedFinishOnError
} RequestItemFinishState;


typedef struct _RequestItem
{
    // managing original interaction coming from dispatcher
    StrandEntry strand;

    MI_Boolean isIdleRequest;
    MI_Boolean pendingCancel;
    RequestItemFinishState finishOnErrorState;

    Message* request;           // Request received from the left
    MI_Uint64 originalOperationId;
    MI_Uint64 key;  // OperationId of the outogoing request; for now RequestItem address (as it was before)
}
RequestItem;

/*
    AgentElem - stores information about single running agent
    (this will be become multiplexer eventually)
*/
struct _AgentElem
{
    StrandMany              strand;

    /* Linked-list support */
    ListElem*               next;
    ListElem*               prev;

    /* hosting context */
    uid_t                   uid;
    gid_t                   gid;

    /* connection to the agent */
    ProtocolSocketAndBase*  protocol;

    /* link to manager */
    AgentMgr*               agentMgr;

    /* agent process pid */
    pid_t                   agentPID;

    MI_Instance*            shellInstance;
    const MI_Char*          shellId;
};

/*
**==============================================================================
*/

#define AGENTELEM_STRANDAUX_CLOSEAGENTITEM 0
#define AGENTELEM_STRANDAUX_ENTRYACK       1

STRAND_DEBUGNAME2( AgentElem, CloseAgentItem, EntryAck );

#define IDLEREQUESTITEM_STRANDAUX_READYTOFINISH 0

STRAND_DEBUGNAME1( IdleRequestItem, ReadyToFinish );

#define REQUESTITEM_STRANDAUX_PREPARETOFINISHONERROR 0

STRAND_DEBUGNAME1( RequestItem, PrepareToFinishOnError );


/*
**==============================================================================
*/

void _AgentElem_InitiateClose( _In_ AgentElem* self )
{
    // remove agent from Mgr's list
    // Do this first so no new request entries are added after this
    ReadWriteLock_AcquireWrite(&self->agentMgr->lock);
    List_Remove(
        &self->agentMgr->headAgents,
        &self->agentMgr->tailAgents,
        (ListElem*)&(self->next));
    ReadWriteLock_ReleaseWrite(&self->agentMgr->lock);

    StrandMany_ScheduleAux( &self->strand, AGENTELEM_STRANDAUX_CLOSEAGENTITEM );
}

void _AgentElem_Post( _In_ Strand* self_, _In_ Message* msg)
{
    AgentElem* self = (AgentElem*)StrandMany_FromStrand(self_);
    DEBUG_ASSERT( NULL != self_ );
    trace_AgentElemPostingMessage(&self->strand.strand.info.interaction, self->strand.strand.info.interaction.other);

    /* ATTN: verify unload message */

    if (BinProtocolNotificationTag == msg->tag)
    {
        BinProtocolNotification* notification = (BinProtocolNotification*)msg;
        if (BinNotificationAgentIdle == notification->type)
        {
            // Check if this agent has outstanding requests -
            // if agent is really idle (only idle notification request)
            // then initiate the close
            if( 1 == self->strand.numEntries )
            {
                _AgentElem_InitiateClose( self );
            }
        }
        /* ignore service messages */
        Strand_Ack( &self->strand.strand );
        return;
    }

    if( !StrandMany_PostFindEntry( &self->strand, msg ) )
    {
        trace_StrandMany_CannotFindItem( Uint64ToPtr(msg->operationId), (int)self->uid );
        _AgentElem_InitiateClose( self );
    }

    // For now ack immediately
    //TODO eventually multiplexer should take care of flow control here
    // For now, we are short circuiting ACK from RequstItem
}

void _AgentElem_PostControl( _In_ Strand* self_, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // not used yet
}

void _AgentElem_Ack( _In_ Strand* self_)
{
    trace_AgentElemAck( &self_->info.interaction, self_->info.interaction.other );
}

void _AgentElem_Cancel( _In_ Strand* self_)
{
    DEBUG_ASSERT( MI_FALSE );  // not used yet
}

void _AgentElem_Close( _In_ Strand* self_)
{
    AgentElem* self = (AgentElem*)StrandMany_FromStrand(self_);

    trace_AgentClosedConnection((int)self->uid);
    // lost connection to the agent ( within 'CloseAgentItem' call):
    //    - send error repsonses to all outstanding requests
    //    - remove agent form the list

    _AgentElem_InitiateClose( self );
}

void _AgentElem_Finish( _In_ Strand* self_)
{
    AgentElem* self = (AgentElem*)StrandMany_FromStrand(self_);
    DEBUG_ASSERT( NULL != self_ );

    // It is ok now for the protocol object to go away
    ProtocolSocketAndBase_ReadyToFinish(self->protocol);

    if (self->shellInstance)
    {
        MI_Instance_Delete(self->shellInstance);
        self->shellInstance = NULL;
    }

    StrandMany_Delete(&self->strand);
}

// AGENTELEM_STRANDAUX_ENTRYACK
void _AgentElem_EntryAck( _In_ Strand* self_)
{
    //Temporary until we have flow control with multiplexing buffers
    Strand_Ack( self_ );

}

// AGENTELEM_STRANDAUX_CLOSEAGENTITEM
static void _AgentElem_CloseAgentItem(Strand* self_);

/*
    Object that implements a single connection going thru binary protocol
    to one agent. It uses that one-to-many interface to channel thru multiple
    operations on the same connection.

    Behavior:
    - Post checks if the message is a idle notification, and if it is and there is
       only one remaining operation (the idle notification one itself) then initiates
       a close. Otherwise it just post the message to the pertinent operation that is
       find using the buildin hash map searching by the operationId field
       in the message.
    - Ack does nothing currently as there is not an explicit in-the-wire flow control
       protocol implemented yet.
    - PostControl and Cancel are not currently implemented
    - Close initiates the closing of all entries and sending the corresponding
       error messages to each one (see _AgentElem_CloseAgentItem below)
    - Shutdown:
       The objects are deleted thru the normal Strand logic. That is,
       once the interaction is closed on both sides and there are no
       entries the object is auto-deleted.

    Unique features and special Behavour:
    - _AgentElem_CloseAgentItem is called at any time is there is an unrecoverable
      error or the connection has been lost and it will iterate thru the existing
      operations/requests sending an appropiate error message to each one.
     - _AgentElem_EntryAck is schedule by each entry (RequestItem) when it
      receives and Ack so that Ack can be simply passed thru to the connection
      (since we dont have yet a more sophisticated on-the-wire flow control
      mechanism).
*/
static StrandFT _AgentElem_FT = {
    _AgentElem_Post,
    _AgentElem_PostControl,
    _AgentElem_Ack,
    _AgentElem_Cancel,
    _AgentElem_Close,
    _AgentElem_Finish,
    NULL,
    _AgentElem_CloseAgentItem,
    _AgentElem_EntryAck,
    NULL,
    NULL,
    NULL };

/*
**==============================================================================
*/

static MI_Result _PrepareMessageForAgent(
            MI_Uint64       operationId,
    _In_    Message*        msg,
    _Out_   Message**       msgOut)
{
    MI_Result result;

    /* clone message (may be incoming message in some cases) */
    result = MessagePackCloneForBinarySending(msg, msgOut);
    if( MI_RESULT_OK == result )
    {
        /* substitute message-id on time server->agent call;
        operationId has to be restored once first response is received */
        (*msgOut)->operationId = operationId;
        (*msgOut)->flags = msg->flags;
    }
    else
    {
        trace_SendRequestToAgent_MessageCloneFailed(result);
    }

    return result;
}

static void _SendErrorResponseAndClose(
    RequestItem* requestItem,
    MI_Result r)
{
    PostResultMsg* resp;
    trace_AgentMgr_SendErrorResponse( requestItem );
    resp = PostResultMsg_NewAndSerialize( requestItem->request, NULL, NULL, MI_RESULT_TYPE_MI, r);

    //TODO - do a force close
    if (!resp)
        return;

    requestItem->request->operationId = requestItem->originalOperationId;

    requestItem->finishOnErrorState = RequestItemFinishState_ProcessedFinishOnError;
    Strand_Post(&requestItem->strand.strand, &resp->base);

    PostResultMsg_Release(resp);

    Strand_Close(&requestItem->strand.strand);
}

// not used much yet (no secondary "semantic" messages at the time)
// currently used for unsubscribe message
void _RequestItem_Post( _In_ Strand* self_, _In_ Message* msg)
{
    RequestItem* self = (RequestItem*)StrandEntry_FromStrand(self_);
    MI_Result result;
    Message* msgOut = NULL;

    DEBUG_ASSERT( NULL != self_ );
    trace_RequestItemPostingMessage( self_, &self->strand.strand.info.interaction, self->strand.strand.info.interaction.other );

    result = _PrepareMessageForAgent( self->key, msg, &msgOut );
    if( MI_RESULT_OK == result )
    {
        StrandEntry_PostParentPassthru(&self->strand, msgOut);
        Message_Release(msgOut);
    }
    else
    {
        trace_RequestItem_PostFailed(result);
    }
}

void _RequestItem_PostControl( _In_ Strand* self_, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // not used yet
}

void _RequestItem_Ack( _In_ Strand* self_)
{
    RequestItem* self = (RequestItem*)StrandEntry_FromStrand(self_);
    DEBUG_ASSERT( NULL != self_ );
    trace_RequestItemAck( &self_->info.interaction, self_->info.interaction.other );

    if (self->finishOnErrorState != RequestItemFinishState_ProcessedFinishOnError)
    {
        StrandEntry_ScheduleAuxParent( &self->strand, AGENTELEM_STRANDAUX_ENTRYACK );
    }

    if (self->finishOnErrorState == RequestItemFinishState_PendingFinishOnError)
    {
        //this is going to set finishOnErrorState to processed state
        _SendErrorResponseAndClose(self, MI_RESULT_FAILED);
    }


    //TODO eventually multiplexer "WITH FC Buffers" should take care of flow control here
}

void _RequestItem_SendCancel( _In_ RequestItem* self )
{
    CancelMsg* msg = CancelMsg_New(self->originalOperationId);  // this will get transformed on _SendMessageToAgent
    MI_Result result;
    Message* msgOut = NULL;

    DEBUG_ASSERT( NULL != self );

    trace_RequestItemCancel( &self->strand.strand );


    if( NULL != msg )
    {
        result = _PrepareMessageForAgent( self->key, &msg->base, &msgOut );
        if( MI_RESULT_OK == result )
        {
            StrandEntry_PostParent(&self->strand, msgOut);
            Message_Release(msgOut);
        }
        else
        {
            trace_RequestItem_Cancel_PrepMessageFailed(result);
        }
        CancelMsg_Release(msg);
    }
    else
    {
        trace_RequestItem_Cancel_CancelMsg_NewFailed();
    }
}

void _RequestItem_Cancel( _In_ Strand* self_ )
{
    RequestItem* self = (RequestItem*)StrandEntry_FromStrand(self_);

    if( self->strand.strand.info.otherAckPending )
    {
        DEBUG_ASSERT( self->strand.ackPassthru );
        // Do nothing now, when the Ack from parent arrives we will send the message
        self->pendingCancel = MI_TRUE;
    }
    else
    {
        _RequestItem_SendCancel( self );
    }
}

void _RequestItem_Finish( _In_ Strand* self_)
{
    RequestItem* self = (RequestItem*)StrandEntry_FromStrand(self_);

    // release request before we delete the entry
    if( NULL != self->request )
    {
        Message_Release(self->request);
        self->request = NULL;
    }

    StrandEntry_Delete( &self->strand );
}

// REQUESTITEM_STRANDAUX_PREPARETOFINISHONERROR
void _RequestItem_PrepareToFinishOnError( _In_ Strand* self_)
{
    RequestItem* self = (RequestItem*)StrandEntry_FromStrand(self_);

    //if we already closed other
    if (self_->info.thisClosedOther)
        return;

    //if there isn't an ack pending on a previous post, send the final response
    if (!self_->info.thisAckPending)
    {
        _SendErrorResponseAndClose(self, MI_RESULT_FAILED);
        return;
    }

    //else mark for finish when the next ack arrives
    self->finishOnErrorState = RequestItemFinishState_PendingFinishOnError;
}

/*
    Object that implements a single operation/request going to an agent thru
    a binary protocol connection. Uses that one-to-many interface to multiplex multiple
    operations in a single connection (AgentElem).

    Behavior:
    - Post calls _PrepareMessageForAgent to adapt the message to be send on the
       wire the uses StrandEntry_PostParentPassthru to post to the parent
       using the default many-to-one post implementation that enques the message
       on the AgentElem
    - Ack checks on the state of finishOnErrorState. On the normal case the ack is
       just passed thru to the parent by using AGENTELEM_STRANDAUX_ENTRYACK
       but if the state is RequestItemFinishState_PendingFinishOnError then an
       error is send instead and if the state is RequestItemFinishState_ProcessedFinishOnError
       it means nothing else is needed.
    - PostControl is not currently implemented
    - Cancel check if there is an Ack pending on the other side of the interaction (dispatcher)
       what means that in that case the cancel cannot be sent immediately and just
       set pendingCancel to true (see _RequestItem_ParentAck below). Otherwise sends
       the cancel immediately.
    - Close uses the default implementation
    - Shutdown:
       The objects are deleted thru the normal Strand logic. That is,
       once the interaction is closed on both sides the object is auto-deleted.
       Note that the interaction is closed once the final message is received as
       noted in _RequestItem_ParentPost below

    Unique features and special Behavour:
    - _RequestItem_PrepareToFinishOnError is scheduled when the parent
       _AgentElem_CloseAgentItem execute, that is, when for some reason
       the connection to the agent needs to be closed. In that case it checks
       if the Interaction has been already closed (so it doesnt need to do anything),
       or if there is an Ack pending on the other side of the interaction (dispatcher)
       what means that in that case the cancel cannot be sent immediately and just
       sets finishOnErrorState RequestItemFinishState_PendingFinishOnError.
       Otherwise it will directly send the error response and close the interaction
       (finishOnErrorState  will be set to RequestItemFinishState_ProcessedFinishOnError
       in that case).
    - _RequestItem_AddedToParent is used to deliver the initial request ONCE
       the Item has been added to the parent AgentElem connection
    - _RequestItem_ParentPost just post the message from the parent back to
       the left interaction (typically dispatcher) unless the connection has already being
       closed for some reason. It restores the original operationId that is replaced in
       the connection to the agent and it also checks if the message is a final message,
       in which case closes the interaction.
    - _RequestItem_ParentAck checks if the corresponding Post was PassThru
       and in that case sends the Ack passThru. It also checks if there was a pending
       cancel to be send (see Cancel above) and send its now that is possible.
*/
static StrandFT _RequestItem_FT = {
    _RequestItem_Post,
    _RequestItem_PostControl,
    _RequestItem_Ack,
    _RequestItem_Cancel,
    NULL,
    _RequestItem_Finish,
    NULL,
    _RequestItem_PrepareToFinishOnError,
    NULL,
    NULL,
    NULL,
    NULL };


void _IdleRequestItem_Post( _In_ Strand* self_, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // not used
}

void _IdleRequestItem_PostControl( _In_ Strand* self_, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // not used
}

void _IdleRequestItem_Ack( _In_ Strand* self_ )
{
    DEBUG_ASSERT( MI_FALSE );  // not used
}

void _IdleRequestItem_Finish( _In_ Strand* self_)
{
    RequestItem* self = (RequestItem*)StrandEntry_FromStrand(self_);

    DEBUG_ASSERT( NULL == self->request );

    StrandEntry_Delete( &self->strand );
}

// IDLEREQUESTITEM_STRANDAUX_READYTOFINISH
void _IdleRequestItem_ReadyToFinish( _In_ Strand* self_)
{
    RequestItem* self = (RequestItem*)StrandEntry_FromStrand(self_);

    Strand_ResetDelayFinish(&self->strand.strand);
}

/*
    Object that implements the especific request needed to receive the Idle notification
    from the agent. It is attached as one Entries on the one-to-many interface with the
    agent connection (AgentElem).

    Behavior:
    - Post, PostControl and Ack are never used
    - Shutdown:
       The object is not deleted thru the normal Strand logic but only
       when the connection is finished. For that SetDelayFinish is set,
       and only reset when _IdleRequestItem_ReadyToFinish is called,
       what would happen when the parent agentElem is closed.
       Aalso note the the idle notification is processed directly by the
       AgentElem as never reaches the IdleRequestItem.
       IdleRequestItem is only used to initiate the corresponding object,
       IdleNotification, in the agent )
*/
static StrandFT _IdleRequestItem_FT = {
    _IdleRequestItem_Post,
    _IdleRequestItem_PostControl,
    _IdleRequestItem_Ack,
    NULL,
    NULL,
    _IdleRequestItem_Finish,
    NULL,
    _IdleRequestItem_ReadyToFinish,
    NULL,
    NULL,
    NULL,
    NULL };

/*
**==============================================================================
*/

void _AgentElem_NewEntry( _In_ StrandMany* self, _In_ StrandEntry* newEntry, _In_opt_ Message* msg, _Inout_ MI_Boolean* failed )
{
    DEBUG_ASSERT( NULL != failed );
    DEBUG_ASSERT( !(*failed) );    //TODO process this properly

    // Nothing to do here. The entry will post its initial message once it receives AddedToParent
}

void _RequestItem_AddedToParent( _In_ StrandEntry* self, _In_ Message* msg )
{
    RequestItem* requestItem = (RequestItem*)self;

    DEBUG_ASSERT( NULL != msg );

    if( requestItem->isIdleRequest )
    {
        // There is no Interaction to deliver an Ack in this case
        StrandEntry_PostParent( &requestItem->strand, msg );
    }
    else
    {
        StrandEntry_PostParentPassthru( &requestItem->strand, msg );
    }
}

// Message back from protocol
void _RequestItem_ParentPost( _In_ StrandEntry* self, _In_ Message* msg)
{
    RequestItem* requestItem = (RequestItem*)self;
    //should never receive a parent post when the parent previously told us to wrap up things on error
    DEBUG_ASSERT(requestItem->finishOnErrorState  == RequestItemFinishState_None);

    if( self->strand.info.thisClosedOther )
    {
        trace_RequestItem_ParentPost_AfterClose( requestItem, msg );
    }
    else
    {
        trace_RequestItemParentPost( requestItem, msg );

        /* restore operationId */
        requestItem->request->operationId = requestItem->originalOperationId;
        msg->operationId = requestItem->originalOperationId;

        Strand_Post( &requestItem->strand.strand, msg );

        /* remove item if result received */
        if( Message_IsFinalResponse(msg) )
        {
            // Now we can close interaction (nothing else is going to be posted)
            Strand_Close( &requestItem->strand.strand );
        }
    }
}

void _RequestItem_ParentAck(_In_ StrandEntry* self)
{
    RequestItem* requestItem = (RequestItem*)self;

    if( !requestItem->isIdleRequest )
    {
        if( requestItem->strand.ackPassthru )
        {

            if( requestItem->pendingCancel )
            {
                requestItem->pendingCancel = MI_FALSE;
                _RequestItem_SendCancel( requestItem );
            }

            Strand_Ack( &self->strand );
        }
        else
        {
            //only case we do a Parent Post without a need to ackPassthru is when
            //posting CancelMsg (See _RequestItem_SendCancel). The strand should have been in canceled state by then
            DEBUG_ASSERT(self->strand.canceled);
        }
    }
    else
    {
        DEBUG_ASSERT( !requestItem->strand.ackPassthru );
    }
}

static StrandManyInternalFT _AgentElem_InternalFT = {
    _AgentElem_NewEntry,
    NULL,
    NULL,
    NULL,
    NULL,
    _RequestItem_AddedToParent,
    _RequestItem_ParentPost,
    NULL,
    _RequestItem_ParentAck,
    NULL };
/*
**==============================================================================
**
** Local functions
**
**==============================================================================
*/
static MI_Uint64 _NextOperationId()
{
    static ptrdiff_t _operationId = 0;
    return (MI_Uint64) Atomic_Inc(&_operationId);
}


// Called with AgentMgr lock acquired
static AgentElem* _FindAgent(
    AgentMgr* self,
    uid_t uid,
    gid_t gid)
{
    AgentElem* agent;
    ListElem* elem;

    elem = self->headAgents;

    while (elem)
    {
        agent = FromOffset(AgentElem,next,elem);

        if (uid == agent->uid && gid == agent->gid)
        {
            return agent;
        }

        elem = elem->next;
    }

    return 0;
}
#ifndef DISABLE_SHELL
static AgentElem* _FindShellAgent(
    AgentMgr* self,
    uid_t uid,
    gid_t gid,
    RequestMsg *msg)
{
    AgentElem* agent;
    ListElem* elem;
    MI_Char *shellId = msg->base.shellId;

    elem = self->headAgents;

    while (elem)
    {
        agent = FromOffset(AgentElem,next,elem);

        if (uid == agent->uid && gid == agent->gid)
        {
            if (shellId && agent->shellId && (Tcscmp(shellId, agent->shellId) == 0))
            {
                return agent;
            }
        }

        elem = elem->next;
    }

    return 0;
}
#endif

static pid_t _SpawnAgentProcess(
    Sock s,
    int logfd,
    uid_t uid,
    gid_t gid,
    const char* provDir,
    MI_Uint32 idletimeout)
{
    pid_t child;
    int fdLimit;
    int fd;
    char param_sock[32];
    char param_logfd[32];
    char param_idletimeout[32];
    const char* agentProgram = OMI_GetPath(ID_AGENTPROGRAM);

    child = fork();

    if (child < 0)
        return -1;  /* Failed */

    if (child > 0)
        return child;   /* Started */

    /* We are in child process here */

    /* switch user */
    if (0 != SetUser(uid,gid))
    {
        _exit(1);
    }

    /* Close all open file descriptors except provided socket
     (Some systems have UNLIMITED of 2^64; limit to something reasonable) */

    fdLimit = getdtablesize();
    if (fdLimit > 2500 || fdLimit < 0)
    {
        fdLimit = 2500;
    }

    /* ATTN: close first 3 also! Left for debugging only */
    for (fd = 3; fd < fdLimit; ++fd)
    {
        if (fd != s && fd != logfd)
            close(fd);
    }

    /* prepare parameter:
        socket fd to attach */
    Snprintf(param_sock, sizeof(param_sock), "%d", (int)s);
    Snprintf(param_logfd, sizeof(param_logfd), "%d", (int)logfd);
    Snprintf(param_idletimeout, sizeof(param_idletimeout), "%d", (int)idletimeout);

    execl(agentProgram,
        agentProgram,
        param_sock,
        param_logfd,
        "--destdir",
        OMI_GetPath(ID_DESTDIR),
        "--providerdir",
        provDir,
        //"--idletimeout",
        //param_idletimeout,
        "--loglevel",
        Log_GetLevelString(Log_GetLevel()),
        NULL);

    trace_AgentLaunch_Failed(scs(agentProgram), errno);
    _exit(1);
    return -1;  /* never get here */
}

static void _AgentElem_CloseAgentItem( Strand* self_ )
{
    AgentElem* agent = (AgentElem*)StrandMany_FromStrand(self_);
    RequestItem* requestItem;

    StrandMany_BeginIteration( &agent->strand );

    /* send error repsonses to all outstanding requests */
    while( NULL != (requestItem = (RequestItem*)StrandMany_Iterate( &agent->strand )) )
    {
        if(  requestItem->isIdleRequest )
        {
            StrandEntry_ScheduleAux(&requestItem->strand, IDLEREQUESTITEM_STRANDAUX_READYTOFINISH );
        }
        else
        {
            StrandEntry_ScheduleAux(&requestItem->strand, REQUESTITEM_STRANDAUX_PREPARETOFINISHONERROR );
        }
        // No need to call StrandMany_DeleteEntry(&requestItem->strand) to delete requestItem (it would do so itself )
    }

    if (agent->protocol)
    {
        // We can now close the interaction with protocol if not done already
        if( !agent->strand.strand.info.thisClosedOther )
            Strand_Close( &agent->strand.strand );
    }
    else
    {
        agent->strand.strand.info.thisClosedOther = agent->strand.strand.info.otherClosedThis = MI_TRUE;
    }

    /* SIGCHILD HANDLER will take care of pid waiting */
    /*if (agent->agentPID > 0)
    {
        int loc = 0;
        pid_t p = waitpid(agent->agentPID, &loc, WNOHANG);

        LOGI_CHAR(("waitpid returned %d, loc %d",(int)p, loc));

        if (p != agent->agentPID)
        {
            kill(agent->agentPID, SIGKILL);
            p = waitpid(agent->agentPID, &loc, WNOHANG);

            LOGW_CHAR(("sent KILL; waitpid returned %d, loc %d",(int)p, loc));
        }
    }*/

    // the AgentElem should delete itself on Finish
}

size_t _AgentElem_HashMapHashProc(const HashBucket* bucket)
{
    const RequestItem* self = (const RequestItem*)StrandEntry_FromBucketConst(bucket);
    return (size_t)self->key;
}

int _AgentElem_HashMapEqualProc(_In_ const HashBucket* bucket1, _In_ const HashBucket* bucket2)
{
    const RequestItem* entry1 = (const RequestItem*)StrandEntry_FromBucketConst(bucket1);
    const RequestItem* entry2 = (const RequestItem*)StrandEntry_FromBucketConst(bucket2);
    return entry1->key == entry2->key;
}

StrandEntry* _AgentElem_FindRequest(_In_ const StrandMany* parent, _In_ const Message* msg)
{
    AgentElem* agent = (AgentElem*)parent;
    RequestItem forSearch;
    HashBucket* bucket;

    forSearch.key = msg->operationId;

    bucket = HashMap_Find(&agent->strand.many,&forSearch.strand.bucket);

    if( NULL == bucket )
    {
        trace_AgentElem_FindRequest_CannotFindKey( agent, &agent->strand.strand, forSearch.key );
        return NULL;
    }
    else
    {
        RequestItem* self = (RequestItem*)StrandEntry_FromBucket(bucket);
        trace_AgentElemFoundKey( agent, &agent->strand.strand, forSearch.key, self, &self->strand.strand );
        return (StrandEntry*)self;
    }
}

// Called with AgentMgr lock acquired
static AgentElem* _CreateAgent(
    _In_ AgentMgr* self,
    uid_t uid,
    gid_t gid)
{
    AgentElem* agent = 0;
    Sock s[2];
    int logfd = -1;
    InteractionOpenParams interactionParams;

    /* create communication pipe */
    if(0 != socketpair(AF_UNIX, SOCK_STREAM, 0, s))
    {
        trace_SocketPair_Failed();
        return 0;
    }

    if (MI_RESULT_OK != Sock_SetBlocking(s[0], MI_FALSE) ||
        MI_RESULT_OK != Sock_SetBlocking(s[1], MI_FALSE))
    {
        trace_SetNonBlocking_Failed();
        goto failed;
    }

    /* create/open log file for agent */
    {
        char path[PAL_MAX_PATH_SIZE];

        if (0 != FormatLogFileName(uid, gid, path))
        {
            trace_CannotFormatLogFilename();
            goto failed;
        }

        /* Create/open fiel with permisisons 644 */
        logfd = open(path, O_WRONLY|O_CREAT|O_APPEND, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
        if (logfd == -1)
        {
            trace_CreateLogFile_Failed(scs(path), (int)errno);
            goto failed;
        }
    }

    agent = (AgentElem*)StrandMany_New(
                            STRAND_DEBUG( AgentElem )
                            &_AgentElem_FT,
                            &_AgentElem_InternalFT,
                            sizeof(AgentElem),
                            STRAND_FLAG_ENTERSTRAND,
                            NULL,
                            100,
                            _AgentElem_HashMapHashProc,
                            _AgentElem_HashMapEqualProc,
                            _AgentElem_FindRequest );

    if (!agent)
        goto failed;

    agent->agentMgr = self;
    agent->uid = uid;
    agent->gid = gid;

    if ((agent->agentPID =
        _SpawnAgentProcess(
            s[0],
            logfd,
            uid,
            gid,
            self->provDir,
            (MI_Uint32)(self->provmgr.idleTimeoutUsec / 1000000))) < 0)
    {
        trace_CannotSpawnChildProcess();
        goto failed;
    }

    close(logfd);
    logfd = -1;

    //printf("Press any key to continue\n");
    //getchar();


    /* Close socket 0 - it will be used by child process */
    Sock_Close(s[0]);
    s[0] = INVALID_SOCK;

    Strand_OpenPrepare(&agent->strand.strand,&interactionParams,NULL,NULL,MI_TRUE);

    if( MI_RESULT_OK != ProtocolSocketAndBase_New_AgentConnector(
        &agent->protocol,
        self->selector,
        s[1],
        &interactionParams ) )
            goto failed;

    s[1] = INVALID_SOCK;

    trace_AgentItemCreated(agent);
    List_Append(
        &self->headAgents,
        &self->tailAgents,
        (ListElem*)&(agent->next));

    return agent;

failed:
    if (INVALID_SOCK != s[0])
        Sock_Close(s[0]);

    if (INVALID_SOCK != s[1])
        Sock_Close(s[1]);

    if (-1 != logfd)
        close(logfd);

    if (agent)
    {
        _AgentElem_InitiateClose(agent);
    }

    return 0;
}


static AgentElem* _CreateShellAgent(
    _In_ AgentMgr* self,
    uid_t uid,
    gid_t gid,
    CreateInstanceReq *msg)
{
    MI_Instance *shellInstance = NULL;
    AgentElem *agentElem;
    MI_Value value;
    MI_Type type;

    if (MI_Instance_Clone(msg->instance, &shellInstance) != MI_RESULT_OK)
    {
        return NULL;
    }

    agentElem =  _CreateAgent(self, uid, gid);

    if (agentElem == NULL)
    {
        MI_Instance_Delete(shellInstance);
        return NULL;
    }

    agentElem->shellInstance = shellInstance;
    if ((MI_Instance_GetElement(shellInstance, MI_T("ShellId"), &value, &type, NULL, NULL) == MI_RESULT_OK) &&
            (type == MI_STRING))
    {
        agentElem->shellId = value.string;
    }


    return agentElem;
}


// Called with AgentMgr lock acquired
static MI_Result _SendRequestToAgent_Common(
    _In_ RequestItem* requestItem,
    _In_ Message* msg,
    _In_opt_ const ProvRegEntry* proventry)
{
    MI_Result result;
    Message* req = NULL;
    MI_Uint64 operationId;

    operationId = _NextOperationId();
    requestItem->key = operationId;

    result = _PrepareMessageForAgent( operationId, msg, &req );
    if( MI_RESULT_OK != result )
    {
        trace_PrepareMessageForAgent_Failed(result);
        StrandEntry_DeleteNoAdded( &requestItem->strand );
        return result;
    }

    if( NULL != proventry )
    {
        DEBUG_ASSERT( Message_IsRequest(req) );
        {
            RequestMsg* request = (RequestMsg*)req;
            request->libraryName = Batch_Strdup(req->batch, proventry->libraryName);
            request->instanceLifetimeContext = proventry->instanceLifetimeContext;

            if (!request->libraryName)
            {
                trace_SendRequestToAgent_Batch_Strdup_Failed();
                StrandEntry_DeleteNoAdded( &requestItem->strand );
                Message_Release(req);
                return MI_RESULT_FAILED;
            }
        }
    }

    trace_AgentMgr_SendRequestToAgent(
        req,
        req->tag,
        MessageName(req->tag),
        req->operationId,
        requestItem->originalOperationId,
        requestItem->key );

    StrandEntry_ScheduleAdd( &requestItem->strand, req);

    Message_Release(req);

    return MI_RESULT_OK;
}

// Called with AgentMgr lock acquired
static MI_Result _SendIdleRequestToAgent(
    _Inout_ AgentElem* agent )
{
    RequestItem* requestItem;
    MI_Result result;
    BinProtocolNotification* notification;

    notification = BinProtocolNotification_New( BinNotificationAgentIdle );

    if( !notification )
    {
        trace_SendRequestToAgent_StrandNewFailed();
        return MI_RESULT_FAILED;
    }

    requestItem = (RequestItem*) StrandEntry_New(
                                    STRAND_DEBUG( IdleRequestItem )
                                    &agent->strand,
                                    &_IdleRequestItem_FT,
                                    sizeof(RequestItem),
                                    STRAND_FLAG_ENTERSTRAND|STRAND_FLAG_NOINTERACTION,
                                    NULL );
    if( NULL == requestItem )
    {
        trace_SendRequestToAgent_StrandNewFailed();
        BinProtocolNotification_Release(notification);
        return MI_RESULT_FAILED;
    }

    requestItem->isIdleRequest = MI_TRUE;
    requestItem->pendingCancel = MI_FALSE;
    requestItem->finishOnErrorState = RequestItemFinishState_None;
    Strand_SetDelayFinish(&requestItem->strand.strand);
    Strand_Leave(&requestItem->strand.strand);

    result = _SendRequestToAgent_Common( requestItem, &notification->base, NULL );

    BinProtocolNotification_Release(notification);

    return result;
}

// Called with AgentMgr lock acquired
static MI_Result _SendRequestToAgent(
    _Inout_ AgentElem* agent,
    _In_ InteractionOpenParams* interactionParams,
    _In_ Message* msg,
    _In_ const ProvRegEntry* proventry)
{
    RequestItem* requestItem;

    DEBUG_ASSERT( NULL != interactionParams );
    trace_SendMessageToAgent( msg->tag );

    requestItem = (RequestItem*) StrandEntry_New(
                                    STRAND_DEBUG( RequestItem )
                                    &agent->strand,
                                    &_RequestItem_FT,
                                    sizeof(RequestItem),
                                    0,
                                    interactionParams );
    if( NULL == requestItem )
    {
        trace_SendRequestToAgent_StrandNewFailed();
        return MI_RESULT_FAILED;
    }

    requestItem->originalOperationId = msg->operationId;
    requestItem->request = msg;
    requestItem->isIdleRequest = MI_FALSE;
    requestItem->pendingCancel = MI_FALSE;
    requestItem->finishOnErrorState = RequestItemFinishState_None;

    /* Add ref to keep request around until Result received */
    Message_AddRef(msg);

    return _SendRequestToAgent_Common( requestItem, msg, proventry );
}

#endif

/*
**==============================================================================
**
** Public API
**
**==============================================================================
*/
MI_Result AgentMgr_Init(
    AgentMgr* self,
    Selector* selector)
{
    /* Check parameters */
    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

    memset(self, 0, sizeof(*self));

    /* Initialize the provider manager */
    MI_RETURN_ERR(ProvMgr_Init(&self->provmgr, selector, NULL, NULL, OMI_GetPath(ID_PROVIDERDIR)));

    self->home = PAL_Strdup(OMI_GetPath(ID_PREFIX));
    self->provDir = PAL_Strdup(OMI_GetPath(ID_PROVIDERDIR));

    self->selector = selector;

    ReadWriteLock_Init(&self->lock);

#if defined(CONFIG_ENABLE_PREEXEC)
    PreExec_Construct(&self->preexec);
#endif /* defined(CONFIG_ENABLE_PREEXEC) */

    return MI_RESULT_OK;
}

MI_Result AgentMgr_Destroy(
    AgentMgr* self)
{
    ListElem* listElem;

    ProvMgr_Destroy(&self->provmgr);
    PAL_Free(self->home);
    PAL_Free(self->provDir);

#if defined(CONFIG_ENABLE_PREEXEC)
    PreExec_Destruct(&self->preexec);
#endif /* defined(CONFIG_ENABLE_PREEXEC) */

#if defined(CONFIG_POSIX)
    /*
        Free all outstanding agents
    */
    ReadWriteLock_AcquireWrite(&self->lock);
    listElem = self->headAgents;
    while (listElem)
    {
        AgentElem* agent = FromOffset(AgentElem,next,listElem);

        StrandMany_ScheduleAux( &agent->strand, AGENTELEM_STRANDAUX_CLOSEAGENTITEM );

        listElem = listElem->next;
    }
    ReadWriteLock_ReleaseWrite(&self->lock);
#endif

    /* Invalidate self */
    memset(self, 0xdd, sizeof(*self));

    return MI_RESULT_OK;
}

void AgentMgr_OpenCallback(
    _Inout_ InteractionOpenParams* params )
{
    MI_Result result;
    AgentMgr_OpenCallbackData* callbackData = (AgentMgr_OpenCallbackData*)params->callbackData;

    result = AgentMgr_HandleRequest( callbackData->self, params, callbackData->proventry );
    if( MI_RESULT_OK != result )
    {
        Strand_FailOpenWithResult(params, result, PostResultMsg_NewAndSerialize);
    }
}

MI_Result AgentMgr_HandleRequest(
    _In_ AgentMgr* self,
    _Inout_ InteractionOpenParams* params,
    _In_ const ProvRegEntry* proventry)
{
    MI_Result result = MI_RESULT_OK;
    AgentElem* agent;
    uid_t uid;
    gid_t gid;
    RequestMsg* msg = (RequestMsg*)params->msg;

    trace_AgentMgrHandleRequest(msg, msg->base.tag);

    DEBUG_ASSERT( Message_IsRequest(&msg->base) );

#ifndef DISABLE_SHELL
    if (msg->base.flags & WSMAN_IsShellOperation)
    {
        /* We need to process the enumerate and get internally so we can enumerate
         * the shells that are registered in the agent manager
         */
        if (msg->base.tag == EnumerateInstancesReqTag)
        {
            return AgentMgr_EnumerateShellInstances(self, proventry, params);
        }
        else if (msg->base.tag == GetInstanceReqTag)
        {
            return AgentMgr_GetShellInstances(self, params);
        }
        else
        {
            /* Rest of operations need to pass through to the provider host */
        }
    }
#endif

    if (proventry->hosting == PROV_HOSTING_INPROC)
    {
#if defined(CONFIG_POSIX)
        /* For in proc provider, following checks if an incoming
         * request from non-root user, and omiserver is running
         * under root user, then return access denied error, otherwise
         * it could cause a problem that non-root user runs code under root
         */
        if (IsAuthCallsIgnored() == 0)
        {
            /* Reject in-proc provider requests for non-root client users */
            if (IsRoot() == 0 && msg->authInfo.uid != 0)
            {
                /* user name */
                char name[USERNAME_SIZE];
                char* uname = (char*)name;
                if (0 != GetUserName(msg->authInfo.uid, name))
                    uname = "unknown user";
                trace_NonRootUserAccessInprocProvider(uname, proventry->className, proventry->nameSpace);
                return MI_RESULT_ACCESS_DENIED;
            }
        }
#endif /* defined(CONFIG_POSIX) */

        return ProvMgr_NewRequest(
            &self->provmgr,
            proventry,
            params );
    }

    if ((proventry->hosting == PROV_HOSTING_USER)
#ifndef DISABLE_SHELL
        || (proventry->hosting == PROV_HOSTING_REQUESTOR_SHELL)
#endif
        )
    {
        if (0 != LookupUser(proventry->user, &uid, &gid))
        {
            trace_GetUserUidGid_Failed(scs(proventry->user));
            return MI_RESULT_FAILED;
        }
    }
    else
    {
        uid = msg->authInfo.uid;
        gid = msg->authInfo.gid;
        MI_UNREFERENCED_PARAMETER(uid);
        MI_UNREFERENCED_PARAMETER(gid);
    }

#if defined(CONFIG_ENABLE_PREEXEC)
    if (PreExec_Exec(&self->preexec, proventry->preexec, uid, gid) != 0)
        return MI_RESULT_FAILED;
#endif /* defined(CONFIG_ENABLE_PREEXEC) */

#if defined(CONFIG_POSIX)

    // We cannot use ReadWriteLock_AcquireRead(&self->lock);
    // as we may need to create the object here
    // (and there is no option to upgrade from read to write acquisition)
    ReadWriteLock_AcquireWrite(&self->lock);

#ifndef DISABLE_SHELL
    if (msg->base.flags & WSMAN_IsShellOperation)
    {
        if (msg->base.tag == CreateInstanceReqTag)
        {
            CreateInstanceReq *createReq = (CreateInstanceReq*) msg;
            agent = _CreateShellAgent(self, uid, gid, createReq);
        }
        else
        {
            agent = _FindShellAgent(self, uid, gid, msg);
        }
    }
    else
#endif
    {
        agent = _FindAgent(self, uid, gid);

        if (!agent)
        {
            agent = _CreateAgent(self, uid, gid);
        }

    }
    if (!agent)
    {
        trace_FailedLoadProviderAgent();
        result = MI_RESULT_FAILED;
    }
    else
    {
        result = _SendIdleRequestToAgent( agent );
    }

    if( MI_RESULT_OK == result )
    {
        result = _SendRequestToAgent(agent, params, &msg->base, proventry);
    }

    ReadWriteLock_ReleaseWrite(&self->lock);

    return result;

#else
    MI_UNUSED(agent);
    /* windows version hosts all providers as 'in-proc' */
    return ProvMgr_NewRequest(
            &self->provmgr,
            proventry,
            params );
#endif
}

#ifndef DISABLE_SHELL
MI_Result AgentMgr_EnumerateShellInstances(
        _In_ AgentMgr* self,
        _In_ const ProvRegEntry* proventry,
        _Inout_ InteractionOpenParams* params)
{
    Context ctx;
    MI_Result r;
    ListElem* elem;
    MI_Instance *instance = NULL;

    elem = self->headAgents;

    r = Context_Init(&ctx, &self->provmgr, NULL, params);

    if (r != MI_RESULT_OK)
    {
        return r;
    }

    ReadWriteLock_AcquireWrite(&self->lock);

    /* Enumerate through the hosts and post an instance for each */

    //r = MI_Context_PostInstance(&ctx->base, instance);
    //
    //
    while (elem)
    {
        AgentElem* agent;

        agent = FromOffset(AgentElem,next,elem);


        if (agent->shellInstance)
        {
            MI_Value value;
            MI_Type type;

            r = Instance_NewDynamic(&instance, MI_T("Shell"), MI_FLAG_CLASS, NULL);
            if (r != MI_RESULT_OK)
            {
                goto cleanup;
            }

            r = MI_Instance_GetElement(agent->shellInstance, MI_T("ShellId"), &value, &type, NULL, NULL);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }
            r = MI_Instance_AddElement(instance, MI_T("ShellId"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }

            r = MI_Instance_GetElement(agent->shellInstance, MI_T("Name"), &value, &type, NULL, NULL);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }
            r = MI_Instance_AddElement(instance, MI_T("Name"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }

            r = MI_Instance_GetElement(agent->shellInstance, MI_T("ResourceUri"), &value, &type, NULL, NULL);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }
            r = MI_Instance_AddElement(instance, MI_T("ResourceUri"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }

            r = MI_Instance_GetElement(agent->shellInstance, MI_T("Owner"), &value, &type, NULL, NULL);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }
            r = MI_Instance_AddElement(instance, MI_T("Owner"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }

            value.string = MI_T("0");
            r = MI_Instance_AddElement(instance, MI_T("ProcessId"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }
            value.string = MI_T("PT7200.000S");
            r = MI_Instance_AddElement(instance, MI_T("IdleTimeOut"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }

            r = MI_Instance_GetElement(agent->shellInstance, MI_T("InputStreams"), &value, &type, NULL, NULL);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }
            r = MI_Instance_AddElement(instance, MI_T("InputStreams"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }

            r = MI_Instance_GetElement(agent->shellInstance, MI_T("OutputStreams"), &value, &type, NULL, NULL);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }
            r = MI_Instance_AddElement(instance, MI_T("OutputStreams"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }

            value.string = MI_T("PT2147483.647S");
            r = MI_Instance_AddElement(instance, MI_T("MaxIdleTimeOut"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }

            r = MI_Instance_GetElement(agent->shellInstance, MI_T("Locale"), &value, &type, NULL, NULL);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }
            r = MI_Instance_AddElement(instance, MI_T("Locale"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }

            r = MI_Instance_GetElement(agent->shellInstance, MI_T("DataLocale"), &value, &type, NULL, NULL);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }
            r = MI_Instance_AddElement(instance, MI_T("DataLocale"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }

            r = MI_Instance_GetElement(agent->shellInstance, MI_T("CompressionMode"), &value, &type, NULL, NULL);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }
            r = MI_Instance_AddElement(instance, MI_T("CompressionMode"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }

            value.string = MI_T("Yes");
            r = MI_Instance_AddElement(instance, MI_T("ProfileLoaded"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }
            value.string = MI_T("UTF8");
            r = MI_Instance_AddElement(instance, MI_T("Encoding"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }
            value.string = MI_T("Blocked");
            r = MI_Instance_AddElement(instance, MI_T("BufferMode"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }
            value.string = MI_T("Connected");
            r = MI_Instance_AddElement(instance, MI_T("State"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }
            value.string = MI_T("P0DT1H25M54S");
            r = MI_Instance_AddElement(instance, MI_T("ShellRunTime"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }
            value.string = MI_T("P0DT1H25M54S");
            r = MI_Instance_AddElement(instance, MI_T("ShellInactivity"), &value, MI_STRING, 0);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }

            r = MI_Context_PostInstance(&ctx.base, instance);
            if (r != MI_RESULT_OK)
            {
                goto cleanup2;
            }

            MI_Instance_Delete(instance);

            if (r != MI_RESULT_OK)
            {
                goto cleanup;
            }
        }

        elem = elem->next;
    }

cleanup:
    MI_Context_PostResult(&ctx.base, r);

    ReadWriteLock_ReleaseWrite(&self->lock);

    return r;

cleanup2:
    MI_Instance_Delete(instance);
    goto cleanup;
}

MI_Result AgentMgr_GetShellInstances(
        _In_ AgentMgr* self,
        _Inout_ InteractionOpenParams* params)
{
    return MI_RESULT_NOT_SUPPORTED;
}

#endif
