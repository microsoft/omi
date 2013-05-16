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

#include <ut/ut.h>
#include <micxx/datetime.h>
#include <base/strings.h>
#include <common.h>

using namespace mi;

static void setUp()
{
}

static void cleanup()
{
}


static void TestTimestamp()
{
    /* YYYYMMDDHHMMSS.MMMMMMSUTC */
    const ZChar STR[] = ZT("20101225123011.123456-360");
    ZChar buffer[26];

    Datetime dt;
    UT_ASSERT(dt.Set(STR) == true);
    UT_ASSERT(dt.IsTimestamp() == true);


    MI_Uint32 year;
    MI_Uint32 month;
    MI_Uint32 day;
    MI_Uint32 hour;
    MI_Uint32 minute;
    MI_Uint32 second;
    MI_Uint32 microseconds;
    MI_Sint32 utc;
    bool f = dt.Get(year, month, day, hour, minute, second, microseconds, utc);

    UT_ASSERT(f == true);
    UT_ASSERT(year == 2010);
    UT_ASSERT(month == 12);
    UT_ASSERT(day == 25);
    UT_ASSERT(hour == 12);
    UT_ASSERT(minute == 30);
    UT_ASSERT(second == 11);
    UT_ASSERT(microseconds == 123456);
    UT_ASSERT(utc == -360);

    dt.ToString(buffer);
    UT_ASSERT(Zcmp(STR, buffer) == 0);

    Datetime dt2;
    dt2.Set(year, month, day, hour, minute, second, microseconds, utc);
    dt2.ToString(buffer);
    UT_ASSERT(Zcmp(STR, buffer) == 0);
    UT_ASSERT(dt == dt2);

    Datetime dt3(year, month, day, hour, minute, second, microseconds, utc);
    UT_ASSERT(dt == dt3);
}

static void TestInterval()
{
    /* DDDDDDDDHHMMSS.MMMMMM:000 */
    const ZChar STR[] = ZT("12345678151617.123456:000");
    ZChar buffer[26];

    Datetime dt;
    UT_ASSERT(dt.Set(STR) == true);
    UT_ASSERT(dt.IsTimestamp() == false);

    MI_Uint32 days;
    MI_Uint32 hours;
    MI_Uint32 minutes;
    MI_Uint32 seconds;
    MI_Uint32 microseconds;
    bool f = dt.Get(days, hours, minutes, seconds, microseconds);
    UT_ASSERT(f == true);

    UT_ASSERT(days == 12345678);
    UT_ASSERT(hours == 15);
    UT_ASSERT(minutes == 16);
    UT_ASSERT(seconds == 17);
    UT_ASSERT(microseconds == 123456);

    dt.ToString(buffer);
    UT_ASSERT(Zcmp(STR, buffer) == 0);

    Datetime dt2;
    dt2.Set(days, hours, minutes, seconds, microseconds);
    dt2.ToString(buffer);
    UT_ASSERT(Zcmp(STR, buffer) == 0);
    UT_ASSERT(dt == dt2);

    Datetime dt3(days, hours, minutes, seconds, microseconds);
    UT_ASSERT(dt == dt3);

    Datetime dt4;
    dt4 = dt3;
    UT_ASSERT(dt3 == dt4);
}

static void TestCurrent()
{
    Datetime x;
    UT_ASSERT(x.SetCurrent() == true);
}

static void RunTests()
{
    UT_TEST(TestTimestamp);
    UT_TEST(TestInterval);
    UT_TEST(TestCurrent);
}

UT_ENTRY_POINT(RunTests);
