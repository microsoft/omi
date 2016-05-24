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
#include "utility.h"
#include "types.h"
#include "ptrarray.h"

#define MIN_CAP_SIZE_BITS 3
#define MAX_CAP_SIZE_BITS 20
const MI_Uint32 MIN_CAP_SIZE = 1<<MIN_CAP_SIZE_BITS;
const MI_Uint32 MAX_CAP_SIZE = 1<<MAX_CAP_SIZE_BITS;

/* Improve the algorithm from O(N^2) to O (NlgN) */
/* Original cause out of memory issue */
size_t GetSize(MI_Uint32 oldsize)
{
#if 0
    return oldsize+1;
#else
    if(oldsize == 0) return MIN_CAP_SIZE;
    else if(oldsize < MIN_CAP_SIZE) return 0;
    else if(oldsize >= MAX_CAP_SIZE) return  oldsize+1;
    else
    {
        MI_Uint8 b = MIN_CAP_SIZE_BITS;
        MI_Uint32 f = MIN_CAP_SIZE;
        for(; b < MAX_CAP_SIZE_BITS; b++)
        {
            if (oldsize == f)
            {
                size_t newsize = oldsize;
                return newsize << 1;
            }
            else if (oldsize < f) return 0;
            f = f << 1;
        }
        return 0;
    }
#endif
}

/*=============================================================================
**
** Append Ptr, allocate memory from batch
**
=============================================================================*/
int Codec_PtrArray_Append_Batch(_In_ void *mofbatch, _Inout_ Codec_PtrArray* self, _In_ void* ptr)
{
    void * olddata;
    Batch * batch = (Batch *)mofbatch;
    size_t newsize;
    newsize = GetSize(self->size);
    if (newsize > 0)
    {
        /* Allocate memory */
        olddata = self->data;
        self->data = (void**)Batch_Get(batch, sizeof(void*) * (newsize));
        if (!self->data)
        {
            return -1;
        }
        memcpy(self->data, olddata, sizeof(void*) * self->size);
    }
    /* else the capacity of olddata is enough */
    self->data[self->size++] = ptr;
    return 0;
}

/*=============================================================================
**
** Append Ptr
**
=============================================================================*/
_Use_decl_annotations_
int Codec_PtrArray_Append(void * mofstate, Codec_PtrArray* self, void* ptr)
{
    MOF_State * state = (MOF_State *)mofstate;
    int c;
    if (!self || !ptr)
        return -1;
    c = Codec_PtrArray_Append_Batch(state->batch, self, ptr);
    if (c != 0)
    {
        yyerrorf(state->errhandler, ID_OUT_OF_MEMORY, "out of memory");
        return -1;
    }
    return c;
}
