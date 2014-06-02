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

#ifndef _micxx_field_h
#define _micxx_field_h

#include <MI.h>

MI_BEGIN_NAMESPACE

template<class TYPE>
class Field
{
public:

    TYPE value;
    MI_Boolean exists;
    MI_Uint8 flags;

    Field();

    Field(const Field<TYPE>& x);

    explicit Field(const TYPE& x);

    void Set(const TYPE& x);

    void Clear();

    bool Equal(const Field<TYPE>& x) const;
};

template<class TYPE>
inline Field<TYPE>::Field() : value(), exists(false), flags(0)
{
}

template<class TYPE>
inline Field<TYPE>::Field(const Field<TYPE>& x) : 
    value(x.value), exists(x.exists),flags(x.flags)
{
}

template<class TYPE>
inline Field<TYPE>::Field(const TYPE& x) : value(x), exists(MI_TRUE), flags(0)
{
}

template<class TYPE>
inline void Field<TYPE>::Set(const TYPE& x)
{
    value = x;
    exists = MI_TRUE;
}

template<class TYPE>
inline void Field<TYPE>::Clear()
{
    value = TYPE();
    exists = MI_FALSE;
    flags = 0;
}

template<class TYPE>
inline bool Field<TYPE>::Equal(const Field<TYPE>& x) const
{
    return exists == x.exists && value == x.value;
}

template<class TYPE>
inline bool operator==(const Field<TYPE>& x, const Field<TYPE>& y)
{
    return x.Equal(y);
}

template<class TYPE>
inline bool operator!=(const Field<TYPE>& x, const Field<TYPE>& y)
{
    return !x.Equal(y);
}

MI_END_NAMESPACE

#endif /* _micxx_field_h */
