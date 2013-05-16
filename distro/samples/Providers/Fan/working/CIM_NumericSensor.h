/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_NumericSensor_h
#define _CIM_NumericSensor_h

#include <MI.h>
#include "CIM_Sensor.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** CIM_NumericSensor [CIM_NumericSensor]
**
** Keys:
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**    DeviceID
**
**==============================================================================
*/

typedef struct _CIM_NumericSensor /* extends CIM_Sensor */
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
}
CIM_NumericSensor;

typedef struct _CIM_NumericSensor_Ref
{
    CIM_NumericSensor* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NumericSensor_Ref;

typedef struct _CIM_NumericSensor_ConstRef
{
    MI_CONST CIM_NumericSensor* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NumericSensor_ConstRef;

typedef struct _CIM_NumericSensor_Array
{
    struct _CIM_NumericSensor** data;
    MI_Uint32 size;
}
CIM_NumericSensor_Array;

typedef struct _CIM_NumericSensor_ConstArray
{
    struct _CIM_NumericSensor MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_NumericSensor_ConstArray;

typedef struct _CIM_NumericSensor_ArrayRef
{
    CIM_NumericSensor_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NumericSensor_ArrayRef;

typedef struct _CIM_NumericSensor_ConstArrayRef
{
    CIM_NumericSensor_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NumericSensor_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_NumericSensor_rtti;

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Construct(
    CIM_NumericSensor* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_NumericSensor_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clone(
    const CIM_NumericSensor* self,
    CIM_NumericSensor** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_NumericSensor_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_NumericSensor_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Destruct(CIM_NumericSensor* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Delete(CIM_NumericSensor* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Post(
    const CIM_NumericSensor* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_InstanceID(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_InstanceID(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_InstanceID(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_Caption(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_Caption(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_Caption(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_Description(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_Description(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_Description(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_ElementName(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_ElementName(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_ElementName(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_InstallDate(
    CIM_NumericSensor* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_InstallDate(
    CIM_NumericSensor* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_Name(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_Name(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_Name(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_OperationalStatus(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_OperationalStatus(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_OperationalStatus(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_StatusDescriptions(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_StatusDescriptions(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_StatusDescriptions(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_Status(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_Status(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_Status(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_HealthState(
    CIM_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_HealthState(
    CIM_NumericSensor* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_CommunicationStatus(
    CIM_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_CommunicationStatus(
    CIM_NumericSensor* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_DetailedStatus(
    CIM_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_DetailedStatus(
    CIM_NumericSensor* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_OperatingStatus(
    CIM_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_OperatingStatus(
    CIM_NumericSensor* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_PrimaryStatus(
    CIM_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_PrimaryStatus(
    CIM_NumericSensor* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_EnabledState(
    CIM_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_EnabledState(
    CIM_NumericSensor* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_OtherEnabledState(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_OtherEnabledState(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_OtherEnabledState(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_RequestedState(
    CIM_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_RequestedState(
    CIM_NumericSensor* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_EnabledDefault(
    CIM_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_EnabledDefault(
    CIM_NumericSensor* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_TimeOfLastStateChange(
    CIM_NumericSensor* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_TimeOfLastStateChange(
    CIM_NumericSensor* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_AvailableRequestedStates(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_AvailableRequestedStates(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_AvailableRequestedStates(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_TransitioningToState(
    CIM_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_TransitioningToState(
    CIM_NumericSensor* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_SystemCreationClassName(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_SystemCreationClassName(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_SystemCreationClassName(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_SystemName(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_SystemName(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_SystemName(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_CreationClassName(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_CreationClassName(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_CreationClassName(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_DeviceID(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_DeviceID(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_DeviceID(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_PowerManagementSupported(
    CIM_NumericSensor* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->PowerManagementSupported)->value = x;
    ((MI_BooleanField*)&self->PowerManagementSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_PowerManagementSupported(
    CIM_NumericSensor* self)
{
    memset((void*)&self->PowerManagementSupported, 0, sizeof(self->PowerManagementSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_PowerManagementCapabilities(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_PowerManagementCapabilities(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_PowerManagementCapabilities(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_Availability(
    CIM_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Availability)->value = x;
    ((MI_Uint16Field*)&self->Availability)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_Availability(
    CIM_NumericSensor* self)
{
    memset((void*)&self->Availability, 0, sizeof(self->Availability));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_StatusInfo(
    CIM_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->StatusInfo)->value = x;
    ((MI_Uint16Field*)&self->StatusInfo)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_StatusInfo(
    CIM_NumericSensor* self)
{
    memset((void*)&self->StatusInfo, 0, sizeof(self->StatusInfo));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_LastErrorCode(
    CIM_NumericSensor* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->LastErrorCode)->value = x;
    ((MI_Uint32Field*)&self->LastErrorCode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_LastErrorCode(
    CIM_NumericSensor* self)
{
    memset((void*)&self->LastErrorCode, 0, sizeof(self->LastErrorCode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_ErrorDescription(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_ErrorDescription(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_ErrorDescription(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        30);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_ErrorCleared(
    CIM_NumericSensor* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->ErrorCleared)->value = x;
    ((MI_BooleanField*)&self->ErrorCleared)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_ErrorCleared(
    CIM_NumericSensor* self)
{
    memset((void*)&self->ErrorCleared, 0, sizeof(self->ErrorCleared));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_OtherIdentifyingInfo(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_OtherIdentifyingInfo(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_OtherIdentifyingInfo(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        32);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_PowerOnHours(
    CIM_NumericSensor* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->PowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->PowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_PowerOnHours(
    CIM_NumericSensor* self)
{
    memset((void*)&self->PowerOnHours, 0, sizeof(self->PowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_TotalPowerOnHours(
    CIM_NumericSensor* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->value = x;
    ((MI_Uint64Field*)&self->TotalPowerOnHours)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_TotalPowerOnHours(
    CIM_NumericSensor* self)
{
    memset((void*)&self->TotalPowerOnHours, 0, sizeof(self->TotalPowerOnHours));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_IdentifyingDescriptions(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_IdentifyingDescriptions(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_IdentifyingDescriptions(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        35);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_AdditionalAvailability(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_AdditionalAvailability(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_AdditionalAvailability(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        36);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_MaxQuiesceTime(
    CIM_NumericSensor* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->value = x;
    ((MI_Uint64Field*)&self->MaxQuiesceTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_MaxQuiesceTime(
    CIM_NumericSensor* self)
{
    memset((void*)&self->MaxQuiesceTime, 0, sizeof(self->MaxQuiesceTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_SensorType(
    CIM_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->SensorType)->value = x;
    ((MI_Uint16Field*)&self->SensorType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_SensorType(
    CIM_NumericSensor* self)
{
    memset((void*)&self->SensorType, 0, sizeof(self->SensorType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_OtherSensorTypeDescription(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        39,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_OtherSensorTypeDescription(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        39,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_OtherSensorTypeDescription(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        39);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_PossibleStates(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_PossibleStates(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_PossibleStates(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        40);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_CurrentState(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        41,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_CurrentState(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        41,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_CurrentState(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        41);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_PollingInterval(
    CIM_NumericSensor* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->PollingInterval)->value = x;
    ((MI_Uint64Field*)&self->PollingInterval)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_PollingInterval(
    CIM_NumericSensor* self)
{
    memset((void*)&self->PollingInterval, 0, sizeof(self->PollingInterval));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_SensorContext(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        43,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_SensorContext(
    CIM_NumericSensor* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        43,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_SensorContext(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        43);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_BaseUnits(
    CIM_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->BaseUnits)->value = x;
    ((MI_Uint16Field*)&self->BaseUnits)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_BaseUnits(
    CIM_NumericSensor* self)
{
    memset((void*)&self->BaseUnits, 0, sizeof(self->BaseUnits));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_UnitModifier(
    CIM_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->UnitModifier)->value = x;
    ((MI_Sint32Field*)&self->UnitModifier)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_UnitModifier(
    CIM_NumericSensor* self)
{
    memset((void*)&self->UnitModifier, 0, sizeof(self->UnitModifier));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_RateUnits(
    CIM_NumericSensor* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RateUnits)->value = x;
    ((MI_Uint16Field*)&self->RateUnits)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_RateUnits(
    CIM_NumericSensor* self)
{
    memset((void*)&self->RateUnits, 0, sizeof(self->RateUnits));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_CurrentReading(
    CIM_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->CurrentReading)->value = x;
    ((MI_Sint32Field*)&self->CurrentReading)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_CurrentReading(
    CIM_NumericSensor* self)
{
    memset((void*)&self->CurrentReading, 0, sizeof(self->CurrentReading));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_NominalReading(
    CIM_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->NominalReading)->value = x;
    ((MI_Sint32Field*)&self->NominalReading)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_NominalReading(
    CIM_NumericSensor* self)
{
    memset((void*)&self->NominalReading, 0, sizeof(self->NominalReading));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_NormalMax(
    CIM_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->NormalMax)->value = x;
    ((MI_Sint32Field*)&self->NormalMax)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_NormalMax(
    CIM_NumericSensor* self)
{
    memset((void*)&self->NormalMax, 0, sizeof(self->NormalMax));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_NormalMin(
    CIM_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->NormalMin)->value = x;
    ((MI_Sint32Field*)&self->NormalMin)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_NormalMin(
    CIM_NumericSensor* self)
{
    memset((void*)&self->NormalMin, 0, sizeof(self->NormalMin));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_MaxReadable(
    CIM_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->MaxReadable)->value = x;
    ((MI_Sint32Field*)&self->MaxReadable)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_MaxReadable(
    CIM_NumericSensor* self)
{
    memset((void*)&self->MaxReadable, 0, sizeof(self->MaxReadable));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_MinReadable(
    CIM_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->MinReadable)->value = x;
    ((MI_Sint32Field*)&self->MinReadable)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_MinReadable(
    CIM_NumericSensor* self)
{
    memset((void*)&self->MinReadable, 0, sizeof(self->MinReadable));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_Resolution(
    CIM_NumericSensor* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Resolution)->value = x;
    ((MI_Uint32Field*)&self->Resolution)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_Resolution(
    CIM_NumericSensor* self)
{
    memset((void*)&self->Resolution, 0, sizeof(self->Resolution));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_Tolerance(
    CIM_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->Tolerance)->value = x;
    ((MI_Sint32Field*)&self->Tolerance)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_Tolerance(
    CIM_NumericSensor* self)
{
    memset((void*)&self->Tolerance, 0, sizeof(self->Tolerance));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_Accuracy(
    CIM_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->Accuracy)->value = x;
    ((MI_Sint32Field*)&self->Accuracy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_Accuracy(
    CIM_NumericSensor* self)
{
    memset((void*)&self->Accuracy, 0, sizeof(self->Accuracy));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_IsLinear(
    CIM_NumericSensor* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->IsLinear)->value = x;
    ((MI_BooleanField*)&self->IsLinear)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_IsLinear(
    CIM_NumericSensor* self)
{
    memset((void*)&self->IsLinear, 0, sizeof(self->IsLinear));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_Hysteresis(
    CIM_NumericSensor* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Hysteresis)->value = x;
    ((MI_Uint32Field*)&self->Hysteresis)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_Hysteresis(
    CIM_NumericSensor* self)
{
    memset((void*)&self->Hysteresis, 0, sizeof(self->Hysteresis));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_LowerThresholdNonCritical(
    CIM_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->LowerThresholdNonCritical)->value = x;
    ((MI_Sint32Field*)&self->LowerThresholdNonCritical)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_LowerThresholdNonCritical(
    CIM_NumericSensor* self)
{
    memset((void*)&self->LowerThresholdNonCritical, 0, sizeof(self->LowerThresholdNonCritical));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_UpperThresholdNonCritical(
    CIM_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->UpperThresholdNonCritical)->value = x;
    ((MI_Sint32Field*)&self->UpperThresholdNonCritical)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_UpperThresholdNonCritical(
    CIM_NumericSensor* self)
{
    memset((void*)&self->UpperThresholdNonCritical, 0, sizeof(self->UpperThresholdNonCritical));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_LowerThresholdCritical(
    CIM_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->LowerThresholdCritical)->value = x;
    ((MI_Sint32Field*)&self->LowerThresholdCritical)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_LowerThresholdCritical(
    CIM_NumericSensor* self)
{
    memset((void*)&self->LowerThresholdCritical, 0, sizeof(self->LowerThresholdCritical));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_UpperThresholdCritical(
    CIM_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->UpperThresholdCritical)->value = x;
    ((MI_Sint32Field*)&self->UpperThresholdCritical)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_UpperThresholdCritical(
    CIM_NumericSensor* self)
{
    memset((void*)&self->UpperThresholdCritical, 0, sizeof(self->UpperThresholdCritical));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_LowerThresholdFatal(
    CIM_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->LowerThresholdFatal)->value = x;
    ((MI_Sint32Field*)&self->LowerThresholdFatal)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_LowerThresholdFatal(
    CIM_NumericSensor* self)
{
    memset((void*)&self->LowerThresholdFatal, 0, sizeof(self->LowerThresholdFatal));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_UpperThresholdFatal(
    CIM_NumericSensor* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->UpperThresholdFatal)->value = x;
    ((MI_Sint32Field*)&self->UpperThresholdFatal)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_UpperThresholdFatal(
    CIM_NumericSensor* self)
{
    memset((void*)&self->UpperThresholdFatal, 0, sizeof(self->UpperThresholdFatal));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_SupportedThresholds(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_SupportedThresholds(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_SupportedThresholds(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        64);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_EnabledThresholds(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_EnabledThresholds(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_EnabledThresholds(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        65);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Set_SettableThresholds(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPtr_SettableThresholds(
    CIM_NumericSensor* self,
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

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Clear_SettableThresholds(
    CIM_NumericSensor* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        66);
}

/*
**==============================================================================
**
** CIM_NumericSensor.RequestStateChange()
**
**==============================================================================
*/

typedef struct _CIM_NumericSensor_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
CIM_NumericSensor_RequestStateChange;

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RequestStateChange_Set_MIReturn(
    CIM_NumericSensor_RequestStateChange* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RequestStateChange_Clear_MIReturn(
    CIM_NumericSensor_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RequestStateChange_Set_RequestedState(
    CIM_NumericSensor_RequestStateChange* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RequestStateChange_Clear_RequestedState(
    CIM_NumericSensor_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RequestStateChange_Set_Job(
    CIM_NumericSensor_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RequestStateChange_SetPtr_Job(
    CIM_NumericSensor_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RequestStateChange_Clear_Job(
    CIM_NumericSensor_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RequestStateChange_Set_TimeoutPeriod(
    CIM_NumericSensor_RequestStateChange* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RequestStateChange_Clear_TimeoutPeriod(
    CIM_NumericSensor_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NumericSensor.SetPowerState()
**
**==============================================================================
*/

typedef struct _CIM_NumericSensor_SetPowerState
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field PowerState;
    /*IN*/ MI_ConstDatetimeField Time;
}
CIM_NumericSensor_SetPowerState;

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPowerState_Set_MIReturn(
    CIM_NumericSensor_SetPowerState* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPowerState_Clear_MIReturn(
    CIM_NumericSensor_SetPowerState* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPowerState_Set_PowerState(
    CIM_NumericSensor_SetPowerState* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PowerState)->value = x;
    ((MI_Uint16Field*)&self->PowerState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPowerState_Clear_PowerState(
    CIM_NumericSensor_SetPowerState* self)
{
    memset((void*)&self->PowerState, 0, sizeof(self->PowerState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPowerState_Set_Time(
    CIM_NumericSensor_SetPowerState* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->Time)->value = x;
    ((MI_DatetimeField*)&self->Time)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SetPowerState_Clear_Time(
    CIM_NumericSensor_SetPowerState* self)
{
    memset((void*)&self->Time, 0, sizeof(self->Time));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NumericSensor.Reset()
**
**==============================================================================
*/

typedef struct _CIM_NumericSensor_Reset
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
CIM_NumericSensor_Reset;

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Reset_Set_MIReturn(
    CIM_NumericSensor_Reset* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_Reset_Clear_MIReturn(
    CIM_NumericSensor_Reset* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NumericSensor.EnableDevice()
**
**==============================================================================
*/

typedef struct _CIM_NumericSensor_EnableDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Enabled;
}
CIM_NumericSensor_EnableDevice;

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_EnableDevice_Set_MIReturn(
    CIM_NumericSensor_EnableDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_EnableDevice_Clear_MIReturn(
    CIM_NumericSensor_EnableDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_EnableDevice_Set_Enabled(
    CIM_NumericSensor_EnableDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Enabled)->value = x;
    ((MI_BooleanField*)&self->Enabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_EnableDevice_Clear_Enabled(
    CIM_NumericSensor_EnableDevice* self)
{
    memset((void*)&self->Enabled, 0, sizeof(self->Enabled));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NumericSensor.OnlineDevice()
**
**==============================================================================
*/

typedef struct _CIM_NumericSensor_OnlineDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Online;
}
CIM_NumericSensor_OnlineDevice;

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_OnlineDevice_Set_MIReturn(
    CIM_NumericSensor_OnlineDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_OnlineDevice_Clear_MIReturn(
    CIM_NumericSensor_OnlineDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_OnlineDevice_Set_Online(
    CIM_NumericSensor_OnlineDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Online)->value = x;
    ((MI_BooleanField*)&self->Online)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_OnlineDevice_Clear_Online(
    CIM_NumericSensor_OnlineDevice* self)
{
    memset((void*)&self->Online, 0, sizeof(self->Online));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NumericSensor.QuiesceDevice()
**
**==============================================================================
*/

typedef struct _CIM_NumericSensor_QuiesceDevice
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstBooleanField Quiesce;
}
CIM_NumericSensor_QuiesceDevice;

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_QuiesceDevice_Set_MIReturn(
    CIM_NumericSensor_QuiesceDevice* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_QuiesceDevice_Clear_MIReturn(
    CIM_NumericSensor_QuiesceDevice* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_QuiesceDevice_Set_Quiesce(
    CIM_NumericSensor_QuiesceDevice* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Quiesce)->value = x;
    ((MI_BooleanField*)&self->Quiesce)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_QuiesceDevice_Clear_Quiesce(
    CIM_NumericSensor_QuiesceDevice* self)
{
    memset((void*)&self->Quiesce, 0, sizeof(self->Quiesce));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NumericSensor.SaveProperties()
**
**==============================================================================
*/

typedef struct _CIM_NumericSensor_SaveProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
CIM_NumericSensor_SaveProperties;

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SaveProperties_Set_MIReturn(
    CIM_NumericSensor_SaveProperties* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_SaveProperties_Clear_MIReturn(
    CIM_NumericSensor_SaveProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NumericSensor.RestoreProperties()
**
**==============================================================================
*/

typedef struct _CIM_NumericSensor_RestoreProperties
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
CIM_NumericSensor_RestoreProperties;

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RestoreProperties_Set_MIReturn(
    CIM_NumericSensor_RestoreProperties* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RestoreProperties_Clear_MIReturn(
    CIM_NumericSensor_RestoreProperties* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NumericSensor.RestoreDefaultThresholds()
**
**==============================================================================
*/

typedef struct _CIM_NumericSensor_RestoreDefaultThresholds
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
}
CIM_NumericSensor_RestoreDefaultThresholds;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_NumericSensor_RestoreDefaultThresholds_rtti;

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RestoreDefaultThresholds_Construct(
    CIM_NumericSensor_RestoreDefaultThresholds* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &CIM_NumericSensor_RestoreDefaultThresholds_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RestoreDefaultThresholds_Clone(
    const CIM_NumericSensor_RestoreDefaultThresholds* self,
    CIM_NumericSensor_RestoreDefaultThresholds** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RestoreDefaultThresholds_Destruct(
    CIM_NumericSensor_RestoreDefaultThresholds* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RestoreDefaultThresholds_Delete(
    CIM_NumericSensor_RestoreDefaultThresholds* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RestoreDefaultThresholds_Post(
    const CIM_NumericSensor_RestoreDefaultThresholds* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RestoreDefaultThresholds_Set_MIReturn(
    CIM_NumericSensor_RestoreDefaultThresholds* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_RestoreDefaultThresholds_Clear_MIReturn(
    CIM_NumericSensor_RestoreDefaultThresholds* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NumericSensor.GetNonLinearFactors()
**
**==============================================================================
*/

typedef struct _CIM_NumericSensor_GetNonLinearFactors
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstSint32Field SensorReading;
    /*OUT*/ MI_ConstSint32Field Accuracy;
    /*OUT*/ MI_ConstUint32Field Resolution;
    /*OUT*/ MI_ConstSint32Field Tolerance;
    /*OUT*/ MI_ConstUint32Field Hysteresis;
}
CIM_NumericSensor_GetNonLinearFactors;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_NumericSensor_GetNonLinearFactors_rtti;

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_GetNonLinearFactors_Construct(
    CIM_NumericSensor_GetNonLinearFactors* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &CIM_NumericSensor_GetNonLinearFactors_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_GetNonLinearFactors_Clone(
    const CIM_NumericSensor_GetNonLinearFactors* self,
    CIM_NumericSensor_GetNonLinearFactors** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_GetNonLinearFactors_Destruct(
    CIM_NumericSensor_GetNonLinearFactors* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_GetNonLinearFactors_Delete(
    CIM_NumericSensor_GetNonLinearFactors* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_GetNonLinearFactors_Post(
    const CIM_NumericSensor_GetNonLinearFactors* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_GetNonLinearFactors_Set_MIReturn(
    CIM_NumericSensor_GetNonLinearFactors* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_GetNonLinearFactors_Clear_MIReturn(
    CIM_NumericSensor_GetNonLinearFactors* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_GetNonLinearFactors_Set_SensorReading(
    CIM_NumericSensor_GetNonLinearFactors* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->SensorReading)->value = x;
    ((MI_Sint32Field*)&self->SensorReading)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_GetNonLinearFactors_Clear_SensorReading(
    CIM_NumericSensor_GetNonLinearFactors* self)
{
    memset((void*)&self->SensorReading, 0, sizeof(self->SensorReading));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_GetNonLinearFactors_Set_Accuracy(
    CIM_NumericSensor_GetNonLinearFactors* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->Accuracy)->value = x;
    ((MI_Sint32Field*)&self->Accuracy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_GetNonLinearFactors_Clear_Accuracy(
    CIM_NumericSensor_GetNonLinearFactors* self)
{
    memset((void*)&self->Accuracy, 0, sizeof(self->Accuracy));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_GetNonLinearFactors_Set_Resolution(
    CIM_NumericSensor_GetNonLinearFactors* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Resolution)->value = x;
    ((MI_Uint32Field*)&self->Resolution)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_GetNonLinearFactors_Clear_Resolution(
    CIM_NumericSensor_GetNonLinearFactors* self)
{
    memset((void*)&self->Resolution, 0, sizeof(self->Resolution));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_GetNonLinearFactors_Set_Tolerance(
    CIM_NumericSensor_GetNonLinearFactors* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->Tolerance)->value = x;
    ((MI_Sint32Field*)&self->Tolerance)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_GetNonLinearFactors_Clear_Tolerance(
    CIM_NumericSensor_GetNonLinearFactors* self)
{
    memset((void*)&self->Tolerance, 0, sizeof(self->Tolerance));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_GetNonLinearFactors_Set_Hysteresis(
    CIM_NumericSensor_GetNonLinearFactors* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Hysteresis)->value = x;
    ((MI_Uint32Field*)&self->Hysteresis)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NumericSensor_GetNonLinearFactors_Clear_Hysteresis(
    CIM_NumericSensor_GetNonLinearFactors* self)
{
    memset((void*)&self->Hysteresis, 0, sizeof(self->Hysteresis));
    return MI_RESULT_OK;
}


#endif /* _CIM_NumericSensor_h */
