/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_ConcreteJob_h
#define _CIM_ConcreteJob_h

#include <MI.h>
#include "CIM_Job.h"
#include "CIM_Error.h"

/*
**==============================================================================
**
** CIM_ConcreteJob [CIM_ConcreteJob]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_ConcreteJob /* extends CIM_Job */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
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
    /* CIM_ConcreteJob properties */
    MI_ConstUint16Field JobState;
    MI_ConstDatetimeField TimeOfLastStateChange;
    MI_ConstDatetimeField TimeBeforeRemoval;
}
CIM_ConcreteJob;

typedef struct _CIM_ConcreteJob_Ref
{
    CIM_ConcreteJob* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ConcreteJob_Ref;

typedef struct _CIM_ConcreteJob_ConstRef
{
    MI_CONST CIM_ConcreteJob* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ConcreteJob_ConstRef;

typedef struct _CIM_ConcreteJob_Array
{
    struct _CIM_ConcreteJob** data;
    MI_Uint32 size;
}
CIM_ConcreteJob_Array;

typedef struct _CIM_ConcreteJob_ConstArray
{
    struct _CIM_ConcreteJob MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_ConcreteJob_ConstArray;

typedef struct _CIM_ConcreteJob_ArrayRef
{
    CIM_ConcreteJob_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ConcreteJob_ArrayRef;

typedef struct _CIM_ConcreteJob_ConstArrayRef
{
    CIM_ConcreteJob_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ConcreteJob_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_ConcreteJob_rtti;

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Construct(
    CIM_ConcreteJob* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_ConcreteJob_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clone(
    const CIM_ConcreteJob* self,
    CIM_ConcreteJob** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_ConcreteJob_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_ConcreteJob_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Destruct(CIM_ConcreteJob* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Delete(CIM_ConcreteJob* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Post(
    const CIM_ConcreteJob* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_InstanceID(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_SetPtr_InstanceID(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_InstanceID(
    CIM_ConcreteJob* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_Caption(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_SetPtr_Caption(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_Caption(
    CIM_ConcreteJob* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_Description(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_SetPtr_Description(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_Description(
    CIM_ConcreteJob* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_ElementName(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_SetPtr_ElementName(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_ElementName(
    CIM_ConcreteJob* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_InstallDate(
    CIM_ConcreteJob* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_InstallDate(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_Name(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_SetPtr_Name(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_Name(
    CIM_ConcreteJob* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_OperationalStatus(
    CIM_ConcreteJob* self,
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

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_SetPtr_OperationalStatus(
    CIM_ConcreteJob* self,
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

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_OperationalStatus(
    CIM_ConcreteJob* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_StatusDescriptions(
    CIM_ConcreteJob* self,
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

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_SetPtr_StatusDescriptions(
    CIM_ConcreteJob* self,
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

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_StatusDescriptions(
    CIM_ConcreteJob* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_Status(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_SetPtr_Status(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_Status(
    CIM_ConcreteJob* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_HealthState(
    CIM_ConcreteJob* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_HealthState(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_CommunicationStatus(
    CIM_ConcreteJob* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_CommunicationStatus(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_DetailedStatus(
    CIM_ConcreteJob* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_DetailedStatus(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_OperatingStatus(
    CIM_ConcreteJob* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_OperatingStatus(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_PrimaryStatus(
    CIM_ConcreteJob* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_PrimaryStatus(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_JobStatus(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_SetPtr_JobStatus(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_JobStatus(
    CIM_ConcreteJob* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_TimeSubmitted(
    CIM_ConcreteJob* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeSubmitted)->value = x;
    ((MI_DatetimeField*)&self->TimeSubmitted)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_TimeSubmitted(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->TimeSubmitted, 0, sizeof(self->TimeSubmitted));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_ScheduledStartTime(
    CIM_ConcreteJob* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->ScheduledStartTime)->value = x;
    ((MI_DatetimeField*)&self->ScheduledStartTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_ScheduledStartTime(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->ScheduledStartTime, 0, sizeof(self->ScheduledStartTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_StartTime(
    CIM_ConcreteJob* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->StartTime)->value = x;
    ((MI_DatetimeField*)&self->StartTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_StartTime(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->StartTime, 0, sizeof(self->StartTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_ElapsedTime(
    CIM_ConcreteJob* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->ElapsedTime)->value = x;
    ((MI_DatetimeField*)&self->ElapsedTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_ElapsedTime(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->ElapsedTime, 0, sizeof(self->ElapsedTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_JobRunTimes(
    CIM_ConcreteJob* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->JobRunTimes)->value = x;
    ((MI_Uint32Field*)&self->JobRunTimes)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_JobRunTimes(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->JobRunTimes, 0, sizeof(self->JobRunTimes));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_RunMonth(
    CIM_ConcreteJob* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->RunMonth)->value = x;
    ((MI_Uint8Field*)&self->RunMonth)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_RunMonth(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->RunMonth, 0, sizeof(self->RunMonth));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_RunDay(
    CIM_ConcreteJob* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->RunDay)->value = x;
    ((MI_Sint8Field*)&self->RunDay)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_RunDay(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->RunDay, 0, sizeof(self->RunDay));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_RunDayOfWeek(
    CIM_ConcreteJob* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->RunDayOfWeek)->value = x;
    ((MI_Sint8Field*)&self->RunDayOfWeek)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_RunDayOfWeek(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->RunDayOfWeek, 0, sizeof(self->RunDayOfWeek));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_RunStartInterval(
    CIM_ConcreteJob* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->RunStartInterval)->value = x;
    ((MI_DatetimeField*)&self->RunStartInterval)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_RunStartInterval(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->RunStartInterval, 0, sizeof(self->RunStartInterval));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_LocalOrUtcTime(
    CIM_ConcreteJob* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->LocalOrUtcTime)->value = x;
    ((MI_Uint16Field*)&self->LocalOrUtcTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_LocalOrUtcTime(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->LocalOrUtcTime, 0, sizeof(self->LocalOrUtcTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_UntilTime(
    CIM_ConcreteJob* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->UntilTime)->value = x;
    ((MI_DatetimeField*)&self->UntilTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_UntilTime(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->UntilTime, 0, sizeof(self->UntilTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_Notify(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_SetPtr_Notify(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_Notify(
    CIM_ConcreteJob* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_Owner(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_SetPtr_Owner(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_Owner(
    CIM_ConcreteJob* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        27);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_Priority(
    CIM_ConcreteJob* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Priority)->value = x;
    ((MI_Uint32Field*)&self->Priority)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_Priority(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->Priority, 0, sizeof(self->Priority));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_PercentComplete(
    CIM_ConcreteJob* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PercentComplete)->value = x;
    ((MI_Uint16Field*)&self->PercentComplete)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_PercentComplete(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->PercentComplete, 0, sizeof(self->PercentComplete));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_DeleteOnCompletion(
    CIM_ConcreteJob* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->DeleteOnCompletion)->value = x;
    ((MI_BooleanField*)&self->DeleteOnCompletion)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_DeleteOnCompletion(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->DeleteOnCompletion, 0, sizeof(self->DeleteOnCompletion));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_ErrorCode(
    CIM_ConcreteJob* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ErrorCode)->value = x;
    ((MI_Uint16Field*)&self->ErrorCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_ErrorCode(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->ErrorCode, 0, sizeof(self->ErrorCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_ErrorDescription(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_SetPtr_ErrorDescription(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_ErrorDescription(
    CIM_ConcreteJob* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        32);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_RecoveryAction(
    CIM_ConcreteJob* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RecoveryAction)->value = x;
    ((MI_Uint16Field*)&self->RecoveryAction)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_RecoveryAction(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->RecoveryAction, 0, sizeof(self->RecoveryAction));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_OtherRecoveryAction(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        34,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_SetPtr_OtherRecoveryAction(
    CIM_ConcreteJob* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        34,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_OtherRecoveryAction(
    CIM_ConcreteJob* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        34);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_JobState(
    CIM_ConcreteJob* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->JobState)->value = x;
    ((MI_Uint16Field*)&self->JobState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_JobState(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->JobState, 0, sizeof(self->JobState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_TimeOfLastStateChange(
    CIM_ConcreteJob* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_TimeOfLastStateChange(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Set_TimeBeforeRemoval(
    CIM_ConcreteJob* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeBeforeRemoval)->value = x;
    ((MI_DatetimeField*)&self->TimeBeforeRemoval)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_Clear_TimeBeforeRemoval(
    CIM_ConcreteJob* self)
{
    memset((void*)&self->TimeBeforeRemoval, 0, sizeof(self->TimeBeforeRemoval));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_ConcreteJob.KillJob()
**
**==============================================================================
*/

typedef struct _CIM_ConcreteJob_KillJob
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField DeleteOnKill;
}
CIM_ConcreteJob_KillJob;

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_KillJob_Set_MIReturn(
    CIM_ConcreteJob_KillJob* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_KillJob_Clear_MIReturn(
    CIM_ConcreteJob_KillJob* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_KillJob_Set_DeleteOnKill(
    CIM_ConcreteJob_KillJob* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->DeleteOnKill)->value = x;
    ((MI_BooleanField*)&self->DeleteOnKill)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_KillJob_Clear_DeleteOnKill(
    CIM_ConcreteJob_KillJob* self)
{
    memset((void*)&self->DeleteOnKill, 0, sizeof(self->DeleteOnKill));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_ConcreteJob.RequestStateChange()
**
**==============================================================================
*/

typedef struct _CIM_ConcreteJob_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
CIM_ConcreteJob_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_ConcreteJob_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_RequestStateChange_Construct(
    CIM_ConcreteJob_RequestStateChange* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &CIM_ConcreteJob_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_RequestStateChange_Clone(
    const CIM_ConcreteJob_RequestStateChange* self,
    CIM_ConcreteJob_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_RequestStateChange_Destruct(
    CIM_ConcreteJob_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_RequestStateChange_Delete(
    CIM_ConcreteJob_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_RequestStateChange_Post(
    const CIM_ConcreteJob_RequestStateChange* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_RequestStateChange_Set_MIReturn(
    CIM_ConcreteJob_RequestStateChange* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_RequestStateChange_Clear_MIReturn(
    CIM_ConcreteJob_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_RequestStateChange_Set_RequestedState(
    CIM_ConcreteJob_RequestStateChange* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_RequestStateChange_Clear_RequestedState(
    CIM_ConcreteJob_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_RequestStateChange_Set_TimeoutPeriod(
    CIM_ConcreteJob_RequestStateChange* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_RequestStateChange_Clear_TimeoutPeriod(
    CIM_ConcreteJob_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_ConcreteJob.GetError()
**
**==============================================================================
*/

typedef struct _CIM_ConcreteJob_GetError
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ CIM_Error_ConstRef Error;
}
CIM_ConcreteJob_GetError;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_ConcreteJob_GetError_rtti;

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetError_Construct(
    CIM_ConcreteJob_GetError* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &CIM_ConcreteJob_GetError_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetError_Clone(
    const CIM_ConcreteJob_GetError* self,
    CIM_ConcreteJob_GetError** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetError_Destruct(
    CIM_ConcreteJob_GetError* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetError_Delete(
    CIM_ConcreteJob_GetError* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetError_Post(
    const CIM_ConcreteJob_GetError* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetError_Set_MIReturn(
    CIM_ConcreteJob_GetError* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetError_Clear_MIReturn(
    CIM_ConcreteJob_GetError* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetError_Set_Error(
    CIM_ConcreteJob_GetError* self,
    const CIM_Error* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetError_SetPtr_Error(
    CIM_ConcreteJob_GetError* self,
    const CIM_Error* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetError_Clear_Error(
    CIM_ConcreteJob_GetError* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** CIM_ConcreteJob.GetErrors()
**
**==============================================================================
*/

typedef struct _CIM_ConcreteJob_GetErrors
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ CIM_Error_ConstArrayRef Errors;
}
CIM_ConcreteJob_GetErrors;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_ConcreteJob_GetErrors_rtti;

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetErrors_Construct(
    CIM_ConcreteJob_GetErrors* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &CIM_ConcreteJob_GetErrors_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetErrors_Clone(
    const CIM_ConcreteJob_GetErrors* self,
    CIM_ConcreteJob_GetErrors** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetErrors_Destruct(
    CIM_ConcreteJob_GetErrors* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetErrors_Delete(
    CIM_ConcreteJob_GetErrors* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetErrors_Post(
    const CIM_ConcreteJob_GetErrors* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetErrors_Set_MIReturn(
    CIM_ConcreteJob_GetErrors* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetErrors_Clear_MIReturn(
    CIM_ConcreteJob_GetErrors* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetErrors_Set_Errors(
    CIM_ConcreteJob_GetErrors* self,
    const CIM_Error * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetErrors_SetPtr_Errors(
    CIM_ConcreteJob_GetErrors* self,
    const CIM_Error * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ConcreteJob_GetErrors_Clear_Errors(
    CIM_ConcreteJob_GetErrors* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _CIM_ConcreteJob_h */
