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

#include "mgr.h"
#include <pal/strings.h>
#include <pal/format.h>
#include <indication/common/indilog.h>
#include <base/messages.h>
#include <provreg/provreg.h>

#define INDICATIONMGR_MAX_PAGES INFINITE

/* Create indication manager */
IndicationManager* IndiMgr_New(_In_ const IndicationHost* host)
{
    IndicationManager* mgr;
    Batch *batch = Batch_New(INDICATIONMGR_MAX_PAGES);
    DEBUG_ASSERT(host);
    trace_FunctionEntered(__FILE__, __LINE__);
    if (NULL == batch)
    {
        LOGD_BATCH_CREATE_OOM;
        return NULL;
    }
    mgr = (IndicationManager*)Batch_GetClear(batch, sizeof(IndicationManager));
    if (NULL == mgr)
    {
        LOGD_BATCH_OOM;
        Batch_Delete(batch);
        return NULL;
    }
    mgr->batch = batch;
    memcpy(&mgr->base, host, sizeof(IndicationHost));

    ReadWriteLock_Init(&mgr->filterLock);
    ReadWriteLock_Init(&mgr->listenerLock);
    ReadWriteLock_Init(&mgr->subscripLock);

    trace_IndiMgr_New( mgr );

    return mgr;
}

/* Create indication manager */
_Use_decl_annotations_
IndicationManager* IndiMgr_NewFromDisp(void* disp)
{
    IndicationHost host;
    if (IndicationHost_InitFromDisp(disp, &host) != 0)
    {
        trace_IndiMgr_NewFromDispFailed(disp);
        return NULL;
    }
    return IndiMgr_New(&host);
}

/* Delete indication manager */
_Use_decl_annotations_
int IndiMgr_Delete(IndicationManager* self)
{
    trace_IndiMgr_Delete(self);
    DEBUG_ASSERT(self);
    Batch_Delete(self->batch);
    return 0;
}

/* Shutdown indication manager */
_Use_decl_annotations_
int IndiMgr_Shutdown(IndicationManager* self)
{
    trace_IndiMgr_Shutdown(self);
    DEBUG_ASSERT(self);

    /* TODO: Cancel active subscriptions */
    /* Send subscription end to active clients */

    /* cleanup subscriptions */
    if (self->subscripList.head)
        CimBase_ReleaseList((CimBase*)self->subscripList.head);

    /* cleanup filters */
    if (self->filterList.head)
        CimBase_ReleaseList((CimBase*)self->filterList.head);

    /* cleanup listeners */
    if (self->listenerList.head)
        CimBase_ReleaseList((CimBase*)self->listenerList.head);

    return IndiMgr_Delete(self);
}

/*
**==============================================================================
**
** Common helper functions
**
**==============================================================================
*/

/* Get object from list */
/* Caller need to make sure the approriate lock was taken on the linked list */
CimBase* _List_FindObjectByID(
    _In_ CimBase* head,
    _In_ CimBase* tail,
    _In_opt_z_ const MI_Char* id)
{
    CimBase * target;
    if (id)
    {
        for (target = head; NULL != target; target = target->next)
        {
            const MI_Char* name = target->identifier;
            if (Tcscasecmp(name, id) == 0)
            {
                return target;
            }
        }
    }
    return NULL;
}

/* Add object to list */
int _List_AddObject(
    _In_ CimBase** pphead,
    _In_ CimBase** pptail,
    _In_ CimBase* obj,
    _In_ void* container)
{
    CimBase * o = _List_FindObjectByID(*pphead, *pptail, obj->identifier);
    if (NULL != o)
    {
        trace_IndiMgr_ObjectExists(tcs(obj->identifier));
        return -1;
    }

    List_Append((ListElem**)pphead,
        (ListElem**)pptail,
        (ListElem*)obj);

    /* Add reference */
    obj->_ft->addref(obj);

    /* Trigger OnAdd event */
    return obj->_ft->onadd(obj, container);
}

