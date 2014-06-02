/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_SystemComponent_h
#define _CIM_SystemComponent_h

#include <MI.h>
#include "CIM_Component.h"
#include "CIM_System.h"
#include "CIM_ManagedSystemElement.h"

/*
**==============================================================================
**
** CIM_SystemComponent [CIM_SystemComponent]
**
** Keys:
**    GroupComponent
**    PartComponent
**
**==============================================================================
*/

typedef struct _CIM_SystemComponent /* extends CIM_Component */
{
    MI_Instance __instance;
    /* CIM_Component properties */
    /*KEY*/ CIM_System_ConstRef GroupComponent;
    /*KEY*/ CIM_ManagedSystemElement_ConstRef PartComponent;
    /* CIM_SystemComponent properties */
}
CIM_SystemComponent;

typedef struct _CIM_SystemComponent_Ref
{
    CIM_SystemComponent* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SystemComponent_Ref;

typedef struct _CIM_SystemComponent_ConstRef
{
    MI_CONST CIM_SystemComponent* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SystemComponent_ConstRef;

typedef struct _CIM_SystemComponent_Array
{
    struct _CIM_SystemComponent** data;
    MI_Uint32 size;
}
CIM_SystemComponent_Array;

typedef struct _CIM_SystemComponent_ConstArray
{
    struct _CIM_SystemComponent MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_SystemComponent_ConstArray;

typedef struct _CIM_SystemComponent_ArrayRef
{
    CIM_SystemComponent_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SystemComponent_ArrayRef;

typedef struct _CIM_SystemComponent_ConstArrayRef
{
    CIM_SystemComponent_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_SystemComponent_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_SystemComponent_rtti;

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Construct(
    CIM_SystemComponent* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_SystemComponent_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Clone(
    const CIM_SystemComponent* self,
    CIM_SystemComponent** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_SystemComponent_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_SystemComponent_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Destruct(CIM_SystemComponent* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Delete(CIM_SystemComponent* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Post(
    const CIM_SystemComponent* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Set_GroupComponent(
    CIM_SystemComponent* self,
    const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_SetPtr_GroupComponent(
    CIM_SystemComponent* self,
    const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Clear_GroupComponent(
    CIM_SystemComponent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Set_PartComponent(
    CIM_SystemComponent* self,
    const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_SetPtr_PartComponent(
    CIM_SystemComponent* self,
    const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_SystemComponent_Clear_PartComponent(
    CIM_SystemComponent* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _CIM_SystemComponent_h */
