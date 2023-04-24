/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <fcntl.h>
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

static int _StartEngine(int argc, char** argv, char ** envp, const char *engineSockFile)
{
    Sock s[2];
    char engineFile[PAL_MAX_PATH_SIZE];
    pid_t child;
    int fdLimit;
    int fd;
    int size;
    char socketString[S_SOCKET_LENGTH];
    char logfilefd[S_SOCKET_LENGTH];
    MI_Result r;
    const char *binDir = OMI_GetPath(ID_BINDIR);

    Strlcpy(engineFile, binDir, PAL_MAX_PATH_SIZE);
    Strlcat(engineFile, "/omiengine", PAL_MAX_PATH_SIZE);
    argv[0] = engineFile;

    r = BinaryProtocolListenFile(engineSockFile, &s_data.mux[0], &s_data.protocol0);
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
        trace_Failed_Socket_Pair();
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
        trace_Failed_Fork();
        err(PAL_T("fork failed"));
    }

    if (child > 0)   // parent
    {
        s_data.enginePid = child;
        trace_ServerClosingSocket(0, s[1]);
        Sock_Close(s[1]);
        s_data.internalSock = s[0];
        r = BinaryProtocolListenSock(s[0], &s_data.mux[1], &s_data.protocol1, engineSockFile);
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
            trace_Failed_Set_User_Engine();
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

    int logfd = Log_GetFD();
    
    /* closing FD for stdin,stdout,stderr also i.e. 0,1,2 respectively*/
    for (fd = 0; fd < fdLimit; ++fd)
    {
        if ((fd != s[1]) && (fd != logfd))
            close(fd);
    }

    /* Re-open fd 0,1,2. */
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);

    argv[argc-1] = int64_to_a(socketString, S_SOCKET_LENGTH, (long long)s[1], &size);
    argv[argc-3] = int64_to_a(logfilefd, S_SOCKET_LENGTH, (long long)logfd, &size);

    execve(argv[0], argv, (char * const*)envp);
    trace_Failed_Launch_Engine();
    err(PAL_T("Launch failed: %d"), errno);
    exit(1);
}

static char** _DuplicateArgv(int argc, const char* argv[])
{
    int i;

    char **newArgv = (char**)PAL_Malloc((argc+5)*sizeof(char*));
    if (!newArgv) 
    {
        return NULL;
    }

    // argv[0] will be filled in later
    if (argc > 1)
    {
        for (i = 1; i<argc; ++i)
        {
            newArgv[i] = (char*)argv[i];
        }
    }

    newArgv[argc] = "--logfilefd";
    newArgv[argc+1] = NULL;
    newArgv[argc+2] = "--socketpair";
    newArgv[argc+3] = NULL;  // to be filled later
    newArgv[argc+4] = NULL;

    return newArgv;
}


