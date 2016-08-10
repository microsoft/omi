/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _micxx_array_h
#define _micxx_array_h

#include <new>
#include "atomic.h"
#include "memory.h"
#include "arraytraits.h"

MI_BEGIN_NAMESPACE

template<class TYPE>
class Array
{
public:

    Array();

    Array(const Array<TYPE>& x);

    Array(const TYPE* data, MI_Uint32 size);

    ~Array();

    Array& operator=(const Array<TYPE>& x);

    MI_Uint32 GetSize() const;

    const TYPE* GetData() const;

    TYPE* GetWritableData();

    const TYPE& operator[](MI_Uint32 index) const;

    TYPE& operator[](MI_Uint32 index);

    void Clear();
    
    void Resize(MI_Uint32 size, const TYPE& item = TYPE());

    /* ATTN: Can we rename of "Remove" */
    void Delete(MI_Uint32 index);

    /* ATTN: Can we rename of "PushBack" */
    void PushBack(const TYPE& item);

private:

    void cow();

    struct Header
    {
        AtomicType m_refCounter;
        MI_Uint32 m_capacity;
    };

    static Header* GetHeader(TYPE* buf)
    {
        return reinterpret_cast<Header*>(
            reinterpret_cast<char*>(buf) - sizeof(Header));
    }

    static const ArrayTraits* traits()
    {
        return GetArrayTraits<TYPE>();
    }

    // for compatability with "C", it must have only one pointer and a size 
    // field - NO CHANGES ALLOWED!
    TYPE*  m_data;
    MI_Uint32 m_size;
};

MI_EXTERN_C MICXX_LINKAGE void __ArrayCopyCtor(void* v_this, 
    const ArrayTraits* v_traits, const void* v_obj, MI_Uint32 size);

MI_EXTERN_C MICXX_LINKAGE void __ArrayAssign(void* v_this, 
    const ArrayTraits* v_traits, const void* v_other);

MI_EXTERN_C MICXX_LINKAGE void __ArrayCOW(void* v_this, 
    const ArrayTraits* v_traits);

MI_EXTERN_C MICXX_LINKAGE void __ArrayResize(void* v_this, 
    const ArrayTraits* v_traits, const void* v_obj, MI_Uint32 new_size);

MI_EXTERN_C MICXX_LINKAGE void __ArrayDelete(void* v_this, 
    const ArrayTraits* v_traits, MI_Uint32 index);

template<class TYPE>
inline Array<TYPE>::Array() : m_data(0), m_size(0) 
{
}

template<class TYPE>
inline MI_Uint32 Array<TYPE>::GetSize() const 
{ 
    return m_size; 
}

template<class TYPE>
inline const TYPE* Array<TYPE>::GetData() const 
{
    return m_data;
}

template<class TYPE>
inline TYPE* Array<TYPE>::GetWritableData() 
{ 
    cow(); 
    return m_data;
}

template<class TYPE>
inline const TYPE& Array<TYPE>::operator[](MI_Uint32 index) const 
{
    return m_data[index];
}

template<class TYPE>
inline TYPE& Array<TYPE>::operator[](MI_Uint32 index) 
{ 
    cow(); 
    return m_data[index];
}

template<class TYPE>
inline void Array<TYPE>::Clear() 
{
    __ArrayAssign(this,traits(),0);
    m_data = 0;
    m_size = 0;
} 

template<class TYPE>
inline Array<TYPE>::Array(const TYPE* data, MI_Uint32 size)
{
    if (!size)
    {
        m_data = 0;
        m_size = 0;
    }
    else
    {
        __ArrayCopyCtor(this, traits(), data, size);
    }
}

template<class TYPE>
inline Array<TYPE>::~Array()
{
    __ArrayAssign(this,traits(),0);
}

template<class TYPE>
inline Array<TYPE>::Array(const Array<TYPE>& x): m_data(0), m_size(0) 
{
    *this = x;
}

template<class TYPE>
inline Array<TYPE>& Array<TYPE>::operator=(const Array<TYPE>& x)
{
    if (m_data != x.m_data)
    {
        __ArrayAssign(this,traits(),&x);
    }
    return *this;
}

template<class TYPE>
inline void Array<TYPE>::cow()
{
    if ( m_data && AtomicGet(GetHeader(m_data)->m_refCounter) != 1 )
        __ArrayCOW(this,traits());
}

template<class TYPE>
inline void Array<TYPE>::PushBack(const TYPE& item)
{
    Resize(GetSize() + 1, item);
}

template<class TYPE>
inline void Array<TYPE>::Resize(MI_Uint32 size, const TYPE& item)
{
    if (GetSize() == size)
        return;

    __ArrayResize(this, traits(), &item, size);

}

template<class TYPE>
inline void Array<TYPE>::Delete(MI_Uint32 index)
{
    /* ATTN: what does this do? */
    if (GetSize() == 1)
    {
        Clear();
        return;
    }

    __ArrayDelete(this, traits(), index);
}

MI_END_NAMESPACE

#endif /* _micxx_array_h */
