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
#include "wsman.h"
#include "wsbuf.h"
#include "wsmanparser.h"
#include <http/http.h>
#include <base/time.h>
#include <xml/xml.h>
#include <base/log.h>
#include <base/result.h>
#include <base/strings.h>
#include <base/user.h>
#include <base/memman.h>
#include <io/io.h>
#include <base/base.h>

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
        LOGD((ZT("goto failed: %u"), __LINE__)); \
        goto failed; \
    }
#else
# define GOTO_FAILED goto failed
#endif

/*
**==============================================================================
**
** Local definitions:
**
**==============================================================================
*/

#define WSMAN_MAX_ENVELOPE_SIZE (250 * 1024)

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

/* These tags are used as magic numbers as well as to distinguish connection data strucutre from enumeration context */
#define DATA_TAG_CONNECTION_DATA 0x17CDDC11
#define DATA_TAG_ENUMERATION_CONTEXT 0xAB70900D

/* Maximum number of enumeration contexts stored at the same time
    effectively limits number of concurent enumerations */
#define WSMAN_MAX_ENUM_CONTEXTS 64

struct _WSMAN
{
    MI_Uint32 magic;
    WSMANCallback callback;
    void* callbackData;
    Http* http;
    Selector* selector;

    /* configurable options */
    WSMAN_Options options;

    /* Array of enumeration contexts:
        each 'pull' will look for corresponding context
    */
    WSMAN_EnumerateContext* enumerateContexts[WSMAN_MAX_ENUM_CONTEXTS];

    /* Cached xml parser with all namespaces registered */
    XML xml;
};

/* Represents state of connection including buffers, unsent packets, states etc */
struct _WSMAN_ConnectionData
{
    /* Since message's data can point to either ConnectionData or EnumerationContext,
        both strucutres need some generic base property - tag;
        in addition, tag used as magic number */
    MI_Uint32   tag;

    /* Link to http layer */
    void* httpConnectionHandle;

    /* Requestor information */
    uid_t uid;
    gid_t gid;

    /* Attributes of the request */
    WSMAN_WSHeader  wsheader;
    union
    {
        /* Actual type is defined by wsheader.rqtAction field */
         WSMAN_WSEnumeratePullBody wsenumpullbody;
    }
    u;

    /* Request page (buffer for most pointers inside header/body structures) */
    Page* page;

    /* for single-instance repsonses, we keep mesage until result received to avoid
        conflicts with keep-alive enabled */
    PostInstanceMsg* single_message;

    /* Number of consumers of this structure:
        connected client, outstanding request to the provider and timer */
    MI_Uint32 refcounter;

    /* response data */
    /* only valid for enumerate/pull requests */
    MI_Uint32 enumerateContextID;

    /* flag indicates that response was not sent yet to the client */
    MI_Boolean outstandingRequest;

    /* True if WinRM client */
    UserAgent userAgent;
};

/* Enumeration context:
    'derived' from socket Handler, so it can subscribe for timeouts */

struct _WSMAN_EnumerateContext
{
    /* Since message's data can point to either ConnectionData or EnumerationContext,
        both strucutres need some generic base property - tag;
        in addition, tag used as magic number */
    MI_Uint32   tag;

    /* based member - can be added to 'selector' for timeout support */
    Handler     base;

    /* response data */
    /* Linked list of messages to send */
    PostInstanceMsg* head;
    PostInstanceMsg* tail;

    /* Total size of all instances in response queue */
    MI_Uint32   totalResponseSize;

    /* NUmber of messages in repsonse queue */
    MI_Uint32   totalResponses;

    /* Number of consumers of this structure:
       reference from enum-context-list in WSMAN, outstanding request to the provider and timer */
    MI_Uint32   refcounter;

    /* lower 16 bits is aninxed in self->enumerateContexts, upper 16 bits are random data (for validation) */
    MI_Uint32   enumerationContextID;
    MI_Result   finalResult;
    /* indicates that 'Result' recevied form provider and stored in finalResult */
    MI_Boolean  enumerationCompleted;
    /* Indicates that context has expired (either by timer or by Release request)
    and all repsonses form the provider has to be ignored */
    MI_Boolean  expired;

    /* pointer to current active connection - either Enumerate or Pull request */
    WSMAN_ConnectionData*   activeConnection;
};

/* forward declarations */
static void _CD_Release(
    WSMAN_ConnectionData* selfConnectionData);

static void _SendEnumPullResponse(
    WSMAN* self,
    WSMAN_EnumerateContext* selfEC);

static MI_Boolean _ProcessEnumResponse(
    WSMAN* self,
    WSMAN_EnumerateContext* selfEC,
    MI_Boolean attachingPullRequest);

static void _WSMAN_ReleaseEnumerateContext(
    WSMAN* self,
    MI_Uint32   enumerationContextID);

/************************************************************************\
*   Helper funcitons
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
static void _EC_ReleaseAllMessages(
    WSMAN_EnumerateContext* self)
{
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
}

static void _EC_SetActiveConnection(
    WSMAN_EnumerateContext* self,
    WSMAN_ConnectionData* selfCD)
{
    if (self->activeConnection)
        _CD_Release(self->activeConnection);

    self->activeConnection = selfCD;
    if (self->activeConnection)
    {
        self->activeConnection->refcounter++;
        self->activeConnection->enumerateContextID = self->enumerationContextID;
    }
}

static void _EC_Release(
    WSMAN_EnumerateContext* self,
    MI_Boolean freeAllMessages)
{
    if (--self->refcounter == 0)
    {
        /* Delete all queued messages*/
        _EC_ReleaseAllMessages(self);

        /* release active connection (if exist) */
        _EC_SetActiveConnection(self, 0);

#ifdef CONFIG_ENABLE_DEBUG
        /* invalidate struct */
        memset(self, 0xcd, sizeof(*self));
#endif
        free(self);
    }
    else if (freeAllMessages)
    {
        /* Delete all queued messages*/
        _EC_ReleaseAllMessages(self);
    }
}

static MI_Boolean _EC_TimeoutCallback(
    Selector* sel,
    Handler* handler,
    MI_Uint32 mask,
    MI_Uint64 currentTimeUsec)
{
    /* since 'base' is not the first member in EC struct,
        adjust pointer as appropriate */
    WSMAN_EnumerateContext* self = (WSMAN_EnumerateContext*)
        (((char*)handler) - offsetof(WSMAN_EnumerateContext, base));

    MI_UNUSED(sel);
    MI_UNUSED(currentTimeUsec);

    if (mask & SELECTOR_TIMEOUT)
    {
        LOGD((ZT("timeout: Removing Enumeration with enumerate context %u"), self->enumerationContextID));

        /* remove context only from wsman list; selector will remove it automatically,
            once 'false' returned */
        _WSMAN_ReleaseEnumerateContext(
            (WSMAN*)self->base.data, self->enumerationContextID);

        /* once 'false' returned, selector will remove handler,
            so actual handling happens in next 'if' */
        return MI_FALSE;
    }

    if (mask & (SELECTOR_REMOVE | SELECTOR_DESTROY))
    {
        _EC_Release(self, MI_TRUE);
    }

    return MI_TRUE;
}

/************************************************************************\
*   WSman operations
\************************************************************************/
static WSMAN_EnumerateContext* _WSMAN_AllocateEnumContext(
    WSMAN* self)
{
    MI_Uint32   enumerationContextID;
    WSMAN_EnumerateContext* enumContext;

    /* Find empty slot */
    for (enumerationContextID = 0; enumerationContextID < MI_COUNT(self->enumerateContexts); enumerationContextID++)
    {
        if (!self->enumerateContexts[enumerationContextID])
            break;
    }

    if (MI_COUNT(self->enumerateContexts) == enumerationContextID)
    {
        LOGW((ZT("Cannot allocate new enumerate context - too many concurrent enumerations") ));
        return 0;   /* no more slots available */
    }

    enumContext = (WSMAN_EnumerateContext*)calloc(1, sizeof(WSMAN_EnumerateContext));

    if (!enumContext)
        return 0;

    /* Store reference to a new context */
    self->enumerateContexts[enumerationContextID] = enumContext;

    /* set tag/magic */
    enumContext->tag = DATA_TAG_ENUMERATION_CONTEXT;

    /* Add random data to the context-id */
    enumerationContextID |= (rand() & 0xFFFF) << 16;
    enumContext->enumerationContextID = enumerationContextID;

    /* set ref-counter to 1, since it's referred by enumerateContexts array now */
    enumContext->refcounter = 1;
    return enumContext;
}

static WSMAN_EnumerateContext* _WSMAN_FindEnumContext(
    WSMAN* self,
    MI_Uint32   enumerationContextID)
{
    MI_Uint32 index = enumerationContextID & 0xFFFF;

    /* ATTN: add logging here! */
    /* verify that context exist and has the same id as required */
    if (index < MI_COUNT(self->enumerateContexts) &&
        self->enumerateContexts[index] &&
        self->enumerateContexts[index]->enumerationContextID == enumerationContextID)
        return self->enumerateContexts[index];

    return 0;
}


