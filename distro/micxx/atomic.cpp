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

#include "atomic.h"
#include <base/atomic.h>

MI_BEGIN_NAMESPACE

//==============================================================================
//
// AtomicType
//
//==============================================================================

inline AtomicInt& AtomicRef(AtomicType& x)
{
    return *((AtomicInt*)&x);
}

inline const AtomicInt& AtomicRef(const AtomicType& x)
{
    return *((const AtomicInt*)&x);
}

unsigned int AtomicGet(const AtomicType& x)
{
    return AtomicRef(x);
}

void AtomicSet(AtomicType& x, unsigned int n)
{
    AtomicRef(x) = n;
}

void AtomicInc(AtomicType& x)
{
    ::AtomicInc(&AtomicRef(x));
}

bool AtomicDec(AtomicType& x)
{
    return ::AtomicDec(&AtomicRef(x)) ? true : false;
}

MI_END_NAMESPACE
