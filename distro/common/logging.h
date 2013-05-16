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

#ifndef _logging_h
#define _logging_h

// Logging functions for OMI components used outside of omi{agent,check,cli,gen,reg,server}

#ifndef ENABLE_TRACING  // We need to change this to log instead of printing on
                        // stdout, when log file rotation is implemented and when
                        // logging from library components used outside of
                        // omi{agent,check,cli,gen,reg,server} is finished.

#define LOGE2(a)
#define LOGW2(a)
#define LOGD2(a)
#define LOGX2(a)

#else

#include <stdio.h>
#include <stddef.h>
#include <pthread.h>

#include <MI.h>
#include <common.h>
#include <base/time.h>
#include <base/result.h>
#include <io/io.h>

#if defined(linux)
#include <syscall.h>
#endif

#if defined(CONFIG_OS_WINDOWS)
#define getpid GetCurrentProcessId()
#endif

// We prefer the LWP thread ID for Linux, but use the pthread ID (the address of errno) for other Unixes
static unsigned long get_tid()
{
#if defined(CONFIG_OS_WINDOWS)
    return (unsigned long)GetCurrentThreadId();
#elif defined(linux)
    return (unsigned long)syscall(SYS_gettid);
#else
    return (unsigned long)pthread_self();
#endif
}

// The time stamp for log messages
#define TIMESTAMP(typ) \
{\
        MI_Uint64 currentTimeUsec;\
        Time_Now(&currentTimeUsec);\
        printf("%s %s %u:%lu %s:%d ", FmtTime(currentTimeUsec), typ, (unsigned int)getpid(), get_tid(), __FILE__, __LINE__);\
}

#undef printf

// the LOGE2, LOGW2 nd LOGD2 macros
#ifndef TRACING_LEVEL
#define TRACING_LEVEL 2
#endif

#if TRACING_LEVEL > 4
 #define LOGX2(a) TIMESTAMP("X"); printf a; putchar('\n'); fflush(stdout);
#else
 #define LOGX2(a)
#endif

#if TRACING_LEVEL > 3
 #define LOGD2(a) TIMESTAMP("T"); printf a; putchar('\n'); fflush(stdout);
#else
 #define LOGD2(a)
#endif

#if TRACING_LEVEL > 2
 #define LOGW2(a) TIMESTAMP("W"); printf a; putchar('\n'); fflush(stdout);
#else
 #define LOGW2(a)
#endif

#define LOGE2(a) TIMESTAMP("E"); printf a; putchar('\n'); fflush(stdout);

/*
**==============================================================================
**
** Formatting functions for some data types
**
**==============================================================================
*/

BEGIN_EXTERNC

extern const char* mistrerror(MI_Result res);
extern const char* selectorflagstr(MI_Uint32 Flags);
extern const char* bitnumberstr(unsigned long Bits);
extern const char* sslstrerror(int SslError);
extern const char* notifyitemtypestr(int NotifyItemType);
extern const char* clientstatusstr(int Status);
extern const char* messagetagnamestr(int Tag);
extern const char* protocoleventnamestr(int Event);
extern const char* FmtTime(MI_Uint64 Time);
extern const char* FmtInterval( MI_Sint64 Time);

END_EXTERNC

#endif // defined ENABLE_TRACING

#endif // defined _logging_h
