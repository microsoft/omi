/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_Job_h
#define _CIM_Job_h

#include <MI.h>
#include "CIM_LogicalElement.h"

/*
**==============================================================================
**
** CIM_Job [CIM_Job]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_Job /* extends CIM_LogicalElement */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_ManagedSystemElement properties */
    MI_ConstDatetimeField InstallDate;
    MI_ConstStringField Name;
    MI_ConstUint16AField OperationalStatus;
    MI_ConstStringAField StatusDescriptions;
    MI_ConstStringField Status;
    MI_ConstUint16Field HealthState;
    MI_ConstUint16Field CommunicationStatus;
    MI_ConstUint16Field DetailedStatus;
    MI_ConstUint16Field OperatingStatus;
    MI_ConstUint16Field PrimaryStatus;
    /* CIM_LogicalElement properties */
    /* CIM_Job properties */
    MI_ConstStringField JobStatus;
    MI_ConstDatetimeField TimeSubmitted;
    MI_ConstDatetimeField ScheduledStartTime;
    MI_ConstDatetimeField StartTime;
    MI_ConstDatetimeField ElapsedTime;
    MI_ConstUint32Field JobRunTimes;
    MI_ConstUint8Field RunMonth;
    MI_ConstSint8Field RunDay;
    MI_ConstSint8Field RunDayOfWeek;
    MI_ConstDatetimeField RunStartInterval;
    MI_ConstUint16Field LocalOrUtcTime;
    MI_ConstDatetimeField UntilTime;
    MI_ConstStringField Notify;
    MI_ConstStringField Owner;
    MI_ConstUint32Field Priority;
    MI_ConstUint16Field PercentComplete;
    MI_ConstBooleanField DeleteOnCompletion;
    MI_ConstUint16Field ErrorCode;
    MI_ConstStringField ErrorDescription;
    MI_ConstUint16Field RecoveryAction;
    MI_ConstStringField OtherRecoveryAction;
}
CIM_Job;

