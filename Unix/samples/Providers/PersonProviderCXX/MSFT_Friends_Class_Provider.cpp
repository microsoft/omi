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
#include "MSFT_Friends_Class_Provider.h"

MI_BEGIN_NAMESPACE

MSFT_Friends_Class_Provider::MSFT_Friends_Class_Provider(
        Module* module) :
    m_Module(module)
{
}

MSFT_Friends_Class_Provider::~MSFT_Friends_Class_Provider()
{
}

void MSFT_Friends_Class_Provider::EnumerateInstances(
    Context&  context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MSFT_Friends_Class_Provider::GetInstance(
    Context&  context,
    const String& nameSpace,
    const MSFT_Friends_Class& instance_ref,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MSFT_Friends_Class_Provider::CreateInstance(
    Context&  context,
    const String& nameSpace,
    const MSFT_Friends_Class& new_instance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MSFT_Friends_Class_Provider::ModifyInstance(
    Context&  context,
    const String& nameSpace,
    const MSFT_Friends_Class& new_instance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MSFT_Friends_Class_Provider::DeleteInstance(
    Context&  context,
    const String& nameSpace,
    const MSFT_Friends_Class& instance_ref)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MSFT_Friends_Class_Provider::AssociatorInstances(
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
    if (!MSFT_Person_IsA(instanceName))
    {
        context.Post(MI_RESULT_FAILED);
        return ;
    }

    MSFT_Person_Class person((const MSFT_Person*)instanceName,true);

    if (role == MI_T("Left") && resultRole == MI_T("Right"))
    {
        if (person.Key().exists && person.Key().value == 1)
        {
            MSFT_Person_Class inst;
            inst.Key_value(2);
            inst.First_value(MI_T("John"));
            inst.Last_value(MI_T("Adams"));
            context.Post(inst);
        }
    }

    if (role == MI_T("Right") && resultRole == MI_T("Left"))
    {
        if (person.Key().exists && person.Key().value == 2)
        {
            MSFT_Person_Class inst;
            inst.Key_value(1);
            inst.First_value(MI_T("George"));
            inst.Last_value(MI_T("Washington"));
            context.Post(inst);
        }
    }

    context.Post(MI_RESULT_OK);
}

void MSFT_Friends_Class_Provider::ReferenceInstances(
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

void MSFT_Friends_Class_Provider::Invoke_AddFriend(
    Context&  context,
    const String& nameSpace,
    const MSFT_Friends_Class& instance,
    const MSFT_Friends_AddFriend_Class& in_param )
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MSFT_Friends_Class_Provider::Invoke_AddFriends(
    Context&  context,
    const String& nameSpace,
    const MSFT_Friends_Class& instance,
    const MSFT_Friends_AddFriends_Class& in_param )
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
MI_BEGIN_NAMESPACE
void MSFT_Friends_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void MSFT_Friends_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
