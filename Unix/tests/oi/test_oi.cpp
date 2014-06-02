/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the ZT("License")); you may not 
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
#include <base/paths.h>
#include <base/log.h>
#include <pal/file.h>

#include "OIParser.h"
#include "FileGen.h"
#if defined(CONFIG_OS_WINDOWS)
#include "EtwGen.h"
#include "ManifestGen.h"
#endif
#include "Syslog.h"

#if defined(CONFIG_ENABLE_WCHAR)
typedef std::wstring String;
#else
typedef std::string String;
#endif

using namespace std;

NitsSetup(TestOiSetup)
NitsEndSetup

NitsCleanup(TestOiSetup)
NitsEndCleanup

NitsTestWithSetup(Test_SingleEvent, TestOiSetup)
{
    OIParser parser;
    OIEvent * events = 0;
    int count = 0;
    char path[PAL_MAX_PATH_SIZE];

    Strlcpy(path, OMI_GetPath(ID_PREFIX), sizeof(path));
    Strlcat(path, "/tests/oi/", sizeof(path));
    Strlcat(path, "test1.txt", sizeof(path));

    memset(&parser, 0, sizeof(OIParser));
    UT_ASSERT_EQUAL(Parser_Init(&parser, path), MI_TRUE);
    UT_ASSERT_EQUAL(Parser_Parse(&parser, &events, &count), MI_TRUE);

    UT_ASSERT_EQUAL(count, 1);
    if (count > 0)
    {
        UT_ASSERT_EQUAL(Strcmp(events->Name, "FrogEvents_JumpEvent"), 0);
        UT_ASSERT_EQUAL(Strcmp(events->Format, "\"I have jumped %d feet\""), 0);
        UT_ASSERT_EQUAL(events->next, 0);

        UT_ASSERT(events->Argument != NULL);
        if (events->Argument)
        {
            UT_ASSERT_EQUAL(Strcmp(events->Argument->Name, "number"), 0);
            UT_ASSERT_EQUAL(Strcmp(events->Argument->Type, "int"), 0);
            UT_ASSERT_EQUAL(events->Argument->next, 0);
        }
    }

    Parser_Destroy(&parser);
}
NitsEndTest

NitsTestWithSetup(Test_MultipleEvents, TestOiSetup)
{
    OIParser parser;
    OIEvent * events = 0;
    int count = 0;
    char path[PAL_MAX_PATH_SIZE];

    Strlcpy(path, OMI_GetPath(ID_PREFIX), sizeof(path));
    Strlcat(path, "/tests/oi/", sizeof(path));
    Strlcat(path, "test2.txt", sizeof(path));

    memset(&parser, 0, sizeof(OIParser));
    UT_ASSERT_EQUAL(Parser_Init(&parser, path), MI_TRUE);
    UT_ASSERT_EQUAL(Parser_Parse(&parser, &events, &count), MI_TRUE);

    UT_ASSERT_EQUAL(count, 3);
    if (count > 0)
    {
        UT_ASSERT_EQUAL(Strcmp(events->Name, "FrogEvents_JumpEvent"), 0);
        UT_ASSERT_EQUAL(Strcmp(events->Format, "\"I have jumped %d feet\""), 0);

        OIArgument * arg = events->Argument;
        UT_ASSERT(arg != NULL);
        if (arg)
        {
            UT_ASSERT_EQUAL(Strcmp(arg->Name, "number"), 0);
            UT_ASSERT_EQUAL(Strcmp(arg->Type, "int"), 0);
            UT_ASSERT_EQUAL(arg->next, 0);
        }

        UT_ASSERT(events->next != 0);
        OIEvent * e = events->next;        
        if (e)
        {
            UT_ASSERT_EQUAL(Strcmp(e->Name, "FrogEvents_EatFlysEvent"), 0);
            UT_ASSERT_EQUAL(Strcmp(e->Format, "\"I have eaten %d flys\""), 0);

            OIArgument * arg = e->Argument;
            UT_ASSERT(arg != NULL);
            if (arg)
            {
                UT_ASSERT_EQUAL(Strcmp(arg->Name, "number"), 0);
                UT_ASSERT_EQUAL(Strcmp(arg->Type, "int"), 0);
                UT_ASSERT_EQUAL(arg->next, 0);
            }
        }

        UT_ASSERT(e->next != 0);
        e = e->next;
        if (e)
        {
            UT_ASSERT_EQUAL(Strcmp(e->Name, "FrogEvents_DiveEvent"), 0);
            UT_ASSERT_EQUAL(Strcmp(e->Format, "\"I have dived %d feet for %d seconds\""), 0);

            OIArgument * arg = e->Argument;
            UT_ASSERT(arg != NULL);
            if (arg)
            {
                UT_ASSERT_EQUAL(Strcmp(arg->Name, "depth"), 0);
                UT_ASSERT_EQUAL(Strcmp(arg->Type, "int"), 0);
                UT_ASSERT(arg->next != 0);
            }

            arg = arg->next;
            UT_ASSERT(arg != NULL);
            if (arg)
            {
                UT_ASSERT_EQUAL(Strcmp(arg->Name, "time"), 0);
                UT_ASSERT_EQUAL(Strcmp(arg->Type, "int"), 0);
                UT_ASSERT_EQUAL(arg->next, 0);
            }
        }
    }

    Parser_Destroy(&parser);
}
NitsEndTest

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

    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] != '\r' && str[i] != '\n')
            strOut += str[i];
    }

    return true;
}

