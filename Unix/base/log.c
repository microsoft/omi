/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "logbase.h"

#if defined(CONFIG_OS_WINDOWS)
# include <windows.h>
# include <time.h>
#else
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <time.h>
# if defined(linux)
#  include <syscall.h>
# endif
#endif

// Disable this by default as it slows down performance (by about 12% in tests with 2 threads)
// it can be re-activated if intermingled traces become too difficult to read and it doesnt affect repro in that particular case
// Note though that It will not prevent the case of different executables logging to the same files
//#define LOGC_USES_LOCK

#include <pal/strings.h>
#include <pal/format.h>
#include <pal/process.h>
#include <pal/thread.h>
#ifdef LOGC_USES_LOCK
#include <pal/lock.h>
#endif

/*
**==============================================================================
**
** Local definitions:
**
**==============================================================================
*/

static FILE* _os;
#ifdef LOGC_USES_LOCK
static Lock _logLock;
#endif
static Log_Level _level = OMI_WARNING;


static const char* _levelStrings[] =
{
    "FATAL",
    "ERROR",
    "WARNING",
    "INFO",
    "DEBUG",
    "VERBOSE",
};

PAL_INLINE PAL_Boolean _ShouldLog(int level)
{
    if (level > Log_GetLevel())
        return PAL_FALSE;
    else
        return PAL_TRUE;
}

#define FMTSIZE 1024
void FilePutLog(
    int priority,
    int eventId,
    const char * file,
    int line,
    const PAL_Char* format,
    ...)
{
    if ((unsigned int)priority > OMI_VERBOSE)
        return;

    if (_ShouldLog(priority))
    {
        TChar fmt[FMTSIZE];
        va_list ap;

        Stprintf(fmt, FMTSIZE, PAL_T("EventId=%d Priority=%s "), eventId, _levelStrings[priority]);
        Tcslcat(fmt, format, FMTSIZE);
                
        va_start(ap, format);
        Log_VPut((Log_Level)priority, file, line, fmt, ap);
        va_end(ap);        
    }    
}

int _GetCurrentTimeInUsec(MI_Uint64* usec)
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
    Ftprintf(os, ZT("%s "), scs(buf));
    Ftprintf(os, ZT("[%u,%lu] "), (unsigned int)Process_ID(), (unsigned long)Thread_TID());
    Ftprintf(os, ZT("%s: "), scs(_levelStrings[(int)level]));

    if (file)
        Ftprintf(os, ZT("%s(%u): "), scs(file), line);
}

/*
**==============================================================================
**
** Public definitions:
**
**==============================================================================
*/

MI_Boolean Log_IsOpen()
{
    return (_os != NULL);
}

#if defined(CONFIG_OS_WINDOWS)
#include <share.h>
#endif

