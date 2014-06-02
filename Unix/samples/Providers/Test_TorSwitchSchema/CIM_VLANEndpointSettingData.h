/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_VLANEndpointSettingData_h
#define _CIM_VLANEndpointSettingData_h

#include <MI.h>
#include "CIM_SettingData.h"

/*
**==============================================================================
**
** CIM_VLANEndpointSettingData [CIM_VLANEndpointSettingData]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_VLANEndpointSettingData /* extends CIM_SettingData */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_SettingData properties */
    /* CIM_VLANEndpointSettingData properties */
    MI_ConstUint16AField PruneEligibleVLANList;
    MI_ConstUint16Field NativeVLAN;
    MI_ConstUint16Field DefaultVLAN;
    MI_ConstUint16AField TrunkedVLANList;
    MI_ConstUint16Field AccessVLAN;
}
CIM_VLANEndpointSettingData;

typedef struct _CIM_VLANEndpointSettingData_Ref
{
    CIM_VLANEndpointSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_VLANEndpointSettingData_Ref;

typedef struct _CIM_VLANEndpointSettingData_ConstRef
{
    MI_CONST CIM_VLANEndpointSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_VLANEndpointSettingData_ConstRef;

typedef struct _CIM_VLANEndpointSettingData_Array
{
    struct _CIM_VLANEndpointSettingData** data;
    MI_Uint32 size;
}
CIM_VLANEndpointSettingData_Array;

typedef struct _CIM_VLANEndpointSettingData_ConstArray
{
    struct _CIM_VLANEndpointSettingData MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_VLANEndpointSettingData_ConstArray;

typedef struct _CIM_VLANEndpointSettingData_ArrayRef
{
    CIM_VLANEndpointSettingData_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_VLANEndpointSettingData_ArrayRef;

typedef struct _CIM_VLANEndpointSettingData_ConstArrayRef
{
    CIM_VLANEndpointSettingData_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_VLANEndpointSettingData_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_VLANEndpointSettingData_rtti;

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Construct(
    _Out_ CIM_VLANEndpointSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_VLANEndpointSettingData_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Clone(
    _In_ const CIM_VLANEndpointSettingData* self,
    _Outptr_ CIM_VLANEndpointSettingData** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_VLANEndpointSettingData_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_VLANEndpointSettingData_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Destruct(_Inout_ CIM_VLANEndpointSettingData* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Delete(_Inout_ CIM_VLANEndpointSettingData* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Post(
    _In_ const CIM_VLANEndpointSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Set_InstanceID(
    _Inout_ CIM_VLANEndpointSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_SetPtr_InstanceID(
    _Inout_ CIM_VLANEndpointSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Clear_InstanceID(
    _Inout_ CIM_VLANEndpointSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Set_Caption(
    _Inout_ CIM_VLANEndpointSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_SetPtr_Caption(
    _Inout_ CIM_VLANEndpointSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Clear_Caption(
    _Inout_ CIM_VLANEndpointSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Set_Description(
    _Inout_ CIM_VLANEndpointSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_SetPtr_Description(
    _Inout_ CIM_VLANEndpointSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Clear_Description(
    _Inout_ CIM_VLANEndpointSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Set_ElementName(
    _Inout_ CIM_VLANEndpointSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_SetPtr_ElementName(
    _Inout_ CIM_VLANEndpointSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Clear_ElementName(
    _Inout_ CIM_VLANEndpointSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Set_PruneEligibleVLANList(
    _Inout_ CIM_VLANEndpointSettingData* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_SetPtr_PruneEligibleVLANList(
    _Inout_ CIM_VLANEndpointSettingData* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Clear_PruneEligibleVLANList(
    _Inout_ CIM_VLANEndpointSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Set_NativeVLAN(
    _Inout_ CIM_VLANEndpointSettingData* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->NativeVLAN)->value = x;
    ((MI_Uint16Field*)&self->NativeVLAN)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Clear_NativeVLAN(
    _Inout_ CIM_VLANEndpointSettingData* self)
{
    memset((void*)&self->NativeVLAN, 0, sizeof(self->NativeVLAN));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Set_DefaultVLAN(
    _Inout_ CIM_VLANEndpointSettingData* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DefaultVLAN)->value = x;
    ((MI_Uint16Field*)&self->DefaultVLAN)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Clear_DefaultVLAN(
    _Inout_ CIM_VLANEndpointSettingData* self)
{
    memset((void*)&self->DefaultVLAN, 0, sizeof(self->DefaultVLAN));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Set_TrunkedVLANList(
    _Inout_ CIM_VLANEndpointSettingData* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_SetPtr_TrunkedVLANList(
    _Inout_ CIM_VLANEndpointSettingData* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Clear_TrunkedVLANList(
    _Inout_ CIM_VLANEndpointSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Set_AccessVLAN(
    _Inout_ CIM_VLANEndpointSettingData* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->AccessVLAN)->value = x;
    ((MI_Uint16Field*)&self->AccessVLAN)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_VLANEndpointSettingData_Clear_AccessVLAN(
    _Inout_ CIM_VLANEndpointSettingData* self)
{
    memset((void*)&self->AccessVLAN, 0, sizeof(self->AccessVLAN));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_VLANEndpointSettingData provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_VLANEndpointSettingData_Self CIM_VLANEndpointSettingData_Self;

MI_EXTERN_C void MI_CALL CIM_VLANEndpointSettingData_Load(
    _Outptr_result_maybenull_ CIM_VLANEndpointSettingData_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_VLANEndpointSettingData_Unload(
    _In_opt_ CIM_VLANEndpointSettingData_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_VLANEndpointSettingData_EnumerateInstances(
    _In_opt_ CIM_VLANEndpointSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_VLANEndpointSettingData_GetInstance(
    _In_opt_ CIM_VLANEndpointSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_VLANEndpointSettingData* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_VLANEndpointSettingData_CreateInstance(
    _In_opt_ CIM_VLANEndpointSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_VLANEndpointSettingData* newInstance);

MI_EXTERN_C void MI_CALL CIM_VLANEndpointSettingData_ModifyInstance(
    _In_opt_ CIM_VLANEndpointSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_VLANEndpointSettingData* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_VLANEndpointSettingData_DeleteInstance(
    _In_opt_ CIM_VLANEndpointSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_VLANEndpointSettingData* instanceName);


#endif /* _CIM_VLANEndpointSettingData_h */
