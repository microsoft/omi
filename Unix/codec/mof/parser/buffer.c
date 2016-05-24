/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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

    /* Grow buffer if neceessary */
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
