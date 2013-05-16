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

#include <protocol/protocol.h>
#include <base/time.h>
#include <provmgr/provmgr.h>
#include <base/strings.h>
#include <base/log.h>
#include <base/env.h>
#include <base/paths.h>
#include <base/getopt.h>
#include <io/io.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

typedef struct _AgentData AgentData;

struct _AgentData
{
    Protocol*   protocol;
    ProvMgr     provmgr;
    Selector    selector;
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
    --loglevel LEVEL    Set the log level (0-4).\n\
\n");

PRINTF_FORMAT(1, 2)
static void FUNCTION_NEVER_RETURNS err(const ZChar* fmt, ...)
{
    va_list ap;
    memset(&ap, 0, sizeof(ap));

    Fzprintf(stderr, ZT("%s: "), arg0);

    va_start(ap, fmt);
    Vfzprintf(stderr, fmt, ap);
    va_end(ap);

    Fzprintf(stderr, ZT("\n"));

    exit(1);
}

static void _ProviderCallback(Message* msg, void* callbackData)
{

    /* forward message to the other side */
    /*if (msg->request)
        msg->clientID = msg->request->clientID;*/

    Protocol_Send(s_data.protocol, msg);
}

/* Called by protocol stack to dispatch an incoming request message */
static MI_Boolean _RequestCallback(
    Protocol* protocol_,
    Message* msg,
    void* data)
{
    //ServerCallbackData* self = (ServerCallbackData*)data;
    MI_Result r;

    MI_UNUSED(protocol_);

    msg->callback = _ProviderCallback;
    //msg->callbackData = self;

    r = ProvMgr_PostMessage(&s_data.provmgr, msg->libraryName, msg);
    
    if (MI_RESULT_OK != r)
    {
        PostResultMsg* resp;

        resp = PostResultMsg_New( msg->msgID );

        if (!resp)
            return MI_FALSE;

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
            Zprintf(ZT("%s: %s\n"), scs(arg0),
                scs(CONFIG_PRODUCT "-" CONFIG_VERSION " - " CONFIG_DATE));
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

            s_opts.idletimeout = x;
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

static void _EventCallback(
    Protocol* protocol,
    ProtocolEvent event,
    void* data)
{
    MI_UNUSED(protocol);
    MI_UNUSED(event);
    MI_UNUSED(data);

    LOGI((ZT("disconnected from server; exiting")));
    Selector_RemoveAllHandlers(&s_data.selector);
    Protocol_Delete(s_data.protocol);
//  Selector_Destroy(&s_data.selector);           // this hangs, so let exit clean it up
    (void)ProvMgr_Destroy(&s_data.provmgr);

    exit(0);
}

static void _ProvMgrCallbackOnIdle(
    ProvMgr* mgr,
    void* callbackData)
{
    BinProtocolNotification* notification;

    MI_UNUSED(mgr);
    MI_UNUSED(callbackData);

    LOGI((ZT("sending 'agent-idle' notification to the server")));

    notification = BinProtocolNotification_New( BinNotificationAgentIdle );

    if (!notification)
        return;

    Protocol_Send(s_data.protocol, &notification->base);

    BinProtocolNotification_Release(notification);
}

int agent_main(int argc, const char* argv[])
{
    MI_Result r;
    Sock fd;
    int logfd;

    arg0 = argv[0];

    memset(&s_data, 0, sizeof(s_data));

    /* Get --destdir option first (other options may depend on it) */
    GetCommandLineDestDirOption(&argc, argv);

    /* Extract options */
    GetCommandLineOptions(&argc, argv);

    /* Print help */
    if (s_opts.help)
    {
        Fzprintf(stderr, HELP, scs(arg0));
        exit(1);
    }

    /* extract socket number */
    if (argc < 3)
    {
        LOGE((ZT("parameter is missing (fd)")));
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

    /* selector */
    {
        /* Initialize the network */
        Sock_Start();

        if (Selector_Init(&s_data.selector) != MI_RESULT_OK)
            err(ZT("Selector_Init() failed"));
    }

    /* Create new protocol object */
    {
        r = Protocol_New_From_Socket(
            &s_data.protocol,
            &s_data.selector,
            fd,
            MI_FALSE,
            _RequestCallback,
            0,
            _EventCallback,
            0);

        if (r != MI_RESULT_OK)
            err(ZT("Protocol_New_Listener() failed"));
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
        s_data.provmgr.idleTimeoutUsec = s_opts.idletimeout * 1000000;
        LOGI((ZT("changing idle timeout to %d sec"), (int)s_opts.idletimeout));

    }

    /* Log start up message */
    LOGI((ZT("agent started; fd %d"), (int)fd));

    /* Run the protocol object (waiting for new messages) */
    r = Protocol_Run(s_data.protocol, TIME_NEVER);

    if (r != MI_RESULT_OK)
        err(ZT("Protocol_Run() failed (%d)"), (int)r);

    // Destroy all global objects
    Selector_RemoveAllHandlers(&s_data.selector);
    Protocol_Delete(s_data.protocol);
    Selector_Destroy(&s_data.selector);

    return 0;
}
