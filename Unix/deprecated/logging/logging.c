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

#include <stdio.h>
#include <stddef.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

#include <MI.h>
#include <common.h>
#include <base/result.h>

#include "logging.h"

#if defined(linux)
#include <syscall.h>
#endif

#if defined(CONFIG_OS_WINDOWS)
# include <windows.h>
# include <time.h>
#elif defined(CONFIG_POSIX)
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# include <sys/types.h>
# include <openssl/ssl.h>
# include <openssl/err.h>
#endif

//==============================================================================
//
// Tables of values used in debugging output
//
//==============================================================================

// type for describing enums
typedef struct _NameValuePairs
{
    unsigned int Value;
    const char* Name;
} NameValuePairs;

// names of selector mask flags
static const char* SelectorFlagNames[] = { "ADD", "READ", "WRITE", "EXCEPTION", "TIMEOUT", "REMOVE", "DESTORY", "IGNORE_REG_OVERLOAD" };

// bit numbers
static const char* BitNumberNames[32] =
{
     "0",  "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",
    "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
    "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
    "30", "31"
};

// names of HttpClient statuses
static NameValuePairs ClientStatusNames[] =
{
    { 200, "OKAY" },      /* operations was successful */
    { 408, "TIMEOUT" },   /* operation was not completed within required timeout */
    {   0, "FAILED" },    /* network error (closed connection, unable to connect, etc.) */
    { 404, "NOTFOUND" },  /* HTTP status 404 */
    { 410, "CANCELED" }   /* operation was canceled by user */
};

static NameValuePairs NotifyItemTypeNames[] =
{
    { 0, "CONNECT" },
    { 1, "START_REQUEST" },
    { 2, "DELETE_HTTP" },
    { 3, "SET_TIMEOUT" }
};

static NameValuePairs MessageTagNames[] =
{
    { 1, "GetInstanceReqTag" },
    { 2, "PostInstanceMsgTag" },
    { 3, "EnumerateInstancesReqTag" },
    { 4, "PostResultMsgTag" },
    { 5, "NoOpReqTag" },
    { 6, "NoOpRspTag" },
    { 7, "InvokeReqTag" },
    { 8, "AssociatorsOfReqTag" },
    { 9, "ReferencesOfReqTag" },
    { 10, "SubscribeReqTag" },
    { 11, "SubscribeResTag" },
    { 12, "DeleteInstanceReqTag" },
    { 13, "CreateInstanceReqTag" },
    { 14, "ModifyInstanceReqTag" },
    { 15, "BinProtocolNotificationTag" },
#ifndef DISABLE_SHELL
    { 24, "ShellCreateReqTag" },
    { 25, "ShellDeleteReqTag" },
    { 26, "ShellReceiveReqTag" },
    { 27, "ShellSendReqTag" },
    { 28, "ShellSignalReqTag" },
    { 29, "ShellConnectReqTag" },
    { 30, "ShellReconnectReqTag" },
    { 31, "ShellDisconnectReqTag" },
    { 32, "ShellCommandReqTag" },
#endif
};

static NameValuePairs ProtocolEventNames[] =
{
    { 0, "CONNECT" },
    { 1, "CONNECT_FAILED" },
    { 2, "DISCONNECT" }
};

//==============================================================================
//
// Helper function for time
//
//==============================================================================

MI_EXPORT MI_Result Time_Now(
    MI_Uint64* self)
{
#if defined(CONFIG_OS_WINDOWS)
    FILETIME ft;
    ULARGE_INTEGER tmp;

    GetSystemTimeAsFileTime(&ft);
    tmp.u.LowPart = ft.dwLowDateTime;
    tmp.u.HighPart = ft.dwHighDateTime;
    tmp.QuadPart -= 0x19DB1DED53E8000;
    *self = tmp.QuadPart / (UINT64)10;
    return MI_RESULT_OK;
#else
    struct timeval tv;
    struct timezone tz;
    memset(&tv, 0, sizeof(tv));
    memset(&tz, 0, sizeof(tz));

    if (gettimeofday(&tv, &tz) != 0)
        return MI_RESULT_FAILED;

    *self = (MI_Uint64)tv.tv_sec * (MI_Uint64)1000000 + (MI_Uint64)tv.tv_usec;
    return MI_RESULT_OK;
#endif
}

//==============================================================================
//
// Helper functions for formatting debugging output
//
//==============================================================================

// We prefer the LWP thread ID for Linux, but use the pthread ID (the address of errno) for other UNIXes
MI_EXPORT unsigned long get_tid()
{
#if defined(CONFIG_OS_WINDOWS)
    return (unsigned long)GetCurrentThreadId();
#elif defined(linux)
    return (unsigned long)syscall(SYS_gettid);
#else
    return (unsigned long)pthread_self();
#endif
}

static char FmtBuf[4][256];
static int WhichFmtBuf = 0;

