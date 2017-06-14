// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT license.
#include "mi_context.hpp"


#include "debug_tags.hpp"
#include "mi_schema.hpp"


#include <cassert>


namespace scx
{


/*ctor*/
MI_Context::MI_Context (
    socket_wrapper::Ptr const& pSocket,
    MI_SchemaDecl::ConstPtr const& pSchemaDecl)
    : m_pSocket (pSocket)
    , m_pSchemaDecl (pSchemaDecl)
    , m_ResultSent (false)
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
    int rval = socket_wrapper::SEND_FAILED;
    if (!m_ResultSent)
    {
        rval = protocol::send_opcode (protocol::POST_RESULT, *m_pSocket);
        if (socket_wrapper::SUCCESS == rval)
        {
            rval = protocol::send<MI_Uint32> (result, *m_pSocket);
            if (socket_wrapper::SUCCESS == rval)
            {
                m_ResultSent = true;
            }
        }
    }
    return rval;
}


int
MI_Context::postInstance (
    util::internal_counted_ptr<MI_Instance const> const& pInstance)
{
    SCX_BOOKEND ("MI_Context::postInstance");
    assert (NULL != pInstance.get ());
    int rval = socket_wrapper::SEND_FAILED;
    if (!m_ResultSent &&
        pInstance)
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
        MI_ClassDecl::ConstPtr pClassDecl (
            m_pSchemaDecl->getClassDecl (pClassName));
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


int
MI_Context::newParameters (
    MI_Value<MI_STRING>::ConstPtr const& pClassName,
    MI_Value<MI_STRING>::ConstPtr const& pMethodName,
    MI_Instance::Ptr* ppInstanceOut)
{
    SCX_BOOKEND ("MI_Context::newParameters");
    assert (ppInstanceOut);
    int rval = EXIT_FAILURE;
    if (pClassName)
    {
        MI_ClassDecl::ConstPtr pClassDecl (
            m_pSchemaDecl->getClassDecl (pClassName));
        if (pClassDecl)
        {
            MI_MethodDecl::ConstPtr pMethodDecl (
                pClassDecl->getMethodDecl (pMethodName->getValue ()));
            if (pMethodDecl)
            {
                // correct: create the instance
                *ppInstanceOut = new MI_Instance (pMethodDecl);
                rval = EXIT_SUCCESS;
            }
            else
            {
                // error: the method doesn't exist
            }
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
