#ifndef INCLUDED_MI_WRAPPER_HPP
#define INCLUDED_MI_WRAPPER_HPP


#ifndef __MI_WRAPPER_COPY_CTOR__
#define __MI_WRAPPER_COPY_CTOR__ (0)
#endif


#ifndef __MI_WRAPPER_ASSIGN_OP__
#define __MI_WRAPPER_ASSIGN_OP__ (0)
#endif


#include "Python.h"


#include "mi_value.hpp"
#include "py_converter.hpp"
#include "py_ptr.hpp"
#include "shared.hpp"


#include <cmath>


namespace scx
{


// forward declaration
//------------------------------------------------------------------------------
template<TypeID_t TYPE_ID>
class MI_Array_Wrapper;


// class MI_Wrapper
//------------------------------------------------------------------------------
template<TypeID_t TYPE_ID>
class MI_Wrapper
{
public:
    typedef py_ptr<MI_Wrapper<TYPE_ID> > PyPtr;

    static void moduleInit (PyObject* const pModule);
    static PyTypeObject* getPyTypeObject ();

    static void dealloc (PyObject* pObj);
//    static PyObject* newObj (PyTypeObject* pType,
//                             PyObject* args,
//                             PyObject* keywords);
    static int init (PyObject* pSelf, PyObject* args, PyObject* keywords);
    static PyPtr createPyPtr (typename MI_Value<TYPE_ID>::Ptr const& pValue);
    static PyObject* _getType (PyObject* pSelf);
    static PyObject* _getValue (MI_Wrapper<TYPE_ID>* pSelf, void*);
    static int _setValue (MI_Wrapper<TYPE_ID>* pSelf, PyObject* pValue, void*);
    static PyObject* to_str (PyObject* pSelf);

    void ctor (typename MI_Value<TYPE_ID>::Ptr const& pValue);
    void dtor ();

    MI_Value<TYPE_ID>* getValue () const;
//    void setValue (typename MI_Value<TYPE_ID>::type_t const& val);


private:
    PyObject_HEAD

    typename MI_Value<TYPE_ID>::Ptr m_pValue;

//    void setValue (MI_Value<TYPE_ID>* pVal);

    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyGetSetDef s_Mutators[];
    static PyMethodDef s_Methods[];

//    static int s_count;

    static PyTypeObject s_PyTypeObject;
    static PyMethodDef METHODS[];
};


template<>
/*static*/ PyTypeObject MI_Wrapper<MI_BOOLEAN>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Wrapper<MI_UINT8>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Wrapper<MI_SINT8>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Wrapper<MI_UINT16>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Wrapper<MI_SINT16>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Wrapper<MI_UINT32>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Wrapper<MI_SINT32>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Wrapper<MI_UINT64>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Wrapper<MI_SINT64>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Wrapper<MI_REAL32>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Wrapper<MI_REAL64>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Wrapper<MI_CHAR16>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Wrapper<MI_STRING>::s_PyTypeObject;


// class MI_Timestamp_Wrapper
//------------------------------------------------------------------------------
class MI_Timestamp_Wrapper
{
public:
    typedef py_ptr<MI_Timestamp_Wrapper> PyPtr;

    static void moduleInit (PyObject* const pModule);
    static PyTypeObject* getPyTypeObject ();

    static void dealloc (PyObject* pObj);
//    static PyObject* newObj (PyTypeObject* pType,
//                             PyObject* args,
//                             PyObject* keywords);
    static int init (PyObject* pSelf, PyObject* args, PyObject* keywords);
    static PyPtr createPyPtr (MI_Timestamp::Ptr const& pValue);
    static PyObject* _getType (PyObject* pSelf);

    static PyObject* _isTimestamp (MI_Timestamp_Wrapper* pSelf, void*);

    static PyObject* _getYear (MI_Timestamp_Wrapper* pSelf, void*);
    static PyObject* _getMonth (MI_Timestamp_Wrapper* pSelf, void*);
    static PyObject* _getDay (MI_Timestamp_Wrapper* pSelf, void*);
    static PyObject* _getHour (MI_Timestamp_Wrapper* pSelf, void*);
    static PyObject* _getMinute (MI_Timestamp_Wrapper* pSelf, void*);
    static PyObject* _getSecond (MI_Timestamp_Wrapper* pSelf, void*);
    static PyObject* _getMicroseconds (MI_Timestamp_Wrapper* pSelf, void*);
    static PyObject* _getUTC (MI_Timestamp_Wrapper* pSelf, void*);

    static int _setYear (MI_Timestamp_Wrapper* pSelf, PyObject* pValue, void*);
    static int _setMonth (MI_Timestamp_Wrapper* pSelf, PyObject* pValue, void*);
    static int _setDay (MI_Timestamp_Wrapper* pSelf, PyObject* pValue, void*);
    static int _setHour (MI_Timestamp_Wrapper* pSelf, PyObject* pValue, void*);
    static int _setMinute (
        MI_Timestamp_Wrapper* pSelf, PyObject* pValue, void*);
    static int _setSecond (
        MI_Timestamp_Wrapper* pSelf, PyObject* pValue, void*);
    static int _setMicroseconds (
        MI_Timestamp_Wrapper* pSelf, PyObject* pValue, void*);
    static int _setUTC (MI_Timestamp_Wrapper* pSelf, PyObject* pValue, void*);

    static PyObject* to_str (PyObject* pSelf);

    void ctor (MI_Timestamp::Ptr const& pTimestamp);
    void dtor ();

    MI_Timestamp::Ptr const& getValue ();

    template<typename char_t, typename traits_t>
    std::basic_ostream<char_t, traits_t>&
    to_stream (std::basic_ostream<char_t, traits_t>& strm) const;

    static char const NAME[];

private:
    PyObject_HEAD

    MI_Timestamp::Ptr m_pTimestamp;

    static char const OMI_NAME[];
    static char const DOC[];
    static PyTypeObject s_PyTypeObject;
    static PyGetSetDef MUTATORS[];
    static PyMethodDef METHODS[];
};


// class MI_Interval_Wrapper
//------------------------------------------------------------------------------
class MI_Interval_Wrapper
{
public:
    typedef py_ptr<MI_Interval_Wrapper> PyPtr;

    static void moduleInit (PyObject* const pModule);
    static PyTypeObject* getPyTypeObject ();

    static void dealloc (PyObject* pObj);
//    static PyObject* newObj (PyTypeObject* pType,
//                             PyObject* args,
//                             PyObject* keywords);
    static int init (PyObject* pSelf, PyObject* args, PyObject* keywords);
    static PyPtr createPyPtr (MI_Interval::Ptr const& pValue);
    static PyObject* _getType (PyObject* pSelf);

    static PyObject* _isTimestamp (MI_Interval_Wrapper* pSelf, void*);

