/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <common.h>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

#include <base/omigetopt.h>
#include <pal/format.h>
#include <pal/strings.h>

using namespace std;

static const ZChar USAGE[] = MI_T("\
Usage: %s property [OPTIONS]\n\
\n\
OVERVIEW:\n\
    This program allows for easy modification to the omiserver.conf\n\
    configuraiton file (and is general enough to be useful to allow\n\
    for editing of other configuraiton files as well.\n\
\n\
    This program will read from STDIN and write to STDOUT, which will\n\
    allow for multiple properties to be edited via shell piping.\n\
\n\
    Exactly one action MUST be specified from the list below.\n\
\n\
OPTIONS:\n\
    -h, --help                  Print this help message.\n\
    -v, --version               Print version information.\n\
    --debug                     Enable debug output.\n\
\n\
    Actions:\n\
\n\
    -a, --add VALUE             Add value to property name specified.\n\
    -r, --remove VALUE          Remove value from property name specified.\n\
    -s, --set VALUE             Set property name to specific value.\n\
    -c, --comment               Comment out property name specified.\n\
    -u, --uncomment             Uncomment out property name specified.\n\
    -q, --query VALUE           Check if property contains queried value.\n\
\n\
EXAMPLES:\n\
    The following will add \"1270\" to property httpsport in file\n\
    /etc/opt/omi/conf/omiserver.conf:\n\
\n\
      $ omiconfigeditor httpsport -a 1270 < /etc/opt/omi/conf/omiserver.conf\n\
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
    bool debug;
    bool help;

    bool comment;
    bool uncomment;
    string add;
    string remove;
    string set;
    string query;

    Options() : debug(false), help(false), comment(false), uncomment(false)
    {
    }
};

