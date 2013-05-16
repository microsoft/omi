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

#ifndef _io_io_h
#define _io_io_h

#include <common.h>
#include <stdio.h>
#include <stdarg.h>
#include <wchar.h>

#if defined(CONFIG_ENABLE_WCHAR)
# define Zprintf Wprintf
# define Fzprintf Fwprintf
# define Szprintf Swprintf
# define Vzprintf Vwprintf
# define Vfzprintf Vfwprintf
# define Vszprintf Vswprintf
# define Zputc fwputc
#else
# define Zprintf Printf
# define Fzprintf Fprintf
# define Szprintf Snprintf
# define Vzprintf Vprintf
# define Vfzprintf Vfprintf
# define Vszprintf Vsnprintf
# define Zputc fputc
#endif

#if defined(_WIN32) || defined( linux )
# define MI_GET_SAFE_PRINTF_STRING(p) (p)
#else
# define MI_GET_SAFE_PRINTF_STRING(p) ((p) ? (p) : "<null>")
#endif

BEGIN_EXTERNC

extern MI_EXPORT FILE* Fopen(
    const char* path,
    const char* mode);

/*
**==============================================================================
**
** Wide-character versions:
**
**==============================================================================
*/

extern int MI_EXPORT Wprintf(
    const wchar_t* format,
    ...);

extern int MI_EXPORT Fwprintf(
    FILE* os,
    const wchar_t* format,
    ...);

extern int MI_EXPORT Swprintf(
    _Out_writes_z_(size) wchar_t* buffer,
    _In_ size_t size,
    _In_z_ const wchar_t* format,
    ...);

extern int MI_EXPORT Vwprintf(
    const wchar_t* format,
    va_list ap);

extern int MI_EXPORT Vfwprintf(
    FILE* os,
    const wchar_t* format,
    va_list ap);

extern MI_EXPORT int Vswprintf(
    _Out_writes_z_(size) wchar_t* buffer,
    _In_ size_t size,
    _In_z_ const wchar_t* format,
    va_list ap);

/*
**==============================================================================
**
** single-character versions:
**
**==============================================================================
*/

extern MI_EXPORT int Printf(
    const char* format,
    ...);

extern MI_EXPORT int Fprintf(
    FILE* os,
    const char* format,
    ...);

extern MI_EXPORT int Snprintf(
    _Out_writes_z_(size) char* buffer,
    _In_ size_t size,
    _In_z_ const char* format,
    ...);

extern MI_EXPORT int Vprintf(
    const char* format,
    va_list ap);

extern MI_EXPORT int Vfprintf(
    FILE* os,
    const char* format,
    va_list ap);

extern MI_EXPORT int Vsnprintf(
    _Out_writes_z_(size) char* buffer,
    _In_ size_t size,
    _In_z_ const char* format,
    va_list ap);

/*
**==============================================================================
**
** These macros are used to type-check printf parameters. There are 3 functions:
**
**     scs - single-character string (use with %s)
**     wcs - wide-character string (use with %S)
**     zcs - z-character string (ZChar) (use with %Z)
**
** Always use these to test the assumption about argument-format agreement.
** For example:
**
**     Zprintf(ZT("%Z %S %s"), zcs(p1), wcs(p2), scs(p3));
**
**==============================================================================
*/

INLINE const char* scs(const char* str) { return str; }

INLINE const wchar_t* wcs(const wchar_t* str) { return str; }

INLINE const ZChar* zcs(const ZChar* str) { return str; }

END_EXTERNC

#endif /* _io_io_h */
