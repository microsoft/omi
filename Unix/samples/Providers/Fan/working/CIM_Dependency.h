/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_Dependency_h
#define _CIM_Dependency_h

#include <MI.h>
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** CIM_Dependency [CIM_Dependency]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _CIM_Dependency
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_ManagedElement_ConstRef Antecedent;
    /*KEY*/ CIM_ManagedElement_ConstRef Dependent;
}
CIM_Dependency;

typedef struct _CIM_Dependency_Ref
{
    CIM_Dependency* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Dependency_Ref;

typedef struct _CIM_Dependency_ConstRef
{
    MI_CONST CIM_Dependency* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Dependency_ConstRef;

typedef struct _CIM_Dependency_Array
{
    struct _CIM_Dependency** data;
    MI_Uint32 size;
}
CIM_Dependency_Array;

typedef struct _CIM_Dependency_ConstArray
{
    struct _CIM_Dependency MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_Dependency_ConstArray;

typedef struct _CIM_Dependency_ArrayRef
{
    CIM_Dependency_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Dependency_ArrayRef;

typedef struct _CIM_Dependency_ConstArrayRef
{
    CIM_Dependency_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Dependency_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_Dependency_rtti;

MI_INLINE MI_Result MI_CALL CIM_Dependency_Construct(
    CIM_Dependency* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_Dependency_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Dependency_Clone(
    const CIM_Dependency* self,
    CIM_Dependency** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_Dependency_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_Dependency_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_Dependency_Destruct(CIM_Dependency* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Dependency_Delete(CIM_Dependency* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Dependency_Post(
    const CIM_Dependency* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Dependency_Set_Antecedent(
    CIM_Dependency* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Dependency_SetPtr_Antecedent(
    CIM_Dependency* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Dependency_Clear_Antecedent(
    CIM_Dependency* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Dependency_Set_Dependent(
    CIM_Dependency* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Dependency_SetPtr_Dependent(
    CIM_Dependency* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Dependency_Clear_Dependent(
    CIM_Dependency* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _CIM_Dependency_h */
