#include "mi_function_table_placeholder.hpp"


#include "functor.hpp"
#include "mi_schema_wrapper.hpp"
#include "mi_context_wrapper.hpp"
#include "mi_function_table.hpp"
#include "mi_instance_wrapper.hpp"
#include "mi_module.hpp"
#include "mi_wrapper.hpp"
#include "unique_ptr.hpp"


#include <cassert>


using namespace scx;


namespace scx
{


class U_Functor
{
public:
    /*ctor*/ U_Functor (py_ptr<PyObject>const& pFn)
        : m_pFn (pFn)
    {
//        SCX_BOOKEND ("U_Functor::ctor");
    }

    /*dtor*/ ~U_Functor ()
    {
//        SCX_BOOKEND ("U_Functor::dtor");
    }

    int
    operator () (
        MI_Context::Ptr const& pContext) const
    {
        SCX_BOOKEND ("U_Functor::operator ()");
        int rval = EXIT_SUCCESS;
        MI_Context_Wrapper::PyPtr pyContext (
            MI_Context_Wrapper::createPyPtr (pContext));
        if (pyContext)
        {
            PyObjPtr pArgs (PyTuple_New (1));
            if (pArgs)
            {
                PyTuple_SetItem (pArgs.get (), 0,
                                 reinterpret_cast<PyObject*>(pyContext.get ()));
                PyObjPtr pRval (PyObject_CallObject (
                                    m_pFn.get (), pArgs.get ()));
                if (!pRval)
                {
                    SCX_BOOKEND_PRINT ("Error returned from call");
                    rval = EXIT_FAILURE;
                }
                else
                {
                    if (Py_None == pRval.get ())
                    {
                        SCX_BOOKEND_PRINT ("an object was returned (Py_None)");
                    }
                    else
                    {
                        SCX_BOOKEND_PRINT (
                            "an object was returned (not Py_None)");
                    }
                }
            }
        }
        else
        {
            PyErr_SetString (PyExc_TypeError, "invalid argument");
            rval = EXIT_FAILURE;
        }
        return rval;
    }

private:
    py_ptr<PyObject> const m_pFn;
};




class GM_Functor
{
public:
    /*ctor*/ GM_Functor (py_ptr<PyObject>const& pFn)
        : m_pFn (pFn)
    {
//        SCX_BOOKEND ("GM_Functor::ctor");
    }

    /*dtor*/ ~GM_Functor ()
    {
//        SCX_BOOKEND ("GM_Functor::dtor");
    }

    int
    operator () (
        MI_Context::Ptr const& pContext,
        MI_Value<MI_STRING>::Ptr const& pNameSpace,
        MI_Value<MI_STRING>::Ptr const& pClassName,
        MI_Instance::Ptr const& pInstance,
        MI_PropertySet::ConstPtr const& pPropertySet) const
    {
        SCX_BOOKEND ("GM_Functor::operator ()");
        int rval = EXIT_SUCCESS;
        MI_Context_Wrapper::PyPtr pyContext (
            MI_Context_Wrapper::createPyPtr (pContext));
        MI_Wrapper<MI_STRING>::PyPtr pyNameSpace (
            MI_Wrapper<MI_STRING>::createPyPtr (pNameSpace));
        MI_Wrapper<MI_STRING>::PyPtr pyClassName (
            MI_Wrapper<MI_STRING>::createPyPtr (pClassName));
        MI_Instance_Wrapper::PyPtr pyInstance (
            MI_Instance_Wrapper::createPyPtr (pInstance));
        MI_PropertySet_Wrapper::PyPtr pyPropertySet;
        if (pPropertySet)
        {
            pyPropertySet = MI_PropertySet_Wrapper::createPyPtr (pPropertySet);
        }
        if (pyContext && pyNameSpace && pyClassName && pyInstance)
        {
            PyObjPtr pArgs (PyTuple_New (5));
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
                    reinterpret_cast<PyObject*>(pyInstance.get ()));
                if (pPropertySet)
                {
                    PyTuple_SetItem (
                        pArgs.get (), 4,
                        reinterpret_cast<PyObject*>(pyPropertySet.get ()));
                }
                else
                {
                    Py_INCREF (Py_None);
                    PyTuple_SetItem (pArgs.get (), 4, Py_None);
                }
                PyObjPtr pRval (PyObject_CallObject (
                                    m_pFn.get (), pArgs.get ()));
                if (!pRval)
                {
                    SCX_BOOKEND_PRINT ("Error returned from call");
                    rval = EXIT_FAILURE;
                }
                else
                {
                    if (Py_None == pRval.get ())
                    {
                        SCX_BOOKEND_PRINT ("an object was returned (Py_None)");
                    }
                    else
                    {
                        SCX_BOOKEND_PRINT (
                            "an object was returned (not Py_None)");
                    }
                }
            }
        }
        else
        {
            PyErr_SetString (PyExc_TypeError, "invalid argument");
            rval = EXIT_FAILURE;
        }
        return rval;
    }

