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

#include "provmgr.h"
#include "context.h"
#include <base/log.h>
#include <base/strings.h>
#include <base/atomic.h>
#include <base/paths.h>
#include <base/time.h>
#include <wql/wql.h>
#include <io/io.h>

#if defined(CONFIG_POSIX)
# include <unistd.h>
#endif

// #define ENABLE_TRACING
// #define TRACING_LEVEL 4
#include <logging.h>

/* ATTN: libraryName is key (switch to module name) */
/* ATTN: implement module provider Unload() methods */
/* ATTN: implement propertySet */

/* Suppress cast error from 'void*' to 'MI_Main' */
#if defined(_MSC_VER)
# pragma warning(disable : 4055)
#endif

/*
**=============================================================================
**
** Local defintions
**
**=============================================================================
*/

extern MI_ContextFT __mi_contextFT;

static MI_Result MI_CALL _Server_GetVersion(MI_Uint32* version)
{
    if (!version)
        return MI_RESULT_INVALID_PARAMETER;

    *version = MI_VERSION;
    return MI_RESULT_OK;
}

static MI_Result MI_CALL _Server_GetSystemName(const ZChar** systemName)
{
#if defined(CONFIG_OS_WINDOWS)
    *systemName = MI_T("unknown");
    return MI_RESULT_OK;
#else
    static char buf[256];

    if (buf[0] == '\0')
    {
        if (gethostname(buf, sizeof(buf)) != 0)
            return MI_RESULT_FAILED;
    }

#if (MI_CHAR_TYPE == 1)
    *systemName = buf;
#else
    {
        static ZChar wbuf[sizeof(buf)];
        ZStrlcpy(wbuf, buf, MI_COUNT(wbuf));
        *systemName = wbuf;
    }
#endif

    return MI_RESULT_OK;
#endif
}

#if 0
static MI_ServerFT _serverFT =
{
    _Server_GetVersion,
    _Server_GetSystemName,
};
#endif

typedef struct InternalFT
{
    ProvMgrFT provMgrFT;
    MI_ServerFT serverFT;
}
InternalFT;

/* warning C4054: 'type cast': from function pointer to void* */
#if defined(_MSC_VER)
# pragma warning(disable : 4054)
#endif

static void* _FindSymbol(const char* name)
{
    if (strcmp(name, "GetPath") == 0)
        return (void*)&GetPath;

    /* Not found */
    return NULL;
}

static InternalFT _internalFT =
{
    { PROVMGRFT_MAGIC, _FindSymbol },
    {
        _Server_GetVersion,
        _Server_GetSystemName
    },
};

static MI_Server _server =
{
    &_internalFT.serverFT,
    &__mi_contextFT,
    &__mi_instanceFT,
    NULL, /* MI_PropertySetFT */
    NULL, /* MI_FilterFT */
};

typedef struct _Library Library;

struct _Provider
{
    struct _Provider* next;
    struct _Provider* prev;

    const MI_ClassDecl* classDecl;
    void* self;

    /* number of outstanding requests */
    AtomicInt refCounter;

    /* time when last outstanding request was handled */
    MI_Uint64 idleSince;

    /* indicator if Provider refused idle-unload */
    MI_Boolean refusedUnload;

    /* pointer to lib object */
    Library* lib;

    /* indications support */
    Context ctxIndications;

};

struct _Library
{
    struct _Library* next;
    struct _Library* prev;
    char libraryName[MAX_PATH_SIZE];
    void* handle;
    const MI_Module* module;
    MI_Module_Self* self;
    struct _Provider* head;
    struct _Provider* tail;
    ProvMgr* provmgr;
};

static Library* MI_CALL _OpenLibrary(
    ProvMgr* self,
    const char* libraryName)
{
    Library* p;

    LOGD2((ZT("_OpenLibrary - Opening library: %s"), libraryName));

    /* Search cache first */
    for (p = self->head; p; p = p->next)
    {
        if (strcmp(p->libraryName, libraryName) == 0)
        {
            LOGD2((ZT("_OpenLibrary - Found library in cache")));
            return p;
        }
    }

    /* Allocate new library object */
    p = (Library*)calloc(1, sizeof(Library));

    if (p == NULL)
    {
        LOGE2((ZT("_OpenLibrary - Out of memory")));
        return NULL;
    }

    /* Library.refs */
    p->provmgr = self;

    /* Open the library */
    {
        char path[MAX_PATH_SIZE];
        Lib_Format(path, self->providerDir, libraryName);
        p->handle = Lib_Open(path);

        if (p->handle == NULL)
        {
            LOGW((ZT("cannot open shared library: {%s}: %s"), scs(libraryName), scs(Lib_Err())));

            /* Try again */

            p->handle = Lib_Open(libraryName);

            if (p->handle == NULL)
            {
                LOGE2((ZT("_OpenLibrary - Cannot open shared library: %s. Error: %s"), path, Lib_Err()));
                LOGW((ZT("cannot open shared library: {%s}: %s"), scs(libraryName), scs(Lib_Err())));
                free(p);
                return NULL;
            }
        }
    }

    /* Lib_Open.libraryName */
    Strlcpy(p->libraryName, libraryName, sizeof(p->libraryName));

    /* Invoke MI_Main() entry point */
    {
        MI_MainFunction staticMain;

        /* Lookup symbol */
        {
            void* ptr = Lib_Sym(p->handle, "MI_Main");

            staticMain = (MI_MainFunction)ptr;

            if (staticMain == NULL)
            {
                free(p);
                LOGE2((ZT("_OpenLibrary - Cannot find MI_Main in shared library: %s"), libraryName));
                LOGW((ZT("cannot find symbol in shared library: %s: %s"), scs(libraryName), scs("MI_Main")));
                return NULL;
            }
        }

        /* Call MI_Main */
        {
            p->module = (*staticMain)(&_server);
        }
    }

    /* Invoke the module initialize function */
    if (p->module->Load != NULL)
    {
        Context ctx;
        MI_Result r = MI_RESULT_OK;

        Context_Init(&ctx, NULL);
        ctx.result = &r;

        (*p->module->Load)(&p->self, (MI_Context*)&ctx);

        if (ctx.magic != CONTEXT_POSTED_MAGIC)
        {
            LOGW2((ZT("_OpenLibrary - Module load failed to call post result")));
            LOGW((ZT("module load failed to call post result")));
        }

        Context_Destroy(&ctx);

        if (MI_RESULT_OK != r)
        {
            LOGW((ZT("_OpenLibrary - Module load with result: %d, library: %s"), (int)r, libraryName));
            LOGE2((ZT("_OpenLibrary - Module load failed with error: %d (%s), library: %s"), (int)r, mistrerror(r), libraryName));
            return NULL;
        }
    }

    /* Add library to the list */
    List_Prepend((ListElem**)&self->head, (ListElem**)&self->tail, (ListElem*)p);

    LOGD2((ZT("_OpenLibrary - OK exit")));

    return p;
}

