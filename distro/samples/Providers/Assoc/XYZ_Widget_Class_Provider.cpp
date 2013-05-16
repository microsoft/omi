/* @migen@ */
#include <MI.h>
#include "XYZ_Widget_Class_Provider.h"

MI_BEGIN_NAMESPACE

XYZ_Widget_Class_Provider::XYZ_Widget_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

XYZ_Widget_Class_Provider::~XYZ_Widget_Class_Provider()
{
}

void XYZ_Widget_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void XYZ_Widget_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void XYZ_Widget_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void XYZ_Widget_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const XYZ_Widget_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void XYZ_Widget_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const XYZ_Widget_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void XYZ_Widget_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const XYZ_Widget_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void XYZ_Widget_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const XYZ_Widget_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
