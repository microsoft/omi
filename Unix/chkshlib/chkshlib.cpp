#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <pal/shlib.h>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage %s SHAREDLIBRARY\n", argv[0]);
        exit(1);
    }

    void* handle = dlopen(argv[1], PAL_DLOPEN_FLAGS);

    if (!handle)
    {
        fprintf(stderr, "%s: %s\n", argv[0], dlerror());
        exit(1);
    }

    dlclose(handle);

    return 0;
}