    static PyObject* _getDays (MI_Interval_Wrapper* pSelf, void*);
    static PyObject* _getHours (MI_Interval_Wrapper* pSelf, void*);
    static PyObject* _getMinutes (MI_Interval_Wrapper* pSelf, void*);
    static PyObject* _getSeconds (MI_Interval_Wrapper* pSelf, void*);
    static PyObject* _getMicroseconds (MI_Interval_Wrapper* pSelf, void*);

    static int _setDays (MI_Interval_Wrapper* pSelf, PyObject* pValue, void*);
    static int _setHours (MI_Interval_Wrapper* pSelf, PyObject* pValue, void*);
    static int _setMinutes (
        MI_Interval_Wrapper* pSelf, PyObject* pValue, void*);
    static int _setSeconds (
        MI_Interval_Wrapper* pSelf, PyObject* pValue, void*);
    static int _setMicroseconds (
        MI_Interval_Wrapper* pSelf, PyObject* pValue, void*);

    static PyObject* to_str (PyObject* pSelf);

    void ctor (MI_Interval::Ptr const& pInterval);
    void dtor ();

    MI_Interval::Ptr const& getValue ();

    template<typename char_t, typename traits_t>
    std::basic_ostream<char_t, traits_t>&
    to_stream (std::basic_ostream<char_t, traits_t>& strm) const;

    static char const NAME[];

private:
    static char const OMI_NAME[];
    static char const DOC[];
    static PyTypeObject s_PyTypeObject;
    static PyGetSetDef MUTATORS[];
    static PyMethodDef METHODS[];

    PyObject_HEAD

    MI_Interval::Ptr m_pInterval;
};


// class MI_Array_Iterator
//------------------------------------------------------------------------------
template<TypeID_t TYPE_ID>
class MI_Array_Iterator
{
public:
    typedef py_ptr<MI_Array_Iterator<TYPE_ID> > PyPtr;
    typedef typename MI_Array_Wrapper<TYPE_ID>::Value_t Value_t;

    static void moduleInit (PyObject* const pModule);

    static void dealloc (PyObject* pObj);

    static PyPtr createPyPtr (typename MI_Array<TYPE_ID>::Ptr const& pArray,
                              size_t index);

    static PyObject* _getValue (MI_Array_Iterator<TYPE_ID>* pSelf, void*);
    static int _setValue (MI_Array_Iterator<TYPE_ID>* pSelf,
                          PyObject* pValue,
                          void*);

    static PyObject* iterNext (PyObject* pObj);

    static PyObject* to_str (PyObject* pSelf);

    void ctor (typename MI_Array<TYPE_ID>::Ptr const& pArray,
               size_t index);
    void dtor ();

private:
    /*ctor*/ MI_Array_Iterator (MI_Array_Iterator const&); // delete
    MI_Array_Iterator& operator = (MI_Array_Iterator const&); // delete

    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyGetSetDef s_Mutators[];
    static PyTypeObject s_PyTypeObject;

    PyObject_HEAD

    typename scx::MI_Array<TYPE_ID>::Ptr m_pArray;
    size_t m_Index;
};


// class MI_Array_Iterator<MI_DATETIMEA> specialization
//------------------------------------------------------------------------------
template<>
class MI_Array_Iterator<MI_DATETIMEA>
{
public:
    typedef py_ptr<MI_Array_Iterator<MI_DATETIMEA> > PyPtr;

    static void moduleInit (PyObject* const pModule);

    static void dealloc (PyObject* pObj);

    static PyPtr createPyPtr (MI_Array<MI_DATETIMEA>::Ptr const& pArray,
                              size_t index);

    static PyObject* _getValue (MI_Array_Iterator<MI_DATETIMEA>* pSelf, void*);
    static int _setValue (MI_Array_Iterator<MI_DATETIMEA>* pSelf,
                          PyObject* pValue,
                          void*);

    static PyObject* iterNext (PyObject* pObj);

    static PyObject* to_str (PyObject* pSelf);

    void ctor (MI_Array<MI_DATETIMEA>::Ptr const& pArray,
               size_t index);
    void dtor ();

private:
    /*ctor*/ MI_Array_Iterator (MI_Array_Iterator const&); // delete
    MI_Array_Iterator& operator = (MI_Array_Iterator const&); // delete

    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyGetSetDef s_Mutators[];
    static PyTypeObject s_PyTypeObject;

    PyObject_HEAD

    scx::MI_Array<MI_DATETIMEA>::Ptr m_pArray;
    size_t m_Index;
};


// class MI_Array_Wrapper
//------------------------------------------------------------------------------
template<TypeID_t TYPE_ID>
class MI_Array_Wrapper
{
public:
    typedef py_ptr<MI_Array_Wrapper<TYPE_ID> > PyPtr;
    typedef typename MI_Type<TYPE_ID & ~MI_ARRAY>::type_t Value_t;

    static void moduleInit (PyObject* const pModule);

    static void dealloc (PyObject* pObj);

    static int init (PyObject* pSelf, PyObject* args, PyObject* keywords);

    static PyPtr createPyPtr (typename MI_Array<TYPE_ID>::Ptr const& pArray);

    static PyObject* _getType (PyObject* pSelf);

    static PyObject* _getValueAt (PyObject* pSelf,
                                  PyObject* args,
                                  PyObject* keywords);
    static PyObject* _setValueAt (PyObject* pSelf,
                                  PyObject* args,
                                  PyObject* keywords);

    static PyObject* _append (PyObject* pSelf,
                              PyObject* args,
                              PyObject* keywords);
    static PyObject* _insert (PyObject* pSelf,
                              PyObject* args,
                              PyObject* keywords);
    static PyObject* _pop (PyObject* pSelf,
                           PyObject* args,
                           PyObject* keywords);

    static PyObject* _count (PyObject* pSelf);

    static PyObject* getIter (PyObject* pObj);

    static PyObject* to_str (PyObject* pSelf);

    static PyTypeObject* getPyTypeObject ();

    void ctor ();
    void dtor ();

    MI_Array<TYPE_ID>* getValue () const;

private:
    /*ctor*/ MI_Array_Wrapper (MI_Array_Wrapper const&); // delete
    MI_Array_Wrapper& operator = (MI_Array_Wrapper const&); // delete

    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyMethodDef METHODS[];
    static PyTypeObject s_PyTypeObject;

    PyObject_HEAD

    typename MI_Array<TYPE_ID>::Ptr m_pArray;
};


// class MI_Array_Wrapper<MI_DATETIMEA> specialization
//------------------------------------------------------------------------------
template<>
class MI_Array_Wrapper<MI_DATETIMEA>
{
public:
    typedef py_ptr<MI_Array_Wrapper<MI_DATETIMEA> > PyPtr;

    static void moduleInit (PyObject* const pModule);

    static void dealloc (PyObject* pObj);

    static int init (PyObject* pSelf, PyObject* args, PyObject* keywords);

    static PyPtr createPyPtr (MI_Array<MI_DATETIMEA>::Ptr const& pArray);

    static PyObject* _getType (PyObject* pSelf);

