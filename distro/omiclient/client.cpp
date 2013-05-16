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

#include "client.h"
#include <base/packing.h>
#include <protocol/protocol.h>
#include <base/time.h>
#include <base/paths.h>
#include "thread.h"

// #define ENABLE_TRACING
// #define TRACING_LEVEL 4
#include <logging.h>

MI_BEGIN_NAMESPACE

//==============================================================================
//
// Local definitions.
//
//==============================================================================

Uint64 _NextMsgID()
{
    static Mutex mutex;
    mutex.Lock();
    static Uint64 _msgID = 10000;
    Uint64 x = _msgID++;
    mutex.Unlock();

    return x;
}

static char* _StringToStr(const String& str)
{
    Uint32 n = str.GetSize();
    char* r = new char[n + 1];

    if (!r)
        return NULL;

    for (Uint32 i = 0; i < n; i++)
    {
        r[i] = char(str[i]);
    }

    r[n] = '\0';

    return r;
}

static String _StrToString(const char* str)
{
    String r;

    while (str)
    {
        MI_Char c = *str++;
        r.Append(&c, 1);
    }

    return r;
}

//==============================================================================
//
// class EnvelopeHandler
//
//==============================================================================

class EnvelopeHandler : public Handler
{
public:

    EnvelopeHandler(Handler* handler) : m_handler(handler)
    {
    }

    virtual void HandleConnect()
    {
        if (m_handler)
            m_handler->HandleConnect();
    }

    virtual void HandleConnectFailed()
    {
        if (m_handler)
            m_handler->HandleConnectFailed();
    }

    virtual void HandleDisconnect()
    {
        if (m_handler)
            m_handler->HandleDisconnect();
    }

    virtual void HandleNoOp(Uint64 msgID)
    {
        if (m_handler)
            m_handler->HandleNoOp(msgID);
    }

    virtual void HandleInstance(Uint64 msgID, const DInstance& instance)
    {
        if (m_handler)
            m_handler->HandleInstance(msgID, instance);
    }

    virtual void HandleResult(Uint64 msgID, MI_Result result)
    {
        if (m_handler)
            m_handler->HandleResult(msgID, result);
    }

    virtual void HandleResult(Uint64 msgID, MI_Result result, const MI_Char *error, const DInstance* cimError)
    {
        if (m_handler)
            m_handler->HandleResult(msgID, result, error, cimError);
    }

private:
    Handler* m_handler;
};

//==============================================================================
//
// class NoOpHandler
//
//==============================================================================

class NoOpHandler : public EnvelopeHandler
{
public:

    enum State { START, DONE, FAILED };

    NoOpHandler(Handler* handler, Uint64 msgID) :
        EnvelopeHandler(handler), m_state(START), m_msgID(msgID)
    {
    }

    virtual void HandleNoOp(Uint64 msgID)
    {
        if (msgID != m_msgID)
        {
            EnvelopeHandler::HandleNoOp(msgID);
            return;
        }

        if (m_state != START)
        {
            m_state = FAILED;
            return;
        }

        m_state = DONE;
    }

    State m_state;
    Uint64 m_msgID;
};

//==============================================================================
//
// class ResultHandler
//
//==============================================================================

class ResultHandler : public EnvelopeHandler
{
public:

    enum State { START, DONE, FAILED };

    ResultHandler(Handler* handler, Uint64 msgID) :
        EnvelopeHandler(handler),
        m_state(START),
        m_msgID(msgID),
        m_result(MI_RESULT_OK),
        m_cimerror(NULL),
        m_errorMessage(NULL)
    {
    }

    virtual void HandleResult(Uint64 msgID, Result result)
    {
        if (msgID != m_msgID)
        {
            EnvelopeHandler::HandleResult(msgID, result);
            return;
        }

        if (m_state != START)
        {
            LOGE2((ZT("ResultHandler::HandleResult - state not START")));
            m_state = FAILED;
            return;
        }

        m_result = result;
        m_state = DONE;
    }

    virtual void HandleResult(Uint64 msgID, MI_Result result, const MI_Char *error, const DInstance* cimError)
    {
        if (msgID != m_msgID)
        {
            EnvelopeHandler::HandleResult(msgID, result, error, cimError);
            return;
        }

        if (m_state != START)
        {
            LOGE2((ZT("ResultHandler::HandleResult - state not START")));
            m_state = FAILED;
            return;
        }

        m_result = result;
        m_cimerror = cimError;
        m_errorMessage = error;
        m_state = DONE;
    }

    State m_state;
    Uint64 m_msgID;
    Result m_result;
    const DInstance* m_cimerror;
    const MI_Char *m_errorMessage;
};

//==============================================================================
//
// class InstanceHandler
//
//==============================================================================

class InstanceHandler : public EnvelopeHandler
{
public:

    enum State { INSTANCE, RESULT, DONE, FAILED };

    InstanceHandler(
        Handler* handler,
        Uint64 msgID,
        DInstance& instance)
        :
        EnvelopeHandler(handler),
        m_state(INSTANCE),
        m_msgID(msgID),
        m_instance(instance),
        m_result(MI_RESULT_OK),
        m_errorMessage(NULL),
        m_cimerror(NULL)
    {
    }

    virtual void HandleInstance(Uint64 msgID, const DInstance& instance)
    {
        if (msgID != m_msgID)
        {
            EnvelopeHandler::HandleInstance(msgID, instance);
            return;
        }

        if (m_state != INSTANCE)
        {
            LOGE2((ZT("InstanceHandler::HandleResult - state not INSTANCE")));
            m_state = FAILED;
            return;
        }

        m_instance = instance;
        m_state = RESULT;
    }

