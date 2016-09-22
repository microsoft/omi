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
#include "Gadget_Class_Provider.h"

MI_BEGIN_NAMESPACE

Gadget_Class_Provider::Gadget_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

Gadget_Class_Provider::~Gadget_Class_Provider()
{
}

void Gadget_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Gadget_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Gadget_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    // Gadget.Key=1003:
    {
        Gadget_Class g;
        g.Key_value(1003);
        g.ModelNumber_value(3);
        g.Size_value(33);
        context.Post(g);
    }

    // Gadget.Key=1004:
    {
        Gadget_Class g;
        g.Key_value(1004);
        g.ModelNumber_value(4);
        g.Size_value(43);
        context.Post(g);
    }

    context.Post(MI_RESULT_OK);
}

void Gadget_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const Gadget_Class& instanceName,
    const PropertySet& propertySet)
{
    if (instanceName.Key_value() == 1003)
    {
        // Gadget.Key=1003:
        Gadget_Class g;
        g.Key_value(1003);
        g.ModelNumber_value(3);
        g.Size_value(33);
        context.Post(g);
        context.Post(MI_RESULT_OK);
    }
    else if (instanceName.Key_value() == 1004)
    {
        // Gadget.Key=1004:
        Gadget_Class g;
        g.Key_value(1004);
        g.ModelNumber_value(4);
        g.Size_value(43);
        context.Post(g);
        context.Post(MI_RESULT_OK);
    }
    else
    {
        context.Post(MI_RESULT_NOT_FOUND);
    }
}

void Gadget_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const Gadget_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Gadget_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const Gadget_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Gadget_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const Gadget_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Gadget_Class_Provider::Invoke_ChangeState(
    Context& context,
    const String& nameSpace,
    const Gadget_Class& instance,
    const Gadget_ChangeState_Class& in)
{
    Gadget_ChangeState_Class out;

    // Print the input parameter:
    if (in.NewState_exists())
    {
        printf("NewState=%u\n", in.NewState_value());
    }

    // Set the output parameter:
    out.OldState_value(2);

    // Set the return value:
    out.MIReturn_value(0);

    // Post the 'out' object.
    context.Post(out);

    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
