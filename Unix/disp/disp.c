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
#include <pal/format.h>
#include <base/messages.h>
#include <base/Strand.h>
#include <base/log.h>
#include <base/paths.h>
#include <pal/hashmap.h>
#include <base/naming.h>
#include <wql/wql.h>
#include "disp.h"
#include <omi_error/errorutil.h>

/*
**==============================================================================
*/

#define DISPENUMPARENT_STRANDAUX_ENUMDONE      0

STRAND_DEBUGNAME1( DispEnumParent, EnumDone );
STRAND_DEBUGNAME( DispEnumEntry );

/*
**==============================================================================
**
** ClassName hash implementation
**
**==============================================================================
*/

typedef struct _ClassNameBucket /* derives from HashBucket */
{
    struct _ClassNameBucket* next;
    ZChar* key;
}
ClassNameBucket;

static size_t ClassNameHash(
    const HashBucket* bucket_)
{
    /* Note: this algorithm has a poor distribution */
    ClassNameBucket* bucket = (ClassNameBucket*)bucket_;
    size_t h = 0;
    ZChar* key = bucket->key;

    while (*key)
    {
        h += 5 * *key++;
    }

    return h;
}

static int ClassNameEqual(
    const HashBucket* bucket1_,
    const HashBucket* bucket2_)
{
    ClassNameBucket* bucket1 = (ClassNameBucket*)bucket1_;
    ClassNameBucket* bucket2 = (ClassNameBucket*)bucket2_;
    return Tcscasecmp(bucket1->key, bucket2->key) == 0;
}

static void ClassNameRelease(
    HashBucket* bucket_)
{
    ClassNameBucket* bucket = (ClassNameBucket*)bucket_;

    PAL_Free(bucket->key);
    PAL_Free(bucket);
}

/*
**==============================================================================
**
** Local definitions
**
**==============================================================================
*/

typedef struct _DispEnumParent
{
    StrandMany              strand;
    Disp*                   disp;
    RequestMsg*             baseRequest;
    MI_Result               result;
    MI_Boolean              done;
}
DispEnumParent;

typedef struct _EnumEntry EnumEntry;

struct _EnumEntry
{
    StrandEntry             strand;
    const ZChar*            className;
    EnumEntry*              next;       // Links the entries that are about to be dispatched
                                        // We cannot use list on StrandMany as that one can get modify in the meantime 
                                        // as the interactions are being dinamically closed themselves
                                        // (that is why that list requires to be in the strand to use it)
};

MI_INLINE void _DispEnumParent_Delete(
    _In_ DispEnumParent* self)
{
    trace_DispDeleteInteraction(self);
    Message_Release( &self->baseRequest->base );
    StrandMany_Delete(&self->strand);
}

// interaction is already opened, we can have left the Strand or not indicated by leftStrand
static void _SendErrorResponse_Opened(
    _Inout_ InteractionOpenParams* interactionParams, 
    _In_ DispEnumParent* self,
    _In_ MI_Result r,
    MI_Boolean leftStrand
    )
{
    PostResultMsg* openResp = PostResultMsg_NewAndSerialize( &self->baseRequest->base, NULL, NULL, MI_RESULT_TYPE_MI, r);

    if( openResp )
    {
        if( leftStrand )
        {
            StrandMany_SchedulePost( &self->strand, &openResp->base );
            StrandMany_ScheduleClose( &self->strand ); 
        }
        else
        {
            Strand_Post( &self->strand.strand, &openResp->base );
            Strand_Close( &self->strand.strand ); 
            Strand_Leave( &self->strand.strand );
        }
        PostResultMsg_Release(openResp);
    }
    else
    {
        // delete the object directly
        _DispEnumParent_Delete( self );
        
        interactionParams->msg = NULL;  // Null this out since we have already sent an Ack
        interactionParams->origin= NULL;  // Null this out since we have already left origin strand
        Strand_FailOpenWithResult(interactionParams, r, PostResultMsg_NewAndSerialize);
    }
}

static void _DispEnumParent__SendLastResponse(
    _In_ DispEnumParent* interaction
    )
{
    PostResultMsg* resp;

    resp = PostResultMsg_NewAndSerialize(&interaction->baseRequest->base, NULL, NULL, MI_RESULT_TYPE_MI, interaction->result);
    if( resp )
    {
        Strand_Post( &interaction->strand.strand, &resp->base );
        Message_Release(&resp->base);
    }

    Strand_Close( &interaction->strand.strand ); 
}

static void _DispEnumParent_Transport_Post( _In_ Strand* self_, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // we dont expect any additional messages at this point
}

static void _DispEnumParent_Transport_PostControl( _In_ Strand* self, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // not used yet
}

static void _DispEnumParent_Transport_Cancel( _In_ Strand* self)
{
    // not used yet
}

static void _DispEnumParent_Finished( _In_ Strand* self_)
{
    DispEnumParent* self = (DispEnumParent*)StrandMany_FromStrand(self_);
    _DispEnumParent_Delete( self );
}

//DISPENUMPARENT_STRANDAUX_ENUMDONE
static void _DispEnumParent_EnumDone( _In_ Strand* self_)
{
    DispEnumParent* self = (DispEnumParent*)StrandMany_FromStrand(self_);

    trace_DispEnumDone(self, self->strand.numEntries, self->result );

    self->done = MI_TRUE;
    
    if( 0 == self->strand.numEntries )
    {
        _DispEnumParent__SendLastResponse( self );
    }
}

