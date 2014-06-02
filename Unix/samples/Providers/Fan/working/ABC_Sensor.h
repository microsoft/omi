/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_Sensor_h
#define _ABC_Sensor_h

#include <MI.h>
#include "CIM_Sensor.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** ABC_Sensor [ABC_Sensor]
**
** Keys:
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**    DeviceID
**
**==============================================================================
*/

typedef struct _ABC_Sensor /* extends CIM_Sensor */
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
    /* CIM_EnabledLogicalElement properties */
    MI_ConstUint16Field EnabledState;
    MI_ConstStringField OtherEnabledState;
    MI_ConstUint16Field RequestedState;
    MI_ConstUint16Field EnabledDefault;
    MI_ConstDatetimeField TimeOfLastStateChange;
    MI_ConstUint16AField AvailableRequestedStates;
    MI_ConstUint16Field TransitioningToState;
    /* CIM_LogicalDevice properties */
    /*KEY*/ MI_ConstStringField SystemCreationClassName;
    /*KEY*/ MI_ConstStringField SystemName;
    /*KEY*/ MI_ConstStringField CreationClassName;
    /*KEY*/ MI_ConstStringField DeviceID;
    MI_ConstBooleanField PowerManagementSupported;
    MI_ConstUint16AField PowerManagementCapabilities;
    MI_ConstUint16Field Availability;
    MI_ConstUint16Field StatusInfo;
    MI_ConstUint32Field LastErrorCode;
    MI_ConstStringField ErrorDescription;
    MI_ConstBooleanField ErrorCleared;
    MI_ConstStringAField OtherIdentifyingInfo;
    MI_ConstUint64Field PowerOnHours;
    MI_ConstUint64Field TotalPowerOnHours;
    MI_ConstStringAField IdentifyingDescriptions;
    MI_ConstUint16AField AdditionalAvailability;
    MI_ConstUint64Field MaxQuiesceTime;
    /* CIM_Sensor properties */
    MI_ConstUint16Field SensorType;
    MI_ConstStringField OtherSensorTypeDescription;
    MI_ConstStringAField PossibleStates;
    MI_ConstStringField CurrentState;
    MI_ConstUint64Field PollingInterval;
    MI_ConstStringField SensorContext;
    /* ABC_Sensor properties */
}
ABC_Sensor;

