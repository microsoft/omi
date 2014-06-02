/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_VirtualTerminal_h
#define _MSFT_VirtualTerminal_h

#include <MI.h>
#include "CIM_LogicalDevice.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** MSFT_VirtualTerminal [MSFT_VirtualTerminal]
**
** Keys:
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**    DeviceID
**
**==============================================================================
*/

typedef struct _MSFT_VirtualTerminal /* extends CIM_LogicalDevice */
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
    /* MSFT_VirtualTerminal properties */
    MI_ConstUint32Field ExecTimeout;
    MI_ConstUint32AField AccessClassIn;
    MI_ConstUint32AField AccessClassOut;
}
MSFT_VirtualTerminal;

typedef struct _MSFT_VirtualTerminal_Ref
{
    MSFT_VirtualTerminal* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_VirtualTerminal_Ref;

typedef struct _MSFT_VirtualTerminal_ConstRef
{
    MI_CONST MSFT_VirtualTerminal* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_VirtualTerminal_ConstRef;

typedef struct _MSFT_VirtualTerminal_Array
{
    struct _MSFT_VirtualTerminal** data;
    MI_Uint32 size;
}
MSFT_VirtualTerminal_Array;

typedef struct _MSFT_VirtualTerminal_ConstArray
{
    struct _MSFT_VirtualTerminal MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_VirtualTerminal_ConstArray;

typedef struct _MSFT_VirtualTerminal_ArrayRef
{
    MSFT_VirtualTerminal_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_VirtualTerminal_ArrayRef;

typedef struct _MSFT_VirtualTerminal_ConstArrayRef
{
    MSFT_VirtualTerminal_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_VirtualTerminal_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_VirtualTerminal_rtti;

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Construct(
    _Out_ MSFT_VirtualTerminal* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_VirtualTerminal_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clone(
    _In_ const MSFT_VirtualTerminal* self,
    _Outptr_ MSFT_VirtualTerminal** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_VirtualTerminal_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_VirtualTerminal_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Destruct(_Inout_ MSFT_VirtualTerminal* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Delete(_Inout_ MSFT_VirtualTerminal* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Post(
    _In_ const MSFT_VirtualTerminal* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_InstanceID(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_InstanceID(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_InstanceID(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_Caption(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_Caption(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_Caption(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_Description(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_Description(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_Description(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_ElementName(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_ElementName(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_ElementName(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_InstallDate(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_InstallDate(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_Name(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_Name(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_Name(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_OperationalStatus(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_OperationalStatus(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_OperationalStatus(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_StatusDescriptions(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_StatusDescriptions(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_StatusDescriptions(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_Status(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_Status(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_Status(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_HealthState(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_HealthState(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_CommunicationStatus(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_CommunicationStatus(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_DetailedStatus(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_DetailedStatus(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_OperatingStatus(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_OperatingStatus(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_PrimaryStatus(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_PrimaryStatus(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_EnabledState(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_EnabledState(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_OtherEnabledState(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_OtherEnabledState(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_OtherEnabledState(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_RequestedState(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_RequestedState(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_EnabledDefault(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_EnabledDefault(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_TimeOfLastStateChange(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_TimeOfLastStateChange(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_AvailableRequestedStates(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_AvailableRequestedStates(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_AvailableRequestedStates(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_TransitioningToState(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_TransitioningToState(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_SystemCreationClassName(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_SystemCreationClassName(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_SystemCreationClassName(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_SystemName(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_SystemName(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_SystemName(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_CreationClassName(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_CreationClassName(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_CreationClassName(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_DeviceID(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_DeviceID(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_DeviceID(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_PowerManagementSupported(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->PowerManagementSupported)->value = x;
    ((MI_BooleanField*)&self->PowerManagementSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_PowerManagementSupported(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->PowerManagementSupported, 0, sizeof(self->PowerManagementSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_PowerManagementCapabilities(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_PowerManagementCapabilities(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_PowerManagementCapabilities(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_Availability(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Availability)->value = x;
    ((MI_Uint16Field*)&self->Availability)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_Availability(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->Availability, 0, sizeof(self->Availability));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_StatusInfo(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->StatusInfo)->value = x;
    ((MI_Uint16Field*)&self->StatusInfo)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_StatusInfo(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->StatusInfo, 0, sizeof(self->StatusInfo));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_LastErrorCode(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->LastErrorCode)->value = x;
    ((MI_Uint32Field*)&self->LastErrorCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_LastErrorCode(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->LastErrorCode, 0, sizeof(self->LastErrorCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_ErrorDescription(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_ErrorDescription(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_ErrorDescription(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        30);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_ErrorCleared(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->ErrorCleared)->value = x;
    ((MI_BooleanField*)&self->ErrorCleared)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_ErrorCleared(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->ErrorCleared, 0, sizeof(self->ErrorCleared));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_OtherIdentifyingInfo(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_OtherIdentifyingInfo(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_OtherIdentifyingInfo(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        32);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_PowerOnHours(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->PowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->PowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_PowerOnHours(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->PowerOnHours, 0, sizeof(self->PowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_TotalPowerOnHours(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_TotalPowerOnHours(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->TotalPowerOnHours, 0, sizeof(self->TotalPowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_IdentifyingDescriptions(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_IdentifyingDescriptions(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_IdentifyingDescriptions(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        35);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_AdditionalAvailability(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_AdditionalAvailability(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_AdditionalAvailability(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        36);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_MaxQuiesceTime(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->value = x;
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_MaxQuiesceTime(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->MaxQuiesceTime, 0, sizeof(self->MaxQuiesceTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_ExecTimeout(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->ExecTimeout)->value = x;
    ((MI_Uint32Field*)&self->ExecTimeout)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_ExecTimeout(
    _Inout_ MSFT_VirtualTerminal* self)
{
    memset((void*)&self->ExecTimeout, 0, sizeof(self->ExecTimeout));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_AccessClassIn(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Uint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        39,
        (MI_Value*)&arr,
        MI_UINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_AccessClassIn(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Uint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        39,
        (MI_Value*)&arr,
        MI_UINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_AccessClassIn(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        39);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Set_AccessClassOut(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Uint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        40,
        (MI_Value*)&arr,
        MI_UINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPtr_AccessClassOut(
    _Inout_ MSFT_VirtualTerminal* self,
    _In_reads_opt_(size) const MI_Uint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        40,
        (MI_Value*)&arr,
        MI_UINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Clear_AccessClassOut(
    _Inout_ MSFT_VirtualTerminal* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        40);
}

/*
**==============================================================================
**
** MSFT_VirtualTerminal.RequestStateChange()
**
**==============================================================================
*/

typedef struct _MSFT_VirtualTerminal_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
MSFT_VirtualTerminal_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_VirtualTerminal_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RequestStateChange_Construct(
    _Out_ MSFT_VirtualTerminal_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_VirtualTerminal_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RequestStateChange_Clone(
    _In_ const MSFT_VirtualTerminal_RequestStateChange* self,
    _Outptr_ MSFT_VirtualTerminal_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RequestStateChange_Destruct(
    _Inout_ MSFT_VirtualTerminal_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RequestStateChange_Delete(
    _Inout_ MSFT_VirtualTerminal_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RequestStateChange_Post(
    _In_ const MSFT_VirtualTerminal_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RequestStateChange_Set_MIReturn(
    _Inout_ MSFT_VirtualTerminal_RequestStateChange* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RequestStateChange_Clear_MIReturn(
    _Inout_ MSFT_VirtualTerminal_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RequestStateChange_Set_RequestedState(
    _Inout_ MSFT_VirtualTerminal_RequestStateChange* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RequestStateChange_Clear_RequestedState(
    _Inout_ MSFT_VirtualTerminal_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RequestStateChange_Set_Job(
    _Inout_ MSFT_VirtualTerminal_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RequestStateChange_SetPtr_Job(
    _Inout_ MSFT_VirtualTerminal_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RequestStateChange_Clear_Job(
    _Inout_ MSFT_VirtualTerminal_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RequestStateChange_Set_TimeoutPeriod(
    _Inout_ MSFT_VirtualTerminal_RequestStateChange* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RequestStateChange_Clear_TimeoutPeriod(
    _Inout_ MSFT_VirtualTerminal_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_VirtualTerminal.SetPowerState()
**
**==============================================================================
*/

typedef struct _MSFT_VirtualTerminal_SetPowerState
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field PowerState;
    /*IN*/ MI_ConstDatetimeField Time;
}
MSFT_VirtualTerminal_SetPowerState;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_VirtualTerminal_SetPowerState_rtti;

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPowerState_Construct(
    _Out_ MSFT_VirtualTerminal_SetPowerState* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_VirtualTerminal_SetPowerState_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPowerState_Clone(
    _In_ const MSFT_VirtualTerminal_SetPowerState* self,
    _Outptr_ MSFT_VirtualTerminal_SetPowerState** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPowerState_Destruct(
    _Inout_ MSFT_VirtualTerminal_SetPowerState* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPowerState_Delete(
    _Inout_ MSFT_VirtualTerminal_SetPowerState* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPowerState_Post(
    _In_ const MSFT_VirtualTerminal_SetPowerState* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPowerState_Set_MIReturn(
    _Inout_ MSFT_VirtualTerminal_SetPowerState* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPowerState_Clear_MIReturn(
    _Inout_ MSFT_VirtualTerminal_SetPowerState* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPowerState_Set_PowerState(
    _Inout_ MSFT_VirtualTerminal_SetPowerState* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PowerState)->value = x;
    ((MI_Uint16Field*)&self->PowerState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPowerState_Clear_PowerState(
    _Inout_ MSFT_VirtualTerminal_SetPowerState* self)
{
    memset((void*)&self->PowerState, 0, sizeof(self->PowerState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPowerState_Set_Time(
    _Inout_ MSFT_VirtualTerminal_SetPowerState* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->Time)->value = x;
    ((MI_DatetimeField*)&self->Time)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SetPowerState_Clear_Time(
    _Inout_ MSFT_VirtualTerminal_SetPowerState* self)
{
    memset((void*)&self->Time, 0, sizeof(self->Time));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_VirtualTerminal.Reset()
**
**==============================================================================
*/

typedef struct _MSFT_VirtualTerminal_Reset
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MSFT_VirtualTerminal_Reset;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_VirtualTerminal_Reset_rtti;

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Reset_Construct(
    _Out_ MSFT_VirtualTerminal_Reset* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_VirtualTerminal_Reset_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Reset_Clone(
    _In_ const MSFT_VirtualTerminal_Reset* self,
    _Outptr_ MSFT_VirtualTerminal_Reset** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Reset_Destruct(
    _Inout_ MSFT_VirtualTerminal_Reset* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Reset_Delete(
    _Inout_ MSFT_VirtualTerminal_Reset* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Reset_Post(
    _In_ const MSFT_VirtualTerminal_Reset* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Reset_Set_MIReturn(
    _Inout_ MSFT_VirtualTerminal_Reset* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_Reset_Clear_MIReturn(
    _Inout_ MSFT_VirtualTerminal_Reset* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_VirtualTerminal.EnableDevice()
**
**==============================================================================
*/

typedef struct _MSFT_VirtualTerminal_EnableDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Enabled;
}
MSFT_VirtualTerminal_EnableDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_VirtualTerminal_EnableDevice_rtti;

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_EnableDevice_Construct(
    _Out_ MSFT_VirtualTerminal_EnableDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_VirtualTerminal_EnableDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_EnableDevice_Clone(
    _In_ const MSFT_VirtualTerminal_EnableDevice* self,
    _Outptr_ MSFT_VirtualTerminal_EnableDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_EnableDevice_Destruct(
    _Inout_ MSFT_VirtualTerminal_EnableDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_EnableDevice_Delete(
    _Inout_ MSFT_VirtualTerminal_EnableDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_EnableDevice_Post(
    _In_ const MSFT_VirtualTerminal_EnableDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_EnableDevice_Set_MIReturn(
    _Inout_ MSFT_VirtualTerminal_EnableDevice* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_EnableDevice_Clear_MIReturn(
    _Inout_ MSFT_VirtualTerminal_EnableDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_EnableDevice_Set_Enabled(
    _Inout_ MSFT_VirtualTerminal_EnableDevice* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Enabled)->value = x;
    ((MI_BooleanField*)&self->Enabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_EnableDevice_Clear_Enabled(
    _Inout_ MSFT_VirtualTerminal_EnableDevice* self)
{
    memset((void*)&self->Enabled, 0, sizeof(self->Enabled));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_VirtualTerminal.OnlineDevice()
**
**==============================================================================
*/

typedef struct _MSFT_VirtualTerminal_OnlineDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Online;
}
MSFT_VirtualTerminal_OnlineDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_VirtualTerminal_OnlineDevice_rtti;

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_OnlineDevice_Construct(
    _Out_ MSFT_VirtualTerminal_OnlineDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_VirtualTerminal_OnlineDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_OnlineDevice_Clone(
    _In_ const MSFT_VirtualTerminal_OnlineDevice* self,
    _Outptr_ MSFT_VirtualTerminal_OnlineDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_OnlineDevice_Destruct(
    _Inout_ MSFT_VirtualTerminal_OnlineDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_OnlineDevice_Delete(
    _Inout_ MSFT_VirtualTerminal_OnlineDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_OnlineDevice_Post(
    _In_ const MSFT_VirtualTerminal_OnlineDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_OnlineDevice_Set_MIReturn(
    _Inout_ MSFT_VirtualTerminal_OnlineDevice* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_OnlineDevice_Clear_MIReturn(
    _Inout_ MSFT_VirtualTerminal_OnlineDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_OnlineDevice_Set_Online(
    _Inout_ MSFT_VirtualTerminal_OnlineDevice* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Online)->value = x;
    ((MI_BooleanField*)&self->Online)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_OnlineDevice_Clear_Online(
    _Inout_ MSFT_VirtualTerminal_OnlineDevice* self)
{
    memset((void*)&self->Online, 0, sizeof(self->Online));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_VirtualTerminal.QuiesceDevice()
**
**==============================================================================
*/

typedef struct _MSFT_VirtualTerminal_QuiesceDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Quiesce;
}
MSFT_VirtualTerminal_QuiesceDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_VirtualTerminal_QuiesceDevice_rtti;

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_QuiesceDevice_Construct(
    _Out_ MSFT_VirtualTerminal_QuiesceDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_VirtualTerminal_QuiesceDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_QuiesceDevice_Clone(
    _In_ const MSFT_VirtualTerminal_QuiesceDevice* self,
    _Outptr_ MSFT_VirtualTerminal_QuiesceDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_QuiesceDevice_Destruct(
    _Inout_ MSFT_VirtualTerminal_QuiesceDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_QuiesceDevice_Delete(
    _Inout_ MSFT_VirtualTerminal_QuiesceDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_QuiesceDevice_Post(
    _In_ const MSFT_VirtualTerminal_QuiesceDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_QuiesceDevice_Set_MIReturn(
    _Inout_ MSFT_VirtualTerminal_QuiesceDevice* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_QuiesceDevice_Clear_MIReturn(
    _Inout_ MSFT_VirtualTerminal_QuiesceDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_QuiesceDevice_Set_Quiesce(
    _Inout_ MSFT_VirtualTerminal_QuiesceDevice* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Quiesce)->value = x;
    ((MI_BooleanField*)&self->Quiesce)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_QuiesceDevice_Clear_Quiesce(
    _Inout_ MSFT_VirtualTerminal_QuiesceDevice* self)
{
    memset((void*)&self->Quiesce, 0, sizeof(self->Quiesce));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_VirtualTerminal.SaveProperties()
**
**==============================================================================
*/

typedef struct _MSFT_VirtualTerminal_SaveProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MSFT_VirtualTerminal_SaveProperties;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_VirtualTerminal_SaveProperties_rtti;

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SaveProperties_Construct(
    _Out_ MSFT_VirtualTerminal_SaveProperties* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_VirtualTerminal_SaveProperties_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SaveProperties_Clone(
    _In_ const MSFT_VirtualTerminal_SaveProperties* self,
    _Outptr_ MSFT_VirtualTerminal_SaveProperties** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SaveProperties_Destruct(
    _Inout_ MSFT_VirtualTerminal_SaveProperties* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SaveProperties_Delete(
    _Inout_ MSFT_VirtualTerminal_SaveProperties* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SaveProperties_Post(
    _In_ const MSFT_VirtualTerminal_SaveProperties* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SaveProperties_Set_MIReturn(
    _Inout_ MSFT_VirtualTerminal_SaveProperties* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_SaveProperties_Clear_MIReturn(
    _Inout_ MSFT_VirtualTerminal_SaveProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_VirtualTerminal.RestoreProperties()
**
**==============================================================================
*/

typedef struct _MSFT_VirtualTerminal_RestoreProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MSFT_VirtualTerminal_RestoreProperties;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_VirtualTerminal_RestoreProperties_rtti;

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RestoreProperties_Construct(
    _Out_ MSFT_VirtualTerminal_RestoreProperties* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_VirtualTerminal_RestoreProperties_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RestoreProperties_Clone(
    _In_ const MSFT_VirtualTerminal_RestoreProperties* self,
    _Outptr_ MSFT_VirtualTerminal_RestoreProperties** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RestoreProperties_Destruct(
    _Inout_ MSFT_VirtualTerminal_RestoreProperties* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RestoreProperties_Delete(
    _Inout_ MSFT_VirtualTerminal_RestoreProperties* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RestoreProperties_Post(
    _In_ const MSFT_VirtualTerminal_RestoreProperties* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RestoreProperties_Set_MIReturn(
    _Inout_ MSFT_VirtualTerminal_RestoreProperties* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_VirtualTerminal_RestoreProperties_Clear_MIReturn(
    _Inout_ MSFT_VirtualTerminal_RestoreProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_VirtualTerminal provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_VirtualTerminal_Self MSFT_VirtualTerminal_Self;

MI_EXTERN_C void MI_CALL MSFT_VirtualTerminal_Load(
    _Outptr_result_maybenull_ MSFT_VirtualTerminal_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_VirtualTerminal_Unload(
    _In_opt_ MSFT_VirtualTerminal_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_VirtualTerminal_EnumerateInstances(
    _In_opt_ MSFT_VirtualTerminal_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_VirtualTerminal_GetInstance(
    _In_opt_ MSFT_VirtualTerminal_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_VirtualTerminal* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_VirtualTerminal_CreateInstance(
    _In_opt_ MSFT_VirtualTerminal_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_VirtualTerminal* newInstance);

MI_EXTERN_C void MI_CALL MSFT_VirtualTerminal_ModifyInstance(
    _In_opt_ MSFT_VirtualTerminal_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_VirtualTerminal* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_VirtualTerminal_DeleteInstance(
    _In_opt_ MSFT_VirtualTerminal_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_VirtualTerminal* instanceName);

MI_EXTERN_C void MI_CALL MSFT_VirtualTerminal_Invoke_RequestStateChange(
    _In_opt_ MSFT_VirtualTerminal_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_VirtualTerminal* instanceName,
    _In_opt_ const MSFT_VirtualTerminal_RequestStateChange* in);

MI_EXTERN_C void MI_CALL MSFT_VirtualTerminal_Invoke_SetPowerState(
    _In_opt_ MSFT_VirtualTerminal_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_VirtualTerminal* instanceName,
    _In_opt_ const MSFT_VirtualTerminal_SetPowerState* in);

MI_EXTERN_C void MI_CALL MSFT_VirtualTerminal_Invoke_Reset(
    _In_opt_ MSFT_VirtualTerminal_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_VirtualTerminal* instanceName,
    _In_opt_ const MSFT_VirtualTerminal_Reset* in);

MI_EXTERN_C void MI_CALL MSFT_VirtualTerminal_Invoke_EnableDevice(
    _In_opt_ MSFT_VirtualTerminal_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_VirtualTerminal* instanceName,
    _In_opt_ const MSFT_VirtualTerminal_EnableDevice* in);

MI_EXTERN_C void MI_CALL MSFT_VirtualTerminal_Invoke_OnlineDevice(
    _In_opt_ MSFT_VirtualTerminal_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_VirtualTerminal* instanceName,
    _In_opt_ const MSFT_VirtualTerminal_OnlineDevice* in);

MI_EXTERN_C void MI_CALL MSFT_VirtualTerminal_Invoke_QuiesceDevice(
    _In_opt_ MSFT_VirtualTerminal_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_VirtualTerminal* instanceName,
    _In_opt_ const MSFT_VirtualTerminal_QuiesceDevice* in);

MI_EXTERN_C void MI_CALL MSFT_VirtualTerminal_Invoke_SaveProperties(
    _In_opt_ MSFT_VirtualTerminal_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_VirtualTerminal* instanceName,
    _In_opt_ const MSFT_VirtualTerminal_SaveProperties* in);

MI_EXTERN_C void MI_CALL MSFT_VirtualTerminal_Invoke_RestoreProperties(
    _In_opt_ MSFT_VirtualTerminal_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_VirtualTerminal* instanceName,
    _In_opt_ const MSFT_VirtualTerminal_RestoreProperties* in);


#endif /* _MSFT_VirtualTerminal_h */
