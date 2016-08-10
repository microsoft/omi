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
#include "L_LifecycleC2.h"
#include "impl.h"

void MI_CALL _L_LifecycleC2_Callback(
    _In_ MI_Uint32 types,
    _In_opt_ void* callbackData)
{
    Config* config = (Config*)callbackData;
    config->currentSubscriptionTypes = types;
    /* signal firing thread to fire indication */
    Sem_Post(&config->sem, 1);
}

void MI_CALL L_LifecycleC2_Load(
    L_LifecycleC2_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r;
    *self = NULL;    
    {
        // Save lifecycle instance to config
        L_LifecycleC2 lifecycle;
        cfgL_LifecycleC2.lifecycleInstance = NULL;
        r = L_LifecycleC2_Construct(&lifecycle, context);
        CHKMIRESULTPOST(r,"L_LifecycleC2_Construct");
        CHKMIRESULTPOST(L_LifecycleC2_Set_key(&lifecycle, MI_T("L_LifecycleC2")), "L_LifecycleC2_Set_key");
        CHKMIRESULTPOST(L_LifecycleC2_Set_value(&lifecycle, 0), "L_LifecycleC2_Set_value");

        cfgL_LifecycleC2.supportedSubscriptionTypes = MI_LIFECYCLE_INDICATION_ALL;

        // Lifecycle indication load
        r = lifecycle_Load(&cfgL_LifecycleC2, (MI_Instance*)&lifecycle, _L_LifecycleC2_Callback, context);
        CHKMIRESULTPOST(r, "lifecycle_Load");

        // Regular class load
        r = class_Load((void**)self, &cfgL_LifecycleC2, NULL);
        CHKMIRESULTPOST(r, "class_Load");

        r = L_LifecycleC2_Destruct(&lifecycle);
        CHKMIRESULTPOST(r, "L_LifecycleC2_Destruct");
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL L_LifecycleC2_Unload(
    L_LifecycleC2_Self* self,
    MI_Context* context)
{
    CHKMIRESULTPOST(lifecycle_StopThread(&cfgL_LifecycleC2), "L_LifecycleC2_Unload");
    CHKMIRESULTPOST(lifecycle_Unload(&cfgL_LifecycleC2), "lifecycle_Unload(L_LifecycleC2)");
    CHKMIRESULTPOST(class_Unload((void*)self, &cfgL_LifecycleC2), "L_LifecycleC2_Unload");
    if (cfgL_LifecycleC2.lifecycleInstance)
    {
        MI_Instance_Delete( cfgL_LifecycleC2.lifecycleInstance );
        cfgL_LifecycleC2.lifecycleInstance = NULL;
    }
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL L_LifecycleC2_EnumerateInstances(
    L_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    CHKMIRESULTPOST(L_LifecycleC2_Post((L_LifecycleC2*)cfgL_LifecycleC2.lifecycleInstance, context), "L_LifecycleC2_Post");
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgL_LifecycleC2, MI_LIFECYCLE_INDICATION_READ, cfgL_LifecycleC2.lifecycleInstance, NULL, NULL), "lifecycle_AddEventToQueue"); 
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL L_LifecycleC2_GetInstance(
    L_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_LifecycleC2* instanceName,
    const MI_PropertySet* propertySet)
{
    CHKMIRESULTPOST(L_LifecycleC2_Post((L_LifecycleC2*)cfgL_LifecycleC2.lifecycleInstance, context), "L_LifecycleC2_Post");
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgL_LifecycleC2, MI_LIFECYCLE_INDICATION_READ, cfgL_LifecycleC2.lifecycleInstance, NULL, NULL), "lifecycle_AddEventToQueue");
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL L_LifecycleC2_CreateInstance(
    L_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_LifecycleC2* newInstance)
{
    CHKMIRESULTPOST(L_LifecycleC2_Post(newInstance, context), "L_LifecycleC2_Post");
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgL_LifecycleC2, MI_LIFECYCLE_INDICATION_CREATE, cfgL_LifecycleC2.lifecycleInstance, NULL, NULL), "lifecycle_AddEventToQueue");
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL L_LifecycleC2_ModifyInstance(
    L_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_LifecycleC2* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    
    CHKMIRESULTPOST(L_LifecycleC2_Post(modifiedInstance, context), "L_LifecycleC2_Post");
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgL_LifecycleC2, MI_LIFECYCLE_INDICATION_MODIFY, (MI_Instance*)modifiedInstance, cfgL_LifecycleC2.lifecycleInstance, NULL), "lifecycle_AddEventToQueue");
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL L_LifecycleC2_DeleteInstance(
    L_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const L_LifecycleC2* instanceName)
{
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgL_LifecycleC2, MI_LIFECYCLE_INDICATION_DELETE, cfgL_LifecycleC2.lifecycleInstance, NULL, NULL), "lifecycle_AddEventToQueue");
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL L_LifecycleC2_Invoke_ThreadControl(
    L_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const L_LifecycleC2* instanceName,
    const L_LifecycleC2_ThreadControl* in)
{
    L_LifecycleC2_ThreadControl outParams;
    
    CHKMIRESULTPOST(lifecycle_ThreadControl(&cfgL_LifecycleC2, in->operation.value), "L_LifecycleC2_ThreadControl");

    CHKMIRESULTPOST(L_LifecycleC2_ThreadControl_Construct( &outParams, context ), "L_LifecycleC2_ThreadControl_Construct");
    CHKMIRESULTPOST(L_LifecycleC2_ThreadControl_Set_MIReturn( &outParams, MI_RESULT_OK ), "L_LifecycleC2_ThreadControl_Set_MIReturn");
    CHKMIRESULTPOST(L_LifecycleC2_ThreadControl_Post( &outParams, context ), "L_LifecycleC2_ThreadControl_Post");
    CHKMIRESULTPOST(L_LifecycleC2_ThreadControl_Destruct( &outParams ), "L_LifecycleC2_ThreadControl_Destruct");
    
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL L_LifecycleC2_Invoke_GenericMethod(
    L_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const L_LifecycleC2* instanceName,
    const L_LifecycleC2_GenericMethod* in)
{
    L_LifecycleC2_GenericMethod outParams;

    CHKMIRESULTPOST(lifecycle_InvokeMethod(&cfgL_LifecycleC2), "L_LifecycleC2_GenericMethod");

    CHKMIRESULTPOST(L_LifecycleC2_GenericMethod_Construct( &outParams, context ), "L_LifecycleC2_GenericMethod_Construct");
    CHKMIRESULTPOST(L_LifecycleC2_GenericMethod_Set_MIReturn( &outParams, MI_RESULT_OK ), "L_LifecycleC2_GenericMethod_Set_MIReturn");
    CHKMIRESULTPOST(L_LifecycleC2_GenericMethod_Post( &outParams, context ), "L_LifecycleC2_GenericMethod_Post");
    CHKMIRESULTPOST(L_LifecycleC2_GenericMethod_Destruct( &outParams ), "L_LifecycleC2_GenericMethod_Destruct");

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL L_LifecycleC2_Invoke_GenericInstMethod(
    L_LifecycleC2_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const L_LifecycleC2* instanceName,
    const L_LifecycleC2_GenericInstMethod* in)
{
    L_LifecycleC2_GenericInstMethod outParams;

    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgL_LifecycleC2, MI_LIFECYCLE_INDICATION_METHODCALL, cfgL_LifecycleC2.lifecycleInstance, NULL, (MI_Instance*)in), "lifecycle_AddEventToQueue");
    
    CHKMIRESULTPOST(L_LifecycleC2_GenericInstMethod_Construct( &outParams, context ), "L_LifecycleC2_GenericInstMethod_Construct");
    CHKMIRESULTPOST(L_LifecycleC2_GenericInstMethod_Set_MIReturn( &outParams, MI_RESULT_OK ), "L_LifecycleC2_GenericInstMethod_Set_MIReturn");
    CHKMIRESULTPOST(L_LifecycleC2_GenericInstMethod_Post( &outParams, context ), "L_LifecycleC2_GenericInstMethod_Post");
    CHKMIRESULTPOST(L_LifecycleC2_GenericInstMethod_Destruct( &outParams ), "L_LifecycleC2_GenericInstMethod_Destruct");

    MI_PostResult(context, MI_RESULT_OK);
}

