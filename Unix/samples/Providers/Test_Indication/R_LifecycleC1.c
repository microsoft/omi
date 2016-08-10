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
#include "R_LifecycleC1.h"
#include "impl.h"

void MI_CALL _R_LifecycleC1_Callback(
    _In_ MI_Uint32 types,
    _In_opt_ void* callbackData)
{
    Config* config = (Config*)callbackData;
    config->currentSubscriptionTypes = types;
    /* signal firing thread to fire indication */
    Sem_Post(&config->sem, 1);
}

void MI_CALL R_LifecycleC1_Load(
    R_LifecycleC1_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r;
    *self = NULL;    
    {
        // Save lifecycle instance to config
        R_LifecycleC1 lifecycle;
        cfgR_LifecycleC1.lifecycleInstance = NULL;
        r = R_LifecycleC1_Construct(&lifecycle, context);
        CHKMIRESULTPOST(r,"R_LifecycleC1_Construct");
        CHKMIRESULTPOST(R_LifecycleC1_Set_key(&lifecycle, MI_T("R_LifecycleC1")), "R_LifecycleC1_Set_key");
        CHKMIRESULTPOST(R_LifecycleC1_Set_value(&lifecycle, 0), "R_LifecycleC1_Set_value");

        cfgR_LifecycleC1.supportedSubscriptionTypes = (MI_LIFECYCLE_INDICATION_READ | MI_LIFECYCLE_INDICATION_METHODCALL); 

        // Lifecycle indication load
        r = lifecycle_Load(&cfgR_LifecycleC1, (MI_Instance*)&lifecycle, _R_LifecycleC1_Callback, context);
        CHKMIRESULTPOST(r, "lifecycle_Load");

        // Regular class load
        r = class_Load((void**)self, &cfgR_LifecycleC1, NULL);
        CHKMIRESULTPOST(r, "class_Load");

        r = R_LifecycleC1_Destruct(&lifecycle);
        CHKMIRESULTPOST(r, "R_LifecycleC1_Destruct");
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC1_Unload(
    R_LifecycleC1_Self* self,
    MI_Context* context)
{
    CHKMIRESULTPOST(lifecycle_StopThread(&cfgR_LifecycleC1), "R_LifecycleC1_Unload");
    CHKMIRESULTPOST(lifecycle_Unload(&cfgR_LifecycleC1), "lifecycle_Unload(R_LifecycleC1)");
    CHKMIRESULTPOST(class_Unload((void*)self, &cfgR_LifecycleC1), "R_LifecycleC1_Unload");
    if (cfgR_LifecycleC1.lifecycleInstance)
    {
        MI_Instance_Delete( cfgR_LifecycleC1.lifecycleInstance );
        cfgR_LifecycleC1.lifecycleInstance = NULL;
    }
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC1_EnumerateInstances(
    R_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    CHKMIRESULTPOST(R_LifecycleC1_Post((R_LifecycleC1*)cfgR_LifecycleC1.lifecycleInstance, context), "R_LifecycleC1_Post");
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgR_LifecycleC1, MI_LIFECYCLE_INDICATION_READ, cfgR_LifecycleC1.lifecycleInstance, NULL, NULL), "lifecycle_AddEventToQueue"); 
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC1_GetInstance(
    R_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_LifecycleC1* instanceName,
    const MI_PropertySet* propertySet)
{
    CHKMIRESULTPOST(R_LifecycleC1_Post((R_LifecycleC1*)cfgR_LifecycleC1.lifecycleInstance, context), "R_LifecycleC1_Post");
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgR_LifecycleC1, MI_LIFECYCLE_INDICATION_READ, cfgR_LifecycleC1.lifecycleInstance, NULL, NULL), "lifecycle_AddEventToQueue");
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC1_CreateInstance(
    R_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_LifecycleC1* newInstance)
{
    CHKMIRESULTPOST(R_LifecycleC1_Post(newInstance, context), "R_LifecycleC1_Post");
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgR_LifecycleC1, MI_LIFECYCLE_INDICATION_CREATE, cfgR_LifecycleC1.lifecycleInstance, NULL, NULL), "lifecycle_AddEventToQueue");
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC1_ModifyInstance(
    R_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_LifecycleC1* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    
    CHKMIRESULTPOST(R_LifecycleC1_Post(modifiedInstance, context), "R_LifecycleC1_Post");
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgR_LifecycleC1, MI_LIFECYCLE_INDICATION_MODIFY, (MI_Instance*)modifiedInstance, cfgR_LifecycleC1.lifecycleInstance, NULL), "lifecycle_AddEventToQueue");
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC1_DeleteInstance(
    R_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_LifecycleC1* instanceName)
{
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgR_LifecycleC1, MI_LIFECYCLE_INDICATION_DELETE, cfgR_LifecycleC1.lifecycleInstance, NULL, NULL), "lifecycle_AddEventToQueue");
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC1_Invoke_ThreadControl(
    R_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_LifecycleC1* instanceName,
    const R_LifecycleC1_ThreadControl* in)
{
    R_LifecycleC1_ThreadControl outParams;
    
    CHKMIRESULTPOST(lifecycle_ThreadControl(&cfgR_LifecycleC1, in->operation.value), "R_LifecycleC1_ThreadControl");

    CHKMIRESULTPOST(R_LifecycleC1_ThreadControl_Construct( &outParams, context ), "R_LifecycleC1_ThreadControl_Construct");
    CHKMIRESULTPOST(R_LifecycleC1_ThreadControl_Set_MIReturn( &outParams, MI_RESULT_OK ), "R_LifecycleC1_ThreadControl_Set_MIReturn");
    CHKMIRESULTPOST(R_LifecycleC1_ThreadControl_Post( &outParams, context ), "R_LifecycleC1_ThreadControl_Post");
    CHKMIRESULTPOST(R_LifecycleC1_ThreadControl_Destruct( &outParams ), "R_LifecycleC1_ThreadControl_Destruct");
    
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC1_Invoke_GenericMethod(
    R_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_LifecycleC1* instanceName,
    const R_LifecycleC1_GenericMethod* in)
{
    R_LifecycleC1_GenericMethod outParams;

    CHKMIRESULTPOST(lifecycle_InvokeMethod(&cfgR_LifecycleC1), "R_LifecycleC1_GenericMethod");

    CHKMIRESULTPOST(R_LifecycleC1_GenericMethod_Construct( &outParams, context ), "R_LifecycleC1_GenericMethod_Construct");
    CHKMIRESULTPOST(R_LifecycleC1_GenericMethod_Set_MIReturn( &outParams, MI_RESULT_OK ), "R_LifecycleC1_GenericMethod_Set_MIReturn");
    CHKMIRESULTPOST(R_LifecycleC1_GenericMethod_Post( &outParams, context ), "R_LifecycleC1_GenericMethod_Post");
    CHKMIRESULTPOST(R_LifecycleC1_GenericMethod_Destruct( &outParams ), "R_LifecycleC1_GenericMethod_Destruct");

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC1_Invoke_GenericInstMethod(
    R_LifecycleC1_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_LifecycleC1* instanceName,
    const R_LifecycleC1_GenericInstMethod* in)
{
    R_LifecycleC1_GenericInstMethod outParams;

    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgR_LifecycleC1, MI_LIFECYCLE_INDICATION_METHODCALL, cfgR_LifecycleC1.lifecycleInstance, NULL, (MI_Instance*)in), "lifecycle_AddEventToQueue");
    
    CHKMIRESULTPOST(R_LifecycleC1_GenericInstMethod_Construct( &outParams, context ), "R_LifecycleC1_GenericInstMethod_Construct");
    CHKMIRESULTPOST(R_LifecycleC1_GenericInstMethod_Set_MIReturn( &outParams, MI_RESULT_OK ), "R_LifecycleC1_GenericInstMethod_Set_MIReturn");
    CHKMIRESULTPOST(R_LifecycleC1_GenericInstMethod_Post( &outParams, context ), "R_LifecycleC1_GenericInstMethod_Post");
    CHKMIRESULTPOST(R_LifecycleC1_GenericInstMethod_Destruct( &outParams ), "R_LifecycleC1_GenericInstMethod_Destruct");

    MI_PostResult(context, MI_RESULT_OK);
}

