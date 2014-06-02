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
#include <micxx/array.h>
#include <micxx/types.h>
#include <pal/atomic.h>

using namespace mi;

NitsSetup(TestArraySetup)
NitsEndSetup

NitsCleanup(TestArraySetup)
NitsEndCleanup

//union AlignmentStruct {
//    void* p;
//    Uint64 i;
//};

NitsTestWithSetup(TestArrayCtor, TestArraySetup)
{
    const char s[] = "string1";
    Array<char> v1(s, sizeof(s));

    UT_ASSERT( strcmp(s, v1.GetData()) == 0);
    UT_ASSERT( v1.GetSize() == sizeof(s));

    // default ctor
    Array<char> v2;

    UT_ASSERT( v2.GetData() == 0);
    UT_ASSERT( v2.GetSize() == 0);

    // array ctor with 0 elements
    Array<char> v3(s, 0);

    UT_ASSERT( v3.GetData() == 0);
    UT_ASSERT( v3.GetSize() == 0);
}
NitsEndTest

NitsTestWithSetup(TestAccessOperator, TestArraySetup)
{
    unsigned int sample[] = {1,2,3};
    Array<unsigned int> v(sample,3);
    UT_ASSERT( v.GetSize() == 3);
    UT_ASSERT( v[0] == 1 );
    UT_ASSERT( v[1] == 2 );
    UT_ASSERT( v[2] == 3 );
}
NitsEndTest

template< typename TYPE, size_t AligmentSize>

static void TestDataAlignmentT()
{
    Array<TYPE> v;
    v.PushBack( TYPE() );

    UT_ASSERT(v.GetSize() == 1);
    UT_ASSERT(((long)v.GetData()) % AligmentSize == 0);

}


struct AlignmentTestStruct {
    char c[21];
    void*p;
};

NitsTestWithSetup(TestDataAlignment, TestArraySetup)
{
    TestDataAlignmentT<char,sizeof(char)>();
    TestDataAlignmentT<long,sizeof(long)>();
    TestDataAlignmentT<Uint64,sizeof(void*)>();
    TestDataAlignmentT<void*,sizeof(void*)>();
    TestDataAlignmentT<int,sizeof(int)>();
    TestDataAlignmentT<short int,sizeof(short int)>();
    TestDataAlignmentT<AlignmentTestStruct,sizeof(void*)>();
}
NitsEndTest

struct TestCreateDestroyClass{
    bool m_created;
    bool m_destroyed;
    static volatile ptrdiff_t m_ctorCalls;
    static volatile ptrdiff_t m_dtorCalls;
    String s;

    TestCreateDestroyClass()
    {
        s = MI_T("1");
        m_created = true;
        m_destroyed = false;
        Atomic_Inc(&m_ctorCalls);
    }
    TestCreateDestroyClass(const TestCreateDestroyClass& x)
    {
        Atomic_Inc(&m_ctorCalls);
        *this = x;
    }

    ~TestCreateDestroyClass()
    {
        UT_ASSERT(isValid());
        m_created = false;
        m_destroyed = true;
        Atomic_Inc(&m_dtorCalls);
    }

    bool isValid()const {return m_created && !m_destroyed && s == MI_T("1");}
};

volatile ptrdiff_t TestCreateDestroyClass::m_ctorCalls = 0;
volatile ptrdiff_t TestCreateDestroyClass::m_dtorCalls = 0;

static void TestAllItemsAreValid( const Array<TestCreateDestroyClass>& v )
{
    for( Uint32 i = 0; i < v.GetSize(); i++ )
    {
        UT_ASSERT(v[i].isValid());
    }
}
    
NitsTestWithSetup(TestCreatingDestroyingObjects, TestArraySetup)
{
    Array<TestCreateDestroyClass> v, v2;

    v.Resize(10);

    TestAllItemsAreValid(v);
    TestAllItemsAreValid(v2);

    v.PushBack( TestCreateDestroyClass() );

    TestAllItemsAreValid(v);
    TestAllItemsAreValid(v2);

    v2 = v;

    TestAllItemsAreValid(v);
    TestAllItemsAreValid(v2);

    v.PushBack( TestCreateDestroyClass() );

    UT_ASSERT(v.GetSize() == 12);
    UT_ASSERT(v2.GetSize() == 11);

    TestAllItemsAreValid(v);
    TestAllItemsAreValid(v2);

    v.Delete(0);
    v2.Delete(10);

    UT_ASSERT(v.GetSize() == 11);
    UT_ASSERT(v2.GetSize() == 10);

    TestAllItemsAreValid(v);
    TestAllItemsAreValid(v2);

    v[1] = v2[4];
    TestAllItemsAreValid(v);
    TestAllItemsAreValid(v2);

}
NitsEndTest