static void _WSMAN_ReleaseEnumerateContext(
    WSMAN* self,
    MI_Uint32   enumerationContextID)
{
    MI_Uint32 index = enumerationContextID & 0xFFFF;

    if (index < MI_COUNT(self->enumerateContexts) &&
        self->enumerateContexts[index] &&
        self->enumerateContexts[index]->enumerationContextID == enumerationContextID)
    {
        /* mark handler for removing:
            we cannot remove it directly since we are inside selector's callback;
            settign time to current will trigger timeout/context removal */
        MI_Uint64 currentTimeUsec = 0;

        Time_Now(&currentTimeUsec);
        self->enumerateContexts[index]->base.fireTimeoutAt = currentTimeUsec;
        self->enumerateContexts[index]->expired = MI_TRUE;

        /* dec-ref context: note: it can still be alive if porvider has outstanding request */
        _EC_Release(self->enumerateContexts[index], MI_FALSE);
        self->enumerateContexts[index] = 0;
    }
}

static void _WSMAN_ReleaseAllEnumerateContexts(
    WSMAN* self)
{
    MI_Uint32 index;

    for (index = 0; index < MI_COUNT(self->enumerateContexts); index++ )
    {
        if (self->enumerateContexts[index])
        {
            /* delete timer if was set */
            Selector_RemoveHandler(self->selector, &self->enumerateContexts[index]->base);

            /* dec-ref context: note: it can still be alive if porvider has outstanding request */
            _EC_Release(self->enumerateContexts[index], MI_FALSE);
            self->enumerateContexts[index] = 0;
        }
    }
}

static void _WSMAN_SetUpdateTimer(
    WSMAN* self,
    WSMAN_EnumerateContext* selfEC)
{
    int timerHasBeenAdded = 0;
    if (selfEC->base.fireTimeoutAt)
    {
        timerHasBeenAdded = 1;
    }

    /* extend time */
    {
        MI_Uint64 currentTimeUsec = 0;

        if (MI_RESULT_OK == Time_Now(&currentTimeUsec))
        {
            selfEC->base.fireTimeoutAt =
                currentTimeUsec + self->options.timeoutEnumContextUsec;
        }
    }

    /* check if timer was already added */
    if (!timerHasBeenAdded)
    {
        /* add timer - first time called */
        selfEC->base.sock = INVALID_SOCK;
        selfEC->base.data = self;
        selfEC->base.callback = _EC_TimeoutCallback;
        selfEC->base.type = WSMAN_HANDLER;

        /* increment counter - will be decremented in callback/remove */
        if (MI_RESULT_OK == Selector_AddHandler(self->selector, &selfEC->base))
            selfEC->refcounter++;
    }
}

/************************************************************************\
*   connection data operations
\************************************************************************/
MI_INLINE void _CD_SetPage(
    WSMAN_ConnectionData* selfConnectionData,
    Page*   page)
{
    if (selfConnectionData->page)
        free(selfConnectionData->page);

    selfConnectionData->page = page;
}

MI_INLINE void _CD_SetSingleMessage(
    WSMAN_ConnectionData* selfConnectionData,
    PostInstanceMsg* single_message)
{
    if (selfConnectionData->single_message)
        PostInstanceMsg_Release(selfConnectionData->single_message);

    selfConnectionData->single_message = single_message;

    if (selfConnectionData->single_message)
        Message_AddRef(&selfConnectionData->single_message->base);
}

static void _CD_Cleanup(
    WSMAN_ConnectionData* selfConnectionData)
{
    _CD_SetPage(selfConnectionData, 0);
    _CD_SetSingleMessage(selfConnectionData, 0);

    selfConnectionData->userAgent = USERAGENT_UNKNOWN;

    /* free allocated instance/batch */
    if (selfConnectionData->wsheader.instanceBatch)
    {
        /* destroying batch takes care of instance and instanceBatch members */
        Batch_Destroy(selfConnectionData->wsheader.instanceBatch);
        selfConnectionData->wsheader.instanceBatch = 0;
        selfConnectionData->wsheader.instance = 0;
    }
    memset(&selfConnectionData->wsheader, 0, sizeof(selfConnectionData->wsheader));
}

static void _CD_Release(
    WSMAN_ConnectionData* selfConnectionData)
{
    if (--selfConnectionData->refcounter == 0)
    {
        _CD_Cleanup(selfConnectionData);

        free(selfConnectionData);
    }
}

static MI_Result _SendResponse(
    Http* self,
    void* httpConnectionHandle,
    int httpErrorCode,
    Page** data)
{
#if defined(CONFIG_ENABLE_WCHAR)
    {
        /* Convert page to wire XML character representation */

        size_t count = (*data)->u.s.size / sizeof(ZChar);

        Page* page = (Page*)malloc(sizeof(Page) + (count * sizeof(char)));

        if (!page)
            return MI_RESULT_FAILED;

        memset(page, 0, sizeof(Page));
        page->u.s.size = count;

        {
            ZChar* src = (ZChar*)(*data + 1);
            char* dest = (char*)(page + 1);

            while (count--)
                *dest++ = (char) *src++;
        }

#if 0
        Zprintf(ZT("PAGE{%.*s}"), (int)(page->u.s.size), (char*)(page + 1));
#endif

        return Http_SendResponse(
            self,
            httpConnectionHandle,
            httpErrorCode,
            &page);
    }
#else /* defined(CONFIG_ENABLE_WCHAR) */

    return Http_SendResponse(
        self,
        httpConnectionHandle,
        httpErrorCode,
        data);

#endif /* !defined(CONFIG_ENABLE_WCHAR) */
}

static void _SendCimFaultResponse(
    Http* http,
    WSMAN_ConnectionData* selfCD,
    WSBUF_FAULT_CODE faultCode,
    const PostResultMsg* message)
{
    Page* responsePage = WSBuf_CreateFaultResponsePage(
        faultCode,
        selfCD->wsheader.unknownMandatoryTag,
        selfCD->wsheader.rqtMessageID,
        message);

    _SendResponse(http,
        selfCD->httpConnectionHandle,
        HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR,
        &responsePage);

    selfCD->outstandingRequest = MI_FALSE;

    if (responsePage)
        free(responsePage);
}

static void _SendFaultResponse(
    Http* http,
    WSMAN_ConnectionData* selfCD,
    WSBUF_FAULT_CODE faultCode,
    const ZChar* descriptionText)
{
    /* This method is called when there is Non-Cim error occured ...
     * so sending MI_RESULT_OK
     */
    PostResultMsg message;
    memset(&message, 0, sizeof(message));
    message.result = MI_RESULT_OK;
    message.errorMessage = descriptionText;

    _SendCimFaultResponse(
        http,
        selfCD,
        faultCode,
        &message);
}

static void _SendReleaseResponse(
    WSMAN* self,
    WSMAN_ConnectionData* selfCD)
{
    Page* responsePage = WSBuf_CreateReleaseResponsePage(
        selfCD->wsheader.rqtMessageID);

    _SendResponse(self->http, selfCD->httpConnectionHandle,
        HTTP_ERROR_CODE_OK,
        &responsePage);

    selfCD->outstandingRequest = MI_FALSE;

    if (responsePage)
        free(responsePage);
}

static int _ValidateHeader(
    Http* http,
    WSMAN_ConnectionData* selfCD)
{
    if (selfCD->wsheader.unknownMandatoryTag)
    {
        _SendFaultResponse(http, selfCD, WSBUF_FAULT_NOT_UNDERSTOOD, 0);
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
#if defined(CONFIG_OS_WINDOWS)
        LOGW((ZT("wsman: requested envelope size (%d) is too small; ")
            ZT("expected at least 8K"), (int)selfCD->wsheader.maxEnvelopeSize));
#else
        LOGW((ZT("wsman: requested envelope size (%d) is too small; "
            "expected at least 8K"), (int)selfCD->wsheader.maxEnvelopeSize));
#endif
        _SendFaultResponse(http, selfCD, WSBUF_FAULT_ENCODING_LIMIT, 0);
        return -1;
    }

    /* Limit envelope size to server's max */
    if (selfCD->wsheader.maxEnvelopeSize == 0 ||
        selfCD->wsheader.maxEnvelopeSize > WSMAN_MAX_ENVELOPE_SIZE)
    {
        selfCD->wsheader.maxEnvelopeSize = WSMAN_MAX_ENVELOPE_SIZE;
    }

    /* verify action for invoke */
    if (selfCD->wsheader.foundAction &&
        0 == selfCD->wsheader.rqtAction &&
        (!selfCD->wsheader.rqtClassname || !selfCD->wsheader.rqtMethod))
    {
        LOGW((ZT("wsman: unknown custom action")));

        _SendFaultResponse(http, selfCD, WSBUF_FAULT_NOT_SUPPORTED,
            ZT("unknown custom action"));
        return -1;
    }

    return 0;
}

