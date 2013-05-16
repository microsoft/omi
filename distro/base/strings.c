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

#include "strings.h"

_Use_decl_annotations_
size_t Strlcat(char* dest, const char* src, size_t size)
{
    const char* start = src;

    if (size)
    {
        char* end = dest + size - 1;

        while (*dest && dest != end)
            dest++;

        while (*src && dest != end)
            *dest++ = *src++;

        *dest = '\0';
    }

    while (*src)
        src++;

    return src - start;
}

_Use_decl_annotations_
size_t Strlcpy(char* dest, const char* src, size_t size)
{
    const char* start = src;

    if (size)
    {
        char* end = dest + size - 1;

        while (*src && dest != end)
            *dest++ = *src++;

        *dest = '\0';
    }

    while (*src)
        src++;

    return src - start;
}

_Use_decl_annotations_
size_t Zlcat(ZChar* dest, const ZChar* src, size_t size)
{
    const ZChar* start = src;

    if (size)
    {
        ZChar* end = dest + size - 1;

        while (*dest && dest != end)
            dest++;

        while (*src && dest != end)
            *dest++ = *src++;

        *dest = '\0';
    }

    while (*src)
        src++;

    return src - start;
}

_Use_decl_annotations_
size_t Zlcpy(ZChar* dest, const ZChar* src, size_t size)
{
    const ZChar* start = src;

    if (size)
    {
        ZChar* end = dest + size - 1;

        while (*src && dest != end)
            *dest++ = *src++;

        *dest = '\0';
    }

    while (*src)
        src++;

    return src - start;
}

_Use_decl_annotations_
size_t ZStrlcat(ZChar* dest, const char* src, size_t size)
{
    const char* start = src;

    if (size)
    {
        ZChar* end = dest + size - 1;

        while (*dest && dest != end)
            dest++;

        while (*src && dest != end)
            *dest++ = *src++;

        *dest = '\0';
    }

    while (*src)
        src++;

    return src - start;
}

_Use_decl_annotations_
size_t ZStrlcpy(ZChar* dest, const char* src, size_t size)
{
    const char* start = src;

    if (size)
    {
        ZChar* end = dest + size - 1;

        while (*src && dest != end)
            *dest++ = *src++;

        *dest = '\0';
    }

    while (*src)
        src++;

    return src - start;
}

_Use_decl_annotations_
size_t StrZlcpy(char* dest, const ZChar* src, size_t size)
{
    const ZChar* start = src;

    if (size)
    {
        char* end = dest + size - 1;

        while (*src && dest != end)
            *dest++ = (char)*src++;

        *dest = '\0';
    }

    while (*src)
        src++;

    return src - start;
}

#if !defined(CONFIG_FAVORSIZE)

#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4125 )
#endif

// The following defines string literals for the numbers 0 through 63. The
// first character is the length of the string. The subsequent characters
// are the string literal iteslf.
static const char* _numberStrings[] =
{
    "\0010",
    "\0011",
    "\0012",
    "\0013",
    "\0014",
    "\0015",
    "\0016",
    "\0017",
    "\0018",
    "\0019",
    "\00210",
    "\00211",
    "\00212",
    "\00213",
    "\00214",
    "\00215",
    "\00216",
    "\00217",
    "\00218",
    "\00219",
    "\00220",
    "\00221",
    "\00222",
    "\00223",
    "\00224",
    "\00225",
    "\00226",
    "\00227",
    "\00228",
    "\00229",
    "\00230",
    "\00231",
    "\00232",
    "\00233",
    "\00234",
    "\00235",
    "\00236",
    "\00237",
    "\00238",
    "\00239",
    "\00240",
    "\00241",
    "\00242",
    "\00243",
    "\00244",
    "\00245",
    "\00246",
    "\00247",
    "\00248",
    "\00249",
    "\00250",
    "\00251",
    "\00252",
    "\00253",
    "\00254",
    "\00255",
    "\00256",
    "\00257",
    "\00258",
    "\00259",
    "\00260",
    "\00261",
    "\00262",
    "\00263",
};
#if defined(_MSC_VER)
#pragma warning( pop )
#endif

#endif /* !defined(CONFIG_FAVORSIZE) */

_Use_decl_annotations_
const char* Uint32ToStr(char buf[11], MI_Uint32 x, size_t* size)
{
    char* p;

#if !defined(CONFIG_FAVORSIZE)

    if (x < 64)
    {
        *size = _numberStrings[x][0];
        return &_numberStrings[x][1];
    }

#endif /* !defined(CONFIG_FAVORSIZE)*/

    p = &buf[10];
    *p = '\0';

    do
    {
        *--p = '0' + x % 10;
    }
    while (x /= 10);

    *size = &buf[10] - p;
    return p;
}

_Use_decl_annotations_
const char* Uint64ToStr(char buf[21], MI_Uint64 x, size_t* size)
{
    char* p;

#if !defined(CONFIG_FAVORSIZE)

    if (x < 64)
    {
        *size = _numberStrings[x][0];
        return &_numberStrings[x][1];
    }

#endif /* !defined(CONFIG_FAVORSIZE)*/

    p = &buf[20];
    *p = '\0';

    do
    {
        *--p = '0' + x % 10;
    }
    while (x /= 10);

    *size = &buf[20] - p;
    return p;
}

#if (MI_CHAR_TYPE != 1)
_Use_decl_annotations_
const ZChar* Uint32ToZStr(ZChar buf[11], MI_Uint32 x, size_t* size)
{
    ZChar* p = &buf[10];
    *p = '\0';

    do
    {
        *--p = '0' + x % 10;
    }
    while (x /= 10);

    *size = &buf[10] - p;
    return p;
}
#endif

#if (MI_CHAR_TYPE != 1)
_Use_decl_annotations_
const ZChar* Uint64ToZStr(ZChar buf[21], MI_Uint64 x, size_t* size)
{
    ZChar* p = &buf[20];
    *p = '\0';

    do
    {
        *--p = '0' + x % 10;
    }
    while (x /= 10);

    *size = &buf[20] - p;
    return p;
}
#endif

_Use_decl_annotations_
char* ZStrdup(const ZChar* str)
{
#if (MI_CHAR_TYPE != 1)
    char* p;
    char* result;
    size_t n = Wcslen(str);

    result = (char*)malloc(n + 1);

    if (!result)
        return NULL;

    p = result;

    while (*str)
    {
        if ((MI_Uint32)*str >= 128)
        {
            free(p);
            return NULL;
        }
        *p++ = (char)*str++;
    }

    *p = '\0';
    return result;
#else
    return Strdup(str);
#endif
}

_Use_decl_annotations_
size_t Wcslen(const wchar_t* str)
{
    const wchar_t* p = str;

    while (p[0] && p[1] && p[2] && p[3] && p[4] && p[5])
    {
        p += 6;
    }

    while (*p)
        p++;

    return p - str;
}
