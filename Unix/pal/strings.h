/*
**==============================================================================
**
** strings.h:
**
**     This file defines string-manipluation functions. For each string 
**     operation, there are three implementations:
**
**         - Single-character - char
**         - Wide-character - wchar_t
**         - T-character - TChar (char or wchar_t depending on configuration)
**
**     Each string function has one of the following prefixes:
**
**         - Str - single character string
**         - Wcs - wide character string
**         - Tcs - T-character string
**
**     For example, the are three variants for simple copying of strings:
**
**         - Strcpy() - same as strcpy()
**         - Wcscpy() - same as wcscpy()
**         - Tcscpy() - same as strcpy() or wcscpy() depending on configuration.
**
**     When passing string literals to the Tcs* variant functions, use the
**     PAL_T() macro. For example:
**
**         TChar buf[32];
**         Tcscpy(buf, PAL_T("Hello"));
**
**     For the typedef TChar, one of the following is true:
**
**         sizeof(TChar) == sizeof(char)
**         sizeof(TChar) == sizeof(wchar_t)
**
**     If the latter is true, then CONFIG_ENABLE_WCHAR is defined.
**
**==============================================================================
*/

#ifndef _pal_strings_h
#define _pal_strings_h

#ifdef _PREFAST_
 #pragma prefast(push)
 #pragma prefast(disable:28252)
 #pragma prefast(disable:28253)
#endif
#include <wchar.h>
#include <string.h>
#ifdef _PREFAST_
 #pragma prefast(pop)
#endif

#include "palcommon.h"

PAL_BEGIN_EXTERNC

/*
**==============================================================================
**
** Strcmp()
** Wcscmp()
** Tcscmp()
**
**==============================================================================
*/

PAL_INLINE int Wcscmp(
    _In_z_ const wchar_t* s1, 
    _In_z_ const wchar_t* s2)
{
    return wcscmp(s1, s2);
}

PAL_INLINE int Strcmp(
    _In_z_ const char* s1, 
    _In_z_ const char* s2)
{
    return strcmp(s1, s2);
}

PAL_INLINE int Tcscmp(
    _In_z_ const TChar* s1, 
    _In_z_ const TChar* s2)
{
#if defined(CONFIG_ENABLE_WCHAR)
    return Wcscmp(s1, s2);
#else
    return Strcmp(s1, s2);
#endif
}

/*
**==============================================================================
**
** Strncmp()
** Wcsncmp()
** Tcsncmp()
**
**==============================================================================
*/

#ifdef _PREFAST_
 #pragma prefast(push)
 #pragma prefast(disable:26061)
#endif

_When_(return == 0, _Post_satisfies_(
        ((_String_length_(s1) >= n) && (_String_length_(s2) >= n)) ||
        ((_String_length_(s1) < n) && (_String_length_(s2) < n) && (_String_length_(s1) == _String_length_(s2)))
    ))
PAL_INLINE int Strncmp(
    _In_z_ const char* s1, 
    _In_z_ const char* s2, 
    size_t n)
{
    return strncmp(s1, s2, n);
}

_When_(return == 0, _Post_satisfies_(
        ((_String_length_(s1) >= n) && (_String_length_(s2) >= n)) ||
        ((_String_length_(s1) < n) && (_String_length_(s2) < n) && (_String_length_(s1) == _String_length_(s2)))
    ))
PAL_INLINE int Wcsncmp(
    _In_z_ const wchar_t* s1, 
    _In_z_ const wchar_t* s2, 
    size_t n)
{
    return wcsncmp(s1, s2, n);
}

#ifdef _PREFAST_
 #pragma prefast(pop)
#endif

_When_(return == 0, _Post_satisfies_(
        ((_String_length_(s1) >= n) && (_String_length_(s2) >= n)) ||
        ((_String_length_(s1) < n) && (_String_length_(s2) < n) && (_String_length_(s1) == _String_length_(s2)))
    ))
