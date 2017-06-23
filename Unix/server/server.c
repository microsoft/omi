/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <stdlib.h>
#include <sock/sock.h>
#include <pal/dir.h>
#include <server/server.h>
#include <libgen.h>
#include <base/random.h>

#define S_SOCKET_LENGTH 8
#define S_SECRET_STRING_LENGTH 32
#define SOCKET_FILE_NAME_LENGTH 10

static Options s_opts;
static ServerData s_data;

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
    --nonroot                   Run in non-root mode.\n\
    --service ACCT              Use ACCT as the service account.\n\
\n");

static int _StartEngine(int argc, char** argv, const char *engineSockFile, const char *secretString)
{
    Sock s[2];
    char engineFile[PAL_MAX_PATH_SIZE];
    pid_t child;
    int fdLimit;
    int fd;
    int size;
    char socketString[S_SOCKET_LENGTH];
    MI_Result r;
    const char *binDir = OMI_GetPath(ID_BINDIR);

    Strlcpy(engineFile, binDir, PAL_MAX_PATH_SIZE);
    Strlcat(engineFile, "/omiengine", PAL_MAX_PATH_SIZE);
    argv[0] = engineFile;

    r = BinaryProtocolListenFile(engineSockFile, &s_data.mux[0], &s_data.protocol0, secretString);
    if (r != MI_RESULT_OK)
    {
        return -1;
    }
    
    if (s_data.internalSock != INVALID_SOCK)
    {
        Sock_Close(s_data.internalSock);
        s_data.internalSock = INVALID_SOCK;
    }

    if(socketpair(AF_UNIX, SOCK_STREAM, 0, s) != 0)
    {
        err(ZT("failed to create unix-domain socket pair"));
    }

    if (MI_RESULT_OK != Sock_SetBlocking(s[0], MI_FALSE) ||
        MI_RESULT_OK != Sock_SetBlocking(s[1], MI_FALSE))
    {
        trace_SetNonBlocking_Failed();
        return -1;
    }

    child = fork();
    if (child < 0)
    {
        err(PAL_T("fork failed"));
    }

    if (child > 0)   // parent
    {
        s_data.enginePid = child;
        trace_ServerClosingSocket(0, s[1]);
        Sock_Close(s[1]);
        s_data.internalSock = s[0];

        r = BinaryProtocolListenSock(s[0], &s_data.mux[1], &s_data.protocol1, engineSockFile, secretString);
        if (r != MI_RESULT_OK)
        {
            return -1;
        }

        return 0;
    }

    // child code here

    trace_EngineClosingSocket(0, s[0]);
    Sock_Close(s[0]);

    if (0 == IsRoot())
    {
        if (SetUser(s_opts.serviceAccountUID, s_opts.serviceAccountGID) != 0)
        {
            err(PAL_T("failed to change uid/gid of engine"));
        }  
    }

    /* Close all open file descriptors except provided socket
     (Some systems have UNLIMITED of 2^64; limit to something reasonable) */

    fdLimit = getdtablesize();
    if (fdLimit > 2500 || fdLimit < 0)
    {
        fdLimit = 2500;
    }

    /* ATTN: close first 3 also! Left for debugging only */
    for (fd = 3; fd < fdLimit; ++fd)
    {
        if (fd != s[1])
            close(fd);
    }

    argv[argc-1] = int64_to_a(socketString, S_SOCKET_LENGTH, (long long)s[1], &size);

    execv(argv[0], argv);
    err(PAL_T("Launch failed: %d"), errno);
    exit(1);
}

static char** _DuplicateArgv(int argc, const char* argv[])
{
    int i;

    char **newArgv = (char**)malloc((argc+3)*sizeof(char*));

    // argv[0] will be filled in later
    if (argc > 1)
    {
        for (i = 1; i<argc; ++i)
        {
            newArgv[i] = (char*)argv[i];
        }
    }

    newArgv[argc] = "--socketpair";
    newArgv[argc+1] = NULL;  // to be filled later
    newArgv[argc+2] = NULL;

    return newArgv;
}

