/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_ComputerSystem_h
#define _ABC_ComputerSystem_h

#include <MI.h>
#include "CIM_ComputerSystem.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** ABC_ComputerSystem [ABC_ComputerSystem]
**
** Keys:
**    Name
**    CreationClassName
**
**==============================================================================
*/

typedef struct _ABC_ComputerSystem /* extends CIM_ComputerSystem */
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
    /* CIM_System properties */
    /*KEY*/ MI_ConstStringField CreationClassName;
    MI_ConstStringField NameFormat;
    MI_ConstStringField PrimaryOwnerName;
    MI_ConstStringField PrimaryOwnerContact;
    MI_ConstStringAField Roles;
    MI_ConstStringAField OtherIdentifyingInfo;
    MI_ConstStringAField IdentifyingDescriptions;
    /* CIM_ComputerSystem properties */
    MI_ConstUint16AField Dedicated;
    MI_ConstStringAField OtherDedicatedDescriptions;
    MI_ConstUint16Field ResetCapability;
    MI_ConstUint16AField PowerManagementCapabilities;
    /* ABC_ComputerSystem properties */
}
ABC_ComputerSystem;

typedef struct _ABC_ComputerSystem_Ref
{
    ABC_ComputerSystem* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ComputerSystem_Ref;

typedef struct _ABC_ComputerSystem_ConstRef
{
    MI_CONST ABC_ComputerSystem* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ComputerSystem_ConstRef;

typedef struct _ABC_ComputerSystem_Array
{
    struct _ABC_ComputerSystem** data;
    MI_Uint32 size;
}
ABC_ComputerSystem_Array;

typedef struct _ABC_ComputerSystem_ConstArray
{
    struct _ABC_ComputerSystem MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_ComputerSystem_ConstArray;

typedef struct _ABC_ComputerSystem_ArrayRef
{
    ABC_ComputerSystem_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ComputerSystem_ArrayRef;

typedef struct _ABC_ComputerSystem_ConstArrayRef
{
    ABC_ComputerSystem_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_ComputerSystem_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_ComputerSystem_rtti;

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Construct(
    ABC_ComputerSystem* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_ComputerSystem_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clone(
    const ABC_ComputerSystem* self,
    ABC_ComputerSystem** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_ComputerSystem_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_ComputerSystem_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Destruct(ABC_ComputerSystem* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Delete(ABC_ComputerSystem* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Post(
    const ABC_ComputerSystem* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_InstanceID(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_InstanceID(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_InstanceID(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_Caption(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_Caption(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_Caption(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_Description(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_Description(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_Description(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_ElementName(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_ElementName(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_ElementName(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_InstallDate(
    ABC_ComputerSystem* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_InstallDate(
    ABC_ComputerSystem* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_Name(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_Name(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_Name(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_OperationalStatus(
    ABC_ComputerSystem* self,
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

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_OperationalStatus(
    ABC_ComputerSystem* self,
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

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_OperationalStatus(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_StatusDescriptions(
    ABC_ComputerSystem* self,
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

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_StatusDescriptions(
    ABC_ComputerSystem* self,
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

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_StatusDescriptions(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_Status(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_Status(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_Status(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_HealthState(
    ABC_ComputerSystem* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_HealthState(
    ABC_ComputerSystem* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_CommunicationStatus(
    ABC_ComputerSystem* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_CommunicationStatus(
    ABC_ComputerSystem* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_DetailedStatus(
    ABC_ComputerSystem* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_DetailedStatus(
    ABC_ComputerSystem* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_OperatingStatus(
    ABC_ComputerSystem* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_OperatingStatus(
    ABC_ComputerSystem* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_PrimaryStatus(
    ABC_ComputerSystem* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_PrimaryStatus(
    ABC_ComputerSystem* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_EnabledState(
    ABC_ComputerSystem* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_EnabledState(
    ABC_ComputerSystem* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_OtherEnabledState(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_OtherEnabledState(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_OtherEnabledState(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_RequestedState(
    ABC_ComputerSystem* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_RequestedState(
    ABC_ComputerSystem* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_EnabledDefault(
    ABC_ComputerSystem* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_EnabledDefault(
    ABC_ComputerSystem* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_TimeOfLastStateChange(
    ABC_ComputerSystem* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_TimeOfLastStateChange(
    ABC_ComputerSystem* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_AvailableRequestedStates(
    ABC_ComputerSystem* self,
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

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_AvailableRequestedStates(
    ABC_ComputerSystem* self,
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

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_AvailableRequestedStates(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_TransitioningToState(
    ABC_ComputerSystem* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_TransitioningToState(
    ABC_ComputerSystem* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_CreationClassName(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_CreationClassName(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_CreationClassName(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_NameFormat(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_NameFormat(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_NameFormat(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_PrimaryOwnerName(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_PrimaryOwnerName(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_PrimaryOwnerName(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_PrimaryOwnerContact(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_PrimaryOwnerContact(
    ABC_ComputerSystem* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_PrimaryOwnerContact(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_Roles(
    ABC_ComputerSystem* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_Roles(
    ABC_ComputerSystem* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_Roles(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        25);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_OtherIdentifyingInfo(
    ABC_ComputerSystem* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_OtherIdentifyingInfo(
    ABC_ComputerSystem* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_OtherIdentifyingInfo(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_IdentifyingDescriptions(
    ABC_ComputerSystem* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_IdentifyingDescriptions(
    ABC_ComputerSystem* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_IdentifyingDescriptions(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        27);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_Dedicated(
    ABC_ComputerSystem* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        28,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_Dedicated(
    ABC_ComputerSystem* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        28,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_Dedicated(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        28);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_OtherDedicatedDescriptions(
    ABC_ComputerSystem* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_OtherDedicatedDescriptions(
    ABC_ComputerSystem* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_OtherDedicatedDescriptions(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        29);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_ResetCapability(
    ABC_ComputerSystem* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ResetCapability)->value = x;
    ((MI_Uint16Field*)&self->ResetCapability)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_ResetCapability(
    ABC_ComputerSystem* self)
{
    memset((void*)&self->ResetCapability, 0, sizeof(self->ResetCapability));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Set_PowerManagementCapabilities(
    ABC_ComputerSystem* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        31,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPtr_PowerManagementCapabilities(
    ABC_ComputerSystem* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        31,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_Clear_PowerManagementCapabilities(
    ABC_ComputerSystem* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        31);
}

/*
**==============================================================================
**
** ABC_ComputerSystem.RequestStateChange()
**
**==============================================================================
*/

typedef struct _ABC_ComputerSystem_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
ABC_ComputerSystem_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_ComputerSystem_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_RequestStateChange_Construct(
    ABC_ComputerSystem_RequestStateChange* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_ComputerSystem_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_RequestStateChange_Clone(
    const ABC_ComputerSystem_RequestStateChange* self,
    ABC_ComputerSystem_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_RequestStateChange_Destruct(
    ABC_ComputerSystem_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_RequestStateChange_Delete(
    ABC_ComputerSystem_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_RequestStateChange_Post(
    const ABC_ComputerSystem_RequestStateChange* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_RequestStateChange_Set_MIReturn(
    ABC_ComputerSystem_RequestStateChange* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_RequestStateChange_Clear_MIReturn(
    ABC_ComputerSystem_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_RequestStateChange_Set_RequestedState(
    ABC_ComputerSystem_RequestStateChange* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_RequestStateChange_Clear_RequestedState(
    ABC_ComputerSystem_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_RequestStateChange_Set_Job(
    ABC_ComputerSystem_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_RequestStateChange_SetPtr_Job(
    ABC_ComputerSystem_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_RequestStateChange_Clear_Job(
    ABC_ComputerSystem_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_RequestStateChange_Set_TimeoutPeriod(
    ABC_ComputerSystem_RequestStateChange* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_RequestStateChange_Clear_TimeoutPeriod(
    ABC_ComputerSystem_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_ComputerSystem.SetPowerState()
**
**==============================================================================
*/

typedef struct _ABC_ComputerSystem_SetPowerState
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32Field PowerState;
    /*IN*/ MI_ConstDatetimeField Time;
}
ABC_ComputerSystem_SetPowerState;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_ComputerSystem_SetPowerState_rtti;

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPowerState_Construct(
    ABC_ComputerSystem_SetPowerState* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_ComputerSystem_SetPowerState_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPowerState_Clone(
    const ABC_ComputerSystem_SetPowerState* self,
    ABC_ComputerSystem_SetPowerState** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPowerState_Destruct(
    ABC_ComputerSystem_SetPowerState* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPowerState_Delete(
    ABC_ComputerSystem_SetPowerState* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPowerState_Post(
    const ABC_ComputerSystem_SetPowerState* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPowerState_Set_MIReturn(
    ABC_ComputerSystem_SetPowerState* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPowerState_Clear_MIReturn(
    ABC_ComputerSystem_SetPowerState* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPowerState_Set_PowerState(
    ABC_ComputerSystem_SetPowerState* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->PowerState)->value = x;
    ((MI_Uint32Field*)&self->PowerState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPowerState_Clear_PowerState(
    ABC_ComputerSystem_SetPowerState* self)
{
    memset((void*)&self->PowerState, 0, sizeof(self->PowerState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPowerState_Set_Time(
    ABC_ComputerSystem_SetPowerState* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->Time)->value = x;
    ((MI_DatetimeField*)&self->Time)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_ComputerSystem_SetPowerState_Clear_Time(
    ABC_ComputerSystem_SetPowerState* self)
{
    memset((void*)&self->Time, 0, sizeof(self->Time));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_ComputerSystem provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_ComputerSystem_Self ABC_ComputerSystem_Self;

MI_EXTERN_C void MI_CALL ABC_ComputerSystem_Load(
    ABC_ComputerSystem_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_ComputerSystem_Unload(
    ABC_ComputerSystem_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_ComputerSystem_EnumerateInstances(
    ABC_ComputerSystem_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_ComputerSystem_GetInstance(
    ABC_ComputerSystem_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ComputerSystem* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_ComputerSystem_CreateInstance(
    ABC_ComputerSystem_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ComputerSystem* newInstance);

MI_EXTERN_C void MI_CALL ABC_ComputerSystem_ModifyInstance(
    ABC_ComputerSystem_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ComputerSystem* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_ComputerSystem_DeleteInstance(
    ABC_ComputerSystem_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_ComputerSystem* instanceName);

MI_EXTERN_C void MI_CALL ABC_ComputerSystem_Invoke_RequestStateChange(
    ABC_ComputerSystem_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_ComputerSystem* instanceName,
    const ABC_ComputerSystem_RequestStateChange* in);

MI_EXTERN_C void MI_CALL ABC_ComputerSystem_Invoke_SetPowerState(
    ABC_ComputerSystem_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_ComputerSystem* instanceName,
    const ABC_ComputerSystem_SetPowerState* in);


#endif /* _ABC_ComputerSystem_h */
