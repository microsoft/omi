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
#include <cctype>
#include <ut/ut.h>
#include <base/process.h>
#include <pal/sleep.h>
#include <base/paths.h>
#include <pal/format.h>
#include <pal/dir.h>
#include <pal/strings.h>
#include <pal/file.h>
#include <omiclient/client.h>
#include <base/log.h>

using namespace std;

MI_Char s_socketFile[PAL_MAX_PATH_SIZE];
char s_socketFile_a[PAL_MAX_PATH_SIZE];


extern "C"
{
extern int climain(int argc, const MI_Char* argv[]);
}

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 28718)
#endif

// Parse the command line into tokens.
bool ParseCommandLine(MI_Char command[PAL_MAX_PATH_SIZE], vector<MI_Char*>& args)
{
    MI_Char *p = command;

    //Tprintf(MI_T("command string: %T\n"), tcs(p));
    for (;;)
    {
        // Skip leading whitespace:
        while (*p && isspace(*p))
            p++;

        if (!*p)
            break;

        // Handle string literal:
        if (*p == '"')
        {
            p++;
            MI_Char* start = p;

            if (!*p)
                return false;

            while (*p && *p != '"')
            {
                if (*p == '\\')
                {
                    p++;

                    if (!*p)
                        return false;
                }

                p++;
            }

            if (*p != '"')
                return false;

            *p++ = '\0';
            args.push_back(start);
        }
        else
        {
            MI_Char* start = p;

            while (*p && !isspace(*p))
            {
                if (*p == '\\')
                {
                    p++;

                    if (!*p)
                        return false;
                }

                p++;
            }

            if (isspace(*p))
                *p++ = '\0';

            args.push_back(start);
        }
    }

    args.push_back((MI_Char*)MI_T("--socketfile"));
    args.push_back(s_socketFile);
    return true;
}
#ifdef _PREFAST_
#pragma prefast (pop)
#endif

static Process serverProcess;

static int StartServer()
{
    const char* path = OMI_GetPath(ID_SERVERPROGRAM);
    const char* argv[17];
    char http[32];
    char https[32];
    std::string v;

    Snprintf(http, sizeof(http),"%d", ut::getUnittestPortNumberWSMANHTTP());
    Snprintf(https, sizeof(https),"%d", ut::getUnittestPortNumberWSMANHTTPS());

    Strlcpy(s_socketFile_a, OMI_GetPath(ID_SOCKETFILE), sizeof(s_socketFile_a)/sizeof(s_socketFile_a[0]));
    TcsStrlcpy(s_socketFile, s_socketFile_a, sizeof(s_socketFile)/sizeof(s_socketFile[0]));

    if (ut::testGetAttr("skipServer", v))
        return 0;

    argv[0] = path;
    argv[1] = "--rundir";
#if defined(CONFIG_OS_WINDOWS)
    argv[2] = "..";
#else
    argv[2] = OMI_GetPath(ID_PREFIX);
#endif
    argv[3] = "--ignoreAuthentication";
    argv[4] = "--socketfile";
    argv[5] = s_socketFile_a;
    argv[6] = "--httpport";
    argv[7] = http;
    argv[8] = "--httpsport";
    argv[9] = https;
    argv[10] = "--livetime";
    argv[11] = "300";

    argv[12] = "--loglevel";
    argv[13] = Log_GetLevelString(Log_GetLevel());
    argv[14] = NULL;

    if (Process_StartChild(&serverProcess, path, (char**)argv) != 0)
        return -1;

    int connected = 0;

    // wait for server to start
    // trying to connect in a loop:
    // since connect may fail quickly if server is not running
    // keep doing it in  a loop
    for (int i = 0; i < 400; i++)
    {
        mi::Client cl;
        const MI_Uint64 TIMEOUT = 1 * 1000 * 1000;

        if (cl.Connect(
            s_socketFile,
            PAL_T("unittest"), 
            PAL_T("unittest"), 
            TIMEOUT))
        {
            connected = 1;
            break;
        }

        Sleep_Milliseconds(10);
    }

    UT_ASSERT(connected == 1);

    return 0;
}

