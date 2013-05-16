/* @migen@ */
#include <MI.h>
#include "Main_Class_Provider.h"

MI_BEGIN_NAMESPACE

Main_Class_Provider::Main_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

Main_Class_Provider::~Main_Class_Provider()
{
}

void Main_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Main_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Main_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    Main_Class fristInst;
    Main_Class secondInst;
	fristInst.Name_value(MI_T("Prop"));
	secondInst.Name_value(MI_T("Prop2"));
	EmbeddedInstance_Class subFristInst;
	subFristInst.Id_value(1);
	StringA strAElement;
	strAElement.PushBack(MI_T("1"));
	strAElement.PushBack(MI_T("2"));
	strAElement.PushBack(MI_T("3"));
	subFristInst.Element_value(strAElement);

	EmbeddedInstance_Class subSecondInst;
	subSecondInst.Id_value(2);
	subSecondInst.Element_value(strAElement);

	fristInst.FristInstance_value(subFristInst);
	secondInst.SecondInstance_value(subSecondInst);
	
	context.Post(fristInst);
	context.Post(secondInst);
    context.Post(MI_RESULT_OK);
}

void Main_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const Main_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Main_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const Main_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Main_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const Main_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Main_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const Main_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
