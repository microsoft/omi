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
#include "Base_Class_Provider.h"

MI_BEGIN_NAMESPACE

Base_Class_Provider::Base_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

Base_Class_Provider::~Base_Class_Provider()
{
}

void Base_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Base_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const Base_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Base_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const Base_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Base_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const Base_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Base_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const Base_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Base_Class_Provider::Invoke_Foo(
    Context& context,
    const String& nameSpace,
    const Base_Class& instance,
    const Base_Foo_Class& in)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
MI_BEGIN_NAMESPACE
void Base_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Base_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
