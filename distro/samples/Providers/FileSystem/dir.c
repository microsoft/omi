#include "dir.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#if defined(_MSC_VER)
# include <windows.h>
# include <sys/stat.h>
# include <io.h>
#else
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
#endif

/*
**==============================================================================
**
** POSIC Implementation
**
**==============================================================================
*/

#if !defined(_MSC_VER)

struct _Dir
{
    char path[MAX_PATH_SIZE];
    DIR* dir;
    DirEnt ent;
};

Dir* Dir_Open(const char* path)
{
    Dir* self = (Dir*)calloc(1, sizeof(Dir));

    if (!self)
        return NULL;

    Strlcpy(self->path, path, sizeof(self->path));

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

    /* Determine whether it is a directory or data file */
    {
        char path[MAX_PATH_SIZE];
        Strlcpy(path, self->path, sizeof(path));
        Strlcat(path, "/", sizeof(path));
        Strlcat(path, p->d_name, sizeof(path));
        self->ent.isDir = Isdir(path);
    }

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

#endif

/*
**==============================================================================
**
** Windows Implementation
**
**==============================================================================
*/

#if defined(_MSC_VER)

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

    /* Save path */

    Strlcpy(self->path, path, sizeof(self->path));

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

    /* Determine whether it is a directory or data file */
    {
        char path[MAX_PATH_SIZE];
        Strlcpy(path, self->path, sizeof(path));
        Strlcat(path, "/", sizeof(path));
        Strlcpy(path, p->d_name, sizeof(path));
        self->ent.isDir = Isdir(path);
    }

    return &dir->ent;
}

int Dir_Close(Dir* dir)
{
    _findclose(dir->handle);
    free(dir);
    return 0;
}

#endif

int Isdir(const char* path)
{
#if defined(CONFIG_OS_WINDOWS)
    {
        struct _stat st;

        if (_stat(path, &st) != 0)
            return 0;

        return _S_IFDIR & st.st_mode;
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
