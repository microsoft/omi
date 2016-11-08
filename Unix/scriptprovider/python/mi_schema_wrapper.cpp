#include "mi_schema_wrapper.hpp"


#include "mi_context_wrapper.hpp"
#include "mi_instance_wrapper.hpp"
#include "mi_wrapper.hpp"


#include <cctype>
#include <cstdlib>


namespace
{


MI_Uint32
hashCode (
    std::string const& name)
{
    MI_Uint8 len = name.length ();
    return len | (tolower (name[0]) << 16) | (tolower (name[len - 1]) << 8);
}


//int
//PyBool_to_MI_Value (
//    PyObject* pSource,
//    scx::MI_Value<MI_BOOLEAN>::Ptr* ppValueOut)
//{
//    SCX_BOOKEND ("PyBool_to_MI_Value");
//    assert (NULL != ppValueOut);
//    int rval = PY_FAILURE;
//    if (PyBool_Check (pSource))
//    {
//        SCX_BOOKEND_PRINT ("PyBool");
//        ppValueOut->reset (
//            new scx::MI_Value<MI_BOOLEAN> (
//                Py_False == pSource ? false : true));
//        rval = PY_SUCCESS;
//    }
//    return rval;
//}


//template<scx::TypeID_t TYPE>
//int
//to_MI_Value (
//    PyObject* pSource,
//    typename scx::MI_Value<TYPE>::Ptr* ppValueOut)
//{
//    SCX_BOOKEND ("to_MI_Value");
//    assert (NULL != ppValueOut);
//    typename scx::MI_Type<TYPE>::type_t value;
//    int rval = scx::fromPyObject (pSource, &value);
//    if (PY_SUCCESS == rval)
//    {
//        ppValueOut->reset (new scx::MI_Value<TYPE> (value));
//    }
//    return rval;
//}


// int
// _PyBool_to_MI_ValueBase (
//     PyObject* pSource,
//     scx::MI_ValueBase::Ptr* ppValueOut)
// {
//     SCX_BOOKEND ("PyBool_to_MI_ValueBase<TypeID_t>");
//     int rval = PY_FAILURE;
//     if (NULL != pSource &&
//         Py_None != pSource)
//     {
//         if (PyObject_TypeCheck (
//                 pSource, scx::MI_Wrapper<MI_BOOLEAN>::getPyTypeObject ()))
//         {
//             SCX_BOOKEND_PRINT ("PyObject_TypeCheck: true");
//             ppValueOut->reset (
//                 reinterpret_cast<scx::MI_Wrapper<MI_BOOLEAN>*>(
//                     pSource)->getValue ());
//             rval = PY_SUCCESS;
//         }
//         else if (PyBool_Check (pSource))
//         {
//             SCX_BOOKEND_PRINT ("PyBool");
//             ppValueOut->reset (
//                 new scx::MI_Value<MI_BOOLEAN> (
//                     Py_False == pSource ? false : true));
//             rval = PY_SUCCESS;
//         }
//     }
//     else
//     {
//         ppValueOut->reset ();
//         rval = PY_SUCCESS;
//     }
//     return rval;
// }


// template<scx::TypeID_t TYPE>
// int
// _to_MI_ValueBase (
//     PyObject* pSource,
//     scx::MI_ValueBase::Ptr* ppValueOut)
// {
//     SCX_BOOKEND ("to_MI_ValueBase<TypeID_t>");
//     int rval = PY_FAILURE;
//     if (NULL != pSource &&
//         Py_None != pSource)
//     {
//         if (PyObject_TypeCheck (pSource, scx::MI_Wrapper<TYPE>::getPyTypeObject ()))
//         {
//             SCX_BOOKEND_PRINT ("PyObject_TypeCheck: true");
//             ppValueOut->reset (
//                 reinterpret_cast<scx::MI_Wrapper<TYPE>*>(pSource)->getValue ());
//             rval = PY_SUCCESS;
//         }
//         else
//         {
//             SCX_BOOKEND_PRINT ("PyObject_TypeCheck: false");
//             typename scx::MI_Type<TYPE>::type_t value;
//             rval = scx::fromPyObject (pSource, &value);
//             if (PY_SUCCESS == rval)
//             {
//                 ppValueOut->reset (new scx::MI_Value<TYPE> (value));
//             }
//         }
//     }
//     else
//     {
//         ppValueOut->reset ();
//         rval = PY_SUCCESS;
//     }
//     return rval;
// }


// int
// to_MI_ValueBase (
//     scx::TypeID_t type,
//     PyObject* pSource,
//     scx::MI_ValueBase::Ptr* ppValueOut)
// {
//     SCX_BOOKEND ("to_MI_ValueBase");
//     assert (NULL != ppValueOut);
//     int rval = PY_FAILURE;
//     switch (type)
//     {
//     case MI_BOOLEAN:
//         rval = _PyBool_to_MI_ValueBase (pSource, ppValueOut);
//         break;
//     case MI_UINT8:
//         rval = _to_MI_ValueBase<MI_UINT8> (pSource, ppValueOut);
//         break;
//     case MI_SINT8:
//         rval = _to_MI_ValueBase<MI_SINT8> (pSource, ppValueOut);
//         break;
//     case MI_UINT16:
//         rval = _to_MI_ValueBase<MI_UINT16> (pSource, ppValueOut);
//         break;
//     case MI_SINT16:
//         rval = _to_MI_ValueBase<MI_SINT16> (pSource, ppValueOut);
//         break;
//     case MI_UINT32:
//         rval = _to_MI_ValueBase<MI_UINT32> (pSource, ppValueOut);
//         break;
//     case MI_SINT32:
//         rval = _to_MI_ValueBase<MI_SINT32> (pSource, ppValueOut);
//         break;
//     case MI_UINT64:
//         rval = _to_MI_ValueBase<MI_UINT64> (pSource, ppValueOut);
//         break;
//     case MI_SINT64:
//         rval = _to_MI_ValueBase<MI_SINT64> (pSource, ppValueOut);
//         break;
//     case MI_REAL32:
//         rval = _to_MI_ValueBase<MI_REAL32> (pSource, ppValueOut);
//         break;
//     case MI_REAL64:
//         rval = _to_MI_ValueBase<MI_REAL64> (pSource, ppValueOut);
//         break;
//     case MI_STRING:
//         rval = _to_MI_ValueBase<MI_STRING> (pSource, ppValueOut);
//         break;
//     default:
//         SCX_BOOKEND_PRINT ("encountered an unhandled type");
//         break;
//     }
//     return rval;
// }


template<typename T>
int
convertCollection (
    PyObject* pValues,
    std::vector<typename T::ValuePtr>* pValuesOut)
{
    SCX_BOOKEND ("convertCollection");
    int rval = 0;
    if (PyList_Check (pValues))
    {
        SCX_BOOKEND_PRINT ("PyList");
        std::vector<typename T::ValuePtr> values;
        for (Py_ssize_t i = 0, count = PyList_Size (pValues);
             PY_SUCCESS == rval && i < count;
             ++i)
        {
            PyObject* pItem = PyList_GET_ITEM (pValues, i);
            if (PyObject_TypeCheck (
                    pItem, const_cast<PyTypeObject*>(T::getPyTypeObject ())))
            {
                SCX_BOOKEND_PRINT ("insert new item");
                values.push_back (reinterpret_cast<T*>(pItem)->getValuePtr ());
            }
            else
            {
                SCX_BOOKEND_PRINT ("wrong type");
                rval = -1;
            }
        }
        if (PY_SUCCESS == rval)
        {
            pValuesOut->swap (values);
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("expected list");
        rval = -1;
    }
    return rval;
}


template<typename T>
int
convertCollection2 (
    PyObject* pValues,
    std::vector<scx::py_ptr<T> >* pValuesOut)
{
    SCX_BOOKEND ("convertCollection2");
    int rval = 0;
    if (PyList_Check (pValues))
    {
        SCX_BOOKEND_PRINT ("PyList");
        std::vector<scx::py_ptr<T> > values;
        for (Py_ssize_t i = 0, count = PyList_Size (pValues);
             PY_SUCCESS == rval && i < count;
             ++i)
        {
            PyObject* pItem = PyList_GET_ITEM (pValues, i);
            if (PyObject_TypeCheck (
                    pItem, const_cast<PyTypeObject*>(T::getPyTypeObject ())))
            {
                SCX_BOOKEND_PRINT ("insert new item");
                values.push_back (scx::py_ptr<T> (reinterpret_cast<T*>(pItem)));
            }
            else
            {
                SCX_BOOKEND_PRINT ("wrong type");
                rval = -1;
            }
        }
        if (PY_SUCCESS == rval)
        {
            pValuesOut->swap (values);
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("expected list");
        rval = -1;
    }
    return rval;
}


} // namespace


namespace scx
{


class Invoke_Functor
{
public:
    /*ctor*/ Invoke_Functor (py_ptr<PyObject>const& pFn)
        : m_pFn (pFn)
    {
        SCX_BOOKEND ("Invoke_Functor::ctor");
        if (pFn)
        {
            SCX_BOOKEND_PRINT ("pFn is not NULL");
//            Py_INCREF (pFn.get ());
        }
        else
        {
            SCX_BOOKEND_PRINT ("pFn is NULL");
        }
    }

    /*ctor*/ Invoke_Functor (Invoke_Functor const& ref)
        : m_pFn (ref.m_pFn)
    {
        SCX_BOOKEND ("Invoke_Functor::ctor (copy");
    }


    /*dtor*/ ~Invoke_Functor ()
    {
        SCX_BOOKEND ("Invoke_Functor::dtor");
    }

    void operator () (
        MI_Context::Ptr const& pContext,
        MI_Value<MI_STRING>::Ptr const& pNameSpace,
        MI_Value<MI_STRING>::Ptr const& pClassName,
        MI_Value<MI_STRING>::Ptr const& pMethodName,
        MI_Instance::Ptr const& pInstanceName,
        MI_Instance::Ptr const& pParameters) const
    {
        SCX_BOOKEND ("Invoke_Functor::operator ()");
        MI_Context_Wrapper::PyPtr pyContext (
            MI_Context_Wrapper::createPyPtr (pContext));
        Py_INCREF (pyContext.get ());
        MI_Wrapper<MI_STRING>::PyPtr pyNameSpace (
            MI_Wrapper<MI_STRING>::createPyPtr (pNameSpace));
        Py_INCREF (pyNameSpace.get ());
        MI_Wrapper<MI_STRING>::PyPtr pyClassName (
            MI_Wrapper<MI_STRING>::createPyPtr (pClassName));
        Py_INCREF (pyClassName.get ());
        MI_Wrapper<MI_STRING>::PyPtr pyMethodName (
            MI_Wrapper<MI_STRING>::createPyPtr (pMethodName));
        Py_INCREF (pyMethodName.get ());

        MI_Instance_Wrapper::PyPtr pyInstanceName;
        if (pInstanceName)
        {
            pyInstanceName = MI_Instance_Wrapper::createPyPtr (pInstanceName);
            Py_INCREF (pyInstanceName.get ());
        }
        MI_Instance_Wrapper::PyPtr pyParameters;
        if (pParameters)
        {
            pyParameters = MI_Instance_Wrapper::createPyPtr (pParameters);
            Py_INCREF (pyParameters.get ());
        }
        if (pyContext && pyNameSpace && pyClassName && pyMethodName)
//            pyInstanceName && pyParameters)
        {
            PyObjPtr pArgs (PyTuple_New (6));
            if (pArgs)
            {
                PyTuple_SetItem (pArgs.get (), 0,
                                 reinterpret_cast<PyObject*>(pyContext.get ()));
                PyTuple_SetItem (
                    pArgs.get (), 1,
                    reinterpret_cast<PyObject*>(pyNameSpace.get ()));
                PyTuple_SetItem (
                    pArgs.get (), 2,
                    reinterpret_cast<PyObject*>(pyClassName.get ()));
                PyTuple_SetItem (
                    pArgs.get (), 3,
                    reinterpret_cast<PyObject*>(pyMethodName.get ()));
                if (pInstanceName)
                {
                    PyTuple_SetItem (
                        pArgs.get (), 4,
                        reinterpret_cast<PyObject*>(pyInstanceName.get ()));
                }
                else
                {
                    SCX_BOOKEND_PRINT ("Instance is NULL");
                    Py_INCREF (Py_None);
                    PyTuple_SetItem (pArgs.get (), 4, Py_None);
                }
                if (pParameters)
                {
                    PyTuple_SetItem (
                        pArgs.get (), 5,
                        reinterpret_cast<PyObject*>(pyParameters.get ()));
                }
                else
                {
                    SCX_BOOKEND_PRINT ("Parameters is NULL");
                    Py_INCREF (Py_None);
                    PyTuple_SetItem (pArgs.get (), 5, Py_None);
                }
                {
                    SCX_BOOKEND ("call python function");
                    if (m_pFn)
                    {
                        SCX_BOOKEND_PRINT ("m_pFn is not NULL");
                    }
                    else
                    {
                        SCX_BOOKEND_PRINT ("m_pFn is NULL");
                    }
                    PyObjPtr pRval (PyObject_CallObject (
                                        m_pFn.get (), pArgs.get ()));
                    if (!pRval)
                    {
                        SCX_BOOKEND_PRINT ("Error returned from call");
                    }
                    else
                    {
                        if (Py_None == pRval.get ())
                        {
                            SCX_BOOKEND_PRINT (
                                "an object was returned (Py_None)");
                        }
                        else
                        {
                            SCX_BOOKEND_PRINT (
                                "an object was returned (not Py_None)");
                        }
                    }
                }
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("Something wasn't allocated");
        }
    }

private:
    py_ptr<PyObject> const m_pFn;
};


typedef util::function_holder<Invoke_Functor,
                              void,
                              MI_Context::Ptr const&,
                              MI_Value<MI_STRING>::Ptr const&,
                              MI_Value<MI_STRING>::Ptr const&,
                              MI_Value<MI_STRING>::Ptr const&,
                              MI_Instance::Ptr const&,
                              MI_Instance::Ptr const&> InvokeFNHolder_t;

} // namespace scx


using namespace scx;
//namespace scx
//{


/*static*/ char const MI_QualifierDecl_Wrapper::NAME[] = "MI_QualifierDecl";
/*static*/ char const MI_QualifierDecl_Wrapper::OMI_NAME[] =
    "omi.MI_QualifierDecl";
/*static*/ char const MI_QualifierDecl_Wrapper::DOC[] =
    "omi.MI_QualifierDecl utility";
/*static*/ PyTypeObject MI_QualifierDecl_Wrapper::s_PyTypeObject = {};


/*static*/ void
MI_QualifierDecl_Wrapper::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_QualifierDecl_Wrapper::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_QualifierDecl_Wrapper);
    s_PyTypeObject.tp_dealloc = dealloc;
    s_PyTypeObject.tp_flags = Py_TPFLAGS_DEFAULT;
    s_PyTypeObject.tp_doc = DOC;
    s_PyTypeObject.tp_init = init;
    s_PyTypeObject.tp_new = newObj;
    s_PyTypeObject.tp_alloc = PyType_GenericAlloc;
    if (0 == PyType_Ready (&s_PyTypeObject))
    {
        Py_INCREF (&s_PyTypeObject);
        PyModule_AddObject (
            pModule, NAME, reinterpret_cast<PyObject*>(&s_PyTypeObject));
    }
}


/*static*/ void
MI_QualifierDecl_Wrapper::dealloc (
    PyObject* pObj)
{
    //SCX_BOOKEND ("MI_QualifierDecl_Wrapper::dealloc");
    if (NULL != pObj)
    {
        MI_QualifierDecl_Wrapper* pDecl =
            reinterpret_cast<MI_QualifierDecl_Wrapper*>(pObj);
        pDecl->~MI_QualifierDecl_Wrapper ();
        pDecl->ob_type->tp_free (pObj);
    }
}


/*static*/ PyTypeObject const*
MI_QualifierDecl_Wrapper::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


PyObject*
MI_QualifierDecl_Wrapper::newObj (
    PyTypeObject* pType,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_QualifierDecl_Wrapper::newObj");
    PyObject* pObj = pType->tp_alloc (pType, 0);
    return pObj;
}


int
MI_QualifierDecl_Wrapper::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_QualifierDecl_Wrapper::init");
    char* KEYWORDS[] = {
        "name",
        "type",
        "scope",
        "flavor",
        "value",
        NULL
    };
    int rval = 0;
    PyObject* pNameObj = NULL;
    PyObject* pTypeObj = NULL;
    PyObject* pScopeObj = NULL;
    PyObject* pFlavorObj = NULL;
    PyObject* pValueObj = NULL;
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "OOOO|O", KEYWORDS,
            &pNameObj, &pTypeObj, &pScopeObj, &pFlavorObj, &pValueObj))
    {
        MI_Value<MI_STRING>::Ptr pName;
        rval = to_MI_Value<MI_STRING> (pNameObj, &pName);
        if (PY_SUCCESS != rval)
        {
            SCX_BOOKEND_PRINT ("Name convert failed");
        }
        MI_Value<MI_UINT32>::Ptr pType;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value<MI_UINT32> (pTypeObj, &pType);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("Type convert failed");
            }
        }
        MI_Value<MI_UINT32>::Ptr pScope;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value<MI_UINT32> (pScopeObj, &pScope);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("Scope convert failed");
            }
        }
        MI_Value<MI_UINT32>::Ptr pFlavor;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value<MI_UINT32> (pFlavorObj, &pFlavor);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("Flavor convert failed");
            }
        }
        MI_ValueBase::Ptr pValue;
        if (PY_SUCCESS == rval &&
            NULL != pValueObj)
        {
            rval = to_MI_ValueBase (pType->getValue (), pValueObj, &pValue);
        }
        if (PY_SUCCESS == rval &&
            pName &&
            pType &&
            pScope &&
            pFlavor)
        {
            //SCX_BOOKEND_PRINT ("MI_QualifierDecl_Wrapper::init succeeded");
            new (pSelf) MI_QualifierDecl_Wrapper (
                pName, pType, pScope, pFlavor, pValue);
        }
        else
        {
            SCX_BOOKEND_PRINT ("MI_QualifierDecl_Wrapper::init failed");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("MI_QualifierDecl_Wrapper::init parse args failed");
    }
    return rval;
}

    
/*dtor*/
MI_QualifierDecl_Wrapper::~MI_QualifierDecl_Wrapper ()
{
    //SCX_BOOKEND ("MI_QualifierDecl_Wrapper::dtor");
}


