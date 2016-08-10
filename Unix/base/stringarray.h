/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_stringarray_h
#define _omi_stringarray_h

#include "config.h"
#include <common.h>
#include <stdio.h>
#include "batch.h"

BEGIN_EXTERNC

/*
**==============================================================================
**
** StringArray
**
**     Manages a null-terminated array of strings.
**
**==============================================================================
*/

typedef struct _StringArray
{
    Batch* batch;
    ZChar** data;
    size_t size;
    size_t capacity;
}
StringArray;

MI_Result StringArray_Init(
    StringArray* self,
    size_t capacity,
    Batch* batch);

MI_Result StringArray_Add(
    StringArray* self,
    const ZChar* str);

void StringArray_Print(
    const StringArray* self,
    FILE* os);

END_EXTERNC

#endif /* _omi_stringarray_h */
