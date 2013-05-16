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

#include <common.h>
#include <string>
#include <vector>
#include <base/lib.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <base/getopt.h>
#include <base/paths.h>
#include <base/dir.h>
#include <io/io.h>
#include <base/file.h>
#include <base/time.h>
#ifndef _MSC_VER
#include <dlfcn.h>
#include <sys/wait.h>
#endif
#include <omiclient/client.h>

#if defined(CONFIG_ENABLE_WCHAR)
typedef std::wstring ZString;
#else
typedef std::string ZString;
#endif

using namespace std;

static const ZChar USAGE[] = MI_T("\
Usage: %s [OPTIONS] PROVIDERLIBRARY\n\
\n\
OVERVIEW:\n\
    This program generates a provider registration file (.reg) from\n\
    information read from a provider library.\n\
\n\
OPTIONS:\n\
    -h, --help                  Print this help message.\n\
    -v, --version               Print version information.\n\
    -n, --namespace NAME        Register provider for this namespace (option\n\
                                may be repeated to specify multiple\n\
                                nsDirs).\n\
    -l, --link                  Mode for developers. Instead of copying library file\n\
                                link is created in lib directory.\n\
    -o, --hosting HOSTING       Use given hosting mode (@requestor@,@inproc@,<user>).\n\
\n\
EXAMPLES:\n\
    The following generates a provider registration file for the provider\n\
    contained in 'libDogProvider.so'. It then copies the .reg file and\n\
    the provider to the installed locations.\n\
\n\
        $ omireg -n interop -n root/cimv2 libDogProvider.so\n\
\n\
");

using namespace std;

static const char* arg0;

//==============================================================================
//
// err()
//
//     Writes a formatted error message to standard error (preceded by argv[0])
//     and then exists.
//
//==============================================================================

static void FUNCTION_NEVER_RETURNS err(const ZChar* fmt, ...)
{
    Fzprintf(stderr, ZT("%s: "), scs(arg0));

    va_list ap;
    va_start(ap, fmt);
    Vfzprintf(stderr, fmt, ap);
    va_end(ap);

    Fzprintf(stderr, ZT("\n"));
    exit(1);
}

//==============================================================================
//
// GetCommandLineOptions()
//
//     This function processes command line options.
//
//==============================================================================

struct Options
{
    bool help;
    bool devmode;
    string  hosting;
    vector<string> nsDirs;

