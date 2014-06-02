/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_IPProtocolEndpoint_h
#define _CIM_IPProtocolEndpoint_h

#include <MI.h>
#include "CIM_ProtocolEndpoint.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** CIM_IPProtocolEndpoint [CIM_IPProtocolEndpoint]
**
** Keys:
**    Name
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**
**==============================================================================
*/

typedef struct _CIM_IPProtocolEndpoint /* extends CIM_ProtocolEndpoint */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_ManagedSystemElement properties */
    MI_ConstDatetimeField InstallDate;
    /*KEY*/ MI_ConstStringField Name;
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
    /* CIM_ServiceAccessPoint properties */
    /*KEY*/ MI_ConstStringField SystemCreationClassName;
    /*KEY*/ MI_ConstStringField SystemName;
    /*KEY*/ MI_ConstStringField CreationClassName;
    /* CIM_ProtocolEndpoint properties */
    MI_ConstStringField NameFormat;
    MI_ConstUint16Field ProtocolType;
    MI_ConstUint16Field ProtocolIFType;
    MI_ConstStringField OtherTypeDescription;
    /* CIM_IPProtocolEndpoint properties */
    MI_ConstStringField IPv4Address;
    MI_ConstStringField Address;
    MI_ConstStringField SubnetMask;
    MI_ConstUint8Field PrefixLength;
    MI_ConstUint16Field AddressType;
    MI_ConstUint16Field IPVersionSupport;
    MI_ConstUint16Field AddressOrigin;
    MI_ConstUint16Field IPv6AddressType;
    MI_ConstUint16Field IPv6SubnetPrefixLength;
}
CIM_IPProtocolEndpoint;

