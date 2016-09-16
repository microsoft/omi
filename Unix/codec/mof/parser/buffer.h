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
#include <common/common.h>
#include <base/batch.h>

typedef struct Buffer
{
    _Field_size_bytes_(capacity)
    void* data;
    _Field_range_(0, capacity) 
    size_t size;
    size_t capacity;
}
Buffer;

#define BUFFER_INITIALIZER { NULL, 0, 0 }

extern int Buffer_Append(_In_ void* mofstate, _Inout_ Buffer* self, _In_ _Readable_bytes_(size) const void* data , _In_ size_t size);

#endif /* _mof_buffer_h */
