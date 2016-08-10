/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "array.h"

#include <assert.h>
#include <new>
#include <common.h>
#include <pal/atomic.h>
#include "types.h"
#include "instance.h"

MI_BEGIN_NAMESPACE

struct header
{
    volatile ptrdiff_t m_refCounter;
    MI_Uint32       m_capacity;
};

struct Array_data
{
    void* p;
    MI_Uint32 size;
};

//==============================================================================
//
// Traits for 'raw' types.
//
//==============================================================================

static ArrayTraits _uint8Traits =
{
    sizeof(Uint8), 0, 0,
};

static ArrayTraits _uint16Traits =
{
    sizeof(Uint16), 0, 0,
};

static ArrayTraits _uint32Traits =
{
    sizeof(Uint32), 0, 0,
};

static ArrayTraits _uint64Traits =
{
    sizeof(Uint64), 0, 0,
};

static ArrayTraits _datetimeTraits =
{
    sizeof(Datetime), 0, 0,
};

static void _stringCtor(void* dest_, const void* src_, MI_Uint32 size)
{
    String* dest = (String*)dest_;
    const String* src = (const String*)src_;

    while(size--)
        new(dest++) String(*src++);
}

static void _stringDtor(void* data_, MI_Uint32 size)
{
    String* data = (String*)data_;

    while (size--)
        data++->~String();
}

static ArrayTraits _stringTraits =
{
    sizeof(String), _stringCtor, _stringDtor,
};

static void _instanceCtor(void* dest_, const void* src_, MI_Uint32 size)
{
    Instance* dest = (Instance*)dest_;
    const Instance* src = (const Instance*)src_;

    while(size--)
        new(dest++) Instance(*src++);
}

static void _instanceDtor(void* data_, MI_Uint32 size)
{
    Instance* data = (Instance*)data_;

    while (size--)
        data++->~Instance();
}

static ArrayTraits _instanceTraits =
{
    sizeof(Instance), _instanceCtor, _instanceDtor,
};

/* Indexable by scalar type */
const ArrayTraits* __traits[16] =
{
    &_uint8Traits, /* boolean */
    &_uint8Traits, /* uint8 */
    &_uint8Traits, /* sint8 */
    &_uint16Traits, /* uint16 */
    &_uint16Traits, /* sint64 */
    &_uint32Traits, /* uint32 */
    &_uint32Traits, /* sint32 */
    &_uint64Traits, /* uint64 */
    &_uint64Traits, /* sint64 */
    &_uint32Traits, /* real32 */
    &_uint64Traits, /* real64 */
    &_uint16Traits, /* char16 */
    &_datetimeTraits, /* datetime */
    &_stringTraits, /* string */
    &_instanceTraits, /* reference */
    &_instanceTraits, /* instance */
};

//==============================================================================
//
// Array
//
//==============================================================================

enum { CAPACITY_ALIGMENT = 16 };
// returns 0 - for 0; 16 for 1-6; 32 for 17-32 etc
inline static MI_Uint32 AlignCapacity(MI_Uint32 size) {return ((size + CAPACITY_ALIGMENT -1) / CAPACITY_ALIGMENT) * CAPACITY_ALIGMENT;}

static void* Allocate(MI_Uint32 size, const ArrayTraits* v_traits)
{
    MI_Uint32 capacity = AlignCapacity(size);

    // allocate new buffer
    header* chunk = (header*)operator new(sizeof(header) + capacity * v_traits->size);

    chunk->m_capacity = capacity;
    Atomic_Swap(&chunk->m_refCounter, 0);

    return (chunk + 1);
}

inline static header* GetHeader(void* buf) 
{
    return reinterpret_cast<header*>(reinterpret_cast<char*>(buf) - sizeof(header));
}

inline static void AddRef(void* data)
{
    if ( data )
        Atomic_Inc(&GetHeader(data)->m_refCounter);
}

