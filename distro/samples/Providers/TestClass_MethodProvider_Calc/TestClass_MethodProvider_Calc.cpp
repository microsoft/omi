/* @statikgen@ */
#include "MI.h"
#include <iostream>
#include "TestClass_MethodProvider_Calc.h"
#include "CIM_Error.h"
#include <vector> 
#include <memory>
#include <stdio.h>
#ifdef _MSC_VER
#include <TypeConvertor.h>
#include <ProviderXMLLogger.h>
#include <ProviderFaultReader.h>
#include <StringToMIResult.h>
#include <strsafe.h>
#include <ProviderUtil.h>
#endif
#include <sstream>
#include <algorithm>

#ifdef _MSC_VER
ProviderFaultReader faultReader(L"ProviderFault.txt");
ProviderXMLLogger logger;
std::wstring providerName = L"TestClass_MethodProvider_Calc";
#endif

void MI_CALL TestClass_MethodProvider_Calc_Load(
	TestClass_MethodProvider_Calc_Self** self,
	MI_Module_Self* selfModule,
	MI_Context* context)
{	
	*self = NULL;

	#ifdef _MSC_VER
	MI_Result result;
	if(faultReader.CheckForFaultInjection(ProviderXMLLogger::scope::PROVIDER_LOAD, result)) 
	{
		MI_PostResult(context, result);
		return;
	}
	wchar_t wzProfile[MAX_PATH]; 	

	if(!GetEnvironmentVariable(MI_T("UserProfile"), wzProfile, MAX_PATH))
	{
		MI_PostResult(context, MI_RESULT_FAILED);
		return;
	}
	wstringstream sStream;
	sStream << wzProfile << MI_T("\\");	

	if(!logger.Initialize(sStream.str(), MI_T("TestClass_MethodProvider_Calc_Log.xml"), providerName ))
	{
		MI_PostResult(context, MI_RESULT_ACCESS_DENIED);
		return;
	}
	#endif
	MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL TestClass_MethodProvider_Calc_Unload(
	TestClass_MethodProvider_Calc_Self* self,
	MI_Context* context)
{
	#ifdef _MSC_VER	
	logger.Finish();
	#endif	
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
	TestClass_MethodProvider_Calc_Self* self,
	MI_Context* context,
	const MI_Char* nameSpace,
	const MI_Char* className,
	const MI_Char* methodName,
	const TestClass_MethodProvider_Calc* instanceName,
	const TestClass_MethodProvider_Calc_Add* in)
{

	MI_Result result = MI_RESULT_OK;
	#ifdef _MSC_VER	
	if(faultReader.CheckForFaultInjection(ProviderXMLLogger::scope::INVOKE_METHOD, result)) 
	{
		MI_PostResult(context, result);
		return;
	}
	#endif
	if(in == NULL || in->Left.exists == 0 || in->Right.exists == 0)
	{
		MI_PostError(context, MI_RESULT_INVALID_PARAMETER, MI_RESULT_TYPE_MI, MI_T("In-Parameter \"left\" or \"right\" cannot be null"));
		return;
	}
	
	#ifdef _MSC_VER	
	TypeConvertor convertor;
	wstring tempMsg;
	wstring temp;
	result = MI_WriteMessage(context, 0, MI_T("Starting method Add"));
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		return;
	}


	result = MI_WriteProgress(context, MI_T("Addition"), MI_T("Getting Parameters"), MI_T("Adding Parameters"), 0, 2);
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		return;
	}

	convertor.GetWstr(MI_SINT64, (void *) &in->Left.value, temp);
	tempMsg = MI_T("Got parameter Left as ");
	tempMsg.append(temp);

	result = MI_WriteMessage(context, 0, tempMsg.c_str());	
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		return;
	}

	convertor.GetWstr(MI_SINT64, (void *) &in->Right.value, temp);
	tempMsg = MI_T("Got parameter Right as ");
	tempMsg.append(temp);

	result = MI_WriteMessage(context, 0, tempMsg.c_str());
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		return;
	}

	logger.WriteContext(ProviderXMLLogger::scope::INVOKE_METHOD, &nameSpace, &className, context, NULL);
	logger.WriteMethod(ProviderXMLLogger::scope::INVOKE_METHOD,&methodName);
	
	tempMsg = MI_T("in->Left == ");
	convertor.GetWstr(MI_SINT64, (void *) &in->Left.value, temp);
	tempMsg.append(temp);
	logger.WriteMessage(ProviderXMLLogger::scope::INVOKE_METHOD, tempMsg);

	tempMsg = MI_T("in->Right == ");	
	convertor.GetWstr(MI_SINT64, (void *) &in->Right.value, temp);
	tempMsg.append(temp);
	logger.WriteMessage(ProviderXMLLogger::scope::INVOKE_METHOD, tempMsg);
	#endif
	
	TestClass_MethodProvider_Calc_Add add;
	result = TestClass_MethodProvider_Calc_Add_Construct(&add, context);
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		#ifdef _MSC_VER	
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		#endif
		return;
	}

	TestClass_MethodProvider_Calc_Add_Set_sum(&add, (in->Left.value + in->Right.value));
	
	#ifdef _MSC_VER	
	tempMsg = MI_T("sum == ");	
	MI_Sint64 sum = (in->Left.value + in->Right.value);
	convertor.GetWstr(MI_SINT64, (void *) &sum, temp);
	tempMsg.append(temp);
	logger.WriteMessage(ProviderXMLLogger::scope::INVOKE_METHOD, tempMsg);

	tempMsg = MI_T("Setting parameter sum as ");	
	tempMsg.append(temp);
	result = MI_WriteMessage(context, 0, tempMsg.c_str());	
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		TestClass_MethodProvider_Calc_Add_Destruct(&add);
		return;
	}

	MI_Boolean userIntent;
	MI_Char tempString[MAX_PATH];
	ZeroMemory(tempString, sizeof(MI_Char) * MAX_PATH);

	HRESULT hr = StringCchPrintf(tempString, MAX_PATH, MI_T("Numbers %ld and %ld"), in->Left.value, in->Right.value);
	if(SUCCEEDED(hr))
	{
		//result = MI_PromptUser(context, L"Do you want the addition result?", MI_PROMPTTYPE_NORMAL, &userIntent);
		result = MI_ShouldProcess(context, tempString, MI_T("Add"), &userIntent);
		if(result != MI_RESULT_OK)
		{
			MI_PostResult(context, result);
			logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
			TestClass_MethodProvider_Calc_Add_Destruct(&add);
			return;
		}

		if(userIntent)
		{
			#endif
			TestClass_MethodProvider_Calc_Add_Set_MIReturn(&add, result);
			result = TestClass_MethodProvider_Calc_Add_Post(&add, context);
			if(result != MI_RESULT_OK)
			{
				MI_PostResult(context, result);
				#ifdef _MSC_VER	
				logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
				#endif
				TestClass_MethodProvider_Calc_Add_Destruct(&add);
				return;
			}
			#ifdef _MSC_VER	
		}
		else
		{
			result = MI_RESULT_OK; //user responded as No
		}
	}
	else
	{
		POST_ERROR(context, hr, MI_RESULT_TYPE_HRESULT, MI_T("StringCChPrintf Failed"));
	}

	logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result); 
	#endif
	MI_PostResult(context, result);    
	TestClass_MethodProvider_Calc_Add_Destruct(&add);
}

