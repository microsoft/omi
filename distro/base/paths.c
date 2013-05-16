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

#include "paths.h"
#include "strings.h"
#include "process.h"
#include <io/io.h>

#if defined(CONFIG_OS_WINDOWS)
# include <windows.h>
# include <process.h>
#endif

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
#define SOCKETFILE RUNDIR "/omiserver.sock"
#define HTTPSENDTRACEFILE LOGDIR "/omiserver-send.trc"
#define HTTPRECVTRACEFILE LOGDIR "/omiserver-recv.trc"

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
#if defined(CONFIG_OS_WINDOWS)
    { "socketfile", "7777", MI_FALSE },
#else
    { "socketfile", SOCKETFILE, MI_FALSE },
#endif
    { "tmpdir", CONFIG_TMPDIR, MI_FALSE },
    { "destdir", "/", MI_FALSE },
    { "authdir", CONFIG_AUTHDIR, MI_FALSE },
    { "httpsendtracefile", HTTPSENDTRACEFILE, MI_FALSE },
    { "httprecvtracefile", HTTPRECVTRACEFILE, MI_FALSE },
    { "srcdir", CONFIG_SRCDIR, MI_FALSE },
};

#if defined(CONFIG_OS_WINDOWS)
static int _GetFullProgramPath(
    const char* programName,
    _Pre_writable_size_(MAX_PATH_SIZE) char path[MAX_PATH_SIZE])
{
    /* Get full path of the current module (library or program). */
    {
        DWORD r = GetModuleFileNameA(NULL, path, MAX_PATH_SIZE);

        if (r < 1 || r >= MAX_PATH_SIZE)
            return -1;
    }

    /* Replace name with name parameter */
    {
        char* end;

        end = strrchr(path, '\\');

        if (!end)
            return -1;

        if (programName)
        {
            end[1] = '\0';

            if (Strlcat(path, programName, MAX_PATH_SIZE) >= MAX_PATH_SIZE)
                return -1;
        }
        else
            end[0] = '\0';
    }

    /* Translate backward to forward slashes */
    {
        char* p;

        for (p = path; *p; p++)
        {
            if (*p == '\\')
                *p = '/';
        }
    }

    return 0;
}
#endif /* defined(CONFIG_OS_WINDOWS) */

