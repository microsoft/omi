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

#include <base/strings.h>
#include <base/messages.h>
#include <base/log.h>
#include <base/strings.h>
#include <base/paths.h>
#include <io/io.h>
#include <base/hashtable.h>
#include <wql/wql.h>
#include "disp.h"

/*
**==============================================================================
**
** ClassName hash implementation
**
**==============================================================================
*/

typedef struct _ClassNameBucket /* derives from HashBucket */
{
    struct _ClassNameBucket* next;
    ZChar* key;
}
ClassNameBucket;

static size_t ClassNameHash(
    const HashBucket* bucket_)
{
    /* Note: this algorithm has a poor distribution */
    ClassNameBucket* bucket = (ClassNameBucket*)bucket_;
    size_t h = 0;
    ZChar* key = bucket->key;

    while (*key)
    {
        h += 5 * *key++;
    }

    return h;
}

static int ClassNameEqual(
    const HashBucket* bucket1_,
    const HashBucket* bucket2_)
{
    ClassNameBucket* bucket1 = (ClassNameBucket*)bucket1_;
    ClassNameBucket* bucket2 = (ClassNameBucket*)bucket2_;
    return Zcasecmp(bucket1->key, bucket2->key) == 0;
}

static void ClassNameRelease(
    HashBucket* bucket_)
{
    ClassNameBucket* bucket = (ClassNameBucket*)bucket_;

    free(bucket->key);
    free(bucket);
}

/*
**==============================================================================
**
** Data structures
**
**==============================================================================
*/

/*
    subscription item - represents single subscription;
*/
typedef struct _DispSubscriptionItem
{
    struct _DispSubscriptionItem* next;
    struct _DispSubscriptionItem* prev;

    /* The batch this context was allocated from */
    Batch batch;

    /* filter */
    MI_ConstString  filter;
    MI_ConstString  language;

    /* unique id of the sub */
    MI_Uint64       subscriptionID;

    /* Client identifier if supported */
    MI_Uint64 clientID;

}
DispSubscriptionItem;


/* subscriptions context -
    used to track indicaiton providers
    and store indications for 'pull' operation
    one context per ns/cn pair
*/
typedef struct _DispIndicationContext
{
    struct _DispIndicationContext* next;
    struct _DispIndicationContext* prev;

    /* The batch this context was allocated from */
    Batch batch;

    /* namespace/cn */
    MI_ConstString  nameSpace;
    MI_ConstString  className;

    /* unique id of the context (used by ProvMgr) */
    MI_Uint64       ctxID;

    /* provider info */
    const ProvRegEntry* provEntry;

    /* exisitng subscriptions */
    DispSubscriptionItem* headSubscriptions;
    DispSubscriptionItem* tailSubscriptions;
}
DispIndicationContext;


/*
**==============================================================================
**
** Local definitions
**
**==============================================================================
*/
static MI_Result _SendErrorResponse(
    Message* req,
    MI_Result r);

static DispIndicationContext* _FindIndCtxByNScn(
    Disp* self,
    MI_ConstString  nameSpace,
    MI_ConstString  className)
{
    DispIndicationContext* current = (DispIndicationContext*)self->headIndCtx;

    while (current)
    {
        if (0 == Zcasecmp(nameSpace, current->nameSpace) &&
            0 == Zcasecmp(className, current->className))
            break;

        current = current->next;
    }
    return current;
}

static DispIndicationContext* _FindIndCtxByID(
    Disp* self,
    MI_Uint64 id)
{
    DispIndicationContext* current = (DispIndicationContext*)self->headIndCtx;

    while (current)
    {
        if (id == current->ctxID)
            break;

        current = current->next;
    }
    return current;
}

static DispSubscriptionItem* _FindSubscriptionItem(
    DispIndicationContext* ctx,
    MI_Uint64 subscriptionID)
{
    DispSubscriptionItem* item = ctx->headSubscriptions;

    while (item)
    {
        if (item->subscriptionID == subscriptionID)
            break;

        item = item->next;
    }
    return item;
}


static void _DestroySubscriptionItem(
    DispSubscriptionItem* item)
{
    Batch_Destroy(&item->batch);
}
static void _DestroyIndCtx(
    DispIndicationContext* ctx)
{
    DispSubscriptionItem* item = ctx->headSubscriptions;

    while (item)
    {
        DispSubscriptionItem* next = item->next;

        _DestroySubscriptionItem(item);
        item = next;
    }
    Batch_Destroy(&ctx->batch);
}


static MI_Result _FindCreateIndCtx(
    Disp* self,
    SubscribeReq* req,
    ProvRegEntry const** reg)
{
    /* look for exisiting first */
    DispIndicationContext* ctx = _FindIndCtxByNScn( self, req->nameSpace, req->className );

    if (!ctx)
    {
        Batch batch = BATCH_INITIALIZER;

        /* Allocate heap space for message */
        ctx = (DispIndicationContext*) Batch_GetClear(&batch, sizeof(DispIndicationContext) );

        if (!ctx)
            return MI_RESULT_FAILED;

        /* Copy batch into context (released by _Destroy method) */
        memcpy(&ctx->batch, &batch, sizeof(batch));

        ctx->className = Batch_Zdup(&batch, req->className);
        ctx->nameSpace = Batch_Zdup(&batch, req->nameSpace);

        if (!ctx->className || !ctx->nameSpace)
        {
            _DestroyIndCtx(ctx);
            return MI_RESULT_FAILED;
        }
        ctx->ctxID = ++self->nextID;

        /* Look for provider info */
        ctx->provEntry = ProvReg_FindProviderForClass(&self->provreg,
            req->nameSpace, req->className);

        if (!ctx->provEntry)
        {
            _DestroyIndCtx(ctx);
            return MI_RESULT_INVALID_NAMESPACE;
        }

        /* add context to the list */
        List_Append(&self->headIndCtx, &self->tailIndCtx, (ListElem*)ctx);
    }

    /* Update request with correct IDs */
    req->ctxID = ctx->ctxID;
    req->subscriptionID = ++self->nextID;

    /* Set out parameter */
    *reg = ctx->provEntry;

    return MI_RESULT_OK;
}

