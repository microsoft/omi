/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_buf_h
#define _omi_buf_h

#include "config.h"
#include <string.h>
#include <common.h>
#include "batch.h"

BEGIN_EXTERNC

/*
**==============================================================================
**
** Buf
**
**==============================================================================
*/
#define BUF_INITIALIZER { NULL, 0, 0, 0 }

typedef struct _Buf
{
    /* The buffer memory (preceded by Page object) */
    void* data;

    /* The current size of the buffer */
    MI_Uint32 size;

    /* The current capacity of the buffer */
    MI_Uint32 capacity;

    /* The current unpacking offset of ths buffer */
    MI_Uint32 offset;
}
Buf;

MI_Result Buf_Init(
    Buf* self,
    MI_Uint32 capacity);

void Buf_Destroy(
    Buf* self);

MI_Result Buf_Reserve(
    Buf* self, 
    MI_Uint32 capacity);

/* Steal the memory page (can be passed to Batch_Attach) */
Page* Buf_StealPage(
    Buf* self);

MI_Result __Buf_App(
    Buf* self, 
    const void* data, 
    MI_Uint32 size);

INLINE MI_Result Buf_App(
    Buf* self, 
    const void* data, 
    MI_Uint32 size)
{
    if (self->size + size <= self->capacity)
    {
        memcpy((char*)self->data + self->size, data, size);
        self->size += size;
        return MI_RESULT_OK;
    }

    return __Buf_App(self, data, size);
}

/* Pad buffer out to the next 2-byte boundary */
MI_INLINE MI_Result Buf_Pad16(
    Buf* self)
{
    MI_Uint32 offset = (self->size + 1) & ~1;

    if (offset > self->capacity)
    {
        if (Buf_Reserve(self, offset) != MI_RESULT_OK)
            return MI_RESULT_FAILED;
    }

    self->size = offset;
    return MI_RESULT_OK;
}

/* Pad buffer out to the next 4-byte boundary */
MI_INLINE MI_Result Buf_Pad32(
    Buf* self)
{
    MI_Uint32 offset = (self->size + 3) & ~3;

    if (offset > self->capacity)
    {
        if (Buf_Reserve(self, offset) != MI_RESULT_OK)
            return MI_RESULT_FAILED;
    }

    self->size = offset;
    return MI_RESULT_OK;
}

/* Pad buffer out to the next 8-byte boundary */
MI_INLINE MI_Result Buf_Pad64(
    Buf* self)
{
    MI_Uint32 offset = (self->size + 7) & ~7;

    if (offset > self->capacity)
    {
        if (Buf_Reserve(self, offset) != MI_RESULT_OK)
            return MI_RESULT_FAILED;
    }

    self->size = offset;
    return MI_RESULT_OK;
}

/* Align buffer on the next 2 byte boundary */
MI_INLINE MI_Result Buf_Align16(
    Buf* self)
{
    MI_Uint32 offset = (self->offset + 1) & ~1;

    if (offset > self->size)
        return MI_RESULT_FAILED;

    self->offset = offset;
    return MI_RESULT_OK;
}

/* Align buffer on the next 4 byte boundary */
MI_INLINE MI_Result Buf_Align32(
    Buf* self)
{
    MI_Uint32 offset = (self->offset + 3) & ~3;

    if (offset > self->size)
        return MI_RESULT_FAILED;

    self->offset = offset;
    return MI_RESULT_OK;
}

