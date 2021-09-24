/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "miapi_common.h"
#include "Application.h"
#include "Session.h"
#include "Operation.h"
#include "SafeHandle.h"
#include <MI.h>
#include <pal/lock.h>
#include <pal/format.h>
#include "Options.h"
#include <base/log.h>

/* Defined for real at bottom of file */
extern const MI_OperationFT g_operationFT;
extern const MI_OperationFT g_operationFT_Failed;
extern const MI_OperationFT g_operationFT_OOM;
extern const MI_OperationFT g_operationFT_InvalidParameter;
extern const MI_OperationFT g_operationFT_NotSupported;
extern const MI_OperationFT g_operationFT_AccessDenied;
extern const MI_SessionFT g_sessionFT;

typedef enum
{
    OPERATION_INSTANCE,
    OPERATION_CLASS,
    OPERATION_INDICATION
} OPERATION_TYPE;

typedef struct _OperationObject OperationObject;
struct _OperationObject
{
    /* Linked list for child session operations.  Includes clients operation handle */
    ChildListNode operationNode;

    /* Type of operation */
    OPERATION_TYPE operationType;

    /* Copy of parent session so we can copy it */
    MI_Session clientSession;
    MI_Session *clientSessionPtr;   /*Pointer for clients session for logging purposes only */

    MI_Operation *clientOperationPtr; /*Pointer for client operation for logging purposes only */

    /* protocol handler operation */
    MI_Operation protocolHandlerOperation;

    /* client callbacks */
    MI_OperationCallbacks callbacks;

    /* Does client want manual or auto acknowledgement of results */
    MI_Boolean manualAck;

    volatile ptrdiff_t cancelled;

    /* Protocol handler instance result acknowledgement */
    MI_Result (MI_CALL * ph_instance_resultAcknowledgement)(_In_ MI_Operation *operation);
    MI_Result (MI_CALL * ph_promptUserResult_callback)(_In_ MI_Operation *operation, MI_OperationCallback_ResponseType response);
    MI_Result (MI_CALL * ph_writeErrorResult_callback)(_In_ MI_Operation *operation, MI_OperationCallback_ResponseType response);
    MI_Result (MI_CALL * ph_streamedParameterResult_callback)(_In_ MI_Operation *operation);

    /* synchronous result location */
    const MI_Instance *instanceResult;
    const MI_Class *classResult;
    const MI_Char *bookmark;
    const MI_Char *machineID;
    MI_Boolean moreResults;
    MI_Result resultCode;
    const MI_Char *errorString;
    const MI_Instance *errorDetails;

    /* State variable to make operation synchronous */
    volatile ptrdiff_t instanceCallbackReceived;

    /* Mode for WriteError API*/
    MI_CallbackMode writeErrorMode;

    /* Mode for PromptUser API*/
    MI_CallbackMode promptUserMode;

    /* Default ack for PromptUser API*/
    MI_Boolean promptUserModeAckMode;

    /* Do we have a result that needs acknowledging */
    MI_Boolean consumedResult;

    /* Did we get the final result? Doing a wait on it so needs to be a LONG */
    volatile ptrdiff_t consumedFinalResult;

    MI_Boolean synchronousOperation;

    enum { RetrievingResults, Completed, Broken } currentState;
} ;

/* Client called result acknowledgement that needs to call into protocol handler.
 * Ack is holding a refcount so we don't need to the official thunk
 * process, we can just dig into the object and release the refcount when done. */
