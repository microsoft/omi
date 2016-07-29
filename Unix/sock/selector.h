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

#ifndef _omi_selector_h
#define _omi_selector_h

#include "config.h"
#include <common.h>
#include "sock.h"
#include <base/list.h>
#include <base/messages.h>

BEGIN_EXTERNC

#define SELECTOR_ADD                    0x1
#define SELECTOR_READ                   0x2
#define SELECTOR_WRITE                  0x4
#define SELECTOR_EXCEPTION              0x8
#define SELECTOR_TIMEOUT                0x10
#define SELECTOR_REMOVE                 0x20
#define SELECTOR_DESTROY                0x40

typedef struct _Selector Selector;
typedef struct _Handler Handler;

struct _Handler
{
    Handler* next;
    Handler* prev;
    Sock sock;
    MI_Boolean isFromBinary;
    MI_Uint32 mask;
    /* time when selector gets 'timeout' event - typically PAL_Time() + ttl-in-usec;
      '0' means 'ignore me' */
    MI_Uint64 fireTimeoutAt;  
    MI_Boolean (*callback)(Selector*, Handler*, MI_Uint32 mask, MI_Uint64 currentTimeUsec);
    void* data;
};

struct _Selector
{
    struct _SelectorRep* rep;
};

extern MI_Boolean ChangeProtocolFlag;
extern MI_Boolean CPFlagHasChanged;
extern pthread_mutex_t ChangeProtocolMutex;
extern pthread_mutex_t ChangeProtocolMutexIsInitialized;

typedef void (*Selector_NotificationCallback)(void* self, Message* message);

MI_Result Selector_Init(
    Selector* self);

void Selector_Destroy(
    Selector* self);

MI_Result Selector_AddHandler(
    Selector* self,
    Handler* handler);

MI_Result Selector_RemoveHandler(
    Selector* self,
    Handler* handler);

/* Used for quick shutdown procedure */
MI_Result Selector_RemoveAllHandlers(
    Selector* self);

MI_Result Selector_ContainsHandler(
    Selector* self,
    Handler* handler);

/* Runs socket processing loop;
    Parameters:
    self - selector
    timeoutUsec - time to run 
    
    Retunrs:
    OK - was stopped by StopRunning call
    FAILED - system call 'select' failed or no more sockets to monitor
    TIMEOUT - timeout reached 
*/
MI_Result Selector_Run(
    Selector* self,
    MI_Uint64 timeoutUsec,
    MI_Boolean noReadsMode );

int Selector_IsSelectorThread(Selector* self, ThreadID *id);

/* Informs selector's Run method that it should exit normaly.
    Funciton is safe for calling from signal hanlder */
MI_Result Selector_StopRunning(
    Selector* self);
MI_Result Selector_StopRunningNoReadsMode(
    Selector* self);

/* Wakes up selector's thread 
    Typical usage is to recalculate timeouts on handlers
    when selector's Run is running in different thread */
MI_Result Selector_Wakeup(
    _In_    Selector*   self,
            MI_Boolean  retryDispatching );

/* 
    * This function guaranties that callback is called in 'Run'/'IO' thread context,
    * so no locking is required for accessing sokcet objects, updating buffers etc
*/
MI_Result Selector_CallInIOThread(
    Selector* self,
    Selector_NotificationCallback  callback,
    void* callback_self,
    Message* message);

/*
    Sets flag 'allowEmptySelector' to allow 
    'run' call on empty selector
*/
void Selector_SetAllowEmptyFlag(
    Selector* self,
    MI_Boolean allowEmptySelector);

END_EXTERNC

#endif /* _omi_selector_h */
