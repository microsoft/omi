/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <pal/strings.h>
#include <pal/format.h>
#include <base/messages.h>
#include <base/Strand.h>
#include <provreg/provreg.h>
#include <indication/common/indilog.h>
#include <omi_error/errorutil.h>
#include "mgr.h"

/*
**==============================================================================
**
** This file implements the interaction interface for indication manager;
** Interaction object implemented here provides following,
** (1) called by dispatcher to handle the subscribe/unsubscribe request(s), which
**     come from protocol;
** (2) aggregates results messages (subscribe response, unsubscribe response,
**     and indication instances) from provider; delivers subscribe response to
**     and indication instance(s) to protocol;
**
**==============================================================================
*/

typedef struct _SubscribeEntry SubscribeEntry;

/*
**==============================================================================
**
** This structure stores information of the request sent to the agentMgr;
**
** Upon a subscribe request reaches to indication manager, it will send
** multi-sub messages to provider due to the subscribe may targets to
** multi-classes. One object of the structure is for one target class.
**
**==============================================================================
*/
struct _SubscribeEntry
{
    StrandEntry             strand;
    SubscribeEntry*         next;       /* Links all scheduled entry */
    RequestMsg*             request;    /* Request sent to provider */
                                        /* !Release the reference when closed! */
    MI_Uint64               key;        /* Address of SubscribeEntry */
    IndicationManager*      mgr;
    IndicationClassEntry*   ice;
};


/*
**==============================================================================
**
** SubscribeElem - stores information about subscribe request
**
** It is used to manage all sub-request of the subscribe request
**
**==============================================================================
*/
typedef struct _SubscribeElem
{
    StrandMany strand;
    Subscription* sub;          /* Release the ref count when closed */
    RequestMsg* request;        /* Request from protocol */
    MI_Uint32 nScheduled;       /* number of classes scheduled */
    MI_Uint32 nSent;            /* number of classes sent to agentmgr */
    MI_Uint32 nHandled;         /* number of classes initially handled by agentmgr */
    MI_Uint32 nFailed;          /* number of classes failed */
    MI_Uint32 nSubscribed;      /* number of classes subscribed */
    MI_Uint32 nComplete;        /* number of classes completed, i.e., either cancelled or failed */
    MI_Result aggrresult;       /* aggregated result of subscription */
    SubscribeStatus status;     /* status of the subscription */
}SubscribeElem;


/*
**==============================================================================
**
** Strand function tables definition for SubscribeElem
**
**==============================================================================
*/

STRAND_DEBUGNAME( SubscribeElem )
STRAND_DEBUGNAME( SubscribeEntry )

void _SubscribeElem_Post(_In_ Strand* self_, _In_ Message* msg)
{
    StrandMany* self = StrandMany_FromStrand(self_);
    trace_SubElem_PostComplete(
        self, 
        msg,
        msg->tag,
        MessageName(msg->tag),
        msg->operationId );
    switch(msg->tag)
    {
    case UnsubscribeReqTag:
        trace_SubElem_PostCancelSubscribe(
            self, 
            msg,
            msg->tag,
            MessageName(msg->tag),
            msg->operationId );

        Strand_Ack(self_);

        /* Cancel all subscribe entries */
        Strand_Cancel(self_);
        break;

    default:
        trace_SubElem_Post(
            self, 
            msg,
            msg->tag,
            MessageName(msg->tag),
            msg->operationId );
        break;
    }
}

void _SubscribeElem_PostControl(_In_ Strand* self_, _In_ Message* msg)
{
    DEBUG_ASSERT(MI_FALSE);
}

void _SubscribeElem_Ack(_In_ Strand* self_)
{
    trace_SubElem_Ack(
        self_,
        &self_->info.interaction,
        self_->info.interaction.other);
}

/*
 * Cancel can be called due to protocol closed the connection
 */
void _SubscribeElem_Cancel( _In_ Strand* self_)
{
    StrandMany* self = StrandMany_FromStrand(self_);
    trace_SubElem_Cancel(
        self,
        &self_->info.interaction,
        self_->info.interaction.other);

    /* Wait for final result and close itself */
}

