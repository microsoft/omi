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
