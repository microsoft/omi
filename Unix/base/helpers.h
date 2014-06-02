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

#ifndef _base_helpers_h
#define _base_helpers_h

#include "instance.h"

BEGIN_EXTERNC

MI_Result MI_CALL Instance_SetElementFromString(
    MI_Instance* self, 
    const ZChar* name, 
    const ZChar* str,
    MI_Uint32 flags);

MI_Result MI_CALL Instance_SetElementFromStringA(
    MI_Instance* self_, 
    const ZChar* name, 
    const ZChar** data,
    MI_Uint32 size,
    MI_Uint32 flags);

MI_Result MI_CALL Instance_GetValue(
    MI_Instance* self,
    const ZChar* name,
    void* value,
    MI_Type type);

MI_INLINE MI_Result Instance_SetBoolean(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Boolean x)
{
    return MI_Instance_SetElement(self, name, (MI_Value*)&x, MI_BOOLEAN, 0);
}

MI_INLINE MI_Result Instance_SetUint8(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Uint8 x)
{
    return MI_Instance_SetElement(self, name, (MI_Value*)&x, MI_UINT8, 0);
}

MI_INLINE MI_Result Instance_SetSint8(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Sint8 x)
{
    return MI_Instance_SetElement(self, name, (MI_Value*)&x, MI_SINT8, 0);
}

MI_INLINE MI_Result Instance_SetUint16(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Uint16 x)
{
    return MI_Instance_SetElement(self, name, (MI_Value*)&x, MI_UINT16, 0);
}

MI_INLINE MI_Result Instance_SetSint16(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Sint16 x)
{
    return MI_Instance_SetElement(self, name, (MI_Value*)&x, MI_SINT16, 0);
}

MI_INLINE MI_Result Instance_SetUint32(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Uint32 x)
{
    return MI_Instance_SetElement(self, name, (MI_Value*)&x, MI_UINT32, 0);
}

MI_INLINE MI_Result Instance_SetSint32(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Sint32 x)
{
    return MI_Instance_SetElement(self, name, (MI_Value*)&x, MI_SINT32, 0);
}

MI_INLINE MI_Result Instance_SetUint64(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Uint64 x)
{
    return MI_Instance_SetElement(self, name, (MI_Value*)&x, MI_UINT64, 0);
}

MI_INLINE MI_Result Instance_SetSint64(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Sint64 x)
{
    return MI_Instance_SetElement(self, name, (MI_Value*)&x, MI_SINT64, 0);
}

MI_INLINE MI_Result Instance_SetReal32(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Real32 x)
{
    return MI_Instance_SetElement(self, name, (MI_Value*)&x, MI_REAL32, 0);
}

MI_INLINE MI_Result Instance_SetReal64(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Real64 x)
{
    return MI_Instance_SetElement(self, name, (MI_Value*)&x, MI_REAL64, 0);
}

MI_INLINE MI_Result Instance_SetChar16(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Char16 x)
{
    return MI_Instance_SetElement(self, name, (MI_Value*)&x, MI_CHAR16, 0);
}

MI_INLINE MI_Result Instance_SetDatetime(
    MI_Instance* self, 
    const ZChar* name, 
    const MI_Datetime* x)
{
    return MI_Instance_SetElement(self, name, (MI_Value*)x, MI_DATETIME, 0);
}

MI_INLINE MI_Result Instance_SetString(
    MI_Instance* self, 
    const ZChar* name, 
    const ZChar* str)
{
    MI_Value value;
    value.string = (ZChar*)str;
    return MI_Instance_SetElement(self, name, &value, MI_STRING, 0);
}

MI_INLINE MI_Result Instance_GetBoolean(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Boolean* x)
{
    return Instance_GetValue(self, name, x, MI_BOOLEAN);
}

MI_INLINE MI_Result Instance_GetUint8(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Uint8* x)
{
    return Instance_GetValue(self, name, x, MI_UINT8);
}

MI_INLINE MI_Result Instance_GetSint8(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Sint8* x)
{
    return Instance_GetValue(self, name, x, MI_SINT8);
}

MI_INLINE MI_Result Instance_GetUint16(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Uint16* x)
{
    return Instance_GetValue(self, name, x, MI_UINT16);
}

MI_INLINE MI_Result Instance_GetSint16(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Sint16* x)
{
    return Instance_GetValue(self, name, x, MI_SINT16);
}

MI_INLINE MI_Result Instance_GetUint32(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Uint32* x)
{
    return Instance_GetValue(self, name, x, MI_UINT32);
}

MI_INLINE MI_Result Instance_GetSint32(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Sint32* x)
{
    return Instance_GetValue(self, name, x, MI_SINT32);
}

MI_INLINE MI_Result Instance_GetUint64(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Uint64* x)
{
    return Instance_GetValue(self, name, x, MI_UINT64);
}

MI_INLINE MI_Result Instance_GetSint64(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Sint64* x)
{
    return Instance_GetValue(self, name, x, MI_SINT64);
}

MI_INLINE MI_Result Instance_GetReal32(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Real32* x)
{
    return Instance_GetValue(self, name, x, MI_REAL32);
}

MI_INLINE MI_Result Instance_GetReal64(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Real64* x)
{
    return Instance_GetValue(self, name, x, MI_REAL64);
}

MI_INLINE MI_Result Instance_GetChar16(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Char16* x)
{
    return Instance_GetValue(self, name, x, MI_CHAR16);
}

MI_INLINE MI_Result Instance_GetDatetime(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Datetime* x)
{
    return Instance_GetValue(self, name, x, MI_DATETIME);
}

MI_INLINE MI_Result Instance_GetString(
    MI_Instance* self, 
    const ZChar* name, 
    _Out_ MI_String* x)
{
    return Instance_GetValue(self, name, x, MI_STRING);
}

MI_INLINE MI_Result Instance_GetInstance(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Instance** x)
{
    return Instance_GetValue(self, name, x, MI_INSTANCE);
}

MI_INLINE MI_Result Instance_GetReference(
    MI_Instance* self, 
    const ZChar* name, 
    MI_Instance** x)
{
    return Instance_GetValue(self, name, x, MI_REFERENCE);
}

int StrToChar16(const ZChar* str, MI_Char16* x);

int StrToDatetime(const ZChar* s, MI_Datetime* x);

int StrToBoolean(const ZChar* str, MI_Boolean* x);

int StrToUint8(const ZChar* str, MI_Uint8* x);

int StrToSint8(const ZChar* str, MI_Sint8* x);

int StrToUint16(const ZChar* str, MI_Uint16* x);

int StrToSint16(const ZChar* str, MI_Sint16* x);

int StrToUint32(const ZChar* str, MI_Uint32* x);

int StrToSint32(const ZChar* str, MI_Sint32* x);

int StrToUint64(const ZChar* str, MI_Uint64* x);

int StrToSint64(const ZChar* str, MI_Sint64* x);

int StrToReal32(const ZChar* str, MI_Real32* x);

int StrToReal64(const ZChar* str, MI_Real64* x);

void DatetimeToStr(const MI_Datetime* x, _Out_writes_z_(26) ZChar buf[26]);

int ParseWSManDatetime(const ZChar* str, MI_Datetime* x);

void FormatWSManDatetime(const MI_Datetime* x, _Out_writes_z_(64) ZChar buffer[64]);

int DatetimeToUsec( const MI_Datetime* x, MI_Uint64* dateTimeAsUsec );

END_EXTERNC

#endif /* _base_helpers_h */
