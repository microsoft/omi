/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <ut/ut.h>
#include <math.h>
#include <micxx/dinstance.h>
#include <tests/base/Outer.h>

using namespace std;
using namespace mi;

// TODO: Override new operator if needed for fault injection
// Currently most places in micxx code use new operator with already allocated memory
// so i am not sure how crucial it is to override that with an injected version for fault injection

template<class ZT>
Array<ZT> MakeArray(const ZT& x, const ZT& y)
{
    Array<ZT> a;
    a.PushBack(x);
    a.PushBack(y);
    return a;
}

Array<String> MakeStrA(const String& x, const String& y)
{
    Array<String> a;
    a.PushBack(x);
    a.PushBack(y);
    return a;
}

NitsTest(Test1)
{
    NitsDisableFaultSim;

    DInstance di(ZT("Gadget"), DInstance::CLASS);
    const StringA COLORS = MakeArray<String>(ZT("Red"), ZT("Green"));
    const Uint32A NUMBERS = MakeArray<Uint32>(10, 20);

    UT_ASSERT(di.AddBoolean(ZT("True"), true));
    UT_ASSERT(di.AddBoolean(ZT("False"), false));
    UT_ASSERT(di.AddUint8(ZT("Uint8S"), 8));
    UT_ASSERT(di.AddString(ZT("Color"), ZT("Red")));
    UT_ASSERT(di.AddStringA(ZT("Colors"), COLORS));
    UT_ASSERT(di.AddUint32A(ZT("Numbers"), NUMBERS));

    {
        Boolean tmp;
        UT_ASSERT(di.GetBoolean(ZT("True"), tmp));
        UT_ASSERT(tmp);
    }
    {
        Boolean tmp;
        UT_ASSERT(di.GetBoolean(ZT("False"), tmp));
        UT_ASSERT(!tmp);
    }
    {
        Uint8 tmp;
        UT_ASSERT(di.GetUint8(ZT("Uint8S"), tmp));
        UT_ASSERT(tmp == 8);
    }
    {
        Uint32A tmp;
        UT_ASSERT(di.GetUint32A(ZT("Numbers"), tmp));
        UT_ASSERT(tmp.GetSize() == 2);
        UT_ASSERT(tmp[0] == NUMBERS[0]);
        UT_ASSERT(tmp[1] == NUMBERS[1]);
    }
    {
        StringA tmp;
        UT_ASSERT(di.GetStringA(ZT("Colors"), tmp));
        UT_ASSERT(tmp.GetSize() == COLORS.GetSize());
        UT_ASSERT(tmp.GetSize() == 2);
        UT_ASSERT(tmp[0] == COLORS[0]);
        UT_ASSERT(tmp[1] == COLORS[1]);
    }
    {
        String color;
        UT_ASSERT(di.SetString(ZT("Color"), ZT("Blue")));
    }


    // Person.Key=1
    {
        DInstance person(ZT("Person"), DInstance::ASSOCIATION);
        UT_ASSERT(person.AddUint32(ZT("Key"), 1, false, true));
        UT_ASSERT(person.AddString(ZT("First"), ZT("George")));
        UT_ASSERT(person.AddString(ZT("Last"), ZT("Washington")));

        Uint32 Key;
        bool isKey;
        bool isNull;
        UT_ASSERT(person.GetUint32(ZT("Key"), Key, isNull, isKey));
        UT_ASSERT(Key == 1);
        UT_ASSERT(isKey);
        UT_ASSERT(!isNull);

        String First;
        UT_ASSERT(person.GetString(ZT("First"), First));
        UT_ASSERT(First == ZT("George"));

        String Last;
        UT_ASSERT(person.GetString(ZT("Last"), Last));
        UT_ASSERT(Last == ZT("Washington"));
        UT_ASSERT(di.AddInstance(ZT("Person"), person));
    }

    DInstance d1(di);
    d1.AddString(ZT("Reason"), ZT("None"));
}
NitsEndTest

