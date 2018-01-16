/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "file.h"
#include <config.h>

#if defined(PAL_HAVE_POSIX)
# include <unistd.h>
#endif

FILE* File_Open(
    _In_z_ const char* path,
    _In_z_ const char* mode)
{
    return fopen(path, mode);
}

void File_Close(FILE* fp)
{
    fclose(fp);
}

int File_Remove(
    _In_z_ const char* path)
{
    return unlink(path) == 0 ? 0 : -1;
}

int File_Touch(
    _In_z_ const char* path)
{
    FILE* fp = File_Open(path, "w");

    if (!fp)
        return -1;

    File_Close(fp);
    return 0;
}

int File_Copy(_In_z_ const char* src, _In_z_ const char* dest)
{
    FILE* is = NULL;
    FILE* os = NULL;
    char buf[4096];

    /* Open input file */
    is = File_Open(src, "rb");
    if (!is)
        return -1;

#if defined(CONFIG_POSIX)

    /* Unlink output file if it exists */
    if (access(dest, F_OK) == 0)
    {
        unlink(dest);
    }

#endif

    /* Open output file */
    os = File_Open(dest, "wb");
    if (!os)
    {
        File_Close(is);
        return -1;
    }

    /* Copy file */
    for (;;)
    {
        ssize_t n = fread(buf, 1, sizeof(buf), is);
        ssize_t m;

        if (n <= 0)
            break;

        m  = fwrite(buf, 1, n, os);

        if (m != n)
        {
            File_Close(is);
            File_Close(os);
            return -1;
        }
    }

    File_Close(is);
    File_Close(os);
    return 0;
}

