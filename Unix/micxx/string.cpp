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

#include "micxx_string.h"
#include "memory.h"

#include <assert.h>
#include <new>
#include <pal/atomic.h>
////////////////////////////////////////////
// Utility and base classes
#include <common.h>

MI_BEGIN_NAMESPACE

// String

static size_t _Strlen(const MI_Char* p)
{
    const MI_Char* start = p;
    while (*p)
        p++;
    return p - start;
}

String::String(const MI_Char* str)
{
    m_data = 0;

    if ( str )
    {
        int size = (int)_Strlen(str);
        m_data = Allocate( size+1 );
        memcpy(m_data,str,(size+1) * sizeof(MI_Char) );
        GetHeader(m_data)->m_size = size;

        AddRef();
    }
}

String::String(const MI_Char* str, MI_Uint32 size)
{
    m_data = 0;

    if ( str && size > 0 )
    {
        m_data = Allocate( size+1 );
        memcpy(m_data,str,(size) * sizeof(MI_Char) );
        m_data[size] = 0;
        GetHeader(m_data)->m_size = size;

        AddRef();
    }
}

void String::Clear()
{
    if (m_data)
    {
        GetHeader(m_data)->m_size = 0;
        m_data[0] = '\0';
    }
}

String& String::operator = (const String& x)
{
    if ( m_data != x.m_data )
    {
        Release();
        m_data = x.m_data;
        AddRef();
    }
    return *this;
}

bool String::Equal(const String& x) const
{
    if ( x.m_data == m_data )
        return true;

    if ( GetSize() != x.GetSize() )
        return false;

    return memcmp(x.Str(), Str(), (GetSize()+1) * sizeof(MI_Char)) == 0;
}

void String::Release()
{
    if ( m_data &&
        AtomicDec(GetHeader(m_data)->m_refCounter))
    {
        operator delete(GetHeader(m_data));
        m_data = 0;
    }
}

MI_Char* String::Allocate(int capacity)
{
    capacity = AlignCapacity(capacity);

    // allocate new buffer
    Header* chunk = (Header*)operator new(
        sizeof(Header) + capacity * sizeof(MI_Char));

    chunk->m_capacity = capacity;
    Atomic_Swap((ptrdiff_t*)&chunk->m_refCounter.__opaque, 0);
    chunk->m_size = 0;

    return reinterpret_cast<MI_Char*>(chunk + 1);
}

String& String::operator += (const MI_Char* str)
{
    // use assign instead
    if ( !m_data )
        return operator=(String(str));

    if ( !str )
        return *this;

    int size = (int)_Strlen(str);


    return StrCat(str,size);
}

void String::Append(const MI_Char* str, MI_Uint32 size)
{
    if (str)
    {
        if (!m_data)
        {
            operator=(String(str, size));
            return;
        }

        StrCat(str, size);
    }
}

MI_Char& String::operator[](MI_Uint32 index)
{
    if (m_data && index < GetHeader(m_data)->m_size)
    {
        return m_data[index];
    }
    else
    {
        static MI_Char dummy;
        return dummy;
    }
}

MI_Char String::operator[](MI_Uint32 index) const
{
    if (m_data && index < GetHeader(m_data)->m_size)
        return m_data[index];
    else
        return '\0';
}

String& String::operator+=(const MI_Char ch)
{
    // ATTN: optimize this!
    MI_Char buf[2];
    buf[0] = ch;
    buf[1] = '\0';
    return operator+=(buf);
}

String& String::StrCat(const MI_Char* str, MI_Uint32 size)
{
    // nothing to change
    if ( !size )
        return *this;

    if ( AtomicGet(GetHeader(m_data)->m_refCounter) != 1 ||
        GetHeader(m_data)->m_capacity <= (size + GetHeader(m_data)->m_size)
        )
    {   // have to allocate a new buffer
        MI_Char* new_buf = Allocate( GetHeader(m_data)->m_size + size + 1 );

        memcpy(new_buf,m_data,GetHeader(m_data)->m_size * sizeof(MI_Char) );
        memcpy(new_buf+GetHeader(m_data)->m_size,str,(size+1) * sizeof(MI_Char) );
        GetHeader(new_buf)->m_size = GetHeader(m_data)->m_size + size;

        Release();
        m_data = new_buf;
        AddRef();
    } 
    else 
    {
        memcpy(m_data+GetHeader(m_data)->m_size,str,(size+1) * sizeof(MI_Char) );
        GetHeader(m_data)->m_size += size;
    }

    return *this;
}

MI_END_NAMESPACE
