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

/* @migen@ */
#include <MI.h>
#include "X_Number1000001_Class_Provider.h"

MI_BEGIN_NAMESPACE

X_Number1000001_Class_Provider::X_Number1000001_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

X_Number1000001_Class_Provider::~X_Number1000001_Class_Provider()
{
}

void X_Number1000001_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_Number1000001_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_Number1000001_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    X_Number1000001_Class inst;

    inst.Number_value(1000001);
    inst.Magnitude_value(6);
    inst.Property0_value(9);

    context.Post(inst);
    context.Post(MI_RESULT_OK);
}

void X_Number1000001_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const X_Number1000001_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_Number1000001_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const X_Number1000001_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_Number1000001_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const X_Number1000001_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_Number1000001_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const X_Number1000001_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_Number1000001_Class_Provider::Invoke_SpellMagnitude(
    Context& context,
    const String& nameSpace,
    const X_Number1000001_Class& instance,
    const X_Number1000001_SpellMagnitude_Class& in)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_Number1000001_Class_Provider::Invoke_TestEmbedded(
    Context& context,
    const String& nameSpace,
    const X_Number1000001_Class& instance,
    const X_Number1000001_TestEmbedded_Class& in)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_Number1000001_Class_Provider::Invoke_Method1(
    Context& context,
    const String& nameSpace,
    const X_Number1000001_Class& instance,
    const X_Number1000001_Method1_Class& in)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
