/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "buf.h"
#include <pal/strings.h>

#define _MIN_CAPACITY 256

/*
**==============================================================================
**
** Local definitions
**
**==============================================================================
*/

/* Round x up to the nearest power of 2 */
static MI_Uint32 _RoundPow2(MI_Uint32 x)
{
    MI_Uint32 r = x - 1;
    r |= (r >> 1);
    r |= (r >> 2);
    r |= (r >> 4);
    r |= (r >> 8);
    r |= (r >> 16);
    return r + 1;
}

/*
**==============================================================================
**
** Public definitions
**
**==============================================================================
*/

MI_Result Buf_Init(
    Buf* self,
    MI_Uint32 capacity)
{
    Page* page;

    /* Adjust capacity if too small */
    if (capacity < _MIN_CAPACITY)
        capacity = _MIN_CAPACITY;

    /* Allocate data buffer */
    page = (Page*)PAL_Malloc(sizeof(Page) + capacity);

    if (!page)
        return MI_RESULT_FAILED;

    memset(page, 0, sizeof(Page) + capacity);
    page->u.s.size = capacity;
    page->u.s.next = 0;

    /* Set fields */
    self->data = page + 1;
    self->size = 0;
    self->capacity = capacity;
    self->offset = 0;

#ifdef CONFIG_ENABLE_DEBUG
#ifdef _PREFAST_
    #pragma prefast(push)
    #pragma prefast(disable:22107) 
#endif
    memset(self->data,0xAA,self->capacity);
#ifdef _PREFAST_
    #pragma prefast(pop)
#endif        
#endif

    return MI_RESULT_OK;
}

void Buf_Destroy(
    Buf* self)
{
    if (self->data)
        PAL_Free((Page*)self->data - 1);
}

MI_Result Buf_Reserve(
    Buf* self, 
    MI_Uint32 capacity)
{
    /* Expand allocation if we need more space */
    if (capacity > self->capacity)
    {
        Page* page;

        capacity = _RoundPow2(capacity);

        if (self->data)
        {
            page = (Page*)self->data - 1;
            page = (Page*)PAL_Realloc(page, sizeof(Page) + capacity);
#ifdef CONFIG_ENABLE_DEBUG
            if (page)
                memset(((char*)(page+1)) + self->capacity,0xAA,capacity - self->capacity);
#else
            if(page)
                memset(((char*)(page+1)) + self->capacity,0,capacity - self->capacity);
#endif
        }
        else
        {
            page = (Page*)PAL_Malloc(sizeof(Page) + capacity);
#ifdef CONFIG_ENABLE_DEBUG
            if(page)
                memset(page,0xAA,sizeof(Page) + capacity);
#else
            if(page)
                memset(page, 0, sizeof(Page) + capacity);
#endif
        }

        if (!page)
            return MI_RESULT_FAILED;

        page->u.s.size = capacity;
        self->data = page + 1;
        self->capacity = capacity;
    }

    return MI_RESULT_OK;
}

MI_Result __Buf_App(
    Buf* self, 
    const void* data, 
    MI_Uint32 size)
{
    MI_Result r = Buf_Reserve(self, self->size + size);

    if (r != MI_RESULT_OK)
        return MI_RESULT_FAILED;

    memcpy((char*)self->data + self->size, data, size);
    self->size += size;

    return MI_RESULT_OK;
}

MI_Result Buf_PackStr(
    Buf* self,
    const ZChar* x)
{
    MI_Uint32 size;

    /* Pack null strings as 0 */
    if (!x)
        return Buf_PackU32(self, 0);
    
    /* Pack the size of the string (size including null terminator) */
    size = (MI_Uint32)Tcslen(x) + 1;
    MI_RETURN_ERR(Buf_PackU32(self, size));

    /* Pack the characters (including the null terminator) */
    MI_RETURN_ERR(Buf_App(self, x, size * sizeof(ZChar)));

    return MI_RESULT_OK;
}

