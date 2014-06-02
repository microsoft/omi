/* @migen@ */
#include <MI.h>
#include "Order_Class_Provider.h"

MI_BEGIN_NAMESPACE

Order_Class_Provider::Order_Class_Provider(
    Module* module) :
    m_Module(module),
    m_IndicationsContext(0)
{
}

Order_Class_Provider::~Order_Class_Provider()
{
}

void Order_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Order_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void Order_Class_Provider::EnableIndications()
{
}

void Order_Class_Provider::DisableIndications()
{
}

void Order_Class_Provider::Subscribe(
    Context& context,
    const String& nameSpace,
    const MI_Filter* filter,
    const String& bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void Order_Class_Provider::Unsubscribe(
    Context& context,
    const String& nameSpace,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
