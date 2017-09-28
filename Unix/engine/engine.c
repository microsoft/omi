/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <server/server.h>

static Options s_opts;
static ServerData s_data;
static Lock s_disp_mutex = LOCK_INITIALIZER;

/*
    Simple interaction object to respond to the noop request.
    It just sends a noop response and closes the interaction
    (therefore shutting down)
*/
void _NoopInteractionAck( _In_ Strand* self) 
{
    // do nothing
}

StrandFT _NoopInteractionUserFT = { 
        NULL, 
        NULL, 
        _NoopInteractionAck, 
        NULL, 
        NULL, 
        NULL,
        NULL,
        NULL, 
        NULL, 
        NULL, 
        NULL, 
        NULL };

STRAND_DEBUGNAME( NoopRequest )

static void _ProcessNoopRequest(_Inout_ InteractionOpenParams*  params)
{
    Strand* strand;
    NoOpReq* req = (NoOpReq*)params->msg;
    NoOpRsp* rsp;

#if !defined(CONFIG_FAVORSIZE)
    if (s_opts.trace)
    {
        NoOpReq_Print(req, stdout);
    }
#endif
            
    strand = Strand_New( STRAND_DEBUG( NoopRequest ) &_NoopInteractionUserFT, 0, STRAND_FLAG_ENTERSTRAND, params );

    if( NULL == strand )
    {
        trace_OutOfMemory();
        Strand_FailOpen(params);
        err(ZT("out of memory"));
    }

    /* Send NoOp response back */
    rsp = NoOpRsp_New(req->base.base.operationId);

    if (!rsp)
    {
        trace_OutOfMemory();
        Strand_FailOpen(params);
        err(ZT("out of memory"));
    }

#if !defined(CONFIG_FAVORSIZE)
    if (s_opts.trace)
    {
        NoOpRsp_Print(rsp, stdout);
    }
#endif

    Strand_Ack( strand );   // Ack open msg
    Strand_Post( strand, &rsp->base );
    Strand_Close( strand );   
    Strand_Leave( strand);
    
    NoOpRsp_Release(rsp);

    trace_ServerReceivedNoOpReqTag( (int)s_opts.terminateByNoop );
    
    if (s_opts.terminateByNoop)
    {
        s_data.terminated = MI_TRUE;
        Selector_StopRunning(&s_data.selector);
    }
}

static MI_Boolean _ProcessPamCheckUserResp(
    Message *msg)
{
    PamCheckUserResp* pamMsg;
    MI_Result result;

    if (msg->tag != PamCheckUserRespTag)
        return MI_FALSE;

    pamMsg = (PamCheckUserResp*) msg;

    // engine waiting server's response

    result = InvokeAuthenticateCallback(pamMsg);

    return (MI_RESULT_OK == result) ? MI_TRUE : MI_FALSE;
}

void EngineCallback(
    _Inout_ InteractionOpenParams* interactionParams)
{
    ServerCallbackData* self = (ServerCallbackData*)interactionParams->callbackData;
    Message* msg = interactionParams->msg;

    DEBUG_ASSERT( NULL != interactionParams );
    DEBUG_ASSERT( NULL != msg );

    MI_Result result;

    if (NoOpReqTag == msg->tag)
    {
        _ProcessNoopRequest(interactionParams);
        return;
    }
    else if (msg->tag == PamCheckUserRespTag)
    {
        if( _ProcessPamCheckUserResp(msg) )
            return;
    }

#if !defined(CONFIG_FAVORSIZE)
    if (s_opts.trace)
    {
        MessagePrint(msg, stdout);
    }
#endif
    
    Lock_Acquire(&s_disp_mutex);
    result = Disp_HandleInteractionRequest(
                &self->data->disp, 
                interactionParams );
    Lock_Release(&s_disp_mutex);
    if( result != MI_RESULT_OK )
    {
        Strand_FailOpenWithResult(interactionParams, result, PostResultMsg_NewAndSerialize);
    }
}

