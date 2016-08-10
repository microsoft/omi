/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/*
**==============================================================================
**
** fixfiles:
**
**     This program performs three tasks:
**
**     (1) 'Fixes' text files (files made of ASCII 7-bit characters). This
**         involves two changes:
**
**         (*) Converting "\r\n" sequences to "\n"
**         (*) Appending "\n" to files that are missing this ending.
**
**     (2) Removes Windows internal files, such as:
**
**         sources
**         sources.dep
**         sources.inc
**         dirs
**         buildchk.dbb
**         buildchk.err
**         buildchk.evt
**         buildchk.log
**         buildchk.prf
**         buildchk.rec
**         buildchk.trc
**         buildchk.wrn
**         buildfre.dbb
**         buildfre.err
**         buildfre.evt
**         buildfre.log
**         buildfre.prf
**         buildfre.rec
**         buildfre.trc
**         buildfre.wrn
**         makefile.cmn
**         project.mk
**         *.cmd
**         *.rc
**
**     (3) Makes script files executable (files beginning with "#!" sequences).
**
**     This fixdist script compiles this program and runs it on the fly.
**
**     Note that this program examines all files in the distribution and runs
**     in under 2 seconds on Linux. It is slower on older Unix platforms but
**     quite fast.
**
**==============================================================================
*/

#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

#define FIXDIST_MAX_PATH 1024

const char* arg0;

typedef enum _Boolean
{
    BOOLEAN_FALSE = 0,
    BOOLEAN_TRUE = 1,
}
Boolean;

static int LoadFile(
    const char* path, 
    size_t extraBytes,
    char** dataOut, 
    size_t* sizeOut,
    unsigned int* mode)
{
    char* data;
    size_t size;
    FILE* is;

    /* Clear output parameters */
    *dataOut = NULL;
    *sizeOut = 0;

    /* Stat this file (to get the size) */
    {
        struct stat st;

        if (stat(path, &st) != 0)
            return -1;

        size = (size_t)st.st_size;
        *mode = (unsigned int)st.st_mode;
    }

    /* Allocate the buffer */
    if (!(data = (char*)malloc(size + extraBytes)))
        return -1;

    /* Open the file */
    if (!(is = fopen(path, "rb")))
    {
        free(data);
        return -1;
    }

    /* Read the file into the buffer */
    {
        size_t n;
        char buf[BUFSIZ];
        char* end = data;

        while ((n = fread(buf, 1, sizeof(buf), is)) > 0)
        {
            size_t remaining = size - (end - data);

            /* No room in output buffer? (file grew since stat() called) */
            if (n > remaining)
            {
                fclose(is);
                free(data);
                return -1;
            }

            memcpy(end, buf, n);
            end += n;
        }

        if (ferror(is) != 0)
        {
            fclose(is);
            free(data);
            return -1;
        }
    }

    /* Close the file */
    fclose(is);

    /* Set output parameters */
    *dataOut = data;
    *sizeOut = size;

    return 0;
}

static int WriteFile(
    const char* path,
    const char* data, 
    size_t size)
{
    FILE* os;

    /* Open file */
    if (!(os = fopen(path, "wb")))
        return -1;

    /* Write file */
    {
        size_t n;

        while ((n = fwrite(data, 1, size, os)) > 0)
        {
            data += n;
            size -= n;
        }

        if (ferror(os) != 0)
        {
            fclose(os);
            return -1;
        }
    }

    fclose(os);

    return size == 0 ? 0 : -1;
}

static Boolean HasTextExtension(const char* path)
{
    static const char* extensions[] =
    {
        ".c",
        ".h",
        ".cpp",
        ".inc",
        ".mof",
    };
    size_t numExtensions = sizeof(extensions) / sizeof(extensions[0]);
    size_t i = 0;
    const char* p;
    
    if (!(p = strrchr(path, '.')))
    {
        return BOOLEAN_FALSE;
    }

    for (i = 0; i < numExtensions; i++)
    {
        if (strcmp(p, extensions[i]) == 0)
            return BOOLEAN_TRUE;
    }

    return BOOLEAN_FALSE;
}

static Boolean IsText(
    const char* data, 
    size_t size, 
    size_t* line,
    char* ch)
{
    const char* p = data;
    const char* end = data + size;

    *line = 1;
    *ch = '\0';

    while (p != end)
    {
        char c = *p++;

        if (c == '\n')
            (*line)++;

        if (!isprint(c) && c != '\n' && c != '\r' && c != '\f' && c != '\t')
        {
            *ch = c;
            return BOOLEAN_FALSE;
        }
    }

    return BOOLEAN_TRUE;
}

