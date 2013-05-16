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
#include <wqlcxx/wqlcxx.h>

using namespace std;
using namespace wqlcxx;

class MyValueSource : public WQLValueSource
{
public:

    MyValueSource(bool a_, long long b_, double c_, const string& d_)
        : a(a_), b(b_), c(c_), d(d_)
    {
    }

    virtual bool LookupValue(
        const char* name, 
        WQLType& type,
        WQLValue& value)
    {
        if (strcmp(name, "A") == 0)
        {
            type = WQLTYPE_BOOLEAN;
            value.booleanValue = a;
            return true;
        }
        else if (strcmp(name, "B") == 0)
        {
            type = WQLTYPE_INTEGER;
            value.integerValue = b;
            return true;
        }
        else if (strcmp(name, "C") == 0)
        {
            type = WQLTYPE_REAL;
            value.realValue = c;
            return true;
        }
        else if (strcmp(name, "D") == 0)
        {
            type = WQLTYPE_STRING;
            value.stringValue = d;
            return true;
        }

        return false;
    }

    bool a;
    long long b;
    double c;
    string d;
};

static void setUp()
{
}

static void cleanup()
{
}

static void Test1()
{
    WQL* wql = WQL::Parse(
        "SELECT A,B,C,D FROM X "
        "WHERE A = TRUE AND B = 1 AND C = 1.0 AND D = \"String\"");

    UT_ASSERT(wql);

    UT_ASSERT(strcmp(wql->GetClassName(), "X") == 0);
    UT_ASSERT(wql->GetPropertyCount() == 4);

    UT_ASSERT(strcmp(wql->GetPropertyName(0), "A") == 0);
    UT_ASSERT(strcmp(wql->GetPropertyName(1), "B") == 0);
    UT_ASSERT(strcmp(wql->GetPropertyName(2), "C") == 0);
    UT_ASSERT(strcmp(wql->GetPropertyName(3), "D") == 0);

    MyValueSource* source1 = new MyValueSource(true, 1, 1.0, "String");
    UT_ASSERT(wql->Evaluate(source1));

    MyValueSource* source2 = new MyValueSource(true, 2, 1.0, "String");
    UT_ASSERT(!wql->Evaluate(source2));

#if 0
    wql->Dump();
#endif

    WQL::Destroy(wql);
    delete source1;
    delete source2;
}

static void Test2()
{
    WQL* wql = WQL::Parse(
        "SELECT * FROM X "
        "WHERE A = TRUE AND B = 1 AND C = 1.0 AND D = \"String\"");

    UT_ASSERT(wql);

    UT_ASSERT(strcmp(wql->GetClassName(), "X") == 0);
    UT_ASSERT(wql->GetPropertyCount() == 0);

    MyValueSource* source1 = new MyValueSource(true, 1, 1.0, "String");
    UT_ASSERT(wql->Evaluate(source1));

    MyValueSource* source2 = new MyValueSource(true, 2, 1.0, "String");
    UT_ASSERT(!wql->Evaluate(source2));

#if 0
    wql->Dump();
#endif

    WQL::Destroy(wql);
    delete source1;
    delete source2;
}

static void RunTests()
{
    UT_TEST(Test1);
    UT_TEST(Test2);
}

UT_ENTRY_POINT(RunTests);