typedef struct _CIM_Job_Ref
{
    CIM_Job* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Job_Ref;

typedef struct _CIM_Job_ConstRef
{
    MI_CONST CIM_Job* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Job_ConstRef;

typedef struct _CIM_Job_Array
{
    struct _CIM_Job** data;
    MI_Uint32 size;
}
CIM_Job_Array;

typedef struct _CIM_Job_ConstArray
{
    struct _CIM_Job MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_Job_ConstArray;

typedef struct _CIM_Job_ArrayRef
{
    CIM_Job_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Job_ArrayRef;

typedef struct _CIM_Job_ConstArrayRef
{
    CIM_Job_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Job_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_Job_rtti;

MI_INLINE MI_Result MI_CALL CIM_Job_Construct(
    CIM_Job* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_Job_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clone(
    const CIM_Job* self,
    CIM_Job** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_Job_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_Job_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Destruct(CIM_Job* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Delete(CIM_Job* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Post(
    const CIM_Job* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_InstanceID(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Job_SetPtr_InstanceID(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_InstanceID(
    CIM_Job* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_Caption(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Job_SetPtr_Caption(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_Caption(
    CIM_Job* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_Description(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Job_SetPtr_Description(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_Description(
    CIM_Job* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_ElementName(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Job_SetPtr_ElementName(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_ElementName(
    CIM_Job* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_InstallDate(
    CIM_Job* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_InstallDate(
    CIM_Job* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_Name(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Job_SetPtr_Name(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_Name(
    CIM_Job* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_OperationalStatus(
    CIM_Job* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Job_SetPtr_OperationalStatus(
    CIM_Job* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_OperationalStatus(
    CIM_Job* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_StatusDescriptions(
    CIM_Job* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Job_SetPtr_StatusDescriptions(
    CIM_Job* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_StatusDescriptions(
    CIM_Job* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_Status(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Job_SetPtr_Status(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_Status(
    CIM_Job* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_HealthState(
    CIM_Job* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_HealthState(
    CIM_Job* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_CommunicationStatus(
    CIM_Job* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_CommunicationStatus(
    CIM_Job* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_DetailedStatus(
    CIM_Job* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_DetailedStatus(
    CIM_Job* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_OperatingStatus(
    CIM_Job* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_OperatingStatus(
    CIM_Job* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_PrimaryStatus(
    CIM_Job* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_PrimaryStatus(
    CIM_Job* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_JobStatus(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Job_SetPtr_JobStatus(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_JobStatus(
    CIM_Job* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_TimeSubmitted(
    CIM_Job* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeSubmitted)->value = x;
    ((MI_DatetimeField*)&self->TimeSubmitted)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_TimeSubmitted(
    CIM_Job* self)
{
    memset((void*)&self->TimeSubmitted, 0, sizeof(self->TimeSubmitted));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_ScheduledStartTime(
    CIM_Job* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->ScheduledStartTime)->value = x;
    ((MI_DatetimeField*)&self->ScheduledStartTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_ScheduledStartTime(
    CIM_Job* self)
{
    memset((void*)&self->ScheduledStartTime, 0, sizeof(self->ScheduledStartTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_StartTime(
    CIM_Job* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->StartTime)->value = x;
    ((MI_DatetimeField*)&self->StartTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_StartTime(
    CIM_Job* self)
{
    memset((void*)&self->StartTime, 0, sizeof(self->StartTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_ElapsedTime(
    CIM_Job* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->ElapsedTime)->value = x;
    ((MI_DatetimeField*)&self->ElapsedTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_ElapsedTime(
    CIM_Job* self)
{
    memset((void*)&self->ElapsedTime, 0, sizeof(self->ElapsedTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_JobRunTimes(
    CIM_Job* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->JobRunTimes)->value = x;
    ((MI_Uint32Field*)&self->JobRunTimes)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_JobRunTimes(
    CIM_Job* self)
{
    memset((void*)&self->JobRunTimes, 0, sizeof(self->JobRunTimes));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_RunMonth(
    CIM_Job* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->RunMonth)->value = x;
    ((MI_Uint8Field*)&self->RunMonth)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_RunMonth(
    CIM_Job* self)
{
    memset((void*)&self->RunMonth, 0, sizeof(self->RunMonth));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_RunDay(
    CIM_Job* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->RunDay)->value = x;
    ((MI_Sint8Field*)&self->RunDay)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_RunDay(
    CIM_Job* self)
{
    memset((void*)&self->RunDay, 0, sizeof(self->RunDay));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_RunDayOfWeek(
    CIM_Job* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->RunDayOfWeek)->value = x;
    ((MI_Sint8Field*)&self->RunDayOfWeek)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_RunDayOfWeek(
    CIM_Job* self)
{
    memset((void*)&self->RunDayOfWeek, 0, sizeof(self->RunDayOfWeek));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_RunStartInterval(
    CIM_Job* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->RunStartInterval)->value = x;
    ((MI_DatetimeField*)&self->RunStartInterval)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_RunStartInterval(
    CIM_Job* self)
{
    memset((void*)&self->RunStartInterval, 0, sizeof(self->RunStartInterval));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_LocalOrUtcTime(
    CIM_Job* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->LocalOrUtcTime)->value = x;
    ((MI_Uint16Field*)&self->LocalOrUtcTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_LocalOrUtcTime(
    CIM_Job* self)
{
    memset((void*)&self->LocalOrUtcTime, 0, sizeof(self->LocalOrUtcTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_UntilTime(
    CIM_Job* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->UntilTime)->value = x;
    ((MI_DatetimeField*)&self->UntilTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_UntilTime(
    CIM_Job* self)
{
    memset((void*)&self->UntilTime, 0, sizeof(self->UntilTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_Notify(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Job_SetPtr_Notify(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_Notify(
    CIM_Job* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_Owner(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Job_SetPtr_Owner(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_Owner(
    CIM_Job* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        27);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_Priority(
    CIM_Job* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Priority)->value = x;
    ((MI_Uint32Field*)&self->Priority)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_Priority(
    CIM_Job* self)
{
    memset((void*)&self->Priority, 0, sizeof(self->Priority));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_PercentComplete(
    CIM_Job* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PercentComplete)->value = x;
    ((MI_Uint16Field*)&self->PercentComplete)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_PercentComplete(
    CIM_Job* self)
{
    memset((void*)&self->PercentComplete, 0, sizeof(self->PercentComplete));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_DeleteOnCompletion(
    CIM_Job* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->DeleteOnCompletion)->value = x;
    ((MI_BooleanField*)&self->DeleteOnCompletion)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_DeleteOnCompletion(
    CIM_Job* self)
{
    memset((void*)&self->DeleteOnCompletion, 0, sizeof(self->DeleteOnCompletion));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_ErrorCode(
    CIM_Job* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ErrorCode)->value = x;
    ((MI_Uint16Field*)&self->ErrorCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_ErrorCode(
    CIM_Job* self)
{
    memset((void*)&self->ErrorCode, 0, sizeof(self->ErrorCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_ErrorDescription(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Job_SetPtr_ErrorDescription(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_ErrorDescription(
    CIM_Job* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        32);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_RecoveryAction(
    CIM_Job* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RecoveryAction)->value = x;
    ((MI_Uint16Field*)&self->RecoveryAction)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_RecoveryAction(
    CIM_Job* self)
{
    memset((void*)&self->RecoveryAction, 0, sizeof(self->RecoveryAction));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_Set_OtherRecoveryAction(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        34,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Job_SetPtr_OtherRecoveryAction(
    CIM_Job* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        34,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Job_Clear_OtherRecoveryAction(
    CIM_Job* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        34);
}

/*
**==============================================================================
**
** CIM_Job.KillJob()
**
**==============================================================================
*/

typedef struct _CIM_Job_KillJob
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField DeleteOnKill;
}
CIM_Job_KillJob;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_Job_KillJob_rtti;

MI_INLINE MI_Result MI_CALL CIM_Job_KillJob_Construct(
    CIM_Job_KillJob* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &CIM_Job_KillJob_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Job_KillJob_Clone(
    const CIM_Job_KillJob* self,
    CIM_Job_KillJob** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_Job_KillJob_Destruct(
    CIM_Job_KillJob* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Job_KillJob_Delete(
    CIM_Job_KillJob* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Job_KillJob_Post(
    const CIM_Job_KillJob* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Job_KillJob_Set_MIReturn(
    CIM_Job_KillJob* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_KillJob_Clear_MIReturn(
    CIM_Job_KillJob* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_KillJob_Set_DeleteOnKill(
    CIM_Job_KillJob* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->DeleteOnKill)->value = x;
    ((MI_BooleanField*)&self->DeleteOnKill)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Job_KillJob_Clear_DeleteOnKill(
    CIM_Job_KillJob* self)
{
    memset((void*)&self->DeleteOnKill, 0, sizeof(self->DeleteOnKill));
    return MI_RESULT_OK;
}


#endif /* _CIM_Job_h */
