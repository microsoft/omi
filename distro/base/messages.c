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

#include "messages.h"
#include "packing.h"
#include <assert.h>
#include "result.h"
#include <io/io.h>
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
    MFT_END_OF_LIST,    /* special type to terminate list of fields */
    MFT_POINTER,        /* Pointer that has to be converted */
    MFT_POINTER_OPT,    /* Pointer that has to be converted (may be null) */
    MFT_POINTER_SET_NULL,   /* Pointer that has to be nullified instead of converting */
    MFT_INSTANCE,       /* instance */
    MFT_INSTANCE_OPT    /* instance  (maybe NULL) */
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
    {MFT_POINTER_SET_NULL,offsetof(Message, request),0,0},
    {MFT_POINTER_SET_NULL,offsetof(Message, callback),0,0},
    {MFT_POINTER_SET_NULL,offsetof(Message, callbackData),0,0},
    {MFT_POINTER_SET_NULL,offsetof(Message, dtor),0,0},
    {MFT_POINTER_SET_NULL,offsetof(Message, dtorData),0,0},
    {MFT_POINTER_OPT,offsetof(Message, libraryName),0,0},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField emptyMessageFields[] =
{
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

static const MessageField enumerateInstancesMessageFields[] =
{
    {MFT_POINTER,offsetof(EnumerateInstancesReq, nameSpace),0,0},
    {MFT_POINTER,offsetof(EnumerateInstancesReq, className),0,0},
    {MFT_POINTER_OPT,offsetof(EnumerateInstancesReq, requestClassName),0,0},
    {MFT_POINTER_OPT,offsetof(EnumerateInstancesReq, queryLanguage),0,0},
    {MFT_POINTER_OPT,offsetof(EnumerateInstancesReq, queryExpression),0,0},
    {MFT_END_OF_LIST, 0, 0, 0}
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
    {MFT_POINTER,offsetof(SubscribeReq, className),0,0},
    {MFT_POINTER,offsetof(SubscribeReq, filter),0,0},
    {MFT_POINTER,offsetof(SubscribeReq, language),0,0},
    {MFT_END_OF_LIST, 0, 0, 0}
};

static const MessageField subscribeResponseMessageFields[] =
{
    {MFT_POINTER,offsetof(SubscribeRes, subscriptionID),0,0},
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
    {MFT_END_OF_LIST, 0, 0, 0}
};

/* Entries in this array corresponds to MessageTag values:
    GetInstanceReqTag = 1,
    PostInstanceMsgTag = 2,
    EnumerateInstancesReqTag = 3,
    PostResultMsgTag = 4,
    NoOpReqTag = 5,
    NoOpRspTag = 6,
    DispResultMsgTag = 7,
    InvokeReqTag = 8,
    AssociatorsOfReqTag = 9,
    ReferencesOfReqTag = 10,
    SubscribeReqTag = 11,
    SubscribeResTag = 12,
    DeleteInstanceReqTag = 13,
    CreateInstanceReqTag = 14,
    ModifyInstanceReqTag = 15,
    BinProtocolNotificationTag = 16
*/
typedef struct _MessageDeclaration
{
    const MessageField* fields;
    size_t              size;
    MI_Boolean          cloneRequired;
}
MessageDeclaration;

static const MessageDeclaration allMessages[] = {
    {baseMessageFields,                 0,                       MI_FALSE},
    {getInstanceMessageFields,          sizeof(GetInstanceReq),   MI_TRUE},
    {postInstanceMessageFields,         sizeof(PostInstanceMsg),        MI_TRUE},
    {enumerateInstancesMessageFields,   sizeof(EnumerateInstancesReq),      MI_FALSE},
    {binPostResultMsgFields,            sizeof(PostResultMsg),      MI_FALSE},
    {emptyMessageFields,                sizeof(NoOpReq),        MI_FALSE},
    {emptyMessageFields,                sizeof(NoOpRsp),        MI_FALSE},
    {emptyMessageFields,                sizeof(DispResultMsg),      MI_FALSE},
    {invokeMessageFields,               sizeof(InvokeReq),      MI_TRUE},
    {associatorsOfMessageFields,        sizeof(AssociationsOfReq),       MI_TRUE},
    {referencesOfMessageFields,         sizeof(AssociationsOfReq),        MI_TRUE},
    {subscribeRequestMessageFields,     sizeof(SubscribeReq),       MI_FALSE},
    {subscribeResponseMessageFields,    sizeof(SubscribeRes),       MI_FALSE},
    {deleteInstanceMessageFields,       sizeof(DeleteInstanceReq),      MI_TRUE},
    {createInstanceMessageFields,       sizeof(CreateInstanceReq),      MI_TRUE},
    {modifyInstanceMessageFields,       sizeof(ModifyInstanceReq),      MI_TRUE},
    {binProtocolNotificationFields,     sizeof(BinProtocolNotification),MI_FALSE}
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
    MI_Uint64 msgID,
    MI_Uint32 flags)
{
    Batch *batch;
    Message* self;

    batch = Batch_New(BATCH_MAX_PAGES);

    if (!batch)
        return NULL;

    /* Allocate heap space for message */
    self = Batch_Get(batch, structSize);

    if (!self)
        return NULL;

    /* Clear all fields */
    memset(self, 0, structSize);

    /* Set the tag */
    self->tag = tag;

    /* Set the message id and flags */
    self->msgID = msgID;
    self->flags = flags;

    /* ref-counter is set to 1, to balance NewMessage/Release Message pair*/
    self->refCounter = 1;

    /* Copy batch onto message (released by delete method) */
    self->batch = batch;

    return self;
}

/*
    Decrements message's ref-counter and destroys
    mesage if last reference was released
    Parameters:
    self - message to decref/release
*/
void Message_Release(
    Message* self)
{
    if (AtomicDec(&self->refCounter))
    {
        /* Call destructor */
        if (self->dtor)
            (*self->dtor)(self, self->dtorData);

        /* Release linked request */
        if (self->request)
            Message_Release(self->request);

        Batch_Destroy(self->batch);
    }
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
                    ptr))
                        return MI_RESULT_INVALID_PARAMETER;
            }
            else if (messageFields->type == MFT_POINTER)
                return MI_RESULT_INVALID_PARAMETER;

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
                        ptrPacked))
                        return MI_RESULT_INVALID_PARAMETER;

                    if (!skipInstanceUnpack && !_UnpackInstance(
                        batch,
                        *ptrPacked,
                        packedSize,
                        (MI_Instance**)ptr))
                        return MI_RESULT_INVALID_PARAMETER;
                }
                else if (messageFields->type == MFT_INSTANCE)
                    return MI_RESULT_INVALID_PARAMETER;

            }

            break;

        default:
            break;
        }

        messageFields++;
    }

    return MI_RESULT_OK;
}

