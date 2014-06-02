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

#ifndef _indication_indimgr_classlist_h
#define _indication_indimgr_classlist_h

#include <common.h>
#include <base/batch.h>
#include <provreg/provreg.h>
#include <indication/common/indicommon.h>
#include "filter.h"

BEGIN_EXTERNC

/*
**==============================================================================
**
** Defines subscribe status
** 
**==============================================================================
*/
typedef enum _SubscribeStatus
{
    SUBSCRIBE_INITED = 0,
    SUBSCRIBE_SUB_STARTED = 1,
    SUBSCRIBE_SUB_SUBSCRIBED = 2,
    SUBSCRIBE_SUB_FAILED = 3,
    SUBSCRIBE_SUB_CANCELLED = 4    /* Was succeeded before unsubscribe/cancelled */
}SubscribeStatus;

const MI_Char* SubscribeStatusName(SubscribeStatus status);

/*
**==============================================================================
**
** Defines indication class entry type
** 
**==============================================================================
*/
typedef struct _IndicationClassEntry
{
    struct _IndicationClassEntry* next;
    struct _IndicationClassEntry* prev;
    const ProvRegEntry* regentry;       /* ProvRegEntry of a class under specific namespace */
    MI_Uint64 subid;                    /* Subscription id */
    void *container;                    /* Container of this class entry */
    SubscribeStatus status;             /* Status of subscription */
    MI_Result subresult;                /* Result code of subscribe call */
}IndicationClassEntry;

/*
**==============================================================================
**
** Defines indication class list, holds a list of target indication class
** associated with one filter object;
** 
** Upon namespaces set to filter object, target indication classes will be
** discovered and added to this list;
**
** Upon an indication filter collection object been created; or filter was
** added to/removed from collection object, the list will be created and
** modified accordingly;
**
** Upon subscription was created on the filterbase object, indication
** manager sends subscribe request to all target classes;
**
** Upon subscription was cancelled, indication manager sends unsubscribe
** request to all active classes (which still be actively subscribed);
**
**==============================================================================
*/
typedef struct _IndicationClassList
{
    IndicationClassEntry *head;
    IndicationClassEntry *tail;
    Batch *batch;                       /* Batch allocator */
    ProvReg *provreg;                   /* Provider registration cache */
    MI_Uint32 totalclass;               /* Total class count */
    SubscriptionTargetType targetType;  /* Subscription target class type */
}
IndicationClassList;

/* Creates a classlist object */
IndicationClassList* IndicationClassList_NewByFilter(
    _In_ ProvReg *provreg,
    _In_ Filter* filter);

/* Creates a class entry object */
IndicationClassEntry* IndicationClassList_AddEntry(
    _Inout_ IndicationClassList* list,
    _In_ const ProvRegEntry* regentry);

/* Delete a classlist object */
void IndicationClassList_Delete(
    _Inout_ IndicationClassList* self);

END_EXTERNC

#endif /* _indication_indimgr_classlist_h */

