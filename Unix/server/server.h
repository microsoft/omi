/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _server_h
#define _server_h

#include <limits.h>
#include <unistd.h>
#include <protocol/protocol.h>
#include <pal/sleep.h>
#if defined(_ENGINE)
#include <wsman/wsman.h>
#include <disp/disp.h>
#endif
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
#if defined(_ENGINE)
    Disp            disp;
    WSMAN**         wsman;
#endif

    // 0 = socketfile, 1 = socketpair
    MuxIn           mux[2];
    ProtocolBase *protocol0;
    ProtocolSocketAndBase *protocol1;

    int             wsman_size;
    Selector        selector;
    MI_Boolean      selectorInitialized;
    MI_Boolean      reloadDispFlag;
    MI_Boolean      terminated;

    /* pointers to self with different types - one per supported transport */
    ServerCallbackData  protocolData;
    ServerCallbackData  wsmanData;
    
    pid_t enginePid;
    pid_t parentPid;
    Sock internalSock;
};

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
    MI_Boolean ignoreAuthentication;
    MI_Boolean locations;
    MI_Boolean logstderr;
    unsigned short *httpport;
    int httpport_size;
    unsigned short *httpsport;
    int httpsport_size;
    char* sslCipherSuite;
#if defined(_ENGINE)
    SSL_Options sslOptions;
#endif
    MI_Uint64 idletimeout;
    MI_Uint64 livetime;
    Log_Level logLevel;
    char *ntlmCredFile;
    char *krb5KeytabPath;
    char *krb5CredCacheSpec;
    const char *serviceAccount;
    uid_t serviceAccountUID;
    gid_t serviceAccountGID;
    Sock socketpairPort;
}
Options;

typedef enum _ServerType { OMI_SERVER, OMI_ENGINE } ServerType;

void PrintProviderMsg(_In_ Message* msg);
void GetCommandLineDestDirOption(int* argc_, const char* argv[]);
void GetCommandLineOptions(int* argc_, const char* argv[]);
void OpenLogFile();
void SetDefaults(Options *opts_ptr, ServerData *data_ptr, const char *executable, ServerType type, Lock *disp_mutex_ptr);
void GetConfigFileOptions();
void HandleSIGTERM(int sig);
void HandleSIGHUP(int sig);
void HandleSIGUSR1(int sig);
void HandleSIGCHLD(int sig);
void FUNCTION_NEVER_RETURNS err(const ZChar* fmt, ...);
void FUNCTION_NEVER_RETURNS info_exit(const ZChar* fmt, ...);
MI_Result BinaryProtocolListenFile(const char *socketFile, MuxIn *mux, ProtocolBase **protocol, const char *expectedSecretString);
MI_Result BinaryProtocolListenSock(Sock sock, MuxIn *mux, ProtocolSocketAndBase **protocol, const char *socketFile, const char *expectedSecretString);
MI_Result WsmanProtocolListen();
MI_Result RunProtocol();
MI_Result InitializeNetwork();
void ServerCleanup(int pidfile);
int VerifyServiceAccount();

#if defined(_ENGINE)
void EngineCallback(_Inout_ InteractionOpenParams* interactionParams);
#else
void ServerCallback(_Inout_ InteractionOpenParams* interactionParams);
#endif

#endif /* _server_h */
