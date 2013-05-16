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
#include "../../micxx/array.h"
#include "../../micxx/types.h"

using namespace mi;

static void setUp()
{
}

static void cleanup()
{
}

//union AlignmentStruct {
//    void* p;
//    Uint64 i;
//};

static void TestCtor()
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

static void TestAccessOperator()
{
    unsigned int sample[] = {1,2,3};
    Array<unsigned int> v(sample,3);
    UT_ASSERT( v.GetSize() == 3);
    UT_ASSERT( v[0] == 1 );
    UT_ASSERT( v[1] == 2 );
    UT_ASSERT( v[2] == 3 );
}

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

static void TestDataAlignment()
{
    TestDataAlignmentT<char,sizeof(char)>();
    TestDataAlignmentT<long,sizeof(long)>();
    TestDataAlignmentT<Uint64,sizeof(void*)>();
    TestDataAlignmentT<void*,sizeof(void*)>();
    TestDataAlignmentT<int,sizeof(int)>();
    TestDataAlignmentT<short int,sizeof(short int)>();
    TestDataAlignmentT<AlignmentTestStruct,sizeof(void*)>();
}

struct TestCreateDestroyClass{
    bool m_created;
    bool m_destroyed;
    static int m_ctorCalls;
    static int m_dtorCalls;
    String s;

    TestCreateDestroyClass()
    {
        s = MI_T("1");
        m_created = true;
        m_destroyed = false;
        m_ctorCalls++;
    }
    TestCreateDestroyClass(const TestCreateDestroyClass& x)
    {
        m_ctorCalls++;
        *this = x;
    }

    ~TestCreateDestroyClass()
    {
        UT_ASSERT(isValid());
        m_created = false;
        m_destroyed = true;
        m_dtorCalls++;
    }

    bool isValid()const {return m_created && !m_destroyed && s == MI_T("1");}
};

int TestCreateDestroyClass::m_ctorCalls = 0;;
int TestCreateDestroyClass::m_dtorCalls = 0;

static void TestAllItemsAreValid( const Array<TestCreateDestroyClass>& v )
{
    for( Uint32 i = 0; i < v.GetSize(); i++ )
    {
        UT_ASSERT(v[i].isValid());
    }
}
    
static void TestCreatingDestroyingObjects()
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

static void TestClear()
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

static void TestResize()
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

static void TestResizeWithRealloc()
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

static void TestAssignEmpty()
{
    Array<TestCreateDestroyClass> v, v2;

    v.Resize(3);

    v = v2;

    UT_ASSERT(v.GetSize() == 0);
    UT_ASSERT(v2.GetSize() == 0);
}

static void TestDeleteTheOnlyOne()
{
    Array<TestCreateDestroyClass> v;

    v.Resize(1);

    v.Delete(0);

    UT_ASSERT(v.GetSize() == 0);
}

static void TestResizeToShrink()
{
    Array<TestCreateDestroyClass> v;

    v.Resize(100);

    v.Resize(10);

    UT_ASSERT(v.GetSize() == 10);
    TestAllItemsAreValid(v);
}

static void TestCtorDtorBalance()
{
    UT_ASSERT(TestCreateDestroyClass::m_ctorCalls == TestCreateDestroyClass::m_dtorCalls);
}

static void TestGetWritableData()
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

static void TestInlineCOW()
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

static void TestInlineCOWFromEmptyVector()
{
    Array< int > v;

    int* p = v.GetWritableData();

    UT_ASSERT(0 == p);
    UT_ASSERT(v.GetSize() == 0);
}


static void RunTests()
{
    // simple type
    UT_TEST(TestCtor);
    UT_TEST(TestAccessOperator);

    // alignment
    UT_TEST(TestDataAlignment);

    UT_TEST(TestCreatingDestroyingObjects);
    UT_TEST(TestClear);
    UT_TEST(TestResize);
    UT_TEST(TestResizeWithRealloc);
    UT_TEST(TestAssignEmpty);
    UT_TEST(TestDeleteTheOnlyOne);
    UT_TEST(TestResizeToShrink);

    UT_TEST(TestGetWritableData);
    UT_TEST(TestInlineCOW);
    UT_TEST(TestInlineCOWFromEmptyVector);


    // should be the last test - verifies balance of ctor/dtor
    UT_TEST(TestCtorDtorBalance);
}

static ut::TestRegister s_register(RunTests);
