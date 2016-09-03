/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <MI.h>
#include "InteractionProtocolHandler.h"
#include "Options.h"
#include <pal/atomic.h>
#include <pal/intsafe.h>
#include <pal/thread.h>
#include <pal/format.h>
#include <pal/strings.h>
#include <pal/lock.h>
#include <pal/sleep.h>
#include <base/Strand.h>
#include <base/messages.h>
#include <base/packing.h>
#include <base/paths.h>
#include <base/result.h>
#include <base/log.h>
#include <protocol/protocol.h>
#include <wsman/wsbuf.h>
#include <wsman/wsmanclient.h>
#include <stdlib.h>

//#define LOGD(a) {Tprintf a;Tprintf(MI_T("\n"));}
//#define LOGD(...)

extern const MI_ApplicationFT g_interactionProtocolHandler_ApplicationFT;
extern const MI_SessionFT g_interactionProtocolHandler_SessionFT;
extern const MI_OperationFT g_interactionProtocolHandler_OperationFT;
extern const MI_SessionFT g_interactionProtocolHandler_SessionFT_Dummy;

typedef enum
{
    PROTOCOL_SOCKET,
    PROTOCOL_WSMAN
} InteractionProtocolHandler_ProtocolType;

typedef struct _ApplicationThread
{
    struct _ApplicationThread *next;
    Thread thread;
} ApplicationThread;

typedef struct _InteractionProtocolHandler_Application
{
    MI_Char *applicationID;
    MI_Application myMiApplication;
    ptrdiff_t threadCount;
    Lock listOfThreadsLock;
    ApplicationThread *listOfThreads;
    Thread safeShutdownThread;
} InteractionProtocolHandler_Application;

typedef void *  SessionCloseCompletionContext;
typedef void (MI_CALL * SessionCloseCompletionCallback)(_In_opt_ SessionCloseCompletionContext);

typedef struct _SessionCloseCompletion
{
    // count indicating who many protocool run thread are running
    // so who ever finish last session close or the last protocol run thread
    // will take care of releasing this completion and calling the callback (if necessary)
    volatile ptrdiff_t                          count;
    SessionCloseCompletionCallback              completionCallback;
    SessionCloseCompletionContext               completionContext;
} SessionCloseCompletion;

typedef struct _InteractionProtocolHandler_Session
{
    InteractionProtocolHandler_Application *    parentApplication;
    MI_DestinationOptions                       destinationOptions;
    MI_Session                                  myMiSession;
    // released by either session close or the protocol run thread, whoever finishes last
    SessionCloseCompletion *                    sessionCloseCompletion;

    InteractionProtocolHandler_ProtocolType protocolType;
    MI_Char *hostname;
} InteractionProtocolHandler_Session;

typedef enum _InteractionProtocolHandler_Operation_CurrentState
{
    InteractionProtocolHandler_Operation_CurrentState_NotConnected = 0,
    InteractionProtocolHandler_Operation_CurrentState_WaitingForConnect,
    InteractionProtocolHandler_Operation_CurrentState_WaitingForClientResultAck,
    InteractionProtocolHandler_Operation_CurrentState_WaitingForResult,
    InteractionProtocolHandler_Operation_CurrentState_ConnectionFailed,
    InteractionProtocolHandler_Operation_CurrentState_Disconnected,
    InteractionProtocolHandler_Operation_CurrentState_Closed

} InteractionProtocolHandler_Operation_CurrentState;

typedef enum _InteractionProtocolHandler_Operation_OperationType
{
    InteractionProtocolHandler_Operation_OperationType_Instance,
    InteractionProtocolHandler_Operation_OperationType_Indication,
    InteractionProtocolHandler_Operation_OperationType_Class
} InteractionProtocolHandler_Operation_OperationType;

typedef struct _InteractionProtocolHandler_Protocols
{
    InteractionProtocolHandler_ProtocolType type;

    union
    {
        ProtocolSocketAndBase* socket;
        WsmanClient* wsman;
    } protocol;

 } InteractionProtocolHandler_Protocols;

typedef struct _InteractionProtocolHandler_Operation
{
    InteractionProtocolHandler_Session *parentSession;
    MI_Operation myMiOperation;
    MI_OperationCallbacks asyncOperationCallbacks;
    Strand strand;  /* To manage interaction with ProtocolSocket */
    RequestMsg* req;   /* Base pointer of full operation request message */
    InteractionProtocolHandler_Protocols protocols;
    ApplicationThread *protocolRunThread;
    volatile ptrdiff_t currentState; /* InteractionProtocolHandler_Operation_CurrentState */
    MI_Boolean deliveredFinalResult;
    InteractionProtocolHandler_Operation_OperationType operationType;
    Message* cachedResultRequest;
    MI_Boolean callingFinalResult;
    Message* currentObjectMessage;
    Message* currentResultMessage;
    MI_Class currentClassResult;

} InteractionProtocolHandler_Operation;

STRAND_DEBUGNAME(ProtocolHandler);

MI_Result InteractionProtocolHandler_Application_IncrementThreadCount(
    _In_     InteractionProtocolHandler_Application *application);
MI_Result InteractionProtocolHandler_Application_DecrementThreadCount(
    _In_     InteractionProtocolHandler_Application *application);
MI_Result InteractionProtocolHandler_Application_SafeCloseThread(
    _In_ InteractionProtocolHandler_Application *application,
    _In_ ApplicationThread *operationThread);


MI_Result MI_CALL InteractionProtocolHandler_Session_New(
        _In_     MI_Application *miApplication,
        _In_opt_z_ const MI_Char *protocol,
        _In_opt_z_ const MI_Char *destination,
        _In_opt_ MI_DestinationOptions *options,
        _In_opt_ MI_SessionCallbacks *callbacks,
        _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
        _Out_    MI_Session *session);

MI_Result MI_CALL InteractionProtocolHandler_Client_Ack_PostToInteraction(_In_ MI_Operation *_operation)
{
    InteractionProtocolHandler_Operation* operation = (InteractionProtocolHandler_Operation *)_operation->reserved2;

    trace_InteractionProtocolHandler_Client_Ack_Post(operation);

    /* Clean up all the result data for this iteration of results */
    if (operation->currentObjectMessage)
    {
        Message_Release(operation->currentObjectMessage);
        operation->currentObjectMessage = NULL;
    }
    if (operation->currentResultMessage)
    {
        Message_Release(operation->currentResultMessage);
        operation->currentResultMessage = NULL;
    }
    if (operation->currentClassResult.ft)
    {
        MI_Class_Delete(&operation->currentClassResult);
        memset(&operation->currentClassResult, 0, sizeof(operation->currentClassResult));
    }

    Strand_ScheduleAck(&operation->strand);

    return MI_RESULT_OK;
}
MI_Result MI_CALL InteractionProtocolHandler_Client_Ack_NoPostToInteraction(_In_ MI_Operation *_operation)
{
    InteractionProtocolHandler_Operation* operation = (InteractionProtocolHandler_Operation *)_operation->reserved2;

    /* Processing an ack that requires no ack to the interaction interface */
    trace_InteractionProtocolHandler_Client_Ack_NoPost(operation);
    return MI_RESULT_OK;
}

static MI_Uint64 _NextOperationId()
{
    static ptrdiff_t _operationId = 10000;
    return (MI_Uint64) Atomic_Inc(&_operationId);
}

static char* _StringToStr(const MI_Char* str)
{
    MI_Uint32 n = Tcslen(str);
    MI_Uint32 i;
    char* r = PAL_Malloc(sizeof(char)* (n + 1));

    if (!r)
        return NULL;

    for (i = 0; i < n; i++)
    {
        r[i] = (char)str[i];
    }

    r[n] = '\0';

    return r;
}


/* ===================================================================================
 * ===================================================================================
 * ===================================================================================
 * ===================================================================================
 * ===================================================================================
 * ===================================================================================
 */

