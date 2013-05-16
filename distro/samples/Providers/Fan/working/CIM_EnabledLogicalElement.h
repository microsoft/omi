/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_EnabledLogicalElement_h
#define _CIM_EnabledLogicalElement_h

#include <MI.h>
#include "CIM_LogicalElement.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** CIM_EnabledLogicalElement [CIM_EnabledLogicalElement]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_EnabledLogicalElement /* extends CIM_LogicalElement */
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
}
CIM_EnabledLogicalElement;

typedef struct _CIM_EnabledLogicalElement_Ref
{
    CIM_EnabledLogicalElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_EnabledLogicalElement_Ref;

typedef struct _CIM_EnabledLogicalElement_ConstRef
{
    MI_CONST CIM_EnabledLogicalElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_EnabledLogicalElement_ConstRef;

typedef struct _CIM_EnabledLogicalElement_Array
{
    struct _CIM_EnabledLogicalElement** data;
    MI_Uint32 size;
}
CIM_EnabledLogicalElement_Array;

typedef struct _CIM_EnabledLogicalElement_ConstArray
{
    struct _CIM_EnabledLogicalElement MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_EnabledLogicalElement_ConstArray;

typedef struct _CIM_EnabledLogicalElement_ArrayRef
{
    CIM_EnabledLogicalElement_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_EnabledLogicalElement_ArrayRef;

typedef struct _CIM_EnabledLogicalElement_ConstArrayRef
{
    CIM_EnabledLogicalElement_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_EnabledLogicalElement_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_EnabledLogicalElement_rtti;

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Construct(
    CIM_EnabledLogicalElement* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_EnabledLogicalElement_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clone(
    const CIM_EnabledLogicalElement* self,
    CIM_EnabledLogicalElement** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_EnabledLogicalElement_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_EnabledLogicalElement_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Destruct(CIM_EnabledLogicalElement* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Delete(CIM_EnabledLogicalElement* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Post(
    const CIM_EnabledLogicalElement* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_InstanceID(
    CIM_EnabledLogicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_SetPtr_InstanceID(
    CIM_EnabledLogicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_InstanceID(
    CIM_EnabledLogicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_Caption(
    CIM_EnabledLogicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_SetPtr_Caption(
    CIM_EnabledLogicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_Caption(
    CIM_EnabledLogicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_Description(
    CIM_EnabledLogicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_SetPtr_Description(
    CIM_EnabledLogicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_Description(
    CIM_EnabledLogicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_ElementName(
    CIM_EnabledLogicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_SetPtr_ElementName(
    CIM_EnabledLogicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_ElementName(
    CIM_EnabledLogicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_InstallDate(
    CIM_EnabledLogicalElement* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_InstallDate(
    CIM_EnabledLogicalElement* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_Name(
    CIM_EnabledLogicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_SetPtr_Name(
    CIM_EnabledLogicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_Name(
    CIM_EnabledLogicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_OperationalStatus(
    CIM_EnabledLogicalElement* self,
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

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_SetPtr_OperationalStatus(
    CIM_EnabledLogicalElement* self,
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

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_OperationalStatus(
    CIM_EnabledLogicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_StatusDescriptions(
    CIM_EnabledLogicalElement* self,
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

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_SetPtr_StatusDescriptions(
    CIM_EnabledLogicalElement* self,
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

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_StatusDescriptions(
    CIM_EnabledLogicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_Status(
    CIM_EnabledLogicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_SetPtr_Status(
    CIM_EnabledLogicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_Status(
    CIM_EnabledLogicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_HealthState(
    CIM_EnabledLogicalElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_HealthState(
    CIM_EnabledLogicalElement* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_CommunicationStatus(
    CIM_EnabledLogicalElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_CommunicationStatus(
    CIM_EnabledLogicalElement* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_DetailedStatus(
    CIM_EnabledLogicalElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_DetailedStatus(
    CIM_EnabledLogicalElement* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_OperatingStatus(
    CIM_EnabledLogicalElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_OperatingStatus(
    CIM_EnabledLogicalElement* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_PrimaryStatus(
    CIM_EnabledLogicalElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_PrimaryStatus(
    CIM_EnabledLogicalElement* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_EnabledState(
    CIM_EnabledLogicalElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_EnabledState(
    CIM_EnabledLogicalElement* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_OtherEnabledState(
    CIM_EnabledLogicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_SetPtr_OtherEnabledState(
    CIM_EnabledLogicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_OtherEnabledState(
    CIM_EnabledLogicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_RequestedState(
    CIM_EnabledLogicalElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_RequestedState(
    CIM_EnabledLogicalElement* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_EnabledDefault(
    CIM_EnabledLogicalElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_EnabledDefault(
    CIM_EnabledLogicalElement* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_TimeOfLastStateChange(
    CIM_EnabledLogicalElement* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_TimeOfLastStateChange(
    CIM_EnabledLogicalElement* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_AvailableRequestedStates(
    CIM_EnabledLogicalElement* self,
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

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_SetPtr_AvailableRequestedStates(
    CIM_EnabledLogicalElement* self,
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

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_AvailableRequestedStates(
    CIM_EnabledLogicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Set_TransitioningToState(
    CIM_EnabledLogicalElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_Clear_TransitioningToState(
    CIM_EnabledLogicalElement* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_EnabledLogicalElement.RequestStateChange()
**
**==============================================================================
*/

typedef struct _CIM_EnabledLogicalElement_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
CIM_EnabledLogicalElement_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_EnabledLogicalElement_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_RequestStateChange_Construct(
    CIM_EnabledLogicalElement_RequestStateChange* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &CIM_EnabledLogicalElement_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_RequestStateChange_Clone(
    const CIM_EnabledLogicalElement_RequestStateChange* self,
    CIM_EnabledLogicalElement_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_RequestStateChange_Destruct(
    CIM_EnabledLogicalElement_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_RequestStateChange_Delete(
    CIM_EnabledLogicalElement_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_RequestStateChange_Post(
    const CIM_EnabledLogicalElement_RequestStateChange* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_RequestStateChange_Set_MIReturn(
    CIM_EnabledLogicalElement_RequestStateChange* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_RequestStateChange_Clear_MIReturn(
    CIM_EnabledLogicalElement_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_RequestStateChange_Set_RequestedState(
    CIM_EnabledLogicalElement_RequestStateChange* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_RequestStateChange_Clear_RequestedState(
    CIM_EnabledLogicalElement_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_RequestStateChange_Set_Job(
    CIM_EnabledLogicalElement_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_RequestStateChange_SetPtr_Job(
    CIM_EnabledLogicalElement_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_RequestStateChange_Clear_Job(
    CIM_EnabledLogicalElement_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_RequestStateChange_Set_TimeoutPeriod(
    CIM_EnabledLogicalElement_RequestStateChange* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElement_RequestStateChange_Clear_TimeoutPeriod(
    CIM_EnabledLogicalElement_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}


#endif /* _CIM_EnabledLogicalElement_h */