/* Do nothing Unsubscribe request will cancel the operation */
void _SubscribeElem_Finish( _In_ Strand* self_)
{
    SubscribeElem* se = (SubscribeElem*)StrandMany_FromStrand(self_);
    trace_SubElem_Finish(
        se,
        &self_->info.interaction,
        self_->info.interaction.other);

    /* Cleanup the subscription */
    {
        IndicationManager* im = (IndicationManager*)se->sub->base._container;
        IndiMgr_RemoveSubscription(im, se->sub);
        Subscription_Release(se->sub);
        se->sub = NULL;
    }

    if (se->request)
    {
        Message_Release(&se->request->base);
        se->request = NULL;
    }

    /* Cleanup the memory of SubscribeElem */
    Strand_Delete(self_);
}

void _SubscribeElem_Close(Strand* self_)
{
    trace_SubscribeElem_Close(
        self_,
        &self_->info.interaction,
        self_->info.interaction.other);
    /* Workaround for binary protocol, when socket was closed, there is no cancel */
    /* send from client to server; upon cancel logic implemented in binary protocol, */
    /* following line should be removed */
    Strand_Cancel(self_);
}

static StrandFT _SubscribeElem_FT = { 
    _SubscribeElem_Post,
    _SubscribeElem_PostControl,
    _SubscribeElem_Ack,
    _SubscribeElem_Cancel,
    _SubscribeElem_Close,
    _SubscribeElem_Finish,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL};


/*
**==============================================================================
**
** StrandMany internal function tables definition 
**
**==============================================================================
*/
static void _SubscribeElem_CheckSendFinalResult(
    _In_ StrandMany* self)
{
    SubscribeElem* se = (SubscribeElem*)self;
    trace_SubElem_CheckSendFinalResult(self);
    if ((se->nSent == se->nScheduled) && (se->nComplete == se->nHandled))
    {
        if (se->status == SUBSCRIBE_SUB_SUBSCRIBED ||
            se->status == SUBSCRIBE_SUB_STARTED)
        {
            PostResultMsg* finalmsg;
            se->aggrresult = (se->nFailed == se->nComplete) ? se->aggrresult : MI_RESULT_OK;
            se->status = (se->nFailed == se->nComplete) ? SUBSCRIBE_SUB_FAILED : SUBSCRIBE_SUB_CANCELLED;
            finalmsg = PostResultMsg_NewAndSerialize(&se->request->base, NULL, STR_SUB_ALL_TARGET_CLASS_FAILED, MI_RESULT_TYPE_MI, se->aggrresult);
            if (finalmsg)
            {
                Strand_Post(&self->strand, &finalmsg->base);
                Message_Release(&finalmsg->base);
            }
            /* else trace log */

            /* close self upon receiving final message */
            Strand_Close(&self->strand);

            trace_SubElem_CheckSendComplete(se, SubscribeStatusName(se->status), se->nHandled);
        }
        else
            trace_SubscribeElem_CheckSendFinalResult(se, SubscribeStatusName(se->status));
    }
}

