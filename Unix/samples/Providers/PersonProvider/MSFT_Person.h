/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MSFT_Person_h
#define _MSFT_Person_h

#include <MI.h>
#include "MSFT_Animal.h"
#include "MSFT_Base.h"

/*
**==============================================================================
**
** MSFT_Person [MSFT_Person]
**
** Keys:
**    Key
**
**==============================================================================
*/

typedef struct _MSFT_Person /* extends MSFT_Animal */
{
    MI_Instance __instance;
    /* MSFT_Base properties */
    /*KEY*/ MI_ConstUint32Field Key;
    /* MSFT_Animal properties */
    MI_ConstStringField Species;
    /* MSFT_Person properties */
    MI_ConstStringField Last;
    MI_ConstStringField First;
    MI_ConstUint32Field ExpensiveProperty;
}
MSFT_Person;

typedef struct _MSFT_Person_Ref
{
    MSFT_Person* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Person_Ref;

typedef struct _MSFT_Person_ConstRef
{
    MI_CONST MSFT_Person* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Person_ConstRef;

typedef struct _MSFT_Person_Array
{
    struct _MSFT_Person** data;
    MI_Uint32 size;
}
MSFT_Person_Array;

typedef struct _MSFT_Person_ConstArray
{
    struct _MSFT_Person MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MSFT_Person_ConstArray;

typedef struct _MSFT_Person_ArrayRef
{
    MSFT_Person_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Person_ArrayRef;

typedef struct _MSFT_Person_ConstArrayRef
{
    MSFT_Person_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MSFT_Person_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MSFT_Person_rtti;

MI_INLINE MI_Result MI_CALL MSFT_Person_Construct(
    MSFT_Person* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MSFT_Person_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Clone(
    const MSFT_Person* self,
    MSFT_Person** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MSFT_Person_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MSFT_Person_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Destruct(MSFT_Person* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Delete(MSFT_Person* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Post(
    const MSFT_Person* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Set_Key(
    MSFT_Person* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->Key)->value = x;
    ((MI_Uint32Field*)&self->Key)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Clear_Key(
    MSFT_Person* self)
{
    memset((void*)&self->Key, 0, sizeof(self->Key));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Set_Species(
    MSFT_Person* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_SetPtr_Species(
    MSFT_Person* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Clear_Species(
    MSFT_Person* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Set_Last(
    MSFT_Person* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_SetPtr_Last(
    MSFT_Person* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Clear_Last(
    MSFT_Person* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Set_First(
    MSFT_Person* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_SetPtr_First(
    MSFT_Person* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Clear_First(
    MSFT_Person* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Set_ExpensiveProperty(
    MSFT_Person* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->ExpensiveProperty)->value = x;
    ((MI_Uint32Field*)&self->ExpensiveProperty)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Clear_ExpensiveProperty(
    MSFT_Person* self)
{
    memset((void*)&self->ExpensiveProperty, 0, sizeof(self->ExpensiveProperty));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_Person.Add()
**
**==============================================================================
*/

typedef struct _MSFT_Person_Add
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstReal32Field X;
    /*IN*/ MI_ConstReal32Field Y;
    /*OUT*/ MI_ConstReal32Field Z;
}
MSFT_Person_Add;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_Person_Add_rtti;

MI_INLINE MI_Result MI_CALL MSFT_Person_Add_Construct(
    MSFT_Person_Add* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MSFT_Person_Add_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Add_Clone(
    const MSFT_Person_Add* self,
    MSFT_Person_Add** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Add_Destruct(
    MSFT_Person_Add* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Add_Delete(
    MSFT_Person_Add* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Add_Post(
    const MSFT_Person_Add* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Add_Set_MIReturn(
    MSFT_Person_Add* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Add_Clear_MIReturn(
    MSFT_Person_Add* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Add_Set_X(
    MSFT_Person_Add* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->X)->value = x;
    ((MI_Real32Field*)&self->X)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Add_Clear_X(
    MSFT_Person_Add* self)
{
    memset((void*)&self->X, 0, sizeof(self->X));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Add_Set_Y(
    MSFT_Person_Add* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->Y)->value = x;
    ((MI_Real32Field*)&self->Y)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Add_Clear_Y(
    MSFT_Person_Add* self)
{
    memset((void*)&self->Y, 0, sizeof(self->Y));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Add_Set_Z(
    MSFT_Person_Add* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->Z)->value = x;
    ((MI_Real32Field*)&self->Z)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_Add_Clear_Z(
    MSFT_Person_Add* self)
{
    memset((void*)&self->Z, 0, sizeof(self->Z));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MSFT_Person.TestAllTypes()
**
**==============================================================================
*/

typedef struct _MSFT_Person_TestAllTypes
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstStringField MIReturn;
    /*IN-OUT*/ MI_ConstBooleanField b;
    /*IN-OUT*/ MI_ConstUint8Field u8;
    /*IN-OUT*/ MI_ConstSint8Field s8;
    /*IN-OUT*/ MI_ConstUint16Field u16;
    /*IN-OUT*/ MI_ConstSint16Field s16;
    /*IN-OUT*/ MI_ConstUint32Field u32;
    /*IN-OUT*/ MI_ConstSint32Field s32;
    /*IN-OUT*/ MI_ConstUint64Field u64;
    /*IN-OUT*/ MI_ConstSint64Field s64;
    /*IN-OUT*/ MI_ConstReal32Field r32;
    /*IN-OUT*/ MI_ConstReal64Field r64;
    /*IN-OUT*/ MI_ConstDatetimeField dt;
    /*IN-OUT*/ MSFT_Base_ConstRef rf;
    /*IN-OUT*/ MI_ConstStringField s;
    /*IN-OUT*/ MI_ConstChar16Field c16;
    /*IN-OUT*/ MI_ConstBooleanAField bA;
    /*IN-OUT*/ MI_ConstUint8AField u8A;
    /*IN-OUT*/ MI_ConstSint8AField s8A;
    /*IN-OUT*/ MI_ConstUint16AField u16A;
    /*IN-OUT*/ MI_ConstSint16AField s16A;
    /*IN-OUT*/ MI_ConstUint32AField u32A;
    /*IN-OUT*/ MI_ConstSint32AField s32A;
    /*IN-OUT*/ MI_ConstUint64AField u64A;
    /*IN-OUT*/ MI_ConstSint64AField s64A;
    /*IN-OUT*/ MI_ConstReal32AField r32A;
    /*IN-OUT*/ MI_ConstReal64AField r64A;
    /*IN-OUT*/ MI_ConstDatetimeAField dtA;
    /*IN-OUT*/ MI_ConstStringAField sA;
    /*IN-OUT*/ MI_ConstChar16AField c16A;
    /*IN-OUT*/ MSFT_Base_ConstArrayRef rfA;
}
MSFT_Person_TestAllTypes;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_Person_TestAllTypes_rtti;

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Construct(
    MSFT_Person_TestAllTypes* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MSFT_Person_TestAllTypes_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clone(
    const MSFT_Person_TestAllTypes* self,
    MSFT_Person_TestAllTypes** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Destruct(
    MSFT_Person_TestAllTypes* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Delete(
    MSFT_Person_TestAllTypes* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Post(
    const MSFT_Person_TestAllTypes* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_MIReturn(
    MSFT_Person_TestAllTypes* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_MIReturn(
    MSFT_Person_TestAllTypes* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_MIReturn(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_b(
    MSFT_Person_TestAllTypes* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->b)->value = x;
    ((MI_BooleanField*)&self->b)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_b(
    MSFT_Person_TestAllTypes* self)
{
    memset((void*)&self->b, 0, sizeof(self->b));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_u8(
    MSFT_Person_TestAllTypes* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->u8)->value = x;
    ((MI_Uint8Field*)&self->u8)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_u8(
    MSFT_Person_TestAllTypes* self)
{
    memset((void*)&self->u8, 0, sizeof(self->u8));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_s8(
    MSFT_Person_TestAllTypes* self,
    MI_Sint8 x)
{
    ((MI_Sint8Field*)&self->s8)->value = x;
    ((MI_Sint8Field*)&self->s8)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_s8(
    MSFT_Person_TestAllTypes* self)
{
    memset((void*)&self->s8, 0, sizeof(self->s8));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_u16(
    MSFT_Person_TestAllTypes* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->u16)->value = x;
    ((MI_Uint16Field*)&self->u16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_u16(
    MSFT_Person_TestAllTypes* self)
{
    memset((void*)&self->u16, 0, sizeof(self->u16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_s16(
    MSFT_Person_TestAllTypes* self,
    MI_Sint16 x)
{
    ((MI_Sint16Field*)&self->s16)->value = x;
    ((MI_Sint16Field*)&self->s16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_s16(
    MSFT_Person_TestAllTypes* self)
{
    memset((void*)&self->s16, 0, sizeof(self->s16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_u32(
    MSFT_Person_TestAllTypes* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->u32)->value = x;
    ((MI_Uint32Field*)&self->u32)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_u32(
    MSFT_Person_TestAllTypes* self)
{
    memset((void*)&self->u32, 0, sizeof(self->u32));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_s32(
    MSFT_Person_TestAllTypes* self,
    MI_Sint32 x)
{
    ((MI_Sint32Field*)&self->s32)->value = x;
    ((MI_Sint32Field*)&self->s32)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_s32(
    MSFT_Person_TestAllTypes* self)
{
    memset((void*)&self->s32, 0, sizeof(self->s32));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_u64(
    MSFT_Person_TestAllTypes* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->u64)->value = x;
    ((MI_Uint64Field*)&self->u64)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_u64(
    MSFT_Person_TestAllTypes* self)
{
    memset((void*)&self->u64, 0, sizeof(self->u64));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_s64(
    MSFT_Person_TestAllTypes* self,
    MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->s64)->value = x;
    ((MI_Sint64Field*)&self->s64)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_s64(
    MSFT_Person_TestAllTypes* self)
{
    memset((void*)&self->s64, 0, sizeof(self->s64));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_r32(
    MSFT_Person_TestAllTypes* self,
    MI_Real32 x)
{
    ((MI_Real32Field*)&self->r32)->value = x;
    ((MI_Real32Field*)&self->r32)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_r32(
    MSFT_Person_TestAllTypes* self)
{
    memset((void*)&self->r32, 0, sizeof(self->r32));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_r64(
    MSFT_Person_TestAllTypes* self,
    MI_Real64 x)
{
    ((MI_Real64Field*)&self->r64)->value = x;
    ((MI_Real64Field*)&self->r64)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_r64(
    MSFT_Person_TestAllTypes* self)
{
    memset((void*)&self->r64, 0, sizeof(self->r64));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_dt(
    MSFT_Person_TestAllTypes* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->dt)->value = x;
    ((MI_DatetimeField*)&self->dt)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_dt(
    MSFT_Person_TestAllTypes* self)
{
    memset((void*)&self->dt, 0, sizeof(self->dt));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_rf(
    MSFT_Person_TestAllTypes* self,
    const MSFT_Base* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_rf(
    MSFT_Person_TestAllTypes* self,
    const MSFT_Base* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_rf(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_s(
    MSFT_Person_TestAllTypes* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_s(
    MSFT_Person_TestAllTypes* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_s(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_c16(
    MSFT_Person_TestAllTypes* self,
    MI_Char16 x)
{
    ((MI_Char16Field*)&self->c16)->value = x;
    ((MI_Char16Field*)&self->c16)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_c16(
    MSFT_Person_TestAllTypes* self)
{
    memset((void*)&self->c16, 0, sizeof(self->c16));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_bA(
    MSFT_Person_TestAllTypes* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_bA(
    MSFT_Person_TestAllTypes* self,
    const MI_Boolean* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&arr,
        MI_BOOLEANA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_bA(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_u8A(
    MSFT_Person_TestAllTypes* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&arr,
        MI_UINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_u8A(
    MSFT_Person_TestAllTypes* self,
    const MI_Uint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&arr,
        MI_UINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_u8A(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_s8A(
    MSFT_Person_TestAllTypes* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&arr,
        MI_SINT8A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_s8A(
    MSFT_Person_TestAllTypes* self,
    const MI_Sint8* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&arr,
        MI_SINT8A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_s8A(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_u16A(
    MSFT_Person_TestAllTypes* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_u16A(
    MSFT_Person_TestAllTypes* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_u16A(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_s16A(
    MSFT_Person_TestAllTypes* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&arr,
        MI_SINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_s16A(
    MSFT_Person_TestAllTypes* self,
    const MI_Sint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        20,
        (MI_Value*)&arr,
        MI_SINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_s16A(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        20);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_u32A(
    MSFT_Person_TestAllTypes* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&arr,
        MI_UINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_u32A(
    MSFT_Person_TestAllTypes* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&arr,
        MI_UINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_u32A(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_s32A(
    MSFT_Person_TestAllTypes* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&arr,
        MI_SINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_s32A(
    MSFT_Person_TestAllTypes* self,
    const MI_Sint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        22,
        (MI_Value*)&arr,
        MI_SINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_s32A(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        22);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_u64A(
    MSFT_Person_TestAllTypes* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&arr,
        MI_UINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_u64A(
    MSFT_Person_TestAllTypes* self,
    const MI_Uint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        23,
        (MI_Value*)&arr,
        MI_UINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_u64A(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        23);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_s64A(
    MSFT_Person_TestAllTypes* self,
    const MI_Sint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&arr,
        MI_SINT64A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_s64A(
    MSFT_Person_TestAllTypes* self,
    const MI_Sint64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        24,
        (MI_Value*)&arr,
        MI_SINT64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_s64A(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        24);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_r32A(
    MSFT_Person_TestAllTypes* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&arr,
        MI_REAL32A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_r32A(
    MSFT_Person_TestAllTypes* self,
    const MI_Real32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&arr,
        MI_REAL32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_r32A(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        25);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_r64A(
    MSFT_Person_TestAllTypes* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&arr,
        MI_REAL64A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_r64A(
    MSFT_Person_TestAllTypes* self,
    const MI_Real64* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        26,
        (MI_Value*)&arr,
        MI_REAL64A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_r64A(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        26);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_dtA(
    MSFT_Person_TestAllTypes* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_dtA(
    MSFT_Person_TestAllTypes* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        27,
        (MI_Value*)&arr,
        MI_DATETIMEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_dtA(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        27);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_sA(
    MSFT_Person_TestAllTypes* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        28,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_sA(
    MSFT_Person_TestAllTypes* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        28,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_sA(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        28);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_c16A(
    MSFT_Person_TestAllTypes* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&arr,
        MI_CHAR16A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_c16A(
    MSFT_Person_TestAllTypes* self,
    const MI_Char16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        29,
        (MI_Value*)&arr,
        MI_CHAR16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_c16A(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        29);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Set_rfA(
    MSFT_Person_TestAllTypes* self,
    const MSFT_Base* const* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_SetPtr_rfA(
    MSFT_Person_TestAllTypes* self,
    const MSFT_Base* const* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        30,
        (MI_Value*)&arr,
        MI_REFERENCEA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_TestAllTypes_Clear_rfA(
    MSFT_Person_TestAllTypes* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        30);
}

/*
**==============================================================================
**
** MSFT_Person.StreamParams()
**
**==============================================================================
*/

typedef struct _MSFT_Person_StreamParams
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint32AField InArg;
}
MSFT_Person_StreamParams;

MI_EXTERN_C MI_CONST MI_MethodDecl MSFT_Person_StreamParams_rtti;

MI_INLINE MI_Result MI_CALL MSFT_Person_StreamParams_Construct(
    MSFT_Person_StreamParams* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MSFT_Person_StreamParams_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_StreamParams_Clone(
    const MSFT_Person_StreamParams* self,
    MSFT_Person_StreamParams** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_StreamParams_Destruct(
    MSFT_Person_StreamParams* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_StreamParams_Delete(
    MSFT_Person_StreamParams* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_StreamParams_Post(
    const MSFT_Person_StreamParams* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_StreamParams_Set_MIReturn(
    MSFT_Person_StreamParams* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_StreamParams_Clear_MIReturn(
    MSFT_Person_StreamParams* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MSFT_Person_StreamParams_Set_InArg(
    MSFT_Person_StreamParams* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT32A,
        0);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_StreamParams_SetPtr_InArg(
    MSFT_Person_StreamParams* self,
    const MI_Uint32* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_UINT32A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MSFT_Person_StreamParams_Clear_InArg(
    MSFT_Person_StreamParams* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MSFT_Person provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MSFT_Person_Self MSFT_Person_Self;

MI_EXTERN_C void MI_CALL MSFT_Person_Load(
    MSFT_Person_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_Person_Unload(
    MSFT_Person_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MSFT_Person_EnumerateInstances(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MSFT_Person_GetInstance(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Person* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_Person_CreateInstance(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Person* newInstance);

MI_EXTERN_C void MI_CALL MSFT_Person_ModifyInstance(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Person* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MSFT_Person_DeleteInstance(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MSFT_Person* instanceName);

MI_EXTERN_C void MI_CALL MSFT_Person_Invoke_Add(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_Person* instanceName,
    const MSFT_Person_Add* in);

MI_EXTERN_C void MI_CALL MSFT_Person_Invoke_TestAllTypes(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_Person* instanceName,
    const MSFT_Person_TestAllTypes* in);

MI_EXTERN_C void MI_CALL MSFT_Person_Invoke_StreamParams(
    MSFT_Person_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MSFT_Person* instanceName,
    const MSFT_Person_StreamParams* in);


#endif /* _MSFT_Person_h */
