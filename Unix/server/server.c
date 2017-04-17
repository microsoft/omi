/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <limits.h>
#include <protocol/protocol.h>
#include <pal/sleep.h>
#include <wsman/wsman.h>
#include <provreg/provreg.h>
#include <provmgr/provmgr.h>
#include <disp/disp.h>
#include <pal/strings.h>
#include <pal/dir.h>
#include <base/log.h>
#include <base/env.h>
#include <base/process.h>
#include <base/pidfile.h>
#include <base/paths.h>
#include <base/conf.h>
#include <base/user.h>
#include <base/omigetopt.h>
#include <base/multiplex.h>
#include <base/Strand.h>
#include <pal/format.h>
#include <pal/lock.h>

#if defined(CONFIG_POSIX)
# include <signal.h>
# include <sys/wait.h>
# include <pthread.h>
#endif

typedef struct _ServerData ServerData;

typedef enum _ServerTransportType
{
    SRV_PROTOCOL,
    SRV_WSMAN
}
ServerTransportType;

typedef struct _ServerCallbackData
{
    ServerData*         data;
    ServerTransportType type;
}
ServerCallbackData;

struct _ServerData
{
    Disp            disp;
    MuxIn           mux;
    ProtocolBase*   protocol;
    WSMAN**         wsman;
    int             wsman_size;
    Selector        selector;
    MI_Boolean      selectorInitialized;
    MI_Boolean      reloadDispFlag;
    MI_Boolean      terminated;

    /* pointers to self with different types - one per supported transport */
    ServerCallbackData  protocolData;
    ServerCallbackData  wsmanData;
} ;

typedef struct _Options
{
    MI_Boolean help;
#if !defined(CONFIG_FAVORSIZE)
    MI_Boolean trace;
#endif
    MI_Boolean httptrace;
    MI_Boolean terminateByNoop;
#if defined(CONFIG_POSIX)
    MI_Boolean daemonize;
    MI_Boolean stop;
    MI_Boolean reloadConfig;
    MI_Boolean reloadDispatcher;
#endif
    /* mostly for unittesting in non-root env */
    MI_Boolean ignoreAuthentication;
    MI_Boolean locations;
    MI_Boolean logstderr;
    unsigned short *httpport;
    int httpport_size;
    unsigned short *httpsport;
    int httpsport_size;
    char* sslCipherSuite;
    SSL_Options sslOptions;
    MI_Uint64 idletimeout;
    MI_Uint64 livetime;
    Log_Level logLevel;
    char *ntlmCredFile;
}
Options;

static Lock s_disp_mutex = LOCK_INITIALIZER;

static Options s_opts;

static ServerData s_data;

static const char* arg0 = 0;

static const ZChar HELP[] = ZT("\
Usage: %s [OPTIONS]\n\
\n\
This program starts the server.\n\
\n\
OPTIONS:\n\
    -h, --help                  Print this help message.\n\
    -d                          Daemonize the server process (POSIX only).\n\
    -s                          Stop the server process (POSIX only).\n\
    -r                          Re-read configuration by the running server (POSIX only).\n\
    --reload-dispatcher         Re-read configuration by the running server (POSIX only), but don't unload providers.\n\
    --httpport PORT             HTTP protocol listener port.\n\
    --httpsport PORT            HTTPS protocol listener port.\n\
    --idletimeout TIMEOUT       Idle providers unload timeout (in seconds).\n\
    -v, --version               Print version information.\n\
    -l, --logstderr             Send log output to standard error.\n\
    --loglevel LEVEL            Set logging level to one of the following\n\
                                symbols/numbers: fatal/0, error/1, warning/2,\n\
                                info/3, debug/4, verbose/5 (default 2).\n\
    --httptrace                 Enable logging of HTTP traffic.\n\
    --timestamp                 Print timestamp server was built with.\n\
\n");

STRAND_DEBUGNAME( NoopRequest )

static void FUNCTION_NEVER_RETURNS err(const ZChar* fmt, ...)
{
    va_list ap;
    memset(&ap, 0, sizeof(ap));

    Ftprintf(stderr, ZT("%s: "), scs(arg0));

    va_start(ap, fmt);
    Vftprintf(stderr, fmt, ap);
    va_end(ap);

    /* Write to log as well */
    va_start(ap, fmt);
    __LOGE((fmt, ap));
    va_end(ap);

    Ftprintf(stderr, ZT("\n"));
    exit(1);
}

