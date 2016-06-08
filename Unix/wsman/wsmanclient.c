/*
**==============================================================================
**
**  Open Management Infrastructure (OMI)
**
**  Copyright (c) Microsoft Corporation
**
**  Licensed under the Apache License, Version 2.0 (the "License"); you may not
**  use this file except in compliance with the License. You may obtain a copy
**  of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
**  THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
**  KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
**  WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
**  MERCHANTABLITY OR NON-INFRINGEMENT.
**
**  See the Apache 2 License for the specific language governing permissions
**  and limitations under the License.
**
**==============================================================================
*/
#include <pal/palcommon.h>
#include <pal/strings.h>
#include <base/base64.h>
#include <base/batch.h>
#include <base/messages.h>
#include <base/log.h>
#include <http/httpclient.h>
#include "wsmanclient.h"

#define PROTOCOLSOCKET_STRANDAUX_POSTMSG 0
#define PROTOCOLSOCKET_STRANDAUX_READYTOFINISH  1
#define PROTOCOLSOCKET_STRANDAUX_CONNECTEVENT 2

STRAND_DEBUGNAME3( WsmanClientConnector, PostMsg, ReadyToFinish, ConnectEvent );

typedef struct _WsmanClient_Headers
{
    MI_Char *protocol;
    MI_Char *hostname;
    MI_Uint32 port;
    MI_Char *httpUrl;
    MI_Char *resourceUri;
    MI_Uint32 maxEnvelopeSize;
    MI_Char *locale;
    MI_Char *dataLocale;
    MI_Interval operationTimeout;
    MI_OperationOptions *operationOptions;
} WsmanClient_Headers;

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
    MI_Boolean sentResponse;

};
static void HttpClientCallbackOnConnectFn(
        HttpClient* http,
        void* callbackData)
{
    WsmanClient *self = (WsmanClient*) callbackData;
    Strand_ScheduleAux( &self->strand, PROTOCOLSOCKET_STRANDAUX_CONNECTEVENT );

}
static void HttpClientCallbackOnStatusFn(
        HttpClient* http,
        void* callbackData,
        MI_Result result)
{
    WsmanClient *self = (WsmanClient*) callbackData;
    PostResultMsg *message = PostResultMsg_New(0);
    if (self->sentResponse)
    {
        message->result = MI_RESULT_OK;
    }
    else
    {
        message->result = result;
    }
    self->sentResponse = MI_TRUE;

    self->strand.info.otherMsg = &message->base;
    Message_AddRef(&message->base);
    Strand_ScheduleAux(&self->strand, PROTOCOLSOCKET_STRANDAUX_POSTMSG);
    Message_Release(&message->base);
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

static MI_Result WsmanClient_CreateAuthHeader(Batch *batch, MI_DestinationOptions *options, char **finalAuthHeader);

static MI_Boolean HttpClientCallbackOnResponseFn(
        HttpClient* http,
        void* callbackData,
        const HttpClientResponseHeader* headers,
        MI_Sint64 contentSize,
        MI_Boolean  lastChunk,
        Page** data)
{
    WsmanClient *self = (WsmanClient*) callbackData;
    if (lastChunk && !self->sentResponse) /* Only last chunk */
    {
        MI_Value val;
        PostInstanceMsg *msg = PostInstanceMsg_New(0);
        val.string = MI_T("Value");
        Instance_NewDynamic(&msg->instance, MI_T("goo"), MI_FLAG_CLASS, msg->base.batch);
        MI_Instance_AddElement(msg->instance, MI_T("prop"), &val, MI_STRING, 0);
        self->sentResponse = MI_TRUE;

        //TODO: Parse response and create message
        self->strand.info.otherMsg = &msg->base;
        Message_AddRef(&msg->base);
        Strand_ScheduleAux(&self->strand, PROTOCOLSOCKET_STRANDAUX_POSTMSG);
        Message_Release(&msg->base);
        return MI_FALSE;
    }
    else if (lastChunk && self->sentResponse)
        return MI_FALSE;
    else
        return MI_TRUE;
}

#define TEST_SENDBODY_REQUEST ""\
"<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\"" \
            " xmlns:a=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\"" \
            " xmlns:w=\"http://schemas.dmtf.org/wbem/wsman/1/wsman.xsd\"" \
            " xmlns:p=\"http://schemas.microsoft.com/wbem/wsman/1/wsman.xsd\">"\
    "<s:Header>"\
        "<a:To>http://localhost:7778/wsman</a:To>"\
        "<w:ResourceURI s:mustUnderstand=\"true\">http://schemas.microsoft.com/wbem/wscim/1/cim-schema/2/X_smallNumber</w:ResourceURI>"\
        "<a:ReplyTo><a:Address s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</a:Address></a:ReplyTo>"\
        "<a:Action s:mustUnderstand=\"true\">http://schemas.xmlsoap.org/ws/2004/09/transfer/Get</a:Action>"\
        "<w:MaxEnvelopeSize s:mustUnderstand=\"true\">327680</w:MaxEnvelopeSize>"\
        "<a:MessageID>uuid:E8928068-D73B-4206-9E95-894088B96288</a:MessageID>" \
        "<w:Locale xml:lang=\"en-US\" s:mustUnderstand=\"false\" />"\
        "<p:DataLocale xml:lang=\"en-US\" s:mustUnderstand=\"false\" />"\
        "<w:SelectorSet>"\
            "<w:Selector Name=\"__cimnamespace\">test/cpp</w:Selector>"\
            "<w:Selector Name=\"Number\">17</w:Selector>"\
        "</w:SelectorSet>"\
        "<w:OperationTimeout>PT60.000S</w:OperationTimeout>"\
    "</s:Header>"\
    "<s:Body>"\
    "</s:Body>"\
"</s:Envelope>"


static void _WsmanClient_SendIn_IO_Thread(void *_self, Message* msg)
{
    WsmanClient *self = (WsmanClient*) _self;
    switch (msg->tag & MessageTagIndexMask)
    {
        case GetInstanceReqTag:
        {
            char *text;
            Page *page = (Page*) PAL_Malloc(sizeof(Page)+sizeof(TEST_SENDBODY_REQUEST)-1);
            memset(page, 0, sizeof(Page));
            page->u.s.size = sizeof(TEST_SENDBODY_REQUEST)-1;
            text = (char*)(page+1);
            memcpy(text, TEST_SENDBODY_REQUEST, sizeof(TEST_SENDBODY_REQUEST) - 1);
            WsmanClient_StartRequest(self, &page);

            break;
        }
        default:
        {
            /* TODO: Post an error for not supported */
            PostResultMsg *message = PostResultMsg_New(0);
            if (self->sentResponse)
            {
                 message->result = MI_RESULT_OK;
            }
            else
            {
                 message->result = MI_RESULT_NOT_SUPPORTED;
            }
            self->sentResponse = MI_TRUE;

            self->strand.info.otherMsg = &message->base;
            Message_AddRef(&message->base);
            Strand_ScheduleAux(&self->strand, PROTOCOLSOCKET_STRANDAUX_POSTMSG);

            break;
        }
    }
}

void _WsmanClient_Post( _In_ Strand* self_, _In_ Message* msg)
{
    WsmanClient* self = FromOffset( WsmanClient, strand, self_ );

    DEBUG_ASSERT( NULL != self_ );

//    DEBUG_ASSERT(self->message == NULL);
//    self->base.mask &= ~SELECTOR_READ;

    trace_ProtocolSocket_PostingOnInteraction( &self->strand.info.interaction, self->strand.info.interaction.other );

    if( //self->closeOtherScheduled ||
        ( MI_RESULT_OK != Selector_CallInIOThread(
        HttpClient_GetSelector(self->httpClient), _WsmanClient_SendIn_IO_Thread, self, msg ) ))
    {
        trace_ProtocolSocket_PostFailed( &self->strand.info.interaction, self->strand.info.interaction.other );
        Strand_ScheduleAck( &self->strand );
    }
}
void _WsmanClient_PostControl( _In_ Strand* self, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // not used yet
}
void _WsmanClient_Ack( _In_ Strand* self_)
{
//    WsmanClient* self = FromOffset( WsmanClient, strand, self_ );
//    ProtocolBase* protocolBase = (ProtocolBase*)self->base.data;
    DEBUG_ASSERT( NULL != self_ );

    trace_ProtocolSocket_Ack( &self_->info.interaction, self_->info.interaction.other );
//    if (!(self->base.mask & SELECTOR_WRITE))
//       self->base.mask |= SELECTOR_READ;
//    Selector_Wakeup(HttpClient_GetSelector(self->httpClient), MI_FALSE );
}
void _WsmanClient_Cancel( _In_ Strand* self_)
{
    WsmanClient* self = FromOffset( WsmanClient, strand, self_ );

    trace_ProtocolSocket_CancelReceived(
        self->strand.info.thisClosedOther,
        &self->strand.info.interaction,
        self->strand.info.interaction.other );

#if 0
    // Abort the socket
    _ProtocolSocket_CheckAbort( self );
#endif
}
void _WsmanClient_Close( _In_ Strand* self_)
{
    WsmanClient* self = FromOffset( WsmanClient, strand, self_ );

    trace_ProtocolSocket_Close(
        self->strand.info.thisClosedOther,
        &self->strand.info.interaction,
        self->strand.info.interaction.other );

#if 0
    if( !self->strand.canceled )
    {
        _ProtocolSocket_CheckAbort( self );
    }
#endif
}
void _WsmanClient_Finish( _In_ Strand* self_)
{
#if 0
    WsmanClient* self = FromOffset( WsmanClient, strand, self_ );
    ProtocolBase* protocolBase = (ProtocolBase*)self->base.data;
    DEBUG_ASSERT( NULL != self_ );

    trace_ProtocolSocket_Finish( self );

    if( protocolBase->type == PRT_TYPE_LISTENER )
    {
        _ProtocolSocket_Delete( self );
    }
    else
    {
        _ProtocolSocketAndBase_Delete( (ProtocolSocketAndBase*)self );
    }
#endif
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
    const char* trustedCertDir = NULL; /* Needs to be extracted from options */
    const char* certFile = NULL; /* Needs to be extracted from options */
    const char* privateKeyFile = NULL; /* Needs to be extracted from options */

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

    miresult = WsmanClient_CreateAuthHeader(batch, options, &self->authorizationHeader);
    if (miresult != MI_RESULT_OK)
    {
        return miresult;
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
            self->wsmanSoapHeaders.httpUrl = MI_T("wsman/");
            self->httpUrl = "wsman/";
        }
    }

    {
        const MI_Char *packetEncoding;
#if defined(CONFIG_ENABLE_WCHAR)
        /* If packet encoding is in options then it must be UTF16 until we implement the conversion */
        if ((MI_DestinationOptions_GetPacketEncoding(options, &packetEncoding) == MI_RESULT_OK) &&
                (Tcscmp(packetEncoding, MI_DESTINATIONOPTIONS_PACKET_ENCODING_UTF16) != 0))
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
        self->contentType = "Content-Type: application/soap+xml;charset=UTF-16";
        return MI_RESULT_INVALID_PARAMETER; /* We cannot add a UTF-16 BOM to the front yet so need to fail */
#else
        /* If packet encoding is in options then it must be UTF8 until we implement the conversion */
        if ((MI_DestinationOptions_GetPacketEncoding(options, &packetEncoding) == MI_RESULT_OK) &&
                (Tcscmp(packetEncoding, MI_DESTINATIONOPTIONS_PACKET_ENCODING_UTF8) != 0))
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
        self->contentType = "Content-Type: application/soap+xml;charset=UTF-8";
#endif
    }

    Strand_Init( STRAND_DEBUG(WsmanClientConnector) &self->strand, &_WsmanClient_FT, STRAND_FLAG_ENTERSTRAND, params);

    Strand_SetDelayFinish(&self->strand);
    Strand_Leave(&self->strand);

    /* NOTE: For SSL we have CA/CN check validation/disabling options that will need to be handled */
    /* also revocation checks */
    miresult = HttpClient_New_Connector2(
            &self->httpClient, selector,
            self->hostname, self->wsmanSoapHeaders.port, secure,
            HttpClientCallbackOnConnectFn, HttpClientCallbackOnStatusFn, HttpClientCallbackOnResponseFn, self,
            trustedCertDir, certFile, privateKeyFile);
    if (miresult != MI_RESULT_OK)
        goto finished;

finished:
    if (miresult != MI_RESULT_OK)
    {
        Batch_Delete(batch);
    }
    else
    {
        *selfOut = self;
    }

    return miresult;
}