static void InteractionProtocolHandler_Operation_Strand_Post( _In_ Strand* self_, _In_ Message* msg)
{
    InteractionProtocolHandler_Operation *operation = FromOffset(InteractionProtocolHandler_Operation, strand, self_);
    trace_InteractionProtocolHandler_Operation_StrandPost(
        operation,
        msg,
        msg->tag,
        MessageName(msg->tag),
        msg->operationId );

    switch(msg->tag)
    {
    case PostInstanceMsgTag:
    {
        MI_Boolean needToAck = MI_FALSE;

        //If we have a previous item we need to send it
        if (operation->cachedResultRequest)
        {
            PostInstanceMsg* rsp = (PostInstanceMsg*)operation->cachedResultRequest;

            operation->currentObjectMessage = operation->cachedResultRequest; /* Needs releasing in Ack */
            operation->cachedResultRequest = NULL;

#ifdef _PREFAST_
    #pragma prefast(push)
    #pragma prefast(disable:26001)
#endif

            operation->asyncOperationCallbacks.instanceResult(&operation->myMiOperation, operation->asyncOperationCallbacks.callbackContext, rsp->instance, MI_TRUE, MI_RESULT_OK, NULL, NULL, InteractionProtocolHandler_Client_Ack_PostToInteraction);

#ifdef _PREFAST_
    #pragma prefast(pop)
#endif
        }
        else
            needToAck = MI_TRUE;

        {
            PostInstanceMsg* rsp = (PostInstanceMsg*)msg;
            if (rsp->instance)
            {
                /* if we have an instance we need to cache it */
                Message_AddRef(msg);
                operation->cachedResultRequest = msg; /* This will be used next time around or when we deliver final result */
            }
        }

        if (needToAck)
        {
            Strand_ScheduleAck(&operation->strand);
            return;
        }

        break;
    }
    case PostIndicationMsgTag:
    {
        PostIndicationMsg* indication = (PostIndicationMsg*)msg;
        trace_InteractionProtocolHandler_Operation_Strand_Post(
            operation,
            indication->base.instance);
        Message_AddRef(msg);
        operation->currentObjectMessage = msg; /* Needs releasing in Ack */
        operation->asyncOperationCallbacks.indicationResult(&operation->myMiOperation, operation->asyncOperationCallbacks.callbackContext, indication->base.instance, indication->bookmark, indication->machineID, MI_TRUE, MI_RESULT_OK, NULL, NULL, InteractionProtocolHandler_Client_Ack_PostToInteraction);

        break;
    }
    case PostResultMsgTag:
    {
        PostResultMsg* resp = (PostResultMsg*)msg;

        trace_MIResult( Result_ToString(resp->result) );

        operation->callingFinalResult = 1;

        Message_AddRef(msg);
        operation->currentResultMessage = msg; /* Released in Ack() */

        if (operation->req->base.tag == SubscribeReqTag)
        {
            PostInstanceMsg* previousResp = (PostInstanceMsg*)operation->cachedResultRequest;
            MI_Instance *previousInstance = NULL;

            if (previousResp)
                previousInstance = previousResp->instance;

            /* Need to get bookmark from message that doesn't yet exist */
            operation->asyncOperationCallbacks.indicationResult(&operation->myMiOperation, operation->asyncOperationCallbacks.callbackContext, previousInstance, NULL, NULL, MI_FALSE, resp->result, resp->errorMessage, resp->cimError, InteractionProtocolHandler_Client_Ack_PostToInteraction);
            operation->deliveredFinalResult = MI_TRUE;
        }
        else if (operation->req->base.tag == GetClassReqTag)
        {
            PostSchemaMsg* previousResp = (PostSchemaMsg*)operation->cachedResultRequest;
            MI_Class *classItem = NULL;

            if (previousResp)
            {
                MI_Instance_GetClassExt(previousResp->schemaInstance, &operation->currentClassResult);/* Needs deleting in Ack() */
                classItem = &operation->currentClassResult;
            }

            operation->currentObjectMessage = operation->cachedResultRequest; /* Needs releasing in Ack() */

            operation->asyncOperationCallbacks.classResult(&operation->myMiOperation, operation->asyncOperationCallbacks.callbackContext, classItem, MI_FALSE, resp->result, resp->errorMessage, resp->cimError, InteractionProtocolHandler_Client_Ack_PostToInteraction);
        }
        else
        {
            PostInstanceMsg* previousResp = (PostInstanceMsg*)operation->cachedResultRequest;
            MI_Instance *previousInstance = NULL;

            if (previousResp)
                previousInstance = previousResp->instance;

            operation->currentObjectMessage = operation->cachedResultRequest; /* Needs releasing in Ack() */

            operation->asyncOperationCallbacks.instanceResult(&operation->myMiOperation, operation->asyncOperationCallbacks.callbackContext, previousInstance, MI_FALSE, resp->result, resp->errorMessage, resp->cimError, InteractionProtocolHandler_Client_Ack_PostToInteraction);
        }


        break;
    }
    case NoOpRspTag:
    {
        //NoOpRsp* resp = (NoOpRsp*)msg;
        /* If we have an existing result then we need to send that along with the result.
         * Note that the Strand_Ack will be done in the Ack we get back from the client.
         */
        trace_InteractionProtocolHandler_NoopRspTag();
        operation->callingFinalResult = 1;
        operation->asyncOperationCallbacks.instanceResult(&operation->myMiOperation, operation->asyncOperationCallbacks.callbackContext, NULL, MI_FALSE, MI_RESULT_OK, NULL, NULL, InteractionProtocolHandler_Client_Ack_PostToInteraction);
        operation->deliveredFinalResult = MI_TRUE;
        break;
    }
    case PostSchemaMsgTag:
    {
         MI_Boolean needToAck = MI_FALSE;

        //If we have a previous item we need to send it
        if (operation->cachedResultRequest)
        {
            PostSchemaMsg* rsp = (PostSchemaMsg*)operation->cachedResultRequest;

            operation->currentObjectMessage = operation->cachedResultRequest; /* Needs releasing in Ack */
            operation->cachedResultRequest = NULL;

            MI_Instance_GetClassExt(rsp->schemaInstance, &operation->currentClassResult);/* Needs deleting in Ack() */

#ifdef _PREFAST_
    #pragma prefast(push)
    #pragma prefast(disable:26001)
#endif
            operation->asyncOperationCallbacks.classResult(&operation->myMiOperation, operation->asyncOperationCallbacks.callbackContext, &operation->currentClassResult, MI_TRUE, MI_RESULT_OK, NULL, NULL, InteractionProtocolHandler_Client_Ack_PostToInteraction);

#ifdef _PREFAST_
    #pragma prefast(pop)
#endif
        }
        else
            needToAck = MI_TRUE;

        {
            PostSchemaMsg* rsp = (PostSchemaMsg*)msg;
            if (rsp->schemaInstance)
            {
                /* if we have an instance we need to cache it */
                Message_AddRef(msg);
                operation->cachedResultRequest = msg; /* This will be used next time around or when we deliver final result */
            }
        }

        if (needToAck)
        {
            Strand_ScheduleAck(&operation->strand);
            return;
        }

        break;
    }
    case BinProtocolNotificationTag:
    {
        /* Don't support these responses yet so just Ack them */
        Strand_Ack(self_);
        return;
    }
    case SubscribeResTag:
    {
        /* Subscribe succeeded */
        Strand_Ack(self_);
        return;
    }
    case GetInstanceReqTag:
    case EnumerateInstancesReqTag:
    case NoOpReqTag:
    case InvokeReqTag:
    case AssociatorsOfReqTag:
    case ReferencesOfReqTag:
    case SubscribeReqTag:
    case DeleteInstanceReqTag:
    case CreateInstanceReqTag:
    case ModifyInstanceReqTag:
    case GetClassReqTag:
    case UnsubscribeReqTag:
    default:
    {
        /* We should not get any of these messages as they are the requests. We should only get the responses. Ack anyway for now. */
        DEBUG_ASSERT( MI_FALSE );
        Strand_Ack(self_);
        return;
    }
    }

}

#ifdef _PREFAST_
#pragma prefast (push)
#pragma prefast (disable: 26001) // bogus "we know the strand points to the middle of the InteractionProtocolHandler_Operation struct" and Linux sal parser doesnt recognize something like _Readable_elements_(_Inexpressible_(InteractionProtocolHandler_Operation))
#endif /* _PREFAST_ */

static void InteractionProtocolHandler_Operation_Strand_PostControl( _In_ Strand* self_, _In_ Message* msg)
{
    InteractionProtocolHandler_Operation *operation = FromOffset(InteractionProtocolHandler_Operation, strand, self_);
    ProtocolEventConnect* eventMsg = (ProtocolEventConnect*)msg;

    trace_InteractionProtocolHandler_Operation_Strand_PostControl( operation );
    DEBUG_ASSERT( ProtocolEventConnectTag == msg->tag );

    if( eventMsg->success )
    {
        trace_InteractionProtocolHandler_Session_ProtocolConnecting();

        /* Posting the operation message so set the state to waiting for a result message */
        operation->currentState = InteractionProtocolHandler_Operation_CurrentState_WaitingForResult;
        Strand_Post(&operation->strand, &operation->req->base);
    }
    else
    {
        trace_InteractionProtocolHandler_Session_ConnectFailed();

    }
}

static void InteractionProtocolHandler_Operation_Strand_Ack( _In_ Strand* self_ )
{
    InteractionProtocolHandler_Operation *operation = FromOffset(InteractionProtocolHandler_Operation, strand, self_);
    trace_InteractionProtocolHandler_Operation_Strand_Ack(operation);
    // We are not streaming any results, so no need to manage flow control on Ack
}

static void InteractionProtocolHandler_Operation_Strand_Cancel( _In_ Strand* self_ )
{
    InteractionProtocolHandler_Operation *operation = FromOffset(InteractionProtocolHandler_Operation, strand, self_);
    trace_InteractionProtocolHandler_Operation_Strand_Cancel(operation);
    // DEBUG_ASSERT( MI_FALSE );  // not used in this direction
}

static void _Operation_SendFinalResult_Internal(InteractionProtocolHandler_Operation *operation)
{
    operation->currentState = InteractionProtocolHandler_Operation_CurrentState_NotConnected;
    operation->callingFinalResult = MI_TRUE;
    if (operation->operationType == InteractionProtocolHandler_Operation_OperationType_Class)
    {
        operation->asyncOperationCallbacks.classResult(&operation->myMiOperation, operation->asyncOperationCallbacks.callbackContext, NULL, MI_FALSE, MI_RESULT_FAILED, NULL, NULL, InteractionProtocolHandler_Client_Ack_NoPostToInteraction);
    }
    else if (operation->operationType == InteractionProtocolHandler_Operation_OperationType_Indication)
    {
        operation->asyncOperationCallbacks.indicationResult(&operation->myMiOperation, operation->asyncOperationCallbacks.callbackContext, NULL, NULL, NULL, MI_FALSE, MI_RESULT_FAILED, NULL, NULL, InteractionProtocolHandler_Client_Ack_NoPostToInteraction);
    }
    else
    {
        operation->asyncOperationCallbacks.instanceResult(&operation->myMiOperation, operation->asyncOperationCallbacks.callbackContext, NULL, MI_FALSE, MI_RESULT_FAILED, NULL, NULL, InteractionProtocolHandler_Client_Ack_NoPostToInteraction);
    }
    operation->deliveredFinalResult = MI_TRUE;
}

static void InteractionProtocolHandler_Operation_Strand_Close( _In_ Strand* self_ )
{
    InteractionProtocolHandler_Operation *operation = FromOffset(InteractionProtocolHandler_Operation, strand, self_);

    trace_InteractionProtocolHandler_Operation_Strand_Close(operation);

    if (!operation->callingFinalResult)
    {
        _Operation_SendFinalResult_Internal(operation);
    }
}

static void InteractionProtocolHandler_Operation_Strand_Finish( _In_ Strand* self_ )
{
    InteractionProtocolHandler_Operation *operation = FromOffset(InteractionProtocolHandler_Operation, strand, self_);
//    MI_Uint32 returnCode;

    trace_InteractionProtocolHandler_Operation_Strand_Finish(operation);

//TODO: At some point we need to make sure the thread is shutdown properly without causing deadlocks
//    Thread_Join(&operation->protocolRunThread, &returnCode);

    Message_Release(&operation->req->base);
    PAL_Free(operation);
}

#ifdef _PREFAST_
#pragma prefast (pop)
#endif /* _PREFAST_ */

/*
    Object that implements the MI Protocol Handler as an Interaction Interface
    over the binary protocol.

    Behavior:
    - Post implementes different behaviour depending on the type of message
       being posted
       * For PostInstanceMsg stores the instance in a cache var, and if there is
          previous cached instance not yet delivered will deliver that one first
          (waiting if necessary).
       * For PostIndicationMsg always delivers it to the client asynchronously.
       * For PostResultMsg it will delivered it thru the proper callback and
          set callingFinalResult to 1 to indicate final result already sent.
          Also note that NoOpRsp is another case of inal result.
       * PostSchemaMsg is treated the same as PostInstanceMsg with the same
          cached var mechanism.
       * SubscribeRes is just acked immediately as nothing is needed there
       * All other message types are not expected
       just passed the operation to tries to ClientRep::MessageCallback
       if that fails it sends the Ack immediately
    - Ack does nothing as there are no secondary messages to be sent to the
       protocol
    - Post control notified when the connect has succeeded (or failed). If succeeded
       the request corresponding to the operartion is send there.
    - Cancel does nothing at this point.
    - Close sends the final result if not being sent already
       (as indicated by callingFinalResult set on Post)
       if not it triggers a timeout that will close it
    - Shutdown:
       The InteractionProtocolHandler objects are shutdown/deleted thru the normal
       Strand logic (once the interaction is closed both ways).
*/
StrandFT InteractionProtocolHandler_Operation_Strand_FT =
{
    InteractionProtocolHandler_Operation_Strand_Post,
    InteractionProtocolHandler_Operation_Strand_PostControl,
    InteractionProtocolHandler_Operation_Strand_Ack,
    InteractionProtocolHandler_Operation_Strand_Cancel,
    InteractionProtocolHandler_Operation_Strand_Close,
    InteractionProtocolHandler_Operation_Strand_Finish,
    NULL,
    NULL,
    NULL,
    NULL
};


