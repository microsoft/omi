/* @migen@ */
#include <MI.h>
#include "Frog_Class_Provider.h"

MI_BEGIN_NAMESPACE

Frog_Class_Provider::Frog_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

Frog_Class_Provider::~Frog_Class_Provider()
{
}

void Frog_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Frog_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Frog_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    Frog_Class f1;
    f1.id_value(MI_T("EnumerateInstances"));
    context.Post(f1);

    context.Post(MI_RESULT_OK);
}

void Frog_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const Frog_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Frog_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const Frog_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Frog_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const Frog_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Frog_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const Frog_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
