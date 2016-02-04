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

#include <assert.h>
#include <ctype.h>
#include "wsman.h"
#include "wsbuf.h"
#include "wsmanparser.h"
#include <pal/sleep.h>
#include <xml/xml.h>
#include <base/log.h>
#include <base/result.h>
#include <pal/strings.h>
#include <base/user.h>
#include <base/memman.h>
#include <pal/format.h>
#include <base/Strand.h>
#include <base/base.h>
#include <base/list.h>
#include <pal/lock.h>
#include <indication/common/indicommon.h>
#include <pal/cpu.h>

#if defined(CONFIG_USE_WCHAR)
# define HASHSTR_CHAR wchar_t
# define HASHSTR_T(scs) L##scs
#endif

#include "wstags.h"

#define CR ZT("\n")

#define TRACE_GOTO_FAILED

#if defined(TRACE_GOTO_FAILED)
# define GOTO_FAILED \
    for (;;) \
    { \
        trace_Wsman_GotoFailed(__FILE__, __LINE__); \
        goto failed; \
    }
#else
# define GOTO_FAILED goto failed
#endif

//-----------------------------------------------------------------------

#define WSMANCONNECTION_STRANDAUX_PROCESSREQUEST                0

STRAND_DEBUGNAME1( WsmanConnection, ProcessRequest );

#define ENUMERATIONCONTEXT_STRANDAUX_PULLATTACHED               0
#define ENUMERATIONCONTEXT_STRANDAUX_UNSUBSCRIBEATTACHED        1
#define ENUMERATIONCONTEXT_STRANDAUX_CONNECTION_DATA_TIMEOUT    2

STRAND_DEBUGNAME2( WsmanEnumerationContext, PullAttached, UnsubscribeAttached );

/*
**==============================================================================
**
** Local definitions:
**
**==============================================================================
*/
#define WSMAN_MAX_ENVELOPE_SIZE MAX_ENVELOPE_SIZE

#define MAX_WSMAN_BUFFER_SIZE 2*1024*1024  // 2 MB
#define MAX_WSMAN_COLLECTION_SIZE 2*1024 // upto 2K instances

const MI_Uint64 WSMAN_TIMEOUT_DEFAULT = 60 * 1000 * 1000; // 60 Seconds in microseconds

#define TYPICAL_ENUM_RESPONSE_ENVELOPE \
    "<SOAP-ENV:Envelope \n" \
    "xmlns:SOAP-ENV=\n" \
    "\"http://www.w3.org/2003/05/soap-envelope\" \n" \
    "xmlns:wsa=\n" \
    "\"http://schemas.xmlsoap.org/ws/2004/08/addressing\" \n" \
    "xmlns:wsen=\n" \
    "\"http://schemas.xmlsoap.org/ws/2004/09/enumeration\" \n" \
    "xmlns:xsi=\n" \
    "\"http://www.w3.org/2001/XMLSchema-instance\" \n" \
    "xmlns:wsmb=\n" \
    "\"http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd\" \n" \
    "xmlns:wsman=\n" \
    "\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\" \n" \
    "xmlns:wxf=\n" \
    "\"http://schemas.xmlsoap.org/ws/2004/09/transfer\" \n" \
    "xmlns:cim=\n" \
    "\"http://schemas.dmtf.org/wbem/wscim/1/common\" \n" \
    "xmlns:wsmid=\n" \
    "\"http://schemas.dmtf.org/wbem/wsman/identity/1/wsmanidentity.xsd\">\n" \
    "<SOAP-ENV:Header>\n" \
    "<wsa:To>\n" \
    "http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous\n" \
    "</wsa:To>\n" \
    "<wsa:Action>\n" \
    "http://schemas.xmlsoap.org/ws/2004/09/enumeration/EnumerateResponse\n" \
    "</wsa:Action>\n" \
    "<wsa:MessageID>\n" \
    "uuid:00000000-0000-0000-0000-000000000000\n" \
    "</wsa:MessageID>\n" \
    "<wsa:RelatesTo>\n" \
    "uuid:00000000-0000-0000-0000-000000000000\n" \
    "</wsa:RelatesTo>\n" \
    "</SOAP-ENV:Header>\n" \
    "<SOAP-ENV:Body>\n" \
    "<wsen:EnumerateResponse>\n" \
    "<wsen:EnumerationContext>\n" \
    "000000000000\n" \
    "</wsen:EnumerationContext>\n" \
    "<wsman:Items>\n" \
    "</wsman:Items>\n" \
    "</wsen:EnumerateResponse>\n" \
    "</SOAP-ENV:Body>\n" \
    "</SOAP-ENV:Envelope>\n"

/* aproximate repsonse header size */
#define APPROX_ENUM_RESP_ENVELOPE_SIZE \
    (sizeof(TYPICAL_ENUM_RESPONSE_ENVELOPE) + 64)

static const MI_Uint32 _MAGIC = 0x1CF2BCB7;

/************************************************************************\
*   Local definitions
\************************************************************************/

typedef struct _WSMAN_ConnectionData    WSMAN_ConnectionData;
typedef struct _WSMAN_EnumerateContext  WSMAN_EnumerateContext;

/* Maximum number of enumeration contexts stored at the same time
    effectively limits number of concurent enumerations */
#define WSMAN_MAX_ENUM_CONTEXTS 64

struct _WSMAN
{
    MI_Uint32 magic;

    OpenCallback callback;
    void* callbackData;

    Http* http;
    Selector* selector;

    /* configurable options */
    WSMAN_Options options;

    // to synchronize access to enumeration contexts
    RecursiveLock lock;

    /* Array of enumeration contexts:
        each 'pull' will look for corresponding context
    */
    WSMAN_EnumerateContext* enumerateContexts[WSMAN_MAX_ENUM_CONTEXTS];
    // If the particular enumerate context is in the process of being deleted
    MI_Boolean enumerateContextDeleted[WSMAN_MAX_ENUM_CONTEXTS];

    ptrdiff_t numEnumerateContexts;
    MI_Boolean deleting;

    /* Cached xml parser with all namespaces registered */
    XML xml;
};

typedef struct _WSMAN_Timer
{
    /* Generic timer to handle timeouts */
    Timer timer;

    /* Force a heartbeat event if nothing else can be sent during HB interval */
    MI_Boolean forceResult;

    /* The Strand is exiting while a timer may be active.  The timer should fire,
     * but not take action to ensure appropriate clean up. */
    MI_Boolean cancelledTimer;

    /* When heartbeats are requested during subscribe, these values are
     * considered when deciding when to send heartbeats. */
    MI_Uint64 heartbeatInterval;

    /* The timeout was called as a result of a PullAttach */
    MI_Boolean isPullAttached;
} WSMAN_Timer;

/* Represents state of connection including buffers, unsent packets, states etc */
struct _WSMAN_ConnectionData
{
    StrandBoth strand;

    WSMAN* wsman;

    /* Requestor information */
    AuthInfo authInfo;

    /* Attributes of the request */
    WSMAN_WSHeader  wsheader;
    union
    {
        /* Actual type is defined by wsheader.rqtAction field */
         WSMAN_WSEnumeratePullBody wsenumpullbody;
    }
    u;

    /* incomming request msg */
    HttpRequestMsg * request;

    /* Request page (buffer for most pointers inside header/body structures) */
    Page* page;

    /* for single-instance/single-schema repsonses, we keep mesage until result
       received to avoid conflicts with keep-alive enabled */
    Message* single_message;

    /* flag indicates that response was not sent yet to the client */
    MI_Boolean outstandingRequest;

    /* True if WinRM client */
    UserAgent userAgent;

    /* Generic timer to handle operation timeouts */
    WSMAN_Timer cdTimer;
    MI_Uint32 enumCtxId;        // TODO: What about replacing it with a WSMAN_EnumerateContext ptr?

    /* A temporarily stored message from Post, prior to handling */
    Message* responseMessage; // TODO: During refactoring, see if it is possible to safely remove this or merge it with single_message

    const HttpHeaders*      httpHeaders;

#if defined(CONFIG_ENABLE_HTTPHEADERS)

    /* Dynamic list of headers */
    HttpHeader headers[HTTP_MAX_HEADERS];
    size_t headersSize;

#endif
};

typedef struct _WSMAN_EnumerateContextData
{
    /* Type of the request initiated the context */
    MI_Uint32 requestTag;

    /* Success response to client sent or not */
    MI_Boolean responsed;
}WSMAN_EnumerateContextData;

/* Enumeration context:
    'derived' from socket Handler, so it can subscribe for timeouts */

struct _WSMAN_EnumerateContext
{
    StrandBoth strand;

    WSMAN* wsman;

    /* based member - can be added to 'selector' for timeout support */
    Handler     base;

    /* response data */
    /* Linked list of messages to send */
    PostInstanceMsg* head;
    PostInstanceMsg* tail;

    /* Total size of all instances in response queue */
    MI_Uint32   totalResponseSize;

    /* Number of messages in repsonse queue */
    MI_Uint32   totalResponses;

    /* lower 16 bits is aninxed in self->enumerateContexts, upper 16 bits are random data (for validation) */
    MI_Uint32   enumerationContextID;
    MI_Result   finalResult;
    PostResultMsg *errorMessage;

    /* Indicates that 'Result' recevied from provider and stored in finalResult.
     * Also blocks future posts from providers during shutdown scenarios. */
    MI_Boolean  enumerationCompleted;

    /* pointer to current active connection - either Enumerate or Pull request */
    WSMAN_ConnectionData*   activeConnection;

    /* pointer to the connection being attached (a pull or unsubscribe). It will
     * become activeConnection once attached */
    volatile WSMAN_ConnectionData*   attachingConnection;

    /* If we are reached our buffer limit, we hold any posted message here and delay ACK */
    PostInstanceMsg* pendingMessage;

#ifndef DISABLE_INDICATION
    /* Whether the subscribe request asked for bookmarks during event delivery. */
    MI_Boolean sendBookmarks;
#endif

    /* additional data associated with operation */
    WSMAN_EnumerateContextData data;

    /* Heartbeat timer */
    WSMAN_Timer ecTimer;
};

/* forward declarations */

static void _SendEnumPullResponse(
    _In_    WSMAN_EnumerateContext* selfEC,
            MI_Boolean              fromRequest );

static void _SendErrorResultResponse(
    _In_        WSMAN_ConnectionData*   selfCD,
    _In_opt_    WSMAN_EnumerateContext* sendECStrand,
                MI_Result               result);

static void _WSMAN_ReleaseEnumerateContext(
    _In_    WSMAN*      self,
            MI_Uint32   enumerationContextID);

static void _HttpProcessRequest(
    _In_    WSMAN_ConnectionData*   selfCD,
    _In_    const HttpHeaders*      headers,
    _In_    Page*                   page);

#ifndef DISABLE_INDICATION

static MI_Result _WSMAN_AddSubscribeResponse(
    WSBuf *wsbuf,
    WSMAN_EnumerateContext* selfEC);

static void _ParseValidateProcessUnsubscribeRequest(
    WSMAN_ConnectionData* selfCD,
    XML* xml);

static void _ParseValidateProcessSubscribeRequest(
    WSMAN_ConnectionData* selfCD,
    XML* xml);

#endif /* ifndef DISABLE_INDICATION */

static MI_Uint64 _NextOperationID()
{
    static volatile ptrdiff_t _operationId = (ptrdiff_t)0x100000;
    return (MI_Uint64) Atomic_Inc(&_operationId);
}

static StrandFT _InteractionWsmanEnum_Left_FT;
static StrandFT _InteractionWsmanEnum_Right_FT;

/************************************************************************\
*   Helper functions
\************************************************************************/
/* Converts Enumeration mode into "Message" struct flag */
MI_INLINE   MI_Uint32 _convertWSMANtoMsgEnumerationMode(
    MI_Uint32 enumerationMode )
{
    if (WSMANTAG_ENUM_MODE_EPR == enumerationMode)
        return WSMAN_EPRFlag;

    if (WSMANTAG_ENUM_MODE_OBJECT_AND_EPR == enumerationMode)
        return WSMAN_ObjectAndEPRFlag;

    return WSMAN_ObjectFlag;
}

/************************************************************************\
*   Enumeration Context operations
\************************************************************************/

static void _EC_ReleasePendingMessage(
    WSMAN_EnumerateContext* self)
{
    if (self->pendingMessage)
    {
        PostInstanceMsg_Release(self->pendingMessage);
        self->pendingMessage = NULL;
        StrandBoth_ScheduleAckRight(&self->strand);
    }
}

// Called inside the EC strand
static void _EC_ReleaseAllMessages(
    WSMAN_EnumerateContext* self)
{
    STRAND_ASSERTONSTRAND( &self->strand.base );

    /* Delete all queued messages*/
    while (self->head)
    {
        PostInstanceMsg* msg = self->head;

        List_Remove(
            (ListElem**)&self->head,
            (ListElem**)&self->tail,
            (ListElem*)msg);
        PostInstanceMsg_Release(msg);
    }
    self->totalResponses = 0;
    self->totalResponseSize = 0;

    _EC_ReleasePendingMessage(self);
}

// Detaches from left connection
// Usually called inside the EC strand (can be on called on CD Strand on creation)
static void _EC_CloseLeft(
    _In_    WSMAN_EnumerateContext* self,
            MI_Boolean              fromRequest )
{
    DEBUG_ASSERT( self->strand.base.info.opened );
    DEBUG_ASSERT( !self->strand.base.info.thisClosedOther );
    DEBUG_ASSERT( NULL != self->activeConnection );

    if( fromRequest )
    {
        // We set this manually
        self->activeConnection->strand.infoRight.otherClosedThis = MI_TRUE;
        self->strand.base.info.thisClosedOther = MI_TRUE;
        self->activeConnection->strand.infoRight.thisClosedOther = MI_TRUE;
        self->strand.base.info.otherClosedThis = MI_TRUE;
        self->activeConnection = NULL;
    }
    else
    {
        self->activeConnection = NULL;
        StrandBoth_CloseLeft( &self->strand );
    }
}

// Called inside the EC strand
// checks if the left interaction is already closed
// if not, it closes it
static void _EC_CheckCloseLeft(
    _In_    WSMAN_EnumerateContext* self)
{
    STRAND_ASSERTONSTRAND(&self->strand.base);
    DEBUG_ASSERT( self->strand.base.info.opened );

    trace_Wsman_EC_CheckCloseLeft( self->strand.base.info.thisClosedOther, self->activeConnection );

    if( !self->strand.base.info.thisClosedOther )
    {
        _EC_CloseLeft( self, MI_FALSE );
    }
    else
    {
        // If we have closed the left already there should not be activeConnection
        DEBUG_ASSERT( NULL == self->activeConnection  );
    }
}

// Called inside the EC strand
// checks if the right interaction is already closed
// if not, it closes it and releases enum context from WSMAN
static void _EC_CheckCloseRight(
    _In_    WSMAN_EnumerateContext* self)
{
    STRAND_ASSERTONSTRAND(&self->strand.base);

    trace_Wsman_EC_CheckCloseRight( Strand_HaveTimer(&self->strand.base), self->strand.infoRight.thisClosedOther );

    if (Strand_HaveTimer(&self->strand.base))
    {
        // takes care of deleting timer if was set (it will come back here once timer is actually expired)
        Strand_FireTimer( &self->strand.base );
    }
    else if( !self->strand.infoRight.thisClosedOther )
    {
        // Remove context from the list
        _WSMAN_ReleaseEnumerateContext(self->wsman, self->enumerationContextID);

        _EC_ReleaseAllMessages(self);

        // Close interaction to the right so object is ready to be deleted
        StrandBoth_CloseRight( &self->strand );
    }
}

/************************************************************************\
*   WSman operations
\************************************************************************/
MI_INLINE
MI_Uint32 _WSMAN_GetEnumContextIndex(
        WSMAN*      self,
        MI_Uint32   enumerationContextID,
        MI_Boolean  isRelease )
{
    MI_Uint32 index = enumerationContextID & 0xFFFF;

    /* verify that context exist and has the same id as required */
    if (index < MI_COUNT(self->enumerateContexts) &&
        self->enumerateContexts[index] &&
        (isRelease || !self->enumerateContextDeleted[index]) &&
        self->enumerateContexts[index]->enumerationContextID == enumerationContextID)
    {
        return index;
    }
    else
    {
        return WSMAN_MAX_ENUM_CONTEXTS;
    }
}

static WSMAN_EnumerateContext* _WSMAN_FindEnumContext(
    WSMAN* self,
    MI_Uint32   enumerationContextID)
{
    MI_Uint32 index;
    WSMAN_EnumerateContext* context = NULL;

    RecursiveLock_Acquire(&self->lock);

    index = _WSMAN_GetEnumContextIndex(self, enumerationContextID, MI_FALSE );
    if( index < WSMAN_MAX_ENUM_CONTEXTS )
    {
        context = self->enumerateContexts[index];
    }
    else
    {
        trace_Wsman_CannotFindEnumerateContext( enumerationContextID );
    }

    RecursiveLock_Release(&self->lock);

    return context;
}

// Called on Release Request
static WSMAN_EnumerateContext* _WSMAN_FindAndDeleteEnumContext(
    WSMAN* self,
    MI_Uint32   enumerationContextID)
{
    MI_Uint32 index;
    WSMAN_EnumerateContext* context = NULL;

    RecursiveLock_Acquire(&self->lock);

    index = _WSMAN_GetEnumContextIndex(self, enumerationContextID, MI_FALSE );
    if( index < WSMAN_MAX_ENUM_CONTEXTS )
    {
        context = self->enumerateContexts[index];
        self->enumerateContextDeleted[index] = MI_TRUE;
    }
    else
    {
        trace_CannotFindEnumerateContext( enumerationContextID );
    }

    RecursiveLock_Release(&self->lock);

    return context;
}

// Called on enum context strand or on CD strand during creation
static void _WSMAN_ReleaseEnumerateContext(
    _In_    WSMAN*      self,
            MI_Uint32   enumerationContextID)
{
    MI_Boolean broadcast = MI_FALSE;
    MI_Uint32 index;

    RecursiveLock_Acquire(&self->lock);

    index = _WSMAN_GetEnumContextIndex(self, enumerationContextID, MI_TRUE );
    if( index < WSMAN_MAX_ENUM_CONTEXTS )
    {
        self->enumerateContexts[index] = 0;
        self->enumerateContextDeleted[index] = MI_FALSE;
        --self->numEnumerateContexts;

        broadcast = self->deleting;
    }
    else
    {
        DEBUG_ASSERT( MI_FALSE );
    }

    RecursiveLock_Release(&self->lock);

    if( broadcast )
        CondLock_Broadcast( (ptrdiff_t)self );
}

// Lock should be acquired when calling here
static void _WSMAN_CancelAllEnumerateContexts(
    WSMAN* self)
{
    MI_Uint32 index;

    for (index = 0; index < MI_COUNT(self->enumerateContexts); index++ )
    {
        if (self->enumerateContexts[index])
        {
            // delete timer if was set
            Selector_RemoveHandler(self->selector, &self->enumerateContexts[index]->base);

            StrandBoth_ScheduleCancel( &self->enumerateContexts[index]->strand );
        }
    }
}

static WSMAN_EnumerateContext* _WSMAN_AllocateEnumContext(
    _In_    WSMAN*          self,
    _In_    Interaction*    withInteraction )
{
    MI_Uint32   enumerationContextID;
    WSMAN_EnumerateContext* enumContext;
    InteractionOpenParams params;

    RecursiveLock_Acquire(&self->lock);

    if( self->numEnumerateContexts >= MI_COUNT(self->enumerateContexts) )
    {
        trace_EnumContexAllocFailed_TooManyConcurrent();
        RecursiveLock_Release(&self->lock);
        return NULL;   /* no more slots available */
    }

    /* Find empty slot */
    for (enumerationContextID = 0; enumerationContextID < MI_COUNT(self->enumerateContexts); enumerationContextID++)
    {
        if (!self->enumerateContexts[enumerationContextID])
            break;
    }

    if (MI_COUNT(self->enumerateContexts) == enumerationContextID)
    {
        trace_EnumContexAllocFailed_TooManyConcurrent();
        RecursiveLock_Release(&self->lock);
        return NULL;   /* no more slots available */
    }

    InteractionOpenParams_Init( &params );
    params.interaction = withInteraction;

    enumContext = (WSMAN_EnumerateContext*)StrandBoth_New(
                        STRAND_DEBUG( WsmanEnumerationContext )
                        &_InteractionWsmanEnum_Left_FT,
                        &_InteractionWsmanEnum_Right_FT,
                        sizeof(WSMAN_EnumerateContext),
                        STRAND_FLAG_ENTERSTRAND,
                        &params );

    if (!enumContext)
    {
        trace_EnumContexAllocFailed_OutOfMemory();
        RecursiveLock_Release(&self->lock);
        return 0;
    }

    /* Store reference to a new context */
    self->enumerateContexts[enumerationContextID] = enumContext;
    self->enumerateContextDeleted[enumerationContextID] = MI_FALSE;

    ++self->numEnumerateContexts;

    RecursiveLock_Release(&self->lock);


    /* Add random data to the context-id */
    enumerationContextID |= (rand() & 0xFFFF) << 16;
    enumContext->enumerationContextID = enumerationContextID;

    enumContext->wsman = self;

    return enumContext;
}

/************************************************************************\
*   connection data operations
\************************************************************************/

