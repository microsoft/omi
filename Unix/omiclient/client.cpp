/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "client.h"
#include <base/packing.h>
#include <protocol/protocol.h>
#include <pal/sleep.h>
#include <base/paths.h>
#include <pal/thread.h>
#include <base/log.h>

#if 0
# define D(X) X
#else
# define D(X) /* empty */
#endif

STRAND_DEBUGNAME(OmiClient);

MI_BEGIN_NAMESPACE

//==============================================================================
//
// Local definitions.
//
//==============================================================================

PAL_Uint64 _NextOperationId()
{
    static volatile ptrdiff_t _operationId = 10000;
    PAL_Uint64 x = Atomic_Inc(&_operationId);

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

    virtual void HandleNoOp(Uint64 operationId)
    {
        if (m_handler)
            m_handler->HandleNoOp(operationId);
    }

    virtual void HandleInstance(Uint64 operationId, const DInstance& instance)
    {
        if (m_handler)
            m_handler->HandleInstance(operationId, instance);
    }

    virtual void HandleResult(Uint64 operationId, MI_Result result)
    {
        if (m_handler)
            m_handler->HandleResult(operationId, result);
    }
    virtual void HandleResult(Uint64 operationId, MI_Result result, const MI_Char *error, const DInstance* cimError)
    {
        if (m_handler)
            m_handler->HandleResult(operationId, result, error, cimError);
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

    NoOpHandler(Handler* handler, Uint64 operationId) : 
        EnvelopeHandler(handler), m_state(START), m_operationId(operationId)
    {
    }

    virtual void HandleNoOp(Uint64 operationId)
    {
        if (operationId != m_operationId)
        {
            EnvelopeHandler::HandleNoOp(operationId);
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
    Uint64 m_operationId;
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

    ResultHandler(Handler* handler, Uint64 operationId) : 
        EnvelopeHandler(handler),
        m_state(START),
        m_operationId(operationId),
        m_result(MI_RESULT_OK),
        m_cimerror(NULL),
        m_errorMessage(NULL)
    {
    }

    virtual void HandleResult(Uint64 operationId, Result result)
    {
        if (operationId != m_operationId)
        {
            EnvelopeHandler::HandleResult(operationId, result);
            return;
        }

        if (m_state != START)
        {
            m_state = FAILED;
            return;
        }

        m_result = result;
        m_state = DONE;
    }

    virtual void HandleResult(Uint64 operationId, MI_Result result, const MI_Char *error, const DInstance* cimError)
    {
        if (operationId != m_operationId)
        {
            EnvelopeHandler::HandleResult(operationId, result, error, cimError);
            return;
        }

        if (m_state != START)
        {
            m_state = FAILED;
            return;
        }

        m_result = result;
        m_cimerror = cimError;
        m_errorMessage = error;
        m_state = DONE;
    }

    State m_state;
    Uint64 m_operationId;
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
        Uint64 operationId,
        DInstance& instance) 
        : 
        EnvelopeHandler(handler),
        m_state(INSTANCE),
        m_operationId(operationId),
        m_instance(instance),
        m_result(MI_RESULT_OK),
        m_errorMessage(NULL),
        m_cimerror(NULL)
    {
    }

    virtual void HandleInstance(Uint64 operationId, const DInstance& instance)
    {
        if (operationId != m_operationId)
        {
            EnvelopeHandler::HandleInstance(operationId, instance);
            return;
        }

        if (m_state != INSTANCE)
        {
            m_state = FAILED;
            return;
        }

        m_instance = instance;
        m_state = RESULT;
    }

    virtual void HandleResult(Uint64 operationId, Result result)
    {
        if (operationId != m_operationId)
        {
            EnvelopeHandler::HandleResult(operationId, result);
            return;
        }

        if (m_state != INSTANCE && m_state != RESULT)
        {
            m_state = FAILED;
            return;
        }

        m_result = result;
        m_state = DONE;
    }
    
    virtual void HandleResult(Uint64 operationId, MI_Result result, const MI_Char *error, const DInstance* cimError)
    {
        if (operationId != m_operationId)
        {
            EnvelopeHandler::HandleResult(operationId, result, error, cimError);
            return;
        }

        if (m_state != INSTANCE && m_state != RESULT)
        {
            m_state = FAILED;
            return;
        }

        m_result = result;
        m_cimerror = cimError;
        m_errorMessage = error;
        m_state = DONE;
    }

    State m_state;
    Uint64 m_operationId;
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
        Uint64 operationId,
        Array<DInstance>& instances) 
        : 
        EnvelopeHandler(handler),
        m_state(INSTANCES),
        m_operationId(operationId),
        m_instances(instances),
        m_result(MI_RESULT_OK)
    {
    }

    virtual void HandleInstance(Uint64 operationId, const DInstance& instance)
    {
        if (operationId != m_operationId)
        {
            EnvelopeHandler::HandleInstance(operationId, instance);
            return;
        }

        if (m_state != INSTANCES)
        {
            m_state = FAILED;
            return;
        }

        m_instances.PushBack(instance);
    }

    virtual void HandleResult(Uint64 operationId, Result result)
    {
        if (operationId != m_operationId)
        {
            EnvelopeHandler::HandleResult(operationId, result);
            return;
        }

        if (m_state != INSTANCES)
        {
            m_state = FAILED;
            return;
        }

        m_result = result;
        m_state = DONE;
    }

    virtual void HandleResult(Uint64 operationId, Result result, const MI_Char *error, const DInstance* cimError)
    {
        if (operationId != m_operationId)
        {
            EnvelopeHandler::HandleResult(operationId, result);
            return;
        }

        if (m_state != INSTANCES)
        {
            m_state = FAILED;
            return;
        }

        m_result = result;
        m_state = DONE;
    }

    State m_state;
    Uint64 m_operationId;
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

    ProtocolSocketAndBase* protocol;
    Strand strand;  // To manage interaction with ProtocolSocket
    Handler* handler;
    ConnectState connectState;

    static void MessageCallback(
        ClientRep * rep,
        Message* msg);

    bool NoOpAsync(
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

void ClientRep::MessageCallback(
    ClientRep * clientRep,
    Message* msg)
{
    Handler* handler = clientRep->handler;

    DEBUG_ASSERT(msg != 0);

    switch (msg->tag)
    {
        case NoOpRspTag:
        {
            D( printf("ClientRep::MessageCallback(): NoOpRspTag\n"); )
            NoOpRsp* rsp = (NoOpRsp*)msg;
            MI_UNUSED(rsp);
            if (handler)
                handler->HandleNoOp(rsp->base.operationId);
            break;
        }
        case PostInstanceMsgTag:
        {
            D( printf("ClientRep::MessageCallback(): PostInstanceMsgTag\n"); )
            PostInstanceMsg* rsp = (PostInstanceMsg*)msg;

            if (rsp->instance)
            {
                DInstance di(rsp->instance, DInstance::CLONE);
                if (handler)
                    handler->HandleInstance(rsp->base.operationId, di);
            }

            break;
        }
        case PostResultMsgTag:
        {
            D( printf("ClientRep::MessageCallback(): PostResultMsgTag\n"); )
            PostResultMsg* rsp = (PostResultMsg*)msg;
            if (handler)
            {
                if (rsp->cimError)
                {
                    DInstance di((MI_Instance*)(rsp->cimError), DInstance::CLONE);
                    handler->HandleResult(rsp->base.operationId, rsp->result, rsp->errorMessage, &di);
                }
                else
                {
                    handler->HandleResult(rsp->base.operationId, rsp->result, rsp->errorMessage, NULL);
                }
            }
            break;
        }
        default:
        {
            D( printf("ClientRep::MessageCallback(): default\n"); )
            break;
        }
    }
}

bool ClientRep::NoOpAsync(
    Uint64 operationId)
{
    NoOpReq* req = 0;
    bool result = true;

    // Fail if not connected:
    if( !protocol || !strand.info.opened )
    {
        result = false;
        goto done;
    }

    // Create request message:
    {
        req = NoOpReq_New(operationId);

        if (!req)
        {
            result = false;
            goto done;
        }
    }

    // Send the message:
    {
        Strand_SchedulePost(&strand,&req->base.base);
    }

done:

    if (req)
        NoOpReq_Release(req);

    return result;
}

bool ClientRep::GetInstanceAsync(
    const String& nameSpace,
    const DInstance& instanceName,
    Uint64 operationId)
{
    GetInstanceReq* req = 0;
    bool result = true;

    // Fail if not connected.
    if( !protocol || !strand.info.opened )
    {
        result = false;
        goto done;
    }

    // Create the request message:
    {
        req = GetInstanceReq_New(operationId, BinaryProtocolFlag);

        if (!req)
        {
            result = false;
            goto done;
        }
    }

    // Set nameSpace:
    req->nameSpace = Batch_Tcsdup(req->base.base.batch, nameSpace.Str());
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
            req->base.base.batch,
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
        Strand_SchedulePost(&strand,&req->base.base);
    }

done:
    if (req)
        GetInstanceReq_Release(req);

    return result;
}

bool ClientRep::CreateInstanceAsync(
    const String& nameSpace,
    const DInstance& instance,
    Uint64 operationId)
{
    CreateInstanceReq* req = 0;
    bool result = true;

    // Fail if not connected.
    if( !protocol || !strand.info.opened )
    {
        result = false;
        goto done;
    }

    // Create the request message:
    {
        req = CreateInstanceReq_New(operationId, BinaryProtocolFlag);

        if (!req)
        {
            result = false;
            goto done;
        }
    }

    // Set nameSpace:
    req->nameSpace = Batch_Tcsdup(req->base.base.batch, nameSpace.Str());
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
            req->base.base.batch,
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
        Strand_SchedulePost(&strand,&req->base.base);
    }

done:
    if (req)
        CreateInstanceReq_Release(req);

    return result;
}

bool ClientRep::ModifyInstanceAsync(
    const String& nameSpace,
    const DInstance& instance,
    Uint64 operationId)
{
    ModifyInstanceReq* req = 0;
    bool result = true;

    // Fail if not connected.
    if( !protocol || !strand.info.opened )
    {
        result = false;
        goto done;
    }

    // Create the request message:
    {
        req = ModifyInstanceReq_New(operationId, BinaryProtocolFlag);

        if (!req)
        {
            result = false;
            goto done;
        }
    }

    // Set nameSpace:
    req->nameSpace = Batch_Tcsdup(req->base.base.batch, nameSpace.Str());
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
            req->base.base.batch,
            &req->packedInstancePtr, 
            &req->packedInstanceSize);

        if (r != MI_RESULT_OK)
        {
            result = false;
            goto done;
        }
    }

    // Send the messages:
    Strand_SchedulePost(&strand,&req->base.base);

