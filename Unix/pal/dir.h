/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _pal_dir_h
#define _pal_dir_h

#include "palcommon.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

PAL_BEGIN_EXTERNC

typedef struct _DirEnt 
{
    char name[PAL_MAX_PATH_SIZE];
    int isDir;
}
DirEnt;

typedef struct _Dir Dir;

Dir* Dir_Open(const char* path);

DirEnt* Dir_Read(Dir* dir);

int Dir_Close(Dir* dir);

PAL_INLINE int Mkdir(const char* path, int mode)
{
    return mkdir(path, mode);
}

/* Create the given directory and any directories along the path */
int Mkdirhier(const char* path, int mode);

PAL_INLINE int Chdir(const char* path)
{
    return chdir(path);
}

PAL_INLINE int Rmdir(const char* path)
{
    return rmdir(path);
}

PAL_Boolean Isdir(const char* path);

/* Find the 'basename' of a path (final component without leading directory) */
const char* Basename(const char* path);

PAL_END_EXTERNC

#endif /* _pal_dir_h */
