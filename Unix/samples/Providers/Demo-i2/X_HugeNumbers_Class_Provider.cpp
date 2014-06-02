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
#include "X_HugeNumbers_Class_Provider.h"

MI_BEGIN_NAMESPACE

X_NumberWorld_Class GetNumberWorld(const String& ns);
X_HugeNumber_Class GetHugeNumberByKey(
    Uint64 key);


X_HugeNumbers_Class_Provider::X_HugeNumbers_Class_Provider(
        Module* module) :
    m_Module(module)
{
}

X_HugeNumbers_Class_Provider::~X_HugeNumbers_Class_Provider()
{
}

void X_HugeNumbers_Class_Provider::EnumerateInstances(
    Context&  context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_HugeNumbers_Class_Provider::GetInstance(
    Context&  context,
    const String& nameSpace,
    const X_HugeNumbers_Class& instance_ref,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_HugeNumbers_Class_Provider::CreateInstance(
    Context&  context,
    const String& nameSpace,
    const X_HugeNumbers_Class& new_instance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_HugeNumbers_Class_Provider::ModifyInstance(
    Context&  context,
    const String& nameSpace,
    const X_HugeNumbers_Class& new_instance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_HugeNumbers_Class_Provider::DeleteInstance(
    Context&  context,
    const String& nameSpace,
    const X_HugeNumbers_Class& instance_ref)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

static void AssocOfHugeNumber(
    Context&  context,
    X_HugeNumber_Class instanceName, 
    const String& resultClass,
    const String& role,
    const String& resultRole,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    if (!instanceName.Number().exists)
    {   // key is missing
        context.Post(MI_RESULT_FAILED);
        return ;
    }
    
    Uint64 num = instanceName.Number().value;


    // only one instance exist on other side
    if ((num == 1000000 || num == 1000000000) &&
        (role.GetSize() == 0 || role == MI_T("number")) &&          // check role
        (resultRole.GetSize() == 0 || resultRole == MI_T("world"))   // check result role
        )
    {
        context.Post(GetNumberWorld(MI_T("")));
    }

   context.Post(MI_RESULT_OK);
}

static void AssocOfNumberWorld(
        Context&  context,
        X_NumberWorld_Class instanceName, 
        const String& resultClass,
        const String& role,
        const String& resultRole,
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter)
{
    if (!instanceName.Name().exists)
    {   // key is missing
        context.Post(MI_RESULT_FAILED);
        return ;
    }
    
    String name = instanceName.Name().value;


    // only one instance exist on other side
    if (name == MI_T("theWorld") &&
        (role.GetSize() == 0 || role == MI_T("world")) &&          // check role
        (resultRole.GetSize() == 0 || resultRole == MI_T("number"))   // check result role
        )
    {
        context.Post(GetHugeNumberByKey(1000000));
        context.Post(GetHugeNumberByKey(1000000000));
    }

   context.Post(MI_RESULT_OK);
}

void X_HugeNumbers_Class_Provider::AssociatorInstances(
    Context&  context,
    const String& nameSpace,
    const MI_Instance* instanceName, 
    const String& resultClass,
    const String& role,
    const String& resultRole,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    if (X_HugeNumber_IsA(instanceName))
    {
        AssocOfHugeNumber(context, X_HugeNumber_Class ((const X_HugeNumber*)instanceName,true),
            resultClass, role, resultRole, propertySet, keysOnly, filter );
        return ;
    }
    if (X_NumberWorld_IsA(instanceName))
    {
        AssocOfNumberWorld(context, X_NumberWorld_Class ((const X_NumberWorld*)instanceName,true),
            resultClass, role, resultRole, propertySet, keysOnly, filter );
        return ;
    }

    // unknown type
    context.Post(MI_RESULT_FAILED);
}

void X_HugeNumbers_Class_Provider::ReferenceInstances(
    Context&  context,
    const String& nameSpace,
    const MI_Instance* instanceName, 
    const String& role,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
MI_BEGIN_NAMESPACE
void X_HugeNumbers_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_HugeNumbers_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
