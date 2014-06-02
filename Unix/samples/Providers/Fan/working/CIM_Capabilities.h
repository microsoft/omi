/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_Capabilities_h
#define _CIM_Capabilities_h

#include <MI.h>
#include "CIM_ManagedElement.h"

/*
**==============================================================================
**
** CIM_Capabilities [CIM_Capabilities]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_Capabilities /* extends CIM_ManagedElement */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Capabilities properties */
}
CIM_Capabilities;

typedef struct _CIM_Capabilities_Ref
{
    CIM_Capabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Capabilities_Ref;

typedef struct _CIM_Capabilities_ConstRef
{
    MI_CONST CIM_Capabilities* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Capabilities_ConstRef;

typedef struct _CIM_Capabilities_Array
{
    struct _CIM_Capabilities** data;
    MI_Uint32 size;
}
CIM_Capabilities_Array;

typedef struct _CIM_Capabilities_ConstArray
{
    struct _CIM_Capabilities MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_Capabilities_ConstArray;

typedef struct _CIM_Capabilities_ArrayRef
{
    CIM_Capabilities_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Capabilities_ArrayRef;

typedef struct _CIM_Capabilities_ConstArrayRef
{
    CIM_Capabilities_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_Capabilities_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_Capabilities_rtti;

MI_INLINE MI_Result MI_CALL CIM_Capabilities_Construct(
    CIM_Capabilities* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_Capabilities_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Capabilities_Clone(
    const CIM_Capabilities* self,
    CIM_Capabilities** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_Capabilities_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_Capabilities_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_Capabilities_Destruct(CIM_Capabilities* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Capabilities_Delete(CIM_Capabilities* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Capabilities_Post(
    const CIM_Capabilities* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_Capabilities_Set_InstanceID(
    CIM_Capabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Capabilities_SetPtr_InstanceID(
    CIM_Capabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Capabilities_Clear_InstanceID(
    CIM_Capabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Capabilities_Set_Caption(
    CIM_Capabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Capabilities_SetPtr_Caption(
    CIM_Capabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Capabilities_Clear_Caption(
    CIM_Capabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_Capabilities_Set_Description(
    CIM_Capabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Capabilities_SetPtr_Description(
    CIM_Capabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Capabilities_Clear_Description(
    CIM_Capabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_Capabilities_Set_ElementName(
    CIM_Capabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_Capabilities_SetPtr_ElementName(
    CIM_Capabilities* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_Capabilities_Clear_ElementName(
    CIM_Capabilities* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}


#endif /* _CIM_Capabilities_h */
