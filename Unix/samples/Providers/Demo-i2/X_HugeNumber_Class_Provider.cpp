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
#include "X_HugeNumber_Class_Provider.h"
#include "X_Halves.h"
#include "X_TestObject.h"
#include "X_Profile.h"

MI_BEGIN_NAMESPACE

X_HugeNumber_Class_Provider::X_HugeNumber_Class_Provider(
        Module* module) :
    m_Module(module)
{
}

X_HugeNumber_Class_Provider::~X_HugeNumber_Class_Provider()
{
}
String _SpellNumber(Uint64 n, bool spellZero);
X_SmallNumber_Class FillNumberByKey(
    Uint64 key);

X_HugeNumber_Class GetHugeNumberByKey(
    Uint64 key)
{
    X_HugeNumber_Class inst;

    if ( key == 1000000 )
    {
        inst.Number_value(1000000);
        inst.Magnitude_value(6);
    }
    else
    {
        inst.Number_value(1000000000);
        inst.Magnitude_value(9);
    }

    inst.MagnitudeObj_value( FillNumberByKey(inst.Magnitude_value()) );

    {
        X_SmallNumber_ClassA res;

        for( int num = 1; num < 4; num++ )
        {
            res.PushBack(FillNumberByKey(num));
        }

        inst.Numbers123_value(res);
    }

    // embedded object test
    X_Halves_Class  h;

    h.half_value(FillNumberByKey(0));
    h.number_value(FillNumberByKey(0));

    inst.Number0_value(h);

    // array of embedded objects
    {
        InstanceA res;

        X_TestObject_Class obj1;

        obj1.id_value(17);
        obj1.str_value(MI_T("a string"));

        res.PushBack(obj1);

        X_Profile_Class obj2;

        obj2.InstanceID_value(MI_T("a profile"));
        obj2.RegisteredName_value(MI_T("embedded object"));
        obj2.SetNamespace(MI_T("interop"));

        res.PushBack(obj2);

        inst.TwoTestObjects_value(res);
    }

    inst.SetNamespace(MI_T("test/cpp"));
    return inst;
}


void X_HugeNumber_Class_Provider::EnumerateInstances(
    Context&  context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(GetHugeNumberByKey(1000000));
    context.Post(GetHugeNumberByKey(1000000000));

    context.Post(MI_RESULT_OK);
}

void X_HugeNumber_Class_Provider::GetInstance(
    Context&  context,
    const String& nameSpace,
    const X_HugeNumber_Class& instance_ref,
    const PropertySet& propertySet)
{
    X_HugeNumber_Class inst;
    MI_Result r = MI_RESULT_OK;

    if ( instance_ref.Number_value() == 1000000 )
    {
        inst = GetHugeNumberByKey(1000000);
    }
    else if ( instance_ref.Number_value() == 1000000000 )
    {
        inst = GetHugeNumberByKey(1000000000);
    }
    else
        r = MI_RESULT_NOT_FOUND;

    if ( MI_RESULT_OK == r )
        context.Post(inst);

    context.Post(r);
}

void X_HugeNumber_Class_Provider::CreateInstance(
    Context&  context,
    const String& nameSpace,
    const X_HugeNumber_Class& new_instance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_HugeNumber_Class_Provider::ModifyInstance(
    Context&  context,
    const String& nameSpace,
    const X_HugeNumber_Class& new_instance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_HugeNumber_Class_Provider::DeleteInstance(
    Context&  context,
    const String& nameSpace,
    const X_HugeNumber_Class& instance_ref)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_HugeNumber_Class_Provider::Invoke_SpellMagnitude(
    Context&  context,
    const String& nameSpace,
    const X_HugeNumber_Class& instance,
    const X_HugeNumber_SpellMagnitude_Class& in_param )
{
    X_HugeNumber_SpellMagnitude_Class out;

    X_HugeNumber_Class inst = GetHugeNumberByKey(instance.Number_value());


    out.MIReturn_value(_SpellNumber(inst.Magnitude_value(), true));
    context.Post(out);
    context.Post(MI_RESULT_OK);
}

static X_TestObject_Class _Solve( const X_TestObject_Class& obj )
{
    X_TestObject_Class res = obj;

    switch (res.operation_value())
    {
    case '-':
        res.result_value(obj.left_operand_value() - obj.right_operand_value());
        break;
    case '+':
        res.result_value(obj.left_operand_value() + obj.right_operand_value());
        break;
    case '*':
        res.result_value(obj.left_operand_value() * obj.right_operand_value());
        break;
    default:
        res.result_value(0);
        break;

    }

    return res;
}

void X_HugeNumber_Class_Provider::Invoke_TestEmbedded(
    Context&  context,
    const String& nameSpace,
    const X_HugeNumber_Class& instance,
    const X_HugeNumber_TestEmbedded_Class& in_param )
{
    X_HugeNumber_TestEmbedded_Class out;

    //class X_TestObject
    //{
    //    [key] Uint64  id;
    //    string  str;
    //    Char16  operation; // +/-*
    //    uint32  left_operand;
    //    uint32  right_operand;
    //    uint32  result;
    //};

    //[static, EmbeddedInstance("X_TestObject")]
    //String TestEmbedded(
    //    [EmbeddedObject, IN, OUT]
    //    String objectsArray[],
    //    [EmbeddedObject, IN, OUT]
    //    String objectSingle,
    //    
    //    [EmbeddedInstance("X_TestObject"), in,out]
    //    String testObjectsArray[],
    //    [EmbeddedInstance("X_TestObject"), in,out]
    //    String testObjectSingle
    //);


    // do some magic with in/out parameters:
    // 'solve' testObjects - "result = left_operand operation right_operand"
    // assume objects are type of SmallNumber - return 'number + 1'
    // function returns a testobject '17'

    if (in_param.testObjectSingle().exists)
    {
        out.testObjectSingle_value( _Solve(in_param.testObjectSingle_value()));
    }

    if (in_param.testObjectsArray().exists)
    {
        X_TestObject_ClassA ret;

        ret.Resize( in_param.testObjectsArray_value().GetSize() );

        for ( unsigned int i  = 0; i < ret.GetSize(); i++ )
        {
            ret[i] = _Solve(in_param.testObjectsArray_value()[i]);
        }

        out.testObjectsArray_value(ret);
    }

    {   // return param
        X_TestObject_Class ret;
        ret.id_value( 17 );
        out.MIReturn_value( ret );
    }

    context.Post(out);
    context.Post(MI_RESULT_OK);
}


MI_END_NAMESPACE
MI_BEGIN_NAMESPACE
void X_HugeNumber_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_HugeNumber_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
