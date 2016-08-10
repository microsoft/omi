/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _miapi_session_h_
#define _miapi_session_h_

#include <MI.h>
#include "ChildList.h"
#include "ProtocolHandlerCache.h"

/* PUBLIC Session_Create for Application to create a new MI_Session */
_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL Session_Create(
    _In_     MI_Application *application, 
    _In_opt_z_ const MI_Char *protocol,
    _In_opt_z_ const MI_Char *destination,
    _In_opt_ MI_DestinationOptions *options,
    _In_opt_ MI_SessionCallbacks *callbacks,
    _Outptr_opt_result_maybenull_ MI_Instance **extendedError,
    _Out_    MI_Session *session);

_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL Session_Close(
    _In_     MI_Session *session,
    _In_opt_ void *completionContext,
    _In_opt_ void (MI_CALL *completionCallback)(_In_opt_ void *completionContext));

_Success_(return == MI_RESULT_OK)
MI_Result MI_CALL Session_GetApplication(
    _In_     MI_Session *session,
    _Out_    MI_Application *application);

/* From a client session get the protocol handler session */
_Success_(return == MI_RESULT_OK)
MI_Result Session_GetProtocolHandlerSession(_In_ MI_Session *clientSession, _Out_ MI_Session *transportSession, _Out_ ProtocolHandlerCacheItem **protocolHandlerItem);

/* From a client session get the protocol handler application */
_Success_(return == MI_RESULT_OK)
MI_Result Session_GetProtocolHandlerApplication(_In_ MI_Session *clientSession, _Out_ MI_Application *protocolHandlerApplication);

void Session_GetDestinationOptions(_Inout_ MI_Session *session, _Out_ MI_DestinationOptions *destOptions);


/* Register client operation with session */
_Success_(return == MI_RESULT_OK)
MI_Result Session_RegisterOperation(_Inout_ MI_Session *session, _Inout_ ChildListNode *newOperaton);

/* UnRegister client operation from session */
_Success_(return == MI_RESULT_OK)
MI_Result Session_UnregisterOperation(_Inout_ ThunkHandle *thunkHandle, _Inout_ ChildListNode *removeOperaton);

void Session_CancelAllOperations(_Inout_ MI_Session *session);

_Success_(return == MI_RESULT_OK)
MI_Result Session_AccessCheck(_In_ MI_Session *session, _In_opt_z_ const MI_Char *operationName);

_Success_(return == MI_RESULT_OK)
MI_Result Session_ImpersonateClient(_In_ MI_Session *session, _Out_ MI_CLIENT_IMPERSONATION_TOKEN *originalImpersonation);
_Success_(return == MI_RESULT_OK)
MI_Result Session_RevertImpersonation(MI_CLIENT_IMPERSONATION_TOKEN originalImpersonation);

#endif /* _miapi_session_h_ */

