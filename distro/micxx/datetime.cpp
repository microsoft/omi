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

#include "datetime.h"
#include <base/strings.h>
#include <io/io.h>
#include <base/helpers.h>

#if defined(_MSC_VER)
# include <windows.h>
# include <time.h>
#else
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <time.h>
#endif

#define T MI_T

MI_BEGIN_NAMESPACE

static int _StrToU32(
    const MI_Char* s, 
    size_t offset, 
    size_t size, 
    MI_Uint32* x)
{
    MI_Char buf[64];
    MI_Char* end;

    if (size >= MI_COUNT(buf))
        return -1;

    memcpy(buf, &s[offset], size * sizeof(MI_Char));
    buf[size] = '\0';

    *x = (MI_Uint32)Ztoul(buf, &end, 10);

    if (*end != '\0')
        return -1;

    /* Success */
    return 0;
}

static bool _StrToDatetime(const MI_Char* s, MI_Datetime* x)
{
    if (Zlen(s) != 25)
        return false;

    memset(x, 0, sizeof(MI_Datetime));

    if (s[21] == '+' || s[21] == '-')
    {
        MI_Uint32 utc;

        /* It must be a timestamp (YYYYMMDDHHMMSS.MMMMMMSUTC) */
        if (_StrToU32(s, 0, 4, &x->u.timestamp.year) != 0 ||
            _StrToU32(s, 4, 2, &x->u.timestamp.month) != 0 ||
            _StrToU32(s, 6, 2, &x->u.timestamp.day) != 0 ||
            _StrToU32(s, 8, 2, &x->u.timestamp.hour) != 0 ||
            _StrToU32(s, 10, 2, &x->u.timestamp.minute) != 0 ||
            _StrToU32(s, 12, 2, &x->u.timestamp.second) != 0 ||
            s[14] != '.' ||
            _StrToU32(s, 15, 6, &x->u.timestamp.microseconds) != 0 ||
            _StrToU32(s, 22, 3, &utc) != 0)
        {
            return false;
        }

        if (s[21] == '+')
             x->u.timestamp.utc = (MI_Sint32)utc;
        else
             x->u.timestamp.utc = -(MI_Sint32)utc;

        x->isTimestamp = 1;
    }
    else if (s[21] == ':')
    {
        /* It must be an interval (DDDDDDDDHHMMSS.MMMMMM:000) */
        if (_StrToU32(s, 0, 8, &x->u.interval.days) != 0 ||
            _StrToU32(s, 8, 2, &x->u.interval.hours) != 0 ||
            _StrToU32(s, 10, 2, &x->u.interval.minutes) != 0 ||
            _StrToU32(s, 12, 2, &x->u.interval.seconds) != 0 ||
            s[14] != '.' ||
            _StrToU32(s, 15, 6, &x->u.interval.microseconds) != 0 ||
            s[22] != '0' || s[23] != '0' || s[24] != '0')
        {
            return false;
        }

        x->isTimestamp = 0;
    }
    else
    {
        return false;
    }

    return true;
}

static int _GetCurrentTimeInUsec(MI_Uint64& usec)
{
#if defined(_MSC_VER)
    FILETIME ft;
    ULARGE_INTEGER tmp;

    GetSystemTimeAsFileTime(&ft);
    tmp.u.LowPart = ft.dwLowDateTime;
    tmp.u.HighPart = ft.dwHighDateTime;
    tmp.QuadPart -= 0X19DB1DED53E8000;
    usec = tmp.QuadPart / (UINT64)10;

    return 0;
#else
    struct timeval tv;
    struct timezone tz;
    memset(&tv, 0, sizeof(tv));
    memset(&tz, 0, sizeof(tz));

    if (gettimeofday(&tv, &tz) != 0)
        return -1;

    usec = (MI_Uint64)tv.tv_sec * (MI_Uint64)1000000 + (MI_Uint64)tv.tv_usec;
    return 0;
#endif
}

Datetime::Datetime(
    MI_Uint32 year,
    MI_Uint32 month,
    MI_Uint32 day,
    MI_Uint32 hour,
    MI_Uint32 minute,
    MI_Uint32 second,
    MI_Uint32 microseconds,
    MI_Sint32 utc)
{
    _rep.isTimestamp = MI_TRUE;
    _rep.u.timestamp.year = year;
    _rep.u.timestamp.month = month;
    _rep.u.timestamp.day = day;
    _rep.u.timestamp.hour = hour;
    _rep.u.timestamp.minute = minute;
    _rep.u.timestamp.second = second;
    _rep.u.timestamp.microseconds = microseconds;
    _rep.u.timestamp.utc = utc;
}

Datetime::Datetime(
    MI_Uint32 days,
    MI_Uint32 hours,
    MI_Uint32 minutes,
    MI_Uint32 seconds,
    MI_Uint32 microseconds)
{
    _rep.isTimestamp = MI_FALSE;
    _rep.u.interval.days = days;
    _rep.u.interval.hours = hours;
    _rep.u.interval.minutes = minutes;
    _rep.u.interval.seconds = seconds;
    _rep.u.interval.microseconds = microseconds;
}