/* ===================================================================================
 * ===================================================================================
 * ===================================================================================
 * ===================================================================================
 * ===================================================================================
 * ===================================================================================
 */

MI_Result MI_CALL InteractionProtocolHandler_Operation_Close(
        _Inout_      MI_Operation *_operation)
{
    InteractionProtocolHandler_Operation* operation = (InteractionProtocolHandler_Operation *)_operation->reserved2;
    trace_InteractionProtocolHandler_Operation_Close(operation);

    Strand_ScheduleClose(&operation->strand);

    return MI_RESULT_OK;
}

MI_Result MI_CALL InteractionProtocolHandler_Operation_Cancel(
        _Inout_      MI_Operation *_operation,
                  MI_CancellationReason reason)
{
    InteractionProtocolHandler_Operation* operation = (InteractionProtocolHandler_Operation *)_operation->reserved2;

    if (!operation->callingFinalResult)
    {
        /*
         * Send unsubscribe if and only if not received FinalResult;
         * Cancellation is not implemented yet in protocol layer
         * For subscribe operation, sending UnsubscribeReq to server,
         * which will cleanup the subscribe operation;
         * TODO Upon end to end cancellation implemented, following 'if'
         * clause should be removed;
         */
        if (operation->req->base.tag == SubscribeReqTag)
        {
            UnsubscribeReq *req = UnsubscribeReq_New(operation->req->base.operationId, BinaryProtocolFlag);
            if (req)
            {
                trace_InteractionProtocolHandler_Operation_Cancel_PostUnsubscribeReq(operation);
                Strand_SchedulePost(&operation->strand, &req->base.base);
            }
            else
            {
                trace_InteractionProtocolHandler_Operation_Cancel_OutOfMemory(operation);
            }
        }

        trace_InteractionProtocolHandler_Operation_Cancel(operation);
        Strand_ScheduleCancel(&operation->strand);
    }
    else
    {
        trace_InteractionProtocolHandler_Operation_CancelAfterFinal(operation);
    }
    return MI_RESULT_OK;
}

MI_Result MI_CALL InteractionProtocolHandler_Operation_GetSession(
        _In_      MI_Operation *_operation,
        _Out_     MI_Session *session)
{
    InteractionProtocolHandler_Operation *operation;
    if (_operation)
    {
        operation = (InteractionProtocolHandler_Operation *)_operation->reserved2;
        if (operation->parentSession)
        {
            memcpy(session, &operation->parentSession->myMiSession, sizeof(*session));
            return MI_RESULT_OK;
        }
        else
            return MI_RESULT_INVALID_PARAMETER;
    }
    else
        return MI_RESULT_INVALID_PARAMETER;
}

const MI_OperationFT g_interactionProtocolHandler_OperationFT =
{
    InteractionProtocolHandler_Operation_Close,
    InteractionProtocolHandler_Operation_Cancel,
    InteractionProtocolHandler_Operation_GetSession,
    NULL, /* GetInstance, only async supported in protocol handlers */
    NULL, /* GetIndication, only async supported in protocol handlers */
    NULL /* GetClass, only async supported in protocol handlers */
};

MI_Result MI_CALL InteractionProtocolHandler_Operation_Close_Error(
    _Inout_      MI_Operation *operation)
{
    return MI_RESULT_OK;
}

MI_Result MI_CALL InteractionProtocolHandler_Operation_Cancel_Error(
    _Inout_      MI_Operation *operation,
                MI_CancellationReason reason)
{
    return MI_RESULT_OK;
}

MI_Result MI_CALL InteractionProtocolHandler_Operation_GetSession_Error(
    _In_      MI_Operation *operation,
    _Out_     MI_Session *session)
{
    if (session)
        memset(session, 0, sizeof(*session));
    return MI_RESULT_FAILED;
}


MI_Result MI_CALL InteractionProtocolHandler_Operation_GetInstance_Error(
    _In_      MI_Operation *operation,
    _Outptr_result_maybenull_     const MI_Instance **instance,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Outptr_opt_result_maybenull_z_ const MI_Char **errorMessage,
    _Outptr_opt_result_maybenull_ const MI_Instance **completionDetails)
{
    if (instance)
        *instance = NULL;
    if (moreResults)
        *moreResults = MI_FALSE;
    if (result)
        *result = MI_RESULT_FAILED;
    if (errorMessage)
        *errorMessage = NULL;
    if (completionDetails)
        *completionDetails = NULL;
    return MI_RESULT_FAILED;
}
MI_Result MI_CALL InteractionProtocolHandler_Operation_GetIndication_Error(
    _In_      MI_Operation *operation,
    _Outptr_result_maybenull_       const MI_Instance **instance,
    _Outptr_opt_result_maybenull_z_ const MI_Char **bookmark,
    _Outptr_opt_result_maybenull_z_ const MI_Char **machineID,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Outptr_opt_result_maybenull_z_ const MI_Char **errorMessage,
    _Outptr_opt_result_maybenull_   const MI_Instance **completionDetails)
{
    if (instance)
        *instance = NULL;
    if (bookmark)
        *bookmark = NULL;
    if (machineID)
        *machineID = NULL;
    if (moreResults)
        *moreResults = MI_FALSE;
    if (result)
        *result = MI_RESULT_FAILED;
    if (errorMessage)
        *errorMessage = NULL;
    if (completionDetails)
        *completionDetails = NULL;
    return MI_RESULT_FAILED;
}

MI_Result MI_CALL InteractionProtocolHandler_Operation_GetClass_Error(
    _In_      MI_Operation *operation,
    _Outptr_result_maybenull_     const MI_Class **classResult,
    _Out_opt_ MI_Boolean *moreResults,
    _Out_opt_ MI_Result *result,
    _Outptr_opt_result_maybenull_z_ const MI_Char **errorMessage,
    _Outptr_opt_result_maybenull_ const MI_Instance **completionDetails)
{
    if (classResult)
        *classResult = NULL;
    if (moreResults)
        *moreResults = MI_FALSE;
    if (result)
        *result = MI_RESULT_FAILED;
    if (errorMessage)
        *errorMessage = NULL;
    if (completionDetails)
        *completionDetails = NULL;
    return MI_RESULT_FAILED;
}


const MI_OperationFT g_interactionProtocolHandler_OperationFT_Dummy =
{
    InteractionProtocolHandler_Operation_Close_Error,
    InteractionProtocolHandler_Operation_Cancel_Error,
    InteractionProtocolHandler_Operation_GetSession_Error,
    InteractionProtocolHandler_Operation_GetInstance_Error,
    InteractionProtocolHandler_Operation_GetIndication_Error,
    InteractionProtocolHandler_Operation_GetClass_Error
};



/* ===================================================================================
 * ===================================================================================
 * ===================================================================================
 * ===================================================================================
 * ===================================================================================
 * ===================================================================================
 */

void SessionCloseCompletion_Release( _In_ SessionCloseCompletion* sessionCloseCompletion )
{
    ptrdiff_t count = Atomic_Dec( &sessionCloseCompletion->count );
    if( 0 == count )
    {
        SessionCloseCompletionCallback completionCallback;
        SessionCloseCompletionContext completionContext;

        // That means that this is the final release
        // so we call the completion callback (if necessary)
        // and delete the sessionCloseCompletion
        completionCallback = sessionCloseCompletion->completionCallback;
        completionContext = sessionCloseCompletion->completionContext;
        trace_SessionCloseCompletion_Release_CompletionCallback(sessionCloseCompletion, (void *)completionCallback);
        PAL_Free(sessionCloseCompletion);
        if( completionCallback )
        {
            completionCallback(completionContext);
        }
    }
    else
    {
        trace_SessionCloseCompletion_Release_Count(sessionCloseCompletion, (int)count );
    }
}

MI_Result MI_CALL InteractionProtocolHandler_Session_New(
        _In_     MI_Application *miApplication,
        _In_opt_z_ const MI_Char *_protocol,
        _In_opt_z_ const MI_Char *destination,
        _In_opt_ MI_DestinationOptions *options,
        _In_opt_ MI_SessionCallbacks *callbacks,
        _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
        _Out_    MI_Session *_session)
{
    InteractionProtocolHandler_Session *session = NULL;
    MI_Result result = MI_RESULT_OK;
    InteractionProtocolHandler_ProtocolType protocolType;

    if (_protocol)
    {
        if (Tcscasecmp(_protocol, MI_T("OMI_SOCKETS")) == 0)
        {
            protocolType = PROTOCOL_SOCKET;
        }
        else if (Tcscasecmp(_protocol, MI_T("MI_REMOTE_WSMAN")) == 0)
        {
            protocolType = PROTOCOL_WSMAN;
        }
        else
        {
            return MI_RESULT_INVALID_PARAMETER;
        }
    }
    else if (destination)
    {
        protocolType = PROTOCOL_WSMAN;
    }
    else
    {
        protocolType = PROTOCOL_SOCKET;
    }

    if (extendedError)
        *extendedError = NULL;

    memset(_session, 0, sizeof(*_session));

    session = PAL_Calloc(1, sizeof(InteractionProtocolHandler_Session));
    if (session == NULL)
    {
        result = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        goto done;
    }
    if (destination)
    {
        session->hostname = PAL_Tcsdup(destination);
        if (session->hostname == NULL)
        {
            result = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            goto done;
        }
    }
    session->protocolType = protocolType;
    session->sessionCloseCompletion = (SessionCloseCompletion*)PAL_Calloc(1, sizeof(SessionCloseCompletion));
    if (session->sessionCloseCompletion == NULL)
    {
        result = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        goto done;
    }
    memset( session->sessionCloseCompletion, 0, sizeof(SessionCloseCompletion) );
    session->sessionCloseCompletion->count = 1;  // The session itself, released on session close

    if (options)
    {
        result = MI_DestinationOptions_Clone(options, &session->destinationOptions);
        if (result != MI_RESULT_OK)
            goto done;
    }

done:
    if (result == MI_RESULT_OK)
    {
        session->parentApplication = (InteractionProtocolHandler_Application*) miApplication->reserved2;
        _session->ft = &g_interactionProtocolHandler_SessionFT;
        _session->reserved1 = 0;
        _session->reserved2 = (ptrdiff_t) session;
        memcpy(&session->myMiSession, _session, sizeof(session->myMiSession));
    }
    else
    {
        _session->ft = &g_interactionProtocolHandler_SessionFT_Dummy;
        _session->reserved1 = 0;
        _session->reserved2 = 0;
        if (session)
        {
            if (session->hostname)
                PAL_Free(session->hostname);

            PAL_Free(session);
        }

    }

    return result;
}

MI_Result MI_CALL InteractionProtocolHandler_Session_Close(
        _Inout_     MI_Session *_session,
        _In_opt_ void *completionContext,
        _In_opt_ void (MI_CALL *completionCallback)(_In_opt_ void *completionContext))
{
    InteractionProtocolHandler_Session *session = (InteractionProtocolHandler_Session *)_session->reserved2;
    if (session)
    {
        SessionCloseCompletion* sessionCloseCompletion = session->sessionCloseCompletion;
        trace_InteractionProtocolHandler_Session_Close(session, (void *)completionCallback);

        if (session->destinationOptions.ft)
        {
            MI_DestinationOptions_Delete(&session->destinationOptions);
        }

        DEBUG_ASSERT( NULL != sessionCloseCompletion );

        sessionCloseCompletion->completionContext = completionContext;
        sessionCloseCompletion->completionCallback = completionCallback;

        PAL_Free(session->hostname);
        PAL_Free(session);
        SessionCloseCompletion_Release( sessionCloseCompletion );
    }
    else if (completionCallback)
    {
        completionCallback(completionContext);
    }

    return MI_RESULT_OK;
}