static MI_Result _UpdateIndicationCtxWithSub(
    Disp* self,
    SubscribeReq* dispReq)
{
    DispIndicationContext* ctx;
    DispSubscriptionItem* subItem;

    ctx = _FindIndCtxByID( self, dispReq->ctxID );

    /* unlikely, but it can be removed by other operation */
    if (!ctx)
        return MI_RESULT_FAILED;

    /* */
    subItem = _FindSubscriptionItem(ctx, dispReq->subscriptionID);

    if (subItem)
        return MI_RESULT_ALREADY_EXISTS;

    {
        Batch batch = BATCH_INITIALIZER;

        /* Allocate heap space for message */
        subItem = (DispSubscriptionItem*) Batch_GetClear(&batch, sizeof(DispSubscriptionItem) );

        if (!subItem)
            return MI_RESULT_FAILED;

        /* Copy batch into context (released by _Destroy method) */
        memcpy(&subItem->batch, &batch, sizeof(batch));

        subItem->filter = Batch_Zdup(&batch, dispReq->filter);
        subItem->language = Batch_Zdup(&batch, dispReq->language);

        if (!subItem->filter || !subItem->language)
        {
            _DestroySubscriptionItem(subItem);
            return MI_RESULT_FAILED;
        }
        subItem->subscriptionID = dispReq->subscriptionID;
        subItem->clientID = dispReq->base.request->clientID;

        /* add item to the context */
        List_Append(
            (ListElem**)&ctx->headSubscriptions,
            (ListElem**)&ctx->tailSubscriptions,
            (ListElem*)subItem);
    }

    return MI_RESULT_OK;
}

static void _ProcessSubscribeResponse(
    Disp* self,
    PostResultMsg* rsp)
{
    MI_Result r;
    SubscribeReq* dispReq = (SubscribeReq*)rsp->base.request;


    /* Find context, create subscription struct */
    Mutex_Lock(&self->mt);

    r = _UpdateIndicationCtxWithSub( self, dispReq );

    Mutex_Unlock(&self->mt);

    /* check if error was detected */
    if (MI_RESULT_OK != r)
    {
        _SendErrorResponse(rsp->base.request->request, r);
    }

    /* send subscription response */
    {
        SubscribeRes* resp;
        char s[50];

        resp = SubscribeRes_New( rsp->base.request->request->msgID );

        if (!resp)
            return ;

        Snprintf(s, MI_COUNT(s), UINT64_FMT "," UINT64_FMT,
            dispReq->ctxID,
            dispReq->subscriptionID);

        resp->subscriptionID = Batch_StrZdup(resp->base.batch, s);

        Message_SetRequest(&resp->base,rsp->base.request->request);
        (*rsp->base.request->request->callback)(&resp->base, rsp->base.request->request->callbackData);

        SubscribeRes_Release(resp);
    }

}

static void _ProviderToDispatcherCallback(
    Message* msg,
    void* callbackData)
{
    switch ( msg->tag )
    {
        case PostResultMsgTag:
        {
            PostResultMsg* rsp = (PostResultMsg*)msg;

            if (msg->request && msg->request->request &&  msg->request->request->tag == DispResultMsgTag)
            {
                DispResultMsg* dispStateMsg = (DispResultMsg*)msg->request->request;

                if (rsp->result != MI_RESULT_OK && dispStateMsg->result == MI_RESULT_OK)
                {
                    dispStateMsg->result = rsp->result;
                }

                if ( AtomicDec(&dispStateMsg->requestCounter) )
                {   /* last result - forward it to the net stack */
                    rsp->result = dispStateMsg->result;
                }
                else    /* not the last result - skip it */
                    return;

            }
            else if (msg->request && msg->request->tag == SubscribeReqTag)
            {
                /* process subscription response */
                if (MI_RESULT_OK != rsp->result )
                    break;

                /*
                    validate parameter msg->request->request is a parameter received from network transport;
                    msg->request is a message created by disp for provmgr
                */
                if (msg->request->request)
                {
                    _ProcessSubscribeResponse((Disp*)callbackData, rsp);
                    return;
                }
            }
        }
        break;

        default:
            break;
    }

    /* forward message to the other side */
    if (msg->request && msg->request->request)
    {
        /* delegate message to protocol stack */
        msg->clientID = msg->request->request->clientID;
        (*msg->request->request->callback)(msg, msg->request->request->callbackData);
    }
    else if (msg->request)
    {
        /* delegate message to protocol stack */
        msg->clientID = msg->request->clientID;
        (*msg->request->callback)(msg, msg->request->callbackData);
    }
    else
    {
        (*msg->callback)(msg, msg->callbackData);
    }
}

