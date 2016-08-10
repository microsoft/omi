/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _micxx_arraytraits_h
#define _micxx_arraytraits_h

#include <new>
#include "atomic.h"
#include "memory.h"
#include "linkage.h"

MI_BEGIN_NAMESPACE

struct ArrayTraits
{
    /* The size in bytes of an array element. */
    size_t size;

    /* Implements the placement copy construction operation for this type */
    void (*copy_ctor)(void* raw, const void* obj, MI_Uint32 numElements);

    /* Implements the dtoror for this type */
    void (*dtor)(void* obj, MI_Uint32 numElements);
};

template<class TYPE>
void __Construct(void* dest_, const void* src_, MI_Uint32 size)
{
    TYPE* dest = (TYPE*)dest_;
    const TYPE* src = (const TYPE*)src_;

    while(size--)
        new(dest++) TYPE(*src++);
}

template<class TYPE>
void __Destruct(void* data_, MI_Uint32 size)
{
    TYPE* data = (TYPE*)data_;

    while (size--)
        (data++)->~TYPE();
}

template<class TYPE>
inline const ArrayTraits* GetArrayTraits()
{
    static const ArrayTraits traits = 
    { 
        sizeof(TYPE), 
        __Construct<TYPE>, 
        __Destruct<TYPE> 
    };
    return &traits;
}

MI_END_NAMESPACE

#endif /* _micxx_arraytraits_h */
