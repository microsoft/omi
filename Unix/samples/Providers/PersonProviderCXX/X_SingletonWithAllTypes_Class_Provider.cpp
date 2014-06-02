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
#include "X_SingletonWithAllTypes_Class_Provider.h"
#include <pal/format.h>

#define T MI_T

MI_BEGIN_NAMESPACE

X_SingletonWithAllTypes_Class_Provider::X_SingletonWithAllTypes_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

X_SingletonWithAllTypes_Class_Provider::~X_SingletonWithAllTypes_Class_Provider()
{
}

void X_SingletonWithAllTypes_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    X_SingletonWithAllTypes_Class inst;

    inst.id_value(1);

    inst.b_value(MI_TRUE);
    inst.c16_value(1044); 
    inst.u8_value(172);
    inst.s8_value(-123);
    inst.u16_value(1745);
    inst.s16_value(-1746);
    inst.u32_value(17567);
    inst.s32_value(-17568);
    // u64 range is 0-18446744073709551615
    // s64: -9223372036854775807 - 1  - 9223372036854775807
    inst.u64_value(MI_ULL(18446744073709551613));
    inst.s64_value(-MI_LL(9223372036854775805));
    inst.s_value(MI_T("string value"));

    Datetime dt(2010, 7, 14, 11, 35, 11, 900675, -7);
    inst.dt_value(dt);

    inst.r32_value(32.32f);
    inst.r64_value(64.6464);

    {   // person
        MSFT_Person_Class person;

        person.First_value(MI_T("John"));
        person.Last_value(MI_T("Smith"));
        person.Key_value(7);

        inst.person_value(person);
    }

    {
        // object
        X_TestObject_Class obj;
        obj.id_value(9000);
        obj.operation_value('?');

        inst.objectSingle_value(obj);
    }

    // fill in array types
    {
        BooleanA ba;

        ba.PushBack(MI_TRUE);
        ba.PushBack(MI_FALSE);

        inst.bA_value(ba);
    }

    {
        Uint8A u8a;
        u8a.PushBack(0);
        u8a.PushBack(255);
        u8a.PushBack(128);

        inst.u8A_value(u8a);
    }
    {
        Sint8A s8a;
        s8a.PushBack(0);
        s8a.PushBack(-128);
        s8a.PushBack(127);

        inst.s8A_value(s8a);
    }
    {
        Uint16A u16a;
        u16a.PushBack(0);
        u16a.PushBack(64000);

        inst.u16A_value(u16a);
    }
    {
        Sint16A s16a;
        s16a.PushBack(0);
        s16a.PushBack(-1216);
        s16a.PushBack(258);

        inst.s16A_value(s16a);
    }
    {
        Char16A c16a;
        c16a.PushBack('&');
        c16a.PushBack('\t');
        c16a.PushBack('<');

        inst.c16A_value(c16a);
    }

/*
ATTN: This crashes the agent!
*/
#if 0

    /* size of instance without 'u64A is 3K;
        Adding 800 u64 to make size bigger than 8K (envelopeSize test) */
    {
        Uint64A u64a;

        for (int i = 0; i < 800; i++ )
            u64a.PushBack( 1000 + i );

        inst.u64A_value(u64a);
    }

#endif

    // array of objects
    {
        X_TestObject_Class obj;
        X_TestObject_ClassA objs;

        obj.str_value(MI_T("object"));

        obj.id_value(9001);
        obj.operation_value('-');
        objs.PushBack(obj);
        obj.id_value(9002);
        obj.operation_value('+');
        objs.PushBack(obj);
        obj.id_value(9003);
        obj.operation_value('/');
        objs.PushBack(obj);
        obj.id_value(9004);
        obj.operation_value('*');
        objs.PushBack(obj);

        inst.fourObjects_value(objs);
    }


    context.Post(inst);
    context.Post(MI_RESULT_OK);
}

void X_SingletonWithAllTypes_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const X_SingletonWithAllTypes_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_SingletonWithAllTypes_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const X_SingletonWithAllTypes_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_SingletonWithAllTypes_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const X_SingletonWithAllTypes_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_SingletonWithAllTypes_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const X_SingletonWithAllTypes_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
MI_BEGIN_NAMESPACE
void X_SingletonWithAllTypes_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_SingletonWithAllTypes_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
