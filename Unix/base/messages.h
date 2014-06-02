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
#include <pal/atomic.h>
#include "user.h"
#include <pal/thread.h>

BEGIN_EXTERNC

/*
**==============================================================================
**
** MessageTag
**
**     Enumeration of all message tags.
**
** If adding here don't forget to add also to allMessages[] 
** and _MsgNames[] on messages.c
**
**==============================================================================
*/

#define MessageTagIndexMask 0x0FFF
#define MessageTagIsRequest 0x1000

typedef enum _MessageTag
{
    GetInstanceReqTag = 1 | MessageTagIsRequest,
    PostInstanceMsgTag = 2,
    EnumerateInstancesReqTag = 3 | MessageTagIsRequest,
    PostResultMsgTag = 4,
    NoOpReqTag = 5 | MessageTagIsRequest,
    NoOpRspTag = 6,
    InvokeReqTag = 7 | MessageTagIsRequest,
    AssociatorsOfReqTag = 8 | MessageTagIsRequest,
    ReferencesOfReqTag = 9 | MessageTagIsRequest,
    SubscribeReqTag = 10 | MessageTagIsRequest,
    UnsubscribeReqTag = 11 | MessageTagIsRequest,
    DeleteInstanceReqTag = 12 | MessageTagIsRequest,
    CreateInstanceReqTag = 13 | MessageTagIsRequest,
    ModifyInstanceReqTag = 14 | MessageTagIsRequest,
    BinProtocolNotificationTag = 15,
    GetClassReqTag = 16 | MessageTagIsRequest,
    PostSchemaMsgTag = 17,
    HttpRequestMsgTag = 18,
    HttpResponseMsgTag = 19,
    PostIndicationMsgTag = 20,
    SubscribeResTag = 21,
    CancelMsgTag = 22,
    ProtocolEventConnectTag = 23
}
MessageTag;

#define MessageTagIndex( messageTag )   ( (messageTag) & MessageTagIndexMask )

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

    /* WSMAN-Schema retrieval specific encoding options */
    WSMAN_IncludeClassOrigin =          0x0100,
    WSMAN_IncludeInheritanceHierarchy = 0x0200,
    WSMAN_IncludeInheritedElements =    0x0400,
    WSMAN_IncludeQualifiers =           0x0800,

    /* WSMAN-Instance operation specific encoding options used by WinRM */
    WSMAN_UsePreciseArrays =            0x1000,

    /* Is encoded instance a CIM_Error */
    WSMAN_IsCimError =                  0x2000
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

//TODO delete fields once Interaction is applied everywhere
struct _Message
{
    /* Links for inserting messages onto linked-lists */
    struct _Message* next;
    struct _Message* prev;

    /* The batch this message was allocated from */
    Batch *batch;

    /* The message tag (see MessageTag enum above) */
    MI_Uint32 tag;

    /* Flags for message processing - like instance encoding type (see MessageFlag enum above) */
    MI_Uint32 flags;

    /* ref counter */
    volatile ptrdiff_t refCounter;

    /* The arguments for this message */
    MI_Uint64 argPtr;

    /* The client that created this message */
    MI_Uint64 clientId;

    /* Operation identifier derived from the original request */
    /* identifies a particular operation in a particular link */
    /* i.e: client-server or server-agent */
    MI_Uint64 operationId;

    /* Message's destructor [opt] 
        'Release' will call dtor (if set) right before destroying the message */
    void (*dtor)(Message* message, void* callbackData);

    /* Data passed as 2nd argument of 'dtor' */
    void* dtorData;
};

Message* __Message_New(
    MessageTag tag,
    size_t structSize,
    MI_Uint64 operationId,
    MI_Uint32 flags,
    CallSite cs);

#define Message_Release(self) \
    __Message_Release(self, CALLSITE)

void __Message_Release(
    Message* self,
    CallSite cs);

#define Message_AddRef(self) \
    __Message_AddRef(self, CALLSITE)

void __Message_AddRef(
    Message* self,
    CallSite cs);

/*
    Verifies if message is final reposne to the initial request
*/
MI_INLINE MI_Boolean Message_IsFinalResponse(
    const Message* msg)
{
    if (PostResultMsgTag == msg->tag ||
        NoOpRspTag == msg->tag)
        return MI_TRUE;

    return MI_FALSE;
}