static bool InhaleTestFile(const char* file, string& str)
{
    char path[PAL_MAX_PATH_SIZE];

    Strlcpy(path, OMI_GetPath(ID_PREFIX), sizeof(path));
    Strlcat(path, "/tests/oi/", sizeof(path));
    Strlcat(path, file, sizeof(path));

    return Inhale(path, str, true);
}

#if defined(CONFIG_OS_WINDOWS)

NitsTestWithSetup(Test_SingleEvent_ETW, TestOiSetup)
{
    OIParser parser;
    OIEvent * events = 0;
    int count = 0;
    char in[PAL_MAX_PATH_SIZE];
    char out[PAL_MAX_PATH_SIZE];
    char providerId[] = "{F93D404F-F291-496E-9D8D-56D8C6F8F650}";

    Strlcpy(in, OMI_GetPath(ID_PREFIX), sizeof(in));
    Strlcat(in, "/tests/oi/", sizeof(in));
    Strlcat(in, "test1.txt", sizeof(in));

    Strlcpy(out, OMI_GetPath(ID_PREFIX), sizeof(out));
    Strlcat(out, "/tests/oi/", sizeof(out));
    Strlcat(out, "out.c.txt", sizeof(out));

    memset(&parser, 0, sizeof(OIParser));
    UT_ASSERT_EQUAL(Parser_Init(&parser, in), MI_TRUE);
    UT_ASSERT_EQUAL(Parser_Parse(&parser, &events, &count), MI_TRUE);

    UT_ASSERT_EQUAL(count, 1);

    Buckets set;
    memset(&set, 0, sizeof(Buckets));
    MI_Boolean ret = GenerateTaskOpcodeKeywords(events, &set);
    UT_ASSERT_EQUAL(ret, MI_TRUE);

    ret = GenerateEtw(events, &set, providerId, out);
    UT_ASSERT_EQUAL(ret, MI_TRUE);

    string gen, expected;
    UT_ASSERT_EQUAL(InhaleTestFile("out.c.txt", gen), true);
    UT_ASSERT_EQUAL(InhaleTestFile("expected1.etw.txt", expected), true);

    UT_ASSERT(gen == expected);

    Parser_Destroy(&parser);
    CleanupBuckets(&set);
}
NitsEndTest

