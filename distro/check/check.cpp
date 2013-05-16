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

#include <climits>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <omiclient/client.h>
#include <base/args.h>
#include <base/dir.h>
#include <base/result.h>
#include <base/strings.h>
#include <base/paths.h>
#include <base/conf.h>
#include <base/env.h>
#include <base/getopt.h>
#include <io/io.h>
#include <base/time.h>

using namespace mi;

const char* arg0;

struct Options
{
    bool help;
};

static Options opts;

PRINTF_FORMAT(1, 2)
static void err(const ZChar* fmt, ...)
{
    Fzprintf(stderr, ZT("%s: "), scs(arg0));

    va_list ap;
    va_start(ap, fmt);
    Vfzprintf(stderr, fmt, ap);
    va_end(ap);

    Fzprintf(stderr, ZT("\n"));
    exit(1);
}

static void _GetCommandLineOptions(
    int& argc,
    const char* argv[],
    Options& options)
{
    GetOptState state = GETOPTSTATE_INITIALIZER;
    const char* supportedOptions[] =
    {
        "--destdir",
        "-h",
        "--help",
        NULL,
    };

    for ( ; ; )
    {
        int r = GetOpt(&argc, argv, supportedOptions, &state);

        if (r == 1)
            break;

        if (r == -1)
            err(ZT("%s"), scs(state.err));

        if (strcmp(state.opt, "-h") == 0 || strcmp(state.opt, "--help") == 0)
        {
            options.help = true;
        }
    }
}

class ClientHandler : public Handler
{
public:

    virtual void HandleConnect()
    {
    }


    virtual void HandleNoOp(Uint64 msgID)
    {
    }

    virtual void HandleConnectFailed()
    {
    }

    virtual void HandleDisconnect()
    {
    }

    virtual void HandleInstance(Uint64 msgID, const DInstance& instance)
    {
    }

    virtual void HandleResult(Uint64 msgID, MI_Result result)
    {
    }
};

static void _CheckIdentifyProvider(Client& cli, const ZChar* nameSpace)
{
    const Uint64 TIMEOUT = 10 * 1000 * 1000;

    // Enumerate instances os OMI_Identify:

    Array<DInstance> instances;
    Result result;

    Zprintf(ZT("Enumerating identify instances... "));
    fflush(stdout);

    if (!cli.EnumerateInstances(nameSpace, ZT("OMI_Identify"), true, 
        TIMEOUT, instances, String(), String(), result))
    {
        Zprintf(ZT("failed\n"));
        err(ZT("communication failed (cannot connect/initiate command)"));
        exit(1);
    }

    Zprintf(ZT("ok\n"));

    // Check identify instance.

    if (instances.GetSize() != 1)
    {
        err(ZT("expected one instance of OMI_Identify but found %u"), 
            instances.GetSize());
    }

    Zprintf(ZT("Checking for standard namespaces... "));
    fflush(stdout);

    StringA nameSpaces;
    bool isNull;
    bool isKey;
    
    if (!instances[0].GetStringA(
        ZT("ConfigNameSpaces"), 
        nameSpaces, 
        isNull, 
        isKey))
    {
        Zprintf(ZT("failed\n"));
        err(ZT("missing ConfigNameSpaces property\n"));
    }

    bool foundRootNw = false;
    bool foundRootCimv2 = false;
    bool foundInterop = false;
    bool foundRootCheck = false;

    // Sort the array
    for (size_t i = 0; i < nameSpaces.GetSize(); i++)
    {
        if (nameSpaces[i] == ZT("root-omi"))
        {
            foundRootNw = true;
        }
        else if (nameSpaces[i] == ZT("root-check"))
        {
            foundRootCheck = true;
        }
        else if (nameSpaces[i] == ZT("root-cimv2"))
        {
            foundRootCimv2 = true;
        }
        else if (nameSpaces[i] == ZT("interop"))
        {
            foundInterop = true;
        }
    }

    if (!foundRootNw)
    {
        Zprintf(ZT("failed\n"));
        err(ZT("missing namespace directory: root-omi"));
    }

    if (!foundRootCheck)
    {
        Zprintf(ZT("failed\n"));
        err(ZT("missing namespace directory: root-check"));
    }

    if (!foundRootCimv2)
    {
        Zprintf(ZT("failed\n"));
        err(ZT("missing namespace directory: root-cimv2"));
    }

    if (!foundInterop)
    {
        Zprintf(ZT("failed\n"));
        err(ZT("missing namespace directory: interop"));
    }

    Zprintf(ZT("ok\n"));
}