//
// Duplicates and sets needed variables and removes the rest
//
static char** _DuplicateEnvp(const char* envp[])
{
    int i;

    // Special env variables:

    static const char Krb5_Trace[]  = "KRB5_TRACE=";
    static const char Krb5_KTName[] = "KRB5_KTNAME=";
    static const char Krb5_CCName[] = "KRB5_CCNAME=";
    static const char Ntlm_User_File[] = "NTLM_USER_FILE=";

    static const char Krb5_Trace_Default[]  = "KRB5_TRACE=/dev/stderr";

    static const char *REQUIRED_ENV[] = {
                               Krb5_Trace,
                               Krb5_KTName,
                               Krb5_CCName,
                               Ntlm_User_File,
                               NULL
                            };
      

    int env_count = 0;
    int new_env_count = 0;
    int trace_set = 0;
    char *strp = NULL;

    if (envp)
    {
        char *envitem = NULL;
        for (envitem = (char*)(envp[0]); envitem; envitem = (char*)(envp[env_count]))
        { 
            env_count++;
        }
    }

    char **newEnv = (char**)PAL_Malloc((MI_COUNT(REQUIRED_ENV))*sizeof(char*));
    if (!newEnv)
    {
        goto err;
    }

    for (i = 1; i < env_count; ++i)
    {
        if ( Strncmp(Krb5_Trace, envp[i], sizeof(Krb5_Trace)-1) == 0 ) 
        {
            trace_set = 1;
            newEnv[new_env_count] = (char*)PAL_Strdup(envp[i]);
            if (!newEnv[new_env_count])
            {
                goto err;
            }
            new_env_count++;
        }
    }

    // Trace

    // We respect KRB5_TRACE set in the environment, but if it is not set we still set it if the log level
    // is info or debug

    if (s_opts.logLevel > 2 && !trace_set)
    {
        newEnv[new_env_count] = PAL_Malloc(sizeof(Krb5_Trace_Default));
        if (!newEnv[new_env_count])
        {
            goto err;
        }
        strp = newEnv[new_env_count];
        memcpy(strp, Krb5_Trace_Default, sizeof(Krb5_Trace_Default));
        new_env_count++;
    }

    // Keytab
    newEnv[new_env_count] = PAL_Malloc(sizeof(Krb5_KTName)+strlen(s_opts.krb5KeytabPath));
    if (!newEnv[new_env_count])
    {
        goto err;
    }
    strp = newEnv[new_env_count];
    new_env_count++;
 
    memcpy(strp, Krb5_KTName, sizeof(Krb5_KTName)-1);
    strp += sizeof(Krb5_KTName)-1;
    memcpy(strp, s_opts.krb5KeytabPath, strlen(s_opts.krb5KeytabPath)+1);

    // Cred Cache
    newEnv[new_env_count] = PAL_Malloc(sizeof(Krb5_CCName)+strlen(s_opts.krb5CredCacheSpec));
    if (!newEnv[new_env_count])
    {
        goto err;
    }
    strp = newEnv[new_env_count];
    new_env_count++;
 
    memcpy(strp, Krb5_CCName, sizeof(Krb5_CCName)-1);
    strp += sizeof(Krb5_CCName)-1;
    memcpy(strp, s_opts.krb5CredCacheSpec, strlen(s_opts.krb5CredCacheSpec)+1);

    // NTLM USer file

    if (s_opts.ntlmCredFile)
    {
        newEnv[new_env_count] = PAL_Malloc(sizeof(Ntlm_User_File)+strlen(s_opts.ntlmCredFile));
        if (!newEnv[new_env_count])
        {
            goto err;
        }
        strp = newEnv[new_env_count];
        new_env_count++;
     
        memcpy(strp, Ntlm_User_File, sizeof(Ntlm_User_File)-1);
        strp += sizeof(Ntlm_User_File)-1;
        memcpy(strp, s_opts.ntlmCredFile, strlen(s_opts.ntlmCredFile)+1);
    }

  //  newArgv[argc+1] = NULL;  // to be filled later
    newEnv[new_env_count++] = NULL;

    return newEnv;

err:

    if (newEnv)
    {
        int i = 0;
        for (i = 0; i < new_env_count; i++ )
        {
            if (newEnv[i])
            {
                PAL_Free(newEnv[i]);
                newEnv[i] = NULL;
            }
        }
        PAL_Free(newEnv);
    }
    return NULL;
}

// find all caller to this function
static int _CreateSockFile(char *sockFileBuf, int sockFileBufSize)
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
        // Socket directory created by installbuilder
        err(PAL_T("Cannot open sockets directory: %s"), scs(sockDir));
    }
        
    if ( GenerateRandomString(name, SOCKET_FILE_NAME_LENGTH) != 0)
    {
        trace_Failed_Generate_Socket_File_Name();
        err(PAL_T("Unable to generate socket file name"));
    }

    Strlcpy(sockFileBuf, sockDir, sockFileBufSize);
    Strlcat(sockFileBuf, "/omi_", sockFileBufSize);
    Strlcat(sockFileBuf, name, sockFileBufSize);

    return 0;
}

