/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "buf.h"
#include <stdlib.h>

#ifdef _PREFAST_
# pragma prefast (push)
# pragma prefast (disable: 28252)
# pragma prefast (disable: 28253)
#endif

#include <string.h>
#include <wchar.h>

#ifdef _PREFAST_
# pragma prefast (pop)
#endif

#define BUF_MINIMUM_CAPACITY 4096

MI_Result Buf_Construct(
    _Out_ Buf* self,
    _Inout_ MI_Char* data,
    size_t capacity)
{
    if (!data && capacity > 0)
        return MI_RESULT_FAILED;

    self->data = data;
    self->size = 0;
    self->capacity = capacity;
    self->owner = 0;

    return MI_RESULT_OK;
}

void Buf_Destruct(
    _Inout_ Buf* self)
{
    if (self->owner)
        free(self->data);
}

MI_Result Buf_Put(
    _Inout_ Buf* self,
    _In_reads_(size) const MI_Char* data,
    size_t size)
{
    /* If allocation is too small, then enlarge it */

    if (self->size + size > self->capacity)
    {
        MI_Char* p;

        /* Adjust capacity */

        if (self->capacity == 0)
            self->capacity = BUF_MINIMUM_CAPACITY;
        else
            self->capacity *= 2;

        /* Keep doubling the capacity until big enough */

        while (self->size + size > self->capacity)
            self->capacity *= 2;

        /* Reallocate the buffer to the new capacity */

        if (self->owner)
        {
            p = (MI_Char*)realloc(
                self->data, 
                self->capacity * sizeof(MI_Char));
        }
        else
        {
            p = (MI_Char*)malloc(self->capacity * sizeof(MI_Char));
        }

        if (!p)
            return MI_RESULT_FAILED;

        self->data = p;
        self->owner = 1;
    }

    /* Append new data to buffer */

    memcpy(
        self->data + self->size, 
        data, 
        size * sizeof(MI_Char));

    self->size += size;

    return MI_RESULT_OK;
}

MI_Result Buf_PutStr(
    _Inout_ Buf* self,
    _In_z_ const MI_Char* str)
{
#if (MI_CHAR_TYPE == 1)
    size_t len = strlen(str);
#else
    size_t len = wcslen(str);
#endif
    return Buf_Put(self, str, len);
}
