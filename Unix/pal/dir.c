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

#if defined(_MSC_VER)
# include <windows.h>
# include <sys/stat.h>
# include <io.h>
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
** Dir type (Windows)
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
    char filespec[PAL_MAX_PATH_SIZE];
    
    /* Allocate and zero-fill struct */
    dir = (Dir*)PAL_Calloc(1, sizeof(Dir));
    if (!dir)
        return NULL;

    /* Build files spec */
    {
        if (Strlcpy(filespec, path, sizeof(filespec)) >= PAL_MAX_PATH_SIZE)
            return NULL;

        if (Strlcat(filespec, "/*", sizeof(filespec)) >= PAL_MAX_PATH_SIZE)
            return NULL;
    }

    /* Find first file matching the file spec */
    dir->handle = _findfirst(filespec, &dir->fileinfo);
    if (dir->handle == -1)
    {
        PAL_Free(dir);
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

    Strlcpy(dir->ent.name, dir->fileinfo.name, PAL_MAX_PATH_SIZE);
    dir->firstTime = 0;
    return &dir->ent;
}

int Dir_Close(Dir* dir)
{
    _findclose(dir->handle);
    PAL_Free(dir);
    return 0;
}

#endif /* defined(_MSC_VER) */

/*
**==============================================================================
**
** Isdir()
**
**==============================================================================
*/

PAL_Boolean Isdir(const char* path)
{
#if defined(_MSC_VER)
    {
        struct _stat st;

        if (_stat(path, &st) != 0)
            return 0;

        return (_S_IFDIR  & st.st_mode) ? PAL_TRUE : PAL_FALSE;
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
