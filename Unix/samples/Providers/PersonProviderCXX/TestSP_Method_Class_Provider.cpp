/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#include <MI.h>
#include "TestSP_Method_Class_Provider.h"

MI_BEGIN_NAMESPACE

TestSP_Method_Class_Provider::TestSP_Method_Class_Provider(
        Module* module) :
    m_Module(module)
{
}

TestSP_Method_Class_Provider::~TestSP_Method_Class_Provider()
{
}

void TestSP_Method_Class_Provider::EnumerateInstances(
    Context&  context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void TestSP_Method_Class_Provider::GetInstance(
    Context&  context,
    const String& nameSpace,
    const TestSP_Method_Class& instance_ref,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void TestSP_Method_Class_Provider::CreateInstance(
    Context&  context,
    const String& nameSpace,
    const TestSP_Method_Class& new_instance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void TestSP_Method_Class_Provider::ModifyInstance(
    Context&  context,
    const String& nameSpace,
    const TestSP_Method_Class& new_instance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void TestSP_Method_Class_Provider::DeleteInstance(
    Context&  context,
    const String& nameSpace,
    const TestSP_Method_Class& instance_ref)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void TestSP_Method_Class_Provider::Invoke_MyFunc(
    Context&  context,
    const String& nameSpace,
    const TestSP_Method_Class& instance,
    const TestSP_Method_MyFunc_Class& in_param )
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

MI_END_NAMESPACE
MI_BEGIN_NAMESPACE
void TestSP_Method_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void TestSP_Method_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