void MI_CALL TestClass_MethodProvider_Calc_Invoke_Subtract(
	TestClass_MethodProvider_Calc_Self* self,
	MI_Context* context,
	const MI_Char* nameSpace,
	const MI_Char* className,
	const MI_Char* methodName,
	const TestClass_MethodProvider_Calc* instanceName,
	const TestClass_MethodProvider_Calc_Subtract* in)
{
	MI_Result result = MI_RESULT_OK;
	
	#ifdef _MSC_VER	
	if(faultReader.CheckForFaultInjection(ProviderXMLLogger::scope::INVOKE_METHOD, result)) 
	{
		MI_PostResult(context, result);
		return;
	}
	#endif

	if(in == NULL || in->Left.exists == 0 || in->Right.exists == 0)
	{
		MI_PostError(context, MI_RESULT_INVALID_PARAMETER, MI_RESULT_TYPE_MI, MI_T("In-Parameter \"left\" or \"right\" cannot be null"));
		return;
	}

	#ifdef _MSC_VER	
	TypeConvertor convertor;
	wstring tempMsg;
	wstring temp;

	result = MI_WriteMessage(context, 1, MI_T("Starting method Subtract"));
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
	}

	result = MI_WriteProgress(context, MI_T("Subtraction"), MI_T("Getting Parameters"), MI_T("Subtracting Parameters"), 0, 2);

	convertor.GetWstr(MI_SINT64, (void *) &in->Left.value, temp);
	tempMsg = MI_T("Got parameter Left as ");
	tempMsg.append(temp);
	result = MI_WriteMessage(context, 1, tempMsg.c_str());
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		return;
	}
		
	convertor.GetWstr(MI_SINT64, (void *) &in->Right.value, temp);
	tempMsg = MI_T("Got parameter Right as ");
	tempMsg.append(temp);
	result = MI_WriteMessage(context, 1, tempMsg.c_str());
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		return;
	}

	logger.WriteContext(ProviderXMLLogger::scope::INVOKE_METHOD, &nameSpace, &className, context, NULL);
	logger.WriteMethod(ProviderXMLLogger::scope::INVOKE_METHOD,&methodName);
	
	tempMsg = MI_T("in->Left == ");
	convertor.GetWstr(MI_SINT64, (void *) &in->Left.value, temp);
	tempMsg.append(temp);
	logger.WriteMessage(ProviderXMLLogger::scope::INVOKE_METHOD, tempMsg);

	tempMsg = MI_T("in->Right == ");	
	convertor.GetWstr(MI_SINT64, (void *) &in->Right.value, temp);
	tempMsg.append(temp);
	logger.WriteMessage(ProviderXMLLogger::scope::INVOKE_METHOD, tempMsg);
	#endif
	TestClass_MethodProvider_Calc_Subtract sub;
	result = TestClass_MethodProvider_Calc_Subtract_Construct(&sub, context);
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		#ifdef _MSC_VER	
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		#endif
		return;
	}

	TestClass_MethodProvider_Calc_Subtract_Set_difference(&sub, ( in->Left.value - in->Right.value));
	
	#ifdef _MSC_VER	
	tempMsg = MI_T("difference == ");	
	MI_Sint64 diff = (in->Left.value - in->Right.value);
	convertor.GetWstr(MI_SINT64, (void *) &diff, temp);
	tempMsg.append(temp);

	logger.WriteMessage(ProviderXMLLogger::scope::INVOKE_METHOD, tempMsg);

	tempMsg = MI_T("Setting parameter difference as ");
	tempMsg.append(temp);
	result = MI_WriteMessage(context, 1, tempMsg.c_str());

	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		TestClass_MethodProvider_Calc_Subtract_Destruct(&sub);
		return;
	}

	MI_Boolean userIntent;

	result = MI_PromptUser(context, MI_T("Do you want the subtraction result?"), MI_PROMPTTYPE_CRITICAL, &userIntent);
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		TestClass_MethodProvider_Calc_Subtract_Destruct(&sub);
		return;
	}

	if(userIntent)
	{
		#endif
		TestClass_MethodProvider_Calc_Subtract_Set_MIReturn(&sub, result);
		result = TestClass_MethodProvider_Calc_Subtract_Post(&sub, context);
		if(result != MI_RESULT_OK)
		{
			MI_PostResult(context, result);
			#ifdef _MSC_VER	
			logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
			#endif
			TestClass_MethodProvider_Calc_Subtract_Destruct(&sub);
			return;
		}
		#ifdef _MSC_VER	
	}
	else
	{
		result = MI_RESULT_OK;
	}

	logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
	#endif
	
	MI_PostResult(context, result);    
	TestClass_MethodProvider_Calc_Subtract_Destruct(&sub);
}

