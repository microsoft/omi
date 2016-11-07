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

#ifndef _micxx_types_h
#define _micxx_types_h

#include <MI.h>
#include "linkage.h"
#include "array.h"
#include "micxx_string.h"
#include "datetime.h"

MI_BEGIN_NAMESPACE

// character type.
typedef MI_Char Char;

// simple types
typedef MI_Boolean Boolean;
typedef MI_Uint8 Uint8;
typedef MI_Sint8 Sint8;
typedef MI_Uint16 Uint16;
typedef MI_Sint16 Sint16;
typedef MI_Uint32 Uint32;
typedef MI_Sint32 Sint32;
typedef MI_Uint64 Uint64;
typedef MI_Sint64 Sint64;
typedef MI_Real32 Real32;
typedef MI_Real64 Real64;
typedef MI_Char16 Char16;

typedef MI_Type Type;

// On PowerPC Linux __bool is defined by default
#if defined(linux) && defined(__PPC__)
#undef __bool
#endif

// Convert from MI_Boolean to bool.
inline bool __bool(MI_Boolean x)
{
    return x ? true : false;
}

MICXX_LINKAGE extern const ArrayTraits* __traits[16];

template<>
inline const ArrayTraits* GetArrayTraits<Uint8>() 
{
    return __traits[MI_UINT8];
};

template<>
inline const ArrayTraits* GetArrayTraits<Sint8>() 
{
    return __traits[MI_SINT8];
};

template<>
inline const ArrayTraits* GetArrayTraits<Uint16>() 
{
    return __traits[MI_UINT16];
};

template<>
inline const ArrayTraits* GetArrayTraits<Sint16>() 
{
    return __traits[MI_SINT16];
};

template<>
inline const ArrayTraits* GetArrayTraits<Uint32>() 
{
    return __traits[MI_UINT32];
};

template<>
inline const ArrayTraits* GetArrayTraits<Sint32>() 
{
    return __traits[MI_SINT32];
};

template<>
inline const ArrayTraits* GetArrayTraits<Uint64>() 
{
    return __traits[MI_UINT64];
};

template<>
inline const ArrayTraits* GetArrayTraits<Sint64>() 
{
    return __traits[MI_SINT64];
};

template<>
inline const ArrayTraits* GetArrayTraits<Real32>() 
{
    return __traits[MI_REAL32];
};

template<>
inline const ArrayTraits* GetArrayTraits<Real64>() 
{
    return __traits[MI_REAL64];
};

template<>
inline const ArrayTraits* GetArrayTraits<Datetime>() 
{
    return __traits[MI_DATETIME];
};

template<>
inline const ArrayTraits* GetArrayTraits<String>() 
{
    return __traits[MI_STRING];
};

// Array types
typedef Array<Boolean> BooleanA;
typedef Array<Uint8> Uint8A;
typedef Array<Sint8> Sint8A;
typedef Array<Uint16> Uint16A;
typedef Array<Sint16> Sint16A;
typedef Array<Uint32> Uint32A;
typedef Array<Sint32> Sint32A;
typedef Array<Uint64> Uint64A;
typedef Array<Sint64> Sint64A;
typedef Array<Real32> Real32A;
typedef Array<Real64> Real64A;
typedef Array<Datetime> DatetimeA;
typedef Array<String> StringA;
typedef Array<Char16> Char16A;

typedef MI_Result Result;

MI_END_NAMESPACE

#endif /* _micxx_types_h */
