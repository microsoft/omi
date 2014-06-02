/*
**==============================================================================
**
** Open Management Infrastructure (OMI)
**
** Copyright (c) Microsoft Corporation
** 
** Licensed under the Apache License, Version 2.0 (the "License"); you may not 
** use this file except in compliance with the License. You may obtain a copy 
** of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED 
** WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, 
** MERCHANTABLITY OR NON-INFRINGEMENT. 
**
** See the Apache 2 License for the specific language governing permissions 
** and limitations under the License.
**
**==============================================================================
*/

#include "impl.h"
#include <time.h>
#include <pal/atomic.h>

#define FMT_APICALL_BEGIN "%s_%s"
#define FMT_APICALL_END "%s_%s:Result(%d)"
#define CLASS_SELF ((void*)0x12345)
#define SUBSCRIBE_SELF ((void*)0x54321)

_Use_decl_annotations_
    MI_Result class_Load(
    void** classSelf,
    Config* config,
    SetupIndicationProperties setp)
{
    MI_Result r = MI_RESULT_OK;

    LOGMSG(("%s_Load: start", config->className));
    DumpConfig(config);
    if (config->logLoadUnloadCall)
        writeAPIlog(config, FMT_APICALL_BEGIN, config->className, "Load", r);
    config->seminited = MI_FALSE;

    switch(config->testGroup)
    {
    case TestGroup_Default:
        break;
    case TestGroup_Init:
        switch (config->initBehavior)
        {
        case InitBehavior_ClassLoadFail:
            {
                LOGMSG(("%s_Load: Expected failure", config->className));
                if (config->initResultCode == MI_RESULT_OK)
                    LOGMSG(("%s_Load: initResultCode is OK, which is unexpected !!", config->className));
                r = config->initResultCode;
                goto DONE;
            }
            break;
        case InitBehavior_ClassLoadTimeout:
            {
                LOGMSG(("%s_Load: Expected timeout and failure", config->className));
                Sleep_Milliseconds(config->initTimeoutMS);
                r = config->initResultCode;
                if (r == MI_RESULT_OK)
                    r = MI_RESULT_FAILED;
                goto DONE;
            }
            break;
        default:
            break;
        }
    case TestGroup_Finalize:
        break;
    case TestGroup_Post:
        break;
    case TestGroup_Misc:
        switch (config->miscTestSubGroup)
        {
        case MiscTestGroup_SelfTest:
            config->classSelf = CLASS_SELF;
            *classSelf = config->classSelf;
            break;
        default:
            break;
        }
        break;
        break;
    default:
        break;
    }

    config->setprop = setp;
    config->context = (void*)config;
    config->count = 0;
    config->disabled = MI_FALSE;
    config->postctx = NULL;
    config->indication = NULL;

    if (Sem_Init(&config->sem, SEM_USER_ACCESS_ALLOW_ALL, 0) != 0)
    {
        LOGMSG(("%s_Load: failed to create semaphore", config->className));
        r = MI_RESULT_FAILED;
    }
    else
        config->seminited = MI_TRUE;
DONE:
    LOGMSG(("%s_Load: done", config->className));
    if (config->logLoadUnloadCall)
        writeAPIlog(config, FMT_APICALL_END, config->className, "Load", r);
    return r;
}

