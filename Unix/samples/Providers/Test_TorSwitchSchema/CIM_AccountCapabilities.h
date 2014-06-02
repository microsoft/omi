/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_AccountCapabilities_h
#define _CIM_AccountCapabilities_h

#include <MI.h>
#include "CIM_EnabledLogicalElementCapabilities.h"

/*
**==============================================================================
**
** CIM_AccountCapabilities [CIM_AccountCapabilities]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_AccountCapabilities /* extends CIM_EnabledLogicalElementCapabilities */
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
    /* CIM_AccountCapabilities properties */
    MI_ConstUint16Field PasswordHistory;
    MI_ConstDatetimeField MaximumPasswordAge;
    MI_ConstUint16AField ComplexPasswordRulesSupported;
    MI_ConstBooleanField DisableOnInactivity;
}
CIM_AccountCapabilities;

typedef struct _CIM_AccountCapabilities_Ref
{
    CIM_AccountCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AccountCapabilities_Ref;

typedef struct _CIM_AccountCapabilities_ConstRef
{
    MI_CONST CIM_AccountCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AccountCapabilities_ConstRef;

typedef struct _CIM_AccountCapabilities_Array
{
    struct _CIM_AccountCapabilities** data;
    MI_Uint32 size;
}
CIM_AccountCapabilities_Array;

typedef struct _CIM_AccountCapabilities_ConstArray
{
    struct _CIM_AccountCapabilities MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_AccountCapabilities_ConstArray;

typedef struct _CIM_AccountCapabilities_ArrayRef
{
    CIM_AccountCapabilities_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AccountCapabilities_ArrayRef;

typedef struct _CIM_AccountCapabilities_ConstArrayRef
{
    CIM_AccountCapabilities_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AccountCapabilities_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_AccountCapabilities_rtti;

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Construct(
    _Out_ CIM_AccountCapabilities* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_AccountCapabilities_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Clone(
    _In_ const CIM_AccountCapabilities* self,
    _Outptr_ CIM_AccountCapabilities** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_AccountCapabilities_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_AccountCapabilities_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Destruct(_Inout_ CIM_AccountCapabilities* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Delete(_Inout_ CIM_AccountCapabilities* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Post(
    _In_ const CIM_AccountCapabilities* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Set_InstanceID(
    _Inout_ CIM_AccountCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_SetPtr_InstanceID(
    _Inout_ CIM_AccountCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Clear_InstanceID(
    _Inout_ CIM_AccountCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Set_Caption(
    _Inout_ CIM_AccountCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_SetPtr_Caption(
    _Inout_ CIM_AccountCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Clear_Caption(
    _Inout_ CIM_AccountCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Set_Description(
    _Inout_ CIM_AccountCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_SetPtr_Description(
    _Inout_ CIM_AccountCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Clear_Description(
    _Inout_ CIM_AccountCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Set_ElementName(
    _Inout_ CIM_AccountCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_SetPtr_ElementName(
    _Inout_ CIM_AccountCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Clear_ElementName(
    _Inout_ CIM_AccountCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Set_ElementNameEditSupported(
    _Inout_ CIM_AccountCapabilities* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->ElementNameEditSupported)->value = x;
    ((MI_BooleanField*)&self->ElementNameEditSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Clear_ElementNameEditSupported(
    _Inout_ CIM_AccountCapabilities* self)
{
    memset((void*)&self->ElementNameEditSupported, 0, sizeof(self->ElementNameEditSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Set_MaxElementNameLen(
    _Inout_ CIM_AccountCapabilities* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MaxElementNameLen)->value = x;
    ((MI_Uint16Field*)&self->MaxElementNameLen)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Clear_MaxElementNameLen(
    _Inout_ CIM_AccountCapabilities* self)
{
    memset((void*)&self->MaxElementNameLen, 0, sizeof(self->MaxElementNameLen));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Set_RequestedStatesSupported(
    _Inout_ CIM_AccountCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_SetPtr_RequestedStatesSupported(
    _Inout_ CIM_AccountCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Clear_RequestedStatesSupported(
    _Inout_ CIM_AccountCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Set_ElementNameMask(
    _Inout_ CIM_AccountCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_SetPtr_ElementNameMask(
    _Inout_ CIM_AccountCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Clear_ElementNameMask(
    _Inout_ CIM_AccountCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Set_StateAwareness(
    _Inout_ CIM_AccountCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_SetPtr_StateAwareness(
    _Inout_ CIM_AccountCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Clear_StateAwareness(
    _Inout_ CIM_AccountCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Set_PasswordHistory(
    _Inout_ CIM_AccountCapabilities* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PasswordHistory)->value = x;
    ((MI_Uint16Field*)&self->PasswordHistory)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Clear_PasswordHistory(
    _Inout_ CIM_AccountCapabilities* self)
{
    memset((void*)&self->PasswordHistory, 0, sizeof(self->PasswordHistory));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Set_MaximumPasswordAge(
    _Inout_ CIM_AccountCapabilities* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MaximumPasswordAge)->value = x;
    ((MI_DatetimeField*)&self->MaximumPasswordAge)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Clear_MaximumPasswordAge(
    _Inout_ CIM_AccountCapabilities* self)
{
    memset((void*)&self->MaximumPasswordAge, 0, sizeof(self->MaximumPasswordAge));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Set_ComplexPasswordRulesSupported(
    _Inout_ CIM_AccountCapabilities* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_SetPtr_ComplexPasswordRulesSupported(
    _Inout_ CIM_AccountCapabilities* self,
    _In_reads_opt_(size) const MI_Uint16* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Clear_ComplexPasswordRulesSupported(
    _Inout_ CIM_AccountCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Set_DisableOnInactivity(
    _Inout_ CIM_AccountCapabilities* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->DisableOnInactivity)->value = x;
    ((MI_BooleanField*)&self->DisableOnInactivity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountCapabilities_Clear_DisableOnInactivity(
    _Inout_ CIM_AccountCapabilities* self)
{
    memset((void*)&self->DisableOnInactivity, 0, sizeof(self->DisableOnInactivity));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_AccountCapabilities provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_AccountCapabilities_Self CIM_AccountCapabilities_Self;

MI_EXTERN_C void MI_CALL CIM_AccountCapabilities_Load(
    _Outptr_result_maybenull_ CIM_AccountCapabilities_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_AccountCapabilities_Unload(
    _In_opt_ CIM_AccountCapabilities_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_AccountCapabilities_EnumerateInstances(
    _In_opt_ CIM_AccountCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_AccountCapabilities_GetInstance(
    _In_opt_ CIM_AccountCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AccountCapabilities* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_AccountCapabilities_CreateInstance(
    _In_opt_ CIM_AccountCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AccountCapabilities* newInstance);

MI_EXTERN_C void MI_CALL CIM_AccountCapabilities_ModifyInstance(
    _In_opt_ CIM_AccountCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AccountCapabilities* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_AccountCapabilities_DeleteInstance(
    _In_opt_ CIM_AccountCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AccountCapabilities* instanceName);


#endif /* _CIM_AccountCapabilities_h */