static Provider* MI_CALL _OpenProvider(
    Library* self,
    const ZChar* className,
    Message* request)
{
    Provider* p;

    LOGD2((ZT("_OpenProvider - class name: %s"), className));

    /* Search cache first */
    for (p = self->head; p != NULL; p = p->next)
    {
        if (Zcasecmp(p->classDecl->name, className) == 0)
        {
            AtomicInc(&p->refCounter);
            LOGD2((ZT("_OpenProvider - Class %s found in cache."), className));
            return p;
        }
    }

    /* New Provider */
    p = (Provider*)calloc(1, sizeof(Provider));

    if (p == NULL)
    {
        LOGE2((ZT("_OpenProvider - Out of memory")));
        return NULL;
    }

    /* Provider.refs */
    p->refCounter = 1;
    p->lib = self;

    /* Provider.classDecl */
    {
        p->classDecl = SchemaDecl_FindClassDecl(self->module->schemaDecl, className);

        if (p->classDecl == NULL || p->classDecl->providerFT == NULL)
        {
            LOGE2((ZT("_OpenProvider - Could not find class %s"), className));
            free(p);
            return NULL;
        }
    }

    /* Initialize context - used for indication providers */
    Context_Init(&p->ctxIndications, NULL);
    p->ctxIndications.chainType = CTX_TYPE_IND_NOTINITIALIZED;

    /* Call provider Load() method */
    if (p->classDecl->providerFT->Load != NULL)
    {
        Context ctx;
        MI_Result r = MI_RESULT_OK;

        Context_Init(&ctx, p);
        ctx.result = &r;
        ctx.loadRequest = request;
        Message_AddRef(ctx.loadRequest);

        (*p->classDecl->providerFT->Load)(&p->self, self->self, &ctx.base);

        if (ctx.magic != CONTEXT_POSTED_MAGIC)
        {
            LOGW((ZT("_OpenProvider - Provider load did not call post result")));
            LOGW2((ZT("_OpenProvider - Provider load did not call post result")));
        }

        Context_Destroy(&ctx);

        if (MI_RESULT_OK != r)
        {
            LOGW((ZT("_OpenProvider - Failed on call to provider's load with result %d; class: %Z"), (int)r, zcs(className)));
            LOGE2((ZT("_OpenProvider - Failed on call to provider's load. error: %d (%s); class: %s"), (int)r, mistrerror(r), className));
            Context_Destroy(&p->ctxIndications);
            free(p);
            return NULL;
        }
    }

    /* Prepend to list */
    List_Prepend(
        (ListElem**)&self->head,
        (ListElem**)&self->tail,
        (ListElem*)p);

    LOGD2((ZT("_OpenProvider - OK exit")));

    return p;
}

static MI_Result MI_CALL _GetProviderByClassName(
    ProvMgr* self,
    const char* libraryName,
    MI_ConstString cn,
    Message* request,
    Provider** provOut)
{
    Library* lib;
    Provider* prov;

    LOGD((ZT("_GetProviderByClassName{%Z}"), zcs(cn)));
    LOGD2((ZT("_GetProviderByClassName - Begin. library: %s, class: %s"), libraryName, cn));

    /* Open the library */
    {
        lib = _OpenLibrary(self, libraryName);

        if (lib == NULL)
        {
            LOGW((ZT("_GetProviderByClassName - failed to open provider library: %s"), scs(libraryName)));
            LOGE2((ZT("_GetProviderByClassName - Failed to open provider library: %s"), libraryName));
            return MI_RESULT_FAILED;
        }
    }

    /* Open the provider */
    {
        prov = _OpenProvider(lib, cn, request);

        if (prov == NULL)
        {
            LOGW((ZT("_GetProviderByClassName - Failed to open the provider %s for class %Z"), libraryName, zcs(cn)));
            LOGE2((ZT("_GetProviderByClassName - Failed to open provider. library: %s, class name: %s"), libraryName, cn));
            return MI_RESULT_FAILED;
        }
    }

    *provOut = prov;

    LOGD2((ZT("_GetProviderByClassName - OK exit")));

    return MI_RESULT_OK;
}

