/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "util.h"

MI_INLINE size_t TStrcptostr(char* dest, const TChar* src, size_t size)
{
    const TChar* start = src;

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

char* TToStr(_Out_writes_z_(size) char* buf, size_t size, _In_z_ const TChar* src)
{
    TStrcptostr(buf, src, size);
    return buf;
}

MI_INLINE size_t StrcptoTStr(TChar* dest, const char* src, size_t size)
{
    const char* start = src;

    if (size)
    {
        TChar* end = dest + size - 1;

        while (*src && dest != end)
            *dest++ = *src++;

        *dest = '\0';
    }

    while (*src)
        src++;

    return src - start;
}

TChar* StrToT(_Out_writes_z_(size) TChar* buf, size_t size, _In_z_ const char* src)
{
    StrcptoTStr(buf, src, size);
    return buf;
}

