/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "messages.h"
#include "packing.h"
#include <assert.h>
#include <stdio.h>
#include "result.h"
#include <pal/format.h>
#include "log.h"
#include "miextras.h"

/*
**==============================================================================
**
** Local definitions
**
**==============================================================================
*/

typedef enum _MessageFieldType
{
    MFT_END_OF_LIST,        /* special type to terminate list of fields */
    MFT_POINTER,            /* Pointer that has to be converted */
    MFT_POINTER_OPT,        /* Pointer that has to be converted (may be null) */
    MFT_POINTER_SET_NULL,   /* Pointer that has to be nullified instead of converting */
    MFT_INSTANCE,           /* instance */
    MFT_INSTANCE_OPT        /* instance  (maybe NULL) */
}
MessageFieldType;

/* Defines meta data for message field (to support packing/unpacking) */
typedef struct _MessageField
{
    /* (ZT=Tag, S=String, B=Boolean, A=StringArray, O=Object) */
    MessageFieldType type;

    /* Byte off within structure to this field and (for instance) to packed pointer/size */
    size_t off;
    size_t offPackedPtr;
    size_t offPackedSize;
}
MessageField;

static const MessageField baseMessageFields[] =
{
    {MFT_POINTER_SET_NULL,offsetof(Message, next),0,0},
    {MFT_POINTER_SET_NULL,offsetof(Message, prev),0,0},
    {MFT_POINTER_SET_NULL,offsetof(Message, dtor),0,0},
    {MFT_POINTER_SET_NULL,offsetof(Message, dtorData),0,0},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField emptyMessageFields[] =
{
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField requestMessageFields[] =
{
    {MFT_POINTER_OPT,offsetof(RequestMsg, regEntry.user),0,0},
    {MFT_POINTER_OPT,offsetof(RequestMsg, regEntry.nameSpace),0,0},
    {MFT_POINTER_OPT,offsetof(RequestMsg, regEntry.className),0,0},
    {MFT_POINTER_OPT,offsetof(RequestMsg, regEntry.libraryName),0,0},
    {MFT_POINTER_OPT,offsetof(RequestMsg, regEntry.interpreter),0,0},
    {MFT_POINTER_OPT,offsetof(RequestMsg, regEntry.startup),0,0},
#if defined(CONFIG_ENABLE_PREEXEC)
    {MFT_POINTER_OPT,offsetof(RequestMsg, regEntry.preexec),0,0},
#endif
    {MFT_INSTANCE_OPT,offsetof(RequestMsg, options),offsetof(RequestMsg, packedOptionsPtr),offsetof(RequestMsg, packedOptionsSize)},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField getClassMessageFields[] =
{
    {MFT_POINTER,offsetof(GetClassReq, nameSpace),0,0},
    {MFT_POINTER,offsetof(GetClassReq, className),0,0},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField getInstanceMessageFields[] =
{
    {MFT_POINTER,offsetof(GetInstanceReq, nameSpace),0,0},
    {MFT_INSTANCE,offsetof(GetInstanceReq, instanceName),offsetof(GetInstanceReq, packedInstanceNamePtr),offsetof(GetInstanceReq, packedInstanceNameSize)},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField postInstanceMessageFields[] =
{
    {MFT_INSTANCE,offsetof(PostInstanceMsg, instance),offsetof(PostInstanceMsg, packedInstancePtr),offsetof(PostInstanceMsg, packedInstanceSize)},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField postSchemaMessageFields[] =
{
    {MFT_INSTANCE_OPT,offsetof(PostSchemaMsg, schemaInstance),offsetof(PostSchemaMsg, packedSchemaInstancePtr),offsetof(PostSchemaMsg, packedSchemaInstanceSize)},
    {MFT_POINTER_OPT,offsetof(PostSchemaMsg, packedSchemaWsmanPtr),0, 0},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField enumerateInstancesMessageFields[] =
{
    {MFT_POINTER,offsetof(EnumerateInstancesReq, nameSpace),0,0},
    {MFT_POINTER_OPT,offsetof(EnumerateInstancesReq, className),0,0},
    {MFT_POINTER_OPT,offsetof(EnumerateInstancesReq, requestClassName),0,0},
    {MFT_POINTER_OPT,offsetof(EnumerateInstancesReq, queryLanguage),0,0},
    {MFT_POINTER_OPT,offsetof(EnumerateInstancesReq, queryExpression),0,0},
    {MFT_POINTER_SET_NULL,offsetof(EnumerateInstancesReq, propertySet),0,0},
    {MFT_INSTANCE_OPT,offsetof(EnumerateInstancesReq, selectorFilter),offsetof(EnumerateInstancesReq, packedFilterPtr),offsetof(EnumerateInstancesReq, packedFilterSize)},
    {MFT_POINTER_SET_NULL,offsetof(EnumerateInstancesReq, wql),0,0},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField pullMessageFields[] =
{
    {MFT_POINTER,offsetof(PullReq, nameSpace),0,0},
    {MFT_POINTER,offsetof(PullReq, className),0,0},
    {MFT_POINTER,offsetof(PullReq, context),0,0},
};

static const MessageField invokeMessageFields[] =
{
    {MFT_POINTER,offsetof(InvokeReq, nameSpace),0,0},
    {MFT_POINTER,offsetof(InvokeReq, function),0,0},
    {MFT_POINTER_OPT,offsetof(InvokeReq, className),0,0},
    {MFT_INSTANCE_OPT,offsetof(InvokeReq, instance),offsetof(InvokeReq, packedInstancePtr),offsetof(InvokeReq, packedInstanceSize)},
    {MFT_INSTANCE_OPT,offsetof(InvokeReq, instanceParams),offsetof(InvokeReq, packedInstanceParamsPtr),offsetof(InvokeReq, packedInstanceParamsSize)},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField associatorsOfMessageFields[] =
{
    {MFT_POINTER,offsetof(AssociationsOfReq, nameSpace),0,0},
    {MFT_POINTER_OPT,offsetof(AssociationsOfReq, className),0,0},
    {MFT_POINTER_OPT,offsetof(AssociationsOfReq, assocClass),0,0},
    {MFT_POINTER_OPT,offsetof(AssociationsOfReq, resultClass),0,0},
    {MFT_POINTER_OPT,offsetof(AssociationsOfReq, role),0,0},
    {MFT_POINTER_OPT,offsetof(AssociationsOfReq, resultRole),0,0},
    {MFT_INSTANCE,offsetof(AssociationsOfReq, instance),offsetof(AssociationsOfReq, packedInstancePtr),offsetof(AssociationsOfReq, packedInstanceSize)},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField referencesOfMessageFields[] =
{
    {MFT_POINTER,offsetof(AssociationsOfReq, nameSpace),0,0},
    {MFT_POINTER_OPT,offsetof(AssociationsOfReq, className),0,0},
    {MFT_POINTER_OPT,offsetof(AssociationsOfReq, assocClass),0,0},
    {MFT_POINTER_OPT,offsetof(AssociationsOfReq, resultClass),0,0},
    {MFT_POINTER_OPT,offsetof(AssociationsOfReq, role),0,0},
    {MFT_POINTER_OPT,offsetof(AssociationsOfReq, resultRole),0,0},
    {MFT_INSTANCE,offsetof(AssociationsOfReq, instance),offsetof(AssociationsOfReq, packedInstancePtr),offsetof(AssociationsOfReq, packedInstanceSize)},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField subscribeRequestMessageFields[] =
{
    {MFT_POINTER,offsetof(SubscribeReq, nameSpace),0,0},
    {MFT_POINTER_OPT,offsetof(SubscribeReq, className),0,0},
    {MFT_POINTER_OPT,offsetof(SubscribeReq, bookmark),0,0},
    {MFT_POINTER,offsetof(SubscribeReq, filter),0,0},
    {MFT_POINTER,offsetof(SubscribeReq, language),0,0},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField deleteInstanceMessageFields[] =
{
    {MFT_POINTER,offsetof(DeleteInstanceReq, nameSpace),0,0},
    {MFT_INSTANCE,offsetof(DeleteInstanceReq, instanceName),offsetof(DeleteInstanceReq, packedInstanceNamePtr),offsetof(DeleteInstanceReq, packedInstanceNameSize)},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField createInstanceMessageFields[] =
{
    {MFT_POINTER,offsetof(CreateInstanceReq, nameSpace),0,0},
    {MFT_INSTANCE,offsetof(CreateInstanceReq, instance),offsetof(CreateInstanceReq, packedInstancePtr),offsetof(CreateInstanceReq, packedInstanceSize)},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField modifyInstanceMessageFields[] =
{
    {MFT_POINTER,offsetof(ModifyInstanceReq, nameSpace),0,0},
    {MFT_INSTANCE,offsetof(ModifyInstanceReq, instance),offsetof(ModifyInstanceReq, packedInstancePtr),offsetof(ModifyInstanceReq, packedInstanceSize)},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField binProtocolNotificationFields[] =
{
    {MFT_POINTER_OPT,offsetof(BinProtocolNotification, user),0,0},
    {MFT_POINTER_OPT,offsetof(BinProtocolNotification, password),0,0},
    {MFT_POINTER_OPT,offsetof(BinProtocolNotification, authFile),0,0},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField binPostResultMsgFields[] =
{
    {MFT_POINTER_OPT,offsetof(PostResultMsg, errorMessage),0,0},
    {MFT_INSTANCE_OPT,offsetof(PostResultMsg, cimError),offsetof(PostResultMsg, packedInstancePtr),offsetof(PostResultMsg, packedInstanceSize)},
    {MFT_POINTER_OPT,offsetof(PostResultMsg, cimErrorClassName),0,0},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField postIndicationMessageFields[] =
{
    {MFT_POINTER_OPT,offsetof(PostIndicationMsg, machineID), 0, 0},
    {MFT_POINTER_OPT,offsetof(PostIndicationMsg, bookmark), 0, 0},
    {MFT_INSTANCE,offsetof(PostInstanceMsg, instance),offsetof(PostInstanceMsg, packedInstancePtr),offsetof(PostInstanceMsg, packedInstanceSize)},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField postSocketFileFields[] =
{
    {MFT_POINTER_OPT,offsetof(PostSocketFile, sockFilePath),0,0},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField socketMaintenanceFields[] =
{
    {MFT_POINTER_OPT,offsetof(VerifySocketConn, message),0,0},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField pamCheckUserFields[] =
{
    {MFT_POINTER_OPT,offsetof(PamCheckUserReq, user),0,0},
    {MFT_POINTER_OPT,offsetof(PamCheckUserReq, passwd),0,0},
    {MFT_END_OF_LIST, 0, 0, 0}
};


#if defined(CONFIG_ENABLE_PREEXEC)
static const MessageField execPreexecReqFields[] =
{
    {MFT_POINTER_OPT,offsetof(ExecPreexecReq, nameSpace),0,0},
    {MFT_POINTER_OPT,offsetof(ExecPreexecReq, className),0,0},
    {MFT_END_OF_LIST, 0, 0, 0}
};
#endif

static const MessageField createAgentMsgFields[] =
{
    {MFT_POINTER_OPT,offsetof(CreateAgentMsg, libraryName),0,0},
    {MFT_END_OF_LIST, 0, 0, 0}
};

/* Entries in this array corresponds to MessageTag values */
typedef struct _MessageDeclaration
{
    const MessageField* fields;
    size_t              size;
    MI_Boolean          cloneRequired;
}
MessageDeclaration;

static const MessageDeclaration allMessages[] = {
    {baseMessageFields,                 0,                              MI_FALSE},
    {getInstanceMessageFields,          sizeof(GetInstanceReq),         MI_TRUE},
    {postInstanceMessageFields,         sizeof(PostInstanceMsg),        MI_TRUE},
    {enumerateInstancesMessageFields,   sizeof(EnumerateInstancesReq),  MI_TRUE},
    {binPostResultMsgFields,            sizeof(PostResultMsg),          MI_FALSE},
    {emptyMessageFields,                sizeof(NoOpReq),                MI_FALSE},
    {emptyMessageFields,                sizeof(NoOpRsp),                MI_FALSE},
    {invokeMessageFields,               sizeof(InvokeReq),              MI_TRUE},
    {associatorsOfMessageFields,        sizeof(AssociationsOfReq),      MI_TRUE},
    {referencesOfMessageFields,         sizeof(AssociationsOfReq),      MI_TRUE},
    {subscribeRequestMessageFields,     sizeof(SubscribeReq),           MI_TRUE},
    {emptyMessageFields,                sizeof(UnsubscribeReq),         MI_FALSE},
    {deleteInstanceMessageFields,       sizeof(DeleteInstanceReq),      MI_TRUE},
    {createInstanceMessageFields,       sizeof(CreateInstanceReq),      MI_TRUE},
    {modifyInstanceMessageFields,       sizeof(ModifyInstanceReq),      MI_TRUE},
    {binProtocolNotificationFields,     sizeof(BinProtocolNotification),MI_FALSE},
    {getClassMessageFields,             sizeof(GetClassReq),            MI_TRUE},
    {postSchemaMessageFields,           sizeof(PostSchemaMsg),          MI_TRUE},
    {emptyMessageFields,                sizeof(HttpRequestMsg),         MI_FALSE},  // this doesnt go thru agent connection anyway
    {emptyMessageFields,                sizeof(HttpResponseMsg),        MI_FALSE},  // this doesnt go thru agent connection anyway
    {postIndicationMessageFields,       sizeof(PostIndicationMsg),      MI_TRUE},
    {emptyMessageFields,                sizeof(SubscribeRes),           MI_FALSE},
    {emptyMessageFields,                sizeof(CancelMsg),              MI_FALSE},
    {emptyMessageFields,                sizeof(ProtocolEventConnect),   MI_FALSE},  // this doesnt go thru agent connection anyway
#ifndef DISABLE_SHELL
    {createInstanceMessageFields,       sizeof(CreateInstanceReq),      MI_TRUE}, /* ShellCreateReqTag */
    {deleteInstanceMessageFields,       sizeof(DeleteInstanceReq),      MI_TRUE}, /* ShellDeleteReqTag */
    {invokeMessageFields,               sizeof(InvokeReq),              MI_TRUE}, /* ShellReceiveReqTag */
    {invokeMessageFields,               sizeof(InvokeReq),              MI_TRUE}, /* ShellSendReqTag */
    {invokeMessageFields,               sizeof(InvokeReq),              MI_TRUE}, /* ShellSignalReqTag */
    {invokeMessageFields,               sizeof(InvokeReq),              MI_TRUE}, /* ShellConnectReqTag */
    {invokeMessageFields,               sizeof(InvokeReq),              MI_TRUE}, /* ShellReconnectReqTag */
    {invokeMessageFields,               sizeof(InvokeReq),              MI_TRUE}, /* ShellDisconnectReqTag */
    {invokeMessageFields,               sizeof(InvokeReq),              MI_TRUE}, /* ShellConnectReqTag */
#endif
    {pullMessageFields,                 sizeof(PullReq),                MI_TRUE},
    {createAgentMsgFields,              sizeof(CreateAgentMsg),         MI_TRUE},
    {postSocketFileFields,              sizeof(PostSocketFile),         MI_TRUE},
    {socketMaintenanceFields,           sizeof(VerifySocketConn),       MI_TRUE},
    {pamCheckUserFields,                sizeof(PamCheckUserReq),        MI_TRUE},
    {emptyMessageFields,                sizeof(PamCheckUserResp),       MI_FALSE}
#if defined(CONFIG_ENABLE_PREEXEC)
    ,
    {execPreexecReqFields,              sizeof(ExecPreexecReq),         MI_TRUE},
    {emptyMessageFields,                sizeof(ExecPreexecResp),        MI_FALSE}
#endif
};

/*
**==============================================================================
**
** Public definitions
**
**==============================================================================
*/

Message* __Message_New(
    MessageTag tag,
    size_t structSize,
    MI_Uint64 operationId,
    MI_Uint32 flags,
    CallSite cs)
{
    Batch *batch;
    Message* self;

    batch = Batch_New(BATCH_MAX_PAGES);

    if (!batch)
        return NULL;

    /* Allocate heap space for message */
    self = (Message*) Batch_Get(batch, structSize);

    if (!self)
        return NULL;

    /* Clear all fields */
    memset(self, 0, structSize);

    /* Set the tag */
    self->tag = tag;

    /* Set the message id and flags */
    self->operationId = operationId;
    self->flags = flags;

    /* ref-counter is set to 1, to balance NewMessage/Release Message pair*/
    self->refCounter = 1;

    /* Copy batch onto message (released by delete method) */
    self->batch = batch;

    (void)cs;
#if defined(CONFIG_ENABLE_DEBUG)
    {
        const char* file = "";
        size_t line = 0;
        const PAL_Char* name = MessageName(self->tag);
        file = cs.file;
        line = cs.line;
        trace_Message_New(file, (MI_Uint32)line, name, self, (unsigned int)self->refCounter);
    }
#endif /* defined(CONFIG_ENABLE_DEBUG) */

    return self;
}

void __Message_AddRef(
    Message* self,
    CallSite cs)
{
    ptrdiff_t refs = Atomic_Inc(&self->refCounter);
    (void)refs;
    (void)cs;
#if defined(CONFIG_ENABLE_DEBUG)
    {
        const char* file = "";
        size_t line = 0;
        const PAL_Char* name = MessageName(self->tag);
        file = cs.file;
        line = cs.line;
        trace_Message_AddRef(file, (MI_Uint32)line, name, self, (unsigned int)(refs));
    }
#endif /* defined(CONFIG_ENABLE_DEBUG) */
}

/*
    Decrements message's ref-counter and destroys
    mesage if last reference was released
    Parameters:
    self - message to decref/release
*/
void __Message_Release(
    Message* self,
    CallSite cs)
{
    ptrdiff_t refs;
    MI_Uint32 tag = self->tag;

    DEBUG_ASSERT(Atomic_Read(&self->refCounter) > 0);

    if (Atomic_Dec(&self->refCounter) == 0)
    {
        refs = self->refCounter;

        /* Call destructor */
        if (self->dtor)
        {
            (*self->dtor)(self, self->dtorData);
        }

        Batch_Destroy(self->batch);
    }
    else
    {
        refs = self->refCounter;
    }

    (void)refs;
    (void)cs;
    (void)tag;
#if defined(CONFIG_ENABLE_DEBUG)
    {
        const char* file = "";
        size_t line = 0;
        const PAL_Char* name = MessageName(tag);

        file = cs.file;
        line = cs.line;
        trace_Message_Release(file, (MI_Uint32)line, name, self, (unsigned int)(refs));
    }
#endif /* defined(CONFIG_ENABLE_DEBUG) */
}

static MI_Boolean _UnpackInstance(
    Batch* batch,
    void* ptr,
    MI_Uint32 size,
    MI_Instance** instanceOut)
{
    MI_Result r;
    Buf buf = BUF_INITIALIZER;

    /* borrow pointer for unpacking, leaving it in the batch */
    buf.data = ptr;
    buf.size = size;

    r = Instance_Unpack(instanceOut, &buf, batch, MI_FALSE);
    return r == MI_RESULT_OK;
}

static MI_Result _RestoreMessage(
    Message* msg,
    const Header_BatchInfoItem* ptrAdjustmentInfo,
    size_t ptrAdjustmentInfoCount,
    MI_Boolean skipInstanceUnpack,
    const MessageField* messageFields)
{
    char* chunk = (char*)msg;
    Batch* batch = msg->batch;

    while (messageFields->type != MFT_END_OF_LIST)
    {
        void** ptr = (void**)(chunk + messageFields->off);
        switch (messageFields->type)
        {
        case MFT_POINTER_SET_NULL:
            *ptr = 0;
            break;

        case MFT_POINTER_OPT:
        case MFT_POINTER:
            if (*ptr)
            {
                if (!Batch_FixPointer(
                    batch,
                    ptrAdjustmentInfo,
                    ptrAdjustmentInfoCount,
                    ptr,
                    (size_t)0))
                {
                    trace_RestoreMsgFailed_PointersForMstPointer();
                    return MI_RESULT_INVALID_PARAMETER;
                }
            }
            else if (messageFields->type == MFT_POINTER)
            {
                trace_RestoreMsgFailed_PointerIsNull();
                return MI_RESULT_INVALID_PARAMETER;
            }

            break;

        case MFT_INSTANCE:
        case MFT_INSTANCE_OPT:
            {
                void** ptrPacked = (void**)(chunk + messageFields->offPackedPtr);
                MI_Uint32 packedSize = * (const MI_Uint32*)(chunk + messageFields->offPackedSize);

                *ptr = 0;

                if (*ptrPacked)
                {
                    if (!Batch_FixPointer(
                        batch,
                        ptrAdjustmentInfo,
                        ptrAdjustmentInfoCount,
                        ptrPacked,
                        (size_t)packedSize))
                    {
                        trace_RestoreMsgFailed_PointersForMstInstance();
                        return MI_RESULT_INVALID_PARAMETER;
                    }

                    if (!skipInstanceUnpack && !_UnpackInstance(
                        batch,
                        *ptrPacked,
                        packedSize,
                        (MI_Instance**)ptr))
                    {
                        trace_RestoreMsgFailed_UnpackingInstance();
                        return MI_RESULT_INVALID_PARAMETER;
                    }
                }
                else if (messageFields->type == MFT_INSTANCE)
                {
                    trace_RestoreMsgFailed_PtrPackedMissing();
                    return MI_RESULT_INVALID_PARAMETER;
                }
            }

            break;

        default:
            break;
        }

        messageFields++;
    }

    return MI_RESULT_OK;
}

static MI_Result _CloneMessageFields(
    _In_        const Message*      msgSrc,
    _Inout_     Message*            msg,
    _In_        const MessageField* messageFields )
{
    char* chunk = (char*)msg;
    Batch* batch = msg->batch;
    const char* chunkSrc = (const char*)msgSrc;

    while (messageFields->type != MFT_END_OF_LIST)
    {
        void** ptr = (void**)(chunk + messageFields->off);
        void** ptrSrc = (void**)(chunkSrc + messageFields->off);

        switch (messageFields->type)
        {
            case MFT_POINTER_SET_NULL:
            default:
            {
                break;
            }

            case MFT_POINTER_OPT:
            case MFT_POINTER:
            {
                if (*ptrSrc)
                {
                    *ptr = Batch_Tcsdup(batch, (const ZChar*)*ptrSrc);

                    if (!*ptr)
                        return MI_RESULT_FAILED;
                }
                else if (messageFields->type == MFT_POINTER)
                    return MI_RESULT_INVALID_PARAMETER;

                break;
            }

            case MFT_INSTANCE:
            case MFT_INSTANCE_OPT:
            {
                void** ptrPacked =
                    (void**)(chunk + messageFields->offPackedPtr);

                MI_Uint32* packedSize =
                    (MI_Uint32*)(chunk + messageFields->offPackedSize);

                const void* ptrPackedSrc =
                    *(void**)(chunkSrc + messageFields->offPackedPtr);

                MI_Uint32 packedSizeSrc =
                    *(MI_Uint32*)(chunkSrc + messageFields->offPackedSize);

                *ptr = 0;

                if (ptrPackedSrc)
                {
                    /* Take existing packed instance if exist (received from
                     * binary protocol
                     */
                    *packedSize = packedSizeSrc;
                    *ptrPacked = Batch_Get(batch, packedSizeSrc);

                    if (!*ptrPacked)
                        return MI_RESULT_FAILED;

                    memcpy(*ptrPacked, ptrPackedSrc, packedSizeSrc);
                }
                else if (*ptrSrc)
                {
                    /* Pack instance in binary buffer (received form wsman) */
                    if (MI_RESULT_OK != InstanceToBatch(
                        (const MI_Instance*)(*ptrSrc),
                        NULL, /* filterProperties */
                        NULL, /* filterPropertiesData */
                        batch,
                        ptrPacked, packedSize))
                        return MI_RESULT_FAILED;
                }
                else if (messageFields->type == MFT_INSTANCE)
                    /* Return error if non-optional parameter is missing */
                    return MI_RESULT_INVALID_PARAMETER;
            }

            break;
        }

        messageFields++;
    }

    return MI_RESULT_OK;
}

static MI_Result _CloneMessage(
    _In_        const Message*      msgSrc,
    _Inout_     Message*            msg,
                MI_Uint32           messageTag )
{
    char* chunk = (char*)msg;
    const char* chunkSrc = (const char*)msgSrc;
    MI_Uint32 messageIndex = MessageTagIndex( messageTag );
    MI_Result result = MI_RESULT_OK;

    if (messageIndex >= MI_COUNT(allMessages))
    {
        trace_RestoreMsgFailed_InvalidTag( msg->tag );
        return MI_RESULT_INVALID_PARAMETER;
    }

    /* copy all primitive data first */
    memcpy(chunk + sizeof(Message), chunkSrc + sizeof(Message), allMessages[messageIndex].size - sizeof(Message));

    if( MessageTag_IsRequest( messageTag ) )
    {
        result = _CloneMessageFields(msgSrc, msg, requestMessageFields);
    }
    if( MI_RESULT_OK == result )
    {
        result = _CloneMessageFields(msgSrc, msg, allMessages[messageIndex].fields);
    }

    return result;
}

MI_Result __MessageFromBatch(
    Batch* batch,
    void* originalMsgPtr,
    const Header_BatchInfoItem* ptrAdjustmentInfo,
    size_t ptrAdjustmentInfoCount,
    MI_Boolean skipInstanceUnpack,
    Message** msgOut,
    CallSite cs)
{
    Message* msg = originalMsgPtr;
    MI_Uint32 index;

    if (!Batch_FixPointer(
        batch,
        ptrAdjustmentInfo,
        ptrAdjustmentInfoCount,
        (void*)&msg,
        sizeof(Message)))
    {
        trace_BatchFixPointerFailed();
        return MI_RESULT_INVALID_PARAMETER;
    }

    /* fix base part of message */
    msg->batch = batch;
    msg->refCounter = 1;

    if (MI_RESULT_OK != _RestoreMessage(
        msg,
        ptrAdjustmentInfo,
        ptrAdjustmentInfoCount,
        skipInstanceUnpack,
        baseMessageFields))
    {
        trace_RestoreMsgFailed_FirstTime();
        return MI_RESULT_INVALID_PARAMETER;
    }

    index = MessageTagIndex( msg->tag );

    trace_MessageFromBatch(msg->tag, index);

    if (index >= MI_COUNT(allMessages))
    {
        trace_RestoreMsgFailed_InvalidTag( msg->tag );
        return MI_RESULT_INVALID_PARAMETER;
    }

    if( MessageTag_IsRequest( msg->tag ) )
    {
        if (MI_RESULT_OK != _RestoreMessage(
            msg,
            ptrAdjustmentInfo,
            ptrAdjustmentInfoCount,
            skipInstanceUnpack,
            requestMessageFields))
        {
            trace_RestoreMsgFailed_SecondTime(msg->tag);
            return MI_RESULT_INVALID_PARAMETER;
        }
    }

    if (MI_RESULT_OK != _RestoreMessage(
        msg,
        ptrAdjustmentInfo,
        ptrAdjustmentInfoCount,
        skipInstanceUnpack,
        allMessages[index].fields))
    {
        trace_RestoreMsgFailed_ThirdTime(msg->tag);
        return MI_RESULT_INVALID_PARAMETER;
    }

    *msgOut = msg;

    (void)cs;
#if defined(CONFIG_ENABLE_DEBUG)
    {
        const char* file = "";
        size_t line = 0;
        const PAL_Char* name = MessageName(msg->tag);
        file = cs.file;
        line = cs.line;
        trace_MessageFromBatch_Complete(file, (MI_Uint32)line, name, msg, (unsigned int)msg->refCounter);
    }
#endif /* defined(CONFIG_ENABLE_DEBUG) */

    return MI_RESULT_OK;
}

MI_Result MessagePackCloneForBinarySending(
    Message* msgSrc,
    Message** msgOut)
{
    Message* msg = msgSrc;
    MI_Uint32 index;
    MI_Result result;

    index = MessageTagIndex( msg->tag );

    if (index >= MI_COUNT(allMessages))
        return MI_RESULT_INVALID_PARAMETER;

    if (!allMessages[index].cloneRequired)
    {
        *msgOut = msg;
        Message_AddRef(msg);
        return MI_RESULT_OK;
    }

    /* create a copy */
    msg = __Message_New((MessageTag)msgSrc->tag, allMessages[index].size, msgSrc->operationId, msgSrc->flags, CALLSITE);

    if (!msg)
    {
        trace_MessagePackCloneForBinarySending_AllocFailed(msgSrc->tag);
        return MI_RESULT_FAILED;
    }

    result = _CloneMessage( msgSrc, msg, msg->tag );
    if( MI_RESULT_OK != result )
    {
        trace_MessagePackCloneForBinarySending_CloneFailed(msg->tag, result);
        Message_Release(msg);
        return result;
    }

    *msgOut = msg;
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MessageName
**
**     Get message name on tag
**
**==============================================================================
*/
#define UNKNOWN_MSG PAL_T("UNKNOWN Message")

const PAL_Char* _MsgNames[] = {
    UNKNOWN_MSG,
    PAL_T("GetInstanceReq"),
    PAL_T("PostInstanceMsg"),
    PAL_T("EnumerateInstancesReq"),
    PAL_T("PostResultMsg"),
    PAL_T("NoOpReq"),
    PAL_T("NoOpRsp"),
    PAL_T("InvokeReq"),
    PAL_T("AssociatorsOfReq"),
    PAL_T("ReferencesOfReq"),
    PAL_T("SubscribeReq"),
    PAL_T("UnsubscribeReq"),
    PAL_T("DeleteInstanceReq"),
    PAL_T("CreateInstanceReq"),
    PAL_T("ModifyInstanceReq"),
    PAL_T("BinProtocolNotification"),
    PAL_T("GetClassReq"),
    PAL_T("PostSchemaMsg"),
    PAL_T("HttpRequestMsg"),
    PAL_T("HttpResponseMsg"),
    PAL_T("PostIndicationMsg"),
    PAL_T("SubscribeRes"),
    PAL_T("CancelMsg"),
    PAL_T("ProtocolEventConnect"),
    PAL_T("ShellCreateReq(create)"),
    PAL_T("ShellDeleteReq(delete)"),
    PAL_T("ShellReceiveReq(invoke)"),
    PAL_T("ShellSendReq(invoke)"),
    PAL_T("ShellSignalReq(invoke)"),
    PAL_T("ShellConnectReq(invoke)"),
    PAL_T("ShellReconnectReq(invoke)"),
    PAL_T("ShellDisconnectReq(invoke)"),
    PAL_T("ShellCommandReq(invoke)"),
    PAL_T("PullReq"),
    PAL_T("CreateAgentMsg"),
    PAL_T("PostSocketFile"),
    PAL_T("VerifySocketConn"),
    PAL_T("PamCheckUserReq"),
    PAL_T("PamCheckUserResp"),
    PAL_T("ExecPreexecReq"),
    PAL_T("ExecPreexecResp"),
};

const PAL_Char* MessageName(MI_Uint32 tag)
{
    tag = MessageTagIndex(tag);
    if( tag < (MI_Uint32)(sizeof(_MsgNames)/sizeof(PAL_Char*)) )
    {
        return _MsgNames[tag];
    }
    return UNKNOWN_MSG;
}

_Use_decl_annotations_
HttpHeaders* HttpHeaders_Clone(
    Batch* batch,
    HttpHeaders* headers)
{
    HttpHeaders* newheaders;
    if ( !batch || !headers )
        return NULL;

    newheaders = (HttpHeaders*) Batch_GetClear(batch, sizeof(HttpHeaders));
    if (!newheaders)
        return NULL;
    if (headers->contentType)
    {
        newheaders->contentType = Batch_Strdup(batch, headers->contentType);
        if (!newheaders->contentType)
            return NULL;
    }
    if (headers->charset)
    {
        newheaders->charset = Batch_Strdup(batch, headers->charset);
        if (!newheaders->charset)
            return NULL;
    }
    if (headers->username)
    {
        newheaders->username = Batch_Strdup(batch, headers->username);
        if (!newheaders->username)
            return NULL;
    }
    if (headers->password)
    {
        newheaders->password = Batch_Strdup(batch, headers->password);
        if (!newheaders->password)
            return NULL;
    }
    if (headers->authorization)
    {
        newheaders->authorization = Batch_Strdup(batch, headers->authorization);
        if (!newheaders->authorization)
            return NULL;
    }
    newheaders->contentLength = headers->contentLength;
    if (headers->userAgent)
    {
        newheaders->userAgent = Batch_Strdup(batch, headers->userAgent);
        if (!newheaders->userAgent)
            return NULL;
    }
    if (headers->httpUrl)
    {
        newheaders->httpUrl = Batch_Strdup(batch, headers->httpUrl);
        if (!newheaders->httpUrl)
            return NULL;
    }
    if (headers->host)
    {
        newheaders->host = Batch_Strdup(batch, headers->host);
        if (!newheaders->host)
            return NULL;
    }
    newheaders->authInfo = headers->authInfo;
#if defined(CONFIG_ENABLE_HTTPHEADERS)
    {
        size_t i;
        newheaders->headersSize = headers->headersSize;
        for ( i = 0; i < newheaders->headersSize; i++ )
        {
            if (headers->headers[i].name)
            {
                newheaders->headers[i].name = Batch_Strdup(batch, headers->headers[i].name);
                if (!newheaders->headers[i].name)
                    return NULL;
            }
            if (headers->headers[i].value)
            {
                newheaders->headers[i].value = Batch_Strdup(batch, headers->headers[i].value);
                if (!newheaders->headers[i].value)
                    return NULL;
            }
        }
    }
#endif
    return newheaders;
}

