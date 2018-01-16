/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <base/user.h>
#include "miapi_common.h"
#include "Application.h"
#include "Session.h"
#include "Operation.h"
#include "SafeHandle.h"
#include "ChildList.h"
#include "Options.h"
#include <MI.h>
#include <pal/lock.h>
#include <pal/format.h>
#include <base/log.h>

/* Defined for real at bottom of file */
extern const MI_SessionFT g_sessionFT; /* Main function table for session */
extern const MI_SessionFT g_sessionFT_OOM; /* Special out of memory version */

/* Real back-end MI_Session structure */
typedef struct _SessionObject SessionObject;

struct _SessionObject
{
    /* Linked list for child application sessions.  Includes clients session handle */
    ChildListNode sessionNode;

    MI_Application clientApplication;
    ProtocolHandlerCacheItem *protocolHandlerItem;
    MI_Session protocolHandlerSession;
    MI_Session *clientSessionPtr;  /*Pointer for client session for logging purposes only */
    MI_SessionCallbacks callbacks;
    ChildList operationList;    /* List of child operations */
    MI_DestinationOptions clientDestinationOptions;

    uid_t uid;
    gid_t gid; 

    /* MI_Session_Close data */
    void *sessionCloseCallbackContext;
    void (MI_CALL *sessionCloseCallback)(_In_opt_ void *completionContext) ;
    volatile ptrdiff_t sessionCloseCallbackCalled;
};

MI_Result Session_ImpersonateClientInternal(_In_ SessionObject *sessionObject, _Out_ MI_CLIENT_IMPERSONATION_TOKEN *originalImpersonation);

/* CIM Extension callback pass-through for WriteMessage */
void MI_CALL Session_WriteMessage_Callback(
    _In_     MI_Application *application,
    _In_opt_ void *callbackContext, 
                MI_Uint32 channel,
    _In_z_   const MI_Char *  message)
{
    SessionObject *sessionObject = (SessionObject*) callbackContext;
    if (sessionObject->callbacks.writeMessage)
    {
        sessionObject->callbacks.writeMessage(&sessionObject->clientApplication, sessionObject->callbacks.callbackContext, channel, message);
    }
}

/* CIM Extensions callback pass-through for WriteError */
void MI_CALL Session_WriteError_Callback(
    _In_     MI_Application *application,
    _In_opt_ void *callbackContext, 
    _In_ MI_Instance *instance)
{
    SessionObject *sessionObject = (SessionObject*) callbackContext;
    if (sessionObject->callbacks.writeError)
    {
        sessionObject->callbacks.writeError(&sessionObject->clientApplication, sessionObject->callbacks.callbackContext, instance);
    }
}

/* When thunk handle ref count gets to zero means no one is referencing this object any more
 * so we can now delete the SessionObject
 */
void Session_Destructor(
    _In_ ThunkHandle *thunkHandle)
{
    SessionObject *sessionObject = (SessionObject *) thunkHandle->u.object;
    thunkHandle->u.object = NULL;
    //NitsAssert(sessionObject->operationList.childCount == 0, L"child operation count should be zero");

    ChildList_DeInitialize(&sessionObject->operationList);

    /* Unregister self from application */
    Application_UnregisterSession(&sessionObject->clientApplication, &sessionObject->sessionNode);

    /* Free our copy of the client-side destination options */
    MI_DestinationOptions_Delete(&sessionObject->clientDestinationOptions);

    PAL_Free(sessionObject);

}
void Session_Destructor_NoAppUnRegister(
    _In_ ThunkHandle *thunkHandle)
{
    SessionObject *sessionObject = (SessionObject *) thunkHandle->u.object;
    //NitsAssert(sessionObject->operationList.childCount == 0, L"child operation count should be zero");

    ChildList_DeInitialize(&sessionObject->operationList);

    /* Note: No need to Unregister self from application as we didn't successfully register */


    PAL_Free(sessionObject);

}

