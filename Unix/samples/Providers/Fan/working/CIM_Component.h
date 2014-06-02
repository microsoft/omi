/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_Component_h
#define _CIM_Component_h

#include <MI.h>
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** CIM_Component [CIM_Component]
**
** Keys:
**    GroupComponent
**    PartComponent
**
**==============================================================================
*/

typedef struct _CIM_Component
{
    MI_Instance __instance;
    /* CIM_Component properties */
    /*KEY*/ CIM_ManagedElement_ConstRef GroupComponent;
    /*KEY*/ CIM_ManagedElement_ConstRef PartComponent;
}
CIM_Component;

typedef struct _CIM_Component_Ref
{
    CIM_Component* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Component_Ref;

typedef struct _CIM_Component_ConstRef
{
    MI_CONST CIM_Component* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Component_ConstRef;

typedef struct _CIM_Component_Array
{
    struct _CIM_Component** data;
    MI_Uint32 size;
}
CIM_Component_Array;

typedef struct _CIM_Component_ConstArray
{
    struct _CIM_Component MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_Component_ConstArray;

typedef struct _CIM_Component_ArrayRef
{
    CIM_Component_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Component_ArrayRef;

typedef struct _CIM_Component_ConstArrayRef
{
    CIM_Component_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Component_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_Component_rtti;

MI_INLINE MI_Result MI_CALL CIM_Component_Construct(
    CIM_Component* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_Component_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Component_Clone(
    const CIM_Component* self,
    CIM_Component** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_Component_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_Component_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_Component_Destruct(CIM_Component* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Component_Delete(CIM_Component* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Component_Post(
    const CIM_Component* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Component_Set_GroupComponent(
    CIM_Component* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Component_SetPtr_GroupComponent(
    CIM_Component* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Component_Clear_GroupComponent(
    CIM_Component* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Component_Set_PartComponent(
    CIM_Component* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Component_SetPtr_PartComponent(
    CIM_Component* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Component_Clear_PartComponent(
    CIM_Component* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _CIM_Component_h */
