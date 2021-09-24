/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "mofcommon.h"
#include "buffer.h"

#define INITIAL_BUFFER_SIZE 256

/*=============================================================================
**
** Append data to buffer
**
=============================================================================*/
_Use_decl_annotations_
int Buffer_Append(void* mofstate, Buffer* self, const void* data , size_t size)
{
    size_t capacity;
    void * olddata;
    MOF_State * state = (MOF_State *)mofstate;
    if (!self || !data)
        return -1;

    olddata = self->data;
    capacity = self->size + size;

    /* Grow buffer if necessary */
    if (capacity > self->capacity)
    {
        size_t r = INITIAL_BUFFER_SIZE;

        while (r < capacity)
            r *= 2;

        self->data = Batch_Get(state->batch, r);

        if (!self->data)
            return -1;

        self->capacity = r;
    }

    /* Copy the old data */
    if (olddata != self->data)
        memcpy((char*)self->data, olddata, self->size);

    /* Copy the new data */
    memcpy((char*)self->data + self->size, data, size);
    self->size += size;

    return 0;
}
