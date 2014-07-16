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

/*
**==============================================================================
**
** preexec.h:
**
**     The pre-exec feature allows a user-defined program to be executed
**     immediately before invoking an out-of-process provider. Providers may
**     use this feature by adding the following line in their provdier
**     registration file:
**
**         PREEXEC=<PROGRAMNAME>
**
**     When a request for this provider is received, the program given by
**     <PROGRAMNAME> is executed once per each unique UID-GID pair. For
**     example, suppose the following requests are received for this provider:
**
**         Request-1: UID=101, GUID=101
**         Request-2: UID=101, GUID=101
**         Request-3: UID=102, GUID=102
**         Request-4: UID=102, GUID=102
**         Request-5: UID=101, GUID=500
**
**     The program will be executed three times as shown below (since there
**     are three unique UID-GID pairs):
**
**         Request-1: UID=101, GUID=101 (executed)
**         Request-2: UID=101, GUID=101
**         Request-3: UID=102, GUID=102 (executed)
**         Request-4: UID=102, GUID=102
**         Request-5: UID=101, GUID=500 (executed)
**
**     The pre-exec module caches this information to avoid invoking the
**     same program more than once for the same UID-GID pair. The key for
**     this cache is formed as follows:
**
**         <PROGRAMNAME>+<UID>+<GID>
**
**     For a program named 'DogPreExec' the keys are determined as follows:
**
**         Request-1: UID=101, GUID=101 (DogPreExec+101+101)
**         Request-2: UID=101, GUID=101 (DogPreExec+101+101)
**         Request-3: UID=102, GUID=102 (DogPreExec+102+102)
**         Request-4: UID=102, GUID=102 (DogPreExec+102+102)
**         Request-5: UID=101, GUID=500 (DogPreExec+101+500)
**
**     The server determines whether to execute a pre-exec program with
**     the following logic:
**
**         (1) The dispatcher receives a request for a given provider.
**         (2) Checks whether the registration defines a PREEXEC line.
**         (3) If so it invokes PreExec_Exec().
**         (4) Checks whether PROGRAMNAME-UID-GID is in the cache.
**         (6) Adds PROGRAMNAME-UID-GUID to the cache.
**         (5) If not initially in the cache, invokes the program.
**
**     The pre-exec program is executed with the following parameters:
**
**         argc=3
**         argv[0]=<FULLPROGRAMPATH>
**         argv[1]=<UID>
**         argv[2]=<GID>
**
**     This feature is not built by default. To include this feature, OMI
**     must be configured with the --enable-preexec option.
**
**     Notes:
**
**         (1) PREEXEC must refer to program that resides in the OMI
**             binary directory (otherwise it would allow any program
**             anywhere to be executed as root).
**
**         (2) It is the administrators responsibility to be certain that
**             the OMI directory tree is secure. For example, the binary
**             and registration directories shoujld only be writable by root.
**
**         (3) Execution of pre-exec programs is as secure as loading of
**             providers as root. The security is determined by correct
**             permissions on the binary, registration, and provider
**             directories.
**
**         (4) If two provider registration files define the same PREEXEC
**             line, the same program will still only be executed at most
**
**             once for each UID-GID pair.
**         (5) This feature is not available on Windows since it goes against
**             the Windows authentication policies. On Windows, one should use
**             root providers in conjunction with impersonation.
**
**         (6) During program execution, this module blocks SIGCHLD signals
**             which are usually handled by a global signal handler (see
**             server/server.c). It does this so that waidpid() will work
**             correctly (as it waits on the completion code of the pre-exec
**             program). Otherwise obth the global SIGCHLD handler and this
**             module would both call waitpid() and one or the other would
**             not respond.
**
**==============================================================================
*/

#ifndef _disp_preexec_h
#define _disp_preexec_h

#include <common.h>
#include <pal/hashmap.h>

typedef struct _PreExec
{
    /* Key=PREEXECPATH+UID+GID */
    HashMap cache;
}
PreExec;

int PreExec_Construct(
    PreExec* self);

void PreExec_Destruct(
    PreExec* self);

int PreExec_Exec(
    PreExec* self,
    const char* programPath,
    uid_t uid,
    uid_t gid);

#endif /* _disp_preexec_h */
