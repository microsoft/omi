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
#include "MSFT_Alert_Class_Provider.h"

MI_BEGIN_NAMESPACE

MSFT_Alert_Class_Provider::MSFT_Alert_Class_Provider(
    Module* module) :
    m_Module(module),
    m_IndicationsContext(0)
{
}

MSFT_Alert_Class_Provider::~MSFT_Alert_Class_Provider()
{
}

void MSFT_Alert_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void MSFT_Alert_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void MSFT_Alert_Class_Provider::EnableIndications()
{
}

void MSFT_Alert_Class_Provider::DisableIndications()
{
}

void MSFT_Alert_Class_Provider::Subscribe(
    Context& context,
    const String& nameSpace,
    const MI_Filter* filter,
    const String& bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MSFT_Alert_Class_Provider::Unsubscribe(
    Context& context,
    const String& nameSpace,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
