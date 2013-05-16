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

#include <limits.h>
#include <protocol/protocol.h>
#include <base/time.h>
#include <wsman/wsman.h>
#include <provreg/provreg.h>
#include <provmgr/provmgr.h>
#include <disp/disp.h>
#include <base/strings.h>
#include <base/dir.h>
#include <base/log.h>
#include <base/env.h>
#include <base/process.h>
#include <base/pidfile.h>
#include <base/paths.h>
#include <base/conf.h>
#include <base/user.h>
#include <base/getopt.h>
#include <io/io.h>

#if defined(CONFIG_POSIX)
# include <signal.h>
# include <sys/wait.h>
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
    Disp        disp;
    Protocol*   protocol;
    WSMAN*      wsman;
    Selector    selector;
    MI_Boolean  selectorInitialized;
    MI_Boolean  terminated;

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
#endif
    /* mostly for unittesting in non-root env */
    MI_Boolean ignoreAuthentication;
    MI_Boolean locations;
    MI_Boolean logstderr;
    unsigned short httpport;
    unsigned short httpsport;
    char* sslCipherSuite;
    MI_Uint64 idletimeout;
    MI_Uint64 livetime;
    Log_Level logLevel;
}
Options;

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
    --httpport PORT             HTTP protocol listener port.\n\
    --httpsport PORT            HTTPS protocol listener port.\n\
    --idletimeout TIMEOUT       Idle providers unload timeout (in seconds).\n\
    -v, --version               Print version information.\n\
    -l, --logstderr             Send log output to standard error.\n\
    --loglevel LEVEL            Set logging level to one of the following\n\
                                symbols/numbers: fatal/0, error/1, warning/2,\n\
                                info/3, debug/4 (default 2).\n\
    --httptrace                 Enable logging of HTTP traffic.\n\
    --timestamp                 Print timestamp server was built with.\n\
\n");

static void FUNCTION_NEVER_RETURNS err(const ZChar* fmt, ...)
{
    va_list ap;
    memset(&ap, 0, sizeof(ap));

    Fzprintf(stderr, ZT("%s: "), scs(arg0));

    va_start(ap, fmt);
    Vfzprintf(stderr, fmt, ap);
    va_end(ap);

    /* Write to log as well */
    va_start(ap, fmt);
    LOGE((fmt, ap));
    va_end(ap);

    Fzprintf(stderr, ZT("\n"));
    exit(1);
}

static void _ProviderCallback(Message* msg, void* callbackData)
{
    ServerCallbackData* self = (ServerCallbackData* )callbackData;

    switch ( msg->tag )
    {
        case PostResultMsgTag:
        {
#if !defined(CONFIG_FAVORSIZE)
            const PostResultMsg* rsp = (const PostResultMsg*)msg;

            if (s_opts.trace)
            {
                PostResultMsg_Print(rsp, stdout);
            }
#endif
        }
        break;

        case PostInstanceMsgTag:
        {
#if !defined(CONFIG_FAVORSIZE)
            const PostInstanceMsg* rsp = (const PostInstanceMsg*)msg;

            if (s_opts.trace)
            {
                PostInstanceMsg_Print(rsp, stdout);
            }
#endif
        }
        break;

        case SubscribeResTag:
        {
#if !defined(CONFIG_FAVORSIZE)
            const SubscribeRes* rsp = (const SubscribeRes*)msg;

            if (s_opts.trace)
            {
                SubscribeRes_Print(rsp, stdout);
            }
#endif
        }
        break;

        case NoOpRspTag:
            break;  /* send noop confirmation to the client */

        default:
        {
            LOGF((ZT("unknown message type: %u"), msg->tag));
            exit(1);
        }
    }

    /* forward message to the other side */
    if (msg->request)
        msg->clientID = msg->request->clientID;

    switch (self->type)
    {
    case SRV_PROTOCOL:
        Protocol_Send(self->data->protocol, msg);
        break;

    case SRV_WSMAN:
        WSMAN_Send(self->data->wsman, msg);
        break;

    default:
        LOGF((ZT("unknown transport type: %u"), (int)self->type));
        exit(1);
    }
}