static WSMAN_EnumerateContext* _CD_CreateEnumContext(
    WSMAN_ConnectionData* self)
{
    WSMAN_EnumerateContext* enumContext;

    DEBUG_ASSERT( !self->strand.infoRight.opened || !self->strand.infoRight.thisAckPending );
    DEBUG_ASSERT( !self->strand.infoRight.otherAckPending );

    enumContext = _WSMAN_AllocateEnumContext( self->wsman, &self->strand.infoRight.interaction );

    if( NULL != enumContext )
    {
        // Establish interaction opened with the enumeration context,
        // (equivalent to what would happening after opening interaction with dispatcher and receiving an Ack)
        self->strand.infoRight.opened = MI_TRUE;
        self->strand.infoRight.thisAckPending = MI_FALSE;
        self->strand.infoRight.thisClosedOther = MI_FALSE;
        enumContext->strand.base.info.opened = MI_TRUE;
        enumContext->strand.base.info.otherAckPending = MI_FALSE;
        enumContext->strand.base.info.otherClosedThis = MI_FALSE;
        // Also reset this so _EC_CheckCloseRight will properly close the CD
        self->strand.infoRight.otherClosedThis = MI_FALSE;

        /* link new context to current EnumRequest */
        enumContext->activeConnection = self;
    }

    return enumContext;
}

MI_INLINE void _CD_SetPage(
    WSMAN_ConnectionData* self,
    Page*   page)
{
    if (self->page)
        PAL_Free(self->page);

    self->page = page;
}

MI_INLINE void _CD_SetSingleMessage(
    WSMAN_ConnectionData* selfConnectionData,
    Message* single_message)
{
    if (selfConnectionData->single_message)
        Message_Release(selfConnectionData->single_message);

    selfConnectionData->single_message = single_message;

    if (selfConnectionData->single_message)
        Message_AddRef(selfConnectionData->single_message);
}

static void _CD_Cleanup(
    WSMAN_ConnectionData* selfConnectionData)
{
    _CD_SetPage(selfConnectionData, 0);
    _CD_SetSingleMessage(selfConnectionData, 0);

    selfConnectionData->userAgent = USERAGENT_UNKNOWN;

    selfConnectionData->httpHeaders = NULL;

#if defined(CONFIG_ENABLE_HTTPHEADERS)
    memset(selfConnectionData->headers, 0, sizeof(selfConnectionData->headers));
#endif

    /* free allocated instance/batch */
    if (selfConnectionData->wsheader.instanceBatch)
    {
        /* destroying batch takes care of instance and instanceBatch members */
        Batch_Destroy(selfConnectionData->wsheader.instanceBatch);
        selfConnectionData->wsheader.instanceBatch = 0;
        selfConnectionData->wsheader.instance = 0;
    }
    memset(&selfConnectionData->wsheader, 0, sizeof(selfConnectionData->wsheader));

    if (selfConnectionData->responseMessage)
    {
        Message_Release(selfConnectionData->responseMessage);
        selfConnectionData->responseMessage = NULL;
        // TODO: This is an un-acked message, but it cannot be acked since this is called from Finish
    }
}

// Used for both WSMAN_ConnectionData and WSMAN_EnumerateContext
static HttpResponseMsg* _PrepareResponseMsg(
    int httpErrorCode,
    Page* data)
{
    HttpResponseMsg* msg;

#if defined(CONFIG_ENABLE_WCHAR)

    if( NULL != data )
    {
        /* Convert page to wire XML character representation */

        size_t count = data->u.s.size / sizeof(ZChar);
        ZChar* src = (ZChar*)(data + 1);
        size_t firstNonAscii = 0; // temp variable used by this conversion function between two passes
        Page* page = NULL;
        int neededSpace = 0;

        neededSpace = ConvertWideCharToMultiByte(
                        src,
                        count,
                        &firstNonAscii,
                        NULL,
                        neededSpace);

        // output string would not be smaller than input
        if(neededSpace < (int)count)
        {
            PAL_Free(data);
            trace_Wsman_HttpResponseMsg_ConversionError();
            return NULL;
        }

        page = (Page*)PAL_Malloc(sizeof(Page) + (neededSpace * sizeof(char)));

        if (!page)
        {
            trace_Wsman_HttpResponseMsgPage_AllocError( httpErrorCode );
            PAL_Free(data);
            return NULL;
        }

        memset(page, 0, sizeof(Page));
        page->u.s.size = neededSpace;

        neededSpace = ConvertWideCharToMultiByte(
                        src,
                        count,
                        &firstNonAscii,
                        (Utf8Char *)(page + 1),
                        neededSpace);

        // previously computed length must be equal to the neededSpace
        if(neededSpace != page->u.s.size)
        {
            PAL_Free(data);
            trace_Wsman_HttpResponseMsg_ConversionError();
            return NULL;
        }

#if 0
        Tprintf(ZT("PAGE{%.*s}"), (int)(page->u.s.size), (char*)(page + 1));
#endif

        PAL_Free(data);

        data = page;
    }

#endif /* !defined(CONFIG_ENABLE_WCHAR) */

    msg = HttpResponseMsg_New(data, httpErrorCode);

    if( NULL == msg )
    {
        trace_Wsman_HttpResponseMsg_AllocError( httpErrorCode );

        if (data)
        {
            PAL_Free(data);
        }
    }

    return msg;
}

MI_Result _SendResponse(
    StrandBoth* self,
    int httpErrorCode,
    Page* data)
{
    HttpResponseMsg* msg;

    STRAND_ASSERTONSTRAND(&self->base);

    msg = _PrepareResponseMsg( httpErrorCode, data );

    if( NULL != msg )
    {
        StrandBoth_PostLeft( self, &msg->base);

        HttpResponseMsg_Release( msg);

        return MI_RESULT_OK;
    }
    else
    {
        return MI_RESULT_FAILED;
    }
}

MI_INLINE
MI_Result _EC_SendResponse(
    WSMAN_EnumerateContext* selfEC,
    int httpErrorCode,
    Page* data)
{
    return _SendResponse( &selfEC->strand, httpErrorCode, data );
}

MI_INLINE
MI_Result _CD_SendResponse(
    WSMAN_ConnectionData* selfCD,
    int httpErrorCode,
    Page* data)
{
    selfCD->outstandingRequest = MI_FALSE;
    return _SendResponse( &selfCD->strand, httpErrorCode, data );
}

MI_INLINE MI_Result _CD_SendErrorFailedResponse(
    _In_    WSMAN_ConnectionData*   selfCD,
            int                     httpErrorCode )
{
    return _CD_SendResponse(
                selfCD,
                httpErrorCode,
                NULL);
}

