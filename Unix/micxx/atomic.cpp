/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
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
