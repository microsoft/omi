/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _mof_buffer_h
#define _mof_buffer_h

#include <stdlib.h>
#include <common/common.h>
#include <base/batch.h>

typedef struct Buffer
{
    _Field_size_bytes_(capacity)
    void* data;
    _Field_range_(0, capacity) 
    size_t size;
    size_t capacity;
}
Buffer;

#define BUFFER_INITIALIZER { NULL, 0, 0 }

extern int Buffer_Append(_In_ void* mofstate, _Inout_ Buffer* self, _In_ _Readable_bytes_(size) const void* data , _In_ size_t size);

#endif /* _mof_buffer_h */