static void GetCommandLineOptions( 
    int& argc, 
    const char**& argv, 
    Options& options)
{
    GetOptState state = GETOPTSTATE_INITIALIZER;
    const char* opts[] =
    {
        "--debug",
        "-h",
        "--help",
        "-v",
        "--version",
        "-a:",
        "--add:",
        "-r:",
        "--remove:",
        "-s:",
        "--set:",
        "-c",
        "--comment",
        "-u",
        "--uncomment",
        "-q:",
        "--query:",
        NULL
    };

    /* For each argument */
    for (;;)
    {
        int r = GetOpt(&argc, (const char**)argv, opts, &state);

        if (r == 1)
            break;

        if (r == -1)
            err(ZT("%s"), scs(state.err));

        if (strcmp(state.opt, "--debug") == 0)
        {
            options.debug = true;
        }
        else if (strcmp(state.opt, "-h") == 0 || 
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
        else
        {
            // Most options are mutually exclusive. Verify this when reading option.

            if (options.comment ||
                options.uncomment ||
                !options.add.empty() ||
                !options.remove.empty() ||
                !options.set.empty() ||
                !options.query.empty())
            {
                err(ZT("Conflicting option specified with: %s"), scs(state.opt));
            }

            if (strcmp(state.opt, "-c") == 0 || 
                strcmp(state.opt, "--comment") == 0)
            {
                options.comment = true;
            }
            else if (strcmp(state.opt, "-u") == 0 || 
                     strcmp(state.opt, "--uncomment") == 0)
            {
                options.uncomment = true;
            }
            else if (strcmp(state.opt, "-a") == 0 || 
                     strcmp(state.opt, "--add") == 0)
            {
                options.add = state.arg;

                if (options.add.find(",") != string::npos)
                    err(ZT("Not allowed to add element with embedded comma: %s"), scs(state.arg));
            }
            else if (strcmp(state.opt, "-r") == 0 ||
                     strcmp(state.opt, "--remove") == 0)
            {
                options.remove = state.arg;

                if (options.remove.find(",") != string::npos)
                    err(ZT("Not allowed to remove element with embedded comma: %s"), scs(state.arg));
            }
            else if (strcmp(state.opt, "-s") == 0 ||
                     strcmp(state.opt, "--set") == 0)
            {
                options.set = state.arg;
            }
            else if (strcmp(state.opt, "-q") == 0 || 
                     strcmp(state.opt, "--query") == 0)
            {
                options.query = state.arg;

                if (options.query.find(",") != string::npos)
                    err(ZT("Not allowed to query element with embedded comma: %s"), scs(state.arg));
            }
            else
            {
                err(ZT("Invalid option specified: %s"), scs(state.opt));
            }
        }
    }
}

static void _TrimLeadingTrailingSpaces(string& str)
{
    // Strip leading spaces from string

    while (!str.empty() && str[0] == ' ')
    {
        str.erase(0, 1);
    }

    // Strip trailing spaces from property

    while (!str.empty() && str[str.size()-1] == ' ')
    {
        str.erase(str.size()-1, 1);
    }

    return;
}

static void _ParseValueList(std::list<std::string>& v, const string& valueList)
{
    char *saveptr;
    char buffer[512];
    char *ptr = buffer;

    if (valueList.empty())
        return;

    if (valueList.size() > sizeof(buffer)-1)
        err(ZT("Value list is too long, size of list = %d"), valueList.size());

    Strlcpy(buffer, valueList.c_str(), sizeof(buffer));

    while (true)
    {
        char *token = Strtok(ptr, ",", &saveptr);
        ptr = NULL;
        if (NULL == token)
        {
            break;
        }

        string element(token);
        _TrimLeadingTrailingSpaces(element);
        if (!element.empty())
        {
            v.push_back(element);
        }
    }
}

static std::list<std::string>::iterator _IsValueInList(std::list<std::string>& v, const string& value)
{
    for (std::list<std::string>::iterator it = v.begin(); it != v.end(); ++it)
    {
        if (*it == value)
            return it;
    }

    return v.end();
}

static std::string& _CreateStringFromList(string& value, const std::list<std::string>& v)
{
    bool first = true;

    for (std::list<std::string>::const_iterator it = v.begin(); it != v.end(); ++it)
    {
        if ( !first )
        {
            value.append(",");
        }
        first = false;

        value.append(*it);
    }

    return value;
}

int MI_MAIN_CALL main(int argc, const char** argv)
{
    arg0 = argv[0];

    // Get command-line options.
    Options opts;

    GetCommandLineOptions(argc, argv, opts);

    // Check arguments.
    if (opts.help)
    {
        Ftprintf(stderr, USAGE, arg0);
        exit(1);
    }
    
    // Check number of arguments.
    if (argc != 2)
    {
        Ftprintf(stderr, ZT("Usage: %s key [OPTIONS]\n"), scs(arg0));
        Ftprintf(stderr, ZT("Try '%s --help' for help\n\n"), scs(arg0));
        exit(1);
    }

    string arg1(argv[1]);

    if (!opts.comment && !opts.uncomment && opts.add.empty() && opts.remove.empty() && opts.set.empty() && opts.query.empty())
    {
        Ftprintf(stderr, ZT("Usage: %s key [OPTIONS]\n"), scs(arg0));
        Ftprintf(stderr, ZT("One option (an action) must be specified\n"));
        Ftprintf(stderr, ZT("Try '%s --help' for help\n\n"), scs(arg0));
        exit(1);
    }

    // Read from stdin, writing results to stdout with modifications as necessary

    bool fDontEchoFile = !opts.query.empty() ? true : false;
    string line;
    while ( getline(cin, line) )
    {
        // Is line not like: "property=value" ?
        size_t pos = line.find("=");
        if (line.empty() || pos == string::npos)
        {
            if (!fDontEchoFile)
            {
                cout << line << std::endl;
            }
            continue;
        }

        // Parse the property and value from the line
        string prop = line.substr(0, pos);
        _TrimLeadingTrailingSpaces(prop);
        if (prop.empty())
        {
            if (!fDontEchoFile)
            {
                cout << line << std::endl;
            }
            continue;
        }

        string value = line.substr(pos+1);
        _TrimLeadingTrailingSpaces(value);

        string commentByte;
        bool fCommentedOut = false;
        if (prop[0] == '#')
        {
            prop.erase(prop.begin());           // Erase '#' byte
            _TrimLeadingTrailingSpaces(prop);   // In case line was like: '#   prop=...'
            commentByte = "#";
            fCommentedOut = true;
        }

        if (opts.debug)
        {
            cerr << "  Line found:     " << line << std::endl;
            cerr << "    Found prop:   '" << prop << "'" << std::endl;
            cerr << "    Found value:  '" << value << "'" << std::endl;
        }

        // If property isn't the one we want, move along
        if (prop != arg1)
        {
            if (!fDontEchoFile)
            {
                cout << line << std::endl;
            }
            continue;
        }

        // Support uncomment
        stringstream ss;

        if (opts.uncomment)
        {
            if (fCommentedOut)
                ss << prop << "=" << value;
            else
                ss << line;
        }
        // Support commenting out the line
        else if (opts.comment)
        {
            ss << "#" << prop << "=" << value;
        }
        // Support setting the value for a property
        else if (!opts.set.empty())
        {
            ss << commentByte << prop << "=" << opts.set;
        }
        // Support adding a value to a property list
        else if (!opts.add.empty())
        {
            std::string valueString;
            std::list<std::string> valueList;

            _ParseValueList(valueList, value);
            if (_IsValueInList(valueList, opts.add) == valueList.end())
            {
                valueList.push_back(opts.add);
            }
            ss << commentByte << prop << "=" << _CreateStringFromList(valueString,valueList);
        }
        // Support for removing a value from a property list
        else if (!opts.remove.empty())
        {
            std::string valueString;
            std::list<std::string> valueList;
            std::list<std::string>::iterator it;

            _ParseValueList(valueList, value);
            if ((it = _IsValueInList(valueList, opts.remove)) != valueList.end())
            {
                valueList.erase(it);
            }
            ss << commentByte << prop << "=" << _CreateStringFromList(valueString,valueList);
        }
        // Support querying a value from a property list
        else if (!opts.query.empty())
        {
        	std::list<std::string> valueList;

                if (!fCommentedOut)
                {
                    _ParseValueList(valueList, value);
                    if (_IsValueInList(valueList, opts.query) != valueList.end())
                    {
                        cout << prop << " has the value " << opts.query << std::endl;
                        return 0;
                    }
                }
                cout << prop << " does not have the value " << opts.query << std::endl;
        	return 1;
        }
        else
        {
            // Um, what are we supposed to do?
            err(ZT("Logic error, file %s, line %d"), scs(__FILE__), __LINE__);
        }

        if (!fDontEchoFile)
        {
            cout << ss.str() << std::endl;
        }
    }

    if (!cin.eof())
    {
        Ftprintf(stderr, ZT("Unexpected error reading from stdin: %d"), errno);
        exit(1);
    }

    return 0;
}
