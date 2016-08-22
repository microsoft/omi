#include "mi_context.hpp"


#include "debug_tags.hpp"
#include "mi_schema.hpp"


#include <cassert>


namespace scx
{


//class MI_Instance : public util::ref_counted_obj
//{
//};


//}

//using namespace scx;


/*ctor*/
MI_Context::MI_Context (
    socket_wrapper::Ptr const& pSocket,
    MI_SchemaDecl::ConstPtr const& pSchemaDecl)
    : m_pSocket (pSocket)
    , m_pSchemaDecl (pSchemaDecl)
{
    SCX_BOOKEND ("MI_Context::ctor");
}


/*dtor*/
MI_Context::~MI_Context ()
{
    SCX_BOOKEND ("MI_Context::dtor");
}


int
MI_Context::postResult (
    MI_Result const& result)
{
    SCX_BOOKEND ("MI_Context::postResult");
    int rval = protocol::send_opcode (protocol::POST_RESULT, *m_pSocket);
    if (socket_wrapper::SUCCESS == rval)
    {
        rval = protocol::send<MI_Uint32> (result, *m_pSocket);
    }
    return rval;
}


int
MI_Context::postInstance (
    util::internal_counted_ptr<MI_Instance const> const& pInstance)
{
    SCX_BOOKEND ("MI_Context::postInstance");
    assert (NULL != pInstance.get ());
    int rval = socket_wrapper::SUCCESS;
    if (pInstance)
    {
        rval = protocol::send_opcode (protocol::POST_INSTANCE, *m_pSocket);
        if (socket_wrapper::SUCCESS == rval)
        {
            rval = pInstance->send (*m_pSocket);
        }
    }
    return rval;
}


int
MI_Context::newInstance (
    MI_Value<MI_STRING>::ConstPtr const& pClassName,
    MI_Instance::Ptr* ppInstanceOut)
{
    SCX_BOOKEND ("MI_Context::newInstance");
    assert (ppInstanceOut);
    int rval = EXIT_FAILURE;

    if (pClassName)
    {
        MI_ClassDecl::ConstPtr pClassDecl =
            m_pSchemaDecl->getClassDecl (pClassName);
        if (pClassDecl)
        {
            // correct: create the instance
            *ppInstanceOut = new MI_Instance (pClassDecl);
            rval = EXIT_SUCCESS;
        }
        else
        {
            // error: the class doesn't exist
        }
    }
    else
    {
        // error: pClassName is NULL
    }

    return rval;
}


} // namespace scx