/*ctor*/
MI_QualifierDecl_Wrapper::MI_QualifierDecl_Wrapper (
    MI_Value<MI_STRING>::ConstPtr const& pName,
    MI_Value<MI_UINT32>::ConstPtr const& pType,
    MI_Value<MI_UINT32>::ConstPtr const& pScope,
    MI_Value<MI_UINT32>::ConstPtr const& pFlavor,
    MI_ValueBase::ConstPtr const& pValue)
    : m_pValue (new MI_QualifierDecl (pName, pType, pScope, pFlavor, pValue))
{
    //SCX_BOOKEND ("MI_QualifierDecl_Wrapper::ctor");
}


/*static*/ char const MI_Qualifier_Wrapper::NAME[] = "MI_Qualifier";
/*static*/ char const MI_Qualifier_Wrapper::OMI_NAME[] = "omi.MI_Qualifier";
/*static*/ char const MI_Qualifier_Wrapper::DOC[] =
    "omi.MI_Qualifier utility";
/*static*/ PyTypeObject MI_Qualifier_Wrapper::s_PyTypeObject = {};


/*static*/ void
MI_Qualifier_Wrapper::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_Qualifier_Wrapper::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_Qualifier_Wrapper);
    s_PyTypeObject.tp_dealloc = dealloc;
    s_PyTypeObject.tp_flags = Py_TPFLAGS_DEFAULT;
    s_PyTypeObject.tp_doc = DOC;
    s_PyTypeObject.tp_init = init;
    s_PyTypeObject.tp_new = newObj;
    s_PyTypeObject.tp_alloc = PyType_GenericAlloc;
    if (0 == PyType_Ready (&s_PyTypeObject))
    {
        Py_INCREF (&s_PyTypeObject);
        PyModule_AddObject (
            pModule, NAME, reinterpret_cast<PyObject*>(&s_PyTypeObject));
    }
}


