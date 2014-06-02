/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _TestClass_MethodProvider_Calc_h
#define _TestClass_MethodProvider_Calc_h

#include <MI.h>
#include "Numbers.h"

/*
**==============================================================================
**
** TestClass_MethodProvider_Calc [TestClass_MethodProvider_Calc]
**
** Keys:
**
**==============================================================================
*/

typedef struct _TestClass_MethodProvider_Calc
{
    MI_Instance __instance;
    /* TestClass_MethodProvider_Calc properties */
}
TestClass_MethodProvider_Calc;

typedef struct _TestClass_MethodProvider_Calc_Ref
{
    TestClass_MethodProvider_Calc* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestClass_MethodProvider_Calc_Ref;

typedef struct _TestClass_MethodProvider_Calc_ConstRef
{
    MI_CONST TestClass_MethodProvider_Calc* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestClass_MethodProvider_Calc_ConstRef;

typedef struct _TestClass_MethodProvider_Calc_Array
{
    struct _TestClass_MethodProvider_Calc** data;
    MI_Uint32 size;
}
TestClass_MethodProvider_Calc_Array;

typedef struct _TestClass_MethodProvider_Calc_ConstArray
{
    struct _TestClass_MethodProvider_Calc MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
TestClass_MethodProvider_Calc_ConstArray;

typedef struct _TestClass_MethodProvider_Calc_ArrayRef
{
    TestClass_MethodProvider_Calc_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestClass_MethodProvider_Calc_ArrayRef;

typedef struct _TestClass_MethodProvider_Calc_ConstArrayRef
{
    TestClass_MethodProvider_Calc_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
TestClass_MethodProvider_Calc_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl TestClass_MethodProvider_Calc_rtti;

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Construct(
    _Inout_ TestClass_MethodProvider_Calc* self,
    _In_ MI_Context* context)
{
    return MI_ConstructInstance(context, &TestClass_MethodProvider_Calc_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Clone(
    _In_ const TestClass_MethodProvider_Calc* self,
    _Outptr_ TestClass_MethodProvider_Calc** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL TestClass_MethodProvider_Calc_IsA(
    _In_ const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &TestClass_MethodProvider_Calc_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Destruct(_Inout_ TestClass_MethodProvider_Calc* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Delete(_Inout_ TestClass_MethodProvider_Calc* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Post(
    _In_ const TestClass_MethodProvider_Calc* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

/*
**==============================================================================
**
** TestClass_MethodProvider_Calc.Add()
**
**==============================================================================
*/

typedef struct _TestClass_MethodProvider_Calc_Add
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint64Field MIReturn;
    /*IN*/ MI_ConstSint64Field Left;
    /*IN*/ MI_ConstSint64Field Right;
    /*OUT*/ MI_ConstSint64Field sum;
}
TestClass_MethodProvider_Calc_Add;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_MethodProvider_Calc_Add_rtti;

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Add_Construct(
    _Inout_ TestClass_MethodProvider_Calc_Add* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_MethodProvider_Calc_Add_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Add_Clone(
    _In_ const TestClass_MethodProvider_Calc_Add* self,
    _Outptr_ TestClass_MethodProvider_Calc_Add** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Add_Destruct(
    _Inout_ TestClass_MethodProvider_Calc_Add* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Add_Delete(
    _Inout_ TestClass_MethodProvider_Calc_Add* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Add_Post(
    _In_ const TestClass_MethodProvider_Calc_Add* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Add_Set_MIReturn(
    _Inout_ TestClass_MethodProvider_Calc_Add* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MIReturn)->value = x;
    ((MI_Uint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Add_Clear_MIReturn(
    _Inout_ TestClass_MethodProvider_Calc_Add* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Add_Set_Left(
    _Inout_ TestClass_MethodProvider_Calc_Add* self,
    _In_ MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->Left)->value = x;
    ((MI_Sint64Field*)&self->Left)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Add_Clear_Left(
    _Inout_ TestClass_MethodProvider_Calc_Add* self)
{
    memset((void*)&self->Left, 0, sizeof(self->Left));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Add_Set_Right(
    _Inout_ TestClass_MethodProvider_Calc_Add* self,
    _In_ MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->Right)->value = x;
    ((MI_Sint64Field*)&self->Right)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Add_Clear_Right(
    _Inout_ TestClass_MethodProvider_Calc_Add* self)
{
    memset((void*)&self->Right, 0, sizeof(self->Right));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Add_Set_sum(
    _Inout_ TestClass_MethodProvider_Calc_Add* self,
    _In_ MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->sum)->value = x;
    ((MI_Sint64Field*)&self->sum)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Add_Clear_sum(
    _Inout_ TestClass_MethodProvider_Calc_Add* self)
{
    memset((void*)&self->sum, 0, sizeof(self->sum));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_MethodProvider_Calc.Subtract()
**
**==============================================================================
*/

typedef struct _TestClass_MethodProvider_Calc_Subtract
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint64Field MIReturn;
    /*IN*/ MI_ConstSint64Field Left;
    /*IN*/ MI_ConstSint64Field Right;
    /*OUT*/ MI_ConstSint64Field difference;
}
TestClass_MethodProvider_Calc_Subtract;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_MethodProvider_Calc_Subtract_rtti;

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Subtract_Construct(
    _Inout_ TestClass_MethodProvider_Calc_Subtract* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_MethodProvider_Calc_Subtract_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Subtract_Clone(
    _In_ const TestClass_MethodProvider_Calc_Subtract* self,
    _Outptr_ TestClass_MethodProvider_Calc_Subtract** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Subtract_Destruct(
    _Inout_ TestClass_MethodProvider_Calc_Subtract* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Subtract_Delete(
    _Inout_ TestClass_MethodProvider_Calc_Subtract* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Subtract_Post(
    _In_ const TestClass_MethodProvider_Calc_Subtract* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Subtract_Set_MIReturn(
    _Inout_ TestClass_MethodProvider_Calc_Subtract* self,
    _In_ MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->MIReturn)->value = x;
    ((MI_Sint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Subtract_Clear_MIReturn(
    _Inout_ TestClass_MethodProvider_Calc_Subtract* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Subtract_Set_Left(
    _Inout_ TestClass_MethodProvider_Calc_Subtract* self,
    _In_ MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->Left)->value = x;
    ((MI_Sint64Field*)&self->Left)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Subtract_Clear_Left(
    _Inout_ TestClass_MethodProvider_Calc_Subtract* self)
{
    memset((void*)&self->Left, 0, sizeof(self->Left));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Subtract_Set_Right(
    _Inout_ TestClass_MethodProvider_Calc_Subtract* self,
    _In_ MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->Right)->value = x;
    ((MI_Sint64Field*)&self->Right)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Subtract_Clear_Right(
    _Inout_ TestClass_MethodProvider_Calc_Subtract* self)
{
    memset((void*)&self->Right, 0, sizeof(self->Right));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Subtract_Set_difference(
    _Inout_ TestClass_MethodProvider_Calc_Subtract* self,
    _In_ MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->difference)->value = x;
    ((MI_Sint64Field*)&self->difference)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Subtract_Clear_difference(
    _Inout_ TestClass_MethodProvider_Calc_Subtract* self)
{
    memset((void*)&self->difference, 0, sizeof(self->difference));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_MethodProvider_Calc.Divide()
**
**==============================================================================
*/

typedef struct _TestClass_MethodProvider_Calc_Divide
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstSint64Field MIReturn;
    /*IN*/ MI_ConstSint64Field Numerator;
    /*IN*/ MI_ConstSint64Field Denominator;
    /*OUT*/ MI_ConstSint64Field quotient;
}
TestClass_MethodProvider_Calc_Divide;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_MethodProvider_Calc_Divide_rtti;

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Divide_Construct(
    _Inout_ TestClass_MethodProvider_Calc_Divide* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_MethodProvider_Calc_Divide_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Divide_Clone(
    _In_ const TestClass_MethodProvider_Calc_Divide* self,
    _Outptr_ TestClass_MethodProvider_Calc_Divide** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Divide_Destruct(
    _Inout_ TestClass_MethodProvider_Calc_Divide* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Divide_Delete(
    _Inout_ TestClass_MethodProvider_Calc_Divide* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Divide_Post(
    _In_ const TestClass_MethodProvider_Calc_Divide* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Divide_Set_MIReturn(
    _Inout_ TestClass_MethodProvider_Calc_Divide* self,
    _In_ MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->MIReturn)->value = x;
    ((MI_Sint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Divide_Clear_MIReturn(
    _Inout_ TestClass_MethodProvider_Calc_Divide* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Divide_Set_Numerator(
    _Inout_ TestClass_MethodProvider_Calc_Divide* self,
    _In_ MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->Numerator)->value = x;
    ((MI_Sint64Field*)&self->Numerator)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Divide_Clear_Numerator(
    _Inout_ TestClass_MethodProvider_Calc_Divide* self)
{
    memset((void*)&self->Numerator, 0, sizeof(self->Numerator));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Divide_Set_Denominator(
    _Inout_ TestClass_MethodProvider_Calc_Divide* self,
    _In_ MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->Denominator)->value = x;
    ((MI_Sint64Field*)&self->Denominator)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Divide_Clear_Denominator(
    _Inout_ TestClass_MethodProvider_Calc_Divide* self)
{
    memset((void*)&self->Denominator, 0, sizeof(self->Denominator));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Divide_Set_quotient(
    _Inout_ TestClass_MethodProvider_Calc_Divide* self,
    _In_ MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->quotient)->value = x;
    ((MI_Sint64Field*)&self->quotient)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Divide_Clear_quotient(
    _Inout_ TestClass_MethodProvider_Calc_Divide* self)
{
    memset((void*)&self->quotient, 0, sizeof(self->quotient));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_MethodProvider_Calc.Multiply()
**
**==============================================================================
*/

typedef struct _TestClass_MethodProvider_Calc_Multiply
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint64Field MIReturn;
    /*IN*/ MI_ConstUint64Field Left;
    /*IN*/ MI_ConstUint64Field Right;
    /*OUT*/ MI_ConstSint64Field product;
}
TestClass_MethodProvider_Calc_Multiply;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_MethodProvider_Calc_Multiply_rtti;

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Multiply_Construct(
    _Inout_ TestClass_MethodProvider_Calc_Multiply* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_MethodProvider_Calc_Multiply_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Multiply_Clone(
    _In_ const TestClass_MethodProvider_Calc_Multiply* self,
    _Outptr_ TestClass_MethodProvider_Calc_Multiply** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Multiply_Destruct(
    _Inout_ TestClass_MethodProvider_Calc_Multiply* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Multiply_Delete(
    _Inout_ TestClass_MethodProvider_Calc_Multiply* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Multiply_Post(
    _In_ const TestClass_MethodProvider_Calc_Multiply* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Multiply_Set_MIReturn(
    _Inout_ TestClass_MethodProvider_Calc_Multiply* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MIReturn)->value = x;
    ((MI_Uint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Multiply_Clear_MIReturn(
    _Inout_ TestClass_MethodProvider_Calc_Multiply* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Multiply_Set_Left(
    _Inout_ TestClass_MethodProvider_Calc_Multiply* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->Left)->value = x;
    ((MI_Uint64Field*)&self->Left)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Multiply_Clear_Left(
    _Inout_ TestClass_MethodProvider_Calc_Multiply* self)
{
    memset((void*)&self->Left, 0, sizeof(self->Left));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Multiply_Set_Right(
    _Inout_ TestClass_MethodProvider_Calc_Multiply* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->Right)->value = x;
    ((MI_Uint64Field*)&self->Right)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Multiply_Clear_Right(
    _Inout_ TestClass_MethodProvider_Calc_Multiply* self)
{
    memset((void*)&self->Right, 0, sizeof(self->Right));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Multiply_Set_product(
    _Inout_ TestClass_MethodProvider_Calc_Multiply* self,
    _In_ MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->product)->value = x;
    ((MI_Sint64Field*)&self->product)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_Multiply_Clear_product(
    _Inout_ TestClass_MethodProvider_Calc_Multiply* self)
{
    memset((void*)&self->product, 0, sizeof(self->product));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_MethodProvider_Calc.AddNumbers()
**
**==============================================================================
*/

typedef struct _TestClass_MethodProvider_Calc_AddNumbers
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
Numbers_ConstRef numbers;
    /*OUT*/ MI_ConstSint64Field sum;
}
TestClass_MethodProvider_Calc_AddNumbers;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_MethodProvider_Calc_AddNumbers_rtti;

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_AddNumbers_Construct(
    _Inout_ TestClass_MethodProvider_Calc_AddNumbers* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_MethodProvider_Calc_AddNumbers_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_AddNumbers_Clone(
    _In_ const TestClass_MethodProvider_Calc_AddNumbers* self,
    _Outptr_ TestClass_MethodProvider_Calc_AddNumbers** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_AddNumbers_Destruct(
    _Inout_ TestClass_MethodProvider_Calc_AddNumbers* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_AddNumbers_Delete(
    _Inout_ TestClass_MethodProvider_Calc_AddNumbers* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_AddNumbers_Post(
    _In_ const TestClass_MethodProvider_Calc_AddNumbers* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_AddNumbers_Set_MIReturn(
    _Inout_ TestClass_MethodProvider_Calc_AddNumbers* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_AddNumbers_Clear_MIReturn(
    _Inout_ TestClass_MethodProvider_Calc_AddNumbers* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_AddNumbers_Set_numbers(
    _Inout_ TestClass_MethodProvider_Calc_AddNumbers* self,
    _In_ const Numbers* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_AddNumbers_SetPtr_numbers(
    _Inout_ TestClass_MethodProvider_Calc_AddNumbers* self,
    _In_ const Numbers* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_AddNumbers_Clear_numbers(
    _Inout_ TestClass_MethodProvider_Calc_AddNumbers* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_AddNumbers_Set_sum(
    _Inout_ TestClass_MethodProvider_Calc_AddNumbers* self,
    _In_ MI_Sint64 x)
{
    ((MI_Sint64Field*)&self->sum)->value = x;
    ((MI_Sint64Field*)&self->sum)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_AddNumbers_Clear_sum(
    _Inout_ TestClass_MethodProvider_Calc_AddNumbers* self)
{
    memset((void*)&self->sum, 0, sizeof(self->sum));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_MethodProvider_Calc.PrimeFactors()
**
**==============================================================================
*/

typedef struct _TestClass_MethodProvider_Calc_PrimeFactors
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint64Field number;
    /*OUT*/ Numbers_ConstRef factors;
}
TestClass_MethodProvider_Calc_PrimeFactors;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_MethodProvider_Calc_PrimeFactors_rtti;

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_PrimeFactors_Construct(
    _Inout_ TestClass_MethodProvider_Calc_PrimeFactors* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_MethodProvider_Calc_PrimeFactors_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_PrimeFactors_Clone(
    _In_ const TestClass_MethodProvider_Calc_PrimeFactors* self,
    _Outptr_ TestClass_MethodProvider_Calc_PrimeFactors** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_PrimeFactors_Destruct(
    _Inout_ TestClass_MethodProvider_Calc_PrimeFactors* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_PrimeFactors_Delete(
    _Inout_ TestClass_MethodProvider_Calc_PrimeFactors* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_PrimeFactors_Post(
    _In_ const TestClass_MethodProvider_Calc_PrimeFactors* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_PrimeFactors_Set_MIReturn(
    _Inout_ TestClass_MethodProvider_Calc_PrimeFactors* self,
    _In_ MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_PrimeFactors_Clear_MIReturn(
    _Inout_ TestClass_MethodProvider_Calc_PrimeFactors* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_PrimeFactors_Set_number(
    _Inout_ TestClass_MethodProvider_Calc_PrimeFactors* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->number)->value = x;
    ((MI_Uint64Field*)&self->number)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_PrimeFactors_Clear_number(
    _Inout_ TestClass_MethodProvider_Calc_PrimeFactors* self)
{
    memset((void*)&self->number, 0, sizeof(self->number));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_PrimeFactors_Set_factors(
    _Inout_ TestClass_MethodProvider_Calc_PrimeFactors* self,
    _In_ const Numbers* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        0);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_PrimeFactors_SetPtr_factors(
    _Inout_ TestClass_MethodProvider_Calc_PrimeFactors* self,
    _In_ const Numbers* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_INSTANCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_PrimeFactors_Clear_factors(
    _Inout_ TestClass_MethodProvider_Calc_PrimeFactors* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

/*
**==============================================================================
**
** TestClass_MethodProvider_Calc.HardError()
**
**==============================================================================
*/

typedef struct _TestClass_MethodProvider_Calc_HardError
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint64Field MIReturn;
    /*IN*/ MI_ConstBooleanField postError;
    /*IN*/ MI_ConstUint16Field perceivedSeverity;
}
TestClass_MethodProvider_Calc_HardError;

MI_EXTERN_C MI_CONST MI_MethodDecl TestClass_MethodProvider_Calc_HardError_rtti;

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_HardError_Construct(
    _Inout_ TestClass_MethodProvider_Calc_HardError* self,
    _In_ MI_Context* context)
{
    return MI_ConstructParameters(context, &TestClass_MethodProvider_Calc_HardError_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_HardError_Clone(
    _In_ const TestClass_MethodProvider_Calc_HardError* self,
    _Outptr_ TestClass_MethodProvider_Calc_HardError** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_HardError_Destruct(
    _Inout_ TestClass_MethodProvider_Calc_HardError* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_HardError_Delete(
    _Inout_ TestClass_MethodProvider_Calc_HardError* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_HardError_Post(
    _In_ const TestClass_MethodProvider_Calc_HardError* self,
    _In_ MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_HardError_Set_MIReturn(
    _Inout_ TestClass_MethodProvider_Calc_HardError* self,
    _In_ MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->MIReturn)->value = x;
    ((MI_Uint64Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_HardError_Clear_MIReturn(
    _Inout_ TestClass_MethodProvider_Calc_HardError* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_HardError_Set_postError(
    _Inout_ TestClass_MethodProvider_Calc_HardError* self,
    _In_ MI_Boolean x)
{
    ((MI_BooleanField*)&self->postError)->value = x;
    ((MI_BooleanField*)&self->postError)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_HardError_Clear_postError(
    _Inout_ TestClass_MethodProvider_Calc_HardError* self)
{
    memset((void*)&self->postError, 0, sizeof(self->postError));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_HardError_Set_perceivedSeverity(
    _Inout_ TestClass_MethodProvider_Calc_HardError* self,
    _In_ MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->perceivedSeverity)->value = x;
    ((MI_Uint16Field*)&self->perceivedSeverity)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL TestClass_MethodProvider_Calc_HardError_Clear_perceivedSeverity(
    _Inout_ TestClass_MethodProvider_Calc_HardError* self)
{
    memset((void*)&self->perceivedSeverity, 0, sizeof(self->perceivedSeverity));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** TestClass_MethodProvider_Calc provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _TestClass_MethodProvider_Calc_Self TestClass_MethodProvider_Calc_Self;

MI_EXTERN_C void MI_CALL TestClass_MethodProvider_Calc_Load(
    _Outptr_result_maybenull_ TestClass_MethodProvider_Calc_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL TestClass_MethodProvider_Calc_Unload(
    _In_opt_ TestClass_MethodProvider_Calc_Self* self,
    _In_ MI_Context* context);

MI_EXTERN_C void MI_CALL TestClass_MethodProvider_Calc_Invoke_Add(
    _In_opt_ TestClass_MethodProvider_Calc_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TestClass_MethodProvider_Calc* instanceName,
    _In_opt_ const TestClass_MethodProvider_Calc_Add* in);

MI_EXTERN_C void MI_CALL TestClass_MethodProvider_Calc_Invoke_Subtract(
    _In_opt_ TestClass_MethodProvider_Calc_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TestClass_MethodProvider_Calc* instanceName,
    _In_opt_ const TestClass_MethodProvider_Calc_Subtract* in);

MI_EXTERN_C void MI_CALL TestClass_MethodProvider_Calc_Invoke_Divide(
    _In_opt_ TestClass_MethodProvider_Calc_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TestClass_MethodProvider_Calc* instanceName,
    _In_opt_ const TestClass_MethodProvider_Calc_Divide* in);

MI_EXTERN_C void MI_CALL TestClass_MethodProvider_Calc_Invoke_Multiply(
    _In_opt_ TestClass_MethodProvider_Calc_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TestClass_MethodProvider_Calc* instanceName,
    _In_opt_ const TestClass_MethodProvider_Calc_Multiply* in);

MI_EXTERN_C void MI_CALL TestClass_MethodProvider_Calc_Invoke_AddNumbers(
    _In_opt_ TestClass_MethodProvider_Calc_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TestClass_MethodProvider_Calc* instanceName,
    _In_opt_ const TestClass_MethodProvider_Calc_AddNumbers* in);

MI_EXTERN_C void MI_CALL TestClass_MethodProvider_Calc_Invoke_PrimeFactors(
    _In_opt_ TestClass_MethodProvider_Calc_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TestClass_MethodProvider_Calc* instanceName,
    _In_opt_ const TestClass_MethodProvider_Calc_PrimeFactors* in);

MI_EXTERN_C void MI_CALL TestClass_MethodProvider_Calc_Invoke_HardError(
    _In_opt_ TestClass_MethodProvider_Calc_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TestClass_MethodProvider_Calc* instanceName,
    _In_opt_ const TestClass_MethodProvider_Calc_HardError* in);


#endif /* _TestClass_MethodProvider_Calc_h */