static MI_Boolean _DispatchEnumerateInstancesReq(
    Disp* self,
    const ZChar* className,
    const EnumerateInstancesReq* req,
    DispResultMsg* dispStateMsg)
{
    const ProvRegEntry* entry;
    EnumerateInstancesReq* msg;
    MI_Result r;

    /* Attempt to find a provider for this class */
    {
        entry = ProvReg_FindProviderForClass(&self->provreg,
            req->nameSpace, className);

        if (!entry)
            return MI_FALSE;
    }

    /* Create new request to send to provider */
    msg = EnumerateInstancesReq_New(req->base.msgID, req->base.flags);
    msg->base.clientID = req->base.clientID;
    msg->base.uid = req->base.uid;
    msg->base.gid = req->base.gid;
    msg->nameSpace = Batch_Zdup(msg->base.batch, req->nameSpace);
    msg->className = Batch_Zdup(msg->base.batch, className);
    msg->base.userAgent = req->base.userAgent;

    if (!msg->nameSpace || !msg->className)
    {
        EnumerateInstancesReq_Release(msg);
        LOGE((ZT("_DispatchEnumerateInstancesReq() out of memory")));
        return MI_FALSE;
    }

    /* Clone the query fields (if any) */
    if (req->queryLanguage)
    {
        msg->queryLanguage = Batch_Zdup(msg->base.batch, req->queryLanguage);
        if (!msg->queryLanguage)
        {
            LOGE((ZT("_DispatchEnumerateInstancesReq() out of memory")));

            AtomicDec(&dispStateMsg->requestCounter);
            return MI_FALSE;
        }
    }

    if (req->queryExpression)
    {
        msg->queryExpression = Batch_Zdup(msg->base.batch,req->queryExpression);
        if (!msg->queryExpression)
        {
            LOGE((ZT("_DispatchEnumerateInstancesReq() out of memory")));

            AtomicDec(&dispStateMsg->requestCounter);
            return MI_FALSE;
        }
    }

    if (req->wql)
        msg->wql = WQL_Clone(req->wql, msg->base.batch);

    /* Save request's class name to allow porvmgr pack back only base properties */
    if (req->basePropertiesOnly)
    {
        msg->requestClassName = Batch_Zdup(msg->base.batch, req->className);
        if (!msg->requestClassName)
        {
            LOGE((ZT("_DispatchEnumerateInstancesReq() out of memory")));

            AtomicDec(&dispStateMsg->requestCounter);
            return MI_FALSE;
        }
    }

    AtomicInc(&dispStateMsg->requestCounter);
    Message_SetRequest(&msg->base, &dispStateMsg->base);

    /* Setup callback */
    msg->base.callback = _ProviderToDispatcherCallback;
    msg->base.callbackData = self;

    /* Send the request to provider manager */
    r = AgentMgr_HandleRequest(&self->agentmgr, &msg->base, entry);

    /* Release the original message */
    EnumerateInstancesReq_Release(msg);

    /* Log failure */
    if (r != MI_RESULT_OK)
    {
        LOGW((ZT("AgentMgr_HandleRequest() failed: %u: %Z"), r, zcs(Result_ToString(r))));

        AtomicDec(&dispStateMsg->requestCounter);
        return MI_FALSE;
    }

    return MI_TRUE;
}

static MI_Boolean _DispatchAssocReq(
    Disp* self,
    const ZChar* className,
    const AssociationsOfReq* req,
    DispResultMsg* dispStateMsg)
{
    const ProvRegEntry* entry;
    AssociationsOfReq* msg;
    MI_Result r;

    /* Attempt to find a provider for this class */
    {
        entry = ProvReg_FindProviderForClass(&self->provreg,
            req->nameSpace, className);

        if (!entry)
            return MI_FALSE;
    }

    /* Create new request to send to provider */
    msg = AssociationsOfReq_New(req->base.msgID, req->base.flags, AssociatorsOfReqTag);
    msg->base.clientID = req->base.clientID;
    msg->base.uid = req->base.uid;
    msg->base.gid = req->base.gid;
    /* original request will be kept for the request duration, so perform shallow copy only */
    /*ATTN! perform full copy*/
    msg->nameSpace = req->nameSpace;
    msg->assocClass = req->assocClass;
    msg->resultClass = req->resultClass;
    msg->role = req->role;
    msg->resultRole = req->resultRole;
    msg->instance = req->instance;
    msg->packedInstancePtr = req->packedInstancePtr;
    msg->packedInstanceSize = req->packedInstanceSize;
    msg->base.userAgent = req->base.userAgent;

    msg->className = className;

    AtomicInc(&dispStateMsg->requestCounter);
    Message_SetRequest(&msg->base, &dispStateMsg->base);

    /* Setup callback */
    msg->base.callback = _ProviderToDispatcherCallback;
    msg->base.callbackData = self;

    /* Send the request to provider manager */
    r = AgentMgr_HandleRequest(&self->agentmgr, &msg->base, entry);

    /* Release the original message */
    AssociationsOfReq_Release(msg);

    /* Log failure */
    if (r != MI_RESULT_OK)
    {
        LOGW((ZT("AgentMgr_HandleRequest() failed: %u: %Z"), r,
            zcs(Result_ToString(r))));

        AtomicDec(&dispStateMsg->requestCounter);
        return MI_FALSE;
    }

    return MI_TRUE;
}