static  MI_Result _Instance_InitConvert_FromBatch(
    Batch* batch,
    const MI_ClassDecl* cd,
    const MI_SchemaDecl* sd,
    MI_Instance* inst_in,
    MI_Boolean keys_only,
    MI_Boolean allow_keyless_inst,
    MI_Instance** instOut
    )
{
    MI_Instance* inst;
    MI_Result r;
    MI_UNUSED(sd);

    /* Allocate the instance for the provider */
    inst = (MI_Instance*)Batch_GetClear(batch, cd->size);

    if (inst == NULL)
    {
        LOGF((ZT("allocation failed")));
        return MI_RESULT_FAILED;
    }

    /* Convert instance name to provider's format (borrow storage) */
    r = Instance_InitConvert(inst, cd, inst_in, keys_only, allow_keyless_inst, MI_FALSE,
        batch);

    if (r != MI_RESULT_OK)
    {
        LOGW((ZT("instance conversion failed: %Z, err %d"), zcs(cd->name), r));
        return r;
    }

    *instOut = inst;
    return MI_RESULT_OK;
}

static MI_Result _HandleGetInstanceReq(
    ProvMgr* self,
    const char* libraryName,
    GetInstanceReq* msg,
    Provider** prov)
{
    MI_Instance* inst;
    MI_Result r;
    const ZChar* className;

    /* Get classname from instance */
    r = __MI_Instance_GetClassName(msg->instanceName, &className);

    if (r != MI_RESULT_OK)
        return r;

    /* find provider */
    r = _GetProviderByClassName(
        self,
        libraryName,
        className,
        &msg->base,
        prov);

    if (MI_RESULT_OK != r)
        return r;

    /* Allocate the instance for the provider */
    r = _Instance_InitConvert_FromBatch(
        msg->base.batch,
        (*prov)->classDecl,
        (*prov)->lib->module->schemaDecl,
        msg->instanceName,
        MI_TRUE,
        MI_FALSE,
        &inst);

    if (MI_RESULT_OK != r)
        return r;

#if 0
    /* Print instance */
    Instance_Print(inst, stdout, 0);
#endif

    /* If provider's GetInstance method null, use EnumerateInstances */
    if ((*prov)->classDecl->providerFT->GetInstance == NULL)
    {
        Context* ctx;

        if ((*prov)->classDecl->providerFT->EnumerateInstances == NULL)
            return MI_RESULT_INVALID_CLASS;

        /* Create context */
        ctx = (Context*)Batch_GetClear(msg->base.batch, sizeof(Context));;
        Context_Init(ctx, *prov);
        ctx->request = &msg->base;

        /* _PostInstance() filters by this if not null */
        ctx->instanceName = inst;

        /* message will be freed in context release*/
        Message_AddRef(&msg->base);

        /* Invoke provider */
        (*(*prov)->classDecl->providerFT->EnumerateInstances)(
            (*prov)->self,
            &ctx->base,
            msg->nameSpace,
            className,
            NULL, /* propertSet */
            MI_FALSE, /* keysOnly */
            NULL); /* filter */

        Context_Destroy(ctx);
    }
    else
    {
        Context* ctx;

        /* Create context */
        ctx = (Context*)Batch_GetClear(msg->base.batch, sizeof(Context));;
        Context_Init(ctx, *prov);
        ctx->request = &msg->base;

        /* message will be freed in context release*/
        Message_AddRef(&msg->base);

        /* Invoke provider */
        (*(*prov)->classDecl->providerFT->GetInstance)(
            (*prov)->self,
            &ctx->base,
            msg->nameSpace,
            className,
            inst,
            NULL);

        Context_Destroy(ctx);
    }

    return MI_RESULT_OK;
}

static MI_Result _HandleCreateInstanceReq(
    ProvMgr* self,
    const char* libraryName,
    CreateInstanceReq* msg,
    Provider** prov)
{
    MI_Instance* inst;
    MI_Result r;
    const ZChar* className;

    /* Get classname from instance */
    r = __MI_Instance_GetClassName(msg->instance, &className);

    if (r != MI_RESULT_OK)
        return r;

    /* find provider */
    r = _GetProviderByClassName(
        self,
        libraryName,
        className,
        &msg->base,
        prov);

    if (MI_RESULT_OK != r)
        return r;

    /* Allocate the instance for the provider */
    r = _Instance_InitConvert_FromBatch(
        msg->base.batch,
        (*prov)->classDecl,
        (*prov)->lib->module->schemaDecl,
        msg->instance,
        MI_FALSE,
        MI_TRUE,
        &inst);

    if (MI_RESULT_OK != r)
        return r;

    /* Invoke provider */
    if (!(*prov)->classDecl->providerFT->CreateInstance)
        return MI_RESULT_INVALID_CLASS;

    {
        Context* ctx = (Context*)Batch_GetClear(msg->base.batch, sizeof(Context));;

        Context_Init(ctx, *prov);
        ctx->request = &msg->base;
        /* message will be freed in ContextDestroy */
        Message_AddRef(&msg->base);
        (*(*prov)->classDecl->providerFT->CreateInstance)((*prov)->self, &ctx->base,
            msg->nameSpace, className, inst);

        Context_Destroy(ctx);
    }

    return MI_RESULT_OK;
}

