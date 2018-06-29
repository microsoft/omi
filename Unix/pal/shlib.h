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
// looks like musl doesn't support RTLD_DEEPBIND, so I disable it tempararyly.
// check RTLD_DEEPBIND here: https://linux.die.net/man/3/dlopen
// musl site: https://www.musl-libc.org
// # define PAL_DLOPEN_FLAGS (RTLD_NOW | RTLD_LOCAL | RTLD_DEEPBIND)
# define PAL_DLOPEN_FLAGS (RTLD_NOW | RTLD_LOCAL)
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
    return (dlclose(self) == 0) ? 0 : -1;
}

PAL_INLINE void* Shlib_Sym(
    _In_ Shlib* self,
    _In_z_ const char* symbol)
{
    return dlsym(self, symbol);
}

PAL_Char* Shlib_Err();

PAL_INLINE void Shlib_FreeErr(
    _In_ PAL_Char* err)
{
    PAL_Free(err);
}

void Shlib_Format(
    _Pre_writable_size_(PAL_MAX_PATH_SIZE) _Null_terminated_ TChar path[PAL_MAX_PATH_SIZE],
    const char* dirName, 
    const char* shortName);

PAL_END_EXTERNC

#endif /* _pal_shlib_h */
