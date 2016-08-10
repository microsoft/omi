/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef MI_CHAR_TYPE
# define MI_CHAR_TYPE 1
#endif

#include <common.h>
#include <gen/gen.h>
#include <base/paths.h>
#include <pal/format.h>
#include <base/env.h>
#include <base/conf.h>
#include <base/omigetopt.h>
#include <windows/config.h>

static const char HELP[] = "\
Usage: %s [OPTIONS] PATH CLASSNAME[=ALIAS] ...\n\
\n\
OVERVIEW:\n\
    This program generates provider source code from MOF class definitions.\n\
    PATH is a file that contains the MOF definitions (or includes them).\n\
    It must include any dependent MOF defintions as well (such as the CIM\n\
    schema). The PATH is followed by a list of CLASSNAME arguments, which are\n\
    the names of the MOF classes to be generated. Each CLASSNAME argument may\n\
    be followed by an optional ALIAS argument (separated by an equal sign).\n\
    The ALIAS provides an alternative name for the class to be used within\n\
    the C source code. For example, 'CIM_ComputerSystem=CompSys' says to\n\
    use 'CompSys' in C sources instead of 'CIM_ComputerSystem'.\n\
\n\
OPTIONS:\n\
    -I PATH                     Search this directory for included MOF files.\n\
    -D                          Generate 'Description' qualifiers.\n\
    -V                          Generate 'Values' and 'ValueMap' qualifiers.\n\
    -M                          Generate 'MappingStrings' qualifiers.\n\
    -O                          Generate 'ModelCorrespondence' qualifiers.\n\
    -S                          Generate standard CIM qualifier declarations.\n\
    -B                          Generate boolean qualifiers.\n\
    -Q                          Suppress qualifier declarations generation.\n\
    -q                          Quiet mode - do not print anything on stdout.\n\
    -h, --help                  Print this help message.\n\
    -v, --version               Print the program version.\n\
    -s SCHEMA                   Specify C name of the schema [schemaDecl].\n\
    -n                          Suppress provider generation (only schema.c).\n\
    --cpp                       Generate cpp skeleton for the provider.\n\
    -d PATH                     Place output files in this directory.\n\
    -l                          Generate strings.rc file.\n\
    -f                          Set filter support flag into MI_Main().\n\
    -A                          Generate single association function.\n\
    -e CLASS                    Generate extra class with this name.\n\
    -y NAME                     Use NAME as entry point (default MI_Main).\n\
    --no-warnings         	Print no warnings.\n\
    -C, --schemafile PATH       Alternative path of main CIM schema file.\n\
    -m PROVIDERNAME             Generate provider makefile.\n\
    --nogi CLASSNAME            Set MI_ProviderFT.GetInstance to NULL for\n\
                                the given class. This forces the provider\n\
                                manager to use the EnumerateInstances method\n\
                                to satisfy all GetInstance requests on this\n\
                                class.\n\
\n\
EXAMPLES:\n\
    The following example generates a 'MSFT_ComputerSystem' class, which is\n\
    defined in schema.mof.\n\
\n\
        $ omigen schema.mof MSFT_ComputerSystem=CompSys\n\
        Created CompSys.h\n\
        Created CompSys.c\n\
        Created schema.c\n\
        Created module.c\n\
\n\
    CompSys.h defines the 'CompSys' structure. schema.c defines run-time type\n\
    information for the CompSys structure. CompSys.c contains the provider\n\
    stubs and module.c contains the MI_Main() provider entry point.\n\
\n\
FILES:\n\
    .omigenrc\n\
        This file contains an option per line as it might appear on the \n\
        command line (-OPTION [ARGUMENT]). These options are appended to the\n\
        command line options, which take precedence. The program first\n\
        attempts to open this file in the current directory followed by\n\
        the home directory (given by the 'HOME' environment variable).\n\
        The following is an example of the contents of this file.\n\
\n\
            -I /opt/microsoft/sca/mof/cim222\n\
            -I /opt/microsoft/sca/mof/extras\n\
\n\
";

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

PRINTF_FORMAT(1, 2)
static void FUNCTION_NEVER_RETURNS err(const char* fmt, ...)
{
    fprintf(stderr, "%s: ", arg0);

    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    fputc('\n', stderr);
    exit(1);
}

static void _GetCommandLineDestDirOption(
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
                err("missing argument for --destdir option");

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
            err("failed to set destdir");
    }

    *argc_ = argc;
}