NitsTestWithSetup(Test_ETWTaskOpcodesKeywords, TestOiSetup)
{
    OIParser parser;
    OIEvent * events = 0;
    int count = 0;
    char in[PAL_MAX_PATH_SIZE];
    char out[PAL_MAX_PATH_SIZE];
    char providerId[] = "{F93D404F-F291-496E-9D8D-56D8C6F8F650}";

    Strlcpy(in, OMI_GetPath(ID_PREFIX), sizeof(in));
    Strlcat(in, "/tests/oi/", sizeof(in));
    Strlcat(in, "test2.txt", sizeof(in));

    Strlcpy(out, OMI_GetPath(ID_PREFIX), sizeof(out));
    Strlcat(out, "/tests/oi/", sizeof(out));
    Strlcat(out, "out.c.txt", sizeof(out));

    memset(&parser, 0, sizeof(OIParser));
    UT_ASSERT_EQUAL(Parser_Init(&parser, in), MI_TRUE);
    UT_ASSERT_EQUAL(Parser_Parse(&parser, &events, &count), MI_TRUE);

    UT_ASSERT_EQUAL(count, 3);
    
    Buckets set;
    memset(&set, 0, sizeof(Buckets));
    MI_Boolean ret = GenerateTaskOpcodeKeywords(events, &set);
    UT_ASSERT_EQUAL(ret, MI_TRUE);

    ret = GenerateEtw(events, &set, providerId, out);
    UT_ASSERT_EQUAL(ret, MI_TRUE);

    string gen, expected;
    UT_ASSERT_EQUAL(InhaleTestFile("out.c.txt", gen), true);
    UT_ASSERT_EQUAL(InhaleTestFile("expected2.etw.txt", expected), true);

    UT_ASSERT(gen == expected);

    Parser_Destroy(&parser);
    CleanupBuckets(&set);
}
NitsEndTest

NitsTestWithSetup(Test_ETWMultipleTasksEtc, TestOiSetup)
{
    OIParser parser;
    OIEvent * events = 0;
    int count = 0;
    char in[PAL_MAX_PATH_SIZE];
    char out[PAL_MAX_PATH_SIZE];
    char providerId[] = "{F93D404F-F291-496E-9D8D-56D8C6F8F650}";

    Strlcpy(in, OMI_GetPath(ID_PREFIX), sizeof(in));
    Strlcat(in, "/tests/oi/", sizeof(in));
    Strlcat(in, "test4.txt", sizeof(in));

    Strlcpy(out, OMI_GetPath(ID_PREFIX), sizeof(out));
    Strlcat(out, "/tests/oi/", sizeof(out));
    Strlcat(out, "out.c.txt", sizeof(out));

    memset(&parser, 0, sizeof(OIParser));
    UT_ASSERT_EQUAL(Parser_Init(&parser, in), MI_TRUE);
    UT_ASSERT_EQUAL(Parser_Parse(&parser, &events, &count), MI_TRUE);

    UT_ASSERT_EQUAL(count, 7);
    
    Buckets set;
    memset(&set, 0, sizeof(Buckets));
    MI_Boolean ret = GenerateTaskOpcodeKeywords(events, &set);
    UT_ASSERT_EQUAL(ret, MI_TRUE);

    ret = GenerateEtw(events, &set, providerId, out);
    UT_ASSERT_EQUAL(ret, MI_TRUE);

    string gen, expected;
    UT_ASSERT_EQUAL(InhaleTestFile("out.c.txt", gen), true);
    UT_ASSERT_EQUAL(InhaleTestFile("expected4.etw.txt", expected), true);

    UT_ASSERT(gen == expected);

    Parser_Destroy(&parser);
    CleanupBuckets(&set);
}
NitsEndTest