static int StartServerWsman()
{
    const char* path = OMI_GetPath(ID_SERVERPROGRAM);
    const char* argv[17];
    std::string v;

    Strlcpy(s_socketFile_a, OMI_GetPath(ID_SOCKETFILE), sizeof(s_socketFile_a)/sizeof(s_socketFile_a[0]));
    TcsStrlcpy(s_socketFile, s_socketFile_a, sizeof(s_socketFile)/sizeof(s_socketFile[0]));

    if (ut::testGetAttr("skipServer", v))
        return 0;

    argv[0] = path;
    argv[1] = "--rundir";
#if defined(CONFIG_OS_WINDOWS)
    argv[2] = "..";
#else
    argv[2] = OMI_GetPath(ID_PREFIX);
#endif
    argv[3] = "--ignoreAuthentication";
    argv[4] = "--socketfile";
    argv[5] = s_socketFile_a;
    argv[6] = "--httpport";
    argv[7] = "5985";
    argv[8] = "--httpsport";
    argv[9] = "5986";
    argv[10] = "--livetime";
    argv[11] = "300";

    argv[12] = "--loglevel";
    argv[13] = Log_GetLevelString(Log_GetLevel());
    argv[14] = NULL;

    if (Process_StartChild(&serverProcess, path, (char**)argv) != 0)
        return -1;

    int connected = 0;

    // wait for server to start
    // trying to connect in a loop:
    // since connect may fail quickly if server is not running
    // keep doing it in  a loop
    for (int i = 0; i < 400; i++)
    {
        mi::Client cl;
        const MI_Uint64 TIMEOUT = 1 * 1000 * 1000;

        if (cl.Connect(
            s_socketFile,
            PAL_T("unittest"), 
            PAL_T("unittest"), 
            TIMEOUT))
        {
            connected = 1;
            break;
        }

        Sleep_Milliseconds(10);
    }

    UT_ASSERT(connected == 1);

    return 0;
}

static int StopServer()
{
    std::string v;

    if (ut::testGetAttr("skipServer", v))
        return 0;

    if (Process_StopChild(&serverProcess) != 0)
        return -1;
    return 0;
}

static bool Inhale(const char* path, string& strOut, bool baseline)
{
    char buf[1024];
    string str;

    /* Open file */
    FILE* is = File_Open(path, "rb");
    if (!is)
        return false;

    /* Read file into str parameter */
    for (;;)
    {
#if defined(CONFIG_OS_WINDOWS)
        long n = fread(buf, 1, sizeof(buf)-2, is);
#else
        ssize_t n = fread(buf, 1, sizeof(buf)-1, is);
#endif
        if (n <= 0)
            break;
        _Analysis_assume_(n<1023);
        buf[n] = '\0';
#if defined(CONFIG_OS_WINDOWS)
        // convert buf to ansi string
        if (!baseline)
        {
            size_t len = n / 2 + 1;
            char* cpBuf = (char*)PAL_Malloc(len);
            buf[n + 1] = '\0';
            if (cpBuf == NULL) return false;
            StrWcslcpy(cpBuf, (ZChar*)buf, len);
            str += cpBuf;
            PAL_Free(cpBuf);
        }
        else
            str += buf;
#else
        str += buf;
#endif
    }

    fclose(is);

    // Remove carriage-returns (Ctrl-M) characters:

    strOut.clear();
    strOut.reserve(str.size());

    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] != '\r')
            strOut += str[i];
    }

    return true;
}

static bool InhaleTmpFile(const char* file, string& str)
{
    char path[PAL_MAX_PATH_SIZE];
    return Inhale(TempPath(path, file), str, false);
}

static bool InhaleTestFile(const char* file, string& str)
{
    char path[PAL_MAX_PATH_SIZE];

    Strlcpy(path, OMI_GetPath(ID_SRCDIR), sizeof(path));
    Strlcat(path, "/tests/cli/", sizeof(path));
    Strlcat(path, file, sizeof(path));

    return Inhale(path, str, true);
}

