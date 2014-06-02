/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _X_SingletonWithAllTypes_h
#define _X_SingletonWithAllTypes_h

#include <MI.h>
#include "MSFT_Person.h"
#include "X_TestObject.h"

/*
**==============================================================================
**
** X_SingletonWithAllTypes [X_SingletonWithAllTypes]
**
** Keys:
**    id
**
**==============================================================================
*/

typedef struct _X_SingletonWithAllTypes
{
    MI_Instance __instance;
    /* X_SingletonWithAllTypes properties */
    /*KEY*/ MI_ConstUint64Field id;
    MI_ConstBooleanField b;
    MI_ConstUint8Field u8;
    MI_ConstSint8Field s8;
    MI_ConstUint16Field u16;
    MI_ConstSint16Field s16;
    MI_ConstUint32Field u32;
    MI_ConstSint32Field s32;
    MI_ConstUint64Field u64;
    MI_ConstSint64Field s64;
    MI_ConstReal32Field r32;
    MI_ConstReal64Field r64;
    MI_ConstDatetimeField dt;
    MI_ConstStringField s;
    MI_ConstChar16Field c16;
    MI_ConstBooleanAField bA;
    MI_ConstUint8AField u8A;
    MI_ConstSint8AField s8A;
    MI_ConstUint16AField u16A;
    MI_ConstSint16AField s16A;
    MI_ConstUint32AField u32A;
    MI_ConstSint32AField s32A;
    MI_ConstUint64AField u64A;
    MI_ConstSint64AField s64A;
    MI_ConstReal32AField r32A;
    MI_ConstReal64AField r64A;
    MI_ConstDatetimeAField dtA;
    MI_ConstStringAField sA;
    MI_ConstChar16AField c16A;
    MSFT_Person_ConstRef person;
    X_TestObject_ConstArrayRef fourObjects;
    MI_ConstReferenceField objectSingle;
    MI_ConstReferenceAField objectsArray;
}
X_SingletonWithAllTypes;

