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

#include "context.h"
#include <wsman/wsbuf.h>
#include <wql/wql.h>
#include <io/io.h>

// #define ENABLE_TRACING
// #define TRACING_LEVEL 4
#include <logging.h>

static MI_Result _ProcessResult(
    MI_Context* self_,
    MI_Result result,
    const ZChar* message,
    const MI_Instance* error)
{
    Context* self = (Context*)self_;

    if (self == NULL || self->magic != CONTEXT_UNPOSTED_MAGIC)
        return MI_RESULT_INVALID_PARAMETER;

    LOGD((ZT("_ProcessResult - Begin")));
    LOGD2((ZT("_ProcessResult - Begin")));

    /* If no instances matched during GetInstance over EnumerateInstance */
    if (self->instanceName != NULL && !self->matchedInstanceName)
    {
        LOGW2((ZT("_ProcessResult - No matching instance name")));
        if (result == MI_RESULT_OK)
            result = MI_RESULT_NOT_FOUND;
    }

    message = message;
    error = error;

    if (self->request != NULL && !self->cancelled)
    {
        PostResultMsg* resp = PostResultMsg_New(self->request->msgID);

        if (resp == NULL)
        {
            LOGE2((ZT("_ProcessResult - PostResultMsg_New failed")));
            return MI_RESULT_FAILED;
        }

        resp->result = result;
        Message_SetRequest(&resp->base,self->request);
        (*self->request->callback)(&resp->base, self->request->callbackData);
        PostResultMsg_Release(resp);
    }

    if (self->result != NULL)
        *self->result = result;

    /* indicate that result was posted */
    self->magic = CONTEXT_POSTED_MAGIC;

    LOGD2((ZT("_ProcessResult - OK exit")));

    return MI_RESULT_OK;
}

static MI_Boolean _FilterProperty(const ZChar* name, void *data)
{
    WQL* wql = (WQL*)data;

    if (WQL_ContainsProperty(wql, name))
        return MI_FALSE;
    else
        return MI_TRUE;
}

static MI_Result _PostInstanceToCallback(
    Context* self,
    const MI_Instance* instance)
{
    PostInstanceMsg* resp = PostInstanceMsg_New(self->request->msgID);

    LOGD2((ZT("_PostInstanceToCallback - Begin")));

    if (resp == NULL)
    {
        LOGE2((ZT("_PostInstanceToCallback - PostInstanceMsg_New failed")));
        return MI_RESULT_FAILED;
    }

    if (self->request->flags & WSMANFlag)
    {
        const MI_ClassDecl* castToClassDecl = 0;

        /* Enumerate response with 'base-properties-only' option may require instance conversion */
        if (EnumerateInstancesReqTag == self->request->tag)
        {
            EnumerateInstancesReq* req = (EnumerateInstancesReq*)self->request;

            if (req->requestClassName)
            {
                castToClassDecl = instance->classDecl;

                while (castToClassDecl != NULL &&
                       Zcasecmp(req->requestClassName, castToClassDecl->name) != 0)
                {
                    castToClassDecl = castToClassDecl->superClassDecl;
                }
            }
        }

        {
            EnumerateInstancesReq* req = NULL;

            if (EnumerateInstancesReqTag == self->request->tag)
                req = (EnumerateInstancesReq*)self->request;

            if (req != NULL && req->wql != NULL)
            {
                WSBuf_InstanceToBuf(
                    self->request->userAgent,
                    instance,
                    _FilterProperty,
                    req->wql,
                    castToClassDecl,
                    resp->base.batch,
                    self->request->flags,
                    &resp->packedInstancePtr,
                    &resp->packedInstanceSize);
            }
            else
            {
                WSBuf_InstanceToBuf(
                    self->request->userAgent,
                    instance,
                    NULL, /* filterProperty */
                    NULL, /* filterPropertyData */
                    castToClassDecl,
                    resp->base.batch,
                    self->request->flags,
                    &resp->packedInstancePtr,
                    &resp->packedInstanceSize);
            }
        }

        resp->base.flags |= self->request->flags;
    }
    else
    {
        EnumerateInstancesReq* req = NULL;

        if (EnumerateInstancesReqTag == self->request->tag)
        {
            req = (EnumerateInstancesReq*)self->request;
        }

        if (req != NULL && req->wql != NULL)
        {
            MI_Result r = InstanceToBatch(
                instance,
                _FilterProperty,
                req->wql,
                resp->base.batch,
                &resp->packedInstancePtr,
                &resp->packedInstanceSize);

            if (r != MI_RESULT_OK)
            {
                LOGE((ZT("failed to pack instance: %u"), r));
                LOGE2((ZT("_PostInstanceToCallback - Failure packing instance. Error: %d (%s)"), (int)r, mistrerror(r)));
            }
        }
        else
        {
            MI_Result r = InstanceToBatch(
                instance,
                NULL,
                NULL,
                resp->base.batch,
                &resp->packedInstancePtr,
                &resp->packedInstanceSize);

            if (r != MI_RESULT_OK)
            {
                LOGE((ZT("failed to pack instance: %u"), r));
                LOGE2((ZT("_PostInstanceToCallback - Failure packing instance. Error: %d (%s)"), (int)r, mistrerror(r)));
            }
        }

        resp->base.flags |= BinaryProtocolFlag;
    }

    /* count message in for back-pressure feature (only Instances) */
    if (self->provider != NULL)
    {
        Provider_NewInstanceCreated(self->provider, &resp->base);
    }

    Message_SetRequest(&resp->base, self->request);
    (*self->request->callback)(&resp->base, self->request->callbackData);
    PostInstanceMsg_Release(resp);

    LOGD2((ZT("_PostInstanceToCallback - OK exit")));

    return MI_RESULT_OK;
}

