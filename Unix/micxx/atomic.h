/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _micxx_atomic_h
#define _micxx_atomic_h

#include "linkage.h"

MI_BEGIN_NAMESPACE

#if !defined(macos)
typedef struct _Atomic
#else
typedef struct _AtomicType
#endif
{
    MI_Uint64 __opaque;
}
AtomicType;

MICXX_LINKAGE unsigned int AtomicGet(const AtomicType& x);

MICXX_LINKAGE void AtomicSet(AtomicType& x, unsigned int n);

MICXX_LINKAGE void AtomicInc(AtomicType& x);

MICXX_LINKAGE bool AtomicDec(AtomicType& x);

MI_END_NAMESPACE

#endif /* _micxx_atomic_h */
