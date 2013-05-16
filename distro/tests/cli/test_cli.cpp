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
#include <cctype>
#include <ut/ut.h>
#include <base/process.h>
#include <base/time.h>
#include <base/paths.h>
#include <io/io.h>
#include <base/dir.h>
#include <base/strings.h>
#include <omiclient/client.h>

using namespace std;

static string s_socketFile;

extern int climain(int argc, const char* argv[]);

// Parse the command line into tokens.
bool ParseCommandLine(const string& str, vector<char*>& args)
{
    unsigned char* p = (unsigned char*)str.c_str();

    for ( ; ; )
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
            unsigned char* start = p;

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
            args.push_back((char *)start);
        }
        else
        {
            unsigned char* start = p;

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

            args.push_back((char *)start);
        }
    }

    args.push_back((char*)"--socketfile");
    args.push_back((char*)s_socketFile.c_str());
    return true;
}

static Process serverProcess;

static int StartServer()
{
    const char* path = GetPath(ID_SERVERPROGRAM);
    const char* argv[14];
    char http[32];
    char https[32];
    std::string v;

    Snprintf(http, sizeof(http),"%d", ut::getUnittestPortNumberWSMANHTTP());
    Snprintf(https, sizeof(https),"%d", ut::getUnittestPortNumberWSMANHTTPS());

    s_socketFile = GetPath(ID_SOCKETFILE);

    if (ut::testGetAttr("skipServer", v))
        return 0;

    argv[0] = path;
    argv[1] = "--rundir";
#if defined(CONFIG_OS_WINDOWS)
    argv[2] = "..";
#else
    argv[2] = GetPath(ID_PREFIX);
#endif
    argv[3] = "--ignoreAuthentication";
    argv[4] = "--socketfile";
    argv[5] = s_socketFile.c_str();
    argv[6] = "--httpport";
    argv[7] = http;
    argv[8] = "--httpsport";
    argv[9] = https;
    argv[10] = "--livetime";
    argv[11] = "300";

    argv[12] = NULL;

    if (Process_StartChild(&serverProcess, path, (char**)argv) != 0)
        return -1;

    // wait for server to start
    // trying to connect in a loop:
    // since connect may fail quickly if server is not running
    // keep doing it in  a loop
    for (int i = 0; i < 400; i++)
    {
        mi::Client cl;
        const MI_Uint64 TIMEOUT = 1 * 1000 * 1000;
        ZChar buf[MAX_PATH_SIZE];

        if (cl.Connect(
            StrToZ(buf, MI_COUNT(buf), s_socketFile.c_str()), 
            ZT("unittest"), 
            ZT("unittest"), 
            TIMEOUT))
        {
            break;
        }

        Time_Sleep(10);
    }

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

static bool Inhale(const char* path, string& str, bool baseline)
{
    char buf[1024];

    str.clear();

    /* Open file */
    FILE* is = Fopen(path, "rb");
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
        // convert buf to ANSI string
        if (!baseline)
        {
            size_t len = n / 2 + 1;
            char* cpBuf = (char*)malloc(len);
            buf[n + 1] = '\0';
            if (cpBuf == NULL) return false;
            StrZlcpy(cpBuf, (ZChar*)buf, len);
            str += cpBuf;
            free(cpBuf);
        }
        else
            str += buf;
#else
        str += buf;
#endif
    }

    fclose(is);
    return true;
}

static bool InhaleTmpFile(const char* file, string& str)
{
    char path[MAX_PATH_SIZE];
    return Inhale(TempPath(path, file), str, false);
}

static bool InhaleTestFile(const char* file, string& str)
{
    char path[MAX_PATH_SIZE];

    Strlcpy(path, GetPath(ID_SRCDIR), sizeof(path));
    Strlcat(path, "/tests/cli/", sizeof(path));
    Strlcat(path, file, sizeof(path));

    return Inhale(path, str, true);
}

static int Exec(const string& cmd, string& out, string& err)
{
    vector<char*> args;
    char path1[MAX_PATH_SIZE];
    char path2[MAX_PATH_SIZE];

    if (!ParseCommandLine(cmd, args))
        return 1;

    // Capture stdout:
    args.push_back((char*)"--stdout");
    args.push_back(TempPath(path1, "STDOUT"));

    // Capture stderr:
    args.push_back((char*)"--stderr");
    args.push_back(TempPath(path2, "STDERR"));

    // username and password (ignored by server, but should be provided)
    args.push_back((char*)"-u");
    args.push_back((char*)"user");
    args.push_back((char*)"-p");
    args.push_back((char*)"pw");

    args.push_back(NULL);

    char** argv = &args[0];
    int argc = int(args.size() - 1);

    int r = climain(argc, (const char**)argv);

    UT_ASSERT(InhaleTmpFile("STDOUT", out));
    UT_ASSERT(InhaleTmpFile("STDERR", err));

    return r;
}

static void TestOMICLI1()
{
    const char CMD[] = "omicli noop";
    string out;
    string err;

    UT_ASSERT(Exec(CMD, out, err) == 0);

    UT_ASSERT(out == "got noop response\n");
    UT_ASSERT(err == "");
}

static void TestOMICLI2()
{
    string out;
    string err;
    UT_ASSERT(Exec("omicli ei root/test MSFT_President", out, err) == 0);
    string str;

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICL12.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}

