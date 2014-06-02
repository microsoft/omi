/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_PhysicalComputerSystemView_h
#define _CIM_PhysicalComputerSystemView_h

#include <MI.h>
#include "CIM_View.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** CIM_PhysicalComputerSystemView [CIM_PhysicalComputerSystemView]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_PhysicalComputerSystemView /* extends CIM_View */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_View properties */
    /* CIM_PhysicalComputerSystemView properties */
    MI_ConstUint16Field EnabledState;
    MI_ConstUint16Field RequestedState;
    MI_ConstUint16AField OperationalStatus;
    MI_ConstUint16Field HealthState;
    MI_ConstBooleanField FRUInfoSupported;
    MI_ConstStringField Tag;
    MI_ConstStringField Manufacturer;
    MI_ConstStringField Model;
    MI_ConstStringField SKU;
    MI_ConstStringField SerialNumber;
    MI_ConstStringField Version;
    MI_ConstStringField PartNumber;
    MI_ConstUint16AField PowerUtilizationModesSupported;
    MI_ConstUint16Field PowerUtilizationMode;
    MI_ConstUint64Field PowerAllocationLimit;
    MI_ConstStringAField NumericSensorElementName;
    MI_ConstUint16AField NumericSensorEnabledState;
    MI_ConstUint16AField NumericSensorHealthState;
    MI_ConstStringAField NumericSensorCurrentState;
    MI_ConstUint16AField NumericSensorPrimaryStatus;
    MI_ConstUint16AField NumericSensorBaseUnits;
    MI_ConstSint32AField NumericSensorUnitModifier;
    MI_ConstUint16AField NumericSensorRateUnits;
    MI_ConstSint32AField NumericSensorCurrentReading;
    MI_ConstUint16AField NumericSensorSensorType;
    MI_ConstStringAField NumericSensorOtherSensorTypeDescription;
    MI_ConstSint32AField NumericSensorUpperThresholdNonCritical;
    MI_ConstSint32AField NumericSensorUpperThresholdCritical;
    MI_ConstSint32AField NumericSensorUpperThresholdFatal;
    MI_ConstStringAField LogInstanceID;
    MI_ConstUint64AField LogMaxNumberOfRecords;
    MI_ConstUint64AField LogCurrentNumberOfRecords;
    MI_ConstUint16AField LogOverWritePolicy;
    MI_ConstUint16AField LogState;
    MI_ConstStringAField StructuredBootString;
    MI_ConstUint8AField PersistentBootConfigOrder;
    MI_ConstUint8Field OneTimeBootSource;
    MI_ConstUint16Field NumberOfProcessors;
    MI_ConstUint16Field NumberOfProcessorCores;
    MI_ConstUint16Field NumberOfProcessorThreads;
    MI_ConstUint16Field ProcessorFamily;
    MI_ConstUint32Field ProcessorMaxClockSpeed;
    MI_ConstUint64Field MemoryBlockSize;
    MI_ConstUint64Field MemoryNumberOfBlocks;
    MI_ConstUint64Field MemoryConsumableBlocks;
    MI_ConstUint16Field CurrentBIOSMajorVersion;
    MI_ConstUint16Field CurrentBIOSMinorVersion;
    MI_ConstUint16Field CurrentBIOSRevisionNumber;
    MI_ConstUint16Field CurrentBIOSBuildNumber;
    MI_ConstUint16Field CurrentManagementFirmwareMajorVersion;
    MI_ConstUint16Field CurrentManagementFirmwareMinorVersion;
    MI_ConstUint16Field CurrentManagementFirmwareRevisionNumber;
    MI_ConstUint16Field CurrentManagementFirmwareBuildNumber;
    MI_ConstStringField CurrentManagementFirmwareElementName;
    MI_ConstStringField CurrentManagementFirmwareVersionString;
    MI_ConstUint16Field OSType;
    MI_ConstStringField OSVersion;
    MI_ConstUint16Field OSEnabledState;
    MI_ConstStringField CurrentBIOSVersionString;
    MI_ConstUint16AField Dedicated;
    MI_ConstStringAField IdentifyingDescriptions;
    MI_ConstStringAField NumericSensorSensorContext;
    MI_ConstStringAField OtherDedicatedDescriptions;
    MI_ConstStringAField OtherIdentifyingInfo;
    MI_ConstUint32Field ProcessorCurrentClockSpeed;
}
CIM_PhysicalComputerSystemView;

