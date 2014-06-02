/* @migen@ */
#include <MI.h>
#include "PerfAssocClass.h"
#include "ProviderUtil.h"

void MI_CALL PerfAssocClass_Load(
    _Outptr_result_maybenull_ PerfAssocClass_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = NULL;
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL PerfAssocClass_Unload(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(self);

    MI_PostResult(context, MI_RESULT_OK);
}

// We will be testing only the worst case, which is falling back to EnumerateInstances
void MI_CALL PerfAssocClass_EnumerateInstances(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(propertySet);
    MI_UNREFERENCED_PARAMETER(keysOnly);
    MI_UNREFERENCED_PARAMETER(filter);

    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
    /*
    MI_Result result = MI_RESULT_FAILED;
    MI_Result resultWithSemantics = MI_RESULT_FAILED;
    MI_Result resultNoSemantics = MI_RESULT_FAILED;

    MI_Session session;
    IF_ERROR_POST_RETURN(context, MI_GetLocalSession(context, &session));

    MI_Operation operationWithSemantics;
    MI_Operation operationNoSemantics;

    MI_Session_EnumerateInstances(&session, 0, NULL, nameSpace, MI_T("Perf_WithPsSemantics"), MI_FALSE, NULL, &operationWithSemantics);
    MI_Session_EnumerateInstances(&session, 0, NULL, nameSpace, MI_T("Perf_NoPsSemantics"), MI_FALSE, NULL, &operationNoSemantics);

    const MI_Instance* resultInstanceWithSemantics = NULL;
    const MI_Instance* resultInstanceNoSemantics= NULL;

    MI_Boolean moreResultsWithSemantics = MI_FALSE;
    MI_Boolean moreResultsNoSemantics = MI_FALSE;

    PerfAssocClass assocClass; 
    if(PerfAssocClass_Construct(&assocClass, context) == MI_RESULT_OK)
    {
        do
        {
            MI_Operation_GetInstance(&operationWithSemantics, &resultInstanceWithSemantics, &moreResultsWithSemantics, &resultWithSemantics, NULL, NULL);
            MI_Operation_GetInstance(&operationNoSemantics, &resultInstanceNoSemantics, &moreResultsNoSemantics, &resultNoSemantics, NULL, NULL);

            IF_ERROR_BREAK((result = resultWithSemantics));
            IF_ERROR_BREAK((result = resultNoSemantics));

            IF_ERROR_BREAK((result = PerfAssocClass_Set_antecedent(&assocClass, (Perf_WithPsSemantics *) resultInstanceWithSemantics)));        
            IF_ERROR_BREAK((result = PerfAssocClass_Set_dependent(&assocClass, (Perf_NoPsSemantics *) resultInstanceNoSemantics)));
            IF_ERROR_BREAK((result = PerfAssocClass_Post(&assocClass, context)));

        } while(moreResultsNoSemantics && moreResultsWithSemantics);

        PerfAssocClass_Destruct(&assocClass);
    }

    MI_Operation_Close(&operationNoSemantics);
    MI_Operation_Close(&operationWithSemantics);

    MI_PostResult(context, result);*/
}

void MI_CALL PerfAssocClass_GetInstance(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const PerfAssocClass* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Result result = MI_RESULT_FAILED;

    result = PerfAssocClass_Post(instanceName, context);
    MI_PostResult(context, result);
}

void MI_CALL PerfAssocClass_CreateInstance(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const PerfAssocClass* newInstance)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(newInstance);

    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL PerfAssocClass_ModifyInstance(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const PerfAssocClass* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(modifiedInstance);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL PerfAssocClass_DeleteInstance(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const PerfAssocClass* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL PerfAssocClass_AssociatorInstancesantecedent(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_WithPsSemantics* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(resultClass);
    MI_UNREFERENCED_PARAMETER(propertySet);
    MI_UNREFERENCED_PARAMETER(keysOnly);
    MI_UNREFERENCED_PARAMETER(filter);

    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);
}

void MI_CALL PerfAssocClass_AssociatorInstancesdependent(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_NoPsSemantics* instanceName,
    _In_z_ const MI_Char* resultClass,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(resultClass);
    MI_UNREFERENCED_PARAMETER(propertySet);
    MI_UNREFERENCED_PARAMETER(keysOnly);
    MI_UNREFERENCED_PARAMETER(filter);

    MI_PostResult(context, MI_RESULT_NOT_SUPPORTED);    
}

void MI_CALL PerfAssocClass_ReferenceInstancesantecedent(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_WithPsSemantics* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(propertySet);
    MI_UNREFERENCED_PARAMETER(keysOnly);
    MI_UNREFERENCED_PARAMETER(filter);

    if(instanceName == NULL || instanceName->v_uint64_key.exists == MI_FALSE)
    {
        IF_ERROR_POST_RETURN(context, MI_RESULT_INVALID_QUERY);
    }

    Perf_NoPsSemantics referencedInstance = {{0}};
    MI_Result result = Perf_NoPsSemantics_Construct(&referencedInstance, context);
    IF_ERROR_POST_RETURN(context, result);

    result = FillInstance(context, &referencedInstance.__instance, instanceName->v_uint64_key.value);
    IF_ERROR_POST_RETURN(context,result);

    PerfAssocClass association = {{0}}; 
    result = PerfAssocClass_Construct(&association, context);
    IF_ERROR_POST_RETURN(context, result);

    result = PerfAssocClass_Set_antecedent(&association, instanceName);
    IF_ERROR_POST_RETURN(context, result);

    result = PerfAssocClass_Set_dependent(&association, &referencedInstance);
    IF_ERROR_POST_RETURN(context, result);

    result = PerfAssocClass_Post(&association, context);
    IF_ERROR_POST_RETURN(context, result);

    result = Perf_NoPsSemantics_Destruct(&referencedInstance);
    IF_ERROR_POST_RETURN(context, result);

    result = PerfAssocClass_Destruct(&association);
    IF_ERROR_POST_RETURN(context, result);

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL PerfAssocClass_ReferenceInstancesdependent(
    _In_opt_ PerfAssocClass_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_NoPsSemantics* instanceName,
    _In_opt_ const MI_PropertySet* propertySet,
    _In_ MI_Boolean keysOnly,
    _In_opt_ const MI_Filter* filter)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(propertySet);
    MI_UNREFERENCED_PARAMETER(keysOnly);
    MI_UNREFERENCED_PARAMETER(filter);

    if(instanceName == NULL || instanceName->v_uint64_key.exists == MI_FALSE)
    {
        IF_ERROR_POST_RETURN(context, MI_RESULT_INVALID_QUERY);
    }

    Perf_WithPsSemantics referencedInstance = {{0}};
    MI_Result result = Perf_WithPsSemantics_Construct(&referencedInstance, context);
    IF_ERROR_POST_RETURN(context, result);

    result = FillInstance(context, &referencedInstance.__instance, instanceName->v_uint64_key.value);
    IF_ERROR_POST_RETURN(context,result);

    PerfAssocClass association = {{0}}; 
    result = PerfAssocClass_Construct(&association, context);
    IF_ERROR_POST_RETURN(context, result);

    result = PerfAssocClass_Set_antecedent(&association, &referencedInstance);
    IF_ERROR_POST_RETURN(context, result);

    result = PerfAssocClass_Set_dependent(&association, instanceName);
    IF_ERROR_POST_RETURN(context, result);

    result = PerfAssocClass_Post(&association, context);
    IF_ERROR_POST_RETURN(context, result);

    result = Perf_WithPsSemantics_Destruct(&referencedInstance);
    IF_ERROR_POST_RETURN(context, result);

    result = PerfAssocClass_Destruct(&association);
    IF_ERROR_POST_RETURN(context, result);

    MI_PostResult(context, MI_RESULT_OK);
}

