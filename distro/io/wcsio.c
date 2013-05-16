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

#include "io.h"

wchar_t* WFixupFormat(
    _Out_writes_z_(size) _Null_terminated_ wchar_t* buf,
    _In_ size_t size,
    _In_z_ const wchar_t* fmt)
{
    size_t n = wcslen(fmt) + 1;
    wchar_t* start;
    wchar_t* p;

    if (n > size)
    {
        start = (wchar_t*)malloc(n * sizeof(wchar_t));

        if (!start)
            return NULL;
    }
    else
        start = buf;

    for (p = start; *fmt; )
    {
        if (fmt[0] == '%' && fmt[1] == 'Z')
        {
            *p++ = '%';
#if defined(CONFIG_ENABLE_WCHAR)
# if defined(_MSC_VER)
            *p++ = 's';
# else
            *p++ = 'S';
# endif
#else
# if defined(_MSC_VER)
            *p++ = 'S';
# else
            *p++ = 's';
# endif
#endif
            fmt += 2;
        }
#if defined(_MSC_VER)
        else if (fmt[0] == '%' && fmt[1] == 's')
        {
            *p++ = '%';
            *p++ = 'S';
            fmt += 2;
        }
        else if (fmt[0] == '%' && fmt[1] == 'S')
        {
            *p++ = '%';
            *p++ = 's';
            fmt += 2;
        }
#endif
        else
            *p++ = *fmt++;
    }

    *p = '\0';

    return start;
}

int Wprintf(
    const wchar_t* format,
    ...)
{
    va_list ap;
    int r;

    memset(&ap, 0, sizeof(ap));
    va_start(ap, format);
    r = Vfwprintf(stdout, format, ap);
    va_end(ap);

    return r;
}

int Fwprintf(
    FILE* os,
    const wchar_t* format,
    ...)
{
    va_list ap;
    int r;

    memset(&ap, 0, sizeof(ap));
    va_start(ap, format);
    r = Vfwprintf(os, format, ap);
    va_end(ap);

    return r;
}

_Use_decl_annotations_
int Swprintf(
    wchar_t* buffer,
    size_t size,
    const wchar_t* format,
    ...)
{
    va_list ap;
    int r;

    va_start(ap, format);
    r = Vswprintf(buffer, size, format, ap);
    va_end(ap);

    return r;
}

int Vwprintf(
    const wchar_t* format,
    va_list ap)
{
    return Vfwprintf(stdout, format, ap);
}

int Vfwprintf(
    FILE* os,
    const wchar_t* format,
    va_list ap)
{
    int r;
    wchar_t buf[128];
    wchar_t* fmt;

    memset(&buf, 0, sizeof(buf));

    fmt = WFixupFormat(buf, sizeof(buf) / sizeof(buf[0]), format);

    if (!fmt)
        return -1;

    r = vfwprintf(os, fmt, ap);

    if (fmt != buf)
        free(fmt);

    return r;
}

_Use_decl_annotations_
int Vswprintf(
    wchar_t* buffer,
    size_t size,
    const wchar_t* format,
    va_list ap)
{
    int r;
    wchar_t* fmt;
    wchar_t buf[128];

    memset(&buf, 0, sizeof(buf));

    fmt = WFixupFormat(buf, sizeof(buf) / sizeof(buf[0]), format);

    if (!fmt)
    {
        buffer[0] = '\0';
        return -1;
    }

#ifdef _MSC_VER
    r = vswprintf_s(buffer, size, fmt, ap);
#else
    r = vswprintf(buffer, size, fmt, ap);
#endif

    if (fmt != buf)
        free(fmt);

    return r;
}

