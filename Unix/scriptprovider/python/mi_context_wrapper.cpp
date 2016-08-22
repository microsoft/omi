#include "mi_context_wrapper.hpp"


#include "mi_instance_wrapper.hpp"
#include "mi_wrapper.hpp"


#include <cassert>


using namespace scx;


namespace
{


template<typename T>
int
to_MI_Result (
    T const& val,
    MI_Result* const pResultOut)
{
    int rval = EXIT_SUCCESS;
    switch (val)
    {
    case MI_RESULT_OK:
        *pResultOut = MI_RESULT_OK;
        break;
    case MI_RESULT_FAILED:
        *pResultOut = MI_RESULT_FAILED;
        break;
    case MI_RESULT_ACCESS_DENIED:
        *pResultOut = MI_RESULT_ACCESS_DENIED;
        break;
    case MI_RESULT_INVALID_NAMESPACE:
        *pResultOut = MI_RESULT_INVALID_NAMESPACE;
        break;
    case MI_RESULT_INVALID_PARAMETER:
        *pResultOut = MI_RESULT_INVALID_PARAMETER;
        break;
    case MI_RESULT_INVALID_CLASS:
        *pResultOut = MI_RESULT_INVALID_CLASS;
        break;
    case MI_RESULT_NOT_FOUND:
        *pResultOut = MI_RESULT_NOT_FOUND;
        break;
    case MI_RESULT_NOT_SUPPORTED:
        *pResultOut = MI_RESULT_NOT_SUPPORTED;
        break;
    case MI_RESULT_CLASS_HAS_CHILDREN:
        *pResultOut = MI_RESULT_CLASS_HAS_CHILDREN;
        break;
    case MI_RESULT_CLASS_HAS_INSTANCES:
        *pResultOut = MI_RESULT_CLASS_HAS_INSTANCES;
        break;
    case MI_RESULT_INVALID_SUPERCLASS:
        *pResultOut = MI_RESULT_INVALID_SUPERCLASS;
        break;
    case MI_RESULT_ALREADY_EXISTS:
        *pResultOut = MI_RESULT_ALREADY_EXISTS;
        break;
    case MI_RESULT_NO_SUCH_PROPERTY:
        *pResultOut = MI_RESULT_NO_SUCH_PROPERTY;
        break;
    case MI_RESULT_TYPE_MISMATCH:
        *pResultOut = MI_RESULT_TYPE_MISMATCH;
        break;
    case MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED:
        *pResultOut = MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED;
        break;
    case MI_RESULT_INVALID_QUERY:
        *pResultOut = MI_RESULT_INVALID_QUERY;
        break;
    case MI_RESULT_METHOD_NOT_AVAILABLE:
        *pResultOut = MI_RESULT_METHOD_NOT_AVAILABLE;
        break;
    case MI_RESULT_METHOD_NOT_FOUND:
        *pResultOut = MI_RESULT_METHOD_NOT_FOUND;
        break;
    case MI_RESULT_NAMESPACE_NOT_EMPTY:
        *pResultOut = MI_RESULT_NAMESPACE_NOT_EMPTY;
        break;
    case MI_RESULT_INVALID_ENUMERATION_CONTEXT:
        *pResultOut = MI_RESULT_INVALID_ENUMERATION_CONTEXT;
        break;
    case MI_RESULT_INVALID_OPERATION_TIMEOUT:
        *pResultOut = MI_RESULT_INVALID_OPERATION_TIMEOUT;
        break;
    case MI_RESULT_PULL_HAS_BEEN_ABANDONED:
        *pResultOut = MI_RESULT_PULL_HAS_BEEN_ABANDONED;
        break;
    case MI_RESULT_PULL_CANNOT_BE_ABANDONED:
        *pResultOut = MI_RESULT_PULL_CANNOT_BE_ABANDONED;
        break;
    case MI_RESULT_FILTERED_ENUMERATION_NOT_SUPPORTED:
        *pResultOut = MI_RESULT_FILTERED_ENUMERATION_NOT_SUPPORTED;
        break;
    case MI_RESULT_CONTINUATION_ON_ERROR_NOT_SUPPORTED:
        *pResultOut = MI_RESULT_CONTINUATION_ON_ERROR_NOT_SUPPORTED;
        break;
    case MI_RESULT_SERVER_LIMITS_EXCEEDED:
        *pResultOut = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        break;
    case MI_RESULT_SERVER_IS_SHUTTING_DOWN:
        *pResultOut = MI_RESULT_SERVER_IS_SHUTTING_DOWN;
        break;
    default:
        SCX_BOOKEND_PRINT ("invalid conversion");
        rval = EXIT_FAILURE;
    }
    return rval;
}


}


/*static*/ char const MI_Context_Wrapper::NAME[] = "MI_Context";
/*static*/ char const MI_Context_Wrapper::OMI_NAME[] = "omi.MI_Context";
/*static*/ char const MI_Context_Wrapper::DOC[] =
    "omi.MI_Context utility";