//==============================================================================
//
// _GetCommandLineOptions()
//
//     This function processes command line options. Each option begins with 
//     the '-' character followed by a single alphabetic character. An option
//     may be followed by an optional argument. GeneratorOptions and their 
//     optional arguments are removed from the argc-argv array upon return. 
//     Extracted options are stored in the options parameter (see the 
//     GeneratorOptions structure defined above).
//
//==============================================================================

static string schemafile;

static void _GetCommandLineOptions( 
    int& argc, 
    const char**& argv, 
    GeneratorOptions& options)
{
    GetOptState state = GETOPTSTATE_INITIALIZER;

    const char* opts[] =
    {
        "-I:",
        "-h",
        "--help",
        "-v",
        "--version",
        "-D",
        "-V",
        "-M",
        "-O",
        "-S",
        "-B",
        "-Q",
        "-f",
        "-q",
        "--no-warnings",
        "-a",
        "-n",
        "--cpp",
        "-s:",
        "-d:",
        "-e:",
        "-y:",
        "-l",
        "-reg:",
        "-A",
        "-C:",
        "--schemafile:",
        "-m:",
        "--nogi:",
        NULL,
    };

    /* For each argument */
    for (;;)
    {
        int r = GetOpt(&argc, (const char**)argv, opts, &state);

        if (r == 1)
            break;

        if (r == -1)
            err("%s", state.err);

        /* Check for -I option */
        if (strcmp(state.opt, "-I") == 0)
        {
            options.paths.push_back(state.arg);
        }
        else if (strcmp(state.opt, "-h") == 0 ||
            strcmp(state.opt, "--help") == 0)
        {
            printf(HELP, arg0);
            exit(1);
        }
        else if (strcmp(state.opt, "-v") == 0 ||
                 strcmp(state.opt, "--version") == 0)
        {
#if defined(CONFIG_OS_WINDOWS)
            printf(ZT("%s: %S\n"), arg0,
                CONFIG_PRODUCT L"-" CONFIG_VERSION L" - " CONFIG_DATE);
#else
            printf("%s: %s\n", arg0,
                CONFIG_PRODUCT "-" CONFIG_VERSION " - " CONFIG_DATE);
#endif
            exit(0);
        }
        else if (strcmp(state.opt, "-D") == 0)
        {
            options.descriptions = true;
        }
        else if (strcmp(state.opt, "-V") == 0)
        {
            options.values = true;
        }
        else if (strcmp(state.opt, "-M") == 0)
        {
            options.mappingStrings = true;
        }
        else if (strcmp(state.opt, "-O") == 0)
        {
            options.modelCorrespondence = true;
        }
        else if (strcmp(state.opt, "-S") == 0)
        {
            options.standardQualifiers = true;
        }
        else if (strcmp(state.opt, "-B") == 0)
        {
            options.booleanQualifiers = true;
        }
        else if (strcmp(state.opt, "-Q") == 0)
        {
            options.ignoreAllQualifiers = true;
        }
        else if (strcmp(state.opt, "-f") == 0)
        {
            options.filterSupport = true;
        }
        else if (strcmp(state.opt, "-q") == 0)
        {
            options.quiet = true;
        }
        else if (strcmp(state.opt, "--no-warnings") == 0)
        {
            options.no_warnings = true;
        }
        else if (strcmp(state.opt, "-a") == 0)
        {
            options.all = true;
        }
        else if (strcmp(state.opt, "-n") == 0)
        {
            options.noProviders = true;
        }
        else if (strcmp(state.opt, "--cpp") == 0)
        {
            options.cpp = true;
        }
        else if (strcmp(state.opt, "-s") == 0)
        {
            options.schema = state.arg;
        }
        else if (strcmp(state.opt, "-d") == 0)
        {
            options.dir = state.arg;
        }
        else if (strcmp(state.opt, "-e") == 0)
        {
            options.extraClasses.push_back(state.arg);
        }
        else if (strcmp(state.opt, "-y") == 0)
        {
            options.entryPoint = state.arg;
        }
        else if (strcmp(state.opt, "-l") == 0)
        {
            options.localize = true;
        }
        else if (strcmp(state.opt, "-reg") == 0)
        {
            options.providerRegistryPath = state.arg;
        }
        else if (strcmp(state.opt, "-A") == 0)
        {
            options.association = true;
        }
        else if (strcmp(state.opt, "-C") == 0 ||
                 strcmp(state.opt, "--schemafile") == 0)
        {
            schemafile = state.arg;

            if (schemafile.size() && access(schemafile.c_str(), R_OK) != 0)
            {
                err("file given by %s option does not exist: %s", 
                    state.opt, schemafile.c_str());
            }
        }
        else if (strcmp(state.opt, "-m") == 0)
        {
            options.providerName = state.arg;
        }
        else if (strcmp(state.opt, "--nogi") == 0)
        {
            options.noGetInstance.push_back(state.arg);
        }
        else if (strncmp(state.opt, "--", 2) == 0 && IsNickname(state.opt+2))
        {
            if (SetPathFromNickname(state.opt+2, state.arg) != 0)
                err(ZT("SetPathFromNickname() failed"));
        }
    }
}

