/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "provmgr.h"
#include "context.h"
#include "AggregationContext.h"
#include "LifecycleContext.h"
#include "SubMgr.h"
#include "nioproc.h"
#include <base/log.h>
#include <pal/strings.h>
#include <pal/atomic.h>
#include <base/paths.h>
#include <pal/sleep.h>
#include <base/class.h>
#include <wql/wql.h>
#include <wsman/wsbuf.h>
#include <pal/format.h>
#include <indication/common/indilog.h>
#include <indication/common/indicommon.h>
#include <omi_error/errorutil.h>
#include <provreg/provreg.h>

#if defined(CONFIG_POSIX)
# include <unistd.h>
#endif

/* ATTN: libraryName is key (switch to module name) */
/* ATTN: implement module provider Unload() methods */
/* ATTN: implement propertySet */

/*
**=============================================================================
**
** Local definitions
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
        TcsStrlcpy(wbuf, buf, MI_COUNT(wbuf));
        *systemName = wbuf;
    }
#endif

    return MI_RESULT_OK;
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

static void* _FindSymbol(const char* name)
{
    if (strcmp(name, "OMI_GetPath") == 0)
        return (void*)&OMI_GetPath;

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

/*
 * Try to find specific library and open it if not found,
 * this function is not thread-safely operate the library list
 */
static Library* MI_CALL _OpenLibraryInternal(
    ProvMgr* self,
    _In_ const ProvRegEntry* proventry)
{
    Library* p;

    /* Search cache first */
    for (p = self->head; p; p = p->next)
    {
        if (strcmp(p->libraryName, proventry->libraryName) == 0)
        {
            return p;
        }
    }

    /* Allocate new library object */
    p = (Library*)PAL_Calloc(1, sizeof(Library));

    if (!p)
        return NULL;

    /* Library.refs */
    p->provmgr = self;
    /* Open the library */
    {
        TChar path[PAL_MAX_PATH_SIZE];
        path[0] = '\0';
        Shlib_Format(path, self->providerDir,
                     proventry->interpreter ? "OMIScriptProvider" :
                         proventry->libraryName);

        p->handle = Shlib_Open(path);

        if (!p->handle)
        {
            TChar Tpath[PAL_MAX_PATH_SIZE];

            if (TcsStrlcpy(Tpath, proventry->libraryName, PAL_MAX_PATH_SIZE) >=
                PAL_MAX_PATH_SIZE)
            {
                trace_SharedLib_CannotOpen(
                    scs(proventry->interpreter ? "OMIScriptProvider" :
                            proventry->libraryName));
                PAL_Free(p);
                return NULL;
            }

            trace_SharedLib_CannotOpenFirstTry(tcs(path), tcs(Shlib_Err()));

            // here we are ignoring error from Shlib_Open on first attempt
            NitsIgnoringError();

            /* Try again */

            p->handle = Shlib_Open(Tpath);

            if (!p->handle)
            {
                trace_SharedLib_CannotOpenSecondTry(
                    scs(proventry->libraryName), tcs(Shlib_Err()));
                PAL_Free(p);
                return NULL;
            }
        }
    }

    /* Lib_Open.libraryName */
    Strlcpy(p->libraryName, proventry->libraryName, sizeof(p->libraryName));
    p->instanceLifetimeContext = proventry->instanceLifetimeContext;

    if (NULL == proventry->interpreter)
    {
        /* Invoke MI_Main() entry point */
        {
            MI_MainFunction statikMain;

            /* Lookup symbol */
            {
                void* ptr = Shlib_Sym(p->handle, "MI_Main");

                statikMain = (MI_MainFunction)ptr;
                if (!statikMain)
                {
                    PAL_Free(p);
                    trace_SharedLibrary_CannotFindSymbol(
                        scs(proventry->libraryName), scs("MI_Main"));
                    return NULL;
                }
            }

            /* Call MI_Main */
            {
                p->module = (*statikMain)(&_server);
                if (!p->module)
                {
                    PAL_Free(p);
                    trace_Provmgr_NullModulePointer(
                        scs(proventry->libraryName), scs("MI_Main"));
                    return NULL;
                }
                if (p->module->version > MI_VERSION)
                {
                    MI_Uint32 v =  p->module->version;
                    PAL_Free(p);
                    trace_Provmgr_FailedToLoadProvider(
                        scs(proventry->libraryName), MI_VERSION_GET_MAJOR(v),
                        MI_VERSION_GET_MINOR(v), MI_VERSION_GET_REVISION(v),
                        MI_MAJOR, MI_MINOR, MI_REVISION);
                    return NULL;
                }
            }
        }
    }
    else
    {
        /* Invoke MI_Main() entry point */
        {
            typedef MI_Module* (*StartFn)(
                MI_Server* server,
                char const* const interpreter,
                char const* const startup,
                char const* const moduleName,
                MI_Module_Self** ppSelf);

            StartFn start;
            /* Lookup symbol */
            {
                void* ptr = Shlib_Sym(p->handle, "Start");
                start = (StartFn)ptr;
                if (!start)
                {
                    PAL_Free(p);
                    trace_SharedLibrary_CannotFindSymbol(
                        scs(proventry->libraryName), scs("start"));
                    return NULL;
                }
            }
            /* Call start */
            {
                p->module = (*start)(
                    &_server, proventry->interpreter, proventry->startup,
                    p->libraryName, &(p->self));
                if (!p->module)
                {
                    PAL_Free(p);
                    trace_Provmgr_NullModulePointer(
                        scs(proventry->libraryName), scs("start"));
                    return NULL;
                }
                if (p->module->version > MI_VERSION)
                {
                    MI_Uint32 v =  p->module->version;
                    PAL_Free(p);
                    trace_Provmgr_FailedToLoadProvider(
                        scs(proventry->libraryName), MI_VERSION_GET_MAJOR(v),
                        MI_VERSION_GET_MINOR(v), MI_VERSION_GET_REVISION(v),
                        MI_MAJOR, MI_MINOR, MI_REVISION);
                    return NULL;
                }
            }
        }
    }

    /* Invoke the module initialize function */
    if (p->module->Load)
    {
        Context ctx;
        MI_Result r = MI_RESULT_OK;

        Context_Init(&ctx, self, NULL, NULL);
        ctx.result = &r;

        (p->module->Load)(&p->self, (MI_Context*)&ctx);

        if (ctx.magic != 0xFFFFFFFF)
        {
            trace_ModuleLoad_FailedPostResult();
        }

        if (MI_RESULT_OK != r)
        {
            trace_FailedCallModuleLoad(r, scs(proventry->libraryName));
            return NULL;
        }
    }

    Lock_Init( &p->provlock );

    /* Add library to the list */
    List_Prepend(
        (ListElem**)&self->head,
        (ListElem**)&self->tail,
        (ListElem*)p);

    return p;
}

/*
 * Try to find specific library and open it if not found,
 * this function ensure thread-safe use of the library list
 */
static Library* MI_CALL _OpenLibrary(
    ProvMgr* self,
    _In_ const ProvRegEntry* proventry)
{
    Library* lib;
    Lock_Acquire( & self->liblock );
    lib = _OpenLibraryInternal( self, proventry );
    Lock_Release( & self->liblock );
    return lib;
}

/*
 * Try to find specific provider (class) and open it if not found,
 * this function is NOT thread-safe
 */
