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
#include "X_Dog_Class_Provider.h"

MI_BEGIN_NAMESPACE

X_Dog_Class_Provider::X_Dog_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

X_Dog_Class_Provider::~X_Dog_Class_Provider()
{
}

void X_Dog_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_Dog_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_Dog_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_Dog_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const X_Dog_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_Dog_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const X_Dog_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_Dog_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const X_Dog_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_Dog_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const X_Dog_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_Dog_Class_Provider::Invoke_Fight(
    Context& context,
    const String& nameSpace,
    const X_Dog_Class& instanceName,
    const X_Dog_Fight_Class& in)
{
    X_Dog_Fight_Class out;

    out.MIReturn_value(0);
    out.CatsOut_value(in.CatsIn_value());
    context.Post(out);
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
