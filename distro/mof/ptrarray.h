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

#ifndef _Ptrarray_h
#define _Ptrarray_h

#ifndef MI_CHAR_TYPE
# define MI_CHAR_TYPE 1
#endif

#include <MI.h>
#include <stddef.h>

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

typedef struct _MofPtrArray
{
    void** data;
    MI_Uint32 size;
}
MofPtrArray;

extern int MofPtrArray_Append(MofPtrArray* self, void* ptr);

extern int MofPtrArray_Prepend(MofPtrArray* self, void* ptr);

#define PTRARRAY_INITIALIZER { NULL, 0 }

#endif /* _Ptrarray_h */
