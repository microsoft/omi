// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
// purpose:
//    class MI_Type:
//        A traits template to convert between the TypeID 'enum' value to the
//        actual value type.
//
//    class MI_Limits:
//        A traits template to convert between the TypeID 'enum' value to the
//        actual value type which also provides min and max values for the
//        value type.
//
//    class IsArray:
//        A traits template used to determine if the value for a TypeID 'enum'
//        is an array.
//
//    class Type_to_ID:
//        A traits template to convert from a value type to the TypeID 'enum'
//        value.
//
//------------------------------------------------------------------------------
#ifndef INCLUDED_MI_TYPE_HPP
#define INCLUDED_MI_TYPE_HPP


#include "MI.h"


#include <cfloat>
#include <climits>
#include <vector>


namespace scx
{


typedef MI_Uint32 TypeID_t;


template<TypeID_t TYPE_ID>
class MI_Type;


template<>
class MI_Type<MI_BOOLEAN>
{
public:
    typedef MI_Boolean type_t;
};


template<>
class MI_Type<MI_UINT8>
{
public:
    typedef MI_Uint8 type_t;
};


template<>
class MI_Type<MI_SINT8>
{
public:
    typedef MI_Sint8 type_t;
};


template<>
class MI_Type<MI_UINT16>
{
public:
    typedef MI_Uint16 type_t;
};


template<>
class MI_Type<MI_SINT16>
{
public:
    typedef MI_Sint16 type_t;
};


template<>
class MI_Type<MI_UINT32>
{
public:
    typedef MI_Uint32 type_t;
};


template<>
class MI_Type<MI_SINT32>
{
public:
    typedef MI_Sint32 type_t;
};


template<>
class MI_Type<MI_UINT64>
{
public:
    typedef MI_Uint64 type_t;
};


template<>
class MI_Type<MI_SINT64>
{
public:
    typedef MI_Sint64 type_t;
};


template<>
class MI_Type<MI_REAL32>
{
public:
    typedef MI_Real32 type_t;
};


template<>
class MI_Type<MI_REAL64>
{
public:
    typedef MI_Real64 type_t;
};


template<>
class MI_Type<MI_CHAR16>
{
public:
    typedef MI_Char16 type_t;
};


template<>
class MI_Type<MI_DATETIME>
{
public:
    typedef MI_Datetime type_t;
};


template<>
class MI_Type<MI_STRING>
{
public:
    typedef std::basic_string<MI_Char> type_t;
};


template<TypeID_t TYPE_ID>
class MI_ArrayType
{
public:
    typedef typename scx::MI_Type<TYPE_ID & ~MI_ARRAY>::type_t nested_type_t;
};


template<TypeID_t TYPE_ID>
class MI_Limits;


template<>
class MI_Limits<MI_SINT8>
{
public:
    typedef MI_Type<MI_SINT8>::type_t type_t;
    static type_t min () { return static_cast<type_t>(SCHAR_MIN); }
    static type_t max () { return static_cast<type_t>(SCHAR_MAX); }
};


template<>
class MI_Limits<MI_UINT8>
{
public:
    typedef MI_Type<MI_UINT8>::type_t type_t;
    static type_t min () { return static_cast<type_t>(0); }
    static type_t max () { return static_cast<type_t>(UCHAR_MAX); }
};


template<>
class MI_Limits<MI_SINT16>
{
public:
    typedef MI_Type<MI_SINT16>::type_t type_t;
    static type_t min () { return static_cast<type_t>(SHRT_MIN); }
    static type_t max () { return static_cast<type_t>(SHRT_MAX); }
};


template<>
class MI_Limits<MI_UINT16>
{
public:
    typedef MI_Type<MI_UINT16>::type_t type_t;
    static type_t min () { return static_cast<type_t>(0); }
    static type_t max () { return static_cast<type_t>(USHRT_MAX); }
};


template<>
class MI_Limits<MI_SINT32>
{
public:
    typedef MI_Type<MI_SINT32>::type_t type_t;
    static type_t min () { return static_cast<type_t>(INT_MIN); }
    static type_t max () { return static_cast<type_t>(INT_MAX); }
};


template<>
class MI_Limits<MI_UINT32>
{
public:
    typedef MI_Type<MI_UINT32>::type_t type_t;
    static type_t min () { return static_cast<type_t>(0); }
    static type_t max () { return static_cast<type_t>(UINT_MAX); }
};


template<>
class MI_Limits<MI_SINT64>
{
public:
    typedef MI_Type<MI_SINT64>::type_t type_t;
    static type_t min () { return static_cast<type_t>(LLONG_MIN); }
    static type_t max () { return static_cast<type_t>(LLONG_MAX); }
};


template<>
class MI_Limits<MI_UINT64>
{
public:
    typedef MI_Type<MI_UINT64>::type_t type_t;
    static type_t min () { return static_cast<type_t>(0); }
    static type_t max () { return static_cast<type_t>(ULLONG_MAX); }
};


template<>
class MI_Limits<MI_REAL32>
{
public:
    typedef MI_Type<MI_REAL32>::type_t type_t;
    static type_t min () { return static_cast<type_t>(FLT_MIN); }
    static type_t max () { return static_cast<type_t>(FLT_MAX); }
};


template<>
class MI_Limits<MI_REAL64>
{
public:
    typedef MI_Type<MI_REAL64>::type_t type_t;
    static type_t min () { return static_cast<type_t>(DBL_MIN); }
    static type_t max () { return static_cast<type_t>(DBL_MAX); }
};


template<>
class MI_Limits<MI_CHAR16>
{
public:
    typedef MI_Type<MI_CHAR16>::type_t type_t;
    static type_t min () { return static_cast<type_t>(0); }
    static type_t max () { return static_cast<type_t>(USHRT_MAX); }
};


template<TypeID_t TYPE_ID>
class IsArray
{
public:
    static bool const VALUE = (TYPE_ID & MI_ARRAY) == MI_ARRAY;
};


template<typename T>
class Type_to_ID;


template<>
class Type_to_ID<MI_Limits<MI_UINT8>::type_t>
{
public:
    static TypeID_t const ID = MI_UINT8;
};


template<>
class Type_to_ID<MI_Limits<MI_SINT8>::type_t>
{
public:
    static TypeID_t const ID = MI_SINT8;
};


template<>
class Type_to_ID<MI_Limits<MI_UINT16>::type_t>
{
public:
    static TypeID_t const ID = MI_UINT16;
};


template<>
class Type_to_ID<MI_Limits<MI_SINT16>::type_t>
{
public:
    static TypeID_t const ID = MI_SINT16;
};


template<>
class Type_to_ID<MI_Limits<MI_UINT32>::type_t>
{
public:
    static TypeID_t const ID = MI_UINT32;
};


template<>
class Type_to_ID<MI_Limits<MI_SINT32>::type_t>
{
public:
    static TypeID_t const ID = MI_SINT32;
};


template<>
class Type_to_ID<MI_Limits<MI_UINT64>::type_t>
{
public:
    static TypeID_t const ID = MI_UINT64;
};


template<>
class Type_to_ID<MI_Limits<MI_SINT64>::type_t>
{
public:
    static TypeID_t const ID = MI_SINT64;
};


template<>
class Type_to_ID<MI_Limits<MI_REAL32>::type_t>
{
public:
    static TypeID_t const ID = MI_REAL32;
};


template<>
class Type_to_ID<MI_Limits<MI_REAL64>::type_t>
{
public:
    static TypeID_t const ID = MI_REAL64;
};


}


#endif // INCLUDED_MI_TYPE_HPP
