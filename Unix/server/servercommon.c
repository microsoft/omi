/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/
#include <base/user.h>
#include <sock/selector.h>
#include <server/server.h>

static Options *s_optsPtr = NULL;
static ServerData *s_dataPtr = NULL;
static ServerType serverType = OMI_SERVER;
static const char* arg0 = 0;

static Lock s_disp_mutex = LOCK_INITIALIZER;

void PrintProviderMsg(_In_ Message* msg)
{
#if !defined(CONFIG_FAVORSIZE)
    if (s_optsPtr->trace)
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

void GetCommandLineDestDirOption(
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
int _ParseHttpPortSpecification(unsigned short **ports, int *size, const char *spec, unsigned short defport)
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

int VerifyServiceAccount()
{
    if (s_optsPtr->serviceAccount == NULL)
    {
        err(ZT("No service account provided"));
    }

    if (LookupUser(s_optsPtr->serviceAccount, &s_optsPtr->serviceAccountUID, &s_optsPtr->serviceAccountGID) != 0)
    {
        err(ZT("invalid service account:  %T"), s_optsPtr->serviceAccount);
    }

    if ( s_optsPtr->serviceAccountUID == 0)
    {
        err(ZT("service account cannot be root"));
    }

    return 0;
}


void GetCommandLineOptions(
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
        "--nonroot",
        "--service:",
        "--socketpair:",
        "--logfilefd:",
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
            s_optsPtr->help = MI_TRUE;
        }
        else if (strcmp(state.opt, "-p") == 0)
        {
            s_optsPtr->locations = MI_TRUE;
        }
#if !defined(CONFIG_FAVORSIZE)
        else if (strcmp(state.opt, "-t") == 0)
        {
            s_optsPtr->trace = MI_TRUE;
        }
#endif
        else if (strcmp(state.opt, "--httptrace") == 0)
        {
            s_optsPtr->httptrace = MI_TRUE;
        }
        else if (strcmp(state.opt, "--timestamp") == 0)
        {
            Tprintf(ZT("%s: %s\n"), scs(arg0), scs(CONFIG_TIMESTAMP));
            exit(0);
        }
        else if (strcmp(state.opt, "--stopnoop") == 0)
        {
            s_optsPtr->terminateByNoop = MI_TRUE;
        }
        else if (strcmp(state.opt, "-v") == 0 ||
                strcmp(state.opt, "--version") == 0)
        {
            Tprintf(ZT("%s: %s"), scs(arg0),
                scs(CONFIG_PRODUCT "-" CONFIG_VERSION " - " CONFIG_DATE));
#if defined(CONFIG_ENABLE_DEBUG)
            Tprintf(ZT(" DEBUG\n"));
#else
            Tprintf(ZT("\n"));
#endif
            exit(0);
        }
#if defined(CONFIG_POSIX)
        else if (strcmp(state.opt, "-d") == 0)
        {
            s_optsPtr->daemonize = MI_TRUE;
        }
        else if (strcmp(state.opt, "-s") == 0)
        {
            s_optsPtr->stop = MI_TRUE;
        }
        else if (strcmp(state.opt, "-r") == 0)
        {
            s_optsPtr->reloadConfig = MI_TRUE;
        }
        else if (strcmp(state.opt, "--reload-dispatcher") == 0)
        {
            s_optsPtr->reloadDispatcher = MI_TRUE;
        }
#endif
        else if (strcmp(state.opt, "--httpport") == 0)
        {
            if ( _ParseHttpPortSpecification(&s_optsPtr->httpport, &s_optsPtr->httpport_size, state.arg, CONFIG_HTTPPORT) )
            {
                err(ZT("bad option argument for --httpport: %s"), scs(state.arg));
            }
        }
        else if (strcmp(state.opt, "--httpsport") == 0)
        {
            if ( _ParseHttpPortSpecification(&s_optsPtr->httpsport, &s_optsPtr->httpsport_size, state.arg, CONFIG_HTTPSPORT) )
            {
                err(ZT("bad option argument for --httpsport: %s"), scs(state.arg));
            }
        }
        else if (strcmp(state.opt, "--idletimeout") == 0)
        {
            char* end;
            MI_Uint64 x = Strtoull(state.arg, &end, 10);

            if (*end != '\0')
            {
                err(ZT("bad option argument for --idletimeout: %s"), scs(state.arg));
            }

            s_optsPtr->idletimeout = x;
        }
        else if (strcmp(state.opt, "--livetime") == 0)
        {
            char* end;
            MI_Uint64 x = Strtoull(state.arg, &end, 10);

            if (*end != '\0')
            {
                err(ZT("bad option argument for --livetime: %s"), scs(state.arg));
            }

            s_optsPtr->livetime = x;
        }
        else if (strcmp(state.opt, "--ignoreAuthentication") == 0 ||
             strcmp(state.opt, "-i") == 0)
        {
            s_optsPtr->ignoreAuthentication = MI_TRUE;
        }
        else if (strcmp(state.opt, "--logstderr") == 0 ||
             strcmp(state.opt, "-l") == 0)
        {
            s_optsPtr->logstderr = MI_TRUE;
        }
        else if (strcmp(state.opt, "--loglevel") == 0)
        {
            if (Log_SetLevelFromString(state.arg) != 0)
            {
                err(ZT("bad option argument for %s: %s"), scs(state.opt), scs(state.arg));
            }
        }
        else if (strcmp(state.opt, "--service") == 0)
        {
            if (s_optsPtr->serviceAccount)
            {
                PAL_Free((void*)s_optsPtr->serviceAccount);
            }
            s_optsPtr->serviceAccount = PAL_Strdup(state.arg);
        }
        else if (strcmp(state.opt, "--nonroot") == 0)
        {
            s_optsPtr->nonRoot = MI_TRUE;
        }
        else if (strcmp(state.opt, "--socketpair") == 0)
        {
            char *end = NULL;
            long port = Strtol(state.arg, &end, 10);
            if (port == LONG_MIN || port == LONG_MAX)
            {
                err(ZT("bad option argument for %s: %s"), scs(state.opt), scs(state.arg));
            }
            s_optsPtr->socketpairPort = port;

        }
        else if (strcmp(state.opt, "--logfilefd") == 0)
        {
            char *end = NULL;
            long filefd = Strtol(state.arg, &end, 10);
            if (filefd == LONG_MIN || filefd == LONG_MAX)
            {
                err(ZT("bad option argument for %s: %s"), scs(state.opt), scs(state.arg));
            }
            Log_OpenFD((int) filefd);
        }
        else if (strcmp(state.opt, "--testopts") == 0)
        {
            s_optsPtr->httptrace = MI_TRUE;

            if (Log_SetLevelFromString("DEBUG") != 0)
            {
                err(ZT("bad argument for Log_SetLevelFromString()"));
            }
        }
        else if (strncmp(state.opt, "--", 2) == 0 && IsNickname(state.opt+2))
        {
            if (SetPathFromNickname(state.opt+2, state.arg) != 0)
            {
                err(ZT("SetPathFromNickname() failed"));
            }
        }
    }

    *argc_ = argc;
}