PAL_INLINE int Tcsncmp(
    _In_z_ const TChar* s1, 
    _In_z_ const TChar* s2, 
    size_t n)
{
#if defined(CONFIG_ENABLE_WCHAR)
    return Wcsncmp(s1, s2, n);
#else
    return Strncmp(s1, s2, n);
#endif
}

/*
**==============================================================================
**
** Strlen()
** Wcslen()
** Tcslen()
**
**==============================================================================
*/

#ifdef _PREFAST_
 #pragma prefast(push)
 #pragma prefast(disable:28196)
 /* 
  * WinBlue bug #48847
  *
  * wcslen and strlen in sdpublic\sdk\inc\crt\string.h 
  * do not have any SAL annotations.  My attempt to work around by
  * _Analysis_assume_ or wcsnlen_s has failed, so I am just disabling
  * prefast warning for these 2 functions
  */
#endif

_Post_satisfies_(return == _String_length_(str))
PAL_INLINE size_t Strlen(
    _In_z_ const char* str)
{
    return strlen(str);
}

_Post_satisfies_(return == _String_length_(str))
PAL_INLINE size_t Wcslen(
    _In_z_ const wchar_t* str)
{
    return wcslen(str);
}

#ifdef _PREFAST_
 #pragma prefast(pop)
#endif

_Post_satisfies_(return == _String_length_(str))
PAL_INLINE size_t Tcslen(
    _In_z_ const TChar* str)
{
#if defined(CONFIG_ENABLE_WCHAR)
    return Wcslen(str);
#else
    return Strlen(str);
#endif
}

/*
**==============================================================================
**
** Strcasecmp()
** Wcscasecmp()
** Tcscasecmp()
**
**==============================================================================
*/

PAL_INLINE int Strcasecmp(
    _In_z_ const char* s1, 
    _In_z_ const char* s2)
{
#if defined(_MSC_VER)
    return _stricmp(s1, s2);
#else
    return strcasecmp(s1, s2);
#endif
}

PAL_INLINE int Wcscasecmp(
    _In_z_ const wchar_t* s1, 
    _In_z_ const wchar_t* s2)
{
#if defined(_MSC_VER)
    return _wcsicmp(s1, s2);
#else
    extern int wcscasecmp(const wchar_t*, const wchar_t*);
    return wcscasecmp(s1, s2);
#endif
}

PAL_INLINE int Tcscasecmp(
    _In_z_ const TChar* s1, 
    _In_z_ const TChar* s2)
{
#if defined(CONFIG_ENABLE_WCHAR)
    return Wcscasecmp(s1, s2);
#else
    return Strcasecmp(s1, s2);
#endif
}

/*
**==============================================================================
**
** Strncasecmp()
** Wcsncasecmp()
** Tcsncasecmp()
**
**==============================================================================
*/

#ifdef _PREFAST_
 #pragma prefast(push)
 #pragma prefast(disable:26061)
#endif

_When_(return == 0, _Post_satisfies_(
        ((_String_length_(s1) >= n) && (_String_length_(s2) >= n)) ||
        ((_String_length_(s1) < n) && (_String_length_(s2) < n) && (_String_length_(s1) == _String_length_(s2)))
    ))
PAL_INLINE int Strncasecmp(
    _In_z_ const char* s1, 
    _In_z_ const char* s2, 
    size_t n)
{
#if defined(_MSC_VER)
    return _strnicmp(s1, s2, n);
#else
    return strncasecmp(s1, s2, n);
#endif
}

_When_(return == 0, _Post_satisfies_(
        ((_String_length_(s1) >= n) && (_String_length_(s2) >= n)) ||
        ((_String_length_(s1) < n) && (_String_length_(s2) < n) && (_String_length_(s1) == _String_length_(s2)))
    ))
PAL_INLINE int Wcsncasecmp(
    _In_z_ const wchar_t* s1, 
    _In_z_ const wchar_t* s2, 
    size_t n)
{
#if defined(_MSC_VER)
    return _wcsnicmp(s1, s2, n);
#else
    extern int wcsncasecmp(const wchar_t*, const wchar_t*, size_t n);
    return wcsncasecmp(s1, s2, n);
#endif
}

