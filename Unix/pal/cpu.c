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

#include "cpu.h"

_Success_(return == 0)
int CPU_GetLocalTimestamp(
    _Out_ PAL_Datetime* current)
{
#ifdef _MSC_VER
    SYSTEMTIME st;
    TIME_ZONE_INFORMATION zone;
    DWORD tz;

    GetLocalTime(&st);
    tz = GetTimeZoneInformation(&zone);
    if (tz == TIME_ZONE_ID_INVALID)
        return -1;

    current->isTimestamp = PAL_TRUE;
    /* TODO: Valid year ranges for SYSTEMTIME and MI_Timestamp are different! */
    // this is probably not a big problem for actual time.The range of SystemTime.wYear (1601-30827) is not a subset of 
    // MI_Timestamp.year (0-9999 according to DMTF + verified by asserts in Mint + assumed in various integer overflow 
    // considerations for arithmetic/comparison built-ins)
    current->u.timestamp.year = st.wYear;
    current->u.timestamp.month = st.wMonth;
    current->u.timestamp.day = st.wDay;
    current->u.timestamp.hour = st.wHour;
    current->u.timestamp.minute = st.wMinute;
    current->u.timestamp.second = st.wSecond;
    current->u.timestamp.microseconds = st.wMilliseconds * 1000;
    current->u.timestamp.utc = -zone.Bias;

    if (tz == TIME_ZONE_ID_DAYLIGHT)
        current->u.timestamp.utc -= zone.DaylightBias;
    else
        current->u.timestamp.utc -= zone.StandardBias;

    return 0;
#else
    struct timeval tv;
    struct tm tm;

    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec, &tm);

    current->isTimestamp = PAL_TRUE;
    current->u.timestamp.year = 1900 + tm.tm_year; // tm.tm_year is the number of years since 1900.
    current->u.timestamp.month = tm.tm_mon + 1; // tm.tm_mon is the number of months since January, in the range 0 to 11.
    current->u.timestamp.day = tm.tm_mday;
    current->u.timestamp.hour = tm.tm_hour;
    current->u.timestamp.minute = tm.tm_min;
    current->u.timestamp.second = tm.tm_sec;
    current->u.timestamp.microseconds = tv.tv_usec;
    current->u.timestamp.utc = -timezone / 60;
    return 0;
#endif
}

_Success_(return == 0)
int CPU_GetUtcTimestamp(
    _Out_ PAL_Datetime* current)
{
#ifdef _MSC_VER
    SYSTEMTIME st;

    GetSystemTime(&st);

    current->isTimestamp = PAL_TRUE;
    /* TODO: Valid year ranges for SYSTEMTIME and MI_Timestamp are different! */
    // this is probably not a big problem for actual time.The range of SystemTime.wYear (1601-30827) is not a subset of 
    // MI_Timestamp.year (0-9999 according to DMTF + verified by asserts in Mint + assumed in various integer overflow 
    // considerations for arithmetic/comparison built-ins)
    current->u.timestamp.year = st.wYear;
    current->u.timestamp.month = st.wMonth;
    current->u.timestamp.day = st.wDay;
    current->u.timestamp.hour = st.wHour;
    current->u.timestamp.minute = st.wMinute;
    current->u.timestamp.second = st.wSecond;
    current->u.timestamp.microseconds = st.wMilliseconds * 1000;
    current->u.timestamp.utc = 0;
    return 0;
#else
    struct timeval tv;
    struct tm tm;

    gettimeofday(&tv, NULL);
    gmtime_r(&tv.tv_sec, &tm);

    current->isTimestamp = PAL_TRUE;
    current->u.timestamp.year = tm.tm_year;
    current->u.timestamp.month = tm.tm_mon + 1; // tm.tm_mon is the number of months since January, in the range 0 to 11.
    current->u.timestamp.day = tm.tm_mday;
    current->u.timestamp.hour = tm.tm_hour;
    current->u.timestamp.minute = tm.tm_min;
    current->u.timestamp.second = tm.tm_sec;
    current->u.timestamp.microseconds = tv.tv_usec;
    current->u.timestamp.utc = 0;
    return 0;
#endif
}