static void TestOMICLI3()
{
    string out;
    string err;
    UT_ASSERT(Exec("omicli enc { X Array [ 1 2 3 ] }", out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICL13.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}

static void TestOMICLI4()
{
    string out;
    string err;
    UT_ASSERT(Exec("omicli gi root/test { MSFT_President Key 1 }", 
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICL14.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}

static void TestOMICLI5()
{
    string out;
    string err;
    UT_ASSERT(Exec("omicli ci -s root/test "
        "{ MSFT_President Key 3 First John Last Smith }",
        out, err) == 2);

    UT_ASSERT(out == "");
    UT_ASSERT(err == "");
}

static void TestOMICLI6()
{
    string out;
    string err;
    UT_ASSERT(Exec("omicli -s mi root/test "
        "{ MSFT_President Key 1 First Geo Last Washington }",
        out, err) == 2);

    UT_ASSERT(out == "");
    UT_ASSERT(err == "");
}

static void TestOMICLI7()
{
    string out;
    string err;
    UT_ASSERT(Exec("omicli ei test/cpp X_SmallNumber", out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI7.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}

static void TestOMICLI8()
{
    string out;
    string err;
    UT_ASSERT(Exec("omicli enc { Link Left { Gadget Key 1 } Right "
        "{ Gadget Key 2 } }", out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI8.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}

static void TestOMICLI9()
{
    string out;
    string err;
    UT_ASSERT(Exec("omicli enc "
        "{ Class1 Key1 Value1 Key2 Value2 Key3 Value3 }", out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI9.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}

static void TestOMICLI10()
{
    string out;
    string err;
    UT_ASSERT(Exec("omicli enc { W Left { X Key Hello } Right "
        "{ Y Key { Z ID Mine } } }", out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI10.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}

static void TestOMICLI11()
{
    string out;
    string err;
    UT_ASSERT(Exec(
        "omicli iv test/cpp { X_SmallNumber } SpellNumber { num 123 }",
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI11.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}

static void TestOMICLI12()
{
    string out;
    string err;
    UT_ASSERT(Exec(
        "omicli iv test/cpp { X_SmallNumber Number 135 } GetFactors", 
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI12.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}

static void TestOMICLI13()
{
    string out;
    string err;
    UT_ASSERT(Exec("omicli a test/cpp { MSFT_Person Key 1 }", out, err) == 0);

    UT_ASSERT(out == "");
    UT_ASSERT(err == "");
}

static void TestOMICLI14()
{
    string out;
    string err;
    UT_ASSERT(Exec("omicli a test/cpp { X_numberWorld Name theWorld }",
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI14.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}

static void TestOMICLI15()
{
    string out;
    string err;
    UT_ASSERT(Exec("omicli r test/cpp { X_Profile InstanceID world } "
        "-ac X_NumberWorldConformsToProfile", out, err) == 0);
    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI15.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}

static void TestOMICLI16()
{
    string out;
    string err;
    UT_ASSERT(Exec("omicli ei root/cimv2 XYZ_Widget", out, err) == 0);

    /* No way to compare since result contains current timestamp */
    UT_ASSERT(err == "");
}

static void TestOMICLI17()
{
    string out;
    string err;
    UT_ASSERT(Exec("omicli -s ci root/cimv2 "
        "{ XYZ_Widget SerialNumber 3 Colors [ Red Green Blue ]  }",
        out, err) == 2);

    UT_ASSERT(out == "");
    UT_ASSERT(err == "");
}

static void TestOMICLI18()
{
    string out;
    string err;
    UT_ASSERT(Exec("omicli ei root/test MSFT_VicePresident", out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI18.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}

static void TestOMICLI19()
{
    string out;
    string err;
    UT_ASSERT(Exec("omicli gi root/test { MSFT_VicePresident Key 2 }", 
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI19.txt", expect));
    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}

static void TestOMICLI20()
{
    string out;
    string err;
    UT_ASSERT(Exec(
        "omicli iv test/cpp { X_Dog } Fight { CatsIn [ { X_Cat Key 1001 } ] }",
        out, err) == 0);

    string expect;
    UT_ASSERT(InhaleTestFile("TestOMICLI20.txt", expect));

    UT_ASSERT(out == expect);
    UT_ASSERT(err == "");
}

static void setUp()
{
}

static void cleanup()
{
}

static void RunTests()
{
    StartServer();
    UT_TEST(TestOMICLI1);
    UT_TEST(TestOMICLI2);
    UT_TEST(TestOMICLI3);
    UT_TEST(TestOMICLI4);
    UT_TEST(TestOMICLI5);
    UT_TEST(TestOMICLI6);
    UT_TEST(TestOMICLI7);
    UT_TEST(TestOMICLI8);
    UT_TEST(TestOMICLI9);
    UT_TEST(TestOMICLI10);
    UT_TEST(TestOMICLI11);
    UT_TEST(TestOMICLI12);
    UT_TEST(TestOMICLI13);
    UT_TEST(TestOMICLI14);
    UT_TEST(TestOMICLI15);
    UT_TEST(TestOMICLI16);
    UT_TEST(TestOMICLI17);
    UT_TEST(TestOMICLI18);
    UT_TEST(TestOMICLI19);
    UT_TEST(TestOMICLI20);
    StopServer();
}

UT_ENTRY_POINT(RunTests);
