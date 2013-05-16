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

typedef enum _FieldType
{
    FT_BOOLEAN = MI_BOOLEAN,
    FT_UINT8 = MI_UINT8,
    FT_SINT8 = MI_SINT8,
    FT_UINT16 = MI_UINT16,
    FT_SINT16 = MI_SINT16,
    FT_UINT32 = MI_UINT32,
    FT_SINT32 = MI_SINT32,
    FT_UINT64 = MI_UINT64,
    FT_SINT64 = MI_SINT64,
    FT_REAL32 = MI_REAL32,
    FT_REAL64 = MI_REAL64,
    FT_CHAR16 = MI_CHAR16,
    FT_DATETIME = MI_DATETIME,
    FT_STRING = MI_STRING,
    FT_REFERENCE = MI_REFERENCE,
    FT_INSTANCE = MI_INSTANCE,
    FT_BOOLEANA = MI_BOOLEANA,
    FT_UINT8A = MI_UINT8A,
    FT_SINT8A = MI_SINT8A,
    FT_UINT16A = MI_UINT16A,
    FT_SINT16A = MI_SINT16A,
    FT_UINT32A = MI_UINT32A,
    FT_SINT32A = MI_SINT32A,
    FT_UINT64A = MI_UINT64A,
    FT_SINT64A = MI_SINT64A,
    FT_REAL32A = MI_REAL32A,
    FT_REAL64A = MI_REAL64A,
    FT_CHAR16A = MI_CHAR16A,
    FT_DATETIMEA = MI_DATETIMEA,
    FT_STRINGA = MI_STRINGA,
    FT_REFERENCEA = MI_REFERENCEA,
    FT_INSTANCEA = MI_INSTANCEA,
    FT_RESULT,
    FT_ATOMIC
}
FieldType;

/* Defines meta data for message field (to support printing) */
typedef struct Field
{
    /* Name of field */
    const char* name;

    /* (ZT=Tag, S=String, B=Boolean, A=StringArray, O=Object) */
    FieldType type;

    /* Byte off within structure to this field */
    size_t off;
}
Field;

static void _Message_Print(
    const void* msg,
    FILE* os,
    const char* structName,
    const Field fields[])
{
    size_t i;

    Fzprintf(os, ZT("%s\n"), scs(structName));
    Fzprintf(os, ZT("{\n"));

    for (i = 0; fields[i].name; i++)
    {
        const Field* f = &fields[i];

        /* Print name */
        Fzprintf(os, ZT("    %s="), scs(f->name));

        /* Print value */
        switch (f->type)
        {
            case FT_UINT32:
            {
                MessageTag* p = (MessageTag*)((char*)msg + f->off);
                Fzprintf(os, ZT("%u"), *p);
                break;
            }
            case FT_RESULT:
            {
                MI_Result* p = (MI_Result*)((char*)msg + f->off);
                Fzprintf(os, MI_T("%u [%Z]"),*p, zcs(Result_ToString(*p)));
                break;
            }
            case FT_ATOMIC:
            {
                AtomicInt* p = (AtomicInt*)((char*)msg + f->off);
                Fzprintf(os, MI_T("%d"),(int)(*p));
                break;
            }
            case FT_UINT64:
            {
                MI_Uint64* p = (MI_Uint64*)((char*)msg + f->off);
                Fzprintf(os, UINT64_FMT_T, *p);
                break;
            }
            case FT_BOOLEAN:
            {
                MI_Boolean* p = (MI_Boolean*)((char*)msg + f->off);
                Fzprintf(os, ZT("%s"), scs(*p ? "TRUE" : "FALSE"));
                break;
            }
            case FT_STRING:
            {
                ZChar** p = (ZChar**)((char*)msg + f->off);

                if (*p)
                    Fzprintf(os, MI_T("\"%Z\""), zcs(*p));
                else
                    Fzprintf(os, ZT("NULL"));
                break;
            }
            case FT_STRINGA:
            {
                StringArray** p = (StringArray**)((char*)msg + f->off);

                if (*p)
                    StringArray_Print(*p, os);
                else
                    Fzprintf(os, ZT("NULL"));
                break;
            }
            case FT_INSTANCE:
            {
                MI_Instance** p = (MI_Instance**)((char*)msg + f->off);

                if (*p)
                {
                    Fzprintf(os, ZT("\n"));
                    MI_Instance_Print(*p, os, 1);
                }
                else
                    Fzprintf(os, ZT("NULL\n"));
                break;
            }
            default:
                break;
        }

        if (f->type != FT_INSTANCE)
            Fzprintf(os, ZT("\n"));
    }

    Fzprintf(os, ZT("}\n"));
}

