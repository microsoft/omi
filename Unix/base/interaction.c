/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <base/interaction.h>

Interaction* Interaction_New(
    _In_ Batch *batch,
    _In_opt_ InteractionFT* ft,
    size_t structSize )
{
    Interaction* self;

    DEBUG_ASSERT( NULL != batch );

    /* Allocate heap space for Interaction */
    self = (Interaction*)Batch_Get(batch, structSize);

    if (!self)
        return NULL;

    /* Clear all fields */
    memset(self, 0, structSize);

    self->ft = ft;

    return self;
}

