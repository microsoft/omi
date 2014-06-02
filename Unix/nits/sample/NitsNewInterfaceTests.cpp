#include "NitsNewInterfaceTests.h"

NitsDefSetup0(Fixture0, MyStruct)
    NitsTrace(PAL_T("Fixture0 being run"));
    NitsContext()->_MyStruct->x = 0;
    NitsContext()->_MyStruct->p = 0;
NitsEndSetup
    
NitsCleanup(Fixture0)
    NitsTrace(PAL_T("Cleanup of Fixture0 being run"));
    NitsContext()->_MyStruct->x = 0;
NitsEndCleanup

NitsCrash(Fixture0)
    NitsContext()->_MyStruct->x = 0;
NitsEndCrash

NitsSetup(SimpleSetup)
NitsEndSetup

NitsTestSetIsolation(SimpleBody)
NitsTestSetTimeout(SimpleBody, 900)
NitsTest(SimpleBody)
    NitsTrace(PAL_T("SimpleBody being run"));
    NitsAssert(true, PAL_T("test passed"));          
NitsEndTest

NitsTestWithSetup(BodyWithSimpleSetup, SimpleSetup)
    NitsTrace(PAL_T("BodyWithSimpleSetup being run"));
    NitsAssert(true, PAL_T("test passed"));          
NitsEndTest

NitsSetup0(Fixture1, MyStruct)
    NitsContext()->_MyStruct->x = 0;
    NitsContext()->_MyStruct->p = 0;
NitsEndSetup




struct MyStruct sFixture2 = {9, 0};

NitsDefSetup1(Fixture2, MyStruct2, Fixture0, sFixture2)
    NitsContext()->_MyStruct2->c = 0;
    NitsContext()->_MyStruct2->d = 0;

	// doing initialization directly; this way we will potentially have this following code pasted in several tests
    NitsContext()->_Fixture0->_MyStruct->x = 0;
    NitsContext()->_Fixture0->_MyStruct->p = 0;
NitsEndSetup



struct MyStruct sFixture4 = {12, 0};

NitsDefSetup1(Fixture4, MyStruct2, Fixture0, sFixture4)
    NitsContext()->_MyStruct2->c = 0;
    NitsContext()->_MyStruct2->d = 0;

    NitsContext()->_Fixture0->_MyStruct->x = 0;
    NitsContext()->_Fixture0->_MyStruct->p = 0;
NitsEndSetup

struct MyStruct sFixture3 = {3, 0};


NitsDefSplit2(Fixture3, MyStruct,
           Fixture0,
           Fixture1)
    // convenient way of accessing currently selected choice
    NitsContext()->_MyStruct->x = 0;
    NitsContext()->_MyStruct->p = 0;

    // you could do it this way too
    NitsContext()->_Fixture0->_MyStruct->x = 0;
    NitsContext()->_Fixture0->_MyStruct->p = 0;

    NitsContext()->_Fixture1->_MyStruct->x = 0;
    NitsContext()->_Fixture1->_MyStruct->p = 0;
NitsEndSetup


struct FirstTest
{
    int x;
};

NitsTest0(FirstTestWithNewInterface)
    NitsTrace(PAL_T("FirstTestWithNewInterface being run"));
    NitsAssert(true, PAL_T("test passed"));
NitsEndTest


NitsTest(BodyOnlyTest)
    NitsTrace(PAL_T("BodyOnlyTest being run"));
    NitsAssert(true, PAL_T("test passed"));
NitsEndTest

NitsSetup(MySetup1)
    NitsTrace(PAL_T("MySetup1 being run"));
NitsEndSetup

NitsCleanup(MySetup1)
    PAL_UNUSED(NitsContext());
    NitsTrace(PAL_T("Cleanup for MySetup1 being run"));
NitsEndCleanup

NitsCleanup(MySetup2)
    PAL_UNUSED(NitsContext());

    NitsTrace(PAL_T("Cleanup for MySetup2 being run"));
NitsEndCleanup


NitsSplit2(SetupWithTwoParentsSplit, NitsEmptyStruct, 
           MySetup1, MySetup2)
    NitsTrace(PAL_T("SetupWithTwoParentsSplit being run"));
NitsEndSetup

NitsCleanup(SetupWithTwoParentsSplit)
    PAL_UNUSED(NitsContext());

    NitsTrace(PAL_T("Cleanup for SetupWithTwoParentsSplit being run"));
NitsEndCleanup


