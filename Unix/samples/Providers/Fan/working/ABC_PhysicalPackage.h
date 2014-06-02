/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _ABC_PhysicalPackage_h
#define _ABC_PhysicalPackage_h

#include <MI.h>
#include "CIM_PhysicalPackage.h"
#include "CIM_PhysicalElement.h"

/*
**==============================================================================
**
** ABC_PhysicalPackage [ABC_PhysicalPackage]
**
** Keys:
**    Tag
**    CreationClassName
**
**==============================================================================
*/

typedef struct _ABC_PhysicalPackage /* extends CIM_PhysicalPackage */
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
    /* ABC_PhysicalPackage properties */
}
ABC_PhysicalPackage;

typedef struct _ABC_PhysicalPackage_Ref
{
    ABC_PhysicalPackage* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_PhysicalPackage_Ref;

typedef struct _ABC_PhysicalPackage_ConstRef
{
    MI_CONST ABC_PhysicalPackage* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_PhysicalPackage_ConstRef;

typedef struct _ABC_PhysicalPackage_Array
{
    struct _ABC_PhysicalPackage** data;
    MI_Uint32 size;
}
ABC_PhysicalPackage_Array;

typedef struct _ABC_PhysicalPackage_ConstArray
{
    struct _ABC_PhysicalPackage MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
ABC_PhysicalPackage_ConstArray;

typedef struct _ABC_PhysicalPackage_ArrayRef
{
    ABC_PhysicalPackage_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_PhysicalPackage_ArrayRef;

typedef struct _ABC_PhysicalPackage_ConstArrayRef
{
    ABC_PhysicalPackage_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
ABC_PhysicalPackage_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl ABC_PhysicalPackage_rtti;

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Construct(
    ABC_PhysicalPackage* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &ABC_PhysicalPackage_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clone(
    const ABC_PhysicalPackage* self,
    ABC_PhysicalPackage** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL ABC_PhysicalPackage_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &ABC_PhysicalPackage_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Destruct(ABC_PhysicalPackage* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Delete(ABC_PhysicalPackage* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Post(
    const ABC_PhysicalPackage* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_InstanceID(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_InstanceID(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_InstanceID(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_Caption(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_Caption(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_Caption(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_Description(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_Description(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_Description(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_ElementName(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_ElementName(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_ElementName(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_InstallDate(
    ABC_PhysicalPackage* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_InstallDate(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_Name(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_Name(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_Name(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_OperationalStatus(
    ABC_PhysicalPackage* self,
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

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_OperationalStatus(
    ABC_PhysicalPackage* self,
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

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_OperationalStatus(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_StatusDescriptions(
    ABC_PhysicalPackage* self,
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

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_StatusDescriptions(
    ABC_PhysicalPackage* self,
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

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_StatusDescriptions(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_Status(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_Status(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_Status(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_HealthState(
    ABC_PhysicalPackage* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_HealthState(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_CommunicationStatus(
    ABC_PhysicalPackage* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_CommunicationStatus(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_DetailedStatus(
    ABC_PhysicalPackage* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_DetailedStatus(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_OperatingStatus(
    ABC_PhysicalPackage* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_OperatingStatus(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_PrimaryStatus(
    ABC_PhysicalPackage* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_PrimaryStatus(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_Tag(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_Tag(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_Tag(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_CreationClassName(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_CreationClassName(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_CreationClassName(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_Manufacturer(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_Manufacturer(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_Manufacturer(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_Model(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_Model(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_Model(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_SKU(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_SKU(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_SKU(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_SerialNumber(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_SerialNumber(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_SerialNumber(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_Version(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_Version(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_Version(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        20);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_PartNumber(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_PartNumber(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_PartNumber(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_OtherIdentifyingInfo(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_OtherIdentifyingInfo(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_OtherIdentifyingInfo(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_PoweredOn(
    ABC_PhysicalPackage* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->PoweredOn)->value = x;
    ((MI_BooleanField*)&self->PoweredOn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_PoweredOn(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->PoweredOn, 0, sizeof(self->PoweredOn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_ManufactureDate(
    ABC_PhysicalPackage* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->ManufactureDate)->value = x;
    ((MI_DatetimeField*)&self->ManufactureDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_ManufactureDate(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->ManufactureDate, 0, sizeof(self->ManufactureDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_VendorEquipmentType(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_VendorEquipmentType(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_VendorEquipmentType(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        25);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_UserTracking(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_UserTracking(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_UserTracking(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_CanBeFRUed(
    ABC_PhysicalPackage* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->CanBeFRUed)->value = x;
    ((MI_BooleanField*)&self->CanBeFRUed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_CanBeFRUed(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->CanBeFRUed, 0, sizeof(self->CanBeFRUed));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_RemovalConditions(
    ABC_PhysicalPackage* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RemovalConditions)->value = x;
    ((MI_Uint16Field*)&self->RemovalConditions)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_RemovalConditions(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->RemovalConditions, 0, sizeof(self->RemovalConditions));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_Removable(
    ABC_PhysicalPackage* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Removable)->value = x;
    ((MI_BooleanField*)&self->Removable)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_Removable(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->Removable, 0, sizeof(self->Removable));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_Replaceable(
    ABC_PhysicalPackage* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Replaceable)->value = x;
    ((MI_BooleanField*)&self->Replaceable)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_Replaceable(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->Replaceable, 0, sizeof(self->Replaceable));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_HotSwappable(
    ABC_PhysicalPackage* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->HotSwappable)->value = x;
    ((MI_BooleanField*)&self->HotSwappable)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_HotSwappable(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->HotSwappable, 0, sizeof(self->HotSwappable));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_Height(
    ABC_PhysicalPackage* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->Height)->value = x;
    ((MI_Real32Field*)&self->Height)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_Height(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->Height, 0, sizeof(self->Height));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_Depth(
    ABC_PhysicalPackage* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->Depth)->value = x;
    ((MI_Real32Field*)&self->Depth)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_Depth(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->Depth, 0, sizeof(self->Depth));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_Width(
    ABC_PhysicalPackage* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->Width)->value = x;
    ((MI_Real32Field*)&self->Width)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_Width(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->Width, 0, sizeof(self->Width));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_Weight(
    ABC_PhysicalPackage* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->Weight)->value = x;
    ((MI_Real32Field*)&self->Weight)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_Weight(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->Weight, 0, sizeof(self->Weight));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_PackageType(
    ABC_PhysicalPackage* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PackageType)->value = x;
    ((MI_Uint16Field*)&self->PackageType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_PackageType(
    ABC_PhysicalPackage* self)
{
    memset((void*)&self->PackageType, 0, sizeof(self->PackageType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_OtherPackageType(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        37,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_OtherPackageType(
    ABC_PhysicalPackage* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        37,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_OtherPackageType(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        37);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Set_VendorCompatibilityStrings(
    ABC_PhysicalPackage* self,
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

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_SetPtr_VendorCompatibilityStrings(
    ABC_PhysicalPackage* self,
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

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_Clear_VendorCompatibilityStrings(
    ABC_PhysicalPackage* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        38);
}

/*
**==============================================================================
**
** ABC_PhysicalPackage.IsCompatible()
**
**==============================================================================
*/

typedef struct _ABC_PhysicalPackage_IsCompatible
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ CIM_PhysicalElement_ConstRef ElementToCheck;
}
ABC_PhysicalPackage_IsCompatible;

MI_EXTERN_C MI_CONST MI_MethodDecl ABC_PhysicalPackage_IsCompatible_rtti;

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_IsCompatible_Construct(
    ABC_PhysicalPackage_IsCompatible* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &ABC_PhysicalPackage_IsCompatible_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_IsCompatible_Clone(
    const ABC_PhysicalPackage_IsCompatible* self,
    ABC_PhysicalPackage_IsCompatible** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_IsCompatible_Destruct(
    ABC_PhysicalPackage_IsCompatible* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_IsCompatible_Delete(
    ABC_PhysicalPackage_IsCompatible* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_IsCompatible_Post(
    const ABC_PhysicalPackage_IsCompatible* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_IsCompatible_Set_MIReturn(
    ABC_PhysicalPackage_IsCompatible* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_IsCompatible_Clear_MIReturn(
    ABC_PhysicalPackage_IsCompatible* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_IsCompatible_Set_ElementToCheck(
    ABC_PhysicalPackage_IsCompatible* self,
    const CIM_PhysicalElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_IsCompatible_SetPtr_ElementToCheck(
    ABC_PhysicalPackage_IsCompatible* self,
    const CIM_PhysicalElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL ABC_PhysicalPackage_IsCompatible_Clear_ElementToCheck(
    ABC_PhysicalPackage_IsCompatible* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** ABC_PhysicalPackage provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _ABC_PhysicalPackage_Self ABC_PhysicalPackage_Self;

MI_EXTERN_C void MI_CALL ABC_PhysicalPackage_Load(
    ABC_PhysicalPackage_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_PhysicalPackage_Unload(
    ABC_PhysicalPackage_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL ABC_PhysicalPackage_EnumerateInstances(
    ABC_PhysicalPackage_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL ABC_PhysicalPackage_GetInstance(
    ABC_PhysicalPackage_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_PhysicalPackage* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_PhysicalPackage_CreateInstance(
    ABC_PhysicalPackage_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_PhysicalPackage* newInstance);

MI_EXTERN_C void MI_CALL ABC_PhysicalPackage_ModifyInstance(
    ABC_PhysicalPackage_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_PhysicalPackage* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL ABC_PhysicalPackage_DeleteInstance(
    ABC_PhysicalPackage_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const ABC_PhysicalPackage* instanceName);

MI_EXTERN_C void MI_CALL ABC_PhysicalPackage_Invoke_IsCompatible(
    ABC_PhysicalPackage_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const ABC_PhysicalPackage* instanceName,
    const ABC_PhysicalPackage_IsCompatible* in);


#endif /* _ABC_PhysicalPackage_h */
