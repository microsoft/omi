/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_IsSpare_h
#define _CIM_IsSpare_h

#include <MI.h>
#include "CIM_Dependency.h"
#include "CIM_ManagedElement.h"
#include "CIM_RedundancySet.h"

/*
**==============================================================================
**
** CIM_IsSpare [CIM_IsSpare]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _CIM_IsSpare /* extends CIM_Dependency */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_ManagedElement_ConstRef Antecedent;
    /*KEY*/ CIM_RedundancySet_ConstRef Dependent;
    /* CIM_IsSpare properties */
    MI_ConstUint16Field SpareStatus;
    MI_ConstUint16Field FailoverSupported;
}
CIM_IsSpare;

typedef struct _CIM_IsSpare_Ref
{
    CIM_IsSpare* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_IsSpare_Ref;

typedef struct _CIM_IsSpare_ConstRef
{
    MI_CONST CIM_IsSpare* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_IsSpare_ConstRef;

typedef struct _CIM_IsSpare_Array
{
    struct _CIM_IsSpare** data;
    MI_Uint32 size;
}
CIM_IsSpare_Array;

typedef struct _CIM_IsSpare_ConstArray
{
    struct _CIM_IsSpare MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_IsSpare_ConstArray;

typedef struct _CIM_IsSpare_ArrayRef
{
    CIM_IsSpare_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_IsSpare_ArrayRef;

typedef struct _CIM_IsSpare_ConstArrayRef
{
    CIM_IsSpare_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_IsSpare_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_IsSpare_rtti;

MI_INLINE MI_Result MI_CALL CIM_IsSpare_Construct(
    CIM_IsSpare* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_IsSpare_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_IsSpare_Clone(
    const CIM_IsSpare* self,
    CIM_IsSpare** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_IsSpare_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_IsSpare_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_IsSpare_Destruct(CIM_IsSpare* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_IsSpare_Delete(CIM_IsSpare* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_IsSpare_Post(
    const CIM_IsSpare* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_IsSpare_Set_Antecedent(
    CIM_IsSpare* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IsSpare_SetPtr_Antecedent(
    CIM_IsSpare* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IsSpare_Clear_Antecedent(
    CIM_IsSpare* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IsSpare_Set_Dependent(
    CIM_IsSpare* self,
    const CIM_RedundancySet* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_IsSpare_SetPtr_Dependent(
    CIM_IsSpare* self,
    const CIM_RedundancySet* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_IsSpare_Clear_Dependent(
    CIM_IsSpare* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_IsSpare_Set_SpareStatus(
    CIM_IsSpare* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->SpareStatus)->value = x;
    ((MI_Uint16Field*)&self->SpareStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IsSpare_Clear_SpareStatus(
    CIM_IsSpare* self)
{
    memset((void*)&self->SpareStatus, 0, sizeof(self->SpareStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IsSpare_Set_FailoverSupported(
    CIM_IsSpare* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->FailoverSupported)->value = x;
    ((MI_Uint16Field*)&self->FailoverSupported)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_IsSpare_Clear_FailoverSupported(
    CIM_IsSpare* self)
{
    memset((void*)&self->FailoverSupported, 0, sizeof(self->FailoverSupported));
    return MI_RESULT_OK;
}


#endif /* _CIM_IsSpare_h */