NitsTest(Test2)
{
    NitsDisableFaultSim;

    DInstance d1;
    DInstance d2(d1);
    d2.AddUint32(ZT("P2"), 0);
    UT_ASSERT(true); //TODO.
}
NitsEndTest

NitsTest(Test3)
{
    NitsDisableFaultSim;

    DInstance d1;
    d1.AddUint32(ZT("P2"), 0);
    d1.AddUint32(ZT("P1"), 0);

    DInstance d2(d1);
    DInstance d3(d2);
    DInstance d4;
    d4 = d3;
    d4 = d1;
    d4 = d2;
    UT_ASSERT(true); //TODO.
}
NitsEndTest

#if 0
template<class ZT>
Array<ZT> MakeArray(const ZT& x, Uint32 n)
{
    Array<ZT> a;
    for (Uint32 i = 0; i < n; i++)
    {
        a.PushBack(x);
    }

    return a;
}
#endif

static double dabs(double x)
{
    return x < 0.0 ? -x : x;
}

bool Close(double x, double y)
{
    return dabs(x - y) <= 0.00001;
}

void CheckInnerInstance(const Inner_Class& inner)
{
    UT_ASSERT(inner.Key_value() == 32);
    UT_ASSERT(inner.Str_value() == ZT("Hello"));
}

template<class ZT>
struct CheckArray
{
    static bool func(const Array<ZT>& a, const ZT& x, const ZT& y)
    {
        return a.GetSize() == 2 && a[0] == x && a[1] == y;
    }
};

template<>
struct CheckArray<Real32>
{
    static bool func(const Array<Real32>& a, const Real32& x, const Real32& y)
    {
        return a.GetSize() == 2 && Close(a[0], x) && Close(a[1], y);
    }
};

template<>
struct CheckArray<Real64>
{
    static bool func(const Array<Real64>& a, const Real64& x, const Real64& y)
    {
        return a.GetSize() == 2 && Close(a[0], x) && Close(a[1], y);
    }
};

void CheckOuterInstance(const Outer_Class& x)
{
    UT_ASSERT(x.booleanScalar_value()); //  == true
    UT_ASSERT(x.uint8Scalar_value() == 8);
    UT_ASSERT(x.sint8Scalar_value() == -8);
    UT_ASSERT(x.uint16Scalar_value() == 16);
    UT_ASSERT(x.sint16Scalar_value() == -16);
    UT_ASSERT(x.uint32Scalar_value() == 32);
    UT_ASSERT(x.sint32Scalar_value() == -32);
    UT_ASSERT(x.uint64Scalar_value() == 64);
    UT_ASSERT(x.sint64Scalar_value() == -64);
    UT_ASSERT(Close(x.real32Scalar_value(), 32.32));
    UT_ASSERT(Close(x.real64Scalar_value(), 64.64));
    UT_ASSERT(x.char16Scalar_value() == 16);

    {
        Datetime datetimeScalar;
        datetimeScalar.Set(MI_T("20091231120030.123456+360"));
        UT_ASSERT(x.datetimeScalar_value() == datetimeScalar);
    }

    UT_ASSERT(x.stringScalar_value() == ZT("string"));

    CheckInnerInstance(x.instanceScalar_value());

    UT_ASSERT(CheckArray<Boolean>::func(x.booleanArray_value(), true, false));
    UT_ASSERT(CheckArray<Uint8>::func(x.uint8Array_value(), 8, 8));
    UT_ASSERT(CheckArray<Sint8>::func(x.sint8Array_value(), -8, -8));
    UT_ASSERT(CheckArray<Uint16>::func(x.uint16Array_value(), 16, 16));
    UT_ASSERT(CheckArray<Sint16>::func(x.sint16Array_value(), -16, -16));
    UT_ASSERT(CheckArray<Uint32>::func(x.uint32Array_value(), 32, 32));
    UT_ASSERT(CheckArray<Sint32>::func(x.sint32Array_value(), -32, -32));
    UT_ASSERT(CheckArray<Uint64>::func(x.uint64Array_value(), 64, 64));
    UT_ASSERT(CheckArray<Sint64>::func(x.sint64Array_value(), -64, -64));
    UT_ASSERT(CheckArray<Real32>::func(x.real32Array_value(), 32.32f, 32.32f));
    UT_ASSERT(CheckArray<Real64>::func(x.real64Array_value(), 64.64, 64.64));
    UT_ASSERT(CheckArray<Char16>::func(x.char16Array_value(), 16, 16));
    UT_ASSERT(CheckArray<String>::func(x.stringArray_value(), 
        String(ZT("string")), String(ZT("string"))));

    {
        Datetime dt;
        dt.Set(ZT("20091231120030.123456+360"));
        UT_ASSERT(CheckArray<Datetime>::func(x.datetimeArray_value(), dt, dt));
    }

    {
        UT_ASSERT(x.instanceArray_value().GetSize() == 2);
        CheckInnerInstance(x.instanceArray_value()[0]);
        CheckInnerInstance(x.instanceArray_value()[1]);
    }
}

