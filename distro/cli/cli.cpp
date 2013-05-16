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

#include <string>
#include <climits>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <string>

#include <omiclient/client.h>
#include <base/result.h>
#include <wql/wql.h>
#include <base/strings.h>
#include <base/paths.h>
#include <base/conf.h>
#include <base/env.h>
#include <base/getopt.h>
#include <io/io.h>
#include <base/time.h>

#if defined(CONFIG_ENABLE_WCHAR)
typedef std::wstring ZString;
#else
typedef std::string ZString;
#endif

// #define ENABLE_TRACING
// #define TRACING_LEVEL 4
#include <logging.h>

using namespace mi;
using namespace std;

const char* arg0;

struct Options
{
    bool help;
    bool quiet;
    bool summary;
    bool suppressResults;
    bool trace;
    bool shallow;
    int repeat;
    String assocClass;
    String resultClass;
    String role;
    String resultRole;
    String user;
    String password;
    Uint64 timeOut;
    unsigned int httpport;
    unsigned int httpsport;
    bool nulls;
    String querylang;
    String queryexpr;

    Options()
    {
        Clear();
    }

    void Clear()
    {
        help = false;
        quiet = false;
        summary = false;
        suppressResults = false;
        trace = false;
        shallow = false;
        repeat = 1;
        assocClass.Clear();
        resultClass.Clear();
        role.Clear();
        resultRole.Clear();
        user.Clear();
        password.Clear();
        timeOut = 90 * 1000 * 1000;
        httpport = CONFIG_HTTPPORT;
        httpsport = CONFIG_HTTPSPORT;
        nulls = false;
        querylang.Clear();
        queryexpr.Clear();
    }
};

static Options opts;

static FILE* sout = stdout;
static FILE* serr = stderr;

static void err(const ZChar* fmt, ...)
{
    Fzprintf(serr, ZT("%s: "), scs(arg0));

    va_list ap;
    va_start(ap, fmt);
    Vfzprintf(serr, fmt, ap);
    va_end(ap);

    Fzprintf(serr, ZT("\n"));
}

static String MakeString(const char* str)
{
    String s;
    while (*str)
        s += ZChar(*str++);

    return s;
}

static std::string ZToStr(const ZChar* str)
{
    std::string r;

    while (*str)
        r += char(*str++);

    return r;
}

static int FindConfigFile(_Pre_writable_size_(MAX_PATH_SIZE) char path[MAX_PATH_SIZE])
{
    /* Look in current directory */
    {
        Strlcpy(path, "./.omiclirc", MAX_PATH_SIZE);

        if (access(path, R_OK) == 0)
            return 0;
    }

    /* Look in HOME directory */
    char* home = Dupenv("HOME");
    if (home)
    {
        Strlcpy(path, home, MAX_PATH_SIZE);
        Strlcat(path, "/.omiclirc", MAX_PATH_SIZE);

        if (access(path, R_OK) == 0)
        {
            free(home);
            return 0;
        }
        free(home);
    }

    /* Look in system config directory */
    {
        Strlcpy(path, GetPath(ID_SYSCONFDIR), MAX_PATH_SIZE);
        Strlcat(path, "/omicli.conf", MAX_PATH_SIZE);

        if (access(path, R_OK) == 0)
            return 0;
    }

    /* Not found */
    return -1;
}

static int GetConfigFileOptions()
{
    char path[MAX_PATH_SIZE];
    Conf* conf;

    /* Form the configuration file path (silently ignore if not found) */
    if (FindConfigFile(path) != 0)
        return 0;

    /* Open the configuration file */
    conf = Conf_Open(path);
    if (!conf)
    {
        err(ZT("failed to open configuration file: %s"), scs(path));
        return 1;
    }

    /* For each key=value pair in configuration file */
    for (;;)
    {
        const char* key;
        const char* value;
        int r = Conf_Read(conf, &key, &value);

        if (r == -1)
        {
            err(ZT("%s: %s\n"), scs(path), scs(Conf_Error(conf)));
            return 1;
        }

        if (r == 1)
            break;

        if (strcmp(key, "httpport") == 0)
        {
            char* end;
            unsigned long x = Strtoul(value, &end, 10);

            if (*end != '\0' || x > USHRT_MAX)
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path),
                    Conf_Line(conf), scs(key), scs(value));
                return 1;
            }

            opts.httpport = (unsigned short)x;
        }
        else if (strcmp(key, "httpsport") == 0)
        {
            char* end;
            unsigned long x = Strtoul(value, &end, 10);

            if (*end != '\0' || x > USHRT_MAX)
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path),
                    Conf_Line(conf), scs(key), scs(value));
                return 1;
            }

            opts.httpsport = (unsigned short)x;
        }
        else if (strcmp(key, "trace") == 0)
        {
            if (Strcasecmp(value, "true") == 0)
            {
                opts.trace = MI_TRUE;
            }
            else if (Strcasecmp(value, "false") == 0)
            {
                opts.trace = MI_FALSE;
            }
            else
            {
                err(ZT("%s(%u): invalid value for '%s': %s"), scs(path),
                    Conf_Line(conf), scs(key), scs(value));
                return 1;
            }
        }
        else if (IsNickname(key))
        {
            if (SetPathFromNickname(key, value) != 0)
            {
                err(ZT("SetPathFromNickname() failed"));
                return 1;
            }
        }
        else
        {
            err(ZT("%s(%u): unknown key: %s"), scs(path), Conf_Line(conf),
                scs(key));
            return 1;
        }
    }

    /* Close configuration file */
    Conf_Close(conf);
    return 0;
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