static MI_Boolean _DispatchRefReq(
    Disp* self,
    const ZChar* className,
    const AssociationsOfReq* req,
    DispResultMsg* dispStateMsg)
{
    const ProvRegEntry* entry;
    AssociationsOfReq* msg;
    MI_Result r;

    /* Attempt to find a provider for this class */
    {
        entry = ProvReg_FindProviderForClass(&self->provreg,
            req->nameSpace, className);

        if (!entry)
            return MI_FALSE;
    }

    /* Create new request to send to provider */
    msg = AssociationsOfReq_New(req->base.msgID, req->base.flags, ReferencesOfReqTag);
    msg->base.clientID = req->base.clientID;
    msg->base.uid = req->base.uid;
    msg->base.gid = req->base.gid;
    /* original request will be kept for the request duration, so perform shallow copy only */
    /*ATTN! perform full copy*/
    msg->nameSpace = req->nameSpace;
    msg->assocClass = req->assocClass;
    msg->role = req->role;
    msg->instance = req->instance;
    msg->packedInstancePtr = req->packedInstancePtr;
    msg->packedInstanceSize = req->packedInstanceSize;
    msg->base.userAgent = req->base.userAgent;

    msg->className = className;

    AtomicInc(&dispStateMsg->requestCounter);
    Message_SetRequest(&msg->base, &dispStateMsg->base);

    /* Setup callback */
    msg->base.callback = _ProviderToDispatcherCallback;
    msg->base.callbackData = self;

    /* Send the request to provider manager */
    r = AgentMgr_HandleRequest(&self->agentmgr, &msg->base, entry);

    /* Release the original message */
    AssociationsOfReq_Release(msg);

    /* Log failure */
    if (r != MI_RESULT_OK)
    {
        LOGW((ZT("AgentMgr_HandleRequest() failed: %u: %Z"), r,
            zcs(Result_ToString(r))));

        AtomicDec(&dispStateMsg->requestCounter);
        return MI_FALSE;
    }

    return MI_TRUE;
}

static MI_Result _SendErrorResponse(
    Message* req,
    MI_Result r
    )
{
    PostResultMsg* resp;

    resp = PostResultMsg_New( req->msgID );

    if (!resp)
        return MI_RESULT_FAILED;

    resp->result = r;
    Message_SetRequest(&resp->base,req);
    (*req->callback)(&resp->base, req->callbackData);

    PostResultMsg_Release(resp);

    return MI_RESULT_OK;
}

static MI_Result _HandleEnumerateInstancesReq(
    Disp* self,
    EnumerateInstancesReq* req)
{
    ProvRegPosition pos;
    MI_Result r;
    MI_Boolean sentOk = MI_FALSE;
    DispResultMsg* dispStateMsg;

    /* Validate input parameters */
    if (!req->className || !req->nameSpace)
        return MI_RESULT_INVALID_PARAMETER;

    /* create a state message that will keep track of results from providers */
    dispStateMsg = DispResultMsg_New(req->base.msgID);
    if (dispStateMsg == NULL)
        return MI_RESULT_FAILED;

    /* add one for sending thread so first 'fast' provider will not send its response all the way */
    AtomicInc(&dispStateMsg->requestCounter);

    dispStateMsg->base.clientID = req->base.clientID;
    /* Setup callback */
    dispStateMsg->base.callback = req->base.callback;
    dispStateMsg->base.callbackData = req->base.callbackData;

    /* Precompile the query */
    req->wql = NULL;
    if (req->queryLanguage != NULL || req->queryExpression != NULL)
    {
        /* Fail if either query language or expression is missing */
        if (req->queryLanguage == NULL || req->queryExpression == NULL)
        {
            LOGW((ZT("queryLanguage or queryExpression is missing")));
            r = MI_RESULT_INVALID_QUERY;
            goto sendErrorBack;
        }

        /* Reject non-WQL queries */
        if (Zcmp(req->queryLanguage, ZT("WQL")) != 0)
        {
            LOGW((ZT("unknown query language: %Z"), zcs(req->queryLanguage)));
            r = MI_RESULT_QUERY_LANGUAGE_NOT_SUPPORTED;
            goto sendErrorBack;
        }

        /* Compile the query */
        {
            req->wql = WQL_Parse(req->queryExpression, req->base.batch);

            if (req->wql == NULL)
            {
                LOGW((ZT("invalid query expression: %Z"),
                    zcs(req->queryExpression)));
                r = MI_RESULT_INVALID_QUERY;
                goto sendErrorBack;
            }
        }

        /* WQL queries from WinRM pass '*' as the class name */

        if (Zcmp(req->className, ZT("*")) == 0)
        {
            req->className = req->wql->className;
        }

        /* Verify that the query classname matches the enumeration classname */
        if (Zcmp(req->wql->className, req->className) != 0)
        {
            LOGW((ZT("query/enumeration class name mismatch: %Z/%Z"),
                zcs(req->wql->className), zcs(req->className)));
            r = MI_RESULT_INVALID_QUERY;
            goto sendErrorBack;
        }
    }

    /* Send to direct name */
    if (_DispatchEnumerateInstancesReq(self, req->className, req, dispStateMsg))
        sentOk = MI_TRUE;

    if (req->deepInheritance)
    {
        /* Begin enumeration of classes for this request */
        {
            r = ProvReg_BeginClasses(&self->provreg, req->nameSpace,
                req->className, MI_TRUE, &pos);

            if (MI_RESULT_OK != r)
            {
                LOGD((ZT("ProvReg_BeginClasses() failed: %u: %Z"),
                    r, zcs(Result_ToString(r))));

                LOGI((ZT("unknown class in enumerate request: %Z:%Z"),
                    zcs(req->nameSpace), zcs(req->className)));

                /* send error back to caller */
                goto sendErrorBack;
            }
        }

        /* While more classes */
        for ( ; ; )
        {
            const ZChar* derived = NULL;
            MI_Boolean done;

            r = ProvReg_NextClass(&pos, &derived, &done);

            if (done)
                break;

            if (MI_RESULT_OK != r)
            {
                LOGD((ZT("ProvReg_NextClass() failed: %u: %Z"),
                    r, zcs(Result_ToString(r))));

                LOGI((ZT("unknown class in enumerate request: %Z:%Z"),
                    zcs(req->nameSpace), zcs(req->className)));

                /* send error back to caller */
                goto sendErrorBack;
            }

            if (_DispatchEnumerateInstancesReq(self, derived, req, dispStateMsg))
                sentOk = MI_TRUE;
        }

        /* Finalize enumeration */
        {
            r = ProvReg_EndClasses(&pos);

            if (MI_RESULT_OK != r)
            {
                LOGD((ZT("ProvReg_EndClasses() failed: %u: %Z"),
                    r, zcs(Result_ToString(r))));
                /* send error back to caller */
                goto sendErrorBack;
            }
        }
    } /* if deep*/

    /* Fail if no provider was found for request */
    if (!sentOk)
    {
        LOGD((ZT("found no providers for class: %Z"),
            zcs(MI_GET_SAFE_PRINTF_STRING(req->className))));
        r = MI_RESULT_NOT_FOUND;
        goto sendErrorBack;
    }

    if ( AtomicDec(&dispStateMsg->requestCounter) )
    {   /* last result - forward it to the net stack */
        r = dispStateMsg->result;
        goto sendErrorBack;
    }

    if (req->wql != NULL)
    {
        WQL_Delete(req->wql);
        req->wql = NULL;
    }
    DispResultMsg_Release(dispStateMsg);
    return MI_RESULT_OK;

sendErrorBack:
    if (req->wql != NULL)
    {
        WQL_Delete(req->wql);
        req->wql = NULL;
    }
    DispResultMsg_Release(dispStateMsg);
    return _SendErrorResponse(&req->base,r);
}