NitsTest(Test4)
{
    NitsDisableFaultSim;

    DInstance d0(ZT("Inner"), DInstance::CLASS);
    d0.AddUint32(ZT("Key"), 32);
    d0.AddString(ZT("Str"), ZT("Hello"));

    DInstance d1(ZT("Outer"), DInstance::CLASS);
    d1.AddBoolean(ZT("booleanScalar"), true);
    d1.AddUint8(ZT("uint8Scalar"), 8);
    d1.AddSint8(ZT("sint8Scalar"), -8);
    d1.AddUint16(ZT("uint16Scalar"), 16);
    d1.AddSint16(ZT("sint16Scalar"), -16);
    d1.AddUint32(ZT("uint32Scalar"), 32);
    d1.AddSint32(ZT("sint32Scalar"), -32);
    d1.AddUint64(ZT("uint64Scalar"), 64);
    d1.AddSint64(ZT("sint64Scalar"), -64);
    d1.AddReal32(ZT("real32Scalar"), 32.32f);
    d1.AddReal64(ZT("real64Scalar"), 64.64);
    d1.AddChar16(ZT("char16Scalar"), 16);
    Datetime datetimeScalar;
    datetimeScalar.Set(ZT("20091231120030.123456+360"));
    d1.AddDatetime(ZT("datetimeScalar"), datetimeScalar);
    d1.AddString(ZT("stringScalar"), ZT("string"));
    d1.AddInstance(ZT("instanceScalar"), d0);

    d1.AddBooleanA(ZT("booleanArray"), MakeArray(Boolean(true), Boolean(false)));
    d1.AddUint8A(ZT("uint8Array"), MakeArray(Uint8(8), Uint8(8)));
    d1.AddSint8A(ZT("sint8Array"), MakeArray(Sint8(-8), Sint8(-8)));
    d1.AddUint16A(ZT("uint16Array"), MakeArray(Uint16(16), Uint16(16)));
    d1.AddSint16A(ZT("sint16Array"), MakeArray(Sint16(-16), Sint16(-16)));
    d1.AddUint32A(ZT("uint32Array"), MakeArray(Uint32(32), Uint32(32)));
    d1.AddSint32A(ZT("sint32Array"), MakeArray(Sint32(-32), Sint32(-32)));
    d1.AddUint64A(ZT("uint64Array"), MakeArray(Uint64(64), Uint64(64)));
    d1.AddSint64A(ZT("sint64Array"), MakeArray(Sint64(-64), Sint64(-64)));
    d1.AddReal32A(ZT("real32Array"), MakeArray(Real32(32.32), Real32(32.32)));
    d1.AddReal64A(ZT("real64Array"), MakeArray(Real64(64.64), Real64(64.64)));
    d1.AddChar16A(ZT("char16Array"), MakeArray(Char16(16), Char16(16)));
    d1.AddDatetimeA(ZT("datetimeArray"), 
        MakeArray(datetimeScalar, datetimeScalar));
    d1.AddStringA(ZT("stringArray"), 
        MakeArray(String(ZT("string")), String(ZT("string"))));
#if 1
    d1.AddInstanceA(ZT("instanceArray"), MakeArray(d0, d0));
#endif

    Outer_Class outer;
    bool flag = DInstance::DynamicToStatic(d1, false, false, outer);
    UT_ASSERT(flag == true);
    CheckOuterInstance(outer);
}
NitsEndTest

