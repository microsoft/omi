/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_PolicyConditionStructure_h
#define _CIM_PolicyConditionStructure_h

#include <MI.h>
#include "CIM_PolicyComponent.h"
#include "CIM_Policy.h"
#include "CIM_PolicyCondition.h"

/*
**==============================================================================
**
** CIM_PolicyConditionStructure [CIM_PolicyConditionStructure]
**
** Keys:
**    GroupComponent
**    PartComponent
**
**==============================================================================
*/

typedef struct _CIM_PolicyConditionStructure /* extends CIM_PolicyComponent */
{
    MI_Instance __instance;
    /* CIM_Component properties */
    /*KEY*/ CIM_Policy_ConstRef GroupComponent;
    /*KEY*/ CIM_PolicyCondition_ConstRef PartComponent;
    /* CIM_PolicyComponent properties */
    /* CIM_PolicyConditionStructure properties */
    MI_ConstUint16Field GroupNumber;
    MI_ConstBooleanField ConditionNegated;
}
CIM_PolicyConditionStructure;

typedef struct _CIM_PolicyConditionStructure_Ref
{
    CIM_PolicyConditionStructure* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyConditionStructure_Ref;

typedef struct _CIM_PolicyConditionStructure_ConstRef
{
    MI_CONST CIM_PolicyConditionStructure* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyConditionStructure_ConstRef;

typedef struct _CIM_PolicyConditionStructure_Array
{
    struct _CIM_PolicyConditionStructure** data;
    MI_Uint32 size;
}
CIM_PolicyConditionStructure_Array;

typedef struct _CIM_PolicyConditionStructure_ConstArray
{
    struct _CIM_PolicyConditionStructure MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_PolicyConditionStructure_ConstArray;

typedef struct _CIM_PolicyConditionStructure_ArrayRef
{
    CIM_PolicyConditionStructure_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyConditionStructure_ArrayRef;

typedef struct _CIM_PolicyConditionStructure_ConstArrayRef
{
    CIM_PolicyConditionStructure_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyConditionStructure_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_PolicyConditionStructure_rtti;

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionStructure_Construct(
    _Out_ CIM_PolicyConditionStructure* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_PolicyConditionStructure_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionStructure_Clone(
    _In_ const CIM_PolicyConditionStructure* self,
    _Outptr_ CIM_PolicyConditionStructure** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_PolicyConditionStructure_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_PolicyConditionStructure_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionStructure_Destruct(_Inout_ CIM_PolicyConditionStructure* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionStructure_Delete(_Inout_ CIM_PolicyConditionStructure* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionStructure_Post(
    _In_ const CIM_PolicyConditionStructure* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionStructure_Set_GroupComponent(
    _Inout_ CIM_PolicyConditionStructure* self,
    _In_ const CIM_Policy* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionStructure_SetPtr_GroupComponent(
    _Inout_ CIM_PolicyConditionStructure* self,
    _In_ const CIM_Policy* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionStructure_Clear_GroupComponent(
    _Inout_ CIM_PolicyConditionStructure* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionStructure_Set_PartComponent(
    _Inout_ CIM_PolicyConditionStructure* self,
    _In_ const CIM_PolicyCondition* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionStructure_SetPtr_PartComponent(
    _Inout_ CIM_PolicyConditionStructure* self,
    _In_ const CIM_PolicyCondition* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionStructure_Clear_PartComponent(
    _Inout_ CIM_PolicyConditionStructure* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionStructure_Set_GroupNumber(
    _Inout_ CIM_PolicyConditionStructure* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->GroupNumber)->value = x;
    ((MI_Uint16Field*)&self->GroupNumber)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionStructure_Clear_GroupNumber(
    _Inout_ CIM_PolicyConditionStructure* self)
{
    memset((void*)&self->GroupNumber, 0, sizeof(self->GroupNumber));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionStructure_Set_ConditionNegated(
    _Inout_ CIM_PolicyConditionStructure* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->ConditionNegated)->value = x;
    ((MI_BooleanField*)&self->ConditionNegated)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyConditionStructure_Clear_ConditionNegated(
    _Inout_ CIM_PolicyConditionStructure* self)
{
    memset((void*)&self->ConditionNegated, 0, sizeof(self->ConditionNegated));
    return MI_RESULT_OK;
}


#endif /* _CIM_PolicyConditionStructure_h */
