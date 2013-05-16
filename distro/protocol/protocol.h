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

#ifndef _omi_protocol_h
#define _omi_protocol_h

#include "config.h"
#include <string.h>
#include <common.h>
#include <base/messages.h>
#include <sock/selector.h>

BEGIN_EXTERNC

typedef struct _Protocol Protocol;

/*
    Callback for processing new message.
    Parameters:
    protocol - pointer to a protocol object that received a message
    message - message; consumer ahs to call 'AddRef' to keep message around
        longer than callback's lifetime
    data - user-provided callback data
    Return:
        normally callbacks should return TRUE (means keep connection open);
        returning FALSE means close connection
*/
typedef MI_Boolean (*ProtocolCallback)(
    Protocol* protocol,
    Message* message,
    void* data);

typedef enum _ProtocolEvent
{
    PROTOCOLEVENT_CONNECT,
    PROTOCOLEVENT_CONNECT_FAILED,
    PROTOCOLEVENT_DISCONNECT
}
ProtocolEvent;

typedef void (*ProtocolEventCallback)(
    Protocol* protocol,
    ProtocolEvent event,
    void* data);

MI_Result Protocol_New_Listener(
    Protocol** self,
    Selector* selector, /*optional, maybe NULL*/
    const char* locator,
    ProtocolCallback callback,
    void* callbackData);

/*
    Creates new protocol object (client side) and
    connect it to the server.

    Parameters:
    self - [out] protocol object
    selector - [opt] selector to use for socket monitoring
    locator - server's address (typically domain socket file name)
    callback - function that protocol calls to inform about new messsages
    callbackData - 
    eventCallback - function that protocl calls to inform about socket states
        connected/disconnected
    user, password [opt] - credentials for explicit auth. If NULL,
        implicit authentication is used

    Returns:
    'OK' if succefful, error otherwise
*/
MI_Result Protocol_New_Connector(
    Protocol** self,
    Selector* selector, /*optional, maybe NULL*/
    const char* locator,
    ProtocolCallback callback,
    void* callbackData,
    ProtocolEventCallback eventCallback,
    void* eventCallbackData,
    const char* user,
    const char* password);

/*
    Creates a new protocol object from connected stream socket
    (typically a pipe from server to agent).

    Parameters:
    self - [out] protocol object
    selector - [opt] selector to use for socket monitoring
    s - socket; if protocol created successfully, socket will be closed in Protocol_Delete.
        If operation failed, socket is not closed.
    skipInstanceUnpack - flag to skip instance un-packing; used 
        to skip unpacking instances from agent
    callback - function that protocol calls to inform about new messsages
    callbackData - 
    eventCallback - function that protocl calls to inform about socket states
        connected/disconnected

    Returns:
    'OK' if succefful, error otherwise
*/
MI_Result Protocol_New_From_Socket(
    Protocol** self,
    Selector* selector, /*optional, maybe NULL*/
    Sock s,
    MI_Boolean skipInstanceUnpack,
    ProtocolCallback callback,
    void* callbackData,
    ProtocolEventCallback eventCallback,
    void* eventCallbackData);

MI_Result Protocol_Delete(
    Protocol* self);

MI_Result Protocol_Run(
    Protocol* self,
    MI_Sint64 timeoutUsec);

MI_Result Protocol_Send(
    Protocol* self,
    Message* message);

END_EXTERNC

#endif /* _omi_protocol_h */