MI_Result MI_CALL InteractionProtocolHandler_Session_GetApplication(
        _In_     MI_Session *_session,
        _Out_    MI_Application *application)
{
    InteractionProtocolHandler_Session *session;
    if (_session)
    {
        session = (InteractionProtocolHandler_Session*)_session->reserved2;
        if (session)
        {
            memcpy(application, &session->parentApplication->myMiApplication, sizeof(*application));
            return MI_RESULT_OK;
        }
        else
            return MI_RESULT_INVALID_PARAMETER;
    }
    else
    {
        return MI_RESULT_INVALID_PARAMETER;
    }
}

static void* MI_CALL InteractionProtocolHandler_Protocol_RunThread(void* _operation)
{
    InteractionProtocolHandler_Operation *operation = (InteractionProtocolHandler_Operation*) _operation;
    MI_Result miResult;
    SessionCloseCompletion* sessionCloseCompletion = NULL;
    ApplicationThread *operationThread = NULL;
    InteractionProtocolHandler_Application *application = NULL;

    trace_InteractionProtocolHandler_Protocol_RunThread();

    // Since for now we create this thread for each operation (instead of per each session)
    // we need to release the refcount when finishing
    sessionCloseCompletion = operation->parentSession->sessionCloseCompletion;

    operationThread = operation->protocolRunThread;

    application = operation->parentSession->parentApplication;

    //printf("InteractionProtocolHandler_Protocol_RunThread starting - application=%p, thread=%p\n", application, operationThread);

    if (operation->protocols.type == PROTOCOL_SOCKET)
    {
        ProtocolSocketAndBase* protocol = operation->protocols.protocol.socket;
        miResult = Protocol_Run( &protocol->internalProtocolBase, TIME_NEVER);
        ProtocolSocketAndBase_ReadyToFinish( protocol );
    }
    else
    {
        miResult = WsmanClient_Run( operation->protocols.protocol.wsman, TIME_NEVER);
        //TODO: do we need a WsmanClient_ReadyToFinish()?
    }

    trace_InteractionProtocolHandler_Protocol_RunThread_WithResult(miResult);


    if( sessionCloseCompletion )
    {
        SessionCloseCompletion_Release( sessionCloseCompletion );
    }

    InteractionProtocolHandler_Application_SafeCloseThread(application, operationThread);
    //printf("InteractionProtocolHandler_Protocol_RunThread - exiting, application=%p, thread=%p\n", application, operationThread);

    return 0;
}

static MI_Result _CreateSocketConnector(
    ProtocolSocketAndBase **socket,
    Selector *selector,
    InteractionOpenParams *interactionParam,
    const MI_Char *locator,
    MI_DestinationOptions *options)
{
    const MI_Char * user = NULL;
    MI_Char * password = NULL;
    char* user_ = NULL;
    char* password_ = NULL;
    MI_Result r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
    const char* locator_ = NULL;
    char* locator_mem = NULL;
    MI_Uint32 passwordLength = 0;

    if (options)
    {
        MI_UserCredentials credentials;
        const MI_Char *optionName;
        r = MI_DestinationOptions_GetCredentialsAt(options, 0, &optionName, &credentials, NULL);
        if ((r == MI_RESULT_NOT_FOUND) || (r == MI_RESULT_INVALID_PARAMETER))
            r = MI_RESULT_OK;
        else if (r != MI_RESULT_OK)
            goto done;
        else
        {
            if ((Tcscmp(credentials.authenticationType, MI_AUTH_TYPE_CLIENT_CERTS) != 0) &&
                (Tcscmp(credentials.authenticationType, MI_AUTH_TYPE_ISSUER_CERT) != 0))
            {
                user = credentials.credentials.usernamePassword.username;
                r = MI_DestinationOptions_GetCredentialsPasswordAt(
                        options, 0, &optionName, NULL, 0, &passwordLength, NULL);
                if ((r != MI_RESULT_NOT_FOUND) && (r != MI_RESULT_SERVER_LIMITS_EXCEEDED))
                {
                    size_t allocSize = 0;
                    if (SizeTMult(passwordLength, sizeof(MI_Char), &allocSize) == S_OK)
                        password = PAL_Malloc(allocSize);

                    if (password == NULL)
                    {
                        r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
                        goto done;
                    }
                    r = MI_DestinationOptions_GetCredentialsPasswordAt(
                            options, 0, &optionName, password, passwordLength, &passwordLength, NULL);
                    if (r != MI_RESULT_OK)
                        goto done;
                }
                else if (r != MI_RESULT_OK)
                    goto done;
            }
        }
    }

    // Locator defaults to SOCKETFILE:
    if (locator == NULL)
    {
#ifdef CONFIG_POSIX
        locator_ = OMI_GetPath(ID_SOCKETFILE);
#else
        locator_ = "localhost:7777";
#endif
    }
    else
    {
        locator_mem = _StringToStr(locator);
        locator_ = locator_mem;
        if (!locator_)
        {
            goto done;
        }
    }

    // Convert host to 'char' type:
    if (user)
    {
        user_ = _StringToStr(user);
        if (!user_)
        {
            goto done;
        }
    }
    if (password)
    {
        password_ = _StringToStr(password);
        if (!password_)
        {
            goto done;
        }
    }

    r = ProtocolSocketAndBase_New_Connector(
        socket,
        NULL, /* selector */
        locator_,
        interactionParam,
        user_,
        password_);
done:
    PAL_Free(locator_mem);
    PAL_Free(user_);
    if (password)
    {
#if defined(_MSC_VER)
        SecureZeroMemory(password, passwordLength * sizeof(MI_Char));
#else
        memset(password, 0, passwordLength * sizeof(MI_Char));
#endif
        PAL_Free(password);
    }
    if (password_)
    {
#if defined(_MSC_VER)
        SecureZeroMemory(password_, passwordLength * sizeof(char));
#else
        memset(password_, 0, passwordLength * sizeof(char));
#endif
        PAL_Free(password_);
    }

   return r;

}

MI_Result InteractionProtocolHandler_Session_Connect(
    InteractionProtocolHandler_Session *session,
    InteractionProtocolHandler_Operation *operation,
    const MI_Char *destination,
    MI_DestinationOptions *options
    )
{
    MI_Result r = MI_RESULT_SERVER_LIMITS_EXCEEDED;
    int res;
    SessionCloseCompletion* sessionCloseCompletion = NULL;

    // Fail if already connected:
    if (((operation->protocols.type == PROTOCOL_SOCKET) && operation->protocols.protocol.socket) ||
        ((operation->protocols.type == PROTOCOL_WSMAN) && operation->protocols.protocol.wsman))
    {
        trace_MI_SessionAlreadyConnected(operation);
        r = MI_RESULT_FAILED;
        goto done;
    }

    // Set connection state to pending.
    operation->currentState = InteractionProtocolHandler_Operation_CurrentState_WaitingForConnect;

    // this is the one that Opens the interaction (not the one that receives the open)
    Strand_Init( STRAND_DEBUG(ProtocolHandler) &operation->strand, &InteractionProtocolHandler_Operation_Strand_FT, STRAND_FLAG_ENTERSTRAND, NULL );

    // Establish connection with server:
    {
        InteractionOpenParams interactionParams;

        Strand_OpenPrepare( &operation->strand, &interactionParams, NULL, NULL, MI_TRUE );

        operation->protocols.type = session->protocolType;

        if (session->protocolType == PROTOCOL_SOCKET)
        {
            r = _CreateSocketConnector(
                    &operation->protocols.protocol.socket,
                    NULL, /* selector */
                    &interactionParams,
                    destination,
                    options);
        }
        else
        {
            r = WsmanClient_New_Connector(
                    &operation->protocols.protocol.wsman,
                    NULL, /* selector */
                    destination,
                    options,
                    &interactionParams);
        }
        if (r != MI_RESULT_OK)
        {
            trace_MI_SocketConnectorFailed(operation, r);
            goto done;
        }

        if (operation->parentSession)
        {
            ptrdiff_t count;

            sessionCloseCompletion = operation->parentSession->sessionCloseCompletion;
            // we just assign a non-zero value to flag indicating if we got here first
            count = Atomic_Inc( &sessionCloseCompletion->count );
            if (count <= 0)
            {
                DEBUG_ASSERT( count > 0 );
            }
        }

        operation->protocolRunThread = PAL_Calloc(1, sizeof(ApplicationThread));
        if (operation->protocolRunThread == NULL)
        {
            if (NULL != sessionCloseCompletion)
            {
                SessionCloseCompletion_Release(sessionCloseCompletion);
            }
            trace_MI_OutOfMemoryInOperation(operation);
            goto done;
        }

        InteractionProtocolHandler_Application_IncrementThreadCount(operation->parentSession->parentApplication);
        //printf("InteractionProtocolHandler_Session_Connect - creating protocol thread, application=%p, thread=%p\n", operation->parentSession->parentApplication, operation->protocolRunThread);
        res = Thread_CreateJoinable(
            &operation->protocolRunThread->thread,
            (ThreadProc)InteractionProtocolHandler_Protocol_RunThread,
            NULL,
            operation);

        if (res != 0)
        {
            trace_MI_FailedToStartRunThread(operation);

            InteractionProtocolHandler_Application_DecrementThreadCount(operation->parentSession->parentApplication);
            if( NULL != sessionCloseCompletion )
            {
                SessionCloseCompletion_Release( sessionCloseCompletion );
            }
            r = MI_RESULT_FAILED;
            goto done1;
        }
    }

done1:
    if (r)
    {
        PAL_Free(operation->protocolRunThread);
        operation->protocolRunThread = NULL;
    }

done:

    return r;
}