static int GetCommandLineOptions(
    int& argc,
    const char* argv[],
    Options& options)
{
    GetOptState state = GETOPTSTATE_INITIALIZER;
    const char* supportedOptions[] =
    {
        "-h",
        "-q",
        "-t",
        "-s",
        "-shallow",
        "-n",
        "-R:",
        "-ac:",
        "-rc:",
        "-r:",
        "-rr:",
        "-rc:",
        "-u:",
        "-p:",
        "-S",
        "--help",
        "--summary",
        "--prefix:",
        "--libdir:",
        "--bindir:",
        "--localstatedir:",
        "--sysconfdir:",
        "--providerdir:",
        "--certsdir:",
        "--rundir:",
        "--logdir:",
        "--pidfile:",
        "--logfile:",
        "--registerdir:",
        "--socketfile:",
        "--pemfile:",
        "--keyfile:",
        "--agentprogram:",
        "--serverprogram:",
        "--stdout:",
        "--stderr:",
        "--querylang:",
        "--queryexpr:",
        NULL,
    };

    for ( ; ; )
    {
        int r = GetOpt(&argc, argv, supportedOptions, &state);

        if (r == 1)
            break;

        if (r == -1)
        {
            Fzprintf(serr, ZT("error: %s\n"), scs(state.err));
            Fzprintf(serr, ZT("Try -h for help\n"));
            return 1;
        }

        if (strcmp(state.opt, "-h") == 0 || strcmp(state.opt, "--help") == 0)
        {
            options.help = true;
        }
        else if (strcmp(state.opt, "-q") == 0)
        {
            options.quiet = true;
        }
        else if (strcmp(state.opt, "-t") == 0)
        {
            options.trace = true;
        }
        else if (strcmp(state.opt, "-s") == 0)
        {
            options.suppressResults = true;
        }
        else if (strcmp(state.opt, "-shallow") == 0)
        {
            options.shallow = true;
        }
        else if (strcmp(state.opt, "-n") == 0)
        {
            options.nulls = true;
        }
        else if (strcmp(state.opt, "-R") == 0)
        {
            options.repeat = atoi(state.arg);

            if (options.repeat <= 0)
            {
                err(ZT("bad value for -R: %s"), scs(state.arg));
                return 1;
            }
        }
        else if (strcmp(state.opt, "-ac") == 0)
        {
            options.assocClass = MakeString(state.arg);
        }
        else if (strcmp(state.opt, "-rc") == 0)
        {
            options.resultClass = MakeString(state.arg);
        }
        else if (strcmp(state.opt, "-r") == 0)
        {
            options.role = MakeString(state.arg);
        }
        else if (strcmp(state.opt, "-rr") == 0)
        {
            options.resultRole = MakeString(state.arg);
        }
        else if (strcmp(state.opt, "-u") == 0)
        {
            options.user = MakeString(state.arg);
        }
        else if (strcmp(state.opt, "-p") == 0)
        {
            options.password = MakeString(state.arg);
        }
        else if (strcmp(state.opt, "--stdout") == 0)
        {
            FILE* os = Fopen(state.arg, "wb");

            if (!os)
                err(ZT("failed to open: %s"), scs(state.arg));

            sout = os;
        }
        else if (strcmp(state.opt, "--stderr") == 0)
        {
            FILE* os = Fopen(state.arg, "wb");

            if (!os)
                err(ZT("failed to open: %s"), scs(state.arg));

            serr = os;
        }
        else if (strcmp(state.opt, "--querylang") == 0)
        {
            options.querylang = MakeString(state.arg);
        }
        else if (strcmp(state.opt, "--queryexpr") == 0)
        {
            options.queryexpr = MakeString(state.arg);
        }
        else if (strcmp(state.opt, "--summary") == 0 ||
                 strcmp(state.opt, "-S") == 0)
        {
            options.summary = true;
        }
        else if (strncmp(state.opt, "--", 2) == 0 && IsNickname(state.opt+2))
        {
            if (SetPathFromNickname(state.opt+2, state.arg) != 0)
                err(ZT("SetPathFromNickname() failed"));
        }
    }

    return 0;
}