    virtual void HandleResult(Uint64 msgID, Result result)
    {
        if (msgID != m_msgID)
        {
            EnvelopeHandler::HandleResult(msgID, result);
            return;
        }

        if (m_state != INSTANCE && m_state != RESULT)
        {
            LOGE2((ZT("InstanceHandler::HandleResult - state not INSTANCE or RESULT")));
            m_state = FAILED;
            return;
        }

        m_result = result;
        m_state = DONE;
    }

    virtual void HandleResult(Uint64 msgID, MI_Result result, const MI_Char *error, const DInstance* cimError)
    {
        if (msgID != m_msgID)
        {
            EnvelopeHandler::HandleResult(msgID, result, error, cimError);
            return;
        }

        if (m_state != INSTANCE && m_state != RESULT)
        {
            LOGE2((ZT("InstanceHandler::HandleResult - state RESULT")));
            m_state = FAILED;
            return;
        }

        m_result = result;
        m_cimerror = cimError;
        m_errorMessage = error;
        m_state = DONE;
    }

    State m_state;
    Uint64 m_msgID;
    DInstance& m_instance;
    Result m_result;
    const MI_Char *m_errorMessage;
    const DInstance* m_cimerror;
};

//==============================================================================
//
// class InstancesHandler
//
//==============================================================================

class InstancesHandler : public EnvelopeHandler
{
public:

    enum State { INSTANCES, RESULT, DONE, FAILED };

    InstancesHandler(
        Handler* handler,
        Uint64 msgID,
        Array<DInstance>& instances)
        :
        EnvelopeHandler(handler),
        m_state(INSTANCES),
        m_msgID(msgID),
        m_instances(instances),
        m_result(MI_RESULT_OK)
    {
    }

    virtual void HandleInstance(Uint64 msgID, const DInstance& instance)
    {
        if (msgID != m_msgID)
        {
            EnvelopeHandler::HandleInstance(msgID, instance);
            return;
        }

        if (m_state != INSTANCES)
        {
            LOGE2((ZT("InstancesHandler::HandleInstance - state not INSTANCES")));
            m_state = FAILED;
            return;
        }

        m_instances.PushBack(instance);
    }

    virtual void HandleResult(Uint64 msgID, Result result)
    {
        if (msgID != m_msgID)
        {
            EnvelopeHandler::HandleResult(msgID, result);
            return;
        }

        if (m_state != INSTANCES)
        {
            LOGE2((ZT("InstancesHandler::HandleResult - state not INSTANCES")));
            m_state = FAILED;
            return;
        }

        m_result = result;
        m_state = DONE;
    }

    virtual void HandleResult(Uint64 msgID, Result result, const MI_Char *error, const DInstance* cimError)
    {
        if (msgID != m_msgID)
        {
            EnvelopeHandler::HandleResult(msgID, result);
            return;
        }

        if (m_state != INSTANCES)
        {
            LOGE2((ZT("InstancesHandler::HandleResult - state not INSTANCES")));
            m_state = FAILED;
            return;
        }

        m_result = result;
        m_state = DONE;
    }

    State m_state;
    Uint64 m_msgID;
    Array<DInstance>& m_instances;
    Result m_result;
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

    Protocol* protocol;
    Handler* handler;
    ConnectState connectState;

    static void EventCallback(
        Protocol* protocol,
        ProtocolEvent event,
        void* data);

    static MI_Boolean MessageCallback(
        Protocol* protocol,
        Message* msg,
        void* data);

    bool NoOpAsync(
        Uint64 msgID);

    bool GetInstanceAsync(
        const String& nameSpace,
        const DInstance& instanceName,
        Uint64 msgID);

    bool CreateInstanceAsync(
        const String& nameSpace,
        const DInstance& instance,
        Uint64 msgID);

    bool ModifyInstanceAsync(
        const String& nameSpace,
        const DInstance& instance,
        Uint64 msgID);

    bool DeleteInstanceAsync(
        const String& nameSpace,
        const DInstance& instanceName,
        Uint64 msgID);

    bool EnumerateInstancesAsync(
        const String& nameSpace,
        const String& className,
        bool deepInheritance,
        const String& queryLanguage,
        const String& queryExpression,
        Uint64 msgID);

    bool InvokeAsync(
        const String& nameSpace,
        const DInstance& instanceName,
        const String& methodName,
        const DInstance& inParameters,
        DInstance& outParameters,
        Uint64 msgID);

    bool AssociatorInstancesAsync(
        const String& nameSpace,
        const DInstance& instanceName,
        const String& assocClass,
        const String& resultClass,
        const String& role,
        const String& resultRole,
        Uint64& msgID);

    bool ReferenceInstancesAsync(
        const String& nameSpace,
        const DInstance& instanceName,
        const String& assocClass,
        const String& role,
        Uint64& msgID);
};

void ClientRep::EventCallback(
    Protocol* protocol,
    ProtocolEvent event,
    void* data)
{
    ClientRep* clientRep = (ClientRep*)data;
    Handler* handler = clientRep->handler;

    LOGD2((ZT("ClientRep::EventCallback - Begin")));

    if (event == PROTOCOLEVENT_CONNECT)
    {
        LOGD2((ZT("ClientRep::EventCallback - PROTOCOLEVENT_CONNECT")));
        clientRep->connectState = ClientRep::CONNECTSTATE_CONNECTED;
        if (handler)
            handler->HandleConnect();
        return;
    }

    if (event == PROTOCOLEVENT_CONNECT_FAILED)
    {
        LOGD2((ZT("ClientRep::EventCallback - PROTOCOLEVENT_CONNECT_FAILED")));
        if (handler)
            handler->HandleConnectFailed();
        clientRep->connectState = ClientRep::CONNECTSTATE_FAILED;
        return;
    }

    if (event == PROTOCOLEVENT_DISCONNECT)
    {
        LOGD2((ZT("ClientRep::EventCallback - PROTOCOLEVENT_DISCONNECT")));
        if (handler)
            handler->HandleDisconnect();
        clientRep->connectState = ClientRep::CONNECTSTATE_DISCONNECTED;
        return;
    }
}

