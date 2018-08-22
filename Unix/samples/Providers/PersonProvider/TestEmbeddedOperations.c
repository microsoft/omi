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
#include "TestEmbeddedOperations.h"
#include "X_TestEmbeddedObjectNotReferenced.h"

// on CentOS 6
#if (__GNUC__==4 && __GNUC_MINOR__==4 && __OPTIMIZE__)
#pragma GCC diagnostic ignored "-Wuninitialized"
#endif

void MI_CALL TestEmbeddedOperations_Load(
    TestEmbeddedOperations_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestEmbeddedOperations_Unload(
    TestEmbeddedOperations_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestEmbeddedOperations_EnumerateInstances(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TestEmbeddedOperations_GetInstance(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestEmbeddedOperations* instanceName,
    const MI_PropertySet* propertySet)
{
    TestEmbeddedOperations res;   
    MSFT_Person person;
    const MSFT_Person*  threePersons[3];
    MSFT_Person threePersonsBuffer[3];
    
    if (context && context->ft)
    {
        if (!instanceName->key.exists || instanceName->key.value != 1)
        {
            MI_PostResult(context, MI_RESULT_NOT_FOUND);
            return;
        }

        MSFT_Person_Construct( &person, context );
        MSFT_Person_Construct( &threePersonsBuffer[0], context );
        MSFT_Person_Construct( &threePersonsBuffer[1], context );
        MSFT_Person_Construct( &threePersonsBuffer[2], context );

        threePersons[0] = &threePersonsBuffer[0];
        threePersons[1] = &threePersonsBuffer[1];
        threePersons[2] = &threePersonsBuffer[2];

        MSFT_Person_Set_Last(&person,MI_T("Smith"));
        MSFT_Person_Set_First(&person,MI_T("John"));
        MSFT_Person_Set_Key(&person, 7);

        TestEmbeddedOperations_Construct(&res, context);
        TestEmbeddedOperations_Set_key(&res, 1);
        TestEmbeddedOperations_Set_person(&res,&person);

        // add three persons
        MSFT_Person_Set_Last(&threePersonsBuffer[0],MI_T("Black"));
        MSFT_Person_Set_First(&threePersonsBuffer[0],MI_T("John"));
        MSFT_Person_Set_Key(&threePersonsBuffer[0], 7);

        MSFT_Person_Set_Last(&threePersonsBuffer[1],MI_T("White"));
        MSFT_Person_Set_First(&threePersonsBuffer[1],MI_T("Bill"));
        MSFT_Person_Set_Key(&threePersonsBuffer[1], 8);

        MSFT_Person_Set_Last(&threePersonsBuffer[2],MI_T("Brown"));
        MSFT_Person_Set_First(&threePersonsBuffer[2],MI_T("Ben"));
        MSFT_Person_Set_Key(&threePersonsBuffer[2], 9);


        TestEmbeddedOperations_Set_threePersons(&res, threePersons, 3);

        TestEmbeddedOperations_Post(&res, context);
        /* destruct all resources */     
        TestEmbeddedOperations_Destruct(&res);
        MSFT_Person_Destruct( &person);
        MSFT_Person_Destruct( &threePersonsBuffer[0]);
        MSFT_Person_Destruct( &threePersonsBuffer[1]);
        MSFT_Person_Destruct( &threePersonsBuffer[2]);
    }
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestEmbeddedOperations_CreateInstance(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestEmbeddedOperations* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TestEmbeddedOperations_ModifyInstance(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestEmbeddedOperations* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TestEmbeddedOperations_DeleteInstance(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestEmbeddedOperations* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TestEmbeddedOperations_Invoke_TestEmbedded(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestEmbeddedOperations* instanceName,
    const TestEmbeddedOperations_TestEmbedded* in)
{
    // INPUT:
    // objectsArray - 2 instances of MSFT_Base
    // objectSingle - MSFT_Person
    // testObjectsArray - 3 objects
    // testObjectSingle - not set

    // OUTPUT
    // objectsArray - 2 instances of MSFT_Animal iwth the same keys and species "test"
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

    TestEmbeddedOperations_TestEmbedded res;

    X_TestObject item;
    const X_TestObject* items[2];
    X_TestObject items_buf[2];
    MSFT_Animal obj_buf[2];
    const MI_Instance*    objs[2];
    unsigned int i, count = 0;
    MI_Uint64 id = 0;


    /* Construct parameters */
    for (i = 0; i < MI_COUNT(items); i++)
    {
        X_TestObject_Construct(&items_buf[i], context);
        items[i] = &items_buf[i];
    }

    for (i = 0; i < MI_COUNT(objs); i++)
    {
        MSFT_Animal_Construct(&obj_buf[i], context);
        objs[i] = MI_InstanceOf(&obj_buf[i]);
    }

    X_TestObject_Construct(&item, context);
    TestEmbeddedOperations_TestEmbedded_Construct(&res, context);


    /* get last two elements */
    if (in->testObjectsArray.exists && in->testObjectsArray.value.size > 1)
    {
        for ( i = in->testObjectsArray.value.size - 2; i < in->testObjectsArray.value.size; i++ )
        {
            items[count] = in->testObjectsArray.value.data[i];
            count++;
        }
        TestEmbeddedOperations_TestEmbedded_Set_testObjectsArray(&res, items, count);
    }

    if (in->testObjectsArray.exists)
    {
        for ( i = 0; i < in->testObjectsArray.value.size; i++ )
        {
            id += in->testObjectsArray.value.data[i]->id.value;
        }

        X_TestObject_Set_id(&item, id);
        TestEmbeddedOperations_TestEmbedded_Set_MIReturn(&res, &item);
    }

    if (in->objectsArray.exists)
    {
        // objectsArray

        for ( i = 0; i < in->objectsArray.value.size; i++ )
        {
            if (i == MI_COUNT(objs))
                break;

            MSFT_Animal_Set_Species(&obj_buf[i], MI_T("test"));
            MSFT_Animal_Set_Key(&obj_buf[i], ((MSFT_Base*)in->objectsArray.value.data[i])->Key.value);
        }

        TestEmbeddedOperations_TestEmbedded_Set_objectsArray(&res, objs, i);
    }

    TestEmbeddedOperations_TestEmbedded_Post(&res, context);

    /* Destruct parameters */
    for (i = 0; i < MI_COUNT(items); i++)
    {
        X_TestObject_Destruct(&items_buf[i]);
    }
    for (i = 0; i < MI_COUNT(objs); i++)
    {
        MSFT_Animal_Destruct(&obj_buf[i]);
    }

    X_TestObject_Destruct(&item);
    TestEmbeddedOperations_TestEmbedded_Destruct(&res);


    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestEmbeddedOperations_Invoke_TestEmbeddedInstanceReturnKey20100609(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestEmbeddedOperations* instanceName,
    const TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609* in)
{
    TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609 res;
    
    if (context && context->ft)
    {
        X_TestEmbeddedInstanceMIReturnObject inst;

        TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Construct(&res, context);
        X_TestEmbeddedInstanceMIReturnObject_Construct(&inst, context);

        X_TestEmbeddedInstanceMIReturnObject_Set_id(&inst, 20100609);

        TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Set_MIReturn(&res, &inst);

        TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Post(&res, context);

        TestEmbeddedOperations_TestEmbeddedInstanceReturnKey20100609_Destruct(&res);
        X_TestEmbeddedInstanceMIReturnObject_Destruct(&inst);
    }
    
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestEmbeddedOperations_Invoke_TestEmbeddedObjectReturnKey20100609(
    TestEmbeddedOperations_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestEmbeddedOperations* instanceName,
    const TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609* in)
{
    TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609 res;
    
    if (context && context->ft)
    {
        X_TestEmbeddedObjectNotReferenced inst;

        TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Construct(&res, context);
        X_TestEmbeddedObjectNotReferenced_Construct(&inst, context);

        X_TestEmbeddedObjectNotReferenced_Set_ObjectID(&inst, 20100609);

        TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Set_MIReturn(&res, MI_InstanceOf(&inst));

        TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Post(&res, context);

        TestEmbeddedOperations_TestEmbeddedObjectReturnKey20100609_Destruct(&res);
        X_TestEmbeddedObjectNotReferenced_Destruct(&inst);
    }
    
    MI_PostResult(context, MI_RESULT_OK);
}