const ZChar USAGE[] = ZT("\
Usage: %s [OPTIONS] COMMAND ...\n\
\n\
This tool sends requests to the CIM server.\n\
\n\
OPTIONS:\n\
    -h, --help          Print this help message.\n\
    -q                  Operate quietly.\n\
    -t                  Enable diagnostic tracing.\n\
    -R N                Repeat command N times.\n\
    -shallow            Use shallow inheritance (see 'ei' command).\n\
    -ac CLASSNAME       Association class (see 'a' and 'r' commands).\n\
    -rc CLASSNAME       Result class (see 'a' command).\n\
    -r ROLE             Role (see 'a' and 'r' commands).\n\
    -rr ROLE            Result role (see 'a' command).\n\
    -n                  Show null properties.\n\
    -u USERNAME         Username.\n\
    -p PASSWORD         User's password.\n\
    -id                 Send identify request.\n\
    --socketfile PATH   Talk to the server server whose socket file resides\n\
                        at the location given by the path argument.\n\
    --httpport          Connect on this port instead of default.\n\
    --httpsport         Connect on this secure port instead of default.\n\
    --querylang         Query language (for 'ei' command).\n\
    --queryexpr         Query expression (for 'ei' command).\n\
\n\
COMMANDS:\n\
    noop\n\
        Perform a no-op operation.\n\
    gi NAMESPACE INSTANCENAME\n\
        Peform a CIM [g]et [i]nstance operation.\n\
    ci NAMESPACE NEWINSTANCE\n\
        Peform a CIM [c]create [i]nstance operation.\n\
    mi NAMESPACE MODIFIEDINSTANCE\n\
        Peform a CIM [m]odify [i]nstance operation.\n\
    di NAMESPACE INSTANCENAME\n\
        Peform a CIM [d]elete [i]nstance operation.\n\
    ei [-shallow] NAMESPACE CLASSNAME\n\
        Peform a CIM [e]numerate [i]nstances operation.\n\
    iv NAMESPACE INSTANCENAME METHODNAME PARAMETERS\n\
        Peform a CIM extrinisic method [i]nvocation operation.\n\
    a [-ac -rc -r -rr ] NAMESPACE INSTANCENAME\n\
        Perform a CIM [a]ssociator instances operation.\n\
    r [-ac -r] NAMESPACE INSTANCENAME (references)\n\
        Perform a CIM [r]eference instances operation.\n\
    enc INSTANCE\n\
        Attempt to encode and print the given instance representation.\n\
    wql NAMESPACE WQLQUERY\n\
        Peform a WQL query operation.\n\
\n");

// Find closing brach (assuming *p points to an opening brace).
static const char** FindClosingBrace(const char** p)
{
    int nesting = 1;

    if (strcmp(*p, "{") != 0)
        return NULL;

    p++;

    while (*p)
    {
        if (strcmp(*p, "{") == 0)
            nesting++;
        else if (strcmp(*p, "}") == 0)
            nesting--;

        p++;

        if (nesting == 0)
            return p;
    }

    return NULL;
}

