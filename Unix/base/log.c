/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "logbase.h"

# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <time.h>
# if defined(linux)
#  include <syscall.h>
# endif

// Disable this by default as it slows down performance (by about 12% in tests with 2 threads)
// it can be re-activated if intermingled traces become too difficult to read and it doesnt affect repro in that particular case
// Note though that It will not prevent the case of different executables logging to the same files
//#define LOGC_USES_LOCK

#include <pal/strings.h>
#include <pal/format.h>
#include <pal/process.h>
#include <pal/thread.h>
#include <pal/once.h>
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


struct LogState
{
    FILE* f;
    int   refcount;
    int   fd;
    char path[PAL_MAX_PATH_SIZE];
};

static struct LogState g_logstate = {NULL, 0, 0, { 0 }};
static struct _Once    g_once_state = ONCE_INITIALIZER;

#ifdef LOGC_USES_LOCK
static Lock _logLock;
#endif
static Log_Level _level = OMI_WARNING;

int Log_GetFD()
{
    return fileno(g_logstate.f);
}

static const char* _levelStrings[] =
{
    "FATAL",
    "ERROR",
    "WARNING",
    "INFO",
    "DEBUG",
    "VERBOSE",
};



/*
 * Worker functions for log opening
 */

static _Success_(return == 0) int _LogOpenWorkerFunc( _In_ void* path, _Outptr_result_maybenull_ void** value)
{
    if (g_logstate.path[0] != 0)
    {
        return MI_RESULT_FAILED;
    }

    if (g_logstate.f)
    {
        return MI_RESULT_OK;
    }

    if (StrTcslcpy(g_logstate.path, (const MI_Char*) path, PAL_MAX_PATH_SIZE) >= PAL_MAX_PATH_SIZE)
    {
        return MI_RESULT_FAILED;
    }

    g_logstate.f = fopen(g_logstate.path, "a");

    return MI_RESULT_OK;
}

static _Success_(return == 0) int _LogOpenFDWorkerFunc( _In_ void* data, _Outptr_result_maybenull_ void** value)

{
    if (g_logstate.f)
    {
        return MI_RESULT_OK;
    }

    g_logstate.f = fdopen(g_logstate.fd, "a");
    if (!g_logstate.f) {
        return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
}

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
    struct timeval tv;
    struct timezone tz;
    memset(&tv, 0, sizeof(tv));
    memset(&tz, 0, sizeof(tz));

    if (gettimeofday(&tv, &tz) != 0)
        return -1;

    *usec = (MI_Uint64)tv.tv_sec * (MI_Uint64)1000000 + (MI_Uint64)tv.tv_usec;
    return 0;
}

#define TIMESTAMP_SIZE 128

int GetTimeStamp(_Pre_writable_size_(TIMESTAMP_SIZE) char buf[TIMESTAMP_SIZE])
{
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

    return 0;
}

static void _PutHeader(
    FILE* os, 
    const char* file, 
    unsigned int line, 
    Log_Level level)
{
    char buf[TIMESTAMP_SIZE];

    GetTimeStamp(buf);
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
    return (g_logstate.f != NULL);
}

MI_Result Log_Open(
    const ZChar* path)
{
    if (!path)
        return MI_RESULT_FAILED;

#ifdef LOGC_USES_LOCK
    Lock_Init(&_logLock);
#endif

    int rslt;

    rslt = Once_Invoke(&g_once_state, _LogOpenWorkerFunc, (void*)path);
    if (0 == rslt )
    {
        Atomic_Inc((volatile ptrdiff_t*)&g_logstate.refcount);
    }

    return (MI_Result) rslt;
}

MI_Result Log_OpenFD(
    int fd)
{
    MI_Result rslt = MI_RESULT_FAILED; 

    if (fd < 0)
    {
        return MI_RESULT_FAILED;
    }

    g_logstate.fd = fd;
    rslt = Once_Invoke(&g_once_state, _LogOpenFDWorkerFunc, NULL);
    if (MI_RESULT_OK == rslt )
    {
        Atomic_Inc((volatile ptrdiff_t*)&g_logstate.refcount);
    }

    return rslt;
}


MI_Result Log_OpenStdErr()
{
    g_logstate.f = stderr;
    return MI_RESULT_OK;
}

MI_Boolean Log_IsRoutedToStdErr()
{
    return (g_logstate.f == stderr);
}

void Log_Close()
{
    if (Atomic_Dec((volatile ptrdiff_t*)&g_logstate.refcount) == 0)
    {
        if (g_logstate.f && g_logstate.f != stderr)
        {
            fclose(g_logstate.f);
        }
        g_logstate.f = NULL;
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
        Strlcpy(buf, level, MAX_LOG_LEVEL_STRING_LENGTH);

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

    if (!g_logstate.f || level > _level)
        return 0;

#ifdef LOGC_USES_LOCK
    Lock_Acquire(&_logLock);
#endif

    _PutHeader(g_logstate.f, file, line, level);

    va_start(ap, format);

    Vftprintf(g_logstate.f, format, ap);

    va_end(ap);
    Ftprintf(g_logstate.f, ZT("\n"));

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
    if (!g_logstate.f || level > _level)
        return 0;

    file = scs(file);

#ifdef LOGC_USES_LOCK
    Lock_Acquire(&_logLock);
#endif

    _PutHeader(g_logstate.f, file, line, level);

    Vftprintf(g_logstate.f, format, ap);

    Ftprintf(g_logstate.f, ZT("\n"));
    fflush(g_logstate.f);

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
    if (!g_logstate.f || level > _level)
        return 0;

#ifdef LOGC_USES_LOCK
    Lock_Acquire(&_logLock);
#endif
    _PutHeader(g_logstate.f, file, line, level);
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

    if (!g_logstate.f)
        return;

#ifdef LOGC_USES_LOCK
    Lock_Acquire(&_logLock);
#endif
    va_start(ap, format);

    Vftprintf(g_logstate.f, format, ap);

    Ftprintf(g_logstate.f, ZT("\n"));
    fflush(g_logstate.f);
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

