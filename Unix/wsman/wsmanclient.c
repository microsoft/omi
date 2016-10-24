/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <pal/palcommon.h>
#include <pal/strings.h>
#include <pal/atomic.h>
#include <pal/sleep.h>
#include <base/base64.h>
#include <base/batch.h>
#include <base/messages.h>
#include <base/log.h>
#include <http/httpclient.h>
#include <xml/xml.h>
#include <omi_error/omierror.h>
#include "wstags.h"
#include "wsmanparser.h"
#include "wsbuf.h"
#include "wsmanclient.h"
#include "wsmanerrorhandling.h"

#define DEFAULT_MAX_ENV_SIZE 100*1024
#define DEFAULT_MAX_ELEMENTS 1000

#define PROTOCOLSOCKET_STRANDAUX_POSTMSG 0
#define PROTOCOLSOCKET_STRANDAUX_READYTOFINISH  1
#define PROTOCOLSOCKET_STRANDAUX_CONNECTEVENT 2

#if defined(CONFIG_ENABLE_WCHAR)

/* We do not yet support utf16 encoding in wsman. This variable is used to prevent unreachable code errors
 * caused by just ifdefing out the support, since that would hit in a number of places rendering the code
  * quite hard to read */

  static MI_Boolean WSMAN_UTF16_IMPLEMENTED = FALSE;
#endif


STRAND_DEBUGNAME3( WsmanClientConnector, PostMsg, ReadyToFinish, ConnectEvent );

typedef struct _EnumerationState
{
    MI_ConstString nameSpace;
    MI_ConstString className;
    MI_ConstString context;
    MI_Boolean endOfSequence;
    MI_Boolean getNextInstance;
    XML *xml;
    MI_Boolean firstResponse;
    XML_Elem e;
}EnumerationState;

struct _WsmanClient
{
    Batch *batch;
    Strand strand;
    HttpClient *httpClient;
    WsmanClient_Headers wsmanSoapHeaders;
    char *authorizationHeader;
    char *hostname;
    char *httpUrl;
    char *contentType;
    ptrdiff_t sentResponse;
    WSBuf wsbuf;
    MI_Uint32 httpError;
    EnumerationState *enumerationState;
    ptrdiff_t ackOriginalPost;
    MI_Uint32 maxElements;
    Page *responsePage;
};

static void PostResult(WsmanClient *self, const MI_Char *message, MI_Result result, const Probable_Cause_Data *cause)
{
    if (Atomic_CompareAndSwap(&self->sentResponse, (ptrdiff_t)MI_FALSE, (ptrdiff_t)MI_TRUE)
        == (ptrdiff_t)MI_FALSE)
    {
        OMI_Error *newError;
        MI_Value valueId;
        MI_Value valueDesc;

        PostResultMsg *errorMsg = PostResultMsg_New(0);

        if (message)
        {
            errorMsg->errorMessage = Batch_Tcsdup(errorMsg->base.batch, message);
        }
        else
        {
            errorMsg->errorMessage = NULL;
        }
        errorMsg->result = result;
        if (cause)
        {
            OMI_ErrorFromErrorCode(errorMsg->base.batch, MI_RESULT_FAILED, MI_RESULT_TYPE_MI, cause->description, &newError);

            valueId.uint16 = cause->id;
            __MI_Instance_SetElement((MI_Instance*)newError, MI_T("ProbableCause"), &valueId, MI_UINT16, 0);
            valueDesc.string = (MI_Char*)cause->description;
            __MI_Instance_SetElement((MI_Instance*)newError, MI_T("ProbableCauseDescription"), &valueDesc, MI_STRING, 0);

            errorMsg->cimError = (const MI_Instance*)newError;
        }

        self->ackOriginalPost = 1;
        self->strand.info.otherMsg = &errorMsg->base;
        Message_AddRef(&errorMsg->base);
        Strand_ScheduleAux(&self->strand, PROTOCOLSOCKET_STRANDAUX_POSTMSG);

        PostResultMsg_Release(errorMsg);

    }

}

static void PostInstance(WsmanClient *self, PostInstanceMsg *msg)
{
    self->strand.info.otherMsg = &msg->base;
    Message_AddRef(&msg->base);
    Strand_ScheduleAux(&self->strand, PROTOCOLSOCKET_STRANDAUX_POSTMSG);
    PostInstanceMsg_Release(msg);
}

static void HttpClientCallbackOnConnectFn(
        HttpClient* http,
        void* callbackData)
{
    WsmanClient *self = (WsmanClient*) callbackData;
    Strand_ScheduleAux( &self->strand, PROTOCOLSOCKET_STRANDAUX_CONNECTEVENT );

}

static void HttpClientCallbackOnStatusFn2(
        HttpClient* http,
        void* callbackData,
        MI_Result result,
        const ZChar *text)
{
    WsmanClient *self = (WsmanClient*) callbackData;
    if (!self->enumerationState || self->enumerationState->endOfSequence)
    {
        PostResult(self, NULL, MI_RESULT_OK, NULL);
    }
#if 0

    {
        MI_Uint64 currentTimeUsec = 0;
        ProtocolBase* protocolBase = (ProtocolBase*)self->base.data;

        trace_ProtocolSocket_TimeoutTrigger( self );
        // provoke a timeout to close/delete the socket
        PAL_Time(&currentTimeUsec);
        self->base.fireTimeoutAt = currentTimeUsec;
        Selector_Wakeup(HttpClient_GetSelector(self->httpClient), MI_TRUE );
    }
#endif
}

