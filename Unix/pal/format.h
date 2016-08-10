/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _base_format_h
#define _base_format_h

#ifndef _MSC_VER
#include "config.h"
#if defined(CONFIG_OS_LINUX)
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#endif
#endif

#include <pal/palcommon.h>
#include <pal/format.placeholders.h>
#include <stdio.h>
#include <stdarg.h>


#ifdef _PREFAST_
 #pragma prefast(push)
 #pragma prefast(disable:28252)
 #pragma prefast(disable:28253)
#endif
#include <wchar.h>
#ifdef _PREFAST_
 #pragma prefast(pop)
#endif

#if defined(CONFIG_ENABLE_WCHAR)
# define Tprintf Wprintf
# define Ftprintf Fwprintf
# define Stprintf Swprintf
# define Stprintf_CultureInvariant Swprintf_CultureInvariant
# define Stscanf_CultureInvariant Swscanf_CultureInvariant
# define Vtprintf Vwprintf
# define Vftprintf Vfwprintf
# define Vstprintf Vswprintf
# define Vstprintf_CultureInvariant Vswprintf_CultureInvariant
# define Vstscanf_CultureInvariant Vswscanf_CultureInvariant
# define Tputc fwputc
#else
# define Tprintf Printf
# define Ftprintf Fprintf
# define Stprintf Snprintf
# define Stprintf_CultureInvariant Snprintf_CultureInvariant
# define Stscanf_CultureInvariant Sscanf_CultureInvariant
# define Vtprintf Vprintf
# define Vftprintf Vfprintf
# define Vstprintf Vsnprintf
# define Vstprintf_CultureInvariant Vsnprintf_CultureInvariant
# define Vstscanf_CultureInvariant Vsscanf_CultureInvariant
# define Tputc fputc
#endif

PAL_BEGIN_EXTERNC

/*
**==============================================================================
**
** Wide-character versions:
**
**==============================================================================
*/

int Wprintf(
    const wchar_t* format, 
    ...);

int Fwprintf(
    FILE* os, 
    const wchar_t* format, 
    ...);

int Swprintf(
    _Out_writes_z_(size) wchar_t* buffer, 
    _In_ size_t size, 
    _In_z_ const wchar_t* format, 
    ...);

int Swprintf_CultureInvariant(
    _Out_writes_z_(size) wchar_t* buffer, 
    _In_ size_t size, 
    _In_z_ const wchar_t* format, 
    ...);

int Vwprintf(
    const wchar_t* format, 
    va_list ap);

int Vfwprintf(
    FILE* os,
    const wchar_t* format, 
    va_list ap);

int Vswprintf(
    _Out_writes_z_(size) wchar_t* buffer, 
    _In_ size_t size, 
    _In_z_ const wchar_t* format, 
    va_list ap);

int Vswprintf_CultureInvariant(
    _Out_writes_z_(size) wchar_t* buffer, 
    _In_ size_t size, 
    _In_z_ const wchar_t* format, 
    va_list ap);

int Swscanf_CultureInvariant(
    _In_z_ const wchar_t* buffer, 
    _In_z_ const wchar_t* format, 
    ...);

int Vswscanf_CultureInvariant(
    _In_z_ const wchar_t* buffer, 
    _In_z_ const wchar_t* format, 
    va_list ap);

/*
**==============================================================================
**
** single-character versions:
**
**==============================================================================
*/

int Printf(
    const char* format, 
    ...);

int Fprintf(
    FILE* os, 
    const char* format, 
    ...);

int Snprintf(
    _Out_writes_z_(size) char* buffer, 
    _In_ size_t size, 
    _In_z_ const char* format, 
    ...);

int Snprintf_CultureInvariant(
    _Out_writes_z_(size) char* buffer, 
    _In_ size_t size, 
    _In_z_ const char* format, 
    ...);

int Vprintf(
    const char* format, 
    va_list ap);

int Vfprintf(
    FILE* os,
    const char* format, 
    va_list ap);

int Vsnprintf(
    _Out_writes_z_(size) char* buffer, 
    _In_ size_t size, 
    _In_z_ const char* format, 
    va_list ap);

int Vsnprintf_CultureInvariant(
    _Out_writes_z_(size) char* buffer, 
    _In_ size_t size, 
    _In_z_ const char* format, 
    va_list ap);

int Sscanf_CultureInvariant(
    _In_z_ const char* buffer, 
    _In_z_ const char* format, 
    ...);

int Vsscanf_CultureInvariant(
    _In_z_ const char* buffer, 
    _In_z_ const char* format, 
    va_list ap);

/*
**==============================================================================
**
** These macros are used to type-check printf parameters. There are 3 functions:
**
**     scs - single-character string (use with %s)
**     wcs - wide-character string (use with %S)
**     tcs - z-character string (TChar) (use with %T)
**
** Always use these to test the assumption about argument-format agreement.
** For example:
**     
**     Tprintf(PAL_T("%T %S %s"), tcs(s1), wcs(s2), scs(s3));
**
**==============================================================================
*/

PAL_INLINE const char* scs(const char* str) { return (NULL == str) ? "null" : str; }

PAL_INLINE const wchar_t* wcs(const wchar_t* str) { return (NULL == str) ? L"null" : str; }

PAL_INLINE const TChar* tcs(const TChar* str) { return (NULL == str) ?PAL_T("null") : str; }

/*
**==============================================================================
**
** Helper function built-on top of the other formatting functions/macros above
**
**==============================================================================
*/

PAL_Char* Stprintf_StrDup(_In_z_ const PAL_Char* templateString, ...);
PAL_Char* Vstprintf_StrDup(_In_z_ const PAL_Char* templateString, va_list ap);

char* FixupFormat(
    _Out_writes_z_(size) _Null_terminated_ char* buf, 
    _In_ size_t size, 
    _In_z_ const char* fmt);

wchar_t* WFixupFormat(
    _Out_writes_z_(size) _Null_terminated_ wchar_t* buf, 
    _In_ size_t size, 
    _In_z_ const wchar_t* fmt);

PAL_END_EXTERNC

#endif /* _base_format_h */