NitsTest1(BodyWithSplitParent, SetupWithTwoParentsSplit, NitsEmptyValue)
    NitsTrace(PAL_T("BodyWithSplitParent being run"));
    NitsAssert(true, PAL_T("test passed"));
NitsEndTest


NitsTestWithSetup(BodyWithSetup, MySetup1)
    NitsTrace(PAL_T("BodyWithSetup being run"));
    NitsAssert(true, PAL_T("test passed"));
NitsEndTest

NitsTest2(BodyWithTwoParents, MySetup1, NitsEmptyValue, MySetup2, NitsEmptyValue)
    NitsTrace(PAL_T("BodyWithSetup being run"));
    NitsAssert(true, PAL_T("test passed"));
NitsEndTest

NitsCleanup(BodyWithSplitParent)
    PAL_UNUSED(NitsContext());

    NitsTrace(PAL_T("Cleanup for BodyWithSplitParent being run"));
NitsEndCleanup

NitsSetup(P1_1)
    NitsTrace(PAL_T("P1_1 being run"));
NitsEndSetup

NitsSetup(P1_2)
    NitsTrace(PAL_T("P1_2 being run"));
NitsEndSetup

NitsSetup2(P1, NitsEmptyStruct, 
           P1_1, NitsEmptyValue,
           P1_2, NitsEmptyValue)
   NitsTrace(PAL_T("P1 being run"));
NitsEndSetup

NitsSetup(P2_1)
    NitsTrace(PAL_T("P2_1 being run"));
NitsEndSetup

NitsSetup1(P2, NitsEmptyStruct,
           P2_1, NitsEmptyValue)
   NitsTrace(PAL_T("P2 being run"));
NitsEndSetup

NitsTest2(T1,
          P1, NitsEmptyValue,
          P2, NitsEmptyValue)
   NitsTrace(PAL_T("T1 being run"));
   NitsAssert(true, PAL_T("test passed"));
NitsEndTest

NitsSplit2(Split_P1_P2, NitsEmptyStruct, 
          P1, P2)

    NitsTrace(PAL_T("Split_P1_P2 being run"));
NitsEndSplit

NitsTest1(T2,
          Split_P1_P2, NitsEmptyValue)
   NitsTrace(PAL_T("T2 being run"));
   NitsAssert(true, PAL_T("test passed"));
NitsEndTest

NitsSetup(C1_1)
    NitsTrace(PAL_T("C1_1 being run"));
NitsEndSetup

NitsCleanup(C1_1)
    PAL_UNUSED(NitsContext());

    NitsTrace(PAL_T("Cleanup of C1_1 being run"));
NitsEndCleanup

NitsSetup(C1_2)
    NitsTrace(PAL_T("C1_2 being run"));
NitsEndSetup


NitsSplit2(C1, NitsEmptyStruct, 
           C1_1,
           C1_2)           
   NitsTrace(PAL_T("C1 being run"));
NitsEndSplit

NitsCleanup(C1)
    PAL_UNUSED(NitsContext());
    NitsTrace(PAL_T("Cleanup of C1 being run"));
NitsEndCleanup

NitsSetup(D1_1)
    if(NitsIsFixtureSelected(C1_1))
        NitsOmitAndReturn;
    NitsTrace(PAL_T("D1_1 being run"));
NitsEndSetup

NitsCleanup(D1_1)
    PAL_UNUSED(NitsContext());

    NitsTrace(PAL_T("Cleanup of D1_1 being run"));
NitsEndCleanup

NitsSetup(D1_2)
    NitsTrace(PAL_T("D1_2 being run"));
NitsEndSetup


NitsSplit2(D1, NitsEmptyStruct, 
           D1_1,
           D1_2)
   NitsTrace(PAL_T("D1 being run"));
NitsEndSplit

NitsCleanup(D1)
    PAL_UNUSED(NitsContext());

    NitsTrace(PAL_T("Cleanup of D1 being run"));
NitsEndCleanup

NitsTest2(TC1D1,
          C1, NitsEmptyValue,
          D1, NitsEmptyValue)
 NitsTrace(PAL_T("TC1D1 being run"));
 NitsAssert(true, PAL_T("test passed"));
NitsEndTest

NitsCleanup(TC1D1)
    PAL_UNUSED(NitsContext());

    NitsTrace(PAL_T("Cleanup of TC1D1 being run"));
NitsEndCleanup

NitsSetup1(MySetup1C1, NitsEmptyStruct,
           MySetup1, NitsEmptyValue)
    NitsTrace(PAL_T("MySetup1C1 being run"));
NitsEndSetup