void _SubscribeElem_NewEntry(
    _In_        StrandMany*     self,
    _In_        StrandEntry*    newEntry,
    _In_opt_    Message*        msg,
    _Inout_     MI_Boolean*     failed)
{
    SubscribeEntry* subItem = (SubscribeEntry*)newEntry;
    
    DEBUG_ASSERT(NULL!=msg);
    DEBUG_ASSERT(NULL != failed);
    DEBUG_ASSERT(MI_FALSE == *failed);
    
    if( self->strand.canceled || newEntry->strand.canceled )
    {
        /* Strand layer will delete the entry internally */
        subItem->ice->status = SUBSCRIBE_SUB_FAILED;
        *failed = MI_TRUE;
        Message_Release( &subItem->request->base );
        subItem->request = NULL;
    }
    else
    {
        SubscribeElem* se = (SubscribeElem*)self;

        trace_SubElem_NewEntry(
            self, 
            newEntry, 
            msg,
            msg->tag,
            MessageName(msg->tag),
            msg->operationId );

        DEBUG_ASSERT( Message_IsRequest(msg) );

        switch(msg->tag)
        {
        case SubscribeReqTag:
            subItem->ice->status = SUBSCRIBE_SUB_STARTED;
            break;

        default:
            trace_SubElem_NewEntry_UnexpectedMessage(
                msg,
                msg->tag,
                MessageName(msg->tag),
                msg->operationId );
            *failed = MI_TRUE;
            Message_Release( &subItem->request->base );
            subItem->request = NULL;
            return;
        }

        /* calculate handled class count */
        se->nSent ++;
        se->nHandled ++;

        /* Set aggregation result */
        if (se->aggrresult != MI_RESULT_OK)
            se->aggrresult = MI_RESULT_OK;

        trace_SubElement_NewDone(self, se->nScheduled, se->nSent, se->nHandled, se->nSubscribed, se->nFailed, se->nComplete, se->aggrresult);
    }
}

void _SubscribeElem_EntryPost( _In_ StrandMany* self_, _In_ Message* msg)
{
    SubscribeElem* se = (SubscribeElem*)self_;
    DEBUG_ASSERT( NULL != self_ );
    trace_SubElem_EntryPost(
        &se->strand.strand.info.interaction,
        se->strand.strand.info.interaction.other,
        msg,
        msg->tag,
        MessageName(msg->tag),
        msg->operationId );

    switch ( msg->tag )
    {
        case PostResultMsgTag:
            {
                PostResultMsg* res = (PostResultMsg*)msg;
                se->nComplete++;
                if (res->result != MI_RESULT_OK)
                {
                    /* Failure final result means the subscription somehow failed after subscribed */
                    se->nFailed ++;
                    se->aggrresult = res->result;
                }

                /* Check if all entries are completed and send final message to protocol if yes */
                _SubscribeElem_CheckSendFinalResult(self_);
            }
            break;

        case SubscribeResTag:
            {
                se->nSubscribed ++;

                /* Subscribe succeed, send success response to protocol */
                if ((se->nSubscribed == 1) && (se->status == SUBSCRIBE_SUB_STARTED))
                {
                    se->aggrresult = MI_RESULT_OK;
                    se->status = SUBSCRIBE_SUB_SUBSCRIBED;
                    trace_SubElem_PostSendSuccessResponse(se, SubscribeStatusName(se->status));
                    Strand_Post(&self_->strand, msg );  // resend it to the left
                }
            }
            break;

        case PostIndicationMsgTag:
            {
                trace_SubElem_EntryPost_PassToLeft(
                    se,
                    msg,
                    msg->tag,
                    MessageName(msg->tag),
                    msg->operationId );
                Strand_Post(&se->strand.strand, msg);
            }
            break;

        default:
            trace_SubscribeElem_EntryPost_UnexpectedMsg(
                msg,
                msg->tag,
                MessageName(msg->tag),
                msg->operationId );
            break;
    }

    trace_SubElem_EntryPostDone(se, se->nScheduled, se->nSent, se->nHandled, se->nSubscribed, se->nFailed, se->nComplete, se->aggrresult);
}

void _SubscribeElem_EntryClose( _In_ StrandMany* self )
{
    trace_SubElem_EntryClose();
}

void _SubscribeEntry_AddedToParent( _In_ StrandEntry* self_, _In_opt_ Message* msg)
{
    SubscribeEntry* subItem = (SubscribeEntry*)self_;
    IndicationManager* mgr = subItem->mgr;
    IndicationHost_Data data;

    DEBUG_ASSERT( NULL != msg );
    
    /* send request to agentmgr */
    data.host = &mgr->base;
    data.proventry = subItem->ice->regentry;
    Strand_Open(&subItem->strand.strand,IndicationHost_HandleRequest,&data,msg,MI_TRUE);

    trace_SubItem_HandleRequest(
        subItem,
        ((SubscribeReq*)msg)->nameSpace,
        ((SubscribeReq*)msg)->className );
}

