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
#include "MILargeEvent.h"

void MI_CALL MILargeEvent_Load(
    MILargeEvent_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MILargeEvent_Unload(
    MILargeEvent_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MILargeEvent_EnumerateInstances(
    MILargeEvent_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_Result result = MI_RESULT_OK;
    MILargeEvent largeEvent;
    ETW_EventHeader etwHeader;
    ETW_GUID etwGUID;
    MI_Uint8  Data4[8];
    MI_Datetime dt;
    MI_Char* str1 = MI_T("fdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfd");
    MI_Char* str2 = MI_T("fdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfd");
    MI_Char* str3 = MI_T("fdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfdafdsafdsafdsfd");
    
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(propertySet);
    MI_UNREFERENCED_PARAMETER(keysOnly);
    MI_UNREFERENCED_PARAMETER(filter);

    result = MILargeEvent_Construct(&largeEvent, context);

    
    result = ETW_GUID_Construct(&etwGUID, context);
    result = ETW_GUID_Set_Data1(&etwGUID, 1);
    result = ETW_GUID_Set_Data2(&etwGUID, 2);
    result = ETW_GUID_Set_Data3(&etwGUID, 3);
    result = ETW_GUID_SetPtr_Data4(&etwGUID, Data4, 8);

    result = ETW_EventHeader_Construct(&etwHeader, context);
    result = ETW_EventHeader_Set_ThreadId(&etwHeader, 1);
    result = ETW_EventHeader_Set_ProcessId(&etwHeader, 2);
    dt.isTimestamp = 1;
    dt.u.timestamp.year = 2;
    dt.u.timestamp.month = 3;
    dt.u.timestamp.day = 4;
    dt.u.timestamp.hour = 5;
    dt.u.timestamp.minute = 6;
    dt.u.timestamp.second = 7;
    
    result = ETW_EventHeader_Set_TimeStamp(&etwHeader, dt);
    result = ETW_EventHeader_SetPtr_ActivityId(&etwHeader, &etwGUID);
    result = ETW_EventHeader_Set_ProviderId(&etwHeader, &etwGUID);
    result = ETW_EventHeader_Set_EventId(&etwHeader, 1);
    result = ETW_EventHeader_Set_Version(&etwHeader, 2);
    result = ETW_EventHeader_Set_Channel(&etwHeader, 3);
    result = ETW_EventHeader_Set_Level(&etwHeader, 4);
    result = ETW_EventHeader_Set_Opcode(&etwHeader, 5);
    result = ETW_EventHeader_Set_Task(&etwHeader, 6);
    result = ETW_EventHeader_Set_Keyword(&etwHeader, 7);


    result = MILargeEvent_Construct(&largeEvent, context);
    result = MILargeEvent_SetPtr_Header(&largeEvent, &etwHeader);
    result = MILargeEvent_Set_ID(&largeEvent, 0);
   result = MILargeEvent_Set_number1(&largeEvent, 1);
    result = MILargeEvent_Set_number2(&largeEvent, 2);
    result = MILargeEvent_Set_number3(&largeEvent, 3);
    result = MILargeEvent_Set_number4(&largeEvent, 4);
    result = MILargeEvent_Set_number5(&largeEvent, 5);
    result = MILargeEvent_Set_number6(&largeEvent, 6);
    result = MILargeEvent_Set_number7(&largeEvent, 7);
    result = MILargeEvent_Set_number8(&largeEvent, 8);
    result = MILargeEvent_Set_number9(&largeEvent, 9);
    result = MILargeEvent_Set_number10(&largeEvent, 10);
    result = MILargeEvent_SetPtr_string1(&largeEvent, str1);
    result = MILargeEvent_SetPtr_string2(&largeEvent, str2);
    result = MILargeEvent_SetPtr_string3(&largeEvent, str3);
    result = MILargeEvent_SetPtr_string4(&largeEvent, str1);
    result = MILargeEvent_SetPtr_string5(&largeEvent, str3);
    result = MILargeEvent_SetPtr_string6(&largeEvent, str2);
    result = MILargeEvent_SetPtr_string7(&largeEvent, str1);
    result = MILargeEvent_SetPtr_string8(&largeEvent, str3);
    result = MILargeEvent_SetPtr_string9(&largeEvent, str2);
    result = MILargeEvent_SetPtr_string10(&largeEvent, str3);

    largeEvent.ID.value = 0;

    while (largeEvent.ID.value++ < 20000)
    {
        MILargeEvent_Post(&largeEvent, context);
    }

    MILargeEvent_Destruct(&largeEvent);
    ETW_EventHeader_Destruct(&etwHeader);
    ETW_GUID_Destruct(&etwGUID);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL MILargeEvent_GetInstance(
    MILargeEvent_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MILargeEvent* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MILargeEvent_CreateInstance(
    MILargeEvent_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MILargeEvent* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MILargeEvent_ModifyInstance(
    MILargeEvent_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MILargeEvent* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL MILargeEvent_DeleteInstance(
    MILargeEvent_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MILargeEvent* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