typedef struct _X_SingletonWithAllTypes_Ref
{
    X_SingletonWithAllTypes* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_SingletonWithAllTypes_Ref;

typedef struct _X_SingletonWithAllTypes_ConstRef
{
    MI_CONST X_SingletonWithAllTypes* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_SingletonWithAllTypes_ConstRef;

typedef struct _X_SingletonWithAllTypes_Array
{
    struct _X_SingletonWithAllTypes** data;
    MI_Uint32 size;
}
X_SingletonWithAllTypes_Array;

typedef struct _X_SingletonWithAllTypes_ConstArray
{
    struct _X_SingletonWithAllTypes MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
X_SingletonWithAllTypes_ConstArray;

typedef struct _X_SingletonWithAllTypes_ArrayRef
{
    X_SingletonWithAllTypes_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_SingletonWithAllTypes_ArrayRef;

typedef struct _X_SingletonWithAllTypes_ConstArrayRef
{
    X_SingletonWithAllTypes_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
X_SingletonWithAllTypes_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl X_SingletonWithAllTypes_rtti;

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Construct(
    X_SingletonWithAllTypes* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &X_SingletonWithAllTypes_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clone(
    const X_SingletonWithAllTypes* self,
    X_SingletonWithAllTypes** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL X_SingletonWithAllTypes_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &X_SingletonWithAllTypes_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Destruct(X_SingletonWithAllTypes* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Delete(X_SingletonWithAllTypes* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Post(
    const X_SingletonWithAllTypes* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_id(
    X_SingletonWithAllTypes* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->id)->value = x;
    ((MI_Uint64Field*)&self->id)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_id(
    X_SingletonWithAllTypes* self)
{
    memset((void*)&self->id, 0, sizeof(self->id));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_b(
    X_SingletonWithAllTypes* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->b)->value = x;
    ((MI_BooleanField*)&self->b)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_b(
    X_SingletonWithAllTypes* self)
{
    memset((void*)&self->b, 0, sizeof(self->b));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_u8(
    X_SingletonWithAllTypes* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->u8)->value = x;
    ((MI_Uint8Field*)&self->u8)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_u8(
    X_SingletonWithAllTypes* self)
{
    memset((void*)&self->u8, 0, sizeof(self->u8));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_s8(
    X_SingletonWithAllTypes* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->s8)->value = x;
    ((MI_Sint8Field*)&self->s8)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_s8(
    X_SingletonWithAllTypes* self)
{
    memset((void*)&self->s8, 0, sizeof(self->s8));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_u16(
    X_SingletonWithAllTypes* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->u16)->value = x;
    ((MI_Uint16Field*)&self->u16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_u16(
    X_SingletonWithAllTypes* self)
{
    memset((void*)&self->u16, 0, sizeof(self->u16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_s16(
    X_SingletonWithAllTypes* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->s16)->value = x;
    ((MI_Sint16Field*)&self->s16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_s16(
    X_SingletonWithAllTypes* self)
{
    memset((void*)&self->s16, 0, sizeof(self->s16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_u32(
    X_SingletonWithAllTypes* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->u32)->value = x;
    ((MI_Uint32Field*)&self->u32)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_u32(
    X_SingletonWithAllTypes* self)
{
    memset((void*)&self->u32, 0, sizeof(self->u32));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_s32(
    X_SingletonWithAllTypes* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->s32)->value = x;
    ((MI_Sint32Field*)&self->s32)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_s32(
    X_SingletonWithAllTypes* self)
{
    memset((void*)&self->s32, 0, sizeof(self->s32));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_u64(
    X_SingletonWithAllTypes* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->u64)->value = x;
    ((MI_Uint64Field*)&self->u64)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_u64(
    X_SingletonWithAllTypes* self)
{
    memset((void*)&self->u64, 0, sizeof(self->u64));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_s64(
    X_SingletonWithAllTypes* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->s64)->value = x;
    ((MI_Sint64Field*)&self->s64)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_s64(
    X_SingletonWithAllTypes* self)
{
    memset((void*)&self->s64, 0, sizeof(self->s64));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_r32(
    X_SingletonWithAllTypes* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->r32)->value = x;
    ((MI_Real32Field*)&self->r32)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_r32(
    X_SingletonWithAllTypes* self)
{
    memset((void*)&self->r32, 0, sizeof(self->r32));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_r64(
    X_SingletonWithAllTypes* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->r64)->value = x;
    ((MI_Real64Field*)&self->r64)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_r64(
    X_SingletonWithAllTypes* self)
{
    memset((void*)&self->r64, 0, sizeof(self->r64));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_dt(
    X_SingletonWithAllTypes* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->dt)->value = x;
    ((MI_DatetimeField*)&self->dt)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_dt(
    X_SingletonWithAllTypes* self)
{
    memset((void*)&self->dt, 0, sizeof(self->dt));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_s(
    X_SingletonWithAllTypes* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_s(
    X_SingletonWithAllTypes* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_s(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_c16(
    X_SingletonWithAllTypes* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->c16)->value = x;
    ((MI_Char16Field*)&self->c16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_c16(
    X_SingletonWithAllTypes* self)
{
    memset((void*)&self->c16, 0, sizeof(self->c16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_bA(
    X_SingletonWithAllTypes* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_bA(
    X_SingletonWithAllTypes* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_bA(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_u8A(
    X_SingletonWithAllTypes* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_u8A(
    X_SingletonWithAllTypes* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_u8A(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_s8A(
    X_SingletonWithAllTypes* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&arr,
        MI_SINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_s8A(
    X_SingletonWithAllTypes* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&arr,
        MI_SINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_s8A(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_u16A(
    X_SingletonWithAllTypes* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_u16A(
    X_SingletonWithAllTypes* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_u16A(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_s16A(
    X_SingletonWithAllTypes* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&arr,
        MI_SINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_s16A(
    X_SingletonWithAllTypes* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&arr,
        MI_SINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_s16A(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_u32A(
    X_SingletonWithAllTypes* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&arr,
        MI_UINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_u32A(
    X_SingletonWithAllTypes* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&arr,
        MI_UINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_u32A(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        20);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_s32A(
    X_SingletonWithAllTypes* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&arr,
        MI_SINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_s32A(
    X_SingletonWithAllTypes* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&arr,
        MI_SINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_s32A(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_u64A(
    X_SingletonWithAllTypes* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&arr,
        MI_UINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_u64A(
    X_SingletonWithAllTypes* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&arr,
        MI_UINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_u64A(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_s64A(
    X_SingletonWithAllTypes* self,
    const MI_Sint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&arr,
        MI_SINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_s64A(
    X_SingletonWithAllTypes* self,
    const MI_Sint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&arr,
        MI_SINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_s64A(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_r32A(
    X_SingletonWithAllTypes* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&arr,
        MI_REAL32A,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_r32A(
    X_SingletonWithAllTypes* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&arr,
        MI_REAL32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_r32A(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_r64A(
    X_SingletonWithAllTypes* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&arr,
        MI_REAL64A,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_r64A(
    X_SingletonWithAllTypes* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&arr,
        MI_REAL64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_r64A(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        25);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_dtA(
    X_SingletonWithAllTypes* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_dtA(
    X_SingletonWithAllTypes* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_dtA(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_sA(
    X_SingletonWithAllTypes* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_sA(
    X_SingletonWithAllTypes* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_sA(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        27);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_c16A(
    X_SingletonWithAllTypes* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        28,
        (MI_Value*)&arr,
        MI_CHAR16A,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_c16A(
    X_SingletonWithAllTypes* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        28,
        (MI_Value*)&arr,
        MI_CHAR16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_c16A(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        28);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_person(
    X_SingletonWithAllTypes* self,
    const MSFT_Person* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_person(
    X_SingletonWithAllTypes* self,
    const MSFT_Person* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_person(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        29);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_fourObjects(
    X_SingletonWithAllTypes* self,
    const X_TestObject * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_fourObjects(
    X_SingletonWithAllTypes* self,
    const X_TestObject * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_fourObjects(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        30);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_objectSingle(
    X_SingletonWithAllTypes* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        31,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_objectSingle(
    X_SingletonWithAllTypes* self,
    const MI_Instance* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        31,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_objectSingle(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        31);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Set_objectsArray(
    X_SingletonWithAllTypes* self,
    const MI_Instance * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        0);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_SetPtr_objectsArray(
    X_SingletonWithAllTypes* self,
    const MI_Instance * const * data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        32,
        (MI_Value*)&arr,
        MI_INSTANCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL X_SingletonWithAllTypes_Clear_objectsArray(
    X_SingletonWithAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        32);
}

/*
**==============================================================================
**
** X_SingletonWithAllTypes provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _X_SingletonWithAllTypes_Self X_SingletonWithAllTypes_Self;

MI_EXTERN_C void MI_CALL X_SingletonWithAllTypes_Load(
    X_SingletonWithAllTypes_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_SingletonWithAllTypes_Unload(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL X_SingletonWithAllTypes_EnumerateInstances(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL X_SingletonWithAllTypes_GetInstance(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SingletonWithAllTypes* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_SingletonWithAllTypes_CreateInstance(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SingletonWithAllTypes* newInstance);

MI_EXTERN_C void MI_CALL X_SingletonWithAllTypes_ModifyInstance(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SingletonWithAllTypes* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL X_SingletonWithAllTypes_DeleteInstance(
    X_SingletonWithAllTypes_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const X_SingletonWithAllTypes* instanceName);


/*
**==============================================================================
**
** X_SingletonWithAllTypes_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class X_SingletonWithAllTypes_Class : public Instance
{
public:
    
    typedef X_SingletonWithAllTypes Self;
    
    X_SingletonWithAllTypes_Class() :
        Instance(&X_SingletonWithAllTypes_rtti)
    {
    }
    
    X_SingletonWithAllTypes_Class(
        const X_SingletonWithAllTypes* instanceName,
        bool keysOnly) :
        Instance(
            &X_SingletonWithAllTypes_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    X_SingletonWithAllTypes_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    X_SingletonWithAllTypes_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    X_SingletonWithAllTypes_Class& operator=(
        const X_SingletonWithAllTypes_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    X_SingletonWithAllTypes_Class(
        const X_SingletonWithAllTypes_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &X_SingletonWithAllTypes_rtti;
    }

    //
    // X_SingletonWithAllTypes_Class.id
    //
    
    const Field<Uint64>& id() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint64>(n);
    }
    
    void id(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& id_value() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint64>(n).value;
    }
    
    void id_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint64>(n).Set(x);
    }
    
    bool id_exists() const
    {
        const size_t n = offsetof(Self, id);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void id_clear()
    {
        const size_t n = offsetof(Self, id);
        GetField<Uint64>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.b
    //
    
    const Field<Boolean>& b() const
    {
        const size_t n = offsetof(Self, b);
        return GetField<Boolean>(n);
    }
    
    void b(const Field<Boolean>& x)
    {
        const size_t n = offsetof(Self, b);
        GetField<Boolean>(n) = x;
    }
    
    const Boolean& b_value() const
    {
        const size_t n = offsetof(Self, b);
        return GetField<Boolean>(n).value;
    }
    
    void b_value(const Boolean& x)
    {
        const size_t n = offsetof(Self, b);
        GetField<Boolean>(n).Set(x);
    }
    
    bool b_exists() const
    {
        const size_t n = offsetof(Self, b);
        return GetField<Boolean>(n).exists ? true : false;
    }
    
    void b_clear()
    {
        const size_t n = offsetof(Self, b);
        GetField<Boolean>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.u8
    //
    
    const Field<Uint8>& u8() const
    {
        const size_t n = offsetof(Self, u8);
        return GetField<Uint8>(n);
    }
    
    void u8(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, u8);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& u8_value() const
    {
        const size_t n = offsetof(Self, u8);
        return GetField<Uint8>(n).value;
    }
    
    void u8_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, u8);
        GetField<Uint8>(n).Set(x);
    }
    
    bool u8_exists() const
    {
        const size_t n = offsetof(Self, u8);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void u8_clear()
    {
        const size_t n = offsetof(Self, u8);
        GetField<Uint8>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.s8
    //
    
    const Field<Sint8>& s8() const
    {
        const size_t n = offsetof(Self, s8);
        return GetField<Sint8>(n);
    }
    
    void s8(const Field<Sint8>& x)
    {
        const size_t n = offsetof(Self, s8);
        GetField<Sint8>(n) = x;
    }
    
    const Sint8& s8_value() const
    {
        const size_t n = offsetof(Self, s8);
        return GetField<Sint8>(n).value;
    }
    
    void s8_value(const Sint8& x)
    {
        const size_t n = offsetof(Self, s8);
        GetField<Sint8>(n).Set(x);
    }
    
    bool s8_exists() const
    {
        const size_t n = offsetof(Self, s8);
        return GetField<Sint8>(n).exists ? true : false;
    }
    
    void s8_clear()
    {
        const size_t n = offsetof(Self, s8);
        GetField<Sint8>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.u16
    //
    
    const Field<Uint16>& u16() const
    {
        const size_t n = offsetof(Self, u16);
        return GetField<Uint16>(n);
    }
    
    void u16(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, u16);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& u16_value() const
    {
        const size_t n = offsetof(Self, u16);
        return GetField<Uint16>(n).value;
    }
    
    void u16_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, u16);
        GetField<Uint16>(n).Set(x);
    }
    
    bool u16_exists() const
    {
        const size_t n = offsetof(Self, u16);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void u16_clear()
    {
        const size_t n = offsetof(Self, u16);
        GetField<Uint16>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.s16
    //
    
    const Field<Sint16>& s16() const
    {
        const size_t n = offsetof(Self, s16);
        return GetField<Sint16>(n);
    }
    
    void s16(const Field<Sint16>& x)
    {
        const size_t n = offsetof(Self, s16);
        GetField<Sint16>(n) = x;
    }
    
    const Sint16& s16_value() const
    {
        const size_t n = offsetof(Self, s16);
        return GetField<Sint16>(n).value;
    }
    
    void s16_value(const Sint16& x)
    {
        const size_t n = offsetof(Self, s16);
        GetField<Sint16>(n).Set(x);
    }
    
    bool s16_exists() const
    {
        const size_t n = offsetof(Self, s16);
        return GetField<Sint16>(n).exists ? true : false;
    }
    
    void s16_clear()
    {
        const size_t n = offsetof(Self, s16);
        GetField<Sint16>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.u32
    //
    
    const Field<Uint32>& u32() const
    {
        const size_t n = offsetof(Self, u32);
        return GetField<Uint32>(n);
    }
    
    void u32(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, u32);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& u32_value() const
    {
        const size_t n = offsetof(Self, u32);
        return GetField<Uint32>(n).value;
    }
    
    void u32_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, u32);
        GetField<Uint32>(n).Set(x);
    }
    
    bool u32_exists() const
    {
        const size_t n = offsetof(Self, u32);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void u32_clear()
    {
        const size_t n = offsetof(Self, u32);
        GetField<Uint32>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.s32
    //
    
    const Field<Sint32>& s32() const
    {
        const size_t n = offsetof(Self, s32);
        return GetField<Sint32>(n);
    }
    
    void s32(const Field<Sint32>& x)
    {
        const size_t n = offsetof(Self, s32);
        GetField<Sint32>(n) = x;
    }
    
    const Sint32& s32_value() const
    {
        const size_t n = offsetof(Self, s32);
        return GetField<Sint32>(n).value;
    }
    
    void s32_value(const Sint32& x)
    {
        const size_t n = offsetof(Self, s32);
        GetField<Sint32>(n).Set(x);
    }
    
    bool s32_exists() const
    {
        const size_t n = offsetof(Self, s32);
        return GetField<Sint32>(n).exists ? true : false;
    }
    
    void s32_clear()
    {
        const size_t n = offsetof(Self, s32);
        GetField<Sint32>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.u64
    //
    
    const Field<Uint64>& u64() const
    {
        const size_t n = offsetof(Self, u64);
        return GetField<Uint64>(n);
    }
    
    void u64(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, u64);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& u64_value() const
    {
        const size_t n = offsetof(Self, u64);
        return GetField<Uint64>(n).value;
    }
    
    void u64_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, u64);
        GetField<Uint64>(n).Set(x);
    }
    
    bool u64_exists() const
    {
        const size_t n = offsetof(Self, u64);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void u64_clear()
    {
        const size_t n = offsetof(Self, u64);
        GetField<Uint64>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.s64
    //
    
    const Field<Sint64>& s64() const
    {
        const size_t n = offsetof(Self, s64);
        return GetField<Sint64>(n);
    }
    
    void s64(const Field<Sint64>& x)
    {
        const size_t n = offsetof(Self, s64);
        GetField<Sint64>(n) = x;
    }
    
    const Sint64& s64_value() const
    {
        const size_t n = offsetof(Self, s64);
        return GetField<Sint64>(n).value;
    }
    
    void s64_value(const Sint64& x)
    {
        const size_t n = offsetof(Self, s64);
        GetField<Sint64>(n).Set(x);
    }
    
    bool s64_exists() const
    {
        const size_t n = offsetof(Self, s64);
        return GetField<Sint64>(n).exists ? true : false;
    }
    
    void s64_clear()
    {
        const size_t n = offsetof(Self, s64);
        GetField<Sint64>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.r32
    //
    
    const Field<Real32>& r32() const
    {
        const size_t n = offsetof(Self, r32);
        return GetField<Real32>(n);
    }
    
    void r32(const Field<Real32>& x)
    {
        const size_t n = offsetof(Self, r32);
        GetField<Real32>(n) = x;
    }
    
    const Real32& r32_value() const
    {
        const size_t n = offsetof(Self, r32);
        return GetField<Real32>(n).value;
    }
    
    void r32_value(const Real32& x)
    {
        const size_t n = offsetof(Self, r32);
        GetField<Real32>(n).Set(x);
    }
    
    bool r32_exists() const
    {
        const size_t n = offsetof(Self, r32);
        return GetField<Real32>(n).exists ? true : false;
    }
    
    void r32_clear()
    {
        const size_t n = offsetof(Self, r32);
        GetField<Real32>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.r64
    //
    
    const Field<Real64>& r64() const
    {
        const size_t n = offsetof(Self, r64);
        return GetField<Real64>(n);
    }
    
    void r64(const Field<Real64>& x)
    {
        const size_t n = offsetof(Self, r64);
        GetField<Real64>(n) = x;
    }
    
    const Real64& r64_value() const
    {
        const size_t n = offsetof(Self, r64);
        return GetField<Real64>(n).value;
    }
    
    void r64_value(const Real64& x)
    {
        const size_t n = offsetof(Self, r64);
        GetField<Real64>(n).Set(x);
    }
    
    bool r64_exists() const
    {
        const size_t n = offsetof(Self, r64);
        return GetField<Real64>(n).exists ? true : false;
    }
    
    void r64_clear()
    {
        const size_t n = offsetof(Self, r64);
        GetField<Real64>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.dt
    //
    
    const Field<Datetime>& dt() const
    {
        const size_t n = offsetof(Self, dt);
        return GetField<Datetime>(n);
    }
    
    void dt(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, dt);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& dt_value() const
    {
        const size_t n = offsetof(Self, dt);
        return GetField<Datetime>(n).value;
    }
    
    void dt_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, dt);
        GetField<Datetime>(n).Set(x);
    }
    
    bool dt_exists() const
    {
        const size_t n = offsetof(Self, dt);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void dt_clear()
    {
        const size_t n = offsetof(Self, dt);
        GetField<Datetime>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.s
    //
    
    const Field<String>& s() const
    {
        const size_t n = offsetof(Self, s);
        return GetField<String>(n);
    }
    
    void s(const Field<String>& x)
    {
        const size_t n = offsetof(Self, s);
        GetField<String>(n) = x;
    }
    
    const String& s_value() const
    {
        const size_t n = offsetof(Self, s);
        return GetField<String>(n).value;
    }
    
    void s_value(const String& x)
    {
        const size_t n = offsetof(Self, s);
        GetField<String>(n).Set(x);
    }
    
    bool s_exists() const
    {
        const size_t n = offsetof(Self, s);
        return GetField<String>(n).exists ? true : false;
    }
    
    void s_clear()
    {
        const size_t n = offsetof(Self, s);
        GetField<String>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.c16
    //
    
    const Field<Char16>& c16() const
    {
        const size_t n = offsetof(Self, c16);
        return GetField<Char16>(n);
    }
    
    void c16(const Field<Char16>& x)
    {
        const size_t n = offsetof(Self, c16);
        GetField<Char16>(n) = x;
    }
    
    const Char16& c16_value() const
    {
        const size_t n = offsetof(Self, c16);
        return GetField<Char16>(n).value;
    }
    
    void c16_value(const Char16& x)
    {
        const size_t n = offsetof(Self, c16);
        GetField<Char16>(n).Set(x);
    }
    
    bool c16_exists() const
    {
        const size_t n = offsetof(Self, c16);
        return GetField<Char16>(n).exists ? true : false;
    }
    
    void c16_clear()
    {
        const size_t n = offsetof(Self, c16);
        GetField<Char16>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.bA
    //
    
    const Field<BooleanA>& bA() const
    {
        const size_t n = offsetof(Self, bA);
        return GetField<BooleanA>(n);
    }
    
    void bA(const Field<BooleanA>& x)
    {
        const size_t n = offsetof(Self, bA);
        GetField<BooleanA>(n) = x;
    }
    
    const BooleanA& bA_value() const
    {
        const size_t n = offsetof(Self, bA);
        return GetField<BooleanA>(n).value;
    }
    
    void bA_value(const BooleanA& x)
    {
        const size_t n = offsetof(Self, bA);
        GetField<BooleanA>(n).Set(x);
    }
    
    bool bA_exists() const
    {
        const size_t n = offsetof(Self, bA);
        return GetField<BooleanA>(n).exists ? true : false;
    }
    
    void bA_clear()
    {
        const size_t n = offsetof(Self, bA);
        GetField<BooleanA>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.u8A
    //
    
    const Field<Uint8A>& u8A() const
    {
        const size_t n = offsetof(Self, u8A);
        return GetField<Uint8A>(n);
    }
    
    void u8A(const Field<Uint8A>& x)
    {
        const size_t n = offsetof(Self, u8A);
        GetField<Uint8A>(n) = x;
    }
    
    const Uint8A& u8A_value() const
    {
        const size_t n = offsetof(Self, u8A);
        return GetField<Uint8A>(n).value;
    }
    
    void u8A_value(const Uint8A& x)
    {
        const size_t n = offsetof(Self, u8A);
        GetField<Uint8A>(n).Set(x);
    }
    
    bool u8A_exists() const
    {
        const size_t n = offsetof(Self, u8A);
        return GetField<Uint8A>(n).exists ? true : false;
    }
    
    void u8A_clear()
    {
        const size_t n = offsetof(Self, u8A);
        GetField<Uint8A>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.s8A
    //
    
    const Field<Sint8A>& s8A() const
    {
        const size_t n = offsetof(Self, s8A);
        return GetField<Sint8A>(n);
    }
    
    void s8A(const Field<Sint8A>& x)
    {
        const size_t n = offsetof(Self, s8A);
        GetField<Sint8A>(n) = x;
    }
    
    const Sint8A& s8A_value() const
    {
        const size_t n = offsetof(Self, s8A);
        return GetField<Sint8A>(n).value;
    }
    
    void s8A_value(const Sint8A& x)
    {
        const size_t n = offsetof(Self, s8A);
        GetField<Sint8A>(n).Set(x);
    }
    
    bool s8A_exists() const
    {
        const size_t n = offsetof(Self, s8A);
        return GetField<Sint8A>(n).exists ? true : false;
    }
    
    void s8A_clear()
    {
        const size_t n = offsetof(Self, s8A);
        GetField<Sint8A>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.u16A
    //
    
    const Field<Uint16A>& u16A() const
    {
        const size_t n = offsetof(Self, u16A);
        return GetField<Uint16A>(n);
    }
    
    void u16A(const Field<Uint16A>& x)
    {
        const size_t n = offsetof(Self, u16A);
        GetField<Uint16A>(n) = x;
    }
    
    const Uint16A& u16A_value() const
    {
        const size_t n = offsetof(Self, u16A);
        return GetField<Uint16A>(n).value;
    }
    
    void u16A_value(const Uint16A& x)
    {
        const size_t n = offsetof(Self, u16A);
        GetField<Uint16A>(n).Set(x);
    }
    
    bool u16A_exists() const
    {
        const size_t n = offsetof(Self, u16A);
        return GetField<Uint16A>(n).exists ? true : false;
    }
    
    void u16A_clear()
    {
        const size_t n = offsetof(Self, u16A);
        GetField<Uint16A>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.s16A
    //
    
    const Field<Sint16A>& s16A() const
    {
        const size_t n = offsetof(Self, s16A);
        return GetField<Sint16A>(n);
    }
    
    void s16A(const Field<Sint16A>& x)
    {
        const size_t n = offsetof(Self, s16A);
        GetField<Sint16A>(n) = x;
    }
    
    const Sint16A& s16A_value() const
    {
        const size_t n = offsetof(Self, s16A);
        return GetField<Sint16A>(n).value;
    }
    
    void s16A_value(const Sint16A& x)
    {
        const size_t n = offsetof(Self, s16A);
        GetField<Sint16A>(n).Set(x);
    }
    
    bool s16A_exists() const
    {
        const size_t n = offsetof(Self, s16A);
        return GetField<Sint16A>(n).exists ? true : false;
    }
    
    void s16A_clear()
    {
        const size_t n = offsetof(Self, s16A);
        GetField<Sint16A>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.u32A
    //
    
    const Field<Uint32A>& u32A() const
    {
        const size_t n = offsetof(Self, u32A);
        return GetField<Uint32A>(n);
    }
    
    void u32A(const Field<Uint32A>& x)
    {
        const size_t n = offsetof(Self, u32A);
        GetField<Uint32A>(n) = x;
    }
    
    const Uint32A& u32A_value() const
    {
        const size_t n = offsetof(Self, u32A);
        return GetField<Uint32A>(n).value;
    }
    
    void u32A_value(const Uint32A& x)
    {
        const size_t n = offsetof(Self, u32A);
        GetField<Uint32A>(n).Set(x);
    }
    
    bool u32A_exists() const
    {
        const size_t n = offsetof(Self, u32A);
        return GetField<Uint32A>(n).exists ? true : false;
    }
    
    void u32A_clear()
    {
        const size_t n = offsetof(Self, u32A);
        GetField<Uint32A>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.s32A
    //
    
    const Field<Sint32A>& s32A() const
    {
        const size_t n = offsetof(Self, s32A);
        return GetField<Sint32A>(n);
    }
    
    void s32A(const Field<Sint32A>& x)
    {
        const size_t n = offsetof(Self, s32A);
        GetField<Sint32A>(n) = x;
    }
    
    const Sint32A& s32A_value() const
    {
        const size_t n = offsetof(Self, s32A);
        return GetField<Sint32A>(n).value;
    }
    
    void s32A_value(const Sint32A& x)
    {
        const size_t n = offsetof(Self, s32A);
        GetField<Sint32A>(n).Set(x);
    }
    
    bool s32A_exists() const
    {
        const size_t n = offsetof(Self, s32A);
        return GetField<Sint32A>(n).exists ? true : false;
    }
    
    void s32A_clear()
    {
        const size_t n = offsetof(Self, s32A);
        GetField<Sint32A>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.u64A
    //
    
    const Field<Uint64A>& u64A() const
    {
        const size_t n = offsetof(Self, u64A);
        return GetField<Uint64A>(n);
    }
    
    void u64A(const Field<Uint64A>& x)
    {
        const size_t n = offsetof(Self, u64A);
        GetField<Uint64A>(n) = x;
    }
    
    const Uint64A& u64A_value() const
    {
        const size_t n = offsetof(Self, u64A);
        return GetField<Uint64A>(n).value;
    }
    
    void u64A_value(const Uint64A& x)
    {
        const size_t n = offsetof(Self, u64A);
        GetField<Uint64A>(n).Set(x);
    }
    
    bool u64A_exists() const
    {
        const size_t n = offsetof(Self, u64A);
        return GetField<Uint64A>(n).exists ? true : false;
    }
    
    void u64A_clear()
    {
        const size_t n = offsetof(Self, u64A);
        GetField<Uint64A>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.s64A
    //
    
    const Field<Sint64A>& s64A() const
    {
        const size_t n = offsetof(Self, s64A);
        return GetField<Sint64A>(n);
    }
    
    void s64A(const Field<Sint64A>& x)
    {
        const size_t n = offsetof(Self, s64A);
        GetField<Sint64A>(n) = x;
    }
    
    const Sint64A& s64A_value() const
    {
        const size_t n = offsetof(Self, s64A);
        return GetField<Sint64A>(n).value;
    }
    
    void s64A_value(const Sint64A& x)
    {
        const size_t n = offsetof(Self, s64A);
        GetField<Sint64A>(n).Set(x);
    }
    
    bool s64A_exists() const
    {
        const size_t n = offsetof(Self, s64A);
        return GetField<Sint64A>(n).exists ? true : false;
    }
    
    void s64A_clear()
    {
        const size_t n = offsetof(Self, s64A);
        GetField<Sint64A>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.r32A
    //
    
    const Field<Real32A>& r32A() const
    {
        const size_t n = offsetof(Self, r32A);
        return GetField<Real32A>(n);
    }
    
    void r32A(const Field<Real32A>& x)
    {
        const size_t n = offsetof(Self, r32A);
        GetField<Real32A>(n) = x;
    }
    
    const Real32A& r32A_value() const
    {
        const size_t n = offsetof(Self, r32A);
        return GetField<Real32A>(n).value;
    }
    
    void r32A_value(const Real32A& x)
    {
        const size_t n = offsetof(Self, r32A);
        GetField<Real32A>(n).Set(x);
    }
    
    bool r32A_exists() const
    {
        const size_t n = offsetof(Self, r32A);
        return GetField<Real32A>(n).exists ? true : false;
    }
    
    void r32A_clear()
    {
        const size_t n = offsetof(Self, r32A);
        GetField<Real32A>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.r64A
    //
    
    const Field<Real64A>& r64A() const
    {
        const size_t n = offsetof(Self, r64A);
        return GetField<Real64A>(n);
    }
    
    void r64A(const Field<Real64A>& x)
    {
        const size_t n = offsetof(Self, r64A);
        GetField<Real64A>(n) = x;
    }
    
    const Real64A& r64A_value() const
    {
        const size_t n = offsetof(Self, r64A);
        return GetField<Real64A>(n).value;
    }
    
    void r64A_value(const Real64A& x)
    {
        const size_t n = offsetof(Self, r64A);
        GetField<Real64A>(n).Set(x);
    }
    
    bool r64A_exists() const
    {
        const size_t n = offsetof(Self, r64A);
        return GetField<Real64A>(n).exists ? true : false;
    }
    
    void r64A_clear()
    {
        const size_t n = offsetof(Self, r64A);
        GetField<Real64A>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.dtA
    //
    
    const Field<DatetimeA>& dtA() const
    {
        const size_t n = offsetof(Self, dtA);
        return GetField<DatetimeA>(n);
    }
    
    void dtA(const Field<DatetimeA>& x)
    {
        const size_t n = offsetof(Self, dtA);
        GetField<DatetimeA>(n) = x;
    }
    
    const DatetimeA& dtA_value() const
    {
        const size_t n = offsetof(Self, dtA);
        return GetField<DatetimeA>(n).value;
    }
    
    void dtA_value(const DatetimeA& x)
    {
        const size_t n = offsetof(Self, dtA);
        GetField<DatetimeA>(n).Set(x);
    }
    
    bool dtA_exists() const
    {
        const size_t n = offsetof(Self, dtA);
        return GetField<DatetimeA>(n).exists ? true : false;
    }
    
    void dtA_clear()
    {
        const size_t n = offsetof(Self, dtA);
        GetField<DatetimeA>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.sA
    //
    
    const Field<StringA>& sA() const
    {
        const size_t n = offsetof(Self, sA);
        return GetField<StringA>(n);
    }
    
    void sA(const Field<StringA>& x)
    {
        const size_t n = offsetof(Self, sA);
        GetField<StringA>(n) = x;
    }
    
    const StringA& sA_value() const
    {
        const size_t n = offsetof(Self, sA);
        return GetField<StringA>(n).value;
    }
    
    void sA_value(const StringA& x)
    {
        const size_t n = offsetof(Self, sA);
        GetField<StringA>(n).Set(x);
    }
    
    bool sA_exists() const
    {
        const size_t n = offsetof(Self, sA);
        return GetField<StringA>(n).exists ? true : false;
    }
    
    void sA_clear()
    {
        const size_t n = offsetof(Self, sA);
        GetField<StringA>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.c16A
    //
    
    const Field<Char16A>& c16A() const
    {
        const size_t n = offsetof(Self, c16A);
        return GetField<Char16A>(n);
    }
    
    void c16A(const Field<Char16A>& x)
    {
        const size_t n = offsetof(Self, c16A);
        GetField<Char16A>(n) = x;
    }
    
    const Char16A& c16A_value() const
    {
        const size_t n = offsetof(Self, c16A);
        return GetField<Char16A>(n).value;
    }
    
    void c16A_value(const Char16A& x)
    {
        const size_t n = offsetof(Self, c16A);
        GetField<Char16A>(n).Set(x);
    }
    
    bool c16A_exists() const
    {
        const size_t n = offsetof(Self, c16A);
        return GetField<Char16A>(n).exists ? true : false;
    }
    
    void c16A_clear()
    {
        const size_t n = offsetof(Self, c16A);
        GetField<Char16A>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.person
    //
    
    const Field<MSFT_Person_Class>& person() const
    {
        const size_t n = offsetof(Self, person);
        return GetField<MSFT_Person_Class>(n);
    }
    
    void person(const Field<MSFT_Person_Class>& x)
    {
        const size_t n = offsetof(Self, person);
        GetField<MSFT_Person_Class>(n) = x;
    }
    
    const MSFT_Person_Class& person_value() const
    {
        const size_t n = offsetof(Self, person);
        return GetField<MSFT_Person_Class>(n).value;
    }
    
    void person_value(const MSFT_Person_Class& x)
    {
        const size_t n = offsetof(Self, person);
        GetField<MSFT_Person_Class>(n).Set(x);
    }
    
    bool person_exists() const
    {
        const size_t n = offsetof(Self, person);
        return GetField<MSFT_Person_Class>(n).exists ? true : false;
    }
    
    void person_clear()
    {
        const size_t n = offsetof(Self, person);
        GetField<MSFT_Person_Class>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.fourObjects
    //
    
    const Field<X_TestObject_ClassA>& fourObjects() const
    {
        const size_t n = offsetof(Self, fourObjects);
        return GetField<X_TestObject_ClassA>(n);
    }
    
    void fourObjects(const Field<X_TestObject_ClassA>& x)
    {
        const size_t n = offsetof(Self, fourObjects);
        GetField<X_TestObject_ClassA>(n) = x;
    }
    
    const X_TestObject_ClassA& fourObjects_value() const
    {
        const size_t n = offsetof(Self, fourObjects);
        return GetField<X_TestObject_ClassA>(n).value;
    }
    
    void fourObjects_value(const X_TestObject_ClassA& x)
    {
        const size_t n = offsetof(Self, fourObjects);
        GetField<X_TestObject_ClassA>(n).Set(x);
    }
    
    bool fourObjects_exists() const
    {
        const size_t n = offsetof(Self, fourObjects);
        return GetField<X_TestObject_ClassA>(n).exists ? true : false;
    }
    
    void fourObjects_clear()
    {
        const size_t n = offsetof(Self, fourObjects);
        GetField<X_TestObject_ClassA>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.objectSingle
    //
    
    const Field<Instance>& objectSingle() const
    {
        const size_t n = offsetof(Self, objectSingle);
        return GetField<Instance>(n);
    }
    
    void objectSingle(const Field<Instance>& x)
    {
        const size_t n = offsetof(Self, objectSingle);
        GetField<Instance>(n) = x;
    }
    
    const Instance& objectSingle_value() const
    {
        const size_t n = offsetof(Self, objectSingle);
        return GetField<Instance>(n).value;
    }
    
    void objectSingle_value(const Instance& x)
    {
        const size_t n = offsetof(Self, objectSingle);
        GetField<Instance>(n).Set(x);
    }
    
    bool objectSingle_exists() const
    {
        const size_t n = offsetof(Self, objectSingle);
        return GetField<Instance>(n).exists ? true : false;
    }
    
    void objectSingle_clear()
    {
        const size_t n = offsetof(Self, objectSingle);
        GetField<Instance>(n).Clear();
    }

    //
    // X_SingletonWithAllTypes_Class.objectsArray
    //
    
    const Field<InstanceA>& objectsArray() const
    {
        const size_t n = offsetof(Self, objectsArray);
        return GetField<InstanceA>(n);
    }
    
    void objectsArray(const Field<InstanceA>& x)
    {
        const size_t n = offsetof(Self, objectsArray);
        GetField<InstanceA>(n) = x;
    }
    
    const InstanceA& objectsArray_value() const
    {
        const size_t n = offsetof(Self, objectsArray);
        return GetField<InstanceA>(n).value;
    }
    
    void objectsArray_value(const InstanceA& x)
    {
        const size_t n = offsetof(Self, objectsArray);
        GetField<InstanceA>(n).Set(x);
    }
    
    bool objectsArray_exists() const
    {
        const size_t n = offsetof(Self, objectsArray);
        return GetField<InstanceA>(n).exists ? true : false;
    }
    
    void objectsArray_clear()
    {
        const size_t n = offsetof(Self, objectsArray);
        GetField<InstanceA>(n).Clear();
    }
};

typedef Array<X_SingletonWithAllTypes_Class> X_SingletonWithAllTypes_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _X_SingletonWithAllTypes_h */