void MI_CALL TestClass_MethodProvider_Calc_Invoke_Divide(
	TestClass_MethodProvider_Calc_Self* self,
	MI_Context* context,
	const MI_Char* nameSpace,
	const MI_Char* className,
	const MI_Char* methodName,
	const TestClass_MethodProvider_Calc* instanceName,
	const TestClass_MethodProvider_Calc_Divide* in)
{
	MI_Result result = MI_RESULT_OK;
	
	#ifdef _MSC_VER	
	if(faultReader.CheckForFaultInjection(ProviderXMLLogger::scope::INVOKE_METHOD, result)) 
	{
		MI_PostResult(context, result);
		return;
	}
	#endif

	if(in == NULL || in->Denominator.exists == 0 || in->Numerator.exists == 0)
	{
		MI_PostError(context, MI_RESULT_INVALID_PARAMETER, MI_RESULT_TYPE_MI, MI_T("In-Parameter \"Denominator\" or \"Numerator\" cannot be null"));
		return;
	}

	#ifdef _MSC_VER	
	TypeConvertor convertor;
	wstring tempMsg;
	wstring temp;

	result = MI_WriteMessage(context, 2, MI_T("Starting method Divide"));
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		return;
	}

	result = MI_WriteProgress(context, MI_T("Division"), MI_T("Getting Parameters"), MI_T("Dividing Parameters"), 0, 2);

	tempMsg = MI_T("Got parameter Numerator as ");
	convertor.GetWstr(MI_SINT64, (void *) &in->Numerator.value, temp);
	tempMsg.append(temp);
	result = MI_WriteMessage(context, 2, tempMsg.c_str());
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		return;
	}

	tempMsg = MI_T("Got parameter Denominator as ");
	convertor.GetWstr(MI_SINT64, (void *) &in->Denominator.value, temp);
	tempMsg.append(temp);
	result = MI_WriteMessage(context, 2, tempMsg.c_str());

	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		return;
	}

	logger.WriteContext(ProviderXMLLogger::scope::INVOKE_METHOD, &nameSpace, &className, context, NULL);
	logger.WriteMethod(ProviderXMLLogger::scope::INVOKE_METHOD,&methodName);
	
	tempMsg = MI_T("in->Numerator == ");
	convertor.GetWstr(MI_SINT64, (void *) &in->Numerator.value, temp);
	tempMsg.append(temp);
	logger.WriteMessage(ProviderXMLLogger::scope::INVOKE_METHOD, tempMsg);

	tempMsg = MI_T("in->Denominator == ");	
	convertor.GetWstr(MI_SINT64, (void *) &in->Denominator.value, temp);
	tempMsg.append(temp);
	logger.WriteMessage(ProviderXMLLogger::scope::INVOKE_METHOD, tempMsg);
	#endif

	TestClass_MethodProvider_Calc_Divide div;
	result = TestClass_MethodProvider_Calc_Divide_Construct(&div, context);
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		#ifdef _MSC_VER	
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		#endif
		return;
	}

	TestClass_MethodProvider_Calc_Divide_Set_quotient(&div, ( in->Numerator.value / in->Denominator.value));

	#ifdef _MSC_VER	
	tempMsg = MI_T("quotient == ");	
	MI_Sint64 quotient = ( in->Numerator.value / in->Denominator.value);
	convertor.GetWstr(MI_SINT64, (void *) &quotient, temp);
	tempMsg.append(temp);

	logger.WriteMessage(ProviderXMLLogger::scope::INVOKE_METHOD, tempMsg);

	tempMsg = MI_T("Setting parameter quotient as ");
	tempMsg.append(temp);
	result = MI_WriteMessage(context, 2, tempMsg.c_str());
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		TestClass_MethodProvider_Calc_Divide_Destruct(&div);
		return;
	}

	MI_Boolean userIntent;
	result = MI_PromptUser(context, MI_T("Do you want the division result?"), MI_PROMPTTYPE_NORMAL, &userIntent);
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		TestClass_MethodProvider_Calc_Divide_Destruct(&div);
		return;
	}

	if(userIntent)
	{
		#endif
		TestClass_MethodProvider_Calc_Divide_Set_MIReturn(&div, result);
		result = TestClass_MethodProvider_Calc_Divide_Post(&div, context);
		if(result != MI_RESULT_OK)
		{
			MI_PostResult(context, result);
			#ifdef _MSC_VER	
			logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
			#endif
			TestClass_MethodProvider_Calc_Divide_Destruct(&div);
			return;
		}
		#ifdef _MSC_VER	
	}
	else
	{
		result = MI_RESULT_OK;
	}	
	logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
	#endif
	MI_PostResult(context, result);    	
	TestClass_MethodProvider_Calc_Divide_Destruct(&div);
}