MI_Boolean ClientRep::MessageCallback(
    Protocol* protocol,
    Message* msg,
    void* data)
{
    ClientRep* clientRep = (ClientRep*)data;
    Handler* handler = clientRep->handler;

    DEBUG_ASSERT(msg != NULL);

    switch (msg->tag)
    {
        case NoOpRspTag:
        {
            NoOpRsp* rsp = (NoOpRsp*)msg;
            LOGD2((ZT("ClientRep::MessageCallback - NoOpRspTag")));
            if (handler != NULL)
                handler->HandleNoOp(rsp->base.msgID);
            break;
        }
        case PostInstanceMsgTag:
        {
            PostInstanceMsg* rsp = (PostInstanceMsg*)msg;
            LOGD2((ZT("ClientRep::MessageCallback - PostInstanceMsgTag")));

            if (rsp->instance)
            {
                DInstance di(rsp->instance, DInstance::CLONE);
                if (handler != NULL)
                    handler->HandleInstance(rsp->base.msgID, di);
            }

            break;
        }
        case SubscribeResTag:
        {
//          SubscribeRes* rsp = (SubscribeRes*)msg;
            LOGD2((ZT("ClientRep::MessageCallback - SubscribeResTag")));
            break;
        }
        case PostResultMsgTag:
        {
            PostResultMsg* rsp = (PostResultMsg*)msg;
            LOGD2((ZT("ClientRep::MessageCallback - PostResultMsgTag. CIM error? %d, result: %d (%s)"), rsp->cimError != NULL, rsp->result, mistrerror(rsp->result)));
            if (handler != NULL)
            {
                if (rsp->cimError != NULL)
                {
                    DInstance di((MI_Instance*)(rsp->cimError), DInstance::CLONE);
                    handler->HandleResult(rsp->base.msgID, rsp->result, rsp->errorMessage, &di);
                }
                else
                {
                    handler->HandleResult(rsp->base.msgID, rsp->result, rsp->errorMessage, NULL);
                }
            }
            break;
        }
        default:
        {
            LOGD2((ZT("ClientRep::MessageCallback - Default")));
            break;
        }
    }
    return MI_TRUE;
}

bool ClientRep::NoOpAsync(
    Uint64 msgID)
{
    NoOpReq* req = NULL;
    bool result = true;

    // Fail if not connected:
    if (!protocol)
    {
        result = false;
        goto done;
    }

    // Create request message:
    {
        req = NoOpReq_New(msgID);

        if (!req)
        {
            LOGE2((ZT("ClientRep::NoOpAsync - failed to create NOOP request message")));
            result = false;
            goto done;
        }
    }

    // Send the message:
    {
        Result r = Protocol_Send(protocol, &req->base);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("ClientRep::NoOpAsync - Protocol_Send failed with result: %d (%s)"), r, mistrerror(r)));
            result = false;
            goto done;
        }
    }

done:

    if (req)
        NoOpReq_Release(req);

    return result;
}

bool ClientRep::GetInstanceAsync(
    const String& nameSpace,
    const DInstance& instanceName,
    Uint64 msgID)
{
    GetInstanceReq* req = NULL;
    bool result = true;

    // Fail if not connected.
    if (!protocol)
    {
        result = false;
        goto done;
    }

    // Create the request message:
    {
        req = GetInstanceReq_New(msgID, BinaryProtocolFlag);

        if (!req)
        {
            LOGE2((ZT("ClientRep::GetInstanceAsync - GetInstanceReq_New failed")));
            result = false;
            goto done;
        }
    }

    // Set nameSpace:
    req->nameSpace = Batch_Zdup(req->base.batch, nameSpace.Str());
    if (!req->nameSpace)
    {
        result = false;
        goto done;
    }

    // Pack the instance name into the message's batch.
    {
        Result r = InstanceToBatch(
            instanceName.m_self,
            NULL,
            NULL,
            req->base.batch,
            &req->packedInstanceNamePtr,
            &req->packedInstanceNameSize);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("ClientRep::GetInstanceAsync - InstanceToBatch failed with result: %d (%s)"), r, mistrerror(r)));
            result = false;
            goto done;
        }
    }

    // Send the messages:
    {
        Result r = Protocol_Send(protocol, &req->base);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("ClientRep::GetInstanceAsync - Protocol_Send failed with result: %d (%s)"), r, mistrerror(r)));
            result = false;
            goto done;
        }
    }

done:
    if (req)
        GetInstanceReq_Release(req);

    return result;
}

bool ClientRep::CreateInstanceAsync(
    const String& nameSpace,
    const DInstance& instance,
    Uint64 msgID)
{
    CreateInstanceReq* req = NULL;
    bool result = true;

    // Fail if not connected.
    if (protocol == NULL)
    {
        LOGE2((ZT("ClientRep::CreateInstanceAsync - not connected")));
        result = false;
        goto done;
    }

    // Create the request message:
    {
        req = CreateInstanceReq_New(msgID, BinaryProtocolFlag);

        if (!req)
        {
            LOGE2((ZT("ClientRep::CreateInstanceAsync failed")));
            result = false;
            goto done;
        }
    }

    // Set nameSpace:
    req->nameSpace = Batch_Zdup(req->base.batch, nameSpace.Str());
    if (!req->nameSpace)
    {
        result = false;
        goto done;
    }

    // Pack the instance name into the message's batch.
    {
        Result r = InstanceToBatch(
            instance.m_self,
            NULL,
            NULL,
            req->base.batch,
            &req->packedInstancePtr,
            &req->packedInstanceSize);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("ClientRep::CreateInstanceAsync - InstanceToBatch failed with error: %d (%s)"), (int)r, mistrerror(r)));
            result = false;
            goto done;
        }
    }

    // Send the messages:
    {
        Result r = Protocol_Send(protocol, &req->base);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("ClientRep::CreateInstanceAsync - ProtocolSend failed with error: %d (%s)"), (int)r, mistrerror(r)));
            result = false;
            goto done;
        }
    }

