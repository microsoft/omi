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
#include <base/Strand.h>
#include <sock/selector.h>
#include <pal/thread.h>
#include <protocol/header.h>

BEGIN_EXTERNC

#define PROTOCOLSOCKET_STRANDAUX_POSTMSG        0
#define PROTOCOLSOCKET_STRANDAUX_READYTOFINISH  1
#define PROTOCOLSOCKET_STRANDAUX_CONNECTEVENT   2

typedef enum _Protocol_AuthState
{
    /* authentication failed (intentionaly takes value '0')*/
    PRT_AUTH_FAILED,

    /* listener (server) waits for connect request */
    PRT_AUTH_WAIT_CONNECTION_REQUEST,

    /* listener (server) waits for second connect request with random data from file */
    PRT_AUTH_WAIT_CONNECTION_REQUEST_WITH_FILE_DATA,

    /* connector (client) waits for server's response */
    PRT_AUTH_WAIT_CONNECTION_RESPONSE,

    /* authentication completed */
    PRT_AUTH_OK
}
Protocol_AuthState;

typedef enum _Protocol_Type
{
    PRT_TYPE_LISTENER,
    PRT_TYPE_CONNECTOR,
    PRT_TYPE_FROM_SOCKET
}
Protocol_Type;

/* Keeps data for file-based authentication */
typedef struct _Protocol_AuthData
{
    char    path[PAL_MAX_PATH_SIZE];
    char    authRandom[AUTH_RANDOM_DATA_SIZE];
}
Protocol_AuthData;

typedef struct _ProtocolBase
{
    MI_Uint32           magic;                  //TODO: Evaluate if this is still needed after implementing multiplexer
    Selector*           selector;
    Selector            internal_selector;
    MI_Boolean          internal_selector_used;
    Addr                addr;
    OpenCallback        callback;               // Callback for new Interaction (when the connection is opened on listener/agent)
    void*               callbackData;
    Protocol_Type       type;
    /* Indicates whether instance has to be upacked or stored as byte array */
    MI_Boolean          skipInstanceUnpack;
}
ProtocolBase;

typedef struct _ProtocolSocket
{
    /* based member*/
    Handler             base;

    Strand              strand;

    /* currently sending message */
    Message*            message;
    size_t              sentCurrentBlockBytes;
    int                 sendingPageIndex;       /* 0 for header otherwise 1-N page index */

    /* receiving data */
    Batch *             receivingBatch;
    size_t              receivedCurrentBlockBytes;
    int                 receivingPageIndex;     /* 0 for header otherwise 1-N page index */

    /* send/recv buffers */
    Header              recv_buffer;
    Header              send_buffer;

    /* Auth state */
    Protocol_AuthState  authState;
    /* server side - auhtenticated user's ids */
    AuthInfo            authInfo;
    Protocol_AuthData*  authData;

    /* Whether connection has been established */
    MI_Boolean          isConnected;
    volatile ptrdiff_t  connectEventSent;

    volatile ptrdiff_t refCount; //used by socket listner for lifetimemanagement
    MI_Boolean          closeOtherScheduled;
} 
ProtocolSocket;

// Combined with a internal protocol base
// A connector (PRT_TYPE_CONNECTOR) or either side of an agent connection (PRT_TYPE_FROM_SOCKET)
typedef struct _ProtocolSocketAndBase
{
    ProtocolSocket          protocolSocket;
    ProtocolBase            internalProtocolBase;
}
ProtocolSocketAndBase;

MI_Result ProtocolBase_New_Listener(
    _Out_       ProtocolBase** selfOut,
    _In_opt_    Selector* selector, /*optional, maybe NULL*/
    _In_        const char* locator,
    _In_        OpenCallback callback,
    _In_        void* callbackData);

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
MI_Result ProtocolSocketAndBase_New_Connector(
    _Out_       ProtocolSocketAndBase** selfOut,
    _In_opt_    Selector*               selector,       // optional, maybe NULL
    _In_        const char*             locator,
    _In_        InteractionOpenParams*  params,
    _In_        const char*             user,
    _In_        const char*             password );

MI_Result ProtocolSocketAndBase_New_AgentConnector(
    _Out_       ProtocolSocketAndBase** selfOut,
    _In_opt_    Selector*               selector,       // optional, maybe NULL
    _In_        Sock                    s,
    _In_        InteractionOpenParams*  params );

MI_Result ProtocolSocketAndBase_New_Agent(
    _Out_       ProtocolSocketAndBase** selfOut,
    _In_opt_    Selector*               selector,       // optional, maybe NULL
    _In_        Sock                    s,
    _In_        OpenCallback            callback,       
    _In_        void*                   callbackData);  // used along with callback

MI_Result ProtocolBase_Delete(
    ProtocolBase* self);

// Call this once it is out of the selector run loop
MI_INLINE void ProtocolSocketAndBase_ReadyToFinish(
    ProtocolSocketAndBase* self)
{
    Strand_ScheduleAux( &self->protocolSocket.strand, PROTOCOLSOCKET_STRANDAUX_READYTOFINISH );
}

MI_Result Protocol_Run(
    ProtocolBase* self,
    MI_Uint64 timeoutUsec);

END_EXTERNC

#endif /* _omi_protocol_h */