NitsTestWithSetup(Test_Manifest, TestOiSetup)
{
    OIParser parser;
    OIEvent * events = 0;
    int count = 0;
    char in[PAL_MAX_PATH_SIZE];
    char out[PAL_MAX_PATH_SIZE];
    char providerId[] = "{d2c91d76-d9a9-46bb-b080-efc944c3ba2d}";

    Strlcpy(in, OMI_GetPath(ID_PREFIX), sizeof(in));
    Strlcat(in, "/tests/oi/", sizeof(in));
    Strlcat(in, "test2.txt", sizeof(in));

    Strlcpy(out, OMI_GetPath(ID_PREFIX), sizeof(out));
    Strlcat(out, "/tests/oi/", sizeof(out));
    Strlcat(out, "man2.txt", sizeof(out));

    memset(&parser, 0, sizeof(OIParser));
    UT_ASSERT_EQUAL(Parser_Init(&parser, in), MI_TRUE);
    UT_ASSERT_EQUAL(Parser_Parse(&parser, &events, &count), MI_TRUE);

    UT_ASSERT_EQUAL(count, 3);

    Buckets set;
    memset(&set, 0, sizeof(Buckets));
    MI_Boolean ret = GenerateTaskOpcodeKeywords(events, &set);
    UT_ASSERT_EQUAL(ret, MI_TRUE);

    ret = GenerateManifest(events, &set, "FrogProvider", providerId, "FrogProvider.exe", out);
    UT_ASSERT_EQUAL(ret, MI_TRUE);

    string gen, expected;
    UT_ASSERT_EQUAL(InhaleTestFile("man2.txt", gen), true);
    UT_ASSERT_EQUAL(InhaleTestFile("manifest2.man.txt", expected), true);

    UT_ASSERT(gen == expected);

    Parser_Destroy(&parser);
    CleanupBuckets(&set);
}
NitsEndTest

NitsTestWithSetup(Test_Manifest_KeywordsOpcodesTasks, TestOiSetup)
{
    OIParser parser;
    OIEvent * events = 0;
    int count = 0;
    char in[PAL_MAX_PATH_SIZE];
    char out[PAL_MAX_PATH_SIZE];
    char providerId[] = "{d2c91d76-d9a9-46bb-b080-efc944c3ba2d}";

    Strlcpy(in, OMI_GetPath(ID_PREFIX), sizeof(in));
    Strlcat(in, "/tests/oi/", sizeof(in));
    Strlcat(in, "test4.txt", sizeof(in));

    Strlcpy(out, OMI_GetPath(ID_PREFIX), sizeof(out));
    Strlcat(out, "/tests/oi/", sizeof(out));
    Strlcat(out, "man4.txt", sizeof(out));

    memset(&parser, 0, sizeof(OIParser));
    UT_ASSERT_EQUAL(Parser_Init(&parser, in), MI_TRUE);
    UT_ASSERT_EQUAL(Parser_Parse(&parser, &events, &count), MI_TRUE);

    UT_ASSERT_EQUAL(count, 7);

    Buckets set;
    memset(&set, 0, sizeof(Buckets));
    MI_Boolean ret = GenerateTaskOpcodeKeywords(events, &set);
    UT_ASSERT_EQUAL(ret, MI_TRUE);

    ret = GenerateManifest(events, &set, "FrogProvider", providerId, "FrogProvider.exe", out);
    UT_ASSERT_EQUAL(ret, MI_TRUE);

    string gen, expected;
    UT_ASSERT_EQUAL(InhaleTestFile("man4.txt", gen), true);
    UT_ASSERT_EQUAL(InhaleTestFile("manifest4.man.txt", expected), true);

    UT_ASSERT(gen == expected);
    
    Parser_Destroy(&parser);
    CleanupBuckets(&set);
}
NitsEndTest
#endif

