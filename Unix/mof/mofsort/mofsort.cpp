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

/* Must be defined first (define MI_CHAR_TYPE) */
#include <mof.h>

#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

extern "C" void ErrorCallback(const char* msg, const wchar_t* wmsg, void*)
{
    fprintf(stderr, "Error: %s\n", msg);
}

extern "C" void WarningCallback(const char* msg, const wchar_t* wmsg, void*)
{
    fprintf(stderr, "Warning: %s\n", msg);
}

static bool Check(const string& path, bool quiet)
{
    MOF_Parser* parser;

    const char* paths [] = { "." };
    parser = MOF_Parser_New(paths, MI_COUNT(paths));

    if (!quiet)
    {
        MOF_Parser_SetErrorCallback(parser, ErrorCallback, NULL);
        MOF_Parser_SetWarningCallback(parser, WarningCallback, NULL);
    }

    int r = MOF_Parser_Parse(parser, path.c_str());

    if (r != 0)
        return false;

    MOF_Parser_Delete(parser);

    return true;
}

int CreateMofFile(
    const char* path, 
    vector<string>& passed, 
    const string& attempt)
{
    FILE* os = fopen(path, "wb");

    if (!os)
        return -1;

    for (size_t i = 0; i < passed.size(); i++)
    {
        fprintf(os, "#pragma include(\"%s\")\n", passed[i].c_str());
    }

    fprintf(os, "#pragma include(\"%s\")\n", attempt.c_str());

    fclose(os);

    return 0;
}

int main(int argc, char** argv)
{
    // Check arguments:

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s MOFFILE...\n", argv[0]);
        exit(1);
    }

    // Build list of MOF file paths:

    vector<string> paths;

    for (int i = 1; i < argc; i++)
    {
        paths.push_back(argv[i]);
    }

    // Build list of passed files file-by-file, by adding one MOF file
    // at a time.

    vector<string> passed;
    vector<string> failed;

    for (;;)
    {
        failed.clear();
        bool pass = false;

        for (size_t i = 0; i < paths.size(); i++)
        {
            const char TMPFILE[] = "/tmp/mofsort.mof";

            if (CreateMofFile(TMPFILE, passed, paths[i]) != 0)
            {
                fprintf(stderr, "failed to create MOF file\n");
                exit(1);
            }

            if (Check(TMPFILE, true))
            {
                //printf("passed: %s\n", paths[i].c_str());
                pass = true;
                passed.push_back(paths[i]);
            }
            else
            {
                //printf("failed: %s\n", paths[i].c_str());
                failed.push_back(paths[i]);
            }
        }

        if (!pass)
            break;

        paths = failed;
    }

    for (size_t i = 0; i < passed.size(); i++)
    {
        printf("#pragma include(\"%s\")\n", passed[i].c_str());
    }

    bool fail = false;

    for (size_t i = 0; i < failed.size(); i++)
    {
        fprintf(stderr, "failed: %s\n", failed[i].c_str());

        {
            const char TMPFILE[] = "/tmp/mofsort.mof";

            if (CreateMofFile(TMPFILE, passed, failed[i]) != 0)
            {
                fprintf(stderr, "failed to create MOF file\n");
                exit(1);
            }

            if (!Check(TMPFILE, false))
            {
                fail = true;
            }
        }
    }

    if (fail)
        exit(1);

    return 0;
}
