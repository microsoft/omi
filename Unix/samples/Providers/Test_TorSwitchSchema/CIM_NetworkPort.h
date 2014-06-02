/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_NetworkPort_h
#define _CIM_NetworkPort_h

#include <MI.h>
#include "CIM_LogicalPort.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** CIM_NetworkPort [CIM_NetworkPort]
**
** Keys:
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**    DeviceID
**
**==============================================================================
*/

typedef struct _CIM_NetworkPort /* extends CIM_LogicalPort */
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
    /* CIM_LogicalPort properties */
    MI_ConstUint64Field Speed;
    MI_ConstUint64Field MaxSpeed;
    MI_ConstUint64Field RequestedSpeed;
    MI_ConstUint16Field UsageRestriction;
    MI_ConstUint16Field PortType;
    MI_ConstStringField OtherPortType;
    /* CIM_NetworkPort properties */
    MI_ConstStringField OtherNetworkPortType;
    MI_ConstUint16Field PortNumber;
    MI_ConstUint16Field LinkTechnology;
    MI_ConstStringField OtherLinkTechnology;
    MI_ConstStringField PermanentAddress;
    MI_ConstStringAField NetworkAddresses;
    MI_ConstBooleanField FullDuplex;
    MI_ConstBooleanField AutoSense;
    MI_ConstUint64Field SupportedMaximumTransmissionUnit;
    MI_ConstUint64Field ActiveMaximumTransmissionUnit;
}
CIM_NetworkPort;