static void _CheckDirLayout()
{
    Zprintf(ZT("Checking directory layout... "));
    fflush(stdout);

    if (Chdir(GetPath(ID_PREFIX)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(GetPath(ID_PREFIX)));

    if (Chdir(GetPath(ID_LIBDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(GetPath(ID_LIBDIR)));

    if (Chdir(GetPath(ID_BINDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(GetPath(ID_BINDIR)));

    if (Chdir(GetPath(ID_LOCALSTATEDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(GetPath(ID_LOCALSTATEDIR)));

    if (Chdir(GetPath(ID_SYSCONFDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(GetPath(ID_SYSCONFDIR)));

    if (Chdir(GetPath(ID_CERTSDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(GetPath(ID_CERTSDIR)));

    if (Chdir(GetPath(ID_CERTSDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(GetPath(ID_CERTSDIR)));

    if (Chdir(GetPath(ID_DATADIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(GetPath(ID_DATADIR)));

    if (Chdir(GetPath(ID_RUNDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(GetPath(ID_RUNDIR)));

    if (Chdir(GetPath(ID_LOGDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(GetPath(ID_LOGDIR)));

    if (Chdir(GetPath(ID_REGISTERDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(GetPath(ID_REGISTERDIR)));

    if (Chdir(GetPath(ID_INCLUDEDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(GetPath(ID_INCLUDEDIR)));

    if (Chdir(GetPath(ID_DESTDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(GetPath(ID_DESTDIR)));

    if (Chdir(GetPath(ID_AUTHDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(GetPath(ID_AUTHDIR)));

    Zprintf(ZT("ok\n"));
}

static void _Check(Client& cli)
{
    // Check in-process identify provider.
    _CheckIdentifyProvider(cli, MI_T("root/omi"));

    // Check out-of-process identify provider.
    _CheckIdentifyProvider(cli, MI_T("root/check"));

    // Check directory layout:
    _CheckDirLayout();
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

const char USAGE[] = "\
Usage: %s [OPTIONS] COMMAND ...\n\
\n\
This tool checks the sanity of an OMI installation.\n\
\n\
OPTIONS:\n\
    --destdir           Set the destination directory (where var/run/omiserver.sock is located).\n\
    -h, --help          Print this help message.\n\
\n\
\n";

int main(int argc, const char* argv[])
{
    arg0 = argv[0];
    const Uint64 CONNECT_TIMEOUT_USEC = 10 * 1000 * 1000;
    Client client(new ClientHandler);

    // Get destdir option.
    GetCommandLineDestDirOption(&argc, argv);

    // Get options:
    _GetCommandLineOptions(argc, argv, opts);

    // There must be at least 1 argument left:
    if (argc != 1 || opts.help)
    {
        Fzprintf(stdout, ZT("%s"), scs(USAGE));
        exit(1);
    }

    // Connect to server:
    {
        ZChar path[MAX_PATH_SIZE];
        ZStrlcpy(path, GetPath(ID_SOCKETFILE), MAX_PATH_SIZE);

        Zprintf(ZT("Connecting locally to server... "));
        fflush(stdout);

        if (!client.Connect(
            path,
            String(), 
            String(), 
            CONNECT_TIMEOUT_USEC))
        {
            Zprintf(ZT("failed\n"));
            err(ZT("failed to connect to %s"), scs(GetPath(ID_SOCKETFILE)));
        }

        Zprintf(ZT("ok\n"));
    }

    // Perform check!
    _Check(client);
    Zprintf(ZT("\n"));

    return 0;
}
