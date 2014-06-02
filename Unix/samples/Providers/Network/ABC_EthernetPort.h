/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_EthernetPort_h
#define _ABC_EthernetPort_h

#include <MI.h>
#include "CIM_EthernetPort.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** ABC_EthernetPort [ABC_EthernetPort]
**
** Keys:
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**    DeviceID
**
**==============================================================================
*/

typedef struct _ABC_EthernetPort /* extends CIM_EthernetPort */
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
    /* ABC_EthernetPort properties */
}
ABC_EthernetPort;

typedef struct _ABC_EthernetPort_Ref
{
    ABC_EthernetPort* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_EthernetPort_Ref;

typedef struct _ABC_EthernetPort_ConstRef
{
    MI_CONST ABC_EthernetPort* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_EthernetPort_ConstRef;

typedef struct _ABC_EthernetPort_Array
{
    struct _ABC_EthernetPort** data;
    MI_Uint32 size;
}
ABC_EthernetPort_Array;

typedef struct _ABC_EthernetPort_ConstArray
{
    struct _ABC_EthernetPort MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_EthernetPort_ConstArray;

typedef struct _ABC_EthernetPort_ArrayRef
{
    ABC_EthernetPort_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_EthernetPort_ArrayRef;

typedef struct _ABC_EthernetPort_ConstArrayRef
{
    ABC_EthernetPort_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_EthernetPort_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_EthernetPort_rtti;

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Construct(
    ABC_EthernetPort* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_EthernetPort_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clone(
    const ABC_EthernetPort* self,
    ABC_EthernetPort** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_EthernetPort_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_EthernetPort_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Destruct(ABC_EthernetPort* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Delete(ABC_EthernetPort* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Post(
    const ABC_EthernetPort* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_InstanceID(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_InstanceID(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_InstanceID(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_Caption(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_Caption(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_Caption(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_Description(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_Description(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_Description(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_ElementName(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_ElementName(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_ElementName(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_InstallDate(
    ABC_EthernetPort* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_InstallDate(
    ABC_EthernetPort* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_Name(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_Name(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_Name(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_OperationalStatus(
    ABC_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_OperationalStatus(
    ABC_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_OperationalStatus(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_StatusDescriptions(
    ABC_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_StatusDescriptions(
    ABC_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_StatusDescriptions(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_Status(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_Status(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_Status(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_HealthState(
    ABC_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_HealthState(
    ABC_EthernetPort* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_CommunicationStatus(
    ABC_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_CommunicationStatus(
    ABC_EthernetPort* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_DetailedStatus(
    ABC_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_DetailedStatus(
    ABC_EthernetPort* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_OperatingStatus(
    ABC_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_OperatingStatus(
    ABC_EthernetPort* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_PrimaryStatus(
    ABC_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_PrimaryStatus(
    ABC_EthernetPort* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_EnabledState(
    ABC_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_EnabledState(
    ABC_EthernetPort* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_OtherEnabledState(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_OtherEnabledState(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_OtherEnabledState(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_RequestedState(
    ABC_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_RequestedState(
    ABC_EthernetPort* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_EnabledDefault(
    ABC_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_EnabledDefault(
    ABC_EthernetPort* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_TimeOfLastStateChange(
    ABC_EthernetPort* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_TimeOfLastStateChange(
    ABC_EthernetPort* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_AvailableRequestedStates(
    ABC_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_AvailableRequestedStates(
    ABC_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_AvailableRequestedStates(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_TransitioningToState(
    ABC_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_TransitioningToState(
    ABC_EthernetPort* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_SystemCreationClassName(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_SystemCreationClassName(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_SystemCreationClassName(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_SystemName(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_SystemName(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_SystemName(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_CreationClassName(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_CreationClassName(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_CreationClassName(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_DeviceID(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_DeviceID(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_DeviceID(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_PowerManagementSupported(
    ABC_EthernetPort* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->PowerManagementSupported)->value = x;
    ((MI_BooleanField*)&self->PowerManagementSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_PowerManagementSupported(
    ABC_EthernetPort* self)
{
    memset((void*)&self->PowerManagementSupported, 0, sizeof(self->PowerManagementSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_PowerManagementCapabilities(
    ABC_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_PowerManagementCapabilities(
    ABC_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_PowerManagementCapabilities(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_Availability(
    ABC_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Availability)->value = x;
    ((MI_Uint16Field*)&self->Availability)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_Availability(
    ABC_EthernetPort* self)
{
    memset((void*)&self->Availability, 0, sizeof(self->Availability));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_StatusInfo(
    ABC_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->StatusInfo)->value = x;
    ((MI_Uint16Field*)&self->StatusInfo)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_StatusInfo(
    ABC_EthernetPort* self)
{
    memset((void*)&self->StatusInfo, 0, sizeof(self->StatusInfo));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_LastErrorCode(
    ABC_EthernetPort* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->LastErrorCode)->value = x;
    ((MI_Uint32Field*)&self->LastErrorCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_LastErrorCode(
    ABC_EthernetPort* self)
{
    memset((void*)&self->LastErrorCode, 0, sizeof(self->LastErrorCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_ErrorDescription(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_ErrorDescription(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_ErrorDescription(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        30);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_ErrorCleared(
    ABC_EthernetPort* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->ErrorCleared)->value = x;
    ((MI_BooleanField*)&self->ErrorCleared)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_ErrorCleared(
    ABC_EthernetPort* self)
{
    memset((void*)&self->ErrorCleared, 0, sizeof(self->ErrorCleared));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_OtherIdentifyingInfo(
    ABC_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_OtherIdentifyingInfo(
    ABC_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_OtherIdentifyingInfo(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        32);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_PowerOnHours(
    ABC_EthernetPort* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->PowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->PowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_PowerOnHours(
    ABC_EthernetPort* self)
{
    memset((void*)&self->PowerOnHours, 0, sizeof(self->PowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_TotalPowerOnHours(
    ABC_EthernetPort* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_TotalPowerOnHours(
    ABC_EthernetPort* self)
{
    memset((void*)&self->TotalPowerOnHours, 0, sizeof(self->TotalPowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_IdentifyingDescriptions(
    ABC_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_IdentifyingDescriptions(
    ABC_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_IdentifyingDescriptions(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        35);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_AdditionalAvailability(
    ABC_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_AdditionalAvailability(
    ABC_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_AdditionalAvailability(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        36);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_MaxQuiesceTime(
    ABC_EthernetPort* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->value = x;
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_MaxQuiesceTime(
    ABC_EthernetPort* self)
{
    memset((void*)&self->MaxQuiesceTime, 0, sizeof(self->MaxQuiesceTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_Speed(
    ABC_EthernetPort* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->Speed)->value = x;
    ((MI_Uint64Field*)&self->Speed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_Speed(
    ABC_EthernetPort* self)
{
    memset((void*)&self->Speed, 0, sizeof(self->Speed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_MaxSpeed(
    ABC_EthernetPort* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MaxSpeed)->value = x;
    ((MI_Uint64Field*)&self->MaxSpeed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_MaxSpeed(
    ABC_EthernetPort* self)
{
    memset((void*)&self->MaxSpeed, 0, sizeof(self->MaxSpeed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_RequestedSpeed(
    ABC_EthernetPort* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->RequestedSpeed)->value = x;
    ((MI_Uint64Field*)&self->RequestedSpeed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_RequestedSpeed(
    ABC_EthernetPort* self)
{
    memset((void*)&self->RequestedSpeed, 0, sizeof(self->RequestedSpeed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_UsageRestriction(
    ABC_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->UsageRestriction)->value = x;
    ((MI_Uint16Field*)&self->UsageRestriction)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_UsageRestriction(
    ABC_EthernetPort* self)
{
    memset((void*)&self->UsageRestriction, 0, sizeof(self->UsageRestriction));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_PortType(
    ABC_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PortType)->value = x;
    ((MI_Uint16Field*)&self->PortType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_PortType(
    ABC_EthernetPort* self)
{
    memset((void*)&self->PortType, 0, sizeof(self->PortType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_OtherPortType(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        43,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_OtherPortType(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        43,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_OtherPortType(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        43);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_OtherNetworkPortType(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        44,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_OtherNetworkPortType(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        44,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_OtherNetworkPortType(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        44);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_PortNumber(
    ABC_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PortNumber)->value = x;
    ((MI_Uint16Field*)&self->PortNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_PortNumber(
    ABC_EthernetPort* self)
{
    memset((void*)&self->PortNumber, 0, sizeof(self->PortNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_LinkTechnology(
    ABC_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->LinkTechnology)->value = x;
    ((MI_Uint16Field*)&self->LinkTechnology)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_LinkTechnology(
    ABC_EthernetPort* self)
{
    memset((void*)&self->LinkTechnology, 0, sizeof(self->LinkTechnology));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_OtherLinkTechnology(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        47,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_OtherLinkTechnology(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        47,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_OtherLinkTechnology(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        47);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_PermanentAddress(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        48,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_PermanentAddress(
    ABC_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        48,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_PermanentAddress(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        48);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_NetworkAddresses(
    ABC_EthernetPort* self,
    const MI_Char** data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_NetworkAddresses(
    ABC_EthernetPort* self,
    const MI_Char** data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_NetworkAddresses(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        49);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_FullDuplex(
    ABC_EthernetPort* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->FullDuplex)->value = x;
    ((MI_BooleanField*)&self->FullDuplex)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_FullDuplex(
    ABC_EthernetPort* self)
{
    memset((void*)&self->FullDuplex, 0, sizeof(self->FullDuplex));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_AutoSense(
    ABC_EthernetPort* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->AutoSense)->value = x;
    ((MI_BooleanField*)&self->AutoSense)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_AutoSense(
    ABC_EthernetPort* self)
{
    memset((void*)&self->AutoSense, 0, sizeof(self->AutoSense));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_SupportedMaximumTransmissionUnit(
    ABC_EthernetPort* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->SupportedMaximumTransmissionUnit)->value = x;
    ((MI_Uint64Field*)&self->SupportedMaximumTransmissionUnit)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_SupportedMaximumTransmissionUnit(
    ABC_EthernetPort* self)
{
    memset((void*)&self->SupportedMaximumTransmissionUnit, 0, sizeof(self->SupportedMaximumTransmissionUnit));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_ActiveMaximumTransmissionUnit(
    ABC_EthernetPort* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ActiveMaximumTransmissionUnit)->value = x;
    ((MI_Uint64Field*)&self->ActiveMaximumTransmissionUnit)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_ActiveMaximumTransmissionUnit(
    ABC_EthernetPort* self)
{
    memset((void*)&self->ActiveMaximumTransmissionUnit, 0, sizeof(self->ActiveMaximumTransmissionUnit));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_MaxDataSize(
    ABC_EthernetPort* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MaxDataSize)->value = x;
    ((MI_Uint32Field*)&self->MaxDataSize)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_MaxDataSize(
    ABC_EthernetPort* self)
{
    memset((void*)&self->MaxDataSize, 0, sizeof(self->MaxDataSize));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_Capabilities(
    ABC_EthernetPort* self,
    const MI_Uint16* data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_Capabilities(
    ABC_EthernetPort* self,
    const MI_Uint16* data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_Capabilities(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        55);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_CapabilityDescriptions(
    ABC_EthernetPort* self,
    const MI_Char** data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_CapabilityDescriptions(
    ABC_EthernetPort* self,
    const MI_Char** data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_CapabilityDescriptions(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        56);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_EnabledCapabilities(
    ABC_EthernetPort* self,
    const MI_Uint16* data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_EnabledCapabilities(
    ABC_EthernetPort* self,
    const MI_Uint16* data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_EnabledCapabilities(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        57);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Set_OtherEnabledCapabilities(
    ABC_EthernetPort* self,
    const MI_Char** data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPtr_OtherEnabledCapabilities(
    ABC_EthernetPort* self,
    const MI_Char** data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Clear_OtherEnabledCapabilities(
    ABC_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        58);
}

/*
**==============================================================================
**
** ABC_EthernetPort.RequestStateChange()
**
**==============================================================================
*/

typedef struct _ABC_EthernetPort_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
ABC_EthernetPort_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_EthernetPort_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RequestStateChange_Construct(
    ABC_EthernetPort_RequestStateChange* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_EthernetPort_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RequestStateChange_Clone(
    const ABC_EthernetPort_RequestStateChange* self,
    ABC_EthernetPort_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RequestStateChange_Destruct(
    ABC_EthernetPort_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RequestStateChange_Delete(
    ABC_EthernetPort_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RequestStateChange_Post(
    const ABC_EthernetPort_RequestStateChange* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RequestStateChange_Set_MIReturn(
    ABC_EthernetPort_RequestStateChange* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RequestStateChange_Clear_MIReturn(
    ABC_EthernetPort_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RequestStateChange_Set_RequestedState(
    ABC_EthernetPort_RequestStateChange* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RequestStateChange_Clear_RequestedState(
    ABC_EthernetPort_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RequestStateChange_Set_Job(
    ABC_EthernetPort_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RequestStateChange_SetPtr_Job(
    ABC_EthernetPort_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RequestStateChange_Clear_Job(
    ABC_EthernetPort_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RequestStateChange_Set_TimeoutPeriod(
    ABC_EthernetPort_RequestStateChange* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RequestStateChange_Clear_TimeoutPeriod(
    ABC_EthernetPort_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_EthernetPort.SetPowerState()
**
**==============================================================================
*/

typedef struct _ABC_EthernetPort_SetPowerState
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field PowerState;
    /*IN*/ MI_ConstDatetimeField Time;
}
ABC_EthernetPort_SetPowerState;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_EthernetPort_SetPowerState_rtti;

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPowerState_Construct(
    ABC_EthernetPort_SetPowerState* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_EthernetPort_SetPowerState_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPowerState_Clone(
    const ABC_EthernetPort_SetPowerState* self,
    ABC_EthernetPort_SetPowerState** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPowerState_Destruct(
    ABC_EthernetPort_SetPowerState* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPowerState_Delete(
    ABC_EthernetPort_SetPowerState* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPowerState_Post(
    const ABC_EthernetPort_SetPowerState* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPowerState_Set_MIReturn(
    ABC_EthernetPort_SetPowerState* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPowerState_Clear_MIReturn(
    ABC_EthernetPort_SetPowerState* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPowerState_Set_PowerState(
    ABC_EthernetPort_SetPowerState* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PowerState)->value = x;
    ((MI_Uint16Field*)&self->PowerState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPowerState_Clear_PowerState(
    ABC_EthernetPort_SetPowerState* self)
{
    memset((void*)&self->PowerState, 0, sizeof(self->PowerState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPowerState_Set_Time(
    ABC_EthernetPort_SetPowerState* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->Time)->value = x;
    ((MI_DatetimeField*)&self->Time)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SetPowerState_Clear_Time(
    ABC_EthernetPort_SetPowerState* self)
{
    memset((void*)&self->Time, 0, sizeof(self->Time));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_EthernetPort.Reset()
**
**==============================================================================
*/

typedef struct _ABC_EthernetPort_Reset
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
ABC_EthernetPort_Reset;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_EthernetPort_Reset_rtti;

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Reset_Construct(
    ABC_EthernetPort_Reset* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_EthernetPort_Reset_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Reset_Clone(
    const ABC_EthernetPort_Reset* self,
    ABC_EthernetPort_Reset** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Reset_Destruct(
    ABC_EthernetPort_Reset* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Reset_Delete(
    ABC_EthernetPort_Reset* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Reset_Post(
    const ABC_EthernetPort_Reset* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Reset_Set_MIReturn(
    ABC_EthernetPort_Reset* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_Reset_Clear_MIReturn(
    ABC_EthernetPort_Reset* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_EthernetPort.EnableDevice()
**
**==============================================================================
*/

typedef struct _ABC_EthernetPort_EnableDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Enabled;
}
ABC_EthernetPort_EnableDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_EthernetPort_EnableDevice_rtti;

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_EnableDevice_Construct(
    ABC_EthernetPort_EnableDevice* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_EthernetPort_EnableDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_EnableDevice_Clone(
    const ABC_EthernetPort_EnableDevice* self,
    ABC_EthernetPort_EnableDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_EnableDevice_Destruct(
    ABC_EthernetPort_EnableDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_EnableDevice_Delete(
    ABC_EthernetPort_EnableDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_EnableDevice_Post(
    const ABC_EthernetPort_EnableDevice* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_EnableDevice_Set_MIReturn(
    ABC_EthernetPort_EnableDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_EnableDevice_Clear_MIReturn(
    ABC_EthernetPort_EnableDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_EnableDevice_Set_Enabled(
    ABC_EthernetPort_EnableDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Enabled)->value = x;
    ((MI_BooleanField*)&self->Enabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_EnableDevice_Clear_Enabled(
    ABC_EthernetPort_EnableDevice* self)
{
    memset((void*)&self->Enabled, 0, sizeof(self->Enabled));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_EthernetPort.OnlineDevice()
**
**==============================================================================
*/

typedef struct _ABC_EthernetPort_OnlineDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Online;
}
ABC_EthernetPort_OnlineDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_EthernetPort_OnlineDevice_rtti;

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_OnlineDevice_Construct(
    ABC_EthernetPort_OnlineDevice* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_EthernetPort_OnlineDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_OnlineDevice_Clone(
    const ABC_EthernetPort_OnlineDevice* self,
    ABC_EthernetPort_OnlineDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_OnlineDevice_Destruct(
    ABC_EthernetPort_OnlineDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_OnlineDevice_Delete(
    ABC_EthernetPort_OnlineDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_OnlineDevice_Post(
    const ABC_EthernetPort_OnlineDevice* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_OnlineDevice_Set_MIReturn(
    ABC_EthernetPort_OnlineDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_OnlineDevice_Clear_MIReturn(
    ABC_EthernetPort_OnlineDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_OnlineDevice_Set_Online(
    ABC_EthernetPort_OnlineDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Online)->value = x;
    ((MI_BooleanField*)&self->Online)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_OnlineDevice_Clear_Online(
    ABC_EthernetPort_OnlineDevice* self)
{
    memset((void*)&self->Online, 0, sizeof(self->Online));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_EthernetPort.QuiesceDevice()
**
**==============================================================================
*/

typedef struct _ABC_EthernetPort_QuiesceDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Quiesce;
}
ABC_EthernetPort_QuiesceDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_EthernetPort_QuiesceDevice_rtti;

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_QuiesceDevice_Construct(
    ABC_EthernetPort_QuiesceDevice* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_EthernetPort_QuiesceDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_QuiesceDevice_Clone(
    const ABC_EthernetPort_QuiesceDevice* self,
    ABC_EthernetPort_QuiesceDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_QuiesceDevice_Destruct(
    ABC_EthernetPort_QuiesceDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_QuiesceDevice_Delete(
    ABC_EthernetPort_QuiesceDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_QuiesceDevice_Post(
    const ABC_EthernetPort_QuiesceDevice* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_QuiesceDevice_Set_MIReturn(
    ABC_EthernetPort_QuiesceDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_QuiesceDevice_Clear_MIReturn(
    ABC_EthernetPort_QuiesceDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_QuiesceDevice_Set_Quiesce(
    ABC_EthernetPort_QuiesceDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Quiesce)->value = x;
    ((MI_BooleanField*)&self->Quiesce)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_QuiesceDevice_Clear_Quiesce(
    ABC_EthernetPort_QuiesceDevice* self)
{
    memset((void*)&self->Quiesce, 0, sizeof(self->Quiesce));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_EthernetPort.SaveProperties()
**
**==============================================================================
*/

typedef struct _ABC_EthernetPort_SaveProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
ABC_EthernetPort_SaveProperties;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_EthernetPort_SaveProperties_rtti;

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SaveProperties_Construct(
    ABC_EthernetPort_SaveProperties* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_EthernetPort_SaveProperties_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SaveProperties_Clone(
    const ABC_EthernetPort_SaveProperties* self,
    ABC_EthernetPort_SaveProperties** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SaveProperties_Destruct(
    ABC_EthernetPort_SaveProperties* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SaveProperties_Delete(
    ABC_EthernetPort_SaveProperties* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SaveProperties_Post(
    const ABC_EthernetPort_SaveProperties* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SaveProperties_Set_MIReturn(
    ABC_EthernetPort_SaveProperties* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_SaveProperties_Clear_MIReturn(
    ABC_EthernetPort_SaveProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_EthernetPort.RestoreProperties()
**
**==============================================================================
*/

typedef struct _ABC_EthernetPort_RestoreProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
ABC_EthernetPort_RestoreProperties;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_EthernetPort_RestoreProperties_rtti;

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RestoreProperties_Construct(
    ABC_EthernetPort_RestoreProperties* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_EthernetPort_RestoreProperties_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RestoreProperties_Clone(
    const ABC_EthernetPort_RestoreProperties* self,
    ABC_EthernetPort_RestoreProperties** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RestoreProperties_Destruct(
    ABC_EthernetPort_RestoreProperties* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RestoreProperties_Delete(
    ABC_EthernetPort_RestoreProperties* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RestoreProperties_Post(
    const ABC_EthernetPort_RestoreProperties* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RestoreProperties_Set_MIReturn(
    ABC_EthernetPort_RestoreProperties* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_EthernetPort_RestoreProperties_Clear_MIReturn(
    ABC_EthernetPort_RestoreProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_EthernetPort provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_EthernetPort_Self ABC_EthernetPort_Self;

MI_EXTERN_C void MI_CALL ABC_EthernetPort_Load(
    ABC_EthernetPort_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_EthernetPort_Unload(
    ABC_EthernetPort_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_EthernetPort_EnumerateInstances(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_EthernetPort_GetInstance(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EthernetPort* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_EthernetPort_CreateInstance(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EthernetPort* newInstance);

MI_EXTERN_C void MI_CALL ABC_EthernetPort_ModifyInstance(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EthernetPort* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_EthernetPort_DeleteInstance(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_EthernetPort* instanceName);

MI_EXTERN_C void MI_CALL ABC_EthernetPort_Invoke_RequestStateChange(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_EthernetPort* instanceName,
    const ABC_EthernetPort_RequestStateChange* in);

MI_EXTERN_C void MI_CALL ABC_EthernetPort_Invoke_SetPowerState(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_EthernetPort* instanceName,
    const ABC_EthernetPort_SetPowerState* in);

MI_EXTERN_C void MI_CALL ABC_EthernetPort_Invoke_Reset(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_EthernetPort* instanceName,
    const ABC_EthernetPort_Reset* in);

MI_EXTERN_C void MI_CALL ABC_EthernetPort_Invoke_EnableDevice(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_EthernetPort* instanceName,
    const ABC_EthernetPort_EnableDevice* in);

MI_EXTERN_C void MI_CALL ABC_EthernetPort_Invoke_OnlineDevice(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_EthernetPort* instanceName,
    const ABC_EthernetPort_OnlineDevice* in);

MI_EXTERN_C void MI_CALL ABC_EthernetPort_Invoke_QuiesceDevice(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_EthernetPort* instanceName,
    const ABC_EthernetPort_QuiesceDevice* in);

MI_EXTERN_C void MI_CALL ABC_EthernetPort_Invoke_SaveProperties(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_EthernetPort* instanceName,
    const ABC_EthernetPort_SaveProperties* in);

MI_EXTERN_C void MI_CALL ABC_EthernetPort_Invoke_RestoreProperties(
    ABC_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_EthernetPort* instanceName,
    const ABC_EthernetPort_RestoreProperties* in);


#endif /* _ABC_EthernetPort_h */