MI_Result MI_CALL Operation_ResultAcknowledgement(_In_ MI_Operation *operation)
{
    if (operation != NULL)
    {
        GenericHandle *genericHandle = (GenericHandle*) operation;
        OperationObject *operationObject = (OperationObject *) genericHandle->thunkHandle->u.object;
        MI_Result (MI_CALL * tmpResultAcknowledgement)(_In_ MI_Operation *operation) = operationObject->ph_instance_resultAcknowledgement;
        MI_Boolean needToAck = !operationObject->moreResults;
        MI_CLIENT_IMPERSONATION_TOKEN originalImpersonation = INVALID_HANDLE_VALUE;

        MI_Result securityCheck = Session_AccessCheck(&operationObject->clientSession, MI_T("acknowledge operation result"));
        if (securityCheck != MI_RESULT_OK)
        {
            trace_MiSession_AccessCheckFailed(__FUNCTION__, &operationObject->clientSession);
            return securityCheck;
        }
        securityCheck = Session_ImpersonateClient(&operationObject->clientSession, &originalImpersonation);
        if (securityCheck != MI_RESULT_OK)
        {
            return securityCheck;
        }

        /* Clean up state information */
        operationObject->ph_instance_resultAcknowledgement = NULL;
        operationObject->instanceResult = NULL;
        operationObject->moreResults = MI_FALSE;
        operationObject->resultCode = MI_RESULT_OK;
        operationObject->errorString = NULL;
        operationObject->errorDetails = NULL;
        operationObject->currentState = Completed;

        /* Call protocol handler version of cleanup */
        tmpResultAcknowledgement(&operationObject->protocolHandlerOperation);

        if (needToAck)
        {
            /* Ack ref-count... only release for the final result */
            ThunkHandle_Release(genericHandle->thunkHandle);
        }
        if (Session_RevertImpersonation(originalImpersonation) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return MI_RESULT_OK;
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
}

/* Client called ShouldProcess callback that needs to call into protocol handler */
MI_Result MI_CALL Operation_OperationCallback_PromptUser_Callback(
    _In_ MI_Operation *operation,
    MI_OperationCallback_ResponseType response)
{
    if (operation)
    {
        GenericHandle *genericHandle = (GenericHandle*) operation;
        ThunkHandle *thunkHandle;
        MI_CLIENT_IMPERSONATION_TOKEN originalImpersonation = INVALID_HANDLE_VALUE;

        ThunkHandle_FromGeneric_ForCompletionCallback(genericHandle, &thunkHandle);
        if(thunkHandle != NULL)
        {
            OperationObject *operationObject = (OperationObject *) thunkHandle->u.object;

            MI_Result securityCheck = Session_AccessCheck(&operationObject->clientSession, MI_T("call promptUser callback"));
            if (securityCheck != MI_RESULT_OK)
            {
                ThunkHandle_Release(genericHandle->thunkHandle);
                trace_MiSession_AccessCheckFailed(__FUNCTION__, &operationObject->clientSession);
                return securityCheck;
            }
            securityCheck = Session_ImpersonateClient(&operationObject->clientSession, &originalImpersonation);
            if (securityCheck != MI_RESULT_OK)
            {
                ThunkHandle_Release(genericHandle->thunkHandle);
                return securityCheck;
            }

            operationObject->ph_promptUserResult_callback(&operationObject->protocolHandlerOperation, response);

            /* Releasing twice, once for the reference added in callback and other for reference added in this completion callback */
            ThunkHandle_Release(genericHandle->thunkHandle);
            ThunkHandle_Release(genericHandle->thunkHandle);

            if (Session_RevertImpersonation(originalImpersonation) != MI_RESULT_OK)
            {
                TerminateProcess(GetCurrentProcess(), -1);
            }
            return MI_RESULT_OK;
        }
        else
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
}

/* Transport callback, need to pass through to client */
void MI_CALL Operation_OperationCallback_PromptUser(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext,
    _In_z_   const MI_Char *message,
             MI_PromptType promptType,
    _In_     MI_Result (MI_CALL * promptUserResult)(_In_ MI_Operation *operation,
                                                      MI_OperationCallback_ResponseType response))
{
    if (callbackContext != NULL)
    {
        OperationObject *operationObject = (OperationObject *) callbackContext;
        GenericHandle *genericHandle = &operationObject->operationNode.clientHandle;
        MI_OperationCallback_ResponseType autoResonse =  operationObject->promptUserModeAckMode == MI_TRUE ?
                                    MI_OperationCallback_ResponseType_Yes : MI_OperationCallback_ResponseType_No;

        ThunkHandle *thunkHandle;

        ThunkHandle_FromGeneric(genericHandle, &thunkHandle); //This should be released after calling callback in callback (promptUserResult)
        if (thunkHandle != NULL)
        {
            MI_Operation *clientOperation = (MI_Operation*)genericHandle;
            MI_Boolean bExecutePromptUser = MI_TRUE;
            if(promptType == MI_PROMPTTYPE_NORMAL)
            {
                if(operationObject->promptUserMode == MI_CALLBACKMODE_REPORT)
                {
                    //Don't pass the callback to the client and default to normal behavior.
                    MI_Result impersonationResult = MI_RESULT_OK;
                    MI_CLIENT_IMPERSONATION_TOKEN currentImpersonationToken;
                    impersonationResult = Session_ImpersonateClient(&operationObject->clientSession, &currentImpersonationToken);
                    if (impersonationResult == MI_RESULT_OK)
                    {
                        operationObject->callbacks.promptUser(clientOperation, operationObject->callbacks.callbackContext, message, promptType, NULL);

                        if (Session_RevertImpersonation(currentImpersonationToken) != MI_RESULT_OK)
                        {
                            TerminateProcess(GetCurrentProcess(), -1);
                        }
                        //Do auto ack based on client's preference
                        promptUserResult(&operationObject->protocolHandlerOperation, autoResonse);
                    }
                    else
                    {
                        //TODO: Set internal state to BROKEN so MI_Operation_Close will succeed
                        operationObject->currentState = Broken;
                    }
                    bExecutePromptUser = MI_FALSE;

                    ThunkHandle_Release(thunkHandle);
                }
                else if (operationObject->promptUserMode == MI_CALLBACKMODE_IGNORE)
                {
                    //Do auto ack based on client's preference
                    bExecutePromptUser = MI_FALSE;
                    promptUserResult(&operationObject->protocolHandlerOperation, autoResonse);

                    ThunkHandle_Release(thunkHandle);
                }
            }
            //This path is for INQUIRE mode. CRITICAL is always in inquire mode.
            if( bExecutePromptUser == MI_TRUE)
            {
                MI_CLIENT_IMPERSONATION_TOKEN currentImpersonationToken;
                MI_Result impersonationResult = MI_RESULT_OK;

                operationObject->ph_promptUserResult_callback = promptUserResult;

                impersonationResult = Session_ImpersonateClient(&operationObject->clientSession, &currentImpersonationToken);

                if (impersonationResult == MI_RESULT_OK)
                {
                    operationObject->callbacks.promptUser(clientOperation, operationObject->callbacks.callbackContext, message, promptType, Operation_OperationCallback_PromptUser_Callback);

                    if (Session_RevertImpersonation(currentImpersonationToken) != MI_RESULT_OK)
                    {
                        TerminateProcess(GetCurrentProcess(), -1);
                    }
                }
                else
                {
                    //TODO: Set internal state to BROKEN so MI_Operation_Close will succeed
                    operationObject->currentState = Broken;
                }
            }
        }
    }
}

/* Client called WriteError callback that needs to call into protocol handler */
MI_Result MI_CALL Operation_OperationCallback_WriteError_Callback(_In_ MI_Operation *operation, MI_OperationCallback_ResponseType response)
{
    if (operation)
    {
        GenericHandle *genericHandle = (GenericHandle*) operation;
        ThunkHandle *thunkHandle;

        ThunkHandle_FromGeneric_ForCompletionCallback(genericHandle, &thunkHandle);
        if(thunkHandle != NULL)
        {
            OperationObject *operationObject = (OperationObject *) thunkHandle->u.object;
            MI_CLIENT_IMPERSONATION_TOKEN originalImpersonation = INVALID_HANDLE_VALUE;

            MI_Result securityCheck = Session_AccessCheck(&operationObject->clientSession, MI_T("call WriteError callback"));
            if (securityCheck != MI_RESULT_OK)
            {
                ThunkHandle_Release(genericHandle->thunkHandle);
                trace_MiSession_AccessCheckFailed(__FUNCTION__, &operationObject->clientSession);
                return securityCheck;
            }
            securityCheck = Session_ImpersonateClient(&operationObject->clientSession, &originalImpersonation);
            if (securityCheck != MI_RESULT_OK)
            {
                ThunkHandle_Release(genericHandle->thunkHandle);
                return securityCheck;
            }

            if(response == MI_OperationCallback_ResponseType_YesToAll) //Change the mode from enquire to report
            {
                operationObject->writeErrorMode = MI_CALLBACKMODE_REPORT;
            }

            operationObject->ph_writeErrorResult_callback(&operationObject->protocolHandlerOperation, response);

            /* Releasing twice, once for the reference added in callback and other for reference added in this completion callback */
            ThunkHandle_Release(genericHandle->thunkHandle);
            ThunkHandle_Release(genericHandle->thunkHandle);

            if (Session_RevertImpersonation(originalImpersonation) != MI_RESULT_OK)
            {
                TerminateProcess(GetCurrentProcess(), -1);
            }
            return MI_RESULT_OK;
        }
        else
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
}

/* Transport callback, need to pass through to client */
void MI_CALL Operation_OperationCallback_WriteError(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext,
    _In_ MI_Instance *instance,
    _In_     MI_Result (MI_CALL * writeErrorResult)(_In_ MI_Operation *operation, MI_OperationCallback_ResponseType response))
{
    if (callbackContext != NULL)
    {
        OperationObject *operationObject = (OperationObject *) callbackContext;
        GenericHandle *genericHandle = &operationObject->operationNode.clientHandle;

        ThunkHandle *thunkHandle;

        ThunkHandle_FromGeneric(genericHandle, &thunkHandle); //This should be released after calling callback in callback (writeErrorResult)
        if (thunkHandle != NULL)
        {
            MI_Operation *clientOperation = (MI_Operation*)genericHandle;
            MI_Result impersonationResult = MI_RESULT_OK;

            MI_CLIENT_IMPERSONATION_TOKEN currentImpersonationToken;
            impersonationResult = Session_ImpersonateClient(&operationObject->clientSession, &currentImpersonationToken);
            if (impersonationResult == MI_RESULT_OK)
            {
                if(operationObject->writeErrorMode == MI_CALLBACKMODE_REPORT)
                {
                    //Don't pass the callback to the client and default to normal behavior.
                    operationObject->callbacks.writeError(clientOperation, operationObject->callbacks.callbackContext, instance, NULL);
                    writeErrorResult(&operationObject->protocolHandlerOperation, MI_OperationCallback_ResponseType_Yes);
                    ThunkHandle_Release(thunkHandle);
                }
                else
                {
                    operationObject->ph_writeErrorResult_callback = writeErrorResult;
                    operationObject->callbacks.writeError(clientOperation, operationObject->callbacks.callbackContext, instance, Operation_OperationCallback_WriteError_Callback);
                }

                if (Session_RevertImpersonation(currentImpersonationToken) != MI_RESULT_OK)
                {
                    TerminateProcess(GetCurrentProcess(), -1);
                }
            }
            else
            {
                //TODO: Set internal state to BROKEN so MI_Operation_Close will succeed
                operationObject->currentState = Broken;
            }
        }
    }
}

/* client called StreamedParameter callback which needs to be passed back to transport */
MI_Result MI_CALL Operation_OperationCallback_StreamedParameter_Callback(
    _In_ MI_Operation *operation)
{
    if (operation)
    {
        GenericHandle *genericHandle = (GenericHandle*) operation;
        ThunkHandle *thunkHandle;
        MI_CLIENT_IMPERSONATION_TOKEN originalImpersonation = INVALID_HANDLE_VALUE;

        ThunkHandle_FromGeneric_ForCompletionCallback(genericHandle, &thunkHandle);
        if(thunkHandle != NULL)
        {
            OperationObject *operationObject = (OperationObject *) thunkHandle->u.object;

            MI_Result securityCheck = Session_AccessCheck(&operationObject->clientSession, MI_T("call StreamedParameter callback"));
            if (securityCheck != MI_RESULT_OK)
            {
                ThunkHandle_Release(genericHandle->thunkHandle);
                trace_MiSession_AccessCheckFailed(__FUNCTION__, &operationObject->clientSession);
                return securityCheck;
            }
            securityCheck = Session_ImpersonateClient(&operationObject->clientSession, &originalImpersonation);
            if (securityCheck != MI_RESULT_OK)
            {
                ThunkHandle_Release(genericHandle->thunkHandle);
                return securityCheck;
            }

            operationObject->ph_streamedParameterResult_callback(&operationObject->protocolHandlerOperation);

            /* Releasing twice, once for the reference added in callback and other for reference added in this completion callback */
            ThunkHandle_Release(genericHandle->thunkHandle);
            ThunkHandle_Release(genericHandle->thunkHandle);

            if (Session_RevertImpersonation(originalImpersonation) != MI_RESULT_OK)
            {
                TerminateProcess(GetCurrentProcess(), -1);
            }
            return MI_RESULT_OK;
        }
        else
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
}

/* Transport callback, need to pass through to client */
void MI_CALL Operation_OperationCallback_StreamedParameter(
    _In_ MI_Operation *operation,
    _In_ void *callbackContext,
    _In_z_ const MI_Char * parameterName,
    _In_ MI_Type resultType,
    _In_ const MI_Value *result,
    _In_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    OperationObject *operationObject = (OperationObject *) callbackContext;

    if (operationObject != NULL)
    {
        GenericHandle *genericHandle = &operationObject->operationNode.clientHandle;

        ThunkHandle *thunkHandle;

        ThunkHandle_FromGeneric(genericHandle, &thunkHandle); //This should be released after calling callback in callback (resultAcknowledgement)
        if (thunkHandle != NULL)
        {
            MI_Operation *clientOperation = (MI_Operation*)genericHandle;
            if (operationObject->callbacks.streamedParameterResult)
            {
                MI_CLIENT_IMPERSONATION_TOKEN currentImpersonationToken;
                MI_Result impersonationResult = MI_RESULT_OK;
                MI_Boolean manualAck = operationObject->manualAck;
                if (manualAck)
                {
                    /* Save off data before calling result in case it calls directly back to us */
                    operationObject->ph_streamedParameterResult_callback = resultAcknowledgement;
                    operationObject->protocolHandlerOperation = *operation;
                }

                impersonationResult = Session_ImpersonateClient(&operationObject->clientSession, &currentImpersonationToken);

                if (impersonationResult == MI_RESULT_OK)
                {
                    operationObject->callbacks.streamedParameterResult(
                            clientOperation,
                            operationObject->callbacks.callbackContext,
                            parameterName,
                            resultType,
                            result,
                            operationObject->manualAck?Operation_OperationCallback_StreamedParameter_Callback:NULL);

                    if (Session_RevertImpersonation(currentImpersonationToken) != MI_RESULT_OK)
                    {
                        TerminateProcess(GetCurrentProcess(), -1);
                    }
                }
                else
                {
                    //TODO: Set internal state to BROKEN so MI_Operation_Close needs to succeed
                    operationObject->currentState = Broken;
                }

                if (!manualAck)
                {
                    resultAcknowledgement(operation);
                    ThunkHandle_Release(thunkHandle);
                }
            }
        }
    }
}


/* Transport callback, need to pass through to client */
void MI_CALL Operation_OperationCallback_WriteMessage(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext,
             MI_Uint32 channel,
    _In_z_   const MI_Char *message)
{
    if (callbackContext != NULL)
    {
        OperationObject *operationObject = (OperationObject *) callbackContext;
        GenericHandle *genericHandle = &operationObject->operationNode.clientHandle;

        ThunkHandle *thunkHandle;

        ThunkHandle_FromGeneric(genericHandle, &thunkHandle); //This should be released after calling callback in callback (resultAcknowledgement)
        if (thunkHandle != NULL)
        {
            MI_Operation *clientOperation = (MI_Operation*) genericHandle;
            MI_CLIENT_IMPERSONATION_TOKEN currentImpersonationToken;
            MI_Result impersonationResult = MI_RESULT_OK;

            impersonationResult = Session_ImpersonateClient(&operationObject->clientSession, &currentImpersonationToken);

            if (impersonationResult == MI_RESULT_OK)
            {
                operationObject->callbacks.writeMessage(clientOperation, operationObject->callbacks.callbackContext, channel, message);

                if (Session_RevertImpersonation(currentImpersonationToken) != MI_RESULT_OK)
                {
                    TerminateProcess(GetCurrentProcess(), -1);
                }
            }
            else
            {
                //TODO: Set internal state to BROKEN so MI_Operation_Close needs to succeed
                operationObject->currentState = Broken;
            }

            ThunkHandle_Release(thunkHandle);
        }
    }
}

/* Transport callback, need to pass through to client */
void MI_CALL Operation_OperationCallback_WriteProgress(
    _In_     MI_Operation *operation,
    _In_opt_ void *callbackContext,
    _In_z_   const MI_Char *activity,
    _In_z_   const MI_Char *currentOperation,
    _In_z_   const MI_Char *statusDescription,
             MI_Uint32 percentageComplete,
             MI_Uint32 secondsRemaining)
{
    if (callbackContext != NULL)
    {
        OperationObject *operationObject = (OperationObject *) callbackContext;
        GenericHandle *genericHandle = &operationObject->operationNode.clientHandle;

        ThunkHandle *thunkHandle;

        ThunkHandle_FromGeneric(genericHandle, &thunkHandle); //This should be released after calling callback in callback (resultAcknowledgement)
        if (thunkHandle != NULL)
        {
            MI_Operation *clientOperation = (MI_Operation*) genericHandle;
            MI_CLIENT_IMPERSONATION_TOKEN currentImpersonationToken;
            MI_Result impersonationResult = MI_RESULT_OK;

            impersonationResult = Session_ImpersonateClient(&operationObject->clientSession, &currentImpersonationToken);

            if (impersonationResult == MI_RESULT_OK)
            {
                operationObject->callbacks.writeProgress(clientOperation, operationObject->callbacks.callbackContext, activity, currentOperation, statusDescription, percentageComplete, secondsRemaining);

                if (Session_RevertImpersonation(currentImpersonationToken) != MI_RESULT_OK)
                {
                    TerminateProcess(GetCurrentProcess(), -1);
                }
            }
            else
            {
                //TODO: Set internal state to BROKEN so MI_Operation_Close needs to succeed
                operationObject->currentState = Broken;
            }

            ThunkHandle_Release(thunkHandle);
        }
    }
}

/* Operation failed to create so nothing to do but clean up the operation */
MI_Result MI_CALL Operation_Close_Failed(
    _In_      MI_Operation *operation)
{
    if (operation)
    {
        memset(operation, 0, sizeof(MI_Operation));
    }
    return MI_RESULT_OK;
}
/* Operation failed to create so nothing to cancel */
MI_Result MI_CALL Operation_Cancel_Failed(
    _In_      MI_Operation *operation,
              MI_CancelationReason reason)
{
    return MI_RESULT_FAILED;
}
/* Operation failed to create so nothing to get, return empty session */
MI_Result MI_CALL Operation_GetParentSession_Failed(
    _In_      MI_Operation *operation,
    _Out_     MI_Session *session)
{
    if (session && operation)
    {
        session->reserved1 = operation->reserved1;
        session->reserved2 = operation->reserved2;
        session->ft = &g_sessionFT;
    }
    else if (session)
    {
        memset(session, 0, sizeof(MI_Session));
    }
    return MI_RESULT_FAILED;
}
/* Operation failed to create and error code was encapsulated
 * inside the client MI_Instance handle itself so return that
 */
MI_Result MI_CALL Operation_GetInstance_Result_Error(
    _In_      MI_Operation *operation,
              MI_Result errorCode,
    _Out_     const MI_Instance **instance,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    if (instance)
    {
        *instance = NULL;
    }
    if (moreResults)
    {
        *moreResults = MI_FALSE;
    }
    if (result)
    {
        *result = errorCode;
    }
    if (errorMessage)
    {
        *errorMessage = NULL;
    }

    if (completionDetails)
    {
        *completionDetails = NULL;
    }
    return MI_RESULT_OK;
}
MI_Result MI_CALL Operation_GetInstance_Result_Failed(
    _In_      MI_Operation *operation,
    _Out_     const MI_Instance **instance,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    return Operation_GetInstance_Result_Error(operation, MI_RESULT_FAILED, instance, moreResults, result, errorMessage, completionDetails);
}
MI_Result MI_CALL Operation_GetInstance_Result_OOM(
    _In_      MI_Operation *operation,
    _Out_     const MI_Instance **instance,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    return Operation_GetInstance_Result_Error(operation, MI_RESULT_SERVER_LIMITS_EXCEEDED, instance, moreResults, result, errorMessage, completionDetails);
}
MI_Result MI_CALL Operation_GetInstance_Result_InvalidParameter(
    _In_      MI_Operation *operation,
    _Out_     const MI_Instance **instance,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    return Operation_GetInstance_Result_Error(operation, MI_RESULT_INVALID_PARAMETER, instance, moreResults, result, errorMessage, completionDetails);
}
MI_Result MI_CALL Operation_GetInstance_Result_NotSupported(
    _In_      MI_Operation *operation,
    _Out_     const MI_Instance **instance,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    return Operation_GetInstance_Result_Error(operation, MI_RESULT_NOT_SUPPORTED, instance, moreResults, result, errorMessage, completionDetails);
}
MI_Result MI_CALL Operation_GetInstance_Result_AccessDenied(
    _In_      MI_Operation *operation,
    _Out_     const MI_Instance **instance,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    return Operation_GetInstance_Result_Error(operation, MI_RESULT_ACCESS_DENIED, instance, moreResults, result, errorMessage, completionDetails);
}

MI_Result MI_CALL Operation_GetIndication_Result_Error(
    _In_      MI_Operation *operation,
              MI_Result errorCode,
    _Out_     const MI_Instance **instance,
    _Out_opt_ const MI_Char **bookmark,
    _Out_opt_ const MI_Char **machineID,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    if (instance)
    {
        *instance = NULL;
    }
    if (bookmark)
    {
        *bookmark = NULL;
    }
    if (machineID)
    {
        *machineID = NULL;
    }
    if (moreResults)
    {
        *moreResults = MI_FALSE;
    }
    if (result)
    {
        *result = errorCode;
    }
    if (errorMessage)
    {
        *errorMessage = NULL;
    }

    if (completionDetails)
    {
        *completionDetails = NULL;
    }
    return MI_RESULT_OK;
}
MI_Result MI_CALL Operation_GetIndication_Result_Failed(
    _In_      MI_Operation *operation,
    _Out_     const MI_Instance **instance,
    _Out_opt_ const MI_Char **bookmark,
    _Out_opt_ const MI_Char **machineID,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    return Operation_GetIndication_Result_Error(operation, MI_RESULT_FAILED, instance, bookmark, machineID, moreResults, result, errorMessage, completionDetails);
}
MI_Result MI_CALL Operation_GetIndication_Result_OOM(
    _In_      MI_Operation *operation,
    _Out_     const MI_Instance **instance,
    _Out_opt_ const MI_Char **bookmark,
    _Out_opt_ const MI_Char **machineID,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    return Operation_GetIndication_Result_Error(operation, MI_RESULT_SERVER_LIMITS_EXCEEDED, instance, bookmark, machineID, moreResults, result, errorMessage, completionDetails);
}
MI_Result MI_CALL Operation_GetIndication_Result_InvalidParameter(
    _In_      MI_Operation *operation,
    _Out_     const MI_Instance **instance,
    _Out_opt_ const MI_Char **bookmark,
    _Out_opt_ const MI_Char **machineID,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    return Operation_GetIndication_Result_Error(operation, MI_RESULT_INVALID_PARAMETER, instance, bookmark, machineID, moreResults, result, errorMessage, completionDetails);
}
MI_Result MI_CALL Operation_GetIndication_Result_NotSupported(
    _In_      MI_Operation *operation,
    _Out_     const MI_Instance **instance,
    _Out_opt_ const MI_Char **bookmark,
    _Out_opt_ const MI_Char **machineID,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    return Operation_GetIndication_Result_Error(operation, MI_RESULT_NOT_SUPPORTED, instance, bookmark, machineID, moreResults, result, errorMessage, completionDetails);
}
MI_Result MI_CALL Operation_GetIndication_Result_AccessDenied(
    _In_      MI_Operation *operation,
    _Out_     const MI_Instance **instance,
    _Out_opt_ const MI_Char **bookmark,
    _Out_opt_ const MI_Char **machineID,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    return Operation_GetIndication_Result_Error(operation, MI_RESULT_ACCESS_DENIED, instance, bookmark, machineID, moreResults, result, errorMessage, completionDetails);
}

MI_Result MI_CALL Operation_GetClass_Result_Error(
    _In_      MI_Operation *operation,
              MI_Result errorCode,
    _Out_     const MI_Class **classResults,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    if (classResults)
    {
        *classResults = NULL;
    }
    if (moreResults)
    {
        *moreResults = MI_FALSE;
    }
    if (result)
    {
        *result = errorCode;
    }
    if (errorMessage)
    {
        *errorMessage = NULL;
    }

    if (completionDetails)
    {
        *completionDetails = NULL;
    }
    return MI_RESULT_OK;
}
MI_Result MI_CALL Operation_GetClass_Result_Failed(
    _In_      MI_Operation *operation,
    _Out_     const MI_Class **classResults,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    return Operation_GetClass_Result_Error(operation, MI_RESULT_FAILED, classResults, moreResults, result, errorMessage, completionDetails);
}
MI_Result MI_CALL Operation_GetClass_Result_OOM(
    _In_      MI_Operation *operation,
    _Out_     const MI_Class **classResults,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    return Operation_GetClass_Result_Error(operation, MI_RESULT_SERVER_LIMITS_EXCEEDED, classResults, moreResults, result, errorMessage, completionDetails);
}
MI_Result MI_CALL Operation_GetClass_Result_InvalidParameter(
    _In_      MI_Operation *operation,
    _Out_     const MI_Class **classResults,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    return Operation_GetClass_Result_Error(operation, MI_RESULT_INVALID_PARAMETER, classResults, moreResults, result, errorMessage, completionDetails);
}
MI_Result MI_CALL Operation_GetClass_Result_NotSupported(
    _In_      MI_Operation *operation,
    _Out_     const MI_Class **classResults,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    return Operation_GetClass_Result_Error(operation, MI_RESULT_NOT_SUPPORTED, classResults, moreResults, result, errorMessage, completionDetails);
}
MI_Result MI_CALL Operation_GetClass_Result_AccessDenied(
    _In_      MI_Operation *operation,
    _Out_     const MI_Class **classResults,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Out_opt_ const MI_Char * *errorMessage,
    _Out_opt_ const MI_Instance **completionDetails)
{
    return Operation_GetClass_Result_Error(operation, MI_RESULT_ACCESS_DENIED, classResults, moreResults, result, errorMessage, completionDetails);
}

/* Transport callback with instance results, need to pass through to client is async. */
void MI_CALL Operation_OperationCallback_Instance(
    _In_     MI_Operation *operation,
    _In_     void *callbackContext,
    _In_opt_ const MI_Instance *instance,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char * errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_opt_ MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    OperationObject *operationObject = (OperationObject *) callbackContext;

    if (operationObject != NULL)
    {
        GenericHandle *genericHandle = &operationObject->operationNode.clientHandle;
        MI_Operation clientOperation = *(MI_Operation*) genericHandle;

        if (operationObject->callbacks.instanceResult)
        {
            /* ASYNC behaviour */
            MI_Boolean manualAck = operationObject->manualAck;
            MI_CLIENT_IMPERSONATION_TOKEN currentImpersonationToken;
            MI_Result impersonationResult = MI_RESULT_OK;

            trace_MIClient_OperationInstancResultAsync(operationObject->clientSessionPtr, operationObject->clientOperationPtr, operationObject, resultCode, moreResults?MI_T("TRUE"):MI_T("FALSE"));

            if (manualAck)
            {
                /* Save off data before calling result in case it calls directly back to us */
                operationObject->ph_instance_resultAcknowledgement = resultAcknowledgement;
                operationObject->protocolHandlerOperation = *operation;
                operationObject->moreResults = moreResults;
            }


            impersonationResult = Session_ImpersonateClient(&operationObject->clientSession, &currentImpersonationToken);

            if (impersonationResult == MI_RESULT_OK)
            {
                operationObject->callbacks.instanceResult(
                    &clientOperation,
                    operationObject->callbacks.callbackContext,
                    instance,
                    moreResults,
                    resultCode,
                    errorString,
                    errorDetails,
                    operationObject->manualAck?Operation_ResultAcknowledgement:NULL);

                if (Session_RevertImpersonation(currentImpersonationToken) != MI_RESULT_OK)
                {
                    TerminateProcess(GetCurrentProcess(), -1);
                }
            }
            else
            {
                //TODO: Set internal state to BROKEN so MI_Operation_Close needs to succeed
                //operationObject->currentState = Broken;
            }
            if (!manualAck || (impersonationResult != MI_RESULT_OK))
            {
                resultAcknowledgement(operation);

                if (!moreResults)
                {
                    /* Final result ref-count */
                    operationObject->currentState = Completed;
                    ThunkHandle_Release(genericHandle->thunkHandle);

                }
            }
        }
        else
        {
            /* SYNC behaviour, store and notify potential waiter for results */
            operationObject->instanceResult = instance;
            operationObject->moreResults = moreResults;
            operationObject->resultCode = resultCode;
            operationObject->errorString = errorString;
            operationObject->errorDetails = errorDetails;
            operationObject->ph_instance_resultAcknowledgement = resultAcknowledgement;
            operationObject->consumedResult = MI_FALSE;

            trace_MIClient_OperationInstanceResult_WaitingForClient(operationObject->clientSessionPtr, operationObject->clientOperationPtr, operationObject, resultCode, moreResults?MI_T("TRUE"):MI_T("FALSE"));
            operationObject->instanceCallbackReceived = 1;
            CondLock_Broadcast((ptrdiff_t) operationObject);
            /* Do rest of work from result retrieval */
        }
    }
}

void MI_CALL Operation_OperationCallback_Class(
    _In_     MI_Operation *operation,
    _In_     void *callbackContext,
    _In_opt_ const MI_Class *classResult,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char *errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_     MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    OperationObject *operationObject = (OperationObject *) callbackContext;

    if (operationObject != NULL)
    {
        GenericHandle *genericHandle = &operationObject->operationNode.clientHandle;
        MI_Operation clientOperation = *(MI_Operation*) genericHandle;

        trace_MIClient_OperationClassResult(operationObject->clientSessionPtr, operationObject->clientOperationPtr, operationObject, resultCode, moreResults?MI_T("TRUE"):MI_T("FALSE"));

        if (operationObject->callbacks.classResult)
        {
            /* ASYNC behaviour */
            MI_Boolean manualAck = operationObject->manualAck;
            MI_CLIENT_IMPERSONATION_TOKEN currentImpersonationToken;
            MI_Result impersonationResult = MI_RESULT_OK;

            if (manualAck)
            {
                /* Save off data before calling result in case it calls directly back to us */
                operationObject->ph_instance_resultAcknowledgement = resultAcknowledgement;
                operationObject->protocolHandlerOperation = *operation;
                operationObject->moreResults = moreResults;
            }

            impersonationResult = Session_ImpersonateClient(&operationObject->clientSession, &currentImpersonationToken);

            if (impersonationResult == MI_RESULT_OK)
            {
                operationObject->callbacks.classResult(
                    &clientOperation,
                    operationObject->callbacks.callbackContext,
                    classResult,
                    moreResults,
                    resultCode,
                    errorString,
                    errorDetails,
                    operationObject->manualAck?Operation_ResultAcknowledgement:NULL);

                if (Session_RevertImpersonation(currentImpersonationToken) != MI_RESULT_OK)
                {
                    TerminateProcess(GetCurrentProcess(), -1);
                }
            }
            else
            {
                //TODO: Set internal state to BROKEN so MI_Operation_Close needs to succeed
                operationObject->currentState = Broken;
            }

            if (!manualAck || (impersonationResult != MI_RESULT_OK))
            {
                resultAcknowledgement(operation);

                if (!moreResults)
                {
                    /* Final result ref-count */
                    ThunkHandle_Release(genericHandle->thunkHandle);
                }
            }
        }
        else
        {
            /* SYNC behaviour, store and notify potential waiter for results */
            operationObject->classResult = classResult;
            operationObject->moreResults = moreResults;
            operationObject->resultCode = resultCode;
            operationObject->errorString = errorString;
            operationObject->errorDetails = errorDetails;
            operationObject->ph_instance_resultAcknowledgement = resultAcknowledgement;
            operationObject->consumedResult = MI_FALSE;

            operationObject->instanceCallbackReceived = 1;
            CondLock_Broadcast((ptrdiff_t)operationObject);
            /* Do rest of work from result retrieval */
        }
    }
}

void MI_CALL Operation_OperationCallback_Indication(
    _In_     MI_Operation *operation,
    _In_     void *callbackContext,
    _In_opt_ const MI_Instance *instance,
    _In_opt_z_ const MI_Char *bookmark,
    _In_opt_z_ const MI_Char *machineID,
             MI_Boolean moreResults,
    _In_     MI_Result resultCode,
    _In_opt_z_ const MI_Char *errorString,
    _In_opt_ const MI_Instance *errorDetails,
    _In_     MI_Result (MI_CALL * resultAcknowledgement)(_In_ MI_Operation *operation))
{
    OperationObject *operationObject = (OperationObject *) callbackContext;

    if (operationObject != NULL)
    {
        GenericHandle *genericHandle = &operationObject->operationNode.clientHandle;
        MI_Operation clientOperation = *(MI_Operation*) genericHandle;

        trace_MIClient_OperationIndicationResult(operationObject->clientSessionPtr, operationObject->clientOperationPtr, operationObject, resultCode, moreResults?MI_T("TRUE"):MI_T("FALSE"));

        if (operationObject->callbacks.indicationResult)
        {
            /* ASYNC behaviour */
            MI_Boolean manualAck = operationObject->manualAck;
            MI_CLIENT_IMPERSONATION_TOKEN currentImpersonationToken;
            MI_Result impersonationResult = MI_RESULT_OK;

            if (manualAck)
            {
                /* Save off data before calling result in case it calls directly back to us */
                operationObject->ph_instance_resultAcknowledgement = resultAcknowledgement;
                operationObject->protocolHandlerOperation = *operation;
                operationObject->moreResults = moreResults;
            }

            impersonationResult = Session_ImpersonateClient(&operationObject->clientSession, &currentImpersonationToken);

            if (impersonationResult == MI_RESULT_OK)
            {
                operationObject->callbacks.indicationResult(
                    &clientOperation,
                    operationObject->callbacks.callbackContext,
                    instance,
                    bookmark,
                    machineID,
                    moreResults,
                    resultCode,
                    errorString,
                    errorDetails,
                    operationObject->manualAck?Operation_ResultAcknowledgement:NULL);

                if (Session_RevertImpersonation(currentImpersonationToken) != MI_RESULT_OK)
                {
                    TerminateProcess(GetCurrentProcess(), -1);
                }
            }
            else
            {
                //TODO: Set internal state to BROKEN so MI_Operation_Close needs to succeed
                operationObject->currentState = Broken;
            }

            if (!manualAck || (impersonationResult != MI_RESULT_OK))
            {
                resultAcknowledgement(operation);

                if (!moreResults)
                {
                    /* Final result ref-count */
                    ThunkHandle_Release(genericHandle->thunkHandle);
                }
            }
        }
        else
        {
            /* SYNC behaviour, store and notify potential waiter for results */
            operationObject->instanceResult = instance;
            operationObject->bookmark = bookmark;
            operationObject->machineID = machineID;
            operationObject->moreResults = moreResults;
            operationObject->resultCode = resultCode;
            operationObject->errorString = errorString;
            operationObject->errorDetails = errorDetails;
            operationObject->ph_instance_resultAcknowledgement = resultAcknowledgement;
            operationObject->consumedResult = MI_FALSE;

            operationObject->instanceCallbackReceived = 1;
            CondLock_Broadcast((ptrdiff_t)operationObject);
            /* Do rest of work from result retrieval */
        }
    }
}

/* When thunk handle ref count gets to zero means no one is referencing this object any more
 * so we can now delete the OperationObject
 */
void Operation_Destructor(
    _In_ ThunkHandle *thunkHandle)
{
    /* Unregister self from session */
    OperationObject *operationObject = (OperationObject*) thunkHandle->u.object;

    /* Close the protocol handler operation */
    if (operationObject->protocolHandlerOperation.ft)
    {
        operationObject->protocolHandlerOperation.ft->Close(&operationObject->protocolHandlerOperation);
    }

    trace_MIClient_OperationCloseCompleted(operationObject->clientSessionPtr, operationObject->clientOperationPtr, operationObject);

    Session_UnregisterOperation((ThunkHandle*)operationObject->clientSession.reserved2, &operationObject->operationNode);

    /* Free operation object itself */
    PAL_Free(operationObject);

}
/* Close the operation down.  If it is still running it will need to be cancelled.
 * Close is potentially async if the operation has not already completed as it
 * will ensure the callback is called for async or GetInstance/etc is called
 * for sync
 */
/* TODO: If operationObject->currentState==Broken then MI_Operation_Close must be able to complete */
MI_Result MI_CALL Operation_Close(
    _In_ MI_Operation *operation)
{
    GenericHandle *genericHandle = (GenericHandle*) operation;
    ThunkHandle *thunkHandle;

    if (operation == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    ThunkHandle_FromGeneric(genericHandle, &thunkHandle);
    if (thunkHandle != NULL)
    {
        OperationObject *operationObject = (OperationObject *) thunkHandle->u.object;
        MI_Operation phOperation = operationObject->protocolHandlerOperation;
        MI_Result (MI_CALL * tmpResultAcknowledgement)(_In_ MI_Operation *operation) = operationObject->ph_instance_resultAcknowledgement;
        MI_CLIENT_IMPERSONATION_TOKEN originalImpersonation = INVALID_HANDLE_VALUE;

        //Do access check
        MI_Result result = Session_AccessCheck(&operationObject->clientSession, MI_T("close operation"));
        if (result != MI_RESULT_OK)
        {
            ThunkHandle_Release(thunkHandle);
            trace_MiSession_AccessCheckFailed(__FUNCTION__, &operationObject->clientSession);
            return result;
        }

        result = Session_ImpersonateClient(&operationObject->clientSession, &originalImpersonation);
        if (result != MI_RESULT_OK)
        {
            ThunkHandle_Release(thunkHandle);
            return result;
        }

        //Make sure the operation is cancelled
        Operation_Cancel(operation, MI_REASON_NONE);

        trace_MIClient_OperationClose(operation, operationObject);

        if (operationObject->synchronousOperation == MI_TRUE)
        {
            //Has the client consumed the final result?  If not we need to wait until it does.
            //Reason for this is that session_close will wait, and if we wait here it is
            //more obvious as to which operation is misbehaving.
            if (operationObject->consumedFinalResult == MI_FALSE)
            {
                ptrdiff_t consumedFinal = operationObject->consumedFinalResult;
                while (!consumedFinal)
                {
                    trace_MIClient_OperationClose_WaitingForFinalResult(operation, operationObject);
                    /* Wait for child session count to hit 0 */
                    CondLock_Wait((ptrdiff_t)&operationObject->consumedFinalResult, &operationObject->consumedFinalResult, consumedFinal, CONDLOCK_DEFAULT_SPINCOUNT);
                    consumedFinal = operationObject->consumedFinalResult;
                }
            }

            /* ack last data if present in case of syncrhonous */
            if (tmpResultAcknowledgement)
            {
                operationObject->instanceResult = NULL;
                operationObject->ph_instance_resultAcknowledgement = NULL;
                tmpResultAcknowledgement(&phOperation);
            }
        }

        //Once we call Shutdown on the thunk handle no operations that try to thunk will fail.  The operation
        //really is no longer after this!
        ThunkHandle_Shutdown(thunkHandle, Operation_Destructor);

        ThunkHandle_Release(thunkHandle);

        if (Session_RevertImpersonation(originalImpersonation) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return result;
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

}


/* Cancel a running operation */
MI_Result MI_CALL Operation_Cancel(
    _In_  MI_Operation *operation,
          MI_CancelationReason reason)
{
    GenericHandle *genericHandle = (GenericHandle*) operation;
    ThunkHandle *thunkHandle;

    if (operation == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    ThunkHandle_FromGeneric(genericHandle, &thunkHandle);
    if (thunkHandle != NULL)
    {
        OperationObject *operationObject = (OperationObject *) thunkHandle->u.object;

        //Do access check
        MI_Result result = Session_AccessCheck(&operationObject->clientSession, MI_T("cancel operation"));
        if (result != MI_RESULT_OK)
        {
            ThunkHandle_Release(thunkHandle);
            trace_MiSession_AccessCheckFailed(__FUNCTION__, &operationObject->clientSession);
            return result;
        }

        trace_MIClient_OperationCancel(operation, operationObject);

        if (operationObject->protocolHandlerOperation.ft &&
            operationObject->protocolHandlerOperation.ft->Cancel &&
            Atomic_CompareAndSwap(&operationObject->cancelled, 0, 1) == 0)
        {
            MI_CLIENT_IMPERSONATION_TOKEN originalImpersonation = INVALID_HANDLE_VALUE;
            result = Session_ImpersonateClient(&operationObject->clientSession, &originalImpersonation);
            if (result != MI_RESULT_OK)
            {
                ThunkHandle_Release(thunkHandle);
                return result;
            }
            operationObject->protocolHandlerOperation.ft->Cancel(&operationObject->protocolHandlerOperation, reason);

            if (Session_RevertImpersonation(originalImpersonation) != MI_RESULT_OK)
            {
                TerminateProcess(GetCurrentProcess(), -1);
            }
        }

        ThunkHandle_Release(thunkHandle);
        return MI_RESULT_OK;
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
}

MI_Result MI_CALL Operation_GetParentSession(
    _In_      MI_Operation *operation,
    _Out_     MI_Session *session)
{
    GenericHandle *genericHandle = (GenericHandle*) operation;
    ThunkHandle *thunkHandle;

    if (session)
    {
        memset(session, 0, sizeof(MI_Session));
    }
    if ((operation == NULL) || (session == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    ThunkHandle_FromGeneric(genericHandle, &thunkHandle);
    if (thunkHandle != NULL)
    {
        OperationObject *operationObject = (OperationObject *)thunkHandle->u.object;
        MI_CLIENT_IMPERSONATION_TOKEN originalImpersonation = INVALID_HANDLE_VALUE;

        //Do access check
        MI_Result result = Session_AccessCheck(&operationObject->clientSession, MI_T("get operation's parent session"));
        if (result != MI_RESULT_OK)
        {
            ThunkHandle_Release(thunkHandle);
            trace_MiSession_AccessCheckFailed(__FUNCTION__, &operationObject->clientSession);
            return result;
        }
        result = Session_ImpersonateClient(&operationObject->clientSession, &originalImpersonation);
        if (result != MI_RESULT_OK)
        {
            ThunkHandle_Release(thunkHandle);
            return result;
        }

        *session = * &operationObject->clientSession;

        ThunkHandle_Release(thunkHandle);

        if (Session_RevertImpersonation(originalImpersonation) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return MI_RESULT_OK;
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
}

/* Report the error to the user in the case of an operation setup problem.  If there is a
 * callback then call that, otherwise encode it into the operation handle itself and use
 * a special error reporting function table that extracts error from the handle.
 */
void Operation_Execute_SetupFailure(
    OPERATION_TYPE operationType,
    MI_Result failureCode,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _In_opt_     MI_Session *parentSession,
    _Out_    MI_Operation *operation)
{
    if (operation)
    {
        /* Client passed in operation so fill it in.  Function table allows for retrieval of error code */
        switch(failureCode)
        {
        case MI_RESULT_INVALID_PARAMETER:
            operation->ft = &g_operationFT_InvalidParameter;
            break;
        case MI_RESULT_SERVER_LIMITS_EXCEEDED:
            operation->ft = &g_operationFT_OOM;
            break;
        case MI_RESULT_NOT_SUPPORTED:
            operation->ft = &g_operationFT_NotSupported;
            break;
        case MI_RESULT_ACCESS_DENIED:
            operation->ft = &g_operationFT_AccessDenied;
            break;
        default:
            operation->ft = &g_operationFT_Failed;
            break;
        }
        if (parentSession)
        {
            operation->reserved1 = parentSession->reserved1;
            operation->reserved2 = parentSession->reserved2;
        }
        else
        {
            operation->reserved1 = 0;
            operation->reserved2 = 0;
        }
    }
    if (callbacks)
    {
        switch(operationType)
        {
        case OPERATION_INSTANCE:
            if(callbacks->instanceResult)
            {
                if (operation)
                {
                    /* Async with operation, so report error */
                    callbacks->instanceResult(operation, callbacks->callbackContext, NULL, MI_FALSE, failureCode, NULL, NULL, NULL);
                }
                else
                {
                    /* Async without operation so use a temporary one */
                    MI_Operation failure;
                    failure.reserved1 = failureCode;
                    failure.reserved2 = 0;
                    failure.ft = &g_operationFT_Failed;
                    callbacks->instanceResult(&failure, callbacks->callbackContext, NULL, MI_FALSE, failureCode, NULL, NULL, NULL);
                }
            }
            break;
        case OPERATION_CLASS:
            if(callbacks->classResult)
            {
                if (operation)
                {
                    /* Async with operation, so report error */
                    callbacks->classResult(operation, callbacks->callbackContext, NULL, MI_FALSE, failureCode, NULL, NULL, NULL);
                }
                else
                {
                    /* Async without operation so use a temporary one */
                    MI_Operation failure;
                    failure.reserved1 = failureCode;
                    failure.reserved2 = 0;
                    failure.ft = &g_operationFT_Failed;
                    callbacks->classResult(&failure, callbacks->callbackContext, NULL, MI_FALSE, failureCode, NULL, NULL, NULL);
                }
            }
            break;
        case OPERATION_INDICATION:
            if(callbacks->indicationResult)
            {
                if (operation)
                {
                    /* Async with operation, so report error */
                    callbacks->indicationResult(operation, callbacks->callbackContext, NULL, NULL, NULL, MI_FALSE, failureCode, NULL, NULL, NULL);
                }
                else
                {
                    /* Async without operation so use a temporary one */
                    MI_Operation failure;
                    failure.reserved1 = failureCode;
                    failure.reserved2 = 0;
                    failure.ft = &g_operationFT_Failed;
                    callbacks->indicationResult(&failure, callbacks->callbackContext, NULL, NULL, NULL, MI_FALSE, failureCode, NULL, NULL, NULL);
                }
            }
            break;
        }
    }
}

/* Sets up all the common things necessary for operations.
 * Do any operation specific things before calling into this otherwise
 * Operation_Close is needed to close down the operation. */
MI_Result Operation_Execute_SetupOperation(
    _In_        MI_Session *session,
                MI_Uint32 flags,
                OPERATION_TYPE operationType,
    _In_opt_    MI_OperationOptions *options,
    _In_opt_    MI_OperationCallbacks *callbacks,
    _In_opt_z_ const MI_Char *operationName,
    _Out_       MI_Operation *operation,
    _Out_       MI_Session *protocolHandlerSession,
    _Out_       MI_OperationCallbacks *protocolHandlerCallbacks,
    _Outptr_ OperationObject **operationObject,
    _Out_opt_   MI_OperationOptions *protocolHandlerOptions,
    _Out_       ProtocolHandlerCacheItem **protocolHandlerItem,
    _Out_       MI_CLIENT_IMPERSONATION_TOKEN *originalImpersonation)
{
    GenericHandle *operationHandle = (GenericHandle*) operation;
    MI_Application clientApplication;
    MI_Result miResult;

    if (protocolHandlerOptions)
    {
        memset(protocolHandlerOptions, 0, sizeof(*protocolHandlerOptions));
    }
    if(protocolHandlerCallbacks)
    {
        memset(protocolHandlerCallbacks, 0, sizeof(*protocolHandlerCallbacks));
    }

    *originalImpersonation = INVALID_HANDLE_VALUE;

    /* If present blank out-bound operation object */
    if (operation)
    {
        memset(operation, 0, sizeof(MI_Operation));
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (session == NULL)
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    miResult = Session_AccessCheck(session, operationName);
    if (miResult != MI_RESULT_OK)
   {
        trace_MiSession_AccessCheckFailed(__FUNCTION__, session);
        return miResult;
    }

    *operationObject = (OperationObject *) PAL_Malloc(sizeof(OperationObject));
    if (*operationObject == NULL)
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }
    memset(*operationObject, 0, sizeof(OperationObject));

    (*operationObject)->currentState = RetrievingResults;

    //Set default Mode for WriteError and PromptUser
    (*operationObject)->writeErrorMode = MI_CALLBACKMODE_REPORT;
    (*operationObject)->promptUserMode= MI_CALLBACKMODE_INQUIRE;
    (*operationObject)->promptUserModeAckMode = MI_TRUE;
    (*operationObject)->consumedFinalResult = MI_FALSE;
    (*operationObject)->clientSession = *session;

    session->ft->GetApplication(session, &clientApplication);
    if (clientApplication.ft == NULL)
    {
        PAL_Free(*operationObject);
        return MI_RESULT_INVALID_PARAMETER;
    }
    miResult = Application_NewGenericHandle(&clientApplication, operationHandle);
    if (miResult != MI_RESULT_OK)
    {
        PAL_Free(*operationObject);
        return miResult;
    }

    miResult = Session_GetProtocolHandlerSession(session, protocolHandlerSession, protocolHandlerItem);
    if (miResult != MI_RESULT_OK)
    {
        PAL_Free(*operationObject);
        ThunkHandle_Release(operationHandle->thunkHandle);
        return miResult;
    }

    /* Plumb everything together */
    operation->ft = &g_operationFT;
    (*operationObject)->operationNode.clientHandle = *(GenericHandle*)operation;
    operationHandle->thunkHandle->u.object = *operationObject;

    memcpy(&(*operationObject)->operationNode.clientHandle, operation, sizeof(GenericHandle));

    protocolHandlerCallbacks->callbackContext = *operationObject;
    switch(operationType)
    {
    case OPERATION_INSTANCE:
        protocolHandlerCallbacks->instanceResult = Operation_OperationCallback_Instance;
        if ((callbacks == NULL) || (callbacks->instanceResult == NULL))
            (*operationObject)->synchronousOperation = MI_TRUE;
        break;
    case OPERATION_CLASS:
        protocolHandlerCallbacks->classResult = Operation_OperationCallback_Class;
        if ((callbacks == NULL) || (callbacks->classResult == NULL))
            (*operationObject)->synchronousOperation = MI_TRUE;
        break;
    case OPERATION_INDICATION:
        protocolHandlerCallbacks->indicationResult = Operation_OperationCallback_Indication;
        if ((callbacks == NULL) || (callbacks->indicationResult == NULL))
            (*operationObject)->synchronousOperation = MI_TRUE;
        break;
    }

    /* Copy client callbacks */
    if (callbacks)
    {
        (*operationObject)->callbacks = *callbacks;

        /* Only CIM extensions client asked for should be plumbed into transport */
        if (callbacks->promptUser)
        {
            protocolHandlerCallbacks->promptUser = Operation_OperationCallback_PromptUser;
        }
        if (callbacks->writeError)
        {
            protocolHandlerCallbacks->writeError = Operation_OperationCallback_WriteError;
        }
        if (callbacks->writeMessage)
        {
            protocolHandlerCallbacks->writeMessage = Operation_OperationCallback_WriteMessage;
        }
        if (callbacks->writeProgress)
        {
            protocolHandlerCallbacks->writeProgress = Operation_OperationCallback_WriteProgress;
        }
        if (callbacks->streamedParameterResult)
        {
            protocolHandlerCallbacks->streamedParameterResult = Operation_OperationCallback_StreamedParameter;
        }
    }

    (*operationObject)->manualAck = flags & MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS;

    miResult = Session_ImpersonateClient(session, originalImpersonation);
    if (miResult != MI_RESULT_OK)
    {
        PAL_Free(*operationObject);
        ThunkHandle_Release(operationHandle->thunkHandle);
        return miResult;
    }

    /* Transform destination and operation options to protocol handler options -> protocolHandlerOptions */
    {
        MI_Application phApplication = MI_APPLICATION_NULL;

        /* Only if we have some options to migrate should we do this */
        if (options && protocolHandlerOptions)
        {
            MI_Boolean mustUnderstand = (MI_Boolean) options->reserved1;

            miResult = Session_GetProtocolHandlerApplication(session, &phApplication);
            if (miResult != MI_RESULT_OK)
            {
                PAL_Free(*operationObject);
                ThunkHandle_Release(operationHandle->thunkHandle);
                return miResult;
            }

            miResult = MI_Application_NewOperationOptions(&phApplication, mustUnderstand, protocolHandlerOptions);
            if (miResult != MI_RESULT_OK)
            {
                PAL_Free(*operationObject);
                ThunkHandle_Release(operationHandle->thunkHandle);
                return miResult;
            }
            miResult = OperationOptions_MigrateOptions(options, protocolHandlerOptions);
            if (miResult != MI_RESULT_OK)
            {
                PAL_Free(*operationObject);
                ThunkHandle_Release(operationHandle->thunkHandle);
                MI_OperationOptions_Delete(protocolHandlerOptions);
                return miResult;
            }
            if( options->reserved2 )
            {
                MI_CallbackMode mode;
                MI_Boolean ackVal;
                //Set the writeerror mode
                miResult = MI_OperationOptions_GetWriteErrorMode(options, &mode);
                if (miResult == MI_RESULT_OK)
                {
                    (*operationObject)->writeErrorMode = mode;
                }
                else if (miResult != MI_RESULT_NO_SUCH_PROPERTY)
                {
                    PAL_Free(*operationObject);
                    ThunkHandle_Release(operationHandle->thunkHandle);
                    MI_OperationOptions_Delete(protocolHandlerOptions);
                    return MI_RESULT_INVALID_PARAMETER;
                }

                //Set promptusermode for regular mode and ack value
                miResult = MI_OperationOptions_GetPromptUserRegularMode(options, &mode, &ackVal);
                if (miResult == MI_RESULT_OK)
                {
                    (*operationObject)->promptUserMode = mode;
                    (*operationObject)->promptUserModeAckMode = ackVal == 0 ? MI_FALSE : MI_TRUE;
                }
                else if (miResult != MI_RESULT_NO_SUCH_PROPERTY)
                {
                    PAL_Free(*operationObject);
                    ThunkHandle_Release(operationHandle->thunkHandle);
                    MI_OperationOptions_Delete(protocolHandlerOptions);
                    return MI_RESULT_INVALID_PARAMETER;
                }
            }
        }
    }

    Session_RegisterOperation(session, &(*operationObject)->operationNode);

    (*operationObject)->operationType = operationType;

    return MI_RESULT_OK;
}

/* Execute a Get Instance operation */
void MI_CALL Operation_Execute_GetInstance(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_     const MI_Instance *inboundInstance,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation)
{
    MI_Result setupError;
    MI_Session protocolHandlerSession = MI_SESSION_NULL;
    MI_OperationCallbacks protocolHandlerCallbacks = MI_OPERATIONCALLBACKS_NULL;
    OperationObject *operationObject = NULL;
    MI_OperationOptions protocolHandlerOptions = MI_OPERATIONOPTIONS_NULL;
    ProtocolHandlerCacheItem *protocolHandlerItem;
    MI_CLIENT_IMPERSONATION_TOKEN originalImpersonationToken = INVALID_HANDLE_VALUE;

    /* Parameter validation specific to this function */
    if (inboundInstance == NULL)
    {
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_INVALID_PARAMETER, callbacks, session, operation);
        return;
    }

    /* General operation setup work */
    setupError = Operation_Execute_SetupOperation(session, flags, OPERATION_INSTANCE, options, callbacks, MI_T("get instance"), operation, &protocolHandlerSession, &protocolHandlerCallbacks, &operationObject, &protocolHandlerOptions, &protocolHandlerItem, &originalImpersonationToken);
    if (setupError != MI_RESULT_OK)
    {
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, setupError, callbacks, session, operation);
        return;
    }

    /* Validate that transport supports this operation */
    if (protocolHandlerSession.ft == NULL || protocolHandlerSession.ft->GetInstance == NULL)
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_NOT_SUPPORTED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    /* Hold the final result refcount. */
    if (!ThunkHandle_AddRef(operationObject->operationNode.clientHandle.thunkHandle))
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_FAILED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    operationObject->clientOperationPtr = operation;
    operationObject->clientSessionPtr = session;
    trace_MIClient_GetInstance(session, operation, operationObject, namespaceName?namespaceName:MI_T("<null>"));

    /* Call in to protocol handler */
    ProtocolHandlerCache_IncrementApiCount(protocolHandlerItem);
    protocolHandlerSession.ft->GetInstance(&protocolHandlerSession, flags | MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, &protocolHandlerOptions, namespaceName, inboundInstance, &protocolHandlerCallbacks, &operationObject->protocolHandlerOperation);
    ProtocolHandlerCache_DecrementApiCount(protocolHandlerItem);

    /* Operation is now asynchronous */

    /* cleanup anything we created that no longer need (we only create then if we have a options parameter, at least for now) */
    if (options)
    {
        MI_OperationOptions_Delete(&protocolHandlerOptions);
    }

    if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
    {
        TerminateProcess(GetCurrentProcess(), -1);
    }
}

/* Execute a method invocation operation */
void MI_CALL Operation_Execute_Invoke(
    _In_       MI_Session *session,
               MI_Uint32 flags,
    _In_opt_   MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_opt_z_ const MI_Char * className,
    _In_z_     const MI_Char * methodName,
    _In_opt_   const MI_Instance *inboundInstance,
    _In_opt_   const MI_Instance *inboundProperties,
    _In_opt_   MI_OperationCallbacks *callbacks,
    _Out_      MI_Operation *operation)
{
    MI_Result setupError;
    MI_Session protocolHandlerSession = MI_SESSION_NULL;
    MI_OperationCallbacks protocolHandlerCallbacks = MI_OPERATIONCALLBACKS_NULL;
    OperationObject *operationObject = NULL;
    MI_OperationOptions protocolHandlerOptions = MI_OPERATIONOPTIONS_NULL;
    ProtocolHandlerCacheItem *protocolHandlerItem;
    MI_CLIENT_IMPERSONATION_TOKEN originalImpersonationToken = INVALID_HANDLE_VALUE;


    /* Parameter validation specific to this function */
    if (methodName == NULL)
    {
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_INVALID_PARAMETER, callbacks, session, operation);
        return;
    }

    /* General operation setup work */
    setupError = Operation_Execute_SetupOperation(session, flags, OPERATION_INSTANCE, options, callbacks, MI_T("invoke method"), operation, &protocolHandlerSession, &protocolHandlerCallbacks, &operationObject, &protocolHandlerOptions, &protocolHandlerItem, &originalImpersonationToken);
    if (setupError != MI_RESULT_OK)
    {
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, setupError, callbacks, session, operation);
        return;
    }

    /* Validate that transport supports this operation */
    if (protocolHandlerSession.ft == NULL || protocolHandlerSession.ft->Invoke == NULL)
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_NOT_SUPPORTED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    /* Hold the final result refcount. */
    if (!ThunkHandle_AddRef(operationObject->operationNode.clientHandle.thunkHandle))
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_FAILED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    operationObject->clientOperationPtr = operation;
    operationObject->clientSessionPtr = session;
    trace_MIClient_Invoke(session, operation, operationObject, namespaceName?namespaceName:MI_T("<null>"), className, methodName);

    /* Call in to protocol handler */
    ProtocolHandlerCache_IncrementApiCount(protocolHandlerItem);
    protocolHandlerSession.ft->Invoke(&protocolHandlerSession, flags | MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, &protocolHandlerOptions, namespaceName, className, methodName, inboundInstance, inboundProperties, &protocolHandlerCallbacks, &operationObject->protocolHandlerOperation);
    ProtocolHandlerCache_DecrementApiCount(protocolHandlerItem);

    /* Operation is now asynchronous */

    /* cleanup anything we created that no longer need (we only create then if we have a options parameter, at least for now) */
    if (options)
    {
        MI_OperationOptions_Delete(&protocolHandlerOptions);
    }
    if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
    {
        TerminateProcess(GetCurrentProcess(), -1);
    }
}

void MI_CALL Operation_Execute_EnumerateInstances(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_opt_z_ const MI_Char * className,
             MI_Boolean keysOnly,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation)
{
    MI_Result setupError;
    MI_Session protocolHandlerSession = MI_SESSION_NULL;
    MI_OperationCallbacks protocolHandlerCallbacks = MI_OPERATIONCALLBACKS_NULL;
    OperationObject *operationObject = NULL;
    MI_OperationOptions protocolHandlerOptions = MI_OPERATIONOPTIONS_NULL;
    ProtocolHandlerCacheItem *protocolHandlerItem;
    MI_CLIENT_IMPERSONATION_TOKEN originalImpersonationToken = INVALID_HANDLE_VALUE;
    /* General operation setup work */
    setupError = Operation_Execute_SetupOperation(session, flags, OPERATION_INSTANCE, options, callbacks, MI_T("enumerate instance"), operation, &protocolHandlerSession, &protocolHandlerCallbacks, &operationObject, &protocolHandlerOptions, &protocolHandlerItem, &originalImpersonationToken);
    if (setupError != MI_RESULT_OK)
    {
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, setupError, callbacks, session, operation);
        return;
    }

    /* Validate that transport supports this operation */
    if (protocolHandlerSession.ft == NULL || protocolHandlerSession.ft->EnumerateInstances == NULL)
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_NOT_SUPPORTED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    /* Hold the final result refcount. */
    if (!ThunkHandle_AddRef(operationObject->operationNode.clientHandle.thunkHandle))
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_FAILED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    operationObject->clientOperationPtr = operation;
    operationObject->clientSessionPtr = session;
    trace_MIClient_EnumerateInstance(session, operation, operationObject, namespaceName?namespaceName:MI_T("<null>"), className);

    /* Call in to protocol handler */
    ProtocolHandlerCache_IncrementApiCount(protocolHandlerItem);
    protocolHandlerSession.ft->EnumerateInstances(&protocolHandlerSession, flags | MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, &protocolHandlerOptions, namespaceName, className, keysOnly, &protocolHandlerCallbacks, &operationObject->protocolHandlerOperation);
    ProtocolHandlerCache_DecrementApiCount(protocolHandlerItem);

    /* Operation is now asynchronous */

    /* cleanup anything we created that no longer need (we only create then if we have a options parameter, at least for now) */
    if (options)
    {
        MI_OperationOptions_Delete(&protocolHandlerOptions);
    }
    if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
    {
        TerminateProcess(GetCurrentProcess(), -1);
    }
}

void MI_CALL Operation_Execute_QueryInstances(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_opt_z_ const MI_Char * queryDialect,
    _In_opt_z_ const MI_Char * queryExpression,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation)
{
    MI_Result setupError;
    MI_Session protocolHandlerSession = MI_SESSION_NULL;
    MI_OperationCallbacks protocolHandlerCallbacks = MI_OPERATIONCALLBACKS_NULL;
    OperationObject *operationObject = NULL;
    MI_OperationOptions protocolHandlerOptions = MI_OPERATIONOPTIONS_NULL;
    ProtocolHandlerCacheItem *protocolHandlerItem;
    MI_CLIENT_IMPERSONATION_TOKEN originalImpersonationToken = INVALID_HANDLE_VALUE;

    /* General operation setup work */
    setupError = Operation_Execute_SetupOperation(session, flags, OPERATION_INSTANCE, options, callbacks, MI_T("query instance"), operation, &protocolHandlerSession, &protocolHandlerCallbacks, &operationObject, &protocolHandlerOptions, &protocolHandlerItem, &originalImpersonationToken);
    if (setupError != MI_RESULT_OK)
    {
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, setupError, callbacks, session, operation);
        return;
    }

    /* Validate that transport supports this operation */
    if (protocolHandlerSession.ft == NULL || protocolHandlerSession.ft->QueryInstances == NULL)
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_NOT_SUPPORTED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    /* Hold the final result refcount. */
    if (!ThunkHandle_AddRef(operationObject->operationNode.clientHandle.thunkHandle))
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_FAILED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    operationObject->clientOperationPtr = operation;
    operationObject->clientSessionPtr = session;
    trace_MIClient_QueryInstances(session, operation, operationObject, namespaceName?namespaceName:MI_T("<null>"), queryDialect, queryExpression);

    /* Call in to protocol handler */
    ProtocolHandlerCache_IncrementApiCount(protocolHandlerItem);
    protocolHandlerSession.ft->QueryInstances(&protocolHandlerSession, flags | MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, &protocolHandlerOptions, namespaceName, queryDialect, queryExpression, &protocolHandlerCallbacks, &operationObject->protocolHandlerOperation);
    ProtocolHandlerCache_DecrementApiCount(protocolHandlerItem);

    /* Operation is now asynchronous */

    /* cleanup anything we created that no longer need (we only create then if we have a options parameter, at least for now) */
    if (options)
    {
        MI_OperationOptions_Delete(&protocolHandlerOptions);
    }
    if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
    {
        TerminateProcess(GetCurrentProcess(), -1);
    }
}

void MI_CALL Operation_Execute_AssociatorInstances(
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
    MI_Result setupError;
    MI_Session protocolHandlerSession = MI_SESSION_NULL;
    MI_OperationCallbacks protocolHandlerCallbacks = MI_OPERATIONCALLBACKS_NULL;
    OperationObject *operationObject = NULL;
    MI_OperationOptions protocolHandlerOptions = MI_OPERATIONOPTIONS_NULL;
    ProtocolHandlerCacheItem *protocolHandlerItem;
    MI_CLIENT_IMPERSONATION_TOKEN originalImpersonationToken = INVALID_HANDLE_VALUE;

    /* Parameter validation specific to this function */
    if (instanceKey == NULL)
    {
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_INVALID_PARAMETER, callbacks, session, operation);
        return;
    }

    /* General operation setup work */
    setupError = Operation_Execute_SetupOperation(session, flags, OPERATION_INSTANCE, options, callbacks, MI_T("get associated instance"), operation, &protocolHandlerSession, &protocolHandlerCallbacks, &operationObject, &protocolHandlerOptions, &protocolHandlerItem, &originalImpersonationToken);
    if (setupError != MI_RESULT_OK)
    {
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, setupError, callbacks, session, operation);
        return;
    }

    /* Validate that transport supports this operation */
    if (protocolHandlerSession.ft == NULL || protocolHandlerSession.ft->AssociatorInstances == NULL)
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_NOT_SUPPORTED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    /* Hold the final result refcount. */
    if (!ThunkHandle_AddRef(operationObject->operationNode.clientHandle.thunkHandle))
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_FAILED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    operationObject->clientOperationPtr = operation;
    operationObject->clientSessionPtr = session;
    trace_MIClient_AssociatorInstances(session, operation, operationObject, namespaceName?namespaceName:MI_T("<null>"), (void *) instanceKey, assocClass, resultClass, role, resultRole);

    /* Call in to protocol handler */
    ProtocolHandlerCache_IncrementApiCount(protocolHandlerItem);
    protocolHandlerSession.ft->AssociatorInstances(&protocolHandlerSession, flags | MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, &protocolHandlerOptions, namespaceName, instanceKey, assocClass, resultClass, role, resultRole, keysOnly, &protocolHandlerCallbacks, &operationObject->protocolHandlerOperation);
    ProtocolHandlerCache_DecrementApiCount(protocolHandlerItem);

    /* Operation is now asynchronous */

    /* cleanup anything we created that no longer need (we only create then if we have a options parameter, at least for now) */
    if (options)
    {
        MI_OperationOptions_Delete(&protocolHandlerOptions);
    }
    if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
    {
        TerminateProcess(GetCurrentProcess(), -1);
    }
}

void MI_CALL Operation_Execute_ReferenceInstances(
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
    MI_Result setupError;
    MI_Session protocolHandlerSession = MI_SESSION_NULL;
    MI_OperationCallbacks protocolHandlerCallbacks = MI_OPERATIONCALLBACKS_NULL;
    OperationObject *operationObject = NULL;
    MI_OperationOptions protocolHandlerOptions = MI_OPERATIONOPTIONS_NULL;
    ProtocolHandlerCacheItem *protocolHandlerItem;
    MI_CLIENT_IMPERSONATION_TOKEN originalImpersonationToken = INVALID_HANDLE_VALUE;

    /* Parameter validation specific to this function */
    if (instanceKey == NULL)
    {
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_INVALID_PARAMETER, callbacks, session, operation);
        return;
    }

    /* General operation setup work */
    setupError = Operation_Execute_SetupOperation(session, flags, OPERATION_INSTANCE, options, callbacks, MI_T("get reference instance"), operation, &protocolHandlerSession, &protocolHandlerCallbacks, &operationObject, &protocolHandlerOptions, &protocolHandlerItem, &originalImpersonationToken);
    if (setupError != MI_RESULT_OK)
    {
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, setupError, callbacks, session, operation);
        return;
    }

    /* Validate that transport supports this operation */
    if (protocolHandlerSession.ft == NULL || protocolHandlerSession.ft->ReferenceInstances == NULL)
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_NOT_SUPPORTED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    /* Hold the final result refcount. */
    if (!ThunkHandle_AddRef(operationObject->operationNode.clientHandle.thunkHandle))
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_FAILED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    operationObject->clientOperationPtr = operation;
    operationObject->clientSessionPtr = session;
    trace_MIClient_ReferenceInstances(session, operation, operationObject, namespaceName?namespaceName:MI_T("<null>"), resultClass, role);

    /* Call in to protocol handler */
    ProtocolHandlerCache_IncrementApiCount(protocolHandlerItem);
    protocolHandlerSession.ft->ReferenceInstances(&protocolHandlerSession, flags | MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, &protocolHandlerOptions, namespaceName, instanceKey, resultClass, role, keysOnly, &protocolHandlerCallbacks, &operationObject->protocolHandlerOperation);
    ProtocolHandlerCache_DecrementApiCount(protocolHandlerItem);

    /* Operation is now asynchronous */

    /* cleanup anything we created that no longer need (we only create then if we have a options parameter, at least for now) */
    if (options)
    {
        MI_OperationOptions_Delete(&protocolHandlerOptions);
    }
    if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
    {
        TerminateProcess(GetCurrentProcess(), -1);
    }
}

/* Execute a Modify Instance operation */
void MI_CALL Operation_Execute_ModifyInstance(
    _In_       MI_Session *session,
               MI_Uint32 flags,
    _In_opt_   MI_OperationOptions *options,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_       const MI_Instance *inboundInstance,
    _In_opt_   MI_OperationCallbacks *callbacks,
    _Out_      MI_Operation *operation)
{
    MI_Result setupError;
    MI_Session protocolHandlerSession = MI_SESSION_NULL;
    MI_OperationCallbacks protocolHandlerCallbacks = MI_OPERATIONCALLBACKS_NULL;
    OperationObject *operationObject = NULL;
    MI_OperationOptions protocolHandlerOptions = MI_OPERATIONOPTIONS_NULL;
    ProtocolHandlerCacheItem *protocolHandlerItem;
    MI_CLIENT_IMPERSONATION_TOKEN originalImpersonationToken = INVALID_HANDLE_VALUE;

    /* Parameter validation specific to this function */
    if (inboundInstance == NULL)
    {
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_INVALID_PARAMETER, callbacks, session, operation);
        return;
    }

    /* General operation setup work */
    setupError = Operation_Execute_SetupOperation(session, flags, OPERATION_INSTANCE, options, callbacks, MI_T("modify instance"), operation, &protocolHandlerSession, &protocolHandlerCallbacks, &operationObject, &protocolHandlerOptions, &protocolHandlerItem, &originalImpersonationToken);
    if (setupError != MI_RESULT_OK)
    {
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, setupError, callbacks, session, operation);
        return;
    }

    /* Validate that transport supports this operation */
    if (protocolHandlerSession.ft == NULL || protocolHandlerSession.ft->ModifyInstance == NULL)
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_NOT_SUPPORTED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    /* Hold the final result refcount. */
    if (!ThunkHandle_AddRef(operationObject->operationNode.clientHandle.thunkHandle))
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_FAILED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    operationObject->clientOperationPtr = operation;
    operationObject->clientSessionPtr = session;
    trace_MIClient_ModifyInstance(session, operation, operationObject, namespaceName?namespaceName:MI_T("<null>"));

    ProtocolHandlerCache_IncrementApiCount(protocolHandlerItem);
    protocolHandlerSession.ft->ModifyInstance(&protocolHandlerSession, flags | MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, &protocolHandlerOptions, namespaceName, inboundInstance, &protocolHandlerCallbacks, &operationObject->protocolHandlerOperation);
    ProtocolHandlerCache_DecrementApiCount(protocolHandlerItem);

    /* cleanup anything we created that no longer need (we only create then if we have a options parameter, at least for now) */
    if (options)
    {
        MI_OperationOptions_Delete(&protocolHandlerOptions);
    }
    if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
    {
        TerminateProcess(GetCurrentProcess(), -1);
    }
}

/* Execute a Create Instance operation */
void MI_CALL Operation_Execute_CreateInstance(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_     const MI_Instance *inboundInstance,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation)
{
    MI_Result setupError;
    MI_Session protocolHandlerSession = MI_SESSION_NULL;
    MI_OperationCallbacks protocolHandlerCallbacks = MI_OPERATIONCALLBACKS_NULL;
    OperationObject *operationObject = NULL;
    MI_OperationOptions protocolHandlerOptions = MI_OPERATIONOPTIONS_NULL;
    ProtocolHandlerCacheItem *protocolHandlerItem;
    MI_CLIENT_IMPERSONATION_TOKEN originalImpersonationToken = INVALID_HANDLE_VALUE;

    /* Parameter validation specific to this function */
    if (inboundInstance == NULL)
    {
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_INVALID_PARAMETER, callbacks, session, operation);
        return;
    }

    /* General operation setup work */
    setupError = Operation_Execute_SetupOperation(session, flags, OPERATION_INSTANCE, options, callbacks, MI_T("create instance"), operation, &protocolHandlerSession, &protocolHandlerCallbacks, &operationObject, &protocolHandlerOptions, &protocolHandlerItem, &originalImpersonationToken);
    if (setupError != MI_RESULT_OK)
    {
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, setupError, callbacks, session, operation);
        return;
    }

    /* Validate that transport supports this operation */
    if (protocolHandlerSession.ft == NULL || protocolHandlerSession.ft->CreateInstance == NULL)
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_NOT_SUPPORTED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    /* Hold the final result refcount. */
    if (!ThunkHandle_AddRef(operationObject->operationNode.clientHandle.thunkHandle))
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_FAILED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    operationObject->clientOperationPtr = operation;
    operationObject->clientSessionPtr = session;
    trace_MIClient_CreateInstance(session, operation, operationObject, namespaceName?namespaceName:MI_T("<null>"));

    ProtocolHandlerCache_IncrementApiCount(protocolHandlerItem);
    protocolHandlerSession.ft->CreateInstance(&protocolHandlerSession, flags | MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, &protocolHandlerOptions, namespaceName, inboundInstance, &protocolHandlerCallbacks, &operationObject->protocolHandlerOperation);
    ProtocolHandlerCache_DecrementApiCount(protocolHandlerItem);

    /* cleanup anything we created that no longer need (we only create then if we have a options parameter, at least for now) */
    if (options)
    {
        MI_OperationOptions_Delete(&protocolHandlerOptions);
    }
    if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
    {
        TerminateProcess(GetCurrentProcess(), -1);
    }
}

