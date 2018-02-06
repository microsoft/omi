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

static int _StartEngine(int argc, char** argv, char ** envp, const char *engineSockFile, const char *secretString)
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
    /* ATTN: close first 3 also! Left for debugging only */
    for (fd = 3; fd < fdLimit; ++fd)
    {
        if ((fd != s[1]) && (fd != logfd))
            close(fd);
    }

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
                trace_Failed_Socket_Directory_Create(sockDir);
                err(PAL_T("failed to create sockets directory: %s"), scs(sockDir));
            }

            r = chown(sockDir, s_opts.serviceAccountUID, s_opts.serviceAccountGID);
            if (r != 0)
            {
                trace_Failed_Socket_Directory_Chown(sockDir);
                err(PAL_T("failed to chown sockets directory: %s"), scs(sockDir));
            }
        }
        else
        {
            r = Mkdir(sockDir, 0755);
            if (r != 0)
            {
                trace_Failed_Socket_Directory_Create(sockDir);
                err(PAL_T("failed to create sockets directory: %s"), scs(sockDir));
            }
        }
    }
        
    if ( GenerateRandomString(name, SOCKET_FILE_NAME_LENGTH) != 0)
    {
        trace_Failed_Generate_Socket_File_Name();
        err(PAL_T("Unable to generate socket file name"));
    }

    if ( GenerateRandomString(secretStringBuf, secretStringBufSize) != 0)
    {
        trace_Failed_Generate_Secret_String();
        err(PAL_T("Unable to generate secretString"));
    }

    Strlcpy(sockFileBuf, sockDir, sockFileBufSize);
    Strlcat(sockFileBuf, "/omi_", sockFileBufSize);
    Strlcat(sockFileBuf, name, sockFileBufSize);

    return 0;
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
    char secretString[S_SECRET_STRING_LENGTH];
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
        info_exit(ZT("probable out of memory\n"));
        process_return = -1;
        goto cleanup;
    }

    /* Get --destdir command-line option */
    GetCommandLineDestDirOption(&argc, argv);

    /* Extract configuration file options */
    GetConfigFileOptions();

    /* Extract command-line options a second time (to override) */
    GetCommandLineOptions(&argc, argv);

    engine_envp = _DuplicateEnvp(envp);
    if (!engine_envp)
    {
        info_exit(ZT("probable out of memory\n"));
        process_return = 1;
        goto cleanup;
    }

    /* Open the log file */
    OpenLogFile();

    /* Print help */
    if (s_opts.help)
    {
        Ftprintf(stderr, HELP, scs(arg0));
        process_return = 0;
        goto cleanup;
    }

    /* Print locations of files and directories */
    if (s_opts.locations)
    {
        PrintPaths();
        Tprintf(ZT("\n"));
        process_return = 0;
        goto cleanup;
    }

#if defined(CONFIG_POSIX)
    if (s_opts.stop)
    {
        trace_Stop_OMI();

        if (PIDFile_IsRunning() != 0)
        {
            trace_OMI_Not_Running();
            info_exit(ZT("server is not running\n"));
        }

        if (PIDFile_Signal(SIGTERM) != 0)
        {
            trace_Stop_OMI_Failed();
            err(ZT("failed to stop server\n"));
        }

        trace_Stop_OMI_OK();
        Tprintf(ZT("%s: stopped server\n"), scs(arg0));

        process_return = 0;
        goto cleanup;
    }
    if (s_opts.reloadConfig)
    {
        trace_ReloadConfig_OMI();

        if (PIDFile_IsRunning() != 0)
        {
            trace_OMI_Not_Running();
            info_exit(ZT("server is not running\n"));
        }

        if (PIDFile_Signal(SIGHUP) != 0)
        {
            trace_ReloadConfig_OMI_Failed();
            err(ZT("failed to refresh server\n"));
        }

        trace_ReloadConfig_OMI_OK();
        Tprintf(ZT("%s: refreshed server\n"), scs(arg0));

        process_return = 0;
        goto cleanup;
    }
    if (s_opts.reloadDispatcher)
    {
        trace_ReloadDispatcher_OMI();

        if (PIDFile_IsRunning() != 0)
        {
            trace_OMI_Not_Running();
            info_exit(ZT("server is not running\n"));
        }

        if (PIDFile_Signal(SIGUSR1) != 0)
        {
            trace_ReloadDispatcher_OMI_Failed();
            err(ZT("failed to reload dispatcher on the server\n"));
        }

        trace_ReloadDispatcher_OMI_OK();
        Tprintf(ZT("%s: server has reloaded its dispatcher\n"), scs(arg0));

        process_return = 0;
        goto cleanup;
    }
#endif

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
        trace_Failed_Set_Sig_Handlers();
        err(ZT("cannot set sighandler, errno %d"), errno);
    }

    /* Watch for SIGCHLD signals */
    SetSignalHandler(SIGCHLD, HandleSIGCHLD);
#endif

    /* Change directory to 'rundir' */
    if (Chdir(OMI_GetPath(ID_RUNDIR)) != 0)
    {
        trace_Failed_ChangeDir(OMI_GetPath(ID_RUNDIR));
        err(ZT("failed to change directory to: %s"), 
            scs(OMI_GetPath(ID_RUNDIR)));
    }

#if defined(CONFIG_POSIX)
    /* Daemonize */
    if (s_opts.daemonize && Process_Daemonize() != 0)
    {
        trace_Failed_Daemonize();
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
        process_return = 5;
        goto cleanup;
    }
#endif

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
            r = _CreateSockFile(socketFile, PAL_MAX_PATH_SIZE, secretString, S_SECRET_STRING_LENGTH);
            if (r != 0)
            {
                err(ZT("failed to create socket file"));
            }

            r = _StartEngine(engine_argc, engine_argv, engine_envp, socketFile, secretString);
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
