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

#define SELECTOR_ADD        (1 << 0)
#define SELECTOR_READ       (1 << 1)
#define SELECTOR_WRITE      (1 << 2)
#define SELECTOR_EXCEPTION  (1 << 3)
#define SELECTOR_TIMEOUT    (1 << 4)
#define SELECTOR_REMOVE     (1 << 5)
#define SELECTOR_DESTROY    (1 << 6)
#define SELECTOR_IGNORE_READ_OVERLOAD    (1 << 7)

/* This is a magic number used for designating a WSMAN Handler */
#define WSMAN_HANDLER 0x123468AC

typedef struct _Selector Selector;
typedef struct _Handler Handler;

struct _Handler
{
    Handler* next;                      // used in linked lists of Handlers
    Handler* prev;
    MI_Uint32 type;                     // type of child if this is nested within a child structure
    Sock sock;                          // socket used by this handler
    MI_Uint32 mask;                     // what types of events are handled
    int padding;                        // for 64-bit CPUs, to make stuff below align to 8-byte boundary
    /* time when selector gets 'timeout' event - typically Time_Now() + ttl-in-usec;
      '0' means 'ignore me' */
    MI_Uint64 fireTimeoutAt;
    MI_Boolean (*callback)(Selector*, Handler*, MI_Uint32 mask, MI_Uint64 currentTimeUsec);
    void (*destructor)(Handler*);       // if not NULL, call this before freeing a Handler
    void* data;
};

struct _Selector
{
    struct _SelectorRep* rep;
};

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
    MI_Sint64 timeoutUsec);

/* Informs selector's Run method that it should exit normaly.
    Funciton is safe for calling from signal hanlder */
MI_Result Selector_StopRunning(
    Selector* self);

/* Wakes up selector's thread 
    Typical usage is to recalculate timeouts on handlers
    when selector's Run is running in different thread */
MI_Result Selector_Wakeup(
    Selector* self);

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
    Informs selector that new Instance was created;
    Selector keeps track of number of Instances
    so it can implement back-pressure (primitive) by
    disabling read from oop and blocking other-thread providers
*/
void Selector_NewInstanceCreated(
    Selector* self,
    Message* msg);


/*
    Verifies if selector is in 'stressed' mode
    and too many instance are alive now
*/
MI_Boolean  Selector_IsStressed(
    Selector* self);


/*
    Sets flag 'allowEmptySelector' to allow 
    'run' call on empty selector
*/
void Selector_SetAllowEmptyFlag(
    Selector* self,
    MI_Boolean allowEmptySelector);

END_EXTERNC

#endif /* _omi_selector_h */