    static PyObject* _getValueAt (PyObject* pSelf,
                                  PyObject* args,
                                  PyObject* keywords);
    static PyObject* _setValueAt (PyObject* pSelf,
                                  PyObject* args,
                                  PyObject* keywords);

    static PyObject* _append (PyObject* pSelf,
                              PyObject* args,
                              PyObject* keywords);
    static PyObject* _insert (PyObject* pSelf,
                              PyObject* args,
                              PyObject* keywords);
    static PyObject* _pop (PyObject* pSelf,
                           PyObject* args,
                           PyObject* keywords);

    static PyObject* _count (PyObject* pSelf);

    static PyObject* getIter (PyObject* pObj);

    static PyObject* to_str (PyObject* pSelf);

    static PyTypeObject* getPyTypeObject ();

    void ctor ();
    void dtor ();

    MI_Array<MI_DATETIMEA>* getValue () const;

private:
    /*ctor*/ MI_Array_Wrapper (MI_Array_Wrapper const&); // delete
    MI_Array_Wrapper& operator = (MI_Array_Wrapper const&); // delete

    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyMethodDef METHODS[];
    static PyTypeObject s_PyTypeObject;

    PyObject_HEAD

    MI_Array<MI_DATETIMEA>::Ptr m_pArray;
};


// class MI_PropertySet_Wrapper
//------------------------------------------------------------------------------
class MI_PropertySet_Wrapper
{
public:
    PyObject_HEAD

    typedef py_ptr<MI_PropertySet_Wrapper> PyPtr;

    static void moduleInit (PyObject* const pModule);
    static PyTypeObject* getPyTypeObject ();

    static void dealloc (PyObject* pObj);
    static PyObject* newObj (PyTypeObject* pType,
                             PyObject* args,
                             PyObject* keywords);
    static int init (PyObject* pSelf, PyObject* args, PyObject* keywords);

    static PyObject* to_str (PyObject* pSelf);

    static PyPtr createPyPtr (MI_PropertySet::ConstPtr const& pPropertySet);

    static PyObject* _GetElementCount (MI_PropertySet_Wrapper* pSelf,
                                       void*);

    static PyObject* _ContainsElement (PyObject* pSelf,
                                       PyObject* args,
                                       PyObject* keywords);

    static PyObject* _GetElementAt (PyObject* pSelf,
                                    PyObject* args,
                                    PyObject* keywords);

    /*ctor*/ MI_PropertySet_Wrapper (
        MI_PropertySet::ConstPtr const& pPropertySet);
    /*dtor*/ ~MI_PropertySet_Wrapper ();

private:
    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyMethodDef METHODS[];
    static PyTypeObject s_PyTypeObject;

    MI_PropertySet::ConstPtr m_pPropertySet;
};


template<>
/*static*/ PyTypeObject MI_Array_Wrapper<MI_BOOLEANA>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Array_Iterator<MI_BOOLEANA>::s_PyTypeObject;

template<>
/*static*/ PyTypeObject MI_Array_Wrapper<MI_UINT8A>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Array_Iterator<MI_UINT8A>::s_PyTypeObject;

template<>
/*static*/ PyTypeObject MI_Array_Wrapper<MI_SINT8A>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Array_Iterator<MI_SINT8A>::s_PyTypeObject;

template<>
/*static*/ PyTypeObject MI_Array_Wrapper<MI_UINT16A>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Array_Iterator<MI_UINT16A>::s_PyTypeObject;

template<>
/*static*/ PyTypeObject MI_Array_Wrapper<MI_SINT16A>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Array_Iterator<MI_SINT16A>::s_PyTypeObject;

template<>
/*static*/ PyTypeObject MI_Array_Wrapper<MI_UINT32A>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Array_Iterator<MI_UINT32A>::s_PyTypeObject;

template<>
/*static*/ PyTypeObject MI_Array_Wrapper<MI_SINT32A>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Array_Iterator<MI_SINT32A>::s_PyTypeObject;

template<>
/*static*/ PyTypeObject MI_Array_Wrapper<MI_UINT64A>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Array_Iterator<MI_UINT64A>::s_PyTypeObject;

template<>
/*static*/ PyTypeObject MI_Array_Wrapper<MI_SINT64A>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Array_Iterator<MI_SINT64A>::s_PyTypeObject;

template<>
/*static*/ PyTypeObject MI_Array_Wrapper<MI_REAL32A>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Array_Iterator<MI_REAL32A>::s_PyTypeObject;

template<>
/*static*/ PyTypeObject MI_Array_Wrapper<MI_REAL64A>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Array_Iterator<MI_REAL64A>::s_PyTypeObject;

template<>
/*static*/ PyTypeObject MI_Array_Wrapper<MI_CHAR16A>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Array_Iterator<MI_CHAR16A>::s_PyTypeObject;

template<>
/*static*/ PyTypeObject MI_Array_Wrapper<MI_STRINGA>::s_PyTypeObject;
template<>
/*static*/ PyTypeObject MI_Array_Iterator<MI_STRINGA>::s_PyTypeObject;

//template<>
///*static*/ PyTypeObject MI_Array_Wrapper<MI_DATETIMEA>::s_PyTypeObject;
//template<>
///*static*/ PyTypeObject MI_Array_Iterator<MI_DATETIMEA>::s_PyTypeObject;


//MI_BOOLEAN
//MI_UINT8
//MI_SINT8
//MI_UINT16
//MI_SINT16
//MI_UINT32
//MI_SINT32
//MI_UINT64
//MI_SINT64
//MI_REAL32
//MI_REAL64
//MI_CHAR16
//MI_DATETIME
//MI_STRING
//MI_REFERENCE
//MI_INSTANCE
//MI_BOOLEANA
//MI_UINT8A
//MI_SINT8A
//MI_UINT16A
//MI_SINT16A
//MI_UINT32A
//MI_SINT32A
//MI_UINT64A
//MI_SINT64A
//MI_REAL32A
//MI_REAL64A
//MI_CHAR16A
//MI_DATETIMEA
//MI_STRINGA
//MI_REFERENCEA
//MI_INSTANCEA


                             
// * MI_BOOLEAN
// * MI_UINT8
// * MI_SINT8
// * MI_UINT16
// * MI_SINT16
// * MI_UINT32
// * MI_SINT32
// * MI_UINT64
// * MI_SINT64
// * MI_REAL32
// * MI_REAL64
// * MI_CHAR16
//   MI_DATETIME
// * MI_STRING
//   MI_REFERENCE
//   MI_INSTANCE


template<TypeID_t TYPE_ID>
/*static*/ void
MI_Wrapper<TYPE_ID>::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_Wrapper::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_Wrapper<TYPE_ID>);
    s_PyTypeObject.tp_dealloc = dealloc;
    s_PyTypeObject.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    s_PyTypeObject.tp_doc = DOC;
    s_PyTypeObject.tp_init = init;
    s_PyTypeObject.tp_new = PyType_GenericNew;
    s_PyTypeObject.tp_alloc = PyType_GenericAlloc;
    s_PyTypeObject.tp_getset = s_Mutators;
    s_PyTypeObject.tp_methods = s_Methods;
    s_PyTypeObject.tp_str = to_str;
    if (0 == PyType_Ready (&s_PyTypeObject))
    {
        Py_INCREF (&s_PyTypeObject);
        PyModule_AddObject (pModule, NAME,
                            reinterpret_cast<PyObject*>(&s_PyTypeObject));
    }
    else
    {
        SCX_BOOKEND_PRINT ("moduleInit failed");
    }
}