MI_Result InteractionProtocolHandler_Session_CommonInstanceCode(
        _In_     MI_Session *_session,
                 MI_Uint32 flags,
        _In_opt_ MI_OperationOptions *options,
        _In_opt_ MI_OperationCallbacks *callbacks,
        _In_opt_ RequestMsg *req,
        _Out_    MI_Operation *_operation)
{
    MI_Result miResult = MI_RESULT_OK;
    InteractionProtocolHandler_Operation *operation = NULL;
    InteractionProtocolHandler_Session *session = (InteractionProtocolHandler_Session *)_session->reserved2;

    if (req == NULL)
    {
        /* Means caller failed to allocate this */
        miResult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
        trace_MI_SessionFailed(session, miResult);
        goto done;
    }

    DEBUG_ASSERT( Message_IsRequest( &req->base ) );

    if (callbacks == NULL)
    {
        miResult = MI_RESULT_INVALID_PARAMETER;
        trace_MI_SessionFailed(session, miResult);
        goto done;
    }

    memset(_operation, 0, sizeof(*_operation));

    //Create actual operation object that holds all the state of the operation
    {
        operation = PAL_Calloc(1, sizeof(InteractionProtocolHandler_Operation));
        if (operation == NULL)
        {
            trace_MI_OutOfMemoryInSession(session);
            miResult = MI_RESULT_SERVER_LIMITS_EXCEEDED;
            goto done;
        }
    }

    operation->parentSession = session;
    if (options)
    {
        struct _GenericOptions_Handle *genericOptions = (struct _GenericOptions_Handle*) options;

        if (genericOptions->genericOptions && genericOptions->genericOptions->optionsInstance)
        {
            miResult = Instance_Clone(genericOptions->genericOptions->optionsInstance, &req->options, req->base.batch);
            if (miResult != MI_RESULT_OK)
            {
                trace_MI_InstanceToBatch_Failed(session, miResult);
                goto done;
            }

            if (session->protocolType == PROTOCOL_SOCKET)
            {
                miResult = InstanceToBatch(
                    genericOptions->genericOptions->optionsInstance,
                    NULL,
                    NULL,
                    req->base.batch,
                    &req->packedOptionsPtr,
                    &req->packedOptionsSize);
            }
            else
            {
                miResult = WSBuf_InstanceToBuf(
                        USERAGENT_UNKNOWN,
                        genericOptions->genericOptions->optionsInstance,
                        NULL,
                        NULL,
                        genericOptions->genericOptions->optionsInstance->classDecl,
                        req->base.batch,
                        WSMAN_ObjectFlag,
                        &req->packedOptionsPtr,
                        &req->packedOptionsSize);
            }
        }
    }
    operation->asyncOperationCallbacks = *callbacks;
    _operation->ft = &g_interactionProtocolHandler_OperationFT;
    _operation->reserved2 = (ptrdiff_t) operation;
    operation->myMiOperation = *_operation;
    if (req->base.tag == SubscribeReqTag)
    {
        operation->operationType = InteractionProtocolHandler_Operation_OperationType_Indication;
    }
    else if (req->base.tag == GetClassReqTag)
    {
        operation->operationType = InteractionProtocolHandler_Operation_OperationType_Class;
    }
    else
    {
        operation->operationType = InteractionProtocolHandler_Operation_OperationType_Instance;
    }
    operation->req = req;

    /* Kick off protocol initialization */
    miResult = InteractionProtocolHandler_Session_Connect(
            session, operation, session->hostname, &session->destinationOptions);
    if (miResult != MI_RESULT_OK)
    {
        trace_MI_SessionConnectFailed(session, miResult);
        goto done;
    }

    trace_InteractionProtocolHandler_SessionConnect_Passed();

    /* Everything is asynchronous from this point onwards if we were successful */

done:
    if (miResult != MI_RESULT_OK)
    {
        trace_MI_SessionFailed(session, miResult);

        if (operation)
        {
            _Operation_SendFinalResult_Internal(operation);
            PAL_Free(operation);
        }

        memset(_operation, 0, sizeof(*_operation));
        _operation->ft = &g_interactionProtocolHandler_OperationFT_Dummy;
    }

    return miResult;
}


void MI_CALL InteractionProtocolHandler_Session_GetInstance(
        _In_     MI_Session *_session,
                 MI_Uint32 flags,
        _In_opt_ MI_OperationOptions *options,
        _In_opt_z_ const MI_Char *namespaceName,
        _In_     const MI_Instance *inboundInstance,
        _In_opt_ MI_OperationCallbacks *callbacks,
        _Out_    MI_Operation *_operation)
{
    MI_Result miResult = MI_RESULT_OK;
    GetInstanceReq *req = NULL;
    InteractionProtocolHandler_Session *session = (InteractionProtocolHandler_Session *)_session->reserved2;

    memset(_operation, 0, sizeof(*_operation));


    // Create the request message:
    {
        MI_Uint32 flag = WSMANFlag;
        if (session->protocolType == PROTOCOL_SOCKET)
            flag = BinaryProtocolFlag;

        req = GetInstanceReq_New(_NextOperationId(), flag);
    }
    // Set nameSpace:
    if (req && namespaceName)
    {
        req->nameSpace = Batch_Tcsdup(req->base.base.batch, namespaceName);
        if (!req->nameSpace)
        {
            GetInstanceReq_Release(req);
            req = NULL;
        }
    }
    // Pack the instance name into the message's batch.
    if (req)
    {
        miResult = Instance_Clone(inboundInstance, &req->instanceName, req->base.base.batch);
        if (miResult != MI_RESULT_OK)
        {
            GetInstanceReq_Release(req);
            req = NULL;
        }

        if (session->protocolType == PROTOCOL_SOCKET)
        {
            miResult = InstanceToBatch(
                inboundInstance,
                NULL,
                NULL,
                req->base.base.batch,
                &req->packedInstanceNamePtr,
                &req->packedInstanceNameSize);
        }
        else
        {
            miResult = WSBuf_InstanceToBuf(
                    USERAGENT_UNKNOWN,
                    inboundInstance,
                    NULL,
                    NULL,
                    inboundInstance->classDecl,
                    req->base.base.batch,
                    WSMAN_ObjectFlag,
                    &req->packedInstanceNamePtr,
                    &req->packedInstanceNameSize);
        }
        if (miResult != MI_RESULT_OK)
        {
            GetInstanceReq_Release(req);
            req = NULL;
        }
    }

    miResult = InteractionProtocolHandler_Session_CommonInstanceCode(_session, flags, options, callbacks, (RequestMsg*)req, _operation);

    if ((miResult != MI_RESULT_OK) && req)
    {
        GetInstanceReq_Release(req);
    }
}

void MI_CALL InteractionProtocolHandler_Session_ModifyInstance(
        _In_     MI_Session *_session,
                 MI_Uint32 flags,
        _In_opt_ MI_OperationOptions *options,
        _In_opt_z_ const MI_Char *namespaceName,
        _In_     const MI_Instance *inboundInstance,
        _In_opt_ MI_OperationCallbacks *callbacks,
        _Out_    MI_Operation *_operation)
{
    MI_Result miResult = MI_RESULT_OK;
    ModifyInstanceReq *req = NULL;
    InteractionProtocolHandler_Session *session = (InteractionProtocolHandler_Session *)_session->reserved2;

    memset(_operation, 0, sizeof(*_operation));


    // Create the request message:
    {
        MI_Uint32 flag = WSMANFlag;
        if (session->protocolType == PROTOCOL_SOCKET)
            flag = BinaryProtocolFlag;

        req = ModifyInstanceReq_New(_NextOperationId(), flag);
    }
    // Set nameSpace:
    if (req && namespaceName)
    {
        req->nameSpace = Batch_Tcsdup(req->base.base.batch, namespaceName);
        if (!req->nameSpace)
        {
            ModifyInstanceReq_Release(req);
            req = NULL;
        }
    }
    // Pack the instance name into the message's batch.
    if (req)
    {
        miResult = Instance_Clone(inboundInstance, &req->instance, req->base.base.batch);
        if (miResult != MI_RESULT_OK)
        {
            ModifyInstanceReq_Release(req);
            req = NULL;
        }

        if (session->protocolType == PROTOCOL_SOCKET)
        {
            miResult = InstanceToBatch(
                inboundInstance,
                NULL,
                NULL,
                req->base.base.batch,
                &req->packedInstancePtr,
                &req->packedInstanceSize);
        }
        else
        {
            miResult = WSBuf_InstanceToBuf(
                    USERAGENT_UNKNOWN,
                    inboundInstance,
                    NULL,
                    NULL,
                    inboundInstance->classDecl,
                    req->base.base.batch,
                    WSMAN_ObjectFlag,
                    &req->packedInstancePtr,
                    &req->packedInstanceSize);
        }
         if (miResult != MI_RESULT_OK)
        {
            ModifyInstanceReq_Release(req);
            req = NULL;
        }
    }

    miResult = InteractionProtocolHandler_Session_CommonInstanceCode(_session, flags, options, callbacks, (RequestMsg*)req, _operation);

    if ((miResult != MI_RESULT_OK) && req)
    {
        ModifyInstanceReq_Release(req);
    }
}

void MI_CALL InteractionProtocolHandler_Session_CreateInstance(
        _In_     MI_Session *_session,
                 MI_Uint32 flags,
        _In_opt_ MI_OperationOptions *options,
        _In_opt_z_ const MI_Char *namespaceName,
        _In_     const MI_Instance *inboundInstance,
        _In_opt_ MI_OperationCallbacks *callbacks,
        _Out_    MI_Operation *_operation)
{
    MI_Result miResult = MI_RESULT_OK;
    CreateInstanceReq *req = NULL;
    InteractionProtocolHandler_Session *session = (InteractionProtocolHandler_Session *)_session->reserved2;

    memset(_operation, 0, sizeof(*_operation));

    // Create the request message:
    {
        MI_Uint32 flag = WSMANFlag;
        if (session->protocolType == PROTOCOL_SOCKET)
            flag = BinaryProtocolFlag;

         req = CreateInstanceReq_New(_NextOperationId(), flag);
    }
    // Set nameSpace:
    if (req && namespaceName)
    {
        req->nameSpace = Batch_Tcsdup(req->base.base.batch, namespaceName);
        if (!req->nameSpace)
        {
            CreateInstanceReq_Release(req);
            req = NULL;
        }
    }
    // Pack the instance name into the message's batch.
    if (req)
    {
        miResult = Instance_Clone(inboundInstance, &req->instance, req->base.base.batch);
        if (miResult != MI_RESULT_OK)
        {
            CreateInstanceReq_Release(req);
            req = NULL;
        }

        if (session->protocolType == PROTOCOL_SOCKET)
        {
            miResult = InstanceToBatch(
                inboundInstance,
                NULL,
                NULL,
                req->base.base.batch,
                &req->packedInstancePtr,
                &req->packedInstanceSize);
        }
        else
        {
            miResult = WSBuf_InstanceToBuf(
                    USERAGENT_UNKNOWN,
                    inboundInstance,
                    NULL,
                    NULL,
                    inboundInstance->classDecl,
                    req->base.base.batch,
                    WSMAN_ObjectFlag,
                    &req->packedInstancePtr,
                    &req->packedInstanceSize);
        }

        if (miResult != MI_RESULT_OK)
        {
            CreateInstanceReq_Release(req);
            req = NULL;
        }
    }

    miResult = InteractionProtocolHandler_Session_CommonInstanceCode(_session, flags, options, callbacks, (RequestMsg*)req, _operation);

    if ((miResult != MI_RESULT_OK) && req)
    {
        CreateInstanceReq_Release(req);
    }
}

