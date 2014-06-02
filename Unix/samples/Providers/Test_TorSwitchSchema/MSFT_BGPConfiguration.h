/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_BGPConfiguration_h
#define _MSFT_BGPConfiguration_h

#include <MI.h>
#include "CIM_AutonomousSystem.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** MSFT_BGPConfiguration [MSFT_BGPConfiguration]
**
** Keys:
**    Name
**    CreationClassName
**
**==============================================================================
*/

typedef struct _MSFT_BGPConfiguration /* extends CIM_AutonomousSystem */
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
    /* CIM_AdminDomain properties */
    /* CIM_AutonomousSystem properties */
    MI_ConstUint16Field ASNumber;
    MI_ConstBooleanField IsSingleHomed;
    MI_ConstBooleanField IsTransit;
    MI_ConstBooleanField RequireIGPSync;
    MI_ConstUint16Field RoutingUpdateSource;
    MI_ConstUint16Field AggregationType;
    /* MSFT_BGPConfiguration properties */
    MI_ConstBooleanField LogNeighborChanges;
}
MSFT_BGPConfiguration;

typedef struct _MSFT_BGPConfiguration_Ref
{
    MSFT_BGPConfiguration* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BGPConfiguration_Ref;

typedef struct _MSFT_BGPConfiguration_ConstRef
{
    MI_CONST MSFT_BGPConfiguration* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BGPConfiguration_ConstRef;

typedef struct _MSFT_BGPConfiguration_Array
{
    struct _MSFT_BGPConfiguration** data;
    MI_Uint32 size;
}
MSFT_BGPConfiguration_Array;

typedef struct _MSFT_BGPConfiguration_ConstArray
{
    struct _MSFT_BGPConfiguration MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_BGPConfiguration_ConstArray;

typedef struct _MSFT_BGPConfiguration_ArrayRef
{
    MSFT_BGPConfiguration_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BGPConfiguration_ArrayRef;

typedef struct _MSFT_BGPConfiguration_ConstArrayRef
{
    MSFT_BGPConfiguration_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_BGPConfiguration_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_BGPConfiguration_rtti;

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Construct(
    _Out_ MSFT_BGPConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_BGPConfiguration_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clone(
    _In_ const MSFT_BGPConfiguration* self,
    _Outptr_ MSFT_BGPConfiguration** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_BGPConfiguration_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_BGPConfiguration_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Destruct(_Inout_ MSFT_BGPConfiguration* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Delete(_Inout_ MSFT_BGPConfiguration* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Post(
    _In_ const MSFT_BGPConfiguration* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_InstanceID(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_SetPtr_InstanceID(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_InstanceID(
    _Inout_ MSFT_BGPConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_Caption(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_SetPtr_Caption(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_Caption(
    _Inout_ MSFT_BGPConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_Description(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_SetPtr_Description(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_Description(
    _Inout_ MSFT_BGPConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_ElementName(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_SetPtr_ElementName(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_ElementName(
    _Inout_ MSFT_BGPConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_InstallDate(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_InstallDate(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_Name(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_SetPtr_Name(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_Name(
    _Inout_ MSFT_BGPConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_OperationalStatus(
    _Inout_ MSFT_BGPConfiguration* self,
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

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_SetPtr_OperationalStatus(
    _Inout_ MSFT_BGPConfiguration* self,
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

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_OperationalStatus(
    _Inout_ MSFT_BGPConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_StatusDescriptions(
    _Inout_ MSFT_BGPConfiguration* self,
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

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_SetPtr_StatusDescriptions(
    _Inout_ MSFT_BGPConfiguration* self,
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

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_StatusDescriptions(
    _Inout_ MSFT_BGPConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_Status(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_SetPtr_Status(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_Status(
    _Inout_ MSFT_BGPConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_HealthState(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_HealthState(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_CommunicationStatus(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_CommunicationStatus(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_DetailedStatus(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_DetailedStatus(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_OperatingStatus(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_OperatingStatus(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_PrimaryStatus(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_PrimaryStatus(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_EnabledState(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_EnabledState(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_OtherEnabledState(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_SetPtr_OtherEnabledState(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_OtherEnabledState(
    _Inout_ MSFT_BGPConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_RequestedState(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_RequestedState(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_EnabledDefault(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_EnabledDefault(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_TimeOfLastStateChange(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_TimeOfLastStateChange(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_AvailableRequestedStates(
    _Inout_ MSFT_BGPConfiguration* self,
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

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_SetPtr_AvailableRequestedStates(
    _Inout_ MSFT_BGPConfiguration* self,
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

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_AvailableRequestedStates(
    _Inout_ MSFT_BGPConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_TransitioningToState(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_TransitioningToState(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_CreationClassName(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_SetPtr_CreationClassName(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_CreationClassName(
    _Inout_ MSFT_BGPConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_NameFormat(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_SetPtr_NameFormat(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_NameFormat(
    _Inout_ MSFT_BGPConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_PrimaryOwnerName(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_SetPtr_PrimaryOwnerName(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_PrimaryOwnerName(
    _Inout_ MSFT_BGPConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_PrimaryOwnerContact(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_SetPtr_PrimaryOwnerContact(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_PrimaryOwnerContact(
    _Inout_ MSFT_BGPConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_Roles(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_SetPtr_Roles(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_Roles(
    _Inout_ MSFT_BGPConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        25);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_OtherIdentifyingInfo(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_SetPtr_OtherIdentifyingInfo(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_OtherIdentifyingInfo(
    _Inout_ MSFT_BGPConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_IdentifyingDescriptions(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_SetPtr_IdentifyingDescriptions(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_IdentifyingDescriptions(
    _Inout_ MSFT_BGPConfiguration* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        27);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_ASNumber(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ASNumber)->value = x;
    ((MI_Uint16Field*)&self->ASNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_ASNumber(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->ASNumber, 0, sizeof(self->ASNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_IsSingleHomed(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->IsSingleHomed)->value = x;
    ((MI_BooleanField*)&self->IsSingleHomed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_IsSingleHomed(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->IsSingleHomed, 0, sizeof(self->IsSingleHomed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_IsTransit(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->IsTransit)->value = x;
    ((MI_BooleanField*)&self->IsTransit)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_IsTransit(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->IsTransit, 0, sizeof(self->IsTransit));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_RequireIGPSync(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->RequireIGPSync)->value = x;
    ((MI_BooleanField*)&self->RequireIGPSync)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_RequireIGPSync(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->RequireIGPSync, 0, sizeof(self->RequireIGPSync));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_RoutingUpdateSource(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RoutingUpdateSource)->value = x;
    ((MI_Uint16Field*)&self->RoutingUpdateSource)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_RoutingUpdateSource(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->RoutingUpdateSource, 0, sizeof(self->RoutingUpdateSource));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_AggregationType(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->AggregationType)->value = x;
    ((MI_Uint16Field*)&self->AggregationType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_AggregationType(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->AggregationType, 0, sizeof(self->AggregationType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Set_LogNeighborChanges(
    _Inout_ MSFT_BGPConfiguration* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->LogNeighborChanges)->value = x;
    ((MI_BooleanField*)&self->LogNeighborChanges)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_Clear_LogNeighborChanges(
    _Inout_ MSFT_BGPConfiguration* self)
{
    memset((void*)&self->LogNeighborChanges, 0, sizeof(self->LogNeighborChanges));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_BGPConfiguration.RequestStateChange()
**
**==============================================================================
*/

typedef struct _MSFT_BGPConfiguration_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
MSFT_BGPConfiguration_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_BGPConfiguration_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_RequestStateChange_Construct(
    _Out_ MSFT_BGPConfiguration_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &MSFT_BGPConfiguration_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_RequestStateChange_Clone(
    _In_ const MSFT_BGPConfiguration_RequestStateChange* self,
    _Outptr_ MSFT_BGPConfiguration_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_RequestStateChange_Destruct(
    _Inout_ MSFT_BGPConfiguration_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_RequestStateChange_Delete(
    _Inout_ MSFT_BGPConfiguration_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_RequestStateChange_Post(
    _In_ const MSFT_BGPConfiguration_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_RequestStateChange_Set_MIReturn(
    _Inout_ MSFT_BGPConfiguration_RequestStateChange* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_RequestStateChange_Clear_MIReturn(
    _Inout_ MSFT_BGPConfiguration_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_RequestStateChange_Set_RequestedState(
    _Inout_ MSFT_BGPConfiguration_RequestStateChange* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_RequestStateChange_Clear_RequestedState(
    _Inout_ MSFT_BGPConfiguration_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_RequestStateChange_Set_Job(
    _Inout_ MSFT_BGPConfiguration_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_RequestStateChange_SetPtr_Job(
    _Inout_ MSFT_BGPConfiguration_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_RequestStateChange_Clear_Job(
    _Inout_ MSFT_BGPConfiguration_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_RequestStateChange_Set_TimeoutPeriod(
    _Inout_ MSFT_BGPConfiguration_RequestStateChange* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_BGPConfiguration_RequestStateChange_Clear_TimeoutPeriod(
    _Inout_ MSFT_BGPConfiguration_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_BGPConfiguration provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_BGPConfiguration_Self MSFT_BGPConfiguration_Self;

MI_EXTERN_C void MI_CALL MSFT_BGPConfiguration_Load(
    _Outptr_result_maybenull_ MSFT_BGPConfiguration_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_BGPConfiguration_Unload(
    _In_opt_ MSFT_BGPConfiguration_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_BGPConfiguration_EnumerateInstances(
    _In_opt_ MSFT_BGPConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_BGPConfiguration_GetInstance(
    _In_opt_ MSFT_BGPConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_BGPConfiguration* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_BGPConfiguration_CreateInstance(
    _In_opt_ MSFT_BGPConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_BGPConfiguration* newInstance);

MI_EXTERN_C void MI_CALL MSFT_BGPConfiguration_ModifyInstance(
    _In_opt_ MSFT_BGPConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_BGPConfiguration* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_BGPConfiguration_DeleteInstance(
    _In_opt_ MSFT_BGPConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_BGPConfiguration* instanceName);

MI_EXTERN_C void MI_CALL MSFT_BGPConfiguration_Invoke_RequestStateChange(
    _In_opt_ MSFT_BGPConfiguration_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const MSFT_BGPConfiguration* instanceName,
    _In_opt_ const MSFT_BGPConfiguration_RequestStateChange* in);


#endif /* _MSFT_BGPConfiguration_h */
