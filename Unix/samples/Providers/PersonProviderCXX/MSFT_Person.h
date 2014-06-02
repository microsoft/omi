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


/*
**==============================================================================
**
** MSFT_Person_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class MSFT_Person_Class : public MSFT_Animal_Class
{
public:
    
    typedef MSFT_Person Self;
    
    MSFT_Person_Class() :
        MSFT_Animal_Class(&MSFT_Person_rtti)
    {
    }
    
    MSFT_Person_Class(
        const MSFT_Person* instanceName,
        bool keysOnly) :
        MSFT_Animal_Class(
            &MSFT_Person_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MSFT_Person_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        MSFT_Animal_Class(clDecl, instance, keysOnly)
    {
    }
    
    MSFT_Person_Class(
        const MI_ClassDecl* clDecl) :
        MSFT_Animal_Class(clDecl)
    {
    }
    
    MSFT_Person_Class& operator=(
        const MSFT_Person_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MSFT_Person_Class(
        const MSFT_Person_Class& x) :
        MSFT_Animal_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &MSFT_Person_rtti;
    }

    //
    // MSFT_Person_Class.Last
    //
    
    const Field<String>& Last() const
    {
        const size_t n = offsetof(Self, Last);
        return GetField<String>(n);
    }
    
    void Last(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Last);
        GetField<String>(n) = x;
    }
    
    const String& Last_value() const
    {
        const size_t n = offsetof(Self, Last);
        return GetField<String>(n).value;
    }
    
    void Last_value(const String& x)
    {
        const size_t n = offsetof(Self, Last);
        GetField<String>(n).Set(x);
    }
    
    bool Last_exists() const
    {
        const size_t n = offsetof(Self, Last);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Last_clear()
    {
        const size_t n = offsetof(Self, Last);
        GetField<String>(n).Clear();
    }

    //
    // MSFT_Person_Class.First
    //
    
    const Field<String>& First() const
    {
        const size_t n = offsetof(Self, First);
        return GetField<String>(n);
    }
    
    void First(const Field<String>& x)
    {
        const size_t n = offsetof(Self, First);
        GetField<String>(n) = x;
    }
    
    const String& First_value() const
    {
        const size_t n = offsetof(Self, First);
        return GetField<String>(n).value;
    }
    
    void First_value(const String& x)
    {
        const size_t n = offsetof(Self, First);
        GetField<String>(n).Set(x);
    }
    
    bool First_exists() const
    {
        const size_t n = offsetof(Self, First);
        return GetField<String>(n).exists ? true : false;
    }
    
    void First_clear()
    {
        const size_t n = offsetof(Self, First);
        GetField<String>(n).Clear();
    }

    //
    // MSFT_Person_Class.ExpensiveProperty
    //
    
    const Field<Uint32>& ExpensiveProperty() const
    {
        const size_t n = offsetof(Self, ExpensiveProperty);
        return GetField<Uint32>(n);
    }
    
    void ExpensiveProperty(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, ExpensiveProperty);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& ExpensiveProperty_value() const
    {
        const size_t n = offsetof(Self, ExpensiveProperty);
        return GetField<Uint32>(n).value;
    }
    
    void ExpensiveProperty_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, ExpensiveProperty);
        GetField<Uint32>(n).Set(x);
    }
    
    bool ExpensiveProperty_exists() const
    {
        const size_t n = offsetof(Self, ExpensiveProperty);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void ExpensiveProperty_clear()
    {
        const size_t n = offsetof(Self, ExpensiveProperty);
        GetField<Uint32>(n).Clear();
    }
};

typedef Array<MSFT_Person_Class> MSFT_Person_ClassA;

class MSFT_Person_Add_Class : public Instance
{
public:
    
    typedef MSFT_Person_Add Self;
    
    MSFT_Person_Add_Class() :
        Instance(&MSFT_Person_Add_rtti)
    {
    }
    
    MSFT_Person_Add_Class(
        const MSFT_Person_Add* instanceName,
        bool keysOnly) :
        Instance(
            &MSFT_Person_Add_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MSFT_Person_Add_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    MSFT_Person_Add_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    MSFT_Person_Add_Class& operator=(
        const MSFT_Person_Add_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MSFT_Person_Add_Class(
        const MSFT_Person_Add_Class& x) :
        Instance(x)
    {
    }

    //
    // MSFT_Person_Add_Class.MIReturn
    //
    
    const Field<Uint32>& MIReturn() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Uint32>(n);
    }
    
    void MIReturn(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& MIReturn_value() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Uint32>(n).value;
    }
    
    void MIReturn_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Uint32>(n).Set(x);
    }
    
    bool MIReturn_exists() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void MIReturn_clear()
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Uint32>(n).Clear();
    }

    //
    // MSFT_Person_Add_Class.X
    //
    
    const Field<Real32>& X() const
    {
        const size_t n = offsetof(Self, X);
        return GetField<Real32>(n);
    }
    
    void X(const Field<Real32>& x)
    {
        const size_t n = offsetof(Self, X);
        GetField<Real32>(n) = x;
    }
    
    const Real32& X_value() const
    {
        const size_t n = offsetof(Self, X);
        return GetField<Real32>(n).value;
    }
    
    void X_value(const Real32& x)
    {
        const size_t n = offsetof(Self, X);
        GetField<Real32>(n).Set(x);
    }
    
    bool X_exists() const
    {
        const size_t n = offsetof(Self, X);
        return GetField<Real32>(n).exists ? true : false;
    }
    
    void X_clear()
    {
        const size_t n = offsetof(Self, X);
        GetField<Real32>(n).Clear();
    }

    //
    // MSFT_Person_Add_Class.Y
    //
    
    const Field<Real32>& Y() const
    {
        const size_t n = offsetof(Self, Y);
        return GetField<Real32>(n);
    }
    
    void Y(const Field<Real32>& x)
    {
        const size_t n = offsetof(Self, Y);
        GetField<Real32>(n) = x;
    }
    
    const Real32& Y_value() const
    {
        const size_t n = offsetof(Self, Y);
        return GetField<Real32>(n).value;
    }
    
    void Y_value(const Real32& x)
    {
        const size_t n = offsetof(Self, Y);
        GetField<Real32>(n).Set(x);
    }
    
    bool Y_exists() const
    {
        const size_t n = offsetof(Self, Y);
        return GetField<Real32>(n).exists ? true : false;
    }
    
    void Y_clear()
    {
        const size_t n = offsetof(Self, Y);
        GetField<Real32>(n).Clear();
    }

    //
    // MSFT_Person_Add_Class.Z
    //
    
    const Field<Real32>& Z() const
    {
        const size_t n = offsetof(Self, Z);
        return GetField<Real32>(n);
    }
    
    void Z(const Field<Real32>& x)
    {
        const size_t n = offsetof(Self, Z);
        GetField<Real32>(n) = x;
    }
    
    const Real32& Z_value() const
    {
        const size_t n = offsetof(Self, Z);
        return GetField<Real32>(n).value;
    }
    
    void Z_value(const Real32& x)
    {
        const size_t n = offsetof(Self, Z);
        GetField<Real32>(n).Set(x);
    }
    
    bool Z_exists() const
    {
        const size_t n = offsetof(Self, Z);
        return GetField<Real32>(n).exists ? true : false;
    }
    
    void Z_clear()
    {
        const size_t n = offsetof(Self, Z);
        GetField<Real32>(n).Clear();
    }
};

typedef Array<MSFT_Person_Add_Class> MSFT_Person_Add_ClassA;

class MSFT_Person_TestAllTypes_Class : public Instance
{
public:
    
    typedef MSFT_Person_TestAllTypes Self;
    
    MSFT_Person_TestAllTypes_Class() :
        Instance(&MSFT_Person_TestAllTypes_rtti)
    {
    }
    
    MSFT_Person_TestAllTypes_Class(
        const MSFT_Person_TestAllTypes* instanceName,
        bool keysOnly) :
        Instance(
            &MSFT_Person_TestAllTypes_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MSFT_Person_TestAllTypes_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    MSFT_Person_TestAllTypes_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    MSFT_Person_TestAllTypes_Class& operator=(
        const MSFT_Person_TestAllTypes_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MSFT_Person_TestAllTypes_Class(
        const MSFT_Person_TestAllTypes_Class& x) :
        Instance(x)
    {
    }

    //
    // MSFT_Person_TestAllTypes_Class.MIReturn
    //
    
    const Field<String>& MIReturn() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<String>(n);
    }
    
    void MIReturn(const Field<String>& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<String>(n) = x;
    }
    
    const String& MIReturn_value() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<String>(n).value;
    }
    
    void MIReturn_value(const String& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<String>(n).Set(x);
    }
    
    bool MIReturn_exists() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<String>(n).exists ? true : false;
    }
    
    void MIReturn_clear()
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<String>(n).Clear();
    }

    //
    // MSFT_Person_TestAllTypes_Class.b
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
    // MSFT_Person_TestAllTypes_Class.u8
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
    // MSFT_Person_TestAllTypes_Class.s8
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
    // MSFT_Person_TestAllTypes_Class.u16
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
    // MSFT_Person_TestAllTypes_Class.s16
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
    // MSFT_Person_TestAllTypes_Class.u32
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
    // MSFT_Person_TestAllTypes_Class.s32
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
    // MSFT_Person_TestAllTypes_Class.u64
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
    // MSFT_Person_TestAllTypes_Class.s64
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
    // MSFT_Person_TestAllTypes_Class.r32
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
    // MSFT_Person_TestAllTypes_Class.r64
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
    // MSFT_Person_TestAllTypes_Class.dt
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
    // MSFT_Person_TestAllTypes_Class.rf
    //
    
    const Field<MSFT_Base_Class>& rf() const
    {
        const size_t n = offsetof(Self, rf);
        return GetField<MSFT_Base_Class>(n);
    }
    
    void rf(const Field<MSFT_Base_Class>& x)
    {
        const size_t n = offsetof(Self, rf);
        GetField<MSFT_Base_Class>(n) = x;
    }
    
    const MSFT_Base_Class& rf_value() const
    {
        const size_t n = offsetof(Self, rf);
        return GetField<MSFT_Base_Class>(n).value;
    }
    
    void rf_value(const MSFT_Base_Class& x)
    {
        const size_t n = offsetof(Self, rf);
        GetField<MSFT_Base_Class>(n).Set(x);
    }
    
    bool rf_exists() const
    {
        const size_t n = offsetof(Self, rf);
        return GetField<MSFT_Base_Class>(n).exists ? true : false;
    }
    
    void rf_clear()
    {
        const size_t n = offsetof(Self, rf);
        GetField<MSFT_Base_Class>(n).Clear();
    }

    //
    // MSFT_Person_TestAllTypes_Class.s
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
    // MSFT_Person_TestAllTypes_Class.c16
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
    // MSFT_Person_TestAllTypes_Class.bA
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
    // MSFT_Person_TestAllTypes_Class.u8A
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
    // MSFT_Person_TestAllTypes_Class.s8A
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
    // MSFT_Person_TestAllTypes_Class.u16A
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
    // MSFT_Person_TestAllTypes_Class.s16A
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
    // MSFT_Person_TestAllTypes_Class.u32A
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
    // MSFT_Person_TestAllTypes_Class.s32A
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
    // MSFT_Person_TestAllTypes_Class.u64A
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
    // MSFT_Person_TestAllTypes_Class.s64A
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
    // MSFT_Person_TestAllTypes_Class.r32A
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
    // MSFT_Person_TestAllTypes_Class.r64A
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
    // MSFT_Person_TestAllTypes_Class.dtA
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
    // MSFT_Person_TestAllTypes_Class.sA
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
    // MSFT_Person_TestAllTypes_Class.c16A
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
    // MSFT_Person_TestAllTypes_Class.rfA
    //
    
    const Field<MSFT_Base_ClassA>& rfA() const
    {
        const size_t n = offsetof(Self, rfA);
        return GetField<MSFT_Base_ClassA>(n);
    }
    
    void rfA(const Field<MSFT_Base_ClassA>& x)
    {
        const size_t n = offsetof(Self, rfA);
        GetField<MSFT_Base_ClassA>(n) = x;
    }
    
    const MSFT_Base_ClassA& rfA_value() const
    {
        const size_t n = offsetof(Self, rfA);
        return GetField<MSFT_Base_ClassA>(n).value;
    }
    
    void rfA_value(const MSFT_Base_ClassA& x)
    {
        const size_t n = offsetof(Self, rfA);
        GetField<MSFT_Base_ClassA>(n).Set(x);
    }
    
    bool rfA_exists() const
    {
        const size_t n = offsetof(Self, rfA);
        return GetField<MSFT_Base_ClassA>(n).exists ? true : false;
    }
    
    void rfA_clear()
    {
        const size_t n = offsetof(Self, rfA);
        GetField<MSFT_Base_ClassA>(n).Clear();
    }
};

typedef Array<MSFT_Person_TestAllTypes_Class> MSFT_Person_TestAllTypes_ClassA;

class MSFT_Person_StreamParams_Class : public Instance
{
public:
    
    typedef MSFT_Person_StreamParams Self;
    
    MSFT_Person_StreamParams_Class() :
        Instance(&MSFT_Person_StreamParams_rtti)
    {
    }
    
    MSFT_Person_StreamParams_Class(
        const MSFT_Person_StreamParams* instanceName,
        bool keysOnly) :
        Instance(
            &MSFT_Person_StreamParams_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MSFT_Person_StreamParams_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    MSFT_Person_StreamParams_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    MSFT_Person_StreamParams_Class& operator=(
        const MSFT_Person_StreamParams_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MSFT_Person_StreamParams_Class(
        const MSFT_Person_StreamParams_Class& x) :
        Instance(x)
    {
    }

    //
    // MSFT_Person_StreamParams_Class.MIReturn
    //
    
    const Field<Uint32>& MIReturn() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Uint32>(n);
    }
    
    void MIReturn(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& MIReturn_value() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Uint32>(n).value;
    }
    
    void MIReturn_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Uint32>(n).Set(x);
    }
    
    bool MIReturn_exists() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void MIReturn_clear()
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Uint32>(n).Clear();
    }

    //
    // MSFT_Person_StreamParams_Class.InArg
    //
    
    const Field<Uint32A>& InArg() const
    {
        const size_t n = offsetof(Self, InArg);
        return GetField<Uint32A>(n);
    }
    
    void InArg(const Field<Uint32A>& x)
    {
        const size_t n = offsetof(Self, InArg);
        GetField<Uint32A>(n) = x;
    }
    
    const Uint32A& InArg_value() const
    {
        const size_t n = offsetof(Self, InArg);
        return GetField<Uint32A>(n).value;
    }
    
    void InArg_value(const Uint32A& x)
    {
        const size_t n = offsetof(Self, InArg);
        GetField<Uint32A>(n).Set(x);
    }
    
    bool InArg_exists() const
    {
        const size_t n = offsetof(Self, InArg);
        return GetField<Uint32A>(n).exists ? true : false;
    }
    
    void InArg_clear()
    {
        const size_t n = offsetof(Self, InArg);
        GetField<Uint32A>(n).Clear();
    }

};

typedef Array<MSFT_Person_StreamParams_Class> MSFT_Person_StreamParams_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _MSFT_Person_h */
