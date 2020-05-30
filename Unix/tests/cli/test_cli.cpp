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
#include <base/paths.h>
#include <base/process.h>
#include <pal/sleep.h>
#include <base/paths.h>
#include <pal/format.h>
#include <pal/dir.h>
#include <pal/strings.h>
#include <pal/file.h>
#include <pal/host.h>
#include <omiclient/client.h>
#include <base/log.h>
#include <base/pidfile.h>
#include <base/paths.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

/* These are not used. They are required for linking */
FILE *g_logfile;
Batch* g_batch;

/* so we can use this:          */
extern "C" void KillOldServerInstance();

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
    const char *omiUser    = NULL;
    const char *omiPassword = NULL;
    const char *sudoPath    = NULL;
    Process serverProcess;
    bool startServer       = false;
    char *ntlmFile   = NULL;
    char *ntlmDomain = NULL;
    char *krb5Realm  = NULL;
    char *hostFqdn   = NULL;
    bool travisCI          = false;
    bool pamConfigured     = false;
    bool runNtlmTests      = false;
    bool runKrbTests       = false;
}



// Post Mortem log handling. Maybe should be in nits base. 

// Delete everything in the log directory. Each test should have a clean test directory.
// It is up to the individual components to recreate their log files, so this should 
// only be done with omi client, server, and agents not running
void LogDir_Reset()
{
    string logdirname(OMI_GetPath(ID_LOGDIR));
    Dir *logdir = Dir_Open(logdirname.c_str());
    DirEnt *ent = Dir_Read(logdir);

    logdirname.append("/");
    while (ent)
    {
        string filepath(logdirname);
        filepath.append(ent->name);

        if (!Isdir(filepath.c_str())) {
            // Remove the file
            File_Remove(filepath.c_str());
        }
        ent = Dir_Read(logdir);
    }

    Dir_Close(logdir);
}

void LogDir_DumpIfNeeded(FILE *f, TestSystem::Result rslt)
{
    static const char LOGFILE_START_MARKER[] = "<<<<<<<<<<<<<<<<<<<< %s ==================\n";
    static const char LOGFILE_END_MARKER[]   = ">>>>>>>>>>>>>>>>>>>> %s ==================\n";


    switch(rslt) {
    case TestSystem::Killed:         //The test took too long and was killed.
    case TestSystem::Failed:         //An assert failed, but no test errors.
    case TestSystem::Error:          //Test code is not working properly.
        {
            string logdirname(OMI_GetPath(ID_LOGDIR));
            Dir *logdir = Dir_Open(logdirname.c_str());
            DirEnt *ent = Dir_Read(logdir);
        
            logdirname.append("/");
            while (ent)
            {
                string filepath(logdirname);
                filepath.append(ent->name);
        
                if (!Isdir(filepath.c_str())) {
                    fprintf(stderr, LOGFILE_START_MARKER, ent->name);

                    // Print the file to stderr
                    FILE* fp = File_Open(filepath.c_str(), "r");

                 
                    if (fp)
                    {
                        (void)fseek(fp, 0, SEEK_END);
                        ssize_t filesize = ftell(fp);
                        if (filesize > 4096)
                        {
                            (void)fseek(fp, -4096, SEEK_END);
                        }
                        else
                        {
                            (void)fseek(fp, 0, SEEK_SET);
                        }
                        if (filesize > 0 )
                        {
                            char *buf = (char*)PAL_Malloc(filesize);
                            (void)/*ssize_t n =*/ fread(buf, filesize, 1, fp);
                            fprintf(stderr, "%s", buf);
                            PAL_Free(buf);
                        }

                        File_Close(fp);
                    }

                    fprintf(stderr, LOGFILE_END_MARKER, ent->name);
                }
                ent = Dir_Read(logdir);
            }

            Dir_Close(logdir);
        }
        break;

    default:
        break;
    }
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
    startServer = true;
    travisCI = false;
#if defined(TRAVIS_CI)
    travisCI = true;
#endif

    KillOldServerInstance();

    Snprintf(httpPort, sizeof(httpPort),"%d", ut::getUnittestPortNumberWSMANHTTP());
    Snprintf(httpsPort, sizeof(httpsPort),"%d", ut::getUnittestPortNumberWSMANHTTPS());

    Strlcpy(s_socketFile_a, OMI_GetPath(ID_SOCKETFILE), sizeof(s_socketFile_a)/sizeof(s_socketFile_a[0]));
    TcsStrlcpy(s_socketFile, s_socketFile_a, sizeof(s_socketFile)/sizeof(s_socketFile[0]));

    if (ut::testGetAttr("skipServer", v))
        return 0;

    argv[args++] = path;
    argv[args++] = "--rundir";
    argv[args++] = OMI_GetPath(ID_PREFIX);
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
    for (int i = 0; i < 200; i++)
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

        Sleep_Milliseconds(100);
    }

    UT_ASSERT(connected == 1);

    return 0;
}

