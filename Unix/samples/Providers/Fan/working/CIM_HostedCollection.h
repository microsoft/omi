/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_HostedCollection_h
#define _CIM_HostedCollection_h

#include <MI.h>
#include "CIM_HostedDependency.h"
#include "CIM_System.h"
#include "CIM_SystemSpecificCollection.h"

/*
**==============================================================================
**
** CIM_HostedCollection [CIM_HostedCollection]
**
** Keys:
**    Antecedent
**    Dependent
**
**==============================================================================
*/

typedef struct _CIM_HostedCollection /* extends CIM_HostedDependency */
{
    MI_Instance __instance;
    /* CIM_Dependency properties */
    /*KEY*/ CIM_System_ConstRef Antecedent;
    /*KEY*/ CIM_SystemSpecificCollection_ConstRef Dependent;
    /* CIM_HostedDependency properties */
    /* CIM_HostedCollection properties */
}
CIM_HostedCollection;

typedef struct _CIM_HostedCollection_Ref
{
    CIM_HostedCollection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_HostedCollection_Ref;

typedef struct _CIM_HostedCollection_ConstRef
{
    MI_CONST CIM_HostedCollection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_HostedCollection_ConstRef;

typedef struct _CIM_HostedCollection_Array
{
    struct _CIM_HostedCollection** data;
    MI_Uint32 size;
}
CIM_HostedCollection_Array;

typedef struct _CIM_HostedCollection_ConstArray
{
    struct _CIM_HostedCollection MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_HostedCollection_ConstArray;

typedef struct _CIM_HostedCollection_ArrayRef
{
    CIM_HostedCollection_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_HostedCollection_ArrayRef;

typedef struct _CIM_HostedCollection_ConstArrayRef
{
    CIM_HostedCollection_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_HostedCollection_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_HostedCollection_rtti;

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Construct(
    CIM_HostedCollection* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_HostedCollection_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Clone(
    const CIM_HostedCollection* self,
    CIM_HostedCollection** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_HostedCollection_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_HostedCollection_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Destruct(CIM_HostedCollection* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Delete(CIM_HostedCollection* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Post(
    const CIM_HostedCollection* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Set_Antecedent(
    CIM_HostedCollection* self,
    const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_SetPtr_Antecedent(
    CIM_HostedCollection* self,
    const CIM_System* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Clear_Antecedent(
    CIM_HostedCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Set_Dependent(
    CIM_HostedCollection* self,
    const CIM_SystemSpecificCollection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_SetPtr_Dependent(
    CIM_HostedCollection* self,
    const CIM_SystemSpecificCollection* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_HostedCollection_Clear_Dependent(
    CIM_HostedCollection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _CIM_HostedCollection_h */