// ATTN: support arrays.
static bool ArgsToInstance(
    const char**& p,
    const char** end,
    DInstance::MetaType metaType,
    bool key,
    DInstance& instanceOut)
{
    if (p == end)
        return false;

    // Consume opening brace:
    if (strcmp(*p++, "{") != 0)
        return false;

    if (p == end)
        return false;

    // Call the 'empty' constructor so that we can use placement operator.
    DInstance instance;

    if (metaType == DInstance::METHOD)
    {
        instance = DInstance(ZT("Parameters"), DInstance::METHOD);
    }
    else
    {
        instance = DInstance(MakeString(*p++), DInstance::CLASS);

        if (p == end)
            return false;
    }

    // Consume name/value pairs:
    for ( ; ; )
    {
        if (strcmp(*p, "}") == 0)
        {
            p++;
            break;
        }

        // Get name:
        String name = MakeString(*p++);

        if (p == end)
            return false;

        // Get value:
        if (strcmp(*p, "{") == 0)
        {
            const char** q = FindClosingBrace(p);

            if (!q || q == end)
                return false;

            // Recursively call to obtain reference or embedded instance.
            DInstance tmpInst;

            if (!ArgsToInstance(p, q, DInstance::CLASS, key, tmpInst))
                return false;

            if (!instance.AddInstance(name, tmpInst, false, key))
                return false;
        }
        else if (strcmp(*p, "[") == 0)
        {
            Array<String> array;
            Array<DInstance> instances;
            p++;

            // Find closing brace:
            while (*p && strcmp(*p, "]") != 0)
            {
                if (strcmp(*p, "{") == 0)
                {
                    const char** q = FindClosingBrace(p);

                    if (!q || q == end)
                        return false;

                    DInstance tmpInst;

                    if (!ArgsToInstance(p, q, DInstance::CLASS, key, tmpInst))
                        return false;

                    instances.PushBack(tmpInst);
                }
                else
                {
                    array.PushBack(MakeString(*p++));
                }
            }

            // Handle missing closing brace:
            if (p == end)
                return false;

            if (instances.GetSize())
            {
                if (!instance.AddInstanceA(name, instances, false, key))
                    return false;
            }
            else if (array.GetSize())
            {
                if (!instance.AddStringA(name, array, false, key))
                    return false;
            }

            p++;
        }
        else
        {
            // Get value:
            String value = MakeString(*p++);

            // Add property:
            if (!instance.AddString(name, value, false, key))
                return false;

            if (p == end)
                break;
        }
    }

    instanceOut = instance;
    return true;
}

static int NoOp(Client& client, int argc, const char* argv[])
{
    MI_UNUSED(argv);

    if (argc != 2)
    {
        Fzprintf(serr, ZT("Usage: %s noop\n\n"), scs(arg0));
        return 1;
    }

    if (!client.NoOp(opts.timeOut))
    {
        err(ZT("noop request failed"));
        return 1;
    }

    if (!opts.quiet)
        Fzprintf(sout, ZT("got noop response\n"));

    return 0;
}

static Uint32 s_numInstances = 0;
static Uint64 s_startTime;

static void PrintInstance(const DInstance& inst, bool nulls)
{
    inst.Print(sout, 0, nulls);
}

static void PrintSummary()
{
    Uint64 now;
    Time_Now(&now);
    Uint64 msec = (now - s_startTime) / 1000;
    double seconds = double(msec) / double(1000.0);

    Zprintf(ZT("number of instances: %u\n"), s_numInstances);
    Zprintf(ZT("seconds: %.3lf\n"), seconds);
    Zprintf(ZT("instances per second: %.3lf\n"), s_numInstances / seconds);
    Zprintf(ZT("\n"));
}

static int Encode(int argc, const char* argv[])
{
    if (argc < 3)
    {
        Fzprintf(serr, ZT("Usage: %s noop CLASSNAME KEYBINDING\n\n"), scs(arg0));
        return 1;
    }

    DInstance inst;
    argc -= 2;
    argv += 2;

    if (!ArgsToInstance(argv, argv + argc, DInstance::CLASS, false, inst))
    {
        err(ZT("invalid instance name specification"));
        return 1;
    }

    if (!opts.quiet)
    {
        PrintInstance(inst, opts.nulls);
    }

    s_numInstances++;

    return 0;
}

static MI_Result s_result;
static bool s_done;

static int EnumerateInstances(Client& client, int argc, const char* argv[])
{
    if (argc != 4)
    {
        Fzprintf(serr, ZT("Usage: %s ei NAMESPACE CLASSNAME\n\n"), scs(arg0));
        return 1;
    }

    // Default to WQL query language.
    if (opts.querylang.GetSize() && opts.queryexpr.GetSize() == 0)
    {
        opts.querylang = ZT("WQL");
    }

    // Reject if --querylang option present but not --queryexpr option.
    if (opts.querylang.GetSize() && opts.queryexpr.GetSize() == 0)
    {
        err(ZT("--querylang options requires --queryexpr option"));
        return 1;
    }

    const String nameSpace = MakeString(argv[2]);
    const String className = MakeString(argv[3]);
    Array<DInstance> instances;
    MI_Result result;
    Uint64 msgID = 0;

    s_result = MI_RESULT_OK;
    s_done = false;

    if (!client.EnumerateInstancesAsync(nameSpace, className, !opts.shallow,
        opts.querylang, opts.queryexpr,  msgID))
    {
        err(ZT("communication failed (cannot connect/initiate command)"));
        return 1;
    }

    Uint64 endTime, now;

    if (Time_Now(&now) != MI_RESULT_OK)
        return 3;

    endTime = now + opts.timeOut;

    for ( ; !s_done && endTime >= now; )
    {
        client.Run(20000);

        if (Time_Now(&now) != MI_RESULT_OK)
            break;
    }

    if (!s_done)
    {
        err(ZT("communication failed (timeout)"));
        return 1;
    }

    result = s_result;

    if (result != MI_RESULT_OK)
    {
        return 2;
    }

    return 0;
}

