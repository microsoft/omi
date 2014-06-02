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
#include "Color_Class_Provider.h"

#define T MI_T

MI_BEGIN_NAMESPACE

Color_Class_Provider::Color_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

Color_Class_Provider::~Color_Class_Provider()
{
}

void Color_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Color_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Color_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    Color_Class color;

    color.Id_value(1001);
    color.Caption_value(T("This is Red"));
    color.Name_value(T("Red"));
    context.Post(color);

    color.Id_value(1002);
    color.Caption_value(T("This is Green"));
    color.Name_value(T("Green"));
    context.Post(color);

    color.Id_value(1003);
    color.Caption_value(T("This is Blue"));
    color.Name_value(T("Blue"));
    context.Post(color);

    color.Id_value(1004);
    color.Caption_value(T("This is Yellow"));
    color.Name_value(T("Yellow"));
    context.Post(color);

    context.Post(MI_RESULT_OK);
}

void Color_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const Color_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Color_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const Color_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Color_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const Color_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Color_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const Color_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

MI_END_NAMESPACE
