/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_PolicyConditionInPolicyRule_h
#define _CIM_PolicyConditionInPolicyRule_h

#include <MI.h>
#include "CIM_PolicyConditionStructure.h"
#include "CIM_PolicyRule.h"
#include "CIM_PolicyCondition.h"

/*
**==============================================================================
**
** CIM_PolicyConditionInPolicyRule [CIM_PolicyConditionInPolicyRule]
**
** Keys:
**    GroupComponent
**    PartComponent
**
**==============================================================================
*/

typedef struct _CIM_PolicyConditionInPolicyRule /* extends CIM_PolicyConditionStructure */
{
    MI_Instance __instance;
    /* CIM_Component properties */
    /*KEY*/ CIM_PolicyRule_ConstRef GroupComponent;
    /*KEY*/ CIM_PolicyCondition_ConstRef PartComponent;
    /* CIM_PolicyComponent properties */
    /* CIM_PolicyConditionStructure properties */
    MI_ConstUint16Field GroupNumber;
    MI_ConstBooleanField ConditionNegated;
    /* CIM_PolicyConditionInPolicyRule properties */
}
CIM_PolicyConditionInPolicyRule;

typedef struct _CIM_PolicyConditionInPolicyRule_Ref
{
    CIM_PolicyConditionInPolicyRule* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyConditionInPolicyRule_Ref;

typedef struct _CIM_PolicyConditionInPolicyRule_ConstRef
{
    MI_CONST CIM_PolicyConditionInPolicyRule* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyConditionInPolicyRule_ConstRef;

typedef struct _CIM_PolicyConditionInPolicyRule_Array
{
    struct _CIM_PolicyConditionInPolicyRule** data;
    MI_Uint32 size;
}
CIM_PolicyConditionInPolicyRule_Array;

typedef struct _CIM_PolicyConditionInPolicyRule_ConstArray
{
    struct _CIM_PolicyConditionInPolicyRule MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_PolicyConditionInPolicyRule_ConstArray;

typedef struct _CIM_PolicyConditionInPolicyRule_ArrayRef
{
    CIM_PolicyConditionInPolicyRule_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyConditionInPolicyRule_ArrayRef;

typedef struct _CIM_PolicyConditionInPolicyRule_ConstArrayRef
{
    CIM_PolicyConditionInPolicyRule_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyConditionInPolicyRule_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_PolicyConditionInPolicyRule_rtti;

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionInPolicyRule_Construct(
    _Out_ CIM_PolicyConditionInPolicyRule* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_PolicyConditionInPolicyRule_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionInPolicyRule_Clone(
    _In_ const CIM_PolicyConditionInPolicyRule* self,
    _Outptr_ CIM_PolicyConditionInPolicyRule** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_PolicyConditionInPolicyRule_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_PolicyConditionInPolicyRule_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionInPolicyRule_Destruct(_Inout_ CIM_PolicyConditionInPolicyRule* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionInPolicyRule_Delete(_Inout_ CIM_PolicyConditionInPolicyRule* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionInPolicyRule_Post(
    _In_ const CIM_PolicyConditionInPolicyRule* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionInPolicyRule_Set_GroupComponent(
    _Inout_ CIM_PolicyConditionInPolicyRule* self,
    _In_ const CIM_PolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionInPolicyRule_SetPtr_GroupComponent(
    _Inout_ CIM_PolicyConditionInPolicyRule* self,
    _In_ const CIM_PolicyRule* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionInPolicyRule_Clear_GroupComponent(
    _Inout_ CIM_PolicyConditionInPolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionInPolicyRule_Set_PartComponent(
    _Inout_ CIM_PolicyConditionInPolicyRule* self,
    _In_ const CIM_PolicyCondition* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionInPolicyRule_SetPtr_PartComponent(
    _Inout_ CIM_PolicyConditionInPolicyRule* self,
    _In_ const CIM_PolicyCondition* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionInPolicyRule_Clear_PartComponent(
    _Inout_ CIM_PolicyConditionInPolicyRule* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionInPolicyRule_Set_GroupNumber(
    _Inout_ CIM_PolicyConditionInPolicyRule* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->GroupNumber)->value = x;
    ((MI_Uint16Field*)&self->GroupNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionInPolicyRule_Clear_GroupNumber(
    _Inout_ CIM_PolicyConditionInPolicyRule* self)
{
    memset((void*)&self->GroupNumber, 0, sizeof(self->GroupNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionInPolicyRule_Set_ConditionNegated(
    _Inout_ CIM_PolicyConditionInPolicyRule* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->ConditionNegated)->value = x;
    ((MI_BooleanField*)&self->ConditionNegated)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionInPolicyRule_Clear_ConditionNegated(
    _Inout_ CIM_PolicyConditionInPolicyRule* self)
{
    memset((void*)&self->ConditionNegated, 0, sizeof(self->ConditionNegated));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_PolicyConditionInPolicyRule provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _CIM_PolicyConditionInPolicyRule_Self CIM_PolicyConditionInPolicyRule_Self;

MI_EXTERN_C void MI_CALL CIM_PolicyConditionInPolicyRule_Load(
    _Outptr_result_maybenull_ CIM_PolicyConditionInPolicyRule_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_PolicyConditionInPolicyRule_Unload(
    _In_opt_ CIM_PolicyConditionInPolicyRule_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL CIM_PolicyConditionInPolicyRule_EnumerateInstances(
    _In_opt_ CIM_PolicyConditionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_PolicyConditionInPolicyRule_GetInstance(
    _In_opt_ CIM_PolicyConditionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicyConditionInPolicyRule* instanceName,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_PolicyConditionInPolicyRule_CreateInstance(
    _In_opt_ CIM_PolicyConditionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicyConditionInPolicyRule* newInstance);

MI_EXTERN_C void MI_CALL CIM_PolicyConditionInPolicyRule_ModifyInstance(
    _In_opt_ CIM_PolicyConditionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicyConditionInPolicyRule* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL CIM_PolicyConditionInPolicyRule_DeleteInstance(
    _In_opt_ CIM_PolicyConditionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicyConditionInPolicyRule* instanceName);

MI_EXTERN_C void MI_CALL CIM_PolicyConditionInPolicyRule_AssociatorInstancesGroupComponent(
    _In_opt_ CIM_PolicyConditionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicyRule* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_PolicyConditionInPolicyRule_AssociatorInstancesPartComponent(
    _In_opt_ CIM_PolicyConditionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicyCondition* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_PolicyConditionInPolicyRule_ReferenceInstancesGroupComponent(
    _In_opt_ CIM_PolicyConditionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicyRule* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);

MI_EXTERN_C void MI_CALL CIM_PolicyConditionInPolicyRule_ReferenceInstancesPartComponent(
    _In_opt_ CIM_PolicyConditionInPolicyRule_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const CIM_PolicyCondition* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter);


#endif /* _CIM_PolicyConditionInPolicyRule_h */
