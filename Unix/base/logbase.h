/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_logbase_h
#define _omi_logbase_h

#include <common.h>
#include <stdarg.h>
#include <pal/format.h>
#include <pal/strings.h>

BEGIN_EXTERNC

/* Log levels (default level is OMI_WARNING */
typedef enum _Log_Level
{
    OMI_FATAL,
    OMI_ERROR,
    OMI_WARNING,
    OMI_INFO,
    OMI_DEBUG,
    OMI_VERBOSE
}
Log_Level;

/* Get the current log level */
Log_Level Log_GetLevel();

/*
**==============================================================================
**
** Log
**
**     This interface supports writing of log entries to a flat file. The 
**     following fragment shows how to use the logging facility.
**
**         Log_Open("/var/log/mylogfile");
**         ...
**         Log_Put(OMI_ERROR, __FILE__, __LINE__, "bad sock=%u", sock);
**         Log_Put(OMI_INFO, __FILE__, __LINE__, "started");
**         Log_Put(OMI_DEBUG, __FILE__, __LINE__, "got this far");
**         ...
**         Log_Close();
**
**     The first argument of Log_Put() is the log level, which is one of
**     the following (in descending order of priority).
**
**         OMI_FATAL
**         OMI_ERROR
**         OMI_WARNING
**         OMI_INFO
**         OMI_DEBUG
**         OMI_VERBOSE
**
**     Passing one of these to Log_SetLevel() affects which entries are
**     written to the log and which are ignored. For example, to log only 
**     OMI_FATAL and OMI_ERROR levels, call Log_SetLevel as follows.
**
**         Log_SetLevel(OMI_ERROR);
**
**     Afterwards, attempts to log anything below the OMI_ERROR level are
**     ignored. The default log level is OMI_WARNING.
**
**     The following macros simplify the writing of log entries by allowing
**     the caller to omit the level, __FILE__, and __LINE__ arguments.
**
**         LOGF() - OMI_FATAL
**         LOGE() - OMI_ERROR
**         LOGW() - OMI_WARNING
**         LOGI() - OMI_INFO
**         LOGD() - OMI_DEBUG
**         LOGV() - OMI_VERBOSE
**
**     Using these macros reduces the code example above to this.
**
**         Log_Open("/var/log/mylogfile");
**         ...
**         LOGE(("bad sock=%u", sock));
**         LOGI(("started"));
**         LOGD(("got this far"));
**         ...
**         Log_Close();
**
**     Notice the use of double parentheses (since macros do not support 
**     varying argument lists).
**
**     Log entries have this format:
**
**         YYYY/MM/DD HH:MM:SS: LEVEL: FILE(LINE): message...
**
**     The code snippet above produces the following log entries.
**
**         2010/01/01 12:43:26: ERROR: erp.c(10): bad sock=14
**         2010/01/01 12:43:27: INFO: erp.c(11): started
**         2010/01/01 12:43:28: DEBUG: erp.c(12): got this far
**
**==============================================================================
*/

/* Is log already open for output to a file or stderr */
MI_Boolean Log_IsOpen();

/* Open 'path' for append (create if it does not exist). */
MI_Result Log_Open(
    const ZChar* path);

/* Open 'fd' for append. */
MI_Result Log_OpenFD(
    int fd);

int Log_GetFD();

/* Open log and write log entries to standard error */
MI_Result Log_OpenStdErr();

/* Close the log file. */
void Log_Close();

/* Set the log level (ignore all log writes below this level). */
void Log_SetLevel(
    Log_Level level);

/* Set the level from one of the following strings/numbers:
 *    FATAL/1
 *    ERROR/2
 *    WARNING/3
 *    INFO/4
 *    DEBUG/5
 *
 *  Examples: 
 *      Log_SetLevelFromString("DEBUG");
 *      Log_SetLevelFromString("3");
 */
int Log_SetLevelFromString(_In_z_ const char* level);

int Log_SetLevelFromPalCharString(_In_z_ const PAL_Char* level);

/* represents the length of longest loglevel string */
#define MAX_LOG_LEVEL_STRING_LENGTH 20

/* Get a string representing the current log level, which will be one of the
 * following symbols: FATAL, ERROR, WARNING, INFO, DEBUG.
 */
const char* Log_GetLevelString(Log_Level level);

/* tells whether the log is routed to stderr */
MI_Boolean Log_IsRoutedToStdErr();

Log_Level Log_GetLevel();

int Log_Put(
    Log_Level level,
    const char* file,
    MI_Uint32 line,
    const ZChar* format,
    ...);

/* Va_List form of Log_Put. Returns '1' if output required,'0' otherwise*/
int Log_VPut(
    Log_Level level,
    const char* file,
    MI_Uint32 line,
    const ZChar* format,
    va_list ap);

/* Private internal function. */
#if defined(CONFIG_ENABLE_DEBUG)
int __Log_Put1(
    Log_Level level,
    const char* file,
    MI_Uint32 line);
#endif

/* Private internal function. */
//#if defined(CONFIG_ENABLE_DEBUG)
void __Log_Put2(
    const ZChar* format,
    ...);
//#endif

void FilePutLog(
    int priority,
    int eventId,
    const char * file,
    int line,
    const PAL_Char* format,
    ...);

/* Private internal function. */
int _GetCurrentTimeInUsec(MI_Uint64* usec);

void __Logf(const ZChar* format, ...);
void __Loge(const ZChar* format, ...);
void __Logw(const ZChar* format, ...);
void __Logi(const ZChar* format, ...);
void __Logd(const ZChar* format, ...);
void __Logv(const ZChar* format, ...);

/*
 * This function appears as the false condition expression in the macros 
 * below. It suppresses the Windows 'conditional expression is constant' 
 * warning without the use of pragmas (which cannot be used in macros).
 */
INLINE int __LogFalse() { return 0; }

#if defined(CONFIG_ENABLE_DEBUG)
# define __LOGF(ARGS) \
    do \
    { \
        if (__Log_Put1(OMI_FATAL, __FILE__, __LINE__)) \
            __Log_Put2 ARGS; \
    } \
    while (__LogFalse())
# define __LOGE(ARGS) \
    do \
    { \
        if (__Log_Put1(OMI_ERROR, __FILE__, __LINE__)) \
            __Log_Put2 ARGS; \
    } \
    while (__LogFalse())
# define __LOGW(ARGS) \
    do \
    { \
        if (__Log_Put1(OMI_WARNING, __FILE__, __LINE__)) \
            __Log_Put2 ARGS; \
    } \
    while (__LogFalse())
# define __LOGI(ARGS) \
    do \
    { \
        if (__Log_Put1(OMI_INFO, __FILE__, __LINE__)) \
            __Log_Put2 ARGS; \
    } \
    while (__LogFalse())
# define __LOGD(ARGS) \
    do \
    { \
        if (__Log_Put1(OMI_DEBUG, __FILE__, __LINE__)) \
            __Log_Put2 ARGS; \
    } \
    while (__LogFalse())
# define __LOGV(ARGS) \
    do \
    { \
        if (__Log_Put1(OMI_VERBOSE, __FILE__, __LINE__)) \
            __Log_Put2 ARGS; \
    } \
    while (__LogFalse())
#else
# define __LOGF(ARGS) __Logf ARGS
# define __LOGE(ARGS) __Loge ARGS
# define __LOGW(ARGS) __Logw ARGS
# define __LOGI(ARGS) __Logi ARGS
# define __LOGD(ARGS) __Logd ARGS
# define __LOGV(ARGS) __Logv ARGS
#endif

END_EXTERNC

#endif /* _omi_logbase_h */