/*static*/ void
MI_Qualifier_Wrapper::dealloc (
    PyObject* pObj)
{
    //SCX_BOOKEND ("MI_Qualifier_Wrapper::dealloc");
    if (NULL != pObj)
    {
        MI_Qualifier_Wrapper* pDecl =
            reinterpret_cast<MI_Qualifier_Wrapper*>(pObj);
        pDecl->~MI_Qualifier_Wrapper ();
        pDecl->ob_type->tp_free (pObj);
    }
}


/*static*/ PyTypeObject const*
MI_Qualifier_Wrapper::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


PyObject*
MI_Qualifier_Wrapper::newObj (
    PyTypeObject* pType,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Qualifier_Wrapper::newObj");
    PyObject* pObj = pType->tp_alloc (pType, 0);
    return pObj;
}


int
MI_Qualifier_Wrapper::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_Qualifier_Wrapper::init");
    char* KEYWORDS[] = {
        "name",
        "type",
        "flavor",
        "value",
        NULL
    };
    int rval = 0;
    PyObject* pNameObj = NULL;
    PyObject* pTypeObj = NULL;
    PyObject* pFlavorObj = NULL;
    PyObject* pValueObj = NULL;
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "OOOO|O", KEYWORDS,
            &pNameObj, &pTypeObj, &pFlavorObj, &pValueObj))
    {
        MI_Value<MI_STRING>::Ptr pName;
        rval = to_MI_Value<MI_STRING> (pNameObj, &pName);
        if (PY_FAILURE == rval)
        {
            SCX_BOOKEND_PRINT ("Name convert failed");
        }
        MI_Value<MI_UINT32>::Ptr pType;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value<MI_UINT32> (pTypeObj, &pType);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("Type convert failed");
            }
        }
        MI_Value<MI_UINT32>::Ptr pFlavor;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value<MI_UINT32> (pFlavorObj, &pFlavor);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("Flavor convert failed");
            }
        }
        MI_ValueBase::Ptr pValue;
        if (PY_SUCCESS == rval &&
            NULL != pValueObj)
        {
            rval = to_MI_ValueBase (pType->getValue (), pValueObj, &pValue);
        }
        if (PY_SUCCESS == rval &&
            pName &&
            pType &&
            pFlavor)
        {
            //SCX_BOOKEND_PRINT ("MI_Qualifier_Wrapper::init succeeded");
            new (pSelf) MI_Qualifier_Wrapper (pName, pType, pFlavor, pValue);
        }
        else
        {
            SCX_BOOKEND_PRINT ("MI_Qualifier_Wrapper::init failed");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("MI_Qualifier_Wrapper::init parse args failed");
    }
    return rval;
}

    
/*dtor*/
MI_Qualifier_Wrapper::~MI_Qualifier_Wrapper ()
{
    //SCX_BOOKEND ("MI_Qualifier_Wrapper::dtor");
}


/*ctor*/
MI_Qualifier_Wrapper::MI_Qualifier_Wrapper (
    MI_Value<MI_STRING>::ConstPtr const& pName,
    MI_Value<MI_UINT32>::ConstPtr const& pType,
    MI_Value<MI_UINT32>::ConstPtr const& pFlavor,
    MI_ValueBase::ConstPtr const& pValue)
    : m_pValue (new MI_Qualifier (pName, pType, pFlavor, pValue))
{
    //SCX_BOOKEND ("MI_Qualifier_Wrapper::ctor");
}


/*static*/ char const MI_PropertyDecl_Wrapper::NAME[] = "MI_PropertyDecl";
/*static*/ char const MI_PropertyDecl_Wrapper::OMI_NAME[] =
    "omi.MI_PropertyDecl";
/*static*/ char const MI_PropertyDecl_Wrapper::DOC[] =
    "omi.MI_PropertyDecl utility";
/*static*/ PyTypeObject MI_PropertyDecl_Wrapper::s_PyTypeObject = {};


/*static*/ void
MI_PropertyDecl_Wrapper::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_PropertyDecl_Wrapper::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_PropertyDecl_Wrapper);
    s_PyTypeObject.tp_dealloc = dealloc;
    s_PyTypeObject.tp_flags = Py_TPFLAGS_DEFAULT;
    s_PyTypeObject.tp_doc = DOC;
    s_PyTypeObject.tp_init = init;
    s_PyTypeObject.tp_new = newObj;
    s_PyTypeObject.tp_alloc = PyType_GenericAlloc;
    if (0 == PyType_Ready (&s_PyTypeObject))
    {
        Py_INCREF (&s_PyTypeObject);
        PyModule_AddObject (
            pModule, NAME, reinterpret_cast<PyObject*>(&s_PyTypeObject));
    }
}


/*static*/ void
MI_PropertyDecl_Wrapper::dealloc (
    PyObject* pObj)
{
    SCX_BOOKEND ("MI_PropertyDecl_Wrapper::dealloc");
    if (NULL != pObj)
    {
        MI_PropertyDecl_Wrapper* pDecl =
            reinterpret_cast<MI_PropertyDecl_Wrapper*>(pObj);
        pDecl->~MI_PropertyDecl_Wrapper ();
        pDecl->ob_type->tp_free (pObj);
    }
}


/*static*/ PyTypeObject const*
MI_PropertyDecl_Wrapper::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


PyObject*
MI_PropertyDecl_Wrapper::newObj (
    PyTypeObject* pType,
    PyObject* args,
    PyObject* keywords)
{
    SCX_BOOKEND ("MI_PropertyDecl_Wrapper::newObj");
    PyObject* pObj = pType->tp_alloc (pType, 0);
    return pObj;
}


