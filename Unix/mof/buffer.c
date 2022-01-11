/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <string.h>
#include <stdlib.h>
#include "buffer.h"
#include "heap.h"
#include "state.h"

#if 0 /* ATTN:REMOVE */
int Buffer_Init(Buffer* self, size_t capacity)
{
    size_t r = 16;

    while (r < capacity)
        r *= 2;

    if (!(self->data = (char*)MOF_Malloc(&state.heap, r)))
        return -1;

    self->size = 0;
    self->capacity = r;

    return 0;
}
#endif

int Buffer_Append(Buffer* self, const void* data , size_t size)
{
    size_t capacity;

    if (!self || !data)
        return -1;

    capacity = self->size + size;

    /* Grow buffer if necessary */
    if (capacity > self->capacity)
    {
        size_t r = 16;

        while (r < capacity)
            r *= 2;

        self->data = (char*)MOF_Realloc(&state.heap, self->data, r);

        if (!self->data)
            return -1;

        self->capacity = r;
    }

    /* Copy the data */
    memcpy((char*)self->data + self->size, data, size);
    self->size += size;

    return 0;
}