void OpenLogFile()
{
    if (s_optsPtr->logstderr)
    {
        if (Log_OpenStdErr() != MI_RESULT_OK)
        {
            err(ZT("failed to open log file to stderr"));
        }
    }
    else
    {
        TChar path[PAL_MAX_PATH_SIZE] = { 0 };
        TcsStrlcpy(path, OMI_GetPath(ID_LOGFILE), MI_COUNT(path));

        /* Open the log file */
        if (Log_Open(path) != MI_RESULT_OK)
        {
            err(PAL_T("failed to open log file: %T, %d"), tcs(path), errno);
        }
    }
}

#if defined(CONFIG_POSIX)

void HandleSIGTERM(int sig)
{
    if (sig == SIGTERM)
    {
        if (s_dataPtr->enginePid > 0)
        {
            int status;

            kill(s_dataPtr->enginePid, SIGTERM);
            waitpid(s_dataPtr->enginePid, &status, 0);
        }

        if (s_dataPtr->selectorInitialized)
        {
            const char* socketFile = OMI_GetPath(ID_SOCKETFILE);
            s_dataPtr->terminated = MI_TRUE;
            Selector_StopRunning(&s_dataPtr->selector);
            if (socketFile != NULL && *socketFile != '\0')
                unlink(socketFile);
        }
    }
}

void HandleSIGHUP(int sig)
{
    if (sig == SIGHUP)
    { 
        if (s_dataPtr->enginePid > 0)
        {
            kill(s_dataPtr->enginePid, SIGHUP);
        }
        else if(s_dataPtr->selectorInitialized)
        {
            Selector_StopRunning(&s_dataPtr->selector);
        }
    }
}