int
MI_PropertyDecl_Wrapper::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    SCX_BOOKEND ("MI_PropertyDecl_Wrapper::init");
    char* KEYWORDS[] = {
        "flags",
//        "code",
        "name",
        "qualifiers",
        "type",
        "className",
        "origin",
        "propagator",
        "value",
        NULL
    };
    int rval = 0;
    PyObject* pFlagsObj = NULL;
//    PyObject* pCodeObj = NULL;
    PyObject* pNameObj = NULL;
    PyObject* pQualifiersObj = NULL;
    PyObject* pTypeObj = NULL;
    PyObject* pClassNameObj = NULL;
    PyObject* pOriginObj = NULL;
    PyObject* pPropagatorObj = NULL;
    PyObject* pValueObj = NULL;
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "OOOOO|OOO", KEYWORDS,
//            args, keywords, "OOOOOO|OOO", KEYWORDS,
            &pFlagsObj, &pNameObj, &pQualifiersObj, &pTypeObj, &pClassNameObj,
            &pOriginObj, &pPropagatorObj, &pValueObj))
//            &pFlagsObj, &pCodeObj, &pNameObj, &pQualifiersObj, &pTypeObj,
//            &pClassNameObj, &pOriginObj, &pPropagatorObj, &pValueObj))
    {
        MI_Value<MI_UINT32>::Ptr pFlags;
        rval = to_MI_Value<MI_UINT32> (pFlagsObj, &pFlags);
        if (PY_FAILURE == rval)
        {
            SCX_BOOKEND_PRINT ("Flags convert failed");
        }
//        MI_Value<MI_UINT32>::Ptr pCode;
//        if (PY_SUCCESS == rval)
//        {
//            rval = to_MI_Value<MI_UINT32> (pCodeObj, &pCode);
//            if (PY_FAILURE == rval)
//            {
//                SCX_BOOKEND_PRINT ("Code convert failed");
//            }
//        }
        MI_Value<MI_STRING>::Ptr pName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value<MI_STRING> (pNameObj, &pName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("Name convert failed");
            }
        }
        std::vector<MI_Qualifier_Wrapper::ValuePtr> qualifiers;
        if (PY_SUCCESS == rval)
        {
            rval = convertCollection<MI_Qualifier_Wrapper> (
                pQualifiersObj, &qualifiers);
        }
        MI_Value<MI_UINT32>::Ptr pType;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value<MI_UINT32> (pTypeObj, &pType);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("Type convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pClassName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (pClassNameObj, &pClassName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("ClassName convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pOrigin;
        if (PY_SUCCESS == rval && pOriginObj)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (pOriginObj, &pOrigin);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pOrigin convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pPropagator;
        if (PY_SUCCESS == rval && pPropagatorObj)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (pPropagatorObj, &pPropagator);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("Propagator convert failed");
            }
        }
        MI_ValueBase::Ptr pValue;
        if (PY_SUCCESS == rval &&
            NULL != pValueObj)
        {
            rval = to_MI_ValueBase (pType->getValue (), pValueObj, &pValue);
        }
        if (PY_SUCCESS == rval &&
            pFlags &&
//            pCode &&
            pName &&
            pType)
        {
            SCX_BOOKEND_PRINT ("MI_PropertyDecl_Wrapper::init succeeded");
            
            MI_Value<MI_UINT32>::Ptr pCode (new MI_Value<MI_UINT32> (
                hashCode (static_cast<MI_Value<MI_STRING> const*>(
                              pName.get ())->getValue ())));

//            MI_Uint32 code = hashCode (
//                static_cast<MI_Value<MI_STRING> const*>(
//                    pName.get ())->getValue ());


            new (pSelf) MI_PropertyDecl_Wrapper (
                pFlags, pCode, pName, qualifiers, pType, pClassName, pOrigin,
                pPropagator, pValue);
        }
        else
        {
            SCX_BOOKEND_PRINT ("MI_PropertyDecl_Wrapper::init failed");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("MI_PropertyDecl_Wrapper::init parse args failed");
    }
    return rval;
}

    
/*dtor*/
MI_PropertyDecl_Wrapper::~MI_PropertyDecl_Wrapper ()
{
    SCX_BOOKEND ("MI_PropertyDecl_Wrapper::dtor");
}


/*ctor*/
MI_PropertyDecl_Wrapper::MI_PropertyDecl_Wrapper (
    MI_Value<MI_UINT32>::ConstPtr const& pFlags,
    MI_Value<MI_UINT32>::ConstPtr const& pCode,
    MI_Value<MI_STRING>::ConstPtr const& pName,
    std::vector<MI_Qualifier::ConstPtr> const& qualifiers,
    MI_Value<MI_UINT32>::ConstPtr const& pType,
    MI_Value<MI_STRING>::ConstPtr const& pClassName,
    MI_Value<MI_STRING>::ConstPtr const& pOrigin,
    MI_Value<MI_STRING>::ConstPtr const& pPropagator,
    MI_ValueBase::ConstPtr const& pValue)
    : m_pValue (new MI_PropertyDecl (pFlags, pCode, pName, &(qualifiers[0]),
                                     qualifiers.size (), pType, pClassName,
                                     pOrigin, pPropagator, pValue))
{
    SCX_BOOKEND ("MI_PropertyDecl_Wrapper::ctor");
}


/*static*/ char const MI_ParameterDecl_Wrapper::NAME[] = "MI_ParameterDecl";
/*static*/ char const MI_ParameterDecl_Wrapper::OMI_NAME[] =
    "omi.MI_ParameterDecl";
/*static*/ char const MI_ParameterDecl_Wrapper::DOC[] =
    "omi.MI_ParameterDecl utility";
/*static*/ PyTypeObject MI_ParameterDecl_Wrapper::s_PyTypeObject = {};


/*static*/ void
MI_ParameterDecl_Wrapper::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_ParameterDecl_Wrapper::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_ParameterDecl_Wrapper);
    s_PyTypeObject.tp_dealloc = dealloc;
    s_PyTypeObject.tp_flags = Py_TPFLAGS_DEFAULT;
    s_PyTypeObject.tp_doc = DOC;
    s_PyTypeObject.tp_init = init;
    s_PyTypeObject.tp_new = newObj;
    s_PyTypeObject.tp_alloc = PyType_GenericAlloc;
    if (0 == PyType_Ready (&s_PyTypeObject))
    {
        Py_INCREF (&s_PyTypeObject);
        PyModule_AddObject (
            pModule, NAME, reinterpret_cast<PyObject*>(&s_PyTypeObject));
    }
}


/*static*/ void
MI_ParameterDecl_Wrapper::dealloc (
    PyObject* pObj)
{
    SCX_BOOKEND ("MI_ParameterDecl_Wrapper::dealloc");
    if (NULL != pObj)
    {
        MI_ParameterDecl_Wrapper* pDecl =
            reinterpret_cast<MI_ParameterDecl_Wrapper*>(pObj);
        pDecl->~MI_ParameterDecl_Wrapper ();
        pDecl->ob_type->tp_free (pObj);
    }
}


/*static*/ PyTypeObject const*
MI_ParameterDecl_Wrapper::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


PyObject*
MI_ParameterDecl_Wrapper::newObj (
    PyTypeObject* pType,
    PyObject* args,
    PyObject* keywords)
{
    SCX_BOOKEND ("MI_ParameterDecl_Wrapper::newObj");
    PyObject* pObj = pType->tp_alloc (pType, 0);
    return pObj;
}


int
MI_ParameterDecl_Wrapper::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    SCX_BOOKEND ("MI_ParameterDecl_Wrapper::init");
    char* KEYWORDS[] = {
        "flags",
//        "code",
        "name",
        "qualifiers",
        "type",
        "className",
        NULL
    };
    int rval = 0;
    PyObject* pFlagsObj = NULL;
//    PyObject* pCodeObj = NULL;
    PyObject* pNameObj = NULL;
    PyObject* pQualifiersObj = NULL;
    PyObject* pTypeObj = NULL;
    PyObject* pClassNameObj = NULL;
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "OOOOO", KEYWORDS, 
//            args, keywords, "OOOOOO", KEYWORDS, 
            &pFlagsObj, &pNameObj, &pQualifiersObj, &pTypeObj, &pClassNameObj))