static void ConfigurePAM()
{
    pamConfigured = true;

    uint args = 0;
    const char* argv[MAX_SERVER_ARGS];


    std::string pamScript = string(CONFIG_BINDIR);
    pamScript.erase(pamScript.find_last_of( '/'), std::string::npos);
    
    pamScript += "/installpam";

    argv[args++] = sudoPath;
    argv[args++] = pamScript.c_str();
    argv[args++] = NULL;

    int r = Process_StartChild(&serverProcess, sudoPath, (char**)argv);

    NitsCompare(r, 0, MI_T("Failed to execute PAM configuration script"));

    Sleep_Milliseconds(50);
}

static void VerifyEnvironmentVariables()
{
    omiUser = std::getenv("OMI_USER");
    omiPassword = std::getenv("OMI_PASSWORD");
    sudoPath = std::getenv("SUDO_PATH");
    char *ntlm_file = std::getenv("NTLM_USER_FILE");
    char *ntlm_domain = std::getenv("NTLM_DOMAIN");
    krb5Realm = std::getenv("OMI_KRB_TESTS_REALM");

    if (!hostFqdn)
    {
        hostFqdn = (char*)GetFullyQualifiedDomainName();
    }

    const char *ntlmSupportedPlatform = std::getenv("NTLM_SUPPORTED_PLATFORM");
    const char *krbTestsEnabled = std::getenv("OMI_KRB_RUN_TESTS");

    if (!hostFqdn) 
    {
        startServer = false;
        NitsCompare(startServer, true, MI_T("Required configuration for hosts fully qualified domain name not found."));
    }

    if (!omiUser || !omiPassword)
    {
        startServer = false;
        NitsCompare(startServer, true, MI_T("Required environment variables OMI_USER and OMI_PASSWORD not found."));
    }
    else
    {
        startServer = true;
        runNtlmTests = true;
    }

    if (!ntlmFile)
    {
        if (ntlm_file) 
        {
            ntlmFile = PAL_Strdup(ntlm_file);
        }
        else
        {
            ntlmFile = PAL_Strdup(CONFIG_CREDSDIR "/ntlm");
            setenv("NTLM_USER_FILE", ntlmFile, 1);
        }
    }

    if (!ntlmDomain)
    {
        if (ntlm_domain)
        {
            ntlmDomain = PAL_Strdup(ntlm_domain);
        }
        else
        {
            char buf[256] = {0};
            (void) gethostname(buf, 256);
            ntlmDomain = PAL_Strdup(buf);

            runNtlmTests = false;
        }
    }

    if (!ntlmSupportedPlatform)
    {
        runNtlmTests = CONFIG_SUPPORTS_NTLM;
    }
    else
    {
        runNtlmTests = (ntlmSupportedPlatform[0] == '1') ? true : false;
    }

    if (!runNtlmTests)
        std::cout << "Skipping NTLM tests..." << std::endl;

    if (!sudoPath)
    {
        std::cout << "Environment variable SUDO_PATH is not set. Assume '/usr/bin/sudo'" << std::endl;
        sudoPath = "/usr/bin/sudo";
    }

    if (!krbTestsEnabled || (strncasecmp(krbTestsEnabled, "true", 4) != 0))
    {
        runKrbTests = false;
    }
    else
    {
        runKrbTests = true;
    }

    if (!pamConfigured)
    {
        ConfigurePAM();
    }
}

