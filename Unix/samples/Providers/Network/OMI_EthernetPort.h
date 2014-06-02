/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _OMI_EthernetPort_h
#define _OMI_EthernetPort_h

#include <MI.h>
#include "CIM_EthernetPort.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** OMI_EthernetPort [OMI_EthernetPort]
**
** Keys:
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**    DeviceID
**
**==============================================================================
*/

typedef struct _OMI_EthernetPort /* extends CIM_EthernetPort */
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
    /* OMI_EthernetPort properties */
}
OMI_EthernetPort;

typedef struct _OMI_EthernetPort_Ref
{
    OMI_EthernetPort* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_EthernetPort_Ref;

typedef struct _OMI_EthernetPort_ConstRef
{
    MI_CONST OMI_EthernetPort* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_EthernetPort_ConstRef;

typedef struct _OMI_EthernetPort_Array
{
    struct _OMI_EthernetPort** data;
    MI_Uint32 size;
}
OMI_EthernetPort_Array;

typedef struct _OMI_EthernetPort_ConstArray
{
    struct _OMI_EthernetPort MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
OMI_EthernetPort_ConstArray;

typedef struct _OMI_EthernetPort_ArrayRef
{
    OMI_EthernetPort_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_EthernetPort_ArrayRef;

typedef struct _OMI_EthernetPort_ConstArrayRef
{
    OMI_EthernetPort_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_EthernetPort_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl OMI_EthernetPort_rtti;

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Construct(
    OMI_EthernetPort* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &OMI_EthernetPort_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clone(
    const OMI_EthernetPort* self,
    OMI_EthernetPort** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL OMI_EthernetPort_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &OMI_EthernetPort_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Destruct(OMI_EthernetPort* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Delete(OMI_EthernetPort* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Post(
    const OMI_EthernetPort* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_InstanceID(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_InstanceID(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_InstanceID(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_Caption(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_Caption(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_Caption(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_Description(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_Description(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_Description(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_ElementName(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_ElementName(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_ElementName(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_InstallDate(
    OMI_EthernetPort* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_InstallDate(
    OMI_EthernetPort* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_Name(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_Name(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_Name(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_OperationalStatus(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_OperationalStatus(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_OperationalStatus(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_StatusDescriptions(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_StatusDescriptions(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_StatusDescriptions(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_Status(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_Status(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_Status(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_HealthState(
    OMI_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_HealthState(
    OMI_EthernetPort* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_CommunicationStatus(
    OMI_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_CommunicationStatus(
    OMI_EthernetPort* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_DetailedStatus(
    OMI_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_DetailedStatus(
    OMI_EthernetPort* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_OperatingStatus(
    OMI_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_OperatingStatus(
    OMI_EthernetPort* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_PrimaryStatus(
    OMI_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_PrimaryStatus(
    OMI_EthernetPort* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_EnabledState(
    OMI_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_EnabledState(
    OMI_EthernetPort* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_OtherEnabledState(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_OtherEnabledState(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_OtherEnabledState(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_RequestedState(
    OMI_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_RequestedState(
    OMI_EthernetPort* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_EnabledDefault(
    OMI_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_EnabledDefault(
    OMI_EthernetPort* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_TimeOfLastStateChange(
    OMI_EthernetPort* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_TimeOfLastStateChange(
    OMI_EthernetPort* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_AvailableRequestedStates(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_AvailableRequestedStates(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_AvailableRequestedStates(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_TransitioningToState(
    OMI_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_TransitioningToState(
    OMI_EthernetPort* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_SystemCreationClassName(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_SystemCreationClassName(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_SystemCreationClassName(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_SystemName(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_SystemName(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_SystemName(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_CreationClassName(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_CreationClassName(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_CreationClassName(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_DeviceID(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_DeviceID(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_DeviceID(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_PowerManagementSupported(
    OMI_EthernetPort* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->PowerManagementSupported)->value = x;
    ((MI_BooleanField*)&self->PowerManagementSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_PowerManagementSupported(
    OMI_EthernetPort* self)
{
    memset((void*)&self->PowerManagementSupported, 0, sizeof(self->PowerManagementSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_PowerManagementCapabilities(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_PowerManagementCapabilities(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_PowerManagementCapabilities(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_Availability(
    OMI_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Availability)->value = x;
    ((MI_Uint16Field*)&self->Availability)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_Availability(
    OMI_EthernetPort* self)
{
    memset((void*)&self->Availability, 0, sizeof(self->Availability));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_StatusInfo(
    OMI_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->StatusInfo)->value = x;
    ((MI_Uint16Field*)&self->StatusInfo)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_StatusInfo(
    OMI_EthernetPort* self)
{
    memset((void*)&self->StatusInfo, 0, sizeof(self->StatusInfo));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_LastErrorCode(
    OMI_EthernetPort* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->LastErrorCode)->value = x;
    ((MI_Uint32Field*)&self->LastErrorCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_LastErrorCode(
    OMI_EthernetPort* self)
{
    memset((void*)&self->LastErrorCode, 0, sizeof(self->LastErrorCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_ErrorDescription(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_ErrorDescription(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_ErrorDescription(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        30);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_ErrorCleared(
    OMI_EthernetPort* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->ErrorCleared)->value = x;
    ((MI_BooleanField*)&self->ErrorCleared)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_ErrorCleared(
    OMI_EthernetPort* self)
{
    memset((void*)&self->ErrorCleared, 0, sizeof(self->ErrorCleared));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_OtherIdentifyingInfo(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_OtherIdentifyingInfo(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_OtherIdentifyingInfo(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        32);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_PowerOnHours(
    OMI_EthernetPort* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->PowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->PowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_PowerOnHours(
    OMI_EthernetPort* self)
{
    memset((void*)&self->PowerOnHours, 0, sizeof(self->PowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_TotalPowerOnHours(
    OMI_EthernetPort* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_TotalPowerOnHours(
    OMI_EthernetPort* self)
{
    memset((void*)&self->TotalPowerOnHours, 0, sizeof(self->TotalPowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_IdentifyingDescriptions(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_IdentifyingDescriptions(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_IdentifyingDescriptions(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        35);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_AdditionalAvailability(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_AdditionalAvailability(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_AdditionalAvailability(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        36);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_MaxQuiesceTime(
    OMI_EthernetPort* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->value = x;
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_MaxQuiesceTime(
    OMI_EthernetPort* self)
{
    memset((void*)&self->MaxQuiesceTime, 0, sizeof(self->MaxQuiesceTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_Speed(
    OMI_EthernetPort* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->Speed)->value = x;
    ((MI_Uint64Field*)&self->Speed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_Speed(
    OMI_EthernetPort* self)
{
    memset((void*)&self->Speed, 0, sizeof(self->Speed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_MaxSpeed(
    OMI_EthernetPort* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MaxSpeed)->value = x;
    ((MI_Uint64Field*)&self->MaxSpeed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_MaxSpeed(
    OMI_EthernetPort* self)
{
    memset((void*)&self->MaxSpeed, 0, sizeof(self->MaxSpeed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_RequestedSpeed(
    OMI_EthernetPort* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->RequestedSpeed)->value = x;
    ((MI_Uint64Field*)&self->RequestedSpeed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_RequestedSpeed(
    OMI_EthernetPort* self)
{
    memset((void*)&self->RequestedSpeed, 0, sizeof(self->RequestedSpeed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_UsageRestriction(
    OMI_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->UsageRestriction)->value = x;
    ((MI_Uint16Field*)&self->UsageRestriction)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_UsageRestriction(
    OMI_EthernetPort* self)
{
    memset((void*)&self->UsageRestriction, 0, sizeof(self->UsageRestriction));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_PortType(
    OMI_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PortType)->value = x;
    ((MI_Uint16Field*)&self->PortType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_PortType(
    OMI_EthernetPort* self)
{
    memset((void*)&self->PortType, 0, sizeof(self->PortType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_OtherPortType(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        43,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_OtherPortType(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        43,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_OtherPortType(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        43);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_OtherNetworkPortType(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        44,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_OtherNetworkPortType(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        44,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_OtherNetworkPortType(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        44);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_PortNumber(
    OMI_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PortNumber)->value = x;
    ((MI_Uint16Field*)&self->PortNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_PortNumber(
    OMI_EthernetPort* self)
{
    memset((void*)&self->PortNumber, 0, sizeof(self->PortNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_LinkTechnology(
    OMI_EthernetPort* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->LinkTechnology)->value = x;
    ((MI_Uint16Field*)&self->LinkTechnology)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_LinkTechnology(
    OMI_EthernetPort* self)
{
    memset((void*)&self->LinkTechnology, 0, sizeof(self->LinkTechnology));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_OtherLinkTechnology(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        47,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_OtherLinkTechnology(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        47,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_OtherLinkTechnology(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        47);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_PermanentAddress(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        48,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_PermanentAddress(
    OMI_EthernetPort* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        48,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_PermanentAddress(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        48);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_NetworkAddresses(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_NetworkAddresses(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_NetworkAddresses(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        49);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_FullDuplex(
    OMI_EthernetPort* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->FullDuplex)->value = x;
    ((MI_BooleanField*)&self->FullDuplex)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_FullDuplex(
    OMI_EthernetPort* self)
{
    memset((void*)&self->FullDuplex, 0, sizeof(self->FullDuplex));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_AutoSense(
    OMI_EthernetPort* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->AutoSense)->value = x;
    ((MI_BooleanField*)&self->AutoSense)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_AutoSense(
    OMI_EthernetPort* self)
{
    memset((void*)&self->AutoSense, 0, sizeof(self->AutoSense));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_SupportedMaximumTransmissionUnit(
    OMI_EthernetPort* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->SupportedMaximumTransmissionUnit)->value = x;
    ((MI_Uint64Field*)&self->SupportedMaximumTransmissionUnit)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_SupportedMaximumTransmissionUnit(
    OMI_EthernetPort* self)
{
    memset((void*)&self->SupportedMaximumTransmissionUnit, 0, sizeof(self->SupportedMaximumTransmissionUnit));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_ActiveMaximumTransmissionUnit(
    OMI_EthernetPort* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ActiveMaximumTransmissionUnit)->value = x;
    ((MI_Uint64Field*)&self->ActiveMaximumTransmissionUnit)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_ActiveMaximumTransmissionUnit(
    OMI_EthernetPort* self)
{
    memset((void*)&self->ActiveMaximumTransmissionUnit, 0, sizeof(self->ActiveMaximumTransmissionUnit));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_MaxDataSize(
    OMI_EthernetPort* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MaxDataSize)->value = x;
    ((MI_Uint32Field*)&self->MaxDataSize)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_MaxDataSize(
    OMI_EthernetPort* self)
{
    memset((void*)&self->MaxDataSize, 0, sizeof(self->MaxDataSize));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_Capabilities(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_Capabilities(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_Capabilities(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        55);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_CapabilityDescriptions(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_CapabilityDescriptions(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_CapabilityDescriptions(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        56);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_EnabledCapabilities(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_EnabledCapabilities(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_EnabledCapabilities(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        57);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Set_OtherEnabledCapabilities(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPtr_OtherEnabledCapabilities(
    OMI_EthernetPort* self,
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

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Clear_OtherEnabledCapabilities(
    OMI_EthernetPort* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        58);
}

/*
**==============================================================================
**
** OMI_EthernetPort.RequestStateChange()
**
**==============================================================================
*/

typedef struct _OMI_EthernetPort_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
OMI_EthernetPort_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl OMI_EthernetPort_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RequestStateChange_Construct(
    OMI_EthernetPort_RequestStateChange* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &OMI_EthernetPort_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RequestStateChange_Clone(
    const OMI_EthernetPort_RequestStateChange* self,
    OMI_EthernetPort_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RequestStateChange_Destruct(
    OMI_EthernetPort_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RequestStateChange_Delete(
    OMI_EthernetPort_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RequestStateChange_Post(
    const OMI_EthernetPort_RequestStateChange* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RequestStateChange_Set_MIReturn(
    OMI_EthernetPort_RequestStateChange* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RequestStateChange_Clear_MIReturn(
    OMI_EthernetPort_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RequestStateChange_Set_RequestedState(
    OMI_EthernetPort_RequestStateChange* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RequestStateChange_Clear_RequestedState(
    OMI_EthernetPort_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RequestStateChange_Set_Job(
    OMI_EthernetPort_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RequestStateChange_SetPtr_Job(
    OMI_EthernetPort_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RequestStateChange_Clear_Job(
    OMI_EthernetPort_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RequestStateChange_Set_TimeoutPeriod(
    OMI_EthernetPort_RequestStateChange* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RequestStateChange_Clear_TimeoutPeriod(
    OMI_EthernetPort_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** OMI_EthernetPort.SetPowerState()
**
**==============================================================================
*/

typedef struct _OMI_EthernetPort_SetPowerState
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field PowerState;
    /*IN*/ MI_ConstDatetimeField Time;
}
OMI_EthernetPort_SetPowerState;

MI_EXTERN_C MI_CONST MI_MethodDecl OMI_EthernetPort_SetPowerState_rtti;

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPowerState_Construct(
    OMI_EthernetPort_SetPowerState* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &OMI_EthernetPort_SetPowerState_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPowerState_Clone(
    const OMI_EthernetPort_SetPowerState* self,
    OMI_EthernetPort_SetPowerState** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPowerState_Destruct(
    OMI_EthernetPort_SetPowerState* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPowerState_Delete(
    OMI_EthernetPort_SetPowerState* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPowerState_Post(
    const OMI_EthernetPort_SetPowerState* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPowerState_Set_MIReturn(
    OMI_EthernetPort_SetPowerState* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPowerState_Clear_MIReturn(
    OMI_EthernetPort_SetPowerState* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPowerState_Set_PowerState(
    OMI_EthernetPort_SetPowerState* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PowerState)->value = x;
    ((MI_Uint16Field*)&self->PowerState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPowerState_Clear_PowerState(
    OMI_EthernetPort_SetPowerState* self)
{
    memset((void*)&self->PowerState, 0, sizeof(self->PowerState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPowerState_Set_Time(
    OMI_EthernetPort_SetPowerState* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->Time)->value = x;
    ((MI_DatetimeField*)&self->Time)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SetPowerState_Clear_Time(
    OMI_EthernetPort_SetPowerState* self)
{
    memset((void*)&self->Time, 0, sizeof(self->Time));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** OMI_EthernetPort.Reset()
**
**==============================================================================
*/

typedef struct _OMI_EthernetPort_Reset
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
OMI_EthernetPort_Reset;

MI_EXTERN_C MI_CONST MI_MethodDecl OMI_EthernetPort_Reset_rtti;

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Reset_Construct(
    OMI_EthernetPort_Reset* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &OMI_EthernetPort_Reset_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Reset_Clone(
    const OMI_EthernetPort_Reset* self,
    OMI_EthernetPort_Reset** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Reset_Destruct(
    OMI_EthernetPort_Reset* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Reset_Delete(
    OMI_EthernetPort_Reset* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Reset_Post(
    const OMI_EthernetPort_Reset* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Reset_Set_MIReturn(
    OMI_EthernetPort_Reset* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_Reset_Clear_MIReturn(
    OMI_EthernetPort_Reset* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** OMI_EthernetPort.EnableDevice()
**
**==============================================================================
*/

typedef struct _OMI_EthernetPort_EnableDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Enabled;
}
OMI_EthernetPort_EnableDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl OMI_EthernetPort_EnableDevice_rtti;

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_EnableDevice_Construct(
    OMI_EthernetPort_EnableDevice* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &OMI_EthernetPort_EnableDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_EnableDevice_Clone(
    const OMI_EthernetPort_EnableDevice* self,
    OMI_EthernetPort_EnableDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_EnableDevice_Destruct(
    OMI_EthernetPort_EnableDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_EnableDevice_Delete(
    OMI_EthernetPort_EnableDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_EnableDevice_Post(
    const OMI_EthernetPort_EnableDevice* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_EnableDevice_Set_MIReturn(
    OMI_EthernetPort_EnableDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_EnableDevice_Clear_MIReturn(
    OMI_EthernetPort_EnableDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_EnableDevice_Set_Enabled(
    OMI_EthernetPort_EnableDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Enabled)->value = x;
    ((MI_BooleanField*)&self->Enabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_EnableDevice_Clear_Enabled(
    OMI_EthernetPort_EnableDevice* self)
{
    memset((void*)&self->Enabled, 0, sizeof(self->Enabled));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** OMI_EthernetPort.OnlineDevice()
**
**==============================================================================
*/

typedef struct _OMI_EthernetPort_OnlineDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Online;
}
OMI_EthernetPort_OnlineDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl OMI_EthernetPort_OnlineDevice_rtti;

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_OnlineDevice_Construct(
    OMI_EthernetPort_OnlineDevice* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &OMI_EthernetPort_OnlineDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_OnlineDevice_Clone(
    const OMI_EthernetPort_OnlineDevice* self,
    OMI_EthernetPort_OnlineDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_OnlineDevice_Destruct(
    OMI_EthernetPort_OnlineDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_OnlineDevice_Delete(
    OMI_EthernetPort_OnlineDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_OnlineDevice_Post(
    const OMI_EthernetPort_OnlineDevice* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_OnlineDevice_Set_MIReturn(
    OMI_EthernetPort_OnlineDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_OnlineDevice_Clear_MIReturn(
    OMI_EthernetPort_OnlineDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_OnlineDevice_Set_Online(
    OMI_EthernetPort_OnlineDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Online)->value = x;
    ((MI_BooleanField*)&self->Online)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_OnlineDevice_Clear_Online(
    OMI_EthernetPort_OnlineDevice* self)
{
    memset((void*)&self->Online, 0, sizeof(self->Online));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** OMI_EthernetPort.QuiesceDevice()
**
**==============================================================================
*/

typedef struct _OMI_EthernetPort_QuiesceDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Quiesce;
}
OMI_EthernetPort_QuiesceDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl OMI_EthernetPort_QuiesceDevice_rtti;

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_QuiesceDevice_Construct(
    OMI_EthernetPort_QuiesceDevice* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &OMI_EthernetPort_QuiesceDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_QuiesceDevice_Clone(
    const OMI_EthernetPort_QuiesceDevice* self,
    OMI_EthernetPort_QuiesceDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_QuiesceDevice_Destruct(
    OMI_EthernetPort_QuiesceDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_QuiesceDevice_Delete(
    OMI_EthernetPort_QuiesceDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_QuiesceDevice_Post(
    const OMI_EthernetPort_QuiesceDevice* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_QuiesceDevice_Set_MIReturn(
    OMI_EthernetPort_QuiesceDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_QuiesceDevice_Clear_MIReturn(
    OMI_EthernetPort_QuiesceDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_QuiesceDevice_Set_Quiesce(
    OMI_EthernetPort_QuiesceDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Quiesce)->value = x;
    ((MI_BooleanField*)&self->Quiesce)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_QuiesceDevice_Clear_Quiesce(
    OMI_EthernetPort_QuiesceDevice* self)
{
    memset((void*)&self->Quiesce, 0, sizeof(self->Quiesce));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** OMI_EthernetPort.SaveProperties()
**
**==============================================================================
*/

typedef struct _OMI_EthernetPort_SaveProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
OMI_EthernetPort_SaveProperties;

MI_EXTERN_C MI_CONST MI_MethodDecl OMI_EthernetPort_SaveProperties_rtti;

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SaveProperties_Construct(
    OMI_EthernetPort_SaveProperties* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &OMI_EthernetPort_SaveProperties_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SaveProperties_Clone(
    const OMI_EthernetPort_SaveProperties* self,
    OMI_EthernetPort_SaveProperties** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SaveProperties_Destruct(
    OMI_EthernetPort_SaveProperties* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SaveProperties_Delete(
    OMI_EthernetPort_SaveProperties* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SaveProperties_Post(
    const OMI_EthernetPort_SaveProperties* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SaveProperties_Set_MIReturn(
    OMI_EthernetPort_SaveProperties* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_SaveProperties_Clear_MIReturn(
    OMI_EthernetPort_SaveProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** OMI_EthernetPort.RestoreProperties()
**
**==============================================================================
*/

typedef struct _OMI_EthernetPort_RestoreProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
OMI_EthernetPort_RestoreProperties;

MI_EXTERN_C MI_CONST MI_MethodDecl OMI_EthernetPort_RestoreProperties_rtti;

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RestoreProperties_Construct(
    OMI_EthernetPort_RestoreProperties* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &OMI_EthernetPort_RestoreProperties_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RestoreProperties_Clone(
    const OMI_EthernetPort_RestoreProperties* self,
    OMI_EthernetPort_RestoreProperties** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RestoreProperties_Destruct(
    OMI_EthernetPort_RestoreProperties* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RestoreProperties_Delete(
    OMI_EthernetPort_RestoreProperties* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RestoreProperties_Post(
    const OMI_EthernetPort_RestoreProperties* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RestoreProperties_Set_MIReturn(
    OMI_EthernetPort_RestoreProperties* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_EthernetPort_RestoreProperties_Clear_MIReturn(
    OMI_EthernetPort_RestoreProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** OMI_EthernetPort provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _OMI_EthernetPort_Self OMI_EthernetPort_Self;

MI_EXTERN_C void MI_CALL OMI_EthernetPort_Load(
    OMI_EthernetPort_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL OMI_EthernetPort_Unload(
    OMI_EthernetPort_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL OMI_EthernetPort_EnumerateInstances(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL OMI_EthernetPort_GetInstance(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_EthernetPort* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL OMI_EthernetPort_CreateInstance(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_EthernetPort* newInstance);

MI_EXTERN_C void MI_CALL OMI_EthernetPort_ModifyInstance(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_EthernetPort* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL OMI_EthernetPort_DeleteInstance(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_EthernetPort* instanceName);

MI_EXTERN_C void MI_CALL OMI_EthernetPort_Invoke_RequestStateChange(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_EthernetPort* instanceName,
    const OMI_EthernetPort_RequestStateChange* in);

MI_EXTERN_C void MI_CALL OMI_EthernetPort_Invoke_SetPowerState(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_EthernetPort* instanceName,
    const OMI_EthernetPort_SetPowerState* in);

MI_EXTERN_C void MI_CALL OMI_EthernetPort_Invoke_Reset(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_EthernetPort* instanceName,
    const OMI_EthernetPort_Reset* in);

MI_EXTERN_C void MI_CALL OMI_EthernetPort_Invoke_EnableDevice(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_EthernetPort* instanceName,
    const OMI_EthernetPort_EnableDevice* in);

MI_EXTERN_C void MI_CALL OMI_EthernetPort_Invoke_OnlineDevice(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_EthernetPort* instanceName,
    const OMI_EthernetPort_OnlineDevice* in);

MI_EXTERN_C void MI_CALL OMI_EthernetPort_Invoke_QuiesceDevice(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_EthernetPort* instanceName,
    const OMI_EthernetPort_QuiesceDevice* in);

MI_EXTERN_C void MI_CALL OMI_EthernetPort_Invoke_SaveProperties(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_EthernetPort* instanceName,
    const OMI_EthernetPort_SaveProperties* in);

MI_EXTERN_C void MI_CALL OMI_EthernetPort_Invoke_RestoreProperties(
    OMI_EthernetPort_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const OMI_EthernetPort* instanceName,
    const OMI_EthernetPort_RestoreProperties* in);


#endif /* _OMI_EthernetPort_h */