MI_Result WsmanProtocolListen()
{
    MI_Result r = MI_RESULT_OK;

    /* Set WSMAN options and create WSMAN server */
    s_data.wsman_size = s_opts.httpport_size + s_opts.httpsport_size;
    if ( s_data.wsman_size > 0 )
    {
        s_data.wsman = PAL_Calloc(s_data.wsman_size, sizeof(WSMAN*));
        if ( s_data.wsman == NULL )
        {
            err(ZT("memory allocation failure allocating %d bytes"), s_data.wsman_size * sizeof(WSMAN*));
        }
    }

    {
        int wsman_count = 0;
        WSMAN_Options options = DEFAULT_WSMAN_OPTIONS;
#if !defined(CONFIG_FAVORSIZE)
        options.enableTracing = s_opts.trace;
#endif
        options.enableHTTPTracing = s_opts.httptrace;

        /* Start up the non-encrypted listeners */
        int count;
        for ( count = 0; count < s_opts.httpport_size; ++count )
        {
            r = WSMAN_New_Listener(
                &s_data.wsman[wsman_count++],
                &s_data.selector, 
                s_opts.httpport[count],
                0,
                s_opts.sslCipherSuite,
                s_opts.sslOptions,
                EngineCallback,
                &s_data.wsmanData,
                &options);

            if (r != MI_RESULT_OK)
            {
                err(ZT("WSMAN_New_Listener() failed for port %u. Err = %d"), s_opts.httpport[count], r);
            }

            /* Log start up message */
            trace_ListeningOnPort(s_opts.httpport[count]);
        }

        /* Start up the encrypted listeners */
        for ( count = 0; count < s_opts.httpsport_size; ++count )
        {
            r = WSMAN_New_Listener(
                &s_data.wsman[wsman_count++],
                &s_data.selector, 
                0,
                s_opts.httpsport[count],
                s_opts.sslCipherSuite,
                s_opts.sslOptions,
                EngineCallback,
                &s_data.wsmanData,
                &options);

            if (r != MI_RESULT_OK)
            {
                err(ZT("WSMAN_New_Listener() failed for encrypted port %u. Err = %d"), s_opts.httpsport[count], r);
            }

            /* Log start up message */
            trace_ListeningOnEncryptedPort(s_opts.httpsport[count]);
        }
    }

    return r;
}

int enginemain(int argc, const char* argv[])
{
    int pidfile = -1;
    MI_Result result;

    SetDefaults(&s_opts, &s_data, argv[0], OMI_ENGINE, &s_disp_mutex);

    /* Get --destdir command-line option */
    GetCommandLineDestDirOption(&argc, argv);

    /* Extract configuration file options */
    GetConfigFileOptions();

    /* Extract command-line options a second time (to override) */
    GetCommandLineOptions(&argc, argv);

#if defined(CONFIG_POSIX)

    /* ATTN: unit-test support; should be removed/ifdefed later */
    if (s_opts.ignoreAuthentication)
    {
        IgnoreAuthCalls(1);
    }

    /* Watch for SIGTERM signals */
    if (0 != SetSignalHandler(SIGTERM, HandleSIGTERM) ||
        0 != SetSignalHandler(SIGHUP, HandleSIGHUP) ||
        0 != SetSignalHandler(SIGUSR1, HandleSIGUSR1))
    {
        err(ZT("cannot set sighandler, errno %d"), errno);
    }

#endif

    /* Change directory to 'rundir' */
    if (Chdir(OMI_GetPath(ID_RUNDIR)) != 0)
    {
        err(ZT("failed to change directory to: %s"), scs(OMI_GetPath(ID_RUNDIR)));
    }

    while (!s_data.terminated)
    {
        MI_Boolean r;

        trace_Product_Version(CONFIG_PRODUCT, CONFIG_VERSION, CONFIG_PLATFORM);

        result = InitializeNetwork();
        if (result != MI_RESULT_OK)
        {
            err(ZT("Failed to initialize network"));
        }

        result = WsmanProtocolListen();
        if (result != MI_RESULT_OK)
        {
            err(ZT("Failed to initialize Wsman"));
        }

        // binary connection with server
        result = BinaryProtocolListenSock(s_opts.socketpairPort, &s_data.mux[1], &s_data.protocol1, NULL, NULL);
        if (result != MI_RESULT_OK)
        {
            err(ZT("Failed to initialize binary protocol for socket"));
        }
        s_data.protocol1->protocolSocket.permanent = MI_TRUE;

        result = Initialize_ProtocolSocketTracker();
        if (result != MI_RESULT_OK)
        {
            err(ZT("Failed to initialize binary protocol tracker for engine"));
        }

        r = SendSocketFileRequest(&s_data.protocol1->protocolSocket);
        if (r == MI_FALSE)
        {
            err(ZT("failed to send socket file request"));
        }

        // binary connection with client
        const char *path = OMI_GetPath(ID_SOCKETFILE);
        result = BinaryProtocolListenFile(path, &s_data.mux[0], &s_data.protocol0, NULL);
        if (result != MI_RESULT_OK)
        {
            err(ZT("Failed to initialize binary protocol for socket file"));
        }

        result = RunProtocol();
        if (result != MI_RESULT_OK)
        {
            err(ZT("Failed protocol loop"));
        }
    }

    Sock_Close(s_opts.socketpairPort);
    ServerCleanup(pidfile);

    return 0;
}