/*
    This object manages a a "Parent" enumeration on the dispatcher level.
    Enumerations in this context include also Associations and References.
    The dispatcher converts that parent enumertion coming from the client
    into several actual child enumerations that can go to the same or different providers
    for each of those child enumerations a "EnumEntry" object (see more info below) will be 
    created and attached to this Parent enumeration using the one-to-many 
    strand interface (StrandMany).

    Behavior:
    - Post and PostControl are not used yet as no secondary messages after
       initial request are issued currently
    - Cancel is also not implememented as Cancelation e2e is not implemented
    - Shutdown: 
       once all the child enumerations have been issued DISPENUMPARENT_STRANDAUX_ENUMDONE
       is scheduled on the parent, what in turn set the done flag to true and sends the last response 
       (final result) to the transport. That would happen if all the enumerations ran in the same thread 
       as by that point all of them would have completed. However if one or more enumerations
       are run in the own thread (by the provider or out-of-proc) then may not be completed
       at that point and then the sending of last response and shutdown will occur once
       the last enumeration is closed and deleted and the parent is notified on
       _DispEnumParent_Entry_Deleted (implemented below on the internal FT)

    Internal interface and unique features:
    - When a message is sent internally (from EnumEntry) it is just sent pass
       thru to the transport EXCEPT if it is a PostResultMsg as in that case the result
       is just stored internally (if it is not success) as we are only returning one single
       result to the parent interaction (managed on _DispEnumParent_Entry_Post below)
*/
static StrandFT _DispEnumParent_TransportFT = { 
    _DispEnumParent_Transport_Post, 
    _DispEnumParent_Transport_PostControl, 
    NULL, 
    _DispEnumParent_Transport_Cancel, 
    NULL,
    _DispEnumParent_Finished,
    NULL,
    _DispEnumParent_EnumDone,
    NULL,
    NULL,
    NULL,
    NULL };

static void _DispEnumEntry_Provider_PostControl( _In_ Strand* self, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // not used yet
}

static void _DispEnumEntry_Provider_Close( _In_ Strand* self )
{
    if(!self->info.thisClosedOther)
    {
        // Just close back
        Strand_Close( self );
    }
}

/*
    This object manages the interaction wich each particular provider enumeration
    that a parent provider is divided into (see more info above on _DispEnumParent_TransportFT)

    Behavior:
    - PostControl is not used yet
    - Posts are just passed pass thru (and acks are managed by StrandMany)
    - Shutdown: once the provider side closes the interaction this object closes the
       interaction back what will trigger automatically deletion of the object
*/
static StrandFT _DispEnumEntry_ProviderFT = { 
    NULL, 
    _DispEnumEntry_Provider_PostControl, 
    NULL, 
    NULL, 
    _DispEnumEntry_Provider_Close,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL };
    
static void _DispEnumParent_Entry_Deleted( _In_ StrandMany* self_ )
{
    DispEnumParent* self = (DispEnumParent*)self_;

    DEBUG_ASSERT( NULL != self );

    trace_DispEntryDeleted(self, self->strand.numEntries, self->done );

    if( self->done && 0 == self->strand.numEntries )
    {
        _DispEnumParent__SendLastResponse( self );
    }
}

static void _DispEnumParent_Entry_Post( _In_ StrandMany* self_, _In_ Message* msg)
{
    DispEnumParent* self = (DispEnumParent*)self_;

    DEBUG_ASSERT( NULL != self );
    
    trace_DispPostingMessage( self->strand.strand.info.interaction.other, self_);

    if( PostResultMsgTag == msg->tag )
    {
        PostResultMsg* rsp = (PostResultMsg*)msg;

        if( MI_RESULT_OK != rsp->result && MI_RESULT_OK == self->result )
        {
            self->result = rsp->result;
        }

        // This is not posted here
    }
    else
    {
        Strand_Post( &self->strand.strand, msg );
    }
}

// used for enums, associators, references and subcriptions
static StrandManyInternalFT _DispEnumParent_InternalFT = { 
    NULL,
    _DispEnumParent_Entry_Deleted,
    _DispEnumParent_Entry_Post, 
    NULL, 
    NULL, 
    NULL, 
    NULL,
    NULL,
    NULL,
    NULL };
        
