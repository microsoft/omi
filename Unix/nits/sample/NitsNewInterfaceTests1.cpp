#include "NitsNewInterfaceTests.h"

struct MyStruct sBodyWithInitializableSetup = {9, 0};

NitsTestWithInitializableSetup(BodyWithInitializableSetup, Fixture0, sBodyWithInitializableSetup)
    NitsTrace(PAL_T("BodyWithInitializableSetup being run"));
    NitsAssert(true, PAL_T("test passed"));          
NitsEndTest

struct MyStruct2 sFixture5 = {5, 10};

NitsDefSetup2(Fixture5, MyStruct2, Fixture2, sFixture5, Fixture4, sFixture5)
    NitsContext()->_MyStruct2->c = 0;
    NitsContext()->_MyStruct2->d = 0;

    NitsContext()->_Fixture2->_Fixture0->_MyStruct->x = 0;
    NitsContext()->_Fixture2->_Fixture0->_MyStruct->p = 0;

    NitsContext()->_Fixture4->_Fixture0->_MyStruct->x = 0;
    NitsContext()->_Fixture4->_Fixture0->_MyStruct->p = 0;
NitsEndSetup

NitsDefSetup(MySetup2)
    NitsTrace(PAL_T("MySetup2 being run"));
NitsEndSetup
