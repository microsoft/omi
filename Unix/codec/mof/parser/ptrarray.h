/*
   PowerShell Desired State Configuration for Linux

   Copyright (c) Microsoft Corporation

   All rights reserved. 

   MIT License

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _mof_ptrarray_h
#define _mof_ptrarray_h

//#ifndef MI_CHAR_TYPE
//# define MI_CHAR_TYPE 2
//#endif

#include <MI.h>
#include <stddef.h>
#include <base/batch.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
**==============================================================================
**
** Codec_PtrArray
**
**     This type manages an array of pointers. Codec_PtrArray.data is the array of
**     pointers and Codec_PtrArray.size is the number of pointers in the array.
**     Functions are provided for prepending and appending pointers to the
**     array. The array of pointers is null terminated.
**
**==============================================================================
*/

typedef struct Codec_PtrArray
{
    void** data;
    MI_Uint32 size;
}
Codec_PtrArray;

#define PTRARRAY_INITIALIZER { NULL, 0 }

extern int Codec_PtrArray_Append(_In_ void *state, _Inout_ Codec_PtrArray* self, _In_ void* ptr);

extern int Codec_PtrArray_Append_Batch(_In_ void *mofbatch, _Inout_ Codec_PtrArray* self, _In_ void* ptr);

#ifdef __cplusplus
}
#endif

#endif /* _mof_ptrarray_h */