private:
    py_ptr<PyObject> const m_pFn;
};


class CD_Functor
{
public:
    /*ctor*/ CD_Functor (py_ptr<PyObject>const& pFn)
        : m_pFn (pFn)
    {
//        SCX_BOOKEND ("CD_Functor::ctor");
    }

    /*dtor*/ ~CD_Functor ()
    {
//        SCX_BOOKEND ("CD_Functor::dtor");
    }

    int
    operator () (
        MI_Context::Ptr const& pContext,
        MI_Value<MI_STRING>::Ptr const& pNameSpace,
        MI_Value<MI_STRING>::Ptr const& pClassName,
        MI_Instance::Ptr const& pInstance) const
    {
        SCX_BOOKEND ("CD_Functor::operator ()");
        int rval = EXIT_SUCCESS;
        MI_Context_Wrapper::PyPtr pyContext (
            MI_Context_Wrapper::createPyPtr (pContext));
        MI_Wrapper<MI_STRING>::PyPtr pyNameSpace (
            MI_Wrapper<MI_STRING>::createPyPtr (pNameSpace));
        MI_Wrapper<MI_STRING>::PyPtr pyClassName (
            MI_Wrapper<MI_STRING>::createPyPtr (pClassName));
        MI_Instance_Wrapper::PyPtr pyInstance (
            MI_Instance_Wrapper::createPyPtr (pInstance));
        if (pyContext && pyNameSpace && pyClassName && pyInstance)
        {
            PyObjPtr pArgs (PyTuple_New (4));
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
                    reinterpret_cast<PyObject*>(pyInstance.get ()));
                PyObjPtr pRval (PyObject_CallObject (
                                    m_pFn.get (), pArgs.get ()));
                if (!pRval)
                {
                    SCX_BOOKEND_PRINT ("Error returned from call");
                    rval = EXIT_FAILURE;
                }
                else
                {
                    if (Py_None == pRval.get ())
                    {
                        SCX_BOOKEND_PRINT ("an object was returned (Py_None)");
                    }
                    else
                    {
                        SCX_BOOKEND_PRINT (
                            "an object was returned (not Py_None)");
                    }
                }
            }
        }
        else
        {
            PyErr_SetString (PyExc_TypeError, "invalid argument");
            rval = EXIT_FAILURE;
        }
        return rval;
    }

private:
    py_ptr<PyObject> const m_pFn;
};


//typedef void (MI_CALL *MI_ProviderFT_EnumerateInstances)(
//    _In_opt_ void* self,
//    _In_ MI_Context* context,
//    _In_z_ const MI_Char* nameSpace,
//    _In_z_ const MI_Char* className,
//    _In_opt_ const MI_PropertySet* propertySet,
//    MI_Boolean keysOnly,
//    _In_opt_ const MI_Filter* filter);
class E_Functor
{
public:
    /*ctor*/ E_Functor (py_ptr<PyObject>const& pFn)
        : m_pFn (pFn)
    {
//        SCX_BOOKEND ("E_Functor::ctor");
    }