/* Called by protocol stack to dispatch an incoming request message */
static MI_Boolean _RequestCallback(
    Protocol* protocol_,
    Message* msg,
    void* data)
{
    ServerCallbackData* self = (ServerCallbackData*)data;
    MI_Result r;

    MI_UNUSED(protocol_);

    if (NoOpReqTag == msg->tag)
    {
        NoOpReq* req = (NoOpReq*)msg;
        NoOpRsp* rsp;

#if !defined(CONFIG_FAVORSIZE)
        if (s_opts.trace)
        {
            NoOpReq_Print(req, stdout);
        }
#endif

        /* Send NoOp response back */
        rsp = NoOpRsp_New(req->base.msgID);

        if (!rsp)
            err(ZT("out of memory"));

        rsp->base.clientID = req->base.clientID;

#if !defined(CONFIG_FAVORSIZE)
        if (s_opts.trace)
        {
            NoOpRsp_Print(rsp, stdout);
        }
#endif

        _ProviderCallback(&rsp->base, self);
        NoOpRsp_Release(rsp);

        if (s_opts.terminateByNoop)
        {
            s_data.terminated = MI_TRUE;
            Selector_StopRunning(&s_data.selector);
        }
        return MI_TRUE;
    }

#if !defined(CONFIG_FAVORSIZE)
    if (s_opts.trace)
    {
        MessagePrint(msg, stdout);
    }
#endif

    msg->callback = _ProviderCallback;
    msg->callbackData = self;

    r = Disp_HandleRequest(&self->data->disp, msg);

    if (MI_RESULT_OK != r)
    {
        PostResultMsg* resp;

        resp = PostResultMsg_New( msg->msgID );

        if (!resp)
            return MI_TRUE;

        resp->result = r;
        Message_SetRequest(&resp->base,msg);
        (*msg->callback)(&resp->base, msg->callbackData);

        PostResultMsg_Release(resp);
    }

    return MI_TRUE;
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
        "--certsdir:",
        "--rundir:",
        "--logdir:",
        "--pidfile:",
        "--logfile:",
        "--registerdir:",
        "--socketfile:",
        "--pemfile:",
        "--keyfile:",
        "--agentprogram:",
        "--serverprogram:",
        "--logstderr",
        "--loglevel:",
        "-l",
        "--testopts",
        NULL,
    };

    for (;;)
    {
        int r = GetOpt(&argc, argv, opts, &state);

        if (r == 1)
            break;

        if (r == -1)
        {
            Fzprintf(stderr, ZT("error: %s\n"), scs(state.err));
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
            Zprintf(ZT("%s: %Z\n"), scs(arg0), zcs(CONFIG_TIMESTAMP));
#else
            Zprintf(ZT("%s: %s\n"), scs(arg0), scs(CONFIG_TIMESTAMP));
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
            Zprintf(ZT("%s: %Z\n"), scs(arg0),
                zcs(CONFIG_PRODUCT ZT("-") CONFIG_VERSION ZT(" - ") CONFIG_DATE));
#else
            Zprintf(ZT("%s: %s\n"), scs(arg0),
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
#endif
        else if (strcmp(state.opt, "--httpport") == 0)
        {
            unsigned long x;
            char* end = NULL;

            x = Strtoul(state.arg, &end, 10);

            if (*end != '\0' || x > USHRT_MAX)
            {
                err(ZT("bad option argument for --httpport: %s"),
                    scs(state.arg));
            }

            s_opts.httpport = (unsigned short)x;
        }
        else if (strcmp(state.opt, "--httpsport") == 0)
        {
            unsigned long x;
            char* end;

            x = Strtoul(state.arg, &end, 10);

            if (*end != '\0' || x > USHRT_MAX)
            {
                err(ZT("bad option argument for --httpsport: %s"),
                    scs(state.arg));
            }

            s_opts.httpsport = (unsigned short)x;
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
        ZChar path[MAX_PATH_SIZE];
        ZStrlcpy(path, GetPath(ID_LOGFILE), MI_COUNT(path));

        /* Open the log file */
        if (Log_Open(path) != MI_RESULT_OK)
            err(ZT("failed to open log file: %Z"), zcs(path));
    }
}

#if defined(CONFIG_POSIX)
static void _HandleSIGTERM(int sig)
{
    if (sig == SIGTERM && s_data.selectorInitialized)
    {
        s_data.terminated = MI_TRUE;
        Selector_StopRunning(&s_data.selector);
    }
}

static void _HandleSIGHUP(int sig)
{
    if (sig == SIGHUP && s_data.selectorInitialized)
    {
        Selector_StopRunning(&s_data.selector);
    }
}

static void _HandleSIGCHLD(int sig)
{
    if (sig == SIGCHLD)
    {
        int status = 0;
        wait(&status);
    }
}
#endif

static void _PrintPaths()
{
    PrintPaths();
}

static void GetConfigFileOptions()
{
    char path[MAX_PATH_SIZE];
    Conf* conf;

    /* Form the configuration file path */
    Strlcpy(path, GetPath(ID_CONFIGFILE), sizeof(path));

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
            char* end;
            unsigned long x = Strtoul(value, &end, 10);

            if (*end != '\0' || x > USHRT_MAX)
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path),
                    Conf_Line(conf), scs(key), scs(value));
            }

            s_opts.httpport = (unsigned short)x;
        }
        else if (strcmp(key, "httpsport") == 0)
        {
            char* end;
            unsigned long x = Strtoul(value, &end, 10);

            if (*end != '\0' || x > USHRT_MAX)
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path),
                    Conf_Line(conf), scs(key), scs(value));
            }

            s_opts.httpsport = (unsigned short)x;
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
        else if (strcmp(key, "sslciphersuite") == 0)
        {
            size_t valueLength = strlen(value);
            s_opts.sslCipherSuite = malloc(valueLength + 1);
            strncpy(s_opts.sslCipherSuite, value, valueLength);
            s_opts.sslCipherSuite[valueLength] = '\0';
        }
        else if (IsNickname(key))
        {
            if (SetPathFromNickname(key, value) != 0)
                err(ZT("SetPathFromNickname() failed"));
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
    s_opts.httpport = CONFIG_HTTPPORT;
    s_opts.httpsport = CONFIG_HTTPSPORT;
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
        Fzprintf(stderr, HELP, scs(arg0));
        exit(1);
    }

    /* Print locations of files and directories */
    if (s_opts.locations)
    {
        _PrintPaths();
        Zprintf(ZT("\n"));
        exit(0);
    }

