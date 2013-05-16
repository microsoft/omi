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

#include "log.h"

#if defined(CONFIG_OS_WINDOWS)
# include <windows.h>
# include <time.h>
#else
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <time.h>
#endif

#include "strings.h"
#include <io/io.h>

/*
**==============================================================================
**
** Local definitions:
**
**==============================================================================
*/

static FILE* _os;

static const char* _levelStrings[] =
{
    "FATAL",
    "ERROR",
    "WARNING",
    "INFO",
    "DEBUG",
};

static Log_Level _level = LOG_WARNING;

static int _GetCurrentTimeInUsec(MI_Uint64* usec)
{
#if defined(CONFIG_OS_WINDOWS)
    FILETIME ft;
    ULARGE_INTEGER tmp;

    GetSystemTimeAsFileTime(&ft);
    tmp.u.LowPart = ft.dwLowDateTime;
    tmp.u.HighPart = ft.dwHighDateTime;
    tmp.QuadPart -= 0X19DB1DED53E8000;
    *usec = tmp.QuadPart / (UINT64)10;

    return 0;
#else
    struct timeval tv;
    struct timezone tz;
    memset(&tv, 0, sizeof(tv));
    memset(&tz, 0, sizeof(tz));

    if (gettimeofday(&tv, &tz) != 0)
        return -1;

    *usec = (MI_Uint64)tv.tv_sec * (MI_Uint64)1000000 + (MI_Uint64)tv.tv_usec;
    return 0;
#endif
}

#define TIMESTAMP_SIZE 128

static int _GetTimeStamp(_Pre_writable_size_(TIMESTAMP_SIZE) char buf[TIMESTAMP_SIZE])
{
#if defined(CONFIG_OS_WINDOWS)
    {
        SYSTEMTIME systime;
        GetLocalTime(&systime);

        sprintf_s(
            buf,
            TIMESTAMP_SIZE,
            "%02u/%02u/%02u %02u:%02u:%02u",
            systime.wYear,
            systime.wMonth,
            systime.wDay,
            systime.wHour,
            systime.wMinute,
            systime.wSecond);
    }
#else
    MI_Uint64 usec;

    if (_GetCurrentTimeInUsec(&usec) != 0)
    {
        buf[0] = '\0';
        return -1;
    }

    {
        time_t t = usec / 1000000;
        struct tm tm;
        localtime_r(&t, &tm);
        sprintf(
            buf,
            "%02u/%02u/%02u %02u:%02u:%02u",
            tm.tm_year + 1900,
            tm.tm_mon + 1,
            tm.tm_mday,
            tm.tm_hour,
            tm.tm_min,
            tm.tm_sec);
    }
#endif

    return 0;
}

static void _PutHeader(
    FILE* os,
    const char* file,
    unsigned int line,
    Log_Level level)
{
    char buf[TIMESTAMP_SIZE];

    _GetTimeStamp(buf);
    Fzprintf(os, ZT("%s: "), scs(buf));
    Fzprintf(os, ZT("%s: "), scs(_levelStrings[(int)level]));

    if (file)
        Fzprintf(os, ZT("%s(%u): "), scs(file), line);
}

/*
**==============================================================================
**
** Public definitions:
**
**==============================================================================
*/

MI_Result Log_Open(
    const ZChar* path)
{
    if (!path || _os)
        return MI_RESULT_FAILED;

#if defined(CONFIG_OS_WINDOWS)
# if (MI_CHAR_TYPE == 1)
    {
        if (fopen_s(&_os, path, "a") != 0)
            return MI_RESULT_FAILED;

        return MI_RESULT_OK;
    }
# else
    {
        if (_wfopen_s(&_os, path, L"a") != 0)
            return MI_RESULT_FAILED;

        return MI_RESULT_OK;
    }
# endif
#else
# if (MI_CHAR_TYPE == 1)
    {
        _os = fopen(path, "a");

        if (!_os)
            return MI_RESULT_FAILED;

        return MI_RESULT_OK;
    }
# else
    {
        char* path7 = ZStrdup(path);

        if (!path7)
            return MI_RESULT_FAILED;

        _os = fopen(path7, "a");

        if (!_os)
        {
            free(path7);
            return MI_RESULT_FAILED;
        }

        free(path7);
        return MI_RESULT_OK;
    }
# endif
#endif
}

