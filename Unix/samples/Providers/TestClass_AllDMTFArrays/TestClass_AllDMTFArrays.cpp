/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#include "MI.h"
#include "TestClass_AllDMTFArrays.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "common.h"
#include <limits.h>
#include <pal/format.h>

//  fix issue for undefine on HPUX 64bits
//  /usr/include/limits.h
//  /usr/include/aCC/limits.h
//  /usr/include/aCC_std/limits.h
#ifndef ULLONG_MAX
#  define ULLONG_MAX        (18446744073709551615ULL) 
#endif

#ifndef LLONG_MAX 
#  define LLONG_MAX         (9223372036854775807LL)
#endif


#define ONLOAD_CREATE_INSTANCES 4
std::vector<TestClass_AllDMTFArrays*> instanceStore;

void SetBoolArray(TestClass_AllDMTFArrays *instance, MI_Uint32 count)
{
    MI_Boolean* boolArray = (MI_Boolean *) PAL_Malloc(sizeof(MI_Boolean) * count);

    if (boolArray != NULL)
    {
        for(MI_Uint32 i=0; i < count; i++)
        {
            //boolArray[i] =  i % 2 ? MI_TRUE : MI_FALSE;
            if (i % 2 == 0)
                boolArray[i] = MI_TRUE;
            else
                boolArray[i] = MI_FALSE;
        }

        TestClass_AllDMTFArrays_Set_a_bool(instance, boolArray, count);
        PAL_Free(boolArray);
    }
}

void SetUint8Array(TestClass_AllDMTFArrays *instance, MI_Uint32 count)
{
    MI_Uint8* uint8Array = (MI_Uint8 *) PAL_Malloc(sizeof(MI_Uint8) * count);

    if (uint8Array != NULL)
    {
        for(MI_Uint32 i=0; i < count; i++)
        {
            uint8Array[i] =  (MI_Uint8) i % 255;
        }

        TestClass_AllDMTFArrays_Set_a_uint8(instance, uint8Array, count);
        PAL_Free(uint8Array);
    }
}

void SetSint8Array(TestClass_AllDMTFArrays *instance, MI_Uint32 count)
{
    MI_Sint8* sint8Array = (MI_Sint8 *) PAL_Malloc(sizeof(MI_Sint8) * count);

    if (sint8Array != NULL)
    {
        for(MI_Uint32 i=0; i < count; i++)
        {
            sint8Array[i] =  (MI_Sint8) (i % 128) * -1;
        }

        TestClass_AllDMTFArrays_Set_a_sint8(instance, sint8Array, count);
        PAL_Free(sint8Array);
    }
}

void SetUint16Array(TestClass_AllDMTFArrays *instance, MI_Uint32 count)
{
    MI_Uint16* uint16Array = (MI_Uint16 *) PAL_Malloc(sizeof(MI_Uint16) * count);
    
    if (uint16Array != NULL)
    {
        for(MI_Uint32 i=0; i < count; i++)
        {
            uint16Array[i] =  (MI_Uint16) i % 65536;
        }

        TestClass_AllDMTFArrays_Set_a_UINT16(instance, uint16Array, count);
        PAL_Free(uint16Array);
    }
}

void SetSint16Array(TestClass_AllDMTFArrays *instance, MI_Uint32 count)
{
    MI_Sint16* sint16Array = (MI_Sint16 *) PAL_Malloc(sizeof(MI_Sint16) * count);

    if (sint16Array != NULL)
    {
        for(MI_Uint32 i=0; i < count; i++)
        {
            sint16Array[i] =  (MI_Sint16) (i % 32768) * -1;
        }

        TestClass_AllDMTFArrays_Set_a_sint16(instance, sint16Array, count);
        PAL_Free(sint16Array);
    }
}

// Uint32:0~4,294,967,295(0xFFFFFFFF)
void SetUint32Array(TestClass_AllDMTFArrays *instance, MI_Uint32 count)
{
    MI_Uint32* uint32Array = (MI_Uint32 *) PAL_Malloc(sizeof(MI_Uint32) * count);

    if (uint32Array != NULL)
    {
        for(MI_Uint32 i=0; i < count; i++)
        {
            uint32Array[i] =  (MI_Uint32) i % ULONG_MAX;
        }

        TestClass_AllDMTFArrays_Set_a_uint32(instance, uint32Array, count);
        PAL_Free(uint32Array);
    }
}

// Sint32:-2,147,483,648(0x80000000)~2,147,483,647(0x7FFFFFFF)
void SetSint32Array(TestClass_AllDMTFArrays *instance, MI_Uint32 count)
{
    MI_Sint32* sint32Array = (MI_Sint32 *) PAL_Malloc(sizeof(MI_Sint32) * count);

    if (sint32Array != NULL)
    {
        for(MI_Uint32 i=0; i < count; i++)
        {
            sint32Array[i] =  (MI_Sint32) (i % LONG_MAX) * -1 ;
        }

        TestClass_AllDMTFArrays_Set_a_sint32(instance, sint32Array, count);
        PAL_Free(sint32Array);
    }
}

// Uint64:0~18,446,744,073,709,551,615(0xFFFFFFFFFFFFFFFFLL)
void SetUint64Array(TestClass_AllDMTFArrays *instance, MI_Uint32 count)
{
    MI_Uint64* uint64Array = (MI_Uint64 *) PAL_Malloc(sizeof(MI_Uint64) * count);

    if (uint64Array != NULL)
    {
        for(MI_Uint32 i=0; i < count; i++)
        {
            uint64Array[i] =  (MI_Uint64) i % ULLONG_MAX;
        }

        TestClass_AllDMTFArrays_Set_a_uint64(instance, uint64Array, count);
        PAL_Free(uint64Array);
    }
}