static MI_Result _HandleGetInstanceReq(
    Disp* self,
    GetInstanceReq* req)
{
    MI_Result r;
    const ProvRegEntry* reg;

    /* Validate input parameters */
    if (!req->instanceName || !req->nameSpace)
        return MI_RESULT_INVALID_PARAMETER;

    // Find a provider for this class.
    reg = ProvReg_FindProviderForClass(&self->provreg, req->nameSpace,
        req->instanceName->classDecl->name );

    if (!reg)
    {
        r = MI_RESULT_INVALID_NAMESPACE; /*ATTN! or class?*/
        LOGD((ZT("cannot find provider for class: %Z/%Z"),
            zcs(MI_GET_SAFE_PRINTF_STRING(req->nameSpace)),
            zcs(MI_GET_SAFE_PRINTF_STRING(req->instanceName->classDecl->name))));
        goto sendErrorBack;
    }

    // Send the request to provider manager.
    r = AgentMgr_HandleRequest(&self->agentmgr, &req->base, reg);

    if (r != MI_RESULT_OK)
    {
        LOGD((ZT("AgentMgr_HandleRequest for namespace: %Z"),
            zcs(MI_GET_SAFE_PRINTF_STRING(req->nameSpace))));
        goto sendErrorBack;
    }

    return MI_RESULT_OK;

sendErrorBack:
    return _SendErrorResponse(&req->base,r);
}

static MI_Result _HandleCreateInstanceReq(
    Disp* self,
    CreateInstanceReq* req)
{
    MI_Result r;
    const ProvRegEntry* reg;

    /* Validate input parameters */
    if (!req->instance || !req->nameSpace)
        return MI_RESULT_INVALID_PARAMETER;

    // Find a provider for this class.
    reg = ProvReg_FindProviderForClass(&self->provreg, req->nameSpace,
        req->instance->classDecl->name );

    if (reg == NULL)
    {
        r = MI_RESULT_INVALID_NAMESPACE; /*ATTN! or class?*/
        LOGD((ZT("cannot find provider for class: %Z/%Z"),
            zcs(MI_GET_SAFE_PRINTF_STRING(req->nameSpace)),
            zcs(MI_GET_SAFE_PRINTF_STRING(req->instance->classDecl->name))));
        goto sendErrorBack;
    }

    // Send the request to provider manager.
    r = AgentMgr_HandleRequest(&self->agentmgr, &req->base, reg);

    if (r != MI_RESULT_OK)
    {
        LOGD((ZT("AgentMgr_HandleRequest for namespace: %Z"),
            zcs(MI_GET_SAFE_PRINTF_STRING(req->nameSpace))));
        goto sendErrorBack;
    }

    return MI_RESULT_OK;

sendErrorBack:
    return _SendErrorResponse(&req->base,r);
}

static MI_Result _HandleModifyInstanceReq(
    Disp* self,
    ModifyInstanceReq* req)
{
    MI_Result r;
    const ProvRegEntry* reg;

    /* Validate input parameters */
    if (!req->instance || !req->nameSpace)
        return MI_RESULT_INVALID_PARAMETER;

    // Find a provider for this class.
    reg = ProvReg_FindProviderForClass(&self->provreg, req->nameSpace,
        req->instance->classDecl->name );

    if (!reg)
    {
        r = MI_RESULT_INVALID_NAMESPACE; /*ATTN! or class?*/
        LOGD((ZT("cannot find provider for class: %Z/%Z"),
            zcs(MI_GET_SAFE_PRINTF_STRING(req->nameSpace)),
            zcs(MI_GET_SAFE_PRINTF_STRING(req->instance->classDecl->name))));
        goto sendErrorBack;
    }

    // Send the request to provider manager.
    r = AgentMgr_HandleRequest(&self->agentmgr, &req->base, reg);

    if (r != MI_RESULT_OK)
    {
        LOGD((ZT("AgentMgr_HandleRequest for namespace: %Z"),
            zcs(MI_GET_SAFE_PRINTF_STRING(req->nameSpace))));
        goto sendErrorBack;
    }

    return MI_RESULT_OK;

sendErrorBack:
    return _SendErrorResponse(&req->base,r);
}

