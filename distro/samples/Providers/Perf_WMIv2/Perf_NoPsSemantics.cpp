/* @migen@ */
#include <MI.h>
#include "Perf_NoPsSemantics.h"
#include "ProviderUtil.h"

struct _Perf_NoPsSemantics_Self
{
	MI_Uint32 maxInstances;
	MI_Uint32 streamInstances;
	MI_Uint32 semanticsFlags;
	MI_Uint32 semanticsCount;
};

void MI_CALL Perf_NoPsSemantics_Load(
	_Outptr_result_maybenull_ Perf_NoPsSemantics_Self** self,
	_In_opt_ MI_Module_Self* selfModule,
	_In_ MI_Context* context)
{
	MI_UNREFERENCED_PARAMETER(selfModule);

	*self = new Perf_NoPsSemantics_Self;

	(*self)->maxInstances = 10;
	(*self)->streamInstances = 0;
	(*self)->semanticsFlags = 0;
	(*self)->semanticsCount = 0;

	MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Perf_NoPsSemantics_Unload(
	_In_opt_ Perf_NoPsSemantics_Self* self,
	_In_ MI_Context* context)
{
	self->maxInstances = 10;
	self->streamInstances = 0;
	self->semanticsFlags = 0;
	self->semanticsCount = 0;

	delete self;

	MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Perf_NoPsSemantics_EnumerateInstances(
	_In_opt_ Perf_NoPsSemantics_Self* self,
	_In_ MI_Context* context,
	_In_opt_z_ const MI_Char* nameSpace,
	_In_opt_z_ const MI_Char* className,
	_In_opt_ const MI_PropertySet* propertySet,
	_In_ MI_Boolean keysOnly,
	_In_opt_ const MI_Filter* filter)
{
	MI_UNREFERENCED_PARAMETER(nameSpace);
	MI_UNREFERENCED_PARAMETER(className);
	MI_UNREFERENCED_PARAMETER(propertySet);
	MI_UNREFERENCED_PARAMETER(keysOnly);
	MI_UNREFERENCED_PARAMETER(filter);

	MI_Result result = MI_RESULT_FAILED;
	Perf_NoPsSemantics instance;

	IF_ERROR_POST_RETURN(context, Perf_NoPsSemantics_Construct(&instance, context));

	for(MI_Uint32 i = 0; i < self->maxInstances; ++i)
	{
		result = FillInstance(context, &instance.__instance, i);
		IF_ERROR_DESTRUCT_POST_RETURN(context, result, instance.__instance);		
		if((result = Perf_NoPsSemantics_Post(&instance, context)) != MI_RESULT_OK)
		{
			break;
		}
	}

	Perf_NoPsSemantics_Destruct(&instance);
	MI_PostResult(context, result);
}

void MI_CALL Perf_NoPsSemantics_GetInstance(
	_In_opt_ Perf_NoPsSemantics_Self* self,
	_In_ MI_Context* context,
	_In_opt_z_ const MI_Char* nameSpace,
	_In_opt_z_ const MI_Char* className,
	_In_ const Perf_NoPsSemantics* instanceName,
	_In_opt_ const MI_PropertySet* propertySet)
{
	MI_UNREFERENCED_PARAMETER(self);
	MI_UNREFERENCED_PARAMETER(nameSpace);
	MI_UNREFERENCED_PARAMETER(className);
	MI_UNREFERENCED_PARAMETER(propertySet);

	MI_Result result = MI_RESULT_FAILED;
	Perf_NoPsSemantics instance;

	result = Perf_NoPsSemantics_Construct(&instance, context);
	IF_ERROR_POST_RETURN(context, result);
	
	result = FillInstance(context, &instance.__instance, instanceName->v_uint64_key.value);
	IF_ERROR_DESTRUCT_POST_RETURN(context, result, instance.__instance);
	
	result = Perf_NoPsSemantics_Post(&instance, context);
	Perf_NoPsSemantics_Destruct(&instance);
	MI_PostResult(context, result);
}

void MI_CALL Perf_NoPsSemantics_CreateInstance(
	_In_opt_ Perf_NoPsSemantics_Self* self,
	_In_ MI_Context* context,
	_In_opt_z_ const MI_Char* nameSpace,
	_In_opt_z_ const MI_Char* className,
	_In_ const Perf_NoPsSemantics* newInstance)
{
	MI_UNREFERENCED_PARAMETER(self);
	MI_UNREFERENCED_PARAMETER(nameSpace);
	MI_UNREFERENCED_PARAMETER(className);
	
	MI_Result result = MI_RESULT_FAILED;
	result = Perf_NoPsSemantics_Post(newInstance, context);
	MI_PostResult(context, result);
}

void MI_CALL Perf_NoPsSemantics_ModifyInstance(
	_In_opt_ Perf_NoPsSemantics_Self* self,
	_In_ MI_Context* context,
	_In_opt_z_ const MI_Char* nameSpace,
	_In_opt_z_ const MI_Char* className,
	_In_ const Perf_NoPsSemantics* modifiedInstance,
	_In_opt_ const MI_PropertySet* propertySet)
{
	MI_UNREFERENCED_PARAMETER(self);
	MI_UNREFERENCED_PARAMETER(nameSpace);
	MI_UNREFERENCED_PARAMETER(className);
	MI_UNREFERENCED_PARAMETER(propertySet);

	MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Perf_NoPsSemantics_DeleteInstance(
	_In_opt_ Perf_NoPsSemantics_Self* self,
	_In_ MI_Context* context,
	_In_opt_z_ const MI_Char* nameSpace,
	_In_opt_z_ const MI_Char* className,
	_In_ const Perf_NoPsSemantics* instanceName)
{
	MI_UNREFERENCED_PARAMETER(self);
	MI_UNREFERENCED_PARAMETER(nameSpace);
	MI_UNREFERENCED_PARAMETER(className);
	MI_UNREFERENCED_PARAMETER(instanceName);

	MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Perf_NoPsSemantics_Invoke_SetBehaviour(
	_In_opt_ Perf_NoPsSemantics_Self* self,
	_In_ MI_Context* context,
	_In_opt_z_ const MI_Char* nameSpace,
	_In_opt_z_ const MI_Char* className,
	_In_opt_z_ const MI_Char* methodName,
	_In_ const Perf_NoPsSemantics* instanceName,
	_In_opt_ const Perf_NoPsSemantics_SetBehaviour* in)
{
	MI_UNREFERENCED_PARAMETER(nameSpace);
	MI_UNREFERENCED_PARAMETER(className);
	MI_UNREFERENCED_PARAMETER(methodName);
	MI_UNREFERENCED_PARAMETER(instanceName);
	
	MI_Result result = MI_RESULT_FAILED;

	Perf_NoPsSemantics_SetBehaviour setBehave;  

	result = Perf_NoPsSemantics_SetBehaviour_Construct(&setBehave, context);
	IF_ERROR_POST_RETURN(context, result);
	
	self->maxInstances = in->maxInstances.value;

	result = Perf_NoPsSemantics_SetBehaviour_Set_MIReturn(&setBehave, 0);
	IF_ERROR_DESTRUCT_POST_RETURN(context, result, setBehave.__instance);
	
	result = Perf_NoPsSemantics_SetBehaviour_Post(&setBehave, context);

	Perf_NoPsSemantics_SetBehaviour_Destruct(&setBehave);
	MI_PostResult(context, result);
}

void MI_CALL Perf_NoPsSemantics_Invoke_PingBackParameters(
	_In_opt_ Perf_NoPsSemantics_Self* self,
	_In_ MI_Context* context,
	_In_opt_z_ const MI_Char* nameSpace,
	_In_opt_z_ const MI_Char* className,
	_In_opt_z_ const MI_Char* methodName,
	_In_ const Perf_NoPsSemantics* instanceName,
	_In_opt_ const Perf_NoPsSemantics_PingBackParameters* in)
{
	MI_UNREFERENCED_PARAMETER(self);
	MI_UNREFERENCED_PARAMETER(nameSpace);
	MI_UNREFERENCED_PARAMETER(className);
	MI_UNREFERENCED_PARAMETER(methodName);
	
	MI_Result result = MI_RESULT_FAILED;

	Perf_NoPsSemantics_PingBackParameters pingBack;  

	result = Perf_NoPsSemantics_PingBackParameters_Construct(&pingBack, context);
	IF_ERROR_POST_RETURN(context, result);
	
	result = Perf_NoPsSemantics_PingBackParameters_Set_outbound(&pingBack, in->inbound.value);
	IF_ERROR_DESTRUCT_POST_RETURN(context, result, pingBack.__instance);
	
	result = Perf_NoPsSemantics_PingBackParameters_Set_MIReturn(&pingBack, 0);
	IF_ERROR_DESTRUCT_POST_RETURN(context, result, pingBack.__instance);
	
	result = Perf_NoPsSemantics_PingBackParameters_Post(&pingBack, context);
	Perf_NoPsSemantics_PingBackParameters_Destruct(&pingBack);
	MI_PostResult(context, result);
}

void MI_CALL Perf_NoPsSemantics_Invoke_streamingInstances(
	_In_opt_ Perf_NoPsSemantics_Self* self,
	_In_ MI_Context* context,
	_In_opt_z_ const MI_Char* nameSpace,
	_In_opt_z_ const MI_Char* className,
	_In_opt_z_ const MI_Char* methodName,
	_In_ const Perf_NoPsSemantics* instanceName,
	_In_opt_ const Perf_NoPsSemantics_streamingInstances* in)
{
	MI_UNREFERENCED_PARAMETER(self);
	MI_UNREFERENCED_PARAMETER(nameSpace);
	MI_UNREFERENCED_PARAMETER(className);
	MI_UNREFERENCED_PARAMETER(methodName);
	MI_UNREFERENCED_PARAMETER(instanceName);
	MI_UNREFERENCED_PARAMETER(in);
	
	MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL Perf_NoPsSemantics_Invoke_streamingPrimitive(
	_In_opt_ Perf_NoPsSemantics_Self* self,
	_In_ MI_Context* context,
	_In_opt_z_ const MI_Char* nameSpace,
	_In_opt_z_ const MI_Char* className,
	_In_opt_z_ const MI_Char* methodName,
	_In_ const Perf_NoPsSemantics* instanceName,
	_In_opt_ const Perf_NoPsSemantics_streamingPrimitive* in)
{
	MI_UNREFERENCED_PARAMETER(self);
	MI_UNREFERENCED_PARAMETER(nameSpace);
	MI_UNREFERENCED_PARAMETER(className);
	MI_UNREFERENCED_PARAMETER(methodName);
	MI_UNREFERENCED_PARAMETER(instanceName);
	MI_UNREFERENCED_PARAMETER(in);

	MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

