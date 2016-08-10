/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

// StorageServiceTest.cpp : Defines the entry point for the console application.
//

#include "ut.h"
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <pal/format.h>
#include <common.h>

#if defined(CONFIG_OS_WINDOWS)
# include <time.h>
#else
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
#endif

using namespace std;

namespace ut {
    typedef unsigned long long uint64;

    static vector< MODULE_TEST_CALLBACK > *s_fn;
    static int  s_tests = 0;
    static bool s_lastTestFailed = false;
    static vector< UnittestException > s_errors;
    static vector< string > s_warnings;
    static string s_TestsToRun;
    static unsigned int s_NumToRunEachTest = 1; // execute each test this number of times
    static bool s_printTestName = false;
    static bool s_summary = false;
    static const char*  s_argv0;
    static string s_xml_file;
    static ut::uint64 s_test_start_time;
    static std::map<std::string, string> s_attributes;
    static bool s_started = false;

    /* helper functions */
    static ut::uint64 TimeNow()
    {
#if defined(CONFIG_OS_WINDOWS)
        FILETIME ft;
        ULARGE_INTEGER tmp;

        GetSystemTimeAsFileTime(&ft);
        tmp.u.LowPart = ft.dwLowDateTime;
        tmp.u.HighPart = ft.dwHighDateTime;
        tmp.QuadPart -= 0X19DB1DED53E8000;
        return (tmp.QuadPart / (UINT64)10);
#else
        struct timeval tv;
        struct timezone tz;
        memset(&tv, 0, sizeof(tv));
        memset(&tz, 0, sizeof(tz));

        if (gettimeofday(&tv, &tz) != 0)
            return 0;

        return ((ut::uint64)tv.tv_sec * (ut::uint64)1000000 + (ut::uint64)tv.tv_usec);
#endif
    }

    void registerCallback(MODULE_TEST_CALLBACK pfn)
    {
        if ( !s_fn )
            s_fn = new vector< MODULE_TEST_CALLBACK >;

        s_fn->push_back( pfn );
    }

    unsigned int testStarted(const char* name)
    {
        if ( !s_TestsToRun.empty() &&
            s_TestsToRun.find(string(",") + name + ",") == s_TestsToRun.npos )
            return 0;

        if (s_printTestName)
            Tprintf(ZT("%s"), scs(name));

        s_tests++;
        s_test_start_time = TimeNow();

        return s_NumToRunEachTest;
    }

    void testCompleted(const char* /*name*/)
    {
        if (s_summary || s_printTestName)
        {
            Tprintf(ZT("%s"), scs(s_lastTestFailed ? "X" : "*"));

            if (s_tests % 80 == 0)
                Tprintf(ZT("\n"));
        }

        if (s_printTestName)
        {
            ut::uint64 elapsed = TimeNow() - s_test_start_time;
            Tprintf(ZT(" (%d.%03d ms)\n"), 
                (int)(elapsed / 1000 ), //ms
                (int)(elapsed % 1000) ); // us

        }
        s_lastTestFailed = false;
    }

    void testFailed(const UnittestException& ex)
    {
        s_lastTestFailed = true;
        s_errors.push_back(ex);
    }

    void testWarning(const char* text)
    {
        s_warnings.push_back(text);
    }

    bool testGetAttr(const std::string& name, std::string& value)
    {
        if (!s_started)
            return false;

        map<string, string>::const_iterator it = s_attributes.find(name);

        if (it == s_attributes.end())
            return false;

        value = it->second;
        return true;
    }

};

using namespace ut;

#define USAGE ZT("\
Usage: %s [OPTIONS] [TESTS]\n\
\n\
Where TESTS is a comma separated list of tests to run.\n\
\n\
OPTIONS:\n\
    -h                  help screen\n\
    -n <number>         execute each test given number of times\n\
    -p                  print out test name\n\
    -xml <file>         create xml results file\n\
    -a <name>[=value]   set attribute for unittest\n\n")

static void Usage()
{
    Tprintf(USAGE, s_argv0);
}