NitsTestWithSetup(Test_Parser_SyslogPriority, TestOiSetup)
{
    OIParser parser;
    OIEvent * events = 0;
    int count = 0;
    char in[PAL_MAX_PATH_SIZE];
    char out[PAL_MAX_PATH_SIZE];

    Strlcpy(in, OMI_GetPath(ID_PREFIX), sizeof(in));
    Strlcat(in, "/tests/oi/", sizeof(in));
    Strlcat(in, "syslog1.txt", sizeof(in));

    Strlcpy(out, OMI_GetPath(ID_PREFIX), sizeof(out));
    Strlcat(out, "/tests/oi/", sizeof(out));
    Strlcat(out, "out.c.txt", sizeof(out));

    memset(&parser, 0, sizeof(OIParser));
    UT_ASSERT_EQUAL(Parser_Init(&parser, in), MI_TRUE);
    UT_ASSERT_EQUAL(Parser_Parse(&parser, &events, &count), MI_TRUE);

    UT_ASSERT_EQUAL(count, 1);
    if (count > 0)
    {
        UT_ASSERT_EQUAL(Strcmp(events->Name, "FrogEvents_JumpEvent"), 0);
        UT_ASSERT_EQUAL(Strcmp(events->Format, "\"I have jumped %d feet\""), 0);
        UT_ASSERT_EQUAL(Strcmp(events->Priority, "LOG_NOTICE"), 0);
        UT_ASSERT_EQUAL(events->next, 0);

        UT_ASSERT(events->Argument != NULL);
        if (events->Argument)
        {
            UT_ASSERT_EQUAL(Strcmp(events->Argument->Name, "number"), 0);
            UT_ASSERT_EQUAL(Strcmp(events->Argument->Type, "int"), 0);
            UT_ASSERT_EQUAL(events->Argument->next, 0);
        }
    }

    Parser_Destroy(&parser);
}
NitsEndTest

NitsTestWithSetup(Test_Parser_SyslogPriorities, TestOiSetup)
{
    OIParser parser;
    OIEvent * events = 0;
    int count = 0;
    char in[PAL_MAX_PATH_SIZE];
    char out[PAL_MAX_PATH_SIZE];

    Strlcpy(in, OMI_GetPath(ID_PREFIX), sizeof(in));
    Strlcat(in, "/tests/oi/", sizeof(in));
    Strlcat(in, "syslog2.txt", sizeof(in));

    Strlcpy(out, OMI_GetPath(ID_PREFIX), sizeof(out));
    Strlcat(out, "/tests/oi/", sizeof(out));
    Strlcat(out, "out.c.txt", sizeof(out));

    memset(&parser, 0, sizeof(OIParser));
    UT_ASSERT_EQUAL(Parser_Init(&parser, in), MI_TRUE);
    UT_ASSERT_EQUAL(Parser_Parse(&parser, &events, &count), MI_TRUE);

    UT_ASSERT_EQUAL(count, 2);
    if (count > 0)
    {
        UT_ASSERT_EQUAL(Strcmp(events->Name, "FrogEvents_JumpEvent"), 0);
        UT_ASSERT_EQUAL(Strcmp(events->Format, "\"I have jumped %d feet\""), 0);
        UT_ASSERT_EQUAL(Strcmp(events->Priority, "LOG_NOTICE"), 0);
        UT_ASSERT(events->Argument != NULL);
        if (events->Argument)
        {
            UT_ASSERT_EQUAL(Strcmp(events->Argument->Name, "number"), 0);
            UT_ASSERT_EQUAL(Strcmp(events->Argument->Type, "int"), 0);
            UT_ASSERT_EQUAL(events->Argument->next, 0);
        }

        UT_ASSERT(events->next != NULL);
        if (events->next)
        {
            OIEvent * second = events->next;
            UT_ASSERT_EQUAL(Strcmp(second->Priority, "LOG_WARNING"), 0);
            UT_ASSERT(second->next == NULL);
        }
    }

    Parser_Destroy(&parser);
}
NitsEndTest

NitsTestWithSetup(Test_SingleEvent_Syslog, TestOiSetup)
{
    OIParser parser;
    OIEvent * events = 0;
    int count = 0;
    char in[PAL_MAX_PATH_SIZE];
    char out[PAL_MAX_PATH_SIZE];

    Strlcpy(in, OMI_GetPath(ID_PREFIX), sizeof(in));
    Strlcat(in, "/tests/oi/", sizeof(in));
    Strlcat(in, "syslog1.txt", sizeof(in));

    Strlcpy(out, OMI_GetPath(ID_PREFIX), sizeof(out));
    Strlcat(out, "/tests/oi/", sizeof(out));
    Strlcat(out, "out.c.txt", sizeof(out));

    memset(&parser, 0, sizeof(OIParser));
    UT_ASSERT_EQUAL(Parser_Init(&parser, in), MI_TRUE);
    UT_ASSERT_EQUAL(Parser_Parse(&parser, &events, &count), MI_TRUE);

    UT_ASSERT_EQUAL(count, 1);

    MI_Boolean ret = GenerateSyslog(events, "examplelog", "LOG_CONS | LOG_PID | LOG_NDELAY", "LOG_LOCAL1", out);
    UT_ASSERT_EQUAL(ret, MI_TRUE);

    string gen, expected;
    UT_ASSERT_EQUAL(InhaleTestFile("out.c.txt", gen), true);
    UT_ASSERT_EQUAL(InhaleTestFile("expected1.syslog.txt", expected), true);

    UT_ASSERT(gen == expected);

    Parser_Destroy(&parser);
}
NitsEndTest

