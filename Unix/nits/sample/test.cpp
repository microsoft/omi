/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef HOOK_BUILD
    #define HOOK_BUILD
#endif

#ifdef _MSC_VER
    #include <windows.h>
#endif

#include <nits/base/nits.h>
#include <pal/palcommon.h>

extern "C" {
#include "Product.h"
}

using namespace TestSystem;

NitsTrapTable(MyTrap, 0)
    void (NITS_CALL *SampleFunc)(unsigned);
NitsEndTrapTable

void NITS_CALL originalFunc(unsigned x)
{
    if (x == 0)
        NitsTrace(PAL_T("Before mocking: NitsGetTrap called originalFunc"));
    else if (x == 1)
        NitsTrace(PAL_T("Before mocking: MyTrap.SampleFunc called originalFunc"));
    else if (x == 3)
        NitsTrace(PAL_T("After revert: MyTrap.SampleFunc called originalFunc"));
    else if (x == 4)
        NitsTrace(PAL_T("During mocking: mockFunc called originalFunc through NitsLastTrap"));
    else
    	NitsAssert(false, PAL_T("unexpected x value"));
}

void NITS_CALL mockFunc(unsigned x)
{
    if (x == 2)
        NitsTrace(PAL_T("During mocking: MyTrap.SampleFunc called mockFunc"));
    else
		NitsAssert(false, PAL_T("unexpected x value"));
    //Not yet implemented.
    //NitsLastTrap(MyTrap, SampleFunc)(4);
}

NitsTrapValue(MyTrap)
    originalFunc,
NitsEndTrapValue

TTEST(AuditTest)(ITest &test)
{
    PAL_UNUSED(test);

    int caseNumber = 2;
    DWORD error = MakeReports(L"MyCompany", caseNumber);
    NitsCompare(error, NO_ERROR, PAL_T("MakeReports should succeed"));

    error = BalanceBooks(L"MyCompany", caseNumber);
    NitsCompare(error, NO_ERROR, PAL_T("BalanceBooks should succeed"));

    //In a real product there would be additional validation.
#ifdef _MSC_VER
    PCSTR testDll = "NitsSample.dll";
#else
    PCSTR testDll = "libnitssample.so";
#endif

    NitsTrapHandle h = NitsOpenTrap(testDll, MyTrap);
    
    //Retrieves MyTrap.SampleFunc with an embedded version check.
    NitsGetTrap(h, MyTrap, SampleFunc)(0);

    //Direct call through the trap. Mockable product code does this.
    MyTrap.SampleFunc(1);

    //Changes the behavior of SampleFunc.
    //NOTE: Never change a table directly - it might be read-only memory!
    NitsSetTrap(h, MyTrap, SampleFunc, mockFunc);

    //Mockable product code calls again, but this time the path is different!
    MyTrap.SampleFunc(2);

    //Reverses the effect of NitsSetTrap.
    NitsCloseTrap(h);

    //Back to the behavior we saw before.
    MyTrap.SampleFunc(3);

    NitsCopyTrap(MyTrap, testDll, testDll);
}

NITS_EXTERN_C void Body(Switch &test)
{
    PAL_UNUSED(test);

    NitsTrace(PAL_T("trace test!"));
    NitsAssert(1 == 1, PAL_T("assert test!"));
    NitsCompare(1, 1, PAL_T("compare test!"));
    NitsCompareString(PAL_T("A"), PAL_T("A"), PAL_T("string test!"));
    NitsCompareSubstring(PAL_T("ABC"), PAL_T("B"), PAL_T("substring test!"));

    NitsCallSite s = TSITE(5);

    if (NitsShouldFault(s, NitsAutomatic))
    {
        NitsAssert(false, PAL_T("fault sim"));
    }
}

TGROUP(Group1)(Switch &test)
{
    PAL_UNUSED(test);

    NitsTrace(PAL_T("Group1!"));
}

TGROUP(Group2)(Switch &test)
{
    PAL_UNUSED(test);

    NitsTrace(PAL_T("Group2!"));
}

TGROUP(Group3)(Switch &test)
{
    PAL_UNUSED(test);

    NitsTrace(PAL_T("Group3!"));
}

TGROUP(Group4)(Switch &test)
{
    PAL_UNUSED(test);

    NitsTrace(PAL_T("Group4!"));
}

TCHOICE(ChoiceA)(Switch &test)
{
    PAL_UNUSED(test);

    NitsTrace(PAL_T("ChoiceA!"));
    test.Child(Group1);
    test.Child(Group2);
}

TCHOICE(ChoiceB)(Switch &test)
{
    PAL_UNUSED(test);

    NitsTrace(PAL_T("ChoiceB!"));
    test.Child(Group3);
}

TCHOICE(ChoiceC)(Switch &test)
{
    PAL_UNUSED(test);

    NitsTrace(PAL_T("ChoiceC!"));
    test.Child(Group3);
    test.Child(Group4);
}

TCHOICE(ChoiceD)(Switch &test)
{
    PAL_UNUSED(test);

    NitsTrace(PAL_T("ChoiceD!"));
    test.Child(ChoiceB);
    test.Child(ChoiceC);
}

void TestHelper(NitsCallSite site)
{
    NitsTraceEx(PAL_T("Helper function!"), site, NitsAutomatic);
}

TSETUP(ChoiceTest, Body)(Switch &test)
{
    PAL_UNUSED(test);

    NitsTrace(PAL_T("Setup!"));
    test.Child(ChoiceA);
    test.Child(ChoiceD);
}

TSET_ISOLATION(FailedAsserts);
TTEST(FailedAsserts)(Switch &test)
{
    PAL_UNUSED(test);

    NitsTrace(PAL_T("This test deliberately fails asserts."));
    NitsAssert(!true, PAL_T("assert should fail!"));
    NitsCompare(1, 2, PAL_T("compare should fail!"));
    NitsCompareString(PAL_T("A"), PAL_T("B"), PAL_T("compare should fail!"));
    NitsCompareSubstring(PAL_T("ABC"), PAL_T("D"), PAL_T("substring should fail!"));

    TestHelper(NitsHere());
}

