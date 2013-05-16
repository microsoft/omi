/* @statikgen@ */
#include "MI.h"
#include "NumbersTask.h"
#include <malloc.h>

void MI_CALL NumbersTask_Load(
    NumbersTask_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL NumbersTask_Unload(
    NumbersTask_Self* self,
    MI_Context* context)
{
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL NumbersTask_EnumerateInstances(
    NumbersTask_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL NumbersTask_GetInstance(
    NumbersTask_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const NumbersTask* instanceName,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL NumbersTask_CreateInstance(
    NumbersTask_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const NumbersTask* newInstance)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL NumbersTask_ModifyInstance(
    NumbersTask_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const NumbersTask* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL NumbersTask_DeleteInstance(
    NumbersTask_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const NumbersTask* instanceName)
{
    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL NumbersTask_Invoke_NewNumber(
    NumbersTask_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const NumbersTask* instanceName,
    const NumbersTask_NewNumber* in)
{
	Numbers num;
	Numbers_Construct(&num, context);

	MI_Uint32 count = in->newDigits.value.size;

	MI_Sint64* num_buf = (MI_Sint64*) malloc(sizeof(MI_Sint64) * count);

	for(MI_Uint32 i=0; i < count; i++)
	{
		num_buf[i] = in->newDigits.value.data[i];
	}

	Numbers_Set_count(&num, count);
	Numbers_Set_numbers(&num, num_buf, count);

	NumbersTask_NewNumber newNumTask;
	NumbersTask_NewNumber_Construct(&newNumTask, context);

	NumbersTask_NewNumber_Set_newNum(&newNumTask, &num);
	NumbersTask_NewNumber_Post(&newNumTask, context);

    MI_PostResult(context, MI_RESULT_OK);
}