static Provider* MI_CALL _OpenProviderInternal(
    Library* self,
    const ZChar* className,
    Message* request)
{
    Provider* p;
    size_t psize = sizeof(Provider);

    /* Search cache first */
    for (p = self->head; p; p = p->next)
    {
        if (Tcscasecmp(p->classDecl->name, className) == 0)
        {
            Provider_Addref(p);
            return p;
        }
    }

#ifndef DISABLE_INDICATION
    /* Allocate SubscriptionManager along with Provider */
    psize += sizeof( SubscriptionManager );
#endif

    /* New Provider */
    p = (Provider*)PAL_Calloc(1, psize);

    if (!p)
    {
        LOGD_ALLOC_OOM;
        return NULL;
    }

    /* Provider.refs */
    p->refCounter = 1;
    p->lib = self;

    /* Provider.classDecl */
    {
        p->classDecl = SchemaDecl_FindClassDecl(self->module->schemaDecl,
            className);

        if (!p->classDecl || (request->tag != GetClassReqTag && !p->classDecl->providerFT))
        {
            PAL_Free(p);
            return NULL;
        }
    }

#ifndef DISABLE_INDICATION
    /*
     * Following picture explains memory layout of provider,
     * provider and submgr are sitting side by side, while
     * provider.submgr sets to the submgr's memory address
     *
     * |---------|
     * | Provider|
     * | ...     |
     * | submgr* |---|
     * |---------|<--|
     * | submgr  |
     * |         |
     * |---------|
     */
    p->subMgr = (SubscriptionManager*)(p + 1);
    SubMgr_Init(p->subMgr, p);
#endif

    if(p->classDecl->providerFT)
    {
        /* Call provider Load() method */
        if (p->classDecl->providerFT->Load)
        {
            Context ctx;
            MI_Result r = MI_RESULT_OK;

            Context_Init(&ctx, self->provmgr, p, NULL);
            ctx.result = &r;
            ctx.loadRequest = request;
            Message_AddRef(ctx.loadRequest);

            (*p->classDecl->providerFT->Load)(&p->self, self->self, &ctx.base);

            if (ctx.magic != 0xFFFFFFFF)
            {
                trace_ProviderLoad_DidNotPostResult();
            }

            if (MI_RESULT_OK != r)
            {
                trace_FailedProviderLoad(r, tcs(className));
                PAL_Free(p);
                return NULL;
            }
        }
    }

    /* Prepend to list */
    List_Prepend(
        (ListElem**)&self->head,
        (ListElem**)&self->tail,
        (ListElem*)p);

    return p;
}

/*
 * Try to find specific provider (class) and open it if not found,
 * this function is thread-safely operate the provider list
 */
static Provider* MI_CALL _OpenProvider(
    Library* self,
    const ZChar* className,
    Message* request)
{
    Provider* prov;
    Lock_Acquire( & self->provlock );
    prov = _OpenProviderInternal( self, className, request );
    Lock_Release( & self->provlock );
    return prov;
}

static MI_Result MI_CALL _GetProviderByClassName(
    _In_ ProvMgr* self,
    _In_ const ProvRegEntry* proventry,
    _In_ MI_ConstString cn,
    _In_ Message* request,
    _Out_ Provider** provOut)
{
    Library* lib;
    Provider* prov;

    trace_GetProviderByClassName(tcs(cn));

    /* Open the library */
    {
        lib = _OpenLibrary(self, proventry);

        if (!lib)
        {
            trace_OpenProviderLib_Failed(scs(proventry->libraryName));
            return MI_RESULT_FAILED;
        }
    }

    /* Open the provider */
    {
        prov = _OpenProvider(lib, cn, request);

        if (!prov)
        {
            trace_OpenProvider_FailedForClass(proventry->libraryName, tcs(cn));
            return MI_RESULT_FAILED;
        }
    }

    *provOut = prov;
    return MI_RESULT_OK;
}

static  MI_Result _Instance_InitConvert_FromBatch(
    Batch* batch,
    const MI_ClassDecl* cd,
    const MI_SchemaDecl* sd,
    MI_Instance* inst_in,
    MI_Boolean keys_only,
    MI_Boolean allow_keyless_inst,
    MI_Instance** instOut,
    MI_Uint32 flags
    )
{
    MI_Instance* inst;
    MI_Result r;

    MI_UNUSED(sd);

    /* Allocate the instance for the provider */
    inst = (MI_Instance*)Batch_GetClear(batch, cd->size);

    if (!inst)
    {
        trace_ProvMgr_AllocFailed();
        return MI_RESULT_FAILED;
    }

    /* Convert instance name to provider's format (borrow storage) */
    r = Instance_InitConvert(inst, cd, inst_in, keys_only, allow_keyless_inst, MI_FALSE,
        batch, flags);

    if (r != MI_RESULT_OK)
    {
        trace_InstanceConversionFailed(tcs(cd->name), r);
        return r;
    }

    *instOut = inst;
    return MI_RESULT_OK;
}

#ifndef DISABLE_INDICATION

/*
 * Internal helper function for _Provider_InvokeSubscribe that expects all
 * validation to be done beforehand.
 */
MI_Result _Provider_InvokeEnable(
    _Inout_ Provider* provider,
    _In_ SubscribeReq* msg )
{
    SubscriptionManager* subMgr = provider->subMgr;
    AggregationContext* aggrContext;

    trace_EnablingIndicationsForClass(provider->classDecl->name, provider);

    aggrContext = SubMgr_CreateAggrContext( subMgr );
    if ( !aggrContext )
    {
        trace_AggregationContext_InitFailed();
        return MI_RESULT_SERVER_LIMITS_EXCEEDED;
    }

    /*
     * Set enabled to true, which will be set to false if
     * posting result during EnableIndications call
     *
     */
    SubMgr_SetEnabled( subMgr, MI_TRUE );

    (*provider->classDecl->providerFT->EnableIndications)(
        provider->self,
        &aggrContext->baseCtx.base,
        msg->nameSpace,
        msg->className);

    if ( MI_FALSE == SubMgr_IsEnabled(subMgr) )
    {
        /*
         * provider posted a final result during EnableIndications call,
         * Clean up already occurred during Post handling, return here
         *
         */
        trace_ProviderEnableIndication_Failed();
        return MI_RESULT_FAILED;
    }

    return MI_RESULT_OK;
}

/*
 * Internal helper function for _Provider_RemoveSubscription that expects all
 * validation to be done beforehand.
 */
_Use_decl_annotations_
MI_Result Provider_InvokeDisable(
    Provider* provider)
{
    MI_Result result = MI_RESULT_OK;
    SubscriptionManager* subMgr;
    MI_Boolean locked;

    DEBUG_ASSERT( provider );

    subMgr = provider->subMgr;

    trace_Provider_InvokeDisable_Start( UintThreadID(), provider->classDecl->name, provider);

    locked = SubMgr_AcquireEnableLock( subMgr, AcquireFromDisable );

    if ( MI_TRUE == locked )
    {
        MI_Boolean wasEnabled = MI_FALSE;
        if ( MI_TRUE == SubMgr_IsEnabled(subMgr) )
        {
            wasEnabled = MI_TRUE;
            SubMgr_SetEnabled(subMgr, MI_FALSE);
        }

        if ( provider->classDecl->flags & MI_FLAG_INDICATION )
        {
            AggregationContext* aggrContext = SubMgr_RemoveAggrContext( subMgr );

            if ( MI_FALSE == SubMgr_IsTerminating( subMgr ) )
            {
                DEBUG_ASSERT( (MI_TRUE == wasEnabled) ? (NULL != aggrContext) : (NULL == aggrContext) );

                if ( aggrContext && ( MI_TRUE == wasEnabled ) )
                {
                    provider->classDecl->providerFT->DisableIndications(
                        provider->self,
                        &aggrContext->baseCtx.base,
                        NULL,  // TODO: Set this based on the initial SubscribeReq, but copy the value so its lifetime matches the context
                        provider->classDecl->name );
                }
            }
            // else don't need to invoke DisableIndications

            if ( aggrContext )
                AggrContext_Delete( aggrContext );
        }
        else
        {
            // TODO: release lifecycle context
        }
    }
    else
    {
        /* active subscription(s) added right before acquire the lock */
        trace_Provider_InvokeDisable_AbandonSinceNewSubscriptionAdded( UintThreadID(), provider->classDecl->name, provider);
        return MI_RESULT_OK;
    }

    /*
     * Disabled the provider, reset flags,
     * new subscribe request will success.
     */
    SubMgr_SetTerminating( subMgr, MI_FALSE );
    SubMgr_SetAllCancelledSafe( subMgr, MI_FALSE );
    SubMgr_ReleaseEnableLock( subMgr );

    trace_Provider_InvokeDisable_Complete( UintThreadID(), provider->classDecl->name, provider);
    return result;
}

