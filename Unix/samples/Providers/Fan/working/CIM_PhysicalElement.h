/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_PhysicalElement_h
#define _CIM_PhysicalElement_h

#include <MI.h>
#include "CIM_ManagedSystemElement.h"

/*
**==============================================================================
**
** CIM_PhysicalElement [CIM_PhysicalElement]
**
** Keys:
**    Tag
**    CreationClassName
**
**==============================================================================
*/

typedef struct _CIM_PhysicalElement /* extends CIM_ManagedSystemElement */
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
}
CIM_PhysicalElement;

typedef struct _CIM_PhysicalElement_Ref
{
    CIM_PhysicalElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PhysicalElement_Ref;

typedef struct _CIM_PhysicalElement_ConstRef
{
    MI_CONST CIM_PhysicalElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PhysicalElement_ConstRef;

typedef struct _CIM_PhysicalElement_Array
{
    struct _CIM_PhysicalElement** data;
    MI_Uint32 size;
}
CIM_PhysicalElement_Array;

typedef struct _CIM_PhysicalElement_ConstArray
{
    struct _CIM_PhysicalElement MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_PhysicalElement_ConstArray;

typedef struct _CIM_PhysicalElement_ArrayRef
{
    CIM_PhysicalElement_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PhysicalElement_ArrayRef;

typedef struct _CIM_PhysicalElement_ConstArrayRef
{
    CIM_PhysicalElement_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PhysicalElement_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_PhysicalElement_rtti;

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Construct(
    CIM_PhysicalElement* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_PhysicalElement_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clone(
    const CIM_PhysicalElement* self,
    CIM_PhysicalElement** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_PhysicalElement_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_PhysicalElement_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Destruct(CIM_PhysicalElement* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Delete(CIM_PhysicalElement* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Post(
    const CIM_PhysicalElement* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_InstanceID(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_InstanceID(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_InstanceID(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_Caption(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_Caption(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_Caption(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_Description(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_Description(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_Description(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_ElementName(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_ElementName(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_ElementName(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_InstallDate(
    CIM_PhysicalElement* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_InstallDate(
    CIM_PhysicalElement* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_Name(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_Name(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_Name(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_OperationalStatus(
    CIM_PhysicalElement* self,
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_OperationalStatus(
    CIM_PhysicalElement* self,
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_OperationalStatus(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_StatusDescriptions(
    CIM_PhysicalElement* self,
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_StatusDescriptions(
    CIM_PhysicalElement* self,
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

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_StatusDescriptions(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_Status(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_Status(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_Status(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_HealthState(
    CIM_PhysicalElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_HealthState(
    CIM_PhysicalElement* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_CommunicationStatus(
    CIM_PhysicalElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_CommunicationStatus(
    CIM_PhysicalElement* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_DetailedStatus(
    CIM_PhysicalElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_DetailedStatus(
    CIM_PhysicalElement* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_OperatingStatus(
    CIM_PhysicalElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_OperatingStatus(
    CIM_PhysicalElement* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_PrimaryStatus(
    CIM_PhysicalElement* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_PrimaryStatus(
    CIM_PhysicalElement* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_Tag(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_Tag(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_Tag(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_CreationClassName(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_CreationClassName(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_CreationClassName(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_Manufacturer(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_Manufacturer(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_Manufacturer(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_Model(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_Model(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_Model(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_SKU(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_SKU(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_SKU(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_SerialNumber(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_SerialNumber(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_SerialNumber(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_Version(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_Version(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_Version(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        20);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_PartNumber(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_PartNumber(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_PartNumber(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_OtherIdentifyingInfo(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_OtherIdentifyingInfo(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_OtherIdentifyingInfo(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_PoweredOn(
    CIM_PhysicalElement* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->PoweredOn)->value = x;
    ((MI_BooleanField*)&self->PoweredOn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_PoweredOn(
    CIM_PhysicalElement* self)
{
    memset((void*)&self->PoweredOn, 0, sizeof(self->PoweredOn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_ManufactureDate(
    CIM_PhysicalElement* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->ManufactureDate)->value = x;
    ((MI_DatetimeField*)&self->ManufactureDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_ManufactureDate(
    CIM_PhysicalElement* self)
{
    memset((void*)&self->ManufactureDate, 0, sizeof(self->ManufactureDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_VendorEquipmentType(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_VendorEquipmentType(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_VendorEquipmentType(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        25);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_UserTracking(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_SetPtr_UserTracking(
    CIM_PhysicalElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_UserTracking(
    CIM_PhysicalElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Set_CanBeFRUed(
    CIM_PhysicalElement* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->CanBeFRUed)->value = x;
    ((MI_BooleanField*)&self->CanBeFRUed)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PhysicalElement_Clear_CanBeFRUed(
    CIM_PhysicalElement* self)
{
    memset((void*)&self->CanBeFRUed, 0, sizeof(self->CanBeFRUed));
    return MI_RESULT_OK;
}


#endif /* _CIM_PhysicalElement_h */
