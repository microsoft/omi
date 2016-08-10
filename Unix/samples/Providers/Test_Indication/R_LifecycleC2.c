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
#include "R_LifecycleC2.h"
#include "impl.h"

void MI_CALL _R_LifecycleC2_Callback(
    _In_ MI_Uint32 types,
    _In_opt_ void* callbackData)
{
    Config* config = (Config*)callbackData;
    config->currentSubscriptionTypes = types;
    /* signal firing thread to fire indication */
    Sem_Post(&config->sem, 1);
}

void MI_CALL R_LifecycleC2_Load(
    R_LifecycleC2_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r;
    *self = NULL;    
    {
        // Save lifecycle instance to config
        R_LifecycleC2 lifecycle;
        cfgR_LifecycleC2.lifecycleInstance = NULL;
        r = R_LifecycleC2_Construct(&lifecycle, context);
        CHKMIRESULTPOST(r,"R_LifecycleC2_Construct");
        CHKMIRESULTPOST(R_LifecycleC2_Set_key(&lifecycle, MI_T("R_LifecycleC2")), "R_LifecycleC2_Set_key");
        CHKMIRESULTPOST(R_LifecycleC2_Set_value(&lifecycle, 0), "R_LifecycleC2_Set_value");

        cfgR_LifecycleC2.supportedSubscriptionTypes = MI_LIFECYCLE_INDICATION_ALL; 

        // Lifecycle indication load
        r = lifecycle_Load(&cfgR_LifecycleC2, (MI_Instance*)&lifecycle, _R_LifecycleC2_Callback, context);
        CHKMIRESULTPOST(r, "lifecycle_Load");

        // Regular class load
        r = class_Load((void**)self, &cfgR_LifecycleC2, NULL);
        CHKMIRESULTPOST(r, "class_Load");

        r = R_LifecycleC2_Destruct(&lifecycle);
        CHKMIRESULTPOST(r, "R_LifecycleC2_Destruct");
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC2_Unload(
    R_LifecycleC2_Self* self,
    MI_Context* context)
{
    CHKMIRESULTPOST(lifecycle_StopThread(&cfgR_LifecycleC2), "R_LifecycleC2_Unload");
    CHKMIRESULTPOST(lifecycle_Unload(&cfgR_LifecycleC2), "lifecycle_Unload(R_LifecycleC2)");
    CHKMIRESULTPOST(class_Unload((void*)self, &cfgR_LifecycleC2), "R_LifecycleC2_Unload");
    if (cfgR_LifecycleC2.lifecycleInstance)
    {
        MI_Instance_Delete( cfgR_LifecycleC2.lifecycleInstance );
        cfgR_LifecycleC2.lifecycleInstance = NULL;
    }
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC2_EnumerateInstances(
    R_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    CHKMIRESULTPOST(R_LifecycleC2_Post((R_LifecycleC2*)cfgR_LifecycleC2.lifecycleInstance, context), "R_LifecycleC2_Post");
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgR_LifecycleC2, MI_LIFECYCLE_INDICATION_READ, cfgR_LifecycleC2.lifecycleInstance, NULL, NULL), "lifecycle_AddEventToQueue"); 
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC2_GetInstance(
    R_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_LifecycleC2* instanceName,
    const MI_PropertySet* propertySet)
{
    CHKMIRESULTPOST(R_LifecycleC2_Post((R_LifecycleC2*)cfgR_LifecycleC2.lifecycleInstance, context), "R_LifecycleC2_Post");
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgR_LifecycleC2, MI_LIFECYCLE_INDICATION_READ, cfgR_LifecycleC2.lifecycleInstance, NULL, NULL), "lifecycle_AddEventToQueue");
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC2_CreateInstance(
    R_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_LifecycleC2* newInstance)
{
    CHKMIRESULTPOST(R_LifecycleC2_Post(newInstance, context), "R_LifecycleC2_Post");
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgR_LifecycleC2, MI_LIFECYCLE_INDICATION_CREATE, cfgR_LifecycleC2.lifecycleInstance, NULL, NULL), "lifecycle_AddEventToQueue");
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC2_ModifyInstance(
    R_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_LifecycleC2* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    
    CHKMIRESULTPOST(R_LifecycleC2_Post(modifiedInstance, context), "R_LifecycleC2_Post");
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgR_LifecycleC2, MI_LIFECYCLE_INDICATION_MODIFY, (MI_Instance*)modifiedInstance, cfgR_LifecycleC2.lifecycleInstance, NULL), "lifecycle_AddEventToQueue");
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC2_DeleteInstance(
    R_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const R_LifecycleC2* instanceName)
{
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgR_LifecycleC2, MI_LIFECYCLE_INDICATION_DELETE, cfgR_LifecycleC2.lifecycleInstance, NULL, NULL), "lifecycle_AddEventToQueue");
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC2_Invoke_ThreadControl(
    R_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_LifecycleC2* instanceName,
    const R_LifecycleC2_ThreadControl* in)
{
    R_LifecycleC2_ThreadControl outParams;
    
    CHKMIRESULTPOST(lifecycle_ThreadControl(&cfgR_LifecycleC2, in->operation.value), "R_LifecycleC2_ThreadControl");

    CHKMIRESULTPOST(R_LifecycleC2_ThreadControl_Construct( &outParams, context ), "R_LifecycleC2_ThreadControl_Construct");
    CHKMIRESULTPOST(R_LifecycleC2_ThreadControl_Set_MIReturn( &outParams, MI_RESULT_OK ), "R_LifecycleC2_ThreadControl_Set_MIReturn");
    CHKMIRESULTPOST(R_LifecycleC2_ThreadControl_Post( &outParams, context ), "R_LifecycleC2_ThreadControl_Post");
    CHKMIRESULTPOST(R_LifecycleC2_ThreadControl_Destruct( &outParams ), "R_LifecycleC2_ThreadControl_Destruct");
    
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC2_Invoke_GenericMethod(
    R_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_LifecycleC2* instanceName,
    const R_LifecycleC2_GenericMethod* in)
{
    R_LifecycleC2_GenericMethod outParams;

    CHKMIRESULTPOST(lifecycle_InvokeMethod(&cfgR_LifecycleC2), "R_LifecycleC2_GenericMethod");

    CHKMIRESULTPOST(R_LifecycleC2_GenericMethod_Construct( &outParams, context ), "R_LifecycleC2_GenericMethod_Construct");
    CHKMIRESULTPOST(R_LifecycleC2_GenericMethod_Set_MIReturn( &outParams, MI_RESULT_OK ), "R_LifecycleC2_GenericMethod_Set_MIReturn");
    CHKMIRESULTPOST(R_LifecycleC2_GenericMethod_Post( &outParams, context ), "R_LifecycleC2_GenericMethod_Post");
    CHKMIRESULTPOST(R_LifecycleC2_GenericMethod_Destruct( &outParams ), "R_LifecycleC2_GenericMethod_Destruct");

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL R_LifecycleC2_Invoke_GenericInstMethod(
    R_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const R_LifecycleC2* instanceName,
    const R_LifecycleC2_GenericInstMethod* in)
{
    R_LifecycleC2_GenericInstMethod outParams;

    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgR_LifecycleC2, MI_LIFECYCLE_INDICATION_METHODCALL, cfgR_LifecycleC2.lifecycleInstance, NULL, (MI_Instance*)in), "lifecycle_AddEventToQueue");
    
    CHKMIRESULTPOST(R_LifecycleC2_GenericInstMethod_Construct( &outParams, context ), "R_LifecycleC2_GenericInstMethod_Construct");
    CHKMIRESULTPOST(R_LifecycleC2_GenericInstMethod_Set_MIReturn( &outParams, MI_RESULT_OK ), "R_LifecycleC2_GenericInstMethod_Set_MIReturn");
    CHKMIRESULTPOST(R_LifecycleC2_GenericInstMethod_Post( &outParams, context ), "R_LifecycleC2_GenericInstMethod_Post");
    CHKMIRESULTPOST(R_LifecycleC2_GenericInstMethod_Destruct( &outParams ), "R_LifecycleC2_GenericInstMethod_Destruct");

    MI_PostResult(context, MI_RESULT_OK);
}

