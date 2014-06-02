/*============================================================================
 * Copyright (C) Microsoft Corporation, All rights reserved. 
 *
 * NOTE: This file must be includable from within C files.  
 * Do not put C++ code in here. 
 *============================================================================
 */
#include <ut/ut.h>
#include <MI.h>
#include <base/batch.h>
#include <base/class.h>
#include <pal/strings.h>
#include <pal/thread.h>
#include <pal/sleep.h>

extern const MI_ApplicationFT g_Test1_applicationFT;
extern const MI_ApplicationFT g_Test2_applicationFT;
extern const MI_SessionFT g_Test1_sessionFT;
extern const MI_SessionFT g_Test2_sessionFT;
extern const MI_OperationFT g_Test1_operationFT;
extern const MI_HostedProviderFT g_Test1_hostedProvider;
extern const MI_DestinationOptionsFT g_testDestinationOptionsFT;
extern const MI_OperationOptionsFT g_testOperationOptionsFT;
extern const MI_SubscriptionDeliveryOptionsFT g_testSubscriptionDeliveryOptionsFT;

MI_EXTERN_C MI_CONST MI_ClassDecl MyClass_rtti;


enum
{
    Test1_Operation_GetInstance,
    Test1_Operation_PutInstance,
    Test1_Operation_CreateInstance,
    Test1_Operation_DeleteInstance,
    Test1_Operation_InvokeInstance,
    Test1_Operation_EnumerateInstance,
    Test1_Operation_GetClass,
    Test1_Operation_EnumerateClasses,
    Test1_Operation_Subscribe
};

typedef struct _Test1_CommonData
{
    MI_Instance *resultInstance;
    MI_Class *resultClass;
    MI_Result resultCode;

    MI_Uint32 flags;
    MI_OperationCallbacks callbacks;

    MI_Operation operation;
} Test1_CommonData;

struct _Test1_GetInstance
{
    Test1_CommonData commonData;

    enum {
        Normal = 0,
        NoResult = 1,
        NoResultDifferentThread = 2
    } testDetails;
} g_test1_GetInstance;

struct _Test1_Invoke
{
    Test1_CommonData commonData;
    
    enum {
        Normal = 0
    } testDetails;

    int streamResultCount;
} g_test1_Invoke;

struct _Test1_EnumerateInstances
{
    Test1_CommonData commonData;

   unsigned int numberOfResultsLeft;
} g_test1_EnumerateInstances;


MI_EXTERN_C void DeliverResultsDifferentThread(Test1_CommonData *data);