static int FixFile(const char* path)
{
    char* data;
    size_t size;
    int modified = 0;
    const size_t extraBytes = 2;
    unsigned int mode;
    size_t line;
    char ch;

    /* Load the file (allocate extra bytes for '\0' terminator and '\n' */
    if (LoadFile(path, extraBytes, &data, &size, &mode) != 0)
    {
        fprintf(stderr, "%s: failed to read file: %s\n", arg0, path);
        exit(1);
    }

    /* Skip non-ASCII files */
    if (!IsText(data, size, &line, &ch))
    {
        if (HasTextExtension(path))
        {
            fprintf(
                stderr, 
                "%s(%u): warning: non-standard character: %u\n",
                path,
                (unsigned int)line,
                (unsigned char)ch);
        }
        return 0;
    }

    /* Null terminate the buffer */
    data[size] = '\0';

    /* Replace "\r\n" sequences with "\n" */
    {
        const char* p = data;
        char* q = data;
        const char* end = data + size;

        while (p != end)
        {
            if (p[0] == '\r' && p[1] == '\n')
            {
                p++;
                size--;
                modified = 1;
            }

            *q++ = *p++;
        }
    }

    /* Add '\n' to the end if missing */
    if (size > 0 && data[size-1] != '\n')
    {
        data[size++] = '\n';
        data[size] = '\0';
        modified = 1;
    }

    /* If file was modified above */
    if (modified)
    {
        /* Remove the original file */
        if (unlink(path) != 0)
        {
            fprintf(stderr, "%s: failed to remove file: %s\n", arg0, path);
            exit(1);
        }

        /* Write the new file */
        if (WriteFile(path, data, size) != 0)
        {
            fprintf(stderr, "%s: failed to write file: %s\n", arg0, path);
            exit(1);
        }

#if 0
        printf("Modified %s\n", path);
#endif
    }

    /* Make script file executable */

    if (data[0] == '#' && data[1] == '!')
    {
        chmod(path, mode | S_IXUSR);
    }

    free(data);
    return 0;
}

static Boolean IsWindowsFile(const char* path)
{
    const char* names[] =
    {
        "sources",
        "sources.dep",
        "sources.inc",
        "dirs",
        "buildchk.dbb",
        "buildchk.err",
        "buildchk.evt",
        "buildchk.log",
        "buildchk.prf",
        "buildchk.rec",
        "buildchk.trc",
        "buildchk.wrn",
        "buildfre.dbb",
        "buildfre.err",
        "buildfre.evt",
        "buildfre.log",
        "buildfre.prf",
        "buildfre.rec",
        "buildfre.trc",
        "buildfre.wrn",
        "makefile.cmn",
        "project.mk"
    };
    const size_t numNames = sizeof(names) / sizeof(names[0]);
    size_t i;

    for (i = 0; i < numNames; i++)
    {
        const char* p = strrchr(path, '/');

        if (p)
            p++;
        else
            p = path;

        if (strcmp(p, names[i]) == 0)
        {
            return BOOLEAN_TRUE;
        }

        /* Check for files with the '.cmd' extension */
        if ((p = strrchr(path, '.')) && strcmp(p, ".cmd") == 0)
        {
            return BOOLEAN_TRUE;
        }

        /* Check for files with the '.rc' extension */
        if ((p = strrchr(path, '.')) && strcmp(p, ".rc") == 0)
        {
            return BOOLEAN_TRUE;
        }
    }

    /* Not a windows file */
    return BOOLEAN_FALSE;
}

static void FixDir(const char* path)
{
    DIR* dir;
    struct dirent* ent;
    char** dirs;
    size_t dirsSize = 0;
    size_t dirsCap = 64;
    size_t i;

    /* Allocate dynamic array to hold directories */
    if (!(dirs = (char**)malloc(dirsCap * sizeof(char*))))
    {
        fprintf(stderr, "%s: malloc failed\n", arg0);
        exit(1);
    }

#if 0
    printf("path{%s}\n", path);
#endif
    
    if (!(dir = opendir(path)))
    {
        fprintf(stderr, "%s: failed to open directory: %s\n", arg0, path);
        exit(1);
    }

    while ((ent = readdir(dir)))
    {
        char buf[FIXDIST_MAX_PATH];
        struct stat st;

        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            continue;

        *buf = '\0';
        strncat(buf, path, sizeof(buf) - 1);
        strncat(buf, "/", sizeof(buf) - 1 - strlen(buf));
        strncat(buf, ent->d_name, sizeof(buf) - 1 - strlen(buf));

        if (stat(buf, &st) != 0)
        {
            fprintf(stderr, "%s: failed to stat: %s\n", arg0, buf);
            exit(1);
        }

        if (st.st_mode & S_IFDIR)
        {
            char* p = strdup(buf);

            if (!p)
            {
                fprintf(stderr, "%s: out of memory\n", arg0);
                exit(1);
            }

            if (dirsSize == dirsCap)
            {
                dirsCap *= 2;

                if (!(dirs = (char**)realloc(dirs, dirsCap * sizeof(char*))))
                {
                    fprintf(stderr, "%s: realloc failed\n", arg0);
                    exit(1);
                }
            }

            dirs[dirsSize++] = p;
        }
        else
        {
            if (IsWindowsFile(buf))
            {
                unlink(buf);
#if 0
                printf("Removed %s\n", buf);
#endif
            }
            else
            {
                FixFile(buf);
            }
        }
    }

    /* Close the directory */
    closedir(dir);

    /* Process subdirectories */
    for (i = 0; i < dirsSize; i++)
    {
        FixDir(dirs[i]);
        free(dirs[i]);
    }

    free(dirs);
}

int main(int argc, char** argv)
{
    arg0 = argv[0];

    if (argc != 1)
    {
        fprintf(stderr, "Usage: %s\n", arg0);
        exit(1);
    }

    /* Fix all files in this directory and beneath it */
    FixDir(".");

    return 0;
}
