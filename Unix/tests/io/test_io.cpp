/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <ut/ut.h>
#include <common.h>
#include <pal/format.h>
#include <pal/file.h>

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

    FILE* is = File_Open(path, "r");

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

NitsSetup(TestIoSetup)
NitsEndSetup

NitsCleanup(TestIoSetup)
NitsEndCleanup

NitsTestWithSetup(Test0, TestIoSetup)
{
    // Create file with Tprintf():
#if defined(_MSC_VER)
    string root = OMI_GetPath(ID_PREFIX);
    string path = root + "/tmp/io_test0.tmp";
#else
    string path = string(CONFIG_TMPDIR) + "/io_test0.tmp";
#endif
    {
        FILE* os = File_Open(path.c_str(), "w");
        UT_ASSERT(os != NULL);
        Ftprintf(os, PAL_T("WCHAR{%S}\n"), L"Test0");
        Ftprintf(os, PAL_T("CHAR{%s}\n"), "Test0");
        Ftprintf(os, PAL_T("ZCHAR{%T}\n"), PAL_T("Test0"));
        File_Close(os);
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
NitsEndTest

NitsTestWithSetup(Test1, TestIoSetup)
{
    ZChar buf[128];

    int r = Stprintf(
        buf, 
        sizeof(buf) / sizeof(buf[0]), 
        PAL_T("{%T}{%S}{%s}{%d}\n"),
        PAL_T("Hello"),
        L"Hello",
        "Hello",
        1234);

    UT_ASSERT(r == 28);
    UT_ASSERT(String(buf) == PAL_T("{Hello}{Hello}{Hello}{1234}\n"));
}
NitsEndTest


