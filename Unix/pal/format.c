/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "format.h"
#include <pal/strings.h>

#include <string.h>
#include <pal/once.h>
#include <pal/intsafe.h>
#include <locale.h>

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
        start = (char*)SystemMalloc(n * sizeof(char));

        if (!start)
            return NULL;
    }
    else
        start = buf;

    for (p = start; *fmt; )
    {
        if (fmt[0] == '%' && fmt[1] == 'T')
        {
            *p++ = '%';
            *p++ = 's';
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

_Use_decl_annotations_
int Snprintf_CultureInvariant(
    char* buffer,
    size_t size,
    const char* format,
    ...)
{
    va_list ap;
    int r;

    va_start(ap, format);
    r = Vsnprintf_CultureInvariant(buffer, size, format, ap);
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

    fmt = FixupFormat(buf, PAL_COUNT(buf), format);

    if (!fmt)
        return -1;

    r = vfprintf(os, fmt, ap);

    if (fmt != buf)
        SystemFree(fmt);

    return r;
}

#if defined(CONFIG_VSNPRINTF_RETURN_MINUSONE_WITH_NULLBUFFER)
static int _GetFormattedSize(
    const char* fmt,
    va_list ap)
{
    char buf[128];
    char* p = buf;
    size_t n = sizeof buf;
    int r;

    while ((r = vsnprintf(p, n, fmt, ap)) == -1)
    {
        if (SizeTMult(n, 2, &n) != S_OK)
            return -1;

        if (p == buf)
            p = (char*)SystemMalloc(n);
        else
        {
            char* q = (char*)SystemRealloc(p, n);

            if (q != NULL)
                p = q;
        }
        if (p == NULL)
            return -1;

        if (p != buf)
            SystemFree(p);
    }
    return r;
}
#endif /* defined(CONFIG_VSNPRINTF_RETURN_MINUSONE_WITH_NULLBUFFER) */

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

    fmt = FixupFormat(buf, PAL_COUNT(buf), format);

    if (!fmt)
    {
        buffer[0] = '\0';
        return -1;
    }

# ifdef __hpux                          // HP-UX 11.21 and earlier will core dump if buffer is NULL
    if (buffer == NULL || size == 0)
        r = _GetFormattedSize(fmt, ap);
    else
# endif
    r = vsnprintf(buffer, size, fmt, ap);
#if defined(CONFIG_VSNPRINTF_RETURN_MINUSONE_WITH_NULLBUFFER) // SUN-SPARC and HP-UX without the UNIX 2003 standard option returns -1
    if (r == -1)                        // instead of the needed byte count if size was too small
        r = _GetFormattedSize(fmt, ap);
# endif

    if (fmt != buf)
        SystemFree(fmt);

    return r;
}

_Use_decl_annotations_
int Vsnprintf_CultureInvariant(
    char* buffer,
    size_t size,
    const char* format,
    va_list ap)
{
    /* Ideally we would avoid calling setlocale and use _vsprintf_s_l
       instead.  The problem is that _create_locale is not exported on Win7 */

    int r;
    char oldLocale[128];
    Strlcpy(oldLocale, setlocale(LC_ALL, NULL), PAL_COUNT(oldLocale));
    setlocale(LC_ALL, "C");
    r = Vsnprintf(buffer, size, format, ap);
    setlocale(LC_ALL, oldLocale);
    return r;
}

_Use_decl_annotations_
int Sscanf_CultureInvariant(
    const char* buffer,
    const char* format,
    ...)
{
    va_list ap;
    int r;

    va_start(ap, format);
    r = Vsscanf_CultureInvariant(buffer, format, ap);
    va_end(ap);

    return r;
}

_Use_decl_annotations_
int Vsscanf_CultureInvariant(
    const char* buffer,
    const char* format,
    va_list ap)
{
    int r;
    char* fmt;
    char buf[128];

    memset(&buf, 0, sizeof(buf));

    fmt = FixupFormat(buf, PAL_COUNT(buf), format);

    if (!fmt)
    {
        return EOF;
    }

    {
        /* Ideally we would avoid calling setlocale and use _sscanf_l
           instead.  The problem is that _create_locale is not exported on Win7 */
        char oldLocale[128];
        Strlcpy(oldLocale, setlocale(LC_ALL, NULL), PAL_COUNT(oldLocale));
        setlocale(LC_ALL, "C");
        r = vsscanf(buffer, fmt, ap);
        setlocale(LC_ALL, oldLocale);
    }

    if (fmt != buf)
        SystemFree(fmt);

    return r;
}

PAL_Char* Vstprintf_StrDup(_In_z_ const PAL_Char* templateString, va_list ap)
{
    PAL_Char* resultString = NULL;
    int resultCharCount;
    int err;
    va_list tmpAp;

    PAL_va_copy(tmpAp, ap);
    resultCharCount = Vstprintf(NULL, 0, templateString, tmpAp);
    va_end(tmpAp);
    if (resultCharCount < 0)
    {
        goto CleanUp;
    }
    else
    {
        resultString  = (PAL_Char*)PAL_Malloc(sizeof(PAL_Char) * (resultCharCount + 1));

        if (!resultString)
        {
            goto CleanUp;
        }

        err = Vstprintf(resultString, resultCharCount + 1, templateString, ap);
        if ((0 <= err) && (err <= resultCharCount))
        {
            resultString[resultCharCount] = PAL_T('\0');
        }
        else
        {
            PAL_Free(resultString);
            resultString = NULL;
            goto CleanUp;
        }
    }

CleanUp:
    return resultString;
}

PAL_Char* Stprintf_StrDup(_In_z_ const PAL_Char* templateString, ...)
{
    PAL_Char* resultString = NULL;
    va_list ap;

    va_start(ap, templateString);
    resultString = Vstprintf_StrDup(templateString, ap);
    va_end(ap);
    return resultString;
}

