/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_EnabledLogicalElementCapabilities_h
#define _CIM_EnabledLogicalElementCapabilities_h

#include <MI.h>
#include "CIM_Capabilities.h"

/*
**==============================================================================
**
** CIM_EnabledLogicalElementCapabilities [CIM_EnabledLogicalElementCapabilities]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_EnabledLogicalElementCapabilities /* extends CIM_Capabilities */
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
}
CIM_EnabledLogicalElementCapabilities;

typedef struct _CIM_EnabledLogicalElementCapabilities_Ref
{
    CIM_EnabledLogicalElementCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_EnabledLogicalElementCapabilities_Ref;

typedef struct _CIM_EnabledLogicalElementCapabilities_ConstRef
{
    MI_CONST CIM_EnabledLogicalElementCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_EnabledLogicalElementCapabilities_ConstRef;

typedef struct _CIM_EnabledLogicalElementCapabilities_Array
{
    struct _CIM_EnabledLogicalElementCapabilities** data;
    MI_Uint32 size;
}
CIM_EnabledLogicalElementCapabilities_Array;

typedef struct _CIM_EnabledLogicalElementCapabilities_ConstArray
{
    struct _CIM_EnabledLogicalElementCapabilities MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_EnabledLogicalElementCapabilities_ConstArray;

typedef struct _CIM_EnabledLogicalElementCapabilities_ArrayRef
{
    CIM_EnabledLogicalElementCapabilities_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_EnabledLogicalElementCapabilities_ArrayRef;

typedef struct _CIM_EnabledLogicalElementCapabilities_ConstArrayRef
{
    CIM_EnabledLogicalElementCapabilities_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_EnabledLogicalElementCapabilities_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_EnabledLogicalElementCapabilities_rtti;

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Construct(
    _Out_ CIM_EnabledLogicalElementCapabilities* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_EnabledLogicalElementCapabilities_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clone(
    _In_ const CIM_EnabledLogicalElementCapabilities* self,
    _Outptr_ CIM_EnabledLogicalElementCapabilities** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_EnabledLogicalElementCapabilities_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_EnabledLogicalElementCapabilities_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Destruct(_Inout_ CIM_EnabledLogicalElementCapabilities* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Delete(_Inout_ CIM_EnabledLogicalElementCapabilities* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Post(
    _In_ const CIM_EnabledLogicalElementCapabilities* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Set_InstanceID(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_SetPtr_InstanceID(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clear_InstanceID(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Set_Caption(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_SetPtr_Caption(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clear_Caption(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Set_Description(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_SetPtr_Description(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clear_Description(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Set_ElementName(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_SetPtr_ElementName(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clear_ElementName(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Set_ElementNameEditSupported(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->ElementNameEditSupported)->value = x;
    ((MI_BooleanField*)&self->ElementNameEditSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clear_ElementNameEditSupported(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self)
{
    memset((void*)&self->ElementNameEditSupported, 0, sizeof(self->ElementNameEditSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Set_MaxElementNameLen(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MaxElementNameLen)->value = x;
    ((MI_Uint16Field*)&self->MaxElementNameLen)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clear_MaxElementNameLen(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self)
{
    memset((void*)&self->MaxElementNameLen, 0, sizeof(self->MaxElementNameLen));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Set_RequestedStatesSupported(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_SetPtr_RequestedStatesSupported(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clear_RequestedStatesSupported(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Set_ElementNameMask(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_SetPtr_ElementNameMask(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clear_ElementNameMask(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Set_StateAwareness(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_SetPtr_StateAwareness(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_EnabledLogicalElementCapabilities_Clear_StateAwareness(
    _Inout_ CIM_EnabledLogicalElementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

/*
**==============================================================================
**
** CIM_EnabledLogicalElementCapabilities provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_EnabledLogicalElementCapabilities_Self CIM_EnabledLogicalElementCapabilities_Self;

MI_EXTERN_C void MI_CALL CIM_EnabledLogicalElementCapabilities_Load(
    _Outptr_result_maybenull_ CIM_EnabledLogicalElementCapabilities_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_EnabledLogicalElementCapabilities_Unload(
    _In_opt_ CIM_EnabledLogicalElementCapabilities_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_EnabledLogicalElementCapabilities_EnumerateInstances(
    _In_opt_ CIM_EnabledLogicalElementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_EnabledLogicalElementCapabilities_GetInstance(
    _In_opt_ CIM_EnabledLogicalElementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_EnabledLogicalElementCapabilities* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_EnabledLogicalElementCapabilities_CreateInstance(
    _In_opt_ CIM_EnabledLogicalElementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_EnabledLogicalElementCapabilities* newInstance);

MI_EXTERN_C void MI_CALL CIM_EnabledLogicalElementCapabilities_ModifyInstance(
    _In_opt_ CIM_EnabledLogicalElementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_EnabledLogicalElementCapabilities* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_EnabledLogicalElementCapabilities_DeleteInstance(
    _In_opt_ CIM_EnabledLogicalElementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_EnabledLogicalElementCapabilities* instanceName);


#endif /* _CIM_EnabledLogicalElementCapabilities_h */