/* Execute a Delete Instance operation */
void MI_CALL Operation_Execute_DeleteInstance(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationOptions *options,
    _In_opt_z_ const MI_Char * namespaceName,
    _In_     const MI_Instance *inboundInstance,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation)
{
    MI_Result setupError;
    MI_Session protocolHandlerSession = MI_SESSION_NULL;
    MI_OperationCallbacks protocolHandlerCallbacks = MI_OPERATIONCALLBACKS_NULL;
    OperationObject *operationObject = NULL;
    MI_OperationOptions protocolHandlerOptions = MI_OPERATIONOPTIONS_NULL;
    ProtocolHandlerCacheItem *protocolHandlerItem;
    MI_CLIENT_IMPERSONATION_TOKEN originalImpersonationToken = INVALID_HANDLE_VALUE;

    /* Parameter validation specific to this function */
    if (inboundInstance == NULL)
    {
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_INVALID_PARAMETER, callbacks, session, operation);
        return;
    }

    /* General operation setup work */
    setupError = Operation_Execute_SetupOperation(session, flags, OPERATION_INSTANCE, options, callbacks, MI_T("delete instance"), operation, &protocolHandlerSession, &protocolHandlerCallbacks, &operationObject, &protocolHandlerOptions, &protocolHandlerItem, &originalImpersonationToken);
    if (setupError != MI_RESULT_OK)
    {
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, setupError, callbacks, session, operation);
        return;
    }

    /* Validate that transport supports this operation */
    if (protocolHandlerSession.ft == NULL || protocolHandlerSession.ft->DeleteInstance == NULL)
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_NOT_SUPPORTED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    /* Hold the final result refcount. */
    if (!ThunkHandle_AddRef(operationObject->operationNode.clientHandle.thunkHandle))
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_FAILED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    operationObject->clientOperationPtr = operation;
    operationObject->clientSessionPtr = session;
    trace_MIClient_DeleteInstance(session, operation, operationObject, namespaceName?namespaceName:MI_T("<null>"));

    ProtocolHandlerCache_IncrementApiCount(protocolHandlerItem);
    protocolHandlerSession.ft->DeleteInstance(&protocolHandlerSession, flags | MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, &protocolHandlerOptions, namespaceName, inboundInstance, &protocolHandlerCallbacks, &operationObject->protocolHandlerOperation);
    ProtocolHandlerCache_DecrementApiCount(protocolHandlerItem);

    /* cleanup anything we created that no longer need (we only create then if we have a options parameter, at least for now) */
    if (options)
    {
        MI_OperationOptions_Delete(&protocolHandlerOptions);
    }
    if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
    {
        TerminateProcess(GetCurrentProcess(), -1);
    }
}