// Sint64:-9,223,372,036,854,775,808(0x8000000000000000)~9,223,372,036,854,775,807(0x7FFFFFFFFFFFFFFFLL)
void SetSint64Array(TestClass_AllDMTFArrays *instance, MI_Uint32 count)
{
    MI_Sint64* sint64Array = (MI_Sint64 *) PAL_Malloc(sizeof(MI_Sint64) * count);

    if (sint64Array != NULL)
    {
        for(MI_Uint64 i=0; i < count; i++)
        {
            sint64Array[i] =  (MI_Sint64) (i % LLONG_MAX) * -1;
        }

        TestClass_AllDMTFArrays_Set_a_sint64(instance, sint64Array, count);
        PAL_Free(sint64Array);
    }
}

void SetReal32Array(TestClass_AllDMTFArrays *instance, MI_Uint32 count)
{
    MI_Real32* real32Array = (MI_Real32 *) PAL_Malloc(sizeof(MI_Real32) * count);

    if (real32Array != NULL)
    {
        for(MI_Uint32 i=0; i < count; i++)
        {
            real32Array[i] =  (MI_Real32) i * 1.001 ;
        }

        TestClass_AllDMTFArrays_Set_a_rEal32(instance, real32Array, count);
        PAL_Free(real32Array);
    }
}

void SetReal64Array(TestClass_AllDMTFArrays *instance, MI_Uint32 count)
{
    MI_Real64* real64Array = (MI_Real64 *) PAL_Malloc(sizeof(MI_Real64) * count);

    if (real64Array != NULL)
    {
        for(MI_Uint32 i=0; i < count; i++)
        {
            real64Array[i] =  (MI_Real64) i * 1.001 ;
        }

        TestClass_AllDMTFArrays_Set_a_REAL64(instance, real64Array, count);
        PAL_Free(real64Array);
    }
}

void SetChar16Array(TestClass_AllDMTFArrays *instance, MI_Uint32 count)
{
    MI_Char16* char16Array = (MI_Char16 *) PAL_Malloc(sizeof(MI_Char16) * count);

    if (char16Array != NULL)
    {
        for(MI_Uint32 i=0; i < count; i++)
        {
            char16Array[i] =  (MI_Char16) (i % 65536) + 93 ;
        }

        TestClass_AllDMTFArrays_Set_a_char16(instance, char16Array, count);
        PAL_Free(char16Array);
    }
}

void SetStringArray(TestClass_AllDMTFArrays *instance, MI_Uint32 count)
{
    MI_Char ** stringArray = (MI_Char **) PAL_Malloc(sizeof(MI_Char*) * count);

    if (stringArray != NULL)
    {
        for(MI_Uint32 i=0; i < count; i++)
        {
            stringArray[i] = (MI_Char *) PAL_Malloc(sizeof(MI_Char) * (100) );
            memset((void *)stringArray[i], 0, sizeof(MI_Char) * 100);
            Stprintf(stringArray[i], 100, MI_T("Test String %d"), i);
        }

        TestClass_AllDMTFArrays_Set_a_string(instance, (const MI_Char **) stringArray, count);

        for(MI_Uint32 i=0; i < count; i++)
        {
            PAL_Free((void *)stringArray[i]);
        }

        PAL_Free(stringArray);
    }
}

void SetDateTimeArray(TestClass_AllDMTFArrays *instance, MI_Uint32 count)
{
    MI_Datetime *datetimeArray = (MI_Datetime *) PAL_Malloc(sizeof(MI_Datetime) * count);

    if (datetimeArray != NULL)
    {
        for(MI_Uint32 i=0; i < count; i++)
        {
            datetimeArray[i].isTimestamp = (MI_Uint32) (i % 2);

            datetimeArray[i].u.interval.days = i % 28;
            datetimeArray[i].u.interval.hours = i % 24;
            datetimeArray[i].u.interval.microseconds = i % 1000;
            datetimeArray[i].u.interval.minutes = i % 60;
            datetimeArray[i].u.interval.seconds = i %60;

            datetimeArray[i].u.timestamp.day = i % 28;
            datetimeArray[i].u.timestamp.hour = i % 24;
            datetimeArray[i].u.timestamp.microseconds = i % 1000;
            datetimeArray[i].u.timestamp.minute = i % 60;
            datetimeArray[i].u.timestamp.second = i % 60;
            datetimeArray[i].u.timestamp.utc = 830;
            datetimeArray[i].u.timestamp.year = 2000 + i;
        }

        TestClass_AllDMTFArrays_Set_a_DATETIME(instance, datetimeArray, count);
        PAL_Free(datetimeArray);
    }
}

void SetEmbeddedInstanceArray(MI_Context *context, TestClass_AllDMTFArrays *instance, MI_Uint32 count)
{
    TestClass_ForEmbedded **instanceArray = (TestClass_ForEmbedded **) PAL_Malloc(sizeof(TestClass_ForEmbedded*) * count);
    
    if (instanceArray != NULL)
    {
        TestClass_ForEmbedded temp;
        TestClass_ForEmbedded_Construct(&temp, context);

        for(MI_Uint32 i=0; i < count; i++)
        {
            TestClass_ForEmbedded_Clone(&temp, &instanceArray[i]);
            TestClass_ForEmbedded_Set_embeddedStringValue(instanceArray[i], MI_T("Test Embedded String"));
        }

        TestClass_AllDMTFArrays_Set_a_embeddedInstance(instance, instanceArray, count);

        for(MI_Uint32 i=0; i < count; i++)
        {
            TestClass_ForEmbedded_Delete(instanceArray[i]);
        }

        PAL_Free(instanceArray);

        TestClass_ForEmbedded_Destruct(&temp);
    }
}

void SetEmbeddedObjectArray(MI_Context *context, TestClass_AllDMTFArrays *instance, MI_Uint32 count)
{
    MI_Instance **objectArray = (MI_Instance **) PAL_Malloc(sizeof(MI_Instance*) * count);

    MI_Value val;

    for(MI_Uint32 i=0; i < count; i++)
    {
        MI_Context_NewDynamicInstance(context, MI_T("DynamicInstance"), 0, &objectArray[i]);
        val.uint32 = i;
        MI_Instance_AddElement(objectArray[i], MI_T("dynamicProperty"), &val, MI_UINT32, MI_FLAG_KEY);
    }

    TestClass_AllDMTFArrays_Set_a_embeddedObject(instance, objectArray, count);

    for(MI_Uint32 i=0; i < count; i++)
    {
        MI_Instance_Delete(objectArray[i]);
    }

    PAL_Free(objectArray);
}