void MI_CALL InteractionProtocolHandler_Session_DeleteInstance(
        _In_     MI_Session *_session,
                 MI_Uint32 flags,
        _In_opt_ MI_OperationOptions *options,
        _In_opt_z_ const MI_Char *namespaceName,
        _In_     const MI_Instance *inboundInstance,
        _In_opt_ MI_OperationCallbacks *callbacks,
        _Out_    MI_Operation *_operation)
{
    MI_Result miResult = MI_RESULT_OK;
    DeleteInstanceReq *req = NULL;
    InteractionProtocolHandler_Session *session = (InteractionProtocolHandler_Session *)_session->reserved2;

    memset(_operation, 0, sizeof(*_operation));

    // Create the request message:
    {
        MI_Uint32 flag = WSMANFlag;
        if (session->protocolType == PROTOCOL_SOCKET)
            flag = BinaryProtocolFlag;

         req = DeleteInstanceReq_New(_NextOperationId(), flag);
    }
    // Set nameSpace:
    if (req && namespaceName)
    {
        req->nameSpace = Batch_Tcsdup(req->base.base.batch, namespaceName);
        if (!req->nameSpace)
        {
            DeleteInstanceReq_Release(req);
            req = NULL;
        }
    }
    // Pack the instance name into the message's batch.
    if (req)
    {
        miResult = Instance_Clone(inboundInstance, &req->instanceName, req->base.base.batch);
        if (miResult != MI_RESULT_OK)
        {
            DeleteInstanceReq_Release(req);
            req = NULL;
        }

        if (session->protocolType == PROTOCOL_SOCKET)
        {
            miResult = InstanceToBatch(
                inboundInstance,
                NULL,
                NULL,
                req->base.base.batch,
                &req->packedInstanceNamePtr,
                &req->packedInstanceNameSize);
        }
        else
        {
            miResult = WSBuf_InstanceToBuf(
                    USERAGENT_UNKNOWN,
                    inboundInstance,
                    NULL,
                    NULL,
                    inboundInstance->classDecl,
                    req->base.base.batch,
                    WSMAN_ObjectFlag,
                    &req->packedInstanceNamePtr,
                    &req->packedInstanceNameSize);
        }

        if (miResult != MI_RESULT_OK)
        {
            DeleteInstanceReq_Release(req);
            req = NULL;
        }
    }

    miResult = InteractionProtocolHandler_Session_CommonInstanceCode(_session, flags, options, callbacks, (RequestMsg*)req, _operation);

    if ((miResult != MI_RESULT_OK) && req)
    {
        DeleteInstanceReq_Release(req);
    }
}

void MI_CALL InteractionProtocolHandler_Session_Invoke(
        _In_     MI_Session *_session,
                 MI_Uint32 flags,
        _In_opt_ MI_OperationOptions *options,
        _In_opt_z_ const MI_Char *namespaceName,
        _In_opt_z_ const MI_Char *className,
        _In_z_     const MI_Char *methodName,
        _In_opt_ const MI_Instance *inboundInstance,
        _In_opt_ const MI_Instance *inboundProperties,
        _In_opt_ MI_OperationCallbacks *callbacks,
        _Out_    MI_Operation *_operation)
{
    MI_Result miResult = MI_RESULT_OK;
    InvokeReq *req = NULL;
    InteractionProtocolHandler_Session *session = (InteractionProtocolHandler_Session *)_session->reserved2;

    memset(_operation, 0, sizeof(*_operation));

    // Create the request message:
    {
        MI_Uint32 flag = WSMANFlag;
        if (session->protocolType == PROTOCOL_SOCKET)
            flag = BinaryProtocolFlag;

         req = InvokeReq_New(_NextOperationId(), flag);
    }
    // Set nameSpace:
    if (req && namespaceName)
    {
        req->nameSpace = Batch_Tcsdup(req->base.base.batch, namespaceName);
        if (!req->nameSpace)
        {
            InvokeReq_Release(req);
            req = NULL;
        }
    }
    // Set method name:
    if (req && methodName)
    {
        req->function = Batch_Tcsdup(req->base.base.batch, methodName);
        if (!req->function)
        {
            InvokeReq_Release(req);
            req = NULL;
        }
    }
    // Pack the instance into the message's batch.
    if (req && inboundInstance)
    {
        miResult = Instance_Clone(inboundInstance, &req->instance, req->base.base.batch);
        if (miResult != MI_RESULT_OK)
        {
            InvokeReq_Release(req);
            req = NULL;
        }

        if (session->protocolType == PROTOCOL_SOCKET)
        {
            miResult = InstanceToBatch(
                inboundInstance,
                NULL,
                NULL,
                req->base.base.batch,
                &req->packedInstancePtr,
                &req->packedInstanceSize);
        }
        else
        {
            miResult = WSBuf_InstanceToBuf(
                    USERAGENT_UNKNOWN,
                    inboundInstance,
                    NULL,
                    NULL,
                    inboundInstance->classDecl,
                    req->base.base.batch,
                    WSMAN_ObjectFlag,
                    &req->packedInstancePtr,
                    &req->packedInstanceSize);
        }

        if (miResult != MI_RESULT_OK)
        {
            InvokeReq_Release(req);
            req = NULL;
        }
    }
    else if (req && className)
    {
        req->className = Batch_Tcsdup(req->base.base.batch, className);
        if (!req->className)
        {
            InvokeReq_Release(req);
            req = NULL;
        }
    }
    if (req && inboundProperties)
    {
        miResult = Instance_Clone(inboundProperties, &req->instanceParams, req->base.base.batch);
        if (miResult != MI_RESULT_OK)
        {
            InvokeReq_Release(req);
            req = NULL;
        }

        if (session->protocolType == PROTOCOL_SOCKET)
        {
            miResult = InstanceToBatch(
                inboundProperties,
                NULL,
                NULL,
                req->base.base.batch,
                &req->packedInstanceParamsPtr,
                &req->packedInstanceParamsSize);
        }
        else
        {
            miResult = WSBuf_InstanceToBuf(
                    USERAGENT_UNKNOWN,
                    inboundInstance,
                    NULL,
                    NULL,
                    inboundInstance->classDecl,
                    req->base.base.batch,
                    WSMAN_ObjectFlag,
                    &req->packedInstancePtr,
                    &req->packedInstanceSize);
        }

        if (miResult != MI_RESULT_OK)
        {
            InvokeReq_Release(req);
            req = NULL;
        }
    }

    miResult = InteractionProtocolHandler_Session_CommonInstanceCode(_session, flags, options, callbacks, (RequestMsg*)req, _operation);

    if ((miResult != MI_RESULT_OK) && req)
    {
        InvokeReq_Release(req);
    }
}

void MI_CALL InteractionProtocolHandler_Session_EnumerateInstances(
        _In_     MI_Session *_session,
                 MI_Uint32 flags,
        _In_opt_ MI_OperationOptions *options,
        _In_opt_z_ const MI_Char *namespaceName,
        _In_opt_z_ const MI_Char *className,
                 MI_Boolean keysOnly,
        _In_opt_ MI_OperationCallbacks *callbacks,
        _Out_    MI_Operation *_operation)
{
    MI_Result miResult = MI_RESULT_OK;
    EnumerateInstancesReq *req = NULL;
    InteractionProtocolHandler_Session *session = (InteractionProtocolHandler_Session *)_session->reserved2;

    memset(_operation, 0, sizeof(*_operation));


    // Create the request message:
    {
        MI_Uint32 flag = WSMANFlag;
        if (session->protocolType == PROTOCOL_SOCKET)
            flag = BinaryProtocolFlag;

         req = EnumerateInstancesReq_New(_NextOperationId(), flag);
    }

    // If no shallow flag, use deep inheritance.
    if (req && !(flags & MI_OPERATIONFLAGS_POLYMORPHISM_SHALLOW))
    {
        req->deepInheritance = MI_TRUE;
    }

    // Set nameSpace:
    if (req && namespaceName)
    {
        req->nameSpace = Batch_Tcsdup(req->base.base.batch, namespaceName);
        if (!req->nameSpace)
        {
            EnumerateInstancesReq_Release(req);
            req = NULL;
        }
    }
    if (req && className)
    {
        req->className = Batch_Tcsdup(req->base.base.batch, className);
        if (!req->className)
        {
            EnumerateInstancesReq_Release(req);
            req = NULL;
        }
    }

    miResult = InteractionProtocolHandler_Session_CommonInstanceCode(_session, flags, options, callbacks, (RequestMsg*)req, _operation);

    if ((miResult != MI_RESULT_OK) && req)
    {
        EnumerateInstancesReq_Release(req);
    }
}

void MI_CALL InteractionProtocolHandler_Session_QueryInstances(
        _In_     MI_Session *_session,
                 MI_Uint32 flags,
        _In_opt_ MI_OperationOptions *options,
        _In_opt_z_ const MI_Char *namespaceName,
        _In_opt_z_ const MI_Char *queryDialect,
        _In_opt_z_ const MI_Char *queryExpression,
        _In_opt_ MI_OperationCallbacks *callbacks,
        _Out_    MI_Operation *_operation)
{
{
    MI_Result miResult = MI_RESULT_OK;
    EnumerateInstancesReq *req = NULL;
    InteractionProtocolHandler_Session *session = (InteractionProtocolHandler_Session *)_session->reserved2;

    memset(_operation, 0, sizeof(*_operation));


    // Create the request message:
    {
        MI_Uint32 flag = WSMANFlag;
        if (session->protocolType == PROTOCOL_SOCKET)
            flag = BinaryProtocolFlag;

         req = EnumerateInstancesReq_New(_NextOperationId(), flag);
    }
    // Set nameSpace:
    if (req && namespaceName)
    {
        req->nameSpace = Batch_Tcsdup(req->base.base.batch, namespaceName);
        if (!req->nameSpace)
        {
            EnumerateInstancesReq_Release(req);
            req = NULL;
        }
    }
    if (req && queryDialect)
    {
        req->queryLanguage = Batch_Tcsdup(req->base.base.batch, queryDialect);
        if (!req->queryLanguage)
        {
            EnumerateInstancesReq_Release(req);
            req = NULL;
        }
    }
    if (req && queryExpression)
    {
        req->queryExpression = Batch_Tcsdup(req->base.base.batch, queryExpression);
        if (!req->queryExpression)
        {
            EnumerateInstancesReq_Release(req);
            req = NULL;
        }
    }
    // If no shallow flag, use deep inheritance.
    if (req && !(flags & MI_OPERATIONFLAGS_POLYMORPHISM_SHALLOW))
    {
        req->deepInheritance = MI_TRUE;
    }

    miResult = InteractionProtocolHandler_Session_CommonInstanceCode(_session, flags, options, callbacks, (RequestMsg*)req, _operation);

    if ((miResult != MI_RESULT_OK) && req)
    {
        EnumerateInstancesReq_Release(req);
    }
}}