// If the message is derived from RequestMsg
MI_INLINE MI_Boolean MessageTag_IsRequest(
    MI_Uint32 msgTag )
{
    return ( ( msgTag & MessageTagIsRequest ) != 0 );
}

MI_INLINE MI_Boolean Message_IsRequest(
    const Message* msg)
{
    return MessageTag_IsRequest( msg->tag );
}

/*
**==============================================================================
*/

typedef struct _AuthInfo
{
    // Linux version
    uid_t uid;
    gid_t gid;
}
AuthInfo;

MI_INLINE void AuthInfo_Copy(
    _Out_ AuthInfo* dest,
    _In_ AuthInfo* src)
{
    memcpy( dest, src, sizeof( AuthInfo ) );
}

/*
**==============================================================================
**
** RequestMsg
**
**     Requests messages types derive from this
**
**==============================================================================
*/
typedef struct _RequestMsg
{
    Message         base;
    AuthInfo        authInfo;
    /* Name of HTTP user agent */
    MI_Uint32       userAgent;
    /* Server -> agent IPC specific */
    const char *libraryName;
    MI_Boolean instanceLifetimeContext;
    /*
    ** Options used by these methods:
    **     MI_Context_GetStringOption()
    **     MI_Context_GetNumberOption()
    **     MI_Context_GetCustomOption()
    **     MI_Context_GetCustomOptionCount()
    **     MI_Context_GetCustomOptionAt()
    */
    MI_Instance*    options;
    void*           packedOptionsPtr;
    MI_Uint32       packedOptionsSize;
}
RequestMsg;
    

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
    Message         base;
    MI_Result       result;
    const ZChar*    errorMessage;
    const MI_Instance* cimError;
    const ZChar*    cimErrorClassName;
    void*           packedInstancePtr; /* Used for packing error across protocols */
    MI_Uint32       packedInstanceSize; /* Used for packing error across protocols */
}
PostResultMsg;

#define PostResultMsg_New(operationId) \
    __PostResultMsg_New(operationId, CALLSITE)

MI_INLINE PostResultMsg* __PostResultMsg_New(
    MI_Uint64 operationId,
    CallSite cs)
{
    return (PostResultMsg*)__Message_New(
        PostResultMsgTag, sizeof(PostResultMsg), operationId, 0,
        cs);
}

#define PostResultMsg_Release(self) \
    __PostResultMsg_Release(self, CALLSITE)

MI_INLINE void __PostResultMsg_Release(
    PostResultMsg* self,
    CallSite cs)
{
    __Message_Release(&self->base, cs);
}

void PostResultMsg_Print(const PostResultMsg* msg, FILE* os);

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
    RequestMsg      base;
    MI_ConstString  nameSpace;
    /* un-packed version of instance */
    MI_Instance*    instanceName;
    /* packed version of instance */
    void*           packedInstanceNamePtr;
    MI_Uint32       packedInstanceNameSize;

    MI_Boolean      includeClassOrigin;
    StringArray*    propertySet;
}
GetInstanceReq;

#define GetInstanceReq_New(operationId, flags) \
    __GetInstanceReq_New(operationId, flags, CALLSITE)


MI_INLINE GetInstanceReq* __GetInstanceReq_New(
    MI_Uint64 operationId,
    MI_Uint32 flags,
    CallSite cs)
{
    return (GetInstanceReq*)__Message_New(
        GetInstanceReqTag, sizeof(GetInstanceReq), operationId, flags,
        cs);
}

#define GetInstanceReq_Release(self) \
    __GetInstanceReq_Release(self, CALLSITE)

MI_INLINE void __GetInstanceReq_Release(
    GetInstanceReq* self,
    CallSite cs)
{
    __Message_Release(&self->base.base, cs);
}

void GetInstanceReq_Print(const GetInstanceReq* msg, FILE* os);

/*
**==============================================================================
**
** GetClassReq
**
**     A CIM GetClass request 
**
**==============================================================================
*/

typedef struct _GetClassReq
{
    RequestMsg      base;
    MI_ConstString  nameSpace;
    MI_ConstString  className;
}
GetClassReq;

#define GetClassReq_New(operationId, flags) \
    __GetClassReq_New(operationId, flags, CALLSITE)