done:
    if (req)
        CreateInstanceReq_Release(req);

    return result;
}

bool ClientRep::ModifyInstanceAsync(
    const String& nameSpace,
    const DInstance& instance,
    Uint64 msgID)
{
    ModifyInstanceReq* req = 0;
    bool result = true;

    // Fail if not connected.
    if (!protocol)
    {
        result = false;
        goto done;
    }

    // Create the request message:
    {
        req = ModifyInstanceReq_New(msgID, BinaryProtocolFlag);

        if (!req)
        {
            LOGE2((ZT("ClientRep::ModifyInstanceAsync - ModifyInstanceReq_New failed")));
            result = false;
            goto done;
        }
    }

    // Set nameSpace:
    req->nameSpace = Batch_Zdup(req->base.batch, nameSpace.Str());
    if (!req->nameSpace)
    {
        result = false;
        goto done;
    }

    // Pack the instance name into the message's batch.
    {
        Result r = InstanceToBatch(
            instance.m_self,
            NULL,
            NULL,
            req->base.batch,
            &req->packedInstancePtr,
            &req->packedInstanceSize);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("ClientRep::ModifyInstanceAsync - InstanceToBatch failed with error: %d (%s)"), (int)r, mistrerror(r)));
            result = false;
            goto done;
        }
    }

    // Send the messages:
    {
        Result r = Protocol_Send(protocol, &req->base);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("ClientRep::ModifyInstanceAsync - Protocol_Send failed with error: %d (%s)"), (int)r, mistrerror(r)));
            result = false;
            goto done;
        }
    }

done:
    if (req)
        ModifyInstanceReq_Release(req);

    return result;
}

bool ClientRep::DeleteInstanceAsync(
    const String& nameSpace,
    const DInstance& instanceName,
    Uint64 msgID)
{
    DeleteInstanceReq* req = 0;
    bool result = true;

    // Fail if not connected.
    if (!protocol)
    {
        result = false;
        goto done;
    }

    // Create the request message:
    {
        req = DeleteInstanceReq_New(msgID, BinaryProtocolFlag);

        if (!req)
        {
            LOGE2((ZT("ClientRep::DeleteInstanceAsync - DeleteInstanceReq_New failed")));
            result = false;
            goto done;
        }
    }

    // Set nameSpace:
    req->nameSpace = Batch_Zdup(req->base.batch, nameSpace.Str());
    if (!req->nameSpace)
    {
        result = false;
        goto done;
    }

    // Pack the instance name into the message's batch.
    {
        Result r = InstanceToBatch(
            instanceName.m_self,
            NULL,
            NULL,
            req->base.batch,
            &req->packedInstanceNamePtr,
            &req->packedInstanceNameSize);

        if (r != MI_RESULT_OK)
        {
            result = false;
            goto done;
        }
    }

    // Send the messages:
    {
        Result r = Protocol_Send(protocol, &req->base);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("ClientRep::DeleteInstance_Async - Protocol_Send failed with error: %d (%s)"), (int)r, mistrerror(r)));
            result = false;
            goto done;
        }
    }

done:
    if (req)
        DeleteInstanceReq_Release(req);

    return result;
}

bool ClientRep::EnumerateInstancesAsync(
    const String& nameSpace,
    const String& className,
    bool deepInheritance,
    const String& queryLanguage,
    const String& queryExpression,
    Uint64 msgID)
{
    EnumerateInstancesReq* req = NULL;
    bool result = true;

    // Fail if not connected.
    if (!protocol)
    {
        result = false;
        goto done;
    }

    // Create the request message:
    {
        req = EnumerateInstancesReq_New(msgID, BinaryProtocolFlag);

        if (!req)
        {
            LOGE2((ZT("ClientRep::EnumerateInstanceAsync - EnumerateInstanceReq_New failed")));
            result = false;
            goto done;
        }
    }

    // Populate the fields of the request message:
    {
        req->nameSpace = Batch_Zdup(req->base.batch, nameSpace.Str());
        req->className = Batch_Zdup(req->base.batch, className.Str());

        if (!req->nameSpace || !req->className)
        {
            result = false;
            goto done;
        }

        if (queryLanguage.GetSize())
        {
            req->queryLanguage =
                Batch_Zdup(req->base.batch, queryLanguage.Str());
            if (!req->queryLanguage)
            {
                result = false;
                goto done;
            }
        }

        if (queryExpression.GetSize())
        {
            req->queryExpression =
                Batch_Zdup(req->base.batch, queryExpression.Str());
            if (!req->queryExpression)
            {
                result = false;
                goto done;
            }
        }

        req->deepInheritance = deepInheritance;
    }

    // Send the messages:
    {
        Result r = Protocol_Send(protocol, &req->base);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("ClientRep::EnumerateInstanceAsync - Protocol_Send failed with error: %d (%s)"), (int)r, mistrerror(r)));
            result = false;
            goto done;
        }
    }

done:
    if (req)
        EnumerateInstancesReq_Release(req);

    return result;
}

