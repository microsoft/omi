/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_PhysicalPackage_h
#define _CIM_PhysicalPackage_h

#include <MI.h>
#include "CIM_PhysicalElement.h"

/*
**==============================================================================
**
** CIM_PhysicalPackage [CIM_PhysicalPackage]
**
** Keys:
**    Tag
**    CreationClassName
**
**==============================================================================
*/

typedef struct _CIM_PhysicalPackage /* extends CIM_PhysicalElement */
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
    /* CIM_PhysicalElement properties */
    /*KEY*/ MI_ConstStringField Tag;
    /*KEY*/ MI_ConstStringField CreationClassName;
    MI_ConstStringField Manufacturer;
    MI_ConstStringField Model;
    MI_ConstStringField SKU;
    MI_ConstStringField SerialNumber;
    MI_ConstStringField Version;
    MI_ConstStringField PartNumber;
    MI_ConstStringField OtherIdentifyingInfo;
    MI_ConstBooleanField PoweredOn;
    MI_ConstDatetimeField ManufactureDate;
    MI_ConstStringField VendorEquipmentType;
    MI_ConstStringField UserTracking;
    MI_ConstBooleanField CanBeFRUed;
    /* CIM_PhysicalPackage properties */
    MI_ConstUint16Field RemovalConditions;
    MI_ConstBooleanField Removable;
    MI_ConstBooleanField Replaceable;
    MI_ConstBooleanField HotSwappable;
    MI_ConstReal32Field Height;
    MI_ConstReal32Field Depth;
    MI_ConstReal32Field Width;
    MI_ConstReal32Field Weight;
    MI_ConstUint16Field PackageType;
    MI_ConstStringField OtherPackageType;
    MI_ConstStringAField VendorCompatibilityStrings;
}
CIM_PhysicalPackage;