MI_EXTERN_C MI_EXPORT MI_Result MI_MAIN_CALL Test1_Application_Initialize(
               MI_Uint32 flags, 
    _In_opt_z_ const MI_Char * applicationID,
    _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
    _Out_      MI_Application *application)
{
    if (NitsAssert(flags==0, PAL_T("TEST1 PH: Flags should be 0")) &&
        NitsAssert(application != NULL, PAL_T("Test1 PH: application is null")))
    {
        application->ft = &g_Test1_applicationFT;
        if (TestSystem::ShouldFault(TLINE, TestSystem::Automatic))
        {
            return MI_RESULT_FAILED;
        }
        return MI_RESULT_OK;
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
}

MI_EXTERN_C MI_EXPORT  MI_Result MI_MAIN_CALL Test2_Application_Initialize(
               MI_Uint32 flags, 
    _In_opt_z_ const MI_Char * applicationID,
    _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
    _Out_      MI_Application *application)
{
    if (extendedError)
        *extendedError = NULL;

    if (NitsAssert(flags==0, PAL_T("TEST2 PH: Flags should be 0")) &&
        NitsAssert(application != NULL, PAL_T("Test2 PH: application is null")))
    {
        application->ft = &g_Test2_applicationFT;
        return MI_RESULT_OK;
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
}

MI_EXTERN_C MI_Result MI_CALL Test1_Application_NewHostedProvider(
    _In_  MI_Application *application,
    _In_z_  const MI_Char * namespaceName,
    _In_z_  const MI_Char * providerName,
    _In_  MI_MainFunction mi_Main,
    _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
    _Out_ MI_HostedProvider *hostedProvider)
{
    if (extendedError)
        *extendedError = NULL;

    NitsAssert(application != NULL, PAL_T("Test1 PH NewHostedProvider: Application is NULL"));
    NitsAssert(namespaceName != NULL, PAL_T("Test1 PH NewHostedProvider: namespace name is NULL"));
    NitsAssert(providerName != NULL, PAL_T("Test1 PH NewHostedProvider: provider name is NULL"));
    NitsAssert(mi_Main != NULL, PAL_T("Test1 PH NewHostedProvider: MI_Main is NULL"));
    if (NitsAssert(hostedProvider != NULL, PAL_T("Test1 PH NewHostedProvider: hostedProvider is NULL")))
    {
        hostedProvider->reserved1 = 0;
        hostedProvider->reserved2 = 0;
        hostedProvider->ft = &g_Test1_hostedProvider;
        return MI_RESULT_OK;
    }
    return MI_RESULT_INVALID_PARAMETER;
}

MI_EXTERN_C MI_Result MI_CALL Test1_Application_NewSession(
    _In_     MI_Application *application, 
    _In_opt_z_ const MI_Char *protocol,
    _In_opt_z_ const MI_Char *destination,
    _In_opt_ MI_DestinationOptions *options,
    _In_opt_ MI_SessionCallbacks *callbacks,
    _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
    _Out_    MI_Session *session)
{
    if (extendedError)
        *extendedError = NULL;

    NitsAssert(application != NULL, PAL_T("Test1 PH: NewSession: Application is NULL"));
    NitsAssert(callbacks != NULL, PAL_T("Test1 PH NewSession: callbacks are NULL"));
    if (NitsAssert(session != NULL, PAL_T("Test1 PH NewSession: session is NULL")))
    {
        memset(session, 0, sizeof(MI_Session));
        session->ft = &g_Test1_sessionFT;

        if (callbacks && callbacks->writeError)
        {
            callbacks->writeError(application, callbacks->callbackContext, NULL);
        }
        if (callbacks && callbacks->writeMessage)
        {
            callbacks->writeMessage(application, callbacks->callbackContext, MI_WRITEMESSAGE_CHANNEL_VERBOSE, PAL_T("writemessage"));
        }
    }
    return MI_RESULT_OK;
}
MI_EXTERN_C MI_Result MI_CALL Test2_Application_NewSession(
    _In_     MI_Application *application, 
    _In_opt_z_ const MI_Char *protocol,
    _In_opt_z_ const MI_Char *destination,
    _In_opt_ MI_DestinationOptions *options,
    _In_opt_ MI_SessionCallbacks *callbacks,
    _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
    _Out_    MI_Session *session)
{
    if (extendedError)
        *extendedError = NULL;

    NitsAssert(application != NULL, PAL_T("Test1 PH: NewSession: Application is NULL"));
    NitsAssert(callbacks != NULL, PAL_T("Test1 PH NewSession: callbacks are NULL"));
    if (NitsAssert(session != NULL, PAL_T("Test1 PH NewSession: session is NULL")))
    {
        memset(session, 0, sizeof(MI_Session));
        session->ft = &g_Test2_sessionFT;
    }
    return MI_RESULT_OK;
}
MI_EXTERN_C MI_Result MI_CALL Test1_Application_Close(
    _In_ MI_Application *application)
{
    if (NitsAssert(application != NULL, PAL_T("Test1 PH Application_Close: application is null")))
    {
        NitsAssert(application->ft == &g_Test1_applicationFT, PAL_T("Test1 PH Application_Close: function table not ours"));
        application->ft = NULL;
    }
    return MI_RESULT_OK;
}

MI_EXTERN_C MI_Result MI_CALL Test2_Application_Close(
    _In_ MI_Application *application)
{
    if (NitsAssert(application != NULL, PAL_T("Test1 PH: application is null")))
    {
        NitsAssert(application->ft == &g_Test2_applicationFT, PAL_T("Test1 PH: function table not ours"));
        application->ft = NULL;
    }
    return MI_RESULT_OK;
}

MI_EXTERN_C MI_Result MI_CALL Test1_Session_Close(
     _In_     MI_Session *session,
    _In_opt_ void *completionContext,
    _In_opt_ void (MI_CALL *completionCallback)(_In_opt_ void *completionContext))
{
    NitsAssert(completionCallback!=NULL, PAL_T("Test1 PH: Session close should always be async"));

    if (NitsAssert(session != NULL, PAL_T("Test1 PH: session is null")))
    {
        session->ft = NULL;

        if (NitsAssert(completionCallback!=NULL, PAL_T("Test1 PH: Session close should always be asynchronous")) && completionCallback != NULL)
        {
            completionCallback(completionContext);
        }
    }
    return MI_RESULT_OK;
}

MI_EXTERN_C MI_Result MI_CALL ResultAcknowledgement(_In_ MI_Operation *operation)
{
    if (NitsAssert(operation != NULL, PAL_T("result acknowledgement has null operation")))
    {

        Test1_CommonData *testData = (Test1_CommonData*) operation->reserved2;
        if (operation->reserved1 == Test1_Operation_EnumerateInstance)
        {
            struct _Test1_EnumerateInstances *enumData = (struct _Test1_EnumerateInstances*) operation->reserved2;

            if (enumData->numberOfResultsLeft--)
            {
                testData->callbacks.instanceResult(operation, testData->callbacks.callbackContext, testData->resultInstance, enumData->numberOfResultsLeft!=0, MI_RESULT_OK, NULL, NULL, ResultAcknowledgement);
                /* don't delete the object yet as there is another ack to come in */
                return MI_RESULT_OK;
            }
        }
        if (operation->reserved1 == Test1_Operation_Subscribe)
        {
            struct _Test1_EnumerateInstances *enumData = (struct _Test1_EnumerateInstances*) operation->reserved2;

            if (enumData->numberOfResultsLeft--)
            {
                testData->callbacks.indicationResult(operation, testData->callbacks.callbackContext, testData->resultInstance, PAL_T("bookmark"), PAL_T("machineID"), enumData->numberOfResultsLeft!=0, MI_RESULT_OK, NULL, NULL, ResultAcknowledgement);
                /* don't delete the object yet as there is another ack to come in */
                return MI_RESULT_OK;
            }
        }
        if (operation->reserved1 == Test1_Operation_EnumerateClasses)
        {
            struct _Test1_EnumerateInstances *enumData = (struct _Test1_EnumerateInstances*) operation->reserved2;

            if (enumData->numberOfResultsLeft--)
            {
                testData->callbacks.classResult(operation, testData->callbacks.callbackContext, testData->resultClass, enumData->numberOfResultsLeft!=0, MI_RESULT_OK, NULL, NULL, ResultAcknowledgement);
                /* don't delete the object yet as there is another ack to come in */
                return MI_RESULT_OK;
            }
        }
        if (testData->resultInstance)
        {
            MI_Instance_Delete(testData->resultInstance);
            testData->resultInstance = NULL;
        }
        if (testData->resultClass)
        {
            MI_Class_Delete(testData->resultClass);
            testData->resultClass = NULL;
        }
    }
    return MI_RESULT_OK;
}
MI_EXTERN_C MI_Result MI_CALL Test1_Operation_WriteErrorCallback(_In_ MI_Operation *operation, MI_OperationCallback_ResponseType response)
{
    return MI_RESULT_OK;
}



MI_EXTERN_C  void MI_CALL Test1_Session_GetInstance(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_     const MI_Instance *inboundInstance,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation)
{
    memset(&g_test1_GetInstance, 0, sizeof(g_test1_GetInstance));
    g_test1_GetInstance.commonData.flags = flags;
    if (callbacks)
    {
        g_test1_GetInstance.commonData.callbacks =  *callbacks;
    }

    NitsAssert(session != NULL, PAL_T("session is null"));
    NitsAssert(flags & MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, PAL_T("Should always get a manual ack request"));
    if (NitsAssert(callbacks != NULL, PAL_T("should be async callbacks")) &&
        NitsAssert(callbacks->instanceResult != NULL, PAL_T("instanceResult callback NULL")) &&
        NitsAssert(operation != NULL, PAL_T("[out] operation is NULL")))
    {
        MI_Application application;
        MI_Instance *instance;
        const MI_Char *className = NULL;
        
        operation->ft = &g_Test1_operationFT;
        operation->reserved1 = Test1_Operation_GetInstance;
        operation->reserved2 = (ptrdiff_t) &g_test1_GetInstance;
        g_test1_GetInstance.commonData.operation = *operation;

        NitsCompare(MI_Instance_GetClassName(inboundInstance, &className), MI_RESULT_OK, PAL_T("instance class name"));

        if (MI_Application_Initialize(0, NULL, NULL, &application) == MI_RESULT_OK)
        {
            if (MI_Application_NewInstance(&application, PAL_T("test"), NULL, &instance) == MI_RESULT_OK)
            {
                g_test1_GetInstance.commonData.resultCode = MI_RESULT_OK;
                g_test1_GetInstance.commonData.resultInstance =  instance;

                if (Tcscmp(className, PAL_T("NoResult"))==0)
                {
                    /* Result after cancel is called on same thread */
                    g_test1_GetInstance.testDetails = _Test1_GetInstance::NoResult;
                    MI_Application_Close(&application);
                    return;
                }
                if (Tcscmp(className, PAL_T("NoResultDifferentThread")) == 0)
                {
                    /* Result after cancel is called on different thread */
                    g_test1_GetInstance.testDetails = _Test1_GetInstance::NoResultDifferentThread;
                    MI_Application_Close(&application);
                    return;
                }
                if (Tcscmp(className, PAL_T("DeliverResultDifferentThread")) == 0)
                {
                    /* instance result delivered on different thread */
                    DeliverResultsDifferentThread(&g_test1_GetInstance.commonData);
                    MI_Application_Close(&application);
                    return;
                } 
                if (callbacks->writeMessage)
                {
                    callbacks->writeMessage(operation, NULL, MI_WRITEMESSAGE_CHANNEL_WARNING, PAL_T("Hello world"));
                    callbacks->writeMessage(operation, callbacks->callbackContext, MI_WRITEMESSAGE_CHANNEL_WARNING, PAL_T("Hello world"));
                }
                if (callbacks->writeError)
                {
                    callbacks->writeError(operation, NULL, NULL, Test1_Operation_WriteErrorCallback);
                    callbacks->writeError(operation, callbacks->callbackContext,  NULL, Test1_Operation_WriteErrorCallback);
                }
                if (callbacks->writeProgress)
                {
                    callbacks->writeProgress(operation, NULL, PAL_T("activity"), PAL_T("current operation"), PAL_T("status description"), 42, 45);
                    callbacks->writeProgress(operation, callbacks->callbackContext, PAL_T("activity"), PAL_T("current operation"), PAL_T("status description"), 42, 45);
                }
                if (callbacks->promptUser)
                {
                    callbacks->promptUser(operation, NULL, PAL_T("message"), MI_PROMPTTYPE_NORMAL, Test1_Operation_WriteErrorCallback);
                    callbacks->promptUser(operation, callbacks->callbackContext, PAL_T("message"), MI_PROMPTTYPE_NORMAL, Test1_Operation_WriteErrorCallback);
                }

                callbacks->instanceResult(operation, NULL, instance, MI_FALSE, MI_RESULT_OK, NULL, NULL, flags & MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS?ResultAcknowledgement:NULL);
                callbacks->instanceResult(operation, callbacks->callbackContext, instance, MI_FALSE, MI_RESULT_OK, NULL, NULL, flags & MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS?ResultAcknowledgement:NULL);
            }
            else
            {
                g_test1_GetInstance.commonData.resultCode = MI_RESULT_SERVER_LIMITS_EXCEEDED;
                callbacks->instanceResult(operation, callbacks->callbackContext, NULL, MI_FALSE, MI_RESULT_SERVER_LIMITS_EXCEEDED, NULL, NULL, flags & MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS?ResultAcknowledgement:NULL);
            }
            MI_Application_Close(&application);
        }
        else
        {
            g_test1_GetInstance.commonData.resultCode = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            callbacks->instanceResult(operation, callbacks->callbackContext, NULL, MI_FALSE, MI_RESULT_SERVER_LIMITS_EXCEEDED, NULL, NULL, flags & MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS?ResultAcknowledgement:NULL);
        }
    }
}

MI_EXTERN_C  void MI_CALL Test1_Session_ModifyInstance(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_     const MI_Instance *inboundInstance,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation)
{
    Test1_Session_GetInstance(session, flags, options, namespaceName, inboundInstance, callbacks, operation);
}
MI_EXTERN_C  void MI_CALL Test1_Session_CreateInstance(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_     const MI_Instance *inboundInstance,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation)
{
    Test1_Session_GetInstance(session, flags, options, namespaceName, inboundInstance, callbacks, operation);
}
MI_EXTERN_C  void MI_CALL Test1_Session_DeleteInstance(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_     const MI_Instance *inboundInstance,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation)
{
    Test1_Session_GetInstance(session, flags, options, namespaceName, inboundInstance, callbacks, operation);
}

MI_EXTERN_C MI_Result MI_CALL Test1_Operation_StreamedParameter_Callback(
    _In_ MI_Operation *operation)
{
    struct _Test1_Invoke *testData = (struct _Test1_Invoke*) operation->reserved2;
    if (++testData->streamResultCount == 5)
    {
        testData->commonData.callbacks.instanceResult(operation, testData->commonData.callbacks.callbackContext, NULL, MI_FALSE, MI_RESULT_OK, NULL, NULL, testData->commonData.flags & MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS?ResultAcknowledgement:NULL);
    }
    else
    {
        MI_Value value;
        value.string = (MI_Char*) PAL_T("My streamed data");
        testData->commonData.callbacks.streamedParameterResult(operation, testData->commonData.callbacks.callbackContext, PAL_T("parameterName"), MI_STRING, &value, Test1_Operation_StreamedParameter_Callback);
    }
    return MI_RESULT_OK;
}
MI_EXTERN_C void MI_CALL Test1_Session_Invoke(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_z_     const MI_Char * className,
    _In_z_     const MI_Char * methodName,
    _In_opt_ const MI_Instance *inboundInstance,
    _In_opt_ const MI_Instance *inboundProperties,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation)
{
    memset(&g_test1_Invoke, 0, sizeof(g_test1_Invoke));
    if (NitsAssert(session!=NULL, PAL_T("PH Test1: Invoke: session parameter not present")) &&
        NitsAssert(className!=NULL, PAL_T("PH Test1: Invoke: className parameter not present")) &&
        NitsAssert(methodName!=NULL, PAL_T("PH Test1: Invoke: methodName parameter not present")) &&
        NitsAssert(operation!=NULL, PAL_T("PH Test1: Invoke: operation out parameter not present")) &&
        NitsAssert(callbacks!=NULL, PAL_T("PH Test1: Invoke: callbacks parameter not present and should always be async")) &&
        NitsAssert(callbacks->instanceResult!=NULL, PAL_T("PH Test1: Invoke: instanceResult callback not present and should always be async")))
    {
        MI_Application application;
        MI_Instance *instance;
        operation->ft = &g_Test1_operationFT;
        operation->reserved1 = Test1_Operation_InvokeInstance;
        operation->reserved2 = (ptrdiff_t) &g_test1_Invoke;
        memset(&g_test1_Invoke, 0, sizeof(g_test1_Invoke));
        g_test1_Invoke.commonData.callbacks = *callbacks;
        g_test1_Invoke.commonData.flags = flags;

        if (MI_Application_Initialize(0, NULL, NULL, &application) == MI_RESULT_OK)
        {
            if (MI_Application_NewInstance(&application, PAL_T("test"), NULL, &instance) == MI_RESULT_OK)
            {
                g_test1_Invoke.commonData.resultInstance =  instance;

                if (callbacks->writeMessage)
                {
                    callbacks->writeMessage(operation, callbacks->callbackContext, MI_WRITEMESSAGE_CHANNEL_WARNING, PAL_T("Hello world"));
                }
                if (callbacks->writeError)
                {
                    callbacks->writeError(operation, callbacks->callbackContext, NULL, Test1_Operation_WriteErrorCallback);
                    callbacks->writeError(operation, callbacks->callbackContext, NULL, Test1_Operation_WriteErrorCallback);
                }
                if (callbacks->writeProgress)
                {
                    callbacks->writeProgress(operation, callbacks->callbackContext, PAL_T("activity"), PAL_T("current operation"), PAL_T("status description"), 42, 45);
                }
                if (callbacks->promptUser)
                {
                    callbacks->promptUser(operation, callbacks->callbackContext, PAL_T("message"), MI_PROMPTTYPE_NORMAL, Test1_Operation_WriteErrorCallback);
                    callbacks->promptUser(operation, callbacks->callbackContext, PAL_T("message"), MI_PROMPTTYPE_CRITICAL, Test1_Operation_WriteErrorCallback);
                }
                if (callbacks->streamedParameterResult)
                {
                    MI_Value value;
                    value.string = (MI_Char*) PAL_T("My streamed data");
                    callbacks->streamedParameterResult(operation, callbacks->callbackContext, PAL_T("parameterName"), MI_STRING, &value, Test1_Operation_StreamedParameter_Callback);
                }
                else
                {
                    callbacks->instanceResult(operation, callbacks->callbackContext, instance, MI_FALSE, MI_RESULT_OK, NULL, NULL, flags & MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS?ResultAcknowledgement:NULL);
                }
            }
            else
            {
                g_test1_Invoke.commonData.resultCode = MI_RESULT_SERVER_LIMITS_EXCEEDED;
                callbacks->instanceResult(operation, callbacks->callbackContext, NULL, MI_FALSE, MI_RESULT_SERVER_LIMITS_EXCEEDED, NULL, NULL, flags & MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS?ResultAcknowledgement:NULL);
            }
            MI_Application_Close(&application);
        }
        else
        {
            g_test1_Invoke.commonData.resultCode = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            callbacks->instanceResult(operation, callbacks->callbackContext, NULL, MI_FALSE, MI_RESULT_SERVER_LIMITS_EXCEEDED, NULL, NULL, flags & MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS?ResultAcknowledgement:NULL);
        }
    }
}

MI_EXTERN_C void MI_CALL Test1_Session_EnumerateInstances(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_z_ const MI_Char * className,
             MI_Boolean keysOnly,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation)
{
    memset(&g_test1_EnumerateInstances, 0, sizeof(g_test1_EnumerateInstances));
    g_test1_EnumerateInstances.commonData.flags = flags;
    if (callbacks)
    {
        g_test1_EnumerateInstances.commonData.callbacks =  *callbacks;
    }

    if (!NitsAssert(session != NULL, PAL_T("session is null")) ||
        !NitsAssert(flags & MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, PAL_T("Should always get a manual ack request")) ||
        !NitsAssert(callbacks != NULL, PAL_T("should be async callbacks")) ||
        !NitsAssert(callbacks->instanceResult != NULL, PAL_T("instanceResult callback NULL")) ||
        !NitsAssert(operation != NULL, PAL_T("[out] operation is NULL")) ||
        !NitsAssert(className != NULL, PAL_T("class name should be present")))
    {
        g_test1_GetInstance.commonData.resultCode = MI_RESULT_INVALID_PARAMETER;
        callbacks->instanceResult(operation, callbacks->callbackContext, NULL, MI_FALSE, MI_RESULT_INVALID_PARAMETER, NULL, NULL, ResultAcknowledgement);
        return;
    }

    operation->ft = &g_Test1_operationFT;
    operation->reserved1 = Test1_Operation_EnumerateInstance;
    operation->reserved2 = (ptrdiff_t) &g_test1_EnumerateInstances;
    g_test1_EnumerateInstances.commonData.operation = *operation;

    g_test1_EnumerateInstances.commonData.resultCode = MI_RESULT_OK;

    if (Tcscmp(className, PAL_T("NoResult"))!=0)
    {
        MI_Application application;
        MI_Instance *instance;
        if (MI_Application_Initialize(0, NULL, NULL, &application) != MI_RESULT_OK)
        {
            g_test1_EnumerateInstances.commonData.resultCode = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            callbacks->instanceResult(operation, callbacks->callbackContext, NULL, MI_FALSE, MI_RESULT_SERVER_LIMITS_EXCEEDED, NULL, NULL, ResultAcknowledgement);
            return;
        }

        if (MI_Application_NewInstance(&application, className, NULL, &instance) != MI_RESULT_OK)
        {
            g_test1_EnumerateInstances.commonData.resultCode = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            callbacks->instanceResult(operation, callbacks->callbackContext, NULL, MI_FALSE, MI_RESULT_SERVER_LIMITS_EXCEEDED, NULL, NULL, ResultAcknowledgement);
            MI_Application_Close(&application);
            return;
        }
    
        g_test1_EnumerateInstances.commonData.resultInstance =  instance;
        MI_Application_Close(&application);
    }

    if (callbacks->writeMessage)
    {
        callbacks->writeMessage(operation, NULL, MI_WRITEMESSAGE_CHANNEL_WARNING, PAL_T("Hello world"));
        callbacks->writeMessage(operation, callbacks->callbackContext, MI_WRITEMESSAGE_CHANNEL_WARNING, PAL_T("Hello world"));
    }
    if (callbacks->writeError)
    {
        callbacks->writeError(operation, NULL, NULL, Test1_Operation_WriteErrorCallback);
        callbacks->writeError(operation, callbacks->callbackContext, NULL, Test1_Operation_WriteErrorCallback);
    }
    if (callbacks->writeProgress)
    {
        callbacks->writeProgress(operation, NULL, PAL_T("activity"), PAL_T("current operation"), PAL_T("status description"), 42, 45);
        callbacks->writeProgress(operation, callbacks->callbackContext, PAL_T("activity"), PAL_T("current operation"), PAL_T("status description"), 42, 45);
    }

    if (Tcscmp(className, PAL_T("NoResult"))==0)
    {
        g_test1_EnumerateInstances.numberOfResultsLeft = 0;
        callbacks->instanceResult(operation, callbacks->callbackContext, NULL, MI_FALSE, MI_RESULT_OK, NULL, NULL, ResultAcknowledgement);
    }
    else
    {
        /* deliver first item.  Next item would need to be sent on ack */
        g_test1_EnumerateInstances.numberOfResultsLeft = 9;
        callbacks->instanceResult(operation, callbacks->callbackContext, g_test1_EnumerateInstances.commonData.resultInstance, MI_TRUE, MI_RESULT_OK, NULL, NULL, ResultAcknowledgement);
    }
}
MI_EXTERN_C void MI_CALL Test1_Session_QueryInstances(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_opt_z_ const MI_Char * filterDialect,
    _In_opt_z_ const MI_Char * filter,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation)
{
    memset(&g_test1_EnumerateInstances, 0, sizeof(g_test1_EnumerateInstances));
    g_test1_EnumerateInstances.commonData.flags = flags;
    if (callbacks)
    {
        g_test1_EnumerateInstances.commonData.callbacks =  *callbacks;
    }

    if (!NitsAssert(session != NULL, PAL_T("session is null")) ||
        !NitsAssert(flags & MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, PAL_T("Should always get a manual ack request")) ||
        !NitsAssert(callbacks != NULL, PAL_T("should be async callbacks")) ||
        !NitsAssert(callbacks->instanceResult != NULL, PAL_T("instanceResult callback NULL")) ||
        !NitsAssert(operation != NULL, PAL_T("[out] operation is NULL")))
    {
        g_test1_GetInstance.commonData.resultCode = MI_RESULT_INVALID_PARAMETER;
        callbacks->instanceResult(operation, callbacks->callbackContext, NULL, MI_FALSE, MI_RESULT_INVALID_PARAMETER, NULL, NULL, ResultAcknowledgement);
        return;
    }

    operation->ft = &g_Test1_operationFT;
    operation->reserved1 = Test1_Operation_EnumerateInstance;
    operation->reserved2 = (ptrdiff_t) &g_test1_EnumerateInstances;
    g_test1_EnumerateInstances.commonData.operation = *operation;

    g_test1_EnumerateInstances.commonData.resultCode = MI_RESULT_OK;

    MI_Application application;
    MI_Instance *instance;
    if (MI_Application_Initialize(0, NULL, NULL, &application) != MI_RESULT_OK)
    {
        g_test1_EnumerateInstances.commonData.resultCode = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        callbacks->instanceResult(operation, callbacks->callbackContext, NULL, MI_FALSE, MI_RESULT_SERVER_LIMITS_EXCEEDED, NULL, NULL, ResultAcknowledgement);
        return;
    }

    if (MI_Application_NewInstance(&application, PAL_T("className"), NULL, &instance) != MI_RESULT_OK)
    {
        g_test1_EnumerateInstances.commonData.resultCode = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        callbacks->instanceResult(operation, callbacks->callbackContext, NULL, MI_FALSE, MI_RESULT_SERVER_LIMITS_EXCEEDED, NULL, NULL, ResultAcknowledgement);
        MI_Application_Close(&application);
        return;
    }
    
    g_test1_EnumerateInstances.commonData.resultInstance =  instance;
    MI_Application_Close(&application);

    if (callbacks->writeMessage)
    {
        callbacks->writeMessage(operation, NULL, MI_WRITEMESSAGE_CHANNEL_WARNING, PAL_T("Hello world"));
        callbacks->writeMessage(operation, callbacks->callbackContext, MI_WRITEMESSAGE_CHANNEL_WARNING, PAL_T("Hello world"));
    }
    if (callbacks->writeError)
    {
        callbacks->writeError(operation, NULL, NULL, Test1_Operation_WriteErrorCallback);
        callbacks->writeError(operation, callbacks->callbackContext,  NULL, Test1_Operation_WriteErrorCallback);
    }
    if (callbacks->writeProgress)
    {
        callbacks->writeProgress(operation, NULL, PAL_T("activity"), PAL_T("current operation"), PAL_T("status description"), 42, 45);
        callbacks->writeProgress(operation, callbacks->callbackContext, PAL_T("activity"), PAL_T("current operation"), PAL_T("status description"), 42, 45);
    }

    /* deliver first item.  Next item would need to be sent on ack */
    g_test1_EnumerateInstances.numberOfResultsLeft = 9;
    callbacks->instanceResult(operation, callbacks->callbackContext, g_test1_EnumerateInstances.commonData.resultInstance, MI_TRUE, MI_RESULT_OK, NULL, NULL, ResultAcknowledgement);
}

MI_EXTERN_C void MI_CALL Test1_Session_AssociatorInstances(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_     const MI_Instance *instanceKey,
    _In_opt_z_ const MI_Char * assocClass,
    _In_opt_z_ const MI_Char * resultClass,
    _In_opt_z_ const MI_Char * role,
    _In_opt_z_ const MI_Char * resultRole,
             MI_Boolean keysOnly,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation)
{
    Test1_Session_EnumerateInstances(session, flags, options, namespaceName, resultClass, keysOnly, callbacks, operation);
}

MI_EXTERN_C void MI_CALL Test1_Session_ReferenceInstances(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_     const MI_Instance *instanceKey,
    _In_opt_z_ const MI_Char * resultClass,
    _In_opt_z_ const MI_Char * role,
             MI_Boolean keysOnly,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation)
{
    Test1_Session_EnumerateInstances(session, flags, options, namespaceName, resultClass, keysOnly, callbacks, operation);
}


MI_EXTERN_C void MI_CALL Test1_Session_GetClass(
    _In_       MI_Session *session,
               MI_Uint32 flags,
    _In_opt_   MI_OperationOptions *options,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_z_     const MI_Char *className,
    _In_opt_   MI_OperationCallbacks *callbacks,
    _Out_      MI_Operation *operation)
{
    memset(&g_test1_GetInstance, 0, sizeof(g_test1_GetInstance));
    g_test1_GetInstance.commonData.flags = flags;
    operation->ft = &g_Test1_operationFT;
    operation->reserved1 = Test1_Operation_GetClass;
    operation->reserved2 = (ptrdiff_t) &g_test1_GetInstance;
    g_test1_GetInstance.commonData.operation = *operation;

    if (callbacks)
    {
        g_test1_GetInstance.commonData.callbacks =  *callbacks;
    }
    else return;

    if (NitsCompare(Class_New(&MyClass_rtti, namespaceName, PAL_T("server"), &g_test1_GetInstance.commonData.resultClass), MI_RESULT_OK, PAL_T("Class_New should succeed")))
    {
        callbacks->classResult(operation, callbacks->callbackContext, g_test1_GetInstance.commonData.resultClass, MI_FALSE, MI_RESULT_OK, NULL, NULL, ResultAcknowledgement);
    }
    else
    {
        callbacks->classResult(operation, callbacks->callbackContext, NULL, MI_FALSE, MI_RESULT_SERVER_LIMITS_EXCEEDED, NULL, NULL, ResultAcknowledgement);
    }
}

MI_EXTERN_C void MI_CALL Test1_Session_EnumerateClasses(
    _In_       MI_Session *session,
               MI_Uint32 flags,
    _In_opt_   MI_OperationOptions *options,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_opt_z_ const MI_Char *className,
               MI_Boolean classNamesOnly,
    _In_opt_   MI_OperationCallbacks *callbacks,
    _Out_      MI_Operation *operation)
{
    memset(&g_test1_EnumerateInstances, 0, sizeof(g_test1_EnumerateInstances));
    g_test1_EnumerateInstances.commonData.flags = flags;
    operation->ft = &g_Test1_operationFT;
    operation->reserved1 = Test1_Operation_EnumerateClasses;
    operation->reserved2 = (ptrdiff_t) &g_test1_EnumerateInstances;
    if (callbacks)
    {
        g_test1_EnumerateInstances.commonData.callbacks =  *callbacks;
    }
    else return;

    if (!NitsAssert(session != NULL, PAL_T("session is null")) ||
        !NitsAssert(flags & MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, PAL_T("Should always get a manual ack request")) ||
        !NitsAssert(callbacks != NULL, PAL_T("should be async callbacks")) ||
        !NitsAssert(callbacks->classResult != NULL, PAL_T("instanceResult callback NULL")) ||
        !NitsAssert(operation != NULL, PAL_T("[out] operation is NULL")))
    {
        g_test1_GetInstance.commonData.resultCode = MI_RESULT_INVALID_PARAMETER;
        callbacks->classResult(operation, callbacks->callbackContext, NULL, MI_FALSE, MI_RESULT_INVALID_PARAMETER, NULL, NULL, ResultAcknowledgement);
        return;
    }

    g_test1_EnumerateInstances.commonData.operation = *operation;

    g_test1_EnumerateInstances.commonData.resultCode = MI_RESULT_OK;

    if (Class_New(&MyClass_rtti, namespaceName, PAL_T("foo"),  &g_test1_EnumerateInstances.commonData.resultClass) != MI_RESULT_OK)
    {
        g_test1_EnumerateInstances.commonData.resultCode = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        callbacks->classResult(operation, callbacks->callbackContext, NULL, MI_FALSE, MI_RESULT_SERVER_LIMITS_EXCEEDED, NULL, NULL, ResultAcknowledgement);
        return;
    }

    /* deliver first item.  Next item would need to be sent on ack */
    g_test1_EnumerateInstances.numberOfResultsLeft = 9;
    callbacks->classResult(operation, callbacks->callbackContext, g_test1_EnumerateInstances.commonData.resultClass, MI_TRUE, MI_RESULT_OK, NULL, NULL, ResultAcknowledgement);
}

MI_EXTERN_C void MI_CALL Test1_Session_Subscribe(
    _In_       MI_Session *session,
               MI_Uint32 flags,
    _In_opt_   MI_OperationOptions *options,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_opt_z_ const MI_Char *queryDialect,
    _In_opt_z_ const MI_Char *queryExpression,
    _In_opt_   const MI_SubscriptionDeliveryOptions *deliverOptions,
    _In_opt_   MI_OperationCallbacks *callbacks,
    _Out_      MI_Operation *operation)
{
    memset(&g_test1_EnumerateInstances, 0, sizeof(g_test1_EnumerateInstances));
    g_test1_EnumerateInstances.commonData.flags = flags;
    if (callbacks)
    {
        g_test1_EnumerateInstances.commonData.callbacks =  *callbacks;
    }

    if (!NitsAssert(session != NULL, PAL_T("session is null")) ||
        !NitsAssert(flags & MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, PAL_T("Should always get a manual ack request")) ||
        !NitsAssert(callbacks != NULL, PAL_T("should be async callbacks")) ||
        !NitsAssert(callbacks->indicationResult != NULL, PAL_T("instanceResult callback NULL")) ||
        !NitsAssert(operation != NULL, PAL_T("[out] operation is NULL"))
        )
    {
        g_test1_GetInstance.commonData.resultCode = MI_RESULT_INVALID_PARAMETER;
        callbacks->indicationResult(operation, callbacks->callbackContext, NULL, NULL, NULL, MI_FALSE, MI_RESULT_INVALID_PARAMETER, NULL, NULL, ResultAcknowledgement);
        return;
    }

    operation->ft = &g_Test1_operationFT;
    operation->reserved1 = Test1_Operation_Subscribe;
    operation->reserved2 = (ptrdiff_t) &g_test1_EnumerateInstances;
    g_test1_EnumerateInstances.commonData.operation = *operation;

    g_test1_EnumerateInstances.commonData.resultCode = MI_RESULT_OK;

    MI_Application application;
    MI_Instance *instance;
    if (MI_Application_Initialize(0, NULL, NULL, &application) != MI_RESULT_OK)
    {
        g_test1_EnumerateInstances.commonData.resultCode = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        callbacks->indicationResult(operation, callbacks->callbackContext, NULL, NULL, NULL, MI_FALSE, MI_RESULT_SERVER_LIMITS_EXCEEDED, NULL, NULL, ResultAcknowledgement);
        return;
    }

    if (MI_Application_NewInstance(&application, PAL_T("indication"), NULL, &instance) != MI_RESULT_OK)
    {
        g_test1_EnumerateInstances.commonData.resultCode = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        callbacks->indicationResult(operation, callbacks->callbackContext, NULL, NULL, NULL, MI_FALSE, MI_RESULT_SERVER_LIMITS_EXCEEDED, NULL, NULL, ResultAcknowledgement);
        MI_Application_Close(&application);
        return;
    }
    
    g_test1_EnumerateInstances.commonData.resultInstance =  instance;
    MI_Application_Close(&application);

    /* deliver first item.  Next item would need to be sent on ack */
    g_test1_EnumerateInstances.numberOfResultsLeft = 9;
    callbacks->indicationResult(operation, callbacks->callbackContext, g_test1_EnumerateInstances.commonData.resultInstance, PAL_T("bookmark"), PAL_T("machineID"), MI_TRUE, MI_RESULT_OK, NULL, NULL, ResultAcknowledgement);
}

MI_EXTERN_C  void MI_CALL Test1_Session_TestConnection(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation)
{
    memset(&g_test1_GetInstance, 0, sizeof(g_test1_GetInstance));
    g_test1_GetInstance.commonData.flags = flags;
    operation->ft = &g_Test1_operationFT;
    operation->reserved1 = Test1_Operation_GetClass;
    operation->reserved2 = (ptrdiff_t) &g_test1_GetInstance;
    g_test1_GetInstance.commonData.operation = *operation;

    if (callbacks)
    {
        g_test1_GetInstance.commonData.callbacks =  *callbacks;
    
        callbacks->instanceResult(operation, callbacks->callbackContext, NULL, MI_FALSE, MI_RESULT_OK, NULL, NULL, ResultAcknowledgement);
    }
    else
    {
        memset(operation, 0, sizeof(*operation));
    }

}

MI_EXTERN_C MI_Result MI_CALL Test1_Operation_Close(
    _In_      MI_Operation *operation)
{
    return MI_RESULT_OK;
}

MI_EXTERN_C PAL_Uint32 THREAD_API PostResultOnDifferentThread(void* )
{
    Sleep_Milliseconds(1000);

    g_test1_GetInstance.commonData.callbacks.instanceResult(&g_test1_GetInstance.commonData.operation, g_test1_GetInstance.commonData.callbacks.callbackContext, g_test1_GetInstance.commonData.resultInstance, MI_FALSE, g_test1_GetInstance.commonData.resultCode, NULL, NULL, ResultAcknowledgement);

    return 0;
}

MI_EXTERN_C void DeliverResultsDifferentThread(Test1_CommonData *data)
{
    if (Thread_CreateDetached(PostResultOnDifferentThread, NULL, NULL))
    {
        NitsAssert(FALSE, PAL_T("threadpool timer failed to create"));
        data->callbacks.instanceResult(&g_test1_GetInstance.commonData.operation, data->callbacks.callbackContext, NULL, MI_FALSE, MI_RESULT_FAILED, NULL, NULL, ResultAcknowledgement);
        return;
    }
}

MI_EXTERN_C MI_Result MI_CALL Test1_Operation_Cancel(
    _In_      MI_Operation *operation,
              MI_CancelationReason reason)
{
    if ((operation->reserved1 == Test1_Operation_GetInstance) &&
        (g_test1_GetInstance.testDetails == _Test1_GetInstance::NoResult))
    {
        g_test1_GetInstance.commonData.callbacks.instanceResult(operation, g_test1_GetInstance.commonData.callbacks.callbackContext, NULL, MI_FALSE, MI_RESULT_FAILED, PAL_T("Operation cancelled"), NULL, ResultAcknowledgement);
    }
    else if ((operation->reserved1 == Test1_Operation_GetInstance) &&
        (g_test1_GetInstance.testDetails == _Test1_GetInstance::NoResultDifferentThread))
    {
        g_test1_GetInstance.commonData.resultCode = MI_RESULT_FAILED;
        g_test1_GetInstance.commonData.resultInstance =  NULL;
        g_test1_GetInstance.commonData.operation = *operation;
        DeliverResultsDifferentThread(&g_test1_GetInstance.commonData);
    }
    return MI_RESULT_OK;
}

MI_EXTERN_C MI_Result MI_CALL Test1_HostedProvider_Close(
        _In_  MI_HostedProvider *hostedProvider)
{
    NitsAssert(hostedProvider != NULL, PAL_T("Test1 HP Close: hostedProvider NULL"));
    NitsAssert(hostedProvider->reserved1 == 0, PAL_T("Test1 HP Close: reserved1 not 0"));
    NitsAssert(hostedProvider->reserved2 == 0, PAL_T("Test1 HP Close: reserved1 not 0"));
    return MI_RESULT_OK;
}
MI_EXTERN_C MI_Result MI_CALL Test1_OperationOptions_SetCustomOption(
    _In_   MI_OperationOptions *options,
    _In_z_ const MI_Char *optionName,
           MI_Type valueType,
    _In_   const MI_Value *value,
           MI_Boolean mustComply,
           MI_Uint32 flags)
{
    if (TestSystem::ShouldFault(TLINE))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    else
    {
        return MI_RESULT_OK;
    }
}
MI_EXTERN_C MI_Result MI_CALL Test1_OperationOptions_SetNumber(
    _In_   MI_OperationOptions *options,
    _In_z_ const MI_Char *optionName,
    _In_   MI_Uint32 value,
           MI_Uint32 flags)
{
    if (TestSystem::ShouldFault(TLINE))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    else
    {
        return MI_RESULT_OK;
    }
}

MI_EXTERN_C MI_Result MI_CALL Test1_OperationOptions_SetString(
    _In_   MI_OperationOptions *options,
    _In_z_ const MI_Char *optionName,
    _In_z_ const MI_Char *value,
           MI_Uint32 flags)
{
    if (TestSystem::ShouldFault(TLINE))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    else
    {
        return MI_RESULT_OK;
    }
}
MI_EXTERN_C void MI_CALL Test1_OperationOptions_Delete(
    _In_ MI_OperationOptions *options)
{
}

MI_EXTERN_C MI_Result MI_CALL Test_Application_NewOperationOptions(
    _In_  MI_Application *application,
          MI_Boolean customOptionsMustUnderstand,
    _Out_ MI_OperationOptions *options)
{
    options->ft = &g_testOperationOptionsFT;
    options->reserved1 = 0;
    options->reserved2 = 0;
    if (TestSystem::ShouldFault(TLINE))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    else
    {
        return MI_RESULT_OK;
    }
}

MI_EXTERN_C MI_Result MI_CALL Test1_DestinationOptions_AddCredentials(
    _In_     MI_DestinationOptions *options,
    _In_z_     const MI_Char *optionName,
    _In_ const MI_UserCredentials *creds,
           MI_Uint32 flags)
{
    if (TestSystem::ShouldFault(TLINE))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    else
    {
        return MI_RESULT_OK;
    }
}

MI_EXTERN_C MI_Result MI_CALL Test1_DestinationOptions_SetNumber(
    _In_ MI_DestinationOptions *options,
    _In_z_ const MI_Char *optionName,
    _In_ MI_Uint32 value,
           MI_Uint32 flags)
{
    if (TestSystem::ShouldFault(TLINE))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    else
    {
        return MI_RESULT_OK;
    }
}

MI_EXTERN_C MI_Result MI_CALL Test1_DestinationOptions_SetString(
    _In_ MI_DestinationOptions *options,
    _In_z_ const MI_Char *optionName,
    _In_z_ const MI_Char *value,
           MI_Uint32 flags)
{
    if (TestSystem::ShouldFault(TLINE))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    else
    {
        return MI_RESULT_OK;
    }
}

MI_EXTERN_C void MI_CALL Test1_DestinationOptions_Delete(
    _In_ MI_DestinationOptions *options)
{
}

MI_EXTERN_C MI_Result  MI_CALL Test1_Application_NewDestinationOptions(
    _In_  MI_Application *application,
    _Out_ MI_DestinationOptions *options)
{
    options->ft = &g_testDestinationOptionsFT;
    options->reserved1 = 0;
    options->reserved2 = 0;
    if (TestSystem::ShouldFault(TLINE))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    else
    {
        return MI_RESULT_OK;
    }
}

MI_EXTERN_C MI_Result  MI_CALL Test1_SubscriptionDeliveryOptions_Create(
    _In_  MI_Application *application,
    _In_  MI_SubscriptionDeliveryType deliveryType,
    _Out_ MI_SubscriptionDeliveryOptions *options)
{
    if (TestSystem::ShouldFault(TLINE))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    else
    {
        options->ft = &g_testSubscriptionDeliveryOptionsFT;
        return MI_RESULT_OK;
    }

}

MI_EXTERN_C MI_Result MI_CALL Test1_SubscriptionDeliveryOptions_Delete(
    _In_ MI_SubscriptionDeliveryOptions *options)
{
    return MI_RESULT_OK;
}

MI_EXTERN_C MI_Result MI_CALL Test1_SubscriptionDeliveryOptions_SetString(
    _In_   MI_SubscriptionDeliveryOptions *options,
    _In_z_ const MI_Char *optionName,
    _In_z_ const MI_Char *value,
            MI_Uint32 flags)
{
    if (TestSystem::ShouldFault(TLINE))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    else
    {
        return MI_RESULT_OK;
    }
}

MI_EXTERN_C MI_Result MI_CALL Test1_SubscriptionDeliveryOptions_SetNumber(
    _In_   MI_SubscriptionDeliveryOptions *options,
    _In_z_ const MI_Char *optionName,
    _In_   MI_Uint32 value,
            MI_Uint32 flags)
{
    if (TestSystem::ShouldFault(TLINE))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    else
    {
        return MI_RESULT_OK;
    }
}

MI_EXTERN_C MI_Result MI_CALL Test1_SubscriptionDeliveryOptions_SetDateTime(
    _In_   MI_SubscriptionDeliveryOptions *options,
    _In_z_ const MI_Char *optionName,
    _In_   const MI_Datetime *value,
            MI_Uint32 flags)
{
    if (TestSystem::ShouldFault(TLINE))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    else
    {
        return MI_RESULT_OK;
    }
}

MI_EXTERN_C MI_Result MI_CALL Test1_SubscriptionDeliveryOptions_SetInterval(
    _In_   MI_SubscriptionDeliveryOptions *options,
    _In_z_ const MI_Char *optionName,
    _In_   const MI_Interval *value,
            MI_Uint32 flags)
{
    if (TestSystem::ShouldFault(TLINE))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    else
    {
        return MI_RESULT_OK;
    }
}

MI_EXTERN_C MI_Result MI_CALL Test1_SubscriptionDeliveryOptions_AddCredentials(
    _In_   MI_SubscriptionDeliveryOptions *options,
    _In_z_ const MI_Char *optionName,
    _In_   const MI_UserCredentials *credentials,
            MI_Uint32 flags)
{
    if (TestSystem::ShouldFault(TLINE))
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    else
    {
        return MI_RESULT_OK;
    }
}

const MI_ApplicationFT g_Test1_applicationFT = { 
    Test1_Application_Close, 
    Test1_Application_NewSession, 
    Test1_Application_NewHostedProvider,
    /*NewInstance -- DO NOT IMPLEMENT*/NULL,
    Test1_Application_NewDestinationOptions,
    Test_Application_NewOperationOptions,
    Test1_SubscriptionDeliveryOptions_Create
};

const MI_ApplicationFT g_Test2_applicationFT = { 
    Test2_Application_Close, 
    Test2_Application_NewSession, 
    NULL,
    NULL,
    Test1_Application_NewDestinationOptions,
    NULL
};

const MI_SessionFT g_Test1_sessionFT = {
    Test1_Session_Close,
    /*Session_GetApplication*/NULL,
    Test1_Session_GetInstance,
    Test1_Session_ModifyInstance,
    Test1_Session_CreateInstance,
    Test1_Session_DeleteInstance,
    Test1_Session_Invoke,
    Test1_Session_EnumerateInstances,
    Test1_Session_QueryInstances,
    Test1_Session_AssociatorInstances,
    Test1_Session_ReferenceInstances,
    Test1_Session_Subscribe,
    Test1_Session_GetClass,
    Test1_Session_EnumerateClasses,
    Test1_Session_TestConnection
};
const MI_SessionFT g_Test2_sessionFT = {
    Test1_Session_Close,
    /*Session_GetApplication*/NULL,
    NULL,
    NULL,
    /*Session_CreateInstance*/NULL,
    /*Session_DeleteInstance*/NULL,
    NULL,
    /*Session_EnumerateInstances*/NULL,
    /*Session_AssociatorInstances*/NULL,
    /*Session_ReferenceInstances*/NULL,
    /*Session_Subscribe*/NULL,
    /*Session_GetClass*/NULL,
    /*Session_EnumerateClasses*/NULL
};


const MI_OperationFT g_Test1_operationFT = {
    Test1_Operation_Close,  /* TODO: REQUIRED */
    Test1_Operation_Cancel, /* TODO: REQUIRED */
    /*OperationGetSession*/NULL, /* Nothing else needed from transport */
    /*OperationGetInstance*/NULL,
    /*OperationGetIndication*/NULL,
    /*OperationGetClass*/NULL
};

const MI_HostedProviderFT g_Test1_hostedProvider = {
    Test1_HostedProvider_Close,
    /* Application --- NOT NEEDED*/ NULL
};

const MI_DestinationOptionsFT g_testDestinationOptionsFT = 
{
    Test1_DestinationOptions_Delete,
    Test1_DestinationOptions_SetString,
    Test1_DestinationOptions_SetNumber,
    Test1_DestinationOptions_AddCredentials
};

const MI_OperationOptionsFT g_testOperationOptionsFT =
{
    Test1_OperationOptions_Delete,
    Test1_OperationOptions_SetString,
    Test1_OperationOptions_SetNumber,
    Test1_OperationOptions_SetCustomOption
};

const MI_SubscriptionDeliveryOptionsFT g_testSubscriptionDeliveryOptionsFT =
{
    Test1_SubscriptionDeliveryOptions_SetString,
    Test1_SubscriptionDeliveryOptions_SetNumber,
    Test1_SubscriptionDeliveryOptions_SetDateTime,
    Test1_SubscriptionDeliveryOptions_SetInterval,
    Test1_SubscriptionDeliveryOptions_AddCredentials,
    Test1_SubscriptionDeliveryOptions_Delete
} ;

