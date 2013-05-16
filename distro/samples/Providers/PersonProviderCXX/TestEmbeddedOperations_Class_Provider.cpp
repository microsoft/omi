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
#include "TestEmbeddedOperations_Class_Provider.h"
#include "X_TestEmbeddedObjectNotReferenced.h"

MI_BEGIN_NAMESPACE

TestEmbeddedOperations_Class_Provider::TestEmbeddedOperations_Class_Provider(
        Module* module) :
    m_Module(module)
{
}

TestEmbeddedOperations_Class_Provider::~TestEmbeddedOperations_Class_Provider()
{
}

void TestEmbeddedOperations_Class_Provider::EnumerateInstances(
    Context&  context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void TestEmbeddedOperations_Class_Provider::GetInstance(
    Context&  context,
    const String& nameSpace,
    const TestEmbeddedOperations_Class& instance_ref,
    const PropertySet& propertySet)
{
    if (!instance_ref.key().exists || instance_ref.key_value() != 1)
    {
        context.Post(MI_RESULT_NOT_FOUND);
        return;
    }

    TestEmbeddedOperations_Class res;
    MSFT_Person_Class person;

    person.Last_value(MI_T("Smith"));
    person.First_value(MI_T("John"));
    person.Key_value(7);

    res.key_value(1);
    res.person_value(person);

    MSFT_Person_ClassA threePersons;

    // add three persons
    person.Last_value(MI_T("Black"));
    person.First_value(MI_T("John"));
    person.Key_value(7);
    threePersons.PushBack(person);

    person.Last_value(MI_T("White"));
    person.First_value(MI_T("Bill"));
    person.Key_value(8);
    threePersons.PushBack(person);

    person.Last_value(MI_T("Brown"));
    person.First_value(MI_T("Ben"));
    person.Key_value(9);
    threePersons.PushBack(person);

    res.threePersons_value(threePersons);

    context.Post(res);
    context.Post(MI_RESULT_OK);
}

void TestEmbeddedOperations_Class_Provider::CreateInstance(
    Context&  context,
    const String& nameSpace,
    const TestEmbeddedOperations_Class& new_instance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void TestEmbeddedOperations_Class_Provider::ModifyInstance(
    Context&  context,
    const String& nameSpace,
    const TestEmbeddedOperations_Class& new_instance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void TestEmbeddedOperations_Class_Provider::DeleteInstance(
    Context&  context,
    const String& nameSpace,
    const TestEmbeddedOperations_Class& instance_ref)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void TestEmbeddedOperations_Class_Provider::Invoke_TestEmbedded(
    Context&  context,
    const String& nameSpace,
    const TestEmbeddedOperations_Class& instance,
    const TestEmbeddedOperations_TestEmbedded_Class& in_param )
{
    // INPUT:
    // objectsArray - 2 instances of MSFT_Base
    // objectSingle - MSFT_Person
    // testObjectsArray - 3 objects
    // testObjectSingle - not set

    // OUTPUT
    // objectsArray - 2 instances of MSFT_Animal with the same keys and species "test"
    // objectSingle - the same
    // testObjectsArray - last 2 objects of input
    // testObjectSingle - key is a sum of input objects

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

    TestEmbeddedOperations_TestEmbedded_Class res;

    X_TestObject_Class item;
    X_TestObject_ClassA items;

    /* get last two elements */
    if (in_param.testObjectsArray().exists && in_param.testObjectsArray_value().GetSize() > 1)
    {
        for ( unsigned int i = in_param.testObjectsArray_value().GetSize() - 2; i < in_param.testObjectsArray_value().GetSize(); i++ )
        {
            items.PushBack(in_param.testObjectsArray_value()[i]);
        }
        res.testObjectsArray_value(items);
    }

    Uint64 id = 0;
    if (in_param.testObjectsArray().exists)
    {
        for ( unsigned int i = 0; i < in_param.testObjectsArray_value().GetSize(); i++ )
        {
            id += in_param.testObjectsArray_value()[i].id_value();
        }
        item.id_value(id);
        res.MIReturn_value(item);
    }

    if (in_param.objectsArray().exists)
    {
        // objectsArray
        InstanceA objs;
        MSFT_Animal_Class obj;

        obj.Species_value(MI_T("test"));
        for ( unsigned int i = 0; i < in_param.objectsArray_value().GetSize(); i++ )
        {
            obj.Key_value(((MSFT_Base_Class&)in_param.objectsArray_value()[i]).Key_value());
            objs.PushBack(obj);
        }

        res.objectsArray_value(objs);
    }


    context.Post(res);
    context.Post(MI_RESULT_OK);
}

void TestEmbeddedOperations_Class_Provider::Invoke_TestEmbeddedInstanceReturnKey20100609(
    Context&  context,
    const String& nameSpace,
    const TestEmbeddedOperations_Class& instance,
    const TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Class& in_param )
{
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Class res;
    X_TestEmbeddedInstanceMIReturnObject_Class inst;

    inst.id_value(20100609);

    res.MIReturn_value(inst);

    context.Post(res);
    context.Post(MI_RESULT_OK);
}

void TestEmbeddedOperations_Class_Provider::Invoke_TestEmbeddedObjectReturnKey20100609(
    Context&  context,
    const String& nameSpace,
    const TestEmbeddedOperations_Class& instance,
        const TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Class& in_param )
{
    TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Class res;
    X_TestEmbeddedObjectNotReferenced_Class inst;

    inst.ObjectID_value(20100609);

    res.MIReturn_value(inst);

    context.Post(res);
    context.Post(MI_RESULT_OK);
}


MI_END_NAMESPACE
MI_BEGIN_NAMESPACE
void TestEmbeddedOperations_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void TestEmbeddedOperations_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

MI_END_NAMESPACE
