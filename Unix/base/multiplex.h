/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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