MI_INLINE MI_Result _CD_SendFailedResponse(
    _In_    WSMAN_ConnectionData*   selfCD )
{
    return _CD_SendErrorFailedResponse(
                selfCD,
                HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
}

// Used for both WSMAN_ConnectionData and WSMAN_EnumerateContext (sendOnDifferentStrand is indicated in that case)
static void _SendCimFaultResponse(
    _In_                WSMAN_ConnectionData*   selfCD,
    _In_opt_            WSMAN_EnumerateContext* sendOnECStrand,
                        WSBUF_FAULT_CODE        faultCode,
    _In_                const PostResultMsg*    message)
{
    MI_Result result;

    Page* responsePage = WSBuf_CreateFaultResponsePage(
        faultCode,
        selfCD->wsheader.unknownMandatoryTag,
        selfCD->wsheader.rqtMessageID,
        message);

    if( NULL == sendOnECStrand )
    {
        STRAND_ASSERTONSTRAND(&selfCD->strand.base);

        result = _CD_SendResponse(
            selfCD,
            HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR,
            responsePage);
    }
    else
    {
        STRAND_ASSERTONSTRAND(&sendOnECStrand->strand.base);

        result = _EC_SendResponse(
            sendOnECStrand,
            HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR,
            responsePage);
    }

    if (result != MI_RESULT_OK)
    {
        DEBUG_ASSERT( MI_RESULT_OK == result );
    }
}

static void _CD_SendFaultResponse(
    _In_                WSMAN_ConnectionData*   selfCD,
    _In_opt_            WSMAN_EnumerateContext* sendOnECStrand,
                        WSBUF_FAULT_CODE        faultCode,
    _In_                const ZChar*            descriptionText)
{
    /* This method is called when there is Non-Cim error occured ...
     * so sending MI_RESULT_OK
     */
    PostResultMsg message;

    memset(&message, 0, sizeof(message));
    message.result = MI_RESULT_OK;
    message.errorMessage = descriptionText;

    _SendCimFaultResponse(
        selfCD,
        sendOnECStrand,
        faultCode,
        &message);
}

static void _CD_SendReleaseResponse(
    WSMAN_ConnectionData* selfCD)
{
    Page* responsePage = WSBuf_CreateReleaseResponsePage(
        selfCD->wsheader.rqtMessageID);

    STRAND_ASSERTONSTRAND(&selfCD->strand.base);

    _CD_SendResponse(selfCD,
        HTTP_ERROR_CODE_OK,
        responsePage);
}

static void _CD_ProcessEnumFailedWithResult(
    _In_    WSMAN_ConnectionData*   self,
    _In_    WSMAN_EnumerateContext* enumContext,
            MI_Result               result )
{
    _WSMAN_ReleaseEnumerateContext(self->wsman, enumContext->enumerationContextID);
    if( MI_RESULT_OK == result )
    {
        // In this case we are calling from the CD strand
        STRAND_ASSERTONSTRAND(&self->strand.base);
        _CD_SendFailedResponse(self);
        _EC_CloseLeft( enumContext, MI_TRUE );
    }
    else
    {
        // In this case we are calling from the EC strand
        STRAND_ASSERTONSTRAND(&enumContext->strand.base);
        _SendErrorResultResponse( self, enumContext, result );
        _EC_CloseLeft( enumContext, MI_FALSE );
    }
    // force close state so the strand will delete itself
    Strand_ForceClose( &enumContext->strand.infoRight );
    enumContext->ecTimer.cancelledTimer = MI_TRUE;
    Strand_FireTimer( &enumContext->strand.base );
}

static void _CD_ProcessEnumFailed(
    _In_    WSMAN_ConnectionData*   self,
    _In_    WSMAN_EnumerateContext* enumContext )
{
    _CD_ProcessEnumFailedWithResult( self, enumContext, MI_RESULT_OK );
}

static int _ValidateHeader(
    WSMAN_ConnectionData* selfCD)
{
    STRAND_ASSERTONSTRAND(&selfCD->strand.base);

    if (selfCD->wsheader.unknownMandatoryTag)
    {
        _CD_SendFaultResponse(selfCD, NULL, WSBUF_FAULT_NOT_UNDERSTOOD, 0);
        return -1;
    }

    //DSP0226
    //1756 R6.2-4: Services should reject any MaxEnvelopeSize value less than 8192 octets. This number
    //1757 is the safe minimum in which faults can be reliably encoded for all character sets. If the requested
    //1758 size is less than this, the service should return a wsman:EncodingLimit fault with the following
    //1759 detail code:
    //1760 http://schemas.dmtf.org/wbem/wsman/1/wsman/faultDetail/MinimumEnvelopeLimit

    if (selfCD->wsheader.maxEnvelopeSize != 0 &&
        selfCD->wsheader.maxEnvelopeSize < 8192)
    {
        trace_Wsman_RequestedEnvelopeSizeIsTooSmall((int)selfCD->wsheader.maxEnvelopeSize);
        _CD_SendFaultResponse(selfCD, NULL, WSBUF_FAULT_ENCODING_LIMIT, 0);
        return -1;
    }

    /* Limit envelope size to server's max */
    if (selfCD->wsheader.maxEnvelopeSize == 0 ||
        selfCD->wsheader.maxEnvelopeSize > WSMAN_MAX_ENVELOPE_SIZE)
    {
        selfCD->wsheader.maxEnvelopeSize = WSMAN_MAX_ENVELOPE_SIZE;
    }

    /* Confirm appropriate OperationTimeout (if specified).
     * This check determines if xs:date was sent instead.
     * Conforms to R6.1-2 "Should" */
    if (selfCD->wsheader.operationTimeout.exists &&
        selfCD->wsheader.operationTimeout.value.isTimestamp )
    {
        trace_Wsman_InvalidOperationTimeoutValue_Timestamp();
        _CD_SendFaultResponse(selfCD, NULL, WSBUF_FAULT_INVALID_MESSAGE_INFORMATION_HEADER,
            ZT("OperationTimeout must be xs:duration if specified"));
        return -1;
    }

    /* verify action for invoke */
    if (selfCD->wsheader.foundAction &&
        0 == selfCD->wsheader.rqtAction &&
        (!selfCD->wsheader.rqtClassname || !selfCD->wsheader.rqtMethod))
    {
        trace_Wsman_UnknownCustomAction();

        _CD_SendFaultResponse(selfCD, NULL, WSBUF_FAULT_NOT_SUPPORTED,
            ZT("unknown custom action"));
        return -1;
    }

    /* Reject unsupported actions:
     * 1 - GetStatus
     * 2 - Renew */
    if (WSMANTAG_ACTION_RENEW == selfCD->wsheader.rqtAction ||
        WSMANTAG_ACTION_GETSTATUS == selfCD->wsheader.rqtAction)
    {
        trace_Wsman_InvalidActionRequest();

        _CD_SendFaultResponse(selfCD, NULL, WSBUF_FAULT_ACTION_NOT_SUPPORTED,
            ZT("Unsupported action requested."));
        return -1;
    }

    return 0;
}

static int _ValidateEnumerateRequest(
    WSMAN_ConnectionData* selfCD)
{
    /* If it has reference params, it must be an association request */
    MI_Instance* referenceParameters =
        selfCD->u.wsenumpullbody.associationFilter.referenceParameters;

    STRAND_ASSERTONSTRAND(&selfCD->strand.base);

    if (referenceParameters)
    {
        selfCD->wsheader.rqtNamespace = referenceParameters->nameSpace;
        selfCD->wsheader.rqtClassname = referenceParameters->classDecl->name;
    }
    else if (!selfCD->wsheader.rqtClassname || !selfCD->wsheader.rqtNamespace)
    {
#if defined(CONFIG_OS_WINDOWS)
        trace_WsmanEnum_ParametersMissing();

        _CD_SendFaultResponse(
            selfCD,
            NULL,
            WSBUF_FAULT_INTERNAL_ERROR,
            ZT("mandatory parameters (className, namespace) ")
                ZT("are missing for enumerate request"));
#else
        trace_WsmanEnum_ParametersMissing();

        _CD_SendFaultResponse(
            selfCD,
            NULL,
            WSBUF_FAULT_INTERNAL_ERROR,
            ZT("mandatory parameters (className, namespace) "
                "are missing for enumerate request"));
#endif
        return -1;
    }

    //R8.2.3; DSP226
    //wsmen:Enumerate/wsman:MaxElements
    //(optional) indicates the maximum number of items the consumer is willing to accept in the
    //EnumerateResponse
    //It plays the same role as wsmen:Pull/wsmen:MaxElements. When this element is absent, its
    //implied value is 1.
    if (!selfCD->u.wsenumpullbody.maxElements)
        selfCD->u.wsenumpullbody.maxElements = 1;

    // if enumeration mode is not specified, use 'Objects'
    if (selfCD->u.wsenumpullbody.enumerationMode == 0)
        selfCD->u.wsenumpullbody.enumerationMode = WSMANTAG_ENUM_MODE_OBJECT;

    return 0;
}

static int _ValidatePullRequest(
    WSMAN_ConnectionData* selfCD)
{
    STRAND_ASSERTONSTRAND(&selfCD->strand.base);

    //R8.2.3; DSP226
    //wsmen:Enumerate/wsman:MaxElements
    //(optional) indicates the maximum number of items the consumer is willing to accept in the
    //EnumerateResponse
    //It plays the same role as wsmen:Pull/wsmen:MaxElements. When this element is absent, its
    //implied value is 1.
    if (!selfCD->u.wsenumpullbody.maxElements)
        selfCD->u.wsenumpullbody.maxElements = 1;

    if (selfCD->u.wsenumpullbody.maxTime.exists)
    {
        MI_Uint64 durationInUsec = 0;
        DatetimeToUsec( &selfCD->u.wsenumpullbody.maxTime.value, &durationInUsec );

        if (0 == durationInUsec)
        {
            trace_Wsman_PullRequest_InvalidMaxTimeValue();
            _CD_SendFaultResponse(
                selfCD,
                NULL,
                WSBUF_FAULT_INVALID_EXPIRATION_TIME,
                ZT("Maxtime cannot be zero if specified"));
            return -1;
        }
    }

    return 0;
}

#if defined(CONFIG_ENABLE_HTTPHEADERS)
static void _FixupHTTPHeaderName(ZChar* name)
{
    while (*name)
    {
        ZChar c = *name;

        if (!isalnum(c) && c != '_')
            *name = '_';

        name++;
    }
}
#endif /* defined(CONFIG_ENABLE_HTTPHEADERS) */


/* Create msg->options instance to represent HTTP headers */
static MI_Result _GetHTTPHeaderOpts(
    WSMAN_ConnectionData* selfCD,
    RequestMsg* msg)
{
    if (selfCD->wsheader.options)
    {
        if (Instance_Clone(selfCD->wsheader.options, &msg->options, msg->base.batch) != MI_RESULT_OK)
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    else
    {
        msg->options = NULL;
    }

#ifndef DISABLE_SHELL
    {
        MI_Instance* options = msg->options;
        MI_Result r;
        MI_Value v;
        ZChar value[128];

        if (options == NULL)
        {
            r = Instance_NewDynamic(&options, MI_T("Options"), MI_FLAG_CLASS,
                msg->base.batch);

            if (r == MI_RESULT_FAILED || options == NULL)
                return MI_RESULT_FAILED;

            msg->options = options;
        }

        {   /* HTTP URL */
            TcsStrlcpy(value, selfCD->httpHeaders->httpUrl, MI_COUNT(value));

            v.string = value;

            r = __MI_Instance_AddElement(
                options,
                MI_T("HTTP_URL"),
                &v,
                MI_STRING,
                0);

            if (r != MI_RESULT_OK)
                return r;
        }
        {   /* USERNAME */
            TcsStrlcpy(value, selfCD->httpHeaders->username, MI_COUNT(value));

            v.string = value;

            r = __MI_Instance_AddElement(
                options,
                MI_T("HTTP_USERNAME"),
                &v,
                MI_STRING,
                0);

            if (r != MI_RESULT_OK)
                return r;
        }
        {   /* authorization string */
            TcsStrlcpy(value, selfCD->httpHeaders->authorization, MI_COUNT(value));

            v.string = value;

            r = __MI_Instance_AddElement(
                options,
                MI_T("HTTP_AUTHORIZATION"),
                &v,
                MI_STRING,
                0);

            if (r != MI_RESULT_OK)
                return r;
        }
    }
#endif


#if defined(CONFIG_ENABLE_HTTPHEADERS)
    {
        MI_Instance* options = msg->options;
        MI_Result r;
        size_t i;

        /* Don't create instance if there are no HTTP headers */
        if (selfCD->headersSize == 0)
            return MI_RESULT_OK;

        /* Create new instance to represent options */

        if (options == NULL)
        {
            r = Instance_NewDynamic(&options, MI_T("Options"), MI_FLAG_CLASS,
                msg->base.batch);

            if (r == MI_RESULT_FAILED || options == NULL)
                return MI_RESULT_FAILED;

            msg->options = options;
        }

        /* Add string options for each of the HTTP headers */

        for (i = 0; i < selfCD->headersSize; i++)
        {
            MI_Value v;
            ZChar name[128];
            ZChar value[128];

            Tcslcpy(name, MI_T("HTTP_"), MI_COUNT(name));
            TcsStrlcat(name, selfCD->headers[i].name, MI_COUNT(name));

            _FixupHTTPHeaderName(name);

            Tcslcpy(value, selfCD->headers[i].value, MI_COUNT(value));

            v.string = value;

            r = __MI_Instance_AddElement(
                options,
                name,
                &v,
                MI_STRING,
                0);

            if (r != MI_RESULT_OK)
                return r;
        }


    }
#endif /* defined(CONFIG_ENABLE_HTTPHEADERS) */

    return MI_RESULT_OK;
}

static MI_Result _GetWSManHeaderOpts(
    WSMAN_ConnectionData* selfCD,
    RequestMsg* msg)
{
    MI_Instance* options = msg->options;
    MI_Result r;
    MI_Value v;

    v.string = (MI_Char*)selfCD->wsheader.rqtResourceUri;

    r = __MI_Instance_AddElement(
        options,
        MI_T("WSMAN_ResourceURI"),
        &v,
        MI_STRING,
        0);
    if (r != MI_RESULT_OK)
        return r;

    v.string = (MI_Char*)selfCD->wsheader.rqtLocale;

    r = __MI_Instance_AddElement(
        options,
        MI_T("WSMAN_Locale"),
        &v,
        MI_STRING,
        0);
    if (r != MI_RESULT_OK)
        return r;

    v.string = (MI_Char*)selfCD->wsheader.rqtDataLocale;

    r = __MI_Instance_AddElement(
        options,
        MI_T("WSMAN_DataLocale"),
        &v,
        MI_STRING,
        0);
    if (r != MI_RESULT_OK)
        return r;

    if (selfCD->wsheader.operationTimeout.exists)
    {
        v.datetime = selfCD->wsheader.operationTimeout.value;
        r = __MI_Instance_AddElement(
            options,
            MI_T("WSMAN_OperationTimeout"),
            &v,
            MI_DATETIME,
            0);
        if (r != MI_RESULT_OK)
            return r;
    }

    return r;
}


/* Converts the WSMAN options into "Message" struct flag */
MI_INLINE   MI_Uint32 _GetFlagsFromWsmanOptions(
        WSMAN_ConnectionData* selfCD )
{
    MI_Uint32 flags = 0;

    if(selfCD->wsheader.includeClassOrigin)
        flags |= WSMAN_IncludeClassOrigin;

    if(selfCD->wsheader.includeInheritanceHierarchy)
        flags |= WSMAN_IncludeInheritanceHierarchy;

    if(selfCD->wsheader.includeInheritedElements)
        flags |= WSMAN_IncludeInheritedElements;

    if(selfCD->wsheader.includeQualifiers)
        flags |= WSMAN_IncludeQualifiers;

    if(selfCD->wsheader.usePreciseArrays)
        flags |= WSMAN_UsePreciseArrays;

#ifndef DISABLE_SHELL
    if(selfCD->wsheader.isShellOperation)
        flags |= WSMAN_IsShellOperation;
#endif


    trace_GetFlagsFromWsmanOptions(
            (flags & WSMAN_IncludeClassOrigin) != 0,
            (flags & WSMAN_IncludeInheritanceHierarchy) != 0,
            (flags & WSMAN_IncludeInheritedElements) != 0,
            (flags & WSMAN_IncludeQualifiers) != 0,
            (flags & WSMAN_UsePreciseArrays) != 0);
    return flags;
}


// open interaction with the part on the right (usually dispatcher)
static void _OpenRight_Imp(
    _In_    StrandBoth*             strand,
    _In_    WSMAN*                  wsman,
    _In_    RequestMsg*             msg )
{
    if( !strand->infoRight.opened )
    {
        // If this is the first time we used this CD it will be waiting an Open already
        strand->infoRight.thisAckPending = MI_FALSE;
    }
    else
    {
        DEBUG_ASSERT( !strand->infoRight.thisAckPending );
    }

    // This give the ability to steal the strand if the open completes,
    // otherwise any Post in the same thread will be delayed
    // and the stack will eventually deadlock on in-proc providers that send
    // several posts in the same open thread
    StrandBoth_Open( strand, wsman->callback, wsman->callbackData, &msg->base, MI_TRUE, MI_FALSE );
    // Operation can be already started (note that the strand is abandoned at this point)
}

/* Return value of zero means that it is not specified and should not be used.
 * Otherwise a value will be provided. */
static MI_Uint64 _GetTimeoutFromConnectionData(
    WSMAN_ConnectionData* self)
{
    MI_Uint64 timeoutUsec = 0;

    if (self->wsheader.operationTimeout.exists ||   /* Common to all operations */
        self->u.wsenumpullbody.maxTime.exists)      /* Only for PULL operations */
    {
        /* A timeout was specified. Determine the correct value to use
         * or use the default.
         * Note: OperationTimeout has precendence when both are specified. */
        if (self->wsheader.operationTimeout.exists)
        {
            DatetimeToUsec(&self->wsheader.operationTimeout.value, &timeoutUsec);
        }
        else
        {
            DatetimeToUsec(&self->u.wsenumpullbody.maxTime.value, &timeoutUsec);
        }

        if (0 == timeoutUsec)
        {
            /* Unable to parse.  Use default instead */
            timeoutUsec = WSMAN_TIMEOUT_DEFAULT;
#if defined(_MSC_VER)
            trace_Wsman_UnableToconvertDatetimeToUsec_MSCVER( timeoutUsec, self->wsheader.rqtAction );
#else
            trace_Wsman_UnableToconvertDatetimeToUsec_POSIX( timeoutUsec, self->wsheader.rqtAction );
#endif
        }
    }
    return timeoutUsec;
}

/* Starts a timer on the CD strand if one was specified in the request. */
static void _CD_StartTimer(
    WSMAN_ConnectionData* self)
{
    MI_Uint64 timeoutInUsec = _GetTimeoutFromConnectionData(self);

    if (0 != timeoutInUsec)
    {
        Strand_StartTimer( &self->strand.base, &self->cdTimer.timer, timeoutInUsec );
    }
}

MI_INLINE
void _OpenRightSingle(
    _In_    WSMAN_ConnectionData*   self,
    _In_    RequestMsg*             msg )
{
#if defined(CONFIG_OS_WINDOWS)
    // TODO: Remove OS-specific check once OMI is multi-threaded
    /* Timers cannot be supported for non-complex operations in OMI until it
     * becomes multi-threaded.  This check limits support to Windows and should
     * be removed once OMI is multi-threaded.
     */
    // TODO: Re-enable once the logic is debugged in OMI
    //_CD_StartTimer( self );
#endif

    _OpenRight_Imp( &self->strand, self->wsman, msg );
}

static void _OpenRightEnum(
    _In_    WSMAN_ConnectionData*   self,
    _In_    WSMAN_EnumerateContext* enumContext,
    _In_    RequestMsg*             msg,
            MI_Boolean              updateTimer )
{
    // Do this while still in the CD strand for safety

#if defined(CONFIG_OS_WINDOWS)
    // TODO: Remove OS-specific check once OMI is multi-threaded
    /* Timers cannot be supported for non-complex operations in OMI until it
     * becomes multi-threaded.  This check limits support to Windows and should
     * be removed once OMI is multi-threaded.
     */
    // TODO: Re-enable once the logic is debugged in OMI
    // self->enumCtxId = enumContext->enumerationContextID;
    //_CD_StartTimer( self );
#else
    // TODO: Remove this else once OMI is multi-threaded
    // In Linux and Unix, only start the CD timer if the operation is a subscribe
    // request. All other complex operations will not support timers until OMI
    // is multi-threaded.
    if (WSMANTAG_ACTION_SUBSCRIBE == self->wsheader.rqtAction)
    {
        self->enumCtxId = enumContext->enumerationContextID;
        _CD_StartTimer( self );
    }
#endif

    // Leave CD strand first, otherwise any Post in the same thread will be delayed
    // and the stack will eventually deadlock on in-proc providers that send
    // several posts in the same open thread
    Strand_Leave( &self->strand.base );

    // Now we are just on the enum context strand
    _OpenRight_Imp( &enumContext->strand, enumContext->wsman, msg );
}

static void _ProcessEnumerateRequest(
    WSMAN_ConnectionData* selfCD)
{
    EnumerateInstancesReq* msg;
    WSMAN_EnumerateContext* enumContext;
    MI_Boolean updateTimer = MI_FALSE;

    STRAND_ASSERTONSTRAND(&selfCD->strand.base);

    /* create EnumerateContext */
    enumContext = _CD_CreateEnumContext(selfCD);

    if (!enumContext)
    {
        _CD_SendFailedResponse(selfCD);
        return;
    }

    // Create new request.
    msg = EnumerateInstancesReq_New(_NextOperationID(),
        WSMANFlag | _convertWSMANtoMsgEnumerationMode(selfCD->u.wsenumpullbody.enumerationMode) | _GetFlagsFromWsmanOptions(selfCD));

    if (!msg || (_GetHTTPHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK) || (_GetWSManHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK))
    {
        _CD_ProcessEnumFailed( selfCD, enumContext );
        return;
    }

    /* Set the user agent */
    msg->base.userAgent = selfCD->userAgent;

    /* In case when client does not support optimized enumeration,
        send empty Enum-response with correct enumerate context */
    if (!selfCD->u.wsenumpullbody.allowOptimization)
    {
        _SendEnumPullResponse(enumContext, MI_TRUE);
        updateTimer = MI_TRUE;
    }

    msg->nameSpace = Batch_Tcsdup(msg->base.base.batch, selfCD->wsheader.rqtNamespace);
    msg->className = Batch_Tcsdup(msg->base.base.batch, selfCD->wsheader.rqtClassname);

    if (!msg->className || !msg->nameSpace)
    {
        _CD_ProcessEnumFailed( selfCD, enumContext );
        EnumerateInstancesReq_Release(msg);
        return;
    }

    msg->deepInheritance = (selfCD->u.wsenumpullbody.polymorphismMode != WSMANTAG_ENUM_POLYMORPHISM_MODE_NONE);
    msg->basePropertiesOnly = (selfCD->u.wsenumpullbody.polymorphismMode == WSMANTAG_ENUM_POLYMORPHISM_MODE_EXCLUDE_PROPS);

    /* Set the query related fields */
    {
        if (selfCD->u.wsenumpullbody.dialect)
        {
            msg->queryLanguage = Batch_Tcsdup(msg->base.base.batch, selfCD->u.wsenumpullbody.dialect);
            if (!msg->queryLanguage)
            {
                _CD_ProcessEnumFailed( selfCD, enumContext );
                EnumerateInstancesReq_Release(msg);
                return;
            }
        }

        if (selfCD->u.wsenumpullbody.filter)
        {
            msg->queryExpression = Batch_Tcsdup(msg->base.base.batch, selfCD->u.wsenumpullbody.filter);
            if (!msg->queryExpression)
            {
                _CD_ProcessEnumFailed( selfCD, enumContext );
                EnumerateInstancesReq_Release(msg);
                return;
            }
        }

        if (selfCD->u.wsenumpullbody.selectorFilter)
        {
            if (Instance_Clone(selfCD->u.wsenumpullbody.selectorFilter, &msg->selectorFilter, msg->base.base.batch) != MI_RESULT_OK)
            {
                _CD_ProcessEnumFailed( selfCD, enumContext );
                EnumerateInstancesReq_Release(msg);
                return;
            }
        }
    }

    AuthInfo_Copy( &msg->base.authInfo, &selfCD->authInfo );

    _OpenRightEnum(selfCD,enumContext,&msg->base,updateTimer);

    EnumerateInstancesReq_Release(msg);
}

static void _ProcessAssociatorsRequest(
    WSMAN_ConnectionData* selfCD)
{
    AssociationsOfReq* msg;
    WSMAN_EnumerateContext* enumContext;
    MI_Uint32 enumerationMode;
    MI_Boolean updateTimer = MI_FALSE;

    /* create EnumerateContext */
    enumContext = _CD_CreateEnumContext(selfCD);

    if (!enumContext)
    {
        _CD_SendFailedResponse(selfCD);
        return;
    }

    /* Extract the enumeration mode */
    enumerationMode = _convertWSMANtoMsgEnumerationMode(
        selfCD->u.wsenumpullbody.enumerationMode);

    /* Create new request. */

    msg = AssociationsOfReq_New(
        _NextOperationID(),
        WSMANFlag | enumerationMode | _GetFlagsFromWsmanOptions(selfCD),
        (selfCD->u.wsenumpullbody.associationFilter.isAssosiatorOperation == MI_TRUE) ? AssociatorsOfReqTag : ReferencesOfReqTag);

    if (!msg || (_GetHTTPHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK) || (_GetWSManHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK))
    {
        _CD_ProcessEnumFailed( selfCD, enumContext );
        return;
    }

    /* Set the user agent */
    msg->base.userAgent = selfCD->userAgent;

    /* In case when client does not support optimized enumeration,
     *  send empty Enum-response with correct enumerate context
     */
    if (!selfCD->u.wsenumpullbody.allowOptimization)
    {
        _SendEnumPullResponse(enumContext, MI_TRUE);
        updateTimer = MI_TRUE;
    }

    msg->nameSpace = Batch_Tcsdup(
        msg->base.base.batch,
        selfCD->wsheader.rqtNamespace);

    msg->className = Batch_Tcsdup(
        msg->base.base.batch,
        selfCD->wsheader.rqtClassname);

    if (!msg->nameSpace || !msg->className)
    {
        _CD_ProcessEnumFailed( selfCD, enumContext );
        AssociationsOfReq_Release(msg);
        return;
    }

    AuthInfo_Copy( &msg->base.authInfo, &selfCD->authInfo );

    /* Set messages fileds from association filter */
    {
        WSMAN_AssociationFilter* filter =
            &selfCD->u.wsenumpullbody.associationFilter;

        msg->instance = filter->referenceParameters;
        msg->role = filter->role;
        msg->resultClass = filter->resultClassName;

        if (filter->isAssosiatorOperation == MI_TRUE)
        {
            msg->assocClass = filter->associationClassName;
            msg->resultRole = filter->resultRole;
        }
    }

    _OpenRightEnum(selfCD,enumContext,&msg->base,updateTimer);

    AssociationsOfReq_Release(msg);
}


static void _CD_ForceCloseRight(
    _In_ WSMAN_ConnectionData* self)
{
    STRAND_ASSERTONSTRAND(&self->strand.base);

    // Set this manually since we are not going to open anything to the right
    self->strand.infoRight.thisAckPending = MI_FALSE;
    self->strand.infoRight.thisClosedOther = MI_TRUE;
    self->strand.infoRight.otherClosedThis = MI_TRUE;
}

static void _ProcessPullRequest(
    WSMAN_ConnectionData* selfCD)
{
    WSMAN_EnumerateContext* enumContext;

    /* find EnumerateContext */
    enumContext = _WSMAN_FindEnumContext(selfCD->wsman, selfCD->u.wsenumpullbody.enumerationContextID);

    if (!enumContext)
    {
        _CD_SendFaultResponse(selfCD, NULL, WSBUF_FAULT_DESTINATION_UNREACHABLE, ZT("Enumeration context not found"));
        _CD_ForceCloseRight(selfCD);
        return;
    }

    /* link new context to the request */
    if (Atomic_CompareAndSwap((ptrdiff_t*)&enumContext->attachingConnection, 0, (ptrdiff_t)selfCD) == 0)
    {
        // We are about to reopen
        StrandBoth_StartOpenAsync( &selfCD->strand );

#if defined(CONFIG_OS_WINDOWS)
        // TODO: Remove OS-specific check once OMI is multi-threaded
        /* Timers cannot be supported for non-complex operations in OMI until it
         * becomes multi-threaded.  This check limits support to Windows and should
         * be removed once OMI is multi-threaded.
         */
        // TODO: Re-enable once the logic is debugged in OMI
        //_CD_StartTimer( selfCD );
#else
        // TODO: Remove this else once OMI is multi-threaded
        // In Linux and Unix, only start the CD timer if the operation is a Pull
        // request for a Subscribe EC. All other complex operations will not
        // support timers until OMI is multi-threaded.
        if (SubscribeReqTag == enumContext->data.requestTag)
        {
            _CD_StartTimer( selfCD );
        }
#endif

        //TODO: make sure there is no other pull attached
        StrandBoth_ScheduleAuxLeft(&enumContext->strand,ENUMERATIONCONTEXT_STRANDAUX_PULLATTACHED);
    }
    else
    {
        //one other pull is already registered
        _CD_SendFaultResponse(selfCD, NULL, WSBUF_FAULT_INTERNAL_ERROR, ZT("Discarding illegitimate Pull request"));
        _CD_ForceCloseRight(selfCD);
        return;
    }
}

static void _ProcessReleaseRequest(
    WSMAN_ConnectionData* selfCD)
{
    WSMAN_EnumerateContext* enumContext;

    // We are not going to open anything to the right anyway
    _CD_ForceCloseRight(selfCD);

    /* find EnumerateContext */
    enumContext = _WSMAN_FindAndDeleteEnumContext(selfCD->wsman, selfCD->u.wsenumpullbody.enumerationContextID);

    if (!enumContext)
    {
        _CD_SendFaultResponse(selfCD, NULL, WSBUF_FAULT_DESTINATION_UNREACHABLE, ZT("Enumeration context not found"));
        return;
    }

    trace_Wsman_ProcessReleaseRequest( selfCD->u.wsenumpullbody.enumerationContextID );

    // Remove it and also cancel anything outgoing
    StrandBoth_ScheduleCancel(&enumContext->strand);

    _CD_SendReleaseResponse(selfCD);
}

static void _ParseValidateProcessEnumerateRequest(
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
    /* ATTN: only used if enumeration contains an association filter. Find
     * some way to prevent creation in that case.
     */

    if (!selfCD->wsheader.instanceBatch)
    {
        selfCD->wsheader.instanceBatch = Batch_New(BATCH_MAX_PAGES);
    }

    /* Parse enumerate request/body */
    if (WS_ParseEnumerateBody(
        xml,
        &selfCD->wsheader.instanceBatch,
        &selfCD->u.wsenumpullbody) != 0)
    {
        trace_WsmanEnum_UnableToParseXml();
        _CD_SendFailedResponse(selfCD);
        return;
    }

    /* Validate enumerate request body */
    if (_ValidateEnumerateRequest(selfCD) != 0)
    {
        /* appropriate error code was already sent to the client */
        return;
    }

    /* Process request */

    if (selfCD->u.wsenumpullbody.foundAssociationOperation)
    {
        _ProcessAssociatorsRequest(selfCD);
    }
    else
    {
        _ProcessEnumerateRequest(selfCD);
    }
}

static void _ParseValidateProcessInvokeRequest(
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
    InvokeReq* msg = 0;

    /* if instance was created from batch, re-use exisintg batch to allocate message */
    if (selfCD->wsheader.instanceBatch)
    {
        /* Allocate heap space for message */
        msg = Batch_GetClear(selfCD->wsheader.instanceBatch, sizeof(InvokeReq));

        if (!msg)
            GOTO_FAILED;

        /* Set the tag */
        msg->base.base.tag = InvokeReqTag;

        /* Set the operation id and flags */
        msg->base.base.operationId = _NextOperationID();
        msg->base.base.flags = WSMANFlag | WSMAN_ObjectFlag | _GetFlagsFromWsmanOptions(selfCD);

        /* ref-counter is set to 1, to balance NewMessage/Release Message pair*/
        msg->base.base.refCounter = 1;

        /* Copy batch onto message (released by delete method) */
        msg->base.base.batch = selfCD->wsheader.instanceBatch;

        msg->instance = selfCD->wsheader.instance;
        selfCD->wsheader.instanceBatch = 0;
        selfCD->wsheader.instance = 0;
    }
    else
        msg = InvokeReq_New(_NextOperationID(), WSMANFlag | WSMAN_ObjectFlag | _GetFlagsFromWsmanOptions(selfCD));

    if (!msg || (_GetHTTPHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK) || (_GetWSManHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK))
        GOTO_FAILED;

    /* Set the user agent */
    msg->base.userAgent = selfCD->userAgent;

    /* Parse invoke request/body */
    switch(selfCD->wsheader.rqtAction)
    {
#ifndef DISABLE_SHELL
    case WSMANTAG_ACTION_SHELL_SIGNAL:
        if (WS_ParseSignalBody(xml, msg->base.base.batch, &msg->instanceParams) != 0)
            GOTO_FAILED;
        break;
    case WSMANTAG_ACTION_SHELL_RECEIVE:
        if (WS_ParseReceiveBody(xml, msg->base.base.batch, &msg->instanceParams) != 0)
            GOTO_FAILED;
        break;
    case WSMANTAG_ACTION_SHELL_SEND:
        if (WS_ParseSendBody(xml, msg->base.base.batch, &msg->instanceParams) != 0)
            GOTO_FAILED;
        break;
    case WSMANTAG_ACTION_SHELL_COMMAND:
#endif
    default:
        if (WS_ParseInvokeBody(xml, msg->base.base.batch, &msg->instanceParams) != 0)
            GOTO_FAILED;
        break;

    }

    /* Extract/set relevant parameters */
    if (selfCD->wsheader.rqtNamespace)
    {
        msg->nameSpace = Batch_Tcsdup(msg->base.base.batch, selfCD->wsheader.rqtNamespace);
        if (!msg->nameSpace)
            GOTO_FAILED;
    }

    if (selfCD->wsheader.isShellOperation)
    {
        msg->base.base.sessionId = Batch_Tcsdup(msg->base.base.batch, selfCD->wsheader.sessionId);
        if (!msg->base.base.sessionId)
            GOTO_FAILED;
    }

    msg->className = Batch_Tcsdup(msg->base.base.batch, selfCD->wsheader.rqtClassname);
    msg->function = Batch_Tcsdup(msg->base.base.batch, selfCD->wsheader.rqtMethod);

    if (!msg->className || !msg->function)
        GOTO_FAILED;

    AuthInfo_Copy( &msg->base.authInfo, &selfCD->authInfo );

    _OpenRightSingle(selfCD,&msg->base);

    InvokeReq_Release(msg);
    return;

failed:
    trace_WsmanInvoke_UnableToProcessRequest();
    _CD_SendFailedResponse(selfCD);

    if (msg)
        InvokeReq_Release(msg);
}

static void _ParseValidateProcessGetInstanceRequest(
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
    GetInstanceReq* msg = 0;

    MI_UNUSED(xml);

    /* Check if instance name parameter was specified */
    if (!selfCD->wsheader.instance || !selfCD->wsheader.instanceBatch)
    {
        trace_WsmanGetInstance_InstanceNameParameterMissing();
        _CD_SendFaultResponse(selfCD, NULL, WSBUF_FAULT_INTERNAL_ERROR, ZT("get-instance: instance name parameter is missing"));
        return;
    }

    /* if instance was created from batch, re-use exisintg batch to allocate message */
    /* Allocate heap space for message */
    msg = Batch_GetClear(selfCD->wsheader.instanceBatch, sizeof(GetInstanceReq));

    if (!msg || (_GetHTTPHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK) || (_GetWSManHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK))
        GOTO_FAILED;

    /* Set the user agent */
    msg->base.userAgent = selfCD->userAgent;

    /* Set the tag */
    msg->base.base.tag = GetInstanceReqTag;

    /* Set the operation id and flags */
    msg->base.base.operationId = _NextOperationID();
    msg->base.base.flags = WSMANFlag | WSMAN_ObjectFlag | _GetFlagsFromWsmanOptions(selfCD);

    /* ref-counter is set to 1, to balance NewMessage/Release Message pair*/
    msg->base.base.refCounter = 1;

    /* Copy batch into message (released by delete method) */
    msg->base.base.batch = selfCD->wsheader.instanceBatch;

    msg->instanceName = selfCD->wsheader.instance;

    /* clear batch/instance fields in header structure */
    selfCD->wsheader.instanceBatch = 0;
    selfCD->wsheader.instance = 0;

    /* Skip parsing get-request/body - assumed to be empty */

    /* Extract/set relevant parameters */
    if (selfCD->wsheader.rqtNamespace)
    {
        msg->nameSpace = Batch_Tcsdup(msg->base.base.batch, selfCD->wsheader.rqtNamespace);
        if (!msg->nameSpace)
            GOTO_FAILED;
    }

    if (selfCD->wsheader.isShellOperation)
    {
        msg->base.base.sessionId = Batch_Tcsdup(msg->base.base.batch, selfCD->wsheader.sessionId);
        if (!msg->base.base.sessionId)
            GOTO_FAILED;
    }

    AuthInfo_Copy( &msg->base.authInfo, &selfCD->authInfo );

    _OpenRightSingle(selfCD,&msg->base);

    GetInstanceReq_Release(msg);
    return;

failed:
    trace_WsmanGetInstance_UnableToProcessRequest();
    _CD_SendFailedResponse(selfCD);

    if (msg)
        GetInstanceReq_Release(msg);
}

static void _ParseValidateProcessGetClassRequest(
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
    GetClassReq* msg = 0;

    MI_Uint32 flags = WSMANFlag | _GetFlagsFromWsmanOptions(selfCD);

    MI_UNUSED(xml);

    msg = GetClassReq_New(_NextOperationID(), flags);

    if (!msg || (_GetHTTPHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK) || (_GetWSManHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK))
        GOTO_FAILED;

    /* Set the user agent */
    msg->base.userAgent = selfCD->userAgent;

    /* Set the tag */
    msg->base.base.tag = GetClassReqTag;

    /* Set the flags */
    msg->base.base.flags = flags;

    /* ref-counter is set to 1, to balance NewMessage/Release Message pair*/
    msg->base.base.refCounter = 1;

    /* Skip parsing get-request/body - assumed to be empty */

    /* Extract/set relevant parameters */
    if (!selfCD->wsheader.rqtClassname || !selfCD->wsheader.rqtNamespace)
    {
        GOTO_FAILED;
    }

    if (selfCD->wsheader.isShellOperation)
    {
        msg->base.base.sessionId = Batch_Tcsdup(msg->base.base.batch, selfCD->wsheader.sessionId);
        if (!msg->base.base.sessionId)
            GOTO_FAILED;
    }

    msg->className = Batch_Tcsdup(
        msg->base.base.batch,
        selfCD->wsheader.rqtClassname);
    if (!msg->className)
        GOTO_FAILED;

    msg->nameSpace = Batch_Tcsdup(
                    msg->base.base.batch,
                    selfCD->wsheader.rqtNamespace);
    if (!msg->nameSpace)
        GOTO_FAILED;

    AuthInfo_Copy( &msg->base.authInfo, &selfCD->authInfo );

    _OpenRightSingle(selfCD,&msg->base);

    GetClassReq_Release(msg);
    return;

failed:
    trace_WsmanGetClass_UnableToProcessRequest();
    _CD_SendFailedResponse(selfCD);

    if (msg)
        GetClassReq_Release(msg);
}

static void _ParseValidateProcessGetRequest(
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
    if(selfCD->wsheader.schemaRequestType == NOT_A_SCHEMA_REQUEST)
    {
        _ParseValidateProcessGetInstanceRequest(selfCD, xml);
    }
    else if(selfCD->wsheader.schemaRequestType == CIM_XML_SCHEMA_REQUEST)
    {
        _ParseValidateProcessGetClassRequest(selfCD, xml);
    }
    else
    {
        trace_WsmanGet_UnsupportedResourceURI();

        _CD_SendFaultResponse(selfCD, NULL, WSBUF_FAULT_NOT_SUPPORTED,
            ZT("GetClass not Supported in WS-CIM format"));
        return;
    }
}

static void _ParseValidateProcessPutRequest(
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
    ModifyInstanceReq* msg = 0;

    MI_UNUSED(xml);

    /* Check if instance name parameter was specified */
    if (!selfCD->wsheader.instance || !selfCD->wsheader.instanceBatch)
    {
        trace_WsmanPut_InstanceNameParameterMissing();
        _CD_SendFaultResponse(selfCD, NULL, WSBUF_FAULT_INTERNAL_ERROR, ZT("Put-instance: instance name parameter is missing"));
        return;
    }

    /* if instance was created from batch, re-use exisintg batch to allocate message */
    /* Allocate heap space for message */
    msg = Batch_GetClear(selfCD->wsheader.instanceBatch, sizeof(ModifyInstanceReq));

    if (!msg || (_GetHTTPHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK) || (_GetWSManHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK))
        GOTO_FAILED;

    /* Set the user agent */
    msg->base.userAgent = selfCD->userAgent;

    /* Set the tag */
    msg->base.base.tag = ModifyInstanceReqTag;

    /* Set the operation id and flags */
    msg->base.base.operationId = _NextOperationID();
    msg->base.base.flags = WSMANFlag | WSMAN_ObjectFlag | _GetFlagsFromWsmanOptions(selfCD);

    /* ref-counter is set to 1, to balance NewMessage/Release Message pair*/
    msg->base.base.refCounter = 1;

    /* Copy batch into message (released by delete method) */
    msg->base.base.batch = selfCD->wsheader.instanceBatch;
    msg->instance = selfCD->wsheader.instance;

    /* clear batch/instance fields in header structure */
    selfCD->wsheader.instanceBatch = 0;
    selfCD->wsheader.instance = 0;

    /* re-use 'create' parser to parse 'Modify' request/body */
    if (WS_ParseCreateBody(xml, msg->base.base.batch, &msg->instance, &selfCD->wsheader.isShellOperation) != 0)
        GOTO_FAILED;

    /* Extract/set relevant parameters */
    if (selfCD->wsheader.rqtNamespace)
    {
        msg->nameSpace = Batch_Tcsdup(msg->base.base.batch, selfCD->wsheader.rqtNamespace);
        if (!msg->nameSpace)
            GOTO_FAILED;
    }

    if (selfCD->wsheader.isShellOperation)
    {
        msg->base.base.sessionId = Batch_Tcsdup(msg->base.base.batch, selfCD->wsheader.sessionId);
        if (!msg->base.base.sessionId)
            GOTO_FAILED;
    }

    AuthInfo_Copy( &msg->base.authInfo, &selfCD->authInfo );

    _OpenRightSingle(selfCD,&msg->base);

    ModifyInstanceReq_Release(msg);
    return;

failed:
    trace_WsmanPutInstance_UnableToProcessRequest();
    _CD_SendFailedResponse(selfCD);

    if (msg)
        ModifyInstanceReq_Release(msg);
}

static void _ParseValidateProcessDeleteRequest(
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
    DeleteInstanceReq* msg = 0;

    MI_UNUSED(xml);

    /* Check if instance name parameter was specified */
    if (!selfCD->wsheader.instance || !selfCD->wsheader.instanceBatch)
    {
        trace_Wsman_InstanceNameParameterMissing();
        _CD_SendFaultResponse(selfCD, NULL, WSBUF_FAULT_INTERNAL_ERROR, ZT("delete-instance: instance name parameter is missing"));
        return;
    }

    /* if instance was created from batch, re-use exisintg batch to allocate message */
    /* Allocate heap space for message */
    msg = Batch_GetClear(selfCD->wsheader.instanceBatch, sizeof(DeleteInstanceReq));

    if (!msg || (_GetHTTPHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK) || (_GetWSManHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK))
        GOTO_FAILED;

    /* Set the user agent */
    msg->base.userAgent = selfCD->userAgent;

    /* Set the tag */
    msg->base.base.tag = DeleteInstanceReqTag;

    /* Set the operation id and flags */
    msg->base.base.operationId = _NextOperationID();
    msg->base.base.flags = WSMANFlag | WSMAN_ObjectFlag | _GetFlagsFromWsmanOptions(selfCD);

    /* ref-counter is set to 1, to balance NewMessage/Release Message pair*/
    msg->base.base.refCounter = 1;

    /* Copy batch into message (released by delete method) */
    msg->base.base.batch = selfCD->wsheader.instanceBatch;

    msg->instanceName = selfCD->wsheader.instance;

    /* clear batch/instance fields in header structure */
    selfCD->wsheader.instanceBatch = 0;
    selfCD->wsheader.instance = 0;

    /* Skip parsing Delete-request/body - assumed to be empty */

    /* Extract/set relevant parameters */
    if (selfCD->wsheader.rqtNamespace)
    {
        msg->nameSpace = Batch_Tcsdup(msg->base.base.batch, selfCD->wsheader.rqtNamespace);
        if (!msg->nameSpace)
            GOTO_FAILED;
    }

    if (selfCD->wsheader.isShellOperation)
    {
        msg->base.base.sessionId = Batch_Tcsdup(msg->base.base.batch, selfCD->wsheader.sessionId);
        if (!msg->base.base.sessionId)
            GOTO_FAILED;
    }

    AuthInfo_Copy( &msg->base.authInfo, &selfCD->authInfo );

    _OpenRightSingle(selfCD,&msg->base);

    DeleteInstanceReq_Release(msg);
    return;

failed:
    trace_WsmanDelete_UnableToProcessRequest();
    _CD_SendFailedResponse(selfCD);

    if (msg)
        DeleteInstanceReq_Release(msg);
}

static void _ParseValidateProcessCreateRequest(
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
    CreateInstanceReq* msg = 0;

    msg = CreateInstanceReq_New(_NextOperationID(), WSMANFlag | WSMAN_CreatedEPRFlag | _GetFlagsFromWsmanOptions(selfCD));

    if (!msg || (_GetHTTPHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK) || (_GetWSManHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK))
        GOTO_FAILED;

    /* Set the user agent */
    msg->base.userAgent = selfCD->userAgent;

    /* Parse create request/body */
    if (WS_ParseCreateBody(xml, msg->base.base.batch, &msg->instance, &selfCD->wsheader.isShellOperation) != 0)
        GOTO_FAILED;

#ifndef DISABLE_SHELL
    {
        MI_Value boolVal;

        if (selfCD->wsheader.isCompressed)
        {
            boolVal.boolean = MI_TRUE;
            if (MI_Instance_AddElement(msg->instance, MI_T("IsCompressed"), &boolVal, MI_BOOLEAN, 0) != 0)
                GOTO_FAILED;
        }
    }
#endif

    /* Extract/set relevant parameters */
    if (selfCD->wsheader.rqtNamespace)
    {
        msg->nameSpace = Batch_Tcsdup(msg->base.base.batch, selfCD->wsheader.rqtNamespace);
        if (!msg->nameSpace)
            GOTO_FAILED;
    }

#ifndef DISABLE_SHELL
    if (selfCD->wsheader.isShellOperation)
    {
        if (selfCD->wsheader.sessionId)
        {
            msg->base.base.sessionId = Batch_Tcsdup(msg->base.base.batch, selfCD->wsheader.sessionId);
            if (!msg->base.base.sessionId)
                GOTO_FAILED;
        }
        /* Determined if it is a shell operation from the body so mark the flags */
        msg->base.base.flags |= WSMAN_IsShellOperation;
    }
#endif

    AuthInfo_Copy( &msg->base.authInfo, &selfCD->authInfo );

    _OpenRightSingle(selfCD,&msg->base);

    CreateInstanceReq_Release(msg);
    return;

failed:
    trace_WsmanCreate_UnableToProcessRequest();
    _CD_SendFailedResponse(selfCD);

    if (msg)
        CreateInstanceReq_Release(msg);
}

static void _ParseValidateProcessPullRequest(
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
    /* Parse pull request/body */
    if (WS_ParsePullBody(xml, &selfCD->u.wsenumpullbody) != 0)
    {
        trace_WsmanPull_UnableToParseXml();
        _CD_SendFailedResponse(selfCD);
        return;
    }

    /* Validate enumerate request body */
    if (_ValidatePullRequest(selfCD) != 0)
    {
        /* appropriate error code was already sent to the client */
        return;
    }

    /* Process reqest */
    _ProcessPullRequest(selfCD);
}

static void _ParseValidateProcessReleaseRequest(
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
    /* Parse pull request/body */
    if (WS_ParseReleaseBody(xml, &selfCD->u.wsenumpullbody) != 0)
    {
        trace_WsmanRelease_UnableToParseXml();
        _CD_SendFailedResponse(selfCD);
        return;
    }

    /* Validate enumerate request body */
    /* no validation needed */

    /* Process request */
    _ProcessReleaseRequest(selfCD);
}

static void _SendIdentifyResponse(
    WSMAN_ConnectionData* selfCD)
{
    WSBuf out;
    Page* responsePage = 0;
#   define MSG \
    ZT("<soap:Envelope ") \
                ZT("xmlns:soap=\"http://www.w3.org/2003/05/soap-envelope\" ") \
                ZT("xmlns:wsmid=\"http://schemas.dmtf.org/wbem/wsman/identity/1/wsmanidentity.xsd\">") CR \
        ZT("<soap:Header/>") CR \
        ZT("<soap:Body>") CR \
            ZT("<soap:IdentifyResponse>") CR \
                ZT("<wsmid:ProtocolVersion>") \
                    ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd") \
                ZT("</wsmid:ProtocolVersion>") CR \
                ZT("<wsmid:ProductVendor>") \
                    CONFIG_FULLPRODUCT \
                ZT("</wsmid:ProductVendor>") CR \
                ZT("<wsmid:ProductVersion>") \
                    CONFIG_VERSION \
                ZT("</wsmid:ProductVersion>") CR \
                ZT("<wsmid:SecurityProfiles>") CR \
                ZT("<wsmid:SecurityProfileName>") \
                    ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman/secprofile/https/basic") \
                ZT("</wsmid:SecurityProfileName>") CR \
                ZT("</wsmid:SecurityProfiles>") CR \
                ZT("<wsmb:Capability_FaultIncludesCIMError xmlns:wsmb=\"http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xml\"/>") CR \
            ZT("</soap:IdentifyResponse>") CR \
        ZT("</soap:Body>") CR \
    ZT("</soap:Envelope>") CR

    if (WSBuf_Init(&out, 1024) != MI_RESULT_OK)
    {
        GOTO_FAILED;
    }

    if (WSBuf_AddLit(&out, LIT(MSG)) != MI_RESULT_OK)
    {
        GOTO_FAILED;
    }

    responsePage = WSBuf_StealPage(&out);

    if (!responsePage)
        GOTO_FAILED;

    _CD_SendResponse(
        selfCD,
        HTTP_ERROR_CODE_OK,
        responsePage);

    return;

failed:
    WSBuf_Destroy(&out);
    _CD_SendFailedResponse(selfCD);
}

static void _HandleIdentifyRequest(
    WSMAN_ConnectionData* selfCD,
    XML* xml)
{
    /* Parse pull request/body */
    if (WS_ParseIdentifyBody(xml) != 0)
    {
        trace_Wsman_NoActionOrIdentify();
        _CD_SendFailedResponse(selfCD);
        return;
    }

    _SendIdentifyResponse(selfCD);
}

/************************************************************************\
*   Dispatcher calls processing
\************************************************************************/

static void _EC_GetMessageSubset(
    WSMAN_EnumerateContext* selfEC,
    WSMAN_ConnectionData* selfCD,
    PostInstanceMsg** subsetEnd,
    MI_Uint32* totalSize,
    MI_ConstString* bookmark)
{
    MI_Uint32 count = 0;
    PostInstanceMsg* lastMsg = NULL; /* Used for tracking the bookmark of the last message */
    *totalSize = 0;
    *subsetEnd = selfEC->head;

    while (*subsetEnd)
    {
        lastMsg = *subsetEnd;

        if (count + 1 > selfCD->u.wsenumpullbody.maxElements ||
            (*totalSize) + (*subsetEnd)->packedInstanceSize + APPROX_ENUM_RESP_ENVELOPE_SIZE > selfCD->wsheader.maxEnvelopeSize)
            break;

        (*totalSize) += (*subsetEnd)->packedInstanceSize;
        count++;

        (*subsetEnd) = (PostInstanceMsg*)(*subsetEnd)->base.next;
    }

#ifndef DISABLE_INDICATION
    /* Subscribe enumerate contexts will only hold indications and
     * bookmarks should only be sent if requested. */
    if (selfEC->sendBookmarks &&
        NULL != lastMsg)
    {
        PostIndicationMsg* indication = (PostIndicationMsg*)lastMsg;
        *bookmark = indication->bookmark;
    }
#endif

}


static void _EC_ProcessPendingMessage(
    WSMAN_EnumerateContext* selfEC)
{
    if (selfEC->pendingMessage)
    {
         if ((selfEC->totalResponseSize + selfEC->pendingMessage->packedInstanceSize <= MAX_WSMAN_BUFFER_SIZE)
        && (selfEC->totalResponses < MAX_WSMAN_COLLECTION_SIZE))
         {
            List_Append(
                (ListElem**)&selfEC->head,
                (ListElem**)&selfEC->tail,
                (ListElem*)selfEC->pendingMessage);

            /* Increment total instance size */
            selfEC->totalResponseSize += selfEC->pendingMessage->packedInstanceSize;

            /* Increment total number of responses */
            selfEC->totalResponses++;

            selfEC->pendingMessage = NULL;
            StrandBoth_ScheduleAckRight(&selfEC->strand);
         }
    }

    return;
}

/*
 * Encapsulates the check to see if the last message has been sent for an
 * WSMAN_Enumeratecontext.  Returns TRUE if the last message has been sent
 * and it is OK to begin cleanup.
 */
static MI_Boolean _EC_IsLastMessageSent(
    WSMAN_EnumerateContext* selfEC )
{
    return (selfEC->enumerationCompleted && !selfEC->head);
}

static void _EC_StartHeartbeatTimer(
    WSMAN_EnumerateContext* selfEC )
{
    if (TIME_NEVER != selfEC->ecTimer.heartbeatInterval &&
        MI_FALSE == _EC_IsLastMessageSent(selfEC))
    {
        /* Timer is not running because it was already fired or never
         * started during the subscribe request. */
        DEBUG_ASSERT( MI_FALSE == Strand_HaveTimer(&selfEC->strand.base) );

        Strand_StartTimer( &selfEC->strand.base, &selfEC->ecTimer.timer, selfEC->ecTimer.heartbeatInterval );
    }
}

/* Sends as many instances as possible (based on envelope-size and instance counter) */
static void _SendEnumPullResponse(
    _In_    WSMAN_EnumerateContext* selfEC,
            MI_Boolean              fromRequest )
{
    WSBuf outBufHeader;
    WSBuf outBufTrailer;
    Page* responsePageCombined = 0;
    Page* responsePageHeader = 0;
    Page* responsePageTrailer = 0;
    MI_Uint32 totalSize, messagesSize = 0;
    WSMAN_ConnectionData* selfCD = selfEC->activeConnection;
    PostInstanceMsg* subsetEnd = 0;
    MI_Boolean endOfSequence = selfEC->enumerationCompleted;
    MI_Result result;
    MI_ConstString bookmarkToSend = NULL;

    DEBUG_ASSERT( NULL != selfCD );

#ifndef DISABLE_INDICATION
    /* SubscribeResponse messages should NOT contain any indications if they
     * have arrived before the SubscribeResponse message. */
    if (selfCD->wsheader.rqtAction != WSMANTAG_ACTION_SUBSCRIBE)
#endif
    {
        /* Get message subset based on envelope size/ maxElements */
        _EC_GetMessageSubset(selfEC, selfCD, &subsetEnd, &messagesSize, &bookmarkToSend);
    }

    /* validate if all mesages can be sent */
    if (endOfSequence && subsetEnd)
    {
        endOfSequence = MI_FALSE;
    }

    /* check if we can put at least one message in response */
    if (NULL != selfEC->head && subsetEnd == selfEC->head)
    {
        trace_Wsman_MaxEnvelopeIsTooSmall((int)subsetEnd->packedInstanceSize);
        _CD_SendFaultResponse(selfCD, fromRequest ? NULL : selfEC , WSBUF_FAULT_ENCODING_LIMIT, ZT("insufficient envelope size for instance transferring"));
        /* Note: leaving context 'as is' so advanced client can increase packet size and re-try */
        _EC_CloseLeft( selfEC, MI_FALSE );
        /* This also releases the context on WSMAN
         * The response should not be sent while a timer is running.
         * The timer must be stopped first */
        _EC_CheckCloseRight( selfEC );
        return;
    }

    /* Create EnumResponse */
    if (WSBuf_Init(&outBufHeader, APPROX_ENUM_RESP_ENVELOPE_SIZE) != MI_RESULT_OK)
    {
        outBufTrailer.page = 0;
        GOTO_FAILED;
    }

    if (WSBuf_Init(&outBufTrailer, 256) != MI_RESULT_OK)
        GOTO_FAILED;

    /* prepare response header */
    if (selfCD->wsheader.rqtAction == WSMANTAG_ACTION_ENUMERATE)
    {
        if (MI_RESULT_OK != WSBuf_CreateSoapResponseHeader(&outBufHeader,
            LIT(ZT("http://schemas.xmlsoap.org/ws/2004/09/enumeration/EnumerateResponse")), selfCD->wsheader.rqtMessageID))
            GOTO_FAILED;
    }
#ifndef DISABLE_INDICATION
    else if (selfCD->wsheader.rqtAction == WSMANTAG_ACTION_SUBSCRIBE)
    {
        if (MI_RESULT_OK != WSBuf_CreateSoapResponseHeader(&outBufHeader,
            LIT(ZT("http://schemas.xmlsoap.org/ws/2004/08/eventing/SubscribeResponse")), selfCD->wsheader.rqtMessageID))
            goto failed;
    }
#endif /* ifndef DISABLE_INDICATION */
    else
    {
        if (MI_RESULT_OK != WSBuf_CreateSoapResponseHeader(&outBufHeader,
            LIT(ZT("http://schemas.xmlsoap.org/ws/2004/09/enumeration/PullResponse")), selfCD->wsheader.rqtMessageID))
            GOTO_FAILED;

#ifndef DISABLE_INDICATION
        if (selfEC->sendBookmarks)
        {
            if (NULL == bookmarkToSend)
            {
                /* A bookmark was requested by the client, but not supplied
                 * by the provider.  Pass along the default value. */
                bookmarkToSend = ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman/bookmark/earliest");  // TODO: Appropriate to do?
            }

            if (MI_RESULT_OK != WSBuf_AddLit(&outBufHeader,
                LIT(ZT("<wsman:Bookmark>"))))
                GOTO_FAILED;

            if (MI_RESULT_OK != WSBuf_AddString(&outBufHeader,
                bookmarkToSend))
                GOTO_FAILED;

            if (MI_RESULT_OK != WSBuf_AddLit(&outBufHeader,
                LIT(ZT("</wsman:Bookmark>"))))
                GOTO_FAILED;
        }
#endif
    }

    if (MI_RESULT_OK != WSBuf_AddLit(&outBufHeader,
        LIT(ZT("</SOAP-ENV:Header>")
        ZT("<SOAP-ENV:Body>"))))
        GOTO_FAILED;

    if (selfCD->wsheader.rqtAction == WSMANTAG_ACTION_ENUMERATE)
    {
        if (MI_RESULT_OK != WSBuf_AddLit(&outBufHeader,
            LIT(ZT("<wsen:EnumerateResponse>"))))
            GOTO_FAILED;
    }
#ifndef DISABLE_INDICATION
    else if (selfCD->wsheader.rqtAction == WSMANTAG_ACTION_SUBSCRIBE)
    {
        if (MI_RESULT_OK != _WSMAN_AddSubscribeResponse(&outBufHeader, selfEC))
            GOTO_FAILED;
    }
#endif /* ifndef DISABLE_INDICATION */
    else
    {
        if (MI_RESULT_OK != WSBuf_AddLit(&outBufHeader,
            LIT(ZT("<wsen:PullResponse>"))))
            GOTO_FAILED;
    }

    if (MI_RESULT_OK != WSBuf_AddLit(&outBufHeader,
        LIT(ZT("<wsen:EnumerationContext>"))))
        GOTO_FAILED;

    if (MI_RESULT_OK != WSBuf_AddUint32(&outBufHeader,selfEC->enumerationContextID))
        GOTO_FAILED;

    if (MI_RESULT_OK != WSBuf_AddLit(&outBufHeader,
        LIT(ZT("</wsen:EnumerationContext>"))))
        GOTO_FAILED;

    if (selfCD->wsheader.rqtAction == WSMANTAG_ACTION_ENUMERATE)
    {
        if (MI_RESULT_OK != WSBuf_AddLit(&outBufHeader,
            LIT(ZT("<wsman:Items>"))))
            GOTO_FAILED;
    }
#ifndef DISABLE_INDICATION
    else if (selfCD->wsheader.rqtAction == WSMANTAG_ACTION_SUBSCRIBE)
    {
    }
#endif /* ifndef DISABLE_INDICATION */
    else
    {
        if (MI_RESULT_OK != WSBuf_AddLit(&outBufHeader,
            LIT(ZT("<wsen:Items>"))))
            GOTO_FAILED;
    }

    /* trailer */
    if (selfCD->wsheader.rqtAction == WSMANTAG_ACTION_ENUMERATE)
    {
        if (MI_RESULT_OK != WSBuf_AddLit(&outBufTrailer,
            LIT(ZT("</wsman:Items>"))))
            GOTO_FAILED;
    }
#ifndef DISABLE_INDICATION
    else if (selfCD->wsheader.rqtAction == WSMANTAG_ACTION_SUBSCRIBE)
    {
    }
#endif /* ifndef DISABLE_INDICATION */
    else
    {
        if (MI_RESULT_OK != WSBuf_AddLit(&outBufTrailer,
            LIT(ZT("</wsen:Items>"))))
            GOTO_FAILED;
    }

    if (endOfSequence)
    {
        if (selfCD->wsheader.rqtAction == WSMANTAG_ACTION_ENUMERATE)
        {
            if (MI_RESULT_OK != WSBuf_AddLit(&outBufTrailer,
                LIT(ZT("<wsman:EndOfSequence/>"))))
                GOTO_FAILED;
        }
        else
        {
            if (MI_RESULT_OK != WSBuf_AddLit(&outBufTrailer,
                LIT(ZT("<wsen:EndOfSequence/>"))))
                GOTO_FAILED;
        }
    }

    if (selfCD->wsheader.rqtAction == WSMANTAG_ACTION_ENUMERATE)
    {
        if (MI_RESULT_OK != WSBuf_AddLit(&outBufTrailer,
            LIT(ZT("</wsen:EnumerateResponse>"))))
            GOTO_FAILED;
    }
#ifndef DISABLE_INDICATION
    else if (selfCD->wsheader.rqtAction == WSMANTAG_ACTION_SUBSCRIBE)
    {
        if (MI_RESULT_OK != WSBuf_AddLit(&outBufTrailer,
            LIT(MI_T("</e:SubscribeResponse>"))))
            goto failed;
    }
#endif /* ifndef DISABLE_INDICATION */
    else
    {
        if (MI_RESULT_OK != WSBuf_AddLit(&outBufTrailer,
            LIT(ZT("</wsen:PullResponse>"))))
            GOTO_FAILED;
    }
    if (MI_RESULT_OK != WSBuf_AddLit(&outBufTrailer,
        LIT(ZT("</SOAP-ENV:Body>")
        ZT("</SOAP-ENV:Envelope>"))))
        GOTO_FAILED;

    /* all together */
    responsePageHeader = WSBuf_StealPage(&outBufHeader);
    responsePageTrailer = WSBuf_StealPage(&outBufTrailer);

    if (!responsePageTrailer || !responsePageHeader)
        GOTO_FAILED;

    /* calculate size */
    totalSize = (MI_Uint32)(responsePageHeader->u.s.size + responsePageTrailer->u.s.size) + messagesSize;

    responsePageCombined = (Page*)PAL_Malloc(sizeof(Page) + totalSize + 1);

    if (!responsePageCombined)
        GOTO_FAILED;

    {
        char* data = (char*) (responsePageCombined + 1);
        data[totalSize] = 0;

        memcpy(data, responsePageHeader+1, responsePageHeader->u.s.size);
        data += responsePageHeader->u.s.size;

#ifndef DISABLE_INDICATION
        /* SubscribeResponse messages should NOT contain any indications if they
         * have arrived before the SubscribeResponse message. */
        if (selfCD->wsheader.rqtAction != WSMANTAG_ACTION_SUBSCRIBE)
#endif
        {
            PostInstanceMsg* msg = selfEC->head;
            while (msg != subsetEnd)
            {
                PostInstanceMsg* next = (PostInstanceMsg*)msg->base.next;

                memcpy(data, msg->packedInstancePtr, msg->packedInstanceSize);
                data += msg->packedInstanceSize;

                /* remove message from the list */
                selfEC->totalResponses--;
                selfEC->totalResponseSize -= msg->packedInstanceSize;
                List_Remove(
                    (ListElem**)&selfEC->head,
                    (ListElem**)&selfEC->tail,
                    (ListElem*)msg);
                PostInstanceMsg_Release(msg);

                msg = next;
            }
        }

        memcpy(data, responsePageTrailer+1, responsePageTrailer->u.s.size);
        data += responsePageTrailer->u.s.size;

        responsePageCombined->u.s.size = totalSize;
        responsePageCombined->u.s.next = 0;
    }

    PAL_Free(responsePageHeader); responsePageHeader = 0;
    PAL_Free(responsePageTrailer); responsePageTrailer = 0;

    if( fromRequest )
    {
        STRAND_ASSERTONSTRAND(&selfCD->strand.base);

        result = _CD_SendResponse(
            selfCD,
            HTTP_ERROR_CODE_OK,
            responsePageCombined);
    }
    else
    {
        STRAND_ASSERTONSTRAND(&selfEC->strand.base);

        result = _EC_SendResponse(
            selfEC,
            HTTP_ERROR_CODE_OK,
            responsePageCombined);
    }

    _EC_StartHeartbeatTimer( selfEC );

    goto Done;

failed:
    WSBuf_Destroy(&outBufHeader);
    WSBuf_Destroy(&outBufTrailer);
    if (responsePageCombined) PAL_Free(responsePageCombined);
    if (responsePageHeader) PAL_Free(responsePageHeader);
    if (responsePageTrailer) PAL_Free(responsePageTrailer);

    if( fromRequest )
    {
        STRAND_ASSERTONSTRAND(&selfCD->strand.base);

        // There should be no responses at this point
        DEBUG_ASSERT( NULL == selfEC->head );

        result = _CD_SendFailedResponse(selfCD);
    }
    else
    {
        STRAND_ASSERTONSTRAND(&selfEC->strand.base);

        _EC_ReleaseAllMessages(selfEC);

        result = _EC_SendResponse(
            selfEC,
            HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR,
            NULL);
    }

Done:
    if (result != MI_RESULT_OK)
    {
        DEBUG_ASSERT( MI_RESULT_OK == result );
    }

    _EC_CloseLeft( selfEC, fromRequest );

    _EC_ProcessPendingMessage( selfEC );
}

static void _SendInvokeResponse(
    WSMAN_ConnectionData* selfCD,
    PostInstanceMsg* message)
{
    WSBuf outBuf;
    Page* responsePage = 0;
    ZChar* action = 0;
    MI_Uint32 actionLen;
    Buf buf = BUF_INITIALIZER;

    Buf_AppStrN(&buf, LIT(ZT("http://")));
    Buf_AppStr(&buf, selfCD->wsheader.rqtServer);
#ifndef DISABLE_SHELL
    if (selfCD->wsheader.isShellOperation)
    {
        Buf_AppStrN(&buf, LIT(ZT("/wbem/wsman/1/windows/")));
    }
    else
#endif
    {
        Buf_AppStrN(&buf, LIT(ZT("/wbem/wscim/1/cim-schema/2/")));
    }
    Buf_AppStr(&buf, selfCD->wsheader.rqtClassname);
    Buf_AppStrN(&buf, LIT(ZT("/")));
    Buf_AppStr(&buf, selfCD->wsheader.rqtMethod);

#ifndef DISABLE_SHELL
    if (selfCD->wsheader.isShellOperation)
    {
        Buf_AppStrN(&buf, LIT(ZT("Response")));
    }
#endif
    Buf_AppStrN(&buf, LIT(ZT("\0")));

    action = (ZChar*)buf.data;
    actionLen = (buf.size / sizeof(ZChar)) - 1 ;

    /* Create EnumResponse */
    if (WSBuf_Init(&outBuf, APPROX_ENUM_RESP_ENVELOPE_SIZE + message->packedInstanceSize) != MI_RESULT_OK)
        GOTO_FAILED;

    if (MI_RESULT_OK != WSBuf_CreateSoapResponseHeader(&outBuf,
        action, actionLen, selfCD->wsheader.rqtMessageID))
        GOTO_FAILED;

    if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
        LIT(ZT("</SOAP-ENV:Header>")
        ZT("<SOAP-ENV:Body>"))))
    {
        GOTO_FAILED;
    }

    if (WSBuf_AddVerbatim(
        &outBuf,
        message->packedInstancePtr,
        message->packedInstanceSize) != MI_RESULT_OK)
    {
        GOTO_FAILED;
    }

    if (MI_RESULT_OK != WSBuf_AddLit(
        &outBuf,
        LIT(ZT("</SOAP-ENV:Body>")
        ZT("</SOAP-ENV:Envelope>"))))
    {
        GOTO_FAILED;
    }

    /* all together */
    responsePage = WSBuf_StealPage(&outBuf);

    if (!responsePage)
        GOTO_FAILED;

    /*{
        FILE* f = File_Open("out_test.xml", "a");
        fwrite((char*)(responsePageCombined+1), 1, (size_t)responsePageCombined->u.s.size, f);
        fclose(f);
    }*/

    _CD_SendResponse(
        selfCD,
        HTTP_ERROR_CODE_OK,
        responsePage);

    Buf_Destroy(&buf);

    return;

