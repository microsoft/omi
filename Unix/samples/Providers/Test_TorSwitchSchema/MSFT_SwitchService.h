/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_SwitchService_h
#define _MSFT_SwitchService_h

#include <MI.h>
#include "CIM_Service.h"
#include "CIM_ConcreteJob.h"
#include "CIM_ManagedElement.h"
#include "CIM_ProtocolEndpoint.h"
#include "CIM_SettingData.h"
#include "CIM_ComputerSystem.h"
#include "MSFT_NetworkVLAN.h"
#include "MSFT_LinkAggregation.h"
#include "CIM_EthernetPort.h"

/*
**==============================================================================
**
** MSFT_SwitchService [MSFT_SwitchService]
**
** Keys:
**    Name
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**
**==============================================================================
*/

typedef struct _MSFT_SwitchService /* extends CIM_Service */
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
    /* MSFT_SwitchService properties */
}
MSFT_SwitchService;

typedef struct _MSFT_SwitchService_Ref
{
    MSFT_SwitchService* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_SwitchService_Ref;

typedef struct _MSFT_SwitchService_ConstRef
{
    MI_CONST MSFT_SwitchService* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_SwitchService_ConstRef;

typedef struct _MSFT_SwitchService_Array
{
    struct _MSFT_SwitchService** data;
    MI_Uint32 size;
}
MSFT_SwitchService_Array;

typedef struct _MSFT_SwitchService_ConstArray
{
    struct _MSFT_SwitchService MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_SwitchService_ConstArray;

typedef struct _MSFT_SwitchService_ArrayRef
{
    MSFT_SwitchService_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_SwitchService_ArrayRef;

typedef struct _MSFT_SwitchService_ConstArrayRef
{
    MSFT_SwitchService_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_SwitchService_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_SwitchService_rtti;

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Construct(
    _Out_ MSFT_SwitchService* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_SwitchService_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clone(
    _In_ const MSFT_SwitchService* self,
    _Outptr_ MSFT_SwitchService** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_SwitchService_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_SwitchService_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Destruct(_Inout_ MSFT_SwitchService* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Delete(_Inout_ MSFT_SwitchService* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Post(
    _In_ const MSFT_SwitchService* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_InstanceID(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_SetPtr_InstanceID(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_InstanceID(
    _Inout_ MSFT_SwitchService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_Caption(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_SetPtr_Caption(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_Caption(
    _Inout_ MSFT_SwitchService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_Description(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_SetPtr_Description(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_Description(
    _Inout_ MSFT_SwitchService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_ElementName(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_SetPtr_ElementName(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_ElementName(
    _Inout_ MSFT_SwitchService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_InstallDate(
    _Inout_ MSFT_SwitchService* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_InstallDate(
    _Inout_ MSFT_SwitchService* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_Name(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_SetPtr_Name(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_Name(
    _Inout_ MSFT_SwitchService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_OperationalStatus(
    _Inout_ MSFT_SwitchService* self,
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

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_SetPtr_OperationalStatus(
    _Inout_ MSFT_SwitchService* self,
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

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_OperationalStatus(
    _Inout_ MSFT_SwitchService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_StatusDescriptions(
    _Inout_ MSFT_SwitchService* self,
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

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_SetPtr_StatusDescriptions(
    _Inout_ MSFT_SwitchService* self,
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

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_StatusDescriptions(
    _Inout_ MSFT_SwitchService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_Status(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_SetPtr_Status(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_Status(
    _Inout_ MSFT_SwitchService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_HealthState(
    _Inout_ MSFT_SwitchService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_HealthState(
    _Inout_ MSFT_SwitchService* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_CommunicationStatus(
    _Inout_ MSFT_SwitchService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_CommunicationStatus(
    _Inout_ MSFT_SwitchService* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_DetailedStatus(
    _Inout_ MSFT_SwitchService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_DetailedStatus(
    _Inout_ MSFT_SwitchService* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_OperatingStatus(
    _Inout_ MSFT_SwitchService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_OperatingStatus(
    _Inout_ MSFT_SwitchService* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_PrimaryStatus(
    _Inout_ MSFT_SwitchService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_PrimaryStatus(
    _Inout_ MSFT_SwitchService* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_EnabledState(
    _Inout_ MSFT_SwitchService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_EnabledState(
    _Inout_ MSFT_SwitchService* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_OtherEnabledState(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_SetPtr_OtherEnabledState(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_OtherEnabledState(
    _Inout_ MSFT_SwitchService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_RequestedState(
    _Inout_ MSFT_SwitchService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_RequestedState(
    _Inout_ MSFT_SwitchService* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_EnabledDefault(
    _Inout_ MSFT_SwitchService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_EnabledDefault(
    _Inout_ MSFT_SwitchService* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_TimeOfLastStateChange(
    _Inout_ MSFT_SwitchService* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_TimeOfLastStateChange(
    _Inout_ MSFT_SwitchService* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_AvailableRequestedStates(
    _Inout_ MSFT_SwitchService* self,
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

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_SetPtr_AvailableRequestedStates(
    _Inout_ MSFT_SwitchService* self,
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

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_AvailableRequestedStates(
    _Inout_ MSFT_SwitchService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_TransitioningToState(
    _Inout_ MSFT_SwitchService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_TransitioningToState(
    _Inout_ MSFT_SwitchService* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_SystemCreationClassName(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_SetPtr_SystemCreationClassName(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_SystemCreationClassName(
    _Inout_ MSFT_SwitchService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_SystemName(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_SetPtr_SystemName(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_SystemName(
    _Inout_ MSFT_SwitchService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_CreationClassName(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_SetPtr_CreationClassName(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_CreationClassName(
    _Inout_ MSFT_SwitchService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_PrimaryOwnerName(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_SetPtr_PrimaryOwnerName(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_PrimaryOwnerName(
    _Inout_ MSFT_SwitchService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_PrimaryOwnerContact(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_SetPtr_PrimaryOwnerContact(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_PrimaryOwnerContact(
    _Inout_ MSFT_SwitchService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        25);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_StartMode(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_SetPtr_StartMode(
    _Inout_ MSFT_SwitchService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_StartMode(
    _Inout_ MSFT_SwitchService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Set_Started(
    _Inout_ MSFT_SwitchService* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Started)->value = x;
    ((MI_BooleanField*)&self->Started)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Clear_Started(
    _Inout_ MSFT_SwitchService* self)
{
    memset((void*)&self->Started, 0, sizeof(self->Started));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_SwitchService.RequestStateChange()
**
**==============================================================================
*/

typedef struct _MSFT_SwitchService_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
MSFT_SwitchService_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_SwitchService_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RequestStateChange_Construct(
    _Out_ MSFT_SwitchService_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_SwitchService_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RequestStateChange_Clone(
    _In_ const MSFT_SwitchService_RequestStateChange* self,
    _Outptr_ MSFT_SwitchService_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RequestStateChange_Destruct(
    _Inout_ MSFT_SwitchService_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RequestStateChange_Delete(
    _Inout_ MSFT_SwitchService_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RequestStateChange_Post(
    _In_ const MSFT_SwitchService_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RequestStateChange_Set_MIReturn(
    _Inout_ MSFT_SwitchService_RequestStateChange* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RequestStateChange_Clear_MIReturn(
    _Inout_ MSFT_SwitchService_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RequestStateChange_Set_RequestedState(
    _Inout_ MSFT_SwitchService_RequestStateChange* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RequestStateChange_Clear_RequestedState(
    _Inout_ MSFT_SwitchService_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RequestStateChange_Set_Job(
    _Inout_ MSFT_SwitchService_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RequestStateChange_SetPtr_Job(
    _Inout_ MSFT_SwitchService_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RequestStateChange_Clear_Job(
    _Inout_ MSFT_SwitchService_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RequestStateChange_Set_TimeoutPeriod(
    _Inout_ MSFT_SwitchService_RequestStateChange* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RequestStateChange_Clear_TimeoutPeriod(
    _Inout_ MSFT_SwitchService_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_SwitchService.StartService()
**
**==============================================================================
*/

typedef struct _MSFT_SwitchService_StartService
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MSFT_SwitchService_StartService;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_SwitchService_StartService_rtti;

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_StartService_Construct(
    _Out_ MSFT_SwitchService_StartService* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_SwitchService_StartService_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_StartService_Clone(
    _In_ const MSFT_SwitchService_StartService* self,
    _Outptr_ MSFT_SwitchService_StartService** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_StartService_Destruct(
    _Inout_ MSFT_SwitchService_StartService* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_StartService_Delete(
    _Inout_ MSFT_SwitchService_StartService* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_StartService_Post(
    _In_ const MSFT_SwitchService_StartService* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_StartService_Set_MIReturn(
    _Inout_ MSFT_SwitchService_StartService* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_StartService_Clear_MIReturn(
    _Inout_ MSFT_SwitchService_StartService* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_SwitchService.StopService()
**
**==============================================================================
*/

typedef struct _MSFT_SwitchService_StopService
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
MSFT_SwitchService_StopService;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_SwitchService_StopService_rtti;

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_StopService_Construct(
    _Out_ MSFT_SwitchService_StopService* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_SwitchService_StopService_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_StopService_Clone(
    _In_ const MSFT_SwitchService_StopService* self,
    _Outptr_ MSFT_SwitchService_StopService** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_StopService_Destruct(
    _Inout_ MSFT_SwitchService_StopService* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_StopService_Delete(
    _Inout_ MSFT_SwitchService_StopService* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_StopService_Post(
    _In_ const MSFT_SwitchService_StopService* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_StopService_Set_MIReturn(
    _Inout_ MSFT_SwitchService_StopService* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_StopService_Clear_MIReturn(
    _Inout_ MSFT_SwitchService_StopService* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_SwitchService.AddProtocolEndpoint()
**
**==============================================================================
*/

typedef struct _MSFT_SwitchService_AddProtocolEndpoint
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
CIM_ManagedElement_ConstRef TargetInterface;
CIM_ProtocolEndpoint_ConstArrayRef ProtocolEndpoint;
CIM_SettingData_ConstArrayRef EndPointSettings;
    /*OUT*/ CIM_ProtocolEndpoint_ConstRef ResultingEndpoint;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_SwitchService_AddProtocolEndpoint;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_SwitchService_AddProtocolEndpoint_rtti;

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_Construct(
    _Out_ MSFT_SwitchService_AddProtocolEndpoint* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_SwitchService_AddProtocolEndpoint_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_Clone(
    _In_ const MSFT_SwitchService_AddProtocolEndpoint* self,
    _Outptr_ MSFT_SwitchService_AddProtocolEndpoint** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_Destruct(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_Delete(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_Post(
    _In_ const MSFT_SwitchService_AddProtocolEndpoint* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_Set_MIReturn(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_Clear_MIReturn(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_Set_TargetInterface(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_SetPtr_TargetInterface(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self,
    _In_ const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_Clear_TargetInterface(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_Set_ProtocolEndpoint(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self,
    _In_reads_opt_(size) const CIM_ProtocolEndpoint * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_SetPtr_ProtocolEndpoint(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self,
    _In_reads_opt_(size) const CIM_ProtocolEndpoint * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_Clear_ProtocolEndpoint(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_Set_EndPointSettings(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self,
    _In_reads_opt_(size) const CIM_SettingData * const * data,
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

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_SetPtr_EndPointSettings(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self,
    _In_reads_opt_(size) const CIM_SettingData * const * data,
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

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_Clear_EndPointSettings(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_Set_ResultingEndpoint(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self,
    _In_ const CIM_ProtocolEndpoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_SetPtr_ResultingEndpoint(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self,
    _In_ const CIM_ProtocolEndpoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_Clear_ResultingEndpoint(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_Set_Job(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_SetPtr_Job(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddProtocolEndpoint_Clear_Job(
    _Inout_ MSFT_SwitchService_AddProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

/*
**==============================================================================
**
** MSFT_SwitchService.RemoveProtocolEndpoint()
**
**==============================================================================
*/

typedef struct _MSFT_SwitchService_RemoveProtocolEndpoint
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
CIM_ProtocolEndpoint_ConstRef Endpoint;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_SwitchService_RemoveProtocolEndpoint;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_SwitchService_RemoveProtocolEndpoint_rtti;

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveProtocolEndpoint_Construct(
    _Out_ MSFT_SwitchService_RemoveProtocolEndpoint* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_SwitchService_RemoveProtocolEndpoint_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveProtocolEndpoint_Clone(
    _In_ const MSFT_SwitchService_RemoveProtocolEndpoint* self,
    _Outptr_ MSFT_SwitchService_RemoveProtocolEndpoint** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveProtocolEndpoint_Destruct(
    _Inout_ MSFT_SwitchService_RemoveProtocolEndpoint* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveProtocolEndpoint_Delete(
    _Inout_ MSFT_SwitchService_RemoveProtocolEndpoint* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveProtocolEndpoint_Post(
    _In_ const MSFT_SwitchService_RemoveProtocolEndpoint* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveProtocolEndpoint_Set_MIReturn(
    _Inout_ MSFT_SwitchService_RemoveProtocolEndpoint* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveProtocolEndpoint_Clear_MIReturn(
    _Inout_ MSFT_SwitchService_RemoveProtocolEndpoint* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveProtocolEndpoint_Set_Endpoint(
    _Inout_ MSFT_SwitchService_RemoveProtocolEndpoint* self,
    _In_ const CIM_ProtocolEndpoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveProtocolEndpoint_SetPtr_Endpoint(
    _Inout_ MSFT_SwitchService_RemoveProtocolEndpoint* self,
    _In_ const CIM_ProtocolEndpoint* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveProtocolEndpoint_Clear_Endpoint(
    _Inout_ MSFT_SwitchService_RemoveProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveProtocolEndpoint_Set_Job(
    _Inout_ MSFT_SwitchService_RemoveProtocolEndpoint* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveProtocolEndpoint_SetPtr_Job(
    _Inout_ MSFT_SwitchService_RemoveProtocolEndpoint* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveProtocolEndpoint_Clear_Job(
    _Inout_ MSFT_SwitchService_RemoveProtocolEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** MSFT_SwitchService.AddVLAN()
**
**==============================================================================
*/

typedef struct _MSFT_SwitchService_AddVLAN
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
CIM_ComputerSystem_ConstRef TargetedSwitch;
MSFT_NetworkVLAN_ConstArrayRef NetworkVLAN;
    /*OUT*/ MSFT_NetworkVLAN_ConstArrayRef VLAN;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_SwitchService_AddVLAN;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_SwitchService_AddVLAN_rtti;

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_Construct(
    _Out_ MSFT_SwitchService_AddVLAN* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_SwitchService_AddVLAN_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_Clone(
    _In_ const MSFT_SwitchService_AddVLAN* self,
    _Outptr_ MSFT_SwitchService_AddVLAN** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_Destruct(
    _Inout_ MSFT_SwitchService_AddVLAN* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_Delete(
    _Inout_ MSFT_SwitchService_AddVLAN* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_Post(
    _In_ const MSFT_SwitchService_AddVLAN* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_Set_MIReturn(
    _Inout_ MSFT_SwitchService_AddVLAN* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_Clear_MIReturn(
    _Inout_ MSFT_SwitchService_AddVLAN* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_Set_TargetedSwitch(
    _Inout_ MSFT_SwitchService_AddVLAN* self,
    _In_ const CIM_ComputerSystem* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_SetPtr_TargetedSwitch(
    _Inout_ MSFT_SwitchService_AddVLAN* self,
    _In_ const CIM_ComputerSystem* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_Clear_TargetedSwitch(
    _Inout_ MSFT_SwitchService_AddVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_Set_NetworkVLAN(
    _Inout_ MSFT_SwitchService_AddVLAN* self,
    _In_reads_opt_(size) const MSFT_NetworkVLAN * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_SetPtr_NetworkVLAN(
    _Inout_ MSFT_SwitchService_AddVLAN* self,
    _In_reads_opt_(size) const MSFT_NetworkVLAN * const * data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_Clear_NetworkVLAN(
    _Inout_ MSFT_SwitchService_AddVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_Set_VLAN(
    _Inout_ MSFT_SwitchService_AddVLAN* self,
    _In_reads_opt_(size) const MSFT_NetworkVLAN* const* data,
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

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_SetPtr_VLAN(
    _Inout_ MSFT_SwitchService_AddVLAN* self,
    _In_reads_opt_(size) const MSFT_NetworkVLAN* const* data,
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

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_Clear_VLAN(
    _Inout_ MSFT_SwitchService_AddVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_Set_Job(
    _Inout_ MSFT_SwitchService_AddVLAN* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_SetPtr_Job(
    _Inout_ MSFT_SwitchService_AddVLAN* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddVLAN_Clear_Job(
    _Inout_ MSFT_SwitchService_AddVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** MSFT_SwitchService.RemoveVLAN()
**
**==============================================================================
*/

typedef struct _MSFT_SwitchService_RemoveVLAN
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MSFT_NetworkVLAN_ConstArrayRef VLAN;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_SwitchService_RemoveVLAN;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_SwitchService_RemoveVLAN_rtti;

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveVLAN_Construct(
    _Out_ MSFT_SwitchService_RemoveVLAN* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_SwitchService_RemoveVLAN_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveVLAN_Clone(
    _In_ const MSFT_SwitchService_RemoveVLAN* self,
    _Outptr_ MSFT_SwitchService_RemoveVLAN** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveVLAN_Destruct(
    _Inout_ MSFT_SwitchService_RemoveVLAN* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveVLAN_Delete(
    _Inout_ MSFT_SwitchService_RemoveVLAN* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveVLAN_Post(
    _In_ const MSFT_SwitchService_RemoveVLAN* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveVLAN_Set_MIReturn(
    _Inout_ MSFT_SwitchService_RemoveVLAN* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveVLAN_Clear_MIReturn(
    _Inout_ MSFT_SwitchService_RemoveVLAN* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveVLAN_Set_VLAN(
    _Inout_ MSFT_SwitchService_RemoveVLAN* self,
    _In_reads_opt_(size) const MSFT_NetworkVLAN* const* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveVLAN_SetPtr_VLAN(
    _Inout_ MSFT_SwitchService_RemoveVLAN* self,
    _In_reads_opt_(size) const MSFT_NetworkVLAN* const* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveVLAN_Clear_VLAN(
    _Inout_ MSFT_SwitchService_RemoveVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveVLAN_Set_Job(
    _Inout_ MSFT_SwitchService_RemoveVLAN* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveVLAN_SetPtr_Job(
    _Inout_ MSFT_SwitchService_RemoveVLAN* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveVLAN_Clear_Job(
    _Inout_ MSFT_SwitchService_RemoveVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** MSFT_SwitchService.EnableVLAN()
**
**==============================================================================
*/

typedef struct _MSFT_SwitchService_EnableVLAN
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MSFT_NetworkVLAN_ConstArrayRef VLAN;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_SwitchService_EnableVLAN;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_SwitchService_EnableVLAN_rtti;

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_EnableVLAN_Construct(
    _Out_ MSFT_SwitchService_EnableVLAN* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_SwitchService_EnableVLAN_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_EnableVLAN_Clone(
    _In_ const MSFT_SwitchService_EnableVLAN* self,
    _Outptr_ MSFT_SwitchService_EnableVLAN** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_EnableVLAN_Destruct(
    _Inout_ MSFT_SwitchService_EnableVLAN* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_EnableVLAN_Delete(
    _Inout_ MSFT_SwitchService_EnableVLAN* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_EnableVLAN_Post(
    _In_ const MSFT_SwitchService_EnableVLAN* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_EnableVLAN_Set_MIReturn(
    _Inout_ MSFT_SwitchService_EnableVLAN* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_EnableVLAN_Clear_MIReturn(
    _Inout_ MSFT_SwitchService_EnableVLAN* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_EnableVLAN_Set_VLAN(
    _Inout_ MSFT_SwitchService_EnableVLAN* self,
    _In_reads_opt_(size) const MSFT_NetworkVLAN* const* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_EnableVLAN_SetPtr_VLAN(
    _Inout_ MSFT_SwitchService_EnableVLAN* self,
    _In_reads_opt_(size) const MSFT_NetworkVLAN* const* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_EnableVLAN_Clear_VLAN(
    _Inout_ MSFT_SwitchService_EnableVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_EnableVLAN_Set_Job(
    _Inout_ MSFT_SwitchService_EnableVLAN* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_EnableVLAN_SetPtr_Job(
    _Inout_ MSFT_SwitchService_EnableVLAN* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_EnableVLAN_Clear_Job(
    _Inout_ MSFT_SwitchService_EnableVLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** MSFT_SwitchService.Disable_VLAN()
**
**==============================================================================
*/

typedef struct _MSFT_SwitchService_Disable_VLAN
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MSFT_NetworkVLAN_ConstArrayRef VLAN;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_SwitchService_Disable_VLAN;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_SwitchService_Disable_VLAN_rtti;

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Disable_VLAN_Construct(
    _Out_ MSFT_SwitchService_Disable_VLAN* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_SwitchService_Disable_VLAN_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Disable_VLAN_Clone(
    _In_ const MSFT_SwitchService_Disable_VLAN* self,
    _Outptr_ MSFT_SwitchService_Disable_VLAN** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Disable_VLAN_Destruct(
    _Inout_ MSFT_SwitchService_Disable_VLAN* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Disable_VLAN_Delete(
    _Inout_ MSFT_SwitchService_Disable_VLAN* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Disable_VLAN_Post(
    _In_ const MSFT_SwitchService_Disable_VLAN* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Disable_VLAN_Set_MIReturn(
    _Inout_ MSFT_SwitchService_Disable_VLAN* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Disable_VLAN_Clear_MIReturn(
    _Inout_ MSFT_SwitchService_Disable_VLAN* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Disable_VLAN_Set_VLAN(
    _Inout_ MSFT_SwitchService_Disable_VLAN* self,
    _In_reads_opt_(size) const MSFT_NetworkVLAN* const* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Disable_VLAN_SetPtr_VLAN(
    _Inout_ MSFT_SwitchService_Disable_VLAN* self,
    _In_reads_opt_(size) const MSFT_NetworkVLAN* const* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Disable_VLAN_Clear_VLAN(
    _Inout_ MSFT_SwitchService_Disable_VLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Disable_VLAN_Set_Job(
    _Inout_ MSFT_SwitchService_Disable_VLAN* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Disable_VLAN_SetPtr_Job(
    _Inout_ MSFT_SwitchService_Disable_VLAN* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_Disable_VLAN_Clear_Job(
    _Inout_ MSFT_SwitchService_Disable_VLAN* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** MSFT_SwitchService.CreateLinkAggregation()
**
**==============================================================================
*/

typedef struct _MSFT_SwitchService_CreateLinkAggregation
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MSFT_LinkAggregation_ConstArrayRef LinkAggragation;
CIM_EthernetPort_ConstArrayRef EthernetPort;
    /*OUT*/ MSFT_LinkAggregation_ConstRef ResultingLinkAggregation;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_SwitchService_CreateLinkAggregation;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_SwitchService_CreateLinkAggregation_rtti;

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_Construct(
    _Out_ MSFT_SwitchService_CreateLinkAggregation* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_SwitchService_CreateLinkAggregation_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_Clone(
    _In_ const MSFT_SwitchService_CreateLinkAggregation* self,
    _Outptr_ MSFT_SwitchService_CreateLinkAggregation** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_Destruct(
    _Inout_ MSFT_SwitchService_CreateLinkAggregation* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_Delete(
    _Inout_ MSFT_SwitchService_CreateLinkAggregation* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_Post(
    _In_ const MSFT_SwitchService_CreateLinkAggregation* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_Set_MIReturn(
    _Inout_ MSFT_SwitchService_CreateLinkAggregation* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_Clear_MIReturn(
    _Inout_ MSFT_SwitchService_CreateLinkAggregation* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_Set_LinkAggragation(
    _Inout_ MSFT_SwitchService_CreateLinkAggregation* self,
    _In_reads_opt_(size) const MSFT_LinkAggregation * const * data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_SetPtr_LinkAggragation(
    _Inout_ MSFT_SwitchService_CreateLinkAggregation* self,
    _In_reads_opt_(size) const MSFT_LinkAggregation * const * data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_Clear_LinkAggragation(
    _Inout_ MSFT_SwitchService_CreateLinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_Set_EthernetPort(
    _Inout_ MSFT_SwitchService_CreateLinkAggregation* self,
    _In_reads_opt_(size) const CIM_EthernetPort* const* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_SetPtr_EthernetPort(
    _Inout_ MSFT_SwitchService_CreateLinkAggregation* self,
    _In_reads_opt_(size) const CIM_EthernetPort* const* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_Clear_EthernetPort(
    _Inout_ MSFT_SwitchService_CreateLinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_Set_ResultingLinkAggregation(
    _Inout_ MSFT_SwitchService_CreateLinkAggregation* self,
    _In_ const MSFT_LinkAggregation* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_SetPtr_ResultingLinkAggregation(
    _Inout_ MSFT_SwitchService_CreateLinkAggregation* self,
    _In_ const MSFT_LinkAggregation* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_Clear_ResultingLinkAggregation(
    _Inout_ MSFT_SwitchService_CreateLinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_Set_Job(
    _Inout_ MSFT_SwitchService_CreateLinkAggregation* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_SetPtr_Job(
    _Inout_ MSFT_SwitchService_CreateLinkAggregation* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_CreateLinkAggregation_Clear_Job(
    _Inout_ MSFT_SwitchService_CreateLinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** MSFT_SwitchService.RemoveLinkAggregation()
**
**==============================================================================
*/

typedef struct _MSFT_SwitchService_RemoveLinkAggregation
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MSFT_LinkAggregation_ConstRef LinkAggregation;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_SwitchService_RemoveLinkAggregation;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_SwitchService_RemoveLinkAggregation_rtti;

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveLinkAggregation_Construct(
    _Out_ MSFT_SwitchService_RemoveLinkAggregation* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_SwitchService_RemoveLinkAggregation_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveLinkAggregation_Clone(
    _In_ const MSFT_SwitchService_RemoveLinkAggregation* self,
    _Outptr_ MSFT_SwitchService_RemoveLinkAggregation** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveLinkAggregation_Destruct(
    _Inout_ MSFT_SwitchService_RemoveLinkAggregation* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveLinkAggregation_Delete(
    _Inout_ MSFT_SwitchService_RemoveLinkAggregation* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveLinkAggregation_Post(
    _In_ const MSFT_SwitchService_RemoveLinkAggregation* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveLinkAggregation_Set_MIReturn(
    _Inout_ MSFT_SwitchService_RemoveLinkAggregation* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveLinkAggregation_Clear_MIReturn(
    _Inout_ MSFT_SwitchService_RemoveLinkAggregation* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveLinkAggregation_Set_LinkAggregation(
    _Inout_ MSFT_SwitchService_RemoveLinkAggregation* self,
    _In_ const MSFT_LinkAggregation* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveLinkAggregation_SetPtr_LinkAggregation(
    _Inout_ MSFT_SwitchService_RemoveLinkAggregation* self,
    _In_ const MSFT_LinkAggregation* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveLinkAggregation_Clear_LinkAggregation(
    _Inout_ MSFT_SwitchService_RemoveLinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveLinkAggregation_Set_Job(
    _Inout_ MSFT_SwitchService_RemoveLinkAggregation* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveLinkAggregation_SetPtr_Job(
    _Inout_ MSFT_SwitchService_RemoveLinkAggregation* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveLinkAggregation_Clear_Job(
    _Inout_ MSFT_SwitchService_RemoveLinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** MSFT_SwitchService.AddPortToAggregation()
**
**==============================================================================
*/

typedef struct _MSFT_SwitchService_AddPortToAggregation
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MSFT_LinkAggregation_ConstRef LinkAggregation;
CIM_EthernetPort_ConstArrayRef EthernetPort;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_SwitchService_AddPortToAggregation;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_SwitchService_AddPortToAggregation_rtti;

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddPortToAggregation_Construct(
    _Out_ MSFT_SwitchService_AddPortToAggregation* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_SwitchService_AddPortToAggregation_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddPortToAggregation_Clone(
    _In_ const MSFT_SwitchService_AddPortToAggregation* self,
    _Outptr_ MSFT_SwitchService_AddPortToAggregation** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddPortToAggregation_Destruct(
    _Inout_ MSFT_SwitchService_AddPortToAggregation* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddPortToAggregation_Delete(
    _Inout_ MSFT_SwitchService_AddPortToAggregation* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddPortToAggregation_Post(
    _In_ const MSFT_SwitchService_AddPortToAggregation* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddPortToAggregation_Set_MIReturn(
    _Inout_ MSFT_SwitchService_AddPortToAggregation* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddPortToAggregation_Clear_MIReturn(
    _Inout_ MSFT_SwitchService_AddPortToAggregation* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddPortToAggregation_Set_LinkAggregation(
    _Inout_ MSFT_SwitchService_AddPortToAggregation* self,
    _In_ const MSFT_LinkAggregation* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddPortToAggregation_SetPtr_LinkAggregation(
    _Inout_ MSFT_SwitchService_AddPortToAggregation* self,
    _In_ const MSFT_LinkAggregation* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddPortToAggregation_Clear_LinkAggregation(
    _Inout_ MSFT_SwitchService_AddPortToAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddPortToAggregation_Set_EthernetPort(
    _Inout_ MSFT_SwitchService_AddPortToAggregation* self,
    _In_reads_opt_(size) const CIM_EthernetPort* const* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddPortToAggregation_SetPtr_EthernetPort(
    _Inout_ MSFT_SwitchService_AddPortToAggregation* self,
    _In_reads_opt_(size) const CIM_EthernetPort* const* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddPortToAggregation_Clear_EthernetPort(
    _Inout_ MSFT_SwitchService_AddPortToAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddPortToAggregation_Set_Job(
    _Inout_ MSFT_SwitchService_AddPortToAggregation* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddPortToAggregation_SetPtr_Job(
    _Inout_ MSFT_SwitchService_AddPortToAggregation* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_AddPortToAggregation_Clear_Job(
    _Inout_ MSFT_SwitchService_AddPortToAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

/*
**==============================================================================
**
** MSFT_SwitchService.RemoveportFromLinkAggregation()
**
**==============================================================================
*/

typedef struct _MSFT_SwitchService_RemoveportFromLinkAggregation
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
CIM_EthernetPort_ConstRef EthernetPort;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
MSFT_SwitchService_RemoveportFromLinkAggregation;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_SwitchService_RemoveportFromLinkAggregation_rtti;

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveportFromLinkAggregation_Construct(
    _Out_ MSFT_SwitchService_RemoveportFromLinkAggregation* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_SwitchService_RemoveportFromLinkAggregation_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveportFromLinkAggregation_Clone(
    _In_ const MSFT_SwitchService_RemoveportFromLinkAggregation* self,
    _Outptr_ MSFT_SwitchService_RemoveportFromLinkAggregation** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveportFromLinkAggregation_Destruct(
    _Inout_ MSFT_SwitchService_RemoveportFromLinkAggregation* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveportFromLinkAggregation_Delete(
    _Inout_ MSFT_SwitchService_RemoveportFromLinkAggregation* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveportFromLinkAggregation_Post(
    _In_ const MSFT_SwitchService_RemoveportFromLinkAggregation* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveportFromLinkAggregation_Set_MIReturn(
    _Inout_ MSFT_SwitchService_RemoveportFromLinkAggregation* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveportFromLinkAggregation_Clear_MIReturn(
    _Inout_ MSFT_SwitchService_RemoveportFromLinkAggregation* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveportFromLinkAggregation_Set_EthernetPort(
    _Inout_ MSFT_SwitchService_RemoveportFromLinkAggregation* self,
    _In_ const CIM_EthernetPort* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveportFromLinkAggregation_SetPtr_EthernetPort(
    _Inout_ MSFT_SwitchService_RemoveportFromLinkAggregation* self,
    _In_ const CIM_EthernetPort* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveportFromLinkAggregation_Clear_EthernetPort(
    _Inout_ MSFT_SwitchService_RemoveportFromLinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveportFromLinkAggregation_Set_Job(
    _Inout_ MSFT_SwitchService_RemoveportFromLinkAggregation* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveportFromLinkAggregation_SetPtr_Job(
    _Inout_ MSFT_SwitchService_RemoveportFromLinkAggregation* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SwitchService_RemoveportFromLinkAggregation_Clear_Job(
    _Inout_ MSFT_SwitchService_RemoveportFromLinkAggregation* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** MSFT_SwitchService provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_SwitchService_Self MSFT_SwitchService_Self;

MI_EXTERN_C void MI_CALL MSFT_SwitchService_Load(
    _Outptr_result_maybenull_ MSFT_SwitchService_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_Unload(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_EnumerateInstances(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_GetInstance(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_SwitchService* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_CreateInstance(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_SwitchService* newInstance);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_ModifyInstance(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_SwitchService* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_DeleteInstance(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_SwitchService* instanceName);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_Invoke_RequestStateChange(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_SwitchService* instanceName,
    _In_opt_ const MSFT_SwitchService_RequestStateChange* in);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_Invoke_StartService(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_SwitchService* instanceName,
    _In_opt_ const MSFT_SwitchService_StartService* in);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_Invoke_StopService(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_SwitchService* instanceName,
    _In_opt_ const MSFT_SwitchService_StopService* in);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_Invoke_AddProtocolEndpoint(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_SwitchService* instanceName,
    _In_opt_ const MSFT_SwitchService_AddProtocolEndpoint* in);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_Invoke_RemoveProtocolEndpoint(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_SwitchService* instanceName,
    _In_opt_ const MSFT_SwitchService_RemoveProtocolEndpoint* in);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_Invoke_AddVLAN(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_SwitchService* instanceName,
    _In_opt_ const MSFT_SwitchService_AddVLAN* in);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_Invoke_RemoveVLAN(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_SwitchService* instanceName,
    _In_opt_ const MSFT_SwitchService_RemoveVLAN* in);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_Invoke_EnableVLAN(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_SwitchService* instanceName,
    _In_opt_ const MSFT_SwitchService_EnableVLAN* in);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_Invoke_Disable_VLAN(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_SwitchService* instanceName,
    _In_opt_ const MSFT_SwitchService_Disable_VLAN* in);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_Invoke_CreateLinkAggregation(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_SwitchService* instanceName,
    _In_opt_ const MSFT_SwitchService_CreateLinkAggregation* in);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_Invoke_RemoveLinkAggregation(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_SwitchService* instanceName,
    _In_opt_ const MSFT_SwitchService_RemoveLinkAggregation* in);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_Invoke_AddPortToAggregation(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_SwitchService* instanceName,
    _In_opt_ const MSFT_SwitchService_AddPortToAggregation* in);

MI_EXTERN_C void MI_CALL MSFT_SwitchService_Invoke_RemoveportFromLinkAggregation(
    _In_opt_ MSFT_SwitchService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_SwitchService* instanceName,
    _In_opt_ const MSFT_SwitchService_RemoveportFromLinkAggregation* in);


#endif /* _MSFT_SwitchService_h */