static int Exec(const MI_Char *cmd, string& out, string& err)
{
    MI_Char command[PAL_MAX_PATH_SIZE];
    vector<MI_Char*> args;
    MI_Char path1[PAL_MAX_PATH_SIZE];
    MI_Char path2[PAL_MAX_PATH_SIZE];

    Tcslcpy(command, cmd, sizeof(command)/sizeof(command[0]));

    if (!ParseCommandLine(command, args))
        return 1;

    // Capture stdout:
    args.push_back((MI_Char*)MI_T("--stdout"));
    args.push_back(TSTempPath(path1, "STDOUT"));

    // Capture stderr:
    args.push_back((MI_Char*)MI_T("--stderr"));
    args.push_back(TSTempPath(path2, "STDERR"));

    // usernmae and password (ignored by server, but should be provided)
    args.push_back((MI_Char*)MI_T("-u"));
    args.push_back((MI_Char*)MI_T("user"));
    args.push_back((MI_Char*)MI_T("-p"));
    args.push_back((MI_Char*)MI_T("pw"));

    args.push_back(NULL);

    MI_Char** argv = &args[0];
    int argc = int(args.size() - 1);

    int r = climain(argc, (const MI_Char**)argv);

    UT_ASSERT(InhaleTmpFile("STDOUT", out));
    UT_ASSERT(InhaleTmpFile("STDERR", err));

    NitsTraceExA("Out string is:-", NitsHere(), NitsAutomatic);
    NitsTraceExA(out.c_str(), NitsHere(), NitsAutomatic);
    NitsTraceExA("Err string is:-", NitsHere(), NitsAutomatic);
    NitsTraceExA(err.c_str(), NitsHere(), NitsAutomatic);

    return r;
}

#if !defined(CONFIG_ENABLE_WCHAR)
static uint WordCount(const string &output, const string &word)
{
    uint occurrences = 0;
    string::size_type start = 0;

    while ((start=output.find(word, start)) != string::npos)
    {
        ++occurrences;
        start += word.length();
    }

    return occurrences;
}
#endif

NitsSetup(TestCliSetup)
    StartServer();
NitsEndSetup

NitsSetup(TestCliSetupWsman)
    StartServerWsman();
NitsEndSetup

NitsCleanup(TestCliSetup)
    StopServer();
NitsEndCleanup

NitsCleanup(TestCliSetupWsman)
    StopServer();
NitsEndCleanup

// TODO: Re-enable fault sim on all tests. All the tests which are disabled for fault injection
// are hitting product code issues which cause crashes/hangs and 
// prevent them from passing successfully when run with fault injection

NitsTestWithSetup(TestOMICLI1, TestCliSetup)
{
    NitsDisableFaultSim;

    const MI_Char CMD[] = MI_T("omicli noop");
    string out;
    string err;

    UT_ASSERT(Exec(CMD, out, err) == 0);

    UT_ASSERT(out == "got noop response\n");
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI2, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli ei root/test MSFT_President"), out, err) == 0);
    string str;

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICL12.txt", expect));

    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI2_Sync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli -synchronous ei root/test MSFT_President"), out, err) == 0);
    string str;

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICL12.txt", expect));

    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI3, TestCliSetup)
{    
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli enc { X Array [ 1 2 3 ] }"), out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICL13.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI3_Sync, TestCliSetup)
{    
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli -synchronous enc { X Array [ 1 2 3 ] }"), out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICL13.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI4, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli gi root/test { MSFT_President Key 1 }"), 
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICL14.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI4_Sync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli -synchronous gi root/test { MSFT_President Key 1 }"), 
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICL14.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI5, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli ci -s root/test { MSFT_President Key 3 First John Last Smith }"),
        out, err) == MI_RESULT_NOT_SUPPORTED);

    UT_ASSERT(out == "");
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI5_Sync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli -synchronous ci -s root/test { MSFT_President Key 3 First John Last Smith }"),
        out, err) == MI_RESULT_NOT_SUPPORTED);

    UT_ASSERT(out == "");
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI6, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli -s mi root/test { MSFT_President Key 1 First Geo Last Washington }"),
        out, err) == MI_RESULT_NOT_SUPPORTED);

    UT_ASSERT(out == "");
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI6_Sync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli -synchronous -s mi root/test { MSFT_President Key 1 First Geo Last Washington }"),
        out, err) == MI_RESULT_NOT_SUPPORTED);

    UT_ASSERT(out == "");
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI7, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli ei test/cpp X_SmallNumber"), out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI7.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

