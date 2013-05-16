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

#include "stringarray.h"
#include "strings.h"
#include <io/io.h>

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
    tmp = (ZChar*)Batch_Zdup(self->batch, str);

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

    Fzprintf(os, ZT("{"));

    for (i = 0; i < self->size; i++)
    {
        Fzprintf(os, MI_T("%Z"), zcs(self->data[i]));

        if (i + 1 != self->size)
            Fzprintf(os, ZT(", "));
    }

    Fzprintf(os, ZT("}"));
}
