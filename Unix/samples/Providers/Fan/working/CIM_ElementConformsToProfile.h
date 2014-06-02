/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_ElementConformsToProfile_h
#define _CIM_ElementConformsToProfile_h

#include <MI.h>
#include "CIM_RegisteredProfile.h"
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** CIM_ElementConformsToProfile [CIM_ElementConformsToProfile]
**
** Keys:
**    ConformantStandard
**    ManagedElement
**
**==============================================================================
*/

typedef struct _CIM_ElementConformsToProfile
{
    MI_Instance __instance;
    /* CIM_ElementConformsToProfile properties */
    /*KEY*/ CIM_RegisteredProfile_ConstRef ConformantStandard;
    /*KEY*/ CIM_ManagedElement_ConstRef ManagedElement;
}
CIM_ElementConformsToProfile;

typedef struct _CIM_ElementConformsToProfile_Ref
{
    CIM_ElementConformsToProfile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementConformsToProfile_Ref;

typedef struct _CIM_ElementConformsToProfile_ConstRef
{
    MI_CONST CIM_ElementConformsToProfile* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementConformsToProfile_ConstRef;

typedef struct _CIM_ElementConformsToProfile_Array
{
    struct _CIM_ElementConformsToProfile** data;
    MI_Uint32 size;
}
CIM_ElementConformsToProfile_Array;

typedef struct _CIM_ElementConformsToProfile_ConstArray
{
    struct _CIM_ElementConformsToProfile MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_ElementConformsToProfile_ConstArray;

typedef struct _CIM_ElementConformsToProfile_ArrayRef
{
    CIM_ElementConformsToProfile_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementConformsToProfile_ArrayRef;

typedef struct _CIM_ElementConformsToProfile_ConstArrayRef
{
    CIM_ElementConformsToProfile_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ElementConformsToProfile_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_ElementConformsToProfile_rtti;

MI_INLINE MI_Result MI_CALL CIM_ElementConformsToProfile_Construct(
    CIM_ElementConformsToProfile* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_ElementConformsToProfile_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementConformsToProfile_Clone(
    const CIM_ElementConformsToProfile* self,
    CIM_ElementConformsToProfile** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_ElementConformsToProfile_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_ElementConformsToProfile_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_ElementConformsToProfile_Destruct(CIM_ElementConformsToProfile* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementConformsToProfile_Delete(CIM_ElementConformsToProfile* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementConformsToProfile_Post(
    const CIM_ElementConformsToProfile* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ElementConformsToProfile_Set_ConformantStandard(
    CIM_ElementConformsToProfile* self,
    const CIM_RegisteredProfile* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ElementConformsToProfile_SetPtr_ConformantStandard(
    CIM_ElementConformsToProfile* self,
    const CIM_RegisteredProfile* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ElementConformsToProfile_Clear_ConformantStandard(
    CIM_ElementConformsToProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ElementConformsToProfile_Set_ManagedElement(
    CIM_ElementConformsToProfile* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ElementConformsToProfile_SetPtr_ManagedElement(
    CIM_ElementConformsToProfile* self,
    const CIM_ManagedElement* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ElementConformsToProfile_Clear_ManagedElement(
    CIM_ElementConformsToProfile* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}


#endif /* _CIM_ElementConformsToProfile_h */