// We reload the ProvReg structure in the Dispatcher when this signal is received.
// This gives us access to providers that are installed after the omiserver is running without terminating current providers that are running.
void HandleSIGUSR1(int sig)
{
    if (sig == SIGUSR1)
    {
        s_dataPtr->reloadDispFlag = MI_TRUE;
    }
}

/* An array of PIDS that abnormally exited */
#define NPIDS 16
static pid_t _pids[NPIDS];
static volatile size_t _npids;

void HandleSIGCHLD(int sig)
{
    if (sig == SIGCHLD)
    {
        for (;;)
        {
            int status = 0;
            pid_t pid = waitpid(-1, &status, WNOHANG);

            /* If engine die for whatever reason, shut down server */
            if (serverType == OMI_SERVER && pid == s_dataPtr->enginePid)
            {
                trace_EngineProcessTerminated();
                exit(1);
            }

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

void GetConfigFileOptions()
{
    char path[PAL_MAX_PATH_SIZE];
    Conf* conf;

    /* Form the configuration file path */
    Strlcpy(path, OMI_GetPath(ID_CONFIGFILE), sizeof(path));

    /* Open the configuration file */
    conf = Conf_Open(path);
    if (!conf)
    {
        err(ZT("failed to open configuration file: %s"), scs(path));
    }

    /* For each key=value pair in configuration file */
    for (;;)
    {
        const char* key;
        const char* value;
        int r = Conf_Read(conf, &key, &value);

        if (r == -1)
        {
            err(ZT("%s: %s\n"), path, scs(Conf_Error(conf)));
        }

        if (r == 1)
            break;

        if (strcmp(key, "httpport") == 0)
        {
            if ( _ParseHttpPortSpecification(&s_optsPtr->httpport, &s_optsPtr->httpport_size, value, CONFIG_HTTPPORT) )
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "httpsport") == 0)
        {
            if ( _ParseHttpPortSpecification(&s_optsPtr->httpsport, &s_optsPtr->httpsport_size, value, CONFIG_HTTPSPORT) )
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "idletimeout") == 0)
        {
            char* end;
            MI_Uint64 x = Strtoull(value, &end, 10);

            if (*end != '\0')
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), Conf_Line(conf), scs(key), scs(value));
            }

            s_optsPtr->idletimeout = x;
        }
        else if (strcmp(key, "livetime") == 0)
        {
            char* end;
            MI_Uint64 x = Strtoull(value, &end, 10);

            if (*end != '\0')
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), Conf_Line(conf), scs(key), scs(value));
            }

            s_optsPtr->livetime = x;
        }
        else if (strcmp(key, "trace") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
#if !defined(CONFIG_FAVORSIZE)
                s_optsPtr->trace = MI_TRUE;
#endif
            }
            else if (Strcasecmp(value, "false") == 0)
            {
#if !defined(CONFIG_FAVORSIZE)
                s_optsPtr->trace = MI_FALSE;
#endif
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "httptrace") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                s_optsPtr->httptrace = MI_TRUE;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                s_optsPtr->httptrace = MI_FALSE;
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "loglevel") == 0)
        {
            if (Log_SetLevelFromString(value) != 0)
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "sslciphersuite") == 0)
        {
            size_t valueLength = strlen(value);
            s_optsPtr->sslCipherSuite = PAL_Malloc(valueLength + 1);
            if (s_optsPtr->sslCipherSuite == NULL)
            {
                err(ZT("Out of memory"));
            }
            Strlcpy(s_optsPtr->sslCipherSuite, value, valueLength+1);
            s_optsPtr->sslCipherSuite[valueLength] = '\0';
        }
        else if (strcmp(key, "NoSSLv2") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                s_optsPtr->sslOptions |= DISABLE_SSL_V2;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                s_optsPtr->sslOptions &= ~DISABLE_SSL_V2;
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "NoSSLv3") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                s_optsPtr->sslOptions |= DISABLE_SSL_V3;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                s_optsPtr->sslOptions &= ~DISABLE_SSL_V3;
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "NoTLSv1_0") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                s_optsPtr->sslOptions |= DISABLE_TSL_V1_0;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                s_optsPtr->sslOptions &= ~DISABLE_TSL_V1_0;
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "NoTLSv1_1") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                s_optsPtr->sslOptions |= DISABLE_TSL_V1_1;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                s_optsPtr->sslOptions &= ~DISABLE_TSL_V1_1;
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "NoTLSv1_2") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                s_optsPtr->sslOptions |= DISABLE_TSL_V1_2;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                s_optsPtr->sslOptions &= ~DISABLE_TSL_V1_2;
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcmp(key, "NoSSLCompression") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                s_optsPtr->sslOptions |= DISABLE_SSL_COMPRESSION;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                s_optsPtr->sslOptions &= ~DISABLE_SSL_COMPRESSION;
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (IsNickname(key))
        {
            if (SetPathFromNickname(key, value) != 0)
            {
                err(ZT("SetPathFromNickname() failed"));
            }
        }
        else if (strcasecmp(key, "NtlmCredsFile") == 0)
        {
            if (value)
            {
                s_optsPtr->ntlmCredFile = PAL_Strdup(value);
            }
        }
        else if (strcasecmp(key, "Krb5CredCache") == 0)
        {
            if (value)
            {
                s_optsPtr->krb5CredCacheSpec = PAL_Strdup(value);
            }
        }
        else if (strcasecmp(key, "nonroot") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                s_optsPtr->nonRoot = MI_TRUE;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                s_optsPtr->nonRoot = MI_FALSE;
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path), Conf_Line(conf), scs(key), scs(value));
            }
        }
        else if (strcasecmp(key, "service") == 0)
        {
            if (value)
            {
                if (s_optsPtr->serviceAccount)
                {
                    PAL_Free((void*)s_optsPtr->serviceAccount);
                }
                s_optsPtr->serviceAccount = PAL_Strdup(value);
            }
        }
        else
        {
            err(ZT("%s(%u): unknown key: %s"), scs(path), Conf_Line(conf), scs(key));
        }
    }

    /* Close configuration file */
    Conf_Close(conf);

    return;
}