static void CheckArguments(int argc, _In_reads_(argc) CharPtr argv[])
{
    for (int i = 0; i < argc; )
    {
        /* Check for -I option */
#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26018)
#endif
        if (strcmp(argv[i], "-n") == 0)
#ifdef _PREFAST_
#pragma prefast (pop)
#endif
        {
            /* Check for mandatory option argument */
            if (i + 1 == argc)
            {
                Ftprintf(stderr, ZT("Missing option argument for -n"));
                Usage();
                exit(1);
            }

            /* Append path to array */
            s_NumToRunEachTest = atol(argv[i+1]);

            /* Remove option and its argument from argv */
            memmove(&argv[i], &argv[i+2], sizeof(char*) * (argc-i-2));
            argc -= 2;
        }
        else if (strcmp(argv[i], "-xml") == 0)
        {
            /* Check for mandatory option argument */
            if (i + 1 == argc)
            {
                Ftprintf(stderr, ZT("Missing option argument for -xml"));
                Usage();
                exit(1);
            }

            /* Append path to array */
            s_xml_file = argv[i+1];

            /* Remove option and its argument from argv */
            memmove(&argv[i], &argv[i+2], sizeof(char*) * (argc-i-2));
            argc -= 2;
        }
        else if (strcmp(argv[i], "-p") == 0)
        {
            s_printTestName = true;

            /* Remove option and its argument from argv */
            memmove(&argv[i], &argv[i+1], sizeof(char*) * (argc-i-1));
            argc--;
        }
        else if (strcmp(argv[i], "-s") == 0)
        {
            s_summary = true;

            memmove(&argv[i], &argv[i+1], sizeof(char*) * (argc-i-1));
            argc--;
        }
        else if (strcmp(argv[i], "-a") == 0)
        {
            /* Check for mandatory option argument */
            if (i + 1 == argc)
            {
                Ftprintf(stderr, ZT("Missing option argument for -a"));
                Usage();
                exit(1);
            }

            /* Append path to array */
            {
                const char* name = argv[i+1];
                const char* value = strchr(name, '=');

                string strName, strValue;

                if (value)
                {
                    strName = string(name, value);
                    strValue = value+1;
                }
                else
                {
                    strName = name;
                }
                //s_attributes[ strName ] = strValue;
                s_attributes.insert(pair<string, string>(strName, strValue));

            }

            /* Remove option and its argument from argv */
            memmove(&argv[i], &argv[i+2], sizeof(char*) * (argc-i-2));
            argc -= 2;
        }
        else if (strcmp(argv[i], "-h") == 0)
        {
            Usage();
            exit(0);
        }
        else if (argv[i][0] == '-')
        {
            Ftprintf(stderr, ZT("unknown option: %s"), scs(argv[i]));
            Usage();
            exit(1);
        }
        else
            i++;
    }

    if ( argc > 1 )
    {
        s_TestsToRun = string(",") + argv[1] + ",";
    }

}

static void produceXmlOutput()
{
    // create xml from results
//<?xml version="1.0" encoding='ISO-8859-1' standalone='yes' ?>
//<?xml-stylesheet type="text/xsl" href="report.xsl"?>
//<Statistics>
//  <Tests>687</Tests>
//  <FailuresTotal>0</FailuresTotal>
//  <Errors>0</Errors>
//  <Failures>0</Failures>
//</Statistics>
    try 
    {
        ofstream fst( s_xml_file.c_str(), ios_base::out);

        fst << "\
<?xml version=\"1.0\" encoding='ISO-8859-1' standalone='yes' ?>\
<Statistics>\
  <Tests>" << s_tests << "</Tests>\
<FailuresTotal>" << s_errors.size() << "</FailuresTotal>\
<Errors>0</Errors>\
<Failures>0</Failures>\
</Statistics>";

        if ( fst.bad() )
            throw 1;
    }
    catch(...)
    {
        Ftprintf(stderr, ZT("unable to open file %s\n"), 
            scs(s_xml_file.c_str()));
    }

}

int MI_MAIN_CALL main(int argc, _In_reads_(argc) CharPtr argv[])
{
    /* Some data structures could be touched during module load. Once we reach
     * this point, it is now safe to touch the other global variables. */
    s_started = true;

    s_argv0 = argv[0];

    if (!s_fn)
    {
        Tprintf(ZT("No tests to run\n"));
        return 0;
    }

    /* Check command-line arguments */

    CheckArguments(argc,argv);

    /* Print program name */

    Tprintf(ZT("==== %s:\n"), scs(s_argv0));

    /* Save start time */

    ut::uint64 starttime = TimeNow();

    /* Run tests */

    for ( unsigned int i = 0; i < s_fn->size(); i++ )
    {
        (*s_fn)[i] ();
    }

    Tprintf(ZT("\n"));

    /* Print test executation summary */

s_summary = true;

    if (s_summary)
    {
        Tprintf(ZT("Completed %d test(s)"), s_tests);

        if (s_errors.empty())
            Tprintf(ZT("OK\n"));
        else
            Tprintf(ZT("%u FAILED\n\n"), (int)s_errors.size());

        ut::uint64 elapsed = TimeNow() - starttime;
        Tprintf(ZT(" \tspent %d.%03d ms\n\n"), 
            (int)(elapsed / 1000 ), //ms
            (int)(elapsed % 1000) ); // us
    }

    /* Print any failures */

    for ( unsigned int i = 0; i < s_errors.size(); i++ )
    {
        Tprintf(ZT("test-case: %s\n"), scs(s_errors[i].m_testcase.c_str()));
        Tprintf(ZT("function: %s\n"), scs(s_errors[i].m_function.c_str()));
        Tprintf(ZT("file: %s:%u\n"), scs(s_errors[i].m_file.c_str()),
            (int)s_errors[i].m_line);
        Tprintf(ZT("condition: %s\n\n"), scs(s_errors[i].m_text.c_str()));
    }

    /* Print any warnings */

    if (!s_warnings.empty())
    {
        Tprintf(ZT("\nWarnings:\n"));

        for ( unsigned int i = 0; i < s_warnings.size(); i++ )
        {
            Tprintf(ZT("%s\n"), scs(s_warnings[i].c_str()));
        }
        Tprintf(ZT("\n"));
    }

    /* Create XML output files */

    if ( !s_xml_file.empty())
    {
        produceXmlOutput();
    }

    delete s_fn; s_fn = 0;

    return s_errors.empty() ? 0 : 1;
}