NitsSetup1(MySetup1C2, NitsEmptyStruct,
           MySetup1, NitsEmptyValue)
    NitsTrace(PAL_T("MySetup1C2 being run"));
NitsEndSetup

NitsTest2(VITest1, 
          MySetup1C1, NitsEmptyValue,
          MySetup1C2, NitsEmptyValue)
    NitsTrace(PAL_T("VITest1 being run"));
    NitsAssert(true, PAL_T("test passed"));          
NitsEndTest

// DEMO Test

struct MyContext
{
    char *bom;
    int length;
};

char *currentBom = 0;


void SetBom(_In_reads_(length) char *bom, int length)
{
    PAL_UNUSED(length);

    currentBom = bom;
}

int DecodeData(_In_reads_(length) char *someData, int length)
{
    PAL_UNUSED(someData);
    PAL_UNUSED(length);

    // do the decoding 
    // when successful return 1
    return 1;
}

void PrintBom(_In_reads_(length) char *bom, int length)
{
    int count = 0;

    if(!bom || (length == 0))
        return;
    
    while((count < length) && bom[count] != 0)
    {
        // code to print each char
        count++;
    }

    if(count == 3)
    {
        NitsTrace(PAL_T("BOM is 123"));
    }
    else if(count == 2)
    {
        NitsTrace(PAL_T("BOM is 45"));
    }
}

NitsSetup0(UTF8, MyContext)
    char temp[] = {1, 2, 3, 0};
    NitsContext()->_MyContext->bom = temp;
    NitsContext()->_MyContext->length = 4;
    NitsTrace(PAL_T("Running UTF8"));
NitsEndSetup
    
NitsSetup0(UTF16, MyContext)
    char temp[] = {4, 5, 0};
    NitsContext()->_MyContext->bom = temp;
    NitsContext()->_MyContext->length = 3;    
    NitsTrace(PAL_T("Running UTF16"));    
NitsEndSetup
    
NitsSplit2(Encodings, MyContext, UTF8, UTF16)
    NitsTrace(PAL_T("Running Encodings"));
    PrintBom(NitsContext()->_MyContext->bom, NitsContext()->_MyContext->length);
NitsEndSplit
    
