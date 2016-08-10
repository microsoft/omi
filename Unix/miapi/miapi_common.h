/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/


#if !defined(_miapi_common_h_)
#define _miapi_common_h_

#include <pal/format.h>

#if defined(_MSC_VER)
#define MI_CLIENT_IMPERSONATION_TOKEN HANDLE
#else
#define _aligned_malloc(size, ignore) PAL_Malloc(size)
#define _aligned_free(ptr) PAL_Free(ptr)
#define MI_CLIENT_IMPERSONATION_TOKEN void *
#if !defined(INVALID_HANDLE_VALUE)
#define INVALID_HANDLE_VALUE 0
#endif
#define TerminateProcess(process,code) exit(code)
#define GetCurrentProcess() 0
#define SecureZeroMemory(dest, size) memset(dest, 0, size)
#endif
#endif

