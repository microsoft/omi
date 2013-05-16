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

#include "lib.h"

/* TODO: enhance error reporting (retrieve system error messages) */

#if defined(CONFIG_OS_WINDOWS)
# include <Windows.h>
#else
# include <dlfcn.h>
#endif

#if defined(_MSC_VER)
# pragma warning(disable : 4054)
#endif

_Use_decl_annotations_
void Lib_Format(
    char path[MAX_PATH_SIZE],
    const char* dirName,
    const char* shortName)
{
    *path = '\0';

    /* Directory */
    if (dirName && dirName[0] != '\0')
    {
        Strlcat(path, dirName, MAX_PATH_SIZE);
        Strlcat(path, "/", MAX_PATH_SIZE);
    }

    /* Prefix */
#if !defined(CONFIG_OS_WINDOWS)
    Strlcat(path, "lib", MAX_PATH_SIZE);
#endif

    /* Library name */
    Strlcat(path, shortName, MAX_PATH_SIZE);

    /* Suffix */
    Strlcat(path, ".", MAX_PATH_SIZE);
    Strlcat(path, CONFIG_SHLIBEXT, MAX_PATH_SIZE);
}

void* Lib_Open(const char* path)
{
#if defined(CONFIG_OS_WINDOWS)
    HMODULE hMod = NULL;
    size_t size = strlen(path) + 1;
    ZChar* cpPath = (ZChar*)malloc(sizeof(ZChar)*size);
    if (cpPath == NULL) return hMod;
    ZStrlcpy(cpPath, path, size);
    hMod = LoadLibraryExW(cpPath, NULL, 0);
    free(cpPath);
    return hMod;
#else
    int flags = RTLD_NOW | RTLD_LOCAL;
# ifdef hpux
    /* this options helps to resolve name conflict problem on HP */
    flags |= RTLD_GROUP;
# endif
    return dlopen(path, flags);
#endif
}

MI_Result Lib_Close(void* handle)
{
    if (!handle)
        return MI_RESULT_INVALID_PARAMETER;

#if defined(CONFIG_OS_WINDOWS)
    if (!FreeLibrary(handle))
        return MI_RESULT_FAILED;
#else
    if (dlclose(handle) != 0)
        return MI_RESULT_FAILED;
#endif

    return MI_RESULT_OK;
}

void* Lib_Sym(void* handle, const char* symbol)
{
#if defined(CONFIG_OS_WINDOWS)
    FARPROC result;
    result = GetProcAddress((HMODULE)handle, symbol);
    return (void*)result;
#else
    return dlsym(handle, symbol);
#endif
}

char* Lib_Err()
{
#if defined(CONFIG_OS_WINDOWS)
    char* err;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|
        FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&err, 0, NULL);
    return err;
#else
    return Strdup(dlerror());
#endif
}

_Use_decl_annotations_
void Lib_Free(CharPtr err)
{
#if defined(CONFIG_OS_WINDOWS)
    LocalFree(err);
#else
    free(err);
#endif
}
