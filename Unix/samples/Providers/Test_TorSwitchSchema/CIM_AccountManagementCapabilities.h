/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_AccountManagementCapabilities_h
#define _CIM_AccountManagementCapabilities_h

#include <MI.h>
#include "CIM_EnabledLogicalElementCapabilities.h"

/*
**==============================================================================
**
** CIM_AccountManagementCapabilities [CIM_AccountManagementCapabilities]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_AccountManagementCapabilities /* extends CIM_EnabledLogicalElementCapabilities */
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
    /* CIM_AccountManagementCapabilities properties */
    MI_ConstUint16AField OperationsSupported;
    MI_ConstStringAField OtherSupportedUserPasswordEncryptionAlgorithms;
    MI_ConstUint16AField SupportedUserPasswordEncryptionAlgorithms;
    MI_ConstStringField UserPasswordEncryptionSalt;
    MI_ConstUint16Field MaximumAccountsSupported;
    MI_ConstUint32AField SupportedUserPasswordEncodings;
}
CIM_AccountManagementCapabilities;

typedef struct _CIM_AccountManagementCapabilities_Ref
{
    CIM_AccountManagementCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AccountManagementCapabilities_Ref;

typedef struct _CIM_AccountManagementCapabilities_ConstRef
{
    MI_CONST CIM_AccountManagementCapabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AccountManagementCapabilities_ConstRef;

typedef struct _CIM_AccountManagementCapabilities_Array
{
    struct _CIM_AccountManagementCapabilities** data;
    MI_Uint32 size;
}
CIM_AccountManagementCapabilities_Array;

typedef struct _CIM_AccountManagementCapabilities_ConstArray
{
    struct _CIM_AccountManagementCapabilities MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_AccountManagementCapabilities_ConstArray;

typedef struct _CIM_AccountManagementCapabilities_ArrayRef
{
    CIM_AccountManagementCapabilities_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AccountManagementCapabilities_ArrayRef;

typedef struct _CIM_AccountManagementCapabilities_ConstArrayRef
{
    CIM_AccountManagementCapabilities_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AccountManagementCapabilities_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_AccountManagementCapabilities_rtti;

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Construct(
    _Out_ CIM_AccountManagementCapabilities* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_AccountManagementCapabilities_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Clone(
    _In_ const CIM_AccountManagementCapabilities* self,
    _Outptr_ CIM_AccountManagementCapabilities** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_AccountManagementCapabilities_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_AccountManagementCapabilities_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Destruct(_Inout_ CIM_AccountManagementCapabilities* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Delete(_Inout_ CIM_AccountManagementCapabilities* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Post(
    _In_ const CIM_AccountManagementCapabilities* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Set_InstanceID(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_SetPtr_InstanceID(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Clear_InstanceID(
    _Inout_ CIM_AccountManagementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Set_Caption(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_SetPtr_Caption(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Clear_Caption(
    _Inout_ CIM_AccountManagementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Set_Description(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_SetPtr_Description(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Clear_Description(
    _Inout_ CIM_AccountManagementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Set_ElementName(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_SetPtr_ElementName(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Clear_ElementName(
    _Inout_ CIM_AccountManagementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Set_ElementNameEditSupported(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->ElementNameEditSupported)->value = x;
    ((MI_BooleanField*)&self->ElementNameEditSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Clear_ElementNameEditSupported(
    _Inout_ CIM_AccountManagementCapabilities* self)
{
    memset((void*)&self->ElementNameEditSupported, 0, sizeof(self->ElementNameEditSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Set_MaxElementNameLen(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MaxElementNameLen)->value = x;
    ((MI_Uint16Field*)&self->MaxElementNameLen)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Clear_MaxElementNameLen(
    _Inout_ CIM_AccountManagementCapabilities* self)
{
    memset((void*)&self->MaxElementNameLen, 0, sizeof(self->MaxElementNameLen));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Set_RequestedStatesSupported(
    _Inout_ CIM_AccountManagementCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_SetPtr_RequestedStatesSupported(
    _Inout_ CIM_AccountManagementCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Clear_RequestedStatesSupported(
    _Inout_ CIM_AccountManagementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Set_ElementNameMask(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_SetPtr_ElementNameMask(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Clear_ElementNameMask(
    _Inout_ CIM_AccountManagementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Set_StateAwareness(
    _Inout_ CIM_AccountManagementCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_SetPtr_StateAwareness(
    _Inout_ CIM_AccountManagementCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Clear_StateAwareness(
    _Inout_ CIM_AccountManagementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Set_OperationsSupported(
    _Inout_ CIM_AccountManagementCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_SetPtr_OperationsSupported(
    _Inout_ CIM_AccountManagementCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Clear_OperationsSupported(
    _Inout_ CIM_AccountManagementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Set_OtherSupportedUserPasswordEncryptionAlgorithms(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_SetPtr_OtherSupportedUserPasswordEncryptionAlgorithms(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Clear_OtherSupportedUserPasswordEncryptionAlgorithms(
    _Inout_ CIM_AccountManagementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Set_SupportedUserPasswordEncryptionAlgorithms(
    _Inout_ CIM_AccountManagementCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_SetPtr_SupportedUserPasswordEncryptionAlgorithms(
    _Inout_ CIM_AccountManagementCapabilities* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Clear_SupportedUserPasswordEncryptionAlgorithms(
    _Inout_ CIM_AccountManagementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Set_UserPasswordEncryptionSalt(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_SetPtr_UserPasswordEncryptionSalt(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Clear_UserPasswordEncryptionSalt(
    _Inout_ CIM_AccountManagementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Set_MaximumAccountsSupported(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MaximumAccountsSupported)->value = x;
    ((MI_Uint16Field*)&self->MaximumAccountsSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Clear_MaximumAccountsSupported(
    _Inout_ CIM_AccountManagementCapabilities* self)
{
    memset((void*)&self->MaximumAccountsSupported, 0, sizeof(self->MaximumAccountsSupported));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Set_SupportedUserPasswordEncodings(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_reads_opt_(size) const MI_Uint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&arr,
        MI_UINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_SetPtr_SupportedUserPasswordEncodings(
    _Inout_ CIM_AccountManagementCapabilities* self,
    _In_reads_opt_(size) const MI_Uint32* data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&arr,
        MI_UINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountManagementCapabilities_Clear_SupportedUserPasswordEncodings(
    _Inout_ CIM_AccountManagementCapabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

/*
**==============================================================================
**
** CIM_AccountManagementCapabilities provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_AccountManagementCapabilities_Self CIM_AccountManagementCapabilities_Self;

MI_EXTERN_C void MI_CALL CIM_AccountManagementCapabilities_Load(
    _Outptr_result_maybenull_ CIM_AccountManagementCapabilities_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_AccountManagementCapabilities_Unload(
    _In_opt_ CIM_AccountManagementCapabilities_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_AccountManagementCapabilities_EnumerateInstances(
    _In_opt_ CIM_AccountManagementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_AccountManagementCapabilities_GetInstance(
    _In_opt_ CIM_AccountManagementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AccountManagementCapabilities* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_AccountManagementCapabilities_CreateInstance(
    _In_opt_ CIM_AccountManagementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AccountManagementCapabilities* newInstance);

MI_EXTERN_C void MI_CALL CIM_AccountManagementCapabilities_ModifyInstance(
    _In_opt_ CIM_AccountManagementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AccountManagementCapabilities* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_AccountManagementCapabilities_DeleteInstance(
    _In_opt_ CIM_AccountManagementCapabilities_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AccountManagementCapabilities* instanceName);


#endif /* _CIM_AccountManagementCapabilities_h */
