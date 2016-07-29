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

#ifndef _mi_client_h
#define _mi_client_h

#include <micxx/micxx.h>
#include "linkage.h"
#include "handler.h"
#include "protocol/protocol.h"

MI_BEGIN_NAMESPACE

class ClientRep;

class OMICLIENT_LINKAGE Client
{
public:

    Client(Handler* handler = 0);

    ~Client();

    bool ConnectAsync(
        const String& locator,
        const String& user,
        const String& password);

    bool Connect(
        const String& locator, 
        const String& user,
        const String& password,
        Uint64 timeOutUsec);

    bool Disconnect();

    bool Connected() const;

    bool Run(Uint64 timeOutUsec);

    bool NoOpAsync(
        Uint64& operationId);

    bool SwitchProtocolAsync(
        Uint64& operationId);

    bool GetInstanceAsync(
        const String& nameSpace,
        const DInstance& instanceName,
        Uint64& operationId);

    bool CreateInstanceAsync(
        const String& nameSpace,
        const DInstance& instance,
        Uint64& operationId);

    bool ModifyInstanceAsync(
        const String& nameSpace,
        const DInstance& instance,
        Uint64& operationId);

    bool DeleteInstanceAsync(
        const String& nameSpace,
        const DInstance& instanceName,
        Uint64& operationId);

    bool EnumerateInstancesAsync(
        const String& nameSpace,
        const String& className,
        bool deepInheritance,
        const String& queryLanguage,
        const String& queryExpression,
        Uint64& operationId);

    bool InvokeAsync(
        const String& nameSpace,
        const DInstance& instanceName,
        const String& methodName,
        const DInstance& inParameters,
        DInstance& outParameters,
        Uint64 operationId);

    bool AssociatorInstancesAsync(
        const String& nameSpace,
        const DInstance& instanceName,
        const String& assocClass,
        const String& resultClass,
        const String& role,
        const String& resultRole,
        Uint64& operationId);

    bool ReferenceInstancesAsync(
        const String& nameSpace,
        const DInstance& instanceName,
        const String& resultClass,
        const String& role,
        Uint64& operationId);

    bool NoOp(Uint64 timeOutUsec);

    bool SwitchProtocol(Uint64 timeOutUsec);

    bool GetInstance(
        const String& nameSpace,
        const DInstance& instanceName,
        Uint64 timeOutUsec,
        DInstance& instance,
        Result& result);

    bool CreateInstance(
        const String& nameSpace,
        const DInstance& instance,
        Uint64 timeOutUsec,
        DInstance& instanceName,
        Result& result);

    bool ModifyInstance(
        const String& nameSpace,
        const DInstance& instance,
        Uint64 timeOutUsec,
        Result& result);

    bool DeleteInstance(
        const String& nameSpace,
        const DInstance& instanceName,
        Uint64 timeOutUsec,
        Result& result);

    bool EnumerateInstances(
        const String& nameSpace,
        const String& className,
        bool deepInheritance,
        Uint64 timeOutUsec,
        Array<DInstance>& instances,
        const String& queryLanguage,
        const String& queryExpression,
        Result& result);

    bool Invoke(
        const String& nameSpace,
        const DInstance& instanceName,
        const String& methodName,
        const DInstance& inParameters,
        Uint64 timeOutUsec,
        DInstance& outParameters,
        Result& result);

    bool AssociatorInstances(
        const String& nameSpace,
        const DInstance& instanceName,
        const String& assocClass,
        const String& resultClass,
        const String& role,
        const String& resultRole,
        Uint64 timeOutUsec,
        Array<DInstance>& instances,
        Result& result);

    bool ReferenceInstances(
        const String& nameSpace,
        const DInstance& instanceName,
        const String& resultClass,
        const String& role,
        Uint64 timeOutUsec,
        Array<DInstance>& instances,
        Result& result);

    inline ClientRep* GetClientRep( void ) { return m_rep; }

private:
    Client(const Client&);
    Client& operator=(const Client&);
    ClientRep* m_rep;
};

//==============================================================================
//
// class ClientRep
//
//==============================================================================

class ClientRep
{
public:
    enum ConnectState
    {
        CONNECTSTATE_PENDING,
        CONNECTSTATE_FAILED,
        CONNECTSTATE_CONNECTED,
        CONNECTSTATE_DISCONNECTED
    };

    ProtocolSocketAndBase* protocol;
    Strand strand;  // To manage interaction with ProtocolSocket
    Handler* handler;
    ConnectState connectState;

    static void MessageCallback(
        ClientRep * rep,
        Message* msg);

    bool NoOpAsync(
        Uint64 operationId);

    bool SwitchProtocolAsync(
        Uint64 operationId);

    bool GetInstanceAsync(
        const String& nameSpace,
        const DInstance& instanceName,
        Uint64 operationId);

    bool CreateInstanceAsync(
        const String& nameSpace,
        const DInstance& instance,
        Uint64 operationId);

    bool ModifyInstanceAsync(
        const String& nameSpace,
        const DInstance& instance,
        Uint64 operationId);

    bool DeleteInstanceAsync(
        const String& nameSpace,
        const DInstance& instanceName,
        Uint64 operationId);

    bool EnumerateInstancesAsync(
        const String& nameSpace,
        const String& className,
        bool deepInheritance,
        const String& queryLanguage,
        const String& queryExpression,
        Uint64 operationId);

    bool InvokeAsync(
        const String& nameSpace,
        const DInstance& instanceName,
        const String& methodName,
        const DInstance& inParameters,
        DInstance& outParameters,
        Uint64 operationId);

    bool AssociatorInstancesAsync(
        const String& nameSpace,
        const DInstance& instanceName,
        const String& assocClass,
        const String& resultClass,
        const String& role,
        const String& resultRole,
        Uint64& operationId);

    bool ReferenceInstancesAsync(
        const String& nameSpace,
        const DInstance& instanceName,
        const String& resultClass,
        const String& role,
        Uint64& operationId);
};

MI_END_NAMESPACE

#endif /* _mi_client_h */