//            &pFlagsObj, &pCodeObj, &pNameObj, &pQualifiersObj, &pTypeObj,
//            &pClassNameObj))
    {
        MI_Value<MI_UINT32>::Ptr pFlags;
        rval = to_MI_Value<MI_UINT32> (pFlagsObj, &pFlags);
        if (PY_FAILURE == rval)
        {
            SCX_BOOKEND_PRINT ("Flags convert failed");
        }
//        MI_Value<MI_UINT32>::Ptr pCode;
//        if (PY_SUCCESS == rval)
//        {
//            rval = to_MI_Value<MI_UINT32> (pCodeObj, &pCode);
//            if (PY_FAILURE == rval)
//            {
//                SCX_BOOKEND_PRINT ("Code convert failed");
//            }
//        }
        MI_Value<MI_STRING>::Ptr pName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value<MI_STRING> (pNameObj, &pName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("Name convert failed");
            }
        }
        std::vector<MI_Qualifier_Wrapper::ValuePtr> qualifiers;
        if (PY_SUCCESS == rval)
        {
            rval = convertCollection<MI_Qualifier_Wrapper> (
                pQualifiersObj, &qualifiers);
        }
        MI_Value<MI_UINT32>::Ptr pType;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value<MI_UINT32> (pTypeObj, &pType);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("Type convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pClassName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (pClassNameObj, &pClassName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("ClassName convert failed");
            }
        }
        if (PY_SUCCESS == rval &&
            pFlags &&
//            pCode &&
            pName &&
            pType)
        {
            SCX_BOOKEND_PRINT ("MI_ParameterDecl_Wrapper::init succeeded");

            MI_Value<MI_UINT32>::Ptr pCode (new MI_Value<MI_UINT32> (
                hashCode (static_cast<MI_Value<MI_STRING> const*>(
                              pName.get ())->getValue ())));

            new (pSelf) MI_ParameterDecl_Wrapper (
                pFlags, pCode, pName, qualifiers, pType, pClassName);
        }
        else
        {
            SCX_BOOKEND_PRINT ("MI_ParameterDecl_Wrapper::init failed");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("MI_ParameterDecl_Wrapper::init parse args failed");
    }
    return rval;
}


/*ctor*/
MI_ParameterDecl_Wrapper::MI_ParameterDecl_Wrapper (
    MI_Value<MI_UINT32>::ConstPtr const& flags,
    MI_Value<MI_UINT32>::ConstPtr const& code,
    MI_Value<MI_STRING>::ConstPtr const& name,
    std::vector<MI_Qualifier::ConstPtr> const& qualifiers,
    MI_Value<MI_UINT32>::ConstPtr const& type,
    MI_Value<MI_STRING>::ConstPtr const& className)
    : m_pValue (new MI_ParameterDecl (flags, code, name, &(qualifiers[0]),
                                      qualifiers.size (), type, className))
{
    SCX_BOOKEND ("MI_ParameterDecl_Wrapper::ctor");
}

    
/*dtor*/
MI_ParameterDecl_Wrapper::~MI_ParameterDecl_Wrapper ()
{
    SCX_BOOKEND ("MI_ParameterDecl_Wrapper::dtor");
}


/*static*/ char const MI_MethodDecl_Placeholder::NAME[] = "MI_MethodDecl";
/*static*/ char const MI_MethodDecl_Placeholder::OMI_NAME[] =
    "omi.MI_MethodDecl";
/*static*/ char const MI_MethodDecl_Placeholder::DOC[] =
    "omi.MI_MethodDecl utility";
/*static*/ PyTypeObject MI_MethodDecl_Placeholder::s_PyTypeObject = {};


/*static*/ void
MI_MethodDecl_Placeholder::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_MethodDecl_Placeholder::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_MethodDecl_Placeholder);
    s_PyTypeObject.tp_dealloc = dealloc;
    s_PyTypeObject.tp_flags = Py_TPFLAGS_DEFAULT;
    s_PyTypeObject.tp_doc = DOC;
    s_PyTypeObject.tp_init = init;
    s_PyTypeObject.tp_new = newObj;
    s_PyTypeObject.tp_alloc = PyType_GenericAlloc;
    if (0 == PyType_Ready (&s_PyTypeObject))
    {
        Py_INCREF (&s_PyTypeObject);
        PyModule_AddObject (
            pModule, NAME, reinterpret_cast<PyObject*>(&s_PyTypeObject));
    }
}


/*static*/ void
MI_MethodDecl_Placeholder::dealloc (
    PyObject* pObj)
{
    SCX_BOOKEND ("MI_MethodDecl_Placeholder::dealloc");
    if (NULL != pObj)
    {
        MI_MethodDecl_Placeholder* pDecl =
            reinterpret_cast<MI_MethodDecl_Placeholder*>(pObj);
        pDecl->~MI_MethodDecl_Placeholder ();
        pDecl->ob_type->tp_free (pObj);
    }
}


/*static*/ PyTypeObject const*
MI_MethodDecl_Placeholder::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


PyObject*
MI_MethodDecl_Placeholder::newObj (
    PyTypeObject* pType,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_MethodDecl_Placeholder::newObj");
    PyObject* pObj = pType->tp_alloc (pType, 0);
    return pObj;
}


int
MI_MethodDecl_Placeholder::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    SCX_BOOKEND ("MI_MethodDecl_Placeholder::init");
    char* KEYWORDS[] = {
        "flags",
//        "code",
        "name",
        "qualifiers",
        "parameters",
        "returnType",
        "origin",
        "propagator",
        "invokeFn",
        NULL
    };
    int rval = 0;
    PyObject* pFlagsObj = NULL;
//    PyObject* pCodeObj = NULL;
    PyObject* pNameObj = NULL;
    PyObject* pQualifiersObj = NULL;
    PyObject* pParametersObj = NULL;
    PyObject* pReturnTypeObj = NULL;
    PyObject* pOriginObj = NULL;
    PyObject* pPropagatorObj = NULL;
    PyObject* pInvokeFnNameObj = NULL;
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "OOOOOOOO", KEYWORDS,
            &pFlagsObj, &pNameObj, &pQualifiersObj, &pParametersObj,
            &pReturnTypeObj, &pOriginObj, &pPropagatorObj, &pInvokeFnNameObj))
//            args, keywords, "OOOOOOOOO", KEYWORDS,
//            &pFlagsObj, &pCodeObj, &pNameObj, &pQualifiersObj, &pParametersObj,
//            &pReturnTypeObj, &pOriginObj, &pPropagatorObj, &pInvokeFnNameObj))
    {
        MI_Value<MI_UINT32>::Ptr pFlags;
        rval = to_MI_Value<MI_UINT32> (pFlagsObj, &pFlags);
        if (PY_FAILURE == rval)
        {
            SCX_BOOKEND_PRINT ("pFlags convert failed");
        }
//        MI_Value<MI_UINT32>::Ptr pCode;
//        if (PY_SUCCESS == rval)
//        {
//            rval = to_MI_Value<MI_UINT32> (pCodeObj, &pCode);
//            if (PY_FAILURE == rval)
//            {
//                SCX_BOOKEND_PRINT ("pCode convert failed");
//            }
//        }
        MI_Value<MI_STRING>::Ptr pName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value<MI_STRING> (pNameObj, &pName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pName convert failed");
            }
        }
        std::vector<MI_Qualifier_Wrapper::ValuePtr> qualifiers;
        if (PY_SUCCESS == rval)
        {
            rval = convertCollection<MI_Qualifier_Wrapper> (
                pQualifiersObj, &qualifiers);
        }
        std::vector<MI_ParameterDecl_Wrapper::ValuePtr> parameters;
        if (PY_SUCCESS == rval)
        {
            rval = convertCollection<MI_ParameterDecl_Wrapper> (
                pParametersObj, &parameters);
        }
        MI_Value<MI_UINT32>::Ptr pReturnType;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value<MI_UINT32> (pReturnTypeObj, &pReturnType);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pReturnType convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pOrigin;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (pOriginObj, &pOrigin);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pOrigin convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pPropagator;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (pPropagatorObj, &pPropagator);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pPropagator convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pInvokeFnName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value<MI_STRING> (pInvokeFnNameObj, &pInvokeFnName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("InvokeFnName convert failed");
            }
        }

        if (PY_SUCCESS == rval &&
            pFlags &&
//            pCode &&
            pName &&
            pReturnType &&
            pInvokeFnName)
        {
            SCX_BOOKEND_PRINT ("MI_MethodDecl_Placeholder::init succeeded");

            MI_Value<MI_UINT32>::Ptr pCode (new MI_Value<MI_UINT32> (
                hashCode (static_cast<MI_Value<MI_STRING> const*>(
                              pName.get ())->getValue ())));

            new (pSelf) MI_MethodDecl_Placeholder (
                pFlags, pCode, pName, qualifiers, parameters, pReturnType,
                pOrigin, pPropagator, pInvokeFnName);
        }
        else
        {
            SCX_BOOKEND_PRINT ("MI_MethodDecl_Placeholder::init failed");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("MI_MethodDecl_Placeholder::init parse args failed");
    }
    return rval;
}

    
/*dtor*/
MI_MethodDecl_Placeholder::~MI_MethodDecl_Placeholder ()
{
    SCX_BOOKEND ("MI_MethodDecl_Placeholder::dtor");
}


