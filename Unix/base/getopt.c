/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <base/omigetopt.h>
#include <pal/strings.h>

#if 0
static void PrintArgs(int argc, char** argv)
{
    int i;

    printf("==== PrintArgs()\n");
    printf("ARGC[%d]\n", argc);

    for (i = 0; i < argc; i++)
    {
        printf("ARGV[%s]\n", argv[i]);
    }

    printf("\n");
}
#endif

int GetOpt(
    int* argc, 
    const char* argv[], 
    const char* opts[],
    GetOptState* state)
{
    int i;
    int j;

    /* Clear state */
    state->opt[0] = '\0';
    state->arg = NULL;
    state->err[0] = '\0';

    for (i = state->index; i < *argc; i++)
    {
        if (argv[i][0] != '-')
        {
            state->index++;
            continue;
        }

        /* Find option argv[i] */
        for (j = 0; opts[j]; j++)
        {
            char opt[GETOPT_OPT_SIZE];
            size_t n;
            int hasArg;

            /* Copy option name */
            n = Strlcpy(opt, opts[j], sizeof(opt));

            /* If option name too long */
            if (n >= sizeof(opt))
            {
                Strlcpy(state->err, "bad parameter", sizeof(state->err));
                return -1;
            }

            /* If option name zero-length */
            if (n == 0)
            {
                Strlcpy(state->err, "bad parameter", sizeof(state->err));
                return -1;
            }

            /* If option has argument */
            if (opt[n-1] == ':')
            {
                hasArg = 1;
                opt[n-1] = '\0';
            }
            else if (opt[n-1] == '?')
            {
                hasArg = 2;
                opt[n-1] = '\0';
            }
            else
                hasArg = 0;

            /* Does argv[i] match this option? */
            if (strcmp(argv[i], opt) == 0)
            {
                if (hasArg == 1)
                {
                    if (i + 1 == *argc)
                    {
                        Strlcpy(state->err, "missing option argument: ", 
                            sizeof(state->err));
                        Strlcat(state->err, opt, sizeof(state->err));
                        return -1;
                    }

                    Strlcpy(state->opt, argv[i], sizeof(state->opt));
                    state->arg =  argv[i+1];
                    memmove((void*)&argv[i], (void*)&argv[i+2],
                        sizeof(char*) * ((*argc) - i - 1));
                    *argc -= 2;
                    return 0;
                }
                else
                {
                    Strlcpy(state->opt, argv[i], sizeof(state->opt));
                    memmove((void*)&argv[i], (void*)&argv[i+1], 
                        sizeof(char*) * ((*argc) - i));
                    *argc -= 1;
                    return 0;
                }
            }
            else if (hasArg && 
                strncmp(argv[i], opt, n-1) == 0 && argv[i][n-1] == '=')
            {
                Strlcpy(state->opt, argv[i], sizeof(state->opt));
                state->opt[n-1] = '\0';
                state->arg =  &argv[i][n];
                memmove((void*)&argv[i], (void*)&argv[i+1], 
                    sizeof(char*) * ((*argc) - i));
                *argc -= 1;
                return 0;
            }
        }

        /* Unknown option */
        Strlcpy(state->err, "unknown option: ", sizeof(state->err));
        Strlcat(state->err, argv[i], sizeof(state->err));
        return -1;
    }

    /* Done */
    return 1;
}