failed:

    WSBuf_Destroy(&outBuf);
    Buf_Destroy(&buf);

    if (responsePage)
        PAL_Free(responsePage);

    _CD_SendFailedResponse(selfCD);
}

static void _SendSingleResponseHelper(
    WSMAN_ConnectionData* selfCD,
    MI_Uint32 packedResultSize,
    void *packedResultPtr,
    const ZChar* action,
    MI_Uint32 actionSize)
{
    WSBuf   outBuf;
    Page*       responsePage = 0;

    if (WSBuf_Init(&outBuf, APPROX_ENUM_RESP_ENVELOPE_SIZE + packedResultSize) != MI_RESULT_OK)
        GOTO_FAILED;

    if (MI_RESULT_OK != WSBuf_CreateSoapResponseHeader(&outBuf,
        action, actionSize, selfCD->wsheader.rqtMessageID))
        GOTO_FAILED;

    if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
        LIT(ZT("</SOAP-ENV:Header>")
        ZT("<SOAP-ENV:Body>")
        )))
        GOTO_FAILED;

    if (0 < packedResultSize)
    {
        if (WSBuf_AddVerbatim(
            &outBuf,
            packedResultPtr,
            packedResultSize) != MI_RESULT_OK)
        {
            GOTO_FAILED;
        }
    }

    /* trailer */
    if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
        LIT(
        ZT("</SOAP-ENV:Body>")
        ZT("</SOAP-ENV:Envelope>"))))
        GOTO_FAILED;

    /* all together */
    responsePage = WSBuf_StealPage(&outBuf);

    if (!responsePage)
        GOTO_FAILED;

    _CD_SendResponse(
        selfCD,
        HTTP_ERROR_CODE_OK,
        responsePage);

    return;

