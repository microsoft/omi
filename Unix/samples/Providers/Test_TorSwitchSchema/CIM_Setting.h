/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_Setting_h
#define _CIM_Setting_h

#include <MI.h>
#include "CIM_ManagedElement.h"
#include "CIM_ManagedSystemElement.h"
#include "CIM_CollectionOfMSEs.h"

/*
**==============================================================================
**
** CIM_Setting [CIM_Setting]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_Setting /* extends CIM_ManagedElement */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Setting properties */
    MI_ConstStringField SettingID;
}
CIM_Setting;

typedef struct _CIM_Setting_Ref
{
    CIM_Setting* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Setting_Ref;

typedef struct _CIM_Setting_ConstRef
{
    MI_CONST CIM_Setting* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Setting_ConstRef;

typedef struct _CIM_Setting_Array
{
    struct _CIM_Setting** data;
    MI_Uint32 size;
}
CIM_Setting_Array;

typedef struct _CIM_Setting_ConstArray
{
    struct _CIM_Setting MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_Setting_ConstArray;

typedef struct _CIM_Setting_ArrayRef
{
    CIM_Setting_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Setting_ArrayRef;

typedef struct _CIM_Setting_ConstArrayRef
{
    CIM_Setting_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Setting_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_Setting_rtti;

MI_INLINE MI_Result MI_CALL CIM_Setting_Construct(
    _Out_ CIM_Setting* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_Setting_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_Clone(
    _In_ const CIM_Setting* self,
    _Outptr_ CIM_Setting** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_Setting_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_Setting_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_Destruct(_Inout_ CIM_Setting* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_Delete(_Inout_ CIM_Setting* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_Post(
    _In_ const CIM_Setting* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_Set_InstanceID(
    _Inout_ CIM_Setting* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_SetPtr_InstanceID(
    _Inout_ CIM_Setting* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_Clear_InstanceID(
    _Inout_ CIM_Setting* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_Set_Caption(
    _Inout_ CIM_Setting* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_SetPtr_Caption(
    _Inout_ CIM_Setting* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_Clear_Caption(
    _Inout_ CIM_Setting* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_Set_Description(
    _Inout_ CIM_Setting* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_SetPtr_Description(
    _Inout_ CIM_Setting* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_Clear_Description(
    _Inout_ CIM_Setting* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_Set_ElementName(
    _Inout_ CIM_Setting* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_SetPtr_ElementName(
    _Inout_ CIM_Setting* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_Clear_ElementName(
    _Inout_ CIM_Setting* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_Set_SettingID(
    _Inout_ CIM_Setting* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_SetPtr_SettingID(
    _Inout_ CIM_Setting* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_Clear_SettingID(
    _Inout_ CIM_Setting* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** CIM_Setting.VerifyOKToApplyToMSE()
**
**==============================================================================
*/

typedef struct _CIM_Setting_VerifyOKToApplyToMSE
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ CIM_ManagedSystemElement_ConstRef MSE;
    /*IN*/ MI_ConstDatetimeField TimeToApply;
    /*IN*/ MI_ConstDatetimeField MustBeCompletedBy;
}
CIM_Setting_VerifyOKToApplyToMSE;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_Setting_VerifyOKToApplyToMSE_rtti;

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToMSE_Construct(
    _Out_ CIM_Setting_VerifyOKToApplyToMSE* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_Setting_VerifyOKToApplyToMSE_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToMSE_Clone(
    _In_ const CIM_Setting_VerifyOKToApplyToMSE* self,
    _Outptr_ CIM_Setting_VerifyOKToApplyToMSE** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToMSE_Destruct(
    _Inout_ CIM_Setting_VerifyOKToApplyToMSE* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToMSE_Delete(
    _Inout_ CIM_Setting_VerifyOKToApplyToMSE* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToMSE_Post(
    _In_ const CIM_Setting_VerifyOKToApplyToMSE* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToMSE_Set_MIReturn(
    _Inout_ CIM_Setting_VerifyOKToApplyToMSE* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToMSE_Clear_MIReturn(
    _Inout_ CIM_Setting_VerifyOKToApplyToMSE* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToMSE_Set_MSE(
    _Inout_ CIM_Setting_VerifyOKToApplyToMSE* self,
    _In_ const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToMSE_SetPtr_MSE(
    _Inout_ CIM_Setting_VerifyOKToApplyToMSE* self,
    _In_ const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToMSE_Clear_MSE(
    _Inout_ CIM_Setting_VerifyOKToApplyToMSE* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToMSE_Set_TimeToApply(
    _Inout_ CIM_Setting_VerifyOKToApplyToMSE* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeToApply)->value = x;
    ((MI_DatetimeField*)&self->TimeToApply)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToMSE_Clear_TimeToApply(
    _Inout_ CIM_Setting_VerifyOKToApplyToMSE* self)
{
    memset((void*)&self->TimeToApply, 0, sizeof(self->TimeToApply));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToMSE_Set_MustBeCompletedBy(
    _Inout_ CIM_Setting_VerifyOKToApplyToMSE* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MustBeCompletedBy)->value = x;
    ((MI_DatetimeField*)&self->MustBeCompletedBy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToMSE_Clear_MustBeCompletedBy(
    _Inout_ CIM_Setting_VerifyOKToApplyToMSE* self)
{
    memset((void*)&self->MustBeCompletedBy, 0, sizeof(self->MustBeCompletedBy));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_Setting.ApplyToMSE()
**
**==============================================================================
*/

typedef struct _CIM_Setting_ApplyToMSE
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ CIM_ManagedSystemElement_ConstRef MSE;
    /*IN*/ MI_ConstDatetimeField TimeToApply;
    /*IN*/ MI_ConstDatetimeField MustBeCompletedBy;
}
CIM_Setting_ApplyToMSE;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_Setting_ApplyToMSE_rtti;

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToMSE_Construct(
    _Out_ CIM_Setting_ApplyToMSE* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_Setting_ApplyToMSE_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToMSE_Clone(
    _In_ const CIM_Setting_ApplyToMSE* self,
    _Outptr_ CIM_Setting_ApplyToMSE** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToMSE_Destruct(
    _Inout_ CIM_Setting_ApplyToMSE* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToMSE_Delete(
    _Inout_ CIM_Setting_ApplyToMSE* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToMSE_Post(
    _In_ const CIM_Setting_ApplyToMSE* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToMSE_Set_MIReturn(
    _Inout_ CIM_Setting_ApplyToMSE* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToMSE_Clear_MIReturn(
    _Inout_ CIM_Setting_ApplyToMSE* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToMSE_Set_MSE(
    _Inout_ CIM_Setting_ApplyToMSE* self,
    _In_ const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToMSE_SetPtr_MSE(
    _Inout_ CIM_Setting_ApplyToMSE* self,
    _In_ const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToMSE_Clear_MSE(
    _Inout_ CIM_Setting_ApplyToMSE* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToMSE_Set_TimeToApply(
    _Inout_ CIM_Setting_ApplyToMSE* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeToApply)->value = x;
    ((MI_DatetimeField*)&self->TimeToApply)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToMSE_Clear_TimeToApply(
    _Inout_ CIM_Setting_ApplyToMSE* self)
{
    memset((void*)&self->TimeToApply, 0, sizeof(self->TimeToApply));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToMSE_Set_MustBeCompletedBy(
    _Inout_ CIM_Setting_ApplyToMSE* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MustBeCompletedBy)->value = x;
    ((MI_DatetimeField*)&self->MustBeCompletedBy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToMSE_Clear_MustBeCompletedBy(
    _Inout_ CIM_Setting_ApplyToMSE* self)
{
    memset((void*)&self->MustBeCompletedBy, 0, sizeof(self->MustBeCompletedBy));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_Setting.VerifyOKToApplyToCollection()
**
**==============================================================================
*/

typedef struct _CIM_Setting_VerifyOKToApplyToCollection
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ CIM_CollectionOfMSEs_ConstRef Collection;
    /*IN*/ MI_ConstDatetimeField TimeToApply;
    /*IN*/ MI_ConstDatetimeField MustBeCompletedBy;
    /*OUT*/ MI_ConstStringAField CanNotApply;
}
CIM_Setting_VerifyOKToApplyToCollection;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_Setting_VerifyOKToApplyToCollection_rtti;

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToCollection_Construct(
    _Out_ CIM_Setting_VerifyOKToApplyToCollection* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_Setting_VerifyOKToApplyToCollection_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToCollection_Clone(
    _In_ const CIM_Setting_VerifyOKToApplyToCollection* self,
    _Outptr_ CIM_Setting_VerifyOKToApplyToCollection** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToCollection_Destruct(
    _Inout_ CIM_Setting_VerifyOKToApplyToCollection* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToCollection_Delete(
    _Inout_ CIM_Setting_VerifyOKToApplyToCollection* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToCollection_Post(
    _In_ const CIM_Setting_VerifyOKToApplyToCollection* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToCollection_Set_MIReturn(
    _Inout_ CIM_Setting_VerifyOKToApplyToCollection* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToCollection_Clear_MIReturn(
    _Inout_ CIM_Setting_VerifyOKToApplyToCollection* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToCollection_Set_Collection(
    _Inout_ CIM_Setting_VerifyOKToApplyToCollection* self,
    _In_ const CIM_CollectionOfMSEs* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToCollection_SetPtr_Collection(
    _Inout_ CIM_Setting_VerifyOKToApplyToCollection* self,
    _In_ const CIM_CollectionOfMSEs* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToCollection_Clear_Collection(
    _Inout_ CIM_Setting_VerifyOKToApplyToCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToCollection_Set_TimeToApply(
    _Inout_ CIM_Setting_VerifyOKToApplyToCollection* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeToApply)->value = x;
    ((MI_DatetimeField*)&self->TimeToApply)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToCollection_Clear_TimeToApply(
    _Inout_ CIM_Setting_VerifyOKToApplyToCollection* self)
{
    memset((void*)&self->TimeToApply, 0, sizeof(self->TimeToApply));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToCollection_Set_MustBeCompletedBy(
    _Inout_ CIM_Setting_VerifyOKToApplyToCollection* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MustBeCompletedBy)->value = x;
    ((MI_DatetimeField*)&self->MustBeCompletedBy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToCollection_Clear_MustBeCompletedBy(
    _Inout_ CIM_Setting_VerifyOKToApplyToCollection* self)
{
    memset((void*)&self->MustBeCompletedBy, 0, sizeof(self->MustBeCompletedBy));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToCollection_Set_CanNotApply(
    _Inout_ CIM_Setting_VerifyOKToApplyToCollection* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToCollection_SetPtr_CanNotApply(
    _Inout_ CIM_Setting_VerifyOKToApplyToCollection* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyToCollection_Clear_CanNotApply(
    _Inout_ CIM_Setting_VerifyOKToApplyToCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** CIM_Setting.ApplyToCollection()
**
**==============================================================================
*/

typedef struct _CIM_Setting_ApplyToCollection
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ CIM_CollectionOfMSEs_ConstRef Collection;
    /*IN*/ MI_ConstDatetimeField TimeToApply;
    /*IN*/ MI_ConstBooleanField ContinueOnError;
    /*IN*/ MI_ConstDatetimeField MustBeCompletedBy;
    /*OUT*/ MI_ConstStringAField CanNotApply;
}
CIM_Setting_ApplyToCollection;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_Setting_ApplyToCollection_rtti;

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_Construct(
    _Out_ CIM_Setting_ApplyToCollection* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_Setting_ApplyToCollection_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_Clone(
    _In_ const CIM_Setting_ApplyToCollection* self,
    _Outptr_ CIM_Setting_ApplyToCollection** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_Destruct(
    _Inout_ CIM_Setting_ApplyToCollection* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_Delete(
    _Inout_ CIM_Setting_ApplyToCollection* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_Post(
    _In_ const CIM_Setting_ApplyToCollection* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_Set_MIReturn(
    _Inout_ CIM_Setting_ApplyToCollection* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_Clear_MIReturn(
    _Inout_ CIM_Setting_ApplyToCollection* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_Set_Collection(
    _Inout_ CIM_Setting_ApplyToCollection* self,
    _In_ const CIM_CollectionOfMSEs* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_SetPtr_Collection(
    _Inout_ CIM_Setting_ApplyToCollection* self,
    _In_ const CIM_CollectionOfMSEs* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_Clear_Collection(
    _Inout_ CIM_Setting_ApplyToCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_Set_TimeToApply(
    _Inout_ CIM_Setting_ApplyToCollection* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeToApply)->value = x;
    ((MI_DatetimeField*)&self->TimeToApply)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_Clear_TimeToApply(
    _Inout_ CIM_Setting_ApplyToCollection* self)
{
    memset((void*)&self->TimeToApply, 0, sizeof(self->TimeToApply));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_Set_ContinueOnError(
    _Inout_ CIM_Setting_ApplyToCollection* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->ContinueOnError)->value = x;
    ((MI_BooleanField*)&self->ContinueOnError)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_Clear_ContinueOnError(
    _Inout_ CIM_Setting_ApplyToCollection* self)
{
    memset((void*)&self->ContinueOnError, 0, sizeof(self->ContinueOnError));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_Set_MustBeCompletedBy(
    _Inout_ CIM_Setting_ApplyToCollection* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MustBeCompletedBy)->value = x;
    ((MI_DatetimeField*)&self->MustBeCompletedBy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_Clear_MustBeCompletedBy(
    _Inout_ CIM_Setting_ApplyToCollection* self)
{
    memset((void*)&self->MustBeCompletedBy, 0, sizeof(self->MustBeCompletedBy));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_Set_CanNotApply(
    _Inout_ CIM_Setting_ApplyToCollection* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_SetPtr_CanNotApply(
    _Inout_ CIM_Setting_ApplyToCollection* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyToCollection_Clear_CanNotApply(
    _Inout_ CIM_Setting_ApplyToCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

/*
**==============================================================================
**
** CIM_Setting.VerifyOKToApplyIncrementalChangeToMSE()
**
**==============================================================================
*/

typedef struct _CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ CIM_ManagedSystemElement_ConstRef MSE;
    /*IN*/ MI_ConstDatetimeField TimeToApply;
    /*IN*/ MI_ConstDatetimeField MustBeCompletedBy;
    /*IN*/ MI_ConstStringAField PropertiesToApply;
}
CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_rtti;

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_Construct(
    _Out_ CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_Clone(
    _In_ const CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE* self,
    _Outptr_ CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_Destruct(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_Delete(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_Post(
    _In_ const CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_Set_MIReturn(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_Clear_MIReturn(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_Set_MSE(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE* self,
    _In_ const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_SetPtr_MSE(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE* self,
    _In_ const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_Clear_MSE(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_Set_TimeToApply(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeToApply)->value = x;
    ((MI_DatetimeField*)&self->TimeToApply)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_Clear_TimeToApply(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE* self)
{
    memset((void*)&self->TimeToApply, 0, sizeof(self->TimeToApply));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_Set_MustBeCompletedBy(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MustBeCompletedBy)->value = x;
    ((MI_DatetimeField*)&self->MustBeCompletedBy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_Clear_MustBeCompletedBy(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE* self)
{
    memset((void*)&self->MustBeCompletedBy, 0, sizeof(self->MustBeCompletedBy));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_Set_PropertiesToApply(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_SetPtr_PropertiesToApply(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE_Clear_PropertiesToApply(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToMSE* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** CIM_Setting.ApplyIncrementalChangeToMSE()
**
**==============================================================================
*/

typedef struct _CIM_Setting_ApplyIncrementalChangeToMSE
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ CIM_ManagedSystemElement_ConstRef MSE;
    /*IN*/ MI_ConstDatetimeField TimeToApply;
    /*IN*/ MI_ConstDatetimeField MustBeCompletedBy;
    /*IN*/ MI_ConstStringAField PropertiesToApply;
}
CIM_Setting_ApplyIncrementalChangeToMSE;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_Setting_ApplyIncrementalChangeToMSE_rtti;

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToMSE_Construct(
    _Out_ CIM_Setting_ApplyIncrementalChangeToMSE* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_Setting_ApplyIncrementalChangeToMSE_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToMSE_Clone(
    _In_ const CIM_Setting_ApplyIncrementalChangeToMSE* self,
    _Outptr_ CIM_Setting_ApplyIncrementalChangeToMSE** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToMSE_Destruct(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToMSE* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToMSE_Delete(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToMSE* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToMSE_Post(
    _In_ const CIM_Setting_ApplyIncrementalChangeToMSE* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToMSE_Set_MIReturn(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToMSE* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToMSE_Clear_MIReturn(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToMSE* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToMSE_Set_MSE(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToMSE* self,
    _In_ const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToMSE_SetPtr_MSE(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToMSE* self,
    _In_ const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToMSE_Clear_MSE(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToMSE* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToMSE_Set_TimeToApply(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToMSE* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeToApply)->value = x;
    ((MI_DatetimeField*)&self->TimeToApply)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToMSE_Clear_TimeToApply(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToMSE* self)
{
    memset((void*)&self->TimeToApply, 0, sizeof(self->TimeToApply));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToMSE_Set_MustBeCompletedBy(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToMSE* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MustBeCompletedBy)->value = x;
    ((MI_DatetimeField*)&self->MustBeCompletedBy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToMSE_Clear_MustBeCompletedBy(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToMSE* self)
{
    memset((void*)&self->MustBeCompletedBy, 0, sizeof(self->MustBeCompletedBy));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToMSE_Set_PropertiesToApply(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToMSE* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToMSE_SetPtr_PropertiesToApply(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToMSE* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToMSE_Clear_PropertiesToApply(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToMSE* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** CIM_Setting.VerifyOKToApplyIncrementalChangeToCollection()
**
**==============================================================================
*/

typedef struct _CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ CIM_CollectionOfMSEs_ConstRef Collection;
    /*IN*/ MI_ConstDatetimeField TimeToApply;
    /*IN*/ MI_ConstDatetimeField MustBeCompletedBy;
    /*IN*/ MI_ConstStringAField PropertiesToApply;
    /*OUT*/ MI_ConstStringAField CanNotApply;
}
CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_rtti;

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_Construct(
    _Out_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_Clone(
    _In_ const CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self,
    _Outptr_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_Destruct(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_Delete(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_Post(
    _In_ const CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_Set_MIReturn(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_Clear_MIReturn(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_Set_Collection(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self,
    _In_ const CIM_CollectionOfMSEs* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_SetPtr_Collection(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self,
    _In_ const CIM_CollectionOfMSEs* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_Clear_Collection(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_Set_TimeToApply(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeToApply)->value = x;
    ((MI_DatetimeField*)&self->TimeToApply)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_Clear_TimeToApply(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self)
{
    memset((void*)&self->TimeToApply, 0, sizeof(self->TimeToApply));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_Set_MustBeCompletedBy(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MustBeCompletedBy)->value = x;
    ((MI_DatetimeField*)&self->MustBeCompletedBy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_Clear_MustBeCompletedBy(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self)
{
    memset((void*)&self->MustBeCompletedBy, 0, sizeof(self->MustBeCompletedBy));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_Set_PropertiesToApply(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_SetPtr_PropertiesToApply(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_Clear_PropertiesToApply(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_Set_CanNotApply(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_SetPtr_CanNotApply(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection_Clear_CanNotApply(
    _Inout_ CIM_Setting_VerifyOKToApplyIncrementalChangeToCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

/*
**==============================================================================
**
** CIM_Setting.ApplyIncrementalChangeToCollection()
**
**==============================================================================
*/

typedef struct _CIM_Setting_ApplyIncrementalChangeToCollection
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ CIM_CollectionOfMSEs_ConstRef Collection;
    /*IN*/ MI_ConstDatetimeField TimeToApply;
    /*IN*/ MI_ConstBooleanField ContinueOnError;
    /*IN*/ MI_ConstDatetimeField MustBeCompletedBy;
    /*IN*/ MI_ConstStringAField PropertiesToApply;
    /*OUT*/ MI_ConstStringAField CanNotApply;
}
CIM_Setting_ApplyIncrementalChangeToCollection;

MI_EXTERN_C MI_CONST MI_MethodDecl CIM_Setting_ApplyIncrementalChangeToCollection_rtti;

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Construct(
    _Out_ CIM_Setting_ApplyIncrementalChangeToCollection* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructParameters(context, &CIM_Setting_ApplyIncrementalChangeToCollection_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Clone(
    _In_ const CIM_Setting_ApplyIncrementalChangeToCollection* self,
    _Outptr_ CIM_Setting_ApplyIncrementalChangeToCollection** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Destruct(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Delete(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Post(
    _In_ const CIM_Setting_ApplyIncrementalChangeToCollection* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Set_MIReturn(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Clear_MIReturn(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Set_Collection(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self,
    _In_ const CIM_CollectionOfMSEs* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_SetPtr_Collection(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self,
    _In_ const CIM_CollectionOfMSEs* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Clear_Collection(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Set_TimeToApply(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeToApply)->value = x;
    ((MI_DatetimeField*)&self->TimeToApply)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Clear_TimeToApply(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self)
{
    memset((void*)&self->TimeToApply, 0, sizeof(self->TimeToApply));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Set_ContinueOnError(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->ContinueOnError)->value = x;
    ((MI_BooleanField*)&self->ContinueOnError)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Clear_ContinueOnError(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self)
{
    memset((void*)&self->ContinueOnError, 0, sizeof(self->ContinueOnError));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Set_MustBeCompletedBy(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self,
    _In_ MI_Datetime x)
{
    ((MI_DatetimeField*)&self->MustBeCompletedBy)->value = x;
    ((MI_DatetimeField*)&self->MustBeCompletedBy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Clear_MustBeCompletedBy(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self)
{
    memset((void*)&self->MustBeCompletedBy, 0, sizeof(self->MustBeCompletedBy));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Set_PropertiesToApply(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_SetPtr_PropertiesToApply(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Clear_PropertiesToApply(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Set_CanNotApply(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_SetPtr_CanNotApply(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Setting_ApplyIncrementalChangeToCollection_Clear_CanNotApply(
    _Inout_ CIM_Setting_ApplyIncrementalChangeToCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}


#endif /* _CIM_Setting_h */