MI_Result Buf_PackStrLen(
    Buf* self,
    const ZChar* x,
    MI_Uint32 size)
{
    /* Pack null strings as 0 */
    if (!x)
        return Buf_PackU32(self, 0);
    
    /* Pack the size of the string (size including null terminator) */
    MI_RETURN_ERR(Buf_PackU32(self, size + 1));

    /* Pack the characters (including the null terminator) */
    MI_RETURN_ERR(Buf_App(self, x, (size + 1) * sizeof(ZChar)));

    return MI_RESULT_OK;
}

MI_Result Buf_UnpackU8A(
    Buf* self,
    const MI_Uint8** data,
    MI_Uint32* size)
{
    /* Unpack size */
    MI_RETURN_ERR(Buf_UnpackU32(self, size));

    if (*size == 0)
    {
        *data = NULL;
        return MI_RESULT_OK;
    }
    
    /* Check whether there are enough bytes left */
    if (self->offset + *size * sizeof(MI_Uint8) > self->size)
        return MI_RESULT_FAILED;

    /* Store pointer to array */
    *data = (const MI_Uint8*)((char*)self->data + self->offset);
    self->offset += *size * sizeof(MI_Uint8);

    return MI_RESULT_OK;
}

MI_Result Buf_UnpackU16A(
    Buf* self,
    const MI_Uint16** data,
    MI_Uint32* size)
{
    /* Unpack size */
    MI_RETURN_ERR(Buf_UnpackU32(self, size));

    if (*size == 0)
    {
        *data = NULL;
        return MI_RESULT_OK;
    }
    
    /* Check whether there are enough bytes left */
    if (self->offset + *size * sizeof(MI_Uint16) > self->size)
        return MI_RESULT_FAILED;

    /* Store pointer to array */
    *data = (const MI_Uint16*)((char*)self->data + self->offset);
    self->offset += *size * sizeof(MI_Uint16);

    return MI_RESULT_OK;
}

MI_Result Buf_UnpackU32A(
    Buf* self,
    const MI_Uint32** data,
    MI_Uint32* size)
{
    /* Unpack size */
    MI_RETURN_ERR(Buf_UnpackU32(self, size));

    if (*size == 0)
    {
        *data = NULL;
        return MI_RESULT_OK;
    }
    
    /* Check whether there are enough bytes left */
    if (self->offset + *size * sizeof(MI_Uint32) > self->size)
        return MI_RESULT_FAILED;

    /* Store pointer to array */
    *data = (const MI_Uint32*)((char*)self->data + self->offset);
    self->offset += *size * sizeof(MI_Uint32);

    return MI_RESULT_OK;
}

MI_Result Buf_UnpackU64A(
    Buf* self,
    const MI_Uint64** data,
    MI_Uint32* size)
{
    /* Unpack size */
    MI_RETURN_ERR(Buf_UnpackU32(self, size));

    if (*size == 0)
    {
        *data = NULL;
        return MI_RESULT_OK;
    }

    /* Align buffer on 8 byte boundary */
    MI_RETURN_ERR(Buf_Align64(self));
    
    /* Check whether there are enough bytes left */
    if (self->offset + *size * sizeof(MI_Uint64) > self->size)
        return MI_RESULT_FAILED;

    /* Store pointer to array */
    *data = (const MI_Uint64*)((char*)self->data + self->offset);
    self->offset += *size * sizeof(MI_Uint64);

    return MI_RESULT_OK;
}

MI_Result Buf_UnpackStr(
    Buf* self,
    const ZChar** x)
{
    MI_Uint32 size;

    /* Unpack size */
    MI_RETURN_ERR(Buf_UnpackU32(self, &size));

    if (size == 0)
    {
        *x = NULL;
        return MI_RESULT_OK;
    }
    
    /* Check whether there are enough bytes left */
    if (self->offset + size * sizeof(ZChar) > self->size)
        return MI_RESULT_FAILED;

    /* Store pointer to array */
    *x = (const ZChar*)((char*)self->data + self->offset);
    self->offset += size * sizeof(ZChar);

    return MI_RESULT_OK;
}

