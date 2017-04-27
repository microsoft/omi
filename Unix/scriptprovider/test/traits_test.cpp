#include "traits_test.hpp"


#include <cstdlib>
#include <traits.hpp>


using test::integral_constant_test;
using test::is_lvalue_reference_test;
using test::is_pointer_test;
using test::is_reference_test;
using test::conditional_test;
using test::is_same_test;
using test::remove_reference_test;
using test::remove_pointer_test;
using test::remove_const_test;
using test::remove_volatile_test;
using test::remove_cv_test;
using test::is_integral_test;
using test::is_floating_point_test;
using test::is_arithmetic_test;
using test::is_signed_test;
using test::is_unsigned_test;


namespace
{


class Foo {};
class Bar {};


} // namespace (unnamed)


// class integral_constant_test definitions
//------------------------------------------------------------------------------
/*ctor*/
integral_constant_test::integral_constant_test ()
{
    add_test (MAKE_TEST (integral_constant_test::test01));
    add_test (MAKE_TEST (integral_constant_test::test02));
    add_test (MAKE_TEST (integral_constant_test::test03));
}


int
integral_constant_test::test01 ()
{
    int rval = EXIT_SUCCESS;

    typedef util::integral_constant<bool, true> bool_const;
    bool_const b_type;
    bool_const::value_type b_value = b_type;
    if (b_value != true)
    {
        rval = EXIT_FAILURE;
    }
    typedef util::integral_constant<char, 'c'> char_const;
    char_const c_type0;
    char_const::type c_type1;
    char_const::value_type c_value0 = c_type0.value;
    char_const::value_type c_value1 = c_type1;
    if (c_value0 != 'c' ||
        c_value1 != 'c' ||
        'x' == c_type0.value ||
        'x' == c_type0)
    {
        rval = EXIT_FAILURE;
    }
    typedef util::integral_constant<unsigned char, 1> uchar_const;
    uchar_const uchar_type;
    uchar_const::value_type uc_value = uchar_type;
    if (uc_value != 1)
    {
        rval = EXIT_FAILURE;
    }
    typedef util::integral_constant<signed char, -1> schar_const;
    schar_const schar_type;
    schar_const::value_type sc_value = schar_type;
    if (sc_value != -1)
    {
        rval = EXIT_FAILURE;
    }
    typedef util::integral_constant<wchar_t, L'w'> wchar_const;
    wchar_const wchar_type;
    wchar_const::value_type wc_value = wchar_type;
    if (wc_value != L'w')
    {
        rval = EXIT_FAILURE;
    }
    typedef util::integral_constant<short, -2> short_const;
    short_const short_type;
    short_const::value_type s_value = short_type;
    if (s_value != -2)
    {
        rval = EXIT_FAILURE;
    }
    typedef util::integral_constant<unsigned short, 2> ushort_const;
    ushort_const ushort_type;
    ushort_const::value_type us_value = ushort_type;
    if (us_value != 2)
    {
        rval = EXIT_FAILURE;
    }
    typedef util::integral_constant<int, -4> int_const;
    int_const int_type;
    int_const::value_type i_value = int_type;
    if (i_value != -4)
    {
        rval = EXIT_FAILURE;
    }
    typedef util::integral_constant<unsigned int, 4> uint_const;
    uint_const uint_type;
    uint_const::value_type ui_value = uint_type;
    if (ui_value != 4)
    {
        rval = EXIT_FAILURE;
    }
    typedef util::integral_constant<long, -4> long_const;
    long_const long_type;
    long_const::value_type l_value = long_type;
    if (l_value != -4)
    {
        rval = EXIT_FAILURE;
    }
    typedef util::integral_constant<unsigned long, 4> ulong_const;
    ulong_const ulong_type;
    ulong_const::value_type ul_value = ulong_type;
    if (ul_value != 4)
    {
        rval = EXIT_FAILURE;
    }
    typedef util::integral_constant<long long, -8> long_long_const;
    long_long_const long_long_type;
    long_long_const::value_type ll_value = long_long_type;
    if (ll_value != -8)
    {
        rval = EXIT_FAILURE;
    }
    typedef util::integral_constant<unsigned long long, 8> ulong_long_const;
    ulong_long_const ulong_long_type;
    ulong_long_const::value_type ull_value = ulong_long_type;
    if (ull_value != 8)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
integral_constant_test::test02 ()
{
    int rval = EXIT_SUCCESS;
    util::true_type::value_type t_value0 = util::true_type::value;
    typedef util::true_type true_const;
    true_const t_type;
    true_const::value_type t_value1 = t_type;
    if (t_value0 != true ||
        t_value1 != true ||
        util::true_type::value != true)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
integral_constant_test::test03 ()
{
    int rval = EXIT_SUCCESS;
    util::false_type::value_type f_value0 = util::false_type::value;
    typedef util::false_type false_const;
    false_const f_type;
    false_const::value_type f_value1 = f_type;
    if (f_value0 != false ||
        f_value1 != false ||
        util::false_type::value != false)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


// is_lvalue_reference_test defintions
//------------------------------------------------------------------------------
/*ctor*/
is_lvalue_reference_test::is_lvalue_reference_test ()
{
    add_test (MAKE_TEST (is_lvalue_reference_test::test01));
    add_test (MAKE_TEST (is_lvalue_reference_test::test02));
    add_test (MAKE_TEST (is_lvalue_reference_test::test03));
}


int
is_lvalue_reference_test::test01 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_lvalue_reference<bool&>::value ||
        !util::is_lvalue_reference<char&>::value ||
        !util::is_lvalue_reference<signed char&>::value ||
        !util::is_lvalue_reference<unsigned char&>::value ||
        !util::is_lvalue_reference<wchar_t&>::value ||
        !util::is_lvalue_reference<short&>::value ||
        !util::is_lvalue_reference<unsigned short&>::value ||
        !util::is_lvalue_reference<int&>::value ||
        !util::is_lvalue_reference<unsigned int&>::value ||
        !util::is_lvalue_reference<long&>::value ||
        !util::is_lvalue_reference<unsigned long&>::value ||
        !util::is_lvalue_reference<long long&>::value ||
        !util::is_lvalue_reference<unsigned long long&>::value ||
        !util::is_lvalue_reference<float&>::value ||
        !util::is_lvalue_reference<double&>::value ||
        !util::is_lvalue_reference<long double&>::value ||
        !util::is_lvalue_reference<Foo&>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_lvalue_reference_test::test02 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_lvalue_reference<bool>::value ||
        util::is_lvalue_reference<char>::value ||
        util::is_lvalue_reference<signed char>::value ||
        util::is_lvalue_reference<unsigned char>::value ||
        util::is_lvalue_reference<wchar_t>::value ||
        util::is_lvalue_reference<short>::value ||
        util::is_lvalue_reference<unsigned short>::value ||
        util::is_lvalue_reference<int>::value ||
        util::is_lvalue_reference<unsigned int>::value ||
        util::is_lvalue_reference<long>::value ||
        util::is_lvalue_reference<unsigned long>::value ||
        util::is_lvalue_reference<long long>::value ||
        util::is_lvalue_reference<unsigned long long>::value ||
        util::is_lvalue_reference<float>::value ||
        util::is_lvalue_reference<double>::value ||
        util::is_lvalue_reference<long double>::value ||
        util::is_lvalue_reference<Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_lvalue_reference_test::test03 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_lvalue_reference<bool*>::value ||
        util::is_lvalue_reference<char*>::value ||
        util::is_lvalue_reference<signed char*>::value ||
        util::is_lvalue_reference<unsigned char*>::value ||
        util::is_lvalue_reference<wchar_t*>::value ||
        util::is_lvalue_reference<short*>::value ||
        util::is_lvalue_reference<unsigned short*>::value ||
        util::is_lvalue_reference<int*>::value ||
        util::is_lvalue_reference<unsigned int*>::value ||
        util::is_lvalue_reference<long*>::value ||
        util::is_lvalue_reference<unsigned long*>::value ||
        util::is_lvalue_reference<long long*>::value ||
        util::is_lvalue_reference<unsigned long long*>::value ||
        util::is_lvalue_reference<float*>::value ||
        util::is_lvalue_reference<double*>::value ||
        util::is_lvalue_reference<long double*>::value ||
        util::is_lvalue_reference<Foo*>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


// is_pointer_test defintions
//------------------------------------------------------------------------------
/*ctor*/
is_pointer_test::is_pointer_test ()
{
    add_test (MAKE_TEST (is_pointer_test::test01));
    add_test (MAKE_TEST (is_pointer_test::test02));
    add_test (MAKE_TEST (is_pointer_test::test03));
}


int
is_pointer_test::test01 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_pointer<bool*>::value ||
        !util::is_pointer<char*>::value ||
        !util::is_pointer<signed char*>::value ||
        !util::is_pointer<unsigned char*>::value ||
        !util::is_pointer<wchar_t*>::value ||
        !util::is_pointer<short*>::value ||
        !util::is_pointer<unsigned short*>::value ||
        !util::is_pointer<int*>::value ||
        !util::is_pointer<unsigned int*>::value ||
        !util::is_pointer<long*>::value ||
        !util::is_pointer<unsigned long*>::value ||
        !util::is_pointer<long long*>::value ||
        !util::is_pointer<unsigned long long*>::value ||
        !util::is_pointer<float*>::value ||
        !util::is_pointer<double*>::value ||
        !util::is_pointer<long double*>::value ||
        !util::is_pointer<Foo*>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_pointer_test::test02 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_pointer<bool>::value ||
        util::is_pointer<char>::value ||
        util::is_pointer<signed char>::value ||
        util::is_pointer<unsigned char>::value ||
        util::is_pointer<wchar_t>::value ||
        util::is_pointer<short>::value ||
        util::is_pointer<unsigned short>::value ||
        util::is_pointer<int>::value ||
        util::is_pointer<unsigned int>::value ||
        util::is_pointer<long>::value ||
        util::is_pointer<unsigned long>::value ||
        util::is_pointer<long long>::value ||
        util::is_pointer<unsigned long long>::value ||
        util::is_pointer<float>::value ||
        util::is_pointer<double>::value ||
        util::is_pointer<long double>::value ||
        util::is_pointer<Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_pointer_test::test03 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_pointer<bool&>::value ||
        util::is_pointer<char&>::value ||
        util::is_pointer<signed char&>::value ||
        util::is_pointer<unsigned char&>::value ||
        util::is_pointer<wchar_t&>::value ||
        util::is_pointer<short&>::value ||
        util::is_pointer<unsigned short&>::value ||
        util::is_pointer<int&>::value ||
        util::is_pointer<unsigned int&>::value ||
        util::is_pointer<long&>::value ||
        util::is_pointer<unsigned long&>::value ||
        util::is_pointer<long long&>::value ||
        util::is_pointer<unsigned long long&>::value ||
        util::is_pointer<float&>::value ||
        util::is_pointer<double&>::value ||
        util::is_pointer<long double&>::value ||
        util::is_pointer<Foo&>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


// is_reference_test defintions
//------------------------------------------------------------------------------
/*ctor*/
is_reference_test::is_reference_test ()
{
    add_test (MAKE_TEST (is_reference_test::test01));
    add_test (MAKE_TEST (is_reference_test::test02));
    add_test (MAKE_TEST (is_reference_test::test03));
}


int
is_reference_test::test01 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_reference<bool&>::value ||
        !util::is_reference<char&>::value ||
        !util::is_reference<signed char&>::value ||
        !util::is_reference<unsigned char&>::value ||
        !util::is_reference<wchar_t&>::value ||
        !util::is_reference<short&>::value ||
        !util::is_reference<unsigned short&>::value ||
        !util::is_reference<int&>::value ||
        !util::is_reference<unsigned int&>::value ||
        !util::is_reference<long&>::value ||
        !util::is_reference<unsigned long&>::value ||
        !util::is_reference<long long&>::value ||
        !util::is_reference<unsigned long long&>::value ||
        !util::is_reference<float&>::value ||
        !util::is_reference<double&>::value ||
        !util::is_reference<long double&>::value ||
        !util::is_reference<Foo&>::value ||
        !util::is_reference<bool const&>::value ||
        !util::is_reference<char const&>::value ||
        !util::is_reference<signed char const&>::value ||
        !util::is_reference<unsigned char const&>::value ||
        !util::is_reference<wchar_t const&>::value ||
        !util::is_reference<short const&>::value ||
        !util::is_reference<unsigned short const&>::value ||
        !util::is_reference<int const&>::value ||
        !util::is_reference<unsigned int const&>::value ||
        !util::is_reference<long const&>::value ||
        !util::is_reference<unsigned long const&>::value ||
        !util::is_reference<long long const&>::value ||
        !util::is_reference<unsigned long long const&>::value ||
        !util::is_reference<float const&>::value ||
        !util::is_reference<double const&>::value ||
        !util::is_reference<long double const&>::value ||
        !util::is_reference<Foo const&>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_reference_test::test02 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_reference<bool>::value ||
        util::is_reference<char>::value ||
        util::is_reference<signed char>::value ||
        util::is_reference<unsigned char>::value ||
        util::is_reference<wchar_t>::value ||
        util::is_reference<short>::value ||
        util::is_reference<unsigned short>::value ||
        util::is_reference<int>::value ||
        util::is_reference<unsigned int>::value ||
        util::is_reference<long>::value ||
        util::is_reference<unsigned long>::value ||
        util::is_reference<long long>::value ||
        util::is_reference<unsigned long long>::value ||
        util::is_reference<float>::value ||
        util::is_reference<double>::value ||
        util::is_reference<long double>::value ||
        util::is_reference<Foo>::value ||
        util::is_reference<bool const>::value ||
        util::is_reference<char const>::value ||
        util::is_reference<signed char const>::value ||
        util::is_reference<unsigned char const>::value ||
        util::is_reference<wchar_t const>::value ||
        util::is_reference<short const>::value ||
        util::is_reference<unsigned short const>::value ||
        util::is_reference<int const>::value ||
        util::is_reference<unsigned int const>::value ||
        util::is_reference<long const>::value ||
        util::is_reference<unsigned long const>::value ||
        util::is_reference<long long const>::value ||
        util::is_reference<unsigned long long const>::value ||
        util::is_reference<float const>::value ||
        util::is_reference<double const>::value ||
        util::is_reference<long double const>::value ||
        util::is_reference<Foo const>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_reference_test::test03 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_reference<bool*>::value ||
        util::is_reference<char*>::value ||
        util::is_reference<signed char*>::value ||
        util::is_reference<unsigned char*>::value ||
        util::is_reference<wchar_t*>::value ||
        util::is_reference<short*>::value ||
        util::is_reference<unsigned short*>::value ||
        util::is_reference<int*>::value ||
        util::is_reference<unsigned int*>::value ||
        util::is_reference<long*>::value ||
        util::is_reference<unsigned long*>::value ||
        util::is_reference<long long*>::value ||
        util::is_reference<unsigned long long*>::value ||
        util::is_reference<float*>::value ||
        util::is_reference<double*>::value ||
        util::is_reference<long double*>::value ||
        util::is_reference<Foo*>::value ||
        util::is_reference<bool const*>::value ||
        util::is_reference<char const*>::value ||
        util::is_reference<signed char const*>::value ||
        util::is_reference<unsigned char const*>::value ||
        util::is_reference<wchar_t const*>::value ||
        util::is_reference<short const*>::value ||
        util::is_reference<unsigned short const*>::value ||
        util::is_reference<int const*>::value ||
        util::is_reference<unsigned int const*>::value ||
        util::is_reference<long const*>::value ||
        util::is_reference<unsigned long const*>::value ||
        util::is_reference<long long const*>::value ||
        util::is_reference<unsigned long long const*>::value ||
        util::is_reference<float const*>::value ||
        util::is_reference<double const*>::value ||
        util::is_reference<long double const*>::value ||
        util::is_reference<Foo const*>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


// class conditional_test definitions
//------------------------------------------------------------------------------
/*ctor*/
conditional_test::conditional_test ()
{
    add_test (MAKE_TEST (conditional_test::test01));
    add_test (MAKE_TEST (conditional_test::test02));
}


int
conditional_test::test01 ()
{
    using namespace util;
    int rval = EXIT_SUCCESS;
    if (true != conditional<true, true_type, false_type>::type::value ||
        false != conditional<true, false_type, true_type>::type::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
conditional_test::test02 ()
{
    using namespace util;
    int rval = EXIT_SUCCESS;
    if (false != conditional<false, true_type, false_type>::type::value ||
        true != conditional<false, false_type, true_type>::type::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


// class is_same_test definitions
//------------------------------------------------------------------------------
/*ctor*/
is_same_test::is_same_test ()
{
    add_test (MAKE_TEST (is_same_test::test01));
    add_test (MAKE_TEST (is_same_test::test02));
    add_test (MAKE_TEST (is_same_test::test03));
    add_test (MAKE_TEST (is_same_test::test04));
    add_test (MAKE_TEST (is_same_test::test05));
    add_test (MAKE_TEST (is_same_test::test06));
    add_test (MAKE_TEST (is_same_test::test07));
}


int
is_same_test::test01 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<bool, bool>::value ||
        !util::is_same<char, char>::value ||
        !util::is_same<signed char, signed char>::value ||
        !util::is_same<unsigned char, unsigned char>::value ||
        !util::is_same<wchar_t, wchar_t>::value ||
        !util::is_same<short, short>::value ||
        !util::is_same<unsigned short, unsigned short>::value ||
        !util::is_same<int, int>::value ||
        !util::is_same<unsigned int, unsigned int>::value ||
        !util::is_same<long, long>::value ||
        !util::is_same<unsigned long, unsigned long>::value ||
        !util::is_same<long long, long long>::value ||
        !util::is_same<unsigned long long, unsigned long long>::value ||
        !util::is_same<float, float>::value ||
        !util::is_same<double, double>::value ||
        !util::is_same<long double, long double>::value ||
        !util::is_same<Foo, Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_same_test::test02 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<bool&, bool&>::value ||
        !util::is_same<char&, char&>::value ||
        !util::is_same<signed char&, signed char&>::value ||
        !util::is_same<unsigned char&, unsigned char&>::value ||
        !util::is_same<wchar_t&, wchar_t&>::value ||
        !util::is_same<short&, short&>::value ||
        !util::is_same<unsigned short&, unsigned short&>::value ||
        !util::is_same<int&, int&>::value ||
        !util::is_same<unsigned int&, unsigned int&>::value ||
        !util::is_same<long&, long&>::value ||
        !util::is_same<unsigned long&, unsigned long&>::value ||
        !util::is_same<long long&, long long&>::value ||
        !util::is_same<unsigned long long&, unsigned long long&>::value ||
        !util::is_same<float&, float&>::value ||
        !util::is_same<double&, double&>::value ||
        !util::is_same<long double&, long double&>::value ||
        !util::is_same<Foo&, Foo&>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_same_test::test03 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<bool*, bool*>::value ||
        !util::is_same<char*, char*>::value ||
        !util::is_same<signed char*, signed char*>::value ||
        !util::is_same<unsigned char*, unsigned char*>::value ||
        !util::is_same<wchar_t*, wchar_t*>::value ||
        !util::is_same<short*, short*>::value ||
        !util::is_same<unsigned short*, unsigned short*>::value ||
        !util::is_same<int*, int*>::value ||
        !util::is_same<unsigned int*, unsigned int*>::value ||
        !util::is_same<long*, long*>::value ||
        !util::is_same<unsigned long*, unsigned long*>::value ||
        !util::is_same<long long*, long long*>::value ||
        !util::is_same<unsigned long long*, unsigned long long*>::value ||
        !util::is_same<float*, float*>::value ||
        !util::is_same<double*, double*>::value ||
        !util::is_same<long double*, long double*>::value ||
        !util::is_same<Foo*, Foo*>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_same_test::test04 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_same<bool, bool&>::value ||
        util::is_same<char, char&>::value ||
        util::is_same<signed char, signed char&>::value ||
        util::is_same<unsigned char, unsigned char&>::value ||
        util::is_same<wchar_t, wchar_t&>::value ||
        util::is_same<short, short&>::value ||
        util::is_same<unsigned short, unsigned short&>::value ||
        util::is_same<int, int&>::value ||
        util::is_same<unsigned int, unsigned int&>::value ||
        util::is_same<long, long&>::value ||
        util::is_same<unsigned long, unsigned long&>::value ||
        util::is_same<long long, long long&>::value ||
        util::is_same<unsigned long long, unsigned long long&>::value ||
        util::is_same<float, float&>::value ||
        util::is_same<double, double&>::value ||
        util::is_same<long double, long double&>::value ||
        util::is_same<Foo, Foo&>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_same_test::test05 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_same<bool, bool*>::value ||
        util::is_same<char, char*>::value ||
        util::is_same<signed char, signed char*>::value ||
        util::is_same<unsigned char, unsigned char*>::value ||
        util::is_same<wchar_t, wchar_t*>::value ||
        util::is_same<short, short*>::value ||
        util::is_same<unsigned short, unsigned short*>::value ||
        util::is_same<int, int*>::value ||
        util::is_same<unsigned int, unsigned int*>::value ||
        util::is_same<long, long*>::value ||
        util::is_same<unsigned long, unsigned long*>::value ||
        util::is_same<long long, long long*>::value ||
        util::is_same<unsigned long long, unsigned long long*>::value ||
        util::is_same<float, float*>::value ||
        util::is_same<double, double*>::value ||
        util::is_same<long double, long double*>::value ||
        util::is_same<Foo, Foo*>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_same_test::test06 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_same<bool, char>::value ||
        util::is_same<char, signed char>::value ||
        util::is_same<signed char, unsigned char>::value ||
        util::is_same<unsigned char, wchar_t>::value ||
        util::is_same<wchar_t, short>::value ||
        util::is_same<short, unsigned short>::value ||
        util::is_same<unsigned short, int>::value ||
        util::is_same<int, unsigned int>::value ||
        util::is_same<unsigned int, long>::value ||
        util::is_same<long, unsigned long>::value ||
        util::is_same<unsigned long, long long>::value ||
        util::is_same<long long, unsigned long long>::value ||
        util::is_same<unsigned long long, float>::value ||
        util::is_same<float, double>::value ||
        util::is_same<double, long double>::value ||
        util::is_same<long double, bool>::value ||
        util::is_same<Foo&, Bar>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_same_test::test07 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_same<bool, bool const>::value ||
        util::is_same<char, char const>::value ||
        util::is_same<signed char, signed char const>::value ||
        util::is_same<unsigned char, unsigned char const>::value ||
        util::is_same<wchar_t, wchar_t const>::value ||
        util::is_same<short, short const>::value ||
        util::is_same<unsigned short, unsigned short const>::value ||
        util::is_same<int, int const>::value ||
        util::is_same<unsigned int, unsigned int const>::value ||
        util::is_same<long, long const>::value ||
        util::is_same<unsigned long, unsigned long const>::value ||
        util::is_same<long long, long long const>::value ||
        util::is_same<
            unsigned long long, unsigned long long const>::value ||
        util::is_same<float, float const>::value ||
        util::is_same<double, double const>::value ||
        util::is_same<long double, long double const>::value ||
        util::is_same<Foo, Foo const>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


// class remove_reference_test definitions
//------------------------------------------------------------------------------
/*ctor*/
remove_reference_test::remove_reference_test ()
{
    add_test (MAKE_TEST (remove_reference_test::test01));
    add_test (MAKE_TEST (remove_reference_test::test02));
    add_test (MAKE_TEST (remove_reference_test::test03));
}


int
remove_reference_test::test01 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_reference<bool&>::type,
            bool>::value ||
        !util::is_same<
            util::remove_reference<char&>::type,
            char>::value ||
        !util::is_same<
            util::remove_reference<signed char&>::type,
            signed char>::value ||
        !util::is_same<
            util::remove_reference<unsigned char&>::type,
            unsigned char>::value ||
        !util::is_same<
            util::remove_reference<wchar_t&>::type,
            wchar_t>::value ||
        !util::is_same<
            util::remove_reference<short&>::type,
            short>::value ||
        !util::is_same<
            util::remove_reference<unsigned short&>::type,
            unsigned short>::value ||
        !util::is_same<
            util::remove_reference<int&>::type,
            int>::value ||
        !util::is_same<
            util::remove_reference<unsigned int&>::type,
            unsigned int>::value ||
        !util::is_same<
            util::remove_reference<long&>::type,
            long>::value ||
        !util::is_same<
            util::remove_reference<unsigned long&>::type,
            unsigned long>::value ||
        !util::is_same<
            util::remove_reference<long long&>::type,
            long long>::value ||
        !util::is_same<
            util::remove_reference<unsigned long long&>::type,
            unsigned long long>::value ||
        !util::is_same<
            util::remove_reference<float&>::type,
            float>::value ||
        !util::is_same<
            util::remove_reference<double&>::type,
            double>::value ||
        !util::is_same<
            util::remove_reference<long double&>::type,
            long double>::value ||
        !util::is_same<
            util::remove_reference<Foo&>::type,
            Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
remove_reference_test::test02 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_reference<bool>::type,
            bool>::value ||
        !util::is_same<
            util::remove_reference<char>::type,
            char>::value ||
        !util::is_same<
            util::remove_reference<signed char>::type,
            signed char>::value ||
        !util::is_same<
            util::remove_reference<unsigned char>::type,
            unsigned char>::value ||
        !util::is_same<
            util::remove_reference<wchar_t>::type,
            wchar_t>::value ||
        !util::is_same<
            util::remove_reference<short>::type,
            short>::value ||
        !util::is_same<
            util::remove_reference<unsigned short>::type,
            unsigned short>::value ||
        !util::is_same<
            util::remove_reference<int>::type,
            int>::value ||
        !util::is_same<
            util::remove_reference<unsigned int>::type,
            unsigned int>::value ||
        !util::is_same<
            util::remove_reference<long>::type,
            long>::value ||
        !util::is_same<
            util::remove_reference<unsigned long>::type,
            unsigned long>::value ||
        !util::is_same<
            util::remove_reference<long long>::type,
            long long>::value ||
        !util::is_same<
            util::remove_reference<unsigned long long>::type,
            unsigned long long>::value ||
        !util::is_same<
            util::remove_reference<float>::type,
            float>::value ||
        !util::is_same<
            util::remove_reference<double>::type,
            double>::value ||
        !util::is_same<
            util::remove_reference<long double>::type,
            long double>::value ||
        !util::is_same<
            util::remove_reference<Foo>::type,
            Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
remove_reference_test::test03 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_reference<bool*>::type,
            bool*>::value ||
        !util::is_same<
            util::remove_reference<char*>::type,
            char*>::value ||
        !util::is_same<
            util::remove_reference<signed char*>::type,
            signed char*>::value ||
        !util::is_same<
            util::remove_reference<unsigned char*>::type,
            unsigned char*>::value ||
        !util::is_same<
            util::remove_reference<wchar_t*>::type,
            wchar_t*>::value ||
        !util::is_same<
            util::remove_reference<short*>::type,
            short*>::value ||
        !util::is_same<
            util::remove_reference<unsigned short*>::type,
            unsigned short*>::value ||
        !util::is_same<
            util::remove_reference<int*>::type,
            int*>::value ||
        !util::is_same<
            util::remove_reference<unsigned int*>::type,
            unsigned int*>::value ||
        !util::is_same<
            util::remove_reference<long*>::type,
            long*>::value ||
        !util::is_same<
            util::remove_reference<unsigned long*>::type,
            unsigned long*>::value ||
        !util::is_same<
            util::remove_reference<long long*>::type,
            long long*>::value ||
        !util::is_same<
            util::remove_reference<unsigned long long*>::type,
            unsigned long long*>::value ||
        !util::is_same<
            util::remove_reference<float*>::type,
            float*>::value ||
        !util::is_same<
            util::remove_reference<double*>::type,
            double*>::value ||
        !util::is_same<
            util::remove_reference<long double*>::type,
            long double*>::value ||
        !util::is_same<
            util::remove_reference<Foo*>::type,
            Foo*>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


// class remove_pointer_test definitions
//------------------------------------------------------------------------------
/*ctor*/
remove_pointer_test::remove_pointer_test ()
{
    add_test (MAKE_TEST (remove_pointer_test::test01));
    add_test (MAKE_TEST (remove_pointer_test::test02));
    add_test (MAKE_TEST (remove_pointer_test::test03));
}


int
remove_pointer_test::test01 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_pointer<bool*>::type,
            bool>::value ||
        !util::is_same<
            util::remove_pointer<char*>::type,
            char>::value ||
        !util::is_same<
            util::remove_pointer<signed char*>::type,
            signed char>::value ||
        !util::is_same<
            util::remove_pointer<unsigned char*>::type,
            unsigned char>::value ||
        !util::is_same<
            util::remove_pointer<wchar_t*>::type,
            wchar_t>::value ||
        !util::is_same<
            util::remove_pointer<short*>::type,
            short>::value ||
        !util::is_same<
            util::remove_pointer<unsigned short*>::type,
            unsigned short>::value ||
        !util::is_same<
            util::remove_pointer<int*>::type,
            int>::value ||
        !util::is_same<
            util::remove_pointer<unsigned int*>::type,
            unsigned int>::value ||
        !util::is_same<
            util::remove_pointer<long*>::type,
            long>::value ||
        !util::is_same<
            util::remove_pointer<unsigned long*>::type,
            unsigned long>::value ||
        !util::is_same<
            util::remove_pointer<long long*>::type,
            long long>::value ||
        !util::is_same<
            util::remove_pointer<unsigned long long*>::type,
            unsigned long long>::value ||
        !util::is_same<
            util::remove_pointer<float*>::type,
            float>::value ||
        !util::is_same<
            util::remove_pointer<double*>::type,
            double>::value ||
        !util::is_same<
            util::remove_pointer<long double*>::type,
            long double>::value ||
        !util::is_same<
            util::remove_pointer<Foo*>::type,
            Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
remove_pointer_test::test02 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_pointer<bool>::type,
            bool>::value ||
        !util::is_same<
            util::remove_pointer<char>::type,
            char>::value ||
        !util::is_same<
            util::remove_pointer<signed char>::type,
            signed char>::value ||
        !util::is_same<
            util::remove_pointer<unsigned char>::type,
            unsigned char>::value ||
        !util::is_same<
            util::remove_pointer<wchar_t>::type,
            wchar_t>::value ||
        !util::is_same<
            util::remove_pointer<short>::type,
            short>::value ||
        !util::is_same<
            util::remove_pointer<unsigned short>::type,
            unsigned short>::value ||
        !util::is_same<
            util::remove_pointer<int>::type,
            int>::value ||
        !util::is_same<
            util::remove_pointer<unsigned int>::type,
            unsigned int>::value ||
        !util::is_same<
            util::remove_pointer<long>::type,
            long>::value ||
        !util::is_same<
            util::remove_pointer<unsigned long>::type,
            unsigned long>::value ||
        !util::is_same<
            util::remove_pointer<long long>::type,
            long long>::value ||
        !util::is_same<
            util::remove_pointer<unsigned long long>::type,
            unsigned long long>::value ||
        !util::is_same<
            util::remove_pointer<float>::type,
            float>::value ||
        !util::is_same<
            util::remove_pointer<double>::type,
            double>::value ||
        !util::is_same<
            util::remove_pointer<long double>::type,
            long double>::value ||
        !util::is_same<
            util::remove_pointer<Foo>::type,
            Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
remove_pointer_test::test03 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_pointer<bool&>::type,
            bool&>::value ||
        !util::is_same<
            util::remove_pointer<char&>::type,
            char&>::value ||
        !util::is_same<
            util::remove_pointer<signed char&>::type,
            signed char&>::value ||
        !util::is_same<
            util::remove_pointer<unsigned char&>::type,
            unsigned char&>::value ||
        !util::is_same<
            util::remove_pointer<wchar_t&>::type,
            wchar_t&>::value ||
        !util::is_same<
            util::remove_pointer<short&>::type,
            short&>::value ||
        !util::is_same<
            util::remove_pointer<unsigned short&>::type,
            unsigned short&>::value ||
        !util::is_same<
            util::remove_pointer<int&>::type,
            int&>::value ||
        !util::is_same<
            util::remove_pointer<unsigned int&>::type,
            unsigned int&>::value ||
        !util::is_same<
            util::remove_pointer<long&>::type,
            long&>::value ||
        !util::is_same<
            util::remove_pointer<unsigned long&>::type,
            unsigned long&>::value ||
        !util::is_same<
            util::remove_pointer<long long&>::type,
            long long&>::value ||
        !util::is_same<
            util::remove_pointer<unsigned long long&>::type,
            unsigned long long&>::value ||
        !util::is_same<
            util::remove_pointer<float&>::type,
            float&>::value ||
        !util::is_same<
            util::remove_pointer<double&>::type,
            double&>::value ||
        !util::is_same<
            util::remove_pointer<long double&>::type,
            long double&>::value ||
        !util::is_same<
            util::remove_pointer<Foo&>::type,
            Foo&>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


// class remove_const_test definitions
//------------------------------------------------------------------------------
/*ctor*/
remove_const_test::remove_const_test ()
{
    add_test (MAKE_TEST (remove_const_test::test01));
    add_test (MAKE_TEST (remove_const_test::test02));
    add_test (MAKE_TEST (remove_const_test::test03));
    add_test (MAKE_TEST (remove_const_test::test04));
    add_test (MAKE_TEST (remove_const_test::test05));
}


int
remove_const_test::test01 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_const<bool const>::type,
            bool>::value ||
        !util::is_same<
            util::remove_const<char const>::type,
            char>::value ||
        !util::is_same<
            util::remove_const<signed char const>::type,
            signed char>::value ||
        !util::is_same<
            util::remove_const<unsigned char const>::type,
            unsigned char>::value ||
        !util::is_same<
            util::remove_const<wchar_t const>::type,
            wchar_t>::value ||
        !util::is_same<
            util::remove_const<short const>::type,
            short>::value ||
        !util::is_same<
            util::remove_const<unsigned short const>::type,
            unsigned short>::value ||
        !util::is_same<
            util::remove_const<int const>::type,
            int>::value ||
        !util::is_same<
            util::remove_const<unsigned int const>::type,
            unsigned int>::value ||
        !util::is_same<
            util::remove_const<long const>::type,
            long>::value ||
        !util::is_same<
            util::remove_const<unsigned long const>::type,
            unsigned long>::value ||
        !util::is_same<
            util::remove_const<long long const>::type,
            long long>::value ||
        !util::is_same<
            util::remove_const<unsigned long long const>::type,
            unsigned long long>::value ||
        !util::is_same<
            util::remove_const<float const>::type,
            float>::value ||
        !util::is_same<
            util::remove_const<double const>::type,
            double>::value ||
        !util::is_same<
            util::remove_const<long double const>::type,
            long double>::value ||
        !util::is_same<
            util::remove_const<Foo const>::type,
            Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
remove_const_test::test02 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_const<bool>::type,
            bool>::value ||
        !util::is_same<
            util::remove_const<char>::type,
            char>::value ||
        !util::is_same<
            util::remove_const<signed char>::type,
            signed char>::value ||
        !util::is_same<
            util::remove_const<unsigned char>::type,
            unsigned char>::value ||
        !util::is_same<
            util::remove_const<wchar_t>::type,
            wchar_t>::value ||
        !util::is_same<
            util::remove_const<short>::type,
            short>::value ||
        !util::is_same<
            util::remove_const<unsigned short>::type,
            unsigned short>::value ||
        !util::is_same<
            util::remove_const<int>::type,
            int>::value ||
        !util::is_same<
            util::remove_const<unsigned int>::type,
            unsigned int>::value ||
        !util::is_same<
            util::remove_const<long>::type,
            long>::value ||
        !util::is_same<
            util::remove_const<unsigned long>::type,
            unsigned long>::value ||
        !util::is_same<
            util::remove_const<long long>::type,
            long long>::value ||
        !util::is_same<
            util::remove_const<unsigned long long>::type,
            unsigned long long>::value ||
        !util::is_same<
            util::remove_const<float>::type,
            float>::value ||
        !util::is_same<
            util::remove_const<double>::type,
            double>::value ||
        !util::is_same<
            util::remove_const<long double>::type,
            long double>::value ||
        !util::is_same<
            util::remove_const<Foo>::type,
            Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
remove_const_test::test03 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_const<bool* const>::type,
            bool*>::value ||
        !util::is_same<
            util::remove_const<char* const>::type,
            char*>::value ||
        !util::is_same<
            util::remove_const<signed char* const>::type,
            signed char*>::value ||
        !util::is_same<
            util::remove_const<unsigned char* const>::type,
            unsigned char*>::value ||
        !util::is_same<
            util::remove_const<wchar_t* const>::type,
            wchar_t*>::value ||
        !util::is_same<
            util::remove_const<short* const>::type,
            short*>::value ||
        !util::is_same<
            util::remove_const<unsigned short* const>::type,
            unsigned short*>::value ||
        !util::is_same<
            util::remove_const<int* const>::type,
            int*>::value ||
        !util::is_same<
            util::remove_const<unsigned int* const>::type,
            unsigned int*>::value ||
        !util::is_same<
            util::remove_const<long* const>::type,
            long*>::value ||
        !util::is_same<
            util::remove_const<unsigned long* const>::type,
            unsigned long*>::value ||
        !util::is_same<
            util::remove_const<long long* const>::type,
            long long*>::value ||
        !util::is_same<
            util::remove_const<unsigned long long* const>::type,
            unsigned long long*>::value ||
        !util::is_same<
            util::remove_const<float* const>::type,
            float*>::value ||
        !util::is_same<
            util::remove_const<double* const>::type,
            double*>::value ||
        !util::is_same<
            util::remove_const<long double* const>::type,
            long double*>::value ||
        !util::is_same<
            util::remove_const<Foo* const>::type,
            Foo*>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
remove_const_test::test04 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_const<bool volatile const>::type,
            bool volatile>::value ||
        !util::is_same<
            util::remove_const<char volatile const>::type,
            char volatile>::value ||
        !util::is_same<
            util::remove_const<signed char volatile const>::type,
            signed char volatile>::value ||
        !util::is_same<
            util::remove_const<unsigned char volatile const>::type,
            unsigned char volatile>::value ||
        !util::is_same<
            util::remove_const<wchar_t volatile const>::type,
            wchar_t volatile>::value ||
        !util::is_same<
            util::remove_const<short volatile const>::type,
            short volatile>::value ||
        !util::is_same<
            util::remove_const<unsigned short volatile const>::type,
            unsigned short volatile>::value ||
        !util::is_same<
            util::remove_const<int volatile const>::type,
            int volatile>::value ||
        !util::is_same<
            util::remove_const<unsigned int volatile const>::type,
            unsigned int volatile>::value ||
        !util::is_same<
            util::remove_const<long volatile const>::type,
            long volatile>::value ||
        !util::is_same<
            util::remove_const<unsigned long volatile const>::type,
            unsigned long volatile>::value ||
        !util::is_same<
            util::remove_const<long long volatile const>::type,
            long long volatile>::value ||
        !util::is_same<
            util::remove_const<unsigned long long volatile const>::type,
            unsigned long long volatile>::value ||
        !util::is_same<
            util::remove_const<float volatile const>::type,
            float volatile>::value ||
        !util::is_same<
            util::remove_const<double volatile const>::type,
            double volatile>::value ||
        !util::is_same<
            util::remove_const<long double volatile const>::type,
            long double volatile>::value ||
        !util::is_same<
            util::remove_const<Foo volatile const>::type,
            Foo volatile>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
remove_const_test::test05 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_const<bool volatile>::type,
            bool volatile>::value ||
        !util::is_same<
            util::remove_const<char volatile>::type,
            char volatile>::value ||
        !util::is_same<
            util::remove_const<signed char volatile>::type,
            signed char volatile>::value ||
        !util::is_same<
            util::remove_const<unsigned char volatile>::type,
            unsigned char volatile>::value ||
        !util::is_same<
            util::remove_const<wchar_t volatile>::type,
            wchar_t volatile>::value ||
        !util::is_same<
            util::remove_const<short volatile>::type,
            short volatile>::value ||
        !util::is_same<
            util::remove_const<unsigned short volatile>::type,
            unsigned short volatile>::value ||
        !util::is_same<
            util::remove_const<int volatile>::type,
            int volatile>::value ||
        !util::is_same<
            util::remove_const<unsigned int volatile>::type,
            unsigned int volatile>::value ||
        !util::is_same<
            util::remove_const<long volatile>::type,
            long volatile>::value ||
        !util::is_same<
            util::remove_const<unsigned long volatile>::type,
            unsigned long volatile>::value ||
        !util::is_same<
            util::remove_const<long long volatile>::type,
            long long volatile>::value ||
        !util::is_same<
            util::remove_const<unsigned long long volatile>::type,
            unsigned long long volatile>::value ||
        !util::is_same<
            util::remove_const<float volatile>::type,
            float volatile>::value ||
        !util::is_same<
            util::remove_const<double volatile>::type,
            double volatile>::value ||
        !util::is_same<
            util::remove_const<long double volatile>::type,
            long double volatile>::value ||
        !util::is_same<
            util::remove_const<Foo volatile>::type,
            Foo volatile>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


// class remove_volatile_test definitions
//------------------------------------------------------------------------------
/*ctor*/
remove_volatile_test::remove_volatile_test ()
{
    add_test (MAKE_TEST (remove_volatile_test::test01));
    add_test (MAKE_TEST (remove_volatile_test::test02));
    add_test (MAKE_TEST (remove_volatile_test::test03));
    add_test (MAKE_TEST (remove_volatile_test::test04));
    add_test (MAKE_TEST (remove_volatile_test::test05));
}


int
remove_volatile_test::test01 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_volatile<bool volatile>::type,
            bool>::value ||
        !util::is_same<
            util::remove_volatile<char volatile>::type,
            char>::value ||
        !util::is_same<
            util::remove_volatile<signed char volatile>::type,
            signed char>::value ||
        !util::is_same<
            util::remove_volatile<unsigned char volatile>::type,
            unsigned char>::value ||
        !util::is_same<
            util::remove_volatile<wchar_t volatile>::type,
            wchar_t>::value ||
        !util::is_same<
            util::remove_volatile<short volatile>::type,
            short>::value ||
        !util::is_same<
            util::remove_volatile<unsigned short volatile>::type,
            unsigned short>::value ||
        !util::is_same<
            util::remove_volatile<int volatile>::type,
            int>::value ||
        !util::is_same<
            util::remove_volatile<unsigned int volatile>::type,
            unsigned int>::value ||
        !util::is_same<
            util::remove_volatile<long volatile>::type,
            long>::value ||
        !util::is_same<
            util::remove_volatile<unsigned long volatile>::type,
            unsigned long>::value ||
        !util::is_same<
            util::remove_volatile<long long volatile>::type,
            long long>::value ||
        !util::is_same<
            util::remove_volatile<unsigned long long volatile>::type,
            unsigned long long>::value ||
        !util::is_same<
            util::remove_volatile<float volatile>::type,
            float>::value ||
        !util::is_same<
            util::remove_volatile<double volatile>::type,
            double>::value ||
        !util::is_same<
            util::remove_volatile<long double volatile>::type,
            long double>::value ||
        !util::is_same<
            util::remove_volatile<Foo volatile>::type,
            Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
remove_volatile_test::test02 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_volatile<bool const>::type,
            bool const>::value ||
        !util::is_same<
            util::remove_volatile<char const>::type,
            char const>::value ||
        !util::is_same<
            util::remove_volatile<signed char const>::type,
            signed char const>::value ||
        !util::is_same<
            util::remove_volatile<unsigned char const>::type,
            unsigned char const>::value ||
        !util::is_same<
            util::remove_volatile<wchar_t const>::type,
            wchar_t const>::value ||
        !util::is_same<
            util::remove_volatile<short const>::type,
            short const>::value ||
        !util::is_same<
            util::remove_volatile<unsigned short const>::type,
            unsigned short const>::value ||
        !util::is_same<
            util::remove_volatile<int const>::type,
            int const>::value ||
        !util::is_same<
            util::remove_volatile<unsigned int const>::type,
            unsigned int const>::value ||
        !util::is_same<
            util::remove_volatile<long const>::type,
            long const>::value ||
        !util::is_same<
            util::remove_volatile<unsigned long const>::type,
            unsigned long const>::value ||
        !util::is_same<
            util::remove_volatile<long long const>::type,
            long long const>::value ||
        !util::is_same<
            util::remove_volatile<unsigned long long const>::type,
            unsigned long long const>::value ||
        !util::is_same<
            util::remove_volatile<float const>::type,
            float const>::value ||
        !util::is_same<
            util::remove_volatile<double const>::type,
            double const>::value ||
        !util::is_same<
            util::remove_volatile<long double const>::type,
            long double const>::value ||
        !util::is_same<
            util::remove_volatile<Foo const>::type,
            Foo const>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
remove_volatile_test::test03 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_volatile<bool>::type,
            bool>::value ||
        !util::is_same<
            util::remove_volatile<char>::type,
            char>::value ||
        !util::is_same<
            util::remove_volatile<signed char>::type,
            signed char>::value ||
        !util::is_same<
            util::remove_volatile<unsigned char>::type,
            unsigned char>::value ||
        !util::is_same<
            util::remove_volatile<wchar_t>::type,
            wchar_t>::value ||
        !util::is_same<
            util::remove_volatile<short>::type,
            short>::value ||
        !util::is_same<
            util::remove_volatile<unsigned short>::type,
            unsigned short>::value ||
        !util::is_same<
            util::remove_volatile<int>::type,
            int>::value ||
        !util::is_same<
            util::remove_volatile<unsigned int>::type,
            unsigned int>::value ||
        !util::is_same<
            util::remove_volatile<long>::type,
            long>::value ||
        !util::is_same<
            util::remove_volatile<unsigned long>::type,
            unsigned long>::value ||
        !util::is_same<
            util::remove_volatile<long long>::type,
            long long>::value ||
        !util::is_same<
            util::remove_volatile<unsigned long long>::type,
            unsigned long long>::value ||
        !util::is_same<
            util::remove_volatile<float>::type,
            float>::value ||
        !util::is_same<
            util::remove_volatile<double>::type,
            double>::value ||
        !util::is_same<
            util::remove_volatile<long double>::type,
            long double>::value ||
        !util::is_same<
            util::remove_volatile<Foo>::type,
            Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
remove_volatile_test::test04 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_volatile<bool* const volatile>::type,
            bool* const>::value ||
        !util::is_same<
            util::remove_volatile<char* const volatile>::type,
            char* const>::value ||
        !util::is_same<
            util::remove_volatile<signed char* const volatile>::type,
            signed char* const>::value ||
        !util::is_same<
            util::remove_volatile<unsigned char* const volatile>::type,
            unsigned char* const>::value ||
        !util::is_same<
            util::remove_volatile<wchar_t* const volatile>::type,
            wchar_t* const>::value ||
        !util::is_same<
            util::remove_volatile<short* const volatile>::type,
            short* const>::value ||
        !util::is_same<
            util::remove_volatile<unsigned short* const volatile>::type,
            unsigned short* const>::value ||
        !util::is_same<
            util::remove_volatile<int* const volatile>::type,
            int* const>::value ||
        !util::is_same<
            util::remove_volatile<unsigned int* const volatile>::type,
            unsigned int* const>::value ||
        !util::is_same<
            util::remove_volatile<long* const volatile>::type,
            long* const>::value ||
        !util::is_same<
            util::remove_volatile<unsigned long* const volatile>::type,
            unsigned long* const>::value ||
        !util::is_same<
            util::remove_volatile<long long* const volatile>::type,
            long long* const>::value ||
        !util::is_same<
            util::remove_volatile<unsigned long long* const volatile>::type,
            unsigned long long* const>::value ||
        !util::is_same<
            util::remove_volatile<float* const volatile>::type,
            float* const>::value ||
        !util::is_same<
            util::remove_volatile<double* const volatile>::type,
            double* const>::value ||
        !util::is_same<
            util::remove_volatile<long double* const volatile>::type,
            long double* const>::value ||
        !util::is_same<
            util::remove_volatile<Foo* const volatile>::type,
            Foo* const>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
remove_volatile_test::test05 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_volatile<bool volatile const>::type,
            bool const>::value ||
        !util::is_same<
            util::remove_volatile<char volatile const>::type,
            char const>::value ||
        !util::is_same<
            util::remove_volatile<signed char volatile const>::type,
            signed char const>::value ||
        !util::is_same<
            util::remove_volatile<unsigned char volatile const>::type,
            unsigned char const>::value ||
        !util::is_same<
            util::remove_volatile<wchar_t volatile const>::type,
            wchar_t const>::value ||
        !util::is_same<
            util::remove_volatile<short volatile const>::type,
            short const>::value ||
        !util::is_same<
            util::remove_volatile<unsigned short volatile const>::type,
            unsigned short const>::value ||
        !util::is_same<
            util::remove_volatile<int volatile const>::type,
            int const>::value ||
        !util::is_same<
            util::remove_volatile<unsigned int volatile const>::type,
            unsigned int const>::value ||
        !util::is_same<
            util::remove_volatile<long volatile const>::type,
            long const>::value ||
        !util::is_same<
            util::remove_volatile<unsigned long volatile const>::type,
            unsigned long const>::value ||
        !util::is_same<
            util::remove_volatile<long long volatile const>::type,
            long long const>::value ||
        !util::is_same<
            util::remove_volatile<unsigned long long volatile const>::type,
            unsigned long long const>::value ||
        !util::is_same<
            util::remove_volatile<float volatile const>::type,
            float const>::value ||
        !util::is_same<
            util::remove_volatile<double volatile const>::type,
            double const>::value ||
        !util::is_same<
            util::remove_volatile<long double volatile const>::type,
            long double const>::value ||
        !util::is_same<
            util::remove_volatile<Foo volatile const>::type,
            Foo const>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


// class remove_cv_test definitions
//------------------------------------------------------------------------------
/*ctor*/
remove_cv_test::remove_cv_test ()
{
    add_test (MAKE_TEST (remove_cv_test::test01));
    add_test (MAKE_TEST (remove_cv_test::test02));
    add_test (MAKE_TEST (remove_cv_test::test03));
    add_test (MAKE_TEST (remove_cv_test::test04));
    add_test (MAKE_TEST (remove_cv_test::test05));
}


int
remove_cv_test::test01 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_cv<bool volatile>::type,
            bool>::value ||
        !util::is_same<
            util::remove_cv<char volatile>::type,
            char>::value ||
        !util::is_same<
            util::remove_cv<signed char volatile>::type,
            signed char>::value ||
        !util::is_same<
            util::remove_cv<unsigned char volatile>::type,
            unsigned char>::value ||
        !util::is_same<
            util::remove_cv<wchar_t volatile>::type,
            wchar_t>::value ||
        !util::is_same<
            util::remove_cv<short volatile>::type,
            short>::value ||
        !util::is_same<
            util::remove_cv<unsigned short volatile>::type,
            unsigned short>::value ||
        !util::is_same<
            util::remove_cv<int volatile>::type,
            int>::value ||
        !util::is_same<
            util::remove_cv<unsigned int volatile>::type,
            unsigned int>::value ||
        !util::is_same<
            util::remove_cv<long volatile>::type,
            long>::value ||
        !util::is_same<
            util::remove_cv<unsigned long volatile>::type,
            unsigned long>::value ||
        !util::is_same<
            util::remove_cv<long long volatile>::type,
            long long>::value ||
        !util::is_same<
            util::remove_cv<unsigned long long volatile>::type,
            unsigned long long>::value ||
        !util::is_same<
            util::remove_cv<float volatile>::type,
            float>::value ||
        !util::is_same<
            util::remove_cv<double volatile>::type,
            double>::value ||
        !util::is_same<
            util::remove_cv<long double volatile>::type,
            long double>::value ||
        !util::is_same<
            util::remove_cv<Foo volatile>::type,
            Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
remove_cv_test::test02 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_cv<bool const>::type,
            bool>::value ||
        !util::is_same<
            util::remove_cv<char const>::type,
            char>::value ||
        !util::is_same<
            util::remove_cv<signed char const>::type,
            signed char>::value ||
        !util::is_same<
            util::remove_cv<unsigned char const>::type,
            unsigned char>::value ||
        !util::is_same<
            util::remove_cv<wchar_t const>::type,
            wchar_t>::value ||
        !util::is_same<
            util::remove_cv<short const>::type,
            short>::value ||
        !util::is_same<
            util::remove_cv<unsigned short const>::type,
            unsigned short>::value ||
        !util::is_same<
            util::remove_cv<int const>::type,
            int>::value ||
        !util::is_same<
            util::remove_cv<unsigned int const>::type,
            unsigned int>::value ||
        !util::is_same<
            util::remove_cv<long const>::type,
            long>::value ||
        !util::is_same<
            util::remove_cv<unsigned long const>::type,
            unsigned long>::value ||
        !util::is_same<
            util::remove_cv<long long const>::type,
            long long>::value ||
        !util::is_same<
            util::remove_cv<unsigned long long const>::type,
            unsigned long long>::value ||
        !util::is_same<
            util::remove_cv<float const>::type,
            float>::value ||
        !util::is_same<
            util::remove_cv<double const>::type,
            double>::value ||
        !util::is_same<
            util::remove_cv<long double const>::type,
            long double>::value ||
        !util::is_same<
            util::remove_cv<Foo const>::type,
            Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
remove_cv_test::test03 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_cv<bool>::type,
            bool>::value ||
        !util::is_same<
            util::remove_cv<char>::type,
            char>::value ||
        !util::is_same<
            util::remove_cv<signed char>::type,
            signed char>::value ||
        !util::is_same<
            util::remove_cv<unsigned char>::type,
            unsigned char>::value ||
        !util::is_same<
            util::remove_cv<wchar_t>::type,
            wchar_t>::value ||
        !util::is_same<
            util::remove_cv<short>::type,
            short>::value ||
        !util::is_same<
            util::remove_cv<unsigned short>::type,
            unsigned short>::value ||
        !util::is_same<
            util::remove_cv<int>::type,
            int>::value ||
        !util::is_same<
            util::remove_cv<unsigned int>::type,
            unsigned int>::value ||
        !util::is_same<
            util::remove_cv<long>::type,
            long>::value ||
        !util::is_same<
            util::remove_cv<unsigned long>::type,
            unsigned long>::value ||
        !util::is_same<
            util::remove_cv<long long>::type,
            long long>::value ||
        !util::is_same<
            util::remove_cv<unsigned long long>::type,
            unsigned long long>::value ||
        !util::is_same<
            util::remove_cv<float>::type,
            float>::value ||
        !util::is_same<
            util::remove_cv<double>::type,
            double>::value ||
        !util::is_same<
            util::remove_cv<long double>::type,
            long double>::value ||
        !util::is_same<
            util::remove_cv<Foo>::type,
            Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
remove_cv_test::test04 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_cv<bool* const volatile>::type,
            bool*>::value ||
        !util::is_same<
            util::remove_cv<char* const volatile>::type,
            char*>::value ||
        !util::is_same<
            util::remove_cv<signed char* const volatile>::type,
            signed char*>::value ||
        !util::is_same<
            util::remove_cv<unsigned char* const volatile>::type,
            unsigned char*>::value ||
        !util::is_same<
            util::remove_cv<wchar_t* const volatile>::type,
            wchar_t*>::value ||
        !util::is_same<
            util::remove_cv<short* const volatile>::type,
            short*>::value ||
        !util::is_same<
            util::remove_cv<unsigned short* const volatile>::type,
            unsigned short*>::value ||
        !util::is_same<
            util::remove_cv<int* const volatile>::type,
            int*>::value ||
        !util::is_same<
            util::remove_cv<unsigned int* const volatile>::type,
            unsigned int*>::value ||
        !util::is_same<
            util::remove_cv<long* const volatile>::type,
            long*>::value ||
        !util::is_same<
            util::remove_cv<unsigned long* const volatile>::type,
            unsigned long*>::value ||
        !util::is_same<
            util::remove_cv<long long* const volatile>::type,
            long long*>::value ||
        !util::is_same<
            util::remove_cv<unsigned long long* const volatile>::type,
            unsigned long long*>::value ||
        !util::is_same<
            util::remove_cv<float* const volatile>::type,
            float*>::value ||
        !util::is_same<
            util::remove_cv<double* const volatile>::type,
            double*>::value ||
        !util::is_same<
            util::remove_cv<long double* const volatile>::type,
            long double*>::value ||
        !util::is_same<
            util::remove_cv<Foo* const volatile>::type,
            Foo*>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
remove_cv_test::test05 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_same<
            util::remove_cv<bool volatile const>::type,
            bool>::value ||
        !util::is_same<
            util::remove_cv<char volatile const>::type,
            char>::value ||
        !util::is_same<
            util::remove_cv<signed char volatile const>::type,
            signed char>::value ||
        !util::is_same<
            util::remove_cv<unsigned char volatile const>::type,
            unsigned char>::value ||
        !util::is_same<
            util::remove_cv<wchar_t volatile const>::type,
            wchar_t>::value ||
        !util::is_same<
            util::remove_cv<short volatile const>::type,
            short>::value ||
        !util::is_same<
            util::remove_cv<unsigned short volatile const>::type,
            unsigned short>::value ||
        !util::is_same<
            util::remove_cv<int volatile const>::type,
            int>::value ||
        !util::is_same<
            util::remove_cv<unsigned int volatile const>::type,
            unsigned int>::value ||
        !util::is_same<
            util::remove_cv<long volatile const>::type,
            long>::value ||
        !util::is_same<
            util::remove_cv<unsigned long volatile const>::type,
            unsigned long>::value ||
        !util::is_same<
            util::remove_cv<long long volatile const>::type,
            long long>::value ||
        !util::is_same<
            util::remove_cv<unsigned long long volatile const>::type,
            unsigned long long>::value ||
        !util::is_same<
            util::remove_cv<float volatile const>::type,
            float>::value ||
        !util::is_same<
            util::remove_cv<double volatile const>::type,
            double>::value ||
        !util::is_same<
            util::remove_cv<long double volatile const>::type,
            long double>::value ||
        !util::is_same<
            util::remove_cv<Foo volatile const>::type,
            Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


// class is_integral_test definitions
//------------------------------------------------------------------------------
/*ctor*/
is_integral_test::is_integral_test ()
{
    add_test (MAKE_TEST (is_integral_test::test01));
    add_test (MAKE_TEST (is_integral_test::test02));
    add_test (MAKE_TEST (is_integral_test::test03));
    add_test (MAKE_TEST (is_integral_test::test04));
    add_test (MAKE_TEST (is_integral_test::test05));
}


int
is_integral_test::test01 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_integral<bool>::value ||
        !util::is_integral<char>::value ||
        !util::is_integral<signed char>::value ||
        !util::is_integral<unsigned char>::value ||
        !util::is_integral<wchar_t>::value ||
        !util::is_integral<short>::value ||
        !util::is_integral<unsigned short>::value ||
        !util::is_integral<int>::value ||
        !util::is_integral<unsigned int>::value ||
        !util::is_integral<long>::value ||
        !util::is_integral<unsigned long>::value ||
        !util::is_integral<long long>::value ||
        !util::is_integral<unsigned long long>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_integral_test::test02 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_integral<float>::value ||
        util::is_integral<double>::value ||
        util::is_integral<long double>::value ||
        util::is_integral<Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_integral_test::test03 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_integral<bool const>::value ||
        !util::is_integral<char const>::value ||
        !util::is_integral<signed char const>::value ||
        !util::is_integral<unsigned char const>::value ||
        !util::is_integral<wchar_t const>::value ||
        !util::is_integral<short const>::value ||
        !util::is_integral<unsigned short const>::value ||
        !util::is_integral<int const>::value ||
        !util::is_integral<unsigned int const>::value ||
        !util::is_integral<long const>::value ||
        !util::is_integral<unsigned long const>::value ||
        !util::is_integral<long long const>::value ||
        !util::is_integral<unsigned long long const>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_integral_test::test04 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_integral<bool*>::value ||
        util::is_integral<char*>::value ||
        util::is_integral<signed char*>::value ||
        util::is_integral<unsigned char*>::value ||
        util::is_integral<wchar_t*>::value ||
        util::is_integral<short*>::value ||
        util::is_integral<unsigned short*>::value ||
        util::is_integral<int*>::value ||
        util::is_integral<unsigned int*>::value ||
        util::is_integral<long*>::value ||
        util::is_integral<unsigned long*>::value ||
        util::is_integral<long long*>::value ||
        util::is_integral<unsigned long long*>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_integral_test::test05 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_integral<bool&>::value ||
        util::is_integral<char&>::value ||
        util::is_integral<signed char&>::value ||
        util::is_integral<unsigned char&>::value ||
        util::is_integral<wchar_t&>::value ||
        util::is_integral<short&>::value ||
        util::is_integral<unsigned short&>::value ||
        util::is_integral<int&>::value ||
        util::is_integral<unsigned int&>::value ||
        util::is_integral<long&>::value ||
        util::is_integral<unsigned long&>::value ||
        util::is_integral<long long&>::value ||
        util::is_integral<unsigned long long&>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


// class is_floating_point_test definitions
//------------------------------------------------------------------------------
/*ctor*/
is_floating_point_test::is_floating_point_test ()
{
    add_test (MAKE_TEST (is_floating_point_test::test01));
    add_test (MAKE_TEST (is_floating_point_test::test02));
    add_test (MAKE_TEST (is_floating_point_test::test03));
    add_test (MAKE_TEST (is_floating_point_test::test04));
    add_test (MAKE_TEST (is_floating_point_test::test05));
}


int
is_floating_point_test::test01 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_floating_point<float>::value ||
        !util::is_floating_point<double>::value ||
        !util::is_floating_point<long double>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_floating_point_test::test02 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_floating_point<bool>::value ||
        util::is_floating_point<char>::value ||
        util::is_floating_point<signed char>::value ||
        util::is_floating_point<unsigned char>::value ||
        util::is_floating_point<wchar_t>::value ||
        util::is_floating_point<short>::value ||
        util::is_floating_point<unsigned short>::value ||
        util::is_floating_point<int>::value ||
        util::is_floating_point<unsigned int>::value ||
        util::is_floating_point<long>::value ||
        util::is_floating_point<unsigned long>::value ||
        util::is_floating_point<long long>::value ||
        util::is_floating_point<unsigned long long>::value ||
        util::is_floating_point<Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_floating_point_test::test03 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_floating_point<float const>::value ||
        !util::is_floating_point<double const>::value ||
        !util::is_floating_point<long double const>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_floating_point_test::test04 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_floating_point<float*>::value ||
        util::is_floating_point<double*>::value ||
        util::is_floating_point<long double*>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_floating_point_test::test05 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_floating_point<float&>::value ||
        util::is_floating_point<double&>::value ||
        util::is_floating_point<long double&>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


// class is_arithmetic_test definitions
//------------------------------------------------------------------------------
/*ctor*/
is_arithmetic_test::is_arithmetic_test ()
{
    add_test (MAKE_TEST (is_arithmetic_test::test01));
    add_test (MAKE_TEST (is_arithmetic_test::test02));
    add_test (MAKE_TEST (is_arithmetic_test::test03));
    add_test (MAKE_TEST (is_arithmetic_test::test04));
    add_test (MAKE_TEST (is_arithmetic_test::test05));
}


int
is_arithmetic_test::test01 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_arithmetic<bool>::value ||
        !util::is_arithmetic<char>::value ||
        !util::is_arithmetic<signed char>::value ||
        !util::is_arithmetic<unsigned char>::value ||
        !util::is_arithmetic<wchar_t>::value ||
        !util::is_arithmetic<short>::value ||
        !util::is_arithmetic<unsigned short>::value ||
        !util::is_arithmetic<int>::value ||
        !util::is_arithmetic<unsigned int>::value ||
        !util::is_arithmetic<long>::value ||
        !util::is_arithmetic<unsigned long>::value ||
        !util::is_arithmetic<long long>::value ||
        !util::is_arithmetic<unsigned long long>::value ||
        !util::is_arithmetic<float>::value ||
        !util::is_arithmetic<double>::value ||
        !util::is_arithmetic<long double>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_arithmetic_test::test02 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_arithmetic<bool const>::value ||
        !util::is_arithmetic<char const>::value ||
        !util::is_arithmetic<signed char const>::value ||
        !util::is_arithmetic<unsigned char const>::value ||
        !util::is_arithmetic<wchar_t const>::value ||
        !util::is_arithmetic<short const>::value ||
        !util::is_arithmetic<unsigned short const>::value ||
        !util::is_arithmetic<int const>::value ||
        !util::is_arithmetic<unsigned int const>::value ||
        !util::is_arithmetic<long const>::value ||
        !util::is_arithmetic<unsigned long const>::value ||
        !util::is_arithmetic<long long const>::value ||
        !util::is_arithmetic<unsigned long long const>::value ||
        !util::is_arithmetic<float const>::value ||
        !util::is_arithmetic<double const>::value ||
        !util::is_arithmetic<long double const>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_arithmetic_test::test03 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_arithmetic<Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_arithmetic_test::test04 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_arithmetic<bool&>::value ||
        util::is_arithmetic<char&>::value ||
        util::is_arithmetic<signed char&>::value ||
        util::is_arithmetic<unsigned char&>::value ||
        util::is_arithmetic<wchar_t&>::value ||
        util::is_arithmetic<short&>::value ||
        util::is_arithmetic<unsigned short&>::value ||
        util::is_arithmetic<int&>::value ||
        util::is_arithmetic<unsigned int&>::value ||
        util::is_arithmetic<long&>::value ||
        util::is_arithmetic<unsigned long&>::value ||
        util::is_arithmetic<long long&>::value ||
        util::is_arithmetic<unsigned long long&>::value ||
        util::is_arithmetic<float&>::value ||
        util::is_arithmetic<double&>::value ||
        util::is_arithmetic<long double&>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_arithmetic_test::test05 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_arithmetic<bool*>::value ||
        util::is_arithmetic<char*>::value ||
        util::is_arithmetic<signed char*>::value ||
        util::is_arithmetic<unsigned char*>::value ||
        util::is_arithmetic<wchar_t*>::value ||
        util::is_arithmetic<short*>::value ||
        util::is_arithmetic<unsigned short*>::value ||
        util::is_arithmetic<int*>::value ||
        util::is_arithmetic<unsigned int*>::value ||
        util::is_arithmetic<long*>::value ||
        util::is_arithmetic<unsigned long*>::value ||
        util::is_arithmetic<long long*>::value ||
        util::is_arithmetic<unsigned long long*>::value ||
        util::is_arithmetic<float*>::value ||
        util::is_arithmetic<double*>::value ||
        util::is_arithmetic<long double*>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


// class is_signed_test definitions
//------------------------------------------------------------------------------
/*ctor*/
is_signed_test::is_signed_test ()
{
    add_test (MAKE_TEST (is_signed_test::test01));
    add_test (MAKE_TEST (is_signed_test::test02));
}


int
is_signed_test::test01 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_signed<char>::value ||
        !util::is_signed<signed char>::value ||
        !util::is_signed<wchar_t>::value ||
        !util::is_signed<short>::value ||
        !util::is_signed<int>::value ||
        !util::is_signed<long>::value ||
        !util::is_signed<long long>::value ||
        !util::is_signed<float>::value ||
        !util::is_signed<double>::value ||
        !util::is_signed<long double>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_signed_test::test02 ()
{
    int rval = EXIT_SUCCESS;
    if (util::is_signed<unsigned char>::value ||
        util::is_signed<unsigned short>::value ||
        util::is_signed<unsigned int>::value ||
        util::is_signed<unsigned long>::value ||
        util::is_signed<unsigned long long>::value ||
        util::is_signed<Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


// class is_unsigned_test definitions
//------------------------------------------------------------------------------
/*ctor*/
is_unsigned_test::is_unsigned_test ()
{
    add_test (MAKE_TEST (is_unsigned_test::test01));
    add_test (MAKE_TEST (is_unsigned_test::test02));
}


int
is_unsigned_test::test01 ()
{
    int rval = EXIT_SUCCESS;
    if (!util::is_unsigned<unsigned char>::value ||
        !util::is_unsigned<unsigned short>::value ||
        !util::is_unsigned<unsigned int>::value ||
        !util::is_unsigned<unsigned long>::value ||
        !util::is_unsigned<unsigned long long>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}


int
is_unsigned_test::test02()
{
    int rval = EXIT_SUCCESS;
    if (util::is_unsigned<char>::value ||
        util::is_unsigned<signed char>::value ||
        util::is_unsigned<wchar_t>::value ||
        util::is_unsigned<short>::value ||
        util::is_unsigned<int>::value ||
        util::is_unsigned<long>::value ||
        util::is_unsigned<long long>::value ||
        util::is_unsigned<float>::value ||
        util::is_unsigned<double>::value ||
        util::is_unsigned<long double>::value ||
        util::is_unsigned<Foo>::value)
    {
        rval = EXIT_FAILURE;
    }
    return rval;
}
