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
#include "X_Halves_Class_Provider.h"

MI_BEGIN_NAMESPACE

X_SmallNumber_Class FillNumberByKey(
    Uint64 key);

X_Halves_Class_Provider::X_Halves_Class_Provider(
        Module* module) :
    m_Module(module)
{
}

X_Halves_Class_Provider::~X_Halves_Class_Provider()
{
}

void X_Halves_Class_Provider::EnumerateInstances(
    Context&  context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_Halves_Class_Provider::GetInstance(
    Context&  context,
    const String& nameSpace,
    const X_Halves_Class& instance_ref,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_Halves_Class_Provider::CreateInstance(
    Context&  context,
    const String& nameSpace,
    const X_Halves_Class& new_instance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_Halves_Class_Provider::ModifyInstance(
    Context&  context,
    const String& nameSpace,
    const X_Halves_Class& new_instance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_Halves_Class_Provider::DeleteInstance(
    Context&  context,
    const String& nameSpace,
    const X_Halves_Class& instance_ref)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_Halves_Class_Provider::AssociatorInstances(
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
    if (!X_SmallNumber_IsA(instanceName))
    {
        context.Post(MI_RESULT_FAILED);
        return ;
    }

    X_SmallNumber_Class number((const X_SmallNumber*)instanceName,true);

    if (!number.Number().exists)
    {   // key is missing
        context.Post(MI_RESULT_FAILED);
        return ;
    }

    Uint64 num = number.Number().value;

    // check if we have smaller half
    if (num % 2 == 0 &&
        (role.GetSize() == 0 || role == MI_T("number")) &&          // check role
        (resultRole.GetSize() == 0 || resultRole == MI_T("half"))   // check result role
        )
    {
        context.Post(FillNumberByKey(num / 2));
    }

    // check if we have bigger half
    if (num * 2 < 10000 &&
        (role.GetSize() == 0 || role == MI_T("half")) &&          // check role
        (resultRole.GetSize() == 0 || resultRole == MI_T("number"))   // check result role
        )
    {
        context.Post(FillNumberByKey(num * 2));
    }

   context.Post(MI_RESULT_OK);
}

void X_Halves_Class_Provider::ReferenceInstances(
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
void X_Halves_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_Halves_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
