/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <protocol/protocol.h>
#include <pal/sleep.h>
#include <provmgr/provmgr.h>
#include <pal/strings.h>
#include <base/log.h>
#include <base/conf.h>
#include <base/env.h>
#include <base/process.h>
#include <base/paths.h>
#include <base/omigetopt.h>
#include <base/multiplex.h>
#include <base/Strand.h>
#include <pal/format.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <pwd.h>
#include <grp.h>
#include <signal.h>

STRAND_DEBUGNAME( IdleNotification )

typedef struct _AgentData AgentData;

struct _AgentData
{
    MuxIn                   mux;
    ProtocolSocketAndBase*  protocol;
    ProvMgr                 provmgr;
    Selector                selector;
    Strand                  idleNotificationStrand;
} ;

typedef struct _Options
{
    const char* provDir;
    MI_Boolean help;
    MI_Uint32   idletimeout;
}
Options;

static AgentData  s_data;

static Options s_opts;
static const char* arg0 = 0;
static const ZChar HELP[] = ZT("\
Usage: %s [OPTIONS]\n\
\n\
This program starts the OMI agent.\n\
\n\
OPTIONS:\n\
    --version           Print version information.\n\
    --providerdir       Find providers in this directory.\n\
    --loglevel LEVEL    Set the log level (0-5).\n\
\n");

PRINTF_FORMAT(1, 2)
static void FUNCTION_NEVER_RETURNS err(const ZChar* fmt, ...)
{
    ZChar* buf = NULL;
    ZChar* buf2 = NULL;
    va_list ap;
    size_t buflen = PAL_MAX_PATH_SIZE;
    buf = (ZChar*) PAL_Malloc( sizeof(ZChar) * buflen * 2 );
    if (buf)
    {
        buf2 = buf + buflen;

        memset(&ap, 0, sizeof(ap));
        va_start(ap, fmt);
        Vstprintf(buf, buflen, fmt, ap);
        va_end(ap);
        Stprintf(buf2, buflen, ZT("%s: %T"), scs(arg0), buf);

        Ftprintf(stderr, ZT("%T\n"), buf2);
        trace_CriticalError(buf2);

        PAL_Free(buf);
    }
    exit(1);
}

void ResetLog()
{    
    char path[PAL_MAX_PATH_SIZE];
    Conf* conf;

    /* Form the configuration file path */
    Strlcpy(path, OMI_GetPath(ID_CONFIGFILE), sizeof(path));

    /* Open the configuration file */
    conf = Conf_Open(path);
    if (!conf)
    {
        trace_CriticalError(MI_T("Failed to open configuration file"));
        return;
    }

    /* For each key=value pair in configuration file */
    for (;;)
    {
        const char* key;
        const char* value;
        int r = Conf_Read(conf, &key, &value);

        if (r == -1)
        {
            trace_CriticalError(MI_T("Incorrect entry in configuration file"));
            break;
        }

        if (r == 1)
            break;

        if (strcmp(key, "loglevel") == 0)
        {
            if (Log_SetLevelFromString(value) != 0)
            {
                trace_CriticalError(MI_T("Incorrect loglevel set in configuration file"));
            }
            break;
        }
    }

    /* Close configuration file */
    Conf_Close(conf);

    return;
}

void HandleSIGUSR2(int sig)
{
    if(sig==SIGUSR2)
    {       
        ResetLog();
    }
}

/* enable core dump for current process */
static void _EnableCoreDump()
{
    struct rlimit core_limits;
    core_limits.rlim_cur = RLIM_INFINITY;
    core_limits.rlim_max = RLIM_INFINITY;
    setrlimit(RLIMIT_CORE, &core_limits);
}

void _IdleNotification_Post( _In_ Strand* self_, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // not used
}

void _IdleNotification_PostControl( _In_ Strand* self_, _In_ Message* msg)
{
    DEBUG_ASSERT( MI_FALSE );  // not used
}

void _IdleNotification_Ack( _In_ Strand* self_ )
{
    // Nothing to do
}

void _IdleNotification_Finish( _In_ Strand* self_ )
{
    // Nothing to do
}

