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

#ifndef _omi_getopt_h
#define _omi_getopt_h

#include <common.h>

#define GETOPTSTATE_INITIALIZER { 0, { '\0' }, NULL, { '\0' } }

#define GETOPT_OPT_SIZE 512
#define GETOPT_ERR_SIZE 512

BEGIN_EXTERNC

typedef struct _GetOptState
{
    int index;
    char opt[GETOPT_OPT_SIZE];
    const char* arg;
    char err[GETOPT_ERR_SIZE];
}
GetOptState;


/*
** GetOpt() extracts and removes options (and their arguments if any) from the 
** argc-argv parameters. The set of expected options are specified by the opts
** parameter (see example below). Returns 0 if an option is found and sets 
** state->opt and state->arg. Returns -1 on error and sets state->err. Returns
** 1 when all arguments are exhausted. After successful processing, no options
** nor their arguments remain in argc-argv. Here is an example:
**
**     static const char* opts[] =
**     {
**         "-h",
**         "--help",
**         "--output:",
**         NULL,
**     };
**     GetOptState state = GETOPTSTATE_INITIALIZER;
**     int help = 0;
**     const char* output = NULL;
**
**     for (;;)
**     {
**         int r = GetOpt(&argc, argv, opts, &state);
**
**         if (r == 1)
**             break;
**
**         if (r == 0)
**         {
**             if (strcmp(state.opt, "-h") == 0)
**                 help = 1;
**             else if (strcmp(state.opt, "--help") == 0)
**                 help = 1;
**             else if (strcmp(state.opt, "--output") == 0)
**                 outfile = state.arg;
**         }
**         else if (r == -1)
**         {
**             fprintf(stderr, "error: %s\n", state.err);
**             break;
**         }
**      }
**
** Note that the opts[] array contains "--output:". The ':' character indicates
** that the --output option takes a required argument.
*/
int GetOpt(
    int* argc, 
    const char* argv[], 
    const char* opts[],
    GetOptState* state);

END_EXTERNC

#endif /* _omi_getopt_h */
