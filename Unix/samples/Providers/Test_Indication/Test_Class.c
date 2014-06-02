/* @migen@ */
#include <MI.h>
#include "Test_Class.h"
#include "impl.h"

void MI_CALL _Test_Class_Callback(
    _In_ MI_Uint32 types,
    _In_opt_ void* callbackData)
{
    Config* config = (Config*)callbackData;
    config->currentSubscriptionTypes = types;
    /* signal firing thread to fire indication */
    Sem_Post(&config->sem, 1);
}

void MI_CALL Test_Class_Load(
    Test_Class_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r;
    *self = NULL;    
    {
        // Save lifecycle instance to config
        Test_Class lifecycle;
        cfgTest_Class.lifecycleInstance = NULL;
        r = Test_Class_Construct(&lifecycle, context);
        CHKMIRESULTPOST(r,"Test_Class_Construct");
        CHKMIRESULTPOST(Test_Class_Set_key(&lifecycle, MI_T("Test_Class")), "Test_Class_Set_key");
        CHKMIRESULTPOST(Test_Class_Set_value(&lifecycle, 0), "Test_Class_Set_value");

        cfgTest_Class.supportedSubscriptionTypes = MI_LIFECYCLE_INDICATION_ALL; 

        // Lifecycle indication load
        r = lifecycle_Load(&cfgTest_Class, (MI_Instance*)&lifecycle, _Test_Class_Callback, context);
        CHKMIRESULTPOST(r, "lifecycle_Load");

        // Regular class load
        r = class_Load((void**)self, &cfgTest_Class, NULL);
        CHKMIRESULTPOST(r, "class_Load");

        r = Test_Class_Destruct(&lifecycle);
        CHKMIRESULTPOST(r, "Test_Class_Destruct");
    }

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_Class_Unload(
    Test_Class_Self* self,
    MI_Context* context)
{
    CHKMIRESULTPOST(lifecycle_StopThread(&cfgTest_Class), "Test_Class_Unload");
    CHKMIRESULTPOST(lifecycle_Unload(&cfgTest_Class), "lifecycle_Unload(Test_Class)");
    CHKMIRESULTPOST(class_Unload((void*)self, &cfgTest_Class), "Test_Class_Unload");
    if (cfgTest_Class.lifecycleInstance)
    {
        MI_Instance_Delete( cfgTest_Class.lifecycleInstance );
        cfgTest_Class.lifecycleInstance = NULL;
    }
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_Class_EnumerateInstances(
    Test_Class_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    CHKMIRESULTPOST(Test_Class_Post((Test_Class*)cfgTest_Class.lifecycleInstance, context), "Test_Class_Post");
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgTest_Class, MI_LIFECYCLE_INDICATION_READ, cfgTest_Class.lifecycleInstance, NULL, NULL), "lifecycle_AddEventToQueue"); 
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_Class_GetInstance(
    Test_Class_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_Class* instanceName,
    const MI_PropertySet* propertySet)
{
    CHKMIRESULTPOST(Test_Class_Post((Test_Class*)cfgTest_Class.lifecycleInstance, context), "Test_Class_Post");
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgTest_Class, MI_LIFECYCLE_INDICATION_READ, cfgTest_Class.lifecycleInstance, NULL, NULL), "lifecycle_AddEventToQueue");
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_Class_CreateInstance(
    Test_Class_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_Class* newInstance)
{
    CHKMIRESULTPOST(Test_Class_Post(newInstance, context), "Test_Class_Post");
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgTest_Class, MI_LIFECYCLE_INDICATION_CREATE, cfgTest_Class.lifecycleInstance, NULL, NULL), "lifecycle_AddEventToQueue");
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_Class_ModifyInstance(
    Test_Class_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_Class* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    
    CHKMIRESULTPOST(Test_Class_Post(modifiedInstance, context), "Test_Class_Post");
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgTest_Class, MI_LIFECYCLE_INDICATION_MODIFY, (MI_Instance*)modifiedInstance, cfgTest_Class.lifecycleInstance, NULL), "lifecycle_AddEventToQueue");
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_Class_DeleteInstance(
    Test_Class_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const Test_Class* instanceName)
{
    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgTest_Class, MI_LIFECYCLE_INDICATION_DELETE, cfgTest_Class.lifecycleInstance, NULL, NULL), "lifecycle_AddEventToQueue");
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_Class_Invoke_ThreadControl(
    Test_Class_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Test_Class* instanceName,
    const Test_Class_ThreadControl* in)
{
    Test_Class_ThreadControl outParams;
    
    CHKMIRESULTPOST(lifecycle_ThreadControl(&cfgTest_Class, in->operation.value), "Test_Class_ThreadControl");

    CHKMIRESULTPOST(Test_Class_ThreadControl_Construct( &outParams, context ), "Test_Class_ThreadControl_Construct");
    CHKMIRESULTPOST(Test_Class_ThreadControl_Set_MIReturn( &outParams, MI_RESULT_OK ), "Test_Class_ThreadControl_Set_MIReturn");
    CHKMIRESULTPOST(Test_Class_ThreadControl_Post( &outParams, context ), "Test_Class_ThreadControl_Post");
    CHKMIRESULTPOST(Test_Class_ThreadControl_Destruct( &outParams ), "Test_Class_ThreadControl_Destruct");
    
    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_Class_Invoke_GenericMethod(
    Test_Class_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Test_Class* instanceName,
    const Test_Class_GenericMethod* in)
{
    Test_Class_GenericMethod outParams;

    CHKMIRESULTPOST(lifecycle_InvokeMethod(&cfgTest_Class), "Test_Class_GenericMethod");

    CHKMIRESULTPOST(Test_Class_GenericMethod_Construct( &outParams, context ), "Test_Class_GenericMethod_Construct");
    CHKMIRESULTPOST(Test_Class_GenericMethod_Set_MIReturn( &outParams, MI_RESULT_OK ), "Test_Class_GenericMethod_Set_MIReturn");
    CHKMIRESULTPOST(Test_Class_GenericMethod_Post( &outParams, context ), "Test_Class_GenericMethod_Post");
    CHKMIRESULTPOST(Test_Class_GenericMethod_Destruct( &outParams ), "Test_Class_GenericMethod_Destruct");

    MI_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Test_Class_Invoke_GenericInstMethod(
    Test_Class_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const Test_Class* instanceName,
    const Test_Class_GenericInstMethod* in)
{
    Test_Class_GenericInstMethod outParams;

    CHKMIRESULTPOST(lifecycle_AddEventToQueue(&cfgTest_Class, MI_LIFECYCLE_INDICATION_METHODCALL, cfgTest_Class.lifecycleInstance, NULL, (MI_Instance*)in), "lifecycle_AddEventToQueue");
    
    CHKMIRESULTPOST(Test_Class_GenericInstMethod_Construct( &outParams, context ), "Test_Class_GenericInstMethod_Construct");
    CHKMIRESULTPOST(Test_Class_GenericInstMethod_Set_MIReturn( &outParams, MI_RESULT_OK ), "Test_Class_GenericInstMethod_Set_MIReturn");
    CHKMIRESULTPOST(Test_Class_GenericInstMethod_Post( &outParams, context ), "Test_Class_GenericInstMethod_Post");
    CHKMIRESULTPOST(Test_Class_GenericInstMethod_Destruct( &outParams ), "Test_Class_GenericInstMethod_Destruct");

    MI_PostResult(context, MI_RESULT_OK);
}