void MI_CALL InteractionProtocolHandler_Session_AssociatorInstances(
        _In_     MI_Session *_session,
                 MI_Uint32 flags,
        _In_opt_ MI_OperationOptions *options,
        _In_opt_z_ const MI_Char *namespaceName,
        _In_     const MI_Instance *instanceKeys,
        _In_opt_z_ const MI_Char *assocClass,
        _In_opt_z_ const MI_Char *resultClass,
        _In_opt_z_ const MI_Char *role,
        _In_opt_z_ const MI_Char *resultRole,
                 MI_Boolean keysOnly,
        _In_opt_ MI_OperationCallbacks *callbacks,
        _Out_    MI_Operation *_operation)
{
    MI_Result miResult = MI_RESULT_OK;
    AssociationsOfReq *req = NULL;
    InteractionProtocolHandler_Session *session = (InteractionProtocolHandler_Session *)_session->reserved2;

    memset(_operation, 0, sizeof(*_operation));

    // Create the request message:
    {
        MI_Uint32 flag = WSMANFlag;
        if (session->protocolType == PROTOCOL_SOCKET)
            flag = BinaryProtocolFlag;

         req = AssociationsOfReq_New(_NextOperationId(), flag, AssociatorsOfReqTag);
    }
    // Set nameSpace:
    if (req && namespaceName)
    {
        req->nameSpace = Batch_Tcsdup(req->base.base.batch, namespaceName);
        if (!req->nameSpace)
        {
            AssociationsOfReq_Release(req);
            req = NULL;
        }
    }
    if (req && assocClass)
    {
        req->assocClass = Batch_Tcsdup(req->base.base.batch, assocClass);
        if (!req->assocClass)
        {
            AssociationsOfReq_Release(req);
            req = NULL;
        }
    }
    if (req && resultClass)
    {
        req->resultClass = Batch_Tcsdup(req->base.base.batch, resultClass);
        if (!req->resultClass)
        {
            AssociationsOfReq_Release(req);
            req = NULL;
        }
    }
    if (req && role)
    {
        req->role = Batch_Tcsdup(req->base.base.batch, role);
        if (!req->role)
        {
            AssociationsOfReq_Release(req);
            req = NULL;
        }
    }
    if (req && resultRole)
    {
        req->resultRole = Batch_Tcsdup(req->base.base.batch, resultRole);
        if (!req->resultRole)
        {
            AssociationsOfReq_Release(req);
            req = NULL;
        }
    }
    // Pack the instance into the message's batch.
    if (req && instanceKeys)
    {
        miResult = Instance_Clone(instanceKeys, &req->instance, req->base.base.batch);
        if (miResult != MI_RESULT_OK)
        {
            AssociationsOfReq_Release(req);
            req = NULL;
        }

        if (session->protocolType == PROTOCOL_SOCKET)
        {
            miResult = InstanceToBatch(
                instanceKeys,
                NULL,
                NULL,
                req->base.base.batch,
                &req->packedInstancePtr,
                &req->packedInstanceSize);
        }
        else
        {
            miResult = WSBuf_InstanceToBuf(
                    USERAGENT_UNKNOWN,
                    instanceKeys,
                    NULL,
                    NULL,
                    instanceKeys->classDecl,
                    req->base.base.batch,
                    WSMAN_ObjectFlag,
                    &req->packedInstancePtr,
                    &req->packedInstanceSize);
        }

        if (miResult != MI_RESULT_OK)
        {
            AssociationsOfReq_Release(req);
            req = NULL;
        }
    }

    miResult = InteractionProtocolHandler_Session_CommonInstanceCode(_session, flags, options, callbacks, (RequestMsg*)req, _operation);

    if ((miResult != MI_RESULT_OK) && req)
    {
        AssociationsOfReq_Release(req);
    }
}

void MI_CALL InteractionProtocolHandler_Session_ReferenceInstances(
        _In_     MI_Session *_session,
                 MI_Uint32 flags,
        _In_opt_ MI_OperationOptions *options,
        _In_opt_z_ const MI_Char *namespaceName,
        _In_     const MI_Instance *instanceKeys,
        _In_opt_z_ const MI_Char *resultClass,
        _In_opt_z_ const MI_Char *role,
                 MI_Boolean keysOnly,
        _In_opt_ MI_OperationCallbacks *callbacks,
        _Out_    MI_Operation *_operation)
{
    MI_Result miResult = MI_RESULT_OK;
    AssociationsOfReq *req = NULL;
    InteractionProtocolHandler_Session *session = (InteractionProtocolHandler_Session *)_session->reserved2;

    memset(_operation, 0, sizeof(*_operation));

    // Create the request message:
    {
        MI_Uint32 flag = WSMANFlag;
        if (session->protocolType == PROTOCOL_SOCKET)
            flag = BinaryProtocolFlag;

         req = AssociationsOfReq_New(_NextOperationId(), flag, ReferencesOfReqTag);
    }
    // Set nameSpace:
    if (req && namespaceName)
    {
        req->nameSpace = Batch_Tcsdup(req->base.base.batch, namespaceName);
        if (!req->nameSpace)
        {
            AssociationsOfReq_Release(req);
            req = NULL;
        }
    }
    if (req && resultClass)
    {
        req->resultClass = Batch_Tcsdup(req->base.base.batch, resultClass);
        if (!req->resultClass)
        {
            AssociationsOfReq_Release(req);
            req = NULL;
        }
    }
    if (req && role)
    {
        req->role = Batch_Tcsdup(req->base.base.batch, role);
        if (!req->role)
        {
            AssociationsOfReq_Release(req);
            req = NULL;
        }
    }
    // Pack the instance into the message's batch.
    if (req && instanceKeys)
    {
        miResult = Instance_Clone(instanceKeys, &req->instance, req->base.base.batch);
        if (miResult != MI_RESULT_OK)
        {
            AssociationsOfReq_Release(req);
            req = NULL;
        }

        if (session->protocolType == PROTOCOL_SOCKET)
        {
            miResult = InstanceToBatch(
                instanceKeys,
                NULL,
                NULL,
                req->base.base.batch,
                &req->packedInstancePtr,
                &req->packedInstanceSize);
        }
        else
        {
            miResult = WSBuf_InstanceToBuf(
                    USERAGENT_UNKNOWN,
                    instanceKeys,
                    NULL,
                    NULL,
                    instanceKeys->classDecl,
                    req->base.base.batch,
                    WSMAN_ObjectFlag,
                    &req->packedInstancePtr,
                    &req->packedInstanceSize);
        }

        if (miResult != MI_RESULT_OK)
        {
            AssociationsOfReq_Release(req);
            req = NULL;
        }
    }

    miResult = InteractionProtocolHandler_Session_CommonInstanceCode(_session, flags, options, callbacks, (RequestMsg*)req, _operation);

    if ((miResult != MI_RESULT_OK) && req)
    {
        AssociationsOfReq_Release(req);
    }
}

void MI_CALL InteractionProtocolHandler_Session_Subscribe(
        _In_     MI_Session *_session,
                 MI_Uint32 flags,
        _In_opt_ MI_OperationOptions *options,
        _In_opt_z_ const MI_Char *namespaceName,
        _In_opt_z_ const MI_Char *queryDialect,
        _In_opt_z_ const MI_Char *queryExpression,
        _In_opt_ const MI_SubscriptionDeliveryOptions *deliverOptions,
        _In_opt_ MI_OperationCallbacks *callbacks,
        _Out_    MI_Operation *_operation)
{
    MI_Result miResult = MI_RESULT_OK;
    SubscribeReq *req = NULL;
    InteractionProtocolHandler_Session *session = (InteractionProtocolHandler_Session *)_session->reserved2;

    memset(_operation, 0, sizeof(*_operation));


    // Create the request message:
    {
        MI_Uint32 flag = WSMANFlag;
        if (session->protocolType == PROTOCOL_SOCKET)
            flag = BinaryProtocolFlag;

         req = SubscribeReq_New(_NextOperationId(), flag);
    }
    // Set nameSpace:
    if (req && namespaceName)
    {
        req->nameSpace = Batch_Tcsdup(req->base.base.batch, namespaceName);
        if (!req->nameSpace)
        {
            SubscribeReq_Release(req);
            req = NULL;
        }
    }
    if (req && queryDialect)
    {
        req->language = Batch_Tcsdup(req->base.base.batch, queryDialect);
        if (!req->language)
        {
            SubscribeReq_Release(req);
            req = NULL;
        }
    }
    if (req && queryExpression)
    {
        req->filter = Batch_Tcsdup(req->base.base.batch, queryExpression);
        if (!req->filter)
        {
            SubscribeReq_Release(req);
            req = NULL;
        }
    }

    /* TODO: Attach options */

    miResult = InteractionProtocolHandler_Session_CommonInstanceCode(_session, flags, options, callbacks, (RequestMsg*)req, _operation);

    if ((miResult != MI_RESULT_OK) && req)
    {
        SubscribeReq_Release(req);
    }
}

void MI_CALL InteractionProtocolHandler_Session_GetClass(
        _In_     MI_Session *_session,
                 MI_Uint32 flags,
        _In_opt_ MI_OperationOptions *options,
        _In_opt_z_ const MI_Char *namespaceName,
        _In_opt_z_ const MI_Char *className,
        _In_opt_ MI_OperationCallbacks *callbacks,
        _Out_    MI_Operation *_operation)
{
    MI_Result miResult = MI_RESULT_OK;
    GetClassReq *req = NULL;
    InteractionProtocolHandler_Session *session = (InteractionProtocolHandler_Session *)_session->reserved2;

    memset(_operation, 0, sizeof(*_operation));


    // Create the request message:
    {
        MI_Uint32 flag = WSMANFlag;
        if (session->protocolType == PROTOCOL_SOCKET)
            flag = BinaryProtocolFlag;

         req = GetClassReq_New(_NextOperationId(), flag);
    }
    // Set nameSpace:
    if (req && namespaceName)
    {
        req->nameSpace = Batch_Tcsdup(req->base.base.batch, namespaceName);
        if (!req->nameSpace)
        {
            GetClassReq_Release(req);
            req = NULL;
        }
    }
    if (req && className)
    {
        req->className = Batch_Tcsdup(req->base.base.batch, className);
        if (!req->className)
        {
            GetClassReq_Release(req);
            req = NULL;
        }
    }

    miResult = InteractionProtocolHandler_Session_CommonInstanceCode(_session, flags, options, callbacks, (RequestMsg*)req, _operation);

    if ((miResult != MI_RESULT_OK) && req)
    {
        GetClassReq_Release(req);
    }
}

void MI_CALL InteractionProtocolHandler_Session_EnumerateClasses(
        _In_     MI_Session *session,
                 MI_Uint32 flags,
        _In_opt_ MI_OperationOptions *options,
        _In_opt_z_ const MI_Char *namespaceName,
        _In_opt_z_ const MI_Char *className,
                 MI_Boolean classNamesOnly,
        _In_opt_ MI_OperationCallbacks *callbacks,
        _Out_    MI_Operation *operation)
{
    memset(operation, 0, sizeof(*operation));
    operation->ft = &g_interactionProtocolHandler_OperationFT;
    if (callbacks && callbacks->classResult)
        callbacks->classResult(operation, callbacks->callbackContext, NULL, MI_FALSE, MI_RESULT_NOT_SUPPORTED, NULL, NULL, InteractionProtocolHandler_Client_Ack_PostToInteraction);
}

void MI_CALL InteractionProtocolHandler_Session_TestConnection(
        _In_     MI_Session *_session,
                 MI_Uint32 flags,
        _In_opt_ MI_OperationCallbacks *callbacks,
        _Out_    MI_Operation *_operation
        )
{

    MI_Result miResult = MI_RESULT_OK;
    NoOpReq *req = NULL;

    memset(_operation, 0, sizeof(*_operation));


    // Create the request message:
    {
         req = NoOpReq_New(_NextOperationId());
    }

    miResult = InteractionProtocolHandler_Session_CommonInstanceCode(_session, flags, NULL, callbacks, (RequestMsg*)req, _operation);

    if ((miResult != MI_RESULT_OK) && req)
    {
        NoOpReq_Release(req);
    }
}


