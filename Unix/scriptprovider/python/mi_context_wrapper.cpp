// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
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
    { "NewParameters",
      reinterpret_cast<PyCFunction>(MI_Context_Wrapper::newParameters),
      METH_KEYWORDS, "create a new MI_Instance for method parameters" },
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
PyObject*
MI_Context_Wrapper::newParameters (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    SCX_BOOKEND ("MI_Context_Wrapper::newParameters");
    PyObject* rval = NULL;
    char* KEYWORDS[] = {
        "className",
        "methodName",
        NULL
    };
    PyObject* pClassNameObj = NULL;
    PyObject* pMethodNameObj = NULL;
    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "OO", KEYWORDS, &pClassNameObj, &pMethodNameObj))
    {
        MI_Type<MI_STRING>::type_t className;
        int ret = fromPyObject (pClassNameObj, &className);

        MI_Type<MI_STRING>::type_t methodName;
        if (PY_SUCCESS == ret)
        {
            ret = fromPyObject (pMethodNameObj, &methodName);
        }
        else
        {
            SCX_BOOKEND_PRINT ("failed to convert class name");
        }

        if (PY_SUCCESS == ret)
        {
            MI_Context_Wrapper* pContext =
                reinterpret_cast<MI_Context_Wrapper*>(pSelf);

            MI_Instance::Ptr pInstance;
            MI_Value<MI_STRING>::ConstPtr pClassName (
                new MI_Value<MI_STRING> (className));

            MI_Value<MI_STRING>::ConstPtr pMethodName (
                new MI_Value<MI_STRING> (methodName));


            ret = pContext->m_pContext->newParameters (
                pClassName, pMethodName, &pInstance);

            if (0 == ret)
            {
                SCX_BOOKEND_PRINT (
                    "ClassName::MethodName is a member of MI_SchemaDecl");
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
                SCX_BOOKEND_PRINT (
                    "ClassName::MethodName not a member of MI_SchemaDecl");
                // error: Name is not a member of MI_SchemaDecl
            }
        }
        else
        {
            SCX_BOOKEND_PRINT ("failed to convert");
            // error: Py_to_MI_convert failed
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("PyArg_ParseTupleAndKeywords failed");
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
