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

#ifndef _omi_log_h
#define _omi_log_h

#include <common.h>
#include <stdarg.h>

BEGIN_EXTERNC

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
**         Log_Put(LOG_ERROR, __FILE__, __LINE__, "bad sock=%u", sock);
**         Log_Put(LOG_INFO, __FILE__, __LINE__, "started");
**         Log_Put(LOG_DEBUG, __FILE__, __LINE__, "got this far");
**         ...
**         Log_Close();
**
**     The first argument of Log_Put() is the log level, which is one of
**     the following (in descending order of priority).
**
**         LOG_FATAL
**         LOG_ERROR
**         LOG_WARNING
**         LOG_INFO
**         LOG_DEBUG
**
**     Passing one of these to Log_SetLevel() affects which entries are
**     written to the log and which are ignored. For example, to log only 
**     LOG_FATAL and LOG_ERROR levels, call Log_SetLevel as follows.
**
**         Log_SetLevel(LOG_ERROR);
**
**     Afterwards, attempts to log anything below the LOG_ERROR level are
**     ignored. The default log level is LOG_WARNING.
**
**     The following macros simplify the writing of log entries by allowing
**     the caller to omit the level, __FILE__, and __LINE__ arguments.
**
**         LOGF() - LOG_FATAL
**         LOGE() - LOG_ERROR
**         LOGW() - LOG_WARNING
**         LOGI() - LOG_INFO
**         LOGD() - LOG_DEBUG
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

/* Log levels (default level is LOG_WARNING */
typedef enum _Log_Level
{
    LOG_FATAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
    LOG_DEBUG
}
Log_Level;

/* Open 'path' for append (create if it does not exist). */
MI_Result Log_Open(
    const ZChar* path);

/* Open 'fd' for append. */
MI_Result Log_OpenFD(
    int fd);

/* Open log and write log entries to standard error */
MI_Result Log_OpenStdErr();

/* Close the log file. */
void Log_Close();

/* Set the log level (ignore all log writes below this level). */
void Log_SetLevel(
    Log_Level level);

/* Get the current log level */
Log_Level Log_GetLevel();

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
int Log_SetLevelFromString(const char* level);

/* Get a string representing the current log level, which will be one of the
 * following symbols: FATAL, ERROR, WARNING, INFO, DEBUG.
 */
const char* Log_GetLevelString(Log_Level level);

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
#if defined(CONFIG_ENABLE_DEBUG)
void __Log_Put2(
    const ZChar* format,
    ...);
#endif

void __Logf(const ZChar* format, ...);
void __Loge(const ZChar* format, ...);
void __Logw(const ZChar* format, ...);
void __Logi(const ZChar* format, ...);
void __Logd(const ZChar* format, ...);

/*
 * This funtion appears as the false condition expression in the macros 
 * below. It suppresses the Windows 'conditional expression is constant' 
 * warning without the use of pragmas (which cannot be used in macros).
 */
INLINE int __LogFalse() { return 0; }

#if defined(CONFIG_ENABLE_DEBUG)
# define LOGF(ARGS) \
    do \
    { \
        if (__Log_Put1(LOG_FATAL, __FILE__, __LINE__)) \
            __Log_Put2 ARGS; \
    } \
    while (__LogFalse())
# define LOGE(ARGS) \
    do \
    { \
        if (__Log_Put1(LOG_ERROR, __FILE__, __LINE__)) \
            __Log_Put2 ARGS; \
    } \
    while (__LogFalse())
# define LOGW(ARGS) \
    do \
    { \
        if (__Log_Put1(LOG_WARNING, __FILE__, __LINE__)) \
            __Log_Put2 ARGS; \
    } \
    while (__LogFalse())
# define LOGI(ARGS) \
    do \
    { \
        if (__Log_Put1(LOG_INFO, __FILE__, __LINE__)) \
            __Log_Put2 ARGS; \
    } \
    while (__LogFalse())
# define LOGD(ARGS) \
    do \
    { \
        if (__Log_Put1(LOG_DEBUG, __FILE__, __LINE__)) \
            __Log_Put2 ARGS; \
    } \
    while (__LogFalse())
#else
# define LOGF(ARGS) __Logf ARGS
# define LOGE(ARGS) __Loge ARGS
# define LOGW(ARGS) __Logw ARGS
# define LOGI(ARGS) __Logi ARGS
# define LOGD(ARGS) __Logd ARGS
#endif

#define LOGTRACE LOGD((MI_T("LOGTRACE: %s(%u)"), __FILE__, __LINE__))

END_EXTERNC

#endif /* _omi_log_h */
