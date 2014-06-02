/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _X_TestObject_h
#define _X_TestObject_h

#include <MI.h>

/*
**==============================================================================
**
** X_TestObject [X_TestObject]
**
** Keys:
**    id
**
**==============================================================================
*/

typedef struct _X_TestObject
{
    MI_Instance __instance;
    /* X_TestObject properties */
    /*KEY*/ MI_ConstUint64Field id;
    MI_ConstStringField str;
    MI_ConstChar16Field operation;
    MI_ConstUint32Field left_operand;
    MI_ConstUint32Field right_operand;
    MI_ConstUint32Field result;
}
X_TestObject;

typedef struct _X_TestObject_Ref
{
    X_TestObject* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_TestObject_Ref;

typedef struct _X_TestObject_ConstRef
{
    MI_CONST X_TestObject* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_TestObject_ConstRef;

typedef struct _X_TestObject_Array
{
    struct _X_TestObject** data;
    MI_Uint32 size;
}
X_TestObject_Array;

typedef struct _X_TestObject_ConstArray
{
    struct _X_TestObject MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_TestObject_ConstArray;

typedef struct _X_TestObject_ArrayRef
{
    X_TestObject_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_TestObject_ArrayRef;

typedef struct _X_TestObject_ConstArrayRef
{
    X_TestObject_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_TestObject_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_TestObject_rtti;

MI_INLINE MI_Result MI_CALL X_TestObject_Construct(
    X_TestObject* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_TestObject_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_TestObject_Clone(
    const X_TestObject* self,
    X_TestObject** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_TestObject_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_TestObject_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Destruct(X_TestObject* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_TestObject_Delete(X_TestObject* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_TestObject_Post(
    const X_TestObject* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_TestObject_Set_id(
    X_TestObject* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->id)->value = x;
    ((MI_Uint64Field*)&self->id)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Clear_id(
    X_TestObject* self)
{
    memset((void*)&self->id, 0, sizeof(self->id));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Set_str(
    X_TestObject* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_TestObject_SetPtr_str(
    X_TestObject* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_TestObject_Clear_str(
    X_TestObject* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL X_TestObject_Set_operation(
    X_TestObject* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->operation)->value = x;
    ((MI_Char16Field*)&self->operation)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Clear_operation(
    X_TestObject* self)
{
    memset((void*)&self->operation, 0, sizeof(self->operation));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Set_left_operand(
    X_TestObject* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->left_operand)->value = x;
    ((MI_Uint32Field*)&self->left_operand)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Clear_left_operand(
    X_TestObject* self)
{
    memset((void*)&self->left_operand, 0, sizeof(self->left_operand));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Set_right_operand(
    X_TestObject* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->right_operand)->value = x;
    ((MI_Uint32Field*)&self->right_operand)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Clear_right_operand(
    X_TestObject* self)
{
    memset((void*)&self->right_operand, 0, sizeof(self->right_operand));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Set_result(
    X_TestObject* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->result)->value = x;
    ((MI_Uint32Field*)&self->result)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_TestObject_Clear_result(
    X_TestObject* self)
{
    memset((void*)&self->result, 0, sizeof(self->result));
    return MI_RESULT_OK;
}


#endif /* _X_TestObject_h */
