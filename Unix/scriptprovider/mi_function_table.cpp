#include "mi_function_table.hpp"


#include "mi_schema.hpp"
#include "mi_context.hpp"
#include "mi_module.hpp"
#include "shared_protocol.hpp"


#include <cassert>


namespace
{


MI_Char const* const LOAD = MI_T ("Load");
MI_Char const* const UNLOAD = MI_T ("Unload");
MI_Char const* const GET_INSTANCE = MI_T ("GetInstance");
MI_Char const* const ENUMERATE_INSTANCES = MI_T ("EnumerateInstances");
MI_Char const* const CREATE_INSTANCE = MI_T ("CreateInstance");
MI_Char const* const MODIFY_INSTANCE = MI_T ("ModifyInstance");
MI_Char const* const DELETE_INSTANCE = MI_T ("DeleteInstance");
MI_Char const* const ASSOCIATOR_INSTANCES = MI_T ("AssociatorInstances");
MI_Char const* const REFERENCE_INSTANCES = MI_T ("ReferenceInstances");
MI_Char const* const ENABLE_INDICATIONS = MI_T ("EnableIndications");
MI_Char const* const DISABLE_INDICATIONS = MI_T ("DisableIndications");
MI_Char const* const SUBSCRIBE = MI_T ("Subscribe");
MI_Char const* const UNSUBSCRIBE = MI_T ("Unsubscribe");
MI_Char const* const INVOKE = MI_T ("Invoke");
MI_Char const* const NO_FUNCTION = 0;

}