bool ClientRep::InvokeAsync(
    const String& nameSpace,
    const DInstance& instanceName,
    const String& methodName,
    const DInstance& inParameters,
    DInstance& outParameters,
    Uint64 msgID)
{
    InvokeReq* req = 0;
    bool result = true;

    // Fail if not connected.
    if (!protocol)
    {
        result = false;
        goto done;
    }

    // Create the request message:
    {
        req = InvokeReq_New(msgID, BinaryProtocolFlag);

        if (!req)
        {
            LOGE2((ZT("ClientRep::InvokeQsync - InvokeReq_New failed")));
            result = false;
            goto done;
        }
    }

    // Set nameSpace:
    req->nameSpace = Batch_Zdup(req->base.batch, nameSpace.Str());
    if (!req->nameSpace)
    {
        LOGE2((ZT("ClientRep::InvokeAsync - Batch_Zdup for name space failed")));
        result = false;
        goto done;
    }

    // Set className:
    req->className = Batch_Zdup(req->base.batch, instanceName.GetClassName().Str());
    if (!req->className)
    {
        LOGE2((ZT("ClientRep::InvokeAsync - Batch_Zdup for class name failed")));
        result = false;
        goto done;
    }

    // Set methodName:
    req->function = Batch_Zdup(req->base.batch, methodName.Str());
    if (!req->function)
    {
        LOGE2((ZT("ClientRep::InvokeAsync - Batch_Zdup for method name failed")));
        result = false;
        goto done;
    }

    // Pack instanceName:
    if (instanceName.Count())
    {
        Result r = InstanceToBatch(
            instanceName.m_self,
            NULL,
            NULL,
            req->base.batch,
            &req->packedInstancePtr,
            &req->packedInstanceSize);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("ClientRep::InvokeAsync - InstanceToBatch for instance name failed")));
            result = false;
            goto done;
        }
    }

    // Pack inParameters:
    {
        Result r = InstanceToBatch(
            inParameters.m_self,
            NULL,
            NULL,
            req->base.batch,
            &req->packedInstanceParamsPtr,
            &req->packedInstanceParamsSize);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("ClientRep::InvokeAsync - InstanceToBatch of parameters failed")));
            result = false;
            goto done;
        }
    }

    // Send the messages:
    {
        Result r = Protocol_Send(protocol, &req->base);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("ClientRep::InvokeAsync - Protocol_Send failed. name space: %s, class: %s, instance: %s"), nameSpace.Str(), instanceName.GetClassName().Str(), methodName.Str()));
            result = false;
            goto done;
        }
    }

done:
    if (req)
        InvokeReq_Release(req);

    return result;
}

bool ClientRep::AssociatorInstancesAsync(
    const String& nameSpace,
    const DInstance& instanceName,
    const String& assocClass,
    const String& resultClass,
    const String& role,
    const String& resultRole,
    Uint64& msgID)
{
    AssociationsOfReq* req = NULL;
    bool result = true;

    // Fail if not connected.
    if (!protocol)
    {
        result = false;
        goto done;
    }

    // Create the request message:
    {
        req = AssociationsOfReq_New(msgID, BinaryProtocolFlag, AssociatorsOfReqTag);

        if (!req)
        {
            result = false;
            goto done;
        }
    }

    // Set nameSpace:
    req->nameSpace = Batch_Zdup(req->base.batch, nameSpace.Str());
    if (!req->nameSpace)
    {
        result = false;
        goto done;
    }

    // Set assocClass:
    if (assocClass.GetSize())
    {
        req->assocClass = Batch_Zdup(req->base.batch, assocClass.Str());
        if (!req->assocClass)
        {
            result = false;
            goto done;
        }
    }

    // Set resultClass:
    if (resultClass.GetSize())
    {
        req->resultClass = Batch_Zdup(req->base.batch,resultClass.Str());
        if (!req->resultClass)
        {
            result = false;
            goto done;
        }
    }

    // Set role:
    if (role.GetSize())
    {
        req->role = Batch_Zdup(req->base.batch, role.Str());
        if (!req->role)
        {
            result = false;
            goto done;
        }
    }

    // Set resultRole:
    if (resultRole.GetSize())
    {
        req->resultRole = Batch_Zdup(req->base.batch, resultRole.Str());
        if (!req->resultRole)
        {
            result = false;
            goto done;
        }
    }

    // Pack the instance name into the message's batch.
    {
        Result r = InstanceToBatch(
            instanceName.m_self,
            NULL,
            NULL,
            req->base.batch,
            &req->packedInstancePtr,
            &req->packedInstanceSize);

        if (r != MI_RESULT_OK)
        {
            result = false;
            goto done;
        }
    }

    // Send the messages:
    {
        Result r = Protocol_Send(protocol, &req->base);

        if (r != MI_RESULT_OK)
        {
            result = false;
            goto done;
        }
    }

done:
    if (req)
    {
        AssociationsOfReq_Release(req);
    }

    return result;
}

bool ClientRep::ReferenceInstancesAsync(
    const String& nameSpace,
    const DInstance& instanceName,
    const String& assocClass,
    const String& role,
    Uint64& msgID)
{
    AssociationsOfReq* req = NULL;
    bool result = true;

    // Fail if not connected.
    if (!protocol)
    {
        result = false;
        goto done;
    }

    // Create the request message:
    {
        req = AssociationsOfReq_New(msgID, BinaryProtocolFlag, ReferencesOfReqTag);

        if (!req)
        {
            result = false;
            goto done;
        }
    }

    // Set nameSpace:
    req->nameSpace = Batch_Zdup(req->base.batch, nameSpace.Str());
    if (!req->nameSpace)
    {
        result = false;
        goto done;
    }

    // Set assocClass:
    if (assocClass.GetSize())
    {
        req->assocClass = Batch_Zdup(req->base.batch, assocClass.Str());
        if (!req->assocClass)
        {
            result = false;
            goto done;
        }
    }

    // Set role:
    if (role.GetSize())
    {
        req->role = Batch_Zdup(req->base.batch, role.Str());
        if (!req->role)
        {
            result = false;
            goto done;
        }
    }

    // Pack the instance name into the message's batch.
    {
        Result r = InstanceToBatch(
            instanceName.m_self,
            NULL,
            NULL,
            req->base.batch,
            &req->packedInstancePtr,
            &req->packedInstanceSize);

        if (r != MI_RESULT_OK)
        {
            result = false;
            goto done;
        }
    }

    // Send the messages:
    {
        Result r = Protocol_Send(protocol, &req->base);

        if (r != MI_RESULT_OK)
        {
            result = false;
            goto done;
        }
    }

done:
    if (req)
        AssociationsOfReq_Release(req);

    return result;
}

