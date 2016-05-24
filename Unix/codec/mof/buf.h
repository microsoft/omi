/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _buf_h
#define _buf_h

#include <MI.h>

typedef struct Buf
{
    /* Pointer to data buffer */
    MI_Char* data;

    /* Current size of buffer */
    size_t size;

    /* Current capacity of buffer */
    size_t capacity;

    /* Non-zero if Buf instance owns the 'data' buffer */
    int owner;
}
Buf;

MI_Result Buf_Construct(
    _Out_ Buf* self,
    _Inout_ MI_Char* data,
    size_t capacity);

void Buf_Destruct(
    _Inout_ Buf* self);

MI_Result Buf_Put(
    _Inout_ Buf* self,
    _In_reads_(size) const MI_Char* data,
    size_t size);

MI_INLINE MI_Result Buf_PutC(
    _Inout_ Buf* self,
    const MI_Char c)
{
    return Buf_Put(self, &c, 1);
}

MI_Result Buf_PutStr(
    _Inout_ Buf* self,
    _In_z_ const MI_Char* str);

#endif /* _buf_h */
