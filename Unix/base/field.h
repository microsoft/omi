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

#ifndef _omi_field_h
#define _omi_field_h

#include "config.h"
#include <string.h>
#include <common.h>
#include "batch.h"
#include "types.h"

BEGIN_EXTERNC

typedef union _Field
{
    MI_BooleanField boolean;
    MI_Uint8Field uint8;
    MI_Sint8Field sint8;
    MI_Uint16Field uint16;
    MI_Sint16Field sint16;
    MI_Uint32Field uint32;
    MI_Sint32Field sint32;
    MI_Uint64Field uint64;
    MI_Sint64Field sint64;
    MI_Real32Field real32;
    MI_Real64Field real64;
    MI_Char16Field char16;
    MI_DatetimeField datetime;
    MI_StringField string;
    MI_ReferenceField reference;
    MI_InstanceField instance;
    MI_BooleanAField booleana;
    MI_Uint8AField uint8a;
    MI_Sint8AField sint8a;
    MI_Uint16AField uint16a;
    MI_Sint16AField sint16a;
    MI_Uint32AField uint32a;
    MI_Sint32AField sint32a;
    MI_Uint64AField uint64a;
    MI_Sint64AField sint64a;
    MI_Real32AField real32a;
    MI_Real64AField real64a;
    MI_Char16AField char16a;
    MI_DatetimeAField datetimea;
    MI_StringAField stringa;
    MI_ReferenceAField referencea;
    MI_InstanceAField instancea;
    MI_ArrayField array;
}
Field;

MI_Result Field_Construct(
    Field* self,
    MI_Type type,
    const MI_Value* value,
    MI_Uint32 flags,
    Batch* batch);

void Field_Destruct(
    Field* self,
    MI_Type type,
    Batch* batch);

void Field_Clear(
    Field* self,
    MI_Type type,
    Batch* batch);

MI_Result Field_Set(
    Field* self,
    MI_Type type,
    const MI_Value* value,
    MI_Uint32 flags,
    Batch* batch);

MI_Result Field_Copy(
    Field* self,
    MI_Type type,
    const Field* field,
    Batch* batch);

void Field_Extract(
    const Field* field,
    MI_Type type,
    MI_Value* valueOut,
    MI_Boolean* existsOut,
    MI_Uint8* flagsOut);

void Field_Print(
    const Field* self,
    FILE* os, 
    MI_Type type, 
    MI_Uint32 level,
    MI_Boolean showNulls,
    MI_Boolean isClass);

MI_INLINE MI_Boolean Field_GetExists(
    const Field* field, 
    MI_Type type)
{
    return *((MI_Boolean*)((char*)field + Type_SizeOf(type)));
}

MI_INLINE MI_Uint8 Field_GetFlags(
    const Field* field, 
    MI_Type type)
{
    return *((MI_Uint8*)
        ((char*)field + Type_SizeOf(type) + sizeof(MI_Uint8)));
}

#define _MODIFIED 0x02 
MI_INLINE MI_Uint32 Field_GetFlagsExt(MI_Type type, const Field *field)
{
    MI_Value value;
    MI_Boolean exists;
    MI_Uint8 flags;
    MI_Uint32 flagsOut = 0;
    
    Field_Extract(field, type, &value, &exists, &flags);
    
    if(!exists)
    {
        flagsOut |= MI_FLAG_NULL;
    }    

    if ((flags & _MODIFIED) == 0)
    {
        flagsOut |= MI_FLAG_NOT_MODIFIED;
    }
    
    return flagsOut;
}

/* Return true if fields are equivalent (only applies to key types) */
MI_Boolean Field_MatchKey(
    const Field* field1,
    const Field* field2, 
    MI_Type type);

END_EXTERNC

#endif /* _omi_field_h */