/* successfully received instance from 'gi' - call invoke with this instance now */
static void _CallInvoke(
    Context* self,
    const MI_Instance* instance)
{
    Context* ctx = (Context*)Batch_GetClear(self->request->batch, sizeof(Context));;

    Context_Init(ctx, self->provider);

    ctx->request = self->request;
    /* message will be freed in context release*/
    Message_AddRef(ctx->request);

    /* disregard all other messages for this context */
    self->cancelled = MI_TRUE;
    /* ATTN! clone instance, since invoke can overlive instance (if it's async)!!! */
    (*self->md->function)(self->prov_self, &ctx->base,
        __nameSpace, __className, __methodName, instance, self->instParams);
}

static MI_Result MI_CALL _PostResult(
    MI_Context* self_,
    MI_Result result)
{
    return _ProcessResult(self_, result, 0, 0);
}

static MI_Result MI_CALL _PostInstance(
    MI_Context* self_,
    const MI_Instance* instance)
{
    Context* self = (Context*)self_;

    LOGD2((ZT("_PostInstance - Begin")));

    if (self == NULL || self->magic != CONTEXT_UNPOSTED_MAGIC || instance == NULL)
    {
        LOGE2((ZT("_PostInstance - Bad parameter")));
        return MI_RESULT_INVALID_PARAMETER;
    }

    if (self->request != NULL && !self->cancelled)
    {
        if (self->instanceName == NULL)
        {
            if (CTX_TYPE_INVOKE_WITH_INSTANCE == self->chainType)
            {
                _CallInvoke(self, instance);
                LOGD2((ZT("_PostInstance - Invoke succeeded. Returning OK")));
                return MI_RESULT_OK;
            }
            else if (EnumerateInstancesReqTag == self->request->tag)
            {
                EnumerateInstancesReq* req = (EnumerateInstancesReq*)self->request;

                if (req->wql != NULL)
                {
                    int r;

                    r = WQL_Eval(req->wql, WQL_LookupInstanceProperty, (void*)instance);

                    if (r == 0)
                    {
                        /* Instance matched the query */
                        LOGD2((ZT("_PostInstance - Matching instance for query. Returning through callback")));
                        return _PostInstanceToCallback(self, instance);
                    }
                    else
                    {
                        /* Mismatch or failure */
                        LOGW2((ZT("_PostInstance - Mismatch or failure in WQL query. Returning OK")));
                        return MI_RESULT_OK;
                    }
                }
            }

            LOGD2((ZT("_PostInstance - Returning through PostInstanceToCallback")));
            return _PostInstanceToCallback(self, instance);
        }
        else if (Instance_MatchKeys(instance, self->instanceName))
        {
            /* Handle GetInstance through EnumerateInstances */
            if (!self->matchedInstanceName)
            {
                self->matchedInstanceName = MI_TRUE;
                LOGD2((ZT("_PostInstance - Matched name. Returning through PostInstanceToCallback")));
                return _PostInstanceToCallback(self, instance);
            }
        }
    }

    LOGW2((ZT("_PostInstance - Null or cancelled request, or no match of key fields. Returning OK")));
    return MI_RESULT_OK;
}

static Batch* _GetBatch(Context* self)
{
    if (self->request)
        return self->request->batch;

    if (self->loadRequest)
        return self->loadRequest->batch;

    return NULL;
}

