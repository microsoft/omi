/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
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
** PtrArray
**
**     This type manages an array of pointers. PtrArray.data is the array of
**     pointers and PtrArray.size is the number of pointers in the array.
**     Functions are provided for prepending and appending pointers to the
**     array. The array of pointers is null terminated.
**
**==============================================================================
*/

typedef struct PtrArray
{
    void** data;
    MI_Uint32 size;
}
PtrArray;

#define PTRARRAY_INITIALIZER { NULL, 0 }

extern int Codec_PtrArray_Append(_In_ void *state, _Inout_ PtrArray* self, _In_ void* ptr);

extern int Codec_PtrArray_Append_Batch(_In_ void *mofbatch, _Inout_ PtrArray* self, _In_ void* ptr);

#ifdef __cplusplus
}
#endif

#endif /* _mof_ptrarray_h */
