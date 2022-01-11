/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _miapi_application_h_
#define _miapi_application_h_

#include "SafeHandle.h"
#include "ChildList.h"
#include "ProtocolHandlerCache.h"
#include <MI.h>

/* PUBLIC Application_NewGenericHandle
 * Retrieve a new generic handler.  This is a generic version of MI_Application/MI_Session/etc.
 * To recycle the handler back into the pool do this: 
 *      ThunkHandle_Shutdown(genericHandle->thunkHandle);
 * application - top-level application that the handle will be attached to
 * handle - resultant handler
 *
 * Return code: MI_Result code
 */
MI_Result Application_NewGenericHandle(
    _Inout_ MI_Application *application, 
    _Out_ GenericHandle *handle);

/* PUBLIC: Application_GetProtocolHandler
 * Retrieve the MI_Application of a protocol handler.  If protocol handler
 * is not loaded this function will load it.
 * It is not valid to have destination and protocolHandler NULL.  It needs
 * one to determine which handler to use.
 *
 * application - top-level application that the handler is attached to
 * destination - For local this should be NULL or empty string.  If protocol
 *               handler is NULL it will pick the default for local/remote 
 *               destination.
 * protocolHandler - If specified is the protocol handler string.
 * protocolHandlerApplication - MI_Application for the protocol handler
 *               exposing the function table to the handler.
 *
 * Return code: MI_Result code
 */
_Success_(return == MI_RESULT_OK)
MI_Result Application_GetProtocolHandler(
    _In_ MI_Application *application, 
    _In_opt_z_ const MI_Char *destination, 
    _In_opt_z_ const MI_Char *protocolHandler, 
    _Outptr_ ProtocolHandlerCacheItem **protocolHandlerItem);

MI_Result Application_RegisterSession(_Inout_ MI_Application *application, _Inout_ ChildListNode *session);
MI_Result Application_UnregisterSession(_Inout_ MI_Application *application, _Inout_ ChildListNode *session);

MI_Result Application_RegisterHostedProvider(_Inout_ MI_Application *application, _Inout_ ChildListNode *hostedProvider);
MI_Result Application_UnregisterHostedProvider(_Inout_ MI_Application *application, _Inout_ ChildListNode *hostedProvider);


#define MIAPI_DEFAULT_LOCAL_PROTOCOL 1
#define MIAPI_DEFAULT_REMOTE_PROTOCOL 2

_Success_(return == MI_RESULT_OK)
MI_EXTERN_C MI_Result Application_SetTestTransport(
    _Inout_ MI_Application *clientMiApplication, 
    _In_z_ const char *protocolHandlerName,
    _In_z_ const char *protocolHandlerDLL,
    _In_z_ const char *protocolHandlerDllEntryPoint,
    MI_Uint32 protocolHandlerMajorVersion,
    MI_Uint32 protocolHandlerMinorVersion,
    MI_Boolean overrideDefaultLocalTransport,
    MI_Boolean overrideDefaultRemoteTransport);

#endif /* _miapi_application_h_ */