const MI_SessionFT g_interactionProtocolHandler_SessionFT =
{
    InteractionProtocolHandler_Session_Close,
    InteractionProtocolHandler_Session_GetApplication,
    InteractionProtocolHandler_Session_GetInstance,
    InteractionProtocolHandler_Session_ModifyInstance,
    InteractionProtocolHandler_Session_CreateInstance,
    InteractionProtocolHandler_Session_DeleteInstance,
    InteractionProtocolHandler_Session_Invoke,
    InteractionProtocolHandler_Session_EnumerateInstances,
    InteractionProtocolHandler_Session_QueryInstances,
    InteractionProtocolHandler_Session_AssociatorInstances,
    InteractionProtocolHandler_Session_ReferenceInstances,
    InteractionProtocolHandler_Session_Subscribe,
    InteractionProtocolHandler_Session_GetClass,
    InteractionProtocolHandler_Session_EnumerateClasses,
    InteractionProtocolHandler_Session_TestConnection
};

MI_Result MI_CALL InteractionProtocolHandler_Session_Close_Dummy(
        _Inout_     MI_Session *session,
        _In_opt_ void *completionContext,
        _In_opt_ void (MI_CALL *completionCallback)(_In_opt_ void *completionContext))
{
    if (completionCallback)
        completionCallback(completionContext);

    return MI_RESULT_OK;
}
const MI_SessionFT g_interactionProtocolHandler_SessionFT_Dummy =
{
    InteractionProtocolHandler_Session_Close_Dummy
};


/* ===================================================================================
 * ===================================================================================
 * ===================================================================================
 * ===================================================================================
 * ===================================================================================
 * ===================================================================================
 */

PAL_Uint32 THREAD_API InteractionProtocolHandler_ThreadShutdown(void *_application)
{
    InteractionProtocolHandler_Application *application = (InteractionProtocolHandler_Application*) _application;
    ApplicationThread *nextThread;
    PAL_Uint32 returnValue;
    //printf("InteractionProtocolHandler_ThreadShutdown start - application = %p\n", application);
    do
    {
        ptrdiff_t notification = (ptrdiff_t) Atomic_Read((ptrdiff_t*) &application->listOfThreads);
        while (notification == 0)
        {
            CondLock_Wait((ptrdiff_t)application, (ptrdiff_t*) &application->listOfThreads, notification, CONDLOCK_DEFAULT_SPINCOUNT);

            notification = (ptrdiff_t) application->listOfThreads;
        }
        //printf("InteractionProtocolHandler_ThreadShutdown Got something to do - application = %p\n", application);

        do
        {
            Lock_Acquire(&application->listOfThreadsLock);

            nextThread = application->listOfThreads;
            if ((application->listOfThreads != NULL) && (application->listOfThreads != (ApplicationThread*)-1))
            {
                application->listOfThreads = nextThread->next;
            }

            Lock_Release(&application->listOfThreadsLock);

            if ((nextThread == NULL) || (nextThread == (ApplicationThread*)-1))
            {
                //printf("InteractionProtocolHandler_ThreadShutdown - Finished iteration, application=%p, nextThread=%p\n", application, nextThread);
                break;
            }

            //printf("InteractionProtocolHandler_ThreadShutdown - shutting down thread, application=%p, thread=%p\n", application, nextThread);
            Thread_Join(&nextThread->thread, &returnValue);
            Thread_Destroy(&nextThread->thread);
            PAL_Free(nextThread);
            InteractionProtocolHandler_Application_DecrementThreadCount(application);
        }
        while (1);
    }
    while (application->listOfThreads != (ApplicationThread*) -1);

    //printf("InteractionProtocolHandler_ThreadShutdown shutdown - application = %p\n", application);

    return 0;
}

MI_Result MI_MAIN_CALL InteractionProtocolHandler_Application_Initialize(MI_Uint32 flags,
    _In_opt_z_ const MI_Char * applicationID,
    _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
    _Out_      MI_Application *miApplication)
{
    InteractionProtocolHandler_Application *application;

    memset(miApplication, 0, sizeof(*miApplication));

    application = PAL_Calloc(1, sizeof(InteractionProtocolHandler_Application));
    if (application == 0)
    {
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    if (applicationID)
    {
        application->applicationID = PAL_Tcsdup(applicationID);
        if (application->applicationID == NULL)
        {
            PAL_Free(application);
            return MI_RESULT_SERVER_LIMITS_EXCEEDED;
        }
    }

    if (Thread_CreateJoinable(&application->safeShutdownThread, InteractionProtocolHandler_ThreadShutdown, NULL, application) != 0)
    {
        if (application->applicationID)
            PAL_Free(application->applicationID);
        PAL_Free(application);
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    miApplication->reserved2 = (ptrdiff_t) application;
    miApplication->ft = &g_interactionProtocolHandler_ApplicationFT;
    memcpy(&application->myMiApplication, miApplication, sizeof(application->myMiApplication));
    if (extendedError)
        *extendedError = NULL;
    return MI_RESULT_OK;
}

MI_Result MI_CALL InteractionProtocolHandler_Application_Close(
        _Inout_     MI_Application *miApplication)
{
    InteractionProtocolHandler_Application *application = (InteractionProtocolHandler_Application *)miApplication->reserved2;
    if (application)
    {
        PAL_Uint32 threadValue;
        ApplicationThread **lastThreadPtr = &application->listOfThreads;
        int didBroadcast = 0;

        /* Wait for all other threads to shutdown. Possible some notification got missed */
        while (Atomic_Read(&application->threadCount))
        {
            //printf("InteractionProtocolHandler_Application_Close - thread count is not zero - application = %p, threadcount=%p, first thread left=%p\n", application, (void*)Atomic_Read(&application->threadCount), (void*)application->listOfThreads);
            Sleep_Milliseconds(100);
            if (didBroadcast == 0)
            {
                /* Only broadcast the first time */
                CondLock_Broadcast((ptrdiff_t) application);
                didBroadcast = 1;
            }
        }

        //printf("InteractionProtocolHandler_Application_Close - Notifying ThreadShutdown to finish - application = %p\n", application);
        Lock_Acquire(&application->listOfThreadsLock);
        while (*lastThreadPtr != 0)
        {
            lastThreadPtr = &(*lastThreadPtr)->next;
        }
        *lastThreadPtr = (ApplicationThread*) -1;
        Lock_Release(&application->listOfThreadsLock);

        CondLock_Broadcast((ptrdiff_t) application);

        //printf("InteractionProtocolHandler_Application_Close - Closing down main shutdown thread - application = %p, threadcount=%p\n", application, (void*)Atomic_Read(&application->threadCount));
        Thread_Join(&application->safeShutdownThread, &threadValue);
        Thread_Destroy(&application->safeShutdownThread);

        //printf("InteractionProtocolHandler_Application_Close - shutdown thread gone - application = %p, threadcount=%p\n", application, (void*)Atomic_Read(&application->threadCount));

        if (application->applicationID)
            PAL_Free(application->applicationID);
        PAL_Free(application);
    }
    memset(miApplication, 0, sizeof(*miApplication));
    return MI_RESULT_OK;
}

MI_Result InteractionProtocolHandler_Application_IncrementThreadCount(
    _In_     InteractionProtocolHandler_Application *application)
{
    //ptrdiff_t a =
    Atomic_Inc(&application->threadCount);
    //printf("InteractionProtocolHandler_Application_IncrementThreadCount - application = %p, new count=%p\n", application, (void*)a);
    return MI_RESULT_OK;
}
MI_Result InteractionProtocolHandler_Application_DecrementThreadCount(
    _In_     InteractionProtocolHandler_Application *application)
{
    //ptrdiff_t a =
    Atomic_Dec(&application->threadCount);
    //printf("InteractionProtocolHandler_Application_DecrementThreadCount - application = %p, new count=%p\n", application, (void*)a);
    return MI_RESULT_OK;
}
MI_Result InteractionProtocolHandler_Application_SafeCloseThread(
    _In_ InteractionProtocolHandler_Application *application,
    _In_ ApplicationThread *operationThread)
{
    //printf("InteractionProtocolHandler_Application_SafeCloseThread - queueing up handle to close - application = %p, thread=%p\n", application, operationThread);
    Lock_Acquire(&application->listOfThreadsLock);
    operationThread->next = application->listOfThreads;
    application->listOfThreads = operationThread;
    Lock_Release(&application->listOfThreadsLock);

    CondLock_Broadcast((ptrdiff_t) application);
    return MI_RESULT_OK;
}

MI_Result MI_CALL InteractionProtocolHandler_Application_NewDestinationOptions(
        _In_     MI_Application *miApplication,
        _Out_    MI_DestinationOptions *options)
{
    return DestinationOptions_Create(miApplication, options);
}

MI_Result MI_CALL InteractionProtocolHandler_Application_NewOperationOptions(
        _In_     MI_Application *miApplication,
        _In_     MI_Boolean customOptionsMustUnderstand,
        _Out_    MI_OperationOptions *options)
{
    return OperationOptions_Create(miApplication, customOptionsMustUnderstand, options);
}

MI_Result MI_CALL InteractionProtocolHandler_Application_NewSubscriptionDeliveryOptions(
        _In_     MI_Application *miApplication,
        _In_     MI_SubscriptionDeliveryType deliveryType,
        _Out_    MI_SubscriptionDeliveryOptions *deliveryOptions)
{
    return SubscriptionDeliveryOptions_Create(miApplication, deliveryType, deliveryOptions);
}

_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL InteractionProtocolHandler_Application_NewHostedProvider(
    _In_  MI_Application *application,
    _In_z_  const MI_Char * namespaceName,
    _In_z_  const MI_Char * providerName,
    _In_  MI_MainFunction mi_Main,
    _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
    _Out_ MI_HostedProvider *hostedProvider)
{
    if ((application == NULL) || (application->ft == NULL) ||
        (application->reserved2 == 0) || (application->reserved1 != 1))
    {
        /* Probably already deleted or failed to initialize */
        return MI_RESULT_INVALID_PARAMETER;
    }

    return MI_RESULT_NOT_SUPPORTED;
}



const MI_ApplicationFT g_interactionProtocolHandler_ApplicationFT =
{
    InteractionProtocolHandler_Application_Close,
    InteractionProtocolHandler_Session_New,
    InteractionProtocolHandler_Application_NewHostedProvider,
    NULL, /* NewInstance, not needed in protocol handler */
    InteractionProtocolHandler_Application_NewDestinationOptions,
    InteractionProtocolHandler_Application_NewOperationOptions,
    InteractionProtocolHandler_Application_NewSubscriptionDeliveryOptions,
    NULL, /* NewSerializer, not needed in protocol handler */
    NULL, /* NewDeserializer, not needed in protocol handler */
    NULL /* NewInstanceFromClass, not needed in protocol handler */
};