done:
    if (req)
        ModifyInstanceReq_Release(req);

    return result;
}

bool ClientRep::DeleteInstanceAsync(
    const String& nameSpace,
    const DInstance& instanceName,
    Uint64 operationId)
{
    DeleteInstanceReq* req = 0;
    bool result = true;

    // Fail if not connected.
    if( !protocol || !strand.info.opened )
    {
        result = false;
        goto done;
    }

    // Create the request message:
    {
        req = DeleteInstanceReq_New(operationId, BinaryProtocolFlag);

        if (!req)
        {
            result = false;
            goto done;
        }
    }

    // Set nameSpace:
    req->nameSpace = Batch_Tcsdup(req->base.base.batch, nameSpace.Str());
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
            req->base.base.batch,
            &req->packedInstanceNamePtr, 
            &req->packedInstanceNameSize);

        if (r != MI_RESULT_OK)
        {
            result = false;
            goto done;
        }
    }

    // Send the messages:
    Strand_SchedulePost(&strand,&req->base.base);

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
    Uint64 operationId)
{
    EnumerateInstancesReq* req = 0;
    bool result = true;

    // Fail if not connected.
    if( !protocol || !strand.info.opened )
    {
        result = false;
        goto done;
    }

    // Create the request message:
    {
        req = EnumerateInstancesReq_New(operationId, BinaryProtocolFlag);

        if (!req)
        {
            result = false;
            goto done;
        }
    }

    // Populate the fields of the request message:
    {
        req->nameSpace = Batch_Tcsdup(req->base.base.batch, nameSpace.Str());
        req->className = Batch_Tcsdup(req->base.base.batch, className.Str());

        if (!req->nameSpace || !req->className)
        {
            result = false;
            goto done;
        }

        if (queryLanguage.GetSize())
        {
            req->queryLanguage = 
                Batch_Tcsdup(req->base.base.batch, queryLanguage.Str());
            if (!req->queryLanguage)
            {
                result = false;
                goto done;
            }
        }

        if (queryExpression.GetSize())
        {
            req->queryExpression = 
                Batch_Tcsdup(req->base.base.batch, queryExpression.Str());
            if (!req->queryExpression)
            {
                result = false;
                goto done;
            }
        }

        req->deepInheritance = deepInheritance;
    }

    // Send the messages:
    Strand_SchedulePost(&strand,&req->base.base);

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
    Uint64 operationId)
{
    InvokeReq* req = 0;
    bool result = true;

    // Fail if not connected.
    if( !protocol || !strand.info.opened )
    {
        result = false;
        goto done;
    }

    // Create the request message:
    {
        req = InvokeReq_New(operationId, BinaryProtocolFlag);

        if (!req)
        {
            result = false;
            goto done;
        }
    }

    // Set nameSpace:
    req->nameSpace = Batch_Tcsdup(req->base.base.batch, nameSpace.Str());
    if (!req->nameSpace)
    {
        result = false;
        goto done;
    }

    // Set className:
    req->className = Batch_Tcsdup(req->base.base.batch, 
        instanceName.GetClassName().Str());
    if (!req->className)
    {
        result = false;
        goto done;
    }

    // Set methodName:
    req->function = Batch_Tcsdup(req->base.base.batch, methodName.Str());
    if (!req->function)
    {
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
            req->base.base.batch, 
            &req->packedInstancePtr, 
            &req->packedInstanceSize);

        if (r != MI_RESULT_OK)
        {
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
            req->base.base.batch,
            &req->packedInstanceParamsPtr, 
            &req->packedInstanceParamsSize);

        if (r != MI_RESULT_OK)
        {
            result = false;
            goto done;
        }
    }

    // Send the messages:
    Strand_SchedulePost(&strand,&req->base.base);

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
    Uint64& operationId)
{
    AssociationsOfReq* req = 0;
    bool result = true;

    // Fail if not connected.
    if( !protocol || !strand.info.opened )
    {
        result = false;
        goto done;
    }

    // Create the request message:
    {
        req = AssociationsOfReq_New(operationId, BinaryProtocolFlag, AssociatorsOfReqTag);

        if (!req)
        {
            result = false;
            goto done;
        }
    }

    // Set nameSpace:
    req->nameSpace = Batch_Tcsdup(req->base.base.batch, nameSpace.Str());
    if (!req->nameSpace)
    {
        result = false;
        goto done;
    }

    // Set assocClass:
    if (assocClass.GetSize())
    {
        req->assocClass = Batch_Tcsdup(req->base.base.batch, assocClass.Str());
        if (!req->assocClass)
        {
            result = false;
            goto done;
        }
    }

    // Set resultClass:
    if (resultClass.GetSize())
    {
        req->resultClass = Batch_Tcsdup(req->base.base.batch,resultClass.Str());
        if (!req->resultClass)
        {
            result = false;
            goto done;
        }
    }

    // Set role:
    if (role.GetSize())
    {
        req->role = Batch_Tcsdup(req->base.base.batch, role.Str());
        if (!req->role)
        {
            result = false;
            goto done;
        }
    }

    // Set resultRole:
    if (resultRole.GetSize())
    {
        req->resultRole = Batch_Tcsdup(req->base.base.batch, resultRole.Str());
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
            req->base.base.batch,
            &req->packedInstancePtr, 
            &req->packedInstanceSize);

        if (r != MI_RESULT_OK)
        {
            result = false;
            goto done;
        }
    }

    // Send the messages:
    Strand_SchedulePost(&strand,&req->base.base);

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
    const String& resultClass,
    const String& role,
    Uint64& operationId)
{
    AssociationsOfReq* req = 0;
    bool result = true;

    // Fail if not connected.
    if( !protocol || !strand.info.opened )
    {
        result = false;
        goto done;
    }

    // Create the request message:
    {
        req = AssociationsOfReq_New(operationId, BinaryProtocolFlag, ReferencesOfReqTag);

        if (!req)
        {
            result = false;
            goto done;
        }
    }

    // Set nameSpace:
    req->nameSpace = Batch_Tcsdup(req->base.base.batch, nameSpace.Str());
    if (!req->nameSpace)
    {
        result = false;
        goto done;
    }

    // Set assocClass:
    if (resultClass.GetSize())
    {
        req->resultClass = Batch_Tcsdup(req->base.base.batch, resultClass.Str());
        if (!req->resultClass)
        {
            result = false;
            goto done;
        }
    }

    // Set role:
    if (role.GetSize())
    {
        req->role = Batch_Tcsdup(req->base.base.batch, role.Str());
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
            req->base.base.batch,
            &req->packedInstancePtr, 
            &req->packedInstanceSize);

        if (r != MI_RESULT_OK)
        {
            result = false;
            goto done;
        }
    }

    // Send the messages:
    Strand_SchedulePost(&strand,&req->base.base);