MI_Result WsmanClient_Delete(WsmanClient *self)
{
    HttpClient_Delete(self->httpClient);
    Batch_Delete(self->batch);

    return MI_RESULT_OK;
}

#define AUTHORIZE_HEADER_BASIC "Authorization: Basic "

typedef struct _PasswordEncData
{
    Batch *batch;
    char *buffer;
    MI_Uint32 bufferLength;
} PasswordEncData;

static int _passwordEnc(
        const char* data,
        size_t size,
        void* callbackData)
{
    PasswordEncData *bufferData = (PasswordEncData*) callbackData;
    bufferData->bufferLength = sizeof(AUTHORIZE_HEADER_BASIC) + size;
    bufferData->buffer = (char *) Batch_Get(bufferData->batch, bufferData->bufferLength);
    if (bufferData->buffer == NULL)
    {
        return -1;
    }

    Strlcpy(bufferData->buffer, AUTHORIZE_HEADER_BASIC, bufferData->bufferLength);


    strncpy(bufferData->buffer+sizeof(AUTHORIZE_HEADER_BASIC)-1, data, size);
    bufferData->buffer[bufferData->bufferLength-1] = '\0';
    return 0;
}

static MI_Result WsmanClient_CreateAuthHeader(Batch *batch, MI_DestinationOptions *options, char **finalAuthHeader)
{
    MI_Uint32 credCount;
    const MI_Char *optionName;
    MI_UserCredentials userCredentials;
    MI_Uint32 passwordLength;
    MI_Char *password; /* password from options */
    const MI_Char *username; /* username from option */
    char *authUsernamePassword; /* <username>:<password> in ansi ready for base64-encoding */
    MI_Uint32 authUsernamePasswordLength;
    PasswordEncData base64EncData;

    base64EncData.batch = batch;

    /* Must have one and only one credential */
    if ((MI_DestinationOptions_GetCredentialsCount(options, &credCount) != MI_RESULT_OK) ||
            (credCount != 1))
    {
        return MI_RESULT_ACCESS_DENIED;
    }

    /* Get username pointer from options.
     * Auth scheme must be basic as only one we support.
     * Option name must be __MI_DESTINATIONOPTIONS_DESTINATION_CREDENTIALS
     */
    if ((MI_DestinationOptions_GetCredentialsAt(options, 0, &optionName, &userCredentials, NULL) != MI_RESULT_OK) ||
        (Tcscmp(optionName, MI_T("__MI_DESTINATIONOPTIONS_DESTINATION_CREDENTIALS")) != 0) ||
        (Tcscmp(userCredentials.authenticationType, MI_AUTH_TYPE_BASIC) != 0))
    {
        return MI_RESULT_ACCESS_DENIED;
    }

    username = userCredentials.credentials.usernamePassword.username;

    /* We need to allocate a buffer for the password.
     * Get length of it, allocate and then retrieve it.
     */
    if (MI_DestinationOptions_GetCredentialsPasswordAt(options, 0, &optionName, NULL, 0, &passwordLength, NULL) != MI_RESULT_OK)
    {
        return MI_RESULT_ACCESS_DENIED;
    }

    password = (MI_Char*) PAL_Malloc(passwordLength * sizeof(MI_Char));
    if (password == NULL)
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    if (MI_DestinationOptions_GetCredentialsPasswordAt(options, 0, &optionName, password, passwordLength, &passwordLength, NULL) != MI_RESULT_OK)
    {
        PAL_Free(password);
        return MI_RESULT_FAILED;
    }

    /* Convert username and password into format needed for auth "<username>:<password>" as ANSI string */
    authUsernamePasswordLength = Tcslen(username) + 1 /* : */ + Tcslen(password);
    authUsernamePassword = (char*) PAL_Malloc(authUsernamePasswordLength + 1);
    if (authUsernamePassword == NULL)
    {
        PAL_Free(password);
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    StrTcslcpy(authUsernamePassword, username, authUsernamePasswordLength+1);
    Strlcat(authUsernamePassword, ":", authUsernamePasswordLength+1);
    StrTcslcat(authUsernamePassword, password, authUsernamePasswordLength+1);

    PAL_Free(password);

    /* Now we need to base64 encode the username:password string. We may as well
     * put the result in the final buffer
     */
    if (Base64Enc(authUsernamePassword, authUsernamePasswordLength, _passwordEnc, &base64EncData) == -1)
    {
        PAL_Free(authUsernamePassword);
        return MI_RESULT_FAILED;
    }

    /* Free up extra memory and set out parameter. We are done. */
    PAL_Free(authUsernamePassword);
    *finalAuthHeader = base64EncData.buffer;

    return MI_RESULT_OK;
}

MI_Result WsmanClient_StartRequest(WsmanClient* self, Page** data)
{
    const char *headerItems[] = { self->contentType, self->authorizationHeader };
    HttpClientRequestHeaders headers = { headerItems, MI_COUNT(headerItems) };

    return HttpClient_StartRequest(self->httpClient, "POST", self->httpUrl, &headers, data);
}

MI_Result WsmanClient_Run(WsmanClient* self, MI_Uint64 timeoutUsec)
{
    return HttpClient_Run(self->httpClient, timeoutUsec);
}