void MI_CALL Operation_Execute_GetClass(
    _In_       MI_Session *session,
               MI_Uint32 flags,
    _In_opt_   MI_OperationOptions *options,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_opt_z_ const MI_Char *className,
    _In_opt_   MI_OperationCallbacks *callbacks,
    _Out_      MI_Operation *operation)
{
    MI_Result setupError;
    MI_Session protocolHandlerSession = MI_SESSION_NULL;
    MI_OperationCallbacks protocolHandlerCallbacks = MI_OPERATIONCALLBACKS_NULL;
    OperationObject *operationObject = NULL;
    MI_OperationOptions protocolHandlerOptions = MI_OPERATIONOPTIONS_NULL;
    ProtocolHandlerCacheItem *protocolHandlerItem;
    MI_CLIENT_IMPERSONATION_TOKEN originalImpersonationToken = INVALID_HANDLE_VALUE;

    /* General operation setup work */
    setupError = Operation_Execute_SetupOperation(session, flags, OPERATION_CLASS, options, callbacks, MI_T("get class"), operation, &protocolHandlerSession, &protocolHandlerCallbacks, &operationObject, &protocolHandlerOptions, &protocolHandlerItem, &originalImpersonationToken);
    if (setupError != MI_RESULT_OK)
    {
        Operation_Execute_SetupFailure(OPERATION_CLASS, setupError, callbacks, session, operation);
        return;
    }

    /* Validate that transport supports this operation */
    if (protocolHandlerSession.ft == NULL || protocolHandlerSession.ft->GetClass == NULL)
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_CLASS, MI_RESULT_NOT_SUPPORTED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    /* Hold the final result refcount. */
    if (!ThunkHandle_AddRef(operationObject->operationNode.clientHandle.thunkHandle))
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_FAILED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    operationObject->clientOperationPtr = operation;
    operationObject->clientSessionPtr = session;
    trace_MIClient_GetClass(session, operation, operationObject, namespaceName?namespaceName:MI_T("<null>"), className);

    /* Call in to protocol handler */
    ProtocolHandlerCache_IncrementApiCount(protocolHandlerItem);
    protocolHandlerSession.ft->GetClass(&protocolHandlerSession, flags | MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, &protocolHandlerOptions, namespaceName, className, &protocolHandlerCallbacks, &operationObject->protocolHandlerOperation);
    ProtocolHandlerCache_DecrementApiCount(protocolHandlerItem);

    /* Operation is now asynchronous */

    /* cleanup anything we created that no longer need (we only create then if we have a options parameter, at least for now) */
    if (options)
    {
        MI_OperationOptions_Delete(&protocolHandlerOptions);
    }
    if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
    {
        TerminateProcess(GetCurrentProcess(), -1);
    }
}