MI_Result Log_Open(
    const ZChar* path)
{
    if (!path || _os)
        return MI_RESULT_FAILED;

#ifdef LOGC_USES_LOCK
    Lock_Init(&_logLock);
#endif

#if defined(CONFIG_OS_WINDOWS)
# if (MI_CHAR_TYPE == 1)
    {
        _os = _fsopen(path, "a", _SH_DENYWR);
        if (_os == NULL)
            return MI_RESULT_FAILED;

        return MI_RESULT_OK;
    }
# else
    {
        _os = _wfsopen(path, L"a", _SH_DENYWR);
        if (_os == NULL)
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
        char path7[PAL_MAX_PATH_SIZE];
        if (StrWcslcpy(path7, path, PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
            return MI_RESULT_FAILED;
        
        _os = fopen(path7, "a");

        if (!_os)
        {
            return MI_RESULT_FAILED;
        }

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

MI_Boolean Log_IsRoutedToStdErr()
{
    return (_os == stderr);
}

void Log_Close()
{
    if (_os && _os != stderr)
    {
        fclose(_os);
    }
    _os = NULL;
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

int Log_SetLevelFromString(_In_z_ const char* level)
{
    size_t i;

    for (i = 0; i < sizeof(_levelStrings) / sizeof(_levelStrings[0]); i++)
    {
        char buf[12];
        size_t size;
        const char* str = Uint32ToStr(buf, (MI_Uint32)i, &size);

        if (Strcasecmp(level, _levelStrings[i]) == 0 || 
            (str && Strcasecmp(level, str) == 0))
        {
            _level = (Log_Level)i;
            return 0;
        }
    }

    return -1;
}

int Log_SetLevelFromPalCharString(_In_z_ const PAL_Char* level)
{
    if(level && (Tcslen(level) < MAX_LOG_LEVEL_STRING_LENGTH))
    {
        char buf[MAX_LOG_LEVEL_STRING_LENGTH];
#if defined(CONFIG_ENABLE_WCHAR)
        StrWcslcpy(buf, level, MAX_LOG_LEVEL_STRING_LENGTH);
#else
        Strlcpy(buf, level, MAX_LOG_LEVEL_STRING_LENGTH);
#endif
        if(Log_SetLevelFromString(buf) != 0)
        {
            return -1;
        }

        return 0;
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

#ifdef LOGC_USES_LOCK
    Lock_Acquire(&_logLock);
#endif

    _PutHeader(_os, file, line, level);

    va_start(ap, format);

    Vftprintf(_os, format, ap);

    va_end(ap);
    Ftprintf(_os, ZT("\n"));

#ifdef LOGC_USES_LOCK
    Lock_Release(&_logLock);
#endif

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

    file = scs(file);

#ifdef LOGC_USES_LOCK
    Lock_Acquire(&_logLock);
#endif

    _PutHeader(_os, file, line, level);

    Vftprintf(_os, format, ap);

    Ftprintf(_os, ZT("\n"));
    fflush(_os);

#ifdef LOGC_USES_LOCK
    Lock_Release(&_logLock);
#endif

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

#ifdef LOGC_USES_LOCK
    Lock_Acquire(&_logLock);
#endif
    _PutHeader(_os, file, line, level);
#ifdef LOGC_USES_LOCK
    Lock_Release(&_logLock);
#endif

    return 1;
}

#endif /* defined(CONFIG_ENABLE_DEBUG) */

void __Log_Put2(
    const ZChar* format,
    ...)
{
    va_list ap;
    memset(&ap, 0, sizeof(ap));

    if (!_os)
        return;

#ifdef LOGC_USES_LOCK
    Lock_Acquire(&_logLock);
#endif
    va_start(ap, format);

    Vftprintf(_os, format, ap);

    Ftprintf(_os, ZT("\n"));
    fflush(_os);
#ifdef LOGC_USES_LOCK
    Lock_Release(&_logLock);
#endif
}

void __Logf(const ZChar* format, ...)
{
    va_list ap;
    va_start(ap, format);
    Log_VPut(OMI_FATAL, NULL, 0, format, ap);
    va_end(ap);
}

void __Loge(const ZChar* format, ...)
{
    va_list ap;
    va_start(ap, format);
    Log_VPut(OMI_ERROR, NULL, 0, format, ap);
    va_end(ap);
}

void __Logw(const ZChar* format, ...)
{
    va_list ap;
    va_start(ap, format);
    Log_VPut(OMI_WARNING, NULL, 0, format, ap);
    va_end(ap);
}

void __Logi(const ZChar* format, ...)
{
    va_list ap;
    va_start(ap, format);
    Log_VPut(OMI_INFO, NULL, 0, format, ap);
    va_end(ap);
}

void __Logd(const ZChar* format, ...)
{
    va_list ap;
    va_start(ap, format);
    Log_VPut(OMI_DEBUG, NULL, 0, format, ap);
    va_end(ap);
}

void __Logv(const ZChar* format, ...)
{
    va_list ap;
    va_start(ap, format);
    Log_VPut(OMI_VERBOSE, NULL, 0, format, ap);
    va_end(ap);
}