MI_INLINE GetClassReq* __GetClassReq_New(
    MI_Uint64 operationId,
    MI_Uint32 flags,
    CallSite cs)
{
    return (GetClassReq*)__Message_New(
        GetClassReqTag, sizeof(GetClassReq), operationId, flags,
        cs);
}

#define GetClassReq_Release(self) \
    __GetClassReq_Release(self, CALLSITE)

MI_INLINE void __GetClassReq_Release(
    GetClassReq* self,
    CallSite cs)
{
    __Message_Release(&self->base.base, cs);
}

void GetClassReq_Print(const GetClassReq* msg, FILE* os);


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
    RequestMsg      base;
    MI_ConstString  nameSpace;
    MI_Instance*    instance;
    void*           packedInstancePtr;
    MI_Uint32       packedInstanceSize;
    StringArray*    propertySet;
}
CreateInstanceReq;

#define CreateInstanceReq_New(operationId, flags) \
    __CreateInstanceReq_New(operationId, flags, CALLSITE)

MI_INLINE CreateInstanceReq* __CreateInstanceReq_New(
    MI_Uint64 operationId,
    MI_Uint32 flags,
    CallSite cs)
{
    return (CreateInstanceReq*)__Message_New(
        CreateInstanceReqTag, sizeof(CreateInstanceReq), operationId, flags,
        cs);
}

#define CreateInstanceReq_Release(self) \
    __CreateInstanceReq_Release(self, CALLSITE)

MI_INLINE void __CreateInstanceReq_Release(
    CreateInstanceReq* self,
    CallSite cs)
{
    __Message_Release(&self->base.base, cs);
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
    RequestMsg      base;
    MI_ConstString  nameSpace;
    MI_Instance*    instance;
    void*           packedInstancePtr;
    MI_Uint32       packedInstanceSize;
    StringArray*    propertySet;
}
ModifyInstanceReq;

#define ModifyInstanceReq_New(operationId, flags) \
    __ModifyInstanceReq_New(operationId, flags, CALLSITE)


MI_INLINE ModifyInstanceReq* __ModifyInstanceReq_New(
    MI_Uint64 operationId,
    MI_Uint32 flags,
    CallSite cs)
{
    return (ModifyInstanceReq*)__Message_New(
        ModifyInstanceReqTag, sizeof(ModifyInstanceReq), operationId, flags,
        cs);
}

#define ModifyInstanceReq_Release(self) \
    __ModifyInstanceReq_Release(self, CALLSITE)

MI_INLINE void __ModifyInstanceReq_Release(
    ModifyInstanceReq* self,
    CallSite cs)
{
    __Message_Release(&self->base.base, cs);
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
    RequestMsg      base;
    MI_ConstString  nameSpace;
    MI_Instance*    instanceName;
    void*           packedInstanceNamePtr;
    MI_Uint32       packedInstanceNameSize;
}
DeleteInstanceReq;

#define DeleteInstanceReq_New(operationId, flags) \
    __DeleteInstanceReq_New(operationId, flags, CALLSITE)

MI_INLINE DeleteInstanceReq* __DeleteInstanceReq_New(
    MI_Uint64 operationId,
    MI_Uint32 flags,
    CallSite cs)
{
    return (DeleteInstanceReq*)__Message_New(
        DeleteInstanceReqTag, sizeof(DeleteInstanceReq), operationId, flags,
        cs);
}

#define DeleteInstanceReq_Release(self) \
    __DeleteInstanceReq_Release(self, CALLSITE)

MI_INLINE void __DeleteInstanceReq_Release(
    DeleteInstanceReq* self,
    CallSite cs)
{
    __Message_Release(&self->base.base, cs);
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
    RequestMsg      base;
    MI_ConstString  nameSpace;
    MI_ConstString  function;
    MI_ConstString  className; /* for static functions only, otherwise null */

    /* un-packed version of instance (for non-static functions) and parameters */
    MI_Instance*    instance;
    MI_Instance*    instanceParams;
    /* packed version of instance */
    void*           packedInstancePtr;
    void*           packedInstanceParamsPtr;
    MI_Uint32       packedInstanceSize;
    MI_Uint32       packedInstanceParamsSize;
}
InvokeReq;

#define InvokeReq_New(operationId, flags) \
    __InvokeReq_New(operationId, flags, CALLSITE)