failed:
    WSBuf_Destroy(&outBuf);
    if (responsePage)
        PAL_Free(responsePage);

    _CD_SendFailedResponse(selfCD);
}

static void _SendSingleInstanceResponse(
    WSMAN_ConnectionData* selfCD,
    PostInstanceMsg* message,
    const ZChar* action,
    MI_Uint32 actionSize)
{
    _SendSingleResponseHelper(selfCD, message->packedInstanceSize,
                                message->packedInstancePtr, action, actionSize);
}

static void _SendSingleSchemaResponse(
    WSMAN_ConnectionData* selfCD,
    PostSchemaMsg* message,
    const ZChar* action,
    MI_Uint32 actionSize)
{
    _SendSingleResponseHelper(selfCD, message->packedSchemaWsmanSize,
                                message->packedSchemaWsmanPtr, action, actionSize);
}

static void _SendEmptyBodyResponse(WSMAN_ConnectionData* selfCD,
                                   const ZChar* action,
                                   MI_Uint32 actionSize)
{
    WSBuf   outBuf;
    Page*       responsePage = 0;

    if (WSBuf_Init(&outBuf, APPROX_ENUM_RESP_ENVELOPE_SIZE) != MI_RESULT_OK)
        GOTO_FAILED;

    if (MI_RESULT_OK != WSBuf_CreateSoapResponseHeader(&outBuf,
        action, actionSize, selfCD->wsheader.rqtMessageID))
        GOTO_FAILED;

    if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
        LIT(ZT("</SOAP-ENV:Header>")
        ZT("<SOAP-ENV:Body/>")
        ZT("</SOAP-ENV:Envelope>")
        )))
        GOTO_FAILED;

    /* all together */
    responsePage = WSBuf_StealPage(&outBuf);

    if (!responsePage)
        GOTO_FAILED;

    _CD_SendResponse(
        selfCD,
        HTTP_ERROR_CODE_OK,
        responsePage);

    return;

failed:
    WSBuf_Destroy(&outBuf);
    if (responsePage)
        PAL_Free(responsePage);

    _CD_SendFailedResponse(selfCD);
}

static void _ProcessEmptyBodyResponse(
    WSMAN_ConnectionData* selfCD)
{
    /* send appropriate response */
    switch (selfCD->wsheader.rqtAction)
    {
    case WSMANTAG_ACTION_PUT:
        _SendEmptyBodyResponse(selfCD, LIT(ZT("http://schemas.xmlsoap.org/ws/2004/09/transfer/PutResponse")));
        break;

    case WSMANTAG_ACTION_DELETE:
        _SendEmptyBodyResponse(selfCD, LIT(ZT("http://schemas.xmlsoap.org/ws/2004/09/transfer/DeleteResponse")));
        break;

    default:
        /* unexpected */
        _CD_SendFaultResponse(
            selfCD,
            NULL,
            WSBUF_FAULT_INTERNAL_ERROR,
            ZT("unexpected internal state"));
        break;
    }
}

static void _SendErrorResponse(
    _In_        WSMAN_ConnectionData*   selfCD,
    _In_opt_    WSMAN_EnumerateContext* sendECStrand,
    _In_        PostResultMsg*          message)
{
    WSBUF_FAULT_CODE faultCode;
    const ZChar* description = 0;

    faultCode = WSBuf_CIMErrorToWSFault(message->result, &description);

    if (message->errorMessage == NULL)
    {
        message->errorMessage = description;
    }

    /* ATTN! consume text from cim_error if supplied */
    _SendCimFaultResponse(selfCD, sendECStrand, faultCode, message);
}


static void _SendErrorResultResponse(
    _In_        WSMAN_ConnectionData*   selfCD,
    _In_opt_    WSMAN_EnumerateContext* sendECStrand,
                MI_Result               result )
{
    PostResultMsg message;
    memset(&message, 0, sizeof(message));
    message.result = result;
    _SendErrorResponse(selfCD, sendECStrand, &message);

    /* This is designed for "simple" CD failure cases */
    if (NULL == sendECStrand &&
        Strand_HaveTimer(&selfCD->strand.base))
    {
        selfCD->cdTimer.cancelledTimer = MI_TRUE;
        Strand_FireTimer( &selfCD->strand.base );
    }
}

/*
 * Processes backlog in enumeration context;
 * once last response is sent, it closes the interactions so the context can be deleted.
 * Regarding timers, it only stops the running timer if a response will be sent.
 */
static void _EC_ProcessEnumResponse(
    _In_    WSMAN_EnumerateContext* selfEC,
            MI_Boolean              pullRequestAttached )
{
    STRAND_ASSERTONSTRAND(&selfEC->strand.base);

    /* If we have been cancelled, it should proceed to allow the strand to
     * finish gracefully. */
    if (selfEC->strand.base.canceled)
    {
        _EC_CheckCloseLeft( selfEC );
        _EC_CheckCloseRight( selfEC );
        return;
    }

    /* do we have connected client to send response to? */
    if( selfEC->strand.base.info.thisClosedOther )
    {
        // TODO: Current code keeps acumulating results if client is not connected (that looks wrong)
        // DEBUG_ASSERT(!selfEC->activeConnection);
        return;
    }

    DEBUG_ASSERT(selfEC->activeConnection);

    /* Operation completed with ERROR */
    if (selfEC->enumerationCompleted && selfEC->finalResult != MI_RESULT_OK)
    {
        if (Strand_HaveTimer(&selfEC->strand.base))
        {
            /* A timer is present, so route the completion through the timer
             * handler to ensure proper timeout handling and clean up */
            selfEC->ecTimer.isPullAttached = pullRequestAttached;
            Strand_FireTimer( &selfEC->strand.base );
            return;
        }

        if (selfEC->errorMessage)
        {
            _SendErrorResponse(selfEC->activeConnection, selfEC, selfEC->errorMessage);
            Message_Release(&selfEC->errorMessage->base);
            selfEC->errorMessage = NULL;
        }
        else
        {
            _SendErrorResultResponse( selfEC->activeConnection, selfEC, selfEC->finalResult);
        }

        _EC_CloseLeft( selfEC, MI_FALSE );
        // This also releases the context on WSMAN
        _EC_CheckCloseRight( selfEC );
        return;
    }

    /* Check if partial response has to be sent (or enumeration is completed) */
    /* Update: send anything that is available once client re-connects with pull */
    /* Send resposne now if:
        - enumeration is complete
        - queue has enough instances to fill entire packet (by size or number)
        - pull request arrives. Normally, network is slower than providers,
            so once client returns with next pull request, lets send all messages
            we have in queue
        - server is stressed (too many instances)
    */
    /*
     TODO: (selfEC->data.requestTag == SubscribeReqTag && selfEC->totalResponses > 0 )
           is a workaround for pull subscription due to timeout response is not implemented yet,
           (1) WSMAN needs to send operation timeout
           response to WSMAN client in case no data is ready to send to
           client yet. So that WSMAN client can eat the response and send
           another pull request. Current behavior is WINRM client sends
           unsubscribe call after certain amount of time, since OMI server
           did not send any response to client.
           (2) We also needs to verify what is the STANDARD behavior once
           there is an indication available but following condition is not
           satisfied yet. Should OMI just send indication directly or Queue
           it up until timeout (OR) totalResponseSize > maxEnvelopSize?
    */
    else if (selfEC->enumerationCompleted ||
        APPROX_ENUM_RESP_ENVELOPE_SIZE + selfEC->totalResponseSize > selfEC->activeConnection->wsheader.maxEnvelopeSize ||
        selfEC->totalResponses >= selfEC->activeConnection->u.wsenumpullbody.maxElements ||
        (pullRequestAttached && selfEC->head) ||
        (selfEC->data.requestTag == SubscribeReqTag && selfEC->totalResponses > 0 )
        )
    {
        /* We have not yet responded to the original SubscribeReq with a
         * SubscribeResponse.  This means that a PostIndication arrived
         * before the SubscribeResponse OR the PostResult with error.  In
         * that case, hold on to it until after the SubscribeResponse has
         * been sent.
         */
        if (selfEC->data.requestTag == SubscribeReqTag &&
            MI_FALSE == selfEC->data.responsed)
        {
            return;
        }

        if (Strand_HaveTimer(&selfEC->strand.base))
        {
            /* A timer is present, so route the completion through the timer
             * handler to ensure proper timeout handling, clean up,
             * and restart if necessary. */
             selfEC->ecTimer.isPullAttached = pullRequestAttached;
            Strand_FireTimer( &selfEC->strand.base );
            return;
        }
        _SendEnumPullResponse(selfEC, MI_FALSE);
    }
#ifndef DISABLE_INDICATION
    /* A Heartbeat event must be sent when no elements are present to send.
     * See R10.2.5-2 and -3. */
    else if (selfEC->ecTimer.forceResult)
    {
        if (Strand_HaveTimer(&selfEC->strand.base))
        {
            /* A timer is present, so route the completion through the timer
             * handler to ensure proper timeout handling, clean up,
             * and restart if necessary. */
             selfEC->ecTimer.isPullAttached = pullRequestAttached;
            Strand_FireTimer( &selfEC->strand.base );
            return;
        }
        // TODO: WinRM Client sent UnsubscribeReq in response to HB event.
        // As a workaround, we send an empty PullResponse instead.
        //_SendHeartbeatResponse( selfEC->activeConnection, selfEC );
        _SendEnumPullResponse(selfEC, MI_FALSE);
        selfEC->ecTimer.forceResult = MI_FALSE;
    }
#endif

    /* release context if last message was sent */
    if (_EC_IsLastMessageSent( selfEC ))
    {
        _EC_CheckCloseLeft( selfEC );
        _EC_CheckCloseRight( selfEC );
    }
}