StrandManyInternalFT _SubscribeElem_InternalFT = {
    _SubscribeElem_NewEntry,
    NULL,
    _SubscribeElem_EntryPost,
    NULL,
    _SubscribeElem_EntryClose,
    _SubscribeEntry_AddedToParent,
    NULL,
    NULL,
    NULL,
    NULL };

/*
**==============================================================================
**
** SubscribeEntry function tables definition 
**
**==============================================================================
*/
void _SubscribeEntry_Post( _In_ Strand* self_, _In_ Message* msg)
{
    SubscribeEntry* self = (SubscribeEntry*)StrandEntry_FromStrand(self_);
    DEBUG_ASSERT( NULL != self_ );
    trace_SubscribeEntry_PostInteraction(
        &self->strand.strand.info.interaction,
        self->strand.strand.info.interaction.other,
        msg,
        msg->tag,
        MessageName(msg->tag),
        msg->operationId );

    switch ( msg->tag )
    {
        case PostResultMsgTag:
            {
                PostResultMsg* res = (PostResultMsg*)msg;
                trace_SubscribeEntry_PostFinalMsg(
                    self,
                    SubscribeStatusName(self->ice->status),
                    msg,
                    msg->tag,
                    MessageName(msg->tag),
                    msg->operationId,
                    res->result);

                if (self->ice->status == SUBSCRIBE_SUB_STARTED ||
                    self->ice->status == SUBSCRIBE_SUB_SUBSCRIBED)
                {
                    self->ice->subresult = res->result;
                    self->ice->status = (res->result == MI_RESULT_OK) ? SUBSCRIBE_SUB_CANCELLED : SUBSCRIBE_SUB_FAILED;

                    /* close self upon receiving final message */
                    Strand_Close(self_);

                    trace_SubscribeEntry_PostClosedSelf(
                        self, SubscribeStatusName(self->ice->status));
                }
                else
                {
                    /* drop the message */
                    trace_SubscribeEntry_PostUnexpectedFinal(
                        self,
                        SubscribeStatusName(self->ice->status),
                        msg,
                        msg->tag,
                        MessageName(msg->tag),
                        msg->operationId );
                    /* Ack the message since we are not going to do anything with it */
                    Strand_Ack( self_ );
                    return;
                }
            }
            break;

        case SubscribeResTag:
            if (self->ice->status == SUBSCRIBE_SUB_STARTED)
            {
                self->ice->subresult = MI_RESULT_OK;
                self->ice->status = SUBSCRIBE_SUB_SUBSCRIBED;
                trace_SubscribeEntry_PostEntry(
                    self, SubscribeStatusName(self->ice->status));
            }
            else
            {
                /* drop the message */
                trace_SubscribeEntry_PostUnexpectedSubscribe(
                    self, 
                    SubscribeStatusName(self->ice->status),
                    msg,
                    msg->tag,
                    MessageName(msg->tag),
                    msg->operationId );
                /* Ack the message since we are not going to do anything with it */
                Strand_Ack( self_ );
                return;
            }
            break;
        
        case PostIndicationMsgTag:
            /* Pass through to SubscribeElem */
            break;

        default:
            trace_SubscribeEntry_PostUnsupportedMessage(
                msg,
                msg->tag,
                MessageName(msg->tag),
                msg->operationId );
            return;
    }

    StrandEntry_PostParentPassthru(&self->strand, msg);
    trace_SubscribeEntry_PostedMsg(
        msg,
        msg->tag,
        MessageName(msg->tag),
        msg->operationId );
}

void _SubscribeEntry_PostControl( _In_ Strand* self_, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );
}

void _SubscribeEntry_Ack( _In_ Strand* self_)
{
    DEBUG_ASSERT( NULL != self_ );
    trace_SubscribeEntry_Ack(
        self_,
        self_->info.interaction.other);
}

/*
 * Cancel can be called due to the protocol (socket) was closed;
 * Either lost the socket connection to client or server shutdown
 */
