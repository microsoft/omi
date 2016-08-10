/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _omi_types_h
#define _omi_types_h

#include "config.h"
#include <common.h>

BEGIN_EXTERNC

extern const MI_Char* __typeNames[32];
extern MI_Uint8 __typeSizes[32];

INLINE const MI_Char* Type_NameOf(MI_Type type)
{
    MI_Uint32 i = (MI_Uint32)type;
    DEBUG_ASSERT(i < 32);
    return __typeNames[i];
}

INLINE size_t Type_SizeOf(MI_Type type)
{
    MI_Uint32 i = (MI_Uint32)type;
    DEBUG_ASSERT(i < 32);
    return (size_t)__typeSizes[i];
}

INLINE MI_Type Type_ScalarOf(MI_Type type)
{
    return (MI_Type)((MI_Uint32)type & ~MI_ARRAY_BIT);
}

END_EXTERNC

#endif /* _omi_types_h */
