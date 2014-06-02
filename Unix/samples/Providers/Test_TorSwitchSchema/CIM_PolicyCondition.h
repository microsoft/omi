/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_PolicyCondition_h
#define _CIM_PolicyCondition_h

#include <MI.h>
#include "CIM_Policy.h"

/*
**==============================================================================
**
** CIM_PolicyCondition [CIM_PolicyCondition]
**
** Keys:
**    SystemCreationClassName
**    SystemName
**    PolicyRuleCreationClassName
**    PolicyRuleName
**    CreationClassName
**    PolicyConditionName
**
**==============================================================================
*/

typedef struct _CIM_PolicyCondition /* extends CIM_Policy */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Policy properties */
    MI_ConstStringField CommonName;
    MI_ConstStringAField PolicyKeywords;
    /* CIM_PolicyCondition properties */
    /*KEY*/ MI_ConstStringField SystemCreationClassName;
    /*KEY*/ MI_ConstStringField SystemName;
    /*KEY*/ MI_ConstStringField PolicyRuleCreationClassName;
    /*KEY*/ MI_ConstStringField PolicyRuleName;
    /*KEY*/ MI_ConstStringField CreationClassName;
    /*KEY*/ MI_ConstStringField PolicyConditionName;
}
CIM_PolicyCondition;

typedef struct _CIM_PolicyCondition_Ref
{
    CIM_PolicyCondition* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyCondition_Ref;

typedef struct _CIM_PolicyCondition_ConstRef
{
    MI_CONST CIM_PolicyCondition* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyCondition_ConstRef;

typedef struct _CIM_PolicyCondition_Array
{
    struct _CIM_PolicyCondition** data;
    MI_Uint32 size;
}
CIM_PolicyCondition_Array;

typedef struct _CIM_PolicyCondition_ConstArray
{
    struct _CIM_PolicyCondition MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_PolicyCondition_ConstArray;

typedef struct _CIM_PolicyCondition_ArrayRef
{
    CIM_PolicyCondition_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyCondition_ArrayRef;

typedef struct _CIM_PolicyCondition_ConstArrayRef
{
    CIM_PolicyCondition_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyCondition_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_PolicyCondition_rtti;

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Construct(
    _Out_ CIM_PolicyCondition* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_PolicyCondition_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Clone(
    _In_ const CIM_PolicyCondition* self,
    _Outptr_ CIM_PolicyCondition** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_PolicyCondition_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_PolicyCondition_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Destruct(_Inout_ CIM_PolicyCondition* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Delete(_Inout_ CIM_PolicyCondition* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Post(
    _In_ const CIM_PolicyCondition* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Set_InstanceID(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_SetPtr_InstanceID(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Clear_InstanceID(
    _Inout_ CIM_PolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Set_Caption(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_SetPtr_Caption(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Clear_Caption(
    _Inout_ CIM_PolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Set_Description(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_SetPtr_Description(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Clear_Description(
    _Inout_ CIM_PolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Set_ElementName(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_SetPtr_ElementName(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Clear_ElementName(
    _Inout_ CIM_PolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Set_CommonName(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_SetPtr_CommonName(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Clear_CommonName(
    _Inout_ CIM_PolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Set_PolicyKeywords(
    _Inout_ CIM_PolicyCondition* self,
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

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_SetPtr_PolicyKeywords(
    _Inout_ CIM_PolicyCondition* self,
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

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Clear_PolicyKeywords(
    _Inout_ CIM_PolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Set_SystemCreationClassName(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_SetPtr_SystemCreationClassName(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Clear_SystemCreationClassName(
    _Inout_ CIM_PolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Set_SystemName(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_SetPtr_SystemName(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Clear_SystemName(
    _Inout_ CIM_PolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Set_PolicyRuleCreationClassName(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_SetPtr_PolicyRuleCreationClassName(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Clear_PolicyRuleCreationClassName(
    _Inout_ CIM_PolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Set_PolicyRuleName(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_SetPtr_PolicyRuleName(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Clear_PolicyRuleName(
    _Inout_ CIM_PolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Set_CreationClassName(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_SetPtr_CreationClassName(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Clear_CreationClassName(
    _Inout_ CIM_PolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Set_PolicyConditionName(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_SetPtr_PolicyConditionName(
    _Inout_ CIM_PolicyCondition* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyCondition_Clear_PolicyConditionName(
    _Inout_ CIM_PolicyCondition* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}


#endif /* _CIM_PolicyCondition_h */