static MI_Result _DispatchEnumerateInstancesReq(
    _In_ Disp* disp,
    _In_ EnumerateInstancesReq* request,
    _In_ const ZChar* className, 
    _In_opt_ EnumEntry* enumEntry,
    _In_opt_ InteractionOpenParams* interactionParams )
{
    const ProvRegEntry* provEntry;
    MI_Result result;
    EnumerateInstancesReq* msg;
    AgentMgr_OpenCallbackData openCallbackData;

    DEBUG_ASSERT( NULL != className );
    
    /* Attempt to find a provider for this class */
    provEntry = ProvReg_FindProviderForClass(&disp->provreg, 
        request->nameSpace, className, &result );

    if (!provEntry)
    {
        return MI_RESULT_NOT_SUPPORTED;
    }

    /* Create new request to send to provider */
    msg = EnumerateInstancesReq_New(request->base.base.operationId, request->base.base.flags);
    if( NULL == msg )
    {
        trace_DispatchEnumerateInstancesReq_OutOfMemory();
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    
    msg->base.options = request->base.options;
    AuthInfo_Copy( &msg->base.authInfo, &request->base.authInfo );
    msg->nameSpace = Batch_Tcsdup(msg->base.base.batch, request->nameSpace);
    msg->className = Batch_Tcsdup(msg->base.base.batch, className);
    msg->base.userAgent = request->base.userAgent;

    if (!msg->nameSpace || !msg->className)
    {
        goto OutOfMemory;
    }

    /* Clone the query fields (if any) */
    if (request->queryLanguage)
    {
        msg->queryLanguage = Batch_Tcsdup(msg->base.base.batch, request->queryLanguage);
        if (!msg->queryLanguage)
        {
            goto OutOfMemory;
        }
    }

    if( request->queryExpression )
    {
        msg->queryExpression = Batch_Tcsdup(msg->base.base.batch,request->queryExpression);
        if (!msg->queryExpression)
        {
            goto OutOfMemory;
        }
    }
    
    /* Save request's class name to allow provmgr pack back only base properties */
    if( request->basePropertiesOnly )
    {
        msg->requestClassName = Batch_Tcsdup(msg->base.base.batch, request->className);
        if (!msg->requestClassName)
        {
            goto OutOfMemory;
        }
    }

    openCallbackData.self = &disp->agentmgr;
    openCallbackData.proventry = provEntry;
    
    if( NULL != enumEntry )
    {
        trace_DispatchEnumDispInteraction(tcs(className));

        /* Send the request to provider manager */
        Strand_Open( &enumEntry->strand.strand, AgentMgr_OpenCallback, &openCallbackData, &msg->base.base, MI_TRUE );
    }
    else
    {
        DEBUG_ASSERT( NULL != interactionParams );
        
        // send it directly to AgentMgr
        interactionParams->callbackData = &openCallbackData;
        interactionParams->msg = &request->base.base;
        
        trace_DispatchEnumDirectly(tcs(className));
        
        AgentMgr_OpenCallback( interactionParams );
    }

    /* Release the original message */
    EnumerateInstancesReq_Release(msg);

    return MI_RESULT_OK;

OutOfMemory:
    trace_DispatchEnumerateInstancesReq_OutOfMemory();
    EnumerateInstancesReq_Release(msg);
    
    return MI_RESULT_SERVER_LIMITS_EXCEEDED;
}

// Also used for References
static MI_Boolean _DispatchAssocReq(
    _In_ Disp* disp,
    _In_ AssociationsOfReq* req,
    _In_ EnumEntry* enumEntry,
    MessageTag tag )
{
    const ProvRegEntry* entry;
    AssociationsOfReq* msg;
    const ZChar* className = enumEntry->className;
    MI_Result result;
    AgentMgr_OpenCallbackData openCallbackData;

    /* Attempt to find a provider for this class */
    entry = ProvReg_FindProviderForClass(&disp->provreg, 
        req->nameSpace, className, &result );

    if (!entry)
    {
        trace__DispatchAssocReq_OutOfMemory();
        return MI_FALSE;
    }

    /* Create new request to send to provider */
    msg = AssociationsOfReq_New(req->base.base.operationId, req->base.base.flags, tag);
    msg->base.options = req->base.options;
    AuthInfo_Copy( &msg->base.authInfo, &req->base.authInfo );
    /* original request will be kept for the request duration, so perform shallow copy only */
    msg->nameSpace = req->nameSpace;
    msg->assocClass = req->assocClass;
    msg->resultClass = req->resultClass;
    msg->role = req->role;
    msg->resultRole = req->resultRole;
    msg->instance = req->instance;
    msg->packedInstancePtr = req->packedInstancePtr;
    msg->packedInstanceSize = req->packedInstanceSize;
    msg->base.userAgent = req->base.userAgent;

    msg->className = Batch_Tcsdup(msg->base.base.batch, className);

    trace_DispatchAssoc(tcs(className));
     
    /* Send the request to provider manager */
    openCallbackData.self = &disp->agentmgr;
    openCallbackData.proventry = entry;
    Strand_Open( &enumEntry->strand.strand, AgentMgr_OpenCallback, &openCallbackData, &msg->base.base, MI_TRUE );

    /* Release the original message */
    AssociationsOfReq_Release(msg);

    return MI_TRUE;
}

DispEnumParent* _DispEnumParent_New(
    _In_ Disp*                  disp,
    _In_ InteractionOpenParams* interactionParams )
{
    DispEnumParent* self;

    self = (DispEnumParent*)StrandMany_New(
                STRAND_DEBUG( DispEnumParent )
                &_DispEnumParent_TransportFT,
                &_DispEnumParent_InternalFT, 
                sizeof( DispEnumParent ),
                STRAND_FLAG_ENTERSTRAND,
                interactionParams,
                1,
                NULL,
                NULL,
                NULL);

    if(self)
    {
        RequestMsg* req = (RequestMsg*)interactionParams->msg;
        DEBUG_ASSERT( NULL != req );
        
        Message_AddRef( &req->base );
        self->baseRequest = req;

        self->disp = disp;
        self->result = MI_RESULT_OK;

        // As soon as we accept the open we can send the open msg ack
        Strand_Ack( &self->strand.strand );
    }
    
    return self;
}

static MI_Result _HandleGetInstanceReq(
    _In_ Disp* self,
    _Inout_ InteractionOpenParams* interactionParams, 
    _In_ GetInstanceReq* req)
{
    MI_Result r;
    const ProvRegEntry* reg;

    /* Validate input parameters */
    if (!req->instanceName || !req->nameSpace)
        return MI_RESULT_INVALID_PARAMETER;

    // Find a provider for this class.
    reg = ProvReg_FindProviderForClass(&self->provreg, req->nameSpace, 
        req->instanceName->classDecl->name, &r );

    if (!reg)
    {
        trace_NoProviderForClass(
            req->nameSpace,
            req->instanceName->classDecl->name);
        goto sendErrorBack;
    }

    // Send the request to provider manager.
    r = AgentMgr_HandleRequest(&self->agentmgr, interactionParams, reg);

    if (r != MI_RESULT_OK)
    {
        trace_AgentMgrHandleRequestForNS(
            req->nameSpace);
        goto sendErrorBack;
    }

    return MI_RESULT_OK;

sendErrorBack:
    // Just abort creating any interaction at all
    return r;
}

static MI_Result _HandleGetClassReq(
    _In_ Disp* self,
    _Inout_ InteractionOpenParams* interactionParams,     
    _In_ GetClassReq* req)
{
    MI_Result r;
    const ProvRegEntry* reg;
    ProvRegEntry freg;
    ProvRegPosition pos;

    /* Validate input parameters */
    if (!req->className || !req->nameSpace)
        return MI_RESULT_INVALID_PARAMETER;

    // client must specify classname for GetClass request
    if(Tcscmp(req->className, PAL_T("*")) == 0)
        return MI_RESULT_INVALID_CLASS;

    memset( &freg, 0, sizeof(freg) );

    // Find a provider for this class.
    reg = ProvReg_FindProviderForClass(&self->provreg, req->nameSpace, 
        req->className, &r );

    if (!reg)
    {
        if(MI_RESULT_INVALID_CLASS == r)
        {
            /* Checking if the requested class is a base class of an implemented class */
            r = ProvReg_BeginClasses(&self->provreg, req->nameSpace, 
                    req->className, MI_TRUE, &pos, MI_FALSE);

            if(MI_RESULT_INVALID_CLASS == r)
            {
                /* Checking if the requested class is an extraclass (Class without key property or Class with key property but not part of any 
                    class heirarchy of an implemented class.)
                    Class with valid providerFT is called as an implemented class */

                /* In extra classes inheritance tree a namespace node is created only if there is at least one extra class in the namespace.
                    So namespace node need not exist in extra classes inheritance tree even for valid namespace */
                r = ProvReg_BeginClasses(&self->provreg, req->nameSpace, 
                        req->className, MI_TRUE, &pos, MI_TRUE);

                if(MI_RESULT_INVALID_NAMESPACE == r)
                    r = MI_RESULT_INVALID_CLASS;
            }
            if (MI_RESULT_OK == r)
            {
                DEBUG_ASSERT(pos.start != NULL);
                MapRegPositionValuesToRegEntry(&freg, &pos);
                freg.nameSpace = req->nameSpace;
                freg.nameSpaceHash = Hash(req->nameSpace);
            }
        }
        
        if (MI_RESULT_OK != r)
        {
            trace_NoProviderForClass(
                req->nameSpace,
                req->className);
            goto sendErrorBack;
        }
    }
    else
    {
        freg = *reg;
    }

    // Send the request to provider manager.
    r = AgentMgr_HandleRequest(&self->agentmgr, interactionParams, &freg);

    if (r != MI_RESULT_OK)
    {
        trace_AgentMgrHandleRequestForNS(
            req->nameSpace);
        goto sendErrorBack;
    }

    return MI_RESULT_OK;

sendErrorBack:
    // Just abort creating any interaction at all
    return r;
}

static MI_Result _HandleCreateInstanceReq(
    _In_ Disp* self,
    _Inout_ InteractionOpenParams* interactionParams, 
    _In_ CreateInstanceReq* req)
{
    MI_Result r;
    const ProvRegEntry* reg;

    /* Validate input parameters */
    if (!req->instance || !req->nameSpace)
        return MI_RESULT_INVALID_PARAMETER;

    // Find a provider for this class.
    reg = ProvReg_FindProviderForClass(&self->provreg, req->nameSpace, 
        req->instance->classDecl->name, &r );

    if (!reg)
    {
        trace_NoProviderForClass(
            req->nameSpace, 
            req->instance->classDecl->name);
        goto sendErrorBack;
    }

    // Send the request to provider manager.
    r = AgentMgr_HandleRequest(&self->agentmgr, interactionParams, reg);

    if (r != MI_RESULT_OK)
    {
        trace_AgentMgrHandleRequestForNS(
            req->nameSpace);
        goto sendErrorBack;
    }

    return MI_RESULT_OK;

sendErrorBack:
    // Just abort creating any interaction at all
    return r;
}

static MI_Result _HandleModifyInstanceReq(
    _In_ Disp* self,
    _Inout_ InteractionOpenParams* interactionParams, 
    _In_ ModifyInstanceReq* req)
{
    MI_Result r;
    const ProvRegEntry* reg;

    /* Validate input parameters */
    if (!req->instance || !req->nameSpace)
        return MI_RESULT_INVALID_PARAMETER;

    // Find a provider for this class.
    reg = ProvReg_FindProviderForClass(&self->provreg, req->nameSpace, 
        req->instance->classDecl->name, &r );

    if (!reg)
    {
        trace_NoProviderForClass(
            req->nameSpace, 
            req->instance->classDecl->name);
        goto sendErrorBack;
    }

    // Send the request to provider manager.
    r = AgentMgr_HandleRequest(&self->agentmgr, interactionParams, reg);

    if (r != MI_RESULT_OK)
    {
        trace_AgentMgrHandleRequestForNS(
            req->nameSpace);
        goto sendErrorBack;
    }

    return MI_RESULT_OK;

sendErrorBack:
    // Just abort creating any interaction at all
    return r;
}

static MI_Result _HandleDeleteInstanceReq(
    _In_ Disp* self,
    _Inout_ InteractionOpenParams* interactionParams, 
    _In_ DeleteInstanceReq* req)
{
    MI_Result r;
    const ProvRegEntry* reg;

    /* Validate input parameters */
    if (!req->instanceName || !req->nameSpace)
        return MI_RESULT_INVALID_PARAMETER;

    // Find a provider for this class.
    reg = ProvReg_FindProviderForClass(&self->provreg, req->nameSpace, 
        req->instanceName->classDecl->name, &r);

    if (!reg)
    {
        trace_NoProviderForClass(
            req->nameSpace, 
            req->instanceName->classDecl->name);
        goto sendErrorBack;
    }

    // Send the request to provider manager.
    r = AgentMgr_HandleRequest(&self->agentmgr, interactionParams, reg);

    if (r != MI_RESULT_OK)
    {
        trace_AgentMgrHandleRequestForNS(
            req->nameSpace);
        goto sendErrorBack;
    }

    return MI_RESULT_OK;

sendErrorBack:
    // Just abort creating any interaction at all
    return r;
}

static MI_Result _HandleInvokeReq(
    _In_ Disp* self,
    _Inout_ InteractionOpenParams* interactionParams, 
    _In_ InvokeReq* req)
{
    MI_Result r;
    const ProvRegEntry* reg;
    MI_ConstString cn = 0;

    /* Validate input parameters */
    if (!req->nameSpace)
        return MI_RESULT_INVALID_PARAMETER;

    if (req->className)
        cn = req->className;
    else if (req->instance)
        cn = req->instance->classDecl->name;

    if (!cn)
    {
        r = MI_RESULT_INVALID_CLASS;
        trace_ClassNameIsExpectedForInvoke();
        goto sendErrorBack;
    }


    // Find a provider for this class.
    reg = ProvReg_FindProviderForClass(&self->provreg, req->nameSpace, cn, &r);

    if (!reg)
    {
        trace_FoundNoProvider(
            cn);
        goto sendErrorBack;
    }

    // Send the request to provider manager.
    r = AgentMgr_HandleRequest(&self->agentmgr, interactionParams, reg);

    if (r != MI_RESULT_OK)
    {
        trace_AgentMgrHandleRequestForNS(
            req->nameSpace);
        goto sendErrorBack;
    }

    return MI_RESULT_OK;

sendErrorBack:
    // Just abort creating any interaction at all
    return r;
}

static MI_Result _HandleEnumerateInstancesReq(
    _In_ Disp* self,
    _Inout_ InteractionOpenParams* interactionParams, 
    _In_ EnumerateInstancesReq* req)
{
    MI_Result r = MI_RESULT_FAILED;
    MI_Boolean sentOk = MI_FALSE;
    WQL_Dialect dialect;
    DispEnumParent* enumInteraction;
    EnumEntry* enumEntry;
    EnumEntry* enumEntryHead = NULL;

    /* Validate input parameters */
    if (!req->nameSpace)
        return MI_RESULT_INVALID_PARAMETER;

    /* Precompile the query */
    if (req->queryLanguage || req->queryExpression)
    {
        /* Fail if either query language or expression is missing */
        if (!req->queryLanguage || !req->queryExpression)
        {
            trace_QueryLanguageOrExpressionMissing();
            return MI_RESULT_INVALID_QUERY;
        }

        /* Reject non-WQL queries */
        if (Tcscasecmp(req->queryLanguage, MI_QUERY_DIALECT_WQL) == 0)
        {
            dialect = WQL_DIALECT_WQL;
        }
        else if (Tcscasecmp(req->queryLanguage, MI_QUERY_DIALECT_CQL) == 0)
        {
            dialect = WQL_DIALECT_CQL;
        }
        else
        {
            trace_UnsupportedQueryLanguage(tcs(req->queryLanguage));
            return MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED;
        }

        /* Compile the query */
        {
            req->wql = WQL_Parse(req->queryExpression, req->base.base.batch,
                dialect);

            if (!req->wql)
            {
                trace_InvalidQueryExpression(tcs(req->queryExpression));
                return MI_RESULT_INVALID_QUERY;
            }
        }

        /* WQL queries from WinRM pass '*' as the class name */

        if (!req->className || (Tcscmp(req->className, PAL_T("*")) == 0))
        {
            req->className = req->wql->className;
        }

        /* Verify that the query classname matches the enumeration classname */
        if (Tcscmp(req->wql->className, req->className) != 0)
        {
            trace_QueryEnumClassnameMismatch(
                tcs(req->wql->className), tcs(req->className));
            return MI_RESULT_INVALID_QUERY;
        }
    }
    else if (!req->className)
    {
        trace_EnumHasNoClassname();
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (req->deepInheritance)
    {
        ProvRegPosition pos;
        EnumEntry* enumEntryPrev;
        
        /* create the interaction that will keep track of results from providers */
        enumInteraction = _DispEnumParent_New(
                            self,
                            interactionParams);
        if (!enumInteraction)
        {
            trace_Disp_ErrorInteractionAlloc();
            return MI_RESULT_FAILED;
        }

        /* Send to direct name */
        /* Start by sending to direct name */
        enumEntry = (EnumEntry*)StrandEntry_New( STRAND_DEBUG( DispEnumEntry ) 
                                                    &enumInteraction->strand, 
                                                    &_DispEnumEntry_ProviderFT, 
                                                    sizeof(EnumEntry), 
                                                    STRAND_FLAG_ENTERSTRAND, 
                                                    NULL);
        if( NULL == enumEntry )
        {
            trace_Disp_ErrorEnumEntryAlloc();
            goto sendErrorBack_Opened;
        }
        r = StrandMany_AddEntry( &enumEntry->strand );
        if( MI_RESULT_OK != r )
        {
            StrandEntry_DeleteNoAdded( &enumEntry->strand );
            goto sendErrorBack_Opened;
        }
        enumEntry->className = req->className;
        enumEntryHead = enumEntry;
        enumEntryPrev = enumEntry;

        /* Begin enumeration of classes for this request */
        {
            r = ProvReg_BeginClasses(&self->provreg, req->nameSpace, 
                req->className, MI_TRUE, &pos, MI_FALSE);

            if (MI_RESULT_OK != r)
            {
                {
                    /* Checking if the class is in extra classes to return appropriate error */
                    MI_Result result;
                    result = ProvReg_BeginClasses(&self->provreg, req->nameSpace, 
                                    req->className, MI_TRUE, &pos, MI_TRUE);
                    if(MI_RESULT_OK == result)
                    {
                        ProvReg_EndClasses(&pos);
                        r = MI_RESULT_NOT_SUPPORTED;
                        goto sendErrorBack_Opened;
                    }
                }
                trace_ProvReg_BeginClasses_Failed( 
                    r, tcs(Result_ToString(r)));
            
                trace_DispEnum_UnknownClass(
                    tcs(req->nameSpace), tcs(req->className));

                /* send error back to caller */
                goto sendErrorBack_Opened;
            }
        }

        /* While more classes */
        for (;;)
        {
            const ZChar* derived = NULL;
            MI_Boolean done;

            r = ProvReg_NextClass(&pos, &derived, &done);

            if (done)
                break;

            if (MI_RESULT_OK != r)
            {
                trace_ProvReg_NextClass_Failed(
                    r, tcs(Result_ToString(r)));
        
                trace_DispEnum_UnknownClass(
                    tcs(req->nameSpace), tcs(req->className));
        
                /* send error back to caller */
                goto sendErrorBack_Opened;
            }

            enumEntry = (EnumEntry*)StrandEntry_New( STRAND_DEBUG( DispEnumEntry ) 
                                                        &enumInteraction->strand, 
                                                        &_DispEnumEntry_ProviderFT, 
                                                        sizeof(EnumEntry), 
                                                        STRAND_FLAG_ENTERSTRAND, 
                                                        NULL);
            if( NULL == enumEntry )
            {
                trace_Disp_ErrorEnumEntryAlloc();
                goto sendErrorBack_Opened;
            }
            
            r = StrandMany_AddEntry( &enumEntry->strand );
            if( MI_RESULT_OK != r )
            {
                trace_Disp_ErrorAddEntry();
                StrandEntry_DeleteNoAdded( &enumEntry->strand );
                goto sendErrorBack_Opened;
            }

            // Use the original message batch, it will not be deleted until enumInteraction (who holds a ref to the message) is deleted
            enumEntry->className = Batch_Tcsdup(req->base.base.batch, derived);
            enumEntry->next = NULL;
            enumEntryPrev->next = enumEntry;
            enumEntryPrev = enumEntry;
        }

        /* Finalize enumeration */
        {
            r = ProvReg_EndClasses(&pos);

            if (MI_RESULT_OK != r)
            {
                trace_ProvReg_EndClasses_Failed(
                    r, tcs(Result_ToString(r)));
                /* send error back to caller */
                goto sendErrorBack_Opened;
            }
        }

        Strand_Leave( &enumInteraction->strand.strand );

        // Now go thru the added entries and dispatch the interactions
        enumEntry = enumEntryHead;
        while( NULL != enumEntry )
        {
            // Move to the next one before the object can be deleted by itself or by delete below
            enumEntryPrev = enumEntry;
            enumEntry = enumEntry->next;
            if( _DispatchEnumerateInstancesReq(self, req, enumEntryPrev->className, enumEntryPrev, NULL) == MI_RESULT_OK)
            {
                sentOk = MI_TRUE;
            }
            else
            {
                StrandEntry_Delete( &enumEntryPrev->strand );
            }
        }
        enumEntryHead = NULL;
            
        /* Fail if no provider was found for request */
        if (!sentOk)
        {        
            trace_FoundNoProvider(
                req->className);
            r = MI_RESULT_NOT_SUPPORTED;
            goto sendErrorBack_Opened;
        }

        StrandMany_ScheduleAux(&enumInteraction->strand,DISPENUMPARENT_STRANDAUX_ENUMDONE);
    } /* if deep*/
    else
    {
        /* Checking to see if the requested className is valid */
        ProvRegPosition pos;
        r = ProvReg_BeginClasses(&self->provreg, req->nameSpace, 
            req->className, MI_TRUE, &pos, MI_FALSE);

        if (MI_RESULT_OK != r)
        {
            /* Checking if the class is in extra classes to return appropriate error */
            MI_Result result;
            result = ProvReg_BeginClasses(&self->provreg, req->nameSpace, 
                            req->className, MI_TRUE, &pos, MI_TRUE);
            if(MI_RESULT_OK == result)
            {
                r = MI_RESULT_NOT_SUPPORTED;
                ProvReg_EndClasses(&pos);
            }
            return r;
        }
        else
        {
            ProvReg_EndClasses(&pos);
        }

        // no need to create new interaction
        return _DispatchEnumerateInstancesReq(self, req, req->className, NULL, interactionParams);
    }

    return MI_RESULT_OK;

sendErrorBack_Opened:
    // Delete not dispatched entries 
    enumEntry = enumEntryHead;
    while( NULL != enumEntry )
    {
        StrandEntry_Delete( &enumEntry->strand );
        enumEntry = enumEntry->next;
    }
    
    // send error back to caller 
    _SendErrorResponse_Opened(interactionParams, enumInteraction, r, MI_FALSE ); 
    return MI_RESULT_OK;
}

static MI_Result _HandleAssociatorsOfReq(
    _In_ Disp* self,
    _Inout_ InteractionOpenParams* interactionParams, 
    _In_ AssociationsOfReq* req)
{
    int res;
    MI_Result r = MI_RESULT_FAILED;
    MI_ConstString cn = 0;
    ProvRegAssocPosition pos;
    MI_Boolean sentOk = MI_FALSE;
    HashMap classNames;
    DispEnumParent* enumInteraction;
    EnumEntry* enumEntry;
    EnumEntry* enumEntryHead = NULL;
    EnumEntry* enumEntryPrev = NULL;

    /* Create a hash table of class names */

    res = HashMap_Init(
        &classNames, 
        64, 
        ClassNameHash, 
        ClassNameEqual, 
        ClassNameRelease);

    if (res != 0)
        return MI_RESULT_FAILED;

    /* Validate input parameters */
    if (!req->instance || !req->nameSpace)
        return MI_RESULT_INVALID_PARAMETER;

    /* create the interaction that will keep track of results from providers */
    enumInteraction = _DispEnumParent_New(
                        self,
                        interactionParams);
    if (!enumInteraction)
    {
        trace_Disp_ErrorInteractionAlloc();
        HashMap_Destroy(&classNames);
        return MI_RESULT_FAILED;
    }
    
    r = ProvReg_BeginAssocClasses(&self->provreg, req->nameSpace, 
        req->instance->classDecl->name,
        req->assocClass, req->resultClass, &pos);

    if (MI_RESULT_OK != r)
    {
        trace_ProvReg_BeginAssocClasses_Failed(r, tcs(Result_ToString(r)));

        /* send error back to caller */
        goto sendErrorBack_Opened;
    }

    /* ATTN: there is a bug in the provider registration tree causing
     * the association provider to be called twice. To avoid this for now,
     * we maintain a hash table of already dispatched classes.
     */

    /* While more classes */
    for (;;)
    {
        MI_Boolean done;
        r = ProvReg_NextAssocClass(&pos, &cn, &done);

        if (done)
            break;

        if (MI_RESULT_OK != r)
        {
            trace_ProvReg_NextAssocClass_Failed(r, tcs(Result_ToString(r)));
            
            /* send error back to caller */
            goto sendErrorBack_Opened;
        }

        /* Check whether this class has been dispatched */
        {
            ClassNameBucket bucket;
            bucket.key = (ZChar*)cn;

            if (!HashMap_Find(&classNames, (const HashBucket*)&bucket))
            {
                enumEntry = (EnumEntry*)StrandEntry_New( STRAND_DEBUG( DispEnumEntry ) 
                                                            &enumInteraction->strand, 
                                                            &_DispEnumEntry_ProviderFT, 
                                                            sizeof(EnumEntry), 
                                                            STRAND_FLAG_ENTERSTRAND, 
                                                            NULL);
                if( NULL == enumEntry )
                {
                    trace_Disp_ErrorEnumEntryAlloc();
                    goto sendErrorBack_Opened;
                }
                
                r = StrandMany_AddEntry( &enumEntry->strand );
                if( MI_RESULT_OK != r )
                {
                    trace_Disp_ErrorAddEntry();
                    StrandEntry_DeleteNoAdded( &enumEntry->strand );
                    goto sendErrorBack_Opened;
                }
                
                // Use the original message batch, it will not be deleted until enumInteraction (who holds a ref to the message) is deleted
                enumEntry->className = Batch_Tcsdup(req->base.base.batch, cn);
                enumEntry->next = NULL;
                if( NULL == enumEntryHead )
                {
                    enumEntryHead = enumEntry;
                }
                else
                {
                    enumEntryPrev->next = enumEntry;
                }
                enumEntryPrev = enumEntry;

                {
                    ClassNameBucket* bucket = (ClassNameBucket*)PAL_Calloc(
                        1, sizeof(ClassNameBucket));

                    if (!bucket)
                    {
                        r = MI_RESULT_FAILED;
                        goto sendErrorBack_Opened;
                    }

                    bucket->key = PAL_Tcsdup(cn);

                    if (HashMap_Insert(&classNames, (HashBucket*)bucket) != 0)
                    {
                        r = MI_RESULT_FAILED;
                        goto sendErrorBack_Opened;
                    }
                }
            }
        }
    }

    /* Finalize enumeration */
    {
        r = ProvReg_EndAssocClasses(&pos);

        if (MI_RESULT_OK != r)
        {
            trace_ProvReg_EndAssocClasses_Failed(r, tcs(Result_ToString(r)));
            
            /* send error back to caller */
            goto sendErrorBack_Opened;
        }
    }

    Strand_Leave( &enumInteraction->strand.strand );
    
    // Now go thru the added entries and dispatch the interactions
    enumEntry = enumEntryHead;
    while( NULL != enumEntry )
    {
        // Move to the next one before the object can be deleted by itself or by delete below
        enumEntryPrev = enumEntry;
        enumEntry = enumEntry->next;
        if (_DispatchAssocReq(self, req, enumEntryPrev, AssociatorsOfReqTag))
        {
            sentOk = MI_TRUE;
        }
        else
        {
            StrandEntry_Delete( &enumEntryPrev->strand );
        }
    }
    enumEntryHead = NULL;
        
    HashMap_Destroy(&classNames);
        
    /* Fail if no provider was found for request */
    if (!sentOk)
    {
        trace_FoundNoProvider(
            tcs(req->instance->classDecl->name));
        _SendErrorResponse_Opened(interactionParams, enumInteraction, MI_RESULT_NOT_SUPPORTED, MI_TRUE );
        return MI_RESULT_OK;
    }

    StrandMany_ScheduleAux(&enumInteraction->strand,DISPENUMPARENT_STRANDAUX_ENUMDONE);
    return MI_RESULT_OK;

sendErrorBack_Opened:
    HashMap_Destroy(&classNames);
    // Delete not dispatched entries 
    enumEntry = enumEntryHead;
    while( NULL != enumEntry )
    {
        StrandEntry_Delete( &enumEntry->strand );
        enumEntry = enumEntry->next;
    }
    
    // send error back to caller 
    _SendErrorResponse_Opened(interactionParams, enumInteraction, r, MI_FALSE );
    return MI_RESULT_OK;
}

static MI_Result _HandleReferencesOfReq(
    _In_ Disp* self,
    _Inout_ InteractionOpenParams* interactionParams, 
    _In_ AssociationsOfReq* req)
{
    MI_Result r = MI_RESULT_FAILED;
    MI_ConstString cn = 0;
    ProvRegAssocPosition pos;
    MI_Boolean sentOk = MI_FALSE;
    DispEnumParent* enumInteraction;
    EnumEntry* enumEntry;
    EnumEntry* enumEntryHead = NULL;
    EnumEntry* enumEntryPrev = NULL;

    /* Validate input parameters */
    if (!req->instance || !req->nameSpace)
        return MI_RESULT_INVALID_PARAMETER;

    /* create the interaction that will keep track of results from providers */
    enumInteraction = _DispEnumParent_New(
                            self,
                            interactionParams);
    if (!enumInteraction)
    {
        trace_Disp_ErrorInteractionAlloc();
        return MI_RESULT_FAILED;
    }

    /* resultClass parameter of ReferencesOf operation contains association class name.
      Here using req->resultClass for passing assocClassName to ProvReg_BeginAssocClasses function */
    r = ProvReg_BeginAssocClasses(&self->provreg, req->nameSpace, 
        req->instance->classDecl->name,
        req->resultClass, 0, &pos);

    if (MI_RESULT_OK != r)
    {
        trace_ProvReg_BeginAssocClasses_Failed(r, tcs(Result_ToString(r)));

        /* send error back to caller */
        goto sendErrorBack_Opened;
    }

    /* While more classes */
    for (;;)
    {
        MI_Boolean done;
        r = ProvReg_NextAssocClass(&pos, &cn, &done);

        if (done)
            break;

        if (MI_RESULT_OK != r)
        {
            trace_ProvReg_NextAssocClass_Failed(r, tcs(Result_ToString(r)));
            
            /* send error back to caller */
            goto sendErrorBack_Opened;
        }

        enumEntry = (EnumEntry*)StrandEntry_New( STRAND_DEBUG( DispEnumEntry ) 
                                                    &enumInteraction->strand, 
                                                    &_DispEnumEntry_ProviderFT, 
                                                    sizeof(EnumEntry), 
                                                    STRAND_FLAG_ENTERSTRAND, 
                                                    NULL);
        if( NULL == enumEntry )
        {
            trace_Disp_ErrorEnumEntryAlloc();
            goto sendErrorBack_Opened;
        }
        
        r = StrandMany_AddEntry( &enumEntry->strand );
        if( MI_RESULT_OK != r )
        {
            trace_Disp_ErrorAddEntry();
            StrandEntry_DeleteNoAdded( &enumEntry->strand );
            goto sendErrorBack_Opened;
        }
        
        // Use the original message batch, it will not be deleted until enumInteraction (who holds a ref to the message) is deleted
        enumEntry->className = Batch_Tcsdup(req->base.base.batch, cn);
        enumEntry->next = NULL;
        if( NULL == enumEntryHead )
        {
            enumEntryHead = enumEntry;
        }
        else
        {
            enumEntryPrev->next = enumEntry;
        }
        enumEntryPrev = enumEntry;
    }

    /* Finalize enumeration */
    {
        r = ProvReg_EndAssocClasses(&pos);

        if (MI_RESULT_OK != r)
        {
            trace_ProvReg_EndAssocClasses_Failed(r, tcs(Result_ToString(r)));
            
            /* send error back to caller */
            goto sendErrorBack_Opened;
        }
    }

    Strand_Leave( &enumInteraction->strand.strand );
    
    // Now go thru the added entries and dispatch the interactions
    enumEntry = enumEntryHead;
    while( NULL != enumEntry )
    {
        // Move to the next one before the object can be deleted by itself or by delete below
        enumEntryPrev = enumEntry;
        enumEntry = enumEntry->next;
        if (_DispatchAssocReq(self, req, enumEntryPrev, ReferencesOfReqTag))
        {
            sentOk = MI_TRUE;
        }
        else
        {
            StrandEntry_Delete( &enumEntryPrev->strand );
        }
    }
    enumEntryHead = NULL;
        
    /* Fail if no provider was found for request */
    if (!sentOk)
    {
        trace_FoundNoProvider(
            tcs(req->instance->classDecl->name));
        _SendErrorResponse_Opened(interactionParams, enumInteraction, MI_RESULT_NOT_SUPPORTED, MI_TRUE );
        return MI_RESULT_OK;
    }

    StrandMany_ScheduleAux(&enumInteraction->strand,DISPENUMPARENT_STRANDAUX_ENUMDONE);
    return MI_RESULT_OK;

sendErrorBack_Opened:
    // Delete not dispatched entries 
    enumEntry = enumEntryHead;
    while( NULL != enumEntry )
    {
        StrandEntry_Delete( &enumEntry->strand );
        enumEntry = enumEntry->next;
    }
    
    // send error back to caller 
    _SendErrorResponse_Opened(interactionParams, enumInteraction, r, FALSE );
    return MI_RESULT_OK;
}

#ifndef DISABLE_INDICATION
static MI_Result _HandleSubscribeReq(
    _In_ Disp* self,
    _Inout_ InteractionOpenParams* params )
{
    params->callbackData = self->indmgr;
    IndiMgr_HandleSubscribeReq(params);
    return MI_RESULT_OK;
}
#endif /* ifndef DISABLE_INDICATION */

/*
**==============================================================================
**
** Public definitions
**
**==============================================================================
*/

MI_Result Disp_Init(Disp* self, Selector* selector)
{
    /* Check parameters */
    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

    memset(self, 0, sizeof(Disp));

#if 0
    /* Initialize the provider registry */
    MI_RETURN_ERR(ProvReg_Init(&self->provreg, OMI_GetPath(ID_REGISTERFILE)));
#else
    MI_RETURN_ERR(ProvReg_Init2(&self->provreg));
#endif

    /* Initialize the provider manager */
    MI_RETURN_ERR(AgentMgr_Init(&self->agentmgr, selector));

#ifndef DISABLE_INDICATION
    /* Initialize indication manager */
    self->indmgr = IndiMgr_NewFromDisp(self);
    if (NULL == self->indmgr)
        MI_RETURN_ERR(MI_RESULT_FAILED);
#endif /* ifndef DISABLE_INDICATION */

    return MI_RESULT_OK;
}

MI_Result Disp_Destroy(Disp* self)
{
    MI_RETURN_ERR(AgentMgr_Destroy(&self->agentmgr));
    ProvReg_Destroy(&self->provreg);

#ifndef DISABLE_INDICATION
    /* Shutdown indication manager */
    IndiMgr_Shutdown(self->indmgr);
#endif /* ifndef DISABLE_INDICATION */

    /*ATTN! remove indication contexts! */
    return MI_RESULT_OK;
}

MI_Result Disp_HandleInteractionRequest(
    _In_ Disp* self,
    _Inout_ InteractionOpenParams* params )
{
    Message* msg = params->msg;
    
    trace_DispHandleInteractionRequest(self, 
        params->interaction, 
        msg,
        msg->tag,
        MessageName(msg->tag),
        msg->operationId);

    DEBUG_ASSERT( NULL != self );
    DEBUG_ASSERT( NULL != params );
    DEBUG_ASSERT( NULL != params->interaction );
    DEBUG_ASSERT( NULL != params->msg );

    switch (msg->tag)
    {
        case GetInstanceReqTag:
        {
            GetInstanceReq* req = (GetInstanceReq*)msg;
            return _HandleGetInstanceReq(self, params, req);
        }

        case GetClassReqTag:
        {
            GetClassReq* req = (GetClassReq*)msg;
            return _HandleGetClassReq(self, params, req);
        }


        case CreateInstanceReqTag:
        {
            CreateInstanceReq* req = (CreateInstanceReq*)msg;
            return _HandleCreateInstanceReq(self, params, req);
        }

        case ModifyInstanceReqTag:
        {
            ModifyInstanceReq* req = (ModifyInstanceReq*)msg;
            return _HandleModifyInstanceReq(self, params, req);
        }

        case DeleteInstanceReqTag:
        {
            DeleteInstanceReq* req = (DeleteInstanceReq*)msg;
            return _HandleDeleteInstanceReq(self, params, req);
        }

        case InvokeReqTag:
        {
            InvokeReq* req = (InvokeReq*)msg;
            return _HandleInvokeReq(self, params, req);
        }

        case EnumerateInstancesReqTag:
        {
            EnumerateInstancesReq* req = (EnumerateInstancesReq*)msg;
            return _HandleEnumerateInstancesReq(self, params, req);
        }

        case AssociatorsOfReqTag:
        {
            AssociationsOfReq* req = (AssociationsOfReq*)msg;
            return _HandleAssociatorsOfReq(self, params, req);
        }

        case ReferencesOfReqTag:
        {
            AssociationsOfReq* req = (AssociationsOfReq*)msg;
            return _HandleReferencesOfReq(self, params, req);
        }

#ifndef DISABLE_INDICATION

        case SubscribeReqTag:
        {
            return _HandleSubscribeReq(self, params);
        }

#endif /* ifndef DISABLE_INDICATION */

        default:
        {
            /* Unsupported mesage type */
            trace_DispUnsupportedMessage( self, 
                params->interaction, 
                msg,
                msg->tag,
                MessageName(msg->tag),
                msg->operationId );
            return MI_RESULT_NOT_SUPPORTED;
        }
    }
}
