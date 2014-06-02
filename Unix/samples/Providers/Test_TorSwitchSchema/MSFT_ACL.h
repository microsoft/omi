/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_ACL_h
#define _MSFT_ACL_h

#include <MI.h>
#include "CIM_NetworkPolicyRule.h"

/*
**==============================================================================
**
** MSFT_ACL [MSFT_ACL]
**
** Keys:
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**    PolicyRuleName
**
**==============================================================================
*/

typedef struct _MSFT_ACL /* extends CIM_NetworkPolicyRule */
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
    /* MSFT_ACL properties */
    MI_ConstUint16Field ACLType;
    MI_ConstUint16Field ActionPolicy;
}
MSFT_ACL;

typedef struct _MSFT_ACL_Ref
{
    MSFT_ACL* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ACL_Ref;

typedef struct _MSFT_ACL_ConstRef
{
    MI_CONST MSFT_ACL* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ACL_ConstRef;

typedef struct _MSFT_ACL_Array
{
    struct _MSFT_ACL** data;
    MI_Uint32 size;
}
MSFT_ACL_Array;

typedef struct _MSFT_ACL_ConstArray
{
    struct _MSFT_ACL MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_ACL_ConstArray;

typedef struct _MSFT_ACL_ArrayRef
{
    MSFT_ACL_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ACL_ArrayRef;

typedef struct _MSFT_ACL_ConstArrayRef
{
    MSFT_ACL_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_ACL_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_ACL_rtti;

MI_INLINE MI_Result MI_CALL MSFT_ACL_Construct(
    _Out_ MSFT_ACL* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &MSFT_ACL_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clone(
    _In_ const MSFT_ACL* self,
    _Outptr_ MSFT_ACL** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_ACL_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_ACL_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Destruct(_Inout_ MSFT_ACL* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Delete(_Inout_ MSFT_ACL* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Post(
    _In_ const MSFT_ACL* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_InstanceID(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_SetPtr_InstanceID(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_InstanceID(
    _Inout_ MSFT_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_Caption(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_SetPtr_Caption(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_Caption(
    _Inout_ MSFT_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_Description(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_SetPtr_Description(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_Description(
    _Inout_ MSFT_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_ElementName(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_SetPtr_ElementName(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_ElementName(
    _Inout_ MSFT_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_CommonName(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_SetPtr_CommonName(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_CommonName(
    _Inout_ MSFT_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_PolicyKeywords(
    _Inout_ MSFT_ACL* self,
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

MI_INLINE MI_Result MI_CALL MSFT_ACL_SetPtr_PolicyKeywords(
    _Inout_ MSFT_ACL* self,
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

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_PolicyKeywords(
    _Inout_ MSFT_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_PolicyDecisionStrategy(
    _Inout_ MSFT_ACL* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PolicyDecisionStrategy)->value = x;
    ((MI_Uint16Field*)&self->PolicyDecisionStrategy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_PolicyDecisionStrategy(
    _Inout_ MSFT_ACL* self)
{
    memset((void*)&self->PolicyDecisionStrategy, 0, sizeof(self->PolicyDecisionStrategy));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_PolicyRoles(
    _Inout_ MSFT_ACL* self,
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

MI_INLINE MI_Result MI_CALL MSFT_ACL_SetPtr_PolicyRoles(
    _Inout_ MSFT_ACL* self,
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

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_PolicyRoles(
    _Inout_ MSFT_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_Enabled(
    _Inout_ MSFT_ACL* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Enabled)->value = x;
    ((MI_Uint16Field*)&self->Enabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_Enabled(
    _Inout_ MSFT_ACL* self)
{
    memset((void*)&self->Enabled, 0, sizeof(self->Enabled));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_SystemCreationClassName(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_SetPtr_SystemCreationClassName(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_SystemCreationClassName(
    _Inout_ MSFT_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_SystemName(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_SetPtr_SystemName(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_SystemName(
    _Inout_ MSFT_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_CreationClassName(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_SetPtr_CreationClassName(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_CreationClassName(
    _Inout_ MSFT_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_PolicyRuleName(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_SetPtr_PolicyRuleName(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_PolicyRuleName(
    _Inout_ MSFT_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_ConditionListType(
    _Inout_ MSFT_ACL* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ConditionListType)->value = x;
    ((MI_Uint16Field*)&self->ConditionListType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_ConditionListType(
    _Inout_ MSFT_ACL* self)
{
    memset((void*)&self->ConditionListType, 0, sizeof(self->ConditionListType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_RuleUsage(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_SetPtr_RuleUsage(
    _Inout_ MSFT_ACL* self,
    _In_z_ const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_RuleUsage(
    _Inout_ MSFT_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_Priority(
    _Inout_ MSFT_ACL* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Priority)->value = x;
    ((MI_Uint16Field*)&self->Priority)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_Priority(
    _Inout_ MSFT_ACL* self)
{
    memset((void*)&self->Priority, 0, sizeof(self->Priority));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_Mandatory(
    _Inout_ MSFT_ACL* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->Mandatory)->value = x;
    ((MI_BooleanField*)&self->Mandatory)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_Mandatory(
    _Inout_ MSFT_ACL* self)
{
    memset((void*)&self->Mandatory, 0, sizeof(self->Mandatory));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_SequencedActions(
    _Inout_ MSFT_ACL* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->SequencedActions)->value = x;
    ((MI_Uint16Field*)&self->SequencedActions)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_SequencedActions(
    _Inout_ MSFT_ACL* self)
{
    memset((void*)&self->SequencedActions, 0, sizeof(self->SequencedActions));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_ExecutionStrategy(
    _Inout_ MSFT_ACL* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ExecutionStrategy)->value = x;
    ((MI_Uint16Field*)&self->ExecutionStrategy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_ExecutionStrategy(
    _Inout_ MSFT_ACL* self)
{
    memset((void*)&self->ExecutionStrategy, 0, sizeof(self->ExecutionStrategy));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_ACLType(
    _Inout_ MSFT_ACL* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ACLType)->value = x;
    ((MI_Uint16Field*)&self->ACLType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_ACLType(
    _Inout_ MSFT_ACL* self)
{
    memset((void*)&self->ACLType, 0, sizeof(self->ACLType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Set_ActionPolicy(
    _Inout_ MSFT_ACL* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ActionPolicy)->value = x;
    ((MI_Uint16Field*)&self->ActionPolicy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_ACL_Clear_ActionPolicy(
    _Inout_ MSFT_ACL* self)
{
    memset((void*)&self->ActionPolicy, 0, sizeof(self->ActionPolicy));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_ACL provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_ACL_Self MSFT_ACL_Self;

MI_EXTERN_C void MI_CALL MSFT_ACL_Load(
    _Outptr_result_maybenull_ MSFT_ACL_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_ACL_Unload(
    _In_opt_ MSFT_ACL_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_ACL_EnumerateInstances(
    _In_opt_ MSFT_ACL_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_ACL_GetInstance(
    _In_opt_ MSFT_ACL_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ACL* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_ACL_CreateInstance(
    _In_opt_ MSFT_ACL_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ACL* newInstance);

MI_EXTERN_C void MI_CALL MSFT_ACL_ModifyInstance(
    _In_opt_ MSFT_ACL_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ACL* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_ACL_DeleteInstance(
    _In_opt_ MSFT_ACL_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const MSFT_ACL* instanceName);


#endif /* _MSFT_ACL_h */