typedef struct _CIM_NetworkPort_Ref
{
    CIM_NetworkPort* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPort_Ref;

typedef struct _CIM_NetworkPort_ConstRef
{
    MI_CONST CIM_NetworkPort* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPort_ConstRef;

typedef struct _CIM_NetworkPort_Array
{
    struct _CIM_NetworkPort** data;
    MI_Uint32 size;
}
CIM_NetworkPort_Array;

typedef struct _CIM_NetworkPort_ConstArray
{
    struct _CIM_NetworkPort MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_NetworkPort_ConstArray;

typedef struct _CIM_NetworkPort_ArrayRef
{
    CIM_NetworkPort_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPort_ArrayRef;

typedef struct _CIM_NetworkPort_ConstArrayRef
{
    CIM_NetworkPort_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPort_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_NetworkPort_rtti;

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Construct(
    _Out_ CIM_NetworkPort* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_NetworkPort_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clone(
    _In_ const CIM_NetworkPort* self,
    _Outptr_ CIM_NetworkPort** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_NetworkPort_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_NetworkPort_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Destruct(_Inout_ CIM_NetworkPort* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Delete(_Inout_ CIM_NetworkPort* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Post(
    _In_ const CIM_NetworkPort* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_InstanceID(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_InstanceID(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_InstanceID(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_Caption(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_Caption(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_Caption(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_Description(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_Description(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_Description(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_ElementName(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_ElementName(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_ElementName(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_InstallDate(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_InstallDate(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_Name(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_Name(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_Name(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_OperationalStatus(
    _Inout_ CIM_NetworkPort* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_OperationalStatus(
    _Inout_ CIM_NetworkPort* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_OperationalStatus(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_StatusDescriptions(
    _Inout_ CIM_NetworkPort* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_StatusDescriptions(
    _Inout_ CIM_NetworkPort* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_StatusDescriptions(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_Status(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_Status(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_Status(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_HealthState(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_HealthState(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_CommunicationStatus(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_CommunicationStatus(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_DetailedStatus(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_DetailedStatus(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_OperatingStatus(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_OperatingStatus(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_PrimaryStatus(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_PrimaryStatus(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_EnabledState(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_EnabledState(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_OtherEnabledState(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_OtherEnabledState(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_OtherEnabledState(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_RequestedState(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_RequestedState(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_EnabledDefault(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_EnabledDefault(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_TimeOfLastStateChange(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_TimeOfLastStateChange(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_AvailableRequestedStates(
    _Inout_ CIM_NetworkPort* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_AvailableRequestedStates(
    _Inout_ CIM_NetworkPort* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_AvailableRequestedStates(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_TransitioningToState(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_TransitioningToState(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_SystemCreationClassName(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_SystemCreationClassName(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_SystemCreationClassName(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_SystemName(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_SystemName(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_SystemName(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_CreationClassName(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_CreationClassName(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_CreationClassName(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_DeviceID(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_DeviceID(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_DeviceID(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_PowerManagementSupported(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->PowerManagementSupported)->value = x;
    ((MI_BooleanField*)&self->PowerManagementSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_PowerManagementSupported(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->PowerManagementSupported, 0, sizeof(self->PowerManagementSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_PowerManagementCapabilities(
    _Inout_ CIM_NetworkPort* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_PowerManagementCapabilities(
    _Inout_ CIM_NetworkPort* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_PowerManagementCapabilities(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_Availability(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Availability)->value = x;
    ((MI_Uint16Field*)&self->Availability)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_Availability(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->Availability, 0, sizeof(self->Availability));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_StatusInfo(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->StatusInfo)->value = x;
    ((MI_Uint16Field*)&self->StatusInfo)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_StatusInfo(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->StatusInfo, 0, sizeof(self->StatusInfo));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_LastErrorCode(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->LastErrorCode)->value = x;
    ((MI_Uint32Field*)&self->LastErrorCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_LastErrorCode(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->LastErrorCode, 0, sizeof(self->LastErrorCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_ErrorDescription(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_ErrorDescription(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_ErrorDescription(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        30);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_ErrorCleared(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->ErrorCleared)->value = x;
    ((MI_BooleanField*)&self->ErrorCleared)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_ErrorCleared(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->ErrorCleared, 0, sizeof(self->ErrorCleared));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_OtherIdentifyingInfo(
    _Inout_ CIM_NetworkPort* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_OtherIdentifyingInfo(
    _Inout_ CIM_NetworkPort* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_OtherIdentifyingInfo(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        32);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_PowerOnHours(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->PowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->PowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_PowerOnHours(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->PowerOnHours, 0, sizeof(self->PowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_TotalPowerOnHours(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_TotalPowerOnHours(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->TotalPowerOnHours, 0, sizeof(self->TotalPowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_IdentifyingDescriptions(
    _Inout_ CIM_NetworkPort* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_IdentifyingDescriptions(
    _Inout_ CIM_NetworkPort* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_IdentifyingDescriptions(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        35);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_AdditionalAvailability(
    _Inout_ CIM_NetworkPort* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_AdditionalAvailability(
    _Inout_ CIM_NetworkPort* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_AdditionalAvailability(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        36);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_MaxQuiesceTime(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->value = x;
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_MaxQuiesceTime(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->MaxQuiesceTime, 0, sizeof(self->MaxQuiesceTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_Speed(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->Speed)->value = x;
    ((MI_Uint64Field*)&self->Speed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_Speed(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->Speed, 0, sizeof(self->Speed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_MaxSpeed(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MaxSpeed)->value = x;
    ((MI_Uint64Field*)&self->MaxSpeed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_MaxSpeed(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->MaxSpeed, 0, sizeof(self->MaxSpeed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_RequestedSpeed(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->RequestedSpeed)->value = x;
    ((MI_Uint64Field*)&self->RequestedSpeed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_RequestedSpeed(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->RequestedSpeed, 0, sizeof(self->RequestedSpeed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_UsageRestriction(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->UsageRestriction)->value = x;
    ((MI_Uint16Field*)&self->UsageRestriction)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_UsageRestriction(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->UsageRestriction, 0, sizeof(self->UsageRestriction));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_PortType(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PortType)->value = x;
    ((MI_Uint16Field*)&self->PortType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_PortType(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->PortType, 0, sizeof(self->PortType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_OtherPortType(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        43,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_OtherPortType(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        43,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_OtherPortType(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        43);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_OtherNetworkPortType(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        44,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_OtherNetworkPortType(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        44,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_OtherNetworkPortType(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        44);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_PortNumber(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PortNumber)->value = x;
    ((MI_Uint16Field*)&self->PortNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_PortNumber(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->PortNumber, 0, sizeof(self->PortNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_LinkTechnology(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->LinkTechnology)->value = x;
    ((MI_Uint16Field*)&self->LinkTechnology)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_LinkTechnology(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->LinkTechnology, 0, sizeof(self->LinkTechnology));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_OtherLinkTechnology(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        47,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_OtherLinkTechnology(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        47,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_OtherLinkTechnology(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        47);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_PermanentAddress(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        48,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_PermanentAddress(
    _Inout_ CIM_NetworkPort* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        48,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_PermanentAddress(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        48);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_NetworkAddresses(
    _Inout_ CIM_NetworkPort* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        49,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPtr_NetworkAddresses(
    _Inout_ CIM_NetworkPort* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        49,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_NetworkAddresses(
    _Inout_ CIM_NetworkPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        49);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_FullDuplex(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->FullDuplex)->value = x;
    ((MI_BooleanField*)&self->FullDuplex)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_FullDuplex(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->FullDuplex, 0, sizeof(self->FullDuplex));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_AutoSense(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->AutoSense)->value = x;
    ((MI_BooleanField*)&self->AutoSense)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_AutoSense(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->AutoSense, 0, sizeof(self->AutoSense));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_SupportedMaximumTransmissionUnit(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->SupportedMaximumTransmissionUnit)->value = x;
    ((MI_Uint64Field*)&self->SupportedMaximumTransmissionUnit)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_SupportedMaximumTransmissionUnit(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->SupportedMaximumTransmissionUnit, 0, sizeof(self->SupportedMaximumTransmissionUnit));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Set_ActiveMaximumTransmissionUnit(
    _Inout_ CIM_NetworkPort* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ActiveMaximumTransmissionUnit)->value = x;
    ((MI_Uint64Field*)&self->ActiveMaximumTransmissionUnit)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Clear_ActiveMaximumTransmissionUnit(
    _Inout_ CIM_NetworkPort* self)
{
    memset((void*)&self->ActiveMaximumTransmissionUnit, 0, sizeof(self->ActiveMaximumTransmissionUnit));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NetworkPort.RequestStateChange()
**
**==============================================================================
*/

typedef struct _CIM_NetworkPort_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
CIM_NetworkPort_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_NetworkPort_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RequestStateChange_Construct(
    _Out_ CIM_NetworkPort_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_NetworkPort_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RequestStateChange_Clone(
    _In_ const CIM_NetworkPort_RequestStateChange* self,
    _Outptr_ CIM_NetworkPort_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RequestStateChange_Destruct(
    _Inout_ CIM_NetworkPort_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RequestStateChange_Delete(
    _Inout_ CIM_NetworkPort_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RequestStateChange_Post(
    _In_ const CIM_NetworkPort_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RequestStateChange_Set_MIReturn(
    _Inout_ CIM_NetworkPort_RequestStateChange* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RequestStateChange_Clear_MIReturn(
    _Inout_ CIM_NetworkPort_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RequestStateChange_Set_RequestedState(
    _Inout_ CIM_NetworkPort_RequestStateChange* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RequestStateChange_Clear_RequestedState(
    _Inout_ CIM_NetworkPort_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RequestStateChange_Set_Job(
    _Inout_ CIM_NetworkPort_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RequestStateChange_SetPtr_Job(
    _Inout_ CIM_NetworkPort_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RequestStateChange_Clear_Job(
    _Inout_ CIM_NetworkPort_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RequestStateChange_Set_TimeoutPeriod(
    _Inout_ CIM_NetworkPort_RequestStateChange* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RequestStateChange_Clear_TimeoutPeriod(
    _Inout_ CIM_NetworkPort_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NetworkPort.SetPowerState()
**
**==============================================================================
*/

typedef struct _CIM_NetworkPort_SetPowerState
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field PowerState;
    /*IN*/ MI_ConstDatetimeField Time;
}
CIM_NetworkPort_SetPowerState;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_NetworkPort_SetPowerState_rtti;

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPowerState_Construct(
    _Out_ CIM_NetworkPort_SetPowerState* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_NetworkPort_SetPowerState_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPowerState_Clone(
    _In_ const CIM_NetworkPort_SetPowerState* self,
    _Outptr_ CIM_NetworkPort_SetPowerState** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPowerState_Destruct(
    _Inout_ CIM_NetworkPort_SetPowerState* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPowerState_Delete(
    _Inout_ CIM_NetworkPort_SetPowerState* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPowerState_Post(
    _In_ const CIM_NetworkPort_SetPowerState* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPowerState_Set_MIReturn(
    _Inout_ CIM_NetworkPort_SetPowerState* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPowerState_Clear_MIReturn(
    _Inout_ CIM_NetworkPort_SetPowerState* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPowerState_Set_PowerState(
    _Inout_ CIM_NetworkPort_SetPowerState* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PowerState)->value = x;
    ((MI_Uint16Field*)&self->PowerState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPowerState_Clear_PowerState(
    _Inout_ CIM_NetworkPort_SetPowerState* self)
{
    memset((void*)&self->PowerState, 0, sizeof(self->PowerState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPowerState_Set_Time(
    _Inout_ CIM_NetworkPort_SetPowerState* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->Time)->value = x;
    ((MI_DatetimeField*)&self->Time)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SetPowerState_Clear_Time(
    _Inout_ CIM_NetworkPort_SetPowerState* self)
{
    memset((void*)&self->Time, 0, sizeof(self->Time));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NetworkPort.Reset()
**
**==============================================================================
*/

typedef struct _CIM_NetworkPort_Reset
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
CIM_NetworkPort_Reset;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_NetworkPort_Reset_rtti;

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Reset_Construct(
    _Out_ CIM_NetworkPort_Reset* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_NetworkPort_Reset_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Reset_Clone(
    _In_ const CIM_NetworkPort_Reset* self,
    _Outptr_ CIM_NetworkPort_Reset** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Reset_Destruct(
    _Inout_ CIM_NetworkPort_Reset* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Reset_Delete(
    _Inout_ CIM_NetworkPort_Reset* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Reset_Post(
    _In_ const CIM_NetworkPort_Reset* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Reset_Set_MIReturn(
    _Inout_ CIM_NetworkPort_Reset* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_Reset_Clear_MIReturn(
    _Inout_ CIM_NetworkPort_Reset* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NetworkPort.EnableDevice()
**
**==============================================================================
*/

typedef struct _CIM_NetworkPort_EnableDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Enabled;
}
CIM_NetworkPort_EnableDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_NetworkPort_EnableDevice_rtti;

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_EnableDevice_Construct(
    _Out_ CIM_NetworkPort_EnableDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_NetworkPort_EnableDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_EnableDevice_Clone(
    _In_ const CIM_NetworkPort_EnableDevice* self,
    _Outptr_ CIM_NetworkPort_EnableDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_EnableDevice_Destruct(
    _Inout_ CIM_NetworkPort_EnableDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_EnableDevice_Delete(
    _Inout_ CIM_NetworkPort_EnableDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_EnableDevice_Post(
    _In_ const CIM_NetworkPort_EnableDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_EnableDevice_Set_MIReturn(
    _Inout_ CIM_NetworkPort_EnableDevice* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_EnableDevice_Clear_MIReturn(
    _Inout_ CIM_NetworkPort_EnableDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_EnableDevice_Set_Enabled(
    _Inout_ CIM_NetworkPort_EnableDevice* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Enabled)->value = x;
    ((MI_BooleanField*)&self->Enabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_EnableDevice_Clear_Enabled(
    _Inout_ CIM_NetworkPort_EnableDevice* self)
{
    memset((void*)&self->Enabled, 0, sizeof(self->Enabled));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NetworkPort.OnlineDevice()
**
**==============================================================================
*/

typedef struct _CIM_NetworkPort_OnlineDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Online;
}
CIM_NetworkPort_OnlineDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_NetworkPort_OnlineDevice_rtti;

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_OnlineDevice_Construct(
    _Out_ CIM_NetworkPort_OnlineDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_NetworkPort_OnlineDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_OnlineDevice_Clone(
    _In_ const CIM_NetworkPort_OnlineDevice* self,
    _Outptr_ CIM_NetworkPort_OnlineDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_OnlineDevice_Destruct(
    _Inout_ CIM_NetworkPort_OnlineDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_OnlineDevice_Delete(
    _Inout_ CIM_NetworkPort_OnlineDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_OnlineDevice_Post(
    _In_ const CIM_NetworkPort_OnlineDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_OnlineDevice_Set_MIReturn(
    _Inout_ CIM_NetworkPort_OnlineDevice* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_OnlineDevice_Clear_MIReturn(
    _Inout_ CIM_NetworkPort_OnlineDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_OnlineDevice_Set_Online(
    _Inout_ CIM_NetworkPort_OnlineDevice* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Online)->value = x;
    ((MI_BooleanField*)&self->Online)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_OnlineDevice_Clear_Online(
    _Inout_ CIM_NetworkPort_OnlineDevice* self)
{
    memset((void*)&self->Online, 0, sizeof(self->Online));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NetworkPort.QuiesceDevice()
**
**==============================================================================
*/

typedef struct _CIM_NetworkPort_QuiesceDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Quiesce;
}
CIM_NetworkPort_QuiesceDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_NetworkPort_QuiesceDevice_rtti;

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_QuiesceDevice_Construct(
    _Out_ CIM_NetworkPort_QuiesceDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_NetworkPort_QuiesceDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_QuiesceDevice_Clone(
    _In_ const CIM_NetworkPort_QuiesceDevice* self,
    _Outptr_ CIM_NetworkPort_QuiesceDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_QuiesceDevice_Destruct(
    _Inout_ CIM_NetworkPort_QuiesceDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_QuiesceDevice_Delete(
    _Inout_ CIM_NetworkPort_QuiesceDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_QuiesceDevice_Post(
    _In_ const CIM_NetworkPort_QuiesceDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_QuiesceDevice_Set_MIReturn(
    _Inout_ CIM_NetworkPort_QuiesceDevice* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_QuiesceDevice_Clear_MIReturn(
    _Inout_ CIM_NetworkPort_QuiesceDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_QuiesceDevice_Set_Quiesce(
    _Inout_ CIM_NetworkPort_QuiesceDevice* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Quiesce)->value = x;
    ((MI_BooleanField*)&self->Quiesce)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_QuiesceDevice_Clear_Quiesce(
    _Inout_ CIM_NetworkPort_QuiesceDevice* self)
{
    memset((void*)&self->Quiesce, 0, sizeof(self->Quiesce));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NetworkPort.SaveProperties()
**
**==============================================================================
*/

typedef struct _CIM_NetworkPort_SaveProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
CIM_NetworkPort_SaveProperties;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_NetworkPort_SaveProperties_rtti;

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SaveProperties_Construct(
    _Out_ CIM_NetworkPort_SaveProperties* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_NetworkPort_SaveProperties_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SaveProperties_Clone(
    _In_ const CIM_NetworkPort_SaveProperties* self,
    _Outptr_ CIM_NetworkPort_SaveProperties** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SaveProperties_Destruct(
    _Inout_ CIM_NetworkPort_SaveProperties* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SaveProperties_Delete(
    _Inout_ CIM_NetworkPort_SaveProperties* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SaveProperties_Post(
    _In_ const CIM_NetworkPort_SaveProperties* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SaveProperties_Set_MIReturn(
    _Inout_ CIM_NetworkPort_SaveProperties* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_SaveProperties_Clear_MIReturn(
    _Inout_ CIM_NetworkPort_SaveProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NetworkPort.RestoreProperties()
**
**==============================================================================
*/

typedef struct _CIM_NetworkPort_RestoreProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
CIM_NetworkPort_RestoreProperties;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_NetworkPort_RestoreProperties_rtti;

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RestoreProperties_Construct(
    _Out_ CIM_NetworkPort_RestoreProperties* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_NetworkPort_RestoreProperties_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RestoreProperties_Clone(
    _In_ const CIM_NetworkPort_RestoreProperties* self,
    _Outptr_ CIM_NetworkPort_RestoreProperties** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RestoreProperties_Destruct(
    _Inout_ CIM_NetworkPort_RestoreProperties* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RestoreProperties_Delete(
    _Inout_ CIM_NetworkPort_RestoreProperties* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RestoreProperties_Post(
    _In_ const CIM_NetworkPort_RestoreProperties* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RestoreProperties_Set_MIReturn(
    _Inout_ CIM_NetworkPort_RestoreProperties* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPort_RestoreProperties_Clear_MIReturn(
    _Inout_ CIM_NetworkPort_RestoreProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NetworkPort provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_NetworkPort_Self CIM_NetworkPort_Self;

MI_EXTERN_C void MI_CALL CIM_NetworkPort_Load(
    _Outptr_result_maybenull_ CIM_NetworkPort_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_NetworkPort_Unload(
    _In_opt_ CIM_NetworkPort_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_NetworkPort_EnumerateInstances(
    _In_opt_ CIM_NetworkPort_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_NetworkPort_GetInstance(
    _In_opt_ CIM_NetworkPort_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPort* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_NetworkPort_CreateInstance(
    _In_opt_ CIM_NetworkPort_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPort* newInstance);

MI_EXTERN_C void MI_CALL CIM_NetworkPort_ModifyInstance(
    _In_opt_ CIM_NetworkPort_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPort* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_NetworkPort_DeleteInstance(
    _In_opt_ CIM_NetworkPort_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPort* instanceName);

MI_EXTERN_C void MI_CALL CIM_NetworkPort_Invoke_RequestStateChange(
    _In_opt_ CIM_NetworkPort_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_NetworkPort* instanceName,
    _In_opt_ const CIM_NetworkPort_RequestStateChange* in);

MI_EXTERN_C void MI_CALL CIM_NetworkPort_Invoke_SetPowerState(
    _In_opt_ CIM_NetworkPort_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_NetworkPort* instanceName,
    _In_opt_ const CIM_NetworkPort_SetPowerState* in);

MI_EXTERN_C void MI_CALL CIM_NetworkPort_Invoke_Reset(
    _In_opt_ CIM_NetworkPort_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_NetworkPort* instanceName,
    _In_opt_ const CIM_NetworkPort_Reset* in);

MI_EXTERN_C void MI_CALL CIM_NetworkPort_Invoke_EnableDevice(
    _In_opt_ CIM_NetworkPort_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_NetworkPort* instanceName,
    _In_opt_ const CIM_NetworkPort_EnableDevice* in);

MI_EXTERN_C void MI_CALL CIM_NetworkPort_Invoke_OnlineDevice(
    _In_opt_ CIM_NetworkPort_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_NetworkPort* instanceName,
    _In_opt_ const CIM_NetworkPort_OnlineDevice* in);

MI_EXTERN_C void MI_CALL CIM_NetworkPort_Invoke_QuiesceDevice(
    _In_opt_ CIM_NetworkPort_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_NetworkPort* instanceName,
    _In_opt_ const CIM_NetworkPort_QuiesceDevice* in);

MI_EXTERN_C void MI_CALL CIM_NetworkPort_Invoke_SaveProperties(
    _In_opt_ CIM_NetworkPort_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_NetworkPort* instanceName,
    _In_opt_ const CIM_NetworkPort_SaveProperties* in);

MI_EXTERN_C void MI_CALL CIM_NetworkPort_Invoke_RestoreProperties(
    _In_opt_ CIM_NetworkPort_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_NetworkPort* instanceName,
    _In_opt_ const CIM_NetworkPort_RestoreProperties* in);


#endif /* _CIM_NetworkPort_h */
