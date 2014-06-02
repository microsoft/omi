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

    /* Grow buffer if neceessary */
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
