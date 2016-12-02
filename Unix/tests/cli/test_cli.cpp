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
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
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
#include <base/pidfile.h>
#include <base/paths.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

MI_Char s_socketFile[PAL_MAX_PATH_SIZE];
char s_socketFile_a[PAL_MAX_PATH_SIZE];

#define MAX_SERVER_ARGS 20

extern "C"
{
extern int climain(int argc, const MI_Char* argv[]);
}

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 28718)
#endif

namespace
{
    char httpPort[32];
    char httpsPort[32];
    const char *omiUser;
    const char *omiPassword;
    const char *sudoPath;
    Process serverProcess;
    bool serverStarted;
    const char *ntlmFile;
    const char *ntlmDomain;
    bool travisCI;
}

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

static int StartServer()
{
    const char* path = OMI_GetPath(ID_SERVERPROGRAM);
    const char* argv[MAX_SERVER_ARGS];
    std::string v;
    uint args = 0;
    serverStarted = true;
    travisCI = false;
#if defined(TRAVIS_CI)
    travisCI = true;
#endif

    Snprintf(httpPort, sizeof(httpPort),"%d", ut::getUnittestPortNumberWSMANHTTP());
    Snprintf(httpsPort, sizeof(httpsPort),"%d", ut::getUnittestPortNumberWSMANHTTPS());

    Strlcpy(s_socketFile_a, OMI_GetPath(ID_SOCKETFILE), sizeof(s_socketFile_a)/sizeof(s_socketFile_a[0]));
    TcsStrlcpy(s_socketFile, s_socketFile_a, sizeof(s_socketFile)/sizeof(s_socketFile[0]));

    if (ut::testGetAttr("skipServer", v))
        return 0;

    argv[args++] = path;
    argv[args++] = "--rundir";
#if defined(CONFIG_OS_WINDOWS)
    argv[args++] = "..";
#else
    argv[args++] = OMI_GetPath(ID_PREFIX);
#endif
    argv[args++] = "--ignoreAuthentication";
    argv[args++] = "--socketfile";
    argv[args++] = s_socketFile_a;
    argv[args++] = "--httpport";
    argv[args++] = httpPort;
    argv[args++] = "--httpsport";
    argv[args++] = httpsPort;
    argv[args++] = "--livetime";
    argv[args++] = "300";

    argv[args++] = "--loglevel";
    argv[args++] = Log_GetLevelString(Log_GetLevel());
    argv[args++] = NULL;

    if (args > MAX_SERVER_ARGS)
        return -1;

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

static int StartServerSudo()
{
    const char* path = OMI_GetPath(ID_SERVERPROGRAM);
    std::string v;
    const int max_buf_size = 64;

    omiUser = std::getenv("OMI_USER");
    omiPassword = std::getenv("OMI_PASSWORD");
    sudoPath = std::getenv("SUDO_PATH");
    ntlmFile = std::getenv("NTLM_USER_FILE");
    ntlmDomain = std::getenv("NTLM_DOMAIN");

    const char *home = std::getenv("HOME");

    travisCI = false;
#if defined(TRAVIS_CI)
    travisCI = true;
#endif

    MI_Char userString[max_buf_size];
    MI_Char passwordString[max_buf_size];
        

    if (!omiUser || !omiPassword || !ntlmFile)
    {
        serverStarted = false;
        NitsCompare(serverStarted, true, MI_T("Required environment variables not found."));
        return -1;
    }
    else
    {
        serverStarted = true;
    }

    if (!sudoPath)
        sudoPath = "/usr/bin/sudo";

    TcsStrlcpy(userString, omiUser, max_buf_size);
    TcsStrlcpy(passwordString, omiPassword, max_buf_size);
        
    Snprintf(httpPort, sizeof(httpPort),"%d", ut::getUnittestPortNumberWSMANHTTP());
    Snprintf(httpsPort, sizeof(httpsPort),"%d", ut::getUnittestPortNumberWSMANHTTPS());

    Strlcpy(s_socketFile_a, OMI_GetPath(ID_SOCKETFILE), sizeof(s_socketFile_a)/sizeof(s_socketFile_a[0]));
    TcsStrlcpy(s_socketFile, s_socketFile_a, sizeof(s_socketFile)/sizeof(s_socketFile[0]));

    if (ut::testGetAttr("skipServer", v))
        return 0;

    uint args = 0;
    const char* argv[MAX_SERVER_ARGS];

#if defined(CONFIG_OS_WINDOWS)
    argv[args++] = path;
    argv[args++] = "--rundir";
    argv[args++] = "..";
    argv[args++] = "--socketfile";
    argv[args++] = s_socketFile_a;
    argv[args++] = "--httpport";
    argv[args++] = httpPort;
    argv[args++] = "--httpsport";
    argv[args++] = httpsPort;
    argv[args++] = "--livetime";
    argv[args++] = "300";
    argv[args++] = "--loglevel";
    argv[args++] = Log_GetLevelString(Log_GetLevel());
    argv[args++] = NULL;
#else
    string executeFile = home;
    executeFile += "/omi_execute.sh";

    std::ofstream ofs;
    ofs.open(executeFile.c_str(), std::ofstream::out | std::ofstream::trunc);
    if (ofs.fail())
    {
        std::cout << "Unable to open " << executeFile << std::endl;
        return -1;
    }

    ofs << "NTLM_USER_FILE=" << ntlmFile << std::endl;
    ofs << "export NTLM_USER_FILE" << std::endl;

    stringstream ss;
    ss << path;
    ss << " --rundir ";
    ss << OMI_GetPath(ID_PREFIX);
    ss << " --socketfile ";
    ss <<  s_socketFile_a;
    ss << " --httpport ";
    ss << httpPort;
    ss << " --httpsport ";
    ss << httpsPort;
    ss << " --livetime ";
    ss << "300";
    ss << " --loglevel ";
    ss << Log_GetLevelString(Log_GetLevel());
    ofs << ss.str() << std::endl;
    ofs.close();

    argv[args++] = sudoPath;
    argv[args++] = "/bin/sh";
    argv[args++] = executeFile.c_str();
    argv[args++] = NULL;
#endif

    if (args > MAX_SERVER_ARGS)
        return -1;

#if defined(CONFIG_OS_WINDOWS)
    if (Process_StartChild(&serverProcess, path, (char**)argv) != 0)
#else
    if (Process_StartChild(&serverProcess, sudoPath, (char**)argv) != 0)
#endif
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
            userString,
            passwordString,
            TIMEOUT))
        {
            connected = 1;
            break;
        }

        Sleep_Milliseconds(10);
    }

    UT_ASSERT(connected == 1);

    std::remove(executeFile.c_str());

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

