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

#ifndef _indication_indimgr_host_h
#define _indication_indimgr_mgr_h

#include <common.h>
#include <base/list.h>
#include <base/messages.h>
#include <pal/lock.h>
#include "filter.h"
#include "filtercol.h"
#include "listener.h"
#include "subscrip.h"
#include "host.h"

BEGIN_EXTERNC

/*
**==============================================================================
**
** Represents a list of Listener objects
**
**==============================================================================
*/
typedef struct _ListenerList
{
    Listener *head;
    Listener *tail;
}ListenerList;

/*
**==============================================================================
**
** Represents a list of subscription objects
**
**==============================================================================
*/
typedef struct _SubscriptionList
{
    Subscription *head;
    Subscription *tail;
}SubscriptionList;


/*
**==============================================================================
**
** Represents a indication manager object
**
**==============================================================================
*/
typedef struct _IndicationManager
{
    IndicationHost base; /* Host object */

    Batch* batch; /* batch allocator */

    ReadWriteLock filterLock; /* readwrite lock for filter list */
    FilterList filterList; /* filter container */
    ReadWriteLock listenerLock; /* readwrite lock for listener list */
    ListenerList listenerList; /* listener container */
    ReadWriteLock subscripLock; /* readwrite lock for subscription list */
    SubscriptionList subscripList; /* subscription container */
}
IndicationManager;

/* Create indication manager */
IndicationManager* IndiMgr_NewFromDisp(_In_ void* disp);

/* Create indication manager */
IndicationManager* IndiMgr_New(_In_ const IndicationHost* host);

/* Delete indication manager */
int IndiMgr_Delete(_Inout_ IndicationManager* self);

/* Shutdown indication manager */
int IndiMgr_Shutdown(_Inout_ IndicationManager* self);

/* Add filter to cache */
int IndiMgr_AddFilter(
    _In_ IndicationManager* self,
    _In_ FilterBase* filter);

/* Remove filter from cache */
int IndiMgr_RemoveFilter(
    _In_ IndicationManager* self,
    _In_ FilterBase* filter);

/* Remove filter from cache by name */
int IndiMgr_RemoveFilterByName(
    _In_ IndicationManager* self,
    _In_z_ const MI_Char* name);

/* Find filter from cache */
FilterBase* IndiMgr_FindFilterByName(
    _In_ IndicationManager* self,
    _In_z_ const MI_Char *name);


/* Find Listener from cache */
Listener* IndiMgr_FindListenerByName(
    _In_ IndicationManager* self,
    _In_z_ const MI_Char *name);

/* Add listener to cache */
int IndiMgr_AddListener(
    _In_ IndicationManager* self,
    _In_ Listener* listener);

/* Remove listener from cache */
int IndiMgr_RemoveListener(
    _In_ IndicationManager* self,
    _In_ Listener* listener);

/* Remove Listener from cache by name */
int IndiMgr_RemoveListenerByName(
    _In_ IndicationManager* self,
    _In_z_ const MI_Char* name);


/* Find subscription from cache */
Subscription* IndiMgr_FindSubscriptionByName(
    _In_ IndicationManager* self,
    _In_z_ const MI_Char *name);

/* Add subscription to cache */
/* Both filter and listener has to be present in cache already */
int IndiMgr_AddSubscription(
    _In_ IndicationManager* self,
    _In_ Subscription* subscrip);

/* Remove subscription from cache */
int IndiMgr_RemoveSubscription(
    _In_ IndicationManager* self,
    _In_ Subscription* subscrip);

/* Remove subscription from cache by name */
int IndiMgr_RemoveSubscriptionByName(
    _In_ IndicationManager* self,
    _In_z_ const MI_Char* name);


/* Handle subscribe request */
void IndiMgr_HandleSubscribeReq(
    _Inout_ InteractionOpenParams* params );

END_EXTERNC

#endif /* _indication_indimgr_mgr_h */
