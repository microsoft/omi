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

void Connector_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    // Connector.Left="Gadget.Key=1001","Widget.Key="1003"
    {
        Widget_Class w;
        w.Key_value(1001);
        Gadget_Class g;
        g.Key_value(1003);
        Connector_Class c;
        c.Left_value(w);
        c.Right_value(g);
        context.Post(c);
    }

    // Connector.Left="Gadget.Key=1002","Widget.Key="1004"
    {
        Widget_Class w;
        w.Key_value(1002);
        Gadget_Class g;
        g.Key_value(1004);
        Connector_Class c;
        c.Left_value(w);
        c.Right_value(g);
        context.Post(c);
    }

    context.Post(MI_RESULT_OK);
}

void Connector_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const Connector_Class& instanceName,
    const PropertySet& propertySet)
{
    if (instanceName.Left_value().Key_value() == 1001 &&
        instanceName.Right_value().Key_value() == 1003)
    {
        // Connector.Left="Gadget.Key=1001","Widget.Key="1003"
        Widget_Class w;
        w.Key_value(1001);

        Gadget_Class g;
        g.Key_value(1003);

        Connector_Class c;
        c.Left_value(w);
        c.Right_value(g);

        context.Post(c);
        context.Post(MI_RESULT_OK);
    }
    else if (instanceName.Left_value().Key_value() == 1002 &&
        instanceName.Right_value().Key_value() == 1004)
    {
        // Connector.Left="Gadget.Key=1002","Widget.Key="1004"
        Widget_Class w;
        w.Key_value(1001);

        Gadget_Class g;
        g.Key_value(1003);

        Connector_Class c;
        c.Left_value(w);
        c.Right_value(g);

        context.Post(c);
        context.Post(MI_RESULT_OK);
    }
    else
    {
        context.Post(MI_RESULT_NOT_FOUND);
    }
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
    if (instanceName.Key_value() == 1001)
    {
        // Gadget.Key=1003:
        Gadget_Class g;
        g.Key_value(1003);
        g.ModelNumber_value(3);
        g.Size_value(33);
        context.Post(g);
        context.Post(MI_RESULT_OK);
    }
    else if (instanceName.Key_value() == 1002)
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

void Connector_Class_Provider::AssociatorInstancesRight(
    Context& context,
    const String& nameSpace,
    const Gadget_Class& instanceName, 
    const String& resultClass,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    if (instanceName.Key_value() == 1003)
    {
        // Widget.Key=1001:
        Widget_Class w;
        w.Key_value(1001);
        w.ModelNumber_value(1);
        w.Color_value("Red");
        context.Post(w);
        context.Post(MI_RESULT_OK);
    }
    else if (instanceName.Key_value() == 1004)
    {
        // Widget.Key=1002:
        Widget_Class w;
        w.Key_value(1002);
        w.ModelNumber_value(2);
        w.Color_value("Green");
        context.Post(w);
        context.Post(MI_RESULT_OK);
    }
    else
    {
        context.Post(MI_RESULT_NOT_FOUND);
    }
}

void Connector_Class_Provider::ReferenceInstancesLeft(
    Context& context,
    const String& nameSpace,
    const Widget_Class& instanceName, 
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    if (instanceName.Key_value() == 1001)
    {
        // Connector.Left="Gadget.Key=1001","Widget.Key="1003"
        Widget_Class w;
        w.Key_value(1001);
        Gadget_Class g;
        g.Key_value(1003);
        Connector_Class c;
        c.Left_value(w);
        c.Right_value(g);
        context.Post(c);
        context.Post(MI_RESULT_OK);
    }
    else if (instanceName.Key_value() == 1002)
    {
        // Connector.Left="Gadget.Key=1002","Widget.Key="1004"
        Widget_Class w;
        w.Key_value(1002);
        Gadget_Class g;
        g.Key_value(1004);
        Connector_Class c;
        c.Left_value(w);
        c.Right_value(g);
        context.Post(c);
        context.Post(MI_RESULT_OK);
    }
    else
    {
        context.Post(MI_RESULT_NOT_FOUND);
    }
}

void Connector_Class_Provider::ReferenceInstancesRight(
    Context& context,
    const String& nameSpace,
    const Gadget_Class& instanceName, 
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    if (instanceName.Key_value() == 1003)
    {
        // Connector.Left="Gadget.Key=1001","Widget.Key="1003"
        Widget_Class w;
        w.Key_value(1001);
        Gadget_Class g;
        g.Key_value(1003);
        Connector_Class c;
        c.Left_value(w);
        c.Right_value(g);
        context.Post(c);
        context.Post(MI_RESULT_OK);
    }
    else if (instanceName.Key_value() == 1004)
    {
        // Connector.Left="Gadget.Key=1002","Widget.Key="1004"
        Widget_Class w;
        w.Key_value(1002);
        Gadget_Class g;
        g.Key_value(1004);
        Connector_Class c;
        c.Left_value(w);
        c.Right_value(g);
        context.Post(c);
        context.Post(MI_RESULT_OK);
    }
    else
    {
        context.Post(MI_RESULT_NOT_FOUND);
    }
}

MI_END_NAMESPACE