#ifdef _PREFAST_
 #pragma prefast(pop)
#endif

_When_(return == 0, _Post_satisfies_(
        ((_String_length_(s1) >= n) && (_String_length_(s2) >= n)) ||
        ((_String_length_(s1) < n) && (_String_length_(s2) < n) && (_String_length_(s1) == _String_length_(s2)))
    ))
PAL_INLINE int Tcsncasecmp(
    _In_z_ const TChar* s1, 
    _In_z_ const TChar* s2, 
    size_t n)
{
#if defined(CONFIG_ENABLE_WCHAR)
    return Wcsncasecmp(s1, s2, n);
#else
    return Strncasecmp(s1, s2, n);
#endif
}

/*
**==============================================================================
**
** Strtoul()
** Wcstoul()
** Tcstoul()
**
**==============================================================================
*/

PAL_INLINE unsigned long Strtoul(
    _In_z_ const char* str, 
    _Out_opt_ _Deref_post_z_ char** end, 
    int base)
{
    return strtoul(str, end, base);
}

PAL_INLINE unsigned long Wcstoul(
    _In_z_ const wchar_t* str, 
    _Out_opt_ _Deref_post_z_ wchar_t** end, 
    int base)
{
    return wcstoul(str, end, base);
}

PAL_INLINE unsigned long Tcstoul(
    _In_z_ const TChar* str, 
    _Out_opt_ _Deref_post_z_ TChar** end, 
    int base)
{
#if defined(CONFIG_ENABLE_WCHAR)
    return Wcstoul(str, end, base);
#else
    return Strtoul(str, end, base);
#endif
}

/*
**==============================================================================
**
** Strtol()
** Wcstol()
** Tcstol()
**
**==============================================================================
*/

PAL_INLINE long Strtol(
    _In_z_ const char* str, 
    _Out_opt_ _Deref_post_z_ char** end, 
    int base)
{
    return strtol(str, end, base);
}

PAL_INLINE long Wcstol(
    _In_z_ const wchar_t* str, 
    _Out_opt_ _Deref_post_z_ wchar_t** end, 
    int base)
{
    return wcstol(str, end, base);
}

PAL_INLINE long Tcstol(
    _In_z_ const TChar* str, 
    _Out_opt_ _Deref_post_z_ TChar** end, 
    int base)
{
#if defined(CONFIG_ENABLE_WCHAR)
    return Wcstol(str, end, base);
#else
    return Strtol(str, end, base);
#endif
}

/*
**==============================================================================
**
** Strtoull()
** Wcstoull()
** Tcstoull()
**
**==============================================================================
*/

PAL_INLINE PAL_Uint64 Strtoull(
    _In_z_ const char* str, 
    _Out_opt_ _Deref_post_z_ char** end, 
    int base)
{
#if defined(_MSC_VER)
    return _strtoui64(str, end, base);
#else
    return strtoull(str, end, base);
#endif
}

#if defined(CONFIG_ENABLE_WCHAR)
PAL_INLINE PAL_Uint64 Wcstoull(
    _In_z_ const wchar_t* str, 
    _Out_opt_ _Deref_post_z_ wchar_t** end, 
    int base)
{
#if defined(_MSC_VER)
    return _wcstoui64(str, end, base);
#else
    extern unsigned long long wcstoull(const wchar_t* s, wchar_t** e, int b);
    return wcstoull(str, end, base);
#endif
}
#endif

PAL_INLINE PAL_Uint64 Tcstoull(
    _In_z_ const TChar* str, 
    _Out_opt_ _Deref_post_z_ TChar** end, 
    int base)
{
#if defined(CONFIG_ENABLE_WCHAR)
    return Wcstoull(str, end, base);
#else
    return Strtoull(str, end, base);
#endif
}

/*
**==============================================================================
**
** Strtoll()
** Wcstoll()
** Tcstoll()
**
**==============================================================================
*/

PAL_INLINE PAL_Sint64 Strtoll(
    _In_z_ const char* str, 
    _Out_opt_ _Deref_post_z_ char** end, 
    int base)
{
#if defined(_MSC_VER)
    return _strtoi64(str, end, base);
#else
    return strtoll(str, end, base);
#endif
}

