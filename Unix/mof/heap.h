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