static MI_Result _HandleDeleteInstanceReq(
    Disp* self,
    DeleteInstanceReq* req)
{
    MI_Result r;
    const ProvRegEntry* reg;

    /* Validate input parameters */
    if (!req->instanceName || !req->nameSpace)
        return MI_RESULT_INVALID_PARAMETER;

    // Find a provider for this class.
    reg = ProvReg_FindProviderForClass(&self->provreg, req->nameSpace,
        req->instanceName->classDecl->name);

    if (!reg)
    {
        r = MI_RESULT_INVALID_NAMESPACE; /*ATTN! or class?*/
        LOGD((ZT("cannot find provider for class: %Z/%Z"),
            zcs(MI_GET_SAFE_PRINTF_STRING(req->nameSpace)),
            zcs(MI_GET_SAFE_PRINTF_STRING(req->instanceName->classDecl->name))));
        goto sendErrorBack;
    }

    // Send the request to provider manager.
    r = AgentMgr_HandleRequest(&self->agentmgr, &req->base, reg);

    if (r != MI_RESULT_OK)
    {
        LOGD((ZT("AgentMgr_HandleRequest for namespace: %Z"),
            zcs(MI_GET_SAFE_PRINTF_STRING(req->nameSpace))));
        goto sendErrorBack;
    }

    return MI_RESULT_OK;

sendErrorBack:
    return _SendErrorResponse(&req->base,r);
}

static MI_Result _HandleSubscribeReq(
    Disp* self,
    SubscribeReq* req)
{
    MI_Result r;
    const ProvRegEntry* reg = 0;
    SubscribeReq* msg = 0;

    /* Validate input parameters */
    if (!req->className || !req->nameSpace || !req->language || !req->filter)
        return MI_RESULT_INVALID_PARAMETER;

    // Duplicate incoming request to substitute callback pointer
    msg = SubscribeReq_New(req->base.msgID, req->base.flags);
    if (!msg)
    {
        r = MI_RESULT_FAILED;
        goto sendErrorBack;
    }

    msg->base.uid = req->base.uid;
    msg->base.gid = req->base.gid;
    msg->nameSpace = Batch_Zdup(msg->base.batch, req->nameSpace);
    msg->className = Batch_Zdup(msg->base.batch, req->className);
    msg->filter = Batch_Zdup(msg->base.batch, req->filter);
    msg->language = Batch_Zdup(msg->base.batch, req->language);
    msg->base.userAgent = req->base.userAgent;

    if (!msg->nameSpace || !msg->className || !msg->filter || !msg->language)
    {
        r = MI_RESULT_FAILED;
        goto sendErrorBack;
    }

    msg->base.clientID = req->base.clientID;

    Message_SetRequest(&msg->base, &req->base);

    /* Setup callback */
    msg->base.callback = _ProviderToDispatcherCallback;
    msg->base.callbackData = self;

    // Find a indication context by ns/cn
    Mutex_Lock(&self->mt);

    r = _FindCreateIndCtx( self, msg, &reg );

    Mutex_Unlock(&self->mt);

    /* check if error was detected */
    if (MI_RESULT_OK != r)
        goto sendErrorBack;

    /* empty reg with OK means context is being initialized;
        sub command will be processed later, once EnableIndicaitons is processed */
    if (!reg)
        return MI_RESULT_OK;

    // Send the request to provider manager.
    r = AgentMgr_HandleRequest(&self->agentmgr, &msg->base, reg);

    if (r != MI_RESULT_OK)
    {
        LOGD((ZT("AgentMgr_HandleRequest for namespace: %Z"),
            zcs(MI_GET_SAFE_PRINTF_STRING(req->nameSpace))));
        goto sendErrorBack;
    }

    SubscribeReq_Release(msg);

    return MI_RESULT_OK;

sendErrorBack:
    if (msg)
        SubscribeReq_Release(msg);

    return _SendErrorResponse(&req->base,r);
}

static MI_Result _HandleInvokeReq(
    Disp* self,
    InvokeReq* req)
{
    MI_Result r;
    const ProvRegEntry* reg;
    MI_ConstString cn = 0;

    /* Validate input parameters */
    if (!req->nameSpace)
        return MI_RESULT_INVALID_PARAMETER;

    if (req->className)
        cn = req->className;
    else if (req->instance)
        cn = req->instance->classDecl->name;

    if (!cn)
    {
        r = MI_RESULT_INVALID_CLASS;
        LOGD((ZT("class name is expected for invoke\n")));
        goto sendErrorBack;
    }


    // Find a provider for this class.
    reg = ProvReg_FindProviderForClass(&self->provreg, req->nameSpace, cn);

    if (!reg)
    {
        r = MI_RESULT_INVALID_NAMESPACE; /*ATTN! or class?*/
        LOGD((ZT("cannot find provider for class: %Z"),
            zcs(MI_GET_SAFE_PRINTF_STRING(cn))));
        goto sendErrorBack;
    }

    // Send the request to provider manager.
    r = AgentMgr_HandleRequest(&self->agentmgr, &req->base, reg);

    if (r != MI_RESULT_OK)
    {
        LOGD((ZT("AgentMgr_HandleRequest for namespace: %Z"),
            MI_GET_SAFE_PRINTF_STRING(req->nameSpace)));
        goto sendErrorBack;
    }

    return MI_RESULT_OK;

sendErrorBack:
    return _SendErrorResponse(&req->base,r);
}


