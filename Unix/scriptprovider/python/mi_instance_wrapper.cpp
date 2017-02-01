#include "mi_instance_wrapper.hpp"
#include "mi_wrapper.hpp"
#include "mi_schema.hpp"

using namespace scx;


namespace
{


template<TypeID_t TYPE_ID>
PyObject*
wrap_value (
    scx::MI_ValueBase::Ptr const& pValue)
{
    //SCX_BOOKEND ("wrap_value");
    typename scx::MI_Wrapper<TYPE_ID>::PyPtr pyValue =
        scx::MI_Wrapper<TYPE_ID>::createPyPtr (
            typename scx::MI_Value<TYPE_ID>::Ptr (
                new typename scx::MI_Value<TYPE_ID> (
                    *static_cast<scx::MI_Value<TYPE_ID>*>(pValue.get ()))));
    return reinterpret_cast<PyObject*>(pyValue.release ());
}


PyObject*
wrap_datetime (
    scx::MI_ValueBase::Ptr const& pValue)
{
    if (static_cast<scx::MI_Datetime*>(pValue.get ())->isTimestamp ())
    {
        scx::MI_Timestamp_Wrapper::PyPtr pyTimestamp =
            scx::MI_Timestamp_Wrapper::createPyPtr (
                scx::MI_Timestamp::Ptr (
                    static_cast<scx::MI_Timestamp*>(pValue.get ())));
        return reinterpret_cast<PyObject*>(pyTimestamp.release ());
    }
    else
    {
        scx::MI_Interval_Wrapper::PyPtr pyInterval =
            scx::MI_Interval_Wrapper::createPyPtr (
                scx::MI_Interval::Ptr (
                    static_cast<scx::MI_Interval*>(pValue.get ())));
        return reinterpret_cast<PyObject*>(pyInterval.release ());
    }
}


template<TypeID_t TYPE_ID>
PyObject*
wrap_array (
    scx::MI_ValueBase::Ptr const& pArray)
{
    typename scx::MI_Array_Wrapper<TYPE_ID>::PyPtr pyArray =
        scx::MI_Array_Wrapper<TYPE_ID>::createPyPtr (
            typename scx::MI_Array<TYPE_ID>::Ptr (
                new typename scx::MI_Array<TYPE_ID> (
                    *static_cast<scx::MI_Array<TYPE_ID>*>(pArray.get ()))));
    return reinterpret_cast<PyObject*>(pyArray.release ());
}


int
convertToBase (
    TypeID_t type,
    PyObject* pValueObj,
    MI_ValueBase::Ptr* ppValueOut)
{
    int ret = PY_FAILURE;
    switch (type)
    {
    case MI_BOOLEAN:
        if (PyObject_TypeCheck (
                pValueObj, scx::MI_Wrapper<MI_BOOLEAN>::getPyTypeObject ()))
        {
            *ppValueOut = new scx::MI_Value<MI_BOOLEAN> (
                *reinterpret_cast<scx::MI_Wrapper<MI_BOOLEAN>*>(
                    pValueObj)->getValue ());
            ret = PY_SUCCESS;
        }
        break;
    case MI_UINT8:
        if (PyObject_TypeCheck (
                pValueObj, scx::MI_Wrapper<MI_UINT8>::getPyTypeObject ()))
        {
            *ppValueOut = new scx::MI_Value<MI_UINT8> (
                *reinterpret_cast<scx::MI_Wrapper<MI_UINT8>*>(
                    pValueObj)->getValue ());
            ret = PY_SUCCESS;
        }
        break;
    case MI_SINT8:
        if (PyObject_TypeCheck (
                pValueObj, scx::MI_Wrapper<MI_SINT8>::getPyTypeObject ()))
        {
            *ppValueOut = new scx::MI_Value<MI_SINT8> (
                *reinterpret_cast<scx::MI_Wrapper<MI_SINT8>*>(
                    pValueObj)->getValue ());
            ret = PY_SUCCESS;
        }
        break;
    case MI_UINT16:
        if (PyObject_TypeCheck (
                pValueObj, scx::MI_Wrapper<MI_UINT16>::getPyTypeObject ()))
        {
            *ppValueOut = new scx::MI_Value<MI_UINT16> (
                *reinterpret_cast<scx::MI_Wrapper<MI_UINT16>*>(
                    pValueObj)->getValue ());
            ret = PY_SUCCESS;
        }
        break;
    case MI_SINT16:
        if (PyObject_TypeCheck (
                pValueObj, scx::MI_Wrapper<MI_SINT16>::getPyTypeObject ()))
        {
            *ppValueOut = new scx::MI_Value<MI_SINT16> (
                *reinterpret_cast<scx::MI_Wrapper<MI_SINT16>*>(
                    pValueObj)->getValue ());
            ret = PY_SUCCESS;
        }
        break;
    case MI_UINT32:
        if (PyObject_TypeCheck (
                pValueObj, scx::MI_Wrapper<MI_UINT32>::getPyTypeObject ()))
        {
            *ppValueOut = new scx::MI_Value<MI_UINT32> (
                *reinterpret_cast<scx::MI_Wrapper<MI_UINT32>*>(
                    pValueObj)->getValue ());
            ret = PY_SUCCESS;
        }
        break;
    case MI_SINT32:
        if (PyObject_TypeCheck (
                pValueObj, scx::MI_Wrapper<MI_SINT32>::getPyTypeObject ()))
        {
            *ppValueOut = new scx::MI_Value<MI_SINT32> (
                *reinterpret_cast<scx::MI_Wrapper<MI_SINT32>*>(
                    pValueObj)->getValue ());
            ret = PY_SUCCESS;
        }
        break;
    case MI_UINT64:
        if (PyObject_TypeCheck (
                pValueObj, scx::MI_Wrapper<MI_UINT64>::getPyTypeObject ()))
        {
            *ppValueOut = new scx::MI_Value<MI_UINT64> (
                *reinterpret_cast<scx::MI_Wrapper<MI_UINT64>*>(
                    pValueObj)->getValue ());
            ret = PY_SUCCESS;
        }
        break;
    case MI_SINT64:
        if (PyObject_TypeCheck (
                pValueObj, scx::MI_Wrapper<MI_SINT64>::getPyTypeObject ()))
        {
            *ppValueOut = new scx::MI_Value<MI_SINT64> (
                *reinterpret_cast<scx::MI_Wrapper<MI_SINT64>*>(
                    pValueObj)->getValue ());
            ret = PY_SUCCESS;
        }
        break;
    case MI_REAL32:
        if (PyObject_TypeCheck (
                pValueObj, scx::MI_Wrapper<MI_REAL32>::getPyTypeObject ()))
        {
            *ppValueOut = new scx::MI_Value<MI_REAL32> (
                *reinterpret_cast<scx::MI_Wrapper<MI_REAL32>*>(
                    pValueObj)->getValue ());
            ret = PY_SUCCESS;
        }
        break;
    case MI_REAL64:
        if (PyObject_TypeCheck (
                pValueObj, scx::MI_Wrapper<MI_REAL64>::getPyTypeObject ()))
        {
            *ppValueOut = new scx::MI_Value<MI_REAL64> (
                *reinterpret_cast<scx::MI_Wrapper<MI_REAL64>*>(
                    pValueObj)->getValue ());
            ret = PY_SUCCESS;
        }
        break;
    case MI_CHAR16:
        if (PyObject_TypeCheck (
                pValueObj, scx::MI_Wrapper<MI_CHAR16>::getPyTypeObject ()))
        {
            *ppValueOut = new scx::MI_Value<MI_CHAR16> (
                *reinterpret_cast<scx::MI_Wrapper<MI_CHAR16>*>(
                    pValueObj)->getValue ());
            ret = PY_SUCCESS;
        }
        break;
    case MI_STRING:
        if (PyObject_TypeCheck (
                pValueObj, scx::MI_Wrapper<MI_STRING>::getPyTypeObject ()))
        {
            *ppValueOut = new scx::MI_Value<MI_STRING> (
                *reinterpret_cast<scx::MI_Wrapper<MI_STRING>*>(
                    pValueObj)->getValue ());
            ret = PY_SUCCESS;
        }
        else
        {
            std::ostringstream strm;
            strm << "PyTypeObject::name: "
                 << scx::MI_Wrapper<MI_STRING>::getPyTypeObject ()->tp_name;
            SCX_BOOKEND_PRINT (strm.str ());
            if (pValueObj && pValueObj != Py_None)
            {
                SCX_BOOKEND_PRINT ("pValueObj is not NULL");
            }
            else
            {
                SCX_BOOKEND_PRINT ("pValueObj is NULL");
            }
            SCX_BOOKEND_PRINT ("Type is not MI_STRING");
        }
        break;
    case MI_DATETIME:
        if (PyObject_TypeCheck (
                pValueObj, MI_Timestamp_Wrapper::getPyTypeObject ()))
        {
            *ppValueOut = new scx::MI_Timestamp (
                *reinterpret_cast<MI_Timestamp_Wrapper*>(
                    pValueObj)->getValue ());
            ret = PY_SUCCESS;
        }
        else if (PyObject_TypeCheck (
                     pValueObj, MI_Interval_Wrapper::getPyTypeObject ()))
        {
            *ppValueOut = new scx::MI_Interval (
                *reinterpret_cast<MI_Interval_Wrapper*>(
                    pValueObj)->getValue ());
            ret = PY_SUCCESS;
        }
        break;
    case MI_INSTANCE:
    case MI_REFERENCE:
        SCX_BOOKEND_PRINT ("Encountered an unhandled type");
        break;
    case MI_BOOLEANA:
        if (PyObject_TypeCheck (
                pValueObj,
                scx::MI_Array_Wrapper<MI_BOOLEANA>::getPyTypeObject ()))
        {
            *ppValueOut = new scx::MI_Array<MI_BOOLEANA> (
                *reinterpret_cast<MI_Array_Wrapper<MI_BOOLEANA>*>(
                    pValueObj)->getValue ());
            ret = PY_SUCCESS;
        }
        break;
    case MI_UINT8A:
        if (PyObject_TypeCheck (
                pValueObj,
                scx::MI_Array_Wrapper<MI_UINT8A>::getPyTypeObject ()))
    {
        *ppValueOut = new scx::MI_Array<MI_UINT8A> (
            *reinterpret_cast<MI_Array_Wrapper<MI_UINT8A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    break;
    case MI_SINT8A:
        if (PyObject_TypeCheck (
                pValueObj,
                scx::MI_Array_Wrapper<MI_SINT8A>::getPyTypeObject ()))
    {
        *ppValueOut = new scx::MI_Array<MI_SINT8A> (
            *reinterpret_cast<MI_Array_Wrapper<MI_SINT8A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    break;
    case MI_UINT16A:
        if (PyObject_TypeCheck (
                pValueObj,
                scx::MI_Array_Wrapper<MI_UINT16A>::getPyTypeObject ()))
    {
        *ppValueOut = new scx::MI_Array<MI_UINT16A> (
            *reinterpret_cast<MI_Array_Wrapper<MI_UINT16A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    break;
    case MI_SINT16A:
        if (PyObject_TypeCheck (
                pValueObj,
                scx::MI_Array_Wrapper<MI_SINT16A>::getPyTypeObject ()))
    {
        *ppValueOut = new scx::MI_Array<MI_SINT16A> (
            *reinterpret_cast<MI_Array_Wrapper<MI_SINT16A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    break;
    case MI_UINT32A:
        if (PyObject_TypeCheck (
                pValueObj,
                scx::MI_Array_Wrapper<MI_UINT32A>::getPyTypeObject ()))
    {
        *ppValueOut = new scx::MI_Array<MI_UINT32A> (
            *reinterpret_cast<MI_Array_Wrapper<MI_UINT32A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    break;
    case MI_SINT32A:
        if (PyObject_TypeCheck (
                pValueObj,
                scx::MI_Array_Wrapper<MI_SINT32A>::getPyTypeObject ()))
    {
        *ppValueOut = new scx::MI_Array<MI_SINT32A> (
            *reinterpret_cast<MI_Array_Wrapper<MI_SINT32A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    break;
    case MI_UINT64A:
        if (PyObject_TypeCheck (
                pValueObj,
                scx::MI_Array_Wrapper<MI_UINT64A>::getPyTypeObject ()))
    {
        *ppValueOut = new scx::MI_Array<MI_UINT64A> (
            *reinterpret_cast<MI_Array_Wrapper<MI_UINT64A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    break;
    case MI_SINT64A:
        if (PyObject_TypeCheck (
                pValueObj,
                scx::MI_Array_Wrapper<MI_SINT64A>::getPyTypeObject ()))
    {
        *ppValueOut = new scx::MI_Array<MI_SINT64A> (
            *reinterpret_cast<MI_Array_Wrapper<MI_SINT64A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    break;
    case MI_REAL32A:
        if (PyObject_TypeCheck (
                pValueObj,
                scx::MI_Array_Wrapper<MI_REAL32A>::getPyTypeObject ()))
    {
        *ppValueOut = new scx::MI_Array<MI_REAL32A> (
            *reinterpret_cast<MI_Array_Wrapper<MI_REAL32A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    break;
    case MI_REAL64A:
        if (PyObject_TypeCheck (
                pValueObj,
                scx::MI_Array_Wrapper<MI_REAL64A>::getPyTypeObject ()))
    {
        *ppValueOut = new scx::MI_Array<MI_REAL64A> (
            *reinterpret_cast<MI_Array_Wrapper<MI_REAL64A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    break;
    case MI_CHAR16A:
        if (PyObject_TypeCheck (
                pValueObj,
                scx::MI_Array_Wrapper<MI_CHAR16A>::getPyTypeObject ()))
    {
        *ppValueOut = new scx::MI_Array<MI_CHAR16A> (
            *reinterpret_cast<MI_Array_Wrapper<MI_CHAR16A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    break;
    case MI_DATETIMEA:
        if (PyObject_TypeCheck (
                pValueObj,
                scx::MI_Array_Wrapper<MI_DATETIMEA>::getPyTypeObject ()))
    {
        *ppValueOut = new scx::MI_Array<MI_DATETIMEA> (
            *reinterpret_cast<MI_Array_Wrapper<MI_DATETIMEA>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    break;
    case MI_STRINGA:
        if (PyObject_TypeCheck (
                pValueObj,
                scx::MI_Array_Wrapper<MI_STRINGA>::getPyTypeObject ()))
    {
        *ppValueOut = new scx::MI_Array<MI_STRINGA> (
            *reinterpret_cast<MI_Array_Wrapper<MI_STRINGA>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    break;
    case MI_INSTANCEA:
    case MI_REFERENCEA:
    default:
        SCX_BOOKEND_PRINT ("Encountered an unhandled type");
        break;
    }
    return ret;
}


int
convertToBase (
    PyObject* pValueObj,
    MI_ValueBase::Ptr* ppValueOut)
{
    int ret = PY_FAILURE;
    if (PyObject_TypeCheck (
            pValueObj, scx::MI_Wrapper<MI_BOOLEAN>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_BOOLEAN");
        *ppValueOut = new scx::MI_Value<MI_BOOLEAN> (
            *reinterpret_cast<scx::MI_Wrapper<MI_BOOLEAN>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj, scx::MI_Wrapper<MI_UINT8>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_UINT8");
        *ppValueOut = new scx::MI_Value<MI_UINT8> (
            *reinterpret_cast<scx::MI_Wrapper<MI_UINT8>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj, scx::MI_Wrapper<MI_SINT8>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_SINT8");
        *ppValueOut = new scx::MI_Value<MI_SINT8> (
            *reinterpret_cast<scx::MI_Wrapper<MI_SINT8>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj, scx::MI_Wrapper<MI_UINT16>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_UINT16");
        *ppValueOut = new scx::MI_Value<MI_UINT16> (
            *reinterpret_cast<scx::MI_Wrapper<MI_UINT16>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj, scx::MI_Wrapper<MI_SINT16>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_SINT16");
        *ppValueOut = new scx::MI_Value<MI_SINT16> (
            *reinterpret_cast<scx::MI_Wrapper<MI_SINT16>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj, scx::MI_Wrapper<MI_UINT32>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_UINT32");
        *ppValueOut = new scx::MI_Value<MI_UINT32> (
            *reinterpret_cast<scx::MI_Wrapper<MI_UINT32>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj, scx::MI_Wrapper<MI_SINT32>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_SINT32");
        *ppValueOut = new scx::MI_Value<MI_SINT32> (
            *reinterpret_cast<scx::MI_Wrapper<MI_SINT32>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj, scx::MI_Wrapper<MI_UINT64>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_UINT64");
        *ppValueOut = new scx::MI_Value<MI_UINT64> (
            *reinterpret_cast<scx::MI_Wrapper<MI_UINT64>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj, scx::MI_Wrapper<MI_SINT64>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_SINT64");
        *ppValueOut = new scx::MI_Value<MI_SINT64> (
            *reinterpret_cast<scx::MI_Wrapper<MI_SINT64>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj, scx::MI_Wrapper<MI_REAL32>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_REAL32");
        *ppValueOut = new scx::MI_Value<MI_REAL32> (
            *reinterpret_cast<scx::MI_Wrapper<MI_REAL32>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj, scx::MI_Wrapper<MI_REAL64>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_REAL64");
        *ppValueOut = new scx::MI_Value<MI_REAL64> (
            *reinterpret_cast<scx::MI_Wrapper<MI_REAL64>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj, scx::MI_Wrapper<MI_CHAR16>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_CHAR16");
        *ppValueOut = new scx::MI_Value<MI_CHAR16> (
            *reinterpret_cast<scx::MI_Wrapper<MI_CHAR16>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj, scx::MI_Wrapper<MI_STRING>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_STRING");
        *ppValueOut = new scx::MI_Value<MI_STRING> (
            *reinterpret_cast<scx::MI_Wrapper<MI_STRING>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj, MI_Timestamp_Wrapper::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_Timestamp_Wrapper");
        *ppValueOut = new scx::MI_Timestamp (
            *reinterpret_cast<MI_Timestamp_Wrapper*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj, MI_Interval_Wrapper::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_Interval_Wrapper");
        *ppValueOut = new scx::MI_Interval (
            *reinterpret_cast<MI_Interval_Wrapper*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj,
                 scx::MI_Array_Wrapper<MI_BOOLEANA>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_BOOLEANA");
        *ppValueOut = new scx::MI_Array<MI_BOOLEANA> (
            *reinterpret_cast<scx::MI_Array_Wrapper<MI_BOOLEANA>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj,
                 scx::MI_Array_Wrapper<MI_UINT8A>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_UINT8A");
        *ppValueOut = new scx::MI_Array<MI_UINT8A> (
            *reinterpret_cast<scx::MI_Array_Wrapper<MI_UINT8A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj,
                 scx::MI_Array_Wrapper<MI_SINT8A>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_SINT8A");
        *ppValueOut = new scx::MI_Array<MI_SINT8A> (
            *reinterpret_cast<scx::MI_Array_Wrapper<MI_SINT8A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj,
                 scx::MI_Array_Wrapper<MI_UINT16A>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_UINT16A");
        *ppValueOut = new scx::MI_Array<MI_UINT16A> (
            *reinterpret_cast<scx::MI_Array_Wrapper<MI_UINT16A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj,
                 scx::MI_Array_Wrapper<MI_SINT16A>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_SINT16A");
        *ppValueOut = new scx::MI_Array<MI_SINT16A> (
            *reinterpret_cast<scx::MI_Array_Wrapper<MI_SINT16A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj,
                 scx::MI_Array_Wrapper<MI_UINT32A>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_UINT32A");
        *ppValueOut = new scx::MI_Array<MI_UINT32A> (
            *reinterpret_cast<scx::MI_Array_Wrapper<MI_UINT32A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj,
                 scx::MI_Array_Wrapper<MI_SINT32A>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_SINT32A");
        *ppValueOut = new scx::MI_Array<MI_SINT32A> (
            *reinterpret_cast<scx::MI_Array_Wrapper<MI_SINT32A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj,
                 scx::MI_Array_Wrapper<MI_UINT64A>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_UINT64A");
        *ppValueOut = new scx::MI_Array<MI_UINT64A> (
            *reinterpret_cast<scx::MI_Array_Wrapper<MI_UINT64A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj,
                 scx::MI_Array_Wrapper<MI_SINT64A>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_SINT64A");
        *ppValueOut = new scx::MI_Array<MI_SINT64A> (
            *reinterpret_cast<scx::MI_Array_Wrapper<MI_SINT64A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj,
                 scx::MI_Array_Wrapper<MI_REAL32A>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_REAL32A");
        *ppValueOut = new scx::MI_Array<MI_REAL32A> (
            *reinterpret_cast<scx::MI_Array_Wrapper<MI_REAL32A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj,
                 scx::MI_Array_Wrapper<MI_REAL64A>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_REAL64A");
        *ppValueOut = new scx::MI_Array<MI_REAL64A> (
            *reinterpret_cast<scx::MI_Array_Wrapper<MI_REAL64A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj,
                 scx::MI_Array_Wrapper<MI_CHAR16A>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_CHAR16A");
        *ppValueOut = new scx::MI_Array<MI_CHAR16A> (
            *reinterpret_cast<scx::MI_Array_Wrapper<MI_CHAR16A>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj,
                 scx::MI_Array_Wrapper<MI_DATETIMEA>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_DATETIMEA");
        *ppValueOut = new scx::MI_Array<MI_DATETIMEA> (
            *reinterpret_cast<scx::MI_Array_Wrapper<MI_DATETIMEA>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    else if (PyObject_TypeCheck (
                 pValueObj,
                 scx::MI_Array_Wrapper<MI_STRINGA>::getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("MI_STRINGA");
        *ppValueOut = new scx::MI_Array<MI_STRINGA> (
            *reinterpret_cast<scx::MI_Array_Wrapper<MI_STRINGA>*>(
                pValueObj)->getValue ());
        ret = PY_SUCCESS;
    }
    return ret;
}


}


/*static*/ char const MI_Instance_Wrapper::NAME[] = "MI_Instance";
/*static*/ char const MI_Instance_Wrapper::OMI_NAME[] = "omi.MI_Instance";
/*static*/ char const MI_Instance_Wrapper::DOC[] =
    "omi.MI_Instance utility";
/*static*/ PyTypeObject MI_Instance_Wrapper::s_PyTypeObject = {};
/*static*/ PyMethodDef MI_Instance_Wrapper::METHODS[] = {
    { "GetValue",
      reinterpret_cast<PyCFunction>(MI_Instance_Wrapper::getValue),
      METH_KEYWORDS, "retrieve a value from the instance" },
    { "SetValue",
      reinterpret_cast<PyCFunction>(MI_Instance_Wrapper::setValue),
      METH_KEYWORDS, "set a value for the instance" },
    { NULL, NULL, 0, NULL }
};


/*static*/ void
MI_Instance_Wrapper::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_Instance_Wrapper::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_Instance_Wrapper);
    s_PyTypeObject.tp_dealloc = dealloc;
    s_PyTypeObject.tp_flags = Py_TPFLAGS_DEFAULT;
    s_PyTypeObject.tp_doc = DOC;
    s_PyTypeObject.tp_init = init;
    s_PyTypeObject.tp_new = PyType_GenericNew;
    s_PyTypeObject.tp_alloc = PyType_GenericAlloc;
    s_PyTypeObject.tp_methods = METHODS;
    if (0 == PyType_Ready (&s_PyTypeObject))
    {
        Py_INCREF (&s_PyTypeObject);
        PyModule_AddObject (
            pModule, NAME, reinterpret_cast<PyObject*>(&s_PyTypeObject));
    }
}


/*static*/ void
MI_Instance_Wrapper::dealloc (
    PyObject* pObj)
{
    //SCX_BOOKEND ("MI_Instance_Wrapper::dealloc");
    if (NULL != pObj)
    {
        MI_Instance_Wrapper* pDecl =
            reinterpret_cast<MI_Instance_Wrapper*>(pObj);
        pDecl->~MI_Instance_Wrapper ();
        pDecl->ob_type->tp_free (pObj);
    }
}


/*static*/
MI_Instance_Wrapper::PyPtr
MI_Instance_Wrapper::createPyPtr (
        MI_Instance::Ptr const& pInstance)
{
    //SCX_BOOKEND ("MI_Instance_Wrapper::createPyPtr");
    PyObjPtr pPyWrapper (s_PyTypeObject.tp_alloc (&s_PyTypeObject, 0));
    if (pPyWrapper)
    {
        SCX_BOOKEND_PRINT ("instance allocated");
        MI_Instance_Wrapper* pWrapper =
            reinterpret_cast<MI_Instance_Wrapper*>(pPyWrapper.get ());
        pWrapper->ctor (pInstance);
        return PyPtr (
            reinterpret_cast<MI_Instance_Wrapper*>(pPyWrapper.release ()),
            DO_NOT_INC_REF);
    }
    //SCX_BOOKEND_PRINT ("instance was not allocated");
    return PyPtr ();
}


/*static*/ PyTypeObject const*
MI_Instance_Wrapper::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


/*static*/ int
MI_Instance_Wrapper::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Instance_Wrapper::init");
    int rval = PY_FAILURE;
    MI_Instance_Wrapper* pInstance =
        reinterpret_cast<MI_Instance_Wrapper*>(pSelf);
    pInstance->ctor (MI_Instance::Ptr (new MI_Instance (MI_ClassDecl::Ptr ())));
    char* KEYWORDS[] = {
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (args, keywords, "", KEYWORDS))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        rval = PY_SUCCESS;
    }
    if (PY_FAILURE == rval)
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments");
    }
    return rval;
}


/*static*/
PyObject*
MI_Instance_Wrapper::getValue (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Instance_Wrapper::getValue");
    PyObject* rval = NULL;
    char* KEYWORDS[] = {
        "name",
        NULL
    };
    PyObject* pNameObj = NULL;
    if (PyArg_ParseTupleAndKeywords (args, keywords, "O", KEYWORDS, &pNameObj))
    {
        MI_Type<MI_STRING>::type_t name;
        int ret = fromPyObject (pNameObj, &name);
        if (PY_SUCCESS == ret)
        {
            MI_Instance_Wrapper* pInstance =
                reinterpret_cast<MI_Instance_Wrapper*>(pSelf);
            MI_ValueBase::Ptr pValue;
            ret = pInstance->m_pInstance->getValue (name, &pValue);
            if (0 == ret)
            {
                //SCX_BOOKEND_PRINT ("Name is a member of MI_ClassDecl");
                if (pValue)
                {
                    switch (pValue->getType ())
                    {
                    case MI_BOOLEAN:
                        rval = wrap_value<MI_BOOLEAN> (pValue);
                        break;
                    case MI_UINT8:
                        rval = wrap_value<MI_UINT8> (pValue);
                        break;
                    case MI_SINT8:
                        rval = wrap_value<MI_SINT8> (pValue);
                        break;
                    case MI_UINT16:
                        rval = wrap_value<MI_UINT16> (pValue);
                        break;
                    case MI_SINT16:
                        rval = wrap_value<MI_SINT16> (pValue);
                        break;
                    case MI_UINT32:
                        rval = wrap_value<MI_UINT32> (pValue);
                        break;
                    case MI_SINT32:
                        rval = wrap_value<MI_SINT32> (pValue);
                        break;
                    case MI_UINT64:
                        rval = wrap_value<MI_UINT64> (pValue);
                        break;
                    case MI_SINT64:
                        rval = wrap_value<MI_SINT64> (pValue);
                        break;
                    case MI_REAL32:
                        rval = wrap_value<MI_REAL32> (pValue);
                        break;
                    case MI_REAL64:
                        rval = wrap_value<MI_REAL64> (pValue);
                        break;
                    case MI_CHAR16:
                        rval = wrap_value<MI_CHAR16> (pValue);
                        break;
                    case MI_DATETIME:
                        rval = wrap_datetime (pValue);
                        break;
                    case MI_STRING:
                        rval = wrap_value<MI_STRING> (pValue);
                        break;
                    case MI_REFERENCE:
                    case MI_INSTANCE:
                        SCX_BOOKEND_PRINT ("encountered an unhandled type");
                        Py_INCREF (Py_None);
                        rval = Py_None;
                        break;
                    case MI_BOOLEANA:
                        rval = wrap_array<MI_BOOLEANA> (pValue);
                        break;
                    case MI_UINT8A:
                        rval = wrap_array<MI_UINT8A> (pValue);
                        break;
                    case MI_SINT8A:
                        rval = wrap_array<MI_SINT8A> (pValue);
                        break;
                    case MI_UINT16A:
                        rval = wrap_array<MI_UINT16A> (pValue);
                        break;
                    case MI_SINT16A:
                        rval = wrap_array<MI_SINT16A> (pValue);
                        break;
                    case MI_UINT32A:
                        rval = wrap_array<MI_UINT32A> (pValue);
                        break;
                    case MI_SINT32A:
                        rval = wrap_array<MI_SINT32A> (pValue);
                        break;
                    case MI_UINT64A:
                        rval = wrap_array<MI_UINT64A> (pValue);
                        break;
                    case MI_SINT64A:
                        rval = wrap_array<MI_SINT64A> (pValue);
                        break;
                    case MI_REAL32A:
                        rval = wrap_array<MI_REAL32A> (pValue);
                        break;
                    case MI_REAL64A:
                        rval = wrap_array<MI_REAL64A> (pValue);
                        break;
                    case MI_CHAR16A:
                        rval = wrap_array<MI_CHAR16A> (pValue);
                        break;
                    case MI_DATETIMEA:
                        rval = wrap_array<MI_DATETIMEA> (pValue);
                        break;
                    case MI_STRINGA:
                        rval = wrap_array<MI_STRINGA> (pValue);
                        break;
                    case MI_REFERENCEA:
                    case MI_INSTANCEA:
                    default:
                        SCX_BOOKEND_PRINT ("encountered an unhandled type");
                        Py_INCREF (Py_None);
                        rval = Py_None;
                        break;
                    }
                }
                else
                {
                    Py_INCREF (Py_None);
                    rval = Py_None;
                }
            }
            else
            {
                SCX_BOOKEND_PRINT ("Value name not a member of MI_ClassDecl");
                // error: Name is not a member of MI_ClassDecl
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("Name convert failed");
            // error: Py_to_MI_convert failed
        }
    }
    else
    {
        // error: PyArg_ParseTupleAndKeywords failed
    }
    return rval;
}


/*static*/
PyObject*
MI_Instance_Wrapper::setValue (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Instance_Wrapper::setValue");
    PyObject* rval = NULL;
    char* KEYWORDS[] = {
        "name",
        "value",
        NULL
    };
    PyObject* pNameObj = NULL;
    PyObject* pValueObj = NULL;
    if (PyArg_ParseTupleAndKeywords (args, keywords, "OO", KEYWORDS,
                                     &pNameObj, &pValueObj))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        MI_Type<MI_STRING>::type_t name;
        int ret = fromPyObject (pNameObj, &name);
        if (PY_SUCCESS == ret)
        {
            MI_Instance_Wrapper* pInstance =
                reinterpret_cast<MI_Instance_Wrapper*>(pSelf);
            if (pInstance->m_pInstance->getObjectDecl ())
            {
                MI_ParameterDecl::ConstPtr pParameterDecl =
                    pInstance->m_pInstance->getObjectDecl ()->getParameterDecl (
                        name);
                if (pParameterDecl)
                {
                    //SCX_BOOKEND_PRINT ("A parameter was found for Name");
                    std::ostringstream strm;
                    strm << "A parameter was found for " << name;
                    SCX_BOOKEND_PRINT (strm.str ());
                    strm.str ("");
                    strm.clear ();
                    strm << "parameter name: "
                         << pParameterDecl->getName ()->getValue ();
                    SCX_BOOKEND_PRINT (strm.str ());
                    strm.str ("");
                    strm.clear ();
                    strm << "type: "
                         << (pParameterDecl->getType ()->getValue ());
                    SCX_BOOKEND_PRINT (strm.str ());
                    MI_ValueBase::Ptr pValue;
                    ret = convertToBase (pParameterDecl->getType ()->getValue (),
                                         pValueObj, &pValue);
                    if (PY_SUCCESS == ret)
                    {
                        SCX_BOOKEND_PRINT ("to_MI_ValueBase succeeded");
                        pInstance->m_pInstance->setValue (name, pValue);
                        rval = Py_None;
                    }
                    else
                    {
                        SCX_BOOKEND_PRINT ("Py_to_MI_convert failed");
                    }
                }
                else
                {
                    SCX_BOOKEND_PRINT ("Name is not a parameter");
                }
            }
            else
            {
                //SCX_BOOKEND_PRINT ("There is no MI_ObjectDecl");
                
                MI_ValueBase::Ptr pValue;
                ret = convertToBase (pValueObj, &pValue);

                if (pValue)
                {
                    //SCX_BOOKEND_PRINT ("Value is a MI_Type");
                    pInstance->m_pInstance->setValue (name, pValue);
                    rval = Py_None;
                }
                else
                {
                    // error
                    SCX_BOOKEND_PRINT ("Value is not a MI_Type");
                }
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("Name convert failed");
            // error: Py_to_MI_convert failed
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        // error: PyArg_ParseTupleAndKeywords failed
    }
    Py_XINCREF (rval);
    return rval;
}


void
MI_Instance_Wrapper::ctor (
    MI_Instance::Ptr const& pInstance)
{
    //SCX_BOOKEND ("MI_Instance_Wrapper::ctor");
    new (&m_pInstance) MI_Instance::Ptr (pInstance);
}


void
MI_Instance_Wrapper::dtor ()
{
    //SCX_BOOKEND ("MI_Instance_Wrapper::dtor");
    typedef MI_Instance::Ptr ptr;
    m_pInstance.~ptr ();
}
