/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _mof_heap_h
#define _mof_heap_h

#include <stdlib.h>
#include <string.h>

typedef struct _MOF_Heap
{
    struct _MOF_Block* head;
}
MOF_Heap;

#define MOF_HEAP_INITIALIZER { NULL, NULL }

void* MOF_Malloc(MOF_Heap* self, size_t size);

void* MOF_Calloc(MOF_Heap* self, size_t count, size_t size);

void* MOF_Realloc(MOF_Heap* self, void* ptr, size_t size);

void MOF_Free(MOF_Heap* self, void* ptr);

char* MOF_Strdup(MOF_Heap* self, const char* str);

void MOF_Release(MOF_Heap* self);

#endif /* _mof_heap_h */