static MI_Result _HandleModifyInstanceReq(
    ProvMgr* self,
    const char* libraryName,
    ModifyInstanceReq* msg,
    Provider** prov)
{
    MI_Instance* inst;
    MI_Result r;
    const ZChar* className;

    /* Get classname from instance */
    r = __MI_Instance_GetClassName(msg->instance, &className);

    if (r != MI_RESULT_OK)
        return r;

    /* find provider */
    r = _GetProviderByClassName(
        self,
        libraryName,
        className,
        &msg->base,
        prov);

    if (MI_RESULT_OK != r)
        return r;

    /* Allocate the instance for the provider */
    r = _Instance_InitConvert_FromBatch(
        msg->base.batch,
        (*prov)->classDecl,
        (*prov)->lib->module->schemaDecl,
        msg->instance,
        MI_FALSE,
        MI_FALSE,
        &inst);

    if (MI_RESULT_OK != r)
        return r;

    /* Invoke provider */
    if (!(*prov)->classDecl->providerFT->ModifyInstance)
        return MI_RESULT_INVALID_CLASS;

    {
        Context* ctx = (Context*)Batch_GetClear(msg->base.batch, sizeof(Context));;
        Context_Init(ctx, *prov);
        ctx->request = &msg->base;
        /* message will be freed in ContextDestory */
        Message_AddRef(&msg->base);
        (*(*prov)->classDecl->providerFT->ModifyInstance)((*prov)->self, &ctx->base,
            msg->nameSpace, className, inst, NULL);

        Context_Destroy(ctx);
    }

    return MI_RESULT_OK;
}

static MI_Result _HandleDeleteInstanceReq(
    ProvMgr* self,
    const char* libraryName,
    DeleteInstanceReq* msg,
    Provider** prov)
{
    MI_Instance* inst;
    MI_Result r;
    const ZChar* className;

    /* Get classname from instance */
    r = __MI_Instance_GetClassName(msg->instanceName, &className);

    if (r != MI_RESULT_OK)
        return r;

    /* find provider */
    r = _GetProviderByClassName(
        self,
        libraryName,
        className,
        &msg->base,
        prov);

    if (MI_RESULT_OK != r)
        return r;

    /* Allocate the instance for the provider */
    r = _Instance_InitConvert_FromBatch(
        msg->base.batch,
        (*prov)->classDecl,
        (*prov)->lib->module->schemaDecl,
        msg->instanceName,
        MI_TRUE,
        MI_FALSE,
        &inst);

    if (MI_RESULT_OK != r)
        return r;

    /* Invoke provider */
    if (!(*prov)->classDecl->providerFT->DeleteInstance)
        return MI_RESULT_INVALID_CLASS;

    {
        Context* ctx = (Context*)Batch_GetClear(msg->base.batch,
            sizeof(Context));;
        Context_Init(ctx, *prov);
        ctx->request = &msg->base;

        /* message will be freed in ContextDestroy */
        Message_AddRef(&msg->base);
        (*(*prov)->classDecl->providerFT->DeleteInstance)((*prov)->self, &ctx->base,
            msg->nameSpace, className, inst);

        Context_Destroy(ctx);
    }

    return MI_RESULT_OK;
}

static MI_Result _HandleSubscribeReq(
    ProvMgr* self,
    const char* libraryName,
    SubscribeReq* msg,
    Provider** prov)
{
    MI_Result r;

    /* find provider */
    r = _GetProviderByClassName(
        self,
        libraryName,
        msg->className,
        &msg->base,
        prov);

    if (MI_RESULT_OK != r)
        return r;

    /* Invoke provider */
    if (!(*prov)->classDecl->providerFT->EnableIndications || !(*prov)->classDecl->providerFT->Subscribe)
        return MI_RESULT_INVALID_CLASS;

    if ((*prov)->ctxIndications.chainType == CTX_TYPE_IND_NOTINITIALIZED)
    {
        /* have to initialize provider first */
        (*prov)->ctxIndications.chainType = CTX_TYPE_IND_READY;

        (*prov)->classDecl->providerFT->EnableIndications((*prov)->self,
            &(*prov)->ctxIndications.base, msg->nameSpace, msg->className);
    }

    if ((*prov)->ctxIndications.chainType == CTX_TYPE_IND_READY)
    {
        /* provider is ready for subscriptions */
        Context* ctx = (Context*)Batch_GetClear(msg->base.batch, sizeof(Context));
        Context_Init(ctx, *prov);
        ctx->request = &msg->base;

        /* message will be freed in ContextDestroy */
        Message_AddRef(&msg->base);
        (*(*prov)->classDecl->providerFT->Subscribe)((*prov)->self, &ctx->base,
            msg->nameSpace, msg->className, 0, __bookmark, msg->subscriptionID,
            __subscriptionSelfPtr);
        Context_Destroy(ctx);
    }
    else
        return MI_RESULT_FAILED;    /* unexpected state */

    return MI_RESULT_OK;
}