static void FUNCTION_NEVER_RETURNS info_exit(const ZChar* fmt, ...)
{
    va_list ap;
    memset(&ap, 0, sizeof(ap));

    Ftprintf(stderr, ZT("%s: "), scs(arg0));

    va_start(ap, fmt);
    Vftprintf(stderr, fmt, ap);
    va_end(ap);

    /* Write to log as well */
    va_start(ap, fmt);
    __LOGI((fmt, ap));
    va_end(ap);

    Ftprintf(stderr, ZT("\n"));
    exit(0);
}

void PrintProviderMsg( _In_ Message* msg)
{
#if !defined(CONFIG_FAVORSIZE)
    if (s_opts.trace)
    {
        switch ( msg->tag )
        {
            case PostResultMsgTag:
            {
                const PostResultMsg* rsp = (const PostResultMsg*)msg;
                PostResultMsg_Print(rsp, stdout);
            }
            break;

            case PostInstanceMsgTag:
            {
                const PostInstanceMsg* rsp = (const PostInstanceMsg*)msg;
                PostInstanceMsg_Print(rsp, stdout);
            }
            break;

            case PostSchemaMsgTag:
            {
                const PostSchemaMsg* rsp = (const PostSchemaMsg*)msg;
                PostSchemaMsg_Print(rsp, stdout);
            }
            break;

            case NoOpRspTag:
                break;  // send noop confirmation to the client 

            default:
            {
                trace_UnknownMessageType(msg->tag);
                exit(1);
            }
        }
    }
#endif // !defined(CONFIG_FAVORSIZE)
}

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

