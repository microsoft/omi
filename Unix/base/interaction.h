/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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