PAL_INLINE PAL_Sint64 Wcstoll(
    _In_z_ const wchar_t* str, 
    _Out_opt_ _Deref_post_z_ wchar_t** end, 
    int base)
{
#if defined(_MSC_VER)
    return _wcstoi64(str, end, base);
#else
    extern long long wcstoll(const wchar_t* s, wchar_t** e, int b);
    return wcstoll(str, end, base);
#endif
}

PAL_INLINE PAL_Sint64 Tcstoll(
    _In_z_ const TChar* str, 
    _Out_opt_ _Deref_post_z_ TChar** end, 
    int base)
{
#if defined(CONFIG_ENABLE_WCHAR)
    return Wcstoll(str, end, base);
#else
    return Strtoll(str, end, base);
#endif
}

/*
**==============================================================================
**
** Strtod()
** Wcstod()
** Tcstod()
**
**==============================================================================
*/

PAL_INLINE double Strtod(
    _In_z_ const char* str, 
    _Out_opt_ _Deref_post_z_ char** end)
{
    return strtod(str, end);
}

PAL_INLINE double Wcstod(
    _In_z_ const wchar_t* str, 
    _Out_opt_ _Deref_post_z_ wchar_t** end)
{
    return wcstod(str, end);
}

PAL_INLINE double Tcstod(
    _In_z_ const TChar* str, 
    _Out_opt_ _Deref_post_z_ TChar** end)
{
#if defined(CONFIG_ENABLE_WCHAR)
    return Wcstod(str, end);
#else
    return Strtod(str, end);
#endif
}

/*
**==============================================================================
**
** Strchr()
** Wcschr()
** Tcschr()
**
**==============================================================================
*/

PAL_INLINE char* Strchr(
    _In_z_ const char* str, 
    char ch)
{
    return (char*)strchr(str, ch);
}

PAL_INLINE wchar_t* Wcschr(
    _In_z_ const wchar_t* str, 
    wchar_t ch)
{
    return (wchar_t*)wcschr(str, ch);
}

PAL_INLINE TChar* Tcschr(
    _In_z_ const TChar* str, 
    TChar ch)
{
#if defined(CONFIG_ENABLE_WCHAR)
    return (wchar_t*)Wcschr(str, ch);
#else
    return (char*)Strchr(str, ch);
#endif
}

/*
**==============================================================================
**
** Strstr()
** Wcsstr()
** Tcsstr()
**
**==============================================================================
*/

PAL_INLINE char* Strstr(
    _In_z_ const char* haystack, 
    _In_z_ const char* needle)
{
    return (char*)strstr(haystack, needle);
}

PAL_INLINE wchar_t* Wcsstr(
    _In_z_ const wchar_t* haystack, 
    _In_z_ const wchar_t* needle)
{
    return (wchar_t*)wcsstr(haystack, needle);
}

PAL_INLINE TChar* Tcsstr(
    _In_z_ const TChar* haystack, 
    _In_z_ const TChar* needle)
{
#if defined(CONFIG_ENABLE_WCHAR)
    return (wchar_t*)Wcsstr(haystack, needle);
#else
    return (char*)Strstr(haystack, needle);
#endif
}

/*
**==============================================================================
**
** Strrchr()
** Wcsrchr()
** Tcsrchr()
**
**==============================================================================
*/

PAL_INLINE char* Strrchr(
    _In_z_ const char* str, 
    char ch)
{
    return (char*)strrchr(str, ch);
}

PAL_INLINE wchar_t* Wcsrchr(
    _In_z_ const wchar_t* str, 
    wchar_t ch)
{
    return (wchar_t*)wcsrchr(str, ch);
}

PAL_INLINE TChar* Tcsrchr(
    _In_z_ const TChar* str, 
    TChar ch)
{
#if defined(CONFIG_ENABLE_WCHAR)
    return Wcsrchr(str, ch);
#else
    return Strrchr(str, ch);
#endif
}

