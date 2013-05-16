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

#ifndef _omi_paths_h
#define _omi_paths_h

#include <common.h>
#include "strings.h"

BEGIN_EXTERNC

typedef enum _PathID
{
    ID_PREFIX,
    ID_LIBDIR,
    ID_BINDIR,
    ID_LOCALSTATEDIR,
    ID_SYSCONFDIR,
    ID_PROVIDERDIR,
    ID_CERTSDIR,
    ID_DATADIR,
    ID_RUNDIR,
    ID_LOGDIR,
    ID_SCHEMADIR,
    ID_SCHEMAFILE,
    ID_PIDFILE,
    ID_LOGFILE,
    ID_REGISTERDIR,
    ID_PEMFILE,
    ID_KEYFILE,
    ID_AGENTPROGRAM,
    ID_SERVERPROGRAM,
    ID_INCLUDEDIR,
    ID_CONFIGFILE,
    ID_SOCKETFILE,
    ID_TMPDIR,
    ID_DESTDIR,
    ID_AUTHDIR,
    ID_HTTPSENDTRACEFILE,
    ID_HTTPRECVTRACEFILE,
    ID_SRCDIR
}
PathID;

const char* GetPath(PathID id);

int SetPath(PathID id, const char* path);

void PrintPaths();

/* Set path form nickname (e.g., "prefix", "libdir") */
int SetPathFromNickname(
    const char* nickname,
    const char* path);

MI_Boolean IsNickname(const char* nickname);

END_EXTERNC

#endif /* _omi_paths_h */