_Use_decl_annotations_
    MI_Result class_Unload(
    void* classSelf,
    Config* config)
{
    MI_Result r = MI_RESULT_OK;

    LOGMSG(("%s_Unload: start", config->className));
    DumpConfig(config);
    if (config->logLoadUnloadCall)
        writeAPIlog(config, FMT_APICALL_END, config->className, "Unload", r);

    if (config->indication)
        MI_Instance_Delete(config->indication);

    if (MI_TRUE == config->seminited)
    {
        Sem_Destroy(&config->sem);
        config->seminited = MI_FALSE;
    }

    switch(config->testGroup)
    {
    case TestGroup_Default:
        break;
    case TestGroup_Init:
        break;
    case TestGroup_Finalize:
        switch (config->finalizeBehavior)
        {
        case FinalizeBehavior_ClassUnloadFail:
            {
                if (config->finalizeResultCode == MI_RESULT_OK)
                    LOGMSG(("%s_Unload: finalizeResultCode is OK, which is unexpected !!", config->className));
                r = config->finalizeResultCode;
            }
            break;
        default:
            break;
        }
        break;
    case TestGroup_Post:
        break;
    case TestGroup_Misc:
        switch(config->miscTestSubGroup)
        {
        case MiscTestGroup_SelfTest:
            if (classSelf != config->classSelf)
                r = MI_RESULT_INVALID_PARAMETER;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    LOGMSG(("%s_Unload: done", config->className));
    if (config->logLoadUnloadCall)
        writeAPIlog(config, FMT_APICALL_END, config->className, "Unload", r);
    return r;
}

MI_Result lifecycle_Load(
    _In_ Config* config, 
    _In_ MI_Instance* lifecycleInstance,
    _In_ MI_LifecycleIndicationCallback callback,
    _In_ MI_Context* context) 
{
    MI_Result r;
    MI_Instance* l = NULL;
    int createthreadcode;
    CHKMIRESULTRETURN(MI_Instance_Clone(lifecycleInstance, &l), "MI_Instance_Clone");

    config->lifecycleInstance = l;

    // Save the lifecycle context
    r = MI_Context_GetLifecycleIndicationContext(context, &config->lifecycleContext);
    CHKMIRESULTRETURN(r, "MI_Context_GetLifecycleIndicationContext");

    // Register callback for lifecycle indication post 
    r = MI_LifecycleIndicationContext_RegisterCallback(config->lifecycleContext, callback, (void*)config);
    CHKMIRESULTRETURN(r, "MI_LifecycleIndicationContext_RegisterCallback");

    // Set supported indication types
    r = MI_LifecycleIndicationContext_SetSupportedTypes(config->lifecycleContext, config->supportedSubscriptionTypes);
    CHKMIRESULTRETURN(r, "MI_LifecycleIndicationContext_SetSupportedTypes");

    // Enable background lifecycle thread
    config->lifecycleThreadDisabled = MI_FALSE;
    createthreadcode = Thread_CreateJoinable(&config->lifecycleBackgroundThread, fireLifecycleEvents, NULL, (void*)config);
    LOGMSG(("Create background thread result (%d)", createthreadcode));

    return MI_RESULT_OK;
}

MI_Result lifecycle_Unload(
    _In_ Config* config)
{
    PAL_Uint32 returnvalue;

    // Signal the background lifecycle thread to terminate
    config->lifecycleThreadDisabled = MI_TRUE;
    Sem_Post(&config->lifecycleQueue.sem, 1);

    // Wait for the background lifecycle thread to terminate 
    Thread_Join(&config->lifecycleBackgroundThread, &returnvalue);
    Thread_Destroy(&config->lifecycleBackgroundThread);
    LOGMSG(("Joined background lifecycle thread for config (%p)", config));
    LOGMSG(("Background lifecycle thread was terminated"));

    return MI_RESULT_OK;
}

MI_Result lifecycle_EnumerateInstances(
    _In_ Config* config)
{
    /*
        Note: this function is invoked by both classes' EnumerateInstances and GetInstance functions because the operations
        are functionality equivalent from a lifecycle indication perspective (both do a MI_LifecycleIndicationContext_PostRead). 
    */
    MI_Result r = MI_RESULT_OK;
    if (config->lifecycleContext && (config->currentSubscriptionTypes & config->supportedSubscriptionTypes & MI_LIFECYCLE_INDICATION_READ))
    {
        r = MI_LifecycleIndicationContext_PostRead(config->lifecycleContext, config->lifecycleInstance);
    }
    return r; 
}

MI_Result lifecycle_CreateInstance(
    _In_ Config* config,
    _In_ MI_Instance* instance)
{
    MI_Result r = MI_RESULT_OK;
    if (config->lifecycleContext && (config->currentSubscriptionTypes & config->supportedSubscriptionTypes & MI_LIFECYCLE_INDICATION_CREATE))
    {
        r = MI_LifecycleIndicationContext_PostCreate(config->lifecycleContext, instance);
    }
    return r;
}

MI_Result lifecycle_DeleteInstance(
    _In_ Config* config)
{
    MI_Result r = MI_RESULT_OK;
    if (config->lifecycleContext && (config->currentSubscriptionTypes & config->supportedSubscriptionTypes & MI_LIFECYCLE_INDICATION_DELETE))
    {
        r = MI_LifecycleIndicationContext_PostDelete(config->lifecycleContext, config->lifecycleInstance);
    }
    return r;
}

MI_Result lifecycle_ModifyInstance(
    _In_ MI_Instance* modifiedInstance, 
    _In_ Config* config)
{
    MI_Result r = MI_RESULT_OK;
    if (config->lifecycleContext && (config->currentSubscriptionTypes & config->supportedSubscriptionTypes & MI_LIFECYCLE_INDICATION_MODIFY))
    {
        r = MI_LifecycleIndicationContext_PostModify(config->lifecycleContext, config->lifecycleInstance, modifiedInstance);
    }
    return r;
}

MI_Result lifecycle_InvokeMethod(
    _In_ Config* config)
{
    MI_Result r = MI_RESULT_OK;
    if (config->lifecycleContext && (config->currentSubscriptionTypes & config->supportedSubscriptionTypes & MI_LIFECYCLE_INDICATION_METHODCALL))
    {
        r = MI_LifecycleIndicationContext_PostMethodCall_Before(config->lifecycleContext, config->lifecycleInstance, MI_T("GenericInstMethod"), NULL);
        CHKMIRESULTRETURN(r, "MI_LifecycleIndicationContext_PostMethodCall_Before");
        r = MI_LifecycleIndicationContext_PostMethodCall_After(config->lifecycleContext, config->lifecycleInstance, MI_T("GenericInstMethod"), NULL, MI_T("0"));
        CHKMIRESULTRETURN(r, "MI_LifecycleIndicationContext_PostMethodCall_After");
    }
    return r;
}

MI_Result lifecycle_ThreadControl(
    _Inout_ Config* config,
    _In_ MI_Uint32 operation)
{
    // Get current status of thread
    MI_Result r = MI_RESULT_OK;
    MI_Boolean threadRunning = ( Atomic_Read( &config->threadrunning ) == 1 );

    // Stop or start the thread if necessary
    if (threadRunning && operation == 0)
    {
        // Stop thread
        r = lifecycle_StopThread(config);
        config->lifecycleThreadControl = operation;
    }
    else if (!threadRunning && operation != 0)
    {
        // Start thread
        config->lifecycleThreadControl = operation;
        r = lifecycle_StartThread(config);
    }

    return r;
}

MI_Result lifecycle_StartThread(
    _In_ Config* config)
{
    int createthreadcode = Thread_CreateJoinable(&config->thread, fireindication, NULL, (void*)config);

    config->disabled = MI_FALSE;
    LOGMSG(("Create background thread result (%d)", createthreadcode));

    return MI_RESULT_OK;
}

MI_Result lifecycle_StopThread(
    _In_ Config* config)
{
    PAL_Uint32 returnvalue;
    config->disabled = MI_TRUE;
    /* Wait for background indication thread to terminate */
    if ( Atomic_Read( &config->threadrunning ) == 1 )
    {
        Thread_Join(&config->thread, &returnvalue);
        LOGMSG(("lifecycle_StopThread: Joined indication thread for config (%p)", config));
        LOGMSG(("Indication thread was terminated"));
    }
    return MI_RESULT_OK;
}

MI_Result lifecycle_AddEventToQueue(
    _In_ Config* config,
    _In_ MI_Uint32 eventType,
    _In_ MI_Instance* sourceInstance,
    _In_ MI_Instance* previousInstance,
    _In_ MI_Instance* methodParam
    )
{
    MI_Result r = MI_RESULT_OK;
    LifecycleEvent* event = (LifecycleEvent*)PAL_Calloc(1, sizeof(LifecycleEvent));

    if (event == NULL)
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED; 
    }

    event->next = NULL;
    event->type = eventType;
    
    // Save these instances to be posted later
    if (sourceInstance)
    {
        r = MI_Instance_Clone(sourceInstance, &event->sourceInstance);
        if (r != MI_RESULT_OK)
            goto DONE;
    }
    if (previousInstance)
    {
        r = MI_Instance_Clone(previousInstance, &event->previousInstance); 
        if (r != MI_RESULT_OK)
            goto DONE;
    }
    if (methodParam)
    {
        r = MI_Instance_Clone(methodParam, &event->methodParam); 
        if (r != MI_RESULT_OK)
            goto DONE;
    }
    
    LifecycleEventQueue_Add(&config->lifecycleQueue, event);
    Sem_Post(&config->lifecycleQueue.sem, 1);

DONE:
    if (r != MI_RESULT_OK)
    {
        LifecycleEvent_Free(event);
    }
    return MI_RESULT_OK;
}

LifecycleEvent* lifecycle_RemoveEventFromQueue(
    _In_ Config* config)
{
    LifecycleEvent* event = LifecycleEventQueue_Remove(&config->lifecycleQueue);
    return event;
}

_Use_decl_annotations_
    MI_Result class_EnableIndications(
    void* classSelf,
    MI_Context* context,
    Config* config,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    /* TODO: store indicationsContext for later usage */
    /* NOTE: Do not call MI_PostResult on this context */
    MI_Result r = MI_RESULT_OK;
    MI_Boolean startfireindication = MI_TRUE;

    LOGMSG(("%s_EnableIndications: start", config->className));
    DumpConfig(config);
    writeAPIlog(config, FMT_APICALL_BEGIN, config->className, "EnableIndications");

    config->disabled = MI_FALSE;
    config->postctx = context;
    config->filter = NULL;

    switch(config->testGroup)
    {
    case TestGroup_Default:
        break;
    case TestGroup_Init:
        switch (config->initBehavior)
        {
        case InitBehavior_EnableFail:
            {
                LOGMSG(("%s_EnableIndications: Expected failure", config->className));
                if (config->initResultCode == MI_RESULT_OK)
                    LOGMSG(("%s_EnableIndications: initResultCode is OK, which is unexpected !!", config->className));
                r = config->initResultCode;
                goto DONE;
            }
            break;
        case InitBehavior_EnableTimeout:
            {
                LOGMSG(("%s_EnableIndications: Expected timeout and failure", config->className));
                Sleep_Milliseconds(config->initTimeoutMS);
                r = config->initResultCode;
                if (r == MI_RESULT_OK)
                    r = MI_RESULT_FAILED;
                goto DONE;
            }
            break;
        default:
            break;
        }
        break;
    case TestGroup_Finalize:
        break;
    case TestGroup_Post:
        switch (config->postBehavior)
        {
        case PostBehavior_Subcontext:
            startfireindication = MI_FALSE;
            break;
        case PostBehavior_Enablecontext_PostOnCalllthread:
        case PostBehavior_Subcontext_PostOnCalllthread:
            goto DONE;
        default:
            break;
        }
        break;
    case TestGroup_Misc:
        switch (config->miscTestSubGroup)
        {
        case MiscTestGroup_SelfTest:
            if (classSelf != config->classSelf)
            {
                r = MI_RESULT_INVALID_PARAMETER;
                goto DONE;
            }
            break;
        case MiscTestGroup_GetExpression:
        case MiscTestGroup_Evaluate:
            startfireindication = MI_FALSE;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    {
        int createthreadcode = Thread_CreateJoinable(&config->thread, fireindication, NULL, (void*)config);
        LOGMSG(("Create background thread result (%d)", createthreadcode));

        if (MI_TRUE == startfireindication)
        {
            LOGMSG(("Signal semaphore to fire indication"));
            Sem_Post(&config->sem, 1);
        }
    }

DONE:
    LOGMSG(("%s_EnableIndications: done", config->className));
    writeAPIlog(config, FMT_APICALL_END, config->className, "EnableIndications", r);
    return r;
}

_Use_decl_annotations_
    MI_Result class_DisableIndications(
    void* classSelf,
    MI_Context* context,
    Config* config,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    MI_Result r = MI_RESULT_OK;

    /* TODO: stop background thread that monitors subscriptions */
    PAL_Uint32 returnvalue;

    LOGMSG(("%s_DisableIndications: start", config->className));
    DumpConfig(config);
    writeAPIlog(config, FMT_APICALL_BEGIN, config->className, "DisableIndications");

    /* signal background thread to terminate */
    config->disabled = MI_TRUE;
    config->filter = NULL;

    switch(config->testGroup)
    {
    case TestGroup_Default:
        break;
    case TestGroup_Init:
        break;
    case TestGroup_Finalize:
        switch (config->finalizeBehavior)
        {
        case FinalizeBehavior_DisableFail:
            if (config->finalizeResultCode == MI_RESULT_OK)
                LOGMSG(("%s_DisableIndications: finalizeResultCode is OK, which is unexpected !!", config->className));
            r = config->finalizeResultCode;
            goto DONE;
            break;
        default:
            break;
        }
        break;
    case TestGroup_Post:
        break;
    case TestGroup_Misc:
        switch(config->miscTestSubGroup)
        {
        case MiscTestGroup_SelfTest:
            if (classSelf != config->classSelf)
                r = MI_RESULT_INVALID_PARAMETER;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

DONE:
    /* wait for background indication thread to terminate */
    if (Atomic_Read( &config->threadrunning ) == 1 )
    {
        Thread_Join(&config->thread, &returnvalue);
        Thread_Destroy(&config->thread);
        LOGMSG(("Joined indication thread for config (%p)", config));
        LOGMSG(("Indication thread was terminated"));
    }

    LOGMSG(("%s_DisableIndications: done", config->className));
    writeAPIlog(config, FMT_APICALL_END, config->className, "DisableIndications", r);

    return r;
}

_Use_decl_annotations_
    MI_Result class_Subscribe(
    void* classSelf,
    MI_Context* context,
    Config* config,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Filter* filter,
    const MI_Char* bookmark,
    MI_Uint64 subscriptionID,
    void** subscriptionSelf)
{
    MI_Result r = MI_RESULT_OK;
    LOGMSG(("%s_Subscribe: start", config->className));
    DumpConfig(config);
    writeAPIlog(config, FMT_APICALL_BEGIN, config->className, "Subscribe");

    switch(config->testGroup)
    {
    case TestGroup_Default:
        break;
    case TestGroup_Init:
        switch (config->initBehavior)
        {
        case InitBehavior_SubscribeFail:
            {
                LOGMSG(("%s_Subscribe: Expected failure", config->className));
                if (config->initResultCode == MI_RESULT_OK)
                    LOGMSG(("%s_Subscribe: initResultCode is OK, which is unexpected !!"));
                r = config->initResultCode;
                goto DONE;
            }
            break;
        case InitBehavior_SubscribeTimeout:
            {
                LOGMSG(("%s_Subscribe: Expected timeout and failure", config->className));
                Sleep_Milliseconds(config->initTimeoutMS);
                r = config->initResultCode;
                if (r == MI_RESULT_OK)
                    r = MI_RESULT_FAILED;
                goto DONE;
            }
            break;
        default:
            break;
        }
        break;
    case TestGroup_Finalize:
        break;
    case TestGroup_Post:
        switch (config->postBehavior)
        {
        case PostBehavior_Subcontext:
            {
                config->postctx = context;
                /* signal other thread to fire indication */
                Sem_Post(&config->sem, 1);
                LOGMSG(("Signal semaphore to fire indication"));
            }
            break;
        case PostBehavior_Enablecontext_PostOnCalllthread:
        case PostBehavior_Subcontext_PostOnCalllthread:
            break;
        default:
            break;
        }
        break;
    case TestGroup_Misc:
        switch (config->miscTestSubGroup)
        {
        case MiscTestGroup_SelfTest:
            config->subscriptionSelf = SUBSCRIBE_SELF;
            *subscriptionSelf = config->subscriptionSelf;
            if (classSelf != config->classSelf)
                r = MI_RESULT_INVALID_PARAMETER;

        case MiscTestGroup_GetExpression:
        case MiscTestGroup_Evaluate:

            config->filter = filter;
            if (bookmark)
            {
                config->subscribeBookmark = MIToansi(bookmark);
            }
            if (NULL == config->subscribeBookmark)
            {
                config->subscribeBookmark = ".";
            }
            config->subscriptionID = subscriptionID;
            /* signal other thread to fire indication */
            Sem_Post(&config->sem, 1);
            LOGMSG(("Signal semaphore to fire indication"));
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

DONE:
    LOGMSG(("%s_Subscribe: done", config->className));
    writeAPIlog(config, FMT_APICALL_END, config->className, "Subscribe", r);
    return r;
}

_Use_decl_annotations_
    MI_Result class_Unsubscribe(
    void* classSelf,
    MI_Context* context,
    Config* config,
    const MI_Char* nameSpace,
    const MI_Char* className,
    MI_Uint64 subscriptionID,
    void* subscriptionSelf)
{
    MI_Result r = MI_RESULT_OK;
    LOGMSG(("%s_Unsubscribe: start", config->className));
    DumpConfig(config);
    writeAPIlog(config, FMT_APICALL_BEGIN, config->className, "Unsubscribe");
    config->filter = NULL;
    switch(config->testGroup)
    {
    case TestGroup_Default:
        break;
    case TestGroup_Init:
        break;
    case TestGroup_Finalize:
        switch (config->finalizeBehavior)
        {
        case FinalizeBehavior_UnsubscribeFail:
            {
                if (config->finalizeResultCode == MI_RESULT_OK)
                    LOGMSG(("%s_Unsubscribe: finalizeResultCode is OK, which is unexpected", config->className));
                r = config->finalizeResultCode;
                goto DONE;
            }
            break;
        default:
            break;
        }
        break;
    case TestGroup_Post:
        break;
    case TestGroup_Misc:
        switch (config->miscTestSubGroup)
        {
        case MiscTestGroup_SelfTest:
            if (subscriptionSelf != config->subscriptionSelf)
                r = MI_RESULT_INVALID_PARAMETER;
            if (classSelf != config->classSelf)
                r = MI_RESULT_INVALID_PARAMETER;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
DONE:
    LOGMSG(("%s_Unsubscribe: done", config->className));
    writeAPIlog(config, FMT_APICALL_END, config->className, "Unsubscribe", r);
    return r;
}

_Use_decl_annotations_
MI_Result class_TestFilter(
    Config* config,
    MI_Instance* inst,
    MI_Boolean* result)
{
    MI_Result r = MI_RESULT_OK;
    *result  = MI_TRUE;
    switch(config->testGroup)
    {
    case TestGroup_Misc:
        switch (config->miscTestSubGroup)
        {
        case MiscTestGroup_GetExpression:
            if (config->filter)
            {
                const MI_Char* expr;
                const MI_Char* lang;
                r = MI_Filter_GetExpression(config->filter, &lang, &expr);
                if (r == MI_RESULT_OK)
                {
                    if (StringCompare(expr, ansiToMI(config->expression))!=0)
                        r = MI_RESULT_FAILED;
                    else if (StringCompare(lang, ansiToMI(config->dialect))!=0)
                        r = MI_RESULT_FAILED;
                }
            }
            else
                r = MI_RESULT_FAILED;
            break;
        case MiscTestGroup_Evaluate:
            if (config->filter)
            {
                r = MI_Filter_Evaluate(config->filter, inst, result);
            }
            else
                r = MI_RESULT_FAILED;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return r;
}

MI_Datetime GetCurrentTimestamp()
{
    MI_Datetime now;
    time_t currentTime;
    struct tm * utcTime;

    time(&currentTime);
    utcTime = gmtime(&currentTime);

    now.isTimestamp = 1;
    now.u.timestamp.microseconds = 0;
    now.u.timestamp.second = utcTime->tm_sec;
    now.u.timestamp.minute = utcTime->tm_min;
    now.u.timestamp.hour = utcTime->tm_hour;
    now.u.timestamp.day = utcTime->tm_mday;
    now.u.timestamp.month = utcTime->tm_mon + 1;
    now.u.timestamp.year = utcTime->tm_year + 1900;
    now.u.timestamp.utc = 0;

    return now;
}

