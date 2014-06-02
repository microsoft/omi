/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_ResourceAllocationSettingData_h
#define _CIM_ResourceAllocationSettingData_h

#include <MI.h>
#include "CIM_SettingData.h"

/*
**==============================================================================
**
** CIM_ResourceAllocationSettingData [CIM_ResourceAllocationSettingData]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_ResourceAllocationSettingData /* extends CIM_SettingData */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_SettingData properties */
    /* CIM_ResourceAllocationSettingData properties */
    MI_ConstUint16Field ResourceType;
    MI_ConstStringField OtherResourceType;
    MI_ConstStringField ResourceSubType;
    MI_ConstStringField PoolID;
    MI_ConstUint16Field ConsumerVisibility;
    MI_ConstStringAField HostResource;
    MI_ConstStringField AllocationUnits;
    MI_ConstUint64Field VirtualQuantity;
    MI_ConstUint64Field Reservation;
    MI_ConstUint64Field Limit;
    MI_ConstUint32Field Weight;
    MI_ConstBooleanField AutomaticAllocation;
    MI_ConstBooleanField AutomaticDeallocation;
    MI_ConstStringField Parent;
    MI_ConstStringAField Connection;
    MI_ConstStringField Address;
    MI_ConstUint16Field MappingBehavior;
    MI_ConstStringField AddressOnParent;
    MI_ConstStringField VirtualQuantityUnits;
}
CIM_ResourceAllocationSettingData;

