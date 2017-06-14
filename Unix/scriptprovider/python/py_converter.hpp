// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
// purpose:
//     This module provides useful helper methods for converting values between
//     PyObject and the following C++ types:
//         char
//         signed char
//         unsigned char
//         short
//         unsigned short
//         int
//         unsigned int
//         long long int
//         unsigned long long int
//         float
//         double
//         std::basic_string<MI_Char>
//
// usage:
//     toPyObject:
//
//         <any of the above C++ types> value;
//         PyObject* pObject = toPyObject (value);
//
//     fromPyObject:
//
//         PyObject* pObject; // (initialization missing)
//         <any of the above C++ types> value;
//         if (PY_SUCCESS == fromPyObject (pObject, &value))
//         {
//             // conversion succeeded
//         }
//
//------------------------------------------------------------------------------

#ifndef INCLUDED_PY_CONVERTER_HPP
#define INCLUDED_PY_CONVERTER_HPP


#include "Python.h"


#include "debug_tags.hpp"
#include "mi_type.hpp"
#include "mi_value.hpp"
#include "traits.hpp"


#include <cassert>
#include <string>


namespace scx
{


#ifndef PY_SUCCESS
#define PY_SUCCESS (0)
#endif

#ifndef PY_FAILURE
#define PY_FAILURE (-1)
#endif


// class PyConverter_Sint declaration
//------------------------------------------------------------------------------
template<typename T>
class PyConverter_Sint
{
public:
    static PyObject* toPyObject (T const& value);
    static int fromPyObject (PyObject* pSource, T* pValueOut);
};


// class PyConverter_Sint<long long> specialization declaration
//------------------------------------------------------------------------------
template<>
class PyConverter_Sint<long long>
{
public:
    static PyObject* toPyObject (long long const& value);
    static int fromPyObject (PyObject* pSource, long long* pValueOut);
};


// class PyConverter_Uint declaration
//------------------------------------------------------------------------------
template<typename T>
class PyConverter_Uint
{
public:
    static PyObject* toPyObject (T const& value);
    static int fromPyObject (PyObject* pSource, T* pValueOut);
};


// class PyConverter_Uint<unsigned long long> specialization declaration
//------------------------------------------------------------------------------
template<>
class PyConverter_Uint<unsigned long long>
{
public:
    static PyObject* toPyObject (unsigned long long const& value);
    static int fromPyObject (PyObject* pSource, unsigned long long* pValueOut);
};


// class PyConverter_Int definition
//------------------------------------------------------------------------------
template<typename T>
class PyConverter_Int :
    public util::conditional<util::is_signed<T>::value,
                             PyConverter_Sint<T>,
                             PyConverter_Uint<T> >::type
{
    // implemented through inheritance
};


// class PyConverter_Real declaration
//------------------------------------------------------------------------------
template<typename T>
class PyConverter_Real
{
public:
    static PyObject* toPyObject (T const& value);
    static int fromPyObject (PyObject* pSource, T* pValueOut);
};


// class PyConverter definition
//------------------------------------------------------------------------------
template<typename T, typename T_VOID = void>
class PyConverter :
    public util::conditional<util::is_integral<T>::value,
                             PyConverter_Int<T>,
                             PyConverter_Real<T> >::type
{
    // implemeted through inheritance
};


// class PyConverter<MI_Type<MI_STRING>::type_t> specialization declaration
//------------------------------------------------------------------------------
template<>
class PyConverter<MI_Type<MI_STRING>::type_t>
{
public:
    static PyObject* toPyObject (MI_Type<MI_STRING>::type_t const& value);
    static int fromPyObject (PyObject* pSource,
                             std::basic_string<MI_Char>* pValueOut);
};


// helper functions
//------------------------------------------------------------------------------
template<typename T>
PyObject* toPyObject (T const& value)
{
    return PyConverter<T>::toPyObject (value);
}


// purpose: attempts to convert PyObject* to MI_Type<TYPE>::type
template<typename T>
int
fromPyObject (
    PyObject* pSource,
    T* pValueOut)
{
    return PyConverter<T>::fromPyObject (pSource, pValueOut);
}


// purpose: attempts to convert PyObject* to MI_Value<TYPE>::type
// notes: this method works with basic Python types
//        this does not work with NULL or PyNone
//        this does not work with MI_Wrapper<TYPE>
template<TypeID_t TYPE>
int
to_MI_Value (
    PyObject* pSource,
    typename scx::MI_Value<TYPE>::Ptr* ppValueOut)
{
    //SCX_BOOKEND ("to_MI_Value");
    assert (NULL != ppValueOut);
    typename scx::MI_Type<TYPE>::type_t value;
    int rval = scx::fromPyObject (pSource, &value);
    if (PY_SUCCESS == rval)
    {
        ppValueOut->reset (new scx::MI_Value<TYPE> (value));
    }
    return rval;
}


// purpose: attempts to convert PyObject* to MI_Value<TYPE>::type
// notes: this method works with basic Python types, NULL, and Py_None
//        this does not work with MI_Wrapper<TYPE>
template<TypeID_t TYPE>
int
to_MI_Value_or_NULL (
    PyObject* pSource,
    typename scx::MI_Value<TYPE>::Ptr* ppValueOut)
{
    //SCX_BOOKEND ("to_MI_Value");
    assert (NULL != ppValueOut);
    int rval = PY_FAILURE;
    if (NULL == pSource ||
        Py_None == pSource)
    {
        ppValueOut->reset ();
        rval = PY_SUCCESS;
    }
    else
    {
        rval = to_MI_Value<TYPE> (pSource, ppValueOut);
    }
    return rval;
}


// purpose: attempts to convert PyObject* to MI_Value<TYPE>::type
// notes: this method works with basic Python types, MI_Wrapper<TYPE>, NULL, and
//        Py_None
int
to_MI_ValueBase (
    TypeID_t type,
    PyObject* pSource,
    MI_ValueBase::Ptr* ppValueOut);



// class PyConverter_Sint definitions
//------------------------------------------------------------------------------
template<typename T>
/*static*/ PyObject* 
PyConverter_Sint<T>::toPyObject (
    T const& value)
{
    return PyLong_FromLong (value);
}


template<typename T>
/*static*/ int
PyConverter_Sint<T>::fromPyObject (
    PyObject* pSource,
    T* pValueOut)
{
    //SCX_BOOKEND ("PyConverter_Sint::fromPyObject");
    int rval = PY_FAILURE;
    assert (NULL != pSource && Py_None != pSource);
    assert (NULL != pValueOut);
    if (PyLong_Check (pSource))
    {
        //SCX_BOOKEND_PRINT ("PyLong");
        long long value = PyLong_AsLongLong (pSource);
        if (-1 != value ||
            NULL == PyErr_Occurred ())
        {
            if (MI_Limits<Type_to_ID<T>::ID>::min () <= value &&
                MI_Limits<Type_to_ID<T>::ID>::max () >= value)
            {
                // succeeded
                *pValueOut = static_cast<T>(value);
                rval = PY_SUCCESS;
            }
            else
            {
                // failed (value out of range)
                //SCX_BOOKEND_PRINT ("value out of range");
            }
        }
        else
        {
            // failed
            //SCX_BOOKEND_PRINT ("PyLong_AsLongLong failed");
        }
    }
    else if (PyInt_Check (pSource))
    {
        //SCX_BOOKEND_PRINT ("PyInt");
        long value = PyInt_AsLong (pSource);
        if (-1 != value ||
            NULL == PyErr_Occurred ())
        {
            if (MI_Limits<Type_to_ID<T>::ID>::min () <= value &&
                MI_Limits<Type_to_ID<T>::ID>::max () >= value)
            {
                // succeeded
                *pValueOut = static_cast<T>(value);
                rval = PY_SUCCESS;
            }
            else
            {
                // failed (value out of range)
                //SCX_BOOKEND_PRINT ("value out of range");
            }
        }
        else
        {
            // failed
            //SCX_BOOKEND_PRINT ("PyInt_AsLong failed");
        }
    }
    else
    {
        // failed
        //SCX_BOOKEND_PRINT ("no idea which type");
    }
    return rval;
}


// class PyConverter_Uint definitions
//------------------------------------------------------------------------------
template<typename T>
/*static*/ PyObject*
PyConverter_Uint<T>::toPyObject (
    T const& value)
{
    return PyLong_FromUnsignedLong (value);
}


template<typename T>
/*static*/ int
PyConverter_Uint<T>::fromPyObject (
    PyObject* pSource,
    T* pValueOut)
{
    //SCX_BOOKEND ("PyConverter_Uint::fromPyObject");
    int rval = PY_FAILURE;
    assert (NULL != pSource && Py_None != pSource);
    assert (NULL != pValueOut);
    if (PyLong_Check (pSource))
    {
        //SCX_BOOKEND_PRINT ("PyLong");
        unsigned long long value = PyLong_AsUnsignedLongLong (pSource);
        if ((unsigned long long)-1 != value ||
            NULL == PyErr_Occurred ())
        {
            if (MI_Limits<Type_to_ID<T>::ID>::max () >= value)
            {
                // succeeded
                *pValueOut = static_cast<T>(value);
                rval = PY_SUCCESS;
            }
            else
            {
                // failed
                //SCX_BOOKEND_PRINT ("value out of range");
            }
        }
        else
        {
            // failed
            //SCX_BOOKEND_PRINT ("PyLong_AsUnsignedLongLong failed");
        }
    }
    else if (PyInt_Check (pSource))
    {
        //SCX_BOOKEND_PRINT ("PyInt");
        long value = PyInt_AsLong (pSource);
        if (-1 != value ||
            NULL == PyErr_Occurred ())
        {
            if (0 <= value &&
                MI_Limits<Type_to_ID<T>::ID>::max () >=
                static_cast<unsigned long>(value))
            {
                *pValueOut = static_cast<T>(value);
                rval = PY_SUCCESS;
            }
            else
            {
                // failed
                //SCX_BOOKEND_PRINT ("value out of range");
            }
        }
        else
        {
            // failed
            //SCX_BOOKEND_PRINT ("PyInt_AsLong failed");
        }
    }
    else
    {
        // failed
        //SCX_BOOKEND_PRINT ("no idea which type");
    }
    return rval;
}


// class PyConverter_Real defintions
//------------------------------------------------------------------------------
template<typename T>
/*static*/ PyObject*
PyConverter_Real<T>::toPyObject (
    T const& value)
{
    return PyFloat_FromDouble (value);
}


template<typename T>
/*static*/ int
PyConverter_Real<T>::fromPyObject (
    PyObject* pSource,
    T* pValueOut)
{
    //SCX_BOOKEND ("PyConverter_Real::fromPyObject");
    int rval = PY_FAILURE;
    assert (pSource && Py_None != pSource);
    assert (NULL != pValueOut);
    if (PyFloat_Check (pSource))
    {
        double value = PyFloat_AS_DOUBLE (pSource);
        if (MI_Limits<Type_to_ID<T>::ID>::min () <= fabs (value) &&
            MI_Limits<Type_to_ID<T>::ID>::max () >= fabs (value))
        {
            *pValueOut = static_cast<T>(value);
            rval = PY_SUCCESS;
        }
        else
        {
            //SCX_BOOKEND_PRINT ("value out of range");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("incorrect type");
    }
    return rval;
}


} // namespace scx


#endif // INCLUDED_PY_CONVERTER_HPP
