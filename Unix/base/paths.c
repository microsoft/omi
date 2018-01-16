/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "paths.h"
#include <pal/strings.h>
#include "process.h"
/* #include <pal/format.h> */
#include <pal/format.h>
#include <pal/file.h>

#define RUNDIR CONFIG_LOCALSTATEDIR "/run"
#define LOGDIR CONFIG_LOCALSTATEDIR "/log"
#define SCHEMADIR CONFIG_DATADIR "/omischema"
#define SCHEMAFILE SCHEMADIR "/CIM_Schema.mof"
#define PIDFILE RUNDIR "/omiserver.pid"
#define LOGFILE LOGDIR "/omiserver.log"
#define REGISTERDIR CONFIG_SYSCONFDIR "/omiregister"
#define PEMFILE CONFIG_CERTSDIR "/omi.pem"
#define KEYFILE CONFIG_CERTSDIR "/omikey.pem"
#define AGENTPROGRAM CONFIG_BINDIR "/omiagent"
#define SERVERPROGRAM CONFIG_BINDIR "/omiserver"
#define CONFIGFILE CONFIG_SYSCONFDIR "/omiserver.conf"
#define CLIENTCONFIGFILE CONFIG_SYSCONFDIR "/omicli.conf"
#define SOCKETFILE RUNDIR "/omiserver.sock"
#define HTTPSENDTRACEFILE LOGDIR "/omiserver-send.trc"
#define HTTPRECVTRACEFILE LOGDIR "/omiserver-recv.trc"
#define HTTPCLIENTSENDTRACEFILE LOGDIR "/omiclient-send.trc"
#define HTTPCLIENTRECVTRACEFILE LOGDIR "/omiclient-recv.trc"
#define KRB5_KEYTABPATH CONFIG_CREDSDIR "/omi.keytab"

BEGIN_EXTERNC

typedef struct _PathInfo
{
    char* nickname;
    char* str;
    MI_Boolean dynamic;
}
PathInfo;

static PathInfo _paths[] =
{
    { "prefix", CONFIG_PREFIX, MI_FALSE },
    { "libdir", CONFIG_LIBDIR, MI_FALSE },
    { "bindir", CONFIG_BINDIR, MI_FALSE },
    { "localstatedir", CONFIG_LOCALSTATEDIR, MI_FALSE },
    { "sysconfdir", CONFIG_SYSCONFDIR, MI_FALSE },
    { "providerdir", CONFIG_PROVIDERDIR, MI_FALSE },
    { "certsdir", CONFIG_CERTSDIR, MI_FALSE },
    { "datadir", CONFIG_DATADIR, MI_FALSE },
    { "rundir", RUNDIR, MI_FALSE },
    { "logdir", LOGDIR, MI_FALSE },
    { "schemadir", SCHEMADIR, MI_FALSE },
    { "schemafile", SCHEMAFILE, MI_FALSE },
    { "pidfile", PIDFILE, MI_FALSE },
    { "logfile", LOGFILE, MI_FALSE },
    { "registerdir", REGISTERDIR, MI_FALSE },
    { "pemfile", PEMFILE, MI_FALSE },
    { "keyfile", KEYFILE, MI_FALSE },
    { "agentprogram", AGENTPROGRAM, MI_FALSE },
    { "serverprogram", SERVERPROGRAM, MI_FALSE },
    { "includedir", CONFIG_INCLUDEDIR, MI_FALSE },
    { "configfile", CONFIGFILE, MI_FALSE },
    { "socketfile", SOCKETFILE, MI_FALSE },
    { "tmpdir", CONFIG_TMPDIR, MI_FALSE },
    { "destdir", "/", MI_FALSE },
    { "authdir", CONFIG_AUTHDIR, MI_FALSE },
    { "httpsendtracefile", HTTPSENDTRACEFILE, MI_FALSE },
    { "httprecvtracefile", HTTPRECVTRACEFILE, MI_FALSE },
    { "httpclientsendtracefile", HTTPCLIENTSENDTRACEFILE, MI_FALSE },
    { "httpclientrecvtracefile", HTTPCLIENTRECVTRACEFILE, MI_FALSE },
    { "srcdir", CONFIG_SRCDIR, MI_FALSE },
    { "keytabfile", KRB5_KEYTABPATH, MI_FALSE },
    { "clientconfigfile", CLIENTCONFIGFILE, MI_FALSE },
    { "credsdir", CONFIG_CREDSDIR, MI_FALSE }
};

