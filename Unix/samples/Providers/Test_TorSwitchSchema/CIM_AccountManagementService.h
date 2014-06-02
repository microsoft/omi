/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_AccountManagementService_h
#define _CIM_AccountManagementService_h

#include <MI.h>
#include "CIM_IdentityManagementService.h"
#include "CIM_ConcreteJob.h"
#include "CIM_ComputerSystem.h"
#include "CIM_Account.h"
#include "CIM_Identity.h"

/*
**==============================================================================
**
** CIM_AccountManagementService [CIM_AccountManagementService]
**
** Keys:
**    Name
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**
**==============================================================================
*/

typedef struct _CIM_AccountManagementService /* extends CIM_IdentityManagementService */
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
    /* CIM_SecurityService properties */
    /* CIM_AuthenticationService properties */
    /* CIM_IdentityManagementService properties */
    /* CIM_AccountManagementService properties */
}
CIM_AccountManagementService;

typedef struct _CIM_AccountManagementService_Ref
{
    CIM_AccountManagementService* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AccountManagementService_Ref;

typedef struct _CIM_AccountManagementService_ConstRef
{
    MI_CONST CIM_AccountManagementService* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AccountManagementService_ConstRef;

typedef struct _CIM_AccountManagementService_Array
{
    struct _CIM_AccountManagementService** data;
    MI_Uint32 size;
}
CIM_AccountManagementService_Array;

typedef struct _CIM_AccountManagementService_ConstArray
{
    struct _CIM_AccountManagementService MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_AccountManagementService_ConstArray;

typedef struct _CIM_AccountManagementService_ArrayRef
{
    CIM_AccountManagementService_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AccountManagementService_ArrayRef;

typedef struct _CIM_AccountManagementService_ConstArrayRef
{
    CIM_AccountManagementService_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AccountManagementService_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_AccountManagementService_rtti;

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Construct(
    _Out_ CIM_AccountManagementService* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_AccountManagementService_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clone(
    _In_ const CIM_AccountManagementService* self,
    _Outptr_ CIM_AccountManagementService** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_AccountManagementService_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_AccountManagementService_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Destruct(_Inout_ CIM_AccountManagementService* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Delete(_Inout_ CIM_AccountManagementService* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Post(
    _In_ const CIM_AccountManagementService* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_InstanceID(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_SetPtr_InstanceID(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_InstanceID(
    _Inout_ CIM_AccountManagementService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_Caption(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_SetPtr_Caption(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_Caption(
    _Inout_ CIM_AccountManagementService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_Description(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_SetPtr_Description(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_Description(
    _Inout_ CIM_AccountManagementService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_ElementName(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_SetPtr_ElementName(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_ElementName(
    _Inout_ CIM_AccountManagementService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_InstallDate(
    _Inout_ CIM_AccountManagementService* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_InstallDate(
    _Inout_ CIM_AccountManagementService* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_Name(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_SetPtr_Name(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_Name(
    _Inout_ CIM_AccountManagementService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_OperationalStatus(
    _Inout_ CIM_AccountManagementService* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_SetPtr_OperationalStatus(
    _Inout_ CIM_AccountManagementService* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_OperationalStatus(
    _Inout_ CIM_AccountManagementService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_StatusDescriptions(
    _Inout_ CIM_AccountManagementService* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_SetPtr_StatusDescriptions(
    _Inout_ CIM_AccountManagementService* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_StatusDescriptions(
    _Inout_ CIM_AccountManagementService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_Status(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_SetPtr_Status(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_Status(
    _Inout_ CIM_AccountManagementService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_HealthState(
    _Inout_ CIM_AccountManagementService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_HealthState(
    _Inout_ CIM_AccountManagementService* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_CommunicationStatus(
    _Inout_ CIM_AccountManagementService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_CommunicationStatus(
    _Inout_ CIM_AccountManagementService* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_DetailedStatus(
    _Inout_ CIM_AccountManagementService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_DetailedStatus(
    _Inout_ CIM_AccountManagementService* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_OperatingStatus(
    _Inout_ CIM_AccountManagementService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_OperatingStatus(
    _Inout_ CIM_AccountManagementService* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_PrimaryStatus(
    _Inout_ CIM_AccountManagementService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_PrimaryStatus(
    _Inout_ CIM_AccountManagementService* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_EnabledState(
    _Inout_ CIM_AccountManagementService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_EnabledState(
    _Inout_ CIM_AccountManagementService* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_OtherEnabledState(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_SetPtr_OtherEnabledState(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_OtherEnabledState(
    _Inout_ CIM_AccountManagementService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_RequestedState(
    _Inout_ CIM_AccountManagementService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_RequestedState(
    _Inout_ CIM_AccountManagementService* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_EnabledDefault(
    _Inout_ CIM_AccountManagementService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_EnabledDefault(
    _Inout_ CIM_AccountManagementService* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_TimeOfLastStateChange(
    _Inout_ CIM_AccountManagementService* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_TimeOfLastStateChange(
    _Inout_ CIM_AccountManagementService* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_AvailableRequestedStates(
    _Inout_ CIM_AccountManagementService* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_SetPtr_AvailableRequestedStates(
    _Inout_ CIM_AccountManagementService* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_AvailableRequestedStates(
    _Inout_ CIM_AccountManagementService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_TransitioningToState(
    _Inout_ CIM_AccountManagementService* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_TransitioningToState(
    _Inout_ CIM_AccountManagementService* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_SystemCreationClassName(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_SetPtr_SystemCreationClassName(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_SystemCreationClassName(
    _Inout_ CIM_AccountManagementService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_SystemName(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_SetPtr_SystemName(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_SystemName(
    _Inout_ CIM_AccountManagementService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_CreationClassName(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_SetPtr_CreationClassName(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_CreationClassName(
    _Inout_ CIM_AccountManagementService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_PrimaryOwnerName(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_SetPtr_PrimaryOwnerName(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_PrimaryOwnerName(
    _Inout_ CIM_AccountManagementService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_PrimaryOwnerContact(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_SetPtr_PrimaryOwnerContact(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_PrimaryOwnerContact(
    _Inout_ CIM_AccountManagementService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        25);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_StartMode(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_SetPtr_StartMode(
    _Inout_ CIM_AccountManagementService* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_StartMode(
    _Inout_ CIM_AccountManagementService* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Set_Started(
    _Inout_ CIM_AccountManagementService* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Started)->value = x;
    ((MI_BooleanField*)&self->Started)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_Clear_Started(
    _Inout_ CIM_AccountManagementService* self)
{
    memset((void*)&self->Started, 0, sizeof(self->Started));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_AccountManagementService.RequestStateChange()
**
**==============================================================================
*/

typedef struct _CIM_AccountManagementService_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
CIM_AccountManagementService_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_AccountManagementService_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_RequestStateChange_Construct(
    _Out_ CIM_AccountManagementService_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_AccountManagementService_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_RequestStateChange_Clone(
    _In_ const CIM_AccountManagementService_RequestStateChange* self,
    _Outptr_ CIM_AccountManagementService_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_RequestStateChange_Destruct(
    _Inout_ CIM_AccountManagementService_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_RequestStateChange_Delete(
    _Inout_ CIM_AccountManagementService_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_RequestStateChange_Post(
    _In_ const CIM_AccountManagementService_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_RequestStateChange_Set_MIReturn(
    _Inout_ CIM_AccountManagementService_RequestStateChange* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_RequestStateChange_Clear_MIReturn(
    _Inout_ CIM_AccountManagementService_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_RequestStateChange_Set_RequestedState(
    _Inout_ CIM_AccountManagementService_RequestStateChange* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_RequestStateChange_Clear_RequestedState(
    _Inout_ CIM_AccountManagementService_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_RequestStateChange_Set_Job(
    _Inout_ CIM_AccountManagementService_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_RequestStateChange_SetPtr_Job(
    _Inout_ CIM_AccountManagementService_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_RequestStateChange_Clear_Job(
    _Inout_ CIM_AccountManagementService_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_RequestStateChange_Set_TimeoutPeriod(
    _Inout_ CIM_AccountManagementService_RequestStateChange* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_RequestStateChange_Clear_TimeoutPeriod(
    _Inout_ CIM_AccountManagementService_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_AccountManagementService.StartService()
**
**==============================================================================
*/

typedef struct _CIM_AccountManagementService_StartService
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
CIM_AccountManagementService_StartService;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_AccountManagementService_StartService_rtti;

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_StartService_Construct(
    _Out_ CIM_AccountManagementService_StartService* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_AccountManagementService_StartService_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_StartService_Clone(
    _In_ const CIM_AccountManagementService_StartService* self,
    _Outptr_ CIM_AccountManagementService_StartService** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_StartService_Destruct(
    _Inout_ CIM_AccountManagementService_StartService* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_StartService_Delete(
    _Inout_ CIM_AccountManagementService_StartService* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_StartService_Post(
    _In_ const CIM_AccountManagementService_StartService* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_StartService_Set_MIReturn(
    _Inout_ CIM_AccountManagementService_StartService* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_StartService_Clear_MIReturn(
    _Inout_ CIM_AccountManagementService_StartService* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_AccountManagementService.StopService()
**
**==============================================================================
*/

typedef struct _CIM_AccountManagementService_StopService
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
CIM_AccountManagementService_StopService;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_AccountManagementService_StopService_rtti;

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_StopService_Construct(
    _Out_ CIM_AccountManagementService_StopService* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_AccountManagementService_StopService_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_StopService_Clone(
    _In_ const CIM_AccountManagementService_StopService* self,
    _Outptr_ CIM_AccountManagementService_StopService** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_StopService_Destruct(
    _Inout_ CIM_AccountManagementService_StopService* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_StopService_Delete(
    _Inout_ CIM_AccountManagementService_StopService* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_StopService_Post(
    _In_ const CIM_AccountManagementService_StopService* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_StopService_Set_MIReturn(
    _Inout_ CIM_AccountManagementService_StopService* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_StopService_Clear_MIReturn(
    _Inout_ CIM_AccountManagementService_StopService* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_AccountManagementService.CreateAccount()
**
**==============================================================================
*/

typedef struct _CIM_AccountManagementService_CreateAccount
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ CIM_ComputerSystem_ConstRef System;
    /*IN*/ CIM_Account_ConstRef AccountTemplate;
    /*OUT*/ CIM_Account_ConstRef Account;
    /*OUT*/ CIM_Identity_ConstArrayRef Identities;
}
CIM_AccountManagementService_CreateAccount;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_AccountManagementService_CreateAccount_rtti;

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_Construct(
    _Out_ CIM_AccountManagementService_CreateAccount* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_AccountManagementService_CreateAccount_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_Clone(
    _In_ const CIM_AccountManagementService_CreateAccount* self,
    _Outptr_ CIM_AccountManagementService_CreateAccount** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_Destruct(
    _Inout_ CIM_AccountManagementService_CreateAccount* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_Delete(
    _Inout_ CIM_AccountManagementService_CreateAccount* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_Post(
    _In_ const CIM_AccountManagementService_CreateAccount* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_Set_MIReturn(
    _Inout_ CIM_AccountManagementService_CreateAccount* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_Clear_MIReturn(
    _Inout_ CIM_AccountManagementService_CreateAccount* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_Set_System(
    _Inout_ CIM_AccountManagementService_CreateAccount* self,
    _In_ const CIM_ComputerSystem* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_SetPtr_System(
    _Inout_ CIM_AccountManagementService_CreateAccount* self,
    _In_ const CIM_ComputerSystem* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_Clear_System(
    _Inout_ CIM_AccountManagementService_CreateAccount* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_Set_AccountTemplate(
    _Inout_ CIM_AccountManagementService_CreateAccount* self,
    _In_ const CIM_Account* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_SetPtr_AccountTemplate(
    _Inout_ CIM_AccountManagementService_CreateAccount* self,
    _In_ const CIM_Account* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_Clear_AccountTemplate(
    _Inout_ CIM_AccountManagementService_CreateAccount* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_Set_Account(
    _Inout_ CIM_AccountManagementService_CreateAccount* self,
    _In_ const CIM_Account* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_SetPtr_Account(
    _Inout_ CIM_AccountManagementService_CreateAccount* self,
    _In_ const CIM_Account* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_Clear_Account(
    _Inout_ CIM_AccountManagementService_CreateAccount* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_Set_Identities(
    _Inout_ CIM_AccountManagementService_CreateAccount* self,
    _In_reads_opt_(size) const CIM_Identity* const* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_SetPtr_Identities(
    _Inout_ CIM_AccountManagementService_CreateAccount* self,
    _In_reads_opt_(size) const CIM_Identity* const* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementService_CreateAccount_Clear_Identities(
    _Inout_ CIM_AccountManagementService_CreateAccount* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** CIM_AccountManagementService provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_AccountManagementService_Self CIM_AccountManagementService_Self;

MI_EXTERN_C void MI_CALL CIM_AccountManagementService_Load(
    _Outptr_result_maybenull_ CIM_AccountManagementService_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_AccountManagementService_Unload(
    _In_opt_ CIM_AccountManagementService_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_AccountManagementService_EnumerateInstances(
    _In_opt_ CIM_AccountManagementService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_AccountManagementService_GetInstance(
    _In_opt_ CIM_AccountManagementService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AccountManagementService* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_AccountManagementService_CreateInstance(
    _In_opt_ CIM_AccountManagementService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AccountManagementService* newInstance);

MI_EXTERN_C void MI_CALL CIM_AccountManagementService_ModifyInstance(
    _In_opt_ CIM_AccountManagementService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AccountManagementService* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_AccountManagementService_DeleteInstance(
    _In_opt_ CIM_AccountManagementService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AccountManagementService* instanceName);

MI_EXTERN_C void MI_CALL CIM_AccountManagementService_Invoke_RequestStateChange(
    _In_opt_ CIM_AccountManagementService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_AccountManagementService* instanceName,
    _In_opt_ const CIM_AccountManagementService_RequestStateChange* in);

MI_EXTERN_C void MI_CALL CIM_AccountManagementService_Invoke_StartService(
    _In_opt_ CIM_AccountManagementService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_AccountManagementService* instanceName,
    _In_opt_ const CIM_AccountManagementService_StartService* in);

MI_EXTERN_C void MI_CALL CIM_AccountManagementService_Invoke_StopService(
    _In_opt_ CIM_AccountManagementService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_AccountManagementService* instanceName,
    _In_opt_ const CIM_AccountManagementService_StopService* in);

MI_EXTERN_C void MI_CALL CIM_AccountManagementService_Invoke_CreateAccount(
    _In_opt_ CIM_AccountManagementService_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_AccountManagementService* instanceName,
    _In_opt_ const CIM_AccountManagementService_CreateAccount* in);


#endif /* _CIM_AccountManagementService_h */