void _WsmanClient_Post( _In_ Strand* self_, _In_ Message* msg);

static XML* InitializeXml(Page **data)
{
    XML *xml = NULL;
    char *buffer = (char*)(*data +1);
    xml = (XML *) PAL_Calloc(1, sizeof (XML));
    if (xml == NULL)
    {
        return NULL;
    }

    /* TODO: Handle BOM and UNICODE data and the likes */

    /* Initialize xml parser */
    XML_Init(xml);

    XML_RegisterNameSpace(xml, 's',
                          ZT("http://www.w3.org/2003/05/soap-envelope"));

    XML_RegisterNameSpace(xml, 'a',
                          ZT("http://schemas.xmlsoap.org/ws/2004/08/addressing"));

    XML_RegisterNameSpace(xml, 'w',
                          ZT("http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd"));

    XML_RegisterNameSpace(xml, 'n',
                          ZT("http://schemas.xmlsoap.org/ws/2004/09/enumeration"));

    XML_RegisterNameSpace(xml, 'b',
                          ZT("http://schemas.dmtf.org/wbem/wsman/1/cimbinding.xsd"));

    XML_RegisterNameSpace(xml, 'p',
                          ZT("http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd"));

    XML_RegisterNameSpace(xml, 'i',
                          ZT("http://schemas.dmtf.org/wbem/wsman/identity/1/wsmanidentity.xsd"));

    XML_RegisterNameSpace(xml, 'x',
                          ZT("http://www.w3.org/2001/XMLSchema-instance"));

    XML_RegisterNameSpace(xml, 'e',
                          ZT("http://schemas.xmlsoap.org/ws/2004/08/eventing"));

#ifndef DISABLE_SHELL
    XML_RegisterNameSpace(xml, MI_T('h'),
                          ZT("http://schemas.microsoft.com/wbem/wsman/1/windows/shell"));
#endif

    XML_SetText(xml, (ZChar*)buffer);

    return xml;
}

static MI_Boolean ProcessNormalResponse(WsmanClient *self, Page **data)
{
    DEBUG_ASSERT(NULL != data && NULL != *data);

    MI_Char *epr;
    WSMAN_WSHeader wsheaders;
    PostInstanceMsg *msg = NULL;
    MI_ConstString context = NULL;
    XML *xml;

    memset(&wsheaders, 0, sizeof(wsheaders));

    xml = InitializeXml(data);
    if (NULL == xml)
    {
        goto error;
    }

    msg = PostInstanceMsg_New(0);
    msg->instance = NULL;

    if ((WS_ParseSoapEnvelope(xml) != 0) ||
        xml->status)
    {
        goto error;
    }

    if ((WS_ParseWSHeader(xml, &wsheaders, USERAGENT_UNKNOWN) != 0) ||
        xml->status)
    {
        goto error;
    }

    if (MI_TRUE != wsheaders.foundAction)
    {
        goto error;
    }

    switch (wsheaders.rqtAction)
    {
    case WSMANTAG_ACTION_SHELL_COMMAND_RESPONSE:
    case WSMANTAG_ACTION_SHELL_SIGNAL_RESPONSE:
    case WSMANTAG_ACTION_SHELL_RECEIVE_RESPONSE:
    case WSMANTAG_ACTION_SHELL_SEND_RESPONSE:
    case WSMANTAG_ACTION_SHELL_CONNECT_RESPONSE:
    case WSMANTAG_ACTION_SHELL_RECONNECT_RESPONSE:
    case WSMANTAG_ACTION_SHELL_DISCONNECT_RESPONSE:
    case 0:   // invoked function
    {
        /*
        if (wsheaders.rqtClassname == NULL || wsheaders.rqtMethod == NULL)
        {
            goto error;
        }
        */

        if ((WS_ParseInstanceBody(xml, msg->base.batch, &msg->instance, wsheaders.rqtAction) != 0) ||
            xml->status)
        {
            goto error;
        }
        break;
    }

    case WSMANTAG_ACTION_GET_RESPONSE:
    case WSMANTAG_ACTION_PUT_RESPONSE:
    {
        if ((WS_ParseInstanceBody(xml, msg->base.batch, &msg->instance, wsheaders.rqtAction) != 0) ||
            xml->status)
        {
            goto error;
        }
        break;
    }
    case WSMANTAG_ACTION_CREATE_RESPONSE:
    {
        if ((WS_ParseCreateResponseBody(xml, msg->base.batch, &epr, &msg->instance) != 0) ||
            xml->status)
        {
            goto error;
        }
        break;
    }

    case WSMANTAG_ACTION_DELETE_RESPONSE:
    {
        if ((WS_ParseEmptyBody(xml) != 0) ||
            xml->status)
        {
            goto error;
        }
        break;
    }

    case WSMANTAG_ACTION_ENUMERATE_RESPONSE:
    {
        self->enumerationState->getNextInstance = MI_FALSE;
        self->enumerationState->endOfSequence = MI_FALSE;
        self->enumerationState->firstResponse = MI_TRUE;
        self->enumerationState->xml = xml;

        int ret = WS_ParseEnumerateResponse(self->enumerationState->xml, 
                                            &context,
                                            &self->enumerationState->endOfSequence, 
                                            msg->base.batch, 
                                            &msg->instance, 
                                            self->enumerationState->firstResponse, 
                                            &self->enumerationState->getNextInstance, 
                                            &self->enumerationState->e);
        if (( ret != 0) || xml->status)
        {
            goto error;
        }

        if (context && (!self->enumerationState->context || Tcscmp(self->enumerationState->context, context) != 0))
        {
            self->enumerationState->context = Batch_Tcsdup(self->batch, context);
        }

        break;
    }

    case WSMANTAG_ACTION_PULL_RESPONSE:
    {
        self->enumerationState->getNextInstance = MI_FALSE;
        self->enumerationState->endOfSequence = MI_FALSE;
        self->enumerationState->firstResponse = MI_FALSE;
        self->enumerationState->xml = xml;

        int ret = WS_ParseEnumerateResponse(self->enumerationState->xml, 
                                            &context,
                                            &self->enumerationState->endOfSequence, 
                                            msg->base.batch, 
                                            &msg->instance, 
                                            self->enumerationState->firstResponse, 
                                            &self->enumerationState->getNextInstance, 
                                            &self->enumerationState->e);
        if (( ret != 0) || xml->status)
        {
            goto error;
        }

        if (context && (!self->enumerationState->context || Tcscmp(self->enumerationState->context, context) != 0))
        {
            self->enumerationState->context = Batch_Tcsdup(self->batch, context);
        }

        break;
    }

    default:
    {
        goto error;
    }
    }

    if (!self->enumerationState || !self->enumerationState->getNextInstance)
    {
        PAL_Free(xml);
        if (self->enumerationState)
            self->enumerationState->xml = NULL;
    }
    else
    {
        self->responsePage = *data;
        *data = NULL;
    }

    PostInstance(self, msg);

    if (self->enumerationState)
    {
        return self->enumerationState->endOfSequence ? MI_FALSE : MI_TRUE;
    }
    else
    {
        return MI_FALSE;
    }

error:
    PostResult(self, MI_T("Internal error parsing Wsman response message"), MI_RESULT_FAILED, NULL);

    if (xml)
        PAL_Free(xml);
    if (msg)
        PostInstanceMsg_Release(msg);
    return MI_FALSE;

}