/*
    Object that is just used to send to agent manager BinProtocolNotification

    Behavior:
    - It is created when the initial BinProtocolNotification is sent by the server
       then kept alive as long as the connection is alive.
    - Post, PostControl and Ack are not actually used
    - Shutdown:
       The objects are deleted thru the normal Strand logic once the connection is closed.

    Unique features and special Behavior:
    - If the agent is idle it will be use to post a BinProtocolNotification
       thru the many-to-one interface so there are no problem or races with
       a request being received or a response to a normal request going out
       at the same time
*/
static StrandFT _IdleNotification_FT = {
    _IdleNotification_Post,
    _IdleNotification_PostControl,
    _IdleNotification_Ack,
    NULL,
    NULL,
    _IdleNotification_Finish,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL };

/* Called by mux to dispatch an incoming request message */
static void _RequestCallback(
    _Inout_     InteractionOpenParams*    interactionParams )
{
    DEBUG_ASSERT( NULL != interactionParams );
    DEBUG_ASSERT( NULL != interactionParams->msg );
    DEBUG_ASSERT( NULL == interactionParams->callbackData );

    if (BinProtocolNotificationTag == interactionParams->msg->tag)
    {
        BinProtocolNotification* notification = (BinProtocolNotification*)interactionParams->msg;
        (void) notification; /* In case DEBUG_ASSERT is compiled out, avoid compiler warnings */

        DEBUG_ASSERT(BinNotificationAgentIdle == notification->type);

        Strand_Init( STRAND_DEBUG(IdleNotification) &s_data.idleNotificationStrand, &_IdleNotification_FT, 0, interactionParams );
    }
    else
    {
        MI_Result result;
        RequestMsg* request = (RequestMsg*)interactionParams->msg;

        DEBUG_ASSERT( Message_IsRequest(interactionParams->msg) );

        result = ProvMgr_NewRequest(
            &s_data.provmgr, &(request->regEntry), interactionParams );

        if (MI_RESULT_OK != result)
        {
            trace_Agent_ProvMgrNewRequest_Failed( result );
            Strand_FailOpenWithResult(interactionParams, result, PostResultMsg_NewAndSerialize);
        }
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

static void GetCommandLineOptions(int* argc, const char* argv[])
{
    GetOptState state = GETOPTSTATE_INITIALIZER;
    const char* opts[] =
    {
        "-h",
        "--help",
        "-v",
        "--version",
        "--providerdir:",
        "--idletimeout:",
        "--loglevel:",
        NULL,
    };

    for (;;)
    {
        int r = GetOpt(argc, argv, opts, &state);

        if (r == 1)
            break;

        if (r == -1)
            err(ZT("%s"), scs(state.err));

        /* Check for -h option */
        if (strcmp(state.opt, "-h") == 0 || strcmp(state.opt, "--help") == 0)
        {
            s_opts.help = MI_TRUE;
        }
        else if (strcmp(state.opt, "--version") == 0)
        {
            Tprintf(ZT("%s: %s\n"), scs(arg0),
                scs((const char *)(CONFIG_PRODUCT MI_T("-") CONFIG_VERSION MI_T(" - ") CONFIG_DATE)));
            exit(0);
        }
        else if (strcmp(state.opt, "--providerdir") == 0)
        {
            s_opts.provDir = state.arg;
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

            s_opts.idletimeout = (MI_Uint32)x;
        }
        else if (strcmp(state.opt, "--loglevel") == 0)
        {
            if (Log_SetLevelFromString(state.arg) != 0)
            {
                err(ZT("bad option argument for %s: %s"),
                    scs(state.opt), scs(state.arg));
            }
        }
    }
}

static void _OnCloseCallback(
    _In_        void*       object)
{
    MI_UNUSED(object);

    trace_Agent_DisconnectedFromServer();
    Selector_StopRunning(&s_data.selector);
}

static void _ProvMgrCallbackOnIdle(
    ProvMgr* mgr,
    void* callbackData)
{
    BinProtocolNotification* notification;

    MI_UNUSED(mgr);
    MI_UNUSED(callbackData);

    DEBUG_ASSERT( s_data.idleNotificationStrand.info.opened );

    trace_Agent_SendingIdleNotification();

    notification = BinProtocolNotification_New( BinNotificationAgentIdle );

    if (!notification)
    {
        // Nothing we can do here
        DEBUG_ASSERT( MI_FALSE );
        return;
    }

    // Call on the always opened idle notification strand
    Strand_SchedulePost( &s_data.idleNotificationStrand, &notification->base);

    BinProtocolNotification_Release(notification);
}

int agent_main(int argc, const char* argv[])
{
    MI_Result r;
    Sock fd;
    int logfd;
    pid_t parentPid;
    const PAL_Uint64 ONE_SECOND_USEC = 1000 * 1000;

    arg0 = argv[0];
    parentPid = getppid();

    memset(&s_data, 0, sizeof(s_data));

    /* Enable core dump */
    _EnableCoreDump();

    /* Get --destdir option first (other options may depend on it) */
    GetCommandLineDestDirOption(&argc, argv);

    /* Extract options */
    GetCommandLineOptions(&argc, argv);

    /* Print help */
    if (s_opts.help)
    {
        Ftprintf(stderr, HELP, scs(arg0));
        exit(1);
    }

    /* extract socket number */
    if (argc < 3)
    {
        trace_Agent_FDParameterIsMissing();
        exit(1);
    }

    fd = Strtol(argv[1], 0, 10);
    logfd = Strtol(argv[2], 0, 10);

    /* Attach log file */
    {
        /* Open the log file */
        if (Log_OpenFD(logfd) != MI_RESULT_OK)
        {
            err(ZT("failed to attach log file to fd: %d; errno %d"), logfd,
                (int)errno);
        }
    }

    /* Watch for SIGUSR2 signals */
    SetSignalHandler(SIGUSR2, HandleSIGUSR2);

    /* selector */
    {
        /* Initialize the network */
        Sock_Start();

        if(Selector_Init(&s_data.selector) != MI_RESULT_OK)
            err(ZT("Selector_Init() failed"));

        Timer_SetSelector(&s_data.selector);
    }

    /* mux */
    {
        if(MuxIn_Init(&s_data.mux, _RequestCallback, NULL, _OnCloseCallback, PostResultMsg_NewAndSerialize) != MI_RESULT_OK)
            err(ZT("MuxIn_Init() failed"));
    }

    /* Create new protocol object */
    {
        r = ProtocolSocketAndBase_New_Agent(
            &s_data.protocol,
            &s_data.selector,
            fd,
            MuxIn_Open,
            &s_data.mux);

        if (r != MI_RESULT_OK)
            err(ZT("ProtocolSocketAndBase_New_Agent() failed"));
    }

    /* Provider manager */
    {
        r = ProvMgr_Init(&s_data.provmgr, &s_data.selector, _ProvMgrCallbackOnIdle, &s_data, s_opts.provDir);

        if (r != MI_RESULT_OK)
            err(ZT("ProvMgr_Init() failed"));
    }

    /* idle timeout */
    if (s_opts.idletimeout)
    {
        /* convert it to usec */
        s_data.provmgr.idleTimeoutUsec = (MI_Uint64)s_opts.idletimeout * 1000000;
        trace_Agent_ChangingIdleTimeout(s_opts.idletimeout);

    }

    /* Log start up message */
    trace_Agent_Started((int)fd);

    /* Run the protocol object (waiting for new messages) */
    for (;;)
    {
        r = Protocol_Run( &s_data.protocol->internalProtocolBase, ONE_SECOND_USEC);

        if (r == MI_RESULT_OK)
        {
            break;
        }
        else if (r == MI_RESULT_TIME_OUT)
        {
            /* check if server process is still alive */
            if (getppid() != parentPid)
            {
                trace_ParentProcessTerminated(parentPid, getppid());
                break;
            }
        }
        else
        {
            err(ZT("Protocol_Run() failed (%d)"), (int)r);
        }
    }

    // Destroy all global objects
    Selector_RemoveAllHandlers(&s_data.selector);
    Selector_Destroy(&s_data.selector);
    ProvMgr_Destroy(&s_data.provmgr);
    ProtocolSocketAndBase_ReadyToFinish(s_data.protocol);

    return 0;
}
