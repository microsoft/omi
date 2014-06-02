/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

#include "context.h"
#include <base/miextras.h>

MI_BEGIN_NAMESPACE

Context::Context(MI_Context* context) : 
    m_context(context),
    m_result(0)
{
}

Context::Context(MI_Context* context, MI_Result* result) : 
    m_context(context), 
    m_result(result)
{
}

/* ATTN: is this safe? */
Context::Context(const Context& x)
{
    m_context = x.m_context;
    m_result = x.m_result;
}

MI_Result Context::Post(const Instance& instance)
{
    return MI_PostInstance(m_context, instance.m_instance);
}

MI_Result Context::Post(MI_Result result)
{
    if (NULL != m_result)
    {
        *m_result = result;
        return MI_RESULT_OK;
    }
    else
    {
        MI_Result r = MI_PostResult(m_context, result);

        // invalidate context, since PostResult must be the last operation on 
        // MI_Context
        m_context = 0;

        return r;
    }
}

MI_Result Context::Post(
    const Instance& indication, 
    MI_Uint32 subscriptionIDCount,
    const String& bookmark)
{
    return MI_PostIndication(m_context, indication.m_instance, 
        subscriptionIDCount, bookmark.Str());
}

MI_Result Context::Post(MI_Result result, const String& message)
{
    if (NULL != m_result)
    {
        *m_result = result;
        return MI_RESULT_OK;
    }

    MI_Result r = MI_PostResultWithMessage(m_context, result, message.Str());

    // invalidate context, since PostResult must be the last operation on 
    // MI_Context
    m_context = 0;

    return r;
}

MI_Result Context::Post(MI_Result result, const CIM_Error_Class& instance)
{
    if (NULL != m_result)
    {
        *m_result = result;
        return MI_RESULT_OK;
    }

    const Instance* tmp = reinterpret_cast<const Instance*>(&instance);
    MI_Result r = MI_PostResultWithError(m_context, result, tmp->m_instance);

    // invalidate context, since PostResult must be the last operation on 
    // MI_Context
    m_context = 0;

    return r;
}

MI_Result Context::RequestUnload()
{
    return MI_RequestUnload(m_context);
}

MI_Result Context::RefuseUnload()
{
    return MI_RefuseUnload(m_context);
}

MI_END_NAMESPACE
