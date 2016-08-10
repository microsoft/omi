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
#include "Widget_Class_Provider.h"

MI_BEGIN_NAMESPACE

Widget_Class_Provider::Widget_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

Widget_Class_Provider::~Widget_Class_Provider()
{
}

void Widget_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    Widget_Class w1;
    w1.SerialNumber_value(1);
    w1.ModelNumber_value(101);
    w1.Color_value(MI_T("Red"));
    w1.Timestamp_value(Datetime::Now());
    context.Post(w1);


    Widget_Class w2;
    w2.SerialNumber_value(2);
    w2.ModelNumber_value(102);
    w2.Color_value(MI_T("Green"));
    w2.Timestamp_value(Datetime::Now());
    context.Post(w2);

    context.Post(MI_RESULT_OK);
}

void Widget_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const Widget_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Widget_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const Widget_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Widget_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const Widget_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Widget_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const Widget_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
MI_BEGIN_NAMESPACE
void Widget_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Widget_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