static MI_Boolean ProcessFaultResponse(WsmanClient *self, Page **data)
{

    WSMAN_WSHeader wsheaders;
    XML *xml;

    if (NULL == data || NULL == *data)
    {
        PostResult(self, MI_T("Server sent a fault with no fault message"), MI_RESULT_FAILED, NULL);
        return FALSE;
    }
    memset(&wsheaders, 0, sizeof(wsheaders));

    xml = InitializeXml(data);
    if (NULL == xml)
    {
        goto error;
    }

    if ((WS_ParseSoapEnvelope(xml) != 0) ||
        xml->status)
    {
        goto error;
    }

    if ((WS_ParseWSHeader(xml, &wsheaders, USERAGENT_UNKNOWN) != 0) ||
        xml->status)
    {
        goto error;
    }

    if (MI_TRUE != wsheaders.foundAction)
    {
        goto error;
    }

    switch (wsheaders.rqtAction)
    {
    case WSMANTAG_ACTION_FAULT_ADDRESSING:
    case WSMANTAG_ACTION_FAULT_ENUMERATION:
    case WSMANTAG_ACTION_FAULT_EVENTING:
    case WSMANTAG_ACTION_FAULT_TRANSFER:
    case WSMANTAG_ACTION_FAULT_WSMAN:
    {
        WSMAN_WSFault fault;
        MI_Result result;
        Error_Types errorType = ERROR_UNKNOWN;
        MI_Char *errorTypeStr = NULL;
        MI_Char wsmanFaultMsg[256];
        MI_Char *errorMessage;
        const Probable_Cause_Data *cause;

        if ((WS_ParseFaultBody(xml, &fault) != 0) ||
            xml->status)
        {
            goto error;
        }

        result = GetWsmanErrorFromSoapFault(
            fault.code,
            fault.subcode,
            fault.detail,
            &errorType,
            &errorTypeStr);

        if (result == MI_RESULT_FAILED)
        {
            errorTypeStr = ZT("UNKNOWN ERROR");
        }

        if (fault.mi_message == NULL)
        {
            Tcslcpy(wsmanFaultMsg, errorTypeStr, Tcslen(errorTypeStr) + 1);
            Tcscat(wsmanFaultMsg, 256, MI_T(": "));
            if (fault.reason)
                Tcscat(wsmanFaultMsg, 256, fault.reason);
            else if (fault.detail)
                Tcscat(wsmanFaultMsg, 256, fault.detail);

            errorMessage = wsmanFaultMsg;
        }
        else
        {
            errorMessage = fault.mi_message;
        }

        cause = GetWsmanCimError(errorType);

        if (self->enumerationState)
        {
            self->enumerationState->endOfSequence = 1;
        }

        PostResult(self, errorMessage, fault.mi_result > 0 ? fault.mi_result : MI_RESULT_FAILED, cause);

        PAL_Free(xml);
        return MI_FALSE;
    }

    default:
    {
        goto error;
    }
    }

error:
    PostResult(self, MI_T("Internal error parsing Wsman fault message"), MI_RESULT_FAILED, NULL);

    if (xml)
        PAL_Free(xml);
    return MI_FALSE;

}

