/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <common.h>
#include <string>
#include <vector>
#include <map>
#include <pal/shlib.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <base/omigetopt.h>
#include <base/paths.h>
#include <pal/dir.h>
#include <pal/format.h>
#include <pal/file.h>
#include <pal/sleep.h>
#include <base/naming.h>
#include <base/env.h>
#include <base/conf.h>
#ifndef _MSC_VER
#include <dlfcn.h>
#include <sys/wait.h>
#endif
#include <omiclient/client.h>
#include <fstream>

#if defined(CONFIG_ENABLE_WCHAR)
typedef std::wstring ZString;
#else
typedef std::string ZString;
#endif

using namespace std;

#define REG_INDICATION_CLASS "INDICATIONCLASS"

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
    -o, --hosting HOSTING       Use given hosting mode (@requestor@,@inproc@,@requestor-shell@,<user>).\n\
    -i, --instancelifetime LT   Changes default lifetime of instances created from\n\
                                the MI_Context. Default is until destroyed by the\n\
                                provider by calling MI_Instance_Delete or\n\
                                MI_Instance_Destruct, but overridable by setting LT to\n\
                                CONTEXT such that it will automatically get deleted when\n\
                                the MI_Context gets destroyed after the operation.\n\
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


char const* const BASE_OPTS[] =
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
    "-i:",
    "--instancelifetime:",
    "--registerdir:",
    "--providerdir:",
};


void AppendBaseOpts (
    std::vector<char const*>* pOptionsOut)
{
    pOptionsOut->insert (
        pOptionsOut->begin (),
        BASE_OPTS, BASE_OPTS + sizeof (BASE_OPTS) / sizeof (char const*));
}


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
    Ftprintf(stderr, ZT("%s: "), scs(arg0));

    va_list ap;
    va_start(ap, fmt);
    Vftprintf(stderr, fmt, ap);
    va_end(ap);

    Ftprintf(stderr, ZT("\n"));
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
    bool instancelifetime;
    vector<string> nsDirs;
    string interpreter;
    string startup;

    Options() : help(false), devmode(false), instancelifetime(false)
    {
    }
};