static int StartServerSudo()
{
    const char* path = OMI_GetPath(ID_SERVERPROGRAM);
    std::string v;
    const int max_buf_size = 64;
    MI_Char userString[max_buf_size];
    MI_Char passwordString[max_buf_size];

    travisCI = false;
#if defined(TRAVIS_CI)
    travisCI = true;
    startServer = false;
    return 0;
#endif

    VerifyEnvironmentVariables();
    if (!startServer)
        return -1;

    KillOldServerInstance();

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

    stringstream efs;
    efs << CONFIG_TMPDIR;
    efs << "/omi_execute_";
    efs << rand() % 100000;
    efs << ".sh";
    string efsString = efs.str();   // This line needed by Ubuntu 16.04
    const char *executeFile = efsString.c_str();
    std::cout << "Execute file is: " << executeFile << std::endl;

    std::ofstream ofs;
    ofs.open(executeFile, std::ofstream::out | std::ofstream::trunc);
    if (ofs.fail())
    {
        std::cout << "Unable to open " << executeFile << std::endl;
        return -1;
    }

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

    // verify that file is ready
    int counter = 0;
    int max_tries = 25;

    std::ifstream ifs;
    ifs.open(executeFile);

    while (counter < max_tries && !ifs.good())
    {
        ifs.close();
        Sleep_Milliseconds(50);
        counter++;
        ifs.open(executeFile);
    };
    ifs.close();

    if (counter >= max_tries)
    {
        std::cout << "File " << executeFile << " takes too long to become ready." << std::endl;
        return -1;
    }

    argv[args++] = sudoPath;
    argv[args++] = "/bin/sh";
    argv[args++] = executeFile;
    argv[args++] = NULL;

    if (args > MAX_SERVER_ARGS)
        return -1;

    if (Process_StartChild(&serverProcess, sudoPath, (char**)argv) != 0)
        return -1;

    Sleep_Milliseconds(100);

    int connected = 0;

    // wait for server to start
    // trying to connect in a loop:
    // since connect may fail quickly if server is not running
    // keep doing it in  a loop
    for (int i = 0; i < 200; i++)
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

        Sleep_Milliseconds(100);
    }

    UT_ASSERT(connected == 1);

    std::remove(executeFile);

    std::cout << "Server started, its pid: " << (int)serverProcess.reserved << std::endl;
    
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
    uint args = 0;
    int status;

    const char* argv[MAX_SERVER_ARGS];

    if (ut::testGetAttr("skipServer", v))
        return 0;

    if (startServer)
    {
        std::stringstream pidStream;
        int pid;
        Process killProcess;
        int numWaits = 0;

        if (PIDFile_Read(&pid) != 0)
        {
            std::cout << "Cannot find server pid" << std::endl;
            return -1;
        }

        pidStream << pid;
        std::string pidStr = pidStream.str();

        argv[args++] = sudoPath;
        argv[args++] = "kill";
        argv[args++] = "-TERM";
        argv[args++] = pidStr.c_str();
        argv[args++] = NULL;

        std::cout << "Killing server process pid: " << pid << "..." << std::endl;
        if (Process_StartChild(&killProcess, sudoPath, (char**)argv) != 0)
            return -2;
        
try_again:
        /* Wait for original process to go */
        pid_t p = waitpid(pid, &status, 0);
        if (p == -1)
        {
            if (errno == ECHILD)
                goto cleanup;

            // EINTR is common in waitpid() and doesn't necessarily indicate failure.
            //       Give the system 10 times to see if the pid cleanly exits.
            if (25 < numWaits && errno == EINTR)
            {
                numWaits++;
                Sleep_Milliseconds(20);
                goto try_again;
            }

            return -3;
        }

    }

cleanup:
    // Just to be sure, clean up the pid file also
    args = 0;

    argv[args++] = sudoPath;
    argv[args++] = "rm";
    argv[args++] = "-f";
    argv[args++] = OMI_GetPath(ID_PIDFILE);
    argv[args++] = NULL;

    Process removePidFile;
    if (Process_StartChild(&removePidFile, sudoPath, (char**)argv) != 0)
        return -2;

    pid_t wpid;
    while ((wpid = wait(&status)) > 0);

    PAL_Free(hostFqdn);
    hostFqdn = NULL;

    PAL_Free(ntlmFile);
    ntlmFile = NULL;

    PAL_Free(ntlmDomain);
    ntlmDomain = NULL;

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
        ssize_t n = fread(buf, 1, sizeof(buf)-1, is);

        if (n <= 0)
            break;
        _Analysis_assume_(n<1023);
        buf[n] = '\0';
        str += buf;
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


