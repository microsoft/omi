/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_NetworkPolicyRule_h
#define _CIM_NetworkPolicyRule_h

#include <MI.h>
#include "CIM_PolicyRule.h"

/*
**==============================================================================
**
** CIM_NetworkPolicyRule [CIM_NetworkPolicyRule]
**
** Keys:
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**    PolicyRuleName
**
**==============================================================================
*/

typedef struct _CIM_NetworkPolicyRule /* extends CIM_PolicyRule */
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
    /* CIM_NetworkPolicyRule properties */
}
CIM_NetworkPolicyRule;

typedef struct _CIM_NetworkPolicyRule_Ref
{
    CIM_NetworkPolicyRule* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyRule_Ref;

typedef struct _CIM_NetworkPolicyRule_ConstRef
{
    MI_CONST CIM_NetworkPolicyRule* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyRule_ConstRef;

typedef struct _CIM_NetworkPolicyRule_Array
{
    struct _CIM_NetworkPolicyRule** data;
    MI_Uint32 size;
}
CIM_NetworkPolicyRule_Array;

typedef struct _CIM_NetworkPolicyRule_ConstArray
{
    struct _CIM_NetworkPolicyRule MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_NetworkPolicyRule_ConstArray;

typedef struct _CIM_NetworkPolicyRule_ArrayRef
{
    CIM_NetworkPolicyRule_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyRule_ArrayRef;

typedef struct _CIM_NetworkPolicyRule_ConstArrayRef
{
    CIM_NetworkPolicyRule_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_NetworkPolicyRule_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_NetworkPolicyRule_rtti;

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Construct(
    _Out_ CIM_NetworkPolicyRule* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_NetworkPolicyRule_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clone(
    _In_ const CIM_NetworkPolicyRule* self,
    _Outptr_ CIM_NetworkPolicyRule** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_NetworkPolicyRule_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_NetworkPolicyRule_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Destruct(_Inout_ CIM_NetworkPolicyRule* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Delete(_Inout_ CIM_NetworkPolicyRule* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Post(
    _In_ const CIM_NetworkPolicyRule* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_InstanceID(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_SetPtr_InstanceID(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_InstanceID(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_Caption(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_SetPtr_Caption(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_Caption(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_Description(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_SetPtr_Description(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_Description(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_ElementName(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_SetPtr_ElementName(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_ElementName(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_CommonName(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_SetPtr_CommonName(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_CommonName(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_PolicyKeywords(
    _Inout_ CIM_NetworkPolicyRule* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_SetPtr_PolicyKeywords(
    _Inout_ CIM_NetworkPolicyRule* self,
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_PolicyKeywords(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_PolicyDecisionStrategy(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PolicyDecisionStrategy)->value = x;
    ((MI_Uint16Field*)&self->PolicyDecisionStrategy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_PolicyDecisionStrategy(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    memset((void*)&self->PolicyDecisionStrategy, 0, sizeof(self->PolicyDecisionStrategy));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_PolicyRoles(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_SetPtr_PolicyRoles(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_reads_opt_(size) const MI_Char** data,
    _In_ MI_Uint32 size)
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

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_PolicyRoles(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_Enabled(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Enabled)->value = x;
    ((MI_Uint16Field*)&self->Enabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_Enabled(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    memset((void*)&self->Enabled, 0, sizeof(self->Enabled));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_SystemCreationClassName(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_SetPtr_SystemCreationClassName(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_SystemCreationClassName(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_SystemName(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_SetPtr_SystemName(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_SystemName(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_CreationClassName(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_SetPtr_CreationClassName(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_CreationClassName(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_PolicyRuleName(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_SetPtr_PolicyRuleName(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_PolicyRuleName(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_ConditionListType(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ConditionListType)->value = x;
    ((MI_Uint16Field*)&self->ConditionListType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_ConditionListType(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    memset((void*)&self->ConditionListType, 0, sizeof(self->ConditionListType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_RuleUsage(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_SetPtr_RuleUsage(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_RuleUsage(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_Priority(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Priority)->value = x;
    ((MI_Uint16Field*)&self->Priority)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_Priority(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    memset((void*)&self->Priority, 0, sizeof(self->Priority));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_Mandatory(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Mandatory)->value = x;
    ((MI_BooleanField*)&self->Mandatory)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_Mandatory(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    memset((void*)&self->Mandatory, 0, sizeof(self->Mandatory));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_SequencedActions(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->SequencedActions)->value = x;
    ((MI_Uint16Field*)&self->SequencedActions)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_SequencedActions(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    memset((void*)&self->SequencedActions, 0, sizeof(self->SequencedActions));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Set_ExecutionStrategy(
    _Inout_ CIM_NetworkPolicyRule* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ExecutionStrategy)->value = x;
    ((MI_Uint16Field*)&self->ExecutionStrategy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_NetworkPolicyRule_Clear_ExecutionStrategy(
    _Inout_ CIM_NetworkPolicyRule* self)
{
    memset((void*)&self->ExecutionStrategy, 0, sizeof(self->ExecutionStrategy));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_NetworkPolicyRule provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_NetworkPolicyRule_Self CIM_NetworkPolicyRule_Self;

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyRule_Load(
    _Outptr_result_maybenull_ CIM_NetworkPolicyRule_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyRule_Unload(
    _In_opt_ CIM_NetworkPolicyRule_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyRule_EnumerateInstances(
    _In_opt_ CIM_NetworkPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyRule_GetInstance(
    _In_opt_ CIM_NetworkPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyRule* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyRule_CreateInstance(
    _In_opt_ CIM_NetworkPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyRule* newInstance);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyRule_ModifyInstance(
    _In_opt_ CIM_NetworkPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyRule* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_NetworkPolicyRule_DeleteInstance(
    _In_opt_ CIM_NetworkPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_NetworkPolicyRule* instanceName);


#endif /* _CIM_NetworkPolicyRule_h */