template<TypeID_t TYPE_ID>
/*static*/ PyTypeObject*
MI_Wrapper<TYPE_ID>::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


template<TypeID_t TYPE_ID>
/*static*/ void
MI_Wrapper<TYPE_ID>::dealloc (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Wrapper::dealloc");
    MI_Wrapper<TYPE_ID>* pWrapper =
        reinterpret_cast<MI_Wrapper<TYPE_ID>*>(pSelf);
    pWrapper->dtor ();
    pWrapper->ob_type->tp_free (pSelf);
}


//template<TypeID_t TYPE_ID>
///*static*/ PyObject*
//MI_Wrapper<TYPE_ID>::newObj (
//    PyTypeObject* pType,
//    PyObject* args,
//    PyObject* keywords)
//{
//    //SCX_BOOKEND ("MI_Wrapper::newObj");
//    return pType->tp_alloc (pType, 0);
//}


template<>
/*static*/ int
MI_Wrapper<MI_BOOLEAN>::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords);


template<TypeID_t TYPE_ID>
/*static*/ int
MI_Wrapper<TYPE_ID>::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Wrapper::init");
    int rval = PY_FAILURE;
    MI_Wrapper<TYPE_ID>* pWrapper =
        reinterpret_cast<MI_Wrapper<TYPE_ID>*>(pSelf);
    pWrapper->ctor (typename MI_Value<TYPE_ID>::Ptr ());
    PyObject* pValue = NULL;
    char* KEYWORDS[] = {
        "value",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "|O", KEYWORDS, &pValue))
    {
        if (NULL == pValue ||
            Py_None == pValue)
        {
            //SCX_BOOKEND_PRINT ("NULL or PyNone");
            rval = PY_SUCCESS;
        }
#if (__MI_WRAPPER_COPY_CTOR__)
        else if (PyObject_TypeCheck (pValue, &s_PyTypeObject))
        {
            //SCX_BOOKEND_PRINT ("MI_Wrapper<TYPE_ID>");
            MI_Wrapper<TYPE_ID>* pOtherWrapper =
                reinterpret_cast<MI_Wrapper<TYPE_ID>*>(pValue);
            pWrapper->m_pValue = pOtherWrapper->m_pValue;
            rval = PY_SUCCESS;
        }
#endif // __MI_WRAPPER_COPY_CTOR__
        else
        {
            rval = to_MI_Value<TYPE_ID> (pValue, &(pWrapper->m_pValue));
        }
    }
    if (PY_FAILURE == rval)
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments");
    }
    return rval;
}


template<>
/*static*/ MI_Wrapper<MI_BOOLEAN>::PyPtr
MI_Wrapper<MI_BOOLEAN>::createPyPtr (
    MI_Value<MI_BOOLEAN>::Ptr const& pValue);


template<TypeID_t TYPE_ID>
/*static*/ typename MI_Wrapper<TYPE_ID>::PyPtr
MI_Wrapper<TYPE_ID>::createPyPtr (
    typename MI_Value<TYPE_ID>::Ptr const& pValue)
{
    SCX_BOOKEND ("MI_Wrapper::createPyPtr");
    PyObjPtr pPyWrapper (s_PyTypeObject.tp_alloc (&s_PyTypeObject, 0));
    //SCX_BOOKEND_PRINT ("mark 2");
    if (pPyWrapper)
    {
        //SCX_BOOKEND_PRINT ("mark 4");
        MI_Wrapper<TYPE_ID>* pWrapper =
            reinterpret_cast<MI_Wrapper<TYPE_ID>*>(pPyWrapper.get ());
        //SCX_BOOKEND_PRINT ("mark 6");
        pWrapper->ctor (pValue);
        //SCX_BOOKEND_PRINT ("mark 8");
        return PyPtr (
            reinterpret_cast<MI_Wrapper<TYPE_ID>*>(pPyWrapper.release ()),
            DO_NOT_INC_REF);
    }
    //SCX_BOOKEND_PRINT ("mark 10");
    return PyPtr ();
}


template<TypeID_t TYPE_ID>
/*static*/ PyObject*
MI_Wrapper<TYPE_ID>::_getType (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Wrapper::_getType");
    return PyInt_FromSize_t (TYPE_ID);
}


template<>
/*static*/ PyObject*
MI_Wrapper<MI_BOOLEAN>::_getValue (
    MI_Wrapper<MI_BOOLEAN>* pSelf,
    void*);


template<TypeID_t TYPE_ID>
/*static*/ PyObject*
MI_Wrapper<TYPE_ID>::_getValue (
    MI_Wrapper<TYPE_ID>* pSelf,
    void*)
{
    //SCX_BOOKEND ("MI_Wrapper::_getValue");
    MI_Value<TYPE_ID> const* pValue = pSelf->getValue ();
    if (NULL != pValue)
    {
        return toPyObject (pValue->getValue ());
    }
    Py_RETURN_NONE;
}


template<>
/*static*/ int
MI_Wrapper<MI_BOOLEAN>::_setValue (
    MI_Wrapper<MI_BOOLEAN>* pSelf,
    PyObject* pValue,
    void*);


template<TypeID_t TYPE_ID>
/*static*/ int
MI_Wrapper<TYPE_ID>::_setValue (
    MI_Wrapper<TYPE_ID>* pSelf,
    PyObject* pValue,
    void*)
{
    //SCX_BOOKEND ("MI_Wrapper::_setValue");
    int rval = PY_FAILURE;
    if (NULL == pValue ||
        Py_None == pValue)
    {
        //SCX_BOOKEND_PRINT ("***** NULL or PyNone");
        pSelf->m_pValue.reset ();
        rval = PY_SUCCESS;
    }
#if (__MI_WRAPPER_ASSIGN_OP__)
    else if (PyObject_TypeCheck (pValue, getPyTypeObject ()))
    {
        //SCX_BOOKEND_PRINT ("***** MI_Wrapper<TYPE_ID>");
        MI_Wrapper<TYPE_ID>* pWrapper =
            reinterpret_cast<MI_Wrapper<TYPE_ID>*>(pValue);
        pSelf->m_pValue = pWrapper->m_pValue;
        rval = PY_SUCCESS;
    }
#endif // __MI_WRAPPER_ASSIGN_OP__
    else
    {
        rval = to_MI_Value<TYPE_ID> (pValue, &(pSelf->m_pValue));
    }
    if (PY_FAILURE == rval)
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments");
    }
    return rval;
}


