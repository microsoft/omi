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

#include "dir.h"
#include "strarr.h"
#include "strings.h"
#include "paths.h"
#include <ctype.h>

#if defined(CONFIG_POSIX)
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
#endif

#if defined(CONFIG_OS_WINDOWS)
# include <windows.h>
# include <sys/stat.h>
# include <io.h>
#endif

/*
**==============================================================================
**
** POSIC Implementation
**
**==============================================================================
*/

#if defined(CONFIG_POSIX)

struct _Dir
{
    DIR* dir;
    DirEnt ent;
};

Dir* Dir_Open(const char* path)
{
    Dir* self = (Dir*)calloc(1, sizeof(Dir));

    if (!self)
        return NULL;

    self->dir = opendir(path);
    if (!self->dir)
    {
        free(self);
        return NULL;
    }

    return self;
}

DirEnt* Dir_Read(Dir* self)
{
    struct dirent* p = readdir(self->dir);
    if (!p)
        return NULL;

    Strlcpy(self->ent.name, p->d_name, sizeof(self->ent.name));

    return &self->ent;
}

int Dir_Close(Dir* self)
{
    if (!self)
        return -1;

    if (closedir(self->dir) != 0)
    {
        free(self);
        return -1;
    }

    free(self);
    return 0;
}

#endif /* defined(CONFIG_POSIX) */

/*
**==============================================================================
**
** Windows Implementation
**
**==============================================================================
*/

#if defined(CONFIG_OS_WINDOWS)

struct _Dir
{
    intptr_t handle;
    struct _finddata_t fileinfo;
    DirEnt ent;
    int firstTime;
};

Dir* Dir_Open(const char* path)
{
    Dir* dir;
    char filespec[MAX_PATH_SIZE];

    /* Allocate and zero-fill struct */
    dir = (Dir*)calloc(1, sizeof(Dir));
    if (!dir)
        return NULL;

    /* Build files spec */
    {
        if (Strlcpy(filespec, path, sizeof(filespec)) >= MAX_PATH_SIZE)
            return NULL;

        if (Strlcat(filespec, "/*", sizeof(filespec)) >= MAX_PATH_SIZE)
            return NULL;
    }

    /* Find first file matching the file spec */
    dir->handle = _findfirst(filespec, &dir->fileinfo);
    if (dir->handle == -1)
    {
        free(dir);
        return NULL;
    }

    /* Note that readdir() has not been called yet */
    dir->firstTime = 1;

    return dir;
}

DirEnt* Dir_Read(Dir* dir)
{
    if (!dir->firstTime)
    {
        if (_findnext(dir->handle, &dir->fileinfo) != 0)
            return NULL;
    }

    Strlcpy(dir->ent.name, dir->fileinfo.name, MAX_PATH_SIZE);
    dir->firstTime = 0;
    return &dir->ent;
}

int Dir_Close(Dir* dir)
{
    _findclose(dir->handle);
    free(dir);
    return 0;
}

#endif /* defined(CONFIG_OS_WINDOWS) */

MI_Boolean Isdir(const char* path)
{
#if defined(CONFIG_OS_WINDOWS)
    {
        struct _stat st;

        if (_stat(path, &st) != 0)
            return 0;

        return (_S_IFDIR  & st.st_mode) ? MI_TRUE : MI_FALSE;
    }
#else
    {
        struct stat st;

        if (stat(path, &st) != 0)
            return 0;

        return S_ISDIR(st.st_mode);
    }
#endif
}

int Mkdirhier(const char* path_, int mode)
{
    char path[MAX_PATH_SIZE];
    char buf[MAX_PATH_SIZE];
    char* p;
    char* context = NULL;

    /* Make a complete copy of the path (that we can destroy) */
    if (Strlcpy(path, path_, sizeof(path)) >= sizeof(path))
        return -1;

    buf[0] = '\0';

    for (p = Strtok(path, "/", &context); p; p = Strtok(NULL, "/", &context))
    {
#if defined(CONFIG_OS_WINDOWS)
        /* Skip drive letters (on Windows) */
        if (p == path && isalpha((unsigned char)p[0]) && p[1] == ':' && p[2] == '\0')
        {
            Strlcat(buf, p, sizeof(buf));
            continue;
        }
#endif

        /* Concatenate next component */
        Strlcat(buf, "/", sizeof(buf));
        Strlcat(buf, p, sizeof(buf));

        /* Create directory if it does not already exist */
        if (!Isdir(buf))
        {
            if (Mkdir(buf, mode) != 0)
                return -1;
        }
    }

    return 0;
}

_Use_decl_annotations_
char* TempPath(char path[MAX_PATH_SIZE], const char* file)
{
    if (Strlcpy(path, GetPath(ID_TMPDIR), MAX_PATH_SIZE) >= MAX_PATH_SIZE)
        return NULL;

    if (Strlcat(path, "/", MAX_PATH_SIZE) >= MAX_PATH_SIZE)
        return NULL;

    if (Strlcat(path, file, MAX_PATH_SIZE) >= MAX_PATH_SIZE)
        return NULL;

    return path;
}

_Use_decl_annotations_
ZChar* ZSTempPath(ZChar path[MAX_PATH_SIZE], const char* file)
{
    if (ZStrlcpy(path, GetPath(ID_TMPDIR), MAX_PATH_SIZE) >= MAX_PATH_SIZE)
        return NULL;

    if (ZStrlcat(path, "/", MAX_PATH_SIZE) >= MAX_PATH_SIZE)
        return NULL;

    if (ZStrlcat(path, file, MAX_PATH_SIZE) >= MAX_PATH_SIZE)
        return NULL;

    return path;
}

const char* Basename(const char* path)
{
    const char* p = strrchr(path, '/');

    if (p)
        return p + 1;

    return path;
}