void MI_CALL TestClass_MethodProvider_Calc_Invoke_Multiply(
	TestClass_MethodProvider_Calc_Self* self,
	MI_Context* context,
	const MI_Char* nameSpace,
	const MI_Char* className,
	const MI_Char* methodName,
	const TestClass_MethodProvider_Calc* instanceName,
	const TestClass_MethodProvider_Calc_Multiply* in)
{
	MI_Result result = MI_RESULT_OK;
	
	#ifdef _MSC_VER	
	if(faultReader.CheckForFaultInjection(ProviderXMLLogger::scope::INVOKE_METHOD, result)) 
	{
		MI_PostResult(context, result);
		return;
	}
	#endif

	if(in == NULL || in->Left.exists == 0 || in->Right.exists == 0)
	{
		MI_PostError(context, MI_RESULT_INVALID_PARAMETER, MI_RESULT_TYPE_MI, MI_T("In-Parameter \"Denominator\" or \"Numerator\" cannot be null"));
		return;
	}

	#ifdef _MSC_VER	
	TypeConvertor convertor;
	wstring tempMsg;
	wstring temp;

	result = MI_WriteMessage(context, 2, MI_T(" Starting method Multiply"));
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		return;
	}

	result = MI_WriteProgress(context, MI_T("Multiplication"), MI_T("Getting Parameters"), MI_T("Multiplying Parameters"), 0, 2);

	tempMsg = MI_T(" Got parameter Left as ") + in->Left.value;

	result = MI_WriteMessage(context, 2, tempMsg.c_str());
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		return;
	}

	tempMsg = MI_T(" Got parameter Right as ") + in->Right.value;
	result = MI_WriteMessage(context, 2, tempMsg.c_str());

	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		return;
	}

	logger.WriteContext(ProviderXMLLogger::scope::INVOKE_METHOD, &nameSpace, &className, context, NULL);
	logger.WriteMethod(ProviderXMLLogger::scope::INVOKE_METHOD,&methodName);
	
	tempMsg = MI_T("in->Left == ");
	convertor.GetWstr(MI_SINT64, (void *) &in->Left.value, temp);
	tempMsg.append(temp);
	logger.WriteMessage(ProviderXMLLogger::scope::INVOKE_METHOD, tempMsg);

	tempMsg = MI_T("in->Right == ");	
	convertor.GetWstr(MI_SINT64, (void *) &in->Right.value, temp);
	tempMsg.append(temp);
	logger.WriteMessage(ProviderXMLLogger::scope::INVOKE_METHOD, tempMsg);
	#endif

	TestClass_MethodProvider_Calc_Multiply mult;
	result = TestClass_MethodProvider_Calc_Multiply_Construct(&mult, context);
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		#ifdef _MSC_VER	
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		#endif
		return;
	}

	TestClass_MethodProvider_Calc_Multiply_Set_product(&mult, ( in->Left.value * in->Right.value));

	#ifdef _MSC_VER	
	tempMsg = MI_T("product == ");	
	MI_Sint64 quotient = ( in->Left.value * in->Right.value);
	convertor.GetWstr(MI_SINT64, (void *) &quotient, temp);
	tempMsg.append(temp);

	logger.WriteMessage(ProviderXMLLogger::scope::INVOKE_METHOD, tempMsg);

	tempMsg = MI_T(" Setting parameter product as ");
	tempMsg.append(temp);
	result = MI_WriteMessage(context, 2, tempMsg.c_str());
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		TestClass_MethodProvider_Calc_Multiply_Destruct(&mult);
		return;
	}

	MI_Boolean userIntent;

	result = MI_PromptUser(context, MI_T("Do you want the multiplication result?"), MI_PROMPTTYPE_CRITICAL, &userIntent);
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		TestClass_MethodProvider_Calc_Multiply_Destruct(&mult);
		return;
	}

	if(userIntent)
	{
		#endif
		TestClass_MethodProvider_Calc_Multiply_Set_MIReturn(&mult, result);
		result = TestClass_MethodProvider_Calc_Multiply_Post(&mult, context);
		if(result != MI_RESULT_OK)
		{
			MI_PostResult(context, result);
			#ifdef _MSC_VER	
			logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
			#endif
			TestClass_MethodProvider_Calc_Multiply_Destruct(&mult);
			return;
		}
		#ifdef _MSC_VER	
	}
	else
	{
		result = MI_RESULT_OK;
	}

	logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
	#endif
	MI_PostResult(context, result);    	
	TestClass_MethodProvider_Calc_Multiply_Destruct(&mult);
}

