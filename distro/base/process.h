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

#ifndef _omi_process_h
#define _omi_process_h

#include <common.h>
#include "strings.h"

BEGIN_EXTERNC

typedef struct _Process
{
    MI_Uint64 reserved;
}
Process;

int Process_StartChild(_In_ Process* self, ConstCharPtr path, _In_ CharPtrPtr argv);

int Process_StopChild(Process* self);

#if defined(CONFIG_POSIX)
int Process_Daemonize();
int SetSignalHandler(int sig, void (*handler)(int));
#endif

END_EXTERNC

#endif /* _omi_process_h */
