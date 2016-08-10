/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _pal_shlib_h
#define _pal_shlib_h

#include <stddef.h>
#include <string.h>
#include <nits/base/nits.h>

#if defined(PAL_HAVE_POSIX)
# include <dlfcn.h>
#endif

#if defined(linux)
# define PAL_DLOPEN_FLAGS (RTLD_NOW | RTLD_LOCAL | RTLD_DEEPBIND)
#else
# define PAL_DLOPEN_FLAGS (RTLD_NOW | RTLD_LOCAL)
#endif

PAL_BEGIN_EXTERNC

typedef struct _Shlib Shlib;

Shlib* Shlib_Open_Injected(
    _In_z_ const PAL_Char* path,
    NitsCallSite cs);


#define Shlib_Open(path) Shlib_Open_Injected(path, NitsHere())

PAL_INLINE int Shlib_Close(
    _Inout_ Shlib* self)
{
#if defined(_MSC_VER)
    return FreeLibrary((HMODULE)self) ? 0 : -1;
#else
    return (dlclose(self) == 0) ? 0 : -1;
#endif
}

PAL_INLINE void* Shlib_Sym(
    _In_ Shlib* self,
    _In_z_ const char* symbol)
{
#if defined(_MSC_VER)
#pragma warning(disable:4054)
#pragma warning(disable:4055)

    FARPROC result;
    result = GetProcAddress((HMODULE)self, symbol);
    return (void*)result;
#else
    return dlsym(self, symbol);
#endif
}

PAL_Char* Shlib_Err();

PAL_INLINE void Shlib_FreeErr(
    _In_ PAL_Char* err)
{
#if defined(_MSC_VER)
    LocalFree(err);
#else
    PAL_Free(err);
#endif
}

void Shlib_Format(
    _Pre_writable_size_(PAL_MAX_PATH_SIZE) _Null_terminated_ TChar path[PAL_MAX_PATH_SIZE],
    const char* dirName, 
    const char* shortName);

PAL_END_EXTERNC

#endif /* _pal_shlib_h */