void MI_CALL Operation_Execute_EnumerateClasses(
    _In_       MI_Session *session,
               MI_Uint32 flags,
    _In_opt_   MI_OperationOptions *options,
    _In_opt_z_ const MI_Char *namespaceName,
    _In_opt_z_ const MI_Char *className,
               MI_Boolean classNamesOnly,
    _In_opt_   MI_OperationCallbacks *callbacks,
    _Out_      MI_Operation *operation)
{
    MI_Result setupError;
    MI_Session protocolHandlerSession = MI_SESSION_NULL;
    MI_OperationCallbacks protocolHandlerCallbacks = MI_OPERATIONCALLBACKS_NULL;
    OperationObject *operationObject = NULL;
    MI_OperationOptions protocolHandlerOptions = MI_OPERATIONOPTIONS_NULL;
    ProtocolHandlerCacheItem *protocolHandlerItem;
    MI_CLIENT_IMPERSONATION_TOKEN originalImpersonationToken = INVALID_HANDLE_VALUE;

    /* General operation setup work */
    setupError = Operation_Execute_SetupOperation(session, flags, OPERATION_CLASS, options, callbacks, MI_T("enumerate class"), operation, &protocolHandlerSession, &protocolHandlerCallbacks, &operationObject, &protocolHandlerOptions, &protocolHandlerItem, &originalImpersonationToken);
    if (setupError != MI_RESULT_OK)
    {
        Operation_Execute_SetupFailure(OPERATION_CLASS, setupError, callbacks, session, operation);
        return;
    }

    /* Validate that transport supports this operation */
    if (protocolHandlerSession.ft == NULL || protocolHandlerSession.ft->EnumerateClasses == NULL)
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_CLASS, MI_RESULT_NOT_SUPPORTED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    /* Hold the final result refcount. */
    if (!ThunkHandle_AddRef(operationObject->operationNode.clientHandle.thunkHandle))
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_FAILED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    operationObject->clientOperationPtr = operation;
    operationObject->clientSessionPtr = session;
    trace_MIClient_EnumerateClasses(session, operation, operationObject, namespaceName?namespaceName:MI_T("<null>"), className);

    /* Call in to protocol handler */
    ProtocolHandlerCache_IncrementApiCount(protocolHandlerItem);
    protocolHandlerSession.ft->EnumerateClasses(&protocolHandlerSession, flags | MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, &protocolHandlerOptions, namespaceName, className, classNamesOnly, &protocolHandlerCallbacks, &operationObject->protocolHandlerOperation);
    ProtocolHandlerCache_DecrementApiCount(protocolHandlerItem);

    /* Operation is now asynchronous */

    /* cleanup anything we created that no longer need (we only create then if we have a options parameter, at least for now) */
    if (options)
    {
        MI_OperationOptions_Delete(&protocolHandlerOptions);
    }
    if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
    {
        TerminateProcess(GetCurrentProcess(), -1);
    }
}