void MI_CALL TestClass_MethodProvider_Calc_Invoke_AddNumbers(
	TestClass_MethodProvider_Calc_Self* self,
	MI_Context* context,
	const MI_Char* nameSpace,
	const MI_Char* className,
	const MI_Char* methodName,
	const TestClass_MethodProvider_Calc* instanceName,
	const TestClass_MethodProvider_Calc_AddNumbers* in)
{
	MI_Result result = MI_RESULT_OK;
	#ifdef _MSC_VER	
	if(faultReader.CheckForFaultInjection(ProviderXMLLogger::scope::INVOKE_METHOD, result)) 
	{
		MI_PostResult(context, result);
		return;
	}
	#endif

	if(in == NULL || in->numbers.exists == 0)
	{
		MI_PostError(context, MI_RESULT_INVALID_PARAMETER, MI_RESULT_TYPE_MI, MI_T("In-Parameter \"numbers\" cannot be null"));
		return;
	}

	#ifdef _MSC_VER	
	TypeConvertor convertor;
	wstring tempMsg;
	wstring temp;

	result = MI_WriteMessage(context, 2, MI_T(" Starting method AddNumbers"));
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		return;
	}

	result = MI_WriteProgress(context, MI_T("AddNumbers"), MI_T("Getting Parameters"), MI_T("Adding Numbers"), 0, 2);

	tempMsg = MI_T(" Got parameters as");

	logger.WriteContext(ProviderXMLLogger::scope::INVOKE_METHOD, &nameSpace, &className, context, NULL);
	logger.WriteMethod(ProviderXMLLogger::scope::INVOKE_METHOD,&methodName);
	#endif
	MI_Uint32 count = in->numbers.value->count.value;
	const Numbers* inParams = in->numbers.value;
	#ifdef _MSC_VER	
	for(MI_Uint32 i = 0; i < count; i++)
	{
		tempMsg.append(MI_T(" "));
		wstring temp;
		convertor.GetWstr(MI_SINT64, (void*) &inParams->numbers.value.data[i], temp);
		tempMsg.append(temp);
	}

	result = MI_WriteMessage(context, 2, tempMsg.c_str());
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		return;
	}
	#endif

	TestClass_MethodProvider_Calc_AddNumbers addNum;
	result = TestClass_MethodProvider_Calc_AddNumbers_Construct(&addNum, context);
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		#ifdef _MSC_VER	
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		#endif
		return;
	}

	MI_Sint64 sum = 0;
	for(MI_Uint32 i = 0; i < count; i++)
	{
		#ifdef _MSC_VER	
		tempMsg = MI_T("in->numbers[");
		convertor.GetWstr(MI_UINT32, (void *) &i, temp);	
		tempMsg.append(temp);
		tempMsg.append(MI_T("] =="));

		convertor.GetWstr(MI_SINT64, (void *) &inParams->numbers.value.data[i], temp);	
		tempMsg.append(temp);
		logger.WriteMessage(ProviderXMLLogger::scope::INVOKE_METHOD, tempMsg);
		#endif
		sum += inParams->numbers.value.data[i];
	}
	TestClass_MethodProvider_Calc_AddNumbers_Set_sum(&addNum, sum);
	
	#ifdef _MSC_VER	
	tempMsg = MI_T("sum == ");		
	convertor.GetWstr(MI_SINT64, (void *) &sum, temp);
	tempMsg.append(temp);
	logger.WriteMessage(ProviderXMLLogger::scope::INVOKE_METHOD, tempMsg);

	tempMsg = MI_T(" Setting parameter sum as ");
	tempMsg.append(temp);
	result = MI_WriteMessage(context, 2, tempMsg.c_str());
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		TestClass_MethodProvider_Calc_AddNumbers_Destruct(&addNum);
		return;
	}

	MI_Boolean userIntent;
	result = MI_PromptUser(context, MI_T("Do you want the multiplication result?"), MI_PROMPTTYPE_CRITICAL, &userIntent);
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		TestClass_MethodProvider_Calc_AddNumbers_Destruct(&addNum);
		return;
	}

	if(userIntent)
	{
		#endif
		result = TestClass_MethodProvider_Calc_AddNumbers_Set_MIReturn(&addNum, result);
		if(result != MI_RESULT_OK)
		{
			MI_PostResult(context, result);
			#ifdef _MSC_VER	
			logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
			#endif
			TestClass_MethodProvider_Calc_AddNumbers_Destruct(&addNum);
			return;
		}

		result = TestClass_MethodProvider_Calc_AddNumbers_Post(&addNum, context);
		if(result != MI_RESULT_OK)
		{
			MI_PostResult(context, result);
			#ifdef _MSC_VER	
			logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
			#endif
			TestClass_MethodProvider_Calc_AddNumbers_Destruct(&addNum);
			return;
		}
		#ifdef _MSC_VER	
	}
	else
	{	
		result = MI_RESULT_OK;
	}

	logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
	#endif
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
	TestClass_MethodProvider_Calc_Self* self,
	MI_Context* context,
	const MI_Char* nameSpace,
	const MI_Char* className,
	const MI_Char* methodName,
	const TestClass_MethodProvider_Calc* instanceName,
	const TestClass_MethodProvider_Calc_PrimeFactors* in)
{
	std::vector<MI_Sint64> primeFactors;
	MI_Result result = MI_RESULT_OK;
	
	#ifdef _MSC_VER
	if(faultReader.CheckForFaultInjection(ProviderXMLLogger::scope::INVOKE_METHOD, result)) 
	{
		MI_PostResult(context, result);
		return;
	}
	#endif

	if(in == NULL || in->number.exists == 0)
	{
		MI_PostError(context, MI_RESULT_INVALID_PARAMETER, MI_RESULT_TYPE_MI, MI_T("In-Parameter \"number\" cannot be null"));
		return;
	}

	#ifdef _MSC_VER
	TypeConvertor convertor;
	wstring tempMsg;
	wstring temp;

	logger.WriteContext(ProviderXMLLogger::scope::INVOKE_METHOD, &nameSpace, &className, context, NULL);
	logger.WriteMethod(ProviderXMLLogger::scope::INVOKE_METHOD,&methodName);

	result = MI_WriteMessage(context, 0, MI_T("Starting method PrimeFactors"));
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		return;
	}
	
	tempMsg = MI_T("in->number == ");
	convertor.GetWstr(MI_UINT64, (void *) &in->number.value, temp);
	tempMsg.append(temp);
	logger.WriteMessage(ProviderXMLLogger::scope::INVOKE_METHOD, tempMsg);

	tempMsg = MI_T("Got parameter number as ");
	tempMsg.append(temp);

	result = MI_WriteMessage(context, 1, tempMsg.c_str());
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		return;
	}

	result = MI_WriteMessage(context, 2, MI_T("Starting calculation"));
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		return;
	}
	#endif
	
	factors(in->number.value, 2, primeFactors);
	TestClass_MethodProvider_Calc_PrimeFactors primeFac;
	result = TestClass_MethodProvider_Calc_PrimeFactors_Construct(&primeFac, context);
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		#ifdef _MSC_VER
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		#endif
		return;
	}
	
	Numbers fac;
	result = Numbers_Construct(&fac, context);
	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		#ifdef _MSC_VER
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		#endif
		TestClass_MethodProvider_Calc_PrimeFactors_Destruct(&primeFac);
		return;
	}

	#ifdef _MSC_VER
	MI_Value val;
	MI_Result operationOptionResult = MI_Context_GetCustomOption(context, MI_T("TEST_SET_NAMESPACE"), NULL, &val);
	if(operationOptionResult == MI_RESULT_OK)
	{
		operationOptionResult = MI_Instance_SetNameSpace(&fac.__instance, nameSpace);
		if(operationOptionResult != MI_RESULT_OK)
		{
			MI_PostError(context, operationOptionResult, MI_RESULT_TYPE_MI, MI_T("Cannot set Namespace on Numbers instance"));
			logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), operationOptionResult);
			Numbers_Destruct(&fac);
			TestClass_MethodProvider_Calc_PrimeFactors_Destruct(&primeFac);
			return;
		}
	}
	#endif

	fac.count.value = primeFactors.size();
	fac.count.exists = MI_TRUE;
	fac.numbers.value.size = primeFactors.size();
	MI_Sint64* answer;
	answer = (MI_Sint64 *) malloc (sizeof (MI_Sint64) * primeFactors.size());

	for(MI_Uint64 i=0; i < primeFactors.size(); i++)
	{
		#ifdef _MSC_VER
		tempMsg = MI_T("factors[");
		convertor.GetWstr(MI_UINT32, (void *) &i, temp);	
		tempMsg.append(temp);
		tempMsg.append(MI_T("] == "));

		convertor.GetWstr(MI_SINT64, (void *) &primeFactors[i], temp);	
		tempMsg.append(temp);
		logger.WriteMessage(ProviderXMLLogger::scope::INVOKE_METHOD, tempMsg);
		#endif
		answer[i] = primeFactors[i];
	}

	fac.numbers.value.data = answer;
	fac.numbers.exists = MI_TRUE;

	TestClass_MethodProvider_Calc_PrimeFactors_Set_factors(&primeFac, &fac);
	TestClass_MethodProvider_Calc_PrimeFactors_Set_MIReturn(&primeFac, result);
	result = TestClass_MethodProvider_Calc_PrimeFactors_Post(&primeFac, context);

	free(answer); 
	Numbers_Destruct(&fac);

	if(result != MI_RESULT_OK)
	{
		MI_PostResult(context, result);
		#ifdef _MSC_VER
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		#endif
		TestClass_MethodProvider_Calc_PrimeFactors_Destruct(&primeFac);
		return;
	}
	#ifdef _MSC_VER
	logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
	#endif
	
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
	#ifdef _MSC_VER	
	logger.WriteContext(ProviderXMLLogger::scope::INVOKE_METHOD, &nameSpace, &className, context, NULL);
	logger.WriteMethod(ProviderXMLLogger::scope::INVOKE_METHOD, &methodName);
	#endif

	MI_Result result = MI_RESULT_OK;
	
	#ifdef _MSC_VER	
	if(faultReader.CheckForFaultInjection(ProviderXMLLogger::scope::INVOKE_METHOD, result)) 
	{
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		MI_PostResult(context, result);
		return;
	}

	if (result != MI_RESULT_OK)
	{
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), result);
		MI_PostResult(context, result);
		return;
	}
	#endif

	if (in->postError.value)
	{
		CIM_Error error;
		CIM_Error_Construct(&error, context);

		CIM_Error_Set_PerceivedSeverity(&error, in->perceivedSeverity.value);

		CIM_Error_Set_Message(&error, MI_T("Hard error message"));
		CIM_Error_Set_CIMStatusCode(&error, 1);
		CIM_Error_Set_ErrorType(&error, 3);
		CIM_Error_Set_MessageID(&error, MI_T("HardError"));

		//MI_PostResultWithError(context, MI_RESULT_FAILED, &(error.__instance));
		MI_Context_PostCimError(context, &(error.__instance)); 
	}
	else
	{
		TestClass_MethodProvider_Calc_HardError hardError;
		TestClass_MethodProvider_Calc_HardError_Construct(&hardError, context);
		TestClass_MethodProvider_Calc_HardError_Set_MIReturn(&hardError, 0);\
		MI_PostInstance(context, &(hardError.__instance));
		#ifdef _MSC_VER	
		logger.WriteResult(ProviderXMLLogger::scope::INVOKE_METHOD, MI_T("Posting MI_Result == "), MI_RESULT_OK);
		#endif
		MI_PostResult(context, MI_RESULT_OK);
		TestClass_MethodProvider_Calc_HardError_Destruct(&hardError);
	}
}