static MI_Result _HandleInvokeReq(
    ProvMgr* self,
    const char* libraryName,
    InvokeReq* msg,
    Provider** prov)
{
    MI_Instance* inst = NULL;
    MI_Instance* instParams = NULL;
    MI_Result r;
    MI_ConstString cn = NULL;
    MI_MethodDecl* md = NULL;

#if 0
    MessagePrint(&msg->base, stdout);
#endif

    /* parameter validation */
    if (msg == NULL || msg->function == NULL)
        return MI_RESULT_INVALID_PARAMETER;

    if (msg->className)
        cn = msg->className;
    else if (msg->instance)
        cn = ((Instance*) msg->instance)->classDecl->name;

    if (!cn)
        return MI_RESULT_INVALID_CLASS;

    /* find provider */
    r = _GetProviderByClassName(
        self,
        libraryName,
        cn,
        &msg->base,
        prov);

    if (MI_RESULT_OK != r)
        return r;

    /* find method declaration */
    md = SchemaDecl_FindMethodDecl((*prov)->classDecl, msg->function);
    if (md == NULL)
        return MI_RESULT_FAILED;

    /* if method is not static, instance must be provided */
    if (msg->instance == NULL && (md->flags & MI_FLAG_STATIC) != MI_FLAG_STATIC)
        return MI_RESULT_INVALID_PARAMETER;

    if (msg->instance)
    {
        r = _Instance_InitConvert_FromBatch(
            msg->base.batch,
            (*prov)->classDecl,
            (*prov)->lib->module->schemaDecl,
            msg->instance,
            MI_TRUE,
            MI_FALSE,
            &inst);

        if (MI_RESULT_OK != r)
            return r;
    }

    if (msg->instanceParams != NULL)
    {
        /* paramerters (if any) */
        r = _Instance_InitConvert_FromBatch(
            msg->base.batch,
            (const MI_ClassDecl*)md,
            (*prov)->lib->module->schemaDecl,
            msg->instanceParams,
            MI_FALSE,
            MI_TRUE,
            &instParams);

        if (MI_RESULT_OK != r)
            return r;
    }

#if 0
    /* Print instance */
    Instance_Print(inst, stdout, 0);
#endif

    /* Invoke provider */
    if (md->function == NULL)
        return MI_RESULT_INVALID_CLASS;

    {
        Context* ctx = (Context*)Batch_GetClear(msg->base.batch, sizeof(Context));;

        Context_Init(ctx, (*prov));
        ctx->request = &msg->base;
        /* message will be freed in context release*/
        Message_AddRef(&msg->base);

        /* call get first if fn is non-static */
        /*if (inst != NULL && (*prov)->classDecl->providerFT->GetInstance != NULL)
        {
            ctx->chainType = CTX_TYPE_INVOKE_WITH_INSTANCE;
            ctx->inst = inst;
            ctx->instParams = instParams;
            ctx->md = md;
            ctx->prov_self = (*prov)->self;

            (*(*prov)->classDecl->providerFT->GetInstance)((*prov)->self, &ctx->base,
                __nameSpace, __className, inst, NULL);
        }
        else */   /* for static - call invoke directly */
        {
            (*md->function)((*prov)->self, &ctx->base, msg->nameSpace, cn, msg->function, inst, instParams);
        }

        Context_Destroy(ctx);
    }

    return MI_RESULT_OK;
}

static MI_Result _HandleEnumerateInstancesReq(
    ProvMgr* self,
    const char* libraryName,
    EnumerateInstancesReq* msg,
    Provider** prov)
{
    Context* ctx = NULL;
    MI_Result r;

    LOGD2((ZT("_HandleEnumerateInstancesReq - Library name: %s"), libraryName));

#if 0
    MessagePrint(&msg->base, stdout);
#endif

    /* find provider */
    r = _GetProviderByClassName(
        self,
        libraryName,
        msg->className,
        &msg->base,
        prov);

    if (MI_RESULT_OK != r)
    {
        LOGE2((ZT("_HandleEnumerateInstancesReq - _GetProviderByClassName for class %s failed with error: %d (%s)"), msg->className, r, mistrerror(r)));
        return r;
    }

    /* Get WQL query, if any */
    msg->wql = NULL;
    if (msg->queryLanguage != NULL && strcmp(msg->queryLanguage, "WQL") == 0 && msg->queryExpression != NULL)
    {
        msg->wql = WQL_Parse(msg->queryExpression, NULL);
        if (msg->wql == NULL)
        {
            LOGE2((ZT("_HandleEnumerateInstancesReq - Invalid WQL query: %s"), msg->queryExpression == NULL ? "null" : msg->queryExpression));
            return MI_RESULT_INVALID_QUERY;
        }
    }

    /* Validate WQL query (if any) against provider's class declaration */
    if (msg->wql != NULL)
    {
        if (WQL_Validate(msg->wql, (*prov)->classDecl) != 0)
        {
            LOGE2((ZT("_HandleEnumerateInstancesReq - Invalid WQL query: %s"), msg->queryExpression == NULL ? "null" : msg->queryExpression));
            LOGW((ZT("query validation failed: %Z"), zcs(msg->wql->text)));
            WQL_Delete(msg->wql);
            msg->wql = NULL;
            return MI_RESULT_INVALID_QUERY;
        }
    }

    /* Invoke provider */
    if (!(*prov)->classDecl->providerFT->EnumerateInstances)
    {
        LOGW2((ZT("_HandleEnumerateInstancesReq - Provider does not support EnumerateInstances request")));
        if (msg->wql != NULL)
        {
            WQL_Delete(msg->wql);
            msg->wql = NULL;
        }
        return MI_RESULT_NOT_SUPPORTED;
    }

    /* Create the context object */
    {
        ctx = (Context*)Batch_GetClear(msg->base.batch, sizeof(Context));;

        if (ctx == NULL)
        {
            LOGF((ZT("allocation failed")));
            LOGE2((ZT("_HandleEnumerateInstancesReq - Out of memory")));
            if (msg->wql != NULL)
            {
                WQL_Delete(msg->wql);
                msg->wql = NULL;
            }
            return MI_RESULT_FAILED;
        }

        Context_Init(ctx, *prov);
        ctx->request = &msg->base;
    }

    LOGD((ZT("enumerate instances of %Z"), zcs(msg->className)));
    LOGD2((ZT("_HandleEnumerateInstancesReq - Enumerating instances of %s"), msg->className));

    /* message will be freed in context release */
    Message_AddRef(&msg->base);
    (*(*prov)->classDecl->providerFT->EnumerateInstances)(
        (*prov)->self, &ctx->base,
        msg->nameSpace, msg->className, NULL, MI_FALSE, NULL);

    if (msg->wql != NULL)
    {
        WQL_Delete(msg->wql);
        msg->wql = NULL;
    }
    if (ctx != NULL)
    {
        Context_Destroy(ctx);
    }

    LOGD2((ZT("_HandleEnumerateInstancesReq - OK exit")));

    return MI_RESULT_OK;
}

