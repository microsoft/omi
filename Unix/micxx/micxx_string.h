/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _micxx_string_h
#define _micxx_string_h

#include <MI.h>
#include "linkage.h"
#include "atomic.h"

MI_BEGIN_NAMESPACE

class MICXX_LINKAGE String
{
public:

    String();

    String(const MI_Char* str);

    String(const MI_Char* str, MI_Uint32 size);

    String(const String& x);

    ~String();

    void Clear();

    String& operator=(const String& x);

    String& operator+=(const String& x);

    String& operator+=(const MI_Char* str);

    String& operator+=(const MI_Char ch);

    void Append(const MI_Char* str, MI_Uint32 size);

    MI_Char& operator[](MI_Uint32 index);

    MI_Char operator[](MI_Uint32 index) const;

#if 0
    /* ATTN: disabled for now (not in standard basic_string<>) */
    operator const MI_Char*() const;
#endif

    const MI_Char* Str() const;

    bool Equal(const String& x) const;

    bool Equal(const MI_Char* str) const;

    MI_Uint32 GetSize() const;

private:

    struct Header
    {
        AtomicType m_refCounter;
        MI_Uint32 m_size;
        MI_Uint32 m_capacity;
    };

    String& StrCat(const MI_Char* str, MI_Uint32 size);

    void AddRef();

    void Release();

    static MI_Char* Allocate(int capacity);

    // returns 0 - for 0; 16 for 1-6; 32 for 17-32 etc
    static int AlignCapacity(MI_Uint32 size) 
    {
        const MI_Uint32 ALIGNMENT = 16;
        return ((size + ALIGNMENT -1) / ALIGNMENT) * ALIGNMENT;
    }

    static Header* GetHeader(_In_ MI_Char* buf) 
    {
        return reinterpret_cast<Header*>(
            reinterpret_cast<char*>(buf) - sizeof(Header));
    }

    // for compatability with "C", it must have only one pointer member!
    MI_Char*  m_data;
};

inline String::String() : m_data(0) 
{
}

inline String::String(const String& x)
{
    m_data = x.m_data;
    AddRef();
}

inline String::~String()
{
    Release();
}

inline void String::AddRef()
{
    if ( m_data )
    {
        AtomicInc(GetHeader(m_data)->m_refCounter);
    }
}

inline String& String::operator+=(const String& x)
{
    if ( !m_data )
        return operator=(x);

    return StrCat(x.Str(), x.GetSize());
}

inline const MI_Char* String::Str() const 
{
    return m_data ? m_data : MI_T("");
}

inline bool String::Equal(const MI_Char* str) const 
{
    return memcmp(str, Str(), (GetSize()+1) * sizeof(MI_Char)) == 0;
}

inline MI_Uint32 String::GetSize() const 
{
    return m_data ? GetHeader(m_data)->m_size : 0;
}

inline bool operator==(const String& x, const String& y)
{
    return x.Equal(y);
}

inline bool operator==(const String& x, const MI_Char* str)
{
    return x.Equal(str);
}

inline bool operator==(const MI_Char* str, const String& x)
{
    return x.Equal(str);
}

inline bool operator!=(const String& x, const String& y)
{
    return !x.Equal(y);
}

inline bool operator!=(const String& x, const MI_Char* str)
{
    return !x.Equal(str);
}

inline bool operator!=(const MI_Char* str, const String& x)
{
    return !x.Equal(str);
}

MI_END_NAMESPACE

#endif /* _micxx_string_h */