static void _ProcessResultEnumerationContext(
    WSMAN_EnumerateContext* selfEC,
    PostResultMsg* message )
{
    trace_ProcessResultEnumerationContext( selfEC, message->result );

    /* mark context as 'completed' */
    selfEC->enumerationCompleted = MI_TRUE;
    selfEC->finalResult = message->result;
    Message_AddRef(&message->base);
    selfEC->errorMessage = message;

    //ATTN!: process error text/messages
    _EC_ProcessEnumResponse(selfEC, MI_FALSE);
}

static void _ProcessSubscribeResponseEnumerationContext(
    WSMAN_EnumerateContext* selfEC,
    SubscribeRes* msg )
{
    trace_ProcessSubscribeResponseEnumerationContext( selfEC );

    DEBUG_ASSERT(selfEC->data.requestTag == SubscribeReqTag);

    /* Success Subscribe Response continues the subscription */
    selfEC->finalResult = MI_RESULT_OK; // TODO: this is not actually a final result
    if (MI_FALSE == selfEC->data.responsed)
    {
        selfEC->data.responsed = MI_TRUE;

        if (NULL == selfEC->activeConnection)
        {
            trace_ProcessSubscribeResponseEnumerationContext_TimedOutRequest( selfEC );
            if (!selfEC->strand.base.info.thisClosedOther)
            {
                _EC_CheckCloseRight( selfEC );
            }
            return;
        }
        _SendEnumPullResponse(selfEC, MI_FALSE);

        trace_ProcessSubscribeResponseEnumerationContext_Success( selfEC );
    }
    else
        trace_ProcessSubscribeResponseEnumerationContext_DuplicateSuccess(selfEC);
    return;
}

static void _ProcessInstanceResponse(
    WSMAN_ConnectionData* selfCD,
    PostInstanceMsg* message)
{
    /* send appropriate response */
    switch (selfCD->wsheader.rqtAction)
    {
#ifndef DISABLE_SHELL
        case WSMANTAG_ACTION_SHELL_COMMAND:
        case WSMANTAG_ACTION_SHELL_SIGNAL:
        case WSMANTAG_ACTION_SHELL_RECEIVE:
        case WSMANTAG_ACTION_SHELL_SEND:
#endif
    case 0: /* since invoke does not have strict URI, we got it as 'undefined' */
        _SendInvokeResponse(selfCD, message);
        break;

    case WSMANTAG_ACTION_GET:
        _SendSingleInstanceResponse(selfCD, message, LIT(ZT("http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse")));
        break;

    case WSMANTAG_ACTION_PUT:
        _SendSingleInstanceResponse(selfCD, message, LIT(ZT("http://schemas.xmlsoap.org/ws/2004/09/transfer/PutResponse")));
        break;

    case WSMANTAG_ACTION_CREATE:
        _SendSingleInstanceResponse(selfCD, message, LIT(ZT("http://schemas.xmlsoap.org/ws/2004/09/transfer/CreateResponse")));
        break;

    default:
        /* unexpected */
        _CD_SendFaultResponse(
            selfCD,
            NULL,
            WSBUF_FAULT_INTERNAL_ERROR,
            ZT("unexpected internal state"));
        break;
    }
}

static void _ProcessResultConnectionData(
    WSMAN_ConnectionData* selfCD,
    PostResultMsg* message )
{
    if (selfCD->outstandingRequest)
    {
        // if response was not store yet, store this result (error probably)
        if( NULL == selfCD->single_message )
        {
            _CD_SetSingleMessage(selfCD, &message->base);
        }
    }
    else
    {
        trace_WsmanConnection_ProcessResult_NoRequest( selfCD );
    }
}

static void _ProcessSingleMessageConnectionData(
    WSMAN_ConnectionData* selfCD,
    Message* message)
{
    /* Ignore expired contexts */
    if( selfCD->outstandingRequest )
    {
        _CD_SetSingleMessage(selfCD, message);
    }
    else
    {
        trace_WsmanConnection_ProcessInstance_Expired( selfCD );
    }
}

static void _ProcessInstanceEnumerationContext(
    WSMAN_EnumerateContext* selfEC,
    PostInstanceMsg* message )
{
    trace_WsmanEnum(
            selfEC,
            selfEC->enumerationCompleted,
            selfEC->totalResponses,
            selfEC->totalResponseSize );

    /* Ignore completed contexts */
    if (selfEC->enumerationCompleted || selfEC->strand.base.canceled)
        return;

    /* add-ref message to keep it alive */
    Message_AddRef( &message->base);

    if ((selfEC->totalResponseSize + message->packedInstanceSize > MAX_WSMAN_BUFFER_SIZE)
        || (selfEC->totalResponses == MAX_WSMAN_COLLECTION_SIZE))
    {
        selfEC->pendingMessage = message;
    }
    else
    {
        /* Add it to the list to process when result is posted */
        List_Append(
            (ListElem**)&selfEC->head,
            (ListElem**)&selfEC->tail,
            (ListElem*)message);

        /* Increment total instance size */
        selfEC->totalResponseSize += message->packedInstanceSize;

        /* Increment total number of responses */
        selfEC->totalResponses++;
    }

    /* Check if we need to send response to the client */
    _EC_ProcessEnumResponse(selfEC, MI_FALSE);
}

//-------------------------------------------------------------------------------------------------------------------

static void _InteractionWsman_Transport_Post( _In_ Strand* self_, _In_ Message* msg)
{
    WSMAN_ConnectionData* self = (WSMAN_ConnectionData*)self_;

    DEBUG_ASSERT( HttpRequestMsgTag == msg->tag );

    self->request = (HttpRequestMsg *)msg;

    Message_AddRef( msg );

    // Schedule it as an auxiliary method, so anthing else scheduled already
    // (like a pending ack from Http) is executed first
    StrandBoth_ScheduleAuxLeft( &self->strand, WSMANCONNECTION_STRANDAUX_PROCESSREQUEST );
}

static void _InteractionWsman_Transport_PostControl( _In_ Strand* self, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // not used yet
}

static void _InteractionWsman_Transport_Ack( _In_ Strand* self )
{
    // ignored
}

static void _InteractionWsman_Transport_Close( _In_ Strand* self_ )
{
    WSMAN_ConnectionData* self = (WSMAN_ConnectionData*)self_;

    if( self->outstandingRequest )
    {
        self->outstandingRequest = MI_FALSE;
        Strand_Cancel( &self->strand.base );
    }

    if (Strand_HaveTimer(&self->strand.base))
    {
        Strand_FireTimer( &self->strand.base );
    }

    // Close back on transport (we only do this on transport close)
    StrandBoth_CloseLeft(&self->strand);
}

static void _InteractionWsman_Transport_Finish( _In_ Strand* self_ )
{
    WSMAN_ConnectionData* self = (WSMAN_ConnectionData*)self_;
    _CD_Cleanup( self );
    Strand_Delete( &self->strand.base );
}

static void _CD_RightPostHandler(
    WSMAN_ConnectionData* self )
{
    /* A result was posted from the right. Handle the result now.
     *
     * Note: The result will not actually get posted to the left until
     * the right side closes the operation.
     */
    switch( self->responseMessage->tag )
    {
    case PostResultMsgTag:
        _ProcessResultConnectionData(self, (PostResultMsg*)self->responseMessage );
        break;

    case PostInstanceMsgTag:
    case PostSchemaMsgTag:
        _ProcessSingleMessageConnectionData(self, self->responseMessage );
        break;

    case HttpResponseMsgTag:
        _CD_SetSingleMessage(self, self->responseMessage);
        break;

    default:
        trace_Wsman_InteractionWsman_Right_Post_UnexpectedMessage( self->responseMessage->tag );
        DEBUG_ASSERT(MI_FALSE);
    }

    Message_Release(self->responseMessage);
    self->responseMessage = NULL;

    /* In any case we are not going to send the response now,
     * therefore we dont wait to the Ack from transport,
     * so send an Ack here */
    StrandBoth_ScheduleAckRight( &self->strand );
}

static void _CD_RightCloseHandler(
    WSMAN_ConnectionData* self )
{
    // send stored response now (stored so there are no races before close)
    if( self->outstandingRequest && self->single_message )
    {
        switch( self->single_message->tag )
        {
        case PostSchemaMsgTag:
            _SendSingleSchemaResponse(self, (PostSchemaMsg*)self->single_message, LIT(ZT("http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse")));
            break;
        case PostInstanceMsgTag:
            _ProcessInstanceResponse(self, (PostInstanceMsg*)self->single_message);
            break;
        case HttpResponseMsgTag:
            // response message from enumeration context, just post it to transport
            StrandBoth_PostLeft( &self->strand, self->single_message );
            self->outstandingRequest = MI_FALSE;
            break;
        default:
            {
                PostResultMsg* message = (PostResultMsg*)self->single_message;
                DEBUG_ASSERT( PostResultMsgTag == self->single_message->tag );

                if( MI_RESULT_OK == message->result)
                {
                    _ProcessEmptyBodyResponse(self);
                }
                else
                {
                    _SendErrorResponse(self, NULL, message);
                }
            }
        }
    }

    StrandBoth_CloseRight( &self->strand );
}

/* Since EC uses direct calls to contact CD instead of scheduling them, it will
 * often be the case that both CD.Post and CD.Close are called before the timeout
 * function has a chance to execute even if it is scheduled during Post (before
 * Close is called).  In order to cover those cases, both actions are conditionally
 * executed here to ensure proper clean up.
 */
static void _CD_PostHandlerForFiredTimers(
    WSMAN_ConnectionData* self )
{
    /* Called from "Post"
     * Note: responseMessage becomes NULL once Post has been processed. */
    if ( self->responseMessage )
    {
        _CD_RightPostHandler( self );
    }

    /* Called from "Close"
     * OR Close was called prior to execution of this function AFTER it was
     * scheduled. */
    if (self->strand.infoRight.otherClosedThis)
    {
        _CD_RightCloseHandler( self );
    }
}

//
// Used to track OperationTimeout (and MaxTime) when specified in WSMan requests.
//
// In timeout scenarios, it cancels simple operations (no EnumerationContext) or
// signals the EnumerationContext that a timeout occurred for further processing.
//
static void _InteractionWsman_Transport_Timeout(
    _In_ Strand* self_,
    TimerReason reason )
{
    WSMAN_ConnectionData* self = (WSMAN_ConnectionData*)self_;

    if (TimerReason_Canceled == reason ||
        MI_TRUE == self->cdTimer.cancelledTimer)  // TODO: Remove once TimerReason_Canceled is supported uniformly
    {
        /* The timer was cancelled, so no action should take place */
        trace_WsmanConnectionData_OperationCancelled(self, self->wsheader.rqtAction);
        return;
    }
    else if (TimerReason_ManuallyFired == reason)
    {
        _CD_PostHandlerForFiredTimers(self);
        return;
    }
    else // TimerReason_Expired (timed out)
    {
        trace_WsmanConnectionData_OperationTimeout(self, self->wsheader.rqtAction);
        DEBUG_ASSERT( TimerReason_Expired == reason );

        if (self->responseMessage)
        {
            /* The timeout was detected during Post.
             *
             * A Post was initiated by EC when the timeout occurred,
             * but the Post has not completed and the message has not yet been
             * sent via Close. Complete the Post so that the operation can be Closed.
             */
            _CD_PostHandlerForFiredTimers( self );
            return;
        }
        else if (self->single_message && self->outstandingRequest)
        {
            /* The timeout was detected during Close.
             *
             * A message has been Posted, but Close has not yet sent it.  Send it now.
             */
            _CD_PostHandlerForFiredTimers( self );
            return;
        }
        else if (self->strand.base.info.otherClosedThis)
        {
            /* The timeout was detected during Close.
             *
             * No messages are "in progress" via Post, so it is OK to send a timeout.
             * We cannot call the AUX method here because the EC has already Closed the connection.
             */
            if (self->outstandingRequest)
            {
                _CD_SendFaultResponse(
                    self,
                    NULL,
                    WSBUF_FAULT_TIMED_OUT,
                    ZT("A timeout occurred while processing the operation."));
            }
            StrandBoth_CloseRight( &self->strand );  // TODO: Could also do it via _CD_PostHandlerForFiredTimers, but that would count of on the side-effect of it not posting and closing the connection
            return;
        }
        else
        {
            /* If the operation is related to a WSMAN_EnumerationContext,
             * redirect the timeout there for handling (timeout or partial response) */
            if (WSMANTAG_ACTION_ENUMERATE == self->wsheader.rqtAction ||
                WSMANTAG_ACTION_SUBSCRIBE == self->wsheader.rqtAction ||
                WSMANTAG_ACTION_PULL == self->wsheader.rqtAction)
            {
                WSMAN_EnumerateContext* enumContext = NULL;
                MI_Uint32 enumCtxId = 0;

                /* Since CD has no reference to its EC during SubscribeReq,
                 * one is added to make look up possible. */
                if (WSMANTAG_ACTION_SUBSCRIBE == self->wsheader.rqtAction)
                    enumCtxId = self->enumCtxId;
                else
                    enumCtxId = self->u.wsenumpullbody.enumerationContextID;

                /* find EnumerationContext */
                enumContext = _WSMAN_FindEnumContext(self->wsman, enumCtxId);

                if (!enumContext)
                {
                    _CD_SendFaultResponse(
                        self,
                        NULL,
                        WSBUF_FAULT_DESTINATION_UNREACHABLE,
                        ZT("Enumeration context not found"));
                    _CD_ForceCloseRight(self);
                    return;
                }

                StrandBoth_ScheduleAuxLeft(&enumContext->strand,ENUMERATIONCONTEXT_STRANDAUX_CONNECTION_DATA_TIMEOUT);
            }
            else // Cancel here for simple operations
            {
                // Send Timeout response message since the action didn't complete in time.
                _CD_SendFaultResponse(
                    self,
                    NULL,
                    WSBUF_FAULT_TIMED_OUT,
                    ZT("A timeout occurred while processing the operation."));

                Strand_Cancel(&self->strand.base);
            }
            return;
        }
    }
}

// WSMANCONNECTION_STRANDAUX_PROCESSREQUEST
static void _InteractionWsman_Transport_ProcessRequest(
    _In_ Strand* self_ )
{
    WSMAN_ConnectionData* self = (WSMAN_ConnectionData*)self_;
    HttpRequestMsg * request = self->request;

    DEBUG_ASSERT( NULL != request );
    self->request = NULL;

    // Note that page is taken over in _HttpProcessRequest (or released if failure)
    _HttpProcessRequest(
        self,
        request->headers,
        request->page);

    // request->page freed inside _HttpProcessRequest
    request->page = NULL;
    Message_Release( &request->base );

    // So far all request processing is synchronous so ack here
    // Note that we cannot use StrandBoth_AckLeft as we can abandon the strand inside _HttpProcessRequest
    StrandBoth_ScheduleAckLeft(&self->strand);
}

/*
 * WsmanConnectionData (CD) is a StrandBoth.  This table represents its incoming
 * "left" action handlers.  It parses and processes WSMAN requests from HttpSocket
 * and establishes strand connections to the right.  For simple operations, it
 * forwards them directly to the dispatcher.  For complex operations such as
 * Enumeration, Association, References, and Subscription, it creates or attaches
 * to a WsmanEnumerationContext prior to forwarding the request to the dispatcher.
 *
 * Shutdown Behavior:
 *     CD has no special cancel handling, but its lifetime is closely tied to the
 * lifetime of its HttpSocket.  When the HttpSocket Closes it, it immediately
 * begins shutting itself down by cancelling and Closing to the left.  Shutdown
 * can also be initiated by the 'right' side via Close calls to its 'right' FT.
 * A timeout may also initiate shutdown via Cancel.
 *
 * Features:
 *     1. It has an operation timer to limit the amount of time it will wait for
 *        a response from the right.  Posts from the 'right' will fire this timer
 *        prior to forwarding the message to the 'left'.
 *     2. Incoming Posts from the 'left' are handled via an AUX method to allow
 *        other concurrently scheduled strand operations to complete prior to
 *        beginning processing of a new request.
 */
static StrandFT _InteractionWsman_TransportFT = {
    _InteractionWsman_Transport_Post,
    _InteractionWsman_Transport_PostControl,
    _InteractionWsman_Transport_Ack,
    NULL,   // cancel will go pass thru if necessary
    _InteractionWsman_Transport_Close,
    _InteractionWsman_Transport_Finish,
    _InteractionWsman_Transport_Timeout,
    _InteractionWsman_Transport_ProcessRequest,
    NULL,
    NULL,
    NULL,
    NULL };

static void _CD_TriggerOrHandle(
    WSMAN_ConnectionData* self )
{
    if (Strand_HaveTimer(&self->strand.base))
    {
        Strand_FireTimer( &self->strand.base );
    }
    else
    {
        _CD_PostHandlerForFiredTimers( self );
    }
}

static void _InteractionWsman_Right_Post( _In_ Strand* self_, _In_ Message* msg)
{
    WSMAN_ConnectionData* self = (WSMAN_ConnectionData*)self_;

    DEBUG_ASSERT( NULL != self );

    trace_WsmanConnection_PostingMsg(
        msg,
        msg->tag,
        MessageName(msg->tag),
        msg->operationId,
        self->strand.base.info.interaction.other,
        self_,
        self->strand.infoRight.interaction.other );

    if( HttpResponseMsgTag != msg->tag )
    {
        PrintProviderMsg(msg);
    }

    /* Preparation for routing the response to the common handler.
     * The common handler will ACK the request after processing it. */
    if ( self->responseMessage )
        Message_Release(self->responseMessage);
    Message_AddRef(msg);
    self->responseMessage = msg;

    _CD_TriggerOrHandle( self );
}

static void _InteractionWsman_Right_PostControl( _In_ Strand* self, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // not used yet
}

static void _InteractionWsman_Right_Ack( _In_ Strand* self_)
{
    WSMAN_ConnectionData* self = (WSMAN_ConnectionData*)self_;

    trace_WsmanConnection_Ack( self_, self->strand.infoRight.interaction.other );
    // Only used for initial open message ack (no "semantic" secondary messages on WSMAN)

    //
    // Doesn't need to ack to left side (http layer) here
    // since left was aleady acked upon opending this strand
    //
}

static void _InteractionWsman_Right_Close( _In_ Strand* self_ )
{
    WSMAN_ConnectionData* self = (WSMAN_ConnectionData*)self_;

    trace_WsmanConnection_Close( self_, self->strand.infoRight.interaction.other, self->outstandingRequest, self->single_message );

    _CD_TriggerOrHandle( self );
}

/*
 * WsmanConnectionData (CD) is a StrandBoth.  This table represents its incoming
 * "right" action handlers.  It forwards Posted messages to its HttpSocket.  An
 * initial Post is held and immediately ACK'd.  When the 'right' component calls
 * Close, CD Posts the message to its HttpSocket.
 *
 * Shutdown Behavior:
 *     After it Posts via a call to its Close method, it will Close to the
 *     'right'.  Once its 'left' processes the message it will get Closed
 *     from the 'left' and Finish.  A timeout can also trigger shutdown, as
 *     described in the CD's 'left' FT.
 */
static StrandFT _InteractionWsman_RightFT = {
    _InteractionWsman_Right_Post,
    _InteractionWsman_Right_PostControl,
    _InteractionWsman_Right_Ack,
    NULL,   // cancel will go pass thru if necessary
    _InteractionWsman_Right_Close,
    NULL,   // self delete
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL };

//-------------------------------------------------------------------------------------------------------------------

static void _InteractionWsmanEnum_Left_Ack( _In_ Strand* self_)
{
    PAL_UNUSED( self_ );  // Implemented to prevent ACK passthrough since this is StrandBoth
}

static void _InteractionWsmanEnum_Left_Cancel( _In_ Strand* self_)
{
    WSMAN_EnumerateContext* self = (WSMAN_EnumerateContext*)self_;

    _EC_CheckCloseLeft( self );
    _EC_CheckCloseRight( self );
}

static void _InteractionWsmanEnum_Left_Close( _In_ Strand* self_)
{
    // do nothing
}

