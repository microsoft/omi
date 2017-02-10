#include "py_converter.hpp"


#include "mi_wrapper.hpp"


namespace
{


int
_PyBool_to_MI_ValueBase (
    PyObject* pSource,
    scx::MI_ValueBase::Ptr* ppValueOut)
{
    SCX_BOOKEND ("PyBool_to_MI_ValueBase");
    int rval = PY_FAILURE;
    if (NULL != pSource &&
        Py_None != pSource)
    {
        if (PyObject_TypeCheck (
                pSource, scx::MI_Wrapper<MI_BOOLEAN>::getPyTypeObject ()))
        {
            SCX_BOOKEND_PRINT ("PyObject_TypeCheck: true");
            ppValueOut->reset (
                reinterpret_cast<scx::MI_Wrapper<MI_BOOLEAN>*>(
                    pSource)->getValue ());
            rval = PY_SUCCESS;
        }
        else if (PyBool_Check (pSource))
        {
            SCX_BOOKEND_PRINT ("PyBool");
            ppValueOut->reset (
                new scx::MI_Value<MI_BOOLEAN> (
                    Py_False == pSource ? false : true));
            rval = PY_SUCCESS;
        }
    }
    else
    {
        ppValueOut->reset ();
        rval = PY_SUCCESS;
    }
    return rval;
}


int
_MI_Datetime_to_MI_ValueBase (
    PyObject* pSource,
    scx::MI_ValueBase::Ptr* ppValueOut)
{
    SCX_BOOKEND ("MI_Datetime_to_MI_ValueBase");
    int rval = PY_FAILURE;
    if (NULL != pSource &&
        Py_None != pSource)
    {
        if (PyObject_TypeCheck (
                pSource, scx::MI_Timestamp_Wrapper::getPyTypeObject ()))
        {
            SCX_BOOKEND_PRINT ("MI_Timestamp");
            ppValueOut->reset (
                reinterpret_cast<scx::MI_Timestamp_Wrapper*>(
                    pSource)->getValue ());
            rval = PY_SUCCESS;
        }
        else if (PyObject_TypeCheck (
                pSource, scx::MI_Interval_Wrapper::getPyTypeObject ()))
        {
            SCX_BOOKEND_PRINT ("MI_Interval");
            ppValueOut->reset (
                reinterpret_cast<scx::MI_Interval_Wrapper*>(
                    pSource)->getValue ());
            rval = PY_SUCCESS;
        }
        else
        {
            SCX_BOOKEND_PRINT ("pSource is not a MI_Datetime");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("NULL or PyNone");
        ppValueOut->reset ();
        rval = PY_SUCCESS;
    }
    return rval;
}


template<scx::TypeID_t TYPE>
int
_to_MI_ValueBase (
    PyObject* pSource,
    scx::MI_ValueBase::Ptr* ppValueOut)
{
    SCX_BOOKEND ("to_MI_ValueBase<TypeID_t>");
    int rval = PY_FAILURE;
    if (NULL != pSource &&
        Py_None != pSource)
    {
        if (PyObject_TypeCheck (pSource, scx::MI_Wrapper<TYPE>::getPyTypeObject ()))
        {
            SCX_BOOKEND_PRINT ("PyObject_TypeCheck: true");
            ppValueOut->reset (
                reinterpret_cast<scx::MI_Wrapper<TYPE>*>(pSource)->getValue ());
            rval = PY_SUCCESS;
        }
        else
        {
            SCX_BOOKEND_PRINT ("PyObject_TypeCheck: false");
            typename scx::MI_Type<TYPE>::type_t value;
            rval = scx::fromPyObject (pSource, &value);
            if (PY_SUCCESS == rval)
            {
                ppValueOut->reset (new scx::MI_Value<TYPE> (value));
            }
        }
    }
    else
    {
        ppValueOut->reset ();
        rval = PY_SUCCESS;
    }
    return rval;
}


template<scx::TypeID_t TYPE>
int
_array_to_MI_ValueBase (
    PyObject* pSource,
    scx::MI_ValueBase::Ptr* ppValueOut)
{
    SCX_BOOKEND ("array_to_MI_ValueBase<TypeID_t>");
    int rval = PY_FAILURE;
    typedef typename scx::MI_Type<TYPE & ~MI_ARRAY>::type_t Value_t;
    if (NULL != pSource &&
        Py_None != pSource)
    {
        if (PyObject_TypeCheck (pSource,
                                scx::MI_Array_Wrapper<TYPE>::getPyTypeObject ()))
        {
            SCX_BOOKEND_PRINT ("PyObject_TypeCheck: true");
            ppValueOut->reset (
                reinterpret_cast<scx::MI_Array_Wrapper<TYPE>*>(
                    pSource)->getValue ());
            rval = PY_SUCCESS;
        }
        else if (PyList_Check (pSource))
        {
            typename scx::MI_Array<TYPE>::Ptr pArray (new scx::MI_Array<TYPE>);
            rval = PY_SUCCESS;
            for (Py_ssize_t i = 0, count = PyList_Size (pSource);
                 PY_SUCCESS == rval && i < count;
                 ++i)
            {
                Value_t value;
                rval = scx::fromPyObject (PyList_GET_ITEM (pSource, i), &value);
                if (PY_SUCCESS == rval)
                {
                    pArray->push_back (value);
                }
            }
            if (PY_SUCCESS == rval)
            {
                ppValueOut->reset (pArray.get ());
            }
        }
        else if (PyTuple_Check (pSource))
        {
            typename scx::MI_Array<TYPE>::Ptr pArray (new scx::MI_Array<TYPE>);
            rval = PY_SUCCESS;
            for (Py_ssize_t i = 0, count = PyTuple_Size (pSource);
                 PY_SUCCESS == rval && i < count;
                 ++i)
            {
                Value_t value;
                rval = scx::fromPyObject (PyTuple_GET_ITEM (pSource, i), &value);
                if (PY_SUCCESS == rval)
                {
                    pArray->push_back (value);
                }
            }
            if (PY_SUCCESS == rval)
            {
                ppValueOut->reset (pArray.get ());
            }
        }
    }
    else
    {
        ppValueOut->reset ();
        rval = PY_SUCCESS;
    }
    return rval;
}


int
_MI_DatetimeA_to_MI_ValueBase (
    PyObject* pSource,
    scx::MI_ValueBase::Ptr* ppValueOut)
{
    SCX_BOOKEND ("_MI_DatetimeA_to_MI_ValueBase");
    int rval = PY_FAILURE;
    if (NULL != pSource &&
        Py_None != pSource)
    {
        if (PyObject_TypeCheck (
                pSource,
                scx::MI_Array_Wrapper<MI_DATETIMEA>::getPyTypeObject ()))
        {
            SCX_BOOKEND_PRINT ("PyObject_TypeCheck: true");
            ppValueOut->reset (
                reinterpret_cast<scx::MI_Array_Wrapper<MI_DATETIMEA>*>(
                    pSource)->getValue ());
            rval = PY_SUCCESS;
        }
        else if (PyList_Check (pSource))
        {
//            typename scx::MI_Array<TYPE>::Ptr pArray (new scx::MI_Array<TYPE>);
            scx::MI_Array<MI_DATETIMEA>::Ptr pArray (
                new scx::MI_Array<MI_DATETIMEA>);
            rval = PY_SUCCESS;
            for (Py_ssize_t i = 0, count = PyList_Size (pSource);
                 PY_SUCCESS == rval && i < count;
                 ++i)
            {
                PyObject* pItem = PyList_GET_ITEM (pSource, i);
                if (PyObject_TypeCheck (
                        pItem, scx::MI_Timestamp_Wrapper::getPyTypeObject ()))
                {
                    pArray->push_back (
                        scx::MI_Datetime::Ptr (
                            reinterpret_cast<scx::MI_Timestamp_Wrapper*>(
                                pItem)->getValue ()));
                }
                else if (PyObject_TypeCheck (
                             pItem,
                             scx::MI_Interval_Wrapper::getPyTypeObject ()))
                {
                    pArray->push_back (
                        scx::MI_Datetime::Ptr (
                            reinterpret_cast<scx::MI_Interval_Wrapper*>(
                                pItem)->getValue ()));
                }
                else
                {
                    rval = PY_FAILURE;
                }
                       
//                Value_t value;
//                rval = scx::fromPyObject (PyList_GET_ITEM (pSource, i), &value);
//                if (PY_SUCCESS == rval)
//                {
//                    pArray->push_back (value);
//                }
            }
            if (PY_SUCCESS == rval)
            {
                ppValueOut->reset (pArray.get ());
            }
        }
        else if (PyTuple_Check (pSource))
        {
//            typename scx::MI_Array<TYPE>::Ptr pArray (new scx::MI_Array<TYPE>);
            scx::MI_Array<MI_DATETIMEA>::Ptr pArray (
                new scx::MI_Array<MI_DATETIMEA>);
            rval = PY_SUCCESS;
            for (Py_ssize_t i = 0, count = PyTuple_Size (pSource);
                 PY_SUCCESS == rval && i < count;
                 ++i)
            {
                PyObject* pItem = PyTuple_GET_ITEM (pSource, i);
                if (PyObject_TypeCheck (
                        pItem, scx::MI_Timestamp_Wrapper::getPyTypeObject ()))
                {
                    pArray->push_back (
                        scx::MI_Datetime::Ptr (
                            reinterpret_cast<scx::MI_Timestamp_Wrapper*>(
                                pItem)->getValue ()));
                }
                else if (PyObject_TypeCheck (
                             pItem,
                             scx::MI_Interval_Wrapper::getPyTypeObject ()))
                {
                    pArray->push_back (
                        scx::MI_Datetime::Ptr (
                            reinterpret_cast<scx::MI_Interval_Wrapper*>(
                                pItem)->getValue ()));
                }
                else
                {
                    rval = PY_FAILURE;
                }

//                Value_t value;
//                rval = scx::fromPyObject (PyTuple_GET_ITEM (pSource, i), &value);
//                if (PY_SUCCESS == rval)
//                {
//                    pArray->push_back (value);
//                }
            }
            if (PY_SUCCESS == rval)
            {
                ppValueOut->reset (pArray.get ());
            }
        }
    }
    else
    {
        ppValueOut->reset ();
        rval = PY_SUCCESS;
    }
    return rval;
}


}


namespace scx
{


// class PyConverter_Sint<long long> specialization definitions
//------------------------------------------------------------------------------
//template<>
/*static*/ PyObject*
PyConverter_Sint<long long>::toPyObject (
    long long const& value)
{
    return PyLong_FromLongLong (value);
}


//template<>
/*static*/ int
PyConverter_Sint<long long>::fromPyObject (
    PyObject* pSource,
    long long* pValueOut)
{
    //SCX_BOOKEND ("PyConverter_Sint<long long>::fromPyObject");
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
            *pValueOut = value;
            rval = PY_SUCCESS;
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
            *pValueOut = static_cast<long long>(value);
            rval = PY_SUCCESS;
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


// class PyConverter_Uint<unsigned long long> specialization definitions
//------------------------------------------------------------------------------
/*static*/ PyObject*
PyConverter_Uint<unsigned long long>::toPyObject (
    unsigned long long const& value)
{
    return PyLong_FromUnsignedLongLong (value);
}


/*static*/ int
PyConverter_Uint<unsigned long long>::fromPyObject (
    PyObject* pSource,
    unsigned long long* pValueOut)
{
    //SCX_BOOKEND ("PyConverter_Uint<unsigned long long>::fromPyObject");
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
            // succeeded
            *pValueOut = value;
            rval = PY_SUCCESS;
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
            if (0 <= value)
            {
                *pValueOut = static_cast<unsigned long long>(value);
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


// class PyConverter<MI_Type<MI_STRING>::type_t> specialization definitions
//------------------------------------------------------------------------------
/*static*/ PyObject*
PyConverter<MI_Type<MI_STRING>::type_t>::toPyObject (
    MI_Type<MI_STRING>::type_t const& value)
{
    return PyString_FromString (value.c_str ());
}


/*static*/ int
PyConverter<MI_Type<MI_STRING>::type_t>::fromPyObject (
    PyObject* pSource,
    MI_Type<MI_STRING>::type_t* pValueOut)
{
    //SCX_BOOKEND ("PyConverter<MI_Type<MI_STRING>::type_t>::fromPyObject");
    int rval = PY_FAILURE;
    assert (NULL != pSource && Py_None != pSource);
    assert (NULL != pValueOut);
    if (PyString_Check (pSource))
    {
        *pValueOut = PyString_AsString (pSource);
        rval = PY_SUCCESS;
    }
    else
    {
        // failed
        //SCX_BOOKEND_PRINT ("no idea which type");
    }
    return rval;
}


int
to_MI_ValueBase (
    TypeID_t type,
    PyObject* pSource,
    MI_ValueBase::Ptr* ppValueOut)
{
    SCX_BOOKEND ("to_MI_ValueBase");
    assert (NULL != ppValueOut);
    int rval = PY_FAILURE;
    switch (type)
    {
    case MI_BOOLEAN:
        rval = _PyBool_to_MI_ValueBase (pSource, ppValueOut);
        break;
    case MI_UINT8:
        rval = _to_MI_ValueBase<MI_UINT8> (pSource, ppValueOut);
        break;
    case MI_SINT8:
        rval = _to_MI_ValueBase<MI_SINT8> (pSource, ppValueOut);
        break;
    case MI_UINT16:
        rval = _to_MI_ValueBase<MI_UINT16> (pSource, ppValueOut);
        break;
    case MI_SINT16:
        rval = _to_MI_ValueBase<MI_SINT16> (pSource, ppValueOut);
        break;
    case MI_UINT32:
        rval = _to_MI_ValueBase<MI_UINT32> (pSource, ppValueOut);
        break;
    case MI_SINT32:
        rval = _to_MI_ValueBase<MI_SINT32> (pSource, ppValueOut);
        break;
    case MI_UINT64:
        rval = _to_MI_ValueBase<MI_UINT64> (pSource, ppValueOut);
        break;
    case MI_SINT64:
        rval = _to_MI_ValueBase<MI_SINT64> (pSource, ppValueOut);
        break;
    case MI_REAL32:
        rval = _to_MI_ValueBase<MI_REAL32> (pSource, ppValueOut);
        break;
    case MI_REAL64:
        rval = _to_MI_ValueBase<MI_REAL64> (pSource, ppValueOut);
        break;
    case MI_STRING:
        rval = _to_MI_ValueBase<MI_STRING> (pSource, ppValueOut);
        break;
    case MI_CHAR16:
        rval = _to_MI_ValueBase<MI_CHAR16> (pSource, ppValueOut);
        break;
    case MI_DATETIME:
        rval = _MI_Datetime_to_MI_ValueBase (pSource, ppValueOut);
        break;

    case MI_BOOLEANA:
        rval = _array_to_MI_ValueBase<MI_BOOLEANA> (pSource, ppValueOut);
        break;
    case MI_UINT8A:
        break;
    case MI_SINT8A:
        rval = _array_to_MI_ValueBase<MI_SINT8A> (pSource, ppValueOut);
        break;
    case MI_UINT16A:
        rval = _array_to_MI_ValueBase<MI_UINT16A> (pSource, ppValueOut);
        break;
    case MI_SINT16A:
        rval = _array_to_MI_ValueBase<MI_SINT16A> (pSource, ppValueOut);
        break;
    case MI_UINT32A:
        rval = _array_to_MI_ValueBase<MI_UINT32A> (pSource, ppValueOut);
        break;
    case MI_SINT32A:
        rval = _array_to_MI_ValueBase<MI_SINT32A> (pSource, ppValueOut);
        break;
    case MI_UINT64A:
        rval = _array_to_MI_ValueBase<MI_UINT64A> (pSource, ppValueOut);
        break;
    case MI_SINT64A:
        rval = _array_to_MI_ValueBase<MI_SINT64A> (pSource, ppValueOut);
        break;
    case MI_REAL32A:
        rval = _array_to_MI_ValueBase<MI_REAL32A> (pSource, ppValueOut);
        break;
    case MI_REAL64A:
        rval = _array_to_MI_ValueBase<MI_REAL64A> (pSource, ppValueOut);
        break;
    case MI_STRINGA:
        rval = _array_to_MI_ValueBase<MI_STRINGA> (pSource, ppValueOut);
        break;
    case MI_CHAR16A:
        rval = _array_to_MI_ValueBase<MI_CHAR16A> (pSource, ppValueOut);
        break;

    case MI_DATETIMEA:
        SCX_BOOKEND_PRINT ("MI_DATETIMEA");
        rval = _MI_DatetimeA_to_MI_ValueBase (pSource, ppValueOut);
//        rval = _array_to_MI_ValueBase<MI_DATETIMEA> (pSource, ppValueOut);
        break;

    // todo: implement the remaining types

    default:
        SCX_BOOKEND_PRINT ("encountered an unhandled type");
        break;
    }
    return rval;
}


} // namespace scx
