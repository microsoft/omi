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
#include "X_NumberWorldConformsToProfile_Class_Provider.h"

MI_BEGIN_NAMESPACE

X_NumberWorldConformsToProfile_Class_Provider::X_NumberWorldConformsToProfile_Class_Provider(
        Module* module) :
    m_Module(module)
{
}

X_NumberWorldConformsToProfile_Class_Provider::~X_NumberWorldConformsToProfile_Class_Provider()
{
}
X_NumberWorld_Class GetNumberWorld(const String& ns);
void X_NumberWorldConformsToProfile_Class_Provider::EnumerateInstances(
    Context&  context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    X_NumberWorldConformsToProfile_Class inst;

    X_Profile_Class instProf;

    instProf.InstanceID_value(MI_T("world"));
    instProf.RegisteredName_value(MI_T("World"));
    instProf.SetNamespace(MI_T("interop"));

    inst.Element_value(GetNumberWorld(nameSpace));
    inst.Profile_value(instProf);
    context.Post(inst);
    context.Post(MI_RESULT_OK);
}

void X_NumberWorldConformsToProfile_Class_Provider::GetInstance(
    Context&  context,
    const String& nameSpace,
    const X_NumberWorldConformsToProfile_Class& instance_ref,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_NumberWorldConformsToProfile_Class_Provider::CreateInstance(
    Context&  context,
    const String& nameSpace,
    const X_NumberWorldConformsToProfile_Class& new_instance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_NumberWorldConformsToProfile_Class_Provider::ModifyInstance(
    Context&  context,
    const String& nameSpace,
    const X_NumberWorldConformsToProfile_Class& new_instance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_NumberWorldConformsToProfile_Class_Provider::DeleteInstance(
    Context&  context,
    const String& nameSpace,
    const X_NumberWorldConformsToProfile_Class& instance_ref)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

static void AssocOfProfile(
    Context&  context,
    X_Profile_Class instanceName, 
    const String& resultClass,
    const String& role,
    const String& resultRole,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    if (!instanceName.InstanceID().exists)
    {   // key is missing
        context.Post(MI_RESULT_FAILED);
        return ;
    }
    
    String ID = instanceName.InstanceID().value;


    // only one instance exist on other side
    if ((ID == MI_T("world")) &&
        (role.GetSize() == 0 || role == MI_T("Profile")) &&          // check role
        (resultRole.GetSize() == 0 || resultRole == MI_T("Element"))   // check result role
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
        (role.GetSize() == 0 || role == MI_T("Element")) &&          // check role
        (resultRole.GetSize() == 0 || resultRole == MI_T("Profile"))   // check result role
        )
    {
        X_Profile_Class inst;

        inst.InstanceID_value(MI_T("world"));
        inst.RegisteredName_value(MI_T("World"));
        inst.SetNamespace(MI_T("interop"));
        context.Post(inst);

    }

   context.Post(MI_RESULT_OK);
}

void X_NumberWorldConformsToProfile_Class_Provider::AssociatorInstances(
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
    if (X_Profile_IsA(instanceName))
    {
        AssocOfProfile(context, X_Profile_Class ((const X_Profile*)instanceName,true),
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

void X_NumberWorldConformsToProfile_Class_Provider::ReferenceInstances(
    Context&  context,
    const String& nameSpace,
    const MI_Instance* instanceName, 
    const String& role,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    // verify instance
    if (X_Profile_IsA(instanceName))
    {
        X_Profile_Class prof((const X_Profile*)instanceName,true);

        if (!prof.InstanceID().exists || prof.InstanceID_value() != MI_T("world"))
        {
            context.Post(MI_RESULT_OK);
            return ;
        }

    } else if (X_NumberWorld_IsA(instanceName))
    {
        X_NumberWorld_Class world((const X_NumberWorld*)instanceName,true);
        if (!world.Name().exists || world.Name_value() != MI_T("theWorld"))
        {
            context.Post(MI_RESULT_OK);
            return ;
        }
    }

    EnumerateInstances(context, nameSpace, propertySet, keysOnly, filter );
}


MI_END_NAMESPACE
MI_BEGIN_NAMESPACE
void X_NumberWorldConformsToProfile_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_NumberWorldConformsToProfile_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