MI_INLINE InvokeReq* __InvokeReq_New(
    MI_Uint64 operationId,
    MI_Uint32 flags,
    CallSite cs)
{
    return (InvokeReq*)__Message_New(
        InvokeReqTag, sizeof(InvokeReq), operationId, flags,
        cs);
}


#define InvokeReq_Release(self) \
    __InvokeReq_Release(self, CALLSITE)

MI_INLINE void __InvokeReq_Release(
    InvokeReq* self,
    CallSite cs)
{
    __Message_Release(&self->base.base, cs);
}

void InvokeReq_Print(const InvokeReq* msg, FILE* os);

/*
**==============================================================================
**
** AssociatorsOfReq
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
    RequestMsg      base;
    MI_ConstString  nameSpace;
    MI_ConstString  assocClass;
    MI_ConstString  resultClass;
    MI_ConstString  role;
    MI_ConstString  resultRole;

    /* dispatcher to provider only */
    MI_ConstString  className;

    /* un-packed version of instance */
    MI_Instance*    instance;
    /* packed version of instance */
    void*           packedInstancePtr;
    MI_Uint32       packedInstanceSize;
}
AssociationsOfReq;

#define AssociationsOfReq_New(operationId, flags, tag) \
    __AssociationsOfReq_New(operationId, flags, tag, CALLSITE)

MI_INLINE AssociationsOfReq* __AssociationsOfReq_New(
    MI_Uint64 operationId,
    MI_Uint32 flags,
    MessageTag tag,
    CallSite cs)
{
    return (AssociationsOfReq*)__Message_New(
        tag, sizeof(AssociationsOfReq), operationId, flags,
        cs);
}

#define AssociationsOfReq_Release(self) \
    __AssociationsOfReq_Release(self, CALLSITE)

MI_INLINE void __AssociationsOfReq_Release(
    AssociationsOfReq* self,
    CallSite cs)
{
    __Message_Release(&self->base.base, cs);
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
    Message         base;
    /* un-packed version of instance */
    MI_Instance*    instance;
    /* packed version of instance */
    void*           packedInstancePtr;
    MI_Uint32       packedInstanceSize;

}
PostInstanceMsg;

#define PostInstanceMsg_New(operationId) \
    __PostInstanceMsg_New(operationId, CALLSITE)

MI_INLINE PostInstanceMsg* __PostInstanceMsg_New(
    MI_Uint64 operationId,
    CallSite cs)
{
    return (PostInstanceMsg*)__Message_New(
        PostInstanceMsgTag, sizeof(PostInstanceMsg), operationId, 0,
        cs);
}

#define PostInstanceMsg_Release(self) \
    __PostInstanceMsg_Release(self, CALLSITE)

MI_INLINE void __PostInstanceMsg_Release(
    PostInstanceMsg* self,
    CallSite cs)
{
    __Message_Release(&self->base, cs);
}

void PostInstanceMsg_Print(const PostInstanceMsg* msg, FILE* os);

/*
**==============================================================================
**
** PostIndicationMsg
**
**==============================================================================
*/

typedef struct _PostIndicationMsg
{
    PostInstanceMsg base;

    /* Indication specific properties */
    MI_ConstString  machineID;
    MI_ConstString  bookmark;
}
PostIndicationMsg;

#define PostIndicationMsg_New(operationId) \
    __PostIndicationMsg_New(operationId, CALLSITE)

MI_INLINE PostIndicationMsg* __PostIndicationMsg_New(
    MI_Uint64 operationId,
    CallSite cs)
{
    return (PostIndicationMsg*)__Message_New(
        PostIndicationMsgTag, sizeof(PostIndicationMsg), operationId, 0,
        cs);
}

#define PostIndicationMsg_Release(self) \
    __PostIndicationMsg_Release(self, CALLSITE)

MI_INLINE void __PostIndicationMsg_Release(
    PostIndicationMsg* self,
    CallSite cs)
{
    __Message_Release(&self->base.base, cs);
}

void PostIndicationMsg_Print(const PostIndicationMsg* msg, FILE* os);

/*
**==============================================================================
**
** PostSchemaMsg
**
**     A CIM GetClass response 
**
**==============================================================================
*/

