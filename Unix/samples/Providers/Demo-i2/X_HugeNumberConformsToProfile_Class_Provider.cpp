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
#include "X_HugeNumberConformsToProfile_Class_Provider.h"

MI_BEGIN_NAMESPACE

X_HugeNumber_Class GetHugeNumberByKey(
    Uint64 key);


X_HugeNumberConformsToProfile_Class_Provider::X_HugeNumberConformsToProfile_Class_Provider(
        Module* module) :
    m_Module(module)
{
}

X_HugeNumberConformsToProfile_Class_Provider::~X_HugeNumberConformsToProfile_Class_Provider()
{
}

void X_HugeNumberConformsToProfile_Class_Provider::EnumerateInstances(
    Context&  context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    X_HugeNumberConformsToProfile_Class inst;

    X_Profile_Class instProf;

    instProf.InstanceID_value(MI_T("number"));
    instProf.RegisteredName_value(MI_T("Huge Numbers"));
    instProf.SetNamespace(MI_T("interop"));

    inst.Profile_value(instProf);
    inst.Element_value(GetHugeNumberByKey(1000000));

    context.Post(inst);

    inst.Element_value(GetHugeNumberByKey(1000000000));

    context.Post(inst);

    context.Post(MI_RESULT_OK);
}

void X_HugeNumberConformsToProfile_Class_Provider::GetInstance(
    Context&  context,
    const String& nameSpace,
    const X_HugeNumberConformsToProfile_Class& instance_ref,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_HugeNumberConformsToProfile_Class_Provider::CreateInstance(
    Context&  context,
    const String& nameSpace,
    const X_HugeNumberConformsToProfile_Class& new_instance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_HugeNumberConformsToProfile_Class_Provider::ModifyInstance(
    Context&  context,
    const String& nameSpace,
    const X_HugeNumberConformsToProfile_Class& new_instance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_HugeNumberConformsToProfile_Class_Provider::DeleteInstance(
    Context&  context,
    const String& nameSpace,
    const X_HugeNumberConformsToProfile_Class& instance_ref)
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
    if ((ID == MI_T("number")) &&
        (role.GetSize() == 0 || role == MI_T("Profile")) &&          // check role
        (resultRole.GetSize() == 0 || resultRole == MI_T("Element"))   // check result role
        )
    {
        context.Post(GetHugeNumberByKey(1000000));
        context.Post(GetHugeNumberByKey(1000000000));
    }

   context.Post(MI_RESULT_OK);
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
        (role.GetSize() == 0 || role == MI_T("Element")) &&          // check role
        (resultRole.GetSize() == 0 || resultRole == MI_T("Profile"))   // check result role
        )
    {
        X_Profile_Class inst;

        inst.InstanceID_value(MI_T("number"));
        inst.RegisteredName_value(MI_T("Huge Number"));
        inst.SetNamespace(MI_T("interop"));
        context.Post(inst);

    }

   context.Post(MI_RESULT_OK);
}

void X_HugeNumberConformsToProfile_Class_Provider::AssociatorInstances(
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
    if (X_HugeNumber_IsA(instanceName))
    {
        AssocOfHugeNumber(context, X_HugeNumber_Class ((const X_HugeNumber*)instanceName,true),
            resultClass, role, resultRole, propertySet, keysOnly, filter );
        return ;
    }

    // unknown type
    context.Post(MI_RESULT_FAILED);
}

void X_HugeNumberConformsToProfile_Class_Provider::ReferenceInstances(
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
void X_HugeNumberConformsToProfile_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_HugeNumberConformsToProfile_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