static int Query(Client& client, int argc, const char* argv[])
{
    // Check arguments
    if (argc != 4)
    {
        Fzprintf(serr, ZT("Usage: %s wql NAMESPACE QUERY\n\n"), scs(arg0));
        return 1;
    }

    // Extract query options.
    opts.querylang = ZT("WQL");
    opts.queryexpr = MakeString(argv[3]);

    // Always perform shallow query.
    opts.shallow = false;

    // Pre-compile the query (to get className).
    std::string className;
    {
        WQL* wql = WQL_Parse(opts.queryexpr.Str(), NULL);

        if (!wql)
        {
            Fzprintf(serr, ZT("%s : invalid query: %s\n\n"), scs(arg0),
                scs(argv[3]));
            return 1;
        }

        className = ZToStr(wql->className);
        WQL_Delete(wql);
    }

    // Invoke enumerate with these arguments.
    const char* args[5];
    args[0] = argv[0];
    args[1] = "ei";
    args[2] = argv[2]; /* namespace */
    args[3] = className.c_str();
    args[4] = NULL;

    return EnumerateInstances(client, 4, args);
}

static int GetInstance(Client& client, int argc, const char* argv[])
{
    if (argc < 4)
    {
        Fzprintf(serr, ZT("Usage: %s gi NAMESPACE INSTANCENAME\n\n"), scs(arg0));
        return 1;
    }

    const String nameSpace = MakeString(argv[2]);

    DInstance instanceName;

    argc -= 3;
    argv += 3;
    const char** p = argv;
    const char** end = p + argc;

    if (!ArgsToInstance(p, end, DInstance::CLASS, true, instanceName))
    {
        err(ZT("invalid instance name specification"));
        return 1;
    }

    if (p != end)
    {
        err(ZT("extraneous arguments after instance name"));
        return 1;
    }

    DInstance instance;
    MI_Result result;

    if (!client.GetInstance(nameSpace, instanceName, opts.timeOut, instance,
        result))
    {
        err(ZT("communication failed"));
        return 1;
    }

    if (!opts.quiet && result == MI_RESULT_OK)
    {
        PrintInstance(instance, opts.nulls);
    }

    s_numInstances++;

    if (result != MI_RESULT_OK)
    {
        if (!opts.suppressResults)
            err(ZT("result: %Z"), zcs(Result_ToString(result)));
        return 2;
    }

    return 0;
}

static int CreateInstance(Client& client, int argc, const char* argv[])
{
    if (argc < 4)
    {
        Fzprintf(serr, ZT("Usage: %s ci NAMESPACE INSTANCE\n\n"), scs(arg0));
        return 1;
    }

    const String nameSpace = MakeString(argv[2]);

    DInstance instance;

    argc -= 3;
    argv += 3;
    const char** p = argv;
    const char** end = p + argc;

    if (!ArgsToInstance(p, end, DInstance::CLASS, true, instance))
    {
        err(ZT("invalid instanceName name specification"));
        return 1;
    }

    if (p != end)
    {
        err(ZT("extraneous arguments after instanceName name"));
        return 1;
    }

    DInstance instanceName;
    MI_Result result;

    if (!client.CreateInstance(nameSpace, instance, opts.timeOut, instanceName,
        result))
    {
        err(ZT("communication failed"));
        return 1;
    }

    if (!opts.quiet && result == MI_RESULT_OK)
    {
        PrintInstance(instanceName, true);
    }

    s_numInstances++;

    if (result != MI_RESULT_OK)
    {
        if (!opts.suppressResults)
            err(ZT("result: %Z"), zcs(Result_ToString(result)));
        return 2;
    }

    return 0;
}

