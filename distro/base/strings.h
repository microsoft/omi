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

#ifndef _base_strings_h
#define _base_strings_h

#include <common.h>
#include <wchar.h>
#include <string.h>

/* Maximum path length */
#define MAX_PATH_SIZE 1024

BEGIN_EXTERNC

MI_INLINE int Wcscmp(const wchar_t* s1, const wchar_t* s2)
{
    return wcscmp(s1, s2);
}

MI_INLINE int Strcmp(const char* s1, const char* s2)
{
    return strcmp(s1, s2);
}

MI_INLINE int Zcmp(const ZChar* s1, const ZChar* s2)
{
#if (MI_CHAR_TYPE == 1)
    return Strcmp(s1, s2);
#else
    return Wcscmp(s1, s2);
#endif
}

MI_INLINE int Zncmp(const ZChar* s1, const ZChar* s2, size_t n)
{
#if (MI_CHAR_TYPE == 1)
    return strncmp(s1, s2, n);
#else
    return wcsncmp(s1, s2, n);
#endif
}

MI_INLINE size_t Strlen(const char* str)
{
    return strlen(str);
}

size_t Wcslen(_In_z_ const wchar_t* str);

MI_INLINE size_t Zlen(const ZChar* str)
{
#if (MI_CHAR_TYPE == 1)
    return Strlen(str);
#else
    return Wcslen(str);
#endif
}

MI_INLINE CharPtr Strdup(_In_z_ const char* s)
{
#if defined(_MSC_VER)
    return _strdup(s);
#else
    return strdup(s);
#endif
}

MI_INLINE WcharPtr Wcsdup(_In_z_ const wchar_t* s)
{
#if defined(_MSC_VER)
    return _wcsdup(s);
#else
  #if defined(sun) || defined(__hpux)
    size_t n = wcslen(s);

    wchar_t* dest = (wchar_t*)malloc((n + 1) * sizeof (wchar_t));
    if (dest != NULL)
        memcpy(dest, s, (n + 1) * sizeof (wchar_t));
    return dest;
  #else
    extern wchar_t* wcsdup(const wchar_t*);

    return wcsdup(s);
  #endif
#endif
}

MI_INLINE ZChar* Zdup(const ZChar* s)
{
#if (MI_CHAR_TYPE == 1)
    return Strdup(s);
#else
    return Wcsdup(s);
#endif
}

char* ZStrdup(_In_z_ const ZChar* str);

MI_INLINE int Strcasecmp(const char* s1, const char* s2)
{
#if defined(_MSC_VER)
    return _stricmp(s1, s2);
#else
    return strcasecmp(s1, s2);
#endif
}

#if (MI_CHAR_TYPE != 1)
MI_INLINE int Wcscasecmp(const wchar_t* s1, const wchar_t* s2)
{
#if defined(_MSC_VER)
    return _wcsicmp(s1, s2);
#else
# if defined(__GNUC__)
    extern int wcscasecmp(const wchar_t*, const wchar_t*);
# endif
    return wcscasecmp(s1, s2);
#endif
}
#endif

MI_INLINE int Zcasecmp(const ZChar* s1, const ZChar* s2)
{
#if (MI_CHAR_TYPE == 1)
    return Strcasecmp(s1, s2);
#else
    return Wcscasecmp(s1, s2);
#endif
}

MI_INLINE int Strncasecmp(const char* s1, const char* s2, size_t n)
{
#if defined(_MSC_VER)
    return _strnicmp(s1, s2, n);
#else
    return strncasecmp(s1, s2, n);
#endif
}

#if (MI_CHAR_TYPE != 1)
MI_INLINE int Wcsncasecmp(const wchar_t* s1, const wchar_t* s2, size_t n)
{
#if defined(_MSC_VER)
    return _wcsnicmp(s1, s2, n);
#else
# if defined(__GNUC__)
    extern int wcsncasecmp(const wchar_t*, const wchar_t*, size_t n);
# endif
    return wcsncasecmp(s1, s2, n);
#endif
}
#endif

MI_INLINE int Zncasecmp(const ZChar* s1, const ZChar* s2, size_t n)
{
#if (MI_CHAR_TYPE == 1)
    return Strncasecmp(s1, s2, n);
#else
    return Wcsncasecmp(s1, s2, n);
#endif
}