NitsTestWithSetup(Test_Parser_AutoID, TestOiSetup)
{
    OIParser parser;
    OIEvent * events = 0;
    int count = 0;
    char in[PAL_MAX_PATH_SIZE];
    char out[PAL_MAX_PATH_SIZE];

    Strlcpy(in, OMI_GetPath(ID_PREFIX), sizeof(in));
    Strlcat(in, "/tests/oi/", sizeof(in));
    Strlcat(in, "syslog3.txt", sizeof(in));

    Strlcpy(out, OMI_GetPath(ID_PREFIX), sizeof(out));
    Strlcat(out, "/tests/oi/", sizeof(out));
    Strlcat(out, "out.c.txt", sizeof(out));

    memset(&parser, 0, sizeof(OIParser));
    UT_ASSERT_EQUAL(Parser_Init(&parser, in), MI_TRUE);
    UT_ASSERT_EQUAL(Parser_Parse(&parser, &events, &count), MI_TRUE);

    UT_ASSERT_EQUAL(count, 5);
    if (count > 0)
    {
        // first event
        UT_ASSERT_EQUAL(Strcmp(events->Name, "trace_1"), 0);
        UT_ASSERT_EQUAL(Strcmp(events->EventId, "1000"), 0);

        // second event
        OIEvent * second = events->next;
        UT_ASSERT(second != NULL);
        if (second)
        {
            UT_ASSERT_EQUAL(Strcmp(second->EventId, "1001"), 0);
            UT_ASSERT(second->next != NULL);

            // third event
            OIEvent * third = second->next;
            UT_ASSERT(third != NULL);
            if (third)
            {
                UT_ASSERT_EQUAL(Strcmp(third->EventId, "2001"), 0);
                UT_ASSERT(third->next != NULL);

                // forth event
                OIEvent * forth = third->next;
                UT_ASSERT(forth != NULL);
                if (forth)
                {
                    UT_ASSERT_EQUAL(Strcmp(forth->EventId, "2002"), 0);
                    UT_ASSERT(forth->next != NULL);

                    // last event
                    OIEvent * last = forth->next;
                    UT_ASSERT(last != NULL);
                    if (last)
                    {
                        UT_ASSERT_EQUAL(Strcmp(last->EventId, "3000"), 0);
                        UT_ASSERT(last->next == NULL);
                    }
                }
            }
        }
    }

    Parser_Destroy(&parser);
}
NitsEndTest

NitsTestWithSetup(Test_AutoID_Syslog, TestOiSetup)
{
    OIParser parser;
    OIEvent * events = 0;
    int count = 0;
    char in[PAL_MAX_PATH_SIZE];
    char out[PAL_MAX_PATH_SIZE];

    Strlcpy(in, OMI_GetPath(ID_PREFIX), sizeof(in));
    Strlcat(in, "/tests/oi/", sizeof(in));
    Strlcat(in, "syslog3.txt", sizeof(in));

    Strlcpy(out, OMI_GetPath(ID_PREFIX), sizeof(out));
    Strlcat(out, "/tests/oi/", sizeof(out));
    Strlcat(out, "out.c.txt", sizeof(out));

    memset(&parser, 0, sizeof(OIParser));
    UT_ASSERT_EQUAL(Parser_Init(&parser, in), MI_TRUE);
    UT_ASSERT_EQUAL(Parser_Parse(&parser, &events, &count), MI_TRUE);

    UT_ASSERT_EQUAL(count, 5);

    MI_Boolean ret = GenerateSyslog(events, "examplelog", "LOG_CONS | LOG_PID | LOG_NDELAY", "LOG_LOCAL1", out);
    UT_ASSERT_EQUAL(ret, MI_TRUE);

    string gen, expected;
    UT_ASSERT_EQUAL(InhaleTestFile("out.c.txt", gen), true);
    UT_ASSERT_EQUAL(InhaleTestFile("expected3.syslog.txt", expected), true);

    UT_ASSERT(gen == expected);

    Parser_Destroy(&parser);
}
NitsEndTest