static void Release(void* v_this, const ArrayTraits* v_traits)
{
    Array_data* v = (Array_data*)v_this;
    if ( v->p &&
        Atomic_Dec(&GetHeader(v->p)->m_refCounter) == 0)
    {
        if (v_traits->dtor)
            v_traits->dtor(v->p,v->size);

        operator delete(GetHeader(v->p));
        v->p = 0;
        v->size = 0;
    }
}

// Array class implementation - taken out to reduce code size
void __ArrayCopyCtor(void* v_this, const ArrayTraits* v_traits, const void* v_obj, MI_Uint32 count)
{
    Array_data* v = (Array_data*)v_this;

    v->p = Allocate(count,v_traits);
    v->size = count;
    AddRef(v->p);

    if(v_traits->copy_ctor)
        v_traits->copy_ctor(v->p,v_obj,count);
    else
        memcpy(v->p,v_obj,count*v_traits->size);
}

void __ArrayAssign(void* v_this, const ArrayTraits* v_traits, const void* v_other)
{
    Array_data* v = (Array_data*)v_this;
    const Array_data* v_x = (const Array_data*)v_other;

    Release(v_this, v_traits);

    if (v_x)
    {
        *v = *v_x;
        AddRef(v->p);
    }
}

void __ArrayCOW(void* v_this, const ArrayTraits* v_traits)
{
    Array_data* v = (Array_data*)v_this;
    if ( v->p && Atomic_Read(&GetHeader(v->p)->m_refCounter) != 1 )
    {
        void* new_data = Allocate(v->size,v_traits);

        if (v_traits->copy_ctor)
            v_traits->copy_ctor(new_data,v->p,v->size);
        else
            memcpy(new_data,v->p,v->size*v_traits->size);

        Release(v_this,v_traits);
        v->p = new_data;
        AddRef(v->p);
    }
}

void __ArrayResize(void* v_this, const ArrayTraits* v_traits, const void* v_obj, MI_Uint32 new_size)
{
    Array_data* v = (Array_data*)v_this;

    // special case - remove all
    if (!new_size)
    {
        Release(v_this,v_traits);
        v->p = 0;
        v->size = 0;
        return;
    }

    // assumptions:
    //      size > 0
    //      if size < m_size, buffer stays the same
    // actions:
    //      cow()
    //      re-alloc

    // make own copy
    __ArrayCOW(v_this,v_traits);


    // see if we need to re-alloc
    if ( !v->p || GetHeader(v->p)->m_capacity < new_size)
    {
        void* new_data = Allocate(new_size,v_traits);
        if (v->size)
            memcpy(new_data,v->p,v->size * v_traits->size);

        if (v->p)
            operator delete(GetHeader(v->p));

        v->p = new_data;
        AddRef(v->p);
    }

    // delete extra
    if ( v->size > new_size && v_traits->dtor )
    {
        v_traits->dtor(((char*)v->p) + new_size*v_traits->size, v->size-new_size);
    }

    // create missing
    if ( v->size < new_size )
    {
        // copy elements one-by-one
        for( ;v->size < new_size; v->size++)
        {
            if ( v_traits->copy_ctor )
            {
                v_traits->copy_ctor(((char*)v->p) + v->size*v_traits->size,v_obj,1);
            }
            else
            {
                memcpy(((char*)v->p) + v->size*v_traits->size,v_obj,v_traits->size);
            }
        }
    }

    v->size = new_size;
}

void __ArrayDelete(void* v_this, const ArrayTraits* v_traits, MI_Uint32 index)
{
    Array_data* v = (Array_data*)v_this;

    __ArrayCOW(v_this,v_traits);

    // destroy item
    if ( v_traits->dtor )
    {
        v_traits->dtor(((char*)v->p) + index*v_traits->size,1);
    }

    // move the rest
    memmove(((char*)v->p) +index*v_traits->size, ((char*)v->p) + (index+1)*v_traits->size, (v->size - index - 1)*v_traits->size);

    // dec size
    v->size --;
}


MI_END_NAMESPACE
