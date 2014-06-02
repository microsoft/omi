/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_AccountSettingData_h
#define _CIM_AccountSettingData_h

#include <MI.h>
#include "CIM_SettingData.h"

/*
**==============================================================================
**
** CIM_AccountSettingData [CIM_AccountSettingData]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_AccountSettingData /* extends CIM_SettingData */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_SettingData properties */
    /* CIM_AccountSettingData properties */
    MI_ConstUint16AField ComplexPasswordRulesEnforced;
    MI_ConstDatetimeField InactivityTimeout;
    MI_ConstDatetimeField MaximumPasswordExpiration;
    MI_ConstUint16Field MaximumSuccessiveLoginFailures;
    MI_ConstUint16Field PasswordHistoryDepth;
}
CIM_AccountSettingData;

typedef struct _CIM_AccountSettingData_Ref
{
    CIM_AccountSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AccountSettingData_Ref;

typedef struct _CIM_AccountSettingData_ConstRef
{
    MI_CONST CIM_AccountSettingData* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AccountSettingData_ConstRef;

typedef struct _CIM_AccountSettingData_Array
{
    struct _CIM_AccountSettingData** data;
    MI_Uint32 size;
}
CIM_AccountSettingData_Array;

typedef struct _CIM_AccountSettingData_ConstArray
{
    struct _CIM_AccountSettingData MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_AccountSettingData_ConstArray;

typedef struct _CIM_AccountSettingData_ArrayRef
{
    CIM_AccountSettingData_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AccountSettingData_ArrayRef;

typedef struct _CIM_AccountSettingData_ConstArrayRef
{
    CIM_AccountSettingData_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AccountSettingData_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_AccountSettingData_rtti;

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Construct(
    _Out_ CIM_AccountSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_AccountSettingData_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Clone(
    _In_ const CIM_AccountSettingData* self,
    _Outptr_ CIM_AccountSettingData** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_AccountSettingData_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_AccountSettingData_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Destruct(_Inout_ CIM_AccountSettingData* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Delete(_Inout_ CIM_AccountSettingData* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Post(
    _In_ const CIM_AccountSettingData* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Set_InstanceID(
    _Inout_ CIM_AccountSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_SetPtr_InstanceID(
    _Inout_ CIM_AccountSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Clear_InstanceID(
    _Inout_ CIM_AccountSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Set_Caption(
    _Inout_ CIM_AccountSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_SetPtr_Caption(
    _Inout_ CIM_AccountSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Clear_Caption(
    _Inout_ CIM_AccountSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Set_Description(
    _Inout_ CIM_AccountSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_SetPtr_Description(
    _Inout_ CIM_AccountSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Clear_Description(
    _Inout_ CIM_AccountSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Set_ElementName(
    _Inout_ CIM_AccountSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_SetPtr_ElementName(
    _Inout_ CIM_AccountSettingData* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Clear_ElementName(
    _Inout_ CIM_AccountSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Set_ComplexPasswordRulesEnforced(
    _Inout_ CIM_AccountSettingData* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_SetPtr_ComplexPasswordRulesEnforced(
    _Inout_ CIM_AccountSettingData* self,
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

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Clear_ComplexPasswordRulesEnforced(
    _Inout_ CIM_AccountSettingData* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Set_InactivityTimeout(
    _Inout_ CIM_AccountSettingData* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InactivityTimeout)->value = x;
    ((MI_DatetimeField*)&self->InactivityTimeout)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Clear_InactivityTimeout(
    _Inout_ CIM_AccountSettingData* self)
{
    memset((void*)&self->InactivityTimeout, 0, sizeof(self->InactivityTimeout));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Set_MaximumPasswordExpiration(
    _Inout_ CIM_AccountSettingData* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MaximumPasswordExpiration)->value = x;
    ((MI_DatetimeField*)&self->MaximumPasswordExpiration)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Clear_MaximumPasswordExpiration(
    _Inout_ CIM_AccountSettingData* self)
{
    memset((void*)&self->MaximumPasswordExpiration, 0, sizeof(self->MaximumPasswordExpiration));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Set_MaximumSuccessiveLoginFailures(
    _Inout_ CIM_AccountSettingData* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->MaximumSuccessiveLoginFailures)->value = x;
    ((MI_Uint16Field*)&self->MaximumSuccessiveLoginFailures)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Clear_MaximumSuccessiveLoginFailures(
    _Inout_ CIM_AccountSettingData* self)
{
    memset((void*)&self->MaximumSuccessiveLoginFailures, 0, sizeof(self->MaximumSuccessiveLoginFailures));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Set_PasswordHistoryDepth(
    _Inout_ CIM_AccountSettingData* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PasswordHistoryDepth)->value = x;
    ((MI_Uint16Field*)&self->PasswordHistoryDepth)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_AccountSettingData_Clear_PasswordHistoryDepth(
    _Inout_ CIM_AccountSettingData* self)
{
    memset((void*)&self->PasswordHistoryDepth, 0, sizeof(self->PasswordHistoryDepth));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_AccountSettingData provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_AccountSettingData_Self CIM_AccountSettingData_Self;

MI_EXTERN_C void MI_CALL CIM_AccountSettingData_Load(
    _Outptr_result_maybenull_ CIM_AccountSettingData_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_AccountSettingData_Unload(
    _In_opt_ CIM_AccountSettingData_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_AccountSettingData_EnumerateInstances(
    _In_opt_ CIM_AccountSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_AccountSettingData_GetInstance(
    _In_opt_ CIM_AccountSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AccountSettingData* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_AccountSettingData_CreateInstance(
    _In_opt_ CIM_AccountSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AccountSettingData* newInstance);

MI_EXTERN_C void MI_CALL CIM_AccountSettingData_ModifyInstance(
    _In_opt_ CIM_AccountSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AccountSettingData* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_AccountSettingData_DeleteInstance(
    _In_opt_ CIM_AccountSettingData_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_AccountSettingData* instanceName);


#endif /* _CIM_AccountSettingData_h */