static int StopServerSudo()
{
    std::string v;

    if (ut::testGetAttr("skipServer", v))
        return 0;

#if defined(CONFIG_OS_WINDOWS)
    if (Process_StopChild(&serverProcess) != 0)
        return -1;
#else
    if (serverStarted)
    {
        uint args = 0;
        const char* argv[MAX_SERVER_ARGS];
        std::stringstream pidStr;
        int pid;
        Process killProcess;
        int status;
        int numWaits = 0;

        if (PIDFile_Read(&pid) != 0)
            return -1;

        pidStr << pid;

        argv[args++] = sudoPath;
        argv[args++] = "kill";
        argv[args++] = "-s";
        argv[args++] = "SIGTERM";
        argv[args++] = pidStr.str().c_str();
        argv[args++] = NULL;

        if (Process_StartChild(&killProcess, sudoPath, (char**)argv) != 0)
            return -1;
        
try_again:
        /* Wait for original process to go */
        pid_t p = waitpid(pid, &status, 0);
        if (p == -1)
        {
            if (errno == ECHILD)
                goto cleanup;

            // EINTR is common in waitpid() and doesn't necessarily indicate failure.
            //       Give the system 10 times to see if the pid cleanly exits.
            if (10 < numWaits && errno == EINTR)
            {
                numWaits++;
                Sleep_Milliseconds(10);
                goto try_again;
            }

            return -1;
        }

    }
#endif

cleanup:
    // To allow pid file to be deleted
    Sleep_Milliseconds(50);

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
    NitsCompare(StartServer(), 0, MI_T("Failed to start omiserver"));;
NitsEndSetup

NitsCleanup(TestCliSetup)
    NitsCompare(StopServer(), 0, MI_T("Failed to stop omiserver"));;
NitsEndSetup

NitsSetup(TestCliSetupSudo)
    NitsCompare(StartServerSudo(), 0, MI_T("Failed to sudo start omiserver"));
NitsEndSetup

NitsCleanup(TestCliSetupSudo)
    NitsCompare(StopServerSudo(), 0, MI_T("Failed to stop the sudo start omiserver"));
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
NitsTestWithSetup(TestOMICLI23_CreateInstanceWsman, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli ci --hostname localhost -u test -p password --port %T test/cpp { MSFT_Person Key 8 Species monster }"),
             httpPort);
    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    string expect;
    NitsCompare(InhaleTestFile("TestOMICLI23.txt", expect), true, MI_T("Inhale failure"));
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI23_CreateInstanceWsmanSync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli ci -synchronous --hostname localhost -u test -p password --port %T test/cpp { MSFT_Person Key 8 Species monster }"),
             httpPort);
    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    string expect;
    NitsCompare(InhaleTestFile("TestOMICLI23.txt", expect), true, MI_T("Inhale failure"));
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI24_DeleteInstanceWsman, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli di --hostname localhost -u test -p password --port %T test/cpp { X_SmallNumber Number 9 }"),
             httpPort);

    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    string expect;
    NitsCompare(out == "", true, MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI24_DeleteInstanceWsmanSync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli di -synchronous --hostname localhost -u test -p password --port %T test/cpp { X_SmallNumber Number 9 }"),
             httpPort);

    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    string expect;
    NitsCompare(out == "", true, MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI25_GetInstanceWsman, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli gi --hostname localhost -u test -p password --port %T root/test { MSFT_President Key 1 }"),
             httpPort);

    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    string expect;
    NitsCompare(InhaleTestFile("TestOMICLI25.txt", expect), true, MI_T("Inhale failure"));
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI25_GetInstanceWsmanHttp, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli gi --encryption http --hostname localhost -u test -p password --port %T root/test { MSFT_President Key 1 }"),
             httpPort);

    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    string expect;
    NitsCompare(InhaleTestFile("TestOMICLI25.txt", expect), true, MI_T("Inhale failure"));
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI25_GetInstanceWsmanHttps, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli gi --encryption https --hostname localhost -u test -p password --port %T root/test { MSFT_President Key 1 }"),
             httpsPort);

    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    string expect;
    NitsCompare(InhaleTestFile("TestOMICLI25.txt", expect), true, MI_T("Inhale failure"));
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI25_GetInstanceWsmanNone, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli gi --encryption none --hostname localhost -u test -p password --port %T root/test { MSFT_President Key 1 }"),
             httpPort);

    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    string expect;
    NitsCompare(InhaleTestFile("TestOMICLI25.txt", expect), true, MI_T("Inhale failure"));
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI25_GetInstanceWsmanSync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli gi -synchronous --hostname localhost -u test -p password --port %T root/test { MSFT_President Key 1 }"),
             httpPort);

    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    string expect;
    NitsCompare(InhaleTestFile("TestOMICLI25.txt", expect), true, MI_T("Inhale failure"));
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI25_GetInstanceWsmanBasicAuth, TestCliSetupSudo)
{
    if (serverStarted)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --hostname localhost --auth Basic -u %T -p %T --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 omiUser,
                 omiPassword,
                 httpPort);

        NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

        string expect;
        NitsCompare(InhaleTestFile("TestOMICLI25.txt", expect), true, MI_T("Inhale failure"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompare(err == "", true, MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI25_GetInstanceWsmanFailBasicAuth, TestCliSetupSudo)
{
    if (serverStarted)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --hostname localhost --auth Basic -u %T -p %T2 --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 omiUser,
                 omiPassword,
                 httpPort);

        string expect = "omicli: result: MI_RESULT_ACCESS_DENIED\n";
        NitsCompare(Exec(buffer, out, err), 2, MI_T("Omicli error"));
        NitsCompareString(out.c_str(), "", MI_T("Output mismatch"));
        NitsCompareString(err.c_str(), expect.c_str(), MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI25_GetInstanceWsmanNegotiateAuth, TestCliSetupSudo)
{
    if (serverStarted && ntlmFile && ntlmDomain && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --hostname localhost --auth NegoWithCreds -u %T\\%T -p %T --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 ntlmDomain,
                 omiUser,
                 omiPassword,
                 httpPort);

        NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

        string expect;
        NitsCompare(InhaleTestFile("TestOMICLI25.txt", expect), true, MI_T("Inhale failure"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompare(err == "", true, MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        NitsCompare(1, 0, MI_T("test did not run"));
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI25_GetInstanceWsmanFailNegotiateAuth, TestCliSetupSudo)
{
    if (serverStarted && ntlmFile && ntlmDomain && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --hostname localhost --auth NegoWithCreds -u %T\\%T -p %T2 --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 ntlmDomain,
                 omiUser,
                 omiPassword,
                 httpPort);

        string expect = "omicli: result: MI_RESULT_ACCESS_DENIED\n";
        NitsCompare(Exec(buffer, out, err), 2, MI_T("Omicli error"));
        NitsCompareString(out.c_str(), "", MI_T("Output mismatch"));
        NitsCompareString(err.c_str(), expect.c_str(), MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI26_InvokeWsman, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli iv --hostname localhost -u test -p password --port %T test/cpp { X_SmallNumber } SpellNumber { num 123 }"),
             httpPort);

    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    string expect;
    NitsCompare(InhaleTestFile("TestOMICLI26.txt", expect), true, MI_T("Inhale failure"));
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI26_InvokeWsmanSync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli iv -synchronous --hostname localhost -u test -p password --port %T test/cpp { X_SmallNumber } SpellNumber { num 123 }"),
             httpPort);

    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    string expect;
    NitsCompare(InhaleTestFile("TestOMICLI26.txt", expect), true, MI_T("Inhale failure"));
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI27_EnumerateWsman, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli ei --hostname localhost -u test -p password --port %T root/cimv2 X_SmallNumber"),
             httpPort);

    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    uint instanceCount = WordCount(out, "X_SmallNumber");
    NitsCompare(instanceCount, 1000, MI_T("Incorrect number of instances"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI27_EnumerateWsmanSync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli ei -synchronous --hostname localhost -u test -p password --port %T root/cimv2 X_SmallNumber"),
             httpPort);

    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    uint instanceCount = WordCount(out, "X_SmallNumber");
    NitsCompare(instanceCount, 1000, MI_T("Incorrect number of instances"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI28_FaultWsman, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli ei --hostname localhost -u test -p password --port %T root/cimv2 President"),
             httpPort);

    NitsCompare(Exec(buffer, out, err), 5, MI_T("Omicli error"));

    string expect;
    NitsCompare(InhaleTestFile("TestOMICLI28.txt", expect), true, MI_T("Inhale failure"));
    NitsCompareString(err.c_str(), expect.c_str(), MI_T("Error mismatch"));
    NitsCompare(out == "", true, MI_T("Output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI29_IdWsman, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli id --hostname localhost -u test -p password --port %T"),
             httpPort);

    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    string expect;
    // Can't really compare output, since each installation has unique values
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

#if !defined(aix)
/* 
 * deactivated these tests on aix because they hang. Thatg is under investigation 
 */

NitsTestWithSetup(TestOMICLI30_EnumerateWsmanSingleElement, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli ei --maxenvsize 8 --maxelements 1 --hostname localhost -u test -p password --port %T root/cimv2 MSFT_President"),
             httpPort);

    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    uint instanceCount = WordCount(out, "MSFT_President");
    NitsCompare(instanceCount, 2, MI_T("Incorrect number of instances"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI30_EnumerateWsmanMediumElements, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli ei --maxenvsize 50 --maxelements 30 --hostname localhost -u test -p password --port %T root/cimv2 X_SmallNumber"),
             httpPort);

    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    uint instanceCount = WordCount(out, "X_SmallNumber");
    NitsCompare(instanceCount, 1000, MI_T("Incorrect number of instances"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI30_EnumerateWsmanMaxElements, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli ei --maxenvsize 500 --maxelements 2000 --hostname localhost -u test -p password --port %T root/cimv2 X_SmallNumber"),
             httpPort);

    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    uint instanceCount = WordCount(out, "X_SmallNumber");
    NitsCompare(instanceCount, 1000, MI_T("Incorrect number of instances"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

#endif /* !defined aix */

NitsTestWithSetup(TestOMICLI31_WQLWsman, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli wql --hostname localhost -u test -p password --port %T root/cimv2 \"SELECT * from X_SmallNumber WHERE Number > 800\""),
             httpPort);

    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    uint instanceCount = WordCount(out, "X_SmallNumber");
    NitsCompare(instanceCount, 199, MI_T("Incorrect number of instances"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

NitsTestWithSetup(TestOMICLI31_WQLWsmanSync, TestCliSetup)
{
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli wql -synchronous --hostname localhost -u test -p password --port %T root/cimv2 \"SELECT * from X_SmallNumber WHERE Number > 800\""),
             httpPort);

    NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

    uint instanceCount = WordCount(out, "X_SmallNumber");
    NitsCompare(instanceCount, 199, MI_T("Incorrect number of instances"));
    NitsCompare(err == "", true, MI_T("Error output mismatch"));
}
NitsEndTest

#endif
