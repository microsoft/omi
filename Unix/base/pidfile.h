/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_pidfile_h
#define _omi_pidfile_h

#include <common.h>
#include <pal/strings.h>

BEGIN_EXTERNC

#if defined(CONFIG_POSIX)

int PIDFile_OpenWrite();

int PIDFile_Delete();

int PIDFile_Read(int* pid);

int PIDFile_Signal(int sig);

int PIDFile_IsRunning();

#endif /* defined(CONFIG_POSIX) */

END_EXTERNC

#endif /* _omi_pidfile_h */