MI_Result Log_OpenFD(
    int fd)
{
#if defined(CONFIG_OS_WINDOWS)
    MI_UNUSED(fd);
    return MI_RESULT_FAILED;
#else
    if (fd < 0 || _os)
        return MI_RESULT_FAILED;

    _os = fdopen(fd, "a");
    if (!_os)
        return MI_RESULT_FAILED;

    return MI_RESULT_OK;

#endif
}

MI_Result Log_OpenStdErr()
{
    _os = stderr;
    return MI_RESULT_OK;
}

void Log_Close()
{
    if (_os && _os != stderr)
    {
        fclose(_os);
        _os = NULL;
    }
}

void Log_SetLevel(
    Log_Level level)
{
    _level = level;
}

Log_Level Log_GetLevel()
{
    return _level;
}

int Log_SetLevelFromString(const char* level)
{
    size_t i;

    for (i = 0; i < sizeof(_levelStrings) / sizeof(_levelStrings[0]); i++)
    {
        char buf[12];
        size_t size;
        const char* str = Uint32ToStr(buf, i, &size);

        if (Strcasecmp(level, _levelStrings[i]) == 0 ||
            Strcasecmp(level, str) == 0)
        {
            _level = (Log_Level)i;
            return 0;
        }
    }

    return -1;
}

const char* Log_GetLevelString(Log_Level level)
{
    return _levelStrings[(int)level];
}

int Log_Put(
    Log_Level level,
    const char* file,
    MI_Uint32 line,
    const ZChar* format,
    ...)
{
    va_list ap;
    memset(&ap, 0, sizeof(ap));

    if (!_os || level > _level)
        return 0;

    _PutHeader(_os, file, line, level);

    va_start(ap, format);

    Vfzprintf(_os, format, ap);

    va_end(ap);
    Fzprintf(_os, ZT("\n"));

    return 1;
}

int Log_VPut(
    Log_Level level,
    const char* file,
    MI_Uint32 line,
    const ZChar* format,
    va_list ap)
{
    if (!_os || level > _level)
        return 0;

    _PutHeader(_os, file, line, level);

    Vfzprintf(_os, format, ap);

    Fzprintf(_os, ZT("\n"));
    fflush(_os);

    return 1;
}

#if defined(CONFIG_ENABLE_DEBUG)

int __Log_Put1(
    Log_Level level,
    const char* file,
    MI_Uint32 line)
{
    if (!_os || level > _level)
        return 0;

    _PutHeader(_os, file, line, level);

    return 1;
}

void __Log_Put2(
    const ZChar* format,
    ...)
{
    va_list ap;
    memset(&ap, 0, sizeof(ap));

    if (!_os)
        return;

    va_start(ap, format);

    Vfzprintf(_os, format, ap);

    Fzprintf(_os, ZT("\n"));
    fflush(_os);
}

#endif /* defined(CONFIG_ENABLE_DEBUG) */

void __Logf(const ZChar* format, ...)
{
    va_list ap;
    va_start(ap, format);
    Log_VPut(LOG_FATAL, NULL, 0, format, ap);
    va_end(ap);
}

void __Loge(const ZChar* format, ...)
{
    va_list ap;
    va_start(ap, format);
    Log_VPut(LOG_ERROR, NULL, 0, format, ap);
    va_end(ap);
}

void __Logw(const ZChar* format, ...)
{
    va_list ap;
    va_start(ap, format);
    Log_VPut(LOG_WARNING, NULL, 0, format, ap);
    va_end(ap);
}

void __Logi(const ZChar* format, ...)
{
    va_list ap;
    va_start(ap, format);
    Log_VPut(LOG_INFO, NULL, 0, format, ap);
    va_end(ap);
}

void __Logd(const ZChar* format, ...)
{
    va_list ap;
    va_start(ap, format);
    Log_VPut(LOG_DEBUG, NULL, 0, format, ap);
    va_end(ap);
}