typedef struct _PostSchemaMsg
{
    Message base;
    /* un-packed version of class instance for local IPC */
    MI_Instance* schemaInstance;
    /* packed version of class instance */
    void*        packedSchemaInstancePtr;
    MI_Uint32    packedSchemaInstanceSize;

    /* Packed WSMan buffer */
    void *packedSchemaWsmanPtr;
    MI_Uint32 packedSchemaWsmanSize;

}
PostSchemaMsg;

#define PostSchemaMsg_New(operationId) \
    __PostSchemaMsg_New(operationId, CALLSITE)

MI_INLINE PostSchemaMsg* __PostSchemaMsg_New(
    MI_Uint64 operationId,
    CallSite cs)
{
    return (PostSchemaMsg*)__Message_New(
        PostSchemaMsgTag, sizeof(PostSchemaMsg), operationId, 0,
        cs);
}

#define PostSchemaMsg_Release(self) \
    __PostSchemaMsg_Release(self, CALLSITE)

MI_INLINE void __PostSchemaMsg_Release(
    PostSchemaMsg* self,
    CallSite cs)
{
    __Message_Release(&self->base, cs);
}

void PostSchemaMsg_Print(const PostSchemaMsg* msg, FILE* os);

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
    RequestMsg      base;
    MI_ConstString  nameSpace;
    MI_ConstString  className;
    /* Used for 'base-properties-only' mode to transfer 
        request's class-name */
    MI_ConstString  requestClassName;
    StringArray*    propertySet;
    MI_Boolean      deepInheritance;
    MI_Boolean      includeClassOrigin;
    MI_Boolean      basePropertiesOnly;

    /* Query language (or null none) */
    const ZChar*    queryLanguage;

    /* Query expression (or null none) */
    const ZChar*    queryExpression;

    /* Compiled WQL query */
    struct _WQL*    wql;
}
EnumerateInstancesReq;

#define EnumerateInstancesReq_New(operationId, flags) \
    __EnumerateInstancesReq_New(operationId, flags, CALLSITE)

MI_INLINE EnumerateInstancesReq* __EnumerateInstancesReq_New(
    MI_Uint64 operationId,
    MI_Uint32 flags,
    CallSite cs)
{
    return (EnumerateInstancesReq*)__Message_New(
        EnumerateInstancesReqTag, 
        sizeof(EnumerateInstancesReq), 
        operationId, 
        flags,
        cs);
}

#define EnumerateInstancesReq_Release(self) \
    __EnumerateInstancesReq_Release(self, CALLSITE)

MI_INLINE void __EnumerateInstancesReq_Release(
    EnumerateInstancesReq* self,
    CallSite cs)
{
    __Message_Release(&self->base.base, cs);
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
    RequestMsg      base;

    MI_ConstString  nameSpace;

    MI_ConstString  className;

    /* bookmark from client */
    MI_ConstString  bookmark;

    /* target type, see indicommon.h:SubscriptionTargetType */
    MI_Uint32       targetType;

    /* filter expression */
    MI_ConstString  filter;

    /* Supported languages defined in MI.h, WQL/CQL/MINT */
    MI_ConstString  language;

    /* Unique subscription ID for each client */
    MI_Uint64       subscriptionID;
}
SubscribeReq;

#define SubscribeReq_New(operationId, flags) \
    __SubscribeReq_New(operationId, flags, CALLSITE)

MI_INLINE SubscribeReq* __SubscribeReq_New(
    MI_Uint64 operationId,
    MI_Uint32 flags,
    CallSite cs)
{
    return (SubscribeReq*)__Message_New(
        SubscribeReqTag, sizeof(SubscribeReq), operationId, flags,
        cs);
}

#define SubscribeReq_Release(self) \
    __SubscribeReq_Release(self, CALLSITE)

MI_INLINE void __SubscribeReq_Release(
    SubscribeReq* self,
    CallSite cs)
{
    __Message_Release(&self->base.base, cs);
}

void SubscribeReq_Print(const SubscribeReq* msg, FILE* os);

/*
**==============================================================================
**
** UnsubscribeReq
**
**     Unsubscribe requeset
**
**==============================================================================
*/
typedef struct _UnsubscribeReq
{
    RequestMsg      base;
}
UnsubscribeReq;

#define UnsubscribeReq_New(operationId, flags) \
    __UnsubscribeReq_New(operationId, flags, CALLSITE)

