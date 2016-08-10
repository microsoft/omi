/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_base_ptrarray_h
#define _omi_base_ptrarray_h

#include <stddef.h>
#include <MI.h>
#include <common.h>

#if defined(__cplusplus)
extern "C"
{
#endif

typedef struct _PtrArray
{
    /* Array of poitners */
    void** data;

    /* Current size of this array */
    size_t size;

    /* Current capacity (will double when exhausted) */
    size_t capacity;

    /* Destroys individual items upon destruction (may be null) */
    void (MI_MAIN_CALL *destructor)(void*);
}
PtrArray;

int PtrArray_Construct(
    PtrArray* self,
    size_t capacity,
    void (MI_MAIN_CALL *destructor)(void*));

void PtrArray_Destruct(
    PtrArray* self);

int PtrArray_Append(
    _Inout_ PtrArray* self, 
    void* element);

#if defined(__cplusplus)
}
#endif

#endif /* _omi_base_ptrarray_h */