void SetDefaults(Options *opts_ptr, ServerData *data_ptr, const char *executable, ServerType type)
{
    s_optsPtr = opts_ptr;
    s_dataPtr = data_ptr;
    arg0 = executable;
    serverType = type;

    memset(s_dataPtr, 0, sizeof(ServerData));

    s_optsPtr->httpport = PAL_Malloc(sizeof(unsigned short));
    s_optsPtr->httpport[0] = CONFIG_HTTPPORT;
    s_optsPtr->httpport_size = 1;

    s_optsPtr->httpsport = PAL_Malloc(sizeof(unsigned short));
    s_optsPtr->httpsport[0] = CONFIG_HTTPSPORT;
    s_optsPtr->httpsport_size = 1;

    s_optsPtr->sslOptions = DISABLE_SSL_V2;
    s_optsPtr->idletimeout = 0;
    s_optsPtr->livetime = 0;
    s_optsPtr->nonRoot = MI_TRUE;

    s_optsPtr->serviceAccount = PAL_Strdup("omi");
    s_optsPtr->serviceAccountUID = -1;
    s_optsPtr->serviceAccountGID = -1;
    s_optsPtr->socketpairPort = (Sock)-1;

    s_optsPtr->ntlmCredFile      = NULL;
    s_optsPtr->krb5KeytabPath    = PAL_Strdup(OMI_GetPath(ID_KRB5_KEYTABPATH));
    s_optsPtr->krb5CredCacheSpec = PAL_Strdup("FILE:/tmp/omi_cc");

    /* Initialize calback parameters */
    s_dataPtr->protocolData.data = s_dataPtr;
    s_dataPtr->protocolData.type = SRV_PROTOCOL;
    s_dataPtr->wsmanData.data = s_dataPtr;
    s_dataPtr->wsmanData.type = SRV_WSMAN;

    s_dataPtr->protocol0 = NULL;
    s_dataPtr->protocol1 = NULL;
    
    s_dataPtr->enginePid = 0;
    s_dataPtr->parentPid = getppid();

    s_dataPtr->internalSock = INVALID_SOCK;
}

STRAND_DEBUGNAME( NoopRequest )