#if defined(CONFIG_POSIX)
    if (s_opts.stop || s_opts.reloadConfig)
    {
        if (PIDFile_IsRunning() != 0)
            err(ZT("server is not running\n"));

        if (PIDFile_Signal(s_opts.stop ? SIGTERM : SIGHUP) != 0)
            err(ZT("failed to stop server\n"));

        if (s_opts.stop)
            Zprintf(ZT("%s: stopped server\n"), scs(arg0));
        else
            Zprintf(ZT("%s: refreshed server\n"), scs(arg0));

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
        0 != SetSignalHandler(SIGHUP, _HandleSIGHUP))
        err(ZT("cannot set sighanlder, erron %d"), errno);


    /* Watch for SIGCHLD signals */
    SetSignalHandler(SIGCHLD, _HandleSIGCHLD);

#endif

    /* Change directory to 'rundir' */
    if (Chdir(GetPath(ID_RUNDIR)) != 0)
    {
        err(ZT("failed to change directory to: %s"),
            scs(GetPath(ID_RUNDIR)));
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
        LOGF((ZT("failed to create PID file: %s"), scs(GetPath(ID_PIDFILE))));
        exit(1);
    }

#endif

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
        }

        /* Create the dispatcher object. */
        {
            r = Disp_Init(&s_data.disp, &s_data.selector);

            if (r != MI_RESULT_OK)
            {
                LOGF((ZT("failed to initialize the dispatcher: %u"), r));
                err(ZT("failed to initialize the dispatcher: %u"), r);
            }
        }

        if (s_opts.idletimeout)
        {
            /* convert it to usec */
            s_data.disp.agentmgr.provmgr.idleTimeoutUsec = s_opts.idletimeout * 1000000;
        }

        /* wsman server */
        if (s_opts.httpport != 0 || s_opts.httpsport != 0)
        {
            r = WSMAN_New_Listener(
                &s_data.wsman,
                &s_data.selector,
                s_opts.httpport,
                s_opts.httpsport,
                s_opts.sslCipherSuite,
                (WSMANCallback)_RequestCallback, /* ATTN! address callback types! */
                &s_data.wsmanData);

            if (r != MI_RESULT_OK)
                err(ZT("WSMAN_New_Listener() failed"));
        }

        /* Set WSMAN options */
        {
            WSMAN_Options options = DEFAULT_WSMAN_OPTIONS;
#if !defined(CONFIG_FAVORSIZE)
            options.enableTracing = s_opts.trace;
#endif
            options.enableHTTPTracing = s_opts.httptrace;
            WSMAN_SetOptions(s_data.wsman, &options);
        }

        /* Create new protocol object */
        {
            r = Protocol_New_Listener(&s_data.protocol, &s_data.selector,
                GetPath(ID_SOCKETFILE), _RequestCallback, &s_data.protocolData);

            if (r != MI_RESULT_OK)
                err(ZT("Protocol_New_Listener() failed"));
        }

        /* Log start up message */
        LOGI((ZT("listening on ports: http %u, https %u"), s_opts.httpport, s_opts.httpsport));

        /* Run the protocol object (waiting for new messages) */
        r = Protocol_Run(s_data.protocol,
            (s_opts.livetime ? s_opts.livetime * 1000000 : TIME_NEVER));

        LOGI((ZT("after run, r %d"), r));

        s_data.selectorInitialized = MI_FALSE;

        if (MI_RESULT_TIME_OUT == r)
        {
            LOGI((ZT("livetime expired; server stopped")));
            s_data.terminated = MI_TRUE;
        }

#if defined(CONFIG_POSIX)
        if (r == MI_RESULT_OK)
        {
            if (s_data.terminated)
                LOGI((ZT("server terminated")));
            else
                LOGI((ZT("re-reading configuration")));
        }
#endif

        // Destroy the dispatcher.
        Selector_RemoveAllHandlers(&s_data.selector);
        Disp_Destroy(&s_data.disp);
        WSMAN_Delete(s_data.wsman);
        Protocol_Delete(s_data.protocol);
        Selector_Destroy(&s_data.selector);

        /* Shutdown the network */
        Sock_Stop();
    }

#if defined(CONFIG_POSIX)
    /* Close PID file */
    close(pidfile);

    /* Remove PID file */
    if (PIDFile_Delete() != 0)
    {
        LOGW((ZT("failed to remove PID file: %s"), scs(GetPath(ID_PIDFILE))));
    }
#endif

    /* Log that we are exiting */
    LOGI((ZT("server exiting")));

    Log_Close();
    return 0;
}