/*ctor*/
MI_MethodDecl_Placeholder::MI_MethodDecl_Placeholder (
    MI_Value<MI_UINT32>::ConstPtr const& pFlags,
    MI_Value<MI_UINT32>::ConstPtr const& pCode,
    MI_Value<MI_STRING>::ConstPtr const& pName,
    std::vector<MI_Qualifier::ConstPtr> const& qualifiers,
    std::vector<MI_ParameterDecl::ConstPtr> const& parameters,
    MI_Value<MI_UINT32>::ConstPtr const& pReturnType,
    MI_Value<MI_STRING>::ConstPtr const& pOrigin,
    MI_Value<MI_STRING>::ConstPtr const& pPropagator,
    MI_Value<MI_STRING>::ConstPtr const& pInvokeFnName)
    : m_pFlags (pFlags)
    , m_pCode (pCode)
    , m_pName (pName)
    , m_Qualifiers (qualifiers)
    , m_Parameters (parameters)
    , m_pReturnType (pReturnType)
    , m_pOrigin (pOrigin)
    , m_pPropagator (pPropagator)
    , m_pInvokeFnName (pInvokeFnName)
{
    SCX_BOOKEND ("MI_MethodDecl_Placeholder::ctor");
}


int
MI_MethodDecl_Placeholder::createMethodDecl (
    PyObject* const pPyModule,
    scx::MI_MethodDecl::Ptr* const ppMethodDeclOut) const
{
    SCX_BOOKEND ("MI_MethodDecl_Placeholder::createMethodDecl");
    assert (0 != pPyModule);
    assert (0 != ppMethodDeclOut);
    int rval = EXIT_FAILURE;
    MI_MethodDecl::Ptr pMethodDecl;
    MI_MethodDecl::InvokeFn::ConstPtr pInvokeFn;
    PyObject* pModuleDict = PyModule_GetDict (pPyModule);
    if (pModuleDict)
    {
        PyObject* pInvokeFnObj = PyDict_GetItemString (
            pModuleDict, m_pInvokeFnName->getValue ().c_str ());
        if (PyCallable_Check (pInvokeFnObj))
        {
            pInvokeFn = new InvokeFNHolder_t (Invoke_Functor (
                    py_ptr<PyObject> (pInvokeFnObj)));
        }
    }
    if (m_pFlags && m_pCode && m_pName && m_pReturnType && pInvokeFn)
    {
        rval = EXIT_SUCCESS;
        *ppMethodDeclOut = new MI_MethodDecl (
            m_pFlags, m_pCode, m_pName, &(m_Qualifiers[0]),
            m_Qualifiers.size (), &(m_Parameters[0]), m_Parameters.size (),
            m_pReturnType, m_pOrigin, m_pPropagator, pInvokeFn);
    }
    return rval;
}





/*static*/ char const MI_ClassDecl_Placeholder::NAME[] = "MI_ClassDecl";
/*static*/ char const MI_ClassDecl_Placeholder::OMI_NAME[] =
    "omi.MI_ClassDecl";
/*static*/ char const MI_ClassDecl_Placeholder::DOC[] =
    "omi.MI_ClassDecl utility";
/*static*/ PyTypeObject MI_ClassDecl_Placeholder::s_PyTypeObject = {};


/*static*/ void
MI_ClassDecl_Placeholder::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_ClassDecl_Wrapper::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_ClassDecl_Placeholder);
    s_PyTypeObject.tp_dealloc = dealloc;
    s_PyTypeObject.tp_flags = Py_TPFLAGS_DEFAULT;
    s_PyTypeObject.tp_doc = DOC;
    s_PyTypeObject.tp_init = init;
    s_PyTypeObject.tp_new = newObj;
    s_PyTypeObject.tp_alloc = PyType_GenericAlloc;
    if (0 == PyType_Ready (&s_PyTypeObject))
    {
        Py_INCREF (&s_PyTypeObject);
        PyModule_AddObject (
            pModule, NAME, reinterpret_cast<PyObject*>(&s_PyTypeObject));
    }
}


/*static*/ void
MI_ClassDecl_Placeholder::dealloc (
    PyObject* pObj)
{
    SCX_BOOKEND ("MI_ClassDecl_Placeholder::dealloc");
    if (NULL != pObj)
    {
        MI_ClassDecl_Placeholder* pDecl =
            reinterpret_cast<MI_ClassDecl_Placeholder*>(pObj);
        pDecl->~MI_ClassDecl_Placeholder ();
        pDecl->ob_type->tp_free (pObj);
    }
}


/*static*/ PyTypeObject const*
MI_ClassDecl_Placeholder::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


PyObject*
MI_ClassDecl_Placeholder::newObj (
    PyTypeObject* pType,
    PyObject* args,
    PyObject* keywords)
{
    SCX_BOOKEND ("MI_ClassDecl_Placeholder::newObj");
    PyObject* pObj = pType->tp_alloc (pType, 0);
    return pObj;
}


int
MI_ClassDecl_Placeholder::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    SCX_BOOKEND ("MI_ClassDecl_Placeholder::init");
    char* KEYWORDS[] = {
        "flags",
//        "code",
        "name",
        "qualifiers",
        "propertyDecls",
        "superClassName",
        "methodDecls",
        "functionTable",
        "owningClassName",
        NULL
    };
    int rval = 0;
    PyObject* pFlagsObj = NULL;
//    PyObject* pCodeObj = NULL;
    PyObject* pNameObj = NULL;
    PyObject* pQualifiersObj = NULL;
    PyObject* pPropertyDeclsObj = NULL;
    PyObject* pSuperClassNameObj = NULL;
    PyObject* pMethodDeclsObj = NULL;
    PyObject* pFunctionTableObj = NULL;
    PyObject* pOwningClassNameObj = NULL;

    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "OOOOOOOO", KEYWORDS,
//            args, keywords, "OOOOOOOOO", KEYWORDS,
            &pFlagsObj, &pNameObj, &pQualifiersObj, &pPropertyDeclsObj,
            &pSuperClassNameObj, &pMethodDeclsObj, &pFunctionTableObj,
            &pOwningClassNameObj))
