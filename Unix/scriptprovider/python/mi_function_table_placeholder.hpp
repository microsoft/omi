#ifndef INCLUDED_MI_FUNCTION_TABLE_PLACEHOLDER_HPP
#define INCLUDED_MI_FUNCTION_TABLE_PLACEHOLDER_HPP


#include "Python.h"


#include "py_ptr.hpp"
#include "mi_value.hpp"


namespace scx
{


class MI_FunctionTable;


class MI_FunctionTable_Placeholder
{
public:
    PyObject_HEAD

    typedef py_ptr<MI_FunctionTable_Placeholder const> ConstPtr;

    static void moduleInit (PyObject* const pModule);

    static void dealloc (PyObject* pObj);
    static PyObject* newObj (PyTypeObject* pType,
                             PyObject* args,
                             PyObject* keywords);
    static int init (PyObject* pSelf, PyObject* args, PyObject* keywords);

    static PyTypeObject const* getPyTypeObject ();

    /*ctor*/ MI_FunctionTable_Placeholder (
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
        MI_Value<MI_STRING>::ConstPtr const& pInvokeName);

    /*dtor*/ ~MI_FunctionTable_Placeholder ();

    util::internal_counted_ptr<MI_FunctionTable> createFunctionTable (
        PyObject* const pPyModule) const;

private:
    static char const NAME[];
    static char const OMI_NAME[];
    static char const DOC[];
    static PyTypeObject s_PyTypeObject;

    MI_Value<MI_STRING>::ConstPtr const m_pLoadName;
    MI_Value<MI_STRING>::ConstPtr const m_pUnloadName;
    MI_Value<MI_STRING>::ConstPtr const m_pGetInstanceName;
    MI_Value<MI_STRING>::ConstPtr const m_pEnumerateInstancesName;
    MI_Value<MI_STRING>::ConstPtr const m_pCreateInstanceName;
    MI_Value<MI_STRING>::ConstPtr const m_pModifyInstanceName;
    MI_Value<MI_STRING>::ConstPtr const m_pDeleteInstanceName;
    MI_Value<MI_STRING>::ConstPtr const m_pAssociatorInstancesName;
    MI_Value<MI_STRING>::ConstPtr const m_pReferenceInstancesName;
    MI_Value<MI_STRING>::ConstPtr const m_pEnableIndicationsName;
    MI_Value<MI_STRING>::ConstPtr const m_pDisableIndicationsName;
    MI_Value<MI_STRING>::ConstPtr const m_pSubscribeName;
    MI_Value<MI_STRING>::ConstPtr const m_pUnsubscribeName;
    MI_Value<MI_STRING>::ConstPtr const m_pInvokeName;
};


} // namespace scx


#endif // INLCUDED_MI_FUNCTION_TABLE_PLACEHOLDER_HPP
