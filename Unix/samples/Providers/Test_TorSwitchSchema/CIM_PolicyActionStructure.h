/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_PolicyActionStructure_h
#define _CIM_PolicyActionStructure_h

#include <MI.h>
#include "CIM_PolicyComponent.h"
#include "CIM_Policy.h"
#include "CIM_PolicyAction.h"

/*
**==============================================================================
**
** CIM_PolicyActionStructure [CIM_PolicyActionStructure]
**
** Keys:
**    GroupComponent
**    PartComponent
**
**==============================================================================
*/

typedef struct _CIM_PolicyActionStructure /* extends CIM_PolicyComponent */
{
    MI_Instance __instance;
    /* CIM_Component properties */
    /*KEY*/ CIM_Policy_ConstRef GroupComponent;
    /*KEY*/ CIM_PolicyAction_ConstRef PartComponent;
    /* CIM_PolicyComponent properties */
    /* CIM_PolicyActionStructure properties */
    MI_ConstUint16Field ActionOrder;
}
CIM_PolicyActionStructure;

typedef struct _CIM_PolicyActionStructure_Ref
{
    CIM_PolicyActionStructure* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyActionStructure_Ref;

typedef struct _CIM_PolicyActionStructure_ConstRef
{
    MI_CONST CIM_PolicyActionStructure* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyActionStructure_ConstRef;

typedef struct _CIM_PolicyActionStructure_Array
{
    struct _CIM_PolicyActionStructure** data;
    MI_Uint32 size;
}
CIM_PolicyActionStructure_Array;

typedef struct _CIM_PolicyActionStructure_ConstArray
{
    struct _CIM_PolicyActionStructure MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_PolicyActionStructure_ConstArray;

typedef struct _CIM_PolicyActionStructure_ArrayRef
{
    CIM_PolicyActionStructure_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyActionStructure_ArrayRef;

typedef struct _CIM_PolicyActionStructure_ConstArrayRef
{
    CIM_PolicyActionStructure_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyActionStructure_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_PolicyActionStructure_rtti;

MI_INLINE MI_Result MI_CALL CIM_PolicyActionStructure_Construct(
    _Out_ CIM_PolicyActionStructure* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_PolicyActionStructure_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionStructure_Clone(
    _In_ const CIM_PolicyActionStructure* self,
    _Outptr_ CIM_PolicyActionStructure** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_PolicyActionStructure_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_PolicyActionStructure_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionStructure_Destruct(_Inout_ CIM_PolicyActionStructure* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionStructure_Delete(_Inout_ CIM_PolicyActionStructure* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionStructure_Post(
    _In_ const CIM_PolicyActionStructure* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionStructure_Set_GroupComponent(
    _Inout_ CIM_PolicyActionStructure* self,
    _In_ const CIM_Policy* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionStructure_SetPtr_GroupComponent(
    _Inout_ CIM_PolicyActionStructure* self,
    _In_ const CIM_Policy* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionStructure_Clear_GroupComponent(
    _Inout_ CIM_PolicyActionStructure* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionStructure_Set_PartComponent(
    _Inout_ CIM_PolicyActionStructure* self,
    _In_ const CIM_PolicyAction* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionStructure_SetPtr_PartComponent(
    _Inout_ CIM_PolicyActionStructure* self,
    _In_ const CIM_PolicyAction* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionStructure_Clear_PartComponent(
    _Inout_ CIM_PolicyActionStructure* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionStructure_Set_ActionOrder(
    _Inout_ CIM_PolicyActionStructure* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->ActionOrder)->value = x;
    ((MI_Uint16Field*)&self->ActionOrder)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyActionStructure_Clear_ActionOrder(
    _Inout_ CIM_PolicyActionStructure* self)
{
    memset((void*)&self->ActionOrder, 0, sizeof(self->ActionOrder));
    return MI_RESULT_OK;
}


#endif /* _CIM_PolicyActionStructure_h */