void CreateInstances(MI_Context *context, unsigned int number)
{
    TestClass_AllDMTFArrays* instance = NULL;
    TestClass_AllDMTFArrays temp;
    TestClass_AllDMTFArrays_Construct(&temp, context);

    for(MI_Uint64 i = 0; i < number; i++)
    {
        TestClass_AllDMTFArrays_Clone(&temp, &instance);

        if(instance==NULL)
            continue;

        SetBoolArray(instance, number);    
        SetUint8Array(instance, number);
        SetSint8Array(instance, number);    
        SetUint16Array(instance, number);
        SetSint16Array(instance, number);
        SetUint32Array(instance, number);
        SetSint32Array(instance, number);
        SetUint64Array(instance, number);
        SetSint64Array(instance, number);
        SetReal32Array(instance, number);
        SetReal64Array(instance, number);
        SetChar16Array(instance, number);
        SetStringArray(instance, number);
        SetDateTimeArray(instance, number);

        //SetEmbeddedInstanceArray(context, instance, number);
        //SetEmbeddedObjectArray(context, instance, number);

        TestClass_AllDMTFArrays_Set_v_Key(instance, i);

        TestClass_ForEmbedded embedded;
        TestClass_ForEmbedded_Construct(&embedded, context);
        TestClass_ForEmbedded_Set_embeddedStringValue(&embedded, MI_T("embedded string"));

        TestClass_AllDMTFArrays_Set_embeddedReference(instance, &embedded);

        TestClass_ForEmbedded_Destruct(&embedded);

        instanceStore.push_back(instance);
    }

    TestClass_AllDMTFArrays_Destruct(&temp);
}

void MI_CALL TestClass_AllDMTFArrays_Load(
    TestClass_AllDMTFArrays_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = new TestClass_AllDMTFArrays_Self;
    (*self)->loadInstances = ONLOAD_CREATE_INSTANCES;

    if(instanceStore.size() == 0)
        CreateInstances(context, ONLOAD_CREATE_INSTANCES);

    MI_PostResult(context, MI_RESULT_OK);    
}

