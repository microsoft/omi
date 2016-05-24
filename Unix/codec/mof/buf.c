/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "buf.h"
#include <stdlib.h>
#include <pal/palcommon.h>

#ifdef _PREFAST_
# pragma prefast (push)
# pragma prefast (disable: 28252)
# pragma prefast (disable: 28253)
#endif

#include <string.h>

#ifdef _PREFAST_
# pragma prefast (pop)
#endif

#define BUF_MINIMUM_CAPACITY 4096

MI_Result Buf_Construct(
    _Out_ Buf* self,
    _Inout_ MI_Char* data,
    size_t capacity)
{
    if (!data && capacity > 0)
        return MI_RESULT_FAILED;

    self->data = data;
    self->size = 0;
    self->capacity = capacity;
    self->owner = 0;

    return MI_RESULT_OK;
}

void Buf_Destruct(
    _Inout_ Buf* self)
{
    if (self->owner)
        PAL_Free(self->data);
}

MI_Result Buf_Put(
    _Inout_ Buf* self,
    _In_reads_(size) const MI_Char* data,
    size_t size)
{
    /* If allocation is too small, then enlarge it */

    if (self->size + size > self->capacity)
    {
        MI_Char* p;

        /* Adjust capacity */

        if (self->capacity == 0)
            self->capacity = BUF_MINIMUM_CAPACITY;
        else
            self->capacity *= 2;

        /* Keep doubling the capacity until big enough */

        while (self->size + size > self->capacity)
            self->capacity *= 2;

        /* Reallocate the buffer to the new capacity */

        if (self->owner)
        {
            p = (MI_Char*)PAL_Realloc(
                self->data, 
                self->capacity * sizeof(MI_Char));
        }
        else
        {
            p = (MI_Char*)PAL_Malloc(self->capacity * sizeof(MI_Char));
        }

        if (!p)
            return MI_RESULT_FAILED;

        self->data = p;
        self->owner = 1;
    }

    /* Append new data to buffer */

    memcpy(
        self->data + self->size, 
        data, 
        size * sizeof(MI_Char));

    self->size += size;

    return MI_RESULT_OK;
}

MI_Result Buf_PutStr(
    _Inout_ Buf* self,
    _In_z_ const MI_Char* str)
{
#if (MI_CHAR_TYPE == 1)
    size_t len = strlen(str);
#else
    size_t len = wcslen(str);
#endif
    return Buf_Put(self, str, len);
}