void MI_CALL Operation_Execute_Subscribe(
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
    MI_Result setupError;
    MI_Session protocolHandlerSession = MI_SESSION_NULL;
    MI_OperationCallbacks protocolHandlerCallbacks = MI_OPERATIONCALLBACKS_NULL;
    OperationObject *operationObject = NULL;
    MI_OperationOptions protocolHandlerOptions = MI_OPERATIONOPTIONS_NULL;
    MI_SubscriptionDeliveryOptions protocolHandlerDeliveryOptions = MI_SUBSCRIPTIONDELIVERYOPTIONS_NULL;
    ProtocolHandlerCacheItem *protocolHandlerItem;
    MI_CLIENT_IMPERSONATION_TOKEN originalImpersonationToken = INVALID_HANDLE_VALUE;

    /* General operation setup work */
    setupError = Operation_Execute_SetupOperation(session, flags, OPERATION_INDICATION, options, callbacks, MI_T("subscribe indication"), operation, &protocolHandlerSession, &protocolHandlerCallbacks, &operationObject, &protocolHandlerOptions, &protocolHandlerItem, &originalImpersonationToken);
    if (setupError != MI_RESULT_OK)
    {
        Operation_Execute_SetupFailure(OPERATION_INDICATION, setupError, callbacks, session, operation);
        return;
    }

    if (deliverOptions)
    {
        /* TODO: Duplicate the delivery options into the protocol handler protocolHandlerDeliveryOptions */
        MI_Application phApplication = MI_APPLICATION_NULL;

        MI_SubscriptionDeliveryType deliveryType = (MI_SubscriptionDeliveryType) deliverOptions->reserved1;

        setupError = Session_GetProtocolHandlerApplication(session, &phApplication);
        if (setupError != MI_RESULT_OK)
        {
            operationObject->consumedFinalResult = MI_TRUE;
            Operation_Close(operation);
            Operation_Execute_SetupFailure(OPERATION_INDICATION, setupError, callbacks, session, operation);
            if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
            {
                TerminateProcess(GetCurrentProcess(), -1);
            }
            return ;
        }

        setupError = MI_Application_NewSubscriptionDeliveryOptions(&phApplication, deliveryType, &protocolHandlerDeliveryOptions);
        if (setupError != MI_RESULT_OK)
        {
            operationObject->consumedFinalResult = MI_TRUE;
            Operation_Close(operation);
            Operation_Execute_SetupFailure(OPERATION_INDICATION, setupError, callbacks, session, operation);
            if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
            {
                TerminateProcess(GetCurrentProcess(), -1);
            }
            return ;
        }
        setupError = SubscriptionDeliveryOptions_MigrateOptions(deliverOptions, &protocolHandlerDeliveryOptions);
        if (setupError != MI_RESULT_OK)
        {
            operationObject->consumedFinalResult = MI_TRUE;
            Operation_Close(operation);
            Operation_Execute_SetupFailure(OPERATION_INDICATION, setupError, callbacks, session, operation);
            MI_SubscriptionDeliveryOptions_Delete(&protocolHandlerDeliveryOptions);
            if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
            {
                TerminateProcess(GetCurrentProcess(), -1);
            }
            return ;
        }
    }

    /* Validate that transport supports this operation */
    if (protocolHandlerSession.ft == NULL || protocolHandlerSession.ft->Subscribe == NULL)
    {
        if (deliverOptions)
        {
            MI_SubscriptionDeliveryOptions_Delete(&protocolHandlerDeliveryOptions);
        }
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INDICATION, MI_RESULT_NOT_SUPPORTED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    /* Hold the final result refcount. */
    if (!ThunkHandle_AddRef(operationObject->operationNode.clientHandle.thunkHandle))
    {
        if (deliverOptions)
        {
            MI_SubscriptionDeliveryOptions_Delete(&protocolHandlerDeliveryOptions);
        }
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_FAILED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    operationObject->clientOperationPtr = operation;
    operationObject->clientSessionPtr = session;
    trace_MIClient_Subscribe(session, operation, operationObject, namespaceName?namespaceName:MI_T("<null>"), queryDialect, queryExpression);

    /* Call in to protocol handler */
    ProtocolHandlerCache_IncrementApiCount(protocolHandlerItem);
    protocolHandlerSession.ft->Subscribe(&protocolHandlerSession, flags | MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, &protocolHandlerOptions, namespaceName, queryDialect, queryExpression, deliverOptions?&protocolHandlerDeliveryOptions:NULL, &protocolHandlerCallbacks, &operationObject->protocolHandlerOperation);
    ProtocolHandlerCache_DecrementApiCount(protocolHandlerItem);

    /* Operation is now asynchronous */

    /* cleanup anything we created that no longer need (we only create then if we have a options parameter, at least for now) */
    if (options)
    {
        MI_OperationOptions_Delete(&protocolHandlerOptions);
    }
    if (deliverOptions)
    {
        MI_SubscriptionDeliveryOptions_Delete(&protocolHandlerDeliveryOptions);
    }
    if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
    {
        TerminateProcess(GetCurrentProcess(), -1);
    }
}

void MI_CALL Operation_Execute_TestConnection(
    _In_     MI_Session *session,
             MI_Uint32 flags,
    _In_opt_ MI_OperationCallbacks *callbacks,
    _Out_    MI_Operation *operation
    )
{
    MI_Result setupError;
    MI_Session protocolHandlerSession = MI_SESSION_NULL;
    MI_OperationCallbacks protocolHandlerCallbacks = MI_OPERATIONCALLBACKS_NULL;
    OperationObject *operationObject = NULL;
    ProtocolHandlerCacheItem *protocolHandlerItem;
    MI_CLIENT_IMPERSONATION_TOKEN originalImpersonationToken = INVALID_HANDLE_VALUE;

    /* General operation setup work */
    setupError = Operation_Execute_SetupOperation(session, flags, OPERATION_INSTANCE, NULL, callbacks, MI_T("test connection"), operation, &protocolHandlerSession, &protocolHandlerCallbacks, &operationObject, NULL, &protocolHandlerItem, &originalImpersonationToken);
    if (setupError != MI_RESULT_OK)
    {
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, setupError, callbacks, session, operation);
        return;
    }

    /* Validate that transport supports this operation */
    if (protocolHandlerSession.ft == NULL || protocolHandlerSession.ft->TestConnection == NULL)
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_NOT_SUPPORTED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    /* Hold the final result refcount. */
    if (!ThunkHandle_AddRef(operationObject->operationNode.clientHandle.thunkHandle))
    {
        operationObject->consumedFinalResult = MI_TRUE;
        Operation_Close(operation);
        Operation_Execute_SetupFailure(OPERATION_INSTANCE, MI_RESULT_FAILED, callbacks, session, operation);
        if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return;
    }

    operationObject->clientOperationPtr = operation;
    operationObject->clientSessionPtr = session;
    trace_MIClient_TestConnection(session, operation, operationObject);

    /* Call in to protocol handler */
    ProtocolHandlerCache_IncrementApiCount(protocolHandlerItem);
    protocolHandlerSession.ft->TestConnection(&protocolHandlerSession, flags | MI_OPERATIONFLAGS_MANUAL_ACK_RESULTS, &protocolHandlerCallbacks, &operationObject->protocolHandlerOperation);
    ProtocolHandlerCache_DecrementApiCount(protocolHandlerItem);

    /* Operation is now asynchronous */
    if (Session_RevertImpersonation(originalImpersonationToken) != MI_RESULT_OK)
    {
        TerminateProcess(GetCurrentProcess(), -1);
    }
}
/* Do synchronous retrieval of results */
MI_Result MI_CALL Operation_GetInstance_Result(
    _In_      MI_Operation *operation,
    _Outptr_result_maybenull_     const MI_Instance **instance,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Outptr_opt_result_maybenull_z_ const MI_Char **errorMessage,
    _Outptr_opt_result_maybenull_ const MI_Instance **completionDetails)
{
    if ((operation == NULL) || (instance == NULL))
    {
        if (result)
            *result = MI_RESULT_INVALID_PARAMETER;
        return MI_RESULT_INVALID_PARAMETER;
    }

    /* Zero out parameters */
    *instance = NULL;

    if (moreResults)
    {
        *moreResults = MI_FALSE;
    }
    if (result)
    {
        *result = MI_RESULT_OK;
    }
    if (errorMessage)
    {
        *errorMessage = NULL;
    }
    if (completionDetails)
    {
        *completionDetails = NULL;
    }

    /* Wait for results and return */
    {
        GenericHandle *genericHandle = (GenericHandle*) operation;
        ThunkHandle *thunkHandle;
        MI_Result returnValue = MI_RESULT_OK;

        ThunkHandle_FromGeneric(genericHandle, &thunkHandle);
        if (thunkHandle != NULL)
        {
            OperationObject *operationObject = (OperationObject *) thunkHandle->u.object;
            ptrdiff_t curInstanceCallbackReceived;
            MI_CLIENT_IMPERSONATION_TOKEN originalImpersonation = INVALID_HANDLE_VALUE;

            returnValue = Session_AccessCheck(&operationObject->clientSession, MI_T("get operation's instance result"));
            if (returnValue != MI_RESULT_OK)
            {
                ThunkHandle_Release(thunkHandle);
                if (result)
                    *result = returnValue;
                trace_MiSession_AccessCheckFailed(__FUNCTION__, &operationObject->clientSession);
                return returnValue;
            }
            returnValue = Session_ImpersonateClient(&operationObject->clientSession, &originalImpersonation);
            if (returnValue != MI_RESULT_OK)
            {
                ThunkHandle_Release(thunkHandle);
                if (result)
                    *result = returnValue;
                return returnValue;
            }

            if ((operationObject->callbacks.instanceResult == NULL) && (operationObject->operationType == OPERATION_INSTANCE))
            {
                if(operationObject->consumedFinalResult == MI_FALSE)
                {
                    if (operationObject->consumedResult)
                    {
                        /* We need to acknowledge the current item, reset the state and wait for the next item
                         * to be retrieved
                         */
                        MI_Result (MI_CALL * tmpResultAcknowledgement)(_In_ MI_Operation *operation) = operationObject->ph_instance_resultAcknowledgement;
                        operationObject->ph_instance_resultAcknowledgement = NULL; /* Calling ack so clear it out */
                        operationObject->instanceResult = NULL; /* Ack-ing result so wipe it out */
                        operationObject->consumedResult = MI_FALSE; /* Reset consumped result as we have not consumed the one we have not got yet */
                        operationObject->instanceCallbackReceived = 0; /* Reset the callback received as we need to get the next one */
                        tmpResultAcknowledgement(&operationObject->protocolHandlerOperation); /* Ack, we can get callback immediately on this thread, unwind and process next immediately */

                        /* Now we are ready to get more results */
                    }

                    /* Wait for new item */
                    curInstanceCallbackReceived = operationObject->instanceCallbackReceived;
                    while (!curInstanceCallbackReceived)
                    {
                        /* 0 is the current value of state, the value we don't want to see. */
                        CondLock_Wait((ptrdiff_t) operationObject, &operationObject->instanceCallbackReceived, curInstanceCallbackReceived, CONDLOCK_DEFAULT_SPINCOUNT);
                        curInstanceCallbackReceived = operationObject->instanceCallbackReceived;
                    }

                    /* We have result, so fill in out parameters and return them to the user */
                    *instance = operationObject->instanceResult;
                    if (moreResults)
                    {
                        *moreResults = operationObject->moreResults;
                    }
                    if (result)
                    {
                        *result = operationObject->resultCode;
                    }
                    if (errorMessage)
                    {
                        *errorMessage = operationObject->errorString;
                    }
                    if (completionDetails)
                    {
                        *completionDetails = operationObject->errorDetails;
                    }

                    /* These results got consumed by this call */
                    operationObject->consumedResult = MI_TRUE;

                    if (!operationObject->moreResults)
                    {
                        operationObject->consumedFinalResult = MI_TRUE;
                        operationObject->currentState = Completed;

                        //Some threads may be waiting on this notification so wake them up
                        CondLock_Broadcast((ptrdiff_t)&operationObject->consumedFinalResult);

                        //No more results, so release the refcount we have for final result
                        ThunkHandle_Release(thunkHandle);
                    }

                    trace_MIClient_OperationInstanceResultSync(operationObject->clientSessionPtr, operationObject->clientOperationPtr, operationObject, operationObject->resultCode, operationObject->moreResults?MI_T("TRUE"):MI_T("FALSE"));
                }
                else
                {
                    if (result)
                    {
                        *result = operationObject->resultCode;
                    }
                    if (moreResults)
                    {
                        *moreResults = MI_FALSE;
                    }
                }
            }
            else
            {
                if (result)
                    *result = MI_RESULT_INVALID_PARAMETER;
                returnValue = MI_RESULT_INVALID_PARAMETER;
            }

            //Release our own refcount
            ThunkHandle_Release(thunkHandle);

            if (Session_RevertImpersonation(originalImpersonation) != MI_RESULT_OK)
            {
                TerminateProcess(GetCurrentProcess(), -1);
            }
        }
        else
        {
            /* Failed to thunk handle */
            if (result)
                *result = MI_RESULT_INVALID_PARAMETER;
            returnValue = MI_RESULT_INVALID_PARAMETER;
        }
        return returnValue;
    }
}

MI_Result MI_CALL Operation_GetIndication_Result(
    _In_      MI_Operation *operation,
    _Outptr_result_maybenull_       const MI_Instance **instance,
    _Outptr_opt_result_maybenull_z_ const MI_Char **bookmark,
    _Outptr_opt_result_maybenull_z_ const MI_Char **machineID,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Outptr_opt_result_maybenull_z_ const MI_Char **errorMessage,
    _Outptr_opt_result_maybenull_   const MI_Instance **completionDetails)
{
    /* validate parameters */
    if ((operation == NULL) || (instance == NULL))
    {
        if (result)
            *result = MI_RESULT_INVALID_PARAMETER;
        return MI_RESULT_INVALID_PARAMETER;
    }

    /* Zero out parameters */
    *instance = NULL;

    if (bookmark)
    {
        *bookmark = NULL;
    }
    if (machineID)
    {
        *machineID = NULL;
    }
    if (moreResults)
    {
        *moreResults = MI_FALSE;
    }
    if (result)
    {
        *result = MI_RESULT_OK;
    }
    if (errorMessage)
    {
        *errorMessage = NULL;
    }
    if (completionDetails)
    {
        *completionDetails = NULL;
    }

    /* Wait for results and return */
    {
        GenericHandle *genericHandle = (GenericHandle*) operation;
        ThunkHandle *thunkHandle;
        MI_Result returnValue = MI_RESULT_OK;

        ThunkHandle_FromGeneric(genericHandle, &thunkHandle);
        if (thunkHandle != NULL)
        {
            OperationObject *operationObject = (OperationObject *) thunkHandle->u.object;
            ptrdiff_t curInstanceCallbackReceived;
            MI_CLIENT_IMPERSONATION_TOKEN originalImpersonation = INVALID_HANDLE_VALUE;

            /* Access check */
            returnValue = Session_AccessCheck(&operationObject->clientSession, MI_T("get operation's indication result"));
            if (returnValue != MI_RESULT_OK)
            {
                ThunkHandle_Release(thunkHandle);
                if (result)
                    *result = returnValue;
                trace_MiSession_AccessCheckFailed(__FUNCTION__, &operationObject->clientSession);
                return returnValue;
            }
            returnValue = Session_ImpersonateClient(&operationObject->clientSession, &originalImpersonation);
            if (returnValue != MI_RESULT_OK)
            {
                ThunkHandle_Release(thunkHandle);
                if (result)
                    *result = returnValue;
                return returnValue;
            }

            if ((operationObject->callbacks.indicationResult == NULL) && (operationObject->operationType == OPERATION_INDICATION))
            {
                if(operationObject->consumedFinalResult == MI_FALSE)
                {
                    if (operationObject->consumedResult)
                    {
                        /* We need to acknowledge the current item, reset the state and wait for the next item
                         * to be retrieved
                         */
                        MI_Result (MI_CALL * tmpResultAcknowledgement)(_In_ MI_Operation *operation) = operationObject->ph_instance_resultAcknowledgement;
                        operationObject->ph_instance_resultAcknowledgement = NULL; /* Calling ack so clear it out */
                        operationObject->instanceResult = NULL; /* Ack-ing result so wipe it out */
                        operationObject->bookmark = NULL;
                        operationObject->machineID = NULL;
                        operationObject->consumedResult = MI_FALSE; /* Reset consumped result as we have not consumed the one we have not got yet */
                        operationObject->instanceCallbackReceived = 0; /* Reset the callback received as we need to get the next one */
                        tmpResultAcknowledgement(&operationObject->protocolHandlerOperation); /* Ack, we can get callback immediately on this thread, unwind and process next immediately */

                        /* Now we are ready to get more results */
                    }

                    /* Wait for new item */
                    curInstanceCallbackReceived = operationObject->instanceCallbackReceived;
                    while (!curInstanceCallbackReceived)
                    {
                        /* 0 is the current value of state, the value we don't want to see. */
                        CondLock_Wait((ptrdiff_t)operationObject, &operationObject->instanceCallbackReceived, curInstanceCallbackReceived, CONDLOCK_DEFAULT_SPINCOUNT);
                        curInstanceCallbackReceived = operationObject->instanceCallbackReceived;
                    }

                    /* We have result, so fill in out parameters and return them to the user */
                    *instance = operationObject->instanceResult;
                    if (bookmark)
                    {
                        *bookmark = operationObject->bookmark;
                    }
                    if (machineID)
                    {
                        *machineID = operationObject->machineID;
                    }
                    if (moreResults)
                    {
                        *moreResults = operationObject->moreResults;
                    }
                    if (result)
                    {
                        *result = operationObject->resultCode;
                    }
                    if (errorMessage)
                    {
                        *errorMessage = operationObject->errorString;
                    }
                    if (completionDetails)
                    {
                        *completionDetails = operationObject->errorDetails;
                    }

                    /* These results got consumed by this call */
                    operationObject->consumedResult = MI_TRUE;

                    if (!operationObject->moreResults)
                    {
                        operationObject->consumedFinalResult = MI_TRUE;

                        //Some threads may be waiting on this notification so wake them up
                        CondLock_Broadcast((ptrdiff_t)&operationObject->consumedFinalResult);

                        //No more results, so release the refcount we have for final result
                        ThunkHandle_Release(thunkHandle);
                    }
                    trace_MIClient_IndicationResultSync(operationObject->clientSessionPtr, operationObject->clientOperationPtr, operationObject, operationObject->resultCode, operationObject->moreResults?MI_T("TRUE"):MI_T("FALSE"));
                }
                else
                {
                    if (result)
                    {
                        *result = operationObject->resultCode;
                    }
                    if (moreResults)
                    {
                        *moreResults = MI_FALSE;
                    }
                }
            }
            else
            {
                if (result)
                    *result = MI_RESULT_INVALID_PARAMETER;
                returnValue = MI_RESULT_INVALID_PARAMETER;
            }
            ThunkHandle_Release(thunkHandle);

            if (Session_RevertImpersonation(originalImpersonation) != MI_RESULT_OK)
            {
                TerminateProcess(GetCurrentProcess(), -1);
            }
        }
        else
        {
            /* Failed to thunk handle */
            if (result)
                *result = MI_RESULT_INVALID_PARAMETER;
            returnValue = MI_RESULT_INVALID_PARAMETER;
        }
        return returnValue;
    }
}

MI_Result MI_CALL Operation_GetClass_Result(
    _In_      MI_Operation *operation,
    _Outptr_result_maybenull_     const MI_Class **classResult,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Outptr_opt_result_maybenull_z_ const MI_Char **errorMessage,
    _Outptr_opt_result_maybenull_ const MI_Instance **completionDetails)
{
    /* valudate parameters */
    if ((operation == NULL) || (classResult == NULL))
    {
        if (result)
            *result = MI_RESULT_INVALID_PARAMETER;
        return MI_RESULT_INVALID_PARAMETER;
    }

    /* Zero out parameters */
    *classResult = NULL;
    if (moreResults)
    {
        *moreResults = MI_FALSE;
    }
    if (result)
    {
        *result = MI_RESULT_OK;
    }
    if (errorMessage)
    {
        *errorMessage = NULL;
    }
    if (completionDetails)
    {
        *completionDetails = NULL;
    }

    /* Wait for results and return */
    {
        GenericHandle *genericHandle = (GenericHandle*) operation;
        ThunkHandle *thunkHandle;
        MI_Result returnResult = MI_RESULT_OK;

        ThunkHandle_FromGeneric(genericHandle, &thunkHandle);
        if (thunkHandle != NULL)
        {
            OperationObject *operationObject = (OperationObject *) thunkHandle->u.object;
            ptrdiff_t curInstanceCallbackReceived;
            MI_CLIENT_IMPERSONATION_TOKEN originalImpersonation = INVALID_HANDLE_VALUE;

            returnResult = Session_AccessCheck(&operationObject->clientSession, MI_T("get operation's class result"));
            if (returnResult != MI_RESULT_OK)
            {
                ThunkHandle_Release(thunkHandle);
                if (result)
                    *result = returnResult;
                trace_MiSession_AccessCheckFailed(__FUNCTION__, &operationObject->clientSession);
                return returnResult;
            }
            returnResult = Session_ImpersonateClient(&operationObject->clientSession, &originalImpersonation);
            if (returnResult != MI_RESULT_OK)
            {
                ThunkHandle_Release(thunkHandle);
                 if (result)
                    *result = returnResult;
               return returnResult;
            }

            if ((operationObject->callbacks.classResult == NULL) && (operationObject->operationType == OPERATION_CLASS))
            {
                if(operationObject->consumedFinalResult == MI_FALSE)
                {
                    if (operationObject->consumedResult)
                    {
                        /* We need to acknowledge the current item, reset the state and wait for the next item
                         * to be retrieved
                         */
                        MI_Result (MI_CALL * tmpResultAcknowledgement)(_In_ MI_Operation *operation) = operationObject->ph_instance_resultAcknowledgement;
                        operationObject->ph_instance_resultAcknowledgement = NULL; /* Calling ack so clear it out */
                        operationObject->classResult = NULL; /* Ack-ing result so wipe it out */
                        operationObject->consumedResult = MI_FALSE; /* Reset consumped result as we have not consumed the one we have not got yet */
                        operationObject->instanceCallbackReceived = 0; /* Reset the callback received as we need to get the next one */
                        tmpResultAcknowledgement(&operationObject->protocolHandlerOperation); /* Ack, we can get callback immediately on this thread, unwind and process next immediately */

                        /* Now we are ready to get more results */
                    }

                    /* Wait for new item */
                    curInstanceCallbackReceived = operationObject->instanceCallbackReceived;
                    while (!curInstanceCallbackReceived)
                    {
                        /* 0 is the current value of state, the value we don't want to see. */
                        CondLock_Wait((ptrdiff_t)operationObject, &operationObject->instanceCallbackReceived, curInstanceCallbackReceived, CONDLOCK_DEFAULT_SPINCOUNT);
                        curInstanceCallbackReceived = operationObject->instanceCallbackReceived;
                    }

                    /* We have result, so fill in out parameters and return them to the user */
                    *classResult = operationObject->classResult;
                    if (moreResults)
                    {
                        *moreResults = operationObject->moreResults;
                    }
                    if (result)
                    {
                        *result = operationObject->resultCode;
                    }
                    if (errorMessage)
                    {
                        *errorMessage = operationObject->errorString;
                    }
                    if (completionDetails)
                    {
                        *completionDetails = operationObject->errorDetails;
                    }

                    /* These results got consumed by this call */
                    operationObject->consumedResult = MI_TRUE;

                    if (!operationObject->moreResults)
                    {
                        operationObject->consumedFinalResult = MI_TRUE;

                        //Some threads may be waiting on this notification so wake them up
                        CondLock_Broadcast((ptrdiff_t)&operationObject->consumedFinalResult);

                        //No more results, so release the refcount we have for final result
                        ThunkHandle_Release(thunkHandle);
                    }


                    trace_MIClient_ClassResultSync(operationObject->clientSessionPtr, operationObject->clientOperationPtr, operationObject, operationObject->resultCode, operationObject->moreResults?MI_T("TRUE"):MI_T("FALSE"));
                }
                else
                {
                    if (result)
                    {
                        *result = operationObject->resultCode;
                    }
                    if (moreResults)
                    {
                        *moreResults = MI_FALSE;
                    }
                }
            }
            else
            {
                if (result)
                    *result = MI_RESULT_INVALID_PARAMETER;
                returnResult = MI_RESULT_INVALID_PARAMETER;
            }
            ThunkHandle_Release(thunkHandle);

            if (Session_RevertImpersonation(originalImpersonation) != MI_RESULT_OK)
            {
                TerminateProcess(GetCurrentProcess(), -1);
            }
        }
        else
        {
            /* Failed to thunk handle */
            if (result)
                *result = MI_RESULT_INVALID_PARAMETER;
            returnResult = MI_RESULT_INVALID_PARAMETER;
        }
        return returnResult;
    }
}

/* Master operation function table */
const MI_OperationFT g_operationFT = {
    Operation_Close,
    Operation_Cancel,
    Operation_GetParentSession,
    Operation_GetInstance_Result,
    Operation_GetIndication_Result,
    Operation_GetClass_Result
};

/* Failed version is for when operation failed to create.
 * Error is encoded in client handler with a special implementation of close and GetInstance
 */
const MI_OperationFT g_operationFT_Failed = {
    Operation_Close_Failed,
    Operation_Cancel_Failed,
    Operation_GetParentSession_Failed,
    Operation_GetInstance_Result_Failed,
    Operation_GetIndication_Result_Failed,
    Operation_GetClass_Result_Failed
};
const MI_OperationFT g_operationFT_OOM = {
    Operation_Close_Failed,
    Operation_Cancel_Failed,
    Operation_GetParentSession_Failed,
    Operation_GetInstance_Result_OOM,
    Operation_GetIndication_Result_OOM,
    Operation_GetClass_Result_OOM
};
const MI_OperationFT g_operationFT_InvalidParameter = {
    Operation_Close_Failed,
    Operation_Cancel_Failed,
    Operation_GetParentSession_Failed,
    Operation_GetInstance_Result_InvalidParameter,
    Operation_GetIndication_Result_InvalidParameter,
    Operation_GetClass_Result_InvalidParameter
};
const MI_OperationFT g_operationFT_NotSupported = {
    Operation_Close_Failed,
    Operation_Cancel_Failed,
    Operation_GetParentSession_Failed,
    Operation_GetInstance_Result_NotSupported,
    Operation_GetIndication_Result_NotSupported,
    Operation_GetClass_Result_NotSupported
};

const MI_OperationFT g_operationFT_AccessDenied = {
    Operation_Close_Failed,
    Operation_Cancel_Failed,
    Operation_GetParentSession_Failed,
    Operation_GetInstance_Result_AccessDenied,
    Operation_GetIndication_Result_AccessDenied,
    Operation_GetClass_Result_AccessDenied
};
