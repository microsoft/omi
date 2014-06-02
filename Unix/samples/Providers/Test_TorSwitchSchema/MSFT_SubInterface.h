/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_SubInterface_h
#define _MSFT_SubInterface_h

#include <MI.h>
#include "CIM_ProtocolEndpoint.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** MSFT_SubInterface [MSFT_SubInterface]
**
** Keys:
**    Name
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**
**==============================================================================
*/

typedef struct _MSFT_SubInterface /* extends CIM_ProtocolEndpoint */
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
    /* MSFT_SubInterface properties */
    MI_ConstStringField ParentInterfaceID;
    MI_ConstUint16Field EncapsulationDot1Q;
}
MSFT_SubInterface;

typedef struct _MSFT_SubInterface_Ref
{
    MSFT_SubInterface* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_SubInterface_Ref;

typedef struct _MSFT_SubInterface_ConstRef
{
    MI_CONST MSFT_SubInterface* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_SubInterface_ConstRef;

typedef struct _MSFT_SubInterface_Array
{
    struct _MSFT_SubInterface** data;
    MI_Uint32 size;
}
MSFT_SubInterface_Array;

typedef struct _MSFT_SubInterface_ConstArray
{
    struct _MSFT_SubInterface MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_SubInterface_ConstArray;

typedef struct _MSFT_SubInterface_ArrayRef
{
    MSFT_SubInterface_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_SubInterface_ArrayRef;

typedef struct _MSFT_SubInterface_ConstArrayRef
{
    MSFT_SubInterface_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_SubInterface_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_SubInterface_rtti;

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Construct(
    _Out_ MSFT_SubInterface* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_SubInterface_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clone(
    _In_ const MSFT_SubInterface* self,
    _Outptr_ MSFT_SubInterface** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_SubInterface_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_SubInterface_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Destruct(_Inout_ MSFT_SubInterface* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Delete(_Inout_ MSFT_SubInterface* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Post(
    _In_ const MSFT_SubInterface* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_InstanceID(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_SetPtr_InstanceID(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_InstanceID(
    _Inout_ MSFT_SubInterface* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_Caption(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_SetPtr_Caption(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_Caption(
    _Inout_ MSFT_SubInterface* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_Description(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_SetPtr_Description(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_Description(
    _Inout_ MSFT_SubInterface* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_ElementName(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_SetPtr_ElementName(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_ElementName(
    _Inout_ MSFT_SubInterface* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_InstallDate(
    _Inout_ MSFT_SubInterface* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_InstallDate(
    _Inout_ MSFT_SubInterface* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_Name(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_SetPtr_Name(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_Name(
    _Inout_ MSFT_SubInterface* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_OperationalStatus(
    _Inout_ MSFT_SubInterface* self,
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

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_SetPtr_OperationalStatus(
    _Inout_ MSFT_SubInterface* self,
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

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_OperationalStatus(
    _Inout_ MSFT_SubInterface* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_StatusDescriptions(
    _Inout_ MSFT_SubInterface* self,
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

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_SetPtr_StatusDescriptions(
    _Inout_ MSFT_SubInterface* self,
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

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_StatusDescriptions(
    _Inout_ MSFT_SubInterface* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_Status(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_SetPtr_Status(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_Status(
    _Inout_ MSFT_SubInterface* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_HealthState(
    _Inout_ MSFT_SubInterface* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_HealthState(
    _Inout_ MSFT_SubInterface* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_CommunicationStatus(
    _Inout_ MSFT_SubInterface* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_CommunicationStatus(
    _Inout_ MSFT_SubInterface* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_DetailedStatus(
    _Inout_ MSFT_SubInterface* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_DetailedStatus(
    _Inout_ MSFT_SubInterface* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_OperatingStatus(
    _Inout_ MSFT_SubInterface* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_OperatingStatus(
    _Inout_ MSFT_SubInterface* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_PrimaryStatus(
    _Inout_ MSFT_SubInterface* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_PrimaryStatus(
    _Inout_ MSFT_SubInterface* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_EnabledState(
    _Inout_ MSFT_SubInterface* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_EnabledState(
    _Inout_ MSFT_SubInterface* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_OtherEnabledState(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_SetPtr_OtherEnabledState(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_OtherEnabledState(
    _Inout_ MSFT_SubInterface* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_RequestedState(
    _Inout_ MSFT_SubInterface* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_RequestedState(
    _Inout_ MSFT_SubInterface* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_EnabledDefault(
    _Inout_ MSFT_SubInterface* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_EnabledDefault(
    _Inout_ MSFT_SubInterface* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_TimeOfLastStateChange(
    _Inout_ MSFT_SubInterface* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_TimeOfLastStateChange(
    _Inout_ MSFT_SubInterface* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_AvailableRequestedStates(
    _Inout_ MSFT_SubInterface* self,
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

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_SetPtr_AvailableRequestedStates(
    _Inout_ MSFT_SubInterface* self,
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

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_AvailableRequestedStates(
    _Inout_ MSFT_SubInterface* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_TransitioningToState(
    _Inout_ MSFT_SubInterface* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_TransitioningToState(
    _Inout_ MSFT_SubInterface* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_SystemCreationClassName(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_SetPtr_SystemCreationClassName(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_SystemCreationClassName(
    _Inout_ MSFT_SubInterface* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_SystemName(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_SetPtr_SystemName(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_SystemName(
    _Inout_ MSFT_SubInterface* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_CreationClassName(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_SetPtr_CreationClassName(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_CreationClassName(
    _Inout_ MSFT_SubInterface* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_NameFormat(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_SetPtr_NameFormat(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_NameFormat(
    _Inout_ MSFT_SubInterface* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_ProtocolType(
    _Inout_ MSFT_SubInterface* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ProtocolType)->value = x;
    ((MI_Uint16Field*)&self->ProtocolType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_ProtocolType(
    _Inout_ MSFT_SubInterface* self)
{
    memset((void*)&self->ProtocolType, 0, sizeof(self->ProtocolType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_ProtocolIFType(
    _Inout_ MSFT_SubInterface* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ProtocolIFType)->value = x;
    ((MI_Uint16Field*)&self->ProtocolIFType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_ProtocolIFType(
    _Inout_ MSFT_SubInterface* self)
{
    memset((void*)&self->ProtocolIFType, 0, sizeof(self->ProtocolIFType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_OtherTypeDescription(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_SetPtr_OtherTypeDescription(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_OtherTypeDescription(
    _Inout_ MSFT_SubInterface* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        27);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_ParentInterfaceID(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        28,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_SetPtr_ParentInterfaceID(
    _Inout_ MSFT_SubInterface* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        28,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_ParentInterfaceID(
    _Inout_ MSFT_SubInterface* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        28);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Set_EncapsulationDot1Q(
    _Inout_ MSFT_SubInterface* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EncapsulationDot1Q)->value = x;
    ((MI_Uint16Field*)&self->EncapsulationDot1Q)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_Clear_EncapsulationDot1Q(
    _Inout_ MSFT_SubInterface* self)
{
    memset((void*)&self->EncapsulationDot1Q, 0, sizeof(self->EncapsulationDot1Q));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_SubInterface.RequestStateChange()
**
**==============================================================================
*/

typedef struct _MSFT_SubInterface_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
MSFT_SubInterface_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_SubInterface_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_RequestStateChange_Construct(
    _Out_ MSFT_SubInterface_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_SubInterface_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_RequestStateChange_Clone(
    _In_ const MSFT_SubInterface_RequestStateChange* self,
    _Outptr_ MSFT_SubInterface_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_RequestStateChange_Destruct(
    _Inout_ MSFT_SubInterface_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_RequestStateChange_Delete(
    _Inout_ MSFT_SubInterface_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_RequestStateChange_Post(
    _In_ const MSFT_SubInterface_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_RequestStateChange_Set_MIReturn(
    _Inout_ MSFT_SubInterface_RequestStateChange* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_RequestStateChange_Clear_MIReturn(
    _Inout_ MSFT_SubInterface_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_RequestStateChange_Set_RequestedState(
    _Inout_ MSFT_SubInterface_RequestStateChange* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_RequestStateChange_Clear_RequestedState(
    _Inout_ MSFT_SubInterface_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_RequestStateChange_Set_Job(
    _Inout_ MSFT_SubInterface_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_RequestStateChange_SetPtr_Job(
    _Inout_ MSFT_SubInterface_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_RequestStateChange_Clear_Job(
    _Inout_ MSFT_SubInterface_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_RequestStateChange_Set_TimeoutPeriod(
    _Inout_ MSFT_SubInterface_RequestStateChange* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_SubInterface_RequestStateChange_Clear_TimeoutPeriod(
    _Inout_ MSFT_SubInterface_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_SubInterface provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_SubInterface_Self MSFT_SubInterface_Self;

MI_EXTERN_C void MI_CALL MSFT_SubInterface_Load(
    _Outptr_result_maybenull_ MSFT_SubInterface_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_SubInterface_Unload(
    _In_opt_ MSFT_SubInterface_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_SubInterface_EnumerateInstances(
    _In_opt_ MSFT_SubInterface_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_SubInterface_GetInstance(
    _In_opt_ MSFT_SubInterface_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_SubInterface* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_SubInterface_CreateInstance(
    _In_opt_ MSFT_SubInterface_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_SubInterface* newInstance);

MI_EXTERN_C void MI_CALL MSFT_SubInterface_ModifyInstance(
    _In_opt_ MSFT_SubInterface_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_SubInterface* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_SubInterface_DeleteInstance(
    _In_opt_ MSFT_SubInterface_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_SubInterface* instanceName);

MI_EXTERN_C void MI_CALL MSFT_SubInterface_Invoke_RequestStateChange(
    _In_opt_ MSFT_SubInterface_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_SubInterface* instanceName,
    _In_opt_ const MSFT_SubInterface_RequestStateChange* in);


#endif /* _MSFT_SubInterface_h */