//==============================================================================
//
// FindConfigFile()
//
//     Find the configuration file by checking in following order:
//
//         ./.omigenrc
//         home/.omigenrc
//         sysconfdir/.omigenrc
//
//==============================================================================

static int FindConfigFile(_Pre_writable_size_(PAL_MAX_PATH_SIZE) char path[PAL_MAX_PATH_SIZE])
{
    /* Look in current directory */
    {
        Strlcpy(path, "./.omigenrc", PAL_MAX_PATH_SIZE);

        if (access(path, R_OK) == 0)
            return 0;
    }

    /* Look in HOME directory */
    char* home = Dupenv("HOME");
    if (home)
    {
        Strlcpy(path, home, PAL_MAX_PATH_SIZE);
        Strlcat(path, "/.omigenrc", PAL_MAX_PATH_SIZE);

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
        Strlcat(path, "/omigen.conf", PAL_MAX_PATH_SIZE);

        if (access(path, R_OK) == 0)
            return 0;
    }

    /* Not found */
    return -1;
}

//==============================================================================
//
// _GetConfigFileOptions()
//
//     Read options from the omigen configuration file.
//
//==============================================================================

static void _GetConfigFileOptions(GeneratorOptions& opts)
{
    char path[PAL_MAX_PATH_SIZE];
    Conf* conf;

    MI_UNUSED(opts);

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

        if (strcmp(key, "schemafile") == 0)
        {
            schemafile = value;

            if (schemafile.size() && access(schemafile.c_str(), R_OK) != 0)
            {
                err("%s(%u): file given by '%s' key does not exist: %s", 
                    path, Conf_Line(conf), key, schemafile.c_str());
            }
        }
        else
            err("%s(%u): unknown key: %s", path, Conf_Line(conf), key);
    }

    /* Close configuration file */
    Conf_Close(conf);
}

//==============================================================================
//
// _EncodeStr()
//
//     Encodes special characters in a string; replaces all 'lookfor wtih replacewith
//
//==============================================================================

static void _EncodeStr(
    std::string& str, 
    const std::string lookfor, 
    const std::string& replacewith)
{
    std::string::size_type start = 0;
    std::string::size_type pos;

    for(;;)
    {
        pos = str.find(lookfor, start);

        if (pos == std::string::npos)
            break;

        str.replace(pos, lookfor.size(), replacewith);
        start = pos + replacewith.size();
    }
}

int MI_MAIN_CALL main(int argc, const char** argv)
{
    arg0 = argv[0];
    GeneratorOptions options;


    // command line
    {
        for (int i = 1; i < argc; i++)
        {
            std::string arg = argv[i];

            // escape special characters
            _EncodeStr(arg, "\\", "\\\\");
            _EncodeStr(arg, "\"", "\\\"");
            _EncodeStr(arg, " ", "\\ ");

            if (!options.cmdLine.empty())
                options.cmdLine += " ";

            options.cmdLine += arg;
        }
    }

    // Get --destdir command-line option.
    _GetCommandLineDestDirOption(&argc, argv);

    // Set path of default CIM schema file.
    schemafile = OMI_GetPath(ID_SCHEMAFILE);

    // Get configuraiton file options.
    _GetConfigFileOptions(options);

    // Get command-line options.
    _GetCommandLineOptions(argc, argv, options);

    // Check arguments. There must one or mores class name arguments unless
    // the -a options was given.
    if (argc < 2 || (!options.all && argc < 3))
    {
        fprintf(stderr, "Usage: %s PATH CLASSNAME[=ALIAS] ...\n", arg0);
        fprintf(stderr, "Try '%s -h' for help\n\n", arg0);
        exit(1);
    }

    // ProgramName argument:
    string programName = argv[0];

    // MofFiles argument (only one file):
    vector<string> mofFiles;
    {
        if (schemafile.size())
            mofFiles.push_back(schemafile);

        mofFiles.push_back(argv[1]);
    }

    // ClassNames argument:
    vector<string> classNames;
    {
        for (int i = 2; i < argc; i++)
            classNames.push_back(argv[i]);
    }

    // Invoke generator:
    return GeneratorMain(programName, mofFiles, classNames, options);
}
