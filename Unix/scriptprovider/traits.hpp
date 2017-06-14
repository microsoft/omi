// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#ifndef INCLUDED_UTIL_TRAITS_HPP
#define INCLUDED_UTIL_TRAITS_HPP


namespace util
{


// integral_constant
//------------------------------------------------------------------------------
template<typename T, T v>
struct integral_constant
{
    static T const value = v;
    typedef T value_type;
    typedef integral_constant<T, v> type;
    /*T*/ operator T () const { return v; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;


// is_lvalue_reference
//------------------------------------------------------------------------------
template<typename T>
struct is_lvalue_reference : public false_type {};

template<typename T>
struct is_lvalue_reference<T&> : public true_type {};


// is_pointer
//------------------------------------------------------------------------------
template<typename T>
struct is_pointer : public false_type {};

template<typename T>
struct is_pointer<T*> : public true_type {};


// is_reference
//------------------------------------------------------------------------------
template<typename T>
struct is_reference : public is_lvalue_reference<T> {};


// conditional
//------------------------------------------------------------------------------
template<bool CONDITION, typename TRUE_TYPE, typename FALSE_TYPE>
struct conditional
{
    typedef TRUE_TYPE type;
};


template<typename TRUE_TYPE, typename FALSE_TYPE>
struct conditional<false, TRUE_TYPE, FALSE_TYPE>
{
    typedef FALSE_TYPE type;
};


// is_same
//------------------------------------------------------------------------------
template<typename T1, typename T2>
struct is_same : public false_type {};


template<typename T>
struct is_same<T, T> : public true_type {};


// remove_reference
//------------------------------------------------------------------------------
template<typename T>
struct remove_reference
{
    typedef T type;
};

template<typename T>
struct remove_reference<T&>
{
    typedef T type;
};


// remove_pointer
//------------------------------------------------------------------------------
template<typename T>
struct remove_pointer
{
    typedef T type;
};

template<typename T>
struct remove_pointer<T*>
{
    typedef T type;
};


// remove_const
//------------------------------------------------------------------------------
template<typename T>
struct remove_const
{
    typedef T type;
};

template<typename T>
struct remove_const<T const>
{
    typedef T type;
};


// remove_volatile
//------------------------------------------------------------------------------
template<typename T>
struct remove_volatile
{
    typedef T type;
};

template<typename T>
struct remove_volatile<T volatile>
{
    typedef T type;
};


// remove_cv
//------------------------------------------------------------------------------
template<typename T>
struct remove_cv
{
    typedef typename remove_const<typename remove_volatile<T>::type>::type type;
};        


// is_intergral
//------------------------------------------------------------------------------
template<typename T>
struct is_integral :
    public integral_constant<
        bool,
        is_same<bool, typename remove_cv<T>::type>::value ||
        is_same<char, typename remove_cv<T>::type>::value ||
        is_same<signed char, typename remove_cv<T>::type>::value ||
        is_same<unsigned char, typename remove_cv<T>::type>::value ||
        is_same<wchar_t, typename remove_cv<T>::type>::value ||
        is_same<short, typename remove_cv<T>::type>::value ||
        is_same<unsigned short, typename remove_cv<T>::type>::value ||
        is_same<int, typename remove_cv<T>::type>::value ||
        is_same<unsigned int, typename remove_cv<T>::type>::value ||
        is_same<long, typename remove_cv<T>::type>::value ||
        is_same<unsigned long, typename remove_cv<T>::type>::value ||
        is_same<long long, typename remove_cv<T>::type>::value ||
        is_same<unsigned long long, typename remove_cv<T>::type>::value> {};


// is_floating_point
//------------------------------------------------------------------------------
template<typename T>
struct is_floating_point :
    public integral_constant<
        bool,
        is_same<float, typename remove_cv<T>::type>::value ||
        is_same<double, typename remove_cv<T>::type>::value ||
        is_same<long double, typename remove_cv<T>::type>::value> {};


// is_arithmetic
//------------------------------------------------------------------------------
template<typename T>
struct is_arithmetic :
    public integral_constant<
        bool,
        is_integral<T>::value || is_floating_point<T>::value> {};


// is_signed
//------------------------------------------------------------------------------
template<typename T>
struct is_signed :
    public integral_constant<
        bool,
        is_floating_point<T>::value ||
        is_same<char, typename remove_cv<T>::type>::value ||
        is_same<signed char, typename remove_cv<T>::type>::value ||
        is_same<wchar_t, typename remove_cv<T>::type>::value ||
        is_same<short, typename remove_cv<T>::type>::value ||
        is_same<int, typename remove_cv<T>::type>::value ||
        is_same<long, typename remove_cv<T>::type>::value ||
        is_same<long long, typename remove_cv<T>::type>::value> {};


// is_unsigned
//------------------------------------------------------------------------------
template<typename T>
struct is_unsigned :
    public integral_constant<
        bool,
        is_same<unsigned char, typename remove_cv<T>::type>::value ||
        is_same<unsigned short, typename remove_cv<T>::type>::value ||
        is_same<unsigned int, typename remove_cv<T>::type>::value ||
        is_same<unsigned long, typename remove_cv<T>::type>::value ||
        is_same<unsigned long long, typename remove_cv<T>::type>::value> {};


} // namespace util


#endif // INCLUDED_UTIL_TRAITS_HPP