/*
**==============================================================================
**
** Strcat()
** Wcscat()
** Tcscat()
**
**==============================================================================
*/

PAL_INLINE char* Strcat(
    _Inout_updates_z_(count) char* dest, 
    size_t count, 
    _In_z_ const char* src)
{
#if defined(_MSC_VER)
    strcat_s(dest, count, src);
    return dest;
#else
    return strcat(dest, src);
#endif
}

PAL_INLINE wchar_t* Wcscat(
    _Inout_updates_z_(count) wchar_t* dest, 
    size_t count, 
    _In_z_ const wchar_t* src)
{
#if defined(_MSC_VER)
    wcscat_s(dest, count, src);
    return dest;
#else
    return wcscat(dest, src);
#endif
}

PAL_INLINE TChar* Tcscat(
    _Inout_updates_z_(count) TChar* dest, 
    size_t count, 
    _In_z_ const TChar* src)
{
#if defined(CONFIG_ENABLE_WCHAR)
    return Wcscat(dest, count, src);
#else
    return Strcat(dest, count, src);
#endif
}

/*
**==============================================================================
**
** Strtok()
** Wcstok()
** Tcstok()
**
**==============================================================================
*/

PAL_INLINE char* Strtok(
    _Inout_opt_z_ char* str, 
    _In_z_ const char* delim, 
    _Inout_ _Deref_prepost_opt_z_ char** ctx)
{
#if defined(_MSC_VER)
    return strtok_s(str, delim, ctx);
#else
    return strtok_r(str, delim, ctx);
#endif
}

PAL_INLINE wchar_t* Wcstok(
    _Inout_opt_z_ wchar_t* str, 
    _In_z_ const wchar_t* delim, 
    _Inout_ _Deref_prepost_opt_z_ wchar_t** ctx)
{
#if defined(_MSC_VER)
    return wcstok_s(str, delim, ctx);
#else
    return wcstok(str, delim, ctx);
#endif
}

PAL_INLINE TChar* Tcstok(
    _Inout_opt_z_ TChar* str, 
    _In_z_ const TChar* delim, 
    _Inout_ _Deref_prepost_opt_z_ TChar** ctx)
{
#if defined(CONFIG_ENABLE_WCHAR)
    return Wcstok(str, delim, ctx);
#else
    return Strtok(str, delim, ctx);
#endif
}

/*
**==============================================================================
**
** Strlcat()
** Wcslcat()
** Tcslcat()
**
**==============================================================================
*/

size_t Strlcat(
    _Inout_updates_z_(size) char* dest, 
    _In_z_ const char* src, 
    size_t size);

size_t Wcslcat(
    _Inout_updates_z_(size) wchar_t* dest, 
    _In_z_ const wchar_t* src, 
    size_t size);

PAL_INLINE size_t Tcslcat(
    _Inout_updates_z_(size) TChar* dest, 
    _In_z_ const TChar* src, 
    size_t size)
{
#if defined(CONFIG_ENABLE_WCHAR)
    return Wcslcat(dest, src, size);
#else
    return Strlcat(dest, src, size);
#endif
}

/* Converts single-characters to TChar while concatenating.
 */
size_t TcsStrlcat(
    _Inout_updates_z_(size) TChar* dest, 
    _In_z_ const char* src, 
    size_t size);

size_t StrTcslcat(
    _Inout_updates_z_(size) char* dest, 
    _In_z_ const TChar* src, 
    size_t size);

/*
**==============================================================================
**
** Strlcpy()
** Wcslcpy()
** Tcslcpy()
**
**==============================================================================
*/

size_t Strlcpy(
    _Out_writes_z_(size) char* dest, 
    _In_z_ const char* src, 
    size_t size);

size_t Wcslcpy(
    _Out_writes_z_(size) wchar_t* dest, 
    _In_z_ const wchar_t* src, 
    size_t size);

PAL_INLINE size_t Tcslcpy(
    _Out_writes_z_(size) TChar* dest, 
    _In_z_ const TChar* src, 
    size_t size)
{
#if defined(CONFIG_ENABLE_WCHAR)
    return Wcslcpy(dest, src, size);
#else
    return Strlcpy(dest, src, size);
#endif
}

