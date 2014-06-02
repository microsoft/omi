/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_Process_h
#define _ABC_Process_h

#include <MI.h>
#include "CIM_Process.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** ABC_Process [ABC_Process]
**
** Keys:
**    CSCreationClassName
**    CSName
**    OSCreationClassName
**    OSName
**    CreationClassName
**    Handle
**
**==============================================================================
*/

typedef struct _ABC_Process /* extends CIM_Process */
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
    /* CIM_Process properties */
    /*KEY*/ MI_ConstStringField CSCreationClassName;
    /*KEY*/ MI_ConstStringField CSName;
    /*KEY*/ MI_ConstStringField OSCreationClassName;
    /*KEY*/ MI_ConstStringField OSName;
    /*KEY*/ MI_ConstStringField CreationClassName;
    /*KEY*/ MI_ConstStringField Handle;
    MI_ConstUint32Field Priority;
    MI_ConstUint16Field ExecutionState;
    MI_ConstStringField OtherExecutionDescription;
    MI_ConstDatetimeField CreationDate;
    MI_ConstDatetimeField TerminationDate;
    MI_ConstUint64Field KernelModeTime;
    MI_ConstUint64Field UserModeTime;
    MI_ConstUint64Field WorkingSetSize;
    /* ABC_Process properties */
    MI_ConstUint32Field runningTime;
}
ABC_Process;

