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

#ifndef _omi_multiplex_h
#define _omi_multiplex_h

#include <common.h>
#include <base/base.h>
#include <base/Strand.h>

/*
**==============================================================================
**
** Multiplex
**
**     This file implements the germ of future multiplexer
**
**         (to be completed with flow control, etc.)
**
**==============================================================================
*/

typedef void (*OnCloseCallback)(
    _In_        void*           object);   // object being closed (not used yet)

typedef struct _MuxIn
{
    OpenCallback    callback;
    void*           callbackData;
    OnCloseCallback onCloseCallback;
    MakeResultMessageCallback makeResultMessageCallback;
    // nothing else for now
}
MuxIn;

MI_INLINE
MI_Result MuxIn_Init(
    _Inout_     MuxIn*          self,
    _In_        OpenCallback    callback,
    _In_        void*           callbackData,
    _In_opt_    OnCloseCallback onCloseCallback,
    _In_ MakeResultMessageCallback makeResultMessageCallback)

{
    self->callback = callback;
    self->callbackData = callbackData;
    self->onCloseCallback = onCloseCallback;
    self->makeResultMessageCallback = makeResultMessageCallback;

    return MI_RESULT_OK;
}

// Called to handle the opening of a new connection
// (and correspondinly opening new Interaction Interface)
void MuxIn_Open(  _Inout_ InteractionOpenParams* params );

#endif /* _omi_multiplex_h */