#include <pal/ownedmemory.h>

static char* Strdup_InOwnedMemory(
    _In_z_ const char* s)
{
    size_t sLen = 0;
    char *newMemory = NULL;
    if(!s) return NULL;
    
    sLen = Strlen(s);
    newMemory = (char *)OwnedMemory_Alloc(sizeof(char) * (sLen + 1));

    if(!newMemory)
        return NULL;

    Strlcpy(newMemory, s, sLen + 1);    

    return newMemory;
}

const char* OMI_GetPath(PathID id)
{
    int i = ((int)id) % MI_COUNT(_paths);
    return _paths[i].str;
}

int CreateLogFileNameWithPrefix(_In_z_ const char *prefix,  _Pre_writable_size_(PAL_MAX_PATH_SIZE) PAL_Char finalPath[PAL_MAX_PATH_SIZE])
{
    char path[PAL_MAX_PATH_SIZE];        

    if (Strlcpy(path, OMI_GetPath(ID_LOGDIR), PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
    {
        return -1;
    }
            
    Strlcat(path, "/", PAL_MAX_PATH_SIZE);
    Strlcat(path, prefix, PAL_MAX_PATH_SIZE);
    Strlcat(path, ".log", PAL_MAX_PATH_SIZE);
#if defined(CONFIG_ENABLE_WCHAR)        
    TcsStrlcpy(finalPath, path, MI_COUNT(path));        
#else
    Strlcpy(finalPath, path, MI_COUNT(path));
#endif
    
    return 0;
}

int SetPath(PathID id, const char* path)
{
    /* First prepend 'destdir' to all other paths */
    if (id == ID_DESTDIR)
    {
        size_t i = 0;

        for (i = 0; i < MI_COUNT(_paths); i++)
        {
            char buf[PAL_MAX_PATH_SIZE];

            if (i == (size_t)ID_DESTDIR)
                continue;

            if (strcmp(_paths[i].nickname, "destdir") == 0)
                continue;

            Strlcpy(buf, path, sizeof(buf));
            Strlcat(buf, "/", sizeof(buf));
            Strlcat(buf, _paths[i].str, sizeof(buf));

            if (SetPath((PathID)i, buf) != 0)
                return -1;
        }
    }

    /* Set the path */
    {
        size_t i = (size_t)((int)id) % MI_COUNT(_paths);
        char* str = Strdup_InOwnedMemory(path);

        if (!str)
            return -1;

        if (_paths[i].dynamic)
            OwnedMemory_Free(_paths[i].str);

        _paths[i].str = str;
        _paths[i].dynamic = MI_TRUE;
    }

    return 0;
}

void PrintPaths()
{
    size_t i;

    for (i = 0; i < MI_COUNT(_paths); i++)
    {
        PathID id = (PathID)i;
        Tprintf(PAL_T("%s=%s\n"), scs(_paths[i].nickname), scs(OMI_GetPath(id)));
    }
}

int SetPathFromNickname(const char* nickname, const char* path)
{
    size_t i;

    for (i = 0; i < MI_COUNT(_paths); i++)
    {
        if (strcmp(_paths[i].nickname, nickname) == 0)
            return SetPath((PathID)i, path);
    }

    return -1;
}

MI_Boolean IsNickname(const char* nickname)
{
    size_t i;

    for (i = 0; i < MI_COUNT(_paths); i++)
    {
        if (strcmp(_paths[i].nickname, nickname) == 0)
        {
            return MI_TRUE;
        }
    }

    /* Not found */
    return MI_FALSE;
}

_Use_decl_annotations_
char* TempPath(char path[PAL_MAX_PATH_SIZE], const char* file)
{
    if (Strlcpy(path, OMI_GetPath(ID_TMPDIR), PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
        return NULL;

    if (Strlcat(path, "/", PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
        return NULL;

    if (Strlcat(path, file, PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
        return NULL;

    return path;
}

_Use_decl_annotations_
TChar* TSTempPath(TChar path[PAL_MAX_PATH_SIZE], const char* file)
{
    if (TcsStrlcpy(path, OMI_GetPath(ID_TMPDIR), PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
        return NULL;
    if (TcsStrlcat(path, "/", PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
        return NULL;

    if (TcsStrlcat(path, file, PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
        return NULL;

    return path;
}

END_EXTERNC
