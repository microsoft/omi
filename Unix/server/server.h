#ifndef __SERVER_H_
#define __SERVER_H_

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
    Server_SSL_Options sslOptions;
    MI_Uint64 idletimeout;
    MI_Uint64 livetime;
    Log_Level logLevel;
}
Options; 

#endif // __SERVER_H
