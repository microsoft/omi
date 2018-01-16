/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "dir.h"
#include <base/paths.h>
#include <pal/strings.h>
#include <ctype.h>

#if defined(PAL_HAVE_POSIX)
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
#endif

/*
**==============================================================================
**
** Dir type (POSIX)
**
**==============================================================================
*/

#if defined(PAL_HAVE_POSIX)

struct _Dir
{
    DIR* dir;
    DirEnt ent;
};

Dir* Dir_Open(const char* path)
{
    Dir* self = (Dir*)PAL_Calloc(1, sizeof(Dir));

    if (!self)
        return NULL;

    self->dir = opendir(path);
    if (!self->dir)
    {
        PAL_Free(self);
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
        PAL_Free(self);
        return -1;
    }

    PAL_Free(self);
    return 0;
}

#endif /* defined(PAL_HAVE_POSIX) */

/*
**==============================================================================
**
** Isdir()
**
**==============================================================================
*/

PAL_Boolean Isdir(const char* path)
{
    {
        struct stat st;

        if (stat(path, &st) != 0)
            return 0;

        return S_ISDIR(st.st_mode);
    }
}

const char* Basename(const char* path)
{
    const char* p = strrchr(path, '/');

    if (p)
        return p + 1;

    return path;
}

int Mkdirhier(const char* path_, int mode)
{
    char path[PAL_MAX_PATH_SIZE];
    char buf[PAL_MAX_PATH_SIZE];
    char* p;
    char* context = NULL;

    /* Make a complete copy of the path (that we can destroy) */
    if (Strlcpy(path, path_, sizeof(path)) >= sizeof(path))
        return -1;

    buf[0] = '\0';

    for (p = Strtok(path, "/", &context); p; p = Strtok(NULL, "/", &context))
    {
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