NitsTestWithSetup(TestClear, TestArraySetup)
{
    Array<TestCreateDestroyClass> v, v2;

    v.PushBack(TestCreateDestroyClass());
    v2 = v;
    v2.Resize(2);

    UT_ASSERT(v.GetSize() == 1);
    UT_ASSERT(v2.GetSize() == 2);

    TestAllItemsAreValid(v);
    TestAllItemsAreValid(v2);

    v2.Clear();
    UT_ASSERT(v.GetSize() == 1);
    UT_ASSERT(v2.GetSize() == 0);

    TestAllItemsAreValid(v);
    TestAllItemsAreValid(v2);
}
NitsEndTest

NitsTestWithSetup(TestResize, TestArraySetup)
{
    Array<TestCreateDestroyClass> v, v2;

    v.Resize(3);
    v2 = v;
    v2.Resize(3);

    UT_ASSERT(v.GetSize() == 3);
    UT_ASSERT(v2.GetSize() == 3);

    TestAllItemsAreValid(v);
    TestAllItemsAreValid(v2);
}
NitsEndTest

NitsTestWithSetup(TestResizeWithRealloc, TestArraySetup)
{
    Array<TestCreateDestroyClass> v, v2;

    v.Resize(3);

    UT_ASSERT(v.GetSize() == 3);

    TestAllItemsAreValid(v);

    // resize to big number to trigger re-alloc
    v.Resize(3000);

    UT_ASSERT(v.GetSize() == 3000);

    TestAllItemsAreValid(v);

}
NitsEndTest

NitsTestWithSetup(TestAssignEmpty, TestArraySetup)
{
    Array<TestCreateDestroyClass> v, v2;

    v.Resize(3);

    v = v2;

    UT_ASSERT(v.GetSize() == 0);
    UT_ASSERT(v2.GetSize() == 0);
}
NitsEndTest

NitsTestWithSetup(TestDeleteTheOnlyOne, TestArraySetup)
{
    Array<TestCreateDestroyClass> v;

    v.Resize(1);

    v.Delete(0);

    UT_ASSERT(v.GetSize() == 0);
}
NitsEndTest

NitsTestWithSetup(TestResizeToShrink, TestArraySetup)
{
    Array<TestCreateDestroyClass> v;

    v.Resize(100);

    v.Resize(10);

    UT_ASSERT(v.GetSize() == 10);
    TestAllItemsAreValid(v);
}
NitsEndTest

NitsTestWithSetup(TestCtorDtorBalance, TestArraySetup)
{
    ptrdiff_t ctor, dtor;

    ctor = Atomic_Read(&TestCreateDestroyClass::m_ctorCalls);
    dtor = Atomic_Read(&TestCreateDestroyClass::m_dtorCalls);

    UT_ASSERT_EQUAL(ctor, dtor);
}
NitsEndTest

NitsTestWithSetup(TestGetWritableData, TestArraySetup)
{
    Array< int > v;

    v.Resize(3);

    v.GetWritableData() [0] = 0;
    v.GetWritableData() [1] = 1;
    v.GetWritableData() [2] = 2;

    UT_ASSERT(0 == v[0]);
    UT_ASSERT(1 == v[1]);
    UT_ASSERT(2 == v[2]);
}
NitsEndTest

NitsTestWithSetup(TestInlineCOW, TestArraySetup)
{
    Array< int > v;

    v.PushBack(0);

    Array< int > v2 = v;

    v2[0] = 1;
    v.PushBack(1);

    UT_ASSERT(0 == v[0]);
    UT_ASSERT(1 == v[1]);
    UT_ASSERT(1 == v2[0]);
    UT_ASSERT(v.GetSize() == 2);
    UT_ASSERT(v2.GetSize() == 1);
}
NitsEndTest

NitsTestWithSetup(TestInlineCOWFromEmptyVector, TestArraySetup)
{
    Array< int > v;

    int* p = v.GetWritableData();

    UT_ASSERT(0 == p);
    UT_ASSERT(v.GetSize() == 0);
}
NitsEndTest


// simple type

// alignment




// should be the last test - verifies balance of ctor/dtor


