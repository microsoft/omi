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

#include <stdlib.h>
#include <stdio.h>
#include <wql/wql.h>
#include <base/getopt.h>

static const char* opt_test;

static void GetCommandLineOptions(
    int* argc_,
    const char* argv[])
{
    int argc = *argc_;
    GetOptState state = GETOPTSTATE_INITIALIZER;
    static const char* opts[] =
    {
        "-t:",
        NULL,
    };

    for (;;)
    {
        int r = GetOpt(&argc, argv, opts, &state);

        if (r == 1)
            break;

        if (r == -1)
        {
            fprintf(stderr, "error: %s\n", state.err);
            exit(1);
        }

        if (strcmp(state.opt, "-t") == 0)
        {
            opt_test = state.arg;
        }
    }

    *argc_ = argc;
}

static void GenTest(WQL* wql, const char* expr, const char* testName)
{
    printf("static void %s()\n", testName);
    printf("{\n");
    printf("    WQL* wql;\n");
    WQL_Dump(wql, 4);

    printf("    wql = WQL_Parse(\"");

    while (*expr)
    {
        char c = *expr++;

        switch (c)
        {
            case '"':
                putchar('\\');
                putchar('"');
                break;
            case '\\':
                putchar('\\');
                putchar('\\');
                break;
            default:
                putchar(c);
                break;
        }
    }
    
    printf("\", NULL);\n");

    printf("    UT_ASSERT(wql != NULL);\n");

    printf("    UT_ASSERT(WQL_Identical(&_wql, wql));\n");
    printf("    WQL_Delete(wql);\n");
    printf("}\n");
}

int main(int argc, const char* argv[])
{
    WQL* wql;

    /* Get options */
    GetCommandLineOptions(&argc, argv);

    /* Check usage */
    if (argc != 2)
    {
        fprintf(stderr, "%s EXPRESSION\n", argv[0]);
        exit(1);
    }

    /* Parse expression */
    {
        wql = WQL_Parse(argv[1], NULL);

        if (!wql)
        {
            fprintf(stderr, "%s: error: invalid WQL expression: %s\n",
                argv[0], argv[1]);
            exit(1);
        }
    }

    /* Dump definition of WQL object */
    if (opt_test)
        GenTest(wql, argv[1], opt_test);
    else
        WQL_Dump(wql, 0);

    /* Delete WQL object */
    WQL_Delete(wql);

    return 0;
}