static const char* FmtBits(MI_Uint32 Mask, const char* Names[], size_t NumNames)
{
    unsigned int i;
    char* NamesBuf = FmtBuf[WhichFmtBuf];

    *NamesBuf = '\0';
    for (i = 0; i < (MI_Uint32)NumNames; i++)
    {
        if ((Mask & (1 << i)) != 0)
        {
            if (*NamesBuf != '\0')
            {
                strcat(NamesBuf, ",");
			}
            strcat(NamesBuf, Names[i]);
		}
	}
    if (*NamesBuf == '\0')
    {
        strcpy(NamesBuf, "none");
	}
    WhichFmtBuf++;
    WhichFmtBuf &= 3;
    return NamesBuf;
}

// formatter for enums
static const char* FmtEnum(unsigned int Value, NameValuePairs* Pairs, size_t NumNames)
{
    size_t i;

    for (i = 0; i < NumNames; i++)
    {
        if (Value == (Pairs + i)->Value)
        {
            return (Pairs + i)->Name;
		}
	}
    WhichFmtBuf++;
    WhichFmtBuf &= 3;
    return "unknown";
}

//==============================================================================
//
// Functions that format debugging output
//
//==============================================================================

MI_EXPORT const char* selectorflagstr(MI_Uint32 Flags)
{
    return FmtBits((unsigned int)Flags, SelectorFlagNames, sizeof (SelectorFlagNames) / sizeof (const char*));
}

MI_EXPORT const char* bitnumberstr(unsigned long Bits)
{
    return FmtBits((unsigned int)Bits, BitNumberNames, sizeof (BitNumberNames) / sizeof (const char*));
}

MI_EXPORT const char* mistrerror(MI_Result res)
{
#if defined CONFIG_ENABLE_WCHAR
    char buf[32];
    size_t i;

    ZChar* str = Result_ToString(res);
    for (i = 0; i < 31 && *(str + i) != '\0'; i++, str++)
        buf[i] = (char)*(str + i);
    buf[i] = '\0';
    return buf;
#else
    return Result_ToString(res);
#endif
}

MI_EXPORT const char* sslstrerror(unsigned long SslError)
{
    char* buf = FmtBuf[WhichFmtBuf];

    ERR_error_string_n(SslError, buf, 256);
    WhichFmtBuf++;
    WhichFmtBuf &= 3;
    return buf;
}

MI_EXPORT const char* notifyitemtypestr(int NotifyItemType)
{
    return FmtEnum((unsigned int)NotifyItemType, NotifyItemTypeNames, sizeof (NotifyItemTypeNames) / sizeof (NameValuePairs));
}

MI_EXPORT const char* clientstatusstr(int Status)
{
    return FmtEnum((unsigned int)Status, ClientStatusNames, sizeof (ClientStatusNames) / sizeof (NameValuePairs));
}

MI_EXPORT const char* messagetagnamestr(int Tag)
{
    return FmtEnum((unsigned int)Tag, MessageTagNames, sizeof (MessageTagNames) / sizeof (NameValuePairs));
}

MI_EXPORT const char* protocoleventnamestr(int Event)
{
    return FmtEnum((unsigned int)Event, ProtocolEventNames, sizeof (ProtocolEventNames) / sizeof (NameValuePairs));
}

MI_EXPORT const char* FmtTime(MI_Uint64 Time)
{
    char* TmBuf;
    unsigned long Sec;
    unsigned long uSec;
    unsigned long Min;
    unsigned long Hr;

    if (Time == 0)
    {
        return "None";
	}

    Sec = (unsigned long)(Time / 1000000);
    uSec = (unsigned long)(Time % 1000000);
    Min = Sec / 60;
    Sec -= Min * 60;
    Hr = Min / 60;
    Min -= Hr * 60;
    Hr %= 24;
    TmBuf = FmtBuf[WhichFmtBuf];
    sprintf(TmBuf, "%02lu:%02lu:%02lu.%03lu", Hr, Min, Sec, uSec / 1000);
    WhichFmtBuf++;
    WhichFmtBuf &= 3;
    return TmBuf;
}

MI_EXPORT const char* FmtInterval(MI_Sint64 Time)
{
    char* TmBufBase = FmtBuf[WhichFmtBuf];
    char* TmBuf = TmBufBase;
    unsigned long Sec;
    unsigned long uSec;
    unsigned long Min;
    unsigned long Hr;

    if (Time < 0)
    {
        *TmBuf++ = '-';
        Time = -Time;
	}
    Sec = (unsigned long)(Time / 1000000);
    uSec = (unsigned long)(Time % 1000000);
    Min = (unsigned long)Sec / 60;
    Sec -= Min * 60;
    Hr = Min / 60;
    Min -= Hr * 60;
    Hr %= 60;
    if (Hr != 0)
    {
        sprintf(TmBuf, "%02lu:%02lu:%02lu.%03lu", Hr, Min, Sec, uSec / 1000);
    }
    else if (Min != 0)
    {
        sprintf(TmBuf, "%02lu:%02lu.%03lu", Min, Sec, uSec / 1000);
	}
    else if (Sec == 0 && uSec == 0)
    {
        sprintf(TmBuf, "0.0");
	}
    else if (Sec != 0 || uSec >= 1000)
    {
        sprintf(TmBuf, "%lu.%03lu", Sec, uSec / 1000);
    }
    else
    {
        sprintf(TmBuf, "%lu.%06lu", Sec, uSec);
    }

    WhichFmtBuf++;
    WhichFmtBuf &= 3;
    return TmBufBase;
}
