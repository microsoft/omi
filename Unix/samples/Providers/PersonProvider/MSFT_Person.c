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
#include "MSFT_Person.h"
#include "CIM_Error.h"
#include "My_CIM_Error.h"
#include <string.h>
#include <stdio.h>

static MSFT_Person* _data[10];
static const size_t _SIZE = MI_COUNT(_data);
static size_t _size = 0;

void MI_CALL MSFT_Person_Load(
    MSFT_Person_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_Person_Unload(
    MSFT_Person_Self* self,
    MI_Context* context)
{
    size_t i;

    /* Delete all instances */
    for (i = 0; i < _size; i++)
        MSFT_Person_Delete(_data[i]);

    _size = 0;

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_Person_EnumerateInstances(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    size_t i;

    /* Run some tests */
    //ATN! memleak!  
    //test1(context);

    /* Enumerate all instances */
    for (i = 0; i < _size; i++)
    {
        MSFT_Person_Post(_data[i], context);
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_Person_GetInstance(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Person* instanceName,
    const MI_PropertySet* propertySet)
{
    size_t i;
    MI_Boolean flag;

    if (propertySet && MI_PropertySet_ContainsElement(propertySet, 
        MI_T("blahblahblah"), &flag) == MI_RESULT_OK && flag == MI_BOOLEAN)
    {
    }

    if (instanceName->Key.value == 777)
    {
        MSFT_Person res;

        MSFT_Person_Construct(&res, context);
        MSFT_Person_Set_Key(&res, 777);
        MSFT_Person_Set_Species(&res, MI_T("c-provider"));
        MSFT_Person_Set_First(&res, MI_T("Test"));
        MSFT_Person_Set_Last(&res, MI_T("-C- Provider"));
        MSFT_Person_Post(&res, context);
        MSFT_Person_Destruct(&res);
        MI_PostResult(context, MI_RESULT_OK);
        return;
    }
    else if (instanceName->Key.value == 9999)
    {
        CIM_Error error;

        CIM_Error_Construct(&error, context);

        CIM_Error_Set_CIMStatusCode(&error, MI_RESULT_SERVER_IS_SHUTTING_DOWN);
        CIM_Error_SetPtr_Message(&error, MI_T("This is a test CIM Error"));
        CIM_Error_SetPtr_CIMStatusCodeDescription(&error, MI_T("28 - CIM_ERR_SERVER_IS_SHUTTING_DOWN. The WBEM Server is shutting down."));

        MI_Context_PostCimError(context, &error.__instance);
        
        CIM_Error_Destruct(&error);
        return;
    }
    else if (instanceName->Key.value == 9998)
    {
        My_CIM_Error error;

        My_CIM_Error_Construct(&error, context);

        My_CIM_Error_Set_CIMStatusCode(&error, MI_RESULT_SERVER_IS_SHUTTING_DOWN);
        My_CIM_Error_SetPtr_Message(&error, MI_T("This is a test CIM Error"));
        My_CIM_Error_SetPtr_CIMStatusCodeDescription(&error, MI_T("28 - CIM_ERR_SERVER_IS_SHUTTING_DOWN. The WBEM Server is shutting down."));

        MI_Context_PostCimError(context, &error.__instance);
        
        My_CIM_Error_Destruct(&error);
        return;
    }
    else if (instanceName->Key.value == 1235)
    {
        /* Called if Modify did not return an instance */
        MSFT_Person res;

        MSFT_Person_Construct(&res, context);
        MSFT_Person_Set_Key(&res, 1235);
        MSFT_Person_SetPtr_Species(&res, MI_T("GetForModify"));
        MSFT_Person_SetPtr_First(&res, MI_T("1235"));
        MSFT_Person_SetPtr_Last(&res, MI_T("0"));
        MSFT_Person_Post(&res, context);
        MSFT_Person_Destruct(&res);
        MI_PostResult(context, MI_RESULT_OK);
        return;
    }

    /* Search for this instance */
    for (i = 0; i < _size; i++)
    {
        if (instanceName->Key.value == _data[i]->Key.value)
        {
            MSFT_Person_Post(_data[i], context);
            MI_PostResult(context, MI_RESULT_OK);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_NOT_FOUND);
}

void MI_CALL MSFT_Person_CreateInstance(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Person* newInstance)
{
    size_t i;
    MSFT_Person* inst = NULL;
    MI_Result r;

    /* Reject if the instance already exists */
    for (i = 0; i < _size; i++)
    {
        if (newInstance->Key.value == _data[i]->Key.value)
        {
            MI_PostResult(context, MI_RESULT_ALREADY_EXISTS);
        }
    }

    /* Reject on array overflow */
    if (_size == _SIZE)
        MI_PostResult(context, MI_RESULT_FAILED);

    /* Clone the new instance.*/

    r = MSFT_Person_Clone(newInstance, &inst);

    if (r != MI_RESULT_OK)
        MI_PostResult(context, MI_RESULT_FAILED);

    /* Add the instance to the array */
    _data[_size++] = inst;

    MSFT_Person_Post(inst, context);
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_Person_ModifyInstance(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Person* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    if (modifiedInstance->Key.value == 1234)
    {
        /* Post back the one we got*/
        MI_PostResult(context, MSFT_Person_Post(modifiedInstance, context));
        return;
    }
    else if (modifiedInstance->Key.value == 1235)
    {
        /* Rely on the GetInstance to return the value */
        MI_PostResult(context, MI_RESULT_OK);
        return;
    }
    
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MSFT_Person_DeleteInstance(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Person* instanceName)
{
    size_t i;

    /* Find and delete this instance. */
    for (i = 0; i < _size; i++)
    {
        if (instanceName->Key.value == _data[i]->Key.value)
        {
            MSFT_Person* inst = _data[i];

            /* Delete this instance */
            MSFT_Person_Delete(inst);

            /* Remove instance from array */
            _data[i] = _data[--_size];
            MI_PostResult(context, MI_RESULT_OK);
            return;
        }
    }

    MI_PostResult(context, MI_RESULT_NOT_FOUND);
}

void MI_CALL MSFT_Person_Invoke_Add(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_Person* instanceName,
    const MSFT_Person_Add* in)
{
    MSFT_Person_Add out;
    
    if (context && context->ft)
    {
        MSFT_Person_Add_Construct(&out, context);
        MSFT_Person_Add_Set_Z(&out, in->X.value + in->Y.value);
        MSFT_Person_Add_Set_MIReturn(&out, 100);
        MSFT_Person_Add_Post(&out, context);
        MSFT_Person_Add_Destruct(&out);
    }
    
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MSFT_Person_Invoke_TestAllTypes(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_Person* instanceName,
    const MSFT_Person_TestAllTypes* in)
{
    MSFT_Person_TestAllTypes out;
    MI_Datetime dt;
    MSFT_Person ref_out;
    MI_Char s[5];
    MI_Boolean ba[2] = {0,1};
    MI_Uint8 MI_Uint8_items[2];
    MI_Sint8 MI_Sint8_items[2];
    MI_Uint16 MI_Uint16_items[2];
    MI_Sint16 MI_Sint16_items[2];
    MI_Uint32 MI_Uint32_items[2];
    MI_Sint32 MI_Sint32_items[2];
    MI_Uint64 MI_Uint64_items[2];
    MI_Sint64 MI_Sint64_items[2];
    const MI_Char* str_res[3] = {0,0,0};

    // clone/clear tests
    MSFT_Person_TestAllTypes* clone;
    MI_Result r;

    MSFT_Person_TestAllTypes_Construct(&out, context);

    // alter all fields so client knows parameter were received
    MSFT_Person_TestAllTypes_Set_b(&out, !in->b.value);
    MSFT_Person_TestAllTypes_Set_u8(&out, in->u8.value+1);
    MSFT_Person_TestAllTypes_Set_s8(&out, in->s8.value+1);
    MSFT_Person_TestAllTypes_Set_u16(&out, in->u16.value+1);
    MSFT_Person_TestAllTypes_Set_s16(&out, in->s16.value+1);
    MSFT_Person_TestAllTypes_Set_u32(&out, in->u32.value+1);
    MSFT_Person_TestAllTypes_Set_s32(&out, in->s32.value+1);
    MSFT_Person_TestAllTypes_Set_u64(&out, in->u64.value+1);
    MSFT_Person_TestAllTypes_Set_s64(&out, in->s64.value+1);
    MSFT_Person_TestAllTypes_Set_r32(&out, -in->r32.value);
    MSFT_Person_TestAllTypes_Set_r64(&out, -in->r64.value);

    dt.isTimestamp = 1;
    dt.u.timestamp = in->dt.value.u.timestamp;
    dt.u.timestamp.day++;
    dt.u.timestamp.hour++;
    dt.u.timestamp.microseconds++;
    dt.u.timestamp.minute++;
    dt.u.timestamp.month++;
    dt.u.timestamp.second++;
    dt.u.timestamp.utc++;
    dt.u.timestamp.year++;

    MSFT_Person_TestAllTypes_Set_dt(&out, dt);

    // out ref
    MSFT_Person_Construct(&ref_out,context);
    MSFT_Person_Set_Key(&ref_out,in->rf.value->Key.value+1);
    MSFT_Person_TestAllTypes_Set_rf(&out, (MSFT_Base*)&ref_out);

    // string
    memcpy(s,in->s.value, 3* sizeof(MI_Char));
    s[3] = '!';
    s[4] = 0;

    MSFT_Person_TestAllTypes_Set_s(&out, s);

    MSFT_Person_TestAllTypes_Set_c16(&out, in->c16.value+1);

    MSFT_Person_TestAllTypes_Set_bA(&out, ba, MI_COUNT(ba));

    // create return array (the items array must not be enclosed in braces
    // since it will go out of scope).
#define CREATE_RETURN_ARRAY(T,value,setFunction)    \
    {                                               \
        MI_Uint32 counter;                          \
        T* items = T##_items;                       \
                                                    \
        items[0] = (T)value.size;                   \
        items[1] = 0;                               \
                                                    \
        for ( counter = 0; counter < value.size; counter++)     \
            items[1] += value.data[counter];                    \
                                                                \
        setFunction(&out,items,2);                              \
    }


    CREATE_RETURN_ARRAY(MI_Uint8,in->u8A.value,MSFT_Person_TestAllTypes_Set_u8A);
    CREATE_RETURN_ARRAY(MI_Sint8,in->s8A.value,MSFT_Person_TestAllTypes_Set_s8A);
    CREATE_RETURN_ARRAY(MI_Uint16,in->u16A.value,MSFT_Person_TestAllTypes_Set_u16A);
    CREATE_RETURN_ARRAY(MI_Sint16,in->s16A.value,MSFT_Person_TestAllTypes_Set_s16A);
    CREATE_RETURN_ARRAY(MI_Uint32,in->u32A.value,MSFT_Person_TestAllTypes_Set_u32A);
    CREATE_RETURN_ARRAY(MI_Sint32,in->s32A.value,MSFT_Person_TestAllTypes_Set_s32A);
    CREATE_RETURN_ARRAY(MI_Uint64,in->u64A.value,MSFT_Person_TestAllTypes_Set_u64A);
    CREATE_RETURN_ARRAY(MI_Sint64,in->s64A.value,MSFT_Person_TestAllTypes_Set_s64A);

    // strA
    if ( in->sA.exists && in->sA.value.size == 2 )
    {   // skip 'in ' inside input strings
        str_res[0] = in->sA.value.data[0]+3;
    str_res[1] = in->sA.value.data[1]+3;
    str_res[2] = MI_T("*");
        MSFT_Person_TestAllTypes_Set_sA(&out, str_res, MI_COUNT(str_res));
    }
    MSFT_Person_TestAllTypes_Set_MIReturn(&out, MI_T("100"));
    MSFT_Person_TestAllTypes_Post(&out, context);

    /* extra tests for auto-generated functions */
    clone = 0;
    r = MSFT_Person_TestAllTypes_Clone( &out, &clone );

    if ( MI_RESULT_OK != r )
    {
        /* indicate error to unit-test */
        MI_PostResult(context, r);
        return;
    }

    /* clear some members */
    MSFT_Person_TestAllTypes_Clear_bA( clone );
    MSFT_Person_TestAllTypes_Clear_u16A( clone );

    /* delete instances */
    MSFT_Person_TestAllTypes_Destruct(&out);
    MSFT_Person_TestAllTypes_Delete(clone);

    MI_PostResult(context, MI_RESULT_OK);
}
void MI_CALL MSFT_Person_Invoke_StreamParams(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_Person* instanceName,
    const MSFT_Person_StreamParams* in)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