static int ModifyInstance(Client& client, int argc, const char* argv[])
{
    if (argc < 4)
    {
        Fzprintf(serr, ZT("Usage: %s mi NAMESPACE INSTANCE\n\n"), scs(arg0));
        return 1;
    }

    const String nameSpace = MakeString(argv[2]);

    DInstance instance;

    argc -= 3;
    argv += 3;
    const char** p = argv;
    const char** end = p + argc;

    if (!ArgsToInstance(p, end, DInstance::CLASS, true, instance))
    {
        err(ZT("invalid instanceName name specification"));
        return 1;
    }

    if (p != end)
    {
        err(ZT("extraneous arguments after instanceName name"));
        return 1;
    }

    MI_Result result;

    if (!client.ModifyInstance(nameSpace, instance, opts.timeOut, result))
    {
        err(ZT("communication failed"));
        return 1;
    }

    if (result != MI_RESULT_OK)
    {
        if (!opts.suppressResults)
            err(ZT("result: %Z"), zcs(Result_ToString(result)));
        return 2;
    }

    return 0;
}

static int DeleteInstance(Client& client, int argc, const char* argv[])
{
    if (argc < 4)
    {
        Fzprintf(serr, ZT("Usage: %s gi NAMESPACE INSTANCENAME\n\n"),
            scs(arg0));
        return 1;
    }

    const String nameSpace = MakeString(argv[2]);

    DInstance instanceName;

    argc -= 3;
    argv += 3;
    const char** p = argv;
    const char** end = p + argc;

    if (!ArgsToInstance(p, end, DInstance::CLASS, true, instanceName))
    {
        err(ZT("invalid instance name specification"));
        return 1;
    }

    if (p != end)
    {
        err(ZT("extraneous arguments after instance name"));
        return 1;
    }

    DInstance instance;
    MI_Result result;

    if (!client.DeleteInstance(nameSpace, instanceName, opts.timeOut, result))
    {
        err(ZT("communication failed"));
        return 1;
    }

    if (result != MI_RESULT_OK)
    {
        if (!opts.suppressResults)
            err(ZT("result: %Z"), zcs(Result_ToString(result)));
        return 2;
    }

    return 0;
}

static int Associators(Client& client, int argc, const char* argv[])
{
    if (argc < 4)
    {
        Fzprintf(serr, ZT("Usage: %s a NAMESPACE INSTANCENAME\n\n"), scs(arg0));
        return 1;
    }

    const String nameSpace = MakeString(argv[2]);

    DInstance instanceName;

    argc -= 3;
    argv += 3;
    const char** p = argv;
    const char** end = p + argc;

    if (!ArgsToInstance(p, end, DInstance::CLASS, true, instanceName))
    {
        err(ZT("invalid instance name specification"));
        return 1;
    }

    if (p != end)
    {
        err(ZT("extraneous arguments after instance name"));
        return 1;
    }

    Array<DInstance> instances;
    MI_Result result;

    if (!client.AssociatorInstances(
        nameSpace,
        instanceName,
        opts.assocClass,
        opts.resultClass,
        opts.role,
        opts.resultRole,
        opts.timeOut,
        instances,
        result))
    {
        err(ZT("communication failed"));
        return 1;
    }

    if (!opts.quiet)
    {
        for (Uint32 i = 0; i < instances.GetSize(); i++)
        {
            PrintInstance(instances[i], opts.nulls);
        }
    }

    s_numInstances += instances.GetSize();

    if (result != MI_RESULT_OK)
    {
        if (!opts.suppressResults)
            err(ZT("results: %Z"), zcs(Result_ToString(result)));
        return 2;
    }

    return 0;
}

static int References(Client& client, int argc, const char* argv[])
{
    if (argc < 4)
    {
        Fzprintf(serr, ZT("Usage: %s a NAMESPACE INSTANCENAME\n\n"), scs(arg0));
        return 1;
    }

    const String nameSpace = MakeString(argv[2]);

    DInstance instanceName;

    argc -= 3;
    argv += 3;
    const char** p = argv;
    const char** end = p + argc;

    if (!ArgsToInstance(p, end, DInstance::CLASS, true, instanceName))
    {
        err(ZT("invalid instance name specification"));
        return 1;
    }

    if (p != end)
    {
        err(ZT("extraneous arguments after instance name"));
        return 1;
    }

    Array<DInstance> instances;
    MI_Result result;

    if (!client.ReferenceInstances(
        nameSpace,
        instanceName,
        opts.assocClass,
        opts.role,
        opts.timeOut,
        instances,
        result))
    {
        err(ZT("communication failed"));
        return 1;
    }

//    if (!opts.quiet)
    {
        for (Uint32 i = 0; i < instances.GetSize(); i++)
        {
            PrintInstance(instances[i], opts.nulls);
        }
    }

    s_numInstances += instances.GetSize();
    if (result != MI_RESULT_OK)
    {
        if (!opts.suppressResults)
            err(ZT("results: %Z"), zcs(Result_ToString(result)));
        return 2;
    }

    return 0;
}

