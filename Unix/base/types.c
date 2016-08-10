/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#include "types.h"
#include <pal/palcommon.h>

const MI_Char* __typeNames[32] =
{
    PAL_T("BOOLEAN"),
    PAL_T("UINT8"),
    PAL_T("SINT8"),
    PAL_T("UINT16"),
    PAL_T("SINT16"),
    PAL_T("UINT32"),
    PAL_T("SINT32"),
    PAL_T("UINT64"),
    PAL_T("SINT64"),
    PAL_T("REAL32"),
    PAL_T("REAL64"),
    PAL_T("CHAR16"),
    PAL_T("DATETIME"),
    PAL_T("STRING"),
    PAL_T("REFERENCE"),
    PAL_T("INSTANCE"),
    PAL_T("BOOLEANA"),
    PAL_T("UINT8A"),
    PAL_T("SINT8A"),
    PAL_T("UINT16A"),
    PAL_T("SINT16A"),
    PAL_T("UINT32A"),
    PAL_T("SINT32A"),
    PAL_T("UINT64A"),
    PAL_T("SINT64A"),
    PAL_T("REAL32A"),
    PAL_T("REAL64A"),
    PAL_T("CHAR16A"),
    PAL_T("DATETIMEA"),
    PAL_T("STRINGA"),
    PAL_T("REFERENCEA"),
    PAL_T("INSTANCEA"),
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