void MessagePrint(const Message* msg, FILE* os)
{
    switch ( msg->tag )
    {
        case GetInstanceReqTag:
            {
                const GetInstanceReq* m = (const GetInstanceReq*)msg;
                GetInstanceReq_Print(m, os);
            }
            break;

        case PostInstanceMsgTag:
            {
                const PostInstanceMsg* m = (const PostInstanceMsg*)msg;
                PostInstanceMsg_Print(m, os);
            }
            break;

        case EnumerateInstancesReqTag:
            {
                const EnumerateInstancesReq* m = (const EnumerateInstancesReq*)msg;
                EnumerateInstancesReq_Print(m, os);
            }
            break;

        case PostResultMsgTag:
            {
                const PostResultMsg* m = (const PostResultMsg*)msg;
                PostResultMsg_Print(m, os);
            }
            break;

        case NoOpReqTag:
            {
                const NoOpReq* m = (const NoOpReq*)msg;
                NoOpReq_Print(m, os);
            }
            break;

        case NoOpRspTag:
            {
                const NoOpRsp* m = (const NoOpRsp*)msg;
                NoOpRsp_Print(m, os);
            }
            break;

        case DispResultMsgTag:
            {
                const DispResultMsg* m = (const DispResultMsg*)msg;
                DispResultMsg_Print(m, os);
            }
            break;

        case InvokeReqTag:
            {
                const InvokeReq* m = (const InvokeReq*)msg;
                InvokeReq_Print(m, os);
            }
            break;

        case AssociatorsOfReqTag:
            {
                const AssociationsOfReq* m = (const AssociationsOfReq*)msg;
                AssociatorsOfReq_Print(m, os);
            }
            break;

        case ReferencesOfReqTag:
            {
                const AssociationsOfReq* m = (const AssociationsOfReq*)msg;
                ReferencesOfReq_Print(m, os);
            }
            break;

        case SubscribeReqTag:
            {
                const SubscribeReq* m = (const SubscribeReq*)msg;
                SubscribeReq_Print(m, os);
            }
            break;

        case SubscribeResTag:
            {
                const SubscribeRes* m = (const SubscribeRes*)msg;
                SubscribeRes_Print(m, os);
            }
            break;

        case DeleteInstanceReqTag:
            {
                const DeleteInstanceReq* m = (const DeleteInstanceReq*)msg;
                DeleteInstanceReq_Print(m, os);
            }
            break;

        case CreateInstanceReqTag:
            {
                const CreateInstanceReq* m = (const CreateInstanceReq*)msg;
                CreateInstanceReq_Print(m, os);
            }
            break;

        case ModifyInstanceReqTag:
            {
                const ModifyInstanceReq* m = (const ModifyInstanceReq*)msg;
                ModifyInstanceReq_Print(m, os);
            }
            break;

        case BinProtocolNotificationTag:
            {
                const BinProtocolNotification* m = (const BinProtocolNotification*)msg;
                BinProtocolNotification_Print(m, os);
            }
            break;

        default:
            Fzprintf(os, ZT("unknown message tag %d\n"), msg->tag);
            break;

    }
}

