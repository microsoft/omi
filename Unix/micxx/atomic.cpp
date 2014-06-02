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
#include <pal/atomic.h>

MI_BEGIN_NAMESPACE

//==============================================================================
//
// AtomicType
//
//==============================================================================

unsigned int AtomicGet(const AtomicType& x)
{
    return (unsigned int)Atomic_Read((ptrdiff_t*)&x.__opaque);
}

void AtomicSet(AtomicType& x, unsigned int n)
{
    *((ptrdiff_t*)&x.__opaque) = (ptrdiff_t)n;
}

void AtomicInc(AtomicType& x)
{
    Atomic_Inc((ptrdiff_t*)&x.__opaque);
}

bool AtomicDec(AtomicType& x)
{
    return Atomic_Dec((ptrdiff_t*)&x.__opaque) == 0 ? true : false;
}

MI_END_NAMESPACE