void _Provider_SubscribeFail(
    _In_ SubscriptionContext* subscrContext,
    _In_ SubscribeReq* msg,
    _In_ MI_Result result )
{
    // TODO: Replace this whole func with Cancel and propagate the result to the subscription context
    PostResultMsg* finalmsg = PostResultMsg_NewAndSerialize(&msg->base.base, NULL, NULL, MI_RESULT_TYPE_MI, result);
    if (finalmsg)
    {
        Strand_SchedulePost(&subscrContext->baseCtx.strand,&finalmsg->base);
        PostResultMsg_Release(finalmsg);
        /*
         * subscribe failed and directly send final result to left side strand,
         * thus context.c:Context_PostMessageLeft won't be called,
         * so release the ref count added by SubscriptionContext.c:SubscrContext_Init
         */
        SubMgrSubscription_Release( subscrContext->subscription );
    }
    else
    {
        trace_OutOfMemory();
        Strand_ScheduleCancel(&subscrContext->baseCtx.strand);
    }
}

_Use_decl_annotations_
void Provider_InvokeSubscribe(
    Provider* provider,
    SubscribeReq* msg,
    SubscriptionContext* subscrContext )
{
    MI_Result result = MI_RESULT_OK;
    SubscriptionManager* subMgr;
    MI_Boolean locked;
    SubscriptionTargetType subType;
    SubMgrSubscription* subscription = NULL;

    DEBUG_ASSERT ( provider && subscrContext );
    DEBUG_ASSERT( provider->subMgr );
    STRAND_ASSERTONSTRAND(&subscrContext->baseCtx.strand);

    if( subscrContext->baseCtx.strand.canceled )
    {
        // abort creating subscription
        Strand_Leave( &subscrContext->baseCtx.strand );
        return;
    }

    subMgr = provider->subMgr;
    subType = (SubscriptionTargetType)msg->targetType;

    do
    {
        trace_ProviderInvokeSubscribe_Begin(UintThreadID(), provider, msg, msg->base.base.tag, subscrContext );

        /* To ensure enable/cancel thread safe */
        locked = SubMgr_AcquireEnableLock( subMgr, AcquireFromSubscribe );
        if ( MI_FALSE == locked )
        {
            result = MI_RESULT_FAILED;
            Strand_Leave( &subscrContext->baseCtx.strand );
            break;
        }

        /*
         * Sanity checks of the request prior to initializing the context and
         * completing the interaction open.
         *
         * These checks can return immediate failure without clean up
         */
        if (SUBSCRIP_TARGET_DEFAULT == subType )
        {
            /*
             * if class is not indication class, then indication manager has a bug
             */
            DEBUG_ASSERT (provider->classDecl->flags & MI_FLAG_INDICATION);
            /*
             * if classdecl is not valid, then omireg tool has a bug
             */
            DEBUG_ASSERT (
                provider->classDecl->providerFT->EnableIndications &&
                provider->classDecl->providerFT->Subscribe);
        }
        else if (SubscriptionTargetType_IsLifecycle( subType ))
        {
            // lifecycleCtx should have been initialized during provider Load().
            if ( ! subMgr->lifecycleCtx )
            {
                trace_LifecycleSubscription_ContextNotInitialized(provider->classDecl->name);
                result = MI_RESULT_FAILED;
                break;
            }

            if ( ! LifeContext_IsTypeSupported(subMgr->lifecycleCtx, msg->targetType) )
            {
                trace_LifecycleSubscription_UnsupportedTargetType(
                    provider->classDecl->name, msg->targetType, subMgr->lifecycleCtx->supportedTypesFromProv);
                result = MI_RESULT_NOT_SUPPORTED;
                Strand_Leave( &subscrContext->baseCtx.strand );
                break;
            }
        }
        else
        {
            trace_InvokeSubscribeWithInvalidTargetType( subType );
            result = MI_RESULT_FAILED;
            Strand_Leave( &subscrContext->baseCtx.strand );
            break;
        }

        subscription = subscrContext->subscription;
        SubscriptionList_AddSubscription( &subMgr->subscrList, subscription );

        /*
         * Upon SubscriptionContext was initialized successfull,
         * it hold one refcount of msg, which will be released
         * inside _Context_Destory;
         *
         * SubscriptionContext was initialized successfully,
         * following logic should report error through
         * interaction interface then.
         */

        /*
         * Acquire post lock, so post indication and result from provider's thread
         * will be blocked until Enable/Subscribe call finished
         *
         */
        SubMgrSubscription_Addref( subscription );
        SubMgrSubscription_AcquirePostLock( subscription );

        /* Alert indication setup */
        if (SUBSCRIP_TARGET_DEFAULT == msg->targetType )
        {
            SubMgr_SetEnableThread( subMgr );

            Strand_Leave( &subscrContext->baseCtx.strand );
            /*
             * EnableIndications must be called for each provider
             * prior to the first Subscribe call for alert indication
             */
            if ( MI_FALSE == SubMgr_IsEnabled( subMgr ) )
            {
                result = _Provider_InvokeEnable( provider, msg );
                if (MI_RESULT_OK != result)
                {
                    trace_EnableIndication_Failed(provider->classDecl->name);
                    result = MI_RESULT_OK;
                    break;
                }
            }

            DEBUG_ASSERT (SubMgr_IsEnabled( subMgr ));

            SubMgrSubscription_SetState(subscription, SubscriptionState_Subscribed);

            /*
             * Invoke Subscribe with dumpy context
             * provider cannot postinstance or indication to this context
             */
            {
                Context ctx;
                MI_Result r = MI_RESULT_OK;
                Subunsub_Context_Init(&ctx, &r, &msg->base);
                (*provider->classDecl->providerFT->Subscribe)(
                    provider->self,
                    &ctx.base,
                    msg->nameSpace,
                    msg->className,
                    &subscrContext->subscription->filter->base,
                    msg->bookmark,
                    msg->subscriptionID,
                    (void**)&subscrContext->subself);
                Context_Close(&ctx);
            }

            if (SubscriptionState_Subscribed == subscrContext->subscription->state)
            {
                trace_Provider_InvokeSubscribe(subscrContext->subscription);

                /*
                 * Subscribe succeeded, send subscribe response,
                 * otherwise finalresult already sent within Subscribe call
                 */
                SubscrContext_SendSubscribeResponseMsg( subscrContext );
                trace_SubscrForEvents_Succeeded(provider->classDecl->name, msg->subscriptionID);
                result = MI_RESULT_OK;
                break;
            }
        }
        /*
         * Lifecycle indication setup
         */
        else if (SubscriptionTargetType_IsLifecycle( (SubscriptionTargetType)msg->targetType ))
        {
            if ( MI_FALSE == SubMgr_IsEnabled( subMgr ) )
                SubMgr_SetEnabled( subMgr, MI_TRUE );

            SubMgrSubscription_SetState( subscrContext->subscription, SubscriptionState_Subscribed );

            LifeContext_UpdateSupportedTypes( subMgr->lifecycleCtx );

            Strand_Leave( &subscrContext->baseCtx.strand );
            SubscrContext_SendSubscribeResponseMsg( subscrContext );
            trace_SubscrForLifecycle_Succeeded(provider->classDecl->name, msg->subscriptionID);

            result = MI_RESULT_OK;
            break;
        }
    }
    while( 0 );

    if ( subscription )
    {
        /*
         * Release post lock, so indication and result
         * posted from provider will go through
         */
        SubMgrSubscription_ReleasePostLock( subscription );
        SubMgrSubscription_Release( subscription );
    }

    /*
     * Now release lock to allow Disable/other subscribe request to continue
     */
    if ( MI_TRUE == locked )
        SubMgr_ReleaseEnableLock( subMgr );

    trace_ProviderInvokeSubscribe_End(UintThreadID(), provider, result);

    /*
     * Once the SubscrContext has been initialized, the interactions is "Open"
     * and must be shut down using the appropriate Strand calls.  Those calls
     * will handle clean up.  This must return MI_RESULT_OK for that to happen.
     */
    if ( result != MI_RESULT_OK )
    {
        _Provider_SubscribeFail( subscrContext, msg, result );
    }
}

/*
 * Invoke EnableIndication if not called yet;
 * and invoke Subscribe call to provider;
 *
 * To ensure enable/disable thread-safe, and since
 * OMI has single IO thread, this function has to be scheduled
 * on separate thread for OMI.
 * TODO: remove separate thread if have multi-IO threads implemented
 */
