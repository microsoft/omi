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

#ifndef _micxx_atomic_h
#define _micxx_atomic_h

#include "linkage.h"

MI_BEGIN_NAMESPACE

typedef struct _Atomic
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
