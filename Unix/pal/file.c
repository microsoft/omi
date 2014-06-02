#include "file.h"
#include <config.h>

#if defined(PAL_HAVE_POSIX)
# include <unistd.h>
#endif

FILE* File_Open(
    _In_z_ const char* path,
    _In_z_ const char* mode)
{
#if defined(_MSC_VER)
    FILE* fp;
    return fopen_s(&fp, path, mode) == 0 ? fp : NULL;
#else
    return fopen(path, mode);
#endif
}

void File_Close(FILE* fp)
{
    fclose(fp);
}

int File_Remove(
    _In_z_ const char* path)
{
#if defined(_MSC_VER)
    return _unlink(path) == 0 ? 0 : -1;
#else
    return unlink(path) == 0 ? 0 : -1;
#endif
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
#if defined(_MSC_VER)
        long n = (long)fread(buf, 1, sizeof(buf), is);
        long m;
#else
        ssize_t n = fread(buf, 1, sizeof(buf), is);
        ssize_t m;
#endif

        if (n <= 0)
            break;

#if defined(CONFIG_OS_WINDOWS)
        m  = (long)fwrite(buf, 1, n, os);
#else
        m  = fwrite(buf, 1, n, os);
#endif

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

