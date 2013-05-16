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

#ifndef _omi_messages_h
#define _omi_messages_h

#include "config.h"
#include <common.h>
#include <stdio.h>
#include "batch.h"
#include "instance.h"
#include "stringarray.h"
#include "atomic.h"
#include "user.h"

BEGIN_EXTERNC

/*
**==============================================================================
**
** MessageTag
**
**     Enumeration of all message tags.
**
**==============================================================================
*/

typedef enum _MessageTag
{
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
}
MessageTag;

/*
**==============================================================================
**
** MessageFlag
**
**     Supported flags for message.
**
**==============================================================================
*/

typedef enum _MessageFlag
{
    /* Instance encoding type (only one can be set at a time) */
    BinaryProtocolFlag =    0x0001,
    WSMANFlag =             0x0002,
    CIMXMLFlag =            0x0004,

    /* WSMAN-specific encoding options */
    WSMAN_ObjectAndEPRFlag =0x0018,
    WSMAN_EPRFlag =         0x0008,
    WSMAN_ObjectFlag =      0x0010,
    WSMAN_CreatedEPRFlag =  0x0020,

    /* Is encoded instance a CIM_Error */
    WSMAN_IsCimError =      0x2000
}
MessageFlag;

/*
**==============================================================================
**
** enum UserAgent
**
**==============================================================================
*/

typedef enum _UserAgent
{
    USERAGENT_UNKNOWN,
    USERAGENT_WINRM
}
UserAgent;

/*
**==============================================================================
**
** Message
**
**     Base type for all messages.
**
**==============================================================================
*/

typedef struct _Message Message;

struct _Message
{
    /* Links for inserting messages onto linked-lists */
    struct _Message* next;
    struct _Message* prev;

    /* The batch this message was allocated from */
    Batch *batch;

    /* original request (can be NULL); lifetime controlled by ref-counter */
    struct _Message* request;

    /* The message tag (see MessageTag enum above) */
    MI_Uint32 tag;

    /* Flags for message processing - like instance encoding type (see MessageFlag enum above) */
    MI_Uint32 flags;

    /* ref counter */
    AtomicInt refCounter;

    /* Message identifier derived from the original request */
    MI_Uint64 msgID;

    /* Client identifier derived from requestor */
    MI_Uint64 clientID;

    /* Callback used to deliver response to this message */
    void (*callback)(Message* message, void* callbackData);

    /* Data passed as 2nd argument of 'callback' */
    void* callbackData;

    /* Message's destructor [opt]
        'Release' will call dtor (if set) right before destroying the message */
    void (*dtor)(Message* message, void* callbackData);

    /* Data passed as 2nd argument of 'dtor' */
    void* dtorData;

    /* Server -> agent IPC specific */
    const char* libraryName;

    /* Requestor information */
    uid_t uid;
    gid_t gid;

    /* Name of HTTP usre agent */
    MI_Uint32 userAgent;
};

Message* __Message_New(
    MessageTag tag,
    size_t structSize,
    MI_Uint64 msgID,
    MI_Uint32 flags);

void Message_Release(
    Message* self);

MI_INLINE void Message_AddRef(
    Message* self)
{
    AtomicInc(&self->refCounter);
}

MI_INLINE void Message_SetRequest(
    Message* self,
    Message* request)
{
    if (self->request)
        Message_Release(self->request);

    self->request = request;

    if (self->request)
        Message_AddRef(self->request);
}

/*
    Verifies if message is final reposne to the initial request
*/
MI_INLINE MI_Boolean Message_IsFinalRepsonse(
    const Message* msg)
{
    if (PostResultMsgTag == msg->tag ||
        NoOpRspTag == msg->tag ||
        SubscribeResTag == msg->tag)
        return MI_TRUE;

    return MI_FALSE;
}

/*
**==============================================================================
**
** PostResultMsg
**
**     generic error response
**
**==============================================================================
*/

typedef struct _PostResultMsg
{
    Message base;
    MI_Result result;
    const ZChar* errorMessage;
    const MI_Instance* cimError;
    void* packedInstancePtr; /* Used for packing error across protocols */
    MI_Uint32 packedInstanceSize; /* Used for packing error across protocols */
}
PostResultMsg;

