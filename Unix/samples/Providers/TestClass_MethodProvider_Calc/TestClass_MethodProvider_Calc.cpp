/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @statikgen@ */
#include "MI.h"
#include <iostream>
#include "TestClass_MethodProvider_Calc.h"
#include "CIM_Error.h"
#include <vector> 
#include <memory>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <pal/palcommon.h>

void MI_CALL TestClass_MethodProvider_Calc_Load(
    _Outptr_result_maybenull_ TestClass_MethodProvider_Calc_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{    
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestClass_MethodProvider_Calc_Unload(
    _In_opt_ TestClass_MethodProvider_Calc_Self* self,
    _In_ MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestClass_MethodProvider_Calc_EnumerateInstances(
    TestClass_MethodProvider_Calc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TestClass_MethodProvider_Calc_GetInstance(
    TestClass_MethodProvider_Calc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_MethodProvider_Calc* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TestClass_MethodProvider_Calc_CreateInstance(
    TestClass_MethodProvider_Calc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_MethodProvider_Calc* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TestClass_MethodProvider_Calc_ModifyInstance(
    TestClass_MethodProvider_Calc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_MethodProvider_Calc* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TestClass_MethodProvider_Calc_DeleteInstance(
    TestClass_MethodProvider_Calc_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const TestClass_MethodProvider_Calc* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL TestClass_MethodProvider_Calc_Invoke_Add(
    _In_opt_ TestClass_MethodProvider_Calc_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TestClass_MethodProvider_Calc* instanceName,
    _In_opt_ const TestClass_MethodProvider_Calc_Add* in)
{

    MI_Result result = MI_RESULT_OK;

    if(in == NULL || in->Left.exists == 0 || in->Right.exists == 0)
    {
        MI_PostError(context, MI_RESULT_INVALID_PARAMETER, MI_RESULT_TYPE_MI, MI_T("In-Parameter \"left\" or \"right\" cannot be null"));
        return;
    }
    
    TestClass_MethodProvider_Calc_Add add = {{0}};
    result = TestClass_MethodProvider_Calc_Add_Construct(&add, context);
    if(result != MI_RESULT_OK)
    {
        MI_PostResult(context, result);
        return;
    }

    TestClass_MethodProvider_Calc_Add_Set_sum(&add, (in->Left.value + in->Right.value));
    
            TestClass_MethodProvider_Calc_Add_Set_MIReturn(&add, result);
            result = TestClass_MethodProvider_Calc_Add_Post(&add, context);
            if(result != MI_RESULT_OK)
            {
                MI_PostResult(context, result);
                TestClass_MethodProvider_Calc_Add_Destruct(&add);
                return;
            }

    MI_PostResult(context, result);    
    TestClass_MethodProvider_Calc_Add_Destruct(&add);
}

void MI_CALL TestClass_MethodProvider_Calc_Invoke_Subtract(
    _In_opt_ TestClass_MethodProvider_Calc_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TestClass_MethodProvider_Calc* instanceName,
    _In_opt_ const TestClass_MethodProvider_Calc_Subtract* in)
{
    MI_Result result = MI_RESULT_OK;
    
    if(in == NULL || in->Left.exists == 0 || in->Right.exists == 0)
    {
        MI_PostError(context, MI_RESULT_INVALID_PARAMETER, MI_RESULT_TYPE_MI, MI_T("In-Parameter \"left\" or \"right\" cannot be null"));
        return;
    }

    TestClass_MethodProvider_Calc_Subtract sub = {{0}};
    result = TestClass_MethodProvider_Calc_Subtract_Construct(&sub, context);
    if(result != MI_RESULT_OK)
    {
        MI_PostResult(context, result);
        return;
    }

    TestClass_MethodProvider_Calc_Subtract_Set_difference(&sub, ( in->Left.value - in->Right.value));
    
        TestClass_MethodProvider_Calc_Subtract_Set_MIReturn(&sub, result);
        result = TestClass_MethodProvider_Calc_Subtract_Post(&sub, context);
        if(result != MI_RESULT_OK)
        {
            MI_PostResult(context, result);
            TestClass_MethodProvider_Calc_Subtract_Destruct(&sub);
            return;
        }
    
    MI_PostResult(context, result);    
    TestClass_MethodProvider_Calc_Subtract_Destruct(&sub);
}

void MI_CALL TestClass_MethodProvider_Calc_Invoke_Divide(
    _In_opt_ TestClass_MethodProvider_Calc_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TestClass_MethodProvider_Calc* instanceName,
    _In_opt_ const TestClass_MethodProvider_Calc_Divide* in)
{
    MI_Result result = MI_RESULT_OK;
    
    if(in == NULL || in->Denominator.exists == 0 || in->Numerator.exists == 0)
    {
        MI_PostError(context, MI_RESULT_INVALID_PARAMETER, MI_RESULT_TYPE_MI, MI_T("In-Parameter \"Denominator\" or \"Numerator\" cannot be null"));
        return;
    }

    TestClass_MethodProvider_Calc_Divide div = {{0}};
    result = TestClass_MethodProvider_Calc_Divide_Construct(&div, context);
    if(result != MI_RESULT_OK)
    {
        MI_PostResult(context, result);
        return;
    }

    TestClass_MethodProvider_Calc_Divide_Set_quotient(&div, ( in->Numerator.value / in->Denominator.value));

        TestClass_MethodProvider_Calc_Divide_Set_MIReturn(&div, result);
        result = TestClass_MethodProvider_Calc_Divide_Post(&div, context);
        if(result != MI_RESULT_OK)
        {
            MI_PostResult(context, result);
            TestClass_MethodProvider_Calc_Divide_Destruct(&div);
            return;
        }
    MI_PostResult(context, result);        
    TestClass_MethodProvider_Calc_Divide_Destruct(&div);
}

void MI_CALL TestClass_MethodProvider_Calc_Invoke_Multiply(
    _In_opt_ TestClass_MethodProvider_Calc_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TestClass_MethodProvider_Calc* instanceName,
    _In_opt_ const TestClass_MethodProvider_Calc_Multiply* in)
{
    MI_Result result = MI_RESULT_OK;
    
    if(in == NULL || in->Left.exists == 0 || in->Right.exists == 0)
    {
        MI_PostError(context, MI_RESULT_INVALID_PARAMETER, MI_RESULT_TYPE_MI, MI_T("In-Parameter \"Denominator\" or \"Numerator\" cannot be null"));
        return;
    }

    TestClass_MethodProvider_Calc_Multiply mult = {{0}};
    result = TestClass_MethodProvider_Calc_Multiply_Construct(&mult, context);
    if(result != MI_RESULT_OK)
    {
        MI_PostResult(context, result);
        return;
    }

    TestClass_MethodProvider_Calc_Multiply_Set_product(&mult, ( in->Left.value * in->Right.value));

        TestClass_MethodProvider_Calc_Multiply_Set_MIReturn(&mult, result);
        result = TestClass_MethodProvider_Calc_Multiply_Post(&mult, context);
        if(result != MI_RESULT_OK)
        {
            MI_PostResult(context, result);
            TestClass_MethodProvider_Calc_Multiply_Destruct(&mult);
            return;
        }
    MI_PostResult(context, result);        
    TestClass_MethodProvider_Calc_Multiply_Destruct(&mult);
}

void MI_CALL TestClass_MethodProvider_Calc_Invoke_AddNumbers(
    _In_opt_ TestClass_MethodProvider_Calc_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TestClass_MethodProvider_Calc* instanceName,
    _In_opt_ const TestClass_MethodProvider_Calc_AddNumbers* in)
{
    MI_Result result = MI_RESULT_OK;

    if(in == NULL || in->numbers.exists == 0)
    {
        MI_PostError(context, MI_RESULT_INVALID_PARAMETER, MI_RESULT_TYPE_MI, MI_T("In-Parameter \"numbers\" cannot be null"));
        return;
    }


    MI_Uint32 count = in->numbers.value->count.value;
    const Numbers* inParams = in->numbers.value;

    TestClass_MethodProvider_Calc_AddNumbers addNum = {{0}};
    result = TestClass_MethodProvider_Calc_AddNumbers_Construct(&addNum, context);
    if(result != MI_RESULT_OK)
    {
        MI_PostResult(context, result);
        return;
    }

    MI_Sint64 sum = 0;
    for(MI_Uint32 i = 0; i < count; i++)
    {
        sum += inParams->numbers.value.data[i];
    }
    TestClass_MethodProvider_Calc_AddNumbers_Set_sum(&addNum, sum);
    
        result = TestClass_MethodProvider_Calc_AddNumbers_Set_MIReturn(&addNum, result);
        if(result != MI_RESULT_OK)
        {
            MI_PostResult(context, result);
            TestClass_MethodProvider_Calc_AddNumbers_Destruct(&addNum);
            return;
        }

        result = TestClass_MethodProvider_Calc_AddNumbers_Post(&addNum, context);
        if(result != MI_RESULT_OK)
        {
            MI_PostResult(context, result);
            TestClass_MethodProvider_Calc_AddNumbers_Destruct(&addNum);
            return;
        }

    MI_PostResult(context, result);        
    TestClass_MethodProvider_Calc_AddNumbers_Destruct(&addNum);
}

bool isPrime(MI_Sint64 number)
{
    for(MI_Sint64 i=2; i <= number / 2; i++)
    {
        if(number % i == 0)
            return false;
    }

    return true;
}

void factors(MI_Uint64 number, MI_Uint64 iteration, std::vector<MI_Sint64> &primeFactors)
{
    if(number % iteration == 0)
    {
        if(isPrime(iteration))
            primeFactors.push_back(iteration);
    }

    if(number == iteration)
        return;

    factors(number, iteration+1, primeFactors);
}


void MI_CALL TestClass_MethodProvider_Calc_Invoke_PrimeFactors(
    _In_opt_ TestClass_MethodProvider_Calc_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TestClass_MethodProvider_Calc* instanceName,
    _In_opt_ const TestClass_MethodProvider_Calc_PrimeFactors* in)
{
    std::vector<MI_Sint64> primeFactors;
    MI_Result result = MI_RESULT_OK;
    
    if(in == NULL || in->number.exists == 0)
    {
        MI_PostError(context, MI_RESULT_INVALID_PARAMETER, MI_RESULT_TYPE_MI, MI_T("In-Parameter \"number\" cannot be null"));
        return;
    }

    factors(in->number.value, 2, primeFactors);
    TestClass_MethodProvider_Calc_PrimeFactors primeFac = {{0}};
    result = TestClass_MethodProvider_Calc_PrimeFactors_Construct(&primeFac, context);
    if(result != MI_RESULT_OK)
    {
        MI_PostResult(context, result);
        return;
    }
    
    Numbers fac = {{0}};
    result = Numbers_Construct(&fac, context);
    if(result != MI_RESULT_OK)
    {
        MI_PostResult(context, result);
        TestClass_MethodProvider_Calc_PrimeFactors_Destruct(&primeFac);
        return;
    }
        
    MI_Sint64* answer;
    answer = (MI_Sint64 *) PAL_Malloc(sizeof (MI_Sint64) * primeFactors.size());

    for(MI_Uint64 i=0; i < primeFactors.size(); i++)
    {
        answer[i] = primeFactors[i];
    }

    Numbers_Set_count(&fac, primeFactors.size());
    Numbers_Set_numbers(&fac, answer, primeFactors.size());

    TestClass_MethodProvider_Calc_PrimeFactors_Set_factors(&primeFac, &fac);
    TestClass_MethodProvider_Calc_PrimeFactors_Set_MIReturn(&primeFac, result);
    result = TestClass_MethodProvider_Calc_PrimeFactors_Post(&primeFac, context);

    PAL_Free(answer); 
    Numbers_Destruct(&fac);

    if(result != MI_RESULT_OK)
    {
        MI_PostResult(context, result);
        TestClass_MethodProvider_Calc_PrimeFactors_Destruct(&primeFac);
        return;
    }
    
    MI_PostResult(context, result);        
    TestClass_MethodProvider_Calc_PrimeFactors_Destruct(&primeFac);
}

MI_EXTERN_C void MI_CALL TestClass_MethodProvider_Calc_Invoke_HardError(
    _In_opt_ TestClass_MethodProvider_Calc_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const TestClass_MethodProvider_Calc* instanceName,
    _In_opt_ const TestClass_MethodProvider_Calc_HardError* in)
{   
    if (in->postError.value)
    {
        CIM_Error error = {{0}};
        CIM_Error_Construct(&error, context);

        CIM_Error_Set_PerceivedSeverity(&error, in->perceivedSeverity.value);

        CIM_Error_Set_Message(&error, MI_T("Hard error message"));
        CIM_Error_Set_CIMStatusCode(&error, 1);
        CIM_Error_Set_ErrorType(&error, 3);
        CIM_Error_Set_MessageID(&error, MI_T("HardError"));

        MI_Context_PostCimError(context, &(error.__instance)); 
    }
    else
    {
        TestClass_MethodProvider_Calc_HardError hardError = {{0}};
        TestClass_MethodProvider_Calc_HardError_Construct(&hardError, context);
        TestClass_MethodProvider_Calc_HardError_Set_MIReturn(&hardError, 0);\
        MI_PostInstance(context, &(hardError.__instance));
        
        MI_PostResult(context, MI_RESULT_OK);
        TestClass_MethodProvider_Calc_HardError_Destruct(&hardError);
    }
}