static MI_Boolean HttpClientCallbackOnResponseFn(
        HttpClient* http,
        void* callbackData,
        const HttpClientResponseHeader* headers,
        MI_Sint64 contentSize,
        MI_Boolean  lastChunk,
        Page** data)
{
    WsmanClient *self = (WsmanClient*) callbackData;

    if (headers)
    {
        self->httpError = headers->httpError;
    }

    if (lastChunk && Atomic_Read(&self->sentResponse) == (ptrdiff_t)MI_FALSE) /* Only last chunk */
    {
        switch (self->httpError)
        {
        case 200:
            return ProcessNormalResponse(self, data);

        case 401:
            PostResult(self, MI_T("Access is denied."), MI_RESULT_ACCESS_DENIED, NULL);
            return MI_FALSE;

        case 500:
            return ProcessFaultResponse(self, data);

        default:
            PostResult(self, MI_T("Client did not get proper response from server."), MI_RESULT_FAILED, NULL);
            return MI_FALSE;
        }
    }
    else if (lastChunk && Atomic_Read(&self->sentResponse) == (ptrdiff_t)MI_TRUE)
        return MI_FALSE;
    else
        return MI_TRUE;
}

static void _WsmanClient_SendIn_IO_Thread(void *_self, Message* msg)
{
    WsmanClient *self = (WsmanClient*) _self;
    MI_Result miresult;
    Page *page = WSBuf_StealPage(&self->wsbuf);
    miresult = WsmanClient_StartRequest(self, &page);

    if (miresult != MI_RESULT_OK)
    {
        PostResult(self, NULL, MI_RESULT_NOT_SUPPORTED, NULL);

        /* NOTE: 
         * 1. Ack any messages?
         * 2. Close other side?
         */
    }
}

