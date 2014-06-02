/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_NumericSensor_h
#define _ABC_NumericSensor_h

#include <MI.h>
#include "CIM_NumericSensor.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** ABC_NumericSensor [ABC_NumericSensor]
**
** Keys:
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**    DeviceID
**
**==============================================================================
*/

typedef struct _ABC_NumericSensor /* extends CIM_NumericSensor */
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
    /* CIM_LogicalDevice properties */
    /*KEY*/ MI_ConstStringField SystemCreationClassName;
    /*KEY*/ MI_ConstStringField SystemName;
    /*KEY*/ MI_ConstStringField CreationClassName;
    /*KEY*/ MI_ConstStringField DeviceID;
    MI_ConstBooleanField PowerManagementSupported;
    MI_ConstUint16AField PowerManagementCapabilities;
    MI_ConstUint16Field Availability;
    MI_ConstUint16Field StatusInfo;
    MI_ConstUint32Field LastErrorCode;
    MI_ConstStringField ErrorDescription;
    MI_ConstBooleanField ErrorCleared;
    MI_ConstStringAField OtherIdentifyingInfo;
    MI_ConstUint64Field PowerOnHours;
    MI_ConstUint64Field TotalPowerOnHours;
    MI_ConstStringAField IdentifyingDescriptions;
    MI_ConstUint16AField AdditionalAvailability;
    MI_ConstUint64Field MaxQuiesceTime;
    /* CIM_Sensor properties */
    MI_ConstUint16Field SensorType;
    MI_ConstStringField OtherSensorTypeDescription;
    MI_ConstStringAField PossibleStates;
    MI_ConstStringField CurrentState;
    MI_ConstUint64Field PollingInterval;
    MI_ConstStringField SensorContext;
    /* CIM_NumericSensor properties */
    MI_ConstUint16Field BaseUnits;
    MI_ConstSint32Field UnitModifier;
    MI_ConstUint16Field RateUnits;
    MI_ConstSint32Field CurrentReading;
    MI_ConstSint32Field NominalReading;
    MI_ConstSint32Field NormalMax;
    MI_ConstSint32Field NormalMin;
    MI_ConstSint32Field MaxReadable;
    MI_ConstSint32Field MinReadable;
    MI_ConstUint32Field Resolution;
    MI_ConstSint32Field Tolerance;
    MI_ConstSint32Field Accuracy;
    MI_ConstBooleanField IsLinear;
    MI_ConstUint32Field Hysteresis;
    MI_ConstSint32Field LowerThresholdNonCritical;
    MI_ConstSint32Field UpperThresholdNonCritical;
    MI_ConstSint32Field LowerThresholdCritical;
    MI_ConstSint32Field UpperThresholdCritical;
    MI_ConstSint32Field LowerThresholdFatal;
    MI_ConstSint32Field UpperThresholdFatal;
    MI_ConstUint16AField SupportedThresholds;
    MI_ConstUint16AField EnabledThresholds;
    MI_ConstUint16AField SettableThresholds;
    /* ABC_NumericSensor properties */
}
ABC_NumericSensor;