/* Align buffer on the next 8 byte boundary */
MI_INLINE MI_Result Buf_Align64(
    Buf* self)
{
    MI_Uint32 offset = (self->offset + 7) & ~7;

    if (offset > self->size)
        return MI_RESULT_FAILED;

    self->offset = offset;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result Buf_PackU8(
    Buf* self,
    MI_Uint8 x)
{
    MI_Uint32 offset = self->size;

    if (offset + sizeof(x) > self->capacity)
    {
        if (Buf_Reserve(self, offset + sizeof(x)) != MI_RESULT_OK)
            return MI_RESULT_FAILED;
    }

    *((MI_Uint8*)((char*)self->data + offset)) = x;
    self->size = offset + sizeof(x);
    return MI_RESULT_OK;
}

MI_INLINE MI_Result Buf_PackU16(
    Buf* self,
    MI_Uint16 x)
{
    MI_Uint32 offset = (self->size + 1) & ~1;

    if (offset + sizeof(x) > self->capacity)
    {
        if (Buf_Reserve(self, offset + sizeof(x)) != MI_RESULT_OK)
            return MI_RESULT_FAILED;
    }

    *((MI_Uint16*)((char*)self->data + offset)) = x;
    self->size = offset + sizeof(x);
    return MI_RESULT_OK;
}

MI_INLINE MI_Result Buf_PackU32(
    Buf* self,
    MI_Uint32 x)
{
    MI_Uint32 offset = (self->size + 3) & ~3;

    if (offset + sizeof(x) > self->capacity)
    {
        if (Buf_Reserve(self, offset + sizeof(x)) != MI_RESULT_OK)
            return MI_RESULT_FAILED;
    }

    *((MI_Uint32*)((char*)self->data + offset)) = x;
    self->size = offset + sizeof(x);
    return MI_RESULT_OK;
}

MI_INLINE MI_Result Buf_PackU64(
    Buf* self,
    MI_Uint64 x)
{
    MI_Uint32 offset = (self->size + 7) & ~7;

    if (offset + sizeof(x) > self->capacity)
    {
        if (Buf_Reserve(self, offset + sizeof(x)) != MI_RESULT_OK)
            return MI_RESULT_FAILED;
    }

    *((MI_Uint64*)((char*)self->data + offset)) = x;
    self->size = offset + sizeof(x);
    return MI_RESULT_OK;
}

MI_Result Buf_PackStr(
    Buf* self,
    const ZChar* x);

MI_Result Buf_PackStrLen(
    Buf* self,
    const ZChar* x,
    MI_Uint32 size);

MI_INLINE MI_Result Buf_PackU8A(
    Buf* self,
    MI_Uint8* data,
    MI_Uint32 size)
{
    MI_RETURN_ERR(Buf_PackU32(self, size));

    if (size)
        MI_RETURN_ERR(Buf_App(self, data, size * sizeof(MI_Uint8)));

    return MI_RESULT_OK;
}

MI_INLINE MI_Result Buf_PackU16A(
    Buf* self,
    MI_Uint16* data,
    MI_Uint32 size)
{
    MI_RETURN_ERR(Buf_PackU32(self, size));

    if (size)
        MI_RETURN_ERR(Buf_App(self, data, size * sizeof(MI_Uint16)));

    return MI_RESULT_OK;
}

MI_INLINE MI_Result Buf_PackU32A(
    Buf* self,
    MI_Uint32* data,
    MI_Uint32 size)
{
    MI_RETURN_ERR(Buf_PackU32(self, size));

    if (size)
        MI_RETURN_ERR(Buf_App(self, data, size * sizeof(MI_Uint32)));

    return MI_RESULT_OK;
}

MI_INLINE MI_Result Buf_PackU64A(
    Buf* self,
    MI_Uint64* data,
    MI_Uint32 size)
{
    MI_RETURN_ERR(Buf_PackU32(self, size));

    if (size)
    {
        MI_RETURN_ERR(Buf_Pad64(self));
        MI_RETURN_ERR(Buf_App(self, data, size * sizeof(MI_Uint64)));
    }

    return MI_RESULT_OK;
}

MI_INLINE MI_Result Buf_UnpackU8(
    Buf* self,
    MI_Uint8* x)
{
    MI_Uint32 offset = self->offset;

    if (offset + sizeof(*x) > self->size)
        return MI_RESULT_FAILED;

    *x = *((MI_Uint8*)((char*)self->data + offset));
    self->offset = offset + sizeof(*x);
    return MI_RESULT_OK;
}

MI_INLINE MI_Result Buf_UnpackU16(
    Buf* self,
    MI_Uint16* x)
{
    MI_Uint32 offset = (self->offset + 1) & ~1;

    if (offset + sizeof(*x) > self->size)
        return MI_RESULT_FAILED;

    *x = *((MI_Uint16*)((char*)self->data + offset));
    self->offset = offset + sizeof(*x);
    return MI_RESULT_OK;
}

MI_INLINE MI_Result Buf_UnpackU32(
    Buf* self,
    MI_Uint32* x)
{
    MI_Uint32 offset = (self->offset + 3) & ~3;

    if (offset + sizeof(*x) > self->size)
        return MI_RESULT_FAILED;

    *x = *((MI_Uint32*)((char*)self->data + offset));
    self->offset = offset + sizeof(*x);
    return MI_RESULT_OK;
}

MI_INLINE MI_Result Buf_UnpackU64(
    Buf* self,
    MI_Uint64* x)
{
    MI_Uint32 offset = (self->offset + 7) & ~7;

    if (offset + sizeof(*x) > self->size)
        return MI_RESULT_FAILED;

    *x = *((MI_Uint64*)((char*)self->data + offset));
    self->offset = offset + sizeof(*x);
    return MI_RESULT_OK;
}

MI_Result Buf_PackPtrdiff_t (
	Buf* self,
	ptrdiff_t data);

MI_Result Buf_UnpackPtrdiff_t (
	Buf* self,
	ptrdiff_t* x);

MI_Result Buf_UnpackU8A(
    Buf* self,
    const MI_Uint8** data,
    MI_Uint32* size);

MI_Result Buf_UnpackU16A(
    Buf* self,
    const MI_Uint16** data,
    MI_Uint32* size);

MI_Result Buf_UnpackU32A(
    Buf* self,
    const MI_Uint32** data,
    MI_Uint32* size);

MI_Result Buf_UnpackU64A(
    Buf* self,
    const MI_Uint64** data,
    MI_Uint32* size);

MI_Result Buf_UnpackStr(
    Buf* self,
    const ZChar** x);

MI_Result Buf_PackStrA(
    Buf* self,
    const ZChar** data,
    MI_Uint32 size);

MI_Result Buf_UnpackStrA(
    Buf* self,
    const ZChar*** data,
    MI_Uint32* size);

MI_Result Buf_PackDT(
    Buf* self,
    const MI_Datetime* x);

MI_Result Buf_UnpackDT(
    Buf* self,
    MI_Datetime* x);

MI_Result Buf_PackDTA(
    Buf* self,
    const MI_Datetime* data,
    MI_Uint32 size);

MI_Result Buf_UnpackDTA(
    Buf* self,
    const MI_Datetime** dataPtr,
    MI_Uint32* sizePtr);

MI_Result Buf_AppStr(
    Buf* self, 
    const ZChar* str);

MI_Result Buf_AppStrN(
    Buf* self, 
    const ZChar* str,
    size_t size);

END_EXTERNC

#endif /* _omi_buf_h */