typedef struct _CIM_PhysicalComputerSystemView_Ref
{
    CIM_PhysicalComputerSystemView* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PhysicalComputerSystemView_Ref;

typedef struct _CIM_PhysicalComputerSystemView_ConstRef
{
    MI_CONST CIM_PhysicalComputerSystemView* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PhysicalComputerSystemView_ConstRef;

typedef struct _CIM_PhysicalComputerSystemView_Array
{
    struct _CIM_PhysicalComputerSystemView** data;
    MI_Uint32 size;
}
CIM_PhysicalComputerSystemView_Array;

typedef struct _CIM_PhysicalComputerSystemView_ConstArray
{
    struct _CIM_PhysicalComputerSystemView MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_PhysicalComputerSystemView_ConstArray;

typedef struct _CIM_PhysicalComputerSystemView_ArrayRef
{
    CIM_PhysicalComputerSystemView_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PhysicalComputerSystemView_ArrayRef;

typedef struct _CIM_PhysicalComputerSystemView_ConstArrayRef
{
    CIM_PhysicalComputerSystemView_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PhysicalComputerSystemView_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_PhysicalComputerSystemView_rtti;

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Construct(
    _Out_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_PhysicalComputerSystemView_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clone(
    _In_ const CIM_PhysicalComputerSystemView* self,
    _Outptr_ CIM_PhysicalComputerSystemView** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_PhysicalComputerSystemView_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_PhysicalComputerSystemView_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Destruct(_Inout_ CIM_PhysicalComputerSystemView* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Delete(_Inout_ CIM_PhysicalComputerSystemView* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Post(
    _In_ const CIM_PhysicalComputerSystemView* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_InstanceID(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_InstanceID(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_InstanceID(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_Caption(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_Caption(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_Caption(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_Description(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_Description(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_Description(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_ElementName(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_ElementName(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_ElementName(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_EnabledState(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_EnabledState(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_RequestedState(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_RequestedState(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_OperationalStatus(
    _Inout_ CIM_PhysicalComputerSystemView* self,
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_OperationalStatus(
    _Inout_ CIM_PhysicalComputerSystemView* self,
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_OperationalStatus(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_HealthState(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_HealthState(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_FRUInfoSupported(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->FRUInfoSupported)->value = x;
    ((MI_BooleanField*)&self->FRUInfoSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_FRUInfoSupported(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->FRUInfoSupported, 0, sizeof(self->FRUInfoSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_Tag(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_Tag(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_Tag(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_Manufacturer(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_Manufacturer(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_Manufacturer(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_Model(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_Model(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_Model(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_SKU(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_SKU(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_SKU(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_SerialNumber(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_SerialNumber(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_SerialNumber(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_Version(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_Version(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_Version(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_PartNumber(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_PartNumber(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_PartNumber(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_PowerUtilizationModesSupported(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_PowerUtilizationModesSupported(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_PowerUtilizationModesSupported(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_PowerUtilizationMode(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PowerUtilizationMode)->value = x;
    ((MI_Uint16Field*)&self->PowerUtilizationMode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_PowerUtilizationMode(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->PowerUtilizationMode, 0, sizeof(self->PowerUtilizationMode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_PowerAllocationLimit(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->PowerAllocationLimit)->value = x;
    ((MI_Uint64Field*)&self->PowerAllocationLimit)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_PowerAllocationLimit(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->PowerAllocationLimit, 0, sizeof(self->PowerAllocationLimit));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumericSensorElementName(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_NumericSensorElementName(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumericSensorElementName(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumericSensorEnabledState(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_NumericSensorEnabledState(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumericSensorEnabledState(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        20);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumericSensorHealthState(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_NumericSensorHealthState(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumericSensorHealthState(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumericSensorCurrentState(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_NumericSensorCurrentState(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumericSensorCurrentState(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumericSensorPrimaryStatus(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_NumericSensorPrimaryStatus(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumericSensorPrimaryStatus(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumericSensorBaseUnits(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_NumericSensorBaseUnits(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumericSensorBaseUnits(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumericSensorUnitModifier(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Sint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&arr,
        MI_SINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_NumericSensorUnitModifier(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Sint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&arr,
        MI_SINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumericSensorUnitModifier(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        25);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumericSensorRateUnits(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_NumericSensorRateUnits(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumericSensorRateUnits(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumericSensorCurrentReading(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Sint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&arr,
        MI_SINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_NumericSensorCurrentReading(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Sint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&arr,
        MI_SINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumericSensorCurrentReading(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        27);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumericSensorSensorType(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_NumericSensorSensorType(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumericSensorSensorType(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        28);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumericSensorOtherSensorTypeDescription(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_NumericSensorOtherSensorTypeDescription(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumericSensorOtherSensorTypeDescription(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        29);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumericSensorUpperThresholdNonCritical(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Sint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&arr,
        MI_SINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_NumericSensorUpperThresholdNonCritical(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Sint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&arr,
        MI_SINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumericSensorUpperThresholdNonCritical(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        30);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumericSensorUpperThresholdCritical(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Sint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        31,
        (MI_Value*)&arr,
        MI_SINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_NumericSensorUpperThresholdCritical(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Sint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        31,
        (MI_Value*)&arr,
        MI_SINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumericSensorUpperThresholdCritical(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        31);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumericSensorUpperThresholdFatal(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Sint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&arr,
        MI_SINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_NumericSensorUpperThresholdFatal(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Sint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&arr,
        MI_SINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumericSensorUpperThresholdFatal(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        32);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_LogInstanceID(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        33,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_LogInstanceID(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        33,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_LogInstanceID(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        33);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_LogMaxNumberOfRecords(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint64* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        34,
        (MI_Value*)&arr,
        MI_UINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_LogMaxNumberOfRecords(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint64* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        34,
        (MI_Value*)&arr,
        MI_UINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_LogMaxNumberOfRecords(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        34);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_LogCurrentNumberOfRecords(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint64* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        35,
        (MI_Value*)&arr,
        MI_UINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_LogCurrentNumberOfRecords(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint64* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        35,
        (MI_Value*)&arr,
        MI_UINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_LogCurrentNumberOfRecords(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        35);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_LogOverWritePolicy(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_LogOverWritePolicy(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_LogOverWritePolicy(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        36);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_LogState(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        37,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_LogState(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        37,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_LogState(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        37);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_StructuredBootString(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        38,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_StructuredBootString(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        38,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_StructuredBootString(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        38);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_PersistentBootConfigOrder(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        39,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_PersistentBootConfigOrder(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        39,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_PersistentBootConfigOrder(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        39);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_OneTimeBootSource(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->OneTimeBootSource)->value = x;
    ((MI_Uint8Field*)&self->OneTimeBootSource)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_OneTimeBootSource(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->OneTimeBootSource, 0, sizeof(self->OneTimeBootSource));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumberOfProcessors(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->NumberOfProcessors)->value = x;
    ((MI_Uint16Field*)&self->NumberOfProcessors)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumberOfProcessors(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->NumberOfProcessors, 0, sizeof(self->NumberOfProcessors));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumberOfProcessorCores(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->NumberOfProcessorCores)->value = x;
    ((MI_Uint16Field*)&self->NumberOfProcessorCores)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumberOfProcessorCores(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->NumberOfProcessorCores, 0, sizeof(self->NumberOfProcessorCores));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumberOfProcessorThreads(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->NumberOfProcessorThreads)->value = x;
    ((MI_Uint16Field*)&self->NumberOfProcessorThreads)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumberOfProcessorThreads(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->NumberOfProcessorThreads, 0, sizeof(self->NumberOfProcessorThreads));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_ProcessorFamily(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ProcessorFamily)->value = x;
    ((MI_Uint16Field*)&self->ProcessorFamily)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_ProcessorFamily(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->ProcessorFamily, 0, sizeof(self->ProcessorFamily));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_ProcessorMaxClockSpeed(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->ProcessorMaxClockSpeed)->value = x;
    ((MI_Uint32Field*)&self->ProcessorMaxClockSpeed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_ProcessorMaxClockSpeed(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->ProcessorMaxClockSpeed, 0, sizeof(self->ProcessorMaxClockSpeed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_MemoryBlockSize(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MemoryBlockSize)->value = x;
    ((MI_Uint64Field*)&self->MemoryBlockSize)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_MemoryBlockSize(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->MemoryBlockSize, 0, sizeof(self->MemoryBlockSize));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_MemoryNumberOfBlocks(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MemoryNumberOfBlocks)->value = x;
    ((MI_Uint64Field*)&self->MemoryNumberOfBlocks)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_MemoryNumberOfBlocks(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->MemoryNumberOfBlocks, 0, sizeof(self->MemoryNumberOfBlocks));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_MemoryConsumableBlocks(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MemoryConsumableBlocks)->value = x;
    ((MI_Uint64Field*)&self->MemoryConsumableBlocks)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_MemoryConsumableBlocks(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->MemoryConsumableBlocks, 0, sizeof(self->MemoryConsumableBlocks));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_CurrentBIOSMajorVersion(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CurrentBIOSMajorVersion)->value = x;
    ((MI_Uint16Field*)&self->CurrentBIOSMajorVersion)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_CurrentBIOSMajorVersion(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->CurrentBIOSMajorVersion, 0, sizeof(self->CurrentBIOSMajorVersion));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_CurrentBIOSMinorVersion(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CurrentBIOSMinorVersion)->value = x;
    ((MI_Uint16Field*)&self->CurrentBIOSMinorVersion)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_CurrentBIOSMinorVersion(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->CurrentBIOSMinorVersion, 0, sizeof(self->CurrentBIOSMinorVersion));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_CurrentBIOSRevisionNumber(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CurrentBIOSRevisionNumber)->value = x;
    ((MI_Uint16Field*)&self->CurrentBIOSRevisionNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_CurrentBIOSRevisionNumber(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->CurrentBIOSRevisionNumber, 0, sizeof(self->CurrentBIOSRevisionNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_CurrentBIOSBuildNumber(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CurrentBIOSBuildNumber)->value = x;
    ((MI_Uint16Field*)&self->CurrentBIOSBuildNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_CurrentBIOSBuildNumber(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->CurrentBIOSBuildNumber, 0, sizeof(self->CurrentBIOSBuildNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_CurrentManagementFirmwareMajorVersion(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CurrentManagementFirmwareMajorVersion)->value = x;
    ((MI_Uint16Field*)&self->CurrentManagementFirmwareMajorVersion)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_CurrentManagementFirmwareMajorVersion(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->CurrentManagementFirmwareMajorVersion, 0, sizeof(self->CurrentManagementFirmwareMajorVersion));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_CurrentManagementFirmwareMinorVersion(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CurrentManagementFirmwareMinorVersion)->value = x;
    ((MI_Uint16Field*)&self->CurrentManagementFirmwareMinorVersion)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_CurrentManagementFirmwareMinorVersion(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->CurrentManagementFirmwareMinorVersion, 0, sizeof(self->CurrentManagementFirmwareMinorVersion));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_CurrentManagementFirmwareRevisionNumber(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CurrentManagementFirmwareRevisionNumber)->value = x;
    ((MI_Uint16Field*)&self->CurrentManagementFirmwareRevisionNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_CurrentManagementFirmwareRevisionNumber(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->CurrentManagementFirmwareRevisionNumber, 0, sizeof(self->CurrentManagementFirmwareRevisionNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_CurrentManagementFirmwareBuildNumber(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CurrentManagementFirmwareBuildNumber)->value = x;
    ((MI_Uint16Field*)&self->CurrentManagementFirmwareBuildNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_CurrentManagementFirmwareBuildNumber(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->CurrentManagementFirmwareBuildNumber, 0, sizeof(self->CurrentManagementFirmwareBuildNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_CurrentManagementFirmwareElementName(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        57,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_CurrentManagementFirmwareElementName(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        57,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_CurrentManagementFirmwareElementName(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        57);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_CurrentManagementFirmwareVersionString(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        58,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_CurrentManagementFirmwareVersionString(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        58,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_CurrentManagementFirmwareVersionString(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        58);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_OSType(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OSType)->value = x;
    ((MI_Uint16Field*)&self->OSType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_OSType(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->OSType, 0, sizeof(self->OSType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_OSVersion(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        60,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_OSVersion(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        60,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_OSVersion(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        60);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_OSEnabledState(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OSEnabledState)->value = x;
    ((MI_Uint16Field*)&self->OSEnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_OSEnabledState(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->OSEnabledState, 0, sizeof(self->OSEnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_CurrentBIOSVersionString(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        62,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_CurrentBIOSVersionString(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        62,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_CurrentBIOSVersionString(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        62);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_Dedicated(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        63,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_Dedicated(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        63,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_Dedicated(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        63);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_IdentifyingDescriptions(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        64,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_IdentifyingDescriptions(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        64,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_IdentifyingDescriptions(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        64);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_NumericSensorSensorContext(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        65,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_NumericSensorSensorContext(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        65,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_NumericSensorSensorContext(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        65);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_OtherDedicatedDescriptions(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        66,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_OtherDedicatedDescriptions(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        66,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_OtherDedicatedDescriptions(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        66);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_OtherIdentifyingInfo(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        67,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetPtr_OtherIdentifyingInfo(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        67,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_OtherIdentifyingInfo(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        67);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Set_ProcessorCurrentClockSpeed(
    _Inout_ CIM_PhysicalComputerSystemView* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->ProcessorCurrentClockSpeed)->value = x;
    ((MI_Uint32Field*)&self->ProcessorCurrentClockSpeed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_Clear_ProcessorCurrentClockSpeed(
    _Inout_ CIM_PhysicalComputerSystemView* self)
{
    memset((void*)&self->ProcessorCurrentClockSpeed, 0, sizeof(self->ProcessorCurrentClockSpeed));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_PhysicalComputerSystemView.RequestStateChange()
**
**==============================================================================
*/

typedef struct _CIM_PhysicalComputerSystemView_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
CIM_PhysicalComputerSystemView_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_PhysicalComputerSystemView_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_RequestStateChange_Construct(
    _Out_ CIM_PhysicalComputerSystemView_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_PhysicalComputerSystemView_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_RequestStateChange_Clone(
    _In_ const CIM_PhysicalComputerSystemView_RequestStateChange* self,
    _Outptr_ CIM_PhysicalComputerSystemView_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_RequestStateChange_Destruct(
    _Inout_ CIM_PhysicalComputerSystemView_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_RequestStateChange_Delete(
    _Inout_ CIM_PhysicalComputerSystemView_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_RequestStateChange_Post(
    _In_ const CIM_PhysicalComputerSystemView_RequestStateChange* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_RequestStateChange_Set_MIReturn(
    _Inout_ CIM_PhysicalComputerSystemView_RequestStateChange* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_RequestStateChange_Clear_MIReturn(
    _Inout_ CIM_PhysicalComputerSystemView_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_RequestStateChange_Set_RequestedState(
    _Inout_ CIM_PhysicalComputerSystemView_RequestStateChange* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_RequestStateChange_Clear_RequestedState(
    _Inout_ CIM_PhysicalComputerSystemView_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_RequestStateChange_Set_Job(
    _Inout_ CIM_PhysicalComputerSystemView_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_RequestStateChange_SetPtr_Job(
    _Inout_ CIM_PhysicalComputerSystemView_RequestStateChange* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_RequestStateChange_Clear_Job(
    _Inout_ CIM_PhysicalComputerSystemView_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_RequestStateChange_Set_TimeoutPeriod(
    _Inout_ CIM_PhysicalComputerSystemView_RequestStateChange* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_RequestStateChange_Clear_TimeoutPeriod(
    _Inout_ CIM_PhysicalComputerSystemView_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_PhysicalComputerSystemView.ClearLog()
**
**==============================================================================
*/

typedef struct _CIM_PhysicalComputerSystemView_ClearLog
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstStringField LogInstanceID;
}
CIM_PhysicalComputerSystemView_ClearLog;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_PhysicalComputerSystemView_ClearLog_rtti;

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ClearLog_Construct(
    _Out_ CIM_PhysicalComputerSystemView_ClearLog* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_PhysicalComputerSystemView_ClearLog_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ClearLog_Clone(
    _In_ const CIM_PhysicalComputerSystemView_ClearLog* self,
    _Outptr_ CIM_PhysicalComputerSystemView_ClearLog** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ClearLog_Destruct(
    _Inout_ CIM_PhysicalComputerSystemView_ClearLog* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ClearLog_Delete(
    _Inout_ CIM_PhysicalComputerSystemView_ClearLog* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ClearLog_Post(
    _In_ const CIM_PhysicalComputerSystemView_ClearLog* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ClearLog_Set_MIReturn(
    _Inout_ CIM_PhysicalComputerSystemView_ClearLog* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ClearLog_Clear_MIReturn(
    _Inout_ CIM_PhysicalComputerSystemView_ClearLog* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ClearLog_Set_LogInstanceID(
    _Inout_ CIM_PhysicalComputerSystemView_ClearLog* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ClearLog_SetPtr_LogInstanceID(
    _Inout_ CIM_PhysicalComputerSystemView_ClearLog* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ClearLog_Clear_LogInstanceID(
    _Inout_ CIM_PhysicalComputerSystemView_ClearLog* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** CIM_PhysicalComputerSystemView.InstallSoftwareFromURI()
**
**==============================================================================
*/

typedef struct _CIM_PhysicalComputerSystemView_InstallSoftwareFromURI
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstStringField URI;
    /*IN*/ MI_ConstUint16AField InstallOptions;
    /*IN*/ MI_ConstStringAField InstallOptionsValues;
}
CIM_PhysicalComputerSystemView_InstallSoftwareFromURI;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_rtti;

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_Construct(
    _Out_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_Clone(
    _In_ const CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self,
    _Outptr_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_Destruct(
    _Inout_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_Delete(
    _Inout_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_Post(
    _In_ const CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_Set_MIReturn(
    _Inout_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_Clear_MIReturn(
    _Inout_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_Set_Job(
    _Inout_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_SetPtr_Job(
    _Inout_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_Clear_Job(
    _Inout_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_Set_URI(
    _Inout_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_SetPtr_URI(
    _Inout_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_Clear_URI(
    _Inout_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_Set_InstallOptions(
    _Inout_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_SetPtr_InstallOptions(
    _Inout_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_Clear_InstallOptions(
    _Inout_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_Set_InstallOptionsValues(
    _Inout_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_SetPtr_InstallOptionsValues(
    _Inout_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_InstallSoftwareFromURI_Clear_InstallOptionsValues(
    _Inout_ CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** CIM_PhysicalComputerSystemView.ModifyPersistentBootConfigOrder()
**
**==============================================================================
*/

typedef struct _CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MI_ConstUint8AField StructuredBootStringIndex;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder_rtti;

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder_Construct(
    _Out_ CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder_Clone(
    _In_ const CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder* self,
    _Outptr_ CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder_Destruct(
    _Inout_ CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder_Delete(
    _Inout_ CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder_Post(
    _In_ const CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder_Set_MIReturn(
    _Inout_ CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder_Clear_MIReturn(
    _Inout_ CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder_Set_StructuredBootStringIndex(
    _Inout_ CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder* self,
    _In_reads_opt_(size) const MI_Uint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder_SetPtr_StructuredBootStringIndex(
    _Inout_ CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder* self,
    _In_reads_opt_(size) const MI_Uint8* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder_Clear_StructuredBootStringIndex(
    _Inout_ CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder_Set_Job(
    _Inout_ CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder_SetPtr_Job(
    _Inout_ CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder_Clear_Job(
    _Inout_ CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** CIM_PhysicalComputerSystemView.SetOneTimeBootSource()
**
**==============================================================================
*/

typedef struct _CIM_PhysicalComputerSystemView_SetOneTimeBootSource
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
MI_ConstUint8Field StructuredBootStringIndex;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
}
CIM_PhysicalComputerSystemView_SetOneTimeBootSource;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_PhysicalComputerSystemView_SetOneTimeBootSource_rtti;

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetOneTimeBootSource_Construct(
    _Out_ CIM_PhysicalComputerSystemView_SetOneTimeBootSource* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_PhysicalComputerSystemView_SetOneTimeBootSource_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetOneTimeBootSource_Clone(
    _In_ const CIM_PhysicalComputerSystemView_SetOneTimeBootSource* self,
    _Outptr_ CIM_PhysicalComputerSystemView_SetOneTimeBootSource** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetOneTimeBootSource_Destruct(
    _Inout_ CIM_PhysicalComputerSystemView_SetOneTimeBootSource* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetOneTimeBootSource_Delete(
    _Inout_ CIM_PhysicalComputerSystemView_SetOneTimeBootSource* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetOneTimeBootSource_Post(
    _In_ const CIM_PhysicalComputerSystemView_SetOneTimeBootSource* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetOneTimeBootSource_Set_MIReturn(
    _Inout_ CIM_PhysicalComputerSystemView_SetOneTimeBootSource* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetOneTimeBootSource_Clear_MIReturn(
    _Inout_ CIM_PhysicalComputerSystemView_SetOneTimeBootSource* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetOneTimeBootSource_Set_StructuredBootStringIndex(
    _Inout_ CIM_PhysicalComputerSystemView_SetOneTimeBootSource* self,
    _In_ MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->StructuredBootStringIndex)->value = x;
    ((MI_Uint8Field*)&self->StructuredBootStringIndex)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetOneTimeBootSource_Clear_StructuredBootStringIndex(
    _Inout_ CIM_PhysicalComputerSystemView_SetOneTimeBootSource* self)
{
    memset((void*)&self->StructuredBootStringIndex, 0, sizeof(self->StructuredBootStringIndex));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetOneTimeBootSource_Set_Job(
    _Inout_ CIM_PhysicalComputerSystemView_SetOneTimeBootSource* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetOneTimeBootSource_SetPtr_Job(
    _Inout_ CIM_PhysicalComputerSystemView_SetOneTimeBootSource* self,
    _In_ const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalComputerSystemView_SetOneTimeBootSource_Clear_Job(
    _Inout_ CIM_PhysicalComputerSystemView_SetOneTimeBootSource* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** CIM_PhysicalComputerSystemView provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_PhysicalComputerSystemView_Self CIM_PhysicalComputerSystemView_Self;

MI_EXTERN_C void MI_CALL CIM_PhysicalComputerSystemView_Load(
    _Outptr_result_maybenull_ CIM_PhysicalComputerSystemView_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_PhysicalComputerSystemView_Unload(
    _In_opt_ CIM_PhysicalComputerSystemView_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_PhysicalComputerSystemView_EnumerateInstances(
    _In_opt_ CIM_PhysicalComputerSystemView_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_PhysicalComputerSystemView_GetInstance(
    _In_opt_ CIM_PhysicalComputerSystemView_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PhysicalComputerSystemView* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_PhysicalComputerSystemView_CreateInstance(
    _In_opt_ CIM_PhysicalComputerSystemView_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PhysicalComputerSystemView* newInstance);

MI_EXTERN_C void MI_CALL CIM_PhysicalComputerSystemView_ModifyInstance(
    _In_opt_ CIM_PhysicalComputerSystemView_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PhysicalComputerSystemView* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_PhysicalComputerSystemView_DeleteInstance(
    _In_opt_ CIM_PhysicalComputerSystemView_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PhysicalComputerSystemView* instanceName);

MI_EXTERN_C void MI_CALL CIM_PhysicalComputerSystemView_Invoke_RequestStateChange(
    _In_opt_ CIM_PhysicalComputerSystemView_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_PhysicalComputerSystemView* instanceName,
    _In_opt_ const CIM_PhysicalComputerSystemView_RequestStateChange* in);

MI_EXTERN_C void MI_CALL CIM_PhysicalComputerSystemView_Invoke_ClearLog(
    _In_opt_ CIM_PhysicalComputerSystemView_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_PhysicalComputerSystemView* instanceName,
    _In_opt_ const CIM_PhysicalComputerSystemView_ClearLog* in);

MI_EXTERN_C void MI_CALL CIM_PhysicalComputerSystemView_Invoke_InstallSoftwareFromURI(
    _In_opt_ CIM_PhysicalComputerSystemView_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_PhysicalComputerSystemView* instanceName,
    _In_opt_ const CIM_PhysicalComputerSystemView_InstallSoftwareFromURI* in);

MI_EXTERN_C void MI_CALL CIM_PhysicalComputerSystemView_Invoke_ModifyPersistentBootConfigOrder(
    _In_opt_ CIM_PhysicalComputerSystemView_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_PhysicalComputerSystemView* instanceName,
    _In_opt_ const CIM_PhysicalComputerSystemView_ModifyPersistentBootConfigOrder* in);

MI_EXTERN_C void MI_CALL CIM_PhysicalComputerSystemView_Invoke_SetOneTimeBootSource(
    _In_opt_ CIM_PhysicalComputerSystemView_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const CIM_PhysicalComputerSystemView* instanceName,
    _In_opt_ const CIM_PhysicalComputerSystemView_SetOneTimeBootSource* in);


#endif /* _CIM_PhysicalComputerSystemView_h */
