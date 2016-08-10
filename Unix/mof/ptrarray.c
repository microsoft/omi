/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "ptrarray.h"
#include "types.h"
#include "state.h"

int PtrArray_Append(PtrArray* self, void* ptr)
{
    MOF_ASSERT(self != NULL);
    MOF_ASSERT(ptr != NULL);

    if (!self || !ptr)
        return -1;

    self->data = (void**)MOF_Realloc(&state.heap,
        self->data, sizeof(void*) * (self->size + 1));

    if (!self->data)
    {
        yyerrorf(ID_OUT_OF_MEMORY, "out of memory");
        return -1;
    }

    self->data[self->size++] = ptr;

    return 0;
}

