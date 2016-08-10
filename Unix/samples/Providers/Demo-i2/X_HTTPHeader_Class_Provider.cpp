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
#include "X_HTTPHeader_Class_Provider.h"

MI_BEGIN_NAMESPACE

X_HTTPHeader_Class_Provider::X_HTTPHeader_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

X_HTTPHeader_Class_Provider::~X_HTTPHeader_Class_Provider()
{
}

void X_HTTPHeader_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_HTTPHeader_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_HTTPHeader_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    MI_Context* ctx = context.context();

    // Use MI_Context_GetCustomOptionCount:

    MI_Uint32 count;
    MI_Result r = MI_Context_GetCustomOptionCount(ctx, &count);

    if (r != MI_RESULT_OK)
    {
        context.Post(MI_RESULT_FAILED);
        return;
    }

    if( 0 == count )
    {
        context.Post(MI_RESULT_FAILED);
        return;
    }

    // Use MI_Context_GetCustomOptionAt:

    for (MI_Uint32 i = 0; i < count; i++)
    {
        const MI_Char* name;
        MI_Value value;
        MI_Type type;

        MI_Result r = MI_Context_GetCustomOptionAt(
            ctx, 
            i, 
            &name, 
            &type, 
            &value);

        if (r == MI_RESULT_OK && type == MI_STRING)
        {
            X_HTTPHeader_Class inst;
            inst.Name_value(name);
            inst.Value_value(value.string);
            context.Post(inst);
        }
    }

    // Use MI_Context_GetCustomOption:
    {
        MI_Result r;
        MI_Value value;
        MI_Type type;

        r = MI_Context_GetCustomOption(
            ctx,
            MI_T("HTTP_Content_Type"),
            &type,
            &value);

        if (r == MI_RESULT_OK && type == MI_STRING)
        {
            X_HTTPHeader_Class inst;
            inst.Name_value(MI_T("GetCustomOption_HTTP_Content_Type"));
            inst.Value_value(value.string);
            context.Post(inst);
        }
    }

    // Use MI_Context_GetStringOption:
    {
        MI_Result r;
        const MI_Char* value;

        r = MI_Context_GetStringOption(
            ctx,
            MI_T("HTTP_Content_Type"),
            &value);

        if (r == MI_RESULT_OK)
        {
            X_HTTPHeader_Class inst;
            inst.Name_value(MI_T("GetStringOption_HTTP_Content_Type"));
            inst.Value_value(value);
            context.Post(inst);
        }
    }

    // Post success:
    context.Post(MI_RESULT_OK);
}

void X_HTTPHeader_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const X_HTTPHeader_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_HTTPHeader_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const X_HTTPHeader_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_HTTPHeader_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const X_HTTPHeader_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_HTTPHeader_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const X_HTTPHeader_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