void GetInstanceReq_Print(const GetInstanceReq* msg, FILE* os)
{
    typedef GetInstanceReq Self;
    static const Field fields[] =
    {
        {"tag", FT_UINT32, offsetof(Self, base.tag)},
        {"msgID", FT_UINT64, offsetof(Self, base.msgID)},
        {"clientID", FT_UINT64, offsetof(Self, base.clientID)},
        {"instanceName", FT_INSTANCE, offsetof(Self, instanceName)},
        {"includeClassOrigin", FT_BOOLEAN, offsetof(Self, includeClassOrigin)},
        {"propertySet", FT_STRINGA, offsetof(Self, propertySet)},
        {"userAgent", FT_UINT32, offsetof(Self, base.userAgent)},
        {NULL, 0, 0},
    };
    _Message_Print(msg, os, "GetInstanceReq", fields);
}

void CreateInstanceReq_Print(const CreateInstanceReq* msg, FILE* os)
{
    typedef CreateInstanceReq Self;
    static const Field fields[] =
    {
        {"tag", FT_UINT32, offsetof(Self, base.tag)},
        {"msgID", FT_UINT64, offsetof(Self, base.msgID)},
        {"clientID", FT_UINT64, offsetof(Self, base.clientID)},
        {"instanceName", FT_INSTANCE, offsetof(Self, instance)},
        {"propertySet", FT_STRINGA, offsetof(Self, propertySet)},
        {"userAgent", FT_UINT32, offsetof(Self, base.userAgent)},
        {NULL, 0, 0},
    };
    _Message_Print(msg, os, "CreateInstanceReq", fields);
}

void ModifyInstanceReq_Print(const ModifyInstanceReq* msg, FILE* os)
{
    typedef ModifyInstanceReq Self;
    static const Field fields[] =
    {
        {"tag", FT_UINT32, offsetof(Self, base.tag)},
        {"msgID", FT_UINT64, offsetof(Self, base.msgID)},
        {"clientID", FT_UINT64, offsetof(Self, base.clientID)},
        {"instanceName", FT_INSTANCE, offsetof(Self, instance)},
        {"propertySet", FT_STRINGA, offsetof(Self, propertySet)},
        {"userAgent", FT_UINT32, offsetof(Self, base.userAgent)},
        {NULL, 0, 0},
    };
    _Message_Print(msg, os, "ModifyInstanceReq", fields);
}

void DeleteInstanceReq_Print(const DeleteInstanceReq* msg, FILE* os)
{
    typedef DeleteInstanceReq Self;
    static const Field fields[] =
    {
        {"tag", FT_UINT32, offsetof(Self, base.tag)},
        {"msgID", FT_UINT64, offsetof(Self, base.msgID)},
        {"clientID", FT_UINT64, offsetof(Self, base.clientID)},
        {"instanceName", FT_INSTANCE, offsetof(Self, instanceName)},
        {"userAgent", FT_UINT32, offsetof(Self, base.userAgent)},
        {NULL, 0, 0},
    };
    _Message_Print(msg, os, "DeleteInstanceReq", fields);
}

void InvokeReq_Print(const InvokeReq* msg, FILE* os)
{
    typedef InvokeReq Self;
    static const Field fields[] =
    {
        {"tag", FT_UINT32, offsetof(Self, base.tag)},
        {"msgID", FT_UINT64, offsetof(Self, base.msgID)},
        {"clientID", FT_UINT64, offsetof(Self, base.clientID)},
        {"nameSpace", FT_STRING, offsetof(Self, nameSpace)},
        {"className", FT_STRING, offsetof(Self, className)},
        {"function", FT_STRING, offsetof(Self, function)},
        {"instance", FT_INSTANCE, offsetof(Self, instance)},
        {"instanceParams", FT_INSTANCE, offsetof(Self, instanceParams)},
        {"userAgent", FT_UINT32, offsetof(Self, base.userAgent)},
        {NULL, 0, 0},
    };
    _Message_Print(msg, os, "InvokeReq", fields);
}