static void _ProcessNoopRequest(_Inout_ InteractionOpenParams*  params)
{
    Strand* strand;
    NoOpReq* req = (NoOpReq*)params->msg;
    NoOpRsp* rsp;

#if !defined(CONFIG_FAVORSIZE)
    if (s_optsPtr->trace)
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
    if (s_optsPtr->trace)
    {
        NoOpRsp_Print(rsp, stdout);
    }
#endif

    Strand_Ack( strand );   // Ack open msg
    Strand_Post( strand, &rsp->base );
    Strand_Close( strand );   
    Strand_Leave( strand);
    
    NoOpRsp_Release(rsp);

    trace_ServerReceivedNoOpReqTag( (int)s_optsPtr->terminateByNoop );
    
    if (s_optsPtr->terminateByNoop)
    {
        s_dataPtr->terminated = MI_TRUE;
        Selector_StopRunning(&s_dataPtr->selector);
    }
}

/* Called by protocol stack to dispatch an incoming request message */
void RequestCallback(
    _Inout_ InteractionOpenParams* interactionParams)
{
    ServerCallbackData* self = (ServerCallbackData*)interactionParams->callbackData;
    Message* msg = interactionParams->msg;
    MI_Result result = MI_RESULT_OK;

    DEBUG_ASSERT( NULL != interactionParams );
    DEBUG_ASSERT( NULL != msg );
    
    if (NoOpReqTag == msg->tag)
    {
        _ProcessNoopRequest(interactionParams);
        return;
    }

#if !defined(CONFIG_FAVORSIZE)
    if (s_optsPtr->trace)
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
 
void FUNCTION_NEVER_RETURNS err(const ZChar* fmt, ...)
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

void FUNCTION_NEVER_RETURNS info_exit(const ZChar* fmt, ...)
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

MI_Result InitializeNetwork()
{
    MI_Result r = MI_RESULT_OK;

    /* selector */
    {
        /* Initialize the network */
        Sock_Start();

        if(Selector_Init(&s_dataPtr->selector) != MI_RESULT_OK)
        {
            err(ZT("Selector_Init() failed"));
        }

        s_dataPtr->selectorInitialized = MI_TRUE;

        Timer_SetSelector(&s_dataPtr->selector);
    }

    /* Create the dispatcher object. */
    {
        r = Disp_Init(&s_dataPtr->disp, &s_dataPtr->selector);

        if (r != MI_RESULT_OK)
        {
            trace_DispatchInitFailed(r);
            err(ZT("failed to initialize the dispatcher: %u"), r);
        }
    }

    if (s_optsPtr->idletimeout)
    {
        /* convert it to usec */
        s_dataPtr->disp.agentmgr.provmgr.idleTimeoutUsec = s_optsPtr->idletimeout * 1000000;
    }

    return r;
}

MI_Result WsmanProtocolListen()
{
    MI_Result r = MI_RESULT_OK;

    /* Set WSMAN options and create WSMAN server */
    s_dataPtr->wsman_size = s_optsPtr->httpport_size + s_optsPtr->httpsport_size;
    if ( s_dataPtr->wsman_size > 0 )
    {
        s_dataPtr->wsman = PAL_Calloc(s_dataPtr->wsman_size, sizeof(WSMAN*));
        if ( s_dataPtr->wsman == NULL )
        {
            err(ZT("memory allocation failure allocating %d bytes"), s_dataPtr->wsman_size * sizeof(WSMAN*));
        }
    }

    {
        int wsman_count = 0;
        WSMAN_Options options = DEFAULT_WSMAN_OPTIONS;
#if !defined(CONFIG_FAVORSIZE)
        options.enableTracing = s_optsPtr->trace;
#endif
        options.enableHTTPTracing = s_optsPtr->httptrace;

        /* Start up the non-encrypted listeners */
        int count;
        for ( count = 0; count < s_optsPtr->httpport_size; ++count )
        {
            r = WSMAN_New_Listener(
                &s_dataPtr->wsman[wsman_count++],
                &s_dataPtr->selector, 
                s_optsPtr->httpport[count],
                0,
                s_optsPtr->sslCipherSuite,
                s_optsPtr->sslOptions,
                RequestCallback,
                &s_dataPtr->wsmanData,
                &options);

            if (r != MI_RESULT_OK)
            {
                err(ZT("WSMAN_New_Listener() failed for port %u. Err = %d"), s_optsPtr->httpport[count], r);
            }

            /* Log start up message */
            trace_ListeningOnPort(s_optsPtr->httpport[count]);
        }

        /* Start up the encrypted listeners */
        for ( count = 0; count < s_optsPtr->httpsport_size; ++count )
        {
            r = WSMAN_New_Listener(
                &s_dataPtr->wsman[wsman_count++],
                &s_dataPtr->selector, 
                0,
                s_optsPtr->httpsport[count],
                s_optsPtr->sslCipherSuite,
                s_optsPtr->sslOptions,
                RequestCallback,
                &s_dataPtr->wsmanData,
                &options);

            if (r != MI_RESULT_OK)
            {
                err(ZT("WSMAN_New_Listener() failed for encrypted port %u. Err = %d"), s_optsPtr->httpsport[count], r);
            }

            /* Log start up message */
            trace_ListeningOnEncryptedPort(s_optsPtr->httpsport[count]);
        }
    }

    return r;
}

MI_Result BinaryProtocolListenFile(
    const char *socketFile, 
    MuxIn *mux, 
    ProtocolBase **protocol,
    const char *expectedSecretString)
{
    MI_Result r = MI_RESULT_OK;

    /* mux */
    {
        if(MuxIn_Init(mux, RequestCallback, &s_dataPtr->protocolData, NULL, PostResultMsg_NewAndSerialize) != MI_RESULT_OK)
        {
            err(ZT("MuxIn_Init() failed"));
        }
    }
        
    /* Create new protocol object */
    {
        r = ProtocolBase_New_Listener(
            protocol, 
            &s_dataPtr->selector, 
            socketFile,
            MuxIn_Open,
            mux);

        if (r != MI_RESULT_OK)
        {
            err(ZT("Protocol_New_Listener() failed: %T"), socketFile);
        }

        (*protocol)->forwardRequests = (serverType == OMI_ENGINE) ? MI_TRUE : MI_FALSE;

        if (serverType == OMI_SERVER && s_optsPtr->nonRoot)
        {
            (*protocol)->socketFile = NULL;
            (*protocol)->expectedSecretString = expectedSecretString;
        }
        else
        {
            (*protocol)->socketFile = NULL;
            (*protocol)->expectedSecretString = NULL;
        }
    }

    return r;
}

MI_Result BinaryProtocolListenSock(
    Sock sock, 
    MuxIn *mux, 
    ProtocolSocketAndBase **protocol, 
    const char *socketFile, 
    const char *expectedSecretString)
{
    MI_Result r = MI_RESULT_OK;

    /* mux */
    {
        if(MuxIn_Init(mux, RequestCallback, &s_dataPtr->protocolData, NULL, PostResultMsg_NewAndSerialize) != MI_RESULT_OK)
        {
            err(ZT("MuxIn_Init() failed"));
        }
    }
        
    /* Create new protocol object */
    {
        r = ProtocolSocketAndBase_New_Agent(
            protocol, 
            &s_dataPtr->selector, 
            sock,
            MuxIn_Open,
            mux);

        if (r != MI_RESULT_OK)
        {
            err(ZT("Protocol_New_Listener() failed."));
        }

        (*protocol)->protocolSocket.clientAuthState = PRT_AUTH_WAIT_CONNECTION_REQUEST;
        (*protocol)->internalProtocolBase.forwardRequests = (serverType == OMI_ENGINE) ? MI_TRUE : MI_FALSE;

        if (serverType == OMI_SERVER && s_optsPtr->nonRoot)
        {
            (*protocol)->internalProtocolBase.socketFile = socketFile;
            (*protocol)->internalProtocolBase.expectedSecretString = expectedSecretString;
            (*protocol)->protocolSocket.engineAuthState = PRT_AUTH_OK;
        }
        else
        {
            (*protocol)->internalProtocolBase.socketFile = socketFile;
            (*protocol)->internalProtocolBase.expectedSecretString = expectedSecretString;
            (*protocol)->protocolSocket.engineAuthState = PRT_AUTH_OK;
        }
    }
    
    return r;
}

MI_Result RunProtocol()
{
    /* Run the protocol object (waiting for new messages) */

    MI_Result r = MI_RESULT_OK;
    const PAL_Uint64 ONE_SECOND_USEC = 1000 * 1000;
    PAL_Uint64 start;
    PAL_Uint64 finish;

    PAL_Time(&start);

    if (s_optsPtr->livetime)
        finish = start + (s_optsPtr->livetime * ONE_SECOND_USEC);
    else
        finish = 0;

    for (;;)
    {
        PAL_Uint64 now;
        int reload_file_exists = -1;  // Unable to access
        char type = 'E';

        if (serverType == OMI_SERVER)
        {
            /* The existence of this reload_dispatcher file provides an alternate way of reloading OMI.
               This mechanism exists because the registering user may have write access to 
               registration directories because it belongs to the "omiusers" group, but cannot reload
               omiserver because it does not have root privileges */
            reload_file_exists = access(CONFIG_LOCALSTATEDIR "/omiusers/reload_dispatcher", F_OK);
            if (reload_file_exists == 0)
            {
                kill(s_dataPtr->enginePid, SIGUSR1);
                unlink(CONFIG_LOCALSTATEDIR "/omiusers/reload_dispatcher");
            }
            type = 'S';
        }

        if (s_dataPtr->reloadDispFlag || 
            reload_file_exists == 0)
        {
            trace_Reload_Providers(type);

            Lock_Acquire(&s_disp_mutex);
            Disp_Reload(&s_dataPtr->disp);
            s_dataPtr->reloadDispFlag = MI_FALSE;
            Lock_Release(&s_disp_mutex);
        }

        s_dataPtr->disp.agentmgr.serverType = (MI_Uint32)serverType;

        r = Selector_Run(&s_dataPtr->selector, ONE_SECOND_USEC, MI_FALSE);

        if (r != MI_RESULT_TIME_OUT)
            break;

        PAL_Time(&now);

        /* Log abnormally terminated terminated process */
        {
            size_t i;

            for (i = 0; i < _npids; i++)
            {
                trace_ChildProcessTerminatedAbnormally(_pids[i]);
            }

            _npids = 0;
        }

        /* check if server process is still alive */
        if (serverType == OMI_ENGINE && getppid() != s_dataPtr->parentPid)
        {
            trace_ParentProcessTerminated(s_dataPtr->parentPid, getppid());
            exit(1);
        }

        if (finish && now > finish)
            break;
    }

    trace_Server_ProtocolRun(r);

    s_dataPtr->selectorInitialized = MI_FALSE;

    if (MI_RESULT_TIME_OUT == r)
    {
        trace_Server_LiveTimeExpired();
        s_dataPtr->terminated = MI_TRUE;
    }

#if defined(CONFIG_POSIX)
    if (r == MI_RESULT_OK)
    {
        if (s_dataPtr->terminated)
            trace_ServerTerminated();
        else
            trace_ServerReReadingConfig();
    }
#endif

    // Destroy the dispatcher.
    Selector_RemoveAllHandlers(&s_dataPtr->selector);
    Disp_Destroy(&s_dataPtr->disp);

    {
        int i;
        for (i = 0; i < s_dataPtr->wsman_size; ++i)
        {
            WSMAN_Delete(s_dataPtr->wsman[i]);
        }
    }

    ProtocolBase_Delete(s_dataPtr->protocol0);
    if (s_dataPtr->protocol1)
        ProtocolSocketAndBase_Delete(s_dataPtr->protocol1);
    Selector_Destroy(&s_dataPtr->selector);

    /* Shutdown the network */
    Sock_Stop();

    return MI_RESULT_OK;
}

void ServerCleanup(int pidfile)
{
    /* Done with WSMAN* array; free it */
    PAL_Free(s_dataPtr->wsman);
    s_dataPtr->wsman_size = 0;

    /* Done with pointers to ports; free them now */
    PAL_Free(s_optsPtr->httpport);
    PAL_Free(s_optsPtr->httpsport);
    s_optsPtr->httpport_size = s_optsPtr->httpsport_size = 0;

    if (s_optsPtr->serviceAccount)
    {
        PAL_Free((void*)s_optsPtr->serviceAccount);
    }
    if (s_optsPtr->ntlmCredFile)
    {
        PAL_Free(s_optsPtr->ntlmCredFile);
    }
    if (s_optsPtr->krb5CredCacheSpec)
    {
        DestroyKrb5CredCache(s_optsPtr->krb5CredCacheSpec); // So it can't be looked at after run
        PAL_Free(s_optsPtr->krb5CredCacheSpec);
    }
    if (s_optsPtr->krb5KeytabPath)
    {
        PAL_Free(s_optsPtr->krb5KeytabPath);
    }

#if defined(CONFIG_POSIX)
    if (pidfile != -1)
    {
        /* Close PID file */
        close(pidfile);

        /* Remove PID file */
        if (unlink(OMI_GetPath(ID_PIDFILE)) != 0)
        {
            trace_FailedRemovePIDFile(scs(OMI_GetPath(ID_PIDFILE)));
        }
    }
#endif

    /* Log that we are exiting */
    trace_ServerExiting(arg0);

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
}

