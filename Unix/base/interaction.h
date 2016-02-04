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

#ifndef _Interaction_h
#define _Interaction_h

#include <base/messages.h>

BEGIN_EXTERNC

typedef struct _Interaction Interaction;

typedef struct _InteractionFT
{
    void (*Post)( _In_ Interaction* self, _In_ Message* msg);
    void (*PostControl)( _In_ Interaction* self, _In_ Message* msg);
    void (*Ack)( _In_ Interaction* self);
    void (*Cancel)( _In_ Interaction* self);
    void (*Close)( _In_ Interaction* self);
}
InteractionFT;

struct _Interaction
{
    InteractionFT * ft;
    Interaction *   other;
};

Interaction* Interaction_New(
    _In_ Batch *batch,
    _In_opt_ InteractionFT* ft,
    size_t structSize );

typedef struct _Strand Strand;

typedef struct _InteractionOpenParams
{
    Interaction*    interaction;
    void*           callbackData;   // Optional callbackData (usually the object being called back)
    Message*        msg;            // Optional initial message, if not NULL receiver SHOULD Ack when is ready
    Strand*         origin;         // Optional origin strand, used by strand to provide a Strand object that should be released (leave) once the interaction is open
} InteractionOpenParams;

MI_INLINE
void InteractionOpenParams_Init( _Out_ InteractionOpenParams* params )
{
    memset( params, 0, sizeof(InteractionOpenParams) );
}

// It should always succeed, return any error thru the interaction
typedef void (*OpenCallback)( _Inout_ InteractionOpenParams* params );

END_EXTERNC

#endif /* _Interaction_h */

