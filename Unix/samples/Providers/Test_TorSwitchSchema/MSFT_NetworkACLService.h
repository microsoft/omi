/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_NetworkACLService_h
#define _MSFT_NetworkACLService_h

#include <MI.h>
#include "CIM_NetworkPolicyService.h"
#include "CIM_ConcreteJob.h"
#include "MSFT_ACL.h"
#include "CIM_NetworkPolicyRule.h"
#include "CIM_NetworkPolicyCondition.h"
#include "CIM_NetworkPolicyAction.h"
#include "CIM_ManagedElement.h"
#include "CIM_NetworkVLAN.h"

/*
**==============================================================================
**
** MSFT_NetworkACLService [MSFT_NetworkACLService]
**
** Keys:
**    Name
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**
**==============================================================================
*/

typedef struct _MSFT_NetworkACLService /* extends CIM_NetworkPolicyService */
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
    /* CIM_Service properties */
    /*KEY*/ MI_ConstStringField SystemCreationClassName;
    /*KEY*/ MI_ConstStringField SystemName;
    /*KEY*/ MI_ConstStringField CreationClassName;
    MI_ConstStringField PrimaryOwnerName;
    MI_ConstStringField PrimaryOwnerContact;
    MI_ConstStringField StartMode;
    MI_ConstBooleanField Started;
    /* CIM_NetworkPolicyService properties */
    MI_ConstUint16Field ServiceType;
    MI_ConstStringField OtherServiceTypeDescription;
    MI_ConstStringField ServiceID;
    MI_ConstUint16Field ServiceIDType;
    /* MSFT_NetworkACLService properties */
}
MSFT_NetworkACLService;