MI_INLINE PostResultMsg* PostResultMsg_New(
    MI_Uint64 msgID)
{
    return (PostResultMsg*)__Message_New(
        PostResultMsgTag, sizeof(PostResultMsg), msgID, 0);
}

MI_INLINE void PostResultMsg_Release(
    PostResultMsg* self)
{
    Message_Release(&self->base);
}

void PostResultMsg_Print(const PostResultMsg* msg, FILE* os);

/*
**==============================================================================
**
** DispResultMsg
**
**     internal structure for dispatcher
**     dispatcher keeps track of multiple 'enumerate' responses
**
**==============================================================================
*/

typedef struct _DispResultMsg
{
    Message base;

    /* number of outstanding requests */
    AtomicInt requestCounter;

    /* current result */
    MI_Result result;
}
DispResultMsg;

MI_INLINE DispResultMsg* DispResultMsg_New(
    MI_Uint64 msgID)
{
    return (DispResultMsg*)__Message_New(
        DispResultMsgTag, sizeof(DispResultMsg), msgID, 0);
}

MI_INLINE void DispResultMsg_Release(
    DispResultMsg* self)
{
    Message_Release(&self->base);
}

void DispResultMsg_Print(const DispResultMsg* msg, FILE* os);

/*
**==============================================================================
**
** GetInstanceReq
**
**     A CIM GetInstance request (see DSP0200).
**
**==============================================================================
*/

typedef struct _GetInstanceReq
{
    Message base;
    MI_ConstString nameSpace;
    /* un-packed version of instance */
    MI_Instance* instanceName;
    /* packed version of instance */
    void*        packedInstanceNamePtr;
    MI_Uint32    packedInstanceNameSize;

    MI_Boolean includeClassOrigin;
    StringArray* propertySet;
}
GetInstanceReq;

MI_INLINE GetInstanceReq* GetInstanceReq_New(
    MI_Uint64 msgID,
    MI_Uint32 flags)
{
    return (GetInstanceReq*)__Message_New(
        GetInstanceReqTag, sizeof(GetInstanceReq), msgID, flags);
}

MI_INLINE void GetInstanceReq_Release(
    GetInstanceReq* self)
{
    Message_Release(&self->base);
}

void GetInstanceReq_Print(const GetInstanceReq* msg, FILE* os);

/*
**==============================================================================
**
** CreateInstanceReq
**
**     A CIM CreateInstance request (see DSP0200).
**
**==============================================================================
*/

typedef struct _CreateInstanceReq
{
    Message base;
    MI_ConstString nameSpace;
    MI_Instance* instance;
    void* packedInstancePtr;
    MI_Uint32 packedInstanceSize;
    StringArray* propertySet;
}
CreateInstanceReq;

MI_INLINE CreateInstanceReq* CreateInstanceReq_New(
    MI_Uint64 msgID,
    MI_Uint32 flags)
{
    return (CreateInstanceReq*)__Message_New(
        CreateInstanceReqTag, sizeof(CreateInstanceReq), msgID, flags);
}

MI_INLINE void CreateInstanceReq_Release(
    CreateInstanceReq* self)
{
    Message_Release(&self->base);
}

void CreateInstanceReq_Print(const CreateInstanceReq* msg, FILE* os);

/*
**==============================================================================
**
** ModifyInstanceReq
**
**     A CIM ModifyInstance request (see DSP0200).
**
**==============================================================================
*/

typedef struct _ModifyInstanceReq
{
    Message base;
    MI_ConstString nameSpace;
    MI_Instance* instance;
    void* packedInstancePtr;
    MI_Uint32 packedInstanceSize;
    StringArray* propertySet;
}
ModifyInstanceReq;

MI_INLINE ModifyInstanceReq* ModifyInstanceReq_New(
    MI_Uint64 msgID,
    MI_Uint32 flags)
{
    return (ModifyInstanceReq*)__Message_New(
        ModifyInstanceReqTag, sizeof(ModifyInstanceReq), msgID, flags);
}

