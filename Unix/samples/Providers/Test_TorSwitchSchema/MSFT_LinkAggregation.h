/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_LinkAggregation_h
#define _MSFT_LinkAggregation_h

#include <MI.h>
#include "CIM_EthernetPort.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** MSFT_LinkAggregation [MSFT_LinkAggregation]
**
** Keys:
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**    DeviceID
**
**==============================================================================
*/

typedef struct _MSFT_LinkAggregation /* extends CIM_EthernetPort */
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
    /* CIM_EthernetPort properties */
    MI_ConstUint32Field MaxDataSize;
    MI_ConstUint16AField Capabilities;
    MI_ConstStringAField CapabilityDescriptions;
    MI_ConstUint16AField EnabledCapabilities;
    MI_ConstStringAField OtherEnabledCapabilities;
    /* MSFT_LinkAggregation properties */
    MI_ConstUint16Field GroupNumber;
    MI_ConstUint16Field LoadBalance;
    MI_ConstBooleanField EnableMulticastHardwareHash;
}
MSFT_LinkAggregation;

typedef struct _MSFT_LinkAggregation_Ref
{
    MSFT_LinkAggregation* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LinkAggregation_Ref;

typedef struct _MSFT_LinkAggregation_ConstRef
{
    MI_CONST MSFT_LinkAggregation* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LinkAggregation_ConstRef;

typedef struct _MSFT_LinkAggregation_Array
{
    struct _MSFT_LinkAggregation** data;
    MI_Uint32 size;
}
MSFT_LinkAggregation_Array;

typedef struct _MSFT_LinkAggregation_ConstArray
{
    struct _MSFT_LinkAggregation MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_LinkAggregation_ConstArray;

typedef struct _MSFT_LinkAggregation_ArrayRef
{
    MSFT_LinkAggregation_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LinkAggregation_ArrayRef;

typedef struct _MSFT_LinkAggregation_ConstArrayRef
{
    MSFT_LinkAggregation_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_LinkAggregation_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_LinkAggregation_rtti;

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Construct(
    _Out_ MSFT_LinkAggregation* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_LinkAggregation_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clone(
    _In_ const MSFT_LinkAggregation* self,
    _Outptr_ MSFT_LinkAggregation** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_LinkAggregation_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_LinkAggregation_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Destruct(_Inout_ MSFT_LinkAggregation* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Delete(_Inout_ MSFT_LinkAggregation* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Post(
    _In_ const MSFT_LinkAggregation* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_InstanceID(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_InstanceID(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_InstanceID(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_Caption(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_Caption(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_Caption(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_Description(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_Description(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_Description(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_ElementName(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_ElementName(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_ElementName(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_InstallDate(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_InstallDate(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_Name(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_Name(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_Name(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_OperationalStatus(
    _Inout_ MSFT_LinkAggregation* self,
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

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_OperationalStatus(
    _Inout_ MSFT_LinkAggregation* self,
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

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_OperationalStatus(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_StatusDescriptions(
    _Inout_ MSFT_LinkAggregation* self,
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

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_StatusDescriptions(
    _Inout_ MSFT_LinkAggregation* self,
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

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_StatusDescriptions(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_Status(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_Status(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_Status(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_HealthState(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_HealthState(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_CommunicationStatus(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_CommunicationStatus(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_DetailedStatus(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_DetailedStatus(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_OperatingStatus(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_OperatingStatus(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_PrimaryStatus(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_PrimaryStatus(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_EnabledState(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_EnabledState(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_OtherEnabledState(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_OtherEnabledState(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_OtherEnabledState(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_RequestedState(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_RequestedState(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_EnabledDefault(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_EnabledDefault(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_TimeOfLastStateChange(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_TimeOfLastStateChange(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_AvailableRequestedStates(
    _Inout_ MSFT_LinkAggregation* self,
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

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_AvailableRequestedStates(
    _Inout_ MSFT_LinkAggregation* self,
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

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_AvailableRequestedStates(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_TransitioningToState(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_TransitioningToState(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_SystemCreationClassName(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_SystemCreationClassName(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_SystemCreationClassName(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_SystemName(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_SystemName(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_SystemName(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_CreationClassName(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_CreationClassName(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_CreationClassName(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_DeviceID(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_DeviceID(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_DeviceID(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_PowerManagementSupported(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->PowerManagementSupported)->value = x;
    ((MI_BooleanField*)&self->PowerManagementSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_PowerManagementSupported(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->PowerManagementSupported, 0, sizeof(self->PowerManagementSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_PowerManagementCapabilities(
    _Inout_ MSFT_LinkAggregation* self,
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

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_PowerManagementCapabilities(
    _Inout_ MSFT_LinkAggregation* self,
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

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_PowerManagementCapabilities(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_Availability(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Availability)->value = x;
    ((MI_Uint16Field*)&self->Availability)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_Availability(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->Availability, 0, sizeof(self->Availability));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_StatusInfo(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->StatusInfo)->value = x;
    ((MI_Uint16Field*)&self->StatusInfo)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_StatusInfo(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->StatusInfo, 0, sizeof(self->StatusInfo));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_LastErrorCode(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->LastErrorCode)->value = x;
    ((MI_Uint32Field*)&self->LastErrorCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_LastErrorCode(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->LastErrorCode, 0, sizeof(self->LastErrorCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_ErrorDescription(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_ErrorDescription(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_ErrorDescription(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        30);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_ErrorCleared(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->ErrorCleared)->value = x;
    ((MI_BooleanField*)&self->ErrorCleared)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_ErrorCleared(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->ErrorCleared, 0, sizeof(self->ErrorCleared));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_OtherIdentifyingInfo(
    _Inout_ MSFT_LinkAggregation* self,
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

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_OtherIdentifyingInfo(
    _Inout_ MSFT_LinkAggregation* self,
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

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_OtherIdentifyingInfo(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        32);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_PowerOnHours(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->PowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->PowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_PowerOnHours(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->PowerOnHours, 0, sizeof(self->PowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_TotalPowerOnHours(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_TotalPowerOnHours(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->TotalPowerOnHours, 0, sizeof(self->TotalPowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_IdentifyingDescriptions(
    _Inout_ MSFT_LinkAggregation* self,
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

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_IdentifyingDescriptions(
    _Inout_ MSFT_LinkAggregation* self,
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

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_IdentifyingDescriptions(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        35);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_AdditionalAvailability(
    _Inout_ MSFT_LinkAggregation* self,
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

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_AdditionalAvailability(
    _Inout_ MSFT_LinkAggregation* self,
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

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_AdditionalAvailability(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        36);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_MaxQuiesceTime(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->value = x;
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_MaxQuiesceTime(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->MaxQuiesceTime, 0, sizeof(self->MaxQuiesceTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_Speed(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->Speed)->value = x;
    ((MI_Uint64Field*)&self->Speed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_Speed(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->Speed, 0, sizeof(self->Speed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_MaxSpeed(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MaxSpeed)->value = x;
    ((MI_Uint64Field*)&self->MaxSpeed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_MaxSpeed(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->MaxSpeed, 0, sizeof(self->MaxSpeed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_RequestedSpeed(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->RequestedSpeed)->value = x;
    ((MI_Uint64Field*)&self->RequestedSpeed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_RequestedSpeed(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->RequestedSpeed, 0, sizeof(self->RequestedSpeed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_UsageRestriction(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->UsageRestriction)->value = x;
    ((MI_Uint16Field*)&self->UsageRestriction)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_UsageRestriction(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->UsageRestriction, 0, sizeof(self->UsageRestriction));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_PortType(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PortType)->value = x;
    ((MI_Uint16Field*)&self->PortType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_PortType(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->PortType, 0, sizeof(self->PortType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_OtherPortType(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        43,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_OtherPortType(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        43,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_OtherPortType(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        43);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_OtherNetworkPortType(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        44,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_OtherNetworkPortType(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        44,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_OtherNetworkPortType(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        44);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_PortNumber(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PortNumber)->value = x;
    ((MI_Uint16Field*)&self->PortNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_PortNumber(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->PortNumber, 0, sizeof(self->PortNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_LinkTechnology(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->LinkTechnology)->value = x;
    ((MI_Uint16Field*)&self->LinkTechnology)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_LinkTechnology(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->LinkTechnology, 0, sizeof(self->LinkTechnology));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_OtherLinkTechnology(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        47,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_OtherLinkTechnology(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        47,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_OtherLinkTechnology(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        47);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_PermanentAddress(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        48,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_PermanentAddress(
    _Inout_ MSFT_LinkAggregation* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        48,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_PermanentAddress(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        48);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_NetworkAddresses(
    _Inout_ MSFT_LinkAggregation* self,
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

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_NetworkAddresses(
    _Inout_ MSFT_LinkAggregation* self,
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

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_NetworkAddresses(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        49);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_FullDuplex(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->FullDuplex)->value = x;
    ((MI_BooleanField*)&self->FullDuplex)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_FullDuplex(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->FullDuplex, 0, sizeof(self->FullDuplex));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_AutoSense(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->AutoSense)->value = x;
    ((MI_BooleanField*)&self->AutoSense)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_AutoSense(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->AutoSense, 0, sizeof(self->AutoSense));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_SupportedMaximumTransmissionUnit(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->SupportedMaximumTransmissionUnit)->value = x;
    ((MI_Uint64Field*)&self->SupportedMaximumTransmissionUnit)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_SupportedMaximumTransmissionUnit(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->SupportedMaximumTransmissionUnit, 0, sizeof(self->SupportedMaximumTransmissionUnit));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_ActiveMaximumTransmissionUnit(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ActiveMaximumTransmissionUnit)->value = x;
    ((MI_Uint64Field*)&self->ActiveMaximumTransmissionUnit)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_ActiveMaximumTransmissionUnit(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->ActiveMaximumTransmissionUnit, 0, sizeof(self->ActiveMaximumTransmissionUnit));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_MaxDataSize(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MaxDataSize)->value = x;
    ((MI_Uint32Field*)&self->MaxDataSize)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_MaxDataSize(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->MaxDataSize, 0, sizeof(self->MaxDataSize));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_Capabilities(
    _Inout_ MSFT_LinkAggregation* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        55,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_Capabilities(
    _Inout_ MSFT_LinkAggregation* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        55,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_Capabilities(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        55);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_CapabilityDescriptions(
    _Inout_ MSFT_LinkAggregation* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        56,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_CapabilityDescriptions(
    _Inout_ MSFT_LinkAggregation* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        56,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_CapabilityDescriptions(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        56);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_EnabledCapabilities(
    _Inout_ MSFT_LinkAggregation* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        57,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_EnabledCapabilities(
    _Inout_ MSFT_LinkAggregation* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        57,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_EnabledCapabilities(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        57);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_OtherEnabledCapabilities(
    _Inout_ MSFT_LinkAggregation* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        58,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPtr_OtherEnabledCapabilities(
    _Inout_ MSFT_LinkAggregation* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        58,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_OtherEnabledCapabilities(
    _Inout_ MSFT_LinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        58);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_GroupNumber(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->GroupNumber)->value = x;
    ((MI_Uint16Field*)&self->GroupNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_GroupNumber(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->GroupNumber, 0, sizeof(self->GroupNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_LoadBalance(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->LoadBalance)->value = x;
    ((MI_Uint16Field*)&self->LoadBalance)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_LoadBalance(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->LoadBalance, 0, sizeof(self->LoadBalance));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Set_EnableMulticastHardwareHash(
    _Inout_ MSFT_LinkAggregation* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->EnableMulticastHardwareHash)->value = x;
    ((MI_BooleanField*)&self->EnableMulticastHardwareHash)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Clear_EnableMulticastHardwareHash(
    _Inout_ MSFT_LinkAggregation* self)
{
    memset((void*)&self->EnableMulticastHardwareHash, 0, sizeof(self->EnableMulticastHardwareHash));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_LinkAggregation.RequestStateChange()
**
**==============================================================================
*/

typedef struct _MSFT_LinkAggregation_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
MSFT_LinkAggregation_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_LinkAggregation_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RequestStateChange_Construct(
    _Out_ MSFT_LinkAggregation_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_LinkAggregation_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RequestStateChange_Clone(
    _In_ const MSFT_LinkAggregation_RequestStateChange* self,
    _Outptr_ MSFT_LinkAggregation_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RequestStateChange_Destruct(
    _Inout_ MSFT_LinkAggregation_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RequestStateChange_Delete(
    _Inout_ MSFT_LinkAggregation_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RequestStateChange_Post(
    _In_ const MSFT_LinkAggregation_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RequestStateChange_Set_MIReturn(
    _Inout_ MSFT_LinkAggregation_RequestStateChange* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RequestStateChange_Clear_MIReturn(
    _Inout_ MSFT_LinkAggregation_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RequestStateChange_Set_RequestedState(
    _Inout_ MSFT_LinkAggregation_RequestStateChange* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RequestStateChange_Clear_RequestedState(
    _Inout_ MSFT_LinkAggregation_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RequestStateChange_Set_Job(
    _Inout_ MSFT_LinkAggregation_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RequestStateChange_SetPtr_Job(
    _Inout_ MSFT_LinkAggregation_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RequestStateChange_Clear_Job(
    _Inout_ MSFT_LinkAggregation_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RequestStateChange_Set_TimeoutPeriod(
    _Inout_ MSFT_LinkAggregation_RequestStateChange* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RequestStateChange_Clear_TimeoutPeriod(
    _Inout_ MSFT_LinkAggregation_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_LinkAggregation.SetPowerState()
**
**==============================================================================
*/

typedef struct _MSFT_LinkAggregation_SetPowerState
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field PowerState;
    /*IN*/ MI_ConstDatetimeField Time;
}
MSFT_LinkAggregation_SetPowerState;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_LinkAggregation_SetPowerState_rtti;

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPowerState_Construct(
    _Out_ MSFT_LinkAggregation_SetPowerState* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_LinkAggregation_SetPowerState_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPowerState_Clone(
    _In_ const MSFT_LinkAggregation_SetPowerState* self,
    _Outptr_ MSFT_LinkAggregation_SetPowerState** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPowerState_Destruct(
    _Inout_ MSFT_LinkAggregation_SetPowerState* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPowerState_Delete(
    _Inout_ MSFT_LinkAggregation_SetPowerState* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPowerState_Post(
    _In_ const MSFT_LinkAggregation_SetPowerState* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPowerState_Set_MIReturn(
    _Inout_ MSFT_LinkAggregation_SetPowerState* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPowerState_Clear_MIReturn(
    _Inout_ MSFT_LinkAggregation_SetPowerState* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPowerState_Set_PowerState(
    _Inout_ MSFT_LinkAggregation_SetPowerState* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PowerState)->value = x;
    ((MI_Uint16Field*)&self->PowerState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPowerState_Clear_PowerState(
    _Inout_ MSFT_LinkAggregation_SetPowerState* self)
{
    memset((void*)&self->PowerState, 0, sizeof(self->PowerState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPowerState_Set_Time(
    _Inout_ MSFT_LinkAggregation_SetPowerState* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->Time)->value = x;
    ((MI_DatetimeField*)&self->Time)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SetPowerState_Clear_Time(
    _Inout_ MSFT_LinkAggregation_SetPowerState* self)
{
    memset((void*)&self->Time, 0, sizeof(self->Time));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_LinkAggregation.Reset()
**
**==============================================================================
*/

typedef struct _MSFT_LinkAggregation_Reset
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MSFT_LinkAggregation_Reset;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_LinkAggregation_Reset_rtti;

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Reset_Construct(
    _Out_ MSFT_LinkAggregation_Reset* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_LinkAggregation_Reset_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Reset_Clone(
    _In_ const MSFT_LinkAggregation_Reset* self,
    _Outptr_ MSFT_LinkAggregation_Reset** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Reset_Destruct(
    _Inout_ MSFT_LinkAggregation_Reset* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Reset_Delete(
    _Inout_ MSFT_LinkAggregation_Reset* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Reset_Post(
    _In_ const MSFT_LinkAggregation_Reset* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Reset_Set_MIReturn(
    _Inout_ MSFT_LinkAggregation_Reset* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_Reset_Clear_MIReturn(
    _Inout_ MSFT_LinkAggregation_Reset* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_LinkAggregation.EnableDevice()
**
**==============================================================================
*/

typedef struct _MSFT_LinkAggregation_EnableDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Enabled;
}
MSFT_LinkAggregation_EnableDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_LinkAggregation_EnableDevice_rtti;

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_EnableDevice_Construct(
    _Out_ MSFT_LinkAggregation_EnableDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_LinkAggregation_EnableDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_EnableDevice_Clone(
    _In_ const MSFT_LinkAggregation_EnableDevice* self,
    _Outptr_ MSFT_LinkAggregation_EnableDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_EnableDevice_Destruct(
    _Inout_ MSFT_LinkAggregation_EnableDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_EnableDevice_Delete(
    _Inout_ MSFT_LinkAggregation_EnableDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_EnableDevice_Post(
    _In_ const MSFT_LinkAggregation_EnableDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_EnableDevice_Set_MIReturn(
    _Inout_ MSFT_LinkAggregation_EnableDevice* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_EnableDevice_Clear_MIReturn(
    _Inout_ MSFT_LinkAggregation_EnableDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_EnableDevice_Set_Enabled(
    _Inout_ MSFT_LinkAggregation_EnableDevice* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Enabled)->value = x;
    ((MI_BooleanField*)&self->Enabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_EnableDevice_Clear_Enabled(
    _Inout_ MSFT_LinkAggregation_EnableDevice* self)
{
    memset((void*)&self->Enabled, 0, sizeof(self->Enabled));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_LinkAggregation.OnlineDevice()
**
**==============================================================================
*/

typedef struct _MSFT_LinkAggregation_OnlineDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Online;
}
MSFT_LinkAggregation_OnlineDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_LinkAggregation_OnlineDevice_rtti;

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_OnlineDevice_Construct(
    _Out_ MSFT_LinkAggregation_OnlineDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_LinkAggregation_OnlineDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_OnlineDevice_Clone(
    _In_ const MSFT_LinkAggregation_OnlineDevice* self,
    _Outptr_ MSFT_LinkAggregation_OnlineDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_OnlineDevice_Destruct(
    _Inout_ MSFT_LinkAggregation_OnlineDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_OnlineDevice_Delete(
    _Inout_ MSFT_LinkAggregation_OnlineDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_OnlineDevice_Post(
    _In_ const MSFT_LinkAggregation_OnlineDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_OnlineDevice_Set_MIReturn(
    _Inout_ MSFT_LinkAggregation_OnlineDevice* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_OnlineDevice_Clear_MIReturn(
    _Inout_ MSFT_LinkAggregation_OnlineDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_OnlineDevice_Set_Online(
    _Inout_ MSFT_LinkAggregation_OnlineDevice* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Online)->value = x;
    ((MI_BooleanField*)&self->Online)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_OnlineDevice_Clear_Online(
    _Inout_ MSFT_LinkAggregation_OnlineDevice* self)
{
    memset((void*)&self->Online, 0, sizeof(self->Online));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_LinkAggregation.QuiesceDevice()
**
**==============================================================================
*/

typedef struct _MSFT_LinkAggregation_QuiesceDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Quiesce;
}
MSFT_LinkAggregation_QuiesceDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_LinkAggregation_QuiesceDevice_rtti;

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_QuiesceDevice_Construct(
    _Out_ MSFT_LinkAggregation_QuiesceDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_LinkAggregation_QuiesceDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_QuiesceDevice_Clone(
    _In_ const MSFT_LinkAggregation_QuiesceDevice* self,
    _Outptr_ MSFT_LinkAggregation_QuiesceDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_QuiesceDevice_Destruct(
    _Inout_ MSFT_LinkAggregation_QuiesceDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_QuiesceDevice_Delete(
    _Inout_ MSFT_LinkAggregation_QuiesceDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_QuiesceDevice_Post(
    _In_ const MSFT_LinkAggregation_QuiesceDevice* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_QuiesceDevice_Set_MIReturn(
    _Inout_ MSFT_LinkAggregation_QuiesceDevice* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_QuiesceDevice_Clear_MIReturn(
    _Inout_ MSFT_LinkAggregation_QuiesceDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_QuiesceDevice_Set_Quiesce(
    _Inout_ MSFT_LinkAggregation_QuiesceDevice* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Quiesce)->value = x;
    ((MI_BooleanField*)&self->Quiesce)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_QuiesceDevice_Clear_Quiesce(
    _Inout_ MSFT_LinkAggregation_QuiesceDevice* self)
{
    memset((void*)&self->Quiesce, 0, sizeof(self->Quiesce));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_LinkAggregation.SaveProperties()
**
**==============================================================================
*/

typedef struct _MSFT_LinkAggregation_SaveProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MSFT_LinkAggregation_SaveProperties;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_LinkAggregation_SaveProperties_rtti;

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SaveProperties_Construct(
    _Out_ MSFT_LinkAggregation_SaveProperties* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_LinkAggregation_SaveProperties_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SaveProperties_Clone(
    _In_ const MSFT_LinkAggregation_SaveProperties* self,
    _Outptr_ MSFT_LinkAggregation_SaveProperties** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SaveProperties_Destruct(
    _Inout_ MSFT_LinkAggregation_SaveProperties* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SaveProperties_Delete(
    _Inout_ MSFT_LinkAggregation_SaveProperties* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SaveProperties_Post(
    _In_ const MSFT_LinkAggregation_SaveProperties* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SaveProperties_Set_MIReturn(
    _Inout_ MSFT_LinkAggregation_SaveProperties* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_SaveProperties_Clear_MIReturn(
    _Inout_ MSFT_LinkAggregation_SaveProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_LinkAggregation.RestoreProperties()
**
**==============================================================================
*/

typedef struct _MSFT_LinkAggregation_RestoreProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MSFT_LinkAggregation_RestoreProperties;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_LinkAggregation_RestoreProperties_rtti;

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RestoreProperties_Construct(
    _Out_ MSFT_LinkAggregation_RestoreProperties* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_LinkAggregation_RestoreProperties_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RestoreProperties_Clone(
    _In_ const MSFT_LinkAggregation_RestoreProperties* self,
    _Outptr_ MSFT_LinkAggregation_RestoreProperties** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RestoreProperties_Destruct(
    _Inout_ MSFT_LinkAggregation_RestoreProperties* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RestoreProperties_Delete(
    _Inout_ MSFT_LinkAggregation_RestoreProperties* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RestoreProperties_Post(
    _In_ const MSFT_LinkAggregation_RestoreProperties* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RestoreProperties_Set_MIReturn(
    _Inout_ MSFT_LinkAggregation_RestoreProperties* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_LinkAggregation_RestoreProperties_Clear_MIReturn(
    _Inout_ MSFT_LinkAggregation_RestoreProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_LinkAggregation provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_LinkAggregation_Self MSFT_LinkAggregation_Self;

MI_EXTERN_C void MI_CALL MSFT_LinkAggregation_Load(
    _Outptr_result_maybenull_ MSFT_LinkAggregation_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregation_Unload(
    _In_opt_ MSFT_LinkAggregation_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregation_EnumerateInstances(
    _In_opt_ MSFT_LinkAggregation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregation_GetInstance(
    _In_opt_ MSFT_LinkAggregation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_LinkAggregation* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregation_CreateInstance(
    _In_opt_ MSFT_LinkAggregation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_LinkAggregation* newInstance);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregation_ModifyInstance(
    _In_opt_ MSFT_LinkAggregation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_LinkAggregation* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregation_DeleteInstance(
    _In_opt_ MSFT_LinkAggregation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_LinkAggregation* instanceName);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregation_Invoke_RequestStateChange(
    _In_opt_ MSFT_LinkAggregation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_LinkAggregation* instanceName,
    _In_opt_ const MSFT_LinkAggregation_RequestStateChange* in);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregation_Invoke_SetPowerState(
    _In_opt_ MSFT_LinkAggregation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_LinkAggregation* instanceName,
    _In_opt_ const MSFT_LinkAggregation_SetPowerState* in);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregation_Invoke_Reset(
    _In_opt_ MSFT_LinkAggregation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_LinkAggregation* instanceName,
    _In_opt_ const MSFT_LinkAggregation_Reset* in);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregation_Invoke_EnableDevice(
    _In_opt_ MSFT_LinkAggregation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_LinkAggregation* instanceName,
    _In_opt_ const MSFT_LinkAggregation_EnableDevice* in);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregation_Invoke_OnlineDevice(
    _In_opt_ MSFT_LinkAggregation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_LinkAggregation* instanceName,
    _In_opt_ const MSFT_LinkAggregation_OnlineDevice* in);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregation_Invoke_QuiesceDevice(
    _In_opt_ MSFT_LinkAggregation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_LinkAggregation* instanceName,
    _In_opt_ const MSFT_LinkAggregation_QuiesceDevice* in);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregation_Invoke_SaveProperties(
    _In_opt_ MSFT_LinkAggregation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_LinkAggregation* instanceName,
    _In_opt_ const MSFT_LinkAggregation_SaveProperties* in);

MI_EXTERN_C void MI_CALL MSFT_LinkAggregation_Invoke_RestoreProperties(
    _In_opt_ MSFT_LinkAggregation_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_LinkAggregation* instanceName,
    _In_opt_ const MSFT_LinkAggregation_RestoreProperties* in);


#endif /* _MSFT_LinkAggregation_h */
