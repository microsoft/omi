/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @statikgen@ */

#include <MI.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <pal/format.h>
#include "TestClass_AllDMTFTypes.h"

#define ONLOAD_CREATE_INSTANCES 4

#define POST_ERROR(_context, _result, _type, _contextualMessage) \
{    MI_PostError(_context, _result, _type, _contextualMessage);    return;    }

std::vector<TestClass_AllDMTFTypes*> instanceStore;

// on CentOS 6
#if (__GNUC__==4 && __GNUC_MINOR__==4 && __OPTIMIZE__)
#pragma GCC diagnostic ignored "-Wuninitialized"
#endif

void GetCopyOfInstanceStore(std::vector<TestClass_AllDMTFTypes*> &copyOfInstanceStore)
{
    //auto hold(vectorLock.Hold());
    copyOfInstanceStore.resize(instanceStore.size());
    std::copy(instanceStore.begin(), instanceStore.end(), copyOfInstanceStore.begin());
    //hold.Unlock();
}

void CreateInstances(MI_Context* context, unsigned int number)
{
    MI_Interval interval;
    MI_Timestamp timestamp;
    MI_Datetime date;

    TestClass_AllDMTFTypes* instance = NULL;
    TestClass_AllDMTFTypes temp; 
    TestClass_AllDMTFTypes_Construct(&temp, context);

    for(unsigned int i=0 ; i < number; i++)
    {
        //instance = new TestClass_AllDMTFTypes;         
        TestClass_AllDMTFTypes_Clone(&temp, &instance);    

        TestClass_AllDMTFTypes_Set_v_bool(instance, (MI_Boolean) (i % 2));
        TestClass_AllDMTFTypes_Set_v_char16(instance, (MI_Char16) (i % 93) + 33 ); //keep it between ASCII 33 to 126

        date.isTimestamp = (i % 2);

        interval.days = i % 30;
        interval.hours = i % 24;
        interval.microseconds = i % 999;
        interval.minutes = i % 60;
        interval.seconds = i % 60;

        timestamp.day = i % 28;
        timestamp.hour = i % 24;
        timestamp.microseconds = i % 999;
        timestamp.minute = i % 60;
        timestamp.month = i % 12;
        timestamp.second = i % 60; 

        timestamp.year = (i % 3000) + 2000;

        //BUG:94799 workaround
        if(date.isTimestamp == 1)
        {
            timestamp.utc = 830; 
        }
        else
        {
            timestamp.utc = 0;
        }

        date.u.interval = interval;
        date.u.timestamp = timestamp;


        TestClass_AllDMTFTypes_Set_v_DATETIME(instance, date);

        TestClass_AllDMTFTypes_Set_v_Key(instance, (MI_Uint64) i);
        TestClass_AllDMTFTypes_Set_v_rEal32(instance, (MI_Real32) (1.003E+2 + i));
        TestClass_AllDMTFTypes_Set_v_Real64(instance, (MI_Real64) (1.4234E-2 + i));
#if defined(hpux)
#pragma diag_suppress 2068
//   HP complains about change of sign        
#endif
        TestClass_AllDMTFTypes_Set_v_sint16(instance, (MI_Sint16) ((0xFF) * -1 + i));
        TestClass_AllDMTFTypes_Set_v_sint32(instance, (MI_Sint32) ((0xFFFF) * -1 + i));
        TestClass_AllDMTFTypes_Set_v_sint64(instance, (MI_Sint64) ((MI_Sint64)(0xFFFFFFFF) * -1 + i));
        TestClass_AllDMTFTypes_Set_v_sint8(instance, (MI_Sint8) ((0xF) * -1 + i));
#if defined(hpux)
#pragma diag_default 2068
#endif

        MI_Char strBuf[100];        
        Stprintf(strBuf, MI_COUNT(strBuf), MI_T("TestString %d"), i);
        TestClass_AllDMTFTypes_Set_v_string(instance, strBuf);
        
        TestClass_AllDMTFTypes_Set_v_UINT16(instance, (MI_Uint16) (0xFF + i));
        TestClass_AllDMTFTypes_Set_v_uint32(instance, (MI_Uint32) (0xFFFF + i));
        TestClass_AllDMTFTypes_Set_v_uint64(instance, (MI_Uint64) (0xFFFFFFFF + i));
        TestClass_AllDMTFTypes_Set_v_uint8(instance, (MI_Uint8) (0xF + i));

        /*TestClass_ForEmbedded embeddedInstance;
        TestClass_ForEmbedded_Construct(&embeddedInstance, context);
        TestClass_ForEmbedded_Set_embeddedStringValue(&embeddedInstance, MI_T("Test Embedded string"));

        TestClass_AllDMTFTypes_Set_v_embeddedInstance(instance, &embeddedInstance);
        TestClass_AllDMTFTypes_Set_v_reference(instance, &embeddedInstance);
        TestClass_ForEmbedded_Destruct(&embeddedInstance);        

        MI_Instance* dynamicInstance;
        MI_Context_NewDynamicInstance(context, MI_T("DyanamicClass"), 0, &dynamicInstance);

        MI_Value val;
        val.uint32 = 100;

        MI_Instance_AddElement(dynamicInstance, MI_T("dynamicProperty"), &val, MI_UINT32, 0);        
        
        TestClass_AllDMTFTypes_Set_v_embeddedObject(instance, dynamicInstance);

        MI_Instance_Delete(dynamicInstance);*/

        //Set Octet string 
        MI_Uint8 octetStringValue[7] = {0x00, 0x00, 0x00, 0x07, 0x41, 0x42, 0x43};
        MI_Uint8 increment = (MI_Uint8) i;
        octetStringValue[4] += increment;
        octetStringValue[5] += increment;
        octetStringValue[6] += increment;

        TestClass_AllDMTFTypes_Set_v_octetUint8(instance, octetStringValue, 7);

        //End set octet string

        instanceStore.push_back(instance);        
    }

    TestClass_AllDMTFTypes_Destruct(&temp);
}

