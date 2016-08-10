/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#include <MI.h>
#include "Perf_WithPsSemantics.h"
#include "ProviderUtil.h"

struct _Perf_WithPsSemantics_Self
{
    MI_Uint32 maxInstances;
    MI_Uint32 streamInstances;
    MI_Uint32 semanticsFlags;
    MI_Uint32 semanticsCount;
};

MI_Result StreamInstance(MI_Context* context, MI_Instance** arrInstances, MI_Uint32 size)
{
    MI_Result result = MI_RESULT_FAILED;
    MI_Value val;

    if(arrInstances == NULL)
        return result;
    
    if(size > 1)
    {
        val.instancea.data = arrInstances;
        val.instancea.size = size;
    
        result = MI_WriteStreamParameter(context, MI_T("instances"), &val, MI_INSTANCEA, MI_FLAG_STREAM);
    }
    else
    {
        val.instance = *arrInstances;
        result = MI_WriteStreamParameter(context, MI_T("instances"), &val, MI_INSTANCE, MI_FLAG_STREAM);
    }
    
    if(result == MI_RESULT_OK)
    {
        for(MI_Uint32 i = 0 ; i < size; i++)
        {    
            MI_Instance_Destruct(arrInstances[i]);
        }
    }

    return result;
}

void MI_CALL Perf_WithPsSemantics_Load(
    _Outptr_result_maybenull_ Perf_WithPsSemantics_Self** self,
    _In_opt_ MI_Module_Self* selfModule,
    _In_ MI_Context* context)
{
    MI_UNREFERENCED_PARAMETER(selfModule);

    *self = new Perf_WithPsSemantics_Self;

    (*self)->maxInstances = 10;
    (*self)->streamInstances = 0;
    (*self)->semanticsFlags = 0;
    (*self)->semanticsCount = 0;

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Perf_WithPsSemantics_Unload(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context)
{
    if (self)
    {
        self->maxInstances = 10;
        self->streamInstances = 0;
        self->semanticsFlags = 0;
        self->semanticsCount = 0;

        delete self;
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Perf_WithPsSemantics_EnumerateInstances(
    _In_opt_ Perf_WithPsSemantics_Self* self,
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

    if (self)
    {
        Perf_WithPsSemantics instance = {{0}};

        result = Perf_WithPsSemantics_Construct(&instance, context);
        IF_ERROR_POST_RETURN(context, result);

        result = PostPsSemantics(context, self->semanticsFlags, self->semanticsCount);
        IF_ERROR_DESTRUCT_POST_RETURN(context, result, instance.__instance);
    
        for(MI_Uint32 i = 0; i < self->maxInstances; ++i)
        {
            result = FillInstance(context, &instance.__instance, i);
            IF_ERROR_DESTRUCT_POST_RETURN(context, result, instance.__instance);        
            if((result = Perf_WithPsSemantics_Post(&instance, context)) != MI_RESULT_OK)
            {
                break;
            }
        }

        Perf_WithPsSemantics_Destruct(&instance);
    }
    MI_PostResult(context, result);
}

void MI_CALL Perf_WithPsSemantics_GetInstance(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_WithPsSemantics* instanceName,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Result result = MI_RESULT_FAILED;

    if (self)
    {
        Perf_WithPsSemantics instance = {{0}};

        result = Perf_WithPsSemantics_Construct(&instance, context);
        IF_ERROR_POST_RETURN(context, result);
    
        result = PostPsSemantics(context, self->semanticsFlags, self->semanticsCount);
        IF_ERROR_DESTRUCT_POST_RETURN(context, result, instance.__instance);    

        result = FillInstance(context, &instance.__instance, instanceName->v_uint64_key.value);
        IF_ERROR_DESTRUCT_POST_RETURN(context, result, instance.__instance);    

        result = Perf_WithPsSemantics_Post(&instance, context);
        IF_ERROR_DESTRUCT_POST_RETURN(context, result, instance.__instance);

        Perf_WithPsSemantics_Destruct(&instance);
    }

    MI_PostResult(context, result);
}

void MI_CALL Perf_WithPsSemantics_CreateInstance(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_WithPsSemantics* newInstance)
{
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);

    MI_Result result = MI_RESULT_FAILED;

    if (self)
    {
        result = PostPsSemantics(context, self->semanticsFlags, self->semanticsCount);
        IF_ERROR_POST_RETURN(context, result);    

        result = Perf_WithPsSemantics_Post(newInstance, context);
    }

    MI_PostResult(context, result);
}

void MI_CALL Perf_WithPsSemantics_ModifyInstance(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_WithPsSemantics* modifiedInstance,
    _In_opt_ const MI_PropertySet* propertySet)
{
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(propertySet);

    MI_Result result = MI_RESULT_FAILED;

    if (self)
    {
        result = PostPsSemantics(context, self->semanticsFlags, self->semanticsCount);
        IF_ERROR_POST_RETURN(context, result);
    }
    
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Perf_WithPsSemantics_DeleteInstance(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_ const Perf_WithPsSemantics* instanceName)
{
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Result result = MI_RESULT_FAILED;
    
    if (self)
    {
        result = PostPsSemantics(context, self->semanticsFlags, self->semanticsCount);
        IF_ERROR_POST_RETURN(context, result);
    }
    
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Perf_WithPsSemantics_Invoke_SetBehaviour(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Perf_WithPsSemantics* instanceName,
    _In_opt_ const Perf_WithPsSemantics_SetBehaviour* in)
{
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);

    MI_Result result = MI_RESULT_FAILED;

    if (self)
    {
        Perf_WithPsSemantics_SetBehaviour setBehave = {{0}};  
        result = Perf_WithPsSemantics_SetBehaviour_Construct(&setBehave, context);
        IF_ERROR_POST_RETURN(context, result);
    
        self->maxInstances = in->maxInstances.value;
        self->semanticsCount = in->psSemanticsCount.value;
        self->semanticsFlags = in->psSemanticsFlags.value;
        self->streamInstances = in->streamInstances.value;

        result = Perf_WithPsSemantics_SetBehaviour_Set_MIReturn(&setBehave, 0);
        IF_ERROR_DESTRUCT_POST_RETURN(context, result, setBehave.__instance);

        result = Perf_WithPsSemantics_SetBehaviour_Post(&setBehave, context);
        IF_ERROR_DESTRUCT_POST_RETURN(context, result, setBehave.__instance);

        Perf_WithPsSemantics_SetBehaviour_Destruct(&setBehave);
    }
    MI_PostResult(context, result);
}

void MI_CALL Perf_WithPsSemantics_Invoke_PingBackParameters(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Perf_WithPsSemantics* instanceName,
    _In_opt_ const Perf_WithPsSemantics_PingBackParameters* in)
{
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);

    MI_Result result = MI_RESULT_FAILED;

    if (self)
    {
        Perf_WithPsSemantics_PingBackParameters pingBack = {{0}}; 
        result = Perf_WithPsSemantics_PingBackParameters_Construct(&pingBack, context);
        IF_ERROR_POST_RETURN(context, result);
    
        result = Perf_WithPsSemantics_PingBackParameters_Set_outbound(&pingBack, in->inbound.value);
        IF_ERROR_DESTRUCT_POST_RETURN(context, result, pingBack.__instance);    
    
        result = Perf_WithPsSemantics_PingBackParameters_Set_MIReturn(&pingBack, 0);
        IF_ERROR_DESTRUCT_POST_RETURN(context, result, pingBack.__instance);    

        result = PostPsSemantics(context, self->semanticsFlags, self->semanticsCount);
        IF_ERROR_DESTRUCT_POST_RETURN(context, result, pingBack.__instance);    

        result = Perf_WithPsSemantics_PingBackParameters_Post(&pingBack, context);
        IF_ERROR_DESTRUCT_POST_RETURN(context, result, pingBack.__instance);

        Perf_WithPsSemantics_PingBackParameters_Destruct(&pingBack);
    }

    MI_PostResult(context, result);
}

void MI_CALL Perf_WithPsSemantics_Invoke_streamingInstances(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Perf_WithPsSemantics* instanceName,
    _In_opt_ const Perf_WithPsSemantics_streamingInstances* in)
{
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);

    MI_Result result = MI_RESULT_FAILED;
    MI_Uint32 streamBufferCount = 0;
    
    if(self->streamInstances == 0)
    {        
        MI_PostError(context, MI_RESULT_PULL_HAS_BEEN_ABANDONED, MI_RESULT_TYPE_MI, MI_T("The streamInstances has been set to 0"));
        return;
    }

    Perf_WithPsSemantics_streamingInstances streamingInstances = {{0}};  

    result = Perf_WithPsSemantics_streamingInstances_Construct(&streamingInstances, context);
    IF_ERROR_POST_RETURN(context, result);
    
    MI_Instance **arrInstances = new MI_Instance*[self->streamInstances];
    memset(arrInstances, 0, sizeof(MI_Instance*) * self->streamInstances);

    for(MI_Uint32 i = 0; i < self->maxInstances; i++)
    {
        result = MI_NewInstance(context, &Perf_WithPsSemantics_rtti, &arrInstances[streamBufferCount]);
        IF_ERROR_DELETE_ARRAY_POST_RETURN(context, result, streamingInstances.__instance, arrInstances, self->streamInstances);
                
        result = FillInstance(context, arrInstances[streamBufferCount], i);
        IF_ERROR_DELETE_ARRAY_POST_RETURN(context, result, streamingInstances.__instance, arrInstances, self->streamInstances);
        
        if((streamBufferCount >= (self->streamInstances - 1)) || i == (self->maxInstances - 1))
        {    
            result = StreamInstance(context, arrInstances, streamBufferCount + 1);
            IF_ERROR_DELETE_ARRAY_POST_RETURN(context, result, streamingInstances.__instance, arrInstances, self->streamInstances);
            
            // Reset the stream buffer
            for (MI_Uint32 count = 0; count < self->streamInstances; count++)
            {
                MI_Instance_Destruct(arrInstances[count]);
                arrInstances[count] = 0;
            }
            streamBufferCount = 0;
        }
        else
        {
            streamBufferCount++; 
        }        
    }

    if((result = Perf_WithPsSemantics_streamingInstances_Set_MIReturn(&streamingInstances,0)) != MI_RESULT_OK)
    {
        goto CLEANUP_INSTANCE;
    }
    
    if((result = PostPsSemantics(context, self->semanticsFlags, self->semanticsCount)) != MI_RESULT_OK)
    {
        goto CLEANUP_INSTANCE;
    }

    result = Perf_WithPsSemantics_streamingInstances_Post(&streamingInstances,context);

CLEANUP_INSTANCE:
    Perf_WithPsSemantics_streamingInstances_Destruct(&streamingInstances);
    delete[] arrInstances;
    MI_PostResult(context, result);
}

void MI_CALL Perf_WithPsSemantics_Invoke_streamingPrimitive(
    _In_opt_ Perf_WithPsSemantics_Self* self,
    _In_ MI_Context* context,
    _In_opt_z_ const MI_Char* nameSpace,
    _In_opt_z_ const MI_Char* className,
    _In_opt_z_ const MI_Char* methodName,
    _In_ const Perf_WithPsSemantics* instanceName,
    _In_opt_ const Perf_WithPsSemantics_streamingPrimitive* in)
{
    MI_UNREFERENCED_PARAMETER(nameSpace);
    MI_UNREFERENCED_PARAMETER(className);
    MI_UNREFERENCED_PARAMETER(methodName);
    MI_UNREFERENCED_PARAMETER(instanceName);
    MI_UNREFERENCED_PARAMETER(in);

    MI_Result result = MI_RESULT_FAILED;
    
    if (self)
    {
        MI_Uint32 streamBufferCount = 0;
    
        if(self->streamInstances == 0)
        {        
            MI_PostError(context, MI_RESULT_PULL_HAS_BEEN_ABANDONED, MI_RESULT_TYPE_MI, MI_T("The streamInstances has been set to 0"));
            return;
        }

        Perf_WithPsSemantics_streamingPrimitive streamingPrimitives = {{0}};  
        result = Perf_WithPsSemantics_streamingPrimitive_Construct(&streamingPrimitives, context);
        IF_ERROR_POST_RETURN(context, result);
    
        MI_Uint32* arrInt = new MI_Uint32[self->streamInstances];
        MI_Value val;
    
        for(MI_Uint32 i = 0; i < self->maxInstances; i++)
        {
            arrInt[streamBufferCount] = i;

            if((streamBufferCount >= (self->streamInstances - 1)) || i == (self->maxInstances -1))
            {    
                val.uint32a.data = NULL;
                val.uint32a.size = 0;

                if(self->streamInstances > 1)
                {
                    val.uint32a.data = arrInt;
                    val.uint32a.size = streamBufferCount + 1;
                    result = MI_WriteStreamParameter(context, MI_T("numbers"), &val, MI_UINT32A, MI_FLAG_STREAM);
                }
                else
                {
                    val.uint32 = arrInt[0];
                    result = MI_WriteStreamParameter(context, MI_T("numbers"), &val, MI_UINT32, MI_FLAG_STREAM);
                }

                if(result != MI_RESULT_OK)
                {
                    goto CLEANUP_PRIMITIVE;
                }

                streamBufferCount = 0;
            }
            else
            {            
                streamBufferCount++;
            }        
        }

        if((result = Perf_WithPsSemantics_streamingPrimitive_Set_MIReturn(&streamingPrimitives, 0)) != MI_RESULT_OK)
        {
            goto CLEANUP_PRIMITIVE;
        }

        if((result = PostPsSemantics(context, self->semanticsFlags, self->semanticsCount)) != MI_RESULT_OK)
        {
            goto CLEANUP_PRIMITIVE;
        }

        result = Perf_WithPsSemantics_streamingPrimitive_Post(&streamingPrimitives, context);

CLEANUP_PRIMITIVE:
        Perf_WithPsSemantics_streamingPrimitive_Destruct(&streamingPrimitives);
        delete[] arrInt;
    }
    MI_PostResult(context, result);
}