/*static*/ PyTypeObject MI_Context_Wrapper::s_PyTypeObject = {};
/*static*/ PyMethodDef MI_Context_Wrapper::METHODS[] = {
    { "PostResult",
      reinterpret_cast<PyCFunction>(MI_Context_Wrapper::postResult),
      METH_KEYWORDS, "post a result to omi" },
    { "PostInstance",
      reinterpret_cast<PyCFunction>(MI_Context_Wrapper::postInstance),
      METH_KEYWORDS, "return a MI_Instance to omi" },
    { "NewInstance",
      reinterpret_cast<PyCFunction>(MI_Context_Wrapper::newInstance),
      METH_KEYWORDS, "create a new MI_Instance" },
    { NULL, NULL, 0, NULL }
};


/*static*/ void
MI_Context_Wrapper::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_Context_Wrapper::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_Context_Wrapper);
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
MI_Context_Wrapper::dealloc (
    PyObject* pObj)
{
    //SCX_BOOKEND ("MI_Context_Wrapper::dealloc");
    if (NULL != pObj)
    {
        MI_Context_Wrapper* pDecl =
            reinterpret_cast<MI_Context_Wrapper*>(pObj);
        pDecl->~MI_Context_Wrapper ();
        pDecl->ob_type->tp_free (pObj);
    }
}


