/* @migen@ */
#include <MI.h>
#include "StressTestClass99.h"

void MI_CALL StressTestClass99_Load(
    _Outptr_result_maybenull_ StressTestClass99_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = NULL;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL StressTestClass99_Unload(
    _In_opt_ StressTestClass99_Self* self,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(self);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL StressTestClass99_EnumerateInstances(
    _In_opt_ StressTestClass99_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter)
{
    MI_Result result = MI_RESULT_FAILED;
    StressTestClass99 tempInstance;
    unsigned int i = 0;

    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(propertySet);
    MI_UNREFERENCED_PARAMETER(keysOnly);
    MI_UNREFERENCED_PARAMETER(filter);

    for(i=0; i < 100; i++)
    {
        result = StressTestClass99_Construct(&tempInstance, context);    
        if(result != MI_RESULT_OK)
        {
            MI_Context_PostError(context, result, MI_RESULT_TYPE_MI, MI_T("Construct"));
            return;
        }

        result = StressTestClass99_Set_someKey0(&tempInstance, i);
        if(result != MI_RESULT_OK)
        {
            MI_Context_PostError(context, result, MI_RESULT_TYPE_MI, MI_T("Set"));
            return;
        }

        result = StressTestClass99_Post(&tempInstance, context);
        if(result != MI_RESULT_OK)
        {
            MI_Context_PostError(context, result, MI_RESULT_TYPE_MI, MI_T("Post"));
            return;
        }                

        result = StressTestClass99_Destruct(&tempInstance);    
        if(result != MI_RESULT_OK)
        {
            MI_Context_PostError(context, result, MI_RESULT_TYPE_MI, MI_T("Destruct"));
            return;
        }
        
        MI_Context_WriteVerbose(context, MI_T("Hello from StressTestClass99 Enumerate"));
    }        


    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL StressTestClass99_GetInstance(
    _In_opt_ StressTestClass99_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass99* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL StressTestClass99_CreateInstance(
    _In_opt_ StressTestClass99_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass99* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL StressTestClass99_ModifyInstance(
    _In_opt_ StressTestClass99_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass99* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL StressTestClass99_DeleteInstance(
    _In_opt_ StressTestClass99_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass99* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

