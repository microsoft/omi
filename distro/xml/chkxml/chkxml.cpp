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
#include <vector>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <xml/xml.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>

#if defined(CONFIG_ENABLE_WCHAR)
# define XML_printf wprintf
# define T(STR) L##STR
#else
# define XML_printf printf
# define T(STR) STR
#endif

using namespace std;
const char* arg0;

typedef struct _Options
{
    bool help;
    bool trace;
    int repeat;
}
Options;

static Options options =
{
    false, /* help */
    false, /* trace */
    1, /* repeat */
};

#if 0
bool Inhale(const char* path, vector<char>& data)
{
    struct stat st;

    if (stat(path, &st) != 0)
    {
        cerr << arg0 << ": failed to stat file: " << path << endl;
        exit(1);
    }

    data.reserve(st.st_size + 1);

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
#endif

static bool Inhale(const char* path, vector<XML_Char>& wdata)
{
    vector<char> data;
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

    for (size_t i = 0; i < data.size(); i++)
        wdata.push_back(data[i]);

    return true;
}

static void Parse(const char* path)
{
    XML xml;
    XML_Elem e;
    int r;
    vector<XML_Char> data;

    if (!Inhale(path, data))
    {
        cerr << arg0 << ": failed to open " << path << endl;
        exit(1);
    }

    XML_Init(&xml);

    XML_SetText(&xml, &data[0]);

    while ((r = XML_Next(&xml, &e)) == 0)
    {
        if (options.trace)
            XML_Elem_Dump(&e);
    }

    if (r != 1)
    {
        XML_Char msg[1024];
        XML_FormatError(&xml, msg, sizeof(msg));
        XML_printf(T("%s:%s\n"), path, msg);
        exit(1);
    }
}

void GetOpts(int* argcInOut, char*** argvInOut)
{
    int argc = *argcInOut;
    char** argv = *argvInOut;

    /* For each argument */
    for (int i = 0; i < argc; )
    {
        /* Get -r option */
        if (strcmp(argv[i], "-r") == 0)
        {
            /* Check for mandatory option argument */
            if (i + 1 == argc)
            {
                cerr << arg0 << ": missing -r option argument" << endl;
                exit(1);
            }

            options.repeat = atoi(argv[i+1]);

            if (options.repeat == 0)
            {
                cerr << arg0 << ": bad option argument for -r: " << argv[i+1] << endl;
                exit(1);
            }

            /* Remove option and its argument from argv */
            memmove(&argv[i], &argv[i+2], sizeof(char*) * (argc-i-2));
            argc -= 2;
        }
        else if (strcmp(argv[i], "-h") == 0)
        {
            options.help = true;

            /* Remove option and its argument from argv */
            memmove(&argv[i], &argv[i+1], sizeof(char*) * (argc-i-1));
            argc--;
        }
        else if (strcmp(argv[i], "-t") == 0)
        {
            options.trace = true;

            /* Remove option and its argument from argv */
            memmove(&argv[i], &argv[i+1], sizeof(char*) * (argc-i-1));
            argc--;
        }
        else if (argv[i][0] == '-')
        {
            cerr << arg0 << ": unknown option: " << argv[i] << endl;
            exit(1);
        }
        else
            i++;
    }

    *argcInOut = argc;
    *argvInOut = argv;
}

int main(int argc, char** argv)
{
    arg0 = argv[0];

    GetOpts(&argc, &argv);

    if (argc < 2)
    {
        cerr << "Usage: " << arg0 << " files..." << endl;
        exit(1);
    }

    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; j < options.repeat; j++)
        {
            if (options.trace)
                cout << "==== parsing " << argv[i] << endl;

            Parse(argv[i]);
        }
    }

    return 0;
}