void AssociatorsOfReq_Print(const AssociationsOfReq* msg, FILE* os)
{
    typedef AssociationsOfReq Self;
    static const Field fields[] =
    {
        {"tag", FT_UINT32, offsetof(Self, base.tag)},
        {"msgID", FT_UINT64, offsetof(Self, base.msgID)},
        {"clientID", FT_UINT64, offsetof(Self, base.clientID)},
        {"nameSpace", FT_STRING, offsetof(Self, nameSpace)},
        {"assocClass", FT_STRING, offsetof(Self, assocClass)},
        {"resultClass", FT_STRING, offsetof(Self, resultClass)},
        {"role", FT_STRING, offsetof(Self, role)},
        {"resultRole", FT_STRING, offsetof(Self, resultRole)},
        {"instance", FT_INSTANCE, offsetof(Self, instance)},
        {"userAgent", FT_UINT32, offsetof(Self, base.userAgent)},
        {NULL, 0, 0},
    };
    _Message_Print(msg, os, "AssociationsOfReq", fields);
}

void ReferencesOfReq_Print(const AssociationsOfReq* msg, FILE* os)
{
    typedef AssociationsOfReq Self;
    static const Field fields[] =
    {
        {"tag", FT_UINT32, offsetof(Self, base.tag)},
        {"msgID", FT_UINT64, offsetof(Self, base.msgID)},
        {"clientID", FT_UINT64, offsetof(Self, base.clientID)},
        {"nameSpace", FT_STRING, offsetof(Self, nameSpace)},
        {"assocClass", FT_STRING, offsetof(Self, assocClass)},
        {"role", FT_STRING, offsetof(Self, role)},
        {"instance", FT_INSTANCE, offsetof(Self, instance)},
        {"userAgent", FT_UINT32, offsetof(Self, base.userAgent)},
        {NULL, 0, 0},
    };
    _Message_Print(msg, os, "ReferencesOfReq", fields);
}

void PostInstanceMsg_Print(const PostInstanceMsg* msg, FILE* os)
{
    typedef PostInstanceMsg Self;
    static const Field fields[] =
    {
        {"tag", FT_UINT32, offsetof(Self, base.tag)},
        {"msgID", FT_UINT64, offsetof(Self, base.msgID)},
        {"clientID", FT_UINT64, offsetof(Self, base.clientID)},
        {"instance", FT_INSTANCE, offsetof(Self, instance)},
        {"userAgent", FT_UINT32, offsetof(Self, base.userAgent)},
        {NULL, 0, 0},
    };
    _Message_Print(msg, os, "PostInstanceMsg", fields);
}

void PostResultMsg_Print(const PostResultMsg* msg, FILE* os)
{
    typedef PostResultMsg Self;
    static const Field fields[] =
    {
        {"tag", FT_UINT32, offsetof(Self, base.tag)},
        {"msgID", FT_UINT64, offsetof(Self, base.msgID)},
        {"clientID", FT_UINT64, offsetof(Self, base.clientID)},
        {"result", FT_RESULT, offsetof(Self, result)},
        {"errorMessage", FT_STRING, offsetof(Self, errorMessage)},
        {"CIM_Error", FT_INSTANCE, offsetof(Self, cimError)},
        {"userAgent", FT_UINT32, offsetof(Self, base.userAgent)},
        {NULL, 0, 0},
    };
    _Message_Print(msg, os, "PostResultMsg", fields);
}

void DispResultMsg_Print(const DispResultMsg* msg, FILE* os)
{
    typedef DispResultMsg Self;
    static const Field fields[] =
    {
        {"tag", FT_UINT32, offsetof(Self, base.tag)},
        {"msgID", FT_UINT64, offsetof(Self, base.msgID)},
        {"clientID", FT_UINT64, offsetof(Self, base.clientID)},
        {"result", FT_RESULT, offsetof(Self, result)},
        {"requestCounter", FT_ATOMIC, offsetof(Self, requestCounter)},
        {"userAgent", FT_UINT32, offsetof(Self, base.userAgent)},
        {NULL, 0, 0},
    };
    _Message_Print(msg, os, "DispResultMsg", fields);
}