typedef struct _CIM_ResourceAllocationSettingData_Ref
{
    CIM_ResourceAllocationSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ResourceAllocationSettingData_Ref;

typedef struct _CIM_ResourceAllocationSettingData_ConstRef
{
    MI_CONST CIM_ResourceAllocationSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ResourceAllocationSettingData_ConstRef;

typedef struct _CIM_ResourceAllocationSettingData_Array
{
    struct _CIM_ResourceAllocationSettingData** data;
    MI_Uint32 size;
}
CIM_ResourceAllocationSettingData_Array;

typedef struct _CIM_ResourceAllocationSettingData_ConstArray
{
    struct _CIM_ResourceAllocationSettingData MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_ResourceAllocationSettingData_ConstArray;

typedef struct _CIM_ResourceAllocationSettingData_ArrayRef
{
    CIM_ResourceAllocationSettingData_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ResourceAllocationSettingData_ArrayRef;

typedef struct _CIM_ResourceAllocationSettingData_ConstArrayRef
{
    CIM_ResourceAllocationSettingData_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ResourceAllocationSettingData_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_ResourceAllocationSettingData_rtti;

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Construct(
    _Out_ CIM_ResourceAllocationSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_ResourceAllocationSettingData_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clone(
    _In_ const CIM_ResourceAllocationSettingData* self,
    _Outptr_ CIM_ResourceAllocationSettingData** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_ResourceAllocationSettingData_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_ResourceAllocationSettingData_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Destruct(_Inout_ CIM_ResourceAllocationSettingData* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Delete(_Inout_ CIM_ResourceAllocationSettingData* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Post(
    _In_ const CIM_ResourceAllocationSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_InstanceID(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_SetPtr_InstanceID(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_InstanceID(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_Caption(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_SetPtr_Caption(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_Caption(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_Description(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_SetPtr_Description(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_Description(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_ElementName(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_SetPtr_ElementName(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_ElementName(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_ResourceType(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ResourceType)->value = x;
    ((MI_Uint16Field*)&self->ResourceType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_ResourceType(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    memset((void*)&self->ResourceType, 0, sizeof(self->ResourceType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_OtherResourceType(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_SetPtr_OtherResourceType(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_OtherResourceType(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_ResourceSubType(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_SetPtr_ResourceSubType(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_ResourceSubType(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_PoolID(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_SetPtr_PoolID(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_PoolID(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_ConsumerVisibility(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ConsumerVisibility)->value = x;
    ((MI_Uint16Field*)&self->ConsumerVisibility)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_ConsumerVisibility(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    memset((void*)&self->ConsumerVisibility, 0, sizeof(self->ConsumerVisibility));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_HostResource(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_SetPtr_HostResource(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_HostResource(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_AllocationUnits(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_SetPtr_AllocationUnits(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_AllocationUnits(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_VirtualQuantity(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->VirtualQuantity)->value = x;
    ((MI_Uint64Field*)&self->VirtualQuantity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_VirtualQuantity(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    memset((void*)&self->VirtualQuantity, 0, sizeof(self->VirtualQuantity));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_Reservation(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->Reservation)->value = x;
    ((MI_Uint64Field*)&self->Reservation)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_Reservation(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    memset((void*)&self->Reservation, 0, sizeof(self->Reservation));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_Limit(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->Limit)->value = x;
    ((MI_Uint64Field*)&self->Limit)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_Limit(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    memset((void*)&self->Limit, 0, sizeof(self->Limit));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_Weight(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Weight)->value = x;
    ((MI_Uint32Field*)&self->Weight)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_Weight(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    memset((void*)&self->Weight, 0, sizeof(self->Weight));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_AutomaticAllocation(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->AutomaticAllocation)->value = x;
    ((MI_BooleanField*)&self->AutomaticAllocation)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_AutomaticAllocation(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    memset((void*)&self->AutomaticAllocation, 0, sizeof(self->AutomaticAllocation));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_AutomaticDeallocation(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->AutomaticDeallocation)->value = x;
    ((MI_BooleanField*)&self->AutomaticDeallocation)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_AutomaticDeallocation(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    memset((void*)&self->AutomaticDeallocation, 0, sizeof(self->AutomaticDeallocation));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_Parent(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_SetPtr_Parent(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_Parent(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_Connection(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_SetPtr_Connection(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_Connection(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_Address(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_SetPtr_Address(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_Address(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_MappingBehavior(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MappingBehavior)->value = x;
    ((MI_Uint16Field*)&self->MappingBehavior)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_MappingBehavior(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    memset((void*)&self->MappingBehavior, 0, sizeof(self->MappingBehavior));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_AddressOnParent(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_SetPtr_AddressOnParent(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_AddressOnParent(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Set_VirtualQuantityUnits(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_SetPtr_VirtualQuantityUnits(
    _Inout_ CIM_ResourceAllocationSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ResourceAllocationSettingData_Clear_VirtualQuantityUnits(
    _Inout_ CIM_ResourceAllocationSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

/*
**==============================================================================
**
** CIM_ResourceAllocationSettingData provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_ResourceAllocationSettingData_Self CIM_ResourceAllocationSettingData_Self;

MI_EXTERN_C void MI_CALL CIM_ResourceAllocationSettingData_Load(
    _Outptr_result_maybenull_ CIM_ResourceAllocationSettingData_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_ResourceAllocationSettingData_Unload(
    _In_opt_ CIM_ResourceAllocationSettingData_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_ResourceAllocationSettingData_EnumerateInstances(
    _In_opt_ CIM_ResourceAllocationSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_ResourceAllocationSettingData_GetInstance(
    _In_opt_ CIM_ResourceAllocationSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ResourceAllocationSettingData* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_ResourceAllocationSettingData_CreateInstance(
    _In_opt_ CIM_ResourceAllocationSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ResourceAllocationSettingData* newInstance);

MI_EXTERN_C void MI_CALL CIM_ResourceAllocationSettingData_ModifyInstance(
    _In_opt_ CIM_ResourceAllocationSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ResourceAllocationSettingData* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_ResourceAllocationSettingData_DeleteInstance(
    _In_opt_ CIM_ResourceAllocationSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_ResourceAllocationSettingData* instanceName);


#endif /* _CIM_ResourceAllocationSettingData_h */
