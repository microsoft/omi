/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_Collection_h
#define _CIM_Collection_h

#include <MI.h>
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** CIM_Collection [CIM_Collection]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_Collection /* extends CIM_ManagedElement */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Collection properties */
}
CIM_Collection;

typedef struct _CIM_Collection_Ref
{
    CIM_Collection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Collection_Ref;

typedef struct _CIM_Collection_ConstRef
{
    MI_CONST CIM_Collection* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Collection_ConstRef;

typedef struct _CIM_Collection_Array
{
    struct _CIM_Collection** data;
    MI_Uint32 size;
}
CIM_Collection_Array;

typedef struct _CIM_Collection_ConstArray
{
    struct _CIM_Collection MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_Collection_ConstArray;

typedef struct _CIM_Collection_ArrayRef
{
    CIM_Collection_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Collection_ArrayRef;

typedef struct _CIM_Collection_ConstArrayRef
{
    CIM_Collection_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Collection_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_Collection_rtti;

MI_INLINE MI_Result MI_CALL CIM_Collection_Construct(
    CIM_Collection* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_Collection_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Collection_Clone(
    const CIM_Collection* self,
    CIM_Collection** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_Collection_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_Collection_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_Collection_Destruct(CIM_Collection* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Collection_Delete(CIM_Collection* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Collection_Post(
    const CIM_Collection* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Collection_Set_InstanceID(
    CIM_Collection* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Collection_SetPtr_InstanceID(
    CIM_Collection* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Collection_Clear_InstanceID(
    CIM_Collection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Collection_Set_Caption(
    CIM_Collection* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Collection_SetPtr_Caption(
    CIM_Collection* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Collection_Clear_Caption(
    CIM_Collection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_Collection_Set_Description(
    CIM_Collection* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Collection_SetPtr_Description(
    CIM_Collection* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Collection_Clear_Description(
    CIM_Collection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_Collection_Set_ElementName(
    CIM_Collection* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Collection_SetPtr_ElementName(
    CIM_Collection* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Collection_Clear_ElementName(
    CIM_Collection* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}


#endif /* _CIM_Collection_h */
