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
#include <string.h>
#include "states.h"
#include "states.inc"

static void setUp()
{
}
static void cleanup()
{
}
typedef int (*FN)(const char* s, size_t n);
static void testAllStrings(FN f)
{
    UT_ASSERT((*f)("Alabama", 7) == STATE_Alabama);
    UT_ASSERT((*f)("Alaska", 6) == STATE_Alaska);
    UT_ASSERT((*f)("Arizona", 7) == STATE_Arizona);
    UT_ASSERT((*f)("Arkansas", 8) == STATE_Arkansas);
    UT_ASSERT((*f)("California", 10) == STATE_California);
    UT_ASSERT((*f)("Colorado", 8) == STATE_Colorado);
    UT_ASSERT((*f)("Connecticut", 11) == STATE_Connecticut);
    UT_ASSERT((*f)("Delaware", 8) == STATE_Delaware);
    UT_ASSERT((*f)("District of Columbia", 20) == STATE_District_of_Columbia);
    UT_ASSERT((*f)("Florida", 7) == STATE_Florida);
    UT_ASSERT((*f)("Georgia", 7) == STATE_Georgia);
    UT_ASSERT((*f)("Hawaii", 6) == STATE_Hawaii);
    UT_ASSERT((*f)("Idaho", 5) == STATE_Idaho);
    UT_ASSERT((*f)("Illinois", 8) == STATE_Illinois);
    UT_ASSERT((*f)("Indiana", 7) == STATE_Indiana);
    UT_ASSERT((*f)("Iowa", 4) == STATE_Iowa);
    UT_ASSERT((*f)("Kansas", 6) == STATE_Kansas);
    UT_ASSERT((*f)("Kentucky", 8) == STATE_Kentucky);
    UT_ASSERT((*f)("Louisiana", 9) == STATE_Louisiana);
    UT_ASSERT((*f)("Maine", 5) == STATE_Maine);
    UT_ASSERT((*f)("Maryland", 8) == STATE_Maryland);
    UT_ASSERT((*f)("Massachusetts", 13) == STATE_Massachusetts);
    UT_ASSERT((*f)("Michigan", 8) == STATE_Michigan);
    UT_ASSERT((*f)("Minnesota", 9) == STATE_Minnesota);
    UT_ASSERT((*f)("Mississippi", 11) == STATE_Mississippi);
    UT_ASSERT((*f)("Missouri", 8) == STATE_Missouri);
    UT_ASSERT((*f)("Montana", 7) == STATE_Montana);
    UT_ASSERT((*f)("Nebraska", 8) == STATE_Nebraska);
    UT_ASSERT((*f)("Nevada", 6) == STATE_Nevada);
    UT_ASSERT((*f)("New Hampshire", 13) == STATE_New_Hampshire);
    UT_ASSERT((*f)("New Jersey", 10) == STATE_New_Jersey);
    UT_ASSERT((*f)("New Mexico", 10) == STATE_New_Mexico);
    UT_ASSERT((*f)("New York", 8) == STATE_New_York);
    UT_ASSERT((*f)("North Carolina", 14) == STATE_North_Carolina);
    UT_ASSERT((*f)("North Dakota", 12) == STATE_North_Dakota);
    UT_ASSERT((*f)("Ohio", 4) == STATE_Ohio);
    UT_ASSERT((*f)("Oklahoma", 8) == STATE_Oklahoma);
    UT_ASSERT((*f)("Oregon", 6) == STATE_Oregon);
    UT_ASSERT((*f)("Pennsylvania", 12) == STATE_Pennsylvania);
    UT_ASSERT((*f)("Rhode Island", 12) == STATE_Rhode_Island);
    UT_ASSERT((*f)("South Carolina", 14) == STATE_South_Carolina);
    UT_ASSERT((*f)("South Dakota", 12) == STATE_South_Dakota);
    UT_ASSERT((*f)("Tennessee", 9) == STATE_Tennessee);
    UT_ASSERT((*f)("Texas", 5) == STATE_Texas);
    UT_ASSERT((*f)("Utah", 4) == STATE_Utah);
    UT_ASSERT((*f)("Vermont", 7) == STATE_Vermont);
    UT_ASSERT((*f)("Virginia", 8) == STATE_Virginia);
    UT_ASSERT((*f)("Washington", 10) == STATE_Washington);
    UT_ASSERT((*f)("West Virginia", 13) == STATE_West_Virginia);
    UT_ASSERT((*f)("Wisconsin", 9) == STATE_Wisconsin);
    UT_ASSERT((*f)("Wyoming", 7) == STATE_Wyoming);
    UT_ASSERT((*f)("*", 1) == 0);
    UT_ASSERT((*f)("**", 2) == 0);
    UT_ASSERT((*f)("***", 3) == 0);
    UT_ASSERT((*f)("****", 4) == 0);
    UT_ASSERT((*f)("*****", 5) == 0);
    UT_ASSERT((*f)("******", 6) == 0);
}

static void TestQuickStr()
{
    for(int i=0; i< 10000; i++) testAllStrings(QuickStr);
}

static void RunTests()
{
    UT_TEST(TestQuickStr);
}

UT_ENTRY_POINT(RunTests);