MI_INLINE UnsubscribeReq* __UnsubscribeReq_New(
    MI_Uint64 operationId,
    MI_Uint32 flags,
    CallSite cs)
{
    return (UnsubscribeReq*)__Message_New(
        UnsubscribeReqTag, sizeof(UnsubscribeReq), operationId, flags,
        cs);
}

#define UnsubscribeReq_Release(self) \
    __UnsubscribeReq_Release(self, CALLSITE)

MI_INLINE void __UnsubscribeReq_Release(
    UnsubscribeReq* self,
    CallSite cs)
{
    __Message_Release(&self->base.base, cs);
}

void UnsubscribeReq_Print(const UnsubscribeReq* msg, FILE* os);

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
    RequestMsg      base;
}
NoOpReq;

#define NoOpReq_New(operationId) \
    __NoOpReq_New(operationId, CALLSITE)

MI_INLINE NoOpReq* __NoOpReq_New(
    MI_Uint64 operationId,
    CallSite cs)
{
    return (NoOpReq*)__Message_New(
        NoOpReqTag, sizeof(NoOpReq), operationId, BinaryProtocolFlag,
        cs);
}

#define NoOpReq_Release(self) \
    __NoOpReq_Release(self, CALLSITE)

MI_INLINE void __NoOpReq_Release(
    NoOpReq* self,
    CallSite cs)
{
    __Message_Release(&self->base.base, cs);
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
    Message         base;
}
NoOpRsp;

#define NoOpRsp_New(operationId) \
    __NoOpRsp_New(operationId, CALLSITE)

MI_INLINE NoOpRsp* __NoOpRsp_New(
    MI_Uint64 operationId,
    CallSite cs)
{
    return (NoOpRsp*)__Message_New(
        NoOpRspTag, sizeof(NoOpRsp), operationId, 0,
        cs);
}

#define NoOpRsp_Release(self) \
    __NoOpRsp_Release(self, CALLSITE)

MI_INLINE void __NoOpRsp_Release(
    NoOpRsp* self,
    CallSite cs)
{
    __Message_Release(&self->base, cs);
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
    BinNotificationConnectRequest = 0,
    BinNotificationConnectResponse = 1,
    BinNotificationAgentIdle = 2
}
BinProtNotificationType;

#define AUTH_RANDOM_DATA_SIZE   64

typedef struct _BinProtocolNotification
{
    Message         base;

    /* see BinProtNotificationType for supported types */
    MI_Uint32       type;

    /* **** Connect-request specific data **** */
    /* explicit auth [opt] */
    const char*     user;
    const char*     password;

    /* implicit auth - Requestor information */
    uid_t           uid;
    gid_t           gid;

    /* File-based authentication - files's content */
    unsigned char   authData[AUTH_RANDOM_DATA_SIZE];

    /* **** Connect-response specific data **** */
    /* ok/access-denied */
    MI_Result       result;

    /* file name - client has to read it and send back content */
    const char*     authFile;

}
BinProtocolNotification;

#define BinProtocolNotification_New(type) \
    __BinProtocolNotification_New(type, CALLSITE)

MI_INLINE BinProtocolNotification* __BinProtocolNotification_New(
    BinProtNotificationType type,
    CallSite cs)
{
    BinProtocolNotification* res = (BinProtocolNotification*)__Message_New(
        BinProtocolNotificationTag, sizeof(BinProtocolNotification), 0, 0,
        cs);

    if (res)
        res->type = type;

    return res;
}

#define BinProtocolNotification_Release(self) \
    __BinProtocolNotification_Release(self, CALLSITE)

MI_INLINE void __BinProtocolNotification_Release(
    BinProtocolNotification* self,
    CallSite cs)
{
    __Message_Release(&self->base, cs);
}

void BinProtocolNotification_Print(const BinProtocolNotification* msg, FILE* os);

MI_INLINE
MI_Boolean Message_IsInternalMessage( _In_ Message* msg )
{
    if( BinProtocolNotificationTag == msg->tag )
    {
        BinProtocolNotification* notification = (BinProtocolNotification*)msg;

        if( BinNotificationAgentIdle != notification->type )
        {
            return MI_TRUE;
        }
    }
    return MI_FALSE;
}

/*
**==============================================================================
**
** HttpHeaders
**
**     Used on HttpRequestMsg below
**
**==============================================================================
*/