static MI_Result MI_CALL _HandleAssociatorsOfReq(
    ProvMgr* self,
    const char* libraryName,
    AssociationsOfReq* msg,
    Provider** prov)
{
    Context* ctx;
    MI_Result r;
    MI_Instance* inst = 0;

    /* find provider */
    r = _GetProviderByClassName(
        self,
        libraryName,
        msg->className,
        &msg->base,
        prov);

    if (MI_RESULT_OK != r)
        return r;

    /* Invoke provider */
    if (!(*prov)->classDecl->providerFT->AssociatorInstances)
        return MI_RESULT_NOT_SUPPORTED;

    if (!msg->instance)
        return MI_RESULT_INVALID_PARAMETER;

    {
        Provider* provInst = 0;

        r = _GetProviderByClassName(
            self,
            libraryName,
            ((Instance*) msg->instance)->classDecl->name,
            &msg->base,
            &provInst);

        if (MI_RESULT_OK != r)
            return r;

        r = _Instance_InitConvert_FromBatch(
            msg->base.batch,
            provInst->classDecl,
            (*prov)->lib->module->schemaDecl,
            msg->instance,
            MI_TRUE,
            MI_FALSE,
            &inst);

        Provider_Release(provInst);

        if (MI_RESULT_OK != r)
            return r;
    }

    ctx = (Context*)Batch_GetClear(msg->base.batch, sizeof(Context));;

    if (ctx == NULL)
    {
        LOGF((ZT("allocation failed")));
        return MI_RESULT_FAILED;
    }

    Context_Init(ctx, (*prov));
    ctx->request = &msg->base;

    /* message will be freed in context release */
    Message_AddRef(&msg->base);
    (*(*prov)->classDecl->providerFT->AssociatorInstances)(
        (*prov)->self,
        &ctx->base,
        msg->nameSpace,
        msg->className,
        inst,
        msg->resultClass,
        msg->role,
        msg->resultRole,
        NULL, MI_FALSE, NULL);

    Context_Destroy(ctx);

    return MI_RESULT_OK;
}

static MI_Result _HandleReferencesOfReq(
    ProvMgr* self,
    const char* libraryName,
    AssociationsOfReq* msg,
    Provider** prov)
{
    Context* ctx;
    MI_Result r;
    MI_Instance* inst = NULL;

    /* find provider */
    r = _GetProviderByClassName(
        self,
        libraryName,
        msg->className,
        &msg->base,
        prov);

    if (MI_RESULT_OK != r)
        return r;

    /* Invoke provider */
    if (!(*prov)->classDecl->providerFT->ReferenceInstances)
        return MI_RESULT_NOT_SUPPORTED;

    if (!msg->instance)
        return MI_RESULT_INVALID_PARAMETER;

    {
        Provider* provInst = 0;

        r = _GetProviderByClassName(
            self,
            libraryName,
            ((Instance*) msg->instance)->classDecl->name,
            &msg->base,
            &provInst);

        if (MI_RESULT_OK != r)
            return r;

        r = _Instance_InitConvert_FromBatch(
            msg->base.batch,
            provInst->classDecl,
            (*prov)->lib->module->schemaDecl,
            msg->instance,
            MI_TRUE,
            MI_FALSE,
            &inst);

        Provider_Release(provInst);

        if (MI_RESULT_OK != r)
            return r;
    }

    ctx = (Context*)Batch_GetClear(msg->base.batch, sizeof(Context));;

    if (ctx == NULL)
    {
        LOGF((ZT("allocation failed")));
        return MI_RESULT_FAILED;
    }

    Context_Init(ctx, *prov);
    ctx->request = &msg->base;

    /* message will be freed in context release */
    Message_AddRef(&msg->base);
    (*(*prov)->classDecl->providerFT->ReferenceInstances)(
        (*prov)->self,
        &ctx->base,
        msg->nameSpace,
        msg->className,
        inst,
        msg->role,
        NULL, MI_FALSE, NULL);

    Context_Destroy(ctx);

    return MI_RESULT_OK;
}