typedef struct _ABC_NumericSensor_Ref
{
    ABC_NumericSensor* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_NumericSensor_Ref;

typedef struct _ABC_NumericSensor_ConstRef
{
    MI_CONST ABC_NumericSensor* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_NumericSensor_ConstRef;

typedef struct _ABC_NumericSensor_Array
{
    struct _ABC_NumericSensor** data;
    MI_Uint32 size;
}
ABC_NumericSensor_Array;

typedef struct _ABC_NumericSensor_ConstArray
{
    struct _ABC_NumericSensor MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_NumericSensor_ConstArray;

typedef struct _ABC_NumericSensor_ArrayRef
{
    ABC_NumericSensor_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_NumericSensor_ArrayRef;

typedef struct _ABC_NumericSensor_ConstArrayRef
{
    ABC_NumericSensor_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_NumericSensor_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_NumericSensor_rtti;

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Construct(
    ABC_NumericSensor* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_NumericSensor_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clone(
    const ABC_NumericSensor* self,
    ABC_NumericSensor** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_NumericSensor_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_NumericSensor_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Destruct(ABC_NumericSensor* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Delete(ABC_NumericSensor* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Post(
    const ABC_NumericSensor* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_InstanceID(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_InstanceID(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_InstanceID(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_Caption(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_Caption(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_Caption(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_Description(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_Description(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_Description(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_ElementName(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_ElementName(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_ElementName(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_InstallDate(
    ABC_NumericSensor* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_InstallDate(
    ABC_NumericSensor* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_Name(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_Name(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_Name(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_OperationalStatus(
    ABC_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_OperationalStatus(
    ABC_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_OperationalStatus(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_StatusDescriptions(
    ABC_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_StatusDescriptions(
    ABC_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_StatusDescriptions(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_Status(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_Status(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_Status(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_HealthState(
    ABC_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_HealthState(
    ABC_NumericSensor* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_CommunicationStatus(
    ABC_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_CommunicationStatus(
    ABC_NumericSensor* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_DetailedStatus(
    ABC_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_DetailedStatus(
    ABC_NumericSensor* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_OperatingStatus(
    ABC_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_OperatingStatus(
    ABC_NumericSensor* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_PrimaryStatus(
    ABC_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_PrimaryStatus(
    ABC_NumericSensor* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_EnabledState(
    ABC_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_EnabledState(
    ABC_NumericSensor* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_OtherEnabledState(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_OtherEnabledState(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_OtherEnabledState(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_RequestedState(
    ABC_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_RequestedState(
    ABC_NumericSensor* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_EnabledDefault(
    ABC_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_EnabledDefault(
    ABC_NumericSensor* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_TimeOfLastStateChange(
    ABC_NumericSensor* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_TimeOfLastStateChange(
    ABC_NumericSensor* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_AvailableRequestedStates(
    ABC_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_AvailableRequestedStates(
    ABC_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_AvailableRequestedStates(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_TransitioningToState(
    ABC_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_TransitioningToState(
    ABC_NumericSensor* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_SystemCreationClassName(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_SystemCreationClassName(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_SystemCreationClassName(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_SystemName(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_SystemName(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_SystemName(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_CreationClassName(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_CreationClassName(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_CreationClassName(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_DeviceID(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_DeviceID(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_DeviceID(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_PowerManagementSupported(
    ABC_NumericSensor* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->PowerManagementSupported)->value = x;
    ((MI_BooleanField*)&self->PowerManagementSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_PowerManagementSupported(
    ABC_NumericSensor* self)
{
    memset((void*)&self->PowerManagementSupported, 0, sizeof(self->PowerManagementSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_PowerManagementCapabilities(
    ABC_NumericSensor* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_PowerManagementCapabilities(
    ABC_NumericSensor* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_PowerManagementCapabilities(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_Availability(
    ABC_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Availability)->value = x;
    ((MI_Uint16Field*)&self->Availability)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_Availability(
    ABC_NumericSensor* self)
{
    memset((void*)&self->Availability, 0, sizeof(self->Availability));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_StatusInfo(
    ABC_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->StatusInfo)->value = x;
    ((MI_Uint16Field*)&self->StatusInfo)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_StatusInfo(
    ABC_NumericSensor* self)
{
    memset((void*)&self->StatusInfo, 0, sizeof(self->StatusInfo));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_LastErrorCode(
    ABC_NumericSensor* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->LastErrorCode)->value = x;
    ((MI_Uint32Field*)&self->LastErrorCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_LastErrorCode(
    ABC_NumericSensor* self)
{
    memset((void*)&self->LastErrorCode, 0, sizeof(self->LastErrorCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_ErrorDescription(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_ErrorDescription(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_ErrorDescription(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        30);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_ErrorCleared(
    ABC_NumericSensor* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->ErrorCleared)->value = x;
    ((MI_BooleanField*)&self->ErrorCleared)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_ErrorCleared(
    ABC_NumericSensor* self)
{
    memset((void*)&self->ErrorCleared, 0, sizeof(self->ErrorCleared));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_OtherIdentifyingInfo(
    ABC_NumericSensor* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_OtherIdentifyingInfo(
    ABC_NumericSensor* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_OtherIdentifyingInfo(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        32);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_PowerOnHours(
    ABC_NumericSensor* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->PowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->PowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_PowerOnHours(
    ABC_NumericSensor* self)
{
    memset((void*)&self->PowerOnHours, 0, sizeof(self->PowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_TotalPowerOnHours(
    ABC_NumericSensor* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_TotalPowerOnHours(
    ABC_NumericSensor* self)
{
    memset((void*)&self->TotalPowerOnHours, 0, sizeof(self->TotalPowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_IdentifyingDescriptions(
    ABC_NumericSensor* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        35,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_IdentifyingDescriptions(
    ABC_NumericSensor* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        35,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_IdentifyingDescriptions(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        35);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_AdditionalAvailability(
    ABC_NumericSensor* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        36,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_AdditionalAvailability(
    ABC_NumericSensor* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        36,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_AdditionalAvailability(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        36);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_MaxQuiesceTime(
    ABC_NumericSensor* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->value = x;
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_MaxQuiesceTime(
    ABC_NumericSensor* self)
{
    memset((void*)&self->MaxQuiesceTime, 0, sizeof(self->MaxQuiesceTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_SensorType(
    ABC_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->SensorType)->value = x;
    ((MI_Uint16Field*)&self->SensorType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_SensorType(
    ABC_NumericSensor* self)
{
    memset((void*)&self->SensorType, 0, sizeof(self->SensorType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_OtherSensorTypeDescription(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        39,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_OtherSensorTypeDescription(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        39,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_OtherSensorTypeDescription(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        39);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_PossibleStates(
    ABC_NumericSensor* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        40,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_PossibleStates(
    ABC_NumericSensor* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        40,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_PossibleStates(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        40);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_CurrentState(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        41,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_CurrentState(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        41,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_CurrentState(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        41);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_PollingInterval(
    ABC_NumericSensor* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->PollingInterval)->value = x;
    ((MI_Uint64Field*)&self->PollingInterval)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_PollingInterval(
    ABC_NumericSensor* self)
{
    memset((void*)&self->PollingInterval, 0, sizeof(self->PollingInterval));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_SensorContext(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        43,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_SensorContext(
    ABC_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        43,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_SensorContext(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        43);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_BaseUnits(
    ABC_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->BaseUnits)->value = x;
    ((MI_Uint16Field*)&self->BaseUnits)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_BaseUnits(
    ABC_NumericSensor* self)
{
    memset((void*)&self->BaseUnits, 0, sizeof(self->BaseUnits));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_UnitModifier(
    ABC_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->UnitModifier)->value = x;
    ((MI_Sint32Field*)&self->UnitModifier)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_UnitModifier(
    ABC_NumericSensor* self)
{
    memset((void*)&self->UnitModifier, 0, sizeof(self->UnitModifier));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_RateUnits(
    ABC_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RateUnits)->value = x;
    ((MI_Uint16Field*)&self->RateUnits)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_RateUnits(
    ABC_NumericSensor* self)
{
    memset((void*)&self->RateUnits, 0, sizeof(self->RateUnits));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_CurrentReading(
    ABC_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->CurrentReading)->value = x;
    ((MI_Sint32Field*)&self->CurrentReading)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_CurrentReading(
    ABC_NumericSensor* self)
{
    memset((void*)&self->CurrentReading, 0, sizeof(self->CurrentReading));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_NominalReading(
    ABC_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->NominalReading)->value = x;
    ((MI_Sint32Field*)&self->NominalReading)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_NominalReading(
    ABC_NumericSensor* self)
{
    memset((void*)&self->NominalReading, 0, sizeof(self->NominalReading));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_NormalMax(
    ABC_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->NormalMax)->value = x;
    ((MI_Sint32Field*)&self->NormalMax)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_NormalMax(
    ABC_NumericSensor* self)
{
    memset((void*)&self->NormalMax, 0, sizeof(self->NormalMax));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_NormalMin(
    ABC_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->NormalMin)->value = x;
    ((MI_Sint32Field*)&self->NormalMin)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_NormalMin(
    ABC_NumericSensor* self)
{
    memset((void*)&self->NormalMin, 0, sizeof(self->NormalMin));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_MaxReadable(
    ABC_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->MaxReadable)->value = x;
    ((MI_Sint32Field*)&self->MaxReadable)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_MaxReadable(
    ABC_NumericSensor* self)
{
    memset((void*)&self->MaxReadable, 0, sizeof(self->MaxReadable));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_MinReadable(
    ABC_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->MinReadable)->value = x;
    ((MI_Sint32Field*)&self->MinReadable)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_MinReadable(
    ABC_NumericSensor* self)
{
    memset((void*)&self->MinReadable, 0, sizeof(self->MinReadable));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_Resolution(
    ABC_NumericSensor* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Resolution)->value = x;
    ((MI_Uint32Field*)&self->Resolution)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_Resolution(
    ABC_NumericSensor* self)
{
    memset((void*)&self->Resolution, 0, sizeof(self->Resolution));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_Tolerance(
    ABC_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->Tolerance)->value = x;
    ((MI_Sint32Field*)&self->Tolerance)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_Tolerance(
    ABC_NumericSensor* self)
{
    memset((void*)&self->Tolerance, 0, sizeof(self->Tolerance));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_Accuracy(
    ABC_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->Accuracy)->value = x;
    ((MI_Sint32Field*)&self->Accuracy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_Accuracy(
    ABC_NumericSensor* self)
{
    memset((void*)&self->Accuracy, 0, sizeof(self->Accuracy));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_IsLinear(
    ABC_NumericSensor* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->IsLinear)->value = x;
    ((MI_BooleanField*)&self->IsLinear)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_IsLinear(
    ABC_NumericSensor* self)
{
    memset((void*)&self->IsLinear, 0, sizeof(self->IsLinear));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_Hysteresis(
    ABC_NumericSensor* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Hysteresis)->value = x;
    ((MI_Uint32Field*)&self->Hysteresis)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_Hysteresis(
    ABC_NumericSensor* self)
{
    memset((void*)&self->Hysteresis, 0, sizeof(self->Hysteresis));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_LowerThresholdNonCritical(
    ABC_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->LowerThresholdNonCritical)->value = x;
    ((MI_Sint32Field*)&self->LowerThresholdNonCritical)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_LowerThresholdNonCritical(
    ABC_NumericSensor* self)
{
    memset((void*)&self->LowerThresholdNonCritical, 0, sizeof(self->LowerThresholdNonCritical));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_UpperThresholdNonCritical(
    ABC_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->UpperThresholdNonCritical)->value = x;
    ((MI_Sint32Field*)&self->UpperThresholdNonCritical)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_UpperThresholdNonCritical(
    ABC_NumericSensor* self)
{
    memset((void*)&self->UpperThresholdNonCritical, 0, sizeof(self->UpperThresholdNonCritical));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_LowerThresholdCritical(
    ABC_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->LowerThresholdCritical)->value = x;
    ((MI_Sint32Field*)&self->LowerThresholdCritical)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_LowerThresholdCritical(
    ABC_NumericSensor* self)
{
    memset((void*)&self->LowerThresholdCritical, 0, sizeof(self->LowerThresholdCritical));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_UpperThresholdCritical(
    ABC_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->UpperThresholdCritical)->value = x;
    ((MI_Sint32Field*)&self->UpperThresholdCritical)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_UpperThresholdCritical(
    ABC_NumericSensor* self)
{
    memset((void*)&self->UpperThresholdCritical, 0, sizeof(self->UpperThresholdCritical));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_LowerThresholdFatal(
    ABC_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->LowerThresholdFatal)->value = x;
    ((MI_Sint32Field*)&self->LowerThresholdFatal)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_LowerThresholdFatal(
    ABC_NumericSensor* self)
{
    memset((void*)&self->LowerThresholdFatal, 0, sizeof(self->LowerThresholdFatal));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_UpperThresholdFatal(
    ABC_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->UpperThresholdFatal)->value = x;
    ((MI_Sint32Field*)&self->UpperThresholdFatal)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_UpperThresholdFatal(
    ABC_NumericSensor* self)
{
    memset((void*)&self->UpperThresholdFatal, 0, sizeof(self->UpperThresholdFatal));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_SupportedThresholds(
    ABC_NumericSensor* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        64,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_SupportedThresholds(
    ABC_NumericSensor* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        64,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_SupportedThresholds(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        64);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_EnabledThresholds(
    ABC_NumericSensor* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        65,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_EnabledThresholds(
    ABC_NumericSensor* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        65,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_EnabledThresholds(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        65);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Set_SettableThresholds(
    ABC_NumericSensor* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        66,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPtr_SettableThresholds(
    ABC_NumericSensor* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        66,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Clear_SettableThresholds(
    ABC_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        66);
}

/*
**==============================================================================
**
** ABC_NumericSensor.RequestStateChange()
**
**==============================================================================
*/

typedef struct _ABC_NumericSensor_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
ABC_NumericSensor_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_NumericSensor_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RequestStateChange_Construct(
    ABC_NumericSensor_RequestStateChange* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_NumericSensor_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RequestStateChange_Clone(
    const ABC_NumericSensor_RequestStateChange* self,
    ABC_NumericSensor_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RequestStateChange_Destruct(
    ABC_NumericSensor_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RequestStateChange_Delete(
    ABC_NumericSensor_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RequestStateChange_Post(
    const ABC_NumericSensor_RequestStateChange* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RequestStateChange_Set_MIReturn(
    ABC_NumericSensor_RequestStateChange* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RequestStateChange_Clear_MIReturn(
    ABC_NumericSensor_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RequestStateChange_Set_RequestedState(
    ABC_NumericSensor_RequestStateChange* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RequestStateChange_Clear_RequestedState(
    ABC_NumericSensor_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RequestStateChange_Set_Job(
    ABC_NumericSensor_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RequestStateChange_SetPtr_Job(
    ABC_NumericSensor_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RequestStateChange_Clear_Job(
    ABC_NumericSensor_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RequestStateChange_Set_TimeoutPeriod(
    ABC_NumericSensor_RequestStateChange* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RequestStateChange_Clear_TimeoutPeriod(
    ABC_NumericSensor_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_NumericSensor.SetPowerState()
**
**==============================================================================
*/

typedef struct _ABC_NumericSensor_SetPowerState
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field PowerState;
    /*IN*/ MI_ConstDatetimeField Time;
}
ABC_NumericSensor_SetPowerState;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_NumericSensor_SetPowerState_rtti;

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPowerState_Construct(
    ABC_NumericSensor_SetPowerState* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_NumericSensor_SetPowerState_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPowerState_Clone(
    const ABC_NumericSensor_SetPowerState* self,
    ABC_NumericSensor_SetPowerState** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPowerState_Destruct(
    ABC_NumericSensor_SetPowerState* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPowerState_Delete(
    ABC_NumericSensor_SetPowerState* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPowerState_Post(
    const ABC_NumericSensor_SetPowerState* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPowerState_Set_MIReturn(
    ABC_NumericSensor_SetPowerState* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPowerState_Clear_MIReturn(
    ABC_NumericSensor_SetPowerState* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPowerState_Set_PowerState(
    ABC_NumericSensor_SetPowerState* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PowerState)->value = x;
    ((MI_Uint16Field*)&self->PowerState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPowerState_Clear_PowerState(
    ABC_NumericSensor_SetPowerState* self)
{
    memset((void*)&self->PowerState, 0, sizeof(self->PowerState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPowerState_Set_Time(
    ABC_NumericSensor_SetPowerState* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->Time)->value = x;
    ((MI_DatetimeField*)&self->Time)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SetPowerState_Clear_Time(
    ABC_NumericSensor_SetPowerState* self)
{
    memset((void*)&self->Time, 0, sizeof(self->Time));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_NumericSensor.Reset()
**
**==============================================================================
*/

typedef struct _ABC_NumericSensor_Reset
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
ABC_NumericSensor_Reset;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_NumericSensor_Reset_rtti;

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Reset_Construct(
    ABC_NumericSensor_Reset* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_NumericSensor_Reset_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Reset_Clone(
    const ABC_NumericSensor_Reset* self,
    ABC_NumericSensor_Reset** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Reset_Destruct(
    ABC_NumericSensor_Reset* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Reset_Delete(
    ABC_NumericSensor_Reset* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Reset_Post(
    const ABC_NumericSensor_Reset* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Reset_Set_MIReturn(
    ABC_NumericSensor_Reset* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_Reset_Clear_MIReturn(
    ABC_NumericSensor_Reset* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_NumericSensor.EnableDevice()
**
**==============================================================================
*/

typedef struct _ABC_NumericSensor_EnableDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Enabled;
}
ABC_NumericSensor_EnableDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_NumericSensor_EnableDevice_rtti;

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_EnableDevice_Construct(
    ABC_NumericSensor_EnableDevice* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_NumericSensor_EnableDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_EnableDevice_Clone(
    const ABC_NumericSensor_EnableDevice* self,
    ABC_NumericSensor_EnableDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_EnableDevice_Destruct(
    ABC_NumericSensor_EnableDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_EnableDevice_Delete(
    ABC_NumericSensor_EnableDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_EnableDevice_Post(
    const ABC_NumericSensor_EnableDevice* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_EnableDevice_Set_MIReturn(
    ABC_NumericSensor_EnableDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_EnableDevice_Clear_MIReturn(
    ABC_NumericSensor_EnableDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_EnableDevice_Set_Enabled(
    ABC_NumericSensor_EnableDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Enabled)->value = x;
    ((MI_BooleanField*)&self->Enabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_EnableDevice_Clear_Enabled(
    ABC_NumericSensor_EnableDevice* self)
{
    memset((void*)&self->Enabled, 0, sizeof(self->Enabled));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_NumericSensor.OnlineDevice()
**
**==============================================================================
*/

typedef struct _ABC_NumericSensor_OnlineDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Online;
}
ABC_NumericSensor_OnlineDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_NumericSensor_OnlineDevice_rtti;

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_OnlineDevice_Construct(
    ABC_NumericSensor_OnlineDevice* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_NumericSensor_OnlineDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_OnlineDevice_Clone(
    const ABC_NumericSensor_OnlineDevice* self,
    ABC_NumericSensor_OnlineDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_OnlineDevice_Destruct(
    ABC_NumericSensor_OnlineDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_OnlineDevice_Delete(
    ABC_NumericSensor_OnlineDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_OnlineDevice_Post(
    const ABC_NumericSensor_OnlineDevice* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_OnlineDevice_Set_MIReturn(
    ABC_NumericSensor_OnlineDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_OnlineDevice_Clear_MIReturn(
    ABC_NumericSensor_OnlineDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_OnlineDevice_Set_Online(
    ABC_NumericSensor_OnlineDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Online)->value = x;
    ((MI_BooleanField*)&self->Online)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_OnlineDevice_Clear_Online(
    ABC_NumericSensor_OnlineDevice* self)
{
    memset((void*)&self->Online, 0, sizeof(self->Online));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_NumericSensor.QuiesceDevice()
**
**==============================================================================
*/

typedef struct _ABC_NumericSensor_QuiesceDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Quiesce;
}
ABC_NumericSensor_QuiesceDevice;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_NumericSensor_QuiesceDevice_rtti;

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_QuiesceDevice_Construct(
    ABC_NumericSensor_QuiesceDevice* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_NumericSensor_QuiesceDevice_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_QuiesceDevice_Clone(
    const ABC_NumericSensor_QuiesceDevice* self,
    ABC_NumericSensor_QuiesceDevice** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_QuiesceDevice_Destruct(
    ABC_NumericSensor_QuiesceDevice* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_QuiesceDevice_Delete(
    ABC_NumericSensor_QuiesceDevice* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_QuiesceDevice_Post(
    const ABC_NumericSensor_QuiesceDevice* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_QuiesceDevice_Set_MIReturn(
    ABC_NumericSensor_QuiesceDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_QuiesceDevice_Clear_MIReturn(
    ABC_NumericSensor_QuiesceDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_QuiesceDevice_Set_Quiesce(
    ABC_NumericSensor_QuiesceDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Quiesce)->value = x;
    ((MI_BooleanField*)&self->Quiesce)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_QuiesceDevice_Clear_Quiesce(
    ABC_NumericSensor_QuiesceDevice* self)
{
    memset((void*)&self->Quiesce, 0, sizeof(self->Quiesce));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_NumericSensor.SaveProperties()
**
**==============================================================================
*/

typedef struct _ABC_NumericSensor_SaveProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
ABC_NumericSensor_SaveProperties;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_NumericSensor_SaveProperties_rtti;

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SaveProperties_Construct(
    ABC_NumericSensor_SaveProperties* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_NumericSensor_SaveProperties_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SaveProperties_Clone(
    const ABC_NumericSensor_SaveProperties* self,
    ABC_NumericSensor_SaveProperties** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SaveProperties_Destruct(
    ABC_NumericSensor_SaveProperties* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SaveProperties_Delete(
    ABC_NumericSensor_SaveProperties* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SaveProperties_Post(
    const ABC_NumericSensor_SaveProperties* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SaveProperties_Set_MIReturn(
    ABC_NumericSensor_SaveProperties* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_SaveProperties_Clear_MIReturn(
    ABC_NumericSensor_SaveProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_NumericSensor.RestoreProperties()
**
**==============================================================================
*/

typedef struct _ABC_NumericSensor_RestoreProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
ABC_NumericSensor_RestoreProperties;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_NumericSensor_RestoreProperties_rtti;

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RestoreProperties_Construct(
    ABC_NumericSensor_RestoreProperties* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_NumericSensor_RestoreProperties_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RestoreProperties_Clone(
    const ABC_NumericSensor_RestoreProperties* self,
    ABC_NumericSensor_RestoreProperties** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RestoreProperties_Destruct(
    ABC_NumericSensor_RestoreProperties* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RestoreProperties_Delete(
    ABC_NumericSensor_RestoreProperties* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RestoreProperties_Post(
    const ABC_NumericSensor_RestoreProperties* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RestoreProperties_Set_MIReturn(
    ABC_NumericSensor_RestoreProperties* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RestoreProperties_Clear_MIReturn(
    ABC_NumericSensor_RestoreProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_NumericSensor.RestoreDefaultThresholds()
**
**==============================================================================
*/

typedef struct _ABC_NumericSensor_RestoreDefaultThresholds
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
ABC_NumericSensor_RestoreDefaultThresholds;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_NumericSensor_RestoreDefaultThresholds_rtti;

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RestoreDefaultThresholds_Construct(
    ABC_NumericSensor_RestoreDefaultThresholds* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_NumericSensor_RestoreDefaultThresholds_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RestoreDefaultThresholds_Clone(
    const ABC_NumericSensor_RestoreDefaultThresholds* self,
    ABC_NumericSensor_RestoreDefaultThresholds** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RestoreDefaultThresholds_Destruct(
    ABC_NumericSensor_RestoreDefaultThresholds* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RestoreDefaultThresholds_Delete(
    ABC_NumericSensor_RestoreDefaultThresholds* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RestoreDefaultThresholds_Post(
    const ABC_NumericSensor_RestoreDefaultThresholds* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RestoreDefaultThresholds_Set_MIReturn(
    ABC_NumericSensor_RestoreDefaultThresholds* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_RestoreDefaultThresholds_Clear_MIReturn(
    ABC_NumericSensor_RestoreDefaultThresholds* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_NumericSensor.GetNonLinearFactors()
**
**==============================================================================
*/

typedef struct _ABC_NumericSensor_GetNonLinearFactors
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstSint32Field SensorReading;
    /*OUT*/ MI_ConstSint32Field Accuracy;
    /*OUT*/ MI_ConstUint32Field Resolution;
    /*OUT*/ MI_ConstSint32Field Tolerance;
    /*OUT*/ MI_ConstUint32Field Hysteresis;
}
ABC_NumericSensor_GetNonLinearFactors;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_NumericSensor_GetNonLinearFactors_rtti;

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_GetNonLinearFactors_Construct(
    ABC_NumericSensor_GetNonLinearFactors* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_NumericSensor_GetNonLinearFactors_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_GetNonLinearFactors_Clone(
    const ABC_NumericSensor_GetNonLinearFactors* self,
    ABC_NumericSensor_GetNonLinearFactors** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_GetNonLinearFactors_Destruct(
    ABC_NumericSensor_GetNonLinearFactors* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_GetNonLinearFactors_Delete(
    ABC_NumericSensor_GetNonLinearFactors* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_GetNonLinearFactors_Post(
    const ABC_NumericSensor_GetNonLinearFactors* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_GetNonLinearFactors_Set_MIReturn(
    ABC_NumericSensor_GetNonLinearFactors* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_GetNonLinearFactors_Clear_MIReturn(
    ABC_NumericSensor_GetNonLinearFactors* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_GetNonLinearFactors_Set_SensorReading(
    ABC_NumericSensor_GetNonLinearFactors* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->SensorReading)->value = x;
    ((MI_Sint32Field*)&self->SensorReading)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_GetNonLinearFactors_Clear_SensorReading(
    ABC_NumericSensor_GetNonLinearFactors* self)
{
    memset((void*)&self->SensorReading, 0, sizeof(self->SensorReading));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_GetNonLinearFactors_Set_Accuracy(
    ABC_NumericSensor_GetNonLinearFactors* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->Accuracy)->value = x;
    ((MI_Sint32Field*)&self->Accuracy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_GetNonLinearFactors_Clear_Accuracy(
    ABC_NumericSensor_GetNonLinearFactors* self)
{
    memset((void*)&self->Accuracy, 0, sizeof(self->Accuracy));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_GetNonLinearFactors_Set_Resolution(
    ABC_NumericSensor_GetNonLinearFactors* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Resolution)->value = x;
    ((MI_Uint32Field*)&self->Resolution)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_GetNonLinearFactors_Clear_Resolution(
    ABC_NumericSensor_GetNonLinearFactors* self)
{
    memset((void*)&self->Resolution, 0, sizeof(self->Resolution));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_GetNonLinearFactors_Set_Tolerance(
    ABC_NumericSensor_GetNonLinearFactors* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->Tolerance)->value = x;
    ((MI_Sint32Field*)&self->Tolerance)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_GetNonLinearFactors_Clear_Tolerance(
    ABC_NumericSensor_GetNonLinearFactors* self)
{
    memset((void*)&self->Tolerance, 0, sizeof(self->Tolerance));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_GetNonLinearFactors_Set_Hysteresis(
    ABC_NumericSensor_GetNonLinearFactors* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Hysteresis)->value = x;
    ((MI_Uint32Field*)&self->Hysteresis)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_NumericSensor_GetNonLinearFactors_Clear_Hysteresis(
    ABC_NumericSensor_GetNonLinearFactors* self)
{
    memset((void*)&self->Hysteresis, 0, sizeof(self->Hysteresis));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** ABC_NumericSensor provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_NumericSensor_Self ABC_NumericSensor_Self;

MI_EXTERN_C void MI_CALL ABC_NumericSensor_Load(
    ABC_NumericSensor_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_NumericSensor_Unload(
    ABC_NumericSensor_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_NumericSensor_EnumerateInstances(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_NumericSensor_GetInstance(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_NumericSensor* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_NumericSensor_CreateInstance(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_NumericSensor* newInstance);

MI_EXTERN_C void MI_CALL ABC_NumericSensor_ModifyInstance(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_NumericSensor* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_NumericSensor_DeleteInstance(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_NumericSensor* instanceName);

MI_EXTERN_C void MI_CALL ABC_NumericSensor_Invoke_RequestStateChange(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_RequestStateChange* in);

MI_EXTERN_C void MI_CALL ABC_NumericSensor_Invoke_SetPowerState(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_SetPowerState* in);

MI_EXTERN_C void MI_CALL ABC_NumericSensor_Invoke_Reset(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_Reset* in);

MI_EXTERN_C void MI_CALL ABC_NumericSensor_Invoke_EnableDevice(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_EnableDevice* in);

MI_EXTERN_C void MI_CALL ABC_NumericSensor_Invoke_OnlineDevice(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_OnlineDevice* in);

MI_EXTERN_C void MI_CALL ABC_NumericSensor_Invoke_QuiesceDevice(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_QuiesceDevice* in);

MI_EXTERN_C void MI_CALL ABC_NumericSensor_Invoke_SaveProperties(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_SaveProperties* in);

MI_EXTERN_C void MI_CALL ABC_NumericSensor_Invoke_RestoreProperties(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_RestoreProperties* in);

MI_EXTERN_C void MI_CALL ABC_NumericSensor_Invoke_RestoreDefaultThresholds(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_RestoreDefaultThresholds* in);

MI_EXTERN_C void MI_CALL ABC_NumericSensor_Invoke_GetNonLinearFactors(
    ABC_NumericSensor_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_NumericSensor* instanceName,
    const ABC_NumericSensor_GetNonLinearFactors* in);


#endif /* _ABC_NumericSensor_h */
