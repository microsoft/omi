/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_PolicyComponent_h
#define _CIM_PolicyComponent_h

#include <MI.h>
#include "CIM_Component.h"
#include "CIM_Policy.h"

/*
**==============================================================================
**
** CIM_PolicyComponent [CIM_PolicyComponent]
**
** Keys:
**    GroupComponent
**    PartComponent
**
**==============================================================================
*/

typedef struct _CIM_PolicyComponent /* extends CIM_Component */
{
    MI_Instance __instance;
    /* CIM_Component properties */
    /*KEY*/ CIM_Policy_ConstRef GroupComponent;
    /*KEY*/ CIM_Policy_ConstRef PartComponent;
    /* CIM_PolicyComponent properties */
}
CIM_PolicyComponent;

typedef struct _CIM_PolicyComponent_Ref
{
    CIM_PolicyComponent* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyComponent_Ref;

typedef struct _CIM_PolicyComponent_ConstRef
{
    MI_CONST CIM_PolicyComponent* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyComponent_ConstRef;

typedef struct _CIM_PolicyComponent_Array
{
    struct _CIM_PolicyComponent** data;
    MI_Uint32 size;
}
CIM_PolicyComponent_Array;

typedef struct _CIM_PolicyComponent_ConstArray
{
    struct _CIM_PolicyComponent MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_PolicyComponent_ConstArray;

typedef struct _CIM_PolicyComponent_ArrayRef
{
    CIM_PolicyComponent_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyComponent_ArrayRef;

typedef struct _CIM_PolicyComponent_ConstArrayRef
{
    CIM_PolicyComponent_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_PolicyComponent_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_PolicyComponent_rtti;

MI_INLINE MI_Result MI_CALL CIM_PolicyComponent_Construct(
    _Out_ CIM_PolicyComponent* self,
    _In_ MI_Context* context)
{
    return MI_Context_ConstructInstance(context, &CIM_PolicyComponent_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyComponent_Clone(
    _In_ const CIM_PolicyComponent* self,
    _Outptr_ CIM_PolicyComponent** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_PolicyComponent_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_PolicyComponent_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_PolicyComponent_Destruct(_Inout_ CIM_PolicyComponent* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyComponent_Delete(_Inout_ CIM_PolicyComponent* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyComponent_Post(
    _In_ const CIM_PolicyComponent* self,
    _In_ MI_Context* context)
{
    return MI_Context_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyComponent_Set_GroupComponent(
    _Inout_ CIM_PolicyComponent* self,
    _In_ const CIM_Policy* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyComponent_SetPtr_GroupComponent(
    _Inout_ CIM_PolicyComponent* self,
    _In_ const CIM_Policy* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyComponent_Clear_GroupComponent(
    _Inout_ CIM_PolicyComponent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyComponent_Set_PartComponent(
    _Inout_ CIM_PolicyComponent* self,
    _In_ const CIM_Policy* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyComponent_SetPtr_PartComponent(
    _Inout_ CIM_PolicyComponent* self,
    _In_ const CIM_Policy* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_PolicyComponent_Clear_PartComponent(
    _Inout_ CIM_PolicyComponent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _CIM_PolicyComponent_h */
