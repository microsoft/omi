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

#ifndef _provmgr_h
#define _provmgr_h

#include <common.h>
#include <base/base.h>
#include <base/messages.h>
#include <sock/selector.h>

BEGIN_EXTERNC

typedef struct _ProvMgr     ProvMgr;

/*
    Callback to notify that prov-mgr unloaded all libraries
*/
typedef void (*ProvMgrCallbackOnIdle)(
    ProvMgr* mgr,
    void* callbackData);

struct _ProvMgr
{
    char providerDir[MAX_PATH_SIZE];

    /* Linked list of loaded providers */
    struct _Library* head;
    struct _Library* tail;

    /* timer notification */
    Handler     timeoutHandler;
    MI_Uint64   idleTimeoutUsec;

    /* idle notifications */
    ProvMgrCallbackOnIdle   idleCallback;
    void*                   idleCallbackData;

    /* selector (for timeouts support) */
    Selector* selector;
};

MI_Result ProvMgr_Init(
    ProvMgr* self,
    Selector* selector,
    ProvMgrCallbackOnIdle idleCallback,
    void* idleCallbackData,
    const char* providerDir);

MI_Result ProvMgr_Destroy(
    ProvMgr* self);

MI_Result ProvMgr_PostMessage(
    ProvMgr* self, 
    const char* libraryName,
    Message* msg);

/* MI_ServerFT is preceded directly by one of these. Providers may
 * inerally case backwards to find this structure but they should verify
 * the magic number.
 */
typedef struct _ProvMgrFT
{
    MI_Uint32 magic;
    void* (*FindSymbol)(const char* name);
}
ProvMgrFT;

#define PROVMGRFT_MAGIC 0xF19768D7

/* 
    Provider access
*/
typedef struct _Provider    Provider;

/*
    Adding reference to the provider:
    used by context functions
*/
void Provider_Addref(Provider* provider);

/*
    Decrementing provider's reference
    so prov mgr knows when provider becomes idle
*/
void Provider_Release(Provider* provider);

/*
    Sets 'refuse-unload' provider option
*/
void Provider_SetRefuseUnloadFlag(Provider* provider, MI_Boolean flag);

/*
    Informs system that new instance was created 
*/
void Provider_NewInstanceCreated(
    Provider* provider,
    Message* msg);

END_EXTERNC

#endif /* _provmgr_h */