/*static*/ PyObject*
MI_Context_Wrapper::postResult (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    SCX_BOOKEND ("MI_Context_Wrapper::postResult");
    PyObject* pRet = NULL;
    // parse the args
    char* KEYWORDS[] = {
        "result",
        NULL
    };
    MI_Uint32 resultAsUInt;
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "I", KEYWORDS, &resultAsUInt))
    {
        SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        MI_Result result;
        if (EXIT_SUCCESS == to_MI_Result (resultAsUInt, &result))
        {
            MI_Context_Wrapper* pContext =
                reinterpret_cast<MI_Context_Wrapper*>(pSelf);
            int rval = pContext->m_pContext->postResult (result);
            if (socket_wrapper::SUCCESS == rval)
            {
                SCX_BOOKEND_PRINT ("results were sent");
                pRet = Py_None;
            }
            else
            {
                SCX_BOOKEND_PRINT ("sending results failed");
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("result is not an MI_RESULT value");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (
            PyExc_ValueError,
            "ERROR: MI_Context_Wrapper::postResult invalid arguments");
    }
    Py_XINCREF (pRet);
    return pRet;
}


/*static*/ PyObject*
MI_Context_Wrapper::postInstance (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    SCX_BOOKEND ("MI_Context_Wrapper::postInstance");
    PyObject* pRet = NULL;
    // parse the args
    char* KEYWORDS[] = {
        "instance",
        NULL
    };
    PyObject* pInstanceObj = NULL;
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "O", KEYWORDS, &pInstanceObj))
    {
        SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords succeeded");
        if (PyObject_TypeCheck (
                pInstanceObj,
                const_cast<PyTypeObject*>(
                    MI_Instance_Wrapper::getPyTypeObject ())))
        {
            MI_Context_Wrapper* pContext =
                reinterpret_cast<MI_Context_Wrapper*>(pSelf);
            MI_Instance_Wrapper* pInstance =
                reinterpret_cast<MI_Instance_Wrapper*>(pInstanceObj);
            int rval = pContext->m_pContext->postInstance (
                pInstance->getInstance ());
            if (socket_wrapper::SUCCESS == rval)
            {
                SCX_BOOKEND_PRINT ("MI_Instance was sent");
                pRet = Py_None;
            }
            else
            {
                SCX_BOOKEND_PRINT ("sending MI_Instance failed");
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("instance is not a MI_Instance");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
        PyErr_SetString (
            PyExc_ValueError,
            "ERROR: MI_Context_Wrapper::postInstance invalid arguments");
    }
    Py_XINCREF (pRet);
    return pRet;
}


/*static*/
PyObject*
MI_Context_Wrapper::newInstance (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    SCX_BOOKEND ("MI_Context_Wrapper::newInstance");
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
            MI_Context_Wrapper* pContext =
                reinterpret_cast<MI_Context_Wrapper*>(pSelf);
            MI_Instance::Ptr pInstance;
            MI_Value<MI_STRING>::ConstPtr pName (
                new MI_Value<MI_STRING> (name));
            ret = pContext->m_pContext->newInstance (pName, &pInstance);
            if (0 == ret)
            {
                SCX_BOOKEND_PRINT ("Name is a member of MI_SchemaDecl");
                if (pInstance)
                {
                    SCX_BOOKEND_PRINT ("pInstance is not NULL");
                    MI_Instance_Wrapper::PyPtr pyInstance =
                        MI_Instance_Wrapper::createPyPtr (pInstance);
                    Py_INCREF (pyInstance.get ());
                    rval = reinterpret_cast<PyObject*>(pyInstance.get ());
                }
                else
                {
                    SCX_BOOKEND_PRINT ("pInstance is NULL");
                    Py_INCREF (Py_None);
                    rval = Py_None;
                }
            }
            else
            {
                SCX_BOOKEND_PRINT ("Class name not a member of MI_SchemaDecl");
                // error: Name is not a member of MI_SchemaDecl
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
MI_Context_Wrapper::PyPtr
MI_Context_Wrapper::createPyPtr (
        MI_Context::Ptr const& pContext)
{
    //SCX_BOOKEND ("MI_Context_Wrapper::createPyPtr");
    PyObjPtr pPyContext (s_PyTypeObject.tp_alloc (&s_PyTypeObject, 0));
    if (pPyContext)
    {
        return PyPtr (
            new (pPyContext.release ()) MI_Context_Wrapper (pContext));
    }
    return PyPtr ();
}


/*static*/ PyTypeObject const*
MI_Context_Wrapper::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


//PyObject*
//MI_Context_Wrapper::newObj (
//    PyTypeObject* pType,
//    PyObject* args,
//    PyObject* keywords)
//{
//    SCX_BOOKEND ("MI_Context_Wrapper::newObj");
//    PyObject* pObj = pType->tp_alloc (pType, 0);
//    return pObj;
//}


//int
//MI_Context_Wrapper::init (
//    PyObject* pSelf,
//    PyObject* args,
//    PyObject* keywords)
//{
//    SCX_BOOKEND ("MI_Context_Wrapper::init");
//    char* KEYWORDS[] = {
//        "name",
//        "type",
//        "scope",
//        "flavor",
//        "subscript",
//        "value",
//        NULL
//    };
//    int rval = 0;
//    PyObject* pName = NULL;
//    PyObject* pType = NULL;
//    PyObject* pScope = NULL;
//    PyObject* pFlavor = NULL;
//    PyObject* pSubscript = NULL;
//    PyObject* pValue = NULL;
//    if (PyArg_ParseTupleAndKeywords (
//            args, keywords, "OOOO|O", KEYWORDS, &pName, &pType, &pScope,
//            &pFlavor, &pValue))
//    {
//        MI_ValueBase::Ptr pNameVal;
//        rval = Py_to_MI_convert (MI_STRING, pName, &pNameVal);
//        if (0 != rval)
//        {
//            SCX_BOOKEND_PRINT ("pName convert failed");
//        }
//        MI_ValueBase::Ptr pTypeVal;
//        if (0 == rval)
//        {
//            rval = Py_to_MI_convert (MI_UINT32, pType, &pTypeVal);
//            if (0 != rval)
//            {
//                SCX_BOOKEND_PRINT ("pType convert failed");
//            }
//        }
//        MI_ValueBase::Ptr pScopeVal;
//        if (0 == rval)
//        {
//            rval = Py_to_MI_convert (MI_UINT32, pScope, &pScopeVal);
//            if (0 != rval)
//            {
//                SCX_BOOKEND_PRINT ("pScope convert failed");
//            }
//        }
//        MI_ValueBase::Ptr pFlavorVal;
//        if (0 == rval)
//        {
//            rval = Py_to_MI_convert (MI_UINT32, pFlavor, &pFlavorVal);
//            if (0 != rval)
//            {
//                SCX_BOOKEND_PRINT ("pFlavor convert failed");
//            }
//        }
//        MI_ValueBase::Ptr pValueVal;
//        if (0 == rval &&
//            NULL != pValue)
//        {
//            rval = Py_to_MI_convert (
//                static_cast<MI_Value<MI_UINT32>*>(
//                    pTypeVal.get ())->getValue (),
//                pValue, &pValueVal);
//        }
//        if (0 == rval &&
//            pNameVal &&
//            pTypeVal &&
//            pScopeVal &&
//            pFlavorVal)
//        {
//            //SCX_BOOKEND_PRINT ("MI_Context_Wrapper::init succeeded");
//            new (pSelf) MI_Context_Wrapper (
//                static_cast<MI_Value<MI_STRING> const*>(
//                    pNameVal.get ())->getValue (),
//                static_cast<MI_Value<MI_UINT32> const*>(
//                    pTypeVal.get ())->getValue (),
//                static_cast<MI_Value<MI_UINT32> const*>(
//                    pScopeVal.get ())->getValue (),
//                static_cast<MI_Value<MI_UINT32> const*>(
//                    pFlavorVal.get ())->getValue (),
//                MI_ValueBase::ConstPtr (pValueVal.get ()));
//        }
//        else
//        {
//            SCX_BOOKEND_PRINT ("MI_Context_Wrapper::init failed");
//        }
//    }
//    else
//    {
//        SCX_BOOKEND_PRINT ("MI_Context_Wrapper::init parse args failed");
//    }
//    return rval;
//}


/*ctor*/
MI_Context_Wrapper::MI_Context_Wrapper (
    MI_Context::Ptr const& pContext)
    : m_pContext (pContext)
{
    //SCX_BOOKEND ("MI_Context_Wrapper::ctor");
}

    
/*dtor*/
MI_Context_Wrapper::~MI_Context_Wrapper ()
{
    SCX_BOOKEND ("MI_Context_Wrapper::dtor");
}
