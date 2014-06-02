#include "shlib.h"
#include "config.h"
#include <pal/strings.h>

Shlib* Shlib_Open_Injected(
    _In_z_ const PAL_Char* path,
    NitsCallSite cs)
{
    if (NitsShouldFault(cs, NitsAutomatic))
    {
#if defined(_MSC_VER)
        /* Caller may call Shlib_Err(). */
        SetLastError(ERROR_OUTOFMEMORY);
#endif
        return NULL;
    }

    if(path == NULL)
        return NULL;
    
#if defined(_MSC_VER)
    return (Shlib*)LoadLibraryEx(path, NULL, 0);
#else
    const char *temp = NULL;

#if defined(CONFIG_ENABLE_WCHAR)
    char buffer[PAL_MAX_PATH_SIZE];
    StrWcslcpy(buffer, path, PAL_MAX_PATH_SIZE);
    temp = buffer;
#else
    temp = path;
#endif

    return (Shlib*)dlopen(temp, PAL_DLOPEN_FLAGS);
#endif
}

PAL_Char* Shlib_Err()
{
#if defined(_MSC_VER)
    PAL_Char* err = NULL;
    
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER|
        FORMAT_MESSAGE_FROM_SYSTEM|
        FORMAT_MESSAGE_IGNORE_INSERTS, 
        NULL, 
        GetLastError(), 
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
        (LPTSTR)&err, 
        0, 
        NULL);
    return err;
#else
    char* err = dlerror();
    size_t len = strlen(err) + 1;
    PAL_Char* copy = PAL_Malloc(len * sizeof(PAL_Char));
    TcsStrlcpy(copy, err, len);
    return copy;
#endif
}

_Use_decl_annotations_
void Shlib_Format(
    TChar path[PAL_MAX_PATH_SIZE],
    const char* dirName, 
    const char* shortName)
{
    *path = '\0';

    /* Directory */
    if (dirName && dirName[0] != '\0')
    {
        TcsStrlcat(path, dirName, PAL_MAX_PATH_SIZE);
        TcsStrlcat(path, "/", PAL_MAX_PATH_SIZE);
    }

    /* Prefix */
#if !defined(CONFIG_OS_WINDOWS)
    TcsStrlcat(path, "lib", PAL_MAX_PATH_SIZE);
#endif

    /* Library name */
    TcsStrlcat(path, shortName, PAL_MAX_PATH_SIZE);

    /* Suffix */
    TcsStrlcat(path, ".", PAL_MAX_PATH_SIZE);
    TcsStrlcat(path, CONFIG_SHLIBEXT, PAL_MAX_PATH_SIZE);
}
