/* @migen@ */
#include <MI.h>
#include "Performance_Class_Provider.h"

MI_BEGIN_NAMESPACE

Performance_Class_Provider::Performance_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

Performance_Class_Provider::~Performance_Class_Provider()
{
}

void Performance_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Performance_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Performance_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
	for(int i = 0; i < 1000; i++)
	{
		Performance_Class perform;
        perform.id_value(i);
		context.Post(perform);
	}

	 context.Post(MI_RESULT_OK);
}

void Performance_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const Performance_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Performance_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const Performance_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Performance_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const Performance_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Performance_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const Performance_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
