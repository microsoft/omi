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

#include <string>
#include <vector>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <unistd.h>

using namespace std;

const char* arg0;

struct Options
{
    vector<string> paths;
    string objdir;
};

static Options opts;

static void _GetOptions( 
    int& argc, 
    char**& argv,
    Options& opts)
{
    /* For each argument */
    for (int i = 0; i < argc; )
    {
        /* Number of argv[] elements to remove at end of loop */
        int r = 0;

        /* Check for -I option */
        if (strncmp(argv[i], "-I", 2) == 0)
        {
            const char* fn = argv[i] + 2;

            /* Check for mandatory option argument */
            if (*fn)
            {
                r = 1;
            }
            else
            {
                if (i + 1 == argc)
                {
                    fprintf(stderr, "%s: missing option argument for -I", arg0);
                    exit(1);
                }

                fn = argv[i+1];
                r = 2;
            }

            opts.paths.push_back(fn);
        }
        else if (strcmp(argv[i], "--objdir") == 0)
        {
            if (i + 1 == argc)
            {
                fprintf(stderr, "%s: missing option argument for --objdir", 
                    arg0);
                exit(1);
            }

            opts.objdir = argv[i+1];
            r = 2;
        }
        else if (argv[i][0] == '-')
        {
            fprintf(stderr, "%s: unknown option: %s", arg0, argv[i]);
            exit(1);
        }
        else
            i++;

        if (r)
        {
            memmove(&argv[i], &argv[i+r], sizeof(char*) * (argc-i-r));
            argc -= r;
        }
    }
}

void PrintDependencies(
    const char* path, 
    set<string>& found,
    size_t level = 0)
{
    vector<string> includes;

    // Recurse no deeper than this!
    if (level > 10)
        return;

    // Open file:
    FILE* is = fopen(path, "rb");
    {
        if (!is)
        {
            if (level == 0)
            {
                fprintf(stderr, "%s: failed to open: %s\n", arg0, path);
                return;
            }

            return;
        }
    }

    // Find #include directives.
    char buf[1024];
    while (fgets(buf, sizeof(buf), is) != NULL)
    {
        char* p = buf;

        // Skip leading whitespace:
        while (*p && isspace(*p))
            p++;

        // Skip lines that do not begin with preprocessor directives.
        if (*p != '#')
            continue;
        p++;

        // Skip whitespace:
        while (*p && isspace(*p))
            p++;

        // Skip line if not 'include' directive.
        if (strncmp(p, "include", 7) != 0)
            continue;
        p += 7;

        // Skip whitespace:
        while (*p && isspace(*p))
            p++;

        // Skip if not '"' or '<':
        if (*p != '"' && *p != '<')
            continue;
        p++;

        // Extract file name (between "..." or <...>).
        {
            const char* start = p;
            while (*p && *p != '"' && *p != '>')
                p++;

            if (p == start)
                continue;

            includes.push_back(string(start, p - start));
        }
    }

    // Close file:
    fclose(is);

    // Search for each include file on the paths.
    for (size_t i = 0; i < includes.size(); i++)
    {
        for (size_t j = 0; j < opts.paths.size(); j++)
        {
            string path = includes[i];

            // Check relative first:
            if (access(path.c_str(), R_OK) == 0)
            {
                if (found.find(path) == found.end())
                {
                    printf(" \\\n    %s", path.c_str());
                    found.insert(path);
                    PrintDependencies(path.c_str(), found, level+1);
                }
            }

            // Find absolute path:
            path = opts.paths[j] + "/" + includes[i];
            if (path[0] != '/')
            {
                char cwd[1024];
                if (getcwd(cwd, sizeof(cwd)) == NULL)
                {
                    fprintf(stdout, "%s: failed to stat current dir\n", arg0);
                    exit(1);
                }

                path = string(cwd) + string("/") + path;
            }

            if (access(path.c_str(), R_OK) == 0)
            {
                if (found.find(path) == found.end())
                {
                    printf(" \\\n    %s", path.c_str());
                    found.insert(path);
                    PrintDependencies(path.c_str(), found, level+1);
                }
            }
        }
    }
}

int main(int argc, char** argv)
{
    arg0 = argv[0];

    // Get command line options.
    _GetOptions(argc, argv, opts);

    // Check arguments:
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s [OPTIONS-AND-ARGUMENTS]\n", argv[0]);
        exit(1);
    }

    // Make dependencies for each file.
    for (int i = 1; i < argc; i++)
    {
        string srcfile = argv[i];
        string objfile;

        // Replace '.cpp' with '.o'
        if (srcfile.size() >= 4 && srcfile.substr(srcfile.size()-4) == ".cpp")
        {
            objfile = srcfile.substr(0, srcfile.size()-4) + ".o";
        }

        // Replace '.c' with '.o'
        if (srcfile.size() >= 2 && srcfile.substr(srcfile.size()-2) == ".c")
        {
            objfile = srcfile.substr(0, srcfile.size()-2) + ".o";
        }

        set<string> found;

        if (opts.objdir.size())
            printf("%s/%s:", opts.objdir.c_str(), objfile.c_str());
        else
            printf("%s:", objfile.c_str());

        PrintDependencies(srcfile.c_str(), found);
        printf("\n\n");
    }

    return 0;
}