void _WsmanClient_Post( _In_ Strand* self_, _In_ Message* msg)
{
    WsmanClient* self = FromOffset( WsmanClient, strand, self_ );
    MI_Result miresult = MI_RESULT_NOT_SUPPORTED;
    MI_Value value;
    MI_Type type;
    MI_Uint32 flags;
    MI_Uint32 index;
    RequestMsg *requestMessage = (RequestMsg*) msg;

    DEBUG_ASSERT( NULL != self_ );

//    DEBUG_ASSERT(self->message == NULL);
//    self->base.mask &= ~SELECTOR_READ;

    trace_ProtocolSocket_PostingOnInteraction( &self->strand.info.interaction, self->strand.info.interaction.other );

    if ((MI_Instance_GetElement(requestMessage->options,
            MI_T("__MI_OPERATIONOPTIONS_TIMEOUT"),
            &value,
            &type,
            &flags,
            &index) == MI_RESULT_OK) &&
        ((flags & MI_FLAG_NULL) != MI_FLAG_NULL) &&
        (type == MI_DATETIME) &&
        (value.datetime.isTimestamp == MI_FALSE))
    {
        self->wsmanSoapHeaders.operationTimeout = value.datetime.u.interval;
    }

    if ((MI_Instance_GetElement(requestMessage->options,
        MI_T("__MI_OPERATIONOPTIONS_RESOURCE_URI"),
        &value,
        &type,
        &flags,
        &index) == MI_RESULT_OK) &&
        ((flags & MI_FLAG_NULL) != MI_FLAG_NULL) &&
        (type == MI_STRING))
    {
        self->wsmanSoapHeaders.resourceUri = value.string;
    }
    if ((MI_Instance_GetElement(requestMessage->options,
        MI_T("__MI_OPERATIONOPTIONS_ACTION"),
        &value,
        &type,
        &flags,
        &index) == MI_RESULT_OK) &&
        ((flags & MI_FLAG_NULL) != MI_FLAG_NULL) &&
        (type == MI_STRING))
    {
        self->wsmanSoapHeaders.action = value.string;
    }

    self->wsmanSoapHeaders.operationOptions = requestMessage->options;

    miresult = WSBuf_Init(&self->wsbuf, self->wsmanSoapHeaders.maxEnvelopeSize);
    if (miresult == MI_RESULT_OK)
    {
        switch (msg->tag)
        {
            case GetInstanceReqTag:
            {
                GetInstanceReq *getMessage = (GetInstanceReq*) msg;
                miresult = GetMessageRequest(&self->wsbuf, &self->wsmanSoapHeaders, getMessage);
                break;
            }

            case CreateInstanceReqTag:
            {
                CreateInstanceReq *createMessage = (CreateInstanceReq*) msg;
                miresult = CreateMessageRequest(&self->wsbuf, &self->wsmanSoapHeaders, createMessage);
                break;
            }

            case ModifyInstanceReqTag:
            {
                ModifyInstanceReq *putMessage = (ModifyInstanceReq*) msg;
                miresult = PutMessageRequest(&self->wsbuf, &self->wsmanSoapHeaders, putMessage);
                break;
            }

            case DeleteInstanceReqTag:
            {
                DeleteInstanceReq *deleteMessage = (DeleteInstanceReq*) msg;
                miresult = DeleteMessageRequest(&self->wsbuf, &self->wsmanSoapHeaders, deleteMessage);
                break;
            }

            case InvokeReqTag:
            {
                InvokeReq *invokeRequest = (InvokeReq*) msg;
                miresult = InvokeMessageRequest(&self->wsbuf, &self->wsmanSoapHeaders, invokeRequest);
                break;
            }

            case EnumerateInstancesReqTag:
            {
                EnumerateInstancesReq *enumerateRequest = (EnumerateInstancesReq*) msg;
                enumerateRequest->maxElements = self->maxElements;
                miresult = EnumerateMessageRequest(&self->wsbuf, &self->wsmanSoapHeaders, enumerateRequest);

                // save these for PullReq
                self->enumerationState = (EnumerationState*)
                    Batch_GetClear(self->batch, sizeof(EnumerationState));
                if (!self->enumerationState)
                {
                    miresult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
                    break;
                }

                self->enumerationState->nameSpace = Batch_Tcsdup(self->batch, enumerateRequest->nameSpace);
                self->enumerationState->className = Batch_Tcsdup(self->batch, enumerateRequest->className);
                if (self->enumerationState->nameSpace == NULL || self->enumerationState->className == NULL)
                {
                    miresult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
                }
                break;
            }

            case PullRequestTag:
            {
                PullReq *pullRequest = (PullReq*) msg;
                pullRequest->maxElements = self->maxElements;
                miresult = EnumeratePullRequest(&self->wsbuf, &self->wsmanSoapHeaders, pullRequest);

                break;
            }

            default:
            {
                miresult = MI_RESULT_NOT_SUPPORTED;
                break;
            }
        }
    }



    if(miresult == MI_RESULT_OK)
    {
        //self->closeOtherScheduled ||

        //Post this on to the IO thread to send it
        miresult = Selector_CallInIOThread( HttpClient_GetSelector(self->httpClient), _WsmanClient_SendIn_IO_Thread, self, msg );
    }

    if (miresult != MI_RESULT_OK)
    {
        trace_ProtocolSocket_PostFailed( &self->strand.info.interaction, self->strand.info.interaction.other );
        Strand_ScheduleAck( &self->strand );
        Strand_ScheduleAck( &self->strand );
    }
}

void _WsmanClient_PostControl( _In_ Strand* self, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // not used yet
}