void _GetCommandLineServerOptions(
    int argc,
    const char* argv[])
{
    int i;

    for (i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-h") == 0 ||
            strcmp(argv[i], "--help") == 0)
        {
            Ftprintf(stderr, HELP, scs(argv[0]));
            exit(0);
        }
        else if (strcmp(argv[i], "-p") == 0)
        {
            PrintPaths();
            Tprintf(ZT("\n"));
            exit(0);
        }
#if defined(CONFIG_POSIX)
        else if (strcmp(argv[i], "-d") == 0)
        {
            if (Process_Daemonize() != 0)
            {
                err(ZT("failed to daemonize server process"));
            }
        }
        else if (strcmp(argv[i], "-s") == 0)
        {
            if (PIDFile_IsRunning() != 0)
            {
                info_exit(ZT("server is not running\n"));
            }

            if (PIDFile_Signal(SIGTERM) != 0)
            {
                err(ZT("failed to stop server\n"));
            }

            Tprintf(ZT("%s: stopped server\n"), scs(argv[0]));

            exit(0);
        }
        else if (strcmp(argv[i], "-r") == 0)
        {
            if (PIDFile_IsRunning() != 0)
            {
                info_exit(ZT("server is not running\n"));
            }

            if (PIDFile_Signal(SIGHUP) != 0)
            {
                err(ZT("failed to refresh server\n"));
            }

            Tprintf(ZT("%s: refreshed server\n"), scs(argv[0]));

            exit(0);
        }
        else if (strcmp(argv[i], "--reload-dispatcher") == 0)
        {
            if (PIDFile_IsRunning() != 0)
            {
                info_exit(ZT("server is not running\n"));
            }

            if (PIDFile_Signal(SIGUSR1) != 0)
            {
                err(ZT("failed to reload dispatcher on the server\n"));
            }

            Tprintf(ZT("%s: server has reloaded its dispatcher\n"), scs(argv[0]));

            exit(0);
        }
#endif
        else if (strcmp(argv[i], "--timestamp") == 0)
        {
            Tprintf(ZT("%s: %s\n"), scs(argv[0]), scs(CONFIG_TIMESTAMP));
            exit(0);
        }
        else if (strcmp(argv[i], "-v") == 0 ||
                strcmp(argv[i], "--version") == 0)
        {
            Tprintf(ZT("%s: %s"), scs(argv[0]),
                scs(CONFIG_PRODUCT "-" CONFIG_VERSION " - " CONFIG_DATE));
#if defined(CONFIG_ENABLE_DEBUG)
            Tprintf(ZT(" DEBUG\n"));
#else
            Tprintf(ZT("\n"));
#endif
            exit(0);
        }
    }
}

