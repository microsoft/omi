// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#ifndef INCLUDED_TRAITS_TEST_HPP
#define INCLUDED_TRAITS_TEST_HPP


#include "test_helper.hpp"


namespace test
{


class integral_constant_test : public test_class<integral_constant_test>
{
public:
    /*ctor*/ integral_constant_test ();

    int test01 ();
    int test02 ();
    int test03 ();
    int test04 ();
};


class is_lvalue_reference_test : public test_class<is_lvalue_reference_test>
{
public:
    /*ctor*/ is_lvalue_reference_test ();

    int test01 ();
    int test02 ();
    int test03 ();
};


class is_pointer_test : public test_class<is_pointer_test>
{
public:
    /*ctor*/ is_pointer_test ();

    int test01 ();
    int test02 ();
    int test03 ();
};


class is_reference_test : public test_class<is_reference_test>
{
public:
    /*ctor*/ is_reference_test ();

    int test01 ();
    int test02 ();
    int test03 ();
};


class conditional_test : public test_class<conditional_test>
{
public:
    /*ctor*/ conditional_test ();

    int test01 ();
    int test02 ();
};


class is_same_test : public test_class<is_same_test>
{
public:
    /*ctor*/ is_same_test ();

    int test01 ();
    int test02 ();
    int test03 ();
    int test04 ();
    int test05 ();
    int test06 ();
    int test07 ();
};


class remove_reference_test : public test_class<remove_reference_test>
{
public:
    /*ctor*/ remove_reference_test ();

    int test01 ();
    int test02 ();
    int test03 ();
};


class remove_pointer_test : public test_class<remove_pointer_test>
{
public:
    /*ctor*/ remove_pointer_test ();

    int test01 ();
    int test02 ();
    int test03 ();
};


class remove_const_test : public test_class<remove_const_test>
{
public:
    /*ctor*/ remove_const_test ();

    int test01 ();
    int test02 ();
    int test03 ();
    int test04 ();
    int test05 ();
};


class remove_volatile_test : public test_class<remove_volatile_test>
{
public:
    /*ctor*/ remove_volatile_test ();

    int test01 ();
    int test02 ();
    int test03 ();
    int test04 ();
    int test05 ();
};


class remove_cv_test : public test_class<remove_cv_test>
{
public:
    /*ctor*/ remove_cv_test ();

    int test01 ();
    int test02 ();
    int test03 ();
    int test04 ();
    int test05 ();
};


class is_integral_test : public test_class<is_integral_test>
{
public:
    /*ctor*/ is_integral_test ();

    int test01 ();
    int test02 ();
    int test03 ();
    int test04 ();
    int test05 ();
};


class is_floating_point_test : public test_class<is_floating_point_test>
{
public:
    /*ctor*/ is_floating_point_test ();

    int test01 ();
    int test02 ();
    int test03 ();
    int test04 ();
    int test05 ();
};


class is_arithmetic_test : public test_class<is_arithmetic_test>
{
public:
    /*ctor*/ is_arithmetic_test ();

    int test01 ();
    int test02 ();
    int test03 ();
    int test04 ();
    int test05 ();
};


class is_signed_test : public test_class<is_signed_test>
{
public:
    /*ctor*/ is_signed_test ();

    int test01 ();
    int test02 ();
};


class is_unsigned_test : public test_class<is_unsigned_test>
{
public:
    /*ctor*/ is_unsigned_test ();

    int test01 ();
    int test02 ();
};


} // namespace test


#endif // INCLUDED_TRAITS_TEST_HPP
