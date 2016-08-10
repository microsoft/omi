/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _micxx_context_h
#define _micxx_context_h

#include <MI.h>
#include "linkage.h"
#include "instance.h"

MI_BEGIN_NAMESPACE

class CIM_Error_Class;

class MICXX_LINKAGE Context
{
public:

    Context(
        MI_Context* context);

    Context(
        MI_Context* context,
        MI_Result* result);

    Context(
        const Context& x);

    MI_Result Post(
        const Instance& instance);

    MI_Result Post(
        const Instance& indication, 
        MI_Uint32 subscriptionIDCount,
        const String& bookmark);

    MI_Result Post(MI_Result result);

    MI_Result Post(
        MI_Result result, 
        const String& message);

    MI_Result Post(
        MI_Result result, 
        const CIM_Error_Class& instance);

    MI_Result RequestUnload();

    MI_Result RefuseUnload();

    MI_Context* context() { return m_context; }

private:

    Context();
    Context& operator=(const Context&);

    MI_Context* m_context;
    MI_Result*  m_result;
};

MI_END_NAMESPACE

#endif /* _micxx_context_h */