void _WsmanClient_Ack( _In_ Strand* self_)
{
    WsmanClient* self = FromOffset( WsmanClient, strand, self_ );
    MI_Result miresult;
    MI_ConstString context = NULL;
    DEBUG_ASSERT( NULL != self_ );

    trace_ProtocolSocket_Ack( &self_->info.interaction, self_->info.interaction.other );
//    if (!(self->base.mask & SELECTOR_WRITE))
//       self->base.mask |= SELECTOR_READ;
//    Selector_Wakeup(HttpClient_GetSelector(self->httpClient), MI_FALSE );

    if (!self->enumerationState || self->enumerationState->endOfSequence)
    {
        if (self->enumerationState)
        {
            PAL_Free(self->enumerationState->xml);
            self->enumerationState->xml = NULL;
            PAL_Free(self->responsePage);
            self->responsePage = NULL;
        }

        PostResult(self, NULL, MI_RESULT_OK, NULL);
        if (Atomic_CompareAndSwap(&self->ackOriginalPost, 1, 0) == 1)
        {
            Strand_ScheduleAck(&self->strand);  /* We are done with this request so ack the original received post request */
        }
    }
    else
    {
        if (self->enumerationState->getNextInstance)
        {
            int ret;
            PostInstanceMsg *newMsg = PostInstanceMsg_New(0);
            if (!newMsg)
            {
                PostResult(self, MI_T("Failed to allocate memory for PostInstanceMsg"), MI_RESULT_FAILED, NULL);

                PAL_Free(self->enumerationState->xml);
                self->enumerationState->xml = NULL;
                return;
            }

            ret = WS_ParseEnumerateResponse(self->enumerationState->xml,
                                            &context,
                                            &self->enumerationState->endOfSequence,
                                            newMsg->base.batch,
                                            &newMsg->instance,
                                            self->enumerationState->firstResponse,
                                            &self->enumerationState->getNextInstance,
                                            &self->enumerationState->e);
            if (( ret != 0) || self->enumerationState->xml->status)
            {
                PostResult(self, MI_T("Internal error parsing Wsman Enumerate response message"), MI_RESULT_FAILED, NULL);

                PAL_Free(self->enumerationState->xml);
                self->enumerationState->xml = NULL;
                PostInstanceMsg_Release(newMsg);
                return;
            }
            else
            {
                if (context && (!self->enumerationState->context || Tcscmp(self->enumerationState->context, context) != 0))
                {
                    self->enumerationState->context = Batch_Tcsdup(self->batch, context);
                }
                PostInstance(self, newMsg);
            }
        }
        else
        {
            PullReq *req = NULL;

            PAL_Free(self->enumerationState->xml);
            self->enumerationState->xml = NULL;
            PAL_Free(self->responsePage);
            self->responsePage = NULL;

            req = PullReq_New(123456, WSMANFlag);
            if (!req)
            {
                PostResult(self, MI_T("Failed to allocate memory for Pull Request message"), MI_RESULT_FAILED, NULL);
                return;
            }

            req->nameSpace = self->enumerationState->nameSpace;
            req->className = self->enumerationState->className;
            req->context = self->enumerationState->context;

            req->maxElements = self->maxElements;

            WSBuf_Destroy(&self->wsbuf);
            miresult = WSBuf_Init(&self->wsbuf, self->wsmanSoapHeaders.maxEnvelopeSize);
            if (miresult != MI_RESULT_OK)
            {
                PostResult(self, MI_T("Failed to initialize WSMan buffer"), MI_RESULT_FAILED, NULL);
                return;
            }

            miresult = EnumeratePullRequest(&self->wsbuf, &self->wsmanSoapHeaders, req);

            if(miresult == MI_RESULT_OK)
            {
                miresult = Selector_CallInIOThread( HttpClient_GetSelector(self->httpClient), _WsmanClient_SendIn_IO_Thread, self, (Message*)req );
                if (miresult != MI_RESULT_OK)
                {
                    PostResult(self, MI_T("Failed to post Pull Request message"), MI_RESULT_FAILED, NULL);
                    return;
                }
            }
        }
    }

}
void _WsmanClient_CheckAbort( _In_ WsmanClient* self )
{
    if( !self->strand.info.thisClosedOther )
    {
        MI_Uint64 currentTimeUsec = 0;

        trace_ProtocolSocket_TimeoutTrigger( self );
        // provoke a timeout to close/delete the socket
        PAL_Time(&currentTimeUsec);
        HttpClient_WakeUpSelector(self->httpClient, currentTimeUsec);
    }
}
void _WsmanClient_Cancel( _In_ Strand* self_)
{
    WsmanClient* self = FromOffset( WsmanClient, strand, self_ );

    trace_ProtocolSocket_CancelReceived(
        self->strand.info.thisClosedOther,

        &self->strand.info.interaction,
        self->strand.info.interaction.other );

    // Abort the socket
    _WsmanClient_CheckAbort( self );
}
void _WsmanClient_Close( _In_ Strand* self_)
{
    WsmanClient* self = FromOffset( WsmanClient, strand, self_ );

    trace_ProtocolSocket_Close(
        self->strand.info.thisClosedOther,
        &self->strand.info.interaction,
        self->strand.info.interaction.other );


    if( !self->strand.canceled )
    {
        _WsmanClient_CheckAbort( self );
    }

    Strand_ScheduleClose(self_);
}
void _WsmanClient_Finish( _In_ Strand* self_)
{
    WsmanClient* self = FromOffset( WsmanClient, strand, self_ );
    trace_ProtocolSocket_Finish( self );

    if (self->responsePage)
        PAL_Free(self->responsePage);

    WsmanClient_Delete(self);
}
// PROTOCOLSOCKET_STRANDAUX_POSTMSG
void _WsmanClient_Aux_PostMsg( _In_ Strand* self_)
{
    WsmanClient* self = FromOffset( WsmanClient, strand, self_ );
//    ProtocolBase* protocolBase = (ProtocolBase*)self->base.data;
    Message * msg = self->strand.info.otherMsg;

    self->strand.info.otherMsg = NULL;

    if( !self->strand.info.thisClosedOther )
    {
        // process the case where the interaction for the connection has not been opened yet
#if 0
        if( NULL != protocolBase->callback && NULL == self->strand.info.interaction.other )
        {
            Strand_Open( self_, protocolBase->callback, protocolBase->callbackData, NULL, MI_FALSE );
        }
        if( Message_IsRequest(msg) )
        {
            RequestMsg* request = (RequestMsg*)msg;
            AuthInfo_Copy( &request->authInfo, &self->authInfo );
        }
#endif

        DEBUG_ASSERT( NULL != self->strand.info.interaction.other );

        // Leave the strand for the case where this is a new request on server
        // and the provider is in-proc and takes over the thread
        Strand_PostAndLeaveStrand( &self->strand, msg );
    }

    // now we can remove the reference added before Strand_ScheduleAux( PROTOCOLSOCKET_STRANDAUX_POSTMSG )
    Message_Release( msg );
}
// PROTOCOLSOCKET_STRANDAUX_READYTOFINISH
void _WsmanClient_Aux_ReadyToFinish( _In_ Strand* self_)
{
    Strand_ResetDelayFinish(self_);
}
// PROTOCOLSOCKET_STRANDAUX_CONNECTEVENT
void _WsmanClient_Aux_ConnectEvent( _In_ Strand* self_)
{
    WsmanClient* self = FromOffset( WsmanClient, strand, self_ );
    ProtocolEventConnect* msg = ProtocolEventConnect_New(/*self->isConnected*/ MI_TRUE);

    DEBUG_ASSERT( NULL != self->strand.info.interaction.other );

    Strand_PostControl( &self->strand, &msg->base );
    Message_Release(&msg->base);
}

