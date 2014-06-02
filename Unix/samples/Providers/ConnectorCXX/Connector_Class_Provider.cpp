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
#include "Connector_Class_Provider.h"

MI_BEGIN_NAMESPACE

Connector_Class_Provider::Connector_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

Connector_Class_Provider::~Connector_Class_Provider()
{
}

void Connector_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Connector_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const Connector_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Connector_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const Connector_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Connector_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const Connector_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Connector_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const Connector_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Connector_Class_Provider::AssociatorInstancesLeft(
    Context& context,
    const String& nameSpace,
    const Widget_Class& instanceName, 
    const String& resultClass,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Connector_Class_Provider::AssociatorInstancesRight(
    Context& context,
    const String& nameSpace,
    const Gadget_Class& instanceName, 
    const String& resultClass,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Connector_Class_Provider::ReferenceInstancesLeft(
    Context& context,
    const String& nameSpace,
    const Widget_Class& instanceName, 
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Connector_Class_Provider::ReferenceInstancesRight(
    Context& context,
    const String& nameSpace,
    const Gadget_Class& instanceName, 
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
MI_BEGIN_NAMESPACE
void Connector_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Connector_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
