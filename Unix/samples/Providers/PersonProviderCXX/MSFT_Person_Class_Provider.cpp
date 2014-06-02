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
#include "MSFT_Person_Class_Provider.h"

MI_BEGIN_NAMESPACE

MSFT_Person_Class_Provider::MSFT_Person_Class_Provider(
    Module* module) :
    m_Module(module),
    _SIZE(MI_COUNT(_data))
{
    _size = 0;
}

MSFT_Person_Class_Provider::~MSFT_Person_Class_Provider()
{
}

void MSFT_Person_Class_Provider::EnumerateInstances(
    Context&  context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    for (size_t i = 0; i < _size; i++)
    {
        context.Post(_data[i]);
    }
    context.Post(MI_RESULT_OK);
}


void MSFT_Person_Class_Provider::GetInstance(
    Context&  context,
    const String& nameSpace,
    const MSFT_Person_Class& instance_ref,
    const PropertySet& propertySet)
{
    size_t i;

    if (instance_ref.Key().value == 777)
    {
        MSFT_Person_Class res;

        res.Key_value(777);
        res.Species_value(MI_T("c++ <provider>"));
        res.First_value(MI_T("Test"));
        res.Last_value(MI_T("-CXX- Provider"));
        context.Post(res);
        context.Post(MI_RESULT_OK);
        return;
    }

    /* Search for this instance */
    for (i = 0; i < _size; i++)
    {
        if (instance_ref.Key() == _data[i].Key())
        {
            context.Post(_data[i]);
            context.Post(MI_RESULT_OK);
            return ;
        }
    }
    context.Post(MI_RESULT_NOT_FOUND);
}

void MSFT_Person_Class_Provider::CreateInstance(
    Context&  context,
    const String& nameSpace,
    const MSFT_Person_Class& new_instance)
{
    size_t i;

    /* Reject if the instance already exists */
    for (i = 0; i < _size; i++)
    {
        if (new_instance.Key() == _data[i].Key())
        {
            context.Post(MI_RESULT_ALREADY_EXISTS);
            return ;
        }
    }

    /* Reject on array overflow */
    if (_size == _SIZE)
    {
        context.Post(MI_RESULT_FAILED);
        return ;
    }

    /* Clone the new instance.*/
    /* Add the instance to the array */
    _data[_size++] = new_instance;

    context.Post(new_instance);
    context.Post(MI_RESULT_OK);
}

void MSFT_Person_Class_Provider::ModifyInstance(
    Context&  context,
    const String& nameSpace,
    const MSFT_Person_Class& new_instance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MSFT_Person_Class_Provider::DeleteInstance(
    Context&  context,
    const String& nameSpace,
    const MSFT_Person_Class& instance_ref)
{
    size_t i;

    /* Find and delete this instance. */
    for (i = 0; i < _size; i++)
    {
        if (instance_ref.Key() == _data[i].Key())
        {
            /* Remove instance from array */
            _data[i] = _data[--_size];
            context.Post(MI_RESULT_OK);
            return ;
        }
    }
    context.Post(MI_RESULT_NOT_FOUND);
}

void MSFT_Person_Class_Provider::Invoke_Add(
    Context&  context,
    const String& nameSpace,
    const MSFT_Person_Class& instance,
    const MSFT_Person_Add_Class& in_param )
{
    MSFT_Person_Add_Class out_param;

    out_param.MIReturn_value(100);
    out_param.Z_value(in_param.X_value() + in_param.Y_value());

    context.Post(out_param);
    context.Post(MI_RESULT_OK);
}

template<typename T, typename ItemT>
T fillArray(const T& in_array)
{
    T res;
    res.PushBack((ItemT)in_array.GetSize());

    ItemT sum = 0;

    for ( MI_Uint32 i = 0; i < in_array.GetSize(); i++ )
        sum += in_array[i];

    res.PushBack( sum );
    return res;
}

void MSFT_Person_Class_Provider::Invoke_TestAllTypes(
    Context&  context,
    const String& nameSpace,
    const MSFT_Person_Class& instance,
    const MSFT_Person_TestAllTypes_Class& in_param )
{
    MSFT_Person_TestAllTypes_Class out_param = in_param;

    out_param.MIReturn_value(MI_T("100"));
    out_param.b_value( !in_param.b_value() );
    out_param.u8_value( in_param.u8_value() + 1 );
    out_param.s8_value( in_param.s8_value() + 1 );
    out_param.u16_value( in_param.u16_value() + 1 );
    out_param.s16_value( in_param.s16_value() + 1 );
    out_param.u32_value( in_param.u32_value() + 1 );
    out_param.s32_value( in_param.s32_value() + 1 );
    out_param.u64_value( in_param.u64_value() + 1 );
    out_param.s64_value( in_param.s64_value() + 1 );
    out_param.r32_value( -in_param.r32_value() );
    out_param.r64_value( -in_param.r64_value() );

    MI_Datetime dt = in_param.dt_value().GetData();

    dt.isTimestamp = 1;
    dt.u.timestamp.day++;
    dt.u.timestamp.hour++;
    dt.u.timestamp.microseconds++;
    dt.u.timestamp.minute++;
    dt.u.timestamp.month++;
    dt.u.timestamp.second++;
    dt.u.timestamp.utc++;
    dt.u.timestamp.year++;

    out_param.dt_value(dt);

    // ref
    if (in_param.rf_exists())
    {
        MSFT_Base_Class ref = in_param.rf_value();

        ref.Key_value(ref.Key_value()+1);
        out_param.rf_value(ref);
    }

    // string
    String s(in_param.s_value().Str(), 3);
    s += MI_T("!");
    out_param.s_value(s);

    // c16
    out_param.c16_value( in_param.c16_value() + 1 );

        // bA
    {
            BooleanA res;

            res.PushBack(MI_FALSE);
            res.PushBack(MI_TRUE);
            out_param.bA_value(res);
    }

    out_param.u8A_value( fillArray<Uint8A,MI_Uint8>(in_param.u8A_value()) );
    out_param.s8A_value( fillArray<Sint8A,MI_Sint8>(in_param.s8A_value()) );
    out_param.u16A_value( fillArray<Uint16A,MI_Uint16>(in_param.u16A_value()) );
    out_param.s16A_value( fillArray<Sint16A,MI_Sint16>(in_param.s16A_value()) );
    out_param.u32A_value( fillArray<Uint32A,MI_Uint32>(in_param.u32A_value()) );
    out_param.s32A_value( fillArray<Sint32A,MI_Sint32>(in_param.s32A_value()) );
    out_param.u64A_value( fillArray<Uint64A,MI_Uint64>(in_param.u64A_value()) );
    out_param.s64A_value( fillArray<Sint64A,MI_Sint64>(in_param.s64A_value()) );

    if ( in_param.sA().exists && in_param.sA().value.GetSize() == 2 )
    {
        String res[3] = {String(in_param.sA().value[0].Str()+3),
            String(in_param.sA().value[1].Str()+3),
            MI_T("*")};

        out_param.sA_value(StringA(res,3));
    }
    context.Post(out_param);
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
MI_BEGIN_NAMESPACE

void MSFT_Person_Class_Provider::Invoke_StreamParams(
    Context&  context,
    const String& nameSpace,
    const MSFT_Person_Class& instance,
    const MSFT_Person_StreamParams_Class& in_param )
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
MI_BEGIN_NAMESPACE
void MSFT_Person_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void MSFT_Person_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