/* Warning: this function truncates wide-characters to single-characters.
 * please use with care.
 */
size_t StrWcslcpy(
    _Out_writes_z_(size) char* dest, 
    _In_z_ const wchar_t* src, 
    size_t size);

/* Converts single-characters to TChar while copying.
 */
size_t TcsStrlcpy(
    _Out_writes_z_(size) TChar* dest, 
    _In_z_ const char* src, 
    size_t size);

size_t StrTcslcpy(
    _Out_writes_z_(size) char* dest, 
    _In_z_ const TChar* src, 
    size_t size);

/* Converts characters to wide characters while copying.  This only works
 * reliably with 7-bit ASCII source strings, except on machines where char is
 * unsigned (PowerPC and Sparc). In those cases, it also works with ISO-8859-1
 * source strings and fairly well with ISO-8859-15 and Windows Code Page 1252
 * source strings.
*/

size_t WcsStrlcpy(
    _Out_writes_z_(size) wchar_t* dest, 
    _In_z_ const char* src,
    size_t size);

/*
**==============================================================================
**
** TcsFromUInt64()
** Converts PAL_Uint64 to PAL_Char
**==============================================================================
*/

_Post_satisfies_(*size == _String_length_(*result))
void TcsFromUInt64(_Pre_writable_size_(64) PAL_Char buf[64], PAL_Uint64 value, _Outptr_result_z_ const PAL_Char **result, _Out_opt_ size_t* size);

/*
**==============================================================================
**
** Missing stuff from base/strings.h
**==============================================================================
*/

_Post_satisfies_(*size == _String_length_(*result))
void Sint64ToZStr(_Pre_writable_size_(64) TChar buf[64], PAL_Sint64 value, _Outptr_result_z_ const TChar **result, _Out_opt_ size_t* size);

_Post_satisfies_(*size == _String_length_(*result))
void Uint64ToStr(_Pre_writable_size_(21) char buf[21], PAL_Uint64 value, _Outptr_result_z_ const char **result,  _Out_opt_ size_t* size);



_Success_(return != NULL) _Ret_notnull_ _Ret_z_
_Post_readable_size_(*size)
_Null_terminated_ const char* Uint32ToStr(_Pre_writable_size_(11) char buf[11], PAL_Uint32 x, size_t* size);

#if !defined(CONFIG_ENABLE_WCHAR)
_Success_(return != NULL) _Ret_notnull_ _Ret_z_
_Post_readable_size_(*size)
PAL_INLINE const TChar* Uint32ToZStr(_Pre_writable_size_(11) TChar buf[11], PAL_Uint32 x, size_t* size)
{
    return Uint32ToStr(buf, x, size);
}

_Post_satisfies_(*size == _String_length_(*result))
PAL_INLINE void Uint64ToZStr(_Pre_writable_size_(21) TChar buf[21], PAL_Uint64 value, _Outptr_result_z_ const TChar **result,  _Out_opt_ size_t* size)
{
    Uint64ToStr(buf, value, result, size);
}

#else
_Success_(return != NULL) _Ret_notnull_ _Ret_z_
_Post_readable_size_(*size)
const TChar* Uint32ToZStr(_Pre_writable_size_(11) TChar buf[11], PAL_Uint32 x, size_t* size);

_Post_satisfies_(*size == _String_length_(*result))
void Uint64ToZStr(_Pre_writable_size_(21) TChar buf[21], PAL_Uint64 value, _Outptr_result_z_ const TChar **result,  _Out_opt_ size_t* size);
#endif

#if defined(CONFIG_ENABLE_WCHAR)

typedef wchar_t Utf32Char;
typedef char Utf8Char;

int ConvertWideCharToMultiByte(
            const Utf32Char* utf32,
            size_t utf32Size,
            size_t* firstNonAscii,
            Utf8Char* utf8,
            int utf8Size);
#endif

PAL_END_EXTERNC

#endif /* _pal_strings_h */