static int _ValidateEnumerateRequest(
    Http* http,
    WSMAN_ConnectionData* selfCD)
{
    /* If it has reference params, it must be an association request */
    MI_Instance* referenceParameters =
        selfCD->u.wsenumpullbody.associationFilter.referenceParameters;

    if (referenceParameters)
    {
        selfCD->wsheader.rqtNamespace = referenceParameters->nameSpace;
        selfCD->wsheader.rqtClassname = referenceParameters->classDecl->name;
    }
    else if (!selfCD->wsheader.rqtClassname || !selfCD->wsheader.rqtNamespace)
    {
#if defined(CONFIG_OS_WINDOWS)
        LOGW((ZT("wsman: mandatory parameters (className, namespace) ")
            ZT("are missing for enumerate request")));

        _SendFaultResponse(
            http,
            selfCD,
            WSBUF_FAULT_INTERNAL_ERROR,
            ZT("mandatory parameters (className, namespace) ")
                ZT("are missing for enumerate request"));
#else
        LOGW((ZT("wsman: mandatory parameters (className, namespace) "
            "are missing for enumerate request")));

        _SendFaultResponse(
            http,
            selfCD,
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
    Http* http,
    WSMAN_ConnectionData* selfCD)
{
    MI_UNUSED(http);
    //R8.2.3; DSP226
    //wsmen:Enumerate/wsman:MaxElements
    //(optional) indicates the maximum number of items the consumer is willing to accept in the
    //EnumerateResponse
    //It plays the same role as wsmen:Pull/wsmen:MaxElements. When this element is absent, its
    //implied value is 1.
    if (!selfCD->u.wsenumpullbody.maxElements)
        selfCD->u.wsenumpullbody.maxElements = 1;

    return 0;
}

static void _ProcessEnumerateRequest(
    Http* http,
    void* httpConnectionHandle,
    WSMAN* self,
    WSMAN_ConnectionData* selfCD)
{
    EnumerateInstancesReq* msg;
    WSMAN_EnumerateContext* enumContext;

    /* create EnumerateContext */
    enumContext = _WSMAN_AllocateEnumContext(self);

    if (!enumContext)
    {
        Http_SendErrorResponse(http, httpConnectionHandle, HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
        selfCD->outstandingRequest = MI_FALSE;
        return;
    }

    /* link new context to current EnumRequest */
    _EC_SetActiveConnection(enumContext, selfCD);


    // Create new request.
    msg = EnumerateInstancesReq_New(/*_NextMsgID()*/ 1,
        WSMANFlag | _convertWSMANtoMsgEnumerationMode(selfCD->u.wsenumpullbody.enumerationMode));

    if (!msg)
    {
        _WSMAN_ReleaseEnumerateContext(self, enumContext->enumerationContextID);
        selfCD->enumerateContextID = 0;
        Http_SendErrorResponse(http, httpConnectionHandle, HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
        selfCD->outstandingRequest = MI_FALSE;
        return;
    }

    /* Set the user agent */
    msg->base.userAgent = selfCD->userAgent;

    /* In case when client does not support optimized enumeration,
        send empty Enum-response with correct enumerate context */
    if (!selfCD->u.wsenumpullbody.allowOptimization)
    {
        _SendEnumPullResponse(self, enumContext);
        _EC_SetActiveConnection(enumContext, 0);
        _WSMAN_SetUpdateTimer(self, enumContext);
    }

    msg->nameSpace = Batch_Zdup(msg->base.batch, selfCD->wsheader.rqtNamespace);
    msg->className = Batch_Zdup(msg->base.batch, selfCD->wsheader.rqtClassname);

    if (!msg->className || !msg->nameSpace)
    {
        _WSMAN_ReleaseEnumerateContext(self, enumContext->enumerationContextID);
        selfCD->enumerateContextID = 0;
        Http_SendErrorResponse(http, httpConnectionHandle, HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
        selfCD->outstandingRequest = MI_FALSE;
        EnumerateInstancesReq_Release(msg);
        return;
    }

    msg->deepInheritance = (selfCD->u.wsenumpullbody.polymorphismMode != WSMANTAG_ENUM_POLYMORPHISM_MODE_NONE);
    msg->basePropertiesOnly = (selfCD->u.wsenumpullbody.polymorphismMode == WSMANTAG_ENUM_POLYMORPHISM_MODE_EXCLUDE_PROPS);

    /* Set the query related fields */
    {
        if (selfCD->u.wsenumpullbody.dialect)
        {
            msg->queryLanguage = Batch_Zdup(msg->base.batch, selfCD->u.wsenumpullbody.dialect);
            if (!msg->queryLanguage)
            {
                _WSMAN_ReleaseEnumerateContext(self, enumContext->enumerationContextID);
                selfCD->enumerateContextID = 0;
                Http_SendErrorResponse(http, httpConnectionHandle, HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
                selfCD->outstandingRequest = MI_FALSE;
                EnumerateInstancesReq_Release(msg);
                return;
            }
        }

        if (selfCD->u.wsenumpullbody.filter)
        {
            msg->queryExpression = Batch_Zdup(msg->base.batch, selfCD->u.wsenumpullbody.filter);
            if (!msg->queryExpression)
            {
                _WSMAN_ReleaseEnumerateContext(self, enumContext->enumerationContextID);
                selfCD->enumerateContextID = 0;
                Http_SendErrorResponse(http, httpConnectionHandle, HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
                selfCD->outstandingRequest = MI_FALSE;
                EnumerateInstancesReq_Release(msg);
                return;
            }
        }
    }

    msg->base.uid = selfCD->uid;
    msg->base.gid = selfCD->gid;

    /* attach client id */
    msg->base.clientID = PtrToUint64(enumContext);

    /* increment counter to keep it alive until provider replies */
    enumContext->refcounter++;

    (*self->callback)(self, &msg->base, self->callbackData);

    EnumerateInstancesReq_Release(msg);
}

static void _ProcessAssociatorsRequest(
    Http* http,
    void* httpConnectionHandle,
    WSMAN* self,
    WSMAN_ConnectionData* selfCD)
{
    AssociationsOfReq* msg;
    WSMAN_EnumerateContext* enumContext;
    MI_Uint32 enumerationMode;


    /* create EnumerateContext */
    enumContext = _WSMAN_AllocateEnumContext(self);

    if (!enumContext)
    {
        Http_SendErrorResponse(
            http,
            httpConnectionHandle,
            HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
        selfCD->outstandingRequest = MI_FALSE;
        return;
    }

    /* link new context to current EnumRequest */
    _EC_SetActiveConnection(enumContext, selfCD);

    /* Extract teh enumeration mode */
    enumerationMode = _convertWSMANtoMsgEnumerationMode(
        selfCD->u.wsenumpullbody.enumerationMode);

    /* Create new request. */

    msg = AssociationsOfReq_New(
        1,
        WSMANFlag | enumerationMode,
        (selfCD->u.wsenumpullbody.associationFilter.isAssosiatorOperation == MI_TRUE) ? AssociatorsOfReqTag : ReferencesOfReqTag);

    if (!msg)
    {
        _WSMAN_ReleaseEnumerateContext(self, enumContext->enumerationContextID);
        selfCD->enumerateContextID = 0;
        Http_SendErrorResponse(
            http,
            httpConnectionHandle,
            HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
        selfCD->outstandingRequest = MI_FALSE;
        return;
    }

    /* Set the user agent */
    msg->base.userAgent = selfCD->userAgent;

    /* In case when client does not support optimized enumeration,
     *  send empty Enum-response with correct enumerate context
     */
    if (!selfCD->u.wsenumpullbody.allowOptimization)
    {
        _SendEnumPullResponse(self, enumContext);
        _EC_SetActiveConnection(enumContext, 0);
        _WSMAN_SetUpdateTimer(self, enumContext);
    }

    msg->nameSpace = Batch_Zdup(
        msg->base.batch,
        selfCD->wsheader.rqtNamespace);

    msg->className = Batch_Zdup(
        msg->base.batch,
        selfCD->wsheader.rqtClassname);

    if (!msg->nameSpace || !msg->className)
    {
        _WSMAN_ReleaseEnumerateContext(self, enumContext->enumerationContextID);
        selfCD->enumerateContextID = 0;
        Http_SendErrorResponse(
            http,
            httpConnectionHandle,
            HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
        selfCD->outstandingRequest = MI_FALSE;
        AssociationsOfReq_Release(msg);
        return;
    }

    msg->base.uid = selfCD->uid;
    msg->base.gid = selfCD->gid;

    /* Set messages fileds from association filter */
    {
        WSMAN_AssociationFilter* filter =
            &selfCD->u.wsenumpullbody.associationFilter;

        msg->instance = filter->referenceParameters;
        msg->assocClass = filter->associationClassName;
        msg->role = filter->role;

        if (filter->isAssosiatorOperation == MI_TRUE)
        {
            msg->resultClass = filter->resultClassName;
            msg->resultRole = filter->resultRole;
        }
    }

    /* attach client id */
    msg->base.clientID = PtrToUint64(enumContext);

    /* increment counter to keep it alive until provider replies */
    enumContext->refcounter++;

    (*self->callback)(self, &msg->base, self->callbackData);

    AssociationsOfReq_Release(msg);
}


static void _ProcessPullRequest(
    Http* http,
    WSMAN* self,
    WSMAN_ConnectionData* selfCD)
{
    WSMAN_EnumerateContext* enumContext;

    /* find EnumerateContext */
    enumContext = _WSMAN_FindEnumContext(self, selfCD->u.wsenumpullbody.enumerationContextID);

    if (!enumContext)
    {
        _SendFaultResponse(http, selfCD, WSBUF_FAULT_DESTINATION_UNREACHABLE, ZT("Enumeration context not found"));
        return;
    }

    /* link new context to the request */
    _EC_SetActiveConnection(enumContext, selfCD);

    _ProcessEnumResponse(self, enumContext, MI_TRUE);

}

static void _ProcessReleaseRequest(
    Http* http,
    WSMAN* self,
    WSMAN_ConnectionData* selfCD)
{
    WSMAN_EnumerateContext* enumContext;

    /* find EnumerateContext */
    enumContext = _WSMAN_FindEnumContext(self, selfCD->u.wsenumpullbody.enumerationContextID);

    if (!enumContext)
    {
        _SendFaultResponse(http, selfCD, WSBUF_FAULT_DESTINATION_UNREACHABLE, ZT("Enumeration context not found"));
        return;
    }

    /* Remove context from the list */
    _WSMAN_ReleaseEnumerateContext(self, enumContext->enumerationContextID);

    _SendReleaseResponse(self, selfCD);
}

static void _ParseValidateProcessEnumerateRequest(
    Http* http,
    void* httpConnectionHandle,
    WSMAN* self,
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
        LOGW((ZT("wsman: unable to parse incoming xml/ enumerate request body")));
        Http_SendErrorResponse(http, httpConnectionHandle, HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
        selfCD->outstandingRequest = MI_FALSE;
        return;
    }

    /* Validate enumerate request body */
    if (_ValidateEnumerateRequest(http, selfCD) != 0)
    {
        /* appropriate error code was already sent to the client */
        return;
    }

    /* Process request */

    if (selfCD->u.wsenumpullbody.foundAssociationOperation)
    {
        _ProcessAssociatorsRequest(http,httpConnectionHandle,self,selfCD);
    }
    else
    {
        _ProcessEnumerateRequest(http,httpConnectionHandle,self,selfCD);
    }
}

static void _ParseValidateProcessInvokeRequest(
    Http* http,
    void* httpConnectionHandle,
    WSMAN* self,
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
        msg->base.tag = InvokeReqTag;

        /* Set the message id and flags */
        msg->base.msgID = 1;
        msg->base.flags = WSMANFlag | WSMAN_ObjectFlag;

        /* ref-counter is set to 1, to balance NewMessage/Release Message pair*/
        msg->base.refCounter = 1;

        /* Copy batch onto message (released by delete method) */
        msg->base.batch = selfCD->wsheader.instanceBatch;

        msg->instance = selfCD->wsheader.instance;
        selfCD->wsheader.instanceBatch = 0;
        selfCD->wsheader.instance = 0;
    }
    else
        msg = InvokeReq_New(1, WSMANFlag | WSMAN_ObjectFlag);

    if (!msg)
        GOTO_FAILED;

    /* Set the user agent */
    msg->base.userAgent = selfCD->userAgent;

    /* Parse invoke request/body */
    if (WS_ParseInvokeBody(xml, msg->base.batch, &msg->instanceParams) != 0)
        GOTO_FAILED;

    /* Extract/set relevant parameters */
    if (selfCD->wsheader.rqtNamespace)
    {
        msg->nameSpace = Batch_Zdup(msg->base.batch, selfCD->wsheader.rqtNamespace);
        if (!msg->nameSpace)
            GOTO_FAILED;
    }

    msg->className = Batch_Zdup(msg->base.batch, selfCD->wsheader.rqtClassname);
    msg->function = Batch_Zdup(msg->base.batch, selfCD->wsheader.rqtMethod);

    if (!msg->className || !msg->function)
        GOTO_FAILED;

    /* attach client id */
    msg->base.clientID = PtrToUint64(selfCD);
    msg->base.uid = selfCD->uid;
    msg->base.gid = selfCD->gid;

    /* increment counter to keep it alive until provider replies */
    selfCD->refcounter++;

    (*self->callback)(self, &msg->base, self->callbackData);

    InvokeReq_Release(msg);
    return;

failed:
    LOGW((ZT("wsman: unable to process invoke request")));
    Http_SendErrorResponse(http, httpConnectionHandle, HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
    selfCD->outstandingRequest = MI_FALSE;

    if (msg)
        InvokeReq_Release(msg);
}

static void _ParseValidateProcessGetRequest(
    Http* http,
    void* httpConnectionHandle,
    WSMAN* self,
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
    GetInstanceReq* msg = 0;

    MI_UNUSED(xml);

    /* Check if instance name parameter was specified */
    if (!selfCD->wsheader.instance || !selfCD->wsheader.instanceBatch)
    {
        LOGW((ZT("wsman: get-instance: instance name parameter is missing")));
        _SendFaultResponse(http, selfCD, WSBUF_FAULT_INTERNAL_ERROR, ZT("get-instance: instance name parameter is missing"));

        selfCD->outstandingRequest = MI_FALSE;
        return;
    }

    /* if instance was created from batch, re-use exisintg batch to allocate message */
    /* Allocate heap space for message */
    msg = Batch_GetClear(selfCD->wsheader.instanceBatch, sizeof(GetInstanceReq));

    if (!msg)
        GOTO_FAILED;

    /* Set the user agent */
    msg->base.userAgent = selfCD->userAgent;

    /* Set the tag */
    msg->base.tag = GetInstanceReqTag;

    /* Set the message id and flags */
    msg->base.msgID = 1;
    msg->base.flags = WSMANFlag | WSMAN_ObjectFlag;

    /* ref-counter is set to 1, to balance NewMessage/Release Message pair*/
    msg->base.refCounter = 1;

    /* Copy batch into message (released by delete method) */
    msg->base.batch = selfCD->wsheader.instanceBatch;

    msg->instanceName = selfCD->wsheader.instance;

    /* clear batch/instance fields in header structure */
    selfCD->wsheader.instanceBatch = 0;
    selfCD->wsheader.instance = 0;

    /* Skip parsing get-request/body - assumed to be empty */

    /* Extract/set relevant parameters */
    if (selfCD->wsheader.rqtNamespace)
    {
        msg->nameSpace = Batch_Zdup(msg->base.batch, selfCD->wsheader.rqtNamespace);
        if (!msg->nameSpace)
            GOTO_FAILED;
    }

    /* attach client id */
    msg->base.clientID = PtrToUint64(selfCD);
    msg->base.uid = selfCD->uid;
    msg->base.gid = selfCD->gid;

    /* increment counter to keep it alive until provider replies */
    selfCD->refcounter++;

    (*self->callback)(self, &msg->base, self->callbackData);

    GetInstanceReq_Release(msg);
    return;

failed:
    LOGW((ZT("wsman: unable to process get-instance request")));
    Http_SendErrorResponse(http, httpConnectionHandle, HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
    selfCD->outstandingRequest = MI_FALSE;

    if (msg)
        GetInstanceReq_Release(msg);
}

static void _ParseValidateProcessPutRequest(
    Http* http,
    void* httpConnectionHandle,
    WSMAN* self,
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
    ModifyInstanceReq* msg = 0;

    MI_UNUSED(xml);

    /* Check if instance name parameter was specified */
    if (!selfCD->wsheader.instance || !selfCD->wsheader.instanceBatch)
    {
        LOGW((ZT("wsman: Put-instance: instance name parameter is missing")));
        _SendFaultResponse(http, selfCD, WSBUF_FAULT_INTERNAL_ERROR, ZT("Put-instance: instance name parameter is missing"));

        selfCD->outstandingRequest = MI_FALSE;
        return;
    }

    /* if instance was created from batch, re-use exisintg batch to allocate message */
    /* Allocate heap space for message */
    msg = Batch_GetClear(selfCD->wsheader.instanceBatch, sizeof(ModifyInstanceReq));

    if (!msg)
        GOTO_FAILED;

    /* Set the user agent */
    msg->base.userAgent = selfCD->userAgent;

    /* Set the tag */
    msg->base.tag = ModifyInstanceReqTag;

    /* Set the message id and flags */
    msg->base.msgID = 1;
    msg->base.flags = WSMANFlag | WSMAN_ObjectFlag;

    /* ref-counter is set to 1, to balance NewMessage/Release Message pair*/
    msg->base.refCounter = 1;

    /* Copy batch into message (released by delete method) */
    msg->base.batch = selfCD->wsheader.instanceBatch;
    msg->instance = selfCD->wsheader.instance;

    /* clear batch/instance fields in header structure */
    selfCD->wsheader.instanceBatch = 0;
    selfCD->wsheader.instance = 0;

    /* re-use 'create' parser to parse 'Modify' request/body */
    if (WS_ParseCreateBody(xml, msg->base.batch, &msg->instance) != 0)
        GOTO_FAILED;

    /* Extract/set relevant parameters */
    if (selfCD->wsheader.rqtNamespace)
    {
        msg->nameSpace = Batch_Zdup(msg->base.batch, selfCD->wsheader.rqtNamespace);
        if (!msg->nameSpace)
            GOTO_FAILED;
    }

    /* attach client id */
    msg->base.clientID = PtrToUint64(selfCD);
    msg->base.uid = selfCD->uid;
    msg->base.gid = selfCD->gid;

    /* increment counter to keep it alive until provider replies */
    selfCD->refcounter++;

    (*self->callback)(self, &msg->base, self->callbackData);

    ModifyInstanceReq_Release(msg);
    return;

failed:
    LOGW((ZT("wsman: unable to process Put-instance request")));
    Http_SendErrorResponse(http, httpConnectionHandle, HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
    selfCD->outstandingRequest = MI_FALSE;

    if (msg)
        ModifyInstanceReq_Release(msg);
}

static void _ParseValidateProcessDeleteRequest(
    Http* http,
    void* httpConnectionHandle,
    WSMAN* self,
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
    DeleteInstanceReq* msg = 0;

    MI_UNUSED(xml);

    /* Check if instance name parameter was specified */
    if (!selfCD->wsheader.instance || !selfCD->wsheader.instanceBatch)
    {
        LOGW((ZT("wsman: delete-instance: instance name parameter is missing")));
        _SendFaultResponse(http, selfCD, WSBUF_FAULT_INTERNAL_ERROR, ZT("delete-instance: instance name parameter is missing"));

        selfCD->outstandingRequest = MI_FALSE;
        return;
    }

    /* if instance was created from batch, re-use exisintg batch to allocate message */
    /* Allocate heap space for message */
    msg = Batch_GetClear(selfCD->wsheader.instanceBatch, sizeof(DeleteInstanceReq));

    if (!msg)
        GOTO_FAILED;

    /* Set the user agent */
    msg->base.userAgent = selfCD->userAgent;

    /* Set the tag */
    msg->base.tag = DeleteInstanceReqTag;

    /* Set the message id and flags */
    msg->base.msgID = 1;
    msg->base.flags = WSMANFlag | WSMAN_ObjectFlag;

    /* ref-counter is set to 1, to balance NewMessage/Release Message pair*/
    msg->base.refCounter = 1;

    /* Copy batch into message (released by delete method) */
    msg->base.batch = selfCD->wsheader.instanceBatch;

    msg->instanceName = selfCD->wsheader.instance;

    /* clear batch/instance fields in header structure */
    selfCD->wsheader.instanceBatch = 0;
    selfCD->wsheader.instance = 0;

    /* Skip parsing Delete-request/body - assumed to be empty */

    /* Extract/set relevant parameters */
    if (selfCD->wsheader.rqtNamespace)
    {
        msg->nameSpace = Batch_Zdup(msg->base.batch, selfCD->wsheader.rqtNamespace);
        if (!msg->nameSpace)
            GOTO_FAILED;
    }

    /* attach client id */
    msg->base.clientID = PtrToUint64(selfCD);
    msg->base.uid = selfCD->uid;
    msg->base.gid = selfCD->gid;

    /* increment counter to keep it alive until provider replies */
    selfCD->refcounter++;

    (*self->callback)(self, &msg->base, self->callbackData);

    DeleteInstanceReq_Release(msg);
    return;

failed:
    LOGW((ZT("wsman: unable to process delete-instance request")));
    Http_SendErrorResponse(http, httpConnectionHandle, HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
    selfCD->outstandingRequest = MI_FALSE;

    if (msg)
        DeleteInstanceReq_Release(msg);
}

static void _ParseValidateProcessCreateRequest(
    Http* http,
    void* httpConnectionHandle,
    WSMAN* self,
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
    CreateInstanceReq* msg = 0;

     msg = CreateInstanceReq_New(1, WSMANFlag | WSMAN_CreatedEPRFlag);

    if (!msg)
        GOTO_FAILED;

    /* Set the user agent */
    msg->base.userAgent = selfCD->userAgent;

    /* Parse create request/body */
    if (WS_ParseCreateBody(xml, msg->base.batch, &msg->instance) != 0)
        GOTO_FAILED;

    /* Extract/set relevant parameters */
    if (selfCD->wsheader.rqtNamespace)
    {
        msg->nameSpace = Batch_Zdup(msg->base.batch, selfCD->wsheader.rqtNamespace);
        if (!msg->nameSpace)
            GOTO_FAILED;
    }

    /* attach client id */
    msg->base.clientID = PtrToUint64(selfCD);
    msg->base.uid = selfCD->uid;
    msg->base.gid = selfCD->gid;

    /* increment counter to keep it alive until provider replies */
    selfCD->refcounter++;

    (*self->callback)(self, &msg->base, self->callbackData);

    CreateInstanceReq_Release(msg);
    return;

failed:
    LOGW((ZT("wsman: unable to process Create request")));
    Http_SendErrorResponse(http, httpConnectionHandle, HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
    selfCD->outstandingRequest = MI_FALSE;

    if (msg)
        CreateInstanceReq_Release(msg);
}

static void _ParseValidateProcessPullRequest(
    Http* http,
    void* httpConnectionHandle,
    WSMAN* self,
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
    /* Parse pull request/body */
    if (WS_ParsePullBody(xml, &selfCD->u.wsenumpullbody) != 0)
    {
        LOGW((ZT("wsman: unable to parse incoming xml/ Pull request body")));
        Http_SendErrorResponse(http, httpConnectionHandle, HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
        selfCD->outstandingRequest = MI_FALSE;
        return;
    }

    /* Validate enumerate request body */
    if (_ValidatePullRequest(http, selfCD) != 0)
    {
        /* appropriate error code was already sent to the client */
        return;
    }

    /* Process reqest */
    _ProcessPullRequest(http,self,selfCD);
}

static void _ParseValidateProcessReleaseRequest(
    Http* http,
    void* httpConnectionHandle,
    WSMAN* self,
    WSMAN_ConnectionData* selfCD,
    XML*    xml)
{
    /* Parse pull request/body */
    if (WS_ParseReleaseBody(xml, &selfCD->u.wsenumpullbody) != 0)
    {
        LOGW((ZT("wsman: unable to parse incoming xml/ Release request body")));
        Http_SendErrorResponse(http, httpConnectionHandle, HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
        selfCD->outstandingRequest = MI_FALSE;
        return;
    }

    /* Validate enumerate request body */
    /* no validation needed */

    /* Process reqest */
    _ProcessReleaseRequest(http,self,selfCD);
}

static void _SendIdentifyResponse(
    WSMAN* self,
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

    _SendResponse(
        self->http,
        selfCD->httpConnectionHandle,
        HTTP_ERROR_CODE_OK,
        &responsePage);

    selfCD->outstandingRequest = MI_FALSE;

    if (responsePage)
        free(responsePage);

    return;

failed:
    WSBuf_Destroy(&out);
    Http_SendErrorResponse(
        self->http,
        selfCD->httpConnectionHandle,
        HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
    selfCD->outstandingRequest = MI_FALSE;
}

static void _HandleIdentifyRequest(
    Http* http,
    void* httpConnectionHandle,
    WSMAN* self,
    WSMAN_ConnectionData* selfCD,
    XML* xml)
{
    /* Parse pull request/body */
    if (WS_ParseIdentifyBody(xml) != 0)
    {
        LOGW((ZT("wsman: found neither Action or Identify")));
        Http_SendErrorResponse(http, httpConnectionHandle,
            HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
        selfCD->outstandingRequest = MI_FALSE;
        return;
    }

    _SendIdentifyResponse(self, selfCD);
}

/************************************************************************\
*   Dispatcher calls processing
\************************************************************************/

static void _EC_GetMessageSubset(
    WSMAN_EnumerateContext* selfEC,
    WSMAN_ConnectionData* selfCD,
    PostInstanceMsg** subsetEnd,
    MI_Uint32* totalSize)
{
    MI_Uint32 count = 0;
    *totalSize = 0;
    *subsetEnd = selfEC->head;

    while (*subsetEnd)
    {
        if (count + 1 > selfCD->u.wsenumpullbody.maxElements ||
            (*totalSize) + (*subsetEnd)->packedInstanceSize + APPROX_ENUM_RESP_ENVELOPE_SIZE > selfCD->wsheader.maxEnvelopeSize)
            break;

        (*totalSize) += (*subsetEnd)->packedInstanceSize;
        count++;
        (*subsetEnd) = (PostInstanceMsg*)(*subsetEnd)->base.next;
    }
}

/* Sends as many instances as posisble (based on envelope-size and instance counter) */
static void _SendEnumPullResponse(
    WSMAN* self,
    WSMAN_EnumerateContext* selfEC)
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

    /* Get message subset based on envelope size/ maxElements */
    _EC_GetMessageSubset(selfEC, selfCD, &subsetEnd, &messagesSize);

    /* validate if all mesages can be sent */
    if (endOfSequence && subsetEnd)
    {
        endOfSequence = MI_FALSE;
    }

    /* check if we can put at least one message in response */
    if (NULL != selfEC->head && subsetEnd == selfEC->head)
    {
        LOGW((ZT("wsman: max-envelope is too small even for one message; message size %d"),
            (int)subsetEnd->packedInstanceSize ));
        _SendFaultResponse(self->http, selfCD, WSBUF_FAULT_ENCODING_LIMIT, ZT("insufficient envelope size for instance transferring"));
        /* Note: leaving context 'as is' so advanced client can increase packet size and re-try */
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
    else
    {
        if (MI_RESULT_OK != WSBuf_CreateSoapResponseHeader(&outBufHeader,
            LIT(ZT("http://schemas.xmlsoap.org/ws/2004/09/enumeration/PullResponse")), selfCD->wsheader.rqtMessageID))
            GOTO_FAILED;
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

    responsePageCombined = (Page*)malloc(sizeof(Page) + totalSize + 1);

    if (!responsePageCombined)
        GOTO_FAILED;

    {
        char* data = (char*) (responsePageCombined + 1);
        data[totalSize] = 0;

        memcpy(data, responsePageHeader+1, responsePageHeader->u.s.size);
        data += responsePageHeader->u.s.size;

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

    free(responsePageHeader); responsePageHeader = 0;
    free(responsePageTrailer); responsePageTrailer = 0;

    _SendResponse(
        self->http,
        selfCD->httpConnectionHandle,
        HTTP_ERROR_CODE_OK,
        &responsePageCombined);

    selfCD->outstandingRequest = MI_FALSE;

    if (responsePageCombined)
        free(responsePageCombined);

    return;

failed:
    WSBuf_Destroy(&outBufHeader);
    WSBuf_Destroy(&outBufTrailer);
    if (responsePageCombined) free(responsePageCombined);
    if (responsePageHeader) free(responsePageHeader);
    if (responsePageTrailer) free(responsePageTrailer);

    _EC_ReleaseAllMessages(selfEC);
    Http_SendErrorResponse(self->http, selfCD->httpConnectionHandle, HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
    selfCD->outstandingRequest = MI_FALSE;
}

static void _SendInvokeResponse(
    WSMAN* self,
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
    Buf_AppStrN(&buf, LIT(ZT("/wbem/wscim/1/cim-schema/2/")));
    Buf_AppStr(&buf, selfCD->wsheader.rqtClassname);
    Buf_AppStrN(&buf, LIT(ZT("/")));
    Buf_AppStr(&buf, selfCD->wsheader.rqtMethod);
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
        FILE* f = Fopen("out_test.xml", "a");
        fwrite((char*)(responsePageCombined+1), 1, (size_t)responsePageCombined->u.s.size, f);
        fclose(f);
    }*/

    _SendResponse(
        self->http,
        selfCD->httpConnectionHandle,
        HTTP_ERROR_CODE_OK,
        &responsePage);

    /* indicate that response was sent */
    selfCD->outstandingRequest = MI_FALSE;

    if (responsePage)
        free(responsePage);

    Buf_Destroy(&buf);

    return;

failed:

    WSBuf_Destroy(&outBuf);
    Buf_Destroy(&buf);

    if (responsePage)
        free(responsePage);

    Http_SendErrorResponse(
        self->http,
        selfCD->httpConnectionHandle,
        HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);

    /* indicate that response was sent */
    selfCD->outstandingRequest = MI_FALSE;
}

static void _SendSingleInstanceResponse(
    WSMAN* self,
    WSMAN_ConnectionData* selfCD,
    PostInstanceMsg* message,
    const ZChar* action,
    MI_Uint32 actionSize)
{
    WSBuf   outBuf;
    Page*       responsePage = 0;

    if (WSBuf_Init(&outBuf, APPROX_ENUM_RESP_ENVELOPE_SIZE + message->packedInstanceSize) != MI_RESULT_OK)
        GOTO_FAILED;

    if (MI_RESULT_OK != WSBuf_CreateSoapResponseHeader(&outBuf,
        action, actionSize, selfCD->wsheader.rqtMessageID))
        GOTO_FAILED;

    if (MI_RESULT_OK != WSBuf_AddLit(&outBuf,
        LIT(ZT("</SOAP-ENV:Header>")
        ZT("<SOAP-ENV:Body>")
        )))
        GOTO_FAILED;

    if (WSBuf_AddVerbatim(
        &outBuf,
        message->packedInstancePtr,
        message->packedInstanceSize) != MI_RESULT_OK)
    {
        GOTO_FAILED;
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

    _SendResponse(
        self->http,
        selfCD->httpConnectionHandle,
        HTTP_ERROR_CODE_OK,
        &responsePage);

    /* indicate that response was sent */
    selfCD->outstandingRequest = MI_FALSE;

    if (responsePage)
        free(responsePage);

    return;

failed:
    WSBuf_Destroy(&outBuf);
    if (responsePage) free(responsePage);

    Http_SendErrorResponse(self->http, selfCD->httpConnectionHandle, HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);

    /* indicate that response was sent */
    selfCD->outstandingRequest = MI_FALSE;
}

static void _SendDeleteInstanceResponse(
    WSMAN* self,
    WSMAN_ConnectionData* selfCD)
{
    WSBuf   outBuf;
    Page*       responsePage = 0;

    if (WSBuf_Init(&outBuf, APPROX_ENUM_RESP_ENVELOPE_SIZE) != MI_RESULT_OK)
        GOTO_FAILED;

    if (MI_RESULT_OK != WSBuf_CreateSoapResponseHeader(&outBuf,
        LIT(ZT("http://schemas.xmlsoap.org/ws/2004/09/transfer/DeleteResponse")), selfCD->wsheader.rqtMessageID))
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

    _SendResponse(
        self->http,
        selfCD->httpConnectionHandle,
        HTTP_ERROR_CODE_OK,
        &responsePage);

    /* indicate that response was sent */
    selfCD->outstandingRequest = MI_FALSE;

    if (responsePage)
        free(responsePage);

    return;

failed:
    WSBuf_Destroy(&outBuf);
    if (responsePage) free(responsePage);

    Http_SendErrorResponse(self->http, selfCD->httpConnectionHandle, HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);

    /* indicate that response was sent */
    selfCD->outstandingRequest = MI_FALSE;
}

static void _SendErrorResponse(
    WSMAN* self,
    WSMAN_ConnectionData* selfCD,
    PostResultMsg* message)
{
    WSBUF_FAULT_CODE faultCode;
    const ZChar* description = 0;

    faultCode = WSBuf_CIMErrorToWSFault(message->result, &description);

    if (message->errorMessage == NULL)
    {
        message->errorMessage = description;
    }

    /* ATTN! consume text from cim_error if supplied */
    _SendCimFaultResponse(self->http, selfCD, faultCode, message);
}


/* Function processes backlog in enumeration context;
    returns true if message was sent to active connection;
    once last repsonse is sent, it deletes context */
static MI_Boolean _ProcessEnumResponse(
    WSMAN* self,
    WSMAN_EnumerateContext* selfEC,
    MI_Boolean attachingPullRequest)
{
    /* do we have connected cleint to send response to? */
    if (!selfEC->activeConnection)
        return MI_FALSE;

    if (selfEC->enumerationCompleted && selfEC->finalResult != MI_RESULT_OK)
    {
        PostResultMsg message;
        memset(&message, 0, sizeof(message));
        message.result = selfEC->finalResult;
        _SendErrorResponse(self, selfEC->activeConnection, &message);

        /* release context */
        _EC_SetActiveConnection(selfEC, 0);
        _WSMAN_ReleaseEnumerateContext(self, selfEC->enumerationContextID);
        selfEC = 0;
        return MI_TRUE;
    }

    /* Check if partial response has to be sent (or enumeration is completed) */
    /* Update: send anything that is available once client re-connects with pull */
    /* Send resposne now if:
        - enumeration is complete
        - queue has enough instances to fill entire packet (by size or number)
        - pull request arrives. Normally, network is lsower than providers,
            so once client returns with next pull request, lets send all messages
            we have in queue
        - server is stressed (too many instances)
    */
    if (selfEC->enumerationCompleted ||
        APPROX_ENUM_RESP_ENVELOPE_SIZE + selfEC->totalResponseSize > selfEC->activeConnection->wsheader.maxEnvelopeSize ||
        selfEC->totalResponses >= selfEC->activeConnection->u.wsenumpullbody.maxElements ||
        (attachingPullRequest && selfEC->head) ||
        (Selector_IsStressed(self->selector) && selfEC->head)
        )
    //if (selfEC->enumerationCompleted || selfEC->head)
    {
        //LOGW_CHAR(("processing responses %d", selfEC->totalResponses));

        _SendEnumPullResponse(self, selfEC);
        _EC_SetActiveConnection(selfEC, 0);
    }

    /* release context if last message was sent */
    if (selfEC->enumerationCompleted && !selfEC->head)
    {
        _EC_SetActiveConnection(selfEC, 0);
        _WSMAN_ReleaseEnumerateContext(self, selfEC->enumerationContextID);
        selfEC = 0;
    }
    else
    {
        /* set/update timer */
        _WSMAN_SetUpdateTimer(self, selfEC);
    }

    return MI_TRUE;
}

static void _ProcessResultEnumerationContext(
    WSMAN* self,
    WSMAN_EnumerateContext* selfEC,
    PostResultMsg* message )
{
    /* mark context as 'completed' */
    selfEC->enumerationCompleted = MI_TRUE;
    selfEC->finalResult = message->result;
    //ATTN!: process error text/messages

    _ProcessEnumResponse(self, selfEC, MI_FALSE);

    /* release context */
    _EC_Release(selfEC, MI_FALSE);
}


static void _ProcessInstanceResponse(
    WSMAN* self,
    WSMAN_ConnectionData* selfCD,
    PostInstanceMsg* message)
{
    /* send appropriate response */
    switch (selfCD->wsheader.rqtAction)
    {
    case 0: /* since invoke does not have strict URI, we got it as 'undefined' */
        _SendInvokeResponse(self, selfCD, message);
        break;

    case WSMANTAG_ACTION_GET:
        _SendSingleInstanceResponse(self, selfCD, message, LIT(ZT("http://schemas.xmlsoap.org/ws/2004/09/transfer/GetResponse")));
        break;

    case WSMANTAG_ACTION_PUT:
        _SendSingleInstanceResponse(self, selfCD, message, LIT(ZT("http://schemas.xmlsoap.org/ws/2004/09/transfer/PutResponse")));
        break;

    case WSMANTAG_ACTION_CREATE:
        _SendSingleInstanceResponse(self, selfCD, message, LIT(ZT("http://schemas.xmlsoap.org/ws/2004/09/transfer/CreateResponse")));
        break;

    default:
        /* unexpected */
        _SendFaultResponse(
            self->http,
            selfCD,
            WSBUF_FAULT_INTERNAL_ERROR,
            ZT("unexpected internal state"));
        break;
    }
    selfCD->outstandingRequest = MI_FALSE;
}

static void _ProcessResultConnectionData(
    WSMAN* self,
    WSMAN_ConnectionData* selfCD,
    PostResultMsg* message )
{
    /* if response was not sent yet, send it now (error probably) */
    if (selfCD->outstandingRequest)
    {
        if (selfCD->single_message)
        {
            _ProcessInstanceResponse(self, selfCD, selfCD->single_message);
        }
        else if (MI_RESULT_OK == message->result &&
            WSMANTAG_ACTION_DELETE == selfCD->wsheader.rqtAction)
        {
            _SendDeleteInstanceResponse(self, selfCD);
        }
        else
        {
            _SendErrorResponse(self, selfCD, message);
        }

        selfCD->outstandingRequest = MI_FALSE;
    }

    /* release connection data */
    _CD_Release(selfCD);
}

static void _ProcessInstanceConnectionData(
    WSMAN* self,
    WSMAN_ConnectionData* selfCD,
    PostInstanceMsg* message)
{
    MI_UNUSED(self);

    /* Ignore expired contexts */
    if (!selfCD->outstandingRequest)
        return;

    _CD_SetSingleMessage(selfCD, message);
}

static void _ProcessInstanceEnumerationContext(
    WSMAN* self,
    WSMAN_EnumerateContext* selfEC,
    PostInstanceMsg* message )
{
    /* Ignore expired contexts */
    if (selfEC->expired)
        return;

    /* add-ref message to keep it alive */
    Message_AddRef( &message->base);

    /* Add it to the list to process when result is posted */
    List_Append(
        (ListElem**)&selfEC->head,
        (ListElem**)&selfEC->tail,
        (ListElem*)message);

    /* Increment total instance size */
    selfEC->totalResponseSize += message->packedInstanceSize;

    /* Increment total number of responses */
    selfEC->totalResponses++;

    /* Check if we need to send response to the client */
    _ProcessEnumResponse(self, selfEC, MI_FALSE);
}

/* HTTP callbacks */
static void _HttpCallbackOnNewConnection(
    Http* http,
    void* callbackData,
    void* httpConnectionHandle,
    void** connectionData)
{
    WSMAN_ConnectionData* selfConnectionData;
    MI_UNUSED(http);
    MI_UNUSED(callbackData);

    selfConnectionData = (WSMAN_ConnectionData*)calloc(1, sizeof(WSMAN_ConnectionData));

    if (!selfConnectionData)
        return /*MI_RESULT_FAILED*/;

    selfConnectionData->httpConnectionHandle = httpConnectionHandle;
    selfConnectionData->refcounter = 1;
    selfConnectionData->tag = DATA_TAG_CONNECTION_DATA;
    *connectionData = selfConnectionData;
}

static void _HttpCallbackOnCloseConnection(
    Http* http,
    void* callbackData,
    void* connectionData)
{
    MI_UNUSED(http);
    MI_UNUSED(callbackData);

    if (connectionData)
    {
        WSMAN_ConnectionData* selfConnectionData = (WSMAN_ConnectionData*)connectionData;
        selfConnectionData->httpConnectionHandle = 0;
        selfConnectionData->outstandingRequest = MI_FALSE;

        _CD_Release(selfConnectionData);
    }
}

#if defined(CONFIG_ENABLE_WCHAR)
static Page* _XMLToWideCharPage(const char* data, size_t size)
{
    size_t wsize = size * sizeof(wchar_t);
    Page* page = (Page*)malloc(sizeof(Page) + wsize);
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

static void _HttpCallbackOnRequest(
    Http* http,
    void* callbackData,
    void* connectionData,
    void* httpConnectionHandle,
    const HttpHeaders* headers,
    Page** page)
{
    WSMAN_ConnectionData* selfCD = (WSMAN_ConnectionData*)connectionData;
    WSMAN* self = (WSMAN*)callbackData;
    XML* xml = (XML*)calloc(1, sizeof (XML));
    if (xml == NULL)
    {
        LOGE((ZT("out of memory")));
        Http_SendErrorResponse(
            http,
            httpConnectionHandle,
            HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
        return;
    }

    memcpy(xml, &self->xml, sizeof(XML));

#if defined(CONFIG_ENABLE_WCHAR)
    /* Convert this page to wide-character */
    {
        Page* wpage = _XMLToWideCharPage(
            (const char*)(*page + 1),
            (*page)->u.s.size);

        if (wpage == NULL)
        {
            LOGE((ZT("out of memory")));
            Http_SendErrorResponse(
                http,
                httpConnectionHandle,
                HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
            free(xml);
            return;
        }

        free(*page);
        *page = wpage;
    }
#endif /* defined(CONFIG_ENABLE_WCHAR) */

    /* Cleanup connection data, since it may still store allocated
     * pointers from previous operation
     */
    _CD_Cleanup(selfCD);

    /* Determine whether WinRM client */

    if (headers->userAgent &&
        Strcasecmp(headers->userAgent, "Microsoft WinRM Client") == 0)
    {
        selfCD->userAgent = USERAGENT_WINRM;
    }

    /* Verify content type */
    if (headers->contentType == NULL ||
        (Strcasecmp(headers->contentType, "application/soap+xml") != 0 &&
         Strcasecmp(headers->contentType, "text/xml") != 0))
    {
        LOGW((ZT("wsman: invalid/missing content type in request [%Z]"),
            zcs(PageData(*page))));

        Http_SendErrorResponse(http, httpConnectionHandle,
            HTTP_ERROR_CODE_BAD_REQUEST);
        free(xml);
        return;
    }

    if (headers->charset != NULL && Strcasecmp(headers->charset, "utf-8") != 0)
    {
        LOGW((ZT("wsman: charset is not supported [%s]"),
            scs(MI_GET_SAFE_PRINTF_STRING(headers->charset))));
        _SendFaultResponse(http, selfCD, WSBUF_FAULT_ENCODING_LIMIT,
            ZT("only utf 8 is supported"));
        free(xml);
        return;
    }

    if (headers->username == NULL || headers->password == NULL ||
        0 != AuthenticateUser(headers->username, headers->password))
    {
        LOGW((ZT("wsman: authentication failed for user [%s]"),
            scs(MI_GET_SAFE_PRINTF_STRING(headers->username))));

        Http_SendErrorResponse(http, httpConnectionHandle,
            HTTP_ERROR_CODE_UNAUTHORIZED);
        ResetUserData(headers);
        free(xml);
        return;
    }
    ResetUserData(headers);

    if (0 != LookupUser(headers->username, &selfCD->uid, &selfCD->gid))
    {
        LOGW((ZT("wsman: get user [%s] uid/gid"),
            scs(MI_GET_SAFE_PRINTF_STRING(headers->username))));

        Http_SendErrorResponse(http, httpConnectionHandle,
            HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
        free(xml);
        return;
    }

    if ((*page)->u.s.size == 0)
    {
        LOGW((ZT("wsman: size of buffer is 0")));

        Http_SendErrorResponse(http, httpConnectionHandle,
            HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
                free(xml);
        return;
    }

    XML_SetText(xml, (ZChar*)(*page + 1));

    /* Parse header */
    if (WS_ParseSoapEnvelope(xml) != 0 || xml->status != 0)
    {
        LOGW((ZT("wsman: failed to parse SOAP envelope")));
        Http_SendErrorResponse(http, httpConnectionHandle,
            HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
        free(xml);
        return;
    }

    /* Parse WS header */
    if (WS_ParseWSHeader(xml, &selfCD->wsheader) != 0 || xml->status != 0)
    {
        if (Zlen((ZChar*)(*page + 1)) < 12)
        {
            // if only "<s:Envelope" is present after the envelope is parsed, we have an empty WS document
            free(xml);
            return;
        }
        LOGW((ZT("wsman: failed to parse WS header")));
        Http_SendErrorResponse(http,
            httpConnectionHandle, HTTP_ERROR_CODE_INTERNAL_SERVER_ERROR);
        free(xml);
        return;
    }

    /* Validate header */
    if (_ValidateHeader(http, selfCD) != 0)
    {
        free(xml);
        return;
    }

    /* See if this is a Identify request */

    if (!selfCD->wsheader.foundAction)
    {
        _HandleIdentifyRequest(
            http,
            httpConnectionHandle,
            self,
            selfCD,
            xml);
        free(xml);
        return;
    }

    /* Take ownership of this page so we can refer to XML strings */
    _CD_SetPage(selfCD, *page);
    *page = NULL;

    selfCD->outstandingRequest = MI_TRUE;

    /* Parse body and send request to the dispatcher */
    switch (selfCD->wsheader.rqtAction)
    {
        case WSMANTAG_ACTION_ENUMERATE:
        {
            _ParseValidateProcessEnumerateRequest(http, httpConnectionHandle, self, selfCD, xml);
            break;
        }
        case WSMANTAG_ACTION_PULL:
        {
            _ParseValidateProcessPullRequest(http, httpConnectionHandle, self, selfCD, xml);
            break;
        }
        case WSMANTAG_ACTION_RELEASE:
        {
            _ParseValidateProcessReleaseRequest(http, httpConnectionHandle, self, selfCD, xml);
            break;
        }
        case WSMANTAG_ACTION_GET:
        {
            _ParseValidateProcessGetRequest(http, httpConnectionHandle, self, selfCD, xml);
            break;
        }
        case WSMANTAG_ACTION_PUT:
        {
            _ParseValidateProcessPutRequest(http, httpConnectionHandle, self, selfCD, xml);
            break;
        }
        case WSMANTAG_ACTION_DELETE:
        {
            _ParseValidateProcessDeleteRequest(http, httpConnectionHandle, self, selfCD, xml);
            break;
        }
        case WSMANTAG_ACTION_CREATE:
        {
            _ParseValidateProcessCreateRequest(http, httpConnectionHandle, self, selfCD, xml);
            break;
        }
        case 0: /* since invoke does not have strict URI, we got it as 'undefined' */
        {
            _ParseValidateProcessInvokeRequest(http, httpConnectionHandle, self, selfCD, xml);
            break;
        }
        default:
        {
            /* unsupported action */
            LOGW((ZT("wsman: unsupported action [%d] "), selfCD->wsheader.rqtAction ));
            _SendFaultResponse(http, selfCD, WSBUF_FAULT_NOT_SUPPORTED, 0);
            selfCD->outstandingRequest = MI_FALSE;
            break;
        }
    }

    free(xml);
}

/*
**==============================================================================
**
** Public definitions:
**
**==============================================================================
*/
MI_Result WSMAN_New_Listener(
    WSMAN** selfOut,
    Selector* selector, /*optional, maybe NULL*/
    unsigned short http_port,   /* 0 to disable */
    unsigned short https_port,  /* 0 to disable */
    char* sslCipherSuite,       /* NULL to disable */
    WSMANCallback callback,
    void* callbackData)
{
    WSMAN* self;
    MI_Result r;

    /* Check parameters */
    if (!selfOut)
        return MI_RESULT_INVALID_PARAMETER;

    /* Clear output parameter */
    *selfOut = NULL;

    /* Allocate structure */
    {
        self = (WSMAN*)calloc(1, sizeof(WSMAN));

        if (!self)
            return MI_RESULT_FAILED;
    }

    /* Save the callback and callbackData */
    self->callback = callback;
    self->callbackData = callbackData;

    /*ATTN! slector can be null!*/
    self->selector = selector;

    /* options */
    {
        WSMAN_Options options = DEFAULT_WSMAN_OPTIONS;

        self->options = options;
    }

    /* Set the magic number */
    self->magic = _MAGIC;

    /* create a server */
    r = Http_New_Server(
        &self->http, selector, http_port, https_port, sslCipherSuite,
        _HttpCallbackOnNewConnection,
        _HttpCallbackOnCloseConnection,
        _HttpCallbackOnRequest, self);

    if (MI_RESULT_OK != r)
    {
        WSMAN_Delete(self);
        return r;
    }

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

    *selfOut = self;

    return MI_RESULT_OK;
}

MI_Result WSMAN_Delete(
    WSMAN* self)
{
    /* Check parameters */
    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

    /* Check magic number */
    if (self->magic != _MAGIC)
        return MI_RESULT_INVALID_PARAMETER;

    Http_Delete(self->http);

    /* clear all outstanding contexts */
    _WSMAN_ReleaseAllEnumerateContexts(self);

    /* Clear magic number */
    self->magic = 0xDDDDDDDD;

    /* Free self pointer */
    free(self);

    return MI_RESULT_OK;
}

MI_Result WSMAN_Run(
    WSMAN* self,
    MI_Uint64 timeoutUsec)
{
    /* Run the selector */
    return Http_Run(self->http, timeoutUsec);
}

static MI_Result _SendIN_IO_thread(
    void* self_,
    Message* message)
{
    WSMAN* self = (WSMAN*)self_;
    WSMAN_ConnectionData* selfCD = 0;
    WSMAN_EnumerateContext* selfEC = 0;

    /* check params */
    if (!self || !message )
        return MI_RESULT_INVALID_PARAMETER;

    if (self->magic != _MAGIC)
    {
        LOGW((ZT("_SendIN_IO_thread: invalid magic!") ));
        return MI_RESULT_INVALID_PARAMETER;
    }

    /* find where to send it */
    selfCD = (WSMAN_ConnectionData*)Uint64ToPtr(message->clientID);
    selfEC = (WSMAN_EnumerateContext*)Uint64ToPtr(message->clientID);

    if (selfCD && selfCD->tag != DATA_TAG_CONNECTION_DATA)
    {
        selfCD = 0;
    }
    if (selfEC && selfEC->tag != DATA_TAG_ENUMERATION_CONTEXT)
    {
        selfEC = 0;
    }
    if (!selfCD && !selfEC)
    {
        LOGW((ZT("_SendIN_IO_thread: clientID!") ));
        return MI_RESULT_INVALID_PARAMETER;
    }

    /* ATTN! validate handler */

    /* Process response message */
    switch (message->tag)
    {
    case PostResultMsgTag:
        if (selfCD)
            _ProcessResultConnectionData(self, selfCD, (PostResultMsg*)message );
        else
            _ProcessResultEnumerationContext(self, selfEC, (PostResultMsg*)message );

        break;

    case PostInstanceMsgTag:
        if (selfCD)
            _ProcessInstanceConnectionData(self, selfCD, (PostInstanceMsg*)message );
        else
            _ProcessInstanceEnumerationContext(self, selfEC, (PostInstanceMsg*)message );

        break;

    default:
        LOGW((ZT("wsman: _SendIN_IO_thread: unexpected message tag %d"), message->tag ));
        return MI_RESULT_INVALID_PARAMETER;
    }

    return MI_RESULT_OK;
}

/* Signature must not have return type so we created this wrapper */
static void _SendIN_IO_thread_wrapper(void* self, Message* message)
{
    _SendIN_IO_thread(self, message);

    /* ATTN: log failed result? */
}


MI_Result WSMAN_Send(
    WSMAN* self,
    Message* message)
{
    return Selector_CallInIOThread(
        self->selector, _SendIN_IO_thread_wrapper, self, message );
}

MI_Result WSMAN_SetOptions(
    WSMAN* self,
    const WSMAN_Options* options)
{
    /* check params */
    if (!self || !options)
        return MI_RESULT_INVALID_PARAMETER;

    /* Check magic number */
    if (self->magic != _MAGIC)
    {
        LOGW((ZT("invalid magic!") ));
        return MI_RESULT_INVALID_PARAMETER;
    }

    self->options = *options;

    /* Set HTTP otpions */
    {
        HttpOptions tmp = DEFAULT_HTTP_OPTIONS;
        tmp.enableTracing = options->enableHTTPTracing;
        Http_SetOptions(self->http, &tmp);
    }

    return MI_RESULT_OK;
}