static int Invoke(Client& client, int argc, const char* argv[])
{
    if (argc < 5)
    {
        Fzprintf(serr,
            ZT("Usage: %s iv NAMESPACE INSTANCENAME METHODNAME PARAMETERS\n\n"),
            scs(arg0));
        return 1;
    }

    const String nameSpace = MakeString(argv[2]);

    // Skip over first 3 args:
    argc -= 3;
    argv += 3;
    const char** p = argv;
    const char** end = p + argc;

    // Get instanceName parameter:
    DInstance instanceName;
    {
        if (!ArgsToInstance(p, end, DInstance::CLASS, true, instanceName))
        {
            err(ZT("invalid instance name specification"));
            return 1;
        }
    }

    // Get methodName parameter:
    if (p == end)
    {
        err(ZT("expected method name"));
        return 1;
    }

    String methodName = MakeString(*p);
    p++;

    // Get method parameters:
    DInstance in(ZT("Parameters"), DInstance::METHOD);

    if (p != end)
    {
        if (!ArgsToInstance(p, end, DInstance::METHOD, true, in))
        {
            err(ZT("invalid parameters specification"));
            return 1;
        }
    }

    // Invoke the method:
    DInstance out;
    MI_Result result;

    if (!client.Invoke(nameSpace, instanceName, methodName, in, opts.timeOut,
        out, result))
    {
        err(ZT("communication failed"));
        return 1;
    }

    if (!opts.quiet && result == MI_RESULT_OK)
    {
        PrintInstance(out, opts.nulls);
    }

    s_numInstances++;

    if (result != MI_RESULT_OK)
    {
        if (!opts.suppressResults)
            err(ZT("results: %Z"), zcs(Result_ToString(result)));
        return 2;
    }

    return 0;
}

class CliHandler : public Handler
{
public:

    /*virtual void HandleConnect();


    virtual void HandleNoOp(Uint64 msgID);*/
    virtual void HandleConnectFailed()
    {
        if (!opts.suppressResults)
            err(ZT("connect failed..."));
        s_result = MI_RESULT_FAILED;
        s_done = true;
    }

    virtual void HandleDisconnect()
    {
        if (!opts.suppressResults)
            err(ZT("disconnected..."));
        s_result = MI_RESULT_FAILED;
        s_done = true;
    }

    virtual void HandleInstance(Uint64 msgID, const DInstance& instance)
    {
        MI_UNUSED(msgID);

        if (!opts.quiet)
        {
            PrintInstance(instance, opts.nulls);
        }

        s_numInstances++;
    }

    virtual void HandleResult(Uint64 msgID, MI_Result result)
    {
        MI_UNUSED(msgID);

        if (result != MI_RESULT_OK)
        {
            if (!opts.suppressResults)
                err(ZT("results: %Z"), zcs(Result_ToString(result)));
        }
        s_result = result;
        s_done = true;
    }
    virtual void HandleResult(Uint64 msgID, MI_Result result, const MI_Char *error, const DInstance* cimError)
    {
        MI_UNUSED(msgID);

        if (result != MI_RESULT_OK)
        {
            if (!opts.suppressResults)
            {
                err(ZT("results: %Z"), zcs(Result_ToString(result)));
                if (!opts.quiet && error)
                {
                    err(ZT("error message: %Z"), zcs(error));
                }
                if (!opts.quiet && cimError)
                {
                    PrintInstance(*cimError, opts.nulls);
                }
            }
        }
        s_result = result;
        s_done = true;
    }
};