static void _InteractionWsmanEnum_Finish( _In_ Strand* self_)
{
    WSMAN_EnumerateContext* self = (WSMAN_EnumerateContext*)self_;

    trace_WsmanEnum_Finish( self_ );

    if (NULL != self->errorMessage)
        Message_Release(&self->errorMessage->base);

#ifdef CONFIG_ENABLE_DEBUG
    // invalidate struct
    memset( ((char*)self) + sizeof(self->strand), 0xcd, sizeof(*self)-sizeof(self->strand) );
#endif

    Strand_Delete( &self->strand.base );
}

static void _PostHandlerForFiredTimers(
    WSMAN_EnumerateContext* self )
{
    /* The timer was fired prior to sending a PullResponse.  Send it now
     * and restart the timer. */
    _EC_ProcessEnumResponse(self, self->ecTimer.isPullAttached);
}

/*
 * Tracks Heartbeat timeouts for subscriptions.
 */
static void _InteractionWsmanEnum_Left_Timeout(
    _In_ Strand* self_,
    TimerReason reason )
{
    WSMAN_EnumerateContext* self = (WSMAN_EnumerateContext*)self_;

    if (TimerReason_Canceled == reason ||
        self->ecTimer.cancelledTimer)  // TODO: Remove once TimerReason_Canceled is supported uniformly
    {
        /* The timer was cancelled, so no action should take place */
        trace_WsmanEnumerationcontext_HeartbeatCancelled(self, self->enumerationContextID);
        self->enumerationCompleted = MI_TRUE;
        return;
    }
    else if( TimerReason_ManuallyFired == reason )
    {
        trace_Wsman_ExpiredTimerForEnumerate(self, self->enumerationContextID);

        _PostHandlerForFiredTimers( self );
        return; /* Prevents shutdown handling from occuring here */
    }
    else
    {
        /* TimerReason_Canceled should never happen here as it always fires
         * the timer before a close
         */
        DEBUG_ASSERT( TimerReason_Expired == reason );

        if (NULL != self->activeConnection &&
            WSMANTAG_ACTION_PULL == self->activeConnection->wsheader.rqtAction)
        {
            trace_WsmanEnumerationcontext_HeartbeatTimeout(self, self->enumerationContextID);

            /* Send what instances are available OR a heartbeat event.
             * Return early to prevents shutdown handling from occuring here
             */
            self->ecTimer.forceResult = MI_TRUE;
            _PostHandlerForFiredTimers( self );
            return; /* Prevents shutdown handling from occuring here */
        }

        /* Else:
         * Heartbeat expired with NO PULL.  Shutdown subscription, but don't
         * send a message because there is no activeConnection
         */
        trace_WsmanEnumerationcontext_HeartbeatMissingPull(self, self->enumerationContextID);
        DEBUG_ASSERT(NULL == self->activeConnection);  // TODO: What about unsubscribeAttach?

        self->enumerationCompleted = MI_TRUE;

        /* Cancel anything outgoing there */
        Strand_Cancel(&self->strand.base);
        _EC_CheckCloseRight( self );
    }
}

static void _EC_Left_Attached( _In_ WSMAN_EnumerateContext* self )
{
    DEBUG_ASSERT( NULL != self->attachingConnection );
    DEBUG_ASSERT( NULL == self->activeConnection );
    self->activeConnection = (WSMAN_ConnectionData*)self->attachingConnection;
    self->attachingConnection = NULL;

    // Receive the Re-Open
    Strand_AcceptOpenAsyncFromStrandBoth( &self->strand.base, &self->activeConnection->strand );
}

// ENUMERATIONCONTEXT_STRANDAUX_PULLATTACHED
static void _InteractionWsmanEnum_Left_PullAttached( _In_ Strand* self_)
{
    WSMAN_EnumerateContext* self = (WSMAN_EnumerateContext*)self_;

    _EC_Left_Attached( self );

    if( self->strand.base.canceled )
    {
        _CD_SendFaultResponse(self->activeConnection, self, WSBUF_FAULT_DESTINATION_UNREACHABLE, ZT("Enumeration context not found"));
        _EC_CloseLeft( self, MI_FALSE );
        // This also releases the context on WSMAN
        _EC_CheckCloseRight( self );
    }
    else
    {
        _EC_ProcessEnumResponse(self, MI_TRUE);
    }
}

/* ENUMERATIONCONTEXT_STRANDAUX_UNSUBSCRIBEATTACHED */
static void _InteractionWsmanEnum_Left_UnsubscribeAttached( _In_ Strand* self_)
{
    WSMAN_EnumerateContext* self = (WSMAN_EnumerateContext*)self_;
    /* Mark the subscribe operation as cancelled, so any indication post will be ignored */
    Strand_Cancel(self_);
    _EC_ReleasePendingMessage(self);
}

/* ENUMERATIONCONTEXT_STRANDAUX_CONNECTION_DATA_TIMEOUT */
static void _InteractionWsmanEnum_Left_ConnectionDataTimeout( _In_ Strand* self_)
{
    WSMAN_EnumerateContext* self = (WSMAN_EnumerateContext*)self_;

    trace_WSManEnumerationContext_CD_Timeout_notifier(self);

    if (NULL == self->activeConnection)
    {
        /* EC sent a response via CD while this method was scheduled, but had
         * not yet executed.  In that case, there is nothing to do because
         * a response was already sent and the connection no longer exists. */
        trace_WSManEnumerateContext_CD_Timeout_on_inactive_context();
        return;
    }

    if (WSMANTAG_ACTION_ENUMERATE == self->activeConnection->wsheader.rqtAction ||
        WSMANTAG_ACTION_SUBSCRIBE == self->activeConnection->wsheader.rqtAction)
    {
        DEBUG_ASSERT( MI_FALSE == Strand_HaveTimer(self_) );

        trace_WSManEnumerateContext_CD_Timeout_during_initial_operation(
            self->activeConnection->wsheader.rqtAction );

        /* Send Timeout response message since the action didn't complete in time. */
        _CD_SendFaultResponse(
            self->activeConnection,
            self,
            WSBUF_FAULT_TIMED_OUT,
            ZT("A timeout occurred while processing the operation."));

        _EC_CheckCloseLeft( self );

        /* Cancel the operation since the CD timed out while the EC and lower layers
         * were processing the request. */
        Strand_Cancel(&self->strand.base);
        _EC_CheckCloseRight( self );
    }
    else
    {
        /* Note: Timeout on a PullRequest should not be treated as a terminating failure
         * for the associated subscription ("making the data source invalid"). */

        DEBUG_ASSERT(WSMANTAG_ACTION_PULL == self->activeConnection->wsheader.rqtAction); // TODO: This must be kept in sync with the caller

        /* While waiting to execute this method, if:
         * Post occurred on CD ||
         * Close occurred on CD
         * Then treat this as a No-op */
        if (self->activeConnection->responseMessage ||
            self->activeConnection->single_message ||
            self->strand.base.info.thisClosedOther)
        {
            trace_WSManEnumerationContext_CD_Timeout_Notification_Ignored(
                self->activeConnection->responseMessage,
                self->activeConnection->single_message,
                self->strand.base.info.thisClosedOther);
        }
        else
        {
            /* Pull will have already called _EC_Left_Attached, so it should not be done again
             * send what instances are available OR a heartbeat event.
             * The return may be ignored because it doesn't affect the action taken here. */
            self->ecTimer.forceResult = MI_TRUE;
            _EC_ProcessEnumResponse(self, MI_TRUE);

            /* Return to avoid closing early.  If HB timer is active, it will
             * fire and Close will happen at a later time.  If it is not
             * present, close will happen within the function. */
            return;
        }
    }

    /* Close anything outgoing here to spur sending of the response. */
    _EC_CheckCloseLeft( self );
}

/*
 * WsmanEnumerationContext (EC) is a StrandBoth.  This table represents its
 * incoming "left" action handlers.  These functions will be called
 * exclusively by its connected CD.
 *
 * Shutdown Behavior:
 *     EC shuts down in a number of ways.  _EC_CheckCloseRight is the main
 *     controller of the timing of actual shutdown.  Examine calls to that
 *     function to see all shutdown scenarios.
 *     1. CD calls Cancel, typically the result of an Unsubscribe or a
 *         ECONNRESET termination of a running operation.
 *     2. The last message for a request has been sent.
 *     3. An error occurred during processing of a request.
 *     4. Its hearbeat timer expired without a pull attached.
 *     5. An incoming request from CD timed out prior to EC sending an
 *         initial response.
 *
 * Features:
 *     1. It has a heartbeat timer that tracks the amount of time between
 *         responses that are sent to the client.  The timer must be stopped
 *         prior to Posting a message to its CD.
 *     2. PullAttached prevents multiple CDs from connecting to the same EC
 *         at the same time.  Only one may be attached.  The same applies to
 *         Unsubscribe.
 *     3. ConnectionDataTimeout processes CD timeouts.  This function allows
 *         coordination of responses so that EC can send partial results.
 *         For example, if MaxElements has not been reached, it will trigger
 *         a Post with the messages in its queue.
 */
static StrandFT _InteractionWsmanEnum_Left_FT = {
    NULL,   // Post from left not used
    NULL,   // Post Control from left not used
    _InteractionWsmanEnum_Left_Ack,
    _InteractionWsmanEnum_Left_Cancel,
    _InteractionWsmanEnum_Left_Close,
    _InteractionWsmanEnum_Finish,
    _InteractionWsmanEnum_Left_Timeout,
    _InteractionWsmanEnum_Left_PullAttached,
    _InteractionWsmanEnum_Left_UnsubscribeAttached,
    _InteractionWsmanEnum_Left_ConnectionDataTimeout,
    NULL,
    NULL };

static void _InteractionWsmanEnum_Right_Post( _In_ Strand* self_, _In_ Message* msg)
{
    WSMAN_EnumerateContext* self = (WSMAN_EnumerateContext*)self_;

    DEBUG_ASSERT( NULL != self );

    trace_WsmanEnum_PostingMsg(
        msg,
        msg->tag,
        MessageName(msg->tag),
        msg->operationId,
        self->strand.base.info.interaction.other,
        self_,
        self->strand.infoRight.interaction.other);

    PrintProviderMsg(msg);

    switch( msg->tag )
    {
    case PostResultMsgTag:
        _ProcessResultEnumerationContext(self, (PostResultMsg*)msg );
        break;

    case SubscribeResTag:
        /* Heartbeat timer should start after this (if used) */
        DEBUG_ASSERT(MI_FALSE == Strand_HaveTimer(&self->strand.base));
        _ProcessSubscribeResponseEnumerationContext(self, (SubscribeRes*)msg );
        break;

    case PostInstanceMsgTag:
        _ProcessInstanceEnumerationContext(self, (PostInstanceMsg*)msg );
        break;

    case PostIndicationMsgTag:
        /* See definition of PostIndicationMsg, it is derived from PostInstanceMsg */
        _ProcessInstanceEnumerationContext(self, (PostInstanceMsg*)msg );
        break;

    default:
        trace_Wsman_InteractionWsmanEnum_Right_Post_UnexpectedMessage( msg->tag );
        DEBUG_ASSERT(MI_FALSE);
    }

    if( NULL == self->pendingMessage)
    {
        StrandBoth_ScheduleAckRight( &self->strand );
    }
    /* Else we will Ack once we can accomodate pendingMessage in WSMan's queue. */
}

static void _InteractionWsmanEnum_Right_Ack( _In_ Strand* self_)
{
    WSMAN_EnumerateContext* self = (WSMAN_EnumerateContext*)self_;

    trace_WsmanEnum_Ack( self_, self->strand.infoRight.interaction.other );

    // We dont need to pass any ack here to the left, just do nothing
}

static void _InteractionWsmanEnum_Right_Close( _In_ Strand* self_)
{
    // do nothing
}

/*
 * WsmanEnumerationContext (EC) is a StrandBoth.  This table represents its
 * incoming 'right' action handlers.  These functions will be called
 * exclusively by whatever component handled the initial request in the
 * dispatcher.  The only function that really does anything is Post.  It
 * processes messages from lower layers and determines when responses should
 * be sent to the 'left' via a most-likely attached CD representing a WSMAN
 * Pull.  It will process result and instance Posts.
 *
 * Shutdown Behavior:
 *     As with its 'left' FT, _EC_CheckCloseRight initiates shutdown for EC.
 *     The scenarios are described in its 'left' FT.
 *
 * Features:
 *     1. It uses a heartbeat timer as described in its 'left' FT.
 *     2. ACKs may not be sent immediately for every Post.  If the timer is
 *         fired as a result of the Post, it will be delayed and ACK'd in the
 *         timer handler.  Also, it if hits flow control where the message
 *         queue has reached its limit, the posted message will become
 *         "pending" and won't be ACK'd until the pending message is processed.
 */
static StrandFT _InteractionWsmanEnum_Right_FT = {
    _InteractionWsmanEnum_Right_Post,
    NULL,   // not used
    _InteractionWsmanEnum_Right_Ack,
    NULL,   // cancel goes pass thru
    _InteractionWsmanEnum_Right_Close,
    _InteractionWsmanEnum_Finish,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL };

//-------------------------------------------------------------------------------------------------------------------

#if defined(CONFIG_ENABLE_WCHAR)
static Page* _XMLToWideCharPage(const char* data, size_t size)
{
    size_t wsize = size * sizeof(wchar_t);
    Page* page = (Page*)PAL_Malloc(sizeof(Page) + wsize);
    wchar_t* p;

    if (!page)
        return NULL;

    page->u.s.independent = 0;
    page->u.s.next = NULL;
    page->u.s.size = wsize;

    p = (wchar_t*)(page + 1);

    while (size--)
    {
        *p++ = *data++;
    }

    return page;
}
#endif /* defined(CONFIG_ENABLE_WCHAR) */

void ResetUserData(const HttpHeaders* headers)
{
    if (headers->password)
    {
        size_t len = strlen(headers->password);
        memset((void*)headers->password, 0, len);
        MemoryUnlock((void*)headers->password, len);
    }
}

static void _HttpCallbackOnNewConnection(
    _Inout_     InteractionOpenParams*  interactionParams )
{
    WSMAN* self = (WSMAN*)interactionParams->callbackData;
    WSMAN_ConnectionData* selfConnectionData;

    DEBUG_ASSERT(NULL != self);

    DEBUG_ASSERT( NULL != interactionParams->interaction );
    DEBUG_ASSERT( NULL == interactionParams->msg );
    DEBUG_ASSERT( NULL != interactionParams->callbackData );

    selfConnectionData = (WSMAN_ConnectionData*)StrandBoth_New(
                            STRAND_DEBUG( WsmanConnection )
                            &_InteractionWsman_TransportFT,
                            &_InteractionWsman_RightFT,
                            sizeof(WSMAN_ConnectionData),
                            0,
                            interactionParams );

    if (!selfConnectionData)
    {
        trace_HttpCallbackOnNewConnection_OutOfMemory();
        Strand_FailOpen( interactionParams );
    }
    else
    {
        selfConnectionData->wsman = self;
    }
}

static void _HttpProcessRequest(
    _In_    WSMAN_ConnectionData*   selfCD,
    _In_    const HttpHeaders*      headers,
    _In_    Page*                   page)
{
    XML * xml = (XML *) PAL_Calloc(1, sizeof (XML));
#if defined(CONFIG_ENABLE_WCHAR)
    int adjustForBom = 0;
#endif

    STRAND_ASSERTONSTRAND(&selfCD->strand.base);

    if (!xml)
    {
        trace_OutOfMemory();
        _CD_SendFailedResponse(selfCD);
        if( NULL != page )
        {
            PAL_Free(page);
        }
        return;
    }

    memcpy(xml, &selfCD->wsman->xml, sizeof(XML));

    /* Cleanup connection data, since it may still store allocated
     * pointers from previous operation
     */
    _CD_Cleanup(selfCD);

    selfCD->httpHeaders = headers;

#if defined(CONFIG_ENABLE_HTTPHEADERS)

    /* Make copy of HTTP headers */

    if (headers->headersSize)
    {
        memcpy(selfCD->headers, headers->headers,
            sizeof(HttpHeader) * headers->headersSize);
        selfCD->headersSize = headers->headersSize;
    }

#endif

    /* Determine whether WinRM client */

    if (headers->userAgent &&
        Strcasecmp(headers->userAgent, "Microsoft WinRM Client") == 0)
    {
        selfCD->userAgent = USERAGENT_WINRM;
    }

    /* Verify content type */
    if (!headers->contentType ||
        (Strcasecmp(headers->contentType,"application/soap+xml") != 0 &&
         Strcasecmp(headers->contentType,"text/xml") != 0))
    {
        trace_Wsman_InvalidMissingContentType(tcs(PageData(page)));

        _CD_SendErrorFailedResponse(selfCD, HTTP_ERROR_CODE_BAD_REQUEST);
        goto Done;
    }

#if defined(CONFIG_ENABLE_WCHAR)
        if (headers->charset &&
            Strcasecmp(headers->charset,"utf-8") == 0)
        {
            /* Convert this page to wide-character */
            Page* wpage = _XMLToWideCharPage(
                (const char*)(page + 1),
                page->u.s.size);

            if (!wpage)
            {
                trace_OutOfMemory();
                _CD_SendFailedResponse(selfCD);
                goto Done;
            }

            PAL_Free(page);
            page = wpage;
        }
        else if (headers->charset &&
            Strcasecmp(headers->charset,"utf-16") == 0)
        {
            adjustForBom = 1;
        }
        else
        {
            trace_Wsman_CharsetIsNotSupported(
                headers->charset);
            _CD_SendFaultResponse(selfCD, NULL, WSBUF_FAULT_ENCODING_LIMIT,
                ZT("only utf 8 is supported"));
            goto Done;
        }
#else
    if (headers->charset &&
        Strcasecmp(headers->charset,"utf-8") != 0)
    {
        trace_Wsman_CharsetIsNotSupported(
            headers->charset);
        _CD_SendFaultResponse( selfCD, NULL, WSBUF_FAULT_ENCODING_LIMIT,
            PAL_T("only utf 8 is supported"));
        goto Done;
    }
#endif /* defined(CONFIG_ENABLE_WCHAR) */

    /*
    Check the authentication/authorization type. It has to be "Basic" (That is the one that OMI supports).
    In case it is not "Basic", we need to inform the user that this is not supported auth.
    Note: the old behavior was, in the http layer. We check if the auth is not "Basic", then we don't set
    the username and password, so it will fail here in WSMAN layer, but the error will be 500 error code
    which means internal server error which doesn't clarify anything to the user. Now we are returning 401
    which will be interpereted by the client and give a meaningful message.
    Also, in the wsman specification, it was mentioned that we should return 401 (HTTP_ERROR_CODE_UNAUTHORIZED)
    with the list of all supported authentication, and they mentioned that this authentication check is prefered
    to be in the HTTP layer not here but this will be a future change.
    */
    if(headers->authorization && Strncasecmp(headers->authorization, AUTHENTICATION_BASIC, AUTHENTICATION_BASIC_LENGTH) != 0)
    {
        trace_Wsman_UnsupportedAuthentication(headers->authorization);
        _CD_SendErrorFailedResponse(selfCD, HTTP_ERROR_CODE_UNAUTHORIZED);
        goto Done;
    }

    if (!headers->username || !headers->password ||
        0 != AuthenticateUser(headers->username, headers->password))
    {
        trace_Wsman_AuthenticationFailed(
            headers->username);

        _CD_SendErrorFailedResponse(selfCD, HTTP_ERROR_CODE_UNAUTHORIZED);
        ResetUserData(headers);
        goto Done;
    }
    ResetUserData(headers);

    if (0 != LookupUser(headers->username, &selfCD->authInfo.uid, &selfCD->authInfo.gid))
    {
        trace_GetUserUidGid_Failed(
            headers->username);

        _CD_SendFailedResponse(selfCD);
        goto Done;
    }

    if (page->u.s.size == 0)
    {
        trace_Wsman_BufferSizeIsZero();

        _CD_SendFailedResponse(selfCD);
        goto Done;
    }

#if defined(CONFIG_ENABLE_WCHAR)
    if (adjustForBom == 1)
    {
        /* Skip over the BOM */
        ZChar *startOfBuffer = (ZChar*)(page + 1);
        XML_SetText(xml, startOfBuffer+1);
    }
    else
    {
        XML_SetText(xml, (ZChar*)(page + 1));
    }
#else
    XML_SetText(xml, (ZChar*)(page + 1));
#endif

    /* Parse SOAP Envelope */
    if (WS_ParseSoapEnvelope(xml) != 0 ||
        xml->status)
    {
        trace_Wsman_FailedParseSOAPEnvelope();
        _CD_SendFaultResponse(selfCD, NULL, WSBUF_FAULT_INTERNAL_ERROR, xml->message);
        goto Done;
    }

    /* Parse WS header */
    if (WS_ParseWSHeader(xml, &selfCD->wsheader, selfCD->userAgent) != 0 ||
        xml->status)
    {
        trace_Wsman_FailedParseWSHeader();
        _CD_SendFaultResponse(selfCD, NULL, WSBUF_FAULT_INTERNAL_ERROR, xml->message);
        goto Done;
    }

    /* Validate header */
    if (_ValidateHeader(selfCD) != 0)
    {
        goto Done;
    }

    /* See if this is a Identify request */

    if (!selfCD->wsheader.foundAction)
    {
        _HandleIdentifyRequest(
            selfCD,
            xml);
        goto Done;
    }

    /* Take ownership of this page so we can refer to XML strings */
    _CD_SetPage(selfCD, page);
    page = NULL;

    DEBUG_ASSERT( !selfCD->strand.infoRight.opened || ( selfCD->strand.infoRight.thisClosedOther && selfCD->strand.infoRight.otherClosedThis ) );
    selfCD->outstandingRequest = MI_TRUE;

    /* Parse body and send request to the dispatcher */
    switch (selfCD->wsheader.rqtAction)
    {
        case WSMANTAG_ACTION_ENUMERATE:
        {
            _ParseValidateProcessEnumerateRequest(selfCD, xml);
            break;
        }
        case WSMANTAG_ACTION_PULL:
        {
            _ParseValidateProcessPullRequest(selfCD, xml);
            break;
        }
        case WSMANTAG_ACTION_RELEASE:
        {
            _ParseValidateProcessReleaseRequest(selfCD, xml);
            break;
        }
        case WSMANTAG_ACTION_GET:
        {
            _ParseValidateProcessGetRequest(selfCD, xml);
            break;
        }
        case WSMANTAG_ACTION_PUT:
        {
            _ParseValidateProcessPutRequest(selfCD, xml);
            break;
        }
        case WSMANTAG_ACTION_DELETE:
        {
            _ParseValidateProcessDeleteRequest(selfCD, xml);
            break;
        }
        case WSMANTAG_ACTION_CREATE:
        {
            _ParseValidateProcessCreateRequest(selfCD, xml);
            break;
        }
#ifndef DISABLE_INDICATION
        case WSMANTAG_ACTION_SUBSCRIBE:
        {
            _ParseValidateProcessSubscribeRequest(selfCD, xml);
        }
        break;
        case WSMANTAG_ACTION_UNSUBSCRIBE:
        {
            _ParseValidateProcessUnsubscribeRequest(selfCD, xml);
        }
        break;
#endif /* ifndef DISABLE_INDICATION */
#ifndef DISABLE_SHELL
        case WSMANTAG_ACTION_SHELL_COMMAND:
        case WSMANTAG_ACTION_SHELL_SIGNAL:
        case WSMANTAG_ACTION_SHELL_RECEIVE:
        case WSMANTAG_ACTION_SHELL_SEND:
#endif
        case 0: /* since invoke does not have strict URI, we got it as 'undefined' */
        {
            _ParseValidateProcessInvokeRequest(selfCD, xml);
            break;
        }
        default:
        {
            /* unsupported action */
            trace_Wsman_UnsupportedAction( selfCD->wsheader.rqtAction );
            _CD_SendFaultResponse(selfCD, NULL, WSBUF_FAULT_NOT_SUPPORTED, 0);
            break;
        }
    }

Done:
    // we should not do anything strand related at this point
    // as we could have abandoned the strand when opening to the right

    PAL_Free(xml);
    if( NULL != page )
    {
        PAL_Free(page);
    }
}