done:
    if (req)
        AssociationsOfReq_Release(req);

    return result;
}

//==============================================================================

MI_EXTERN_C void _Client_Post( _In_ Strand* self_, _In_ Message* msg)
{
    ClientRep* rep = FromOffset(ClientRep,strand,self_);
    
    trace_Client_Post(
        msg,
        msg->tag,
        MessageName(msg->tag),
        msg->operationId );
    
    ClientRep::MessageCallback( rep, msg );

    Strand_Ack(self_);  // return an Ack to protocol
}

MI_EXTERN_C void _Client_PostControl( _In_ Strand* self_, _In_ Message* msg)
{
    ClientRep* rep = FromOffset(ClientRep,strand,self_);
    ProtocolEventConnect* eventMsg = (ProtocolEventConnect*)msg;
    Handler* handler = rep->handler;

    DEBUG_ASSERT( ProtocolEventConnectTag == msg->tag );

    if( eventMsg->success )
    {
        D( printf("==== EventCallback() PROTOCOLEVENT_CONNECT\n"); )
        rep->connectState = ClientRep::CONNECTSTATE_CONNECTED;
        if (handler)
            handler->HandleConnect();
    }
    else
    {
        D( printf("==== EventCallback() PROTOCOLEVENT_CONNECT_FAILED\n"); )
        if (handler)
            handler->HandleConnectFailed();
        rep->connectState = ClientRep::CONNECTSTATE_FAILED;
    }
}