MI_Result _Provider_InvokeSubscribeWrapper(
    _In_ Provider* provider,
    _Inout_ InteractionOpenParams* interactionParams )
{
    SubscriptionContext* subscrContext;
    MI_Result result;

    result = SubMgr_CreateSubscription( provider->subMgr, provider, interactionParams, &subscrContext );
    if ( MI_RESULT_OK != result )
    {
        trace_FailedToAddSubscrMgr();
        return result;
    }

    result = Schedule_SubscribeRequest( provider, (SubscribeReq*)interactionParams->msg, subscrContext );
    if( MI_RESULT_OK != result )
    {
        _Provider_SubscribeFail( subscrContext, (SubscribeReq*)interactionParams->msg, result );
        /*
         * schedule failed so CONTEXT_STRANDAUX_INVOKESUBSCRIBE won't be called,
         * so release the ref count added by _SubMgrSubscription_New
         */
        SubMgrSubscription_Release( subscrContext->subscription );
    }

    return MI_RESULT_OK;
}

_Use_decl_annotations_
MI_Result Provider_RemoveSubscription(
    Provider* provider,
    MI_Uint64 subscriptionID)
{
    SubMgrSubscription* subscription = NULL;
    SubscriptionManager* subMgr;
    MI_Result result = MI_RESULT_OK;

    DEBUG_ASSERT (provider && provider->subMgr);
    subMgr = provider->subMgr;

    trace_RemovingSubscriptionForClass(subscriptionID, provider->classDecl->name);
    subscription = SubMgr_GetSubscription( subMgr, subscriptionID );
    if (NULL == subscription)
    {
        /* Not present or not found means that there is nothing to do. */
        return MI_RESULT_OK;
    }

    SubMgrSubscription_SetState(subscription, SubscriptionState_Unsubscribed);

    result = SubMgr_DeleteSubscription( subMgr, subscription);

    /* check if the subscription list was empty or not */
    if ( MI_TRUE == SubMgr_IsSubListEmpty( subMgr ) )
    {
        /*
         * The specified subscription is the LAST one for its
         * SubscriptionManager. Indications should be disabled for this
         * provider. There is separate cleanup for Lifecycle and "normal"
         * indications.  SubscriptionManager will be cleaned up once the
         * provider processes the Disable call.
         */
        result = Provider_InvokeDisable ( provider );
    }

    return result;
}

_Use_decl_annotations_
MI_Result Provider_TerminateIndication(
    Provider* provider,
    MI_Result result,
    const ZChar* errorMessage,
    const MI_Instance* cimError )
{
    SubscriptionManager* subMgr;
    MI_Boolean locked;
    DEBUG_ASSERT (provider && provider->subMgr);

    trace_Provider_TerminateIndication_Start( UintThreadID(), provider->classDecl->name, provider);

    Provider_Addref( provider );

    subMgr = provider->subMgr;

    /*
     * SubMgr_AcquireEnableLock cancel all subscriptions if have any,
     * internally it call Provider_InvokeDisable if no subscription;
     * otherwise just return;
     * Provider_InvokeDisable releases the aggregation context;
     */
    locked = SubMgr_AcquireEnableLock( subMgr, AcquireFromTerminate );
    DEBUG_ASSERT( MI_TRUE == locked );
    if (locked)
    {
        SubMgr_ReleaseEnableLock( subMgr );
    }

    trace_Provider_TerminateIndication_Complete( UintThreadID(), provider->classDecl->name, provider);

    Provider_Release( provider );

    return MI_RESULT_OK;
}

#endif /* ifndef DISABLE_INDICATION */

static MI_Result _HandleGetInstanceReq(
    _In_ ProvMgr* self,
    _In_ const ProvRegEntry* proventry,
    _Inout_ InteractionOpenParams* interactionParams,
    _Out_ Provider** prov)
{
    MI_Instance* inst;
    MI_Result r;
    const ZChar* className;
    GetInstanceReq* msg = (GetInstanceReq*)interactionParams->msg;

    /* Get classname from instance */
    r = __MI_Instance_GetClassName(msg->instanceName, &className);

    if (r != MI_RESULT_OK)
        return r;

    trace_New_Request(MessageName(msg->base.base.tag), tcs(msg->nameSpace), tcs(className));

    /* find provider */
    r = _GetProviderByClassName(
        self,
        proventry,
        className,
        &msg->base.base,
        prov);

    if ( MI_RESULT_OK != r )
        return r;

    /* Allocate the instance for the provider */
    r = _Instance_InitConvert_FromBatch(
        msg->base.base.batch,
        (*prov)->classDecl,
        (*prov)->lib->module->schemaDecl,
        msg->instanceName,
        MI_TRUE,
        MI_FALSE,
        &inst,
        msg->base.base.flags);

    if (MI_RESULT_OK != r)
        return r;

#if 0
    /* Print instance */
    Instance_Print(inst, stdout, 0, MI_FALSE, MI_FALSE);
#endif

    /* If provider's GetInstance method null, use EnumerateInstances */
    if ((*prov)->classDecl->providerFT->GetInstance == NULL)
    {
        Context* ctx;

        if ((*prov)->classDecl->providerFT->EnumerateInstances == NULL)
            return MI_RESULT_INVALID_CLASS;

        /* Create context */
        ctx = (Context*)Batch_GetClear(msg->base.base.batch, sizeof(Context));;
        r = Context_Init(ctx, self, (*prov), interactionParams);
        if( MI_RESULT_OK != r )
            return r;

        /* _PostInstance() filters by this if not null */
        ctx->instanceName = inst;

        /* Invoke provider */
        (*(*prov)->classDecl->providerFT->EnumerateInstances)(
            (*prov)->self,
            &ctx->base,
            msg->nameSpace,
            className,
            NULL, /* propertySet */
            MI_FALSE, /* keysOnly */
            NULL); /* filter */
    }
    else
    {
        Context* ctx;

        /* Create context */
        ctx = (Context*)Batch_GetClear(msg->base.base.batch, sizeof(Context));;
        r = Context_Init(ctx, self, (*prov), interactionParams);
        if( MI_RESULT_OK != r )
            return r;

        /* Invoke provider */
        (*(*prov)->classDecl->providerFT->GetInstance)(
            (*prov)->self,
            &ctx->base,
            msg->nameSpace,
            className,
            inst,
            NULL);
    }

    return MI_RESULT_OK;
}

static void _PostClassToCallback(
    Context* self,
    InteractionOpenParams* params,
    const MI_Class* schema)
{
    MI_Result result = MI_RESULT_OK;
    PostSchemaMsg* resp = PostSchemaMsg_New(self->request->base.operationId);

    if (!resp)
    {
        trace_PostSchemaMsg_Failed();
        result = MI_RESULT_FAILED;
        goto End;
    }

    if (self->request->base.flags & WSMANFlag)
    {
        result = WSBuf_ClassToBuf(
                    schema,
                    self->request->base.flags,
                    resp->base.batch,
                    &resp->packedSchemaWsmanPtr,
                    &resp->packedSchemaWsmanSize);

        trace_ProvMgr_PostingSchemaInWsmanToCallback();

        if(result != MI_RESULT_OK)
        {
            trace_SchemaConversion_ToCimXmlFailed(result);
            goto End;
        }

        resp->base.flags |= self->request->base.flags;
    }
    else
    {
        result = Instance_New(&resp->schemaInstance, schema->classDecl, resp->base.batch);
        if (result != MI_RESULT_OK)
        {
            trace_SchemaConversion_ToInstanceFailed(result);
            goto End;
        }

        result = InstanceToBatch(
            resp->schemaInstance,
            NULL,
            NULL,
            resp->base.batch,
            &resp->packedSchemaInstancePtr,
            &resp->packedSchemaInstanceSize);
        if (result != MI_RESULT_OK)
        {
            trace_SchemaInstancePackaging_Failed(result);
            goto End;
        }

        resp->base.flags |= BinaryProtocolFlag;
    }

    Context_CompleteOpen( self, params, MI_RESULT_OK );
    Context_PostSchema( self, &resp->base);
    {
        PostResultMsg* msg = PostResultMsg_New( self->request->base.operationId );
        if (msg)
        {
            msg->requestTag = self->request->base.tag;
            msg->requestFlags = self->request->base.flags;
            Context_PostMessageLeft( self, &msg->base );
            PostResultMsg_Release( msg );
        }
    }

    Strand_ScheduleClose(&self->strand);
End:
    if(resp)
    {
        PostSchemaMsg_Release(resp);
    }

    if( MI_RESULT_OK != result )
    {
        Context_CompleteOpen( self, params, result );
    }
}