NitsTest1(DecoderTest,
        Encodings, EncodingsDefaults)
    int x = 0;
    char someData[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    NitsTrace(PAL_T("Running DecoderTest"));
    PrintBom(NitsContext()->_Encodings->_MyContext->bom, NitsContext()->_Encodings->_MyContext->length);
    SetBom(NitsContext()->_Encodings->_MyContext->bom, NitsContext()->_Encodings->_MyContext->length);
    x = DecodeData(someData, 10);
    NitsAssert(x, PAL_T("Foo failed"));
NitsEndTest

void FaultSimHelper1()
{
    char *mem1 = (char *)SystemMalloc(10);
    char *mem2 = (char *)SystemMalloc(15);

    // faulting on mem1 alloc
    if(NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        NitsAssert(false, PAL_T("mem1 alloc failed"));
    }

    if(mem1)
        SystemFree(mem1);

    // faulting on mem2 alloc
    if(NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        NitsAssert(false, PAL_T("mem2 alloc failed"));
    }

    if(mem2)
        SystemFree(mem2);
}
void FaultSimHelper()
{
    char *mem1 = (char *)SystemMalloc(10);
    char *mem2 = (char *)SystemMalloc(15);
    char *mem3 = (char *)SystemMalloc(20);
	char *mem4 = (char *)SystemMalloc(25);

    // faulting on mem1 alloc
    if(NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        NitsAssert(false, PAL_T("mem1 alloc failed"));
    }

    if(mem1)
        SystemFree(mem1);

    // faulting on mem2 alloc
    if(NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        NitsAssert(false, PAL_T("mem2 alloc failed"));
    }

    if(mem2)
        SystemFree(mem2);

    // faulting on mem3 alloc
	if(NitsShouldFault(NitsHere(), NitsAutomatic))
	{
		NitsAssert(false, PAL_T("mem3 alloc failed"));
	}

	if(mem3)
		SystemFree(mem3);

    // faulting on mem4 alloc
	if(NitsShouldFault(NitsHere(), NitsAutomatic))
	{
		NitsAssert(false, PAL_T("mem4 alloc failed"));
	}

	if(mem4)
		SystemFree(mem4);

	FaultSimHelper1();
}

NitsTest2(VITest1FaultSim, 
          MySetup1C1, NitsEmptyValue,
          MySetup1C2, NitsEmptyValue)
    NitsEnableFaultSim;
    NitsFaultSimMarkForRerun;
    FaultSimHelper();

    FaultSimHelper1();

    NitsTrace(PAL_T("VITest1 being run"));
    NitsAssert(true, PAL_T("test passed"));          
NitsEndTest


NitsTest2(TC1D1FaultSim,
          C1, NitsEmptyValue,
          D1, NitsEmptyValue)
    NitsEnableFaultSim;

    FaultSimHelper();

    FaultSimHelper1();

    NitsTrace(PAL_T("TC1D1 being run"));
    NitsAssert(true, PAL_T("test passed"));
NitsEndSetup

NitsTest(FaultSimTest1)
    NitsEnableFaultSim;

    FaultSimHelper();

    FaultSimHelper1();

    NitsTrace(PAL_T("FaultSimTest1 being run"));    
    
    NitsAssert(true, PAL_T("test passed"));
NitsEndTest

struct FooStruct1
{
    int i1;
};

struct FooStruct2
{
    int i2;
};

NitsSetup0(FooSetup1, FooStruct1)
    NitsAssert(NitsContext()->_FooStruct1->i1 == 10, PAL_T("wrong value"));
    if(NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        NitsTrace(PAL_T("FooSetup1 fault occurred"));
        NitsAssert(false, PAL_T("FooSetup1 fault location failed"));
        NitsReturn;
    }
    NitsContext()->_FooStruct1->i1 = 15;
    NitsTrace(PAL_T("FooSetup1 being run"));            
NitsEndSetup

struct FooStruct1 sFooStruct1 = {10};

NitsSetup1(FooSetup2, FooStruct2, FooSetup1, sFooStruct1)
    NitsAssert(NitsContext()->_FooSetup1->_FooStruct1->i1 == 15, PAL_T("wrong value"));
    NitsAssert(NitsContext()->_FooStruct2->i2 == 20, PAL_T("wrong value"));
    if(NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        NitsTrace(PAL_T("FooSetup2 fault occurred"));
        NitsAssert(false, PAL_T("FooSetup2 fault location failed"));
        NitsReturn;
    }
    NitsContext()->_FooSetup1->_FooStruct1->i1 = 35;
    NitsContext()->_FooStruct2->i2 = 25;
    NitsTrace(PAL_T("FooSetup2 being run"));        
NitsEndSetup

struct FooStruct2 sFooStruct2 = {20};

NitsTest1(FooTest, FooSetup2, sFooStruct2)
    NitsEnableFaultSim;
    NitsFaultSimMarkForRerun;

    NitsAssert(NitsContext()->_FooSetup2->_FooStruct2->i2 == 25, PAL_T("wrong value"));    
    NitsAssert(NitsContext()->_FooSetup2->_FooSetup1->_FooStruct1->i1 == 35, PAL_T("wrong value"));    
    if(NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        NitsTrace(PAL_T("FooTest fault occurred"));
        NitsAssert(false, PAL_T("FooTest fault location failed"));
        NitsReturn;
    }
    NitsContext()->_FooSetup2->_FooStruct2->i2 = 45;
    NitsContext()->_FooSetup2->_FooSetup1->_FooStruct1->i1 = 55;
    NitsTrace(PAL_T("FooTest being run"));            
NitsEndTest

NitsCleanup(FooTest)
    NitsAssert(NitsContext()->_FooSetup2->_FooStruct2->i2 == 45, PAL_T("wrong value"));
    NitsAssert(NitsContext()->_FooSetup2->_FooSetup1->_FooStruct1->i1 == 55, PAL_T("wrong value"));    
    NitsTrace(PAL_T("FooTest cleanup being run"));                
NitsEndCleanup

NitsTest(UselessTest)
    /* Causes error due to not having test assertions. */
NitsEndTest

#include <pal/shlib.h>

typedef int (*FuncPtr)();

NitsTest(SampleProductTest)
    Shlib *library = NULL;
    FuncPtr funcPtr;

    NitsEnableFaultSim;

#ifdef _MSC_VER
    library = Shlib_Open(PAL_T("nitssampleproduct.dll"));
#else
    library = Shlib_Open(PAL_T("libnitssampleproduct.so"));
#endif

    if (library == NULL)
    {
        NitsAssert(false, PAL_T("sampleproduct library can not be opened"));
        return;        
    }

    funcPtr = (FuncPtr)Shlib_Sym(library, "DoSomething");
    if (funcPtr == NULL)
    {
        Shlib_Close(library);
        NitsAssert(false, PAL_T("DoSomething not found"));
        return;
    }
    bool passed = (funcPtr() == 3);
    NitsAssert(passed, PAL_T("DoSomething failed"));
    Shlib_Close(library);    
NitsEndTest

NitsTest(TestGetCustomStringAParams)        
    NitsTrace(NitsTestGetParam(PAL_T("loglevel")));
    NitsAssert(PAL_TRUE, PAL_T(""));
NitsEndTest

NitsSetup(Var1)
    if(NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        NitsTrace(PAL_T("Var1 fault occurred"));
        NitsAssert(false, PAL_T("Var1 fault location failed"));
        NitsReturn;
    }
    NitsTrace(PAL_T("Var1 being run"));
NitsEndSetup

NitsCleanup(Var1)
    NitsTrace(PAL_T("Cleanup for Var1 being run"));
NitsEndCleanup

NitsSetup(Var2)
    if(NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        NitsTrace(PAL_T("Var2 fault occurred"));
        NitsAssert(false, PAL_T("Var2 fault location failed"));
        NitsReturn;
    }
    NitsTrace(PAL_T("Var2 being run"));
NitsEndSetup

NitsCleanup(Var2)
    NitsTrace(PAL_T("Cleanup for Var2 being run"));
NitsEndCleanup

NitsSplit2(VarSplit, NitsEmptyStruct, Var1, Var2)
    if(NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        NitsTrace(PAL_T("VarSplit fault occurred"));
        NitsAssert(false, PAL_T("VarSplit fault location failed"));
        NitsReturn;
    }
    NitsTrace(PAL_T("VarSplit being run"));
NitsEndSplit

NitsCleanup(VarSplit)
    NitsTrace(PAL_T("Cleanup for VarSplit being run"));
NitsEndCleanup

NitsSetup(SingleSetup)
    if(NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        NitsTrace(PAL_T("SingleSetup fault occurred"));
        NitsAssert(false, PAL_T("SingleSetup fault location failed"));
        NitsReturn;
    }
    NitsTrace(PAL_T("SingleSetup being run"));
NitsEndSetup

NitsCleanup(SingleSetup)
    NitsTrace(PAL_T("Cleanup for SingleSetup being run"));
NitsEndCleanup

NitsTest2(ComboTest, VarSplit, NitsEmptyValue, SingleSetup, NitsEmptyValue)
    NitsEnableFaultSim;
    NitsFaultSimMarkForRerun;
    if(NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        NitsTrace(PAL_T("Combotest fault occurred"));
        NitsAssert(false, PAL_T("Combotest fault location failed"));
        NitsReturn;
    }
    NitsTrace(PAL_T("Combotest being run"));
    NitsAssert(PAL_TRUE, PAL_T(""));
NitsEndTest

NitsCleanup(ComboTest)
    NitsTrace(PAL_T("Cleanup for ComboTest being run"));
NitsEndCleanup

NitsModuleSetup(MyModuleSetup1)
    NitsTrace(PAL_T("MyModuleSetup1 being run"));
    NitsAssert(PAL_TRUE, PAL_T(""));
NitsEndModuleSetup

NitsCleanup(MyModuleSetup1)
    NitsTrace(PAL_T("Cleanup for MyModuleSetup1 being run"));
    NitsAssert(PAL_TRUE, PAL_T(""));
NitsEndCleanup

NitsModuleSetup(MyModuleSetup2)
    NitsTrace(PAL_T("MyModuleSetup2 being run"));
    NitsAssert(PAL_TRUE, PAL_T(""));
NitsEndModuleSetup

NitsCleanup(MyModuleSetup2)
    NitsTrace(PAL_T("Cleanup for MyModuleSetup2 being run"));
    NitsAssert(PAL_TRUE, PAL_T(""));
NitsEndCleanup

NitsSetup(FirstLevelSetup)    
    if(NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        NitsTrace(PAL_T("FirstLevelSetup fault occurred"));
        NitsAssert(false, PAL_T("FirstLevelSetup fault location failed"));
        NitsReturn;
    }
    NitsTrace(PAL_T("FirstLevelSetup being run"));
NitsEndSetup

NitsCleanup(FirstLevelSetup)
    NitsTrace(PAL_T("Cleanup of FirstLevelSetup being run"));
NitsEndCleanup

NitsSetup1(SecondLevelSetup, NitsEmptyStruct, FirstLevelSetup, NitsEmptyValue)
    if(NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        NitsTrace(PAL_T("SecondLevelSetup fault occurred"));
        NitsAssert(false, PAL_T("SecondLevelSetup fault location failed"));
        NitsReturn;
    }
    NitsTrace(PAL_T("SecondLevelSetup being run"));
NitsEndSetup

NitsCleanup(SecondLevelSetup)
    NitsTrace(PAL_T("Cleanup of SecondLevelSetup being run"));
NitsEndCleanup

NitsTest2(TestWithALoop, SecondLevelSetup, NitsEmptyValue, FirstLevelSetup, NitsEmptyValue)
    NitsEnableFaultSim;
    NitsFaultSimMarkForRerun;
    if(NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        NitsTrace(PAL_T("TestWithALoop fault occurred"));
        NitsAssert(false, PAL_T("TestWithALoop fault location failed"));
        NitsReturn;
    }
    NitsTrace(PAL_T("TestWithALoop being run"));
    NitsAssert(PAL_TRUE, PAL_T(""));
NitsEndTest

NitsCleanup(TestWithALoop)
    NitsTrace(PAL_T("Cleanup of TestWithALoop being run"));
NitsEndCleanup

NitsSetup(FailingSetup)
    NitsAssert(false, PAL_T("FailingSetup failed"));
    NitsTrace(PAL_T("FailingSetup being run"));
NitsEndSetup

NitsCleanup(FailingSetup)
    NitsTrace(PAL_T("Cleanup of FailingSetup being run"));
NitsEndCleanup

NitsTestWithSetup(FailingSetupTest, FailingSetup)
    NitsTrace(PAL_T("FailingSetupTest being run"));
NitsEndTest

NitsCleanup(FailingSetupTest)
    NitsTrace(PAL_T("Cleanup of FailingSetupTest being run"));
NitsEndCleanup

NitsSetup(FailingLevel1Setup)
    NitsAssert(false, PAL_T("FailingLevel1Setup failed"));
    NitsTrace(PAL_T("FailingLevel1Setup being run"));
NitsEndSetup

NitsCleanup(FailingLevel1Setup)
    NitsTrace(PAL_T("Cleanup of FailingLevel1Setup being run"));
NitsEndCleanup

NitsSetup1(FailingLevel2Setup, NitsEmptyStruct, FailingLevel1Setup, NitsEmptyValue)    
    NitsTrace(PAL_T("FailingLevel2Setup being run"));
NitsEndSetup

NitsCleanup(FailingLevel2Setup)
    NitsTrace(PAL_T("Cleanup of FailingLevel2Setup being run"));
NitsEndCleanup

NitsTestWithSetup(FailingTwoLevelSetupTest, FailingLevel2Setup)
    NitsTrace(PAL_T("FailingTwoLevelSetupTest being run"));
NitsEndTest

NitsCleanup(FailingTwoLevelSetupTest)
    NitsTrace(PAL_T("Cleanup of FailingTwoLevelSetupTest being run"));
NitsEndCleanup

NitsSetup(Var1Fail)
    NitsAssert(false, PAL_T("Var1Fail failed"));
    NitsTrace(PAL_T("Var1Fail being run"));
NitsEndSetup

NitsCleanup(Var1Fail)
    NitsTrace(PAL_T("Cleanup of Var1Fail being run"));
NitsEndCleanup

NitsSetup(Var2Success)
    NitsTrace(PAL_T("Var2Success being run"));
NitsEndSetup

NitsCleanup(Var2Success)
    NitsTrace(PAL_T("Cleanup of Var2Success being run"));
NitsEndCleanup

NitsSplit2(VarFailSuccess, NitsEmptyStruct, Var1Fail, Var2Success)
    NitsTrace(PAL_T("VarFailSuccess being run"));
NitsEndSplit

NitsCleanup(VarFailSuccess)
    NitsTrace(PAL_T("Cleanup of VarFailSuccess being run"));
NitsEndCleanup

NitsTestWithSetup(SplitTestOneFailOtherSuccess, VarFailSuccess)
    NitsAssert(true, PAL_T("SplitTestOneFailOtherSuccess success"));
    NitsTrace(PAL_T("SplitTestOneFailOtherSuccess being run"));
NitsEndTest

NitsCleanup(SplitTestOneFailOtherSuccess)
    NitsTrace(PAL_T("Cleanup of SplitTestOneFailOtherSuccess being run"));
NitsEndCleanup

NitsTest(FailingCleanupTest)
    NitsAssert(true, PAL_T("FailingCleanupTest success"));
    NitsTrace(PAL_T("FailingCleanupTest being run"));
NitsEndTest

NitsCleanup(FailingCleanupTest)
    NitsAssert(false, PAL_T("Cleanup for FailingCleanupTest fails"));
    NitsTrace(PAL_T("Cleanup for FailingCleanupTest being run"));
NitsEndCleanup

NitsSetup(UnexpectedFaultSimErrorSetup)
    NitsTrace(PAL_T("UnexpectedFaultSimErrorSetup being run"));
NitsEndSetup

NitsCleanup(UnexpectedFaultSimErrorSetup)
    NitsTrace(PAL_T("Cleanup of UnexpectedFaultSimErrorSetup being run"));
NitsEndCleanup

PAL_Uint32 g_unexpectedFaultSimError = 0;

NitsTestWithSetup(UnexpectedFaultSimErrorTest, UnexpectedFaultSimErrorSetup)
    NitsFaultSimMarkForRerun;
    NitsEnableFaultSim;
    g_unexpectedFaultSimError++;    
    if(g_unexpectedFaultSimError == 1)
    {
        NitsAssert(true, PAL_T("UnexpectedFaultSimErrorTest success"));
    }
    
    if(NitsShouldFault(NitsHere(), NitsAutomatic))
    {
        NitsTrace(PAL_T("UnexpectedFaultSimErrorTest fault occurred; will be ignored"));
    }

    if(g_unexpectedFaultSimError == 3)
    {
        NitsAssert(false, PAL_T("UnexpectedFaultSimErrorTest asserted false on without fault "));
    }

    NitsTrace(PAL_T("UnexpectedFaultSimErrorTest being run"));
NitsEndTest

NitsCleanup(UnexpectedFaultSimErrorTest)
    NitsTrace(PAL_T("Cleanup of UnexpectedFaultSimErrorTest being run"));
NitsEndCleanup


/*********************************************************************************************************************************
** NITS DEMO:- Refactoring existing tests with new interface
**********************************************************************************************************************************/

/*********************************************************************************************************************************
** Dummy product
**********************************************************************************************************************************/

typedef struct _TestApplication
{
    unsigned int applicationHandle;
} TestApplication;

TestApplication *Create_TestApplication()
{
    TestApplication *application = (TestApplication *) SystemMalloc(sizeof(TestApplication));
    if(application)
    {
        application->applicationHandle = 1;
    }
    return application;
}

void Close_TestApplication(TestApplication *application)
{
    if(application)
        SystemFree(application);
}

enum ProtocolType
{
    ProtocolA,
    ProtocolB
};

typedef struct _TestSession
{
    TestApplication *application;
    unsigned int sessionHandle;
    ProtocolType protocolType;
} TestSession;

TestSession *Create_TestSession(TestApplication *application, ProtocolType protocol)
{
    TestSession *session = (TestSession *) SystemMalloc(sizeof(TestSession));
    if(session)
    {
        session->application = application;
        session->sessionHandle = 1;
        session->protocolType = protocol;
    }
    return session;
}

void Close_TestSession(TestSession *session)
{
    if(session)
        SystemFree(session);
}

typedef struct _TestOperation
{
    TestSession *session;
    unsigned int operationId;
} TestOperation;

TestOperation *Create_TestOperation(TestSession *session)
{
    TestOperation *operation = (TestOperation *) SystemMalloc(sizeof(TestOperation));
    if(operation)
    {
        operation->session = session;
        operation->operationId = 1;        
    }
    return operation;
}

void Close_TestOperation(TestOperation *operation)
{
    if(operation)
        SystemFree(operation);
}

int Execute_Operation(int a[5], ProtocolType protoType)
{
    int sum = 0;
    for(int i = 0; i < 5; i++)
    {
        sum += a[i];
    }
    if(protoType == ProtocolB)
    {
        return sum + 1;
    }
    else
    {
        return sum;
    }
    
}

/*********************************************************************************************************************************
** Test code with duplication
**********************************************************************************************************************************/

NitsTest(TestOperationProtocolA)
    TestApplication *application = Create_TestApplication();
    NitsAssertOrReturn(application != NULL, PAL_T("application creation failed"));
    TestSession *session = Create_TestSession(application, ProtocolA);
    NitsAssertOrReturn(session != NULL, PAL_T("session creation failed on protocol A"));
    TestOperation *operation = Create_TestOperation(session);
    NitsAssertOrReturn(operation != NULL, PAL_T("operation creation failed"));
    int a[5] = {0, 1, 2, 3, 4};
    NitsAssertOrReturn(Execute_Operation(a, ProtocolA) == 10, PAL_T("Operation execute failed"));
NitsEndTest

NitsTest(TestOperationProtocolB)
    TestApplication *application = Create_TestApplication();
    NitsAssertOrReturn(application != NULL, PAL_T("application creation failed"));
    TestSession *session = Create_TestSession(application, ProtocolB);
    NitsAssertOrReturn(session != NULL, PAL_T("session creation failed on protocol B"));
    TestOperation *operation = Create_TestOperation(session);
    NitsAssertOrReturn(operation != NULL, PAL_T("operation creation failed"));
    int a[5] = {0, 1, 2, 3, 4};
    NitsAssertOrReturn(Execute_Operation(a, ProtocolB) == 11, PAL_T("Operation execute failed"));
NitsEndTest

/*********************************************************************************************************************************
** Refactored test code
**********************************************************************************************************************************/

struct CommonData
{
    TestApplication *application;
    TestSession *session;
    TestOperation *operation;
};

NitsSetup0(CommonSetup, CommonData)
    NitsTrace(PAL_T("CommonSetup being run"));
NitsEndSetup

NitsSetup1(SetupApplication, NitsEmptyStruct, 
            CommonSetup, CommonSetupDefaults)
    NitsContext()->_CommonSetup->_CommonData->application = Create_TestApplication();
    NitsTrace(PAL_T("SetupApplication being run"));
    NitsAssertOrReturn(NitsContext()->_CommonSetup->_CommonData->application != NULL, PAL_T("application creation failed"));
NitsEndSetup

struct SessionData
{
    int protocolType;
};

NitsSetup0(SetupSessionProtocolA, SessionData)
    NitsTrace(PAL_T("SetupSessionProtocolA being run"));
    NitsContext()->_SessionData->protocolType = ProtocolA;
NitsEndSetup

NitsSetup0(SetupSessionProtocolB, SessionData)
    NitsTrace(PAL_T("SetupSessionProtocolB being run"));
    NitsContext()->_SessionData->protocolType = ProtocolB;
NitsEndSetup

NitsSplit2(SetupSessionSplit, SessionData, 
            SetupSessionProtocolA, SetupSessionProtocolB)   
    NitsTrace(PAL_T("SetupSessionSplit being run"));
NitsEndSplit

NitsSetup2(SetupSessionProtocol, NitsEmptyStruct,
        CommonSetup, CommonSetupDefaults,
        SetupSessionSplit, SetupSessionSplitDefaults)
        NitsContext()->_CommonSetup->_CommonData->session = Create_TestSession(NitsContext()->_CommonSetup->_CommonData->application,
        (ProtocolType)NitsContext()->_SetupSessionSplit->_SetupSessionProtocolA->_SessionData->protocolType);
    NitsAssertOrReturn(NitsContext()->_CommonSetup->_CommonData->session != NULL, PAL_T("session creation failed"));
    NitsTrace(PAL_T("SetupSessionProtocol being run"));
NitsEndSetup

struct OperationData
{
    int *a;
};

NitsSetup1(SetupOperation, OperationData, 
        CommonSetup, CommonSetupDefaults)
    int a[5] = {0, 1, 2, 3, 4};
    
    NitsContext()->_OperationData->a = a;
    NitsContext()->_CommonSetup->_CommonData->operation = Create_TestOperation(NitsContext()->_CommonSetup->_CommonData->session);
    NitsAssertOrReturn(NitsContext()->_CommonSetup->_CommonData->operation != NULL, PAL_T("operation creation failed"));
    NitsTrace(PAL_T("SetupOperation being run"));
NitsEndSetup

NitsTest3(TestOperationBothProtocols, 
    SetupApplication, SetupApplicationDefaults,
    SetupSessionProtocol, SetupSessionProtocolDefaults,
    SetupOperation, SetupOperationDefaults)    
    int result = Execute_Operation(NitsContext()->_SetupOperation->_OperationData->a, 
        (ProtocolType)(NitsContext()->_SetupSessionProtocol->_SetupSessionSplit->_SessionData->protocolType));
    
    if(NitsContext()->_SetupSessionProtocol->_SetupSessionSplit->_SessionData->protocolType == ProtocolA)
        NitsAssert(result == 10, PAL_T("Operation execute failed"));    
    else if(NitsContext()->_SetupSessionProtocol->_SetupSessionSplit->_SessionData->protocolType == ProtocolB)
        NitsAssert(result == 11, PAL_T("Operation execute failed")); 
    else
        NitsAssert(false, PAL_T("unknown protocol"));
    NitsTrace(PAL_T("TestOperationBothProtocols being run"));
NitsEndTest

