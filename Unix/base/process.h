/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_process_h
#define _omi_process_h

#include <common.h>
#include <pal/strings.h>

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