//==============================================================================
//
// class Client
//
//==============================================================================

Client::Client(Handler* handler)
{
    LOGD2((ZT("Client::Client - Begin")));
    m_rep = new ClientRep;
    m_rep->protocol = 0;
    m_rep->connectState = ClientRep::CONNECTSTATE_DISCONNECTED;
    m_rep->handler = handler;
}

Client::~Client()
{
    Disconnect();
    delete m_rep->handler;
    delete m_rep;
}

bool Client::ConnectAsync(
    const String& locatorIn,
    const String& user,
    const String& password)
{
    Result r;
    bool result = true;
    String locator = locatorIn;
    char* locator_ = NULL;
    char* user_ = NULL;
    char* password_ = NULL;

    LOGD2((ZT("Client::ConnectAsync - Begin. locator: %s"), locatorIn.Str()));

    // Fail if already connected:
    if (m_rep->protocol != NULL)
    {
        LOGE2((ZT("Client::ConnectAsync - Attempt to connect witout disconnecting")));
        result = false;
        goto done;
    }

    // Locator defaults to SOCKETFILE:
    if (locator.GetSize() == 0)
    {
#ifdef CONFIG_POSIX
        locator = _StrToString(GetPath(ID_SOCKETFILE));
#else
        locator = MI_T("localhost:7777");
#endif
    }

    // Convert host to 'char' type:
    locator_ = _StringToStr(locator);
    if (locator_ == NULL)
    {
        goto done;
    }
    user_ = _StringToStr(user);
    if (user_ == NULL)
    {
        goto done;
    }
    password_ = _StringToStr(password);
    if (password_ == NULL)
    {
        goto done;
    }

    // Set connection state to pending.
    m_rep->connectState = ClientRep::CONNECTSTATE_PENDING;

    // Establish connection with server:
    {
        Protocol* protocol = NULL;
        r = Protocol_New_Connector(
            &protocol,
            NULL,
            locator_,
            (ProtocolCallback)ClientRep::MessageCallback,
            m_rep,
            (ProtocolEventCallback)ClientRep::EventCallback,
            m_rep,
            user_,
            password_);

        if (r != MI_RESULT_OK)
        {
            result = false;
            LOGE2((ZT("Client::ConnectAsync - Protocol_New_Connector failed with error: %d (%s)"), r, mistrerror(r)));
            goto done;
        }

        m_rep->protocol = protocol;
    }

done:

    if (locator_)
        delete [] locator_;
    if (user_)
        delete [] user_;
    if (password_)
        delete [] password_;

    LOGD2((ZT("Client::ConnectAsync - End. result: %d"), result));
    return result;
}

bool Client::Connect(
    const String& locator,
    const String& user,
    const String& password,
    Uint64 timeOutUsec)
{
    LOGD2((ZT("Client::Connect - Begin. locator: %s, timeOutUsec: %lu"), locator.Str(), timeOutUsec));

    m_rep->connectState = ClientRep::CONNECTSTATE_PENDING;

    if (!ConnectAsync(locator, user, password))
    {
        LOGE2((ZT("Client::Connect - ConnectAsync failed")));
        return false;
    }

    Uint64 endTime, now;

    if (Time_Now(&now) != MI_RESULT_OK)
        return false;

    endTime = now + timeOutUsec;

    // Wait for connection establishment or timeout.
    for ( ; endTime >= now; )
    {
        Protocol_Run(m_rep->protocol, 50000);

        if (m_rep->connectState != ClientRep::CONNECTSTATE_PENDING)
            break;

        if (Time_Now(&now) != MI_RESULT_OK)
            break;
    }

    if (m_rep->connectState != ClientRep::CONNECTSTATE_CONNECTED)
    {
        LOGE2((ZT("Client::Connect - connect state %d not CONNECTSTATE_CONNECTED"), m_rep->connectState));
        return false;
    }

    LOGD2((ZT("Client::Connect - OK exit")));

    return true;
}

bool Client::Disconnect()
{
    bool result = true;

    LOGD2((ZT("Client::Disconnect - Begin")));

    // Fail if not connected:
    if (!m_rep->protocol)
    {
        result = false;
        goto done;
    }

    // Delete the protocol object.
    {
        Result r = Protocol_Delete(m_rep->protocol);

        if (r != MI_RESULT_OK)
        {
            LOGE2((ZT("Client::Disconnect - Protocol_Delete failed with error: %d (%s)"), (int)r, mistrerror(r)));
            result = false;
            goto done;
        }

        m_rep->protocol = NULL;
    }

    m_rep->connectState = ClientRep::CONNECTSTATE_DISCONNECTED;

done:
    LOGD2((ZT("Client::Disconnect - returning; %d"), result));
    return result;
}

bool Client::Connected() const
{
    return m_rep->protocol ? true : false;
}