template<TypeID_t TYPE_ID>
/*static*/ PyObject*
MI_Wrapper<TYPE_ID>::to_str (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Wrapper::to_str");
    MI_Wrapper<TYPE_ID> const* pWrapper =
        reinterpret_cast<MI_Wrapper<TYPE_ID> const*>(pSelf);
    std::ostringstream strm;
    strm << NAME << '(';
    if (pWrapper->m_pValue)
    {
        strm << pWrapper->m_pValue->getValue ();
    }
    else
    {
        strm << "None";
    }
    strm << ')';
    return PyString_FromString (strm.str ().c_str ());
    //return MI_to_str<TYPE_ID>::to_str (pSelf);
}


template<>
/*static*/ PyObject*
MI_Wrapper<MI_BOOLEAN>::to_str (
    PyObject* pSelf);


template<>
/*static*/ PyObject*
MI_Wrapper<MI_SINT8>::to_str (
    PyObject* pSelf);


template<>
/*static*/ PyObject*
MI_Wrapper<MI_UINT8>::to_str (
    PyObject* pSelf);


template<TypeID_t TYPE_ID>
void
MI_Wrapper<TYPE_ID>::ctor (
    typename MI_Value<TYPE_ID>::Ptr const& pValue)
{
    //SCX_BOOKEND ("MI_Wrapper::ctor");
    new (&m_pValue) typename MI_Value<TYPE_ID>::Ptr (pValue);
}


template<TypeID_t TYPE_ID>
void
MI_Wrapper<TYPE_ID>::dtor ()
{
    //SCX_BOOKEND ("MI_Wrapper::dtor");
    typedef typename util::internal_counted_ptr<MI_Value<TYPE_ID> > ptr;
    m_pValue.~ptr ();
}


//template<TypeID_t TYPE_ID>
//void
//MI_Wrapper<TYPE_ID>::setValue (
//    typename MI_Value<TYPE_ID>::type_t const& val)
//{
//    (*m_pValue) = val;
//}


template<TypeID_t TYPE_ID>
MI_Value<TYPE_ID>*
MI_Wrapper<TYPE_ID>::getValue () const
{
    //SCX_BOOKEND ("MI_Wrapper::getValue");
    return m_pValue.get ();
}


//template<TypeID_t TYPE_ID>
//void
//MI_Wrapper<TYPE_ID>::setValue (
//    MI_Value<TYPE_ID>* pVal)
//{
//    m_pValue = pVal;
//}


// class MI_Timestamp_Wrapper
//------------------------------------------------------------------------------
template<typename char_t, typename traits_t>
std::basic_ostream<char_t, traits_t>&
MI_Timestamp_Wrapper::to_stream (
    std::basic_ostream<char_t, traits_t>& strm) const
{
    strm << NAME
         << "(Year(" << m_pTimestamp->getYear ()
         << "),Month(" << m_pTimestamp->getMonth ()
         << "),Day(" << m_pTimestamp->getDay ()
         << "),Hour(" << m_pTimestamp->getHour ()
         << "),Minute(" << m_pTimestamp->getMinute ()
         << "),Second(" << m_pTimestamp->getSecond ()
         << "),Microseconds(" << m_pTimestamp->getMicroseconds ()
         << "),UTC(" << m_pTimestamp->getUTC () << "))";
    return strm;
}


// class MI_Interval_Wrapper
//------------------------------------------------------------------------------
template<typename char_t, typename traits_t>
std::basic_ostream<char_t, traits_t>&
MI_Interval_Wrapper::to_stream (
    std::basic_ostream<char_t, traits_t>& strm) const
{
    strm << NAME
         << "(Days(" << m_pInterval->getDays ()
         << "),Hours(" << m_pInterval->getHours ()
         << "),Minutes(" << m_pInterval->getMinutes ()
         << "),Seconds(" << m_pInterval->getSeconds ()
         << "),Microseconds(" << m_pInterval->getMicroseconds ()
         << "))";
    return strm;
}


// MI_Array_Wrapper definitions
//------------------------------------------------------------------------------
template<TypeID_t TYPE_ID>
/*static*/ void
MI_Array_Wrapper<TYPE_ID>::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_Array_Wrapper::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_Array_Wrapper<TYPE_ID>);
    s_PyTypeObject.tp_dealloc = dealloc;
    s_PyTypeObject.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    s_PyTypeObject.tp_doc = DOC;
    s_PyTypeObject.tp_init = init;
    s_PyTypeObject.tp_new = PyType_GenericNew;
    s_PyTypeObject.tp_alloc = PyType_GenericAlloc;
    s_PyTypeObject.tp_methods = METHODS;
    s_PyTypeObject.tp_str = to_str;
    s_PyTypeObject.tp_iter = getIter;
    if (0 == PyType_Ready (&s_PyTypeObject))
    {
        Py_INCREF (&s_PyTypeObject);
        PyModule_AddObject (pModule, NAME,
                            reinterpret_cast<PyObject*>(&s_PyTypeObject));
        MI_Array_Iterator<TYPE_ID>::moduleInit (pModule);
    }
}


template<TypeID_t TYPE_ID>
/*static*/ void
MI_Array_Wrapper<TYPE_ID>::dealloc (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Array_Wrapper::dealloc");
    MI_Array_Wrapper<TYPE_ID>* pArray =
        reinterpret_cast<MI_Array_Wrapper<TYPE_ID>*>(pSelf);
    pArray->dtor ();
    pArray->ob_type->tp_free (pSelf);
}


template<>
/*static*/ int
MI_Array_Wrapper<MI_BOOLEANA>::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords);


template<TypeID_t TYPE_ID>
/*static*/ int
MI_Array_Wrapper<TYPE_ID>::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Array_Wrapper::init");
    int rval = PY_FAILURE;
    MI_Array_Wrapper<TYPE_ID>* pWrapper =
        reinterpret_cast<MI_Array_Wrapper<TYPE_ID>*>(pSelf);
    pWrapper->ctor ();
    PyObject* pValue = NULL;
    char* KEYWORDS[] = {
        "values",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "|O", KEYWORDS, &pValue))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        if (NULL == pValue)
        {
            //SCX_BOOKEND_PRINT ("***** NULL");
            rval = PY_SUCCESS;
        }
        else if (Py_None == pValue)
        {
            //SCX_BOOKEND_PRINT ("***** Py_None");
            rval = PY_SUCCESS;
        }
#if (__MI_WRAPPER_COPY_CTOR__)
        else if (PyObject_TypeCheck (pValue, getPyTypeObject ()))
        {
            SCX_BOOKEND_PRINT ("***** MI_Array_Wrapper<TYPE_ID>");
            MI_Array_Wrapper<TYPE_ID>* pOtherWrapper =
                reinterpret_cast<MI_Array_Wrapper<TYPE_ID>*>(pValue);
            pWrapper->m_pArray = pOtherWrapper->m_pArray;
            rval = PY_SUCCESS;
        }