MI_INLINE void ModifyInstanceReq_Release(
    ModifyInstanceReq* self)
{
    Message_Release(&self->base);
}

void ModifyInstanceReq_Print(const ModifyInstanceReq* msg, FILE* os);

/*
**==============================================================================
**
** DeleteInstanceReq
**
**     A CIM DeleteInstance request (see DSP0200).
**
**==============================================================================
*/

typedef struct _DeleteInstanceReq
{
    Message base;
    MI_ConstString nameSpace;
    MI_Instance* instanceName;
    void* packedInstanceNamePtr;
    MI_Uint32 packedInstanceNameSize;
}
DeleteInstanceReq;

MI_INLINE DeleteInstanceReq* DeleteInstanceReq_New(
    MI_Uint64 msgID,
    MI_Uint32 flags)
{
    return (DeleteInstanceReq*)__Message_New(
        DeleteInstanceReqTag, sizeof(DeleteInstanceReq), msgID, flags);
}

MI_INLINE void DeleteInstanceReq_Release(
    DeleteInstanceReq* self)
{
    Message_Release(&self->base);
}

void DeleteInstanceReq_Print(
    const DeleteInstanceReq* msg,
    FILE* os);

/*
**==============================================================================
**
** InvokeReq
**
**     A CIM Invoke request (see DSP0200).
**
**==============================================================================
*/

typedef struct _InvokeReq
{
    Message base;
    MI_ConstString nameSpace;
    MI_ConstString function;
    MI_ConstString className; /* for static functions only, otherwise null */

    /* un-packed version of instance (for non-static functions) and parameters */
    MI_Instance* instance;
    MI_Instance* instanceParams;
    /* packed version of instance */
    void*        packedInstancePtr;
    void*        packedInstanceParamsPtr;
    MI_Uint32    packedInstanceSize;
    MI_Uint32    packedInstanceParamsSize;
}
InvokeReq;

MI_INLINE InvokeReq* InvokeReq_New(
    MI_Uint64 msgID,
    MI_Uint32 flags)
{
    return (InvokeReq*)__Message_New(
        InvokeReqTag, sizeof(InvokeReq), msgID, flags);
}

MI_INLINE void InvokeReq_Release(
    InvokeReq* self)
{
    Message_Release(&self->base);
}

void InvokeReq_Print(const InvokeReq* msg, FILE* os);

/*
**==============================================================================
**
** AssociationsOfReq
**
**     A CIM "Associators of" request (see DSP0200).
**
** AND
**
** ReferencesOfReq
**
**     A CIM "References of" request (see DSP0200).
**
**
**==============================================================================
*/

typedef struct _AssociationsOfReq
{
    Message base;
    MI_ConstString nameSpace;
    MI_ConstString assocClass;
    MI_ConstString resultClass;
    MI_ConstString role;
    MI_ConstString resultRole;

    /* dispatcher to provider only */
    MI_ConstString className;

    /* un-packed version of instance */
    MI_Instance* instance;
    /* packed version of instance */
    void*        packedInstancePtr;
    MI_Uint32    packedInstanceSize;
}
AssociationsOfReq;

MI_INLINE AssociationsOfReq* AssociationsOfReq_New(
    MI_Uint64 msgID,
    MI_Uint32 flags,
    MessageTag tag)
{
    return (AssociationsOfReq*)__Message_New(
        tag, sizeof(AssociationsOfReq), msgID, flags);
}

MI_INLINE void AssociationsOfReq_Release(
    AssociationsOfReq* self)
{
    Message_Release(&self->base);
}

void AssociatorsOfReq_Print(const AssociationsOfReq* msg, FILE* os);

void ReferencesOfReq_Print(const AssociationsOfReq* msg, FILE* os);

/*
**==============================================================================
**
** PostInstanceMsg
**
**     A CIM GetInstance response (see DSP0200).
**
**==============================================================================
*/

typedef struct _PostInstanceMsg
{
    Message base;
    /* un-packed version of instance */
    MI_Instance* instance;
    /* packed version of instance */
    void*        packedInstancePtr;
    MI_Uint32    packedInstanceSize;

}
PostInstanceMsg;

