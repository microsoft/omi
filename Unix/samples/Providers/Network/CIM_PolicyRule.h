/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_PolicyRule_h
#define _CIM_PolicyRule_h

#include <MI.h>
#include "CIM_PolicySet.h"

/*
**==============================================================================
**
** CIM_PolicyRule [CIM_PolicyRule]
**
** Keys:
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**    PolicyRuleName
**
**==============================================================================
*/

typedef struct _CIM_PolicyRule /* extends CIM_PolicySet */
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
    /* CIM_PolicySet properties */
    MI_ConstUint16Field PolicyDecisionStrategy;
    MI_ConstStringAField PolicyRoles;
    MI_ConstUint16Field Enabled;
    /* CIM_PolicyRule properties */
    /*KEY*/ MI_ConstStringField SystemCreationClassName;
    /*KEY*/ MI_ConstStringField SystemName;
    /*KEY*/ MI_ConstStringField CreationClassName;
    /*KEY*/ MI_ConstStringField PolicyRuleName;
    MI_ConstUint16Field ConditionListType;
    MI_ConstStringField RuleUsage;
    MI_ConstUint16Field Priority;
    MI_ConstBooleanField Mandatory;
    MI_ConstUint16Field SequencedActions;
    MI_ConstUint16Field ExecutionStrategy;
}
CIM_PolicyRule;

typedef struct _CIM_PolicyRule_Ref
{
    CIM_PolicyRule* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyRule_Ref;

typedef struct _CIM_PolicyRule_ConstRef
{
    MI_CONST CIM_PolicyRule* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyRule_ConstRef;

typedef struct _CIM_PolicyRule_Array
{
    struct _CIM_PolicyRule** data;
    MI_Uint32 size;
}
CIM_PolicyRule_Array;

typedef struct _CIM_PolicyRule_ConstArray
{
    struct _CIM_PolicyRule MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_PolicyRule_ConstArray;

typedef struct _CIM_PolicyRule_ArrayRef
{
    CIM_PolicyRule_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyRule_ArrayRef;

typedef struct _CIM_PolicyRule_ConstArrayRef
{
    CIM_PolicyRule_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyRule_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_PolicyRule_rtti;

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Construct(
    CIM_PolicyRule* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_PolicyRule_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clone(
    const CIM_PolicyRule* self,
    CIM_PolicyRule** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_PolicyRule_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_PolicyRule_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Destruct(CIM_PolicyRule* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Delete(CIM_PolicyRule* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Post(
    const CIM_PolicyRule* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_InstanceID(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_SetPtr_InstanceID(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_InstanceID(
    CIM_PolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_Caption(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_SetPtr_Caption(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_Caption(
    CIM_PolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_Description(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_SetPtr_Description(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_Description(
    CIM_PolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_ElementName(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_SetPtr_ElementName(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_ElementName(
    CIM_PolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_CommonName(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_SetPtr_CommonName(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_CommonName(
    CIM_PolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_PolicyKeywords(
    CIM_PolicyRule* self,
    const MI_Char** data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_SetPtr_PolicyKeywords(
    CIM_PolicyRule* self,
    const MI_Char** data,
    MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_PolicyKeywords(
    CIM_PolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_PolicyDecisionStrategy(
    CIM_PolicyRule* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PolicyDecisionStrategy)->value = x;
    ((MI_Uint16Field*)&self->PolicyDecisionStrategy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_PolicyDecisionStrategy(
    CIM_PolicyRule* self)
{
    memset((void*)&self->PolicyDecisionStrategy, 0, sizeof(self->PolicyDecisionStrategy));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_PolicyRoles(
    CIM_PolicyRule* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_SetPtr_PolicyRoles(
    CIM_PolicyRule* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_PolicyRoles(
    CIM_PolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_Enabled(
    CIM_PolicyRule* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Enabled)->value = x;
    ((MI_Uint16Field*)&self->Enabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_Enabled(
    CIM_PolicyRule* self)
{
    memset((void*)&self->Enabled, 0, sizeof(self->Enabled));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_SystemCreationClassName(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_SetPtr_SystemCreationClassName(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_SystemCreationClassName(
    CIM_PolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_SystemName(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_SetPtr_SystemName(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_SystemName(
    CIM_PolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_CreationClassName(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_SetPtr_CreationClassName(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_CreationClassName(
    CIM_PolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_PolicyRuleName(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_SetPtr_PolicyRuleName(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_PolicyRuleName(
    CIM_PolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_ConditionListType(
    CIM_PolicyRule* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ConditionListType)->value = x;
    ((MI_Uint16Field*)&self->ConditionListType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_ConditionListType(
    CIM_PolicyRule* self)
{
    memset((void*)&self->ConditionListType, 0, sizeof(self->ConditionListType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_RuleUsage(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_SetPtr_RuleUsage(
    CIM_PolicyRule* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_RuleUsage(
    CIM_PolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_Priority(
    CIM_PolicyRule* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Priority)->value = x;
    ((MI_Uint16Field*)&self->Priority)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_Priority(
    CIM_PolicyRule* self)
{
    memset((void*)&self->Priority, 0, sizeof(self->Priority));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_Mandatory(
    CIM_PolicyRule* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Mandatory)->value = x;
    ((MI_BooleanField*)&self->Mandatory)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_Mandatory(
    CIM_PolicyRule* self)
{
    memset((void*)&self->Mandatory, 0, sizeof(self->Mandatory));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_SequencedActions(
    CIM_PolicyRule* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->SequencedActions)->value = x;
    ((MI_Uint16Field*)&self->SequencedActions)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_SequencedActions(
    CIM_PolicyRule* self)
{
    memset((void*)&self->SequencedActions, 0, sizeof(self->SequencedActions));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Set_ExecutionStrategy(
    CIM_PolicyRule* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ExecutionStrategy)->value = x;
    ((MI_Uint16Field*)&self->ExecutionStrategy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyRule_Clear_ExecutionStrategy(
    CIM_PolicyRule* self)
{
    memset((void*)&self->ExecutionStrategy, 0, sizeof(self->ExecutionStrategy));
    return MI_RESULT_OK;
}


#endif /* _CIM_PolicyRule_h */