    Options() : help(false), devmode(false)
    {
    }
};

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
            memmove((char*)&argv[i], (char*)&argv[i+2], sizeof(char*) * (argc-i-1));
            argc -= 2;
        }
        else if (strncmp(argv[i], "--destdir=", 10) == 0)
        {
            destdir = argv[i] + 10;
            memmove((char*)&argv[i], (char*)&argv[i+1], sizeof(char*) * (argc-i));

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

static void GetCommandLineOptions(
    int& argc,
    const char**& argv,
    Options& options)
{
    GetOptState state = GETOPTSTATE_INITIALIZER;
    const char* opts[] =
    {
        "-h",
        "--help",
        "-v",
        "--version",
        "-n:",
        "--namespace:",
        "-l",
        "--link",
        "-o:",
        "--hosting:",
        NULL
    };

    /* For each argument */
    for ( ; ; )
    {
        int r = GetOpt(&argc, (const char**)argv, opts, &state);

        if (r == 1)
            break;

        if (r == -1)
            err(ZT("%s"), scs(state.err));

        if (strcmp(state.opt, "-h") == 0 ||
            strcmp(state.opt, "--help") == 0)
        {
            options.help = true;
        }
        else if (strcmp(state.opt, "-v") == 0 ||
                 strcmp(state.opt, "--version") == 0)
        {
#if defined(CONFIG_OS_WINDOWS)
            Zprintf(ZT("%s: %S\n"), scs(arg0),
                zcs(CONFIG_PRODUCT L"-" CONFIG_VERSION L" - " CONFIG_DATE));
#else
            Zprintf(ZT("%s: %s\n"), scs(arg0),
                scs(CONFIG_PRODUCT "-" CONFIG_VERSION " - " CONFIG_DATE));
#endif
            exit(0);
        }
        else if (strcmp(state.opt, "-l") == 0 ||
            strcmp(state.opt, "--link") == 0)
        {
            options.devmode = true;
        }
        else if (strcmp(state.opt, "-n") == 0 ||
            strcmp(state.opt, "--namespace") == 0)
        {
            string ns = state.arg;

            for (size_t i = 0; i < ns.size(); i++)
            {
                if (ns[i] == '/')
                    ns[i] = NAMESPACE_SEPARATOR;
            }

            ns = string(GetPath(ID_REGISTERDIR)) + string("/") + ns;
            options.nsDirs.push_back(ns);
        }
        else if (strcmp(state.opt, "-o") == 0 ||
            strcmp(state.opt, "--hosting") == 0)
        {
            options.hosting = state.arg;
        }
    }
}

typedef MI_Module* (*MainProc)(MI_Server* server);

static string BaseName(const string& str)
{
    const char* start = strrchr(str.c_str(), '/');

    if (start != NULL)
        start++;
    else
        start = str.c_str();

    return string(start);
}

static string BaseLibName(const string& str)
{
    const char* start = strrchr(str.c_str(), '/');

    if (start != NULL)
        start++;
    else
        start = str.c_str();

    if (strncmp(start, "lib", 3) == 0)
        start += 3;

    const char* p = start;

    while (*p != '\0' && *p != '.')
        p++;

    return string(start, p - start);
}

static void PrintClassPath(FILE* os, const MI_ClassDecl* cd)
{
    for (const MI_ClassDecl* p = cd; p; p = p->superClassDecl)
    {
        if (p != cd)
            Fprintf(os, ":");
        Fprintf(os, "%Z", zcs(p->name));
    }
}

static const MI_ClassDecl* FindClassDecl(
    const MI_SchemaDecl* sd,
    const ZChar* className)
{
    for (MI_Uint32 i = 0; i < sd->numClassDecls; i++)
    {
        const MI_ClassDecl* p = sd->classDecls[i];

        if (Zcmp(p->name, className) == 0)
            return p;
    }

    return 0;
}

static void GenClassLine(
    FILE* os,
    const MI_SchemaDecl* sd,
    const MI_ClassDecl* cd)
{
    // Print the class path: CLASS1.CLASS2.CLASS3
    Fprintf(os, "CLASS=");
    PrintClassPath(os, cd);

    // Print the association classes:
    if (cd->flags & MI_FLAG_ASSOCIATION)
    {
        Fprintf(os, "{");

        MI_Uint32 n = 0;

        for (MI_Uint32 i = 0; i < cd->numProperties; i++)
        {
            const MI_PropertyDecl* pd = cd->properties[i];

            if (pd->type == MI_REFERENCE && pd->className)
            {
                const MI_ClassDecl* rcd = FindClassDecl(sd, pd->className);

                if (!rcd)
                    err(ZT("failed to find class: %Z"), zcs(pd->className));

                if (n != 0)
                    Fprintf(os, ",");
                PrintClassPath(os, rcd);
                n++;
            }
        }

        Fprintf(os, "}");
    }
    Fprintf(os, "\n");
}

static MI_Module* LoadModule(const char* path)
{
    const char FUNC[] = "MI_Main";

    // Load the library:
    void* handle = Lib_Open(path);
    if (!handle)
    {
        char* msg = Lib_Err();
        err(ZT("failed to load library: %s\n"), scs(msg));
    }

    // Load the MI_Main() entry point:
    void* sym = Lib_Sym(handle, FUNC);
    if (!sym)
    {
        err(ZT("failed to find symbol '%s' in library '%s'\n"),
            scs(FUNC), scs(path));
    }

    // Call MI_Main() to get MI_Module object.
    MainProc main = (MainProc)sym;
    MI_Module* module = (*main)(NULL);
    if (!module)
    {
        err(ZT("%s:%s() failed"), scs(path), scs(FUNC));
    }

    // Check character size:
    if (module->charSize != sizeof(ZChar))
    {
        err(ZT("provider char size (%u) does not match %s char size (%u)"),
            module->charSize, scs(arg0), (int)sizeof(ZChar));
    }

    return module;
}

static void GenRegFile(
    FILE* os,
    int argc,
    const char** argv,
    const string& baseName,
    MI_Module* module,
    const Options& opts)
{
    // Get schemaDecl:
    MI_SchemaDecl* sd = module->schemaDecl;
    if (!sd)
    {
        err(ZT("MI_Module.schemaDecl is null"));
    }

    // Generate header line.
    Fprintf(os, "# ");
    for (int i = 0; i < argc; i++)
    {
        string arg;

        if (i == 0)
            arg = BaseName(argv[i]);
        else
            arg = argv[i];

        Fprintf(os, "%s", scs(arg.c_str()));
        if (i + 1 != argc)
            Fprintf(os, " ");
    }
    Fprintf(os, "\n");

    // Write library name:
    Fprintf(os, "LIBRARY=%s\n", scs(baseName.c_str()));

    // Hosting
    if (!opts.hosting.empty())
    {
        Fprintf(os, "HOSTING=%s\n", scs(opts.hosting.c_str()));
    }

    // Find providers:
    for (MI_Uint32 i = 0; i < sd->numClassDecls; i++)
    {
        const MI_ClassDecl* cd = sd->classDecls[i];

        if (!cd)
            err(ZT("null classDecl element"));

        // If it has a provider, print the class line.
        if (cd->providerFT)
        {
            GenClassLine(os, sd, cd);
        }
    }
}

static bool Inhale(const char* path, vector<char>& data)
{
    FILE* is = Fopen(path, "r");

    if (!is)
        return false;

    size_t n;
    char buf[4096];

    while ((n = fread(buf, 1, sizeof(buf), is)) != 0)
    {
        data.insert(data.end(), buf, buf + n);
    }

    data.push_back('\0');

    fclose(is);

    return true;
}

static ZString _ToZString(const char* str)
{
    ZString r;

    while (*str != '\0')
        r += ZChar(*str++);

    return r;
}

static void _RefreshServer()
{
#ifndef _MSC_VER
    mi::Client cl;
    const MI_Uint64 TIMEOUT = 500 * 1000;

    const char* sockfile = GetPath(ID_SOCKETFILE);

    if (!sockfile)
    {
        err(ZT("GetPath(ID_SOCKETFILE) failed"));
    }

    ZString socketFile = _ToZString(GetPath(ID_SOCKETFILE));

    if (cl.Connect(socketFile.c_str(), MI_T(""), MI_T(""), TIMEOUT))
    {
        // reload server's config
        pid_t child = fork();
        if (child == 0)
        {
            execl(GetPath(ID_SERVERPROGRAM), GetPath(ID_SERVERPROGRAM), "-r", NULL);
            exit(1); // never get here... if everything is ok
        }
        else if (child > 0)
        {
            /* wait for child */
            int s;
            waitpid(child, &s, 0);
        }

        // wait until it restarts
        cl.NoOp(TIMEOUT);

        // wait for server to restart
        for (int i = 0; i < 30; i++)
        {
            if (cl.Connect(socketFile.c_str(), MI_T(""), MI_T(""), TIMEOUT))
                break;

            Time_Sleep(50);
        }
    }
#else
    /* TODO: Now do we notify the server that the configuration has changed on Windows? */
#endif
}

int MI_MAIN_CALL main(int argc, const char** argv)
{
    arg0 = argv[0];

    // Get --destdir command-line option.
    GetCommandLineDestDirOption(&argc, argv);

    // Get command-line options.
    Options opts;
    GetCommandLineOptions(argc, argv, opts);

    if (opts.nsDirs.size() == 0)
    {
        string ns = CONFIG_NAMESPACE;

        for (size_t i = 0; i < ns.size(); i++)
        {
            if (ns[i] == '/')
                ns[i] = NAMESPACE_SEPARATOR;
        }

        ns = string(GetPath(ID_REGISTERDIR)) + string("/") + ns;
        opts.nsDirs.push_back(ns);
    }

    // Check arguments.
    if (opts.help)
    {
        Fzprintf(stderr, USAGE, arg0);
        exit(1);
    }

    // Check number of arguments.
    if (argc != 2)
    {
        Fzprintf(stderr, ZT("Usage: %s PROVIDERLIBRARY\n"), scs(arg0));
        Fzprintf(stderr, ZT("Try '%s --help' for help\n\n"), scs(arg0));
        exit(1);
    }

    // Check that namespace directories are writable.
    for (size_t i = 0; i < opts.nsDirs.size(); i++)
    {
        const string path = opts.nsDirs[i];

        if (!Isdir(path.c_str()))
            err(ZT("no such namespace directory: %s"), scs(path.c_str()));

        if (access(path.c_str(), W_OK) != 0)
            err(ZT("namespace directory is not writable: %s"),
                scs(path.c_str()));
    }

#ifdef CONFIG_OS_HPUX
    // HP is the only platform that locks loaded binary files
    // so if provider is already loaded unlink/copy will fail
    // force server to unload all providers before copying
    _RefreshServer();
#endif

    {

#ifndef _MSC_VER
        vector<char> data1;

        if (!Inhale(argv[1], data1))
            err(ZT("cannot read provider library: %s"), scs(argv[1]));
#endif

        string path = GetPath(ID_PROVIDERDIR);
        path += "/";
        path += Basename(argv[1]);

#ifndef _MSC_VER
        if (opts.devmode)
        {
            if (argv[1][0] != '/')
            {
                err(ZT("expected absolute path: '%s'"), scs(argv[1]));
            }

            unlink(path.c_str());

            if (symlink(argv[1], path.c_str()) != 0)
            {
                err(ZT("failed to symlink '%s' to '%s'"),
                    scs(argv[1]), scs(path.c_str()));
            }
        }
        else
        {
#endif
            if (File_Copy(argv[1], path.c_str()) != 0)
                err(ZT("failed to copy '%s' to '%s'"),
                    scs(argv[1]), scs(path.c_str()));

#ifndef _MSC_VER
            // set mod explicitly
            // w by owner only; RX for all.
            chmod(path.c_str(),
                S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
#endif

            Zprintf(ZT("Created %s\n"), scs(path.c_str()));
#ifndef _MSC_VER
        }
#endif
    }

    // Load module:
    MI_Module* module = LoadModule(argv[1]);
    if (!module)
        err(ZT("failed to load provider library: %s"), scs(argv[1]));

    // Generate .reg file in each namespace directory:
    for (size_t i = 0; i < opts.nsDirs.size(); i++)
    {
        // Open output file (using basename of library):
        string baseLibName = BaseLibName(argv[1]);
        string regFileName = baseLibName + ".reg";

        string path = opts.nsDirs[i];
        path += "/";
        path += regFileName;

        FILE* os = fopen(path.c_str(), "wb");

        if (os == NULL)
        {
            err(ZT("failed to open: %s"), scs(path.c_str()));
            exit(1);
        }

        // Generate the registration file.
        GenRegFile(os, argc, argv, baseLibName, module, opts);

        Zprintf(ZT("Created %s\n"), scs(path.c_str()));

        fclose(os);
    }

    // ask server to re-read configuration
    _RefreshServer();

    return 0;
}