static bool FileExists(const char *path)
{
    FILE* is = File_Open(path, "rb");
    if (!is)
        return false;
    return true;
}

// removes file if it exists
static void removeIfExist( const char* file )
{
    if ( access(file, F_OK) == 0 )
        UT_ASSERT( 0 == remove(file) );
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

NitsSetup(TestCliSetup)
    NitsCompare(StartServer(), 0, MI_T("Failed to start omiserver"));;
NitsEndSetup

NitsCleanup(TestCliSetup)
    NitsCompare(StopServer(), 0, MI_T("Failed to stop omiserver"));;
NitsEndSetup

NitsSetup(TestCliSetupSudo)
    //LogDir_Reset();
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

    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
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

    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
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
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
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
    NitsCompareSubstring(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
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
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
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
             MI_T("omicli gi --encryption none --hostname localhost -u test -p password --port %T root/test { MSFT_President Key 1 }"),
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
    if (startServer)
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
        if (travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI36_GetInstanceWsmanFailBasicAuthWithEncrypt, TestCliSetupSudo)
{
    if (runNtlmTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --encryption http --hostname %T --auth Basic -u %T -p %T --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 hostFqdn,
                 omiUser,
                 omiPassword,
                 httpPort);

        string expect = string("");
        string expected_err = string("omicli: result: MI_RESULT_ACCESS_DENIED\n");
        NitsCompare(InhaleTestFile("TestOMICLI36.txt", expect), true, MI_T("Inhale failure"));
        NitsCompare(Exec(buffer, out, err), 2, MI_T("Omicli error"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompareSubstring(err.c_str(), expected_err.c_str(), MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        if (!runNtlmTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest


NitsTestWithSetup(TestOMICLI25_AuthParamIgnoreCase, TestCliSetupSudo)
{
    if (startServer)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --hostname localhost --auth BASiC -u %T -p %T --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
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
        if (travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI33_GetInstanceWsmanFailBasicAuth, TestCliSetupSudo)
{
    if (startServer)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --encryption none --hostname localhost --auth Basic -u %T -p BadPassword --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 omiUser,
                 httpPort);

        string expect = string("");
        string expected_err = string("omicli: result: MI_RESULT_ACCESS_DENIED\nomicli: result: Basic Authorization failed for user");
        NitsCompare(InhaleTestFile("TestOMICLI33.txt", expect), true, MI_T("Inhale failure"));
        NitsCompare(Exec(buffer, out, err), 2, MI_T("Omicli error"));
        if (omiUser != string("omi_test"))
        {
            // replace all instances of omi_test with actual user name
            for (int i = expect.find("omi_test"); i >= 0; i = expect.find("omi_test"))
                expect.replace(i, 8, omiUser);
        }
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompareSubstring(err.c_str(), expected_err.c_str(), MI_T("Error output mismatch"));
    }
    else
    {
        if (travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI25_GetInstanceWsmanNegotiateAuth, TestCliSetupSudo)
{
    if (runNtlmTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --hostname %T --auth NegoWithCreds -u %T@%T -p %T --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 hostFqdn,
                 omiUser,
                 ntlmDomain,
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
        if (!runNtlmTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI35_GetInstanceWsmanFailNegotiateAuth, TestCliSetupSudo)
{
    if (runNtlmTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --hostname %T --auth NegoWithCreds -u %T\\%T -p BadPassword --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 hostFqdn,
                 ntlmDomain,
                 omiUser,
                 httpPort);

        string expect = string("");
        string expected_err = string("omicli: result: MI_RESULT_ACCESS_DENIED\nomicli: result: Authorization failed");
        NitsCompare(InhaleTestFile("TestOMICLI35.txt", expect), true, MI_T("Inhale failure"));
        NitsCompare(Exec(buffer, out, err), 2, MI_T("Omicli error"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompareSubstring(err.c_str(), expected_err.c_str(), MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        if (!runNtlmTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI25_GetInstanceWsmanNegotiateAuthSSL, TestCliSetupSudo)
{
    if (runNtlmTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --encryption https --hostname %T --auth NegoWithCreds -u %T\\%T -p %T --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 hostFqdn,
                 ntlmDomain,
                 omiUser,
                 omiPassword,
                 httpsPort);

        NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

        string expect;
        NitsCompare(InhaleTestFile("TestOMICLI25.txt", expect), true, MI_T("Inhale failure"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompare(err == "", true, MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        if (!runNtlmTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI35_GetInstanceWsmanFailNegotiateAuthSSL, TestCliSetupSudo)
{
    if (runNtlmTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --encryption https --hostname %T --auth NegoWithCreds -u %T\\%T -p BadPassword --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 hostFqdn,
                 ntlmDomain,
                 omiUser,
                 httpsPort);

        string expect = string("");
        string expected_err = string("omicli: result: MI_RESULT_ACCESS_DENIED\nomicli: result: Authorization failed");
        NitsCompare(InhaleTestFile("TestOMICLI35.txt", expect), true, MI_T("Inhale failure"));
        NitsCompare(Exec(buffer, out, err), 2, MI_T("Omicli error"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompareSubstring(err.c_str(), expected_err.c_str(), MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        if (!runNtlmTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI25_GetInstanceWsmanNegotiateAuthWithEncrypt, TestCliSetupSudo)
{
    if (runNtlmTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --encryption http --hostname %T --auth NegoWithCreds -u %T\\%T -p %T --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 hostFqdn,
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
        if (!runNtlmTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI35_GetInstanceWsmanFailNegotiateAuthWithEncrypt, TestCliSetupSudo)
{
    if (runNtlmTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --encryption http --hostname %T --auth NegoWithCreds -u %T\\%T -p BadPassword --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 hostFqdn,
                 ntlmDomain,
                 omiUser,
                 httpPort);

        string expect = string("");
        string expected_err = string("omicli: result: MI_RESULT_ACCESS_DENIED\nomicli: result: Authorization failed\n");
        NitsCompare(InhaleTestFile("TestOMICLI35.txt", expect), true, MI_T("Inhale failure"));
        NitsCompare(Exec(buffer, out, err), 2, MI_T("Omicli error"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompareSubstring(err.c_str(), expected_err.c_str(), MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        if (!runNtlmTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI25_GetInstanceWsmanNegotiateAuthNoEncrypt, TestCliSetupSudo)
{
    if (runNtlmTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --encryption none --hostname %T --auth NegoWithCreds -u %T\\%T -p %T --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 hostFqdn,
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
        if (!runNtlmTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI35_GetInstanceWsmanFailNegotiateAuthNoEncrypt, TestCliSetupSudo)
{
    if (runNtlmTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --encryption none --hostname %T --auth NegoWithCreds -u %T\\%T -p BadPassword --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 hostFqdn,
                 ntlmDomain,
                 omiUser,
                 httpPort);

        string expect = string("");
        string expected_err = string("omicli: result: MI_RESULT_ACCESS_DENIED\nomicli: result: Authorization failed");
        NitsCompare(InhaleTestFile("TestOMICLI35.txt", expect), true, MI_T("Inhale failure"));
        NitsCompare(Exec(buffer, out, err), 2, MI_T("Omicli error"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompareSubstring(err.c_str(), expected_err.c_str(), MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        if (!runNtlmTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
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
    NitsCompare(instanceCount, 5, MI_T("Incorrect number of instances"));
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

NitsTestWithSetup(TestOMICLI32_UserOption, TestCliSetup)
{
// Test to make sure that if -u USERNAME is not specified, it returns an error
    NitsDisableFaultSim;

    string out;
    string err;
    MI_Char buffer[1024];

    Stprintf(buffer, MI_COUNT(buffer),
             MI_T("omicli gi --hostname localhost --auth Basic -p %T --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
             omiPassword,
             httpPort);

    NitsCompare(Exec(buffer, out, err), 1, MI_T("Omicli error"));
}
NitsEndTest


NitsTestWithSetup(TestOMICLI36_GetInstanceWsmanKerberosAuth, TestCliSetupSudo)
{
    if (runKrbTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --hostname %T --auth Kerberos -u %T@%T -p %T --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 hostFqdn,
                 omiUser,
                 krb5Realm,
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
        if (!runKrbTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

#endif /* !defined aix */

NitsTestWithSetup(TestOMICLI42_EnumerateWsmanBasicAuthNoEncrypt, TestCliSetupSudo)
{
    if (startServer && !travisCI)
    {
        NitsDisableFaultSim;
    
        string out;
        string err;
        MI_Char buffer[1024];
    
        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli ei --maxelements 1 --encryption none --auth Basic  --hostname %T -u %T -p %T --port %T oop/requestor/test/cpp MSFT_President"),
                     hostFqdn,
                     omiUser,
                     omiPassword,
                     httpPort);
    
        NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));
        string expect;
        NitsCompare(InhaleTestFile("TestOMICLI42.txt", expect), true, MI_T("Inhale failure"));
    
        uint instanceCount = WordCount(out, "MSFT_President");
        NitsCompare(instanceCount, 5, MI_T("Incorrect number of instances"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompare(err == "", true, MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        if (travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest
NitsTestWithSetup(TestOMICLI42_EnumerateWsmanKerberosAuthEncrypt, TestCliSetupSudo)
{
    if (runKrbTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;
    
        string out;
        string err;
        MI_Char buffer[1024];
    
        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli ei --maxelements 1 --encryption http --auth Kerberos  --hostname %T -u %T@%T -p %T --port %T oop/requestor/test/cpp MSFT_President"),
                     hostFqdn,
                     omiUser,
                     krb5Realm,
                     omiPassword,
                     httpPort);
    
        NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));
        string expect;
        NitsCompare(InhaleTestFile("TestOMICLI42.txt", expect), true, MI_T("Inhale failure"));
    
        uint instanceCount = WordCount(out, "MSFT_President");
        NitsCompare(instanceCount, 5, MI_T("Incorrect number of instances"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompare(err == "", true, MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        if (!runKrbTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI42_EnumerateWsmanKerberosAuthNoEncrypt, TestCliSetupSudo)
{
    if (runKrbTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;
    
        string out;
        string err;
        MI_Char buffer[1024];
    
        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli ei --maxelements 1 --encryption none --auth Kerberos  --hostname %T -u %T@%T -p %T --port %T oop/requestor/test/cpp MSFT_President"),
                     hostFqdn,
                     omiUser,
                     krb5Realm,
                     omiPassword,
                     httpPort);
    
        NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));
        string expect;
        NitsCompare(InhaleTestFile("TestOMICLI42.txt", expect), true, MI_T("Inhale failure"));
    
        uint instanceCount = WordCount(out, "MSFT_President");
        NitsCompare(instanceCount, 5, MI_T("Incorrect number of instances"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompare(err == "", true, MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        if (!runKrbTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI42_EnumerateWsmanNegotiateAuthEncrypt, TestCliSetupSudo)
{
    if (runNtlmTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;
    
        string out;
        string err;
        MI_Char buffer[1024];
    
        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli ei --maxelements 1 --encryption http --auth NegoWithCreds --hostname %T -u %T@%T -p %T --port %T oop/requestor/test/cpp MSFT_President"),
                     hostFqdn,
                     omiUser,
                     ntlmDomain,
                     omiPassword,
                     httpPort);
    
        NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));
        string expect;
        NitsCompare(InhaleTestFile("TestOMICLI42.txt", expect), true, MI_T("Inhale failure"));
    
        uint instanceCount = WordCount(out, "MSFT_President");
        NitsCompare(instanceCount, 5, MI_T("Incorrect number of instances"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompare(err == "", true, MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        if (!runNtlmTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI42_EnumerateWsmanNegotiateAuthNoEncrypt, TestCliSetupSudo)
{
    if (runNtlmTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;
    
        string out;
        string err;
        MI_Char buffer[1024];
    
        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli ei --maxelements 1 --encryption none --auth NegoWithCreds --hostname %T -u %T@%T -p %T --port %T oop/requestor/test/cpp MSFT_President"),
                     hostFqdn,
                     omiUser,
                     ntlmDomain,
                     omiPassword,
                     httpPort);
    
        NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));
        string expect;
        NitsCompare(InhaleTestFile("TestOMICLI42.txt", expect), true, MI_T("Inhale failure"));
    
        uint instanceCount = WordCount(out, "MSFT_President");
        NitsCompare(instanceCount, 5, MI_T("Incorrect number of instances"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompare(err == "", true, MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        if (!runNtlmTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI37_GetInstanceWsmanFailKerberosAuth, TestCliSetupSudo)
{
    if (runKrbTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --hostname %T --auth Kerberos -u %T\\%T -p BadPassword --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 hostFqdn,
                 krb5Realm,
                 omiUser,
                 httpPort);

        string expect = string("");
        string expected_err = string("omicli: result: MI_RESULT_ACCESS_DENIED\n");
#if defined(is_macos)
        NitsCompare(InhaleTestFile("TestOMICLI37.mac.txt", expect), true, MI_T("Inhale failure"));
#else
        NitsCompare(InhaleTestFile("TestOMICLI37.txt", expect), true, MI_T("Inhale failure"));
#endif
        NitsCompare(Exec(buffer, out, err), 2, MI_T("Omicli error"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompareSubstring(err.c_str(), expected_err.c_str(), MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        if (!runKrbTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI38_GetInstanceWsmanKerberosAuthSSL, TestCliSetupSudo)
{
    if (runKrbTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --encryption https --hostname %T --auth Kerberos -u %T\\%T -p %T --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 hostFqdn,
                 krb5Realm,
                 omiUser,
                 omiPassword,
                 httpsPort);

        NitsCompare(Exec(buffer, out, err), 0, MI_T("Omicli error"));

        string expect;
        NitsCompare(InhaleTestFile("TestOMICLI25.txt", expect), true, MI_T("Inhale failure"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompare(err == "", true, MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        if (!runKrbTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI39_GetInstanceWsmanFailKerberosAuthSSL, TestCliSetupSudo)
{
    if (runKrbTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --encryption https --hostname %T --auth Kerberos -u %T\\%T -p BadPassword --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 hostFqdn,
                 krb5Realm,
                 omiUser,
                 httpsPort);

        string expect = string("");
        string expected_err = string("omicli: result: MI_RESULT_ACCESS_DENIED\n");
#if defined(is_macos)
        NitsCompare(InhaleTestFile("TestOMICLI37.mac.txt", expect), true, MI_T("Inhale failure"));
#else
        NitsCompare(InhaleTestFile("TestOMICLI37.txt", expect), true, MI_T("Inhale failure"));
#endif
        NitsCompare(Exec(buffer, out, err), 2, MI_T("Omicli error"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompareSubstring(err.c_str(), expected_err.c_str(), MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        if (!runKrbTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI40_GetInstanceWsmanKerberosAuthWithEncrypt, TestCliSetupSudo)
{

    /* Disabled until encrypt issues addressed */
#if defined(is_macos)
    if (false)
#else
    if (runKrbTests && startServer && !travisCI)
#endif
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --encryption http --hostname %T --auth Kerberos -u %T\\%T -p %T --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 hostFqdn,
                 krb5Realm,
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
        if (/*!runKrbTests || travisCI*/1)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI41_GetInstanceWsmanFailKerberosAuthWithEncrypt, TestCliSetupSudo)
{
    /* Disabled until encrypt issues addressed */
    if (runKrbTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --encryption http --hostname %T --auth Kerberos -u %T\\%T -p BadPassword --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 hostFqdn,
                 krb5Realm,
                 omiUser,
                 httpPort);

        string expect = string("");
        string expected_err = string("omicli: result: MI_RESULT_ACCESS_DENIED\n");
#if defined(is_macos)
        NitsCompare(InhaleTestFile("TestOMICLI37.mac.txt", expect), true, MI_T("Inhale failure"));
#else
        NitsCompare(InhaleTestFile("TestOMICLI37.txt", expect), true, MI_T("Inhale failure"));
#endif
        NitsCompare(Exec(buffer, out, err), 2, MI_T("Omicli error"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompareSubstring(err.c_str(), expected_err.c_str(), MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        if (/*!runKrbTests || travisCI*/1)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI44_GetInstanceWsmanKerberosAuthNoEncrypt, TestCliSetupSudo)
{
    if (runKrbTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --encryption none --hostname %T --auth Kerberos -u %T\\%T -p %T --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 hostFqdn,
                 krb5Realm,
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
        if (!runKrbTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI45_GetInstanceWsmanFailKerberosAuthNoEncrypt, TestCliSetupSudo)
{
    if (runKrbTests && startServer && !travisCI)
    {
        NitsDisableFaultSim;

        string out;
        string err;
        MI_Char buffer[1024];

        Stprintf(buffer, MI_COUNT(buffer),
                 MI_T("omicli gi --encryption none --hostname %T --auth Kerberos -u %T\\%T -p BadPassword --port %T oop/requestor/test/cpp { MSFT_President Key 1 }"),
                 hostFqdn,
                 krb5Realm,
                 omiUser,
                 httpPort);

        string expect = string("");
        string expected_err = string("omicli: result: MI_RESULT_ACCESS_DENIED\n");
#if defined(is_macos)
        NitsCompare(InhaleTestFile("TestOMICLI37.mac.txt", expect), true, MI_T("Inhale failure"));
#else
        NitsCompare(InhaleTestFile("TestOMICLI37.txt", expect), true, MI_T("Inhale failure"));
#endif
        NitsCompare(Exec(buffer, out, err), 2, MI_T("Omicli error"));
        NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
        NitsCompareSubstring(err.c_str(), expected_err.c_str(), MI_T("Error output mismatch"));
    }
    else
    {
        // every test must contain an assertion
        if (!runKrbTests || travisCI)
            NitsCompare(0, 0, MI_T("test skipped"));   
        else
            NitsCompare(1, 0, MI_T("test did not run"));   
    }
}
NitsEndTest

NitsTestWithSetup(TestOMICLI_PreExec1, TestCliSetupSudo)
{
    NitsDisableFaultSim;

    NitsResult rslt = NitsTrue;

    // We have a knonw provider, which produces a file named "cli_preexec.txt" when the preexec is run.
    // The first request to the agent should cause the preexec to be run. The second should not produce the file
    struct passwd *root_pw_info = getpwuid(0);
    string out;
    string err;

    char resultFile[PAL_MAX_PATH_SIZE];
    Strlcpy(resultFile, OMI_GetPath(ID_TMPDIR), PAL_MAX_PATH_SIZE);
    Strlcat(resultFile, "/cli_preexec.txt", PAL_MAX_PATH_SIZE);

    removeIfExist(resultFile); // remove cli_preexec.txt is case there is one laying around
    string str;

    // Verify that the preexec gets called the firrst request to a provider with a defined preexec.
    string expect;
    char resultids[100];
    sprintf(resultids, "%u %u 0 %d\n", (unsigned) getuid(), (unsigned) getgid(), root_pw_info->pw_gid);

    if (travisCI)
    {
        NitsCompare(0, 0, MI_T("test skipped"));   
        goto Done;
    }

    rslt = NitsAssert(Exec(MI_T("omicli gi oop/requestor/preexec { MSFT_President Key 1 }"), out, err) == 0, MI_T("omicli command failed"));
    if (rslt == NitsFalse)
    {
        goto Done;
    }
    UT_ASSERT(InhaleTestFile("TestOMICL14.txt", expect));
    rslt = NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
    if (rslt == NitsFalse)
    {
        goto Done;
    }

    rslt = NitsCompareString(err.c_str(), "", MI_T("Output mismatch in stderr"));
    if (rslt == NitsFalse)
    {
        goto Done;
    }


    UT_ASSERT(Inhale(resultFile, out, true));
    rslt = NitsCompareString(out.c_str(), resultids, MI_T("Output mismatch from preexec script"));
    if (rslt == NitsFalse)
    {
        goto Done;
    }

    // Verify that the preexec does not get called after the firrst request to a provider with a defined preexec.
    removeIfExist(resultFile); // remove cli_preexec.txt
         
    // Execute the request, but we should not see the file produced by the preexec.
    rslt = NitsAssert(Exec(MI_T("omicli gi oop/requestor/preexec { MSFT_President Key 1 }"), out, err) == 0, MI_T("omicli command failed"));
    if (rslt == NitsFalse)
    {
        goto Done;
    }

    UT_ASSERT(InhaleTestFile("TestOMICL14.txt", expect));
    NitsCompareString(out.c_str(), expect.c_str(), MI_T("Output mismatch"));
    NitsCompareString(err.c_str(), "", MI_T("Output mismatch in stderr"));

    // Fail if the file was recreated
    NitsAssert(FileExists(resultFile) == false, MI_T("Preexec getting called extra times"));

Done:
    fprintf(stderr, "done\n"); // This is here to allow the label.
   
   // LogDir_DumpIfNeeded(stderr, (TestSystem::Result)NitsTestResult());
}
NitsEndTest