#if defined(CONFIG_ENABLE_HTTPHEADERS)
# define HTTP_MAX_HEADERS 32
#endif

#if defined(CONFIG_ENABLE_HTTPHEADERS)
/* Represent an HTTP header */
typedef struct _HttpHeader
{
    const char* name;
    const char* value;
}
HttpHeader;
#endif

/* Headers strucutre is creaetd provided by http module 
    and has several pre-parsed values from http headers */
typedef struct _HttpHeaders
{
    /* required fields */
    /* content type is pre-parsed: <content-type>;charset=<charset>*/
    const char* contentType;
    const char* charset;

    /* Authorization field: */
    /* for Basic, server decodes username/pwd */
    const char* username;
    const char* password;

    /* for other than basci, server provides entire field: */
    const char* authorization;

    /* length of http payload */
    size_t  contentLength;

    /* The User-Agent header */
    const char* userAgent;

#if defined(CONFIG_ENABLE_HTTPHEADERS)

    /* Dynamic list of headers */
    HttpHeader headers[HTTP_MAX_HEADERS];
    size_t headersSize;

#endif
}
HttpHeaders;

HttpHeaders* HttpHeaders_Clone(
    _In_ Batch* batch,
    _In_ HttpHeaders* headers);

/*
**==============================================================================
**
** Http Messages: HttpRequestMsg and HttpResponseMsg
**
**     A internal HTTP(WSMAN) message with page content
**
**==============================================================================
*/

typedef struct _HttpRequestMsg
{
    Message base;

    HttpHeaders * headers;
    Page * page;
}
HttpRequestMsg;

#define HttpRequestMsg_Release(self) \
    __HttpRequestMsg_Release(self, CALLSITE)

MI_INLINE void __HttpRequestMsg_Release(
    HttpRequestMsg* self,
    CallSite cs)
{
    __Message_Release(&self->base, cs);
}

#define HttpRequestMsg_New(page, headers) \
    __HttpRequestMsg_New(page, headers, CALLSITE)

MI_INLINE void __HttpRequestMsg_dtor(Message* message, void* callbackData)
{
    HttpRequestMsg* msg;
    DEBUG_ASSERT(message->tag == HttpRequestMsgTag);
    msg = (HttpRequestMsg*)message;
    if (msg->page)
        PAL_Free(msg->page);
}

MI_INLINE HttpRequestMsg* __HttpRequestMsg_New( 
    _In_ Page * page, 
    HttpHeaders * headers,
    CallSite cs)
{
    HttpRequestMsg* msg = (HttpRequestMsg*)__Message_New(
        HttpRequestMsgTag, sizeof(HttpRequestMsg), 0, 0,
        cs);

    if (msg)
    {
        /* msg owns the page memory now */
        msg->page = page;
        msg->base.dtor = __HttpRequestMsg_dtor;

        /* copy the headers since does not own memory of headers, which owned by caller */
        msg->headers = HttpHeaders_Clone(msg->base.batch, headers);
        if (!msg->headers)
        {
            HttpRequestMsg_Release(msg);
            msg = NULL;
        }
    }

    return msg;
}

typedef struct _HttpResponseMsg
{
    Message base;

    Page * page;
    int httpErrorCode;
}
HttpResponseMsg;

#define HttpResponseMsg_New(page, httpErrorCode) \
    __HttpResponseMsg_New(page, httpErrorCode, CALLSITE)

MI_INLINE void __HttpResponseMsg_dtor(Message* message, void* callbackData)
{
    HttpResponseMsg* msg;
    DEBUG_ASSERT( message->tag == HttpResponseMsgTag );
    msg = (HttpResponseMsg*)message;
    if (msg->page)
        PAL_Free(msg->page);
}

MI_INLINE HttpResponseMsg* __HttpResponseMsg_New( 
    _In_ Page * page, 
    int httpErrorCode,
    CallSite cs)
{
    HttpResponseMsg* msg = (HttpResponseMsg*)__Message_New(
        HttpResponseMsgTag, sizeof(HttpResponseMsg), 0, 0,
        cs);

    if (msg)
    {
        msg->page = page;
        msg->base.dtor = __HttpResponseMsg_dtor;
        msg->httpErrorCode = httpErrorCode;
    }    

    return msg;
}

