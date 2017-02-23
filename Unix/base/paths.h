/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_pahts_h
#define _omi_pahts_h

#include <common.h>
#include <pal/strings.h>

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
    ID_HTTPCLIENTSENDTRACEFILE,
    ID_HTTPCLIENTRECVTRACEFILE,
    ID_SRCDIR,
    ID_CLIENTCONFIGFILE
}
PathID;

const char* OMI_GetPath(PathID id);

int SetPath(PathID id, const char* path);

void PrintPaths();

/* Set path form nickname (e.g., "prefix", "libdir") */
int SetPathFromNickname(
    const char* nickname, 
    const char* path);

MI_Boolean IsNickname(const char* nickname);

/* Format TMPDIR/file (leave result in 'path' and return path) */
char* TempPath(_Pre_writable_size_(PAL_MAX_PATH_SIZE) char path[PAL_MAX_PATH_SIZE], const char* file);

TChar* TSTempPath(_Pre_writable_size_(PAL_MAX_PATH_SIZE) TChar path[PAL_MAX_PATH_SIZE], const char* file);

END_EXTERNC

#endif /* _omi_pahts_h */