    /*dtor*/ ~E_Functor ()
    {
//        SCX_BOOKEND ("E_Functor::dtor");
    }

    int
    operator () (
        MI_Context::Ptr const& pContext,
        MI_Value<MI_STRING>::Ptr const& pNameSpace,
        MI_Value<MI_STRING>::Ptr const& pClassName,
        MI_PropertySet::ConstPtr const& pPropertySet,
        MI_Value<MI_BOOLEAN>::Ptr const& pKeysOnly) const
    {
        SCX_BOOKEND ("E_Functor::operator ()");
        int rval = EXIT_SUCCESS;
        MI_Context_Wrapper::PyPtr pyContext (
            MI_Context_Wrapper::createPyPtr (pContext));
        MI_Wrapper<MI_STRING>::PyPtr pyNameSpace (
            MI_Wrapper<MI_STRING>::createPyPtr (pNameSpace));
        MI_Wrapper<MI_STRING>::PyPtr pyClassName (
            MI_Wrapper<MI_STRING>::createPyPtr (pClassName));
        MI_PropertySet_Wrapper::PyPtr pyPropertySet;
        if (pPropertySet)
        {
            pyPropertySet = MI_PropertySet_Wrapper::createPyPtr (pPropertySet);
        }
        MI_Wrapper<MI_BOOLEAN>::PyPtr pyKeysOnly (
            MI_Wrapper<MI_BOOLEAN>::createPyPtr (pKeysOnly));
        if (pyContext && pyNameSpace && pyClassName && pKeysOnly)
        {
            PyObjPtr pArgs (PyTuple_New (5));
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
                if (pPropertySet)
                {
                    PyTuple_SetItem (
                        pArgs.get (), 3,
                        reinterpret_cast<PyObject*>(pyPropertySet.get ()));
                }
                else
                {
                    Py_INCREF (Py_None);
                    PyTuple_SetItem (pArgs.get (), 3, Py_None);
                }
                PyTuple_SetItem (
                    pArgs.get (), 4,
                    reinterpret_cast<PyObject*>(pyKeysOnly.get ()));
                PyObjPtr pRval (PyObject_CallObject (
                                    m_pFn.get (), pArgs.get ()));
                if (!pRval)
                {
                    SCX_BOOKEND_PRINT ("Error returned from call");
                    rval = EXIT_FAILURE;
                }
                else
                {
                    if (Py_None == pRval.get ())
                    {
                        SCX_BOOKEND_PRINT ("an object was returned (Py_None)");
                    }
                    else
                    {
                        SCX_BOOKEND_PRINT (
                            "an object was returned (not Py_None)");
                    }
                }
            }
        }
        else
        {
            PyErr_SetString (PyExc_TypeError, "invalid argument");
            rval = EXIT_FAILURE;
        }
        return rval;
    }

private:
    py_ptr<PyObject> const m_pFn;
};


typedef util::function_holder<Load_Unload_Functor,
                              int,
                              MI_Module::Ptr const&,
                              MI_Context::Ptr const&> LoadFNHolder_t;


typedef util::function_holder<U_Functor,
                              int,
                              MI_Context::Ptr const&> U_FNHolder_t;


typedef util::function_holder<GM_Functor,
                              int,
                              MI_Context::Ptr const&,
                              MI_Value<MI_STRING>::Ptr const&,
                              MI_Value<MI_STRING>::Ptr const&,
                              MI_Instance::Ptr const&,
                              MI_PropertySet::ConstPtr const&> GM_FNHolder_t;


typedef util::function_holder<CD_Functor,
                              int,
                              MI_Context::Ptr const&,
                              MI_Value<MI_STRING>::Ptr const&,
                              MI_Value<MI_STRING>::Ptr const&,
                              MI_Instance::Ptr const&> CD_FNHolder_t;


typedef util::function_holder<E_Functor,
                              int,
                              MI_Context::Ptr const&,
                              MI_Value<MI_STRING>::Ptr const&,
                              MI_Value<MI_STRING>::Ptr const&,
                              MI_PropertySet::ConstPtr const&,
                              MI_Value<MI_BOOLEAN>::Ptr const&> E_FNHolder_t;


} // namespace scx


