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

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

static bool Inhale(const char* path, vector<char>& data)
{
    FILE* is = fopen(path, "r");

    if (!is)
        return false;

    size_t n;
    char buf[4096];

    while ((n = fread(buf, 1, sizeof(buf), is)) != 0)
    {
        data.insert(data.end(), buf, buf + n);
    }

    data.push_back('\0');

    fclose(is);

    return true;
}

static bool StripLeadingCommentWithPattern(
    const vector<char>& in,
    const char* pattern,
    vector<char>& out)
{
    const char* start = &in[0];
    const char* p = start;

    // Skip leading whitespace:

    while (isspace(*p))
        p++;

    // Return on end of string:

    if (*p == '\0')
    {
        return false;
    }

    // Return if this is not the start of a comment:

    if (!(p[0] ==  '/' && p[1] == '*'))
    {
        return false;
    }

    // Scan for end of comment:

    for (; *p; p++)
    {
        if (p[0] == '*' && p[1] == '/')
        {
            break;
        }
    }

    // Return on end of string:

    if (*p == '\0')
    {
        return false;
    }

    // Set p beyond closing comment:

    p += 2;

    // Skip trailing whitespace:

    while (isspace(*p))
        p++;

    // Check whether this comment contains the pattern:

    string comment(start, p - start);

    if (!strstr(comment.c_str(), pattern))
    {
        return false;
    }

    // Assign the output buffer:
    {
        const char* end = p;

        while (*end)
            end++;

        out.clear();
        out.insert(out.end(), p, end);
    }

    return true;
}

static bool WriteFileFromBuffer(
    const char* path,
    const vector<char>& buf)
{
    // Open file:

    FILE* os = fopen(path, "wb");

    if (!os)
    {
        return false;
    }

    // Write file:

    size_t n = fwrite(&buf[0], 1, buf.size(), os);

    if (n != buf.size())
    {
        return false;
    }

    return true;
}

static bool StripLicense(
    const char* path,
    const char* pattern)
{
    // Open the source file:

    vector<char> buf;

    if (!Inhale(path, buf))
    {
        return false;
    }

    // Strip the leading comment containing the given pattern:

    vector<char> out;

    if (StripLeadingCommentWithPattern(buf, pattern, out))
    {
        if (!WriteFileFromBuffer(path, out))
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char** argv)
{
    // Check arguments:

    if (argc < 3)
    {
        cerr << "Usage: " << argv[0] << " PATTERN FILENAME..." << endl;
        exit(1);
    }

    const char* pattern = argv[1];

    // Strip licensings:

    for (int i = 2; i < argc; i++)
    {
        printf("%s\n", argv[i]);
        StripLicense(argv[i], pattern);
    }

    return 0;
}
