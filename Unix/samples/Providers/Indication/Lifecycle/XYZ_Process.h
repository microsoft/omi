/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _XYZ_Process_h
#define _XYZ_Process_h

#include <MI.h>
#include "CIM_Process.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** XYZ_Process [XYZ_Process]
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

typedef struct _XYZ_Process /* extends CIM_Process */
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
    /* XYZ_Process properties */
    MI_ConstUint32Field runningTime;
}
XYZ_Process;

typedef struct _XYZ_Process_Ref
{
    XYZ_Process* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Process_Ref;

typedef struct _XYZ_Process_ConstRef
{
    MI_CONST XYZ_Process* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Process_ConstRef;

typedef struct _XYZ_Process_Array
{
    struct _XYZ_Process** data;
    MI_Uint32 size;
}
XYZ_Process_Array;

typedef struct _XYZ_Process_ConstArray
{
    struct _XYZ_Process MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
XYZ_Process_ConstArray;

typedef struct _XYZ_Process_ArrayRef
{
    XYZ_Process_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Process_ArrayRef;

typedef struct _XYZ_Process_ConstArrayRef
{
    XYZ_Process_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
XYZ_Process_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl XYZ_Process_rtti;

MI_INLINE MI_Result MI_CALL XYZ_Process_Construct(
    XYZ_Process* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &XYZ_Process_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clone(
    const XYZ_Process* self,
    XYZ_Process** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL XYZ_Process_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &XYZ_Process_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Destruct(XYZ_Process* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Delete(XYZ_Process* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Post(
    const XYZ_Process* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_InstanceID(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_SetPtr_InstanceID(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_InstanceID(
    XYZ_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_Caption(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_SetPtr_Caption(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_Caption(
    XYZ_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_Description(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_SetPtr_Description(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_Description(
    XYZ_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_ElementName(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_SetPtr_ElementName(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_ElementName(
    XYZ_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_InstallDate(
    XYZ_Process* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_InstallDate(
    XYZ_Process* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_Name(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_SetPtr_Name(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_Name(
    XYZ_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_OperationalStatus(
    XYZ_Process* self,
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

MI_INLINE MI_Result MI_CALL XYZ_Process_SetPtr_OperationalStatus(
    XYZ_Process* self,
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

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_OperationalStatus(
    XYZ_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_StatusDescriptions(
    XYZ_Process* self,
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

MI_INLINE MI_Result MI_CALL XYZ_Process_SetPtr_StatusDescriptions(
    XYZ_Process* self,
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

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_StatusDescriptions(
    XYZ_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_Status(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_SetPtr_Status(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_Status(
    XYZ_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_HealthState(
    XYZ_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_HealthState(
    XYZ_Process* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_CommunicationStatus(
    XYZ_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_CommunicationStatus(
    XYZ_Process* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_DetailedStatus(
    XYZ_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_DetailedStatus(
    XYZ_Process* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_OperatingStatus(
    XYZ_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_OperatingStatus(
    XYZ_Process* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_PrimaryStatus(
    XYZ_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_PrimaryStatus(
    XYZ_Process* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_EnabledState(
    XYZ_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_EnabledState(
    XYZ_Process* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_OtherEnabledState(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_SetPtr_OtherEnabledState(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_OtherEnabledState(
    XYZ_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_RequestedState(
    XYZ_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_RequestedState(
    XYZ_Process* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_EnabledDefault(
    XYZ_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_EnabledDefault(
    XYZ_Process* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_TimeOfLastStateChange(
    XYZ_Process* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_TimeOfLastStateChange(
    XYZ_Process* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_AvailableRequestedStates(
    XYZ_Process* self,
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

MI_INLINE MI_Result MI_CALL XYZ_Process_SetPtr_AvailableRequestedStates(
    XYZ_Process* self,
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

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_AvailableRequestedStates(
    XYZ_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_TransitioningToState(
    XYZ_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_TransitioningToState(
    XYZ_Process* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_CSCreationClassName(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_SetPtr_CSCreationClassName(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_CSCreationClassName(
    XYZ_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_CSName(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_SetPtr_CSName(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_CSName(
    XYZ_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_OSCreationClassName(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_SetPtr_OSCreationClassName(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_OSCreationClassName(
    XYZ_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_OSName(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_SetPtr_OSName(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_OSName(
    XYZ_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_CreationClassName(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_SetPtr_CreationClassName(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_CreationClassName(
    XYZ_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        25);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_Handle(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_SetPtr_Handle(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_Handle(
    XYZ_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_Priority(
    XYZ_Process* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Priority)->value = x;
    ((MI_Uint32Field*)&self->Priority)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_Priority(
    XYZ_Process* self)
{
    memset((void*)&self->Priority, 0, sizeof(self->Priority));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_ExecutionState(
    XYZ_Process* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ExecutionState)->value = x;
    ((MI_Uint16Field*)&self->ExecutionState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_ExecutionState(
    XYZ_Process* self)
{
    memset((void*)&self->ExecutionState, 0, sizeof(self->ExecutionState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_OtherExecutionDescription(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_SetPtr_OtherExecutionDescription(
    XYZ_Process* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_OtherExecutionDescription(
    XYZ_Process* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        29);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_CreationDate(
    XYZ_Process* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->CreationDate)->value = x;
    ((MI_DatetimeField*)&self->CreationDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_CreationDate(
    XYZ_Process* self)
{
    memset((void*)&self->CreationDate, 0, sizeof(self->CreationDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_TerminationDate(
    XYZ_Process* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TerminationDate)->value = x;
    ((MI_DatetimeField*)&self->TerminationDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_TerminationDate(
    XYZ_Process* self)
{
    memset((void*)&self->TerminationDate, 0, sizeof(self->TerminationDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_KernelModeTime(
    XYZ_Process* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->KernelModeTime)->value = x;
    ((MI_Uint64Field*)&self->KernelModeTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_KernelModeTime(
    XYZ_Process* self)
{
    memset((void*)&self->KernelModeTime, 0, sizeof(self->KernelModeTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_UserModeTime(
    XYZ_Process* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->UserModeTime)->value = x;
    ((MI_Uint64Field*)&self->UserModeTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_UserModeTime(
    XYZ_Process* self)
{
    memset((void*)&self->UserModeTime, 0, sizeof(self->UserModeTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_WorkingSetSize(
    XYZ_Process* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->WorkingSetSize)->value = x;
    ((MI_Uint64Field*)&self->WorkingSetSize)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_WorkingSetSize(
    XYZ_Process* self)
{
    memset((void*)&self->WorkingSetSize, 0, sizeof(self->WorkingSetSize));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Set_runningTime(
    XYZ_Process* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->runningTime)->value = x;
    ((MI_Uint32Field*)&self->runningTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Clear_runningTime(
    XYZ_Process* self)
{
    memset((void*)&self->runningTime, 0, sizeof(self->runningTime));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** XYZ_Process.RequestStateChange()
**
**==============================================================================
*/

typedef struct _XYZ_Process_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
XYZ_Process_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl XYZ_Process_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL XYZ_Process_RequestStateChange_Construct(
    XYZ_Process_RequestStateChange* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &XYZ_Process_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_RequestStateChange_Clone(
    const XYZ_Process_RequestStateChange* self,
    XYZ_Process_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_RequestStateChange_Destruct(
    XYZ_Process_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_RequestStateChange_Delete(
    XYZ_Process_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_RequestStateChange_Post(
    const XYZ_Process_RequestStateChange* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_RequestStateChange_Set_MIReturn(
    XYZ_Process_RequestStateChange* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_RequestStateChange_Clear_MIReturn(
    XYZ_Process_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_RequestStateChange_Set_RequestedState(
    XYZ_Process_RequestStateChange* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_RequestStateChange_Clear_RequestedState(
    XYZ_Process_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_RequestStateChange_Set_Job(
    XYZ_Process_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_RequestStateChange_SetPtr_Job(
    XYZ_Process_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_RequestStateChange_Clear_Job(
    XYZ_Process_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_RequestStateChange_Set_TimeoutPeriod(
    XYZ_Process_RequestStateChange* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_RequestStateChange_Clear_TimeoutPeriod(
    XYZ_Process_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** XYZ_Process.Create()
**
**==============================================================================
*/

typedef struct _XYZ_Process_Create
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstStringField imageName;
    /*OUT*/ CIM_Process_ConstRef process;
}
XYZ_Process_Create;

MI_EXTERN_C MI_CONST MI_MethodDecl XYZ_Process_Create_rtti;

MI_INLINE MI_Result MI_CALL XYZ_Process_Create_Construct(
    XYZ_Process_Create* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &XYZ_Process_Create_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Create_Clone(
    const XYZ_Process_Create* self,
    XYZ_Process_Create** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Create_Destruct(
    XYZ_Process_Create* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Create_Delete(
    XYZ_Process_Create* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Create_Post(
    const XYZ_Process_Create* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Create_Set_MIReturn(
    XYZ_Process_Create* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Create_Clear_MIReturn(
    XYZ_Process_Create* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Create_Set_imageName(
    XYZ_Process_Create* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Create_SetPtr_imageName(
    XYZ_Process_Create* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Create_Clear_imageName(
    XYZ_Process_Create* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Create_Set_process(
    XYZ_Process_Create* self,
    const CIM_Process* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Create_SetPtr_process(
    XYZ_Process_Create* self,
    const CIM_Process* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_Create_Clear_process(
    XYZ_Process_Create* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** XYZ_Process.GetRunTime()
**
**==============================================================================
*/

typedef struct _XYZ_Process_GetRunTime
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32Field pid;
    /*OUT*/ MI_ConstUint32Field runningTime;
}
XYZ_Process_GetRunTime;

MI_EXTERN_C MI_CONST MI_MethodDecl XYZ_Process_GetRunTime_rtti;

MI_INLINE MI_Result MI_CALL XYZ_Process_GetRunTime_Construct(
    XYZ_Process_GetRunTime* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &XYZ_Process_GetRunTime_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_GetRunTime_Clone(
    const XYZ_Process_GetRunTime* self,
    XYZ_Process_GetRunTime** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_GetRunTime_Destruct(
    XYZ_Process_GetRunTime* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_GetRunTime_Delete(
    XYZ_Process_GetRunTime* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_GetRunTime_Post(
    const XYZ_Process_GetRunTime* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL XYZ_Process_GetRunTime_Set_MIReturn(
    XYZ_Process_GetRunTime* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_GetRunTime_Clear_MIReturn(
    XYZ_Process_GetRunTime* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_GetRunTime_Set_pid(
    XYZ_Process_GetRunTime* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->pid)->value = x;
    ((MI_Uint32Field*)&self->pid)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_GetRunTime_Clear_pid(
    XYZ_Process_GetRunTime* self)
{
    memset((void*)&self->pid, 0, sizeof(self->pid));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_GetRunTime_Set_runningTime(
    XYZ_Process_GetRunTime* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->runningTime)->value = x;
    ((MI_Uint32Field*)&self->runningTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL XYZ_Process_GetRunTime_Clear_runningTime(
    XYZ_Process_GetRunTime* self)
{
    memset((void*)&self->runningTime, 0, sizeof(self->runningTime));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** XYZ_Process provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _XYZ_Process_Self XYZ_Process_Self;

MI_EXTERN_C void MI_CALL XYZ_Process_Load(
    XYZ_Process_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_Process_Unload(
    XYZ_Process_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL XYZ_Process_EnumerateInstances(
    XYZ_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL XYZ_Process_GetInstance(
    XYZ_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Process* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL XYZ_Process_CreateInstance(
    XYZ_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Process* newInstance);

MI_EXTERN_C void MI_CALL XYZ_Process_ModifyInstance(
    XYZ_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Process* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL XYZ_Process_DeleteInstance(
    XYZ_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const XYZ_Process* instanceName);

MI_EXTERN_C void MI_CALL XYZ_Process_Invoke_RequestStateChange(
    XYZ_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const XYZ_Process* instanceName,
    const XYZ_Process_RequestStateChange* in);

MI_EXTERN_C void MI_CALL XYZ_Process_Invoke_Create(
    XYZ_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const XYZ_Process* instanceName,
    const XYZ_Process_Create* in);

MI_EXTERN_C void MI_CALL XYZ_Process_Invoke_GetRunTime(
    XYZ_Process_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const XYZ_Process* instanceName,
    const XYZ_Process_GetRunTime* in);


#endif /* _XYZ_Process_h */
