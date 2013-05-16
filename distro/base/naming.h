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

#ifndef _base_naming_h
#define _base_naming_h

#include "config.h"
#include <common.h>
#include "strings.h"

BEGIN_EXTERNC

extern const MI_Uint8 __omi_ToLowerTable[256];

/* Return MI_TRUE if name is a legal CIM name */
MI_Boolean LegalName(const ZChar* name);

/* Return lowercase of this character */
MI_INLINE MI_Uint8 ToLower(MI_Uint8 x)
{
    return __omi_ToLowerTable[x];
}

/* Return hash code os this name */
MI_INLINE MI_Uint32 Hash(const ZChar* name)
{
    MI_Uint32 n = (MI_Uint32)Zlen(name);

    if (n == 0)
        return 0;

    return ToLower((MI_Uint8)name[0]) << 16 |
        ToLower((MI_Uint8)name[n-1]) << 8 | n;
}

/* Determine the length of a name by its code */
MI_INLINE MI_Uint32 NameLen(const ZChar* name, MI_Uint32 code)
{
    /* The 8 least signifiant bits of the length (possibly full length) */
    MI_Uint32 n = code & 0xFF;
    return name[n] ? (n + (MI_Uint32)Zlen(name + n)) : n;
}

END_EXTERNC

#endif /* _base_naming_h */