/* PUBLIC: Application calls this
 * This function needs to find the transport handler and load if not already loaded.
 * Then calls into the transport handler to itself to create their session.
 */
_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL Session_Create(
    _In_     MI_Application *application, 
    _In_opt_z_ const MI_Char *protocol,
    _In_opt_z_ const MI_Char *destination,
    _In_opt_ MI_DestinationOptions *options,
    _In_opt_ MI_SessionCallbacks *callbacks,
    _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
    _Out_    MI_Session *session)
{
    SessionObject *sessionObject = NULL;
    MI_DestinationOptions protocolHandlerDestinationOptions = MI_DESTINATIONOPTIONS_NULL;
    MI_DestinationOptions tempDestinationOptions = MI_DESTINATIONOPTIONS_NULL;
    GenericHandle *genericHandle = (GenericHandle *)session;
    MI_SessionCallbacks myCallbacks;
    MI_Result returnCode = MI_RESULT_OK;
    MI_CLIENT_IMPERSONATION_TOKEN originalImpersonation = INVALID_HANDLE_VALUE;

    trace_MISessionEnter(__FUNCTION__, application, protocol, destination, session);

    /* initialize the client session in case we fail to fill it in */
    if (session)
    {
        memset(session, 0, sizeof(MI_Session));
    }
    if (extendedError)
    {
        *extendedError = NULL;
    }

    if ((application == NULL) || (session == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }

    /* Allocate our real back-end session */
    sessionObject = (SessionObject *) PAL_Malloc(sizeof(SessionObject));
    if (sessionObject == NULL)
    {
        session->ft = &g_sessionFT_OOM;
        return MI_RESULT_FAILED;
    }
    memset(sessionObject, 0, sizeof(SessionObject));

    returnCode = ChildList_Initialize(&sessionObject->operationList);
    if (returnCode != MI_RESULT_OK)
    {
        PAL_Free(sessionObject);
        return returnCode;
    }

    /* Get a safe-handle */
    if (Application_NewGenericHandle(application, genericHandle) != MI_RESULT_OK)
    {
        ChildList_DeInitialize(&sessionObject->operationList);
        PAL_Free(sessionObject);
        session->ft = &g_sessionFT_OOM;
        return MI_RESULT_FAILED;
    }

    /* Set up links within thunk handle */
    sessionObject->clientApplication = *application;
    genericHandle->thunkHandle->u.object = sessionObject;


    /* Copy callbacks */
    if (callbacks)
    {
        sessionObject->callbacks = *callbacks;
    }

    /* Set up protocol handlers callbacks to call back into us */
    memset(&myCallbacks, 0, sizeof(myCallbacks));
    myCallbacks.callbackContext = sessionObject;
    myCallbacks.writeMessage = Session_WriteMessage_Callback;
    myCallbacks.writeError = Session_WriteError_Callback;

    /* copy the clients token.  This is the token that all operations validate against */
    sessionObject->uid = getuid();
    sessionObject->gid = getgid();

    /* Register session with application */
    returnCode = Application_RegisterSession(application, &sessionObject->sessionNode);
    if (returnCode != MI_RESULT_OK)
    {
        ThunkHandle_Shutdown(genericHandle->thunkHandle, NULL);
        ChildList_DeInitialize(&sessionObject->operationList);
        PAL_Free(sessionObject);
        session->reserved2 = 0;
        session->ft = &g_sessionFT_OOM;
        return returnCode;
    }

    returnCode = Session_ImpersonateClientInternal(sessionObject, &originalImpersonation);
    if (returnCode != MI_RESULT_OK)
    {
        Application_UnregisterSession(application, &sessionObject->sessionNode);
        ThunkHandle_Shutdown(genericHandle->thunkHandle, NULL);
        ChildList_DeInitialize(&sessionObject->operationList);
        PAL_Free(sessionObject);
        session->reserved2 = 0;
        session->ft = &g_sessionFT_OOM;
        return returnCode;
    }

    /* select transport & load it */
    returnCode = Application_GetProtocolHandler(application, destination, protocol, &sessionObject->protocolHandlerItem);
    if (returnCode != MI_RESULT_OK)
    {
        if (Session_RevertImpersonation(originalImpersonation) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        Application_UnregisterSession(application, &sessionObject->sessionNode);
        ThunkHandle_Shutdown(genericHandle->thunkHandle, NULL);
        ChildList_DeInitialize(&sessionObject->operationList);
        PAL_Free(sessionObject);
        session->reserved2 = 0;
        session->ft = &g_sessionFT_OOM;
        return returnCode;
    }

    /* create a DestinationOptions if not given */
    if (!options)
    {
        returnCode = MI_Application_NewDestinationOptions(application, &tempDestinationOptions);
        if (returnCode == MI_RESULT_OK)
        {
            options = &tempDestinationOptions;
        }
    }

    if (returnCode == MI_RESULT_OK)
    {
        /* duplicate the client options so we can use them to merge with operation options */
        DestinationOptions_Duplicate(options, &sessionObject->clientDestinationOptions);

        /* Create a protocol handler version to use now */
        returnCode = MI_Application_NewDestinationOptions(&sessionObject->protocolHandlerItem->application, &protocolHandlerDestinationOptions);
        if (returnCode == MI_RESULT_OK)
        {
            returnCode = DestinationOptions_MigrateOptions(options, &protocolHandlerDestinationOptions, sessionObject->protocolHandlerItem->name[0] != '\0'? sessionObject->protocolHandlerItem->name : MI_T(""), extendedError);
            if (returnCode != MI_RESULT_OK)
            {
                MI_DestinationOptions_Delete(&protocolHandlerDestinationOptions);
            }
        }
    }

    if (returnCode != MI_RESULT_OK)
    {
        if (tempDestinationOptions.ft != NULL)
        {
            MI_DestinationOptions_Delete(&tempDestinationOptions);
        }
        if (Session_RevertImpersonation(originalImpersonation) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        Application_UnregisterSession(application, &sessionObject->sessionNode);
        ThunkHandle_Shutdown(genericHandle->thunkHandle, NULL);
        ChildList_DeInitialize(&sessionObject->operationList);
        MI_DestinationOptions_Delete(&sessionObject->clientDestinationOptions);
        PAL_Free(sessionObject);
        session->reserved2 = 0;
        session->ft = &g_sessionFT_OOM;
        return returnCode;
    }

    /* Copy client application handle */
    sessionObject->clientApplication = *application;

    returnCode = sessionObject->protocolHandlerItem->application.ft->NewSession(&sessionObject->protocolHandlerItem->application, protocol, destination, &protocolHandlerDestinationOptions, &myCallbacks, extendedError, &sessionObject->protocolHandlerSession);
    if (returnCode != MI_RESULT_OK)
    {
        if (tempDestinationOptions.ft != NULL)
        {
            MI_DestinationOptions_Delete(&tempDestinationOptions);
        }
        MI_DestinationOptions_Delete(&protocolHandlerDestinationOptions);
        ThunkHandle_Shutdown(genericHandle->thunkHandle, Session_Destructor);
        session->reserved2 = 0;
        session->ft = &g_sessionFT_OOM;
        if (Session_RevertImpersonation(originalImpersonation) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
        return returnCode;
    }

    if (tempDestinationOptions.ft != NULL)
    {
        MI_DestinationOptions_Delete(&tempDestinationOptions);
    }

    MI_DestinationOptions_Delete(&protocolHandlerDestinationOptions);

    /* Fix up clients function table to point to us*/
    session->ft = &g_sessionFT;

    sessionObject->clientSessionPtr = session;  /*for debug logging only*/

    /* Copy client handle */
    sessionObject->sessionNode.clientHandle = *(GenericHandle*)session;

    trace_MIClient_SessionCreate(application, session, sessionObject);

    if (Session_RevertImpersonation(originalImpersonation) != MI_RESULT_OK)
    {
        TerminateProcess(GetCurrentProcess(), -1);
    }

    return returnCode;
}

_Success_(return == MI_RESULT_OK)
MI_Result Session_RegisterOperation(_Inout_ MI_Session *session, _Inout_ ChildListNode *operation)
{
    GenericHandle *genericHandle = (GenericHandle *)session;
    ThunkHandle *thunkHandle = NULL;
    MI_Result errorReturn = MI_RESULT_OK;

    ThunkHandle_FromGeneric(genericHandle, &thunkHandle);
    if (thunkHandle)
    {
        SessionObject *sessionObject = (SessionObject*) thunkHandle->u.object;
        errorReturn = ChildList_AddNode(&sessionObject->operationList, operation);
        ThunkHandle_Release(thunkHandle);
    }
    else
    {
        errorReturn = MI_RESULT_FAILED;
    }

    return errorReturn;
}

_Success_(return == MI_RESULT_OK)
MI_Result Session_UnregisterOperation(_Inout_ ThunkHandle *thunkHandle, _Inout_ ChildListNode *operation)
{
    SessionObject *sessionObject = (SessionObject*) thunkHandle->u.object;
    ChildList_RemoveNode(&sessionObject->operationList, operation);

    return MI_RESULT_OK;
}


/* Callback from protocol handler that Close has competed.  It is 
 * safe for us to finish closing things down now and then callback
 * to the client.
 */
void MI_CALL Session_CloseCallback(_In_ void *completionContext)
{
    ThunkHandle *thunkHandle = (ThunkHandle*) completionContext;
    SessionObject *sessionObject = (SessionObject*) thunkHandle->u.object;

    /* Final callback */
    if (sessionObject->sessionCloseCallback != NULL)
    {
        MI_CLIENT_IMPERSONATION_TOKEN currentImpersonationToken;
        MI_Result impersonationResult = Session_ImpersonateClientInternal(sessionObject, &currentImpersonationToken);

        if (impersonationResult == MI_RESULT_OK)
        {
            /* Client was async, so callback */
            sessionObject->sessionCloseCallback(sessionObject->sessionCloseCallbackContext);

            trace_MIClient_SessionCloseCompleted(sessionObject->clientSessionPtr, sessionObject);

            if (Session_RevertImpersonation(currentImpersonationToken) != MI_RESULT_OK)
            {
                TerminateProcess(GetCurrentProcess(), -1);
            }
        }
        /* Shutdown was holding open refcount until callback was called */
        ThunkHandle_Release(thunkHandle);
    }
    else
    {
        /* Client was synchronous, so signal waiting thread */
        sessionObject->sessionCloseCallbackCalled = 1;
        CondLock_Broadcast((ptrdiff_t)sessionObject);
    }
}

/* Shutdown of all child operations was successful so now
 * we need to call into the protocol handler to tell it 
 * to shutdown
 */
void Session_AllOperationsShutdown(void *context)
{
    MI_CLIENT_IMPERSONATION_TOKEN originalImpersonation = INVALID_HANDLE_VALUE;
    MI_Result miResult;
    ThunkHandle *sessionThunk = (ThunkHandle*) context;
    SessionObject *sessionObject = (SessionObject*) sessionThunk->u.object;
    ProtocolHandlerCacheItem *protocolHandlerItem = sessionObject->protocolHandlerItem;
    /* Call into protocol handler to initiate shutdown */
    ProtocolHandlerCache_IncrementApiCount(protocolHandlerItem);
    
    miResult = Session_ImpersonateClientInternal(sessionObject, &originalImpersonation);
    //If it is failed it is going to have to be best effort and hope it works!
    sessionObject->protocolHandlerSession.ft->Close(&sessionObject->protocolHandlerSession, sessionThunk, Session_CloseCallback);

    if ((miResult == MI_RESULT_OK) && (Session_RevertImpersonation(originalImpersonation) != MI_RESULT_OK))
    {
        TerminateProcess(GetCurrentProcess(), -1);
    }

    ProtocolHandlerCache_DecrementApiCount(protocolHandlerItem);

    /* Close is async so do nothing else after this */
}

/* Trigger cancellation of all operations */
void Session_CancelAllOperations(_Inout_ MI_Session *session)
{
    ThunkHandle *thunkHandle;
    SessionObject *sessionObject;

    ThunkHandle_FromGeneric((GenericHandle*)session, &thunkHandle);
    if (thunkHandle == NULL)
    {
        /* Failed means version was wrong or object was shutdown */
        return;
    }

    sessionObject = (SessionObject*) thunkHandle->u.object;

    {
        ChildListOutstandingHandles _smallBuffer[100];
        ChildListOutstandingHandles* outstandingOperations = _smallBuffer;
        ptrdiff_t outstandingOperationSize = sizeof(_smallBuffer)/sizeof(_smallBuffer[0]);
        ptrdiff_t outstandingOperationCount;

        int r = ChildList_Shutdown(&sessionObject->operationList);
        if (r)
        {
            r = ChildList_GetCurrentList(&sessionObject->operationList, outstandingOperations, outstandingOperationSize, &outstandingOperationCount);
            if (r == 0 && outstandingOperationCount > outstandingOperationSize)
            {
                outstandingOperations = (ChildListOutstandingHandles*) PAL_Malloc(outstandingOperationCount*sizeof(ChildListOutstandingHandles));
                if (outstandingOperations == NULL)
                {
                    //TSASSERT(0, L"ignored memory allocation on purpose", TLINE);
                    //Note that we cannot cancel the operations.  
                    //It is completely up to the client to close all operations in this case and it will cause it to not respond if they do not
                }
                else
                {
                    outstandingOperationSize = outstandingOperationCount;
                    r = ChildList_GetCurrentList(&sessionObject->operationList, outstandingOperations, outstandingOperationSize, &outstandingOperationCount);
                }
            }

            /* Cancel all child operations */
            if (r)
            {
    #ifdef _PREFAST_
    //famous last words, but I am pretty sure this code is not an overflow. outstandingOperationCount has how many items are in it and it will never be more than 
    //outstandingOperationSize if r is non-zero
     #pragma prefast(push)
     #pragma prefast(disable:26015) 
    #endif
                while (outstandingOperationCount)
                {
                    MI_Operation *operation = (MI_Operation*)&outstandingOperations[outstandingOperationCount-1].clientHandle;
            
                    /* Mode to next one as cancel may cause current operation to get deleted */
                    outstandingOperationCount--;

                    MI_Operation_Cancel(operation, MI_REASON_NONE);
                }
    #ifdef _PREFAST_
     #pragma prefast(pop)
    #endif
            }
            if (outstandingOperations != _smallBuffer)
            {
                PAL_Free(outstandingOperations);
            }
        }
    }
    ThunkHandle_Release(thunkHandle);
}

/* Client API MI_Session_Close method.
 */
_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL Session_Close(
    _In_     MI_Session *session,
    _In_opt_ void *completionContext,
    _In_opt_ void (MI_CALL *completionCallback)(_In_opt_ void *completionContext))
{
    GenericHandle *genericHandle = (GenericHandle *)session;
    ThunkHandle *thunkHandle = NULL;
    SessionObject *sessionObject = NULL;
    MI_CLIENT_IMPERSONATION_TOKEN originalImpersonation = INVALID_HANDLE_VALUE;

    trace_MISessionClose(__FUNCTION__, session, completionContext, (void*)completionCallback);

    /* invalid parameter check, already closed, or out of memory during creation */
    if ((session == NULL) || (genericHandle->thunkHandle == NULL))
    {
        if (completionCallback != NULL)
        {
            completionCallback(completionContext);
        }
        trace_MIInvalidSession(__FUNCTION__, session);
        return MI_RESULT_INVALID_PARAMETER;
    }

    ThunkHandle_FromGeneric(genericHandle, &thunkHandle);
    if (thunkHandle == NULL)
    {
        /* Failed means version was wrong or object was shutdown */
        trace_MISessionInvalidThunkHandle(__FUNCTION__, session);
        return MI_RESULT_INVALID_PARAMETER;
    }

    sessionObject = (SessionObject*) thunkHandle->u.object;

    {
        MI_Result securityResult = Session_AccessCheck(session, MI_T("close session"));
        if (securityResult != MI_RESULT_OK)
        {
            ThunkHandle_Release(thunkHandle);
            trace_MISession_AccessCheckFailed(__FUNCTION__, session);
            return securityResult;
        }
    }

    trace_MIClient_SessionClose(session, sessionObject);

    /* Mark handle for shutdown */
    if (ThunkHandle_Shutdown(thunkHandle, Session_Destructor))
    {
        MI_Result miResult =  Session_ImpersonateClientInternal(sessionObject, &originalImpersonation);
        if (miResult != MI_RESULT_OK)
        {
            ThunkHandle_Release(thunkHandle);
            return miResult;
        }

        /* remember callback details */
        if (completionCallback)
        {
            sessionObject->sessionCloseCallbackContext = completionContext;
            sessionObject->sessionCloseCallback = completionCallback;
        }

        /* Cancel all child operations */
        {
            ChildListOutstandingHandles _smallBuffer[100];
            ChildListOutstandingHandles* outstandingOperations = _smallBuffer;
            ptrdiff_t outstandingOperationSize = sizeof(_smallBuffer)/sizeof(_smallBuffer[0]);
            ptrdiff_t outstandingOperationCount;

            int r = ChildList_Shutdown(&sessionObject->operationList);
            if (r)
            {
                r = ChildList_GetCurrentList(&sessionObject->operationList, outstandingOperations, outstandingOperationSize, &outstandingOperationCount);
                if (r == 0 && outstandingOperationCount > outstandingOperationSize)
                {
                    outstandingOperations = (ChildListOutstandingHandles*) PAL_Malloc(outstandingOperationCount*sizeof(ChildListOutstandingHandles));
                    if (outstandingOperations == NULL)
                    {
                        //TSASSERT(0, L"ignored memory allocation on purpose", TLINE);
                        //Note that we cannot cancel the operations.  
                        //It is completely up to the client to close all operations in this case and it will cause it to not respond if they do not
                    }
                    else
                    {
                        outstandingOperationSize = outstandingOperationCount;
                        r = ChildList_GetCurrentList(&sessionObject->operationList, outstandingOperations, outstandingOperationSize, &outstandingOperationCount);
                    }
                }

                /* Cancel all child operations */
                if (r)
                {
    #ifdef _PREFAST_
    //famous last words, but I am pretty sure this code is not an overflow. outstandingOperationCount has how many items are in it and it will never be more than 
    //outstandingOperationSize if r is non-zero
     #pragma prefast(push)
     #pragma prefast(disable:26015) 
    #endif
                    while (outstandingOperationCount)
                    {
                        MI_Operation *operation = (MI_Operation*)&outstandingOperations[outstandingOperationCount-1].clientHandle;
            
                        /* Mode to next one as cancel may cause current operation to get deleted */
                        outstandingOperationCount--;

                        MI_Operation_Cancel(operation, MI_REASON_NONE);
                    }
    #ifdef _PREFAST_
     #pragma prefast(pop)
    #endif
                }
                if (outstandingOperations != _smallBuffer)
                {
                    PAL_Free(outstandingOperations);
                }
            }
            ChildList_RegisterShutdownCallback(&sessionObject->operationList, Session_AllOperationsShutdown, thunkHandle);
        }
        
        /* Callback into the protocol handler happens asynchronously once all child operations are shutdown */

        /* CALL IS ASYNC. NO MORE CODE HERE except for code to make close synchronous.  Anything else that is needed goes here: Session_CloseCallback */

        if (completionCallback == NULL)
        {
            ptrdiff_t curSessionCloseCallbackCalled = sessionObject->sessionCloseCallbackCalled;
            /* block until protocol handler calls back */
            while (!curSessionCloseCallbackCalled)
            {
                trace_MIClient_SessionClose_WaitingOnOperations(session, sessionObject, sessionObject->operationList.childCount);
                /* 0 is the current value of state, the value we don't want to see. */
                CondLock_Wait((ptrdiff_t) sessionObject, &sessionObject->sessionCloseCallbackCalled, curSessionCloseCallbackCalled, CONDLOCK_DEFAULT_SPINCOUNT);
                curSessionCloseCallbackCalled = sessionObject->sessionCloseCallbackCalled;
            }
            trace_MIClient_SessionCloseCompleted(session, sessionObject);
            ThunkHandle_Release(thunkHandle);
        }
        else
        {
            /* ThunkHandle_Release(thunkHandle) happens in callback code */
        }

        if (Session_RevertImpersonation(originalImpersonation) != MI_RESULT_OK)
        {
            TerminateProcess(GetCurrentProcess(), -1);
        }
    }
    else
    {
        /* Not the first call to Close so ignore this.  It is unlikely this will happen
         * as the ThunkHandle_FromGeneric would generally fail but there is a small 
         * race condition that could cause this to happen
         */
        ThunkHandle_Release(thunkHandle);
    }

    return MI_RESULT_OK;
}

_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL Session_GetApplication(
    _In_     MI_Session *session,
    _Out_    MI_Application *application)
{
    GenericHandle *genericHandle = (GenericHandle*) session;
    ThunkHandle * thunkHandle = NULL;
    SessionObject *sessionObject;

    if (application)
    {
        memset(application, 0, sizeof(MI_Application));
    }
    if ((session == NULL) || (application == NULL))
    {
        return MI_RESULT_INVALID_PARAMETER;
    }


    ThunkHandle_FromGeneric(genericHandle, &thunkHandle);
    if (thunkHandle == NULL)
    {
        /* Failed means version was wrong or object was shutdown */
        return MI_RESULT_INVALID_PARAMETER;
    }

    sessionObject = (SessionObject *) thunkHandle->u.object;
    *application = sessionObject->clientApplication;

    /* finished with object for now... */
    ThunkHandle_Release(thunkHandle);
    return MI_RESULT_OK;
}

/* Get a copy of the session destination options */
void Session_GetDestinationOptions(_Inout_ MI_Session *session, _Out_ MI_DestinationOptions *destOptions)
{
    GenericHandle *genericHandle = (GenericHandle*) session;
    ThunkHandle * thunkHandle = NULL;
    SessionObject *sessionObject;

    memset(destOptions, 0, sizeof(MI_DestinationOptions));

    ThunkHandle_FromGeneric(genericHandle, &thunkHandle);
    if (thunkHandle == NULL)
    {
        /* Failed means version was wrong or object was shutdown */
        return;
    }

    sessionObject = (SessionObject *) thunkHandle->u.object;
    DestinationOptions_Duplicate(&sessionObject->clientDestinationOptions, destOptions);
    /* finished with object for now... */
    ThunkHandle_Release(thunkHandle);
}

/* From a client session get the transport session */
_Success_(return==MI_RESULT_OK)
MI_Result Session_GetProtocolHandlerSession(
    _In_ MI_Session *clientSession, 
    _Out_ MI_Session *protocolHandlerSession,
    _Out_ ProtocolHandlerCacheItem **protocolHandlerItem)
{
    ThunkHandle *sessionThunk = NULL;
    SessionObject *sessionObject = NULL;

    ThunkHandle_FromGeneric((GenericHandle*)clientSession, &sessionThunk);
    if (sessionThunk == NULL)
    {
        return MI_RESULT_FAILED;
    }

    sessionObject = (SessionObject *) sessionThunk->u.object;
    *protocolHandlerSession = sessionObject->protocolHandlerSession;
    *protocolHandlerItem = sessionObject->protocolHandlerItem;
    /* release up sessionThunk */
    ThunkHandle_Release(sessionThunk);

    return MI_RESULT_OK;
}

_Success_(return==MI_RESULT_OK)
MI_Result Session_GetProtocolHandlerApplication(
    _In_ MI_Session *clientSession, 
    _Out_ MI_Application *protocolHandlerApplication)
{
    ThunkHandle *sessionThunk = NULL;
    SessionObject *sessionObject = NULL;

    ThunkHandle_FromGeneric((GenericHandle*)clientSession, &sessionThunk);
    if (sessionThunk == NULL)
    {
        return MI_RESULT_FAILED;
    }

    sessionObject = (SessionObject *) sessionThunk->u.object;
    *protocolHandlerApplication = sessionObject->protocolHandlerItem->application;

    /* release up sessionThunk */
    ThunkHandle_Release(sessionThunk);

    return MI_RESULT_OK;
}

_Success_(return == MI_RESULT_OK)
MI_Result Session_AccessCheck(_In_ MI_Session *session, _In_opt_z_ const MI_Char *operationName)
{
    ThunkHandle *sessionThunk = NULL;
    SessionObject *sessionObject = NULL;
    MI_Result r;

    trace_MIEnter(__FUNCTION__, session);

    /* NOTE: Access check may be called from Operat_Cancel or Operation_Close after the
     * session has been closed.  Therefore do thunk and ignore Active bit on handle.
     */
    ThunkHandle_FromGeneric_ForCompletionCallback((GenericHandle*)session, &sessionThunk);
    if (sessionThunk == NULL)
    {
        trace_MISession_InvalidSessionThunk(__FUNCTION__, session);
        return MI_RESULT_INVALID_PARAMETER;
    }

    sessionObject = (SessionObject *) sessionThunk->u.object;

    if ((getuid() == sessionObject->uid) && (getgid() == sessionObject->gid))
    {
        r = MI_RESULT_OK;
    }
    else
    {
        r = MI_RESULT_ACCESS_DENIED;
    }

    /* release up sessionThunk */
    ThunkHandle_Release(sessionThunk);

    trace_MILeavingSessionWithOperation(__FUNCTION__, session, operationName);
    return r;
}

/*Impersonates based on who created the session, returning original thread token to call Session_RevertImpersonation with*/
_Success_(return == MI_RESULT_OK)
MI_Result Session_ImpersonateClient(_In_ MI_Session *session, _Out_ MI_CLIENT_IMPERSONATION_TOKEN *originalImpersonation)
{
    return MI_RESULT_OK;
}

/*Impersonates based on who created the session, returning original thread token to call Session_RevertImpersonation with*/
MI_Result Session_ImpersonateClientInternal(_In_ SessionObject *sessionObject, _Out_ MI_CLIENT_IMPERSONATION_TOKEN *originalImpersonation)
{
    *originalImpersonation = INVALID_HANDLE_VALUE;
    return MI_RESULT_OK;
}

//Reverts the impersonation token back to what it was before Session_ImpersonateClient was called
_Success_(return == MI_RESULT_OK)
MI_Result Session_RevertImpersonation(MI_CLIENT_IMPERSONATION_TOKEN originalImpersonation)
{
    return MI_RESULT_OK;
}

const MI_SessionFT g_sessionFT_OOM = {
    Session_Close,
    NULL
};

const MI_SessionFT g_sessionFT = {
    Session_Close,
    Session_GetApplication,
    Operation_Execute_GetInstance,
    Operation_Execute_ModifyInstance,
    Operation_Execute_CreateInstance,
    Operation_Execute_DeleteInstance,
    Operation_Execute_Invoke,
    Operation_Execute_EnumerateInstances,
    Operation_Execute_QueryInstances,
    Operation_Execute_AssociatorInstances,
    Operation_Execute_ReferenceInstances,
    Operation_Execute_Subscribe,
    Operation_Execute_GetClass,
    Operation_Execute_EnumerateClasses,
    Operation_Execute_TestConnection
};