int climain(int argc, const char* argv[])
{
    arg0 = argv[0];
    const Uint64 CONNECT_TIMEOUT_USEC = 10 * 1000 * 1000;
    int r = 0;
    Client client( new CliHandler );

    // Setup default stderr and stdout streams:
    serr = stderr;
    sout = stdout;

    // Initialize options:
    opts.Clear();

    // Get the options:
    GetCommandLineDestDirOption(&argc, argv);

    // Get configuration file options:
    if (GetConfigFileOptions() != 0)
    {
        r = 1;
        goto done;
    }

    // Get the options:
    if (GetCommandLineOptions(argc, argv, opts) != 0)
    {
        r = 1;
        goto done;
    }

    // There must be at least 1 argument left:
    if (argc < 2)
    {
        if (argc >= 1)
        {
            Fzprintf(sout, USAGE, argv[0]);
        }
        else
        {
            Fzprintf(sout, USAGE, MI_T("omicli"));
        }
        r = 1;
        goto done;
    }

    // Remember start time (will calculate total time in PrintSummary()
    Time_Now(&s_startTime);
    // Connect to server:

    if (strcmp(argv[1], "enc") != 0)
    {
#if defined(CONFIG_OS_WINDOWS)
        if (!client.Connect(ZT("7777"), opts.user, opts.password, CONNECT_TIMEOUT_USEC))
#else
        String socketFileString(GetPath(ID_SOCKETFILE));

LOGD2(("climain - B. Calling client.Connect. socketfile: %s, timeout: %lu", socketFileString, (unsigned long)CONNECT_TIMEOUT_USEC));
        if (!client.Connect(
            socketFileString,
            opts.user,
            opts.password,
            CONNECT_TIMEOUT_USEC))
#endif
        {
LOGD2(("climain - C. client.Connect failed"));
#if defined(CONFIG_OS_WINDOWS)
            err(ZT("failed to connect on port 7777"));
#else
            err(ZT("failed to connect to %s"), scs(GetPath(ID_SOCKETFILE)));
#endif
LOGD2(("climain - D. client.Connect failed"));
            r = 1;
            goto done;
        }
    }
    if (strcmp(argv[1], "noop") == 0)
    {
        for (int i = 0; i < opts.repeat; i++)
        {
            r = NoOp(client, argc, argv);
            if (r != 0)
                goto done;
        }
    }
    else if (strcmp(argv[1], "enc") == 0)
    {
        r = Encode(argc, argv);
        goto done;
    }
    else if (strcmp(argv[1], "ei") == 0)
    {
        for (int i = 0; i < opts.repeat; i++)
        {
            r = EnumerateInstances(client, argc, argv);
            if (r != 0)
                goto done;
        }
    }
    else if (strcmp(argv[1], "id") == 0)
    {
        if (argc != 2)
        {
            Fzprintf(serr, ZT("Usage: %s id\n\n"), scs(arg0));
            r = 1;
            goto done;
        }

        const char* args[5];
        args[0]= argv[0];
        args[1]= (char*)"ei";
        args[2]= (char*)"root/omi";
        args[3]= (char*)"OMI_Identify";
        args[4]= NULL;

        for (int i = 0; i < opts.repeat; i++)
        {
            r = EnumerateInstances(client, 4, args);
            if (r != 0)
                goto done;
        }
    }
    else if (strcmp(argv[1], "gi") == 0)
    {
        for (int i = 0; i < opts.repeat; i++)
        {
            r = GetInstance(client, argc, argv);
            if (r != 0)
                goto done;
        }
    }
    else if (strcmp(argv[1], "ci") == 0)
    {
        for (int i = 0; i < opts.repeat; i++)
        {
            r = CreateInstance(client, argc, argv);
            if (r != 0)
                goto done;
        }
    }
    else if (strcmp(argv[1], "mi") == 0)
    {
        for (int i = 0; i < opts.repeat; i++)
        {
            r = ModifyInstance(client, argc, argv);
            if (r != 0)
                goto done;
        }
    }
    else if (strcmp(argv[1], "di") == 0)
    {
        for (int i = 0; i < opts.repeat; i++)
        {
            r = DeleteInstance(client, argc, argv);
            if (r != 0)
                goto done;
        }
    }
    else if (strcmp(argv[1], "iv") == 0)
    {
        for (int i = 0; i < opts.repeat; i++)
        {
            r = Invoke(client, argc, argv);
            if (r != 0)
                goto done;
        }
    }
    else if (strcmp(argv[1], "a") == 0)
    {
        for (int i = 0; i < opts.repeat; i++)
        {
            r = Associators(client, argc, argv);
            if (r != 0)
                goto done;
        }
    }
    else if (strcmp(argv[1], "r") == 0)
    {
        for (int i = 0; i < opts.repeat; i++)
        {
            r = References(client, argc, argv);
            if (r != 0)
                goto done;
        }
    }
    else if (strcmp(argv[1], "wql") == 0)
    {
        for (int i = 0; i < opts.repeat; i++)
        {
            r = Query(client, argc, argv);
            if (r != 0)
                goto done;
        }
    }
    else
    {
        err(ZT("unknown command: %s"), scs(argv[1]));
        r = 1;
        goto done;
    }

done:

    if (sout != stdout)
        fclose(sout);

    if (serr != stdout)
        fclose(serr);

    if (opts.summary)
        PrintSummary();

    return r;
}