static MI_Result _Clone(
    const Message* msgSrc,
    Message* msg,
    const MessageField* messageFields,
    size_t size)
{
    char* chunk = (char*)msg;
    Batch* batch = msg->batch;
    const char* chunkSrc = (const char*)msgSrc;

    /* copy all primitve data first */
    memcpy(chunk + sizeof(Message), chunkSrc + sizeof(Message), size - sizeof(Message));

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
                    *ptr = Batch_Zdup(batch, (const ZChar*)*ptrSrc);

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

MI_Result MessageFromBatch(
    Batch* batch,
    void* originalMsgPtr,
    const Header_BatchInfoItem* ptrAdjustmentInfo,
    size_t ptrAdjustmentInfoCount,
    MI_Boolean skipInstanceUnpack,
    Message** msgOut)
{
    Message* msg = originalMsgPtr;
    MI_Uint32 index;

    if (!Batch_FixPointer(
        batch,
        ptrAdjustmentInfo,
        ptrAdjustmentInfoCount,
        (void*)&msg))
        return MI_RESULT_INVALID_PARAMETER;

    /* fix base part of message */
    msg->batch = batch;
    msg->refCounter = 1;

    if (MI_RESULT_OK != _RestoreMessage(
        msg,
        ptrAdjustmentInfo,
        ptrAdjustmentInfoCount,
        skipInstanceUnpack,
        baseMessageFields))
        return MI_RESULT_INVALID_PARAMETER;

    index = (MI_Uint32)msg->tag;

    if (index >= MI_COUNT(allMessages))
        return MI_RESULT_INVALID_PARAMETER;

    if (MI_RESULT_OK != _RestoreMessage(
        msg,
        ptrAdjustmentInfo,
        ptrAdjustmentInfoCount,
        skipInstanceUnpack,
        allMessages[index].fields))
        return MI_RESULT_INVALID_PARAMETER;

    *msgOut = msg;
    return MI_RESULT_OK;
}

MI_Result MessagePackCloneForBinarySending(
    Message* msgSrc,
    Message** msgOut)
{
    Message* msg = msgSrc;
    MI_Uint32 index;

    index = (MI_Uint32)msg->tag;

    if (index >= MI_COUNT(allMessages))
        return MI_RESULT_INVALID_PARAMETER;

    if (!allMessages[index].cloneRequired)
    {
        *msgOut = msg;
        Message_AddRef(msg);
        return MI_RESULT_OK;
    }

    /* create a copy */
    msg = __Message_New(msgSrc->tag, allMessages[index].size, msgSrc->msgID, msgSrc->flags);

    if (!msg)
        return MI_RESULT_FAILED;

    msg->clientID = msgSrc->clientID;

    if (MI_RESULT_OK != _Clone(msgSrc, msg, allMessages[index].fields, allMessages[index].size))
    {
        Message_Release(msg);
        return MI_RESULT_FAILED;
    }

    *msgOut = msg;
    return MI_RESULT_OK;
}