bool Client::Run(Uint64 timeOutUsec)
{
    bool result = true;
    LOGX2((ZT("Client::Run - Begin. timeOutUsec: %lu"), (unsigned long)timeOutUsec));

    // Fail if not connected.
    if (m_rep->protocol == NULL)
    {
        LOGE2((ZT("Client::Run - Not connected")));
        result = false;
        goto done;
    }

    // Process events.
    // ATTN: what can this return?
    Protocol_Run(m_rep->protocol, timeOutUsec);

done:
    LOGX2((ZT("Client::Run - Returning: %d"), result));
    return result;
}

bool Client::NoOpAsync(
    Uint64& msgID)
{
    msgID = _NextMsgID();
    return m_rep->NoOpAsync(msgID);
}

bool Client::GetInstanceAsync(
    const String& nameSpace,
    const DInstance& instanceName,
    Uint64& msgID)
{
    msgID = _NextMsgID();
    return m_rep->GetInstanceAsync(nameSpace, instanceName, msgID);
}

bool Client::CreateInstanceAsync(
    const String& nameSpace,
    const DInstance& instance,
    Uint64& msgID)
{
    msgID = _NextMsgID();
    return m_rep->CreateInstanceAsync(nameSpace, instance, msgID);
}

bool Client::ModifyInstanceAsync(
    const String& nameSpace,
    const DInstance& instance,
    Uint64& msgID)
{
    msgID = _NextMsgID();
    return m_rep->ModifyInstanceAsync(nameSpace, instance, msgID);
}

bool Client::DeleteInstanceAsync(
    const String& nameSpace,
    const DInstance& instanceName,
    Uint64& msgID)
{
    msgID = _NextMsgID();
    return m_rep->DeleteInstanceAsync(nameSpace, instanceName, msgID);
}

bool Client::EnumerateInstancesAsync(
    const String& nameSpace,
    const String& className,
    bool deepInheritance,
    const String& queryLanguage,
    const String& queryExpression,
    Uint64& msgID)
{
    msgID = _NextMsgID();
    return m_rep->EnumerateInstancesAsync(nameSpace, className,
        deepInheritance, queryLanguage, queryExpression, msgID);
}

bool Client::InvokeAsync(
    const String& nameSpace,
    const DInstance& instanceName,
    const String& methodName,
    const DInstance& inParameters,
    DInstance& outParameters,
    Uint64 msgID)
{
    msgID = _NextMsgID();
    return m_rep->InvokeAsync(nameSpace, instanceName, methodName, inParameters,
        outParameters, msgID);
}

bool Client::AssociatorInstancesAsync(
    const String& nameSpace,
    const DInstance& instanceName,
    const String& assocClass,
    const String& resultClass,
    const String& role,
    const String& resultRole,
    Uint64& msgID)
{
    msgID = _NextMsgID();
    return m_rep->AssociatorInstancesAsync(nameSpace, instanceName, assocClass,
        resultClass, role, resultRole, msgID);
}

bool Client::ReferenceInstancesAsync(
    const String& nameSpace,
    const DInstance& instanceName,
    const String& assocClass,
    const String& role,
    Uint64& msgID)
{
    msgID = _NextMsgID();
    return m_rep->ReferenceInstancesAsync(nameSpace, instanceName, assocClass,
        role, msgID);
}

bool Client::GetInstance(
    const String& nameSpace,
    const DInstance& instanceName,
    Uint64 timeOutUsec,
    DInstance& instance,
    Result& result)
{
    Handler* oldHandler = m_rep->handler;
    Uint64 msgID = _NextMsgID();
    InstanceHandler handler(oldHandler, msgID, instance);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->GetInstanceAsync(nameSpace, instanceName, msgID))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (Time_Now(&now) != MI_RESULT_OK)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(m_rep->protocol, 50000);

        if (handler.m_state == InstanceHandler::FAILED ||
            handler.m_state == InstanceHandler::DONE)
        {
            break;
        }

        if (Time_Now(&now) != MI_RESULT_OK)
            break;
    }

    if (handler.m_state == InstanceHandler::DONE)
        result = handler.m_result;
    else
        flag = false;

done:
    m_rep->handler = oldHandler;
    return flag;
}

bool Client::CreateInstance(
    const String& nameSpace,
    const DInstance& instance,
    Uint64 timeOutUsec,
    DInstance& instanceName,
    Result& result)
{
    Handler* oldHandler = m_rep->handler;
    Uint64 msgID = _NextMsgID();
    InstanceHandler handler(oldHandler, msgID, instanceName);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->CreateInstanceAsync(nameSpace, instance, msgID))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (Time_Now(&now) != MI_RESULT_OK)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(m_rep->protocol, 50000);

        if (handler.m_state == InstanceHandler::FAILED ||
            handler.m_state == InstanceHandler::DONE)
        {
            break;
        }

        if (Time_Now(&now) != MI_RESULT_OK)
            break;
    }

    if (handler.m_state == InstanceHandler::DONE)
        result = handler.m_result;
    else
        flag = false;

done:
    m_rep->handler = oldHandler;
    return flag;
}

bool Client::ModifyInstance(
    const String& nameSpace,
    const DInstance& instance,
    Uint64 timeOutUsec,
    Result& result)
{
    Handler* oldHandler = m_rep->handler;
    Uint64 msgID = _NextMsgID();
    ResultHandler handler(oldHandler, msgID);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->ModifyInstanceAsync(nameSpace, instance, msgID))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (Time_Now(&now) != MI_RESULT_OK)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(m_rep->protocol, 50000);

        if (handler.m_state == ResultHandler::FAILED ||
            handler.m_state == ResultHandler::DONE)
        {
            break;
        }

        if (Time_Now(&now) != MI_RESULT_OK)
            break;
    }

    if (handler.m_state == ResultHandler::DONE)
        result = handler.m_result;
    else
        flag = false;