static MI_Result _HandleGetClassReq(
    _In_ ProvMgr* self,
    _In_ const ProvRegEntry* proventry,
    _Inout_ InteractionOpenParams* interactionParams,
    _Out_ Provider** prov)
{
    MI_Result r;
    MI_Class resultClass;
    Context* ctx = NULL;
    GetClassReq* msg = (GetClassReq*)interactionParams->msg;

    trace_New_Request(MessageName(msg->base.base.tag), tcs(msg->nameSpace), tcs(msg->className));

    memset(&resultClass, 0, sizeof(MI_Class));

    /* find provider */
    r = _GetProviderByClassName(
        self,
        proventry,
        msg->className,
        &msg->base.base,
        prov);

    if ( MI_RESULT_OK != r )
        return r;

    ctx = (Context*)Batch_GetClear(msg->base.base.batch,
            sizeof(Context));;
    r = Context_PartialInit(ctx, (*prov), interactionParams);
    if( MI_RESULT_OK != r )
        return r;

    // by default serializer will use the function tables to access resultClass as a wrapper to MI_ClassDecl
    // this place will be modified in future to fill in the appropriate extended function tables
    // providing access to schema in form of instance of cimclass
    Class_Construct(&resultClass, (*prov)->classDecl);

    _PostClassToCallback(ctx, interactionParams, &resultClass);
    return MI_RESULT_OK;
}

static MI_Result _HandleCreateInstanceReq(
    _In_ ProvMgr* self,
    _In_ const ProvRegEntry* proventry,
    _Inout_ InteractionOpenParams* interactionParams,
    _Out_ Provider** prov)
{
    MI_Instance* inst;
    MI_Result r;
    const ZChar* className;
    CreateInstanceReq* msg = (CreateInstanceReq*)interactionParams->msg;

    /* Get classname from instance */
    r = __MI_Instance_GetClassName(msg->instance, &className);

    if (r != MI_RESULT_OK)
        return r;

    trace_New_Request(MessageName(msg->base.base.tag), tcs(msg->nameSpace), tcs(className));

    /* find provider */
    r = _GetProviderByClassName(
        self,
        proventry,
        className,
        &msg->base.base,
        prov);

    if ( MI_RESULT_OK != r )
        return r;

    /* Allocate the instance for the provider */
    r = _Instance_InitConvert_FromBatch(
        msg->base.base.batch,
        (*prov)->classDecl,
        (*prov)->lib->module->schemaDecl,
        msg->instance,
        MI_FALSE,
        MI_TRUE,
        &inst,
        msg->base.base.flags);

    if (MI_RESULT_OK != r)
        return r;

    /* Invoke provider */
    if (!(*prov)->classDecl->providerFT->CreateInstance)
        return MI_RESULT_INVALID_CLASS;

    {
        Context* ctx = (Context*)Batch_GetClear(msg->base.base.batch,
            sizeof(Context));;
        Context_Init(ctx, self, (*prov), interactionParams);
        if( MI_RESULT_OK != r )
            return r;

        /* message will be freed in context release*/
        (*(*prov)->classDecl->providerFT->CreateInstance)((*prov)->self, &ctx->base,
            msg->nameSpace, className, inst);
    }

    return MI_RESULT_OK;
}

static MI_Result _HandleModifyInstanceReq(
    _In_ ProvMgr* self,
    _In_ const ProvRegEntry* proventry,
    _Inout_ InteractionOpenParams* interactionParams,
    _Out_ Provider** prov)
{
    MI_Instance* inst;
    MI_Result r;
    const ZChar* className;
    ModifyInstanceReq* msg = (ModifyInstanceReq*)interactionParams->msg;

    /* Get classname from instance */
    r = __MI_Instance_GetClassName(msg->instance, &className);

    if (r != MI_RESULT_OK)
        return r;

    trace_New_Request(MessageName(msg->base.base.tag), tcs(msg->nameSpace), tcs(className));

    /* find provider */
    r = _GetProviderByClassName(
        self,
        proventry,
        className,
        &msg->base.base,
        prov);

    if ( MI_RESULT_OK != r )
        return r;

    /* Allocate the instance for the provider */
    r = _Instance_InitConvert_FromBatch(
        msg->base.base.batch,
        (*prov)->classDecl,
        (*prov)->lib->module->schemaDecl,
        msg->instance,
        MI_FALSE,
        MI_FALSE,
        &inst,
        msg->base.base.flags);

    if (MI_RESULT_OK != r)
        return r;

    /* Invoke provider */
    if (!(*prov)->classDecl->providerFT->ModifyInstance)
        return MI_RESULT_INVALID_CLASS;

    {
        Context* ctx = (Context*)Batch_GetClear(msg->base.base.batch,
            sizeof(Context));;
        r = Context_Init(ctx, self, (*prov), interactionParams);
        if( MI_RESULT_OK != r )
            return r;

        /* Need to store instance in case we need to call GetInstance */
        ctx->keyInstance = inst;

        /* message will be freed in context release*/
        (*(*prov)->classDecl->providerFT->ModifyInstance)((*prov)->self, &ctx->base,
            msg->nameSpace, className, inst, NULL);
    }

    return MI_RESULT_OK;
}

static MI_Result _HandleDeleteInstanceReq(
    _In_ ProvMgr* self,
    _In_ const ProvRegEntry* proventry,
    _Inout_ InteractionOpenParams* interactionParams,
    _Out_ Provider** prov)
{
    MI_Instance* inst;
    MI_Result r;
    const ZChar* className;
    DeleteInstanceReq* msg = (DeleteInstanceReq*)interactionParams->msg;

    /* Get classname from instance */
    r = __MI_Instance_GetClassName(msg->instanceName, &className);

    if (r != MI_RESULT_OK)
        return r;

    trace_New_Request(MessageName(msg->base.base.tag), tcs(msg->nameSpace), tcs(className));

    /* find provider */
    r = _GetProviderByClassName(
        self,
        proventry,
        className,
        &msg->base.base,
        prov);

    if ( MI_RESULT_OK != r )
        return r;

    /* Allocate the instance for the provider */
    r = _Instance_InitConvert_FromBatch(
        msg->base.base.batch,
        (*prov)->classDecl,
        (*prov)->lib->module->schemaDecl,
        msg->instanceName,
        MI_TRUE,
        MI_FALSE,
        &inst,
        msg->base.base.flags);

    if (MI_RESULT_OK != r)
        return r;

    /* Invoke provider */
    if (!(*prov)->classDecl->providerFT->DeleteInstance)
        return MI_RESULT_INVALID_CLASS;

    {
        Context* ctx = (Context*)Batch_GetClear(msg->base.base.batch,
            sizeof(Context));;
        r = Context_Init(ctx, self, (*prov), interactionParams);
        if( MI_RESULT_OK != r )
            return r;

        /* message will be freed in context release*/
        (*(*prov)->classDecl->providerFT->DeleteInstance)((*prov)->self, &ctx->base,
            msg->nameSpace, className, inst);
    }

    return MI_RESULT_OK;
}

#ifndef DISABLE_INDICATION

/*
 * Behaves conditionally depending on whether or not indications were
 * compiled into the product.
 */
static MI_Result _HandleSubscribeReq(
    _In_ ProvMgr* self,
    _In_ const ProvRegEntry* proventry,
    _Inout_ InteractionOpenParams* interactionParams,
    _Out_ Provider** prov)
{
    MI_Result r;
    SubscribeReq* msg = (SubscribeReq*)interactionParams->msg;

    trace_New_Request(MessageName(msg->base.base.tag), tcs(msg->nameSpace), tcs(msg->className));

    *prov = NULL;

    /* find provider */
    r = _GetProviderByClassName(
        self,
        proventry,
        msg->className,
        &msg->base.base,
        prov);

    if ( MI_RESULT_OK != r )
    {
        trace_ProvMgr_ClassNotFound( tcs(msg->className) );
        return r;
    }

    return _Provider_InvokeSubscribeWrapper( *prov, interactionParams );
}

