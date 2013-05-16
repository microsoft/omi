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

#ifndef _micxx_arraytraits_h
#define _micxx_arraytraits_h

#include <new>
#include "atomic.h"
#include "memory.h"

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
