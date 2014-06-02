/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _OMI_ACL_h
#define _OMI_ACL_h

#include <MI.h>
#include "MSFT_ACL.h"

/*
**==============================================================================
**
** OMI_ACL [OMI_ACL]
**
** Keys:
**    SystemCreationClassName
**    SystemName
**    CreationClassName
**    PolicyRuleName
**
**==============================================================================
*/

typedef struct _OMI_ACL /* extends MSFT_ACL */
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
    /* OMI_ACL properties */
}
OMI_ACL;

typedef struct _OMI_ACL_Ref
{
    OMI_ACL* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ACL_Ref;

typedef struct _OMI_ACL_ConstRef
{
    MI_CONST OMI_ACL* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ACL_ConstRef;

typedef struct _OMI_ACL_Array
{
    struct _OMI_ACL** data;
    MI_Uint32 size;
}
OMI_ACL_Array;

typedef struct _OMI_ACL_ConstArray
{
    struct _OMI_ACL MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
OMI_ACL_ConstArray;

typedef struct _OMI_ACL_ArrayRef
{
    OMI_ACL_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ACL_ArrayRef;

typedef struct _OMI_ACL_ConstArrayRef
{
    OMI_ACL_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
OMI_ACL_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl OMI_ACL_rtti;

MI_INLINE MI_Result MI_CALL OMI_ACL_Construct(
    OMI_ACL* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &OMI_ACL_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clone(
    const OMI_ACL* self,
    OMI_ACL** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL OMI_ACL_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &OMI_ACL_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Destruct(OMI_ACL* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Delete(OMI_ACL* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Post(
    const OMI_ACL* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_InstanceID(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_SetPtr_InstanceID(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_InstanceID(
    OMI_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_Caption(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_SetPtr_Caption(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_Caption(
    OMI_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_Description(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_SetPtr_Description(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_Description(
    OMI_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_ElementName(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_SetPtr_ElementName(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_ElementName(
    OMI_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_CommonName(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_SetPtr_CommonName(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_CommonName(
    OMI_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_PolicyKeywords(
    OMI_ACL* self,
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

MI_INLINE MI_Result MI_CALL OMI_ACL_SetPtr_PolicyKeywords(
    OMI_ACL* self,
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

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_PolicyKeywords(
    OMI_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_PolicyDecisionStrategy(
    OMI_ACL* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PolicyDecisionStrategy)->value = x;
    ((MI_Uint16Field*)&self->PolicyDecisionStrategy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_PolicyDecisionStrategy(
    OMI_ACL* self)
{
    memset((void*)&self->PolicyDecisionStrategy, 0, sizeof(self->PolicyDecisionStrategy));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_PolicyRoles(
    OMI_ACL* self,
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

MI_INLINE MI_Result MI_CALL OMI_ACL_SetPtr_PolicyRoles(
    OMI_ACL* self,
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

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_PolicyRoles(
    OMI_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_Enabled(
    OMI_ACL* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Enabled)->value = x;
    ((MI_Uint16Field*)&self->Enabled)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_Enabled(
    OMI_ACL* self)
{
    memset((void*)&self->Enabled, 0, sizeof(self->Enabled));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_SystemCreationClassName(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_SetPtr_SystemCreationClassName(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_SystemCreationClassName(
    OMI_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_SystemName(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_SetPtr_SystemName(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_SystemName(
    OMI_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_CreationClassName(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_SetPtr_CreationClassName(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_CreationClassName(
    OMI_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_PolicyRuleName(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_SetPtr_PolicyRuleName(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_PolicyRuleName(
    OMI_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_ConditionListType(
    OMI_ACL* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ConditionListType)->value = x;
    ((MI_Uint16Field*)&self->ConditionListType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_ConditionListType(
    OMI_ACL* self)
{
    memset((void*)&self->ConditionListType, 0, sizeof(self->ConditionListType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_RuleUsage(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_SetPtr_RuleUsage(
    OMI_ACL* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_RuleUsage(
    OMI_ACL* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_Priority(
    OMI_ACL* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Priority)->value = x;
    ((MI_Uint16Field*)&self->Priority)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_Priority(
    OMI_ACL* self)
{
    memset((void*)&self->Priority, 0, sizeof(self->Priority));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_Mandatory(
    OMI_ACL* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->Mandatory)->value = x;
    ((MI_BooleanField*)&self->Mandatory)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_Mandatory(
    OMI_ACL* self)
{
    memset((void*)&self->Mandatory, 0, sizeof(self->Mandatory));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_SequencedActions(
    OMI_ACL* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->SequencedActions)->value = x;
    ((MI_Uint16Field*)&self->SequencedActions)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_SequencedActions(
    OMI_ACL* self)
{
    memset((void*)&self->SequencedActions, 0, sizeof(self->SequencedActions));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_ExecutionStrategy(
    OMI_ACL* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ExecutionStrategy)->value = x;
    ((MI_Uint16Field*)&self->ExecutionStrategy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_ExecutionStrategy(
    OMI_ACL* self)
{
    memset((void*)&self->ExecutionStrategy, 0, sizeof(self->ExecutionStrategy));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_ACLType(
    OMI_ACL* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ACLType)->value = x;
    ((MI_Uint16Field*)&self->ACLType)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_ACLType(
    OMI_ACL* self)
{
    memset((void*)&self->ACLType, 0, sizeof(self->ACLType));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Set_ActionPolicy(
    OMI_ACL* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ActionPolicy)->value = x;
    ((MI_Uint16Field*)&self->ActionPolicy)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL OMI_ACL_Clear_ActionPolicy(
    OMI_ACL* self)
{
    memset((void*)&self->ActionPolicy, 0, sizeof(self->ActionPolicy));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** OMI_ACL provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _OMI_ACL_Self OMI_ACL_Self;

MI_EXTERN_C void MI_CALL OMI_ACL_Load(
    OMI_ACL_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL OMI_ACL_Unload(
    OMI_ACL_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL OMI_ACL_EnumerateInstances(
    OMI_ACL_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL OMI_ACL_GetInstance(
    OMI_ACL_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_ACL* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL OMI_ACL_CreateInstance(
    OMI_ACL_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_ACL* newInstance);

MI_EXTERN_C void MI_CALL OMI_ACL_ModifyInstance(
    OMI_ACL_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_ACL* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL OMI_ACL_DeleteInstance(
    OMI_ACL_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const OMI_ACL* instanceName);


#endif /* _OMI_ACL_h */