static MI_Result _HandleAssociatorsOfReq(
    Disp* self,
    AssociationsOfReq* req)
{
    MI_Result r;
    MI_ConstString cn = 0;
    DispResultMsg* dispStateMsg;
    ProvRegAssocPosition pos;
    MI_Boolean sentOk = MI_FALSE;
    HashTable classNames;

    /* Create a hash table of class names */

    r = HashTable_Init(
        &classNames,
        64,
        ClassNameHash,
        ClassNameEqual,
        ClassNameRelease);

    if (r != 0)
        return MI_RESULT_FAILED;

    /* Validate input parameters */
    if (!req->instance || !req->nameSpace)
        return MI_RESULT_INVALID_PARAMETER;

    /* create a state message that will keep track of results from providers */
    dispStateMsg = DispResultMsg_New(req->base.msgID);
    if (!dispStateMsg)
        return MI_RESULT_FAILED;

    /* add one for sending thread so first 'fast' provider will not send its response all the way */
    AtomicInc(&dispStateMsg->requestCounter);

    dispStateMsg->base.clientID = req->base.clientID;
    /* Setup callback */
    dispStateMsg->base.callback = req->base.callback;
    dispStateMsg->base.callbackData = req->base.callbackData;
    Message_SetRequest(&dispStateMsg->base, &req->base);

    r = ProvReg_BeginAssocClasses(&self->provreg, req->nameSpace,
        req->instance->classDecl->name,
        req->assocClass, req->resultClass, &pos);

    if (MI_RESULT_OK != r)
    {
        LOGD((ZT("ProvReg_BeginAssocClasses() failed: %u: Zs"),
            r, zcs(Result_ToString(r))));

        /* send error back to caller */
        goto sendErrorBack;
    }

    /* ATTN: there is a bug in the provider registration tree causing
     * the association provider to be called twice. To avoid this for now,
     * we maintain a hash table of already dispatched classes.
     */

    /* While more classes */
    for ( ; ; )
    {
        MI_Boolean done;
        r = ProvReg_NextAssocClass(&pos, &cn, &done);

        if (done)
            break;

        if (MI_RESULT_OK != r)
        {
            LOGD((ZT("ProvReg_NextAssocClass() failed: %u: %Z"),
                r, zcs(Result_ToString(r))));
            /* send error back to caller */
            goto sendErrorBack;
        }

        /* Check whether this class has been dispatched */
        {
            ClassNameBucket bucket;
            bucket.key = (ZChar*)cn;

            if (!HashTable_Find(&classNames, (const HashBucket*)&bucket))
            {
                if (_DispatchAssocReq(self, cn, req, dispStateMsg))
                    sentOk = MI_TRUE;

                {
                    ClassNameBucket* bucket = (ClassNameBucket*)calloc(
                        1, sizeof(ClassNameBucket));

                    if (!bucket)
                    {
                        r = MI_RESULT_FAILED;
                        goto sendErrorBack;
                    }

                    bucket->key = Zdup(cn);

                    if (HashTable_Insert(&classNames, (HashBucket*)bucket) != 0)
                    {
                        r = MI_RESULT_FAILED;
                        goto sendErrorBack;
                    }
                }
            }
        }
    }

    /* Finalize enumeration */
    {
        r = ProvReg_EndAssocClasses(&pos);

        if (MI_RESULT_OK != r)
        {
            LOGD((ZT("ProvReg_EndAssocClasses() failed: %u: %Z"),
                r, zcs(Result_ToString(r))));
            /* send error back to caller */
            goto sendErrorBack;
        }
    }

    /* Fail if no provider was found for request */
    if (!sentOk)
    {
        LOGD((ZT("found no providers for class: %Z"),
            zcs(req->instance->classDecl->name)));
        r = MI_RESULT_NOT_FOUND;
        goto sendErrorBack;
    }

    if ( AtomicDec(&dispStateMsg->requestCounter) )
    {   /* last result - forward it to the net stack */
        r = dispStateMsg->result;
        goto sendErrorBack;
    }

    HashTable_Destroy(&classNames);
    DispResultMsg_Release(dispStateMsg);
    return MI_RESULT_OK;

sendErrorBack:
    DispResultMsg_Release(dispStateMsg);
    HashTable_Destroy(&classNames);
    return _SendErrorResponse(&req->base,r);
}