static void _UnloadAllProviders(
    ProvMgr* self,
    Library* lib,
    MI_Boolean idleOnly,
    MI_Uint64 currentTimeUsec,
    MI_Uint64* nextFireAtTime)
{
    Provider* p;
    Provider *p_next;

    for (p = lib->head; p != NULL; )
    {
        MI_Uint64 provFireAtTime = p->idleSince + self->idleTimeoutUsec;

        p_next = p->next;

        /* unload if 'force' option passed or provider is idle long enough */
        if (!idleOnly ||
            (!p->refusedUnload && 0 == p->refCounter && provFireAtTime <= currentTimeUsec))
        {
            LOGD((ZT("Unloading provider %Z"), zcs(p->classDecl->name)));

            /* Call provider unload() method */
            if (p->classDecl->providerFT->Unload != NULL)
            {
                Context ctx;

                Context_Init(&ctx, NULL);
                (*p->classDecl->providerFT->Unload)(p->self, &ctx.base);

                Context_Destroy(&ctx);
            }

            Context_Destroy(&p->ctxIndications);

            if (p->refCounter != 0)
            {
                /* Error condition - unloading active provider! */
                LOGE((ZT("Unloading active provider %Z, with ref counter %d"),
                    zcs(p->classDecl->name), (int)p->refCounter));
                LOGE((ZT("Unloading active provider for lib %s, ref counter %d"),
                    scs(lib->libraryName), (int)p->refCounter));

                // ATTN: _exit is a good option here, since provider's behavior maybe undefined
                _exit(1);
            }

            List_Remove(
                (ListElem**)&lib->head,
                (ListElem**)&lib->tail,
                (ListElem*)p);

            free(p);
        }
        else if (idleOnly && 0 == p->refCounter && nextFireAtTime)
        {
            /* re-calculate idle timeout */

            if (provFireAtTime < *nextFireAtTime)
            {
                *nextFireAtTime = provFireAtTime;
            }
        }

        /* move to next one */
        p = p_next;
    }
}

static void _UnloadAllLibraries(
    ProvMgr* self,
    MI_Boolean idleOnly,
    MI_Uint64 currentTimeUsec,
    MI_Uint64* nextFireAtTime)
{
    Library* p, *p_next;

    /* release all (or idle-only) opened libraries */
    for (p = self->head; p != NULL; )
    {
        p_next = p->next;

        _UnloadAllProviders(self,p,idleOnly,currentTimeUsec,nextFireAtTime);

        /* Unload libraries that have no loaded providers */
        if (p->head == NULL)
        {
            /* Invoke the module un-initialize function */
            if (p->module->Unload != NULL)
            {
                Context ctx;
                MI_Result r = MI_RESULT_OK;

                Context_Init(&ctx, NULL);
                ctx.result = &r;

                (*p->module->Unload)(p->self, (MI_Context*)&ctx);

                if (ctx.magic != CONTEXT_POSTED_MAGIC)
                {
                    LOGW((ZT("_UnloadAllLibraries - Unload did not call post result")));
                }

                Context_Destroy(&ctx);

                if (MI_RESULT_OK != r)
                {
                    LOGW((ZT("_UnloadAllLibraries - Failed to call library unload: %u:%s"), r, scs(p->libraryName)));
                }
            }

            Lib_Close(p->handle);
            LOGD((ZT("_UnloadAllLibraries - Unloading lib %s"), scs(p->libraryName)));

            List_Remove(
                (ListElem**)&self->head,
                (ListElem**)&self->tail,
                (ListElem*)p);

            free(p);
        }

        p = p_next;
    }
}

/*
    Timeout handler: unloads idle providers and libraris,
    re-calculates new timeout (for next provider),
    notifies server/agent if all libraries are unloaded
*/
static MI_Boolean _TimeoutCallback(
    Selector* sel,
    Handler* handler,
    MI_Uint32 mask,
    MI_Uint64 currentTimeUsec)
{
    MI_UNUSED(sel);

    if ((mask & SELECTOR_TIMEOUT) != 0)
    {
        ProvMgr* self = (ProvMgr*)handler->data;
        const MI_Uint64 u64max = ~MI_ULL(0);
        MI_Uint64 nextFireAtTime = u64max;

        /* Unload all idle providers */
        //LOGI((ZT("Unloading idle providers")));

        _UnloadAllLibraries(self, MI_TRUE, currentTimeUsec, &nextFireAtTime);
        if (u64max != nextFireAtTime)
        {
            /* re-set timeout */
            handler->fireTimeoutAt = nextFireAtTime;
        }
        else
        {
            /* disable timeout, since no more idle providers */
            handler->fireTimeoutAt = TIME_NEVER;
        }

        /* If all libraries are gone, notify caller */
        if (self->head == NULL && self->idleCallback != NULL)
        {
            (*self->idleCallback)(self, self->idleCallbackData);
        }

        return MI_TRUE;
    }

    if ((mask & (SELECTOR_REMOVE | SELECTOR_DESTROY)) != 0)
    {
        /* ignore it */
    }

    return MI_TRUE;
}

/*
**=============================================================================
**
** Public defintions
**
**=============================================================================
*/

