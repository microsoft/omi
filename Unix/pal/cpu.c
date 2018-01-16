/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <sys/time.h>
#include "cpu.h"

_Success_(return == 0)
int CPU_GetLocalTimestamp(
    _Out_ PAL_Datetime* current)
{
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
}

_Success_(return == 0)
int CPU_GetUtcTimestamp(
    _Out_ PAL_Datetime* current)
{
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
}