void EnumerateInstancesReq_Print(
    const EnumerateInstancesReq* msg,
    FILE* os)
{
    typedef EnumerateInstancesReq Self;
    static const Field fields[] =
    {
        {"tag", FT_UINT32, offsetof(Self, base.tag)},
        {"msgID", FT_UINT64, offsetof(Self, base.msgID)},
        {"clientID", FT_UINT64, offsetof(Self, base.clientID)},
        {"nameSpace", FT_STRING, offsetof(Self, nameSpace)},
        {"className", FT_STRING, offsetof(Self, className)},
        {"requestClassName", FT_STRING, offsetof(Self, requestClassName)},
        {"deepInheritance", FT_BOOLEAN, offsetof(Self, deepInheritance)},
        {"includeClassOrigin", FT_BOOLEAN, offsetof(Self, includeClassOrigin)},
        {"propertySet", FT_STRINGA, offsetof(Self, propertySet)},
        {"queryLanguage", FT_STRING, offsetof(Self, queryLanguage)},
        {"queryExpression", FT_STRING, offsetof(Self, queryExpression)},
        {"userAgent", FT_UINT32, offsetof(Self, base.userAgent)},
        {NULL, 0, 0},
    };
    _Message_Print(msg, os, "EnumerateInstancesReq", fields);
}

void SubscribeReq_Print(const SubscribeReq* msg, FILE* os)
{
    typedef SubscribeReq Self;
    static const Field fields[] =
    {
        {"tag", FT_UINT32, offsetof(Self, base.tag)},
        {"msgID", FT_UINT64, offsetof(Self, base.msgID)},
        {"clientID", FT_UINT64, offsetof(Self, base.clientID)},
        {"nameSpace", FT_STRING, offsetof(Self, nameSpace)},
        {"className", FT_STRING, offsetof(Self, className)},
        {"filter", FT_STRING, offsetof(Self, filter)},
        {"language", FT_STRING, offsetof(Self, language)},
        {"userAgent", FT_UINT32, offsetof(Self, base.userAgent)},
        {NULL, 0, 0},
    };
    _Message_Print(msg, os, "SubscribeReq", fields);
}

void SubscribeRes_Print(const SubscribeRes* msg, FILE* os)
{
    typedef SubscribeRes Self;
    static const Field fields[] =
    {
        {"tag", FT_UINT32, offsetof(Self, base.tag)},
        {"msgID", FT_UINT64, offsetof(Self, base.msgID)},
        {"clientID", FT_UINT64, offsetof(Self, base.clientID)},
        {"subscriptionID", FT_STRING, offsetof(Self, subscriptionID)},
        {"userAgent", FT_UINT32, offsetof(Self, base.userAgent)},
        {NULL, 0, 0},
    };
    _Message_Print(msg, os, "SubscribeRes", fields);
}

void NoOpReq_Print(const NoOpReq* msg, FILE* os)
{
    typedef NoOpReq Self;
    static const Field fields[] =
    {
        {"tag", FT_UINT32, offsetof(Self, base.tag)},
        {"msgID", FT_UINT64, offsetof(Self, base.msgID)},
        {"clientID", FT_UINT64, offsetof(Self, base.clientID)},
        {"userAgent", FT_UINT32, offsetof(Self, base.userAgent)},
        {NULL, 0, 0},
    };
    _Message_Print(msg, os, "NoOpReq", fields);
}

void NoOpRsp_Print(const NoOpRsp* msg, FILE* os)
{
    typedef NoOpRsp Self;
    static const Field fields[] =
    {
        {"tag", FT_UINT32, offsetof(Self, base.tag)},
        {"msgID", FT_UINT64, offsetof(Self, base.msgID)},
        {"clientID", FT_UINT64, offsetof(Self, base.clientID)},
        {"userAgent", FT_UINT32, offsetof(Self, base.userAgent)},
        {NULL, 0, 0},
    };
    _Message_Print(msg, os, "NoOpRsp", fields);
}

void BinProtocolNotification_Print(const BinProtocolNotification* msg, FILE* os)
{
    typedef BinProtocolNotification Self;
    static const Field fields[] =
    {
        {"tag", FT_UINT32, offsetof(Self, base.tag)},
        {"msgID", FT_UINT64, offsetof(Self, base.msgID)},
        {"clientID", FT_UINT64, offsetof(Self, base.clientID)},
        {"userAgent", FT_UINT32, offsetof(Self, base.userAgent)},
        {NULL, 0, 0},
    };
    _Message_Print(msg, os, "BinProtocolNotification", fields);
}