MI_EXTERN_C void _Client_Ack( _In_ Strand* self )
{
    trace_Client_Ack();
    // We are not streaming any results, so no need to manage flow control on Ack
}

MI_EXTERN_C void _Client_Cancel( _In_ Strand* self )
{
    DEBUG_ASSERT( MI_FALSE );  // not used yet
}

MI_EXTERN_C void _Client_Close( _In_ Strand* self_ )
{
    ClientRep* rep = FromOffset(ClientRep,strand,self_);
    Handler* handler = rep->handler;
    
    trace_Client_Close();
    // most management done by strand implementation
    
    if (handler)
        handler->HandleDisconnect();
    rep->connectState = ClientRep::CONNECTSTATE_DISCONNECTED;
}

MI_EXTERN_C void _Client_Finish( _In_ Strand* self_ )
{
    trace_Client_Finish();
    // nothing to do here, (class take care of deleting itself)
}

/*
    Object that implements the C++ client endpoint.
    It opens an interaction to the binary protocol below 
    to communicate on a TCP Socket.

    Behavior:
    - Post just passed the operation to tries to ClientRep::MessageCallback
       if that fails it sends the Ack immediately
    - Post control is used to notify connected state (connect succeeded/failed)
    - Ack does not do anything at this point (as there are no secondary messages)
    - Cancel is not used
    - Puts it on disconnected state if not there already
    - Shutdown: 
       The Client objects are shutdown/deleted thru the normal
       Strand logic (once the interaction is closed).
*/
StrandFT _Client_InteractionFT =
{
    _Client_Post, 
    _Client_PostControl, 
    _Client_Ack,
    _Client_Cancel, 
    _Client_Close,
    _Client_Finish,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL 
};

