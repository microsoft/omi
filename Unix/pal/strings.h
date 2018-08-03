/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/*
**==============================================================================
**
** strings.h:
**
**     This file defines string-manipluation functions. For each string 
**     operation, there are three implementations:
**
**         - Single-character - char
**         - T-character - TChar (char depending on configuration)
**
**     Each string function has one of the following prefixes:
**
**         - Str - single character string
**         - Tcs - T-character string
**
**     For example, the are three variants for simple copying of strings:
**
**         - Strcpy() - same as strcpy()
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
**
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
#include <ctype.h>
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
** Tcscmp()
**
**==============================================================================
*/

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
    return Strcmp(s1, s2);
}

/*
**==============================================================================
**
** Strncmp()
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
    return Strncmp(s1, s2, n);
}

/*
**==============================================================================
**
** Strlen()
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

#ifdef _PREFAST_
 #pragma prefast(pop)
#endif

_Post_satisfies_(return == _String_length_(str))
PAL_INLINE size_t Tcslen(
    _In_z_ const TChar* str)
{
    return Strlen(str);
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
    return strcasecmp(s1, s2);
}

PAL_INLINE int Wcscasecmp(
    _In_z_ const wchar_t* s1, 
    _In_z_ const wchar_t* s2)
{
    extern int wcscasecmp(const wchar_t*, const wchar_t*);
    return wcscasecmp(s1, s2);
}

PAL_INLINE int Tcscasecmp(
    _In_z_ const TChar* s1, 
    _In_z_ const TChar* s2)
{
    return Strcasecmp(s1, s2);
}

/*
**==============================================================================
**
** Strncasecmp()
** Wcsncasecmp() // MOF parser uses this function
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
    return strncasecmp(s1, s2, n);
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
    extern int wcsncasecmp(const wchar_t*, const wchar_t*, size_t n);
    return wcsncasecmp(s1, s2, n);
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
    return Strncasecmp(s1, s2, n);
}

/*
**==============================================================================
**
** Strtoul()
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

PAL_INLINE unsigned long Tcstoul(
    _In_z_ const TChar* str, 
    _Out_opt_ _Deref_post_z_ TChar** end, 
    int base)
{
    return Strtoul(str, end, base);
}

/*
**==============================================================================
**
** Strtol()
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

PAL_INLINE long Tcstol(
    _In_z_ const TChar* str, 
    _Out_opt_ _Deref_post_z_ TChar** end, 
    int base)
{
    return Strtol(str, end, base);
}

/*
**==============================================================================
**
** Strtoull()
** Tcstoull()
**
**==============================================================================
*/

PAL_INLINE PAL_Uint64 Strtoull(
    _In_z_ const char* str, 
    _Out_opt_ _Deref_post_z_ char** end, 
    int base)
{
    return strtoull(str, end, base);
}

PAL_INLINE PAL_Uint64 Tcstoull(
    _In_z_ const TChar* str, 
    _Out_opt_ _Deref_post_z_ TChar** end, 
    int base)
{
    return Strtoull(str, end, base);
}

/*
**==============================================================================
**
** Strtoll()
** Wcstoll() // MOF Parser uses this function
** Tcstoll()
**
**==============================================================================
*/

PAL_INLINE PAL_Sint64 Strtoll(
    _In_z_ const char* str, 
    _Out_opt_ _Deref_post_z_ char** end, 
    int base)
{
    return strtoll(str, end, base);
}

PAL_INLINE PAL_Sint64 Wcstoll(
    _In_z_ const wchar_t* str, 
    _Out_opt_ _Deref_post_z_ wchar_t** end, 
    int base)
{
    extern long long wcstoll(const wchar_t* s, wchar_t** e, int b);
    return wcstoll(str, end, base);
}

PAL_INLINE PAL_Sint64 Tcstoll(
    _In_z_ const TChar* str, 
    _Out_opt_ _Deref_post_z_ TChar** end, 
    int base)
{
    return Strtoll(str, end, base);
}

