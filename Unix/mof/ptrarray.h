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

typedef struct PtrArray
{
    void** data;
    MI_Uint32 size;
}
PtrArray;

#define PTRARRAY_INITIALIZER { NULL, 0 }

extern int PtrArray_Append(PtrArray* self, void* ptr);

extern int PtrArray_Prepend(PtrArray* self, void* ptr);

#endif /* _mof_ptrarray_h */