void _SubscribeEntry_Cancel( _In_ Strand* self)
{
    StrandEntry* entry = StrandEntry_FromStrand(self);
    SubscribeEntry* se = (SubscribeEntry*)entry;
    SubscribeReq* req = (SubscribeReq*)se->request;
    trace_SubscribeEntry_Cancel(entry, req->nameSpace, req->className);

    /* It expects to get final result from agentmgr */
    /* and then close self */
}

void _SubscribeEntry_Finish( _In_ Strand* self)
{
    SubscribeEntry* entry = (SubscribeEntry*)StrandEntry_FromStrand(self);
    trace_SubscribeEntry_Finish();
    /* Release the message */
    Message_Release(&entry->request->base);
    Strand_Delete(self);
}

static StrandFT _SubscribeEntry_FT = { 
    _SubscribeEntry_Post,
    _SubscribeEntry_PostControl,
    _SubscribeEntry_Ack,
    _SubscribeEntry_Cancel,
    NULL,
    _SubscribeEntry_Finish,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL};

static SubscribeReq* _Create_SubscribeReq(
    _In_ IndicationManager* self,
    _In_ const ProvRegEntry* pre,
    _In_ SubscribeReq* req)
{
    SubscribeReq* msg = 0;

    /* Duplicate incoming request to substitute callback pointer */
    msg = SubscribeReq_New(req->base.base.operationId, req->base.base.flags);
    if (!msg)
    {
        return NULL;
    }

    msg->base.options = req->base.options;
    AuthInfo_Copy( &msg->base.authInfo, &req->base.authInfo );
    msg->nameSpace = Batch_Tcsdup(msg->base.base.batch, req->nameSpace);
    msg->className = Batch_Tcsdup(msg->base.base.batch, pre->className);
    msg->filter = Batch_Tcsdup(msg->base.base.batch, req->filter);
    msg->language = Batch_Tcsdup(msg->base.base.batch, req->language);
    if (req->bookmark)
        msg->bookmark = Batch_Tcsdup(msg->base.base.batch, req->bookmark);
    msg->base.userAgent = req->base.userAgent;

    if (!msg->nameSpace || !msg->className || !msg->filter || !msg->language || (req->bookmark && !msg->bookmark))
    {
        SubscribeReq_Release(msg);
        return NULL;
    }

    switch (pre->regType)
    {
    case PROVREG_INDICATION:
        msg->targetType = SUBSCRIP_TARGET_DEFAULT;
        break;
    default:
        msg->targetType = req->targetType;
        break;
    }
    return msg;
}

/* TODO: Reuse hash proc with other components */
size_t __HashMapHashProc(const HashBucket* bucket)
{
    const SubscribeEntry* self = (const SubscribeEntry*)StrandEntry_FromBucketConst(bucket);
    return (size_t)self->key;
}

/* TODO: Reuse hash proc with other components */
int __HashMapEqualProc(_In_ const HashBucket* bucket1, _In_ const HashBucket* bucket2)
{
    const SubscribeEntry* entry1 = (const SubscribeEntry*)StrandEntry_FromBucketConst(bucket1);
    const SubscribeEntry* entry2 = (const SubscribeEntry*)StrandEntry_FromBucketConst(bucket2);
    return entry1->key == entry2->key;
}

/* TODO: Reuse hash proc with other components */
StrandEntry* __FindSubRequest(_In_ const StrandMany* parent, _In_ const Message* msg)
{
    SubscribeElem* subelem = (SubscribeElem*)parent;
    SubscribeEntry forSearch;
    HashBucket* bucket;
    forSearch.key = msg->operationId;
    bucket = HashMap_Find(&subelem->strand.many, &forSearch.strand.bucket);

    if( NULL == bucket )
    {
        trace__FindSubRequest_CannotFindKey( subelem, &subelem->strand.strand, forSearch.key );
        return NULL;
    }
    else
    {
        SubscribeEntry* self = (SubscribeEntry*)StrandEntry_FromBucket(bucket);
        trace_FindSubRequest_FoundKey(
            subelem, &subelem->strand.strand, forSearch.key, self, &self->strand.strand );
        return (StrandEntry*)self;
    }
}