static int _CreateSockFile(char *sockFileBuf, int sockFileBufSize, char *secretStringBuf, int secretStringBufSize)
{
    char sockDir[PAL_MAX_PATH_SIZE];
    char file[PAL_MAX_PATH_SIZE];
    char name[SOCKET_FILE_NAME_LENGTH];

    Strlcpy(sockDir, OMI_GetPath(ID_SYSCONFDIR), PAL_MAX_PATH_SIZE);
    Strlcat(sockDir, "/sockets", PAL_MAX_PATH_SIZE);

    Dir *dir = Dir_Open(sockDir);
    if (dir)
    {
        DirEnt *entry;
        while((entry = Dir_Read(dir)))
        {
            if (strcmp(entry->name, ".") == 0 || strcmp(entry->name, "..") == 0)
                continue;

            Strlcpy(file, sockDir, PAL_MAX_PATH_SIZE);
            Strlcat(file, "/", PAL_MAX_PATH_SIZE);
            Strlcat(file, entry->name, PAL_MAX_PATH_SIZE);
            //printf("Removing %s...\n", file);
            unlink(file);
        }
        Dir_Close(dir);
    }
    else
    {
        int r;

        if (0 == IsRoot())
        {
            r = Mkdir(sockDir, 0700);
            if (r != 0)
            {
                err(PAL_T("failed to create sockets directory: %s"), scs(sockDir));
            }

            r = chown(sockDir, s_opts.serviceAccountUID, s_opts.serviceAccountGID);
            if (r != 0)
            {
                err(PAL_T("failed to chown sockets directory: %s"), scs(sockDir));
            }
        }
        else
        {
            r = Mkdir(sockDir, 0755);
            if (r != 0)
            {
                err(PAL_T("failed to create sockets directory: %s"), scs(sockDir));
            }
        }
    }
        
    if ( GenerateRandomString(name, SOCKET_FILE_NAME_LENGTH) != 0)
    {
        err(PAL_T("Unable to generate socket file name"));
    }

    if ( GenerateRandomString(secretStringBuf, secretStringBufSize) != 0)
    {
        err(PAL_T("Unable to generate secretString"));
    }

    Strlcpy(sockFileBuf, sockDir, sockFileBufSize);
    Strlcat(sockFileBuf, "/omi_", sockFileBufSize);
    Strlcat(sockFileBuf, name, sockFileBufSize);

    return 0;
}

int servermain(int argc, const char* argv[])
{
#if defined(CONFIG_POSIX)
    int pidfile = -1;
#endif
    int engine_argc = 0;
    char **engine_argv = NULL;
    char socketFile[PAL_MAX_PATH_SIZE];
    char secretString[S_SECRET_STRING_LENGTH];
    const char* arg0 = argv[0];
    MI_Result result;    
    int r;

    SetDefaults(&s_opts, &s_data, arg0, OMI_SERVER);

    /* pass all command-line args to engine */
    engine_argc = argc + 2;
    engine_argv = _DuplicateArgv(argc, argv);

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
        PrintPaths();
        Tprintf(ZT("\n"));
        exit(0);
    }

#if defined(CONFIG_POSIX)
    if (s_opts.stop || s_opts.reloadConfig)
    {
        if (PIDFile_IsRunning() != 0)
        {
            info_exit(ZT("server is not running\n"));
        }

        if (PIDFile_Signal(s_opts.stop ? SIGTERM : SIGHUP) != 0)
        {
            err(ZT("failed to stop server\n"));
        }

        if (s_opts.stop)
        {
            Tprintf(ZT("%s: stopped server\n"), scs(arg0));
        }
        else
        {
            Tprintf(ZT("%s: refreshed server\n"), scs(arg0));
        }

        exit(0);
    }
    if (s_opts.reloadDispatcher)
    {
        if (PIDFile_IsRunning() != 0)
        {
            info_exit(ZT("server is not running\n"));
        }

        if (PIDFile_Signal(SIGUSR1) != 0)
        {
            err(ZT("failed to reload dispatcher on the server\n"));
        }

        Tprintf(ZT("%s: server has reloaded its dispatcher\n"), scs(arg0));

        exit(0);        
    }
#endif

#if defined(CONFIG_POSIX)

    if (PIDFile_IsRunning() == 0)
    {
        err(ZT("server is already running\n"));
    }

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
    if (0 != SetSignalHandler(SIGTERM, HandleSIGTERM) ||
        0 != SetSignalHandler(SIGHUP, HandleSIGHUP) ||
        0 != SetSignalHandler(SIGUSR1, HandleSIGUSR1))
    {
        err(ZT("cannot set sighandler, errno %d"), errno);
    }

    /* Watch for SIGCHLD signals */
    SetSignalHandler(SIGCHLD, HandleSIGCHLD);
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
    {
        err(ZT("failed to daemonize server process"));
    }

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

    if (s_opts.nonRoot == MI_TRUE)
    {
        r = VerifyServiceAccount();
        if (r != 0)
        {
            err(ZT("invalid service account:  %T"), s_opts.serviceAccount);
        }
    }

    while (!s_data.terminated)
    {
        result = InitializeNetwork();
        if (result != MI_RESULT_OK)
        {
            err(ZT("Failed to initialize network"));
        }

        if (s_opts.nonRoot == MI_TRUE)
        {
            r = _CreateSockFile(socketFile, PAL_MAX_PATH_SIZE, secretString, S_SECRET_STRING_LENGTH);
            if (r != 0)
            {
                err(ZT("failed to create socket file"));
            }

            r = _StartEngine(engine_argc, engine_argv, socketFile, secretString);
            if (r != 0)
            {
                err(ZT("failed to start omi engine"));
            }
        }
        else
        {
            result = WsmanProtocolListen();
            if (result != MI_RESULT_OK)
            {
                err(ZT("Failed to initialize Wsman"));
            }

            result = BinaryProtocolListenFile(OMI_GetPath(ID_SOCKETFILE), &s_data.mux[0], &s_data.protocol0, NULL);
            if (result != MI_RESULT_OK)
            {
                err(ZT("Failed to initialize binary protocol for socket file"));
            }
        }

        result = RunProtocol();
        if (result != MI_RESULT_OK)
        {
            err(ZT("Failed protocol loop"));
        }
    }

    free(engine_argv);
    ServerCleanup(pidfile);

    return 0;
}