//namespace scx
//{




/*static*/ char const MI_FunctionTable_Placeholder::NAME[] =
    "MI_FunctionTable";
/*static*/ char const MI_FunctionTable_Placeholder::OMI_NAME[] =
    "omi.MI_FunctionTable";
/*static*/ char const MI_FunctionTable_Placeholder::DOC[] =
    "omi.MI_FunctionTable utility";
/*static*/ PyTypeObject MI_FunctionTable_Placeholder::s_PyTypeObject = {};


/*static*/ void
MI_FunctionTable_Placeholder::moduleInit (
    PyObject* const pModule)
{
    SCX_BOOKEND ("MI_FunctionTable_Placeholder::moduleInit");
    Zero_PyTypeObject (&s_PyTypeObject);
    s_PyTypeObject.tp_name = OMI_NAME;
    s_PyTypeObject.tp_basicsize = sizeof (MI_FunctionTable_Placeholder);
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
MI_FunctionTable_Placeholder::dealloc (
    PyObject* pObj)
{
    SCX_BOOKEND ("MI_FunctionTable_Placeholder::dealloc");
    if (NULL != pObj)
    {
        MI_FunctionTable_Placeholder* pDecl =
            reinterpret_cast<MI_FunctionTable_Placeholder*>(pObj);
        pDecl->~MI_FunctionTable_Placeholder ();
        pDecl->ob_type->tp_free (pObj);
    }
}


/*static*/ PyTypeObject const*
MI_FunctionTable_Placeholder::getPyTypeObject ()
{
    return &s_PyTypeObject;
}


PyObject*
MI_FunctionTable_Placeholder::newObj (
    PyTypeObject* pType,
    PyObject* args,
    PyObject* keywords)
{
    SCX_BOOKEND ("MI_FunctionTable_Placeholder::newObj");
    PyObject* pObj = pType->tp_alloc (pType, 0);
    return pObj;
}


int
MI_FunctionTable_Placeholder::init (
    PyObject* pSelf,
    PyObject* args,
    PyObject* keywords)
{
    SCX_BOOKEND ("MI_FunctionTable_Placeholder::init");
    char* KEYWORDS[] = {
        "Load",
        "Unload",
        "GetInstance",
        "EnumerateInstances",
        "CreateInstance",
        "ModifyInstance",
        "DeleteInstance",
        "AssociatorInstances",
        "ReferenceInstances",
        "EnableIndications",
        "DisableIndications",
        "Subscribe",
        "Unsubscribe",
        "Invoke",
        NULL
    };
    int rval = 0;
    PyObject* pLoadObj = NULL;
    PyObject* pUnloadObj = NULL;
    PyObject* pGetInstanceObj = NULL;
    PyObject* pEnumerateInstancesObj = NULL;
    PyObject* pCreateInstanceObj = NULL;
    PyObject* pModifyInstanceObj = NULL;
    PyObject* pDeleteInstanceObj = NULL;
    PyObject* pAssociatorInstancesObj = NULL;
    PyObject* pReferenceInstancesObj = NULL;
    PyObject* pEnableIndicationsObj = NULL;
    PyObject* pDisableIndicationsObj = NULL;
    PyObject* pSubscribeObj = NULL;
    PyObject* pUnsubscribeObj = NULL;
    PyObject* pInvokeObj = NULL;

    if (PyArg_ParseTupleAndKeywords (
            args, keywords, "OOOOOOO|OOOOOOO", KEYWORDS, &pLoadObj, &pUnloadObj,
            &pGetInstanceObj, &pEnumerateInstancesObj, &pCreateInstanceObj,
            &pModifyInstanceObj, &pDeleteInstanceObj, &pAssociatorInstancesObj,
            &pReferenceInstancesObj, &pEnableIndicationsObj,
            &pDisableIndicationsObj, &pSubscribeObj, &pUnsubscribeObj,
            &pInvokeObj))
    {
        SCX_BOOKEND_PRINT ("ParseTupleAndKeywords succeeded");
//        typedef MI_Type<MI_STRING>::type_t MI_String_t;
        MI_Value<MI_STRING>::Ptr pLoadName;
        rval = to_MI_Value_or_NULL<MI_STRING> (pLoadObj, &pLoadName);
        if (PY_FAILURE == rval)
        {
            SCX_BOOKEND_PRINT ("pLoadName convert failed");
        }
        MI_Value<MI_STRING>::Ptr pUnloadName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (pUnloadObj, &pUnloadName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pUnloadName convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pGetInstanceName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (
                pGetInstanceObj, &pGetInstanceName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pGetInstanceName convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pEnumerateInstancesName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (
                pEnumerateInstancesObj, &pEnumerateInstancesName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pEnumerateInstancesName convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pCreateInstanceName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (
                pCreateInstanceObj, &pCreateInstanceName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pCreateInstanceName convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pModifyInstanceName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (
                pModifyInstanceObj, &pModifyInstanceName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pModifyInstanceName convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pDeleteInstanceName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (
                pDeleteInstanceObj, &pDeleteInstanceName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pDeleteInstanceName convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pAssociatorInstancesName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (
                pAssociatorInstancesObj, &pAssociatorInstancesName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pAssociatorInstancesName convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pReferenceInstancesName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (
                pReferenceInstancesObj, &pReferenceInstancesName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pReferenceInstancesName convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pEnableIndicationsName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (
                pEnableIndicationsObj, &pEnableIndicationsName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pEnableIndicationsName convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pDisableIndicationsName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (
                pDisableIndicationsObj, &pDisableIndicationsName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pDisableIndicationsName convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pSubscribeName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (
                pSubscribeObj, &pSubscribeName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pSubscribeName convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pUnsubscribeName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (
                pUnsubscribeObj, &pUnsubscribeName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pUnsubscribeName convert failed");
            }
        }
        MI_Value<MI_STRING>::Ptr pInvokeName;
        if (PY_SUCCESS == rval)
        {
            rval = to_MI_Value_or_NULL<MI_STRING> (pInvokeObj, &pInvokeName);
            if (PY_FAILURE == rval)
            {
                SCX_BOOKEND_PRINT ("pInvokeName convert failed");
            }
        }
        if (PY_SUCCESS == rval)
        {
            SCX_BOOKEND_PRINT ("initialization succeeded");
//            MI_Value<MI_STRING>::ConstPtr pLoadName (
//                new MI_Value<MI_STRING> (loadName));
//            MI_Value<MI_STRING>::ConstPtr pUnloadName (
//                new MI_Value<MI_STRING> (unloadName));
//            MI_Value<MI_STRING>::ConstPtr pGetInstanceName (
//                new MI_Value<MI_STRING> (getInstanceName));
//            MI_Value<MI_STRING>::ConstPtr pEnumerateInstancesName (
//                new MI_Value<MI_STRING> (enumerateInstancesName));
//            MI_Value<MI_STRING>::ConstPtr pCreateInstanceName (
//                new MI_Value<MI_STRING> (createInstanceName));
//            MI_Value<MI_STRING>::ConstPtr pModifyInstanceName (
//                new MI_Value<MI_STRING> (modifyInstanceName));
//            MI_Value<MI_STRING>::ConstPtr pDeleteInstanceName (
//                new MI_Value<MI_STRING> (deleteInstanceName));
//            MI_Value<MI_STRING>::ConstPtr pAssociatorInstancesName (
//                new MI_Value<MI_STRING> (associatorInstancesName));
//            MI_Value<MI_STRING>::ConstPtr pReferenceInstancesName (
//                new MI_Value<MI_STRING> (referenceInstancesName));
//            MI_Value<MI_STRING>::ConstPtr pEnableIndicationsName (
//                new MI_Value<MI_STRING> (enableIndicationsName));
//            MI_Value<MI_STRING>::ConstPtr pDisableIndicationsName (
//                new MI_Value<MI_STRING> (disableIndicationsName));
//            MI_Value<MI_STRING>::ConstPtr pSubscribeName (
//                new MI_Value<MI_STRING> (subscribeName));
//            MI_Value<MI_STRING>::ConstPtr pUnsubscribeName (
//                new MI_Value<MI_STRING> (unsubscribeName));
//            MI_Value<MI_STRING>::ConstPtr pInvokeName (
//                new MI_Value<MI_STRING> (invokeName));
            new (pSelf) MI_FunctionTable_Placeholder (
                pLoadName, pUnloadName, pGetInstanceName,
                pEnumerateInstancesName, pCreateInstanceName,
                pModifyInstanceName, pDeleteInstanceName,
                pAssociatorInstancesName, pReferenceInstancesName,
                pEnableIndicationsName, pDisableIndicationsName,
                pSubscribeName, pUnsubscribeName, pInvokeName);
        }
        else
        {
            SCX_BOOKEND_PRINT ("initialization failed");
        }
    }
    else
    {
        SCX_BOOKEND_PRINT ("MI_FunctionTable_Placeholder_init parse args failed");
    }
    return rval;
}


/*ctor*/
MI_FunctionTable_Placeholder::MI_FunctionTable_Placeholder (
    MI_Value<MI_STRING>::ConstPtr const& pLoadName,
    MI_Value<MI_STRING>::ConstPtr const& pUnloadName,
    MI_Value<MI_STRING>::ConstPtr const& pGetInstanceName,
    MI_Value<MI_STRING>::ConstPtr const& pEnumerateInstancesName,
    MI_Value<MI_STRING>::ConstPtr const& pCreateInstanceName,
    MI_Value<MI_STRING>::ConstPtr const& pModifyInstanceName,
    MI_Value<MI_STRING>::ConstPtr const& pDeleteInstanceName,
    MI_Value<MI_STRING>::ConstPtr const& pAssociatorInstancesName,
    MI_Value<MI_STRING>::ConstPtr const& pReferenceInstancesName,
    MI_Value<MI_STRING>::ConstPtr const& pEnableIndicationsName,
    MI_Value<MI_STRING>::ConstPtr const& pDisableIndicationsName,
    MI_Value<MI_STRING>::ConstPtr const& pSubscribeName,
    MI_Value<MI_STRING>::ConstPtr const& pUnsubscribeName,
    MI_Value<MI_STRING>::ConstPtr const& pInvokeName)
    : m_pLoadName (pLoadName)
    , m_pUnloadName (pUnloadName)
    , m_pGetInstanceName (pGetInstanceName)
    , m_pEnumerateInstancesName (pEnumerateInstancesName)
    , m_pCreateInstanceName (pCreateInstanceName)
    , m_pModifyInstanceName (pModifyInstanceName)
    , m_pDeleteInstanceName (pDeleteInstanceName)
    , m_pAssociatorInstancesName (pAssociatorInstancesName)
    , m_pReferenceInstancesName (pReferenceInstancesName)
    , m_pEnableIndicationsName (pEnableIndicationsName)
    , m_pDisableIndicationsName (pDisableIndicationsName)
    , m_pSubscribeName (pSubscribeName)
    , m_pUnsubscribeName (pUnsubscribeName)
    , m_pInvokeName (pInvokeName)
{
    SCX_BOOKEND ("MI_FunctionTable_Placeholder::ctor");
    
}

    
/*dtor*/
MI_FunctionTable_Placeholder::~MI_FunctionTable_Placeholder ()
{
    SCX_BOOKEND ("MI_FunctionTable_Placeholder::dtor");
}


MI_FunctionTable::Ptr
MI_FunctionTable_Placeholder::createFunctionTable (
    PyObject* const pPyModule) const
{
    SCX_BOOKEND ("MI_FunctionTable_Placeholder::createFunctionTable");
    assert (0 != pPyModule);

    MI_FunctionTable::LoadFn::Ptr pLoadFn;
    MI_FunctionTable::UnloadFn::Ptr pUnloadFn;
    MI_FunctionTable::GetInstanceFn::Ptr pGetInstanceFn;
    MI_FunctionTable::EnumerateInstancesFn::Ptr pEnumerateInstancesFn;
    MI_FunctionTable::CreateInstanceFn::Ptr pCreateInstanceFn;
    MI_FunctionTable::ModifyInstanceFn::Ptr pModifyInstanceFn;
    MI_FunctionTable::DeleteInstanceFn::Ptr pDeleteInstanceFn;

    MI_FunctionTable::Ptr pFT;

    PyObject* pModuleDict = PyModule_GetDict (pPyModule);
    if (pModuleDict)
    {
        PyObject* pLoadObj = PyDict_GetItemString (
            pModuleDict, m_pLoadName->getValue ().c_str ());
        if (PyCallable_Check (pLoadObj))
        {
            pLoadFn = new LoadFNHolder_t (Load_Unload_Functor (
                    py_ptr<PyObject> (pLoadObj, DO_NOT_INC_REF)));

        }
        PyObject* pUnloadObj = PyDict_GetItemString (
            pModuleDict, m_pUnloadName->getValue ().c_str ());
        if (PyCallable_Check (pUnloadObj))
        {
            pUnloadFn = new U_FNHolder_t (U_Functor (
                    py_ptr<PyObject> (pUnloadObj, DO_NOT_INC_REF)));
        }
        PyObject* pGetInstanceObj = PyDict_GetItemString (
            pModuleDict, m_pGetInstanceName->getValue ().c_str ());
        if (PyCallable_Check (pGetInstanceObj))
        {
            pGetInstanceFn = new GM_FNHolder_t (GM_Functor (
                    py_ptr<PyObject> (pGetInstanceObj, DO_NOT_INC_REF)));
        }
        PyObject* pEnumerateInstancesObj = PyDict_GetItemString (
            pModuleDict, m_pEnumerateInstancesName->getValue ().c_str ());
        if (PyCallable_Check (pEnumerateInstancesObj))
        {
            pEnumerateInstancesFn = new E_FNHolder_t (E_Functor (
                    py_ptr<PyObject> (pEnumerateInstancesObj, DO_NOT_INC_REF)));
        }
        PyObject* pCreateInstanceObj = PyDict_GetItemString (
            pModuleDict, m_pCreateInstanceName->getValue ().c_str ());
        if (PyCallable_Check (pCreateInstanceObj))
        {
            pCreateInstanceFn = new CD_FNHolder_t (CD_Functor (
                    py_ptr<PyObject> (pCreateInstanceObj, DO_NOT_INC_REF)));
        }
        PyObject* pModifyInstanceObj = PyDict_GetItemString (
            pModuleDict, m_pModifyInstanceName->getValue ().c_str ());
        if (PyCallable_Check (pModifyInstanceObj))
        {
            pModifyInstanceFn = new GM_FNHolder_t (GM_Functor (
                    py_ptr<PyObject> (pModifyInstanceObj, DO_NOT_INC_REF)));
        }
        PyObject* pDeleteInstanceObj = PyDict_GetItemString (
            pModuleDict, m_pDeleteInstanceName->getValue ().c_str ());
        if (PyCallable_Check (pDeleteInstanceObj))
        {
            pDeleteInstanceFn = new CD_FNHolder_t (CD_Functor (
                    py_ptr<PyObject> (pDeleteInstanceObj, DO_NOT_INC_REF)));
        }
    }

    if (pLoadFn && pUnloadFn && pGetInstanceFn && pEnumerateInstancesFn &&
        pCreateInstanceFn && pModifyInstanceFn && pDeleteInstanceFn)
    {
        pFT = new MI_FunctionTable (
            pLoadFn, pUnloadFn, pGetInstanceFn, pEnumerateInstancesFn,
            pCreateInstanceFn, pModifyInstanceFn, pDeleteInstanceFn);
    }
    
    return pFT;
}


//} // namespace scx