NitsTest(Test5)
{
    NitsDisableFaultSim;

    DInstance d0(ZT("Inner"), DInstance::CLASS);
    d0.AddUint32(ZT("Key"), 32);
    d0.AddString(ZT("Str"), ZT("Hello"));

    DInstance d1(ZT("Outer"), DInstance::CLASS);
    d1.AddString(ZT("booleanScalar"), ZT("true"));
    d1.AddString(ZT("uint8Scalar"), ZT("8"));
    d1.AddString(ZT("uint8Scalar"), ZT("8"));
    d1.AddString(ZT("sint8Scalar"), ZT("-8"));
    d1.AddString(ZT("uint16Scalar"), ZT("16"));
    d1.AddString(ZT("sint16Scalar"), ZT("-16"));
    d1.AddString(ZT("uint32Scalar"), ZT("32"));
    d1.AddString(ZT("sint32Scalar"), ZT("-32"));
    d1.AddString(ZT("uint64Scalar"), ZT("64"));
    d1.AddString(ZT("sint64Scalar"), ZT("-64"));
    d1.AddString(ZT("real32Scalar"), ZT("32.32"));
    d1.AddString(ZT("real64Scalar"), ZT("64.64"));
    d1.AddString(ZT("char16Scalar"), ZT("16"));
    d1.AddString(ZT("datetimeScalar"), ZT("20091231120030.123456+360"));
    d1.AddString(ZT("stringScalar"), ZT("string"));
    d1.AddInstance(ZT("instanceScalar"), d0);

    d1.AddStringA(ZT("booleanArray"), MakeStrA(ZT("true"), ZT("false")));

    d1.AddStringA(ZT("uint8Array"), MakeStrA(ZT("8"), ZT("8")));
    d1.AddStringA(ZT("sint8Array"), MakeStrA(ZT("-8"), ZT("-8")));

    d1.AddStringA(ZT("uint16Array"), MakeStrA(ZT("16"), ZT("16")));
    d1.AddStringA(ZT("sint16Array"), MakeStrA(ZT("-16"), ZT("-16")));

    d1.AddStringA(ZT("uint32Array"), MakeStrA(ZT("32"), ZT("32")));
    d1.AddStringA(ZT("sint32Array"), MakeStrA(ZT("-32"), ZT("-32")));

    d1.AddStringA(ZT("uint64Array"), MakeStrA(ZT("64"), ZT("64")));
    d1.AddStringA(ZT("sint64Array"), MakeStrA(ZT("-64"), ZT("-64")));

    d1.AddStringA(ZT("real32Array"), MakeStrA(ZT("32.32"), ZT("32.32")));
    d1.AddStringA(ZT("real64Array"), MakeStrA(ZT("64.64"), ZT("64.64")));

    d1.AddStringA(ZT("char16Array"), MakeStrA(ZT("16"), ZT("16")));

    d1.AddStringA(ZT("datetimeArray"), MakeStrA(ZT("20091231120030.123456+360"), 
        ZT("20091231120030.123456+360")));

    d1.AddStringA(ZT("stringArray"), 
        MakeArray(String(ZT("string")), String(ZT("string"))));
    d1.AddInstanceA(ZT("instanceArray"), MakeArray(d0, d0));

    Outer_Class outer;
    bool flag = DInstance::DynamicToStatic(d1, false, false, outer);
    UT_ASSERT(flag == true);

    CheckOuterInstance(outer);

    DInstance dinst2;
    flag = DInstance::StaticToDynamic(outer, false, dinst2);
    UT_ASSERT(flag == true);

    Outer_Class outer2;
    flag = DInstance::DynamicToStatic(dinst2, false, false, outer2);
    UT_ASSERT(flag == true);

    CheckOuterInstance(outer2);
}
NitsEndTest