struct DefaultStartup
{
    std::string def;
    std::string startup;
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

static void GetCommandLineOptions( 
    int& argc, 
    const char**& argv,
    const char** opts,
    std::map<std::string, DefaultStartup> const& scriptMap,
    Options& options)
{
    GetOptState state = GETOPTSTATE_INITIALIZER;

    /* For each argument */
    for (;;)
    {
        int r = GetOpt(&argc, (const char**)argv, opts, &state);

        std::map<std::string, DefaultStartup>::const_iterator scriptPos;

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
            Tprintf(ZT("%s: %S\n"), scs(arg0),
                tcs(CONFIG_PRODUCT L"-" CONFIG_VERSION L" - " CONFIG_DATE));
#else
            Tprintf(ZT("%s: %s\n"), scs(arg0),
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

            ns = string(OMI_GetPath(ID_REGISTERDIR)) + string("/") + ns;
            options.nsDirs.push_back(ns);
        }
        else if (strcmp(state.opt, "-o") == 0 || 
            strcmp(state.opt, "--hosting") == 0)
        {
            options.hosting = state.arg;
        }
        else if (strcmp(state.opt, "-i") == 0 ||
            strcmp(state.opt, "--instancelifetime") == 0)
        {
            if (Strcasecmp(state.arg, "context") == 0)
            {
                options.instancelifetime = true;
            }
        }
        else if (strncmp(state.opt, "--", 2) == 0 && IsNickname(state.opt+2))
        {
            if (SetPathFromNickname(state.opt+2, state.arg) != 0)
                err(ZT("SetPathFromNickname() failed"));
        }
        else if (scriptMap.end () != (scriptPos = scriptMap.find (state.opt)))
        {
            // need to check for argument, else use default.
            options.interpreter =
                state.arg != NULL ? state.arg : scriptPos->second.def;
            options.startup = scriptPos->second.startup;
        }
    }
}

typedef MI_Module* (*MainProc)(MI_Server* server);

typedef MI_Module* (*StartProc)(
    MI_Server* const server,
    char const* const interpreter,
    char const* const startup,
    char const* const moduleName);

static string BaseName(const string& str)
{
    const char* start = strrchr(str.c_str(), '/');

    if (start)
        start++;
    else
        start = str.c_str();

    return string(start);
}

static string BaseLibName(const string& str)
{
    const char* start = strrchr(str.c_str(), '/');

    if (start)
        start++;
    else
        start = str.c_str();

    if (strncmp(start, "lib", 3) == 0)
        start += 3;

    const char* p = start;

    while (*p && *p != '.')
        p++;

    return string(start, p - start);
}

static void PrintClassPath(FILE* os, const MI_ClassDecl* cd)
{
    for (const MI_ClassDecl* p = cd; p; p = p->superClassDecl)
    {
        if (p != cd)
            Fprintf(os, ":");
        Fprintf(os, "%T", p->name);        
    }
}

static const MI_ClassDecl* FindClassDecl(
    const MI_SchemaDecl* sd, 
    const ZChar* className)
{
    MI_Uint32 hash = Hash(className);
    for (MI_Uint32 i = 0; i < sd->numClassDecls; i++)
    {
        const MI_ClassDecl* p = sd->classDecls[i];

        if (hash == p->code && Tcscmp(p->name, className) == 0)
            return p;
    }

    return 0;
}

static bool IsASuperClass(
    const MI_SchemaDecl* sd, 
    const ZChar* className)
{
    MI_Uint32 hash = Hash(className);
    for (MI_Uint32 i = 0; i < sd->numClassDecls; i++)
    {
        const MI_ClassDecl* p = sd->classDecls[i];

        // Even if we remote the following check code will work fine and not much impact on performance.
        if (hash == p->code && Tcscmp(p->name, className) == 0)
            continue;

        for(p = p->superClassDecl; p; p = p->superClassDecl)
        {
            if(hash == p->code && Tcscmp(p->name, className) == 0)
                return true;
        }
    }

    return false;
}

static void GenClassLine(
    FILE* os, 
    const MI_SchemaDecl* sd, 
    const MI_ClassDecl* cd)
{
    // Print the class path: CLASS1.CLASS2.CLASS3
    PrintClassPath(os, cd);

    // Print the association classes:
    if (cd->flags & MI_FLAG_ASSOCIATION)
    {
        const MI_ClassDecl* rcd1 = NULL;
        const MI_ClassDecl* rcd2 = NULL;
        for (MI_Uint32 i = 0; i < cd->numProperties; i++)
        {
            const MI_PropertyDecl* pd = cd->properties[i];

            if (pd->type == MI_REFERENCE && pd->className)
            {
                const MI_ClassDecl* rcd = FindClassDecl(sd, pd->className);

                if (!rcd)
                    err(PAL_T("failed to find class: %T"), tcs(pd->className));

                if (!rcd1)
                    rcd1 = rcd;
                else if (!rcd2)
                    rcd2 = rcd;
                else
                    err(PAL_T("invalid assocation class: %T, which has more than two reference properties"), tcs(cd->name));
            }
        }

        if (!rcd2)
            err(PAL_T("invalid assocation class: %T, which has less than two reference properties"), tcs(cd->name));

        Fprintf(os, "{");
        PrintClassPath(os, rcd1);
        Fprintf(os, ",");
        PrintClassPath(os, rcd2);

        Fprintf(os, "}");
    }
    Fprintf(os, "\n");
}

static MI_Module* LoadModule(const char* path)
{
    const char FUNC[] = "MI_Main";
    TChar Tpath[PAL_MAX_PATH_SIZE];

    if (TcsStrlcpy(Tpath, path, PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
        err(ZT("failed to load library: %s\n"), scs(path));

    // Load the library:
    Shlib* handle = Shlib_Open(Tpath);
    if (!handle)
    {
        TChar* msg = Shlib_Err();
        err(ZT("failed to load library: %T\n"), tcs(msg));
    }

    // Load the MI_Main() entry point:
    void* sym = Shlib_Sym(handle, FUNC);
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
        err(ZT("Char size required for provider (%u) different from OMI server char size (%u), see --enable-wchar in omi configuration help"), 
            module->charSize, (int)sizeof(ZChar));
    }

    // Check version
    if (module->version > MI_VERSION)
    {
        MI_Uint32 v =  module->version;
        err(ZT("provider version (%d.%d.%d) newer than server version (%d.%d.%d), which is not supported"),
            MI_VERSION_GET_MAJOR(v), MI_VERSION_GET_MINOR(v), MI_VERSION_GET_REVISION(v), MI_MAJOR, MI_MINOR, MI_REVISION);
    }

    return module;
}

static MI_Module* LoadModuleFromScript(
    const char* const interpreter,
    const char* const startup,
    const char* const moduleName)
{
    const char START[] = "Start";
    const char PROVIDER[] = "libOMIScriptProvider.so";

    // load the script provider library
    Shlib* handle = Shlib_Open(PROVIDER);
    if (!handle)
    {
        TChar* msg = Shlib_Err();
        err(ZT("failed to load %s: %T\n"), scs(PROVIDER), tcs(msg));
    }

    // Load the entry point:
    void* sym = Shlib_Sym(handle, START);
    if (!sym)
    {
        err(ZT("failed to find symbol '%s' in %s\n"), 
            scs(START), scs(PROVIDER));
    }

    // Call Start to get MI_Module object.
    StartProc start = reinterpret_cast<StartProc>(sym);
    MI_Module* module = start(NULL, interpreter, startup, moduleName);
    if (!module)
    {
        err(ZT("%s:%s:%s:%s:%s(): failed"),
            scs(PROVIDER), scs(START), scs(interpreter), scs(startup),
            scs(moduleName));
    }
    
    return module;
}

static ZString _ToZString(const char* str)
{
    ZString r;

    while (*str)
        r += ZChar(*str++);

    return r;
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
    string arg;
    for (int i = 0; i < argc; i++)
    {
        if (i == 0)
            arg = BaseName(argv[i]);
        else
            arg = argv[i];

        Fprintf(os, "%s", scs(arg.c_str()));
        if (i + 1 != argc)
            Fprintf(os, " ");
    }
    Fprintf(os, "\n");

    if (!opts.interpreter.empty ())
    {
        Fprintf (os, "INTERPRETER=%s\n", scs (opts.interpreter.c_str ()));
        Fprintf (os, "STARTUP=%s\n", scs (opts.startup.c_str ()));
    }

    // Write library name:
    Fprintf(os, "LIBRARY=%s\n",
            scs(opts.interpreter.empty () ? baseName.c_str() : arg.c_str ()));

    // Hosting
    if (!opts.hosting.empty())
    {
        Fprintf(os, "HOSTING=%s\n", scs(opts.hosting.c_str()));
    }
    if (opts.instancelifetime)
    {
        Fprintf(os, "INSTANCELIFETIME=CONTEXT\n");
    }

    // Find providers:
    for (MI_Uint32 i = 0; i < sd->numClassDecls; i++)
    {
        const MI_ClassDecl* cd = sd->classDecls[i];

        if (!cd)
            err(ZT("null classDecl element"));

        if (cd->providerFT)
        {
            if (cd->flags & MI_FLAG_INDICATION)
            {
                Fprintf(os, REG_INDICATION_CLASS);
                // If it is a provider implemented indication class, print the class line
                Fprintf(os, "=");
                GenClassLine(os, sd, cd);
            }
            else
            {
                // If it is a provider implemented class, print the class line as CLASS=class1:class2:class3
                Fprintf(os, "CLASS=");
                GenClassLine(os, sd, cd);
            }
        }
        else
        {
            // Noting down all non implemented classes which are not a super class.
            // With this all the classes present in a provider either implemented or not implemeted will be listed in .reg file.
            // EXTRACLASS=class1:class2:class3

            // Checking if the class is a super class of any other class (implemented or not-implemented)
            if(! IsASuperClass(sd, cd->name))
            {
                Fprintf(os, "EXTRACLASS=");
                GenClassLine(os, sd, cd);
            }
        }
    }
}

static bool Inhale(const char* path, vector<char>& data)
{
    bool Ret = false;
    std::ifstream inputFile(path, std::ios::in | std::ios::binary);

    if (inputFile.is_open())
    {
        // get length of file:
        int Length = 0;

        // Ask the operating system how big the file is.  It should have
        // the information in cache, since we just opened it.
        struct stat fileStat;
        if (0 == stat(path, &fileStat))
        {
            Length = fileStat.st_size;
            data.resize(Length+1, '\0');

            // read data as a block:
            inputFile.read (&data[0], Length);
            inputFile.close();
    
            data[Length] = '\0';
    
            Ret = true;
        }
    }

    return Ret;
}

static void _RefreshServer()
{
#ifndef _MSC_VER
    mi::Client cl;
    const MI_Uint64 TIMEOUT = 500 * 1000;

    const char* sockfile = OMI_GetPath(ID_SOCKETFILE);

    if (!sockfile)
    {
        err(ZT("OMI_GetPath(ID_SOCKETFILE) failed"));
    }

    ZString socketFile = _ToZString(OMI_GetPath(ID_SOCKETFILE));

    if (cl.Connect(socketFile.c_str(), MI_T(""), MI_T(""), TIMEOUT))
    {
        // reload server's config
        pid_t child = fork();
        if (!child)
        {
            execl(OMI_GetPath(ID_SERVERPROGRAM), OMI_GetPath(ID_SERVERPROGRAM), "-r",
                NULL );
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
        for ( int i = 0; i < 30; i++ )
        {
            if (cl.Connect(socketFile.c_str(), MI_T(""), MI_T(""), TIMEOUT))
                break;

            Sleep_Milliseconds(50);
        }
    }
#endif
}


static int FindConfigFile(
    _Pre_writable_size_(PAL_MAX_PATH_SIZE) char path[PAL_MAX_PATH_SIZE])
{
    /* Look in current directory */
    {
        Strlcpy(path, "./.omiregrc", PAL_MAX_PATH_SIZE);

        if (access(path, R_OK) == 0)
            return 0;
    }

    /* Look in HOME directory */
    char* home = Dupenv("HOME");
    if (home)
    {
        Strlcpy(path, home, PAL_MAX_PATH_SIZE);
        Strlcat(path, "/.omiregrc", PAL_MAX_PATH_SIZE);

        if (access(path, R_OK) == 0)
        {
            PAL_Free(home);
            return 0;
        }
        PAL_Free(home);
    }

    /* Look in system config directory */
    {
        Strlcpy(path, OMI_GetPath(ID_DESTDIR), PAL_MAX_PATH_SIZE);
        Strlcat(path, "/", PAL_MAX_PATH_SIZE);
        Strlcat(path, OMI_GetPath(ID_SYSCONFDIR), PAL_MAX_PATH_SIZE);
        Strlcat(path, "/omireg.conf", PAL_MAX_PATH_SIZE);

        if (access(path, R_OK) == 0)
            return 0;
    }

    /* Not found */
    return -1;
}


// script = --Python:python2.7:client.py
int ParseTagDefaultStartup (
    char const* value,
    std::string* pTagOut,
    std::string* pDefaultOut,
    std::string* pStartupOut)
{
    int rval = EXIT_SUCCESS;
    char const* tok0 = strchr (value, ':');
    if (NULL != tok0 &&
        tok0 != value &&
        tok0 + 1 != '\0')
    {
        char const* tok1 = strchr (tok0 + 1, ':');
        if (NULL != tok1 &&
            tok1 != tok0 + 1 &&
            tok1 + 1 != '\0')
        {
            pTagOut->assign (value, tok0 - value);
            ++tok0;
            pDefaultOut->assign (tok0, tok1 - tok0);
            ++tok1;
            pStartupOut->assign (tok1, strlen (tok1));
        }
        else
        {
            rval = EXIT_FAILURE;
        }
    }
    else
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


static void _GetConfigFileOptions(
    std::map<std::string, DefaultStartup>* pScriptMapOut,
    std::vector<std::string> *pCmdOptsOut,
    std::vector<char const*>* pCmdlnOptsOut)
{
    char path[PAL_MAX_PATH_SIZE];
    Conf* conf;

    /* Form the configuration file path */
    if (FindConfigFile(path) != 0)
        err("failed to find configuration file");

    /* Open the configuration file */
    conf = Conf_Open(path);
    if (!conf)
        err("failed to open configuration file: %s", path);

    /* For each key=value pair in configuration file */
    for (;;)
    {
        const char* key;
        const char* value;
        int r = Conf_Read(conf, &key, &value);

        if (r == -1)
            err("%s: %s\n", path, Conf_Error(conf));

        if (r == 1)
            break;

        if (strcmp(key, "script") == 0)
        {
            std::string opt;
            DefaultStartup args;

            if (EXIT_SUCCESS ==
                ParseTagDefaultStartup (
                    value, &opt, &(args.def), &(args.startup)))
            {
                std::pair<std::map<std::string, DefaultStartup>::iterator,
                          bool> r = pScriptMapOut->insert (std::make_pair (opt, args));
                if (r.second)
                {
                    pCmdOptsOut->push_back (r.first->first + '?');
                    pCmdlnOptsOut->push_back (pCmdOptsOut->back ().c_str ());
                }
                else
                {
                    err("%s(%u): duplicate key: %s",
                        path, Conf_Line(conf), opt.c_str ());
                }
            }
        }
        else
            err("%s(%u): unknown key: %s", path, Conf_Line(conf), key);
    }

    /* Close configuration file */
    Conf_Close(conf);
}


int MI_MAIN_CALL main(int argc, const char** argv)
{
    arg0 = argv[0];

    // Get --destdir command-line option.
    GetCommandLineDestDirOption(&argc, argv);

    std::vector<char const*> cmdlnOpts;
    AppendBaseOpts (&cmdlnOpts);

    std::map<std::string, DefaultStartup> scriptMap;
    std::vector<std::string> cmdOpts;

    _GetConfigFileOptions (&scriptMap, &cmdOpts, &cmdlnOpts);

    cmdlnOpts.push_back (NULL);

    // Get command-line options.
    Options opts;

    GetCommandLineOptions(argc, argv, &(cmdlnOpts[0]), scriptMap, opts);

    if (opts.nsDirs.size() == 0)
    {
        string ns = CONFIG_NAMESPACE;

        for (size_t i = 0; i < ns.size(); i++)
        {
            if (ns[i] == '/')
                ns[i] = NAMESPACE_SEPARATOR;
        }

        ns = string(OMI_GetPath(ID_REGISTERDIR)) + string("/") + ns;
        opts.nsDirs.push_back(ns);
    }

    // Check arguments.
    if (opts.help)
    {
        Ftprintf(stderr, USAGE, arg0);
        exit(1);
    }
    
    // Check number of arguments.
    if (argc != 2)
    {
        Ftprintf(stderr, ZT("Usage: %s PROVIDERLIBRARY\n"), scs(arg0));
        Ftprintf(stderr, ZT("Try '%s --help' for help\n\n"), scs(arg0));
        exit(1);
    }

    // Check that namespace directories are writable.
    for (size_t i = 0; i < opts.nsDirs.size(); i++)
    {
        const string path = opts.nsDirs[i];

        if (!Isdir(path.c_str()))
        {
            if (Mkdir(path.c_str(), 0755) != 0)
            {
                err(ZT("Failed to create namespace directory: %s "), scs(path.c_str()));
            }
            else
            {
                Tprintf(ZT("Created namespace directory: %s\n"), scs(path.c_str()));
            }
        }

        if (access(path.c_str(), W_OK) != 0)
            err(ZT("namespace directory is not writable: %s"), 
                scs(path.c_str()));
    }

    char argv1[PAL_MAX_PATH_SIZE];
    Strlcpy(argv1, argv[1], PAL_MAX_PATH_SIZE);
#ifdef CONFIG_OS_WINDOWS
    // Translate backward to forward slashes in the argv[1]       
    char* p;

    for (p = argv1; *p; p++)
    {
        if (*p == '\\')
            *p = '/';
    }
#endif


#ifdef CONFIG_OS_HPUX
    // HP is the only platform that locks loaded binary files 
    // so if provider is already loaded unlink/copy will fail 
    // force server to unload all providers before copying
    _RefreshServer();
#endif

    {
        if (opts.interpreter.empty ())
        {

#ifndef _MSC_VER
            vector<char> data1;
        
            if (!Inhale(argv1, data1))
                err(ZT("cannot read provider library: %s"), scs(argv1));
#endif

            string path = OMI_GetPath(ID_PROVIDERDIR);
            path += "/";
            path += Basename(argv1);

#ifndef _MSC_VER
            if (opts.devmode)
            {
                if (argv[1][0] != '/')
                {
                    err(ZT("expected absolute path: '%s'"), scs(argv1));
                }
                
                unlink(path.c_str());
                
                if (symlink(argv1, path.c_str()) != 0)
                {
                    err(ZT("failed to symlink '%s' to '%s'"), 
                        scs(argv1), scs(path.c_str()));
                }
            }
            else
            {
#endif
                if (File_Copy(argv1, path.c_str()) != 0)
                    err(ZT("failed to copy '%s' to '%s'"), 
                        scs(argv1), scs(path.c_str()));

#ifndef _MSC_VER
                // set mod explicitly
                // w by owner only; RX for all.
                chmod(path.c_str(), 
                      S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);
#endif

                Tprintf(ZT("Created %s\n"), scs(path.c_str()));
#ifndef _MSC_VER
            }
#endif
        }
    }

    // Load module:
    MI_Module* module = NULL;

    if (opts.interpreter.empty ())
    {
        module = LoadModule(argv1);
    }
    else
    {
        module = LoadModuleFromScript (opts.interpreter.c_str(),
                                       opts.startup.c_str (), argv1);
    }

    if (!module)
        err(ZT("failed to load provider library: %s"), scs(argv1));

    // Generate .reg file in each namespace directory:
    for (size_t i = 0; i < opts.nsDirs.size(); i++)
    {
        // Open output file (using basename of library):
        string baseLibName = BaseLibName(argv1);
        string regFileName = baseLibName + ".reg";

        string path = opts.nsDirs[i];
        path += "/";
        path += regFileName;

        FILE* os = fopen(path.c_str(), "wb");

        if (!os)
            err(ZT("failed to open: %s"), scs(path.c_str()));

        // Generate the registration file.
        GenRegFile(os, argc, argv, baseLibName, module, opts);

        Tprintf(ZT("Created %s\n"), scs(path.c_str()));

        fclose(os);
    }

    // ask server to re-read configuration
    _RefreshServer();

    return 0;
}