namespace scx
{


/*ctor*/
MI_FunctionTable::MI_FunctionTable (
    LoadFn::Ptr const& pLoad,
    UnloadFn::Ptr const& pUnload,
    GetInstanceFn::Ptr const& pGetInstance,
    EnumerateInstancesFn::Ptr const& pEnumerateInstances,
    CreateInstanceFn::Ptr const& pCreateInstance,
    ModifyInstanceFn::Ptr const& pModifyInstance,
    DeleteInstanceFn::Ptr const& pDeleteInstance,
    InvokeFn::Ptr const& pInvoke)
    : m_pLoad (pLoad)
      , m_pUnload (pUnload)
      , m_pGetInstance (pGetInstance)
      , m_pEnumerateInstances (pEnumerateInstances)
      , m_pCreateInstance (pCreateInstance)
      , m_pModifyInstance (pModifyInstance)
      , m_pDeleteInstance (pDeleteInstance)
      , m_pInvoke (pInvoke)
{
    SCX_BOOKEND ("MI_FunctionTable::ctor");
}


/*dtor*/
MI_FunctionTable::~MI_FunctionTable ()
{
    SCX_BOOKEND ("MI_FunctionTable::dtor");
}


int
MI_FunctionTable::Load (
    MI_Module::Ptr const& pModule,
    MI_Context::Ptr const& pContext) const
{
    SCX_BOOKEND ("MI_FunctionTable::Load");
    assert (m_pLoad);
    return m_pLoad->fn (pModule, pContext);
}


int
MI_FunctionTable::Unload (
    MI_Context::Ptr const& pContext) const
{
    SCX_BOOKEND ("MI_FunctionTable::Unload");
    assert (m_pUnload);
    return m_pUnload->fn (pContext);
}


int
MI_FunctionTable::GetInstance (
    MI_Context::Ptr const& pContext,
    MI_Value<MI_STRING>::Ptr const& pNameSpace,
    MI_Value<MI_STRING>::Ptr const& pClassName,
    MI_Instance::Ptr const& pInstanceName,
    MI_PropertySet::ConstPtr const& pPropertySet) const
{
    SCX_BOOKEND ("MI_FunctionTable::GetInstance");
    assert (m_pGetInstance);
    return m_pGetInstance->fn (
        pContext, pNameSpace, pClassName, pInstanceName,pPropertySet);
}


int
MI_FunctionTable::EnumerateInstances (
    MI_Context::Ptr const& pContext,
    MI_Value<MI_STRING>::Ptr const& pNameSpace,
    MI_Value<MI_STRING>::Ptr const& pClassName,
    MI_PropertySet::ConstPtr const& pPropertySet,
    MI_Value<MI_BOOLEAN>::Ptr const& pKeysOnly) const
{
    SCX_BOOKEND ("MI_FunctionTable::EnumerateInstances");
    std::ostringstream strm;
    strm << "namespace: ";
    if (pNameSpace)
    {
        strm << '\"' << pNameSpace->getValue () << '\"';
    }
    else
    {
        strm << "NULL";
    }
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();

    strm << "classname: ";
    if (pClassName)
    {
        strm << '\"' << pClassName->getValue () << '\"';
    }
    else
    {
        strm << "NULL";
    }
    SCX_BOOKEND_PRINT (strm.str ());

    strm.str ("");
    strm.clear ();
    strm << "pPropertySet: is ";
    if (pPropertySet)
    {
        strm << "NOT NULL";
    }
    else
    {
        strm << "NULL";
    }
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();

    strm.str ("");
    strm.clear ();
    strm << "pKeysOnly: ";
    if (pPropertySet)
    {
        strm << (pKeysOnly->getValue () ? "TRUE" : "FALSE");
    }
    else
    {
        strm << "NULL";
    }
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();

    strm << "m_pEnumerateInstances: ";
    if (m_pEnumerateInstances)
    {
        strm << "is NOT NULL";
    }
    else
    {
        strm << "is NULL";
    }
    SCX_BOOKEND_PRINT (strm.str ());
    strm.str ("");
    strm.clear ();

    assert (m_pEnumerateInstances);
    return m_pEnumerateInstances->fn (
        pContext, pNameSpace, pClassName, pPropertySet, pKeysOnly);
}


int
MI_FunctionTable::CreateInstance (
    MI_Context::Ptr const& pContext,
    MI_Value<MI_STRING>::Ptr const& pNameSpace,
    MI_Value<MI_STRING>::Ptr const& pClassName,
    MI_Instance::Ptr const& pNewInstance) const
{
    SCX_BOOKEND ("MI_FunctionTable::CreateInstance");
    assert (m_pCreateInstance);
    return m_pCreateInstance->fn (
        pContext, pNameSpace, pClassName, pNewInstance);
}


int
MI_FunctionTable::ModifyInstance (
    MI_Context::Ptr const& pContext,
    MI_Value<MI_STRING>::Ptr const& pNameSpace,
    MI_Value<MI_STRING>::Ptr const& pClassName,
    MI_Instance::Ptr const& pModifiedInstance,
    MI_PropertySet::ConstPtr const& pPropertySet) const
{
    SCX_BOOKEND ("MI_FunctionTable::ModifyInstance");
    assert (m_pModifyInstance);
    return m_pModifyInstance->fn (
        pContext, pNameSpace, pClassName, pModifiedInstance, pPropertySet);
}


int
MI_FunctionTable::DeleteInstance (
    MI_Context::Ptr const& pContext,
    MI_Value<MI_STRING>::Ptr const& pNameSpace,
    MI_Value<MI_STRING>::Ptr const& pClassName,
    MI_Instance::Ptr const& pInstanceName) const
{
    SCX_BOOKEND ("MI_FunctionTable::DeleteInstance");
    assert (m_pDeleteInstance);
    return m_pDeleteInstance->fn (pContext, pNameSpace, pClassName, pInstanceName);
}


int
MI_FunctionTable::Invoke (
    MI_Context::Ptr const& pContext,
    MI_Value<MI_STRING>::Ptr const& pNameSpace,
    MI_Value<MI_STRING>::Ptr const& pClassName,
    MI_Value<MI_STRING>::Ptr const& pMethodName,
    MI_Instance::Ptr const& pInstanceName,
    MI_Instance::Ptr const& pInputParameters) const
{
    SCX_BOOKEND ("MI_FunctionTable::Invoke");
    return m_pInvoke->fn (pContext, pNameSpace, pClassName, pMethodName,
                          pInstanceName, pInputParameters);
}


int
MI_FunctionTable::send (
    socket_wrapper& sock) const
{
    SCX_BOOKEND ("MI_FunctionTable::send");
    int rval = protocol::send (LOAD, sock);
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = protocol::send (UNLOAD, sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = protocol::send (GET_INSTANCE, sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = protocol::send (ENUMERATE_INSTANCES, sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = protocol::send (CREATE_INSTANCE, sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = protocol::send (MODIFY_INSTANCE, sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = protocol::send (DELETE_INSTANCE, sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = protocol::send (NO_FUNCTION, sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = protocol::send (NO_FUNCTION, sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = protocol::send (NO_FUNCTION, sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = protocol::send (NO_FUNCTION, sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = protocol::send (NO_FUNCTION, sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = protocol::send (NO_FUNCTION, sock);
    }
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = protocol::send (INVOKE, sock);
    }
    return rval;
}


} // namespace scx
