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

char* FixupFormat(
    _Out_writes_z_(size) _Null_terminated_ char* buf,
    _In_ size_t size,
    _In_z_ const char* fmt)
{
    size_t n = strlen(fmt) + 1;
    char* start;
    char* p;

    if (n > size)
    {
        start = (char*)malloc(n * sizeof(char));

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
            *p++ = 'S';
#else
            *p++ = 's';
#endif
            fmt += 2;
        }
        else
            *p++ = *fmt++;
    }

    *p = '\0';

    return start;
}

int Printf(
    const char* format,
    ...)
{
    va_list ap;
    int r;

    memset(&ap, 0, sizeof(ap));
    va_start(ap, format);
    r = Vfprintf(stdout, format, ap);
    va_end(ap);

    return r;
}

int Fprintf(
    FILE* os,
    const char* format,
    ...)
{
    va_list ap;
    int r;

    memset(&ap, 0, sizeof(ap));
    va_start(ap, format);
    r = Vfprintf(os, format, ap);
    va_end(ap);

    return r;
}

_Use_decl_annotations_
int Snprintf(
    char* buffer,
    size_t size,
    const char* format,
    ...)
{
    va_list ap;
    int r;

    va_start(ap, format);
    r = Vsnprintf(buffer, size, format, ap);
    va_end(ap);

    return r;
}

int Vprintf(
    const char* format,
    va_list ap)
{
    return Vfprintf(stdout, format, ap);
}

int Vfprintf(
    FILE* os,
    const char* format,
    va_list ap)
{
    int r;
    char buf[128];
    char* fmt;

    memset(&buf, 0, sizeof(buf));

    fmt = FixupFormat(buf, sizeof(buf) / sizeof(buf[0]), format);

    if (!fmt)
        return -1;

    r = vfprintf(os, fmt, ap);

    if (fmt != buf)
        free(fmt);

    return r;
}

_Use_decl_annotations_
int Vsnprintf(
    char* buffer,
    size_t size,
    const char* format,
    va_list ap)
{
    int r;
    char* fmt;
    char buf[128];

    memset(&buf, 0, sizeof(buf));

    fmt = FixupFormat(buf, sizeof(buf) / sizeof(buf[0]), format);

    if (!fmt)
    {
        buffer[0] = '\0';
        return -1;
    }

#ifdef _MSC_VER
    r = _vsnprintf_s(buffer, size, _TRUNCATE, fmt, ap);
#else
    r = vsnprintf(buffer, size, fmt, ap);
#endif

    if (fmt != buf)
        free(fmt);

    return r;
}