//            &pFlagsObj, &pCodeObj, &pNameObj, &pQualifiersObj,
//            &pPropertyDeclsObj, &pSuperClassNameObj, &pMethodDeclsObj,
//            &pFunctionTableObj, &pOwningClassNameObj))
    {
        MI_Value<MI_UINT32>::Ptr pFlags;
        rval = to_MI_Value<MI_UINT32> (pFlagsObj, &pFlags);
        if (PY_FAILURE == rval)
        {
            SCX_BOOKEND_PRINT ("pFlags convert failed");
        }
//        MI_Value<MI_UINT32>::Ptr pCode;
//        if (PY_SUCCESS == rval)
//        {
//            rval = to_MI_Value<MI_UINT32> (pCodeObj, &pCode);
//            if (PY_FAILURE == rval)
//            {
//                SCX_BOOKEND_PRINT ("pCode convert failed");
//            }
//        }
        MI_Value<MI_STRING>::Ptr pName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value<MI_STRING> (pNameObj, &pName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pName convert failed");
            }
        }
        std::vector<MI_Qualifier_Wrapper::ValuePtr> qualifiers;
        if (PY_SUCCESS == rval)
        {
            rval = convertCollection<MI_Qualifier_Wrapper> (
                pQualifiersObj, &qualifiers);
        }
        std::vector<MI_PropertyDecl_Wrapper::ValuePtr> propertyDecls;
        if (PY_SUCCESS == rval)
        {
            rval = convertCollection<MI_PropertyDecl_Wrapper> (
                pPropertyDeclsObj, &propertyDecls);
        }
        MI_Value<MI_STRING>::Ptr pSuperClassName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (
                pSuperClassNameObj, &pSuperClassName);
        }
        std::vector<MI_MethodDecl_Placeholder::ConstPtr> methodDecls;
        if (PY_SUCCESS == rval)
        {
            SCX_BOOKEND ("convertCollection2<MI_MethodDecl_Placholder const>");
            rval = convertCollection2<MI_MethodDecl_Placeholder const> (
                pMethodDeclsObj, &methodDecls);
        }
        MI_FunctionTable_Placeholder::ConstPtr pFunctionTable;
        if (PyObject_TypeCheck (
                pFunctionTableObj,
                const_cast<PyTypeObject*>(
                    MI_FunctionTable_Placeholder::getPyTypeObject ())))
        {
            pFunctionTable = reinterpret_cast<MI_FunctionTable_Placeholder*>(
                pFunctionTableObj);
        }
        MI_Value<MI_STRING>::Ptr pOwningClassName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (
                pOwningClassNameObj, &pOwningClassName);
        }

        if (PY_SUCCESS == rval &&
            pFlags &&
//            pCode &&
            pName,
            pFunctionTable)
        {
            SCX_BOOKEND_PRINT ("MI_ClassDecl_Placeholder::init succeeded");
#if (1)
            std::ostringstream strm;
            strm << "flags: "
                 << static_cast<MI_Value<MI_UINT32> const*>(
                     pFlags.get ())->getValue ();
            SCX_BOOKEND_PRINT (strm.str ());


//            MI_Uint32 code = hashCode (
//                static_cast<MI_Value<MI_STRING> const*>(
//                    pName.get ())->getValue ());
//
//            if (code == static_cast<MI_Value<MI_UINT32> const*>(
//                    pCode.get ())->getValue ())
//            {
//                SCX_BOOKEND_PRINT ("code == hashCode (name)");
//            }
//            else
//            {
//                SCX_BOOKEND_PRINT ("code != hashCode (name)");
//            }
//            strm.str ("");
//            strm.clear ();
//            strm << "code: " << std::hex
//                 << static_cast<MI_Value<MI_UINT32> const*>(
//                     pCode.get ())->getValue ();
//            SCX_BOOKEND_PRINT (strm.str ());


            strm.str ("");
            strm.clear ();
            strm << "name: "
                 << static_cast<MI_Value<MI_STRING> const*>(
                     pName.get ())->getValue ();
            SCX_BOOKEND_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
            strm << "super class name: ";
            if (pSuperClassName)
            {
                strm << static_cast<MI_Value<MI_STRING> const*>(
                    pSuperClassName.get ())->getValue ();
            }
            else
            {
                strm << "NULL";
            }
            SCX_BOOKEND_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
            strm << "owning class name: ";
            if (pOwningClassName)
            {
                strm << static_cast<MI_Value<MI_STRING> const*>(
                    pOwningClassName.get ())->getValue ();
            }
            else
            {
                strm << "NULL";
            }
            SCX_BOOKEND_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();

#endif
            MI_Value<MI_UINT32>::Ptr pCode (new MI_Value<MI_UINT32> (
                hashCode (static_cast<MI_Value<MI_STRING> const*>(
                              pName.get ())->getValue ())));

            new (pSelf) MI_ClassDecl_Placeholder (
                pFlags, pCode, pName, qualifiers, propertyDecls,
                pSuperClassName, methodDecls, pFunctionTable, pOwningClassName);
//                 MI_Value<MI_UINT32>::ConstPtr (
//                     static_cast<MI_Value<MI_UINT32> const*>(pFlags.get ())),
//                 MI_Value<MI_UINT32>::ConstPtr (
//                     static_cast<MI_Value<MI_UINT32> const*>(pCode.get ())),
//                 MI_Value<MI_STRING>::ConstPtr (
//                     static_cast<MI_Value<MI_STRING> const*>(pName.get ())),
//                 qualifiers,
//                 propertyDecls,
//                 MI_Value<MI_STRING>::ConstPtr (
//                     static_cast<MI_Value<MI_STRING> const*>(
//                         pSuperClassName.get ())),
//                 methodDecls,
//                 pFunctionTable,
//                 MI_Value<MI_STRING>::ConstPtr (
//                     static_cast<MI_Value<MI_STRING> const*>(
//                         pOwningClassName.get ())));
        }
        else
        {
            SCX_BOOKEND_PRINT ("MI_ClassDecl_Placeholder::init failed");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("MI_ClassDecl_Placeholder::init parse args failed");
    }
    return rval;
}

    
/*dtor*/
MI_ClassDecl_Placeholder::~MI_ClassDecl_Placeholder ()
{
    SCX_BOOKEND ("MI_ClassDecl_Placeholder::dtor");
}


scx::MI_ClassDecl::Ptr
MI_ClassDecl_Placeholder::createClassDecl (
    PyObject* const pPyModule) const
{
    SCX_BOOKEND ("MI_ClassDecl_Placeholder::createClassDecl");
    assert (0 != pPyModule);
    MI_ClassDecl::Ptr pClassDecl;
    MI_FunctionTable::Ptr pFT (
        m_pFunctionTable->createFunctionTable (pPyModule));
    std::vector<MI_MethodDecl::Ptr> methodDecls;
    {
        SCX_BOOKEND ("creating MI_MethodDecls");
    for (std::vector<MI_MethodDecl_Placeholder::ConstPtr>::const_iterator
             pos = m_MethodDecls.begin (),
             end = m_MethodDecls.end ();
         pos != end;
         ++pos)
    {
        SCX_BOOKEND ("createMethodDecl loop");
        MI_MethodDecl::Ptr pMethodDecl;
        if (EXIT_SUCCESS == (*pos)->createMethodDecl (pPyModule, &pMethodDecl))
//        if (pMethodDecl)
        {
            SCX_BOOKEND ("push_back");
            methodDecls.push_back (pMethodDecl);
        }
    }
    }
    if (pFT &&
        methodDecls.size () == m_MethodDecls.size ())
    {
        SCX_BOOKEND ("creating MI_ClassDecl");
        pClassDecl =
            new MI_ClassDecl (m_pFlags, m_pCode, m_pName, &(m_Qualifiers[0]),
                              m_Qualifiers.size (), &(m_PropertyDecls[0]),
                              m_PropertyDecls.size (), m_pSuperClassName,
                              &(methodDecls[0]), methodDecls.size (), pFT);
    }
    return pClassDecl;
}


scx::MI_Value<MI_STRING>::ConstPtr const&
MI_ClassDecl_Placeholder::getName () const
{
    return m_pName;
}


scx::MI_Value<MI_STRING>::ConstPtr const&
MI_ClassDecl_Placeholder::getOwningClassName () const
{
    return m_pOwningClassName;
}


/*ctor*/
MI_ClassDecl_Placeholder::MI_ClassDecl_Placeholder (
    MI_Value<MI_UINT32>::ConstPtr const& pFlags,
    MI_Value<MI_UINT32>::ConstPtr const& pCode,
    MI_Value<MI_STRING>::ConstPtr const& pName,
    std::vector<MI_Qualifier::ConstPtr> const& qualifiers,
    std::vector<MI_PropertyDecl::ConstPtr> const& propertyDecls,
    MI_Value<MI_STRING>::ConstPtr const& pSuperClassName,
    std::vector<MI_MethodDecl_Placeholder::ConstPtr> const& methodDecls,
    MI_FunctionTable_Placeholder::ConstPtr const& pFunctionTable,
    MI_Value<MI_STRING>::ConstPtr const& pOwningClassName)
    : m_pFlags (pFlags)
    , m_pCode (pCode)
    , m_pName (pName)
    , m_Qualifiers (qualifiers)
    , m_PropertyDecls (propertyDecls)
    , m_pSuperClassName (pSuperClassName)
    , m_MethodDecls (methodDecls)
    , m_pFunctionTable (pFunctionTable)
    , m_pOwningClassName (pOwningClassName)
{
    SCX_BOOKEND ("MI_ClassDecl_Placeholder::ctor");
}















/*static*/ char const MI_SchemaDecl_Placeholder::NAME[] = "MI_SchemaDecl";
/*static*/ char const MI_SchemaDecl_Placeholder::OMI_NAME[] =
    "omi.MI_SchemaDecl";
/*static*/ char const MI_SchemaDecl_Placeholder::DOC[] =
    "omi.MI_SchemaDecl utility";
/*static*/ PyTypeObject MI_SchemaDecl_Placeholder::s_PyTypeObject = {};


/*static*/ void
MI_SchemaDecl_Placeholder::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_SchemaDecl_Placeholder::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_SchemaDecl_Placeholder);
    s_PyTypeObject.tp_dealloc = dealloc;
    s_PyTypeObject.tp_flags = Py_TPFLAGS_DEFAULT;
    s_PyTypeObject.tp_doc = DOC;
    s_PyTypeObject.tp_init = init;
    s_PyTypeObject.tp_new = newObj;
    s_PyTypeObject.tp_alloc = PyType_GenericAlloc;
    if (0 == PyType_Ready (&s_PyTypeObject))
    {
        Py_INCREF (&s_PyTypeObject);
        PyModule_AddObject (
            pModule, NAME, reinterpret_cast<PyObject*>(&s_PyTypeObject));
    }
}