/*
**==============================================================================
**
** Strtod()
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

PAL_INLINE double Tcstod(
    _In_z_ const TChar* str, 
    _Out_opt_ _Deref_post_z_ TChar** end)
{
    return Strtod(str, end);
}

/*
**==============================================================================
**
** Strchr()
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

PAL_INLINE TChar* Tcschr(
    _In_z_ const TChar* str, 
    TChar ch)
{
    return (char*)Strchr(str, ch);
}

/*
**==============================================================================
**
** Strstr()
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

PAL_INLINE TChar* Tcsstr(
    _In_z_ const TChar* haystack, 
    _In_z_ const TChar* needle)
{
    return (char*)Strstr(haystack, needle);
}

/*
**==============================================================================
**
** Strcasestr()
** Tcscasestr()
**
**==============================================================================
*/


#if defined(hpux) || defined(sun) || defined(aix)

// A version of strcasestr as hpux, solaris or aix don't have it.
//

PAL_INLINE char *Strcasestr(const char *haystack, const char *needle)
{

    if (!haystack)
        return NULL;

    if (*needle == '\0') {
        return (char *)haystack;
    }

    do {
        const char *hp = haystack;
        const char *np = needle;

        while (tolower((unsigned char)*hp) == tolower((unsigned char)*np) && *np) hp++, np++;
        if (*np == '\0') {
            return (char *)haystack;
        }

    } while (*haystack++);

    return NULL;
}

#else

PAL_INLINE char* Strcasestr(
    _In_z_ const char* haystack, 
    _In_z_ const char* needle)
{
    return (char*)strcasestr(haystack, needle);
}

#endif


/*
**==============================================================================
**
** Strrchr()
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

PAL_INLINE TChar* Tcsrchr(
    _In_z_ const TChar* str, 
    TChar ch)
{
    return Strrchr(str, ch);
}

/*
**==============================================================================
**
** Strcat()
** Tcscat()
**
**==============================================================================
*/

PAL_INLINE char* Strcat(
    _Inout_updates_z_(count) char* dest, 
    size_t count, 
    _In_z_ const char* src)
{
    return strcat(dest, src);
}

PAL_INLINE TChar* Tcscat(
    _Inout_updates_z_(count) TChar* dest, 
    size_t count, 
    _In_z_ const TChar* src)
{
    return Strcat(dest, count, src);
}

/*
**==============================================================================
**
** Strtok()
** Tcstok()
**
**==============================================================================
*/

PAL_INLINE char* Strtok(
    _Inout_opt_z_ char* str, 
    _In_z_ const char* delim, 
    _Inout_ _Deref_prepost_opt_z_ char** ctx)
{
    return strtok_r(str, delim, ctx);
}

PAL_INLINE TChar* Tcstok(
    _Inout_opt_z_ TChar* str, 
    _In_z_ const TChar* delim, 
    _Inout_ _Deref_prepost_opt_z_ TChar** ctx)
{
    return Strtok(str, delim, ctx);
}

/*
**==============================================================================
**
** Strlcat()
** Tcslcat()
**
** Note: the size parameter in these lcat functions represent the size of dest buffer
**==============================================================================
*/

size_t Strlcat(
    _Inout_updates_z_(size) char* dest, 
    _In_z_ const char* src, 
    size_t size);

PAL_INLINE size_t Tcslcat(
    _Inout_updates_z_(size) TChar* dest, 
    _In_z_ const TChar* src, 
    size_t size)
{
    return Strlcat(dest, src, size);
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
** Tcslcpy()
**
** Note: the size parameter in these lcpy functions represent the size of dest buffer
**==============================================================================
*/

size_t Strlcpy(
    _Out_writes_z_(size) char* dest, 
    _In_z_ const char* src, 
    size_t size);

PAL_INLINE size_t Tcslcpy(
    _Out_writes_z_(size) TChar* dest, 
    _In_z_ const TChar* src, 
    size_t size)
{
    return Strlcpy(dest, src, size);
}

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

PAL_INLINE char *
int64_to_a(char *buf, int buflen, long long value, int *psize )

{
    char* p;

    p = buf+buflen;
    p--;
    *p = '\0';

    do
    {
        /* if the buffer is smaller than needed, we will return NULL */
        if (p < buf) return NULL;
        *--p = '0' + value % 10;
    }
    while (value /= 10);

    if (psize)
    {
       *psize = (buflen-(p - buf))-1;
    }

    return p;
}

PAL_END_EXTERNC

#endif /* _pal_strings_h */