static MI_Result _HandleReferencesOfReq(
    Disp* self,
    AssociationsOfReq* req)
{
    MI_Result r;
    MI_ConstString cn = 0;
    DispResultMsg* dispStateMsg;
    ProvRegAssocPosition pos;
    MI_Boolean sentOk = MI_FALSE;

    /* Validate input parameters */
    if (!req->instance || !req->nameSpace)
        return MI_RESULT_INVALID_PARAMETER;

    /* create a state message that will keep track of results from providers */
    dispStateMsg = DispResultMsg_New(req->base.msgID);
    if (!dispStateMsg)
        return MI_RESULT_FAILED;

    /* add one for sending thread so first 'fast' provider will not send its response all the way */
    AtomicInc(&dispStateMsg->requestCounter);

    dispStateMsg->base.clientID = req->base.clientID;
    /* Setup callback */
    dispStateMsg->base.callback = req->base.callback;
    dispStateMsg->base.callbackData = req->base.callbackData;
    Message_SetRequest(&dispStateMsg->base, &req->base);

    r = ProvReg_BeginAssocClasses(&self->provreg,
                                  req->nameSpace,
                                  req->instance->classDecl->name,
                                  req->assocClass,
                                  0,
                                  &pos);

    if (MI_RESULT_OK != r)
    {
        LOGD((ZT("ProvReg_BeginAssocClasses() failed: %u: %Z"),
            r, zcs(Result_ToString(r))));

        /* send error back to caller */
        goto sendErrorBack;
    }

    /* While more classes */
    for ( ; ; )
    {
        MI_Boolean done;

        r = ProvReg_NextAssocClass(&pos, &cn, &done);
        if (done)
            break;

        if (MI_RESULT_OK != r)
        {
            LOGD((ZT("ProvReg_NextAssocClass() failed: %u: %Z"),
                r, zcs(Result_ToString(r))));
            /* send error back to caller */
            goto sendErrorBack;
        }

        if (_DispatchRefReq(self, cn, req, dispStateMsg))
            sentOk = MI_TRUE;
    }

    /* Finalize enumeration */
    {
        r = ProvReg_EndAssocClasses(&pos);

        if (MI_RESULT_OK != r)
        {
            LOGD((ZT("ProvReg_EndAssocClasses() failed: %u: %Z"),
                r, zcs(Result_ToString(r))));
            /* send error back to caller */
            goto sendErrorBack;
        }
    }

    /* Fail if no provider was found for request */
    if (!sentOk)
    {
        LOGD((ZT("found no providers for class: %Z"),
            zcs(req->instance->classDecl->name)));
        r = MI_RESULT_NOT_FOUND;
        goto sendErrorBack;
    }

    if (AtomicDec(&dispStateMsg->requestCounter))
    {   /* last result - forward it to the net stack */
        r = dispStateMsg->result;
        goto sendErrorBack;
    }

    DispResultMsg_Release(dispStateMsg);
    return MI_RESULT_OK;

sendErrorBack:
    DispResultMsg_Release(dispStateMsg);
    return _SendErrorResponse(&req->base,r);
}

/*
**==============================================================================
**
** Public definitions
**
**==============================================================================
*/

MI_Result Disp_Init(Disp* self, Selector* selector)
{
    /* Check parameters */
    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

    memset(self, 0, sizeof(Disp));

#if 0
    /* Initialize the provider registry */
    MI_RETURN_ERR(ProvReg_Init(&self->provreg, GetPath(ID_REGISTERFILE)));
#else
    MI_RETURN_ERR(ProvReg_Init2(&self->provreg));
#endif

    /* Initialize the provider manager */
    MI_RETURN_ERR(AgentMgr_Init(&self->agentmgr, selector));

    /* Initialize indications part */
    MI_RETURN_ERR(Mutex_Init(&self->mt));

    return MI_RESULT_OK;
}

MI_Result Disp_Destroy(Disp* self)
{
    MI_RETURN_ERR(AgentMgr_Destroy(&self->agentmgr));
    ProvReg_Destroy(&self->provreg);

    /*ATTN! remove indication contexts! */
    Mutex_Destroy(&self->mt);
    return MI_RESULT_OK;
}

MI_Result Disp_HandleRequest(
    Disp* self,
    Message* msg)
{
    LOGD((ZT("Disp_HandleRequest")));

    switch (msg->tag)
    {
        case EnumerateInstancesReqTag:
        {
            EnumerateInstancesReq* req = (EnumerateInstancesReq*)msg;
            return _HandleEnumerateInstancesReq(self, req);
        }

        case GetInstanceReqTag:
        {
            GetInstanceReq* req = (GetInstanceReq*)msg;
            return _HandleGetInstanceReq(self, req);
        }

        case CreateInstanceReqTag:
        {
            CreateInstanceReq* req = (CreateInstanceReq*)msg;
            return _HandleCreateInstanceReq(self, req);
        }

        case ModifyInstanceReqTag:
        {
            ModifyInstanceReq* req = (ModifyInstanceReq*)msg;
            return _HandleModifyInstanceReq(self, req);
        }

        case DeleteInstanceReqTag:
        {
            DeleteInstanceReq* req = (DeleteInstanceReq*)msg;
            return _HandleDeleteInstanceReq(self, req);
        }

        case InvokeReqTag:
        {
            InvokeReq* req = (InvokeReq*)msg;
            return _HandleInvokeReq(self, req);
        }

        case AssociatorsOfReqTag:
        {
            AssociationsOfReq* req = (AssociationsOfReq*)msg;
            return _HandleAssociatorsOfReq(self, req);
        }

        case ReferencesOfReqTag:
        {
            AssociationsOfReq* req = (AssociationsOfReq*)msg;
            return _HandleReferencesOfReq(self, req);
        }

        case SubscribeReqTag:
        {
            SubscribeReq* req = (SubscribeReq*)msg;
            return _HandleSubscribeReq(self, req);
        }

        default:
        {
            /* Unsupported mesage type */
            return _SendErrorResponse(msg,MI_RESULT_NOT_SUPPORTED);
        }
    }
}