#endif /* ifndef DISABLE_INDICATION */

static MI_Result _HandleInvokeReq(
    _In_ ProvMgr* self,
    _In_ const ProvRegEntry* proventry,
    _Inout_ InteractionOpenParams* interactionParams,
    _Out_ Provider** prov)
{
    MI_Instance* inst = 0;
    MI_Instance* instParams = 0;
    MI_Result r;
    MI_ConstString cn = 0;
    MI_MethodDecl* md = 0;
    InvokeReq* msg = (InvokeReq*)interactionParams->msg;

#if 0
    MessagePrint(&msg->base, stdout);
#endif

    /* parameter validation */
    if (!msg || !msg->function)
        return MI_RESULT_INVALID_PARAMETER;

    trace_New_Request(MessageName(msg->base.base.tag), tcs(msg->nameSpace), tcs(msg->className));

    if (msg->className)
        cn = msg->className;
    else if (msg->instance)
        cn = ((Instance*) msg->instance)->classDecl->name;

    if (!cn)
        return MI_RESULT_INVALID_CLASS;

    /* find provider */
    r = _GetProviderByClassName(
        self,
        proventry,
        cn,
        &msg->base.base,
        prov);

    if ( MI_RESULT_OK != r )
        return r;

    /* find method declaration */
    md = SchemaDecl_FindMethodDecl( (*prov)->classDecl, msg->function );

    if (!md)
        return MI_RESULT_FAILED;

    /* if method is not static, instance must be provided */
    if (!msg->instance && (md->flags & MI_FLAG_STATIC) != MI_FLAG_STATIC)
        return MI_RESULT_INVALID_PARAMETER;

    if (msg->instance)
    {

        r = _Instance_InitConvert_FromBatch(
            msg->base.base.batch,
            (*prov)->classDecl,
            (*prov)->lib->module->schemaDecl,
            msg->instance,
            MI_TRUE,
            MI_FALSE,
            &inst,
            msg->base.base.flags);

        if (MI_RESULT_OK != r)
            return r;
    }

    if (msg->instanceParams)
    {
        /* parameters (if any) */
        r = _Instance_InitConvert_FromBatch(
            msg->base.base.batch,
            (const MI_ClassDecl*)md,
            (*prov)->lib->module->schemaDecl,
            msg->instanceParams,
            MI_FALSE,
            MI_TRUE,
            &instParams,
            msg->base.base.flags);

        if (MI_RESULT_OK != r)
            return r;
    }

#if 0
    /* Print instance */
    Instance_Print(inst, stdout, 0, 0, 0);
#endif

    /* Invoke provider */
    if (!md->function)
        return MI_RESULT_INVALID_CLASS;

    {
        Context* ctx = (Context*)Batch_GetClear(msg->base.base.batch, sizeof(Context));
        r = Context_Init(ctx, self, (*prov), interactionParams);
        if( MI_RESULT_OK != r )
            return r;

        /* call get first if fn is non-static */
        /*if (inst && (*prov)->classDecl->providerFT->GetInstance)
        {
            ctx->ctxType = CTX_TYPE_INVOKE_WITH_INSTANCE;
            ctx->inst = inst;
            ctx->instParams = instParams;
            ctx->md = md;
            ctx->prov_self = (*prov)->self;

            (*(*prov)->classDecl->providerFT->GetInstance)((*prov)->self, &ctx->base,
                __nameSpace, __className, inst, NULL);
        }
        else */   /* for static - call invoke directly */
            (*md->function)((*prov)->self, &ctx->base,
                msg->nameSpace, cn, msg->function, inst, instParams);
    }

    return MI_RESULT_OK;
}

static MI_Result _HandleEnumerateInstancesReq(
    _In_ ProvMgr* self,
    _In_ const ProvRegEntry* proventry,
    _Inout_ InteractionOpenParams* interactionParams,
    _Out_ Provider** prov)
{
    Context* ctx;
    MI_Result r;
    EnumerateInstancesReq* msg = (EnumerateInstancesReq*)interactionParams->msg;
    InstanceFilter* instanceFilter = NULL;
    MI_Filter* filter = NULL;

#if 0
    MessagePrint(&msg->base, stdout);
#endif

    trace_New_Request(MessageName(msg->base.base.tag), tcs(msg->nameSpace), tcs(msg->className));

    /* find provider unless we are enumerating shells. If it is a shell
     * enumeration we skip the provider itself and pull the data out of the
     * agentmgr itself.*/
    if (((msg->base.base.flags & WSMAN_IsShellRequest) == 0) ||
        ((msg->base.base.flags & WSMAN_IsShellRequest) && (Tcscmp(msg->className, MI_T("Shell")) != 0)))
    {
        r = _GetProviderByClassName(
                self,
                proventry,
                msg->className,
                &msg->base.base,
                prov);

        if ( MI_RESULT_OK != r )
            return r;
    }

    DEBUG_ASSERT(msg->wql == NULL);

    /* Get WQL query, if any */
    if (msg->queryLanguage != NULL && msg->queryExpression != NULL)
    {
        /* Create filter then Get WQL query */
        instanceFilter = InstanceFilter_New( &(msg->base.base) );

        if (instanceFilter == NULL)
        {
            trace_InstanceFilter_AllocFailed();
            return MI_RESULT_INVALID_QUERY;
        }

        filter = &(instanceFilter->base);

        msg->wql = InstanceFilter_GetWQL(instanceFilter);
    }

    /* Validate WQL query (if any) against provider's class declaration */
    if (msg->wql)
    {
        if (WQL_Validate(msg->wql, (*prov)->classDecl) != 0)
        {
            trace_QueryValidationFailed(tcs(msg->wql->text));
            return MI_RESULT_INVALID_QUERY;
        }
    }

    /* Invoke provider */
    if (((msg->base.base.flags & WSMAN_IsShellRequest) == 0) &&
        (!(*prov)->classDecl->providerFT->EnumerateInstances))
        return MI_RESULT_NOT_SUPPORTED;

    /* Create the context object */
    {
        ctx = (Context*)Batch_GetClear(
            msg->base.base.batch, sizeof(Context));;

        if (!ctx)
        {
            trace_ProvMgr_AllocFailed();
            return MI_RESULT_FAILED;
        }

        r = Context_Init(ctx, self, (*prov), interactionParams);

        if( MI_RESULT_OK != r )
            return r;
    }

    trace_ProvMgr_EnumerateInstancesOfClass( tcs(msg->className) );

    (*(*prov)->classDecl->providerFT->EnumerateInstances)(
            (*prov)->self, &ctx->base,
            msg->nameSpace, msg->className, NULL, MI_FALSE, filter);

    return MI_RESULT_OK;
}

static MI_Result MI_CALL _HandleAssociatorsOfReq(
    _In_ ProvMgr* self,
    _In_ const ProvRegEntry* proventry,
    _Inout_ InteractionOpenParams* interactionParams,
    _Out_ Provider** prov)
{
    Context* ctx;
    MI_Result r;
    MI_Instance* inst = 0;
    AssociationsOfReq* msg = (AssociationsOfReq*)interactionParams->msg;

    trace_New_Request(MessageName(msg->base.base.tag), tcs(msg->nameSpace), tcs(msg->className));

    /* find provider */
    r = _GetProviderByClassName(
        self,
        proventry,
        msg->className,
        &msg->base.base,
        prov);

    if ( MI_RESULT_OK != r )
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
            proventry,
            ((Instance*) msg->instance)->classDecl->name,
            &msg->base.base,
            &provInst );

        if ( MI_RESULT_OK != r )
            return r;

        r = _Instance_InitConvert_FromBatch(
            msg->base.base.batch,
            provInst->classDecl,
            (*prov)->lib->module->schemaDecl,
            msg->instance,
            MI_TRUE,
            MI_FALSE,
            &inst,
            msg->base.base.flags);

        Provider_Release(provInst);

        if (MI_RESULT_OK != r)
            return r;
    }

    ctx = (Context*)Batch_GetClear(
        msg->base.base.batch, sizeof(Context));;

    if (!ctx)
    {
        trace_ProvMgr_AllocFailed();
        return MI_RESULT_FAILED;
    }

    r = Context_Init(ctx, self, (*prov), interactionParams);
    if( MI_RESULT_OK != r )
        return r;

    /* message will be freed in context release */
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

    return MI_RESULT_OK;
}

