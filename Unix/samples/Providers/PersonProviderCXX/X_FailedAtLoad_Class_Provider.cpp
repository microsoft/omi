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
#include "X_FailedAtLoad_Class_Provider.h"
#include <assert.h>

MI_BEGIN_NAMESPACE

X_FailedAtLoad_Class_Provider::X_FailedAtLoad_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

X_FailedAtLoad_Class_Provider::~X_FailedAtLoad_Class_Provider()
{
}

void X_FailedAtLoad_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_FAILED);
}

void X_FailedAtLoad_Class_Provider::Unload(
        Context& context)
{
    assert("since load returned an error, this function should never be called!" && NULL);
    context.Post(MI_RESULT_OK);
}

void X_FailedAtLoad_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    assert("since load returned an error, this function should never be called!" && NULL);
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_FailedAtLoad_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const X_FailedAtLoad_Class& instanceName,
    const PropertySet& propertySet)
{
    assert("since load returned an error, this function should never be called!" && NULL);
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_FailedAtLoad_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const X_FailedAtLoad_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_FailedAtLoad_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const X_FailedAtLoad_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_FailedAtLoad_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const X_FailedAtLoad_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
