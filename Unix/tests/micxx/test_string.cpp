/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <ut/ut.h>
#include "../../micxx/micxx_string.h"
#include "../../common/common.h"
#include <pal/strings.h>

using namespace mi;

namespace tt {
static void setUp4()
{
    char* p = (char*) PAL_Malloc(90);
    PAL_Free(p);
}
}


NitsSetup(TestStringSetup)
{
    tt::setUp4();
}
NitsEndSetup

NitsCleanup(TestStringSetup)
NitsEndCleanup


NitsTestWithSetup(TestStringCtor, TestStringSetup)
{
    String s1(MI_T("string1"));

    UT_ASSERT( Tcscmp(s1.Str(), MI_T("string1")) == 0);

    // reset value
    s1 = 0;
    UT_ASSERT( Tcscmp(s1.Str(), MI_T("string1")) != 0);
    UT_ASSERT( Tcscmp(s1.Str(), MI_T("")) == 0);
}
NitsEndTest

NitsTestWithSetup(TestCharWithSizeCtor, TestStringSetup)
{
    String s1(MI_T("string1"), 3);

    UT_ASSERT( Tcscmp(s1.Str(), MI_T("str")) == 0);
    UT_ASSERT(s1.GetSize() == 3);
    UT_ASSERT(s1 == MI_T("str"));
}
NitsEndTest

NitsTestWithSetup(TestCharWithZeroSizeCtor, TestStringSetup)
{
    String s1(MI_T("string1"), 0);

    UT_ASSERT( Tcscmp(s1.Str(), MI_T("")) == 0);
    UT_ASSERT(s1.GetSize() == 0);
    UT_ASSERT(s1 == MI_T(""));
}
NitsEndTest

NitsTestWithSetup(TestNullCharWithZeroSizeCtor, TestStringSetup)
{
    String s1(0, 0);

    UT_ASSERT( Tcscmp(s1.Str(), MI_T("")) == 0);
    UT_ASSERT(s1.GetSize() == 0);
    UT_ASSERT(s1 == MI_T(""));
}
NitsEndTest

NitsTestWithSetup(TestCopyCtor, TestStringSetup)
{
    String s1(MI_T("str1"));
    String s2 = s1;
    String s3(s1);
    String s4;  s4 = s1;

    // all strings has to be identical and point to the same memory block
    UT_ASSERT( Tcscmp(s1.Str(), MI_T("str1")) == 0);
    UT_ASSERT( s1 == s2 );
    UT_ASSERT( s1 == s3 );
    UT_ASSERT( s1 == s4 );

    UT_ASSERT( s1.Str() == s2.Str() );
    UT_ASSERT( s1.Str() == s3.Str() );
    UT_ASSERT( s1.Str() == s4.Str() );

}
NitsEndTest

NitsTestWithSetup(TestAssignmentToSelf, TestStringSetup)
{
    String s1;

    s1 = s1;
    UT_ASSERT( s1 == MI_T("") );

    s1 = MI_T("*");
    s1 = s1;
    UT_ASSERT( s1 == MI_T("*") );
    
}
NitsEndTest

NitsTestWithSetup(TestRefCounting, TestStringSetup)
{
    String s1(MI_T("str1"));
    String s2 = s1;
    String s3(s1);
    String s4;  s4 = s1;

    // assign the same string again - should re-allocate string, but keep contetn the same
    s1 = MI_T("str1");

    UT_ASSERT( s1 == s2 );
    UT_ASSERT( s1 == s3 );
    UT_ASSERT( s1 == s4 );

    UT_ASSERT(s1.Str() != s2.Str());
    UT_ASSERT(s2.Str() == s3.Str());
    UT_ASSERT(s2.Str() == s4.Str());
}
NitsEndTest

NitsTestWithSetup(TestComparison, TestStringSetup)
{
    // compare == / !=
    String s1 = MI_T("s1");

    // compare to self
    UT_ASSERT( s1 == s1 );
    // even null
    String s_null;

    UT_ASSERT( s_null == s_null );

    String s2 = MI_T("s_2");

    UT_ASSERT( s1 != s2 );

    s2 = MI_T("s1");

    UT_ASSERT(s1 == s2 );


    UT_ASSERT( s1 == MI_T("s1") );
    UT_ASSERT( s1 != MI_T("something else") );
}
NitsEndTest

NitsTestWithSetup(TestComparisonOfEmptyStrings, TestStringSetup)
{
    String s_null, s_empty = MI_T(""), s_not_empty = MI_T("123");

    // compare to self
    UT_ASSERT( s_null == s_null );
    UT_ASSERT( s_empty == s_empty );
    UT_ASSERT( s_not_empty == s_not_empty );

    // compare null
    UT_ASSERT( s_null == s_empty );
    UT_ASSERT( s_null != s_not_empty );

    // compare empty
    UT_ASSERT( s_empty != s_not_empty );

    // compare to char*
    UT_ASSERT( s_null == MI_T("") );
    UT_ASSERT( s_empty == MI_T("") );
    UT_ASSERT( s_not_empty == MI_T("123") );

}
NitsEndTest

NitsTestWithSetup(TestGetSize, TestStringSetup)
{
    String s;

    UT_ASSERT( s.GetSize() == 0 );

    s = MI_T("123");

    UT_ASSERT( s.GetSize() == 3 );
}
NitsEndTest

NitsTestWithSetup(TestConcatString, TestStringSetup)
{
    String s;

    UT_ASSERT( s == MI_T("") );

    s += MI_T("1");
    UT_ASSERT( s == MI_T("1") );
    UT_ASSERT( s.GetSize() == 1 );

    s += String(MI_T("4"));
    UT_ASSERT( s == MI_T("14") );
    UT_ASSERT( s.GetSize() == 2 );
}
NitsEndTest

NitsTestWithSetup(TestConcatStringRefCounter, TestStringSetup)
{
    // check that ref-counter works properly with += operator

    String source1 = MI_T("source");
    String source2 = MI_T("*");

    String target = source2;

    // they point to the same buffer 
    UT_ASSERT( target == source2 );
    UT_ASSERT( target.Str() == source2.Str() );

    const ZChar* source2_p = source2.Str();

    target += source1;
    UT_ASSERT( target == MI_T("*source") );
    UT_ASSERT( target.Str() != source2.Str() );
    UT_ASSERT( source2_p == source2.Str() );
    UT_ASSERT( source2 == MI_T("*") );
}
NitsEndTest

NitsTestWithSetup(TestConcatStringEmptyString, TestStringSetup)
{
    String s1,s2;

    s1 += String(MI_T("1"));
    UT_ASSERT(s1 == MI_T("1"));
    s1 += String(MI_T("234567890123456"));
    UT_ASSERT(s1 == MI_T("1234567890123456"));
    UT_ASSERT(s1.GetSize() == 16);
    s1 += String();
    UT_ASSERT(s1 == MI_T("1234567890123456"));
    UT_ASSERT(s1.GetSize() == 16);

    s2 += MI_T("1");
    UT_ASSERT(s2 == MI_T("1"));
    s2 += MI_T("234567890123456");
    UT_ASSERT(s2 == MI_T("1234567890123456"));
    UT_ASSERT(s2.GetSize() == 16);
    s2 += MI_T("");
    UT_ASSERT(s2 == MI_T("1234567890123456"));
    UT_ASSERT(s2.GetSize() == 16);

    const ZChar* null_str = 0;
    s2 += null_str;
    UT_ASSERT(s2 == MI_T("1234567890123456"));
    UT_ASSERT(s2.GetSize() == 16);
}
NitsEndTest



