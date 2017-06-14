// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#include "mi_type_test.hpp"


#include <cstdlib>
#include <mi_type.hpp>
#include <traits.hpp>


using test::mi_type_test;


/*ctor*/
mi_type_test::mi_type_test ()
{
    add_test (MAKE_TEST (mi_type_test::test01));
    add_test (MAKE_TEST (mi_type_test::test02));
    add_test (MAKE_TEST (mi_type_test::test03));
    add_test (MAKE_TEST (mi_type_test::test04));
    add_test (MAKE_TEST (mi_type_test::test05));
    add_test (MAKE_TEST (mi_type_test::test06));
    add_test (MAKE_TEST (mi_type_test::test07));
}


int
mi_type_test::test01 ()
{
    // test MI_Type<>::type_t
    int rval = EXIT_SUCCESS;
    if (!util::is_same<scx::MI_Type<MI_BOOLEAN>::type_t, MI_Boolean>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Type<MI_UINT8>::type_t, MI_Uint8>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Type<MI_SINT8>::type_t, MI_Sint8>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Type<MI_UINT16>::type_t, MI_Uint16>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Type<MI_SINT16>::type_t, MI_Sint16>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Type<MI_UINT32>::type_t, MI_Uint32>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Type<MI_SINT32>::type_t, MI_Sint32>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Type<MI_UINT64>::type_t, MI_Uint64>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Type<MI_SINT64>::type_t, MI_Sint64>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Type<MI_REAL32>::type_t, MI_Real32>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Type<MI_REAL64>::type_t, MI_Real64>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Type<MI_CHAR16>::type_t, MI_Char16>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Type<MI_DATETIME>::type_t, MI_Datetime>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Type<MI_STRING>::type_t,
                       std::basic_string<MI_Char> >::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_type_test::test02 ()
{
    // test MI_ArrayType<>::nested_type_t
    int rval = EXIT_SUCCESS;
    if (!util::is_same<scx::MI_ArrayType<MI_BOOLEANA>::nested_type_t,
                       MI_Boolean>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_ArrayType<MI_UINT8A>::nested_type_t,
                       MI_Uint8>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_ArrayType<MI_SINT8A>::nested_type_t,
                       MI_Sint8>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_ArrayType<MI_UINT16A>::nested_type_t,
                       MI_Uint16>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_ArrayType<MI_SINT16A>::nested_type_t,
                       MI_Sint16>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_ArrayType<MI_UINT32A>::nested_type_t,
                       MI_Uint32>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_ArrayType<MI_SINT32A>::nested_type_t,
                       MI_Sint32>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_ArrayType<MI_UINT64A>::nested_type_t,
                       MI_Uint64>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_ArrayType<MI_SINT64A>::nested_type_t,
                       MI_Sint64>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_ArrayType<MI_REAL32A>::nested_type_t,
                       MI_Real32>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_ArrayType<MI_REAL64A>::nested_type_t,
                       MI_Real64>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_ArrayType<MI_CHAR16A>::nested_type_t,
                       MI_Char16>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_ArrayType<MI_DATETIMEA>::nested_type_t,
                       MI_Datetime>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_ArrayType<MI_STRINGA>::nested_type_t,
                       std::basic_string<MI_Char> >::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_type_test::test03 ()
{
    // test MI_Limits<>::type_t
    int rval = EXIT_SUCCESS;
    if (!util::is_same<scx::MI_Limits<MI_UINT8>::type_t, MI_Uint8>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Limits<MI_SINT8>::type_t, MI_Sint8>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Limits<MI_UINT16>::type_t, MI_Uint16>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Limits<MI_SINT16>::type_t, MI_Sint16>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Limits<MI_UINT32>::type_t, MI_Uint32>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Limits<MI_SINT32>::type_t, MI_Sint32>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Limits<MI_UINT64>::type_t, MI_Uint64>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Limits<MI_SINT64>::type_t, MI_Sint64>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Limits<MI_REAL32>::type_t, MI_Real32>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Limits<MI_REAL64>::type_t, MI_Real64>::value)
    {
        rval = EXIT_FAILURE;
    }
    if (!util::is_same<scx::MI_Limits<MI_CHAR16>::type_t, MI_Char16>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_type_test::test04 ()
{
    // test MI_Limits<>::min
    int rval = EXIT_SUCCESS;
    if (scx::MI_Limits<MI_UINT8>::min () != 0)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_SINT8>::min () != SCHAR_MIN)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_UINT16>::min () != 0)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_SINT16>::min () != SHRT_MIN)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_UINT32>::min () != 0)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_SINT32>::min () != INT_MIN)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_UINT64>::min () != 0)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_SINT64>::min () != LLONG_MIN)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_REAL32>::min () != FLT_MIN)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_REAL64>::min () != DBL_MIN)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_CHAR16>::min () != 0)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_type_test::test05 ()
{
    // test MI_Limits<>::max
    int rval = EXIT_SUCCESS;
    if (scx::MI_Limits<MI_UINT8>::max () != UCHAR_MAX)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_SINT8>::max () != SCHAR_MAX)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_UINT16>::max () != USHRT_MAX)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_SINT16>::max () != SHRT_MAX)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_UINT32>::max () != UINT_MAX)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_SINT32>::max () != INT_MAX)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_UINT64>::max () != ULLONG_MAX)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_SINT64>::max () != LLONG_MAX)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_REAL32>::max () != FLT_MAX)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_REAL64>::max () != DBL_MAX)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::MI_Limits<MI_CHAR16>::max () != USHRT_MAX)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_type_test::test06 ()
{
    // test IsArray<>
    int rval = EXIT_SUCCESS;
    if (scx::IsArray<MI_BOOLEAN>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::IsArray<MI_UINT8>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::IsArray<MI_SINT8>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::IsArray<MI_UINT16>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::IsArray<MI_SINT16>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::IsArray<MI_UINT32>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::IsArray<MI_SINT32>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::IsArray<MI_UINT64>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::IsArray<MI_SINT64>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::IsArray<MI_REAL32>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::IsArray<MI_REAL64>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::IsArray<MI_CHAR16>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::IsArray<MI_DATETIME>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (scx::IsArray<MI_STRING>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (!scx::IsArray<MI_BOOLEANA>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (!scx::IsArray<MI_UINT8A>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (!scx::IsArray<MI_SINT8A>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (!scx::IsArray<MI_UINT16A>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (!scx::IsArray<MI_SINT16A>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (!scx::IsArray<MI_UINT32A>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (!scx::IsArray<MI_SINT32A>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (!scx::IsArray<MI_UINT64A>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (!scx::IsArray<MI_SINT64A>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (!scx::IsArray<MI_REAL32A>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (!scx::IsArray<MI_REAL64A>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (!scx::IsArray<MI_CHAR16A>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (!scx::IsArray<MI_DATETIMEA>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    if (!scx::IsArray<MI_STRINGA>::VALUE)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
mi_type_test::test07 ()
{
    // test Type_to_ID
    int rval = EXIT_SUCCESS;
    if (MI_UINT8 != scx::Type_to_ID<MI_Uint8>::ID)
    {
        rval = EXIT_FAILURE;
    }
    if (MI_SINT8 != scx::Type_to_ID<MI_Sint8>::ID)
    {
        rval = EXIT_FAILURE;
    }
    if (MI_UINT16 != scx::Type_to_ID<MI_Uint16>::ID)
    {
        rval = EXIT_FAILURE;
    }
    if (MI_SINT16 != scx::Type_to_ID<MI_Sint16>::ID)
    {
        rval = EXIT_FAILURE;
    }
    if (MI_UINT32 != scx::Type_to_ID<MI_Uint32>::ID)
    {
        rval = EXIT_FAILURE;
    }
    if (MI_SINT32 != scx::Type_to_ID<MI_Sint32>::ID)
    {
        rval = EXIT_FAILURE;
    }
    if (MI_UINT64 != scx::Type_to_ID<MI_Uint64>::ID)
    {
        rval = EXIT_FAILURE;
    }
    if (MI_SINT64 != scx::Type_to_ID<MI_Sint64>::ID)
    {
        rval = EXIT_FAILURE;
    }
    if (MI_REAL32 != scx::Type_to_ID<MI_Real32>::ID)
    {
        rval = EXIT_FAILURE;
    }
    if (MI_REAL64 != scx::Type_to_ID<MI_Real64>::ID)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}