typedef struct _MSFT_NetworkACLService_Ref
{
    MSFT_NetworkACLService* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_NetworkACLService_Ref;

typedef struct _MSFT_NetworkACLService_ConstRef
{
    MI_CONST MSFT_NetworkACLService* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_NetworkACLService_ConstRef;

typedef struct _MSFT_NetworkACLService_Array
{
    struct _MSFT_NetworkACLService** data;
    MI_Uint32 size;
}
MSFT_NetworkACLService_Array;

typedef struct _MSFT_NetworkACLService_ConstArray
{
    struct _MSFT_NetworkACLService MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_NetworkACLService_ConstArray;

typedef struct _MSFT_NetworkACLService_ArrayRef
{
    MSFT_NetworkACLService_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_NetworkACLService_ArrayRef;

typedef struct _MSFT_NetworkACLService_ConstArrayRef
{
    MSFT_NetworkACLService_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_NetworkACLService_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_NetworkACLService_rtti;

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Construct(
    _Out_ MSFT_NetworkACLService* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_NetworkACLService_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clone(
    _In_ const MSFT_NetworkACLService* self,
    _Outptr_ MSFT_NetworkACLService** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_NetworkACLService_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_NetworkACLService_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Destruct(_Inout_ MSFT_NetworkACLService* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Delete(_Inout_ MSFT_NetworkACLService* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Post(
    _In_ const MSFT_NetworkACLService* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_InstanceID(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_InstanceID(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_InstanceID(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_Caption(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_Caption(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_Caption(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_Description(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_Description(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_Description(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_ElementName(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_ElementName(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_ElementName(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_InstallDate(
    _Inout_ MSFT_NetworkACLService* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_InstallDate(
    _Inout_ MSFT_NetworkACLService* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_Name(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_Name(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_Name(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_OperationalStatus(
    _Inout_ MSFT_NetworkACLService* self,
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

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_OperationalStatus(
    _Inout_ MSFT_NetworkACLService* self,
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

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_OperationalStatus(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_StatusDescriptions(
    _Inout_ MSFT_NetworkACLService* self,
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

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_StatusDescriptions(
    _Inout_ MSFT_NetworkACLService* self,
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

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_StatusDescriptions(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_Status(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_Status(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_Status(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_HealthState(
    _Inout_ MSFT_NetworkACLService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_HealthState(
    _Inout_ MSFT_NetworkACLService* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_CommunicationStatus(
    _Inout_ MSFT_NetworkACLService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_CommunicationStatus(
    _Inout_ MSFT_NetworkACLService* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_DetailedStatus(
    _Inout_ MSFT_NetworkACLService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_DetailedStatus(
    _Inout_ MSFT_NetworkACLService* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_OperatingStatus(
    _Inout_ MSFT_NetworkACLService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_OperatingStatus(
    _Inout_ MSFT_NetworkACLService* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_PrimaryStatus(
    _Inout_ MSFT_NetworkACLService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_PrimaryStatus(
    _Inout_ MSFT_NetworkACLService* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_EnabledState(
    _Inout_ MSFT_NetworkACLService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_EnabledState(
    _Inout_ MSFT_NetworkACLService* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_OtherEnabledState(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_OtherEnabledState(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_OtherEnabledState(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_RequestedState(
    _Inout_ MSFT_NetworkACLService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_RequestedState(
    _Inout_ MSFT_NetworkACLService* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_EnabledDefault(
    _Inout_ MSFT_NetworkACLService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_EnabledDefault(
    _Inout_ MSFT_NetworkACLService* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_TimeOfLastStateChange(
    _Inout_ MSFT_NetworkACLService* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_TimeOfLastStateChange(
    _Inout_ MSFT_NetworkACLService* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_AvailableRequestedStates(
    _Inout_ MSFT_NetworkACLService* self,
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

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_AvailableRequestedStates(
    _Inout_ MSFT_NetworkACLService* self,
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

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_AvailableRequestedStates(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_TransitioningToState(
    _Inout_ MSFT_NetworkACLService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_TransitioningToState(
    _Inout_ MSFT_NetworkACLService* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_SystemCreationClassName(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_SystemCreationClassName(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_SystemCreationClassName(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_SystemName(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_SystemName(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_SystemName(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_CreationClassName(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_CreationClassName(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_CreationClassName(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_PrimaryOwnerName(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_PrimaryOwnerName(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_PrimaryOwnerName(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_PrimaryOwnerContact(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_PrimaryOwnerContact(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_PrimaryOwnerContact(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        25);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_StartMode(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_StartMode(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_StartMode(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_Started(
    _Inout_ MSFT_NetworkACLService* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Started)->value = x;
    ((MI_BooleanField*)&self->Started)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_Started(
    _Inout_ MSFT_NetworkACLService* self)
{
    memset((void*)&self->Started, 0, sizeof(self->Started));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_ServiceType(
    _Inout_ MSFT_NetworkACLService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ServiceType)->value = x;
    ((MI_Uint16Field*)&self->ServiceType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_ServiceType(
    _Inout_ MSFT_NetworkACLService* self)
{
    memset((void*)&self->ServiceType, 0, sizeof(self->ServiceType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_OtherServiceTypeDescription(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_OtherServiceTypeDescription(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_OtherServiceTypeDescription(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        29);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_ServiceID(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_SetPtr_ServiceID(
    _Inout_ MSFT_NetworkACLService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_ServiceID(
    _Inout_ MSFT_NetworkACLService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        30);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Set_ServiceIDType(
    _Inout_ MSFT_NetworkACLService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ServiceIDType)->value = x;
    ((MI_Uint16Field*)&self->ServiceIDType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_Clear_ServiceIDType(
    _Inout_ MSFT_NetworkACLService* self)
{
    memset((void*)&self->ServiceIDType, 0, sizeof(self->ServiceIDType));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_NetworkACLService.RequestStateChange()
**
**==============================================================================
*/

typedef struct _MSFT_NetworkACLService_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
MSFT_NetworkACLService_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_NetworkACLService_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RequestStateChange_Construct(
    _Out_ MSFT_NetworkACLService_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_NetworkACLService_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RequestStateChange_Clone(
    _In_ const MSFT_NetworkACLService_RequestStateChange* self,
    _Outptr_ MSFT_NetworkACLService_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RequestStateChange_Destruct(
    _Inout_ MSFT_NetworkACLService_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RequestStateChange_Delete(
    _Inout_ MSFT_NetworkACLService_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RequestStateChange_Post(
    _In_ const MSFT_NetworkACLService_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RequestStateChange_Set_MIReturn(
    _Inout_ MSFT_NetworkACLService_RequestStateChange* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RequestStateChange_Clear_MIReturn(
    _Inout_ MSFT_NetworkACLService_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RequestStateChange_Set_RequestedState(
    _Inout_ MSFT_NetworkACLService_RequestStateChange* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RequestStateChange_Clear_RequestedState(
    _Inout_ MSFT_NetworkACLService_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RequestStateChange_Set_Job(
    _Inout_ MSFT_NetworkACLService_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RequestStateChange_SetPtr_Job(
    _Inout_ MSFT_NetworkACLService_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RequestStateChange_Clear_Job(
    _Inout_ MSFT_NetworkACLService_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RequestStateChange_Set_TimeoutPeriod(
    _Inout_ MSFT_NetworkACLService_RequestStateChange* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RequestStateChange_Clear_TimeoutPeriod(
    _Inout_ MSFT_NetworkACLService_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_NetworkACLService.StartService()
**
**==============================================================================
*/

typedef struct _MSFT_NetworkACLService_StartService
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MSFT_NetworkACLService_StartService;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_NetworkACLService_StartService_rtti;

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_StartService_Construct(
    _Out_ MSFT_NetworkACLService_StartService* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_NetworkACLService_StartService_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_StartService_Clone(
    _In_ const MSFT_NetworkACLService_StartService* self,
    _Outptr_ MSFT_NetworkACLService_StartService** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_StartService_Destruct(
    _Inout_ MSFT_NetworkACLService_StartService* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_StartService_Delete(
    _Inout_ MSFT_NetworkACLService_StartService* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_StartService_Post(
    _In_ const MSFT_NetworkACLService_StartService* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_StartService_Set_MIReturn(
    _Inout_ MSFT_NetworkACLService_StartService* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_StartService_Clear_MIReturn(
    _Inout_ MSFT_NetworkACLService_StartService* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_NetworkACLService.StopService()
**
**==============================================================================
*/

typedef struct _MSFT_NetworkACLService_StopService
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MSFT_NetworkACLService_StopService;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_NetworkACLService_StopService_rtti;

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_StopService_Construct(
    _Out_ MSFT_NetworkACLService_StopService* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_NetworkACLService_StopService_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_StopService_Clone(
    _In_ const MSFT_NetworkACLService_StopService* self,
    _Outptr_ MSFT_NetworkACLService_StopService** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_StopService_Destruct(
    _Inout_ MSFT_NetworkACLService_StopService* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_StopService_Delete(
    _Inout_ MSFT_NetworkACLService_StopService* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_StopService_Post(
    _In_ const MSFT_NetworkACLService_StopService* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_StopService_Set_MIReturn(
    _Inout_ MSFT_NetworkACLService_StopService* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_StopService_Clear_MIReturn(
    _Inout_ MSFT_NetworkACLService_StopService* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_NetworkACLService.CreateACL()
**
**==============================================================================
*/

typedef struct _MSFT_NetworkACLService_CreateACL
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MSFT_ACL_ConstRef AccessList;
    /*OUT*/ MSFT_ACL_ConstRef ResultingACL;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_NetworkACLService_CreateACL;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_NetworkACLService_CreateACL_rtti;

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_CreateACL_Construct(
    _Out_ MSFT_NetworkACLService_CreateACL* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_NetworkACLService_CreateACL_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_CreateACL_Clone(
    _In_ const MSFT_NetworkACLService_CreateACL* self,
    _Outptr_ MSFT_NetworkACLService_CreateACL** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_CreateACL_Destruct(
    _Inout_ MSFT_NetworkACLService_CreateACL* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_CreateACL_Delete(
    _Inout_ MSFT_NetworkACLService_CreateACL* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_CreateACL_Post(
    _In_ const MSFT_NetworkACLService_CreateACL* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_CreateACL_Set_MIReturn(
    _Inout_ MSFT_NetworkACLService_CreateACL* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_CreateACL_Clear_MIReturn(
    _Inout_ MSFT_NetworkACLService_CreateACL* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_CreateACL_Set_AccessList(
    _Inout_ MSFT_NetworkACLService_CreateACL* self,
    _In_ const MSFT_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_CreateACL_SetPtr_AccessList(
    _Inout_ MSFT_NetworkACLService_CreateACL* self,
    _In_ const MSFT_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_CreateACL_Clear_AccessList(
    _Inout_ MSFT_NetworkACLService_CreateACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_CreateACL_Set_ResultingACL(
    _Inout_ MSFT_NetworkACLService_CreateACL* self,
    _In_ const MSFT_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_CreateACL_SetPtr_ResultingACL(
    _Inout_ MSFT_NetworkACLService_CreateACL* self,
    _In_ const MSFT_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_CreateACL_Clear_ResultingACL(
    _Inout_ MSFT_NetworkACLService_CreateACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_CreateACL_Set_Job(
    _Inout_ MSFT_NetworkACLService_CreateACL* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_CreateACL_SetPtr_Job(
    _Inout_ MSFT_NetworkACLService_CreateACL* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_CreateACL_Clear_Job(
    _Inout_ MSFT_NetworkACLService_CreateACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_NetworkACLService.AddRule()
**
**==============================================================================
*/

typedef struct _MSFT_NetworkACLService_AddRule
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MSFT_ACL_ConstRef TargetACL;
CIM_NetworkPolicyRule_ConstRef NetworkPolicyRule;
CIM_NetworkPolicyCondition_ConstArrayRef NetworkPolicyCondition;
CIM_NetworkPolicyAction_ConstArrayRef NetworkPolicyAction;
MI_ConstUint32Field SequenceNumber;
    /*OUT*/ CIM_NetworkPolicyRule_ConstRef ResultingNetworkPolicyRule;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_NetworkACLService_AddRule;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_NetworkACLService_AddRule_rtti;

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Construct(
    _Out_ MSFT_NetworkACLService_AddRule* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_NetworkACLService_AddRule_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Clone(
    _In_ const MSFT_NetworkACLService_AddRule* self,
    _Outptr_ MSFT_NetworkACLService_AddRule** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Destruct(
    _Inout_ MSFT_NetworkACLService_AddRule* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Delete(
    _Inout_ MSFT_NetworkACLService_AddRule* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Post(
    _In_ const MSFT_NetworkACLService_AddRule* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Set_MIReturn(
    _Inout_ MSFT_NetworkACLService_AddRule* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Clear_MIReturn(
    _Inout_ MSFT_NetworkACLService_AddRule* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Set_TargetACL(
    _Inout_ MSFT_NetworkACLService_AddRule* self,
    _In_ const MSFT_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_SetPtr_TargetACL(
    _Inout_ MSFT_NetworkACLService_AddRule* self,
    _In_ const MSFT_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Clear_TargetACL(
    _Inout_ MSFT_NetworkACLService_AddRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Set_NetworkPolicyRule(
    _Inout_ MSFT_NetworkACLService_AddRule* self,
    _In_ const CIM_NetworkPolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_SetPtr_NetworkPolicyRule(
    _Inout_ MSFT_NetworkACLService_AddRule* self,
    _In_ const CIM_NetworkPolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Clear_NetworkPolicyRule(
    _Inout_ MSFT_NetworkACLService_AddRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Set_NetworkPolicyCondition(
    _Inout_ MSFT_NetworkACLService_AddRule* self,
    _In_reads_opt_(size) const CIM_NetworkPolicyCondition * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_SetPtr_NetworkPolicyCondition(
    _Inout_ MSFT_NetworkACLService_AddRule* self,
    _In_reads_opt_(size) const CIM_NetworkPolicyCondition * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Clear_NetworkPolicyCondition(
    _Inout_ MSFT_NetworkACLService_AddRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Set_NetworkPolicyAction(
    _Inout_ MSFT_NetworkACLService_AddRule* self,
    _In_reads_opt_(size) const CIM_NetworkPolicyAction * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_SetPtr_NetworkPolicyAction(
    _Inout_ MSFT_NetworkACLService_AddRule* self,
    _In_reads_opt_(size) const CIM_NetworkPolicyAction * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Clear_NetworkPolicyAction(
    _Inout_ MSFT_NetworkACLService_AddRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Set_SequenceNumber(
    _Inout_ MSFT_NetworkACLService_AddRule* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->SequenceNumber)->value = x;
    ((MI_Uint32Field*)&self->SequenceNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Clear_SequenceNumber(
    _Inout_ MSFT_NetworkACLService_AddRule* self)
{
    memset((void*)&self->SequenceNumber, 0, sizeof(self->SequenceNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Set_ResultingNetworkPolicyRule(
    _Inout_ MSFT_NetworkACLService_AddRule* self,
    _In_ const CIM_NetworkPolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_SetPtr_ResultingNetworkPolicyRule(
    _Inout_ MSFT_NetworkACLService_AddRule* self,
    _In_ const CIM_NetworkPolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Clear_ResultingNetworkPolicyRule(
    _Inout_ MSFT_NetworkACLService_AddRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Set_Job(
    _Inout_ MSFT_NetworkACLService_AddRule* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_SetPtr_Job(
    _Inout_ MSFT_NetworkACLService_AddRule* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRule_Clear_Job(
    _Inout_ MSFT_NetworkACLService_AddRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

/*
**==============================================================================
**
** MSFT_NetworkACLService.RemoveACL()
**
**==============================================================================
*/

typedef struct _MSFT_NetworkACLService_RemoveACL
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MSFT_ACL_ConstRef RemovedACL;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_NetworkACLService_RemoveACL;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_NetworkACLService_RemoveACL_rtti;

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveACL_Construct(
    _Out_ MSFT_NetworkACLService_RemoveACL* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_NetworkACLService_RemoveACL_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveACL_Clone(
    _In_ const MSFT_NetworkACLService_RemoveACL* self,
    _Outptr_ MSFT_NetworkACLService_RemoveACL** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveACL_Destruct(
    _Inout_ MSFT_NetworkACLService_RemoveACL* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveACL_Delete(
    _Inout_ MSFT_NetworkACLService_RemoveACL* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveACL_Post(
    _In_ const MSFT_NetworkACLService_RemoveACL* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveACL_Set_MIReturn(
    _Inout_ MSFT_NetworkACLService_RemoveACL* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveACL_Clear_MIReturn(
    _Inout_ MSFT_NetworkACLService_RemoveACL* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveACL_Set_RemovedACL(
    _Inout_ MSFT_NetworkACLService_RemoveACL* self,
    _In_ const MSFT_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveACL_SetPtr_RemovedACL(
    _Inout_ MSFT_NetworkACLService_RemoveACL* self,
    _In_ const MSFT_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveACL_Clear_RemovedACL(
    _Inout_ MSFT_NetworkACLService_RemoveACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveACL_Set_Job(
    _Inout_ MSFT_NetworkACLService_RemoveACL* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveACL_SetPtr_Job(
    _Inout_ MSFT_NetworkACLService_RemoveACL* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveACL_Clear_Job(
    _Inout_ MSFT_NetworkACLService_RemoveACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** MSFT_NetworkACLService.RemoveRule()
**
**==============================================================================
*/

typedef struct _MSFT_NetworkACLService_RemoveRule
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
CIM_NetworkPolicyRule_ConstRef RemovedRule;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_NetworkACLService_RemoveRule;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_NetworkACLService_RemoveRule_rtti;

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveRule_Construct(
    _Out_ MSFT_NetworkACLService_RemoveRule* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_NetworkACLService_RemoveRule_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveRule_Clone(
    _In_ const MSFT_NetworkACLService_RemoveRule* self,
    _Outptr_ MSFT_NetworkACLService_RemoveRule** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveRule_Destruct(
    _Inout_ MSFT_NetworkACLService_RemoveRule* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveRule_Delete(
    _Inout_ MSFT_NetworkACLService_RemoveRule* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveRule_Post(
    _In_ const MSFT_NetworkACLService_RemoveRule* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveRule_Set_MIReturn(
    _Inout_ MSFT_NetworkACLService_RemoveRule* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveRule_Clear_MIReturn(
    _Inout_ MSFT_NetworkACLService_RemoveRule* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveRule_Set_RemovedRule(
    _Inout_ MSFT_NetworkACLService_RemoveRule* self,
    _In_ const CIM_NetworkPolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveRule_SetPtr_RemovedRule(
    _Inout_ MSFT_NetworkACLService_RemoveRule* self,
    _In_ const CIM_NetworkPolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveRule_Clear_RemovedRule(
    _Inout_ MSFT_NetworkACLService_RemoveRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveRule_Set_Job(
    _Inout_ MSFT_NetworkACLService_RemoveRule* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveRule_SetPtr_Job(
    _Inout_ MSFT_NetworkACLService_RemoveRule* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_RemoveRule_Clear_Job(
    _Inout_ MSFT_NetworkACLService_RemoveRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** MSFT_NetworkACLService.ResequenceRule()
**
**==============================================================================
*/

typedef struct _MSFT_NetworkACLService_ResequenceRule
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
CIM_NetworkPolicyRule_ConstRef TargetRule;
MI_ConstUint32Field SequenceNumber;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_NetworkACLService_ResequenceRule;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_NetworkACLService_ResequenceRule_rtti;

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_ResequenceRule_Construct(
    _Out_ MSFT_NetworkACLService_ResequenceRule* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_NetworkACLService_ResequenceRule_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_ResequenceRule_Clone(
    _In_ const MSFT_NetworkACLService_ResequenceRule* self,
    _Outptr_ MSFT_NetworkACLService_ResequenceRule** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_ResequenceRule_Destruct(
    _Inout_ MSFT_NetworkACLService_ResequenceRule* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_ResequenceRule_Delete(
    _Inout_ MSFT_NetworkACLService_ResequenceRule* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_ResequenceRule_Post(
    _In_ const MSFT_NetworkACLService_ResequenceRule* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_ResequenceRule_Set_MIReturn(
    _Inout_ MSFT_NetworkACLService_ResequenceRule* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_ResequenceRule_Clear_MIReturn(
    _Inout_ MSFT_NetworkACLService_ResequenceRule* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_ResequenceRule_Set_TargetRule(
    _Inout_ MSFT_NetworkACLService_ResequenceRule* self,
    _In_ const CIM_NetworkPolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_ResequenceRule_SetPtr_TargetRule(
    _Inout_ MSFT_NetworkACLService_ResequenceRule* self,
    _In_ const CIM_NetworkPolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_ResequenceRule_Clear_TargetRule(
    _Inout_ MSFT_NetworkACLService_ResequenceRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_ResequenceRule_Set_SequenceNumber(
    _Inout_ MSFT_NetworkACLService_ResequenceRule* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->SequenceNumber)->value = x;
    ((MI_Uint32Field*)&self->SequenceNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_ResequenceRule_Clear_SequenceNumber(
    _Inout_ MSFT_NetworkACLService_ResequenceRule* self)
{
    memset((void*)&self->SequenceNumber, 0, sizeof(self->SequenceNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_ResequenceRule_Set_Job(
    _Inout_ MSFT_NetworkACLService_ResequenceRule* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_ResequenceRule_SetPtr_Job(
    _Inout_ MSFT_NetworkACLService_ResequenceRule* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_ResequenceRule_Clear_Job(
    _Inout_ MSFT_NetworkACLService_ResequenceRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_NetworkACLService.AttachACL()
**
**==============================================================================
*/

typedef struct _MSFT_NetworkACLService_AttachACL
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MSFT_ACL_ConstRef AttachedACL;
CIM_ManagedElement_ConstRef TargetInterface;
MI_ConstUint16Field Direction;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_NetworkACLService_AttachACL;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_NetworkACLService_AttachACL_rtti;

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_Construct(
    _Out_ MSFT_NetworkACLService_AttachACL* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_NetworkACLService_AttachACL_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_Clone(
    _In_ const MSFT_NetworkACLService_AttachACL* self,
    _Outptr_ MSFT_NetworkACLService_AttachACL** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_Destruct(
    _Inout_ MSFT_NetworkACLService_AttachACL* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_Delete(
    _Inout_ MSFT_NetworkACLService_AttachACL* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_Post(
    _In_ const MSFT_NetworkACLService_AttachACL* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_Set_MIReturn(
    _Inout_ MSFT_NetworkACLService_AttachACL* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_Clear_MIReturn(
    _Inout_ MSFT_NetworkACLService_AttachACL* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_Set_AttachedACL(
    _Inout_ MSFT_NetworkACLService_AttachACL* self,
    _In_ const MSFT_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_SetPtr_AttachedACL(
    _Inout_ MSFT_NetworkACLService_AttachACL* self,
    _In_ const MSFT_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_Clear_AttachedACL(
    _Inout_ MSFT_NetworkACLService_AttachACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_Set_TargetInterface(
    _Inout_ MSFT_NetworkACLService_AttachACL* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_SetPtr_TargetInterface(
    _Inout_ MSFT_NetworkACLService_AttachACL* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_Clear_TargetInterface(
    _Inout_ MSFT_NetworkACLService_AttachACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_Set_Direction(
    _Inout_ MSFT_NetworkACLService_AttachACL* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Direction)->value = x;
    ((MI_Uint16Field*)&self->Direction)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_Clear_Direction(
    _Inout_ MSFT_NetworkACLService_AttachACL* self)
{
    memset((void*)&self->Direction, 0, sizeof(self->Direction));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_Set_Job(
    _Inout_ MSFT_NetworkACLService_AttachACL* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_SetPtr_Job(
    _Inout_ MSFT_NetworkACLService_AttachACL* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachACL_Clear_Job(
    _Inout_ MSFT_NetworkACLService_AttachACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** MSFT_NetworkACLService.AttachVACL()
**
**==============================================================================
*/

typedef struct _MSFT_NetworkACLService_AttachVACL
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MSFT_ACL_ConstRef AttachedVACL;
CIM_NetworkVLAN_ConstRef TargetInterface;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_NetworkACLService_AttachVACL;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_NetworkACLService_AttachVACL_rtti;

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachVACL_Construct(
    _Out_ MSFT_NetworkACLService_AttachVACL* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_NetworkACLService_AttachVACL_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachVACL_Clone(
    _In_ const MSFT_NetworkACLService_AttachVACL* self,
    _Outptr_ MSFT_NetworkACLService_AttachVACL** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachVACL_Destruct(
    _Inout_ MSFT_NetworkACLService_AttachVACL* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachVACL_Delete(
    _Inout_ MSFT_NetworkACLService_AttachVACL* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachVACL_Post(
    _In_ const MSFT_NetworkACLService_AttachVACL* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachVACL_Set_MIReturn(
    _Inout_ MSFT_NetworkACLService_AttachVACL* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachVACL_Clear_MIReturn(
    _Inout_ MSFT_NetworkACLService_AttachVACL* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachVACL_Set_AttachedVACL(
    _Inout_ MSFT_NetworkACLService_AttachVACL* self,
    _In_ const MSFT_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachVACL_SetPtr_AttachedVACL(
    _Inout_ MSFT_NetworkACLService_AttachVACL* self,
    _In_ const MSFT_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachVACL_Clear_AttachedVACL(
    _Inout_ MSFT_NetworkACLService_AttachVACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachVACL_Set_TargetInterface(
    _Inout_ MSFT_NetworkACLService_AttachVACL* self,
    _In_ const CIM_NetworkVLAN* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachVACL_SetPtr_TargetInterface(
    _Inout_ MSFT_NetworkACLService_AttachVACL* self,
    _In_ const CIM_NetworkVLAN* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachVACL_Clear_TargetInterface(
    _Inout_ MSFT_NetworkACLService_AttachVACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachVACL_Set_Job(
    _Inout_ MSFT_NetworkACLService_AttachVACL* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachVACL_SetPtr_Job(
    _Inout_ MSFT_NetworkACLService_AttachVACL* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AttachVACL_Clear_Job(
    _Inout_ MSFT_NetworkACLService_AttachVACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_NetworkACLService.DetachACL()
**
**==============================================================================
*/

typedef struct _MSFT_NetworkACLService_DetachACL
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MSFT_ACL_ConstRef AttachedACL;
CIM_ManagedElement_ConstRef TargetInterface;
MI_ConstUint16Field Direction;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_NetworkACLService_DetachACL;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_NetworkACLService_DetachACL_rtti;

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_Construct(
    _Out_ MSFT_NetworkACLService_DetachACL* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_NetworkACLService_DetachACL_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_Clone(
    _In_ const MSFT_NetworkACLService_DetachACL* self,
    _Outptr_ MSFT_NetworkACLService_DetachACL** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_Destruct(
    _Inout_ MSFT_NetworkACLService_DetachACL* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_Delete(
    _Inout_ MSFT_NetworkACLService_DetachACL* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_Post(
    _In_ const MSFT_NetworkACLService_DetachACL* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_Set_MIReturn(
    _Inout_ MSFT_NetworkACLService_DetachACL* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_Clear_MIReturn(
    _Inout_ MSFT_NetworkACLService_DetachACL* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_Set_AttachedACL(
    _Inout_ MSFT_NetworkACLService_DetachACL* self,
    _In_ const MSFT_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_SetPtr_AttachedACL(
    _Inout_ MSFT_NetworkACLService_DetachACL* self,
    _In_ const MSFT_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_Clear_AttachedACL(
    _Inout_ MSFT_NetworkACLService_DetachACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_Set_TargetInterface(
    _Inout_ MSFT_NetworkACLService_DetachACL* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_SetPtr_TargetInterface(
    _Inout_ MSFT_NetworkACLService_DetachACL* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_Clear_TargetInterface(
    _Inout_ MSFT_NetworkACLService_DetachACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_Set_Direction(
    _Inout_ MSFT_NetworkACLService_DetachACL* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Direction)->value = x;
    ((MI_Uint16Field*)&self->Direction)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_Clear_Direction(
    _Inout_ MSFT_NetworkACLService_DetachACL* self)
{
    memset((void*)&self->Direction, 0, sizeof(self->Direction));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_Set_Job(
    _Inout_ MSFT_NetworkACLService_DetachACL* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_SetPtr_Job(
    _Inout_ MSFT_NetworkACLService_DetachACL* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_DetachACL_Clear_Job(
    _Inout_ MSFT_NetworkACLService_DetachACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** MSFT_NetworkACLService.AddRuleWithMatchedACL()
**
**==============================================================================
*/

typedef struct _MSFT_NetworkACLService_AddRuleWithMatchedACL
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MSFT_ACL_ConstRef TargetACL;
CIM_NetworkPolicyRule_ConstRef NetworkPolicyRule;
MSFT_ACL_ConstArrayRef MatchedACLs;
CIM_NetworkPolicyAction_ConstArrayRef NetworkPolicyAction;
MI_ConstUint32Field SequenceNumber;
    /*OUT*/ CIM_NetworkPolicyRule_ConstRef ResultingNetworkPolicyRule;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_NetworkACLService_AddRuleWithMatchedACL;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_NetworkACLService_AddRuleWithMatchedACL_rtti;

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Construct(
    _Out_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_NetworkACLService_AddRuleWithMatchedACL_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Clone(
    _In_ const MSFT_NetworkACLService_AddRuleWithMatchedACL* self,
    _Outptr_ MSFT_NetworkACLService_AddRuleWithMatchedACL** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Destruct(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Delete(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Post(
    _In_ const MSFT_NetworkACLService_AddRuleWithMatchedACL* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Set_MIReturn(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Clear_MIReturn(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Set_TargetACL(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self,
    _In_ const MSFT_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_SetPtr_TargetACL(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self,
    _In_ const MSFT_ACL* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Clear_TargetACL(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Set_NetworkPolicyRule(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self,
    _In_ const CIM_NetworkPolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_SetPtr_NetworkPolicyRule(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self,
    _In_ const CIM_NetworkPolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Clear_NetworkPolicyRule(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Set_MatchedACLs(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self,
    _In_reads_opt_(size) const MSFT_ACL* const* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_SetPtr_MatchedACLs(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self,
    _In_reads_opt_(size) const MSFT_ACL* const* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Clear_MatchedACLs(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Set_NetworkPolicyAction(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self,
    _In_reads_opt_(size) const CIM_NetworkPolicyAction * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_SetPtr_NetworkPolicyAction(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self,
    _In_reads_opt_(size) const CIM_NetworkPolicyAction * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Clear_NetworkPolicyAction(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Set_SequenceNumber(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->SequenceNumber)->value = x;
    ((MI_Uint32Field*)&self->SequenceNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Clear_SequenceNumber(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self)
{
    memset((void*)&self->SequenceNumber, 0, sizeof(self->SequenceNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Set_ResultingNetworkPolicyRule(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self,
    _In_ const CIM_NetworkPolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_SetPtr_ResultingNetworkPolicyRule(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self,
    _In_ const CIM_NetworkPolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Clear_ResultingNetworkPolicyRule(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Set_Job(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_SetPtr_Job(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_NetworkACLService_AddRuleWithMatchedACL_Clear_Job(
    _Inout_ MSFT_NetworkACLService_AddRuleWithMatchedACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

/*
**==============================================================================
**
** MSFT_NetworkACLService provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_NetworkACLService_Self MSFT_NetworkACLService_Self;

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_Load(
    _Outptr_result_maybenull_ MSFT_NetworkACLService_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_Unload(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_EnumerateInstances(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_GetInstance(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_NetworkACLService* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_CreateInstance(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_NetworkACLService* newInstance);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_ModifyInstance(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_NetworkACLService* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_DeleteInstance(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_NetworkACLService* instanceName);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_Invoke_RequestStateChange(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_NetworkACLService* instanceName,
    _In_opt_ const MSFT_NetworkACLService_RequestStateChange* in);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_Invoke_StartService(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_NetworkACLService* instanceName,
    _In_opt_ const MSFT_NetworkACLService_StartService* in);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_Invoke_StopService(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_NetworkACLService* instanceName,
    _In_opt_ const MSFT_NetworkACLService_StopService* in);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_Invoke_CreateACL(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_NetworkACLService* instanceName,
    _In_opt_ const MSFT_NetworkACLService_CreateACL* in);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_Invoke_AddRule(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_NetworkACLService* instanceName,
    _In_opt_ const MSFT_NetworkACLService_AddRule* in);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_Invoke_RemoveACL(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_NetworkACLService* instanceName,
    _In_opt_ const MSFT_NetworkACLService_RemoveACL* in);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_Invoke_RemoveRule(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_NetworkACLService* instanceName,
    _In_opt_ const MSFT_NetworkACLService_RemoveRule* in);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_Invoke_ResequenceRule(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_NetworkACLService* instanceName,
    _In_opt_ const MSFT_NetworkACLService_ResequenceRule* in);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_Invoke_AttachACL(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_NetworkACLService* instanceName,
    _In_opt_ const MSFT_NetworkACLService_AttachACL* in);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_Invoke_AttachVACL(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_NetworkACLService* instanceName,
    _In_opt_ const MSFT_NetworkACLService_AttachVACL* in);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_Invoke_DetachACL(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_NetworkACLService* instanceName,
    _In_opt_ const MSFT_NetworkACLService_DetachACL* in);

MI_EXTERN_C void MI_CALL MSFT_NetworkACLService_Invoke_AddRuleWithMatchedACL(
    _In_opt_ MSFT_NetworkACLService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_NetworkACLService* instanceName,
    _In_opt_ const MSFT_NetworkACLService_AddRuleWithMatchedACL* in);


#endif /* _MSFT_NetworkACLService_h */
