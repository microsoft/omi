#ifndef __dir_h
#define __dir_h

#if defined(_MSC_VER)
# include <io.h>
# include <direct.h>
#else
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
#endif

#define MAX_PATH_SIZE 1024

typedef struct _DirEnt 
{
    char name[MAX_PATH_SIZE];
    int isDir;
}
DirEnt;

typedef struct _Dir Dir;

Dir* Dir_Open(const char* path);

DirEnt* Dir_Read(Dir* dir);

int Dir_Close(Dir* dir);

size_t Strlcpy(char* dest, const char* src, size_t size);

size_t Strlcat(char* dest, const char* src, size_t size);

int Isdir(const char* path);

#endif /* __dir_h */
