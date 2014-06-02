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

#ifndef _mof_buffer_h
#define _mof_buffer_h

#include <stdlib.h>
#include <common.h>

typedef struct Buffer
{
    void* data;
    size_t size;
    size_t capacity;
}
Buffer;

#define BUFFER_INITIALIZER { NULL, 0, 0 }

#if 0 /* ATTN:REMOVE */
extern int Buffer_Init(Buffer* self, size_t capacity);
#endif

extern int Buffer_Append(Buffer* self, const void* data , size_t size);

INLINE int Buffer_AppendChar(Buffer* self, char c)
{
    return Buffer_Append(self, &c, 1);
}

#endif /* _mof_buffer_h */