/*
**==============================================================================
**
** Public definitions:
**
**==============================================================================
*/
MI_Result WSMAN_New_Listener(
    _Out_       WSMAN**                 selfOut,
    _In_opt_    Selector*               selector,       // optional, maybe NULL
    _In_opt_    unsigned short          http_port,      // 0 to disable
    _In_opt_    unsigned short          https_port,     // 0 to disable
    _In_opt_z_  const char*             sslCipherSuite, /* NULL to disable */
    _In_opt_    Server_SSL_Options      sslOptions,     // 0 no special options
    _In_        OpenCallback            callback,
    _In_        void*                   callbackData,
    _In_opt_    const WSMAN_Options*    options)
{
    WSMAN* self;
    MI_Result r;
    HttpOptions tmpHttpOptions = DEFAULT_HTTP_OPTIONS;

    /* Check parameters */
    if (!selfOut)
        return MI_RESULT_INVALID_PARAMETER;

    /* Clear output parameter */
    *selfOut = NULL;

    /* Allocate structure */
    {
        self = (WSMAN*)PAL_Calloc(1, sizeof(WSMAN));

        if (!self)
            return MI_RESULT_FAILED;
    }

    /* Save the callback and callbackData */
    self->callback = callback;
    self->callbackData = callbackData;
    self->numEnumerateContexts = 0;
    self->deleting = MI_FALSE;

    /*ATTN! slector can be null!*/
    self->selector = selector;

    /* Set the magic number */
    self->magic = _MAGIC;

    // options
    if( NULL == options )
    {
        WSMAN_Options tmpOptions = DEFAULT_WSMAN_OPTIONS;

        self->options = tmpOptions;
    }
    else
    {
        self->options = *options;

        // Set HTTP options
        tmpHttpOptions.enableTracing = options->enableHTTPTracing;
    }

    /* create a server */
    r = Http_New_Server(
        &self->http,
        selector,
        http_port,
        https_port,
        sslCipherSuite,
        sslOptions,
        _HttpCallbackOnNewConnection,
        self,
        &tmpHttpOptions );

    if (MI_RESULT_OK != r)
    {
        WSMAN_Delete(self);
        return r;
    }

    RecursiveLock_Init(&self->lock);

    /* Initialize xml parser */
    XML_Init(&self->xml);

    XML_RegisterNameSpace(&self->xml, 's',
        ZT("http://www.w3.org/2003/05/soap-envelope"));

    XML_RegisterNameSpace(&self->xml, 'a',
        ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing"));

    XML_RegisterNameSpace(&self->xml, 'w',
        ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd"));

    XML_RegisterNameSpace(&self->xml, 'n',
        ZT("http://schemas.xmlsoap.org/ws/2004/09/enumeration"));

    XML_RegisterNameSpace(&self->xml, 'b',
        ZT("http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd"));

    XML_RegisterNameSpace(&self->xml, 'p',
        ZT("http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd"));

    XML_RegisterNameSpace(&self->xml, 'i',
        ZT("http://schemas.dmtf.org/wbem/wsman/identity/1/wsmanidentity.xsd"));

    XML_RegisterNameSpace(&self->xml, 'x',
        ZT("http://www.w3.org/2001/XMLSchema-instance"));

    XML_RegisterNameSpace(&self->xml, MI_T('e'),
        ZT("http://schemas.xmlsoap.org/ws/2004/08/eventing"));

#ifndef DISABLE_SHELL
    XML_RegisterNameSpace(&self->xml, MI_T('h'),
        ZT("http://schemas.microsoft.com/wbem/wsman/1/windows/shell"));
#endif

    *selfOut = self;

    return MI_RESULT_OK;
}

MI_Result WSMAN_Delete(
    WSMAN* self)
{
    size_t count;

    /* Check parameters */
    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

    /* Check magic number */
    if (self->magic != _MAGIC)
        return MI_RESULT_INVALID_PARAMETER;

    RecursiveLock_Acquire(&self->lock);

    // that would take care of canceling all connections (and perhaps some enumeration contexts)
    Http_Delete(self->http);

    // initiate cancel of all outstanding contexts
    _WSMAN_CancelAllEnumerateContexts(self);

    self->deleting = MI_TRUE;

    while( ( count = self->numEnumerateContexts ) > 0 )
    {
        RecursiveLock_Release(&self->lock);

        CondLock_Wait(
            (ptrdiff_t)self, &self->numEnumerateContexts, count, CONDLOCK_DEFAULT_SPINCOUNT);

        RecursiveLock_Acquire(&self->lock);
    }

    /* Clear magic number */
    self->magic = 0xDDDDDDDD;

    RecursiveLock_Release(&self->lock);

    /* Free self pointer */
    PAL_Free(self);

    return MI_RESULT_OK;
}

MI_Result WSMAN_Run(
    WSMAN* self,
    MI_Uint64 timeoutUsec)
{
    /* Run the selector */
    return Http_Run(self->http, timeoutUsec);
}

#ifndef DISABLE_INDICATION

/*
static void _SendHeartbeatResponse(
    WSMAN_ConnectionData* selfCD,
    WSMAN_EnumerateContext* selfEC )
{
    WSBuf outBuf;
    Page* responsePage = 0;

    if (WSBuf_Init(&outBuf, APPROX_ENUM_RESP_ENVELOPE_SIZE) != MI_RESULT_OK)
        GOTO_FAILED;

    if (MI_RESULT_OK != WSBuf_CreateSoapResponseHeader(
        &outBuf,
        LIT(ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman/Heartbeat")),
        selfCD->wsheader.rqtMessageID))
        GOTO_FAILED;

    if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
        LIT(ZT("</SOAP-ENV:Header>")
        ZT("<SOAP-ENV:Body>")
        )))
        GOTO_FAILED;

    / * trailer * /
    if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
        LIT(
        ZT("</SOAP-ENV:Body>")
        ZT("</SOAP-ENV:Envelope>"))))
        GOTO_FAILED;

    / * all together * /
    responsePage = WSBuf_StealPage(&outBuf);

    if (!responsePage)
        GOTO_FAILED;

    _EC_SendResponse(
        selfEC,
        HTTP_ERROR_CODE_OK,
        responsePage);

    / * Restart the timer after sending a response * /
    _EC_StartHeartbeatTimer( selfEC );

    / * Forces the response beyond the CD and initiates CD shutdown * /
    _EC_CloseLeft( selfEC, MI_FALSE );

    return;

failed:
    WSBuf_Destroy(&outBuf);
    if (responsePage)
        PAL_Free(responsePage);

    _CD_SendFaultResponse(
        selfCD,
        selfEC,
        WSBUF_FAULT_ENCODING_LIMIT,
        ZT("insufficient envelope size for heartbeat transferring"));
}
*/

static void _SendUnsubscribeResponse(
    WSMAN_ConnectionData* selfCD )
{
    WSBuf outBuf;
    Page* responsePage = 0;

    if (WSBuf_Init(&outBuf, APPROX_ENUM_RESP_ENVELOPE_SIZE) != MI_RESULT_OK)
        GOTO_FAILED;

    if (MI_RESULT_OK != WSBuf_CreateSoapResponseHeader(
        &outBuf,
        LIT(ZT("http://schemas.xmlsoap.org/ws/2004/08/eventing/UnsubscribeResponse")),
        selfCD->wsheader.rqtMessageID))
        GOTO_FAILED;

    if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
        LIT(ZT("</SOAP-ENV:Header>\n<SOAP-ENV:Body/>\n</SOAP-ENV:Envelope>")
        )))
        GOTO_FAILED;

    /* all together */
    responsePage = WSBuf_StealPage(&outBuf);

    if (!responsePage)
        GOTO_FAILED;

    _CD_SendResponse(
        selfCD,
        HTTP_ERROR_CODE_OK,
        responsePage);

    return;

failed:
    WSBuf_Destroy(&outBuf);
    if (responsePage)
        PAL_Free(responsePage);

    _CD_SendFaultResponse(
        selfCD,
        NULL,
        WSBUF_FAULT_ENCODING_LIMIT,
        ZT("insufficient envelope size for heartbeat transferring"));
}

static MI_Result _WSMAN_AddSubscribeResponse(
    WSBuf *wsbuf,
    WSMAN_EnumerateContext* selfEC)
{
    if (MI_RESULT_OK != WSBuf_AddLit(wsbuf,
            LIT(ZT("<e:SubscribeResponse>"))))
            GOTO_FAILED;
    //
    // Add subscription identifier
    //
    //    <e:SubscriptionManager>
    //      <a:Address>http://localhost:5985/wsman</a:Address>
    //      <a:ReferenceProperties>
    //        <w:ResourceURI>http://schemas.dmtf.org/wbem/wscim/1/*</w:ResourceURI>
    //        <e:Identifier>0860D524-6F0A-46FE-B95E-7CB0C1A2C1B8</e:Identifier>
    //      </a:ReferenceProperties>
    //    </e:SubscriptionManager>
    //    <e:Expires>[xs:dateTime | xs:duration]</e:Expires>
    //
    {
        if (MI_RESULT_OK != WSBuf_AddLit(wsbuf,
            LIT(ZT("<e:SubscriptionManager>"))))
            GOTO_FAILED;
        if (MI_RESULT_OK != WSBuf_AddLit(wsbuf,
            LIT(ZT("<wsa:ReferenceProperties>"))))
            GOTO_FAILED;
        if (MI_RESULT_OK != WSBuf_AddLit(wsbuf,
            LIT(ZT("<wsman:ResourceURI>"))))
            GOTO_FAILED;
        if (MI_RESULT_OK != WSBuf_AddLit(wsbuf,
            LIT(ZT("http://schemas.dmtf.org/wbem/wscim/1/*"))))
            GOTO_FAILED;
        if (MI_RESULT_OK != WSBuf_AddLit(wsbuf,
            LIT(ZT("</wsman:ResourceURI>"))))
            GOTO_FAILED;
        if (MI_RESULT_OK != WSBuf_AddLit(wsbuf,
            LIT(ZT("<e:Identifier>"))))
            GOTO_FAILED;

        trace_Wsman_AddSubscribeResponse( selfEC, selfEC->enumerationContextID );

        if (MI_RESULT_OK != WSBuf_AddUint32(wsbuf,selfEC->enumerationContextID))
            GOTO_FAILED;
        if (MI_RESULT_OK != WSBuf_AddLit(wsbuf,
            LIT(ZT("</e:Identifier>"))))
            GOTO_FAILED;
        if (MI_RESULT_OK != WSBuf_AddLit(wsbuf,
            LIT(ZT("</wsa:ReferenceProperties>"))))
            GOTO_FAILED;
        if (MI_RESULT_OK != WSBuf_AddLit(wsbuf,
            LIT(ZT("</e:SubscriptionManager>"))))
            GOTO_FAILED;
    }

    return MI_RESULT_OK;

failed:
    return MI_RESULT_FAILED;
}

static int _ValidateSubscribeRequest(
    WSMAN_ConnectionData* selfCD)
{
    if (!selfCD->wsheader.rqtClassname || !selfCD->wsheader.rqtNamespace ||
        !selfCD->u.wsenumpullbody.filter || !selfCD->u.wsenumpullbody.dialect)
    {
        trace_Wsman_ParametersMissingInSubscribeRequest();
        _CD_SendFaultResponse(
            selfCD,
            NULL,
            WSBUF_FAULT_INTERNAL_ERROR,
            ZT("mandatory parameters (className, namesapce) are not provided for subscribe request"));
        return -1;
    }

    /*R8.2.3; DSP226
      wsmen:Enumerate/wsman:MaxElements
      (optional) indicates the maximum number of items the consumer is willing to accept in the
      EnumerateResponse
      It plays the same role as wsmen:Pull/wsmen:MaxElements. When this element is absent, its
      implied value is 1. */
    if (!selfCD->u.wsenumpullbody.maxElements)
        selfCD->u.wsenumpullbody.maxElements = 1;

    if (selfCD->u.wsenumpullbody.heartbeat.exists &&
        selfCD->u.wsenumpullbody.heartbeat.value.isTimestamp)
    {
        trace_Wsman_InvalidHeartbeatType();
        _CD_SendFaultResponse(
            selfCD,
            NULL,
            WSBUF_FAULT_INVALID_HEARTBEAT,
            ZT("Heartbeat must be xs:duration"));
        return -1;
    }

    if (selfCD->u.wsenumpullbody.connectionRetry.exists)
    {
        trace_Wsman_UnsupportedConnectionRetry();
        _CD_SendFaultResponse(
            selfCD,
            NULL,
            WSBUF_FAULT_CONNECTION_RETRY_NOT_SUPPORTED,
            ZT("Connection retry is not supported"));
        return -1;
    }

    if (selfCD->u.wsenumpullbody.initialBookmark &&
        Tcslen(selfCD->u.wsenumpullbody.initialBookmark) == 0)
    {
        trace_Wsman_SubscribeBookmark_Empty();
        _CD_SendFaultResponse(
            selfCD,
            NULL,
            WSBUF_FAULT_BOOKMARK_INVALID_FORMAT,
            ZT("The specified bookmark is empty"));
        return -1;
    }

    return 0;
}

static int _ValidateUnsubscribeRequest(
    WSMAN_ConnectionData* selfCD)
{
    /* validate selfCD->wsheader.contextID */
    return 0;
}

static void _ProcessSubscribeRequest(
    WSMAN_ConnectionData* selfCD)
{
    SubscribeReq* msg;
    WSMAN_EnumerateContext* enumContext;

    /* create EnumerateContext */
    enumContext = _CD_CreateEnumContext(selfCD);

    if (!enumContext)
    {
        _CD_SendFailedResponse(selfCD);
        return;
    }

    /* Create new request */
    msg = SubscribeReq_New(_NextOperationID(),
        WSMANFlag | _convertWSMANtoMsgEnumerationMode(selfCD->u.wsenumpullbody.enumerationMode));

    if (!msg || (_GetHTTPHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK) || (_GetWSManHeaderOpts(selfCD, &msg->base) != MI_RESULT_OK))
    {
        _CD_ProcessEnumFailed( selfCD, enumContext );
        return;
    }

    if (selfCD->wsheader.rqtNamespace)
    {
        msg->nameSpace = Batch_Tcsdup(msg->base.base.batch, selfCD->wsheader.rqtNamespace);
        if (NULL == msg->nameSpace)
        {
            trace_OutOfMemory();
            _CD_SendFailedResponse(selfCD);
            SubscribeReq_Release(msg);
            return;
        }
    }

    if (selfCD->wsheader.rqtClassname)
    {
        msg->className = Batch_Tcsdup(msg->base.base.batch, selfCD->wsheader.rqtClassname);
        if (NULL == msg->className)
        {
            trace_OutOfMemory();
            _CD_SendFailedResponse(selfCD);
            SubscribeReq_Release(msg);
            return;
        }
    }

    if (selfCD->u.wsenumpullbody.filter)
    {
        msg->filter = Batch_Tcsdup(msg->base.base.batch, selfCD->u.wsenumpullbody.filter);
        if (NULL == msg->filter)
        {
            trace_OutOfMemory();
            _CD_SendFailedResponse(selfCD);
            SubscribeReq_Release(msg);
            return;
        }
    }

    if (selfCD->u.wsenumpullbody.dialect)
    {
        msg->language = Batch_Tcsdup(msg->base.base.batch, selfCD->u.wsenumpullbody.dialect);
        if (NULL == msg->language)
        {
            trace_OutOfMemory();
            _CD_SendFailedResponse(selfCD);
            SubscribeReq_Release(msg);
            return;
        }
    }

    if (selfCD->u.wsenumpullbody.initialBookmark)
    {
        msg->bookmark = Batch_Tcsdup(msg->base.base.batch, selfCD->u.wsenumpullbody.initialBookmark);
        if (NULL == msg->bookmark)
        {
            trace_OutOfMemory();
            _CD_SendFailedResponse(selfCD);
            SubscribeReq_Release(msg);
            return;
        }
    }

    enumContext->sendBookmarks = selfCD->u.wsenumpullbody.sendBookmarks;

    AuthInfo_Copy( &msg->base.authInfo, &selfCD->authInfo );

    /* attach request tag to context */
    enumContext->data.requestTag = msg->base.base.tag;

    /* mark the response flag to false */
    enumContext->data.responsed = MI_FALSE;

    if (selfCD->u.wsenumpullbody.heartbeat.exists)
    {
        /* Move heartbeat value to EC so it will be preserved across
         * connections and requests */
        if (0 != DatetimeToUsec(&selfCD->u.wsenumpullbody.heartbeat.value, &enumContext->ecTimer.heartbeatInterval))
        {
            enumContext->ecTimer.heartbeatInterval = WSMAN_TIMEOUT_DEFAULT;
#if defined(_MSC_VER)
            trace_Wsman_UnableToconvertDatetimeToUsec_MSCVER( enumContext->ecTimer.heartbeatInterval, enumContext->data.requestTag );
#else
            trace_Wsman_UnableToconvertDatetimeToUsec_POSIX( enumContext->ecTimer.heartbeatInterval, enumContext->data.requestTag );
#endif
        }
    }

    _OpenRightEnum(selfCD,enumContext,&msg->base,MI_FALSE);

    SubscribeReq_Release(msg);
}

static void _ProcessUnsubscribeRequest(
    WSMAN_ConnectionData* selfCD)
{
    WSMAN_EnumerateContext* enumContext;
    trace_ProcessUnsubscribeRequest( selfCD );

    enumContext = _WSMAN_FindAndDeleteEnumContext( selfCD->wsman, selfCD->wsheader.contextID );

    if( NULL == enumContext )
    {
        trace_Wsman_UnableToFindContext( selfCD->wsheader.contextID );
    }
    else
    {
        //only one unsubscribe can attach and the entry got deleted in _WSMAN_FindAndDeleteEnumContext call
        StrandBoth_ScheduleAuxLeft(&enumContext->strand,ENUMERATIONCONTEXT_STRANDAUX_UNSUBSCRIBEATTACHED);
    }

    _SendUnsubscribeResponse(selfCD);

    _CD_ForceCloseRight(selfCD);

    trace_ProcessUnsubscribeRequest_Complete(
        selfCD, 0, MessageName(UnsubscribeReqTag));
}

static void _ParseValidateProcessSubscribeRequest(
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
    /* Parse subscribe request/body */
    if (WS_ParseSubscribeBody(xml, &selfCD->u.wsenumpullbody) != 0)
    {
        trace_Wsman_UnableToParseXMLSubscribe();
        _CD_SendFailedResponse(selfCD);
        return;
    }

    /* Validate subscribe request body */
    if (_ValidateSubscribeRequest(selfCD) != 0)
    {
        /* appropriate error code was already sent to the client */
        return;
    }

    /* Process reqest */
    _ProcessSubscribeRequest(selfCD);
}

static void _ParseValidateProcessUnsubscribeRequest(
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
        /* Parse enumerate request/body */
    if (WS_ParseUnsubscribeBody(xml, &selfCD->u.wsenumpullbody) != 0)
    {
        trace_Wsman_UnableToParseXMLUnsubscribe();
        _CD_SendFailedResponse(selfCD);
        return;
    }

    /* Validate enumerate request body */
    if (_ValidateUnsubscribeRequest(selfCD) != 0)
    {
        /* appropriate error code was already sent to the client */
        return;
    }

    /* Process reqest */
    _ProcessUnsubscribeRequest(selfCD);
}

#endif /* #ifndef DISABLE_INDICATION */
