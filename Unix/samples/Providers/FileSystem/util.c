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

