/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_ManagedElement_h
#define _CIM_ManagedElement_h

#include <MI.h>

/*
**==============================================================================
**
** CIM_ManagedElement [CIM_ManagedElement]
**
** Keys:
**
**==============================================================================
*/

typedef struct _CIM_ManagedElement
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
}
CIM_ManagedElement;

typedef struct _CIM_ManagedElement_Ref
{
    CIM_ManagedElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ManagedElement_Ref;

typedef struct _CIM_ManagedElement_ConstRef
{
    MI_CONST CIM_ManagedElement* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ManagedElement_ConstRef;

typedef struct _CIM_ManagedElement_Array
{
    struct _CIM_ManagedElement** data;
    MI_Uint32 size;
}
CIM_ManagedElement_Array;

typedef struct _CIM_ManagedElement_ConstArray
{
    struct _CIM_ManagedElement MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_ManagedElement_ConstArray;

typedef struct _CIM_ManagedElement_ArrayRef
{
    CIM_ManagedElement_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ManagedElement_ArrayRef;

typedef struct _CIM_ManagedElement_ConstArrayRef
{
    CIM_ManagedElement_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_ManagedElement_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_ManagedElement_rtti;

MI_INLINE MI_Result MI_CALL CIM_ManagedElement_Construct(
    CIM_ManagedElement* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_ManagedElement_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ManagedElement_Clone(
    const CIM_ManagedElement* self,
    CIM_ManagedElement** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_ManagedElement_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_ManagedElement_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_ManagedElement_Destruct(CIM_ManagedElement* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ManagedElement_Delete(CIM_ManagedElement* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ManagedElement_Post(
    const CIM_ManagedElement* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_ManagedElement_Set_InstanceID(
    CIM_ManagedElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ManagedElement_SetPtr_InstanceID(
    CIM_ManagedElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ManagedElement_Clear_InstanceID(
    CIM_ManagedElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ManagedElement_Set_Caption(
    CIM_ManagedElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ManagedElement_SetPtr_Caption(
    CIM_ManagedElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ManagedElement_Clear_Caption(
    CIM_ManagedElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_ManagedElement_Set_Description(
    CIM_ManagedElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ManagedElement_SetPtr_Description(
    CIM_ManagedElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ManagedElement_Clear_Description(
    CIM_ManagedElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_ManagedElement_Set_ElementName(
    CIM_ManagedElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_ManagedElement_SetPtr_ElementName(
    CIM_ManagedElement* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_ManagedElement_Clear_ElementName(
    CIM_ManagedElement* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}


#endif /* _CIM_ManagedElement_h */