#define HttpResponseMsg_Release(self) \
    __HttpResponseMsg_Release(self, CALLSITE)

MI_INLINE void __HttpResponseMsg_Release(
    HttpResponseMsg* self,
    CallSite cs)
{
    __Message_Release(&self->base, cs);
}

/*
**==============================================================================
**
** SubscribeRes
**
**     Informs that the subscription is initiated
**
**==============================================================================
*/
typedef struct _SubscribeRes
{
    Message         base;
}
SubscribeRes;

#define SubscribeRes_New(operationId) \
    __SubscribeRes_New(operationId, CALLSITE)

MI_INLINE SubscribeRes* __SubscribeRes_New(
    MI_Uint64 operationId,
    CallSite cs)
{
    SubscribeRes* res = (SubscribeRes*)__Message_New(
        SubscribeResTag, sizeof(SubscribeRes), operationId, 0,
        cs);

    return res;
}

#define SubscribeRes_Release(self) \
    __SubscribeRes_Release(self, CALLSITE)

MI_INLINE void __SubscribeRes_Release(
    SubscribeRes* self,
    CallSite cs)
{
    __Message_Release(&self->base, cs);
}

/*
**==============================================================================
**
** CancelMsg
**
**     Cancelation across protocol
**
**==============================================================================
*/
typedef struct _CancelMsg
{
    Message         base;
}
CancelMsg;

#define CancelMsg_New(operationId) \
    __CancelMsg_New(operationId, CALLSITE)

MI_INLINE CancelMsg* __CancelMsg_New(
    MI_Uint64 operationId,
    CallSite cs)
{
    CancelMsg* res = (CancelMsg*)__Message_New(
        CancelMsgTag, sizeof(CancelMsg), operationId, 0,
        cs);

    return res;
}

#define CancelMsg_Release(self) \
    __CancelMsg_Release(self, CALLSITE)

MI_INLINE void __CancelMsg_Release(
    CancelMsg* self,
    CallSite cs)
{
    __Message_Release(&self->base, cs);
}

/*
**==============================================================================
**
** ProtocolEventConnect
**
**     Informs if protocol has connected successfully or failed to connect
**
**==============================================================================
*/
typedef struct _ProtocolEventConnect
{
    Message         base;

    MI_Boolean      success;
}
ProtocolEventConnect;

#define ProtocolEventConnect_New(success) \
    __ProtocolEventConnect_New(success, CALLSITE)


MI_INLINE ProtocolEventConnect* __ProtocolEventConnect_New(
    MI_Boolean success,
    CallSite cs)
{
    ProtocolEventConnect* res = (ProtocolEventConnect*)__Message_New(
        ProtocolEventConnectTag, sizeof(ProtocolEventConnect), 0, 0,
        cs);

    if (res)
        res->success = success;

    return res;
}

#define ProtocolEventConnect_Release(self) \
    __ProtocolEventConnect_Release(self, CALLSITE)

MI_INLINE void __ProtocolEventConnect_Release(
    ProtocolEventConnect* self,
    CallSite cs)
{
    __Message_Release(&self->base, cs);
}

/*
**==============================================================================
**
**     binary transport with batch support
**
**     
**
**==============================================================================
*/

#define MessageFromBatch(batch, originalMsgPtr, ptrAdjustmentInfo, ptrAdjustmentInfoCount, skipInstanceUnpack, msgOut) \
    __MessageFromBatch(batch, originalMsgPtr, ptrAdjustmentInfo, ptrAdjustmentInfoCount, skipInstanceUnpack, msgOut, CALLSITE)

MI_Result __MessageFromBatch(
    Batch* batch,
    void* originalMsgPtr,
    const Header_BatchInfoItem* ptrAdjustmentInfo,
    size_t ptrAdjustmentInfoCount,
    MI_Boolean skipInstanceUnpack,
    Message** msgOut,
    CallSite cs);

/*
**==============================================================================
**
**     Creates a clone of given message, 
**      suitable for sending with binary protocol
**      This is needed to:
**      - make batch smaller (no small blocks from instance's parts
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

/*
**==============================================================================
**
** MessageName
**
**     Get message name on tag
**
**==============================================================================
*/
const PAL_Char* MessageName(MI_Uint32 tag);

END_EXTERNC

#endif /* _omi_messages_h */
