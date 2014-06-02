/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_AllocationCapabilities_h
#define _CIM_AllocationCapabilities_h

#include <MI.h>
#include "CIM_Capabilities.h"

/*
**==============================================================================
**
** CIM_AllocationCapabilities [CIM_AllocationCapabilities]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_AllocationCapabilities /* extends CIM_Capabilities */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Capabilities properties */
    /* CIM_AllocationCapabilities properties */
    MI_ConstUint16Field ResourceType;
    MI_ConstStringField OtherResourceType;
    MI_ConstStringField ResourceSubType;
    MI_ConstUint16Field RequestTypesSupported;
    MI_ConstUint16Field SharingMode;
    MI_ConstUint16AField SupportedAddStates;
    MI_ConstUint16AField SupportedRemoveStates;
}
CIM_AllocationCapabilities;

typedef struct _CIM_AllocationCapabilities_Ref
{
    CIM_AllocationCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AllocationCapabilities_Ref;

typedef struct _CIM_AllocationCapabilities_ConstRef
{
    MI_CONST CIM_AllocationCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AllocationCapabilities_ConstRef;

typedef struct _CIM_AllocationCapabilities_Array
{
    struct _CIM_AllocationCapabilities** data;
    MI_Uint32 size;
}
CIM_AllocationCapabilities_Array;

typedef struct _CIM_AllocationCapabilities_ConstArray
{
    struct _CIM_AllocationCapabilities MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_AllocationCapabilities_ConstArray;

typedef struct _CIM_AllocationCapabilities_ArrayRef
{
    CIM_AllocationCapabilities_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AllocationCapabilities_ArrayRef;

typedef struct _CIM_AllocationCapabilities_ConstArrayRef
{
    CIM_AllocationCapabilities_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AllocationCapabilities_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_AllocationCapabilities_rtti;

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Construct(
    _Out_ CIM_AllocationCapabilities* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_AllocationCapabilities_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Clone(
    _In_ const CIM_AllocationCapabilities* self,
    _Outptr_ CIM_AllocationCapabilities** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_AllocationCapabilities_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_AllocationCapabilities_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Destruct(_Inout_ CIM_AllocationCapabilities* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Delete(_Inout_ CIM_AllocationCapabilities* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Post(
    _In_ const CIM_AllocationCapabilities* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Set_InstanceID(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_SetPtr_InstanceID(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Clear_InstanceID(
    _Inout_ CIM_AllocationCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Set_Caption(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_SetPtr_Caption(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Clear_Caption(
    _Inout_ CIM_AllocationCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Set_Description(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_SetPtr_Description(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Clear_Description(
    _Inout_ CIM_AllocationCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Set_ElementName(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_SetPtr_ElementName(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Clear_ElementName(
    _Inout_ CIM_AllocationCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Set_ResourceType(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ResourceType)->value = x;
    ((MI_Uint16Field*)&self->ResourceType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Clear_ResourceType(
    _Inout_ CIM_AllocationCapabilities* self)
{
    memset((void*)&self->ResourceType, 0, sizeof(self->ResourceType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Set_OtherResourceType(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_SetPtr_OtherResourceType(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Clear_OtherResourceType(
    _Inout_ CIM_AllocationCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Set_ResourceSubType(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_SetPtr_ResourceSubType(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Clear_ResourceSubType(
    _Inout_ CIM_AllocationCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Set_RequestTypesSupported(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestTypesSupported)->value = x;
    ((MI_Uint16Field*)&self->RequestTypesSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Clear_RequestTypesSupported(
    _Inout_ CIM_AllocationCapabilities* self)
{
    memset((void*)&self->RequestTypesSupported, 0, sizeof(self->RequestTypesSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Set_SharingMode(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->SharingMode)->value = x;
    ((MI_Uint16Field*)&self->SharingMode)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Clear_SharingMode(
    _Inout_ CIM_AllocationCapabilities* self)
{
    memset((void*)&self->SharingMode, 0, sizeof(self->SharingMode));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Set_SupportedAddStates(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_SetPtr_SupportedAddStates(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Clear_SupportedAddStates(
    _Inout_ CIM_AllocationCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Set_SupportedRemoveStates(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_SetPtr_SupportedRemoveStates(
    _Inout_ CIM_AllocationCapabilities* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AllocationCapabilities_Clear_SupportedRemoveStates(
    _Inout_ CIM_AllocationCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

/*
**==============================================================================
**
** CIM_AllocationCapabilities provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_AllocationCapabilities_Self CIM_AllocationCapabilities_Self;

MI_EXTERN_C void MI_CALL CIM_AllocationCapabilities_Load(
    _Outptr_result_maybenull_ CIM_AllocationCapabilities_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_AllocationCapabilities_Unload(
    _In_opt_ CIM_AllocationCapabilities_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_AllocationCapabilities_EnumerateInstances(
    _In_opt_ CIM_AllocationCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_AllocationCapabilities_GetInstance(
    _In_opt_ CIM_AllocationCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AllocationCapabilities* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_AllocationCapabilities_CreateInstance(
    _In_opt_ CIM_AllocationCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AllocationCapabilities* newInstance);

MI_EXTERN_C void MI_CALL CIM_AllocationCapabilities_ModifyInstance(
    _In_opt_ CIM_AllocationCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AllocationCapabilities* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_AllocationCapabilities_DeleteInstance(
    _In_opt_ CIM_AllocationCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AllocationCapabilities* instanceName);


#endif /* _CIM_AllocationCapabilities_h */
