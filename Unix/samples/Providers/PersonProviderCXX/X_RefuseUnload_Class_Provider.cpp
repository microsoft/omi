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
#include "X_RefuseUnload_Class_Provider.h"

MI_BEGIN_NAMESPACE

X_RefuseUnload_Class_Provider::X_RefuseUnload_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

X_RefuseUnload_Class_Provider::~X_RefuseUnload_Class_Provider()
{
}

void X_RefuseUnload_Class_Provider::Load(
        Context& context)
{
    context.RefuseUnload();
    context.Post(MI_RESULT_OK);
}

void X_RefuseUnload_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_RefuseUnload_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_RefuseUnload_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const X_RefuseUnload_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_RefuseUnload_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const X_RefuseUnload_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_RefuseUnload_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const X_RefuseUnload_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_RefuseUnload_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const X_RefuseUnload_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_RefuseUnload_Class_Provider::Invoke_RequestUnload(
    Context& context,
    const String& nameSpace,
    const X_RefuseUnload_Class& instance,
    const X_RefuseUnload_RequestUnload_Class& in)
{
    context.RequestUnload();
    context.Post(MI_RESULT_OK);
}


MI_END_NAMESPACE
