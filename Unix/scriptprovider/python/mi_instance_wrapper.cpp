#include "mi_instance_wrapper.hpp"


#include "mi_wrapper.hpp"
#include "mi_schema.hpp"

using namespace scx;
//namespace scx
//{


namespace
{


template<TypeID_t TYPE_ID>
PyObject*
wrap_value (
    scx::MI_ValueBase::Ptr const& pValue)
{
    typename scx::MI_Wrapper<TYPE_ID>::PyPtr pyValue =
        scx::MI_Wrapper<TYPE_ID>::createPyPtr (
            typename scx::MI_Value<TYPE_ID>::Ptr (
                static_cast<scx::MI_Value<TYPE_ID>*>(pValue.get ())));
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
//    s_PyTypeObject.tp_init = init;
//    s_PyTypeObject.tp_new = newObj;
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
    SCX_BOOKEND ("MI_Instance_Wrapper::dealloc");
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
    SCX_BOOKEND ("MI_Instance_Wrapper::createPyPtr");
    PyObjPtr pPyInstance (s_PyTypeObject.tp_alloc (&s_PyTypeObject, 0));
    if (pPyInstance)
    {
        SCX_BOOKEND_PRINT ("instance allocated");
        return PyPtr (
            new (pPyInstance.release ()) MI_Instance_Wrapper (pInstance));
    }
    SCX_BOOKEND_PRINT ("instance was not allocated");
    return PyPtr ();
}


/*static*/ PyTypeObject const*
MI_Instance_Wrapper::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


//PyObject*
//MI_Instance_Wrapper::newObj (
//    PyTypeObject* pType,
//    PyObject* args,
//    PyObject* keywords)
//{
//    SCX_BOOKEND ("MI_Instance_Wrapper::newObj");
//    PyObject* pObj = pType->tp_alloc (pType, 0);
//    return pObj;
//}


//int
//MI_Instance_Wrapper::init (
//    PyObject* pSelf,
//    PyObject* args,
//    PyObject* keywords)
//{
//    SCX_BOOKEND ("MI_Instance_Wrapper::init");
//    int rval = 0;
//    return rval;
//}


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
                    // todo construct the appropriate Python MI_Wrapper type.
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
                    case MI_BOOLEANA:
                    case MI_UINT8A:
                    case MI_SINT8A:
                    case MI_UINT16A:
                    case MI_SINT16A:
                    case MI_UINT32A:
                    case MI_SINT32A:
                    case MI_UINT64A:
                    case MI_SINT64A:
                    case MI_REAL32A:
                    case MI_REAL64A:
                    case MI_CHAR16A:
                    case MI_DATETIMEA:
                    case MI_STRINGA:
                    case MI_REFERENCEA:
                    case MI_INSTANCEA:
                    default:
                        SCX_BOOKEND ("encountered an unhandled type");
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
        MI_Type<MI_STRING>::type_t name;
        int ret = fromPyObject (pNameObj, &name);
        if (PY_SUCCESS == ret)
        {
            MI_Instance_Wrapper* pInstance =
                reinterpret_cast<MI_Instance_Wrapper*>(pSelf);
            MI_PropertyDecl::ConstPtr pPropertyDecl =
                pInstance->m_pInstance->getClassDecl ()->getPropertyDecl (name);
            if (pPropertyDecl)
            {
                SCX_BOOKEND_PRINT ("A property was found for Name");
                std::ostringstream strm;
                strm << "type: "
//                     << (~protocol::MI_NULL_FLAG &
                     << (
                         pPropertyDecl->getType ()->getValue ());
                SCX_BOOKEND_PRINT (strm.str ());
                strm.str ("");
                strm.clear ();

                
                // need to replace this instance of Py_to_MI_convert with
                // something like to_MI_ValueBase from mi_schema_wrapper.cpp
                MI_ValueBase::Ptr pValue;
                ret = to_MI_ValueBase (
//                ret = to_MI_ValueBase (~protocol::MI_NULL_FLAG &
                                       pPropertyDecl->getType ()->getValue (),
                                       pValueObj, &pValue);

//                ret = Py_to_MI_convert (
//                    ~protocol::MI_NULL_FLAG &
//                    pPropertyDecl->getType ()->getValue (),
//                    pValueObj, &pValue);


                if (0 == ret)
                {
                    SCX_BOOKEND_PRINT ("Py_to_MI_convert succeeded");
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
                SCX_BOOKEND_PRINT ("Name is not a property");
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


/*ctor*/
MI_Instance_Wrapper::MI_Instance_Wrapper (
    MI_Instance::Ptr const& pInstance)
    : m_pInstance (pInstance)
{
    SCX_BOOKEND ("MI_Instance_Wrapper::ctor");
}

    
/*dtor*/
MI_Instance_Wrapper::~MI_Instance_Wrapper ()
{
    SCX_BOOKEND ("MI_Instance_Wrapper::dtor");
}