/* Remove object from list by ID */
int _List_RemoveObjectByID(
    _In_ CimBase** pphead,
    _In_ CimBase** pptail,
    _In_z_ const MI_Char* id,
    _In_ void* container)
{
    CimBase * o;
    DEBUG_ASSERT(id);
    o = _List_FindObjectByID(*pphead, *pptail, id);
    if (NULL == o)
    {
        trace_IndiMgr_CannotFindObject(tcs(id));
        return -1;
    }

    List_Remove((ListElem**)pphead,
        (ListElem**)pptail,
        (ListElem*)o);

    /* Release reference */
    o->_ft->release(o);

    /* Trigger OnRemove event */
    return o->_ft->onremove(o, container);
}

/* Remove object from list */
int _List_RemoveObject(
    _In_ CimBase** pphead,
    _In_ CimBase** pptail,
    _In_ CimBase* obj,
    _In_ void* container)
{
    return _List_RemoveObjectByID(pphead, pptail, obj->identifier, container);
}

/*
**==============================================================================
**
** Common helper functions with ReadWriteLock
**
**==============================================================================
*/
CimBase* _LockListAndFindObjectByID(
    _In_ CimBase* head,
    _In_ CimBase* tail,
    _In_opt_z_ const MI_Char* id,
    _In_ ReadWriteLock* lock)
{
    CimBase* obj;
    ReadWriteLock_AcquireRead(lock);
    obj = _List_FindObjectByID(head, tail, id);
    ReadWriteLock_ReleaseRead(lock);
    return obj;
}

/* Add object to list */
int _LockListAndAddObject(
    _In_ CimBase** pphead,
    _In_ CimBase** pptail,
    _In_ CimBase* obj,
    _In_ void* container,
    _In_ ReadWriteLock* lock)
{
    int r;
    ReadWriteLock_AcquireWrite(lock);
    r = _List_AddObject(pphead, pptail, obj, container);
    ReadWriteLock_ReleaseWrite(lock);
    return r;
}

/* Remove object from list by ID */
int _LockListAndRemoveObjectByID(
    _In_ CimBase** pphead,
    _In_ CimBase** pptail,
    _In_z_ const MI_Char* id,
    _In_ void* container,
    _In_ ReadWriteLock* lock)
{
    int r;
    ReadWriteLock_AcquireWrite(lock);
    r = _List_RemoveObjectByID(pphead, pptail, id, container);
    ReadWriteLock_ReleaseWrite(lock);
    return r;
}

/*
**==============================================================================
**
** Filter management
**
**==============================================================================
*/
/* Add filter to cache */
_Use_decl_annotations_
int IndiMgr_AddFilter(
    IndicationManager* self,
    FilterBase* filter)
{
    DEBUG_ASSERT(self);
    DEBUG_ASSERT(filter);
    trace_IndiMgr_AddFilter(self, filter);

    /* Add filter to list */
    return _LockListAndAddObject(
        (CimBase**)&self->filterList.head,
        (CimBase**)&self->filterList.tail,
        (CimBase*)filter,
        self,
        &self->filterLock);
}

/* Remove filter from cache */
_Use_decl_annotations_
int IndiMgr_RemoveFilter(
    IndicationManager* self,
    FilterBase* filter)
{
    DEBUG_ASSERT(self);
    DEBUG_ASSERT(filter);
    trace_IndiMgr_RemoveFilter(self, filter);
    if (filter->base._container != self)
    {
        trace_IndiMgr_FilterNotRemoved(filter, self);
        return -1;
    }

    return IndiMgr_RemoveFilterByName(self, filter->base.identifier);
}

/* Remove filter from cache by name */
_Use_decl_annotations_
int IndiMgr_RemoveFilterByName(
    IndicationManager* self,
    const MI_Char* name)
{
    DEBUG_ASSERT(self);
    DEBUG_ASSERT(name);
    return _LockListAndRemoveObjectByID(
        (CimBase**)&self->filterList.head,
        (CimBase**)&self->filterList.tail,
        name,
        self,
        &self->filterLock);
}

/* Find filter from cache, name (case insenstive) is the unique identifier of filter */
_Use_decl_annotations_
FilterBase* IndiMgr_FindFilterByName(
    IndicationManager* self,
    const MI_Char *name)
{
    DEBUG_ASSERT(self);
    DEBUG_ASSERT(name);

    return (FilterBase*)_LockListAndFindObjectByID(
        (CimBase*)self->filterList.head,
        (CimBase*)self->filterList.tail,
        name,
        &self->filterLock);
}


/*
**==============================================================================
**
** Listener management
**
**==============================================================================
*/

