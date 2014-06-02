/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_Fan_h
#define _ABC_Fan_h

#include <MI.h>
#include "CIM_Fan.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** ABC_Fan [ABC_Fan]
**
** Keys:
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**    DeviceID
**
**==============================================================================
*/

typedef struct _ABC_Fan /* extends CIM_Fan */
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
    /* CIM_CoolingDevice properties */
    MI_ConstBooleanField ActiveCooling;
    /* CIM_Fan properties */
    MI_ConstBooleanField VariableSpeed;
    MI_ConstUint64Field DesiredSpeed;
    /* ABC_Fan properties */
}
ABC_Fan;

typedef struct _ABC_Fan_Ref
{
    ABC_Fan* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Fan_Ref;

typedef struct _ABC_Fan_ConstRef
{
    MI_CONST ABC_Fan* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Fan_ConstRef;

typedef struct _ABC_Fan_Array
{
    struct _ABC_Fan** data;
    MI_Uint32 size;
}
ABC_Fan_Array;

typedef struct _ABC_Fan_ConstArray
{
    struct _ABC_Fan MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_Fan_ConstArray;

typedef struct _ABC_Fan_ArrayRef
{
    ABC_Fan_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Fan_ArrayRef;

typedef struct _ABC_Fan_ConstArrayRef
{
    ABC_Fan_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Fan_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_Fan_rtti;

MI_INLINE MI_Result MI_CALL ABC_Fan_Construct(
    ABC_Fan* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_Fan_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clone(
    const ABC_Fan* self,
    ABC_Fan** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_Fan_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_Fan_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Destruct(ABC_Fan* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Delete(ABC_Fan* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Post(
    const ABC_Fan* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_InstanceID(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_InstanceID(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_InstanceID(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_Caption(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_Caption(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_Caption(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_Description(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_Description(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_Description(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_ElementName(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_ElementName(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_ElementName(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_InstallDate(
    ABC_Fan* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_InstallDate(
    ABC_Fan* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_Name(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_Name(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_Name(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_OperationalStatus(
    ABC_Fan* self,
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

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_OperationalStatus(
    ABC_Fan* self,
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

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_OperationalStatus(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_StatusDescriptions(
    ABC_Fan* self,
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

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_StatusDescriptions(
    ABC_Fan* self,
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

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_StatusDescriptions(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_Status(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_Status(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_Status(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_HealthState(
    ABC_Fan* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_HealthState(
    ABC_Fan* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_CommunicationStatus(
    ABC_Fan* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_CommunicationStatus(
    ABC_Fan* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_DetailedStatus(
    ABC_Fan* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_DetailedStatus(
    ABC_Fan* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_OperatingStatus(
    ABC_Fan* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_OperatingStatus(
    ABC_Fan* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_PrimaryStatus(
    ABC_Fan* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_PrimaryStatus(
    ABC_Fan* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_EnabledState(
    ABC_Fan* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_EnabledState(
    ABC_Fan* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_OtherEnabledState(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_OtherEnabledState(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_OtherEnabledState(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_RequestedState(
    ABC_Fan* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_RequestedState(
    ABC_Fan* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_EnabledDefault(
    ABC_Fan* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_EnabledDefault(
    ABC_Fan* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_TimeOfLastStateChange(
    ABC_Fan* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_TimeOfLastStateChange(
    ABC_Fan* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_AvailableRequestedStates(
    ABC_Fan* self,
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

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_AvailableRequestedStates(
    ABC_Fan* self,
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

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_AvailableRequestedStates(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_TransitioningToState(
    ABC_Fan* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_TransitioningToState(
    ABC_Fan* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_SystemCreationClassName(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_SystemCreationClassName(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_SystemCreationClassName(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_SystemName(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_SystemName(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_SystemName(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_CreationClassName(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_CreationClassName(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_CreationClassName(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_DeviceID(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_DeviceID(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_DeviceID(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_PowerManagementSupported(
    ABC_Fan* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->PowerManagementSupported)->value = x;
    ((MI_BooleanField*)&self->PowerManagementSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_PowerManagementSupported(
    ABC_Fan* self)
{
    memset((void*)&self->PowerManagementSupported, 0, sizeof(self->PowerManagementSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_PowerManagementCapabilities(
    ABC_Fan* self,
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

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_PowerManagementCapabilities(
    ABC_Fan* self,
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

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_PowerManagementCapabilities(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_Availability(
    ABC_Fan* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Availability)->value = x;
    ((MI_Uint16Field*)&self->Availability)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_Availability(
    ABC_Fan* self)
{
    memset((void*)&self->Availability, 0, sizeof(self->Availability));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_StatusInfo(
    ABC_Fan* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->StatusInfo)->value = x;
    ((MI_Uint16Field*)&self->StatusInfo)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_StatusInfo(
    ABC_Fan* self)
{
    memset((void*)&self->StatusInfo, 0, sizeof(self->StatusInfo));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_LastErrorCode(
    ABC_Fan* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->LastErrorCode)->value = x;
    ((MI_Uint32Field*)&self->LastErrorCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_LastErrorCode(
    ABC_Fan* self)
{
    memset((void*)&self->LastErrorCode, 0, sizeof(self->LastErrorCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_ErrorDescription(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_ErrorDescription(
    ABC_Fan* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_ErrorDescription(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        30);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_ErrorCleared(
    ABC_Fan* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->ErrorCleared)->value = x;
    ((MI_BooleanField*)&self->ErrorCleared)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_ErrorCleared(
    ABC_Fan* self)
{
    memset((void*)&self->ErrorCleared, 0, sizeof(self->ErrorCleared));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_OtherIdentifyingInfo(
    ABC_Fan* self,
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

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_OtherIdentifyingInfo(
    ABC_Fan* self,
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

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_OtherIdentifyingInfo(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        32);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_PowerOnHours(
    ABC_Fan* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->PowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->PowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_PowerOnHours(
    ABC_Fan* self)
{
    memset((void*)&self->PowerOnHours, 0, sizeof(self->PowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_TotalPowerOnHours(
    ABC_Fan* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_TotalPowerOnHours(
    ABC_Fan* self)
{
    memset((void*)&self->TotalPowerOnHours, 0, sizeof(self->TotalPowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_IdentifyingDescriptions(
    ABC_Fan* self,
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

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_IdentifyingDescriptions(
    ABC_Fan* self,
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

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_IdentifyingDescriptions(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        35);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_AdditionalAvailability(
    ABC_Fan* self,
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

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPtr_AdditionalAvailability(
    ABC_Fan* self,
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

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_AdditionalAvailability(
    ABC_Fan* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        36);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_MaxQuiesceTime(
    ABC_Fan* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->value = x;
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_MaxQuiesceTime(
    ABC_Fan* self)
{
    memset((void*)&self->MaxQuiesceTime, 0, sizeof(self->MaxQuiesceTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_ActiveCooling(
    ABC_Fan* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->ActiveCooling)->value = x;
    ((MI_BooleanField*)&self->ActiveCooling)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_ActiveCooling(
    ABC_Fan* self)
{
    memset((void*)&self->ActiveCooling, 0, sizeof(self->ActiveCooling));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_VariableSpeed(
    ABC_Fan* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->VariableSpeed)->value = x;
    ((MI_BooleanField*)&self->VariableSpeed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_VariableSpeed(
    ABC_Fan* self)
{
    memset((void*)&self->VariableSpeed, 0, sizeof(self->VariableSpeed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Set_DesiredSpeed(
    ABC_Fan* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->DesiredSpeed)->value = x;
    ((MI_Uint64Field*)&self->DesiredSpeed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Clear_DesiredSpeed(
    ABC_Fan* self)
{
    memset((void*)&self->DesiredSpeed, 0, sizeof(self->DesiredSpeed));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Fan.RequestStateChange()
**
**==============================================================================
*/

typedef struct _ABC_Fan_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
ABC_Fan_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Fan_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL ABC_Fan_RequestStateChange_Construct(
    ABC_Fan_RequestStateChange* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Fan_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RequestStateChange_Clone(
    const ABC_Fan_RequestStateChange* self,
    ABC_Fan_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RequestStateChange_Destruct(
    ABC_Fan_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RequestStateChange_Delete(
    ABC_Fan_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RequestStateChange_Post(
    const ABC_Fan_RequestStateChange* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RequestStateChange_Set_MIReturn(
    ABC_Fan_RequestStateChange* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RequestStateChange_Clear_MIReturn(
    ABC_Fan_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RequestStateChange_Set_RequestedState(
    ABC_Fan_RequestStateChange* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RequestStateChange_Clear_RequestedState(
    ABC_Fan_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RequestStateChange_Set_Job(
    ABC_Fan_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RequestStateChange_SetPtr_Job(
    ABC_Fan_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RequestStateChange_Clear_Job(
    ABC_Fan_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RequestStateChange_Set_TimeoutPeriod(
    ABC_Fan_RequestStateChange* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RequestStateChange_Clear_TimeoutPeriod(
    ABC_Fan_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Fan.SetPowerState()
**
**==============================================================================
*/

typedef struct _ABC_Fan_SetPowerState
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field PowerState;
    /*IN*/ MI_ConstDatetimeField Time;
}
ABC_Fan_SetPowerState;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Fan_SetPowerState_rtti;

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPowerState_Construct(
    ABC_Fan_SetPowerState* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Fan_SetPowerState_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPowerState_Clone(
    const ABC_Fan_SetPowerState* self,
    ABC_Fan_SetPowerState** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPowerState_Destruct(
    ABC_Fan_SetPowerState* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPowerState_Delete(
    ABC_Fan_SetPowerState* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPowerState_Post(
    const ABC_Fan_SetPowerState* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPowerState_Set_MIReturn(
    ABC_Fan_SetPowerState* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPowerState_Clear_MIReturn(
    ABC_Fan_SetPowerState* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPowerState_Set_PowerState(
    ABC_Fan_SetPowerState* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PowerState)->value = x;
    ((MI_Uint16Field*)&self->PowerState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPowerState_Clear_PowerState(
    ABC_Fan_SetPowerState* self)
{
    memset((void*)&self->PowerState, 0, sizeof(self->PowerState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPowerState_Set_Time(
    ABC_Fan_SetPowerState* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->Time)->value = x;
    ((MI_DatetimeField*)&self->Time)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetPowerState_Clear_Time(
    ABC_Fan_SetPowerState* self)
{
    memset((void*)&self->Time, 0, sizeof(self->Time));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Fan.Reset()
**
**==============================================================================
*/

typedef struct _ABC_Fan_Reset
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
ABC_Fan_Reset;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Fan_Reset_rtti;

MI_INLINE MI_Result MI_CALL ABC_Fan_Reset_Construct(
    ABC_Fan_Reset* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Fan_Reset_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Reset_Clone(
    const ABC_Fan_Reset* self,
    ABC_Fan_Reset** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Reset_Destruct(
    ABC_Fan_Reset* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Reset_Delete(
    ABC_Fan_Reset* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Reset_Post(
    const ABC_Fan_Reset* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Reset_Set_MIReturn(
    ABC_Fan_Reset* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_Reset_Clear_MIReturn(
    ABC_Fan_Reset* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Fan.EnableDevice()
**
**==============================================================================
*/

typedef struct _ABC_Fan_EnableDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Enabled;
}
ABC_Fan_EnableDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Fan_EnableDevice_rtti;

MI_INLINE MI_Result MI_CALL ABC_Fan_EnableDevice_Construct(
    ABC_Fan_EnableDevice* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Fan_EnableDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_EnableDevice_Clone(
    const ABC_Fan_EnableDevice* self,
    ABC_Fan_EnableDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_EnableDevice_Destruct(
    ABC_Fan_EnableDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_EnableDevice_Delete(
    ABC_Fan_EnableDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_EnableDevice_Post(
    const ABC_Fan_EnableDevice* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_EnableDevice_Set_MIReturn(
    ABC_Fan_EnableDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_EnableDevice_Clear_MIReturn(
    ABC_Fan_EnableDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_EnableDevice_Set_Enabled(
    ABC_Fan_EnableDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Enabled)->value = x;
    ((MI_BooleanField*)&self->Enabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_EnableDevice_Clear_Enabled(
    ABC_Fan_EnableDevice* self)
{
    memset((void*)&self->Enabled, 0, sizeof(self->Enabled));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Fan.OnlineDevice()
**
**==============================================================================
*/

typedef struct _ABC_Fan_OnlineDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Online;
}
ABC_Fan_OnlineDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Fan_OnlineDevice_rtti;

MI_INLINE MI_Result MI_CALL ABC_Fan_OnlineDevice_Construct(
    ABC_Fan_OnlineDevice* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Fan_OnlineDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_OnlineDevice_Clone(
    const ABC_Fan_OnlineDevice* self,
    ABC_Fan_OnlineDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_OnlineDevice_Destruct(
    ABC_Fan_OnlineDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_OnlineDevice_Delete(
    ABC_Fan_OnlineDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_OnlineDevice_Post(
    const ABC_Fan_OnlineDevice* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_OnlineDevice_Set_MIReturn(
    ABC_Fan_OnlineDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_OnlineDevice_Clear_MIReturn(
    ABC_Fan_OnlineDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_OnlineDevice_Set_Online(
    ABC_Fan_OnlineDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Online)->value = x;
    ((MI_BooleanField*)&self->Online)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_OnlineDevice_Clear_Online(
    ABC_Fan_OnlineDevice* self)
{
    memset((void*)&self->Online, 0, sizeof(self->Online));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Fan.QuiesceDevice()
**
**==============================================================================
*/

typedef struct _ABC_Fan_QuiesceDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Quiesce;
}
ABC_Fan_QuiesceDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Fan_QuiesceDevice_rtti;

MI_INLINE MI_Result MI_CALL ABC_Fan_QuiesceDevice_Construct(
    ABC_Fan_QuiesceDevice* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Fan_QuiesceDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_QuiesceDevice_Clone(
    const ABC_Fan_QuiesceDevice* self,
    ABC_Fan_QuiesceDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_QuiesceDevice_Destruct(
    ABC_Fan_QuiesceDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_QuiesceDevice_Delete(
    ABC_Fan_QuiesceDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_QuiesceDevice_Post(
    const ABC_Fan_QuiesceDevice* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_QuiesceDevice_Set_MIReturn(
    ABC_Fan_QuiesceDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_QuiesceDevice_Clear_MIReturn(
    ABC_Fan_QuiesceDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_QuiesceDevice_Set_Quiesce(
    ABC_Fan_QuiesceDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Quiesce)->value = x;
    ((MI_BooleanField*)&self->Quiesce)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_QuiesceDevice_Clear_Quiesce(
    ABC_Fan_QuiesceDevice* self)
{
    memset((void*)&self->Quiesce, 0, sizeof(self->Quiesce));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Fan.SaveProperties()
**
**==============================================================================
*/

typedef struct _ABC_Fan_SaveProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
ABC_Fan_SaveProperties;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Fan_SaveProperties_rtti;

MI_INLINE MI_Result MI_CALL ABC_Fan_SaveProperties_Construct(
    ABC_Fan_SaveProperties* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Fan_SaveProperties_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SaveProperties_Clone(
    const ABC_Fan_SaveProperties* self,
    ABC_Fan_SaveProperties** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SaveProperties_Destruct(
    ABC_Fan_SaveProperties* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SaveProperties_Delete(
    ABC_Fan_SaveProperties* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SaveProperties_Post(
    const ABC_Fan_SaveProperties* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SaveProperties_Set_MIReturn(
    ABC_Fan_SaveProperties* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SaveProperties_Clear_MIReturn(
    ABC_Fan_SaveProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Fan.RestoreProperties()
**
**==============================================================================
*/

typedef struct _ABC_Fan_RestoreProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
ABC_Fan_RestoreProperties;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Fan_RestoreProperties_rtti;

MI_INLINE MI_Result MI_CALL ABC_Fan_RestoreProperties_Construct(
    ABC_Fan_RestoreProperties* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Fan_RestoreProperties_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RestoreProperties_Clone(
    const ABC_Fan_RestoreProperties* self,
    ABC_Fan_RestoreProperties** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RestoreProperties_Destruct(
    ABC_Fan_RestoreProperties* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RestoreProperties_Delete(
    ABC_Fan_RestoreProperties* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RestoreProperties_Post(
    const ABC_Fan_RestoreProperties* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RestoreProperties_Set_MIReturn(
    ABC_Fan_RestoreProperties* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_RestoreProperties_Clear_MIReturn(
    ABC_Fan_RestoreProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Fan.SetSpeed()
**
**==============================================================================
*/

typedef struct _ABC_Fan_SetSpeed
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint64Field DesiredSpeed;
}
ABC_Fan_SetSpeed;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Fan_SetSpeed_rtti;

MI_INLINE MI_Result MI_CALL ABC_Fan_SetSpeed_Construct(
    ABC_Fan_SetSpeed* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Fan_SetSpeed_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetSpeed_Clone(
    const ABC_Fan_SetSpeed* self,
    ABC_Fan_SetSpeed** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetSpeed_Destruct(
    ABC_Fan_SetSpeed* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetSpeed_Delete(
    ABC_Fan_SetSpeed* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetSpeed_Post(
    const ABC_Fan_SetSpeed* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetSpeed_Set_MIReturn(
    ABC_Fan_SetSpeed* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetSpeed_Clear_MIReturn(
    ABC_Fan_SetSpeed* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetSpeed_Set_DesiredSpeed(
    ABC_Fan_SetSpeed* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->DesiredSpeed)->value = x;
    ((MI_Uint64Field*)&self->DesiredSpeed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Fan_SetSpeed_Clear_DesiredSpeed(
    ABC_Fan_SetSpeed* self)
{
    memset((void*)&self->DesiredSpeed, 0, sizeof(self->DesiredSpeed));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Fan provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_Fan_Self ABC_Fan_Self;

MI_EXTERN_C void MI_CALL ABC_Fan_Load(
    ABC_Fan_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_Fan_Unload(
    ABC_Fan_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_Fan_EnumerateInstances(
    ABC_Fan_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_Fan_GetInstance(
    ABC_Fan_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Fan* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_Fan_CreateInstance(
    ABC_Fan_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Fan* newInstance);

MI_EXTERN_C void MI_CALL ABC_Fan_ModifyInstance(
    ABC_Fan_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Fan* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_Fan_DeleteInstance(
    ABC_Fan_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Fan* instanceName);

MI_EXTERN_C void MI_CALL ABC_Fan_Invoke_RequestStateChange(
    ABC_Fan_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Fan* instanceName,
    const ABC_Fan_RequestStateChange* in);

MI_EXTERN_C void MI_CALL ABC_Fan_Invoke_SetPowerState(
    ABC_Fan_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Fan* instanceName,
    const ABC_Fan_SetPowerState* in);

MI_EXTERN_C void MI_CALL ABC_Fan_Invoke_Reset(
    ABC_Fan_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Fan* instanceName,
    const ABC_Fan_Reset* in);

MI_EXTERN_C void MI_CALL ABC_Fan_Invoke_EnableDevice(
    ABC_Fan_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Fan* instanceName,
    const ABC_Fan_EnableDevice* in);

MI_EXTERN_C void MI_CALL ABC_Fan_Invoke_OnlineDevice(
    ABC_Fan_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Fan* instanceName,
    const ABC_Fan_OnlineDevice* in);

MI_EXTERN_C void MI_CALL ABC_Fan_Invoke_QuiesceDevice(
    ABC_Fan_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Fan* instanceName,
    const ABC_Fan_QuiesceDevice* in);

MI_EXTERN_C void MI_CALL ABC_Fan_Invoke_SaveProperties(
    ABC_Fan_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Fan* instanceName,
    const ABC_Fan_SaveProperties* in);

MI_EXTERN_C void MI_CALL ABC_Fan_Invoke_RestoreProperties(
    ABC_Fan_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Fan* instanceName,
    const ABC_Fan_RestoreProperties* in);

MI_EXTERN_C void MI_CALL ABC_Fan_Invoke_SetSpeed(
    ABC_Fan_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Fan* instanceName,
    const ABC_Fan_SetSpeed* in);


#endif /* _ABC_Fan_h */
