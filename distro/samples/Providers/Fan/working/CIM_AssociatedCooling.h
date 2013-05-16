/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_AssociatedCooling_h
#define _CIM_AssociatedCooling_h

#include <MI.h>
#include "CIM_Dependency.h"
#include "CIM_CoolingDevice.h"
#include "CIM_ManagedSystemElement.h"

/*
**==============================================================================
**
** CIM_AssociatedCooling [CIM_AssociatedCooling]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _CIM_AssociatedCooling /* extends CIM_Dependency */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_CoolingDevice_ConstRef Antecedent;
    /*KEY*/ CIM_ManagedSystemElement_ConstRef Dependent;
    /* CIM_AssociatedCooling properties */
}
CIM_AssociatedCooling;

typedef struct _CIM_AssociatedCooling_Ref
{
    CIM_AssociatedCooling* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AssociatedCooling_Ref;

typedef struct _CIM_AssociatedCooling_ConstRef
{
    MI_CONST CIM_AssociatedCooling* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AssociatedCooling_ConstRef;

typedef struct _CIM_AssociatedCooling_Array
{
    struct _CIM_AssociatedCooling** data;
    MI_Uint32 size;
}
CIM_AssociatedCooling_Array;

typedef struct _CIM_AssociatedCooling_ConstArray
{
    struct _CIM_AssociatedCooling MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_AssociatedCooling_ConstArray;

typedef struct _CIM_AssociatedCooling_ArrayRef
{
    CIM_AssociatedCooling_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AssociatedCooling_ArrayRef;

typedef struct _CIM_AssociatedCooling_ConstArrayRef
{
    CIM_AssociatedCooling_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_AssociatedCooling_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_AssociatedCooling_rtti;

MI_INLINE MI_Result MI_CALL CIM_AssociatedCooling_Construct(
    CIM_AssociatedCooling* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_AssociatedCooling_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedCooling_Clone(
    const CIM_AssociatedCooling* self,
    CIM_AssociatedCooling** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_AssociatedCooling_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_AssociatedCooling_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedCooling_Destruct(CIM_AssociatedCooling* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedCooling_Delete(CIM_AssociatedCooling* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedCooling_Post(
    const CIM_AssociatedCooling* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedCooling_Set_Antecedent(
    CIM_AssociatedCooling* self,
    const CIM_CoolingDevice* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedCooling_SetPtr_Antecedent(
    CIM_AssociatedCooling* self,
    const CIM_CoolingDevice* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedCooling_Clear_Antecedent(
    CIM_AssociatedCooling* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedCooling_Set_Dependent(
    CIM_AssociatedCooling* self,
    const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedCooling_SetPtr_Dependent(
    CIM_AssociatedCooling* self,
    const CIM_ManagedSystemElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_AssociatedCooling_Clear_Dependent(
    CIM_AssociatedCooling* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _CIM_AssociatedCooling_h */