MI_INLINE PostInstanceMsg* PostInstanceMsg_New(
    MI_Uint64 msgID)
{
    return (PostInstanceMsg*)__Message_New(
        PostInstanceMsgTag, sizeof(PostInstanceMsg), msgID, 0);
}

MI_INLINE void PostInstanceMsg_Release(
    PostInstanceMsg* self)
{
    Message_Release(&self->base);
}

void PostInstanceMsg_Print(const PostInstanceMsg* msg, FILE* os);

/*
**==============================================================================
**
** EnumerateInstancesReq
**
**     A CIM EnumerateInstances request (see DSP0200).
**
**==============================================================================
*/

typedef struct _EnumerateInstancesReq
{
    Message base;
    MI_ConstString nameSpace;
    MI_ConstString className;
    /* Used for 'base-properties-only' mode to transfer
        request's class-name */
    MI_ConstString requestClassName;
    StringArray* propertySet;
    MI_Boolean deepInheritance;
    MI_Boolean includeClassOrigin;
    MI_Boolean basePropertiesOnly;

    /* Query language (or null none) */
    const ZChar* queryLanguage;

    /* Query expression (or null none) */
    const ZChar* queryExpression;

    /* Compiled WQL query */
    struct _WQL* wql;
}
EnumerateInstancesReq;

MI_INLINE EnumerateInstancesReq* EnumerateInstancesReq_New(
    MI_Uint64 msgID,
    MI_Uint32 flags)
{
    return (EnumerateInstancesReq*)__Message_New(
        EnumerateInstancesReqTag, sizeof(EnumerateInstancesReq), msgID, flags);
}

MI_INLINE void EnumerateInstancesReq_Release(
    EnumerateInstancesReq* self)
{
    Message_Release(&self->base);
}

void EnumerateInstancesReq_Print(const EnumerateInstancesReq* msg, FILE* os);

/*
**==============================================================================
**
** SubscribeReq
**
**     Subscribe request (internal representation of it)
**
**==============================================================================
*/

typedef struct _SubscribeReq
{
    Message base;
    MI_ConstString nameSpace;
    MI_ConstString className;
    MI_ConstString filter;
    MI_ConstString language;

    /* used for disp -> provmgr */
    MI_Uint64      ctxID;
    /* used for disp -> provider */
    MI_Uint64      subscriptionID;
}
SubscribeReq;

MI_INLINE SubscribeReq* SubscribeReq_New(
    MI_Uint64 msgID,
    MI_Uint32 flags)
{
    return (SubscribeReq*)__Message_New(
        SubscribeReqTag, sizeof(SubscribeReq), msgID, flags);
}

MI_INLINE void SubscribeReq_Release(
    SubscribeReq* self)
{
    Message_Release(&self->base);
}

void SubscribeReq_Print(const SubscribeReq* msg, FILE* os);

/*
**==============================================================================
**
** SubscribeRes
**
**     Subscribe request (internal representation of it)
**
**==============================================================================
*/

typedef struct _SubscribeRes
{
    Message base;
    MI_ConstString subscriptionID;
}
SubscribeRes;

MI_INLINE SubscribeRes* SubscribeRes_New(
    MI_Uint64 msgID)
{
    return (SubscribeRes*)__Message_New(
        SubscribeResTag, sizeof(SubscribeRes), msgID, 0);
}

MI_INLINE void SubscribeRes_Release(
    SubscribeRes* self)
{
    Message_Release(&self->base);
}

void SubscribeRes_Print(const SubscribeRes* msg, FILE* os);

/*
**==============================================================================
**
** NoOpReq
**
**     A NoOp request.
**
**==============================================================================
*/

typedef struct _NoOpReq
{
    Message base;
}
NoOpReq;

MI_INLINE NoOpReq* NoOpReq_New(
    MI_Uint64 msgID)
{
    return (NoOpReq*)__Message_New(
        NoOpReqTag, sizeof(NoOpReq), msgID, BinaryProtocolFlag);
}

