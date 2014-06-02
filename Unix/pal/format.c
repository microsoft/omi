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

#include "format.h"
#include <pal/strings.h>

#include <string.h>
#include <pal/once.h>

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
        n *= 2;

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

#ifdef _MSC_VER
    r = _vsnprintf_s(buffer, size, _TRUNCATE, fmt, ap);
#else
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
#endif

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
        start = (wchar_t*)SystemMalloc(n * sizeof(wchar_t));

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

_Use_decl_annotations_
int Swprintf_CultureInvariant(
    wchar_t* buffer, 
    size_t size, 
    const wchar_t* format, 
    ...)
{
    va_list ap;
    int r;

    va_start(ap, format);
    r = Vswprintf_CultureInvariant(buffer, size, format, ap);
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

    fmt = WFixupFormat(buf, PAL_COUNT(buf), format);

    if (!fmt)
        return -1;

    r = vfwprintf(os, fmt, ap);

    if (fmt != buf)
        SystemFree(fmt);

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

    fmt = WFixupFormat(buf, PAL_COUNT(buf), format);

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
        SystemFree(fmt);

    return r;
}

_Use_decl_annotations_
int Vswprintf_CultureInvariant(
    wchar_t* buffer, 
    size_t size, 
    const wchar_t* format, 
    va_list ap)
{
    /* Ideally we would avoid calling setlocale and use _vswprintf_s_l
    instead.  The problem is that _create_locale is not exported on Win7.  */

    int r;
#ifdef _MSC_VER    
    wchar_t oldLocale[128];
    Wcslcpy(oldLocale, _wsetlocale(LC_ALL, NULL), PAL_COUNT(oldLocale));
    _wsetlocale(LC_ALL, L"C");
#else
    char oldLocale[128];
    Strlcpy(oldLocale, setlocale(LC_ALL, NULL), PAL_COUNT(oldLocale));
    setlocale(LC_ALL, "C");
#endif
    r = Vswprintf(buffer, size, format, ap);
#ifdef _MSC_VER
    _wsetlocale(LC_ALL, oldLocale);
#else
    setlocale(LC_ALL, oldLocale);
#endif
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
#ifdef _MSC_VER
        {
            /* no *v*scanf on Windows and some older UNIXes... using a workaround instead */
            void *args[10] = {0}; 
            int numberOfFormatSpecifiers = 0;
            const char *c;

            for (c = format; c[0] != '\0'; c++)
            {
                if (c[0] == '%')
                {
                    if ((c[1] == '%') || (c[1] == '*'))
                    {
                        c++;
                    }
                    else
                    {
                        if (numberOfFormatSpecifiers >= 10)
                        {
                            r = EOF;
                            goto CleanUp;
                        }
                        args[numberOfFormatSpecifiers] = va_arg(ap, void*);
                        numberOfFormatSpecifiers++;
                    }
                }
            }

            r = sscanf_s(
                buffer, fmt, 
                args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9]);
        }
CleanUp:
#else
        r = vsscanf(buffer, fmt, ap);
#endif
        setlocale(LC_ALL, oldLocale);
    }

    if (fmt != buf)
        SystemFree(fmt);

    return r;
}


_Use_decl_annotations_
int Swscanf_CultureInvariant(
    const wchar_t* buffer, 
    const wchar_t* format, 
    ...)
{
    va_list ap;
    int r;

    va_start(ap, format);
    r = Vswscanf_CultureInvariant(buffer, format, ap);
    va_end(ap);

    return r;
}

_Use_decl_annotations_
int Vswscanf_CultureInvariant(
    const wchar_t* buffer, 
    const wchar_t* format, 
    va_list ap)
{
    int r;
    wchar_t* fmt;
    wchar_t buf[128];

    memset(&buf, 0, sizeof(buf));

    fmt = WFixupFormat(buf, PAL_COUNT(buf), format);

    if (!fmt)
    {
        return EOF;
    }

    {
        /* TODO/FIXME - ideally we would avoid calling setlocale and use _swscanf_l
           instead.  The problem is that _create_locale is not exported on Win7 */
#ifndef CONFIG_HAVE_VSWSCANF
# ifdef _MSC_VER
        wchar_t oldLocale[128];
        Wcslcpy(oldLocale, _wsetlocale(LC_ALL, NULL), PAL_COUNT(oldLocale));
        _wsetlocale(LC_ALL, L"C");
# else
        char oldLocale[128];
        Strlcpy(oldLocale, setlocale(LC_ALL, NULL), sizeof oldLocale);
        setlocale(LC_ALL, "C");
# endif
        {
            /* no *v*scanf on Windows... using a workaround instead */
            void *args[10] = {0}; 
            int numberOfFormatSpecifiers = 0;
            const wchar_t *c;

            for (c = format; c[0] != L'\0'; c++)
            {
                if (c[0] == L'%')
                {
                    if ((c[1] == L'%') || (c[1] == L'*'))
                    {
                        c++;
                    }
                    else
                    {
                        if (numberOfFormatSpecifiers >= 10)
                        {
                            r = EOF;
                            goto CleanUp;
                        }
                        args[numberOfFormatSpecifiers] = va_arg(ap, void*);
                        numberOfFormatSpecifiers++;
                    }
                }
            }
# ifdef _MSC_VER
            r = swscanf_s(
                buffer, fmt, 
                args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9]);
# else
            r = swscanf(
                buffer, fmt, 
                args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9]);
# endif
        }
        
CleanUp:
# ifdef _MSC_VER
        _wsetlocale(LC_ALL, oldLocale);        
# else
        setlocale(LC_ALL, oldLocale);        
# endif
#else
        char oldLocale[128];
        Strlcpy(oldLocale, setlocale(LC_ALL, NULL), PAL_COUNT(oldLocale));
        setlocale(LC_ALL, "C");
        r = vswscanf(buffer, fmt, ap);
        setlocale(LC_ALL, oldLocale);                
#endif
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

#if defined(CONFIG_ENABLE_WCHAR)
    /* on Linux, if stackBuffer is too small, then 
       1. snprintf returns the number of required characters
       2. swnprintf returns -1 (arrgh!)
       for #2 we need to loop to find the required size...
     */
    resultCharCount = 16;
    do 
    {
        PAL_Char* tmp = (PAL_Char*)PAL_Realloc(
            resultString, sizeof(PAL_Char) * resultCharCount);

        if (!tmp)
        {
            PAL_Free(resultString);
            resultString = NULL;
            goto CleanUp;
        }
        resultString = tmp;

        PAL_va_copy(tmpAp, ap);
        err = Vstprintf(resultString, resultCharCount, templateString, tmpAp);
        va_end(tmpAp);
        if (err < 0)
        {
            if (resultCharCount < ( ((size_t)-1) / (2*sizeof(PAL_Char)) ))
            {
                resultCharCount *= 2;
                continue;
            }
            else
            {
                PAL_Free(resultString);
                resultString = NULL;
                goto CleanUp;
            }
        }
    }
    while (err < 0);
#else /* !defined(CONFIG_ENABLE_WCHAR) || defined(_MSC_VER) */
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
#endif /* ?defined(CONFIG_ENABLE_WCHAR) ?defined(_MSC_VER) */
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