MI_INLINE unsigned long Strtoul(_In_z_ const char* str, _Out_opt_ _Deref_post_z_ char** end, int base)
{
    return strtoul(str, end, base);
}

#if (MI_CHAR_TYPE != 1)
MI_INLINE unsigned long Wcstoul(_In_z_ const wchar_t* str, _Out_opt_ _Deref_post_z_ wchar_t** end, int base)
{
    return wcstoul(str, end, base);
}
#endif

MI_INLINE unsigned long Ztoul(_In_z_ const ZChar* str, _Out_opt_ _Deref_post_z_ ZChar** end, int base)
{
#if (MI_CHAR_TYPE == 1)
    return Strtoul(str, end, base);
#else
    return Wcstoul(str, end, base);
#endif
}

MI_INLINE long Strtol(_In_z_ const char* str, _Out_opt_ _Deref_post_z_ char** end, int base)
{
    return strtol(str, end, base);
}

#if (MI_CHAR_TYPE != 1)
MI_INLINE long Wcstol(_In_z_ const wchar_t* str, _Out_opt_ _Deref_post_z_ wchar_t** end, int base)
{
    return wcstol(str, end, base);
}
#endif

MI_INLINE long Ztol(_In_z_ const ZChar* str, _Out_opt_ _Deref_post_z_ ZChar** end, int base)
{
#if (MI_CHAR_TYPE == 1)
    return Strtol(str, end, base);
#else
    return Wcstol(str, end, base);
#endif
}

MI_INLINE MI_Uint64 Strtoull(_In_z_ const char* str, _Out_opt_ _Deref_post_z_ char** end, int base)
{
#if defined(_MSC_VER)
    return _strtoui64(str, end, base);
#else
    return strtoull(str, end, base);
#endif
}

#if (MI_CHAR_TYPE != 1)
MI_INLINE MI_Uint64 Wcstoull(_In_z_ const wchar_t* str, _Out_opt_ _Deref_post_z_ wchar_t** end, int base)
{
#if defined(_MSC_VER)
    return _wcstoui64(str, end, base);
#else
    extern unsigned long long wcstoull(const wchar_t* s, wchar_t** e, int b);
    return wcstoull(str, end, base);
#endif
}
#endif

MI_INLINE MI_Uint64 Ztoull(_In_z_ const ZChar* str, _Out_opt_ _Deref_post_z_ ZChar** end, int base)
{
#if (MI_CHAR_TYPE == 1)
    return Strtoull(str, end, base);
#else
    return Wcstoull(str, end, base);
#endif
}

/*BOOKMARK*/
MI_INLINE MI_Sint64 Strtoll(_In_z_ const char* str, _Out_opt_ _Deref_post_z_ char** end, int base)
{
#if defined(_MSC_VER)
    return _strtoi64(str, end, base);
#else
    return strtoll(str, end, base);
#endif
}

#if (MI_CHAR_TYPE != 1)
MI_INLINE MI_Sint64 Wcstoll(_In_z_ const wchar_t* str, _Out_opt_ _Deref_post_z_ wchar_t** end, int base)
{
#if defined(_MSC_VER)
    return _wcstoi64(str, end, base);
#else
    extern long long wcstoll(const wchar_t* s, wchar_t** e, int b);
    return wcstoll(str, end, base);
#endif
}
#endif

MI_INLINE MI_Sint64 Ztoll(_In_z_ const ZChar* str, _Out_opt_ _Deref_post_z_ ZChar** end, int base)
{
#if (MI_CHAR_TYPE == 1)
    return Strtoll(str, end, base);
#else
    return Wcstoll(str, end, base);
#endif
}

MI_INLINE double Strtod(_In_z_ const char* str, _Out_opt_ _Deref_post_z_ char** end)
{
    return strtod(str, end);
}

MI_INLINE double Wcstod(_In_z_ const wchar_t* str, _Out_opt_ _Deref_post_z_ wchar_t** end)
{
    return wcstod(str, end);
}