MI_Result Buf_PackPtrdiff_t (
	Buf* self,
	ptrdiff_t data)
{
#if defined(PAL_64BIT)
	MI_RETURN_ERR(Buf_PackU64(self, (MI_Uint64)data));
#elif defined(PAL_32BIT)
	MI_RETURN_ERR(Buf_PackU32(self, (MI_Uint32)data));
#else
    return MI_RESULT_NOT_SUPPORTED;
#endif
	return MI_RESULT_OK;
}

MI_Result Buf_UnpackPtrdiff_t (
	Buf* self,
	ptrdiff_t* x)
{
#if defined(PAL_64BIT)
	MI_RETURN_ERR(Buf_UnpackU64(self, (MI_Uint64*)x));
#elif defined(PAL_32BIT)
	MI_RETURN_ERR(Buf_UnpackU32(self, (MI_Uint32*)x));
#else
	return MI_RESULT_NOT_SUPPORTED;
#endif
	return MI_RESULT_OK;
}

MI_Result Buf_PackStrA(
    Buf* self,
    const ZChar** data,
    MI_Uint32 size)
{
    MI_Uint32 i;

    /* Pack the array size (the number of strings) */
    MI_RETURN_ERR(Buf_PackU32(self, size));

    if (size)
    {
        ptrdiff_t sizes[64];
        ptrdiff_t offset;

        if (!data)
            return MI_RESULT_FAILED;

        MI_RETURN_ERR(Buf_Pad64(self));

        /* Let "size(string) times size(ZChar)" be denoted by ZCharSize(string). 
        * Put ZCharSize offsets of all strings first. 
        *
        * For example: consider the string  "RED\0GREEN\0BLUE\0"
        * We put four ZCharSize offsets in the buffer:
        *           0*sizeof(ZChar) | (4)*sizeof(ZChar) | (4+6)*sizeof(ZChar) | (4+6+5)*sizeof(ZChar)
        *
        * Each ZCharSize offset is encoded as a 64-bit
        * integer. The unpack function replaces this integer with a pointer
        * to the corresponding string. This avoids having to allocate memory
        * for the pointer array while unpacking.
        */

        /* Pack the ZCharSize offsets */
        offset = 0;
        for (i = 0; i < size; i++)
        {
            ptrdiff_t n;

            if (!data[i])
            return MI_RESULT_FAILED;

            n = ((ptrdiff_t)Tcslen(data[i]) + 1) * sizeof(ZChar);

            /* Save size so that it will not have to be recalculated by the
            * next loop using strlen.
            */
            if (i < MI_COUNT(sizes))
            sizes[i] = n;

            /* Pack according to the platform */
            MI_RETURN_ERR(Buf_PackPtrdiff_t (self, offset));

            /* Accumulate the ZCharSizes */
            offset += n;
        }

        /* Pack the total size */
        MI_RETURN_ERR(Buf_PackPtrdiff_t(self, offset));

        /* Pack strings one after the other. */
        for (i = 0; i < size; i++)
        {
            MI_Uint32 n;
            
            if (i < MI_COUNT(sizes))
                n = (MI_Uint32)sizes[i];
            else 
                n = ((MI_Uint32)Tcslen(data[i]) + 1) * sizeof(ZChar);

            MI_RETURN_ERR(Buf_App(self, data[i], n));
        }
    }

    return MI_RESULT_OK;
}

