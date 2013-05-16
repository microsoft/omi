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

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <ut/ut.h>
#include <common.h>
#include <io/io.h>

#if defined(_MSC_VER)
#include <base/paths.h>
#endif

#if defined(CONFIG_ENABLE_WCHAR)
typedef std::wstring String;
#else
typedef std::string String;
#endif

using namespace std;

static bool Inhale(const char* path, vector<char>& data)
{
    data.clear();

    FILE* is = Fopen(path, "r");

    if (!is)
        return false;

    size_t n;
    char buf[4096];

    while ((n = fread(buf, 1, sizeof(buf), is)) != 0)
        data.insert(data.end(), buf, buf + n);

    data.push_back('\0');
    fclose(is);

    return true;
}

static void setUp()
{
}

static void cleanup()
{
}

static void Test0()
{
    // Create file with Zprintf():
#if defined(_MSC_VER)
    string root = GetPath(ID_PREFIX);
    string path = root + "/tmp/io_test0.tmp";
#else
    string path = string(CONFIG_TMPDIR) + "/io_test0.tmp";
#endif
    {
        FILE* os = Fopen(path.c_str(), "w");
        UT_ASSERT(os != NULL);
        Fzprintf(os, ZT("WCHAR{%S}\n"), L"Test0");
        Fzprintf(os, ZT("CHAR{%s}\n"), "Test0");
        Fzprintf(os, ZT("ZCHAR{%Z}\n"), ZT("Test0"));
        fclose(os);
    }

    // Read file into memory:

    vector<char> data;
    UT_ASSERT(Inhale(path.c_str(), data) == true);

    const char DATA[] =
        "WCHAR{Test0}\n"
        "CHAR{Test0}\n"
        "ZCHAR{Test0}\n";

    // Be sure file contaisn what we expected:

    UT_ASSERT(strcmp(&data[0], DATA) == 0);
}

static void Test1()
{
    ZChar buf[128];

    int r = Szprintf(
        buf, 
        sizeof(buf) / sizeof(buf[0]), 
        ZT("{%Z}{%S}{%s}{%d}\n"),
        ZT("Hello"),
        L"Hello",
        "Hello",
        1234);

    UT_ASSERT(r == 28);
    UT_ASSERT(String(buf) == ZT("{Hello}{Hello}{Hello}{1234}\n"));
}

static void RunTests()
{
    UT_TEST(Test0);
    UT_TEST(Test1);
}

UT_ENTRY_POINT(RunTests);
