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
#include <pal/dir.h>
#include <base/result.h>
#include <pal/strings.h>
#include <base/paths.h>
#include <base/conf.h>
#include <base/env.h>
#include <base/omigetopt.h>
#include <pal/format.h>
#include <pal/sleep.h>

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
    Ftprintf(stderr, ZT("%s: "), scs(arg0));

    va_list ap;
    va_start(ap, fmt);
    Vftprintf(stderr, fmt, ap);
    va_end(ap);

    Ftprintf(stderr, ZT("\n"));
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
        "-h",
        NULL,
    };

    for (;;)
    {
        int r = GetOpt(&argc, argv, supportedOptions, &state);

        if (r == 1)
            break;

        if (r == -1)
            err(ZT("%s"), scs(state.err));

        if (strcmp(state.opt, "-h") == 0)
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


    virtual void HandleNoOp(Uint64 operationId)
    {
    }

    virtual void HandleConnectFailed()
    {
    }

    virtual void HandleDisconnect()
    {
    }

    virtual void HandleInstance(Uint64 operationId, const DInstance& instance)
    {
    }
            
    virtual void HandleResult(Uint64 operationId, MI_Result result)
    {        
    }

    /* need to define both HandleResult functions to prevent error about hiding base class virtual functions */
    virtual void HandleResult(Uint64 operationId, MI_Result result, const MI_Char *errorMessage, const DInstance* cimError)
    {
        return Handler::HandleResult(operationId, result, errorMessage, cimError);
    }
};

static void _CheckIdentifyProvider(Client& cli, const ZChar* nameSpace)
{
    const Uint64 TIMEOUT = 10 * 1000 * 1000;

    // Enumerate instances os OMI_Identify:

    Array<DInstance> instances;
    Result result;

    Tprintf(ZT("Enumerating identify instances... "));
    fflush(stdout);

    if (!cli.EnumerateInstances(nameSpace, ZT("OMI_Identify"), true, 
        TIMEOUT, instances, String(), String(), result))
    {
        Tprintf(ZT("failed\n"));
        err(ZT("communication failed (cannot connect/initiate command)"));
        exit(1);
    }

    Tprintf(ZT("ok\n"));

    // Check identify instance.

    if (instances.GetSize() != 1)
    {
        err(ZT("expected one instance of OMI_Identify but found %u"), 
            instances.GetSize());
    }

    Tprintf(ZT("Checking for standard namespaces... "));
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
        Tprintf(ZT("failed\n"));
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
        Tprintf(ZT("failed\n"));
        err(ZT("missing namespace directory: root-omi"));
    }

    if (!foundRootCheck)
    {
        Tprintf(ZT("failed\n"));
        err(ZT("missing namespace directory: root-check"));
    }

    if (!foundRootCimv2)
    {
        Tprintf(ZT("failed\n"));
        err(ZT("missing namespace directory: root-cimv2"));
    }

    if (!foundInterop)
    {
        Tprintf(ZT("failed\n"));
        err(ZT("missing namespace directory: interop"));
    }

    Tprintf(ZT("ok\n"));
}

static void _CheckDirLayout()
{
    Tprintf(ZT("Checking directory layout... "));
    fflush(stdout);

    if (Chdir(OMI_GetPath(ID_PREFIX)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(OMI_GetPath(ID_PREFIX)));

    if (Chdir(OMI_GetPath(ID_LIBDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(OMI_GetPath(ID_LIBDIR)));

    if (Chdir(OMI_GetPath(ID_BINDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(OMI_GetPath(ID_BINDIR)));

    if (Chdir(OMI_GetPath(ID_LOCALSTATEDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(OMI_GetPath(ID_LOCALSTATEDIR)));

    if (Chdir(OMI_GetPath(ID_SYSCONFDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(OMI_GetPath(ID_SYSCONFDIR)));

    if (Chdir(OMI_GetPath(ID_CERTSDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(OMI_GetPath(ID_CERTSDIR)));

    if (Chdir(OMI_GetPath(ID_CERTSDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(OMI_GetPath(ID_CERTSDIR)));

    if (Chdir(OMI_GetPath(ID_DATADIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(OMI_GetPath(ID_DATADIR)));

    if (Chdir(OMI_GetPath(ID_RUNDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(OMI_GetPath(ID_RUNDIR)));

    if (Chdir(OMI_GetPath(ID_LOGDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(OMI_GetPath(ID_LOGDIR)));

    if (Chdir(OMI_GetPath(ID_REGISTERDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(OMI_GetPath(ID_REGISTERDIR)));

    if (Chdir(OMI_GetPath(ID_INCLUDEDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(OMI_GetPath(ID_INCLUDEDIR)));

    if (Chdir(OMI_GetPath(ID_DESTDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(OMI_GetPath(ID_DESTDIR)));

    if (Chdir(OMI_GetPath(ID_AUTHDIR)) != 0)
        err(ZT("chdir(%s) failed\n"), scs(OMI_GetPath(ID_AUTHDIR)));

    Tprintf(ZT("ok\n"));
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
    -h                  Print this help message.\n\
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
        Ftprintf(stdout, ZT("%s"), scs(USAGE));
        exit(1);
    }

    // Connect to server:
    {
        TChar path[PAL_MAX_PATH_SIZE];
        TcsStrlcpy(path, OMI_GetPath(ID_SOCKETFILE), PAL_MAX_PATH_SIZE);

        Tprintf(ZT("Connecting locally to server... "));
        fflush(stdout);

        if (!client.Connect(
            path,
            String(), 
            String(), 
            CONNECT_TIMEOUT_USEC))
        {
            Tprintf(ZT("failed\n"));
            err(ZT("failed to connect to %s"), scs(OMI_GetPath(ID_SOCKETFILE)));
        }

        Tprintf(ZT("ok\n"));
    }

    // Perform check!
    _Check(client);
    Tprintf(ZT("\n"));

    return 0;
}