typedef struct _ABC_Sensor_Ref
{
    ABC_Sensor* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Sensor_Ref;

typedef struct _ABC_Sensor_ConstRef
{
    MI_CONST ABC_Sensor* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Sensor_ConstRef;

typedef struct _ABC_Sensor_Array
{
    struct _ABC_Sensor** data;
    MI_Uint32 size;
}
ABC_Sensor_Array;

typedef struct _ABC_Sensor_ConstArray
{
    struct _ABC_Sensor MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_Sensor_ConstArray;

typedef struct _ABC_Sensor_ArrayRef
{
    ABC_Sensor_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Sensor_ArrayRef;

typedef struct _ABC_Sensor_ConstArrayRef
{
    ABC_Sensor_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Sensor_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_Sensor_rtti;

MI_INLINE MI_Result MI_CALL ABC_Sensor_Construct(
    ABC_Sensor* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_Sensor_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clone(
    const ABC_Sensor* self,
    ABC_Sensor** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_Sensor_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_Sensor_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Destruct(ABC_Sensor* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Delete(ABC_Sensor* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Post(
    const ABC_Sensor* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_InstanceID(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_InstanceID(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_InstanceID(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_Caption(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_Caption(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_Caption(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_Description(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_Description(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_Description(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_ElementName(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_ElementName(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_ElementName(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_InstallDate(
    ABC_Sensor* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_InstallDate(
    ABC_Sensor* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_Name(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_Name(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_Name(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_OperationalStatus(
    ABC_Sensor* self,
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

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_OperationalStatus(
    ABC_Sensor* self,
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

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_OperationalStatus(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_StatusDescriptions(
    ABC_Sensor* self,
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

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_StatusDescriptions(
    ABC_Sensor* self,
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

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_StatusDescriptions(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_Status(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_Status(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_Status(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_HealthState(
    ABC_Sensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_HealthState(
    ABC_Sensor* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_CommunicationStatus(
    ABC_Sensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_CommunicationStatus(
    ABC_Sensor* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_DetailedStatus(
    ABC_Sensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_DetailedStatus(
    ABC_Sensor* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_OperatingStatus(
    ABC_Sensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_OperatingStatus(
    ABC_Sensor* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_PrimaryStatus(
    ABC_Sensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_PrimaryStatus(
    ABC_Sensor* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_EnabledState(
    ABC_Sensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_EnabledState(
    ABC_Sensor* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_OtherEnabledState(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_OtherEnabledState(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_OtherEnabledState(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_RequestedState(
    ABC_Sensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_RequestedState(
    ABC_Sensor* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_EnabledDefault(
    ABC_Sensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_EnabledDefault(
    ABC_Sensor* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_TimeOfLastStateChange(
    ABC_Sensor* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_TimeOfLastStateChange(
    ABC_Sensor* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_AvailableRequestedStates(
    ABC_Sensor* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_AvailableRequestedStates(
    ABC_Sensor* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_AvailableRequestedStates(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_TransitioningToState(
    ABC_Sensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_TransitioningToState(
    ABC_Sensor* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_SystemCreationClassName(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_SystemCreationClassName(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_SystemCreationClassName(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_SystemName(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_SystemName(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_SystemName(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_CreationClassName(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_CreationClassName(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_CreationClassName(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_DeviceID(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_DeviceID(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_DeviceID(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_PowerManagementSupported(
    ABC_Sensor* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->PowerManagementSupported)->value = x;
    ((MI_BooleanField*)&self->PowerManagementSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_PowerManagementSupported(
    ABC_Sensor* self)
{
    memset((void*)&self->PowerManagementSupported, 0, sizeof(self->PowerManagementSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_PowerManagementCapabilities(
    ABC_Sensor* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_PowerManagementCapabilities(
    ABC_Sensor* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_PowerManagementCapabilities(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_Availability(
    ABC_Sensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Availability)->value = x;
    ((MI_Uint16Field*)&self->Availability)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_Availability(
    ABC_Sensor* self)
{
    memset((void*)&self->Availability, 0, sizeof(self->Availability));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_StatusInfo(
    ABC_Sensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->StatusInfo)->value = x;
    ((MI_Uint16Field*)&self->StatusInfo)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_StatusInfo(
    ABC_Sensor* self)
{
    memset((void*)&self->StatusInfo, 0, sizeof(self->StatusInfo));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_LastErrorCode(
    ABC_Sensor* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->LastErrorCode)->value = x;
    ((MI_Uint32Field*)&self->LastErrorCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_LastErrorCode(
    ABC_Sensor* self)
{
    memset((void*)&self->LastErrorCode, 0, sizeof(self->LastErrorCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_ErrorDescription(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_ErrorDescription(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_ErrorDescription(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        30);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_ErrorCleared(
    ABC_Sensor* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->ErrorCleared)->value = x;
    ((MI_BooleanField*)&self->ErrorCleared)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_ErrorCleared(
    ABC_Sensor* self)
{
    memset((void*)&self->ErrorCleared, 0, sizeof(self->ErrorCleared));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_OtherIdentifyingInfo(
    ABC_Sensor* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_OtherIdentifyingInfo(
    ABC_Sensor* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_OtherIdentifyingInfo(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        32);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_PowerOnHours(
    ABC_Sensor* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->PowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->PowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_PowerOnHours(
    ABC_Sensor* self)
{
    memset((void*)&self->PowerOnHours, 0, sizeof(self->PowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_TotalPowerOnHours(
    ABC_Sensor* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_TotalPowerOnHours(
    ABC_Sensor* self)
{
    memset((void*)&self->TotalPowerOnHours, 0, sizeof(self->TotalPowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_IdentifyingDescriptions(
    ABC_Sensor* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        35,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_IdentifyingDescriptions(
    ABC_Sensor* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        35,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_IdentifyingDescriptions(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        35);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_AdditionalAvailability(
    ABC_Sensor* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        36,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_AdditionalAvailability(
    ABC_Sensor* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        36,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_AdditionalAvailability(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        36);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_MaxQuiesceTime(
    ABC_Sensor* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->value = x;
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_MaxQuiesceTime(
    ABC_Sensor* self)
{
    memset((void*)&self->MaxQuiesceTime, 0, sizeof(self->MaxQuiesceTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_SensorType(
    ABC_Sensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->SensorType)->value = x;
    ((MI_Uint16Field*)&self->SensorType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_SensorType(
    ABC_Sensor* self)
{
    memset((void*)&self->SensorType, 0, sizeof(self->SensorType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_OtherSensorTypeDescription(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        39,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_OtherSensorTypeDescription(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        39,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_OtherSensorTypeDescription(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        39);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_PossibleStates(
    ABC_Sensor* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        40,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_PossibleStates(
    ABC_Sensor* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        40,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_PossibleStates(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        40);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_CurrentState(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        41,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_CurrentState(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        41,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_CurrentState(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        41);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_PollingInterval(
    ABC_Sensor* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->PollingInterval)->value = x;
    ((MI_Uint64Field*)&self->PollingInterval)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_PollingInterval(
    ABC_Sensor* self)
{
    memset((void*)&self->PollingInterval, 0, sizeof(self->PollingInterval));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Set_SensorContext(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        43,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPtr_SensorContext(
    ABC_Sensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        43,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Clear_SensorContext(
    ABC_Sensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        43);
}

/*
**==============================================================================
**
** ABC_Sensor.RequestStateChange()
**
**==============================================================================
*/

typedef struct _ABC_Sensor_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
ABC_Sensor_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Sensor_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL ABC_Sensor_RequestStateChange_Construct(
    ABC_Sensor_RequestStateChange* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Sensor_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RequestStateChange_Clone(
    const ABC_Sensor_RequestStateChange* self,
    ABC_Sensor_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RequestStateChange_Destruct(
    ABC_Sensor_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RequestStateChange_Delete(
    ABC_Sensor_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RequestStateChange_Post(
    const ABC_Sensor_RequestStateChange* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RequestStateChange_Set_MIReturn(
    ABC_Sensor_RequestStateChange* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RequestStateChange_Clear_MIReturn(
    ABC_Sensor_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RequestStateChange_Set_RequestedState(
    ABC_Sensor_RequestStateChange* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RequestStateChange_Clear_RequestedState(
    ABC_Sensor_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RequestStateChange_Set_Job(
    ABC_Sensor_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RequestStateChange_SetPtr_Job(
    ABC_Sensor_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RequestStateChange_Clear_Job(
    ABC_Sensor_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RequestStateChange_Set_TimeoutPeriod(
    ABC_Sensor_RequestStateChange* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RequestStateChange_Clear_TimeoutPeriod(
    ABC_Sensor_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Sensor.SetPowerState()
**
**==============================================================================
*/

typedef struct _ABC_Sensor_SetPowerState
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field PowerState;
    /*IN*/ MI_ConstDatetimeField Time;
}
ABC_Sensor_SetPowerState;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Sensor_SetPowerState_rtti;

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPowerState_Construct(
    ABC_Sensor_SetPowerState* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Sensor_SetPowerState_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPowerState_Clone(
    const ABC_Sensor_SetPowerState* self,
    ABC_Sensor_SetPowerState** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPowerState_Destruct(
    ABC_Sensor_SetPowerState* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPowerState_Delete(
    ABC_Sensor_SetPowerState* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPowerState_Post(
    const ABC_Sensor_SetPowerState* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPowerState_Set_MIReturn(
    ABC_Sensor_SetPowerState* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPowerState_Clear_MIReturn(
    ABC_Sensor_SetPowerState* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPowerState_Set_PowerState(
    ABC_Sensor_SetPowerState* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PowerState)->value = x;
    ((MI_Uint16Field*)&self->PowerState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPowerState_Clear_PowerState(
    ABC_Sensor_SetPowerState* self)
{
    memset((void*)&self->PowerState, 0, sizeof(self->PowerState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPowerState_Set_Time(
    ABC_Sensor_SetPowerState* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->Time)->value = x;
    ((MI_DatetimeField*)&self->Time)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SetPowerState_Clear_Time(
    ABC_Sensor_SetPowerState* self)
{
    memset((void*)&self->Time, 0, sizeof(self->Time));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Sensor.Reset()
**
**==============================================================================
*/

typedef struct _ABC_Sensor_Reset
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
ABC_Sensor_Reset;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Sensor_Reset_rtti;

MI_INLINE MI_Result MI_CALL ABC_Sensor_Reset_Construct(
    ABC_Sensor_Reset* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Sensor_Reset_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Reset_Clone(
    const ABC_Sensor_Reset* self,
    ABC_Sensor_Reset** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Reset_Destruct(
    ABC_Sensor_Reset* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Reset_Delete(
    ABC_Sensor_Reset* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Reset_Post(
    const ABC_Sensor_Reset* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Reset_Set_MIReturn(
    ABC_Sensor_Reset* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_Reset_Clear_MIReturn(
    ABC_Sensor_Reset* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Sensor.EnableDevice()
**
**==============================================================================
*/

typedef struct _ABC_Sensor_EnableDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Enabled;
}
ABC_Sensor_EnableDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Sensor_EnableDevice_rtti;

MI_INLINE MI_Result MI_CALL ABC_Sensor_EnableDevice_Construct(
    ABC_Sensor_EnableDevice* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Sensor_EnableDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_EnableDevice_Clone(
    const ABC_Sensor_EnableDevice* self,
    ABC_Sensor_EnableDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_EnableDevice_Destruct(
    ABC_Sensor_EnableDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_EnableDevice_Delete(
    ABC_Sensor_EnableDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_EnableDevice_Post(
    const ABC_Sensor_EnableDevice* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_EnableDevice_Set_MIReturn(
    ABC_Sensor_EnableDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_EnableDevice_Clear_MIReturn(
    ABC_Sensor_EnableDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_EnableDevice_Set_Enabled(
    ABC_Sensor_EnableDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Enabled)->value = x;
    ((MI_BooleanField*)&self->Enabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_EnableDevice_Clear_Enabled(
    ABC_Sensor_EnableDevice* self)
{
    memset((void*)&self->Enabled, 0, sizeof(self->Enabled));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Sensor.OnlineDevice()
**
**==============================================================================
*/

typedef struct _ABC_Sensor_OnlineDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Online;
}
ABC_Sensor_OnlineDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Sensor_OnlineDevice_rtti;

MI_INLINE MI_Result MI_CALL ABC_Sensor_OnlineDevice_Construct(
    ABC_Sensor_OnlineDevice* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Sensor_OnlineDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_OnlineDevice_Clone(
    const ABC_Sensor_OnlineDevice* self,
    ABC_Sensor_OnlineDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_OnlineDevice_Destruct(
    ABC_Sensor_OnlineDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_OnlineDevice_Delete(
    ABC_Sensor_OnlineDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_OnlineDevice_Post(
    const ABC_Sensor_OnlineDevice* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_OnlineDevice_Set_MIReturn(
    ABC_Sensor_OnlineDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_OnlineDevice_Clear_MIReturn(
    ABC_Sensor_OnlineDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_OnlineDevice_Set_Online(
    ABC_Sensor_OnlineDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Online)->value = x;
    ((MI_BooleanField*)&self->Online)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_OnlineDevice_Clear_Online(
    ABC_Sensor_OnlineDevice* self)
{
    memset((void*)&self->Online, 0, sizeof(self->Online));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Sensor.QuiesceDevice()
**
**==============================================================================
*/

typedef struct _ABC_Sensor_QuiesceDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Quiesce;
}
ABC_Sensor_QuiesceDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Sensor_QuiesceDevice_rtti;

MI_INLINE MI_Result MI_CALL ABC_Sensor_QuiesceDevice_Construct(
    ABC_Sensor_QuiesceDevice* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Sensor_QuiesceDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_QuiesceDevice_Clone(
    const ABC_Sensor_QuiesceDevice* self,
    ABC_Sensor_QuiesceDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_QuiesceDevice_Destruct(
    ABC_Sensor_QuiesceDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_QuiesceDevice_Delete(
    ABC_Sensor_QuiesceDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_QuiesceDevice_Post(
    const ABC_Sensor_QuiesceDevice* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_QuiesceDevice_Set_MIReturn(
    ABC_Sensor_QuiesceDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_QuiesceDevice_Clear_MIReturn(
    ABC_Sensor_QuiesceDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_QuiesceDevice_Set_Quiesce(
    ABC_Sensor_QuiesceDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Quiesce)->value = x;
    ((MI_BooleanField*)&self->Quiesce)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_QuiesceDevice_Clear_Quiesce(
    ABC_Sensor_QuiesceDevice* self)
{
    memset((void*)&self->Quiesce, 0, sizeof(self->Quiesce));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Sensor.SaveProperties()
**
**==============================================================================
*/

typedef struct _ABC_Sensor_SaveProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
ABC_Sensor_SaveProperties;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Sensor_SaveProperties_rtti;

MI_INLINE MI_Result MI_CALL ABC_Sensor_SaveProperties_Construct(
    ABC_Sensor_SaveProperties* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Sensor_SaveProperties_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SaveProperties_Clone(
    const ABC_Sensor_SaveProperties* self,
    ABC_Sensor_SaveProperties** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SaveProperties_Destruct(
    ABC_Sensor_SaveProperties* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SaveProperties_Delete(
    ABC_Sensor_SaveProperties* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SaveProperties_Post(
    const ABC_Sensor_SaveProperties* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SaveProperties_Set_MIReturn(
    ABC_Sensor_SaveProperties* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_SaveProperties_Clear_MIReturn(
    ABC_Sensor_SaveProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Sensor.RestoreProperties()
**
**==============================================================================
*/

typedef struct _ABC_Sensor_RestoreProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
ABC_Sensor_RestoreProperties;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Sensor_RestoreProperties_rtti;

MI_INLINE MI_Result MI_CALL ABC_Sensor_RestoreProperties_Construct(
    ABC_Sensor_RestoreProperties* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Sensor_RestoreProperties_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RestoreProperties_Clone(
    const ABC_Sensor_RestoreProperties* self,
    ABC_Sensor_RestoreProperties** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RestoreProperties_Destruct(
    ABC_Sensor_RestoreProperties* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RestoreProperties_Delete(
    ABC_Sensor_RestoreProperties* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RestoreProperties_Post(
    const ABC_Sensor_RestoreProperties* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RestoreProperties_Set_MIReturn(
    ABC_Sensor_RestoreProperties* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Sensor_RestoreProperties_Clear_MIReturn(
    ABC_Sensor_RestoreProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Sensor provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_Sensor_Self ABC_Sensor_Self;

MI_EXTERN_C void MI_CALL ABC_Sensor_Load(
    ABC_Sensor_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_Sensor_Unload(
    ABC_Sensor_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_Sensor_EnumerateInstances(
    ABC_Sensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_Sensor_GetInstance(
    ABC_Sensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Sensor* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_Sensor_CreateInstance(
    ABC_Sensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Sensor* newInstance);

MI_EXTERN_C void MI_CALL ABC_Sensor_ModifyInstance(
    ABC_Sensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Sensor* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_Sensor_DeleteInstance(
    ABC_Sensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Sensor* instanceName);

MI_EXTERN_C void MI_CALL ABC_Sensor_Invoke_RequestStateChange(
    ABC_Sensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Sensor* instanceName,
    const ABC_Sensor_RequestStateChange* in);

MI_EXTERN_C void MI_CALL ABC_Sensor_Invoke_SetPowerState(
    ABC_Sensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Sensor* instanceName,
    const ABC_Sensor_SetPowerState* in);

MI_EXTERN_C void MI_CALL ABC_Sensor_Invoke_Reset(
    ABC_Sensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Sensor* instanceName,
    const ABC_Sensor_Reset* in);

MI_EXTERN_C void MI_CALL ABC_Sensor_Invoke_EnableDevice(
    ABC_Sensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Sensor* instanceName,
    const ABC_Sensor_EnableDevice* in);

MI_EXTERN_C void MI_CALL ABC_Sensor_Invoke_OnlineDevice(
    ABC_Sensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Sensor* instanceName,
    const ABC_Sensor_OnlineDevice* in);

MI_EXTERN_C void MI_CALL ABC_Sensor_Invoke_QuiesceDevice(
    ABC_Sensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Sensor* instanceName,
    const ABC_Sensor_QuiesceDevice* in);

MI_EXTERN_C void MI_CALL ABC_Sensor_Invoke_SaveProperties(
    ABC_Sensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Sensor* instanceName,
    const ABC_Sensor_SaveProperties* in);

MI_EXTERN_C void MI_CALL ABC_Sensor_Invoke_RestoreProperties(
    ABC_Sensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Sensor* instanceName,
    const ABC_Sensor_RestoreProperties* in);


#endif /* _ABC_Sensor_h */
