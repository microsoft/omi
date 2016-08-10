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
#include "Dog_Class_Provider.h"

MI_BEGIN_NAMESPACE

Dog_Class_Provider::Dog_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

Dog_Class_Provider::~Dog_Class_Provider()
{
}

void Dog_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Dog_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Dog_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    Dog_Class dog;
    dog.Key_value(MI_T("1001"));

#if 0
    {
        Array<Uint16> arr;
        dog.Array1_value(arr);
    }
#endif
    {
        Array<Uint16> arr;
        dog.Array2_value(arr);
    }
    {
        Array<Uint16> arr;
        arr.PushBack(10);
        arr.PushBack(20);
        arr.PushBack(30);
        dog.Array3_value(arr);
    }

    dog.Print();
    context.Post(dog);
    context.Post(MI_RESULT_OK);
}

void Dog_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const Dog_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Dog_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const Dog_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Dog_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const Dog_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Dog_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const Dog_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
