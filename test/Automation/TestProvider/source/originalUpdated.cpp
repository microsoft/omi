/* @migen@ */
#include <MI.h>
#include "DemoTest_Class_Provider.h"

MI_BEGIN_NAMESPACE

DemoTest_Class_Provider::DemoTest_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

DemoTest_Class_Provider::~DemoTest_Class_Provider()
{
}

void DemoTest_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void DemoTest_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void DemoTest_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    DemoTest_Class original1;
	original1.Name_value("EnumeratteInstances has been implemented in original files.");
	context.Post(original1);
    context.Post(MI_RESULT_OK);
}

void DemoTest_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const DemoTest_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void DemoTest_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const DemoTest_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void DemoTest_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const DemoTest_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void DemoTest_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const DemoTest_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