MI_INLINE void NoOpReq_Release(
    NoOpReq* self)
{
    Message_Release(&self->base);
}

void NoOpReq_Print(const NoOpReq* msg, FILE* os);

/*
**==============================================================================
**
** NoOpRsp
**
**     A NoOp request.
**
**==============================================================================
*/

typedef struct _NoOpRsp
{
    Message base;
}
NoOpRsp;

MI_INLINE NoOpRsp* NoOpRsp_New(
    MI_Uint64 msgID)
{
    return (NoOpRsp*)__Message_New(
        NoOpRspTag, sizeof(NoOpRsp), msgID, 0);
}

MI_INLINE void NoOpRsp_Release(
    NoOpRsp* self)
{
    Message_Release(&self->base);
}

void NoOpRsp_Print(const NoOpRsp* msg, FILE* os);

/*
**==============================================================================
**
** BinProtocolNotification
**
**     A internal notification transfered over bin protocol.
**
**==============================================================================
*/
typedef enum _BinProtNotificationType
{
    BinNotificationAgentIdle = 0,
    BinNotificationConnectRequest = 1,
    BinNotificationConnectResponse = 2
}
BinProtNotificationType;

#define AUTH_RANDOM_DATA_SIZE   64

typedef struct _BinProtocolNotification
{
    Message base;

    /* see BinProtNotificationType for supported types */
    MI_Uint32   type;

    /* **** Connect-request specific data **** */
    /* explicit auth [opt] */
    const char* user;
    const char* password;

    /* implicit auth - Requestor information */
    uid_t uid;
    gid_t gid;

    /* File-based authentication - files's content */
    unsigned char authData[AUTH_RANDOM_DATA_SIZE];

    /* **** Connect-response specific data **** */
    /* ok/access-denied */
    MI_Result   result;

    /* file name - client has to read it and send back content */
    const char* authFile;

}
BinProtocolNotification;

MI_INLINE BinProtocolNotification* BinProtocolNotification_New(BinProtNotificationType type)
{
    BinProtocolNotification* res = (BinProtocolNotification*)__Message_New(
        BinProtocolNotificationTag, sizeof(BinProtocolNotification), 0, 0);

    if (res)
        res->type = type;

    return res;
}

MI_INLINE void BinProtocolNotification_Release(
    BinProtocolNotification* self)
{
    Message_Release(&self->base);
}

void BinProtocolNotification_Print(const BinProtocolNotification* msg, FILE* os);

/*
**==============================================================================
**
**     binary transport with batch support
**
**
**
**==============================================================================
*/

MI_Result MessageFromBatch(
    Batch* batch,
    void* originalMsgPtr,
    const Header_BatchInfoItem* ptrAdjustmentInfo,
    size_t ptrAdjustmentInfoCount,
    MI_Boolean skipInstanceUnpack,
    Message** msgOut
    );


/*
**==============================================================================
**
**     Creates a clone of given message,
**      suitable for sending with binary protocol
**      This is needed to:
**      - make batch smaller (no small blocks form instance's parts
**      - all instances are packed
**
**      Note: requests without instances (like Enum) don't need a copy -
**      add-ref-ed original message is returned in that case
**
**==============================================================================
*/
MI_Result MessagePackCloneForBinarySending(
    Message* msgSrc,
    Message** msgOut);


/*
**==============================================================================
**
** Print the message
**
**==============================================================================
*/
void MessagePrint(const Message* msg, FILE* os);

/*
**==============================================================================
**
** Uint64ToPtr()
** PtrToUint64()
**
**==============================================================================
*/

MI_INLINE void* Uint64ToPtr(MI_Uint64 x)
{
    union U
    {
        void* ptr;
        MI_Uint64 x;
    };

    union U u;
    u.x = x;

    return u.ptr;
}

MI_INLINE MI_Uint64 PtrToUint64(void* ptr)
{
    union U
    {
        void* ptr;
        MI_Uint64 x;
    };

    union U u;
    u.ptr = ptr;

    return u.x;
}

END_EXTERNC

#endif /* _omi_messages_h */