NitsTestWithSetup(Test_SingleEvent_FileGen, TestOiSetup)
{
    OIParser parser;
    OIEvent * events = 0;
    int count = 0;
    char in[PAL_MAX_PATH_SIZE];
    char out[PAL_MAX_PATH_SIZE];

    Strlcpy(in, OMI_GetPath(ID_PREFIX), sizeof(in));
    Strlcat(in, "/tests/oi/", sizeof(in));
    Strlcat(in, "syslog1.txt", sizeof(in));

    Strlcpy(out, OMI_GetPath(ID_PREFIX), sizeof(out));
    Strlcat(out, "/tests/oi/", sizeof(out));
    Strlcat(out, "out.c.txt", sizeof(out));

    memset(&parser, 0, sizeof(OIParser));
    UT_ASSERT_EQUAL(Parser_Init(&parser, in), MI_TRUE);
    UT_ASSERT_EQUAL(Parser_Parse(&parser, &events, &count), MI_TRUE);

    UT_ASSERT_EQUAL(count, 1);

    MI_Boolean ret = GenerateFile(events, out);
    UT_ASSERT_EQUAL(ret, MI_TRUE);

    string gen, expected;
    UT_ASSERT_EQUAL(InhaleTestFile("out.c.txt", gen), true);
    UT_ASSERT_EQUAL(InhaleTestFile("expected1.filegen.txt", expected), true);

    UT_ASSERT(gen == expected);

    Parser_Destroy(&parser);
}
NitsEndTest

NitsTestWithSetup(Test_Parser_Parsing, TestOiSetup)
{
    OIParser parser;
    OIEvent * events = 0;
    int count = 0;
    char in[PAL_MAX_PATH_SIZE];

    Strlcpy(in, OMI_GetPath(ID_PREFIX), sizeof(in));
    Strlcat(in, "/tests/oi/", sizeof(in));
    Strlcat(in, "test3.txt", sizeof(in));

    memset(&parser, 0, sizeof(OIParser));
    UT_ASSERT_EQUAL(Parser_Init(&parser, in), MI_TRUE);
    UT_ASSERT_EQUAL(Parser_Parse(&parser, &events, &count), MI_TRUE);

    UT_ASSERT_EQUAL(count, 1);
    if (count > 0)
    {
        // first event
        UT_ASSERT_EQUAL(Strcmp(events->Name, "trace_Me"), 0);
        UT_ASSERT_EQUAL(Strcmp(events->EventId, "1"), 0);
        UT_ASSERT_EQUAL(Strcmp(events->Format, "\", testing commas , , , \""), 0);
    }

    Parser_Destroy(&parser);
}
NitsEndTest

#if 0
/*
This test should only work when the code is built for ETW logging
*/
NitsTestWithSetup(Test_ETWActivityID, TestOiSetup)
{
    OIGUID test, newone;
    memset(&test, 0, sizeof(OIGUID));    
    memset(&newone, 0, sizeof(OIGUID));    
    UT_ASSERT_EQUAL(test.Data1, 0);

    OIActivityId(OI_CTRL_CREATE_ID, &test);
    OIActivityId(OI_CTRL_SET_ID, &test);
    OIActivityId(OI_CTRL_GET_ID, &newone);

    trace_EventTransfer(&test, &newone);
    trace_EventTransfer(NULL, &newone);

    UT_ASSERT_EQUAL(test.Data1, newone.Data1);
}
NitsEndTest
#endif


