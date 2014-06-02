/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_NetworkPolicyServiceCapabilities_h
#define _CIM_NetworkPolicyServiceCapabilities_h

#include <MI.h>
#include "CIM_EnabledLogicalElementCapabilities.h"

/*
**==============================================================================
**
** CIM_NetworkPolicyServiceCapabilities [CIM_NetworkPolicyServiceCapabilities]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_NetworkPolicyServiceCapabilities /* extends CIM_EnabledLogicalElementCapabilities */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Capabilities properties */
    /* CIM_EnabledLogicalElementCapabilities properties */
    MI_ConstBooleanField ElementNameEditSupported;
    MI_ConstUint16Field MaxElementNameLen;
    MI_ConstUint16AField RequestedStatesSupported;
    MI_ConstStringField ElementNameMask;
    MI_ConstUint16AField StateAwareness;
    /* CIM_NetworkPolicyServiceCapabilities properties */
}
CIM_NetworkPolicyServiceCapabilities;

typedef struct _CIM_NetworkPolicyServiceCapabilities_Ref
{
    CIM_NetworkPolicyServiceCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyServiceCapabilities_Ref;

typedef struct _CIM_NetworkPolicyServiceCapabilities_ConstRef
{
    MI_CONST CIM_NetworkPolicyServiceCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyServiceCapabilities_ConstRef;

typedef struct _CIM_NetworkPolicyServiceCapabilities_Array
{
    struct _CIM_NetworkPolicyServiceCapabilities** data;
    MI_Uint32 size;
}
CIM_NetworkPolicyServiceCapabilities_Array;

typedef struct _CIM_NetworkPolicyServiceCapabilities_ConstArray
{
    struct _CIM_NetworkPolicyServiceCapabilities MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_NetworkPolicyServiceCapabilities_ConstArray;

typedef struct _CIM_NetworkPolicyServiceCapabilities_ArrayRef
{
    CIM_NetworkPolicyServiceCapabilities_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyServiceCapabilities_ArrayRef;

typedef struct _CIM_NetworkPolicyServiceCapabilities_ConstArrayRef
{
    CIM_NetworkPolicyServiceCapabilities_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyServiceCapabilities_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_NetworkPolicyServiceCapabilities_rtti;

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Construct(
    _Out_ CIM_NetworkPolicyServiceCapabilities* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_NetworkPolicyServiceCapabilities_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Clone(
    _In_ const CIM_NetworkPolicyServiceCapabilities* self,
    _Outptr_ CIM_NetworkPolicyServiceCapabilities** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_NetworkPolicyServiceCapabilities_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_NetworkPolicyServiceCapabilities_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Destruct(_Inout_ CIM_NetworkPolicyServiceCapabilities* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Delete(_Inout_ CIM_NetworkPolicyServiceCapabilities* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Post(
    _In_ const CIM_NetworkPolicyServiceCapabilities* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Set_InstanceID(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_SetPtr_InstanceID(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Clear_InstanceID(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Set_Caption(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_SetPtr_Caption(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Clear_Caption(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Set_Description(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_SetPtr_Description(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Clear_Description(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Set_ElementName(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_SetPtr_ElementName(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Clear_ElementName(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Set_ElementNameEditSupported(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->ElementNameEditSupported)->value = x;
    ((MI_BooleanField*)&self->ElementNameEditSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Clear_ElementNameEditSupported(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self)
{
    memset((void*)&self->ElementNameEditSupported, 0, sizeof(self->ElementNameEditSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Set_MaxElementNameLen(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MaxElementNameLen)->value = x;
    ((MI_Uint16Field*)&self->MaxElementNameLen)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Clear_MaxElementNameLen(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self)
{
    memset((void*)&self->MaxElementNameLen, 0, sizeof(self->MaxElementNameLen));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Set_RequestedStatesSupported(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_SetPtr_RequestedStatesSupported(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Clear_RequestedStatesSupported(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Set_ElementNameMask(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_SetPtr_ElementNameMask(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Clear_ElementNameMask(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Set_StateAwareness(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_SetPtr_StateAwareness(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyServiceCapabilities_Clear_StateAwareness(
    _Inout_ CIM_NetworkPolicyServiceCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

/*
**==============================================================================
**
** CIM_NetworkPolicyServiceCapabilities provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_NetworkPolicyServiceCapabilities_Self CIM_NetworkPolicyServiceCapabilities_Self;

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyServiceCapabilities_Load(
    _Outptr_result_maybenull_ CIM_NetworkPolicyServiceCapabilities_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyServiceCapabilities_Unload(
    _In_opt_ CIM_NetworkPolicyServiceCapabilities_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyServiceCapabilities_EnumerateInstances(
    _In_opt_ CIM_NetworkPolicyServiceCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyServiceCapabilities_GetInstance(
    _In_opt_ CIM_NetworkPolicyServiceCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyServiceCapabilities* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyServiceCapabilities_CreateInstance(
    _In_opt_ CIM_NetworkPolicyServiceCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyServiceCapabilities* newInstance);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyServiceCapabilities_ModifyInstance(
    _In_opt_ CIM_NetworkPolicyServiceCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyServiceCapabilities* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyServiceCapabilities_DeleteInstance(
    _In_opt_ CIM_NetworkPolicyServiceCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyServiceCapabilities* instanceName);


#endif /* _CIM_NetworkPolicyServiceCapabilities_h */