static MI_Result _HandleReferencesOfReq(
    _In_ ProvMgr* self,
    _In_ const ProvRegEntry* proventry,
    _Inout_ InteractionOpenParams* interactionParams,
    _Out_ Provider** prov)
{
    Context* ctx;
    MI_Result r;
    MI_Instance* inst = 0;
    AssociationsOfReq* msg = (AssociationsOfReq*)interactionParams->msg;

    trace_New_Request(MessageName(msg->base.base.tag), tcs(msg->nameSpace), tcs(msg->className));

    /* find provider */
    r = _GetProviderByClassName(
        self,
        proventry,
        msg->className,
        &msg->base.base,
        prov );

    if ( MI_RESULT_OK != r )
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
            proventry,
            ((Instance*) msg->instance)->classDecl->name,
            &msg->base.base,
            &provInst );

        if ( MI_RESULT_OK != r )
            return r;

        r = _Instance_InitConvert_FromBatch(
            msg->base.base.batch,
            provInst->classDecl,
            (*prov)->lib->module->schemaDecl,
            msg->instance,
            MI_TRUE,
            MI_FALSE,
            &inst,
            msg->base.base.flags);

        Provider_Release(provInst);

        if (MI_RESULT_OK != r)
            return r;
    }

    ctx = (Context*)Batch_GetClear(
        msg->base.base.batch, sizeof(Context));;

    if (!ctx)
    {
        trace_ProvMgr_AllocFailed();
        return MI_RESULT_FAILED;
    }

    r = Context_Init(ctx, self, (*prov), interactionParams);
    if( MI_RESULT_OK != r )
        return r;

    /* message will be freed in context release */
    (*(*prov)->classDecl->providerFT->ReferenceInstances)(
        (*prov)->self,
        &ctx->base,
        msg->nameSpace,
        msg->className,
        inst,
        msg->role,
        NULL, MI_FALSE, NULL);

    return MI_RESULT_OK;
}

static void _UnloadAllProviders(
    ProvMgr* self,
    Library* lib,
    MI_Boolean idleOnly,
    MI_Uint64 currentTimeUsec,
    MI_Uint64* nextFireAtTime)
{
    Provider* p, *p_next;

    for (p = lib->head; p; )
    {
        /* ATTN: idleSince is sometimes 0 */

        MI_Uint64 provFireAtTime;
        if (p->idleSince != 0)
            provFireAtTime = p->idleSince + self->idleTimeoutUsec;
        else
            provFireAtTime = ~((MI_Uint64)0);

        p_next = p->next;

        /* unload if 'force' option passed or provider is idle long enough */
        if (!idleOnly ||
            (!p->refusedUnload && 0 == p->refCounter && provFireAtTime <= currentTimeUsec))
        {
            trace_ProvMgr_UnloadingProvider( tcs(p->classDecl->name) );

#ifndef DISABLE_INDICATION
            if (p->subMgr)
            {
                if (p->subMgr->lifecycleCtx)
                {
                    LifeContext_Delete(p->subMgr->lifecycleCtx);
                    p->subMgr->lifecycleCtx = NULL;
                }
            }
#endif /* ifndef DISABLE_INDICATION */

            /* Call provider unload() method */
            if (p->classDecl->providerFT && p->classDecl->providerFT->Unload)
            {
                Context ctx;
                Context_Init(&ctx, self, 0, NULL);
                (*p->classDecl->providerFT->Unload)(p->self, &ctx.base);

                DEBUG_ASSERT(ctx.magic == (MI_Uint32)-1);
            }

            if (p->refCounter != 0)
            {
                /* Error condition - unloading active provider! */
                trace_UnloadingActiveProvider(
                    tcs(p->classDecl->name), (int)p->refCounter);
                trace_UnloadingActiveProviderWithLib(
                    scs(lib->libraryName), (int)p->refCounter);

                /* ATTN: _exit is a good option here, since provider's behavior maybe undefined */
                trace_UnloadingActiveProvider_ServerExit(scs(lib->libraryName));
                _exit(1);
            }

            List_Remove(
                (ListElem**)&lib->head,
                (ListElem**)&lib->tail,
                (ListElem*)p);

            Provider_Finalize( p );
            PAL_Free(p);
        }
        else if (idleOnly && 0 == p->refCounter && nextFireAtTime)
        {
            /* re-calculate idle timeout */

            if (provFireAtTime < *nextFireAtTime)
                *nextFireAtTime = provFireAtTime;
        }

        /* move to next one */
        p = p_next;
    }
}

/*
 * Unload all libraries *NOT* thread safely
 */
static void _UnloadAllLibrariesInternal(
    ProvMgr* self,
    MI_Boolean idleOnly,
    MI_Uint64 currentTimeUsec,
    MI_Uint64* nextFireAtTime)
{
    Library* p, *p_next;

    /* release all (or idle-only) opened libraries */
    for (p = self->head; p; )
    {
        p_next = p->next;

        Lock_Acquire( &p->provlock );
        _UnloadAllProviders(self,p,idleOnly,currentTimeUsec,nextFireAtTime);
        Lock_Release( &p->provlock );

        /* Unload libraries that have no loaded providers */
        if (!p->head)
        {
            /* Invoke the module un-initialize function */
            if (p->module->Unload)
            {
                Context ctx;
                MI_Result r = MI_RESULT_OK;

                Context_Init(&ctx, self, NULL, NULL);
                ctx.result = &r;

                (p->module->Unload)(p->self, (MI_Context*)&ctx);

                if (ctx.magic != 0xFFFFFFFF)
                {
                    trace_LibraryUnload_DidNotPostResult();
                }

                if (MI_RESULT_OK != r)
                {
                    trace_FailedCallLibraryUnload(r, scs(p->libraryName));
                }
            }

            Shlib_Close(p->handle);
            trace_ProvMgr_UnloadingLibrary( scs(p->libraryName) );

            List_Remove(
                (ListElem**)&self->head,
                (ListElem**)&self->tail,
                (ListElem*)p);

            PAL_Free(p);
        }

        p = p_next;
    }
}

/*
 * Unload all libraries thread safely
 */
static void _UnloadAllLibraries(
    ProvMgr* self,
    MI_Boolean idleOnly,
    MI_Uint64 currentTimeUsec,
    MI_Uint64* nextFireAtTime)
{
    Lock_Acquire( &self->liblock );
    _UnloadAllLibrariesInternal( self, idleOnly, currentTimeUsec, nextFireAtTime );

    // If all libraries are gone, notify caller
    if (!self->head && self->idleCallback)
        (*self->idleCallback)(self,self->idleCallbackData);

    Lock_Release( &self->liblock );
}

/*
    Timeout handler: unloads idle providers and libraries,
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

    if (mask & SELECTOR_TIMEOUT)
    {
        ProvMgr* self = (ProvMgr*)handler->data;
        const MI_Uint64   u64max = ~ MI_ULL(0);
        MI_Uint64   nextFireAtTime = u64max;

        /* Unload all idle providers */
        /* trace_UnloadingIdleProviders(); */

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

        return MI_TRUE;
    }

    if (mask & (SELECTOR_REMOVE | SELECTOR_DESTROY))
    {
        /* ignore it */
    }

    return MI_TRUE;
}

/*
**=============================================================================
**
** Public definitions
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
    if (!self || !providerDir)
        return MI_RESULT_INVALID_PARAMETER;

    memset(self, 0, sizeof(ProvMgr));

    Strlcpy(self->providerDir, providerDir, sizeof(self->providerDir)-1);

    self->idleTimeoutUsec = PROVMGR_IDLE_TIMEOUT_USEC;

    /* Add socket handler to catch timeout event */

    self->timeoutHandler.sock = INVALID_SOCK;
    self->timeoutHandler.data = self;
    self->timeoutHandler.callback = _TimeoutCallback;
    self->timeoutHandler.handlerName = MI_T("PROVMGR_TIMEOUT_MANAGER");
    self->idleCallback = idleCallback;
    self->idleCallbackData = idleCallbackData;
    self->selector = selector;

    Selector_AddHandler(selector, &self->timeoutHandler);

    self->ioThreadId = Thread_ID(); /* IO thread always initializes for Linux */
    Lock_Init( &self->liblock );