static StrandFT _WsmanClient_FT =
{
    _WsmanClient_Post,
    _WsmanClient_PostControl,
    _WsmanClient_Ack,
    _WsmanClient_Cancel,
    _WsmanClient_Close,
    _WsmanClient_Finish,
    NULL,
    _WsmanClient_Aux_PostMsg,
    _WsmanClient_Aux_ReadyToFinish,
    _WsmanClient_Aux_ConnectEvent,
    NULL,
    NULL
};
// Call this once it is out of the selector run loop
void WsmanClient_ReadyToFinish( WsmanClient* self)
{
    Strand_ScheduleAux( &self->strand, PROTOCOLSOCKET_STRANDAUX_READYTOFINISH );
}


MI_Result WsmanClient_New_Connector(
        WsmanClient **selfOut,
        Selector *selector,
        const MI_Char* host,
        MI_DestinationOptions *options,
        InteractionOpenParams *params)
{
    Batch *batch;
    WsmanClient *self;
    MI_Result miresult;
    MI_Boolean secure = MI_FALSE;

    *selfOut = NULL;

    batch = Batch_New(BATCH_MAX_PAGES);
    if (batch == NULL)
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;

    self = (WsmanClient*) Batch_GetClear(batch, sizeof(WsmanClient));
    if (!self)
    {
        miresult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        goto finished;
    }

    self->batch = batch;

    {
        const MI_Char *transport;
        miresult = MI_DestinationOptions_GetTransport(options, &transport);
        if (miresult == MI_RESULT_OK)
        {
            if (Tcscmp(transport, MI_DESTINATIONOPTIONS_TRANSPORT_HTTP) == 0)
            {
                 secure = MI_FALSE;
                 self->wsmanSoapHeaders.port = CONFIG_HTTPPORT; /* TODO: This needs to be read from the configuration file! */
            }
            else if (Tcscmp(transport, MI_DESTINATIONOPTIONS_TRANPSORT_HTTPS) == 0)
            {
                 secure = MI_TRUE;
                 self->wsmanSoapHeaders.port = CONFIG_HTTPSPORT; /* TODO: This needs to be read from the configuration file! */
            }
            else
            {
                 miresult = MI_RESULT_INVALID_PARAMETER;
                 goto finished;
            }
            self->wsmanSoapHeaders.protocol = Batch_Tcsdup(batch, transport);
            if (self->wsmanSoapHeaders.protocol == NULL)
            {
                 miresult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
                 goto finished;
            }
        }
        else if (miresult == MI_RESULT_NO_SUCH_PROPERTY)
        {
            /* Set defaults for a few things. */
            secure = MI_FALSE;

            self->wsmanSoapHeaders.protocol = MI_T("http");

            self->wsmanSoapHeaders.port = CONFIG_HTTPPORT; /* TODO: This needs to be read from the configuration file! */
        }
        else
            goto finished;
    }

    if (host != NULL)
    {
        self->wsmanSoapHeaders.hostname = Batch_Tcsdup(batch, host);
        if (self->wsmanSoapHeaders.hostname == NULL)
        {
            miresult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            goto finished;
        }
    }
    else
        self->wsmanSoapHeaders.hostname = MI_T("localhost");

    self->hostname = Batch_ZStrdup(batch, host);
    if (self->hostname == NULL)
    {
        miresult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        goto finished;
    }

    {
        MI_Uint32 tmpPort;
        miresult = MI_DestinationOptions_GetDestinationPort(options, &tmpPort);
        if (miresult == MI_RESULT_OK)
        {
            /* Port exists so override default */
            self->wsmanSoapHeaders.port = (MI_Uint16) tmpPort;
        }
        else if (miresult != MI_RESULT_NO_SUCH_PROPERTY)
            goto finished;
    }


    /* Retrieve custom http URL if one exists and convert to utf8 */
    {
        const MI_Char *httpUrl_t;

        miresult = MI_DestinationOptions_GetHttpUrlPrefix(options, &httpUrl_t);
        if ( miresult == MI_RESULT_OK)
        {
            self->wsmanSoapHeaders.httpUrl = Batch_Tcsdup(batch, httpUrl_t);
            if (self->wsmanSoapHeaders.httpUrl == NULL)
            {
                miresult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
                goto finished;
            }
            self->httpUrl = Batch_ZStrdup(batch, httpUrl_t);
            if (self->httpUrl == NULL)
            {
                miresult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
                goto finished;
            }
        }
        else if (miresult != MI_RESULT_NO_SUCH_PROPERTY)
        {
            goto finished;
        }
        else
        {
            self->wsmanSoapHeaders.httpUrl = MI_T("/wsman/");
            self->httpUrl = "/wsman/";
        }
    }

    {
        const MI_Char *packetEncoding;
#if defined(CONFIG_ENABLE_WCHAR)
        /* If packet encoding is in options then it must be UTF16 until we implement the conversion */
        if ((MI_DestinationOptions_GetPacketEncoding(options, &packetEncoding) == MI_RESULT_OK) &&
                (Tcscmp(packetEncoding, MI_DESTINATIONOPTIONS_PACKET_ENCODING_UTF16) != 0))
        {
            miresult = MI_RESULT_INVALID_PARAMETER;
            goto finished;
        }
        self->contentType = "Content-Type: application/soap+xml;charset=UTF-16";

        if (!WSMAN_UTF16_IMPLEMENTED)
        {
            /* We don't yet implement utf-16 BOM. Fail */

            miresult = MI_RESULT_INVALID_PARAMETER;
            goto finished;/* We cannot add a UTF-16 BOM to the front yet so need to fail */
        }
#else
        /* If packet encoding is in options then it must be UTF8 until we implement the conversion */
        if ((MI_DestinationOptions_GetPacketEncoding(options, &packetEncoding) == MI_RESULT_OK) &&
                (Tcscmp(packetEncoding, MI_DESTINATIONOPTIONS_PACKET_ENCODING_UTF8) != 0))
        {
            miresult = MI_RESULT_INVALID_PARAMETER;
            goto finished;
        }
        self->contentType = "Content-Type: application/soap+xml;charset=UTF-8";
#endif
    }

    if (MI_DestinationOptions_GetMaxEnvelopeSize(options, &self->wsmanSoapHeaders.maxEnvelopeSize) != MI_RESULT_OK)
    {
        self->wsmanSoapHeaders.maxEnvelopeSize = DEFAULT_MAX_ENV_SIZE;
    }
    else
    {
        self->wsmanSoapHeaders.maxEnvelopeSize *= 1024;
    }

    if (MI_DestinationOptions_GetMaxElements(options, &self->maxElements) != MI_RESULT_OK)
    {
        self->maxElements = DEFAULT_MAX_ELEMENTS;
    }

    if (MI_DestinationOptions_GetTimeout(options, &self->wsmanSoapHeaders.operationTimeout) != MI_RESULT_OK)
    {
        memset(&self->wsmanSoapHeaders.operationTimeout, 0, sizeof(self->wsmanSoapHeaders.operationTimeout));
        self->wsmanSoapHeaders.operationTimeout.minutes = 1;
    }

    {
        const MI_Char *tmpStr;
        if (MI_DestinationOptions_GetDataLocale(options, &tmpStr) != MI_RESULT_OK)
        {
            tmpStr = MI_T("en-us");
        }
        self->wsmanSoapHeaders.dataLocale = Batch_Tcsdup(batch, tmpStr);
        if (self->wsmanSoapHeaders.dataLocale == NULL)
        {
            miresult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            goto finished;
        }
    }

    {
        const MI_Char *tmpStr;
        if (MI_DestinationOptions_GetUILocale(options, &tmpStr) != MI_RESULT_OK)
        {
            tmpStr = MI_T("en-us");
        }
        self->wsmanSoapHeaders.locale = Batch_Tcsdup(batch, tmpStr);
        if (self->wsmanSoapHeaders.locale == NULL)
        {
            miresult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            goto finished;
        }
    }

    Strand_Init( STRAND_DEBUG(WsmanClientConnector) &self->strand, &_WsmanClient_FT, STRAND_FLAG_ENTERSTRAND, params);

    Strand_SetDelayFinish(&self->strand);
    Strand_Leave(&self->strand);

    /* NOTE: For SSL we have CA/CN check validation/disabling options that will need to be handled */
    /* also revocation checks */
    miresult = HttpClient_New_Connector2(
                                &self->httpClient, selector,
                                self->hostname, self->wsmanSoapHeaders.port, secure,
                                HttpClientCallbackOnConnectFn, HttpClientCallbackOnStatusFn2, HttpClientCallbackOnResponseFn,
                                self, NULL, NULL, NULL, options);
    if (miresult != MI_RESULT_OK)
    {
        goto finished2;
    }

    *selfOut = self;

finished:
    if (miresult != MI_RESULT_OK)
    {
        Batch_Delete(batch);
    }

finished2:
    return miresult;
}

MI_Result WsmanClient_Delete(WsmanClient *self)
{
    HttpClient_Delete(self->httpClient);
    Batch_Delete(self->batch);

    return MI_RESULT_OK;
}


MI_Result WsmanClient_StartRequest(WsmanClient* self, Page** data)
{
    return HttpClient_StartRequestV2(self->httpClient, "POST", self->httpUrl, self->contentType, NULL, NULL, data);
}


MI_Result WsmanClient_Run(WsmanClient* self, MI_Uint64 timeoutUsec)
{
    return HttpClient_Run(self->httpClient, timeoutUsec);
}