typedef struct _ABC_Process_Ref
{
    ABC_Process* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Process_Ref;

typedef struct _ABC_Process_ConstRef
{
    MI_CONST ABC_Process* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Process_ConstRef;

typedef struct _ABC_Process_Array
{
    struct _ABC_Process** data;
    MI_Uint32 size;
}
ABC_Process_Array;

typedef struct _ABC_Process_ConstArray
{
    struct _ABC_Process MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_Process_ConstArray;

typedef struct _ABC_Process_ArrayRef
{
    ABC_Process_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Process_ArrayRef;

typedef struct _ABC_Process_ConstArrayRef
{
    ABC_Process_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_Process_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_Process_rtti;

MI_INLINE MI_Result MI_CALL ABC_Process_Construct(
    ABC_Process* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_Process_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clone(
    const ABC_Process* self,
    ABC_Process** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_Process_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_Process_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Destruct(ABC_Process* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Delete(ABC_Process* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Post(
    const ABC_Process* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_InstanceID(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_SetPtr_InstanceID(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_InstanceID(
    ABC_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_Caption(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_SetPtr_Caption(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_Caption(
    ABC_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_Description(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_SetPtr_Description(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_Description(
    ABC_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_ElementName(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_SetPtr_ElementName(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_ElementName(
    ABC_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_InstallDate(
    ABC_Process* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_InstallDate(
    ABC_Process* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_Name(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_SetPtr_Name(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_Name(
    ABC_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_OperationalStatus(
    ABC_Process* self,
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

MI_INLINE MI_Result MI_CALL ABC_Process_SetPtr_OperationalStatus(
    ABC_Process* self,
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

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_OperationalStatus(
    ABC_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_StatusDescriptions(
    ABC_Process* self,
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

MI_INLINE MI_Result MI_CALL ABC_Process_SetPtr_StatusDescriptions(
    ABC_Process* self,
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

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_StatusDescriptions(
    ABC_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_Status(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_SetPtr_Status(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_Status(
    ABC_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_HealthState(
    ABC_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_HealthState(
    ABC_Process* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_CommunicationStatus(
    ABC_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_CommunicationStatus(
    ABC_Process* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_DetailedStatus(
    ABC_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_DetailedStatus(
    ABC_Process* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_OperatingStatus(
    ABC_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_OperatingStatus(
    ABC_Process* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_PrimaryStatus(
    ABC_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_PrimaryStatus(
    ABC_Process* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_EnabledState(
    ABC_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_EnabledState(
    ABC_Process* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_OtherEnabledState(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_SetPtr_OtherEnabledState(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_OtherEnabledState(
    ABC_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_RequestedState(
    ABC_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_RequestedState(
    ABC_Process* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_EnabledDefault(
    ABC_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_EnabledDefault(
    ABC_Process* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_TimeOfLastStateChange(
    ABC_Process* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_TimeOfLastStateChange(
    ABC_Process* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_AvailableRequestedStates(
    ABC_Process* self,
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

MI_INLINE MI_Result MI_CALL ABC_Process_SetPtr_AvailableRequestedStates(
    ABC_Process* self,
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

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_AvailableRequestedStates(
    ABC_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_TransitioningToState(
    ABC_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_TransitioningToState(
    ABC_Process* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_CSCreationClassName(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_SetPtr_CSCreationClassName(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_CSCreationClassName(
    ABC_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_CSName(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_SetPtr_CSName(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_CSName(
    ABC_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_OSCreationClassName(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_SetPtr_OSCreationClassName(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_OSCreationClassName(
    ABC_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_OSName(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_SetPtr_OSName(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_OSName(
    ABC_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_CreationClassName(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_SetPtr_CreationClassName(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_CreationClassName(
    ABC_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        25);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_Handle(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_SetPtr_Handle(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_Handle(
    ABC_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_Priority(
    ABC_Process* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Priority)->value = x;
    ((MI_Uint32Field*)&self->Priority)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_Priority(
    ABC_Process* self)
{
    memset((void*)&self->Priority, 0, sizeof(self->Priority));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_ExecutionState(
    ABC_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ExecutionState)->value = x;
    ((MI_Uint16Field*)&self->ExecutionState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_ExecutionState(
    ABC_Process* self)
{
    memset((void*)&self->ExecutionState, 0, sizeof(self->ExecutionState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_OtherExecutionDescription(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_SetPtr_OtherExecutionDescription(
    ABC_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_OtherExecutionDescription(
    ABC_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        29);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_CreationDate(
    ABC_Process* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->CreationDate)->value = x;
    ((MI_DatetimeField*)&self->CreationDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_CreationDate(
    ABC_Process* self)
{
    memset((void*)&self->CreationDate, 0, sizeof(self->CreationDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_TerminationDate(
    ABC_Process* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TerminationDate)->value = x;
    ((MI_DatetimeField*)&self->TerminationDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_TerminationDate(
    ABC_Process* self)
{
    memset((void*)&self->TerminationDate, 0, sizeof(self->TerminationDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_KernelModeTime(
    ABC_Process* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->KernelModeTime)->value = x;
    ((MI_Uint64Field*)&self->KernelModeTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_KernelModeTime(
    ABC_Process* self)
{
    memset((void*)&self->KernelModeTime, 0, sizeof(self->KernelModeTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_UserModeTime(
    ABC_Process* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->UserModeTime)->value = x;
    ((MI_Uint64Field*)&self->UserModeTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_UserModeTime(
    ABC_Process* self)
{
    memset((void*)&self->UserModeTime, 0, sizeof(self->UserModeTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_WorkingSetSize(
    ABC_Process* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->WorkingSetSize)->value = x;
    ((MI_Uint64Field*)&self->WorkingSetSize)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_WorkingSetSize(
    ABC_Process* self)
{
    memset((void*)&self->WorkingSetSize, 0, sizeof(self->WorkingSetSize));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Set_runningTime(
    ABC_Process* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->runningTime)->value = x;
    ((MI_Uint32Field*)&self->runningTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Clear_runningTime(
    ABC_Process* self)
{
    memset((void*)&self->runningTime, 0, sizeof(self->runningTime));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Process.RequestStateChange()
**
**==============================================================================
*/

typedef struct _ABC_Process_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
ABC_Process_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Process_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL ABC_Process_RequestStateChange_Construct(
    ABC_Process_RequestStateChange* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Process_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Process_RequestStateChange_Clone(
    const ABC_Process_RequestStateChange* self,
    ABC_Process_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Process_RequestStateChange_Destruct(
    ABC_Process_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Process_RequestStateChange_Delete(
    ABC_Process_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Process_RequestStateChange_Post(
    const ABC_Process_RequestStateChange* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Process_RequestStateChange_Set_MIReturn(
    ABC_Process_RequestStateChange* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_RequestStateChange_Clear_MIReturn(
    ABC_Process_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_RequestStateChange_Set_RequestedState(
    ABC_Process_RequestStateChange* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_RequestStateChange_Clear_RequestedState(
    ABC_Process_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_RequestStateChange_Set_Job(
    ABC_Process_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_RequestStateChange_SetPtr_Job(
    ABC_Process_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Process_RequestStateChange_Clear_Job(
    ABC_Process_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_Process_RequestStateChange_Set_TimeoutPeriod(
    ABC_Process_RequestStateChange* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_RequestStateChange_Clear_TimeoutPeriod(
    ABC_Process_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_Process.Create()
**
**==============================================================================
*/

typedef struct _ABC_Process_Create
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstStringField imageName;
    /*OUT*/ CIM_Process_ConstRef process;
}
ABC_Process_Create;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_Process_Create_rtti;

MI_INLINE MI_Result MI_CALL ABC_Process_Create_Construct(
    ABC_Process_Create* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_Process_Create_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Create_Clone(
    const ABC_Process_Create* self,
    ABC_Process_Create** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Create_Destruct(
    ABC_Process_Create* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Create_Delete(
    ABC_Process_Create* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Create_Post(
    const ABC_Process_Create* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Create_Set_MIReturn(
    ABC_Process_Create* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Create_Clear_MIReturn(
    ABC_Process_Create* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_Process_Create_Set_imageName(
    ABC_Process_Create* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Create_SetPtr_imageName(
    ABC_Process_Create* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Create_Clear_imageName(
    ABC_Process_Create* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Create_Set_process(
    ABC_Process_Create* self,
    const CIM_Process* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Create_SetPtr_process(
    ABC_Process_Create* self,
    const CIM_Process* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_Process_Create_Clear_process(
    ABC_Process_Create* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** ABC_Process provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_Process_Self ABC_Process_Self;

MI_EXTERN_C void MI_CALL ABC_Process_Load(
    ABC_Process_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_Process_Unload(
    ABC_Process_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_Process_EnumerateInstances(
    ABC_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_Process_GetInstance(
    ABC_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Process* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_Process_CreateInstance(
    ABC_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Process* newInstance);

MI_EXTERN_C void MI_CALL ABC_Process_ModifyInstance(
    ABC_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Process* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_Process_DeleteInstance(
    ABC_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_Process* instanceName);

MI_EXTERN_C void MI_CALL ABC_Process_Invoke_RequestStateChange(
    ABC_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Process* instanceName,
    const ABC_Process_RequestStateChange* in);

MI_EXTERN_C void MI_CALL ABC_Process_Invoke_Create(
    ABC_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_Process* instanceName,
    const ABC_Process_Create* in);


#endif /* _ABC_Process_h */
