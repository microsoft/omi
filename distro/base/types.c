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

#include "types.h"

const char* __typeNames[32] =
{
    "BOOLEAN",
    "UINT8",
    "SINT8",
    "UINT16",
    "SINT16",
    "UINT32",
    "SINT32",
    "UINT64",
    "SINT64",
    "REAL32",
    "REAL64",
    "CHAR16",
    "DATETIME",
    "STRING",
    "REFERENCE",
    "INSTANCE",
    "BOOLEANA",
    "UINT8A",
    "SINT8A",
    "UINT16A",
    "SINT16A",
    "UINT32A",
    "SINT32A",
    "UINT64A",
    "SINT64A",
    "REAL32A",
    "REAL64A",
    "CHAR16A",
    "DATETIMEA",
    "STRINGA",
    "REFERENCEA",
    "INSTANCEA",
};

MI_Uint8 __typeSizes[32] =
{
    sizeof(MI_Boolean),
    sizeof(MI_Uint8),
    sizeof(MI_Sint8),
    sizeof(MI_Uint16),
    sizeof(MI_Sint16),
    sizeof(MI_Uint32),
    sizeof(MI_Sint32),
    sizeof(MI_Uint64),
    sizeof(MI_Sint64),
    sizeof(MI_Real32),
    sizeof(MI_Real64),
    sizeof(MI_Char16),
    sizeof(MI_Datetime),
    sizeof(MI_String),
    sizeof(MI_Instance*), /* reference */
    sizeof(MI_Instance*), /* instance */
    sizeof(MI_BooleanA),
    sizeof(MI_Uint8A),
    sizeof(MI_Sint8A),
    sizeof(MI_Uint16A),
    sizeof(MI_Sint16A),
    sizeof(MI_Uint32A),
    sizeof(MI_Sint32A),
    sizeof(MI_Uint64A),
    sizeof(MI_Sint64A),
    sizeof(MI_Real32A),
    sizeof(MI_Real64A),
    sizeof(MI_Char16A),
    sizeof(MI_DatetimeA),
    sizeof(MI_StringA),
    sizeof(MI_InstanceA),
    sizeof(MI_InstanceA),
};