static MI_Result MI_CALL _ConstructInstance(
    MI_Context* self_,
    const MI_ClassDecl* classDecl,
    MI_Instance* instance)
{
    Context* self = (Context*)self_;

    if (self == NULL || self->magic != CONTEXT_UNPOSTED_MAGIC || instance == NULL || classDecl == NULL)
        return MI_RESULT_INVALID_PARAMETER;

    return Instance_Construct(instance, classDecl, _GetBatch(self));
}

static MI_Result MI_CALL _ConstructParameters(
    MI_Context* self_,
    const MI_MethodDecl* methodDecl,
    MI_Instance* instance)
{
    Context* self = (Context*)self_;

    if (self == NULL || self->magic != CONTEXT_UNPOSTED_MAGIC || instance == NULL || methodDecl == NULL)
        return MI_RESULT_INVALID_PARAMETER;

    return Parameters_Init(instance, methodDecl, _GetBatch(self));
}

static MI_Result MI_CALL _NewInstance(
    MI_Context* self_,
    const MI_ClassDecl* classDecl,
    MI_Instance** instance)
{
    Context* self = (Context*)self_;

    if (self == NULL || self->magic != CONTEXT_UNPOSTED_MAGIC || classDecl == NULL || instance == NULL)
        return MI_RESULT_INVALID_PARAMETER;

    return Instance_New(instance, classDecl, _GetBatch(self));
}

static MI_Result MI_CALL _NewDynamicInstance(
    MI_Context* self_,
    const ZChar* className,
    MI_Uint32 flags,
    MI_Instance** instance)
{
    Context* self = (Context*)self_;

    if (self == NULL || self->magic != CONTEXT_UNPOSTED_MAGIC || className == NULL || instance == NULL)
        return MI_RESULT_INVALID_PARAMETER;

    return Instance_NewDynamic(instance, className, flags,
        _GetBatch(self));
}

static MI_Result MI_CALL _NewParameters(
    MI_Context* self_,
    const MI_MethodDecl* methodDecl,
    MI_Instance** instance)
{
    Context* self = (Context*)self_;

    if (self == NULL || self->magic != CONTEXT_UNPOSTED_MAGIC || methodDecl == NULL || instance == NULL)
        return MI_RESULT_INVALID_PARAMETER;

    return Parameters_New(instance, methodDecl, _GetBatch(self));
}

static MI_Result MI_CALL _Canceled(
    const MI_Context* self_,
    MI_Boolean* flag)
{
    Context* self = (Context*)self_;

    if (self == NULL || self->magic != CONTEXT_UNPOSTED_MAGIC || flag == NULL)
        return MI_RESULT_INVALID_PARAMETER;

    *flag = self->cancelled;
    return MI_RESULT_OK;
}