void MI_CALL TestClass_AllDMTFArrays_Unload(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context)
{
    for(MI_Uint32 i=0; i<instanceStore.size(); i++)
    {
        if(instanceStore[i])
        {
            TestClass_AllDMTFArrays_Delete(instanceStore[i]);
        }
    }

    instanceStore.clear();

    delete self;

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestClass_AllDMTFArrays_EnumerateInstances(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_Result result;
    TestClass_AllDMTFArrays* temp=NULL;

    for(MI_Uint32 i = 0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]==NULL)
            continue;
    
        temp=NULL;
        result = TestClass_AllDMTFArrays_Clone( instanceStore[i],  &temp );

        if(temp)
        {
            result = TestClass_AllDMTFArrays_Post(temp, context);
            TestClass_AllDMTFArrays_Destruct(temp);
        }

        if(result != MI_RESULT_OK)
        {
            //MI_PostResult(context, result);
            POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestClass_AllDMTFArrays_GetInstance(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_AllDMTFArrays* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            result = TestClass_AllDMTFArrays_Post(instanceStore[i], context);
            break;
        }
    } 

    if(result != MI_RESULT_OK)
    {
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));
    }

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_CreateInstance(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_AllDMTFArrays* newInstance)
{
    MI_Result result = MI_RESULT_FAILED;

    if(newInstance)
    {
        TestClass_AllDMTFArrays temp;
        TestClass_AllDMTFArrays_Construct(&temp, context );

        TestClass_AllDMTFArrays_Set_a_bool(&temp, newInstance->a_bool.value.data, newInstance->a_bool.value.size);
        TestClass_AllDMTFArrays_Set_a_char16(&temp,  newInstance->a_char16.value.data, newInstance->a_char16.value.size);
        TestClass_AllDMTFArrays_Set_a_DATETIME(&temp, newInstance->a_DATETIME.value.data, newInstance->a_DATETIME.value.size);
        TestClass_AllDMTFArrays_Set_a_rEal32(&temp, newInstance->a_rEal32.value.data, newInstance->a_rEal32.value.size);
        TestClass_AllDMTFArrays_Set_a_REAL64(&temp, newInstance->a_REAL64.value.data, newInstance->a_REAL64.value.size);
        TestClass_AllDMTFArrays_Set_a_sint16(&temp, newInstance->a_sint16.value.data, newInstance->a_sint16.value.size);
        TestClass_AllDMTFArrays_Set_a_sint32(&temp, newInstance->a_sint32.value.data, newInstance->a_sint32.value.size);
        TestClass_AllDMTFArrays_Set_a_sint64(&temp, newInstance->a_sint64.value.data, newInstance->a_sint64.value.size);
        TestClass_AllDMTFArrays_Set_a_sint8(&temp, newInstance->a_sint8.value.data, newInstance->a_sint8.value.size);
        TestClass_AllDMTFArrays_Set_a_string(&temp, (const MI_Char**) newInstance->a_string.value.data, newInstance->a_string.value.size);
        TestClass_AllDMTFArrays_Set_a_UINT16(&temp, newInstance->a_UINT16.value.data, newInstance->a_UINT16.value.size);
        TestClass_AllDMTFArrays_Set_a_uint32(&temp, newInstance->a_uint32.value.data, newInstance->a_uint32.value.size);
        TestClass_AllDMTFArrays_Set_a_uint64(&temp, newInstance->a_uint64.value.data, newInstance->a_uint64.value.size);
        TestClass_AllDMTFArrays_Set_a_uint8(&temp, newInstance->a_uint8.value.data, newInstance->a_uint8.value.size);
        TestClass_AllDMTFArrays_Set_embeddedReference(&temp, newInstance->embeddedReference.value);

        TestClass_AllDMTFArrays_Set_a_embeddedInstance(&temp, newInstance->a_embeddedInstance.value.data, newInstance->a_embeddedInstance.value.size);

        TestClass_AllDMTFArrays_Set_a_embeddedObject(&temp, newInstance->a_embeddedObject.value.data, newInstance->a_embeddedObject.value.size);

        TestClass_AllDMTFArrays_Set_v_Key(&temp, newInstance->v_Key.value);

        result = TestClass_AllDMTFArrays_Post(&temp, context);

        TestClass_AllDMTFArrays *instanceToStore = NULL;
        TestClass_AllDMTFArrays_Clone(&temp, &instanceToStore);

        TestClass_AllDMTFArrays_Destruct(&temp);

        instanceStore.push_back(instanceToStore);
    }

    if(result != MI_RESULT_OK)
    {
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));
    }

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_ModifyInstance(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_AllDMTFArrays* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_Result result = MI_RESULT_OK;
    MI_Uint32 count;

    result = MI_RESULT_OK;    

    MI_Value val;
    MI_Type type;

    MI_Uint32 flags;

    if (propertySet != NULL)
    {
        MI_PropertySet_GetElementCount(propertySet, &count);

        if(count == 0)
        {
            //MI_PostResult(context,MI_RESULT_OK);
            POST_ERROR(context, MI_RESULT_OK, MI_RESULT_TYPE_MI, MI_T("Property count is 0"));
        }
    }
    else
    {
        count = modifiedInstance->__instance.classDecl->numProperties;

        bool foundInstance = false;
        MI_Uint32 index = instanceStore.size();

        for(MI_Uint32 i = 0; i < instanceStore.size(); i++)
        {
            if(((instanceStore)[i])->v_Key.value == modifiedInstance->v_Key.value)
            {    
                foundInstance = true;
                index = i;
                break;
            }
        }

        if(!foundInstance)
        {
            //MI_PostResult(context, MI_RESULT_NOT_FOUND);
            POST_ERROR(context, MI_RESULT_NOT_FOUND, MI_RESULT_TYPE_MI, MI_T("No instance found"));
        }

        const MI_Char* name = NULL;
        TestClass_AllDMTFArrays* test = (instanceStore)[index];

        for(MI_Uint32 i=0 ; i < count; i++)
        {
            if((result = MI_Instance_GetElementAt(&(modifiedInstance->__instance), i, &name, &val, &type, &flags)) != MI_RESULT_OK)
            {
                //MI_PostResult(context, result);
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot get element of instance"));
            }
            
            if((flags & MI_FLAG_NULL) == 0)
            {
                /*Only MI_FLAG_NULL, MI_FLAG_BORROW and MI_FLAG_ADOPT are valid for SetElement operation*/
                MI_Uint32 validFlags = (MI_FLAG_NULL|MI_FLAG_BORROW|MI_FLAG_ADOPT)&flags;

                if((result = MI_Instance_SetElement( (MI_Instance *) &(test->__instance), (MI_Char *) name, (MI_Value *) &val, (MI_Type) type, (MI_Uint32) validFlags)) != MI_RESULT_OK)
                {
                    //MI_PostResult(context, result);
                    POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot set element of instance"));
                }
            }
        }

        TestClass_AllDMTFArrays_Post(test, context);
    }

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_DeleteInstance(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_AllDMTFArrays* instanceName)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    std::vector<TestClass_AllDMTFArrays*>::iterator it;

    for(it = instanceStore.begin(); it != instanceStore.end(); it++)
    {
        if(instanceName->v_Key.value == (*it)->v_Key.value)
        {
            TestClass_AllDMTFArrays_Delete(*it);
            instanceStore.erase(it);	
            result = MI_RESULT_OK;
            break;
        }
    }

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_GetReal32Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetReal32Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_GetReal32Array real32Array;
    TestClass_AllDMTFArrays_GetReal32Array_Construct(&real32Array, context);

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFArrays_GetReal32Array_Set_MIReturn(&real32Array, 0);
            TestClass_AllDMTFArrays_GetReal32Array_Set_real32Array(&real32Array, instanceStore[i]->a_rEal32.value.data, instanceStore[i]->a_rEal32.value.size);

            result = TestClass_AllDMTFArrays_GetReal32Array_Post(&real32Array, context);
            break;
        }
    }

    TestClass_AllDMTFArrays_GetReal32Array_Destruct(&real32Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_SetReal32Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetReal32Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_SetReal32Array real32Array;
    TestClass_AllDMTFArrays_SetReal32Array_Construct(&real32Array, context);

    if(in->real32Array.exists == MI_TRUE)
    {
        for(MI_Uint32 i=0; i < instanceStore.size(); i++)
        {
            if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
            {
                result = TestClass_AllDMTFArrays_Set_a_rEal32(instanceStore[i], in->real32Array.value.data, in->real32Array.value.size);			
                TestClass_AllDMTFArrays_SetReal32Array_Set_MIReturn(&real32Array, 0);
                result = TestClass_AllDMTFArrays_SetReal32Array_Post(&real32Array, context);
                break;
            }
        }
    }
    else
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }

    TestClass_AllDMTFArrays_SetReal32Array_Destruct(&real32Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_GetReal64Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetReal64Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_GetReal64Array real64Array;
    TestClass_AllDMTFArrays_GetReal64Array_Construct(&real64Array, context);

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFArrays_GetReal64Array_Set_MIReturn(&real64Array, 0);
            TestClass_AllDMTFArrays_GetReal64Array_Set_real64Array(&real64Array, instanceStore[i]->a_REAL64.value.data, instanceStore[i]->a_REAL64.value.size);

            result = TestClass_AllDMTFArrays_GetReal64Array_Post(&real64Array, context);
            break;
        }
    }

    TestClass_AllDMTFArrays_GetReal64Array_Destruct(&real64Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_SetReal64Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetReal64Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_SetReal64Array real64Array;
    TestClass_AllDMTFArrays_SetReal64Array_Construct(&real64Array, context);

    if(in->real64Array.exists)
    {
        for(MI_Uint32 i=0; i < instanceStore.size(); i++)
        {
            if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
            {
                result = TestClass_AllDMTFArrays_Set_a_REAL64(instanceStore[i], in->real64Array.value.data, in->real64Array.value.size);			
                TestClass_AllDMTFArrays_SetReal64Array_Set_MIReturn(&real64Array, 0);
                result = TestClass_AllDMTFArrays_SetReal64Array_Post(&real64Array, context);
                break;
            }
        }
    }
    else
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }

    TestClass_AllDMTFArrays_SetReal64Array_Destruct(&real64Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_GetChar16Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetChar16Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_GetChar16Array char16Array;
    TestClass_AllDMTFArrays_GetChar16Array_Construct(&char16Array, context);

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFArrays_GetChar16Array_Set_MIReturn(&char16Array, 0);
            TestClass_AllDMTFArrays_GetChar16Array_Set_charArray(&char16Array, instanceStore[i]->a_char16.value.data, instanceStore[i]->a_char16.value.size);

            result = TestClass_AllDMTFArrays_GetChar16Array_Post(&char16Array, context);
            break;
        }
    }

    TestClass_AllDMTFArrays_GetChar16Array_Destruct(&char16Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_SetChar16Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetChar16Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_SetChar16Array char16Array;
    TestClass_AllDMTFArrays_SetChar16Array_Construct(&char16Array, context);

    if(in->charArray.exists == MI_TRUE)
    {
        for(MI_Uint32 i=0; i < instanceStore.size(); i++)
        {
            if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
            {   			
                TestClass_AllDMTFArrays_Set_a_char16(instanceStore[i], in->charArray.value.data, in->charArray.value.size);			
                TestClass_AllDMTFArrays_SetChar16Array_Set_MIReturn(&char16Array, 0);
                result = TestClass_AllDMTFArrays_SetChar16Array_Post(&char16Array, context);
                break;
            }
        }
    }
    else
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }

    TestClass_AllDMTFArrays_SetChar16Array_Destruct(&char16Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_GetStringArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetStringArray* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_GetStringArray stringArray;
    TestClass_AllDMTFArrays_GetStringArray_Construct(&stringArray, context);

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFArrays_GetStringArray_Set_MIReturn(&stringArray, 0);
            TestClass_AllDMTFArrays_GetStringArray_Set_StringArray(&stringArray, (const MI_Char **) instanceStore[i]->a_string.value.data, instanceStore[i]->a_string.value.size);

            result = TestClass_AllDMTFArrays_GetStringArray_Post(&stringArray, context);
            break;
        }
    }

    TestClass_AllDMTFArrays_GetStringArray_Destruct(&stringArray);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_SetStringArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetStringArray* in)
{
    MI_Result result = MI_RESULT_OK;

    TestClass_AllDMTFArrays_SetStringArray stringArray;
    TestClass_AllDMTFArrays_SetStringArray_Construct(&stringArray, context);		

    if(in->StringArray.exists == MI_TRUE)
    {
        for(MI_Uint32 i=0; i < instanceStore.size(); i++)
        {
            if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
            {   	
                TestClass_AllDMTFArrays_Set_a_string(instanceStore[i], (const MI_Char **) in->StringArray.value.data, in->StringArray.value.size);			
                TestClass_AllDMTFArrays_SetStringArray_Set_MIReturn(&stringArray, 0);
                result = TestClass_AllDMTFArrays_SetStringArray_Post(&stringArray, context);
                break;
            }
        }
    }
    else
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }

    TestClass_AllDMTFArrays_SetStringArray_Destruct(&stringArray);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_GetDateTimeArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetDateTimeArray* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_GetDateTimeArray datetimeArray;
    TestClass_AllDMTFArrays_GetDateTimeArray_Construct(&datetimeArray, context);

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFArrays_GetDateTimeArray_Set_MIReturn(&datetimeArray, 0);
            TestClass_AllDMTFArrays_GetDateTimeArray_Set_datetimeArray(&datetimeArray, instanceStore[i]->a_DATETIME.value.data, instanceStore[i]->a_DATETIME.value.size);

            result = TestClass_AllDMTFArrays_GetDateTimeArray_Post(&datetimeArray, context);
            break;
        }
    }

    TestClass_AllDMTFArrays_GetDateTimeArray_Destruct(&datetimeArray);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_SetdatetimeArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetdatetimeArray* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_SetdatetimeArray dateArray;
    TestClass_AllDMTFArrays_SetdatetimeArray_Construct(&dateArray, context);

    if(in->datetimeArray.exists == MI_TRUE)
    {
        for(MI_Uint32 i=0; i < instanceStore.size(); i++)
        {
            if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
            {            			
                result = TestClass_AllDMTFArrays_Set_a_DATETIME(instanceStore[i], in->datetimeArray.value.data, in->datetimeArray.value.size);			
                TestClass_AllDMTFArrays_SetdatetimeArray_Set_MIReturn(&dateArray, 0);
                result = TestClass_AllDMTFArrays_SetdatetimeArray_Post(&dateArray, context);
                break;
            }
        }
    }
    else
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }

    TestClass_AllDMTFArrays_SetdatetimeArray_Destruct(&dateArray);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_GetReferenceArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetReferenceArray* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_GetReferenceArray refArray;
    TestClass_AllDMTFArrays_GetReferenceArray_Construct(&refArray, context);

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFArrays_GetReferenceArray_Set_MIReturn(&refArray, 0);
            TestClass_AllDMTFArrays_GetReferenceArray_Set_embeddedRefArray(&refArray, &instanceStore[i]->embeddedReference.value, 1);

            result = TestClass_AllDMTFArrays_GetReferenceArray_Post(&refArray, context);		
            break;
        }
    }

    TestClass_AllDMTFArrays_GetReferenceArray_Destruct(&refArray);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_SetReferenceArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetReferenceArray* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_SetReferenceArray refArray;
    TestClass_AllDMTFArrays_SetReferenceArray_Construct(&refArray, context);

    if(in->embeddedRefArray.exists == MI_TRUE)
    {
        for(MI_Uint32 i=0; i < instanceStore.size(); i++)
        {
            if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
            {            			
                TestClass_AllDMTFArrays_Set_embeddedReference(instanceStore[i], in->embeddedRefArray.value.data[0]);			
                TestClass_AllDMTFArrays_SetReferenceArray_Set_MIReturn(&refArray, 0);
                result = TestClass_AllDMTFArrays_SetReferenceArray_Post(&refArray, context);
                break;
            }
        }
    }
    else
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }

    TestClass_AllDMTFArrays_SetReferenceArray_Destruct(&refArray);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_GetBooleanArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetBooleanArray* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_GetBooleanArray boolArray;
    TestClass_AllDMTFArrays_GetBooleanArray_Construct(&boolArray, context);

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {


            TestClass_AllDMTFArrays_GetBooleanArray_Set_MIReturn(&boolArray, 0);
            TestClass_AllDMTFArrays_GetBooleanArray_Set_booleanArray(&boolArray, instanceStore[i]->a_bool.value.data, instanceStore[i]->a_bool.value.size);

            result = TestClass_AllDMTFArrays_GetBooleanArray_Post(&boolArray, context);		
            break;
        }
    }

    TestClass_AllDMTFArrays_GetBooleanArray_Destruct(&boolArray);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_SetBooleanArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetBooleanArray* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_SetBooleanArray boolArray;
    TestClass_AllDMTFArrays_SetBooleanArray_Construct(&boolArray, context);

    if(in->booleanArray.exists == MI_TRUE)
    {
        for(MI_Uint32 i=0; i < instanceStore.size(); i++)
        {
            if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
            {            			
                TestClass_AllDMTFArrays_Set_a_bool(instanceStore[i], in->booleanArray.value.data, in->booleanArray.value.size);			
                TestClass_AllDMTFArrays_SetBooleanArray_Set_MIReturn(&boolArray, 0);
                result = TestClass_AllDMTFArrays_SetBooleanArray_Post(&boolArray, context);
                break;
            }
        }
    }
    else
    {
        result = MI_RESULT_INVALID_PARAMETER;            
    }

    TestClass_AllDMTFArrays_SetBooleanArray_Destruct(&boolArray);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_GetUint8Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetUint8Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_GetUint8Array uint8Array;
    TestClass_AllDMTFArrays_GetUint8Array_Construct(&uint8Array, context);

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFArrays_GetUint8Array_Set_MIReturn(&uint8Array, 0);
            TestClass_AllDMTFArrays_GetUint8Array_Set_uint8Array(&uint8Array, instanceStore[i]->a_uint8.value.data, instanceStore[i]->a_uint8.value.size);

            result = TestClass_AllDMTFArrays_GetUint8Array_Post(&uint8Array, context);		
            break;
        }
    }

    TestClass_AllDMTFArrays_GetUint8Array_Destruct(&uint8Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_SetUint8Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetUint8Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_SetUint8Array uint8Array;
    TestClass_AllDMTFArrays_SetUint8Array_Construct(&uint8Array, context);			

    if(in->uint8Array.exists == MI_TRUE)
    {
        for(MI_Uint32 i=0; i < instanceStore.size(); i++)
        {
            if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
            {

                TestClass_AllDMTFArrays_Set_a_uint8(instanceStore[i], in->uint8Array.value.data, in->uint8Array.value.size);			
                TestClass_AllDMTFArrays_SetUint8Array_Set_MIReturn(&uint8Array, 0);
                result = TestClass_AllDMTFArrays_SetUint8Array_Post(&uint8Array, context);
                break;
            }
        }
    }
    else
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }

    TestClass_AllDMTFArrays_SetUint8Array_Destruct(&uint8Array);			

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_GetSint8Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetSint8Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_GetSint8Array sint8Array;
    TestClass_AllDMTFArrays_GetSint8Array_Construct(&sint8Array, context);

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {


            TestClass_AllDMTFArrays_GetSint8Array_Set_MIReturn(&sint8Array, 0);
            TestClass_AllDMTFArrays_GetSint8Array_Set_sint8Array(&sint8Array, instanceStore[i]->a_sint8.value.data, instanceStore[i]->a_sint8.value.size);

            result = TestClass_AllDMTFArrays_GetSint8Array_Post(&sint8Array, context);		
            break;
        }
    }

    TestClass_AllDMTFArrays_GetSint8Array_Destruct(&sint8Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_SetSint8Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetSint8Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_SetSint8Array sint8Array;
    TestClass_AllDMTFArrays_SetSint8Array_Construct(&sint8Array, context);

    if(in->sint8Array.exists == MI_TRUE)
    {
        for(MI_Uint32 i=0; i < instanceStore.size(); i++)
        {
            if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
            {

                TestClass_AllDMTFArrays_Set_a_sint8(instanceStore[i], in->sint8Array.value.data, in->sint8Array.value.size);			
                TestClass_AllDMTFArrays_SetSint8Array_Set_MIReturn(&sint8Array, 0);
                result = TestClass_AllDMTFArrays_SetSint8Array_Post(&sint8Array, context);
                break;
            }
        }
    }
    else
    {
        result = MI_RESULT_INVALID_PARAMETER;       
    }

    TestClass_AllDMTFArrays_SetSint8Array_Destruct(&sint8Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_GetUint16Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetUint16Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_GetUint16Array uint16Array;
    TestClass_AllDMTFArrays_GetUint16Array_Construct(&uint16Array, context);

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFArrays_GetUint16Array_Set_MIReturn(&uint16Array, 0);
            TestClass_AllDMTFArrays_GetUint16Array_Set_uint16Array(&uint16Array, instanceStore[i]->a_UINT16.value.data, instanceStore[i]->a_UINT16.value.size);

            result = TestClass_AllDMTFArrays_GetUint16Array_Post(&uint16Array, context);		
            break;
        }
    }

    TestClass_AllDMTFArrays_GetUint16Array_Destruct(&uint16Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_SetUint16Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetUint16Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_SetUint16Array uint16Array;
    TestClass_AllDMTFArrays_SetUint16Array_Construct(&uint16Array, context);

    if(in->uint16Array.exists == MI_TRUE)
    {
        for(MI_Uint32 i=0; i < instanceStore.size(); i++)
        {
            if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
            {

                TestClass_AllDMTFArrays_Set_a_UINT16(instanceStore[i], in->uint16Array.value.data, in->uint16Array.value.size);			
                TestClass_AllDMTFArrays_SetUint16Array_Set_MIReturn(&uint16Array, 0);
                result = TestClass_AllDMTFArrays_SetUint16Array_Post(&uint16Array, context);
                break;
            }
        }
    }
    else
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }

    TestClass_AllDMTFArrays_SetUint16Array_Destruct(&uint16Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_GetSint16Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetSint16Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_GetSint16Array sint16Array;
    TestClass_AllDMTFArrays_GetSint16Array_Construct(&sint16Array, context);

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFArrays_GetSint16Array_Set_MIReturn(&sint16Array, 0);
            TestClass_AllDMTFArrays_GetSint16Array_Set_sint16Array(&sint16Array, instanceStore[i]->a_sint16.value.data, instanceStore[i]->a_sint16.value.size);

            result = TestClass_AllDMTFArrays_GetSint16Array_Post(&sint16Array, context);		
            break;
        }
    }

    TestClass_AllDMTFArrays_GetSint16Array_Destruct(&sint16Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_SetSint16Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetSint16Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_SetSint16Array sint16Array;
    TestClass_AllDMTFArrays_SetSint16Array_Construct(&sint16Array, context);

    if(in->sint16Array.exists == MI_TRUE)
    {
        for(MI_Uint32 i=0; i < instanceStore.size(); i++)
        {
            if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
            {            			
                TestClass_AllDMTFArrays_Set_a_sint16(instanceStore[i], in->sint16Array.value.data, in->sint16Array.value.size);			
                TestClass_AllDMTFArrays_SetSint16Array_Set_MIReturn(&sint16Array, 0);
                result = TestClass_AllDMTFArrays_SetSint16Array_Post(&sint16Array, context);
                break;
            }
        }
    }
    else
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }

    TestClass_AllDMTFArrays_SetSint16Array_Destruct(&sint16Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_GetUint32Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetUint32Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_GetUint32Array uint32Array;
    TestClass_AllDMTFArrays_GetUint32Array_Construct(&uint32Array, context);

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFArrays_GetUint32Array_Set_MIReturn(&uint32Array, 0);
            TestClass_AllDMTFArrays_GetUint32Array_Set_uint32Array(&uint32Array, instanceStore[i]->a_uint32.value.data, instanceStore[i]->a_uint32.value.size);

            result = TestClass_AllDMTFArrays_GetUint32Array_Post(&uint32Array, context);		
            break;
        }
    }

    TestClass_AllDMTFArrays_GetUint32Array_Destruct(&uint32Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_SetUint32Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetUint32Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_SetUint32Array uint32Array;
    TestClass_AllDMTFArrays_SetUint32Array_Construct(&uint32Array, context);

    if(in->uint32Array.exists == MI_TRUE)
    {
        for(MI_Uint32 i=0; i < instanceStore.size(); i++)
        {
            if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
            {            			
                TestClass_AllDMTFArrays_Set_a_uint32(instanceStore[i], in->uint32Array.value.data, in->uint32Array.value.size);			
                TestClass_AllDMTFArrays_SetUint32Array_Set_MIReturn(&uint32Array, 0);
                result = TestClass_AllDMTFArrays_SetUint32Array_Post(&uint32Array, context);
                break;
            }
        }
    }
    else
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }

    TestClass_AllDMTFArrays_SetUint32Array_Destruct(&uint32Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_GetSint32Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetSint32Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_GetSint32Array sint32Array;
    TestClass_AllDMTFArrays_GetSint32Array_Construct(&sint32Array, context);

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFArrays_GetSint32Array_Set_MIReturn(&sint32Array, 0);
            TestClass_AllDMTFArrays_GetSint32Array_Set_sint32Array(&sint32Array, instanceStore[i]->a_sint32.value.data, instanceStore[i]->a_sint32.value.size);

            result = TestClass_AllDMTFArrays_GetSint32Array_Post(&sint32Array, context);		
            break;
        }
    }

    TestClass_AllDMTFArrays_GetSint32Array_Destruct(&sint32Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_SetSint32Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetSint32Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_SetSint32Array sint32Array;
    TestClass_AllDMTFArrays_SetSint32Array_Construct(&sint32Array, context);

    if(in->sint32Array.exists == MI_TRUE)
    {
        for(MI_Uint32 i=0; i < instanceStore.size(); i++)
        {
            if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
            {            			
                TestClass_AllDMTFArrays_Set_a_sint32(instanceStore[i], in->sint32Array.value.data, in->sint32Array.value.size);			
                TestClass_AllDMTFArrays_SetSint32Array_Set_MIReturn(&sint32Array, 0);
                result = TestClass_AllDMTFArrays_SetSint32Array_Post(&sint32Array, context);
                break;
            }
        }
    }
    else
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }

    TestClass_AllDMTFArrays_SetSint32Array_Destruct(&sint32Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_GetUint64Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetUint64Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_GetUint64Array uint64Array;
    TestClass_AllDMTFArrays_GetUint64Array_Construct(&uint64Array, context);

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFArrays_GetUint64Array_Set_MIReturn(&uint64Array, 0);
            TestClass_AllDMTFArrays_GetUint64Array_Set_uint64Array(&uint64Array, instanceStore[i]->a_uint64.value.data, instanceStore[i]->a_uint64.value.size);

            result = TestClass_AllDMTFArrays_GetUint64Array_Post(&uint64Array, context);		
            break;
        }
    }

    TestClass_AllDMTFArrays_GetUint64Array_Destruct(&uint64Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_SetUint64Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetUint64Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_SetUint64Array uint64Array;
    TestClass_AllDMTFArrays_SetUint64Array_Construct(&uint64Array, context);

    if(in->uint64Array.exists == MI_TRUE)
    {
        for(MI_Uint32 i=0; i < instanceStore.size(); i++)
        {
            if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
            {            			
                TestClass_AllDMTFArrays_Set_a_uint64(instanceStore[i], in->uint64Array.value.data, in->uint64Array.value.size);			
                TestClass_AllDMTFArrays_SetUint64Array_Set_MIReturn(&uint64Array, 0);
                result = TestClass_AllDMTFArrays_SetUint64Array_Post(&uint64Array, context);
                break;
            }
        }
    }
    else
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }

    TestClass_AllDMTFArrays_SetUint64Array_Destruct(&uint64Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_GetSint64Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetSint64Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_GetSint64Array sint64Array;
    TestClass_AllDMTFArrays_GetSint64Array_Construct(&sint64Array, context);

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFArrays_GetSint64Array_Set_MIReturn(&sint64Array, 0);
            TestClass_AllDMTFArrays_GetSint64Array_Set_sint64Array(&sint64Array, instanceStore[i]->a_sint64.value.data, instanceStore[i]->a_sint64.value.size);

            result = TestClass_AllDMTFArrays_GetSint64Array_Post(&sint64Array, context);		
            break;
        }
    }

    TestClass_AllDMTFArrays_GetSint64Array_Destruct(&sint64Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_SetSint64Array(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetSint64Array* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_SetSint64Array sint64Array;
    TestClass_AllDMTFArrays_SetSint64Array_Construct(&sint64Array, context);

    if(in->sint64Array.exists == MI_TRUE)
    {
        for(MI_Uint32 i=0; i < instanceStore.size(); i++)
        {
            if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
            {            			
                TestClass_AllDMTFArrays_Set_a_sint64(instanceStore[i], in->sint64Array.value.data, in->sint64Array.value.size);			
                TestClass_AllDMTFArrays_SetSint64Array_Set_MIReturn(&sint64Array, 0);
                result = TestClass_AllDMTFArrays_SetSint64Array_Post(&sint64Array, context);
                break;
            }
        }
    }
    else
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }

    TestClass_AllDMTFArrays_SetSint64Array_Destruct(&sint64Array);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_GetEmbeddedInstanceArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetEmbeddedInstanceArray* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_GetEmbeddedInstanceArray embInstanceArray;
    TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_Construct(&embInstanceArray, context);

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_Set_MIReturn(&embInstanceArray, 0);
            TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_Set_embeddedInstanceArray(&embInstanceArray, instanceStore[i]->a_embeddedInstance.value.data, instanceStore[i]->a_embeddedInstance.value.size);

            result = TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_Post(&embInstanceArray, context);		
            break;
        }
    }

    TestClass_AllDMTFArrays_GetEmbeddedInstanceArray_Destruct(&embInstanceArray);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_SetEmbeddedInstanceArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetEmbeddedInstanceArray* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_SetEmbeddedInstanceArray embInstanceArray;
    TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_Construct(&embInstanceArray, context);	

    if(in->embeddedInstanceArray.exists == MI_TRUE)
    {
        for(MI_Uint32 i=0; i < instanceStore.size(); i++)
        {
            if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
            {           		
                TestClass_AllDMTFArrays_Set_a_embeddedInstance(instanceStore[i], in->embeddedInstanceArray.value.data, in->embeddedInstanceArray.value.size);			
                TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_Set_MIReturn(&embInstanceArray, 0);
                result = TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_Post(&embInstanceArray, context);
                break;
            }
        }
    }
    else
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }

    TestClass_AllDMTFArrays_SetEmbeddedInstanceArray_Destruct(&embInstanceArray);	

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_GetEmbeddedObjectArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_GetEmbeddedObjectArray* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_GetEmbeddedObjectArray embObjectArray;
    TestClass_AllDMTFArrays_GetEmbeddedObjectArray_Construct(&embObjectArray, context);

    for(MI_Uint32 i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFArrays_GetEmbeddedObjectArray_Set_MIReturn(&embObjectArray, 0);
            TestClass_AllDMTFArrays_GetEmbeddedObjectArray_Set_embeddedObjectArray(&embObjectArray, instanceStore[i]->a_embeddedObject.value.data, instanceStore[i]->a_embeddedObject.value.size);

            result = TestClass_AllDMTFArrays_GetEmbeddedObjectArray_Post(&embObjectArray, context);		
            break;
        }
    }

    TestClass_AllDMTFArrays_GetEmbeddedObjectArray_Destruct(&embObjectArray);

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFArrays_Invoke_SetEmbeddedObjectArray(
    TestClass_AllDMTFArrays_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFArrays* instanceName,
    const TestClass_AllDMTFArrays_SetEmbeddedObjectArray* in)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    TestClass_AllDMTFArrays_SetEmbeddedObjectArray embObjectArray;
    TestClass_AllDMTFArrays_SetEmbeddedObjectArray_Construct(&embObjectArray, context);	

    if(in->embeddedObjectArray.exists == MI_TRUE)
    {
        for(MI_Uint32 i=0; i < instanceStore.size(); i++)
        {
            if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
            {            		
                TestClass_AllDMTFArrays_Set_a_embeddedObject(instanceStore[i], in->embeddedObjectArray.value.data, in->embeddedObjectArray.value.size);			
                TestClass_AllDMTFArrays_SetEmbeddedObjectArray_Set_MIReturn(&embObjectArray, 0);
                result = TestClass_AllDMTFArrays_SetEmbeddedObjectArray_Post(&embObjectArray, context);
                break;
            }
        }
    }
    else
    {
        result = MI_RESULT_INVALID_PARAMETER;
    }

    TestClass_AllDMTFArrays_SetEmbeddedObjectArray_Destruct(&embObjectArray);	

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

    MI_PostResult(context, result);
}