#endif // __MI_WRAPPER_COPY_CTOR__
        else if (PyList_Check (pValue))
        {
            //SCX_BOOKEND_PRINT ("***** PyList");
            typename MI_Array<TYPE_ID>::Ptr pArray (new MI_Array<TYPE_ID>);
            rval = PY_SUCCESS;
            for (Py_ssize_t i = 0, count = PyList_Size (pValue);
                 PY_SUCCESS == rval && i < count;
                 ++i)
            {
                Value_t value;
                rval = fromPyObject (PyList_GET_ITEM (pValue, i), &value);
                if (PY_SUCCESS == rval)
                {
                    //SCX_BOOKEND_PRINT ("insert new value");
                    pArray->push_back (value);
                }
                else
                {
                    //SCX_BOOKEND_PRINT ("fromPyObject failed");
                }
            }
            if (PY_SUCCESS == rval)
            {
                //SCX_BOOKEND_PRINT ("list convert succeeded");
                pWrapper->m_pArray.reset (pArray.get ());
            }
        }
        else if (PyTuple_Check (pValue))
        {
            //SCX_BOOKEND_PRINT ("***** PyTuple");
            typename MI_Array<TYPE_ID>::Ptr pArray (new MI_Array<TYPE_ID>);
            rval = PY_SUCCESS;
            for (Py_ssize_t i = 0, count = PyTuple_Size (pValue);
                 PY_SUCCESS == rval && i < count;
                 ++i)
            {
                Value_t value;
                rval = fromPyObject (PyTuple_GET_ITEM (pValue, i), &value);
                if (PY_SUCCESS == rval)
                {
                    //SCX_BOOKEND_PRINT ("insert new value");
                    pArray->push_back (value);
                }
                else
                {
                    //SCX_BOOKEND_PRINT ("fromPyObject failed");
                }
            }
            if (PY_SUCCESS == rval)
            {
                //SCX_BOOKEND_PRINT ("tuple convert succeeded");
                pWrapper->m_pArray.reset (pArray.get ());
            }
        }
    }
    if (PY_FAILURE == rval)
    {
        PyErr_SetString (PyExc_ValueError, "invalid arguments");
    }
    return rval;
}


template<TypeID_t TYPE_ID>
/*static*/ typename MI_Array_Wrapper<TYPE_ID>::PyPtr
MI_Array_Wrapper<TYPE_ID>::createPyPtr (
    typename MI_Array<TYPE_ID>::Ptr const& pArray)
{
    //SCX_BOOKEND ("MI_Array_Wrapper::createPyPtr");
    PyObjPtr pPyArray (s_PyTypeObject.tp_alloc (&s_PyTypeObject, 0));
    if (pPyArray)
    {
        MI_Array_Wrapper<TYPE_ID>* pWrapper =
            reinterpret_cast<MI_Array_Wrapper<TYPE_ID>*>(pPyArray.get ());
        pWrapper->ctor ();
        pWrapper->m_pArray = pArray;
        return PyPtr (
            reinterpret_cast<MI_Array_Wrapper<TYPE_ID>*>(pPyArray.release ()),
            DO_NOT_INC_REF);
    }
    return PyPtr ();
}


template<TypeID_t TYPE_ID>
/*static*/ PyObject*
MI_Array_Wrapper<TYPE_ID>::_getType (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Wrapper::_getType");
    return PyInt_FromSize_t (TYPE_ID);
}


template<>
/*static*/ PyObject*
MI_Array_Wrapper<MI_BOOLEANA>::_getValueAt (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords);


template<TypeID_t TYPE_ID>
/*static*/ PyObject*
MI_Array_Wrapper<TYPE_ID>::_getValueAt (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Array_Wrapper::_getValueAt");
    PyObject* pRval = NULL;
    long index = 0;
    char* KEYWORDS[] = {
        "index",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "l", KEYWORDS, &index))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        MI_Array_Wrapper<TYPE_ID>* pArray =
            reinterpret_cast<MI_Array_Wrapper<TYPE_ID>*>(pSelf);
        if (0 > index)
        {
            index += static_cast<long>(pArray->m_pArray->size ());
        }
        if (static_cast<size_t>(index) < pArray->m_pArray->size ())
        {
            pRval = toPyObject ((*(pArray->m_pArray))[index]);
        }
        else
        {
            //SCX_BOOKEND_PRINT ("index out of range");
            PyErr_SetString (PyExc_IndexError, "index out of range");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (PyExc_ValueError,
                         "invalid arguments");
    }
    return pRval;
}


template<>
/*static*/ PyObject*
MI_Array_Wrapper<MI_BOOLEANA>::_setValueAt (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords);


template<TypeID_t TYPE_ID>
/*static*/ PyObject*
MI_Array_Wrapper<TYPE_ID>::_setValueAt (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Array_Wrapper::_setValueAt");
    PyObject* rval = NULL;
    long index = 0;
    PyObject* pValueObj = NULL;
    char* KEYWORDS[] = {
        "index",
        "value",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "lO", KEYWORDS, &index, &pValueObj))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        MI_Array_Wrapper<TYPE_ID>* pArray =
            reinterpret_cast<MI_Array_Wrapper<TYPE_ID>*>(pSelf);
        if (0 > index)
        {
            index += static_cast<long>(pArray->m_pArray->size ());
        }
        if (0 <= index &&
            static_cast<size_t>(index) < pArray->m_pArray->size ())
        {
            Value_t value;
            if (PY_SUCCESS == fromPyObject (pValueObj, &value))
            {
                (*(pArray->m_pArray))[index] = value;
                rval = Py_None;
            }
            else
            {
                //SCX_BOOKEND_PRINT ("fromPyObject failed");
                PyErr_SetString (PyExc_ValueError, "incompatible value type.");
            }
        }
        else
        {
            //SCX_BOOKEND_PRINT ("index out of range");
            PyErr_SetString (PyExc_IndexError, "index out of range");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (PyExc_ValueError, "invalid arguments.");
    }
    Py_XINCREF (rval);
    return rval;
}


template<>
/*static*/ PyObject*
MI_Array_Wrapper<MI_BOOLEANA>::_append (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords);


template<TypeID_t TYPE_ID>
/*static*/ PyObject*
MI_Array_Wrapper<TYPE_ID>::_append (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Array_Wrapper::_append");
    PyObject* rval = NULL;
    PyObject* pValueObj = NULL;
    char* KEYWORDS[] = {
        "value",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "O", KEYWORDS, &pValueObj))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        MI_Array_Wrapper<TYPE_ID>* pArray =
            reinterpret_cast<MI_Array_Wrapper<TYPE_ID>*>(pSelf);
        Value_t value;
        if (PY_SUCCESS == fromPyObject (pValueObj, &value))
        {
            pArray->m_pArray->push_back (value);
            rval = Py_None;
        }
        else
        {
            //SCX_BOOKEND_PRINT ("fromPyObject failed");
            PyErr_SetString (PyExc_ValueError, "incompatible value type.");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (PyExc_ValueError, "invalid arguments.");
    }
    Py_XINCREF (rval);
    return rval;
}