MI_INLINE double Ztod(_In_z_ const ZChar* str, _Out_opt_ _Deref_post_z_ ZChar** end)
{
#if (MI_CHAR_TYPE == 1)
    return Strtod(str, end);
#else
    return Wcstod(str, end);
#endif
}

MI_INLINE ZChar* Zchr(_In_z_ const ZChar* str, ZChar ch)
{
#if (MI_CHAR_TYPE == 1)
    return (ZChar*)strchr(str, ch);
#else
    return (ZChar*)wcschr(str, ch);
#endif
}

MI_INLINE ZChar* Zrchr(_In_z_ const ZChar* str, ZChar ch)
{
#if (MI_CHAR_TYPE == 1)
    return (ZChar*)strrchr(str, ch);
#else
    return (ZChar*)wcsrchr(str, ch);
#endif
}

MI_INLINE char* Strcat(_Inout_updates_z_(count) char* dest, size_t count, _In_z_ const char* src)
{
#if defined(_MSC_VER)
    strcat_s(dest, count, src);
    return dest;
#else
    return strcat(dest, src);
#endif
}

MI_INLINE char* Strtok(_Inout_opt_z_ char* str, _In_z_ const char* delim, _Inout_ _Deref_prepost_opt_z_ char** context)
{
#if defined(_MSC_VER)
    return strtok_s(str, delim, context);
#else
    return strtok_r(str, delim, context);
#endif
}

size_t Strlcat(_Inout_updates_z_(size) char* dest, _In_z_ const char* src, size_t size);

size_t Strlcpy(_Out_writes_z_(size) char* dest, _In_z_ const char* src, size_t size);

size_t ZStrlcat(_Inout_updates_z_(size) ZChar* dest, _In_z_ const char* src, size_t size);

size_t ZStrlcpy(_Out_writes_z_(size) ZChar* dest, _In_z_ const char* src, size_t size);

size_t StrZlcpy(_Out_writes_z_(size) char* dest, _In_z_ const ZChar* src, size_t size);

size_t Zlcat(_Inout_updates_z_(size) ZChar* dest, _In_z_ const ZChar* src, size_t size);

size_t Zlcpy(_Out_writes_z_(size) ZChar* dest, _In_z_ const ZChar* src, size_t size);

INLINE ZChar* StrToZ(_Out_writes_z_(size) ZChar* buf, size_t size, _In_z_ const char* src)
{
    ZStrlcpy(buf, src, size);
    return buf;
}

INLINE char* ZToStr(_Out_writes_z_(size) char* buf, size_t size, _In_z_ const ZChar* src)
{
    StrZlcpy(buf, src, size);
    return buf;
}

_Success_(return != NULL) _Ret_notnull_
_Post_readable_size_(*size)
_Null_terminated_ const char* Uint32ToStr(_Pre_writable_size_(11) char buf[11], MI_Uint32 x, size_t* size);

_Success_(return != NULL) _Ret_notnull_
_Post_readable_size_(*size)
_Null_terminated_ const char* Uint64ToStr(_Pre_writable_size_(21) char buf[21], MI_Uint64 x, size_t* size);

#if (MI_CHAR_TYPE == 1)
_Success_(return != NULL) _Ret_notnull_
_Post_readable_size_(*size)
INLINE const ZChar* Uint32ToZStr(_Pre_writable_size_(11) ZChar buf[11], MI_Uint32 x, size_t* size)
{
    return Uint32ToStr(buf, x, size);
}

_Success_(return != NULL) _Ret_notnull_
_Post_readable_size_(*size)
INLINE const ZChar* Uint64ToZStr(_Pre_writable_size_(21) ZChar buf[21], MI_Uint64 x, size_t* size)
{
    return Uint64ToStr(buf, x, size);
}
#else
_Success_(return != NULL) _Ret_notnull_
_Post_readable_size_(*size)
const ZChar* Uint32ToZStr(_Pre_writable_size_(11) ZChar buf[11], MI_Uint32 x, size_t* size);

_Success_(return != NULL) _Ret_notnull_
_Post_readable_size_(*size)
const ZChar* Uint64ToZStr(_Pre_writable_size_(21) ZChar buf[21], MI_Uint64 x, size_t* size);
#endif

END_EXTERNC

#endif /* _base_strings_h */