/*
**==============================================================================
**
** Handle SubscribeReq Message
**
**  NOTE:
**  UnsubscribeReq message will be posted by protocol to _SubscribeElem_Post
**  directly;
**==============================================================================
*/
_Use_decl_annotations_
void IndiMgr_HandleSubscribeReq(
    InteractionOpenParams* params )
{
    IndicationManager* self = (IndicationManager*)params->callbackData;
    SubscribeReq* req = (SubscribeReq*)params->msg;
    MI_Result r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
    Filter* filter = NULL;
    Listener* listener = NULL;
    Subscription* subscrip = NULL;
    MI_Boolean subscripAddedToIndiMgr = MI_FALSE;
    const MI_Char* errmsg = STR_OUT_OF_MEMORY;
    MI_Instance *error = NULL;

    trace_IndiMgr_HandleSubscribe(self, params->interaction, req, req->base.base.operationId);

    DEBUG_ASSERT( NULL != params->msg );
    
    if (!req->nameSpace || !req->language || !req->filter)
    {
        trace_IndiMgr_HandleSubscribe_InvalidParameters();
        r = (NULL == req->nameSpace) ? MI_RESULT_INVALID_NAMESPACE : MI_RESULT_INVALID_QUERY;
        errmsg = (NULL == req->nameSpace) ? STR_NULL_NAMESPACE_NOT_ALLOWED : STR_NULL_DIALECT_NOT_ALLOWED;
        goto FAILED;
    }

    /* Create filter and set namespace */
    filter = Filter_New(req->filter, req->language, &error);
    if (NULL == filter)
    {
        goto FAILED;
    }
    else
    {
        MI_StringA nsa;
        MI_Char* ns;
        nsa.size = 1;
        ns = (MI_Char*)req->nameSpace;
        nsa.data = &ns;
        if (Filter_SetNamespace(filter, &nsa) != 0)
        {
            trace_IndiMgr_HandleSubscribe_FailedToSetNamespace(filter, req);
            goto FAILED;
        }
    }

    listener = Listener_New(LISTENER_TEMP);
    if (NULL == listener)
        goto FAILED;

    subscrip = Subscription_New((FilterBase*)filter, listener);
    if (NULL == subscrip)
        goto FAILED;

    /* Generate subscription ID */
    subscrip->subscriptionID = GenerateSubscriptionID();
    if (0 != IndiMgr_AddSubscription(self, subscrip))
    {
        trace_IndiMgr_HandleSubscribe_FailedToAddSub(subscrip, req);
        goto FAILED;
    }
    subscripAddedToIndiMgr = MI_TRUE;

    /* Send the request to provider manager */
    if (NULL == subscrip->classlist)
    {
        trace_IndiMgr_HandleSubscribe_NoClassFound(req);
        goto FAILED;
    }
    else
    {
        SubscribeEntry *eheader = NULL;
        IndicationClassEntry *e;
        SubscribeElem *sube = (SubscribeElem*)StrandMany_New(
            STRAND_DEBUG( SubscribeElem )
            &_SubscribeElem_FT,
            &_SubscribeElem_InternalFT,
            sizeof(SubscribeElem),
            STRAND_FLAG_ENTERSTRAND|STRAND_FLAG_DELAYACCEPTOPEN,    
            params,
            128,
            __HashMapHashProc,
            __HashMapEqualProc,
            __FindSubRequest);
        if (!sube)
        {
            trace_IndiMgr_HandleSubscribeReq_StrandManyNewFailed(req);
            r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            goto FAILED;
        }

        /* Ref to subscription released by _SubscribeElem_Finish */
        Subscription_AddRef(subscrip);
        sube->sub = subscrip;
        Message_AddRef(&req->base.base);
        sube->request = &req->base;
        sube->nScheduled = 0;
        sube->nHandled = 0;
        sube->nSubscribed = 0;
        sube->nFailed = 0;
        sube->nComplete = 0;
        sube->nSent = 0;
        sube->status = SUBSCRIBE_INITED;
        sube->aggrresult = MI_RESULT_FAILED;

        /* Set targettype of subscribe request */
        req->targetType = (MI_Uint32)subscrip->classlist->targetType;

        /* Iterate through target classes and send subscribe request to each class */
        e = subscrip->classlist->head;
        while(e)
        {
            SubscribeReq *msg = _Create_SubscribeReq(self, e->regentry, req);
            if (msg)
            {
                SubscribeEntry* entry;
                msg->subscriptionID = subscrip->subscriptionID;

                entry = (SubscribeEntry*) StrandEntry_New( 
                            STRAND_DEBUG(SubscribeEntry)
                            &sube->strand,
                            &_SubscribeEntry_FT,
                            sizeof(SubscribeEntry),
                            0,
                            NULL);
                if( NULL == entry )
                {
                    trace_IndiMgr_HandleSubscribeReq_StrandNewFailed(req);
                    SubscribeReq_Release(msg);
                    NitsIgnoringError(); // this error will be ignored and we will still continue the operation
                    continue;
                }

                /* SubscribeEntry owns the msg */
                entry->request = &msg->base;
                entry->mgr = self;
                entry->ice = e;
                entry->key = PtrToUint64(entry);                
                msg->base.base.operationId = entry->key;

                /* add entry to list */
                if (eheader)
                {
                    entry->next = eheader->next;
                    eheader->next = entry;
                }
                else
                {
                    entry->next = NULL;
                    eheader = entry;
                }
                sube->nScheduled++;
            }
            else
            {
                trace_IndiMgr_HandleSubscribe_FailedToCreateMessage(
                    e->regentry->className, req);
            }
            e = e->next;
        }

        if (eheader)
        {
            SubscribeEntry* subentry = eheader;
            sube->status = SUBSCRIBE_SUB_STARTED;

            /* Accept Open and ACK open now to protocol to indicate that msg was received */
            Strand_AcceptOpen( &sube->strand.strand, params );
            Strand_Ack( &sube->strand.strand );
            Strand_Leave( &sube->strand.strand );
 
            /* Send one subscribe request per class */
            while (subentry)
            {
                SubscribeEntry* nextEntry = subentry->next;

                trace_IndiMgr_HandleSubscribe_BeginAddingEntry(
                    subentry, &subentry->request->base, MessageName(subentry->request->base.tag), req);

                StrandEntry_ScheduleAdd(&subentry->strand, &subentry->request->base);

                trace_IndiMgr_HandleSubscribe_AddingEntryDone(subentry, req);

                subentry = nextEntry;
            }
            r = MI_RESULT_OK;
        }
        else
        {
            Strand_Leave(&sube->strand.strand);
            /* Failed to create all SubscribeEntries */
            trace_IndiMgr_HandleSubscribeReq_FailedCreate(req);
            r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }
    }

FAILED:
    if (filter)
    {
        Filter_Release(filter);
    }
    if (listener)
    {
        Listener_Release(listener);
    }
    if ((r != MI_RESULT_OK) && subscripAddedToIndiMgr)
    {
        IndiMgr_RemoveSubscription(self, subscrip);
    }

    if (r != MI_RESULT_OK)
    {
        PostResultMsg* finalmsg;
        if (!error && subscrip)
        {
            error = subscrip->lastError;
            if (error)
                r = subscrip->lastErrorCode;
        }
        finalmsg = PostResultMsg_NewAndSerialize(&req->base.base, error, errmsg, MI_RESULT_TYPE_MI, r);
        Strand_FailOpenWithMsg( params, (Message*)finalmsg  );
        if (finalmsg)
        {
            PostResultMsg_Release(finalmsg);
        }
        else
        {
            trace_IndiMgr_HandleSubscribe_Outofmemory( self );
        }
        if (error)
            MI_Instance_Delete(error);
    }

    if (subscrip)
    {
        Subscription_Release(subscrip);
    }

    trace_IndiMgr_HandleSubscribe_Done(self, params->interaction, req, req->base.base.operationId, r);
    return;
}