static MI_Result MI_CALL _PostIndication(
    MI_Context* context,
    const MI_Instance* indication,
    MI_Uint32 subscriptionIDCount,
    const ZChar* bookmark)
{
    /* ATTN: just use _PostInstance() for now */
    MI_UNUSED(subscriptionIDCount);
    MI_UNUSED(bookmark);
#if 0
    return _PostInstance(context, indication);
#endif
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _GetLocale(
    const MI_Context* context,
    MI_LocaleType localeType,
    ZChar locale[MI_MAX_LOCALE_SIZE])
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _RegisterCancel(
    MI_Context* context,
    MI_CancelCallback callback,
    void* callbackData)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result MI_CALL _RequestUnload(
    MI_Context* self_)
{
    Context* self = (Context*)self_;

    if (self == NULL || self->magic != CONTEXT_UNPOSTED_MAGIC || self->provider == NULL)
        return MI_RESULT_INVALID_PARAMETER;

    Provider_SetRefuseUnloadFlag(self->provider, MI_FALSE);
    return MI_RESULT_OK;
}

static MI_Result MI_CALL _RefuseUnload(
    MI_Context* self_)
{
    Context* self = (Context*)self_;

    if (self == NULL || self->magic != CONTEXT_UNPOSTED_MAGIC || self->provider == NULL)
        return MI_RESULT_INVALID_PARAMETER;

    Provider_SetRefuseUnloadFlag(self->provider, MI_TRUE);
    return MI_RESULT_OK;
}

static MI_Result _GetLocalSession(
    _In_ const MI_Context* context,
    _Out_ MI_Session* session)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result _SetStringOption(
    _In_ MI_Context* context,
    _In_z_ const ZChar* name,
    _In_z_ const ZChar* value)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result _GetStringOption(
    _In_  MI_Context* context,
    _In_z_ const ZChar* name,
    _Outptr_result_z_  const ZChar** value)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result _GetNumberOption(
    _In_  MI_Context* context,
    _In_z_ const ZChar *name,
    _Out_opt_  MI_Uint32* value)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result _GetCustomOption(
    _In_  MI_Context* context,
    _In_z_ const ZChar* name,
    _Out_opt_  MI_Type* valueType,
    _Out_opt_  MI_Value* value)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result _GetCustomOptionCount(
    _In_  MI_Context* context,
    _Out_opt_ MI_Uint32* count)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result _GetCustomOptionAt(
    _In_  MI_Context* context,
    _In_ MI_Uint32 index,
    _Outptr_opt_result_maybenull_z_  const ZChar** name,
    _Out_opt_  MI_Type* valueType,
    _Out_opt_  MI_Value* value)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result _WriteMessage(
    _In_ MI_Context* context,
    MI_Uint32 channel,
    _In_z_ const ZChar* message)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result _WriteProgress(
    _In_ MI_Context* context,
    _In_z_ const ZChar* activity,
    _In_z_ const ZChar* currentOperation,
    _In_z_ const ZChar* statusDescription,
    MI_Uint32 percentComplete,
    MI_Uint32 secondsRemaining)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result _WriteStreamParameter(
    _In_ MI_Context* context,
    _In_z_ const ZChar* name,
    _In_ const MI_Value* value,
    _In_ MI_Type type,
    _In_ MI_Uint32 flags)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result _WriteCimError(
    _In_ MI_Context* context,
    _In_ const MI_Instance *error,
    _Out_ MI_Boolean *flag)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result _PromptUser(
    _In_ MI_Context* context,
    _In_z_ const ZChar* message,
    MI_PromptType promptType,
    _Out_ MI_Boolean* result)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result _ShouldProcess(
    _In_ MI_Context* context,
    _In_z_ const ZChar* target,
    _In_z_ const ZChar* action,
    _Out_ MI_Boolean* result)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result _ShouldContinue(
    _In_ MI_Context* context,
    _In_z_ const ZChar* message,
    _Out_ MI_Boolean* result)
{
    return MI_RESULT_NOT_SUPPORTED;
}

static MI_Result _PostError(
    _In_ MI_Context* self,
    MI_Uint32 result,
    _In_z_ const ZChar* type,
    _In_z_ const ZChar* message)
{
    return _ProcessResult(self, result, message, NULL);
}

static MI_Result _PostCimError(
    _In_ MI_Context* self,
    _In_ const MI_Instance *error)
{
    return _ProcessResult(self, MI_RESULT_FAILED, 0, error);
}

static MI_Result _WriteError(
    _In_ MI_Context* context,
    MI_Uint32 resultCode,
    _In_z_ const ZChar* resultType,
    _In_z_ const ZChar* errorMessage,
    _Out_ MI_Boolean *flag)
{
    return MI_RESULT_NOT_SUPPORTED;
}

/* Function table for contexts */

MI_ContextFT __mi_contextFT =
{
    _PostResult,
    _PostInstance,
    _PostIndication,
    _ConstructInstance,
    _ConstructParameters,
    _NewInstance,
    _NewDynamicInstance,
    _NewParameters,
    _Canceled,
    _GetLocale,
    _RegisterCancel,
    _RequestUnload,
    _RefuseUnload,
    _GetLocalSession,
    _SetStringOption,
    _GetStringOption,
    _GetNumberOption,
    _GetCustomOption,
    _GetCustomOptionCount,
    _GetCustomOptionAt,
    _WriteMessage,
    _WriteProgress,
    _WriteStreamParameter,
    _WriteCimError,
    _PromptUser,
    _ShouldProcess,
    _ShouldContinue,
    _PostError,
    _PostCimError,
    _WriteError,
};

void Context_Init(
    Context* self,
    Provider* provider)
{
    memset(self, 0, sizeof(Context));
    self->base.ft = &__mi_contextFT;
    self->magic = CONTEXT_UNPOSTED_MAGIC;
    self->provider = provider;
    Provider_Addref(self->provider);
}

void Context_Destroy(
    Context* self)
{
    Message* request = self ? self->request : NULL;
    Message* loadRequest = self ? self->loadRequest : NULL;

    LOGD2((ZT("Context_Destroy - Begin")))

    if (self != NULL && self->provider != NULL)
    {
        Provider_Release(self->provider);
    }

    memset(self, 0xFF, sizeof (Context));       // change magic field to neither of CONTEXT{UNPOSTED,POSTED}_MAGIC

    /* Context typically allocated from message's batch
     * so it may be freed right inside 'Release' call
     */
    if (request != NULL)
        Message_Release(request);

    if (loadRequest != NULL)
        Message_Release(loadRequest);

    LOGD2((ZT("Context_Destroy - OK exit")))
    return;
}
