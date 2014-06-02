/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_VLANEndpoint_h
#define _ABC_VLANEndpoint_h

#include <MI.h>
#include "CIM_VLANEndpoint.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** ABC_VLANEndpoint [ABC_VLANEndpoint]
**
** Keys:
**    Name
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**
**==============================================================================
*/

typedef struct _ABC_VLANEndpoint /* extends CIM_VLANEndpoint */
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
    /* CIM_VLANEndpoint properties */
    MI_ConstUint16Field DesiredEndpointMode;
    MI_ConstStringField OtherEndpointMode;
    MI_ConstUint16Field OperationalEndpointMode;
    MI_ConstUint16Field DesiredVLANTrunkEncapsulation;
    MI_ConstStringField OtherTrunkEncapsulation;
    MI_ConstUint16Field OperationalVLANTrunkEncapsulation;
    MI_ConstUint16Field GVRPStatus;
    /* ABC_VLANEndpoint properties */
}
ABC_VLANEndpoint;

typedef struct _ABC_VLANEndpoint_Ref
{
    ABC_VLANEndpoint* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_VLANEndpoint_Ref;

typedef struct _ABC_VLANEndpoint_ConstRef
{
    MI_CONST ABC_VLANEndpoint* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_VLANEndpoint_ConstRef;

typedef struct _ABC_VLANEndpoint_Array
{
    struct _ABC_VLANEndpoint** data;
    MI_Uint32 size;
}
ABC_VLANEndpoint_Array;

typedef struct _ABC_VLANEndpoint_ConstArray
{
    struct _ABC_VLANEndpoint MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_VLANEndpoint_ConstArray;

typedef struct _ABC_VLANEndpoint_ArrayRef
{
    ABC_VLANEndpoint_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_VLANEndpoint_ArrayRef;

typedef struct _ABC_VLANEndpoint_ConstArrayRef
{
    ABC_VLANEndpoint_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_VLANEndpoint_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_VLANEndpoint_rtti;

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Construct(
    ABC_VLANEndpoint* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_VLANEndpoint_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clone(
    const ABC_VLANEndpoint* self,
    ABC_VLANEndpoint** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_VLANEndpoint_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_VLANEndpoint_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Destruct(ABC_VLANEndpoint* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Delete(ABC_VLANEndpoint* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Post(
    const ABC_VLANEndpoint* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_InstanceID(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_SetPtr_InstanceID(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_InstanceID(
    ABC_VLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_Caption(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_SetPtr_Caption(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_Caption(
    ABC_VLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_Description(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_SetPtr_Description(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_Description(
    ABC_VLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_ElementName(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_SetPtr_ElementName(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_ElementName(
    ABC_VLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_InstallDate(
    ABC_VLANEndpoint* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_InstallDate(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_Name(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_SetPtr_Name(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_Name(
    ABC_VLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_OperationalStatus(
    ABC_VLANEndpoint* self,
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

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_SetPtr_OperationalStatus(
    ABC_VLANEndpoint* self,
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

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_OperationalStatus(
    ABC_VLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_StatusDescriptions(
    ABC_VLANEndpoint* self,
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

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_SetPtr_StatusDescriptions(
    ABC_VLANEndpoint* self,
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

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_StatusDescriptions(
    ABC_VLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_Status(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_SetPtr_Status(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_Status(
    ABC_VLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_HealthState(
    ABC_VLANEndpoint* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_HealthState(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_CommunicationStatus(
    ABC_VLANEndpoint* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_CommunicationStatus(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_DetailedStatus(
    ABC_VLANEndpoint* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_DetailedStatus(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_OperatingStatus(
    ABC_VLANEndpoint* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_OperatingStatus(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_PrimaryStatus(
    ABC_VLANEndpoint* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_PrimaryStatus(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_EnabledState(
    ABC_VLANEndpoint* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_EnabledState(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_OtherEnabledState(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_SetPtr_OtherEnabledState(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_OtherEnabledState(
    ABC_VLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_RequestedState(
    ABC_VLANEndpoint* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_RequestedState(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_EnabledDefault(
    ABC_VLANEndpoint* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_EnabledDefault(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_TimeOfLastStateChange(
    ABC_VLANEndpoint* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_TimeOfLastStateChange(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_AvailableRequestedStates(
    ABC_VLANEndpoint* self,
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

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_SetPtr_AvailableRequestedStates(
    ABC_VLANEndpoint* self,
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

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_AvailableRequestedStates(
    ABC_VLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_TransitioningToState(
    ABC_VLANEndpoint* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_TransitioningToState(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_SystemCreationClassName(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_SetPtr_SystemCreationClassName(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_SystemCreationClassName(
    ABC_VLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_SystemName(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_SetPtr_SystemName(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_SystemName(
    ABC_VLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_CreationClassName(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_SetPtr_CreationClassName(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_CreationClassName(
    ABC_VLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_NameFormat(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_SetPtr_NameFormat(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_NameFormat(
    ABC_VLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_ProtocolType(
    ABC_VLANEndpoint* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ProtocolType)->value = x;
    ((MI_Uint16Field*)&self->ProtocolType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_ProtocolType(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->ProtocolType, 0, sizeof(self->ProtocolType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_ProtocolIFType(
    ABC_VLANEndpoint* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ProtocolIFType)->value = x;
    ((MI_Uint16Field*)&self->ProtocolIFType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_ProtocolIFType(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->ProtocolIFType, 0, sizeof(self->ProtocolIFType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_OtherTypeDescription(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_SetPtr_OtherTypeDescription(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_OtherTypeDescription(
    ABC_VLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        27);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_DesiredEndpointMode(
    ABC_VLANEndpoint* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DesiredEndpointMode)->value = x;
    ((MI_Uint16Field*)&self->DesiredEndpointMode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_DesiredEndpointMode(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->DesiredEndpointMode, 0, sizeof(self->DesiredEndpointMode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_OtherEndpointMode(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_SetPtr_OtherEndpointMode(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_OtherEndpointMode(
    ABC_VLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        29);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_OperationalEndpointMode(
    ABC_VLANEndpoint* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperationalEndpointMode)->value = x;
    ((MI_Uint16Field*)&self->OperationalEndpointMode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_OperationalEndpointMode(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->OperationalEndpointMode, 0, sizeof(self->OperationalEndpointMode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_DesiredVLANTrunkEncapsulation(
    ABC_VLANEndpoint* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DesiredVLANTrunkEncapsulation)->value = x;
    ((MI_Uint16Field*)&self->DesiredVLANTrunkEncapsulation)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_DesiredVLANTrunkEncapsulation(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->DesiredVLANTrunkEncapsulation, 0, sizeof(self->DesiredVLANTrunkEncapsulation));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_OtherTrunkEncapsulation(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_SetPtr_OtherTrunkEncapsulation(
    ABC_VLANEndpoint* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_OtherTrunkEncapsulation(
    ABC_VLANEndpoint* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        32);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_OperationalVLANTrunkEncapsulation(
    ABC_VLANEndpoint* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperationalVLANTrunkEncapsulation)->value = x;
    ((MI_Uint16Field*)&self->OperationalVLANTrunkEncapsulation)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_OperationalVLANTrunkEncapsulation(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->OperationalVLANTrunkEncapsulation, 0, sizeof(self->OperationalVLANTrunkEncapsulation));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Set_GVRPStatus(
    ABC_VLANEndpoint* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->GVRPStatus)->value = x;
    ((MI_Uint16Field*)&self->GVRPStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_Clear_GVRPStatus(
    ABC_VLANEndpoint* self)
{
    memset((void*)&self->GVRPStatus, 0, sizeof(self->GVRPStatus));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_VLANEndpoint.RequestStateChange()
**
**==============================================================================
*/

typedef struct _ABC_VLANEndpoint_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
ABC_VLANEndpoint_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_VLANEndpoint_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_RequestStateChange_Construct(
    ABC_VLANEndpoint_RequestStateChange* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_VLANEndpoint_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_RequestStateChange_Clone(
    const ABC_VLANEndpoint_RequestStateChange* self,
    ABC_VLANEndpoint_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_RequestStateChange_Destruct(
    ABC_VLANEndpoint_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_RequestStateChange_Delete(
    ABC_VLANEndpoint_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_RequestStateChange_Post(
    const ABC_VLANEndpoint_RequestStateChange* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_RequestStateChange_Set_MIReturn(
    ABC_VLANEndpoint_RequestStateChange* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_RequestStateChange_Clear_MIReturn(
    ABC_VLANEndpoint_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_RequestStateChange_Set_RequestedState(
    ABC_VLANEndpoint_RequestStateChange* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_RequestStateChange_Clear_RequestedState(
    ABC_VLANEndpoint_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_RequestStateChange_Set_Job(
    ABC_VLANEndpoint_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_RequestStateChange_SetPtr_Job(
    ABC_VLANEndpoint_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_RequestStateChange_Clear_Job(
    ABC_VLANEndpoint_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_RequestStateChange_Set_TimeoutPeriod(
    ABC_VLANEndpoint_RequestStateChange* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_VLANEndpoint_RequestStateChange_Clear_TimeoutPeriod(
    ABC_VLANEndpoint_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_VLANEndpoint provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_VLANEndpoint_Self ABC_VLANEndpoint_Self;

MI_EXTERN_C void MI_CALL ABC_VLANEndpoint_Load(
    ABC_VLANEndpoint_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_VLANEndpoint_Unload(
    ABC_VLANEndpoint_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_VLANEndpoint_EnumerateInstances(
    ABC_VLANEndpoint_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_VLANEndpoint_GetInstance(
    ABC_VLANEndpoint_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_VLANEndpoint* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_VLANEndpoint_CreateInstance(
    ABC_VLANEndpoint_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_VLANEndpoint* newInstance);

MI_EXTERN_C void MI_CALL ABC_VLANEndpoint_ModifyInstance(
    ABC_VLANEndpoint_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_VLANEndpoint* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_VLANEndpoint_DeleteInstance(
    ABC_VLANEndpoint_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_VLANEndpoint* instanceName);

MI_EXTERN_C void MI_CALL ABC_VLANEndpoint_Invoke_RequestStateChange(
    ABC_VLANEndpoint_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_VLANEndpoint* instanceName,
    const ABC_VLANEndpoint_RequestStateChange* in);


#endif /* _ABC_VLANEndpoint_h */