//==============================================================================
//
// class Client
//
//==============================================================================

Client::Client(Handler* handler)
{
    m_rep = new ClientRep;
    m_rep->protocol = 0;
    m_rep->connectState = ClientRep::CONNECTSTATE_DISCONNECTED;
    m_rep->handler = handler;

    //Log_OpenStdErr();   
    //Log_SetLevel(LOG_DEBUG);
    
    Strand_Init( STRAND_DEBUG(OmiClient) &m_rep->strand, &_Client_InteractionFT, STRAND_FLAG_ENTERSTRAND, NULL );    // this is the one that Opens the interaction (not the one that receives the open)
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

    // Fail if already connected:
    if (m_rep->protocol)
    {
        result = false;
        goto done;
    }

    // Locator defaults to SOCKETFILE:
    if (locator.GetSize() == 0)
    {
#ifdef CONFIG_POSIX
        locator = _StrToString(OMI_GetPath(ID_SOCKETFILE));
#else
        locator = MI_T("localhost:7777");
#endif
    }

    // Convert host to 'char' type:
    locator_ = _StringToStr(locator);
    if (!locator_)
    {
        goto done;
    }
    user_ = _StringToStr(user);
    if (!user_)
    {
        goto done;
    }
    password_ = _StringToStr(password);
    if (!password_)
    {
        goto done;
    }

    // Set connection state to pending.
    m_rep->connectState = ClientRep::CONNECTSTATE_PENDING;

    // Establish connection with server:
    {
        InteractionOpenParams params;
        ProtocolSocketAndBase* protocol = NULL;

        Strand_OpenPrepare(&m_rep->strand,&params,NULL,NULL,MI_TRUE);
        
        r = ProtocolSocketAndBase_New_Connector(
            &protocol, 
            NULL,
            locator_,
            &params,
            user_,
            password_ );

        if (r != MI_RESULT_OK)
        {
            result = false;
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
    return result;
}

bool Client::Connect(
    const String& locator, 
    const String& user,
    const String& password,
    Uint64 timeOutUsec)
{
    m_rep->connectState = ClientRep::CONNECTSTATE_PENDING;

    if (!ConnectAsync(locator, user, password))
        return false;

    Uint64 endTime, now;

    if (PAL_Time(&now) != PAL_TRUE)
        return false;

    endTime = now + timeOutUsec;

    // Wait for connection establishment or timeout.
    for (;endTime >= now;)
    {
        Protocol_Run(&m_rep->protocol->internalProtocolBase, SELECT_BASE_TIMEOUT_MSEC * 1000);

        if (m_rep->connectState != ClientRep::CONNECTSTATE_PENDING)
            break;

        if (PAL_Time(&now) != PAL_TRUE)
            break;
    }

    if (m_rep->connectState != ClientRep::CONNECTSTATE_CONNECTED)
        return false;

    return true;
}

bool Client::Disconnect()
{
    bool result = true;

    // Fail if not connected:
    if( !m_rep->protocol || !m_rep->strand.info.opened )
    {
        result = false;
        goto done;
    }

    if ( m_rep->strand.info.opened )
    {
        Strand_ScheduleClose( &m_rep->strand );
        Protocol_Run(&m_rep->protocol->internalProtocolBase, SELECT_BASE_TIMEOUT_MSEC * 1000);
    }

    // Delete the protocol object.
    {
        ProtocolSocketAndBase_ReadyToFinish(m_rep->protocol);

        m_rep->protocol = 0;
    }

    m_rep->connectState = ClientRep::CONNECTSTATE_DISCONNECTED;

done:
    return result;
}

bool Client::Connected() const
{
    return m_rep->protocol && m_rep->strand.info.opened ? true : false;
}

bool Client::Run(Uint64 timeOutUsec)
{
    bool result = true;

    // Fail if not connected.
    if (!m_rep->protocol || !m_rep->strand.info.opened)
    {
        result = false;
        goto done;
    }

    // Process events.
    // ATTN: what can this return?
    Protocol_Run(&m_rep->protocol->internalProtocolBase, timeOutUsec);

done:
    return result;
}

bool Client::NoOpAsync(
    Uint64& operationId)
{
    operationId = _NextOperationId();
    return m_rep->NoOpAsync(operationId);
}

bool Client::GetInstanceAsync(
    const String& nameSpace,
    const DInstance& instanceName,
    Uint64& operationId)
{
    operationId = _NextOperationId();
    return m_rep->GetInstanceAsync(nameSpace, instanceName, operationId);
}

bool Client::CreateInstanceAsync(
    const String& nameSpace,
    const DInstance& instance,
    Uint64& operationId)
{
    operationId = _NextOperationId();
    return m_rep->CreateInstanceAsync(nameSpace, instance, operationId);
}

bool Client::ModifyInstanceAsync(
    const String& nameSpace,
    const DInstance& instance,
    Uint64& operationId)
{
    operationId = _NextOperationId();
    return m_rep->ModifyInstanceAsync(nameSpace, instance, operationId);
}

bool Client::DeleteInstanceAsync(
    const String& nameSpace,
    const DInstance& instanceName,
    Uint64& operationId)
{
    operationId = _NextOperationId();
    return m_rep->DeleteInstanceAsync(nameSpace, instanceName, operationId);
}

bool Client::EnumerateInstancesAsync(
    const String& nameSpace,
    const String& className,
    bool deepInheritance,
    const String& queryLanguage,
    const String& queryExpression,
    Uint64& operationId)
{
    operationId = _NextOperationId();
    return m_rep->EnumerateInstancesAsync(nameSpace, className, 
        deepInheritance, queryLanguage, queryExpression, operationId);
}

bool Client::InvokeAsync(
    const String& nameSpace,
    const DInstance& instanceName,
    const String& methodName,
    const DInstance& inParameters,
    DInstance& outParameters,
    Uint64 operationId)
{
    operationId = _NextOperationId();
    return m_rep->InvokeAsync(nameSpace, instanceName, methodName, inParameters,
        outParameters, operationId);
}

bool Client::AssociatorInstancesAsync(
    const String& nameSpace,
    const DInstance& instanceName,
    const String& assocClass,
    const String& resultClass,
    const String& role,
    const String& resultRole,
    Uint64& operationId)
{
    operationId = _NextOperationId();
    return m_rep->AssociatorInstancesAsync(nameSpace, instanceName, assocClass,
        resultClass, role, resultRole, operationId);
}

bool Client::ReferenceInstancesAsync(
    const String& nameSpace,
    const DInstance& instanceName,
    const String& assocClass,
    const String& role,
    Uint64& operationId)
{
    operationId = _NextOperationId();
    return m_rep->ReferenceInstancesAsync(nameSpace, instanceName, assocClass,
        role, operationId);
}

bool Client::GetInstance(
    const String& nameSpace,
    const DInstance& instanceName,
    Uint64 timeOutUsec,
    DInstance& instance,
    Result& result)
{
    Handler* oldHandler = m_rep->handler;
    Uint64 operationId = _NextOperationId();
    InstanceHandler handler(oldHandler, operationId, instance);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->GetInstanceAsync(nameSpace, instanceName, operationId))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (PAL_Time(&now) != PAL_TRUE)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(&m_rep->protocol->internalProtocolBase, SELECT_BASE_TIMEOUT_MSEC * 1000);

        if (handler.m_state == InstanceHandler::FAILED ||
            handler.m_state == InstanceHandler::DONE)
        {
            break;
        }

        if (PAL_Time(&now) != PAL_TRUE)
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
    Uint64 operationId = _NextOperationId();
    InstanceHandler handler(oldHandler, operationId, instanceName);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->CreateInstanceAsync(nameSpace, instance, operationId))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (PAL_Time(&now) != PAL_TRUE)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(&m_rep->protocol->internalProtocolBase, SELECT_BASE_TIMEOUT_MSEC * 1000);

        if (handler.m_state == InstanceHandler::FAILED ||
            handler.m_state == InstanceHandler::DONE)
        {
            break;
        }

        if (PAL_Time(&now) != PAL_TRUE)
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
    Uint64 operationId = _NextOperationId();
    ResultHandler handler(oldHandler, operationId);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->ModifyInstanceAsync(nameSpace, instance, operationId))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (PAL_Time(&now) != PAL_TRUE)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(&m_rep->protocol->internalProtocolBase, SELECT_BASE_TIMEOUT_MSEC * 1000);

        if (handler.m_state == ResultHandler::FAILED ||
            handler.m_state == ResultHandler::DONE)
        {
            break;
        }

        if (PAL_Time(&now) != PAL_TRUE)
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
    Uint64 operationId = _NextOperationId();
    ResultHandler handler(oldHandler, operationId);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->DeleteInstanceAsync(nameSpace, instanceName, operationId))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (PAL_Time(&now) != PAL_TRUE)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(&m_rep->protocol->internalProtocolBase, SELECT_BASE_TIMEOUT_MSEC * 1000);

        if (handler.m_state == ResultHandler::FAILED ||
            handler.m_state == ResultHandler::DONE)
        {
            break;
        }

        if (PAL_Time(&now) != PAL_TRUE)
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
    Uint64 operationId = _NextOperationId();
    NoOpHandler handler(oldHandler, operationId);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->NoOpAsync(operationId))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (PAL_Time(&now) != PAL_TRUE)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(&m_rep->protocol->internalProtocolBase, SELECT_BASE_TIMEOUT_MSEC * 1000);

        if (handler.m_state == NoOpHandler::FAILED ||
            handler.m_state == NoOpHandler::DONE)
        {
            break;
        }

        if (PAL_Time(&now) != PAL_TRUE)
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
    Uint64 operationId = _NextOperationId();
    InstancesHandler handler(oldHandler, operationId, instances);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->EnumerateInstancesAsync(nameSpace, className, deepInheritance,
        queryLanguage, queryExpression, operationId))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (PAL_Time(&now) != PAL_TRUE)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(&m_rep->protocol->internalProtocolBase, SELECT_BASE_TIMEOUT_MSEC * 1000);

        if (handler.m_state == InstancesHandler::FAILED ||
            handler.m_state == InstancesHandler::DONE)
        {
            break;
        }

        if (PAL_Time(&now) != PAL_TRUE)
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
    Uint64 operationId = _NextOperationId();
    InstanceHandler handler(oldHandler, operationId, outParameters);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->InvokeAsync(nameSpace, instanceName, methodName, inParameters,
        outParameters, operationId))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (PAL_Time(&now) != PAL_TRUE)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(&m_rep->protocol->internalProtocolBase, SELECT_BASE_TIMEOUT_MSEC * 1000);

        if (handler.m_state == InstanceHandler::FAILED ||
            handler.m_state == InstanceHandler::DONE)
        {
            break;
        }

        if (PAL_Time(&now) != PAL_TRUE)
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
    Uint64 operationId = _NextOperationId();
    InstancesHandler handler(oldHandler, operationId, instances);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->AssociatorInstancesAsync(nameSpace, instanceName, assocClass,
        resultClass, role, resultRole, operationId))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (PAL_Time(&now) != PAL_TRUE)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(&m_rep->protocol->internalProtocolBase, SELECT_BASE_TIMEOUT_MSEC * 1000);

        if (handler.m_state == InstancesHandler::FAILED ||
            handler.m_state == InstancesHandler::DONE)
        {
            break;
        }

        if (PAL_Time(&now) != PAL_TRUE)
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
    Uint64 operationId = _NextOperationId();
    InstancesHandler handler(oldHandler, operationId, instances);
    m_rep->handler = &handler;
    bool flag = true;

    if (!m_rep->ReferenceInstancesAsync(nameSpace, instanceName, assocClass,
        role, operationId))
    {
        flag = false;
        goto done;
    }

    Uint64 endTime, now;

    if (PAL_Time(&now) != PAL_TRUE)
        return false;

    endTime = now + timeOutUsec;

    for (;endTime >= now;)
    {
        Protocol_Run(&m_rep->protocol->internalProtocolBase, SELECT_BASE_TIMEOUT_MSEC * 1000);

        if (handler.m_state == InstancesHandler::FAILED ||
            handler.m_state == InstancesHandler::DONE)
        {
            break;
        }

        if (PAL_Time(&now) != PAL_TRUE)
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
