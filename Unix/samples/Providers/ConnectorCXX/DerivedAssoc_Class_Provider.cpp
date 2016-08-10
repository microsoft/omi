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
#include "DerivedAssoc_Class_Provider.h"

MI_BEGIN_NAMESPACE

DerivedAssoc_Class_Provider::DerivedAssoc_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

DerivedAssoc_Class_Provider::~DerivedAssoc_Class_Provider()
{
}

void DerivedAssoc_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void DerivedAssoc_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const DerivedAssoc_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void DerivedAssoc_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const DerivedAssoc_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void DerivedAssoc_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const DerivedAssoc_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void DerivedAssoc_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const DerivedAssoc_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
MI_BEGIN_NAMESPACE
void DerivedAssoc_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void DerivedAssoc_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
