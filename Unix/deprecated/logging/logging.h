/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
#include <base/result.h>

#if defined(linux)
#include <syscall.h>
#endif

#if defined(CONFIG_OS_WINDOWS)
#define getpid GetCurrentProcessId()
#endif

// The time stamp for log messages
#define TIMESTAMP(typ) \
{\
        MI_Uint64 currentTimeUsec;\
        void* ptr;\
        ptr = malloc(8);\
        free(ptr);\
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
 #define LOGD2(a) do { TIMESTAMP("T"); printf a; putchar('\n'); fflush(stdout); } while (0)
#else
 #define LOGD2(a)
#endif

#if TRACING_LEVEL > 2
 #define LOGW2(a) do { TIMESTAMP("W"); printf a; putchar('\n'); fflush(stdout); } while (0)
#else
 #define LOGW2(a)
#endif

#define LOGE2(a) do { TIMESTAMP("E"); printf a; putchar('\n'); fflush(stdout); } while (0)

/*
**==============================================================================
**
** Formatting functions for some data types
**
**==============================================================================
*/

BEGIN_EXTERNC

extern unsigned long get_tid();
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
extern MI_Result Time_Now(MI_Uint64* self);

END_EXTERNC

#endif // defined ENABLE_TRACING

#endif // defined _logging_h
