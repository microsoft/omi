/* @migen@ */
#include <MI.h>
#include "XYZ_Assoc2_Class_Provider.h"

MI_BEGIN_NAMESPACE

XYZ_Assoc2_Class_Provider::XYZ_Assoc2_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

XYZ_Assoc2_Class_Provider::~XYZ_Assoc2_Class_Provider()
{
}

void XYZ_Assoc2_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void XYZ_Assoc2_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void XYZ_Assoc2_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void XYZ_Assoc2_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const XYZ_Assoc2_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void XYZ_Assoc2_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const XYZ_Assoc2_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void XYZ_Assoc2_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const XYZ_Assoc2_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void XYZ_Assoc2_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const XYZ_Assoc2_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void XYZ_Assoc2_Class_Provider::AssociatorInstancesLeft(
    Context& context,
    const String& nameSpace,
    const XYZ_Widget2_Class& instanceName, 
    const String& resultClass,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    {
        XYZ_Gadget2_Class gadget;
        gadget.Key_value("1001");
        context.Post(gadget);
    }
    {
        XYZ_Gadget2_Class gadget;
        gadget.Key_value("1002");
        context.Post(gadget);
    }

    context.Post(MI_RESULT_OK);
}

void XYZ_Assoc2_Class_Provider::AssociatorInstancesRight(
    Context& context,
    const String& nameSpace,
    const XYZ_Gadget2_Class& instanceName, 
    const String& resultClass,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_OK);
}

void XYZ_Assoc2_Class_Provider::ReferenceInstancesLeft(
    Context& context,
    const String& nameSpace,
    const XYZ_Widget2_Class& instanceName, 
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_OK);
}

void XYZ_Assoc2_Class_Provider::ReferenceInstancesRight(
    Context& context,
    const String& nameSpace,
    const XYZ_Gadget2_Class& instanceName, 
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_OK);
}


MI_END_NAMESPACE