template<>
/*static*/ PyObject*
MI_Array_Wrapper<MI_BOOLEANA>::_insert (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords);


template<TypeID_t TYPE_ID>
/*static*/ PyObject*
MI_Array_Wrapper<TYPE_ID>::_insert (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Array_Wrapper::_insert");
    PyObject* rval = NULL;
    long index = 0;;
    PyObject* pValueObj = NULL;
    char* KEYWORDS[] = {
        "index",
        "value",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "lO", KEYWORDS, &index, &pValueObj))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        MI_Array_Wrapper<TYPE_ID>* pArray =
            reinterpret_cast<MI_Array_Wrapper<TYPE_ID>*>(pSelf);
        if (0 > index)
        {
            index += static_cast<long>(pArray->m_pArray->size ());
        }
        if (0 <= index &&
            static_cast<long>(pArray->m_pArray->size ()) >= index)
        {
            Value_t value;
            if (PY_SUCCESS == fromPyObject (pValueObj, &value))
            {
                pArray->m_pArray->insert (index, value);
                rval = Py_None;
            }
            else
            {
                //SCX_BOOKEND_PRINT ("fromPyObject failed");
                PyErr_SetString (PyExc_ValueError, "incompatible value type.");
            }
        }
        else
        {
            //SCX_BOOKEND_PRINT ("index out of range");
            PyErr_SetString (PyExc_IndexError, "index out of range");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (PyExc_ValueError, "invalid arguments");
    }
    Py_XINCREF (rval);
    return rval;
}


template<>
/*static*/ PyObject*
MI_Array_Wrapper<MI_BOOLEANA>::_pop (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords);


template<TypeID_t TYPE_ID>
/*static*/ PyObject*
MI_Array_Wrapper<TYPE_ID>::_pop (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Array_Wrapper::_pop");
    PyObject* rval = NULL;
    MI_Array_Wrapper<TYPE_ID>* pArray =
        reinterpret_cast<MI_Array_Wrapper<TYPE_ID>*>(pSelf);
    long index = static_cast<long>(pArray->m_pArray->size ()) - 1;
    char* KEYWORDS[] = {
        "index",
        NULL
    };
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "|l", KEYWORDS, &index))
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        if (0 > index)
        {
            index += static_cast<long>(pArray->m_pArray->size ());
        }
        if (0 <= index &&
            static_cast<size_t>(index) < pArray->m_pArray->size ())
        {
            rval = toPyObject ((*(pArray->m_pArray))[index]);
            pArray->m_pArray->erase (index);
        }
        else
        {
            //SCX_BOOKEND_PRINT ("index out of range");
            PyErr_SetString (PyExc_IndexError, "index out of range");
        }
    }
    else
    {
        //SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (PyExc_ValueError,
                         "invalid arguments.");
    }
    return rval;
}


template<TypeID_t TYPE_ID>
/*static*/ PyObject*
MI_Array_Wrapper<TYPE_ID>::_count (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("static MI_Array_Wrapper::_count");
    MI_Array_Wrapper<TYPE_ID> const* pArray =
        reinterpret_cast<MI_Array_Wrapper<TYPE_ID> const*>(pSelf);
    return PyLong_FromSsize_t (pArray->m_pArray->size ());
}

    
template<TypeID_t TYPE_ID>
/*static*/ PyObject*
MI_Array_Wrapper<TYPE_ID>::getIter (
    PyObject* pObj)
{
    //SCX_BOOKEND ("MI_Array_Wrapper::getIter");
    MI_Array_Wrapper<TYPE_ID>* pArrayWrapper =
        reinterpret_cast<MI_Array_Wrapper<TYPE_ID>*>(pObj);
    typename MI_Array_Iterator<TYPE_ID>::PyPtr pIterator (
        MI_Array_Iterator<TYPE_ID>::createPyPtr (pArrayWrapper->m_pArray, -1));
    return reinterpret_cast<PyObject*>(pIterator.release ());
}


template<>
/*static*/ PyObject*
MI_Array_Wrapper<MI_BOOLEANA>::to_str (
    PyObject* pSelf);


template<>
/*static*/ PyObject*
MI_Array_Wrapper<MI_UINT8A>::to_str (
    PyObject* pSelf);


template<>
/*static*/ PyObject*
MI_Array_Wrapper<MI_SINT8A>::to_str (
    PyObject* pSelf);


template<TypeID_t TYPE_ID>
/*static*/ PyObject*
MI_Array_Wrapper<TYPE_ID>::to_str (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Array_Wrapper::to_str");
    MI_Array_Wrapper<TYPE_ID>* pArray =
        reinterpret_cast<MI_Array_Wrapper<TYPE_ID>*>(pSelf);
    std::ostringstream strm;
    strm << NAME << "([";
    size_t const size = pArray->m_pArray->size ();
    if (0 < size)
    {
        strm << (*(pArray->m_pArray))[0];
        for (size_t i = 1; i < size; ++i)
        {
            strm << ',' << (*(pArray->m_pArray))[i];
        }
    }
    strm << "])";
    return PyString_FromString (strm.str ().c_str ());
}


template<TypeID_t TYPE_ID>
void
MI_Array_Wrapper<TYPE_ID>::ctor ()
{
    //SCX_BOOKEND ("MI_Array_Wrapper::ctor");
    new (&m_pArray) typename MI_Array<TYPE_ID>::Ptr (new MI_Array<TYPE_ID> ());
}


template<TypeID_t TYPE_ID>
void
MI_Array_Wrapper<TYPE_ID>::dtor ()
{
    //SCX_BOOKEND ("MI_Array_Wrapper::dtor");
    typedef typename util::internal_counted_ptr<MI_Array<TYPE_ID> > ptr;
    m_pArray.~ptr ();
}


template<TypeID_t TYPE_ID>
MI_Array<TYPE_ID>*
MI_Array_Wrapper<TYPE_ID>::getValue () const
{
    return m_pArray.get ();
}


template<TypeID_t TYPE_ID>
/*static*/ PyTypeObject*
MI_Array_Wrapper<TYPE_ID>::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


// class MI_Array_Iterator definitions
//------------------------------------------------------------------------------
template<TypeID_t TYPE_ID>
/*static*/ void
MI_Array_Iterator<TYPE_ID>::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_Array_Iterator::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_Array_Iterator<TYPE_ID>);
    s_PyTypeObject.tp_dealloc = dealloc;
    s_PyTypeObject.tp_flags = Py_TPFLAGS_DEFAULT;
    s_PyTypeObject.tp_doc = DOC;
    s_PyTypeObject.tp_alloc = PyType_GenericAlloc;
    s_PyTypeObject.tp_getset = s_Mutators;
    s_PyTypeObject.tp_str = to_str;
    s_PyTypeObject.tp_iternext = iterNext;
    if (0 == PyType_Ready (&s_PyTypeObject))
    {
        Py_INCREF (&s_PyTypeObject);
        PyModule_AddObject (pModule, NAME,
                            reinterpret_cast<PyObject*>(&s_PyTypeObject));
    }
}


