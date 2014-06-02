/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
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