bool Datetime::Set(
    MI_Uint32 year,
    MI_Uint32 month,
    MI_Uint32 day,
    MI_Uint32 hour,
    MI_Uint32 minute,
    MI_Uint32 second,
    MI_Uint32 microseconds,
    MI_Sint32 utc)
{
    // ATTN: check ranges!
    _rep.isTimestamp = MI_TRUE;
    _rep.u.timestamp.year = year;
    _rep.u.timestamp.month = month;
    _rep.u.timestamp.day = day;
    _rep.u.timestamp.hour = hour;
    _rep.u.timestamp.minute = minute;
    _rep.u.timestamp.second = second;
    _rep.u.timestamp.microseconds = microseconds;
    _rep.u.timestamp.utc = utc;
    return true;
}

bool Datetime::Set(
    MI_Uint32 days,
    MI_Uint32 hours,
    MI_Uint32 minutes,
    MI_Uint32 seconds,
    MI_Uint32 microseconds)
{
    // ATTN: check ranges!
    _rep.isTimestamp = MI_FALSE;
    _rep.u.interval.days = days;
    _rep.u.interval.hours = hours;
    _rep.u.interval.minutes = minutes;
    _rep.u.interval.seconds = seconds;
    _rep.u.interval.microseconds = microseconds;

    return 0;
}

bool Datetime::Set(const MI_Char* str)
{
    if (!_StrToDatetime(str, &_rep))
    {
        Clear();
        return false;
    }

    return true;
}

bool Datetime::Get(
    MI_Uint32& year,
    MI_Uint32& month,
    MI_Uint32& day,
    MI_Uint32& hour,
    MI_Uint32& minute,
    MI_Uint32& second,
    MI_Uint32& microseconds,
    MI_Sint32& utc) const
{
    if (!_rep.isTimestamp)
        return false;

    year = _rep.u.timestamp.year;
    month = _rep.u.timestamp.month;
    day = _rep.u.timestamp.day;
    hour = _rep.u.timestamp.hour;
    minute = _rep.u.timestamp.minute;
    second = _rep.u.timestamp.second;
    microseconds = _rep.u.timestamp.microseconds;
    utc = _rep.u.timestamp.utc;

    return true;
}

bool Datetime::Get(
    MI_Uint32& days,
    MI_Uint32& hours,
    MI_Uint32& minutes,
    MI_Uint32& seconds,
    MI_Uint32& microseconds) const
{
    if (_rep.isTimestamp)
        return false;

    days = _rep.u.interval.days;
    hours = _rep.u.interval.hours;
    minutes = _rep.u.interval.minutes;
    seconds = _rep.u.interval.seconds;
    microseconds = _rep.u.interval.microseconds;

    return true;
}

void Datetime::ToString(MI_Char buffer[26]) const
{
    const MI_Datetime* p = (const MI_Datetime*)&_rep;
    DatetimeToStr(p, buffer);
}

bool Datetime::Equal(const Datetime& x) const
{
    if (_rep.isTimestamp)
    {
        return x._rep.isTimestamp &&
            _rep.u.timestamp.year == x._rep.u.timestamp.year &&
            _rep.u.timestamp.month == x._rep.u.timestamp.month &&
            _rep.u.timestamp.day == x._rep.u.timestamp.day &&
            _rep.u.timestamp.hour == x._rep.u.timestamp.hour &&
            _rep.u.timestamp.minute == x._rep.u.timestamp.minute &&
            _rep.u.timestamp.second == x._rep.u.timestamp.second &&
            _rep.u.timestamp.microseconds == x._rep.u.timestamp.microseconds &&
            _rep.u.timestamp.utc == x._rep.u.timestamp.utc;
    }
    else
    {
        return !x._rep.isTimestamp &&
            _rep.u.interval.days == x._rep.u.interval.days &&
            _rep.u.interval.hours == x._rep.u.interval.hours &&
            _rep.u.interval.minutes == x._rep.u.interval.minutes &&
            _rep.u.interval.seconds == x._rep.u.interval.seconds &&
            _rep.u.interval.microseconds == x._rep.u.interval.microseconds;
    }
}

void Datetime::Print(FILE* os) const
{
    MI_Char buffer[26];
    ToString(buffer);
    Fzprintf(os, T("%Z"), zcs(buffer));
}

#define TIMESTAMP_SIZE 128

bool Datetime::SetCurrent()
{
    /* ATTN: get UTC offset */
    MI_Uint64 usec;

    if (_GetCurrentTimeInUsec(usec) != 0)
        return false;

    MI_Uint32 year;
    MI_Uint32 month;
    MI_Uint32 day;
    MI_Uint32 hour;
    MI_Uint32 minute;
    MI_Uint32 second;
    MI_Uint32 microseconds = 0;
    MI_Sint32 utc = 0;

#if defined(_MSC_VER)
    {
        time_t t = usec / 1000000;
        struct tm tm;
        localtime_s(&tm, &t);
        year = tm.tm_year + 1900;
        month = tm.tm_mon + 1;
        day = tm.tm_mday;
        hour = tm.tm_hour;
        minute = tm.tm_min;
        second = tm.tm_sec;
        microseconds = (MI_Uint32)(usec % MI_Uint64(1000000));
    }
#else
    {
        time_t t = usec / 1000000;
        struct tm tm;
        localtime_r(&t, &tm);
        year = tm.tm_year + 1900;
        month = tm.tm_mon + 1;
        day = tm.tm_mday;
        hour = tm.tm_hour;
        minute = tm.tm_min;
        second = tm.tm_sec;
        microseconds = (MI_Uint32)(usec % MI_Uint64(1000000));
    }
#endif

    return Set(year, month, day, hour, minute, second, microseconds, utc);
}

Datetime Datetime::Now()
{
    Datetime result;
    result.SetCurrent();
    return result;
}

MI_END_NAMESPACE
