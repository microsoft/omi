/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_Realizes_h
#define _CIM_Realizes_h

#include <MI.h>
#include "CIM_Dependency.h"
#include "CIM_PhysicalElement.h"
#include "CIM_LogicalDevice.h"

/*
**==============================================================================
**
** CIM_Realizes [CIM_Realizes]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _CIM_Realizes /* extends CIM_Dependency */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_PhysicalElement_ConstRef Antecedent;
    /*KEY*/ CIM_LogicalDevice_ConstRef Dependent;
    /* CIM_Realizes properties */
}
CIM_Realizes;

typedef struct _CIM_Realizes_Ref
{
    CIM_Realizes* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Realizes_Ref;

typedef struct _CIM_Realizes_ConstRef
{
    MI_CONST CIM_Realizes* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Realizes_ConstRef;

typedef struct _CIM_Realizes_Array
{
    struct _CIM_Realizes** data;
    MI_Uint32 size;
}
CIM_Realizes_Array;

typedef struct _CIM_Realizes_ConstArray
{
    struct _CIM_Realizes MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_Realizes_ConstArray;

typedef struct _CIM_Realizes_ArrayRef
{
    CIM_Realizes_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Realizes_ArrayRef;

typedef struct _CIM_Realizes_ConstArrayRef
{
    CIM_Realizes_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Realizes_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_Realizes_rtti;

MI_INLINE MI_Result MI_CALL CIM_Realizes_Construct(
    CIM_Realizes* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_Realizes_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Realizes_Clone(
    const CIM_Realizes* self,
    CIM_Realizes** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_Realizes_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_Realizes_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_Realizes_Destruct(CIM_Realizes* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Realizes_Delete(CIM_Realizes* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Realizes_Post(
    const CIM_Realizes* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Realizes_Set_Antecedent(
    CIM_Realizes* self,
    const CIM_PhysicalElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Realizes_SetPtr_Antecedent(
    CIM_Realizes* self,
    const CIM_PhysicalElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Realizes_Clear_Antecedent(
    CIM_Realizes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Realizes_Set_Dependent(
    CIM_Realizes* self,
    const CIM_LogicalDevice* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Realizes_SetPtr_Dependent(
    CIM_Realizes* self,
    const CIM_LogicalDevice* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Realizes_Clear_Dependent(
    CIM_Realizes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _CIM_Realizes_h */
