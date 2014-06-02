/* @migen@ */
#include <MI.h>
#include "StressTestClass0.h"

void MI_CALL StressTestClass0_Load(
    _Outptr_result_maybenull_ StressTestClass0_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = NULL;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL StressTestClass0_Unload(
    _In_opt_ StressTestClass0_Self* self,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(self);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL StressTestClass0_EnumerateInstances(
    _In_opt_ StressTestClass0_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter)
{
    MI_Result result = MI_RESULT_FAILED;
    StressTestClass0 tempInstance;    
    unsigned int i = 0;

    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(propertySet);
    MI_UNREFERENCED_PARAMETER(keysOnly);
    MI_UNREFERENCED_PARAMETER(filter);

    for(i=0; i < 100; i++)
    {
        result = StressTestClass0_Construct(&tempInstance, context);    
        if(result != MI_RESULT_OK)
        {
            MI_Context_PostError(context, result, MI_RESULT_TYPE_MI, MI_T("Construct"));
            return;
        }

        result = StressTestClass0_Set_someKey0(&tempInstance, i);
        if(result != MI_RESULT_OK)
        {
            MI_Context_PostError(context, result, MI_RESULT_TYPE_MI, MI_T("Set"));
            return;
        }

        result = StressTestClass0_Post(&tempInstance, context);
        if(result != MI_RESULT_OK)
        {
            MI_Context_PostError(context, result, MI_RESULT_TYPE_MI, MI_T("Post"));
            return;
        }                

        result = StressTestClass0_Destruct(&tempInstance);    
        if(result != MI_RESULT_OK)
        {
            MI_Context_PostError(context, result, MI_RESULT_TYPE_MI, MI_T("Destruct"));
            return;
        }
        
        MI_Context_WriteVerbose(context, MI_T("Hello from StressTestClass0 Enumerate"));
    }

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL StressTestClass0_GetInstance(
    _In_opt_ StressTestClass0_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass0* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL StressTestClass0_CreateInstance(
    _In_opt_ StressTestClass0_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass0* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL StressTestClass0_ModifyInstance(
    _In_opt_ StressTestClass0_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass0* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL StressTestClass0_DeleteInstance(
    _In_opt_ StressTestClass0_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const StressTestClass0* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Context_PostResult(context, MI_RESULT_OK);
}