void MI_CALL TestClass_AllDMTFTypes_Load(
    TestClass_AllDMTFTypes_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{    
    *self = NULL;

    if(instanceStore.size() == 0)
    {
        CreateInstances(context, ONLOAD_CREATE_INSTANCES);
    }


    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestClass_AllDMTFTypes_Unload(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context)
{
    for(unsigned int i=0; i<instanceStore.size(); i++)
    {
        TestClass_AllDMTFTypes_Delete(instanceStore[i]);
    }

    instanceStore.clear();

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestClass_AllDMTFTypes_EnumerateInstances(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_Result result = MI_RESULT_OK;

    //make copy to avoid deadlock when writting progress and concurrently processing some other operation
    std::vector<TestClass_AllDMTFTypes*> copyOfInstanceStore;
    GetCopyOfInstanceStore(copyOfInstanceStore);

    for(MI_Uint32 i=0; i < copyOfInstanceStore.size(); i++)
    {
        result = TestClass_AllDMTFTypes_Post(copyOfInstanceStore[i], context);
        if(result != MI_RESULT_OK)
        {            
            break;
        }
        }

    MI_PostResult(context, result); 
}

void MI_CALL TestClass_AllDMTFTypes_GetInstance(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_AllDMTFTypes* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_Result result = MI_RESULT_NOT_FOUND;

    std::vector<TestClass_AllDMTFTypes*> copyOfInstanceStore;
    GetCopyOfInstanceStore(copyOfInstanceStore);

    for(unsigned int i=0; i < copyOfInstanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            MI_WriteMessage(context, 1, MI_T("Getting instance"));            
            result = TestClass_AllDMTFTypes_Post(instanceStore[i], context);            
            break;
        }
    }

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFTypes_CreateInstance(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_AllDMTFTypes* newInstance)
{    
    MI_Result result = MI_RESULT_OK;    

    TestClass_AllDMTFTypes temp;
    result = TestClass_AllDMTFTypes_Construct(&temp, context);

    if(result != MI_RESULT_OK)
    {
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not construct instance"));
    }

    TestClass_AllDMTFTypes_Set_v_bool(&temp, newInstance->v_bool.value);
    TestClass_AllDMTFTypes_Set_v_char16(&temp, newInstance->v_char16.value); //keep it between ASCII 33 to 126
    TestClass_AllDMTFTypes_Set_v_DATETIME(&temp, newInstance->v_DATETIME.value);

    TestClass_AllDMTFTypes_Set_v_Key(&temp, newInstance->v_Key.value);
    TestClass_AllDMTFTypes_Set_v_rEal32(&temp, newInstance->v_rEal32.value);
    TestClass_AllDMTFTypes_Set_v_Real64(&temp, newInstance->v_Real64.value);
    TestClass_AllDMTFTypes_Set_v_sint16(&temp, newInstance->v_sint16.value);
    TestClass_AllDMTFTypes_Set_v_sint32(&temp, newInstance->v_sint32.value);
    TestClass_AllDMTFTypes_Set_v_sint64(&temp, newInstance->v_sint64.value);
    TestClass_AllDMTFTypes_Set_v_sint8(&temp, newInstance->v_sint8.value);
    TestClass_AllDMTFTypes_Set_v_string(&temp, newInstance->v_string.value);
    TestClass_AllDMTFTypes_Set_v_UINT16(&temp, newInstance->v_UINT16.value);
    TestClass_AllDMTFTypes_Set_v_uint32(&temp, newInstance->v_uint32.value);
    TestClass_AllDMTFTypes_Set_v_uint64(&temp, newInstance->v_uint64.value);
    TestClass_AllDMTFTypes_Set_v_uint8(&temp, newInstance->v_uint8.value);

    TestClass_AllDMTFTypes_Set_v_reference(&temp, newInstance->v_reference.value);
    TestClass_AllDMTFTypes_Set_v_embeddedInstance(&temp, newInstance->v_embeddedInstance.value);
    TestClass_AllDMTFTypes_Set_v_embeddedObject(&temp, newInstance->v_embeddedObject.value);

    if(newInstance->v_octetUint8.exists)
    TestClass_AllDMTFTypes_Set_v_octetUint8(&temp, newInstance->v_octetUint8.value.data, newInstance->v_octetUint8.value.size);

    result = TestClass_AllDMTFTypes_Post(&temp, context);

    if(result != MI_RESULT_OK)
    {
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not post message"));
    }

    TestClass_AllDMTFTypes * pCloneInstance = NULL;       
    result = TestClass_AllDMTFTypes_Clone(&temp, &pCloneInstance);
    if(result != MI_RESULT_OK)
    {
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not clone instance"));
    }

    instanceStore.push_back(pCloneInstance);

    result = TestClass_AllDMTFTypes_Destruct(&temp);

    MI_PostResult(context, result);
}

void MI_CALL TestClass_AllDMTFTypes_ModifyInstance(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_AllDMTFTypes* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_Result result;
    MI_Uint32 count;

    MI_Value val;
    MI_Type type;

    MI_Uint32 flags;    

    MI_Value reportFlagsOfPropertyToModifyValue;
    MI_Type reportFlagsOfPropertyToModifyType;
    result = MI_GetCustomOption(context, MI_T("ReportFlagsOfPropertyToModify"), &reportFlagsOfPropertyToModifyType, &reportFlagsOfPropertyToModifyValue);
    if ((result == MI_RESULT_OK) && (reportFlagsOfPropertyToModifyType == MI_STRING))
    {
        MI_Char* nameOfPropertyToReport = reportFlagsOfPropertyToModifyValue.string;

        MI_Uint32 flagsToReport;
        result = MI_Instance_GetElement(&(modifiedInstance->__instance), nameOfPropertyToReport, NULL, NULL, &flagsToReport, NULL);
        if(result != MI_RESULT_OK)
        {
            POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not get flags to report"));
        }

        MI_Char warningMessage[100];

        Stprintf(warningMessage, MI_COUNT(warningMessage), MI_T("ReportFlags: %s: 0x%08x"), nameOfPropertyToReport, flagsToReport);

        result = MI_WriteMessage(context, 0, warningMessage);
        if(result != MI_RESULT_OK)
        {
            POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not write message on warning channel"));
        }
    }
    result = MI_RESULT_OK;    

    if (propertySet != NULL)
    {
        MI_PropertySet_GetElementCount(propertySet, &count);

        if(count == 0)
        {
            MI_PostResult(context,MI_RESULT_OK);
            return;
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
            POST_ERROR(context, MI_RESULT_NOT_FOUND, MI_RESULT_TYPE_MI, MI_T("Instance not fund!"));
        }

        const MI_Char* name = NULL;

        TestClass_AllDMTFTypes* test = (instanceStore)[index];

        for(MI_Uint32 i=0 ; i < count; i++)
        {
            if((result = MI_Instance_GetElementAt(&(modifiedInstance->__instance), i, &name, &val, &type, &flags)) != MI_RESULT_OK )
            {
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not get element of instance"));
            }

            //only if the property is modified
            //if((flags & MI_FLAG_NOT_MODIFIED) == 0)
            //{
            if((flags & MI_FLAG_NULL) == 0)
            {
                /*Only MI_FLAG_NULL, MI_FLAG_BORROW and MI_FLAG_ADOPT are valid for SetElement operation*/
                MI_Uint32 validFlags = (MI_FLAG_NULL|MI_FLAG_BORROW|MI_FLAG_ADOPT)&flags;

                if((result = MI_Instance_SetElement( (MI_Instance *) &(test->__instance), (MI_Char *) name, (MI_Value *) &val, (MI_Type) type, (MI_Uint32) validFlags)) != MI_RESULT_OK)
                {
                    POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not set element on instance"));
                }
            }

        }

        TestClass_AllDMTFTypes_Post(test, context);
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestClass_AllDMTFTypes_DeleteInstance(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_AllDMTFTypes* instanceName)
{
    MI_Result result = MI_RESULT_OK;

    bool foundInstance = false;

    std::vector<TestClass_AllDMTFTypes*>::iterator it;

    MI_Char tempString[1000];
    memset(tempString, 0, sizeof(MI_Char) * 1000);     

    for(it = instanceStore.begin(); it != instanceStore.end(); it++)
    {    
        if(instanceName->v_Key.value == (*it)->v_Key.value)
        {
            foundInstance = true;
                TestClass_AllDMTFTypes_Delete((*it));
                instanceStore.erase(it);                
            memset(tempString, 0, sizeof(MI_Char) * 1000);
            break;
    }
    }

    if(!foundInstance)
        result = MI_RESULT_NOT_FOUND;

    if(result != MI_RESULT_OK)
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Instance not found!"));

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_GetBoolValue(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetBoolValue* in)
{
    MI_Result result = MI_RESULT_OK;

    std::vector<TestClass_AllDMTFTypes*> copyOfInstanceStore;
    GetCopyOfInstanceStore(copyOfInstanceStore);

    for(unsigned int i=0; i < copyOfInstanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {            
            TestClass_AllDMTFTypes_GetBoolValue temp;
            TestClass_AllDMTFTypes_GetBoolValue_Construct(&temp, context);

            TestClass_AllDMTFTypes_GetBoolValue_Set_boolVal(&temp, copyOfInstanceStore[i]->v_bool.value);
            TestClass_AllDMTFTypes_GetBoolValue_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_GetBoolValue_Post(&temp, context);

            TestClass_AllDMTFTypes_GetBoolValue_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not post value"));

            break;
        }
    }

    MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_SetBoolValue(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetBoolValue* in)
{
    MI_Result result = MI_RESULT_OK;

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_SetBoolValue temp;
            TestClass_AllDMTFTypes_SetBoolValue_Construct(&temp, context);

            instanceStore[i]->v_bool.value = in->boolVal.value;

            TestClass_AllDMTFTypes_SetBoolValue_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_SetBoolValue_Post(&temp, context);

            TestClass_AllDMTFTypes_SetBoolValue_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not post instance"));

            break;
        }
    }

        MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_GetUint8Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetUint8Value* in)
{
    MI_Result result = MI_RESULT_OK;

    std::vector<TestClass_AllDMTFTypes*> copyOfInstanceStore;
    GetCopyOfInstanceStore(copyOfInstanceStore);

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_GetUint8Value temp;
            TestClass_AllDMTFTypes_GetUint8Value_Construct(&temp, context);

            TestClass_AllDMTFTypes_GetUint8Value_Set_Uint8Val(&temp, copyOfInstanceStore[i]->v_uint8.value);
            TestClass_AllDMTFTypes_GetUint8Value_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_GetUint8Value_Post(&temp, context);

            TestClass_AllDMTFTypes_GetUint8Value_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

    MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_SetUint8Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetUint8Value* in)
{
    MI_Result result = MI_RESULT_OK;

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_SetUint8Value temp;
            TestClass_AllDMTFTypes_SetUint8Value_Construct(&temp, context);

            instanceStore[i]->v_uint8.value = in->Uint8Val.value;

            TestClass_AllDMTFTypes_SetUint8Value_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_SetUint8Value_Post(&temp, context);

            TestClass_AllDMTFTypes_SetUint8Value_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

        MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_GetSint8Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetSint8Value* in)
{
    MI_Result result = MI_RESULT_OK;

    std::vector<TestClass_AllDMTFTypes*> copyOfInstanceStore;
    GetCopyOfInstanceStore(copyOfInstanceStore);

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_GetSint8Value temp;
            TestClass_AllDMTFTypes_GetSint8Value_Construct(&temp, context);

            TestClass_AllDMTFTypes_GetSint8Value_Set_Sint8Val(&temp, copyOfInstanceStore[i]->v_sint8.value);
            TestClass_AllDMTFTypes_GetSint8Value_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_GetSint8Value_Post(&temp, context);

            TestClass_AllDMTFTypes_GetSint8Value_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

    MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_SetSint8Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetSint8Value* in)
{
    MI_Result result = MI_RESULT_OK;

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_SetSint8Value temp;
            TestClass_AllDMTFTypes_SetSint8Value_Construct(&temp, context);

            instanceStore[i]->v_sint8.value = in->Sint8Val.value;

            TestClass_AllDMTFTypes_SetSint8Value_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_SetSint8Value_Post(&temp, context);

            TestClass_AllDMTFTypes_SetSint8Value_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

        MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_GetUint16Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetUint16Value* in)
{
    MI_Result result = MI_RESULT_OK;

    std::vector<TestClass_AllDMTFTypes*> copyOfInstanceStore;
    GetCopyOfInstanceStore(copyOfInstanceStore);

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_GetUint16Value temp;
            TestClass_AllDMTFTypes_GetUint16Value_Construct(&temp, context);

            TestClass_AllDMTFTypes_GetUint16Value_Set_Uint16Val(&temp, copyOfInstanceStore[i]->v_UINT16.value);
            TestClass_AllDMTFTypes_GetUint16Value_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_GetUint16Value_Post(&temp, context);

            TestClass_AllDMTFTypes_GetUint16Value_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

    MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_SetUint16Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetUint16Value* in)
{
    MI_Result result = MI_RESULT_OK;

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_SetUint16Value temp;
            TestClass_AllDMTFTypes_SetUint16Value_Construct(&temp, context);

            instanceStore[i]->v_UINT16.value = in->Uint16Val.value;

            TestClass_AllDMTFTypes_SetUint16Value_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_SetUint16Value_Post(&temp, context);

            TestClass_AllDMTFTypes_SetUint16Value_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

        MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_GetSint16Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetSint16Value* in)
{
    MI_Result result = MI_RESULT_OK;

    std::vector<TestClass_AllDMTFTypes*> copyOfInstanceStore;
    GetCopyOfInstanceStore(copyOfInstanceStore);

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_GetSint16Value temp;
            TestClass_AllDMTFTypes_GetSint16Value_Construct(&temp, context);

            TestClass_AllDMTFTypes_GetSint16Value_Set_Sint16Val(&temp, copyOfInstanceStore[i]->v_sint16.value);
            TestClass_AllDMTFTypes_GetSint16Value_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_GetSint16Value_Post(&temp, context);

            TestClass_AllDMTFTypes_GetSint16Value_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

    MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_SetSint16Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetSint16Value* in)
{
    MI_Result result = MI_RESULT_OK;

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_SetSint16Value temp;
            TestClass_AllDMTFTypes_SetSint16Value_Construct(&temp, context);

            instanceStore[i]->v_sint16.value = in->Sint16Val.value;

            TestClass_AllDMTFTypes_SetSint16Value_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_SetSint16Value_Post(&temp, context);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

        MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_GetUint32Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetUint32Value* in)
{
    MI_Result result = MI_RESULT_OK;

    std::vector<TestClass_AllDMTFTypes*> copyOfInstanceStore;
    GetCopyOfInstanceStore(copyOfInstanceStore);

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_GetUint32Value temp;
            TestClass_AllDMTFTypes_GetUint32Value_Construct(&temp, context);

            TestClass_AllDMTFTypes_GetUint32Value_Set_Uint32Val(&temp, copyOfInstanceStore[i]->v_uint32.value);
            TestClass_AllDMTFTypes_GetUint32Value_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_GetUint32Value_Post(&temp, context);

            TestClass_AllDMTFTypes_GetUint32Value_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

    MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_SetUint32Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetUint32Value* in)
{
    MI_Result result = MI_RESULT_OK;

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_SetUint32Value temp;
            TestClass_AllDMTFTypes_SetUint32Value_Construct(&temp, context);

            instanceStore[i]->v_uint32.value = in->Uint32Val.value;

            TestClass_AllDMTFTypes_SetUint32Value_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_SetUint32Value_Post(&temp, context);

            TestClass_AllDMTFTypes_SetUint32Value_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

        MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_GetSint32Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetSint32Value* in)
{
    MI_Result result = MI_RESULT_OK;

    std::vector<TestClass_AllDMTFTypes*> copyOfInstanceStore;
    GetCopyOfInstanceStore(copyOfInstanceStore);

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_GetSint32Value temp;
            TestClass_AllDMTFTypes_GetSint32Value_Construct(&temp, context);

            TestClass_AllDMTFTypes_GetSint32Value_Set_Sint32Val(&temp, copyOfInstanceStore[i]->v_sint32.value);
            TestClass_AllDMTFTypes_GetSint32Value_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_GetSint32Value_Post(&temp, context);

            TestClass_AllDMTFTypes_GetSint32Value_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

    MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_SetSint32Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetSint32Value* in)
{
    MI_Result result = MI_RESULT_OK;

    MI_Value reportFlagsOfInParameterValue;
    MI_Type reportFlagsOfInParameterType;
    result = MI_GetCustomOption(context, MI_T("ReportFlagsOfInParameter"), &reportFlagsOfInParameterType, &reportFlagsOfInParameterValue);
    if (result == MI_RESULT_OK)
    {
        MI_Uint32 flagsToReport;
        result = MI_Instance_GetElement(&(in->__instance), MI_T("Sint32Val"), NULL, NULL, &flagsToReport, NULL);
        if(result != MI_RESULT_OK)
        {
            POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not get flags to report"));
        }

        MI_Char warningMessage[100];

        Stprintf(warningMessage, MI_COUNT(warningMessage), MI_T("ReportFlags: Sint32Val: 0x%08x"), flagsToReport);

        result = MI_WriteMessage(context, 0, warningMessage);
        if(result != MI_RESULT_OK)
        {
            POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not write message on warning channel"));
        }
    }
    result = MI_RESULT_OK;    

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_SetSint32Value temp;
            TestClass_AllDMTFTypes_SetSint32Value_Construct(&temp, context);

            instanceStore[i]->v_sint32.value = in->Sint32Val.value;

            TestClass_AllDMTFTypes_SetSint32Value_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_SetSint32Value_Post(&temp, context);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            TestClass_AllDMTFTypes_SetSint32Value_Destruct(&temp);

            break;
        }
    }


        MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_GetUint64Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetUint64Value* in)
{
    MI_Result result = MI_RESULT_OK;

    std::vector<TestClass_AllDMTFTypes*> copyOfInstanceStore;
    GetCopyOfInstanceStore(copyOfInstanceStore);

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_GetUint64Value temp;
            TestClass_AllDMTFTypes_GetUint64Value_Construct(&temp, context);

            TestClass_AllDMTFTypes_GetUint64Value_Set_Uint64Val(&temp, copyOfInstanceStore[i]->v_uint64.value);
            TestClass_AllDMTFTypes_GetUint64Value_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_GetUint64Value_Post(&temp, context);

            TestClass_AllDMTFTypes_GetUint64Value_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

    MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_SetUint64Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetUint64Value* in)
{
    MI_Result result = MI_RESULT_OK;

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_SetUint64Value temp;
            TestClass_AllDMTFTypes_SetUint64Value_Construct(&temp, context);

            instanceStore[i]->v_uint64.value = in->Uint64Val.value;

            TestClass_AllDMTFTypes_SetUint64Value_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_SetUint64Value_Post(&temp, context);

            TestClass_AllDMTFTypes_SetUint64Value_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

        MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_GetSint64Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetSint64Value* in)
{
    MI_Result result = MI_RESULT_OK;

    std::vector<TestClass_AllDMTFTypes*> copyOfInstanceStore;
    GetCopyOfInstanceStore(copyOfInstanceStore);

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_GetSint64Value temp;
            TestClass_AllDMTFTypes_GetSint64Value_Construct(&temp, context);

            TestClass_AllDMTFTypes_GetSint64Value_Set_Sint64Val(&temp, copyOfInstanceStore[i]->v_sint64.value);
            TestClass_AllDMTFTypes_GetSint64Value_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_GetSint64Value_Post(&temp, context);

            TestClass_AllDMTFTypes_GetSint64Value_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

    MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_SetSint64Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetSint64Value* in)
{
    MI_Result result = MI_RESULT_OK;

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_SetSint64Value temp;
            TestClass_AllDMTFTypes_SetSint64Value_Construct(&temp, context);

            instanceStore[i]->v_sint64.value = in->Sint64Val.value;

            TestClass_AllDMTFTypes_SetSint64Value_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_SetSint64Value_Post(&temp, context);

            TestClass_AllDMTFTypes_SetSint64Value_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

        MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_GetStringCustomOption(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetStringCustomOption* in)
{
    MI_Result result = MI_RESULT_OK;

    MI_Value customOptionValue;
    MI_Type customOptionType;
    result = MI_GetCustomOption(context, in->optionName.value, &customOptionType, &customOptionValue);
    if(result != MI_RESULT_OK)
    {
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Could not get customoption"));
    }

    if (customOptionType != MI_STRING)
    {
        result = MI_RESULT_FAILED;
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Custom option type is not string"));
    }

    TestClass_AllDMTFTypes_GetStringCustomOption methodResult;
    result = TestClass_AllDMTFTypes_GetStringCustomOption_Construct(&methodResult, context);
    if(result != MI_RESULT_OK)
    {
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot construct instance"));
    }

    result = TestClass_AllDMTFTypes_GetStringCustomOption_Set_MIReturn(&methodResult, 0);
    if(result != MI_RESULT_OK)
    {
        TestClass_AllDMTFTypes_GetStringCustomOption_Destruct(&methodResult);
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot set return value"));
    }

    result = TestClass_AllDMTFTypes_GetStringCustomOption_Set_optionValue(&methodResult, customOptionValue.string);
    if(result != MI_RESULT_OK)
    {
        TestClass_AllDMTFTypes_GetStringCustomOption_Destruct(&methodResult);
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot set option value"));
    }

    result = MI_PostInstance(context, &(methodResult.__instance));
    if(result != MI_RESULT_OK)
    {
        TestClass_AllDMTFTypes_GetStringCustomOption_Destruct(&methodResult);
        POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));
    }

    MI_PostResult(context, MI_RESULT_OK);
    TestClass_AllDMTFTypes_GetStringCustomOption_Destruct(&methodResult);
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_GetEmbeddedObjectValue(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetEmbeddedObjectValue* in)
{
    MI_Result result = MI_RESULT_OK;

    std::vector<TestClass_AllDMTFTypes*> copyOfInstanceStore;
    GetCopyOfInstanceStore(copyOfInstanceStore);

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_GetEmbeddedObjectValue temp;
            TestClass_AllDMTFTypes_GetEmbeddedObjectValue_Construct(&temp, context);

            TestClass_AllDMTFTypes_GetEmbeddedObjectValue_Set_EmbeddedObjectVal(&temp, copyOfInstanceStore[i]->v_embeddedObject.value);
            TestClass_AllDMTFTypes_GetEmbeddedObjectValue_Set_MIReturn(&temp, result);

            TestClass_AllDMTFTypes_GetEmbeddedObjectValue_Post(&temp, context);

            TestClass_AllDMTFTypes_GetEmbeddedObjectValue_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

    MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_SetEmbeddedObjectValue(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetEmbeddedObjectValue* in)
{
    MI_Result result = MI_RESULT_OK;

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_SetEmbeddedObjectValue temp;
            TestClass_AllDMTFTypes_SetEmbeddedObjectValue_Construct(&temp, context);

            TestClass_AllDMTFTypes_Set_v_embeddedObject(instanceStore[i], in->EmbeddedObjectVal.value);

            TestClass_AllDMTFTypes_SetEmbeddedObjectValue_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_SetEmbeddedObjectValue_Post(&temp, context);

            TestClass_AllDMTFTypes_SetEmbeddedObjectValue_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

        MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_GetEmbeddedInstanceValue(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetEmbeddedInstanceValue* in)
{
    MI_Result result = MI_RESULT_OK;

    std::vector<TestClass_AllDMTFTypes*> copyOfInstanceStore;
    GetCopyOfInstanceStore(copyOfInstanceStore);

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_GetEmbeddedInstanceValue temp;
            TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_Construct(&temp, context);

            TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_Set_EmbeddedInstanceVal(&temp, copyOfInstanceStore[i]->v_embeddedInstance.value);
            TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_Set_MIReturn(&temp, result);

            TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_Post(&temp, context);

            TestClass_AllDMTFTypes_GetEmbeddedInstanceValue_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_SetEmbeddedInstanceValue(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetEmbeddedInstanceValue* in)
{
    MI_Result result = MI_RESULT_OK;

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_SetEmbeddedInstanceValue temp;
            TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_Construct(&temp, context);

            TestClass_AllDMTFTypes_Set_v_embeddedInstance(instanceStore[i], in->EmbeddedInstanceVal.value);

            TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_Set_MIReturn(&temp, result);

            TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_Post(&temp, context);

            TestClass_AllDMTFTypes_SetEmbeddedInstanceValue_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

        MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_GetReferenceValue(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetReferenceValue* in)
{
    MI_Result result = MI_RESULT_OK;

    std::vector<TestClass_AllDMTFTypes*> copyOfInstanceStore;
    GetCopyOfInstanceStore(copyOfInstanceStore);

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_GetReferenceValue temp;
            TestClass_AllDMTFTypes_GetReferenceValue_Construct(&temp, context);

            TestClass_AllDMTFTypes_GetReferenceValue_Set_ReferenceVal(&temp, copyOfInstanceStore[i]->v_reference.value);
            TestClass_AllDMTFTypes_GetReferenceValue_Set_MIReturn(&temp, result);

            TestClass_AllDMTFTypes_GetReferenceValue_Post(&temp, context);

            TestClass_AllDMTFTypes_GetReferenceValue_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_SetReferenceValue(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetReferenceValue* in)
{
    MI_Result result = MI_RESULT_OK;

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_SetReferenceValue temp;
            TestClass_AllDMTFTypes_SetReferenceValue_Construct(&temp, context);

            TestClass_AllDMTFTypes_Set_v_reference(instanceStore[i], in->ReferenceVal.value);

            TestClass_AllDMTFTypes_SetReferenceValue_Set_MIReturn(&temp, result);

            TestClass_AllDMTFTypes_SetReferenceValue_Post(&temp, context);

            TestClass_AllDMTFTypes_SetReferenceValue_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

        MI_PostResult(context, result);    
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_GetOctetUint8Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_GetOctetUint8Value* in)
{
    MI_Result result = MI_RESULT_OK;

    std::vector<TestClass_AllDMTFTypes*> copyOfInstanceStore;
    GetCopyOfInstanceStore(copyOfInstanceStore);

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_GetOctetUint8Value temp;
            TestClass_AllDMTFTypes_GetOctetUint8Value_Construct(&temp, context);

            TestClass_AllDMTFTypes_GetOctetUint8Value_Set_v_octetUint8Val(&temp, copyOfInstanceStore[i]->v_octetUint8.value.data, copyOfInstanceStore[i]->v_octetUint8.value.size);
            TestClass_AllDMTFTypes_GetOctetUint8Value_Set_MIReturn(&temp, result);

            result = TestClass_AllDMTFTypes_GetOctetUint8Value_Post(&temp, context);

            TestClass_AllDMTFTypes_GetOctetUint8Value_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestClass_AllDMTFTypes_Invoke_SetOctetUint8Value(
    TestClass_AllDMTFTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const TestClass_AllDMTFTypes* instanceName,
    const TestClass_AllDMTFTypes_SetOctetUint8Value* in)
{
    MI_Result result = MI_RESULT_OK;

    for(unsigned int i=0; i < instanceStore.size(); i++)
    {
        if(instanceStore[i]->v_Key.value == instanceName->v_Key.value)
        {
            TestClass_AllDMTFTypes_SetOctetUint8Value temp;
            TestClass_AllDMTFTypes_SetOctetUint8Value_Construct(&temp, context);

            TestClass_AllDMTFTypes_Set_v_octetUint8(instanceStore[i], in->v_octetUint8Val.value.data, in->v_octetUint8Val.value.size);

            TestClass_AllDMTFTypes_SetOctetUint8Value_Set_MIReturn(&temp, result);

            TestClass_AllDMTFTypes_SetOctetUint8Value_Post(&temp, context);

            TestClass_AllDMTFTypes_SetOctetUint8Value_Destruct(&temp);

            if(result != MI_RESULT_OK)
                POST_ERROR(context, result, MI_RESULT_TYPE_MI, MI_T("Couldnot post instance"));

            break;
        }
    }

    MI_PostResult(context, result);    
}


