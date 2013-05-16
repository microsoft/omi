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


#endif /* _X_SingletonWithAllTypes_h */