#if defined(CONFIG_OS_WINDOWS)
static int _ResolvePrefixPath(_Pre_writable_size_(MAX_PATH_SIZE) _Null_terminated_ char path[MAX_PATH_SIZE])
{
    char* p;

    /* Get path of directory containing current module */
    if (_GetFullProgramPath(NULL, path) != 0)
        return -1;

    /* Work down directory hierarchy, looking for '.prefix' file */
    for (;;)
    {
        char buf[MAX_PATH_SIZE];

        /* Format path to .prefix file */
        Strlcpy(buf, path, sizeof(buf));
        Strlcat(buf, "/.prefix", sizeof(buf));

        /* If .prefix file exists, return success */
        if (access(buf, F_OK) == 0)
        {
            FILE* is;
            const char UUID[] = "E4349DE8-6E94-4CB6-AE44-45D8A61C489E";
            char uuid[36];

            /* Open .prefix file */
            is = Fopen(buf, "rb");
            if (!is)
                continue;

            /* Read UUID from file */
            if (fread(uuid, 1, sizeof(uuid), is) != sizeof(uuid))
            {
                fclose(is);
                continue;
            }

            /* Check whether UUID is the expected one */
            if (memcmp(uuid, UUID, sizeof(uuid)) != 0)
            {
                fclose(is);
                continue;
            }

            /* Success! */
            fclose(is);
            return 0;
        }

        /* Remove next level from path */
        p = strrchr(path, '/');
        if (!p)
        {
            /* Not found! */
            break;
        }

        *p = '\0';
    }

    /* repeat these steps from current directory:
        needed for nightly builds, since they build in
        standalone directory, outisde of 'source' */

    /* Get current directory */
    if (_getcwd(path, MAX_PATH_SIZE) == 0)
        return -1;

    /* Translate backward to forward slashes */
    {
        for (p = path; *p; p++)
        {
            if (*p == '\\')
                *p = '/';
        }
    }


    /* Work down directory hierarchy, looking for '.prefix' file */
    for (;;)
    {
        char buf[MAX_PATH_SIZE];

        if (!path || *path == 0)
            break;

        /* Format path to .prefix file */
        Strlcpy(buf, path, sizeof(buf));
        Strlcat(buf, "/.prefix", sizeof(buf));

        /* If .prefix file exists, return success */
        if (access(buf, F_OK) == 0)
        {
            FILE* is;
            const char UUID[] = "E4349DE8-6E94-4CB6-AE44-45D8A61C489E";
            char uuid[36];

            /* Open .prefix file */
            is = Fopen(buf, "rb");
            if (!is)
                continue;

            /* Read UUID from file */
            if (fread(uuid, 1, sizeof(uuid), is) != sizeof(uuid))
            {
                fclose(is);
                continue;
            }

            /* Check whether UUID is the expected one */
            if (memcmp(uuid, UUID, sizeof(uuid)) != 0)
            {
                fclose(is);
                continue;
            }

            /* Success! */
            fclose(is);
            return 0;
        }

        /* Remove next level from path */
        p = strrchr(path, '/');
        if (!p)
        {
            /* Not found! */
            break;
        }

        *p = '\0';
    }

    /* Not found! */
    return -1;
}
#endif /* defined(CONFIG_OS_WINDOWS) */

const char* GetPath(PathID id)
{
    int i = ((int)id) % MI_COUNT(_paths);

#if defined(CONFIG_OS_WINDOWS)
    /* Look for Windows programs in same directory as this module */
    if (id == ID_SERVERPROGRAM)
    {
        static char path[MAX_PATH_SIZE];

        if (path[0] == '\0')
        {
            if (_GetFullProgramPath("omiserver", path) != 0)
                return NULL;
        }

        return path;
    }
    else if (id == ID_PREFIX)
    {
        static char path[MAX_PATH_SIZE];

        if (path[0] == '\0')
        {
            if (_ResolvePrefixPath(path) != 0)
                return CONFIG_PREFIX;
        }

        return path;
    }
    else if (id == ID_SRCDIR)
    {
        static char path[MAX_PATH_SIZE];

        if (path[0] == '\0')
        {
            if (_ResolvePrefixPath(path) != 0)
                return CONFIG_SRCDIR;
        }

        return path;
    }

    /* Although id is defined in enumeration and will always be less than
     * MI_COUNT(_paths), VS prefast tool is compalining about buffer overrun
     */
#endif

#if defined(CONFIG_OS_WINDOWS)
    if (_paths[i].str[0] == '.' && !_paths[i].dynamic)
    {
        char buf[MAX_PATH_SIZE];
        Strlcpy(buf, GetPath(ID_PREFIX), sizeof(buf));
        Strlcat(buf, _paths[i].str + 1, sizeof(buf));
        _paths[i].str = Strdup(buf);
        _paths[i].dynamic = MI_TRUE;
    }
#endif

    return _paths[i].str;

}

int SetPath(PathID id, const char* path)
{
    /* First prepend 'destdir' to all other paths */
    if (id == ID_DESTDIR)
    {
        size_t i = 0;

        for (i = 0; i < MI_COUNT(_paths); i++)
        {
            char buf[MAX_PATH_SIZE];

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
        char* str = Strdup(path);

        if (!str)
            return -1;

        if (_paths[i].dynamic)
            free(_paths[i].str);

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
        Zprintf(ZT("%s=%s\n"), scs(_paths[i].nickname), scs(GetPath(id)));
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

END_EXTERNC