/* Add listener to cache */
_Use_decl_annotations_
int IndiMgr_AddListener(
    IndicationManager* self,
    Listener* listener)
{
    DEBUG_ASSERT(self);
    DEBUG_ASSERT(listener);
    trace_IndiMgr_AddListener(self, listener);

    /* Add listener to list */
    return _LockListAndAddObject(
        (CimBase**)&self->listenerList.head,
        (CimBase**)&self->listenerList.tail,
        (CimBase*)listener,
        self,
        &self->listenerLock);
}

/* Remove listener from cache */
_Use_decl_annotations_
int IndiMgr_RemoveListener(
    IndicationManager* self,
    Listener* listener)
{
    DEBUG_ASSERT(self);
    DEBUG_ASSERT(listener);
    trace_IndiMgr_RemoveListener(self, listener);
    if (listener->base._container != self)
    {
        trace_IndiMgr_ListenerNotRemoved(listener, self);
        return -1;
    }
    return IndiMgr_RemoveListenerByName(self, listener->base.identifier);
}

/* Remove Listener from cache by name */
_Use_decl_annotations_
int IndiMgr_RemoveListenerByName(
    IndicationManager* self,
    const MI_Char* name)
{
    DEBUG_ASSERT(self);
    DEBUG_ASSERT(name);
    return _LockListAndRemoveObjectByID(
        (CimBase**)&self->listenerList.head,
        (CimBase**)&self->listenerList.tail,
        name,
        self,
        &self->listenerLock);
}

/* Find Listener from cache */
_Use_decl_annotations_
Listener* IndiMgr_FindListenerByName(
    IndicationManager* self,
    const MI_Char *name)
{
    DEBUG_ASSERT(self);
    DEBUG_ASSERT(name);

    return (Listener*)_LockListAndFindObjectByID(
        (CimBase*)self->listenerList.head,
        (CimBase*)self->listenerList.tail,
        name,
        &self->listenerLock);
}

/*
**==============================================================================
**
** Subscriptions management
**
**==============================================================================
*/
/* Add subscription to cache */
/* Both filter and listener has to be present in cache already */
_Use_decl_annotations_
int IndiMgr_AddSubscription(
    IndicationManager* self,
    Subscription* subscrip)
{
    DEBUG_ASSERT(self);
    DEBUG_ASSERT(subscrip);
    trace_IndiMgr_AddSubscription(self, subscrip);

    /* Check the subscriptionID */
    DEBUG_ASSERT(subscrip->subscriptionID > 0);

    /* Add listener to list */
    return _LockListAndAddObject(
        (CimBase**)&self->subscripList.head,
        (CimBase**)&self->subscripList.tail,
        (CimBase*)subscrip,
        self,
        &self->subscripLock);
}

/* Remove subscription from cache */
_Use_decl_annotations_
int IndiMgr_RemoveSubscription(
    IndicationManager* self,
    Subscription* subscrip)
{
    DEBUG_ASSERT(self);
    DEBUG_ASSERT(subscrip);
    trace_IndiMgr_RemoveSubscription(self, subscrip);
    if (subscrip->base._container != self)
    {
        trace_IndiMgr_SubscriptionNotRemoved(subscrip, self);
        return -1;
    }
    return IndiMgr_RemoveSubscriptionByName(self, subscrip->base.identifier);
}

/* Remove Subscription from cache by name */
_Use_decl_annotations_
int IndiMgr_RemoveSubscriptionByName(
    IndicationManager* self,
    const MI_Char* name)
{
    DEBUG_ASSERT(self);
    DEBUG_ASSERT(name);

    return _LockListAndRemoveObjectByID(
        (CimBase**)&self->subscripList.head,
        (CimBase**)&self->subscripList.tail,
        name,
        self,
        &self->subscripLock);
}

/* Find subscription from cache */
_Use_decl_annotations_
Subscription* IndiMgr_FindSubscriptionByName(
    IndicationManager* self,
    const MI_Char *name)
{
    DEBUG_ASSERT(self);
    DEBUG_ASSERT(name);

    return (Subscription*)_LockListAndFindObjectByID(
        (CimBase*)self->subscripList.head,
        (CimBase*)self->subscripList.tail,
        name,
        &self->subscripLock);
}