static void _ProcessNoopRequest(
    _Inout_     InteractionOpenParams*  params )
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
        err(ZT("out of memory"));
        trace_OutOfMemory();
        Strand_FailOpen(params);
        return;
    }

    /* Send NoOp response back */
    rsp = NoOpRsp_New(req->base.base.operationId);

    if (!rsp)
    {
        err(ZT("out of memory"));
        trace_OutOfMemory();
        Strand_FailOpen(params);
        return;
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

/* Called by protocol stack to dispatch an incoming request message */
static void _RequestCallback(
    _Inout_ InteractionOpenParams* interactionParams )
{
    ServerCallbackData* self = (ServerCallbackData*)interactionParams->callbackData;
    Message* msg = interactionParams->msg;
    MI_Result result;

    DEBUG_ASSERT( NULL != interactionParams );
    DEBUG_ASSERT( NULL != msg );
    
    if (NoOpReqTag == msg->tag)
    {
        _ProcessNoopRequest( interactionParams );
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
 
static void GetCommandLineDestDirOption(
    int* argc_,
    const char* argv[])
{
    int argc = *argc_;
    int i;
    const char* destdir = NULL;

    for (i = 1; i < argc; )
    {
        if (strcmp(argv[i], "--destdir") == 0)
        {
            if (i + 1 == argc)
                err(ZT("missing argument for --destdir option"));

            destdir = argv[i+1];
            memmove((char*)&argv[i], (char*)&argv[i+2], 
                sizeof(char*) * (argc-i-1));
            argc -= 2;
        }
        else if (strncmp(argv[i], "--destdir=", 10) == 0)
        {
            destdir = argv[i] + 10;
            memmove((char*)&argv[i], (char*)&argv[i+1], 
                sizeof(char*) * (argc-i));

            argc -= 1;
        }
        else
            i++;
    }

    if (destdir)
    {
        if (SetPath(ID_DESTDIR, destdir) != 0)
            err(ZT("failed to set destdir"));
    }

    *argc_ = argc;
}

/*
 * Parse an HTTP or HTTPS port specification:
 *
 *   "1270" would simply place 1270 in the list,
 *   "1270,5599" would place port 1270 and port 5599 to the list
 *
 * Returns 0 if parameter was good, non-zero if parameter was bad
 */
static int ParseHttpPortSpecification(unsigned short **ports, int *size, const char *spec, unsigned short defport)
{
    // defport is unused (no longer support "+" to add default port
    (void) defport;

    // Ignore anything that is already stored
    *size = 0;

    // Skip leading spaces
    char *saveptr;
    char *ptr = (char *) spec;
    while (*ptr == ' ')
    {
        ptr++;
    }

    while ( 1 )
    {
        unsigned long x;
        char *end = NULL;

        char *token = Strtok(ptr, ",", &saveptr);
        ptr = NULL;
        if (NULL == token)
        {
            break;
        }

        x = Strtoul(token, &end, 10);
        if (*end != '\0' || x > USHRT_MAX)
        {
            return 1;
        }

        /* Don't add a port of '0' */
        if ( x != 0 )
        {
            /* Don't add duplicate ports; just ignore second port */
            int found = 0, i;
            for (i = 0; i < (*size); ++i)
            {
                if ( (*ports)[i] == x )
                {
                    found = 1;
                    break;
                }
            }

            if ( ! found )
            {
                int bytes = ++(*size) * sizeof(unsigned int);
                *ports = PAL_Realloc(*ports, bytes);
                if ( (*ports) == 0 )
                {
                    err(ZT("memory allocation failure allocating %d bytes"), bytes);
                }

                (*ports)[(*size) - 1] = x;
            }
        }
    }

    return 0;
}

static void GetCommandLineOptions(
    int* argc_,
    const char* argv[])
{
    int argc = *argc_;
    GetOptState state = GETOPTSTATE_INITIALIZER;
    static const char* opts[] =
    {
        "-h",
        "--help",
        "-p",
        "-t",
        "--httptrace",
        "--timestamp",
        "--stopnoop",
        "-v",
        "--version",
        "-d",
        "-s",
        "-r",
        "--httpport:",
        "--httpsport:",
        "--idletimeout:",
        "--livetime:",
        "--ignoreAuthentication",
        "-i",
        "--prefix:",
        "--libdir:",
        "--bindir:",
        "--localstatedir:",
        "--sysconfdir:",
        "--providerdir:",
                "--registerdir:",
        "--certsdir:",
        "--rundir:",
        "--logdir:",
        "--pidfile:",
        "--logfile:",
        "--configfile:",
        "--socketfile:",
        "--pemfile:",
        "--keyfile:",
        "--agentprogram:",
        "--serverprogram:",
        "--logstderr",
        "--loglevel:",
        "-l",
        "--testopts",
        "--reload-dispatcher",
        NULL,
    };

    for (;;)
    {
        int r = GetOpt(&argc, argv, opts, &state);

        if (r == 1)
            break;

        if (r == -1)
        {
            Ftprintf(stderr, ZT("error: %s\n"), scs(state.err));
            exit(1);
        }

        if (strcmp(state.opt, "-h") == 0 ||
            strcmp(state.opt, "--help") == 0)
        {
            s_opts.help = MI_TRUE;
        }
        else if (strcmp(state.opt, "-p") == 0)
        {
            s_opts.locations = MI_TRUE;
        }
#if !defined(CONFIG_FAVORSIZE)
        else if (strcmp(state.opt, "-t") == 0)
        {
            s_opts.trace = MI_TRUE;
        }
#endif
        else if (strcmp(state.opt, "--httptrace") == 0)
        {
            s_opts.httptrace = MI_TRUE;
        }
        else if (strcmp(state.opt, "--timestamp") == 0)
        {
#if defined(CONFIG_OS_WINDOWS)
            Tprintf(PAL_T("%s: %T\n"), scs(arg0), tcs(CONFIG_TIMESTAMP));
#else
            Tprintf(ZT("%s: %s\n"), scs(arg0), scs(CONFIG_TIMESTAMP));
#endif
            exit(0);
        }
        else if (strcmp(state.opt, "--stopnoop") == 0)
        {
            s_opts.terminateByNoop = MI_TRUE;
        }
        else if (strcmp(state.opt, "-v") == 0 ||
                strcmp(state.opt, "--version") == 0)
        {
#if defined(CONFIG_OS_WINDOWS)
            Tprintf(PAL_T("%s: %T\n"), scs(arg0),
                tcs(CONFIG_PRODUCT PAL_T("-") CONFIG_VERSION PAL_T(" - ") CONFIG_DATE));
#else
            Tprintf(ZT("%s: %s\n"), scs(arg0),
                scs(CONFIG_PRODUCT "-" CONFIG_VERSION " - " CONFIG_DATE));
#endif
            exit(0);
        }
#if defined(CONFIG_POSIX)
        else if (strcmp(state.opt, "-d") == 0)
        {
            s_opts.daemonize = MI_TRUE;
        }
        else if (strcmp(state.opt, "-s") == 0)
        {
            s_opts.stop = MI_TRUE;
        }
        else if (strcmp(state.opt, "-r") == 0)
        {
            s_opts.reloadConfig = MI_TRUE;
        }
        else if (strcmp(state.opt, "--reload-dispatcher") == 0)
        {
            s_opts.reloadDispatcher = MI_TRUE;
        }
#endif
        else if (strcmp(state.opt, "--httpport") == 0)
        {
            if ( ParseHttpPortSpecification(&s_opts.httpport, &s_opts.httpport_size, state.arg, CONFIG_HTTPPORT) )
            {
                err(ZT("bad option argument for --httpport: %s"), 
                    scs(state.arg));
            }
        }
        else if (strcmp(state.opt, "--httpsport") == 0)
        {
            if ( ParseHttpPortSpecification(&s_opts.httpsport, &s_opts.httpsport_size, state.arg, CONFIG_HTTPSPORT) )
            {
                err(ZT("bad option argument for --httpsport: %s"), 
                    scs(state.arg));
            }
        }
        else if (strcmp(state.opt, "--idletimeout") == 0)
        {
            char* end;
            MI_Uint64 x = Strtoull(state.arg, &end, 10);

            if (*end != '\0')
            {
                err(ZT("bad option argument for --idletimeout: %s"), 
                    scs(state.arg));
            }

            s_opts.idletimeout = x;
        }
        else if (strcmp(state.opt, "--livetime") == 0)
        {
            char* end;
            MI_Uint64 x = Strtoull(state.arg, &end, 10);

            if (*end != '\0')
            {
                err(ZT("bad option argument for --livetime: %s"), 
                    scs(state.arg));
            }

            s_opts.livetime = x;
        }
        else if (strcmp(state.opt, "--ignoreAuthentication") == 0 ||
             strcmp(state.opt, "-i") == 0)
        {
            s_opts.ignoreAuthentication = MI_TRUE;
        }
        else if (strcmp(state.opt, "--logstderr") == 0 ||
             strcmp(state.opt, "-l") == 0)
        {
            s_opts.logstderr = MI_TRUE;
        }
        else if (strcmp(state.opt, "--loglevel") == 0)
        {
            if (Log_SetLevelFromString(state.arg) != 0)
            {
                err(ZT("bad option argument for %s: %s"), 
                    scs(state.opt), scs(state.arg));
            }
        }
        else if (strcmp(state.opt, "--testopts") == 0)
        {
            s_opts.httptrace = MI_TRUE;

            if (Log_SetLevelFromString("DEBUG") != 0)
            {
                err(ZT("bad argument for Log_SetLevelFromString()"));
            }
        }
        else if (strncmp(state.opt, "--", 2) == 0 && IsNickname(state.opt+2))
        {
            if (SetPathFromNickname(state.opt+2, state.arg) != 0)
                err(ZT("SetPathFromNickname() failed"));
        }
    }

    *argc_ = argc;
}

static void OpenLogFile()
{
    if (s_opts.logstderr)
    {
        if (Log_OpenStdErr() != MI_RESULT_OK)
            err(ZT("failed to open log file to stderr"));
    }
    else
    {
        TChar path[PAL_MAX_PATH_SIZE];
        TcsStrlcpy(path, OMI_GetPath(ID_LOGFILE), MI_COUNT(path));

        /* Open the log file */
        if (Log_Open(path) != MI_RESULT_OK)
            err(PAL_T("failed to open log file: %T"), tcs(path));
    }
}

#if defined(CONFIG_POSIX)

static void _HandleSIGTERM(int sig)
{
    if (sig == SIGTERM && s_data.selectorInitialized)
    {
        const char* socketFile = OMI_GetPath(ID_SOCKETFILE);
        s_data.terminated = MI_TRUE;
        Selector_StopRunning(&s_data.selector);
        if (socketFile != NULL && *socketFile != '\0')
            unlink(socketFile);
    }
}

static void _HandleSIGHUP(int sig)
{
    if (sig == SIGHUP && s_data.selectorInitialized)
    {
        Selector_StopRunning(&s_data.selector);
    }
}

// We reload the ProvReg structure in the Dispatcher when this signal is received.
// This gives us access to providers that are installed after the omiserver is running without terminating current providers that are running.
static void _HandleSIGUSR1(int sig)
{
    if (sig == SIGUSR1)
    {
        s_data.reloadDispFlag = MI_TRUE;
    }
}

/* An array of PIDS that abnormally exited */
#define NPIDS 16
static pid_t _pids[NPIDS];
static volatile size_t _npids;

static void _HandleSIGCHLD(int sig)
{
    if (sig == SIGCHLD)
    {
        for (;;)
        {
            int status = 0;
            pid_t pid = waitpid(-1, &status, WNOHANG);

            /* If abnormal exit, append to PIDs array */
            if (pid > 0 && !WIFEXITED(status))
            {
                /* Save PID so error can be logged outside this function */
                if (_npids < NPIDS)
                    _pids[_npids++] = pid;
            }

            if (pid > 0 || (pid == -1 && errno == EINTR))
                continue;

            break;
        }
    }
}

#endif /* defined(CONFIG_POSIX) */

static void _PrintPaths()
{
    PrintPaths();
}

static void GetConfigFileOptions()
{
    char path[PAL_MAX_PATH_SIZE];
    Conf* conf;

    /* Form the configuration file path */
    Strlcpy(path, OMI_GetPath(ID_CONFIGFILE), sizeof(path));

    /* Open the configuration file */
    conf = Conf_Open(path);
    if (!conf)
        err(ZT("failed to open configuration file: %s"), scs(path));

    /* For each key=value pair in configuration file */
    for (;;)
    {
        const char* key;
        const char* value;
        int r = Conf_Read(conf, &key, &value);

        if (r == -1)
            err(ZT("%s: %s\n"), path, scs(Conf_Error(conf)));

        if (r == 1)
            break;

        if (strcmp(key, "httpport") == 0)
        {
            if ( ParseHttpPortSpecification(&s_opts.httpport, &s_opts.httpport_size, value, CONFIG_HTTPPORT) )
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), 
                    Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "httpsport") == 0)
        {
            if ( ParseHttpPortSpecification(&s_opts.httpsport, &s_opts.httpsport_size, value, CONFIG_HTTPSPORT) )
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), 
                    Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "idletimeout") == 0)
        {
            char* end;
            MI_Uint64 x = Strtoull(value, &end, 10);

            if (*end != '\0')
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), 
                    Conf_Line(conf), scs(key), scs(value));
            }

            s_opts.idletimeout = x;
        }
        else if (strcmp(key, "livetime") == 0)
        {
            char* end;
            MI_Uint64 x = Strtoull(value, &end, 10);

            if (*end != '\0')
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), 
                    Conf_Line(conf), scs(key), scs(value));
            }

            s_opts.livetime = x;
        }
        else if (strcmp(key, "trace") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
#if !defined(CONFIG_FAVORSIZE)
                s_opts.trace = MI_TRUE;
#endif
            }
            else if (Strcasecmp(value, "false") == 0)
            {
#if !defined(CONFIG_FAVORSIZE)
                s_opts.trace = MI_FALSE;
#endif
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), 
                    Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "httptrace") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                s_opts.httptrace = MI_TRUE;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                s_opts.httptrace = MI_FALSE;
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), 
                    Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "loglevel") == 0)
        {
            if (Log_SetLevelFromString(value) != 0)
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), 
                    Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "sslciphersuite") == 0)
        {
            size_t valueLength = strlen(value);
            s_opts.sslCipherSuite = PAL_Malloc(valueLength + 1);
            if (s_opts.sslCipherSuite == NULL)
                err(ZT("Out of memory"));
            Strlcpy(s_opts.sslCipherSuite, value, valueLength+1);
            s_opts.sslCipherSuite[valueLength] = '\0';
        }
        else if (strcmp(key, "NoSSLv2") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                s_opts.sslOptions |= DISABLE_SSL_V2;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                s_opts.sslOptions &= ~DISABLE_SSL_V2;
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path),
                    Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "NoSSLv3") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                s_opts.sslOptions |= DISABLE_SSL_V3;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                s_opts.sslOptions &= ~DISABLE_SSL_V3;
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path),
                    Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "NoTLSv1_0") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                s_opts.sslOptions |= DISABLE_TSL_V1_0;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                s_opts.sslOptions &= ~DISABLE_TSL_V1_0;
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path),
                    Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "NoTLSv1_1") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                s_opts.sslOptions |= DISABLE_TSL_V1_1;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                s_opts.sslOptions &= ~DISABLE_TSL_V1_1;
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path),
                    Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "NoTLSv1_2") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                s_opts.sslOptions |= DISABLE_TSL_V1_2;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                s_opts.sslOptions &= ~DISABLE_TSL_V1_2;
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path),
                    Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "NoSSLCompression") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                s_opts.sslOptions |= DISABLE_SSL_COMPRESSION;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                s_opts.sslOptions &= ~DISABLE_SSL_COMPRESSION;
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path),
                    Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (IsNickname(key))
        {
            if (SetPathFromNickname(key, value) != 0)
                err(ZT("SetPathFromNickname() failed"));
        }
        else if (strcasecmp(key, "NtlmCredsFile") == 0)
        {
            if (value)
            {
                s_opts.ntlmCredFile = PAL_Strdup(value);
            }
        }
        else
        {
            err(ZT("%s(%u): unknown key: %s"), scs(path), Conf_Line(conf), 
                scs(key));
        }
    }

    /* Close configuration file */
    Conf_Close(conf);

    return;
}