MI_Result Buf_UnpackStrA(
    Buf* self,
    const ZChar*** dataOut,
    MI_Uint32* sizeOut)
{
    const ZChar** data;
    MI_Uint32 size;
    MI_Uint32 i;
    MI_Uint32 offset;
    ptrdiff_t start;
	
    /* Unpack the size of the array */
    MI_RETURN_ERR(Buf_UnpackU32(self, &size));

    /* Handle zero-size array case */
    if (size == 0)
    {
        *dataOut = NULL;
        *sizeOut = 0;
        return MI_RESULT_OK;
    }

    /* Align to read uint64 sizes */
    MI_RETURN_ERR(Buf_Align64(self));

    /* Set pointer data array */
    data = (const ZChar**)((char*)self->data + self->offset);

    /* Calculate offset to first string in array (data[0]) */
    offset = self->offset + ((size+1) * sizeof(ptrdiff_t));

    /* Fail if offset is beyond end of buffer */
    if (offset > self->size)
        return MI_RESULT_FAILED;

    /* Unpack the string ZCharSizes/pointers and convert to string pointers 
    *  We intentionally iterate (size + 1) times.
    */
    start = 0;
    for (i = 0; i <= size; i++)
    {
        ptrdiff_t n;

        /* Unpack size of next string in array */
        MI_RETURN_ERR(Buf_UnpackPtrdiff_t (self, &n));

        /* Remember the first element - this will be the base */
        if (i == 0)
            start = n;

        /* Fail if not enough room left in buffer for string */
        if (offset + (n-start) > self->size)
            return MI_RESULT_FAILED;
		
        /* Add string pointer to array */
        data[i] = (ZChar*)((char*)self->data + offset + (n-start));
    }
    
    /* Update the offset */
    self->offset = offset + (MI_Uint32)(((ptrdiff_t)data[size]) - ((ptrdiff_t)data[0]));

    /* Set the output parameters */
    *dataOut = data;
    *sizeOut = size;

    return MI_RESULT_OK;
}

MI_Result Buf_PackDT(
    Buf* self,
    const MI_Datetime* x)
{
    MI_RETURN_ERR(Buf_Pad32(self));
    MI_RETURN_ERR(Buf_App(self, x, sizeof(MI_Datetime)));
    return MI_RESULT_OK;
}

MI_Result Buf_UnpackDT(
    Buf* self,
    MI_Datetime* x)
{
    MI_Uint32 offset;

    MI_RETURN_ERR(Buf_Align32(self));

    /* Find ending offset of datetime structure */
    offset = self->offset + sizeof(MI_Datetime);

    if (offset > self->size)
        return MI_RESULT_FAILED;

    memcpy(x, (char*)self->data + self->offset, sizeof(MI_Datetime));
    self->offset = offset;

    return MI_RESULT_OK;
}

MI_Result Buf_PackDTA(
    Buf* self,
    const MI_Datetime* data,
    MI_Uint32 size)
{
    MI_RETURN_ERR(Buf_PackU32(self, size));
    MI_RETURN_ERR(Buf_App(self, data, size * sizeof(MI_Datetime)));
    return MI_RESULT_OK;
}

MI_Result Buf_UnpackDTA(
    Buf* self,
    const MI_Datetime** dataPtr,
    MI_Uint32* sizePtr)
{
    MI_Uint32 offset;

    /* Unpack the size */
    MI_RETURN_ERR(Buf_UnpackU32(self, sizePtr));

    /* Handle zero-sized array (null data pointer) */
    if (*sizePtr == 0)
    {
        *dataPtr = NULL;
        return MI_RESULT_OK;
    }

    /* Find ending offset of datetime array */
    offset = self->offset + *sizePtr * sizeof(MI_Datetime);

    /* Set pointer to data array */
    *dataPtr = (const MI_Datetime*)((char*)self->data + self->offset);

    /* Advance offset beyond array */
    self->offset = offset;

    return MI_RESULT_OK;
}

Page* Buf_StealPage(
    Buf* self)
{
    if (self->data)
    {
        Page* page = (Page*)self->data - 1;
        self->data = NULL;
        return page;
    }

    return NULL;
}

MI_Result Buf_AppStr(
    Buf* self, 
    const ZChar* str)
{
    return Buf_App(self, str, (MI_Uint32)Tcslen(str) * sizeof(ZChar));
}

MI_Result Buf_AppStrN(
    Buf* self, 
    const ZChar* str,
    size_t size)
{
    return Buf_App(self, str, (MI_Uint32)size * sizeof(ZChar));
}