int servermain(int argc, const char* argv[], const char *envp[])
{
#if defined(CONFIG_POSIX)
    int pidfile = -1;
#endif
    int engine_argc = 0;
    char **engine_argv = NULL;
    char **engine_envp = NULL;
    char socketFile[PAL_MAX_PATH_SIZE];
    const char* arg0 = argv[0];
    MI_Result result;    
    int r;
    int process_return = 0;
    char *ntlm_user_file = getenv("NTLM_USER_FILE");

    SetDefaults(&s_opts, &s_data, arg0, OMI_SERVER);

    /* pass all command-line args to engine */
    engine_argc = argc + 4;
    engine_argv = _DuplicateArgv(argc, argv);
    if (!engine_argv)
    {
        err(ZT("probable out of memory\n"));
    }

    /* Get --destdir command-line option */
    GetCommandLineDestDirOption(&argc, argv);

    /* Get command-line options applicable to server only */
    _GetCommandLineServerOptions(argc, argv);

    /* Extract configuration file options */
    GetConfigFileOptions();

    /* Extract command-line options a second time (to override) */
    GetCommandLineOptions(argc, argv);

    engine_envp = _DuplicateEnvp(envp);
    if (!engine_envp)
    {
        err(ZT("probable out of memory\n"));
    }

    /* Open the log file */
    OpenLogFile();

#if defined(CONFIG_POSIX)

    if (PIDFile_IsRunning() == 0)
    {
        trace_OMI_Already_Running();
        err(ZT("server is already running\n"));
    }

    /* Verify that server is started as root */
    if (0 != IsRoot() && !s_opts.ignoreAuthentication)
    {
        trace_Need_Root_Access();
        err(ZT("expected to run as root"));
    }

    if (s_opts.ignoreAuthentication)
    {
        IgnoreAuthCalls(1);
    }

    SetPermissionGroups(&s_opts.allowedList, &s_opts.deniedList);

    /* Watch for SIGTERM signals */
    if (0 != SetSignalHandler(SIGTERM, HandleSIGTERM) ||
        0 != SetSignalHandler(SIGHUP, HandleSIGHUP) ||
        0 != SetSignalHandler(SIGUSR1, HandleSIGUSR1))
    {
        trace_Failed_Set_Sig_Handlers();
        err(ZT("cannot set sighandler, errno %d"), errno);
    }

    /* Watch for SIGCHLD signals */
    SetSignalHandler(SIGCHLD, HandleSIGCHLD);

    /* Watch for SIGUSR2 signals */
    SetSignalHandler(SIGUSR2, HandleSIGUSR2);
#endif

    /* Change directory to 'rundir' */
    if (Chdir(OMI_GetPath(ID_RUNDIR)) != 0)
    {
        trace_Failed_ChangeDir(OMI_GetPath(ID_RUNDIR));
        err(ZT("failed to change directory to: %s"), 
            scs(OMI_GetPath(ID_RUNDIR)));
    }

    /* Create PID file */
    if ((pidfile = PIDFile_OpenWrite()) == -1)
    {
        fprintf(stderr, "Could not create pid file %s\n", OMI_GetPath(ID_PIDFILE));
        trace_CreatePIDFileFailed(OMI_GetPath(ID_PIDFILE));

        process_return = 5;
        goto cleanup;
    }

    /* If ntlm cred file is in use, check permissions and set NTLM_USER_FILE env variable */

    if (ntlm_user_file)
    {
        /* We do NOT accept the NTLM_USER_FILE environement variable for the server */
        trace_NtlmEnvIgnored(ntlm_user_file);
        unsetenv("NTLM_USER_FILE");
    }

    if (s_opts.nonRoot == MI_TRUE)
    {
        r = VerifyServiceAccount();
        if (r != 0)
        {
            trace_Invalid_Service_Account(s_opts.serviceAccount);
            err(ZT("invalid service account:  %T"), s_opts.serviceAccount);
        }
    }

    if ((s_opts.ntlmCredFile || s_opts.krb5CredCacheSpec || s_opts.krb5KeytabPath) && !s_opts.ignoreAuthentication)
    {
       if (!ValidateGssCredentials(s_opts.ntlmCredFile, s_opts.krb5KeytabPath, s_opts.krb5CredCacheSpec, s_opts.serviceAccountUID, s_opts.serviceAccountGID))
       {
           trace_NtlmCredFileInvalid(s_opts.ntlmCredFile);
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
            r = _CreateSockFile(socketFile, PAL_MAX_PATH_SIZE);
            if (r != 0)
            {
                err(ZT("failed to create socket file"));
            }

            r = _StartEngine(engine_argc, engine_argv, engine_envp, socketFile);
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

            result = BinaryProtocolListenFile(OMI_GetPath(ID_SOCKETFILE), &s_data.mux[0], &s_data.protocol0);
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

cleanup:

#if defined(CONFIG_POSIX)
    /* reset signal handlers */
    if (0 != SetSignalHandler(SIGTERM, SIG_DFL) ||
        0 != SetSignalHandler(SIGHUP, SIG_DFL) ||
        0 != SetSignalHandler(SIGCHLD, SIG_DFL))
    {
        err(ZT("cannot reset sighandler, errno %d"), errno);
    }
#endif

    PAL_Free(engine_argv);

    if (engine_envp) 
    {
        char *envitem = NULL;
        int i = 0;
        for (envitem = engine_envp[0]; envitem; envitem = engine_envp[i]) 
        {
            if (envitem)
            {
                PAL_Free(envitem);
            }
            i++;
        }
        PAL_Free(engine_envp);
    }

    ServerCleanup(pidfile);

    return process_return;
}