#ifndef DISABLE_INDICATION
    RequestHandler_Init(&g_requesthandler);
#endif

    return MI_RESULT_OK;
}

MI_Result ProvMgr_Destroy(
    ProvMgr* self)
{
    if (!self)
        return MI_RESULT_INVALID_PARAMETER;

#ifndef DISABLE_INDICATION
    RequestHandler_Finalize(&g_requesthandler);
#endif

    /* release opened libraries */
    _UnloadAllLibraries(self, MI_FALSE, 0, NULL);

    /* If local session is initialized then we need to clean-up */
    while (Atomic_Read(&self->localSessionInitialized) != 0)
    {
        if (Atomic_CompareAndSwap(&self->localSessionInitialized, 2, 1))
        {
            /* Initialized, so need to deinitialize */
            MI_Session_Close(&self->localSession, NULL, NULL);
            MI_Application_Close(&self->localApplication);
            self->localSessionInitialized = 0;
            /* Broadcast does a memory barrier so no need for assignment to be atomic */
            CondLock_Broadcast((ptrdiff_t) &self->localSession);
        }
        else if (self->localSessionInitialized == 1)
        {
            /* Initializing for some reason so wait for it to complete */
            ptrdiff_t init = self->localSessionInitialized;
            while (init == 1)
            {
                CondLock_Wait((ptrdiff_t)&self->localSession, &self->localSessionInitialized, init, CONDLOCK_DEFAULT_SPINCOUNT);
                init = self->localSessionInitialized;
            }
        }
    }

    memset(self, -1, sizeof(ProvMgr));

    return MI_RESULT_OK;
}

/*
    Routes incoming message to appropriate
    message handler based on message tag
*/
MI_Result MI_CALL ProvMgr_NewRequest(
    _In_ ProvMgr* self,
    _In_ const ProvRegEntry* proventry,
    _Inout_ InteractionOpenParams* params )
{
    Provider* prov = 0;
    MI_Result r = MI_RESULT_INVALID_PARAMETER;


    /* Check parameters */
    if( !self || !params || !params->msg || !params->interaction )
        return MI_RESULT_INVALID_PARAMETER;

    /* Dispatch the message */
    switch( params->msg->tag )
    {
        case GetInstanceReqTag:
        {
            r = _HandleGetInstanceReq(self, proventry, params, &prov);
            break;
        }
        case GetClassReqTag:
        {
            r = _HandleGetClassReq(self, proventry, params, &prov);
            break;
        }
        case CreateInstanceReqTag:
#ifndef DISABLE_SHELL
        case ShellCreateReqTag:
#endif
        {
            r = _HandleCreateInstanceReq(self, proventry, params, &prov);
            break;
        }
        case ModifyInstanceReqTag:
        {
            r = _HandleModifyInstanceReq(self, proventry, params, &prov);
            break;
        }
        case DeleteInstanceReqTag:
#ifndef DISABLE_SHELL
        case ShellDeleteReqTag:
#endif
        {
            r = _HandleDeleteInstanceReq(self, proventry, params, &prov);
            break;
        }
        case InvokeReqTag:
#ifndef DISABLE_SHELL
        case ShellSendReqTag:
        case ShellReceiveReqTag:
        case ShellSignalReqTag:
        case ShellConnectReqTag:
        case ShellReconnectReqTag:
        case ShellDisconnectReqTag:
        case ShellCommandReqTag:
#endif
        {
            r = _HandleInvokeReq(self, proventry, params, &prov);
            break;
        }
        case EnumerateInstancesReqTag:
        {
            r = _HandleEnumerateInstancesReq(self, proventry, params, &prov);
            break;
        }
        case AssociatorsOfReqTag:
        {
            r = _HandleAssociatorsOfReq(self, proventry, params, &prov);
            break;
        }
        case ReferencesOfReqTag:
        {
            r = _HandleReferencesOfReq(self, proventry, params, &prov);
            break;
        }
#ifndef DISABLE_INDICATION
        case SubscribeReqTag:
        {
            r = _HandleSubscribeReq(self, proventry, params, &prov);
            break;
        }
#endif
        default:
            trace_ProvMgr_NewRequest_UnsupportedMessage(
                params->msg, MessageName(params->msg->tag));
            break;
    }

    Provider_Release(prov); /* Releases hold from Provider_AddRef in _OpenProvider() */
    return r;
}

/*
 * Increments provider's ref-counter
 */
void Provider_Addref(Provider* provider)
{
    if (provider)
        Atomic_Inc(&provider->refCounter);
}

/*
 * Finalize provider before free memory
 */
_Use_decl_annotations_
void Provider_Finalize(Provider* provider)
{
    if (provider)
    {
#ifndef DISABLE_INDICATION
        DEBUG_ASSERT( provider->subMgr );
        SubMgr_Finalize( provider->subMgr );
#endif
    }
}

/*
 * Decrements provider's ref-counter and
 * marks provider as idle if ref-counter is 0 and
 * 'refuse-unload' was not called
 */
void Provider_Release(Provider* provider)
{
    if (provider && Atomic_Dec(&provider->refCounter) == 0)
    {
        if (!provider->refusedUnload)
        {
            /* Provider becomes idle */
            if (PAL_TRUE != PAL_Time(&provider->idleSince))
                provider->idleSince = ~ (MI_Uint64)0;

            /* Set timer if it's first idle provider */
            if (TIME_NEVER == provider->lib->provmgr->timeoutHandler.fireTimeoutAt)
            {
                if (PAL_TRUE == PAL_Time(&provider->lib->provmgr->timeoutHandler.fireTimeoutAt))
                {
                    provider->lib->provmgr->timeoutHandler.fireTimeoutAt += provider->lib->provmgr->idleTimeoutUsec;

                    /* wakeup main thread */
                    Selector_Wakeup(provider->lib->provmgr->selector, MI_TRUE);
                }
            }
        }
    }
}

void Provider_SetRefuseUnloadFlag(Provider* provider, MI_Boolean flag)
{
    provider->refusedUnload = flag;
}


MI_Result ProvMgr_GetLocalSesson(
    _Inout_ ProvMgr* self,
    _Out_ MI_Session *localSession)
{
#if defined(DISABLE_LOCALSESSION)
    MI_UNREFERENCED_PARAMETER(self);
    MI_UNREFERENCED_PARAMETER(localSession);

    return MI_RESULT_NOT_SUPPORTED;
#else /* defined(DISABLE_LOCALSESSION) */

    while (Atomic_Read(&self->localSessionInitialized) != 2)
    {
        if (Atomic_CompareAndSwap(&self->localSessionInitialized, 0, 1) == 0)
        {
            /* Need to initialize */
            MI_Result miResult;
            miResult = MI_Application_Initialize(0, MI_T("OMI Local Session"), NULL, &self->localApplication);
            if (miResult == MI_RESULT_OK)
            {
                miResult = MI_Application_NewSession(&self->localApplication, NULL, NULL, NULL, NULL, NULL, &self->localSession);
                if (miResult == MI_RESULT_OK)
                {
                    /* Succeeded, so mark as initialized */
                    *localSession = self->localSession;
                    self->localSessionInitialized = 2;
                }
                else
                {
                    /* Failed, so reset state */
                    MI_Application_Close(&self->localApplication);
                    self->localSessionInitialized = 0;
                }
            }
            else
            {
                /* Failed so reset state */
                self->localSessionInitialized = 0;
            }
            /* memory barrier as part of broadcast which is why state updates were not atomic */
            CondLock_Broadcast((ptrdiff_t) &self->localSession);

            return miResult;
        }
        else if (self->localSessionInitialized == 1)
        {
            /* Wait for the initialization on another thread to complete */
            ptrdiff_t init = self->localSessionInitialized;
            while (init == 1)
            {
                CondLock_Wait((ptrdiff_t)&self->localSession, &self->localSessionInitialized, init, CONDLOCK_DEFAULT_SPINCOUNT);
                init = self->localSessionInitialized;
            }
            /* Need to try another trip around the loop to make sure it is initialized this time around */
        }
    }

    *localSession = self->localSession;
    return MI_RESULT_OK;
#endif  /* defined(DISABLE_LOCALSESSION) */
}
