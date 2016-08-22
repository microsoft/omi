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


// is_arithmetic
//------------------------------------------------------------------------------
template<typename T>
struct is_arithmetic : public false_type {};

template<>
struct is_arithmetic<bool> : public true_type {};

template<>
struct is_arithmetic<char> : public true_type {};

template<>
struct is_arithmetic<wchar_t> : public true_type {};

template<>
struct is_arithmetic<signed char> : public true_type {};

template<>
struct is_arithmetic<unsigned char> : public true_type {};

template<>
struct is_arithmetic<short> : public true_type {};

template<>
struct is_arithmetic<unsigned short> : public true_type {};

template<>
struct is_arithmetic<int> : public true_type {};

template<>
struct is_arithmetic<unsigned int> : public true_type {};

template<>
struct is_arithmetic<long> : public true_type {};

template<>
struct is_arithmetic<unsigned long> : public true_type {};

template<>
struct is_arithmetic<long long> : public true_type {};

template<>
struct is_arithmetic<unsigned long long> : public true_type {};

template<>
struct is_arithmetic<float> : public true_type {};

template<>
struct is_arithmetic<double> : public true_type {};

template<>
struct is_arithmetic<long double> : public true_type {};


// is_intergral
//------------------------------------------------------------------------------
template<typename T>
struct is_integral : public false_type {};

template<>
struct is_integral<bool> : public true_type {};

template<>
struct is_integral<char> : public true_type {};

template<>
struct is_integral<wchar_t> : public true_type {};

template<>
struct is_integral<signed char> : public true_type {};

template<>
struct is_integral<unsigned char> : public true_type {};

template<>
struct is_integral<short> : public true_type {};

template<>
struct is_integral<unsigned short> : public true_type {};

template<>
struct is_integral<int> : public true_type {};

template<>
struct is_integral<unsigned int> : public true_type {};

template<>
struct is_integral<long> : public true_type {};

template<>
struct is_integral<unsigned long> : public true_type {};

template<>
struct is_integral<long long> : public true_type {};

template<>
struct is_integral<unsigned long long> : public true_type {};


// is_floating_point
//------------------------------------------------------------------------------
template<typename T>
struct is_floating_point : public false_type {};

template<>
struct is_floating_point<float> : public true_type {};

template<>
struct is_floating_point<double> : public true_type {};

template<>
struct is_floating_point<long double> : public true_type {};


// is_signed
//------------------------------------------------------------------------------
template<typename T>
struct is_signed :
    public conditional<is_arithmetic<T>::value && T(-1) < T(0),
                       true_type, false_type>::type {};


// is_unsigned
//------------------------------------------------------------------------------
template<typename T>
struct is_unsigned :
    public conditional<is_arithmetic<T>::value && T(0) < T(-1),
                       true_type, false_type>::type {};


} // namespace util


#endif // INCLUDED_UTIL_TRAITS_HPP
