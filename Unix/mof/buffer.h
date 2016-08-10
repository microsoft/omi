/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