typedef struct _CIM_IPProtocolEndpoint_Ref
{
    CIM_IPProtocolEndpoint* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_IPProtocolEndpoint_Ref;

typedef struct _CIM_IPProtocolEndpoint_ConstRef
{
    MI_CONST CIM_IPProtocolEndpoint* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_IPProtocolEndpoint_ConstRef;

typedef struct _CIM_IPProtocolEndpoint_Array
{
    struct _CIM_IPProtocolEndpoint** data;
    MI_Uint32 size;
}
CIM_IPProtocolEndpoint_Array;

typedef struct _CIM_IPProtocolEndpoint_ConstArray
{
    struct _CIM_IPProtocolEndpoint MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_IPProtocolEndpoint_ConstArray;

typedef struct _CIM_IPProtocolEndpoint_ArrayRef
{
    CIM_IPProtocolEndpoint_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_IPProtocolEndpoint_ArrayRef;

typedef struct _CIM_IPProtocolEndpoint_ConstArrayRef
{
    CIM_IPProtocolEndpoint_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_IPProtocolEndpoint_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_IPProtocolEndpoint_rtti;

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Construct(
    _Out_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_IPProtocolEndpoint_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clone(
    _In_ const CIM_IPProtocolEndpoint* self,
    _Outptr_ CIM_IPProtocolEndpoint** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_IPProtocolEndpoint_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_IPProtocolEndpoint_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Destruct(_Inout_ CIM_IPProtocolEndpoint* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Delete(_Inout_ CIM_IPProtocolEndpoint* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Post(
    _In_ const CIM_IPProtocolEndpoint* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_InstanceID(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_InstanceID(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_InstanceID(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_Caption(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_Caption(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_Caption(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_Description(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_Description(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_Description(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_ElementName(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_ElementName(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_ElementName(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_InstallDate(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_InstallDate(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_Name(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_Name(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_Name(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_OperationalStatus(
    _Inout_ CIM_IPProtocolEndpoint* self,
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

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_OperationalStatus(
    _Inout_ CIM_IPProtocolEndpoint* self,
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

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_OperationalStatus(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_StatusDescriptions(
    _Inout_ CIM_IPProtocolEndpoint* self,
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

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_StatusDescriptions(
    _Inout_ CIM_IPProtocolEndpoint* self,
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

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_StatusDescriptions(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_Status(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_Status(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_Status(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_HealthState(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_HealthState(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_CommunicationStatus(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_CommunicationStatus(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_DetailedStatus(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_DetailedStatus(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_OperatingStatus(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_OperatingStatus(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_PrimaryStatus(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_PrimaryStatus(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_EnabledState(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_EnabledState(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_OtherEnabledState(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_OtherEnabledState(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_OtherEnabledState(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_RequestedState(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_RequestedState(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_EnabledDefault(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_EnabledDefault(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_TimeOfLastStateChange(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_TimeOfLastStateChange(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_AvailableRequestedStates(
    _Inout_ CIM_IPProtocolEndpoint* self,
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

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_AvailableRequestedStates(
    _Inout_ CIM_IPProtocolEndpoint* self,
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

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_AvailableRequestedStates(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_TransitioningToState(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_TransitioningToState(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_SystemCreationClassName(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_SystemCreationClassName(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_SystemCreationClassName(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_SystemName(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_SystemName(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_SystemName(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_CreationClassName(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_CreationClassName(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_CreationClassName(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_NameFormat(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_NameFormat(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_NameFormat(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_ProtocolType(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ProtocolType)->value = x;
    ((MI_Uint16Field*)&self->ProtocolType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_ProtocolType(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->ProtocolType, 0, sizeof(self->ProtocolType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_ProtocolIFType(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ProtocolIFType)->value = x;
    ((MI_Uint16Field*)&self->ProtocolIFType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_ProtocolIFType(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->ProtocolIFType, 0, sizeof(self->ProtocolIFType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_OtherTypeDescription(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_OtherTypeDescription(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_OtherTypeDescription(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        27);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_IPv4Address(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        28,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_IPv4Address(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        28,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_IPv4Address(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        28);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_Address(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_Address(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_Address(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        29);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_SubnetMask(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_SetPtr_SubnetMask(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_SubnetMask(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        30);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_PrefixLength(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->PrefixLength)->value = x;
    ((MI_Uint8Field*)&self->PrefixLength)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_PrefixLength(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->PrefixLength, 0, sizeof(self->PrefixLength));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_AddressType(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->AddressType)->value = x;
    ((MI_Uint16Field*)&self->AddressType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_AddressType(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->AddressType, 0, sizeof(self->AddressType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_IPVersionSupport(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->IPVersionSupport)->value = x;
    ((MI_Uint16Field*)&self->IPVersionSupport)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_IPVersionSupport(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->IPVersionSupport, 0, sizeof(self->IPVersionSupport));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_AddressOrigin(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->AddressOrigin)->value = x;
    ((MI_Uint16Field*)&self->AddressOrigin)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_AddressOrigin(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->AddressOrigin, 0, sizeof(self->AddressOrigin));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_IPv6AddressType(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->IPv6AddressType)->value = x;
    ((MI_Uint16Field*)&self->IPv6AddressType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_IPv6AddressType(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->IPv6AddressType, 0, sizeof(self->IPv6AddressType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Set_IPv6SubnetPrefixLength(
    _Inout_ CIM_IPProtocolEndpoint* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->IPv6SubnetPrefixLength)->value = x;
    ((MI_Uint16Field*)&self->IPv6SubnetPrefixLength)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_Clear_IPv6SubnetPrefixLength(
    _Inout_ CIM_IPProtocolEndpoint* self)
{
    memset((void*)&self->IPv6SubnetPrefixLength, 0, sizeof(self->IPv6SubnetPrefixLength));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_IPProtocolEndpoint.RequestStateChange()
**
**==============================================================================
*/

typedef struct _CIM_IPProtocolEndpoint_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
CIM_IPProtocolEndpoint_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_IPProtocolEndpoint_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_RequestStateChange_Construct(
    _Out_ CIM_IPProtocolEndpoint_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_IPProtocolEndpoint_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_RequestStateChange_Clone(
    _In_ const CIM_IPProtocolEndpoint_RequestStateChange* self,
    _Outptr_ CIM_IPProtocolEndpoint_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_RequestStateChange_Destruct(
    _Inout_ CIM_IPProtocolEndpoint_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_RequestStateChange_Delete(
    _Inout_ CIM_IPProtocolEndpoint_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_RequestStateChange_Post(
    _In_ const CIM_IPProtocolEndpoint_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_RequestStateChange_Set_MIReturn(
    _Inout_ CIM_IPProtocolEndpoint_RequestStateChange* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_RequestStateChange_Clear_MIReturn(
    _Inout_ CIM_IPProtocolEndpoint_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_RequestStateChange_Set_RequestedState(
    _Inout_ CIM_IPProtocolEndpoint_RequestStateChange* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_RequestStateChange_Clear_RequestedState(
    _Inout_ CIM_IPProtocolEndpoint_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_RequestStateChange_Set_Job(
    _Inout_ CIM_IPProtocolEndpoint_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_RequestStateChange_SetPtr_Job(
    _Inout_ CIM_IPProtocolEndpoint_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_RequestStateChange_Clear_Job(
    _Inout_ CIM_IPProtocolEndpoint_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_RequestStateChange_Set_TimeoutPeriod(
    _Inout_ CIM_IPProtocolEndpoint_RequestStateChange* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IPProtocolEndpoint_RequestStateChange_Clear_TimeoutPeriod(
    _Inout_ CIM_IPProtocolEndpoint_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_IPProtocolEndpoint provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_IPProtocolEndpoint_Self CIM_IPProtocolEndpoint_Self;

MI_EXTERN_C void MI_CALL CIM_IPProtocolEndpoint_Load(
    _Outptr_result_maybenull_ CIM_IPProtocolEndpoint_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_IPProtocolEndpoint_Unload(
    _In_opt_ CIM_IPProtocolEndpoint_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_IPProtocolEndpoint_EnumerateInstances(
    _In_opt_ CIM_IPProtocolEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_IPProtocolEndpoint_GetInstance(
    _In_opt_ CIM_IPProtocolEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_IPProtocolEndpoint* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_IPProtocolEndpoint_CreateInstance(
    _In_opt_ CIM_IPProtocolEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_IPProtocolEndpoint* newInstance);

MI_EXTERN_C void MI_CALL CIM_IPProtocolEndpoint_ModifyInstance(
    _In_opt_ CIM_IPProtocolEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_IPProtocolEndpoint* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_IPProtocolEndpoint_DeleteInstance(
    _In_opt_ CIM_IPProtocolEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_IPProtocolEndpoint* instanceName);

MI_EXTERN_C void MI_CALL CIM_IPProtocolEndpoint_Invoke_RequestStateChange(
    _In_opt_ CIM_IPProtocolEndpoint_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_IPProtocolEndpoint* instanceName,
    _In_opt_ const CIM_IPProtocolEndpoint_RequestStateChange* in);


#endif /* _CIM_IPProtocolEndpoint_h */