typedef struct _CIM_PhysicalPackage_Ref
{
    CIM_PhysicalPackage* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PhysicalPackage_Ref;

typedef struct _CIM_PhysicalPackage_ConstRef
{
    MI_CONST CIM_PhysicalPackage* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PhysicalPackage_ConstRef;

typedef struct _CIM_PhysicalPackage_Array
{
    struct _CIM_PhysicalPackage** data;
    MI_Uint32 size;
}
CIM_PhysicalPackage_Array;

typedef struct _CIM_PhysicalPackage_ConstArray
{
    struct _CIM_PhysicalPackage MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_PhysicalPackage_ConstArray;

typedef struct _CIM_PhysicalPackage_ArrayRef
{
    CIM_PhysicalPackage_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PhysicalPackage_ArrayRef;

typedef struct _CIM_PhysicalPackage_ConstArrayRef
{
    CIM_PhysicalPackage_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PhysicalPackage_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_PhysicalPackage_rtti;

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Construct(
    CIM_PhysicalPackage* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_PhysicalPackage_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clone(
    const CIM_PhysicalPackage* self,
    CIM_PhysicalPackage** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_PhysicalPackage_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_PhysicalPackage_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Destruct(CIM_PhysicalPackage* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Delete(CIM_PhysicalPackage* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Post(
    const CIM_PhysicalPackage* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_InstanceID(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_InstanceID(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_InstanceID(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_Caption(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_Caption(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_Caption(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_Description(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_Description(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_Description(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_ElementName(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_ElementName(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_ElementName(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_InstallDate(
    CIM_PhysicalPackage* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_InstallDate(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_Name(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_Name(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_Name(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_OperationalStatus(
    CIM_PhysicalPackage* self,
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_OperationalStatus(
    CIM_PhysicalPackage* self,
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_OperationalStatus(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_StatusDescriptions(
    CIM_PhysicalPackage* self,
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_StatusDescriptions(
    CIM_PhysicalPackage* self,
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_StatusDescriptions(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_Status(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_Status(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_Status(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_HealthState(
    CIM_PhysicalPackage* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_HealthState(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_CommunicationStatus(
    CIM_PhysicalPackage* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_CommunicationStatus(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_DetailedStatus(
    CIM_PhysicalPackage* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_DetailedStatus(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_OperatingStatus(
    CIM_PhysicalPackage* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_OperatingStatus(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_PrimaryStatus(
    CIM_PhysicalPackage* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_PrimaryStatus(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_Tag(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_Tag(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_Tag(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_CreationClassName(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_CreationClassName(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_CreationClassName(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_Manufacturer(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_Manufacturer(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_Manufacturer(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_Model(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_Model(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_Model(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_SKU(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_SKU(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_SKU(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_SerialNumber(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_SerialNumber(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_SerialNumber(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_Version(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_Version(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_Version(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        20);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_PartNumber(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_PartNumber(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_PartNumber(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_OtherIdentifyingInfo(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_OtherIdentifyingInfo(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_OtherIdentifyingInfo(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_PoweredOn(
    CIM_PhysicalPackage* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->PoweredOn)->value = x;
    ((MI_BooleanField*)&self->PoweredOn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_PoweredOn(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->PoweredOn, 0, sizeof(self->PoweredOn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_ManufactureDate(
    CIM_PhysicalPackage* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->ManufactureDate)->value = x;
    ((MI_DatetimeField*)&self->ManufactureDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_ManufactureDate(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->ManufactureDate, 0, sizeof(self->ManufactureDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_VendorEquipmentType(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_VendorEquipmentType(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_VendorEquipmentType(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        25);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_UserTracking(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_UserTracking(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_UserTracking(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_CanBeFRUed(
    CIM_PhysicalPackage* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->CanBeFRUed)->value = x;
    ((MI_BooleanField*)&self->CanBeFRUed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_CanBeFRUed(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->CanBeFRUed, 0, sizeof(self->CanBeFRUed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_RemovalConditions(
    CIM_PhysicalPackage* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RemovalConditions)->value = x;
    ((MI_Uint16Field*)&self->RemovalConditions)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_RemovalConditions(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->RemovalConditions, 0, sizeof(self->RemovalConditions));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_Removable(
    CIM_PhysicalPackage* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Removable)->value = x;
    ((MI_BooleanField*)&self->Removable)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_Removable(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->Removable, 0, sizeof(self->Removable));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_Replaceable(
    CIM_PhysicalPackage* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Replaceable)->value = x;
    ((MI_BooleanField*)&self->Replaceable)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_Replaceable(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->Replaceable, 0, sizeof(self->Replaceable));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_HotSwappable(
    CIM_PhysicalPackage* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->HotSwappable)->value = x;
    ((MI_BooleanField*)&self->HotSwappable)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_HotSwappable(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->HotSwappable, 0, sizeof(self->HotSwappable));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_Height(
    CIM_PhysicalPackage* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->Height)->value = x;
    ((MI_Real32Field*)&self->Height)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_Height(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->Height, 0, sizeof(self->Height));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_Depth(
    CIM_PhysicalPackage* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->Depth)->value = x;
    ((MI_Real32Field*)&self->Depth)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_Depth(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->Depth, 0, sizeof(self->Depth));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_Width(
    CIM_PhysicalPackage* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->Width)->value = x;
    ((MI_Real32Field*)&self->Width)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_Width(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->Width, 0, sizeof(self->Width));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_Weight(
    CIM_PhysicalPackage* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->Weight)->value = x;
    ((MI_Real32Field*)&self->Weight)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_Weight(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->Weight, 0, sizeof(self->Weight));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_PackageType(
    CIM_PhysicalPackage* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PackageType)->value = x;
    ((MI_Uint16Field*)&self->PackageType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_PackageType(
    CIM_PhysicalPackage* self)
{
    memset((void*)&self->PackageType, 0, sizeof(self->PackageType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_OtherPackageType(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        37,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_OtherPackageType(
    CIM_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        37,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_OtherPackageType(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        37);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Set_VendorCompatibilityStrings(
    CIM_PhysicalPackage* self,
    const MI_Char** data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_SetPtr_VendorCompatibilityStrings(
    CIM_PhysicalPackage* self,
    const MI_Char** data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_Clear_VendorCompatibilityStrings(
    CIM_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        38);
}

/*
**==============================================================================
**
** CIM_PhysicalPackage.IsCompatible()
**
**==============================================================================
*/

typedef struct _CIM_PhysicalPackage_IsCompatible
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ CIM_PhysicalElement_ConstRef ElementToCheck;
}
CIM_PhysicalPackage_IsCompatible;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_PhysicalPackage_IsCompatible_rtti;

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_IsCompatible_Construct(
    CIM_PhysicalPackage_IsCompatible* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &CIM_PhysicalPackage_IsCompatible_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_IsCompatible_Clone(
    const CIM_PhysicalPackage_IsCompatible* self,
    CIM_PhysicalPackage_IsCompatible** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_IsCompatible_Destruct(
    CIM_PhysicalPackage_IsCompatible* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_IsCompatible_Delete(
    CIM_PhysicalPackage_IsCompatible* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_IsCompatible_Post(
    const CIM_PhysicalPackage_IsCompatible* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_IsCompatible_Set_MIReturn(
    CIM_PhysicalPackage_IsCompatible* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_IsCompatible_Clear_MIReturn(
    CIM_PhysicalPackage_IsCompatible* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_IsCompatible_Set_ElementToCheck(
    CIM_PhysicalPackage_IsCompatible* self,
    const CIM_PhysicalElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_IsCompatible_SetPtr_ElementToCheck(
    CIM_PhysicalPackage_IsCompatible* self,
    const CIM_PhysicalElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalPackage_IsCompatible_Clear_ElementToCheck(
    CIM_PhysicalPackage_IsCompatible* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _CIM_PhysicalPackage_h */
