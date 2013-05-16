/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_OwningCollectionElement_h
#define _CIM_OwningCollectionElement_h

#include <MI.h>
#include "CIM_ManagedElement.h"
#include "CIM_Collection.h"

/*
**==============================================================================
**
** CIM_OwningCollectionElement [CIM_OwningCollectionElement]
**
** Keys:
**    OwningElement
**    OwnedElement
**
**==============================================================================
*/

typedef struct _CIM_OwningCollectionElement
{
    MI_Instance __instance;
    /* CIM_OwningCollectionElement properties */
    /*KEY*/ CIM_ManagedElement_ConstRef OwningElement;
    /*KEY*/ CIM_Collection_ConstRef OwnedElement;
}
CIM_OwningCollectionElement;

typedef struct _CIM_OwningCollectionElement_Ref
{
    CIM_OwningCollectionElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_OwningCollectionElement_Ref;

typedef struct _CIM_OwningCollectionElement_ConstRef
{
    MI_CONST CIM_OwningCollectionElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_OwningCollectionElement_ConstRef;

typedef struct _CIM_OwningCollectionElement_Array
{
    struct _CIM_OwningCollectionElement** data;
    MI_Uint32 size;
}
CIM_OwningCollectionElement_Array;

typedef struct _CIM_OwningCollectionElement_ConstArray
{
    struct _CIM_OwningCollectionElement MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_OwningCollectionElement_ConstArray;

typedef struct _CIM_OwningCollectionElement_ArrayRef
{
    CIM_OwningCollectionElement_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_OwningCollectionElement_ArrayRef;

typedef struct _CIM_OwningCollectionElement_ConstArrayRef
{
    CIM_OwningCollectionElement_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_OwningCollectionElement_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_OwningCollectionElement_rtti;

MI_INLINE MI_Result MI_CALL CIM_OwningCollectionElement_Construct(
    CIM_OwningCollectionElement* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_OwningCollectionElement_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_OwningCollectionElement_Clone(
    const CIM_OwningCollectionElement* self,
    CIM_OwningCollectionElement** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_OwningCollectionElement_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_OwningCollectionElement_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_OwningCollectionElement_Destruct(CIM_OwningCollectionElement* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_OwningCollectionElement_Delete(CIM_OwningCollectionElement* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_OwningCollectionElement_Post(
    const CIM_OwningCollectionElement* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_OwningCollectionElement_Set_OwningElement(
    CIM_OwningCollectionElement* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_OwningCollectionElement_SetPtr_OwningElement(
    CIM_OwningCollectionElement* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_OwningCollectionElement_Clear_OwningElement(
    CIM_OwningCollectionElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_OwningCollectionElement_Set_OwnedElement(
    CIM_OwningCollectionElement* self,
    const CIM_Collection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_OwningCollectionElement_SetPtr_OwnedElement(
    CIM_OwningCollectionElement* self,
    const CIM_Collection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_OwningCollectionElement_Clear_OwnedElement(
    CIM_OwningCollectionElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _CIM_OwningCollectionElement_h */