int servermain(int argc, const char* argv[])
{
    MI_Result r;
#if defined(CONFIG_POSIX)
    int pidfile = -1;
#endif

    arg0 = argv[0];

    memset(&s_data, 0, sizeof(s_data));

    /* Set default options */
    s_opts.httpport = PAL_Malloc(sizeof(unsigned short));
    s_opts.httpport[0] = CONFIG_HTTPPORT;
    s_opts.httpport_size = 1;

    s_opts.httpsport = PAL_Malloc(sizeof(unsigned short));
    s_opts.httpsport[0] = CONFIG_HTTPSPORT;
    s_opts.httpsport_size = 1;

    s_opts.sslOptions = DISABLE_SSL_V2;
    s_opts.idletimeout = 0;
    s_opts.livetime = 0;

    /* Get --destdir command-line option */
    GetCommandLineDestDirOption(&argc, argv);

    /* Extract configuration file options */
    GetConfigFileOptions();

    /* Extract command-line options a second time (to override) */
    GetCommandLineOptions(&argc, argv);

    /* Open the log file */
    OpenLogFile();

    /* Print help */
    if (s_opts.help)
    {
        Ftprintf(stderr, HELP, scs(arg0));
        exit(1);
    }

    /* Print locations of files and directories */
    if (s_opts.locations)
    {
        _PrintPaths();
        Tprintf(ZT("\n"));
        exit(0);
    }

#if defined(CONFIG_POSIX)
    if (s_opts.stop || s_opts.reloadConfig)
    {
        if (PIDFile_IsRunning() != 0)
            info_exit(ZT("server is not running\n"));

        if (PIDFile_Signal(s_opts.stop ? SIGTERM : SIGHUP) != 0)
            err(ZT("failed to stop server\n"));

        if (s_opts.stop)
            Tprintf(ZT("%s: stopped server\n"), scs(arg0));
        else
            Tprintf(ZT("%s: refreshed server\n"), scs(arg0));

        exit(0);
    }
    if (s_opts.reloadDispatcher)
    {
        if (PIDFile_IsRunning() != 0)
            info_exit(ZT("server is not running\n"));

        if (PIDFile_Signal(SIGUSR1) != 0)
            err(ZT("failed to reload dispatcher on the server\n"));

        Tprintf(ZT("%s: server has reloaded its dispatcher\n"), scs(arg0));

        exit(0);        
    }
#endif

#if defined(CONFIG_POSIX)

    if (PIDFile_IsRunning() == 0)
        err(ZT("server is already running\n"));

    /* Verify that server is started as root */
    if (0 != IsRoot() && !s_opts.ignoreAuthentication)
    {
        err(ZT("expected to run as root"));
    }

    /* ATTN: unit-test support; should be removed/ifdefed later */
    if (s_opts.ignoreAuthentication)
    {
        IgnoreAuthCalls(1);
    }

    /* Watch for SIGTERM signals */
    if (0 != SetSignalHandler(SIGTERM, _HandleSIGTERM) ||
        0 != SetSignalHandler(SIGHUP, _HandleSIGHUP) ||
        0 != SetSignalHandler(SIGUSR1, _HandleSIGUSR1))
        err(ZT("cannot set sighandler, errno %d"), errno);


    /* Watch for SIGCHLD signals */
    SetSignalHandler(SIGCHLD, _HandleSIGCHLD);

#endif

    /* Change directory to 'rundir' */
    if (Chdir(OMI_GetPath(ID_RUNDIR)) != 0)
    {
        err(ZT("failed to change directory to: %s"), 
            scs(OMI_GetPath(ID_RUNDIR)));
    }

#if defined(CONFIG_POSIX)
    /* Daemonize */
    if (s_opts.daemonize && Process_Daemonize() != 0)
        err(ZT("failed to daemonize server process"));
#endif

#if defined(CONFIG_POSIX)

    /* Create PID file */
    if ((pidfile = PIDFile_OpenWrite()) == -1)
    {
        fprintf(stderr, "Could not create pid file %s\n", OMI_GetPath(ID_PIDFILE));
        trace_CreatePIDFileFailed( scs(OMI_GetPath(ID_PIDFILE)) );

        // Need to let the world know. We may not have a functioning log system at this point
        // or know to look

        fprintf(stderr, "Cannot create PID file. omi server exiting\n");
        exit(1);
    }

#endif

    /* If ntlm cred file is in use, check permissions and set NTLM_USER_FILE env variable */

    char *ntlm_user_file = getenv("NTLM_USER_FILE");
    if (ntlm_user_file)
    {
        /* We do NOT accept the NTLM_USER_FILE environement variable for the server */
        trace_NtlmEnvIgnored(ntlm_user_file);
        unsetenv("NTLM_USER_FILE");
    }

    if (s_opts.ntlmCredFile && !s_opts.ignoreAuthentication)
    {
       if (!ValidateNtlmCredsFile(s_opts.ntlmCredFile))
       {
           trace_NtlmCredFileInvalid(s_opts.ntlmCredFile);
       }
    }


    /* Initialize calback parameters */
    s_data.protocolData.data = &s_data;
    s_data.protocolData.type = SRV_PROTOCOL;
    s_data.wsmanData.data = &s_data;
    s_data.wsmanData.type = SRV_WSMAN;

    while (!s_data.terminated)
    {
        /* selector */
        {
            /* Initialize the network */
            Sock_Start();

            if(Selector_Init(&s_data.selector) != MI_RESULT_OK)
                err(ZT("Selector_Init() failed"));

            s_data.selectorInitialized = MI_TRUE;

            Timer_SetSelector(&s_data.selector);
        }

        /* Create the dispatcher object. */
        {
            r = Disp_Init(&s_data.disp, &s_data.selector);

            if (r != MI_RESULT_OK)
            {
                trace_DispatchInitFailed(r);
                err(ZT("failed to initialize the dispatcher: %u"), r);
            }
        }

        if (s_opts.idletimeout)
        {
            /* convert it to usec */
            s_data.disp.agentmgr.provmgr.idleTimeoutUsec = s_opts.idletimeout * 1000000;
        }

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
                    _RequestCallback,
                    &s_data.wsmanData,
                    &options);

                if (r != MI_RESULT_OK)
                {
                    err(ZT("WSMAN_New_Listener() failed for port %u"), s_opts.httpport[count]);
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
                    _RequestCallback,
                    &s_data.wsmanData,
                    &options);

                if (r != MI_RESULT_OK)
                {
                    err(ZT("WSMAN_New_Listener() failed for encrypted port %u"), s_opts.httpsport[count]);
                }

                /* Log start up message */
                trace_ListeningOnEncryptedPort(s_opts.httpsport[count]);
            }
        }

        /* mux */
        {
            if(MuxIn_Init(&s_data.mux, _RequestCallback, &s_data.protocolData, NULL, PostResultMsg_NewAndSerialize) != MI_RESULT_OK)
                err(ZT("MuxIn_Init() failed"));
        }
        
        /* Create new protocol object */
        {
            r = ProtocolBase_New_Listener(
                &s_data.protocol, 
                &s_data.selector, 
                OMI_GetPath(ID_SOCKETFILE), 
                MuxIn_Open,
                &s_data.mux);

            if (r != MI_RESULT_OK)
                err(ZT("Protocol_New_Listener() failed"));
        }

        /* Run the protocol object (waiting for new messages) */
        {
            const PAL_Uint64 ONE_SECOND_USEC = 1000 * 1000;
            PAL_Uint64 start;
            PAL_Uint64 finish;

            PAL_Time(&start);

            if (s_opts.livetime)
                finish = start + (s_opts.livetime * ONE_SECOND_USEC);
            else
                finish = 0;

            for (;;)
            {
                PAL_Uint64 now;
                int reload_file_exists = access(CONFIG_LOCALSTATEDIR "/omiusers/reload_dispatcher", F_OK);

                if (s_data.reloadDispFlag || 
		    reload_file_exists == 0)
                {
                    Lock_Acquire(&s_disp_mutex);
                    Disp_Reload(&s_data.disp);
                    s_data.reloadDispFlag = MI_FALSE;
                    Lock_Release(&s_disp_mutex);

		    if (reload_file_exists == 0)
		    {
			unlink(CONFIG_LOCALSTATEDIR "/omiusers/reload_dispatcher");
		    }
                }

                r = Protocol_Run(s_data.protocol, ONE_SECOND_USEC);

                if (r != MI_RESULT_TIME_OUT)
                    break;

                PAL_Time(&now);

                /* Log abnormally terminated terminated process */
                {
                    size_t i;

                    for (i = 0; i < _npids; i++)
                        trace_ChildProcessTerminatedAbnormally(_pids[i]);

                    _npids = 0;
                }

                if (finish && now > finish)
                    break;
            }
        }

        trace_Server_ProtocolRun(r);

        s_data.selectorInitialized = MI_FALSE;

        if (MI_RESULT_TIME_OUT == r)
        {
            trace_Server_LiveTimeExpired();
            s_data.terminated = MI_TRUE;
        }

