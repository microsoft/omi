/* @migen@ */
#include <MI.h>
#include "Perf_NoPsSemantics.h"
#include "ProviderUtil.h"
#include <pal/thread.h>
#include <pal/cpu.h>

struct _Perf_NoPsSemantics_Self
{
    MI_Uint32 maxInstances;
    MI_Uint32 streamInstances;
    MI_Uint32 semanticsFlags;
    MI_Uint32 semanticsCount;
    MI_Boolean enablePostNumberInstances;
    MI_Boolean keepPosting;
    MI_Uint32 numberPostedInstances;
    Perf_NoPsSemantics* preCreatedInstance;
};

struct _Perf_NoPsSemantics_Enumerate_ThreadArgumentStructure
{
    Perf_NoPsSemantics_Self* self;
    MI_Context* context;
};

MI_EXTERN_C PAL_Uint32 THREAD_API EnumerateInstanceThread(void *param)
{    
    MI_Result result = MI_RESULT_FAILED;
    Perf_NoPsSemantics instance = {{0}};
    _In_opt_ Perf_NoPsSemantics_Self* self;
    _In_ MI_Context* context;

    _Perf_NoPsSemantics_Enumerate_ThreadArgumentStructure* args = NULL;

    if(param != NULL)
    {
        args = (_Perf_NoPsSemantics_Enumerate_ThreadArgumentStructure*) param;
    }
    else
    {
        return 0;
    }

    self = args->self;
    context = args->context;

    IF_ERROR_POST_RETURN_WITH_RETURNVALUE(context, Perf_NoPsSemantics_Construct(&instance, context), MI_RESULT_FAILED);

    if (self->enablePostNumberInstances)
    {
        MI_Uint32 i= 0;
        while(self->keepPosting && i<self->maxInstances)
        {
            result = FillInstance(context, &instance.__instance, i);

            IF_ERROR_DESTRUCT_POST_RETURNVALUE(context, result, instance.__instance, MI_RESULT_FAILED);    
            self->numberPostedInstances ++;
            if((result = Perf_NoPsSemantics_Post(&instance, context)) != MI_RESULT_OK)
            {
                break;
            }
            i++;
        }
    }
    else
    {
        for(MI_Uint32 i = 0; i < self->maxInstances; ++i)
        {   
            if(self->preCreatedInstance == NULL)
        {
            result = FillInstance(context, &instance.__instance, i);
            IF_ERROR_DESTRUCT_POST_RETURNVALUE(context, result, instance.__instance, MI_RESULT_FAILED);        
            if((result = Perf_NoPsSemantics_Post(&instance, context)) != MI_RESULT_OK)
            {
                break;
            }
        }
            else
            {
                result = Perf_NoPsSemantics_Set_v_uint64_key(self->preCreatedInstance, i);
                IF_ERROR_POST_RETURN_WITH_RETURNVALUE(context, result, 1);
                if((result = Perf_NoPsSemantics_Post(self->preCreatedInstance, context)) != MI_RESULT_OK)
                {
                    break;
                }    
            }
        }
    }

    Perf_NoPsSemantics_Destruct(&instance);
    MI_PostResult(context, result);

    self->keepPosting = MI_TRUE;
    delete args;
    return 0;
}


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
    (*self)->enablePostNumberInstances = MI_FALSE;
    (*self)->keepPosting = MI_TRUE;
    (*self)->numberPostedInstances = 0;

    Perf_NoPsSemantics temp = {{0}};
    Perf_NoPsSemantics_Construct(&temp, context);
    Perf_NoPsSemantics_Clone(&temp, &(*self)->preCreatedInstance);
    Perf_NoPsSemantics_Destruct(&temp);

    FillInstance(context, &(*self)->preCreatedInstance->__instance, 0);

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Perf_NoPsSemantics_Unload(
    _In_opt_ Perf_NoPsSemantics_Self* self,
    _In_ MI_Context* context)
{
    if (self)
    {
        self->maxInstances = 10;
        self->streamInstances = 0;
        self->semanticsFlags = 0;
        self->semanticsCount = 0;
        self->enablePostNumberInstances = MI_FALSE;
        self->keepPosting = MI_TRUE;
        self->numberPostedInstances = 0;
        Perf_NoPsSemantics_Delete(self->preCreatedInstance);
        delete self;
    }

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


    _Perf_NoPsSemantics_Enumerate_ThreadArgumentStructure *args = new _Perf_NoPsSemantics_Enumerate_ThreadArgumentStructure;

    args->context = context;
    args->self = self;

    Thread_CreateDetached(EnumerateInstanceThread, NULL, args);
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
    Perf_NoPsSemantics instance = {{0}};

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

    if (self)
    {
        Perf_NoPsSemantics_SetBehaviour setBehave = {{0}};  

        result = Perf_NoPsSemantics_SetBehaviour_Construct(&setBehave, context);
        IF_ERROR_POST_RETURN(context, result);
    
        if (in->maxInstances.exists){
            self->maxInstances = in->maxInstances.value;
        }

        if (in->enablePostNumberInstances.exists){
            self->enablePostNumberInstances = in->enablePostNumberInstances.value;
        }

        result = Perf_NoPsSemantics_SetBehaviour_Set_MIReturn(&setBehave, 0);
        IF_ERROR_DESTRUCT_POST_RETURN(context, result, setBehave.__instance);
    
        result = Perf_NoPsSemantics_SetBehaviour_Post(&setBehave, context);

        Perf_NoPsSemantics_SetBehaviour_Destruct(&setBehave);
    }

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

    Perf_NoPsSemantics_PingBackParameters pingBack = {{0}};  

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

void MI_CALL Perf_NoPsSemantics_Invoke_GetNumberPostedInstances(
    _In_opt_ Perf_NoPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Perf_NoPsSemantics* instanceName,
    _In_opt_ const Perf_NoPsSemantics_GetNumberPostedInstances* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    if (self)
    {
        Perf_NoPsSemantics_GetNumberPostedInstances r;
        Perf_NoPsSemantics_GetNumberPostedInstances_Construct(&r, context);

        Perf_NoPsSemantics_GetNumberPostedInstances_Set_MIReturn(&r, 0);
        Perf_NoPsSemantics_GetNumberPostedInstances_Set_numberInstances(&r, self->numberPostedInstances);


        Perf_NoPsSemantics_GetNumberPostedInstances_Post(&r, context);

        Perf_NoPsSemantics_GetNumberPostedInstances_Destruct(&r);

        MI_Context_PostResult(context, MI_RESULT_OK);
        self->enablePostNumberInstances = MI_FALSE;
    
        self->numberPostedInstances = 0;
    }
}


void MI_CALL Perf_NoPsSemantics_Invoke_StopPosting(
    _In_opt_ Perf_NoPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Perf_NoPsSemantics* instanceName,
    _In_opt_ const Perf_NoPsSemantics_StopPosting* in)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    if (self)
    {
        self->keepPosting =MI_FALSE;

        Perf_NoPsSemantics_StopPosting r;
        Perf_NoPsSemantics_StopPosting_Construct(&r,context);
        Perf_NoPsSemantics_StopPosting_Set_MIReturn(&r,0);
        Perf_NoPsSemantics_StopPosting_Post(&r, context);
        Perf_NoPsSemantics_StopPosting_Destruct(&r);
    }

    MI_Context_PostResult(context, MI_RESULT_OK);
}


