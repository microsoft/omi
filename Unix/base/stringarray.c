/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "stringarray.h"
#include <pal/strings.h>
#include <pal/format.h>

MI_Result StringArray_Init(
    StringArray* self,
    size_t capacity,
    Batch* batch)
{
    self->batch = batch;
    self->size = 0;
    self->capacity = capacity;

    if (capacity)
    {
        self->data = Batch_Get(batch, sizeof(ZChar*) * capacity);

        if (!self->data)
            return MI_RESULT_FAILED;
    }
    else
        self->data = NULL;

    return MI_RESULT_OK;
}

MI_Result StringArray_Add(
    StringArray* self,
    const ZChar* str)
{
    ZChar* tmp;

    /* Enlarge data capacity if necessary */
    if (self->size == self->capacity)
        return MI_RESULT_FAILED;

    /* Allocate new string */
    tmp = (ZChar*)Batch_Tcsdup(self->batch, str);

    if (!tmp)
        return MI_RESULT_FAILED;

    /* Add to end of array */
    self->data[self->size++] = tmp;

    return MI_RESULT_OK;
}

void StringArray_Print(
    const StringArray* self,
    FILE* os)
{
    size_t i;

    Ftprintf(os, PAL_T("{"));

    for (i = 0; i < self->size; i++)
    {
        Ftprintf(os, PAL_T("%T"), tcs(self->data[i]));

        if (i + 1 != self->size)
            Ftprintf(os, PAL_T(", "));
    }

    Ftprintf(os, PAL_T("}"));
}