#if defined(CONFIG_POSIX)
        if (r == MI_RESULT_OK)
        {
            if (s_data.terminated)
                trace_ServerTerminated();
            else
                trace_ServerReReadingConfig();
        }
#endif

        // Destroy the dispatcher.
        Selector_RemoveAllHandlers(&s_data.selector);
        Disp_Destroy(&s_data.disp);

        {
            int i;
            for (i = 0; i < s_data.wsman_size; ++i)
            {
                WSMAN_Delete(s_data.wsman[i]);
            }
        }

        ProtocolBase_Delete(s_data.protocol);
        Selector_Destroy(&s_data.selector);

        /* Shutdown the network */
        Sock_Stop();
    }

    /* Done with WSMAN* array; free it */
    PAL_Free(s_data.wsman);
    s_data.wsman_size = 0;

    /* Done with pointers to ports; free them now */
    PAL_Free(s_opts.httpport);
    PAL_Free(s_opts.httpsport);
    s_opts.httpport_size = s_opts.httpsport_size = 0;

#if defined(CONFIG_POSIX)
    /* Close PID file */
    close(pidfile);

    /* Remove PID file */
    if (PIDFile_Delete() != 0)
    {
        trace_FailedRemovePIDFile(scs(OMI_GetPath(ID_PIDFILE)));
    }
#endif

    /* Log that we are exiting */
    trace_ServerExiting();

    Log_Close();

#if defined(USE_ALLOCATOR)

# if defined(USE_PAL_ATEXIT)
    PAL_AtexitCall();
# endif

    PAL_DumpAllocStats();

    if (PAL_GetBlocksAllocated())
    {
        printf("WARNING: %s: server has unfreed blocks on exit\n", arg0);
        PAL_DumpAllocList();
    }
#endif

    return 0;
}