template<TypeID_t TYPE_ID>
/*static*/ void
MI_Array_Iterator<TYPE_ID>::dealloc (
    PyObject* pObj)
{
    //SCX_BOOKEND ("MI_Array_Iterator::dealloc");
    MI_Array_Iterator<TYPE_ID>* pArray =
        reinterpret_cast<MI_Array_Iterator<TYPE_ID>*>(pObj);
    pArray->dtor ();
    pArray->ob_type->tp_free (pObj);
}


template<TypeID_t TYPE_ID>
/*static*/ typename MI_Array_Iterator<TYPE_ID>::PyPtr
MI_Array_Iterator<TYPE_ID>::createPyPtr (
    typename MI_Array<TYPE_ID>::Ptr const& pArray,
    size_t index)
{
    //SCX_BOOKEND ("MI_Array_Iterator::createPyPtr");
    PyObjPtr pPyIterator (s_PyTypeObject.tp_alloc (&s_PyTypeObject, 0));
    if (pPyIterator)
    {
        MI_Array_Iterator<TYPE_ID>* pIterator =
            reinterpret_cast<MI_Array_Iterator<TYPE_ID>*>(pPyIterator.get ());
        pIterator->ctor (pArray, index);
        return PyPtr (
            reinterpret_cast<MI_Array_Iterator<TYPE_ID>*>(
                pPyIterator.release ()),
            DO_NOT_INC_REF);
    }
    return PyPtr ();
}


template<>
/*static*/ PyObject*
MI_Array_Iterator<MI_BOOLEANA>::_getValue (
    MI_Array_Iterator<MI_BOOLEANA>* pSelf,
    void*);


template<TypeID_t TYPE_ID>
/*static*/ PyObject*
MI_Array_Iterator<TYPE_ID>::_getValue (
    MI_Array_Iterator<TYPE_ID>* pSelf,
    void*)
{
    //SCX_BOOKEND ("MI_Array_Iterator::_getValue");
    if (pSelf->m_pArray->size () > pSelf->m_Index)
    {
        return toPyObject ((*(pSelf->m_pArray))[pSelf->m_Index]);
    }
    PyErr_SetString (PyExc_IndexError, "index out of array bounds.");
    return NULL;
}


template<>
/*static*/ int
MI_Array_Iterator<MI_BOOLEANA>::_setValue (
    MI_Array_Iterator<MI_BOOLEANA>* pSelf,
    PyObject* pValueObj,
    void*);


template<TypeID_t TYPE_ID>
/*static*/ int
MI_Array_Iterator<TYPE_ID>::_setValue (
    MI_Array_Iterator<TYPE_ID>* pSelf,
    PyObject* pValueObj,
    void*)
{
    //SCX_BOOKEND ("MI_Array_Iterator::_setValue");
    int rval = PY_FAILURE;
    if (pSelf->m_pArray->size () > pSelf->m_Index)
    {
        Value_t value;
        rval = fromPyObject (pValueObj, &value);
        if (PY_SUCCESS == rval)
        {
            (*(pSelf->m_pArray))[pSelf->m_Index] = value;
        }
        else
        {
            PyErr_SetString (PyExc_ValueError, "invalid argument");
        }
    }
    else
    {
        PyErr_SetString (PyExc_IndexError, "index out of array bounds.");
    }
    return rval;
}


template<TypeID_t TYPE_ID>
/*static*/ PyObject*
MI_Array_Iterator<TYPE_ID>::iterNext (
    PyObject* pSelf)
{
    //SCX_BOOKEND ("MI_Array_Iterator::iterNext");
    PyObject* rval = NULL;
    MI_Array_Iterator<TYPE_ID>* pIterator =
        reinterpret_cast<MI_Array_Iterator<TYPE_ID>*>(pSelf);
    if (pIterator->m_pArray->size () > (1 + pIterator->m_Index))
    {
        ++(pIterator->m_Index);
        Py_INCREF (pSelf);
        rval = pSelf;
    }
    return rval;
}


template<>
/*static*/ PyObject*
MI_Array_Iterator<MI_BOOLEANA>::to_str (
    PyObject* pSelf);


template<>
/*static*/ PyObject*
MI_Array_Iterator<MI_UINT8A>::to_str (
    PyObject* pSelf);


template<>
/*static*/ PyObject*
MI_Array_Iterator<MI_SINT8A>::to_str (
    PyObject* pSelf);


template<TypeID_t TYPE_ID>
/*static*/ PyObject*
MI_Array_Iterator<TYPE_ID>::to_str (
    PyObject* pSelf)
{
    PyObject* rval = NULL;
    MI_Array_Iterator<TYPE_ID>* pIterator =
        reinterpret_cast<MI_Array_Iterator<TYPE_ID>*>(pSelf);
    if (pIterator->m_pArray->size () > pIterator->m_Index)
    {
        std::ostringstream strm;
        strm << NAME << '(' << (*(pIterator->m_pArray))[pIterator->m_Index]
             << ')';
        rval = PyString_FromString (strm.str ().c_str ());
    }
    else
    {
        PyErr_SetString (PyExc_IndexError, "index out of array bounds.");
    }
    return rval;
}


template<TypeID_t TYPE_ID>
void
MI_Array_Iterator<TYPE_ID>::ctor (
    typename MI_Array<TYPE_ID>::Ptr const& pArray,
    size_t index)
{
    //SCX_BOOKEND ("MI_Array_Iterator::ctor");
    new (&m_pArray) typename MI_Array<TYPE_ID>::Ptr (pArray);
    m_Index = index;
}


template<TypeID_t TYPE_ID>
void
MI_Array_Iterator<TYPE_ID>::dtor ()
{
    //SCX_BOOKEND ("MI_Array_Iterator::dtor");
    typedef typename util::internal_counted_ptr<MI_Array<TYPE_ID> > ptr;
    m_pArray.~ptr ();
}


} // namespace scx


// helper functions
//------------------------------------------------------------------------------
template<typename char_t, typename traits_t>
std::basic_ostream<char_t, traits_t>&
operator << (
    std::basic_ostream<char_t, traits_t>& strm,
    scx::MI_Timestamp_Wrapper const& timestamp)
{
    return timestamp.to_stream (strm);
}


template<typename char_t, typename traits_t>
std::basic_ostream<char_t, traits_t>&
operator << (
    std::basic_ostream<char_t, traits_t>& strm,
    scx::MI_Interval_Wrapper const& interval)
{
    return interval.to_stream (strm);
}


#endif // INCLUDED_MI_WRAPPER_HPP