done:
    m_rep->handler = oldHandler;
    return flag;
}

bool Client::DeleteInstance(
    const String& nameSpace,
    const DInstance& instanceName,
    Uint64 timeOutUsec,
    Result& result)
{
    Handler* oldHandler = m_rep->handler;
    Uint64 msgID = _NextMsgID();
    ResultHandler handler(oldHandler, msgID);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->DeleteInstanceAsync(nameSpace, instanceName, msgID))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (Time_Now(&now) != MI_RESULT_OK)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(m_rep->protocol, 50000);

        if (handler.m_state == ResultHandler::FAILED ||
            handler.m_state == ResultHandler::DONE)
        {
            break;
        }

        if (Time_Now(&now) != MI_RESULT_OK)
            break;
    }

    if (handler.m_state == ResultHandler::DONE)
        result = handler.m_result;
    else
        flag = false;

done:
    m_rep->handler = oldHandler;
    return flag;
}

bool Client::NoOp(Uint64 timeOutUsec)
{
    Handler* oldHandler = m_rep->handler;
    Uint64 msgID = _NextMsgID();
    NoOpHandler handler(oldHandler, msgID);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->NoOpAsync(msgID))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (Time_Now(&now) != MI_RESULT_OK)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(m_rep->protocol, 50000);

        if (handler.m_state == NoOpHandler::FAILED ||
            handler.m_state == NoOpHandler::DONE)
        {
            break;
        }

        if (Time_Now(&now) != MI_RESULT_OK)
            break;
    }

    if (handler.m_state != NoOpHandler::DONE)
        flag = false;

done:
    m_rep->handler = oldHandler;
    return flag;
}

bool Client::EnumerateInstances(
    const String& nameSpace,
    const String& className,
    bool deepInheritance,
    Uint64 timeOutUsec,
    Array<DInstance>& instances,
    const String& queryLanguage,
    const String& queryExpression,
    Result& result)
{
    Handler* oldHandler = m_rep->handler;
    Uint64 msgID = _NextMsgID();
    InstancesHandler handler(oldHandler, msgID, instances);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->EnumerateInstancesAsync(nameSpace, className, deepInheritance,
        queryLanguage, queryExpression, msgID))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (Time_Now(&now) != MI_RESULT_OK)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(m_rep->protocol, 50000);

        if (handler.m_state == InstancesHandler::FAILED ||
            handler.m_state == InstancesHandler::DONE)
        {
            break;
        }

        if (Time_Now(&now) != MI_RESULT_OK)
            break;
    }

    if (handler.m_state == InstancesHandler::DONE)
        result = handler.m_result;
    else
        flag = false;

done:
    m_rep->handler = oldHandler;
    return flag;
}

bool Client::Invoke(
    const String& nameSpace,
    const DInstance& instanceName,
    const String& methodName,
    const DInstance& inParameters,
    Uint64 timeOutUsec,
    DInstance& outParameters,
    Result& result)
{
    Handler* oldHandler = m_rep->handler;
    Uint64 msgID = _NextMsgID();
    InstanceHandler handler(oldHandler, msgID, outParameters);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->InvokeAsync(nameSpace, instanceName, methodName, inParameters,
        outParameters, msgID))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (Time_Now(&now) != MI_RESULT_OK)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(m_rep->protocol, 50000);

        if (handler.m_state == InstanceHandler::FAILED ||
            handler.m_state == InstanceHandler::DONE)
        {
            break;
        }

        if (Time_Now(&now) != MI_RESULT_OK)
            break;
    }

    if (handler.m_state == InstanceHandler::DONE)
        result = handler.m_result;
    else
        flag = false;

done:
    m_rep->handler = oldHandler;
    return flag;
}

bool Client::AssociatorInstances(
    const String& nameSpace,
    const DInstance& instanceName,
    const String& assocClass,
    const String& resultClass,
    const String& role,
    const String& resultRole,
    Uint64 timeOutUsec,
    Array<DInstance>& instances,
    Result& result)
{
    Handler* oldHandler = m_rep->handler;
    Uint64 msgID = _NextMsgID();
    InstancesHandler handler(oldHandler, msgID, instances);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->AssociatorInstancesAsync(nameSpace, instanceName, assocClass,
        resultClass, role, resultRole, msgID))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (Time_Now(&now) != MI_RESULT_OK)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(m_rep->protocol, 50000);

        if (handler.m_state == InstancesHandler::FAILED ||
            handler.m_state == InstancesHandler::DONE)
        {
            break;
        }

        if (Time_Now(&now) != MI_RESULT_OK)
            break;
    }

    if (handler.m_state == InstancesHandler::DONE)
        result = handler.m_result;
    else
        flag = false;

done:
    m_rep->handler = oldHandler;
    return flag;
}

bool Client::ReferenceInstances(
    const String& nameSpace,
    const DInstance& instanceName,
    const String& assocClass,
    const String& role,
    Uint64 timeOutUsec,
    Array<DInstance>& instances,
    Result& result)
{
    Handler* oldHandler = m_rep->handler;
    Uint64 msgID = _NextMsgID();
    InstancesHandler handler(oldHandler, msgID, instances);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->ReferenceInstancesAsync(nameSpace, instanceName, assocClass,
        role, msgID))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (Time_Now(&now) != MI_RESULT_OK)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(m_rep->protocol, 50000);

        if (handler.m_state == InstancesHandler::FAILED ||
            handler.m_state == InstancesHandler::DONE)
        {
            break;
        }

        if (Time_Now(&now) != MI_RESULT_OK)
            break;
    }

    if (handler.m_state == InstancesHandler::DONE)
        result = handler.m_result;
    else
        flag = false;

done:
    m_rep->handler = oldHandler;
    return flag;
}

MI_END_NAMESPACE