/*static*/ void
MI_SchemaDecl_Placeholder::dealloc (
    PyObject* pObj)
{
    //SCX_BOOKEND ("MI_SchemaDecl_Placeholder::dealloc");
    if (NULL != pObj)
    {
        MI_SchemaDecl_Placeholder* pDecl =
            reinterpret_cast<MI_SchemaDecl_Placeholder*>(pObj);
        pDecl->~MI_SchemaDecl_Placeholder ();
        pDecl->ob_type->tp_free (pObj);
    }
}


/*static*/ PyTypeObject const*
MI_SchemaDecl_Placeholder::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


PyObject*
MI_SchemaDecl_Placeholder::newObj (
    PyTypeObject* pType,
    PyObject* args,
    PyObject* keywords)
{
    //SCX_BOOKEND ("MI_SchemaDecl_Placeholder::newObj");
    PyObject* pObj = pType->tp_alloc (pType, 0);
    return pObj;
}


int
MI_SchemaDecl_Placeholder::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    SCX_BOOKEND ("MI_SchemaDecl_Placeholder::init");
    char* KEYWORDS[] = {
        "qualifierDecls",
        "classDecls",
        NULL
    };
    int rval = 0;
    PyObject* pQualifierDeclsObj = NULL;
    PyObject* pClassDeclsObj = NULL;

    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "OO", KEYWORDS,
            &pQualifierDeclsObj, &pClassDeclsObj))
    {
        std::vector<MI_QualifierDecl_Wrapper::ValuePtr> qualifierDecls;
        if (PY_SUCCESS == rval)
        {
            rval = convertCollection<MI_QualifierDecl_Wrapper> (
                pQualifierDeclsObj, &qualifierDecls);
        }

        std::vector<MI_ClassDecl_Placeholder::ConstPtr> classDecls;
        if (PY_SUCCESS == rval)
        {
            rval = convertCollection2<MI_ClassDecl_Placeholder const> (
                pClassDeclsObj, &classDecls);
        }
        if (PY_SUCCESS == rval)
        {
            SCX_BOOKEND_PRINT ("MI_SchemaDecl_Placeholder::init succeeded");
            std::ostringstream strm;
            strm << "MI_SchemaDecl_Placeholder address: " << std::hex
                 << static_cast<void*>(pSelf);
            SCX_BOOKEND_PRINT (strm.str ());
            strm.str ("");
            strm.clear ();
#if (1)
            new (pSelf) MI_SchemaDecl_Placeholder (
                qualifierDecls, classDecls);
#else
            MI_SchemaDecl_Placeholder* pSchemaDecl_PH =
                reinterpret_cast<MI_SchemaDecl_Placeholder*>(pSelf);
            new (const_cast<std::vector<MI_QualifierDecl::ConstPtr>* >(
                     &(pSchemaDecl_PH->m_QualifierDecls)))
                std::vector<MI_QualifierDecl::ConstPtr> (qualifierDecls);            
            new (const_cast<std::vector<MI_ClassDecl_Placeholder::ConstPtr>* >(
                     &(pSchemaDecl_PH->m_ClassDecls)))
                std::vector<MI_ClassDecl_Placeholder::ConstPtr> (classDecls);
#endif
        }
        else
        {
            SCX_BOOKEND_PRINT ("MI_SchemaDecl_Placeholder::init failed");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("MI_SchemaDecl_Placeholder::init parse args failed");
    }
    return rval;
}

    
/*dtor*/
MI_SchemaDecl_Placeholder::~MI_SchemaDecl_Placeholder ()
{
    SCX_BOOKEND ("MI_SchemaDecl_Placeholder::dtor");
}


scx::MI_SchemaDecl::Ptr
MI_SchemaDecl_Placeholder::createSchemaDecl (
    PyObject* const pPyModule) const
{
    SCX_BOOKEND ("MI_SchemaDecl_Placeholder::createSchemaDecl");
    assert (0 != pPyModule);
    SCX_BOOKEND_PRINT ("**** 0 ****");
    MI_SchemaDecl::Ptr pSchemaDecl;
    std::vector<MI_ClassDecl::Ptr> classDecls;
    SCX_BOOKEND_PRINT ("**** 1 ****");

    std::ostringstream strm;
    strm << "m_ClassDecls.size (): " << m_ClassDecls.size ();
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();


//    for (size_t i = 0, count = m_ClassDecls.size (); i < count; ++i)
//    {
//        SCX_BOOKEND_PRINT ("**** 3");
//        if (m_ClassDecls[i].get ())
//        {
//            SCX_BOOKEND_PRINT ("m_ClassDecls[i] is not NULL");
//        }
//        else
//        {
//            SCX_BOOKEND_PRINT ("m_ClassDecls[i] is NULL");
//        }
//        SCX_BOOKEND_PRINT ("     3 ****");
//    }
    SCX_BOOKEND_PRINT ("**** 4 ****");

    for (std::vector<MI_ClassDecl_Placeholder::ConstPtr>::const_iterator
             pos = m_ClassDecls.begin (),
             end = m_ClassDecls.end ();
         pos != end;
         ++pos)
    {
        SCX_BOOKEND_PRINT ("**** 5");
        if (*pos)
        {
            SCX_BOOKEND_PRINT ("*pos is not NULL");
        }
        else
        {
            SCX_BOOKEND_PRINT ("*pos is NULL");
        }
        MI_ClassDecl::Ptr pClassDecl = (*pos)->createClassDecl (pPyModule);
        SCX_BOOKEND_PRINT ("     5 ****");
        if (pClassDecl)
        {
            classDecls.push_back (pClassDecl);
        }
    }
    SCX_BOOKEND_PRINT ("**** 10 ****");
    if (classDecls.size () == m_ClassDecls.size ())
    {
        int rval = EXIT_SUCCESS;
        for (size_t i = 0, count = classDecls.size ();
             i < count && EXIT_SUCCESS == rval;
             ++i)
        {
            MI_Value<MI_STRING>::ConstPtr const& pOwningClassName =
                m_ClassDecls[i]->getOwningClassName ();
            if (pOwningClassName)
            {
                size_t j = 0;
                size_t const count = m_ClassDecls.size ();
                while (j < count &&
                       m_ClassDecls[j]->getName ()->getValue () !=
                           pOwningClassName->getValue ())
                {
                    ++j;
                }
                if (j < count)
                {
                    classDecls[i]->setOwningClassDecl (classDecls[j]);
                }
                else
                {
                    rval = EXIT_FAILURE;
                }
            }
        }
        if (EXIT_SUCCESS == rval)
        {
            pSchemaDecl = new MI_SchemaDecl (
                &(m_QualifierDecls[0]), m_QualifierDecls.size (),
                &(classDecls[0]), classDecls.size ());
        }
    }
    SCX_BOOKEND_PRINT ("**** 40 ****");
//    MI_FunctionTable::Ptr pFT (
//        m_pFunctionTable->createFunctionTable (pPyModule));
//    std::vector<MI_MethodDecl::Ptr> methodDecls;
//    for (std::vector<MI_MethodDecl_Placeholder::ConstPtr>::const_iterator
//             pos = m_MethodDecls.begin (),
//             end = m_MethodDecls.end ();
//         pos != end;
//         ++pos)
//    {
//        MI_MethodDecl::Ptr pMethodDecl = (*pos)->createMethodDecl (pPyModule);
//        if (pMethodDecl)
//        {
//            methodDecls.push_back (pMethodDecl);
//        }
//    }
//    if (pFT &&
//        methodDecls.size () == m_MethodDecls.size ())
//    {
//        pClassDecl =
//            new MI_SchemaDecl (m_pFlags, m_pCode, m_pName, &(m_Qualifiers[0]),
//                              m_Qualifiers.size (), &(m_PropertyDecls[0]),
//                              m_PropertyDecls.size (), m_pSuperClassName,
//                              &(methodDecls[0]), methodDecls.size (), pFT);
//    }
    return pSchemaDecl;
}


/*ctor*/
MI_SchemaDecl_Placeholder::MI_SchemaDecl_Placeholder (
    std::vector<MI_QualifierDecl::ConstPtr> const& qualifierDecls,
    std::vector<MI_ClassDecl_Placeholder::ConstPtr> const& classDecls)
    : m_QualifierDecls (qualifierDecls)
    , m_ClassDecls (classDecls)
{
    SCX_BOOKEND ("MI_SchemaDecl_Placeholder::ctor");
    std::ostringstream strm;
    strm << "qualifierDecls.size (): " << qualifierDecls.size ();
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
    strm << "classDecls.size (): " << classDecls.size ();
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();
}



//} // namespace scx