MI_Result ProvMgr_Init(
    ProvMgr* self,
    Selector* selector,
    ProvMgrCallbackOnIdle idleCallback,
    void* idleCallbackData,
    const char* providerDir)
{
    LOGD2((ZT("ProvMgr_Init - Begin")));

    if (self == NULL || providerDir == NULL)
        return MI_RESULT_INVALID_PARAMETER;

    memset(self, 0, sizeof(ProvMgr));

    Strlcpy(self->providerDir, providerDir, sizeof(self->providerDir)-1);

    self->idleTimeoutUsec = MI_ULL(90) * MI_ULL(1000000);

    /* Add socket handler to catch timeout event */

    self->timeoutHandler.sock = INVALID_SOCK;
    self->timeoutHandler.data = self;
    self->timeoutHandler.callback = _TimeoutCallback;
    self->idleCallback = idleCallback;
    self->idleCallbackData = idleCallbackData;
    self->selector = selector;

    Selector_AddHandler(selector, &self->timeoutHandler);

    LOGD2((ZT("ProvMgr_Init - OK exit")));
    return MI_RESULT_OK;
}

MI_Result ProvMgr_Destroy(
    ProvMgr* self)
{
    if (self == NULL)
        return MI_RESULT_INVALID_PARAMETER;

    /* release opened libraries */
    _UnloadAllLibraries(self, MI_FALSE, 0, NULL);

    memset(self, 0xFF, sizeof(ProvMgr));

    return MI_RESULT_OK;
}

/*
    Routes incoming message to appropriate
    message handler based on message tag
*/
MI_Result MI_CALL ProvMgr_PostMessage(
    ProvMgr* self,
    const char* libraryName,
    Message* msg)
{
    Provider* prov = NULL;
    MI_Result r = MI_RESULT_INVALID_PARAMETER;

    LOGD2((ZT("ProvMgr_PostMessage - Begin. message: %d (%s)"), msg->tag, messagetagnamestr(msg->tag)));

    /* Check parameters */
    if (self == NULL || msg == NULL)
        return MI_RESULT_INVALID_PARAMETER;

    /* Dispatch the message */
    switch (msg->tag)
    {
        case GetInstanceReqTag:
        {
            r = _HandleGetInstanceReq(self, libraryName, (GetInstanceReq*)msg, &prov);
            break;
        }
        case CreateInstanceReqTag:
        {
            r = _HandleCreateInstanceReq(self, libraryName, (CreateInstanceReq*)msg, &prov);
            break;
        }
        case ModifyInstanceReqTag:
        {
            r = _HandleModifyInstanceReq(self, libraryName, (ModifyInstanceReq*)msg, &prov);
            break;
        }
        case DeleteInstanceReqTag:
        {
            r = _HandleDeleteInstanceReq(self, libraryName, (DeleteInstanceReq*)msg, &prov);
            break;
        }
        case InvokeReqTag:
        {
            r = _HandleInvokeReq(self, libraryName, (InvokeReq*)msg, &prov);
            break;
        }
        case EnumerateInstancesReqTag:
        {
            r = _HandleEnumerateInstancesReq(self, libraryName, (EnumerateInstancesReq*)msg, &prov);
            break;
        }
        case AssociatorsOfReqTag:
        {
            r = _HandleAssociatorsOfReq(self, libraryName, (AssociationsOfReq*)msg, &prov);
            break;
        }
        case ReferencesOfReqTag:
        {
            r = _HandleReferencesOfReq(self, libraryName, (AssociationsOfReq*)msg, &prov);
            break;
        }
        case SubscribeReqTag:
        {
            r = _HandleSubscribeReq(self, libraryName, (SubscribeReq*)msg, &prov);
            break;
        }

        default:
            break;
    }

    Provider_Release(prov);
    LOGD2((ZT("ProvMgr_PostMessage - End. returning: %d (%s)"), r, mistrerror(r)));
    return r;
}

/*
    Increments provider's ref-counter
*/
void Provider_Addref(Provider* provider)
{
    if (provider)
        AtomicInc(&provider->refCounter);
}

/*
    Decrements provider's ref-counter and
    marks provider as idle if ref-counter is 0 and
    'refuse-unload' was not called
*/
void Provider_Release(Provider* provider)
{
    if (provider != NULL && AtomicDec(&provider->refCounter))
    {
        if (!provider->refusedUnload)
        {
            /* Provider becomes idle */
            if (MI_RESULT_OK != Time_Now(&provider->idleSince))
                provider->idleSince = ~ (MI_Uint64)0;

            /* Set timer if it's first idle provider */
            if (TIME_NEVER == provider->lib->provmgr->timeoutHandler.fireTimeoutAt)
            {
                if (MI_RESULT_OK == Time_Now(&provider->lib->provmgr->timeoutHandler.fireTimeoutAt))
                {
                    provider->lib->provmgr->timeoutHandler.fireTimeoutAt += provider->lib->provmgr->idleTimeoutUsec;

                    //LOGD((ZT("Setting fire-at to ") UINT64_FMT_T, provider->lib->provmgr->timeoutHandler.fireTimeoutAt));

                    /* wakeup main thread */
                    Selector_Wakeup(provider->lib->provmgr->selector);
                }
            }
        }
    }
}

void Provider_SetRefuseUnloadFlag(Provider* provider, MI_Boolean flag)
{
    provider->refusedUnload = flag;
}

void Provider_NewInstanceCreated(
    Provider* provider,
    Message* msg)
{
    Selector_NewInstanceCreated(provider->lib->provmgr->selector, msg);
}