/*
NitsTestWithSetup(TestOMICLI7_Sync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli -synchronous ei test/cpp X_SmallNumber"), out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI7.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest
*/

NitsTestWithSetup(TestOMICLI8, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli enc { Link Left { Gadget Key 1 } Right { Gadget Key 2 } }"), out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI8.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest


NitsTestWithSetup(TestOMICLI9, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli enc { Class1 Key1 Value1 Key2 Value2 Key3 Value3 }"), out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI9.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest


NitsTestWithSetup(TestOMICLI10, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli enc { W Left { X Key Hello } Right { Y Key { Z ID Mine } } }"), out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI10.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest


NitsTestWithSetup(TestOMICLI11, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(
        MI_T("omicli iv test/cpp { X_SmallNumber } SpellNumber { num 123 }"),
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI11.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI11_Sync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(
        MI_T("omicli -synchronous iv test/cpp { X_SmallNumber } SpellNumber { num 123 }"),
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI11.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI12, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(
        MI_T("omicli iv test/cpp { X_SmallNumber Number 135 } GetFactors"), 
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI12.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI12_Sync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(
        MI_T("omicli -synchronous iv test/cpp { X_SmallNumber Number 135 } GetFactors"), 
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI12.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI13, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli a test/cpp { MSFT_Person Key 1 }"), out, err) == 0);

    UT_ASSERT(out == "");
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI13_Sync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli -synchronous a test/cpp { MSFT_Person Key 1 }"), out, err) == 0);

    UT_ASSERT(out == "");
    UT_ASSERT(err == "");
}
NitsEndTest


NitsTestWithSetup(TestOMICLI14, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli a test/cpp { X_numberWorld Name theWorld }"),
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI14.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI14_Sync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli -synchronous a test/cpp { X_numberWorld Name theWorld }"),
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI14.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI15, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli r test/cpp { X_Profile InstanceID world } -rc X_NumberWorldConformsToProfile"), out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI15.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI15_Sync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli -synchronous r test/cpp { X_Profile InstanceID world } -rc X_NumberWorldConformsToProfile"), out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI15.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI16, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli ei root/cimv2 XYZ_Widget"), out, err) == 0);

    /* No way to compare since result contains current timestamp */
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI16_Sync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli -synchronous ei root/cimv2 XYZ_Widget"), out, err) == 0);

    /* No way to compare since result contains current timestamp */
    UT_ASSERT(err == "");
}
NitsEndTest


NitsTestWithSetup(TestOMICLI17, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli -s ci root/cimv2 { XYZ_Widget SerialNumber 3 Colors [ Red Green Blue ]  }"),
        out, err) == MI_RESULT_NOT_SUPPORTED);

    UT_ASSERT(out == "");
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI17_Sync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli -synchronous -s ci root/cimv2 { XYZ_Widget SerialNumber 3 Colors [ Red Green Blue ]  }"),
        out, err) == MI_RESULT_NOT_SUPPORTED);

    UT_ASSERT(out == "");
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI18, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli ei root/test MSFT_VicePresident"), out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI18.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI18_Sync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli -synchronous ei root/test MSFT_VicePresident"), out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI18.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI19, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli gi root/test { MSFT_VicePresident Key 2 }"), 
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI19.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI19_Sync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli -synchronous gi root/test { MSFT_VicePresident Key 2 }"), 
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI19.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI20, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(
        MI_T("omicli iv test/cpp { X_Dog } Fight { CatsIn [ { X_Cat Key 1001 } ] }"),
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI20.txt", expect));

    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI20_Sync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(
        MI_T("omicli -synchronous iv test/cpp { X_Dog } Fight { CatsIn [ { X_Cat Key 1001 } ] }"),
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI20.txt", expect));

    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI21, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(
        MI_T("omicli --querylang WQL --queryexpr \"SELECT * FROM X_HugeNumber\" ei test/cpp X_HugeNumber"),
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI21.txt", expect));

    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI21_Sync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(
        MI_T("omicli -synchronous --querylang WQL --queryexpr \"SELECT * FROM X_HugeNumber\" ei test/cpp X_HugeNumber"),
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI21.txt", expect));

    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI22, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli gc test/cpp X_SmallNumber"), out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI22.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

NitsTestWithSetup(TestOMICLI22_Sync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    UT_ASSERT(Exec(MI_T("omicli -synchronous gc test/cpp X_SmallNumber"), out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI22.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}
NitsEndTest

// Wsman client does not support wide chars right now 
#if !defined(CONFIG_ENABLE_WCHAR)
NitsTestWithSetup(TestOMICLI23_CreateInstanceWsman, TestCliSetupWsman)
{
    NitsDisableFaultSim;

    string out;
    string err;
    NitsCompare(
        Exec(MI_T("omicli ci --hostname localhost -u test -p password --httpport 5985 --httpsport 5986 test/cpp { MSFT_Person Key 8 Species monster }"), 
             out, err), 0, MI_T("Omicli error"));

    string expect;
    NitsCompare(InhaleTestFile("TestOMICLI23.txt", expect), true, MI_T("Inhale failure"));
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI23_CreateInstanceWsmanSync, TestCliSetupWsman)
{
    NitsDisableFaultSim;

    string out;
    string err;
    NitsCompare(
        Exec(MI_T("omicli ci -synchronous --hostname localhost -u test -p password --httpport 5985 --httpsport 5986 test/cpp { MSFT_Person Key 8 Species monster }"), 
             out, err), 0, MI_T("Omicli error"));

    string expect;
    NitsCompare(InhaleTestFile("TestOMICLI23.txt", expect), true, MI_T("Inhale failure"));
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI24_DeleteInstanceWsman, TestCliSetupWsman)
{
    NitsDisableFaultSim;

    string out;
    string err;
    NitsCompare(
        Exec(MI_T("omicli di --hostname localhost -u test -p password --httpport 5985 --httpsport 5986 test/cpp { X_SmallNumber Number 9 }"), 
             out, err), 0, MI_T("Omicli error"));

    string expect;
    NitsCompare(out == "", true, MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI24_DeleteInstanceWsmanSync, TestCliSetupWsman)
{
    NitsDisableFaultSim;

    string out;
    string err;
    NitsCompare(
        Exec(MI_T("omicli di -synchronous --hostname localhost -u test -p password --httpport 5985 --httpsport 5986 test/cpp { X_SmallNumber Number 9 }"), 
             out, err), 0, MI_T("Omicli error"));

    string expect;
    NitsCompare(out == "", true, MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI25_GetInstanceWsman, TestCliSetupWsman)
{
    NitsDisableFaultSim;

    string out;
    string err;
    NitsCompare(
        Exec(MI_T("omicli gi --hostname localhost -u test -p password --httpport 5985 --httpsport 5986 root/test { MSFT_President Key 1 }"), 
             out, err), 0, MI_T("Omicli error"));

    string expect;
    NitsCompare(InhaleTestFile("TestOMICLI25.txt", expect), true, MI_T("Inhale failure"));
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI25_GetInstanceWsmanSync, TestCliSetupWsman)
{
    NitsDisableFaultSim;

    string out;
    string err;
    NitsCompare(
        Exec(MI_T("omicli gi -synchronous --hostname localhost -u test -p password --httpport 5985 --httpsport 5986 root/test { MSFT_President Key 1 }"), 
             out, err), 0, MI_T("Omicli error"));

    string expect;
    NitsCompare(InhaleTestFile("TestOMICLI25.txt", expect), true, MI_T("Inhale failure"));
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI26_InvokeWsman, TestCliSetupWsman)
{
    NitsDisableFaultSim;

    string out;
    string err;
    NitsCompare(
        Exec(MI_T("omicli iv --hostname localhost -u test -p password --httpport 5985 --httpsport 5986 test/cpp { X_SmallNumber } SpellNumber { num 123 }"),
             out, err), 0, MI_T("Omicli error")); 

    string expect;
    NitsCompare(InhaleTestFile("TestOMICLI26.txt", expect), true, MI_T("Inhale failure"));
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI26_InvokeWsmanSync, TestCliSetupWsman)
{
    NitsDisableFaultSim;

    string out;
    string err;
    NitsCompare(
        Exec(MI_T("omicli iv -synchronous --hostname localhost -u test -p password --httpport 5985 --httpsport 5986 test/cpp { X_SmallNumber } SpellNumber { num 123 }"),
             out, err), 0, MI_T("Omicli error")); 

    string expect;
    NitsCompare(InhaleTestFile("TestOMICLI26.txt", expect), true, MI_T("Inhale failure"));
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI27_EnumerateWsman, TestCliSetupWsman)
{
    NitsDisableFaultSim;

    string out;
    string err;
    NitsCompare(
        Exec(MI_T("omicli ei --hostname localhost -u test -p password --httpport 5985 --httpsport 5986 root/cimv2 X_SmallNumber"),
             out, err), 0, MI_T("Omicli error")); 

    uint instanceCount = WordCount(out, "X_SmallNumber");
    NitsCompare(instanceCount, 1000, MI_T("Incorrect number of instances"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI27_EnumerateWsmanSync, TestCliSetupWsman)
{
    NitsDisableFaultSim;

    string out;
    string err;
    NitsCompare(
        Exec(MI_T("omicli ei -synchronous --hostname localhost -u test -p password --httpport 5985 --httpsport 5986 root/cimv2 X_SmallNumber"),
             out, err), 0, MI_T("Omicli error")); 

    uint instanceCount = WordCount(out, "X_SmallNumber");
    NitsCompare(instanceCount, 1000, MI_T("Incorrect number of instances"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI28_FaultWsman, TestCliSetupWsman)
{
    NitsDisableFaultSim;

    string out;
    string err;
    NitsCompare(
        Exec(MI_T("omicli ei --hostname localhost -u test -p password --httpport 5985 --httpsport 5986 root/cimv2 President"),
             out, err), 5, MI_T("Omicli error")); 

    string expect;
    NitsCompare(InhaleTestFile("TestOMICLI28.txt", expect), true, MI_T("Inhale failure"));
    NitsCompareString(err.c_str(), expect.c_str(), MI_T("Error mismatch"));
    NitsCompare(out == "", true, MI_T("Output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI29_IdWsman, TestCliSetupWsman)
{
    NitsDisableFaultSim;

    string out;
    string err;
    NitsCompare(
        Exec(MI_T("omicli id --hostname localhost -u test -p password"),
             out, err), 0, MI_T("Omicli error")); 

    string expect;
    // Can't really compare output, since each installation has unique values
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

#if !defined(aix)
/* 
 * deactivated these tests on aix because they hang. Thatg is under investigation 
 */

NitsTestWithSetup(TestOMICLI30_EnumerateWsmanSingleElement, TestCliSetupWsman)
{
    NitsDisableFaultSim;

    string out;
    string err;
    NitsCompare(
        Exec(MI_T("omicli ei --maxenvsize 8 --maxelements 1 --hostname localhost -u test -p password --httpport 5985 --httpsport 5986 root/cimv2 X_SmallNumber"),
             out, err), 0, MI_T("Omicli error")); 

    uint instanceCount = WordCount(out, "X_SmallNumber");
    NitsCompare(instanceCount, 1000, MI_T("Incorrect number of instances"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest


NitsTestWithSetup(TestOMICLI30_EnumerateWsmanMediumElements, TestCliSetupWsman)
{
    NitsDisableFaultSim;

    string out;
    string err;
    NitsCompare(
        Exec(MI_T("omicli ei --maxenvsize 50 --maxelements 20 --hostname localhost -u test -p password --httpport 5985 --httpsport 5986 root/cimv2 X_SmallNumber"),
             out, err), 0, MI_T("Omicli error")); 

    uint instanceCount = WordCount(out, "X_SmallNumber");
    NitsCompare(instanceCount, 1000, MI_T("Incorrect number of instances"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI30_EnumerateWsmanMaxElements, TestCliSetupWsman)
{
    NitsDisableFaultSim;

    string out;
    string err;
    NitsCompare(
        Exec(MI_T("omicli ei --maxenvsize 500 --maxelements 2000 --hostname localhost -u test -p password --httpport 5985 --httpsport 5986 root/cimv2 X_SmallNumber"),
             out, err), 0, MI_T("Omicli error")); 

    uint instanceCount = WordCount(out, "X_SmallNumber");
    NitsCompare(instanceCount, 1000, MI_T("Incorrect number of instances"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

#endif
