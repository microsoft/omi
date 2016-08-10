/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <indication/common/indilog.h>
#include <disp/disp.h>
#include "subscrip.h"
#include "mgr.h"

const MI_Uint32 g_SubscriptionMagic = 0xF11EE2FE;

static void _Subscription_SetLastError(
    _In_opt_ void* context,
    _In_ MI_Instance* error,
    MI_Result result)
{
    Subscription* sub = (Subscription*)context;
    MI_UNREFERENCED_PARAMETER(result);
    DEBUG_ASSERT(sub);
    sub->lastError = error;
    sub->lastErrorCode = result;
}

/* Check if given object is a Subscription */
MI_Boolean CimBase_IsSubscription(_In_ CimBase* self)
{
    return (self->_magic == g_SubscriptionMagic) ? MI_TRUE : MI_FALSE;
}

void Subscription_Finalize(_Inout_ CimBase *self)
{
    Subscription* sub;
    trace_Subscription_Finalize(self);
    DEBUG_ASSERT(self);

    sub = (Subscription*)self;
    DEBUG_ASSERT(sub->filter);
    DEBUG_ASSERT(sub->listener);
    /* release reference to filter */
    FilterBase_Release(sub->filter);
    /* release reference to listener */
    Listener_Release(sub->listener);
    /* cleanup class cache */
    if (sub->classlist)
    {
        IndicationClassList_Delete(sub->classlist);
        sub->classlist = NULL;
    }
}

/* Create identifier of current object */
MI_Char* CreateSubscriptionIdentifier(_In_ CimBase *self)
{
    Subscription *sub;
    DEBUG_ASSERT(self);
    if (self->_magic != g_SubscriptionMagic)
    {
        trace_ObjectIsnotAValidSubscr(self);
        return NULL;
    }
    sub = (Subscription*) self;
    return GetID((MI_Uint32)sub->subscriptionID, TEMP_SUBSCRIPTION_ID_PREFIX, self->batch);;
}

/* Add to container callback */
int Subscription_OnAdd(_Inout_ CimBase *self, _In_ void* container)
{
    Subscription* sub;
    int r;

    trace_Subscription_OnAdd(self, container);
    DEBUG_ASSERT(self);

    if (self->_magic != g_SubscriptionMagic)
    {
        trace_Subscription_OnAdd_NotValidSubscr(self);
        return -1;
    }
    sub = (Subscription*) self;

    r = CimBase_OnAdd(self, container);
    if (r != 0)
    {
        trace_Subscription_OnAdd_CimBaseOnAddFailed(r);
        return r;
    }

    switch(sub->persistType)
    {
    case SUBSCRIP_PER_TEMPORARY:
        /* Add temp filter and handler to indication manager */
        {
            IndicationManager* mgr = (IndicationManager*)container;
            if (sub->filter->type == FILTER_UNARY_TEMP)
            {
                r = IndiMgr_AddFilter(mgr, sub->filter);
                if (r != 0)
                {
                    trace_Subscription_OnAdd_FailedAddFilter(r);
                    return -1;
                }
                sub->filter->errhandler.context = (void*)sub;
                sub->filter->errhandler.setlasterror = _Subscription_SetLastError;
            }
            r = IndiMgr_AddListener(mgr, sub->listener);
            if (r != 0)
            {
                trace_Subscription_OnAdd_FailedAddListener(r);
                return -1;
            }
        }
        /* Discover target class(es) based on filter */
        {
            IndicationManager* mgr = (IndicationManager*)container;
            ProvReg* provreg = IndicationHost_GetProvReg(&mgr->base);
            if (!provreg)
            {
                trace_Subscription_OnAdd_ProvRegIsNull();
                return -1;
            }
            else
            {
                sub->classlist = IndicationClassList_NewByFilter(provreg, (Filter*)sub->filter);
                if (NULL == sub->classlist)
                {
                    trace_Subscription_OnAdd_Failed();
                    return -1;
                }
            }
        }
        break;
    default:
        break;
    }
    trace_Subscription_OnAdd_Success(self, container);

    return r;
}

/* Remove from container callback */
int Subscription_OnRemove(_Inout_ CimBase *self, _In_ void* container)
{
    Subscription* sub;
    int r;

    trace_Subscription_OnRemove(self, container);
    DEBUG_ASSERT(self);

    if (self->_magic != g_SubscriptionMagic)
    {
        trace_Subscription_OnRemove_NotValidSubscr(self);
        return -1;
    }
    sub = (Subscription*) self;
    r = CimBase_OnRemove(self, container);
    if (r != 0)
    {
        trace_Subscription_OnRemove_RemoveFailed(self, container);
    }
    switch(sub->persistType)
    {
    case SUBSCRIP_PER_TEMPORARY:
        /* Remove temp filter and handler to indication manager */
        {
            IndicationManager* mgr = (IndicationManager*)container;
            if (sub->filter->type == FILTER_UNARY_TEMP)
            {
                r = IndiMgr_RemoveFilter(mgr, sub->filter);
                if (r != 0)
                {
                    trace_Subscription_OnRemove_RemoveFilterFailed(r);
                    return r;
                }
            }
            r = IndiMgr_RemoveListener(mgr, sub->listener);
        }
        break;
    default:
        break;
    }

    /* classlist is cleaned up in Subscription_Finalize */

    trace_Subscription_OnRemove_Result(self, container, r);
    return r;
}

CimBaseFT g_subscriptionft =
{
    CimBase_AddRef,
    CimBase_Release,
    Subscription_Finalize,
    Subscription_OnAdd,
    Subscription_OnRemove,
    CreateSubscriptionIdentifier,
};

/* Creates a subscription object */
/* Subscription object holds reference to both filter and listener upon succeed */
Subscription* Subscription_New(_In_ FilterBase *filter, _In_ Listener* listener)
{
    Subscription * sub = NULL;
    DEBUG_ASSERT(filter);
    DEBUG_ASSERT(listener);
    sub = (Subscription*)CimBase_Create(sizeof(Subscription));
    if (NULL == sub)
    {
        LOGD_BATCH_OOM;
        return NULL;
    }

    /* TODO: subType based on filter type */
    sub->persistType = SUBSCRIP_PER_TEMPORARY;
    CimBase_Set_Magic(&sub->base, g_SubscriptionMagic);
    CimBase_Set_FT(&sub->base, &g_subscriptionft);

    /* Hold one reference to listener */
    Listener_AddRef(listener);
    sub->listener = listener;

    /* Hold one reference to filter */
    FilterBase_AddRef(filter);
    sub->filter = filter;

    Subscription_AddRef(sub);
    return sub;
}

/* Add a reference to a subscription object */
int Subscription_AddRef(_Inout_ Subscription* self)
{
    DEBUG_ASSERT(self);
    return self->base._ft->addref((CimBase*)self);
}

/* Release a reference to a subscription object */
int Subscription_Release(_Inout_ Subscription* self)
{
    DEBUG_ASSERT(self);
    return self->base._ft->release((CimBase*)self);
}

/* Get reference count */
int Subscription_GetRefcount(_In_ Subscription* self)
{
    DEBUG_ASSERT(self);
    return CimBase_GetRefcount((CimBase*)self);
}

